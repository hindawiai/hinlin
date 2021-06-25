<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RECIPROCAL_DIV_H
#घोषणा _LINUX_RECIPROCAL_DIV_H

#समावेश <linux/types.h>

/*
 * This algorithm is based on the paper "Division by Invariant
 * Integers Using Multiplication" by Torbjथघrn Granlund and Peter
 * L. Montgomery.
 *
 * The assembler implementation from Agner Fog, which this code is
 * based on, can be found here:
 * http://www.agner.org/optimize/यंत्रlib.zip
 *
 * This optimization क्रम A/B is helpful अगर the भागisor B is mostly
 * runसमय invariant. The reciprocal of B is calculated in the
 * slow-path with reciprocal_value(). The fast-path can then just use
 * a much faster multiplication operation with a variable भागidend A
 * to calculate the भागision A/B.
 */

काष्ठा reciprocal_value अणु
	u32 m;
	u8 sh1, sh2;
पूर्ण;

/* "reciprocal_value" and "reciprocal_divide" together implement the basic
 * version of the algorithm described in Figure 4.1 of the paper.
 */
काष्ठा reciprocal_value reciprocal_value(u32 d);

अटल अंतरभूत u32 reciprocal_भागide(u32 a, काष्ठा reciprocal_value R)
अणु
	u32 t = (u32)(((u64)a * R.m) >> 32);
	वापस (t + ((a - t) >> R.sh1)) >> R.sh2;
पूर्ण

काष्ठा reciprocal_value_adv अणु
	u32 m;
	u8 sh, exp;
	bool is_wide_m;
पूर्ण;

/* "reciprocal_value_adv" implements the advanced version of the algorithm
 * described in Figure 4.2 of the paper except when "divisor > (1U << 31)" whose
 * उच्चमान(log2(d)) result will be 32 which then requires u128 भागide on host. The
 * exception हाल could be easily handled beक्रमe calling "reciprocal_value_adv".
 *
 * The advanced version requires more complex calculation to get the reciprocal
 * multiplier and other control variables, but then could reduce the required
 * emulation operations.
 *
 * It makes no sense to use this advanced version क्रम host भागide emulation,
 * those extra complनिकासies क्रम calculating multiplier etc could completely
 * waive our saving on emulation operations.
 *
 * However, it makes sense to use it क्रम JIT भागide code generation क्रम which
 * we are willing to trade perक्रमmance of JITed code with that of host. As shown
 * by the following pseuकरो code, the required emulation operations could go करोwn
 * from 6 (the basic version) to 3 or 4.
 *
 * To use the result of "reciprocal_value_adv", suppose we want to calculate
 * n/d, the pseuकरो C code will be:
 *
 *   काष्ठा reciprocal_value_adv rvalue;
 *   u8 pre_shअगरt, exp;
 *
 *   // handle exception हाल.
 *   अगर (d >= (1U << 31)) अणु
 *     result = n >= d;
 *     वापस;
 *   पूर्ण
 *
 *   rvalue = reciprocal_value_adv(d, 32)
 *   exp = rvalue.exp;
 *   अगर (rvalue.is_wide_m && !(d & 1)) अणु
 *     // न्यूनमान(log2(d & (2^32 -d)))
 *     pre_shअगरt = fls(d & -d) - 1;
 *     rvalue = reciprocal_value_adv(d >> pre_shअगरt, 32 - pre_shअगरt);
 *   पूर्ण अन्यथा अणु
 *     pre_shअगरt = 0;
 *   पूर्ण
 *
 *   // code generation starts.
 *   अगर (imm == 1U << exp) अणु
 *     result = n >> exp;
 *   पूर्ण अन्यथा अगर (rvalue.is_wide_m) अणु
 *     // pre_shअगरt must be zero when reached here.
 *     t = (n * rvalue.m) >> 32;
 *     result = n - t;
 *     result >>= 1;
 *     result += t;
 *     result >>= rvalue.sh - 1;
 *   पूर्ण अन्यथा अणु
 *     अगर (pre_shअगरt)
 *       result = n >> pre_shअगरt;
 *     result = ((u64)result * rvalue.m) >> 32;
 *     result >>= rvalue.sh;
 *   पूर्ण
 */
काष्ठा reciprocal_value_adv reciprocal_value_adv(u32 d, u8 prec);

#पूर्ण_अगर /* _LINUX_RECIPROCAL_DIV_H */
