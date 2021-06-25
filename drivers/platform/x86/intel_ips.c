<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2009-2010 Intel Corporation
 *
 * Authors:
 *	Jesse Barnes <jbarnes@virtuousgeek.org>
 */

/*
 * Some Intel Ibex Peak based platक्रमms support so-called "पूर्णांकelligent
 * घातer sharing", which allows the CPU and GPU to cooperate to maximize
 * perक्रमmance within a given TDP (thermal design poपूर्णांक).  This driver
 * perक्रमms the coordination between the CPU and GPU, monitors thermal and
 * घातer statistics in the platक्रमm, and initializes घातer monitoring
 * hardware.  It also provides a few tunables to control behavior.  Its
 * primary purpose is to safely allow CPU and GPU turbo modes to be enabled
 * by tracking घातer and thermal budget; secondarily it can boost turbo
 * perक्रमmance by allocating more घातer or thermal budget to the CPU or GPU
 * based on available headroom and activity.
 *
 * The basic algorithm is driven by a 5s moving average of temperature.  If
 * thermal headroom is available, the CPU and/or GPU घातer clamps may be
 * adjusted upwards.  If we hit the thermal उच्चमानing or a thermal trigger,
 * we scale back the clamp.  Aside from trigger events (when we're critically
 * बंद or over our TDP) we करोn't adjust the clamps more than once every
 * five seconds.
 *
 * The thermal device (device 31, function 6) has a set of रेजिस्टरs that
 * are updated by the ME firmware.  The ME should also take the clamp values
 * written to those रेजिस्टरs and ग_लिखो them to the CPU, but we currently
 * bypass that functionality and ग_लिखो the CPU MSR directly.
 *
 * UNSUPPORTED:
 *   - dual MCP configs
 *
 * TODO:
 *   - handle CPU hotplug
 *   - provide turbo enable/disable api
 *
 * Related करोcuments:
 *   - CDI 403777, 403778 - Auburndale EDS vol 1 & 2
 *   - CDI 401376 - Ibex Peak EDS
 *   - ref 26037, 26641 - IPS BIOS spec
 *   - ref 26489 - Nehalem BIOS ग_लिखोr's guide
 *   - ref 26921 - Ibex Peak BIOS Specअगरication
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/tick.h>
#समावेश <linux/समयr.h>
#समावेश <linux/dmi.h>
#समावेश <drm/i915_drm.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/processor.h>
#समावेश "intel_ips.h"

#समावेश <linux/io-64-nonatomic-lo-hi.h>

#घोषणा PCI_DEVICE_ID_INTEL_THERMAL_SENSOR 0x3b32

/*
 * Package level MSRs क्रम monitor/control
 */
#घोषणा PLATFORM_INFO	0xce
#घोषणा   PLATFORM_TDP		(1<<29)
#घोषणा   PLATFORM_RATIO	(1<<28)

#घोषणा IA32_MISC_ENABLE	0x1a0
#घोषणा   IA32_MISC_TURBO_EN	(1ULL<<38)

#घोषणा TURBO_POWER_CURRENT_LIMIT	0x1ac
#घोषणा   TURBO_TDC_OVR_EN	(1UL<<31)
#घोषणा   TURBO_TDC_MASK	(0x000000007fff0000UL)
#घोषणा   TURBO_TDC_SHIFT	(16)
#घोषणा   TURBO_TDP_OVR_EN	(1UL<<15)
#घोषणा   TURBO_TDP_MASK	(0x0000000000003fffUL)

/*
 * Core/thपढ़ो MSRs क्रम monitoring
 */
#घोषणा IA32_PERF_CTL		0x199
#घोषणा   IA32_PERF_TURBO_DIS	(1ULL<<32)

/*
 * Thermal PCI device regs
 */
#घोषणा THM_CFG_TBAR	0x10
#घोषणा THM_CFG_TBAR_HI	0x14

#घोषणा THM_TSIU	0x00
#घोषणा THM_TSE		0x01
#घोषणा   TSE_EN	0xb8
#घोषणा THM_TSS		0x02
#घोषणा THM_TSTR	0x03
#घोषणा THM_TSTTP	0x04
#घोषणा THM_TSCO	0x08
#घोषणा THM_TSES	0x0c
#घोषणा THM_TSGPEN	0x0d
#घोषणा   TSGPEN_HOT_LOHI	(1<<1)
#घोषणा   TSGPEN_CRIT_LOHI	(1<<2)
#घोषणा THM_TSPC	0x0e
#घोषणा THM_PPEC	0x10
#घोषणा THM_CTA		0x12
#घोषणा THM_PTA		0x14
#घोषणा   PTA_SLOPE_MASK	(0xff00)
#घोषणा   PTA_SLOPE_SHIFT	8
#घोषणा   PTA_OFFSET_MASK	(0x00ff)
#घोषणा THM_MGTA	0x16
#घोषणा   MGTA_SLOPE_MASK	(0xff00)
#घोषणा   MGTA_SLOPE_SHIFT	8
#घोषणा   MGTA_OFFSET_MASK	(0x00ff)
#घोषणा THM_TRC		0x1a
#घोषणा   TRC_CORE2_EN	(1<<15)
#घोषणा   TRC_THM_EN	(1<<12)
#घोषणा   TRC_C6_WAR	(1<<8)
#घोषणा   TRC_CORE1_EN	(1<<7)
#घोषणा   TRC_CORE_PWR	(1<<6)
#घोषणा   TRC_PCH_EN	(1<<5)
#घोषणा   TRC_MCH_EN	(1<<4)
#घोषणा   TRC_DIMM4	(1<<3)
#घोषणा   TRC_DIMM3	(1<<2)
#घोषणा   TRC_DIMM2	(1<<1)
#घोषणा   TRC_DIMM1	(1<<0)
#घोषणा THM_TES		0x20
#घोषणा THM_TEN		0x21
#घोषणा   TEN_UPDATE_EN	1
#घोषणा THM_PSC		0x24
#घोषणा   PSC_NTG	(1<<0) /* No GFX turbo support */
#घोषणा   PSC_NTPC	(1<<1) /* No CPU turbo support */
#घोषणा   PSC_PP_DEF	(0<<2) /* Perf policy up to driver */
#घोषणा   PSP_PP_PC	(1<<2) /* BIOS prefers CPU perf */
#घोषणा   PSP_PP_BAL	(2<<2) /* BIOS wants balanced perf */
#घोषणा   PSP_PP_GFX	(3<<2) /* BIOS prefers GFX perf */
#घोषणा   PSP_PBRT	(1<<4) /* BIOS run समय support */
#घोषणा THM_CTV1	0x30
#घोषणा   CTV_TEMP_ERROR (1<<15)
#घोषणा   CTV_TEMP_MASK	0x3f
#घोषणा   CTV_
#घोषणा THM_CTV2	0x32
#घोषणा THM_CEC		0x34 /* unकरोcumented घातer accumulator in joules */
#घोषणा THM_AE		0x3f
#घोषणा THM_HTS		0x50 /* 32 bits */
#घोषणा   HTS_PCPL_MASK	(0x7fe00000)
#घोषणा   HTS_PCPL_SHIFT 21
#घोषणा   HTS_GPL_MASK  (0x001ff000)
#घोषणा   HTS_GPL_SHIFT 12
#घोषणा   HTS_PP_MASK	(0x00000c00)
#घोषणा   HTS_PP_SHIFT  10
#घोषणा   HTS_PP_DEF	0
#घोषणा   HTS_PP_PROC	1
#घोषणा   HTS_PP_BAL	2
#घोषणा   HTS_PP_GFX	3
#घोषणा   HTS_PCTD_DIS	(1<<9)
#घोषणा   HTS_GTD_DIS	(1<<8)
#घोषणा   HTS_PTL_MASK  (0x000000fe)
#घोषणा   HTS_PTL_SHIFT 1
#घोषणा   HTS_NVV	(1<<0)
#घोषणा THM_HTSHI	0x54 /* 16 bits */
#घोषणा   HTS2_PPL_MASK		(0x03ff)
#घोषणा   HTS2_PRST_MASK	(0x3c00)
#घोषणा   HTS2_PRST_SHIFT	10
#घोषणा   HTS2_PRST_UNLOADED	0
#घोषणा   HTS2_PRST_RUNNING	1
#घोषणा   HTS2_PRST_TDISOP	2 /* turbo disabled due to घातer */
#घोषणा   HTS2_PRST_TDISHT	3 /* turbo disabled due to high temp */
#घोषणा   HTS2_PRST_TDISUSR	4 /* user disabled turbo */
#घोषणा   HTS2_PRST_TDISPLAT	5 /* platक्रमm disabled turbo */
#घोषणा   HTS2_PRST_TDISPM	6 /* घातer management disabled turbo */
#घोषणा   HTS2_PRST_TDISERR	7 /* some kind of error disabled turbo */
#घोषणा THM_PTL		0x56
#घोषणा THM_MGTV	0x58
#घोषणा   TV_MASK	0x000000000000ff00
#घोषणा   TV_SHIFT	8
#घोषणा THM_PTV		0x60
#घोषणा   PTV_MASK	0x00ff
#घोषणा THM_MMGPC	0x64
#घोषणा THM_MPPC	0x66
#घोषणा THM_MPCPC	0x68
#घोषणा THM_TSPIEN	0x82
#घोषणा   TSPIEN_AUX_LOHI	(1<<0)
#घोषणा   TSPIEN_HOT_LOHI	(1<<1)
#घोषणा   TSPIEN_CRIT_LOHI	(1<<2)
#घोषणा   TSPIEN_AUX2_LOHI	(1<<3)
#घोषणा THM_TSLOCK	0x83
#घोषणा THM_ATR		0x84
#घोषणा THM_TOF		0x87
#घोषणा THM_STS		0x98
#घोषणा   STS_PCPL_MASK		(0x7fe00000)
#घोषणा   STS_PCPL_SHIFT	21
#घोषणा   STS_GPL_MASK		(0x001ff000)
#घोषणा   STS_GPL_SHIFT		12
#घोषणा   STS_PP_MASK		(0x00000c00)
#घोषणा   STS_PP_SHIFT		10
#घोषणा   STS_PP_DEF		0
#घोषणा   STS_PP_PROC		1
#घोषणा   STS_PP_BAL		2
#घोषणा   STS_PP_GFX		3
#घोषणा   STS_PCTD_DIS		(1<<9)
#घोषणा   STS_GTD_DIS		(1<<8)
#घोषणा   STS_PTL_MASK		(0x000000fe)
#घोषणा   STS_PTL_SHIFT		1
#घोषणा   STS_NVV		(1<<0)
#घोषणा THM_SEC		0x9c
#घोषणा   SEC_ACK	(1<<0)
#घोषणा THM_TC3		0xa4
#घोषणा THM_TC1		0xa8
#घोषणा   STS_PPL_MASK		(0x0003ff00)
#घोषणा   STS_PPL_SHIFT		16
#घोषणा THM_TC2		0xac
#घोषणा THM_DTV		0xb0
#घोषणा THM_ITV		0xd8
#घोषणा   ITV_ME_SEQNO_MASK 0x00ff0000 /* ME should update every ~200ms */
#घोषणा   ITV_ME_SEQNO_SHIFT (16)
#घोषणा   ITV_MCH_TEMP_MASK 0x0000ff00
#घोषणा   ITV_MCH_TEMP_SHIFT (8)
#घोषणा   ITV_PCH_TEMP_MASK 0x000000ff

#घोषणा thm_पढ़ोb(off) पढ़ोb(ips->regmap + (off))
#घोषणा thm_पढ़ोw(off) पढ़ोw(ips->regmap + (off))
#घोषणा thm_पढ़ोl(off) पढ़ोl(ips->regmap + (off))
#घोषणा thm_पढ़ोq(off) पढ़ोq(ips->regmap + (off))

#घोषणा thm_ग_लिखोb(off, val) ग_लिखोb((val), ips->regmap + (off))
#घोषणा thm_ग_लिखोw(off, val) ग_लिखोw((val), ips->regmap + (off))
#घोषणा thm_ग_लिखोl(off, val) ग_लिखोl((val), ips->regmap + (off))

अटल स्थिर पूर्णांक IPS_ADJUST_PERIOD = 5000; /* ms */
अटल bool late_i915_load = false;

/* For initial average collection */
अटल स्थिर पूर्णांक IPS_SAMPLE_PERIOD = 200; /* ms */
अटल स्थिर पूर्णांक IPS_SAMPLE_WINDOW = 5000; /* 5s moving winकरोw of samples */
#घोषणा IPS_SAMPLE_COUNT (IPS_SAMPLE_WINDOW / IPS_SAMPLE_PERIOD)

/* Per-SKU limits */
काष्ठा ips_mcp_limits अणु
	पूर्णांक mcp_घातer_limit; /* mW units */
	पूर्णांक core_घातer_limit;
	पूर्णांक mch_घातer_limit;
	पूर्णांक core_temp_limit; /* degrees C */
	पूर्णांक mch_temp_limit;
पूर्ण;

/* Max temps are -10 degrees C to aव्योम PROCHOT# */

अटल काष्ठा ips_mcp_limits ips_sv_limits = अणु
	.mcp_घातer_limit = 35000,
	.core_घातer_limit = 29000,
	.mch_घातer_limit = 20000,
	.core_temp_limit = 95,
	.mch_temp_limit = 90
पूर्ण;

अटल काष्ठा ips_mcp_limits ips_lv_limits = अणु
	.mcp_घातer_limit = 25000,
	.core_घातer_limit = 21000,
	.mch_घातer_limit = 13000,
	.core_temp_limit = 95,
	.mch_temp_limit = 90
पूर्ण;

अटल काष्ठा ips_mcp_limits ips_ulv_limits = अणु
	.mcp_घातer_limit = 18000,
	.core_घातer_limit = 14000,
	.mch_घातer_limit = 11000,
	.core_temp_limit = 95,
	.mch_temp_limit = 90
पूर्ण;

काष्ठा ips_driver अणु
	काष्ठा device *dev;
	व्योम __iomem *regmap;
	पूर्णांक irq;

	काष्ठा task_काष्ठा *monitor;
	काष्ठा task_काष्ठा *adjust;
	काष्ठा dentry *debug_root;
	काष्ठा समयr_list समयr;

	/* Average CPU core temps (all averages in .01 degrees C क्रम precision) */
	u16 ctv1_avg_temp;
	u16 ctv2_avg_temp;
	/* GMCH average */
	u16 mch_avg_temp;
	/* Average क्रम the CPU (both cores?) */
	u16 mcp_avg_temp;
	/* Average घातer consumption (in mW) */
	u32 cpu_avg_घातer;
	u32 mch_avg_घातer;

	/* Offset values */
	u16 cta_val;
	u16 pta_val;
	u16 mgta_val;

	/* Maximums & prefs, रक्षित by turbo status lock */
	spinlock_t turbo_status_lock;
	u16 mcp_temp_limit;
	u16 mcp_घातer_limit;
	u16 core_घातer_limit;
	u16 mch_घातer_limit;
	bool cpu_turbo_enabled;
	bool __cpu_turbo_on;
	bool gpu_turbo_enabled;
	bool __gpu_turbo_on;
	bool gpu_preferred;
	bool poll_turbo_status;
	bool second_cpu;
	bool turbo_toggle_allowed;
	काष्ठा ips_mcp_limits *limits;

	/* Optional MCH पूर्णांकerfaces क्रम अगर i915 is in use */
	अचिन्हित दीर्घ (*पढ़ो_mch_val)(व्योम);
	bool (*gpu_उठाओ)(व्योम);
	bool (*gpu_lower)(व्योम);
	bool (*gpu_busy)(व्योम);
	bool (*gpu_turbo_disable)(व्योम);

	/* For restoration at unload */
	u64 orig_turbo_limit;
	u64 orig_turbo_ratios;
पूर्ण;

अटल bool
ips_gpu_turbo_enabled(काष्ठा ips_driver *ips);

/**
 * ips_cpu_busy - is CPU busy?
 * @ips: IPS driver काष्ठा
 *
 * Check CPU क्रम load to see whether we should increase its thermal budget.
 *
 * RETURNS:
 * True अगर the CPU could use more घातer, false otherwise.
 */
अटल bool ips_cpu_busy(काष्ठा ips_driver *ips)
अणु
	अगर ((avenrun[0] >> FSHIFT) > 1)
		वापस true;

	वापस false;
पूर्ण

/**
 * ips_cpu_उठाओ - उठाओ CPU घातer clamp
 * @ips: IPS driver काष्ठा
 *
 * Raise the CPU घातer clamp by %IPS_CPU_STEP, in accordance with TDP क्रम
 * this platक्रमm.
 *
 * We करो this by adjusting the TURBO_POWER_CURRENT_LIMIT MSR upwards (as
 * दीर्घ as we haven't hit the TDP limit क्रम the SKU).
 */
अटल व्योम ips_cpu_उठाओ(काष्ठा ips_driver *ips)
अणु
	u64 turbo_override;
	u16 cur_tdp_limit, new_tdp_limit;

	अगर (!ips->cpu_turbo_enabled)
		वापस;

	rdmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);

	cur_tdp_limit = turbo_override & TURBO_TDP_MASK;
	new_tdp_limit = cur_tdp_limit + 8; /* 1W increase */

	/* Clamp to SKU TDP limit */
	अगर (((new_tdp_limit * 10) / 8) > ips->core_घातer_limit)
		new_tdp_limit = cur_tdp_limit;

	thm_ग_लिखोw(THM_MPCPC, (new_tdp_limit * 10) / 8);

	turbo_override |= TURBO_TDC_OVR_EN | TURBO_TDP_OVR_EN;
	wrmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);

	turbo_override &= ~TURBO_TDP_MASK;
	turbo_override |= new_tdp_limit;

	wrmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);
पूर्ण

/**
 * ips_cpu_lower - lower CPU घातer clamp
 * @ips: IPS driver काष्ठा
 *
 * Lower CPU घातer clamp b %IPS_CPU_STEP अगर possible.
 *
 * We करो this by adjusting the TURBO_POWER_CURRENT_LIMIT MSR करोwn, going
 * as low as the platक्रमm limits will allow (though we could go lower there
 * wouldn't be much poपूर्णांक).
 */
अटल व्योम ips_cpu_lower(काष्ठा ips_driver *ips)
अणु
	u64 turbo_override;
	u16 cur_limit, new_limit;

	rdmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);

	cur_limit = turbo_override & TURBO_TDP_MASK;
	new_limit = cur_limit - 8; /* 1W decrease */

	/* Clamp to SKU TDP limit */
	अगर (new_limit  < (ips->orig_turbo_limit & TURBO_TDP_MASK))
		new_limit = ips->orig_turbo_limit & TURBO_TDP_MASK;

	thm_ग_लिखोw(THM_MPCPC, (new_limit * 10) / 8);

	turbo_override |= TURBO_TDC_OVR_EN | TURBO_TDP_OVR_EN;
	wrmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);

	turbo_override &= ~TURBO_TDP_MASK;
	turbo_override |= new_limit;

	wrmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);
पूर्ण

/**
 * करो_enable_cpu_turbo - पूर्णांकernal turbo enable function
 * @data: unused
 *
 * Internal function क्रम actually updating MSRs.  When we enable/disable
 * turbo, we need to करो it on each CPU; this function is the one called
 * by on_each_cpu() when needed.
 */
अटल व्योम करो_enable_cpu_turbo(व्योम *data)
अणु
	u64 perf_ctl;

	rdmsrl(IA32_PERF_CTL, perf_ctl);
	अगर (perf_ctl & IA32_PERF_TURBO_DIS) अणु
		perf_ctl &= ~IA32_PERF_TURBO_DIS;
		wrmsrl(IA32_PERF_CTL, perf_ctl);
	पूर्ण
पूर्ण

/**
 * ips_enable_cpu_turbo - enable turbo mode on all CPUs
 * @ips: IPS driver काष्ठा
 *
 * Enable turbo mode by clearing the disable bit in IA32_PERF_CTL on
 * all logical thपढ़ोs.
 */
अटल व्योम ips_enable_cpu_turbo(काष्ठा ips_driver *ips)
अणु
	/* Alपढ़ोy on, no need to mess with MSRs */
	अगर (ips->__cpu_turbo_on)
		वापस;

	अगर (ips->turbo_toggle_allowed)
		on_each_cpu(करो_enable_cpu_turbo, ips, 1);

	ips->__cpu_turbo_on = true;
पूर्ण

/**
 * करो_disable_cpu_turbo - पूर्णांकernal turbo disable function
 * @data: unused
 *
 * Internal function क्रम actually updating MSRs.  When we enable/disable
 * turbo, we need to करो it on each CPU; this function is the one called
 * by on_each_cpu() when needed.
 */
अटल व्योम करो_disable_cpu_turbo(व्योम *data)
अणु
	u64 perf_ctl;

	rdmsrl(IA32_PERF_CTL, perf_ctl);
	अगर (!(perf_ctl & IA32_PERF_TURBO_DIS)) अणु
		perf_ctl |= IA32_PERF_TURBO_DIS;
		wrmsrl(IA32_PERF_CTL, perf_ctl);
	पूर्ण
पूर्ण

/**
 * ips_disable_cpu_turbo - disable turbo mode on all CPUs
 * @ips: IPS driver काष्ठा
 *
 * Disable turbo mode by setting the disable bit in IA32_PERF_CTL on
 * all logical thपढ़ोs.
 */
अटल व्योम ips_disable_cpu_turbo(काष्ठा ips_driver *ips)
अणु
	/* Alपढ़ोy off, leave it */
	अगर (!ips->__cpu_turbo_on)
		वापस;

	अगर (ips->turbo_toggle_allowed)
		on_each_cpu(करो_disable_cpu_turbo, ips, 1);

	ips->__cpu_turbo_on = false;
पूर्ण

/**
 * ips_gpu_busy - is GPU busy?
 * @ips: IPS driver काष्ठा
 *
 * Check GPU क्रम load to see whether we should increase its thermal budget.
 * We need to call पूर्णांकo the i915 driver in this हाल.
 *
 * RETURNS:
 * True अगर the GPU could use more घातer, false otherwise.
 */
अटल bool ips_gpu_busy(काष्ठा ips_driver *ips)
अणु
	अगर (!ips_gpu_turbo_enabled(ips))
		वापस false;

	वापस ips->gpu_busy();
पूर्ण

/**
 * ips_gpu_उठाओ - उठाओ GPU घातer clamp
 * @ips: IPS driver काष्ठा
 *
 * Raise the GPU frequency/घातer अगर possible.  We need to call पूर्णांकo the
 * i915 driver in this हाल.
 */
अटल व्योम ips_gpu_उठाओ(काष्ठा ips_driver *ips)
अणु
	अगर (!ips_gpu_turbo_enabled(ips))
		वापस;

	अगर (!ips->gpu_उठाओ())
		ips->gpu_turbo_enabled = false;

	वापस;
पूर्ण

/**
 * ips_gpu_lower - lower GPU घातer clamp
 * @ips: IPS driver काष्ठा
 *
 * Lower GPU frequency/घातer अगर possible.  Need to call i915.
 */
अटल व्योम ips_gpu_lower(काष्ठा ips_driver *ips)
अणु
	अगर (!ips_gpu_turbo_enabled(ips))
		वापस;

	अगर (!ips->gpu_lower())
		ips->gpu_turbo_enabled = false;

	वापस;
पूर्ण

/**
 * ips_enable_gpu_turbo - notअगरy the gfx driver turbo is available
 * @ips: IPS driver काष्ठा
 *
 * Call पूर्णांकo the graphics driver indicating that it can safely use
 * turbo mode.
 */
अटल व्योम ips_enable_gpu_turbo(काष्ठा ips_driver *ips)
अणु
	अगर (ips->__gpu_turbo_on)
		वापस;
	ips->__gpu_turbo_on = true;
पूर्ण

/**
 * ips_disable_gpu_turbo - notअगरy the gfx driver to disable turbo mode
 * @ips: IPS driver काष्ठा
 *
 * Request that the graphics driver disable turbo mode.
 */
अटल व्योम ips_disable_gpu_turbo(काष्ठा ips_driver *ips)
अणु
	/* Aव्योम calling i915 अगर turbo is alपढ़ोy disabled */
	अगर (!ips->__gpu_turbo_on)
		वापस;

	अगर (!ips->gpu_turbo_disable())
		dev_err(ips->dev, "failed to disable graphics turbo\n");
	अन्यथा
		ips->__gpu_turbo_on = false;
पूर्ण

/**
 * mcp_exceeded - check whether we're outside our thermal & घातer limits
 * @ips: IPS driver काष्ठा
 *
 * Check whether the MCP is over its thermal or घातer budget.
 */
अटल bool mcp_exceeded(काष्ठा ips_driver *ips)
अणु
	अचिन्हित दीर्घ flags;
	bool ret = false;
	u32 temp_limit;
	u32 avg_घातer;

	spin_lock_irqsave(&ips->turbo_status_lock, flags);

	temp_limit = ips->mcp_temp_limit * 100;
	अगर (ips->mcp_avg_temp > temp_limit)
		ret = true;

	avg_घातer = ips->cpu_avg_घातer + ips->mch_avg_घातer;
	अगर (avg_घातer > ips->mcp_घातer_limit)
		ret = true;

	spin_unlock_irqrestore(&ips->turbo_status_lock, flags);

	वापस ret;
पूर्ण

/**
 * cpu_exceeded - check whether a CPU core is outside its limits
 * @ips: IPS driver काष्ठा
 * @cpu: CPU number to check
 *
 * Check a given CPU's average temp or घातer is over its limit.
 */
अटल bool cpu_exceeded(काष्ठा ips_driver *ips, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक avg;
	bool ret = false;

	spin_lock_irqsave(&ips->turbo_status_lock, flags);
	avg = cpu ? ips->ctv2_avg_temp : ips->ctv1_avg_temp;
	अगर (avg > (ips->limits->core_temp_limit * 100))
		ret = true;
	अगर (ips->cpu_avg_घातer > ips->core_घातer_limit * 100)
		ret = true;
	spin_unlock_irqrestore(&ips->turbo_status_lock, flags);

	अगर (ret)
		dev_info(ips->dev, "CPU power or thermal limit exceeded\n");

	वापस ret;
पूर्ण

/**
 * mch_exceeded - check whether the GPU is over budget
 * @ips: IPS driver काष्ठा
 *
 * Check the MCH temp & घातer against their maximums.
 */
अटल bool mch_exceeded(काष्ठा ips_driver *ips)
अणु
	अचिन्हित दीर्घ flags;
	bool ret = false;

	spin_lock_irqsave(&ips->turbo_status_lock, flags);
	अगर (ips->mch_avg_temp > (ips->limits->mch_temp_limit * 100))
		ret = true;
	अगर (ips->mch_avg_घातer > ips->mch_घातer_limit)
		ret = true;
	spin_unlock_irqrestore(&ips->turbo_status_lock, flags);

	वापस ret;
पूर्ण

/**
 * verअगरy_limits - verअगरy BIOS provided limits
 * @ips: IPS काष्ठाure
 *
 * BIOS can optionally provide non-शेष limits क्रम घातer and temp.  Check
 * them here and use the शेषs अगर the BIOS values are not provided or
 * are otherwise unusable.
 */
अटल व्योम verअगरy_limits(काष्ठा ips_driver *ips)
अणु
	अगर (ips->mcp_घातer_limit < ips->limits->mcp_घातer_limit ||
	    ips->mcp_घातer_limit > 35000)
		ips->mcp_घातer_limit = ips->limits->mcp_घातer_limit;

	अगर (ips->mcp_temp_limit < ips->limits->core_temp_limit ||
	    ips->mcp_temp_limit < ips->limits->mch_temp_limit ||
	    ips->mcp_temp_limit > 150)
		ips->mcp_temp_limit = min(ips->limits->core_temp_limit,
					  ips->limits->mch_temp_limit);
पूर्ण

/**
 * update_turbo_limits - get various limits & settings from regs
 * @ips: IPS driver काष्ठा
 *
 * Update the IPS घातer & temp limits, aदीर्घ with turbo enable flags,
 * based on latest रेजिस्टर contents.
 *
 * Used at init समय and क्रम runसमय BIOS support, which requires polling
 * the regs क्रम updates (as a result of AC->DC transition क्रम example).
 *
 * LOCKING:
 * Caller must hold turbo_status_lock (outside of init)
 */
अटल व्योम update_turbo_limits(काष्ठा ips_driver *ips)
अणु
	u32 hts = thm_पढ़ोl(THM_HTS);

	ips->cpu_turbo_enabled = !(hts & HTS_PCTD_DIS);
	/* 
	 * Disable turbo क्रम now, until we can figure out why the घातer figures
	 * are wrong
	 */
	ips->cpu_turbo_enabled = false;

	अगर (ips->gpu_busy)
		ips->gpu_turbo_enabled = !(hts & HTS_GTD_DIS);

	ips->core_घातer_limit = thm_पढ़ोw(THM_MPCPC);
	ips->mch_घातer_limit = thm_पढ़ोw(THM_MMGPC);
	ips->mcp_temp_limit = thm_पढ़ोw(THM_PTL);
	ips->mcp_घातer_limit = thm_पढ़ोw(THM_MPPC);

	verअगरy_limits(ips);
	/* Ignore BIOS CPU vs GPU pref */
पूर्ण

/**
 * ips_adjust - adjust घातer clamp based on thermal state
 * @data: ips driver काष्ठाure
 *
 * Wake up every 5s or so and check whether we should adjust the घातer clamp.
 * Check CPU and GPU load to determine which needs adjusपंचांगent.  There are
 * several things to consider here:
 *   - करो we need to adjust up or करोwn?
 *   - is CPU busy?
 *   - is GPU busy?
 *   - is CPU in turbo?
 *   - is GPU in turbo?
 *   - is CPU or GPU preferred? (CPU is शेष)
 *
 * So, given the above, we करो the following:
 *   - up (TDP available)
 *     - CPU not busy, GPU not busy - nothing
 *     - CPU busy, GPU not busy - adjust CPU up
 *     - CPU not busy, GPU busy - adjust GPU up
 *     - CPU busy, GPU busy - adjust preferred unit up, taking headroom from
 *       non-preferred unit अगर necessary
 *   - करोwn (at TDP limit)
 *     - adjust both CPU and GPU करोwn अगर possible
 *
		cpu+ gpu+	cpu+gpu-	cpu-gpu+	cpu-gpu-
cpu < gpu <	cpu+gpu+	cpu+		gpu+		nothing
cpu < gpu >=	cpu+gpu-(mcp<)	cpu+gpu-(mcp<)	gpu-		gpu-
cpu >= gpu <	cpu-gpu+(mcp<)	cpu-		cpu-gpu+(mcp<)	cpu-
cpu >= gpu >=	cpu-gpu-	cpu-gpu-	cpu-gpu-	cpu-gpu-
 *
 */
अटल पूर्णांक ips_adjust(व्योम *data)
अणु
	काष्ठा ips_driver *ips = data;
	अचिन्हित दीर्घ flags;

	dev_dbg(ips->dev, "starting ips-adjust thread\n");

	/*
	 * Adjust CPU and GPU clamps every 5s अगर needed.  Doing it more
	 * often isn't recommended due to ME पूर्णांकeraction.
	 */
	करो अणु
		bool cpu_busy = ips_cpu_busy(ips);
		bool gpu_busy = ips_gpu_busy(ips);

		spin_lock_irqsave(&ips->turbo_status_lock, flags);
		अगर (ips->poll_turbo_status)
			update_turbo_limits(ips);
		spin_unlock_irqrestore(&ips->turbo_status_lock, flags);

		/* Update turbo status अगर necessary */
		अगर (ips->cpu_turbo_enabled)
			ips_enable_cpu_turbo(ips);
		अन्यथा
			ips_disable_cpu_turbo(ips);

		अगर (ips->gpu_turbo_enabled)
			ips_enable_gpu_turbo(ips);
		अन्यथा
			ips_disable_gpu_turbo(ips);

		/* We're outside our comक्रमt zone, crank them करोwn */
		अगर (mcp_exceeded(ips)) अणु
			ips_cpu_lower(ips);
			ips_gpu_lower(ips);
			जाओ sleep;
		पूर्ण

		अगर (!cpu_exceeded(ips, 0) && cpu_busy)
			ips_cpu_उठाओ(ips);
		अन्यथा
			ips_cpu_lower(ips);

		अगर (!mch_exceeded(ips) && gpu_busy)
			ips_gpu_उठाओ(ips);
		अन्यथा
			ips_gpu_lower(ips);

sleep:
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(IPS_ADJUST_PERIOD));
	पूर्ण जबतक (!kthपढ़ो_should_stop());

	dev_dbg(ips->dev, "ips-adjust thread stopped\n");

	वापस 0;
पूर्ण

/*
 * Helpers क्रम पढ़ोing out temp/घातer values and calculating their
 * averages क्रम the decision making and monitoring functions.
 */

अटल u16 calc_avg_temp(काष्ठा ips_driver *ips, u16 *array)
अणु
	u64 total = 0;
	पूर्णांक i;
	u16 avg;

	क्रम (i = 0; i < IPS_SAMPLE_COUNT; i++)
		total += (u64)(array[i] * 100);

	करो_भाग(total, IPS_SAMPLE_COUNT);

	avg = (u16)total;

	वापस avg;
पूर्ण

अटल u16 पढ़ो_mgtv(काष्ठा ips_driver *ips)
अणु
	u16 ret;
	u64 slope, offset;
	u64 val;

	val = thm_पढ़ोq(THM_MGTV);
	val = (val & TV_MASK) >> TV_SHIFT;

	slope = offset = thm_पढ़ोw(THM_MGTA);
	slope = (slope & MGTA_SLOPE_MASK) >> MGTA_SLOPE_SHIFT;
	offset = offset & MGTA_OFFSET_MASK;

	ret = ((val * slope + 0x40) >> 7) + offset;

	वापस 0; /* MCH temp reporting buggy */
पूर्ण

अटल u16 पढ़ो_ptv(काष्ठा ips_driver *ips)
अणु
	u16 val;

	val = thm_पढ़ोw(THM_PTV) & PTV_MASK;

	वापस val;
पूर्ण

अटल u16 पढ़ो_ctv(काष्ठा ips_driver *ips, पूर्णांक cpu)
अणु
	पूर्णांक reg = cpu ? THM_CTV2 : THM_CTV1;
	u16 val;

	val = thm_पढ़ोw(reg);
	अगर (!(val & CTV_TEMP_ERROR))
		val = (val) >> 6; /* discard fractional component */
	अन्यथा
		val = 0;

	वापस val;
पूर्ण

अटल u32 get_cpu_घातer(काष्ठा ips_driver *ips, u32 *last, पूर्णांक period)
अणु
	u32 val;
	u32 ret;

	/*
	 * CEC is in joules/65535.  Take dअगरference over समय to
	 * get watts.
	 */
	val = thm_पढ़ोl(THM_CEC);

	/* period is in ms and we want mW */
	ret = (((val - *last) * 1000) / period);
	ret = (ret * 1000) / 65535;
	*last = val;

	वापस 0;
पूर्ण

अटल स्थिर u16 temp_decay_factor = 2;
अटल u16 update_average_temp(u16 avg, u16 val)
अणु
	u16 ret;

	/* Multiply by 100 क्रम extra precision */
	ret = (val * 100 / temp_decay_factor) +
		(((temp_decay_factor - 1) * avg) / temp_decay_factor);
	वापस ret;
पूर्ण

अटल स्थिर u16 घातer_decay_factor = 2;
अटल u16 update_average_घातer(u32 avg, u32 val)
अणु
	u32 ret;

	ret = (val / घातer_decay_factor) +
		(((घातer_decay_factor - 1) * avg) / घातer_decay_factor);

	वापस ret;
पूर्ण

अटल u32 calc_avg_घातer(काष्ठा ips_driver *ips, u32 *array)
अणु
	u64 total = 0;
	u32 avg;
	पूर्णांक i;

	क्रम (i = 0; i < IPS_SAMPLE_COUNT; i++)
		total += array[i];

	करो_भाग(total, IPS_SAMPLE_COUNT);
	avg = (u32)total;

	वापस avg;
पूर्ण

अटल व्योम monitor_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ips_driver *ips = from_समयr(ips, t, समयr);
	wake_up_process(ips->monitor);
पूर्ण

/**
 * ips_monitor - temp/घातer monitoring thपढ़ो
 * @data: ips driver काष्ठाure
 *
 * This is the मुख्य function क्रम the IPS driver.  It monitors घातer and
 * tempurature in the MCP and adjusts CPU and GPU घातer clams accordingly.
 *
 * We keep a 5s moving average of घातer consumption and tempurature.  Using
 * that data, aदीर्घ with CPU vs GPU preference, we adjust the घातer clamps
 * up or करोwn.
 */
अटल पूर्णांक ips_monitor(व्योम *data)
अणु
	काष्ठा ips_driver *ips = data;
	अचिन्हित दीर्घ seqno_बारtamp, expire, last_msecs, last_sample_period;
	पूर्णांक i;
	u32 *cpu_samples, *mchp_samples, old_cpu_घातer;
	u16 *mcp_samples, *ctv1_samples, *ctv2_samples, *mch_samples;
	u8 cur_seqno, last_seqno;

	mcp_samples = kसुस्मृति(IPS_SAMPLE_COUNT, माप(u16), GFP_KERNEL);
	ctv1_samples = kसुस्मृति(IPS_SAMPLE_COUNT, माप(u16), GFP_KERNEL);
	ctv2_samples = kसुस्मृति(IPS_SAMPLE_COUNT, माप(u16), GFP_KERNEL);
	mch_samples = kसुस्मृति(IPS_SAMPLE_COUNT, माप(u16), GFP_KERNEL);
	cpu_samples = kसुस्मृति(IPS_SAMPLE_COUNT, माप(u32), GFP_KERNEL);
	mchp_samples = kसुस्मृति(IPS_SAMPLE_COUNT, माप(u32), GFP_KERNEL);
	अगर (!mcp_samples || !ctv1_samples || !ctv2_samples || !mch_samples ||
			!cpu_samples || !mchp_samples) अणु
		dev_err(ips->dev,
			"failed to allocate sample array, ips disabled\n");
		kमुक्त(mcp_samples);
		kमुक्त(ctv1_samples);
		kमुक्त(ctv2_samples);
		kमुक्त(mch_samples);
		kमुक्त(cpu_samples);
		kमुक्त(mchp_samples);
		वापस -ENOMEM;
	पूर्ण

	last_seqno = (thm_पढ़ोl(THM_ITV) & ITV_ME_SEQNO_MASK) >>
		ITV_ME_SEQNO_SHIFT;
	seqno_बारtamp = get_jअगरfies_64();

	old_cpu_घातer = thm_पढ़ोl(THM_CEC);
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(IPS_SAMPLE_PERIOD));

	/* Collect an initial average */
	क्रम (i = 0; i < IPS_SAMPLE_COUNT; i++) अणु
		u32 mchp, cpu_घातer;
		u16 val;

		mcp_samples[i] = पढ़ो_ptv(ips);

		val = पढ़ो_ctv(ips, 0);
		ctv1_samples[i] = val;

		val = पढ़ो_ctv(ips, 1);
		ctv2_samples[i] = val;

		val = पढ़ो_mgtv(ips);
		mch_samples[i] = val;

		cpu_घातer = get_cpu_घातer(ips, &old_cpu_घातer,
					  IPS_SAMPLE_PERIOD);
		cpu_samples[i] = cpu_घातer;

		अगर (ips->पढ़ो_mch_val) अणु
			mchp = ips->पढ़ो_mch_val();
			mchp_samples[i] = mchp;
		पूर्ण

		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(IPS_SAMPLE_PERIOD));
		अगर (kthपढ़ो_should_stop())
			अवरोध;
	पूर्ण

	ips->mcp_avg_temp = calc_avg_temp(ips, mcp_samples);
	ips->ctv1_avg_temp = calc_avg_temp(ips, ctv1_samples);
	ips->ctv2_avg_temp = calc_avg_temp(ips, ctv2_samples);
	ips->mch_avg_temp = calc_avg_temp(ips, mch_samples);
	ips->cpu_avg_घातer = calc_avg_घातer(ips, cpu_samples);
	ips->mch_avg_घातer = calc_avg_घातer(ips, mchp_samples);
	kमुक्त(mcp_samples);
	kमुक्त(ctv1_samples);
	kमुक्त(ctv2_samples);
	kमुक्त(mch_samples);
	kमुक्त(cpu_samples);
	kमुक्त(mchp_samples);

	/* Start the adjusपंचांगent thपढ़ो now that we have data */
	wake_up_process(ips->adjust);

	/*
	 * Ok, now we have an initial avg.  From here on out, we track the
	 * running avg using a decaying average calculation.  This allows
	 * us to reduce the sample frequency अगर the CPU and GPU are idle.
	 */
	old_cpu_घातer = thm_पढ़ोl(THM_CEC);
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(IPS_SAMPLE_PERIOD));
	last_sample_period = IPS_SAMPLE_PERIOD;

	समयr_setup(&ips->समयr, monitor_समयout, TIMER_DEFERRABLE);
	करो अणु
		u32 cpu_val, mch_val;
		u16 val;

		/* MCP itself */
		val = पढ़ो_ptv(ips);
		ips->mcp_avg_temp = update_average_temp(ips->mcp_avg_temp, val);

		/* Processor 0 */
		val = पढ़ो_ctv(ips, 0);
		ips->ctv1_avg_temp =
			update_average_temp(ips->ctv1_avg_temp, val);
		/* Power */
		cpu_val = get_cpu_घातer(ips, &old_cpu_घातer,
					last_sample_period);
		ips->cpu_avg_घातer =
			update_average_घातer(ips->cpu_avg_घातer, cpu_val);

		अगर (ips->second_cpu) अणु
			/* Processor 1 */
			val = पढ़ो_ctv(ips, 1);
			ips->ctv2_avg_temp =
				update_average_temp(ips->ctv2_avg_temp, val);
		पूर्ण

		/* MCH */
		val = पढ़ो_mgtv(ips);
		ips->mch_avg_temp = update_average_temp(ips->mch_avg_temp, val);
		/* Power */
		अगर (ips->पढ़ो_mch_val) अणु
			mch_val = ips->पढ़ो_mch_val();
			ips->mch_avg_घातer =
				update_average_घातer(ips->mch_avg_घातer,
						     mch_val);
		पूर्ण

		/*
		 * Make sure ME is updating thermal regs.
		 * Note:
		 * If it's been more than a second since the last update,
		 * the ME is probably hung.
		 */
		cur_seqno = (thm_पढ़ोl(THM_ITV) & ITV_ME_SEQNO_MASK) >>
			ITV_ME_SEQNO_SHIFT;
		अगर (cur_seqno == last_seqno &&
		    समय_after(jअगरfies, seqno_बारtamp + HZ)) अणु
			dev_warn(ips->dev,
				 "ME failed to update for more than 1s, likely hung\n");
		पूर्ण अन्यथा अणु
			seqno_बारtamp = get_jअगरfies_64();
			last_seqno = cur_seqno;
		पूर्ण

		last_msecs = jअगरfies_to_msecs(jअगरfies);
		expire = jअगरfies + msecs_to_jअगरfies(IPS_SAMPLE_PERIOD);

		__set_current_state(TASK_INTERRUPTIBLE);
		mod_समयr(&ips->समयr, expire);
		schedule();

		/* Calculate actual sample period क्रम घातer averaging */
		last_sample_period = jअगरfies_to_msecs(jअगरfies) - last_msecs;
		अगर (!last_sample_period)
			last_sample_period = 1;
	पूर्ण जबतक (!kthपढ़ो_should_stop());

	del_समयr_sync(&ips->समयr);

	dev_dbg(ips->dev, "ips-monitor thread stopped\n");

	वापस 0;
पूर्ण

#अगर 0
#घोषणा THM_DUMPW(reg) \
	अणु \
	u16 val = thm_पढ़ोw(reg); \
	dev_dbg(ips->dev, #reg ": 0x%04x\n", val); \
	पूर्ण
#घोषणा THM_DUMPL(reg) \
	अणु \
	u32 val = thm_पढ़ोl(reg); \
	dev_dbg(ips->dev, #reg ": 0x%08x\n", val); \
	पूर्ण
#घोषणा THM_DUMPQ(reg) \
	अणु \
	u64 val = thm_पढ़ोq(reg); \
	dev_dbg(ips->dev, #reg ": 0x%016x\n", val); \
	पूर्ण

अटल व्योम dump_thermal_info(काष्ठा ips_driver *ips)
अणु
	u16 ptl;

	ptl = thm_पढ़ोw(THM_PTL);
	dev_dbg(ips->dev, "Processor temp limit: %d\n", ptl);

	THM_DUMPW(THM_CTA);
	THM_DUMPW(THM_TRC);
	THM_DUMPW(THM_CTV1);
	THM_DUMPL(THM_STS);
	THM_DUMPW(THM_PTV);
	THM_DUMPQ(THM_MGTV);
पूर्ण
#पूर्ण_अगर

/**
 * ips_irq_handler - handle temperature triggers and other IPS events
 * @irq: irq number
 * @arg: unused
 *
 * Handle temperature limit trigger events, generally by lowering the clamps.
 * If we're at a critical limit, we clamp back to the lowest possible value
 * to prevent emergency shutकरोwn.
 */
अटल irqवापस_t ips_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा ips_driver *ips = arg;
	u8 tses = thm_पढ़ोb(THM_TSES);
	u8 tes = thm_पढ़ोb(THM_TES);

	अगर (!tses && !tes)
		वापस IRQ_NONE;

	dev_info(ips->dev, "TSES: 0x%02x\n", tses);
	dev_info(ips->dev, "TES: 0x%02x\n", tes);

	/* STS update from EC? */
	अगर (tes & 1) अणु
		u32 sts, tc1;

		sts = thm_पढ़ोl(THM_STS);
		tc1 = thm_पढ़ोl(THM_TC1);

		अगर (sts & STS_NVV) अणु
			spin_lock(&ips->turbo_status_lock);
			ips->core_घातer_limit = (sts & STS_PCPL_MASK) >>
				STS_PCPL_SHIFT;
			ips->mch_घातer_limit = (sts & STS_GPL_MASK) >>
				STS_GPL_SHIFT;
			/* ignore EC CPU vs GPU pref */
			ips->cpu_turbo_enabled = !(sts & STS_PCTD_DIS);
			/* 
			 * Disable turbo क्रम now, until we can figure
			 * out why the घातer figures are wrong
			 */
			ips->cpu_turbo_enabled = false;
			अगर (ips->gpu_busy)
				ips->gpu_turbo_enabled = !(sts & STS_GTD_DIS);
			ips->mcp_temp_limit = (sts & STS_PTL_MASK) >>
				STS_PTL_SHIFT;
			ips->mcp_घातer_limit = (tc1 & STS_PPL_MASK) >>
				STS_PPL_SHIFT;
			verअगरy_limits(ips);
			spin_unlock(&ips->turbo_status_lock);

			thm_ग_लिखोb(THM_SEC, SEC_ACK);
		पूर्ण
		thm_ग_लिखोb(THM_TES, tes);
	पूर्ण

	/* Thermal trip */
	अगर (tses) अणु
		dev_warn(ips->dev, "thermal trip occurred, tses: 0x%04x\n",
			 tses);
		thm_ग_लिखोb(THM_TSES, tses);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#अगर_अघोषित CONFIG_DEBUG_FS
अटल व्योम ips_debugfs_init(काष्ठा ips_driver *ips) अणु वापस; पूर्ण
अटल व्योम ips_debugfs_cleanup(काष्ठा ips_driver *ips) अणु वापस; पूर्ण
#अन्यथा

/* Expose current state and limits in debugfs अगर possible */

अटल पूर्णांक cpu_temp_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा ips_driver *ips = m->निजी;

	seq_म_लिखो(m, "%d.%02d\n", ips->ctv1_avg_temp / 100,
		   ips->ctv1_avg_temp % 100);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(cpu_temp);

अटल पूर्णांक cpu_घातer_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा ips_driver *ips = m->निजी;

	seq_म_लिखो(m, "%dmW\n", ips->cpu_avg_घातer);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(cpu_घातer);

अटल पूर्णांक cpu_clamp_show(काष्ठा seq_file *m, व्योम *data)
अणु
	u64 turbo_override;
	पूर्णांक tdp, tdc;

	rdmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);

	tdp = (पूर्णांक)(turbo_override & TURBO_TDP_MASK);
	tdc = (पूर्णांक)((turbo_override & TURBO_TDC_MASK) >> TURBO_TDC_SHIFT);

	/* Convert to .1W/A units */
	tdp = tdp * 10 / 8;
	tdc = tdc * 10 / 8;

	/* Watts Amperes */
	seq_म_लिखो(m, "%d.%dW %d.%dA\n", tdp / 10, tdp % 10,
		   tdc / 10, tdc % 10);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(cpu_clamp);

अटल पूर्णांक mch_temp_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा ips_driver *ips = m->निजी;

	seq_म_लिखो(m, "%d.%02d\n", ips->mch_avg_temp / 100,
		   ips->mch_avg_temp % 100);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(mch_temp);

अटल पूर्णांक mch_घातer_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा ips_driver *ips = m->निजी;

	seq_म_लिखो(m, "%dmW\n", ips->mch_avg_घातer);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(mch_घातer);

अटल व्योम ips_debugfs_cleanup(काष्ठा ips_driver *ips)
अणु
	debugfs_हटाओ_recursive(ips->debug_root);
पूर्ण

अटल व्योम ips_debugfs_init(काष्ठा ips_driver *ips)
अणु
	ips->debug_root = debugfs_create_dir("ips", शून्य);

	debugfs_create_file("cpu_temp", 0444, ips->debug_root, ips, &cpu_temp_fops);
	debugfs_create_file("cpu_power", 0444, ips->debug_root, ips, &cpu_घातer_fops);
	debugfs_create_file("cpu_clamp", 0444, ips->debug_root, ips, &cpu_clamp_fops);
	debugfs_create_file("mch_temp", 0444, ips->debug_root, ips, &mch_temp_fops);
	debugfs_create_file("mch_power", 0444, ips->debug_root, ips, &mch_घातer_fops);
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/**
 * ips_detect_cpu - detect whether CPU supports IPS
 *
 * Walk our list and see अगर we're on a supported CPU.  If we find one,
 * वापस the limits क्रम it.
 */
अटल काष्ठा ips_mcp_limits *ips_detect_cpu(काष्ठा ips_driver *ips)
अणु
	u64 turbo_घातer, misc_en;
	काष्ठा ips_mcp_limits *limits = शून्य;
	u16 tdp;

	अगर (!(boot_cpu_data.x86 == 6 && boot_cpu_data.x86_model == 37)) अणु
		dev_info(ips->dev, "Non-IPS CPU detected.\n");
		वापस शून्य;
	पूर्ण

	rdmsrl(IA32_MISC_ENABLE, misc_en);
	/*
	 * If the turbo enable bit isn't set, we shouldn't try to enable/disable
	 * turbo manually or we'll get an illegal MSR access, even though
	 * turbo will still be available.
	 */
	अगर (misc_en & IA32_MISC_TURBO_EN)
		ips->turbo_toggle_allowed = true;
	अन्यथा
		ips->turbo_toggle_allowed = false;

	अगर (म_माला(boot_cpu_data.x86_model_id, "CPU       M"))
		limits = &ips_sv_limits;
	अन्यथा अगर (म_माला(boot_cpu_data.x86_model_id, "CPU       L"))
		limits = &ips_lv_limits;
	अन्यथा अगर (म_माला(boot_cpu_data.x86_model_id, "CPU       U"))
		limits = &ips_ulv_limits;
	अन्यथा अणु
		dev_info(ips->dev, "No CPUID match found.\n");
		वापस शून्य;
	पूर्ण

	rdmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_घातer);
	tdp = turbo_घातer & TURBO_TDP_MASK;

	/* Sanity check TDP against CPU */
	अगर (limits->core_घातer_limit != (tdp / 8) * 1000) अणु
		dev_info(ips->dev,
			 "CPU TDP doesn't match expected value (found %d, expected %d)\n",
			 tdp / 8, limits->core_घातer_limit / 1000);
		limits->core_घातer_limit = (tdp / 8) * 1000;
	पूर्ण

	वापस limits;
पूर्ण

/**
 * ips_get_i915_syms - try to get GPU control methods from i915 driver
 * @ips: IPS driver
 *
 * The i915 driver exports several पूर्णांकerfaces to allow the IPS driver to
 * monitor and control graphics turbo mode.  If we can find them, we can
 * enable graphics turbo, otherwise we must disable it to aव्योम exceeding
 * thermal and घातer limits in the MCP.
 */
अटल bool ips_get_i915_syms(काष्ठा ips_driver *ips)
अणु
	ips->पढ़ो_mch_val = symbol_get(i915_पढ़ो_mch_val);
	अगर (!ips->पढ़ो_mch_val)
		जाओ out_err;
	ips->gpu_उठाओ = symbol_get(i915_gpu_उठाओ);
	अगर (!ips->gpu_उठाओ)
		जाओ out_put_mch;
	ips->gpu_lower = symbol_get(i915_gpu_lower);
	अगर (!ips->gpu_lower)
		जाओ out_put_उठाओ;
	ips->gpu_busy = symbol_get(i915_gpu_busy);
	अगर (!ips->gpu_busy)
		जाओ out_put_lower;
	ips->gpu_turbo_disable = symbol_get(i915_gpu_turbo_disable);
	अगर (!ips->gpu_turbo_disable)
		जाओ out_put_busy;

	वापस true;

out_put_busy:
	symbol_put(i915_gpu_busy);
out_put_lower:
	symbol_put(i915_gpu_lower);
out_put_उठाओ:
	symbol_put(i915_gpu_उठाओ);
out_put_mch:
	symbol_put(i915_पढ़ो_mch_val);
out_err:
	वापस false;
पूर्ण

अटल bool
ips_gpu_turbo_enabled(काष्ठा ips_driver *ips)
अणु
	अगर (!ips->gpu_busy && late_i915_load) अणु
		अगर (ips_get_i915_syms(ips)) अणु
			dev_info(ips->dev,
				 "i915 driver attached, reenabling gpu turbo\n");
			ips->gpu_turbo_enabled = !(thm_पढ़ोl(THM_HTS) & HTS_GTD_DIS);
		पूर्ण
	पूर्ण

	वापस ips->gpu_turbo_enabled;
पूर्ण

व्योम
ips_link_to_i915_driver(व्योम)
अणु
	/* We can't cleanly get at the various ips_driver काष्ठाs from
	 * this caller (the i915 driver), so just set a flag saying
	 * that it's समय to try getting the symbols again.
	 */
	late_i915_load = true;
पूर्ण
EXPORT_SYMBOL_GPL(ips_link_to_i915_driver);

अटल स्थिर काष्ठा pci_device_id ips_id_table[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_THERMAL_SENSOR), पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, ips_id_table);

अटल पूर्णांक ips_blacklist_callback(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_info("Blacklisted intel_ips for %s\n", id->ident);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id ips_blacklist[] = अणु
	अणु
		.callback = ips_blacklist_callback,
		.ident = "HP ProBook",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP ProBook"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण	/* terminating entry */
पूर्ण;

अटल पूर्णांक ips_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	u64 platक्रमm_info;
	काष्ठा ips_driver *ips;
	u32 hts;
	पूर्णांक ret = 0;
	u16 htshi, trc, trc_required_mask;
	u8 tse;

	अगर (dmi_check_प्रणाली(ips_blacklist))
		वापस -ENODEV;

	ips = devm_kzalloc(&dev->dev, माप(*ips), GFP_KERNEL);
	अगर (!ips)
		वापस -ENOMEM;

	spin_lock_init(&ips->turbo_status_lock);
	ips->dev = &dev->dev;

	ips->limits = ips_detect_cpu(ips);
	अगर (!ips->limits) अणु
		dev_info(&dev->dev, "IPS not supported on this CPU\n");
		वापस -ENXIO;
	पूर्ण

	ret = pcim_enable_device(dev);
	अगर (ret) अणु
		dev_err(&dev->dev, "can't enable PCI device, aborting\n");
		वापस ret;
	पूर्ण

	ret = pcim_iomap_regions(dev, 1 << 0, pci_name(dev));
	अगर (ret) अणु
		dev_err(&dev->dev, "failed to map thermal regs, aborting\n");
		वापस ret;
	पूर्ण
	ips->regmap = pcim_iomap_table(dev)[0];

	pci_set_drvdata(dev, ips);

	tse = thm_पढ़ोb(THM_TSE);
	अगर (tse != TSE_EN) अणु
		dev_err(&dev->dev, "thermal device not enabled (0x%02x), aborting\n", tse);
		वापस -ENXIO;
	पूर्ण

	trc = thm_पढ़ोw(THM_TRC);
	trc_required_mask = TRC_CORE1_EN | TRC_CORE_PWR | TRC_MCH_EN;
	अगर ((trc & trc_required_mask) != trc_required_mask) अणु
		dev_err(&dev->dev, "thermal reporting for required devices not enabled, aborting\n");
		वापस -ENXIO;
	पूर्ण

	अगर (trc & TRC_CORE2_EN)
		ips->second_cpu = true;

	update_turbo_limits(ips);
	dev_dbg(&dev->dev, "max cpu power clamp: %dW\n",
		ips->mcp_घातer_limit / 10);
	dev_dbg(&dev->dev, "max core power clamp: %dW\n",
		ips->core_घातer_limit / 10);
	/* BIOS may update limits at runसमय */
	अगर (thm_पढ़ोl(THM_PSC) & PSP_PBRT)
		ips->poll_turbo_status = true;

	अगर (!ips_get_i915_syms(ips)) अणु
		dev_info(&dev->dev, "failed to get i915 symbols, graphics turbo disabled until i915 loads\n");
		ips->gpu_turbo_enabled = false;
	पूर्ण अन्यथा अणु
		dev_dbg(&dev->dev, "graphics turbo enabled\n");
		ips->gpu_turbo_enabled = true;
	पूर्ण

	/*
	 * Check PLATFORM_INFO MSR to make sure this chip is
	 * turbo capable.
	 */
	rdmsrl(PLATFORM_INFO, platक्रमm_info);
	अगर (!(platक्रमm_info & PLATFORM_TDP)) अणु
		dev_err(&dev->dev, "platform indicates TDP override unavailable, aborting\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * IRQ handler क्रम ME पूर्णांकeraction
	 * Note: करोn't use MSI here as the PCH has bugs.
	 */
	ret = pci_alloc_irq_vectors(dev, 1, 1, PCI_IRQ_LEGACY);
	अगर (ret < 0)
		वापस ret;

	ips->irq = pci_irq_vector(dev, 0);

	ret = request_irq(ips->irq, ips_irq_handler, IRQF_SHARED, "ips", ips);
	अगर (ret) अणु
		dev_err(&dev->dev, "request irq failed, aborting\n");
		वापस ret;
	पूर्ण

	/* Enable aux, hot & critical पूर्णांकerrupts */
	thm_ग_लिखोb(THM_TSPIEN, TSPIEN_AUX2_LOHI | TSPIEN_CRIT_LOHI |
		   TSPIEN_HOT_LOHI | TSPIEN_AUX_LOHI);
	thm_ग_लिखोb(THM_TEN, TEN_UPDATE_EN);

	/* Collect adjusपंचांगent values */
	ips->cta_val = thm_पढ़ोw(THM_CTA);
	ips->pta_val = thm_पढ़ोw(THM_PTA);
	ips->mgta_val = thm_पढ़ोw(THM_MGTA);

	/* Save turbo limits & ratios */
	rdmsrl(TURBO_POWER_CURRENT_LIMIT, ips->orig_turbo_limit);

	ips_disable_cpu_turbo(ips);
	ips->cpu_turbo_enabled = false;

	/* Create thermal adjust thपढ़ो */
	ips->adjust = kthपढ़ो_create(ips_adjust, ips, "ips-adjust");
	अगर (IS_ERR(ips->adjust)) अणु
		dev_err(&dev->dev,
			"failed to create thermal adjust thread, aborting\n");
		ret = -ENOMEM;
		जाओ error_मुक्त_irq;

	पूर्ण

	/*
	 * Set up the work queue and monitor thपढ़ो. The monitor thपढ़ो
	 * will wake up ips_adjust thपढ़ो.
	 */
	ips->monitor = kthपढ़ो_run(ips_monitor, ips, "ips-monitor");
	अगर (IS_ERR(ips->monitor)) अणु
		dev_err(&dev->dev,
			"failed to create thermal monitor thread, aborting\n");
		ret = -ENOMEM;
		जाओ error_thपढ़ो_cleanup;
	पूर्ण

	hts = (ips->core_घातer_limit << HTS_PCPL_SHIFT) |
		(ips->mcp_temp_limit << HTS_PTL_SHIFT) | HTS_NVV;
	htshi = HTS2_PRST_RUNNING << HTS2_PRST_SHIFT;

	thm_ग_लिखोw(THM_HTSHI, htshi);
	thm_ग_लिखोl(THM_HTS, hts);

	ips_debugfs_init(ips);

	dev_info(&dev->dev, "IPS driver initialized, MCP temp limit %d\n",
		 ips->mcp_temp_limit);
	वापस ret;

error_thपढ़ो_cleanup:
	kthपढ़ो_stop(ips->adjust);
error_मुक्त_irq:
	मुक्त_irq(ips->irq, ips);
	pci_मुक्त_irq_vectors(dev);
	वापस ret;
पूर्ण

अटल व्योम ips_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा ips_driver *ips = pci_get_drvdata(dev);
	u64 turbo_override;

	ips_debugfs_cleanup(ips);

	/* Release i915 driver */
	अगर (ips->पढ़ो_mch_val)
		symbol_put(i915_पढ़ो_mch_val);
	अगर (ips->gpu_उठाओ)
		symbol_put(i915_gpu_उठाओ);
	अगर (ips->gpu_lower)
		symbol_put(i915_gpu_lower);
	अगर (ips->gpu_busy)
		symbol_put(i915_gpu_busy);
	अगर (ips->gpu_turbo_disable)
		symbol_put(i915_gpu_turbo_disable);

	rdmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);
	turbo_override &= ~(TURBO_TDC_OVR_EN | TURBO_TDP_OVR_EN);
	wrmsrl(TURBO_POWER_CURRENT_LIMIT, turbo_override);
	wrmsrl(TURBO_POWER_CURRENT_LIMIT, ips->orig_turbo_limit);

	मुक्त_irq(ips->irq, ips);
	pci_मुक्त_irq_vectors(dev);
	अगर (ips->adjust)
		kthपढ़ो_stop(ips->adjust);
	अगर (ips->monitor)
		kthपढ़ो_stop(ips->monitor);
	dev_dbg(&dev->dev, "IPS driver removed\n");
पूर्ण

अटल काष्ठा pci_driver ips_pci_driver = अणु
	.name = "intel ips",
	.id_table = ips_id_table,
	.probe = ips_probe,
	.हटाओ = ips_हटाओ,
पूर्ण;

module_pci_driver(ips_pci_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jesse Barnes <jbarnes@virtuousgeek.org>");
MODULE_DESCRIPTION("Intelligent Power Sharing Driver");
