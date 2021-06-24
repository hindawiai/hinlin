<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2/3 System Control Module रेजिस्टर access
 *
 * Copyright (C) 2007, 2012 Texas Instruments, Inc.
 * Copyright (C) 2007 Nokia Corporation
 *
 * Written by Paul Walmsley
 */
#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/cpu_pm.h>

#समावेश "soc.h"
#समावेश "iomap.h"
#समावेश "common.h"
#समावेश "cm-regbits-34xx.h"
#समावेश "prm-regbits-34xx.h"
#समावेश "prm3xxx.h"
#समावेश "cm3xxx.h"
#समावेश "sdrc.h"
#समावेश "pm.h"
#समावेश "control.h"
#समावेश "clock.h"

/* Used by omap3_ctrl_save_padconf() */
#घोषणा START_PADCONF_SAVE		0x2
#घोषणा PADCONF_SAVE_DONE		0x1

अटल व्योम __iomem *omap2_ctrl_base;
अटल s16 omap2_ctrl_offset;

#अगर defined(CONFIG_ARCH_OMAP3) && defined(CONFIG_PM)
काष्ठा omap3_scratchpad अणु
	u32 boot_config_ptr;
	u32 खुला_restore_ptr;
	u32 secure_ram_restore_ptr;
	u32 sdrc_module_semaphore;
	u32 prcm_block_offset;
	u32 sdrc_block_offset;
पूर्ण;

काष्ठा omap3_scratchpad_prcm_block अणु
	u32 prm_contents[2];
	u32 cm_contents[11];
	u32 prcm_block_size;
पूर्ण;

काष्ठा omap3_scratchpad_sdrc_block अणु
	u16 sysconfig;
	u16 cs_cfg;
	u16 sharing;
	u16 err_type;
	u32 dll_a_ctrl;
	u32 dll_b_ctrl;
	u32 घातer;
	u32 cs_0;
	u32 mcfg_0;
	u16 mr_0;
	u16 emr_1_0;
	u16 emr_2_0;
	u16 emr_3_0;
	u32 actim_ctrla_0;
	u32 actim_ctrlb_0;
	u32 rfr_ctrl_0;
	u32 cs_1;
	u32 mcfg_1;
	u16 mr_1;
	u16 emr_1_1;
	u16 emr_2_1;
	u16 emr_3_1;
	u32 actim_ctrla_1;
	u32 actim_ctrlb_1;
	u32 rfr_ctrl_1;
	u16 dcdl_1_ctrl;
	u16 dcdl_2_ctrl;
	u32 flags;
	u32 block_size;
पूर्ण;

व्योम *omap3_secure_ram_storage;

/*
 * This is used to store ARM रेजिस्टरs in SDRAM beक्रमe attempting
 * an MPU OFF. The save and restore happens from the SRAM sleep code.
 * The address is stored in scratchpad, so that it can be used
 * during the restore path.
 */
u32 omap3_arm_context[128];

काष्ठा omap3_control_regs अणु
	u32 sysconfig;
	u32 devconf0;
	u32 mem_dftrw0;
	u32 mem_dftrw1;
	u32 msuspendmux_0;
	u32 msuspendmux_1;
	u32 msuspendmux_2;
	u32 msuspendmux_3;
	u32 msuspendmux_4;
	u32 msuspendmux_5;
	u32 sec_ctrl;
	u32 devconf1;
	u32 csirxfe;
	u32 iva2_bootaddr;
	u32 iva2_booपंचांगod;
	u32 wkup_ctrl;
	u32 debobs_0;
	u32 debobs_1;
	u32 debobs_2;
	u32 debobs_3;
	u32 debobs_4;
	u32 debobs_5;
	u32 debobs_6;
	u32 debobs_7;
	u32 debobs_8;
	u32 prog_io0;
	u32 prog_io1;
	u32 dss_dpll_spपढ़ोing;
	u32 core_dpll_spपढ़ोing;
	u32 per_dpll_spपढ़ोing;
	u32 usbhost_dpll_spपढ़ोing;
	u32 pbias_lite;
	u32 temp_sensor;
	u32 sramlकरो4;
	u32 sramlकरो5;
	u32 csi;
	u32 padconf_sys_nirq;
पूर्ण;

अटल काष्ठा omap3_control_regs control_context;
#पूर्ण_अगर /* CONFIG_ARCH_OMAP3 && CONFIG_PM */

व्योम __init omap2_set_globals_control(व्योम __iomem *ctrl)
अणु
	omap2_ctrl_base = ctrl;
पूर्ण

u8 omap_ctrl_पढ़ोb(u16 offset)
अणु
	u32 val;
	u8 byte_offset = offset & 0x3;

	val = omap_ctrl_पढ़ोl(offset);

	वापस (val >> (byte_offset * 8)) & 0xff;
पूर्ण

u16 omap_ctrl_पढ़ोw(u16 offset)
अणु
	u32 val;
	u16 byte_offset = offset & 0x2;

	val = omap_ctrl_पढ़ोl(offset);

	वापस (val >> (byte_offset * 8)) & 0xffff;
पूर्ण

u32 omap_ctrl_पढ़ोl(u16 offset)
अणु
	offset &= 0xfffc;

	वापस पढ़ोl_relaxed(omap2_ctrl_base + offset);
पूर्ण

व्योम omap_ctrl_ग_लिखोb(u8 val, u16 offset)
अणु
	u32 पंचांगp;
	u8 byte_offset = offset & 0x3;

	पंचांगp = omap_ctrl_पढ़ोl(offset);

	पंचांगp &= 0xffffffff ^ (0xff << (byte_offset * 8));
	पंचांगp |= val << (byte_offset * 8);

	omap_ctrl_ग_लिखोl(पंचांगp, offset);
पूर्ण

व्योम omap_ctrl_ग_लिखोw(u16 val, u16 offset)
अणु
	u32 पंचांगp;
	u8 byte_offset = offset & 0x2;

	पंचांगp = omap_ctrl_पढ़ोl(offset);

	पंचांगp &= 0xffffffff ^ (0xffff << (byte_offset * 8));
	पंचांगp |= val << (byte_offset * 8);

	omap_ctrl_ग_लिखोl(पंचांगp, offset);
पूर्ण

व्योम omap_ctrl_ग_लिखोl(u32 val, u16 offset)
अणु
	offset &= 0xfffc;
	ग_लिखोl_relaxed(val, omap2_ctrl_base + offset);
पूर्ण

#अगर_घोषित CONFIG_ARCH_OMAP3

/**
 * omap3_ctrl_ग_लिखो_boot_mode - set scratchpad boot mode क्रम the next boot
 * @booपंचांगode: 8-bit value to pass to some boot code
 *
 * Set the booपंचांगode in the scratchpad RAM.  This is used after the
 * प्रणाली restarts.  Not sure what actually uses this - it may be the
 * bootloader, rather than the boot ROM - contrary to the preserved
 * comment below.  No वापस value.
 */
व्योम omap3_ctrl_ग_लिखो_boot_mode(u8 booपंचांगode)
अणु
	u32 l;

	l = ('B' << 24) | ('M' << 16) | booपंचांगode;

	/*
	 * Reserve the first word in scratchpad क्रम communicating
	 * with the boot ROM. A poपूर्णांकer to a data काष्ठाure
	 * describing the boot process can be stored there,
	 * cf. OMAP34xx TRM, Initialization / Software Booting
	 * Configuration.
	 *
	 * XXX This should use some omap_ctrl_ग_लिखोl()-type function
	 */
	ग_लिखोl_relaxed(l, OMAP2_L4_IO_ADDRESS(OMAP343X_SCRATCHPAD + 4));
पूर्ण

#पूर्ण_अगर

/**
 * omap_ctrl_ग_लिखो_dsp_boot_addr - set boot address क्रम a remote processor
 * @bootaddr: physical address of the boot loader
 *
 * Set boot address क्रम the boot loader of a supported processor
 * when a घातer ON sequence occurs.
 */
व्योम omap_ctrl_ग_लिखो_dsp_boot_addr(u32 bootaddr)
अणु
	u32 offset = cpu_is_omap243x() ? OMAP243X_CONTROL_IVA2_BOOTADDR :
		     cpu_is_omap34xx() ? OMAP343X_CONTROL_IVA2_BOOTADDR :
		     cpu_is_omap44xx() ? OMAP4_CTRL_MODULE_CORE_DSP_BOOTADDR :
		     soc_is_omap54xx() ? OMAP4_CTRL_MODULE_CORE_DSP_BOOTADDR :
		     0;

	अगर (!offset) अणु
		pr_err("%s: unsupported omap type\n", __func__);
		वापस;
	पूर्ण

	omap_ctrl_ग_लिखोl(bootaddr, offset);
पूर्ण

/**
 * omap_ctrl_ग_लिखो_dsp_boot_mode - set boot mode क्रम a remote processor
 * @booपंचांगode: 8-bit value to pass to some boot code
 *
 * Sets boot mode क्रम the boot loader of a supported processor
 * when a घातer ON sequence occurs.
 */
व्योम omap_ctrl_ग_लिखो_dsp_boot_mode(u8 booपंचांगode)
अणु
	u32 offset = cpu_is_omap243x() ? OMAP243X_CONTROL_IVA2_BOOTMOD :
		     cpu_is_omap34xx() ? OMAP343X_CONTROL_IVA2_BOOTMOD :
		     0;

	अगर (!offset) अणु
		pr_err("%s: unsupported omap type\n", __func__);
		वापस;
	पूर्ण

	omap_ctrl_ग_लिखोl(booपंचांगode, offset);
पूर्ण

#अगर defined(CONFIG_ARCH_OMAP3) && defined(CONFIG_PM)
/*
 * Clears the scratchpad contents in हाल of cold boot-
 * called during bootup
 */
व्योम omap3_clear_scratchpad_contents(व्योम)
अणु
	u32 max_offset = OMAP343X_SCRATCHPAD_ROM_OFFSET;
	व्योम __iomem *v_addr;
	u32 offset = 0;

	v_addr = OMAP2_L4_IO_ADDRESS(OMAP343X_SCRATCHPAD_ROM);
	अगर (omap3xxx_prm_clear_global_cold_reset()) अणु
		क्रम ( ; offset <= max_offset; offset += 0x4)
			ग_लिखोl_relaxed(0x0, (v_addr + offset));
	पूर्ण
पूर्ण

/* Populate the scratchpad काष्ठाure with restore काष्ठाure */
व्योम omap3_save_scratchpad_contents(व्योम)
अणु
	व्योम  __iomem *scratchpad_address;
	u32 arm_context_addr;
	काष्ठा omap3_scratchpad scratchpad_contents;
	काष्ठा omap3_scratchpad_prcm_block prcm_block_contents;
	काष्ठा omap3_scratchpad_sdrc_block sdrc_block_contents;

	/*
	 * Populate the Scratchpad contents
	 *
	 * The "get_*restore_pointer" functions are used to provide a
	 * physical restore address where the ROM code jumps जबतक waking
	 * up from MPU OFF/OSWR state.
	 * The restore poपूर्णांकer is stored पूर्णांकo the scratchpad.
	 */
	scratchpad_contents.boot_config_ptr = 0x0;
	अगर (cpu_is_omap3630())
		scratchpad_contents.खुला_restore_ptr =
			__pa_symbol(omap3_restore_3630);
	अन्यथा अगर (omap_rev() != OMAP3430_REV_ES3_0 &&
					omap_rev() != OMAP3430_REV_ES3_1 &&
					omap_rev() != OMAP3430_REV_ES3_1_2)
		scratchpad_contents.खुला_restore_ptr =
			__pa_symbol(omap3_restore);
	अन्यथा
		scratchpad_contents.खुला_restore_ptr =
			__pa_symbol(omap3_restore_es3);

	अगर (omap_type() == OMAP2_DEVICE_TYPE_GP)
		scratchpad_contents.secure_ram_restore_ptr = 0x0;
	अन्यथा
		scratchpad_contents.secure_ram_restore_ptr =
			(u32) __pa(omap3_secure_ram_storage);
	scratchpad_contents.sdrc_module_semaphore = 0x0;
	scratchpad_contents.prcm_block_offset = 0x2C;
	scratchpad_contents.sdrc_block_offset = 0x64;

	/* Populate the PRCM block contents */
	omap3_prm_save_scratchpad_contents(prcm_block_contents.prm_contents);
	omap3_cm_save_scratchpad_contents(prcm_block_contents.cm_contents);

	prcm_block_contents.prcm_block_size = 0x0;

	/* Populate the SDRC block contents */
	sdrc_block_contents.sysconfig =
			(sdrc_पढ़ो_reg(SDRC_SYSCONFIG) & 0xFFFF);
	sdrc_block_contents.cs_cfg =
			(sdrc_पढ़ो_reg(SDRC_CS_CFG) & 0xFFFF);
	sdrc_block_contents.sharing =
			(sdrc_पढ़ो_reg(SDRC_SHARING) & 0xFFFF);
	sdrc_block_contents.err_type =
			(sdrc_पढ़ो_reg(SDRC_ERR_TYPE) & 0xFFFF);
	sdrc_block_contents.dll_a_ctrl = sdrc_पढ़ो_reg(SDRC_DLLA_CTRL);
	sdrc_block_contents.dll_b_ctrl = 0x0;
	/*
	 * Due to a OMAP3 errata (1.142), on EMU/HS devices SRDC should
	 * be programed to issue स्वतःmatic self refresh on समयout
	 * of AUTO_CNT = 1 prior to any transition to OFF mode.
	 */
	अगर ((omap_type() != OMAP2_DEVICE_TYPE_GP)
			&& (omap_rev() >= OMAP3430_REV_ES3_0))
		sdrc_block_contents.घातer = (sdrc_पढ़ो_reg(SDRC_POWER) &
				~(SDRC_POWER_AUTOCOUNT_MASK|
				SDRC_POWER_CLKCTRL_MASK)) |
				(1 << SDRC_POWER_AUTOCOUNT_SHIFT) |
				SDRC_SELF_REFRESH_ON_AUTOCOUNT;
	अन्यथा
		sdrc_block_contents.घातer = sdrc_पढ़ो_reg(SDRC_POWER);

	sdrc_block_contents.cs_0 = 0x0;
	sdrc_block_contents.mcfg_0 = sdrc_पढ़ो_reg(SDRC_MCFG_0);
	sdrc_block_contents.mr_0 = (sdrc_पढ़ो_reg(SDRC_MR_0) & 0xFFFF);
	sdrc_block_contents.emr_1_0 = 0x0;
	sdrc_block_contents.emr_2_0 = 0x0;
	sdrc_block_contents.emr_3_0 = 0x0;
	sdrc_block_contents.actim_ctrla_0 =
			sdrc_पढ़ो_reg(SDRC_ACTIM_CTRL_A_0);
	sdrc_block_contents.actim_ctrlb_0 =
			sdrc_पढ़ो_reg(SDRC_ACTIM_CTRL_B_0);
	sdrc_block_contents.rfr_ctrl_0 =
			sdrc_पढ़ो_reg(SDRC_RFR_CTRL_0);
	sdrc_block_contents.cs_1 = 0x0;
	sdrc_block_contents.mcfg_1 = sdrc_पढ़ो_reg(SDRC_MCFG_1);
	sdrc_block_contents.mr_1 = sdrc_पढ़ो_reg(SDRC_MR_1) & 0xFFFF;
	sdrc_block_contents.emr_1_1 = 0x0;
	sdrc_block_contents.emr_2_1 = 0x0;
	sdrc_block_contents.emr_3_1 = 0x0;
	sdrc_block_contents.actim_ctrla_1 =
			sdrc_पढ़ो_reg(SDRC_ACTIM_CTRL_A_1);
	sdrc_block_contents.actim_ctrlb_1 =
			sdrc_पढ़ो_reg(SDRC_ACTIM_CTRL_B_1);
	sdrc_block_contents.rfr_ctrl_1 =
			sdrc_पढ़ो_reg(SDRC_RFR_CTRL_1);
	sdrc_block_contents.dcdl_1_ctrl = 0x0;
	sdrc_block_contents.dcdl_2_ctrl = 0x0;
	sdrc_block_contents.flags = 0x0;
	sdrc_block_contents.block_size = 0x0;

	arm_context_addr = __pa_symbol(omap3_arm_context);

	/* Copy all the contents to the scratchpad location */
	scratchpad_address = OMAP2_L4_IO_ADDRESS(OMAP343X_SCRATCHPAD);
	स_नकल_toio(scratchpad_address, &scratchpad_contents,
		 माप(scratchpad_contents));
	/* Scratchpad contents being 32 bits, a भागide by 4 करोne here */
	स_नकल_toio(scratchpad_address +
		scratchpad_contents.prcm_block_offset,
		&prcm_block_contents, माप(prcm_block_contents));
	स_नकल_toio(scratchpad_address +
		scratchpad_contents.sdrc_block_offset,
		&sdrc_block_contents, माप(sdrc_block_contents));
	/*
	 * Copies the address of the location in SDRAM where ARM
	 * रेजिस्टरs get saved during a MPU OFF transition.
	 */
	स_नकल_toio(scratchpad_address +
		scratchpad_contents.sdrc_block_offset +
		माप(sdrc_block_contents), &arm_context_addr, 4);
पूर्ण

व्योम omap3_control_save_context(व्योम)
अणु
	control_context.sysconfig = omap_ctrl_पढ़ोl(OMAP2_CONTROL_SYSCONFIG);
	control_context.devconf0 = omap_ctrl_पढ़ोl(OMAP2_CONTROL_DEVCONF0);
	control_context.mem_dftrw0 =
			omap_ctrl_पढ़ोl(OMAP343X_CONTROL_MEM_DFTRW0);
	control_context.mem_dftrw1 =
			omap_ctrl_पढ़ोl(OMAP343X_CONTROL_MEM_DFTRW1);
	control_context.msuspendmux_0 =
			omap_ctrl_पढ़ोl(OMAP2_CONTROL_MSUSPENDMUX_0);
	control_context.msuspendmux_1 =
			omap_ctrl_पढ़ोl(OMAP2_CONTROL_MSUSPENDMUX_1);
	control_context.msuspendmux_2 =
			omap_ctrl_पढ़ोl(OMAP2_CONTROL_MSUSPENDMUX_2);
	control_context.msuspendmux_3 =
			omap_ctrl_पढ़ोl(OMAP2_CONTROL_MSUSPENDMUX_3);
	control_context.msuspendmux_4 =
			omap_ctrl_पढ़ोl(OMAP2_CONTROL_MSUSPENDMUX_4);
	control_context.msuspendmux_5 =
			omap_ctrl_पढ़ोl(OMAP2_CONTROL_MSUSPENDMUX_5);
	control_context.sec_ctrl = omap_ctrl_पढ़ोl(OMAP2_CONTROL_SEC_CTRL);
	control_context.devconf1 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_DEVCONF1);
	control_context.csirxfe = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_CSIRXFE);
	control_context.iva2_bootaddr =
			omap_ctrl_पढ़ोl(OMAP343X_CONTROL_IVA2_BOOTADDR);
	control_context.iva2_booपंचांगod =
			omap_ctrl_पढ़ोl(OMAP343X_CONTROL_IVA2_BOOTMOD);
	control_context.wkup_ctrl = omap_ctrl_पढ़ोl(OMAP34XX_CONTROL_WKUP_CTRL);
	control_context.debobs_0 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_DEBOBS(0));
	control_context.debobs_1 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_DEBOBS(1));
	control_context.debobs_2 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_DEBOBS(2));
	control_context.debobs_3 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_DEBOBS(3));
	control_context.debobs_4 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_DEBOBS(4));
	control_context.debobs_5 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_DEBOBS(5));
	control_context.debobs_6 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_DEBOBS(6));
	control_context.debobs_7 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_DEBOBS(7));
	control_context.debobs_8 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_DEBOBS(8));
	control_context.prog_io0 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_PROG_IO0);
	control_context.prog_io1 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_PROG_IO1);
	control_context.dss_dpll_spपढ़ोing =
			omap_ctrl_पढ़ोl(OMAP343X_CONTROL_DSS_DPLL_SPREADING);
	control_context.core_dpll_spपढ़ोing =
			omap_ctrl_पढ़ोl(OMAP343X_CONTROL_CORE_DPLL_SPREADING);
	control_context.per_dpll_spपढ़ोing =
			omap_ctrl_पढ़ोl(OMAP343X_CONTROL_PER_DPLL_SPREADING);
	control_context.usbhost_dpll_spपढ़ोing =
		omap_ctrl_पढ़ोl(OMAP343X_CONTROL_USBHOST_DPLL_SPREADING);
	control_context.pbias_lite =
			omap_ctrl_पढ़ोl(OMAP343X_CONTROL_PBIAS_LITE);
	control_context.temp_sensor =
			omap_ctrl_पढ़ोl(OMAP343X_CONTROL_TEMP_SENSOR);
	control_context.sramlकरो4 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_SRAMLDO4);
	control_context.sramlकरो5 = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_SRAMLDO5);
	control_context.csi = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_CSI);
	control_context.padconf_sys_nirq =
		omap_ctrl_पढ़ोl(OMAP343X_CONTROL_PADCONF_SYSNIRQ);
पूर्ण

व्योम omap3_control_restore_context(व्योम)
अणु
	omap_ctrl_ग_लिखोl(control_context.sysconfig, OMAP2_CONTROL_SYSCONFIG);
	omap_ctrl_ग_लिखोl(control_context.devconf0, OMAP2_CONTROL_DEVCONF0);
	omap_ctrl_ग_लिखोl(control_context.mem_dftrw0,
					OMAP343X_CONTROL_MEM_DFTRW0);
	omap_ctrl_ग_लिखोl(control_context.mem_dftrw1,
					OMAP343X_CONTROL_MEM_DFTRW1);
	omap_ctrl_ग_लिखोl(control_context.msuspendmux_0,
					OMAP2_CONTROL_MSUSPENDMUX_0);
	omap_ctrl_ग_लिखोl(control_context.msuspendmux_1,
					OMAP2_CONTROL_MSUSPENDMUX_1);
	omap_ctrl_ग_लिखोl(control_context.msuspendmux_2,
					OMAP2_CONTROL_MSUSPENDMUX_2);
	omap_ctrl_ग_लिखोl(control_context.msuspendmux_3,
					OMAP2_CONTROL_MSUSPENDMUX_3);
	omap_ctrl_ग_लिखोl(control_context.msuspendmux_4,
					OMAP2_CONTROL_MSUSPENDMUX_4);
	omap_ctrl_ग_लिखोl(control_context.msuspendmux_5,
					OMAP2_CONTROL_MSUSPENDMUX_5);
	omap_ctrl_ग_लिखोl(control_context.sec_ctrl, OMAP2_CONTROL_SEC_CTRL);
	omap_ctrl_ग_लिखोl(control_context.devconf1, OMAP343X_CONTROL_DEVCONF1);
	omap_ctrl_ग_लिखोl(control_context.csirxfe, OMAP343X_CONTROL_CSIRXFE);
	omap_ctrl_ग_लिखोl(control_context.iva2_bootaddr,
					OMAP343X_CONTROL_IVA2_BOOTADDR);
	omap_ctrl_ग_लिखोl(control_context.iva2_booपंचांगod,
					OMAP343X_CONTROL_IVA2_BOOTMOD);
	omap_ctrl_ग_लिखोl(control_context.wkup_ctrl, OMAP34XX_CONTROL_WKUP_CTRL);
	omap_ctrl_ग_लिखोl(control_context.debobs_0, OMAP343X_CONTROL_DEBOBS(0));
	omap_ctrl_ग_लिखोl(control_context.debobs_1, OMAP343X_CONTROL_DEBOBS(1));
	omap_ctrl_ग_लिखोl(control_context.debobs_2, OMAP343X_CONTROL_DEBOBS(2));
	omap_ctrl_ग_लिखोl(control_context.debobs_3, OMAP343X_CONTROL_DEBOBS(3));
	omap_ctrl_ग_लिखोl(control_context.debobs_4, OMAP343X_CONTROL_DEBOBS(4));
	omap_ctrl_ग_लिखोl(control_context.debobs_5, OMAP343X_CONTROL_DEBOBS(5));
	omap_ctrl_ग_लिखोl(control_context.debobs_6, OMAP343X_CONTROL_DEBOBS(6));
	omap_ctrl_ग_लिखोl(control_context.debobs_7, OMAP343X_CONTROL_DEBOBS(7));
	omap_ctrl_ग_लिखोl(control_context.debobs_8, OMAP343X_CONTROL_DEBOBS(8));
	omap_ctrl_ग_लिखोl(control_context.prog_io0, OMAP343X_CONTROL_PROG_IO0);
	omap_ctrl_ग_लिखोl(control_context.prog_io1, OMAP343X_CONTROL_PROG_IO1);
	omap_ctrl_ग_लिखोl(control_context.dss_dpll_spपढ़ोing,
					OMAP343X_CONTROL_DSS_DPLL_SPREADING);
	omap_ctrl_ग_लिखोl(control_context.core_dpll_spपढ़ोing,
					OMAP343X_CONTROL_CORE_DPLL_SPREADING);
	omap_ctrl_ग_लिखोl(control_context.per_dpll_spपढ़ोing,
					OMAP343X_CONTROL_PER_DPLL_SPREADING);
	omap_ctrl_ग_लिखोl(control_context.usbhost_dpll_spपढ़ोing,
				OMAP343X_CONTROL_USBHOST_DPLL_SPREADING);
	omap_ctrl_ग_लिखोl(control_context.pbias_lite,
					OMAP343X_CONTROL_PBIAS_LITE);
	omap_ctrl_ग_लिखोl(control_context.temp_sensor,
					OMAP343X_CONTROL_TEMP_SENSOR);
	omap_ctrl_ग_लिखोl(control_context.sramlकरो4, OMAP343X_CONTROL_SRAMLDO4);
	omap_ctrl_ग_लिखोl(control_context.sramlकरो5, OMAP343X_CONTROL_SRAMLDO5);
	omap_ctrl_ग_लिखोl(control_context.csi, OMAP343X_CONTROL_CSI);
	omap_ctrl_ग_लिखोl(control_context.padconf_sys_nirq,
			 OMAP343X_CONTROL_PADCONF_SYSNIRQ);
पूर्ण

व्योम omap3630_ctrl_disable_rta(व्योम)
अणु
	अगर (!cpu_is_omap3630())
		वापस;
	omap_ctrl_ग_लिखोl(OMAP36XX_RTA_DISABLE, OMAP36XX_CONTROL_MEM_RTA_CTRL);
पूर्ण

/**
 * omap3_ctrl_save_padconf - save padconf रेजिस्टरs to scratchpad RAM
 *
 * Tell the SCM to start saving the padconf रेजिस्टरs, then रुको क्रम
 * the process to complete.  Returns 0 unconditionally, although it
 * should also eventually be able to वापस -ETIMEDOUT, अगर the save
 * करोes not complete.
 *
 * XXX This function is missing a समयout.  What should it be?
 */
पूर्णांक omap3_ctrl_save_padconf(व्योम)
अणु
	u32 cpo;

	/* Save the padconf रेजिस्टरs */
	cpo = omap_ctrl_पढ़ोl(OMAP343X_CONTROL_PADCONF_OFF);
	cpo |= START_PADCONF_SAVE;
	omap_ctrl_ग_लिखोl(cpo, OMAP343X_CONTROL_PADCONF_OFF);

	/* रुको क्रम the save to complete */
	जबतक (!(omap_ctrl_पढ़ोl(OMAP343X_CONTROL_GENERAL_PURPOSE_STATUS)
		 & PADCONF_SAVE_DONE))
		udelay(1);

	वापस 0;
पूर्ण

/**
 * omap3_ctrl_set_iva_booपंचांगode_idle - sets the IVA2 booपंचांगode to idle
 *
 * Sets the booपंचांगode क्रम IVA2 to idle. This is needed by the PM code to
 * क्रमce disable IVA2 so that it करोes not prevent any low-घातer states.
 */
अटल व्योम __init omap3_ctrl_set_iva_booपंचांगode_idle(व्योम)
अणु
	omap_ctrl_ग_लिखोl(OMAP3_IVA2_BOOTMOD_IDLE,
			 OMAP343X_CONTROL_IVA2_BOOTMOD);
पूर्ण

/**
 * omap3_ctrl_setup_d2d_padconf - setup stacked modem pads क्रम idle
 *
 * Sets up the pads controlling the stacked modem in such way that the
 * device can enter idle.
 */
अटल व्योम __init omap3_ctrl_setup_d2d_padconf(व्योम)
अणु
	u16 mask, padconf;

	/*
	 * In a stand alone OMAP3430 where there is not a stacked
	 * modem क्रम the D2D Idle Ack and D2D MStandby must be pulled
	 * high. S CONTROL_PADCONF_SAD2D_IDLEACK and
	 * CONTROL_PADCONF_SAD2D_MSTDBY to have a pull up.
	 */
	mask = (1 << 4) | (1 << 3); /* pull-up, enabled */
	padconf = omap_ctrl_पढ़ोw(OMAP3_PADCONF_SAD2D_MSTANDBY);
	padconf |= mask;
	omap_ctrl_ग_लिखोw(padconf, OMAP3_PADCONF_SAD2D_MSTANDBY);

	padconf = omap_ctrl_पढ़ोw(OMAP3_PADCONF_SAD2D_IDLEACK);
	padconf |= mask;
	omap_ctrl_ग_लिखोw(padconf, OMAP3_PADCONF_SAD2D_IDLEACK);
पूर्ण

/**
 * omap3_ctrl_init - करोes अटल initializations क्रम control module
 *
 * Initializes प्रणाली control module. This sets up the sysconfig स्वतःidle,
 * and sets up modem and iva2 so that they can be idled properly.
 */
व्योम __init omap3_ctrl_init(व्योम)
अणु
	omap_ctrl_ग_लिखोl(OMAP3430_AUTOIDLE_MASK, OMAP2_CONTROL_SYSCONFIG);

	omap3_ctrl_set_iva_booपंचांगode_idle();

	omap3_ctrl_setup_d2d_padconf();
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_OMAP3 && CONFIG_PM */

अटल अचिन्हित दीर्घ am43xx_control_reg_offsets[] = अणु
	AM33XX_CONTROL_SYSCONFIG_OFFSET,
	AM33XX_CONTROL_STATUS_OFFSET,
	AM43XX_CONTROL_MPU_L2_CTRL_OFFSET,
	AM33XX_CONTROL_CORE_SLDO_CTRL_OFFSET,
	AM33XX_CONTROL_MPU_SLDO_CTRL_OFFSET,
	AM33XX_CONTROL_CLK32KDIVRATIO_CTRL_OFFSET,
	AM33XX_CONTROL_BANDGAP_CTRL_OFFSET,
	AM33XX_CONTROL_BANDGAP_TRIM_OFFSET,
	AM33XX_CONTROL_PLL_CLKINPULOW_CTRL_OFFSET,
	AM33XX_CONTROL_MOSC_CTRL_OFFSET,
	AM33XX_CONTROL_DEEPSLEEP_CTRL_OFFSET,
	AM43XX_CONTROL_DISPLAY_PLL_SEL_OFFSET,
	AM33XX_CONTROL_INIT_PRIORITY_0_OFFSET,
	AM33XX_CONTROL_INIT_PRIORITY_1_OFFSET,
	AM33XX_CONTROL_TPTC_CFG_OFFSET,
	AM33XX_CONTROL_USB_CTRL0_OFFSET,
	AM33XX_CONTROL_USB_CTRL1_OFFSET,
	AM43XX_CONTROL_USB_CTRL2_OFFSET,
	AM43XX_CONTROL_GMII_SEL_OFFSET,
	AM43XX_CONTROL_MPUSS_CTRL_OFFSET,
	AM43XX_CONTROL_TIMER_CASCADE_CTRL_OFFSET,
	AM43XX_CONTROL_PWMSS_CTRL_OFFSET,
	AM33XX_CONTROL_MREQPRIO_0_OFFSET,
	AM33XX_CONTROL_MREQPRIO_1_OFFSET,
	AM33XX_CONTROL_HW_EVENT_SEL_GRP1_OFFSET,
	AM33XX_CONTROL_HW_EVENT_SEL_GRP2_OFFSET,
	AM33XX_CONTROL_HW_EVENT_SEL_GRP3_OFFSET,
	AM33XX_CONTROL_HW_EVENT_SEL_GRP4_OFFSET,
	AM33XX_CONTROL_SMRT_CTRL_OFFSET,
	AM33XX_CONTROL_MPUSS_HW_DEBUG_SEL_OFFSET,
	AM43XX_CONTROL_CQDETECT_STS_OFFSET,
	AM43XX_CONTROL_CQDETECT_STS2_OFFSET,
	AM43XX_CONTROL_VTP_CTRL_OFFSET,
	AM33XX_CONTROL_VREF_CTRL_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_0_3_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_4_7_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_8_11_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_12_15_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_16_19_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_20_23_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_24_27_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_28_31_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_32_35_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_36_39_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_40_43_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_44_47_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_48_51_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_52_55_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_56_59_OFFSET,
	AM33XX_CONTROL_TPCC_EVT_MUX_60_63_OFFSET,
	AM33XX_CONTROL_TIMER_EVT_CAPT_OFFSET,
	AM33XX_CONTROL_ECAP_EVT_CAPT_OFFSET,
	AM33XX_CONTROL_ADC_EVT_CAPT_OFFSET,
	AM43XX_CONTROL_ADC1_EVT_CAPT_OFFSET,
	AM33XX_CONTROL_RESET_ISO_OFFSET,
पूर्ण;

अटल u32 am33xx_control_vals[ARRAY_SIZE(am43xx_control_reg_offsets)];

/**
 * am43xx_control_save_context - Save the wakeup करोमुख्य रेजिस्टरs
 *
 * Save the wkup करोमुख्य रेजिस्टरs
 */
अटल व्योम am43xx_control_save_context(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(am43xx_control_reg_offsets); i++)
		am33xx_control_vals[i] =
				omap_ctrl_पढ़ोl(am43xx_control_reg_offsets[i]);
पूर्ण

/**
 * am43xx_control_restore_context - Restore the wakeup करोमुख्य रेजिस्टरs
 *
 * Restore the wkup करोमुख्य रेजिस्टरs
 */
अटल व्योम am43xx_control_restore_context(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(am43xx_control_reg_offsets); i++)
		omap_ctrl_ग_लिखोl(am33xx_control_vals[i],
				 am43xx_control_reg_offsets[i]);
पूर्ण

अटल पूर्णांक cpu_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_CLUSTER_PM_ENTER:
		अगर (enable_off_mode)
			am43xx_control_save_context();
		अवरोध;
	हाल CPU_CLUSTER_PM_EXIT:
		अगर (enable_off_mode)
			am43xx_control_restore_context();
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

काष्ठा control_init_data अणु
	पूर्णांक index;
	व्योम __iomem *mem;
	s16 offset;
पूर्ण;

अटल काष्ठा control_init_data ctrl_data = अणु
	.index = TI_CLKM_CTRL,
पूर्ण;

अटल स्थिर काष्ठा control_init_data omap2_ctrl_data = अणु
	.index = TI_CLKM_CTRL,
	.offset = -OMAP2_CONTROL_GENERAL,
पूर्ण;

अटल स्थिर काष्ठा control_init_data ctrl_aux_data = अणु
	.index = TI_CLKM_CTRL_AUX,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_scrm_dt_match_table[] = अणु
	अणु .compatible = "ti,am3-scm", .data = &ctrl_data पूर्ण,
	अणु .compatible = "ti,am4-scm", .data = &ctrl_data पूर्ण,
	अणु .compatible = "ti,omap2-scm", .data = &omap2_ctrl_data पूर्ण,
	अणु .compatible = "ti,omap3-scm", .data = &omap2_ctrl_data पूर्ण,
	अणु .compatible = "ti,dm814-scm", .data = &ctrl_data पूर्ण,
	अणु .compatible = "ti,dm816-scrm", .data = &ctrl_data पूर्ण,
	अणु .compatible = "ti,omap4-scm-core", .data = &ctrl_data पूर्ण,
	अणु .compatible = "ti,omap5-scm-core", .data = &ctrl_data पूर्ण,
	अणु .compatible = "ti,omap5-scm-wkup-pad-conf", .data = &ctrl_aux_data पूर्ण,
	अणु .compatible = "ti,dra7-scm-core", .data = &ctrl_data पूर्ण,
	अणु पूर्ण
पूर्ण;

/**
 * omap2_control_base_init - initialize iomappings क्रम the control driver
 *
 * Detects and initializes the iomappings क्रम the control driver, based
 * on the DT data. Returns 0 in success, negative error value
 * otherwise.
 */
पूर्णांक __init omap2_control_base_init(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा control_init_data *data;
	व्योम __iomem *mem;

	क्रम_each_matching_node_and_match(np, omap_scrm_dt_match_table, &match) अणु
		data = (काष्ठा control_init_data *)match->data;

		mem = of_iomap(np, 0);
		अगर (!mem)
			वापस -ENOMEM;

		अगर (data->index == TI_CLKM_CTRL) अणु
			omap2_ctrl_base = mem;
			omap2_ctrl_offset = data->offset;
		पूर्ण

		data->mem = mem;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * omap_control_init - low level init क्रम the control driver
 *
 * Initializes the low level घड़ी infraकाष्ठाure क्रम control driver.
 * Returns 0 in success, negative error value in failure.
 */
पूर्णांक __init omap_control_init(व्योम)
अणु
	काष्ठा device_node *np, *scm_conf;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा omap_prcm_init_data *data;
	पूर्णांक ret;
	काष्ठा regmap *syscon;
	अटल काष्ठा notअगरier_block nb;

	क्रम_each_matching_node_and_match(np, omap_scrm_dt_match_table, &match) अणु
		data = match->data;

		/*
		 * Check अगर we have scm_conf node, अगर yes, use this to
		 * access घड़ी रेजिस्टरs.
		 */
		scm_conf = of_get_child_by_name(np, "scm_conf");

		अगर (scm_conf) अणु
			syscon = syscon_node_to_regmap(scm_conf);

			अगर (IS_ERR(syscon))
				वापस PTR_ERR(syscon);

			अगर (of_get_child_by_name(scm_conf, "clocks")) अणु
				ret = omap2_clk_provider_init(scm_conf,
							      data->index,
							      syscon, शून्य);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* No scm_conf found, direct access */
			ret = omap2_clk_provider_init(np, data->index, शून्य,
						      data->mem);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Only AM43XX can lose ctrl रेजिस्टरs context during rtc-ddr suspend */
	अगर (soc_is_am43xx()) अणु
		nb.notअगरier_call = cpu_notअगरier;
		cpu_pm_रेजिस्टर_notअगरier(&nb);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * omap3_control_legacy_iomap_init - legacy iomap init क्रम घड़ी providers
 *
 * Legacy iomap init क्रम घड़ी provider. Needed only by legacy boot mode,
 * where the base addresses are not parsed from DT, but still required
 * by the घड़ी driver to be setup properly.
 */
व्योम __init omap3_control_legacy_iomap_init(व्योम)
अणु
	omap2_clk_legacy_provider_init(TI_CLKM_SCRM, omap2_ctrl_base);
पूर्ण
