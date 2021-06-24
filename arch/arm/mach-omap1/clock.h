<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/arch/arm/mach-omap1/घड़ी.h
 *
 *  Copyright (C) 2004 - 2005, 2009 Nokia corporation
 *  Written by Tuukka Tikkanen <tuukka.tikkanen@elektrobit.com>
 *  Based on घड़ीs.h by Tony Lindgren, Gorकरोn McNutt and RidgeRun, Inc
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP1_CLOCK_H
#घोषणा __ARCH_ARM_MACH_OMAP1_CLOCK_H

#समावेश <linux/clk.h>
#समावेश <linux/list.h>

#समावेश <linux/clkdev.h>

काष्ठा module;
काष्ठा clk;

काष्ठा omap_clk अणु
	u16				cpu;
	काष्ठा clk_lookup		lk;
पूर्ण;

#घोषणा CLK(dev, con, ck, cp)		\
	अणु				\
		 .cpu = cp,		\
		.lk = अणु			\
			.dev_id = dev,	\
			.con_id = con,	\
			.clk = ck,	\
		पूर्ण,			\
	पूर्ण

/* Platक्रमm flags क्रम the clkdev-OMAP पूर्णांकegration code */
#घोषणा CK_310		(1 << 0)
#घोषणा CK_7XX		(1 << 1)	/* 7xx, 850 */
#घोषणा CK_1510		(1 << 2)
#घोषणा CK_16XX		(1 << 3)	/* 16xx, 17xx, 5912 */
#घोषणा CK_1710		(1 << 4)	/* 1710 extra क्रम rate selection */


/* Temporary, needed during the common घड़ी framework conversion */
#घोषणा __clk_get_name(clk)	(clk->name)
#घोषणा __clk_get_parent(clk)	(clk->parent)
#घोषणा __clk_get_rate(clk)	(clk->rate)

/**
 * काष्ठा clkops - some घड़ी function poपूर्णांकers
 * @enable: fn ptr that enables the current घड़ी in hardware
 * @disable: fn ptr that enables the current घड़ी in hardware
 * @find_idlest: function वापसing the IDLEST रेजिस्टर क्रम the घड़ी's IP blk
 * @find_companion: function वापसing the "companion" clk reg क्रम the घड़ी
 * @allow_idle: fn ptr that enables स्वतःidle क्रम the current घड़ी in hardware
 * @deny_idle: fn ptr that disables स्वतःidle क्रम the current घड़ी in hardware
 *
 * A "companion" clk is an accompanying घड़ी to the one being queried
 * that must be enabled क्रम the IP module connected to the घड़ी to
 * become accessible by the hardware.  Neither @find_idlest nor
 * @find_companion should be needed; that inक्रमmation is IP
 * block-specअगरic; the hwmod code has been created to handle this, but
 * until hwmod data is पढ़ोy and drivers have been converted to use PM
 * runसमय calls in place of clk_enable()/clk_disable(), @find_idlest and
 * @find_companion must, unक्रमtunately, reमुख्य.
 */
काष्ठा clkops अणु
	पूर्णांक			(*enable)(काष्ठा clk *);
	व्योम			(*disable)(काष्ठा clk *);
	व्योम			(*find_idlest)(काष्ठा clk *, व्योम __iomem **,
					       u8 *, u8 *);
	व्योम			(*find_companion)(काष्ठा clk *, व्योम __iomem **,
						  u8 *);
	व्योम			(*allow_idle)(काष्ठा clk *);
	व्योम			(*deny_idle)(काष्ठा clk *);
पूर्ण;

/*
 * काष्ठा clk.flags possibilities
 *
 * XXX करोcument the rest of the घड़ी flags here
 *
 * CLOCK_CLKOUTX2: (OMAP4 only) DPLL CLKOUT and CLKOUTX2 GATE_CTRL
 *     bits share the same रेजिस्टर.  This flag allows the
 *     omap4_dpllmx*() code to determine which GATE_CTRL bit field
 *     should be used.  This is a temporary solution - a better approach
 *     would be to associate घड़ी type-specअगरic data with the घड़ी,
 *     similar to the काष्ठा dpll_data approach.
 */
#घोषणा ENABLE_REG_32BIT	(1 << 0)	/* Use 32-bit access */
#घोषणा CLOCK_IDLE_CONTROL	(1 << 1)
#घोषणा CLOCK_NO_IDLE_PARENT	(1 << 2)
#घोषणा ENABLE_ON_INIT		(1 << 3)	/* Enable upon framework init */
#घोषणा INVERT_ENABLE		(1 << 4)	/* 0 enables, 1 disables */
#घोषणा CLOCK_CLKOUTX2		(1 << 5)

/**
 * काष्ठा clk - OMAP काष्ठा clk
 * @node: list_head connecting this घड़ी पूर्णांकo the full घड़ी list
 * @ops: काष्ठा clkops * क्रम this घड़ी
 * @name: the name of the घड़ी in the hardware (used in hwmod data and debug)
 * @parent: poपूर्णांकer to this घड़ी's parent काष्ठा clk
 * @children: list_head connecting to the child clks' @sibling list_heads
 * @sibling: list_head connecting this clk to its parent clk's @children
 * @rate: current घड़ी rate
 * @enable_reg: रेजिस्टर to ग_लिखो to enable the घड़ी (see @enable_bit)
 * @recalc: fn ptr that वापसs the घड़ी's current rate
 * @set_rate: fn ptr that can change the घड़ी's current rate
 * @round_rate: fn ptr that can round the घड़ी's current rate
 * @init: fn ptr to करो घड़ी-specअगरic initialization
 * @enable_bit: bitshअगरt to ग_लिखो to enable/disable the घड़ी (see @enable_reg)
 * @usecount: number of users that have requested this घड़ी to be enabled
 * @fixed_भाग: when > 0, this घड़ी's rate is its parent's rate / @fixed_भाग
 * @flags: see "struct clk.flags possibilities" above
 * @rate_offset: bitshअगरt क्रम rate selection bitfield (OMAP1 only)
 * @src_offset: bitshअगरt क्रम source selection bitfield (OMAP1 only)
 *
 * XXX @rate_offset, @src_offset should probably be हटाओd and OMAP1
 * घड़ी code converted to use clksel.
 *
 * XXX @usecount is poorly named.  It should be "enable_count" or
 * something similar.  "users" in the description refers to kernel
 * code (core code or drivers) that have called clk_enable() and not
 * yet called clk_disable(); the usecount of parent घड़ीs is also
 * incremented by the घड़ी code when clk_enable() is called on child
 * घड़ीs and decremented by the घड़ी code when clk_disable() is
 * called on child घड़ीs.
 *
 * XXX @clkdm, @usecount, @children, @sibling should be marked क्रम
 * पूर्णांकernal use only.
 *
 * @children and @sibling are used to optimize parent-to-child घड़ी
 * tree traversals.  (child-to-parent traversals use @parent.)
 *
 * XXX The notion of the घड़ी's current rate probably needs to be
 * separated from the घड़ी's target rate.
 */
काष्ठा clk अणु
	काष्ठा list_head	node;
	स्थिर काष्ठा clkops	*ops;
	स्थिर अक्षर		*name;
	काष्ठा clk		*parent;
	काष्ठा list_head	children;
	काष्ठा list_head	sibling;	/* node क्रम children */
	अचिन्हित दीर्घ		rate;
	व्योम __iomem		*enable_reg;
	अचिन्हित दीर्घ		(*recalc)(काष्ठा clk *);
	पूर्णांक			(*set_rate)(काष्ठा clk *, अचिन्हित दीर्घ);
	दीर्घ			(*round_rate)(काष्ठा clk *, अचिन्हित दीर्घ);
	व्योम			(*init)(काष्ठा clk *);
	u8			enable_bit;
	s8			usecount;
	u8			fixed_भाग;
	u8			flags;
	u8			rate_offset;
	u8			src_offset;
#अगर defined(CONFIG_PM_DEBUG) && defined(CONFIG_DEBUG_FS)
	काष्ठा dentry		*dent;	/* For visible tree hierarchy */
#पूर्ण_अगर
पूर्ण;

काष्ठा clk_functions अणु
	पूर्णांक		(*clk_enable)(काष्ठा clk *clk);
	व्योम		(*clk_disable)(काष्ठा clk *clk);
	दीर्घ		(*clk_round_rate)(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
	पूर्णांक		(*clk_set_rate)(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
	पूर्णांक		(*clk_set_parent)(काष्ठा clk *clk, काष्ठा clk *parent);
	व्योम		(*clk_allow_idle)(काष्ठा clk *clk);
	व्योम		(*clk_deny_idle)(काष्ठा clk *clk);
	व्योम		(*clk_disable_unused)(काष्ठा clk *clk);
पूर्ण;

बाह्य पूर्णांक clk_init(काष्ठा clk_functions *custom_घड़ीs);
बाह्य व्योम clk_preinit(काष्ठा clk *clk);
बाह्य पूर्णांक clk_रेजिस्टर(काष्ठा clk *clk);
बाह्य व्योम clk_reparent(काष्ठा clk *child, काष्ठा clk *parent);
बाह्य व्योम clk_unरेजिस्टर(काष्ठा clk *clk);
बाह्य व्योम propagate_rate(काष्ठा clk *clk);
बाह्य व्योम recalculate_root_घड़ीs(व्योम);
बाह्य अचिन्हित दीर्घ followparent_recalc(काष्ठा clk *clk);
बाह्य व्योम clk_enable_init_घड़ीs(व्योम);
अचिन्हित दीर्घ omap_fixed_भागisor_recalc(काष्ठा clk *clk);
बाह्य काष्ठा clk *omap_clk_get_by_name(स्थिर अक्षर *name);
बाह्य पूर्णांक omap_clk_enable_स्वतःidle_all(व्योम);
बाह्य पूर्णांक omap_clk_disable_स्वतःidle_all(व्योम);

बाह्य स्थिर काष्ठा clkops clkops_null;

बाह्य काष्ठा clk dummy_ck;

पूर्णांक omap1_clk_init(व्योम);
व्योम omap1_clk_late_init(व्योम);
बाह्य पूर्णांक omap1_clk_enable(काष्ठा clk *clk);
बाह्य व्योम omap1_clk_disable(काष्ठा clk *clk);
बाह्य दीर्घ omap1_clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
बाह्य पूर्णांक omap1_clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
बाह्य अचिन्हित दीर्घ omap1_ckctl_recalc(काष्ठा clk *clk);
बाह्य पूर्णांक omap1_set_sossi_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
बाह्य अचिन्हित दीर्घ omap1_sossi_recalc(काष्ठा clk *clk);
बाह्य अचिन्हित दीर्घ omap1_ckctl_recalc_dsp_करोमुख्य(काष्ठा clk *clk);
बाह्य पूर्णांक omap1_clk_set_rate_dsp_करोमुख्य(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
बाह्य पूर्णांक omap1_set_uart_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
बाह्य अचिन्हित दीर्घ omap1_uart_recalc(काष्ठा clk *clk);
बाह्य पूर्णांक omap1_set_ext_clk_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
बाह्य दीर्घ omap1_round_ext_clk_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
बाह्य व्योम omap1_init_ext_clk(काष्ठा clk *clk);
बाह्य पूर्णांक omap1_select_table_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
बाह्य दीर्घ omap1_round_to_table_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
बाह्य पूर्णांक omap1_clk_set_rate_ckctl_arm(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
बाह्य दीर्घ omap1_clk_round_rate_ckctl_arm(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
बाह्य अचिन्हित दीर्घ omap1_watchकरोg_recalc(काष्ठा clk *clk);

#अगर_घोषित CONFIG_OMAP_RESET_CLOCKS
बाह्य व्योम omap1_clk_disable_unused(काष्ठा clk *clk);
#अन्यथा
#घोषणा omap1_clk_disable_unused	शून्य
#पूर्ण_अगर

काष्ठा uart_clk अणु
	काष्ठा clk	clk;
	अचिन्हित दीर्घ	sysc_addr;
पूर्ण;

/* Provide a method क्रम preventing idling some ARM IDLECT घड़ीs */
काष्ठा arm_idlect1_clk अणु
	काष्ठा clk	clk;
	अचिन्हित दीर्घ	no_idle_count;
	__u8		idlect_shअगरt;
पूर्ण;

/* ARM_CKCTL bit shअगरts */
#घोषणा CKCTL_PERDIV_OFFSET	0
#घोषणा CKCTL_LCDDIV_OFFSET	2
#घोषणा CKCTL_ARMDIV_OFFSET	4
#घोषणा CKCTL_DSPDIV_OFFSET	6
#घोषणा CKCTL_TCDIV_OFFSET	8
#घोषणा CKCTL_DSPMMUDIV_OFFSET	10
/*#घोषणा ARM_TIMXO		12*/
#घोषणा EN_DSPCK		13
/*#घोषणा ARM_INTHCK_SEL	14*/ /* Divide-by-2 क्रम mpu पूर्णांकh_ck */
/* DSP_CKCTL bit shअगरts */
#घोषणा CKCTL_DSPPERDIV_OFFSET	0

/* ARM_IDLECT2 bit shअगरts */
#घोषणा EN_WDTCK	0
#घोषणा EN_XORPCK	1
#घोषणा EN_PERCK	2
#घोषणा EN_LCDCK	3
#घोषणा EN_LBCK		4 /* Not on 1610/1710 */
/*#घोषणा EN_HSABCK	5*/
#घोषणा EN_APICK	6
#घोषणा EN_TIMCK	7
#घोषणा DMACK_REQ	8
#घोषणा EN_GPIOCK	9 /* Not on 1610/1710 */
/*#घोषणा EN_LBFREECK	10*/
#घोषणा EN_CKOUT_ARM	11

/* ARM_IDLECT3 bit shअगरts */
#घोषणा EN_OCPI_CK	0
#घोषणा EN_TC1_CK	2
#घोषणा EN_TC2_CK	4

/* DSP_IDLECT2 bit shअगरts (0,1,2 are same as क्रम ARM_IDLECT2) */
#घोषणा EN_DSPTIMCK	5

/* Various रेजिस्टर defines क्रम घड़ी controls scattered around OMAP chip */
#घोषणा SDW_MCLK_INV_BIT	2	/* In ULPD_CLKC_CTRL */
#घोषणा USB_MCLK_EN_BIT		4	/* In ULPD_CLKC_CTRL */
#घोषणा USB_HOST_HHC_UHOST_EN	9	/* In MOD_CONF_CTRL_0 */
#घोषणा SWD_ULPD_PLL_CLK_REQ	1	/* In SWD_CLK_DIV_CTRL_SEL */
#घोषणा COM_ULPD_PLL_CLK_REQ	1	/* In COM_CLK_DIV_CTRL_SEL */
#घोषणा SWD_CLK_DIV_CTRL_SEL	0xfffe0874
#घोषणा COM_CLK_DIV_CTRL_SEL	0xfffe0878
#घोषणा SOFT_REQ_REG		0xfffe0834
#घोषणा SOFT_REQ_REG2		0xfffe0880

बाह्य __u32 arm_idlect1_mask;
बाह्य काष्ठा clk *api_ck_p, *ck_dpll1_p, *ck_ref_p;

बाह्य स्थिर काष्ठा clkops clkops_dspck;
बाह्य स्थिर काष्ठा clkops clkops_dummy;
बाह्य स्थिर काष्ठा clkops clkops_uart_16xx;
बाह्य स्थिर काष्ठा clkops clkops_generic;

/* used क्रम passing SoC type to omap1_अणुselect,round_toपूर्ण_table_rate() */
बाह्य u32 cpu_mask;

#पूर्ण_अगर
