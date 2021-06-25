<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Bluefield-specअगरic EDAC driver.
 *
 * Copyright (c) 2019 Mellanox Technologies.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/edac.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "edac_module.h"

#घोषणा DRIVER_NAME		"bluefield-edac"

/*
 * Mellanox BlueField EMI (External Memory Interface) रेजिस्टर definitions.
 */

#घोषणा MLXBF_ECC_CNT 0x340
#घोषणा MLXBF_ECC_CNT__SERR_CNT GENMASK(15, 0)
#घोषणा MLXBF_ECC_CNT__DERR_CNT GENMASK(31, 16)

#घोषणा MLXBF_ECC_ERR 0x348
#घोषणा MLXBF_ECC_ERR__SECC BIT(0)
#घोषणा MLXBF_ECC_ERR__DECC BIT(16)

#घोषणा MLXBF_ECC_LATCH_SEL 0x354
#घोषणा MLXBF_ECC_LATCH_SEL__START BIT(24)

#घोषणा MLXBF_ERR_ADDR_0 0x358

#घोषणा MLXBF_ERR_ADDR_1 0x37c

#घोषणा MLXBF_SYNDROM 0x35c
#घोषणा MLXBF_SYNDROM__DERR BIT(0)
#घोषणा MLXBF_SYNDROM__SERR BIT(1)
#घोषणा MLXBF_SYNDROM__SYN GENMASK(25, 16)

#घोषणा MLXBF_ADD_INFO 0x364
#घोषणा MLXBF_ADD_INFO__ERR_PRANK GENMASK(9, 8)

#घोषणा MLXBF_EDAC_MAX_DIMM_PER_MC	2
#घोषणा MLXBF_EDAC_ERROR_GRAIN		8

/*
 * Request MLNX_SIP_GET_DIMM_INFO
 *
 * Retrieve inक्रमmation about DIMM on a certain slot.
 *
 * Call रेजिस्टर usage:
 * a0: MLNX_SIP_GET_DIMM_INFO
 * a1: (Memory controller index) << 16 | (Dimm index in memory controller)
 * a2-7: not used.
 *
 * Return status:
 * a0: MLXBF_DIMM_INFO defined below describing the DIMM.
 * a1-3: not used.
 */
#घोषणा MLNX_SIP_GET_DIMM_INFO		0x82000008

/* Format क्रम the SMC response about the memory inक्रमmation */
#घोषणा MLXBF_DIMM_INFO__SIZE_GB GENMASK_ULL(15, 0)
#घोषणा MLXBF_DIMM_INFO__IS_RDIMM BIT(16)
#घोषणा MLXBF_DIMM_INFO__IS_LRDIMM BIT(17)
#घोषणा MLXBF_DIMM_INFO__IS_NVDIMM BIT(18)
#घोषणा MLXBF_DIMM_INFO__RANKS GENMASK_ULL(23, 21)
#घोषणा MLXBF_DIMM_INFO__PACKAGE_X GENMASK_ULL(31, 24)

काष्ठा bluefield_edac_priv अणु
	पूर्णांक dimm_ranks[MLXBF_EDAC_MAX_DIMM_PER_MC];
	व्योम __iomem *emi_base;
	पूर्णांक dimm_per_mc;
पूर्ण;

अटल u64 smc_call1(u64 smc_op, u64 smc_arg)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(smc_op, smc_arg, 0, 0, 0, 0, 0, 0, &res);

	वापस res.a0;
पूर्ण

/*
 * Gather the ECC inक्रमmation from the External Memory Interface रेजिस्टरs
 * and report it to the edac handler.
 */
अटल व्योम bluefield_gather_report_ecc(काष्ठा mem_ctl_info *mci,
					पूर्णांक error_cnt,
					पूर्णांक is_single_ecc)
अणु
	काष्ठा bluefield_edac_priv *priv = mci->pvt_info;
	u32 dram_additional_info, err_prank, edea0, edea1;
	u32 ecc_latch_select, dram_syndrom, serr, derr, syndrom;
	क्रमागत hw_event_mc_err_type ecc_type;
	u64 ecc_dimm_addr;
	पूर्णांक ecc_dimm;

	ecc_type = is_single_ecc ? HW_EVENT_ERR_CORRECTED :
				   HW_EVENT_ERR_UNCORRECTED;

	/*
	 * Tell the External Memory Interface to populate the relevant
	 * रेजिस्टरs with inक्रमmation about the last ECC error occurrence.
	 */
	ecc_latch_select = MLXBF_ECC_LATCH_SEL__START;
	ग_लिखोl(ecc_latch_select, priv->emi_base + MLXBF_ECC_LATCH_SEL);

	/*
	 * Verअगरy that the ECC reported info in the रेजिस्टरs is of the
	 * same type as the one asked to report. If not, just report the
	 * error without the detailed inक्रमmation.
	 */
	dram_syndrom = पढ़ोl(priv->emi_base + MLXBF_SYNDROM);
	serr = FIELD_GET(MLXBF_SYNDROM__SERR, dram_syndrom);
	derr = FIELD_GET(MLXBF_SYNDROM__DERR, dram_syndrom);
	syndrom = FIELD_GET(MLXBF_SYNDROM__SYN, dram_syndrom);

	अगर ((is_single_ecc && !serr) || (!is_single_ecc && !derr)) अणु
		edac_mc_handle_error(ecc_type, mci, error_cnt, 0, 0, 0,
				     0, 0, -1, mci->ctl_name, "");
		वापस;
	पूर्ण

	dram_additional_info = पढ़ोl(priv->emi_base + MLXBF_ADD_INFO);
	err_prank = FIELD_GET(MLXBF_ADD_INFO__ERR_PRANK, dram_additional_info);

	ecc_dimm = (err_prank >= 2 && priv->dimm_ranks[0] <= 2) ? 1 : 0;

	edea0 = पढ़ोl(priv->emi_base + MLXBF_ERR_ADDR_0);
	edea1 = पढ़ोl(priv->emi_base + MLXBF_ERR_ADDR_1);

	ecc_dimm_addr = ((u64)edea1 << 32) | edea0;

	edac_mc_handle_error(ecc_type, mci, error_cnt,
			     PFN_DOWN(ecc_dimm_addr),
			     offset_in_page(ecc_dimm_addr),
			     syndrom, ecc_dimm, 0, 0, mci->ctl_name, "");
पूर्ण

अटल व्योम bluefield_edac_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा bluefield_edac_priv *priv = mci->pvt_info;
	u32 ecc_count, single_error_count, द्विगुन_error_count, ecc_error = 0;

	/*
	 * The memory controller might not be initialized by the firmware
	 * when there isn't memory, which may lead to bad रेजिस्टर पढ़ोings.
	 */
	अगर (mci->edac_cap == EDAC_FLAG_NONE)
		वापस;

	ecc_count = पढ़ोl(priv->emi_base + MLXBF_ECC_CNT);
	single_error_count = FIELD_GET(MLXBF_ECC_CNT__SERR_CNT, ecc_count);
	द्विगुन_error_count = FIELD_GET(MLXBF_ECC_CNT__DERR_CNT, ecc_count);

	अगर (single_error_count) अणु
		ecc_error |= MLXBF_ECC_ERR__SECC;

		bluefield_gather_report_ecc(mci, single_error_count, 1);
	पूर्ण

	अगर (द्विगुन_error_count) अणु
		ecc_error |= MLXBF_ECC_ERR__DECC;

		bluefield_gather_report_ecc(mci, द्विगुन_error_count, 0);
	पूर्ण

	/* Write to clear reported errors. */
	अगर (ecc_count)
		ग_लिखोl(ecc_error, priv->emi_base + MLXBF_ECC_ERR);
पूर्ण

/* Initialize the DIMMs inक्रमmation क्रम the given memory controller. */
अटल व्योम bluefield_edac_init_dimms(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा bluefield_edac_priv *priv = mci->pvt_info;
	पूर्णांक mem_ctrl_idx = mci->mc_idx;
	काष्ठा dimm_info *dimm;
	u64 smc_info, smc_arg;
	पूर्णांक is_empty = 1, i;

	क्रम (i = 0; i < priv->dimm_per_mc; i++) अणु
		dimm = mci->dimms[i];

		smc_arg = mem_ctrl_idx << 16 | i;
		smc_info = smc_call1(MLNX_SIP_GET_DIMM_INFO, smc_arg);

		अगर (!FIELD_GET(MLXBF_DIMM_INFO__SIZE_GB, smc_info)) अणु
			dimm->mtype = MEM_EMPTY;
			जारी;
		पूर्ण

		is_empty = 0;

		dimm->edac_mode = EDAC_SECDED;

		अगर (FIELD_GET(MLXBF_DIMM_INFO__IS_NVDIMM, smc_info))
			dimm->mtype = MEM_NVDIMM;
		अन्यथा अगर (FIELD_GET(MLXBF_DIMM_INFO__IS_LRDIMM, smc_info))
			dimm->mtype = MEM_LRDDR4;
		अन्यथा अगर (FIELD_GET(MLXBF_DIMM_INFO__IS_RDIMM, smc_info))
			dimm->mtype = MEM_RDDR4;
		अन्यथा
			dimm->mtype = MEM_DDR4;

		dimm->nr_pages =
			FIELD_GET(MLXBF_DIMM_INFO__SIZE_GB, smc_info) *
			(SZ_1G / PAGE_SIZE);
		dimm->grain = MLXBF_EDAC_ERROR_GRAIN;

		/* Mem controller क्रम BlueField only supports x4, x8 and x16 */
		चयन (FIELD_GET(MLXBF_DIMM_INFO__PACKAGE_X, smc_info)) अणु
		हाल 4:
			dimm->dtype = DEV_X4;
			अवरोध;
		हाल 8:
			dimm->dtype = DEV_X8;
			अवरोध;
		हाल 16:
			dimm->dtype = DEV_X16;
			अवरोध;
		शेष:
			dimm->dtype = DEV_UNKNOWN;
		पूर्ण

		priv->dimm_ranks[i] =
			FIELD_GET(MLXBF_DIMM_INFO__RANKS, smc_info);
	पूर्ण

	अगर (is_empty)
		mci->edac_cap = EDAC_FLAG_NONE;
	अन्यथा
		mci->edac_cap = EDAC_FLAG_SECDED;
पूर्ण

अटल पूर्णांक bluefield_edac_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bluefield_edac_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा edac_mc_layer layers[1];
	काष्ठा mem_ctl_info *mci;
	काष्ठा resource *emi_res;
	अचिन्हित पूर्णांक mc_idx, dimm_count;
	पूर्णांक rc, ret;

	/* Read the MSS (Memory SubSystem) index from ACPI table. */
	अगर (device_property_पढ़ो_u32(dev, "mss_number", &mc_idx)) अणु
		dev_warn(dev, "bf_edac: MSS number unknown\n");
		वापस -EINVAL;
	पूर्ण

	/* Read the DIMMs per MC from ACPI table. */
	अगर (device_property_पढ़ो_u32(dev, "dimm_per_mc", &dimm_count)) अणु
		dev_warn(dev, "bf_edac: DIMMs per MC unknown\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dimm_count > MLXBF_EDAC_MAX_DIMM_PER_MC) अणु
		dev_warn(dev, "bf_edac: DIMMs per MC not valid\n");
		वापस -EINVAL;
	पूर्ण

	emi_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!emi_res)
		वापस -EINVAL;

	layers[0].type = EDAC_MC_LAYER_SLOT;
	layers[0].size = dimm_count;
	layers[0].is_virt_csrow = true;

	mci = edac_mc_alloc(mc_idx, ARRAY_SIZE(layers), layers, माप(*priv));
	अगर (!mci)
		वापस -ENOMEM;

	priv = mci->pvt_info;

	priv->dimm_per_mc = dimm_count;
	priv->emi_base = devm_ioremap_resource(dev, emi_res);
	अगर (IS_ERR(priv->emi_base)) अणु
		dev_err(dev, "failed to map EMI IO resource\n");
		ret = PTR_ERR(priv->emi_base);
		जाओ err;
	पूर्ण

	mci->pdev = dev;
	mci->mtype_cap = MEM_FLAG_DDR4 | MEM_FLAG_RDDR4 |
			 MEM_FLAG_LRDDR4 | MEM_FLAG_NVDIMM;
	mci->edac_ctl_cap = EDAC_FLAG_SECDED;

	mci->mod_name = DRIVER_NAME;
	mci->ctl_name = "BlueField_Memory_Controller";
	mci->dev_name = dev_name(dev);
	mci->edac_check = bluefield_edac_check;

	/* Initialize mci with the actual populated DIMM inक्रमmation. */
	bluefield_edac_init_dimms(mci);

	platक्रमm_set_drvdata(pdev, mci);

	/* Register with EDAC core */
	rc = edac_mc_add_mc(mci);
	अगर (rc) अणु
		dev_err(dev, "failed to register with EDAC core\n");
		ret = rc;
		जाओ err;
	पूर्ण

	/* Only POLL mode supported so far. */
	edac_op_state = EDAC_OPSTATE_POLL;

	वापस 0;

err:
	edac_mc_मुक्त(mci);

	वापस ret;

पूर्ण

अटल पूर्णांक bluefield_edac_mc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mem_ctl_info *mci = platक्रमm_get_drvdata(pdev);

	edac_mc_del_mc(&pdev->dev);
	edac_mc_मुक्त(mci);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id bluefield_mc_acpi_ids[] = अणु
	अणु"MLNXBF08", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, bluefield_mc_acpi_ids);

अटल काष्ठा platक्रमm_driver bluefield_edac_mc_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.acpi_match_table = bluefield_mc_acpi_ids,
	पूर्ण,
	.probe = bluefield_edac_mc_probe,
	.हटाओ = bluefield_edac_mc_हटाओ,
पूर्ण;

module_platक्रमm_driver(bluefield_edac_mc_driver);

MODULE_DESCRIPTION("Mellanox BlueField memory edac driver");
MODULE_AUTHOR("Mellanox Technologies");
MODULE_LICENSE("GPL v2");
