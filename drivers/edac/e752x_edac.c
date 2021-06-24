<शैली गुरु>
/*
 * Intel e752x Memory Controller kernel module
 * (C) 2004 Linux Networx (http://lnxi.com)
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Implement support क्रम the e7520, E7525, e7320 and i3100 memory controllers.
 *
 * Datasheets:
 *	https://www.पूर्णांकel.in/content/www/in/en/chipsets/e7525-memory-controller-hub-datasheet.hपंचांगl
 *	ftp://करोwnload.पूर्णांकel.com/design/पूर्णांकarch/datashts/31345803.pdf
 *
 * Written by Tom Zimmerman
 *
 * Contributors:
 * 	Thayne Harbaugh at realmsys.com (?)
 * 	Wang Zhenyu at पूर्णांकel.com
 * 	Dave Jiang at mvista.com
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/edac.h>
#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR	"e752x_edac"

अटल पूर्णांक report_non_memory_errors;
अटल पूर्णांक क्रमce_function_unhide;
अटल पूर्णांक sysbus_parity = -1;

अटल काष्ठा edac_pci_ctl_info *e752x_pci;

#घोषणा e752x_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "e752x", fmt, ##arg)

#घोषणा e752x_mc_prपूर्णांकk(mci, level, fmt, arg...) \
	edac_mc_chipset_prपूर्णांकk(mci, level, "e752x", fmt, ##arg)

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7520_0
#घोषणा PCI_DEVICE_ID_INTEL_7520_0      0x3590
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7520_0      */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7520_1_ERR
#घोषणा PCI_DEVICE_ID_INTEL_7520_1_ERR  0x3591
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7520_1_ERR  */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7525_0
#घोषणा PCI_DEVICE_ID_INTEL_7525_0      0x359E
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7525_0      */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7525_1_ERR
#घोषणा PCI_DEVICE_ID_INTEL_7525_1_ERR  0x3593
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7525_1_ERR  */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7320_0
#घोषणा PCI_DEVICE_ID_INTEL_7320_0	0x3592
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7320_0 */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_7320_1_ERR
#घोषणा PCI_DEVICE_ID_INTEL_7320_1_ERR	0x3593
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_7320_1_ERR */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_3100_0
#घोषणा PCI_DEVICE_ID_INTEL_3100_0	0x35B0
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_3100_0 */

#अगर_अघोषित PCI_DEVICE_ID_INTEL_3100_1_ERR
#घोषणा PCI_DEVICE_ID_INTEL_3100_1_ERR	0x35B1
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_3100_1_ERR */

#घोषणा E752X_NR_CSROWS		8	/* number of csrows */

/* E752X रेजिस्टर addresses - device 0 function 0 */
#घोषणा E752X_MCHSCRB		0x52	/* Memory Scrub रेजिस्टर (16b) */
					/*
					 * 6:5     Scrub Completion Count
					 * 3:2     Scrub Rate (i3100 only)
					 *      01=fast 10=normal
					 * 1:0     Scrub Mode enable
					 *      00=off 10=on
					 */
#घोषणा E752X_DRB		0x60	/* DRAM row boundary रेजिस्टर (8b) */
#घोषणा E752X_DRA		0x70	/* DRAM row attribute रेजिस्टर (8b) */
					/*
					 * 31:30   Device width row 7
					 *      01=x8 10=x4 11=x8 DDR2
					 * 27:26   Device width row 6
					 * 23:22   Device width row 5
					 * 19:20   Device width row 4
					 * 15:14   Device width row 3
					 * 11:10   Device width row 2
					 *  7:6    Device width row 1
					 *  3:2    Device width row 0
					 */
#घोषणा E752X_DRC		0x7C	/* DRAM controller mode reg (32b) */
					/* FIXME:IS THIS RIGHT? */
					/*
					 * 22    Number channels 0=1,1=2
					 * 19:18 DRB Granularity 32/64MB
					 */
#घोषणा E752X_DRM		0x80	/* Dimm mapping रेजिस्टर */
#घोषणा E752X_DDRCSR		0x9A	/* DDR control and status reg (16b) */
					/*
					 * 14:12 1 single A, 2 single B, 3 dual
					 */
#घोषणा E752X_TOLM		0xC4	/* DRAM top of low memory reg (16b) */
#घोषणा E752X_REMAPBASE		0xC6	/* DRAM remap base address reg (16b) */
#घोषणा E752X_REMAPLIMIT	0xC8	/* DRAM remap limit address reg (16b) */
#घोषणा E752X_REMAPOFFSET	0xCA	/* DRAM remap limit offset reg (16b) */

/* E752X रेजिस्टर addresses - device 0 function 1 */
#घोषणा E752X_FERR_GLOBAL	0x40	/* Global first error रेजिस्टर (32b) */
#घोषणा E752X_NERR_GLOBAL	0x44	/* Global next error रेजिस्टर (32b) */
#घोषणा E752X_HI_FERR		0x50	/* Hub पूर्णांकerface first error reg (8b) */
#घोषणा E752X_HI_NERR		0x52	/* Hub पूर्णांकerface next error reg (8b) */
#घोषणा E752X_HI_ERRMASK	0x54	/* Hub पूर्णांकerface error mask reg (8b) */
#घोषणा E752X_HI_SMICMD		0x5A	/* Hub पूर्णांकerface SMI command reg (8b) */
#घोषणा E752X_SYSBUS_FERR	0x60	/* System buss first error reg (16b) */
#घोषणा E752X_SYSBUS_NERR	0x62	/* System buss next error reg (16b) */
#घोषणा E752X_SYSBUS_ERRMASK	0x64	/* System buss error mask reg (16b) */
#घोषणा E752X_SYSBUS_SMICMD	0x6A	/* System buss SMI command reg (16b) */
#घोषणा E752X_BUF_FERR		0x70	/* Memory buffer first error reg (8b) */
#घोषणा E752X_BUF_NERR		0x72	/* Memory buffer next error reg (8b) */
#घोषणा E752X_BUF_ERRMASK	0x74	/* Memory buffer error mask reg (8b) */
#घोषणा E752X_BUF_SMICMD	0x7A	/* Memory buffer SMI cmd reg (8b) */
#घोषणा E752X_DRAM_FERR		0x80	/* DRAM first error रेजिस्टर (16b) */
#घोषणा E752X_DRAM_NERR		0x82	/* DRAM next error रेजिस्टर (16b) */
#घोषणा E752X_DRAM_ERRMASK	0x84	/* DRAM error mask रेजिस्टर (8b) */
#घोषणा E752X_DRAM_SMICMD	0x8A	/* DRAM SMI command रेजिस्टर (8b) */
#घोषणा E752X_DRAM_RETR_ADD	0xAC	/* DRAM Retry address रेजिस्टर (32b) */
#घोषणा E752X_DRAM_SEC1_ADD	0xA0	/* DRAM first correctable memory */
					/*     error address रेजिस्टर (32b) */
					/*
					 * 31    Reserved
					 * 30:2  CE address (64 byte block 34:6
					 * 1     Reserved
					 * 0     HiLoCS
					 */
#घोषणा E752X_DRAM_SEC2_ADD	0xC8	/* DRAM first correctable memory */
					/*     error address रेजिस्टर (32b) */
					/*
					 * 31    Reserved
					 * 30:2  CE address (64 byte block 34:6)
					 * 1     Reserved
					 * 0     HiLoCS
					 */
#घोषणा E752X_DRAM_DED_ADD	0xA4	/* DRAM first uncorrectable memory */
					/*     error address रेजिस्टर (32b) */
					/*
					 * 31    Reserved
					 * 30:2  CE address (64 byte block 34:6)
					 * 1     Reserved
					 * 0     HiLoCS
					 */
#घोषणा E752X_DRAM_SCRB_ADD	0xA8	/* DRAM 1st uncorrectable scrub mem */
					/*     error address रेजिस्टर (32b) */
					/*
					 * 31    Reserved
					 * 30:2  CE address (64 byte block 34:6
					 * 1     Reserved
					 * 0     HiLoCS
					 */
#घोषणा E752X_DRAM_SEC1_SYNDROME 0xC4	/* DRAM first correctable memory */
					/*     error syndrome रेजिस्टर (16b) */
#घोषणा E752X_DRAM_SEC2_SYNDROME 0xC6	/* DRAM second correctable memory */
					/*     error syndrome रेजिस्टर (16b) */
#घोषणा E752X_DEVPRES1		0xF4	/* Device Present 1 रेजिस्टर (8b) */

/* 3100 IMCH specअगरic रेजिस्टर addresses - device 0 function 1 */
#घोषणा I3100_NSI_FERR		0x48	/* NSI first error reg (32b) */
#घोषणा I3100_NSI_NERR		0x4C	/* NSI next error reg (32b) */
#घोषणा I3100_NSI_SMICMD	0x54	/* NSI SMI command रेजिस्टर (32b) */
#घोषणा I3100_NSI_EMASK		0x90	/* NSI error mask रेजिस्टर (32b) */

/* ICH5R रेजिस्टर addresses - device 30 function 0 */
#घोषणा ICH5R_PCI_STAT		0x06	/* PCI status रेजिस्टर (16b) */
#घोषणा ICH5R_PCI_2ND_STAT	0x1E	/* PCI status secondary reg (16b) */
#घोषणा ICH5R_PCI_BRIDGE_CTL	0x3E	/* PCI bridge control रेजिस्टर (16b) */

क्रमागत e752x_chips अणु
	E7520 = 0,
	E7525 = 1,
	E7320 = 2,
	I3100 = 3
पूर्ण;

/*
 * Those chips Support single-rank and dual-rank memories only.
 *
 * On e752x chips, the odd rows are present only on dual-rank memories.
 * Dividing the rank by two will provide the dimm#
 *
 * i3100 MC has a dअगरferent mapping: it supports only 4 ranks.
 *
 * The mapping is (from 1 to n):
 *	slot	   single-ranked	द्विगुन-ranked
 *	dimm #1 -> rank #4		NA
 *	dimm #2 -> rank #3		NA
 *	dimm #3 -> rank #2		Ranks 2 and 3
 *	dimm #4 -> rank $1		Ranks 1 and 4
 *
 * FIXME: The current mapping क्रम i3100 considers that it supports up to 8
 *	  ranks/chanel, but datasheet says that the MC supports only 4 ranks.
 */

काष्ठा e752x_pvt अणु
	काष्ठा pci_dev *dev_d0f0;
	काष्ठा pci_dev *dev_d0f1;
	u32 tolm;
	u32 remapbase;
	u32 remaplimit;
	पूर्णांक mc_symmetric;
	u8 map[8];
	पूर्णांक map_type;
	स्थिर काष्ठा e752x_dev_info *dev_info;
पूर्ण;

काष्ठा e752x_dev_info अणु
	u16 err_dev;
	u16 ctl_dev;
	स्थिर अक्षर *ctl_name;
पूर्ण;

काष्ठा e752x_error_info अणु
	u32 ferr_global;
	u32 nerr_global;
	u32 nsi_ferr;	/* 3100 only */
	u32 nsi_nerr;	/* 3100 only */
	u8 hi_ferr;	/* all but 3100 */
	u8 hi_nerr;	/* all but 3100 */
	u16 sysbus_ferr;
	u16 sysbus_nerr;
	u8 buf_ferr;
	u8 buf_nerr;
	u16 dram_ferr;
	u16 dram_nerr;
	u32 dram_sec1_add;
	u32 dram_sec2_add;
	u16 dram_sec1_syndrome;
	u16 dram_sec2_syndrome;
	u32 dram_ded_add;
	u32 dram_scrb_add;
	u32 dram_retr_add;
पूर्ण;

अटल स्थिर काष्ठा e752x_dev_info e752x_devs[] = अणु
	[E7520] = अणु
		.err_dev = PCI_DEVICE_ID_INTEL_7520_1_ERR,
		.ctl_dev = PCI_DEVICE_ID_INTEL_7520_0,
		.ctl_name = "E7520"पूर्ण,
	[E7525] = अणु
		.err_dev = PCI_DEVICE_ID_INTEL_7525_1_ERR,
		.ctl_dev = PCI_DEVICE_ID_INTEL_7525_0,
		.ctl_name = "E7525"पूर्ण,
	[E7320] = अणु
		.err_dev = PCI_DEVICE_ID_INTEL_7320_1_ERR,
		.ctl_dev = PCI_DEVICE_ID_INTEL_7320_0,
		.ctl_name = "E7320"पूर्ण,
	[I3100] = अणु
		.err_dev = PCI_DEVICE_ID_INTEL_3100_1_ERR,
		.ctl_dev = PCI_DEVICE_ID_INTEL_3100_0,
		.ctl_name = "3100"पूर्ण,
पूर्ण;

/* Valid scrub rates क्रम the e752x/3100 hardware memory scrubber. We
 * map the scrubbing bandwidth to a hardware रेजिस्टर value. The 'set'
 * operation finds the 'matching or higher value'.  Note that scrubbing
 * on the e752x can only be enabled/disabled.  The 3100 supports
 * a normal and fast mode.
 */

#घोषणा SDRATE_EOT 0xFFFFFFFF

काष्ठा scrubrate अणु
	u32 bandwidth;	/* bandwidth consumed by scrubbing in bytes/sec */
	u16 scrubval;	/* रेजिस्टर value क्रम scrub rate */
पूर्ण;

/* Rate below assumes same perक्रमmance as i3100 using PC3200 DDR2 in
 * normal mode.  e752x bridges करोn't support choosing normal or fast mode,
 * so the scrubbing bandwidth value isn't all that important - scrubbing is
 * either on or off.
 */
अटल स्थिर काष्ठा scrubrate scrubrates_e752x[] = अणु
	अणु0,		0x00पूर्ण,	/* Scrubbing Off */
	अणु500000,	0x02पूर्ण,	/* Scrubbing On */
	अणुSDRATE_EOT,	0x00पूर्ण	/* End of Table */
पूर्ण;

/* Fast mode: 2 GByte PC3200 DDR2 scrubbed in 33s = 63161283 bytes/s
 * Normal mode: 125 (32000 / 256) बार slower than fast mode.
 */
अटल स्थिर काष्ठा scrubrate scrubrates_i3100[] = अणु
	अणु0,		0x00पूर्ण,	/* Scrubbing Off */
	अणु500000,	0x0aपूर्ण,	/* Normal mode - 32k घड़ीs */
	अणु62500000,	0x06पूर्ण,	/* Fast mode - 256 घड़ीs */
	अणुSDRATE_EOT,	0x00पूर्ण	/* End of Table */
पूर्ण;

अटल अचिन्हित दीर्घ ctl_page_to_phys(काष्ठा mem_ctl_info *mci,
				अचिन्हित दीर्घ page)
अणु
	u32 remap;
	काष्ठा e752x_pvt *pvt = (काष्ठा e752x_pvt *)mci->pvt_info;

	edac_dbg(3, "\n");

	अगर (page < pvt->tolm)
		वापस page;

	अगर ((page >= 0x100000) && (page < pvt->remapbase))
		वापस page;

	remap = (page - pvt->tolm) + pvt->remapbase;

	अगर (remap < pvt->remaplimit)
		वापस remap;

	e752x_prपूर्णांकk(KERN_ERR, "Invalid page %lx - out of range\n", page);
	वापस pvt->tolm - 1;
पूर्ण

अटल व्योम करो_process_ce(काष्ठा mem_ctl_info *mci, u16 error_one,
			u32 sec1_add, u16 sec1_syndrome)
अणु
	u32 page;
	पूर्णांक row;
	पूर्णांक channel;
	पूर्णांक i;
	काष्ठा e752x_pvt *pvt = (काष्ठा e752x_pvt *)mci->pvt_info;

	edac_dbg(3, "\n");

	/* convert the addr to 4k page */
	page = sec1_add >> (PAGE_SHIFT - 4);

	/* FIXME - check क्रम -1 */
	अगर (pvt->mc_symmetric) अणु
		/* chip select are bits 14 & 13 */
		row = ((page >> 1) & 3);
		e752x_prपूर्णांकk(KERN_WARNING,
			"Test row %d Table %d %d %d %d %d %d %d %d\n", row,
			pvt->map[0], pvt->map[1], pvt->map[2], pvt->map[3],
			pvt->map[4], pvt->map[5], pvt->map[6],
			pvt->map[7]);

		/* test क्रम channel remapping */
		क्रम (i = 0; i < 8; i++) अणु
			अगर (pvt->map[i] == row)
				अवरोध;
		पूर्ण

		e752x_prपूर्णांकk(KERN_WARNING, "Test computed row %d\n", i);

		अगर (i < 8)
			row = i;
		अन्यथा
			e752x_mc_prपूर्णांकk(mci, KERN_WARNING,
					"row %d not found in remap table\n",
					row);
	पूर्ण अन्यथा
		row = edac_mc_find_csrow_by_page(mci, page);

	/* 0 = channel A, 1 = channel B */
	channel = !(error_one & 1);

	/* e752x mc पढ़ोs 34:6 of the DRAM linear address */
	edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
			     page, offset_in_page(sec1_add << 4), sec1_syndrome,
			     row, channel, -1,
			     "e752x CE", "");
पूर्ण

अटल अंतरभूत व्योम process_ce(काष्ठा mem_ctl_info *mci, u16 error_one,
			u32 sec1_add, u16 sec1_syndrome, पूर्णांक *error_found,
			पूर्णांक handle_error)
अणु
	*error_found = 1;

	अगर (handle_error)
		करो_process_ce(mci, error_one, sec1_add, sec1_syndrome);
पूर्ण

अटल व्योम करो_process_ue(काष्ठा mem_ctl_info *mci, u16 error_one,
			u32 ded_add, u32 scrb_add)
अणु
	u32 error_2b, block_page;
	पूर्णांक row;
	काष्ठा e752x_pvt *pvt = (काष्ठा e752x_pvt *)mci->pvt_info;

	edac_dbg(3, "\n");

	अगर (error_one & 0x0202) अणु
		error_2b = ded_add;

		/* convert to 4k address */
		block_page = error_2b >> (PAGE_SHIFT - 4);

		row = pvt->mc_symmetric ?
		/* chip select are bits 14 & 13 */
			((block_page >> 1) & 3) :
			edac_mc_find_csrow_by_page(mci, block_page);

		/* e752x mc पढ़ोs 34:6 of the DRAM linear address */
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
					block_page,
					offset_in_page(error_2b << 4), 0,
					 row, -1, -1,
					"e752x UE from Read", "");

	पूर्ण
	अगर (error_one & 0x0404) अणु
		error_2b = scrb_add;

		/* convert to 4k address */
		block_page = error_2b >> (PAGE_SHIFT - 4);

		row = pvt->mc_symmetric ?
		/* chip select are bits 14 & 13 */
			((block_page >> 1) & 3) :
			edac_mc_find_csrow_by_page(mci, block_page);

		/* e752x mc पढ़ोs 34:6 of the DRAM linear address */
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
					block_page,
					offset_in_page(error_2b << 4), 0,
					row, -1, -1,
					"e752x UE from Scruber", "");
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम process_ue(काष्ठा mem_ctl_info *mci, u16 error_one,
			u32 ded_add, u32 scrb_add, पूर्णांक *error_found,
			पूर्णांक handle_error)
अणु
	*error_found = 1;

	अगर (handle_error)
		करो_process_ue(mci, error_one, ded_add, scrb_add);
पूर्ण

अटल अंतरभूत व्योम process_ue_no_info_wr(काष्ठा mem_ctl_info *mci,
					 पूर्णांक *error_found, पूर्णांक handle_error)
अणु
	*error_found = 1;

	अगर (!handle_error)
		वापस;

	edac_dbg(3, "\n");
	edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0,
			     -1, -1, -1,
			     "e752x UE log memory write", "");
पूर्ण

अटल व्योम करो_process_ded_retry(काष्ठा mem_ctl_info *mci, u16 error,
				 u32 retry_add)
अणु
	u32 error_1b, page;
	पूर्णांक row;
	काष्ठा e752x_pvt *pvt = (काष्ठा e752x_pvt *)mci->pvt_info;

	error_1b = retry_add;
	page = error_1b >> (PAGE_SHIFT - 4);  /* convert the addr to 4k page */

	/* chip select are bits 14 & 13 */
	row = pvt->mc_symmetric ? ((page >> 1) & 3) :
		edac_mc_find_csrow_by_page(mci, page);

	e752x_mc_prपूर्णांकk(mci, KERN_WARNING,
			"CE page 0x%lx, row %d : Memory read retry\n",
			(दीर्घ अचिन्हित पूर्णांक)page, row);
पूर्ण

अटल अंतरभूत व्योम process_ded_retry(काष्ठा mem_ctl_info *mci, u16 error,
				u32 retry_add, पूर्णांक *error_found,
				पूर्णांक handle_error)
अणु
	*error_found = 1;

	अगर (handle_error)
		करो_process_ded_retry(mci, error, retry_add);
पूर्ण

अटल अंतरभूत व्योम process_threshold_ce(काष्ठा mem_ctl_info *mci, u16 error,
					पूर्णांक *error_found, पूर्णांक handle_error)
अणु
	*error_found = 1;

	अगर (handle_error)
		e752x_mc_prपूर्णांकk(mci, KERN_WARNING, "Memory threshold CE\n");
पूर्ण

अटल अक्षर *global_message[11] = अणु
	"PCI Express C1",
	"PCI Express C",
	"PCI Express B1",
	"PCI Express B",
	"PCI Express A1",
	"PCI Express A",
	"DMA Controller",
	"HUB or NS Interface",
	"System Bus",
	"DRAM Controller",  /* 9th entry */
	"Internal Buffer"
पूर्ण;

#घोषणा DRAM_ENTRY	9

अटल अक्षर *fatal_message[2] = अणु "Non-Fatal ", "Fatal " पूर्ण;

अटल व्योम करो_global_error(पूर्णांक fatal, u32 errors)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 11; i++) अणु
		अगर (errors & (1 << i)) अणु
			/* If the error is from DRAM Controller OR
			 * we are to report ALL errors, then
			 * report the error
			 */
			अगर ((i == DRAM_ENTRY) || report_non_memory_errors)
				e752x_prपूर्णांकk(KERN_WARNING, "%sError %s\n",
					fatal_message[fatal],
					global_message[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम global_error(पूर्णांक fatal, u32 errors, पूर्णांक *error_found,
				पूर्णांक handle_error)
अणु
	*error_found = 1;

	अगर (handle_error)
		करो_global_error(fatal, errors);
पूर्ण

अटल अक्षर *hub_message[7] = अणु
	"HI Address or Command Parity", "HI Illegal Access",
	"HI Internal Parity", "Out of Range Access",
	"HI Data Parity", "Enhanced Config Access",
	"Hub Interface Target Abort"
पूर्ण;

अटल व्योम करो_hub_error(पूर्णांक fatal, u8 errors)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 7; i++) अणु
		अगर (errors & (1 << i))
			e752x_prपूर्णांकk(KERN_WARNING, "%sError %s\n",
				fatal_message[fatal], hub_message[i]);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम hub_error(पूर्णांक fatal, u8 errors, पूर्णांक *error_found,
			पूर्णांक handle_error)
अणु
	*error_found = 1;

	अगर (handle_error)
		करो_hub_error(fatal, errors);
पूर्ण

#घोषणा NSI_FATAL_MASK		0x0c080081
#घोषणा NSI_NON_FATAL_MASK	0x23a0ba64
#घोषणा NSI_ERR_MASK		(NSI_FATAL_MASK | NSI_NON_FATAL_MASK)

अटल अक्षर *nsi_message[30] = अणु
	"NSI Link Down",	/* NSI_FERR/NSI_NERR bit 0, fatal error */
	"",						/* reserved */
	"NSI Parity Error",				/* bit 2, non-fatal */
	"",						/* reserved */
	"",						/* reserved */
	"Correctable Error Message",			/* bit 5, non-fatal */
	"Non-Fatal Error Message",			/* bit 6, non-fatal */
	"Fatal Error Message",				/* bit 7, fatal */
	"",						/* reserved */
	"Receiver Error",				/* bit 9, non-fatal */
	"",						/* reserved */
	"Bad TLP",					/* bit 11, non-fatal */
	"Bad DLLP",					/* bit 12, non-fatal */
	"REPLAY_NUM Rollover",				/* bit 13, non-fatal */
	"",						/* reserved */
	"Replay Timer Timeout",				/* bit 15, non-fatal */
	"",						/* reserved */
	"",						/* reserved */
	"",						/* reserved */
	"Data Link Protocol Error",			/* bit 19, fatal */
	"",						/* reserved */
	"Poisoned TLP",					/* bit 21, non-fatal */
	"",						/* reserved */
	"Completion Timeout",				/* bit 23, non-fatal */
	"Completer Abort",				/* bit 24, non-fatal */
	"Unexpected Completion",			/* bit 25, non-fatal */
	"Receiver Overflow",				/* bit 26, fatal */
	"Malformed TLP",				/* bit 27, fatal */
	"",						/* reserved */
	"Unsupported Request"				/* bit 29, non-fatal */
पूर्ण;

अटल व्योम करो_nsi_error(पूर्णांक fatal, u32 errors)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 30; i++) अणु
		अगर (errors & (1 << i))
			prपूर्णांकk(KERN_WARNING "%sError %s\n",
			       fatal_message[fatal], nsi_message[i]);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम nsi_error(पूर्णांक fatal, u32 errors, पूर्णांक *error_found,
		पूर्णांक handle_error)
अणु
	*error_found = 1;

	अगर (handle_error)
		करो_nsi_error(fatal, errors);
पूर्ण

अटल अक्षर *membuf_message[4] = अणु
	"Internal PMWB to DRAM parity",
	"Internal PMWB to System Bus Parity",
	"Internal System Bus or IO to PMWB Parity",
	"Internal DRAM to PMWB Parity"
पूर्ण;

अटल व्योम करो_membuf_error(u8 errors)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (errors & (1 << i))
			e752x_prपूर्णांकk(KERN_WARNING, "Non-Fatal Error %s\n",
				membuf_message[i]);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम membuf_error(u8 errors, पूर्णांक *error_found, पूर्णांक handle_error)
अणु
	*error_found = 1;

	अगर (handle_error)
		करो_membuf_error(errors);
पूर्ण

अटल अक्षर *sysbus_message[10] = अणु
	"Addr or Request Parity",
	"Data Strobe Glitch",
	"Addr Strobe Glitch",
	"Data Parity",
	"Addr Above TOM",
	"Non DRAM Lock Error",
	"MCERR", "BINIT",
	"Memory Parity",
	"IO Subsystem Parity"
पूर्ण;

अटल व्योम करो_sysbus_error(पूर्णांक fatal, u32 errors)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु
		अगर (errors & (1 << i))
			e752x_prपूर्णांकk(KERN_WARNING, "%sError System Bus %s\n",
				fatal_message[fatal], sysbus_message[i]);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sysbus_error(पूर्णांक fatal, u32 errors, पूर्णांक *error_found,
				पूर्णांक handle_error)
अणु
	*error_found = 1;

	अगर (handle_error)
		करो_sysbus_error(fatal, errors);
पूर्ण

अटल व्योम e752x_check_hub_पूर्णांकerface(काष्ठा e752x_error_info *info,
				पूर्णांक *error_found, पूर्णांक handle_error)
अणु
	u8 stat8;

	//pci_पढ़ो_config_byte(dev,E752X_HI_FERR,&stat8);

	stat8 = info->hi_ferr;

	अगर (stat8 & 0x7f) अणु	/* Error, so process */
		stat8 &= 0x7f;

		अगर (stat8 & 0x2b)
			hub_error(1, stat8 & 0x2b, error_found, handle_error);

		अगर (stat8 & 0x54)
			hub_error(0, stat8 & 0x54, error_found, handle_error);
	पूर्ण
	//pci_पढ़ो_config_byte(dev,E752X_HI_NERR,&stat8);

	stat8 = info->hi_nerr;

	अगर (stat8 & 0x7f) अणु	/* Error, so process */
		stat8 &= 0x7f;

		अगर (stat8 & 0x2b)
			hub_error(1, stat8 & 0x2b, error_found, handle_error);

		अगर (stat8 & 0x54)
			hub_error(0, stat8 & 0x54, error_found, handle_error);
	पूर्ण
पूर्ण

अटल व्योम e752x_check_ns_पूर्णांकerface(काष्ठा e752x_error_info *info,
				पूर्णांक *error_found, पूर्णांक handle_error)
अणु
	u32 stat32;

	stat32 = info->nsi_ferr;
	अगर (stat32 & NSI_ERR_MASK) अणु /* Error, so process */
		अगर (stat32 & NSI_FATAL_MASK)	/* check क्रम fatal errors */
			nsi_error(1, stat32 & NSI_FATAL_MASK, error_found,
				  handle_error);
		अगर (stat32 & NSI_NON_FATAL_MASK) /* check क्रम non-fatal ones */
			nsi_error(0, stat32 & NSI_NON_FATAL_MASK, error_found,
				  handle_error);
	पूर्ण
	stat32 = info->nsi_nerr;
	अगर (stat32 & NSI_ERR_MASK) अणु
		अगर (stat32 & NSI_FATAL_MASK)
			nsi_error(1, stat32 & NSI_FATAL_MASK, error_found,
				  handle_error);
		अगर (stat32 & NSI_NON_FATAL_MASK)
			nsi_error(0, stat32 & NSI_NON_FATAL_MASK, error_found,
				  handle_error);
	पूर्ण
पूर्ण

अटल व्योम e752x_check_sysbus(काष्ठा e752x_error_info *info,
			पूर्णांक *error_found, पूर्णांक handle_error)
अणु
	u32 stat32, error32;

	//pci_पढ़ो_config_dword(dev,E752X_SYSBUS_FERR,&stat32);
	stat32 = info->sysbus_ferr + (info->sysbus_nerr << 16);

	अगर (stat32 == 0)
		वापस;		/* no errors */

	error32 = (stat32 >> 16) & 0x3ff;
	stat32 = stat32 & 0x3ff;

	अगर (stat32 & 0x087)
		sysbus_error(1, stat32 & 0x087, error_found, handle_error);

	अगर (stat32 & 0x378)
		sysbus_error(0, stat32 & 0x378, error_found, handle_error);

	अगर (error32 & 0x087)
		sysbus_error(1, error32 & 0x087, error_found, handle_error);

	अगर (error32 & 0x378)
		sysbus_error(0, error32 & 0x378, error_found, handle_error);
पूर्ण

अटल व्योम e752x_check_membuf(काष्ठा e752x_error_info *info,
			पूर्णांक *error_found, पूर्णांक handle_error)
अणु
	u8 stat8;

	stat8 = info->buf_ferr;

	अगर (stat8 & 0x0f) अणु	/* Error, so process */
		stat8 &= 0x0f;
		membuf_error(stat8, error_found, handle_error);
	पूर्ण

	stat8 = info->buf_nerr;

	अगर (stat8 & 0x0f) अणु	/* Error, so process */
		stat8 &= 0x0f;
		membuf_error(stat8, error_found, handle_error);
	पूर्ण
पूर्ण

अटल व्योम e752x_check_dram(काष्ठा mem_ctl_info *mci,
			काष्ठा e752x_error_info *info, पूर्णांक *error_found,
			पूर्णांक handle_error)
अणु
	u16 error_one, error_next;

	error_one = info->dram_ferr;
	error_next = info->dram_nerr;

	/* decode and report errors */
	अगर (error_one & 0x0101)	/* check first error correctable */
		process_ce(mci, error_one, info->dram_sec1_add,
			info->dram_sec1_syndrome, error_found, handle_error);

	अगर (error_next & 0x0101)	/* check next error correctable */
		process_ce(mci, error_next, info->dram_sec2_add,
			info->dram_sec2_syndrome, error_found, handle_error);

	अगर (error_one & 0x4040)
		process_ue_no_info_wr(mci, error_found, handle_error);

	अगर (error_next & 0x4040)
		process_ue_no_info_wr(mci, error_found, handle_error);

	अगर (error_one & 0x2020)
		process_ded_retry(mci, error_one, info->dram_retr_add,
				error_found, handle_error);

	अगर (error_next & 0x2020)
		process_ded_retry(mci, error_next, info->dram_retr_add,
				error_found, handle_error);

	अगर (error_one & 0x0808)
		process_threshold_ce(mci, error_one, error_found, handle_error);

	अगर (error_next & 0x0808)
		process_threshold_ce(mci, error_next, error_found,
				handle_error);

	अगर (error_one & 0x0606)
		process_ue(mci, error_one, info->dram_ded_add,
			info->dram_scrb_add, error_found, handle_error);

	अगर (error_next & 0x0606)
		process_ue(mci, error_next, info->dram_ded_add,
			info->dram_scrb_add, error_found, handle_error);
पूर्ण

अटल व्योम e752x_get_error_info(काष्ठा mem_ctl_info *mci,
				 काष्ठा e752x_error_info *info)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा e752x_pvt *pvt;

	स_रखो(info, 0, माप(*info));
	pvt = (काष्ठा e752x_pvt *)mci->pvt_info;
	dev = pvt->dev_d0f1;
	pci_पढ़ो_config_dword(dev, E752X_FERR_GLOBAL, &info->ferr_global);

	अगर (info->ferr_global) अणु
		अगर (pvt->dev_info->err_dev == PCI_DEVICE_ID_INTEL_3100_1_ERR) अणु
			pci_पढ़ो_config_dword(dev, I3100_NSI_FERR,
					     &info->nsi_ferr);
			info->hi_ferr = 0;
		पूर्ण अन्यथा अणु
			pci_पढ़ो_config_byte(dev, E752X_HI_FERR,
					     &info->hi_ferr);
			info->nsi_ferr = 0;
		पूर्ण
		pci_पढ़ो_config_word(dev, E752X_SYSBUS_FERR,
				&info->sysbus_ferr);
		pci_पढ़ो_config_byte(dev, E752X_BUF_FERR, &info->buf_ferr);
		pci_पढ़ो_config_word(dev, E752X_DRAM_FERR, &info->dram_ferr);
		pci_पढ़ो_config_dword(dev, E752X_DRAM_SEC1_ADD,
				&info->dram_sec1_add);
		pci_पढ़ो_config_word(dev, E752X_DRAM_SEC1_SYNDROME,
				&info->dram_sec1_syndrome);
		pci_पढ़ो_config_dword(dev, E752X_DRAM_DED_ADD,
				&info->dram_ded_add);
		pci_पढ़ो_config_dword(dev, E752X_DRAM_SCRB_ADD,
				&info->dram_scrb_add);
		pci_पढ़ो_config_dword(dev, E752X_DRAM_RETR_ADD,
				&info->dram_retr_add);

		/* ignore the reserved bits just in हाल */
		अगर (info->hi_ferr & 0x7f)
			pci_ग_लिखो_config_byte(dev, E752X_HI_FERR,
					info->hi_ferr);

		अगर (info->nsi_ferr & NSI_ERR_MASK)
			pci_ग_लिखो_config_dword(dev, I3100_NSI_FERR,
					info->nsi_ferr);

		अगर (info->sysbus_ferr)
			pci_ग_लिखो_config_word(dev, E752X_SYSBUS_FERR,
					info->sysbus_ferr);

		अगर (info->buf_ferr & 0x0f)
			pci_ग_लिखो_config_byte(dev, E752X_BUF_FERR,
					info->buf_ferr);

		अगर (info->dram_ferr)
			pci_ग_लिखो_bits16(pvt->dev_d0f1, E752X_DRAM_FERR,
					 info->dram_ferr, info->dram_ferr);

		pci_ग_लिखो_config_dword(dev, E752X_FERR_GLOBAL,
				info->ferr_global);
	पूर्ण

	pci_पढ़ो_config_dword(dev, E752X_NERR_GLOBAL, &info->nerr_global);

	अगर (info->nerr_global) अणु
		अगर (pvt->dev_info->err_dev == PCI_DEVICE_ID_INTEL_3100_1_ERR) अणु
			pci_पढ़ो_config_dword(dev, I3100_NSI_NERR,
					     &info->nsi_nerr);
			info->hi_nerr = 0;
		पूर्ण अन्यथा अणु
			pci_पढ़ो_config_byte(dev, E752X_HI_NERR,
					     &info->hi_nerr);
			info->nsi_nerr = 0;
		पूर्ण
		pci_पढ़ो_config_word(dev, E752X_SYSBUS_NERR,
				&info->sysbus_nerr);
		pci_पढ़ो_config_byte(dev, E752X_BUF_NERR, &info->buf_nerr);
		pci_पढ़ो_config_word(dev, E752X_DRAM_NERR, &info->dram_nerr);
		pci_पढ़ो_config_dword(dev, E752X_DRAM_SEC2_ADD,
				&info->dram_sec2_add);
		pci_पढ़ो_config_word(dev, E752X_DRAM_SEC2_SYNDROME,
				&info->dram_sec2_syndrome);

		अगर (info->hi_nerr & 0x7f)
			pci_ग_लिखो_config_byte(dev, E752X_HI_NERR,
					info->hi_nerr);

		अगर (info->nsi_nerr & NSI_ERR_MASK)
			pci_ग_लिखो_config_dword(dev, I3100_NSI_NERR,
					info->nsi_nerr);

		अगर (info->sysbus_nerr)
			pci_ग_लिखो_config_word(dev, E752X_SYSBUS_NERR,
					info->sysbus_nerr);

		अगर (info->buf_nerr & 0x0f)
			pci_ग_लिखो_config_byte(dev, E752X_BUF_NERR,
					info->buf_nerr);

		अगर (info->dram_nerr)
			pci_ग_लिखो_bits16(pvt->dev_d0f1, E752X_DRAM_NERR,
					 info->dram_nerr, info->dram_nerr);

		pci_ग_लिखो_config_dword(dev, E752X_NERR_GLOBAL,
				info->nerr_global);
	पूर्ण
पूर्ण

अटल पूर्णांक e752x_process_error_info(काष्ठा mem_ctl_info *mci,
				काष्ठा e752x_error_info *info,
				पूर्णांक handle_errors)
अणु
	u32 error32, stat32;
	पूर्णांक error_found;

	error_found = 0;
	error32 = (info->ferr_global >> 18) & 0x3ff;
	stat32 = (info->ferr_global >> 4) & 0x7ff;

	अगर (error32)
		global_error(1, error32, &error_found, handle_errors);

	अगर (stat32)
		global_error(0, stat32, &error_found, handle_errors);

	error32 = (info->nerr_global >> 18) & 0x3ff;
	stat32 = (info->nerr_global >> 4) & 0x7ff;

	अगर (error32)
		global_error(1, error32, &error_found, handle_errors);

	अगर (stat32)
		global_error(0, stat32, &error_found, handle_errors);

	e752x_check_hub_पूर्णांकerface(info, &error_found, handle_errors);
	e752x_check_ns_पूर्णांकerface(info, &error_found, handle_errors);
	e752x_check_sysbus(info, &error_found, handle_errors);
	e752x_check_membuf(info, &error_found, handle_errors);
	e752x_check_dram(mci, info, &error_found, handle_errors);
	वापस error_found;
पूर्ण

अटल व्योम e752x_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा e752x_error_info info;

	e752x_get_error_info(mci, &info);
	e752x_process_error_info(mci, &info, 1);
पूर्ण

/* Program byte/sec bandwidth scrub rate to hardware */
अटल पूर्णांक set_sdram_scrub_rate(काष्ठा mem_ctl_info *mci, u32 new_bw)
अणु
	स्थिर काष्ठा scrubrate *scrubrates;
	काष्ठा e752x_pvt *pvt = (काष्ठा e752x_pvt *) mci->pvt_info;
	काष्ठा pci_dev *pdev = pvt->dev_d0f0;
	पूर्णांक i;

	अगर (pvt->dev_info->ctl_dev == PCI_DEVICE_ID_INTEL_3100_0)
		scrubrates = scrubrates_i3100;
	अन्यथा
		scrubrates = scrubrates_e752x;

	/* Translate the desired scrub rate to a e752x/3100 रेजिस्टर value.
	 * Search क्रम the bandwidth that is equal or greater than the
	 * desired rate and program the cooresponding रेजिस्टर value.
	 */
	क्रम (i = 0; scrubrates[i].bandwidth != SDRATE_EOT; i++)
		अगर (scrubrates[i].bandwidth >= new_bw)
			अवरोध;

	अगर (scrubrates[i].bandwidth == SDRATE_EOT)
		वापस -1;

	pci_ग_लिखो_config_word(pdev, E752X_MCHSCRB, scrubrates[i].scrubval);

	वापस scrubrates[i].bandwidth;
पूर्ण

/* Convert current scrub rate value पूर्णांकo byte/sec bandwidth */
अटल पूर्णांक get_sdram_scrub_rate(काष्ठा mem_ctl_info *mci)
अणु
	स्थिर काष्ठा scrubrate *scrubrates;
	काष्ठा e752x_pvt *pvt = (काष्ठा e752x_pvt *) mci->pvt_info;
	काष्ठा pci_dev *pdev = pvt->dev_d0f0;
	u16 scrubval;
	पूर्णांक i;

	अगर (pvt->dev_info->ctl_dev == PCI_DEVICE_ID_INTEL_3100_0)
		scrubrates = scrubrates_i3100;
	अन्यथा
		scrubrates = scrubrates_e752x;

	/* Find the bandwidth matching the memory scrubber configuration */
	pci_पढ़ो_config_word(pdev, E752X_MCHSCRB, &scrubval);
	scrubval = scrubval & 0x0f;

	क्रम (i = 0; scrubrates[i].bandwidth != SDRATE_EOT; i++)
		अगर (scrubrates[i].scrubval == scrubval)
			अवरोध;

	अगर (scrubrates[i].bandwidth == SDRATE_EOT) अणु
		e752x_prपूर्णांकk(KERN_WARNING,
			"Invalid sdram scrub control value: 0x%x\n", scrubval);
		वापस -1;
	पूर्ण
	वापस scrubrates[i].bandwidth;

पूर्ण

/* Return 1 अगर dual channel mode is active.  Else वापस 0. */
अटल अंतरभूत पूर्णांक dual_channel_active(u16 ddrcsr)
अणु
	वापस (((ddrcsr >> 12) & 3) == 3);
पूर्ण

/* Remap csrow index numbers अगर map_type is "reverse"
 */
अटल अंतरभूत पूर्णांक remap_csrow_index(काष्ठा mem_ctl_info *mci, पूर्णांक index)
अणु
	काष्ठा e752x_pvt *pvt = mci->pvt_info;

	अगर (!pvt->map_type)
		वापस (7 - index);

	वापस (index);
पूर्ण

अटल व्योम e752x_init_csrows(काष्ठा mem_ctl_info *mci, काष्ठा pci_dev *pdev,
			u16 ddrcsr)
अणु
	काष्ठा csrow_info *csrow;
	क्रमागत edac_type edac_mode;
	अचिन्हित दीर्घ last_cumul_size;
	पूर्णांक index, mem_dev, drc_chan;
	पूर्णांक drc_drbg;		/* DRB granularity 0=64mb, 1=128mb */
	पूर्णांक drc_ddim;		/* DRAM Data Integrity Mode 0=none, 2=edac */
	u8 value;
	u32 dra, drc, cumul_size, i, nr_pages;

	dra = 0;
	क्रम (index = 0; index < 4; index++) अणु
		u8 dra_reg;
		pci_पढ़ो_config_byte(pdev, E752X_DRA + index, &dra_reg);
		dra |= dra_reg << (index * 8);
	पूर्ण
	pci_पढ़ो_config_dword(pdev, E752X_DRC, &drc);
	drc_chan = dual_channel_active(ddrcsr) ? 1 : 0;
	drc_drbg = drc_chan + 1;	/* 128 in dual mode, 64 in single */
	drc_ddim = (drc >> 20) & 0x3;

	/* The dram row boundary (DRB) reg values are boundary address क्रम
	 * each DRAM row with a granularity of 64 or 128MB (single/dual
	 * channel operation).  DRB regs are cumulative; thereक्रमe DRB7 will
	 * contain the total memory contained in all eight rows.
	 */
	क्रम (last_cumul_size = index = 0; index < mci->nr_csrows; index++) अणु
		/* mem_dev 0=x8, 1=x4 */
		mem_dev = (dra >> (index * 4 + 2)) & 0x3;
		csrow = mci->csrows[remap_csrow_index(mci, index)];

		mem_dev = (mem_dev == 2);
		pci_पढ़ो_config_byte(pdev, E752X_DRB + index, &value);
		/* convert a 128 or 64 MiB DRB to a page size. */
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
		क्रम (i = 0; i < csrow->nr_channels; i++) अणु
			काष्ठा dimm_info *dimm = csrow->channels[i]->dimm;

			edac_dbg(3, "Initializing rank at (%i,%i)\n", index, i);
			dimm->nr_pages = nr_pages / csrow->nr_channels;
			dimm->grain = 1 << 12;	/* 4KiB - resolution of CELOG */
			dimm->mtype = MEM_RDDR;	/* only one type supported */
			dimm->dtype = mem_dev ? DEV_X4 : DEV_X8;
			dimm->edac_mode = edac_mode;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम e752x_init_mem_map_table(काष्ठा pci_dev *pdev,
				काष्ठा e752x_pvt *pvt)
अणु
	पूर्णांक index;
	u8 value, last, row;

	last = 0;
	row = 0;

	क्रम (index = 0; index < 8; index += 2) अणु
		pci_पढ़ो_config_byte(pdev, E752X_DRB + index, &value);
		/* test अगर there is a dimm in this slot */
		अगर (value == last) अणु
			/* no dimm in the slot, so flag it as empty */
			pvt->map[index] = 0xff;
			pvt->map[index + 1] = 0xff;
		पूर्ण अन्यथा अणु	/* there is a dimm in the slot */
			pvt->map[index] = row;
			row++;
			last = value;
			/* test the next value to see अगर the dimm is द्विगुन
			 * sided
			 */
			pci_पढ़ो_config_byte(pdev, E752X_DRB + index + 1,
					&value);

			/* the dimm is single sided, so flag as empty */
			/* this is a द्विगुन sided dimm to save the next row #*/
			pvt->map[index + 1] = (value == last) ? 0xff :	row;
			row++;
			last = value;
		पूर्ण
	पूर्ण
पूर्ण

/* Return 0 on success or 1 on failure. */
अटल पूर्णांक e752x_get_devs(काष्ठा pci_dev *pdev, पूर्णांक dev_idx,
			काष्ठा e752x_pvt *pvt)
अणु
	pvt->dev_d0f1 = pci_get_device(PCI_VENDOR_ID_INTEL,
				pvt->dev_info->err_dev, शून्य);

	अगर (pvt->dev_d0f1 == शून्य) अणु
		pvt->dev_d0f1 = pci_scan_single_device(pdev->bus,
							PCI_DEVFN(0, 1));
		pci_dev_get(pvt->dev_d0f1);
	पूर्ण

	अगर (pvt->dev_d0f1 == शून्य) अणु
		e752x_prपूर्णांकk(KERN_ERR, "error reporting device not found:"
			"vendor %x device 0x%x (broken BIOS?)\n",
			PCI_VENDOR_ID_INTEL, e752x_devs[dev_idx].err_dev);
		वापस 1;
	पूर्ण

	pvt->dev_d0f0 = pci_get_device(PCI_VENDOR_ID_INTEL,
				e752x_devs[dev_idx].ctl_dev,
				शून्य);

	अगर (pvt->dev_d0f0 == शून्य)
		जाओ fail;

	वापस 0;

fail:
	pci_dev_put(pvt->dev_d0f1);
	वापस 1;
पूर्ण

/* Setup प्रणाली bus parity mask रेजिस्टर.
 * Sysbus parity supported on:
 * e7320/e7520/e7525 + Xeon
 */
अटल व्योम e752x_init_sysbus_parity_mask(काष्ठा e752x_pvt *pvt)
अणु
	अक्षर *cpu_id = cpu_data(0).x86_model_id;
	काष्ठा pci_dev *dev = pvt->dev_d0f1;
	पूर्णांक enable = 1;

	/* Allow module parameter override, अन्यथा see अगर CPU supports parity */
	अगर (sysbus_parity != -1) अणु
		enable = sysbus_parity;
	पूर्ण अन्यथा अगर (cpu_id[0] && !म_माला(cpu_id, "Xeon")) अणु
		e752x_prपूर्णांकk(KERN_INFO, "System Bus Parity not "
			     "supported by CPU, disabling\n");
		enable = 0;
	पूर्ण

	अगर (enable)
		pci_ग_लिखो_config_word(dev, E752X_SYSBUS_ERRMASK, 0x0000);
	अन्यथा
		pci_ग_लिखो_config_word(dev, E752X_SYSBUS_ERRMASK, 0x0309);
पूर्ण

अटल व्योम e752x_init_error_reporting_regs(काष्ठा e752x_pvt *pvt)
अणु
	काष्ठा pci_dev *dev;

	dev = pvt->dev_d0f1;
	/* Turn off error disable & SMI in हाल the BIOS turned it on */
	अगर (pvt->dev_info->err_dev == PCI_DEVICE_ID_INTEL_3100_1_ERR) अणु
		pci_ग_लिखो_config_dword(dev, I3100_NSI_EMASK, 0);
		pci_ग_लिखो_config_dword(dev, I3100_NSI_SMICMD, 0);
	पूर्ण अन्यथा अणु
		pci_ग_लिखो_config_byte(dev, E752X_HI_ERRMASK, 0x00);
		pci_ग_लिखो_config_byte(dev, E752X_HI_SMICMD, 0x00);
	पूर्ण

	e752x_init_sysbus_parity_mask(pvt);

	pci_ग_लिखो_config_word(dev, E752X_SYSBUS_SMICMD, 0x00);
	pci_ग_लिखो_config_byte(dev, E752X_BUF_ERRMASK, 0x00);
	pci_ग_लिखो_config_byte(dev, E752X_BUF_SMICMD, 0x00);
	pci_ग_लिखो_config_byte(dev, E752X_DRAM_ERRMASK, 0x00);
	pci_ग_लिखो_config_byte(dev, E752X_DRAM_SMICMD, 0x00);
पूर्ण

अटल पूर्णांक e752x_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	u16 pci_data;
	u8 stat8;
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा e752x_pvt *pvt;
	u16 ddrcsr;
	पूर्णांक drc_chan;		/* Number of channels 0=1chan,1=2chan */
	काष्ठा e752x_error_info discard;

	edac_dbg(0, "mci\n");
	edac_dbg(0, "Starting Probe1\n");

	/* check to see अगर device 0 function 1 is enabled; अगर it isn't, we
	 * assume the BIOS has reserved it क्रम a reason and is expecting
	 * exclusive access, we take care not to violate that assumption and
	 * fail the probe. */
	pci_पढ़ो_config_byte(pdev, E752X_DEVPRES1, &stat8);
	अगर (!क्रमce_function_unhide && !(stat8 & (1 << 5))) अणु
		prपूर्णांकk(KERN_INFO "Contact your BIOS vendor to see if the "
			"E752x error registers can be safely un-hidden\n");
		वापस -ENODEV;
	पूर्ण
	stat8 |= (1 << 5);
	pci_ग_लिखो_config_byte(pdev, E752X_DEVPRES1, stat8);

	pci_पढ़ो_config_word(pdev, E752X_DDRCSR, &ddrcsr);
	/* FIXME: should check >>12 or 0xf, true क्रम all? */
	/* Dual channel = 1, Single channel = 0 */
	drc_chan = dual_channel_active(ddrcsr);

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = E752X_NR_CSROWS;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = drc_chan + 1;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, माप(*pvt));
	अगर (mci == शून्य)
		वापस -ENOMEM;

	edac_dbg(3, "init mci\n");
	mci->mtype_cap = MEM_FLAG_RDDR;
	/* 3100 IMCH supports SECDEC only */
	mci->edac_ctl_cap = (dev_idx == I3100) ? EDAC_FLAG_SECDED :
		(EDAC_FLAG_NONE | EDAC_FLAG_SECDED | EDAC_FLAG_S4ECD4ED);
	/* FIXME - what अगर dअगरferent memory types are in dअगरferent csrows? */
	mci->mod_name = EDAC_MOD_STR;
	mci->pdev = &pdev->dev;

	edac_dbg(3, "init pvt\n");
	pvt = (काष्ठा e752x_pvt *)mci->pvt_info;
	pvt->dev_info = &e752x_devs[dev_idx];
	pvt->mc_symmetric = ((ddrcsr & 0x10) != 0);

	अगर (e752x_get_devs(pdev, dev_idx, pvt)) अणु
		edac_mc_मुक्त(mci);
		वापस -ENODEV;
	पूर्ण

	edac_dbg(3, "more mci init\n");
	mci->ctl_name = pvt->dev_info->ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = e752x_check;
	mci->ctl_page_to_phys = ctl_page_to_phys;
	mci->set_sdram_scrub_rate = set_sdram_scrub_rate;
	mci->get_sdram_scrub_rate = get_sdram_scrub_rate;

	/* set the map type.  1 = normal, 0 = reversed
	 * Must be set beक्रमe e752x_init_csrows in हाल csrow mapping
	 * is reversed.
	 */
	pci_पढ़ो_config_byte(pdev, E752X_DRM, &stat8);
	pvt->map_type = ((stat8 & 0x0f) > ((stat8 >> 4) & 0x0f));

	e752x_init_csrows(mci, pdev, ddrcsr);
	e752x_init_mem_map_table(pdev, pvt);

	अगर (dev_idx == I3100)
		mci->edac_cap = EDAC_FLAG_SECDED; /* the only mode supported */
	अन्यथा
		mci->edac_cap |= EDAC_FLAG_NONE;
	edac_dbg(3, "tolm, remapbase, remaplimit\n");

	/* load the top of low memory, remap base, and remap limit vars */
	pci_पढ़ो_config_word(pdev, E752X_TOLM, &pci_data);
	pvt->tolm = ((u32) pci_data) << 4;
	pci_पढ़ो_config_word(pdev, E752X_REMAPBASE, &pci_data);
	pvt->remapbase = ((u32) pci_data) << 14;
	pci_पढ़ो_config_word(pdev, E752X_REMAPLIMIT, &pci_data);
	pvt->remaplimit = ((u32) pci_data) << 14;
	e752x_prपूर्णांकk(KERN_INFO,
			"tolm = %x, remapbase = %x, remaplimit = %x\n",
			pvt->tolm, pvt->remapbase, pvt->remaplimit);

	/* Here we assume that we will never see multiple instances of this
	 * type of memory controller.  The ID is thereक्रमe hardcoded to 0.
	 */
	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(3, "failed edac_mc_add_mc()\n");
		जाओ fail;
	पूर्ण

	e752x_init_error_reporting_regs(pvt);
	e752x_get_error_info(mci, &discard);	/* clear other MCH errors */

	/* allocating generic PCI control info */
	e752x_pci = edac_pci_create_generic_ctl(&pdev->dev, EDAC_MOD_STR);
	अगर (!e752x_pci) अणु
		prपूर्णांकk(KERN_WARNING
			"%s(): Unable to create PCI control\n", __func__);
		prपूर्णांकk(KERN_WARNING
			"%s(): PCI error report via EDAC not setup\n",
			__func__);
	पूर्ण

	/* get this far and it's successful */
	edac_dbg(3, "success\n");
	वापस 0;

fail:
	pci_dev_put(pvt->dev_d0f0);
	pci_dev_put(pvt->dev_d0f1);
	edac_mc_मुक्त(mci);

	वापस -ENODEV;
पूर्ण

/* वापसs count (>= 0), or negative on error */
अटल पूर्णांक e752x_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	edac_dbg(0, "\n");

	/* wake up and enable device */
	अगर (pci_enable_device(pdev) < 0)
		वापस -EIO;

	वापस e752x_probe1(pdev, ent->driver_data);
पूर्ण

अटल व्योम e752x_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा e752x_pvt *pvt;

	edac_dbg(0, "\n");

	अगर (e752x_pci)
		edac_pci_release_generic_ctl(e752x_pci);

	अगर ((mci = edac_mc_del_mc(&pdev->dev)) == शून्य)
		वापस;

	pvt = (काष्ठा e752x_pvt *)mci->pvt_info;
	pci_dev_put(pvt->dev_d0f0);
	pci_dev_put(pvt->dev_d0f1);
	edac_mc_मुक्त(mci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id e752x_pci_tbl[] = अणु
	अणु
	 PCI_VEND_DEV(INTEL, 7520_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7520पूर्ण,
	अणु
	 PCI_VEND_DEV(INTEL, 7525_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7525पूर्ण,
	अणु
	 PCI_VEND_DEV(INTEL, 7320_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7320पूर्ण,
	अणु
	 PCI_VEND_DEV(INTEL, 3100_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 I3100पूर्ण,
	अणु
	 0,
	 पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, e752x_pci_tbl);

अटल काष्ठा pci_driver e752x_driver = अणु
	.name = EDAC_MOD_STR,
	.probe = e752x_init_one,
	.हटाओ = e752x_हटाओ_one,
	.id_table = e752x_pci_tbl,
पूर्ण;

अटल पूर्णांक __init e752x_init(व्योम)
अणु
	पूर्णांक pci_rc;

	edac_dbg(3, "\n");

	/* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
	opstate_init();

	pci_rc = pci_रेजिस्टर_driver(&e752x_driver);
	वापस (pci_rc < 0) ? pci_rc : 0;
पूर्ण

अटल व्योम __निकास e752x_निकास(व्योम)
अणु
	edac_dbg(3, "\n");
	pci_unरेजिस्टर_driver(&e752x_driver);
पूर्ण

module_init(e752x_init);
module_निकास(e752x_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Linux Networx (http://lnxi.com) Tom Zimmerman\n");
MODULE_DESCRIPTION("MC support for Intel e752x/3100 memory controllers");

module_param(क्रमce_function_unhide, पूर्णांक, 0444);
MODULE_PARM_DESC(क्रमce_function_unhide, "if BIOS sets Dev0:Fun1 up as hidden:"
		 " 1=force unhide and hope BIOS doesn't fight driver for "
		"Dev0:Fun1 access");

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");

module_param(sysbus_parity, पूर्णांक, 0444);
MODULE_PARM_DESC(sysbus_parity, "0=disable system bus parity checking,"
		" 1=enable system bus parity checking, default=auto-detect");
module_param(report_non_memory_errors, पूर्णांक, 0644);
MODULE_PARM_DESC(report_non_memory_errors, "0=disable non-memory error "
		"reporting, 1=enable non-memory error reporting");
