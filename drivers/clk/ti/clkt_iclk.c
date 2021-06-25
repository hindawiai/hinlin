<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2/3 पूर्णांकerface घड़ी control
 *
 * Copyright (C) 2011 Nokia Corporation
 * Paul Walmsley
 */
#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk/ti.h>

#समावेश "clock.h"

/* Register offsets */
#घोषणा OMAP24XX_CM_FCLKEN2		0x04
#घोषणा CM_AUTOIDLE			0x30
#घोषणा CM_ICLKEN			0x10
#घोषणा CM_IDLEST			0x20

#घोषणा OMAP24XX_CM_IDLEST_VAL		0

/* Private functions */

/* XXX */
व्योम omap2_clkt_iclk_allow_idle(काष्ठा clk_hw_omap *clk)
अणु
	u32 v;
	काष्ठा clk_omap_reg r;

	स_नकल(&r, &clk->enable_reg, माप(r));
	r.offset ^= (CM_AUTOIDLE ^ CM_ICLKEN);

	v = ti_clk_ll_ops->clk_पढ़ोl(&r);
	v |= (1 << clk->enable_bit);
	ti_clk_ll_ops->clk_ग_लिखोl(v, &r);
पूर्ण

/* XXX */
व्योम omap2_clkt_iclk_deny_idle(काष्ठा clk_hw_omap *clk)
अणु
	u32 v;
	काष्ठा clk_omap_reg r;

	स_नकल(&r, &clk->enable_reg, माप(r));

	r.offset ^= (CM_AUTOIDLE ^ CM_ICLKEN);

	v = ti_clk_ll_ops->clk_पढ़ोl(&r);
	v &= ~(1 << clk->enable_bit);
	ti_clk_ll_ops->clk_ग_लिखोl(v, &r);
पूर्ण

/**
 * omap2430_clk_i2chs_find_idlest - वापस CM_IDLEST info क्रम 2430 I2CHS
 * @clk: काष्ठा clk * being enabled
 * @idlest_reg: व्योम __iomem ** to store CM_IDLEST reg address पूर्णांकo
 * @idlest_bit: poपूर्णांकer to a u8 to store the CM_IDLEST bit shअगरt पूर्णांकo
 * @idlest_val: poपूर्णांकer to a u8 to store the CM_IDLEST indicator
 *
 * OMAP2430 I2CHS CM_IDLEST bits are in CM_IDLEST1_CORE, but the
 * CM_*CLKEN bits are in CM_अणुI,Fपूर्णCLKEN2_CORE.  This custom function
 * passes back the correct CM_IDLEST रेजिस्टर address क्रम I2CHS
 * modules.  No वापस value.
 */
अटल व्योम omap2430_clk_i2chs_find_idlest(काष्ठा clk_hw_omap *clk,
					   काष्ठा clk_omap_reg *idlest_reg,
					   u8 *idlest_bit,
					   u8 *idlest_val)
अणु
	स_नकल(idlest_reg, &clk->enable_reg, माप(*idlest_reg));
	idlest_reg->offset ^= (OMAP24XX_CM_FCLKEN2 ^ CM_IDLEST);
	*idlest_bit = clk->enable_bit;
	*idlest_val = OMAP24XX_CM_IDLEST_VAL;
पूर्ण

/* Public data */

स्थिर काष्ठा clk_hw_omap_ops clkhwops_iclk = अणु
	.allow_idle	= omap2_clkt_iclk_allow_idle,
	.deny_idle	= omap2_clkt_iclk_deny_idle,
पूर्ण;

स्थिर काष्ठा clk_hw_omap_ops clkhwops_iclk_रुको = अणु
	.allow_idle	= omap2_clkt_iclk_allow_idle,
	.deny_idle	= omap2_clkt_iclk_deny_idle,
	.find_idlest	= omap2_clk_dflt_find_idlest,
	.find_companion	= omap2_clk_dflt_find_companion,
पूर्ण;

/* 2430 I2CHS has non-standard IDLEST रेजिस्टर */
स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap2430_i2chs_रुको = अणु
	.find_idlest	= omap2430_clk_i2chs_find_idlest,
	.find_companion	= omap2_clk_dflt_find_companion,
पूर्ण;
