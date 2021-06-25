<शैली गुरु>
/*
 * AMD 76x Memory Controller kernel module
 * (C) 2003 Linux Networx (http://lnxi.com)
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written by Thayne Harbaugh
 * Based on work by Dan Hollis <goemon at anime करोt net> and others.
 *	http://www.anime.net/~goemon/linux-ecc/
 *
 * $Id: edac_amd76x.c,v 1.4.2.5 2005/10/05 00:43:44 dsp_llnl Exp $
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/edac.h>
#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR	"amd76x_edac"

#घोषणा amd76x_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "amd76x", fmt, ##arg)

#घोषणा amd76x_mc_prपूर्णांकk(mci, level, fmt, arg...) \
	edac_mc_chipset_prपूर्णांकk(mci, level, "amd76x", fmt, ##arg)

#घोषणा AMD76X_NR_CSROWS 8
#घोषणा AMD76X_NR_DIMMS  4

/* AMD 76x रेजिस्टर addresses - device 0 function 0 - PCI bridge */

#घोषणा AMD76X_ECC_MODE_STATUS	0x48	/* Mode and status of ECC (32b)
					 *
					 * 31:16 reserved
					 * 15:14 SERR enabled: x1=ue 1x=ce
					 * 13    reserved
					 * 12    diag: disabled, enabled
					 * 11:10 mode: dis, EC, ECC, ECC+scrub
					 *  9:8  status: x1=ue 1x=ce
					 *  7:4  UE cs row
					 *  3:0  CE cs row
					 */

#घोषणा AMD76X_DRAM_MODE_STATUS	0x58	/* DRAM Mode and status (32b)
					 *
					 * 31:26 घड़ी disable 5 - 0
					 * 25    SDRAM init
					 * 24    reserved
					 * 23    mode रेजिस्टर service
					 * 22:21 suspend to RAM
					 * 20    burst refresh enable
					 * 19    refresh disable
					 * 18    reserved
					 * 17:16 cycles-per-refresh
					 * 15:8  reserved
					 *  7:0  x4 mode enable 7 - 0
					 */

#घोषणा AMD76X_MEM_BASE_ADDR	0xC0	/* Memory base address (8 x 32b)
					 *
					 * 31:23 chip-select base
					 * 22:16 reserved
					 * 15:7  chip-select mask
					 *  6:3  reserved
					 *  2:1  address mode
					 *  0    chip-select enable
					 */

काष्ठा amd76x_error_info अणु
	u32 ecc_mode_status;
पूर्ण;

क्रमागत amd76x_chips अणु
	AMD761 = 0,
	AMD762
पूर्ण;

काष्ठा amd76x_dev_info अणु
	स्थिर अक्षर *ctl_name;
पूर्ण;

अटल स्थिर काष्ठा amd76x_dev_info amd76x_devs[] = अणु
	[AMD761] = अणु
		.ctl_name = "AMD761"पूर्ण,
	[AMD762] = अणु
		.ctl_name = "AMD762"पूर्ण,
पूर्ण;

अटल काष्ठा edac_pci_ctl_info *amd76x_pci;

/**
 *	amd76x_get_error_info	-	fetch error inक्रमmation
 *	@mci: Memory controller
 *	@info: Info to fill in
 *
 *	Fetch and store the AMD76x ECC status. Clear pending status
 *	on the chip so that further errors will be reported
 */
अटल व्योम amd76x_get_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा amd76x_error_info *info)
अणु
	काष्ठा pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);
	pci_पढ़ो_config_dword(pdev, AMD76X_ECC_MODE_STATUS,
			&info->ecc_mode_status);

	अगर (info->ecc_mode_status & BIT(8))
		pci_ग_लिखो_bits32(pdev, AMD76X_ECC_MODE_STATUS,
				 (u32) BIT(8), (u32) BIT(8));

	अगर (info->ecc_mode_status & BIT(9))
		pci_ग_लिखो_bits32(pdev, AMD76X_ECC_MODE_STATUS,
				 (u32) BIT(9), (u32) BIT(9));
पूर्ण

/**
 *	amd76x_process_error_info	-	Error check
 *	@mci: Memory controller
 *	@info: Previously fetched inक्रमmation from chip
 *	@handle_errors: 1 अगर we should करो recovery
 *
 *	Process the chip state and decide अगर an error has occurred.
 *	A वापस of 1 indicates an error. Also अगर handle_errors is true
 *	then attempt to handle and clean up after the error
 */
अटल पूर्णांक amd76x_process_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा amd76x_error_info *info,
				पूर्णांक handle_errors)
अणु
	पूर्णांक error_found;
	u32 row;

	error_found = 0;

	/*
	 *      Check क्रम an uncorrectable error
	 */
	अगर (info->ecc_mode_status & BIT(8)) अणु
		error_found = 1;

		अगर (handle_errors) अणु
			row = (info->ecc_mode_status >> 4) & 0xf;
			edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
					     mci->csrows[row]->first_page, 0, 0,
					     row, 0, -1,
					     mci->ctl_name, "");
		पूर्ण
	पूर्ण

	/*
	 *      Check क्रम a correctable error
	 */
	अगर (info->ecc_mode_status & BIT(9)) अणु
		error_found = 1;

		अगर (handle_errors) अणु
			row = info->ecc_mode_status & 0xf;
			edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
					     mci->csrows[row]->first_page, 0, 0,
					     row, 0, -1,
					     mci->ctl_name, "");
		पूर्ण
	पूर्ण

	वापस error_found;
पूर्ण

/**
 *	amd76x_check	-	Poll the controller
 *	@mci: Memory controller
 *
 *	Called by the poll handlers this function पढ़ोs the status
 *	from the controller and checks क्रम errors.
 */
अटल व्योम amd76x_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा amd76x_error_info info;
	amd76x_get_error_info(mci, &info);
	amd76x_process_error_info(mci, &info, 1);
पूर्ण

अटल व्योम amd76x_init_csrows(काष्ठा mem_ctl_info *mci, काष्ठा pci_dev *pdev,
			क्रमागत edac_type edac_mode)
अणु
	काष्ठा csrow_info *csrow;
	काष्ठा dimm_info *dimm;
	u32 mba, mba_base, mba_mask, dms;
	पूर्णांक index;

	क्रम (index = 0; index < mci->nr_csrows; index++) अणु
		csrow = mci->csrows[index];
		dimm = csrow->channels[0]->dimm;

		/* find the DRAM Chip Select Base address and mask */
		pci_पढ़ो_config_dword(pdev,
				AMD76X_MEM_BASE_ADDR + (index * 4), &mba);

		अगर (!(mba & BIT(0)))
			जारी;

		mba_base = mba & 0xff800000UL;
		mba_mask = ((mba & 0xff80) << 16) | 0x7fffffUL;
		pci_पढ़ो_config_dword(pdev, AMD76X_DRAM_MODE_STATUS, &dms);
		csrow->first_page = mba_base >> PAGE_SHIFT;
		dimm->nr_pages = (mba_mask + 1) >> PAGE_SHIFT;
		csrow->last_page = csrow->first_page + dimm->nr_pages - 1;
		csrow->page_mask = mba_mask >> PAGE_SHIFT;
		dimm->grain = dimm->nr_pages << PAGE_SHIFT;
		dimm->mtype = MEM_RDDR;
		dimm->dtype = ((dms >> index) & 0x1) ? DEV_X4 : DEV_UNKNOWN;
		dimm->edac_mode = edac_mode;
	पूर्ण
पूर्ण

/**
 *	amd76x_probe1	-	Perक्रमm set up क्रम detected device
 *	@pdev; PCI device detected
 *	@dev_idx: Device type index
 *
 *	We have found an AMD76x and now need to set up the memory
 *	controller status reporting. We configure and set up the
 *	memory controller reporting and claim the device.
 */
अटल पूर्णांक amd76x_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	अटल स्थिर क्रमागत edac_type ems_modes[] = अणु
		EDAC_NONE,
		EDAC_EC,
		EDAC_SECDED,
		EDAC_SECDED
	पूर्ण;
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	u32 ems;
	u32 ems_mode;
	काष्ठा amd76x_error_info discard;

	edac_dbg(0, "\n");
	pci_पढ़ो_config_dword(pdev, AMD76X_ECC_MODE_STATUS, &ems);
	ems_mode = (ems >> 10) & 0x3;

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = AMD76X_NR_CSROWS;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = 1;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, 0);

	अगर (mci == शून्य)
		वापस -ENOMEM;

	edac_dbg(0, "mci = %p\n", mci);
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FLAG_RDDR;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_EC | EDAC_FLAG_SECDED;
	mci->edac_cap = ems_mode ?
		(EDAC_FLAG_EC | EDAC_FLAG_SECDED) : EDAC_FLAG_NONE;
	mci->mod_name = EDAC_MOD_STR;
	mci->ctl_name = amd76x_devs[dev_idx].ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = amd76x_check;
	mci->ctl_page_to_phys = शून्य;

	amd76x_init_csrows(mci, pdev, ems_modes[ems_mode]);
	amd76x_get_error_info(mci, &discard);	/* clear counters */

	/* Here we assume that we will never see multiple instances of this
	 * type of memory controller.  The ID is thereक्रमe hardcoded to 0.
	 */
	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(3, "failed edac_mc_add_mc()\n");
		जाओ fail;
	पूर्ण

	/* allocating generic PCI control info */
	amd76x_pci = edac_pci_create_generic_ctl(&pdev->dev, EDAC_MOD_STR);
	अगर (!amd76x_pci) अणु
		prपूर्णांकk(KERN_WARNING
			"%s(): Unable to create PCI control\n",
			__func__);
		prपूर्णांकk(KERN_WARNING
			"%s(): PCI error report via EDAC not setup\n",
			__func__);
	पूर्ण

	/* get this far and it's successful */
	edac_dbg(3, "success\n");
	वापस 0;

fail:
	edac_mc_मुक्त(mci);
	वापस -ENODEV;
पूर्ण

/* वापसs count (>= 0), or negative on error */
अटल पूर्णांक amd76x_init_one(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	edac_dbg(0, "\n");

	/* करोn't need to call pci_enable_device() */
	वापस amd76x_probe1(pdev, ent->driver_data);
पूर्ण

/**
 *	amd76x_हटाओ_one	-	driver shutकरोwn
 *	@pdev: PCI device being handed back
 *
 *	Called when the driver is unloaded. Find the matching mci
 *	काष्ठाure क्रम the device then delete the mci and मुक्त the
 *	resources.
 */
अटल व्योम amd76x_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;

	edac_dbg(0, "\n");

	अगर (amd76x_pci)
		edac_pci_release_generic_ctl(amd76x_pci);

	अगर ((mci = edac_mc_del_mc(&pdev->dev)) == शून्य)
		वापस;

	edac_mc_मुक्त(mci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id amd76x_pci_tbl[] = अणु
	अणु
	 PCI_VEND_DEV(AMD, FE_GATE_700C), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 AMD762पूर्ण,
	अणु
	 PCI_VEND_DEV(AMD, FE_GATE_700E), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 AMD761पूर्ण,
	अणु
	 0,
	 पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, amd76x_pci_tbl);

अटल काष्ठा pci_driver amd76x_driver = अणु
	.name = EDAC_MOD_STR,
	.probe = amd76x_init_one,
	.हटाओ = amd76x_हटाओ_one,
	.id_table = amd76x_pci_tbl,
पूर्ण;

अटल पूर्णांक __init amd76x_init(व्योम)
अणु
       /* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
       opstate_init();

	वापस pci_रेजिस्टर_driver(&amd76x_driver);
पूर्ण

अटल व्योम __निकास amd76x_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&amd76x_driver);
पूर्ण

module_init(amd76x_init);
module_निकास(amd76x_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Linux Networx (http://lnxi.com) Thayne Harbaugh");
MODULE_DESCRIPTION("MC support for AMD 76x memory controllers");

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
