<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel E3-1200
 * Copyright (C) 2014 Jason Baron <jbaron@akamai.com>
 *
 * Support क्रम the E3-1200 processor family. Heavily based on previous
 * Intel EDAC drivers.
 *
 * Since the DRAM controller is on the cpu chip, we can use its PCI device
 * id to identअगरy these processors.
 *
 * PCI DRAM controller device ids (Taken from The PCI ID Repository - https://pci-ids.ucw.cz/)
 *
 * 0108: Xeon E3-1200 Processor Family DRAM Controller
 * 010c: Xeon E3-1200/2nd Generation Core Processor Family DRAM Controller
 * 0150: Xeon E3-1200 v2/3rd Gen Core processor DRAM Controller
 * 0158: Xeon E3-1200 v2/Ivy Bridge DRAM Controller
 * 015c: Xeon E3-1200 v2/3rd Gen Core processor DRAM Controller
 * 0c04: Xeon E3-1200 v3/4th Gen Core Processor DRAM Controller
 * 0c08: Xeon E3-1200 v3 Processor DRAM Controller
 * 1918: Xeon E3-1200 v5 Skylake Host Bridge/DRAM Registers
 * 5918: Xeon E3-1200 Xeon E3-1200 v6/7th Gen Core Processor Host Bridge/DRAM Registers
 * 3e..: 8th/9th Gen Core Processor Host Bridge/DRAM Registers
 *
 * Based on Intel specअगरication:
 * https://www.पूर्णांकel.com/content/dam/www/खुला/us/en/करोcuments/datasheets/xeon-e3-1200v3-vol-2-datasheet.pdf
 * http://www.पूर्णांकel.com/content/www/us/en/processors/xeon/xeon-e3-1200-family-vol-2-datasheet.hपंचांगl
 * https://www.पूर्णांकel.com/content/www/us/en/processors/core/7th-gen-core-family-mobile-h-processor-lines-datasheet-vol-2.hपंचांगl
 * https://www.पूर्णांकel.com/content/www/us/en/products/करोcs/processors/core/8th-gen-core-family-datasheet-vol-2.hपंचांगl
 *
 * According to the above datasheet (p.16):
 * "
 * 6. Software must not access B0/D0/F0 32-bit memory-mapped रेजिस्टरs with
 * requests that cross a DW boundary.
 * "
 *
 * Thus, we make use of the explicit: lo_hi_पढ़ोq(), which अवरोधs the पढ़ोq पूर्णांकo
 * 2 पढ़ोl() calls. This restriction may be lअगरted in subsequent chip releases,
 * but lo_hi_पढ़ोq() ensures that we are safe across all e3-1200 processors.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/edac.h>

#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR "ie31200_edac"

#घोषणा ie31200_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "ie31200", fmt, ##arg)

#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_1 0x0108
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_2 0x010c
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_3 0x0150
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_4 0x0158
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_5 0x015c
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_6 0x0c04
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_7 0x0c08
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_8 0x1918
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_9 0x5918

/* Coffee Lake-S */
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_MASK 0x3e00
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_1    0x3e0f
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_2    0x3e18
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_3    0x3e1f
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_4    0x3e30
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_5    0x3e31
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_6    0x3e32
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_7    0x3e33
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_8    0x3ec2
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_9    0x3ec6
#घोषणा PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_10   0x3eca

/* Test अगर HB is क्रम Skylake or later. */
#घोषणा DEVICE_ID_SKYLAKE_OR_LATER(did)                                        \
	(((did) == PCI_DEVICE_ID_INTEL_IE31200_HB_8) ||                        \
	 ((did) == PCI_DEVICE_ID_INTEL_IE31200_HB_9) ||                        \
	 (((did) & PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_MASK) ==                 \
	  PCI_DEVICE_ID_INTEL_IE31200_HB_CFL_MASK))

#घोषणा IE31200_DIMMS			4
#घोषणा IE31200_RANKS			8
#घोषणा IE31200_RANKS_PER_CHANNEL	4
#घोषणा IE31200_DIMMS_PER_CHANNEL	2
#घोषणा IE31200_CHANNELS		2

/* Intel IE31200 रेजिस्टर addresses - device 0 function 0 - DRAM Controller */
#घोषणा IE31200_MCHBAR_LOW		0x48
#घोषणा IE31200_MCHBAR_HIGH		0x4c
#घोषणा IE31200_MCHBAR_MASK		GENMASK_ULL(38, 15)
#घोषणा IE31200_MMR_WINDOW_SIZE		BIT(15)

/*
 * Error Status Register (16b)
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
#घोषणा IE31200_ERRSTS			0xc8
#घोषणा IE31200_ERRSTS_UE		BIT(1)
#घोषणा IE31200_ERRSTS_CE		BIT(0)
#घोषणा IE31200_ERRSTS_BITS		(IE31200_ERRSTS_UE | IE31200_ERRSTS_CE)

/*
 * Channel 0 ECC Error Log (64b)
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

#घोषणा IE31200_C0ECCERRLOG			0x40c8
#घोषणा IE31200_C1ECCERRLOG			0x44c8
#घोषणा IE31200_C0ECCERRLOG_SKL			0x4048
#घोषणा IE31200_C1ECCERRLOG_SKL			0x4448
#घोषणा IE31200_ECCERRLOG_CE			BIT(0)
#घोषणा IE31200_ECCERRLOG_UE			BIT(1)
#घोषणा IE31200_ECCERRLOG_RANK_BITS		GENMASK_ULL(28, 27)
#घोषणा IE31200_ECCERRLOG_RANK_SHIFT		27
#घोषणा IE31200_ECCERRLOG_SYNDROME_BITS		GENMASK_ULL(23, 16)
#घोषणा IE31200_ECCERRLOG_SYNDROME_SHIFT	16

#घोषणा IE31200_ECCERRLOG_SYNDROME(log)		   \
	((log & IE31200_ECCERRLOG_SYNDROME_BITS) >> \
	 IE31200_ECCERRLOG_SYNDROME_SHIFT)

#घोषणा IE31200_CAPID0			0xe4
#घोषणा IE31200_CAPID0_PDCD		BIT(4)
#घोषणा IE31200_CAPID0_DDPCD		BIT(6)
#घोषणा IE31200_CAPID0_ECC		BIT(1)

#घोषणा IE31200_MAD_DIMM_0_OFFSET		0x5004
#घोषणा IE31200_MAD_DIMM_0_OFFSET_SKL		0x500C
#घोषणा IE31200_MAD_DIMM_SIZE			GENMASK_ULL(7, 0)
#घोषणा IE31200_MAD_DIMM_A_RANK			BIT(17)
#घोषणा IE31200_MAD_DIMM_A_RANK_SHIFT		17
#घोषणा IE31200_MAD_DIMM_A_RANK_SKL		BIT(10)
#घोषणा IE31200_MAD_DIMM_A_RANK_SKL_SHIFT	10
#घोषणा IE31200_MAD_DIMM_A_WIDTH		BIT(19)
#घोषणा IE31200_MAD_DIMM_A_WIDTH_SHIFT		19
#घोषणा IE31200_MAD_DIMM_A_WIDTH_SKL		GENMASK_ULL(9, 8)
#घोषणा IE31200_MAD_DIMM_A_WIDTH_SKL_SHIFT	8

/* Skylake reports 1GB increments, everything अन्यथा is 256MB */
#घोषणा IE31200_PAGES(n, skl)	\
	(n << (28 + (2 * skl) - PAGE_SHIFT))

अटल पूर्णांक nr_channels;
अटल काष्ठा pci_dev *mci_pdev;
अटल पूर्णांक ie31200_रेजिस्टरed = 1;

काष्ठा ie31200_priv अणु
	व्योम __iomem *winकरोw;
	व्योम __iomem *c0errlog;
	व्योम __iomem *c1errlog;
पूर्ण;

क्रमागत ie31200_chips अणु
	IE31200 = 0,
पूर्ण;

काष्ठा ie31200_dev_info अणु
	स्थिर अक्षर *ctl_name;
पूर्ण;

काष्ठा ie31200_error_info अणु
	u16 errsts;
	u16 errsts2;
	u64 eccerrlog[IE31200_CHANNELS];
पूर्ण;

अटल स्थिर काष्ठा ie31200_dev_info ie31200_devs[] = अणु
	[IE31200] = अणु
		.ctl_name = "IE31200"
	पूर्ण,
पूर्ण;

काष्ठा dimm_data अणु
	u8 size; /* in multiples of 256MB, except Skylake is 1GB */
	u8 dual_rank : 1,
	   x16_width : 2; /* 0 means x8 width */
पूर्ण;

अटल पूर्णांक how_many_channels(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक n_channels;
	अचिन्हित अक्षर capid0_2b; /* 2nd byte of CAPID0 */

	pci_पढ़ो_config_byte(pdev, IE31200_CAPID0 + 1, &capid0_2b);

	/* check PDCD: Dual Channel Disable */
	अगर (capid0_2b & IE31200_CAPID0_PDCD) अणु
		edac_dbg(0, "In single channel mode\n");
		n_channels = 1;
	पूर्ण अन्यथा अणु
		edac_dbg(0, "In dual channel mode\n");
		n_channels = 2;
	पूर्ण

	/* check DDPCD - check अगर both channels are filled */
	अगर (capid0_2b & IE31200_CAPID0_DDPCD)
		edac_dbg(0, "2 DIMMS per channel disabled\n");
	अन्यथा
		edac_dbg(0, "2 DIMMS per channel enabled\n");

	वापस n_channels;
पूर्ण

अटल bool ecc_capable(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित अक्षर capid0_4b; /* 4th byte of CAPID0 */

	pci_पढ़ो_config_byte(pdev, IE31200_CAPID0 + 3, &capid0_4b);
	अगर (capid0_4b & IE31200_CAPID0_ECC)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक eccerrlog_row(u64 log)
अणु
	वापस ((log & IE31200_ECCERRLOG_RANK_BITS) >>
				IE31200_ECCERRLOG_RANK_SHIFT);
पूर्ण

अटल व्योम ie31200_clear_error_info(काष्ठा mem_ctl_info *mci)
अणु
	/*
	 * Clear any error bits.
	 * (Yes, we really clear bits by writing 1 to them.)
	 */
	pci_ग_लिखो_bits16(to_pci_dev(mci->pdev), IE31200_ERRSTS,
			 IE31200_ERRSTS_BITS, IE31200_ERRSTS_BITS);
पूर्ण

अटल व्योम ie31200_get_and_clear_error_info(काष्ठा mem_ctl_info *mci,
					     काष्ठा ie31200_error_info *info)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा ie31200_priv *priv = mci->pvt_info;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because there is no atomic way to पढ़ो all the
	 * रेजिस्टरs at once and the रेजिस्टरs can transition from CE being
	 * overwritten by UE.
	 */
	pci_पढ़ो_config_word(pdev, IE31200_ERRSTS, &info->errsts);
	अगर (!(info->errsts & IE31200_ERRSTS_BITS))
		वापस;

	info->eccerrlog[0] = lo_hi_पढ़ोq(priv->c0errlog);
	अगर (nr_channels == 2)
		info->eccerrlog[1] = lo_hi_पढ़ोq(priv->c1errlog);

	pci_पढ़ो_config_word(pdev, IE31200_ERRSTS, &info->errsts2);

	/*
	 * If the error is the same क्रम both पढ़ोs then the first set
	 * of पढ़ोs is valid.  If there is a change then there is a CE
	 * with no info and the second set of पढ़ोs is valid and
	 * should be UE info.
	 */
	अगर ((info->errsts ^ info->errsts2) & IE31200_ERRSTS_BITS) अणु
		info->eccerrlog[0] = lo_hi_पढ़ोq(priv->c0errlog);
		अगर (nr_channels == 2)
			info->eccerrlog[1] =
				lo_hi_पढ़ोq(priv->c1errlog);
	पूर्ण

	ie31200_clear_error_info(mci);
पूर्ण

अटल व्योम ie31200_process_error_info(काष्ठा mem_ctl_info *mci,
				       काष्ठा ie31200_error_info *info)
अणु
	पूर्णांक channel;
	u64 log;

	अगर (!(info->errsts & IE31200_ERRSTS_BITS))
		वापस;

	अगर ((info->errsts ^ info->errsts2) & IE31200_ERRSTS_BITS) अणु
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, "UE overwrote CE", "");
		info->errsts = info->errsts2;
	पूर्ण

	क्रम (channel = 0; channel < nr_channels; channel++) अणु
		log = info->eccerrlog[channel];
		अगर (log & IE31200_ECCERRLOG_UE) अणु
			edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
					     0, 0, 0,
					     eccerrlog_row(log),
					     channel, -1,
					     "ie31200 UE", "");
		पूर्ण अन्यथा अगर (log & IE31200_ECCERRLOG_CE) अणु
			edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
					     0, 0,
					     IE31200_ECCERRLOG_SYNDROME(log),
					     eccerrlog_row(log),
					     channel, -1,
					     "ie31200 CE", "");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ie31200_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा ie31200_error_info info;

	ie31200_get_and_clear_error_info(mci, &info);
	ie31200_process_error_info(mci, &info);
पूर्ण

अटल व्योम __iomem *ie31200_map_mchbar(काष्ठा pci_dev *pdev)
अणु
	जोड़ अणु
		u64 mchbar;
		काष्ठा अणु
			u32 mchbar_low;
			u32 mchbar_high;
		पूर्ण;
	पूर्ण u;
	व्योम __iomem *winकरोw;

	pci_पढ़ो_config_dword(pdev, IE31200_MCHBAR_LOW, &u.mchbar_low);
	pci_पढ़ो_config_dword(pdev, IE31200_MCHBAR_HIGH, &u.mchbar_high);
	u.mchbar &= IE31200_MCHBAR_MASK;

	अगर (u.mchbar != (resource_माप_प्रकार)u.mchbar) अणु
		ie31200_prपूर्णांकk(KERN_ERR, "mmio space beyond accessible range (0x%llx)\n",
			       (अचिन्हित दीर्घ दीर्घ)u.mchbar);
		वापस शून्य;
	पूर्ण

	winकरोw = ioremap(u.mchbar, IE31200_MMR_WINDOW_SIZE);
	अगर (!winकरोw)
		ie31200_prपूर्णांकk(KERN_ERR, "Cannot map mmio space at 0x%llx\n",
			       (अचिन्हित दीर्घ दीर्घ)u.mchbar);

	वापस winकरोw;
पूर्ण

अटल व्योम __skl_populate_dimm_info(काष्ठा dimm_data *dd, u32 addr_decode,
				     पूर्णांक chan)
अणु
	dd->size = (addr_decode >> (chan << 4)) & IE31200_MAD_DIMM_SIZE;
	dd->dual_rank = (addr_decode & (IE31200_MAD_DIMM_A_RANK_SKL << (chan << 4))) ? 1 : 0;
	dd->x16_width = ((addr_decode & (IE31200_MAD_DIMM_A_WIDTH_SKL << (chan << 4))) >>
				(IE31200_MAD_DIMM_A_WIDTH_SKL_SHIFT + (chan << 4)));
पूर्ण

अटल व्योम __populate_dimm_info(काष्ठा dimm_data *dd, u32 addr_decode,
				 पूर्णांक chan)
अणु
	dd->size = (addr_decode >> (chan << 3)) & IE31200_MAD_DIMM_SIZE;
	dd->dual_rank = (addr_decode & (IE31200_MAD_DIMM_A_RANK << chan)) ? 1 : 0;
	dd->x16_width = (addr_decode & (IE31200_MAD_DIMM_A_WIDTH << chan)) ? 1 : 0;
पूर्ण

अटल व्योम populate_dimm_info(काष्ठा dimm_data *dd, u32 addr_decode, पूर्णांक chan,
			       bool skl)
अणु
	अगर (skl)
		__skl_populate_dimm_info(dd, addr_decode, chan);
	अन्यथा
		__populate_dimm_info(dd, addr_decode, chan);
पूर्ण


अटल पूर्णांक ie31200_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	पूर्णांक i, j, ret;
	काष्ठा mem_ctl_info *mci = शून्य;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा dimm_data dimm_info[IE31200_CHANNELS][IE31200_DIMMS_PER_CHANNEL];
	व्योम __iomem *winकरोw;
	काष्ठा ie31200_priv *priv;
	u32 addr_decode, mad_offset;

	/*
	 * Kaby Lake, Coffee Lake seem to work like Skylake. Please re-visit
	 * this logic when adding new CPU support.
	 */
	bool skl = DEVICE_ID_SKYLAKE_OR_LATER(pdev->device);

	edac_dbg(0, "MC:\n");

	अगर (!ecc_capable(pdev)) अणु
		ie31200_prपूर्णांकk(KERN_INFO, "No ECC support\n");
		वापस -ENODEV;
	पूर्ण

	nr_channels = how_many_channels(pdev);
	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = IE31200_DIMMS;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = nr_channels;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers,
			    माप(काष्ठा ie31200_priv));
	अगर (!mci)
		वापस -ENOMEM;

	winकरोw = ie31200_map_mchbar(pdev);
	अगर (!winकरोw) अणु
		ret = -ENODEV;
		जाओ fail_मुक्त;
	पूर्ण

	edac_dbg(3, "MC: init mci\n");
	mci->pdev = &pdev->dev;
	अगर (skl)
		mci->mtype_cap = MEM_FLAG_DDR4;
	अन्यथा
		mci->mtype_cap = MEM_FLAG_DDR3;
	mci->edac_ctl_cap = EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->mod_name = EDAC_MOD_STR;
	mci->ctl_name = ie31200_devs[dev_idx].ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = ie31200_check;
	mci->ctl_page_to_phys = शून्य;
	priv = mci->pvt_info;
	priv->winकरोw = winकरोw;
	अगर (skl) अणु
		priv->c0errlog = winकरोw + IE31200_C0ECCERRLOG_SKL;
		priv->c1errlog = winकरोw + IE31200_C1ECCERRLOG_SKL;
		mad_offset = IE31200_MAD_DIMM_0_OFFSET_SKL;
	पूर्ण अन्यथा अणु
		priv->c0errlog = winकरोw + IE31200_C0ECCERRLOG;
		priv->c1errlog = winकरोw + IE31200_C1ECCERRLOG;
		mad_offset = IE31200_MAD_DIMM_0_OFFSET;
	पूर्ण

	/* populate DIMM info */
	क्रम (i = 0; i < IE31200_CHANNELS; i++) अणु
		addr_decode = पढ़ोl(winकरोw + mad_offset +
					(i * 4));
		edac_dbg(0, "addr_decode: 0x%x\n", addr_decode);
		क्रम (j = 0; j < IE31200_DIMMS_PER_CHANNEL; j++) अणु
			populate_dimm_info(&dimm_info[i][j], addr_decode, j,
					   skl);
			edac_dbg(0, "size: 0x%x, rank: %d, width: %d\n",
				 dimm_info[i][j].size,
				 dimm_info[i][j].dual_rank,
				 dimm_info[i][j].x16_width);
		पूर्ण
	पूर्ण

	/*
	 * The dram rank boundary (DRB) reg values are boundary addresses
	 * क्रम each DRAM rank with a granularity of 64MB.  DRB regs are
	 * cumulative; the last one will contain the total memory
	 * contained in all ranks.
	 */
	क्रम (i = 0; i < IE31200_DIMMS_PER_CHANNEL; i++) अणु
		क्रम (j = 0; j < IE31200_CHANNELS; j++) अणु
			काष्ठा dimm_info *dimm;
			अचिन्हित दीर्घ nr_pages;

			nr_pages = IE31200_PAGES(dimm_info[j][i].size, skl);
			अगर (nr_pages == 0)
				जारी;

			अगर (dimm_info[j][i].dual_rank) अणु
				nr_pages = nr_pages / 2;
				dimm = edac_get_dimm(mci, (i * 2) + 1, j, 0);
				dimm->nr_pages = nr_pages;
				edac_dbg(0, "set nr pages: 0x%lx\n", nr_pages);
				dimm->grain = 8; /* just a guess */
				अगर (skl)
					dimm->mtype = MEM_DDR4;
				अन्यथा
					dimm->mtype = MEM_DDR3;
				dimm->dtype = DEV_UNKNOWN;
				dimm->edac_mode = EDAC_UNKNOWN;
			पूर्ण
			dimm = edac_get_dimm(mci, i * 2, j, 0);
			dimm->nr_pages = nr_pages;
			edac_dbg(0, "set nr pages: 0x%lx\n", nr_pages);
			dimm->grain = 8; /* same guess */
			अगर (skl)
				dimm->mtype = MEM_DDR4;
			अन्यथा
				dimm->mtype = MEM_DDR3;
			dimm->dtype = DEV_UNKNOWN;
			dimm->edac_mode = EDAC_UNKNOWN;
		पूर्ण
	पूर्ण

	ie31200_clear_error_info(mci);

	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(3, "MC: failed edac_mc_add_mc()\n");
		ret = -ENODEV;
		जाओ fail_unmap;
	पूर्ण

	/* get this far and it's successful */
	edac_dbg(3, "MC: success\n");
	वापस 0;

fail_unmap:
	iounmap(winकरोw);

fail_मुक्त:
	edac_mc_मुक्त(mci);

	वापस ret;
पूर्ण

अटल पूर्णांक ie31200_init_one(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rc;

	edac_dbg(0, "MC:\n");
	अगर (pci_enable_device(pdev) < 0)
		वापस -EIO;
	rc = ie31200_probe1(pdev, ent->driver_data);
	अगर (rc == 0 && !mci_pdev)
		mci_pdev = pci_dev_get(pdev);

	वापस rc;
पूर्ण

अटल व्योम ie31200_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा ie31200_priv *priv;

	edac_dbg(0, "\n");
	pci_dev_put(mci_pdev);
	mci_pdev = शून्य;
	mci = edac_mc_del_mc(&pdev->dev);
	अगर (!mci)
		वापस;
	priv = mci->pvt_info;
	iounmap(priv->winकरोw);
	edac_mc_मुक्त(mci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ie31200_pci_tbl[] = अणु
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_1),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_2),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_3),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_4),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_5),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_6),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_7),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_8),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_9),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_CFL_1),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_CFL_2),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_CFL_3),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_CFL_4),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_CFL_5),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_CFL_6),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_CFL_7),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_CFL_8),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_CFL_9),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु PCI_VEND_DEV(INTEL, IE31200_HB_CFL_10), PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 पूर्ण,
	अणु 0, पूर्ण /* 0 terminated list. */
पूर्ण;
MODULE_DEVICE_TABLE(pci, ie31200_pci_tbl);

अटल काष्ठा pci_driver ie31200_driver = अणु
	.name = EDAC_MOD_STR,
	.probe = ie31200_init_one,
	.हटाओ = ie31200_हटाओ_one,
	.id_table = ie31200_pci_tbl,
पूर्ण;

अटल पूर्णांक __init ie31200_init(व्योम)
अणु
	पूर्णांक pci_rc, i;

	edac_dbg(3, "MC:\n");
	/* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
	opstate_init();

	pci_rc = pci_रेजिस्टर_driver(&ie31200_driver);
	अगर (pci_rc < 0)
		जाओ fail0;

	अगर (!mci_pdev) अणु
		ie31200_रेजिस्टरed = 0;
		क्रम (i = 0; ie31200_pci_tbl[i].venकरोr != 0; i++) अणु
			mci_pdev = pci_get_device(ie31200_pci_tbl[i].venकरोr,
						  ie31200_pci_tbl[i].device,
						  शून्य);
			अगर (mci_pdev)
				अवरोध;
		पूर्ण
		अगर (!mci_pdev) अणु
			edac_dbg(0, "ie31200 pci_get_device fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण
		pci_rc = ie31200_init_one(mci_pdev, &ie31200_pci_tbl[i]);
		अगर (pci_rc < 0) अणु
			edac_dbg(0, "ie31200 init fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण
	पूर्ण
	वापस 0;

fail1:
	pci_unरेजिस्टर_driver(&ie31200_driver);
fail0:
	pci_dev_put(mci_pdev);

	वापस pci_rc;
पूर्ण

अटल व्योम __निकास ie31200_निकास(व्योम)
अणु
	edac_dbg(3, "MC:\n");
	pci_unरेजिस्टर_driver(&ie31200_driver);
	अगर (!ie31200_रेजिस्टरed)
		ie31200_हटाओ_one(mci_pdev);
पूर्ण

module_init(ie31200_init);
module_निकास(ie31200_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jason Baron <jbaron@akamai.com>");
MODULE_DESCRIPTION("MC support for Intel Processor E31200 memory hub controllers");
