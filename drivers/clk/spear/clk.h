<शैली गुरु>
/*
 * Clock framework definitions क्रम SPEAr platक्रमm
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __SPEAR_CLK_H
#घोषणा __SPEAR_CLK_H

#समावेश <linux/clk-provider.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/types.h>

/* Auxiliary Synth clk */
/* Default masks */
#घोषणा AUX_EQ_SEL_SHIFT	30
#घोषणा AUX_EQ_SEL_MASK		1
#घोषणा AUX_EQ1_SEL		0
#घोषणा AUX_EQ2_SEL		1
#घोषणा AUX_XSCALE_SHIFT	16
#घोषणा AUX_XSCALE_MASK		0xFFF
#घोषणा AUX_YSCALE_SHIFT	0
#घोषणा AUX_YSCALE_MASK		0xFFF
#घोषणा AUX_SYNT_ENB		31

काष्ठा aux_clk_masks अणु
	u32 eq_sel_mask;
	u32 eq_sel_shअगरt;
	u32 eq1_mask;
	u32 eq2_mask;
	u32 xscale_sel_mask;
	u32 xscale_sel_shअगरt;
	u32 yscale_sel_mask;
	u32 yscale_sel_shअगरt;
	u32 enable_bit;
पूर्ण;

काष्ठा aux_rate_tbl अणु
	u16 xscale;
	u16 yscale;
	u8 eq;
पूर्ण;

काष्ठा clk_aux अणु
	काष्ठा			clk_hw hw;
	व्योम __iomem		*reg;
	स्थिर काष्ठा aux_clk_masks *masks;
	काष्ठा aux_rate_tbl	*rtbl;
	u8			rtbl_cnt;
	spinlock_t		*lock;
पूर्ण;

/* Fractional Synth clk */
काष्ठा frac_rate_tbl अणु
	u32 भाग;
पूर्ण;

काष्ठा clk_frac अणु
	काष्ठा			clk_hw hw;
	व्योम __iomem		*reg;
	काष्ठा frac_rate_tbl	*rtbl;
	u8			rtbl_cnt;
	spinlock_t		*lock;
पूर्ण;

/* GPT clk */
काष्ठा gpt_rate_tbl अणु
	u16 mscale;
	u16 nscale;
पूर्ण;

काष्ठा clk_gpt अणु
	काष्ठा			clk_hw hw;
	व्योम __iomem		*reg;
	काष्ठा gpt_rate_tbl	*rtbl;
	u8			rtbl_cnt;
	spinlock_t		*lock;
पूर्ण;

/* VCO-PLL clk */
काष्ठा pll_rate_tbl अणु
	u8 mode;
	u16 m;
	u8 n;
	u8 p;
पूर्ण;

काष्ठा clk_vco अणु
	काष्ठा			clk_hw hw;
	व्योम __iomem		*mode_reg;
	व्योम __iomem		*cfg_reg;
	काष्ठा pll_rate_tbl	*rtbl;
	u8			rtbl_cnt;
	spinlock_t		*lock;
पूर्ण;

काष्ठा clk_pll अणु
	काष्ठा			clk_hw hw;
	काष्ठा clk_vco		*vco;
	स्थिर अक्षर		*parent[1];
	spinlock_t		*lock;
पूर्ण;

प्रकार अचिन्हित दीर्घ (*clk_calc_rate)(काष्ठा clk_hw *hw, अचिन्हित दीर्घ prate,
		पूर्णांक index);

/* clk रेजिस्टर routines */
काष्ठा clk *clk_रेजिस्टर_aux(स्थिर अक्षर *aux_name, स्थिर अक्षर *gate_name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags, व्योम __iomem *reg,
		स्थिर काष्ठा aux_clk_masks *masks, काष्ठा aux_rate_tbl *rtbl,
		u8 rtbl_cnt, spinlock_t *lock, काष्ठा clk **gate_clk);
काष्ठा clk *clk_रेजिस्टर_frac(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg,
		काष्ठा frac_rate_tbl *rtbl, u8 rtbl_cnt, spinlock_t *lock);
काष्ठा clk *clk_रेजिस्टर_gpt(स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित
		दीर्घ flags, व्योम __iomem *reg, काष्ठा gpt_rate_tbl *rtbl, u8
		rtbl_cnt, spinlock_t *lock);
काष्ठा clk *clk_रेजिस्टर_vco_pll(स्थिर अक्षर *vco_name, स्थिर अक्षर *pll_name,
		स्थिर अक्षर *vco_gate_name, स्थिर अक्षर *parent_name,
		अचिन्हित दीर्घ flags, व्योम __iomem *mode_reg, व्योम __iomem
		*cfg_reg, काष्ठा pll_rate_tbl *rtbl, u8 rtbl_cnt,
		spinlock_t *lock, काष्ठा clk **pll_clk,
		काष्ठा clk **vco_gate_clk);

दीर्घ clk_round_rate_index(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
		अचिन्हित दीर्घ parent_rate, clk_calc_rate calc_rate, u8 rtbl_cnt,
		पूर्णांक *index);

#पूर्ण_अगर /* __SPEAR_CLK_H */
