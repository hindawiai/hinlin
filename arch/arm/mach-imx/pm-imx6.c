<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011-2014 Freescale Semiconductor, Inc.
 * Copyright 2011 Linaro Ltd.
 */

#समावेश <linux/clk/imx.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fncpy.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/tlb.h>

#समावेश "common.h"
#समावेश "hardware.h"

#घोषणा CCR				0x0
#घोषणा BM_CCR_WB_COUNT			(0x7 << 16)
#घोषणा BM_CCR_RBC_BYPASS_COUNT		(0x3f << 21)
#घोषणा BM_CCR_RBC_EN			(0x1 << 27)

#घोषणा CLPCR				0x54
#घोषणा BP_CLPCR_LPM			0
#घोषणा BM_CLPCR_LPM			(0x3 << 0)
#घोषणा BM_CLPCR_BYPASS_PMIC_READY	(0x1 << 2)
#घोषणा BM_CLPCR_ARM_CLK_DIS_ON_LPM	(0x1 << 5)
#घोषणा BM_CLPCR_SBYOS			(0x1 << 6)
#घोषणा BM_CLPCR_DIS_REF_OSC		(0x1 << 7)
#घोषणा BM_CLPCR_VSTBY			(0x1 << 8)
#घोषणा BP_CLPCR_STBY_COUNT		9
#घोषणा BM_CLPCR_STBY_COUNT		(0x3 << 9)
#घोषणा BM_CLPCR_COSC_PWRDOWN		(0x1 << 11)
#घोषणा BM_CLPCR_WB_PER_AT_LPM		(0x1 << 16)
#घोषणा BM_CLPCR_WB_CORE_AT_LPM		(0x1 << 17)
#घोषणा BM_CLPCR_BYP_MMDC_CH0_LPM_HS	(0x1 << 19)
#घोषणा BM_CLPCR_BYP_MMDC_CH1_LPM_HS	(0x1 << 21)
#घोषणा BM_CLPCR_MASK_CORE0_WFI		(0x1 << 22)
#घोषणा BM_CLPCR_MASK_CORE1_WFI		(0x1 << 23)
#घोषणा BM_CLPCR_MASK_CORE2_WFI		(0x1 << 24)
#घोषणा BM_CLPCR_MASK_CORE3_WFI		(0x1 << 25)
#घोषणा BM_CLPCR_MASK_SCU_IDLE		(0x1 << 26)
#घोषणा BM_CLPCR_MASK_L2CC_IDLE		(0x1 << 27)

#घोषणा CGPR				0x64
#घोषणा BM_CGPR_INT_MEM_CLK_LPM		(0x1 << 17)

#घोषणा MX6Q_SUSPEND_OCRAM_SIZE		0x1000
#घोषणा MX6_MAX_MMDC_IO_NUM		33

अटल व्योम __iomem *ccm_base;
अटल व्योम __iomem *suspend_ocram_base;
अटल व्योम (*imx6_suspend_in_ocram_fn)(व्योम __iomem *ocram_vbase);

/*
 * suspend ocram space layout:
 * ======================== high address ======================
 *                              .
 *                              .
 *                              .
 *                              ^
 *                              ^
 *                              ^
 *                      imx6_suspend code
 *              PM_INFO काष्ठाure(imx6_cpu_pm_info)
 * ======================== low address =======================
 */

काष्ठा imx6_pm_base अणु
	phys_addr_t pbase;
	व्योम __iomem *vbase;
पूर्ण;

काष्ठा imx6_pm_socdata अणु
	u32 ddr_type;
	स्थिर अक्षर *mmdc_compat;
	स्थिर अक्षर *src_compat;
	स्थिर अक्षर *iomuxc_compat;
	स्थिर अक्षर *gpc_compat;
	स्थिर अक्षर *pl310_compat;
	स्थिर u32 mmdc_io_num;
	स्थिर u32 *mmdc_io_offset;
पूर्ण;

अटल स्थिर u32 imx6q_mmdc_io_offset[] __initस्थिर = अणु
	0x5ac, 0x5b4, 0x528, 0x520, /* DQM0 ~ DQM3 */
	0x514, 0x510, 0x5bc, 0x5c4, /* DQM4 ~ DQM7 */
	0x56c, 0x578, 0x588, 0x594, /* CAS, RAS, SDCLK_0, SDCLK_1 */
	0x5a8, 0x5b0, 0x524, 0x51c, /* SDQS0 ~ SDQS3 */
	0x518, 0x50c, 0x5b8, 0x5c0, /* SDQS4 ~ SDQS7 */
	0x784, 0x788, 0x794, 0x79c, /* GPR_B0DS ~ GPR_B3DS */
	0x7a0, 0x7a4, 0x7a8, 0x748, /* GPR_B4DS ~ GPR_B7DS */
	0x59c, 0x5a0, 0x750, 0x774, /* SODT0, SODT1, MODE_CTL, MODE */
	0x74c,			    /* GPR_ADDS */
पूर्ण;

अटल स्थिर u32 imx6dl_mmdc_io_offset[] __initस्थिर = अणु
	0x470, 0x474, 0x478, 0x47c, /* DQM0 ~ DQM3 */
	0x480, 0x484, 0x488, 0x48c, /* DQM4 ~ DQM7 */
	0x464, 0x490, 0x4ac, 0x4b0, /* CAS, RAS, SDCLK_0, SDCLK_1 */
	0x4bc, 0x4c0, 0x4c4, 0x4c8, /* DRAM_SDQS0 ~ DRAM_SDQS3 */
	0x4cc, 0x4d0, 0x4d4, 0x4d8, /* DRAM_SDQS4 ~ DRAM_SDQS7 */
	0x764, 0x770, 0x778, 0x77c, /* GPR_B0DS ~ GPR_B3DS */
	0x780, 0x784, 0x78c, 0x748, /* GPR_B4DS ~ GPR_B7DS */
	0x4b4, 0x4b8, 0x750, 0x760, /* SODT0, SODT1, MODE_CTL, MODE */
	0x74c,			    /* GPR_ADDS */
पूर्ण;

अटल स्थिर u32 imx6sl_mmdc_io_offset[] __initस्थिर = अणु
	0x30c, 0x310, 0x314, 0x318, /* DQM0 ~ DQM3 */
	0x5c4, 0x5cc, 0x5d4, 0x5d8, /* GPR_B0DS ~ GPR_B3DS */
	0x300, 0x31c, 0x338, 0x5ac, /* CAS, RAS, SDCLK_0, GPR_ADDS */
	0x33c, 0x340, 0x5b0, 0x5c0, /* SODT0, SODT1, MODE_CTL, MODE */
	0x330, 0x334, 0x320,        /* SDCKE0, SDCKE1, RESET */
पूर्ण;

अटल स्थिर u32 imx6sll_mmdc_io_offset[] __initस्थिर = अणु
	0x294, 0x298, 0x29c, 0x2a0, /* DQM0 ~ DQM3 */
	0x544, 0x54c, 0x554, 0x558, /* GPR_B0DS ~ GPR_B3DS */
	0x530, 0x540, 0x2ac, 0x52c, /* MODE_CTL, MODE, SDCLK_0, GPR_ADDDS */
	0x2a4, 0x2a8,		    /* SDCKE0, SDCKE1*/
पूर्ण;

अटल स्थिर u32 imx6sx_mmdc_io_offset[] __initस्थिर = अणु
	0x2ec, 0x2f0, 0x2f4, 0x2f8, /* DQM0 ~ DQM3 */
	0x60c, 0x610, 0x61c, 0x620, /* GPR_B0DS ~ GPR_B3DS */
	0x300, 0x2fc, 0x32c, 0x5f4, /* CAS, RAS, SDCLK_0, GPR_ADDS */
	0x310, 0x314, 0x5f8, 0x608, /* SODT0, SODT1, MODE_CTL, MODE */
	0x330, 0x334, 0x338, 0x33c, /* SDQS0 ~ SDQS3 */
पूर्ण;

अटल स्थिर u32 imx6ul_mmdc_io_offset[] __initस्थिर = अणु
	0x244, 0x248, 0x24c, 0x250, /* DQM0, DQM1, RAS, CAS */
	0x27c, 0x498, 0x4a4, 0x490, /* SDCLK0, GPR_B0DS-B1DS, GPR_ADDS */
	0x280, 0x284, 0x260, 0x264, /* SDQS0~1, SODT0, SODT1 */
	0x494, 0x4b0,	            /* MODE_CTL, MODE, */
पूर्ण;

अटल स्थिर काष्ठा imx6_pm_socdata imx6q_pm_data __initस्थिर = अणु
	.mmdc_compat = "fsl,imx6q-mmdc",
	.src_compat = "fsl,imx6q-src",
	.iomuxc_compat = "fsl,imx6q-iomuxc",
	.gpc_compat = "fsl,imx6q-gpc",
	.pl310_compat = "arm,pl310-cache",
	.mmdc_io_num = ARRAY_SIZE(imx6q_mmdc_io_offset),
	.mmdc_io_offset = imx6q_mmdc_io_offset,
पूर्ण;

अटल स्थिर काष्ठा imx6_pm_socdata imx6dl_pm_data __initस्थिर = अणु
	.mmdc_compat = "fsl,imx6q-mmdc",
	.src_compat = "fsl,imx6q-src",
	.iomuxc_compat = "fsl,imx6dl-iomuxc",
	.gpc_compat = "fsl,imx6q-gpc",
	.pl310_compat = "arm,pl310-cache",
	.mmdc_io_num = ARRAY_SIZE(imx6dl_mmdc_io_offset),
	.mmdc_io_offset = imx6dl_mmdc_io_offset,
पूर्ण;

अटल स्थिर काष्ठा imx6_pm_socdata imx6sl_pm_data __initस्थिर = अणु
	.mmdc_compat = "fsl,imx6sl-mmdc",
	.src_compat = "fsl,imx6sl-src",
	.iomuxc_compat = "fsl,imx6sl-iomuxc",
	.gpc_compat = "fsl,imx6sl-gpc",
	.pl310_compat = "arm,pl310-cache",
	.mmdc_io_num = ARRAY_SIZE(imx6sl_mmdc_io_offset),
	.mmdc_io_offset = imx6sl_mmdc_io_offset,
पूर्ण;

अटल स्थिर काष्ठा imx6_pm_socdata imx6sll_pm_data __initस्थिर = अणु
	.mmdc_compat = "fsl,imx6sll-mmdc",
	.src_compat = "fsl,imx6sll-src",
	.iomuxc_compat = "fsl,imx6sll-iomuxc",
	.gpc_compat = "fsl,imx6sll-gpc",
	.pl310_compat = "arm,pl310-cache",
	.mmdc_io_num = ARRAY_SIZE(imx6sll_mmdc_io_offset),
	.mmdc_io_offset = imx6sll_mmdc_io_offset,
पूर्ण;

अटल स्थिर काष्ठा imx6_pm_socdata imx6sx_pm_data __initस्थिर = अणु
	.mmdc_compat = "fsl,imx6sx-mmdc",
	.src_compat = "fsl,imx6sx-src",
	.iomuxc_compat = "fsl,imx6sx-iomuxc",
	.gpc_compat = "fsl,imx6sx-gpc",
	.pl310_compat = "arm,pl310-cache",
	.mmdc_io_num = ARRAY_SIZE(imx6sx_mmdc_io_offset),
	.mmdc_io_offset = imx6sx_mmdc_io_offset,
पूर्ण;

अटल स्थिर काष्ठा imx6_pm_socdata imx6ul_pm_data __initस्थिर = अणु
	.mmdc_compat = "fsl,imx6ul-mmdc",
	.src_compat = "fsl,imx6ul-src",
	.iomuxc_compat = "fsl,imx6ul-iomuxc",
	.gpc_compat = "fsl,imx6ul-gpc",
	.pl310_compat = शून्य,
	.mmdc_io_num = ARRAY_SIZE(imx6ul_mmdc_io_offset),
	.mmdc_io_offset = imx6ul_mmdc_io_offset,
पूर्ण;

/*
 * This काष्ठाure is क्रम passing necessary data क्रम low level ocram
 * suspend code(arch/arm/mach-imx/suspend-imx6.S), अगर this काष्ठा
 * definition is changed, the offset definition in
 * arch/arm/mach-imx/suspend-imx6.S must be also changed accordingly,
 * otherwise, the suspend to ocram function will be broken!
 */
काष्ठा imx6_cpu_pm_info अणु
	phys_addr_t pbase; /* The physical address of pm_info. */
	phys_addr_t resume_addr; /* The physical resume address क्रम यंत्र code */
	u32 ddr_type;
	u32 pm_info_size; /* Size of pm_info. */
	काष्ठा imx6_pm_base mmdc_base;
	काष्ठा imx6_pm_base src_base;
	काष्ठा imx6_pm_base iomuxc_base;
	काष्ठा imx6_pm_base ccm_base;
	काष्ठा imx6_pm_base gpc_base;
	काष्ठा imx6_pm_base l2_base;
	u32 mmdc_io_num; /* Number of MMDC IOs which need saved/restored. */
	u32 mmdc_io_val[MX6_MAX_MMDC_IO_NUM][2]; /* To save offset and value */
पूर्ण __aligned(8);

व्योम imx6_set_पूर्णांक_mem_clk_lpm(bool enable)
अणु
	u32 val = पढ़ोl_relaxed(ccm_base + CGPR);

	val &= ~BM_CGPR_INT_MEM_CLK_LPM;
	अगर (enable)
		val |= BM_CGPR_INT_MEM_CLK_LPM;
	ग_लिखोl_relaxed(val, ccm_base + CGPR);
पूर्ण

व्योम imx6_enable_rbc(bool enable)
अणु
	u32 val;

	/*
	 * need to mask all पूर्णांकerrupts in GPC beक्रमe
	 * operating RBC configurations
	 */
	imx_gpc_mask_all();

	/* configure RBC enable bit */
	val = पढ़ोl_relaxed(ccm_base + CCR);
	val &= ~BM_CCR_RBC_EN;
	val |= enable ? BM_CCR_RBC_EN : 0;
	ग_लिखोl_relaxed(val, ccm_base + CCR);

	/* configure RBC count */
	val = पढ़ोl_relaxed(ccm_base + CCR);
	val &= ~BM_CCR_RBC_BYPASS_COUNT;
	val |= enable ? BM_CCR_RBC_BYPASS_COUNT : 0;
	ग_लिखोl(val, ccm_base + CCR);

	/*
	 * need to delay at least 2 cycles of CKIL(32K)
	 * due to hardware design requirement, which is
	 * ~61us, here we use 65us क्रम safe
	 */
	udelay(65);

	/* restore GPC पूर्णांकerrupt mask settings */
	imx_gpc_restore_all();
पूर्ण

अटल व्योम imx6q_enable_wb(bool enable)
अणु
	u32 val;

	/* configure well bias enable bit */
	val = पढ़ोl_relaxed(ccm_base + CLPCR);
	val &= ~BM_CLPCR_WB_PER_AT_LPM;
	val |= enable ? BM_CLPCR_WB_PER_AT_LPM : 0;
	ग_लिखोl_relaxed(val, ccm_base + CLPCR);

	/* configure well bias count */
	val = पढ़ोl_relaxed(ccm_base + CCR);
	val &= ~BM_CCR_WB_COUNT;
	val |= enable ? BM_CCR_WB_COUNT : 0;
	ग_लिखोl_relaxed(val, ccm_base + CCR);
पूर्ण

पूर्णांक imx6_set_lpm(क्रमागत mxc_cpu_pwr_mode mode)
अणु
	u32 val = पढ़ोl_relaxed(ccm_base + CLPCR);

	val &= ~BM_CLPCR_LPM;
	चयन (mode) अणु
	हाल WAIT_CLOCKED:
		अवरोध;
	हाल WAIT_UNCLOCKED:
		val |= 0x1 << BP_CLPCR_LPM;
		val |= BM_CLPCR_ARM_CLK_DIS_ON_LPM;
		अवरोध;
	हाल STOP_POWER_ON:
		val |= 0x2 << BP_CLPCR_LPM;
		val &= ~BM_CLPCR_VSTBY;
		val &= ~BM_CLPCR_SBYOS;
		अगर (cpu_is_imx6sl())
			val |= BM_CLPCR_BYPASS_PMIC_READY;
		अगर (cpu_is_imx6sl() || cpu_is_imx6sx() || cpu_is_imx6ul() ||
		    cpu_is_imx6ull() || cpu_is_imx6sll() || cpu_is_imx6ulz())
			val |= BM_CLPCR_BYP_MMDC_CH0_LPM_HS;
		अन्यथा
			val |= BM_CLPCR_BYP_MMDC_CH1_LPM_HS;
		अवरोध;
	हाल WAIT_UNCLOCKED_POWER_OFF:
		val |= 0x1 << BP_CLPCR_LPM;
		val &= ~BM_CLPCR_VSTBY;
		val &= ~BM_CLPCR_SBYOS;
		अवरोध;
	हाल STOP_POWER_OFF:
		val |= 0x2 << BP_CLPCR_LPM;
		val |= 0x3 << BP_CLPCR_STBY_COUNT;
		val |= BM_CLPCR_VSTBY;
		val |= BM_CLPCR_SBYOS;
		अगर (cpu_is_imx6sl() || cpu_is_imx6sx())
			val |= BM_CLPCR_BYPASS_PMIC_READY;
		अगर (cpu_is_imx6sl() || cpu_is_imx6sx() || cpu_is_imx6ul() ||
		    cpu_is_imx6ull() || cpu_is_imx6sll() || cpu_is_imx6ulz())
			val |= BM_CLPCR_BYP_MMDC_CH0_LPM_HS;
		अन्यथा
			val |= BM_CLPCR_BYP_MMDC_CH1_LPM_HS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * ERR007265: CCM: When improper low-घातer sequence is used,
	 * the SoC enters low घातer mode beक्रमe the ARM core executes WFI.
	 *
	 * Software workaround:
	 * 1) Software should trigger IRQ #32 (IOMUX) to be always pending
	 *    by setting IOMUX_GPR1_GINT.
	 * 2) Software should then unmask IRQ #32 in GPC beक्रमe setting CCM
	 *    Low-Power mode.
	 * 3) Software should mask IRQ #32 right after CCM Low-Power mode
	 *    is set (set bits 0-1 of CCM_CLPCR).
	 *
	 * Note that IRQ #32 is GIC SPI #0.
	 */
	अगर (mode != WAIT_CLOCKED)
		imx_gpc_hwirq_unmask(0);
	ग_लिखोl_relaxed(val, ccm_base + CLPCR);
	अगर (mode != WAIT_CLOCKED)
		imx_gpc_hwirq_mask(0);

	वापस 0;
पूर्ण

अटल पूर्णांक imx6q_suspend_finish(अचिन्हित दीर्घ val)
अणु
	अगर (!imx6_suspend_in_ocram_fn) अणु
		cpu_करो_idle();
	पूर्ण अन्यथा अणु
		/*
		 * call low level suspend function in ocram,
		 * as we need to भग्न DDR IO.
		 */
		local_flush_tlb_all();
		/* check अगर need to flush पूर्णांकernal L2 cache */
		अगर (!((काष्ठा imx6_cpu_pm_info *)
			suspend_ocram_base)->l2_base.vbase)
			flush_cache_all();
		imx6_suspend_in_ocram_fn(suspend_ocram_base);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx6q_pm_enter(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		imx6_set_lpm(STOP_POWER_ON);
		imx6_set_पूर्णांक_mem_clk_lpm(true);
		imx_gpc_pre_suspend(false);
		अगर (cpu_is_imx6sl())
			imx6sl_set_रुको_clk(true);
		/* Zzz ... */
		cpu_करो_idle();
		अगर (cpu_is_imx6sl())
			imx6sl_set_रुको_clk(false);
		imx_gpc_post_resume();
		imx6_set_lpm(WAIT_CLOCKED);
		अवरोध;
	हाल PM_SUSPEND_MEM:
		imx6_set_lpm(STOP_POWER_OFF);
		imx6_set_पूर्णांक_mem_clk_lpm(false);
		imx6q_enable_wb(true);
		/*
		 * For suspend पूर्णांकo ocram, यंत्र code alपढ़ोy take care of
		 * RBC setting, so we करो NOT need to करो that here.
		 */
		अगर (!imx6_suspend_in_ocram_fn)
			imx6_enable_rbc(true);
		imx_gpc_pre_suspend(true);
		imx_anatop_pre_suspend();
		/* Zzz ... */
		cpu_suspend(0, imx6q_suspend_finish);
		अगर (cpu_is_imx6q() || cpu_is_imx6dl())
			imx_smp_prepare();
		imx_anatop_post_resume();
		imx_gpc_post_resume();
		imx6_enable_rbc(false);
		imx6q_enable_wb(false);
		imx6_set_पूर्णांक_mem_clk_lpm(true);
		imx6_set_lpm(WAIT_CLOCKED);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx6q_pm_valid(suspend_state_t state)
अणु
	वापस (state == PM_SUSPEND_STANDBY || state == PM_SUSPEND_MEM);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops imx6q_pm_ops = अणु
	.enter = imx6q_pm_enter,
	.valid = imx6q_pm_valid,
पूर्ण;

अटल पूर्णांक __init imx6_pm_get_base(काष्ठा imx6_pm_base *base,
				स्थिर अक्षर *compat)
अणु
	काष्ठा device_node *node;
	काष्ठा resource res;
	पूर्णांक ret = 0;

	node = of_find_compatible_node(शून्य, शून्य, compat);
	अगर (!node)
		वापस -ENODEV;

	ret = of_address_to_resource(node, 0, &res);
	अगर (ret)
		जाओ put_node;

	base->pbase = res.start;
	base->vbase = ioremap(res.start, resource_size(&res));
	अगर (!base->vbase)
		ret = -ENOMEM;

put_node:
	of_node_put(node);
	वापस ret;
पूर्ण

अटल पूर्णांक __init imx6q_suspend_init(स्थिर काष्ठा imx6_pm_socdata *socdata)
अणु
	phys_addr_t ocram_pbase;
	काष्ठा device_node *node;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा imx6_cpu_pm_info *pm_info;
	काष्ठा gen_pool *ocram_pool;
	अचिन्हित दीर्घ ocram_base;
	पूर्णांक i, ret = 0;
	स्थिर u32 *mmdc_offset_array;

	suspend_set_ops(&imx6q_pm_ops);

	अगर (!socdata) अणु
		pr_warn("%s: invalid argument!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	node = of_find_compatible_node(शून्य, शून्य, "mmio-sram");
	अगर (!node) अणु
		pr_warn("%s: failed to find ocram node!\n", __func__);
		वापस -ENODEV;
	पूर्ण

	pdev = of_find_device_by_node(node);
	अगर (!pdev) अणु
		pr_warn("%s: failed to find ocram device!\n", __func__);
		ret = -ENODEV;
		जाओ put_node;
	पूर्ण

	ocram_pool = gen_pool_get(&pdev->dev, शून्य);
	अगर (!ocram_pool) अणु
		pr_warn("%s: ocram pool unavailable!\n", __func__);
		ret = -ENODEV;
		जाओ put_device;
	पूर्ण

	ocram_base = gen_pool_alloc(ocram_pool, MX6Q_SUSPEND_OCRAM_SIZE);
	अगर (!ocram_base) अणु
		pr_warn("%s: unable to alloc ocram!\n", __func__);
		ret = -ENOMEM;
		जाओ put_device;
	पूर्ण

	ocram_pbase = gen_pool_virt_to_phys(ocram_pool, ocram_base);

	suspend_ocram_base = __arm_ioremap_exec(ocram_pbase,
		MX6Q_SUSPEND_OCRAM_SIZE, false);

	स_रखो(suspend_ocram_base, 0, माप(*pm_info));
	pm_info = suspend_ocram_base;
	pm_info->pbase = ocram_pbase;
	pm_info->resume_addr = __pa_symbol(v7_cpu_resume);
	pm_info->pm_info_size = माप(*pm_info);

	/*
	 * ccm physical address is not used by यंत्र code currently,
	 * so get ccm भव address directly.
	 */
	pm_info->ccm_base.vbase = ccm_base;

	ret = imx6_pm_get_base(&pm_info->mmdc_base, socdata->mmdc_compat);
	अगर (ret) अणु
		pr_warn("%s: failed to get mmdc base %d!\n", __func__, ret);
		जाओ put_device;
	पूर्ण

	ret = imx6_pm_get_base(&pm_info->src_base, socdata->src_compat);
	अगर (ret) अणु
		pr_warn("%s: failed to get src base %d!\n", __func__, ret);
		जाओ src_map_failed;
	पूर्ण

	ret = imx6_pm_get_base(&pm_info->iomuxc_base, socdata->iomuxc_compat);
	अगर (ret) अणु
		pr_warn("%s: failed to get iomuxc base %d!\n", __func__, ret);
		जाओ iomuxc_map_failed;
	पूर्ण

	ret = imx6_pm_get_base(&pm_info->gpc_base, socdata->gpc_compat);
	अगर (ret) अणु
		pr_warn("%s: failed to get gpc base %d!\n", __func__, ret);
		जाओ gpc_map_failed;
	पूर्ण

	अगर (socdata->pl310_compat) अणु
		ret = imx6_pm_get_base(&pm_info->l2_base, socdata->pl310_compat);
		अगर (ret) अणु
			pr_warn("%s: failed to get pl310-cache base %d!\n",
				__func__, ret);
			जाओ pl310_cache_map_failed;
		पूर्ण
	पूर्ण

	pm_info->ddr_type = imx_mmdc_get_ddr_type();
	pm_info->mmdc_io_num = socdata->mmdc_io_num;
	mmdc_offset_array = socdata->mmdc_io_offset;

	क्रम (i = 0; i < pm_info->mmdc_io_num; i++) अणु
		pm_info->mmdc_io_val[i][0] =
			mmdc_offset_array[i];
		pm_info->mmdc_io_val[i][1] =
			पढ़ोl_relaxed(pm_info->iomuxc_base.vbase +
			mmdc_offset_array[i]);
	पूर्ण

	imx6_suspend_in_ocram_fn = fncpy(
		suspend_ocram_base + माप(*pm_info),
		&imx6_suspend,
		MX6Q_SUSPEND_OCRAM_SIZE - माप(*pm_info));

	जाओ put_device;

pl310_cache_map_failed:
	iounmap(pm_info->gpc_base.vbase);
gpc_map_failed:
	iounmap(pm_info->iomuxc_base.vbase);
iomuxc_map_failed:
	iounmap(pm_info->src_base.vbase);
src_map_failed:
	iounmap(pm_info->mmdc_base.vbase);
put_device:
	put_device(&pdev->dev);
put_node:
	of_node_put(node);

	वापस ret;
पूर्ण

अटल व्योम __init imx6_pm_common_init(स्थिर काष्ठा imx6_pm_socdata
					*socdata)
अणु
	काष्ठा regmap *gpr;
	पूर्णांक ret;

	WARN_ON(!ccm_base);

	अगर (IS_ENABLED(CONFIG_SUSPEND)) अणु
		ret = imx6q_suspend_init(socdata);
		अगर (ret)
			pr_warn("%s: No DDR LPM support with suspend %d!\n",
				__func__, ret);
	पूर्ण

	/*
	 * This is क्रम SW workaround step #1 of ERR007265, see comments
	 * in imx6_set_lpm क्रम details of this errata.
	 * Force IOMUXC irq pending, so that the पूर्णांकerrupt to GPC can be
	 * used to deनिश्चित dsm_request संकेत when the संकेत माला_लो
	 * निश्चितed unexpectedly.
	 */
	gpr = syscon_regmap_lookup_by_compatible("fsl,imx6q-iomuxc-gpr");
	अगर (!IS_ERR(gpr))
		regmap_update_bits(gpr, IOMUXC_GPR1, IMX6Q_GPR1_GINT,
				   IMX6Q_GPR1_GINT);
पूर्ण

अटल व्योम imx6_pm_stby_घातeroff(व्योम)
अणु
	imx6_set_lpm(STOP_POWER_OFF);
	imx6q_suspend_finish(0);

	mdelay(1000);

	pr_emerg("Unable to poweroff system\n");
पूर्ण

अटल पूर्णांक imx6_pm_stby_घातeroff_probe(व्योम)
अणु
	अगर (pm_घातer_off) अणु
		pr_warn("%s: pm_power_off already claimed  %p %ps!\n",
			__func__, pm_घातer_off, pm_घातer_off);
		वापस -EBUSY;
	पूर्ण

	pm_घातer_off = imx6_pm_stby_घातeroff;
	वापस 0;
पूर्ण

व्योम __init imx6_pm_ccm_init(स्थिर अक्षर *ccm_compat)
अणु
	काष्ठा device_node *np;
	u32 val;

	np = of_find_compatible_node(शून्य, शून्य, ccm_compat);
	ccm_base = of_iomap(np, 0);
	BUG_ON(!ccm_base);

	/*
	 * Initialize CCM_CLPCR_LPM पूर्णांकo RUN mode to aव्योम ARM core
	 * घड़ी being shut करोwn unexpectedly by WAIT mode.
	 */
	val = पढ़ोl_relaxed(ccm_base + CLPCR);
	val &= ~BM_CLPCR_LPM;
	ग_लिखोl_relaxed(val, ccm_base + CLPCR);

	अगर (of_property_पढ़ो_bool(np, "fsl,pmic-stby-poweroff"))
		imx6_pm_stby_घातeroff_probe();

	of_node_put(np);
पूर्ण

व्योम __init imx6q_pm_init(व्योम)
अणु
	imx6_pm_common_init(&imx6q_pm_data);
पूर्ण

व्योम __init imx6dl_pm_init(व्योम)
अणु
	imx6_pm_common_init(&imx6dl_pm_data);
पूर्ण

व्योम __init imx6sl_pm_init(व्योम)
अणु
	काष्ठा regmap *gpr;

	अगर (cpu_is_imx6sl()) अणु
		imx6_pm_common_init(&imx6sl_pm_data);
	पूर्ण अन्यथा अणु
		imx6_pm_common_init(&imx6sll_pm_data);
		gpr = syscon_regmap_lookup_by_compatible("fsl,imx6q-iomuxc-gpr");
		अगर (!IS_ERR(gpr))
			regmap_update_bits(gpr, IOMUXC_GPR5,
				IMX6SLL_GPR5_AFCG_X_BYPASS_MASK, 0);
	पूर्ण
पूर्ण

व्योम __init imx6sx_pm_init(व्योम)
अणु
	imx6_pm_common_init(&imx6sx_pm_data);
पूर्ण

व्योम __init imx6ul_pm_init(व्योम)
अणु
	imx6_pm_common_init(&imx6ul_pm_data);
पूर्ण
