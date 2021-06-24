<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * यंत्र-generic/पूर्णांक-ll64.h
 *
 * Integer declarations क्रम architectures which use "long long"
 * क्रम 64-bit types.
 */
#अगर_अघोषित _ASM_GENERIC_INT_LL64_H
#घोषणा _ASM_GENERIC_INT_LL64_H

#समावेश <uapi/यंत्र-generic/पूर्णांक-ll64.h>


#अगर_अघोषित __ASSEMBLY__

प्रकार __s8  s8;
प्रकार __u8  u8;
प्रकार __s16 s16;
प्रकार __u16 u16;
प्रकार __s32 s32;
प्रकार __u32 u32;
प्रकार __s64 s64;
प्रकार __u64 u64;

#घोषणा S8_C(x)  x
#घोषणा U8_C(x)  x ## U
#घोषणा S16_C(x) x
#घोषणा U16_C(x) x ## U
#घोषणा S32_C(x) x
#घोषणा U32_C(x) x ## U
#घोषणा S64_C(x) x ## LL
#घोषणा U64_C(x) x ## ULL

#अन्यथा /* __ASSEMBLY__ */

#घोषणा S8_C(x)  x
#घोषणा U8_C(x)  x
#घोषणा S16_C(x) x
#घोषणा U16_C(x) x
#घोषणा S32_C(x) x
#घोषणा U32_C(x) x
#घोषणा S64_C(x) x
#घोषणा U64_C(x) x

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_GENERIC_INT_LL64_H */
