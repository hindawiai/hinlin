<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2007 PA Semi, Inc
 *
 * Author: Egor Martovetsky <egor@pasemi.com>
 * Maपूर्णांकained by: Olof Johansson <olof@lixom.net>
 *
 * Driver क्रम the PWRficient onchip memory controllers
 */


#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/edac.h>
#समावेश "edac_module.h"

#घोषणा MODULE_NAME "pasemi_edac"

#घोषणा MCCFG_MCEN				0x300
#घोषणा   MCCFG_MCEN_MMC_EN			0x00000001
#घोषणा MCCFG_ERRCOR				0x388
#घोषणा   MCCFG_ERRCOR_RNK_FAIL_DET_EN		0x00000100
#घोषणा   MCCFG_ERRCOR_ECC_GEN_EN		0x00000010
#घोषणा   MCCFG_ERRCOR_ECC_CRR_EN		0x00000001
#घोषणा MCCFG_SCRUB				0x384
#घोषणा   MCCFG_SCRUB_RGLR_SCRB_EN		0x00000001
#घोषणा MCDEBUG_ERRCTL1				0x728
#घोषणा   MCDEBUG_ERRCTL1_RFL_LOG_EN		0x00080000
#घोषणा   MCDEBUG_ERRCTL1_MBE_LOG_EN		0x00040000
#घोषणा   MCDEBUG_ERRCTL1_SBE_LOG_EN		0x00020000
#घोषणा MCDEBUG_ERRSTA				0x730
#घोषणा   MCDEBUG_ERRSTA_RFL_STATUS		0x00000004
#घोषणा   MCDEBUG_ERRSTA_MBE_STATUS		0x00000002
#घोषणा   MCDEBUG_ERRSTA_SBE_STATUS		0x00000001
#घोषणा MCDEBUG_ERRCNT1				0x734
#घोषणा   MCDEBUG_ERRCNT1_SBE_CNT_OVRFLO	0x00000080
#घोषणा MCDEBUG_ERRLOG1A			0x738
#घोषणा   MCDEBUG_ERRLOG1A_MERR_TYPE_M		0x30000000
#घोषणा   MCDEBUG_ERRLOG1A_MERR_TYPE_NONE	0x00000000
#घोषणा   MCDEBUG_ERRLOG1A_MERR_TYPE_SBE	0x10000000
#घोषणा   MCDEBUG_ERRLOG1A_MERR_TYPE_MBE	0x20000000
#घोषणा   MCDEBUG_ERRLOG1A_MERR_TYPE_RFL	0x30000000
#घोषणा   MCDEBUG_ERRLOG1A_MERR_BA_M		0x00700000
#घोषणा   MCDEBUG_ERRLOG1A_MERR_BA_S		20
#घोषणा   MCDEBUG_ERRLOG1A_MERR_CS_M		0x00070000
#घोषणा   MCDEBUG_ERRLOG1A_MERR_CS_S		16
#घोषणा   MCDEBUG_ERRLOG1A_SYNDROME_M		0x0000ffff
#घोषणा MCDRAM_RANKCFG				0x114
#घोषणा   MCDRAM_RANKCFG_EN			0x00000001
#घोषणा   MCDRAM_RANKCFG_TYPE_SIZE_M		0x000001c0
#घोषणा   MCDRAM_RANKCFG_TYPE_SIZE_S		6

#घोषणा PASEMI_EDAC_NR_CSROWS			8
#घोषणा PASEMI_EDAC_NR_CHANS			1
#घोषणा PASEMI_EDAC_ERROR_GRAIN			64

अटल पूर्णांक last_page_in_mmc;
अटल पूर्णांक प्रणाली_mmc_id;


अटल u32 pasemi_edac_get_error_info(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(mci->pdev);
	u32 पंचांगp;

	pci_पढ़ो_config_dword(pdev, MCDEBUG_ERRSTA,
			      &पंचांगp);

	पंचांगp &= (MCDEBUG_ERRSTA_RFL_STATUS | MCDEBUG_ERRSTA_MBE_STATUS
		| MCDEBUG_ERRSTA_SBE_STATUS);

	अगर (पंचांगp) अणु
		अगर (पंचांगp & MCDEBUG_ERRSTA_SBE_STATUS)
			pci_ग_लिखो_config_dword(pdev, MCDEBUG_ERRCNT1,
					       MCDEBUG_ERRCNT1_SBE_CNT_OVRFLO);
		pci_ग_लिखो_config_dword(pdev, MCDEBUG_ERRSTA, पंचांगp);
	पूर्ण

	वापस पंचांगp;
पूर्ण

अटल व्योम pasemi_edac_process_error_info(काष्ठा mem_ctl_info *mci, u32 errsta)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(mci->pdev);
	u32 errlog1a;
	u32 cs;

	अगर (!errsta)
		वापस;

	pci_पढ़ो_config_dword(pdev, MCDEBUG_ERRLOG1A, &errlog1a);

	cs = (errlog1a & MCDEBUG_ERRLOG1A_MERR_CS_M) >>
		MCDEBUG_ERRLOG1A_MERR_CS_S;

	/* uncorrectable/multi-bit errors */
	अगर (errsta & (MCDEBUG_ERRSTA_MBE_STATUS |
		      MCDEBUG_ERRSTA_RFL_STATUS)) अणु
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     mci->csrows[cs]->first_page, 0, 0,
				     cs, 0, -1, mci->ctl_name, "");
	पूर्ण

	/* correctable/single-bit errors */
	अगर (errsta & MCDEBUG_ERRSTA_SBE_STATUS)
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
				     mci->csrows[cs]->first_page, 0, 0,
				     cs, 0, -1, mci->ctl_name, "");
पूर्ण

अटल व्योम pasemi_edac_check(काष्ठा mem_ctl_info *mci)
अणु
	u32 errsta;

	errsta = pasemi_edac_get_error_info(mci);
	अगर (errsta)
		pasemi_edac_process_error_info(mci, errsta);
पूर्ण

अटल पूर्णांक pasemi_edac_init_csrows(काष्ठा mem_ctl_info *mci,
				   काष्ठा pci_dev *pdev,
				   क्रमागत edac_type edac_mode)
अणु
	काष्ठा csrow_info *csrow;
	काष्ठा dimm_info *dimm;
	u32 rankcfg;
	पूर्णांक index;

	क्रम (index = 0; index < mci->nr_csrows; index++) अणु
		csrow = mci->csrows[index];
		dimm = csrow->channels[0]->dimm;

		pci_पढ़ो_config_dword(pdev,
				      MCDRAM_RANKCFG + (index * 12),
				      &rankcfg);

		अगर (!(rankcfg & MCDRAM_RANKCFG_EN))
			जारी;

		चयन ((rankcfg & MCDRAM_RANKCFG_TYPE_SIZE_M) >>
			MCDRAM_RANKCFG_TYPE_SIZE_S) अणु
		हाल 0:
			dimm->nr_pages = 128 << (20 - PAGE_SHIFT);
			अवरोध;
		हाल 1:
			dimm->nr_pages = 256 << (20 - PAGE_SHIFT);
			अवरोध;
		हाल 2:
		हाल 3:
			dimm->nr_pages = 512 << (20 - PAGE_SHIFT);
			अवरोध;
		हाल 4:
			dimm->nr_pages = 1024 << (20 - PAGE_SHIFT);
			अवरोध;
		हाल 5:
			dimm->nr_pages = 2048 << (20 - PAGE_SHIFT);
			अवरोध;
		शेष:
			edac_mc_prपूर्णांकk(mci, KERN_ERR,
				"Unrecognized Rank Config. rankcfg=%u\n",
				rankcfg);
			वापस -EINVAL;
		पूर्ण

		csrow->first_page = last_page_in_mmc;
		csrow->last_page = csrow->first_page + dimm->nr_pages - 1;
		last_page_in_mmc += dimm->nr_pages;
		csrow->page_mask = 0;
		dimm->grain = PASEMI_EDAC_ERROR_GRAIN;
		dimm->mtype = MEM_DDR;
		dimm->dtype = DEV_UNKNOWN;
		dimm->edac_mode = edac_mode;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pasemi_edac_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा mem_ctl_info *mci = शून्य;
	काष्ठा edac_mc_layer layers[2];
	u32 errctl1, errcor, scrub, mcen;

	pci_पढ़ो_config_dword(pdev, MCCFG_MCEN, &mcen);
	अगर (!(mcen & MCCFG_MCEN_MMC_EN))
		वापस -ENODEV;

	/*
	 * We should think about enabling other error detection later on
	 */

	pci_पढ़ो_config_dword(pdev, MCDEBUG_ERRCTL1, &errctl1);
	errctl1 |= MCDEBUG_ERRCTL1_SBE_LOG_EN |
		MCDEBUG_ERRCTL1_MBE_LOG_EN |
		MCDEBUG_ERRCTL1_RFL_LOG_EN;
	pci_ग_लिखो_config_dword(pdev, MCDEBUG_ERRCTL1, errctl1);

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = PASEMI_EDAC_NR_CSROWS;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = PASEMI_EDAC_NR_CHANS;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(प्रणाली_mmc_id++, ARRAY_SIZE(layers), layers,
			    0);
	अगर (mci == शून्य)
		वापस -ENOMEM;

	pci_पढ़ो_config_dword(pdev, MCCFG_ERRCOR, &errcor);
	errcor |= MCCFG_ERRCOR_RNK_FAIL_DET_EN |
		MCCFG_ERRCOR_ECC_GEN_EN |
		MCCFG_ERRCOR_ECC_CRR_EN;

	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FLAG_DDR | MEM_FLAG_RDDR;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_EC | EDAC_FLAG_SECDED;
	mci->edac_cap = (errcor & MCCFG_ERRCOR_ECC_GEN_EN) ?
		((errcor & MCCFG_ERRCOR_ECC_CRR_EN) ?
		 (EDAC_FLAG_EC | EDAC_FLAG_SECDED) : EDAC_FLAG_EC) :
		EDAC_FLAG_NONE;
	mci->mod_name = MODULE_NAME;
	mci->dev_name = pci_name(pdev);
	mci->ctl_name = "pasemi,pwrficient-mc";
	mci->edac_check = pasemi_edac_check;
	mci->ctl_page_to_phys = शून्य;
	pci_पढ़ो_config_dword(pdev, MCCFG_SCRUB, &scrub);
	mci->scrub_cap = SCRUB_FLAG_HW_PROG | SCRUB_FLAG_HW_SRC;
	mci->scrub_mode =
		((errcor & MCCFG_ERRCOR_ECC_CRR_EN) ? SCRUB_FLAG_HW_SRC : 0) |
		((scrub & MCCFG_SCRUB_RGLR_SCRB_EN) ? SCRUB_FLAG_HW_PROG : 0);

	अगर (pasemi_edac_init_csrows(mci, pdev,
				    (mci->edac_cap & EDAC_FLAG_SECDED) ?
				    EDAC_SECDED :
				    ((mci->edac_cap & EDAC_FLAG_EC) ?
				     EDAC_EC : EDAC_NONE)))
		जाओ fail;

	/*
	 * Clear status
	 */
	pasemi_edac_get_error_info(mci);

	अगर (edac_mc_add_mc(mci))
		जाओ fail;

	/* get this far and it's successful */
	वापस 0;

fail:
	edac_mc_मुक्त(mci);
	वापस -ENODEV;
पूर्ण

अटल व्योम pasemi_edac_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci = edac_mc_del_mc(&pdev->dev);

	अगर (!mci)
		वापस;

	edac_mc_मुक्त(mci);
पूर्ण


अटल स्थिर काष्ठा pci_device_id pasemi_edac_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_PASEMI, 0xa00a) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pasemi_edac_pci_tbl);

अटल काष्ठा pci_driver pasemi_edac_driver = अणु
	.name = MODULE_NAME,
	.probe = pasemi_edac_probe,
	.हटाओ = pasemi_edac_हटाओ,
	.id_table = pasemi_edac_pci_tbl,
पूर्ण;

अटल पूर्णांक __init pasemi_edac_init(व्योम)
अणु
       /* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
       opstate_init();

	वापस pci_रेजिस्टर_driver(&pasemi_edac_driver);
पूर्ण

अटल व्योम __निकास pasemi_edac_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pasemi_edac_driver);
पूर्ण

module_init(pasemi_edac_init);
module_निकास(pasemi_edac_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Egor Martovetsky <egor@pasemi.com>");
MODULE_DESCRIPTION("MC support for PA Semi PWRficient memory controller");
module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");

