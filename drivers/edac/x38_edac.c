<शैली गुरु>
/*
 * Intel X38 Memory Controller kernel module
 * Copyright (C) 2008 Cluster Computing, Inc.
 *
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * This file is based on i3200_edac.c
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/edac.h>

#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR		"x38_edac"

#घोषणा PCI_DEVICE_ID_INTEL_X38_HB	0x29e0

#घोषणा X38_RANKS		8
#घोषणा X38_RANKS_PER_CHANNEL	4
#घोषणा X38_CHANNELS		2

/* Intel X38 रेजिस्टर addresses - device 0 function 0 - DRAM Controller */

#घोषणा X38_MCHBAR_LOW	0x48	/* MCH Memory Mapped Register BAR */
#घोषणा X38_MCHBAR_HIGH	0x4c
#घोषणा X38_MCHBAR_MASK	0xfffffc000ULL	/* bits 35:14 */
#घोषणा X38_MMR_WINDOW_SIZE	16384

#घोषणा X38_TOM	0xa0	/* Top of Memory (16b)
				 *
				 * 15:10 reserved
				 *  9:0  total populated physical memory
				 */
#घोषणा X38_TOM_MASK	0x3ff	/* bits 9:0 */
#घोषणा X38_TOM_SHIFT 26	/* 64MiB grain */

#घोषणा X38_ERRSTS	0xc8	/* Error Status Register (16b)
				 *
				 * 15    reserved
				 * 14    Isochronous TBWRR Run Behind FIFO Full
				 *       (ITCV)
				 * 13    Isochronous TBWRR Run Behind FIFO Put
				 *       (ITSTV)
				 * 12    reserved
				 * 11    MCH Thermal Sensor Event
				 *       क्रम SMI/SCI/SERR (GTSE)
				 * 10    reserved
				 *  9    LOCK to non-DRAM Memory Flag (LCKF)
				 *  8    reserved
				 *  7    DRAM Throttle Flag (DTF)
				 *  6:2  reserved
				 *  1    Multi-bit DRAM ECC Error Flag (DMERR)
				 *  0    Single-bit DRAM ECC Error Flag (DSERR)
				 */
#घोषणा X38_ERRSTS_UE		0x0002
#घोषणा X38_ERRSTS_CE		0x0001
#घोषणा X38_ERRSTS_BITS	(X38_ERRSTS_UE | X38_ERRSTS_CE)


/* Intel  MMIO रेजिस्टर space - device 0 function 0 - MMR space */

#घोषणा X38_C0DRB	0x200	/* Channel 0 DRAM Rank Boundary (16b x 4)
				 *
				 * 15:10 reserved
				 *  9:0  Channel 0 DRAM Rank Boundary Address
				 */
#घोषणा X38_C1DRB	0x600	/* Channel 1 DRAM Rank Boundary (16b x 4) */
#घोषणा X38_DRB_MASK	0x3ff	/* bits 9:0 */
#घोषणा X38_DRB_SHIFT 26	/* 64MiB grain */

#घोषणा X38_C0ECCERRLOG 0x280	/* Channel 0 ECC Error Log (64b)
				 *
				 * 63:48 Error Column Address (ERRCOL)
				 * 47:32 Error Row Address (ERRROW)
				 * 31:29 Error Bank Address (ERRBANK)
				 * 28:27 Error Rank Address (ERRRANK)
				 * 26:24 reserved
				 * 23:16 Error Syndrome (ERRSYND)
				 * 15: 2 reserved
				 *    1  Multiple Bit Error Status (MERRSTS)
				 *    0  Correctable Error Status (CERRSTS)
				 */
#घोषणा X38_C1ECCERRLOG 0x680	/* Channel 1 ECC Error Log (64b) */
#घोषणा X38_ECCERRLOG_CE	0x1
#घोषणा X38_ECCERRLOG_UE	0x2
#घोषणा X38_ECCERRLOG_RANK_BITS	0x18000000
#घोषणा X38_ECCERRLOG_SYNDROME_BITS	0xff0000

#घोषणा X38_CAPID0 0xe0	/* see P.94 of spec क्रम details */

अटल पूर्णांक x38_channel_num;

अटल पूर्णांक how_many_channel(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित अक्षर capid0_8b; /* 8th byte of CAPID0 */

	pci_पढ़ो_config_byte(pdev, X38_CAPID0 + 8, &capid0_8b);
	अगर (capid0_8b & 0x20) अणु	/* check DCD: Dual Channel Disable */
		edac_dbg(0, "In single channel mode\n");
		x38_channel_num = 1;
	पूर्ण अन्यथा अणु
		edac_dbg(0, "In dual channel mode\n");
		x38_channel_num = 2;
	पूर्ण

	वापस x38_channel_num;
पूर्ण

अटल अचिन्हित दीर्घ eccerrlog_syndrome(u64 log)
अणु
	वापस (log & X38_ECCERRLOG_SYNDROME_BITS) >> 16;
पूर्ण

अटल पूर्णांक eccerrlog_row(पूर्णांक channel, u64 log)
अणु
	वापस ((log & X38_ECCERRLOG_RANK_BITS) >> 27) |
		(channel * X38_RANKS_PER_CHANNEL);
पूर्ण

क्रमागत x38_chips अणु
	X38 = 0,
पूर्ण;

काष्ठा x38_dev_info अणु
	स्थिर अक्षर *ctl_name;
पूर्ण;

काष्ठा x38_error_info अणु
	u16 errsts;
	u16 errsts2;
	u64 eccerrlog[X38_CHANNELS];
पूर्ण;

अटल स्थिर काष्ठा x38_dev_info x38_devs[] = अणु
	[X38] = अणु
		.ctl_name = "x38"पूर्ण,
पूर्ण;

अटल काष्ठा pci_dev *mci_pdev;
अटल पूर्णांक x38_रेजिस्टरed = 1;


अटल व्योम x38_clear_error_info(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * Clear any error bits.
	 * (Yes, we really clear bits by writing 1 to them.)
	 */
	pci_ग_लिखो_bits16(pdev, X38_ERRSTS, X38_ERRSTS_BITS,
			 X38_ERRSTS_BITS);
पूर्ण

अटल व्योम x38_get_and_clear_error_info(काष्ठा mem_ctl_info *mci,
				 काष्ठा x38_error_info *info)
अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *winकरोw = mci->pvt_info;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because there is no atomic way to पढ़ो all the
	 * रेजिस्टरs at once and the रेजिस्टरs can transition from CE being
	 * overwritten by UE.
	 */
	pci_पढ़ो_config_word(pdev, X38_ERRSTS, &info->errsts);
	अगर (!(info->errsts & X38_ERRSTS_BITS))
		वापस;

	info->eccerrlog[0] = lo_hi_पढ़ोq(winकरोw + X38_C0ECCERRLOG);
	अगर (x38_channel_num == 2)
		info->eccerrlog[1] = lo_hi_पढ़ोq(winकरोw + X38_C1ECCERRLOG);

	pci_पढ़ो_config_word(pdev, X38_ERRSTS, &info->errsts2);

	/*
	 * If the error is the same क्रम both पढ़ोs then the first set
	 * of पढ़ोs is valid.  If there is a change then there is a CE
	 * with no info and the second set of पढ़ोs is valid and
	 * should be UE info.
	 */
	अगर ((info->errsts ^ info->errsts2) & X38_ERRSTS_BITS) अणु
		info->eccerrlog[0] = lo_hi_पढ़ोq(winकरोw + X38_C0ECCERRLOG);
		अगर (x38_channel_num == 2)
			info->eccerrlog[1] =
				lo_hi_पढ़ोq(winकरोw + X38_C1ECCERRLOG);
	पूर्ण

	x38_clear_error_info(mci);
पूर्ण

अटल व्योम x38_process_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा x38_error_info *info)
अणु
	पूर्णांक channel;
	u64 log;

	अगर (!(info->errsts & X38_ERRSTS_BITS))
		वापस;

	अगर ((info->errsts ^ info->errsts2) & X38_ERRSTS_BITS) अणु
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1,
				     "UE overwrote CE", "");
		info->errsts = info->errsts2;
	पूर्ण

	क्रम (channel = 0; channel < x38_channel_num; channel++) अणु
		log = info->eccerrlog[channel];
		अगर (log & X38_ECCERRLOG_UE) अणु
			edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
					     0, 0, 0,
					     eccerrlog_row(channel, log),
					     -1, -1,
					     "x38 UE", "");
		पूर्ण अन्यथा अगर (log & X38_ECCERRLOG_CE) अणु
			edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
					     0, 0, eccerrlog_syndrome(log),
					     eccerrlog_row(channel, log),
					     -1, -1,
					     "x38 CE", "");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम x38_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा x38_error_info info;

	x38_get_and_clear_error_info(mci, &info);
	x38_process_error_info(mci, &info);
पूर्ण

अटल व्योम __iomem *x38_map_mchbar(काष्ठा pci_dev *pdev)
अणु
	जोड़ अणु
		u64 mchbar;
		काष्ठा अणु
			u32 mchbar_low;
			u32 mchbar_high;
		पूर्ण;
	पूर्ण u;
	व्योम __iomem *winकरोw;

	pci_पढ़ो_config_dword(pdev, X38_MCHBAR_LOW, &u.mchbar_low);
	pci_ग_लिखो_config_dword(pdev, X38_MCHBAR_LOW, u.mchbar_low | 0x1);
	pci_पढ़ो_config_dword(pdev, X38_MCHBAR_HIGH, &u.mchbar_high);
	u.mchbar &= X38_MCHBAR_MASK;

	अगर (u.mchbar != (resource_माप_प्रकार)u.mchbar) अणु
		prपूर्णांकk(KERN_ERR
			"x38: mmio space beyond accessible range (0x%llx)\n",
			(अचिन्हित दीर्घ दीर्घ)u.mchbar);
		वापस शून्य;
	पूर्ण

	winकरोw = ioremap(u.mchbar, X38_MMR_WINDOW_SIZE);
	अगर (!winकरोw)
		prपूर्णांकk(KERN_ERR "x38: cannot map mmio space at 0x%llx\n",
			(अचिन्हित दीर्घ दीर्घ)u.mchbar);

	वापस winकरोw;
पूर्ण


अटल व्योम x38_get_drbs(व्योम __iomem *winकरोw,
			u16 drbs[X38_CHANNELS][X38_RANKS_PER_CHANNEL])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < X38_RANKS_PER_CHANNEL; i++) अणु
		drbs[0][i] = पढ़ोw(winकरोw + X38_C0DRB + 2*i) & X38_DRB_MASK;
		drbs[1][i] = पढ़ोw(winकरोw + X38_C1DRB + 2*i) & X38_DRB_MASK;
	पूर्ण
पूर्ण

अटल bool x38_is_stacked(काष्ठा pci_dev *pdev,
			u16 drbs[X38_CHANNELS][X38_RANKS_PER_CHANNEL])
अणु
	u16 tom;

	pci_पढ़ो_config_word(pdev, X38_TOM, &tom);
	tom &= X38_TOM_MASK;

	वापस drbs[X38_CHANNELS - 1][X38_RANKS_PER_CHANNEL - 1] == tom;
पूर्ण

अटल अचिन्हित दीर्घ drb_to_nr_pages(
			u16 drbs[X38_CHANNELS][X38_RANKS_PER_CHANNEL],
			bool stacked, पूर्णांक channel, पूर्णांक rank)
अणु
	पूर्णांक n;

	n = drbs[channel][rank];
	अगर (rank > 0)
		n -= drbs[channel][rank - 1];
	अगर (stacked && (channel == 1) && drbs[channel][rank] ==
				drbs[channel][X38_RANKS_PER_CHANNEL - 1]) अणु
		n -= drbs[0][X38_RANKS_PER_CHANNEL - 1];
	पूर्ण

	n <<= (X38_DRB_SHIFT - PAGE_SHIFT);
	वापस n;
पूर्ण

अटल पूर्णांक x38_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	पूर्णांक rc;
	पूर्णांक i, j;
	काष्ठा mem_ctl_info *mci = शून्य;
	काष्ठा edac_mc_layer layers[2];
	u16 drbs[X38_CHANNELS][X38_RANKS_PER_CHANNEL];
	bool stacked;
	व्योम __iomem *winकरोw;

	edac_dbg(0, "MC:\n");

	winकरोw = x38_map_mchbar(pdev);
	अगर (!winकरोw)
		वापस -ENODEV;

	x38_get_drbs(winकरोw, drbs);

	how_many_channel(pdev);

	/* FIXME: unconventional pvt_info usage */
	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = X38_RANKS;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = x38_channel_num;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, 0);
	अगर (!mci)
		वापस -ENOMEM;

	edac_dbg(3, "MC: init mci\n");

	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FLAG_DDR2;

	mci->edac_ctl_cap = EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;

	mci->mod_name = EDAC_MOD_STR;
	mci->ctl_name = x38_devs[dev_idx].ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = x38_check;
	mci->ctl_page_to_phys = शून्य;
	mci->pvt_info = winकरोw;

	stacked = x38_is_stacked(pdev, drbs);

	/*
	 * The dram rank boundary (DRB) reg values are boundary addresses
	 * क्रम each DRAM rank with a granularity of 64MB.  DRB regs are
	 * cumulative; the last one will contain the total memory
	 * contained in all ranks.
	 */
	क्रम (i = 0; i < mci->nr_csrows; i++) अणु
		अचिन्हित दीर्घ nr_pages;
		काष्ठा csrow_info *csrow = mci->csrows[i];

		nr_pages = drb_to_nr_pages(drbs, stacked,
			i / X38_RANKS_PER_CHANNEL,
			i % X38_RANKS_PER_CHANNEL);

		अगर (nr_pages == 0)
			जारी;

		क्रम (j = 0; j < x38_channel_num; j++) अणु
			काष्ठा dimm_info *dimm = csrow->channels[j]->dimm;

			dimm->nr_pages = nr_pages / x38_channel_num;
			dimm->grain = nr_pages << PAGE_SHIFT;
			dimm->mtype = MEM_DDR2;
			dimm->dtype = DEV_UNKNOWN;
			dimm->edac_mode = EDAC_UNKNOWN;
		पूर्ण
	पूर्ण

	x38_clear_error_info(mci);

	rc = -ENODEV;
	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(3, "MC: failed edac_mc_add_mc()\n");
		जाओ fail;
	पूर्ण

	/* get this far and it's successful */
	edac_dbg(3, "MC: success\n");
	वापस 0;

fail:
	iounmap(winकरोw);
	अगर (mci)
		edac_mc_मुक्त(mci);

	वापस rc;
पूर्ण

अटल पूर्णांक x38_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rc;

	edac_dbg(0, "MC:\n");

	अगर (pci_enable_device(pdev) < 0)
		वापस -EIO;

	rc = x38_probe1(pdev, ent->driver_data);
	अगर (!mci_pdev)
		mci_pdev = pci_dev_get(pdev);

	वापस rc;
पूर्ण

अटल व्योम x38_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;

	edac_dbg(0, "\n");

	mci = edac_mc_del_mc(&pdev->dev);
	अगर (!mci)
		वापस;

	iounmap(mci->pvt_info);

	edac_mc_मुक्त(mci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id x38_pci_tbl[] = अणु
	अणु
	 PCI_VEND_DEV(INTEL, X38_HB), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 X38पूर्ण,
	अणु
	 0,
	 पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, x38_pci_tbl);

अटल काष्ठा pci_driver x38_driver = अणु
	.name = EDAC_MOD_STR,
	.probe = x38_init_one,
	.हटाओ = x38_हटाओ_one,
	.id_table = x38_pci_tbl,
पूर्ण;

अटल पूर्णांक __init x38_init(व्योम)
अणु
	पूर्णांक pci_rc;

	edac_dbg(3, "MC:\n");

	/* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
	opstate_init();

	pci_rc = pci_रेजिस्टर_driver(&x38_driver);
	अगर (pci_rc < 0)
		जाओ fail0;

	अगर (!mci_pdev) अणु
		x38_रेजिस्टरed = 0;
		mci_pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
					PCI_DEVICE_ID_INTEL_X38_HB, शून्य);
		अगर (!mci_pdev) अणु
			edac_dbg(0, "x38 pci_get_device fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण

		pci_rc = x38_init_one(mci_pdev, x38_pci_tbl);
		अगर (pci_rc < 0) अणु
			edac_dbg(0, "x38 init fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण
	पूर्ण

	वापस 0;

fail1:
	pci_unरेजिस्टर_driver(&x38_driver);

fail0:
	pci_dev_put(mci_pdev);

	वापस pci_rc;
पूर्ण

अटल व्योम __निकास x38_निकास(व्योम)
अणु
	edac_dbg(3, "MC:\n");

	pci_unरेजिस्टर_driver(&x38_driver);
	अगर (!x38_रेजिस्टरed) अणु
		x38_हटाओ_one(mci_pdev);
		pci_dev_put(mci_pdev);
	पूर्ण
पूर्ण

module_init(x38_init);
module_निकास(x38_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cluster Computing, Inc. Hitoshi Mitake");
MODULE_DESCRIPTION("MC support for Intel X38 memory hub controllers");

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
