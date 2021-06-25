<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * EMIF driver
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Aneesh V <aneesh@ti.com>
 * Santosh Shilimkar <santosh.shilimkar@ti.com>
 */
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/reboot.h>
#समावेश <linux/platक्रमm_data/emअगर_plat.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pm.h>

#समावेश "emif.h"
#समावेश "jedec_ddr.h"
#समावेश "of_memory.h"

/**
 * काष्ठा emअगर_data - Per device अटल data क्रम driver's use
 * @duplicate:			Whether the DDR devices attached to this EMIF
 *				instance are exactly same as that on EMIF1. In
 *				this हाल we can save some memory and processing
 * @temperature_level:		Maximum temperature of LPDDR2 devices attached
 *				to this EMIF - पढ़ो from MR4 रेजिस्टर. If there
 *				are two devices attached to this EMIF, this
 *				value is the maximum of the two temperature
 *				levels.
 * @node:			node in the device list
 * @base:			base address of memory-mapped IO रेजिस्टरs.
 * @dev:			device poपूर्णांकer.
 * @addressing			table with addressing inक्रमmation from the spec
 * @regs_cache:			An array of 'struct emif_regs' that stores
 *				calculated रेजिस्टर values क्रम dअगरferent
 *				frequencies, to aव्योम re-calculating them on
 *				each DVFS transition.
 * @curr_regs:			The set of रेजिस्टर values used in the last
 *				frequency change (i.e. corresponding to the
 *				frequency in effect at the moment)
 * @plat_data:			Poपूर्णांकer to saved platक्रमm data.
 * @debugfs_root:		dentry to the root folder क्रम EMIF in debugfs
 * @np_ddr:			Poपूर्णांकer to ddr device tree node
 */
काष्ठा emअगर_data अणु
	u8				duplicate;
	u8				temperature_level;
	u8				lpmode;
	काष्ठा list_head		node;
	अचिन्हित दीर्घ			irq_state;
	व्योम __iomem			*base;
	काष्ठा device			*dev;
	स्थिर काष्ठा lpddr2_addressing	*addressing;
	काष्ठा emअगर_regs		*regs_cache[EMIF_MAX_NUM_FREQUENCIES];
	काष्ठा emअगर_regs		*curr_regs;
	काष्ठा emअगर_platक्रमm_data	*plat_data;
	काष्ठा dentry			*debugfs_root;
	काष्ठा device_node		*np_ddr;
पूर्ण;

अटल काष्ठा emअगर_data *emअगर1;
अटल DEFINE_SPINLOCK(emअगर_lock);
अटल अचिन्हित दीर्घ	irq_state;
अटल u32		t_ck; /* DDR घड़ी period in ps */
अटल LIST_HEAD(device_list);

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम करो_emअगर_regdump_show(काष्ठा seq_file *s, काष्ठा emअगर_data *emअगर,
	काष्ठा emअगर_regs *regs)
अणु
	u32 type = emअगर->plat_data->device_info->type;
	u32 ip_rev = emअगर->plat_data->ip_rev;

	seq_म_लिखो(s, "EMIF register cache dump for %dMHz\n",
		regs->freq/1000000);

	seq_म_लिखो(s, "ref_ctrl_shdw\t: 0x%08x\n", regs->ref_ctrl_shdw);
	seq_म_लिखो(s, "sdram_tim1_shdw\t: 0x%08x\n", regs->sdram_tim1_shdw);
	seq_म_लिखो(s, "sdram_tim2_shdw\t: 0x%08x\n", regs->sdram_tim2_shdw);
	seq_म_लिखो(s, "sdram_tim3_shdw\t: 0x%08x\n", regs->sdram_tim3_shdw);

	अगर (ip_rev == EMIF_4D) अणु
		seq_म_लिखो(s, "read_idle_ctrl_shdw_normal\t: 0x%08x\n",
			regs->पढ़ो_idle_ctrl_shdw_normal);
		seq_म_लिखो(s, "read_idle_ctrl_shdw_volt_ramp\t: 0x%08x\n",
			regs->पढ़ो_idle_ctrl_shdw_volt_ramp);
	पूर्ण अन्यथा अगर (ip_rev == EMIF_4D5) अणु
		seq_म_लिखो(s, "dll_calib_ctrl_shdw_normal\t: 0x%08x\n",
			regs->dll_calib_ctrl_shdw_normal);
		seq_म_लिखो(s, "dll_calib_ctrl_shdw_volt_ramp\t: 0x%08x\n",
			regs->dll_calib_ctrl_shdw_volt_ramp);
	पूर्ण

	अगर (type == DDR_TYPE_LPDDR2_S2 || type == DDR_TYPE_LPDDR2_S4) अणु
		seq_म_लिखो(s, "ref_ctrl_shdw_derated\t: 0x%08x\n",
			regs->ref_ctrl_shdw_derated);
		seq_म_लिखो(s, "sdram_tim1_shdw_derated\t: 0x%08x\n",
			regs->sdram_tim1_shdw_derated);
		seq_म_लिखो(s, "sdram_tim3_shdw_derated\t: 0x%08x\n",
			regs->sdram_tim3_shdw_derated);
	पूर्ण
पूर्ण

अटल पूर्णांक emअगर_regdump_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा emअगर_data	*emअगर	= s->निजी;
	काष्ठा emअगर_regs	**regs_cache;
	पूर्णांक			i;

	अगर (emअगर->duplicate)
		regs_cache = emअगर1->regs_cache;
	अन्यथा
		regs_cache = emअगर->regs_cache;

	क्रम (i = 0; i < EMIF_MAX_NUM_FREQUENCIES && regs_cache[i]; i++) अणु
		करो_emअगर_regdump_show(s, emअगर, regs_cache[i]);
		seq_अ_दो(s, '\n');
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(emअगर_regdump);

अटल पूर्णांक emअगर_mr4_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा emअगर_data *emअगर = s->निजी;

	seq_म_लिखो(s, "MR4=%d\n", emअगर->temperature_level);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(emअगर_mr4);

अटल पूर्णांक __init_or_module emअगर_debugfs_init(काष्ठा emअगर_data *emअगर)
अणु
	emअगर->debugfs_root = debugfs_create_dir(dev_name(emअगर->dev), शून्य);
	debugfs_create_file("regcache_dump", S_IRUGO, emअगर->debugfs_root, emअगर,
			    &emअगर_regdump_fops);
	debugfs_create_file("mr4", S_IRUGO, emअगर->debugfs_root, emअगर,
			    &emअगर_mr4_fops);
	वापस 0;
पूर्ण

अटल व्योम __निकास emअगर_debugfs_निकास(काष्ठा emअगर_data *emअगर)
अणु
	debugfs_हटाओ_recursive(emअगर->debugfs_root);
	emअगर->debugfs_root = शून्य;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक __init_or_module emअगर_debugfs_init(काष्ठा emअगर_data *emअगर)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __निकास emअगर_debugfs_निकास(काष्ठा emअगर_data *emअगर)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Calculate the period of DDR घड़ी from frequency value
 */
अटल व्योम set_ddr_clk_period(u32 freq)
अणु
	/* Divide 10^12 by frequency to get period in ps */
	t_ck = (u32)DIV_ROUND_UP_ULL(1000000000000ull, freq);
पूर्ण

/*
 * Get bus width used by EMIF. Note that this may be dअगरferent from the
 * bus width of the DDR devices used. For instance two 16-bit DDR devices
 * may be connected to a given CS of EMIF. In this हाल bus width as far
 * as EMIF is concerned is 32, where as the DDR bus width is 16 bits.
 */
अटल u32 get_emअगर_bus_width(काष्ठा emअगर_data *emअगर)
अणु
	u32		width;
	व्योम __iomem	*base = emअगर->base;

	width = (पढ़ोl(base + EMIF_SDRAM_CONFIG) & NARROW_MODE_MASK)
			>> NARROW_MODE_SHIFT;
	width = width == 0 ? 32 : 16;

	वापस width;
पूर्ण

/*
 * Get the CL from SDRAM_CONFIG रेजिस्टर
 */
अटल u32 get_cl(काष्ठा emअगर_data *emअगर)
अणु
	u32		cl;
	व्योम __iomem	*base = emअगर->base;

	cl = (पढ़ोl(base + EMIF_SDRAM_CONFIG) & CL_MASK) >> CL_SHIFT;

	वापस cl;
पूर्ण

अटल व्योम set_lpmode(काष्ठा emअगर_data *emअगर, u8 lpmode)
अणु
	u32 temp;
	व्योम __iomem *base = emअगर->base;

	/*
	 * Workaround क्रम errata i743 - LPDDR2 Power-Down State is Not
	 * Efficient
	 *
	 * i743 DESCRIPTION:
	 * The EMIF supports घातer-करोwn state क्रम low घातer. The EMIF
	 * स्वतःmatically माला_दो the SDRAM पूर्णांकo घातer-करोwn after the memory is
	 * not accessed क्रम a defined number of cycles and the
	 * EMIF_PWR_MGMT_CTRL[10:8] REG_LP_MODE bit field is set to 0x4.
	 * As the EMIF supports स्वतःmatic output impedance calibration, a ZQ
	 * calibration दीर्घ command is issued every समय it निकासs active
	 * घातer-करोwn and preअक्षरge घातer-करोwn modes. The EMIF रुकोs and
	 * blocks any other command during this calibration.
	 * The EMIF करोes not allow selective disabling of ZQ calibration upon
	 * निकास of घातer-करोwn mode. Due to very लघु periods of घातer-करोwn
	 * cycles, ZQ calibration overhead creates bandwidth issues and
	 * increases overall प्रणाली घातer consumption. On the other hand,
	 * issuing ZQ calibration दीर्घ commands when निकासing self-refresh is
	 * still required.
	 *
	 * WORKAROUND
	 * Because there is no घातer consumption benefit of the घातer-करोwn due
	 * to the calibration and there is a perक्रमmance risk, the guideline
	 * is to not allow घातer-करोwn state and, thereक्रमe, to not have set
	 * the EMIF_PWR_MGMT_CTRL[10:8] REG_LP_MODE bit field to 0x4.
	 */
	अगर ((emअगर->plat_data->ip_rev == EMIF_4D) &&
	    (lpmode == EMIF_LP_MODE_PWR_DN)) अणु
		WARN_ONCE(1,
			  "REG_LP_MODE = LP_MODE_PWR_DN(4) is prohibited by erratum i743 switch to LP_MODE_SELF_REFRESH(2)\n");
		/* rollback LP_MODE to Self-refresh mode */
		lpmode = EMIF_LP_MODE_SELF_REFRESH;
	पूर्ण

	temp = पढ़ोl(base + EMIF_POWER_MANAGEMENT_CONTROL);
	temp &= ~LP_MODE_MASK;
	temp |= (lpmode << LP_MODE_SHIFT);
	ग_लिखोl(temp, base + EMIF_POWER_MANAGEMENT_CONTROL);
पूर्ण

अटल व्योम करो_freq_update(व्योम)
अणु
	काष्ठा emअगर_data *emअगर;

	/*
	 * Workaround क्रम errata i728: Disable LPMODE during FREQ_UPDATE
	 *
	 * i728 DESCRIPTION:
	 * The EMIF स्वतःmatically माला_दो the SDRAM पूर्णांकo self-refresh mode
	 * after the EMIF has not perक्रमmed accesses during
	 * EMIF_PWR_MGMT_CTRL[7:4] REG_SR_TIM number of DDR घड़ी cycles
	 * and the EMIF_PWR_MGMT_CTRL[10:8] REG_LP_MODE bit field is set
	 * to 0x2. If during a small winकरोw the following three events
	 * occur:
	 * - The SR_TIMING counter expires
	 * - And frequency change is requested
	 * - And OCP access is requested
	 * Then it causes instable घड़ी on the DDR पूर्णांकerface.
	 *
	 * WORKAROUND
	 * To aव्योम the occurrence of the three events, the workaround
	 * is to disable the self-refresh when requesting a frequency
	 * change. Beक्रमe requesting a frequency change the software must
	 * program EMIF_PWR_MGMT_CTRL[10:8] REG_LP_MODE to 0x0. When the
	 * frequency change has been करोne, the software can reprogram
	 * EMIF_PWR_MGMT_CTRL[10:8] REG_LP_MODE to 0x2
	 */
	list_क्रम_each_entry(emअगर, &device_list, node) अणु
		अगर (emअगर->lpmode == EMIF_LP_MODE_SELF_REFRESH)
			set_lpmode(emअगर, EMIF_LP_MODE_DISABLE);
	पूर्ण

	/*
	 * TODO: Do FREQ_UPDATE here when an API
	 * is available क्रम this as part of the new
	 * घड़ी framework
	 */

	list_क्रम_each_entry(emअगर, &device_list, node) अणु
		अगर (emअगर->lpmode == EMIF_LP_MODE_SELF_REFRESH)
			set_lpmode(emअगर, EMIF_LP_MODE_SELF_REFRESH);
	पूर्ण
पूर्ण

/* Find addressing table entry based on the device's type and density */
अटल स्थिर काष्ठा lpddr2_addressing *get_addressing_table(
	स्थिर काष्ठा ddr_device_info *device_info)
अणु
	u32		index, type, density;

	type = device_info->type;
	density = device_info->density;

	चयन (type) अणु
	हाल DDR_TYPE_LPDDR2_S4:
		index = density - 1;
		अवरोध;
	हाल DDR_TYPE_LPDDR2_S2:
		चयन (density) अणु
		हाल DDR_DENSITY_1Gb:
		हाल DDR_DENSITY_2Gb:
			index = density + 3;
			अवरोध;
		शेष:
			index = density - 1;
		पूर्ण
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	वापस &lpddr2_jedec_addressing_table[index];
पूर्ण

/*
 * Find the the right timing table from the array of timing
 * tables of the device using DDR घड़ी frequency
 */
अटल स्थिर काष्ठा lpddr2_timings *get_timings_table(काष्ठा emअगर_data *emअगर,
		u32 freq)
अणु
	u32				i, min, max, freq_nearest;
	स्थिर काष्ठा lpddr2_timings	*timings = शून्य;
	स्थिर काष्ठा lpddr2_timings	*timings_arr = emअगर->plat_data->timings;
	काष्ठा				device *dev = emअगर->dev;

	/* Start with a very high frequency - 1GHz */
	freq_nearest = 1000000000;

	/*
	 * Find the timings table such that:
	 *  1. the frequency range covers the required frequency(safe) AND
	 *  2. the max_freq is बंदst to the required frequency(optimal)
	 */
	क्रम (i = 0; i < emअगर->plat_data->timings_arr_size; i++) अणु
		max = timings_arr[i].max_freq;
		min = timings_arr[i].min_freq;
		अगर ((freq >= min) && (freq <= max) && (max < freq_nearest)) अणु
			freq_nearest = max;
			timings = &timings_arr[i];
		पूर्ण
	पूर्ण

	अगर (!timings)
		dev_err(dev, "%s: couldn't find timings for - %dHz\n",
			__func__, freq);

	dev_dbg(dev, "%s: timings table: freq %d, speed bin freq %d\n",
		__func__, freq, freq_nearest);

	वापस timings;
पूर्ण

अटल u32 get_sdram_ref_ctrl_shdw(u32 freq,
		स्थिर काष्ठा lpddr2_addressing *addressing)
अणु
	u32 ref_ctrl_shdw = 0, val = 0, freq_khz, t_refi;

	/* Scale करोwn frequency and t_refi to aव्योम overflow */
	freq_khz = freq / 1000;
	t_refi = addressing->tREFI_ns / 100;

	/*
	 * refresh rate to be set is 'tREFI(in us) * freq in MHz
	 * भागision by 10000 to account क्रम change in units
	 */
	val = t_refi * freq_khz / 10000;
	ref_ctrl_shdw |= val << REFRESH_RATE_SHIFT;

	वापस ref_ctrl_shdw;
पूर्ण

अटल u32 get_sdram_tim_1_shdw(स्थिर काष्ठा lpddr2_timings *timings,
		स्थिर काष्ठा lpddr2_min_tck *min_tck,
		स्थिर काष्ठा lpddr2_addressing *addressing)
अणु
	u32 tim1 = 0, val = 0;

	val = max(min_tck->tWTR, DIV_ROUND_UP(timings->tWTR, t_ck)) - 1;
	tim1 |= val << T_WTR_SHIFT;

	अगर (addressing->num_banks == B8)
		val = DIV_ROUND_UP(timings->tFAW, t_ck*4);
	अन्यथा
		val = max(min_tck->tRRD, DIV_ROUND_UP(timings->tRRD, t_ck));
	tim1 |= (val - 1) << T_RRD_SHIFT;

	val = DIV_ROUND_UP(timings->tRAS_min + timings->tRPab, t_ck) - 1;
	tim1 |= val << T_RC_SHIFT;

	val = max(min_tck->tRASmin, DIV_ROUND_UP(timings->tRAS_min, t_ck));
	tim1 |= (val - 1) << T_RAS_SHIFT;

	val = max(min_tck->tWR, DIV_ROUND_UP(timings->tWR, t_ck)) - 1;
	tim1 |= val << T_WR_SHIFT;

	val = max(min_tck->tRCD, DIV_ROUND_UP(timings->tRCD, t_ck)) - 1;
	tim1 |= val << T_RCD_SHIFT;

	val = max(min_tck->tRPab, DIV_ROUND_UP(timings->tRPab, t_ck)) - 1;
	tim1 |= val << T_RP_SHIFT;

	वापस tim1;
पूर्ण

अटल u32 get_sdram_tim_1_shdw_derated(स्थिर काष्ठा lpddr2_timings *timings,
		स्थिर काष्ठा lpddr2_min_tck *min_tck,
		स्थिर काष्ठा lpddr2_addressing *addressing)
अणु
	u32 tim1 = 0, val = 0;

	val = max(min_tck->tWTR, DIV_ROUND_UP(timings->tWTR, t_ck)) - 1;
	tim1 = val << T_WTR_SHIFT;

	/*
	 * tFAW is approximately 4 बार tRRD. So add 1875*4 = 7500ps
	 * to tFAW क्रम de-rating
	 */
	अगर (addressing->num_banks == B8) अणु
		val = DIV_ROUND_UP(timings->tFAW + 7500, 4 * t_ck) - 1;
	पूर्ण अन्यथा अणु
		val = DIV_ROUND_UP(timings->tRRD + 1875, t_ck);
		val = max(min_tck->tRRD, val) - 1;
	पूर्ण
	tim1 |= val << T_RRD_SHIFT;

	val = DIV_ROUND_UP(timings->tRAS_min + timings->tRPab + 1875, t_ck);
	tim1 |= (val - 1) << T_RC_SHIFT;

	val = DIV_ROUND_UP(timings->tRAS_min + 1875, t_ck);
	val = max(min_tck->tRASmin, val) - 1;
	tim1 |= val << T_RAS_SHIFT;

	val = max(min_tck->tWR, DIV_ROUND_UP(timings->tWR, t_ck)) - 1;
	tim1 |= val << T_WR_SHIFT;

	val = max(min_tck->tRCD, DIV_ROUND_UP(timings->tRCD + 1875, t_ck));
	tim1 |= (val - 1) << T_RCD_SHIFT;

	val = max(min_tck->tRPab, DIV_ROUND_UP(timings->tRPab + 1875, t_ck));
	tim1 |= (val - 1) << T_RP_SHIFT;

	वापस tim1;
पूर्ण

अटल u32 get_sdram_tim_2_shdw(स्थिर काष्ठा lpddr2_timings *timings,
		स्थिर काष्ठा lpddr2_min_tck *min_tck,
		स्थिर काष्ठा lpddr2_addressing *addressing,
		u32 type)
अणु
	u32 tim2 = 0, val = 0;

	val = min_tck->tCKE - 1;
	tim2 |= val << T_CKE_SHIFT;

	val = max(min_tck->tRTP, DIV_ROUND_UP(timings->tRTP, t_ck)) - 1;
	tim2 |= val << T_RTP_SHIFT;

	/* tXSNR = tRFCab_ps + 10 ns(tRFCab_ps क्रम LPDDR2). */
	val = DIV_ROUND_UP(addressing->tRFCab_ps + 10000, t_ck) - 1;
	tim2 |= val << T_XSNR_SHIFT;

	/* XSRD same as XSNR क्रम LPDDR2 */
	tim2 |= val << T_XSRD_SHIFT;

	val = max(min_tck->tXP, DIV_ROUND_UP(timings->tXP, t_ck)) - 1;
	tim2 |= val << T_XP_SHIFT;

	वापस tim2;
पूर्ण

अटल u32 get_sdram_tim_3_shdw(स्थिर काष्ठा lpddr2_timings *timings,
		स्थिर काष्ठा lpddr2_min_tck *min_tck,
		स्थिर काष्ठा lpddr2_addressing *addressing,
		u32 type, u32 ip_rev, u32 derated)
अणु
	u32 tim3 = 0, val = 0, t_dqsck;

	val = timings->tRAS_max_ns / addressing->tREFI_ns - 1;
	val = val > 0xF ? 0xF : val;
	tim3 |= val << T_RAS_MAX_SHIFT;

	val = DIV_ROUND_UP(addressing->tRFCab_ps, t_ck) - 1;
	tim3 |= val << T_RFC_SHIFT;

	t_dqsck = (derated == EMIF_DERATED_TIMINGS) ?
		timings->tDQSCK_max_derated : timings->tDQSCK_max;
	अगर (ip_rev == EMIF_4D5)
		val = DIV_ROUND_UP(t_dqsck + 1000, t_ck) - 1;
	अन्यथा
		val = DIV_ROUND_UP(t_dqsck, t_ck) - 1;

	tim3 |= val << T_TDQSCKMAX_SHIFT;

	val = DIV_ROUND_UP(timings->tZQCS, t_ck) - 1;
	tim3 |= val << ZQ_ZQCS_SHIFT;

	val = DIV_ROUND_UP(timings->tCKESR, t_ck);
	val = max(min_tck->tCKESR, val) - 1;
	tim3 |= val << T_CKESR_SHIFT;

	अगर (ip_rev == EMIF_4D5) अणु
		tim3 |= (EMIF_T_CSTA - 1) << T_CSTA_SHIFT;

		val = DIV_ROUND_UP(EMIF_T_PDLL_UL, 128) - 1;
		tim3 |= val << T_PDLL_UL_SHIFT;
	पूर्ण

	वापस tim3;
पूर्ण

अटल u32 get_zq_config_reg(स्थिर काष्ठा lpddr2_addressing *addressing,
		bool cs1_used, bool cal_resistors_per_cs)
अणु
	u32 zq = 0, val = 0;

	val = EMIF_ZQCS_INTERVAL_US * 1000 / addressing->tREFI_ns;
	zq |= val << ZQ_REFINTERVAL_SHIFT;

	val = DIV_ROUND_UP(T_ZQCL_DEFAULT_NS, T_ZQCS_DEFAULT_NS) - 1;
	zq |= val << ZQ_ZQCL_MULT_SHIFT;

	val = DIV_ROUND_UP(T_ZQINIT_DEFAULT_NS, T_ZQCL_DEFAULT_NS) - 1;
	zq |= val << ZQ_ZQINIT_MULT_SHIFT;

	zq |= ZQ_SFEXITEN_ENABLE << ZQ_SFEXITEN_SHIFT;

	अगर (cal_resistors_per_cs)
		zq |= ZQ_DUALCALEN_ENABLE << ZQ_DUALCALEN_SHIFT;
	अन्यथा
		zq |= ZQ_DUALCALEN_DISABLE << ZQ_DUALCALEN_SHIFT;

	zq |= ZQ_CS0EN_MASK; /* CS0 is used क्रम sure */

	val = cs1_used ? 1 : 0;
	zq |= val << ZQ_CS1EN_SHIFT;

	वापस zq;
पूर्ण

अटल u32 get_temp_alert_config(स्थिर काष्ठा lpddr2_addressing *addressing,
		स्थिर काष्ठा emअगर_custom_configs *custom_configs, bool cs1_used,
		u32 sdram_io_width, u32 emअगर_bus_width)
अणु
	u32 alert = 0, पूर्णांकerval, devcnt;

	अगर (custom_configs && (custom_configs->mask &
				EMIF_CUSTOM_CONFIG_TEMP_ALERT_POLL_INTERVAL))
		पूर्णांकerval = custom_configs->temp_alert_poll_पूर्णांकerval_ms;
	अन्यथा
		पूर्णांकerval = TEMP_ALERT_POLL_INTERVAL_DEFAULT_MS;

	पूर्णांकerval *= 1000000;			/* Convert to ns */
	पूर्णांकerval /= addressing->tREFI_ns;	/* Convert to refresh cycles */
	alert |= (पूर्णांकerval << TA_REFINTERVAL_SHIFT);

	/*
	 * sdram_io_width is in 'log2(x) - 1' क्रमm. Convert emअगर_bus_width
	 * also to this क्रमm and subtract to get TA_DEVCNT, which is
	 * in log2(x) क्रमm.
	 */
	emअगर_bus_width = __fls(emअगर_bus_width) - 1;
	devcnt = emअगर_bus_width - sdram_io_width;
	alert |= devcnt << TA_DEVCNT_SHIFT;

	/* DEVWDT is in 'log2(x) - 3' क्रमm */
	alert |= (sdram_io_width - 2) << TA_DEVWDT_SHIFT;

	alert |= 1 << TA_SFEXITEN_SHIFT;
	alert |= 1 << TA_CS0EN_SHIFT;
	alert |= (cs1_used ? 1 : 0) << TA_CS1EN_SHIFT;

	वापस alert;
पूर्ण

अटल u32 get_पढ़ो_idle_ctrl_shdw(u8 volt_ramp)
अणु
	u32 idle = 0, val = 0;

	/*
	 * Maximum value in normal conditions and increased frequency
	 * when voltage is ramping
	 */
	अगर (volt_ramp)
		val = READ_IDLE_INTERVAL_DVFS / t_ck / 64 - 1;
	अन्यथा
		val = 0x1FF;

	/*
	 * READ_IDLE_CTRL रेजिस्टर in EMIF4D has same offset and fields
	 * as DLL_CALIB_CTRL in EMIF4D5, so use the same shअगरts
	 */
	idle |= val << DLL_CALIB_INTERVAL_SHIFT;
	idle |= EMIF_READ_IDLE_LEN_VAL << ACK_WAIT_SHIFT;

	वापस idle;
पूर्ण

अटल u32 get_dll_calib_ctrl_shdw(u8 volt_ramp)
अणु
	u32 calib = 0, val = 0;

	अगर (volt_ramp == DDR_VOLTAGE_RAMPING)
		val = DLL_CALIB_INTERVAL_DVFS / t_ck / 16 - 1;
	अन्यथा
		val = 0; /* Disabled when voltage is stable */

	calib |= val << DLL_CALIB_INTERVAL_SHIFT;
	calib |= DLL_CALIB_ACK_WAIT_VAL << ACK_WAIT_SHIFT;

	वापस calib;
पूर्ण

अटल u32 get_ddr_phy_ctrl_1_attilaphy_4d(स्थिर काष्ठा lpddr2_timings *timings,
	u32 freq, u8 RL)
अणु
	u32 phy = EMIF_DDR_PHY_CTRL_1_BASE_VAL_ATTILAPHY, val = 0;

	val = RL + DIV_ROUND_UP(timings->tDQSCK_max, t_ck) - 1;
	phy |= val << READ_LATENCY_SHIFT_4D;

	अगर (freq <= 100000000)
		val = EMIF_DLL_SLAVE_DLY_CTRL_100_MHZ_AND_LESS_ATTILAPHY;
	अन्यथा अगर (freq <= 200000000)
		val = EMIF_DLL_SLAVE_DLY_CTRL_200_MHZ_ATTILAPHY;
	अन्यथा
		val = EMIF_DLL_SLAVE_DLY_CTRL_400_MHZ_ATTILAPHY;

	phy |= val << DLL_SLAVE_DLY_CTRL_SHIFT_4D;

	वापस phy;
पूर्ण

अटल u32 get_phy_ctrl_1_पूर्णांकelliphy_4d5(u32 freq, u8 cl)
अणु
	u32 phy = EMIF_DDR_PHY_CTRL_1_BASE_VAL_INTELLIPHY, half_delay;

	/*
	 * DLL operates at 266 MHz. If DDR frequency is near 266 MHz,
	 * half-delay is not needed अन्यथा set half-delay
	 */
	अगर (freq >= 265000000 && freq < 267000000)
		half_delay = 0;
	अन्यथा
		half_delay = 1;

	phy |= half_delay << DLL_HALF_DELAY_SHIFT_4D5;
	phy |= ((cl + DIV_ROUND_UP(EMIF_PHY_TOTAL_READ_LATENCY_INTELLIPHY_PS,
			t_ck) - 1) << READ_LATENCY_SHIFT_4D5);

	वापस phy;
पूर्ण

अटल u32 get_ext_phy_ctrl_2_पूर्णांकelliphy_4d5(व्योम)
अणु
	u32 fअगरo_we_slave_ratio;

	fअगरo_we_slave_ratio =  DIV_ROUND_CLOSEST(
		EMIF_INTELLI_PHY_DQS_GATE_OPENING_DELAY_PS * 256, t_ck);

	वापस fअगरo_we_slave_ratio | fअगरo_we_slave_ratio << 11 |
		fअगरo_we_slave_ratio << 22;
पूर्ण

अटल u32 get_ext_phy_ctrl_3_पूर्णांकelliphy_4d5(व्योम)
अणु
	u32 fअगरo_we_slave_ratio;

	fअगरo_we_slave_ratio =  DIV_ROUND_CLOSEST(
		EMIF_INTELLI_PHY_DQS_GATE_OPENING_DELAY_PS * 256, t_ck);

	वापस fअगरo_we_slave_ratio >> 10 | fअगरo_we_slave_ratio << 1 |
		fअगरo_we_slave_ratio << 12 | fअगरo_we_slave_ratio << 23;
पूर्ण

अटल u32 get_ext_phy_ctrl_4_पूर्णांकelliphy_4d5(व्योम)
अणु
	u32 fअगरo_we_slave_ratio;

	fअगरo_we_slave_ratio =  DIV_ROUND_CLOSEST(
		EMIF_INTELLI_PHY_DQS_GATE_OPENING_DELAY_PS * 256, t_ck);

	वापस fअगरo_we_slave_ratio >> 9 | fअगरo_we_slave_ratio << 2 |
		fअगरo_we_slave_ratio << 13;
पूर्ण

अटल u32 get_pwr_mgmt_ctrl(u32 freq, काष्ठा emअगर_data *emअगर, u32 ip_rev)
अणु
	u32 pwr_mgmt_ctrl	= 0, समयout;
	u32 lpmode		= EMIF_LP_MODE_SELF_REFRESH;
	u32 समयout_perf	= EMIF_LP_MODE_TIMEOUT_PERFORMANCE;
	u32 समयout_pwr		= EMIF_LP_MODE_TIMEOUT_POWER;
	u32 freq_threshold	= EMIF_LP_MODE_FREQ_THRESHOLD;
	u32 mask;
	u8 shअगरt;

	काष्ठा emअगर_custom_configs *cust_cfgs = emअगर->plat_data->custom_configs;

	अगर (cust_cfgs && (cust_cfgs->mask & EMIF_CUSTOM_CONFIG_LPMODE)) अणु
		lpmode		= cust_cfgs->lpmode;
		समयout_perf	= cust_cfgs->lpmode_समयout_perक्रमmance;
		समयout_pwr	= cust_cfgs->lpmode_समयout_घातer;
		freq_threshold  = cust_cfgs->lpmode_freq_threshold;
	पूर्ण

	/* Timeout based on DDR frequency */
	समयout = freq >= freq_threshold ? समयout_perf : समयout_pwr;

	/*
	 * The value to be set in रेजिस्टर is "log2(timeout) - 3"
	 * अगर समयout < 16 load 0 in रेजिस्टर
	 * अगर समयout is not a घातer of 2, round to next highest घातer of 2
	 */
	अगर (समयout < 16) अणु
		समयout = 0;
	पूर्ण अन्यथा अणु
		अगर (समयout & (समयout - 1))
			समयout <<= 1;
		समयout = __fls(समयout) - 3;
	पूर्ण

	चयन (lpmode) अणु
	हाल EMIF_LP_MODE_CLOCK_STOP:
		shअगरt = CS_TIM_SHIFT;
		mask = CS_TIM_MASK;
		अवरोध;
	हाल EMIF_LP_MODE_SELF_REFRESH:
		/* Workaround क्रम errata i735 */
		अगर (समयout < 6)
			समयout = 6;

		shअगरt = SR_TIM_SHIFT;
		mask = SR_TIM_MASK;
		अवरोध;
	हाल EMIF_LP_MODE_PWR_DN:
		shअगरt = PD_TIM_SHIFT;
		mask = PD_TIM_MASK;
		अवरोध;
	हाल EMIF_LP_MODE_DISABLE:
	शेष:
		mask = 0;
		shअगरt = 0;
		अवरोध;
	पूर्ण
	/* Round to maximum in हाल of overflow, BUT warn! */
	अगर (lpmode != EMIF_LP_MODE_DISABLE && समयout > mask >> shअगरt) अणु
		pr_err("TIMEOUT Overflow - lpmode=%d perf=%d pwr=%d freq=%d\n",
		       lpmode,
		       समयout_perf,
		       समयout_pwr,
		       freq_threshold);
		WARN(1, "timeout=0x%02x greater than 0x%02x. Using max\n",
		     समयout, mask >> shअगरt);
		समयout = mask >> shअगरt;
	पूर्ण

	/* Setup required timing */
	pwr_mgmt_ctrl = (समयout << shअगरt) & mask;
	/* setup a शेष mask क्रम rest of the modes */
	pwr_mgmt_ctrl |= (SR_TIM_MASK | CS_TIM_MASK | PD_TIM_MASK) &
			  ~mask;

	/* No CS_TIM in EMIF_4D5 */
	अगर (ip_rev == EMIF_4D5)
		pwr_mgmt_ctrl &= ~CS_TIM_MASK;

	pwr_mgmt_ctrl |= lpmode << LP_MODE_SHIFT;

	वापस pwr_mgmt_ctrl;
पूर्ण

/*
 * Get the temperature level of the EMIF instance:
 * Reads the MR4 रेजिस्टर of attached SDRAM parts to find out the temperature
 * level. If there are two parts attached(one on each CS), then the temperature
 * level क्रम the EMIF instance is the higher of the two temperatures.
 */
अटल व्योम get_temperature_level(काष्ठा emअगर_data *emअगर)
अणु
	u32		temp, temperature_level;
	व्योम __iomem	*base;

	base = emअगर->base;

	/* Read mode रेजिस्टर 4 */
	ग_लिखोl(DDR_MR4, base + EMIF_LPDDR2_MODE_REG_CONFIG);
	temperature_level = पढ़ोl(base + EMIF_LPDDR2_MODE_REG_DATA);
	temperature_level = (temperature_level & MR4_SDRAM_REF_RATE_MASK) >>
				MR4_SDRAM_REF_RATE_SHIFT;

	अगर (emअगर->plat_data->device_info->cs1_used) अणु
		ग_लिखोl(DDR_MR4 | CS_MASK, base + EMIF_LPDDR2_MODE_REG_CONFIG);
		temp = पढ़ोl(base + EMIF_LPDDR2_MODE_REG_DATA);
		temp = (temp & MR4_SDRAM_REF_RATE_MASK)
				>> MR4_SDRAM_REF_RATE_SHIFT;
		temperature_level = max(temp, temperature_level);
	पूर्ण

	/* treat everything less than nominal(3) in MR4 as nominal */
	अगर (unlikely(temperature_level < SDRAM_TEMP_NOMINAL))
		temperature_level = SDRAM_TEMP_NOMINAL;

	/* अगर we get reserved value in MR4 persist with the existing value */
	अगर (likely(temperature_level != SDRAM_TEMP_RESERVED_4))
		emअगर->temperature_level = temperature_level;
पूर्ण

/*
 * Program EMIF shaकरोw रेजिस्टरs that are not dependent on temperature
 * or voltage
 */
अटल व्योम setup_रेजिस्टरs(काष्ठा emअगर_data *emअगर, काष्ठा emअगर_regs *regs)
अणु
	व्योम __iomem	*base = emअगर->base;

	ग_लिखोl(regs->sdram_tim2_shdw, base + EMIF_SDRAM_TIMING_2_SHDW);
	ग_लिखोl(regs->phy_ctrl_1_shdw, base + EMIF_DDR_PHY_CTRL_1_SHDW);
	ग_लिखोl(regs->pwr_mgmt_ctrl_shdw,
	       base + EMIF_POWER_MANAGEMENT_CTRL_SHDW);

	/* Settings specअगरic क्रम EMIF4D5 */
	अगर (emअगर->plat_data->ip_rev != EMIF_4D5)
		वापस;
	ग_लिखोl(regs->ext_phy_ctrl_2_shdw, base + EMIF_EXT_PHY_CTRL_2_SHDW);
	ग_लिखोl(regs->ext_phy_ctrl_3_shdw, base + EMIF_EXT_PHY_CTRL_3_SHDW);
	ग_लिखोl(regs->ext_phy_ctrl_4_shdw, base + EMIF_EXT_PHY_CTRL_4_SHDW);
पूर्ण

/*
 * When voltage ramps dll calibration and क्रमced पढ़ो idle should
 * happen more often
 */
अटल व्योम setup_volt_sensitive_regs(काष्ठा emअगर_data *emअगर,
		काष्ठा emअगर_regs *regs, u32 volt_state)
अणु
	u32		calib_ctrl;
	व्योम __iomem	*base = emअगर->base;

	/*
	 * EMIF_READ_IDLE_CTRL in EMIF4D refers to the same रेजिस्टर as
	 * EMIF_DLL_CALIB_CTRL in EMIF4D5 and dll_calib_ctrl_shaकरोw_*
	 * is an alias of the respective पढ़ो_idle_ctrl_shdw_* (members of
	 * a जोड़). So, the below code takes care of both हालs
	 */
	अगर (volt_state == DDR_VOLTAGE_RAMPING)
		calib_ctrl = regs->dll_calib_ctrl_shdw_volt_ramp;
	अन्यथा
		calib_ctrl = regs->dll_calib_ctrl_shdw_normal;

	ग_लिखोl(calib_ctrl, base + EMIF_DLL_CALIB_CTRL_SHDW);
पूर्ण

/*
 * setup_temperature_sensitive_regs() - set the timings क्रम temperature
 * sensitive रेजिस्टरs. This happens once at initialisation समय based
 * on the temperature at boot समय and subsequently based on the temperature
 * alert पूर्णांकerrupt. Temperature alert can happen when the temperature
 * increases or drops. So this function can have the effect of either
 * derating the timings or going back to nominal values.
 */
अटल व्योम setup_temperature_sensitive_regs(काष्ठा emअगर_data *emअगर,
		काष्ठा emअगर_regs *regs)
अणु
	u32		tim1, tim3, ref_ctrl, type;
	व्योम __iomem	*base = emअगर->base;
	u32		temperature;

	type = emअगर->plat_data->device_info->type;

	tim1 = regs->sdram_tim1_shdw;
	tim3 = regs->sdram_tim3_shdw;
	ref_ctrl = regs->ref_ctrl_shdw;

	/* No de-rating क्रम non-lpddr2 devices */
	अगर (type != DDR_TYPE_LPDDR2_S2 && type != DDR_TYPE_LPDDR2_S4)
		जाओ out;

	temperature = emअगर->temperature_level;
	अगर (temperature == SDRAM_TEMP_HIGH_DERATE_REFRESH) अणु
		ref_ctrl = regs->ref_ctrl_shdw_derated;
	पूर्ण अन्यथा अगर (temperature == SDRAM_TEMP_HIGH_DERATE_REFRESH_AND_TIMINGS) अणु
		tim1 = regs->sdram_tim1_shdw_derated;
		tim3 = regs->sdram_tim3_shdw_derated;
		ref_ctrl = regs->ref_ctrl_shdw_derated;
	पूर्ण

out:
	ग_लिखोl(tim1, base + EMIF_SDRAM_TIMING_1_SHDW);
	ग_लिखोl(tim3, base + EMIF_SDRAM_TIMING_3_SHDW);
	ग_लिखोl(ref_ctrl, base + EMIF_SDRAM_REFRESH_CTRL_SHDW);
पूर्ण

अटल irqवापस_t handle_temp_alert(व्योम __iomem *base, काष्ठा emअगर_data *emअगर)
अणु
	u32		old_temp_level;
	irqवापस_t	ret = IRQ_HANDLED;
	काष्ठा emअगर_custom_configs *custom_configs;

	spin_lock_irqsave(&emअगर_lock, irq_state);
	old_temp_level = emअगर->temperature_level;
	get_temperature_level(emअगर);

	अगर (unlikely(emअगर->temperature_level == old_temp_level)) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (!emअगर->curr_regs) अणु
		dev_err(emअगर->dev, "temperature alert before registers are calculated, not de-rating timings\n");
		जाओ out;
	पूर्ण

	custom_configs = emअगर->plat_data->custom_configs;

	/*
	 * IF we detect higher than "nominal rating" from DDR sensor
	 * on an unsupported DDR part, shutकरोwn प्रणाली
	 */
	अगर (custom_configs && !(custom_configs->mask &
				EMIF_CUSTOM_CONFIG_EXTENDED_TEMP_PART)) अणु
		अगर (emअगर->temperature_level >= SDRAM_TEMP_HIGH_DERATE_REFRESH) अणु
			dev_err(emअगर->dev,
				"%s:NOT Extended temperature capable memory. Converting MR4=0x%02x as shutdown event\n",
				__func__, emअगर->temperature_level);
			/*
			 * Temperature far too high - करो kernel_घातer_off()
			 * from thपढ़ो context
			 */
			emअगर->temperature_level = SDRAM_TEMP_VERY_HIGH_SHUTDOWN;
			ret = IRQ_WAKE_THREAD;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (emअगर->temperature_level < old_temp_level ||
		emअगर->temperature_level == SDRAM_TEMP_VERY_HIGH_SHUTDOWN) अणु
		/*
		 * Temperature coming करोwn - defer handling to thपढ़ो OR
		 * Temperature far too high - करो kernel_घातer_off() from
		 * thपढ़ो context
		 */
		ret = IRQ_WAKE_THREAD;
	पूर्ण अन्यथा अणु
		/* Temperature is going up - handle immediately */
		setup_temperature_sensitive_regs(emअगर, emअगर->curr_regs);
		करो_freq_update();
	पूर्ण

out:
	spin_unlock_irqrestore(&emअगर_lock, irq_state);
	वापस ret;
पूर्ण

अटल irqवापस_t emअगर_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	u32			पूर्णांकerrupts;
	काष्ठा emअगर_data	*emअगर = dev_id;
	व्योम __iomem		*base = emअगर->base;
	काष्ठा device		*dev = emअगर->dev;
	irqवापस_t		ret = IRQ_HANDLED;

	/* Save the status and clear it */
	पूर्णांकerrupts = पढ़ोl(base + EMIF_SYSTEM_OCP_INTERRUPT_STATUS);
	ग_लिखोl(पूर्णांकerrupts, base + EMIF_SYSTEM_OCP_INTERRUPT_STATUS);

	/*
	 * Handle temperature alert
	 * Temperature alert should be same क्रम all ports
	 * So, it's enough to process it only क्रम one of the ports
	 */
	अगर (पूर्णांकerrupts & TA_SYS_MASK)
		ret = handle_temp_alert(base, emअगर);

	अगर (पूर्णांकerrupts & ERR_SYS_MASK)
		dev_err(dev, "Access error from SYS port - %x\n", पूर्णांकerrupts);

	अगर (emअगर->plat_data->hw_caps & EMIF_HW_CAPS_LL_INTERFACE) अणु
		/* Save the status and clear it */
		पूर्णांकerrupts = पढ़ोl(base + EMIF_LL_OCP_INTERRUPT_STATUS);
		ग_लिखोl(पूर्णांकerrupts, base + EMIF_LL_OCP_INTERRUPT_STATUS);

		अगर (पूर्णांकerrupts & ERR_LL_MASK)
			dev_err(dev, "Access error from LL port - %x\n",
				पूर्णांकerrupts);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t emअगर_thपढ़ोed_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा emअगर_data	*emअगर = dev_id;

	अगर (emअगर->temperature_level == SDRAM_TEMP_VERY_HIGH_SHUTDOWN) अणु
		dev_emerg(emअगर->dev, "SDRAM temperature exceeds operating limit.. Needs shut down!!!\n");

		/* If we have Power OFF ability, use it, अन्यथा try restarting */
		अगर (pm_घातer_off) अणु
			kernel_घातer_off();
		पूर्ण अन्यथा अणु
			WARN(1, "FIXME: NO pm_power_off!!! trying restart\n");
			kernel_restart("SDRAM Over-temp Emergency restart");
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	spin_lock_irqsave(&emअगर_lock, irq_state);

	अगर (emअगर->curr_regs) अणु
		setup_temperature_sensitive_regs(emअगर, emअगर->curr_regs);
		करो_freq_update();
	पूर्ण अन्यथा अणु
		dev_err(emअगर->dev, "temperature alert before registers are calculated, not de-rating timings\n");
	पूर्ण

	spin_unlock_irqrestore(&emअगर_lock, irq_state);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम clear_all_पूर्णांकerrupts(काष्ठा emअगर_data *emअगर)
अणु
	व्योम __iomem	*base = emअगर->base;

	ग_लिखोl(पढ़ोl(base + EMIF_SYSTEM_OCP_INTERRUPT_STATUS),
		base + EMIF_SYSTEM_OCP_INTERRUPT_STATUS);
	अगर (emअगर->plat_data->hw_caps & EMIF_HW_CAPS_LL_INTERFACE)
		ग_लिखोl(पढ़ोl(base + EMIF_LL_OCP_INTERRUPT_STATUS),
			base + EMIF_LL_OCP_INTERRUPT_STATUS);
पूर्ण

अटल व्योम disable_and_clear_all_पूर्णांकerrupts(काष्ठा emअगर_data *emअगर)
अणु
	व्योम __iomem		*base = emअगर->base;

	/* Disable all पूर्णांकerrupts */
	ग_लिखोl(पढ़ोl(base + EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET),
		base + EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR);
	अगर (emअगर->plat_data->hw_caps & EMIF_HW_CAPS_LL_INTERFACE)
		ग_लिखोl(पढ़ोl(base + EMIF_LL_OCP_INTERRUPT_ENABLE_SET),
			base + EMIF_LL_OCP_INTERRUPT_ENABLE_CLEAR);

	/* Clear all पूर्णांकerrupts */
	clear_all_पूर्णांकerrupts(emअगर);
पूर्ण

अटल पूर्णांक __init_or_module setup_पूर्णांकerrupts(काष्ठा emअगर_data *emअगर, u32 irq)
अणु
	u32		पूर्णांकerrupts, type;
	व्योम __iomem	*base = emअगर->base;

	type = emअगर->plat_data->device_info->type;

	clear_all_पूर्णांकerrupts(emअगर);

	/* Enable पूर्णांकerrupts क्रम SYS पूर्णांकerface */
	पूर्णांकerrupts = EN_ERR_SYS_MASK;
	अगर (type == DDR_TYPE_LPDDR2_S2 || type == DDR_TYPE_LPDDR2_S4)
		पूर्णांकerrupts |= EN_TA_SYS_MASK;
	ग_लिखोl(पूर्णांकerrupts, base + EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET);

	/* Enable पूर्णांकerrupts क्रम LL पूर्णांकerface */
	अगर (emअगर->plat_data->hw_caps & EMIF_HW_CAPS_LL_INTERFACE) अणु
		/* TA need not be enabled क्रम LL */
		पूर्णांकerrupts = EN_ERR_LL_MASK;
		ग_लिखोl(पूर्णांकerrupts, base + EMIF_LL_OCP_INTERRUPT_ENABLE_SET);
	पूर्ण

	/* setup IRQ handlers */
	वापस devm_request_thपढ़ोed_irq(emअगर->dev, irq,
				    emअगर_पूर्णांकerrupt_handler,
				    emअगर_thपढ़ोed_isr,
				    0, dev_name(emअगर->dev),
				    emअगर);

पूर्ण

अटल व्योम __init_or_module emअगर_oneसमय_settings(काष्ठा emअगर_data *emअगर)
अणु
	u32				pwr_mgmt_ctrl, zq, temp_alert_cfg;
	व्योम __iomem			*base = emअगर->base;
	स्थिर काष्ठा lpddr2_addressing	*addressing;
	स्थिर काष्ठा ddr_device_info	*device_info;

	device_info = emअगर->plat_data->device_info;
	addressing = get_addressing_table(device_info);

	/*
	 * Init घातer management settings
	 * We करोn't know the frequency yet. Use a high frequency
	 * value क्रम a conservative समयout setting
	 */
	pwr_mgmt_ctrl = get_pwr_mgmt_ctrl(1000000000, emअगर,
			emअगर->plat_data->ip_rev);
	emअगर->lpmode = (pwr_mgmt_ctrl & LP_MODE_MASK) >> LP_MODE_SHIFT;
	ग_लिखोl(pwr_mgmt_ctrl, base + EMIF_POWER_MANAGEMENT_CONTROL);

	/* Init ZQ calibration settings */
	zq = get_zq_config_reg(addressing, device_info->cs1_used,
		device_info->cal_resistors_per_cs);
	ग_लिखोl(zq, base + EMIF_SDRAM_OUTPUT_IMPEDANCE_CALIBRATION_CONFIG);

	/* Check temperature level temperature level*/
	get_temperature_level(emअगर);
	अगर (emअगर->temperature_level == SDRAM_TEMP_VERY_HIGH_SHUTDOWN)
		dev_emerg(emअगर->dev, "SDRAM temperature exceeds operating limit.. Needs shut down!!!\n");

	/* Init temperature polling */
	temp_alert_cfg = get_temp_alert_config(addressing,
		emअगर->plat_data->custom_configs, device_info->cs1_used,
		device_info->io_width, get_emअगर_bus_width(emअगर));
	ग_लिखोl(temp_alert_cfg, base + EMIF_TEMPERATURE_ALERT_CONFIG);

	/*
	 * Program बाह्यal PHY control रेजिस्टरs that are not frequency
	 * dependent
	 */
	अगर (emअगर->plat_data->phy_type != EMIF_PHY_TYPE_INTELLIPHY)
		वापस;
	ग_लिखोl(EMIF_EXT_PHY_CTRL_1_VAL, base + EMIF_EXT_PHY_CTRL_1_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_5_VAL, base + EMIF_EXT_PHY_CTRL_5_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_6_VAL, base + EMIF_EXT_PHY_CTRL_6_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_7_VAL, base + EMIF_EXT_PHY_CTRL_7_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_8_VAL, base + EMIF_EXT_PHY_CTRL_8_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_9_VAL, base + EMIF_EXT_PHY_CTRL_9_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_10_VAL, base + EMIF_EXT_PHY_CTRL_10_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_11_VAL, base + EMIF_EXT_PHY_CTRL_11_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_12_VAL, base + EMIF_EXT_PHY_CTRL_12_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_13_VAL, base + EMIF_EXT_PHY_CTRL_13_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_14_VAL, base + EMIF_EXT_PHY_CTRL_14_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_15_VAL, base + EMIF_EXT_PHY_CTRL_15_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_16_VAL, base + EMIF_EXT_PHY_CTRL_16_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_17_VAL, base + EMIF_EXT_PHY_CTRL_17_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_18_VAL, base + EMIF_EXT_PHY_CTRL_18_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_19_VAL, base + EMIF_EXT_PHY_CTRL_19_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_20_VAL, base + EMIF_EXT_PHY_CTRL_20_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_21_VAL, base + EMIF_EXT_PHY_CTRL_21_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_22_VAL, base + EMIF_EXT_PHY_CTRL_22_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_23_VAL, base + EMIF_EXT_PHY_CTRL_23_SHDW);
	ग_लिखोl(EMIF_EXT_PHY_CTRL_24_VAL, base + EMIF_EXT_PHY_CTRL_24_SHDW);
पूर्ण

अटल व्योम get_शेष_timings(काष्ठा emअगर_data *emअगर)
अणु
	काष्ठा emअगर_platक्रमm_data *pd = emअगर->plat_data;

	pd->timings		= lpddr2_jedec_timings;
	pd->timings_arr_size	= ARRAY_SIZE(lpddr2_jedec_timings);

	dev_warn(emअगर->dev, "%s: using default timings\n", __func__);
पूर्ण

अटल पूर्णांक is_dev_data_valid(u32 type, u32 density, u32 io_width, u32 phy_type,
		u32 ip_rev, काष्ठा device *dev)
अणु
	पूर्णांक valid;

	valid = (type == DDR_TYPE_LPDDR2_S4 ||
			type == DDR_TYPE_LPDDR2_S2)
		&& (density >= DDR_DENSITY_64Mb
			&& density <= DDR_DENSITY_8Gb)
		&& (io_width >= DDR_IO_WIDTH_8
			&& io_width <= DDR_IO_WIDTH_32);

	/* Combinations of EMIF and PHY revisions that we support today */
	चयन (ip_rev) अणु
	हाल EMIF_4D:
		valid = valid && (phy_type == EMIF_PHY_TYPE_ATTILAPHY);
		अवरोध;
	हाल EMIF_4D5:
		valid = valid && (phy_type == EMIF_PHY_TYPE_INTELLIPHY);
		अवरोध;
	शेष:
		valid = 0;
	पूर्ण

	अगर (!valid)
		dev_err(dev, "%s: invalid DDR details\n", __func__);
	वापस valid;
पूर्ण

अटल पूर्णांक is_custom_config_valid(काष्ठा emअगर_custom_configs *cust_cfgs,
		काष्ठा device *dev)
अणु
	पूर्णांक valid = 1;

	अगर ((cust_cfgs->mask & EMIF_CUSTOM_CONFIG_LPMODE) &&
		(cust_cfgs->lpmode != EMIF_LP_MODE_DISABLE))
		valid = cust_cfgs->lpmode_freq_threshold &&
			cust_cfgs->lpmode_समयout_perक्रमmance &&
			cust_cfgs->lpmode_समयout_घातer;

	अगर (cust_cfgs->mask & EMIF_CUSTOM_CONFIG_TEMP_ALERT_POLL_INTERVAL)
		valid = valid && cust_cfgs->temp_alert_poll_पूर्णांकerval_ms;

	अगर (!valid)
		dev_warn(dev, "%s: invalid custom configs\n", __func__);

	वापस valid;
पूर्ण

#अगर defined(CONFIG_OF)
अटल व्योम __init_or_module of_get_custom_configs(काष्ठा device_node *np_emअगर,
		काष्ठा emअगर_data *emअगर)
अणु
	काष्ठा emअगर_custom_configs	*cust_cfgs = शून्य;
	पूर्णांक				len;
	स्थिर __be32			*lpmode, *poll_पूर्णांकvl;

	lpmode = of_get_property(np_emअगर, "low-power-mode", &len);
	poll_पूर्णांकvl = of_get_property(np_emअगर, "temp-alert-poll-interval", &len);

	अगर (lpmode || poll_पूर्णांकvl)
		cust_cfgs = devm_kzalloc(emअगर->dev, माप(*cust_cfgs),
			GFP_KERNEL);

	अगर (!cust_cfgs)
		वापस;

	अगर (lpmode) अणु
		cust_cfgs->mask |= EMIF_CUSTOM_CONFIG_LPMODE;
		cust_cfgs->lpmode = be32_to_cpup(lpmode);
		of_property_पढ़ो_u32(np_emअगर,
				"low-power-mode-timeout-performance",
				&cust_cfgs->lpmode_समयout_perक्रमmance);
		of_property_पढ़ो_u32(np_emअगर,
				"low-power-mode-timeout-power",
				&cust_cfgs->lpmode_समयout_घातer);
		of_property_पढ़ो_u32(np_emअगर,
				"low-power-mode-freq-threshold",
				&cust_cfgs->lpmode_freq_threshold);
	पूर्ण

	अगर (poll_पूर्णांकvl) अणु
		cust_cfgs->mask |=
				EMIF_CUSTOM_CONFIG_TEMP_ALERT_POLL_INTERVAL;
		cust_cfgs->temp_alert_poll_पूर्णांकerval_ms =
						be32_to_cpup(poll_पूर्णांकvl);
	पूर्ण

	अगर (of_find_property(np_emअगर, "extended-temp-part", &len))
		cust_cfgs->mask |= EMIF_CUSTOM_CONFIG_EXTENDED_TEMP_PART;

	अगर (!is_custom_config_valid(cust_cfgs, emअगर->dev)) अणु
		devm_kमुक्त(emअगर->dev, cust_cfgs);
		वापस;
	पूर्ण

	emअगर->plat_data->custom_configs = cust_cfgs;
पूर्ण

अटल व्योम __init_or_module of_get_ddr_info(काष्ठा device_node *np_emअगर,
		काष्ठा device_node *np_ddr,
		काष्ठा ddr_device_info *dev_info)
अणु
	u32 density = 0, io_width = 0;
	पूर्णांक len;

	अगर (of_find_property(np_emअगर, "cs1-used", &len))
		dev_info->cs1_used = true;

	अगर (of_find_property(np_emअगर, "cal-resistor-per-cs", &len))
		dev_info->cal_resistors_per_cs = true;

	अगर (of_device_is_compatible(np_ddr, "jedec,lpddr2-s4"))
		dev_info->type = DDR_TYPE_LPDDR2_S4;
	अन्यथा अगर (of_device_is_compatible(np_ddr, "jedec,lpddr2-s2"))
		dev_info->type = DDR_TYPE_LPDDR2_S2;

	of_property_पढ़ो_u32(np_ddr, "density", &density);
	of_property_पढ़ो_u32(np_ddr, "io-width", &io_width);

	/* Convert from density in Mb to the density encoding in jedc_ddr.h */
	अगर (density & (density - 1))
		dev_info->density = 0;
	अन्यथा
		dev_info->density = __fls(density) - 5;

	/* Convert from io_width in bits to io_width encoding in jedc_ddr.h */
	अगर (io_width & (io_width - 1))
		dev_info->io_width = 0;
	अन्यथा
		dev_info->io_width = __fls(io_width) - 1;
पूर्ण

अटल काष्ठा emअगर_data * __init_or_module of_get_memory_device_details(
		काष्ठा device_node *np_emअगर, काष्ठा device *dev)
अणु
	काष्ठा emअगर_data		*emअगर = शून्य;
	काष्ठा ddr_device_info		*dev_info = शून्य;
	काष्ठा emअगर_platक्रमm_data	*pd = शून्य;
	काष्ठा device_node		*np_ddr;
	पूर्णांक				len;

	np_ddr = of_parse_phandle(np_emअगर, "device-handle", 0);
	अगर (!np_ddr)
		जाओ error;
	emअगर	= devm_kzalloc(dev, माप(काष्ठा emअगर_data), GFP_KERNEL);
	pd	= devm_kzalloc(dev, माप(*pd), GFP_KERNEL);
	dev_info = devm_kzalloc(dev, माप(*dev_info), GFP_KERNEL);

	अगर (!emअगर || !pd || !dev_info) अणु
		dev_err(dev, "%s: Out of memory!!\n",
			__func__);
		जाओ error;
	पूर्ण

	emअगर->plat_data		= pd;
	pd->device_info		= dev_info;
	emअगर->dev		= dev;
	emअगर->np_ddr		= np_ddr;
	emअगर->temperature_level	= SDRAM_TEMP_NOMINAL;

	अगर (of_device_is_compatible(np_emअगर, "ti,emif-4d"))
		emअगर->plat_data->ip_rev = EMIF_4D;
	अन्यथा अगर (of_device_is_compatible(np_emअगर, "ti,emif-4d5"))
		emअगर->plat_data->ip_rev = EMIF_4D5;

	of_property_पढ़ो_u32(np_emअगर, "phy-type", &pd->phy_type);

	अगर (of_find_property(np_emअगर, "hw-caps-ll-interface", &len))
		pd->hw_caps |= EMIF_HW_CAPS_LL_INTERFACE;

	of_get_ddr_info(np_emअगर, np_ddr, dev_info);
	अगर (!is_dev_data_valid(pd->device_info->type, pd->device_info->density,
			pd->device_info->io_width, pd->phy_type, pd->ip_rev,
			emअगर->dev)) अणु
		dev_err(dev, "%s: invalid device data!!\n", __func__);
		जाओ error;
	पूर्ण
	/*
	 * For EMIF instances other than EMIF1 see अगर the devices connected
	 * are exactly same as on EMIF1(which is typically the हाल). If so,
	 * mark it as a duplicate of EMIF1. This will save some memory and
	 * computation.
	 */
	अगर (emअगर1 && emअगर1->np_ddr == np_ddr) अणु
		emअगर->duplicate = true;
		जाओ out;
	पूर्ण अन्यथा अगर (emअगर1) अणु
		dev_warn(emअगर->dev, "%s: Non-symmetric DDR geometry\n",
			__func__);
	पूर्ण

	of_get_custom_configs(np_emअगर, emअगर);
	emअगर->plat_data->timings = of_get_ddr_timings(np_ddr, emअगर->dev,
					emअगर->plat_data->device_info->type,
					&emअगर->plat_data->timings_arr_size);

	emअगर->plat_data->min_tck = of_get_min_tck(np_ddr, emअगर->dev);
	जाओ out;

error:
	वापस शून्य;
out:
	वापस emअगर;
पूर्ण

#अन्यथा

अटल काष्ठा emअगर_data * __init_or_module of_get_memory_device_details(
		काष्ठा device_node *np_emअगर, काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा emअगर_data *__init_or_module get_device_details(
		काष्ठा platक्रमm_device *pdev)
अणु
	u32				size;
	काष्ठा emअगर_data		*emअगर = शून्य;
	काष्ठा ddr_device_info		*dev_info;
	काष्ठा emअगर_custom_configs	*cust_cfgs;
	काष्ठा emअगर_platक्रमm_data	*pd;
	काष्ठा device			*dev;
	व्योम				*temp;

	pd = pdev->dev.platक्रमm_data;
	dev = &pdev->dev;

	अगर (!(pd && pd->device_info && is_dev_data_valid(pd->device_info->type,
			pd->device_info->density, pd->device_info->io_width,
			pd->phy_type, pd->ip_rev, dev))) अणु
		dev_err(dev, "%s: invalid device data\n", __func__);
		जाओ error;
	पूर्ण

	emअगर	= devm_kzalloc(dev, माप(*emअगर), GFP_KERNEL);
	temp	= devm_kzalloc(dev, माप(*pd), GFP_KERNEL);
	dev_info = devm_kzalloc(dev, माप(*dev_info), GFP_KERNEL);

	अगर (!emअगर || !pd || !dev_info) अणु
		dev_err(dev, "%s:%d: allocation error\n", __func__, __LINE__);
		जाओ error;
	पूर्ण

	स_नकल(temp, pd, माप(*pd));
	pd = temp;
	स_नकल(dev_info, pd->device_info, माप(*dev_info));

	pd->device_info		= dev_info;
	emअगर->plat_data		= pd;
	emअगर->dev		= dev;
	emअगर->temperature_level	= SDRAM_TEMP_NOMINAL;

	/*
	 * For EMIF instances other than EMIF1 see अगर the devices connected
	 * are exactly same as on EMIF1(which is typically the हाल). If so,
	 * mark it as a duplicate of EMIF1 and skip copying timings data.
	 * This will save some memory and some computation later.
	 */
	emअगर->duplicate = emअगर1 && (स_भेद(dev_info,
		emअगर1->plat_data->device_info,
		माप(काष्ठा ddr_device_info)) == 0);

	अगर (emअगर->duplicate) अणु
		pd->timings = शून्य;
		pd->min_tck = शून्य;
		जाओ out;
	पूर्ण अन्यथा अगर (emअगर1) अणु
		dev_warn(emअगर->dev, "%s: Non-symmetric DDR geometry\n",
			__func__);
	पूर्ण

	/*
	 * Copy custom configs - ignore allocation error, अगर any, as
	 * custom_configs is not very critical
	 */
	cust_cfgs = pd->custom_configs;
	अगर (cust_cfgs && is_custom_config_valid(cust_cfgs, dev)) अणु
		temp = devm_kzalloc(dev, माप(*cust_cfgs), GFP_KERNEL);
		अगर (temp)
			स_नकल(temp, cust_cfgs, माप(*cust_cfgs));
		अन्यथा
			dev_warn(dev, "%s:%d: allocation error\n", __func__,
				__LINE__);
		pd->custom_configs = temp;
	पूर्ण

	/*
	 * Copy timings and min-tck values from platक्रमm data. If it is not
	 * available or अगर memory allocation fails, use JEDEC शेषs
	 */
	size = माप(काष्ठा lpddr2_timings) * pd->timings_arr_size;
	अगर (pd->timings) अणु
		temp = devm_kzalloc(dev, size, GFP_KERNEL);
		अगर (temp) अणु
			स_नकल(temp, pd->timings, size);
			pd->timings = temp;
		पूर्ण अन्यथा अणु
			dev_warn(dev, "%s:%d: allocation error\n", __func__,
				__LINE__);
			get_शेष_timings(emअगर);
		पूर्ण
	पूर्ण अन्यथा अणु
		get_शेष_timings(emअगर);
	पूर्ण

	अगर (pd->min_tck) अणु
		temp = devm_kzalloc(dev, माप(*pd->min_tck), GFP_KERNEL);
		अगर (temp) अणु
			स_नकल(temp, pd->min_tck, माप(*pd->min_tck));
			pd->min_tck = temp;
		पूर्ण अन्यथा अणु
			dev_warn(dev, "%s:%d: allocation error\n", __func__,
				__LINE__);
			pd->min_tck = &lpddr2_jedec_min_tck;
		पूर्ण
	पूर्ण अन्यथा अणु
		pd->min_tck = &lpddr2_jedec_min_tck;
	पूर्ण

out:
	वापस emअगर;

error:
	वापस शून्य;
पूर्ण

अटल पूर्णांक __init_or_module emअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा emअगर_data	*emअगर;
	काष्ठा resource		*res;
	पूर्णांक			irq;

	अगर (pdev->dev.of_node)
		emअगर = of_get_memory_device_details(pdev->dev.of_node, &pdev->dev);
	अन्यथा
		emअगर = get_device_details(pdev);

	अगर (!emअगर) अणु
		pr_err("%s: error getting device data\n", __func__);
		जाओ error;
	पूर्ण

	list_add(&emअगर->node, &device_list);
	emअगर->addressing = get_addressing_table(emअगर->plat_data->device_info);

	/* Save poपूर्णांकers to each other in emअगर and device काष्ठाures */
	emअगर->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, emअगर);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	emअगर->base = devm_ioremap_resource(emअगर->dev, res);
	अगर (IS_ERR(emअगर->base))
		जाओ error;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		जाओ error;

	emअगर_oneसमय_settings(emअगर);
	emअगर_debugfs_init(emअगर);
	disable_and_clear_all_पूर्णांकerrupts(emअगर);
	setup_पूर्णांकerrupts(emअगर, irq);

	/* One-समय actions taken on probing the first device */
	अगर (!emअगर1) अणु
		emअगर1 = emअगर;

		/*
		 * TODO: रेजिस्टर notअगरiers क्रम frequency and voltage
		 * change here once the respective frameworks are
		 * available
		 */
	पूर्ण

	dev_info(&pdev->dev, "%s: device configured with addr = %p and IRQ%d\n",
		__func__, emअगर->base, irq);

	वापस 0;
error:
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __निकास emअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा emअगर_data *emअगर = platक्रमm_get_drvdata(pdev);

	emअगर_debugfs_निकास(emअगर);

	वापस 0;
पूर्ण

अटल व्योम emअगर_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा emअगर_data	*emअगर = platक्रमm_get_drvdata(pdev);

	disable_and_clear_all_पूर्णांकerrupts(emअगर);
पूर्ण

अटल पूर्णांक get_emअगर_reg_values(काष्ठा emअगर_data *emअगर, u32 freq,
		काष्ठा emअगर_regs *regs)
अणु
	u32				ip_rev, phy_type;
	u32				cl, type;
	स्थिर काष्ठा lpddr2_timings	*timings;
	स्थिर काष्ठा lpddr2_min_tck	*min_tck;
	स्थिर काष्ठा ddr_device_info	*device_info;
	स्थिर काष्ठा lpddr2_addressing	*addressing;
	काष्ठा emअगर_data		*emअगर_क्रम_calc;
	काष्ठा device			*dev;

	dev = emअगर->dev;
	/*
	 * If the devices on this EMIF instance is duplicate of EMIF1,
	 * use EMIF1 details क्रम the calculation
	 */
	emअगर_क्रम_calc	= emअगर->duplicate ? emअगर1 : emअगर;
	timings		= get_timings_table(emअगर_क्रम_calc, freq);
	addressing	= emअगर_क्रम_calc->addressing;
	अगर (!timings || !addressing) अणु
		dev_err(dev, "%s: not enough data available for %dHz",
			__func__, freq);
		वापस -1;
	पूर्ण

	device_info	= emअगर_क्रम_calc->plat_data->device_info;
	type		= device_info->type;
	ip_rev		= emअगर_क्रम_calc->plat_data->ip_rev;
	phy_type	= emअगर_क्रम_calc->plat_data->phy_type;

	min_tck		= emअगर_क्रम_calc->plat_data->min_tck;

	set_ddr_clk_period(freq);

	regs->ref_ctrl_shdw = get_sdram_ref_ctrl_shdw(freq, addressing);
	regs->sdram_tim1_shdw = get_sdram_tim_1_shdw(timings, min_tck,
			addressing);
	regs->sdram_tim2_shdw = get_sdram_tim_2_shdw(timings, min_tck,
			addressing, type);
	regs->sdram_tim3_shdw = get_sdram_tim_3_shdw(timings, min_tck,
		addressing, type, ip_rev, EMIF_NORMAL_TIMINGS);

	cl = get_cl(emअगर);

	अगर (phy_type == EMIF_PHY_TYPE_ATTILAPHY && ip_rev == EMIF_4D) अणु
		regs->phy_ctrl_1_shdw = get_ddr_phy_ctrl_1_attilaphy_4d(
			timings, freq, cl);
	पूर्ण अन्यथा अगर (phy_type == EMIF_PHY_TYPE_INTELLIPHY && ip_rev == EMIF_4D5) अणु
		regs->phy_ctrl_1_shdw = get_phy_ctrl_1_पूर्णांकelliphy_4d5(freq, cl);
		regs->ext_phy_ctrl_2_shdw = get_ext_phy_ctrl_2_पूर्णांकelliphy_4d5();
		regs->ext_phy_ctrl_3_shdw = get_ext_phy_ctrl_3_पूर्णांकelliphy_4d5();
		regs->ext_phy_ctrl_4_shdw = get_ext_phy_ctrl_4_पूर्णांकelliphy_4d5();
	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण

	/* Only समयout values in pwr_mgmt_ctrl_shdw रेजिस्टर */
	regs->pwr_mgmt_ctrl_shdw =
		get_pwr_mgmt_ctrl(freq, emअगर_क्रम_calc, ip_rev) &
		(CS_TIM_MASK | SR_TIM_MASK | PD_TIM_MASK);

	अगर (ip_rev & EMIF_4D) अणु
		regs->पढ़ो_idle_ctrl_shdw_normal =
			get_पढ़ो_idle_ctrl_shdw(DDR_VOLTAGE_STABLE);

		regs->पढ़ो_idle_ctrl_shdw_volt_ramp =
			get_पढ़ो_idle_ctrl_shdw(DDR_VOLTAGE_RAMPING);
	पूर्ण अन्यथा अगर (ip_rev & EMIF_4D5) अणु
		regs->dll_calib_ctrl_shdw_normal =
			get_dll_calib_ctrl_shdw(DDR_VOLTAGE_STABLE);

		regs->dll_calib_ctrl_shdw_volt_ramp =
			get_dll_calib_ctrl_shdw(DDR_VOLTAGE_RAMPING);
	पूर्ण

	अगर (type == DDR_TYPE_LPDDR2_S2 || type == DDR_TYPE_LPDDR2_S4) अणु
		regs->ref_ctrl_shdw_derated = get_sdram_ref_ctrl_shdw(freq / 4,
			addressing);

		regs->sdram_tim1_shdw_derated =
			get_sdram_tim_1_shdw_derated(timings, min_tck,
				addressing);

		regs->sdram_tim3_shdw_derated = get_sdram_tim_3_shdw(timings,
			min_tck, addressing, type, ip_rev,
			EMIF_DERATED_TIMINGS);
	पूर्ण

	regs->freq = freq;

	वापस 0;
पूर्ण

/*
 * get_regs() - माला_लो the cached emअगर_regs काष्ठाure क्रम a given EMIF instance
 * given frequency(freq):
 *
 * As an optimisation, every EMIF instance other than EMIF1 shares the
 * रेजिस्टर cache with EMIF1 अगर the devices connected on this instance
 * are same as that on EMIF1(indicated by the duplicate flag)
 *
 * If we करो not have an entry corresponding to the frequency given, we
 * allocate a new entry and calculate the values
 *
 * Upon finding the right reg dump, save it in curr_regs. It can be
 * directly used क्रम thermal de-rating and voltage ramping changes.
 */
अटल काष्ठा emअगर_regs *get_regs(काष्ठा emअगर_data *emअगर, u32 freq)
अणु
	पूर्णांक			i;
	काष्ठा emअगर_regs	**regs_cache;
	काष्ठा emअगर_regs	*regs = शून्य;
	काष्ठा device		*dev;

	dev = emअगर->dev;
	अगर (emअगर->curr_regs && emअगर->curr_regs->freq == freq) अणु
		dev_dbg(dev, "%s: using curr_regs - %u Hz", __func__, freq);
		वापस emअगर->curr_regs;
	पूर्ण

	अगर (emअगर->duplicate)
		regs_cache = emअगर1->regs_cache;
	अन्यथा
		regs_cache = emअगर->regs_cache;

	क्रम (i = 0; i < EMIF_MAX_NUM_FREQUENCIES && regs_cache[i]; i++) अणु
		अगर (regs_cache[i]->freq == freq) अणु
			regs = regs_cache[i];
			dev_dbg(dev,
				"%s: reg dump found in reg cache for %u Hz\n",
				__func__, freq);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If we करोn't have an entry क्रम this frequency in the cache create one
	 * and calculate the values
	 */
	अगर (!regs) अणु
		regs = devm_kzalloc(emअगर->dev, माप(*regs), GFP_ATOMIC);
		अगर (!regs)
			वापस शून्य;

		अगर (get_emअगर_reg_values(emअगर, freq, regs)) अणु
			devm_kमुक्त(emअगर->dev, regs);
			वापस शून्य;
		पूर्ण

		/*
		 * Now look क्रम an un-used entry in the cache and save the
		 * newly created काष्ठा. If there are no मुक्त entries
		 * over-ग_लिखो the last entry
		 */
		क्रम (i = 0; i < EMIF_MAX_NUM_FREQUENCIES && regs_cache[i]; i++)
			;

		अगर (i >= EMIF_MAX_NUM_FREQUENCIES) अणु
			dev_warn(dev, "%s: regs_cache full - reusing a slot!!\n",
				__func__);
			i = EMIF_MAX_NUM_FREQUENCIES - 1;
			devm_kमुक्त(emअगर->dev, regs_cache[i]);
		पूर्ण
		regs_cache[i] = regs;
	पूर्ण

	वापस regs;
पूर्ण

अटल व्योम करो_volt_notअगरy_handling(काष्ठा emअगर_data *emअगर, u32 volt_state)
अणु
	dev_dbg(emअगर->dev, "%s: voltage notification : %d", __func__,
		volt_state);

	अगर (!emअगर->curr_regs) अणु
		dev_err(emअगर->dev,
			"%s: volt-notify before registers are ready: %d\n",
			__func__, volt_state);
		वापस;
	पूर्ण

	setup_volt_sensitive_regs(emअगर, emअगर->curr_regs, volt_state);
पूर्ण

/*
 * TODO: voltage notअगरy handling should be hooked up to
 * regulator framework as soon as the necessary support
 * is available in मुख्यline kernel. This function is un-used
 * right now.
 */
अटल व्योम __attribute__((unused)) volt_notअगरy_handling(u32 volt_state)
अणु
	काष्ठा emअगर_data *emअगर;

	spin_lock_irqsave(&emअगर_lock, irq_state);

	list_क्रम_each_entry(emअगर, &device_list, node)
		करो_volt_notअगरy_handling(emअगर, volt_state);
	करो_freq_update();

	spin_unlock_irqrestore(&emअगर_lock, irq_state);
पूर्ण

अटल व्योम करो_freq_pre_notअगरy_handling(काष्ठा emअगर_data *emअगर, u32 new_freq)
अणु
	काष्ठा emअगर_regs *regs;

	regs = get_regs(emअगर, new_freq);
	अगर (!regs)
		वापस;

	emअगर->curr_regs = regs;

	/*
	 * Update the shaकरोw रेजिस्टरs:
	 * Temperature and voltage-ramp sensitive settings are also configured
	 * in terms of DDR cycles. So, we need to update them too when there
	 * is a freq change
	 */
	dev_dbg(emअगर->dev, "%s: setting up shadow registers for %uHz",
		__func__, new_freq);
	setup_रेजिस्टरs(emअगर, regs);
	setup_temperature_sensitive_regs(emअगर, regs);
	setup_volt_sensitive_regs(emअगर, regs, DDR_VOLTAGE_STABLE);

	/*
	 * Part of workaround क्रम errata i728. See करो_freq_update()
	 * क्रम more details
	 */
	अगर (emअगर->lpmode == EMIF_LP_MODE_SELF_REFRESH)
		set_lpmode(emअगर, EMIF_LP_MODE_DISABLE);
पूर्ण

/*
 * TODO: frequency notअगरy handling should be hooked up to
 * घड़ी framework as soon as the necessary support is
 * available in मुख्यline kernel. This function is un-used
 * right now.
 */
अटल व्योम __attribute__((unused)) freq_pre_notअगरy_handling(u32 new_freq)
अणु
	काष्ठा emअगर_data *emअगर;

	/*
	 * NOTE: we are taking the spin-lock here and releases it
	 * only in post-notअगरier. This करोesn't look good and
	 * Sparse complains about it, but this seems to be
	 * un-aव्योमable. We need to lock a sequence of events
	 * that is split between EMIF and घड़ी framework.
	 *
	 * 1. EMIF driver updates EMIF timings in shaकरोw रेजिस्टरs in the
	 *    frequency pre-notअगरy callback from घड़ी framework
	 * 2. घड़ी framework sets up the रेजिस्टरs क्रम the new frequency
	 * 3. घड़ी framework initiates a hw-sequence that updates
	 *    the frequency EMIF timings synchronously.
	 *
	 * All these 3 steps should be perक्रमmed as an atomic operation
	 * vis-a-vis similar sequence in the EMIF पूर्णांकerrupt handler
	 * क्रम temperature events. Otherwise, there could be race
	 * conditions that could result in incorrect EMIF timings क्रम
	 * a given frequency
	 */
	spin_lock_irqsave(&emअगर_lock, irq_state);

	list_क्रम_each_entry(emअगर, &device_list, node)
		करो_freq_pre_notअगरy_handling(emअगर, new_freq);
पूर्ण

अटल व्योम करो_freq_post_notअगरy_handling(काष्ठा emअगर_data *emअगर)
अणु
	/*
	 * Part of workaround क्रम errata i728. See करो_freq_update()
	 * क्रम more details
	 */
	अगर (emअगर->lpmode == EMIF_LP_MODE_SELF_REFRESH)
		set_lpmode(emअगर, EMIF_LP_MODE_SELF_REFRESH);
पूर्ण

/*
 * TODO: frequency notअगरy handling should be hooked up to
 * घड़ी framework as soon as the necessary support is
 * available in मुख्यline kernel. This function is un-used
 * right now.
 */
अटल व्योम __attribute__((unused)) freq_post_notअगरy_handling(व्योम)
अणु
	काष्ठा emअगर_data *emअगर;

	list_क्रम_each_entry(emअगर, &device_list, node)
		करो_freq_post_notअगरy_handling(emअगर);

	/*
	 * Lock is करोne in pre-notअगरy handler. See freq_pre_notअगरy_handling()
	 * क्रम more details
	 */
	spin_unlock_irqrestore(&emअगर_lock, irq_state);
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id emअगर_of_match[] = अणु
		अणु .compatible = "ti,emif-4d" पूर्ण,
		अणु .compatible = "ti,emif-4d5" पूर्ण,
		अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, emअगर_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver emअगर_driver = अणु
	.हटाओ		= __निकास_p(emअगर_हटाओ),
	.shutकरोwn	= emअगर_shutकरोwn,
	.driver = अणु
		.name = "emif",
		.of_match_table = of_match_ptr(emअगर_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(emअगर_driver, emअगर_probe);

MODULE_DESCRIPTION("TI EMIF SDRAM Controller Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:emif");
MODULE_AUTHOR("Texas Instruments Inc");
