<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARM-specअगरic support क्रम Broadcom STB S2/S3/S5 घातer management
 *
 * S2: घड़ी gate CPUs and as many peripherals as possible
 * S3: घातer off all of the chip except the Always ON (AON) island; keep DDR is
 *     self-refresh
 * S5: (a.k.a. S3 cold boot) much like S3, except DDR is घातered करोwn, so we
 *     treat this mode like a soft घातer-off, with wakeup allowed from AON
 *
 * Copyright तऊ 2014-2017 Broadcom
 */

#घोषणा pr_fmt(fmt) "brcmstb-pm: " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kconfig.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>
#समावेश <linux/suspend.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/soc/brcmstb/brcmstb.h>

#समावेश <यंत्र/fncpy.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/suspend.h>

#समावेश "pm.h"
#समावेश "aon_defs.h"

#घोषणा SHIMPHY_DDR_PAD_CNTRL		0x8c

/* Method #0 */
#घोषणा SHIMPHY_PAD_PLL_SEQUENCE	BIT(8)
#घोषणा SHIMPHY_PAD_GATE_PLL_S3		BIT(9)

/* Method #1 */
#घोषणा PWRDWN_SEQ_NO_SEQUENCING	0
#घोषणा PWRDWN_SEQ_HOLD_CHANNEL		1
#घोषणा	PWRDWN_SEQ_RESET_PLL		2
#घोषणा PWRDWN_SEQ_POWERDOWN_PLL	3

#घोषणा SHIMPHY_PAD_S3_PWRDWN_SEQ_MASK	0x00f00000
#घोषणा SHIMPHY_PAD_S3_PWRDWN_SEQ_SHIFT	20

#घोषणा	DDR_FORCE_CKE_RST_N		BIT(3)
#घोषणा	DDR_PHY_RST_N			BIT(2)
#घोषणा	DDR_PHY_CKE			BIT(1)

#घोषणा	DDR_PHY_NO_CHANNEL		0xffffffff

#घोषणा MAX_NUM_MEMC			3

काष्ठा brcmstb_memc अणु
	व्योम __iomem *ddr_phy_base;
	व्योम __iomem *ddr_shimphy_base;
	व्योम __iomem *ddr_ctrl;
पूर्ण;

काष्ठा brcmstb_pm_control अणु
	व्योम __iomem *aon_ctrl_base;
	व्योम __iomem *aon_sram;
	काष्ठा brcmstb_memc memcs[MAX_NUM_MEMC];

	व्योम __iomem *boot_sram;
	माप_प्रकार boot_sram_len;

	bool support_warm_boot;
	माप_प्रकार pll_status_offset;
	पूर्णांक num_memc;

	काष्ठा brcmstb_s3_params *s3_params;
	dma_addr_t s3_params_pa;
	पूर्णांक s3entry_method;
	u32 warm_boot_offset;
	u32 phy_a_standby_ctrl_offs;
	u32 phy_b_standby_ctrl_offs;
	bool needs_ddr_pad;
	काष्ठा platक्रमm_device *pdev;
पूर्ण;

क्रमागत bsp_initiate_command अणु
	BSP_CLOCK_STOP		= 0x00,
	BSP_GEN_RANDOM_KEY	= 0x4A,
	BSP_RESTORE_RANDOM_KEY	= 0x55,
	BSP_GEN_FIXED_KEY	= 0x63,
पूर्ण;

#घोषणा PM_INITIATE		0x01
#घोषणा PM_INITIATE_SUCCESS	0x00
#घोषणा PM_INITIATE_FAIL	0xfe

अटल काष्ठा brcmstb_pm_control ctrl;

noअंतरभूत पूर्णांक brcmstb_pm_s3_finish(व्योम);

अटल पूर्णांक (*brcmstb_pm_करो_s2_sram)(व्योम __iomem *aon_ctrl_base,
		व्योम __iomem *ddr_phy_pll_status);

अटल पूर्णांक brcmstb_init_sram(काष्ठा device_node *dn)
अणु
	व्योम __iomem *sram;
	काष्ठा resource res;
	पूर्णांक ret;

	ret = of_address_to_resource(dn, 0, &res);
	अगर (ret)
		वापस ret;

	/* Uncached, executable remapping of SRAM */
	sram = __arm_ioremap_exec(res.start, resource_size(&res), false);
	अगर (!sram)
		वापस -ENOMEM;

	ctrl.boot_sram = sram;
	ctrl.boot_sram_len = resource_size(&res);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sram_dt_ids[] = अणु
	अणु .compatible = "mmio-sram" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक करो_bsp_initiate_command(क्रमागत bsp_initiate_command cmd)
अणु
	व्योम __iomem *base = ctrl.aon_ctrl_base;
	पूर्णांक ret;
	पूर्णांक समयo = 1000 * 1000; /* 1 second */

	ग_लिखोl_relaxed(0, base + AON_CTRL_PM_INITIATE);
	(व्योम)पढ़ोl_relaxed(base + AON_CTRL_PM_INITIATE);

	/* Go! */
	ग_लिखोl_relaxed((cmd << 1) | PM_INITIATE, base + AON_CTRL_PM_INITIATE);

	/*
	 * If firmware करोesn't support the 'ack', then just assume it's करोne
	 * after 10ms. Note that this only works क्रम command 0, BSP_CLOCK_STOP
	 */
	अगर (of_machine_is_compatible("brcm,bcm74371a0")) अणु
		(व्योम)पढ़ोl_relaxed(base + AON_CTRL_PM_INITIATE);
		mdelay(10);
		वापस 0;
	पूर्ण

	क्रम (;;) अणु
		ret = पढ़ोl_relaxed(base + AON_CTRL_PM_INITIATE);
		अगर (!(ret & PM_INITIATE))
			अवरोध;
		अगर (समयo <= 0) अणु
			pr_err("error: timeout waiting for BSP (%x)\n", ret);
			अवरोध;
		पूर्ण
		समयo -= 50;
		udelay(50);
	पूर्ण

	वापस (ret & 0xff) != PM_INITIATE_SUCCESS;
पूर्ण

अटल पूर्णांक brcmstb_pm_handshake(व्योम)
अणु
	व्योम __iomem *base = ctrl.aon_ctrl_base;
	u32 पंचांगp;
	पूर्णांक ret;

	/* BSP घातer handshake, v1 */
	पंचांगp = पढ़ोl_relaxed(base + AON_CTRL_HOST_MISC_CMDS);
	पंचांगp &= ~1UL;
	ग_लिखोl_relaxed(पंचांगp, base + AON_CTRL_HOST_MISC_CMDS);
	(व्योम)पढ़ोl_relaxed(base + AON_CTRL_HOST_MISC_CMDS);

	ret = करो_bsp_initiate_command(BSP_CLOCK_STOP);
	अगर (ret)
		pr_err("BSP handshake failed\n");

	/*
	 * HACK: BSP may have पूर्णांकernal race on the CLOCK_STOP command.
	 * Aव्योम touching the BSP क्रम a few milliseconds.
	 */
	mdelay(3);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम shimphy_set(u32 value, u32 mask)
अणु
	पूर्णांक i;

	अगर (!ctrl.needs_ddr_pad)
		वापस;

	क्रम (i = 0; i < ctrl.num_memc; i++) अणु
		u32 पंचांगp;

		पंचांगp = पढ़ोl_relaxed(ctrl.memcs[i].ddr_shimphy_base +
			SHIMPHY_DDR_PAD_CNTRL);
		पंचांगp = value | (पंचांगp & mask);
		ग_लिखोl_relaxed(पंचांगp, ctrl.memcs[i].ddr_shimphy_base +
			SHIMPHY_DDR_PAD_CNTRL);
	पूर्ण
	wmb(); /* Complete sequence in order. */
पूर्ण

अटल अंतरभूत व्योम ddr_ctrl_set(bool warmboot)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ctrl.num_memc; i++) अणु
		u32 पंचांगp;

		पंचांगp = पढ़ोl_relaxed(ctrl.memcs[i].ddr_ctrl +
				ctrl.warm_boot_offset);
		अगर (warmboot)
			पंचांगp |= 1;
		अन्यथा
			पंचांगp &= ~1; /* Cold boot */
		ग_लिखोl_relaxed(पंचांगp, ctrl.memcs[i].ddr_ctrl +
				ctrl.warm_boot_offset);
	पूर्ण
	/* Complete sequence in order */
	wmb();
पूर्ण

अटल अंतरभूत व्योम s3entry_method0(व्योम)
अणु
	shimphy_set(SHIMPHY_PAD_GATE_PLL_S3 | SHIMPHY_PAD_PLL_SEQUENCE,
		    0xffffffff);
पूर्ण

अटल अंतरभूत व्योम s3entry_method1(व्योम)
अणु
	/*
	 * S3 Entry Sequence
	 * -----------------
	 * Step 1: SHIMPHY_ADDR_CNTL_0_DDR_PAD_CNTRL [ S3_PWRDWN_SEQ ] = 3
	 * Step 2: MEMC_DDR_0_WARM_BOOT [ WARM_BOOT ] = 1
	 */
	shimphy_set((PWRDWN_SEQ_POWERDOWN_PLL <<
		    SHIMPHY_PAD_S3_PWRDWN_SEQ_SHIFT),
		    ~SHIMPHY_PAD_S3_PWRDWN_SEQ_MASK);

	ddr_ctrl_set(true);
पूर्ण

अटल अंतरभूत व्योम s5entry_method1(व्योम)
अणु
	पूर्णांक i;

	/*
	 * S5 Entry Sequence
	 * -----------------
	 * Step 1: SHIMPHY_ADDR_CNTL_0_DDR_PAD_CNTRL [ S3_PWRDWN_SEQ ] = 3
	 * Step 2: MEMC_DDR_0_WARM_BOOT [ WARM_BOOT ] = 0
	 * Step 3: DDR_PHY_CONTROL_REGS_[AB]_0_STANDBY_CONTROL[ CKE ] = 0
	 *	   DDR_PHY_CONTROL_REGS_[AB]_0_STANDBY_CONTROL[ RST_N ] = 0
	 */
	shimphy_set((PWRDWN_SEQ_POWERDOWN_PLL <<
		    SHIMPHY_PAD_S3_PWRDWN_SEQ_SHIFT),
		    ~SHIMPHY_PAD_S3_PWRDWN_SEQ_MASK);

	ddr_ctrl_set(false);

	क्रम (i = 0; i < ctrl.num_memc; i++) अणु
		u32 पंचांगp;

		/* Step 3: Channel A (RST_N = CKE = 0) */
		पंचांगp = पढ़ोl_relaxed(ctrl.memcs[i].ddr_phy_base +
				  ctrl.phy_a_standby_ctrl_offs);
		पंचांगp &= ~(DDR_PHY_RST_N | DDR_PHY_RST_N);
		ग_लिखोl_relaxed(पंचांगp, ctrl.memcs[i].ddr_phy_base +
			     ctrl.phy_a_standby_ctrl_offs);

		/* Step 3: Channel B? */
		अगर (ctrl.phy_b_standby_ctrl_offs != DDR_PHY_NO_CHANNEL) अणु
			पंचांगp = पढ़ोl_relaxed(ctrl.memcs[i].ddr_phy_base +
					  ctrl.phy_b_standby_ctrl_offs);
			पंचांगp &= ~(DDR_PHY_RST_N | DDR_PHY_RST_N);
			ग_लिखोl_relaxed(पंचांगp, ctrl.memcs[i].ddr_phy_base +
				     ctrl.phy_b_standby_ctrl_offs);
		पूर्ण
	पूर्ण
	/* Must complete */
	wmb();
पूर्ण

/*
 * Run a Power Management State Machine (PMSM) shutकरोwn command and put the CPU
 * पूर्णांकo a low-घातer mode
 */
अटल व्योम brcmstb_करो_pmsm_घातer_करोwn(अचिन्हित दीर्घ base_cmd, bool oneग_लिखो)
अणु
	व्योम __iomem *base = ctrl.aon_ctrl_base;

	अगर ((ctrl.s3entry_method == 1) && (base_cmd == PM_COLD_CONFIG))
		s5entry_method1();

	/* pm_start_pwrdn transition 0->1 */
	ग_लिखोl_relaxed(base_cmd, base + AON_CTRL_PM_CTRL);

	अगर (!oneग_लिखो) अणु
		(व्योम)पढ़ोl_relaxed(base + AON_CTRL_PM_CTRL);

		ग_लिखोl_relaxed(base_cmd | PM_PWR_DOWN, base + AON_CTRL_PM_CTRL);
		(व्योम)पढ़ोl_relaxed(base + AON_CTRL_PM_CTRL);
	पूर्ण
	wfi();
पूर्ण

/* Support S5 cold boot out of "poweroff" */
अटल व्योम brcmstb_pm_घातeroff(व्योम)
अणु
	brcmstb_pm_handshake();

	/* Clear magic S3 warm-boot value */
	ग_लिखोl_relaxed(0, ctrl.aon_sram + AON_REG_MAGIC_FLAGS);
	(व्योम)पढ़ोl_relaxed(ctrl.aon_sram + AON_REG_MAGIC_FLAGS);

	/* Skip रुको-क्रम-पूर्णांकerrupt संकेत; just use a countकरोwn */
	ग_लिखोl_relaxed(0x10, ctrl.aon_ctrl_base + AON_CTRL_PM_CPU_WAIT_COUNT);
	(व्योम)पढ़ोl_relaxed(ctrl.aon_ctrl_base + AON_CTRL_PM_CPU_WAIT_COUNT);

	अगर (ctrl.s3entry_method == 1) अणु
		shimphy_set((PWRDWN_SEQ_POWERDOWN_PLL <<
			     SHIMPHY_PAD_S3_PWRDWN_SEQ_SHIFT),
			     ~SHIMPHY_PAD_S3_PWRDWN_SEQ_MASK);
		ddr_ctrl_set(false);
		brcmstb_करो_pmsm_घातer_करोwn(M1_PM_COLD_CONFIG, true);
		वापस; /* We should never actually get here */
	पूर्ण

	brcmstb_करो_pmsm_घातer_करोwn(PM_COLD_CONFIG, false);
पूर्ण

अटल व्योम *brcmstb_pm_copy_to_sram(व्योम *fn, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक size = ALIGN(len, FNCPY_ALIGN);

	अगर (ctrl.boot_sram_len < size) अणु
		pr_err("standby code will not fit in SRAM\n");
		वापस शून्य;
	पूर्ण

	वापस fncpy(ctrl.boot_sram, fn, size);
पूर्ण

/*
 * S2 suspend/resume picks up where we left off, so we must execute carefully
 * from SRAM, in order to allow DDR to come back up safely beक्रमe we जारी.
 */
अटल पूर्णांक brcmstb_pm_s2(व्योम)
अणु
	/* A previous S3 can set a value hazarकरोus to S2, so make sure. */
	अगर (ctrl.s3entry_method == 1) अणु
		shimphy_set((PWRDWN_SEQ_NO_SEQUENCING <<
			    SHIMPHY_PAD_S3_PWRDWN_SEQ_SHIFT),
			    ~SHIMPHY_PAD_S3_PWRDWN_SEQ_MASK);
		ddr_ctrl_set(false);
	पूर्ण

	brcmstb_pm_करो_s2_sram = brcmstb_pm_copy_to_sram(&brcmstb_pm_करो_s2,
			brcmstb_pm_करो_s2_sz);
	अगर (!brcmstb_pm_करो_s2_sram)
		वापस -EINVAL;

	वापस brcmstb_pm_करो_s2_sram(ctrl.aon_ctrl_base,
			ctrl.memcs[0].ddr_phy_base +
			ctrl.pll_status_offset);
पूर्ण

/*
 * This function is called on a new stack, so करोn't allow inlining (which will
 * generate stack references on the old stack). It cannot be made अटल because
 * it is referenced from brcmstb_pm_s3()
 */
noअंतरभूत पूर्णांक brcmstb_pm_s3_finish(व्योम)
अणु
	काष्ठा brcmstb_s3_params *params = ctrl.s3_params;
	dma_addr_t params_pa = ctrl.s3_params_pa;
	phys_addr_t reentry = virt_to_phys(&cpu_resume_arm);
	क्रमागत bsp_initiate_command cmd;
	u32 flags;

	/*
	 * Clear parameter काष्ठाure, but not DTU area, which has alपढ़ोy been
	 * filled in. We know DTU is a the end, so we can just subtract its
	 * size.
	 */
	स_रखो(params, 0, माप(*params) - माप(params->dtu));

	flags = पढ़ोl_relaxed(ctrl.aon_sram + AON_REG_MAGIC_FLAGS);

	flags &= S3_BOOTLOADER_RESERVED;
	flags |= S3_FLAG_NO_MEM_VERIFY;
	flags |= S3_FLAG_LOAD_RANDKEY;

	/* Load अक्रमom / fixed key */
	अगर (flags & S3_FLAG_LOAD_RANDKEY)
		cmd = BSP_GEN_RANDOM_KEY;
	अन्यथा
		cmd = BSP_GEN_FIXED_KEY;
	अगर (करो_bsp_initiate_command(cmd)) अणु
		pr_info("key loading failed\n");
		वापस -EIO;
	पूर्ण

	params->magic = BRCMSTB_S3_MAGIC;
	params->reentry = reentry;

	/* No more ग_लिखोs to DRAM */
	flush_cache_all();

	flags |= BRCMSTB_S3_MAGIC_SHORT;

	ग_लिखोl_relaxed(flags, ctrl.aon_sram + AON_REG_MAGIC_FLAGS);
	ग_लिखोl_relaxed(lower_32_bits(params_pa),
		       ctrl.aon_sram + AON_REG_CONTROL_LOW);
	ग_लिखोl_relaxed(upper_32_bits(params_pa),
		       ctrl.aon_sram + AON_REG_CONTROL_HIGH);

	चयन (ctrl.s3entry_method) अणु
	हाल 0:
		s3entry_method0();
		brcmstb_करो_pmsm_घातer_करोwn(PM_WARM_CONFIG, false);
		अवरोध;
	हाल 1:
		s3entry_method1();
		brcmstb_करो_pmsm_घातer_करोwn(M1_PM_WARM_CONFIG, true);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Must have been पूर्णांकerrupted from wfi()? */
	वापस -EINTR;
पूर्ण

अटल पूर्णांक brcmstb_pm_करो_s3(अचिन्हित दीर्घ sp)
अणु
	अचिन्हित दीर्घ save_sp;
	पूर्णांक ret;

	यंत्र अस्थिर (
		"mov	%[save], sp\n"
		"mov	sp, %[new]\n"
		"bl	brcmstb_pm_s3_finish\n"
		"mov	%[ret], r0\n"
		"mov	%[new], sp\n"
		"mov	sp, %[save]\n"
		: [save] "=&r" (save_sp), [ret] "=&r" (ret)
		: [new] "r" (sp)
	);

	वापस ret;
पूर्ण

अटल पूर्णांक brcmstb_pm_s3(व्योम)
अणु
	व्योम __iomem *sp = ctrl.boot_sram + ctrl.boot_sram_len;

	वापस cpu_suspend((अचिन्हित दीर्घ)sp, brcmstb_pm_करो_s3);
पूर्ण

अटल पूर्णांक brcmstb_pm_standby(bool deep_standby)
अणु
	पूर्णांक ret;

	अगर (brcmstb_pm_handshake())
		वापस -EIO;

	अगर (deep_standby)
		ret = brcmstb_pm_s3();
	अन्यथा
		ret = brcmstb_pm_s2();
	अगर (ret)
		pr_err("%s: standby failed\n", __func__);

	वापस ret;
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
		वापस ctrl.support_warm_boot;
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
	अणुपूर्ण
पूर्ण;

काष्ठा ddr_phy_ofdata अणु
	bool supports_warm_boot;
	माप_प्रकार pll_status_offset;
	पूर्णांक s3entry_method;
	u32 warm_boot_offset;
	u32 phy_a_standby_ctrl_offs;
	u32 phy_b_standby_ctrl_offs;
पूर्ण;

अटल काष्ठा ddr_phy_ofdata ddr_phy_71_1 = अणु
	.supports_warm_boot = true,
	.pll_status_offset = 0x0c,
	.s3entry_method = 1,
	.warm_boot_offset = 0x2c,
	.phy_a_standby_ctrl_offs = 0x198,
	.phy_b_standby_ctrl_offs = DDR_PHY_NO_CHANNEL
पूर्ण;

अटल काष्ठा ddr_phy_ofdata ddr_phy_72_0 = अणु
	.supports_warm_boot = true,
	.pll_status_offset = 0x10,
	.s3entry_method = 1,
	.warm_boot_offset = 0x40,
	.phy_a_standby_ctrl_offs = 0x2a4,
	.phy_b_standby_ctrl_offs = 0x8a4
पूर्ण;

अटल काष्ठा ddr_phy_ofdata ddr_phy_225_1 = अणु
	.supports_warm_boot = false,
	.pll_status_offset = 0x4,
	.s3entry_method = 0
पूर्ण;

अटल काष्ठा ddr_phy_ofdata ddr_phy_240_1 = अणु
	.supports_warm_boot = true,
	.pll_status_offset = 0x4,
	.s3entry_method = 0
पूर्ण;

अटल स्थिर काष्ठा of_device_id ddr_phy_dt_ids[] = अणु
	अणु
		.compatible = "brcm,brcmstb-ddr-phy-v71.1",
		.data = &ddr_phy_71_1,
	पूर्ण,
	अणु
		.compatible = "brcm,brcmstb-ddr-phy-v72.0",
		.data = &ddr_phy_72_0,
	पूर्ण,
	अणु
		.compatible = "brcm,brcmstb-ddr-phy-v225.1",
		.data = &ddr_phy_225_1,
	पूर्ण,
	अणु
		.compatible = "brcm,brcmstb-ddr-phy-v240.1",
		.data = &ddr_phy_240_1,
	पूर्ण,
	अणु
		/* Same as v240.1, क्रम the रेजिस्टरs we care about */
		.compatible = "brcm,brcmstb-ddr-phy-v240.2",
		.data = &ddr_phy_240_1,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा ddr_seq_ofdata अणु
	bool needs_ddr_pad;
	u32 warm_boot_offset;
पूर्ण;

अटल स्थिर काष्ठा ddr_seq_ofdata ddr_seq_b22 = अणु
	.needs_ddr_pad = false,
	.warm_boot_offset = 0x2c,
पूर्ण;

अटल स्थिर काष्ठा ddr_seq_ofdata ddr_seq = अणु
	.needs_ddr_pad = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ddr_shimphy_dt_ids[] = अणु
	अणु .compatible = "brcm,brcmstb-ddr-shimphy-v1.0" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id brcmstb_memc_of_match[] = अणु
	अणु
		.compatible = "brcm,brcmstb-memc-ddr-rev-b.2.1",
		.data = &ddr_seq,
	पूर्ण,
	अणु
		.compatible = "brcm,brcmstb-memc-ddr-rev-b.2.2",
		.data = &ddr_seq_b22,
	पूर्ण,
	अणु
		.compatible = "brcm,brcmstb-memc-ddr-rev-b.2.3",
		.data = &ddr_seq_b22,
	पूर्ण,
	अणु
		.compatible = "brcm,brcmstb-memc-ddr-rev-b.3.0",
		.data = &ddr_seq_b22,
	पूर्ण,
	अणु
		.compatible = "brcm,brcmstb-memc-ddr-rev-b.3.1",
		.data = &ddr_seq_b22,
	पूर्ण,
	अणु
		.compatible = "brcm,brcmstb-memc-ddr",
		.data = &ddr_seq,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

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

	वापस of_io_request_and_map(dn, index, dn->full_name);
पूर्ण

अटल पूर्णांक brcmstb_pm_panic_notअगरy(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ action, व्योम *data)
अणु
	ग_लिखोl_relaxed(BRCMSTB_PANIC_MAGIC, ctrl.aon_sram + AON_REG_PANIC);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block brcmstb_pm_panic_nb = अणु
	.notअगरier_call = brcmstb_pm_panic_notअगरy,
पूर्ण;

अटल पूर्णांक brcmstb_pm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा ddr_phy_ofdata *ddr_phy_data;
	स्थिर काष्ठा ddr_seq_ofdata *ddr_seq_data;
	स्थिर काष्ठा of_device_id *of_id = शून्य;
	काष्ठा device_node *dn;
	व्योम __iomem *base;
	पूर्णांक ret, i;

	/* AON ctrl रेजिस्टरs */
	base = brcmstb_ioremap_match(aon_ctrl_dt_ids, 0, शून्य);
	अगर (IS_ERR(base)) अणु
		pr_err("error mapping AON_CTRL\n");
		वापस PTR_ERR(base);
	पूर्ण
	ctrl.aon_ctrl_base = base;

	/* AON SRAM रेजिस्टरs */
	base = brcmstb_ioremap_match(aon_ctrl_dt_ids, 1, शून्य);
	अगर (IS_ERR(base)) अणु
		/* Assume standard offset */
		ctrl.aon_sram = ctrl.aon_ctrl_base +
				     AON_CTRL_SYSTEM_DATA_RAM_OFS;
	पूर्ण अन्यथा अणु
		ctrl.aon_sram = base;
	पूर्ण

	ग_लिखोl_relaxed(0, ctrl.aon_sram + AON_REG_PANIC);

	/* DDR PHY रेजिस्टरs */
	base = brcmstb_ioremap_match(ddr_phy_dt_ids, 0,
				     (स्थिर व्योम **)&ddr_phy_data);
	अगर (IS_ERR(base)) अणु
		pr_err("error mapping DDR PHY\n");
		वापस PTR_ERR(base);
	पूर्ण
	ctrl.support_warm_boot = ddr_phy_data->supports_warm_boot;
	ctrl.pll_status_offset = ddr_phy_data->pll_status_offset;
	/* Only need DDR PHY 0 क्रम now? */
	ctrl.memcs[0].ddr_phy_base = base;
	ctrl.s3entry_method = ddr_phy_data->s3entry_method;
	ctrl.phy_a_standby_ctrl_offs = ddr_phy_data->phy_a_standby_ctrl_offs;
	ctrl.phy_b_standby_ctrl_offs = ddr_phy_data->phy_b_standby_ctrl_offs;
	/*
	 * Slightly grosss to use the phy ver to get a memc,
	 * offset but that is the only versioned things so far
	 * we can test क्रम.
	 */
	ctrl.warm_boot_offset = ddr_phy_data->warm_boot_offset;

	/* DDR SHIM-PHY रेजिस्टरs */
	क्रम_each_matching_node(dn, ddr_shimphy_dt_ids) अणु
		i = ctrl.num_memc;
		अगर (i >= MAX_NUM_MEMC) अणु
			pr_warn("too many MEMCs (max %d)\n", MAX_NUM_MEMC);
			अवरोध;
		पूर्ण

		base = of_io_request_and_map(dn, 0, dn->full_name);
		अगर (IS_ERR(base)) अणु
			अगर (!ctrl.support_warm_boot)
				अवरोध;

			pr_err("error mapping DDR SHIMPHY %d\n", i);
			वापस PTR_ERR(base);
		पूर्ण
		ctrl.memcs[i].ddr_shimphy_base = base;
		ctrl.num_memc++;
	पूर्ण

	/* Sequencer DRAM Param and Control Registers */
	i = 0;
	क्रम_each_matching_node(dn, brcmstb_memc_of_match) अणु
		base = of_iomap(dn, 0);
		अगर (!base) अणु
			pr_err("error mapping DDR Sequencer %d\n", i);
			वापस -ENOMEM;
		पूर्ण

		of_id = of_match_node(brcmstb_memc_of_match, dn);
		अगर (!of_id) अणु
			iounmap(base);
			वापस -EINVAL;
		पूर्ण

		ddr_seq_data = of_id->data;
		ctrl.needs_ddr_pad = ddr_seq_data->needs_ddr_pad;
		/* Adjust warm boot offset based on the DDR sequencer */
		अगर (ddr_seq_data->warm_boot_offset)
			ctrl.warm_boot_offset = ddr_seq_data->warm_boot_offset;

		ctrl.memcs[i].ddr_ctrl = base;
		i++;
	पूर्ण

	pr_debug("PM: supports warm boot:%d, method:%d, wboffs:%x\n",
		ctrl.support_warm_boot, ctrl.s3entry_method,
		ctrl.warm_boot_offset);

	dn = of_find_matching_node(शून्य, sram_dt_ids);
	अगर (!dn) अणु
		pr_err("SRAM not found\n");
		वापस -EINVAL;
	पूर्ण

	ret = brcmstb_init_sram(dn);
	अगर (ret) अणु
		pr_err("error setting up SRAM for PM\n");
		वापस ret;
	पूर्ण

	ctrl.pdev = pdev;

	ctrl.s3_params = kदो_स्मृति(माप(*ctrl.s3_params), GFP_KERNEL);
	अगर (!ctrl.s3_params)
		वापस -ENOMEM;
	ctrl.s3_params_pa = dma_map_single(&pdev->dev, ctrl.s3_params,
					   माप(*ctrl.s3_params),
					   DMA_TO_DEVICE);
	अगर (dma_mapping_error(&pdev->dev, ctrl.s3_params_pa)) अणु
		pr_err("error mapping DMA memory\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
				       &brcmstb_pm_panic_nb);

	pm_घातer_off = brcmstb_pm_घातeroff;
	suspend_set_ops(&brcmstb_pm_ops);

	वापस 0;

out:
	kमुक्त(ctrl.s3_params);

	pr_warn("PM: initialization failed with code %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver brcmstb_pm_driver = अणु
	.driver = अणु
		.name	= "brcmstb-pm",
		.of_match_table = aon_ctrl_dt_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init brcmstb_pm_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&brcmstb_pm_driver,
				     brcmstb_pm_probe);
पूर्ण
module_init(brcmstb_pm_init);
