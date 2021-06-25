<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* * CAAM control-plane driver backend
 * Controller-level driver, kernel property detection, initialization
 *
 * Copyright 2008-2012 Freescale Semiconductor, Inc.
 * Copyright 2018-2019 NXP
 */

#समावेश <linux/device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/fsl/mc.h>

#समावेश "compat.h"
#समावेश "debugfs.h"
#समावेश "regs.h"
#समावेश "intern.h"
#समावेश "jr.h"
#समावेश "desc_constr.h"
#समावेश "ctrl.h"

bool caam_dpaa2;
EXPORT_SYMBOL(caam_dpaa2);

#अगर_घोषित CONFIG_CAAM_QI
#समावेश "qi.h"
#पूर्ण_अगर

/*
 * Descriptor to instantiate RNG State Handle 0 in normal mode and
 * load the JDKEK, TDKEK and TDSK रेजिस्टरs
 */
अटल व्योम build_instantiation_desc(u32 *desc, पूर्णांक handle, पूर्णांक करो_sk)
अणु
	u32 *jump_cmd, op_flags;

	init_job_desc(desc, 0);

	op_flags = OP_TYPE_CLASS1_ALG | OP_ALG_ALGSEL_RNG |
			(handle << OP_ALG_AAI_SHIFT) | OP_ALG_AS_INIT |
			OP_ALG_PR_ON;

	/* INIT RNG in non-test mode */
	append_operation(desc, op_flags);

	अगर (!handle && करो_sk) अणु
		/*
		 * For SH0, Secure Keys must be generated as well
		 */

		/* रुको क्रम करोne */
		jump_cmd = append_jump(desc, JUMP_CLASS_CLASS1);
		set_jump_tgt_here(desc, jump_cmd);

		/*
		 * load 1 to clear written reg:
		 * resets the करोne पूर्णांकerrupt and वापसs the RNG to idle.
		 */
		append_load_imm_u32(desc, 1, LDST_SRCDST_WORD_CLRW);

		/* Initialize State Handle  */
		append_operation(desc, OP_TYPE_CLASS1_ALG | OP_ALG_ALGSEL_RNG |
				 OP_ALG_AAI_RNG4_SK);
	पूर्ण

	append_jump(desc, JUMP_CLASS_CLASS1 | JUMP_TYPE_HALT);
पूर्ण

/* Descriptor क्रम deinstantiation of State Handle 0 of the RNG block. */
अटल व्योम build_deinstantiation_desc(u32 *desc, पूर्णांक handle)
अणु
	init_job_desc(desc, 0);

	/* Uninstantiate State Handle 0 */
	append_operation(desc, OP_TYPE_CLASS1_ALG | OP_ALG_ALGSEL_RNG |
			 (handle << OP_ALG_AAI_SHIFT) | OP_ALG_AS_INITFINAL);

	append_jump(desc, JUMP_CLASS_CLASS1 | JUMP_TYPE_HALT);
पूर्ण

/*
 * run_descriptor_deco0 - runs a descriptor on DECO0, under direct control of
 *			  the software (no JR/QI used).
 * @ctrldev - poपूर्णांकer to device
 * @status - descriptor status, after being run
 *
 * Return: - 0 अगर no error occurred
 *	   - -ENODEV अगर the DECO couldn't be acquired
 *	   - -EAGAIN अगर an error occurred जबतक executing the descriptor
 */
अटल अंतरभूत पूर्णांक run_descriptor_deco0(काष्ठा device *ctrldev, u32 *desc,
					u32 *status)
अणु
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(ctrldev);
	काष्ठा caam_ctrl __iomem *ctrl = ctrlpriv->ctrl;
	काष्ठा caam_deco __iomem *deco = ctrlpriv->deco;
	अचिन्हित पूर्णांक समयout = 100000;
	u32 deco_dbg_reg, deco_state, flags;
	पूर्णांक i;


	अगर (ctrlpriv->virt_en == 1 ||
	    /*
	     * Apparently on i.MX8MअणुQ,M,N,Pपूर्ण it करोesn't matter अगर virt_en == 1
	     * and the following steps should be perक्रमmed regardless
	     */
	    of_machine_is_compatible("fsl,imx8mq") ||
	    of_machine_is_compatible("fsl,imx8mm") ||
	    of_machine_is_compatible("fsl,imx8mn") ||
	    of_machine_is_compatible("fsl,imx8mp")) अणु
		clrsetbits_32(&ctrl->deco_rsr, 0, DECORSR_JR0);

		जबतक (!(rd_reg32(&ctrl->deco_rsr) & DECORSR_VALID) &&
		       --समयout)
			cpu_relax();

		समयout = 100000;
	पूर्ण

	clrsetbits_32(&ctrl->deco_rq, 0, DECORR_RQD0ENABLE);

	जबतक (!(rd_reg32(&ctrl->deco_rq) & DECORR_DEN0) &&
								 --समयout)
		cpu_relax();

	अगर (!समयout) अणु
		dev_err(ctrldev, "failed to acquire DECO 0\n");
		clrsetbits_32(&ctrl->deco_rq, DECORR_RQD0ENABLE, 0);
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < desc_len(desc); i++)
		wr_reg32(&deco->descbuf[i], caam32_to_cpu(*(desc + i)));

	flags = DECO_JQCR_WHL;
	/*
	 * If the descriptor length is दीर्घer than 4 words, then the
	 * FOUR bit in JRCTRL रेजिस्टर must be set.
	 */
	अगर (desc_len(desc) >= 4)
		flags |= DECO_JQCR_FOUR;

	/* Inकाष्ठा the DECO to execute it */
	clrsetbits_32(&deco->jr_ctl_hi, 0, flags);

	समयout = 10000000;
	करो अणु
		deco_dbg_reg = rd_reg32(&deco->desc_dbg);

		अगर (ctrlpriv->era < 10)
			deco_state = (deco_dbg_reg & DESC_DBG_DECO_STAT_MASK) >>
				     DESC_DBG_DECO_STAT_SHIFT;
		अन्यथा
			deco_state = (rd_reg32(&deco->dbg_exec) &
				      DESC_DER_DECO_STAT_MASK) >>
				     DESC_DER_DECO_STAT_SHIFT;

		/*
		 * If an error occurred in the descriptor, then
		 * the DECO status field will be set to 0x0D
		 */
		अगर (deco_state == DECO_STAT_HOST_ERR)
			अवरोध;

		cpu_relax();
	पूर्ण जबतक ((deco_dbg_reg & DESC_DBG_DECO_STAT_VALID) && --समयout);

	*status = rd_reg32(&deco->op_status_hi) &
		  DECO_OP_STATUS_HI_ERR_MASK;

	अगर (ctrlpriv->virt_en == 1)
		clrsetbits_32(&ctrl->deco_rsr, DECORSR_JR0, 0);

	/* Mark the DECO as मुक्त */
	clrsetbits_32(&ctrl->deco_rq, DECORR_RQD0ENABLE, 0);

	अगर (!समयout)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

/*
 * deinstantiate_rng - builds and executes a descriptor on DECO0,
 *		       which deinitializes the RNG block.
 * @ctrldev - poपूर्णांकer to device
 * @state_handle_mask - biपंचांगask containing the instantiation status
 *			क्रम the RNG4 state handles which exist in
 *			the RNG4 block: 1 अगर it's been instantiated
 *
 * Return: - 0 अगर no error occurred
 *	   - -ENOMEM अगर there isn't enough memory to allocate the descriptor
 *	   - -ENODEV अगर DECO0 couldn't be acquired
 *	   - -EAGAIN अगर an error occurred when executing the descriptor
 */
अटल पूर्णांक deinstantiate_rng(काष्ठा device *ctrldev, पूर्णांक state_handle_mask)
अणु
	u32 *desc, status;
	पूर्णांक sh_idx, ret = 0;

	desc = kदो_स्मृति(CAAM_CMD_SZ * 3, GFP_KERNEL | GFP_DMA);
	अगर (!desc)
		वापस -ENOMEM;

	क्रम (sh_idx = 0; sh_idx < RNG4_MAX_HANDLES; sh_idx++) अणु
		/*
		 * If the corresponding bit is set, then it means the state
		 * handle was initialized by us, and thus it needs to be
		 * deinitialized as well
		 */
		अगर ((1 << sh_idx) & state_handle_mask) अणु
			/*
			 * Create the descriptor क्रम deinstantating this state
			 * handle
			 */
			build_deinstantiation_desc(desc, sh_idx);

			/* Try to run it through DECO0 */
			ret = run_descriptor_deco0(ctrldev, desc, &status);

			अगर (ret ||
			    (status && status != JRSTA_SSRC_JUMP_HALT_CC)) अणु
				dev_err(ctrldev,
					"Failed to deinstantiate RNG4 SH%d\n",
					sh_idx);
				अवरोध;
			पूर्ण
			dev_info(ctrldev, "Deinstantiated RNG4 SH%d\n", sh_idx);
		पूर्ण
	पूर्ण

	kमुक्त(desc);

	वापस ret;
पूर्ण

अटल व्योम devm_deinstantiate_rng(व्योम *data)
अणु
	काष्ठा device *ctrldev = data;
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(ctrldev);

	/*
	 * De-initialize RNG state handles initialized by this driver.
	 * In हाल of SoCs with Management Complex, RNG is managed by MC f/w.
	 */
	अगर (ctrlpriv->rng4_sh_init)
		deinstantiate_rng(ctrldev, ctrlpriv->rng4_sh_init);
पूर्ण

/*
 * instantiate_rng - builds and executes a descriptor on DECO0,
 *		     which initializes the RNG block.
 * @ctrldev - poपूर्णांकer to device
 * @state_handle_mask - biपंचांगask containing the instantiation status
 *			क्रम the RNG4 state handles which exist in
 *			the RNG4 block: 1 अगर it's been instantiated
 *			by an बाह्यal entry, 0 otherwise.
 * @gen_sk  - generate data to be loaded पूर्णांकo the JDKEK, TDKEK and TDSK;
 *	      Caution: this can be करोne only once; अगर the keys need to be
 *	      regenerated, a POR is required
 *
 * Return: - 0 अगर no error occurred
 *	   - -ENOMEM अगर there isn't enough memory to allocate the descriptor
 *	   - -ENODEV अगर DECO0 couldn't be acquired
 *	   - -EAGAIN अगर an error occurred when executing the descriptor
 *	      f.i. there was a RNG hardware error due to not "good enough"
 *	      entropy being acquired.
 */
अटल पूर्णांक instantiate_rng(काष्ठा device *ctrldev, पूर्णांक state_handle_mask,
			   पूर्णांक gen_sk)
अणु
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(ctrldev);
	काष्ठा caam_ctrl __iomem *ctrl;
	u32 *desc, status = 0, rdsta_val;
	पूर्णांक ret = 0, sh_idx;

	ctrl = (काष्ठा caam_ctrl __iomem *)ctrlpriv->ctrl;
	desc = kदो_स्मृति(CAAM_CMD_SZ * 7, GFP_KERNEL | GFP_DMA);
	अगर (!desc)
		वापस -ENOMEM;

	क्रम (sh_idx = 0; sh_idx < RNG4_MAX_HANDLES; sh_idx++) अणु
		स्थिर u32 rdsta_अगर = RDSTA_IF0 << sh_idx;
		स्थिर u32 rdsta_pr = RDSTA_PR0 << sh_idx;
		स्थिर u32 rdsta_mask = rdsta_अगर | rdsta_pr;
		/*
		 * If the corresponding bit is set, this state handle
		 * was initialized by somebody अन्यथा, so it's left alone.
		 */
		अगर (rdsta_अगर & state_handle_mask) अणु
			अगर (rdsta_pr & state_handle_mask)
				जारी;

			dev_info(ctrldev,
				 "RNG4 SH%d was previously instantiated without prediction resistance. Tearing it down\n",
				 sh_idx);

			ret = deinstantiate_rng(ctrldev, rdsta_अगर);
			अगर (ret)
				अवरोध;
		पूर्ण

		/* Create the descriptor क्रम instantiating RNG State Handle */
		build_instantiation_desc(desc, sh_idx, gen_sk);

		/* Try to run it through DECO0 */
		ret = run_descriptor_deco0(ctrldev, desc, &status);

		/*
		 * If ret is not 0, or descriptor status is not 0, then
		 * something went wrong. No need to try the next state
		 * handle (अगर available), bail out here.
		 * Also, अगर क्रम some reason, the State Handle didn't get
		 * instantiated although the descriptor has finished
		 * without any error (HW optimizations क्रम later
		 * CAAM eras), then try again.
		 */
		अगर (ret)
			अवरोध;

		rdsta_val = rd_reg32(&ctrl->r4tst[0].rdsta) & RDSTA_MASK;
		अगर ((status && status != JRSTA_SSRC_JUMP_HALT_CC) ||
		    (rdsta_val & rdsta_mask) != rdsta_mask) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण

		dev_info(ctrldev, "Instantiated RNG4 SH%d\n", sh_idx);
		/* Clear the contents beक्रमe recreating the descriptor */
		स_रखो(desc, 0x00, CAAM_CMD_SZ * 7);
	पूर्ण

	kमुक्त(desc);

	अगर (ret)
		वापस ret;

	वापस devm_add_action_or_reset(ctrldev, devm_deinstantiate_rng, ctrldev);
पूर्ण

/*
 * kick_trng - sets the various parameters क्रम enabling the initialization
 *	       of the RNG4 block in CAAM
 * @pdev - poपूर्णांकer to the platक्रमm device
 * @ent_delay - Defines the length (in प्रणाली घड़ीs) of each entropy sample.
 */
अटल व्योम kick_trng(काष्ठा platक्रमm_device *pdev, पूर्णांक ent_delay)
अणु
	काष्ठा device *ctrldev = &pdev->dev;
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(ctrldev);
	काष्ठा caam_ctrl __iomem *ctrl;
	काष्ठा rng4tst __iomem *r4tst;
	u32 val;

	ctrl = (काष्ठा caam_ctrl __iomem *)ctrlpriv->ctrl;
	r4tst = &ctrl->r4tst[0];

	/*
	 * Setting both RTMCTL:PRGM and RTMCTL:TRNG_ACC causes TRNG to
	 * properly invalidate the entropy in the entropy रेजिस्टर and
	 * क्रमce re-generation.
	 */
	clrsetbits_32(&r4tst->rपंचांगctl, 0, RTMCTL_PRGM | RTMCTL_ACC);

	/*
	 * Perक्रमmance-wise, it करोes not make sense to
	 * set the delay to a value that is lower
	 * than the last one that worked (i.e. the state handles
	 * were instantiated properly. Thus, instead of wasting
	 * समय trying to set the values controlling the sample
	 * frequency, the function simply वापसs.
	 */
	val = (rd_reg32(&r4tst->rtsdctl) & RTSDCTL_ENT_DLY_MASK)
	      >> RTSDCTL_ENT_DLY_SHIFT;
	अगर (ent_delay <= val)
		जाओ start_rng;

	val = rd_reg32(&r4tst->rtsdctl);
	val = (val & ~RTSDCTL_ENT_DLY_MASK) |
	      (ent_delay << RTSDCTL_ENT_DLY_SHIFT);
	wr_reg32(&r4tst->rtsdctl, val);
	/* min. freq. count, equal to 1/4 of the entropy sample length */
	wr_reg32(&r4tst->rtfrqmin, ent_delay >> 2);
	/* disable maximum frequency count */
	wr_reg32(&r4tst->rtfrqmax, RTFRQMAX_DISABLE);
	/* पढ़ो the control रेजिस्टर */
	val = rd_reg32(&r4tst->rपंचांगctl);
start_rng:
	/*
	 * select raw sampling in both entropy shअगरter
	 * and statistical checker; ; put RNG4 पूर्णांकo run mode
	 */
	clrsetbits_32(&r4tst->rपंचांगctl, RTMCTL_PRGM | RTMCTL_ACC,
		      RTMCTL_SAMP_MODE_RAW_ES_SC);
पूर्ण

अटल पूर्णांक caam_get_era_from_hw(काष्ठा caam_ctrl __iomem *ctrl)
अणु
	अटल स्थिर काष्ठा अणु
		u16 ip_id;
		u8 maj_rev;
		u8 era;
	पूर्ण id[] = अणु
		अणु0x0A10, 1, 1पूर्ण,
		अणु0x0A10, 2, 2पूर्ण,
		अणु0x0A12, 1, 3पूर्ण,
		अणु0x0A14, 1, 3पूर्ण,
		अणु0x0A14, 2, 4पूर्ण,
		अणु0x0A16, 1, 4पूर्ण,
		अणु0x0A10, 3, 4पूर्ण,
		अणु0x0A11, 1, 4पूर्ण,
		अणु0x0A18, 1, 4पूर्ण,
		अणु0x0A11, 2, 5पूर्ण,
		अणु0x0A12, 2, 5पूर्ण,
		अणु0x0A13, 1, 5पूर्ण,
		अणु0x0A1C, 1, 5पूर्ण
	पूर्ण;
	u32 ccbvid, id_ms;
	u8 maj_rev, era;
	u16 ip_id;
	पूर्णांक i;

	ccbvid = rd_reg32(&ctrl->perfmon.ccb_id);
	era = (ccbvid & CCBVID_ERA_MASK) >> CCBVID_ERA_SHIFT;
	अगर (era)	/* This is '0' prior to CAAM ERA-6 */
		वापस era;

	id_ms = rd_reg32(&ctrl->perfmon.caam_id_ms);
	ip_id = (id_ms & SECVID_MS_IPID_MASK) >> SECVID_MS_IPID_SHIFT;
	maj_rev = (id_ms & SECVID_MS_MAJ_REV_MASK) >> SECVID_MS_MAJ_REV_SHIFT;

	क्रम (i = 0; i < ARRAY_SIZE(id); i++)
		अगर (id[i].ip_id == ip_id && id[i].maj_rev == maj_rev)
			वापस id[i].era;

	वापस -ENOTSUPP;
पूर्ण

/**
 * caam_get_era() - Return the ERA of the SEC on SoC, based
 * on "sec-era" optional property in the DTS. This property is updated
 * by u-boot.
 * In हाल this property is not passed an attempt to retrieve the CAAM
 * era via रेजिस्टर पढ़ोs will be made.
 *
 * @ctrl:	controller region
 */
अटल पूर्णांक caam_get_era(काष्ठा caam_ctrl __iomem *ctrl)
अणु
	काष्ठा device_node *caam_node;
	पूर्णांक ret;
	u32 prop;

	caam_node = of_find_compatible_node(शून्य, शून्य, "fsl,sec-v4.0");
	ret = of_property_पढ़ो_u32(caam_node, "fsl,sec-era", &prop);
	of_node_put(caam_node);

	अगर (!ret)
		वापस prop;
	अन्यथा
		वापस caam_get_era_from_hw(ctrl);
पूर्ण

/*
 * ERRATA: imx6 devices (imx6D, imx6Q, imx6DL, imx6S, imx6DP and imx6QP)
 * have an issue wherein AXI bus transactions may not occur in the correct
 * order. This isn't a problem running single descriptors, but can be अगर
 * running multiple concurrent descriptors. Reworking the driver to throttle
 * to single requests is impractical, thus the workaround is to limit the AXI
 * pipeline to a depth of 1 (from it's शेष of 4) to preclude this situation
 * from occurring.
 */
अटल व्योम handle_imx6_err005766(u32 __iomem *mcr)
अणु
	अगर (of_machine_is_compatible("fsl,imx6q") ||
	    of_machine_is_compatible("fsl,imx6dl") ||
	    of_machine_is_compatible("fsl,imx6qp"))
		clrsetbits_32(mcr, MCFGR_AXIPIPE_MASK,
			      1 << MCFGR_AXIPIPE_SHIFT);
पूर्ण

अटल स्थिर काष्ठा of_device_id caam_match[] = अणु
	अणु
		.compatible = "fsl,sec-v4.0",
	पूर्ण,
	अणु
		.compatible = "fsl,sec4.0",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, caam_match);

काष्ठा caam_imx_data अणु
	स्थिर काष्ठा clk_bulk_data *clks;
	पूर्णांक num_clks;
पूर्ण;

अटल स्थिर काष्ठा clk_bulk_data caam_imx6_clks[] = अणु
	अणु .id = "ipg" पूर्ण,
	अणु .id = "mem" पूर्ण,
	अणु .id = "aclk" पूर्ण,
	अणु .id = "emi_slow" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा caam_imx_data caam_imx6_data = अणु
	.clks = caam_imx6_clks,
	.num_clks = ARRAY_SIZE(caam_imx6_clks),
पूर्ण;

अटल स्थिर काष्ठा clk_bulk_data caam_imx7_clks[] = अणु
	अणु .id = "ipg" पूर्ण,
	अणु .id = "aclk" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा caam_imx_data caam_imx7_data = अणु
	.clks = caam_imx7_clks,
	.num_clks = ARRAY_SIZE(caam_imx7_clks),
पूर्ण;

अटल स्थिर काष्ठा clk_bulk_data caam_imx6ul_clks[] = अणु
	अणु .id = "ipg" पूर्ण,
	अणु .id = "mem" पूर्ण,
	अणु .id = "aclk" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा caam_imx_data caam_imx6ul_data = अणु
	.clks = caam_imx6ul_clks,
	.num_clks = ARRAY_SIZE(caam_imx6ul_clks),
पूर्ण;

अटल स्थिर काष्ठा clk_bulk_data caam_vf610_clks[] = अणु
	अणु .id = "ipg" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा caam_imx_data caam_vf610_data = अणु
	.clks = caam_vf610_clks,
	.num_clks = ARRAY_SIZE(caam_vf610_clks),
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute caam_imx_soc_table[] = अणु
	अणु .soc_id = "i.MX6UL", .data = &caam_imx6ul_data पूर्ण,
	अणु .soc_id = "i.MX6*",  .data = &caam_imx6_data पूर्ण,
	अणु .soc_id = "i.MX7*",  .data = &caam_imx7_data पूर्ण,
	अणु .soc_id = "i.MX8M*", .data = &caam_imx7_data पूर्ण,
	अणु .soc_id = "VF*",     .data = &caam_vf610_data पूर्ण,
	अणु .family = "Freescale i.MX" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल व्योम disable_घड़ीs(व्योम *data)
अणु
	काष्ठा caam_drv_निजी *ctrlpriv = data;

	clk_bulk_disable_unprepare(ctrlpriv->num_clks, ctrlpriv->clks);
पूर्ण

अटल पूर्णांक init_घड़ीs(काष्ठा device *dev, स्थिर काष्ठा caam_imx_data *data)
अणु
	काष्ठा caam_drv_निजी *ctrlpriv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ctrlpriv->num_clks = data->num_clks;
	ctrlpriv->clks = devm_kmemdup(dev, data->clks,
				      data->num_clks * माप(data->clks[0]),
				      GFP_KERNEL);
	अगर (!ctrlpriv->clks)
		वापस -ENOMEM;

	ret = devm_clk_bulk_get(dev, ctrlpriv->num_clks, ctrlpriv->clks);
	अगर (ret) अणु
		dev_err(dev,
			"Failed to request all necessary clocks\n");
		वापस ret;
	पूर्ण

	ret = clk_bulk_prepare_enable(ctrlpriv->num_clks, ctrlpriv->clks);
	अगर (ret) अणु
		dev_err(dev,
			"Failed to prepare/enable all necessary clocks\n");
		वापस ret;
	पूर्ण

	वापस devm_add_action_or_reset(dev, disable_घड़ीs, ctrlpriv);
पूर्ण

अटल व्योम caam_हटाओ_debugfs(व्योम *root)
अणु
	debugfs_हटाओ_recursive(root);
पूर्ण

#अगर_घोषित CONFIG_FSL_MC_BUS
अटल bool check_version(काष्ठा fsl_mc_version *mc_version, u32 major,
			  u32 minor, u32 revision)
अणु
	अगर (mc_version->major > major)
		वापस true;

	अगर (mc_version->major == major) अणु
		अगर (mc_version->minor > minor)
			वापस true;

		अगर (mc_version->minor == minor &&
		    mc_version->revision > revision)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
#पूर्ण_अगर

/* Probe routine क्रम CAAM top (controller) level */
अटल पूर्णांक caam_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret, ring, gen_sk, ent_delay = RTSDCTL_ENT_DLY_MIN;
	u64 caam_id;
	स्थिर काष्ठा soc_device_attribute *imx_soc_match;
	काष्ठा device *dev;
	काष्ठा device_node *nprop, *np;
	काष्ठा caam_ctrl __iomem *ctrl;
	काष्ठा caam_drv_निजी *ctrlpriv;
	काष्ठा dentry *dfs_root;
	u32 scfgr, comp_params;
	u8 rng_vid;
	पूर्णांक pg_size;
	पूर्णांक BLOCK_OFFSET = 0;
	bool pr_support = false;

	ctrlpriv = devm_kzalloc(&pdev->dev, माप(*ctrlpriv), GFP_KERNEL);
	अगर (!ctrlpriv)
		वापस -ENOMEM;

	dev = &pdev->dev;
	dev_set_drvdata(dev, ctrlpriv);
	nprop = pdev->dev.of_node;

	imx_soc_match = soc_device_match(caam_imx_soc_table);
	caam_imx = (bool)imx_soc_match;

	अगर (imx_soc_match) अणु
		अगर (!imx_soc_match->data) अणु
			dev_err(dev, "No clock data provided for i.MX SoC");
			वापस -EINVAL;
		पूर्ण

		ret = init_घड़ीs(dev, imx_soc_match->data);
		अगर (ret)
			वापस ret;
	पूर्ण


	/* Get configuration properties from device tree */
	/* First, get रेजिस्टर page */
	ctrl = devm_of_iomap(dev, nprop, 0, शून्य);
	ret = PTR_ERR_OR_ZERO(ctrl);
	अगर (ret) अणु
		dev_err(dev, "caam: of_iomap() failed\n");
		वापस ret;
	पूर्ण

	caam_little_end = !(bool)(rd_reg32(&ctrl->perfmon.status) &
				  (CSTA_PLEND | CSTA_ALT_PLEND));
	comp_params = rd_reg32(&ctrl->perfmon.comp_parms_ms);
	अगर (comp_params & CTPR_MS_PS && rd_reg32(&ctrl->mcr) & MCFGR_LONG_PTR)
		caam_ptr_sz = माप(u64);
	अन्यथा
		caam_ptr_sz = माप(u32);
	caam_dpaa2 = !!(comp_params & CTPR_MS_DPAA2);
	ctrlpriv->qi_present = !!(comp_params & CTPR_MS_QI_MASK);

#अगर_घोषित CONFIG_CAAM_QI
	/* If (DPAA 1.x) QI present, check whether dependencies are available */
	अगर (ctrlpriv->qi_present && !caam_dpaa2) अणु
		ret = qman_is_probed();
		अगर (!ret) अणु
			वापस -EPROBE_DEFER;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			dev_err(dev, "failing probe due to qman probe error\n");
			वापस -ENODEV;
		पूर्ण

		ret = qman_portals_probed();
		अगर (!ret) अणु
			वापस -EPROBE_DEFER;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			dev_err(dev, "failing probe due to qman portals probe error\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Allocating the BLOCK_OFFSET based on the supported page size on
	 * the platक्रमm
	 */
	pg_size = (comp_params & CTPR_MS_PG_SZ_MASK) >> CTPR_MS_PG_SZ_SHIFT;
	अगर (pg_size == 0)
		BLOCK_OFFSET = PG_SIZE_4K;
	अन्यथा
		BLOCK_OFFSET = PG_SIZE_64K;

	ctrlpriv->ctrl = (काष्ठा caam_ctrl __iomem __क्रमce *)ctrl;
	ctrlpriv->assure = (काष्ठा caam_assurance __iomem __क्रमce *)
			   ((__क्रमce uपूर्णांक8_t *)ctrl +
			    BLOCK_OFFSET * ASSURE_BLOCK_NUMBER
			   );
	ctrlpriv->deco = (काष्ठा caam_deco __iomem __क्रमce *)
			 ((__क्रमce uपूर्णांक8_t *)ctrl +
			 BLOCK_OFFSET * DECO_BLOCK_NUMBER
			 );

	/* Get the IRQ of the controller (क्रम security violations only) */
	ctrlpriv->secvio_irq = irq_of_parse_and_map(nprop, 0);
	np = of_find_compatible_node(शून्य, शून्य, "fsl,qoriq-mc");
	ctrlpriv->mc_en = !!np;
	of_node_put(np);

#अगर_घोषित CONFIG_FSL_MC_BUS
	अगर (ctrlpriv->mc_en) अणु
		काष्ठा fsl_mc_version *mc_version;

		mc_version = fsl_mc_get_version();
		अगर (mc_version)
			pr_support = check_version(mc_version, 10, 20, 0);
		अन्यथा
			वापस -EPROBE_DEFER;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Enable DECO watchकरोgs and, अगर this is a PHYS_ADDR_T_64BIT kernel,
	 * दीर्घ poपूर्णांकers in master configuration रेजिस्टर.
	 * In हाल of SoCs with Management Complex, MC f/w perक्रमms
	 * the configuration.
	 */
	अगर (!ctrlpriv->mc_en)
		clrsetbits_32(&ctrl->mcr, MCFGR_AWCACHE_MASK,
			      MCFGR_AWCACHE_CACH | MCFGR_AWCACHE_BUFF |
			      MCFGR_WDENABLE | MCFGR_LARGE_BURST);

	handle_imx6_err005766(&ctrl->mcr);

	/*
	 *  Read the Compile Time parameters and SCFGR to determine
	 * अगर भवization is enabled क्रम this platक्रमm
	 */
	scfgr = rd_reg32(&ctrl->scfgr);

	ctrlpriv->virt_en = 0;
	अगर (comp_params & CTPR_MS_VIRT_EN_INCL) अणु
		/* VIRT_EN_INCL = 1 & VIRT_EN_POR = 1 or
		 * VIRT_EN_INCL = 1 & VIRT_EN_POR = 0 & SCFGR_VIRT_EN = 1
		 */
		अगर ((comp_params & CTPR_MS_VIRT_EN_POR) ||
		    (!(comp_params & CTPR_MS_VIRT_EN_POR) &&
		       (scfgr & SCFGR_VIRT_EN)))
				ctrlpriv->virt_en = 1;
	पूर्ण अन्यथा अणु
		/* VIRT_EN_INCL = 0 && VIRT_EN_POR_VALUE = 1 */
		अगर (comp_params & CTPR_MS_VIRT_EN_POR)
				ctrlpriv->virt_en = 1;
	पूर्ण

	अगर (ctrlpriv->virt_en == 1)
		clrsetbits_32(&ctrl->jrstart, 0, JRSTART_JR0_START |
			      JRSTART_JR1_START | JRSTART_JR2_START |
			      JRSTART_JR3_START);

	ret = dma_set_mask_and_coherent(dev, caam_get_dma_mask(dev));
	अगर (ret) अणु
		dev_err(dev, "dma_set_mask_and_coherent failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	ctrlpriv->era = caam_get_era(ctrl);
	ctrlpriv->करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);

	dfs_root = debugfs_create_dir(dev_name(dev), शून्य);
	अगर (IS_ENABLED(CONFIG_DEBUG_FS)) अणु
		ret = devm_add_action_or_reset(dev, caam_हटाओ_debugfs,
					       dfs_root);
		अगर (ret)
			वापस ret;
	पूर्ण

	caam_debugfs_init(ctrlpriv, dfs_root);

	/* Check to see अगर (DPAA 1.x) QI present. If so, enable */
	अगर (ctrlpriv->qi_present && !caam_dpaa2) अणु
		ctrlpriv->qi = (काष्ठा caam_queue_अगर __iomem __क्रमce *)
			       ((__क्रमce uपूर्णांक8_t *)ctrl +
				 BLOCK_OFFSET * QI_BLOCK_NUMBER
			       );
		/* This is all that's required to physically enable QI */
		wr_reg32(&ctrlpriv->qi->qi_control_lo, QICTL_DQEN);

		/* If QMAN driver is present, init CAAM-QI backend */
#अगर_घोषित CONFIG_CAAM_QI
		ret = caam_qi_init(pdev);
		अगर (ret)
			dev_err(dev, "caam qi i/f init failed: %d\n", ret);
#पूर्ण_अगर
	पूर्ण

	ring = 0;
	क्रम_each_available_child_of_node(nprop, np)
		अगर (of_device_is_compatible(np, "fsl,sec-v4.0-job-ring") ||
		    of_device_is_compatible(np, "fsl,sec4.0-job-ring")) अणु
			ctrlpriv->jr[ring] = (काष्ठा caam_job_ring __iomem __क्रमce *)
					     ((__क्रमce uपूर्णांक8_t *)ctrl +
					     (ring + JR_BLOCK_NUMBER) *
					      BLOCK_OFFSET
					     );
			ctrlpriv->total_jobrs++;
			ring++;
		पूर्ण

	/* If no QI and no rings specअगरied, quit and go home */
	अगर ((!ctrlpriv->qi_present) && (!ctrlpriv->total_jobrs)) अणु
		dev_err(dev, "no queues configured, terminating\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (ctrlpriv->era < 10)
		rng_vid = (rd_reg32(&ctrl->perfmon.cha_id_ls) &
			   CHA_ID_LS_RNG_MASK) >> CHA_ID_LS_RNG_SHIFT;
	अन्यथा
		rng_vid = (rd_reg32(&ctrl->vreg.rng) & CHA_VER_VID_MASK) >>
			   CHA_VER_VID_SHIFT;

	/*
	 * If SEC has RNG version >= 4 and RNG state handle has not been
	 * alपढ़ोy instantiated, करो RNG instantiation
	 * In हाल of SoCs with Management Complex, RNG is managed by MC f/w.
	 */
	अगर (!(ctrlpriv->mc_en && pr_support) && rng_vid >= 4) अणु
		ctrlpriv->rng4_sh_init =
			rd_reg32(&ctrl->r4tst[0].rdsta);
		/*
		 * If the secure keys (TDKEK, JDKEK, TDSK), were alपढ़ोy
		 * generated, संकेत this to the function that is instantiating
		 * the state handles. An error would occur अगर RNG4 attempts
		 * to regenerate these keys beक्रमe the next POR.
		 */
		gen_sk = ctrlpriv->rng4_sh_init & RDSTA_SKVN ? 0 : 1;
		ctrlpriv->rng4_sh_init &= RDSTA_MASK;
		करो अणु
			पूर्णांक inst_handles =
				rd_reg32(&ctrl->r4tst[0].rdsta) &
								RDSTA_MASK;
			/*
			 * If either SH were instantiated by somebody अन्यथा
			 * (e.g. u-boot) then it is assumed that the entropy
			 * parameters are properly set and thus the function
			 * setting these (kick_trng(...)) is skipped.
			 * Also, अगर a handle was instantiated, करो not change
			 * the TRNG parameters.
			 */
			अगर (!(ctrlpriv->rng4_sh_init || inst_handles)) अणु
				dev_info(dev,
					 "Entropy delay = %u\n",
					 ent_delay);
				kick_trng(pdev, ent_delay);
				ent_delay += 400;
			पूर्ण
			/*
			 * अगर instantiate_rng(...) fails, the loop will rerun
			 * and the kick_trng(...) function will modअगरy the
			 * upper and lower limits of the entropy sampling
			 * पूर्णांकerval, leading to a successful initialization of
			 * the RNG.
			 */
			ret = instantiate_rng(dev, inst_handles,
					      gen_sk);
			अगर (ret == -EAGAIN)
				/*
				 * अगर here, the loop will rerun,
				 * so करोn't hog the CPU
				 */
				cpu_relax();
		पूर्ण जबतक ((ret == -EAGAIN) && (ent_delay < RTSDCTL_ENT_DLY_MAX));
		अगर (ret) अणु
			dev_err(dev, "failed to instantiate RNG");
			वापस ret;
		पूर्ण
		/*
		 * Set handles initialized by this module as the complement of
		 * the alपढ़ोy initialized ones
		 */
		ctrlpriv->rng4_sh_init = ~ctrlpriv->rng4_sh_init & RDSTA_MASK;

		/* Enable RDB bit so that RNG works faster */
		clrsetbits_32(&ctrl->scfgr, 0, SCFGR_RDBENABLE);
	पूर्ण

	/* NOTE: RTIC detection ought to go here, around Si समय */

	caam_id = (u64)rd_reg32(&ctrl->perfmon.caam_id_ms) << 32 |
		  (u64)rd_reg32(&ctrl->perfmon.caam_id_ls);

	/* Report "alive" क्रम developer to see */
	dev_info(dev, "device ID = 0x%016llx (Era %d)\n", caam_id,
		 ctrlpriv->era);
	dev_info(dev, "job rings = %d, qi = %d\n",
		 ctrlpriv->total_jobrs, ctrlpriv->qi_present);

	ret = devm_of_platक्रमm_populate(dev);
	अगर (ret)
		dev_err(dev, "JR platform devices creation error\n");

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver caam_driver = अणु
	.driver = अणु
		.name = "caam",
		.of_match_table = caam_match,
	पूर्ण,
	.probe       = caam_probe,
पूर्ण;

module_platक्रमm_driver(caam_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FSL CAAM request backend");
MODULE_AUTHOR("Freescale Semiconductor - NMG/STC");
