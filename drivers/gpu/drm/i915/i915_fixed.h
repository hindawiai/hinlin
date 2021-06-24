<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#अगर_अघोषित _I915_FIXED_H_
#घोषणा _I915_FIXED_H_

#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/types.h>

प्रकार काष्ठा अणु
	u32 val;
पूर्ण uपूर्णांक_fixed_16_16_t;

#घोषणा FP_16_16_MAX ((uपूर्णांक_fixed_16_16_t)अणु .val = अच_पूर्णांक_उच्च पूर्ण)

अटल अंतरभूत bool is_fixed16_zero(uपूर्णांक_fixed_16_16_t val)
अणु
	वापस val.val == 0;
पूर्ण

अटल अंतरभूत uपूर्णांक_fixed_16_16_t u32_to_fixed16(u32 val)
अणु
	uपूर्णांक_fixed_16_16_t fp = अणु .val = val << 16 पूर्ण;

	WARN_ON(val > U16_MAX);

	वापस fp;
पूर्ण

अटल अंतरभूत u32 fixed16_to_u32_round_up(uपूर्णांक_fixed_16_16_t fp)
अणु
	वापस DIV_ROUND_UP(fp.val, 1 << 16);
पूर्ण

अटल अंतरभूत u32 fixed16_to_u32(uपूर्णांक_fixed_16_16_t fp)
अणु
	वापस fp.val >> 16;
पूर्ण

अटल अंतरभूत uपूर्णांक_fixed_16_16_t min_fixed16(uपूर्णांक_fixed_16_16_t min1,
					     uपूर्णांक_fixed_16_16_t min2)
अणु
	uपूर्णांक_fixed_16_16_t min = अणु .val = min(min1.val, min2.val) पूर्ण;

	वापस min;
पूर्ण

अटल अंतरभूत uपूर्णांक_fixed_16_16_t max_fixed16(uपूर्णांक_fixed_16_16_t max1,
					     uपूर्णांक_fixed_16_16_t max2)
अणु
	uपूर्णांक_fixed_16_16_t max = अणु .val = max(max1.val, max2.val) पूर्ण;

	वापस max;
पूर्ण

अटल अंतरभूत uपूर्णांक_fixed_16_16_t clamp_u64_to_fixed16(u64 val)
अणु
	uपूर्णांक_fixed_16_16_t fp = अणु .val = (u32)val पूर्ण;

	WARN_ON(val > U32_MAX);

	वापस fp;
पूर्ण

अटल अंतरभूत u32 भाग_round_up_fixed16(uपूर्णांक_fixed_16_16_t val,
				       uपूर्णांक_fixed_16_16_t d)
अणु
	वापस DIV_ROUND_UP(val.val, d.val);
पूर्ण

अटल अंतरभूत u32 mul_round_up_u32_fixed16(u32 val, uपूर्णांक_fixed_16_16_t mul)
अणु
	u64 पंचांगp;

	पंचांगp = mul_u32_u32(val, mul.val);
	पंचांगp = DIV_ROUND_UP_ULL(पंचांगp, 1 << 16);
	WARN_ON(पंचांगp > U32_MAX);

	वापस (u32)पंचांगp;
पूर्ण

अटल अंतरभूत uपूर्णांक_fixed_16_16_t mul_fixed16(uपूर्णांक_fixed_16_16_t val,
					     uपूर्णांक_fixed_16_16_t mul)
अणु
	u64 पंचांगp;

	पंचांगp = mul_u32_u32(val.val, mul.val);
	पंचांगp = पंचांगp >> 16;

	वापस clamp_u64_to_fixed16(पंचांगp);
पूर्ण

अटल अंतरभूत uपूर्णांक_fixed_16_16_t भाग_fixed16(u32 val, u32 d)
अणु
	u64 पंचांगp;

	पंचांगp = (u64)val << 16;
	पंचांगp = DIV_ROUND_UP_ULL(पंचांगp, d);

	वापस clamp_u64_to_fixed16(पंचांगp);
पूर्ण

अटल अंतरभूत u32 भाग_round_up_u32_fixed16(u32 val, uपूर्णांक_fixed_16_16_t d)
अणु
	u64 पंचांगp;

	पंचांगp = (u64)val << 16;
	पंचांगp = DIV_ROUND_UP_ULL(पंचांगp, d.val);
	WARN_ON(पंचांगp > U32_MAX);

	वापस (u32)पंचांगp;
पूर्ण

अटल अंतरभूत uपूर्णांक_fixed_16_16_t mul_u32_fixed16(u32 val, uपूर्णांक_fixed_16_16_t mul)
अणु
	u64 पंचांगp;

	पंचांगp = mul_u32_u32(val, mul.val);

	वापस clamp_u64_to_fixed16(पंचांगp);
पूर्ण

अटल अंतरभूत uपूर्णांक_fixed_16_16_t add_fixed16(uपूर्णांक_fixed_16_16_t add1,
					     uपूर्णांक_fixed_16_16_t add2)
अणु
	u64 पंचांगp;

	पंचांगp = (u64)add1.val + add2.val;

	वापस clamp_u64_to_fixed16(पंचांगp);
पूर्ण

अटल अंतरभूत uपूर्णांक_fixed_16_16_t add_fixed16_u32(uपूर्णांक_fixed_16_16_t add1,
						 u32 add2)
अणु
	uपूर्णांक_fixed_16_16_t पंचांगp_add2 = u32_to_fixed16(add2);
	u64 पंचांगp;

	पंचांगp = (u64)add1.val + पंचांगp_add2.val;

	वापस clamp_u64_to_fixed16(पंचांगp);
पूर्ण

#पूर्ण_अगर /* _I915_FIXED_H_ */
