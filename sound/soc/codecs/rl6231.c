<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rl6231.c - RL6231 class device shared support
 *
 * Copyright 2014 Realtek Semiconductor Corp.
 *
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश <linux/gcd.h>
#समावेश "rl6231.h"

/**
 * rl6231_get_pre_भाग - Return the value of pre भागider.
 *
 * @map: map क्रम setting.
 * @reg: रेजिस्टर.
 * @sft: shअगरt.
 *
 * Return the value of pre भागider from given रेजिस्टर value.
 * Return negative error code क्रम unexpected रेजिस्टर value.
 */
पूर्णांक rl6231_get_pre_भाग(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, पूर्णांक sft)
अणु
	पूर्णांक pd, val;

	regmap_पढ़ो(map, reg, &val);

	val = (val >> sft) & 0x7;

	चयन (val) अणु
	हाल 0:
	हाल 1:
	हाल 2:
	हाल 3:
		pd = val + 1;
		अवरोध;
	हाल 4:
		pd = 6;
		अवरोध;
	हाल 5:
		pd = 8;
		अवरोध;
	हाल 6:
		pd = 12;
		अवरोध;
	हाल 7:
		pd = 16;
		अवरोध;
	शेष:
		pd = -EINVAL;
		अवरोध;
	पूर्ण

	वापस pd;
पूर्ण
EXPORT_SYMBOL_GPL(rl6231_get_pre_भाग);

/**
 * rl6231_calc_dmic_clk - Calculate the frequency भागider parameter of dmic.
 *
 * @rate: base घड़ी rate.
 *
 * Choose भागider parameter that gives the highest possible DMIC frequency in
 * 1MHz - 3MHz range.
 */
पूर्णांक rl6231_calc_dmic_clk(पूर्णांक rate)
अणु
	अटल स्थिर पूर्णांक भाग[] = अणु2, 3, 4, 6, 8, 12पूर्ण;
	पूर्णांक i;

	अगर (rate < 1000000 * भाग[0]) अणु
		pr_warn("Base clock rate %d is too low\n", rate);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(भाग); i++) अणु
		अगर ((भाग[i] % 3) == 0)
			जारी;
		/* find भागider that gives DMIC frequency below 1.536MHz */
		अगर (1536000 * भाग[i] >= rate)
			वापस i;
	पूर्ण

	pr_warn("Base clock rate %d is too high\n", rate);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(rl6231_calc_dmic_clk);

काष्ठा pll_calc_map अणु
	अचिन्हित पूर्णांक pll_in;
	अचिन्हित पूर्णांक pll_out;
	पूर्णांक k;
	पूर्णांक n;
	पूर्णांक m;
	bool m_bp;
	bool k_bp;
पूर्ण;

अटल स्थिर काष्ठा pll_calc_map pll_preset_table[] = अणु
	अणु19200000,  4096000,  23, 14, 1, false, falseपूर्ण,
	अणु19200000,  24576000,  3, 30, 3, false, falseपूर्ण,
	अणु48000000,  3840000,  23,  2, 0, false, falseपूर्ण,
	अणु3840000,   24576000,  3, 30, 0, true, falseपूर्ण,
	अणु3840000,   22579200,  3,  5, 0, true, falseपूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक find_best_भाग(अचिन्हित पूर्णांक in,
	अचिन्हित पूर्णांक max, अचिन्हित पूर्णांक भाग)
अणु
	अचिन्हित पूर्णांक d;

	अगर (in <= max)
		वापस 1;

	d = in / max;
	अगर (in % max)
		d++;

	जबतक (भाग % d != 0)
		d++;


	वापस d;
पूर्ण

/**
 * rl6231_pll_calc - Calcualte PLL M/N/K code.
 * @freq_in: बाह्यal घड़ी provided to codec.
 * @freq_out: target घड़ी which codec works on.
 * @pll_code: Poपूर्णांकer to काष्ठाure with M, N, K, m_bypass and k_bypass flag.
 *
 * Calcualte M/N/K code to configure PLL क्रम codec.
 *
 * Returns 0 क्रम success or negative error code.
 */
पूर्णांक rl6231_pll_calc(स्थिर अचिन्हित पूर्णांक freq_in,
	स्थिर अचिन्हित पूर्णांक freq_out, काष्ठा rl6231_pll_code *pll_code)
अणु
	पूर्णांक max_n = RL6231_PLL_N_MAX, max_m = RL6231_PLL_M_MAX;
	पूर्णांक i, k, n_t;
	पूर्णांक k_t, min_k, max_k, n = 0, m = 0, m_t = 0;
	अचिन्हित पूर्णांक red, pll_out, in_t, out_t, भाग, भाग_प्रकार;
	अचिन्हित पूर्णांक red_t = असल(freq_out - freq_in);
	अचिन्हित पूर्णांक f_in, f_out, f_max;
	bool m_bypass = false, k_bypass = false;

	अगर (RL6231_PLL_INP_MAX < freq_in || RL6231_PLL_INP_MIN > freq_in)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(pll_preset_table); i++) अणु
		अगर (freq_in == pll_preset_table[i].pll_in &&
			freq_out == pll_preset_table[i].pll_out) अणु
			k = pll_preset_table[i].k;
			m = pll_preset_table[i].m;
			n = pll_preset_table[i].n;
			m_bypass = pll_preset_table[i].m_bp;
			k_bypass = pll_preset_table[i].k_bp;
			pr_debug("Use preset PLL parameter table\n");
			जाओ code_find;
		पूर्ण
	पूर्ण

	min_k = 80000000 / freq_out - 2;
	max_k = 150000000 / freq_out - 2;
	अगर (max_k > RL6231_PLL_K_MAX)
		max_k = RL6231_PLL_K_MAX;
	अगर (min_k > RL6231_PLL_K_MAX)
		min_k = max_k = RL6231_PLL_K_MAX;
	भाग_प्रकार = gcd(freq_in, freq_out);
	f_max = 0xffffffff / RL6231_PLL_N_MAX;
	भाग = find_best_भाग(freq_in, f_max, भाग_प्रकार);
	f_in = freq_in / भाग;
	f_out = freq_out / भाग;
	k = min_k;
	अगर (min_k < -1)
		min_k = -1;
	क्रम (k_t = min_k; k_t <= max_k; k_t++) अणु
		क्रम (n_t = 0; n_t <= max_n; n_t++) अणु
			in_t = f_in * (n_t + 2);
			pll_out = f_out * (k_t + 2);
			अगर (in_t == pll_out) अणु
				m_bypass = true;
				n = n_t;
				k = k_t;
				जाओ code_find;
			पूर्ण
			out_t = in_t / (k_t + 2);
			red = असल(f_out - out_t);
			अगर (red < red_t) अणु
				m_bypass = true;
				n = n_t;
				m = 0;
				k = k_t;
				अगर (red == 0)
					जाओ code_find;
				red_t = red;
			पूर्ण
			क्रम (m_t = 0; m_t <= max_m; m_t++) अणु
				out_t = in_t / ((m_t + 2) * (k_t + 2));
				red = असल(f_out - out_t);
				अगर (red < red_t) अणु
					m_bypass = false;
					n = n_t;
					m = m_t;
					k = k_t;
					अगर (red == 0)
						जाओ code_find;
					red_t = red;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	pr_debug("Only get approximation about PLL\n");

code_find:
	अगर (k == -1) अणु
		k_bypass = true;
		k = 0;
	पूर्ण

	pll_code->m_bp = m_bypass;
	pll_code->k_bp = k_bypass;
	pll_code->m_code = m;
	pll_code->n_code = n;
	pll_code->k_code = k;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rl6231_pll_calc);

पूर्णांक rl6231_get_clk_info(पूर्णांक sclk, पूर्णांक rate)
अणु
	पूर्णांक i;
	अटल स्थिर पूर्णांक pd[] = अणु1, 2, 3, 4, 6, 8, 12, 16पूर्ण;

	अगर (sclk <= 0 || rate <= 0)
		वापस -EINVAL;

	rate = rate << 8;
	क्रम (i = 0; i < ARRAY_SIZE(pd); i++)
		अगर (sclk == rate * pd[i])
			वापस i;

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(rl6231_get_clk_info);

MODULE_DESCRIPTION("RL6231 class device shared support");
MODULE_AUTHOR("Oder Chiou <oder_chiou@realtek.com>");
MODULE_LICENSE("GPL v2");
