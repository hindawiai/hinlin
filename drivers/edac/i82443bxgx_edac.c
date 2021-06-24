<शैली गुरु>
/*
 * Intel 82443BX/GX (440BX/GX chipset) Memory Controller EDAC kernel
 * module (C) 2006 Tim Small
 *
 * This file may be distributed under the terms of the GNU General
 * Public License.
 *
 * Written by Tim Small <tim@buttersideup.com>, based on work by Linux
 * Networx, Thayne Harbaugh, Dan Hollis <goemon at anime करोt net> and
 * others.
 *
 * 440GX fix by Jason Uhlenkott <juhlenko@akamai.com>.
 *
 * Written with reference to 82443BX Host Bridge Datasheet:
 * http://करोwnload.पूर्णांकel.com/design/chipsets/datashts/29063301.pdf
 * references to this करोcument given in [].
 *
 * This module करोesn't support the 440LX, but it may be possible to
 * make it करो so (the 440LX's रेजिस्टर definitions are dअगरferent, but
 * not completely so - I haven't studied them in enough detail to know
 * how easy this would be).
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>


#समावेश <linux/edac.h>
#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR    "i82443bxgx_edac"

/* The 82443BX supports SDRAM, or EDO (EDO क्रम mobile only), "Memory
 * Size: 8 MB to 512 MB (1GB with Registered DIMMs) with eight memory
 * rows" "The 82443BX supports multiple-bit error detection and
 * single-bit error correction when ECC mode is enabled and
 * single/multi-bit error detection when correction is disabled.
 * During ग_लिखोs to the DRAM, the 82443BX generates ECC क्रम the data
 * on a QWord basis. Partial QWord ग_लिखोs require a पढ़ो-modअगरy-ग_लिखो
 * cycle when ECC is enabled."
*/

/* "Additionally, the 82443BX ensures that the data is corrected in
 * मुख्य memory so that accumulation of errors is prevented. Another
 * error within the same QWord would result in a द्विगुन-bit error
 * which is unrecoverable. This is known as hardware scrubbing since
 * it requires no software पूर्णांकervention to correct the data in memory."
 */

/* [Also see page 100 (section 4.3), "DRAM Interface"]
 * [Also see page 112 (section 4.6.1.4), ECC]
 */

#घोषणा I82443BXGX_NR_CSROWS 8
#घोषणा I82443BXGX_NR_CHANS  1
#घोषणा I82443BXGX_NR_DIMMS  4

/* 82443 PCI Device 0 */
#घोषणा I82443BXGX_NBXCFG 0x50	/* 32bit रेजिस्टर starting at this PCI
				 * config space offset */
#घोषणा I82443BXGX_NBXCFG_OFFSET_NON_ECCROW 24	/* Array of bits, zero अगर
						 * row is non-ECC */
#घोषणा I82443BXGX_NBXCFG_OFFSET_DRAM_FREQ 12	/* 2 bits,00=100MHz,10=66 MHz */

#घोषणा I82443BXGX_NBXCFG_OFFSET_DRAM_INTEGRITY 7	/* 2 bits:       */
#घोषणा I82443BXGX_NBXCFG_INTEGRITY_NONE   0x0	/* 00 = Non-ECC */
#घोषणा I82443BXGX_NBXCFG_INTEGRITY_EC     0x1	/* 01 = EC (only) */
#घोषणा I82443BXGX_NBXCFG_INTEGRITY_ECC    0x2	/* 10 = ECC */
#घोषणा I82443BXGX_NBXCFG_INTEGRITY_SCRUB  0x3	/* 11 = ECC + HW Scrub */

#घोषणा I82443BXGX_NBXCFG_OFFSET_ECC_DIAG_ENABLE  6

/* 82443 PCI Device 0 */
#घोषणा I82443BXGX_EAP   0x80	/* 32bit रेजिस्टर starting at this PCI
				 * config space offset, Error Address
				 * Poपूर्णांकer Register */
#घोषणा I82443BXGX_EAP_OFFSET_EAP  12	/* High 20 bits of error address */
#घोषणा I82443BXGX_EAP_OFFSET_MBE  BIT(1)	/* Err at EAP was multi-bit (W1TC) */
#घोषणा I82443BXGX_EAP_OFFSET_SBE  BIT(0)	/* Err at EAP was single-bit (W1TC) */

#घोषणा I82443BXGX_ERRCMD  0x90	/* 8bit रेजिस्टर starting at this PCI
				 * config space offset. */
#घोषणा I82443BXGX_ERRCMD_OFFSET_SERR_ON_MBE BIT(1)	/* 1 = enable */
#घोषणा I82443BXGX_ERRCMD_OFFSET_SERR_ON_SBE BIT(0)	/* 1 = enable */

#घोषणा I82443BXGX_ERRSTS  0x91	/* 16bit रेजिस्टर starting at this PCI
				 * config space offset. */
#घोषणा I82443BXGX_ERRSTS_OFFSET_MBFRE 5	/* 3 bits - first err row multibit */
#घोषणा I82443BXGX_ERRSTS_OFFSET_MEF   BIT(4)	/* 1 = MBE occurred */
#घोषणा I82443BXGX_ERRSTS_OFFSET_SBFRE 1	/* 3 bits - first err row singlebit */
#घोषणा I82443BXGX_ERRSTS_OFFSET_SEF   BIT(0)	/* 1 = SBE occurred */

#घोषणा I82443BXGX_DRAMC 0x57	/* 8bit रेजिस्टर starting at this PCI
				 * config space offset. */
#घोषणा I82443BXGX_DRAMC_OFFSET_DT 3	/* 2 bits, DRAM Type */
#घोषणा I82443BXGX_DRAMC_DRAM_IS_EDO 0	/* 00 = EDO */
#घोषणा I82443BXGX_DRAMC_DRAM_IS_SDRAM 1	/* 01 = SDRAM */
#घोषणा I82443BXGX_DRAMC_DRAM_IS_RSDRAM 2	/* 10 = Registered SDRAM */

#घोषणा I82443BXGX_DRB 0x60	/* 8x 8bit रेजिस्टरs starting at this PCI
				 * config space offset. */

/* FIXME - करोn't poll when ECC disabled? */

काष्ठा i82443bxgx_edacmc_error_info अणु
	u32 eap;
पूर्ण;

अटल काष्ठा edac_pci_ctl_info *i82443bxgx_pci;

अटल काष्ठा pci_dev *mci_pdev;	/* init dev: in हाल that AGP code has
					 * alपढ़ोy रेजिस्टरed driver
					 */

अटल पूर्णांक i82443bxgx_रेजिस्टरed = 1;

अटल व्योम i82443bxgx_edacmc_get_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा i82443bxgx_edacmc_error_info
				*info)
अणु
	काष्ठा pci_dev *pdev;
	pdev = to_pci_dev(mci->pdev);
	pci_पढ़ो_config_dword(pdev, I82443BXGX_EAP, &info->eap);
	अगर (info->eap & I82443BXGX_EAP_OFFSET_SBE)
		/* Clear error to allow next error to be reported [p.61] */
		pci_ग_लिखो_bits32(pdev, I82443BXGX_EAP,
				 I82443BXGX_EAP_OFFSET_SBE,
				 I82443BXGX_EAP_OFFSET_SBE);

	अगर (info->eap & I82443BXGX_EAP_OFFSET_MBE)
		/* Clear error to allow next error to be reported [p.61] */
		pci_ग_लिखो_bits32(pdev, I82443BXGX_EAP,
				 I82443BXGX_EAP_OFFSET_MBE,
				 I82443BXGX_EAP_OFFSET_MBE);
पूर्ण

अटल पूर्णांक i82443bxgx_edacmc_process_error_info(काष्ठा mem_ctl_info *mci,
						काष्ठा
						i82443bxgx_edacmc_error_info
						*info, पूर्णांक handle_errors)
अणु
	पूर्णांक error_found = 0;
	u32 eapaddr, page, pageoffset;

	/* bits 30:12 hold the 4kb block in which the error occurred
	 * [p.61] */
	eapaddr = (info->eap & 0xfffff000);
	page = eapaddr >> PAGE_SHIFT;
	pageoffset = eapaddr - (page << PAGE_SHIFT);

	अगर (info->eap & I82443BXGX_EAP_OFFSET_SBE) अणु
		error_found = 1;
		अगर (handle_errors)
			edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
					     page, pageoffset, 0,
					     edac_mc_find_csrow_by_page(mci, page),
					     0, -1, mci->ctl_name, "");
	पूर्ण

	अगर (info->eap & I82443BXGX_EAP_OFFSET_MBE) अणु
		error_found = 1;
		अगर (handle_errors)
			edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
					     page, pageoffset, 0,
					     edac_mc_find_csrow_by_page(mci, page),
					     0, -1, mci->ctl_name, "");
	पूर्ण

	वापस error_found;
पूर्ण

अटल व्योम i82443bxgx_edacmc_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i82443bxgx_edacmc_error_info info;

	i82443bxgx_edacmc_get_error_info(mci, &info);
	i82443bxgx_edacmc_process_error_info(mci, &info, 1);
पूर्ण

अटल व्योम i82443bxgx_init_csrows(काष्ठा mem_ctl_info *mci,
				काष्ठा pci_dev *pdev,
				क्रमागत edac_type edac_mode,
				क्रमागत mem_type mtype)
अणु
	काष्ठा csrow_info *csrow;
	काष्ठा dimm_info *dimm;
	पूर्णांक index;
	u8 drbar, dramc;
	u32 row_base, row_high_limit, row_high_limit_last;

	pci_पढ़ो_config_byte(pdev, I82443BXGX_DRAMC, &dramc);
	row_high_limit_last = 0;
	क्रम (index = 0; index < mci->nr_csrows; index++) अणु
		csrow = mci->csrows[index];
		dimm = csrow->channels[0]->dimm;

		pci_पढ़ो_config_byte(pdev, I82443BXGX_DRB + index, &drbar);
		edac_dbg(1, "MC%d: Row=%d DRB = %#0x\n",
			 mci->mc_idx, index, drbar);
		row_high_limit = ((u32) drbar << 23);
		/* find the DRAM Chip Select Base address and mask */
		edac_dbg(1, "MC%d: Row=%d, Boundary Address=%#0x, Last = %#0x\n",
			 mci->mc_idx, index, row_high_limit,
			 row_high_limit_last);

		/* 440GX goes to 2GB, represented with a DRB of 0. */
		अगर (row_high_limit_last && !row_high_limit)
			row_high_limit = 1UL << 31;

		/* This row is empty [p.49] */
		अगर (row_high_limit == row_high_limit_last)
			जारी;
		row_base = row_high_limit_last;
		csrow->first_page = row_base >> PAGE_SHIFT;
		csrow->last_page = (row_high_limit >> PAGE_SHIFT) - 1;
		dimm->nr_pages = csrow->last_page - csrow->first_page + 1;
		/* EAP reports in 4kilobyte granularity [61] */
		dimm->grain = 1 << 12;
		dimm->mtype = mtype;
		/* I करोn't think 440BX can tell you device type? FIXME? */
		dimm->dtype = DEV_UNKNOWN;
		/* Mode is global to all rows on 440BX */
		dimm->edac_mode = edac_mode;
		row_high_limit_last = row_high_limit;
	पूर्ण
पूर्ण

अटल पूर्णांक i82443bxgx_edacmc_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	u8 dramc;
	u32 nbxcfg, ecc_mode;
	क्रमागत mem_type mtype;
	क्रमागत edac_type edac_mode;

	edac_dbg(0, "MC:\n");

	/* Something is really hosed अगर PCI config space पढ़ोs from
	 * the MC aren't working.
	 */
	अगर (pci_पढ़ो_config_dword(pdev, I82443BXGX_NBXCFG, &nbxcfg))
		वापस -EIO;

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = I82443BXGX_NR_CSROWS;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = I82443BXGX_NR_CHANS;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, 0);
	अगर (mci == शून्य)
		वापस -ENOMEM;

	edac_dbg(0, "MC: mci = %p\n", mci);
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FLAG_EDO | MEM_FLAG_SDR | MEM_FLAG_RDR;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_EC | EDAC_FLAG_SECDED;
	pci_पढ़ो_config_byte(pdev, I82443BXGX_DRAMC, &dramc);
	चयन ((dramc >> I82443BXGX_DRAMC_OFFSET_DT) & (BIT(0) | BIT(1))) अणु
	हाल I82443BXGX_DRAMC_DRAM_IS_EDO:
		mtype = MEM_EDO;
		अवरोध;
	हाल I82443BXGX_DRAMC_DRAM_IS_SDRAM:
		mtype = MEM_SDR;
		अवरोध;
	हाल I82443BXGX_DRAMC_DRAM_IS_RSDRAM:
		mtype = MEM_RDR;
		अवरोध;
	शेष:
		edac_dbg(0, "Unknown/reserved DRAM type value in DRAMC register!\n");
		mtype = -MEM_UNKNOWN;
	पूर्ण

	अगर ((mtype == MEM_SDR) || (mtype == MEM_RDR))
		mci->edac_cap = mci->edac_ctl_cap;
	अन्यथा
		mci->edac_cap = EDAC_FLAG_NONE;

	mci->scrub_cap = SCRUB_FLAG_HW_SRC;
	pci_पढ़ो_config_dword(pdev, I82443BXGX_NBXCFG, &nbxcfg);
	ecc_mode = ((nbxcfg >> I82443BXGX_NBXCFG_OFFSET_DRAM_INTEGRITY) &
		(BIT(0) | BIT(1)));

	mci->scrub_mode = (ecc_mode == I82443BXGX_NBXCFG_INTEGRITY_SCRUB)
		? SCRUB_HW_SRC : SCRUB_NONE;

	चयन (ecc_mode) अणु
	हाल I82443BXGX_NBXCFG_INTEGRITY_NONE:
		edac_mode = EDAC_NONE;
		अवरोध;
	हाल I82443BXGX_NBXCFG_INTEGRITY_EC:
		edac_mode = EDAC_EC;
		अवरोध;
	हाल I82443BXGX_NBXCFG_INTEGRITY_ECC:
	हाल I82443BXGX_NBXCFG_INTEGRITY_SCRUB:
		edac_mode = EDAC_SECDED;
		अवरोध;
	शेष:
		edac_dbg(0, "Unknown/reserved ECC state in NBXCFG register!\n");
		edac_mode = EDAC_UNKNOWN;
		अवरोध;
	पूर्ण

	i82443bxgx_init_csrows(mci, pdev, edac_mode, mtype);

	/* Many BIOSes करोn't clear error flags on boot, so करो this
	 * here, or we get "phantom" errors occurring at module-load
	 * समय. */
	pci_ग_लिखो_bits32(pdev, I82443BXGX_EAP,
			(I82443BXGX_EAP_OFFSET_SBE |
				I82443BXGX_EAP_OFFSET_MBE),
			(I82443BXGX_EAP_OFFSET_SBE |
				I82443BXGX_EAP_OFFSET_MBE));

	mci->mod_name = EDAC_MOD_STR;
	mci->ctl_name = "I82443BXGX";
	mci->dev_name = pci_name(pdev);
	mci->edac_check = i82443bxgx_edacmc_check;
	mci->ctl_page_to_phys = शून्य;

	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(3, "failed edac_mc_add_mc()\n");
		जाओ fail;
	पूर्ण

	/* allocating generic PCI control info */
	i82443bxgx_pci = edac_pci_create_generic_ctl(&pdev->dev, EDAC_MOD_STR);
	अगर (!i82443bxgx_pci) अणु
		prपूर्णांकk(KERN_WARNING
			"%s(): Unable to create PCI control\n",
			__func__);
		prपूर्णांकk(KERN_WARNING
			"%s(): PCI error report via EDAC not setup\n",
			__func__);
	पूर्ण

	edac_dbg(3, "MC: success\n");
	वापस 0;

fail:
	edac_mc_मुक्त(mci);
	वापस -ENODEV;
पूर्ण

/* वापसs count (>= 0), or negative on error */
अटल पूर्णांक i82443bxgx_edacmc_init_one(काष्ठा pci_dev *pdev,
				      स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rc;

	edac_dbg(0, "MC:\n");

	/* करोn't need to call pci_enable_device() */
	rc = i82443bxgx_edacmc_probe1(pdev, ent->driver_data);

	अगर (mci_pdev == शून्य)
		mci_pdev = pci_dev_get(pdev);

	वापस rc;
पूर्ण

अटल व्योम i82443bxgx_edacmc_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;

	edac_dbg(0, "\n");

	अगर (i82443bxgx_pci)
		edac_pci_release_generic_ctl(i82443bxgx_pci);

	अगर ((mci = edac_mc_del_mc(&pdev->dev)) == शून्य)
		वापस;

	edac_mc_मुक्त(mci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id i82443bxgx_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82443BX_0)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82443BX_2)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82443GX_0)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82443GX_2)पूर्ण,
	अणु0,पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, i82443bxgx_pci_tbl);

अटल काष्ठा pci_driver i82443bxgx_edacmc_driver = अणु
	.name = EDAC_MOD_STR,
	.probe = i82443bxgx_edacmc_init_one,
	.हटाओ = i82443bxgx_edacmc_हटाओ_one,
	.id_table = i82443bxgx_pci_tbl,
पूर्ण;

अटल पूर्णांक __init i82443bxgx_edacmc_init(व्योम)
अणु
	पूर्णांक pci_rc;
       /* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
       opstate_init();

	pci_rc = pci_रेजिस्टर_driver(&i82443bxgx_edacmc_driver);
	अगर (pci_rc < 0)
		जाओ fail0;

	अगर (mci_pdev == शून्य) अणु
		स्थिर काष्ठा pci_device_id *id = &i82443bxgx_pci_tbl[0];
		पूर्णांक i = 0;
		i82443bxgx_रेजिस्टरed = 0;

		जबतक (mci_pdev == शून्य && id->venकरोr != 0) अणु
			mci_pdev = pci_get_device(id->venकरोr,
					id->device, शून्य);
			i++;
			id = &i82443bxgx_pci_tbl[i];
		पूर्ण
		अगर (!mci_pdev) अणु
			edac_dbg(0, "i82443bxgx pci_get_device fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण

		pci_rc = i82443bxgx_edacmc_init_one(mci_pdev, i82443bxgx_pci_tbl);

		अगर (pci_rc < 0) अणु
			edac_dbg(0, "i82443bxgx init fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण
	पूर्ण

	वापस 0;

fail1:
	pci_unरेजिस्टर_driver(&i82443bxgx_edacmc_driver);

fail0:
	pci_dev_put(mci_pdev);
	वापस pci_rc;
पूर्ण

अटल व्योम __निकास i82443bxgx_edacmc_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&i82443bxgx_edacmc_driver);

	अगर (!i82443bxgx_रेजिस्टरed)
		i82443bxgx_edacmc_हटाओ_one(mci_pdev);

	pci_dev_put(mci_pdev);
पूर्ण

module_init(i82443bxgx_edacmc_init);
module_निकास(i82443bxgx_edacmc_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tim Small <tim@buttersideup.com> - WPAD");
MODULE_DESCRIPTION("EDAC MC support for Intel 82443BX/GX memory controllers");

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
