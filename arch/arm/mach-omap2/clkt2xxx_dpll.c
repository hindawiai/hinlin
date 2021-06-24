<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2-specअगरic DPLL control functions
 *
 * Copyright (C) 2011 Nokia Corporation
 * Paul Walmsley
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश "clock.h"
#समावेश "cm2xxx.h"
#समावेश "cm-regbits-24xx.h"

/* Private functions */

/**
 * _allow_idle - enable DPLL स्वतःidle bits
 * @clk: काष्ठा clk * of the DPLL to operate on
 *
 * Enable DPLL स्वतःmatic idle control.  The DPLL will enter low-घातer
 * stop when its करोwnstream घड़ीs are gated.  No वापस value.
 * REVISIT: DPLL can optionally enter low-घातer bypass by writing 0x1
 * instead.  Add some mechanism to optionally enter this mode.
 */
अटल व्योम _allow_idle(काष्ठा clk_hw_omap *clk)
अणु
	अगर (!clk || !clk->dpll_data)
		वापस;

	omap2xxx_cm_set_dpll_स्वतः_low_घातer_stop();
पूर्ण

/**
 * _deny_idle - prevent DPLL from स्वतःmatically idling
 * @clk: काष्ठा clk * of the DPLL to operate on
 *
 * Disable DPLL स्वतःmatic idle control.  No वापस value.
 */
अटल व्योम _deny_idle(काष्ठा clk_hw_omap *clk)
अणु
	अगर (!clk || !clk->dpll_data)
		वापस;

	omap2xxx_cm_set_dpll_disable_स्वतःidle();
पूर्ण


/* Public data */
स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap2xxx_dpll = अणु
	.allow_idle	= _allow_idle,
	.deny_idle	= _deny_idle,
पूर्ण;
