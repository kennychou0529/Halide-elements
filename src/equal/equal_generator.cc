#include <cstdint>
#include "Halide.h"
#include "Element.h"

using namespace Halide;
using Halide::Element::schedule;

template<typename T>
class Equal : public Halide::Generator<Equal<T>> {
public:
    ImageParam src0{type_of<T>(), 2, "src0"}
    ImageParam src1{type_of<T>(), 2, "src1"};

    GeneratorParam<int32_t> width{"width", 1024};
    GeneratorParam<int32_t> height{"height", 768};

    Func build() {
        Func dst{"dst"};

        dst = Element::equal<T>(src0, src1);

        schedule(src0, {width, height});
        schedule(src1, {width, height});
        schedule(dst, {width, height});

        return dst;
    }
};

RegisterGenerator<Equal<uint8_t>> equal_u8{"equal_u8"};
RegisterGenerator<Equal<uint16_t>> equal_u16{"equal_u16"};
RegisterGenerator<Equal<uint32_t>> equal_u32{"equal_u32"};
