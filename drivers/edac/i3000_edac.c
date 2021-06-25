<शैली गुरु>
/*
 * Intel 3000/3010 Memory Controller kernel module
 * Copyright (C) 2007 Akamai Technologies, Inc.
 * Shamelessly copied from:
 * 	Intel D82875P Memory Controller kernel module
 * 	(C) 2003 Linux Networx (http://lnxi.com)
 *
 * This file may be distributed under the terms of the
 * GNU General Public License.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/edac.h>
#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR		"i3000_edac"

#घोषणा I3000_RANKS		8
#घोषणा I3000_RANKS_PER_CHANNEL	4
#घोषणा I3000_CHANNELS		2

/* Intel 3000 रेजिस्टर addresses - device 0 function 0 - DRAM Controller */

#घोषणा I3000_MCHBAR		0x44	/* MCH Memory Mapped Register BAR */
#घोषणा I3000_MCHBAR_MASK	0xffffc000
#घोषणा I3000_MMR_WINDOW_SIZE	16384

#घोषणा I3000_EDEAP	0x70	/* Extended DRAM Error Address Poपूर्णांकer (8b)
				 *
				 * 7:1   reserved
				 * 0     bit 32 of address
				 */
#घोषणा I3000_DEAP	0x58	/* DRAM Error Address Poपूर्णांकer (32b)
				 *
				 * 31:7  address
				 * 6:1   reserved
				 * 0     Error channel 0/1
				 */
#घोषणा I3000_DEAP_GRAIN 		(1 << 7)

/*
 * Helper functions to decode the DEAP/EDEAP hardware रेजिस्टरs.
 *
 * The type promotion here is deliberate; we're deriving an
 * अचिन्हित दीर्घ pfn and offset from hardware regs which are u8/u32.
 */

अटल अंतरभूत अचिन्हित दीर्घ deap_pfn(u8 edeap, u32 deap)
अणु
	deap >>= PAGE_SHIFT;
	deap |= (edeap & 1) << (32 - PAGE_SHIFT);
	वापस deap;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ deap_offset(u32 deap)
अणु
	वापस deap & ~(I3000_DEAP_GRAIN - 1) & ~PAGE_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक deap_channel(u32 deap)
अणु
	वापस deap & 1;
पूर्ण

#घोषणा I3000_DERRSYN	0x5c	/* DRAM Error Syndrome (8b)
				 *
				 *  7:0  DRAM ECC Syndrome
				 */

#घोषणा I3000_ERRSTS	0xc8	/* Error Status Register (16b)
				 *
				 * 15:12 reserved
				 * 11    MCH Thermal Sensor Event
				 *         क्रम SMI/SCI/SERR
				 * 10    reserved
				 *  9    LOCK to non-DRAM Memory Flag (LCKF)
				 *  8    Received Refresh Timeout Flag (RRTOF)
				 *  7:2  reserved
				 *  1    Multi-bit DRAM ECC Error Flag (DMERR)
				 *  0    Single-bit DRAM ECC Error Flag (DSERR)
				 */
#घोषणा I3000_ERRSTS_BITS	0x0b03	/* bits which indicate errors */
#घोषणा I3000_ERRSTS_UE		0x0002
#घोषणा I3000_ERRSTS_CE		0x0001

#घोषणा I3000_ERRCMD	0xca	/* Error Command (16b)
				 *
				 * 15:12 reserved
				 * 11    SERR on MCH Thermal Sensor Event
				 *         (TSESERR)
				 * 10    reserved
				 *  9    SERR on LOCK to non-DRAM Memory
				 *         (LCKERR)
				 *  8    SERR on DRAM Refresh Timeout
				 *         (DRTOERR)
				 *  7:2  reserved
				 *  1    SERR Multi-Bit DRAM ECC Error
				 *         (DMERR)
				 *  0    SERR on Single-Bit ECC Error
				 *         (DSERR)
				 */

/* Intel  MMIO रेजिस्टर space - device 0 function 0 - MMR space */

#घोषणा I3000_DRB_SHIFT 25	/* 32MiB grain */

#घोषणा I3000_C0DRB	0x100	/* Channel 0 DRAM Rank Boundary (8b x 4)
				 *
				 * 7:0   Channel 0 DRAM Rank Boundary Address
				 */
#घोषणा I3000_C1DRB	0x180	/* Channel 1 DRAM Rank Boundary (8b x 4)
				 *
				 * 7:0   Channel 1 DRAM Rank Boundary Address
				 */

#घोषणा I3000_C0DRA	0x108	/* Channel 0 DRAM Rank Attribute (8b x 2)
				 *
				 * 7     reserved
				 * 6:4   DRAM odd Rank Attribute
				 * 3     reserved
				 * 2:0   DRAM even Rank Attribute
				 *
				 * Each attribute defines the page
				 * size of the corresponding rank:
				 *     000: unpopulated
				 *     001: reserved
				 *     010: 4 KB
				 *     011: 8 KB
				 *     100: 16 KB
				 *     Others: reserved
				 */
#घोषणा I3000_C1DRA	0x188	/* Channel 1 DRAM Rank Attribute (8b x 2) */

अटल अंतरभूत अचिन्हित अक्षर odd_rank_attrib(अचिन्हित अक्षर dra)
अणु
	वापस (dra & 0x70) >> 4;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर even_rank_attrib(अचिन्हित अक्षर dra)
अणु
	वापस dra & 0x07;
पूर्ण

#घोषणा I3000_C0DRC0	0x120	/* DRAM Controller Mode 0 (32b)
				 *
				 * 31:30 reserved
				 * 29    Initialization Complete (IC)
				 * 28:11 reserved
				 * 10:8  Refresh Mode Select (RMS)
				 * 7     reserved
				 * 6:4   Mode Select (SMS)
				 * 3:2   reserved
				 * 1:0   DRAM Type (DT)
				 */

#घोषणा I3000_C0DRC1	0x124	/* DRAM Controller Mode 1 (32b)
				 *
				 * 31    Enhanced Addressing Enable (ENHADE)
				 * 30:0  reserved
				 */

क्रमागत i3000p_chips अणु
	I3000 = 0,
पूर्ण;

काष्ठा i3000_dev_info अणु
	स्थिर अक्षर *ctl_name;
पूर्ण;

काष्ठा i3000_error_info अणु
	u16 errsts;
	u8 derrsyn;
	u8 edeap;
	u32 deap;
	u16 errsts2;
पूर्ण;

अटल स्थिर काष्ठा i3000_dev_info i3000_devs[] = अणु
	[I3000] = अणु
		.ctl_name = "i3000"पूर्ण,
पूर्ण;

अटल काष्ठा pci_dev *mci_pdev;
अटल पूर्णांक i3000_रेजिस्टरed = 1;
अटल काष्ठा edac_pci_ctl_info *i3000_pci;

अटल व्योम i3000_get_error_info(काष्ठा mem_ctl_info *mci,
				 काष्ठा i3000_error_info *info)
अणु
	काष्ठा pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because there is no atomic way to पढ़ो all the
	 * रेजिस्टरs at once and the रेजिस्टरs can transition from CE being
	 * overwritten by UE.
	 */
	pci_पढ़ो_config_word(pdev, I3000_ERRSTS, &info->errsts);
	अगर (!(info->errsts & I3000_ERRSTS_BITS))
		वापस;
	pci_पढ़ो_config_byte(pdev, I3000_EDEAP, &info->edeap);
	pci_पढ़ो_config_dword(pdev, I3000_DEAP, &info->deap);
	pci_पढ़ो_config_byte(pdev, I3000_DERRSYN, &info->derrsyn);
	pci_पढ़ो_config_word(pdev, I3000_ERRSTS, &info->errsts2);

	/*
	 * If the error is the same क्रम both पढ़ोs then the first set
	 * of पढ़ोs is valid.  If there is a change then there is a CE
	 * with no info and the second set of पढ़ोs is valid and
	 * should be UE info.
	 */
	अगर ((info->errsts ^ info->errsts2) & I3000_ERRSTS_BITS) अणु
		pci_पढ़ो_config_byte(pdev, I3000_EDEAP, &info->edeap);
		pci_पढ़ो_config_dword(pdev, I3000_DEAP, &info->deap);
		pci_पढ़ो_config_byte(pdev, I3000_DERRSYN, &info->derrsyn);
	पूर्ण

	/*
	 * Clear any error bits.
	 * (Yes, we really clear bits by writing 1 to them.)
	 */
	pci_ग_लिखो_bits16(pdev, I3000_ERRSTS, I3000_ERRSTS_BITS,
			 I3000_ERRSTS_BITS);
पूर्ण

अटल पूर्णांक i3000_process_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा i3000_error_info *info,
				पूर्णांक handle_errors)
अणु
	पूर्णांक row, multi_chan, channel;
	अचिन्हित दीर्घ pfn, offset;

	multi_chan = mci->csrows[0]->nr_channels - 1;

	अगर (!(info->errsts & I3000_ERRSTS_BITS))
		वापस 0;

	अगर (!handle_errors)
		वापस 1;

	अगर ((info->errsts ^ info->errsts2) & I3000_ERRSTS_BITS) अणु
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1,
				     "UE overwrote CE", "");
		info->errsts = info->errsts2;
	पूर्ण

	pfn = deap_pfn(info->edeap, info->deap);
	offset = deap_offset(info->deap);
	channel = deap_channel(info->deap);

	row = edac_mc_find_csrow_by_page(mci, pfn);

	अगर (info->errsts & I3000_ERRSTS_UE)
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     pfn, offset, 0,
				     row, -1, -1,
				     "i3000 UE", "");
	अन्यथा
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
				     pfn, offset, info->derrsyn,
				     row, multi_chan ? channel : 0, -1,
				     "i3000 CE", "");

	वापस 1;
पूर्ण

अटल व्योम i3000_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i3000_error_info info;

	i3000_get_error_info(mci, &info);
	i3000_process_error_info(mci, &info, 1);
पूर्ण

अटल पूर्णांक i3000_is_पूर्णांकerleaved(स्थिर अचिन्हित अक्षर *c0dra,
				स्थिर अचिन्हित अक्षर *c1dra,
				स्थिर अचिन्हित अक्षर *c0drb,
				स्थिर अचिन्हित अक्षर *c1drb)
अणु
	पूर्णांक i;

	/*
	 * If the channels aren't populated identically then
	 * we're not पूर्णांकerleaved.
	 */
	क्रम (i = 0; i < I3000_RANKS_PER_CHANNEL / 2; i++)
		अगर (odd_rank_attrib(c0dra[i]) != odd_rank_attrib(c1dra[i]) ||
			even_rank_attrib(c0dra[i]) !=
						even_rank_attrib(c1dra[i]))
			वापस 0;

	/*
	 * If the rank boundaries क्रम the two channels are dअगरferent
	 * then we're not पूर्णांकerleaved.
	 */
	क्रम (i = 0; i < I3000_RANKS_PER_CHANNEL; i++)
		अगर (c0drb[i] != c1drb[i])
			वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक i3000_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	पूर्णांक rc;
	पूर्णांक i, j;
	काष्ठा mem_ctl_info *mci = शून्य;
	काष्ठा edac_mc_layer layers[2];
	अचिन्हित दीर्घ last_cumul_size, nr_pages;
	पूर्णांक पूर्णांकerleaved, nr_channels;
	अचिन्हित अक्षर dra[I3000_RANKS / 2], drb[I3000_RANKS];
	अचिन्हित अक्षर *c0dra = dra, *c1dra = &dra[I3000_RANKS_PER_CHANNEL / 2];
	अचिन्हित अक्षर *c0drb = drb, *c1drb = &drb[I3000_RANKS_PER_CHANNEL];
	अचिन्हित दीर्घ mchbar;
	व्योम __iomem *winकरोw;

	edac_dbg(0, "MC:\n");

	pci_पढ़ो_config_dword(pdev, I3000_MCHBAR, (u32 *) & mchbar);
	mchbar &= I3000_MCHBAR_MASK;
	winकरोw = ioremap(mchbar, I3000_MMR_WINDOW_SIZE);
	अगर (!winकरोw) अणु
		prपूर्णांकk(KERN_ERR "i3000: cannot map mmio space at 0x%lx\n",
			mchbar);
		वापस -ENODEV;
	पूर्ण

	c0dra[0] = पढ़ोb(winकरोw + I3000_C0DRA + 0);	/* ranks 0,1 */
	c0dra[1] = पढ़ोb(winकरोw + I3000_C0DRA + 1);	/* ranks 2,3 */
	c1dra[0] = पढ़ोb(winकरोw + I3000_C1DRA + 0);	/* ranks 0,1 */
	c1dra[1] = पढ़ोb(winकरोw + I3000_C1DRA + 1);	/* ranks 2,3 */

	क्रम (i = 0; i < I3000_RANKS_PER_CHANNEL; i++) अणु
		c0drb[i] = पढ़ोb(winकरोw + I3000_C0DRB + i);
		c1drb[i] = पढ़ोb(winकरोw + I3000_C1DRB + i);
	पूर्ण

	iounmap(winकरोw);

	/*
	 * Figure out how many channels we have.
	 *
	 * If we have what the datasheet calls "asymmetric channels"
	 * (essentially the same as what was called "भव single
	 * channel mode" in the i82875) then it's a single channel as
	 * far as EDAC is concerned.
	 */
	पूर्णांकerleaved = i3000_is_पूर्णांकerleaved(c0dra, c1dra, c0drb, c1drb);
	nr_channels = पूर्णांकerleaved ? 2 : 1;

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = I3000_RANKS / nr_channels;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = nr_channels;
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
	mci->ctl_name = i3000_devs[dev_idx].ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = i3000_check;
	mci->ctl_page_to_phys = शून्य;

	/*
	 * The dram rank boundary (DRB) reg values are boundary addresses
	 * क्रम each DRAM rank with a granularity of 32MB.  DRB regs are
	 * cumulative; the last one will contain the total memory
	 * contained in all ranks.
	 *
	 * If we're in interleaved mode then we're only walking through
	 * the ranks of controller 0, so we द्विगुन all the values we see.
	 */
	क्रम (last_cumul_size = i = 0; i < mci->nr_csrows; i++) अणु
		u8 value;
		u32 cumul_size;
		काष्ठा csrow_info *csrow = mci->csrows[i];

		value = drb[i];
		cumul_size = value << (I3000_DRB_SHIFT - PAGE_SHIFT);
		अगर (पूर्णांकerleaved)
			cumul_size <<= 1;
		edac_dbg(3, "MC: (%d) cumul_size 0x%x\n", i, cumul_size);
		अगर (cumul_size == last_cumul_size)
			जारी;

		csrow->first_page = last_cumul_size;
		csrow->last_page = cumul_size - 1;
		nr_pages = cumul_size - last_cumul_size;
		last_cumul_size = cumul_size;

		क्रम (j = 0; j < nr_channels; j++) अणु
			काष्ठा dimm_info *dimm = csrow->channels[j]->dimm;

			dimm->nr_pages = nr_pages / nr_channels;
			dimm->grain = I3000_DEAP_GRAIN;
			dimm->mtype = MEM_DDR2;
			dimm->dtype = DEV_UNKNOWN;
			dimm->edac_mode = EDAC_UNKNOWN;
		पूर्ण
	पूर्ण

	/*
	 * Clear any error bits.
	 * (Yes, we really clear bits by writing 1 to them.)
	 */
	pci_ग_लिखो_bits16(pdev, I3000_ERRSTS, I3000_ERRSTS_BITS,
			 I3000_ERRSTS_BITS);

	rc = -ENODEV;
	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(3, "MC: failed edac_mc_add_mc()\n");
		जाओ fail;
	पूर्ण

	/* allocating generic PCI control info */
	i3000_pci = edac_pci_create_generic_ctl(&pdev->dev, EDAC_MOD_STR);
	अगर (!i3000_pci) अणु
		prपूर्णांकk(KERN_WARNING
			"%s(): Unable to create PCI control\n",
			__func__);
		prपूर्णांकk(KERN_WARNING
			"%s(): PCI error report via EDAC not setup\n",
			__func__);
	पूर्ण

	/* get this far and it's successful */
	edac_dbg(3, "MC: success\n");
	वापस 0;

fail:
	अगर (mci)
		edac_mc_मुक्त(mci);

	वापस rc;
पूर्ण

/* वापसs count (>= 0), or negative on error */
अटल पूर्णांक i3000_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rc;

	edac_dbg(0, "MC:\n");

	अगर (pci_enable_device(pdev) < 0)
		वापस -EIO;

	rc = i3000_probe1(pdev, ent->driver_data);
	अगर (!mci_pdev)
		mci_pdev = pci_dev_get(pdev);

	वापस rc;
पूर्ण

अटल व्योम i3000_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;

	edac_dbg(0, "\n");

	अगर (i3000_pci)
		edac_pci_release_generic_ctl(i3000_pci);

	mci = edac_mc_del_mc(&pdev->dev);
	अगर (!mci)
		वापस;

	edac_mc_मुक्त(mci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id i3000_pci_tbl[] = अणु
	अणु
	 PCI_VEND_DEV(INTEL, 3000_HB), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 I3000पूर्ण,
	अणु
	 0,
	 पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, i3000_pci_tbl);

अटल काष्ठा pci_driver i3000_driver = अणु
	.name = EDAC_MOD_STR,
	.probe = i3000_init_one,
	.हटाओ = i3000_हटाओ_one,
	.id_table = i3000_pci_tbl,
पूर्ण;

अटल पूर्णांक __init i3000_init(व्योम)
अणु
	पूर्णांक pci_rc;

	edac_dbg(3, "MC:\n");

	/* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
	opstate_init();

	pci_rc = pci_रेजिस्टर_driver(&i3000_driver);
	अगर (pci_rc < 0)
		जाओ fail0;

	अगर (!mci_pdev) अणु
		i3000_रेजिस्टरed = 0;
		mci_pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
					PCI_DEVICE_ID_INTEL_3000_HB, शून्य);
		अगर (!mci_pdev) अणु
			edac_dbg(0, "i3000 pci_get_device fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण

		pci_rc = i3000_init_one(mci_pdev, i3000_pci_tbl);
		अगर (pci_rc < 0) अणु
			edac_dbg(0, "i3000 init fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण
	पूर्ण

	वापस 0;

fail1:
	pci_unरेजिस्टर_driver(&i3000_driver);

fail0:
	pci_dev_put(mci_pdev);

	वापस pci_rc;
पूर्ण

अटल व्योम __निकास i3000_निकास(व्योम)
अणु
	edac_dbg(3, "MC:\n");

	pci_unरेजिस्टर_driver(&i3000_driver);
	अगर (!i3000_रेजिस्टरed) अणु
		i3000_हटाओ_one(mci_pdev);
		pci_dev_put(mci_pdev);
	पूर्ण
पूर्ण

module_init(i3000_init);
module_निकास(i3000_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Akamai Technologies Arthur Ulfeldt/Jason Uhlenkott");
MODULE_DESCRIPTION("MC support for Intel 3000 memory hub controllers");

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
