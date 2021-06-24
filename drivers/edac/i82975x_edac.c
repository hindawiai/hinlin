<शैली गुरु>
/*
 * Intel 82975X Memory Controller kernel module
 * (C) 2007 aCarLab (India) Pvt. Ltd. (http://acarlab.com)
 * (C) 2007 jetzbroadband (http://jetzbroadband.com)
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written by Arvind R.
 *   Copied from i82875p_edac.c source:
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/edac.h>
#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR		"i82975x_edac"

#घोषणा i82975x_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "i82975x", fmt, ##arg)

#घोषणा i82975x_mc_prपूर्णांकk(mci, level, fmt, arg...) \
	edac_mc_chipset_prपूर्णांकk(mci, level, "i82975x", fmt, ##arg)

#अगर_अघोषित PCI_DEVICE_ID_INTEL_82975_0
#घोषणा PCI_DEVICE_ID_INTEL_82975_0	0x277c
#पूर्ण_अगर				/* PCI_DEVICE_ID_INTEL_82975_0 */

#घोषणा I82975X_NR_DIMMS		8
#घोषणा I82975X_NR_CSROWS(nr_chans)	(I82975X_NR_DIMMS / (nr_chans))

/* Intel 82975X रेजिस्टर addresses - device 0 function 0 - DRAM Controller */
#घोषणा I82975X_EAP		0x58	/* Dram Error Address Poपूर्णांकer (32b)
					 *
					 * 31:7  128 byte cache-line address
					 * 6:1   reserved
					 * 0     0: CH0; 1: CH1
					 */

#घोषणा I82975X_DERRSYN		0x5c	/* Dram Error SYNdrome (8b)
					 *
					 *  7:0  DRAM ECC Syndrome
					 */

#घोषणा I82975X_DES		0x5d	/* Dram ERRor DeSTination (8b)
					 * 0h:    Processor Memory Reads
					 * 1h:7h  reserved
					 * More - See Page 65 of Intel DocSheet.
					 */

#घोषणा I82975X_ERRSTS		0xc8	/* Error Status Register (16b)
					 *
					 * 15:12 reserved
					 * 11    Thermal Sensor Event
					 * 10    reserved
					 *  9    non-DRAM lock error (ndlock)
					 *  8    Refresh Timeout
					 *  7:2  reserved
					 *  1    ECC UE (multibit DRAM error)
					 *  0    ECC CE (singlebit DRAM error)
					 */

/* Error Reporting is supported by 3 mechanisms:
  1. DMI SERR generation  ( ERRCMD )
  2. SMI DMI  generation  ( SMICMD )
  3. SCI DMI  generation  ( SCICMD )
NOTE: Only ONE of the three must be enabled
*/
#घोषणा I82975X_ERRCMD		0xca	/* Error Command (16b)
					 *
					 * 15:12 reserved
					 * 11    Thermal Sensor Event
					 * 10    reserved
					 *  9    non-DRAM lock error (ndlock)
					 *  8    Refresh Timeout
					 *  7:2  reserved
					 *  1    ECC UE (multibit DRAM error)
					 *  0    ECC CE (singlebit DRAM error)
					 */

#घोषणा I82975X_SMICMD		0xcc	/* Error Command (16b)
					 *
					 * 15:2  reserved
					 *  1    ECC UE (multibit DRAM error)
					 *  0    ECC CE (singlebit DRAM error)
					 */

#घोषणा I82975X_SCICMD		0xce	/* Error Command (16b)
					 *
					 * 15:2  reserved
					 *  1    ECC UE (multibit DRAM error)
					 *  0    ECC CE (singlebit DRAM error)
					 */

#घोषणा I82975X_XEAP	0xfc	/* Extended Dram Error Address Poपूर्णांकer (8b)
					 *
					 * 7:1   reserved
					 * 0     Bit32 of the Dram Error Address
					 */

#घोषणा I82975X_MCHBAR		0x44	/*
					 *
					 * 31:14 Base Addr of 16K memory-mapped
					 *	configuration space
					 * 13:1  reserved
					 *  0    mem-mapped config space enable
					 */

/* NOTE: Following addresses have to indexed using MCHBAR offset (44h, 32b) */
/* Intel 82975x memory mapped रेजिस्टर space */

#घोषणा I82975X_DRB_SHIFT 25	/* fixed 32MiB grain */

#घोषणा I82975X_DRB		0x100	/* DRAM Row Boundary (8b x 8)
					 *
					 * 7   set to 1 in highest DRB of
					 *	channel अगर 4GB in ch.
					 * 6:2 upper boundary of rank in
					 *	32MB grains
					 * 1:0 set to 0
					 */
#घोषणा I82975X_DRB_CH0R0		0x100
#घोषणा I82975X_DRB_CH0R1		0x101
#घोषणा I82975X_DRB_CH0R2		0x102
#घोषणा I82975X_DRB_CH0R3		0x103
#घोषणा I82975X_DRB_CH1R0		0x180
#घोषणा I82975X_DRB_CH1R1		0x181
#घोषणा I82975X_DRB_CH1R2		0x182
#घोषणा I82975X_DRB_CH1R3		0x183


#घोषणा I82975X_DRA		0x108	/* DRAM Row Attribute (4b x 8)
					 *  defines the PAGE SIZE to be used
					 *	क्रम the rank
					 *  7    reserved
					 *  6:4  row attr of odd rank, i.e. 1
					 *  3    reserved
					 *  2:0  row attr of even rank, i.e. 0
					 *
					 * 000 = unpopulated
					 * 001 = reserved
					 * 010 = 4KiB
					 * 011 = 8KiB
					 * 100 = 16KiB
					 * others = reserved
					 */
#घोषणा I82975X_DRA_CH0R01		0x108
#घोषणा I82975X_DRA_CH0R23		0x109
#घोषणा I82975X_DRA_CH1R01		0x188
#घोषणा I82975X_DRA_CH1R23		0x189


#घोषणा I82975X_BNKARC	0x10e /* Type of device in each rank - Bank Arch (16b)
					 *
					 * 15:8  reserved
					 * 7:6  Rank 3 architecture
					 * 5:4  Rank 2 architecture
					 * 3:2  Rank 1 architecture
					 * 1:0  Rank 0 architecture
					 *
					 * 00 => 4 banks
					 * 01 => 8 banks
					 */
#घोषणा I82975X_C0BNKARC	0x10e
#घोषणा I82975X_C1BNKARC	0x18e



#घोषणा I82975X_DRC		0x120 /* DRAM Controller Mode0 (32b)
					 *
					 * 31:30 reserved
					 * 29    init complete
					 * 28:11 reserved, according to Intel
					 *    22:21 number of channels
					 *		00=1 01=2 in 82875
					 *		seems to be ECC mode
					 *		bits in 82975 in Asus
					 *		P5W
					 *	 19:18 Data Integ Mode
					 *		00=none 01=ECC in 82875
					 * 10:8  refresh mode
					 *  7    reserved
					 *  6:4  mode select
					 *  3:2  reserved
					 *  1:0  DRAM type 10=Second Revision
					 *		DDR2 SDRAM
					 *         00, 01, 11 reserved
					 */
#घोषणा I82975X_DRC_CH0M0		0x120
#घोषणा I82975X_DRC_CH1M0		0x1A0


#घोषणा I82975X_DRC_M1	0x124 /* DRAM Controller Mode1 (32b)
					 * 31	0=Standard Address Map
					 *	1=Enhanced Address Map
					 * 30:0	reserved
					 */

#घोषणा I82975X_DRC_CH0M1		0x124
#घोषणा I82975X_DRC_CH1M1		0x1A4

क्रमागत i82975x_chips अणु
	I82975X = 0,
पूर्ण;

काष्ठा i82975x_pvt अणु
	व्योम __iomem *mch_winकरोw;
पूर्ण;

काष्ठा i82975x_dev_info अणु
	स्थिर अक्षर *ctl_name;
पूर्ण;

काष्ठा i82975x_error_info अणु
	u16 errsts;
	u32 eap;
	u8 des;
	u8 derrsyn;
	u16 errsts2;
	u8 chan;		/* the channel is bit 0 of EAP */
	u8 xeap;		/* extended eap bit */
पूर्ण;

अटल स्थिर काष्ठा i82975x_dev_info i82975x_devs[] = अणु
	[I82975X] = अणु
		.ctl_name = "i82975x"
	पूर्ण,
पूर्ण;

अटल काष्ठा pci_dev *mci_pdev;	/* init dev: in हाल that AGP code has
					 * alपढ़ोy रेजिस्टरed driver
					 */

अटल पूर्णांक i82975x_रेजिस्टरed = 1;

अटल व्योम i82975x_get_error_info(काष्ठा mem_ctl_info *mci,
		काष्ठा i82975x_error_info *info)
अणु
	काष्ठा pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because there is no atomic way to पढ़ो all the
	 * रेजिस्टरs at once and the रेजिस्टरs can transition from CE being
	 * overwritten by UE.
	 */
	pci_पढ़ो_config_word(pdev, I82975X_ERRSTS, &info->errsts);
	pci_पढ़ो_config_dword(pdev, I82975X_EAP, &info->eap);
	pci_पढ़ो_config_byte(pdev, I82975X_XEAP, &info->xeap);
	pci_पढ़ो_config_byte(pdev, I82975X_DES, &info->des);
	pci_पढ़ो_config_byte(pdev, I82975X_DERRSYN, &info->derrsyn);
	pci_पढ़ो_config_word(pdev, I82975X_ERRSTS, &info->errsts2);

	pci_ग_लिखो_bits16(pdev, I82975X_ERRSTS, 0x0003, 0x0003);

	/*
	 * If the error is the same then we can क्रम both पढ़ोs then
	 * the first set of पढ़ोs is valid.  If there is a change then
	 * there is a CE no info and the second set of पढ़ोs is valid
	 * and should be UE info.
	 */
	अगर (!(info->errsts2 & 0x0003))
		वापस;

	अगर ((info->errsts ^ info->errsts2) & 0x0003) अणु
		pci_पढ़ो_config_dword(pdev, I82975X_EAP, &info->eap);
		pci_पढ़ो_config_byte(pdev, I82975X_XEAP, &info->xeap);
		pci_पढ़ो_config_byte(pdev, I82975X_DES, &info->des);
		pci_पढ़ो_config_byte(pdev, I82975X_DERRSYN,
				&info->derrsyn);
	पूर्ण
पूर्ण

अटल पूर्णांक i82975x_process_error_info(काष्ठा mem_ctl_info *mci,
		काष्ठा i82975x_error_info *info, पूर्णांक handle_errors)
अणु
	पूर्णांक row, chan;
	अचिन्हित दीर्घ offst, page;

	अगर (!(info->errsts2 & 0x0003))
		वापस 0;

	अगर (!handle_errors)
		वापस 1;

	अगर ((info->errsts ^ info->errsts2) & 0x0003) अणु
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, "UE overwrote CE", "");
		info->errsts = info->errsts2;
	पूर्ण

	page = (अचिन्हित दीर्घ) info->eap;
	page >>= 1;
	अगर (info->xeap & 1)
		page |= 0x80000000;
	page >>= (PAGE_SHIFT - 1);
	row = edac_mc_find_csrow_by_page(mci, page);

	अगर (row == -1)	अणु
		i82975x_mc_prपूर्णांकk(mci, KERN_ERR, "error processing EAP:\n"
			"\tXEAP=%u\n"
			"\t EAP=0x%08x\n"
			"\tPAGE=0x%08x\n",
			(info->xeap & 1) ? 1 : 0, info->eap, (अचिन्हित पूर्णांक) page);
		वापस 0;
	पूर्ण
	chan = (mci->csrows[row]->nr_channels == 1) ? 0 : info->eap & 1;
	offst = info->eap
			& ((1 << PAGE_SHIFT) -
			   (1 << mci->csrows[row]->channels[chan]->dimm->grain));

	अगर (info->errsts & 0x0002)
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     page, offst, 0,
				     row, -1, -1,
				     "i82975x UE", "");
	अन्यथा
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
				     page, offst, info->derrsyn,
				     row, chan ? chan : 0, -1,
				     "i82975x CE", "");

	वापस 1;
पूर्ण

अटल व्योम i82975x_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i82975x_error_info info;

	i82975x_get_error_info(mci, &info);
	i82975x_process_error_info(mci, &info, 1);
पूर्ण

/* Return 1 अगर dual channel mode is active.  Else वापस 0. */
अटल पूर्णांक dual_channel_active(व्योम __iomem *mch_winकरोw)
अणु
	/*
	 * We treat पूर्णांकerleaved-symmetric configuration as dual-channel - EAP's
	 * bit-0 giving the channel of the error location.
	 *
	 * All other configurations are treated as single channel - the EAP's
	 * bit-0 will resolve ok in symmetric area of mixed
	 * (symmetric/asymmetric) configurations
	 */
	u8	drb[4][2];
	पूर्णांक	row;
	पूर्णांक    dualch;

	क्रम (dualch = 1, row = 0; dualch && (row < 4); row++) अणु
		drb[row][0] = पढ़ोb(mch_winकरोw + I82975X_DRB + row);
		drb[row][1] = पढ़ोb(mch_winकरोw + I82975X_DRB + row + 0x80);
		dualch = dualch && (drb[row][0] == drb[row][1]);
	पूर्ण
	वापस dualch;
पूर्ण

अटल व्योम i82975x_init_csrows(काष्ठा mem_ctl_info *mci,
		काष्ठा pci_dev *pdev, व्योम __iomem *mch_winकरोw)
अणु
	काष्ठा csrow_info *csrow;
	अचिन्हित दीर्घ last_cumul_size;
	u8 value;
	u32 cumul_size, nr_pages;
	पूर्णांक index, chan;
	काष्ठा dimm_info *dimm;

	last_cumul_size = 0;

	/*
	 * 82875 comment:
	 * The dram row boundary (DRB) reg values are boundary address
	 * क्रम each DRAM row with a granularity of 32 or 64MB (single/dual
	 * channel operation).  DRB regs are cumulative; thereक्रमe DRB7 will
	 * contain the total memory contained in all rows.
	 *
	 */

	क्रम (index = 0; index < mci->nr_csrows; index++) अणु
		csrow = mci->csrows[index];

		value = पढ़ोb(mch_winकरोw + I82975X_DRB + index +
					((index >= 4) ? 0x80 : 0));
		cumul_size = value;
		cumul_size <<= (I82975X_DRB_SHIFT - PAGE_SHIFT);
		/*
		 * Adjust cumul_size w.r.t number of channels
		 *
		 */
		अगर (csrow->nr_channels > 1)
			cumul_size <<= 1;
		edac_dbg(3, "(%d) cumul_size 0x%x\n", index, cumul_size);

		nr_pages = cumul_size - last_cumul_size;
		अगर (!nr_pages)
			जारी;

		/*
		 * Initialise dram labels
		 * index values:
		 *   [0-7] क्रम single-channel; i.e. csrow->nr_channels = 1
		 *   [0-3] क्रम dual-channel; i.e. csrow->nr_channels = 2
		 */
		क्रम (chan = 0; chan < csrow->nr_channels; chan++) अणु
			dimm = mci->csrows[index]->channels[chan]->dimm;

			dimm->nr_pages = nr_pages / csrow->nr_channels;

			snम_लिखो(csrow->channels[chan]->dimm->label, EDAC_MC_LABEL_LEN, "DIMM %c%d",
				 (chan == 0) ? 'A' : 'B',
				 index);
			dimm->grain = 1 << 7;	/* 128Byte cache-line resolution */

			/* ECC is possible on i92975x ONLY with DEV_X8.  */
			dimm->dtype = DEV_X8;

			dimm->mtype = MEM_DDR2; /* I82975x supports only DDR2 */
			dimm->edac_mode = EDAC_SECDED; /* only supported */
		पूर्ण

		csrow->first_page = last_cumul_size;
		csrow->last_page = cumul_size - 1;
		last_cumul_size = cumul_size;
	पूर्ण
पूर्ण

/* #घोषणा  i82975x_DEBUG_IOMEM */

#अगर_घोषित i82975x_DEBUG_IOMEM
अटल व्योम i82975x_prपूर्णांक_dram_timings(व्योम __iomem *mch_winकरोw)
अणु
	/*
	 * The रेजिस्टर meanings are from Intel specs;
	 * (shows 13-5-5-5 क्रम 800-DDR2)
	 * Asus P5W Bios reports 15-5-4-4
	 * What's your religion?
	 */
	अटल स्थिर पूर्णांक caslats[4] = अणु 5, 4, 3, 6 पूर्ण;
	u32	dtreg[2];

	dtreg[0] = पढ़ोl(mch_winकरोw + 0x114);
	dtreg[1] = पढ़ोl(mch_winकरोw + 0x194);
	i82975x_prपूर्णांकk(KERN_INFO, "DRAM Timings :     Ch0    Ch1\n"
		"                RAS Active Min = %d     %d\n"
		"                CAS latency    =  %d      %d\n"
		"                RAS to CAS     =  %d      %d\n"
		"                RAS precharge  =  %d      %d\n",
		(dtreg[0] >> 19 ) & 0x0f,
			(dtreg[1] >> 19) & 0x0f,
		caslats[(dtreg[0] >> 8) & 0x03],
			caslats[(dtreg[1] >> 8) & 0x03],
		((dtreg[0] >> 4) & 0x07) + 2,
			((dtreg[1] >> 4) & 0x07) + 2,
		(dtreg[0] & 0x07) + 2,
			(dtreg[1] & 0x07) + 2
	);

पूर्ण
#पूर्ण_अगर

अटल पूर्णांक i82975x_probe1(काष्ठा pci_dev *pdev, पूर्णांक dev_idx)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा i82975x_pvt *pvt;
	व्योम __iomem *mch_winकरोw;
	u32 mchbar;
	u32 drc[2];
	काष्ठा i82975x_error_info discard;
	पूर्णांक	chans;
#अगर_घोषित i82975x_DEBUG_IOMEM
	u8 c0drb[4];
	u8 c1drb[4];
#पूर्ण_अगर

	edac_dbg(0, "\n");

	pci_पढ़ो_config_dword(pdev, I82975X_MCHBAR, &mchbar);
	अगर (!(mchbar & 1)) अणु
		edac_dbg(3, "failed, MCHBAR disabled!\n");
		जाओ fail0;
	पूर्ण
	mchbar &= 0xffffc000;	/* bits 31:14 used क्रम 16K winकरोw */
	mch_winकरोw = ioremap(mchbar, 0x1000);
	अगर (!mch_winकरोw) अणु
		edac_dbg(3, "error ioremapping MCHBAR!\n");
		जाओ fail0;
	पूर्ण

#अगर_घोषित i82975x_DEBUG_IOMEM
	i82975x_prपूर्णांकk(KERN_INFO, "MCHBAR real = %0x, remapped = %p\n",
					mchbar, mch_winकरोw);

	c0drb[0] = पढ़ोb(mch_winकरोw + I82975X_DRB_CH0R0);
	c0drb[1] = पढ़ोb(mch_winकरोw + I82975X_DRB_CH0R1);
	c0drb[2] = पढ़ोb(mch_winकरोw + I82975X_DRB_CH0R2);
	c0drb[3] = पढ़ोb(mch_winकरोw + I82975X_DRB_CH0R3);
	c1drb[0] = पढ़ोb(mch_winकरोw + I82975X_DRB_CH1R0);
	c1drb[1] = पढ़ोb(mch_winकरोw + I82975X_DRB_CH1R1);
	c1drb[2] = पढ़ोb(mch_winकरोw + I82975X_DRB_CH1R2);
	c1drb[3] = पढ़ोb(mch_winकरोw + I82975X_DRB_CH1R3);
	i82975x_prपूर्णांकk(KERN_INFO, "DRBCH0R0 = 0x%02x\n", c0drb[0]);
	i82975x_prपूर्णांकk(KERN_INFO, "DRBCH0R1 = 0x%02x\n", c0drb[1]);
	i82975x_prपूर्णांकk(KERN_INFO, "DRBCH0R2 = 0x%02x\n", c0drb[2]);
	i82975x_prपूर्णांकk(KERN_INFO, "DRBCH0R3 = 0x%02x\n", c0drb[3]);
	i82975x_prपूर्णांकk(KERN_INFO, "DRBCH1R0 = 0x%02x\n", c1drb[0]);
	i82975x_prपूर्णांकk(KERN_INFO, "DRBCH1R1 = 0x%02x\n", c1drb[1]);
	i82975x_prपूर्णांकk(KERN_INFO, "DRBCH1R2 = 0x%02x\n", c1drb[2]);
	i82975x_prपूर्णांकk(KERN_INFO, "DRBCH1R3 = 0x%02x\n", c1drb[3]);
#पूर्ण_अगर

	drc[0] = पढ़ोl(mch_winकरोw + I82975X_DRC_CH0M0);
	drc[1] = पढ़ोl(mch_winकरोw + I82975X_DRC_CH1M0);
#अगर_घोषित i82975x_DEBUG_IOMEM
	i82975x_prपूर्णांकk(KERN_INFO, "DRC_CH0 = %0x, %s\n", drc[0],
			((drc[0] >> 21) & 3) == 1 ?
				"ECC enabled" : "ECC disabled");
	i82975x_prपूर्णांकk(KERN_INFO, "DRC_CH1 = %0x, %s\n", drc[1],
			((drc[1] >> 21) & 3) == 1 ?
				"ECC enabled" : "ECC disabled");

	i82975x_prपूर्णांकk(KERN_INFO, "C0 BNKARC = %0x\n",
		पढ़ोw(mch_winकरोw + I82975X_C0BNKARC));
	i82975x_prपूर्णांकk(KERN_INFO, "C1 BNKARC = %0x\n",
		पढ़ोw(mch_winकरोw + I82975X_C1BNKARC));
	i82975x_prपूर्णांक_dram_timings(mch_winकरोw);
	जाओ fail1;
#पूर्ण_अगर
	अगर (!(((drc[0] >> 21) & 3) == 1 || ((drc[1] >> 21) & 3) == 1)) अणु
		i82975x_prपूर्णांकk(KERN_INFO, "ECC disabled on both channels.\n");
		जाओ fail1;
	पूर्ण

	chans = dual_channel_active(mch_winकरोw) + 1;

	/* assuming only one controller, index thus is 0 */
	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = I82975X_NR_DIMMS;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = I82975X_NR_CSROWS(chans);
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, माप(*pvt));
	अगर (!mci) अणु
		rc = -ENOMEM;
		जाओ fail1;
	पूर्ण

	edac_dbg(3, "init mci\n");
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FLAG_DDR2;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_NONE | EDAC_FLAG_SECDED;
	mci->mod_name = EDAC_MOD_STR;
	mci->ctl_name = i82975x_devs[dev_idx].ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = i82975x_check;
	mci->ctl_page_to_phys = शून्य;
	edac_dbg(3, "init pvt\n");
	pvt = (काष्ठा i82975x_pvt *) mci->pvt_info;
	pvt->mch_winकरोw = mch_winकरोw;
	i82975x_init_csrows(mci, pdev, mch_winकरोw);
	mci->scrub_mode = SCRUB_HW_SRC;
	i82975x_get_error_info(mci, &discard);  /* clear counters */

	/* finalize this instance of memory controller with edac core */
	अगर (edac_mc_add_mc(mci)) अणु
		edac_dbg(3, "failed edac_mc_add_mc()\n");
		जाओ fail2;
	पूर्ण

	/* get this far and it's successful */
	edac_dbg(3, "success\n");
	वापस 0;

fail2:
	edac_mc_मुक्त(mci);

fail1:
	iounmap(mch_winकरोw);
fail0:
	वापस rc;
पूर्ण

/* वापसs count (>= 0), or negative on error */
अटल पूर्णांक i82975x_init_one(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rc;

	edac_dbg(0, "\n");

	अगर (pci_enable_device(pdev) < 0)
		वापस -EIO;

	rc = i82975x_probe1(pdev, ent->driver_data);

	अगर (mci_pdev == शून्य)
		mci_pdev = pci_dev_get(pdev);

	वापस rc;
पूर्ण

अटल व्योम i82975x_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा i82975x_pvt *pvt;

	edac_dbg(0, "\n");

	mci = edac_mc_del_mc(&pdev->dev);
	अगर (mci  == शून्य)
		वापस;

	pvt = mci->pvt_info;
	अगर (pvt->mch_winकरोw)
		iounmap( pvt->mch_winकरोw );

	edac_mc_मुक्त(mci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id i82975x_pci_tbl[] = अणु
	अणु
		PCI_VEND_DEV(INTEL, 82975_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		I82975X
	पूर्ण,
	अणु
		0,
	पूर्ण	/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, i82975x_pci_tbl);

अटल काष्ठा pci_driver i82975x_driver = अणु
	.name = EDAC_MOD_STR,
	.probe = i82975x_init_one,
	.हटाओ = i82975x_हटाओ_one,
	.id_table = i82975x_pci_tbl,
पूर्ण;

अटल पूर्णांक __init i82975x_init(व्योम)
अणु
	पूर्णांक pci_rc;

	edac_dbg(3, "\n");

	/* Ensure that the OPSTATE is set correctly क्रम POLL or NMI */
	opstate_init();

	pci_rc = pci_रेजिस्टर_driver(&i82975x_driver);
	अगर (pci_rc < 0)
		जाओ fail0;

	अगर (mci_pdev == शून्य) अणु
		mci_pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
				PCI_DEVICE_ID_INTEL_82975_0, शून्य);

		अगर (!mci_pdev) अणु
			edac_dbg(0, "i82975x pci_get_device fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण

		pci_rc = i82975x_init_one(mci_pdev, i82975x_pci_tbl);

		अगर (pci_rc < 0) अणु
			edac_dbg(0, "i82975x init fail\n");
			pci_rc = -ENODEV;
			जाओ fail1;
		पूर्ण
	पूर्ण

	वापस 0;

fail1:
	pci_unरेजिस्टर_driver(&i82975x_driver);

fail0:
	pci_dev_put(mci_pdev);
	वापस pci_rc;
पूर्ण

अटल व्योम __निकास i82975x_निकास(व्योम)
अणु
	edac_dbg(3, "\n");

	pci_unरेजिस्टर_driver(&i82975x_driver);

	अगर (!i82975x_रेजिस्टरed) अणु
		i82975x_हटाओ_one(mci_pdev);
		pci_dev_put(mci_pdev);
	पूर्ण
पूर्ण

module_init(i82975x_init);
module_निकास(i82975x_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arvind R. <arvino55@gmail.com>");
MODULE_DESCRIPTION("MC support for Intel 82975 memory hub controllers");

module_param(edac_op_state, पूर्णांक, 0444);
MODULE_PARM_DESC(edac_op_state, "EDAC Error Reporting state: 0=Poll,1=NMI");
