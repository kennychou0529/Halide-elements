#include <cstdint>

#include "Halide.h"
#include "Element.h"

using namespace Halide;
using Halide::Element::schedule;

template<typename T>
class Cmpgt : public Halide::Generator<Cmpgt<T>> {
public:
    ImageParam src0{type_of<T>(), 2, "src0"};
    ImageParam src1{type_of<T>(), 2, "src1"};

    GeneratorParam<int32_t> width{"width", 1024};
    GeneratorParam<int32_t> height{"height", 768};

    Func build() {
        Func dst{"dst"};

        dst = Element::cmpgt<T>(src0, src1);

        schedule(src0, {width, height});
        schedule(src1, {width, height});
        schedule(dst, {width, height});

        return dst;
    }
};

RegisterGenerator<Cmpgt<uint8_t>> cmpgt_u8{"cmpgt_u8"};
RegisterGenerator<Cmpgt<uint16_t>> cmpgt_u16{"cmpgt_u16"};
RegisterGenerator<Cmpgt<uint32_t>> cmpgt_u32{"cmpgt_u32"};
