<शैली गुरु>
/*
 * Intel D82875P Memory Controller kernel module
 * (C) 2003 Linux Networx (http://lnxi.com)
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written by Thayne Harbaugh
 * Contributors:
 *	Wang Zhenyu at पूर्णांकel.com
 *
 * $Id: edac_i82875p.c,v 1.5.2.11 2005/10/05 00:43:44 dsp_llnl Exp $
 *
 * Note: E7210 appears same as D82875P - zhenyu.z.wang at पूर्णांकel.com
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/edac.h>
#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR		"i82875p_edac"

#घोषणा i82875p_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "i82875p", fmt, ##arg)

#घोषणा i82875p_mc_prपूर्णांकk(mci, level, fmt, arg...) \
	edac_mc_chipset_prपूर्णांकk(mci, level, "i82875p", fmt, ##arg)

#अगर_अघोषित PCI_DEVICE_ID_INTEL_82875_0
#घोषणा PCI_DEVICE_ID_INTEL_82875_0	0x2578
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_82875_0 */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_82875_6
#घोषणा PCI_DEVICE_ID_INTEL_82875_6	0x257e
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_82875_6 */

/* four csrows in dual channel, eight in single channel */
#घोषणा I82875P_NR_DIMMS		8
#घोषणा I82875P_NR_CSROWS(nr_chans)	(I82875P_NR_DIMMS / (nr_chans))

/* Intel 82875p रेजिस्टर addresses - device 0 function 0 - DRAM Controller */
#घोषणा I82875P_EAP		0x58	/* Error Address Poपूर्णांकer (32b)
					 *
					 * 31:12 block address
					 * 11:0  reserved
					 */

#घोषणा I82875P_DERRSYN		0x5c	/* DRAM Error Syndrome (8b)
					 *
					 *  7:0  DRAM ECC Syndrome
					 */

#घोषणा I82875P_DES		0x5d	/* DRAM Error Status (8b)
					 *
					 *  7:1  reserved
					 *  0    Error channel 0/1
					 */

#घोषणा I82875P_ERRSTS		0xc8	/* Error Status Register (16b)
					 *
					 * 15:10 reserved
					 *  9    non-DRAM lock error (ndlock)
					 *  8    Sftwr Generated SMI
					 *  7    ECC UE
					 *  6    reserved
					 *  5    MCH detects unimplemented cycle
					 *  4    AGP access outside GA
					 *  3    Invalid AGP access
					 *  2    Invalid GA translation table
					 *  1    Unsupported AGP command
					 *  0    ECC CE
					 */

#घोषणा I82875P_ERRCMD		0xca	/* Error Command (16b)
					 *
					 * 15:10 reserved
					 *  9    SERR on non-DRAM lock
					 *  8    SERR on ECC UE
					 *  7    SERR on ECC CE
					 *  6    target पात on high exception
					 *  5    detect unimplemented cyc
					 *  4    AGP access outside of GA
					 *  3    SERR on invalid AGP access
					 *  2    invalid translation table
					 *  1    SERR on unsupported AGP command
					 *  0    reserved
					 */

/* Intel 82875p रेजिस्टर addresses - device 6 function 0 - DRAM Controller */
#घोषणा I82875P_PCICMD6		0x04	/* PCI Command Register (16b)
					 *
					 * 15:10 reserved
					 *  9    fast back-to-back - ro 0
					 *  8    SERR enable - ro 0
					 *  7    addr/data stepping - ro 0
					 *  6    parity err enable - ro 0
					 *  5    VGA palette snoop - ro 0
					 *  4    mem wr & invalidate - ro 0
					 *  3    special cycle - ro 0
					 *  2    bus master - ro 0
					 *  1    mem access dev6 - 0(dis),1(en)
					 *  0    IO access dev3 - 0(dis),1(en)
					 */

#घोषणा I82875P_BAR6		0x10	/* Mem Delays Base ADDR Reg (32b)
					 *
					 * 31:12 mem base addr [31:12]
					 * 11:4  address mask - ro 0
					 *  3    prefetchable - ro 0(non),1(pre)
					 *  2:1  mem type - ro 0
					 *  0    mem space - ro 0
					 */

/* Intel 82875p MMIO रेजिस्टर space - device 0 function 0 - MMR space */

#घोषणा I82875P_DRB_SHIFT 26	/* 64MiB grain */
#घोषणा I82875P_DRB		0x00	/* DRAM Row Boundary (8b x 8)
					 *
					 *  7    reserved
					 *  6:0  64MiB row boundary addr
					 */

#घोषणा I82875P_DRA		0x10	/* DRAM Row Attribute (4b x 8)
					 *
					 *  7    reserved
					 *  6:4  row attr row 1
					 *  3    reserved
					 *  2:0  row attr row 0
					 *
					 * 000 =  4KiB
					 * 001 =  8KiB
					 * 010 = 16KiB
					 * 011 = 32KiB
					 */

#घोषणा I82875P_DRC		0x68	/* DRAM Controller Mode (32b)
					 *
					 * 31:30 reserved
					 * 29    init complete
					 * 28:23 reserved
					 * 22:21 nr chan 00=1,01=2
					 * 20    reserved
					 * 19:18 Data Integ Mode 00=none,01=ecc
					 * 17:11 reserved
					 * 10:8  refresh mode
					 *  7    reserved
					 *  6:4  mode select
					 *  3:2  reserved
					 *  1:0  DRAM type 01=DDR
					 */

क्रमागत i82875p_chips अणु
	I82875P = 0,
पूर्ण;

काष्ठा i82875p_pvt अणु
	काष्ठा pci_dev *ovrfl_pdev;
	व्योम __iomem *ovrfl_winकरोw;
पूर्ण;

काष्ठा i82875p_dev_info अणु
	स्थिर अक्षर *ctl_name;
पूर्ण;

काष्ठा i82875p_error_info अणु
	u16 errsts;
	u32 eap;
	u8 des;
	u8 derrsyn;
	u16 errsts2;
पूर्ण;

अटल स्थिर काष्ठा i82875p_dev_info i82875p_devs[] = अणु
	[I82875P] = अणु
		.ctl_name = "i82875p"पूर्ण,
पूर्ण;

अटल काष्ठा pci_dev *mci_pdev;	/* init dev: in हाल that AGP code has
					 * alपढ़ोy रेजिस्टरed driver
					 */

अटल काष्ठा edac_pci_ctl_info *i82875p_pci;

अटल व्योम i82875p_get_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा i82875p_error_info *info)
अणु
	काष्ठा pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because there is no atomic way to पढ़ो all the
	 * रेजिस्टरs at once and the रेजिस्टरs can transition from CE being
	 * overwritten by UE.
	 */
	pci_पढ़ो_config_word(pdev, I82875P_ERRSTS, &info->errsts);

	अगर (!(info->errsts & 0x0081))
		वापस;

	pci_पढ़ो_config_dword(pdev, I82875P_EAP, &info->eap);
	pci_पढ़ो_config_byte(pdev, I82875P_DES, &info->des);
	pci_पढ़ो_config_byte(pdev, I82875P_DERRSYN, &info->derrsyn);
	pci_पढ़ो_config_word(pdev, I82875P_ERRSTS, &info->errsts2);

	/*
	 * If the error is the same then we can क्रम both पढ़ोs then
	 * the first set of पढ़ोs is valid.  If there is a change then
	 * there is a CE no info and the second set of पढ़ोs is valid
	 * and should be UE info.
	 */
	अगर ((info->errsts ^ info->errsts2) & 0x0081) अणु
		pci_पढ़ो_config_dword(pdev, I82875P_EAP, &info->eap);
		pci_पढ़ो_config_byte(pdev, I82875P_DES, &info->des);
		pci_पढ़ो_config_byte(pdev, I82875P_DERRSYN, &info->derrsyn);
	पूर्ण

	pci_ग_लिखो_bits16(pdev, I82875P_ERRSTS, 0x0081, 0x0081);
पूर्ण

अटल पूर्णांक i82875p_process_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा i82875p_error_info *info,
				पूर्णांक handle_errors)
अणु
	पूर्णांक row, multi_chan;

	multi_chan = mci->csrows[0]->nr_channels - 1;

	अगर (!(info->errsts & 0x0081))
		वापस 0;

	अगर (!handle_errors)
		वापस 1;

	अगर ((info->errsts ^ info->errsts2) & 0x0081) अणु
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1,
				     "UE overwrote CE", "");
		info->errsts = info->errsts2;
	पूर्ण

	info->eap >>= PAGE_SHIFT;
	row = edac_mc_find_csrow_by_page(mci, info->eap);

	अगर (info->errsts & 0x0080)
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     info->eap, 0, 0,
				     row, -1, -1,
				     "i82875p UE", "");
	अन्यथा
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
				     info->eap, 0, info->derrsyn,
				     row, multi_chan ? (info->des & 0x1) : 0,
				     -1, "i82875p CE", "");

	वापस 1;
पूर्ण

अटल व्योम i82875p_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i82875p_error_info info;

	i82875p_get_error_info(mci, &info);
	i82875p_process_error_info(mci, &info, 1);
पूर्ण

/* Return 0 on success or 1 on failure. */
अटल पूर्णांक i82875p_setup_overfl_dev(काष्ठा pci_dev *pdev,
				काष्ठा pci_dev **ovrfl_pdev,
				व्योम __iomem **ovrfl_winकरोw)
अणु
	काष्ठा pci_dev *dev;
	व्योम __iomem *winकरोw;

	*ovrfl_pdev = शून्य;
	*ovrfl_winकरोw = शून्य;
	dev = pci_get_device(PCI_VEND_DEV(INTEL, 82875_6), शून्य);

	अगर (dev == शून्य) अणु
		/* Intel tells BIOS developers to hide device 6 which
		 * configures the overflow device access containing
		 * the DRBs - this is where we expose device 6.
		 * http://www.x86-secret.com/articles/tweak/pat/patsecrets-2.hपंचांग
		 */
		pci_ग_लिखो_bits8(pdev, 0xf4, 0x2, 0x2);
		dev = pci_scan_single_device(pdev->bus, PCI_DEVFN(6, 0));

		अगर (dev == शून्य)
			वापस 1;

		pci_bus_assign_resources(dev->bus);
		pci_bus_add_device(dev);
	पूर्ण

	*ovrfl_pdev = dev;

	अगर (pci_enable_device(dev)) अणु
		i82875p_prपूर्णांकk(KERN_ERR, "%s(): Failed to enable overflow "
			"device\n", __func__);
		वापस 1;
	पूर्ण

	अगर (pci_request_regions(dev, pci_name(dev))) अणु
#अगर_घोषित CORRECT_BIOS
		जाओ fail0;
#पूर्ण_अगर
	पूर्ण

	/* cache is irrelevant क्रम PCI bus पढ़ोs/ग_लिखोs */
	winकरोw = pci_ioremap_bar(dev, 0);
	अगर (winकरोw == शून्य) अणु
		i82875p_prपूर्णांकk(KERN_ERR, "%s(): Failed to ioremap bar6\n",
			__func__);
		जाओ fail1;
	पूर्ण

	*ovrfl_winकरोw = winकरोw;
	वापस 0;

fail1:
	pci_release_regions(dev);

#अगर_घोषित CORRECT_BIOS
fail0:
	pci_disable_device(dev);
#पूर्ण_अगर
	/* NOTE: the ovrfl proc entry and pci_dev are पूर्णांकentionally left */
	वापस 1;
पूर्ण

/* Return 1 अगर dual channel mode is active.  Else वापस 0. */
अटल अंतरभूत पूर्णांक dual_channel_active(u32 drc)
अणु
	वापस (drc >> 21) & 0x1;
पूर्ण

अटल व्योम i82875p_init_csrows(काष्ठा mem_ctl_info *mci,
				काष्ठा pci_dev *pdev,
				व्योम __iomem * ovrfl_winकरोw, u32 drc)
अणु
	काष्ठा csrow_info *csrow;
	काष्ठा dimm_info *dimm;
	अचिन्हित nr_chans = dual_channel_active(drc) + 1;
	अचिन्हित दीर्घ last_cumul_size;
	u8 value;
	u32 drc_ddim;		/* DRAM Data Integrity Mode 0=none,2=edac */
	u32 cumul_size, nr_pages;
	पूर्णांक index, j;

	drc_ddim = (drc >> 18) & 0x1;
	last_cumul_size = 0;

	/* The dram row boundary (DRB) reg values are boundary address
	 * क्रम each DRAM row with a granularity of 32 or 64MB (single/dual
	 * channel operation).  DRB regs are cumulative; thereक्रमe DRB7 will
	 * contain the total memory contained in all eight rows.
	 */

	क्रम (index = 0; index < mci->nr_csrows; index++) अणु
		csrow = mci->csrows[index];

		value = पढ़ोb(ovrfl_winकरोw + I82875P_DRB + index);
		cumul_size = value << (I82875P_DRB_SHIFT - PAGE_SHIFT);
		edac_dbg(3, "(%d) cumul_size 0x%x\n", index, cumul_size);
		अगर (cumul_size == last_cumul_size)
			जारी;	/* not populated */

		csrow->first_page = last_cumul_size;
		csrow->last_page = cumul_size - 1;
		nr_pages = cumul_size - last_cumul_size;
		last_cumul_size = cumul_size;

		क्रम (j = 0; j < nr_chans; j++) अणु
			dimm = csrow->channels[j]->dimm;

			dimm->nr_pages = nr_pages / nr_chans;
			dimm->grain = 1 << 12;	/* I82875P_EAP has 4KiB reolution */
			dimm->mtype = MEM_DDR;
			dimm->dtype = DEV_UNKNOWN;
			dimm->edac_mode = drc_ddim ? EDAC_SECDED : EDAC_NONE;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक i82875p_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा i82875p_pvt *pvt;
	काष्ठा pci_dev *ovrfl_pdev;
	व्योम __iomem *ovrfl_winकरोw;
	u32 drc;
	u32 nr_chans;
	काष्ठा i82875p_error_info discard;

	edac_dbg(0, "\n");

	अगर (i82875p_setup_overfl_dev(pdev, &ovrfl_pdev, &ovrfl_winकरोw))
		वापस -ENODEV;
	drc = पढ़ोl(ovrfl_winकरोw + I82875P_DRC);
	nr_chans = dual_channel_active(drc) + 1;

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = I82875P_NR_CSROWS(nr_chans);
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = nr_chans;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, माप(*pvt));
	अगर (!mci) अणु
		rc = -ENOMEM;
		जाओ fail0;
	पूर्ण

	edac_dbg(3, "init mci\n");
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FLAG_DDR;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_UNKNOWN;
	mci->mod_name = EDAC_MOD_STR;
	mci->ctl_name = i82875p_devs[dev_idx].ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = i82875p_check;
	mci->ctl_page_to_phys = शून्य;
	edac_dbg(3, "init pvt\n");
	pvt = (काष्ठा i82875p_pvt *)mci->pvt_info;
	pvt->ovrfl_pdev = ovrfl_pdev;
	pvt->ovrfl_winकरोw = ovrfl_winकरोw;
	i82875p_init_csrows(mci, pdev, ovrfl_winकरोw, drc);
	i82875p_get_error_info(mci, &discard);	/* clear counters */

	/* Here we assume that we will never see multiple instances of this
	 * type of memory controller.  The ID is thereक्रमe hardcoded to 0.
	 */
	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(3, "failed edac_mc_add_mc()\n");
		जाओ fail1;
	पूर्ण

	/* allocating generic PCI control info */
	i82875p_pci = edac_pci_create_generic_ctl(&pdev->dev, EDAC_MOD_STR);
	अगर (!i82875p_pci) अणु
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

fail1:
	edac_mc_मुक्त(mci);

fail0:
	iounmap(ovrfl_winकरोw);
	pci_release_regions(ovrfl_pdev);

	pci_disable_device(ovrfl_pdev);
	/* NOTE: the ovrfl proc entry and pci_dev are पूर्णांकentionally left */
	वापस rc;
पूर्ण

/* वापसs count (>= 0), or negative on error */
अटल पूर्णांक i82875p_init_one(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rc;

	edac_dbg(0, "\n");
	i82875p_prपूर्णांकk(KERN_INFO, "i82875p init one\n");

	अगर (pci_enable_device(pdev) < 0)
		वापस -EIO;

	rc = i82875p_probe1(pdev, ent->driver_data);

	अगर (mci_pdev == शून्य)
		mci_pdev = pci_dev_get(pdev);

	वापस rc;
पूर्ण

अटल व्योम i82875p_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा i82875p_pvt *pvt = शून्य;

	edac_dbg(0, "\n");

	अगर (i82875p_pci)
		edac_pci_release_generic_ctl(i82875p_pci);

	अगर ((mci = edac_mc_del_mc(&pdev->dev)) == शून्य)
		वापस;

	pvt = (काष्ठा i82875p_pvt *)mci->pvt_info;

	अगर (pvt->ovrfl_winकरोw)
		iounmap(pvt->ovrfl_winकरोw);

	अगर (pvt->ovrfl_pdev) अणु
#अगर_घोषित CORRECT_BIOS
		pci_release_regions(pvt->ovrfl_pdev);
#पूर्ण_अगर				/*CORRECT_BIOS */
		pci_disable_device(pvt->ovrfl_pdev);
		pci_dev_put(pvt->ovrfl_pdev);
	पूर्ण

	edac_mc_मुक्त(mci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id i82875p_pci_tbl[] = अणु
	अणु
	 PCI_VEND_DEV(INTEL, 82875_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 I82875Pपूर्ण,
	अणु
	 0,
	 पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, i82875p_pci_tbl);

अटल काष्ठा pci_driver i82875p_driver = अणु
	.name = EDAC_MOD_STR,
	.probe = i82875p_init_one,
	.हटाओ = i82875p_हटाओ_one,
	.id_table = i82875p_pci_tbl,
पूर्ण;

अटल पूर्णांक __init i82875p_init(व्योम)
अणु
	पूर्णांक pci_rc;

	edac_dbg(3, "\n");

       /* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
       opstate_init();

	pci_rc = pci_रेजिस्टर_driver(&i82875p_driver);

	अगर (pci_rc < 0)
		जाओ fail0;

	अगर (mci_pdev == शून्य) अणु
		mci_pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
					PCI_DEVICE_ID_INTEL_82875_0, शून्य);

		अगर (!mci_pdev) अणु
			edac_dbg(0, "875p pci_get_device fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण

		pci_rc = i82875p_init_one(mci_pdev, i82875p_pci_tbl);

		अगर (pci_rc < 0) अणु
			edac_dbg(0, "875p init fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण
	पूर्ण

	वापस 0;

fail1:
	pci_unरेजिस्टर_driver(&i82875p_driver);

fail0:
	pci_dev_put(mci_pdev);
	वापस pci_rc;
पूर्ण

अटल व्योम __निकास i82875p_निकास(व्योम)
अणु
	edac_dbg(3, "\n");

	i82875p_हटाओ_one(mci_pdev);
	pci_dev_put(mci_pdev);

	pci_unरेजिस्टर_driver(&i82875p_driver);

पूर्ण

module_init(i82875p_init);
module_निकास(i82875p_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Linux Networx (http://lnxi.com) Thayne Harbaugh");
MODULE_DESCRIPTION("MC support for Intel 82875 memory hub controllers");

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
