#pragma once


namespace alt {


    template<typename P, P p>
    struct Type {};


}


#define DECLARE_PROPERTY_TYPE( Prop, Field, T ) \
namespace alt { \
    template<> \
    struct Type<Prop, Field> \
    { \
        using type = T; \
    }; \
} \
