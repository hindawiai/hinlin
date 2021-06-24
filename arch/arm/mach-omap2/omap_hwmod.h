<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap_hwmod macros, काष्ठाures
 *
 * Copyright (C) 2009-2011 Nokia Corporation
 * Copyright (C) 2011-2012 Texas Instruments, Inc.
 * Paul Walmsley
 *
 * Created in collaboration with (alphabetical order): Benoथऍt Cousson,
 * Kevin Hilman, Tony Lindgren, Rajendra Nayak, Vikram Pandita, Sakari
 * Poussa, Anand Sawant, Santosh Shilimkar, Riअक्षरd Woodruff
 *
 * These headers and macros are used to define OMAP on-chip module
 * data and their पूर्णांकegration with other OMAP modules and Linux.
 * Copious करोcumentation and references can also be found in the
 * omap_hwmod code, in arch/arm/mach-omap2/omap_hwmod.c (as of this
 * writing).
 *
 * To करो:
 * - add पूर्णांकerconnect error log काष्ठाures
 * - init_conn_id_bit (CONNID_BIT_VECTOR)
 * - implement शेष hwmod SMS/SDRC flags?
 * - move Linux-specअगरic data ("non-ROM data") out
 */
#अगर_अघोषित __ARCH_ARM_PLAT_OMAP_INCLUDE_MACH_OMAP_HWMOD_H
#घोषणा __ARCH_ARM_PLAT_OMAP_INCLUDE_MACH_OMAP_HWMOD_H

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/ioport.h>
#समावेश <linux/spinlock.h>

काष्ठा omap_device;

बाह्य काष्ठा sysc_regbits omap_hwmod_sysc_type1;
बाह्य काष्ठा sysc_regbits omap_hwmod_sysc_type2;
बाह्य काष्ठा sysc_regbits omap_hwmod_sysc_type3;
बाह्य काष्ठा sysc_regbits omap34xx_sr_sysc_fields;
बाह्य काष्ठा sysc_regbits omap36xx_sr_sysc_fields;
बाह्य काष्ठा sysc_regbits omap3_sham_sysc_fields;
बाह्य काष्ठा sysc_regbits omap3xxx_aes_sysc_fields;
बाह्य काष्ठा sysc_regbits omap_hwmod_sysc_type_mcasp;
बाह्य काष्ठा sysc_regbits omap_hwmod_sysc_type_usb_host_fs;

/*
 * OCP SYSCONFIG bit shअगरts/masks TYPE1. These are क्रम IPs compliant
 * with the original PRCM protocol defined क्रम OMAP2420
 */
#घोषणा SYSC_TYPE1_MIDLEMODE_SHIFT	12
#घोषणा SYSC_TYPE1_MIDLEMODE_MASK	(0x3 << SYSC_TYPE1_MIDLEMODE_SHIFT)
#घोषणा SYSC_TYPE1_CLOCKACTIVITY_SHIFT	8
#घोषणा SYSC_TYPE1_CLOCKACTIVITY_MASK	(0x3 << SYSC_TYPE1_CLOCKACTIVITY_SHIFT)
#घोषणा SYSC_TYPE1_SIDLEMODE_SHIFT	3
#घोषणा SYSC_TYPE1_SIDLEMODE_MASK	(0x3 << SYSC_TYPE1_SIDLEMODE_SHIFT)
#घोषणा SYSC_TYPE1_ENAWAKEUP_SHIFT	2
#घोषणा SYSC_TYPE1_ENAWAKEUP_MASK	(1 << SYSC_TYPE1_ENAWAKEUP_SHIFT)
#घोषणा SYSC_TYPE1_SOFTRESET_SHIFT	1
#घोषणा SYSC_TYPE1_SOFTRESET_MASK	(1 << SYSC_TYPE1_SOFTRESET_SHIFT)
#घोषणा SYSC_TYPE1_AUTOIDLE_SHIFT	0
#घोषणा SYSC_TYPE1_AUTOIDLE_MASK	(1 << SYSC_TYPE1_AUTOIDLE_SHIFT)

/*
 * OCP SYSCONFIG bit shअगरts/masks TYPE2. These are क्रम IPs compliant
 * with the new PRCM protocol defined क्रम new OMAP4 IPs.
 */
#घोषणा SYSC_TYPE2_SOFTRESET_SHIFT	0
#घोषणा SYSC_TYPE2_SOFTRESET_MASK	(1 << SYSC_TYPE2_SOFTRESET_SHIFT)
#घोषणा SYSC_TYPE2_SIDLEMODE_SHIFT	2
#घोषणा SYSC_TYPE2_SIDLEMODE_MASK	(0x3 << SYSC_TYPE2_SIDLEMODE_SHIFT)
#घोषणा SYSC_TYPE2_MIDLEMODE_SHIFT	4
#घोषणा SYSC_TYPE2_MIDLEMODE_MASK	(0x3 << SYSC_TYPE2_MIDLEMODE_SHIFT)
#घोषणा SYSC_TYPE2_DMADISABLE_SHIFT	16
#घोषणा SYSC_TYPE2_DMADISABLE_MASK	(0x1 << SYSC_TYPE2_DMADISABLE_SHIFT)

/*
 * OCP SYSCONFIG bit shअगरts/masks TYPE3.
 * This is applicable क्रम some IPs present in AM33XX
 */
#घोषणा SYSC_TYPE3_SIDLEMODE_SHIFT	0
#घोषणा SYSC_TYPE3_SIDLEMODE_MASK	(0x3 << SYSC_TYPE3_SIDLEMODE_SHIFT)
#घोषणा SYSC_TYPE3_MIDLEMODE_SHIFT	2
#घोषणा SYSC_TYPE3_MIDLEMODE_MASK	(0x3 << SYSC_TYPE3_MIDLEMODE_SHIFT)

/* OCP SYSSTATUS bit shअगरts/masks */
#घोषणा SYSS_RESETDONE_SHIFT		0
#घोषणा SYSS_RESETDONE_MASK		(1 << SYSS_RESETDONE_SHIFT)

/* Master standby/slave idle mode flags */
#घोषणा HWMOD_IDLEMODE_FORCE		(1 << 0)
#घोषणा HWMOD_IDLEMODE_NO		(1 << 1)
#घोषणा HWMOD_IDLEMODE_SMART		(1 << 2)
#घोषणा HWMOD_IDLEMODE_SMART_WKUP	(1 << 3)

/* modulemode control type (SW or HW) */
#घोषणा MODULEMODE_HWCTRL		1
#घोषणा MODULEMODE_SWCTRL		2

#घोषणा DEBUG_OMAP2UART1_FLAGS	0
#घोषणा DEBUG_OMAP2UART2_FLAGS	0
#घोषणा DEBUG_OMAP2UART3_FLAGS	0
#घोषणा DEBUG_OMAP3UART3_FLAGS	0
#घोषणा DEBUG_OMAP3UART4_FLAGS	0
#घोषणा DEBUG_OMAP4UART3_FLAGS	0
#घोषणा DEBUG_OMAP4UART4_FLAGS	0
#घोषणा DEBUG_TI81XXUART1_FLAGS	0
#घोषणा DEBUG_TI81XXUART2_FLAGS	0
#घोषणा DEBUG_TI81XXUART3_FLAGS	0
#घोषणा DEBUG_AM33XXUART1_FLAGS	0

#घोषणा DEBUG_OMAPUART_FLAGS	(HWMOD_INIT_NO_IDLE | HWMOD_INIT_NO_RESET)

#अगर_घोषित CONFIG_OMAP_GPMC_DEBUG
#घोषणा DEBUG_OMAP_GPMC_HWMOD_FLAGS	HWMOD_INIT_NO_RESET
#अन्यथा
#घोषणा DEBUG_OMAP_GPMC_HWMOD_FLAGS	0
#पूर्ण_अगर

#अगर defined(CONFIG_DEBUG_OMAP2UART1)
#अघोषित DEBUG_OMAP2UART1_FLAGS
#घोषणा DEBUG_OMAP2UART1_FLAGS DEBUG_OMAPUART_FLAGS
#या_अगर defined(CONFIG_DEBUG_OMAP2UART2)
#अघोषित DEBUG_OMAP2UART2_FLAGS
#घोषणा DEBUG_OMAP2UART2_FLAGS DEBUG_OMAPUART_FLAGS
#या_अगर defined(CONFIG_DEBUG_OMAP2UART3)
#अघोषित DEBUG_OMAP2UART3_FLAGS
#घोषणा DEBUG_OMAP2UART3_FLAGS DEBUG_OMAPUART_FLAGS
#या_अगर defined(CONFIG_DEBUG_OMAP3UART3)
#अघोषित DEBUG_OMAP3UART3_FLAGS
#घोषणा DEBUG_OMAP3UART3_FLAGS DEBUG_OMAPUART_FLAGS
#या_अगर defined(CONFIG_DEBUG_OMAP3UART4)
#अघोषित DEBUG_OMAP3UART4_FLAGS
#घोषणा DEBUG_OMAP3UART4_FLAGS DEBUG_OMAPUART_FLAGS
#या_अगर defined(CONFIG_DEBUG_OMAP4UART3)
#अघोषित DEBUG_OMAP4UART3_FLAGS
#घोषणा DEBUG_OMAP4UART3_FLAGS DEBUG_OMAPUART_FLAGS
#या_अगर defined(CONFIG_DEBUG_OMAP4UART4)
#अघोषित DEBUG_OMAP4UART4_FLAGS
#घोषणा DEBUG_OMAP4UART4_FLAGS DEBUG_OMAPUART_FLAGS
#या_अगर defined(CONFIG_DEBUG_TI81XXUART1)
#अघोषित DEBUG_TI81XXUART1_FLAGS
#घोषणा DEBUG_TI81XXUART1_FLAGS DEBUG_OMAPUART_FLAGS
#या_अगर defined(CONFIG_DEBUG_TI81XXUART2)
#अघोषित DEBUG_TI81XXUART2_FLAGS
#घोषणा DEBUG_TI81XXUART2_FLAGS DEBUG_OMAPUART_FLAGS
#या_अगर defined(CONFIG_DEBUG_TI81XXUART3)
#अघोषित DEBUG_TI81XXUART3_FLAGS
#घोषणा DEBUG_TI81XXUART3_FLAGS DEBUG_OMAPUART_FLAGS
#या_अगर defined(CONFIG_DEBUG_AM33XXUART1)
#अघोषित DEBUG_AM33XXUART1_FLAGS
#घोषणा DEBUG_AM33XXUART1_FLAGS DEBUG_OMAPUART_FLAGS
#पूर्ण_अगर

/**
 * काष्ठा omap_hwmod_rst_info - IPs reset lines use by hwmod
 * @name: name of the reset line (module local name)
 * @rst_shअगरt: Offset of the reset bit
 * @st_shअगरt: Offset of the reset status bit (OMAP2/3 only)
 *
 * @name should be something लघु, e.g., "cpu0" or "rst". It is defined
 * locally to the hwmod.
 */
काष्ठा omap_hwmod_rst_info अणु
	स्थिर अक्षर	*name;
	u8		rst_shअगरt;
	u8		st_shअगरt;
पूर्ण;

/**
 * काष्ठा omap_hwmod_opt_clk - optional घड़ीs used by this hwmod
 * @role: "sys", "32k", "tv", etc -- क्रम use in clk_get()
 * @clk: opt घड़ी: OMAP घड़ी name
 * @_clk: poपूर्णांकer to the काष्ठा clk (filled in at runसमय)
 *
 * The module's पूर्णांकerface घड़ी and मुख्य functional घड़ी should not
 * be added as optional घड़ीs.
 */
काष्ठा omap_hwmod_opt_clk अणु
	स्थिर अक्षर	*role;
	स्थिर अक्षर	*clk;
	काष्ठा clk	*_clk;
पूर्ण;


/* omap_hwmod_omap2_firewall.flags bits */
#घोषणा OMAP_FIREWALL_L3		(1 << 0)
#घोषणा OMAP_FIREWALL_L4		(1 << 1)

/**
 * काष्ठा omap_hwmod_omap2_firewall - OMAP2/3 device firewall data
 * @l3_perm_bit: bit shअगरt क्रम L3_PM_*_PERMISSION_*
 * @l4_fw_region: L4 firewall region ID
 * @l4_prot_group: L4 protection group ID
 * @flags: (see omap_hwmod_omap2_firewall.flags macros above)
 */
काष्ठा omap_hwmod_omap2_firewall अणु
	u8 l3_perm_bit;
	u8 l4_fw_region;
	u8 l4_prot_group;
	u8 flags;
पूर्ण;

/*
 * omap_hwmod_ocp_अगर.user bits: these indicate the initiators that use this
 * पूर्णांकerface to पूर्णांकeract with the hwmod.  Used to add sleep dependencies
 * when the module is enabled or disabled.
 */
#घोषणा OCP_USER_MPU			(1 << 0)
#घोषणा OCP_USER_SDMA			(1 << 1)
#घोषणा OCP_USER_DSP			(1 << 2)
#घोषणा OCP_USER_IVA			(1 << 3)

/* omap_hwmod_ocp_अगर.flags bits */
#घोषणा OCPIF_SWSUP_IDLE		(1 << 0)
#घोषणा OCPIF_CAN_BURST			(1 << 1)

/* omap_hwmod_ocp_अगर._पूर्णांक_flags possibilities */
#घोषणा _OCPIF_INT_FLAGS_REGISTERED	(1 << 0)


/**
 * काष्ठा omap_hwmod_ocp_अगर - OCP पूर्णांकerface data
 * @master: काष्ठा omap_hwmod that initiates OCP transactions on this link
 * @slave: काष्ठा omap_hwmod that responds to OCP transactions on this link
 * @addr: address space associated with this link
 * @clk: पूर्णांकerface घड़ी: OMAP घड़ी name
 * @_clk: poपूर्णांकer to the पूर्णांकerface काष्ठा clk (filled in at runसमय)
 * @fw: पूर्णांकerface firewall data
 * @width: OCP data width
 * @user: initiators using this पूर्णांकerface (see OCP_USER_* macros above)
 * @flags: OCP पूर्णांकerface flags (see OCPIF_* macros above)
 * @_पूर्णांक_flags: पूर्णांकernal flags (see _OCPIF_INT_FLAGS* macros above)
 *
 * It may also be useful to add a tag_cnt field क्रम OCP2.x devices.
 *
 * Parameter names beginning with an underscore are managed पूर्णांकernally by
 * the omap_hwmod code and should not be set during initialization.
 */
काष्ठा omap_hwmod_ocp_अगर अणु
	काष्ठा omap_hwmod		*master;
	काष्ठा omap_hwmod		*slave;
	काष्ठा omap_hwmod_addr_space	*addr;
	स्थिर अक्षर			*clk;
	काष्ठा clk			*_clk;
	काष्ठा list_head		node;
	जोड़ अणु
		काष्ठा omap_hwmod_omap2_firewall omap2;
	पूर्ण				fw;
	u8				width;
	u8				user;
	u8				flags;
	u8				_पूर्णांक_flags;
पूर्ण;


/* Macros क्रम use in काष्ठा omap_hwmod_sysconfig */

/* Flags क्रम use in omap_hwmod_sysconfig.idlemodes */
#घोषणा MASTER_STANDBY_SHIFT	4
#घोषणा SLAVE_IDLE_SHIFT	0
#घोषणा SIDLE_FORCE		(HWMOD_IDLEMODE_FORCE << SLAVE_IDLE_SHIFT)
#घोषणा SIDLE_NO		(HWMOD_IDLEMODE_NO << SLAVE_IDLE_SHIFT)
#घोषणा SIDLE_SMART		(HWMOD_IDLEMODE_SMART << SLAVE_IDLE_SHIFT)
#घोषणा SIDLE_SMART_WKUP	(HWMOD_IDLEMODE_SMART_WKUP << SLAVE_IDLE_SHIFT)
#घोषणा MSTANDBY_FORCE		(HWMOD_IDLEMODE_FORCE << MASTER_STANDBY_SHIFT)
#घोषणा MSTANDBY_NO		(HWMOD_IDLEMODE_NO << MASTER_STANDBY_SHIFT)
#घोषणा MSTANDBY_SMART		(HWMOD_IDLEMODE_SMART << MASTER_STANDBY_SHIFT)
#घोषणा MSTANDBY_SMART_WKUP	(HWMOD_IDLEMODE_SMART_WKUP << MASTER_STANDBY_SHIFT)

/* omap_hwmod_sysconfig.sysc_flags capability flags */
#घोषणा SYSC_HAS_AUTOIDLE	(1 << 0)
#घोषणा SYSC_HAS_SOFTRESET	(1 << 1)
#घोषणा SYSC_HAS_ENAWAKEUP	(1 << 2)
#घोषणा SYSC_HAS_EMUFREE	(1 << 3)
#घोषणा SYSC_HAS_CLOCKACTIVITY	(1 << 4)
#घोषणा SYSC_HAS_SIDLEMODE	(1 << 5)
#घोषणा SYSC_HAS_MIDLEMODE	(1 << 6)
#घोषणा SYSS_HAS_RESET_STATUS	(1 << 7)
#घोषणा SYSC_NO_CACHE		(1 << 8)  /* XXX SW flag, beदीर्घs अन्यथाwhere */
#घोषणा SYSC_HAS_RESET_STATUS	(1 << 9)
#घोषणा SYSC_HAS_DMADISABLE	(1 << 10)

/* omap_hwmod_sysconfig.घड़ीact flags */
#घोषणा CLOCKACT_TEST_BOTH	0x0
#घोषणा CLOCKACT_TEST_MAIN	0x1
#घोषणा CLOCKACT_TEST_ICLK	0x2
#घोषणा CLOCKACT_TEST_NONE	0x3

/**
 * काष्ठा omap_hwmod_class_sysconfig - hwmod class OCP_SYS* data
 * @rev_offs: IP block revision रेजिस्टर offset (from module base addr)
 * @sysc_offs: OCP_SYSCONFIG रेजिस्टर offset (from module base addr)
 * @syss_offs: OCP_SYSSTATUS रेजिस्टर offset (from module base addr)
 * @srst_udelay: Delay needed after करोing a softreset in usecs
 * @idlemodes: One or more of अणुSIDLE,MSTANDBYपूर्ण_अणुOFF,FORCE,SMARTपूर्ण
 * @sysc_flags: SYSअणुC,Sपूर्ण_HAS* flags indicating SYSCONFIG bits supported
 * @घड़ीact: the शेष value of the module CLOCKACTIVITY bits
 *
 * @घड़ीact describes to the module which घड़ीs are likely to be
 * disabled when the PRCM issues its idle request to the module.  Some
 * modules have separate घड़ीकरोमुख्यs क्रम the पूर्णांकerface घड़ी and मुख्य
 * functional घड़ी, and can check whether they should acknowledge the
 * idle request based on the पूर्णांकernal module functionality that has
 * been associated with the घड़ीs marked in @घड़ीact.  This field is
 * only used अगर HWMOD_SET_DEFAULT_CLOCKACT is set (see below)
 *
 * @sysc_fields: काष्ठाure containing the offset positions of various bits in
 * SYSCONFIG रेजिस्टर. This can be populated using omap_hwmod_sysc_type1 or
 * omap_hwmod_sysc_type2 defined in omap_hwmod_common_data.c depending on
 * whether the device ip is compliant with the original PRCM protocol
 * defined क्रम OMAP2420 or the new PRCM protocol क्रम new OMAP4 IPs.
 * If the device follows a dअगरferent scheme क्रम the sysconfig रेजिस्टर ,
 * then this field has to be populated with the correct offset काष्ठाure.
 */
काष्ठा omap_hwmod_class_sysconfig अणु
	s32 rev_offs;
	s32 sysc_offs;
	s32 syss_offs;
	u16 sysc_flags;
	काष्ठा sysc_regbits *sysc_fields;
	u8 srst_udelay;
	u8 idlemodes;
पूर्ण;

/**
 * काष्ठा omap_hwmod_omap2_prcm - OMAP2/3-specअगरic PRCM data
 * @module_offs: PRCM submodule offset from the start of the PRM/CM
 * @idlest_reg_id: IDLEST रेजिस्टर ID (e.g., 3 क्रम CM_IDLEST3)
 * @idlest_idle_bit: रेजिस्टर bit shअगरt क्रम CM_IDLEST slave idle bit
 *
 * @prcm_reg_id and @module_bit are specअगरic to the AUTOIDLE, WKST,
 * WKEN, GRPSEL रेजिस्टरs.  In an ideal world, no extra inक्रमmation
 * would be needed क्रम IDLEST inक्रमmation, but alas, there are some
 * exceptions, so @idlest_reg_id, @idlest_idle_bit, @idlest_stdby_bit
 * are needed क्रम the IDLEST रेजिस्टरs (c.f. 2430 I2CHS, 3430 USBHOST)
 */
काष्ठा omap_hwmod_omap2_prcm अणु
	s16 module_offs;
	u8 idlest_reg_id;
	u8 idlest_idle_bit;
पूर्ण;

/*
 * Possible values क्रम काष्ठा omap_hwmod_omap4_prcm.flags
 *
 * HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT: Some IP blocks करोn't have a PRCM
 *     module-level context loss रेजिस्टर associated with them; this
 *     flag bit should be set in those हालs
 * HWMOD_OMAP4_ZERO_CLKCTRL_OFFSET: Some IP blocks have a valid CLKCTRL
 *	offset of zero; this flag bit should be set in those हालs to
 *	distinguish from hwmods that have no clkctrl offset.
 * HWMOD_OMAP4_CLKFWK_CLKCTR_CLOCK: Module घड़ीctrl घड़ी is managed
 *	by the common घड़ी framework and not hwmod.
 */
#घोषणा HWMOD_OMAP4_NO_CONTEXT_LOSS_BIT		(1 << 0)
#घोषणा HWMOD_OMAP4_ZERO_CLKCTRL_OFFSET		(1 << 1)
#घोषणा HWMOD_OMAP4_CLKFWK_CLKCTR_CLOCK		(1 << 2)

/**
 * काष्ठा omap_hwmod_omap4_prcm - OMAP4-specअगरic PRCM data
 * @clkctrl_offs: offset of the PRCM घड़ी control रेजिस्टर
 * @rstctrl_offs: offset of the XXX_RSTCTRL रेजिस्टर located in the PRM
 * @context_offs: offset of the RM_*_CONTEXT रेजिस्टर
 * @lostcontext_mask: biपंचांगask क्रम selecting bits from RM_*_CONTEXT रेजिस्टर
 * @rstst_reg: (AM33XX only) address of the XXX_RSTST रेजिस्टर in the PRM
 * @submodule_wkdep_bit: bit shअगरt of the WKDEP range
 * @flags: PRCM रेजिस्टर capabilities क्रम this IP block
 * @modulemode: allowable modulemodes
 * @context_lost_counter: Count of module level context lost
 *
 * If @lostcontext_mask is not defined, context loss check code uses
 * whole रेजिस्टर without masking. @lostcontext_mask should only be
 * defined in हालs where @context_offs रेजिस्टर is shared by two or
 * more hwmods.
 */
काष्ठा omap_hwmod_omap4_prcm अणु
	u16		clkctrl_offs;
	u16		rstctrl_offs;
	u16		rstst_offs;
	u16		context_offs;
	u32		lostcontext_mask;
	u8		submodule_wkdep_bit;
	u8		modulemode;
	u8		flags;
	पूर्णांक		context_lost_counter;
पूर्ण;


/*
 * omap_hwmod.flags definitions
 *
 * HWMOD_SWSUP_SIDLE: omap_hwmod code should manually bring module in and out
 *     of idle, rather than relying on module smart-idle
 * HWMOD_SWSUP_MSTANDBY: omap_hwmod code should manually bring module in and
 *     out of standby, rather than relying on module smart-standby
 * HWMOD_INIT_NO_RESET: करोn't reset this module at boot - important क्रम
 *     SDRAM controller, etc. XXX probably beदीर्घs outside the मुख्य hwmod file
 *     XXX Should be HWMOD_SETUP_NO_RESET
 * HWMOD_INIT_NO_IDLE: करोn't idle this module at boot - important क्रम SDRAM
 *     controller, etc. XXX probably beदीर्घs outside the मुख्य hwmod file
 *     XXX Should be HWMOD_SETUP_NO_IDLE
 * HWMOD_NO_OCP_AUTOIDLE: disable module स्वतःidle (OCP_SYSCONFIG.AUTOIDLE)
 *     when module is enabled, rather than the शेष, which is to
 *     enable स्वतःidle
 * HWMOD_SET_DEFAULT_CLOCKACT: program CLOCKACTIVITY bits at startup
 * HWMOD_NO_IDLEST: this module करोes not have idle status - this is the हाल
 *     only क्रम few initiator modules on OMAP2 & 3.
 * HWMOD_CONTROL_OPT_CLKS_IN_RESET: Enable all optional घड़ीs during reset.
 *     This is needed क्रम devices like DSS that require optional घड़ीs enabled
 *     in order to complete the reset. Optional घड़ीs will be disabled
 *     again after the reset.
 * HWMOD_16BIT_REG: Module has 16bit रेजिस्टरs
 * HWMOD_EXT_OPT_MAIN_CLK: The only मुख्य functional घड़ी source क्रम
 *     this IP block comes from an off-chip source and is not always
 *     enabled.  This prevents the hwmod code from being able to
 *     enable and reset the IP block early.  XXX Eventually it should
 *     be possible to query the घड़ी framework क्रम this inक्रमmation.
 * HWMOD_BLOCK_WFI: Some OMAP peripherals apparently करोn't work
 *     correctly अगर the MPU is allowed to go idle जबतक the
 *     peripherals are active.  This is apparently true क्रम the I2C on
 *     OMAP2420, and also the EMAC on AM3517/3505.  It's unlikely that
 *     this is really true -- we're probably not configuring something
 *     correctly, or this is being abused to deal with some PM latency
 *     issues -- but we're currently suffering from a लघुage of
 *     folks who are able to track these issues करोwn properly.
 * HWMOD_FORCE_MSTANDBY: Always keep MIDLEMODE bits cleared so that device
 *     is kept in क्रमce-standby mode. Failing to करो so causes PM problems
 *     with musb on OMAP3630 at least. Note that musb has a dedicated रेजिस्टर
 *     to control MSTANDBY संकेत when MIDLEMODE is set to क्रमce-standby.
 * HWMOD_SWSUP_SIDLE_ACT: omap_hwmod code should manually bring the module
 *     out of idle, but rely on smart-idle to the put it back in idle,
 *     so the wakeups are still functional (Only known हाल क्रम now is UART)
 * HWMOD_RECONFIG_IO_CHAIN: omap_hwmod code needs to reconfigure wake-up 
 *     events by calling _reconfigure_io_chain() when a device is enabled
 *     or idled.
 * HWMOD_OPT_CLKS_NEEDED: The optional घड़ीs are needed क्रम the module to
 *     operate and they need to be handled at the same समय as the मुख्य_clk.
 * HWMOD_NO_IDLE: Do not idle the hwmod at all. Useful to handle certain
 *     IPs like CPSW on DRA7, where घड़ीs to this module cannot be disabled.
 * HWMOD_CLKDM_NOAUTO: Allows the hwmod's घड़ीकरोमुख्य to be prevented from
 *     entering HW_AUTO जबतक hwmod is active. This is needed to workaround
 *     some modules which करोn't function correctly with HW_AUTO. For example,
 *     DCAN on DRA7x SoC needs this to workaround errata i893.
 */
#घोषणा HWMOD_SWSUP_SIDLE			(1 << 0)
#घोषणा HWMOD_SWSUP_MSTANDBY			(1 << 1)
#घोषणा HWMOD_INIT_NO_RESET			(1 << 2)
#घोषणा HWMOD_INIT_NO_IDLE			(1 << 3)
#घोषणा HWMOD_NO_OCP_AUTOIDLE			(1 << 4)
#घोषणा HWMOD_SET_DEFAULT_CLOCKACT		(1 << 5)
#घोषणा HWMOD_NO_IDLEST				(1 << 6)
#घोषणा HWMOD_CONTROL_OPT_CLKS_IN_RESET		(1 << 7)
#घोषणा HWMOD_16BIT_REG				(1 << 8)
#घोषणा HWMOD_EXT_OPT_MAIN_CLK			(1 << 9)
#घोषणा HWMOD_BLOCK_WFI				(1 << 10)
#घोषणा HWMOD_FORCE_MSTANDBY			(1 << 11)
#घोषणा HWMOD_SWSUP_SIDLE_ACT			(1 << 12)
#घोषणा HWMOD_RECONFIG_IO_CHAIN			(1 << 13)
#घोषणा HWMOD_OPT_CLKS_NEEDED			(1 << 14)
#घोषणा HWMOD_NO_IDLE				(1 << 15)
#घोषणा HWMOD_CLKDM_NOAUTO			(1 << 16)

/*
 * omap_hwmod._पूर्णांक_flags definitions
 * These are क्रम पूर्णांकernal use only and are managed by the omap_hwmod code.
 *
 * _HWMOD_NO_MPU_PORT: no path exists क्रम the MPU to ग_लिखो to this module
 * _HWMOD_SYSCONFIG_LOADED: set when the OCP_SYSCONFIG value has been cached
 * _HWMOD_SKIP_ENABLE: set अगर hwmod enabled during init (HWMOD_INIT_NO_IDLE) -
 *     causes the first call to _enable() to only update the pinmux
 */
#घोषणा _HWMOD_NO_MPU_PORT			(1 << 0)
#घोषणा _HWMOD_SYSCONFIG_LOADED			(1 << 1)
#घोषणा _HWMOD_SKIP_ENABLE			(1 << 2)

/*
 * omap_hwmod._state definitions
 *
 * INITIALIZED: reset (optionally), initialized, enabled, disabled
 *              (optionally)
 *
 *
 */
#घोषणा _HWMOD_STATE_UNKNOWN			0
#घोषणा _HWMOD_STATE_REGISTERED			1
#घोषणा _HWMOD_STATE_CLKS_INITED		2
#घोषणा _HWMOD_STATE_INITIALIZED		3
#घोषणा _HWMOD_STATE_ENABLED			4
#घोषणा _HWMOD_STATE_IDLE			5
#घोषणा _HWMOD_STATE_DISABLED			6

#अगर_घोषित CONFIG_PM
#घोषणा _HWMOD_STATE_DEFAULT			_HWMOD_STATE_IDLE
#अन्यथा
#घोषणा _HWMOD_STATE_DEFAULT			_HWMOD_STATE_ENABLED
#पूर्ण_अगर

/**
 * काष्ठा omap_hwmod_class - the type of an IP block
 * @name: name of the hwmod_class
 * @sysc: device SYSCONFIG/SYSSTATUS रेजिस्टर data
 * @pre_shutकरोwn: ptr to fn to be executed immediately prior to device shutकरोwn
 * @reset: ptr to fn to be executed in place of the standard hwmod reset fn
 * @lock: ptr to fn to be executed to lock IP रेजिस्टरs
 * @unlock: ptr to fn to be executed to unlock IP रेजिस्टरs
 *
 * Represent the class of a OMAP hardware "modules" (e.g. समयr,
 * smartreflex, gpio, uart...)
 *
 * @pre_shutकरोwn is a function that will be run immediately beक्रमe
 * hwmod घड़ीs are disabled, etc.  It is पूर्णांकended क्रम use क्रम hwmods
 * like the MPU watchकरोg, which cannot be disabled with the standard
 * omap_hwmod_shutकरोwn().  The function should वापस 0 upon success,
 * or some negative error upon failure.  Returning an error will cause
 * omap_hwmod_shutकरोwn() to पात the device shutकरोwn and वापस an
 * error.
 *
 * If @reset is defined, then the function it poपूर्णांकs to will be
 * executed in place of the standard hwmod _reset() code in
 * mach-omap2/omap_hwmod.c.  This is needed क्रम IP blocks which have
 * unusual reset sequences - usually processor IP blocks like the IVA.
 */
काष्ठा omap_hwmod_class अणु
	स्थिर अक्षर				*name;
	काष्ठा omap_hwmod_class_sysconfig	*sysc;
	पूर्णांक					(*pre_shutकरोwn)(काष्ठा omap_hwmod *oh);
	पूर्णांक					(*reset)(काष्ठा omap_hwmod *oh);
	व्योम					(*lock)(काष्ठा omap_hwmod *oh);
	व्योम					(*unlock)(काष्ठा omap_hwmod *oh);
पूर्ण;

/**
 * काष्ठा omap_hwmod - पूर्णांकegration data क्रम OMAP hardware "modules" (IP blocks)
 * @name: name of the hwmod
 * @class: काष्ठा omap_hwmod_class * to the class of this hwmod
 * @od: काष्ठा omap_device currently associated with this hwmod (पूर्णांकernal use)
 * @prcm: PRCM data pertaining to this hwmod
 * @मुख्य_clk: मुख्य घड़ी: OMAP घड़ी name
 * @_clk: poपूर्णांकer to the मुख्य काष्ठा clk (filled in at runसमय)
 * @opt_clks: other device घड़ीs that drivers can request (0..*)
 * @voltdm: poपूर्णांकer to voltage करोमुख्य (filled in at runसमय)
 * @dev_attr: arbitrary device attributes that can be passed to the driver
 * @_sysc_cache: पूर्णांकernal-use hwmod flags
 * @mpu_rt_idx: index of device address space क्रम रेजिस्टर target (क्रम DT boot)
 * @_mpu_rt_va: cached रेजिस्टर target start address (पूर्णांकernal use)
 * @_mpu_port: cached MPU रेजिस्टर target slave (पूर्णांकernal use)
 * @opt_clks_cnt: number of @opt_clks
 * @master_cnt: number of @master entries
 * @slaves_cnt: number of @slave entries
 * @response_lat: device OCP response latency (in पूर्णांकerface घड़ी cycles)
 * @_पूर्णांक_flags: पूर्णांकernal-use hwmod flags
 * @_state: पूर्णांकernal-use hwmod state
 * @_postsetup_state: पूर्णांकernal-use state to leave the hwmod in after _setup()
 * @flags: hwmod flags (करोcumented below)
 * @_lock: spinlock serializing operations on this hwmod
 * @node: list node क्रम hwmod list (पूर्णांकernal use)
 * @parent_hwmod: (temporary) a poपूर्णांकer to the hierarchical parent of this hwmod
 *
 * @मुख्य_clk refers to this module's "main clock," which क्रम our
 * purposes is defined as "the functional घड़ी needed क्रम रेजिस्टर
 * accesses to complete."  Modules may not have a मुख्य घड़ी अगर the
 * पूर्णांकerface घड़ी also serves as a मुख्य घड़ी.
 *
 * Parameter names beginning with an underscore are managed पूर्णांकernally by
 * the omap_hwmod code and should not be set during initialization.
 *
 * @masters and @slaves are now deprecated.
 *
 * @parent_hwmod is temporary; there should be no need क्रम it, as this
 * inक्रमmation should alपढ़ोy be expressed in the OCP पूर्णांकerface
 * काष्ठाures.  @parent_hwmod is present as a workaround until we improve
 * handling क्रम hwmods with multiple parents (e.g., OMAP4+ DSS with
 * multiple रेजिस्टर tarमाला_लो across dअगरferent पूर्णांकerconnects).
 */
काष्ठा omap_hwmod अणु
	स्थिर अक्षर			*name;
	काष्ठा omap_hwmod_class		*class;
	काष्ठा omap_device		*od;
	काष्ठा omap_hwmod_rst_info	*rst_lines;
	जोड़ अणु
		काष्ठा omap_hwmod_omap2_prcm omap2;
		काष्ठा omap_hwmod_omap4_prcm omap4;
	पूर्ण				prcm;
	स्थिर अक्षर			*मुख्य_clk;
	काष्ठा clk			*_clk;
	काष्ठा omap_hwmod_opt_clk	*opt_clks;
	स्थिर अक्षर			*clkdm_name;
	काष्ठा घड़ीकरोमुख्य		*clkdm;
	काष्ठा list_head		slave_ports; /* connect to *_TA */
	व्योम				*dev_attr;
	u32				_sysc_cache;
	व्योम __iomem			*_mpu_rt_va;
	spinlock_t			_lock;
	काष्ठा lock_class_key		hwmod_key; /* unique lock class */
	काष्ठा list_head		node;
	काष्ठा omap_hwmod_ocp_अगर	*_mpu_port;
	u32				flags;
	u8				mpu_rt_idx;
	u8				response_lat;
	u8				rst_lines_cnt;
	u8				opt_clks_cnt;
	u8				slaves_cnt;
	u8				hwmods_cnt;
	u8				_पूर्णांक_flags;
	u8				_state;
	u8				_postsetup_state;
	काष्ठा omap_hwmod		*parent_hwmod;
पूर्ण;

#अगर_घोषित CONFIG_OMAP_HWMOD

काष्ठा device_node;

काष्ठा omap_hwmod *omap_hwmod_lookup(स्थिर अक्षर *name);
पूर्णांक omap_hwmod_क्रम_each(पूर्णांक (*fn)(काष्ठा omap_hwmod *oh, व्योम *data),
			व्योम *data);

पूर्णांक __init omap_hwmod_setup_one(स्थिर अक्षर *name);
पूर्णांक omap_hwmod_parse_module_range(काष्ठा omap_hwmod *oh,
				  काष्ठा device_node *np,
				  काष्ठा resource *res);

काष्ठा ti_sysc_module_data;
काष्ठा ti_sysc_cookie;

पूर्णांक omap_hwmod_init_module(काष्ठा device *dev,
			   स्थिर काष्ठा ti_sysc_module_data *data,
			   काष्ठा ti_sysc_cookie *cookie);

पूर्णांक omap_hwmod_enable(काष्ठा omap_hwmod *oh);
पूर्णांक omap_hwmod_idle(काष्ठा omap_hwmod *oh);
पूर्णांक omap_hwmod_shutकरोwn(काष्ठा omap_hwmod *oh);

पूर्णांक omap_hwmod_निश्चित_hardreset(काष्ठा omap_hwmod *oh, स्थिर अक्षर *name);
पूर्णांक omap_hwmod_deनिश्चित_hardreset(काष्ठा omap_hwmod *oh, स्थिर अक्षर *name);

व्योम omap_hwmod_ग_लिखो(u32 v, काष्ठा omap_hwmod *oh, u16 reg_offs);
u32 omap_hwmod_पढ़ो(काष्ठा omap_hwmod *oh, u16 reg_offs);
पूर्णांक omap_hwmod_softreset(काष्ठा omap_hwmod *oh);

पूर्णांक omap_hwmod_count_resources(काष्ठा omap_hwmod *oh, अचिन्हित दीर्घ flags);
पूर्णांक omap_hwmod_fill_resources(काष्ठा omap_hwmod *oh, काष्ठा resource *res);
पूर्णांक omap_hwmod_get_resource_byname(काष्ठा omap_hwmod *oh, अचिन्हित पूर्णांक type,
				   स्थिर अक्षर *name, काष्ठा resource *res);

काष्ठा घातerकरोमुख्य *omap_hwmod_get_pwrdm(काष्ठा omap_hwmod *oh);
व्योम __iomem *omap_hwmod_get_mpu_rt_va(काष्ठा omap_hwmod *oh);

पूर्णांक omap_hwmod_क्रम_each_by_class(स्थिर अक्षर *classname,
				 पूर्णांक (*fn)(काष्ठा omap_hwmod *oh,
					   व्योम *user),
				 व्योम *user);

पूर्णांक omap_hwmod_set_postsetup_state(काष्ठा omap_hwmod *oh, u8 state);
पूर्णांक omap_hwmod_get_context_loss_count(काष्ठा omap_hwmod *oh);

बाह्य व्योम __init omap_hwmod_init(व्योम);

स्थिर अक्षर *omap_hwmod_get_मुख्य_clk(काष्ठा omap_hwmod *oh);

#अन्यथा	/* CONFIG_OMAP_HWMOD */

अटल अंतरभूत पूर्णांक
omap_hwmod_क्रम_each_by_class(स्थिर अक्षर *classname,
			     पूर्णांक (*fn)(काष्ठा omap_hwmod *oh, व्योम *user),
			     व्योम *user)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_OMAP_HWMOD */

/*
 *
 */

व्योम omap_hwmod_rtc_unlock(काष्ठा omap_hwmod *oh);
व्योम omap_hwmod_rtc_lock(काष्ठा omap_hwmod *oh);

/*
 * Chip variant-specअगरic hwmod init routines - XXX should be converted
 * to use initcalls once the initial boot ordering is straightened out
 */
बाह्य पूर्णांक omap2420_hwmod_init(व्योम);
बाह्य पूर्णांक omap2430_hwmod_init(व्योम);
बाह्य पूर्णांक omap3xxx_hwmod_init(व्योम);
बाह्य पूर्णांक omap44xx_hwmod_init(व्योम);
बाह्य पूर्णांक am33xx_hwmod_init(व्योम);
बाह्य पूर्णांक dm814x_hwmod_init(व्योम);
बाह्य पूर्णांक dm816x_hwmod_init(व्योम);
बाह्य पूर्णांक dra7xx_hwmod_init(व्योम);
पूर्णांक am43xx_hwmod_init(व्योम);

बाह्य पूर्णांक __init omap_hwmod_रेजिस्टर_links(काष्ठा omap_hwmod_ocp_अगर **ois);

#पूर्ण_अगर
