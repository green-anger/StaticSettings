#pragma once

#include <mutex>
#include <stdexcept>
#include <unordered_map>

#include <boost/any.hpp>
#include <boost/signals2.hpp>

#include "TypeRegister.hpp"


namespace alt {


    class StaticSettings
    {
    public:
        template<typename P, P p>
        static void setProperty( typename Type<P, p>::type value );

        template<typename P, P p>
        static auto getProperty();

        template<typename P>
        struct Signaller
        {
            static boost::signals2::signal<void( P )> changed;
        };

        class NoProperty : std::runtime_error
        {
        public:
            NoProperty() : std::runtime_error( "StaticSettings doesn't have property!" ) {}

            virtual const char* what() const override
            {
                return std::runtime_error::what();
            }
        };

    private:
        template<typename P>
        struct Mapper
        {
            static std::mutex mutex_;
            static std::unordered_map<P, boost::any> property_;
        };
    };


    template<typename P>
    boost::signals2::signal<void( P )> StaticSettings::Signaller<P>::changed;


    template<typename P>
    std::mutex StaticSettings::Mapper<P>::mutex_;


    template<typename P>
    std::unordered_map<P, boost::any> StaticSettings::Mapper<P>::property_ = {};


    template<typename P, P p>
    inline void StaticSettings::setProperty( typename Type<P, p>::type value )
    {
        {
            std::lock_guard<std::mutex> lock( StaticSettings::Mapper<P>::mutex_ );
            StaticSettings::Mapper<P>::property_[p] = value;
        }
        StaticSettings::Signaller<P>::changed( p );
    }


    template<typename P, P p>
    inline auto StaticSettings::getProperty()
    {
        boost::any result;
        {
            std::lock_guard<std::mutex> lock( StaticSettings::Mapper<P>::mutex_ );
            auto it = StaticSettings::Mapper<P>::property_.find( p );

            if ( it == StaticSettings::Mapper<P>::property_.end() )
            {
                throw StaticSettings::NoProperty();
            }
            result = it->second;
        }

        return boost::any_cast<typename Type<P, p>::type>( result );
    }


}
