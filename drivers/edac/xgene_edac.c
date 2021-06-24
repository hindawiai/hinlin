<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * APM X-Gene SoC EDAC (error detection and correction)
 *
 * Copyright (c) 2015, Applied Micro Circuits Corporation
 * Author: Feng Kan <fkan@apm.com>
 *         Loc Ho <lho@apm.com>
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/edac.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>

#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR			"xgene_edac"

/* Global error configuration status रेजिस्टरs (CSR) */
#घोषणा PCPHPERRINTSTS			0x0000
#घोषणा PCPHPERRINTMSK			0x0004
#घोषणा  MCU_CTL_ERR_MASK		BIT(12)
#घोषणा  IOB_PA_ERR_MASK		BIT(11)
#घोषणा  IOB_BA_ERR_MASK		BIT(10)
#घोषणा  IOB_XGIC_ERR_MASK		BIT(9)
#घोषणा  IOB_RB_ERR_MASK		BIT(8)
#घोषणा  L3C_UNCORR_ERR_MASK		BIT(5)
#घोषणा  MCU_UNCORR_ERR_MASK		BIT(4)
#घोषणा  PMD3_MERR_MASK			BIT(3)
#घोषणा  PMD2_MERR_MASK			BIT(2)
#घोषणा  PMD1_MERR_MASK			BIT(1)
#घोषणा  PMD0_MERR_MASK			BIT(0)
#घोषणा PCPLPERRINTSTS			0x0008
#घोषणा PCPLPERRINTMSK			0x000C
#घोषणा  CSW_SWITCH_TRACE_ERR_MASK	BIT(2)
#घोषणा  L3C_CORR_ERR_MASK		BIT(1)
#घोषणा  MCU_CORR_ERR_MASK		BIT(0)
#घोषणा MEMERRINTSTS			0x0010
#घोषणा MEMERRINTMSK			0x0014

काष्ठा xgene_edac अणु
	काष्ठा device		*dev;
	काष्ठा regmap		*csw_map;
	काष्ठा regmap		*mcba_map;
	काष्ठा regmap		*mcbb_map;
	काष्ठा regmap		*efuse_map;
	काष्ठा regmap		*rb_map;
	व्योम __iomem		*pcp_csr;
	spinlock_t		lock;
	काष्ठा dentry           *dfs;

	काष्ठा list_head	mcus;
	काष्ठा list_head	pmds;
	काष्ठा list_head	l3s;
	काष्ठा list_head	socs;

	काष्ठा mutex		mc_lock;
	पूर्णांक			mc_active_mask;
	पूर्णांक			mc_रेजिस्टरed_mask;
पूर्ण;

अटल व्योम xgene_edac_pcp_rd(काष्ठा xgene_edac *edac, u32 reg, u32 *val)
अणु
	*val = पढ़ोl(edac->pcp_csr + reg);
पूर्ण

अटल व्योम xgene_edac_pcp_clrbits(काष्ठा xgene_edac *edac, u32 reg,
				   u32 bits_mask)
अणु
	u32 val;

	spin_lock(&edac->lock);
	val = पढ़ोl(edac->pcp_csr + reg);
	val &= ~bits_mask;
	ग_लिखोl(val, edac->pcp_csr + reg);
	spin_unlock(&edac->lock);
पूर्ण

अटल व्योम xgene_edac_pcp_setbits(काष्ठा xgene_edac *edac, u32 reg,
				   u32 bits_mask)
अणु
	u32 val;

	spin_lock(&edac->lock);
	val = पढ़ोl(edac->pcp_csr + reg);
	val |= bits_mask;
	ग_लिखोl(val, edac->pcp_csr + reg);
	spin_unlock(&edac->lock);
पूर्ण

/* Memory controller error CSR */
#घोषणा MCU_MAX_RANK			8
#घोषणा MCU_RANK_STRIDE			0x40

#घोषणा MCUGECR				0x0110
#घोषणा  MCU_GECR_DEMANDUCINTREN_MASK	BIT(0)
#घोषणा  MCU_GECR_BACKUCINTREN_MASK	BIT(1)
#घोषणा  MCU_GECR_CINTREN_MASK		BIT(2)
#घोषणा  MUC_GECR_MCUADDRERREN_MASK	BIT(9)
#घोषणा MCUGESR				0x0114
#घोषणा  MCU_GESR_ADDRNOMATCH_ERR_MASK	BIT(7)
#घोषणा  MCU_GESR_ADDRMULTIMATCH_ERR_MASK	BIT(6)
#घोषणा  MCU_GESR_PHYP_ERR_MASK		BIT(3)
#घोषणा MCUESRR0			0x0314
#घोषणा  MCU_ESRR_MULTUCERR_MASK	BIT(3)
#घोषणा  MCU_ESRR_BACKUCERR_MASK	BIT(2)
#घोषणा  MCU_ESRR_DEMANDUCERR_MASK	BIT(1)
#घोषणा  MCU_ESRR_CERR_MASK		BIT(0)
#घोषणा MCUESRRA0			0x0318
#घोषणा MCUEBLRR0			0x031c
#घोषणा  MCU_EBLRR_ERRBANK_RD(src)	(((src) & 0x00000007) >> 0)
#घोषणा MCUERCRR0			0x0320
#घोषणा  MCU_ERCRR_ERRROW_RD(src)	(((src) & 0xFFFF0000) >> 16)
#घोषणा  MCU_ERCRR_ERRCOL_RD(src)	((src) & 0x00000FFF)
#घोषणा MCUSBECNT0			0x0324
#घोषणा MCU_SBECNT_COUNT(src)		((src) & 0xFFFF)

#घोषणा CSW_CSWCR			0x0000
#घोषणा  CSW_CSWCR_DUALMCB_MASK		BIT(0)

#घोषणा MCBADDRMR			0x0000
#घोषणा  MCBADDRMR_MCU_INTLV_MODE_MASK	BIT(3)
#घोषणा  MCBADDRMR_DUALMCU_MODE_MASK	BIT(2)
#घोषणा  MCBADDRMR_MCB_INTLV_MODE_MASK	BIT(1)
#घोषणा  MCBADDRMR_ADDRESS_MODE_MASK	BIT(0)

काष्ठा xgene_edac_mc_ctx अणु
	काष्ठा list_head	next;
	अक्षर			*name;
	काष्ठा mem_ctl_info	*mci;
	काष्ठा xgene_edac	*edac;
	व्योम __iomem		*mcu_csr;
	u32			mcu_id;
पूर्ण;

अटल sमाप_प्रकार xgene_edac_mc_err_inject_ग_लिखो(काष्ठा file *file,
					      स्थिर अक्षर __user *data,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mem_ctl_info *mci = file->निजी_data;
	काष्ठा xgene_edac_mc_ctx *ctx = mci->pvt_info;
	पूर्णांक i;

	क्रम (i = 0; i < MCU_MAX_RANK; i++) अणु
		ग_लिखोl(MCU_ESRR_MULTUCERR_MASK | MCU_ESRR_BACKUCERR_MASK |
		       MCU_ESRR_DEMANDUCERR_MASK | MCU_ESRR_CERR_MASK,
		       ctx->mcu_csr + MCUESRRA0 + i * MCU_RANK_STRIDE);
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations xgene_edac_mc_debug_inject_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = xgene_edac_mc_err_inject_ग_लिखो,
	.llseek = generic_file_llseek,
पूर्ण;

अटल व्योम xgene_edac_mc_create_debugfs_node(काष्ठा mem_ctl_info *mci)
अणु
	अगर (!IS_ENABLED(CONFIG_EDAC_DEBUG))
		वापस;

	अगर (!mci->debugfs)
		वापस;

	edac_debugfs_create_file("inject_ctrl", S_IWUSR, mci->debugfs, mci,
				 &xgene_edac_mc_debug_inject_fops);
पूर्ण

अटल व्योम xgene_edac_mc_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा xgene_edac_mc_ctx *ctx = mci->pvt_info;
	अचिन्हित पूर्णांक pcp_hp_stat;
	अचिन्हित पूर्णांक pcp_lp_stat;
	u32 reg;
	u32 rank;
	u32 bank;
	u32 count;
	u32 col_row;

	xgene_edac_pcp_rd(ctx->edac, PCPHPERRINTSTS, &pcp_hp_stat);
	xgene_edac_pcp_rd(ctx->edac, PCPLPERRINTSTS, &pcp_lp_stat);
	अगर (!((MCU_UNCORR_ERR_MASK & pcp_hp_stat) ||
	      (MCU_CTL_ERR_MASK & pcp_hp_stat) ||
	      (MCU_CORR_ERR_MASK & pcp_lp_stat)))
		वापस;

	क्रम (rank = 0; rank < MCU_MAX_RANK; rank++) अणु
		reg = पढ़ोl(ctx->mcu_csr + MCUESRR0 + rank * MCU_RANK_STRIDE);

		/* Detect uncorrectable memory error */
		अगर (reg & (MCU_ESRR_DEMANDUCERR_MASK |
			   MCU_ESRR_BACKUCERR_MASK)) अणु
			/* Detected uncorrectable memory error */
			edac_mc_chipset_prपूर्णांकk(mci, KERN_ERR, "X-Gene",
				"MCU uncorrectable error at rank %d\n", rank);

			edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci,
				1, 0, 0, 0, 0, 0, -1, mci->ctl_name, "");
		पूर्ण

		/* Detect correctable memory error */
		अगर (reg & MCU_ESRR_CERR_MASK) अणु
			bank = पढ़ोl(ctx->mcu_csr + MCUEBLRR0 +
				     rank * MCU_RANK_STRIDE);
			col_row = पढ़ोl(ctx->mcu_csr + MCUERCRR0 +
					rank * MCU_RANK_STRIDE);
			count = पढ़ोl(ctx->mcu_csr + MCUSBECNT0 +
				      rank * MCU_RANK_STRIDE);
			edac_mc_chipset_prपूर्णांकk(mci, KERN_WARNING, "X-Gene",
				"MCU correctable error at rank %d bank %d column %d row %d count %d\n",
				rank, MCU_EBLRR_ERRBANK_RD(bank),
				MCU_ERCRR_ERRCOL_RD(col_row),
				MCU_ERCRR_ERRROW_RD(col_row),
				MCU_SBECNT_COUNT(count));

			edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci,
				1, 0, 0, 0, 0, 0, -1, mci->ctl_name, "");
		पूर्ण

		/* Clear all error रेजिस्टरs */
		ग_लिखोl(0x0, ctx->mcu_csr + MCUEBLRR0 + rank * MCU_RANK_STRIDE);
		ग_लिखोl(0x0, ctx->mcu_csr + MCUERCRR0 + rank * MCU_RANK_STRIDE);
		ग_लिखोl(0x0, ctx->mcu_csr + MCUSBECNT0 +
		       rank * MCU_RANK_STRIDE);
		ग_लिखोl(reg, ctx->mcu_csr + MCUESRR0 + rank * MCU_RANK_STRIDE);
	पूर्ण

	/* Detect memory controller error */
	reg = पढ़ोl(ctx->mcu_csr + MCUGESR);
	अगर (reg) अणु
		अगर (reg & MCU_GESR_ADDRNOMATCH_ERR_MASK)
			edac_mc_chipset_prपूर्णांकk(mci, KERN_WARNING, "X-Gene",
				"MCU address miss-match error\n");
		अगर (reg & MCU_GESR_ADDRMULTIMATCH_ERR_MASK)
			edac_mc_chipset_prपूर्णांकk(mci, KERN_WARNING, "X-Gene",
				"MCU address multi-match error\n");

		ग_लिखोl(reg, ctx->mcu_csr + MCUGESR);
	पूर्ण
पूर्ण

अटल व्योम xgene_edac_mc_irq_ctl(काष्ठा mem_ctl_info *mci, bool enable)
अणु
	काष्ठा xgene_edac_mc_ctx *ctx = mci->pvt_info;
	अचिन्हित पूर्णांक val;

	अगर (edac_op_state != EDAC_OPSTATE_INT)
		वापस;

	mutex_lock(&ctx->edac->mc_lock);

	/*
	 * As there is only single bit क्रम enable error and पूर्णांकerrupt mask,
	 * we must only enable top level पूर्णांकerrupt after all MCUs are
	 * रेजिस्टरed. Otherwise, अगर there is an error and the corresponding
	 * MCU has not रेजिस्टरed, the पूर्णांकerrupt will never get cleared. To
	 * determine all MCU have रेजिस्टरed, we will keep track of active
	 * MCUs and रेजिस्टरed MCUs.
	 */
	अगर (enable) अणु
		/* Set रेजिस्टरed MCU bit */
		ctx->edac->mc_रेजिस्टरed_mask |= 1 << ctx->mcu_id;

		/* Enable पूर्णांकerrupt after all active MCU रेजिस्टरed */
		अगर (ctx->edac->mc_रेजिस्टरed_mask ==
		    ctx->edac->mc_active_mask) अणु
			/* Enable memory controller top level पूर्णांकerrupt */
			xgene_edac_pcp_clrbits(ctx->edac, PCPHPERRINTMSK,
					       MCU_UNCORR_ERR_MASK |
					       MCU_CTL_ERR_MASK);
			xgene_edac_pcp_clrbits(ctx->edac, PCPLPERRINTMSK,
					       MCU_CORR_ERR_MASK);
		पूर्ण

		/* Enable MCU पूर्णांकerrupt and error reporting */
		val = पढ़ोl(ctx->mcu_csr + MCUGECR);
		val |= MCU_GECR_DEMANDUCINTREN_MASK |
		       MCU_GECR_BACKUCINTREN_MASK |
		       MCU_GECR_CINTREN_MASK |
		       MUC_GECR_MCUADDRERREN_MASK;
		ग_लिखोl(val, ctx->mcu_csr + MCUGECR);
	पूर्ण अन्यथा अणु
		/* Disable MCU पूर्णांकerrupt */
		val = पढ़ोl(ctx->mcu_csr + MCUGECR);
		val &= ~(MCU_GECR_DEMANDUCINTREN_MASK |
			 MCU_GECR_BACKUCINTREN_MASK |
			 MCU_GECR_CINTREN_MASK |
			 MUC_GECR_MCUADDRERREN_MASK);
		ग_लिखोl(val, ctx->mcu_csr + MCUGECR);

		/* Disable memory controller top level पूर्णांकerrupt */
		xgene_edac_pcp_setbits(ctx->edac, PCPHPERRINTMSK,
				       MCU_UNCORR_ERR_MASK | MCU_CTL_ERR_MASK);
		xgene_edac_pcp_setbits(ctx->edac, PCPLPERRINTMSK,
				       MCU_CORR_ERR_MASK);

		/* Clear रेजिस्टरed MCU bit */
		ctx->edac->mc_रेजिस्टरed_mask &= ~(1 << ctx->mcu_id);
	पूर्ण

	mutex_unlock(&ctx->edac->mc_lock);
पूर्ण

अटल पूर्णांक xgene_edac_mc_is_active(काष्ठा xgene_edac_mc_ctx *ctx, पूर्णांक mc_idx)
अणु
	अचिन्हित पूर्णांक reg;
	u32 mcu_mask;

	अगर (regmap_पढ़ो(ctx->edac->csw_map, CSW_CSWCR, &reg))
		वापस 0;

	अगर (reg & CSW_CSWCR_DUALMCB_MASK) अणु
		/*
		 * Dual MCB active - Determine अगर all 4 active or just MCU0
		 * and MCU2 active
		 */
		अगर (regmap_पढ़ो(ctx->edac->mcbb_map, MCBADDRMR, &reg))
			वापस 0;
		mcu_mask = (reg & MCBADDRMR_DUALMCU_MODE_MASK) ? 0xF : 0x5;
	पूर्ण अन्यथा अणु
		/*
		 * Single MCB active - Determine अगर MCU0/MCU1 or just MCU0
		 * active
		 */
		अगर (regmap_पढ़ो(ctx->edac->mcba_map, MCBADDRMR, &reg))
			वापस 0;
		mcu_mask = (reg & MCBADDRMR_DUALMCU_MODE_MASK) ? 0x3 : 0x1;
	पूर्ण

	/* Save active MC mask अगर hasn't set alपढ़ोy */
	अगर (!ctx->edac->mc_active_mask)
		ctx->edac->mc_active_mask = mcu_mask;

	वापस (mcu_mask & (1 << mc_idx)) ? 1 : 0;
पूर्ण

अटल पूर्णांक xgene_edac_mc_add(काष्ठा xgene_edac *edac, काष्ठा device_node *np)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा xgene_edac_mc_ctx पंचांगp_ctx;
	काष्ठा xgene_edac_mc_ctx *ctx;
	काष्ठा resource res;
	पूर्णांक rc;

	स_रखो(&पंचांगp_ctx, 0, माप(पंचांगp_ctx));
	पंचांगp_ctx.edac = edac;

	अगर (!devres_खोलो_group(edac->dev, xgene_edac_mc_add, GFP_KERNEL))
		वापस -ENOMEM;

	rc = of_address_to_resource(np, 0, &res);
	अगर (rc < 0) अणु
		dev_err(edac->dev, "no MCU resource address\n");
		जाओ err_group;
	पूर्ण
	पंचांगp_ctx.mcu_csr = devm_ioremap_resource(edac->dev, &res);
	अगर (IS_ERR(पंचांगp_ctx.mcu_csr)) अणु
		dev_err(edac->dev, "unable to map MCU resource\n");
		rc = PTR_ERR(पंचांगp_ctx.mcu_csr);
		जाओ err_group;
	पूर्ण

	/* Ignore non-active MCU */
	अगर (of_property_पढ़ो_u32(np, "memory-controller", &पंचांगp_ctx.mcu_id)) अणु
		dev_err(edac->dev, "no memory-controller property\n");
		rc = -ENODEV;
		जाओ err_group;
	पूर्ण
	अगर (!xgene_edac_mc_is_active(&पंचांगp_ctx, पंचांगp_ctx.mcu_id)) अणु
		rc = -ENODEV;
		जाओ err_group;
	पूर्ण

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = 4;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = 2;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(पंचांगp_ctx.mcu_id, ARRAY_SIZE(layers), layers,
			    माप(*ctx));
	अगर (!mci) अणु
		rc = -ENOMEM;
		जाओ err_group;
	पूर्ण

	ctx = mci->pvt_info;
	*ctx = पंचांगp_ctx;		/* Copy over resource value */
	ctx->name = "xgene_edac_mc_err";
	ctx->mci = mci;
	mci->pdev = &mci->dev;
	mci->ctl_name = ctx->name;
	mci->dev_name = ctx->name;

	mci->mtype_cap = MEM_FLAG_RDDR | MEM_FLAG_RDDR2 | MEM_FLAG_RDDR3 |
			 MEM_FLAG_DDR | MEM_FLAG_DDR2 | MEM_FLAG_DDR3;
	mci->edac_ctl_cap = EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->mod_name = EDAC_MOD_STR;
	mci->ctl_page_to_phys = शून्य;
	mci->scrub_cap = SCRUB_FLAG_HW_SRC;
	mci->scrub_mode = SCRUB_HW_SRC;

	अगर (edac_op_state == EDAC_OPSTATE_POLL)
		mci->edac_check = xgene_edac_mc_check;

	अगर (edac_mc_add_mc(mci)) अणु
		dev_err(edac->dev, "edac_mc_add_mc failed\n");
		rc = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	xgene_edac_mc_create_debugfs_node(mci);

	list_add(&ctx->next, &edac->mcus);

	xgene_edac_mc_irq_ctl(mci, true);

	devres_हटाओ_group(edac->dev, xgene_edac_mc_add);

	dev_info(edac->dev, "X-Gene EDAC MC registered\n");
	वापस 0;

err_मुक्त:
	edac_mc_मुक्त(mci);
err_group:
	devres_release_group(edac->dev, xgene_edac_mc_add);
	वापस rc;
पूर्ण

अटल पूर्णांक xgene_edac_mc_हटाओ(काष्ठा xgene_edac_mc_ctx *mcu)
अणु
	xgene_edac_mc_irq_ctl(mcu->mci, false);
	edac_mc_del_mc(&mcu->mci->dev);
	edac_mc_मुक्त(mcu->mci);
	वापस 0;
पूर्ण

/* CPU L1/L2 error CSR */
#घोषणा MAX_CPU_PER_PMD				2
#घोषणा CPU_CSR_STRIDE				0x00100000
#घोषणा CPU_L2C_PAGE				0x000D0000
#घोषणा CPU_MEMERR_L2C_PAGE			0x000E0000
#घोषणा CPU_MEMERR_CPU_PAGE			0x000F0000

#घोषणा MEMERR_CPU_ICFECR_PAGE_OFFSET		0x0000
#घोषणा MEMERR_CPU_ICFESR_PAGE_OFFSET		0x0004
#घोषणा  MEMERR_CPU_ICFESR_ERRWAY_RD(src)	(((src) & 0xFF000000) >> 24)
#घोषणा  MEMERR_CPU_ICFESR_ERRINDEX_RD(src)	(((src) & 0x003F0000) >> 16)
#घोषणा  MEMERR_CPU_ICFESR_ERRINFO_RD(src)	(((src) & 0x0000FF00) >> 8)
#घोषणा  MEMERR_CPU_ICFESR_ERRTYPE_RD(src)	(((src) & 0x00000070) >> 4)
#घोषणा  MEMERR_CPU_ICFESR_MULTCERR_MASK	BIT(2)
#घोषणा  MEMERR_CPU_ICFESR_CERR_MASK		BIT(0)
#घोषणा MEMERR_CPU_LSUESR_PAGE_OFFSET		0x000c
#घोषणा  MEMERR_CPU_LSUESR_ERRWAY_RD(src)	(((src) & 0xFF000000) >> 24)
#घोषणा  MEMERR_CPU_LSUESR_ERRINDEX_RD(src)	(((src) & 0x003F0000) >> 16)
#घोषणा  MEMERR_CPU_LSUESR_ERRINFO_RD(src)	(((src) & 0x0000FF00) >> 8)
#घोषणा  MEMERR_CPU_LSUESR_ERRTYPE_RD(src)	(((src) & 0x00000070) >> 4)
#घोषणा  MEMERR_CPU_LSUESR_MULTCERR_MASK	BIT(2)
#घोषणा  MEMERR_CPU_LSUESR_CERR_MASK		BIT(0)
#घोषणा MEMERR_CPU_LSUECR_PAGE_OFFSET		0x0008
#घोषणा MEMERR_CPU_MMUECR_PAGE_OFFSET		0x0010
#घोषणा MEMERR_CPU_MMUESR_PAGE_OFFSET		0x0014
#घोषणा  MEMERR_CPU_MMUESR_ERRWAY_RD(src)	(((src) & 0xFF000000) >> 24)
#घोषणा  MEMERR_CPU_MMUESR_ERRINDEX_RD(src)	(((src) & 0x007F0000) >> 16)
#घोषणा  MEMERR_CPU_MMUESR_ERRINFO_RD(src)	(((src) & 0x0000FF00) >> 8)
#घोषणा  MEMERR_CPU_MMUESR_ERRREQSTR_LSU_MASK	BIT(7)
#घोषणा  MEMERR_CPU_MMUESR_ERRTYPE_RD(src)	(((src) & 0x00000070) >> 4)
#घोषणा  MEMERR_CPU_MMUESR_MULTCERR_MASK	BIT(2)
#घोषणा  MEMERR_CPU_MMUESR_CERR_MASK		BIT(0)
#घोषणा MEMERR_CPU_ICFESRA_PAGE_OFFSET		0x0804
#घोषणा MEMERR_CPU_LSUESRA_PAGE_OFFSET		0x080c
#घोषणा MEMERR_CPU_MMUESRA_PAGE_OFFSET		0x0814

#घोषणा MEMERR_L2C_L2ECR_PAGE_OFFSET		0x0000
#घोषणा MEMERR_L2C_L2ESR_PAGE_OFFSET		0x0004
#घोषणा  MEMERR_L2C_L2ESR_ERRSYN_RD(src)	(((src) & 0xFF000000) >> 24)
#घोषणा  MEMERR_L2C_L2ESR_ERRWAY_RD(src)	(((src) & 0x00FC0000) >> 18)
#घोषणा  MEMERR_L2C_L2ESR_ERRCPU_RD(src)	(((src) & 0x00020000) >> 17)
#घोषणा  MEMERR_L2C_L2ESR_ERRGROUP_RD(src)	(((src) & 0x0000E000) >> 13)
#घोषणा  MEMERR_L2C_L2ESR_ERRACTION_RD(src)	(((src) & 0x00001C00) >> 10)
#घोषणा  MEMERR_L2C_L2ESR_ERRTYPE_RD(src)	(((src) & 0x00000300) >> 8)
#घोषणा  MEMERR_L2C_L2ESR_MULTUCERR_MASK	BIT(3)
#घोषणा  MEMERR_L2C_L2ESR_MULTICERR_MASK	BIT(2)
#घोषणा  MEMERR_L2C_L2ESR_UCERR_MASK		BIT(1)
#घोषणा  MEMERR_L2C_L2ESR_ERR_MASK		BIT(0)
#घोषणा MEMERR_L2C_L2EALR_PAGE_OFFSET		0x0008
#घोषणा CPUX_L2C_L2RTOCR_PAGE_OFFSET		0x0010
#घोषणा MEMERR_L2C_L2EAHR_PAGE_OFFSET		0x000c
#घोषणा CPUX_L2C_L2RTOSR_PAGE_OFFSET		0x0014
#घोषणा  MEMERR_L2C_L2RTOSR_MULTERR_MASK	BIT(1)
#घोषणा  MEMERR_L2C_L2RTOSR_ERR_MASK		BIT(0)
#घोषणा CPUX_L2C_L2RTOALR_PAGE_OFFSET		0x0018
#घोषणा CPUX_L2C_L2RTOAHR_PAGE_OFFSET		0x001c
#घोषणा MEMERR_L2C_L2ESRA_PAGE_OFFSET		0x0804

/*
 * Processor Module Doमुख्य (PMD) context - Context क्रम a pair of processsors.
 * Each PMD consists of 2 CPUs and a shared L2 cache. Each CPU consists of
 * its own L1 cache.
 */
काष्ठा xgene_edac_pmd_ctx अणु
	काष्ठा list_head	next;
	काष्ठा device		ddev;
	अक्षर			*name;
	काष्ठा xgene_edac	*edac;
	काष्ठा edac_device_ctl_info *edac_dev;
	व्योम __iomem		*pmd_csr;
	u32			pmd;
	पूर्णांक			version;
पूर्ण;

अटल व्योम xgene_edac_pmd_l1_check(काष्ठा edac_device_ctl_info *edac_dev,
				    पूर्णांक cpu_idx)
अणु
	काष्ठा xgene_edac_pmd_ctx *ctx = edac_dev->pvt_info;
	व्योम __iomem *pg_f;
	u32 val;

	pg_f = ctx->pmd_csr + cpu_idx * CPU_CSR_STRIDE + CPU_MEMERR_CPU_PAGE;

	val = पढ़ोl(pg_f + MEMERR_CPU_ICFESR_PAGE_OFFSET);
	अगर (!val)
		जाओ chk_lsu;
	dev_err(edac_dev->dev,
		"CPU%d L1 memory error ICF 0x%08X Way 0x%02X Index 0x%02X Info 0x%02X\n",
		ctx->pmd * MAX_CPU_PER_PMD + cpu_idx, val,
		MEMERR_CPU_ICFESR_ERRWAY_RD(val),
		MEMERR_CPU_ICFESR_ERRINDEX_RD(val),
		MEMERR_CPU_ICFESR_ERRINFO_RD(val));
	अगर (val & MEMERR_CPU_ICFESR_CERR_MASK)
		dev_err(edac_dev->dev, "One or more correctable error\n");
	अगर (val & MEMERR_CPU_ICFESR_MULTCERR_MASK)
		dev_err(edac_dev->dev, "Multiple correctable error\n");
	चयन (MEMERR_CPU_ICFESR_ERRTYPE_RD(val)) अणु
	हाल 1:
		dev_err(edac_dev->dev, "L1 TLB multiple hit\n");
		अवरोध;
	हाल 2:
		dev_err(edac_dev->dev, "Way select multiple hit\n");
		अवरोध;
	हाल 3:
		dev_err(edac_dev->dev, "Physical tag parity error\n");
		अवरोध;
	हाल 4:
	हाल 5:
		dev_err(edac_dev->dev, "L1 data parity error\n");
		अवरोध;
	हाल 6:
		dev_err(edac_dev->dev, "L1 pre-decode parity error\n");
		अवरोध;
	पूर्ण

	/* Clear any HW errors */
	ग_लिखोl(val, pg_f + MEMERR_CPU_ICFESR_PAGE_OFFSET);

	अगर (val & (MEMERR_CPU_ICFESR_CERR_MASK |
		   MEMERR_CPU_ICFESR_MULTCERR_MASK))
		edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);

chk_lsu:
	val = पढ़ोl(pg_f + MEMERR_CPU_LSUESR_PAGE_OFFSET);
	अगर (!val)
		जाओ chk_mmu;
	dev_err(edac_dev->dev,
		"CPU%d memory error LSU 0x%08X Way 0x%02X Index 0x%02X Info 0x%02X\n",
		ctx->pmd * MAX_CPU_PER_PMD + cpu_idx, val,
		MEMERR_CPU_LSUESR_ERRWAY_RD(val),
		MEMERR_CPU_LSUESR_ERRINDEX_RD(val),
		MEMERR_CPU_LSUESR_ERRINFO_RD(val));
	अगर (val & MEMERR_CPU_LSUESR_CERR_MASK)
		dev_err(edac_dev->dev, "One or more correctable error\n");
	अगर (val & MEMERR_CPU_LSUESR_MULTCERR_MASK)
		dev_err(edac_dev->dev, "Multiple correctable error\n");
	चयन (MEMERR_CPU_LSUESR_ERRTYPE_RD(val)) अणु
	हाल 0:
		dev_err(edac_dev->dev, "Load tag error\n");
		अवरोध;
	हाल 1:
		dev_err(edac_dev->dev, "Load data error\n");
		अवरोध;
	हाल 2:
		dev_err(edac_dev->dev, "WSL multihit error\n");
		अवरोध;
	हाल 3:
		dev_err(edac_dev->dev, "Store tag error\n");
		अवरोध;
	हाल 4:
		dev_err(edac_dev->dev,
			"DTB multihit from load pipeline error\n");
		अवरोध;
	हाल 5:
		dev_err(edac_dev->dev,
			"DTB multihit from store pipeline error\n");
		अवरोध;
	पूर्ण

	/* Clear any HW errors */
	ग_लिखोl(val, pg_f + MEMERR_CPU_LSUESR_PAGE_OFFSET);

	अगर (val & (MEMERR_CPU_LSUESR_CERR_MASK |
		   MEMERR_CPU_LSUESR_MULTCERR_MASK))
		edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);

chk_mmu:
	val = पढ़ोl(pg_f + MEMERR_CPU_MMUESR_PAGE_OFFSET);
	अगर (!val)
		वापस;
	dev_err(edac_dev->dev,
		"CPU%d memory error MMU 0x%08X Way 0x%02X Index 0x%02X Info 0x%02X %s\n",
		ctx->pmd * MAX_CPU_PER_PMD + cpu_idx, val,
		MEMERR_CPU_MMUESR_ERRWAY_RD(val),
		MEMERR_CPU_MMUESR_ERRINDEX_RD(val),
		MEMERR_CPU_MMUESR_ERRINFO_RD(val),
		val & MEMERR_CPU_MMUESR_ERRREQSTR_LSU_MASK ? "LSU" : "ICF");
	अगर (val & MEMERR_CPU_MMUESR_CERR_MASK)
		dev_err(edac_dev->dev, "One or more correctable error\n");
	अगर (val & MEMERR_CPU_MMUESR_MULTCERR_MASK)
		dev_err(edac_dev->dev, "Multiple correctable error\n");
	चयन (MEMERR_CPU_MMUESR_ERRTYPE_RD(val)) अणु
	हाल 0:
		dev_err(edac_dev->dev, "Stage 1 UTB hit error\n");
		अवरोध;
	हाल 1:
		dev_err(edac_dev->dev, "Stage 1 UTB miss error\n");
		अवरोध;
	हाल 2:
		dev_err(edac_dev->dev, "Stage 1 UTB allocate error\n");
		अवरोध;
	हाल 3:
		dev_err(edac_dev->dev, "TMO operation single bank error\n");
		अवरोध;
	हाल 4:
		dev_err(edac_dev->dev, "Stage 2 UTB error\n");
		अवरोध;
	हाल 5:
		dev_err(edac_dev->dev, "Stage 2 UTB miss error\n");
		अवरोध;
	हाल 6:
		dev_err(edac_dev->dev, "Stage 2 UTB allocate error\n");
		अवरोध;
	हाल 7:
		dev_err(edac_dev->dev, "TMO operation multiple bank error\n");
		अवरोध;
	पूर्ण

	/* Clear any HW errors */
	ग_लिखोl(val, pg_f + MEMERR_CPU_MMUESR_PAGE_OFFSET);

	edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);
पूर्ण

अटल व्योम xgene_edac_pmd_l2_check(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा xgene_edac_pmd_ctx *ctx = edac_dev->pvt_info;
	व्योम __iomem *pg_d;
	व्योम __iomem *pg_e;
	u32 val_hi;
	u32 val_lo;
	u32 val;

	/* Check L2 */
	pg_e = ctx->pmd_csr + CPU_MEMERR_L2C_PAGE;
	val = पढ़ोl(pg_e + MEMERR_L2C_L2ESR_PAGE_OFFSET);
	अगर (!val)
		जाओ chk_l2c;
	val_lo = पढ़ोl(pg_e + MEMERR_L2C_L2EALR_PAGE_OFFSET);
	val_hi = पढ़ोl(pg_e + MEMERR_L2C_L2EAHR_PAGE_OFFSET);
	dev_err(edac_dev->dev,
		"PMD%d memory error L2C L2ESR 0x%08X @ 0x%08X.%08X\n",
		ctx->pmd, val, val_hi, val_lo);
	dev_err(edac_dev->dev,
		"ErrSyndrome 0x%02X ErrWay 0x%02X ErrCpu %d ErrGroup 0x%02X ErrAction 0x%02X\n",
		MEMERR_L2C_L2ESR_ERRSYN_RD(val),
		MEMERR_L2C_L2ESR_ERRWAY_RD(val),
		MEMERR_L2C_L2ESR_ERRCPU_RD(val),
		MEMERR_L2C_L2ESR_ERRGROUP_RD(val),
		MEMERR_L2C_L2ESR_ERRACTION_RD(val));

	अगर (val & MEMERR_L2C_L2ESR_ERR_MASK)
		dev_err(edac_dev->dev, "One or more correctable error\n");
	अगर (val & MEMERR_L2C_L2ESR_MULTICERR_MASK)
		dev_err(edac_dev->dev, "Multiple correctable error\n");
	अगर (val & MEMERR_L2C_L2ESR_UCERR_MASK)
		dev_err(edac_dev->dev, "One or more uncorrectable error\n");
	अगर (val & MEMERR_L2C_L2ESR_MULTUCERR_MASK)
		dev_err(edac_dev->dev, "Multiple uncorrectable error\n");

	चयन (MEMERR_L2C_L2ESR_ERRTYPE_RD(val)) अणु
	हाल 0:
		dev_err(edac_dev->dev, "Outbound SDB parity error\n");
		अवरोध;
	हाल 1:
		dev_err(edac_dev->dev, "Inbound SDB parity error\n");
		अवरोध;
	हाल 2:
		dev_err(edac_dev->dev, "Tag ECC error\n");
		अवरोध;
	हाल 3:
		dev_err(edac_dev->dev, "Data ECC error\n");
		अवरोध;
	पूर्ण

	/* Clear any HW errors */
	ग_लिखोl(val, pg_e + MEMERR_L2C_L2ESR_PAGE_OFFSET);

	अगर (val & (MEMERR_L2C_L2ESR_ERR_MASK |
		   MEMERR_L2C_L2ESR_MULTICERR_MASK))
		edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);
	अगर (val & (MEMERR_L2C_L2ESR_UCERR_MASK |
		   MEMERR_L2C_L2ESR_MULTUCERR_MASK))
		edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);

chk_l2c:
	/* Check अगर any memory request समयd out on L2 cache */
	pg_d = ctx->pmd_csr + CPU_L2C_PAGE;
	val = पढ़ोl(pg_d + CPUX_L2C_L2RTOSR_PAGE_OFFSET);
	अगर (val) अणु
		val_lo = पढ़ोl(pg_d + CPUX_L2C_L2RTOALR_PAGE_OFFSET);
		val_hi = पढ़ोl(pg_d + CPUX_L2C_L2RTOAHR_PAGE_OFFSET);
		dev_err(edac_dev->dev,
			"PMD%d L2C error L2C RTOSR 0x%08X @ 0x%08X.%08X\n",
			ctx->pmd, val, val_hi, val_lo);
		ग_लिखोl(val, pg_d + CPUX_L2C_L2RTOSR_PAGE_OFFSET);
	पूर्ण
पूर्ण

अटल व्योम xgene_edac_pmd_check(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा xgene_edac_pmd_ctx *ctx = edac_dev->pvt_info;
	अचिन्हित पूर्णांक pcp_hp_stat;
	पूर्णांक i;

	xgene_edac_pcp_rd(ctx->edac, PCPHPERRINTSTS, &pcp_hp_stat);
	अगर (!((PMD0_MERR_MASK << ctx->pmd) & pcp_hp_stat))
		वापस;

	/* Check CPU L1 error */
	क्रम (i = 0; i < MAX_CPU_PER_PMD; i++)
		xgene_edac_pmd_l1_check(edac_dev, i);

	/* Check CPU L2 error */
	xgene_edac_pmd_l2_check(edac_dev);
पूर्ण

अटल व्योम xgene_edac_pmd_cpu_hw_cfg(काष्ठा edac_device_ctl_info *edac_dev,
				      पूर्णांक cpu)
अणु
	काष्ठा xgene_edac_pmd_ctx *ctx = edac_dev->pvt_info;
	व्योम __iomem *pg_f = ctx->pmd_csr + cpu * CPU_CSR_STRIDE +
			     CPU_MEMERR_CPU_PAGE;

	/*
	 * Enable CPU memory error:
	 *  MEMERR_CPU_ICFESRA, MEMERR_CPU_LSUESRA, and MEMERR_CPU_MMUESRA
	 */
	ग_लिखोl(0x00000301, pg_f + MEMERR_CPU_ICFECR_PAGE_OFFSET);
	ग_लिखोl(0x00000301, pg_f + MEMERR_CPU_LSUECR_PAGE_OFFSET);
	ग_लिखोl(0x00000101, pg_f + MEMERR_CPU_MMUECR_PAGE_OFFSET);
पूर्ण

अटल व्योम xgene_edac_pmd_hw_cfg(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा xgene_edac_pmd_ctx *ctx = edac_dev->pvt_info;
	व्योम __iomem *pg_d = ctx->pmd_csr + CPU_L2C_PAGE;
	व्योम __iomem *pg_e = ctx->pmd_csr + CPU_MEMERR_L2C_PAGE;

	/* Enable PMD memory error - MEMERR_L2C_L2ECR and L2C_L2RTOCR */
	ग_लिखोl(0x00000703, pg_e + MEMERR_L2C_L2ECR_PAGE_OFFSET);
	/* Configure L2C HW request समय out feature अगर supported */
	अगर (ctx->version > 1)
		ग_लिखोl(0x00000119, pg_d + CPUX_L2C_L2RTOCR_PAGE_OFFSET);
पूर्ण

अटल व्योम xgene_edac_pmd_hw_ctl(काष्ठा edac_device_ctl_info *edac_dev,
				  bool enable)
अणु
	काष्ठा xgene_edac_pmd_ctx *ctx = edac_dev->pvt_info;
	पूर्णांक i;

	/* Enable PMD error पूर्णांकerrupt */
	अगर (edac_dev->op_state == OP_RUNNING_INTERRUPT) अणु
		अगर (enable)
			xgene_edac_pcp_clrbits(ctx->edac, PCPHPERRINTMSK,
					       PMD0_MERR_MASK << ctx->pmd);
		अन्यथा
			xgene_edac_pcp_setbits(ctx->edac, PCPHPERRINTMSK,
					       PMD0_MERR_MASK << ctx->pmd);
	पूर्ण

	अगर (enable) अणु
		xgene_edac_pmd_hw_cfg(edac_dev);

		/* Two CPUs per a PMD */
		क्रम (i = 0; i < MAX_CPU_PER_PMD; i++)
			xgene_edac_pmd_cpu_hw_cfg(edac_dev, i);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार xgene_edac_pmd_l1_inject_ctrl_ग_लिखो(काष्ठा file *file,
						   स्थिर अक्षर __user *data,
						   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = file->निजी_data;
	काष्ठा xgene_edac_pmd_ctx *ctx = edac_dev->pvt_info;
	व्योम __iomem *cpux_pg_f;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_CPU_PER_PMD; i++) अणु
		cpux_pg_f = ctx->pmd_csr + i * CPU_CSR_STRIDE +
			    CPU_MEMERR_CPU_PAGE;

		ग_लिखोl(MEMERR_CPU_ICFESR_MULTCERR_MASK |
		       MEMERR_CPU_ICFESR_CERR_MASK,
		       cpux_pg_f + MEMERR_CPU_ICFESRA_PAGE_OFFSET);
		ग_लिखोl(MEMERR_CPU_LSUESR_MULTCERR_MASK |
		       MEMERR_CPU_LSUESR_CERR_MASK,
		       cpux_pg_f + MEMERR_CPU_LSUESRA_PAGE_OFFSET);
		ग_लिखोl(MEMERR_CPU_MMUESR_MULTCERR_MASK |
		       MEMERR_CPU_MMUESR_CERR_MASK,
		       cpux_pg_f + MEMERR_CPU_MMUESRA_PAGE_OFFSET);
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार xgene_edac_pmd_l2_inject_ctrl_ग_लिखो(काष्ठा file *file,
						   स्थिर अक्षर __user *data,
						   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = file->निजी_data;
	काष्ठा xgene_edac_pmd_ctx *ctx = edac_dev->pvt_info;
	व्योम __iomem *pg_e = ctx->pmd_csr + CPU_MEMERR_L2C_PAGE;

	ग_लिखोl(MEMERR_L2C_L2ESR_MULTUCERR_MASK |
	       MEMERR_L2C_L2ESR_MULTICERR_MASK |
	       MEMERR_L2C_L2ESR_UCERR_MASK |
	       MEMERR_L2C_L2ESR_ERR_MASK,
	       pg_e + MEMERR_L2C_L2ESRA_PAGE_OFFSET);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations xgene_edac_pmd_debug_inject_fops[] = अणु
	अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = xgene_edac_pmd_l1_inject_ctrl_ग_लिखो,
	.llseek = generic_file_llseek, पूर्ण,
	अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = xgene_edac_pmd_l2_inject_ctrl_ग_लिखो,
	.llseek = generic_file_llseek, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम
xgene_edac_pmd_create_debugfs_nodes(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा xgene_edac_pmd_ctx *ctx = edac_dev->pvt_info;
	काष्ठा dentry *dbgfs_dir;
	अक्षर name[10];

	अगर (!IS_ENABLED(CONFIG_EDAC_DEBUG) || !ctx->edac->dfs)
		वापस;

	snम_लिखो(name, माप(name), "PMD%d", ctx->pmd);
	dbgfs_dir = edac_debugfs_create_dir_at(name, ctx->edac->dfs);
	अगर (!dbgfs_dir)
		वापस;

	edac_debugfs_create_file("l1_inject_ctrl", S_IWUSR, dbgfs_dir, edac_dev,
				 &xgene_edac_pmd_debug_inject_fops[0]);
	edac_debugfs_create_file("l2_inject_ctrl", S_IWUSR, dbgfs_dir, edac_dev,
				 &xgene_edac_pmd_debug_inject_fops[1]);
पूर्ण

अटल पूर्णांक xgene_edac_pmd_available(u32 efuse, पूर्णांक pmd)
अणु
	वापस (efuse & (1 << pmd)) ? 0 : 1;
पूर्ण

अटल पूर्णांक xgene_edac_pmd_add(काष्ठा xgene_edac *edac, काष्ठा device_node *np,
			      पूर्णांक version)
अणु
	काष्ठा edac_device_ctl_info *edac_dev;
	काष्ठा xgene_edac_pmd_ctx *ctx;
	काष्ठा resource res;
	अक्षर edac_name[10];
	u32 pmd;
	पूर्णांक rc;
	u32 val;

	अगर (!devres_खोलो_group(edac->dev, xgene_edac_pmd_add, GFP_KERNEL))
		वापस -ENOMEM;

	/* Determine अगर this PMD is disabled */
	अगर (of_property_पढ़ो_u32(np, "pmd-controller", &pmd)) अणु
		dev_err(edac->dev, "no pmd-controller property\n");
		rc = -ENODEV;
		जाओ err_group;
	पूर्ण
	rc = regmap_पढ़ो(edac->efuse_map, 0, &val);
	अगर (rc)
		जाओ err_group;
	अगर (!xgene_edac_pmd_available(val, pmd)) अणु
		rc = -ENODEV;
		जाओ err_group;
	पूर्ण

	snम_लिखो(edac_name, माप(edac_name), "l2c%d", pmd);
	edac_dev = edac_device_alloc_ctl_info(माप(*ctx),
					      edac_name, 1, "l2c", 1, 2, शून्य,
					      0, edac_device_alloc_index());
	अगर (!edac_dev) अणु
		rc = -ENOMEM;
		जाओ err_group;
	पूर्ण

	ctx = edac_dev->pvt_info;
	ctx->name = "xgene_pmd_err";
	ctx->pmd = pmd;
	ctx->edac = edac;
	ctx->edac_dev = edac_dev;
	ctx->ddev = *edac->dev;
	ctx->version = version;
	edac_dev->dev = &ctx->ddev;
	edac_dev->ctl_name = ctx->name;
	edac_dev->dev_name = ctx->name;
	edac_dev->mod_name = EDAC_MOD_STR;

	rc = of_address_to_resource(np, 0, &res);
	अगर (rc < 0) अणु
		dev_err(edac->dev, "no PMD resource address\n");
		जाओ err_मुक्त;
	पूर्ण
	ctx->pmd_csr = devm_ioremap_resource(edac->dev, &res);
	अगर (IS_ERR(ctx->pmd_csr)) अणु
		dev_err(edac->dev,
			"devm_ioremap_resource failed for PMD resource address\n");
		rc = PTR_ERR(ctx->pmd_csr);
		जाओ err_मुक्त;
	पूर्ण

	अगर (edac_op_state == EDAC_OPSTATE_POLL)
		edac_dev->edac_check = xgene_edac_pmd_check;

	xgene_edac_pmd_create_debugfs_nodes(edac_dev);

	rc = edac_device_add_device(edac_dev);
	अगर (rc > 0) अणु
		dev_err(edac->dev, "edac_device_add_device failed\n");
		rc = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	अगर (edac_op_state == EDAC_OPSTATE_INT)
		edac_dev->op_state = OP_RUNNING_INTERRUPT;

	list_add(&ctx->next, &edac->pmds);

	xgene_edac_pmd_hw_ctl(edac_dev, 1);

	devres_हटाओ_group(edac->dev, xgene_edac_pmd_add);

	dev_info(edac->dev, "X-Gene EDAC PMD%d registered\n", ctx->pmd);
	वापस 0;

err_मुक्त:
	edac_device_मुक्त_ctl_info(edac_dev);
err_group:
	devres_release_group(edac->dev, xgene_edac_pmd_add);
	वापस rc;
पूर्ण

अटल पूर्णांक xgene_edac_pmd_हटाओ(काष्ठा xgene_edac_pmd_ctx *pmd)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = pmd->edac_dev;

	xgene_edac_pmd_hw_ctl(edac_dev, 0);
	edac_device_del_device(edac_dev->dev);
	edac_device_मुक्त_ctl_info(edac_dev);
	वापस 0;
पूर्ण

/* L3 Error device */
#घोषणा L3C_ESR				(0x0A * 4)
#घोषणा  L3C_ESR_DATATAG_MASK		BIT(9)
#घोषणा  L3C_ESR_MULTIHIT_MASK		BIT(8)
#घोषणा  L3C_ESR_UCEVICT_MASK		BIT(6)
#घोषणा  L3C_ESR_MULTIUCERR_MASK	BIT(5)
#घोषणा  L3C_ESR_MULTICERR_MASK		BIT(4)
#घोषणा  L3C_ESR_UCERR_MASK		BIT(3)
#घोषणा  L3C_ESR_CERR_MASK		BIT(2)
#घोषणा  L3C_ESR_UCERRINTR_MASK		BIT(1)
#घोषणा  L3C_ESR_CERRINTR_MASK		BIT(0)
#घोषणा L3C_ECR				(0x0B * 4)
#घोषणा  L3C_ECR_UCINTREN		BIT(3)
#घोषणा  L3C_ECR_CINTREN		BIT(2)
#घोषणा  L3C_UCERREN			BIT(1)
#घोषणा  L3C_CERREN			BIT(0)
#घोषणा L3C_ELR				(0x0C * 4)
#घोषणा  L3C_ELR_ERRSYN(src)		((src & 0xFF800000) >> 23)
#घोषणा  L3C_ELR_ERRWAY(src)		((src & 0x007E0000) >> 17)
#घोषणा  L3C_ELR_AGENTID(src)		((src & 0x0001E000) >> 13)
#घोषणा  L3C_ELR_ERRGRP(src)		((src & 0x00000F00) >> 8)
#घोषणा  L3C_ELR_OPTYPE(src)		((src & 0x000000F0) >> 4)
#घोषणा  L3C_ELR_PADDRHIGH(src)		(src & 0x0000000F)
#घोषणा L3C_AELR			(0x0D * 4)
#घोषणा L3C_BELR			(0x0E * 4)
#घोषणा  L3C_BELR_BANK(src)		(src & 0x0000000F)

काष्ठा xgene_edac_dev_ctx अणु
	काष्ठा list_head	next;
	काष्ठा device		ddev;
	अक्षर			*name;
	काष्ठा xgene_edac	*edac;
	काष्ठा edac_device_ctl_info *edac_dev;
	पूर्णांक			edac_idx;
	व्योम __iomem		*dev_csr;
	पूर्णांक			version;
पूर्ण;

/*
 * Version 1 of the L3 controller has broken single bit correctable logic क्रम
 * certain error syndromes. Log them as uncorrectable in that हाल.
 */
अटल bool xgene_edac_l3_promote_to_uc_err(u32 l3cesr, u32 l3celr)
अणु
	अगर (l3cesr & L3C_ESR_DATATAG_MASK) अणु
		चयन (L3C_ELR_ERRSYN(l3celr)) अणु
		हाल 0x13C:
		हाल 0x0B4:
		हाल 0x007:
		हाल 0x00D:
		हाल 0x00E:
		हाल 0x019:
		हाल 0x01A:
		हाल 0x01C:
		हाल 0x04E:
		हाल 0x041:
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अगर (L3C_ELR_ERRWAY(l3celr) == 9)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम xgene_edac_l3_check(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	u32 l3cesr;
	u32 l3celr;
	u32 l3caelr;
	u32 l3cbelr;

	l3cesr = पढ़ोl(ctx->dev_csr + L3C_ESR);
	अगर (!(l3cesr & (L3C_ESR_UCERR_MASK | L3C_ESR_CERR_MASK)))
		वापस;

	अगर (l3cesr & L3C_ESR_UCERR_MASK)
		dev_err(edac_dev->dev, "L3C uncorrectable error\n");
	अगर (l3cesr & L3C_ESR_CERR_MASK)
		dev_warn(edac_dev->dev, "L3C correctable error\n");

	l3celr = पढ़ोl(ctx->dev_csr + L3C_ELR);
	l3caelr = पढ़ोl(ctx->dev_csr + L3C_AELR);
	l3cbelr = पढ़ोl(ctx->dev_csr + L3C_BELR);
	अगर (l3cesr & L3C_ESR_MULTIHIT_MASK)
		dev_err(edac_dev->dev, "L3C multiple hit error\n");
	अगर (l3cesr & L3C_ESR_UCEVICT_MASK)
		dev_err(edac_dev->dev,
			"L3C dropped eviction of line with error\n");
	अगर (l3cesr & L3C_ESR_MULTIUCERR_MASK)
		dev_err(edac_dev->dev, "L3C multiple uncorrectable error\n");
	अगर (l3cesr & L3C_ESR_DATATAG_MASK)
		dev_err(edac_dev->dev,
			"L3C data error syndrome 0x%X group 0x%X\n",
			L3C_ELR_ERRSYN(l3celr), L3C_ELR_ERRGRP(l3celr));
	अन्यथा
		dev_err(edac_dev->dev,
			"L3C tag error syndrome 0x%X Way of Tag 0x%X Agent ID 0x%X Operation type 0x%X\n",
			L3C_ELR_ERRSYN(l3celr), L3C_ELR_ERRWAY(l3celr),
			L3C_ELR_AGENTID(l3celr), L3C_ELR_OPTYPE(l3celr));
	/*
	 * NOTE: Address [41:38] in L3C_ELR_PADDRHIGH(l3celr).
	 *       Address [37:6] in l3caelr. Lower 6 bits are zero.
	 */
	dev_err(edac_dev->dev, "L3C error address 0x%08X.%08X bank %d\n",
		L3C_ELR_PADDRHIGH(l3celr) << 6 | (l3caelr >> 26),
		(l3caelr & 0x3FFFFFFF) << 6, L3C_BELR_BANK(l3cbelr));
	dev_err(edac_dev->dev,
		"L3C error status register value 0x%X\n", l3cesr);

	/* Clear L3C error पूर्णांकerrupt */
	ग_लिखोl(0, ctx->dev_csr + L3C_ESR);

	अगर (ctx->version <= 1 &&
	    xgene_edac_l3_promote_to_uc_err(l3cesr, l3celr)) अणु
		edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
		वापस;
	पूर्ण
	अगर (l3cesr & L3C_ESR_CERR_MASK)
		edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);
	अगर (l3cesr & L3C_ESR_UCERR_MASK)
		edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
पूर्ण

अटल व्योम xgene_edac_l3_hw_init(काष्ठा edac_device_ctl_info *edac_dev,
				  bool enable)
अणु
	काष्ठा xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	u32 val;

	val = पढ़ोl(ctx->dev_csr + L3C_ECR);
	val |= L3C_UCERREN | L3C_CERREN;
	/* On disable, we just disable पूर्णांकerrupt but keep error enabled */
	अगर (edac_dev->op_state == OP_RUNNING_INTERRUPT) अणु
		अगर (enable)
			val |= L3C_ECR_UCINTREN | L3C_ECR_CINTREN;
		अन्यथा
			val &= ~(L3C_ECR_UCINTREN | L3C_ECR_CINTREN);
	पूर्ण
	ग_लिखोl(val, ctx->dev_csr + L3C_ECR);

	अगर (edac_dev->op_state == OP_RUNNING_INTERRUPT) अणु
		/* Enable/disable L3 error top level पूर्णांकerrupt */
		अगर (enable) अणु
			xgene_edac_pcp_clrbits(ctx->edac, PCPHPERRINTMSK,
					       L3C_UNCORR_ERR_MASK);
			xgene_edac_pcp_clrbits(ctx->edac, PCPLPERRINTMSK,
					       L3C_CORR_ERR_MASK);
		पूर्ण अन्यथा अणु
			xgene_edac_pcp_setbits(ctx->edac, PCPHPERRINTMSK,
					       L3C_UNCORR_ERR_MASK);
			xgene_edac_pcp_setbits(ctx->edac, PCPLPERRINTMSK,
					       L3C_CORR_ERR_MASK);
		पूर्ण
	पूर्ण
पूर्ण

अटल sमाप_प्रकार xgene_edac_l3_inject_ctrl_ग_लिखो(काष्ठा file *file,
					       स्थिर अक्षर __user *data,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = file->निजी_data;
	काष्ठा xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;

	/* Generate all errors */
	ग_लिखोl(0xFFFFFFFF, ctx->dev_csr + L3C_ESR);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations xgene_edac_l3_debug_inject_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = xgene_edac_l3_inject_ctrl_ग_लिखो,
	.llseek = generic_file_llseek
पूर्ण;

अटल व्योम
xgene_edac_l3_create_debugfs_nodes(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	काष्ठा dentry *dbgfs_dir;
	अक्षर name[10];

	अगर (!IS_ENABLED(CONFIG_EDAC_DEBUG) || !ctx->edac->dfs)
		वापस;

	snम_लिखो(name, माप(name), "l3c%d", ctx->edac_idx);
	dbgfs_dir = edac_debugfs_create_dir_at(name, ctx->edac->dfs);
	अगर (!dbgfs_dir)
		वापस;

	debugfs_create_file("l3_inject_ctrl", S_IWUSR, dbgfs_dir, edac_dev,
			    &xgene_edac_l3_debug_inject_fops);
पूर्ण

अटल पूर्णांक xgene_edac_l3_add(काष्ठा xgene_edac *edac, काष्ठा device_node *np,
			     पूर्णांक version)
अणु
	काष्ठा edac_device_ctl_info *edac_dev;
	काष्ठा xgene_edac_dev_ctx *ctx;
	काष्ठा resource res;
	व्योम __iomem *dev_csr;
	पूर्णांक edac_idx;
	पूर्णांक rc = 0;

	अगर (!devres_खोलो_group(edac->dev, xgene_edac_l3_add, GFP_KERNEL))
		वापस -ENOMEM;

	rc = of_address_to_resource(np, 0, &res);
	अगर (rc < 0) अणु
		dev_err(edac->dev, "no L3 resource address\n");
		जाओ err_release_group;
	पूर्ण
	dev_csr = devm_ioremap_resource(edac->dev, &res);
	अगर (IS_ERR(dev_csr)) अणु
		dev_err(edac->dev,
			"devm_ioremap_resource failed for L3 resource address\n");
		rc = PTR_ERR(dev_csr);
		जाओ err_release_group;
	पूर्ण

	edac_idx = edac_device_alloc_index();
	edac_dev = edac_device_alloc_ctl_info(माप(*ctx),
					      "l3c", 1, "l3c", 1, 0, शून्य, 0,
					      edac_idx);
	अगर (!edac_dev) अणु
		rc = -ENOMEM;
		जाओ err_release_group;
	पूर्ण

	ctx = edac_dev->pvt_info;
	ctx->dev_csr = dev_csr;
	ctx->name = "xgene_l3_err";
	ctx->edac_idx = edac_idx;
	ctx->edac = edac;
	ctx->edac_dev = edac_dev;
	ctx->ddev = *edac->dev;
	ctx->version = version;
	edac_dev->dev = &ctx->ddev;
	edac_dev->ctl_name = ctx->name;
	edac_dev->dev_name = ctx->name;
	edac_dev->mod_name = EDAC_MOD_STR;

	अगर (edac_op_state == EDAC_OPSTATE_POLL)
		edac_dev->edac_check = xgene_edac_l3_check;

	xgene_edac_l3_create_debugfs_nodes(edac_dev);

	rc = edac_device_add_device(edac_dev);
	अगर (rc > 0) अणु
		dev_err(edac->dev, "failed edac_device_add_device()\n");
		rc = -ENOMEM;
		जाओ err_ctl_मुक्त;
	पूर्ण

	अगर (edac_op_state == EDAC_OPSTATE_INT)
		edac_dev->op_state = OP_RUNNING_INTERRUPT;

	list_add(&ctx->next, &edac->l3s);

	xgene_edac_l3_hw_init(edac_dev, 1);

	devres_हटाओ_group(edac->dev, xgene_edac_l3_add);

	dev_info(edac->dev, "X-Gene EDAC L3 registered\n");
	वापस 0;

err_ctl_मुक्त:
	edac_device_मुक्त_ctl_info(edac_dev);
err_release_group:
	devres_release_group(edac->dev, xgene_edac_l3_add);
	वापस rc;
पूर्ण

अटल पूर्णांक xgene_edac_l3_हटाओ(काष्ठा xgene_edac_dev_ctx *l3)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = l3->edac_dev;

	xgene_edac_l3_hw_init(edac_dev, 0);
	edac_device_del_device(l3->edac->dev);
	edac_device_मुक्त_ctl_info(edac_dev);
	वापस 0;
पूर्ण

/* SoC error device */
#घोषणा IOBAXIS0TRANSERRINTSTS		0x0000
#घोषणा  IOBAXIS0_M_ILLEGAL_ACCESS_MASK	BIT(1)
#घोषणा  IOBAXIS0_ILLEGAL_ACCESS_MASK	BIT(0)
#घोषणा IOBAXIS0TRANSERRINTMSK		0x0004
#घोषणा IOBAXIS0TRANSERRREQINFOL	0x0008
#घोषणा IOBAXIS0TRANSERRREQINFOH	0x000c
#घोषणा  REQTYPE_RD(src)		(((src) & BIT(0)))
#घोषणा  ERRADDRH_RD(src)		(((src) & 0xffc00000) >> 22)
#घोषणा IOBAXIS1TRANSERRINTSTS		0x0010
#घोषणा IOBAXIS1TRANSERRINTMSK		0x0014
#घोषणा IOBAXIS1TRANSERRREQINFOL	0x0018
#घोषणा IOBAXIS1TRANSERRREQINFOH	0x001c
#घोषणा IOBPATRANSERRINTSTS		0x0020
#घोषणा  IOBPA_M_REQIDRAM_CORRUPT_MASK	BIT(7)
#घोषणा  IOBPA_REQIDRAM_CORRUPT_MASK	BIT(6)
#घोषणा  IOBPA_M_TRANS_CORRUPT_MASK	BIT(5)
#घोषणा  IOBPA_TRANS_CORRUPT_MASK	BIT(4)
#घोषणा  IOBPA_M_WDATA_CORRUPT_MASK	BIT(3)
#घोषणा  IOBPA_WDATA_CORRUPT_MASK	BIT(2)
#घोषणा  IOBPA_M_RDATA_CORRUPT_MASK	BIT(1)
#घोषणा  IOBPA_RDATA_CORRUPT_MASK	BIT(0)
#घोषणा IOBBATRANSERRINTSTS		0x0030
#घोषणा  M_ILLEGAL_ACCESS_MASK		BIT(15)
#घोषणा  ILLEGAL_ACCESS_MASK		BIT(14)
#घोषणा  M_WIDRAM_CORRUPT_MASK		BIT(13)
#घोषणा  WIDRAM_CORRUPT_MASK		BIT(12)
#घोषणा  M_RIDRAM_CORRUPT_MASK		BIT(11)
#घोषणा  RIDRAM_CORRUPT_MASK		BIT(10)
#घोषणा  M_TRANS_CORRUPT_MASK		BIT(9)
#घोषणा  TRANS_CORRUPT_MASK		BIT(8)
#घोषणा  M_WDATA_CORRUPT_MASK		BIT(7)
#घोषणा  WDATA_CORRUPT_MASK		BIT(6)
#घोषणा  M_RBM_POISONED_REQ_MASK	BIT(5)
#घोषणा  RBM_POISONED_REQ_MASK		BIT(4)
#घोषणा  M_XGIC_POISONED_REQ_MASK	BIT(3)
#घोषणा  XGIC_POISONED_REQ_MASK		BIT(2)
#घोषणा  M_WRERR_RESP_MASK		BIT(1)
#घोषणा  WRERR_RESP_MASK		BIT(0)
#घोषणा IOBBATRANSERRREQINFOL		0x0038
#घोषणा IOBBATRANSERRREQINFOH		0x003c
#घोषणा  REQTYPE_F2_RD(src)		((src) & BIT(0))
#घोषणा  ERRADDRH_F2_RD(src)		(((src) & 0xffc00000) >> 22)
#घोषणा IOBBATRANSERRCSWREQID		0x0040
#घोषणा XGICTRANSERRINTSTS		0x0050
#घोषणा  M_WR_ACCESS_ERR_MASK		BIT(3)
#घोषणा  WR_ACCESS_ERR_MASK		BIT(2)
#घोषणा  M_RD_ACCESS_ERR_MASK		BIT(1)
#घोषणा  RD_ACCESS_ERR_MASK		BIT(0)
#घोषणा XGICTRANSERRINTMSK		0x0054
#घोषणा XGICTRANSERRREQINFO		0x0058
#घोषणा  REQTYPE_MASK			BIT(26)
#घोषणा  ERRADDR_RD(src)		((src) & 0x03ffffff)
#घोषणा GLBL_ERR_STS			0x0800
#घोषणा  MDED_ERR_MASK			BIT(3)
#घोषणा  DED_ERR_MASK			BIT(2)
#घोषणा  MSEC_ERR_MASK			BIT(1)
#घोषणा  SEC_ERR_MASK			BIT(0)
#घोषणा GLBL_SEC_ERRL			0x0810
#घोषणा GLBL_SEC_ERRH			0x0818
#घोषणा GLBL_MSEC_ERRL			0x0820
#घोषणा GLBL_MSEC_ERRH			0x0828
#घोषणा GLBL_DED_ERRL			0x0830
#घोषणा GLBL_DED_ERRLMASK		0x0834
#घोषणा GLBL_DED_ERRH			0x0838
#घोषणा GLBL_DED_ERRHMASK		0x083c
#घोषणा GLBL_MDED_ERRL			0x0840
#घोषणा GLBL_MDED_ERRLMASK		0x0844
#घोषणा GLBL_MDED_ERRH			0x0848
#घोषणा GLBL_MDED_ERRHMASK		0x084c

/* IO Bus Registers */
#घोषणा RBCSR				0x0000
#घोषणा STICKYERR_MASK			BIT(0)
#घोषणा RBEIR				0x0008
#घोषणा AGENT_OFFLINE_ERR_MASK		BIT(30)
#घोषणा UNIMPL_RBPAGE_ERR_MASK		BIT(29)
#घोषणा WORD_ALIGNED_ERR_MASK		BIT(28)
#घोषणा PAGE_ACCESS_ERR_MASK		BIT(27)
#घोषणा WRITE_ACCESS_MASK		BIT(26)

अटल स्थिर अक्षर * स्थिर soc_mem_err_v1[] = अणु
	"10GbE0",
	"10GbE1",
	"Security",
	"SATA45",
	"SATA23/ETH23",
	"SATA01/ETH01",
	"USB1",
	"USB0",
	"QML",
	"QM0",
	"QM1 (XGbE01)",
	"PCIE4",
	"PCIE3",
	"PCIE2",
	"PCIE1",
	"PCIE0",
	"CTX Manager",
	"OCM",
	"1GbE",
	"CLE",
	"AHBC",
	"PktDMA",
	"GFC",
	"MSLIM",
	"10GbE2",
	"10GbE3",
	"QM2 (XGbE23)",
	"IOB",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
पूर्ण;

अटल व्योम xgene_edac_iob_gic_report(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	u32 err_addr_lo;
	u32 err_addr_hi;
	u32 reg;
	u32 info;

	/* GIC transaction error पूर्णांकerrupt */
	reg = पढ़ोl(ctx->dev_csr + XGICTRANSERRINTSTS);
	अगर (!reg)
		जाओ chk_iob_err;
	dev_err(edac_dev->dev, "XGIC transaction error\n");
	अगर (reg & RD_ACCESS_ERR_MASK)
		dev_err(edac_dev->dev, "XGIC read size error\n");
	अगर (reg & M_RD_ACCESS_ERR_MASK)
		dev_err(edac_dev->dev, "Multiple XGIC read size error\n");
	अगर (reg & WR_ACCESS_ERR_MASK)
		dev_err(edac_dev->dev, "XGIC write size error\n");
	अगर (reg & M_WR_ACCESS_ERR_MASK)
		dev_err(edac_dev->dev, "Multiple XGIC write size error\n");
	info = पढ़ोl(ctx->dev_csr + XGICTRANSERRREQINFO);
	dev_err(edac_dev->dev, "XGIC %s access @ 0x%08X (0x%08X)\n",
		info & REQTYPE_MASK ? "read" : "write", ERRADDR_RD(info),
		info);
	ग_लिखोl(reg, ctx->dev_csr + XGICTRANSERRINTSTS);

chk_iob_err:
	/* IOB memory error */
	reg = पढ़ोl(ctx->dev_csr + GLBL_ERR_STS);
	अगर (!reg)
		वापस;
	अगर (reg & SEC_ERR_MASK) अणु
		err_addr_lo = पढ़ोl(ctx->dev_csr + GLBL_SEC_ERRL);
		err_addr_hi = पढ़ोl(ctx->dev_csr + GLBL_SEC_ERRH);
		dev_err(edac_dev->dev,
			"IOB single-bit correctable memory at 0x%08X.%08X error\n",
			err_addr_lo, err_addr_hi);
		ग_लिखोl(err_addr_lo, ctx->dev_csr + GLBL_SEC_ERRL);
		ग_लिखोl(err_addr_hi, ctx->dev_csr + GLBL_SEC_ERRH);
	पूर्ण
	अगर (reg & MSEC_ERR_MASK) अणु
		err_addr_lo = पढ़ोl(ctx->dev_csr + GLBL_MSEC_ERRL);
		err_addr_hi = पढ़ोl(ctx->dev_csr + GLBL_MSEC_ERRH);
		dev_err(edac_dev->dev,
			"IOB multiple single-bit correctable memory at 0x%08X.%08X error\n",
			err_addr_lo, err_addr_hi);
		ग_लिखोl(err_addr_lo, ctx->dev_csr + GLBL_MSEC_ERRL);
		ग_लिखोl(err_addr_hi, ctx->dev_csr + GLBL_MSEC_ERRH);
	पूर्ण
	अगर (reg & (SEC_ERR_MASK | MSEC_ERR_MASK))
		edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);

	अगर (reg & DED_ERR_MASK) अणु
		err_addr_lo = पढ़ोl(ctx->dev_csr + GLBL_DED_ERRL);
		err_addr_hi = पढ़ोl(ctx->dev_csr + GLBL_DED_ERRH);
		dev_err(edac_dev->dev,
			"IOB double-bit uncorrectable memory at 0x%08X.%08X error\n",
			err_addr_lo, err_addr_hi);
		ग_लिखोl(err_addr_lo, ctx->dev_csr + GLBL_DED_ERRL);
		ग_लिखोl(err_addr_hi, ctx->dev_csr + GLBL_DED_ERRH);
	पूर्ण
	अगर (reg & MDED_ERR_MASK) अणु
		err_addr_lo = पढ़ोl(ctx->dev_csr + GLBL_MDED_ERRL);
		err_addr_hi = पढ़ोl(ctx->dev_csr + GLBL_MDED_ERRH);
		dev_err(edac_dev->dev,
			"Multiple IOB double-bit uncorrectable memory at 0x%08X.%08X error\n",
			err_addr_lo, err_addr_hi);
		ग_लिखोl(err_addr_lo, ctx->dev_csr + GLBL_MDED_ERRL);
		ग_लिखोl(err_addr_hi, ctx->dev_csr + GLBL_MDED_ERRH);
	पूर्ण
	अगर (reg & (DED_ERR_MASK | MDED_ERR_MASK))
		edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
पूर्ण

अटल व्योम xgene_edac_rb_report(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	u32 err_addr_lo;
	u32 err_addr_hi;
	u32 reg;

	/* If the रेजिस्टर bus resource isn't available, just skip it */
	अगर (!ctx->edac->rb_map)
		जाओ rb_skip;

	/*
	 * Check RB access errors
	 * 1. Out of range
	 * 2. Un-implemented page
	 * 3. Un-aligned access
	 * 4. Offline slave IP
	 */
	अगर (regmap_पढ़ो(ctx->edac->rb_map, RBCSR, &reg))
		वापस;
	अगर (reg & STICKYERR_MASK) अणु
		bool ग_लिखो;

		dev_err(edac_dev->dev, "IOB bus access error(s)\n");
		अगर (regmap_पढ़ो(ctx->edac->rb_map, RBEIR, &reg))
			वापस;
		ग_लिखो = reg & WRITE_ACCESS_MASK ? 1 : 0;
		अगर (reg & AGENT_OFFLINE_ERR_MASK)
			dev_err(edac_dev->dev,
				"IOB bus %s access to offline agent error\n",
				ग_लिखो ? "write" : "read");
		अगर (reg & UNIMPL_RBPAGE_ERR_MASK)
			dev_err(edac_dev->dev,
				"IOB bus %s access to unimplemented page error\n",
				ग_लिखो ? "write" : "read");
		अगर (reg & WORD_ALIGNED_ERR_MASK)
			dev_err(edac_dev->dev,
				"IOB bus %s word aligned access error\n",
				ग_लिखो ? "write" : "read");
		अगर (reg & PAGE_ACCESS_ERR_MASK)
			dev_err(edac_dev->dev,
				"IOB bus %s to page out of range access error\n",
				ग_लिखो ? "write" : "read");
		अगर (regmap_ग_लिखो(ctx->edac->rb_map, RBEIR, 0))
			वापस;
		अगर (regmap_ग_लिखो(ctx->edac->rb_map, RBCSR, 0))
			वापस;
	पूर्ण
rb_skip:

	/* IOB Bridge agent transaction error पूर्णांकerrupt */
	reg = पढ़ोl(ctx->dev_csr + IOBBATRANSERRINTSTS);
	अगर (!reg)
		वापस;

	dev_err(edac_dev->dev, "IOB bridge agent (BA) transaction error\n");
	अगर (reg & WRERR_RESP_MASK)
		dev_err(edac_dev->dev, "IOB BA write response error\n");
	अगर (reg & M_WRERR_RESP_MASK)
		dev_err(edac_dev->dev,
			"Multiple IOB BA write response error\n");
	अगर (reg & XGIC_POISONED_REQ_MASK)
		dev_err(edac_dev->dev, "IOB BA XGIC poisoned write error\n");
	अगर (reg & M_XGIC_POISONED_REQ_MASK)
		dev_err(edac_dev->dev,
			"Multiple IOB BA XGIC poisoned write error\n");
	अगर (reg & RBM_POISONED_REQ_MASK)
		dev_err(edac_dev->dev, "IOB BA RBM poisoned write error\n");
	अगर (reg & M_RBM_POISONED_REQ_MASK)
		dev_err(edac_dev->dev,
			"Multiple IOB BA RBM poisoned write error\n");
	अगर (reg & WDATA_CORRUPT_MASK)
		dev_err(edac_dev->dev, "IOB BA write error\n");
	अगर (reg & M_WDATA_CORRUPT_MASK)
		dev_err(edac_dev->dev, "Multiple IOB BA write error\n");
	अगर (reg & TRANS_CORRUPT_MASK)
		dev_err(edac_dev->dev, "IOB BA transaction error\n");
	अगर (reg & M_TRANS_CORRUPT_MASK)
		dev_err(edac_dev->dev, "Multiple IOB BA transaction error\n");
	अगर (reg & RIDRAM_CORRUPT_MASK)
		dev_err(edac_dev->dev,
			"IOB BA RDIDRAM read transaction ID error\n");
	अगर (reg & M_RIDRAM_CORRUPT_MASK)
		dev_err(edac_dev->dev,
			"Multiple IOB BA RDIDRAM read transaction ID error\n");
	अगर (reg & WIDRAM_CORRUPT_MASK)
		dev_err(edac_dev->dev,
			"IOB BA RDIDRAM write transaction ID error\n");
	अगर (reg & M_WIDRAM_CORRUPT_MASK)
		dev_err(edac_dev->dev,
			"Multiple IOB BA RDIDRAM write transaction ID error\n");
	अगर (reg & ILLEGAL_ACCESS_MASK)
		dev_err(edac_dev->dev,
			"IOB BA XGIC/RB illegal access error\n");
	अगर (reg & M_ILLEGAL_ACCESS_MASK)
		dev_err(edac_dev->dev,
			"Multiple IOB BA XGIC/RB illegal access error\n");

	err_addr_lo = पढ़ोl(ctx->dev_csr + IOBBATRANSERRREQINFOL);
	err_addr_hi = पढ़ोl(ctx->dev_csr + IOBBATRANSERRREQINFOH);
	dev_err(edac_dev->dev, "IOB BA %s access at 0x%02X.%08X (0x%08X)\n",
		REQTYPE_F2_RD(err_addr_hi) ? "read" : "write",
		ERRADDRH_F2_RD(err_addr_hi), err_addr_lo, err_addr_hi);
	अगर (reg & WRERR_RESP_MASK)
		dev_err(edac_dev->dev, "IOB BA requestor ID 0x%08X\n",
			पढ़ोl(ctx->dev_csr + IOBBATRANSERRCSWREQID));
	ग_लिखोl(reg, ctx->dev_csr + IOBBATRANSERRINTSTS);
पूर्ण

अटल व्योम xgene_edac_pa_report(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	u32 err_addr_lo;
	u32 err_addr_hi;
	u32 reg;

	/* IOB Processing agent transaction error पूर्णांकerrupt */
	reg = पढ़ोl(ctx->dev_csr + IOBPATRANSERRINTSTS);
	अगर (!reg)
		जाओ chk_iob_axi0;
	dev_err(edac_dev->dev, "IOB processing agent (PA) transaction error\n");
	अगर (reg & IOBPA_RDATA_CORRUPT_MASK)
		dev_err(edac_dev->dev, "IOB PA read data RAM error\n");
	अगर (reg & IOBPA_M_RDATA_CORRUPT_MASK)
		dev_err(edac_dev->dev,
			"Multiple IOB PA read data RAM error\n");
	अगर (reg & IOBPA_WDATA_CORRUPT_MASK)
		dev_err(edac_dev->dev, "IOB PA write data RAM error\n");
	अगर (reg & IOBPA_M_WDATA_CORRUPT_MASK)
		dev_err(edac_dev->dev,
			"Multiple IOB PA write data RAM error\n");
	अगर (reg & IOBPA_TRANS_CORRUPT_MASK)
		dev_err(edac_dev->dev, "IOB PA transaction error\n");
	अगर (reg & IOBPA_M_TRANS_CORRUPT_MASK)
		dev_err(edac_dev->dev, "Multiple IOB PA transaction error\n");
	अगर (reg & IOBPA_REQIDRAM_CORRUPT_MASK)
		dev_err(edac_dev->dev, "IOB PA transaction ID RAM error\n");
	अगर (reg & IOBPA_M_REQIDRAM_CORRUPT_MASK)
		dev_err(edac_dev->dev,
			"Multiple IOB PA transaction ID RAM error\n");
	ग_लिखोl(reg, ctx->dev_csr + IOBPATRANSERRINTSTS);

chk_iob_axi0:
	/* IOB AXI0 Error */
	reg = पढ़ोl(ctx->dev_csr + IOBAXIS0TRANSERRINTSTS);
	अगर (!reg)
		जाओ chk_iob_axi1;
	err_addr_lo = पढ़ोl(ctx->dev_csr + IOBAXIS0TRANSERRREQINFOL);
	err_addr_hi = पढ़ोl(ctx->dev_csr + IOBAXIS0TRANSERRREQINFOH);
	dev_err(edac_dev->dev,
		"%sAXI slave 0 illegal %s access @ 0x%02X.%08X (0x%08X)\n",
		reg & IOBAXIS0_M_ILLEGAL_ACCESS_MASK ? "Multiple " : "",
		REQTYPE_RD(err_addr_hi) ? "read" : "write",
		ERRADDRH_RD(err_addr_hi), err_addr_lo, err_addr_hi);
	ग_लिखोl(reg, ctx->dev_csr + IOBAXIS0TRANSERRINTSTS);

chk_iob_axi1:
	/* IOB AXI1 Error */
	reg = पढ़ोl(ctx->dev_csr + IOBAXIS1TRANSERRINTSTS);
	अगर (!reg)
		वापस;
	err_addr_lo = पढ़ोl(ctx->dev_csr + IOBAXIS1TRANSERRREQINFOL);
	err_addr_hi = पढ़ोl(ctx->dev_csr + IOBAXIS1TRANSERRREQINFOH);
	dev_err(edac_dev->dev,
		"%sAXI slave 1 illegal %s access @ 0x%02X.%08X (0x%08X)\n",
		reg & IOBAXIS0_M_ILLEGAL_ACCESS_MASK ? "Multiple " : "",
		REQTYPE_RD(err_addr_hi) ? "read" : "write",
		ERRADDRH_RD(err_addr_hi), err_addr_lo, err_addr_hi);
	ग_लिखोl(reg, ctx->dev_csr + IOBAXIS1TRANSERRINTSTS);
पूर्ण

अटल व्योम xgene_edac_soc_check(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	स्थिर अक्षर * स्थिर *soc_mem_err = शून्य;
	u32 pcp_hp_stat;
	u32 pcp_lp_stat;
	u32 reg;
	पूर्णांक i;

	xgene_edac_pcp_rd(ctx->edac, PCPHPERRINTSTS, &pcp_hp_stat);
	xgene_edac_pcp_rd(ctx->edac, PCPLPERRINTSTS, &pcp_lp_stat);
	xgene_edac_pcp_rd(ctx->edac, MEMERRINTSTS, &reg);
	अगर (!((pcp_hp_stat & (IOB_PA_ERR_MASK | IOB_BA_ERR_MASK |
			      IOB_XGIC_ERR_MASK | IOB_RB_ERR_MASK)) ||
	      (pcp_lp_stat & CSW_SWITCH_TRACE_ERR_MASK) || reg))
		वापस;

	अगर (pcp_hp_stat & IOB_XGIC_ERR_MASK)
		xgene_edac_iob_gic_report(edac_dev);

	अगर (pcp_hp_stat & (IOB_RB_ERR_MASK | IOB_BA_ERR_MASK))
		xgene_edac_rb_report(edac_dev);

	अगर (pcp_hp_stat & IOB_PA_ERR_MASK)
		xgene_edac_pa_report(edac_dev);

	अगर (pcp_lp_stat & CSW_SWITCH_TRACE_ERR_MASK) अणु
		dev_info(edac_dev->dev,
			 "CSW switch trace correctable memory parity error\n");
		edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);
	पूर्ण

	अगर (!reg)
		वापस;
	अगर (ctx->version == 1)
		soc_mem_err = soc_mem_err_v1;
	अगर (!soc_mem_err) अणु
		dev_err(edac_dev->dev, "SoC memory parity error 0x%08X\n",
			reg);
		edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
		वापस;
	पूर्ण
	क्रम (i = 0; i < 31; i++) अणु
		अगर (reg & (1 << i)) अणु
			dev_err(edac_dev->dev, "%s memory parity error\n",
				soc_mem_err[i]);
			edac_device_handle_ue(edac_dev, 0, 0,
					      edac_dev->ctl_name);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम xgene_edac_soc_hw_init(काष्ठा edac_device_ctl_info *edac_dev,
				   bool enable)
अणु
	काष्ठा xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;

	/* Enable SoC IP error पूर्णांकerrupt */
	अगर (edac_dev->op_state == OP_RUNNING_INTERRUPT) अणु
		अगर (enable) अणु
			xgene_edac_pcp_clrbits(ctx->edac, PCPHPERRINTMSK,
					       IOB_PA_ERR_MASK |
					       IOB_BA_ERR_MASK |
					       IOB_XGIC_ERR_MASK |
					       IOB_RB_ERR_MASK);
			xgene_edac_pcp_clrbits(ctx->edac, PCPLPERRINTMSK,
					       CSW_SWITCH_TRACE_ERR_MASK);
		पूर्ण अन्यथा अणु
			xgene_edac_pcp_setbits(ctx->edac, PCPHPERRINTMSK,
					       IOB_PA_ERR_MASK |
					       IOB_BA_ERR_MASK |
					       IOB_XGIC_ERR_MASK |
					       IOB_RB_ERR_MASK);
			xgene_edac_pcp_setbits(ctx->edac, PCPLPERRINTMSK,
					       CSW_SWITCH_TRACE_ERR_MASK);
		पूर्ण

		ग_लिखोl(enable ? 0x0 : 0xFFFFFFFF,
		       ctx->dev_csr + IOBAXIS0TRANSERRINTMSK);
		ग_लिखोl(enable ? 0x0 : 0xFFFFFFFF,
		       ctx->dev_csr + IOBAXIS1TRANSERRINTMSK);
		ग_लिखोl(enable ? 0x0 : 0xFFFFFFFF,
		       ctx->dev_csr + XGICTRANSERRINTMSK);

		xgene_edac_pcp_setbits(ctx->edac, MEMERRINTMSK,
				       enable ? 0x0 : 0xFFFFFFFF);
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_edac_soc_add(काष्ठा xgene_edac *edac, काष्ठा device_node *np,
			      पूर्णांक version)
अणु
	काष्ठा edac_device_ctl_info *edac_dev;
	काष्ठा xgene_edac_dev_ctx *ctx;
	व्योम __iomem *dev_csr;
	काष्ठा resource res;
	पूर्णांक edac_idx;
	पूर्णांक rc;

	अगर (!devres_खोलो_group(edac->dev, xgene_edac_soc_add, GFP_KERNEL))
		वापस -ENOMEM;

	rc = of_address_to_resource(np, 0, &res);
	अगर (rc < 0) अणु
		dev_err(edac->dev, "no SoC resource address\n");
		जाओ err_release_group;
	पूर्ण
	dev_csr = devm_ioremap_resource(edac->dev, &res);
	अगर (IS_ERR(dev_csr)) अणु
		dev_err(edac->dev,
			"devm_ioremap_resource failed for soc resource address\n");
		rc = PTR_ERR(dev_csr);
		जाओ err_release_group;
	पूर्ण

	edac_idx = edac_device_alloc_index();
	edac_dev = edac_device_alloc_ctl_info(माप(*ctx),
					      "SOC", 1, "SOC", 1, 2, शून्य, 0,
					      edac_idx);
	अगर (!edac_dev) अणु
		rc = -ENOMEM;
		जाओ err_release_group;
	पूर्ण

	ctx = edac_dev->pvt_info;
	ctx->dev_csr = dev_csr;
	ctx->name = "xgene_soc_err";
	ctx->edac_idx = edac_idx;
	ctx->edac = edac;
	ctx->edac_dev = edac_dev;
	ctx->ddev = *edac->dev;
	ctx->version = version;
	edac_dev->dev = &ctx->ddev;
	edac_dev->ctl_name = ctx->name;
	edac_dev->dev_name = ctx->name;
	edac_dev->mod_name = EDAC_MOD_STR;

	अगर (edac_op_state == EDAC_OPSTATE_POLL)
		edac_dev->edac_check = xgene_edac_soc_check;

	rc = edac_device_add_device(edac_dev);
	अगर (rc > 0) अणु
		dev_err(edac->dev, "failed edac_device_add_device()\n");
		rc = -ENOMEM;
		जाओ err_ctl_मुक्त;
	पूर्ण

	अगर (edac_op_state == EDAC_OPSTATE_INT)
		edac_dev->op_state = OP_RUNNING_INTERRUPT;

	list_add(&ctx->next, &edac->socs);

	xgene_edac_soc_hw_init(edac_dev, 1);

	devres_हटाओ_group(edac->dev, xgene_edac_soc_add);

	dev_info(edac->dev, "X-Gene EDAC SoC registered\n");

	वापस 0;

err_ctl_मुक्त:
	edac_device_मुक्त_ctl_info(edac_dev);
err_release_group:
	devres_release_group(edac->dev, xgene_edac_soc_add);
	वापस rc;
पूर्ण

अटल पूर्णांक xgene_edac_soc_हटाओ(काष्ठा xgene_edac_dev_ctx *soc)
अणु
	काष्ठा edac_device_ctl_info *edac_dev = soc->edac_dev;

	xgene_edac_soc_hw_init(edac_dev, 0);
	edac_device_del_device(soc->edac->dev);
	edac_device_मुक्त_ctl_info(edac_dev);
	वापस 0;
पूर्ण

अटल irqवापस_t xgene_edac_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xgene_edac *ctx = dev_id;
	काष्ठा xgene_edac_pmd_ctx *pmd;
	काष्ठा xgene_edac_dev_ctx *node;
	अचिन्हित पूर्णांक pcp_hp_stat;
	अचिन्हित पूर्णांक pcp_lp_stat;

	xgene_edac_pcp_rd(ctx, PCPHPERRINTSTS, &pcp_hp_stat);
	xgene_edac_pcp_rd(ctx, PCPLPERRINTSTS, &pcp_lp_stat);
	अगर ((MCU_UNCORR_ERR_MASK & pcp_hp_stat) ||
	    (MCU_CTL_ERR_MASK & pcp_hp_stat) ||
	    (MCU_CORR_ERR_MASK & pcp_lp_stat)) अणु
		काष्ठा xgene_edac_mc_ctx *mcu;

		list_क्रम_each_entry(mcu, &ctx->mcus, next)
			xgene_edac_mc_check(mcu->mci);
	पूर्ण

	list_क्रम_each_entry(pmd, &ctx->pmds, next) अणु
		अगर ((PMD0_MERR_MASK << pmd->pmd) & pcp_hp_stat)
			xgene_edac_pmd_check(pmd->edac_dev);
	पूर्ण

	list_क्रम_each_entry(node, &ctx->l3s, next)
		xgene_edac_l3_check(node->edac_dev);

	list_क्रम_each_entry(node, &ctx->socs, next)
		xgene_edac_soc_check(node->edac_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xgene_edac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_edac *edac;
	काष्ठा device_node *child;
	काष्ठा resource *res;
	पूर्णांक rc;

	edac = devm_kzalloc(&pdev->dev, माप(*edac), GFP_KERNEL);
	अगर (!edac)
		वापस -ENOMEM;

	edac->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, edac);
	INIT_LIST_HEAD(&edac->mcus);
	INIT_LIST_HEAD(&edac->pmds);
	INIT_LIST_HEAD(&edac->l3s);
	INIT_LIST_HEAD(&edac->socs);
	spin_lock_init(&edac->lock);
	mutex_init(&edac->mc_lock);

	edac->csw_map = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							"regmap-csw");
	अगर (IS_ERR(edac->csw_map)) अणु
		dev_err(edac->dev, "unable to get syscon regmap csw\n");
		rc = PTR_ERR(edac->csw_map);
		जाओ out_err;
	पूर्ण

	edac->mcba_map = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							 "regmap-mcba");
	अगर (IS_ERR(edac->mcba_map)) अणु
		dev_err(edac->dev, "unable to get syscon regmap mcba\n");
		rc = PTR_ERR(edac->mcba_map);
		जाओ out_err;
	पूर्ण

	edac->mcbb_map = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							 "regmap-mcbb");
	अगर (IS_ERR(edac->mcbb_map)) अणु
		dev_err(edac->dev, "unable to get syscon regmap mcbb\n");
		rc = PTR_ERR(edac->mcbb_map);
		जाओ out_err;
	पूर्ण
	edac->efuse_map = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							  "regmap-efuse");
	अगर (IS_ERR(edac->efuse_map)) अणु
		dev_err(edac->dev, "unable to get syscon regmap efuse\n");
		rc = PTR_ERR(edac->efuse_map);
		जाओ out_err;
	पूर्ण

	/*
	 * NOTE: The रेजिस्टर bus resource is optional क्रम compatibility
	 * reason.
	 */
	edac->rb_map = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						       "regmap-rb");
	अगर (IS_ERR(edac->rb_map)) अणु
		dev_warn(edac->dev, "missing syscon regmap rb\n");
		edac->rb_map = शून्य;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	edac->pcp_csr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(edac->pcp_csr)) अणु
		dev_err(&pdev->dev, "no PCP resource address\n");
		rc = PTR_ERR(edac->pcp_csr);
		जाओ out_err;
	पूर्ण

	अगर (edac_op_state == EDAC_OPSTATE_INT) अणु
		पूर्णांक irq;
		पूर्णांक i;

		क्रम (i = 0; i < 3; i++) अणु
			irq = platक्रमm_get_irq_optional(pdev, i);
			अगर (irq < 0) अणु
				dev_err(&pdev->dev, "No IRQ resource\n");
				rc = -EINVAL;
				जाओ out_err;
			पूर्ण
			rc = devm_request_irq(&pdev->dev, irq,
					      xgene_edac_isr, IRQF_SHARED,
					      dev_name(&pdev->dev), edac);
			अगर (rc) अणु
				dev_err(&pdev->dev,
					"Could not request IRQ %d\n", irq);
				जाओ out_err;
			पूर्ण
		पूर्ण
	पूर्ण

	edac->dfs = edac_debugfs_create_dir(pdev->dev.kobj.name);

	क्रम_each_child_of_node(pdev->dev.of_node, child) अणु
		अगर (!of_device_is_available(child))
			जारी;
		अगर (of_device_is_compatible(child, "apm,xgene-edac-mc"))
			xgene_edac_mc_add(edac, child);
		अगर (of_device_is_compatible(child, "apm,xgene-edac-pmd"))
			xgene_edac_pmd_add(edac, child, 1);
		अगर (of_device_is_compatible(child, "apm,xgene-edac-pmd-v2"))
			xgene_edac_pmd_add(edac, child, 2);
		अगर (of_device_is_compatible(child, "apm,xgene-edac-l3"))
			xgene_edac_l3_add(edac, child, 1);
		अगर (of_device_is_compatible(child, "apm,xgene-edac-l3-v2"))
			xgene_edac_l3_add(edac, child, 2);
		अगर (of_device_is_compatible(child, "apm,xgene-edac-soc"))
			xgene_edac_soc_add(edac, child, 0);
		अगर (of_device_is_compatible(child, "apm,xgene-edac-soc-v1"))
			xgene_edac_soc_add(edac, child, 1);
	पूर्ण

	वापस 0;

out_err:
	वापस rc;
पूर्ण

अटल पूर्णांक xgene_edac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_edac *edac = dev_get_drvdata(&pdev->dev);
	काष्ठा xgene_edac_mc_ctx *mcu;
	काष्ठा xgene_edac_mc_ctx *temp_mcu;
	काष्ठा xgene_edac_pmd_ctx *pmd;
	काष्ठा xgene_edac_pmd_ctx *temp_pmd;
	काष्ठा xgene_edac_dev_ctx *node;
	काष्ठा xgene_edac_dev_ctx *temp_node;

	list_क्रम_each_entry_safe(mcu, temp_mcu, &edac->mcus, next)
		xgene_edac_mc_हटाओ(mcu);

	list_क्रम_each_entry_safe(pmd, temp_pmd, &edac->pmds, next)
		xgene_edac_pmd_हटाओ(pmd);

	list_क्रम_each_entry_safe(node, temp_node, &edac->l3s, next)
		xgene_edac_l3_हटाओ(node);

	list_क्रम_each_entry_safe(node, temp_node, &edac->socs, next)
		xgene_edac_soc_हटाओ(node);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xgene_edac_of_match[] = अणु
	अणु .compatible = "apm,xgene-edac" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xgene_edac_of_match);

अटल काष्ठा platक्रमm_driver xgene_edac_driver = अणु
	.probe = xgene_edac_probe,
	.हटाओ = xgene_edac_हटाओ,
	.driver = अणु
		.name = "xgene-edac",
		.of_match_table = xgene_edac_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init xgene_edac_init(व्योम)
अणु
	पूर्णांक rc;

	/* Make sure error reporting method is sane */
	चयन (edac_op_state) अणु
	हाल EDAC_OPSTATE_POLL:
	हाल EDAC_OPSTATE_INT:
		अवरोध;
	शेष:
		edac_op_state = EDAC_OPSTATE_INT;
		अवरोध;
	पूर्ण

	rc = platक्रमm_driver_रेजिस्टर(&xgene_edac_driver);
	अगर (rc) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MOD_STR,
			    "EDAC fails to register\n");
		जाओ reg_failed;
	पूर्ण

	वापस 0;

reg_failed:
	वापस rc;
पूर्ण
module_init(xgene_edac_init);

अटल व्योम __निकास xgene_edac_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&xgene_edac_driver);
पूर्ण
module_निकास(xgene_edac_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Feng Kan <fkan@apm.com>");
MODULE_DESCRIPTION("APM X-Gene EDAC driver");
module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state,
		 "EDAC error reporting state: 0=Poll, 2=Interrupt");
