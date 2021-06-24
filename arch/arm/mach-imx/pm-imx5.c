<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2011 Freescale Semiconductor, Inc. All Rights Reserved.
 */
#समावेश <linux/suspend.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/export.h>

#समावेश <linux/genभाग.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fncpy.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "common.h"
#समावेश "cpuidle.h"
#समावेश "hardware.h"

#घोषणा MXC_CCM_CLPCR			0x54
#घोषणा MXC_CCM_CLPCR_LPM_OFFSET	0
#घोषणा MXC_CCM_CLPCR_LPM_MASK		0x3
#घोषणा MXC_CCM_CLPCR_STBY_COUNT_OFFSET	9
#घोषणा MXC_CCM_CLPCR_VSTBY		(0x1 << 8)
#घोषणा MXC_CCM_CLPCR_SBYOS		(0x1 << 6)

#घोषणा MXC_CORTEXA8_PLAT_LPC		0xc
#घोषणा MXC_CORTEXA8_PLAT_LPC_DSM	(1 << 0)
#घोषणा MXC_CORTEXA8_PLAT_LPC_DBG_DSM	(1 << 1)

#घोषणा MXC_SRPG_NEON_SRPGCR		0x280
#घोषणा MXC_SRPG_ARM_SRPGCR		0x2a0
#घोषणा MXC_SRPG_EMPGC0_SRPGCR		0x2c0
#घोषणा MXC_SRPG_EMPGC1_SRPGCR		0x2d0

#घोषणा MXC_SRPGCR_PCR			1

/*
 * The WAIT_UNCLOCKED_POWER_OFF state only requires <= 500ns to निकास.
 * This is also the lowest घातer state possible without affecting
 * non-cpu parts of the प्रणाली.  For these reasons, imx5 should शेष
 * to always using this state क्रम cpu idling.  The PM_SUSPEND_STANDBY also
 * uses this state and needs to take no action when रेजिस्टरs reमुख्य configured
 * क्रम this state.
 */
#घोषणा IMX5_DEFAULT_CPU_IDLE_STATE WAIT_UNCLOCKED_POWER_OFF

काष्ठा imx5_suspend_io_state अणु
	u32	offset;
	u32	clear;
	u32	set;
	u32	saved_value;
पूर्ण;

काष्ठा imx5_pm_data अणु
	phys_addr_t ccm_addr;
	phys_addr_t cortex_addr;
	phys_addr_t gpc_addr;
	phys_addr_t m4अगर_addr;
	phys_addr_t iomuxc_addr;
	व्योम (*suspend_यंत्र)(व्योम __iomem *ocram_vbase);
	स्थिर u32 *suspend_यंत्र_sz;
	स्थिर काष्ठा imx5_suspend_io_state *suspend_io_config;
	पूर्णांक suspend_io_count;
पूर्ण;

अटल स्थिर काष्ठा imx5_suspend_io_state imx53_suspend_io_config[] = अणु
#घोषणा MX53_DSE_HIGHZ_MASK (0x7 << 19)
	अणु.offset = 0x584, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* DQM0 */
	अणु.offset = 0x594, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* DQM1 */
	अणु.offset = 0x560, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* DQM2 */
	अणु.offset = 0x554, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* DQM3 */
	अणु.offset = 0x574, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* CAS */
	अणु.offset = 0x588, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* RAS */
	अणु.offset = 0x578, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* SDCLK_0 */
	अणु.offset = 0x570, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* SDCLK_1 */

	अणु.offset = 0x580, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* SDODT0 */
	अणु.offset = 0x564, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* SDODT1 */
	अणु.offset = 0x57c, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* SDQS0 */
	अणु.offset = 0x590, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* SDQS1 */
	अणु.offset = 0x568, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* SDQS2 */
	अणु.offset = 0x558, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* SDSQ3 */
	अणु.offset = 0x6f0, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* GRP_ADDS */
	अणु.offset = 0x718, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* GRP_BODS */
	अणु.offset = 0x71c, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* GRP_B1DS */
	अणु.offset = 0x728, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* GRP_B2DS */
	अणु.offset = 0x72c, .clear = MX53_DSE_HIGHZ_MASKपूर्ण, /* GRP_B3DS */

	/* Controls the CKE संकेत which is required to leave self refresh */
	अणु.offset = 0x720, .clear = MX53_DSE_HIGHZ_MASK, .set = 1 << 19पूर्ण, /* CTLDS */
पूर्ण;

अटल स्थिर काष्ठा imx5_pm_data imx51_pm_data __initस्थिर = अणु
	.ccm_addr = 0x73fd4000,
	.cortex_addr = 0x83fa0000,
	.gpc_addr = 0x73fd8000,
पूर्ण;

अटल स्थिर काष्ठा imx5_pm_data imx53_pm_data __initस्थिर = अणु
	.ccm_addr = 0x53fd4000,
	.cortex_addr = 0x63fa0000,
	.gpc_addr = 0x53fd8000,
	.m4अगर_addr = 0x63fd8000,
	.iomuxc_addr = 0x53fa8000,
	.suspend_यंत्र = &imx53_suspend,
	.suspend_यंत्र_sz = &imx53_suspend_sz,
	.suspend_io_config = imx53_suspend_io_config,
	.suspend_io_count = ARRAY_SIZE(imx53_suspend_io_config),
पूर्ण;

#घोषणा MX5_MAX_SUSPEND_IOSTATE ARRAY_SIZE(imx53_suspend_io_config)

/*
 * This काष्ठाure is क्रम passing necessary data क्रम low level ocram
 * suspend code(arch/arm/mach-imx/suspend-imx53.S), अगर this काष्ठा
 * definition is changed, the offset definition in that file
 * must be also changed accordingly otherwise, the suspend to ocram
 * function will be broken!
 */
काष्ठा imx5_cpu_suspend_info अणु
	व्योम __iomem	*m4अगर_base;
	व्योम __iomem	*iomuxc_base;
	u32		io_count;
	काष्ठा imx5_suspend_io_state io_state[MX5_MAX_SUSPEND_IOSTATE];
पूर्ण __aligned(8);

अटल व्योम __iomem *ccm_base;
अटल व्योम __iomem *cortex_base;
अटल व्योम __iomem *gpc_base;
अटल व्योम __iomem *suspend_ocram_base;
अटल व्योम (*imx5_suspend_in_ocram_fn)(व्योम __iomem *ocram_vbase);

/*
 * set cpu low घातer mode beक्रमe WFI inकाष्ठाion. This function is called
 * mx5 because it can be used क्रम mx51, and mx53.
 */
अटल व्योम mx5_cpu_lp_set(क्रमागत mxc_cpu_pwr_mode mode)
अणु
	u32 plat_lpc, arm_srpgcr, ccm_clpcr;
	u32 empgc0, empgc1;
	पूर्णांक stop_mode = 0;

	/* always allow platक्रमm to issue a deep sleep mode request */
	plat_lpc = imx_पढ़ोl(cortex_base + MXC_CORTEXA8_PLAT_LPC) &
	    ~(MXC_CORTEXA8_PLAT_LPC_DSM);
	ccm_clpcr = imx_पढ़ोl(ccm_base + MXC_CCM_CLPCR) &
		    ~(MXC_CCM_CLPCR_LPM_MASK);
	arm_srpgcr = imx_पढ़ोl(gpc_base + MXC_SRPG_ARM_SRPGCR) &
		     ~(MXC_SRPGCR_PCR);
	empgc0 = imx_पढ़ोl(gpc_base + MXC_SRPG_EMPGC0_SRPGCR) &
		 ~(MXC_SRPGCR_PCR);
	empgc1 = imx_पढ़ोl(gpc_base + MXC_SRPG_EMPGC1_SRPGCR) &
		 ~(MXC_SRPGCR_PCR);

	चयन (mode) अणु
	हाल WAIT_CLOCKED:
		अवरोध;
	हाल WAIT_UNCLOCKED:
		ccm_clpcr |= 0x1 << MXC_CCM_CLPCR_LPM_OFFSET;
		अवरोध;
	हाल WAIT_UNCLOCKED_POWER_OFF:
	हाल STOP_POWER_OFF:
		plat_lpc |= MXC_CORTEXA8_PLAT_LPC_DSM
			    | MXC_CORTEXA8_PLAT_LPC_DBG_DSM;
		अगर (mode == WAIT_UNCLOCKED_POWER_OFF) अणु
			ccm_clpcr |= 0x1 << MXC_CCM_CLPCR_LPM_OFFSET;
			ccm_clpcr &= ~MXC_CCM_CLPCR_VSTBY;
			ccm_clpcr &= ~MXC_CCM_CLPCR_SBYOS;
			stop_mode = 0;
		पूर्ण अन्यथा अणु
			ccm_clpcr |= 0x2 << MXC_CCM_CLPCR_LPM_OFFSET;
			ccm_clpcr |= 0x3 << MXC_CCM_CLPCR_STBY_COUNT_OFFSET;
			ccm_clpcr |= MXC_CCM_CLPCR_VSTBY;
			ccm_clpcr |= MXC_CCM_CLPCR_SBYOS;
			stop_mode = 1;
		पूर्ण
		arm_srpgcr |= MXC_SRPGCR_PCR;
		अवरोध;
	हाल STOP_POWER_ON:
		ccm_clpcr |= 0x2 << MXC_CCM_CLPCR_LPM_OFFSET;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "UNKNOWN cpu power mode: %d\n", mode);
		वापस;
	पूर्ण

	imx_ग_लिखोl(plat_lpc, cortex_base + MXC_CORTEXA8_PLAT_LPC);
	imx_ग_लिखोl(ccm_clpcr, ccm_base + MXC_CCM_CLPCR);
	imx_ग_लिखोl(arm_srpgcr, gpc_base + MXC_SRPG_ARM_SRPGCR);
	imx_ग_लिखोl(arm_srpgcr, gpc_base + MXC_SRPG_NEON_SRPGCR);

	अगर (stop_mode) अणु
		empgc0 |= MXC_SRPGCR_PCR;
		empgc1 |= MXC_SRPGCR_PCR;

		imx_ग_लिखोl(empgc0, gpc_base + MXC_SRPG_EMPGC0_SRPGCR);
		imx_ग_लिखोl(empgc1, gpc_base + MXC_SRPG_EMPGC1_SRPGCR);
	पूर्ण
पूर्ण

अटल पूर्णांक mx5_suspend_enter(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_MEM:
		mx5_cpu_lp_set(STOP_POWER_OFF);
		अवरोध;
	हाल PM_SUSPEND_STANDBY:
		/* DEFAULT_IDLE_STATE alपढ़ोy configured */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (state == PM_SUSPEND_MEM) अणु
		local_flush_tlb_all();
		flush_cache_all();

		/*clear the EMPGC0/1 bits */
		imx_ग_लिखोl(0, gpc_base + MXC_SRPG_EMPGC0_SRPGCR);
		imx_ग_लिखोl(0, gpc_base + MXC_SRPG_EMPGC1_SRPGCR);

		अगर (imx5_suspend_in_ocram_fn)
			imx5_suspend_in_ocram_fn(suspend_ocram_base);
		अन्यथा
			cpu_करो_idle();

	पूर्ण अन्यथा अणु
		cpu_करो_idle();
	पूर्ण

	/* वापस रेजिस्टरs to शेष idle state */
	mx5_cpu_lp_set(IMX5_DEFAULT_CPU_IDLE_STATE);
	वापस 0;
पूर्ण

अटल पूर्णांक mx5_pm_valid(suspend_state_t state)
अणु
	वापस (state > PM_SUSPEND_ON && state <= PM_SUSPEND_MAX);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops mx5_suspend_ops = अणु
	.valid = mx5_pm_valid,
	.enter = mx5_suspend_enter,
पूर्ण;

अटल अंतरभूत पूर्णांक imx5_cpu_करो_idle(व्योम)
अणु
	पूर्णांक ret = tzic_enable_wake();

	अगर (likely(!ret))
		cpu_करो_idle();

	वापस ret;
पूर्ण

अटल व्योम imx5_pm_idle(व्योम)
अणु
	imx5_cpu_करो_idle();
पूर्ण

अटल पूर्णांक __init imx_suspend_alloc_ocram(
				माप_प्रकार size,
				व्योम __iomem **virt_out,
				phys_addr_t *phys_out)
अणु
	काष्ठा device_node *node;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा gen_pool *ocram_pool;
	अचिन्हित दीर्घ ocram_base;
	व्योम __iomem *virt;
	phys_addr_t phys;
	पूर्णांक ret = 0;

	/* Copied from imx6: TODO factorize */
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

	ocram_base = gen_pool_alloc(ocram_pool, size);
	अगर (!ocram_base) अणु
		pr_warn("%s: unable to alloc ocram!\n", __func__);
		ret = -ENOMEM;
		जाओ put_device;
	पूर्ण

	phys = gen_pool_virt_to_phys(ocram_pool, ocram_base);
	virt = __arm_ioremap_exec(phys, size, false);
	अगर (phys_out)
		*phys_out = phys;
	अगर (virt_out)
		*virt_out = virt;

put_device:
	put_device(&pdev->dev);
put_node:
	of_node_put(node);

	वापस ret;
पूर्ण

अटल पूर्णांक __init imx5_suspend_init(स्थिर काष्ठा imx5_pm_data *soc_data)
अणु
	काष्ठा imx5_cpu_suspend_info *suspend_info;
	पूर्णांक ret;
	/* Need this to aव्योम compile error due to स्थिर typeof in fncpy.h */
	व्योम (*suspend_यंत्र)(व्योम __iomem *) = soc_data->suspend_यंत्र;

	अगर (!suspend_यंत्र)
		वापस 0;

	अगर (!soc_data->suspend_यंत्र_sz || !*soc_data->suspend_यंत्र_sz)
		वापस -EINVAL;

	ret = imx_suspend_alloc_ocram(
		*soc_data->suspend_यंत्र_sz + माप(*suspend_info),
		&suspend_ocram_base, शून्य);
	अगर (ret)
		वापस ret;

	suspend_info = suspend_ocram_base;

	suspend_info->io_count = soc_data->suspend_io_count;
	स_नकल(suspend_info->io_state, soc_data->suspend_io_config,
	       माप(*suspend_info->io_state) * soc_data->suspend_io_count);

	suspend_info->m4अगर_base = ioremap(soc_data->m4अगर_addr, SZ_16K);
	अगर (!suspend_info->m4अगर_base) अणु
		ret = -ENOMEM;
		जाओ failed_map_m4अगर;
	पूर्ण

	suspend_info->iomuxc_base = ioremap(soc_data->iomuxc_addr, SZ_16K);
	अगर (!suspend_info->iomuxc_base) अणु
		ret = -ENOMEM;
		जाओ failed_map_iomuxc;
	पूर्ण

	imx5_suspend_in_ocram_fn = fncpy(
		suspend_ocram_base + माप(*suspend_info),
		suspend_यंत्र,
		*soc_data->suspend_यंत्र_sz);

	वापस 0;

failed_map_iomuxc:
	iounmap(suspend_info->m4अगर_base);

failed_map_m4अगर:
	वापस ret;
पूर्ण

अटल पूर्णांक __init imx5_pm_common_init(स्थिर काष्ठा imx5_pm_data *data)
अणु
	पूर्णांक ret;
	काष्ठा clk *gpc_dvfs_clk = clk_get(शून्य, "gpc_dvfs");

	अगर (IS_ERR(gpc_dvfs_clk))
		वापस PTR_ERR(gpc_dvfs_clk);

	ret = clk_prepare_enable(gpc_dvfs_clk);
	अगर (ret)
		वापस ret;

	arm_pm_idle = imx5_pm_idle;

	ccm_base = ioremap(data->ccm_addr, SZ_16K);
	cortex_base = ioremap(data->cortex_addr, SZ_16K);
	gpc_base = ioremap(data->gpc_addr, SZ_16K);
	WARN_ON(!ccm_base || !cortex_base || !gpc_base);

	/* Set the रेजिस्टरs to the शेष cpu idle state. */
	mx5_cpu_lp_set(IMX5_DEFAULT_CPU_IDLE_STATE);

	ret = imx5_cpuidle_init();
	अगर (ret)
		pr_warn("%s: cpuidle init failed %d\n", __func__, ret);

	ret = imx5_suspend_init(data);
	अगर (ret)
		pr_warn("%s: No DDR LPM support with suspend %d!\n",
			__func__, ret);

	suspend_set_ops(&mx5_suspend_ops);

	वापस 0;
पूर्ण

व्योम __init imx51_pm_init(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_SOC_IMX51))
		imx5_pm_common_init(&imx51_pm_data);
पूर्ण

व्योम __init imx53_pm_init(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_SOC_IMX53))
		imx5_pm_common_init(&imx53_pm_data);
पूर्ण
