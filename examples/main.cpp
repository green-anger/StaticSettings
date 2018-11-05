#include <cassert>
#include <iostream>
#include <sstream>
#include <typeinfo>

#include "DeclareTypes.h"
#include "MoreProperty.h"
#include "StaticSettings.hpp"
#include "ThreadSafePrinter.hpp"
#include "Worker.h"


using namespace property;
using SS = alt::StaticSettings;
using TSP = alt::ThreadSafePrinter<alt::MarkPolicy>;


int main( int argc, char** argv )
{
    ///// Basic usage

    const int val1 = 10;
    SS::setProperty<Label, Label::Size>( val1 );
    auto get1 = SS::getProperty<Label, Label::Size>();
    assert( val1 == get1 );

    const std::string val2 = "str";
    SS::setProperty<Label, Label::Text>( val2 );
    auto get2 = SS::getProperty<Label, Label::Text>();
    assert( val2 == get2 );

    const double val3 = 3.14159;
    SS::setProperty<Label, Label::Weight>( val3 );
    auto get3 = SS::getProperty<Label, Label::Weight>();
    assert( val3 == get3 );

    const std::vector<std::string> val4 = { "one", "two", "three" };
    SS::setProperty<List, List::Items>( val4 );
    auto get4 = SS::getProperty<List, List::Items>();
    assert( val4 == get4 );

    // Getting property that has not been set yet => throw
    try {
        auto get5 = SS::getProperty<List, List::Letter>();
    }
    catch( SS::NoProperty ) {
        std::cout << "No such property!" << std::endl;
    }

    // Shows that getProperty always returns declared type
    const char val5 = 'L';
    SS::setProperty<List, List::Letter>( val5 );
    auto get5 = SS::getProperty<List, List::Letter>();
    assert( val5 == get5 );
    assert( typeid( val5 ) != typeid( get5 ) );

    const unsigned char val6 = 'M';
    SS::setProperty<List, List::Letter>( val6 );
    auto get6 = SS::getProperty<List, List::Letter>();
    assert( val6 == get6 );
    assert( typeid( val6 ) == typeid( get6 ) );


    ///// Thread safe testing

    SS::setProperty<Demo, Demo::Id>( 0 );

    {
        // Workers will set property in separate threads
        std::vector<Worker> workers;

        // Subscribe to property change
        SS::Signaller<Demo>::changed.connect( []( Demo val ) {
            if ( Demo::Id == val )
            {
                auto id = SS::getProperty<Demo, Demo::Id>();
                TSP() << "Demo::Id changed to " << id;
            }
        } );

        // Create workers
        for ( int i = 0; i < 50; ++i )
        {
            workers.emplace_back( Worker() );
        }
    }

    std::cout << "Final Demo::Id value = "
        << SS::getProperty<Demo, Demo::Id>()
        << std::endl;

    return 0;
}
