<शैली गुरु>
/*
 * Copyright (C) 2014 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _CLK_IPROC_H
#घोषणा _CLK_IPROC_H

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/clk-provider.h>

#घोषणा IPROC_CLK_NAME_LEN 25
#घोषणा IPROC_CLK_INVALID_OFFSET 0xffffffff
#घोषणा bit_mask(width) ((1 << (width)) - 1)

/* घड़ीs that should not be disabled at runसमय */
#घोषणा IPROC_CLK_AON BIT(0)

/* PLL that requires gating through ASIU */
#घोषणा IPROC_CLK_PLL_ASIU BIT(1)

/* PLL that has fractional part of the NDIV */
#घोषणा IPROC_CLK_PLL_HAS_NDIV_FRAC BIT(2)

/*
 * Some of the iProc PLL/घड़ीs may have an ASIC bug that requires पढ़ो back
 * of the same रेजिस्टर following the ग_लिखो to flush the ग_लिखो transaction पूर्णांकo
 * the पूर्णांकended रेजिस्टर
 */
#घोषणा IPROC_CLK_NEEDS_READ_BACK BIT(3)

/*
 * Some PLLs require the PLL SW override bit to be set beक्रमe changes can be
 * applied to the PLL
 */
#घोषणा IPROC_CLK_PLL_NEEDS_SW_CFG BIT(4)

/*
 * Some PLLs use a dअगरferent way to control घड़ी घातer, via the PWRDWN bit in
 * the PLL control रेजिस्टर
 */
#घोषणा IPROC_CLK_EMBED_PWRCTRL BIT(5)

/*
 * Some PLLs have separate रेजिस्टरs क्रम Status and Control.  Identअगरy this to
 * let the driver know अगर additional रेजिस्टरs need to be used
 */
#घोषणा IPROC_CLK_PLL_SPLIT_STAT_CTRL BIT(6)

/*
 * Some PLLs have an additional भागide by 2 in master घड़ी calculation;
 * MCLK = VCO_freq / (Mभाग * 2). Identअगरy this to let the driver know
 * of modअगरied calculations
 */
#घोषणा IPROC_CLK_MCLK_DIV_BY_2 BIT(7)

/*
 * Some PLLs provide a look up table क्रम the leaf घड़ी frequencies and
 * स्वतः calculates VCO frequency parameters based on the provided leaf
 * घड़ी frequencies. They have a user mode that allows the भागider
 * controls to be determined by the user
 */
#घोषणा IPROC_CLK_PLL_USER_MODE_ON BIT(8)

/*
 * Some PLLs have an active low reset
 */
#घोषणा IPROC_CLK_PLL_RESET_ACTIVE_LOW BIT(9)

/*
 * Calculate the PLL parameters are runसमय, instead of using table
 */
#घोषणा IPROC_CLK_PLL_CALC_PARAM BIT(10)

/*
 * Parameters क्रम VCO frequency configuration
 *
 * VCO frequency =
 * ((nभाग_पूर्णांक + nभाग_frac / 2^20) * (ref freqeuncy  / pभाग)
 */
काष्ठा iproc_pll_vco_param अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक nभाग_पूर्णांक;
	अचिन्हित पूर्णांक nभाग_frac;
	अचिन्हित पूर्णांक pभाग;
पूर्ण;

काष्ठा iproc_clk_reg_op अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक width;
पूर्ण;

/*
 * Clock gating control at the top ASIU level
 */
काष्ठा iproc_asiu_gate अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक en_shअगरt;
पूर्ण;

/*
 * Control of घातering on/off of a PLL
 *
 * Beक्रमe घातering off a PLL, input isolation (ISO) needs to be enabled
 */
काष्ठा iproc_pll_aon_pwr_ctrl अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक pwr_width;
	अचिन्हित पूर्णांक pwr_shअगरt;
	अचिन्हित पूर्णांक iso_shअगरt;
पूर्ण;

/*
 * Control of the PLL reset
 */
काष्ठा iproc_pll_reset_ctrl अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक reset_shअगरt;
	अचिन्हित पूर्णांक p_reset_shअगरt;
पूर्ण;

/*
 * Control of the Ki, Kp, and Ka parameters
 */
काष्ठा iproc_pll_dig_filter_ctrl अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक ki_shअगरt;
	अचिन्हित पूर्णांक ki_width;
	अचिन्हित पूर्णांक kp_shअगरt;
	अचिन्हित पूर्णांक kp_width;
	अचिन्हित पूर्णांक ka_shअगरt;
	अचिन्हित पूर्णांक ka_width;
पूर्ण;

/*
 * To enable SW control of the PLL
 */
काष्ठा iproc_pll_sw_ctrl अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक shअगरt;
पूर्ण;

काष्ठा iproc_pll_vco_ctrl अणु
	अचिन्हित पूर्णांक u_offset;
	अचिन्हित पूर्णांक l_offset;
पूर्ण;

/*
 * Main PLL control parameters
 */
काष्ठा iproc_pll_ctrl अणु
	अचिन्हित दीर्घ flags;
	काष्ठा iproc_pll_aon_pwr_ctrl aon;
	काष्ठा iproc_asiu_gate asiu;
	काष्ठा iproc_pll_reset_ctrl reset;
	काष्ठा iproc_pll_dig_filter_ctrl dig_filter;
	काष्ठा iproc_pll_sw_ctrl sw_ctrl;
	काष्ठा iproc_clk_reg_op nभाग_पूर्णांक;
	काष्ठा iproc_clk_reg_op nभाग_frac;
	काष्ठा iproc_clk_reg_op pभाग;
	काष्ठा iproc_pll_vco_ctrl vco_ctrl;
	काष्ठा iproc_clk_reg_op status;
	काष्ठा iproc_clk_reg_op macro_mode;
पूर्ण;

/*
 * Controls enabling/disabling a PLL derived घड़ी
 */
काष्ठा iproc_clk_enable_ctrl अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक enable_shअगरt;
	अचिन्हित पूर्णांक hold_shअगरt;
	अचिन्हित पूर्णांक bypass_shअगरt;
पूर्ण;

/*
 * Main घड़ी control parameters क्रम घड़ीs derived from the PLLs
 */
काष्ठा iproc_clk_ctrl अणु
	अचिन्हित पूर्णांक channel;
	अचिन्हित दीर्घ flags;
	काष्ठा iproc_clk_enable_ctrl enable;
	काष्ठा iproc_clk_reg_op mभाग;
पूर्ण;

/*
 * Divisor of the ASIU घड़ीs
 */
काष्ठा iproc_asiu_भाग अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक en_shअगरt;
	अचिन्हित पूर्णांक high_shअगरt;
	अचिन्हित पूर्णांक high_width;
	अचिन्हित पूर्णांक low_shअगरt;
	अचिन्हित पूर्णांक low_width;
पूर्ण;

व्योम iproc_armpll_setup(काष्ठा device_node *node);
व्योम iproc_pll_clk_setup(काष्ठा device_node *node,
			 स्थिर काष्ठा iproc_pll_ctrl *pll_ctrl,
			 स्थिर काष्ठा iproc_pll_vco_param *vco,
			 अचिन्हित पूर्णांक num_vco_entries,
			 स्थिर काष्ठा iproc_clk_ctrl *clk_ctrl,
			 अचिन्हित पूर्णांक num_clks);
व्योम iproc_asiu_setup(काष्ठा device_node *node,
		      स्थिर काष्ठा iproc_asiu_भाग *भाग,
		      स्थिर काष्ठा iproc_asiu_gate *gate,
		      अचिन्हित पूर्णांक num_clks);

#पूर्ण_अगर /* _CLK_IPROC_H */
