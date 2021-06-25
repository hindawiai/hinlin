<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap_hwmod implementation क्रम OMAP2/3/4
 *
 * Copyright (C) 2009-2011 Nokia Corporation
 * Copyright (C) 2011-2012 Texas Instruments, Inc.
 *
 * Paul Walmsley, Benoथऍt Cousson, Kevin Hilman
 *
 * Created in collaboration with (alphabetical order): Thara Gopinath,
 * Tony Lindgren, Rajendra Nayak, Vikram Pandita, Sakari Poussa, Anand
 * Sawant, Santosh Shilimkar, Riअक्षरd Woodruff
 *
 * Introduction
 * ------------
 * One way to view an OMAP SoC is as a collection of largely unrelated
 * IP blocks connected by पूर्णांकerconnects.  The IP blocks include
 * devices such as ARM processors, audio serial पूर्णांकerfaces, UARTs,
 * etc.  Some of these devices, like the DSP, are created by TI;
 * others, like the SGX, largely originate from बाह्यal venकरोrs.  In
 * TI's करोcumentation, on-chip devices are referred to as "OMAP
 * modules."  Some of these IP blocks are identical across several
 * OMAP versions.  Others are revised frequently.
 *
 * These OMAP modules are tied together by various पूर्णांकerconnects.
 * Most of the address and data flow between modules is via OCP-based
 * पूर्णांकerconnects such as the L3 and L4 buses; but there are other
 * पूर्णांकerconnects that distribute the hardware घड़ी tree, handle idle
 * and reset संकेतing, supply घातer, and connect the modules to
 * various pads or balls on the OMAP package.
 *
 * OMAP hwmod provides a consistent way to describe the on-chip
 * hardware blocks and their पूर्णांकegration पूर्णांकo the rest of the chip.
 * This description can be स्वतःmatically generated from the TI
 * hardware database.  OMAP hwmod provides a standard, consistent API
 * to reset, enable, idle, and disable these hardware blocks.  And
 * hwmod provides a way क्रम other core code, such as the Linux device
 * code or the OMAP घातer management and address space mapping code,
 * to query the hardware database.
 *
 * Using hwmod
 * -----------
 * Drivers won't call hwmod functions directly.  That is करोne by the
 * omap_device code, and in rare occasions, by custom पूर्णांकegration code
 * in arch/arm/ *omap*.  The omap_device code includes functions to
 * build a काष्ठा platक्रमm_device using omap_hwmod data, and that is
 * currently how hwmod data is communicated to drivers and to the
 * Linux driver model.  Most drivers will call omap_hwmod functions only
 * indirectly, via pm_runसमय*() functions.
 *
 * From a layering perspective, here is where the OMAP hwmod code
 * fits पूर्णांकo the kernel software stack:
 *
 *            +-------------------------------+
 *            |      Device driver code       |
 *            |      (e.g., drivers/)         |
 *            +-------------------------------+
 *            |      Linux driver model       |
 *            |     (platक्रमm_device /        |
 *            |  platक्रमm_driver data/code)   |
 *            +-------------------------------+
 *            | OMAP core-driver पूर्णांकegration  |
 *            |(arch/arm/mach-omap2/devices.c)|
 *            +-------------------------------+
 *            |      omap_device code         |
 *            | (../plat-omap/omap_device.c)  |
 *            +-------------------------------+
 *   ---->    |    omap_hwmod code/data       |    <-----
 *            | (../mach-omap2/omap_hwmod*)   |
 *            +-------------------------------+
 *            | OMAP घड़ी/PRCM/रेजिस्टर fns  |
 *            | (अणुपढ़ो,ग_लिखोपूर्णl_relaxed, clk*) |
 *            +-------------------------------+
 *
 * Device drivers should not contain any OMAP-specअगरic code or data in
 * them.  They should only contain code to operate the IP block that
 * the driver is responsible क्रम.  This is because these IP blocks can
 * also appear in other SoCs, either from TI (such as DaVinci) or from
 * other manufacturers; and drivers should be reusable across other
 * platक्रमms.
 *
 * The OMAP hwmod code also will attempt to reset and idle all on-chip
 * devices upon boot.  The goal here is क्रम the kernel to be
 * completely self-reliant and independent from bootloaders.  This is
 * to ensure a repeatable configuration, both to ensure consistent
 * runसमय behavior, and to make it easier क्रम others to reproduce
 * bugs.
 *
 * OMAP module activity states
 * ---------------------------
 * The hwmod code considers modules to be in one of several activity
 * states.  IP blocks start out in an UNKNOWN state, then once they
 * are रेजिस्टरed via the hwmod code, proceed to the REGISTERED state.
 * Once their घड़ी names are resolved to घड़ी poपूर्णांकers, the module
 * enters the CLKS_INITED state; and finally, once the module has been
 * reset and the पूर्णांकegration रेजिस्टरs programmed, the INITIALIZED state
 * is entered.  The hwmod code will then place the module पूर्णांकo either
 * the IDLE state to save घातer, or in the हाल of a critical प्रणाली
 * module, the ENABLED state.
 *
 * OMAP core पूर्णांकegration code can then call omap_hwmod*() functions
 * directly to move the module between the IDLE, ENABLED, and DISABLED
 * states, as needed.  This is करोne during both the PM idle loop, and
 * in the OMAP core पूर्णांकegration code's implementation of the PM runसमय
 * functions.
 *
 * References
 * ----------
 * This is a partial list.
 * - OMAP2420 Mulसमयdia Processor Silicon Revision 2.1.1, 2.2 (SWPU064)
 * - OMAP2430 Mulसमयdia Device POP Silicon Revision 2.1 (SWPU090)
 * - OMAP34xx Mulसमयdia Device Silicon Revision 3.1 (SWPU108)
 * - OMAP4430 Mulसमयdia Device Silicon Revision 1.0 (SWPU140)
 * - Open Core Protocol Specअगरication 2.2
 *
 * To करो:
 * - handle IO mapping
 * - bus throughput & module latency measurement code
 *
 * XXX add tests at the beginning of each function to ensure the hwmod is
 * in the appropriate state
 * XXX error वापस values should be checked to ensure that they are
 * appropriate
 */
#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/memblock.h>

#समावेश <linux/platक्रमm_data/ti-sysc.h>

#समावेश <dt-bindings/bus/ti-sysc.h>

#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "clock.h"
#समावेश "omap_hwmod.h"

#समावेश "soc.h"
#समावेश "common.h"
#समावेश "clockdomain.h"
#समावेश "hdq1w.h"
#समावेश "mmc.h"
#समावेश "powerdomain.h"
#समावेश "cm2xxx.h"
#समावेश "cm3xxx.h"
#समावेश "cm33xx.h"
#समावेश "prm.h"
#समावेश "prm3xxx.h"
#समावेश "prm44xx.h"
#समावेश "prm33xx.h"
#समावेश "prminst44xx.h"
#समावेश "pm.h"
#समावेश "wd_timer.h"

/* Name of the OMAP hwmod क्रम the MPU */
#घोषणा MPU_INITIATOR_NAME		"mpu"

/*
 * Number of काष्ठा omap_hwmod_link records per काष्ठा
 * omap_hwmod_ocp_अगर record (master->slave and slave->master)
 */
#घोषणा LINKS_PER_OCP_IF		2

/*
 * Address offset (in bytes) between the reset control and the reset
 * status रेजिस्टरs: 4 bytes on OMAP4
 */
#घोषणा OMAP4_RST_CTRL_ST_OFFSET	4

/*
 * Maximum length क्रम module घड़ी handle names
 */
#घोषणा MOD_CLK_MAX_NAME_LEN		32

/**
 * काष्ठा clkctrl_provider - clkctrl provider mapping data
 * @num_addrs: number of base address ranges क्रम the provider
 * @addr: base address(es) क्रम the provider
 * @size: size(s) of the provider address space(s)
 * @node: device node associated with the provider
 * @link: list link
 */
काष्ठा clkctrl_provider अणु
	पूर्णांक			num_addrs;
	u32			*addr;
	u32			*size;
	काष्ठा device_node	*node;
	काष्ठा list_head	link;
पूर्ण;

अटल LIST_HEAD(clkctrl_providers);

/**
 * काष्ठा omap_hwmod_reset - IP specअगरic reset functions
 * @match: string to match against the module name
 * @len: number of अक्षरacters to match
 * @reset: IP specअगरic reset function
 *
 * Used only in हालs where काष्ठा omap_hwmod is dynamically allocated.
 */
काष्ठा omap_hwmod_reset अणु
	स्थिर अक्षर *match;
	पूर्णांक len;
	पूर्णांक (*reset)(काष्ठा omap_hwmod *oh);
पूर्ण;

/**
 * काष्ठा omap_hwmod_soc_ops - fn ptrs क्रम some SoC-specअगरic operations
 * @enable_module: function to enable a module (via MODULEMODE)
 * @disable_module: function to disable a module (via MODULEMODE)
 *
 * XXX Eventually this functionality will be hidden inside the PRM/CM
 * device drivers.  Until then, this should aव्योम huge blocks of cpu_is_*()
 * conditionals in this code.
 */
काष्ठा omap_hwmod_soc_ops अणु
	व्योम (*enable_module)(काष्ठा omap_hwmod *oh);
	पूर्णांक (*disable_module)(काष्ठा omap_hwmod *oh);
	पूर्णांक (*रुको_target_पढ़ोy)(काष्ठा omap_hwmod *oh);
	पूर्णांक (*निश्चित_hardreset)(काष्ठा omap_hwmod *oh,
				काष्ठा omap_hwmod_rst_info *ohri);
	पूर्णांक (*deनिश्चित_hardreset)(काष्ठा omap_hwmod *oh,
				  काष्ठा omap_hwmod_rst_info *ohri);
	पूर्णांक (*is_hardreset_निश्चितed)(काष्ठा omap_hwmod *oh,
				     काष्ठा omap_hwmod_rst_info *ohri);
	पूर्णांक (*init_clkdm)(काष्ठा omap_hwmod *oh);
	व्योम (*update_context_lost)(काष्ठा omap_hwmod *oh);
	पूर्णांक (*get_context_lost)(काष्ठा omap_hwmod *oh);
	पूर्णांक (*disable_direct_prcm)(काष्ठा omap_hwmod *oh);
	u32 (*xlate_clkctrl)(काष्ठा omap_hwmod *oh);
पूर्ण;

/* soc_ops: adapts the omap_hwmod code to the currently-booted SoC */
अटल काष्ठा omap_hwmod_soc_ops soc_ops;

/* omap_hwmod_list contains all रेजिस्टरed काष्ठा omap_hwmods */
अटल LIST_HEAD(omap_hwmod_list);
अटल DEFINE_MUTEX(list_lock);

/* mpu_oh: used to add/हटाओ MPU initiator from sleepdep list */
अटल काष्ठा omap_hwmod *mpu_oh;

/* inited: set to true once the hwmod code is initialized */
अटल bool inited;

/* Private functions */

/**
 * _update_sysc_cache - वापस the module OCP_SYSCONFIG रेजिस्टर, keep copy
 * @oh: काष्ठा omap_hwmod *
 *
 * Load the current value of the hwmod OCP_SYSCONFIG रेजिस्टर पूर्णांकo the
 * काष्ठा omap_hwmod क्रम later use.  Returns -EINVAL अगर the hwmod has no
 * OCP_SYSCONFIG रेजिस्टर or 0 upon success.
 */
अटल पूर्णांक _update_sysc_cache(काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh->class->sysc) अणु
		WARN(1, "omap_hwmod: %s: cannot read OCP_SYSCONFIG: not defined on hwmod's class\n", oh->name);
		वापस -EINVAL;
	पूर्ण

	/* XXX ensure module पूर्णांकerface घड़ी is up */

	oh->_sysc_cache = omap_hwmod_पढ़ो(oh, oh->class->sysc->sysc_offs);

	अगर (!(oh->class->sysc->sysc_flags & SYSC_NO_CACHE))
		oh->_पूर्णांक_flags |= _HWMOD_SYSCONFIG_LOADED;

	वापस 0;
पूर्ण

/**
 * _ग_लिखो_sysconfig - ग_लिखो a value to the module's OCP_SYSCONFIG रेजिस्टर
 * @v: OCP_SYSCONFIG value to ग_लिखो
 * @oh: काष्ठा omap_hwmod *
 *
 * Write @v पूर्णांकo the module class' OCP_SYSCONFIG रेजिस्टर, अगर it has
 * one.  No वापस value.
 */
अटल व्योम _ग_लिखो_sysconfig(u32 v, काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh->class->sysc) अणु
		WARN(1, "omap_hwmod: %s: cannot write OCP_SYSCONFIG: not defined on hwmod's class\n", oh->name);
		वापस;
	पूर्ण

	/* XXX ensure module पूर्णांकerface घड़ी is up */

	/* Module might have lost context, always update cache and रेजिस्टर */
	oh->_sysc_cache = v;

	/*
	 * Some IP blocks (such as RTC) require unlocking of IP beक्रमe
	 * accessing its रेजिस्टरs. If a function poपूर्णांकer is present
	 * to unlock, then call it beक्रमe accessing sysconfig and
	 * call lock after writing sysconfig.
	 */
	अगर (oh->class->unlock)
		oh->class->unlock(oh);

	omap_hwmod_ग_लिखो(v, oh, oh->class->sysc->sysc_offs);

	अगर (oh->class->lock)
		oh->class->lock(oh);
पूर्ण

/**
 * _set_master_standbymode: set the OCP_SYSCONFIG MIDLEMODE field in @v
 * @oh: काष्ठा omap_hwmod *
 * @standbymode: MIDLEMODE field bits
 * @v: poपूर्णांकer to रेजिस्टर contents to modअगरy
 *
 * Update the master standby mode bits in @v to be @standbymode क्रम
 * the @oh hwmod.  Does not ग_लिखो to the hardware.  Returns -EINVAL
 * upon error or 0 upon success.
 */
अटल पूर्णांक _set_master_standbymode(काष्ठा omap_hwmod *oh, u8 standbymode,
				   u32 *v)
अणु
	u32 mstandby_mask;
	u8 mstandby_shअगरt;

	अगर (!oh->class->sysc ||
	    !(oh->class->sysc->sysc_flags & SYSC_HAS_MIDLEMODE))
		वापस -EINVAL;

	अगर (!oh->class->sysc->sysc_fields) अणु
		WARN(1, "omap_hwmod: %s: offset struct for sysconfig not provided in class\n", oh->name);
		वापस -EINVAL;
	पूर्ण

	mstandby_shअगरt = oh->class->sysc->sysc_fields->midle_shअगरt;
	mstandby_mask = (0x3 << mstandby_shअगरt);

	*v &= ~mstandby_mask;
	*v |= __ffs(standbymode) << mstandby_shअगरt;

	वापस 0;
पूर्ण

/**
 * _set_slave_idlemode: set the OCP_SYSCONFIG SIDLEMODE field in @v
 * @oh: काष्ठा omap_hwmod *
 * @idlemode: SIDLEMODE field bits
 * @v: poपूर्णांकer to रेजिस्टर contents to modअगरy
 *
 * Update the slave idle mode bits in @v to be @idlemode क्रम the @oh
 * hwmod.  Does not ग_लिखो to the hardware.  Returns -EINVAL upon error
 * or 0 upon success.
 */
अटल पूर्णांक _set_slave_idlemode(काष्ठा omap_hwmod *oh, u8 idlemode, u32 *v)
अणु
	u32 sidle_mask;
	u8 sidle_shअगरt;

	अगर (!oh->class->sysc ||
	    !(oh->class->sysc->sysc_flags & SYSC_HAS_SIDLEMODE))
		वापस -EINVAL;

	अगर (!oh->class->sysc->sysc_fields) अणु
		WARN(1, "omap_hwmod: %s: offset struct for sysconfig not provided in class\n", oh->name);
		वापस -EINVAL;
	पूर्ण

	sidle_shअगरt = oh->class->sysc->sysc_fields->sidle_shअगरt;
	sidle_mask = (0x3 << sidle_shअगरt);

	*v &= ~sidle_mask;
	*v |= __ffs(idlemode) << sidle_shअगरt;

	वापस 0;
पूर्ण

/**
 * _set_घड़ीactivity: set OCP_SYSCONFIG.CLOCKACTIVITY bits in @v
 * @oh: काष्ठा omap_hwmod *
 * @घड़ीact: CLOCKACTIVITY field bits
 * @v: poपूर्णांकer to रेजिस्टर contents to modअगरy
 *
 * Update the घड़ीactivity mode bits in @v to be @घड़ीact क्रम the
 * @oh hwmod.  Used क्रम additional घातersaving on some modules.  Does
 * not ग_लिखो to the hardware.  Returns -EINVAL upon error or 0 upon
 * success.
 */
अटल पूर्णांक _set_घड़ीactivity(काष्ठा omap_hwmod *oh, u8 घड़ीact, u32 *v)
अणु
	u32 clkact_mask;
	u8  clkact_shअगरt;

	अगर (!oh->class->sysc ||
	    !(oh->class->sysc->sysc_flags & SYSC_HAS_CLOCKACTIVITY))
		वापस -EINVAL;

	अगर (!oh->class->sysc->sysc_fields) अणु
		WARN(1, "omap_hwmod: %s: offset struct for sysconfig not provided in class\n", oh->name);
		वापस -EINVAL;
	पूर्ण

	clkact_shअगरt = oh->class->sysc->sysc_fields->clkact_shअगरt;
	clkact_mask = (0x3 << clkact_shअगरt);

	*v &= ~clkact_mask;
	*v |= घड़ीact << clkact_shअगरt;

	वापस 0;
पूर्ण

/**
 * _set_softreset: set OCP_SYSCONFIG.SOFTRESET bit in @v
 * @oh: काष्ठा omap_hwmod *
 * @v: poपूर्णांकer to रेजिस्टर contents to modअगरy
 *
 * Set the SOFTRESET bit in @v क्रम hwmod @oh.  Returns -EINVAL upon
 * error or 0 upon success.
 */
अटल पूर्णांक _set_softreset(काष्ठा omap_hwmod *oh, u32 *v)
अणु
	u32 softrst_mask;

	अगर (!oh->class->sysc ||
	    !(oh->class->sysc->sysc_flags & SYSC_HAS_SOFTRESET))
		वापस -EINVAL;

	अगर (!oh->class->sysc->sysc_fields) अणु
		WARN(1, "omap_hwmod: %s: offset struct for sysconfig not provided in class\n", oh->name);
		वापस -EINVAL;
	पूर्ण

	softrst_mask = (0x1 << oh->class->sysc->sysc_fields->srst_shअगरt);

	*v |= softrst_mask;

	वापस 0;
पूर्ण

/**
 * _clear_softreset: clear OCP_SYSCONFIG.SOFTRESET bit in @v
 * @oh: काष्ठा omap_hwmod *
 * @v: poपूर्णांकer to रेजिस्टर contents to modअगरy
 *
 * Clear the SOFTRESET bit in @v क्रम hwmod @oh.  Returns -EINVAL upon
 * error or 0 upon success.
 */
अटल पूर्णांक _clear_softreset(काष्ठा omap_hwmod *oh, u32 *v)
अणु
	u32 softrst_mask;

	अगर (!oh->class->sysc ||
	    !(oh->class->sysc->sysc_flags & SYSC_HAS_SOFTRESET))
		वापस -EINVAL;

	अगर (!oh->class->sysc->sysc_fields) अणु
		WARN(1,
		     "omap_hwmod: %s: sysc_fields absent for sysconfig class\n",
		     oh->name);
		वापस -EINVAL;
	पूर्ण

	softrst_mask = (0x1 << oh->class->sysc->sysc_fields->srst_shअगरt);

	*v &= ~softrst_mask;

	वापस 0;
पूर्ण

/**
 * _रुको_softreset_complete - रुको क्रम an OCP softreset to complete
 * @oh: काष्ठा omap_hwmod * to रुको on
 *
 * Wait until the IP block represented by @oh reports that its OCP
 * softreset is complete.  This can be triggered by software (see
 * _ocp_softreset()) or by hardware upon वापसing from off-mode (one
 * example is HSMMC).  Waits क्रम up to MAX_MODULE_SOFTRESET_WAIT
 * microseconds.  Returns the number of microseconds रुकोed.
 */
अटल पूर्णांक _रुको_softreset_complete(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा omap_hwmod_class_sysconfig *sysc;
	u32 softrst_mask;
	पूर्णांक c = 0;

	sysc = oh->class->sysc;

	अगर (sysc->sysc_flags & SYSS_HAS_RESET_STATUS && sysc->syss_offs > 0)
		omap_test_समयout((omap_hwmod_पढ़ो(oh, sysc->syss_offs)
				   & SYSS_RESETDONE_MASK),
				  MAX_MODULE_SOFTRESET_WAIT, c);
	अन्यथा अगर (sysc->sysc_flags & SYSC_HAS_RESET_STATUS) अणु
		softrst_mask = (0x1 << sysc->sysc_fields->srst_shअगरt);
		omap_test_समयout(!(omap_hwmod_पढ़ो(oh, sysc->sysc_offs)
				    & softrst_mask),
				  MAX_MODULE_SOFTRESET_WAIT, c);
	पूर्ण

	वापस c;
पूर्ण

/**
 * _set_dmadisable: set OCP_SYSCONFIG.DMADISABLE bit in @v
 * @oh: काष्ठा omap_hwmod *
 *
 * The DMADISABLE bit is a semi-स्वतःmatic bit present in sysconfig रेजिस्टर
 * of some modules. When the DMA must perक्रमm पढ़ो/ग_लिखो accesses, the
 * DMADISABLE bit is cleared by the hardware. But when the DMA must stop
 * क्रम घातer management, software must set the DMADISABLE bit back to 1.
 *
 * Set the DMADISABLE bit in @v क्रम hwmod @oh.  Returns -EINVAL upon
 * error or 0 upon success.
 */
अटल पूर्णांक _set_dmadisable(काष्ठा omap_hwmod *oh)
अणु
	u32 v;
	u32 dmadisable_mask;

	अगर (!oh->class->sysc ||
	    !(oh->class->sysc->sysc_flags & SYSC_HAS_DMADISABLE))
		वापस -EINVAL;

	अगर (!oh->class->sysc->sysc_fields) अणु
		WARN(1, "omap_hwmod: %s: offset struct for sysconfig not provided in class\n", oh->name);
		वापस -EINVAL;
	पूर्ण

	/* घड़ीs must be on क्रम this operation */
	अगर (oh->_state != _HWMOD_STATE_ENABLED) अणु
		pr_warn("omap_hwmod: %s: dma can be disabled only from enabled state\n", oh->name);
		वापस -EINVAL;
	पूर्ण

	pr_debug("omap_hwmod: %s: setting DMADISABLE\n", oh->name);

	v = oh->_sysc_cache;
	dmadisable_mask =
		(0x1 << oh->class->sysc->sysc_fields->dmadisable_shअगरt);
	v |= dmadisable_mask;
	_ग_लिखो_sysconfig(v, oh);

	वापस 0;
पूर्ण

/**
 * _set_module_स्वतःidle: set the OCP_SYSCONFIG AUTOIDLE field in @v
 * @oh: काष्ठा omap_hwmod *
 * @स्वतःidle: desired AUTOIDLE bitfield value (0 or 1)
 * @v: poपूर्णांकer to रेजिस्टर contents to modअगरy
 *
 * Update the module स्वतःidle bit in @v to be @स्वतःidle क्रम the @oh
 * hwmod.  The स्वतःidle bit controls whether the module can gate
 * पूर्णांकernal घड़ीs स्वतःmatically when it isn't करोing anything; the
 * exact function of this bit varies on a per-module basis.  This
 * function करोes not ग_लिखो to the hardware.  Returns -EINVAL upon
 * error or 0 upon success.
 */
अटल पूर्णांक _set_module_स्वतःidle(काष्ठा omap_hwmod *oh, u8 स्वतःidle,
				u32 *v)
अणु
	u32 स्वतःidle_mask;
	u8 स्वतःidle_shअगरt;

	अगर (!oh->class->sysc ||
	    !(oh->class->sysc->sysc_flags & SYSC_HAS_AUTOIDLE))
		वापस -EINVAL;

	अगर (!oh->class->sysc->sysc_fields) अणु
		WARN(1, "omap_hwmod: %s: offset struct for sysconfig not provided in class\n", oh->name);
		वापस -EINVAL;
	पूर्ण

	स्वतःidle_shअगरt = oh->class->sysc->sysc_fields->स्वतःidle_shअगरt;
	स्वतःidle_mask = (0x1 << स्वतःidle_shअगरt);

	*v &= ~स्वतःidle_mask;
	*v |= स्वतःidle << स्वतःidle_shअगरt;

	वापस 0;
पूर्ण

/**
 * _enable_wakeup: set OCP_SYSCONFIG.ENAWAKEUP bit in the hardware
 * @oh: काष्ठा omap_hwmod *
 *
 * Allow the hardware module @oh to send wakeups.  Returns -EINVAL
 * upon error or 0 upon success.
 */
अटल पूर्णांक _enable_wakeup(काष्ठा omap_hwmod *oh, u32 *v)
अणु
	अगर (!oh->class->sysc ||
	    !((oh->class->sysc->sysc_flags & SYSC_HAS_ENAWAKEUP) ||
	      (oh->class->sysc->idlemodes & SIDLE_SMART_WKUP) ||
	      (oh->class->sysc->idlemodes & MSTANDBY_SMART_WKUP)))
		वापस -EINVAL;

	अगर (!oh->class->sysc->sysc_fields) अणु
		WARN(1, "omap_hwmod: %s: offset struct for sysconfig not provided in class\n", oh->name);
		वापस -EINVAL;
	पूर्ण

	अगर (oh->class->sysc->sysc_flags & SYSC_HAS_ENAWAKEUP)
		*v |= 0x1 << oh->class->sysc->sysc_fields->enwkup_shअगरt;

	अगर (oh->class->sysc->idlemodes & SIDLE_SMART_WKUP)
		_set_slave_idlemode(oh, HWMOD_IDLEMODE_SMART_WKUP, v);
	अगर (oh->class->sysc->idlemodes & MSTANDBY_SMART_WKUP)
		_set_master_standbymode(oh, HWMOD_IDLEMODE_SMART_WKUP, v);

	/* XXX test pwrdm_get_wken क्रम this hwmod's subप्रणाली */

	वापस 0;
पूर्ण

अटल काष्ठा घड़ीकरोमुख्य *_get_clkdm(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा clk_hw_omap *clk;

	अगर (!oh)
		वापस शून्य;

	अगर (oh->clkdm) अणु
		वापस oh->clkdm;
	पूर्ण अन्यथा अगर (oh->_clk) अणु
		अगर (!omap2_clk_is_hw_omap(__clk_get_hw(oh->_clk)))
			वापस शून्य;
		clk = to_clk_hw_omap(__clk_get_hw(oh->_clk));
		वापस clk->clkdm;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * _add_initiator_dep: prevent @oh from smart-idling जबतक @init_oh is active
 * @oh: काष्ठा omap_hwmod *
 *
 * Prevent the hardware module @oh from entering idle जबतक the
 * hardare module initiator @init_oh is active.  Useful when a module
 * will be accessed by a particular initiator (e.g., अगर a module will
 * be accessed by the IVA, there should be a sleepdep between the IVA
 * initiator and the module).  Only applies to modules in smart-idle
 * mode.  If the घड़ीकरोमुख्य is marked as not needing स्वतःdeps, वापस
 * 0 without करोing anything.  Otherwise, वापसs -EINVAL upon error or
 * passes aदीर्घ clkdm_add_sleepdep() value upon success.
 */
अटल पूर्णांक _add_initiator_dep(काष्ठा omap_hwmod *oh, काष्ठा omap_hwmod *init_oh)
अणु
	काष्ठा घड़ीकरोमुख्य *clkdm, *init_clkdm;

	clkdm = _get_clkdm(oh);
	init_clkdm = _get_clkdm(init_oh);

	अगर (!clkdm || !init_clkdm)
		वापस -EINVAL;

	अगर (clkdm && clkdm->flags & CLKDM_NO_AUTODEPS)
		वापस 0;

	वापस clkdm_add_sleepdep(clkdm, init_clkdm);
पूर्ण

/**
 * _del_initiator_dep: allow @oh to smart-idle even अगर @init_oh is active
 * @oh: काष्ठा omap_hwmod *
 *
 * Allow the hardware module @oh to enter idle जबतक the hardare
 * module initiator @init_oh is active.  Useful when a module will not
 * be accessed by a particular initiator (e.g., अगर a module will not
 * be accessed by the IVA, there should be no sleepdep between the IVA
 * initiator and the module).  Only applies to modules in smart-idle
 * mode.  If the घड़ीकरोमुख्य is marked as not needing स्वतःdeps, वापस
 * 0 without करोing anything.  Returns -EINVAL upon error or passes
 * aदीर्घ clkdm_del_sleepdep() value upon success.
 */
अटल पूर्णांक _del_initiator_dep(काष्ठा omap_hwmod *oh, काष्ठा omap_hwmod *init_oh)
अणु
	काष्ठा घड़ीकरोमुख्य *clkdm, *init_clkdm;

	clkdm = _get_clkdm(oh);
	init_clkdm = _get_clkdm(init_oh);

	अगर (!clkdm || !init_clkdm)
		वापस -EINVAL;

	अगर (clkdm && clkdm->flags & CLKDM_NO_AUTODEPS)
		वापस 0;

	वापस clkdm_del_sleepdep(clkdm, init_clkdm);
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_clkctrl_match_table[] __initस्थिर = अणु
	अणु .compatible = "ti,clkctrl" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init _setup_clkctrl_provider(काष्ठा device_node *np)
अणु
	स्थिर __be32 *addrp;
	काष्ठा clkctrl_provider *provider;
	u64 size;
	पूर्णांक i;

	provider = memblock_alloc(माप(*provider), SMP_CACHE_BYTES);
	अगर (!provider)
		वापस -ENOMEM;

	provider->node = np;

	provider->num_addrs =
		of_property_count_elems_of_size(np, "reg", माप(u32)) / 2;

	provider->addr =
		memblock_alloc(माप(व्योम *) * provider->num_addrs,
			       SMP_CACHE_BYTES);
	अगर (!provider->addr)
		वापस -ENOMEM;

	provider->size =
		memblock_alloc(माप(u32) * provider->num_addrs,
			       SMP_CACHE_BYTES);
	अगर (!provider->size)
		वापस -ENOMEM;

	क्रम (i = 0; i < provider->num_addrs; i++) अणु
		addrp = of_get_address(np, i, &size, शून्य);
		provider->addr[i] = (u32)of_translate_address(np, addrp);
		provider->size[i] = size;
		pr_debug("%s: %pOF: %x...%x\n", __func__, np, provider->addr[i],
			 provider->addr[i] + provider->size[i]);
	पूर्ण

	list_add(&provider->link, &clkctrl_providers);

	वापस 0;
पूर्ण

अटल पूर्णांक __init _init_clkctrl_providers(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret = 0;

	क्रम_each_matching_node(np, ti_clkctrl_match_table) अणु
		ret = _setup_clkctrl_provider(np);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 _omap4_xlate_clkctrl(काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh->prcm.omap4.modulemode)
		वापस 0;

	वापस omap_cm_xlate_clkctrl(oh->clkdm->prcm_partition,
				     oh->clkdm->cm_inst,
				     oh->prcm.omap4.clkctrl_offs);
पूर्ण

अटल काष्ठा clk *_lookup_clkctrl_clk(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा clkctrl_provider *provider;
	काष्ठा clk *clk;
	u32 addr;

	अगर (!soc_ops.xlate_clkctrl)
		वापस शून्य;

	addr = soc_ops.xlate_clkctrl(oh);
	अगर (!addr)
		वापस शून्य;

	pr_debug("%s: %s: addr=%x\n", __func__, oh->name, addr);

	list_क्रम_each_entry(provider, &clkctrl_providers, link) अणु
		पूर्णांक i;

		क्रम (i = 0; i < provider->num_addrs; i++) अणु
			अगर (provider->addr[i] <= addr &&
			    provider->addr[i] + provider->size[i] > addr) अणु
				काष्ठा of_phandle_args clkspec;

				clkspec.np = provider->node;
				clkspec.args_count = 2;
				clkspec.args[0] = addr - provider->addr[0];
				clkspec.args[1] = 0;

				clk = of_clk_get_from_provider(&clkspec);

				pr_debug("%s: %s got %p (offset=%x, provider=%pOF)\n",
					 __func__, oh->name, clk,
					 clkspec.args[0], provider->node);

				वापस clk;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * _init_मुख्य_clk - get a काष्ठा clk * क्रम the the hwmod's मुख्य functional clk
 * @oh: काष्ठा omap_hwmod *
 *
 * Called from _init_घड़ीs().  Populates the @oh _clk (मुख्य
 * functional घड़ी poपूर्णांकer) अगर a घड़ी matching the hwmod name is found,
 * or a मुख्य_clk is present.  Returns 0 on success or -EINVAL on error.
 */
अटल पूर्णांक _init_मुख्य_clk(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक ret = 0;
	काष्ठा clk *clk = शून्य;

	clk = _lookup_clkctrl_clk(oh);

	अगर (!IS_ERR_OR_शून्य(clk)) अणु
		pr_debug("%s: mapped main_clk %s for %s\n", __func__,
			 __clk_get_name(clk), oh->name);
		oh->मुख्य_clk = __clk_get_name(clk);
		oh->_clk = clk;
		soc_ops.disable_direct_prcm(oh);
	पूर्ण अन्यथा अणु
		अगर (!oh->मुख्य_clk)
			वापस 0;

		oh->_clk = clk_get(शून्य, oh->मुख्य_clk);
	पूर्ण

	अगर (IS_ERR(oh->_clk)) अणु
		pr_warn("omap_hwmod: %s: cannot clk_get main_clk %s\n",
			oh->name, oh->मुख्य_clk);
		वापस -EINVAL;
	पूर्ण
	/*
	 * HACK: This needs a re-visit once clk_prepare() is implemented
	 * to करो something meaningful. Today its just a no-op.
	 * If clk_prepare() is used at some poपूर्णांक to करो things like
	 * voltage scaling etc, then this would have to be moved to
	 * some poपूर्णांक where subप्रणालीs like i2c and pmic become
	 * available.
	 */
	clk_prepare(oh->_clk);

	अगर (!_get_clkdm(oh))
		pr_debug("omap_hwmod: %s: missing clockdomain for %s.\n",
			   oh->name, oh->मुख्य_clk);

	वापस ret;
पूर्ण

/**
 * _init_पूर्णांकerface_clks - get a काष्ठा clk * क्रम the the hwmod's पूर्णांकerface clks
 * @oh: काष्ठा omap_hwmod *
 *
 * Called from _init_घड़ीs().  Populates the @oh OCP slave पूर्णांकerface
 * घड़ी poपूर्णांकers.  Returns 0 on success or -EINVAL on error.
 */
अटल पूर्णांक _init_पूर्णांकerface_clks(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा omap_hwmod_ocp_अगर *os;
	काष्ठा clk *c;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(os, &oh->slave_ports, node) अणु
		अगर (!os->clk)
			जारी;

		c = clk_get(शून्य, os->clk);
		अगर (IS_ERR(c)) अणु
			pr_warn("omap_hwmod: %s: cannot clk_get interface_clk %s\n",
				oh->name, os->clk);
			ret = -EINVAL;
			जारी;
		पूर्ण
		os->_clk = c;
		/*
		 * HACK: This needs a re-visit once clk_prepare() is implemented
		 * to करो something meaningful. Today its just a no-op.
		 * If clk_prepare() is used at some poपूर्णांक to करो things like
		 * voltage scaling etc, then this would have to be moved to
		 * some poपूर्णांक where subप्रणालीs like i2c and pmic become
		 * available.
		 */
		clk_prepare(os->_clk);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * _init_opt_clk - get a काष्ठा clk * क्रम the the hwmod's optional घड़ीs
 * @oh: काष्ठा omap_hwmod *
 *
 * Called from _init_घड़ीs().  Populates the @oh omap_hwmod_opt_clk
 * घड़ी poपूर्णांकers.  Returns 0 on success or -EINVAL on error.
 */
अटल पूर्णांक _init_opt_clks(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा omap_hwmod_opt_clk *oc;
	काष्ठा clk *c;
	पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = oh->opt_clks_cnt, oc = oh->opt_clks; i > 0; i--, oc++) अणु
		c = clk_get(शून्य, oc->clk);
		अगर (IS_ERR(c)) अणु
			pr_warn("omap_hwmod: %s: cannot clk_get opt_clk %s\n",
				oh->name, oc->clk);
			ret = -EINVAL;
			जारी;
		पूर्ण
		oc->_clk = c;
		/*
		 * HACK: This needs a re-visit once clk_prepare() is implemented
		 * to करो something meaningful. Today its just a no-op.
		 * If clk_prepare() is used at some poपूर्णांक to करो things like
		 * voltage scaling etc, then this would have to be moved to
		 * some poपूर्णांक where subप्रणालीs like i2c and pmic become
		 * available.
		 */
		clk_prepare(oc->_clk);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम _enable_optional_घड़ीs(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा omap_hwmod_opt_clk *oc;
	पूर्णांक i;

	pr_debug("omap_hwmod: %s: enabling optional clocks\n", oh->name);

	क्रम (i = oh->opt_clks_cnt, oc = oh->opt_clks; i > 0; i--, oc++)
		अगर (oc->_clk) अणु
			pr_debug("omap_hwmod: enable %s:%s\n", oc->role,
				 __clk_get_name(oc->_clk));
			clk_enable(oc->_clk);
		पूर्ण
पूर्ण

अटल व्योम _disable_optional_घड़ीs(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा omap_hwmod_opt_clk *oc;
	पूर्णांक i;

	pr_debug("omap_hwmod: %s: disabling optional clocks\n", oh->name);

	क्रम (i = oh->opt_clks_cnt, oc = oh->opt_clks; i > 0; i--, oc++)
		अगर (oc->_clk) अणु
			pr_debug("omap_hwmod: disable %s:%s\n", oc->role,
				 __clk_get_name(oc->_clk));
			clk_disable(oc->_clk);
		पूर्ण
पूर्ण

/**
 * _enable_घड़ीs - enable hwmod मुख्य घड़ी and पूर्णांकerface घड़ीs
 * @oh: काष्ठा omap_hwmod *
 *
 * Enables all घड़ीs necessary क्रम रेजिस्टर पढ़ोs and ग_लिखोs to succeed
 * on the hwmod @oh.  Returns 0.
 */
अटल पूर्णांक _enable_घड़ीs(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा omap_hwmod_ocp_अगर *os;

	pr_debug("omap_hwmod: %s: enabling clocks\n", oh->name);

	अगर (oh->flags & HWMOD_OPT_CLKS_NEEDED)
		_enable_optional_घड़ीs(oh);

	अगर (oh->_clk)
		clk_enable(oh->_clk);

	list_क्रम_each_entry(os, &oh->slave_ports, node) अणु
		अगर (os->_clk && (os->flags & OCPIF_SWSUP_IDLE)) अणु
			omap2_clk_deny_idle(os->_clk);
			clk_enable(os->_clk);
		पूर्ण
	पूर्ण

	/* The opt घड़ीs are controlled by the device driver. */

	वापस 0;
पूर्ण

/**
 * _omap4_clkctrl_managed_by_clkfwk - true अगर clkctrl managed by घड़ी framework
 * @oh: काष्ठा omap_hwmod *
 */
अटल bool _omap4_clkctrl_managed_by_clkfwk(काष्ठा omap_hwmod *oh)
अणु
	अगर (oh->prcm.omap4.flags & HWMOD_OMAP4_CLKFWK_CLKCTR_CLOCK)
		वापस true;

	वापस false;
पूर्ण

/**
 * _omap4_has_clkctrl_घड़ी - वापसs true अगर a module has clkctrl घड़ी
 * @oh: काष्ठा omap_hwmod *
 */
अटल bool _omap4_has_clkctrl_घड़ी(काष्ठा omap_hwmod *oh)
अणु
	अगर (oh->prcm.omap4.clkctrl_offs)
		वापस true;

	अगर (!oh->prcm.omap4.clkctrl_offs &&
	    oh->prcm.omap4.flags & HWMOD_OMAP4_ZERO_CLKCTRL_OFFSET)
		वापस true;

	वापस false;
पूर्ण

/**
 * _disable_घड़ीs - disable hwmod मुख्य घड़ी and पूर्णांकerface घड़ीs
 * @oh: काष्ठा omap_hwmod *
 *
 * Disables the hwmod @oh मुख्य functional and पूर्णांकerface घड़ीs.  Returns 0.
 */
अटल पूर्णांक _disable_घड़ीs(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा omap_hwmod_ocp_अगर *os;

	pr_debug("omap_hwmod: %s: disabling clocks\n", oh->name);

	अगर (oh->_clk)
		clk_disable(oh->_clk);

	list_क्रम_each_entry(os, &oh->slave_ports, node) अणु
		अगर (os->_clk && (os->flags & OCPIF_SWSUP_IDLE)) अणु
			clk_disable(os->_clk);
			omap2_clk_allow_idle(os->_clk);
		पूर्ण
	पूर्ण

	अगर (oh->flags & HWMOD_OPT_CLKS_NEEDED)
		_disable_optional_घड़ीs(oh);

	/* The opt घड़ीs are controlled by the device driver. */

	वापस 0;
पूर्ण

/**
 * _omap4_enable_module - enable CLKCTRL modulemode on OMAP4
 * @oh: काष्ठा omap_hwmod *
 *
 * Enables the PRCM module mode related to the hwmod @oh.
 * No वापस value.
 */
अटल व्योम _omap4_enable_module(काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh->clkdm || !oh->prcm.omap4.modulemode ||
	    _omap4_clkctrl_managed_by_clkfwk(oh))
		वापस;

	pr_debug("omap_hwmod: %s: %s: %d\n",
		 oh->name, __func__, oh->prcm.omap4.modulemode);

	omap_cm_module_enable(oh->prcm.omap4.modulemode,
			      oh->clkdm->prcm_partition,
			      oh->clkdm->cm_inst, oh->prcm.omap4.clkctrl_offs);
पूर्ण

/**
 * _omap4_रुको_target_disable - रुको क्रम a module to be disabled on OMAP4
 * @oh: काष्ठा omap_hwmod *
 *
 * Wait क्रम a module @oh to enter slave idle.  Returns 0 अगर the module
 * करोes not have an IDLEST bit or अगर the module successfully enters
 * slave idle; otherwise, pass aदीर्घ the वापस value of the
 * appropriate *_cm*_रुको_module_idle() function.
 */
अटल पूर्णांक _omap4_रुको_target_disable(काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh)
		वापस -EINVAL;

	अगर (oh->_पूर्णांक_flags & _HWMOD_NO_MPU_PORT || !oh->clkdm)
		वापस 0;

	अगर (oh->flags & HWMOD_NO_IDLEST)
		वापस 0;

	अगर (_omap4_clkctrl_managed_by_clkfwk(oh))
		वापस 0;

	अगर (!_omap4_has_clkctrl_घड़ी(oh))
		वापस 0;

	वापस omap_cm_रुको_module_idle(oh->clkdm->prcm_partition,
					oh->clkdm->cm_inst,
					oh->prcm.omap4.clkctrl_offs, 0);
पूर्ण

/**
 * _save_mpu_port_index - find and save the index to @oh's MPU port
 * @oh: काष्ठा omap_hwmod *
 *
 * Determines the array index of the OCP slave port that the MPU uses
 * to address the device, and saves it पूर्णांकo the काष्ठा omap_hwmod.
 * Intended to be called during hwmod registration only. No वापस
 * value.
 */
अटल व्योम __init _save_mpu_port_index(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा omap_hwmod_ocp_अगर *os = शून्य;

	अगर (!oh)
		वापस;

	oh->_पूर्णांक_flags |= _HWMOD_NO_MPU_PORT;

	list_क्रम_each_entry(os, &oh->slave_ports, node) अणु
		अगर (os->user & OCP_USER_MPU) अणु
			oh->_mpu_port = os;
			oh->_पूर्णांक_flags &= ~_HWMOD_NO_MPU_PORT;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

/**
 * _find_mpu_rt_port - वापस omap_hwmod_ocp_अगर accessible by the MPU
 * @oh: काष्ठा omap_hwmod *
 *
 * Given a poपूर्णांकer to a काष्ठा omap_hwmod record @oh, वापस a poपूर्णांकer
 * to the काष्ठा omap_hwmod_ocp_अगर record that is used by the MPU to
 * communicate with the IP block.  This पूर्णांकerface need not be directly
 * connected to the MPU (and almost certainly is not), but is directly
 * connected to the IP block represented by @oh.  Returns a poपूर्णांकer
 * to the काष्ठा omap_hwmod_ocp_अगर * upon success, or वापसs शून्य upon
 * error or अगर there करोes not appear to be a path from the MPU to this
 * IP block.
 */
अटल काष्ठा omap_hwmod_ocp_अगर *_find_mpu_rt_port(काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh || oh->_पूर्णांक_flags & _HWMOD_NO_MPU_PORT || oh->slaves_cnt == 0)
		वापस शून्य;

	वापस oh->_mpu_port;
पूर्ण;

/**
 * _enable_sysc - try to bring a module out of idle via OCP_SYSCONFIG
 * @oh: काष्ठा omap_hwmod *
 *
 * Ensure that the OCP_SYSCONFIG रेजिस्टर क्रम the IP block represented
 * by @oh is set to indicate to the PRCM that the IP block is active.
 * Usually this means placing the module पूर्णांकo smart-idle mode and
 * smart-standby, but अगर there is a bug in the स्वतःmatic idle handling
 * क्रम the IP block, it may need to be placed पूर्णांकo the क्रमce-idle or
 * no-idle variants of these modes.  No वापस value.
 */
अटल व्योम _enable_sysc(काष्ठा omap_hwmod *oh)
अणु
	u8 idlemode, sf;
	u32 v;
	bool clkdm_act;
	काष्ठा घड़ीकरोमुख्य *clkdm;

	अगर (!oh->class->sysc)
		वापस;

	/*
	 * Wait until reset has completed, this is needed as the IP
	 * block is reset स्वतःmatically by hardware in some हालs
	 * (off-mode क्रम example), and the drivers require the
	 * IP to be पढ़ोy when they access it
	 */
	अगर (oh->flags & HWMOD_CONTROL_OPT_CLKS_IN_RESET)
		_enable_optional_घड़ीs(oh);
	_रुको_softreset_complete(oh);
	अगर (oh->flags & HWMOD_CONTROL_OPT_CLKS_IN_RESET)
		_disable_optional_घड़ीs(oh);

	v = oh->_sysc_cache;
	sf = oh->class->sysc->sysc_flags;

	clkdm = _get_clkdm(oh);
	अगर (sf & SYSC_HAS_SIDLEMODE) अणु
		अगर (oh->flags & HWMOD_SWSUP_SIDLE ||
		    oh->flags & HWMOD_SWSUP_SIDLE_ACT) अणु
			idlemode = HWMOD_IDLEMODE_NO;
		पूर्ण अन्यथा अणु
			अगर (sf & SYSC_HAS_ENAWAKEUP)
				_enable_wakeup(oh, &v);
			अगर (oh->class->sysc->idlemodes & SIDLE_SMART_WKUP)
				idlemode = HWMOD_IDLEMODE_SMART_WKUP;
			अन्यथा
				idlemode = HWMOD_IDLEMODE_SMART;
		पूर्ण

		/*
		 * This is special handling क्रम some IPs like
		 * 32k sync समयr. Force them to idle!
		 */
		clkdm_act = (clkdm && clkdm->flags & CLKDM_ACTIVE_WITH_MPU);
		अगर (clkdm_act && !(oh->class->sysc->idlemodes &
				   (SIDLE_SMART | SIDLE_SMART_WKUP)))
			idlemode = HWMOD_IDLEMODE_FORCE;

		_set_slave_idlemode(oh, idlemode, &v);
	पूर्ण

	अगर (sf & SYSC_HAS_MIDLEMODE) अणु
		अगर (oh->flags & HWMOD_FORCE_MSTANDBY) अणु
			idlemode = HWMOD_IDLEMODE_FORCE;
		पूर्ण अन्यथा अगर (oh->flags & HWMOD_SWSUP_MSTANDBY) अणु
			idlemode = HWMOD_IDLEMODE_NO;
		पूर्ण अन्यथा अणु
			अगर (sf & SYSC_HAS_ENAWAKEUP)
				_enable_wakeup(oh, &v);
			अगर (oh->class->sysc->idlemodes & MSTANDBY_SMART_WKUP)
				idlemode = HWMOD_IDLEMODE_SMART_WKUP;
			अन्यथा
				idlemode = HWMOD_IDLEMODE_SMART;
		पूर्ण
		_set_master_standbymode(oh, idlemode, &v);
	पूर्ण

	/*
	 * XXX The घड़ी framework should handle this, by
	 * calling पूर्णांकo this code.  But this must रुको until the
	 * घड़ी काष्ठाures are tagged with omap_hwmod entries
	 */
	अगर ((oh->flags & HWMOD_SET_DEFAULT_CLOCKACT) &&
	    (sf & SYSC_HAS_CLOCKACTIVITY))
		_set_घड़ीactivity(oh, CLOCKACT_TEST_ICLK, &v);

	_ग_लिखो_sysconfig(v, oh);

	/*
	 * Set the स्वतःidle bit only after setting the smartidle bit
	 * Setting this will not have any impact on the other modules.
	 */
	अगर (sf & SYSC_HAS_AUTOIDLE) अणु
		idlemode = (oh->flags & HWMOD_NO_OCP_AUTOIDLE) ?
			0 : 1;
		_set_module_स्वतःidle(oh, idlemode, &v);
		_ग_लिखो_sysconfig(v, oh);
	पूर्ण
पूर्ण

/**
 * _idle_sysc - try to put a module पूर्णांकo idle via OCP_SYSCONFIG
 * @oh: काष्ठा omap_hwmod *
 *
 * If module is marked as SWSUP_SIDLE, क्रमce the module पूर्णांकo slave
 * idle; otherwise, configure it क्रम smart-idle.  If module is marked
 * as SWSUP_MSUSPEND, क्रमce the module पूर्णांकo master standby; otherwise,
 * configure it क्रम smart-standby.  No वापस value.
 */
अटल व्योम _idle_sysc(काष्ठा omap_hwmod *oh)
अणु
	u8 idlemode, sf;
	u32 v;

	अगर (!oh->class->sysc)
		वापस;

	v = oh->_sysc_cache;
	sf = oh->class->sysc->sysc_flags;

	अगर (sf & SYSC_HAS_SIDLEMODE) अणु
		अगर (oh->flags & HWMOD_SWSUP_SIDLE) अणु
			idlemode = HWMOD_IDLEMODE_FORCE;
		पूर्ण अन्यथा अणु
			अगर (sf & SYSC_HAS_ENAWAKEUP)
				_enable_wakeup(oh, &v);
			अगर (oh->class->sysc->idlemodes & SIDLE_SMART_WKUP)
				idlemode = HWMOD_IDLEMODE_SMART_WKUP;
			अन्यथा
				idlemode = HWMOD_IDLEMODE_SMART;
		पूर्ण
		_set_slave_idlemode(oh, idlemode, &v);
	पूर्ण

	अगर (sf & SYSC_HAS_MIDLEMODE) अणु
		अगर ((oh->flags & HWMOD_SWSUP_MSTANDBY) ||
		    (oh->flags & HWMOD_FORCE_MSTANDBY)) अणु
			idlemode = HWMOD_IDLEMODE_FORCE;
		पूर्ण अन्यथा अणु
			अगर (sf & SYSC_HAS_ENAWAKEUP)
				_enable_wakeup(oh, &v);
			अगर (oh->class->sysc->idlemodes & MSTANDBY_SMART_WKUP)
				idlemode = HWMOD_IDLEMODE_SMART_WKUP;
			अन्यथा
				idlemode = HWMOD_IDLEMODE_SMART;
		पूर्ण
		_set_master_standbymode(oh, idlemode, &v);
	पूर्ण

	/* If the cached value is the same as the new value, skip the ग_लिखो */
	अगर (oh->_sysc_cache != v)
		_ग_लिखो_sysconfig(v, oh);
पूर्ण

/**
 * _shutकरोwn_sysc - क्रमce a module पूर्णांकo idle via OCP_SYSCONFIG
 * @oh: काष्ठा omap_hwmod *
 *
 * Force the module पूर्णांकo slave idle and master suspend. No वापस
 * value.
 */
अटल व्योम _shutकरोwn_sysc(काष्ठा omap_hwmod *oh)
अणु
	u32 v;
	u8 sf;

	अगर (!oh->class->sysc)
		वापस;

	v = oh->_sysc_cache;
	sf = oh->class->sysc->sysc_flags;

	अगर (sf & SYSC_HAS_SIDLEMODE)
		_set_slave_idlemode(oh, HWMOD_IDLEMODE_FORCE, &v);

	अगर (sf & SYSC_HAS_MIDLEMODE)
		_set_master_standbymode(oh, HWMOD_IDLEMODE_FORCE, &v);

	अगर (sf & SYSC_HAS_AUTOIDLE)
		_set_module_स्वतःidle(oh, 1, &v);

	_ग_लिखो_sysconfig(v, oh);
पूर्ण

/**
 * _lookup - find an omap_hwmod by name
 * @name: find an omap_hwmod by name
 *
 * Return a poपूर्णांकer to an omap_hwmod by name, or शून्य अगर not found.
 */
अटल काष्ठा omap_hwmod *_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा omap_hwmod *oh, *temp_oh;

	oh = शून्य;

	list_क्रम_each_entry(temp_oh, &omap_hwmod_list, node) अणु
		अगर (!म_भेद(name, temp_oh->name)) अणु
			oh = temp_oh;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस oh;
पूर्ण

/**
 * _init_clkdm - look up a घड़ीकरोमुख्य name, store poपूर्णांकer in omap_hwmod
 * @oh: काष्ठा omap_hwmod *
 *
 * Convert a घड़ीकरोमुख्य name stored in a काष्ठा omap_hwmod पूर्णांकo a
 * घड़ीकरोमुख्य poपूर्णांकer, and save it पूर्णांकo the काष्ठा omap_hwmod.
 * Return -EINVAL अगर the clkdm_name lookup failed.
 */
अटल पूर्णांक _init_clkdm(काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh->clkdm_name) अणु
		pr_debug("omap_hwmod: %s: missing clockdomain\n", oh->name);
		वापस 0;
	पूर्ण

	oh->clkdm = clkdm_lookup(oh->clkdm_name);
	अगर (!oh->clkdm) अणु
		pr_warn("omap_hwmod: %s: could not associate to clkdm %s\n",
			oh->name, oh->clkdm_name);
		वापस 0;
	पूर्ण

	pr_debug("omap_hwmod: %s: associated to clkdm %s\n",
		oh->name, oh->clkdm_name);

	वापस 0;
पूर्ण

/**
 * _init_घड़ीs - clk_get() all घड़ीs associated with this hwmod. Retrieve as
 * well the घड़ीकरोमुख्य.
 * @oh: काष्ठा omap_hwmod *
 * @np: device_node mapped to this hwmod
 *
 * Called by omap_hwmod_setup_*() (after omap2_clk_init()).
 * Resolves all घड़ी names embedded in the hwmod.  Returns 0 on
 * success, or a negative error code on failure.
 */
अटल पूर्णांक _init_घड़ीs(काष्ठा omap_hwmod *oh, काष्ठा device_node *np)
अणु
	पूर्णांक ret = 0;

	अगर (oh->_state != _HWMOD_STATE_REGISTERED)
		वापस 0;

	pr_debug("omap_hwmod: %s: looking up clocks\n", oh->name);

	अगर (soc_ops.init_clkdm)
		ret |= soc_ops.init_clkdm(oh);

	ret |= _init_मुख्य_clk(oh);
	ret |= _init_पूर्णांकerface_clks(oh);
	ret |= _init_opt_clks(oh);

	अगर (!ret)
		oh->_state = _HWMOD_STATE_CLKS_INITED;
	अन्यथा
		pr_warn("omap_hwmod: %s: cannot _init_clocks\n", oh->name);

	वापस ret;
पूर्ण

/**
 * _lookup_hardreset - fill रेजिस्टर bit info क्रम this hwmod/reset line
 * @oh: काष्ठा omap_hwmod *
 * @name: name of the reset line in the context of this hwmod
 * @ohri: काष्ठा omap_hwmod_rst_info * that this function will fill in
 *
 * Return the bit position of the reset line that match the
 * input name. Return -ENOENT अगर not found.
 */
अटल पूर्णांक _lookup_hardreset(काष्ठा omap_hwmod *oh, स्थिर अक्षर *name,
			     काष्ठा omap_hwmod_rst_info *ohri)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < oh->rst_lines_cnt; i++) अणु
		स्थिर अक्षर *rst_line = oh->rst_lines[i].name;
		अगर (!म_भेद(rst_line, name)) अणु
			ohri->rst_shअगरt = oh->rst_lines[i].rst_shअगरt;
			ohri->st_shअगरt = oh->rst_lines[i].st_shअगरt;
			pr_debug("omap_hwmod: %s: %s: %s: rst %d st %d\n",
				 oh->name, __func__, rst_line, ohri->rst_shअगरt,
				 ohri->st_shअगरt);

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

/**
 * _निश्चित_hardreset - निश्चित the HW reset line of submodules
 * contained in the hwmod module.
 * @oh: काष्ठा omap_hwmod *
 * @name: name of the reset line to lookup and निश्चित
 *
 * Some IP like dsp, ipu or iva contain processor that require an HW
 * reset line to be निश्चित / deनिश्चित in order to enable fully the IP.
 * Returns -EINVAL अगर @oh is null, -ENOSYS अगर we have no way of
 * निश्चितing the hardreset line on the currently-booted SoC, or passes
 * aदीर्घ the वापस value from _lookup_hardreset() or the SoC's
 * निश्चित_hardreset code.
 */
अटल पूर्णांक _निश्चित_hardreset(काष्ठा omap_hwmod *oh, स्थिर अक्षर *name)
अणु
	काष्ठा omap_hwmod_rst_info ohri;
	पूर्णांक ret = -EINVAL;

	अगर (!oh)
		वापस -EINVAL;

	अगर (!soc_ops.निश्चित_hardreset)
		वापस -ENOSYS;

	ret = _lookup_hardreset(oh, name, &ohri);
	अगर (ret < 0)
		वापस ret;

	ret = soc_ops.निश्चित_hardreset(oh, &ohri);

	वापस ret;
पूर्ण

/**
 * _deनिश्चित_hardreset - deनिश्चित the HW reset line of submodules contained
 * in the hwmod module.
 * @oh: काष्ठा omap_hwmod *
 * @name: name of the reset line to look up and deनिश्चित
 *
 * Some IP like dsp, ipu or iva contain processor that require an HW
 * reset line to be निश्चित / deनिश्चित in order to enable fully the IP.
 * Returns -EINVAL अगर @oh is null, -ENOSYS अगर we have no way of
 * deनिश्चितing the hardreset line on the currently-booted SoC, or passes
 * aदीर्घ the वापस value from _lookup_hardreset() or the SoC's
 * deनिश्चित_hardreset code.
 */
अटल पूर्णांक _deनिश्चित_hardreset(काष्ठा omap_hwmod *oh, स्थिर अक्षर *name)
अणु
	काष्ठा omap_hwmod_rst_info ohri;
	पूर्णांक ret = -EINVAL;

	अगर (!oh)
		वापस -EINVAL;

	अगर (!soc_ops.deनिश्चित_hardreset)
		वापस -ENOSYS;

	ret = _lookup_hardreset(oh, name, &ohri);
	अगर (ret < 0)
		वापस ret;

	अगर (oh->clkdm) अणु
		/*
		 * A घड़ीकरोमुख्य must be in SW_SUP otherwise reset
		 * might not be completed. The घड़ीकरोमुख्य can be set
		 * in HW_AUTO only when the module become पढ़ोy.
		 */
		clkdm_deny_idle(oh->clkdm);
		ret = clkdm_hwmod_enable(oh->clkdm, oh);
		अगर (ret) अणु
			WARN(1, "omap_hwmod: %s: could not enable clockdomain %s: %d\n",
			     oh->name, oh->clkdm->name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	_enable_घड़ीs(oh);
	अगर (soc_ops.enable_module)
		soc_ops.enable_module(oh);

	ret = soc_ops.deनिश्चित_hardreset(oh, &ohri);

	अगर (soc_ops.disable_module)
		soc_ops.disable_module(oh);
	_disable_घड़ीs(oh);

	अगर (ret == -EBUSY)
		pr_warn("omap_hwmod: %s: failed to hardreset\n", oh->name);

	अगर (oh->clkdm) अणु
		/*
		 * Set the घड़ीकरोमुख्य to HW_AUTO, assuming that the
		 * previous state was HW_AUTO.
		 */
		clkdm_allow_idle(oh->clkdm);

		clkdm_hwmod_disable(oh->clkdm, oh);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * _पढ़ो_hardreset - पढ़ो the HW reset line state of submodules
 * contained in the hwmod module
 * @oh: काष्ठा omap_hwmod *
 * @name: name of the reset line to look up and पढ़ो
 *
 * Return the state of the reset line.  Returns -EINVAL अगर @oh is
 * null, -ENOSYS अगर we have no way of पढ़ोing the hardreset line
 * status on the currently-booted SoC, or passes aदीर्घ the वापस
 * value from _lookup_hardreset() or the SoC's is_hardreset_निश्चितed
 * code.
 */
अटल पूर्णांक _पढ़ो_hardreset(काष्ठा omap_hwmod *oh, स्थिर अक्षर *name)
अणु
	काष्ठा omap_hwmod_rst_info ohri;
	पूर्णांक ret = -EINVAL;

	अगर (!oh)
		वापस -EINVAL;

	अगर (!soc_ops.is_hardreset_निश्चितed)
		वापस -ENOSYS;

	ret = _lookup_hardreset(oh, name, &ohri);
	अगर (ret < 0)
		वापस ret;

	वापस soc_ops.is_hardreset_निश्चितed(oh, &ohri);
पूर्ण

/**
 * _are_all_hardreset_lines_निश्चितed - वापस true अगर the @oh is hard-reset
 * @oh: काष्ठा omap_hwmod *
 *
 * If all hardreset lines associated with @oh are निश्चितed, then वापस true.
 * Otherwise, अगर part of @oh is out hardreset or अगर no hardreset lines
 * associated with @oh are निश्चितed, then वापस false.
 * This function is used to aव्योम executing some parts of the IP block
 * enable/disable sequence अगर its hardreset line is set.
 */
अटल bool _are_all_hardreset_lines_निश्चितed(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक i, rst_cnt = 0;

	अगर (oh->rst_lines_cnt == 0)
		वापस false;

	क्रम (i = 0; i < oh->rst_lines_cnt; i++)
		अगर (_पढ़ो_hardreset(oh, oh->rst_lines[i].name) > 0)
			rst_cnt++;

	अगर (oh->rst_lines_cnt == rst_cnt)
		वापस true;

	वापस false;
पूर्ण

/**
 * _are_any_hardreset_lines_निश्चितed - वापस true अगर any part of @oh is
 * hard-reset
 * @oh: काष्ठा omap_hwmod *
 *
 * If any hardreset lines associated with @oh are निश्चितed, then
 * वापस true.  Otherwise, अगर no hardreset lines associated with @oh
 * are निश्चितed, or अगर @oh has no hardreset lines, then वापस false.
 * This function is used to aव्योम executing some parts of the IP block
 * enable/disable sequence अगर any hardreset line is set.
 */
अटल bool _are_any_hardreset_lines_निश्चितed(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक rst_cnt = 0;
	पूर्णांक i;

	क्रम (i = 0; i < oh->rst_lines_cnt && rst_cnt == 0; i++)
		अगर (_पढ़ो_hardreset(oh, oh->rst_lines[i].name) > 0)
			rst_cnt++;

	वापस (rst_cnt) ? true : false;
पूर्ण

/**
 * _omap4_disable_module - enable CLKCTRL modulemode on OMAP4
 * @oh: काष्ठा omap_hwmod *
 *
 * Disable the PRCM module mode related to the hwmod @oh.
 * Return EINVAL अगर the modulemode is not supported and 0 in हाल of success.
 */
अटल पूर्णांक _omap4_disable_module(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक v;

	अगर (!oh->clkdm || !oh->prcm.omap4.modulemode ||
	    _omap4_clkctrl_managed_by_clkfwk(oh))
		वापस -EINVAL;

	/*
	 * Since पूर्णांकegration code might still be करोing something, only
	 * disable अगर all lines are under hardreset.
	 */
	अगर (_are_any_hardreset_lines_निश्चितed(oh))
		वापस 0;

	pr_debug("omap_hwmod: %s: %s\n", oh->name, __func__);

	omap_cm_module_disable(oh->clkdm->prcm_partition, oh->clkdm->cm_inst,
			       oh->prcm.omap4.clkctrl_offs);

	v = _omap4_रुको_target_disable(oh);
	अगर (v)
		pr_warn("omap_hwmod: %s: _wait_target_disable failed\n",
			oh->name);

	वापस 0;
पूर्ण

/**
 * _ocp_softreset - reset an omap_hwmod via the OCP_SYSCONFIG bit
 * @oh: काष्ठा omap_hwmod *
 *
 * Resets an omap_hwmod @oh via the OCP_SYSCONFIG bit.  hwmod must be
 * enabled क्रम this to work.  Returns -ENOENT अगर the hwmod cannot be
 * reset this way, -EINVAL अगर the hwmod is in the wrong state,
 * -ETIMEDOUT अगर the module did not reset in समय, or 0 upon success.
 *
 * In OMAP3 a specअगरic SYSSTATUS रेजिस्टर is used to get the reset status.
 * Starting in OMAP4, some IPs करो not have SYSSTATUS रेजिस्टरs and instead
 * use the SYSCONFIG softreset bit to provide the status.
 *
 * Note that some IP like McBSP करो have reset control but करोn't have
 * reset status.
 */
अटल पूर्णांक _ocp_softreset(काष्ठा omap_hwmod *oh)
अणु
	u32 v;
	पूर्णांक c = 0;
	पूर्णांक ret = 0;

	अगर (!oh->class->sysc ||
	    !(oh->class->sysc->sysc_flags & SYSC_HAS_SOFTRESET))
		वापस -ENOENT;

	/* घड़ीs must be on क्रम this operation */
	अगर (oh->_state != _HWMOD_STATE_ENABLED) अणु
		pr_warn("omap_hwmod: %s: reset can only be entered from enabled state\n",
			oh->name);
		वापस -EINVAL;
	पूर्ण

	/* For some modules, all optionnal घड़ीs need to be enabled as well */
	अगर (oh->flags & HWMOD_CONTROL_OPT_CLKS_IN_RESET)
		_enable_optional_घड़ीs(oh);

	pr_debug("omap_hwmod: %s: resetting via OCP SOFTRESET\n", oh->name);

	v = oh->_sysc_cache;
	ret = _set_softreset(oh, &v);
	अगर (ret)
		जाओ dis_opt_clks;

	_ग_लिखो_sysconfig(v, oh);

	अगर (oh->class->sysc->srst_udelay)
		udelay(oh->class->sysc->srst_udelay);

	c = _रुको_softreset_complete(oh);
	अगर (c == MAX_MODULE_SOFTRESET_WAIT) अणु
		pr_warn("omap_hwmod: %s: softreset failed (waited %d usec)\n",
			oh->name, MAX_MODULE_SOFTRESET_WAIT);
		ret = -ETIMEDOUT;
		जाओ dis_opt_clks;
	पूर्ण अन्यथा अणु
		pr_debug("omap_hwmod: %s: softreset in %d usec\n", oh->name, c);
	पूर्ण

	ret = _clear_softreset(oh, &v);
	अगर (ret)
		जाओ dis_opt_clks;

	_ग_लिखो_sysconfig(v, oh);

	/*
	 * XXX add _HWMOD_STATE_WEDGED क्रम modules that करोn't come back from
	 * _रुको_target_पढ़ोy() or _reset()
	 */

dis_opt_clks:
	अगर (oh->flags & HWMOD_CONTROL_OPT_CLKS_IN_RESET)
		_disable_optional_घड़ीs(oh);

	वापस ret;
पूर्ण

/**
 * _reset - reset an omap_hwmod
 * @oh: काष्ठा omap_hwmod *
 *
 * Resets an omap_hwmod @oh.  If the module has a custom reset
 * function poपूर्णांकer defined, then call it to reset the IP block, and
 * pass aदीर्घ its वापस value to the caller.  Otherwise, अगर the IP
 * block has an OCP_SYSCONFIG रेजिस्टर with a SOFTRESET bitfield
 * associated with it, call a function to reset the IP block via that
 * method, and pass aदीर्घ the वापस value to the caller.  Finally, अगर
 * the IP block has some hardreset lines associated with it, निश्चित
 * all of those, but करो _not_ deनिश्चित them. (This is because driver
 * authors have expressed an apparent requirement to control the
 * deनिश्चितion of the hardreset lines themselves.)
 *
 * The शेष software reset mechanism क्रम most OMAP IP blocks is
 * triggered via the OCP_SYSCONFIG.SOFTRESET bit.  However, some
 * hwmods cannot be reset via this method.  Some are not tarमाला_लो and
 * thereक्रमe have no OCP header रेजिस्टरs to access.  Others (like the
 * IVA) have idiosyncratic reset sequences.  So क्रम these relatively
 * rare हालs, custom reset code can be supplied in the काष्ठा
 * omap_hwmod_class .reset function poपूर्णांकer.
 *
 * _set_dmadisable() is called to set the DMADISABLE bit so that it
 * करोes not prevent idling of the प्रणाली. This is necessary क्रम हालs
 * where ROMCODE/BOOTLOADER uses dma and transfers control to the
 * kernel without disabling dma.
 *
 * Passes aदीर्घ the वापस value from either _ocp_softreset() or the
 * custom reset function - these must वापस -EINVAL अगर the hwmod
 * cannot be reset this way or अगर the hwmod is in the wrong state,
 * -ETIMEDOUT अगर the module did not reset in समय, or 0 upon success.
 */
अटल पूर्णांक _reset(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक i, r;

	pr_debug("omap_hwmod: %s: resetting\n", oh->name);

	अगर (oh->class->reset) अणु
		r = oh->class->reset(oh);
	पूर्ण अन्यथा अणु
		अगर (oh->rst_lines_cnt > 0) अणु
			क्रम (i = 0; i < oh->rst_lines_cnt; i++)
				_निश्चित_hardreset(oh, oh->rst_lines[i].name);
			वापस 0;
		पूर्ण अन्यथा अणु
			r = _ocp_softreset(oh);
			अगर (r == -ENOENT)
				r = 0;
		पूर्ण
	पूर्ण

	_set_dmadisable(oh);

	/*
	 * OCP_SYSCONFIG bits need to be reprogrammed after a
	 * softreset.  The _enable() function should be split to aव्योम
	 * the reग_लिखो of the OCP_SYSCONFIG रेजिस्टर.
	 */
	अगर (oh->class->sysc) अणु
		_update_sysc_cache(oh);
		_enable_sysc(oh);
	पूर्ण

	वापस r;
पूर्ण

/**
 * _omap4_update_context_lost - increment hwmod context loss counter अगर
 * hwmod context was lost, and clear hardware context loss reg
 * @oh: hwmod to check क्रम context loss
 *
 * If the PRCM indicates that the hwmod @oh lost context, increment
 * our in-memory context loss counter, and clear the RM_*_CONTEXT
 * bits. No वापस value.
 */
अटल व्योम _omap4_update_context_lost(काष्ठा omap_hwmod *oh)
अणु
	अगर (oh->prcm.omap4.flags & HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT)
		वापस;

	अगर (!prm_was_any_context_lost_old(oh->clkdm->pwrdm.ptr->prcm_partition,
					  oh->clkdm->pwrdm.ptr->prcm_offs,
					  oh->prcm.omap4.context_offs))
		वापस;

	oh->prcm.omap4.context_lost_counter++;
	prm_clear_context_loss_flags_old(oh->clkdm->pwrdm.ptr->prcm_partition,
					 oh->clkdm->pwrdm.ptr->prcm_offs,
					 oh->prcm.omap4.context_offs);
पूर्ण

/**
 * _omap4_get_context_lost - get context loss counter क्रम a hwmod
 * @oh: hwmod to get context loss counter क्रम
 *
 * Returns the in-memory context loss counter क्रम a hwmod.
 */
अटल पूर्णांक _omap4_get_context_lost(काष्ठा omap_hwmod *oh)
अणु
	वापस oh->prcm.omap4.context_lost_counter;
पूर्ण

/**
 * _enable - enable an omap_hwmod
 * @oh: काष्ठा omap_hwmod *
 *
 * Enables an omap_hwmod @oh such that the MPU can access the hwmod's
 * रेजिस्टर target.  Returns -EINVAL अगर the hwmod is in the wrong
 * state or passes aदीर्घ the वापस value of _रुको_target_पढ़ोy().
 */
अटल पूर्णांक _enable(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक r;

	pr_debug("omap_hwmod: %s: enabling\n", oh->name);

	/*
	 * hwmods with HWMOD_INIT_NO_IDLE flag set are left in enabled
	 * state at init.
	 */
	अगर (oh->_पूर्णांक_flags & _HWMOD_SKIP_ENABLE) अणु
		oh->_पूर्णांक_flags &= ~_HWMOD_SKIP_ENABLE;
		वापस 0;
	पूर्ण

	अगर (oh->_state != _HWMOD_STATE_INITIALIZED &&
	    oh->_state != _HWMOD_STATE_IDLE &&
	    oh->_state != _HWMOD_STATE_DISABLED) अणु
		WARN(1, "omap_hwmod: %s: enabled state can only be entered from initialized, idle, or disabled state\n",
			oh->name);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If an IP block contains HW reset lines and all of them are
	 * निश्चितed, we let पूर्णांकegration code associated with that
	 * block handle the enable.  We've received very little
	 * inक्रमmation on what those driver authors need, and until
	 * detailed inक्रमmation is provided and the driver code is
	 * posted to the खुला lists, this is probably the best we
	 * can करो.
	 */
	अगर (_are_all_hardreset_lines_निश्चितed(oh))
		वापस 0;

	_add_initiator_dep(oh, mpu_oh);

	अगर (oh->clkdm) अणु
		/*
		 * A घड़ीकरोमुख्य must be in SW_SUP beक्रमe enabling
		 * completely the module. The घड़ीकरोमुख्य can be set
		 * in HW_AUTO only when the module become पढ़ोy.
		 */
		clkdm_deny_idle(oh->clkdm);
		r = clkdm_hwmod_enable(oh->clkdm, oh);
		अगर (r) अणु
			WARN(1, "omap_hwmod: %s: could not enable clockdomain %s: %d\n",
			     oh->name, oh->clkdm->name, r);
			वापस r;
		पूर्ण
	पूर्ण

	_enable_घड़ीs(oh);
	अगर (soc_ops.enable_module)
		soc_ops.enable_module(oh);
	अगर (oh->flags & HWMOD_BLOCK_WFI)
		cpu_idle_poll_ctrl(true);

	अगर (soc_ops.update_context_lost)
		soc_ops.update_context_lost(oh);

	r = (soc_ops.रुको_target_पढ़ोy) ? soc_ops.रुको_target_पढ़ोy(oh) :
		-EINVAL;
	अगर (oh->clkdm && !(oh->flags & HWMOD_CLKDM_NOAUTO))
		clkdm_allow_idle(oh->clkdm);

	अगर (!r) अणु
		oh->_state = _HWMOD_STATE_ENABLED;

		/* Access the sysconfig only अगर the target is पढ़ोy */
		अगर (oh->class->sysc) अणु
			अगर (!(oh->_पूर्णांक_flags & _HWMOD_SYSCONFIG_LOADED))
				_update_sysc_cache(oh);
			_enable_sysc(oh);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (soc_ops.disable_module)
			soc_ops.disable_module(oh);
		_disable_घड़ीs(oh);
		pr_err("omap_hwmod: %s: _wait_target_ready failed: %d\n",
		       oh->name, r);

		अगर (oh->clkdm)
			clkdm_hwmod_disable(oh->clkdm, oh);
	पूर्ण

	वापस r;
पूर्ण

/**
 * _idle - idle an omap_hwmod
 * @oh: काष्ठा omap_hwmod *
 *
 * Idles an omap_hwmod @oh.  This should be called once the hwmod has
 * no further work.  Returns -EINVAL अगर the hwmod is in the wrong
 * state or वापसs 0.
 */
अटल पूर्णांक _idle(काष्ठा omap_hwmod *oh)
अणु
	अगर (oh->flags & HWMOD_NO_IDLE) अणु
		oh->_पूर्णांक_flags |= _HWMOD_SKIP_ENABLE;
		वापस 0;
	पूर्ण

	pr_debug("omap_hwmod: %s: idling\n", oh->name);

	अगर (_are_all_hardreset_lines_निश्चितed(oh))
		वापस 0;

	अगर (oh->_state != _HWMOD_STATE_ENABLED) अणु
		WARN(1, "omap_hwmod: %s: idle state can only be entered from enabled state\n",
			oh->name);
		वापस -EINVAL;
	पूर्ण

	अगर (oh->class->sysc)
		_idle_sysc(oh);
	_del_initiator_dep(oh, mpu_oh);

	/*
	 * If HWMOD_CLKDM_NOAUTO is set then we करोn't
	 * deny idle the clkdm again since idle was alपढ़ोy denied
	 * in _enable()
	 */
	अगर (oh->clkdm && !(oh->flags & HWMOD_CLKDM_NOAUTO))
		clkdm_deny_idle(oh->clkdm);

	अगर (oh->flags & HWMOD_BLOCK_WFI)
		cpu_idle_poll_ctrl(false);
	अगर (soc_ops.disable_module)
		soc_ops.disable_module(oh);

	/*
	 * The module must be in idle mode beक्रमe disabling any parents
	 * घड़ीs. Otherwise, the parent घड़ी might be disabled beक्रमe
	 * the module transition is करोne, and thus will prevent the
	 * transition to complete properly.
	 */
	_disable_घड़ीs(oh);
	अगर (oh->clkdm) अणु
		clkdm_allow_idle(oh->clkdm);
		clkdm_hwmod_disable(oh->clkdm, oh);
	पूर्ण

	oh->_state = _HWMOD_STATE_IDLE;

	वापस 0;
पूर्ण

/**
 * _shutकरोwn - shutकरोwn an omap_hwmod
 * @oh: काष्ठा omap_hwmod *
 *
 * Shut करोwn an omap_hwmod @oh.  This should be called when the driver
 * used क्रम the hwmod is हटाओd or unloaded or अगर the driver is not
 * used by the प्रणाली.  Returns -EINVAL अगर the hwmod is in the wrong
 * state or वापसs 0.
 */
अटल पूर्णांक _shutकरोwn(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक ret, i;
	u8 prev_state;

	अगर (_are_all_hardreset_lines_निश्चितed(oh))
		वापस 0;

	अगर (oh->_state != _HWMOD_STATE_IDLE &&
	    oh->_state != _HWMOD_STATE_ENABLED) अणु
		WARN(1, "omap_hwmod: %s: disabled state can only be entered from idle, or enabled state\n",
			oh->name);
		वापस -EINVAL;
	पूर्ण

	pr_debug("omap_hwmod: %s: disabling\n", oh->name);

	अगर (oh->class->pre_shutकरोwn) अणु
		prev_state = oh->_state;
		अगर (oh->_state == _HWMOD_STATE_IDLE)
			_enable(oh);
		ret = oh->class->pre_shutकरोwn(oh);
		अगर (ret) अणु
			अगर (prev_state == _HWMOD_STATE_IDLE)
				_idle(oh);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (oh->class->sysc) अणु
		अगर (oh->_state == _HWMOD_STATE_IDLE)
			_enable(oh);
		_shutकरोwn_sysc(oh);
	पूर्ण

	/* घड़ीs and deps are alपढ़ोy disabled in idle */
	अगर (oh->_state == _HWMOD_STATE_ENABLED) अणु
		_del_initiator_dep(oh, mpu_oh);
		/* XXX what about the other प्रणाली initiators here? dma, dsp */
		अगर (oh->flags & HWMOD_BLOCK_WFI)
			cpu_idle_poll_ctrl(false);
		अगर (soc_ops.disable_module)
			soc_ops.disable_module(oh);
		_disable_घड़ीs(oh);
		अगर (oh->clkdm)
			clkdm_hwmod_disable(oh->clkdm, oh);
	पूर्ण
	/* XXX Should this code also क्रमce-disable the optional घड़ीs? */

	क्रम (i = 0; i < oh->rst_lines_cnt; i++)
		_निश्चित_hardreset(oh, oh->rst_lines[i].name);

	oh->_state = _HWMOD_STATE_DISABLED;

	वापस 0;
पूर्ण

अटल पूर्णांक of_dev_find_hwmod(काष्ठा device_node *np,
			     काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक count, i, res;
	स्थिर अक्षर *p;

	count = of_property_count_strings(np, "ti,hwmods");
	अगर (count < 1)
		वापस -ENODEV;

	क्रम (i = 0; i < count; i++) अणु
		res = of_property_पढ़ो_string_index(np, "ti,hwmods",
						    i, &p);
		अगर (res)
			जारी;
		अगर (!म_भेद(p, oh->name)) अणु
			pr_debug("omap_hwmod: dt %pOFn[%i] uses hwmod %s\n",
				 np, i, oh->name);
			वापस i;
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

/**
 * of_dev_hwmod_lookup - look up needed hwmod from dt blob
 * @np: काष्ठा device_node *
 * @oh: काष्ठा omap_hwmod *
 * @index: index of the entry found
 * @found: काष्ठा device_node * found or शून्य
 *
 * Parse the dt blob and find out needed hwmod. Recursive function is
 * implemented to take care hierarchical dt blob parsing.
 * Return: Returns 0 on success, -ENODEV when not found.
 */
अटल पूर्णांक of_dev_hwmod_lookup(काष्ठा device_node *np,
			       काष्ठा omap_hwmod *oh,
			       पूर्णांक *index,
			       काष्ठा device_node **found)
अणु
	काष्ठा device_node *np0 = शून्य;
	पूर्णांक res;

	res = of_dev_find_hwmod(np, oh);
	अगर (res >= 0) अणु
		*found = np;
		*index = res;
		वापस 0;
	पूर्ण

	क्रम_each_child_of_node(np, np0) अणु
		काष्ठा device_node *fc;
		पूर्णांक i;

		res = of_dev_hwmod_lookup(np0, oh, &i, &fc);
		अगर (res == 0) अणु
			*found = fc;
			*index = i;
			of_node_put(np0);
			वापस 0;
		पूर्ण
	पूर्ण

	*found = शून्य;
	*index = 0;

	वापस -ENODEV;
पूर्ण

/**
 * omap_hwmod_fix_mpu_rt_idx - fix up mpu_rt_idx रेजिस्टर offsets
 *
 * @oh: काष्ठा omap_hwmod *
 * @np: काष्ठा device_node *
 *
 * Fix up module रेजिस्टर offsets क्रम modules with mpu_rt_idx.
 * Only needed क्रम cpsw with पूर्णांकerconnect target module defined
 * in device tree जबतक still using legacy hwmod platक्रमm data
 * क्रम rev, sysc and syss रेजिस्टरs.
 *
 * Can be हटाओd when all cpsw hwmod platक्रमm data has been
 * dropped.
 */
अटल व्योम omap_hwmod_fix_mpu_rt_idx(काष्ठा omap_hwmod *oh,
				      काष्ठा device_node *np,
				      काष्ठा resource *res)
अणु
	काष्ठा device_node *child = शून्य;
	पूर्णांक error;

	child = of_get_next_child(np, child);
	अगर (!child)
		वापस;

	error = of_address_to_resource(child, oh->mpu_rt_idx, res);
	अगर (error)
		pr_err("%s: error mapping mpu_rt_idx: %i\n",
		       __func__, error);
पूर्ण

/**
 * omap_hwmod_parse_module_range - map module IO range from device tree
 * @oh: काष्ठा omap_hwmod *
 * @np: काष्ठा device_node *
 *
 * Parse the device tree range an पूर्णांकerconnect target module provides
 * क्रम it's child device IP blocks. This way we can support the old
 * "ti,hwmods" property with just dts data without a need क्रम platक्रमm
 * data क्रम IO resources. And we करोn't need all the child IP device
 * nodes available in the dts.
 */
पूर्णांक omap_hwmod_parse_module_range(काष्ठा omap_hwmod *oh,
				  काष्ठा device_node *np,
				  काष्ठा resource *res)
अणु
	काष्ठा property *prop;
	स्थिर __be32 *ranges;
	स्थिर अक्षर *name;
	u32 nr_addr, nr_size;
	u64 base, size;
	पूर्णांक len, error;

	अगर (!res)
		वापस -EINVAL;

	ranges = of_get_property(np, "ranges", &len);
	अगर (!ranges)
		वापस -ENOENT;

	len /= माप(*ranges);

	अगर (len < 3)
		वापस -EINVAL;

	of_property_क्रम_each_string(np, "compatible", prop, name)
		अगर (!म_भेदन("ti,sysc-", name, 8))
			अवरोध;

	अगर (!name)
		वापस -ENOENT;

	error = of_property_पढ़ो_u32(np, "#address-cells", &nr_addr);
	अगर (error)
		वापस -ENOENT;

	error = of_property_पढ़ो_u32(np, "#size-cells", &nr_size);
	अगर (error)
		वापस -ENOENT;

	अगर (nr_addr != 1 || nr_size != 1) अणु
		pr_err("%s: invalid range for %s->%pOFn\n", __func__,
		       oh->name, np);
		वापस -EINVAL;
	पूर्ण

	ranges++;
	base = of_translate_address(np, ranges++);
	size = be32_to_cpup(ranges);

	pr_debug("omap_hwmod: %s %pOFn at 0x%llx size 0x%llx\n",
		 oh->name, np, base, size);

	अगर (oh && oh->mpu_rt_idx) अणु
		omap_hwmod_fix_mpu_rt_idx(oh, np, res);

		वापस 0;
	पूर्ण

	res->start = base;
	res->end = base + size - 1;
	res->flags = IORESOURCE_MEM;

	वापस 0;
पूर्ण

/**
 * _init_mpu_rt_base - populate the भव address क्रम a hwmod
 * @oh: काष्ठा omap_hwmod * to locate the भव address
 * @data: (unused, caller should pass शून्य)
 * @index: index of the reg entry iospace in device tree
 * @np: काष्ठा device_node * of the IP block's device node in the DT data
 *
 * Cache the भव address used by the MPU to access this IP block's
 * रेजिस्टरs.  This address is needed early so the OCP रेजिस्टरs that
 * are part of the device's address space can be ioremapped properly.
 *
 * If SYSC access is not needed, the रेजिस्टरs will not be remapped
 * and non-availability of MPU access is not treated as an error.
 *
 * Returns 0 on success, -EINVAL अगर an invalid hwmod is passed, and
 * -ENXIO on असलent or invalid रेजिस्टर target address space.
 */
अटल पूर्णांक __init _init_mpu_rt_base(काष्ठा omap_hwmod *oh, व्योम *data,
				    पूर्णांक index, काष्ठा device_node *np)
अणु
	व्योम __iomem *बहु_शुरू = शून्य;
	काष्ठा resource res;
	पूर्णांक error;

	अगर (!oh)
		वापस -EINVAL;

	_save_mpu_port_index(oh);

	/* अगर we करोn't need sysc access we don't need to ioremap */
	अगर (!oh->class->sysc)
		वापस 0;

	/* we can't जारी without MPU PORT अगर we need sysc access */
	अगर (oh->_पूर्णांक_flags & _HWMOD_NO_MPU_PORT)
		वापस -ENXIO;

	अगर (!np) अणु
		pr_err("omap_hwmod: %s: no dt node\n", oh->name);
		वापस -ENXIO;
	पूर्ण

	/* Do we have a dts range क्रम the पूर्णांकerconnect target module? */
	error = omap_hwmod_parse_module_range(oh, np, &res);
	अगर (!error)
		बहु_शुरू = ioremap(res.start, resource_size(&res));

	/* No ranges, rely on device reg entry */
	अगर (!बहु_शुरू)
		बहु_शुरू = of_iomap(np, index + oh->mpu_rt_idx);
	अगर (!बहु_शुरू) अणु
		pr_err("omap_hwmod: %s: Missing dt reg%i for %pOF\n",
		       oh->name, index, np);
		वापस -ENXIO;
	पूर्ण

	pr_debug("omap_hwmod: %s: MPU register target at va %p\n",
		 oh->name, बहु_शुरू);

	oh->_mpu_rt_va = बहु_शुरू;
	वापस 0;
पूर्ण

अटल व्योम __init parse_module_flags(काष्ठा omap_hwmod *oh,
				      काष्ठा device_node *np)
अणु
	अगर (of_find_property(np, "ti,no-reset-on-init", शून्य))
		oh->flags |= HWMOD_INIT_NO_RESET;
	अगर (of_find_property(np, "ti,no-idle-on-init", शून्य))
		oh->flags |= HWMOD_INIT_NO_IDLE;
	अगर (of_find_property(np, "ti,no-idle", शून्य))
		oh->flags |= HWMOD_NO_IDLE;
पूर्ण

/**
 * _init - initialize पूर्णांकernal data क्रम the hwmod @oh
 * @oh: काष्ठा omap_hwmod *
 * @n: (unused)
 *
 * Look up the घड़ीs and the address space used by the MPU to access
 * रेजिस्टरs beदीर्घing to the hwmod @oh.  @oh must alपढ़ोy be
 * रेजिस्टरed at this poपूर्णांक.  This is the first of two phases क्रम
 * hwmod initialization.  Code called here करोes not touch any hardware
 * रेजिस्टरs, it simply prepares पूर्णांकernal data काष्ठाures.  Returns 0
 * upon success or अगर the hwmod isn't registered or if the hwmod's
 * address space is not defined, or -EINVAL upon failure.
 */
अटल पूर्णांक __init _init(काष्ठा omap_hwmod *oh, व्योम *data)
अणु
	पूर्णांक r, index;
	काष्ठा device_node *np = शून्य;
	काष्ठा device_node *bus;

	अगर (oh->_state != _HWMOD_STATE_REGISTERED)
		वापस 0;

	bus = of_find_node_by_name(शून्य, "ocp");
	अगर (!bus)
		वापस -ENODEV;

	r = of_dev_hwmod_lookup(bus, oh, &index, &np);
	अगर (r)
		pr_debug("omap_hwmod: %s missing dt data\n", oh->name);
	अन्यथा अगर (np && index)
		pr_warn("omap_hwmod: %s using broken dt data from %pOFn\n",
			oh->name, np);

	r = _init_mpu_rt_base(oh, शून्य, index, np);
	अगर (r < 0) अणु
		WARN(1, "omap_hwmod: %s: doesn't have mpu register target base\n",
		     oh->name);
		वापस 0;
	पूर्ण

	r = _init_घड़ीs(oh, np);
	अगर (r < 0) अणु
		WARN(1, "omap_hwmod: %s: couldn't init clocks\n", oh->name);
		वापस -EINVAL;
	पूर्ण

	अगर (np) अणु
		काष्ठा device_node *child;

		parse_module_flags(oh, np);
		child = of_get_next_child(np, शून्य);
		अगर (child)
			parse_module_flags(oh, child);
	पूर्ण

	oh->_state = _HWMOD_STATE_INITIALIZED;

	वापस 0;
पूर्ण

/**
 * _setup_iclk_स्वतःidle - configure an IP block's पूर्णांकerface घड़ीs
 * @oh: काष्ठा omap_hwmod *
 *
 * Set up the module's पूर्णांकerface घड़ीs.  XXX This function is still mostly
 * a stub; implementing this properly requires iclk स्वतःidle usecounting in
 * the घड़ी code.   No वापस value.
 */
अटल व्योम _setup_iclk_स्वतःidle(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा omap_hwmod_ocp_अगर *os;

	अगर (oh->_state != _HWMOD_STATE_INITIALIZED)
		वापस;

	list_क्रम_each_entry(os, &oh->slave_ports, node) अणु
		अगर (!os->_clk)
			जारी;

		अगर (os->flags & OCPIF_SWSUP_IDLE) अणु
			/*
			 * we might have multiple users of one iclk with
			 * dअगरferent requirements, disable स्वतःidle when
			 * the module is enabled, e.g. dss iclk
			 */
		पूर्ण अन्यथा अणु
			/* we are enabling स्वतःidle afterwards anyways */
			clk_enable(os->_clk);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

/**
 * _setup_reset - reset an IP block during the setup process
 * @oh: काष्ठा omap_hwmod *
 *
 * Reset the IP block corresponding to the hwmod @oh during the setup
 * process.  The IP block is first enabled so it can be successfully
 * reset.  Returns 0 upon success or a negative error code upon
 * failure.
 */
अटल पूर्णांक _setup_reset(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक r = 0;

	अगर (oh->_state != _HWMOD_STATE_INITIALIZED)
		वापस -EINVAL;

	अगर (oh->flags & HWMOD_EXT_OPT_MAIN_CLK)
		वापस -EPERM;

	अगर (oh->rst_lines_cnt == 0) अणु
		r = _enable(oh);
		अगर (r) अणु
			pr_warn("omap_hwmod: %s: cannot be enabled for reset (%d)\n",
				oh->name, oh->_state);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!(oh->flags & HWMOD_INIT_NO_RESET))
		r = _reset(oh);

	वापस r;
पूर्ण

/**
 * _setup_postsetup - transition to the appropriate state after _setup
 * @oh: काष्ठा omap_hwmod *
 *
 * Place an IP block represented by @oh पूर्णांकo a "post-setup" state --
 * either IDLE, ENABLED, or DISABLED.  ("post-setup" simply means that
 * this function is called at the end of _setup().)  The postsetup
 * state क्रम an IP block can be changed by calling
 * omap_hwmod_enter_postsetup_state() early in the boot process,
 * beक्रमe one of the omap_hwmod_setup*() functions are called क्रम the
 * IP block.
 *
 * The IP block stays in this state until a PM runसमय-based driver is
 * loaded क्रम that IP block.  A post-setup state of IDLE is
 * appropriate क्रम almost all IP blocks with runसमय PM-enabled
 * drivers, since those drivers are able to enable the IP block.  A
 * post-setup state of ENABLED is appropriate क्रम kernels with PM
 * runसमय disabled.  The DISABLED state is appropriate क्रम unusual IP
 * blocks such as the MPU WDTIMER on kernels without WDTIMER drivers
 * included, since the WDTIMER starts running on reset and will reset
 * the MPU अगर left active.
 *
 * This post-setup mechanism is deprecated.  Once all of the OMAP
 * drivers have been converted to use PM runसमय, and all of the IP
 * block data and पूर्णांकerconnect data is available to the hwmod code, it
 * should be possible to replace this mechanism with a "lazy reset"
 * arrangement.  In a "lazy reset" setup, each IP block is enabled
 * when the driver first probes, then all reमुख्यing IP blocks without
 * drivers are either shut करोwn or enabled after the drivers have
 * loaded.  However, this cannot take place until the above
 * preconditions have been met, since otherwise the late reset code
 * has no way of knowing which IP blocks are in use by drivers, and
 * which ones are unused.
 *
 * No वापस value.
 */
अटल व्योम _setup_postsetup(काष्ठा omap_hwmod *oh)
अणु
	u8 postsetup_state;

	अगर (oh->rst_lines_cnt > 0)
		वापस;

	postsetup_state = oh->_postsetup_state;
	अगर (postsetup_state == _HWMOD_STATE_UNKNOWN)
		postsetup_state = _HWMOD_STATE_ENABLED;

	/*
	 * XXX HWMOD_INIT_NO_IDLE करोes not beदीर्घ in hwmod data -
	 * it should be set by the core code as a runसमय flag during startup
	 */
	अगर ((oh->flags & (HWMOD_INIT_NO_IDLE | HWMOD_NO_IDLE)) &&
	    (postsetup_state == _HWMOD_STATE_IDLE)) अणु
		oh->_पूर्णांक_flags |= _HWMOD_SKIP_ENABLE;
		postsetup_state = _HWMOD_STATE_ENABLED;
	पूर्ण

	अगर (postsetup_state == _HWMOD_STATE_IDLE)
		_idle(oh);
	अन्यथा अगर (postsetup_state == _HWMOD_STATE_DISABLED)
		_shutकरोwn(oh);
	अन्यथा अगर (postsetup_state != _HWMOD_STATE_ENABLED)
		WARN(1, "hwmod: %s: unknown postsetup state %d! defaulting to enabled\n",
		     oh->name, postsetup_state);

	वापस;
पूर्ण

/**
 * _setup - prepare IP block hardware क्रम use
 * @oh: काष्ठा omap_hwmod *
 * @n: (unused, pass शून्य)
 *
 * Configure the IP block represented by @oh.  This may include
 * enabling the IP block, resetting it, and placing it पूर्णांकo a
 * post-setup state, depending on the type of IP block and applicable
 * flags.  IP blocks are reset to prevent any previous configuration
 * by the bootloader or previous operating प्रणाली from पूर्णांकerfering
 * with घातer management or other parts of the प्रणाली.  The reset can
 * be aव्योमed; see omap_hwmod_no_setup_reset().  This is the second of
 * two phases क्रम hwmod initialization.  Code called here generally
 * affects the IP block hardware, or प्रणाली पूर्णांकegration hardware
 * associated with the IP block.  Returns 0.
 */
अटल पूर्णांक _setup(काष्ठा omap_hwmod *oh, व्योम *data)
अणु
	अगर (oh->_state != _HWMOD_STATE_INITIALIZED)
		वापस 0;

	अगर (oh->parent_hwmod) अणु
		पूर्णांक r;

		r = _enable(oh->parent_hwmod);
		WARN(r, "hwmod: %s: setup: failed to enable parent hwmod %s\n",
		     oh->name, oh->parent_hwmod->name);
	पूर्ण

	_setup_iclk_स्वतःidle(oh);

	अगर (!_setup_reset(oh))
		_setup_postsetup(oh);

	अगर (oh->parent_hwmod) अणु
		u8 postsetup_state;

		postsetup_state = oh->parent_hwmod->_postsetup_state;

		अगर (postsetup_state == _HWMOD_STATE_IDLE)
			_idle(oh->parent_hwmod);
		अन्यथा अगर (postsetup_state == _HWMOD_STATE_DISABLED)
			_shutकरोwn(oh->parent_hwmod);
		अन्यथा अगर (postsetup_state != _HWMOD_STATE_ENABLED)
			WARN(1, "hwmod: %s: unknown postsetup state %d! defaulting to enabled\n",
			     oh->parent_hwmod->name, postsetup_state);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * _रेजिस्टर - रेजिस्टर a काष्ठा omap_hwmod
 * @oh: काष्ठा omap_hwmod *
 *
 * Registers the omap_hwmod @oh.  Returns -EEXIST अगर an omap_hwmod
 * alपढ़ोy has been रेजिस्टरed by the same name; -EINVAL अगर the
 * omap_hwmod is in the wrong state, अगर @oh is शून्य, अगर the
 * omap_hwmod's class field is शून्य; अगर the omap_hwmod is missing a
 * name, or अगर the omap_hwmod's class is missing a name; or 0 upon
 * success.
 *
 * XXX The data should be copied पूर्णांकo booपंचांगem, so the original data
 * should be marked __initdata and मुक्तd after init.  This would allow
 * unneeded omap_hwmods to be मुक्तd on multi-OMAP configurations.  Note
 * that the copy process would be relatively complex due to the large number
 * of subकाष्ठाures.
 */
अटल पूर्णांक _रेजिस्टर(काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh || !oh->name || !oh->class || !oh->class->name ||
	    (oh->_state != _HWMOD_STATE_UNKNOWN))
		वापस -EINVAL;

	pr_debug("omap_hwmod: %s: registering\n", oh->name);

	अगर (_lookup(oh->name))
		वापस -EEXIST;

	list_add_tail(&oh->node, &omap_hwmod_list);

	INIT_LIST_HEAD(&oh->slave_ports);
	spin_lock_init(&oh->_lock);
	lockdep_set_class(&oh->_lock, &oh->hwmod_key);

	oh->_state = _HWMOD_STATE_REGISTERED;

	/*
	 * XXX Rather than करोing a म_भेद(), this should test a flag
	 * set in the hwmod data, inserted by the स्वतःgenerator code.
	 */
	अगर (!म_भेद(oh->name, MPU_INITIATOR_NAME))
		mpu_oh = oh;

	वापस 0;
पूर्ण

/**
 * _add_link - add an पूर्णांकerconnect between two IP blocks
 * @oi: poपूर्णांकer to a काष्ठा omap_hwmod_ocp_अगर record
 *
 * Add काष्ठा omap_hwmod_link records connecting the slave IP block
 * specअगरied in @oi->slave to @oi.  This code is assumed to run beक्रमe
 * preemption or SMP has been enabled, thus aव्योमing the need क्रम
 * locking in this code.  Changes to this assumption will require
 * additional locking.  Returns 0.
 */
अटल पूर्णांक _add_link(काष्ठा omap_hwmod_ocp_अगर *oi)
अणु
	pr_debug("omap_hwmod: %s -> %s: adding link\n", oi->master->name,
		 oi->slave->name);

	list_add(&oi->node, &oi->slave->slave_ports);
	oi->slave->slaves_cnt++;

	वापस 0;
पूर्ण

/**
 * _रेजिस्टर_link - रेजिस्टर a काष्ठा omap_hwmod_ocp_अगर
 * @oi: काष्ठा omap_hwmod_ocp_अगर *
 *
 * Registers the omap_hwmod_ocp_अगर record @oi.  Returns -EEXIST अगर it
 * has alपढ़ोy been रेजिस्टरed; -EINVAL अगर @oi is शून्य or अगर the
 * record poपूर्णांकed to by @oi is missing required fields; or 0 upon
 * success.
 *
 * XXX The data should be copied पूर्णांकo booपंचांगem, so the original data
 * should be marked __initdata and मुक्तd after init.  This would allow
 * unneeded omap_hwmods to be मुक्तd on multi-OMAP configurations.
 */
अटल पूर्णांक __init _रेजिस्टर_link(काष्ठा omap_hwmod_ocp_अगर *oi)
अणु
	अगर (!oi || !oi->master || !oi->slave || !oi->user)
		वापस -EINVAL;

	अगर (oi->_पूर्णांक_flags & _OCPIF_INT_FLAGS_REGISTERED)
		वापस -EEXIST;

	pr_debug("omap_hwmod: registering link from %s to %s\n",
		 oi->master->name, oi->slave->name);

	/*
	 * Register the connected hwmods, अगर they haven't been
	 * रेजिस्टरed alपढ़ोy
	 */
	अगर (oi->master->_state != _HWMOD_STATE_REGISTERED)
		_रेजिस्टर(oi->master);

	अगर (oi->slave->_state != _HWMOD_STATE_REGISTERED)
		_रेजिस्टर(oi->slave);

	_add_link(oi);

	oi->_पूर्णांक_flags |= _OCPIF_INT_FLAGS_REGISTERED;

	वापस 0;
पूर्ण

/* Static functions पूर्णांकended only क्रम use in soc_ops field function poपूर्णांकers */

/**
 * _omap2xxx_3xxx_रुको_target_पढ़ोy - रुको क्रम a module to leave slave idle
 * @oh: काष्ठा omap_hwmod *
 *
 * Wait क्रम a module @oh to leave slave idle.  Returns 0 अगर the module
 * करोes not have an IDLEST bit or अगर the module successfully leaves
 * slave idle; otherwise, pass aदीर्घ the वापस value of the
 * appropriate *_cm*_रुको_module_पढ़ोy() function.
 */
अटल पूर्णांक _omap2xxx_3xxx_रुको_target_पढ़ोy(काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh)
		वापस -EINVAL;

	अगर (oh->flags & HWMOD_NO_IDLEST)
		वापस 0;

	अगर (!_find_mpu_rt_port(oh))
		वापस 0;

	/* XXX check module SIDLEMODE, hardreset status, enabled घड़ीs */

	वापस omap_cm_रुको_module_पढ़ोy(0, oh->prcm.omap2.module_offs,
					 oh->prcm.omap2.idlest_reg_id,
					 oh->prcm.omap2.idlest_idle_bit);
पूर्ण

/**
 * _omap4_रुको_target_पढ़ोy - रुको क्रम a module to leave slave idle
 * @oh: काष्ठा omap_hwmod *
 *
 * Wait क्रम a module @oh to leave slave idle.  Returns 0 अगर the module
 * करोes not have an IDLEST bit or अगर the module successfully leaves
 * slave idle; otherwise, pass aदीर्घ the वापस value of the
 * appropriate *_cm*_रुको_module_पढ़ोy() function.
 */
अटल पूर्णांक _omap4_रुको_target_पढ़ोy(काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh)
		वापस -EINVAL;

	अगर (oh->flags & HWMOD_NO_IDLEST || !oh->clkdm)
		वापस 0;

	अगर (!_find_mpu_rt_port(oh))
		वापस 0;

	अगर (_omap4_clkctrl_managed_by_clkfwk(oh))
		वापस 0;

	अगर (!_omap4_has_clkctrl_घड़ी(oh))
		वापस 0;

	/* XXX check module SIDLEMODE, hardreset status */

	वापस omap_cm_रुको_module_पढ़ोy(oh->clkdm->prcm_partition,
					 oh->clkdm->cm_inst,
					 oh->prcm.omap4.clkctrl_offs, 0);
पूर्ण

/**
 * _omap2_निश्चित_hardreset - call OMAP2 PRM hardreset fn with hwmod args
 * @oh: काष्ठा omap_hwmod * to निश्चित hardreset
 * @ohri: hardreset line data
 *
 * Call omap2_prm_निश्चित_hardreset() with parameters extracted from
 * the hwmod @oh and the hardreset line data @ohri.  Only पूर्णांकended क्रम
 * use as an soc_ops function poपूर्णांकer.  Passes aदीर्घ the वापस value
 * from omap2_prm_निश्चित_hardreset().  XXX This function is scheduled
 * क्रम removal when the PRM code is moved पूर्णांकo drivers/.
 */
अटल पूर्णांक _omap2_निश्चित_hardreset(काष्ठा omap_hwmod *oh,
				   काष्ठा omap_hwmod_rst_info *ohri)
अणु
	वापस omap_prm_निश्चित_hardreset(ohri->rst_shअगरt, 0,
					 oh->prcm.omap2.module_offs, 0);
पूर्ण

/**
 * _omap2_deनिश्चित_hardreset - call OMAP2 PRM hardreset fn with hwmod args
 * @oh: काष्ठा omap_hwmod * to deनिश्चित hardreset
 * @ohri: hardreset line data
 *
 * Call omap2_prm_deनिश्चित_hardreset() with parameters extracted from
 * the hwmod @oh and the hardreset line data @ohri.  Only पूर्णांकended क्रम
 * use as an soc_ops function poपूर्णांकer.  Passes aदीर्घ the वापस value
 * from omap2_prm_deनिश्चित_hardreset().  XXX This function is
 * scheduled क्रम removal when the PRM code is moved पूर्णांकo drivers/.
 */
अटल पूर्णांक _omap2_deनिश्चित_hardreset(काष्ठा omap_hwmod *oh,
				     काष्ठा omap_hwmod_rst_info *ohri)
अणु
	वापस omap_prm_deनिश्चित_hardreset(ohri->rst_shअगरt, ohri->st_shअगरt, 0,
					   oh->prcm.omap2.module_offs, 0, 0);
पूर्ण

/**
 * _omap2_is_hardreset_निश्चितed - call OMAP2 PRM hardreset fn with hwmod args
 * @oh: काष्ठा omap_hwmod * to test hardreset
 * @ohri: hardreset line data
 *
 * Call omap2_prm_is_hardreset_निश्चितed() with parameters extracted
 * from the hwmod @oh and the hardreset line data @ohri.  Only
 * पूर्णांकended क्रम use as an soc_ops function poपूर्णांकer.  Passes aदीर्घ the
 * वापस value from omap2_prm_is_hardreset_निश्चितed().  XXX This
 * function is scheduled क्रम removal when the PRM code is moved पूर्णांकo
 * drivers/.
 */
अटल पूर्णांक _omap2_is_hardreset_निश्चितed(काष्ठा omap_hwmod *oh,
					काष्ठा omap_hwmod_rst_info *ohri)
अणु
	वापस omap_prm_is_hardreset_निश्चितed(ohri->st_shअगरt, 0,
					      oh->prcm.omap2.module_offs, 0);
पूर्ण

/**
 * _omap4_निश्चित_hardreset - call OMAP4 PRM hardreset fn with hwmod args
 * @oh: काष्ठा omap_hwmod * to निश्चित hardreset
 * @ohri: hardreset line data
 *
 * Call omap4_prminst_निश्चित_hardreset() with parameters extracted
 * from the hwmod @oh and the hardreset line data @ohri.  Only
 * पूर्णांकended क्रम use as an soc_ops function poपूर्णांकer.  Passes aदीर्घ the
 * वापस value from omap4_prminst_निश्चित_hardreset().  XXX This
 * function is scheduled क्रम removal when the PRM code is moved पूर्णांकo
 * drivers/.
 */
अटल पूर्णांक _omap4_निश्चित_hardreset(काष्ठा omap_hwmod *oh,
				   काष्ठा omap_hwmod_rst_info *ohri)
अणु
	अगर (!oh->clkdm)
		वापस -EINVAL;

	वापस omap_prm_निश्चित_hardreset(ohri->rst_shअगरt,
					 oh->clkdm->pwrdm.ptr->prcm_partition,
					 oh->clkdm->pwrdm.ptr->prcm_offs,
					 oh->prcm.omap4.rstctrl_offs);
पूर्ण

/**
 * _omap4_deनिश्चित_hardreset - call OMAP4 PRM hardreset fn with hwmod args
 * @oh: काष्ठा omap_hwmod * to deनिश्चित hardreset
 * @ohri: hardreset line data
 *
 * Call omap4_prminst_deनिश्चित_hardreset() with parameters extracted
 * from the hwmod @oh and the hardreset line data @ohri.  Only
 * पूर्णांकended क्रम use as an soc_ops function poपूर्णांकer.  Passes aदीर्घ the
 * वापस value from omap4_prminst_deनिश्चित_hardreset().  XXX This
 * function is scheduled क्रम removal when the PRM code is moved पूर्णांकo
 * drivers/.
 */
अटल पूर्णांक _omap4_deनिश्चित_hardreset(काष्ठा omap_hwmod *oh,
				     काष्ठा omap_hwmod_rst_info *ohri)
अणु
	अगर (!oh->clkdm)
		वापस -EINVAL;

	अगर (ohri->st_shअगरt)
		pr_err("omap_hwmod: %s: %s: hwmod data error: OMAP4 does not support st_shift\n",
		       oh->name, ohri->name);
	वापस omap_prm_deनिश्चित_hardreset(ohri->rst_shअगरt, ohri->rst_shअगरt,
					   oh->clkdm->pwrdm.ptr->prcm_partition,
					   oh->clkdm->pwrdm.ptr->prcm_offs,
					   oh->prcm.omap4.rstctrl_offs,
					   oh->prcm.omap4.rstctrl_offs +
					   OMAP4_RST_CTRL_ST_OFFSET);
पूर्ण

/**
 * _omap4_is_hardreset_निश्चितed - call OMAP4 PRM hardreset fn with hwmod args
 * @oh: काष्ठा omap_hwmod * to test hardreset
 * @ohri: hardreset line data
 *
 * Call omap4_prminst_is_hardreset_निश्चितed() with parameters
 * extracted from the hwmod @oh and the hardreset line data @ohri.
 * Only पूर्णांकended क्रम use as an soc_ops function poपूर्णांकer.  Passes aदीर्घ
 * the वापस value from omap4_prminst_is_hardreset_निश्चितed().  XXX
 * This function is scheduled क्रम removal when the PRM code is moved
 * पूर्णांकo drivers/.
 */
अटल पूर्णांक _omap4_is_hardreset_निश्चितed(काष्ठा omap_hwmod *oh,
					काष्ठा omap_hwmod_rst_info *ohri)
अणु
	अगर (!oh->clkdm)
		वापस -EINVAL;

	वापस omap_prm_is_hardreset_निश्चितed(ohri->rst_shअगरt,
					      oh->clkdm->pwrdm.ptr->
					      prcm_partition,
					      oh->clkdm->pwrdm.ptr->prcm_offs,
					      oh->prcm.omap4.rstctrl_offs);
पूर्ण

/**
 * _omap4_disable_direct_prcm - disable direct PRCM control क्रम hwmod
 * @oh: काष्ठा omap_hwmod * to disable control क्रम
 *
 * Disables direct PRCM clkctrl करोne by hwmod core. Instead, the hwmod
 * will be using its मुख्य_clk to enable/disable the module. Returns
 * 0 अगर successful.
 */
अटल पूर्णांक _omap4_disable_direct_prcm(काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh)
		वापस -EINVAL;

	oh->prcm.omap4.flags |= HWMOD_OMAP4_CLKFWK_CLKCTR_CLOCK;

	वापस 0;
पूर्ण

/**
 * _am33xx_deनिश्चित_hardreset - call AM33XX PRM hardreset fn with hwmod args
 * @oh: काष्ठा omap_hwmod * to deनिश्चित hardreset
 * @ohri: hardreset line data
 *
 * Call am33xx_prminst_deनिश्चित_hardreset() with parameters extracted
 * from the hwmod @oh and the hardreset line data @ohri.  Only
 * पूर्णांकended क्रम use as an soc_ops function poपूर्णांकer.  Passes aदीर्घ the
 * वापस value from am33xx_prminst_deनिश्चित_hardreset().  XXX This
 * function is scheduled क्रम removal when the PRM code is moved पूर्णांकo
 * drivers/.
 */
अटल पूर्णांक _am33xx_deनिश्चित_hardreset(काष्ठा omap_hwmod *oh,
				     काष्ठा omap_hwmod_rst_info *ohri)
अणु
	वापस omap_prm_deनिश्चित_hardreset(ohri->rst_shअगरt, ohri->st_shअगरt,
					   oh->clkdm->pwrdm.ptr->prcm_partition,
					   oh->clkdm->pwrdm.ptr->prcm_offs,
					   oh->prcm.omap4.rstctrl_offs,
					   oh->prcm.omap4.rstst_offs);
पूर्ण

/* Public functions */

u32 omap_hwmod_पढ़ो(काष्ठा omap_hwmod *oh, u16 reg_offs)
अणु
	अगर (oh->flags & HWMOD_16BIT_REG)
		वापस पढ़ोw_relaxed(oh->_mpu_rt_va + reg_offs);
	अन्यथा
		वापस पढ़ोl_relaxed(oh->_mpu_rt_va + reg_offs);
पूर्ण

व्योम omap_hwmod_ग_लिखो(u32 v, काष्ठा omap_hwmod *oh, u16 reg_offs)
अणु
	अगर (oh->flags & HWMOD_16BIT_REG)
		ग_लिखोw_relaxed(v, oh->_mpu_rt_va + reg_offs);
	अन्यथा
		ग_लिखोl_relaxed(v, oh->_mpu_rt_va + reg_offs);
पूर्ण

/**
 * omap_hwmod_softreset - reset a module via SYSCONFIG.SOFTRESET bit
 * @oh: काष्ठा omap_hwmod *
 *
 * This is a खुला function exposed to drivers. Some drivers may need to करो
 * some settings beक्रमe and after resetting the device.  Those drivers after
 * करोing the necessary settings could use this function to start a reset by
 * setting the SYSCONFIG.SOFTRESET bit.
 */
पूर्णांक omap_hwmod_softreset(काष्ठा omap_hwmod *oh)
अणु
	u32 v;
	पूर्णांक ret;

	अगर (!oh || !(oh->_sysc_cache))
		वापस -EINVAL;

	v = oh->_sysc_cache;
	ret = _set_softreset(oh, &v);
	अगर (ret)
		जाओ error;
	_ग_लिखो_sysconfig(v, oh);

	ret = _clear_softreset(oh, &v);
	अगर (ret)
		जाओ error;
	_ग_लिखो_sysconfig(v, oh);

error:
	वापस ret;
पूर्ण

/**
 * omap_hwmod_lookup - look up a रेजिस्टरed omap_hwmod by name
 * @name: name of the omap_hwmod to look up
 *
 * Given a @name of an omap_hwmod, वापस a poपूर्णांकer to the रेजिस्टरed
 * काष्ठा omap_hwmod *, or शून्य upon error.
 */
काष्ठा omap_hwmod *omap_hwmod_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा omap_hwmod *oh;

	अगर (!name)
		वापस शून्य;

	oh = _lookup(name);

	वापस oh;
पूर्ण

/**
 * omap_hwmod_क्रम_each - call function क्रम each रेजिस्टरed omap_hwmod
 * @fn: poपूर्णांकer to a callback function
 * @data: व्योम * data to pass to callback function
 *
 * Call @fn क्रम each रेजिस्टरed omap_hwmod, passing @data to each
 * function.  @fn must वापस 0 क्रम success or any other value क्रम
 * failure.  If @fn वापसs non-zero, the iteration across omap_hwmods
 * will stop and the non-zero वापस value will be passed to the
 * caller of omap_hwmod_क्रम_each().  @fn is called with
 * omap_hwmod_क्रम_each() held.
 */
पूर्णांक omap_hwmod_क्रम_each(पूर्णांक (*fn)(काष्ठा omap_hwmod *oh, व्योम *data),
			व्योम *data)
अणु
	काष्ठा omap_hwmod *temp_oh;
	पूर्णांक ret = 0;

	अगर (!fn)
		वापस -EINVAL;

	list_क्रम_each_entry(temp_oh, &omap_hwmod_list, node) अणु
		ret = (*fn)(temp_oh, data);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * omap_hwmod_रेजिस्टर_links - रेजिस्टर an array of hwmod links
 * @ois: poपूर्णांकer to an array of omap_hwmod_ocp_अगर to रेजिस्टर
 *
 * Intended to be called early in boot beक्रमe the घड़ी framework is
 * initialized.  If @ois is not null, will रेजिस्टर all omap_hwmods
 * listed in @ois that are valid क्रम this chip.  Returns -EINVAL अगर
 * omap_hwmod_init() hasn't been called beक्रमe calling this function,
 * -ENOMEM अगर the link memory area can't be allocated, or 0 upon
 * success.
 */
पूर्णांक __init omap_hwmod_रेजिस्टर_links(काष्ठा omap_hwmod_ocp_अगर **ois)
अणु
	पूर्णांक r, i;

	अगर (!inited)
		वापस -EINVAL;

	अगर (!ois)
		वापस 0;

	अगर (ois[0] == शून्य) /* Empty list */
		वापस 0;

	i = 0;
	करो अणु
		r = _रेजिस्टर_link(ois[i]);
		WARN(r && r != -EEXIST,
		     "omap_hwmod: _register_link(%s -> %s) returned %d\n",
		     ois[i]->master->name, ois[i]->slave->name, r);
	पूर्ण जबतक (ois[++i]);

	वापस 0;
पूर्ण

/**
 * _ensure_mpu_hwmod_is_setup - ensure the MPU SS hwmod is init'ed and set up
 * @oh: poपूर्णांकer to the hwmod currently being set up (usually not the MPU)
 *
 * If the hwmod data corresponding to the MPU subप्रणाली IP block
 * hasn't been initialized and set up yet, करो so now.  This must be
 * करोne first since sleep dependencies may be added from other hwmods
 * to the MPU.  Intended to be called only by omap_hwmod_setup*().  No
 * वापस value.
 */
अटल व्योम __init _ensure_mpu_hwmod_is_setup(काष्ठा omap_hwmod *oh)
अणु
	अगर (!mpu_oh || mpu_oh->_state == _HWMOD_STATE_UNKNOWN)
		pr_err("omap_hwmod: %s: MPU initiator hwmod %s not yet registered\n",
		       __func__, MPU_INITIATOR_NAME);
	अन्यथा अगर (mpu_oh->_state == _HWMOD_STATE_REGISTERED && oh != mpu_oh)
		omap_hwmod_setup_one(MPU_INITIATOR_NAME);
पूर्ण

/**
 * omap_hwmod_setup_one - set up a single hwmod
 * @oh_name: स्थिर अक्षर * name of the alपढ़ोy-रेजिस्टरed hwmod to set up
 *
 * Initialize and set up a single hwmod.  Intended to be used क्रम a
 * small number of early devices, such as the समयr IP blocks used क्रम
 * the scheduler घड़ी.  Must be called after omap2_clk_init().
 * Resolves the काष्ठा clk names to काष्ठा clk poपूर्णांकers क्रम each
 * रेजिस्टरed omap_hwmod.  Also calls _setup() on each hwmod.  Returns
 * -EINVAL upon error or 0 upon success.
 */
पूर्णांक __init omap_hwmod_setup_one(स्थिर अक्षर *oh_name)
अणु
	काष्ठा omap_hwmod *oh;

	pr_debug("omap_hwmod: %s: %s\n", oh_name, __func__);

	oh = _lookup(oh_name);
	अगर (!oh) अणु
		WARN(1, "omap_hwmod: %s: hwmod not yet registered\n", oh_name);
		वापस -EINVAL;
	पूर्ण

	_ensure_mpu_hwmod_is_setup(oh);

	_init(oh, शून्य);
	_setup(oh, शून्य);

	वापस 0;
पूर्ण

अटल व्योम omap_hwmod_check_one(काष्ठा device *dev,
				 स्थिर अक्षर *name, s8 v1, u8 v2)
अणु
	अगर (v1 < 0)
		वापस;

	अगर (v1 != v2)
		dev_warn(dev, "%s %d != %d\n", name, v1, v2);
पूर्ण

/**
 * omap_hwmod_check_sysc - check sysc against platक्रमm sysc
 * @dev: काष्ठा device
 * @data: module data
 * @sysc_fields: new sysc configuration
 */
अटल पूर्णांक omap_hwmod_check_sysc(काष्ठा device *dev,
				 स्थिर काष्ठा ti_sysc_module_data *data,
				 काष्ठा sysc_regbits *sysc_fields)
अणु
	स्थिर काष्ठा sysc_regbits *regbits = data->cap->regbits;

	omap_hwmod_check_one(dev, "dmadisable_shift",
			     regbits->dmadisable_shअगरt,
			     sysc_fields->dmadisable_shअगरt);
	omap_hwmod_check_one(dev, "midle_shift",
			     regbits->midle_shअगरt,
			     sysc_fields->midle_shअगरt);
	omap_hwmod_check_one(dev, "sidle_shift",
			     regbits->sidle_shअगरt,
			     sysc_fields->sidle_shअगरt);
	omap_hwmod_check_one(dev, "clkact_shift",
			     regbits->clkact_shअगरt,
			     sysc_fields->clkact_shअगरt);
	omap_hwmod_check_one(dev, "enwkup_shift",
			     regbits->enwkup_shअगरt,
			     sysc_fields->enwkup_shअगरt);
	omap_hwmod_check_one(dev, "srst_shift",
			     regbits->srst_shअगरt,
			     sysc_fields->srst_shअगरt);
	omap_hwmod_check_one(dev, "autoidle_shift",
			     regbits->स्वतःidle_shअगरt,
			     sysc_fields->स्वतःidle_shअगरt);

	वापस 0;
पूर्ण

/**
 * omap_hwmod_init_regbits - init sysconfig specअगरic रेजिस्टर bits
 * @dev: काष्ठा device
 * @oh: module
 * @data: module data
 * @sysc_fields: new sysc configuration
 */
अटल पूर्णांक omap_hwmod_init_regbits(काष्ठा device *dev, काष्ठा omap_hwmod *oh,
				   स्थिर काष्ठा ti_sysc_module_data *data,
				   काष्ठा sysc_regbits **sysc_fields)
अणु
	चयन (data->cap->type) अणु
	हाल TI_SYSC_OMAP2:
	हाल TI_SYSC_OMAP2_TIMER:
		*sysc_fields = &omap_hwmod_sysc_type1;
		अवरोध;
	हाल TI_SYSC_OMAP3_SHAM:
		*sysc_fields = &omap3_sham_sysc_fields;
		अवरोध;
	हाल TI_SYSC_OMAP3_AES:
		*sysc_fields = &omap3xxx_aes_sysc_fields;
		अवरोध;
	हाल TI_SYSC_OMAP4:
	हाल TI_SYSC_OMAP4_TIMER:
		*sysc_fields = &omap_hwmod_sysc_type2;
		अवरोध;
	हाल TI_SYSC_OMAP4_SIMPLE:
		*sysc_fields = &omap_hwmod_sysc_type3;
		अवरोध;
	हाल TI_SYSC_OMAP34XX_SR:
		*sysc_fields = &omap34xx_sr_sysc_fields;
		अवरोध;
	हाल TI_SYSC_OMAP36XX_SR:
		*sysc_fields = &omap36xx_sr_sysc_fields;
		अवरोध;
	हाल TI_SYSC_OMAP4_SR:
		*sysc_fields = &omap36xx_sr_sysc_fields;
		अवरोध;
	हाल TI_SYSC_OMAP4_MCASP:
		*sysc_fields = &omap_hwmod_sysc_type_mcasp;
		अवरोध;
	हाल TI_SYSC_OMAP4_USB_HOST_FS:
		*sysc_fields = &omap_hwmod_sysc_type_usb_host_fs;
		अवरोध;
	शेष:
		*sysc_fields = शून्य;
		अगर (!oh->class->sysc->sysc_fields)
			वापस 0;

		dev_err(dev, "sysc_fields not found\n");

		वापस -EINVAL;
	पूर्ण

	वापस omap_hwmod_check_sysc(dev, data, *sysc_fields);
पूर्ण

/**
 * omap_hwmod_init_reg_offs - initialize sysconfig रेजिस्टर offsets
 * @dev: काष्ठा device
 * @data: module data
 * @rev_offs: revision रेजिस्टर offset
 * @sysc_offs: sysc रेजिस्टर offset
 * @syss_offs: syss रेजिस्टर offset
 */
अटल पूर्णांक omap_hwmod_init_reg_offs(काष्ठा device *dev,
				    स्थिर काष्ठा ti_sysc_module_data *data,
				    s32 *rev_offs, s32 *sysc_offs,
				    s32 *syss_offs)
अणु
	*rev_offs = -ENODEV;
	*sysc_offs = 0;
	*syss_offs = 0;

	अगर (data->offsets[SYSC_REVISION] >= 0)
		*rev_offs = data->offsets[SYSC_REVISION];

	अगर (data->offsets[SYSC_SYSCONFIG] >= 0)
		*sysc_offs = data->offsets[SYSC_SYSCONFIG];

	अगर (data->offsets[SYSC_SYSSTATUS] >= 0)
		*syss_offs = data->offsets[SYSC_SYSSTATUS];

	वापस 0;
पूर्ण

/**
 * omap_hwmod_init_sysc_flags - initialize sysconfig features
 * @dev: काष्ठा device
 * @data: module data
 * @sysc_flags: module configuration
 */
अटल पूर्णांक omap_hwmod_init_sysc_flags(काष्ठा device *dev,
				      स्थिर काष्ठा ti_sysc_module_data *data,
				      u32 *sysc_flags)
अणु
	*sysc_flags = 0;

	चयन (data->cap->type) अणु
	हाल TI_SYSC_OMAP2:
	हाल TI_SYSC_OMAP2_TIMER:
		/* See SYSC_OMAP2_* in include/dt-bindings/bus/ti-sysc.h */
		अगर (data->cfg->sysc_val & SYSC_OMAP2_CLOCKACTIVITY)
			*sysc_flags |= SYSC_HAS_CLOCKACTIVITY;
		अगर (data->cfg->sysc_val & SYSC_OMAP2_EMUFREE)
			*sysc_flags |= SYSC_HAS_EMUFREE;
		अगर (data->cfg->sysc_val & SYSC_OMAP2_ENAWAKEUP)
			*sysc_flags |= SYSC_HAS_ENAWAKEUP;
		अगर (data->cfg->sysc_val & SYSC_OMAP2_SOFTRESET)
			*sysc_flags |= SYSC_HAS_SOFTRESET;
		अगर (data->cfg->sysc_val & SYSC_OMAP2_AUTOIDLE)
			*sysc_flags |= SYSC_HAS_AUTOIDLE;
		अवरोध;
	हाल TI_SYSC_OMAP4:
	हाल TI_SYSC_OMAP4_TIMER:
		/* See SYSC_OMAP4_* in include/dt-bindings/bus/ti-sysc.h */
		अगर (data->cfg->sysc_val & SYSC_OMAP4_DMADISABLE)
			*sysc_flags |= SYSC_HAS_DMADISABLE;
		अगर (data->cfg->sysc_val & SYSC_OMAP4_FREEEMU)
			*sysc_flags |= SYSC_HAS_EMUFREE;
		अगर (data->cfg->sysc_val & SYSC_OMAP4_SOFTRESET)
			*sysc_flags |= SYSC_HAS_SOFTRESET;
		अवरोध;
	हाल TI_SYSC_OMAP34XX_SR:
	हाल TI_SYSC_OMAP36XX_SR:
		/* See SYSC_OMAP3_SR_* in include/dt-bindings/bus/ti-sysc.h */
		अगर (data->cfg->sysc_val & SYSC_OMAP3_SR_ENAWAKEUP)
			*sysc_flags |= SYSC_HAS_ENAWAKEUP;
		अवरोध;
	शेष:
		अगर (data->cap->regbits->emuमुक्त_shअगरt >= 0)
			*sysc_flags |= SYSC_HAS_EMUFREE;
		अगर (data->cap->regbits->enwkup_shअगरt >= 0)
			*sysc_flags |= SYSC_HAS_ENAWAKEUP;
		अगर (data->cap->regbits->srst_shअगरt >= 0)
			*sysc_flags |= SYSC_HAS_SOFTRESET;
		अगर (data->cap->regbits->स्वतःidle_shअगरt >= 0)
			*sysc_flags |= SYSC_HAS_AUTOIDLE;
		अवरोध;
	पूर्ण

	अगर (data->cap->regbits->midle_shअगरt >= 0 &&
	    data->cfg->midlemodes)
		*sysc_flags |= SYSC_HAS_MIDLEMODE;

	अगर (data->cap->regbits->sidle_shअगरt >= 0 &&
	    data->cfg->sidlemodes)
		*sysc_flags |= SYSC_HAS_SIDLEMODE;

	अगर (data->cfg->quirks & SYSC_QUIRK_UNCACHED)
		*sysc_flags |= SYSC_NO_CACHE;
	अगर (data->cfg->quirks & SYSC_QUIRK_RESET_STATUS)
		*sysc_flags |= SYSC_HAS_RESET_STATUS;

	अगर (data->cfg->syss_mask & 1)
		*sysc_flags |= SYSS_HAS_RESET_STATUS;

	वापस 0;
पूर्ण

/**
 * omap_hwmod_init_idlemodes - initialize module idle modes
 * @dev: काष्ठा device
 * @data: module data
 * @idlemodes: module supported idle modes
 */
अटल पूर्णांक omap_hwmod_init_idlemodes(काष्ठा device *dev,
				     स्थिर काष्ठा ti_sysc_module_data *data,
				     u32 *idlemodes)
अणु
	*idlemodes = 0;

	अगर (data->cfg->midlemodes & BIT(SYSC_IDLE_FORCE))
		*idlemodes |= MSTANDBY_FORCE;
	अगर (data->cfg->midlemodes & BIT(SYSC_IDLE_NO))
		*idlemodes |= MSTANDBY_NO;
	अगर (data->cfg->midlemodes & BIT(SYSC_IDLE_SMART))
		*idlemodes |= MSTANDBY_SMART;
	अगर (data->cfg->midlemodes & BIT(SYSC_IDLE_SMART_WKUP))
		*idlemodes |= MSTANDBY_SMART_WKUP;

	अगर (data->cfg->sidlemodes & BIT(SYSC_IDLE_FORCE))
		*idlemodes |= SIDLE_FORCE;
	अगर (data->cfg->sidlemodes & BIT(SYSC_IDLE_NO))
		*idlemodes |= SIDLE_NO;
	अगर (data->cfg->sidlemodes & BIT(SYSC_IDLE_SMART))
		*idlemodes |= SIDLE_SMART;
	अगर (data->cfg->sidlemodes & BIT(SYSC_IDLE_SMART_WKUP))
		*idlemodes |= SIDLE_SMART_WKUP;

	वापस 0;
पूर्ण

/**
 * omap_hwmod_check_module - check new module against platक्रमm data
 * @dev: काष्ठा device
 * @oh: module
 * @data: new module data
 * @sysc_fields: sysc रेजिस्टर bits
 * @rev_offs: revision रेजिस्टर offset
 * @sysc_offs: sysconfig रेजिस्टर offset
 * @syss_offs: sysstatus रेजिस्टर offset
 * @sysc_flags: sysc specअगरic flags
 * @idlemodes: sysc supported idlemodes
 */
अटल पूर्णांक omap_hwmod_check_module(काष्ठा device *dev,
				   काष्ठा omap_hwmod *oh,
				   स्थिर काष्ठा ti_sysc_module_data *data,
				   काष्ठा sysc_regbits *sysc_fields,
				   s32 rev_offs, s32 sysc_offs,
				   s32 syss_offs, u32 sysc_flags,
				   u32 idlemodes)
अणु
	अगर (!oh->class->sysc)
		वापस -ENODEV;

	अगर (oh->class->sysc->sysc_fields &&
	    sysc_fields != oh->class->sysc->sysc_fields)
		dev_warn(dev, "sysc_fields mismatch\n");

	अगर (rev_offs != oh->class->sysc->rev_offs)
		dev_warn(dev, "rev_offs %08x != %08x\n", rev_offs,
			 oh->class->sysc->rev_offs);
	अगर (sysc_offs != oh->class->sysc->sysc_offs)
		dev_warn(dev, "sysc_offs %08x != %08x\n", sysc_offs,
			 oh->class->sysc->sysc_offs);
	अगर (syss_offs != oh->class->sysc->syss_offs)
		dev_warn(dev, "syss_offs %08x != %08x\n", syss_offs,
			 oh->class->sysc->syss_offs);

	अगर (sysc_flags != oh->class->sysc->sysc_flags)
		dev_warn(dev, "sysc_flags %08x != %08x\n", sysc_flags,
			 oh->class->sysc->sysc_flags);

	अगर (idlemodes != oh->class->sysc->idlemodes)
		dev_warn(dev, "idlemodes %08x != %08x\n", idlemodes,
			 oh->class->sysc->idlemodes);

	अगर (data->cfg->srst_udelay != oh->class->sysc->srst_udelay)
		dev_warn(dev, "srst_udelay %i != %i\n",
			 data->cfg->srst_udelay,
			 oh->class->sysc->srst_udelay);

	वापस 0;
पूर्ण

/**
 * omap_hwmod_allocate_module - allocate new module
 * @dev: काष्ठा device
 * @oh: module
 * @sysc_fields: sysc रेजिस्टर bits
 * @घड़ीकरोमुख्य: घड़ीकरोमुख्य
 * @rev_offs: revision रेजिस्टर offset
 * @sysc_offs: sysconfig रेजिस्टर offset
 * @syss_offs: sysstatus रेजिस्टर offset
 * @sysc_flags: sysc specअगरic flags
 * @idlemodes: sysc supported idlemodes
 *
 * Note that the allocations here cannot use devm as ti-sysc can rebind.
 */
अटल पूर्णांक omap_hwmod_allocate_module(काष्ठा device *dev, काष्ठा omap_hwmod *oh,
				      स्थिर काष्ठा ti_sysc_module_data *data,
				      काष्ठा sysc_regbits *sysc_fields,
				      काष्ठा घड़ीकरोमुख्य *clkdm,
				      s32 rev_offs, s32 sysc_offs,
				      s32 syss_offs, u32 sysc_flags,
				      u32 idlemodes)
अणु
	काष्ठा omap_hwmod_class_sysconfig *sysc;
	काष्ठा omap_hwmod_class *class = शून्य;
	काष्ठा omap_hwmod_ocp_अगर *oi = शून्य;
	व्योम __iomem *regs = शून्य;
	अचिन्हित दीर्घ flags;

	sysc = kzalloc(माप(*sysc), GFP_KERNEL);
	अगर (!sysc)
		वापस -ENOMEM;

	sysc->sysc_fields = sysc_fields;
	sysc->rev_offs = rev_offs;
	sysc->sysc_offs = sysc_offs;
	sysc->syss_offs = syss_offs;
	sysc->sysc_flags = sysc_flags;
	sysc->idlemodes = idlemodes;
	sysc->srst_udelay = data->cfg->srst_udelay;

	अगर (!oh->_mpu_rt_va) अणु
		regs = ioremap(data->module_pa,
			       data->module_size);
		अगर (!regs)
			जाओ out_मुक्त_sysc;
	पूर्ण

	/*
	 * We may need a new oh->class as the other devices in the same class
	 * may not yet have ioremapped their रेजिस्टरs.
	 */
	अगर (oh->class->name && म_भेद(oh->class->name, data->name)) अणु
		class = kmemdup(oh->class, माप(*oh->class), GFP_KERNEL);
		अगर (!class)
			जाओ out_unmap;
	पूर्ण

	अगर (list_empty(&oh->slave_ports)) अणु
		oi = kसुस्मृति(1, माप(*oi), GFP_KERNEL);
		अगर (!oi)
			जाओ out_मुक्त_class;

		/*
		 * Note that we assume पूर्णांकerconnect पूर्णांकerface घड़ीs will be
		 * managed by the पूर्णांकerconnect driver क्रम OCPIF_SWSUP_IDLE हाल
		 * on omap24xx and omap3.
		 */
		oi->slave = oh;
		oi->user = OCP_USER_MPU | OCP_USER_SDMA;
	पूर्ण

	spin_lock_irqsave(&oh->_lock, flags);
	अगर (regs)
		oh->_mpu_rt_va = regs;
	अगर (class)
		oh->class = class;
	oh->class->sysc = sysc;
	अगर (oi)
		_add_link(oi);
	अगर (clkdm)
		oh->clkdm = clkdm;
	oh->_state = _HWMOD_STATE_INITIALIZED;
	oh->_postsetup_state = _HWMOD_STATE_DEFAULT;
	_setup(oh, शून्य);
	spin_unlock_irqrestore(&oh->_lock, flags);

	वापस 0;

out_मुक्त_class:
	kमुक्त(class);
out_unmap:
	iounmap(regs);
out_मुक्त_sysc:
	kमुक्त(sysc);
	वापस -ENOMEM;
पूर्ण

अटल स्थिर काष्ठा omap_hwmod_reset omap24xx_reset_quirks[] = अणु
	अणु .match = "msdi", .len = 4, .reset = omap_msdi_reset, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_hwmod_reset omap_reset_quirks[] = अणु
	अणु .match = "dss_core", .len = 8, .reset = omap_dss_reset, पूर्ण,
	अणु .match = "hdq1w", .len = 5, .reset = omap_hdq1w_reset, पूर्ण,
	अणु .match = "i2c", .len = 3, .reset = omap_i2c_reset, पूर्ण,
	अणु .match = "wd_timer", .len = 8, .reset = omap2_wd_समयr_reset, पूर्ण,
पूर्ण;

अटल व्योम
omap_hwmod_init_reset_quirk(काष्ठा device *dev, काष्ठा omap_hwmod *oh,
			    स्थिर काष्ठा ti_sysc_module_data *data,
			    स्थिर काष्ठा omap_hwmod_reset *quirks,
			    पूर्णांक quirks_sz)
अणु
	स्थिर काष्ठा omap_hwmod_reset *quirk;
	पूर्णांक i;

	क्रम (i = 0; i < quirks_sz; i++) अणु
		quirk = &quirks[i];
		अगर (!म_भेदन(data->name, quirk->match, quirk->len)) अणु
			oh->class->reset = quirk->reset;

			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
omap_hwmod_init_reset_quirks(काष्ठा device *dev, काष्ठा omap_hwmod *oh,
			     स्थिर काष्ठा ti_sysc_module_data *data)
अणु
	अगर (soc_is_omap24xx())
		omap_hwmod_init_reset_quirk(dev, oh, data,
					    omap24xx_reset_quirks,
					    ARRAY_SIZE(omap24xx_reset_quirks));

	omap_hwmod_init_reset_quirk(dev, oh, data, omap_reset_quirks,
				    ARRAY_SIZE(omap_reset_quirks));
पूर्ण

/**
 * omap_hwmod_init_module - initialize new module
 * @dev: काष्ठा device
 * @data: module data
 * @cookie: cookie क्रम the caller to use क्रम later calls
 */
पूर्णांक omap_hwmod_init_module(काष्ठा device *dev,
			   स्थिर काष्ठा ti_sysc_module_data *data,
			   काष्ठा ti_sysc_cookie *cookie)
अणु
	काष्ठा omap_hwmod *oh;
	काष्ठा sysc_regbits *sysc_fields;
	s32 rev_offs, sysc_offs, syss_offs;
	u32 sysc_flags, idlemodes;
	पूर्णांक error;

	अगर (!dev || !data || !data->name || !cookie)
		वापस -EINVAL;

	oh = _lookup(data->name);
	अगर (!oh) अणु
		oh = kzalloc(माप(*oh), GFP_KERNEL);
		अगर (!oh)
			वापस -ENOMEM;

		oh->name = data->name;
		oh->_state = _HWMOD_STATE_UNKNOWN;
		lockdep_रेजिस्टर_key(&oh->hwmod_key);

		/* Unused, can be handled by PRM driver handling resets */
		oh->prcm.omap4.flags = HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT;

		oh->class = kzalloc(माप(*oh->class), GFP_KERNEL);
		अगर (!oh->class) अणु
			kमुक्त(oh);
			वापस -ENOMEM;
		पूर्ण

		omap_hwmod_init_reset_quirks(dev, oh, data);

		oh->class->name = data->name;
		mutex_lock(&list_lock);
		error = _रेजिस्टर(oh);
		mutex_unlock(&list_lock);
	पूर्ण

	cookie->data = oh;

	error = omap_hwmod_init_regbits(dev, oh, data, &sysc_fields);
	अगर (error)
		वापस error;

	error = omap_hwmod_init_reg_offs(dev, data, &rev_offs,
					 &sysc_offs, &syss_offs);
	अगर (error)
		वापस error;

	error = omap_hwmod_init_sysc_flags(dev, data, &sysc_flags);
	अगर (error)
		वापस error;

	error = omap_hwmod_init_idlemodes(dev, data, &idlemodes);
	अगर (error)
		वापस error;

	अगर (data->cfg->quirks & SYSC_QUIRK_NO_IDLE)
		oh->flags |= HWMOD_NO_IDLE;
	अगर (data->cfg->quirks & SYSC_QUIRK_NO_IDLE_ON_INIT)
		oh->flags |= HWMOD_INIT_NO_IDLE;
	अगर (data->cfg->quirks & SYSC_QUIRK_NO_RESET_ON_INIT)
		oh->flags |= HWMOD_INIT_NO_RESET;
	अगर (data->cfg->quirks & SYSC_QUIRK_USE_CLOCKACT)
		oh->flags |= HWMOD_SET_DEFAULT_CLOCKACT;
	अगर (data->cfg->quirks & SYSC_QUIRK_SWSUP_SIDLE)
		oh->flags |= HWMOD_SWSUP_SIDLE;
	अगर (data->cfg->quirks & SYSC_QUIRK_SWSUP_SIDLE_ACT)
		oh->flags |= HWMOD_SWSUP_SIDLE_ACT;
	अगर (data->cfg->quirks & SYSC_QUIRK_SWSUP_MSTANDBY)
		oh->flags |= HWMOD_SWSUP_MSTANDBY;

	error = omap_hwmod_check_module(dev, oh, data, sysc_fields,
					rev_offs, sysc_offs, syss_offs,
					sysc_flags, idlemodes);
	अगर (!error)
		वापस error;

	वापस omap_hwmod_allocate_module(dev, oh, data, sysc_fields,
					  cookie->clkdm, rev_offs,
					  sysc_offs, syss_offs,
					  sysc_flags, idlemodes);
पूर्ण

/**
 * omap_hwmod_setup_earlycon_flags - set up flags क्रम early console
 *
 * Enable DEBUG_OMAPUART_FLAGS क्रम uart hwmod that is being used as
 * early concole so that hwmod core करोesn't reset and keep it in idle
 * that specअगरic uart.
 */
#अगर_घोषित CONFIG_SERIAL_EARLYCON
अटल व्योम __init omap_hwmod_setup_earlycon_flags(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा omap_hwmod *oh;
	स्थिर अक्षर *uart;

	np = of_find_node_by_path("/chosen");
	अगर (np) अणु
		uart = of_get_property(np, "stdout-path", शून्य);
		अगर (uart) अणु
			np = of_find_node_by_path(uart);
			अगर (np) अणु
				uart = of_get_property(np, "ti,hwmods", शून्य);
				oh = omap_hwmod_lookup(uart);
				अगर (!oh) अणु
					uart = of_get_property(np->parent,
							       "ti,hwmods",
							       शून्य);
					oh = omap_hwmod_lookup(uart);
				पूर्ण
				अगर (oh)
					oh->flags |= DEBUG_OMAPUART_FLAGS;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 * omap_hwmod_setup_all - set up all रेजिस्टरed IP blocks
 *
 * Initialize and set up all IP blocks रेजिस्टरed with the hwmod code.
 * Must be called after omap2_clk_init().  Resolves the काष्ठा clk
 * names to काष्ठा clk poपूर्णांकers क्रम each रेजिस्टरed omap_hwmod.  Also
 * calls _setup() on each hwmod.  Returns 0 upon success.
 */
अटल पूर्णांक __init omap_hwmod_setup_all(व्योम)
अणु
	अगर (!inited)
		वापस 0;

	_ensure_mpu_hwmod_is_setup(शून्य);

	omap_hwmod_क्रम_each(_init, शून्य);
#अगर_घोषित CONFIG_SERIAL_EARLYCON
	omap_hwmod_setup_earlycon_flags();
#पूर्ण_अगर
	omap_hwmod_क्रम_each(_setup, शून्य);

	वापस 0;
पूर्ण
omap_postcore_initcall(omap_hwmod_setup_all);

/**
 * omap_hwmod_enable - enable an omap_hwmod
 * @oh: काष्ठा omap_hwmod *
 *
 * Enable an omap_hwmod @oh.  Intended to be called by omap_device_enable().
 * Returns -EINVAL on error or passes aदीर्घ the वापस value from _enable().
 */
पूर्णांक omap_hwmod_enable(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ flags;

	अगर (!oh)
		वापस -EINVAL;

	spin_lock_irqsave(&oh->_lock, flags);
	r = _enable(oh);
	spin_unlock_irqrestore(&oh->_lock, flags);

	वापस r;
पूर्ण

/**
 * omap_hwmod_idle - idle an omap_hwmod
 * @oh: काष्ठा omap_hwmod *
 *
 * Idle an omap_hwmod @oh.  Intended to be called by omap_device_idle().
 * Returns -EINVAL on error or passes aदीर्घ the वापस value from _idle().
 */
पूर्णांक omap_hwmod_idle(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ flags;

	अगर (!oh)
		वापस -EINVAL;

	spin_lock_irqsave(&oh->_lock, flags);
	r = _idle(oh);
	spin_unlock_irqrestore(&oh->_lock, flags);

	वापस r;
पूर्ण

/**
 * omap_hwmod_shutकरोwn - shutकरोwn an omap_hwmod
 * @oh: काष्ठा omap_hwmod *
 *
 * Shutकरोwn an omap_hwmod @oh.  Intended to be called by
 * omap_device_shutकरोwn().  Returns -EINVAL on error or passes aदीर्घ
 * the वापस value from _shutकरोwn().
 */
पूर्णांक omap_hwmod_shutकरोwn(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ flags;

	अगर (!oh)
		वापस -EINVAL;

	spin_lock_irqsave(&oh->_lock, flags);
	r = _shutकरोwn(oh);
	spin_unlock_irqrestore(&oh->_lock, flags);

	वापस r;
पूर्ण

/*
 * IP block data retrieval functions
 */

/**
 * omap_hwmod_get_pwrdm - वापस poपूर्णांकer to this module's मुख्य घातerकरोमुख्य
 * @oh: काष्ठा omap_hwmod *
 *
 * Return the घातerकरोमुख्य poपूर्णांकer associated with the OMAP module
 * @oh's मुख्य घड़ी.  If @oh करोes not have a मुख्य clk, वापस the
 * घातerकरोमुख्य associated with the पूर्णांकerface घड़ी associated with the
 * module's MPU port. (XXX Perhaps this should use the SDMA port
 * instead?)  Returns शून्य on error, or a काष्ठा घातerकरोमुख्य * on
 * success.
 */
काष्ठा घातerकरोमुख्य *omap_hwmod_get_pwrdm(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा clk *c;
	काष्ठा omap_hwmod_ocp_अगर *oi;
	काष्ठा घड़ीकरोमुख्य *clkdm;
	काष्ठा clk_hw_omap *clk;

	अगर (!oh)
		वापस शून्य;

	अगर (oh->clkdm)
		वापस oh->clkdm->pwrdm.ptr;

	अगर (oh->_clk) अणु
		c = oh->_clk;
	पूर्ण अन्यथा अणु
		oi = _find_mpu_rt_port(oh);
		अगर (!oi)
			वापस शून्य;
		c = oi->_clk;
	पूर्ण

	clk = to_clk_hw_omap(__clk_get_hw(c));
	clkdm = clk->clkdm;
	अगर (!clkdm)
		वापस शून्य;

	वापस clkdm->pwrdm.ptr;
पूर्ण

/**
 * omap_hwmod_get_mpu_rt_va - वापस the module's base address (क्रम the MPU)
 * @oh: काष्ठा omap_hwmod *
 *
 * Returns the भव address corresponding to the beginning of the
 * module's रेजिस्टर target, in the address range that is पूर्णांकended to
 * be used by the MPU.  Returns the भव address upon success or शून्य
 * upon error.
 */
व्योम __iomem *omap_hwmod_get_mpu_rt_va(काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh)
		वापस शून्य;

	अगर (oh->_पूर्णांक_flags & _HWMOD_NO_MPU_PORT)
		वापस शून्य;

	अगर (oh->_state == _HWMOD_STATE_UNKNOWN)
		वापस शून्य;

	वापस oh->_mpu_rt_va;
पूर्ण

/*
 * XXX what about functions क्रम drivers to save/restore ocp_sysconfig
 * क्रम context save/restore operations?
 */

/**
 * omap_hwmod_निश्चित_hardreset - निश्चित the HW reset line of submodules
 * contained in the hwmod module.
 * @oh: काष्ठा omap_hwmod *
 * @name: name of the reset line to lookup and निश्चित
 *
 * Some IP like dsp, ipu or iva contain processor that require
 * an HW reset line to be निश्चित / deनिश्चित in order to enable fully
 * the IP.  Returns -EINVAL अगर @oh is null or अगर the operation is not
 * yet supported on this OMAP; otherwise, passes aदीर्घ the वापस value
 * from _निश्चित_hardreset().
 */
पूर्णांक omap_hwmod_निश्चित_hardreset(काष्ठा omap_hwmod *oh, स्थिर अक्षर *name)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (!oh)
		वापस -EINVAL;

	spin_lock_irqsave(&oh->_lock, flags);
	ret = _निश्चित_hardreset(oh, name);
	spin_unlock_irqrestore(&oh->_lock, flags);

	वापस ret;
पूर्ण

/**
 * omap_hwmod_deनिश्चित_hardreset - deनिश्चित the HW reset line of submodules
 * contained in the hwmod module.
 * @oh: काष्ठा omap_hwmod *
 * @name: name of the reset line to look up and deनिश्चित
 *
 * Some IP like dsp, ipu or iva contain processor that require
 * an HW reset line to be निश्चित / deनिश्चित in order to enable fully
 * the IP.  Returns -EINVAL अगर @oh is null or अगर the operation is not
 * yet supported on this OMAP; otherwise, passes aदीर्घ the वापस value
 * from _deनिश्चित_hardreset().
 */
पूर्णांक omap_hwmod_deनिश्चित_hardreset(काष्ठा omap_hwmod *oh, स्थिर अक्षर *name)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (!oh)
		वापस -EINVAL;

	spin_lock_irqsave(&oh->_lock, flags);
	ret = _deनिश्चित_hardreset(oh, name);
	spin_unlock_irqrestore(&oh->_lock, flags);

	वापस ret;
पूर्ण

/**
 * omap_hwmod_क्रम_each_by_class - call @fn क्रम each hwmod of class @classname
 * @classname: काष्ठा omap_hwmod_class name to search क्रम
 * @fn: callback function poपूर्णांकer to call क्रम each hwmod in class @classname
 * @user: arbitrary context data to pass to the callback function
 *
 * For each omap_hwmod of class @classname, call @fn.
 * If the callback function वापसs something other than
 * zero, the iterator is terminated, and the callback function's वापस
 * value is passed back to the caller.  Returns 0 upon success, -EINVAL
 * अगर @classname or @fn are शून्य, or passes back the error code from @fn.
 */
पूर्णांक omap_hwmod_क्रम_each_by_class(स्थिर अक्षर *classname,
				 पूर्णांक (*fn)(काष्ठा omap_hwmod *oh,
					   व्योम *user),
				 व्योम *user)
अणु
	काष्ठा omap_hwmod *temp_oh;
	पूर्णांक ret = 0;

	अगर (!classname || !fn)
		वापस -EINVAL;

	pr_debug("omap_hwmod: %s: looking for modules of class %s\n",
		 __func__, classname);

	list_क्रम_each_entry(temp_oh, &omap_hwmod_list, node) अणु
		अगर (!म_भेद(temp_oh->class->name, classname)) अणु
			pr_debug("omap_hwmod: %s: %s: calling callback fn\n",
				 __func__, temp_oh->name);
			ret = (*fn)(temp_oh, user);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		pr_debug("omap_hwmod: %s: iterator terminated early: %d\n",
			 __func__, ret);

	वापस ret;
पूर्ण

/**
 * omap_hwmod_set_postsetup_state - set the post-_setup() state क्रम this hwmod
 * @oh: काष्ठा omap_hwmod *
 * @state: state that _setup() should leave the hwmod in
 *
 * Sets the hwmod state that @oh will enter at the end of _setup()
 * (called by omap_hwmod_setup_*()).  See also the करोcumentation
 * क्रम _setup_postsetup(), above.  Returns 0 upon success or
 * -EINVAL अगर there is a problem with the arguments or अगर the hwmod is
 * in the wrong state.
 */
पूर्णांक omap_hwmod_set_postsetup_state(काष्ठा omap_hwmod *oh, u8 state)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (!oh)
		वापस -EINVAL;

	अगर (state != _HWMOD_STATE_DISABLED &&
	    state != _HWMOD_STATE_ENABLED &&
	    state != _HWMOD_STATE_IDLE)
		वापस -EINVAL;

	spin_lock_irqsave(&oh->_lock, flags);

	अगर (oh->_state != _HWMOD_STATE_REGISTERED) अणु
		ret = -EINVAL;
		जाओ ohsps_unlock;
	पूर्ण

	oh->_postsetup_state = state;
	ret = 0;

ohsps_unlock:
	spin_unlock_irqrestore(&oh->_lock, flags);

	वापस ret;
पूर्ण

/**
 * omap_hwmod_get_context_loss_count - get lost context count
 * @oh: काष्ठा omap_hwmod *
 *
 * Returns the context loss count of associated @oh
 * upon success, or zero अगर no context loss data is available.
 *
 * On OMAP4, this queries the per-hwmod context loss रेजिस्टर,
 * assuming one exists.  If not, or on OMAP2/3, this queries the
 * enclosing घातerकरोमुख्य context loss count.
 */
पूर्णांक omap_hwmod_get_context_loss_count(काष्ठा omap_hwmod *oh)
अणु
	काष्ठा घातerकरोमुख्य *pwrdm;
	पूर्णांक ret = 0;

	अगर (soc_ops.get_context_lost)
		वापस soc_ops.get_context_lost(oh);

	pwrdm = omap_hwmod_get_pwrdm(oh);
	अगर (pwrdm)
		ret = pwrdm_get_context_loss_count(pwrdm);

	वापस ret;
पूर्ण

/**
 * omap_hwmod_init - initialize the hwmod code
 *
 * Sets up some function poपूर्णांकers needed by the hwmod code to operate on the
 * currently-booted SoC.  Intended to be called once during kernel init
 * beक्रमe any hwmods are रेजिस्टरed.  No वापस value.
 */
व्योम __init omap_hwmod_init(व्योम)
अणु
	अगर (cpu_is_omap24xx()) अणु
		soc_ops.रुको_target_पढ़ोy = _omap2xxx_3xxx_रुको_target_पढ़ोy;
		soc_ops.निश्चित_hardreset = _omap2_निश्चित_hardreset;
		soc_ops.deनिश्चित_hardreset = _omap2_deनिश्चित_hardreset;
		soc_ops.is_hardreset_निश्चितed = _omap2_is_hardreset_निश्चितed;
	पूर्ण अन्यथा अगर (cpu_is_omap34xx()) अणु
		soc_ops.रुको_target_पढ़ोy = _omap2xxx_3xxx_रुको_target_पढ़ोy;
		soc_ops.निश्चित_hardreset = _omap2_निश्चित_hardreset;
		soc_ops.deनिश्चित_hardreset = _omap2_deनिश्चित_hardreset;
		soc_ops.is_hardreset_निश्चितed = _omap2_is_hardreset_निश्चितed;
		soc_ops.init_clkdm = _init_clkdm;
	पूर्ण अन्यथा अगर (cpu_is_omap44xx() || soc_is_omap54xx() || soc_is_dra7xx()) अणु
		soc_ops.enable_module = _omap4_enable_module;
		soc_ops.disable_module = _omap4_disable_module;
		soc_ops.रुको_target_पढ़ोy = _omap4_रुको_target_पढ़ोy;
		soc_ops.निश्चित_hardreset = _omap4_निश्चित_hardreset;
		soc_ops.deनिश्चित_hardreset = _omap4_deनिश्चित_hardreset;
		soc_ops.is_hardreset_निश्चितed = _omap4_is_hardreset_निश्चितed;
		soc_ops.init_clkdm = _init_clkdm;
		soc_ops.update_context_lost = _omap4_update_context_lost;
		soc_ops.get_context_lost = _omap4_get_context_lost;
		soc_ops.disable_direct_prcm = _omap4_disable_direct_prcm;
		soc_ops.xlate_clkctrl = _omap4_xlate_clkctrl;
	पूर्ण अन्यथा अगर (cpu_is_ti814x() || cpu_is_ti816x() || soc_is_am33xx() ||
		   soc_is_am43xx()) अणु
		soc_ops.enable_module = _omap4_enable_module;
		soc_ops.disable_module = _omap4_disable_module;
		soc_ops.रुको_target_पढ़ोy = _omap4_रुको_target_पढ़ोy;
		soc_ops.निश्चित_hardreset = _omap4_निश्चित_hardreset;
		soc_ops.deनिश्चित_hardreset = _am33xx_deनिश्चित_hardreset;
		soc_ops.is_hardreset_निश्चितed = _omap4_is_hardreset_निश्चितed;
		soc_ops.init_clkdm = _init_clkdm;
		soc_ops.disable_direct_prcm = _omap4_disable_direct_prcm;
		soc_ops.xlate_clkctrl = _omap4_xlate_clkctrl;
	पूर्ण अन्यथा अणु
		WARN(1, "omap_hwmod: unknown SoC type\n");
	पूर्ण

	_init_clkctrl_providers();

	inited = true;
पूर्ण

/**
 * omap_hwmod_get_मुख्य_clk - get poपूर्णांकer to मुख्य घड़ी name
 * @oh: काष्ठा omap_hwmod *
 *
 * Returns the मुख्य घड़ी name assocated with @oh upon success,
 * or शून्य अगर @oh is शून्य.
 */
स्थिर अक्षर *omap_hwmod_get_मुख्य_clk(काष्ठा omap_hwmod *oh)
अणु
	अगर (!oh)
		वापस शून्य;

	वापस oh->मुख्य_clk;
पूर्ण
