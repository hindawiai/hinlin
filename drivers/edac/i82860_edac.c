<शैली गुरु>
/*
 * Intel 82860 Memory Controller kernel module
 * (C) 2005 Red Hat (http://www.redhat.com)
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written by Ben Woodard <woodard@redhat.com>
 * shamelessly copied from and based upon the edac_i82875 driver
 * by Thayne Harbaugh of Linux Networx. (http://lnxi.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/edac.h>
#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR	"i82860_edac"

#घोषणा i82860_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "i82860", fmt, ##arg)

#घोषणा i82860_mc_prपूर्णांकk(mci, level, fmt, arg...) \
	edac_mc_chipset_prपूर्णांकk(mci, level, "i82860", fmt, ##arg)

#अगर_अघोषित PCI_DEVICE_ID_INTEL_82860_0
#घोषणा PCI_DEVICE_ID_INTEL_82860_0	0x2531
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_82860_0 */

#घोषणा I82860_MCHCFG 0x50
#घोषणा I82860_GBA 0x60
#घोषणा I82860_GBA_MASK 0x7FF
#घोषणा I82860_GBA_SHIFT 24
#घोषणा I82860_ERRSTS 0xC8
#घोषणा I82860_EAP 0xE4
#घोषणा I82860_DERRCTL_STS 0xE2

क्रमागत i82860_chips अणु
	I82860 = 0,
पूर्ण;

काष्ठा i82860_dev_info अणु
	स्थिर अक्षर *ctl_name;
पूर्ण;

काष्ठा i82860_error_info अणु
	u16 errsts;
	u32 eap;
	u16 derrsyn;
	u16 errsts2;
पूर्ण;

अटल स्थिर काष्ठा i82860_dev_info i82860_devs[] = अणु
	[I82860] = अणु
		.ctl_name = "i82860"पूर्ण,
पूर्ण;

अटल काष्ठा pci_dev *mci_pdev;	/* init dev: in हाल that AGP code
					 * has alपढ़ोy रेजिस्टरed driver
					 */
अटल काष्ठा edac_pci_ctl_info *i82860_pci;

अटल व्योम i82860_get_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा i82860_error_info *info)
अणु
	काष्ठा pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because there is no atomic way to पढ़ो all the
	 * रेजिस्टरs at once and the रेजिस्टरs can transition from CE being
	 * overwritten by UE.
	 */
	pci_पढ़ो_config_word(pdev, I82860_ERRSTS, &info->errsts);
	pci_पढ़ो_config_dword(pdev, I82860_EAP, &info->eap);
	pci_पढ़ो_config_word(pdev, I82860_DERRCTL_STS, &info->derrsyn);
	pci_पढ़ो_config_word(pdev, I82860_ERRSTS, &info->errsts2);

	pci_ग_लिखो_bits16(pdev, I82860_ERRSTS, 0x0003, 0x0003);

	/*
	 * If the error is the same क्रम both पढ़ोs then the first set of पढ़ोs
	 * is valid.  If there is a change then there is a CE no info and the
	 * second set of पढ़ोs is valid and should be UE info.
	 */
	अगर (!(info->errsts2 & 0x0003))
		वापस;

	अगर ((info->errsts ^ info->errsts2) & 0x0003) अणु
		pci_पढ़ो_config_dword(pdev, I82860_EAP, &info->eap);
		pci_पढ़ो_config_word(pdev, I82860_DERRCTL_STS, &info->derrsyn);
	पूर्ण
पूर्ण

अटल पूर्णांक i82860_process_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा i82860_error_info *info,
				पूर्णांक handle_errors)
अणु
	काष्ठा dimm_info *dimm;
	पूर्णांक row;

	अगर (!(info->errsts2 & 0x0003))
		वापस 0;

	अगर (!handle_errors)
		वापस 1;

	अगर ((info->errsts ^ info->errsts2) & 0x0003) अणु
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, "UE overwrote CE", "");
		info->errsts = info->errsts2;
	पूर्ण

	info->eap >>= PAGE_SHIFT;
	row = edac_mc_find_csrow_by_page(mci, info->eap);
	dimm = mci->csrows[row]->channels[0]->dimm;

	अगर (info->errsts & 0x0002)
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     info->eap, 0, 0,
				     dimm->location[0], dimm->location[1], -1,
				     "i82860 UE", "");
	अन्यथा
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
				     info->eap, 0, info->derrsyn,
				     dimm->location[0], dimm->location[1], -1,
				     "i82860 CE", "");

	वापस 1;
पूर्ण

अटल व्योम i82860_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i82860_error_info info;

	i82860_get_error_info(mci, &info);
	i82860_process_error_info(mci, &info, 1);
पूर्ण

अटल व्योम i82860_init_csrows(काष्ठा mem_ctl_info *mci, काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ last_cumul_size;
	u16 mchcfg_ddim;	/* DRAM Data Integrity Mode 0=none, 2=edac */
	u16 value;
	u32 cumul_size;
	काष्ठा csrow_info *csrow;
	काष्ठा dimm_info *dimm;
	पूर्णांक index;

	pci_पढ़ो_config_word(pdev, I82860_MCHCFG, &mchcfg_ddim);
	mchcfg_ddim = mchcfg_ddim & 0x180;
	last_cumul_size = 0;

	/* The group row boundary (GRA) reg values are boundary address
	 * क्रम each DRAM row with a granularity of 16MB.  GRA regs are
	 * cumulative; thereक्रमe GRA15 will contain the total memory contained
	 * in all eight rows.
	 */
	क्रम (index = 0; index < mci->nr_csrows; index++) अणु
		csrow = mci->csrows[index];
		dimm = csrow->channels[0]->dimm;

		pci_पढ़ो_config_word(pdev, I82860_GBA + index * 2, &value);
		cumul_size = (value & I82860_GBA_MASK) <<
			(I82860_GBA_SHIFT - PAGE_SHIFT);
		edac_dbg(3, "(%d) cumul_size 0x%x\n", index, cumul_size);

		अगर (cumul_size == last_cumul_size)
			जारी;	/* not populated */

		csrow->first_page = last_cumul_size;
		csrow->last_page = cumul_size - 1;
		dimm->nr_pages = cumul_size - last_cumul_size;
		last_cumul_size = cumul_size;
		dimm->grain = 1 << 12;	/* I82860_EAP has 4KiB reolution */
		dimm->mtype = MEM_RMBS;
		dimm->dtype = DEV_UNKNOWN;
		dimm->edac_mode = mchcfg_ddim ? EDAC_SECDED : EDAC_NONE;
	पूर्ण
पूर्ण

अटल पूर्णांक i82860_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा i82860_error_info discard;

	/*
	 * RDRAM has channels but these करोn't map onto the csrow असलtraction.
	 * According with the datasheet, there are 2 Rambus channels, supporting
	 * up to 16 direct RDRAM devices.
	 * The device groups from the GRA रेजिस्टरs seem to map reasonably
	 * well onto the notion of a chip select row.
	 * There are 16 GRA रेजिस्टरs and since the name is associated with
	 * the channel and the GRA रेजिस्टरs map to physical devices so we are
	 * going to make 1 channel क्रम group.
	 */
	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = 2;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_SLOT;
	layers[1].size = 8;
	layers[1].is_virt_csrow = true;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, 0);
	अगर (!mci)
		वापस -ENOMEM;

	edac_dbg(3, "init mci\n");
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FLAG_DDR;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_SECDED;
	/* I"m not sure about this but I think that all RDRAM is SECDED */
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->mod_name = EDAC_MOD_STR;
	mci->ctl_name = i82860_devs[dev_idx].ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = i82860_check;
	mci->ctl_page_to_phys = शून्य;
	i82860_init_csrows(mci, pdev);
	i82860_get_error_info(mci, &discard);	/* clear counters */

	/* Here we assume that we will never see multiple instances of this
	 * type of memory controller.  The ID is thereक्रमe hardcoded to 0.
	 */
	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(3, "failed edac_mc_add_mc()\n");
		जाओ fail;
	पूर्ण

	/* allocating generic PCI control info */
	i82860_pci = edac_pci_create_generic_ctl(&pdev->dev, EDAC_MOD_STR);
	अगर (!i82860_pci) अणु
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
अटल पूर्णांक i82860_init_one(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rc;

	edac_dbg(0, "\n");
	i82860_prपूर्णांकk(KERN_INFO, "i82860 init one\n");

	अगर (pci_enable_device(pdev) < 0)
		वापस -EIO;

	rc = i82860_probe1(pdev, ent->driver_data);

	अगर (rc == 0)
		mci_pdev = pci_dev_get(pdev);

	वापस rc;
पूर्ण

अटल व्योम i82860_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;

	edac_dbg(0, "\n");

	अगर (i82860_pci)
		edac_pci_release_generic_ctl(i82860_pci);

	अगर ((mci = edac_mc_del_mc(&pdev->dev)) == शून्य)
		वापस;

	edac_mc_मुक्त(mci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id i82860_pci_tbl[] = अणु
	अणु
	 PCI_VEND_DEV(INTEL, 82860_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 I82860पूर्ण,
	अणु
	 0,
	 पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, i82860_pci_tbl);

अटल काष्ठा pci_driver i82860_driver = अणु
	.name = EDAC_MOD_STR,
	.probe = i82860_init_one,
	.हटाओ = i82860_हटाओ_one,
	.id_table = i82860_pci_tbl,
पूर्ण;

अटल पूर्णांक __init i82860_init(व्योम)
अणु
	पूर्णांक pci_rc;

	edac_dbg(3, "\n");

       /* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
       opstate_init();

	अगर ((pci_rc = pci_रेजिस्टर_driver(&i82860_driver)) < 0)
		जाओ fail0;

	अगर (!mci_pdev) अणु
		mci_pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
					PCI_DEVICE_ID_INTEL_82860_0, शून्य);

		अगर (mci_pdev == शून्य) अणु
			edac_dbg(0, "860 pci_get_device fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण

		pci_rc = i82860_init_one(mci_pdev, i82860_pci_tbl);

		अगर (pci_rc < 0) अणु
			edac_dbg(0, "860 init fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण
	पूर्ण

	वापस 0;

fail1:
	pci_unरेजिस्टर_driver(&i82860_driver);

fail0:
	pci_dev_put(mci_pdev);
	वापस pci_rc;
पूर्ण

अटल व्योम __निकास i82860_निकास(व्योम)
अणु
	edac_dbg(3, "\n");
	pci_unरेजिस्टर_driver(&i82860_driver);
	pci_dev_put(mci_pdev);
पूर्ण

module_init(i82860_init);
module_निकास(i82860_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Red Hat Inc. (http://www.redhat.com) "
		"Ben Woodard <woodard@redhat.com>");
MODULE_DESCRIPTION("ECC support for Intel 82860 memory hub controllers");

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
