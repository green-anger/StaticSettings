## What is StaticSettings?

[StaticSettings](https://github.com/green-anger/StaticSettings) is a header-only library allowing you to
setup different type settings (properties) for your application (or its part) and access them from anywhere
in a uniform and thread safe manner. It is not a Singleton, but it mostly consists of static variables, hence the name.

## How to use it

First of all you must define an entity with some properties in enum class:
```c++
enum class Label
{
    Size,
    Text,
    Weight,
};
```

Then you must declare actual types for these properties:
```c++
DECLARE_PROPERTY_TYPE( property::Label, property::Label::Size, int )
DECLARE_PROPERTY_TYPE( property::Label, property::Label::Text, std::string )
DECLARE_PROPERTY_TYPE( property::Label, property::Label::Weight, double )
```

And you're ready to use them from anywhere:
```c++
alt::StaticSettings::setProperty<Label, Label::Size>( 10 );
alt::StaticSettings::setProperty<Label, Label::Text>( "Label name" );
auto labelSize = alt::StaticSettings::getProperty<Label, Label::Size>();
auto labelText = alt::StaticSettings::getProperty<Label, Label::Text>();
```

For full demo including thread safe testing see [provided example](./examples).

Note: Properties doesn't have a default value, so getting it before it's been set will raise an exception.

## Benefits

* Produces compile time error:
    - If you use a property and haven't declared its type
    - If you use a property and have declared its type more than once
    - If you set a property value of type that cannot be casted to property type
* Can use custom types in property declaration
* Uniform access to properties regardless of declared types
* Property change subscription
* Thread safe
* Small codebase (around 100 lines)

## Dependencies

General:
* C++14

Embedded into the example source code for testing purpose (not needed for usage):
* [ThreadSafePrinter](https://github.com/green-anger/ThreadSafePrinter/)

Library
* [Boost](https://www.boost.org/) 1.39.0
    - [Boost.Any](https://www.boost.org/doc/libs/1_68_0/doc/html/any.html)
    - [Boost.Signals2](https://www.boost.org/doc/libs/release/libs/signals2/)

Note: As the library itself cannot include above-mentioned libraries, you will have to do it
for your project. In case of boost it's quite easy, just download, extract and point to it.

Note: If you're using C++17 compiler and don't need a subscription to property change, in the source
code remove Signaller struct and all calls to it, replace Boost.Any with std::any and you will have
no dependencies at all.

## Versioning

StaticSettings uses [Semantic Versioning 2.0.0](https://semver.org/).

## License

StaticSettings is licensed under [MIT License](./LICENSE).
