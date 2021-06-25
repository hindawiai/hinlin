<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MIPS-specअगरic support क्रम Broadcom STB S2/S3/S5 घातer management
 *
 * Copyright (C) 2016-2017 Broadcom
 */

#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/bmips.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "pm.h"

#घोषणा S2_NUM_PARAMS		6
#घोषणा MAX_NUM_MEMC		3

/* S3 स्थिरants */
#घोषणा MAX_GP_REGS		16
#घोषणा MAX_CP0_REGS		32
#घोषणा NUM_MEMC_CLIENTS	128
#घोषणा AON_CTRL_RAM_SIZE	128
#घोषणा BRCMSTB_S3_MAGIC	0x5AFEB007

#घोषणा CLEAR_RESET_MASK	0x01

/* Index each CP0 रेजिस्टर that needs to be saved */
#घोषणा CONTEXT		0
#घोषणा USER_LOCAL	1
#घोषणा PGMK		2
#घोषणा HWRENA		3
#घोषणा COMPARE		4
#घोषणा STATUS		5
#घोषणा CONFIG		6
#घोषणा MODE		7
#घोषणा EDSP		8
#घोषणा BOOT_VEC	9
#घोषणा EBASE		10

काष्ठा brcmstb_memc अणु
	व्योम __iomem *ddr_phy_base;
	व्योम __iomem *arb_base;
पूर्ण;

काष्ठा brcmstb_pm_control अणु
	व्योम __iomem *aon_ctrl_base;
	व्योम __iomem *aon_sram_base;
	व्योम __iomem *समयrs_base;
	काष्ठा brcmstb_memc memcs[MAX_NUM_MEMC];
	पूर्णांक num_memc;
पूर्ण;

काष्ठा brcm_pm_s3_context अणु
	u32			cp0_regs[MAX_CP0_REGS];
	u32			memc0_rts[NUM_MEMC_CLIENTS];
	u32			sc_boot_vec;
पूर्ण;

काष्ठा brcmstb_mem_transfer;

काष्ठा brcmstb_mem_transfer अणु
	काष्ठा brcmstb_mem_transfer	*next;
	व्योम				*src;
	व्योम				*dst;
	dma_addr_t			pa_src;
	dma_addr_t			pa_dst;
	u32				len;
	u8				key;
	u8				mode;
	u8				src_remapped;
	u8				dst_remapped;
	u8				src_dst_remapped;
पूर्ण;

#घोषणा AON_SAVE_SRAM(base, idx, val) \
	__raw_ग_लिखोl(val, base + (idx << 2))

/* Used क्रम saving रेजिस्टरs in यंत्र */
u32 gp_regs[MAX_GP_REGS];

#घोषणा	BSP_CLOCK_STOP		0x00
#घोषणा PM_INITIATE		0x01

अटल काष्ठा brcmstb_pm_control ctrl;

अटल व्योम brcm_pm_save_cp0_context(काष्ठा brcm_pm_s3_context *ctx)
अणु
	/* Generic MIPS */
	ctx->cp0_regs[CONTEXT] = पढ़ो_c0_context();
	ctx->cp0_regs[USER_LOCAL] = पढ़ो_c0_userlocal();
	ctx->cp0_regs[PGMK] = पढ़ो_c0_pagemask();
	ctx->cp0_regs[HWRENA] = पढ़ो_c0_cache();
	ctx->cp0_regs[COMPARE] = पढ़ो_c0_compare();
	ctx->cp0_regs[STATUS] = पढ़ो_c0_status();

	/* Broadcom specअगरic */
	ctx->cp0_regs[CONFIG] = पढ़ो_c0_brcm_config();
	ctx->cp0_regs[MODE] = पढ़ो_c0_brcm_mode();
	ctx->cp0_regs[EDSP] = पढ़ो_c0_brcm_edsp();
	ctx->cp0_regs[BOOT_VEC] = पढ़ो_c0_brcm_bootvec();
	ctx->cp0_regs[EBASE] = पढ़ो_c0_ebase();

	ctx->sc_boot_vec = bmips_पढ़ो_zscm_reg(0xa0);
पूर्ण

अटल व्योम brcm_pm_restore_cp0_context(काष्ठा brcm_pm_s3_context *ctx)
अणु
	/* Restore cp0 state */
	bmips_ग_लिखो_zscm_reg(0xa0, ctx->sc_boot_vec);

	/* Generic MIPS */
	ग_लिखो_c0_context(ctx->cp0_regs[CONTEXT]);
	ग_लिखो_c0_userlocal(ctx->cp0_regs[USER_LOCAL]);
	ग_लिखो_c0_pagemask(ctx->cp0_regs[PGMK]);
	ग_लिखो_c0_cache(ctx->cp0_regs[HWRENA]);
	ग_लिखो_c0_compare(ctx->cp0_regs[COMPARE]);
	ग_लिखो_c0_status(ctx->cp0_regs[STATUS]);

	/* Broadcom specअगरic */
	ग_लिखो_c0_brcm_config(ctx->cp0_regs[CONFIG]);
	ग_लिखो_c0_brcm_mode(ctx->cp0_regs[MODE]);
	ग_लिखो_c0_brcm_edsp(ctx->cp0_regs[EDSP]);
	ग_लिखो_c0_brcm_bootvec(ctx->cp0_regs[BOOT_VEC]);
	ग_लिखो_c0_ebase(ctx->cp0_regs[EBASE]);
पूर्ण

अटल व्योम  brcmstb_pm_handshake(व्योम)
अणु
	व्योम __iomem *base = ctrl.aon_ctrl_base;
	u32 पंचांगp;

	/* BSP घातer handshake, v1 */
	पंचांगp = __raw_पढ़ोl(base + AON_CTRL_HOST_MISC_CMDS);
	पंचांगp &= ~1UL;
	__raw_ग_लिखोl(पंचांगp, base + AON_CTRL_HOST_MISC_CMDS);
	(व्योम)__raw_पढ़ोl(base + AON_CTRL_HOST_MISC_CMDS);

	__raw_ग_लिखोl(0, base + AON_CTRL_PM_INITIATE);
	(व्योम)__raw_पढ़ोl(base + AON_CTRL_PM_INITIATE);
	__raw_ग_लिखोl(BSP_CLOCK_STOP | PM_INITIATE,
		     base + AON_CTRL_PM_INITIATE);
	/*
	 * HACK: BSP may have पूर्णांकernal race on the CLOCK_STOP command.
	 * Aव्योम touching the BSP क्रम a few milliseconds.
	 */
	mdelay(3);
पूर्ण

अटल व्योम brcmstb_pm_s5(व्योम)
अणु
	व्योम __iomem *base = ctrl.aon_ctrl_base;

	brcmstb_pm_handshake();

	/* Clear magic s3 warm-boot value */
	AON_SAVE_SRAM(ctrl.aon_sram_base, 0, 0);

	/* Set the countकरोwn */
	__raw_ग_लिखोl(0x10, base + AON_CTRL_PM_CPU_WAIT_COUNT);
	(व्योम)__raw_पढ़ोl(base + AON_CTRL_PM_CPU_WAIT_COUNT);

	/* Prepare to S5 cold boot */
	__raw_ग_लिखोl(PM_COLD_CONFIG, base + AON_CTRL_PM_CTRL);
	(व्योम)__raw_पढ़ोl(base + AON_CTRL_PM_CTRL);

	__raw_ग_लिखोl((PM_COLD_CONFIG | PM_PWR_DOWN), base +
		      AON_CTRL_PM_CTRL);
	(व्योम)__raw_पढ़ोl(base + AON_CTRL_PM_CTRL);

	__यंत्र__ __अस्थिर__(
	"	wait\n"
	: : : "memory");
पूर्ण

अटल पूर्णांक brcmstb_pm_s3(व्योम)
अणु
	काष्ठा brcm_pm_s3_context s3_context;
	व्योम __iomem *memc_arb_base;
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;
	पूर्णांक i;

	/* Prepare क्रम s3 */
	AON_SAVE_SRAM(ctrl.aon_sram_base, 0, BRCMSTB_S3_MAGIC);
	AON_SAVE_SRAM(ctrl.aon_sram_base, 1, (u32)&s3_reentry);
	AON_SAVE_SRAM(ctrl.aon_sram_base, 2, 0);

	/* Clear RESET_HISTORY */
	पंचांगp = __raw_पढ़ोl(ctrl.aon_ctrl_base + AON_CTRL_RESET_CTRL);
	पंचांगp &= ~CLEAR_RESET_MASK;
	__raw_ग_लिखोl(पंचांगp, ctrl.aon_ctrl_base + AON_CTRL_RESET_CTRL);

	local_irq_save(flags);

	/* Inhibit DDR_RSTb pulse क्रम both MMCs*/
	क्रम (i = 0; i < ctrl.num_memc; i++) अणु
		पंचांगp = __raw_पढ़ोl(ctrl.memcs[i].ddr_phy_base +
			DDR40_PHY_CONTROL_REGS_0_STANDBY_CTRL);

		पंचांगp &= ~0x0f;
		__raw_ग_लिखोl(पंचांगp, ctrl.memcs[i].ddr_phy_base +
			DDR40_PHY_CONTROL_REGS_0_STANDBY_CTRL);
		पंचांगp |= (0x05 | BIT(5));
		__raw_ग_लिखोl(पंचांगp, ctrl.memcs[i].ddr_phy_base +
			DDR40_PHY_CONTROL_REGS_0_STANDBY_CTRL);
	पूर्ण

	/* Save CP0 context */
	brcm_pm_save_cp0_context(&s3_context);

	/* Save RTS(skip debug रेजिस्टर) */
	memc_arb_base = ctrl.memcs[0].arb_base + 4;
	क्रम (i = 0; i < NUM_MEMC_CLIENTS; i++) अणु
		s3_context.memc0_rts[i] = __raw_पढ़ोl(memc_arb_base);
		memc_arb_base += 4;
	पूर्ण

	/* Save I/O context */
	local_flush_tlb_all();
	_dma_cache_wback_inv(0, ~0);

	brcm_pm_करो_s3(ctrl.aon_ctrl_base, current_cpu_data.dcache.linesz);

	/* CPU reconfiguration */
	local_flush_tlb_all();
	bmips_cpu_setup();
	cpumask_clear(&bmips_booted_mask);

	/* Restore RTS (skip debug रेजिस्टर) */
	memc_arb_base = ctrl.memcs[0].arb_base + 4;
	क्रम (i = 0; i < NUM_MEMC_CLIENTS; i++) अणु
		__raw_ग_लिखोl(s3_context.memc0_rts[i], memc_arb_base);
		memc_arb_base += 4;
	पूर्ण

	/* restore CP0 context */
	brcm_pm_restore_cp0_context(&s3_context);

	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_pm_s2(व्योम)
अणु
	/*
	 * We need to pass 6 arguments to an assembly function. Lets aव्योम the
	 * stack and pass arguments in a explicit 4 byte array. The assembly
	 * code assumes all arguments are 4 bytes and arguments are ordered
	 * like so:
	 *
	 * 0: AON_CTRl base रेजिस्टर
	 * 1: DDR_PHY base रेजिस्टर
	 * 2: TIMERS base resgister
	 * 3: I-Cache line size
	 * 4: Restart vector address
	 * 5: Restart vector size
	 */
	u32 s2_params[6];

	/* Prepare s2 parameters */
	s2_params[0] = (u32)ctrl.aon_ctrl_base;
	s2_params[1] = (u32)ctrl.memcs[0].ddr_phy_base;
	s2_params[2] = (u32)ctrl.समयrs_base;
	s2_params[3] = (u32)current_cpu_data.icache.linesz;
	s2_params[4] = (u32)BMIPS_WARM_RESTART_VEC;
	s2_params[5] = (u32)(bmips_smp_पूर्णांक_vec_end -
		bmips_smp_पूर्णांक_vec);

	/* Drop to standby */
	brcm_pm_करो_s2(s2_params);

	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_pm_standby(bool deep_standby)
अणु
	brcmstb_pm_handshake();

	/* Send IRQs to BMIPS_WARM_RESTART_VEC */
	clear_c0_cause(CAUSEF_IV);
	irq_disable_hazard();
	set_c0_status(ST0_BEV);
	irq_disable_hazard();

	अगर (deep_standby)
		brcmstb_pm_s3();
	अन्यथा
		brcmstb_pm_s2();

	/* Send IRQs to normal runसमय vectors */
	clear_c0_status(ST0_BEV);
	irq_disable_hazard();
	set_c0_cause(CAUSEF_IV);
	irq_disable_hazard();

	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_pm_enter(suspend_state_t state)
अणु
	पूर्णांक ret = -EINVAL;

	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		ret = brcmstb_pm_standby(false);
		अवरोध;
	हाल PM_SUSPEND_MEM:
		ret = brcmstb_pm_standby(true);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक brcmstb_pm_valid(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		वापस true;
	हाल PM_SUSPEND_MEM:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops brcmstb_pm_ops = अणु
	.enter		= brcmstb_pm_enter,
	.valid		= brcmstb_pm_valid,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aon_ctrl_dt_ids[] = अणु
	अणु .compatible = "brcm,brcmstb-aon-ctrl" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id ddr_phy_dt_ids[] = अणु
	अणु .compatible = "brcm,brcmstb-ddr-phy" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id arb_dt_ids[] = अणु
	अणु .compatible = "brcm,brcmstb-memc-arb" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id समयrs_ids[] = अणु
	अणु .compatible = "brcm,brcmstb-timers" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल अंतरभूत व्योम __iomem *brcmstb_ioremap_node(काष्ठा device_node *dn,
						 पूर्णांक index)
अणु
	वापस of_io_request_and_map(dn, index, dn->full_name);
पूर्ण

अटल व्योम __iomem *brcmstb_ioremap_match(स्थिर काष्ठा of_device_id *matches,
					   पूर्णांक index, स्थिर व्योम **ofdata)
अणु
	काष्ठा device_node *dn;
	स्थिर काष्ठा of_device_id *match;

	dn = of_find_matching_node_and_match(शून्य, matches, &match);
	अगर (!dn)
		वापस ERR_PTR(-EINVAL);

	अगर (ofdata)
		*ofdata = match->data;

	वापस brcmstb_ioremap_node(dn, index);
पूर्ण

अटल पूर्णांक brcmstb_pm_init(व्योम)
अणु
	काष्ठा device_node *dn;
	व्योम __iomem *base;
	पूर्णांक i;

	/* AON ctrl रेजिस्टरs */
	base = brcmstb_ioremap_match(aon_ctrl_dt_ids, 0, शून्य);
	अगर (IS_ERR(base)) अणु
		pr_err("error mapping AON_CTRL\n");
		जाओ aon_err;
	पूर्ण
	ctrl.aon_ctrl_base = base;

	/* AON SRAM रेजिस्टरs */
	base = brcmstb_ioremap_match(aon_ctrl_dt_ids, 1, शून्य);
	अगर (IS_ERR(base)) अणु
		pr_err("error mapping AON_SRAM\n");
		जाओ sram_err;
	पूर्ण
	ctrl.aon_sram_base = base;

	ctrl.num_memc = 0;
	/* Map MEMC DDR PHY रेजिस्टरs */
	क्रम_each_matching_node(dn, ddr_phy_dt_ids) अणु
		i = ctrl.num_memc;
		अगर (i >= MAX_NUM_MEMC) अणु
			pr_warn("Too many MEMCs (max %d)\n", MAX_NUM_MEMC);
			अवरोध;
		पूर्ण
		base = brcmstb_ioremap_node(dn, 0);
		अगर (IS_ERR(base))
			जाओ ddr_err;

		ctrl.memcs[i].ddr_phy_base = base;
		ctrl.num_memc++;
	पूर्ण

	/* MEMC ARB रेजिस्टरs */
	base = brcmstb_ioremap_match(arb_dt_ids, 0, शून्य);
	अगर (IS_ERR(base)) अणु
		pr_err("error mapping MEMC ARB\n");
		जाओ ddr_err;
	पूर्ण
	ctrl.memcs[0].arb_base = base;

	/* Timer रेजिस्टरs */
	base = brcmstb_ioremap_match(समयrs_ids, 0, शून्य);
	अगर (IS_ERR(base)) अणु
		pr_err("error mapping timers\n");
		जाओ पंचांगr_err;
	पूर्ण
	ctrl.समयrs_base = base;

	/* s3 cold boot aka s5 */
	pm_घातer_off = brcmstb_pm_s5;

	suspend_set_ops(&brcmstb_pm_ops);

	वापस 0;

पंचांगr_err:
	iounmap(ctrl.memcs[0].arb_base);
ddr_err:
	क्रम (i = 0; i < ctrl.num_memc; i++)
		iounmap(ctrl.memcs[i].ddr_phy_base);

	iounmap(ctrl.aon_sram_base);
sram_err:
	iounmap(ctrl.aon_ctrl_base);
aon_err:
	वापस PTR_ERR(base);
पूर्ण
arch_initcall(brcmstb_pm_init);
