<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/export.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/गणित.स>
#समावेश <linux/minmax.h>
#समावेश <linux/types.h>

#समावेश <linux/reciprocal_भाग.h>

/*
 * For a description of the algorithm please have a look at
 * include/linux/reciprocal_भाग.h
 */

काष्ठा reciprocal_value reciprocal_value(u32 d)
अणु
	काष्ठा reciprocal_value R;
	u64 m;
	पूर्णांक l;

	l = fls(d - 1);
	m = ((1ULL << 32) * ((1ULL << l) - d));
	करो_भाग(m, d);
	++m;
	R.m = (u32)m;
	R.sh1 = min(l, 1);
	R.sh2 = max(l - 1, 0);

	वापस R;
पूर्ण
EXPORT_SYMBOL(reciprocal_value);

काष्ठा reciprocal_value_adv reciprocal_value_adv(u32 d, u8 prec)
अणु
	काष्ठा reciprocal_value_adv R;
	u32 l, post_shअगरt;
	u64 mhigh, mlow;

	/* उच्चमान(log2(d)) */
	l = fls(d - 1);
	/* NOTE: mlow/mhigh could overflow u64 when l == 32. This हाल needs to
	 * be handled beक्रमe calling "reciprocal_value_adv", please see the
	 * comment at include/linux/reciprocal_भाग.h.
	 */
	WARN(l == 32,
	     "ceil(log2(0x%08x)) == 32, %s doesn't support such divisor",
	     d, __func__);
	post_shअगरt = l;
	mlow = 1ULL << (32 + l);
	करो_भाग(mlow, d);
	mhigh = (1ULL << (32 + l)) + (1ULL << (32 + l - prec));
	करो_भाग(mhigh, d);

	क्रम (; post_shअगरt > 0; post_shअगरt--) अणु
		u64 lo = mlow >> 1, hi = mhigh >> 1;

		अगर (lo >= hi)
			अवरोध;

		mlow = lo;
		mhigh = hi;
	पूर्ण

	R.m = (u32)mhigh;
	R.sh = post_shअगरt;
	R.exp = l;
	R.is_wide_m = mhigh > U32_MAX;

	वापस R;
पूर्ण
EXPORT_SYMBOL(reciprocal_value_adv);
