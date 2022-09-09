#ifndef NPY_SIMD
#error "Not a standalone header"
#endif

#ifndef _NPY_SIMD_SVE_OPERATORS_H
#define _NPY_SIMD_SVE_OPERATORS_H

/***************************
 * Shifting
 ***************************/
// left
#define NPYV_IMPL_SVE_SHIFT_L(SIGN, WIDTH)                    \
    NPY_FINLINE npyv_##SIGN##WIDTH npyv_shl_##SIGN##WIDTH(    \
            npyv_##SIGN##WIDTH A, npy_uintp C)                \
    {                                                         \
        return svlsl_##SIGN##WIDTH##_x(svptrue_b##WIDTH(), A, \
                                       svdup_n_u##WIDTH(C));  \
    }

NPYV_IMPL_SVE_SHIFT_L(u, 8)
NPYV_IMPL_SVE_SHIFT_L(u, 16)
NPYV_IMPL_SVE_SHIFT_L(u, 32)
NPYV_IMPL_SVE_SHIFT_L(u, 64)
NPYV_IMPL_SVE_SHIFT_L(s, 8)
NPYV_IMPL_SVE_SHIFT_L(s, 16)
NPYV_IMPL_SVE_SHIFT_L(s, 32)
NPYV_IMPL_SVE_SHIFT_L(s, 64)

// left by an immediate constant
#define NPYV_IMPL_SVE_SHIFT_L_IMM(WIDTH)                            \
    NPY_FINLINE npyv_u##WIDTH npyv_shli_u##WIDTH(npyv_u##WIDTH A,   \
                                                 npy_uint##WIDTH C) \
    {                                                               \
        return svlsl_n_u##WIDTH##_x(svptrue_b##WIDTH(), A, C);      \
    }                                                               \
    NPY_FINLINE npyv_s##WIDTH npyv_shli_s##WIDTH(npyv_s##WIDTH A,   \
                                                 npy_uint##WIDTH C) \
    {                                                               \
        return svlsl_n_s##WIDTH##_x(svptrue_b##WIDTH(), A, C);      \
    }

NPYV_IMPL_SVE_SHIFT_L_IMM(8)
NPYV_IMPL_SVE_SHIFT_L_IMM(16)
NPYV_IMPL_SVE_SHIFT_L_IMM(32)
NPYV_IMPL_SVE_SHIFT_L_IMM(64)

// right
#define NPYV_IMPL_SVE_SHIFT_R(WIDTH)                                         \
    NPY_FINLINE npyv_u##WIDTH npyv_shr_u##WIDTH(npyv_u##WIDTH A, npy_intp C) \
    {                                                                        \
        return svlsr_u##WIDTH##_x(svptrue_b##WIDTH(), A,                     \
                                  svdup_n_u##WIDTH(C));                      \
    }                                                                        \
    NPY_FINLINE npyv_s##WIDTH npyv_shr_s##WIDTH(npyv_s##WIDTH A, npy_intp C) \
    {                                                                        \
        return svasr_s##WIDTH##_x(svptrue_b##WIDTH(), A,                     \
                                  svdup_n_u##WIDTH(C));                      \
    }

NPYV_IMPL_SVE_SHIFT_R(8)
NPYV_IMPL_SVE_SHIFT_R(16)
NPYV_IMPL_SVE_SHIFT_R(32)
NPYV_IMPL_SVE_SHIFT_R(64)

// right by an immediate constant
#define NPYV_IMPL_SVE_SHIFT_R_IMM(WIDTH)                            \
    NPY_FINLINE npyv_u##WIDTH npyv_shri_u##WIDTH(npyv_u##WIDTH A,   \
                                                 npy_uint##WIDTH C) \
    {                                                               \
        return svlsr_n_u##WIDTH##_x(svptrue_b##WIDTH(), A, C);      \
    }                                                               \
    NPY_FINLINE npyv_s##WIDTH npyv_shri_s##WIDTH(npyv_s##WIDTH A,   \
                                                 npy_uint##WIDTH C) \
    {                                                               \
        return svasr_n_s##WIDTH##_x(svptrue_b##WIDTH(), A, C);      \
    }

NPYV_IMPL_SVE_SHIFT_R_IMM(8)
NPYV_IMPL_SVE_SHIFT_R_IMM(16)
NPYV_IMPL_SVE_SHIFT_R_IMM(32)
NPYV_IMPL_SVE_SHIFT_R_IMM(64)

/***************************
 * Logical
 ***************************/
#define NPYV_IMPL_SVE_LOGICAL(SFX0, SFX1, SFX2)                           \
    NPY_FINLINE npyv_##SFX0 npyv_and_##SFX0(npyv_##SFX0 a, npyv_##SFX0 b) \
    {                                                                     \
        return svreinterpret_##SFX0##_##SFX2(svand_##SFX2##_x(            \
                svptrue_##SFX1(), svreinterpret_##SFX2##_##SFX0(a),       \
                svreinterpret_##SFX2##_##SFX0(b)));                       \
    }                                                                     \
    NPY_FINLINE npyv_##SFX0 npyv_or_##SFX0(npyv_##SFX0 a, npyv_##SFX0 b)  \
    {                                                                     \
        return svreinterpret_##SFX0##_##SFX2(svorr_##SFX2##_x(            \
                svptrue_##SFX1(), svreinterpret_##SFX2##_##SFX0(a),       \
                svreinterpret_##SFX2##_##SFX0(b)));                       \
    }                                                                     \
    NPY_FINLINE npyv_##SFX0 npyv_xor_##SFX0(npyv_##SFX0 a, npyv_##SFX0 b) \
    {                                                                     \
        return svreinterpret_##SFX0##_##SFX2(sveor_##SFX2##_x(            \
                svptrue_##SFX1(), svreinterpret_##SFX2##_##SFX0(a),       \
                svreinterpret_##SFX2##_##SFX0(b)));                       \
    }                                                                     \
    NPY_FINLINE npyv_##SFX0 npyv_not_##SFX0(npyv_##SFX0 a)                \
    {                                                                     \
        return svreinterpret_##SFX0##_##SFX2(svnot_##SFX2##_x(            \
                svptrue_##SFX1(), svreinterpret_##SFX2##_##SFX0(a)));     \
    }                                                                     \
    NPY_FINLINE npyv_##SFX0 npyv_andc_##SFX0(npyv_##SFX0 a, npyv_##SFX0 b)\
    {                                                                     \
        return svreinterpret_##SFX0##_##SFX2(svbic_##SFX2##_x(            \
							      svptrue_##SFX1(), svreinterpret_##SFX2##_##SFX0(b), svreinterpret_##SFX2##_##SFX0(a))); \
    }
NPYV_IMPL_SVE_LOGICAL(u8, b8, u8)
NPYV_IMPL_SVE_LOGICAL(u16, b16, u16)
NPYV_IMPL_SVE_LOGICAL(u32, b32, u32)
NPYV_IMPL_SVE_LOGICAL(u64, b64, u64)
NPYV_IMPL_SVE_LOGICAL(s8, b8, s8)
NPYV_IMPL_SVE_LOGICAL(s16, b16, s16)
NPYV_IMPL_SVE_LOGICAL(s32, b32, s32)
NPYV_IMPL_SVE_LOGICAL(s64, b64, s64)
NPYV_IMPL_SVE_LOGICAL(f32, b32, u32)
NPYV_IMPL_SVE_LOGICAL(f64, b64, u64)

/***************************
 * Logical (boolean)
 ***************************/
#define NPYV_IMPL_SVE_LOGICAL_MASK(SFX)                               \
    NPY_FINLINE npyv_##SFX npyv_and_##SFX(npyv_##SFX a, npyv_##SFX b) \
    {                                                                 \
        return svand_b_z(svptrue_##SFX(), a, b);                      \
    }                                                                 \
    NPY_FINLINE npyv_##SFX npyv_or_##SFX(npyv_##SFX a, npyv_##SFX b)  \
    {                                                                 \
        return svorr_b_z(svptrue_b8(), a, b);                         \
    }                                                                 \
    NPY_FINLINE npyv_##SFX npyv_xor_##SFX(npyv_##SFX a, npyv_##SFX b) \
    {                                                                 \
        return sveor_b_z(svptrue_b8(), a, b);                         \
    }                                                                 \
    NPY_FINLINE npyv_##SFX npyv_not_##SFX(npyv_##SFX a)               \
    {                                                                 \
        return svnot_b_z(svptrue_b8(), a);                            \
    }                                                                 \
    NPY_FINLINE npyv_##SFX npyv_andc_##SFX(npyv_##SFX a, npyv_##SFX b)\
    {                                                                 \
      return svbic_b_z(svptrue_b8(), b, a);                           \
    }                                                                 \
    NPY_FINLINE npyv_##SFX npyv_orc_##SFX(npyv_##SFX a, npyv_##SFX b)\
    {                                                                 \
      return npyv_or_##SFX(npyv_not_##SFX(b), a);		      \
    }                                                                 \
    NPY_FINLINE npyv_##SFX npyv_xnor_##SFX(npyv_##SFX a, npyv_##SFX b)\
    {                                                                 \
      return npyv_not_##SFX(npyv_xor_##SFX(a, b));		      \
    }
NPYV_IMPL_SVE_LOGICAL_MASK(b8)
NPYV_IMPL_SVE_LOGICAL_MASK(b16)
NPYV_IMPL_SVE_LOGICAL_MASK(b32)
NPYV_IMPL_SVE_LOGICAL_MASK(b64)

/***************************
 * Comparison
 ***************************/
// int equal
#define NPYV_IMPL_SVE_COMPARE(SFX, BSFX, SFX1)                \
    NPY_FINLINE npyv_##BSFX npyv_cmpeq_##SFX(SFX1 a, SFX1 b)  \
    {                                                         \
        return svcmpeq_##SFX(svptrue_##BSFX(), a, b);         \
    }                                                         \
    NPY_FINLINE npyv_##BSFX npyv_cmpneq_##SFX(SFX1 a, SFX1 b) \
    {                                                         \
        return svcmpne_##SFX(svptrue_##BSFX(), a, b);         \
    }                                                         \
    NPY_FINLINE npyv_##BSFX npyv_cmpgt_##SFX(SFX1 a, SFX1 b)  \
    {                                                         \
        return svcmpgt_##SFX(svptrue_##BSFX(), a, b);         \
    }                                                         \
    NPY_FINLINE npyv_##BSFX npyv_cmpge_##SFX(SFX1 a, SFX1 b)  \
    {                                                         \
        return svcmpge_##SFX(svptrue_##BSFX(), a, b);         \
    }                                                         \
    NPY_FINLINE npyv_##BSFX npyv_cmplt_##SFX(SFX1 a, SFX1 b)  \
    {                                                         \
        return svcmplt_##SFX(svptrue_##BSFX(), a, b);         \
    }                                                         \
    NPY_FINLINE npyv_##BSFX npyv_cmple_##SFX(SFX1 a, SFX1 b)  \
    {                                                         \
        return svcmple_##SFX(svptrue_##BSFX(), a, b);         \
    }

NPYV_IMPL_SVE_COMPARE(u8, b8, svuint8_t)
NPYV_IMPL_SVE_COMPARE(u16, b16, svuint16_t)
NPYV_IMPL_SVE_COMPARE(u32, b32, svuint32_t)
NPYV_IMPL_SVE_COMPARE(u64, b64, svuint64_t)
NPYV_IMPL_SVE_COMPARE(s8, b8, svint8_t)
NPYV_IMPL_SVE_COMPARE(s16, b16, svint16_t)
NPYV_IMPL_SVE_COMPARE(s32, b32, svint32_t)
NPYV_IMPL_SVE_COMPARE(s64, b64, svint64_t)
NPYV_IMPL_SVE_COMPARE(f32, b32, svfloat32_t)
NPYV_IMPL_SVE_COMPARE(f64, b64, svfloat64_t)

// check special cases
NPY_FINLINE npyv_b32
npyv_notnan_f32(npyv_f32 a)
{
    return svcmpeq(svptrue_b32(), a, a);
}
NPY_FINLINE npyv_b64
npyv_notnan_f64(npyv_f64 a)
{
    return svcmpeq(svptrue_b64(), a, a);
}

#endif  // _NPY_SIMD_SVE_OPERATORS_H
