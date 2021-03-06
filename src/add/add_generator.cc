#include <cstdint>
#include "Halide.h"

#include "Element.h"

using namespace Halide;
using Halide::Element::schedule;

template<typename T>
class Add : public Halide::Generator<Add<T>> {
    ImageParam src0{type_of<T>(), 2, "src0"};
    ImageParam src1{type_of<T>(), 2, "src1"};

    GeneratorParam<int32_t> width{"width", 1024};
    GeneratorParam<int32_t> height{"height", 768};

public:
    Func build() {
        Func dst{"dst"};

        dst =  Element::add<T>(src0, src1);

        schedule(src0, {width, height});
        schedule(src1, {width, height});
        schedule(dst, {width, height});

        return dst;
    }
};

RegisterGenerator<Add<uint8_t>> add_u8{"add_u8"};
RegisterGenerator<Add<uint16_t>> add_u16{"add_u16"};
RegisterGenerator<Add<uint32_t>> add_u32{"add_u32"};
