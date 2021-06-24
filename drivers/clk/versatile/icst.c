<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/common/icst307.c
 *
 *  Copyright (C) 2003 Deep Blue Solutions, Ltd, All Rights Reserved.
 *
 *  Support functions क्रम calculating घड़ीs/भागisors क्रम the ICST307
 *  घड़ी generators.  See https://www.idt.com/ क्रम more inक्रमmation
 *  on these devices.
 *
 *  This is an almost identical implementation to the ICST525 घड़ी generator.
 *  The s2भाग and idx2s files are dअगरferent
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/भाग64.h>
#समावेश "icst.h"

/*
 * Divisors क्रम each OD setting.
 */
स्थिर अचिन्हित अक्षर icst307_s2भाग[8] = अणु 10, 2, 8, 4, 5, 7, 3, 6 पूर्ण;
स्थिर अचिन्हित अक्षर icst525_s2भाग[8] = अणु 10, 2, 8, 4, 5, 7, 9, 6 पूर्ण;
EXPORT_SYMBOL(icst307_s2भाग);
EXPORT_SYMBOL(icst525_s2भाग);

अचिन्हित दीर्घ icst_hz(स्थिर काष्ठा icst_params *p, काष्ठा icst_vco vco)
अणु
	u64 भागidend = p->ref * 2 * (u64)(vco.v + 8);
	u32 भागisor = (vco.r + 2) * p->s2भाग[vco.s];

	करो_भाग(भागidend, भागisor);
	वापस (अचिन्हित दीर्घ)भागidend;
पूर्ण

EXPORT_SYMBOL(icst_hz);

/*
 * Ascending भागisor S values.
 */
स्थिर अचिन्हित अक्षर icst307_idx2s[8] = अणु 1, 6, 3, 4, 7, 5, 2, 0 पूर्ण;
स्थिर अचिन्हित अक्षर icst525_idx2s[8] = अणु 1, 3, 4, 7, 5, 2, 6, 0 पूर्ण;
EXPORT_SYMBOL(icst307_idx2s);
EXPORT_SYMBOL(icst525_idx2s);

काष्ठा icst_vco
icst_hz_to_vco(स्थिर काष्ठा icst_params *p, अचिन्हित दीर्घ freq)
अणु
	काष्ठा icst_vco vco = अणु .s = 1, .v = p->vd_max, .r = p->rd_max पूर्ण;
	अचिन्हित दीर्घ f;
	अचिन्हित पूर्णांक i = 0, rd, best = (अचिन्हित पूर्णांक)-1;

	/*
	 * First, find the PLL output भागisor such
	 * that the PLL output is within spec.
	 */
	करो अणु
		f = freq * p->s2भाग[p->idx2s[i]];

		अगर (f > p->vco_min && f <= p->vco_max)
			अवरोध;
		i++;
	पूर्ण जबतक (i < 8);

	अगर (i >= 8)
		वापस vco;

	vco.s = p->idx2s[i];

	/*
	 * Now find the बंदst भागisor combination
	 * which gives a PLL output of 'f'.
	 */
	क्रम (rd = p->rd_min; rd <= p->rd_max; rd++) अणु
		अचिन्हित दीर्घ fref_भाग, f_pll;
		अचिन्हित पूर्णांक vd;
		पूर्णांक f_dअगरf;

		fref_भाग = (2 * p->ref) / rd;

		vd = (f + fref_भाग / 2) / fref_भाग;
		अगर (vd < p->vd_min || vd > p->vd_max)
			जारी;

		f_pll = fref_भाग * vd;
		f_dअगरf = f_pll - f;
		अगर (f_dअगरf < 0)
			f_dअगरf = -f_dअगरf;

		अगर ((अचिन्हित)f_dअगरf < best) अणु
			vco.v = vd - 8;
			vco.r = rd - 2;
			अगर (f_dअगरf == 0)
				अवरोध;
			best = f_dअगरf;
		पूर्ण
	पूर्ण

	वापस vco;
पूर्ण

EXPORT_SYMBOL(icst_hz_to_vco);
