<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#अगर_अघोषित _MALIDP_UTILS_
#घोषणा _MALIDP_UTILS_

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>

#घोषणा has_bit(nr, mask)	(BIT(nr) & (mask))
#घोषणा has_bits(bits, mask)	(((bits) & (mask)) == (bits))

#घोषणा dp_रुको_cond(__cond, __tries, __min_range, __max_range)	\
(अणु							\
	पूर्णांक num_tries = __tries;			\
	जबतक (!__cond && (num_tries > 0)) अणु		\
		usleep_range(__min_range, __max_range);	\
		num_tries--;				\
	पूर्ण						\
	(__cond) ? 0 : -ETIMEDOUT;			\
पूर्ण)

/* the restriction of range is [start, end] */
काष्ठा malidp_range अणु
	u32 start;
	u32 end;
पूर्ण;

अटल अंतरभूत व्योम set_range(काष्ठा malidp_range *rg, u32 start, u32 end)
अणु
	rg->start = start;
	rg->end   = end;
पूर्ण

अटल अंतरभूत bool in_range(काष्ठा malidp_range *rg, u32 v)
अणु
	वापस (v >= rg->start) && (v <= rg->end);
पूर्ण

#पूर्ण_अगर /* _MALIDP_UTILS_ */
