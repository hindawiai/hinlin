<शैली गुरु>
/*
 * Intel e7xxx Memory Controller kernel module
 * (C) 2003 Linux Networx (http://lnxi.com)
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * See "enum e7xxx_chips" below क्रम supported chipsets
 *
 * Written by Thayne Harbaugh
 * Based on work by Dan Hollis <goemon at anime करोt net> and others.
 *	http://www.anime.net/~goemon/linux-ecc/
 *
 * Datasheet:
 *	http://www.पूर्णांकel.com/content/www/us/en/chipsets/e7501-chipset-memory-controller-hub-datasheet.hपंचांगl
 *
 * Contributors:
 *	Eric Biederman (Linux Networx)
 *	Tom Zimmerman (Linux Networx)
 *	Jim Garlick (Lawrence Livermore National Lअसल)
 *	Dave Peterson (Lawrence Livermore National Lअसल)
 *	That One Guy (Some other place)
 *	Wang Zhenyu (पूर्णांकel.com)
 *
 * $Id: edac_e7xxx.c,v 1.5.2.9 2005/10/05 00:43:44 dsp_llnl Exp $
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/edac.h>
#समावेश "edac_module.h"

#घोषणा	EDAC_MOD_STR	"e7xxx_edac"

#घोषणा e7xxx_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "e7xxx", fmt, ##arg)

#घोषणा e7xxx_mc_prपूर्णांकk(mci, level, fmt, arg...) \
	edac_mc_chipset_prपूर्णांकk(mci, level, "e7xxx", fmt, ##arg)

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7205_0
#घोषणा PCI_DEVICE_ID_INTEL_7205_0	0x255d
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7205_0 */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7205_1_ERR
#घोषणा PCI_DEVICE_ID_INTEL_7205_1_ERR	0x2551
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7205_1_ERR */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7500_0
#घोषणा PCI_DEVICE_ID_INTEL_7500_0	0x2540
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7500_0 */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7500_1_ERR
#घोषणा PCI_DEVICE_ID_INTEL_7500_1_ERR	0x2541
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7500_1_ERR */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7501_0
#घोषणा PCI_DEVICE_ID_INTEL_7501_0	0x254c
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7501_0 */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7501_1_ERR
#घोषणा PCI_DEVICE_ID_INTEL_7501_1_ERR	0x2541
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7501_1_ERR */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7505_0
#घोषणा PCI_DEVICE_ID_INTEL_7505_0	0x2550
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7505_0 */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7505_1_ERR
#घोषणा PCI_DEVICE_ID_INTEL_7505_1_ERR	0x2551
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7505_1_ERR */

#घोषणा E7XXX_NR_CSROWS		8	/* number of csrows */
#घोषणा E7XXX_NR_DIMMS		8	/* 2 channels, 4 dimms/channel */

/* E7XXX रेजिस्टर addresses - device 0 function 0 */
#घोषणा E7XXX_DRB		0x60	/* DRAM row boundary रेजिस्टर (8b) */
#घोषणा E7XXX_DRA		0x70	/* DRAM row attribute रेजिस्टर (8b) */
					/*
					 * 31   Device width row 7 0=x8 1=x4
					 * 27   Device width row 6
					 * 23   Device width row 5
					 * 19   Device width row 4
					 * 15   Device width row 3
					 * 11   Device width row 2
					 *  7   Device width row 1
					 *  3   Device width row 0
					 */
#घोषणा E7XXX_DRC		0x7C	/* DRAM controller mode reg (32b) */
					/*
					 * 22    Number channels 0=1,1=2
					 * 19:18 DRB Granularity 32/64MB
					 */
#घोषणा E7XXX_TOLM		0xC4	/* DRAM top of low memory reg (16b) */
#घोषणा E7XXX_REMAPBASE		0xC6	/* DRAM remap base address reg (16b) */
#घोषणा E7XXX_REMAPLIMIT	0xC8	/* DRAM remap limit address reg (16b) */

/* E7XXX रेजिस्टर addresses - device 0 function 1 */
#घोषणा E7XXX_DRAM_FERR		0x80	/* DRAM first error रेजिस्टर (8b) */
#घोषणा E7XXX_DRAM_NERR		0x82	/* DRAM next error रेजिस्टर (8b) */
#घोषणा E7XXX_DRAM_CELOG_ADD	0xA0	/* DRAM first correctable memory */
					/*     error address रेजिस्टर (32b) */
					/*
					 * 31:28 Reserved
					 * 27:6  CE address (4k block 33:12)
					 *  5:0  Reserved
					 */
#घोषणा E7XXX_DRAM_UELOG_ADD	0xB0	/* DRAM first uncorrectable memory */
					/*     error address रेजिस्टर (32b) */
					/*
					 * 31:28 Reserved
					 * 27:6  CE address (4k block 33:12)
					 *  5:0  Reserved
					 */
#घोषणा E7XXX_DRAM_CELOG_SYNDROME 0xD0	/* DRAM first correctable memory */
					/*     error syndrome रेजिस्टर (16b) */

क्रमागत e7xxx_chips अणु
	E7500 = 0,
	E7501,
	E7505,
	E7205,
पूर्ण;

काष्ठा e7xxx_pvt अणु
	काष्ठा pci_dev *bridge_ck;
	u32 tolm;
	u32 remapbase;
	u32 remaplimit;
	स्थिर काष्ठा e7xxx_dev_info *dev_info;
पूर्ण;

काष्ठा e7xxx_dev_info अणु
	u16 err_dev;
	स्थिर अक्षर *ctl_name;
पूर्ण;

काष्ठा e7xxx_error_info अणु
	u8 dram_ferr;
	u8 dram_nerr;
	u32 dram_celog_add;
	u16 dram_celog_syndrome;
	u32 dram_uelog_add;
पूर्ण;

अटल काष्ठा edac_pci_ctl_info *e7xxx_pci;

अटल स्थिर काष्ठा e7xxx_dev_info e7xxx_devs[] = अणु
	[E7500] = अणु
		.err_dev = PCI_DEVICE_ID_INTEL_7500_1_ERR,
		.ctl_name = "E7500"पूर्ण,
	[E7501] = अणु
		.err_dev = PCI_DEVICE_ID_INTEL_7501_1_ERR,
		.ctl_name = "E7501"पूर्ण,
	[E7505] = अणु
		.err_dev = PCI_DEVICE_ID_INTEL_7505_1_ERR,
		.ctl_name = "E7505"पूर्ण,
	[E7205] = अणु
		.err_dev = PCI_DEVICE_ID_INTEL_7205_1_ERR,
		.ctl_name = "E7205"पूर्ण,
पूर्ण;

/* FIXME - is this valid क्रम both SECDED and S4ECD4ED? */
अटल अंतरभूत पूर्णांक e7xxx_find_channel(u16 syndrome)
अणु
	edac_dbg(3, "\n");

	अगर ((syndrome & 0xff00) == 0)
		वापस 0;

	अगर ((syndrome & 0x00ff) == 0)
		वापस 1;

	अगर ((syndrome & 0xf000) == 0 || (syndrome & 0x0f00) == 0)
		वापस 0;

	वापस 1;
पूर्ण

अटल अचिन्हित दीर्घ ctl_page_to_phys(काष्ठा mem_ctl_info *mci,
				अचिन्हित दीर्घ page)
अणु
	u32 remap;
	काष्ठा e7xxx_pvt *pvt = (काष्ठा e7xxx_pvt *)mci->pvt_info;

	edac_dbg(3, "\n");

	अगर ((page < pvt->tolm) ||
		((page >= 0x100000) && (page < pvt->remapbase)))
		वापस page;

	remap = (page - pvt->tolm) + pvt->remapbase;

	अगर (remap < pvt->remaplimit)
		वापस remap;

	e7xxx_prपूर्णांकk(KERN_ERR, "Invalid page %lx - out of range\n", page);
	वापस pvt->tolm - 1;
पूर्ण

अटल व्योम process_ce(काष्ठा mem_ctl_info *mci, काष्ठा e7xxx_error_info *info)
अणु
	u32 error_1b, page;
	u16 syndrome;
	पूर्णांक row;
	पूर्णांक channel;

	edac_dbg(3, "\n");
	/* पढ़ो the error address */
	error_1b = info->dram_celog_add;
	/* FIXME - should use PAGE_SHIFT */
	page = error_1b >> 6;	/* convert the address to 4k page */
	/* पढ़ो the syndrome */
	syndrome = info->dram_celog_syndrome;
	/* FIXME - check क्रम -1 */
	row = edac_mc_find_csrow_by_page(mci, page);
	/* convert syndrome to channel */
	channel = e7xxx_find_channel(syndrome);
	edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1, page, 0, syndrome,
			     row, channel, -1, "e7xxx CE", "");
पूर्ण

अटल व्योम process_ce_no_info(काष्ठा mem_ctl_info *mci)
अणु
	edac_dbg(3, "\n");
	edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1, 0, 0, 0, -1, -1, -1,
			     "e7xxx CE log register overflow", "");
पूर्ण

अटल व्योम process_ue(काष्ठा mem_ctl_info *mci, काष्ठा e7xxx_error_info *info)
अणु
	u32 error_2b, block_page;
	पूर्णांक row;

	edac_dbg(3, "\n");
	/* पढ़ो the error address */
	error_2b = info->dram_uelog_add;
	/* FIXME - should use PAGE_SHIFT */
	block_page = error_2b >> 6;	/* convert to 4k address */
	row = edac_mc_find_csrow_by_page(mci, block_page);

	edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, block_page, 0, 0,
			     row, -1, -1, "e7xxx UE", "");
पूर्ण

अटल व्योम process_ue_no_info(काष्ठा mem_ctl_info *mci)
अणु
	edac_dbg(3, "\n");

	edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0, -1, -1, -1,
			     "e7xxx UE log register overflow", "");
पूर्ण

अटल व्योम e7xxx_get_error_info(काष्ठा mem_ctl_info *mci,
				 काष्ठा e7xxx_error_info *info)
अणु
	काष्ठा e7xxx_pvt *pvt;

	pvt = (काष्ठा e7xxx_pvt *)mci->pvt_info;
	pci_पढ़ो_config_byte(pvt->bridge_ck, E7XXX_DRAM_FERR, &info->dram_ferr);
	pci_पढ़ो_config_byte(pvt->bridge_ck, E7XXX_DRAM_NERR, &info->dram_nerr);

	अगर ((info->dram_ferr & 1) || (info->dram_nerr & 1)) अणु
		pci_पढ़ो_config_dword(pvt->bridge_ck, E7XXX_DRAM_CELOG_ADD,
				&info->dram_celog_add);
		pci_पढ़ो_config_word(pvt->bridge_ck,
				E7XXX_DRAM_CELOG_SYNDROME,
				&info->dram_celog_syndrome);
	पूर्ण

	अगर ((info->dram_ferr & 2) || (info->dram_nerr & 2))
		pci_पढ़ो_config_dword(pvt->bridge_ck, E7XXX_DRAM_UELOG_ADD,
				&info->dram_uelog_add);

	अगर (info->dram_ferr & 3)
		pci_ग_लिखो_bits8(pvt->bridge_ck, E7XXX_DRAM_FERR, 0x03, 0x03);

	अगर (info->dram_nerr & 3)
		pci_ग_लिखो_bits8(pvt->bridge_ck, E7XXX_DRAM_NERR, 0x03, 0x03);
पूर्ण

अटल पूर्णांक e7xxx_process_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा e7xxx_error_info *info,
				पूर्णांक handle_errors)
अणु
	पूर्णांक error_found;

	error_found = 0;

	/* decode and report errors */
	अगर (info->dram_ferr & 1) अणु	/* check first error correctable */
		error_found = 1;

		अगर (handle_errors)
			process_ce(mci, info);
	पूर्ण

	अगर (info->dram_ferr & 2) अणु	/* check first error uncorrectable */
		error_found = 1;

		अगर (handle_errors)
			process_ue(mci, info);
	पूर्ण

	अगर (info->dram_nerr & 1) अणु	/* check next error correctable */
		error_found = 1;

		अगर (handle_errors) अणु
			अगर (info->dram_ferr & 1)
				process_ce_no_info(mci);
			अन्यथा
				process_ce(mci, info);
		पूर्ण
	पूर्ण

	अगर (info->dram_nerr & 2) अणु	/* check next error uncorrectable */
		error_found = 1;

		अगर (handle_errors) अणु
			अगर (info->dram_ferr & 2)
				process_ue_no_info(mci);
			अन्यथा
				process_ue(mci, info);
		पूर्ण
	पूर्ण

	वापस error_found;
पूर्ण

अटल व्योम e7xxx_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा e7xxx_error_info info;

	e7xxx_get_error_info(mci, &info);
	e7xxx_process_error_info(mci, &info, 1);
पूर्ण

/* Return 1 अगर dual channel mode is active.  Else वापस 0. */
अटल अंतरभूत पूर्णांक dual_channel_active(u32 drc, पूर्णांक dev_idx)
अणु
	वापस (dev_idx == E7501) ? ((drc >> 22) & 0x1) : 1;
पूर्ण

/* Return DRB granularity (0=32mb, 1=64mb). */
अटल अंतरभूत पूर्णांक drb_granularity(u32 drc, पूर्णांक dev_idx)
अणु
	/* only e7501 can be single channel */
	वापस (dev_idx == E7501) ? ((drc >> 18) & 0x3) : 1;
पूर्ण

अटल व्योम e7xxx_init_csrows(काष्ठा mem_ctl_info *mci, काष्ठा pci_dev *pdev,
			पूर्णांक dev_idx, u32 drc)
अणु
	अचिन्हित दीर्घ last_cumul_size;
	पूर्णांक index, j;
	u8 value;
	u32 dra, cumul_size, nr_pages;
	पूर्णांक drc_chan, drc_drbg, drc_ddim, mem_dev;
	काष्ठा csrow_info *csrow;
	काष्ठा dimm_info *dimm;
	क्रमागत edac_type edac_mode;

	pci_पढ़ो_config_dword(pdev, E7XXX_DRA, &dra);
	drc_chan = dual_channel_active(drc, dev_idx);
	drc_drbg = drb_granularity(drc, dev_idx);
	drc_ddim = (drc >> 20) & 0x3;
	last_cumul_size = 0;

	/* The dram row boundary (DRB) reg values are boundary address
	 * क्रम each DRAM row with a granularity of 32 or 64MB (single/dual
	 * channel operation).  DRB regs are cumulative; thereक्रमe DRB7 will
	 * contain the total memory contained in all eight rows.
	 */
	क्रम (index = 0; index < mci->nr_csrows; index++) अणु
		/* mem_dev 0=x8, 1=x4 */
		mem_dev = (dra >> (index * 4 + 3)) & 0x1;
		csrow = mci->csrows[index];

		pci_पढ़ो_config_byte(pdev, E7XXX_DRB + index, &value);
		/* convert a 64 or 32 MiB DRB to a page size. */
		cumul_size = value << (25 + drc_drbg - PAGE_SHIFT);
		edac_dbg(3, "(%d) cumul_size 0x%x\n", index, cumul_size);
		अगर (cumul_size == last_cumul_size)
			जारी;	/* not populated */

		csrow->first_page = last_cumul_size;
		csrow->last_page = cumul_size - 1;
		nr_pages = cumul_size - last_cumul_size;
		last_cumul_size = cumul_size;

		/*
		* अगर single channel or x8 devices then SECDED
		* अगर dual channel and x4 then S4ECD4ED
		*/
		अगर (drc_ddim) अणु
			अगर (drc_chan && mem_dev) अणु
				edac_mode = EDAC_S4ECD4ED;
				mci->edac_cap |= EDAC_FLAG_S4ECD4ED;
			पूर्ण अन्यथा अणु
				edac_mode = EDAC_SECDED;
				mci->edac_cap |= EDAC_FLAG_SECDED;
			पूर्ण
		पूर्ण अन्यथा
			edac_mode = EDAC_NONE;

		क्रम (j = 0; j < drc_chan + 1; j++) अणु
			dimm = csrow->channels[j]->dimm;

			dimm->nr_pages = nr_pages / (drc_chan + 1);
			dimm->grain = 1 << 12;	/* 4KiB - resolution of CELOG */
			dimm->mtype = MEM_RDDR;	/* only one type supported */
			dimm->dtype = mem_dev ? DEV_X4 : DEV_X8;
			dimm->edac_mode = edac_mode;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक e7xxx_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	u16 pci_data;
	काष्ठा mem_ctl_info *mci = शून्य;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा e7xxx_pvt *pvt = शून्य;
	u32 drc;
	पूर्णांक drc_chan;
	काष्ठा e7xxx_error_info discard;

	edac_dbg(0, "mci\n");

	pci_पढ़ो_config_dword(pdev, E7XXX_DRC, &drc);

	drc_chan = dual_channel_active(drc, dev_idx);
	/*
	 * According with the datasheet, this device has a maximum of
	 * 4 DIMMS per channel, either single-rank or dual-rank. So, the
	 * total amount of dimms is 8 (E7XXX_NR_DIMMS).
	 * That means that the DIMM is mapped as CSROWs, and the channel
	 * will map the rank. So, an error to either channel should be
	 * attributed to the same dimm.
	 */
	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = E7XXX_NR_CSROWS;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = drc_chan + 1;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, माप(*pvt));
	अगर (mci == शून्य)
		वापस -ENOMEM;

	edac_dbg(3, "init mci\n");
	mci->mtype_cap = MEM_FLAG_RDDR;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_SECDED |
		EDAC_FLAG_S4ECD4ED;
	/* FIXME - what अगर dअगरferent memory types are in dअगरferent csrows? */
	mci->mod_name = EDAC_MOD_STR;
	mci->pdev = &pdev->dev;
	edac_dbg(3, "init pvt\n");
	pvt = (काष्ठा e7xxx_pvt *)mci->pvt_info;
	pvt->dev_info = &e7xxx_devs[dev_idx];
	pvt->bridge_ck = pci_get_device(PCI_VENDOR_ID_INTEL,
					pvt->dev_info->err_dev, pvt->bridge_ck);

	अगर (!pvt->bridge_ck) अणु
		e7xxx_prपूर्णांकk(KERN_ERR, "error reporting device not found:"
			"vendor %x device 0x%x (broken BIOS?)\n",
			PCI_VENDOR_ID_INTEL, e7xxx_devs[dev_idx].err_dev);
		जाओ fail0;
	पूर्ण

	edac_dbg(3, "more mci init\n");
	mci->ctl_name = pvt->dev_info->ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = e7xxx_check;
	mci->ctl_page_to_phys = ctl_page_to_phys;
	e7xxx_init_csrows(mci, pdev, dev_idx, drc);
	mci->edac_cap |= EDAC_FLAG_NONE;
	edac_dbg(3, "tolm, remapbase, remaplimit\n");
	/* load the top of low memory, remap base, and remap limit vars */
	pci_पढ़ो_config_word(pdev, E7XXX_TOLM, &pci_data);
	pvt->tolm = ((u32) pci_data) << 4;
	pci_पढ़ो_config_word(pdev, E7XXX_REMAPBASE, &pci_data);
	pvt->remapbase = ((u32) pci_data) << 14;
	pci_पढ़ो_config_word(pdev, E7XXX_REMAPLIMIT, &pci_data);
	pvt->remaplimit = ((u32) pci_data) << 14;
	e7xxx_prपूर्णांकk(KERN_INFO,
		"tolm = %x, remapbase = %x, remaplimit = %x\n", pvt->tolm,
		pvt->remapbase, pvt->remaplimit);

	/* clear any pending errors, or initial state bits */
	e7xxx_get_error_info(mci, &discard);

	/* Here we assume that we will never see multiple instances of this
	 * type of memory controller.  The ID is thereक्रमe hardcoded to 0.
	 */
	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(3, "failed edac_mc_add_mc()\n");
		जाओ fail1;
	पूर्ण

	/* allocating generic PCI control info */
	e7xxx_pci = edac_pci_create_generic_ctl(&pdev->dev, EDAC_MOD_STR);
	अगर (!e7xxx_pci) अणु
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
	pci_dev_put(pvt->bridge_ck);

fail0:
	edac_mc_मुक्त(mci);

	वापस -ENODEV;
पूर्ण

/* वापसs count (>= 0), or negative on error */
अटल पूर्णांक e7xxx_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	edac_dbg(0, "\n");

	/* wake up and enable device */
	वापस pci_enable_device(pdev) ?
		-EIO : e7xxx_probe1(pdev, ent->driver_data);
पूर्ण

अटल व्योम e7xxx_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा e7xxx_pvt *pvt;

	edac_dbg(0, "\n");

	अगर (e7xxx_pci)
		edac_pci_release_generic_ctl(e7xxx_pci);

	अगर ((mci = edac_mc_del_mc(&pdev->dev)) == शून्य)
		वापस;

	pvt = (काष्ठा e7xxx_pvt *)mci->pvt_info;
	pci_dev_put(pvt->bridge_ck);
	edac_mc_मुक्त(mci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id e7xxx_pci_tbl[] = अणु
	अणु
	 PCI_VEND_DEV(INTEL, 7205_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7205पूर्ण,
	अणु
	 PCI_VEND_DEV(INTEL, 7500_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7500पूर्ण,
	अणु
	 PCI_VEND_DEV(INTEL, 7501_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7501पूर्ण,
	अणु
	 PCI_VEND_DEV(INTEL, 7505_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7505पूर्ण,
	अणु
	 0,
	 पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, e7xxx_pci_tbl);

अटल काष्ठा pci_driver e7xxx_driver = अणु
	.name = EDAC_MOD_STR,
	.probe = e7xxx_init_one,
	.हटाओ = e7xxx_हटाओ_one,
	.id_table = e7xxx_pci_tbl,
पूर्ण;

अटल पूर्णांक __init e7xxx_init(व्योम)
अणु
       /* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
       opstate_init();

	वापस pci_रेजिस्टर_driver(&e7xxx_driver);
पूर्ण

अटल व्योम __निकास e7xxx_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&e7xxx_driver);
पूर्ण

module_init(e7xxx_init);
module_निकास(e7xxx_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Linux Networx (http://lnxi.com) Thayne Harbaugh et al\n"
		"Based on.work by Dan Hollis et al");
MODULE_DESCRIPTION("MC support for Intel e7xxx memory controllers");
module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
