#include <iostream>

#include "DeclareTypes.h"
#include "MoreProperty.h"
#include "StaticSettings.hpp"
#include "ThreadSafePrinter.hpp"
#include "Worker.h"


using namespace property;
using TSP = alt::ThreadSafePrinter<alt::MarkPolicy>;


int Worker::uid_ = 0;


Worker::Worker()
    : id_( ++uid_ )
{
    TSP() << "Created Worker with id " << id_;

    // Just to show usage in different translation units
    alt::StaticSettings::setProperty<Label, Label::Size>( id_ );

    t_.reset( new std::thread( [id = this->id_]() {
        TSP() << "In lambda id " << id;
        for ( int i = 0; i < 10; ++i )
        {
            TSP() << id << "(" << i << ")";
            alt::StaticSettings::setProperty<Demo, Demo::Id>( id );
        }
    } ) );
}


Worker::~Worker()
{
    if ( t_ && t_->joinable() )
    {
        t_->join();
    }
}
