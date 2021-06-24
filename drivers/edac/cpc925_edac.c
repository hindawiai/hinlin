<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cpc925_edac.c, EDAC driver क्रम IBM CPC925 Bridge and Memory Controller.
 *
 * Copyright (c) 2008 Wind River Systems, Inc.
 *
 * Authors:	Cao Qingtao <qingtao.cao@windriver.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/edac.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gfp.h>

#समावेश "edac_module.h"

#घोषणा CPC925_EDAC_REVISION	" Ver: 1.0.0"
#घोषणा CPC925_EDAC_MOD_STR	"cpc925_edac"

#घोषणा cpc925_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "CPC925", fmt, ##arg)

#घोषणा cpc925_mc_prपूर्णांकk(mci, level, fmt, arg...) \
	edac_mc_chipset_prपूर्णांकk(mci, level, "CPC925", fmt, ##arg)

/*
 * CPC925 रेजिस्टरs are of 32 bits with bit0 defined at the
 * most signअगरicant bit and bit31 at that of least signअगरicant.
 */
#घोषणा CPC925_BITS_PER_REG	32
#घोषणा CPC925_BIT(nr)		(1UL << (CPC925_BITS_PER_REG - 1 - nr))

/*
 * EDAC device names क्रम the error detections of
 * CPU Interface and Hypertransport Link.
 */
#घोषणा CPC925_CPU_ERR_DEV	"cpu"
#घोषणा CPC925_HT_LINK_DEV	"htlink"

/* Suppose DDR Refresh cycle is 15.6 microsecond */
#घोषणा CPC925_REF_FREQ		0xFA69
#घोषणा CPC925_SCRUB_BLOCK_SIZE 64	/* bytes */
#घोषणा CPC925_NR_CSROWS	8

/*
 * All रेजिस्टरs and bits definitions are taken from
 * "CPC925 Bridge and Memory Controller User Manual, SA14-2761-02".
 */

/*
 * CPU and Memory Controller Registers
 */
/************************************************************
 *	Processor Interface Exception Mask Register (APIMASK)
 ************************************************************/
#घोषणा REG_APIMASK_OFFSET	0x30070
क्रमागत apimask_bits अणु
	APIMASK_DART	= CPC925_BIT(0), /* DART Exception */
	APIMASK_ADI0	= CPC925_BIT(1), /* Handshake Error on PI0_ADI */
	APIMASK_ADI1	= CPC925_BIT(2), /* Handshake Error on PI1_ADI */
	APIMASK_STAT	= CPC925_BIT(3), /* Status Exception */
	APIMASK_DERR	= CPC925_BIT(4), /* Data Error Exception */
	APIMASK_ADRS0	= CPC925_BIT(5), /* Addressing Exception on PI0 */
	APIMASK_ADRS1	= CPC925_BIT(6), /* Addressing Exception on PI1 */
					 /* BIT(7) Reserved */
	APIMASK_ECC_UE_H = CPC925_BIT(8), /* UECC upper */
	APIMASK_ECC_CE_H = CPC925_BIT(9), /* CECC upper */
	APIMASK_ECC_UE_L = CPC925_BIT(10), /* UECC lower */
	APIMASK_ECC_CE_L = CPC925_BIT(11), /* CECC lower */

	CPU_MASK_ENABLE = (APIMASK_DART | APIMASK_ADI0 | APIMASK_ADI1 |
			   APIMASK_STAT | APIMASK_DERR | APIMASK_ADRS0 |
			   APIMASK_ADRS1),
	ECC_MASK_ENABLE = (APIMASK_ECC_UE_H | APIMASK_ECC_CE_H |
			   APIMASK_ECC_UE_L | APIMASK_ECC_CE_L),
पूर्ण;
#घोषणा APIMASK_ADI(n)		CPC925_BIT(((n)+1))

/************************************************************
 *	Processor Interface Exception Register (APIEXCP)
 ************************************************************/
#घोषणा REG_APIEXCP_OFFSET	0x30060
क्रमागत apiexcp_bits अणु
	APIEXCP_DART	= CPC925_BIT(0), /* DART Exception */
	APIEXCP_ADI0	= CPC925_BIT(1), /* Handshake Error on PI0_ADI */
	APIEXCP_ADI1	= CPC925_BIT(2), /* Handshake Error on PI1_ADI */
	APIEXCP_STAT	= CPC925_BIT(3), /* Status Exception */
	APIEXCP_DERR	= CPC925_BIT(4), /* Data Error Exception */
	APIEXCP_ADRS0	= CPC925_BIT(5), /* Addressing Exception on PI0 */
	APIEXCP_ADRS1	= CPC925_BIT(6), /* Addressing Exception on PI1 */
					 /* BIT(7) Reserved */
	APIEXCP_ECC_UE_H = CPC925_BIT(8), /* UECC upper */
	APIEXCP_ECC_CE_H = CPC925_BIT(9), /* CECC upper */
	APIEXCP_ECC_UE_L = CPC925_BIT(10), /* UECC lower */
	APIEXCP_ECC_CE_L = CPC925_BIT(11), /* CECC lower */

	CPU_EXCP_DETECTED = (APIEXCP_DART | APIEXCP_ADI0 | APIEXCP_ADI1 |
			     APIEXCP_STAT | APIEXCP_DERR | APIEXCP_ADRS0 |
			     APIEXCP_ADRS1),
	UECC_EXCP_DETECTED = (APIEXCP_ECC_UE_H | APIEXCP_ECC_UE_L),
	CECC_EXCP_DETECTED = (APIEXCP_ECC_CE_H | APIEXCP_ECC_CE_L),
	ECC_EXCP_DETECTED = (UECC_EXCP_DETECTED | CECC_EXCP_DETECTED),
पूर्ण;

/************************************************************
 *	Memory Bus Configuration Register (MBCR)
************************************************************/
#घोषणा REG_MBCR_OFFSET		0x2190
#घोषणा MBCR_64BITCFG_SHIFT	23
#घोषणा MBCR_64BITCFG_MASK	(1UL << MBCR_64BITCFG_SHIFT)
#घोषणा MBCR_64BITBUS_SHIFT	22
#घोषणा MBCR_64BITBUS_MASK	(1UL << MBCR_64BITBUS_SHIFT)

/************************************************************
 *	Memory Bank Mode Register (MBMR)
************************************************************/
#घोषणा REG_MBMR_OFFSET		0x21C0
#घोषणा MBMR_MODE_MAX_VALUE	0xF
#घोषणा MBMR_MODE_SHIFT		25
#घोषणा MBMR_MODE_MASK		(MBMR_MODE_MAX_VALUE << MBMR_MODE_SHIFT)
#घोषणा MBMR_BBA_SHIFT		24
#घोषणा MBMR_BBA_MASK		(1UL << MBMR_BBA_SHIFT)

/************************************************************
 *	Memory Bank Boundary Address Register (MBBAR)
 ************************************************************/
#घोषणा REG_MBBAR_OFFSET	0x21D0
#घोषणा MBBAR_BBA_MAX_VALUE	0xFF
#घोषणा MBBAR_BBA_SHIFT		24
#घोषणा MBBAR_BBA_MASK		(MBBAR_BBA_MAX_VALUE << MBBAR_BBA_SHIFT)

/************************************************************
 *	Memory Scrub Control Register (MSCR)
 ************************************************************/
#घोषणा REG_MSCR_OFFSET		0x2400
#घोषणा MSCR_SCRUB_MOD_MASK	0xC0000000 /* scrub_mod - bit0:1*/
#घोषणा MSCR_BACKGR_SCRUB	0x40000000 /* 01 */
#घोषणा MSCR_SI_SHIFT		16 	/* si - bit8:15*/
#घोषणा MSCR_SI_MAX_VALUE	0xFF
#घोषणा MSCR_SI_MASK		(MSCR_SI_MAX_VALUE << MSCR_SI_SHIFT)

/************************************************************
 *	Memory Scrub Range Start Register (MSRSR)
 ************************************************************/
#घोषणा REG_MSRSR_OFFSET	0x2410

/************************************************************
 *	Memory Scrub Range End Register (MSRER)
 ************************************************************/
#घोषणा REG_MSRER_OFFSET	0x2420

/************************************************************
 *	Memory Scrub Pattern Register (MSPR)
 ************************************************************/
#घोषणा REG_MSPR_OFFSET		0x2430

/************************************************************
 *	Memory Check Control Register (MCCR)
 ************************************************************/
#घोषणा REG_MCCR_OFFSET		0x2440
क्रमागत mccr_bits अणु
	MCCR_ECC_EN	= CPC925_BIT(0), /* ECC high and low check */
पूर्ण;

/************************************************************
 *	Memory Check Range End Register (MCRER)
 ************************************************************/
#घोषणा REG_MCRER_OFFSET	0x2450

/************************************************************
 *	Memory Error Address Register (MEAR)
 ************************************************************/
#घोषणा REG_MEAR_OFFSET		0x2460
#घोषणा MEAR_BCNT_MAX_VALUE	0x3
#घोषणा MEAR_BCNT_SHIFT		30
#घोषणा MEAR_BCNT_MASK		(MEAR_BCNT_MAX_VALUE << MEAR_BCNT_SHIFT)
#घोषणा MEAR_RANK_MAX_VALUE	0x7
#घोषणा MEAR_RANK_SHIFT		27
#घोषणा MEAR_RANK_MASK		(MEAR_RANK_MAX_VALUE << MEAR_RANK_SHIFT)
#घोषणा MEAR_COL_MAX_VALUE	0x7FF
#घोषणा MEAR_COL_SHIFT		16
#घोषणा MEAR_COL_MASK		(MEAR_COL_MAX_VALUE << MEAR_COL_SHIFT)
#घोषणा MEAR_BANK_MAX_VALUE	0x3
#घोषणा MEAR_BANK_SHIFT		14
#घोषणा MEAR_BANK_MASK		(MEAR_BANK_MAX_VALUE << MEAR_BANK_SHIFT)
#घोषणा MEAR_ROW_MASK		0x00003FFF

/************************************************************
 *	Memory Error Syndrome Register (MESR)
 ************************************************************/
#घोषणा REG_MESR_OFFSET		0x2470
#घोषणा MESR_ECC_SYN_H_MASK	0xFF00
#घोषणा MESR_ECC_SYN_L_MASK	0x00FF

/************************************************************
 *	Memory Mode Control Register (MMCR)
 ************************************************************/
#घोषणा REG_MMCR_OFFSET		0x2500
क्रमागत mmcr_bits अणु
	MMCR_REG_DIMM_MODE = CPC925_BIT(3),
पूर्ण;

/*
 * HyperTransport Link Registers
 */
/************************************************************
 *  Error Handling/Enumeration Scratch Pad Register (ERRCTRL)
 ************************************************************/
#घोषणा REG_ERRCTRL_OFFSET	0x70140
क्रमागत errctrl_bits अणु			 /* nonfatal पूर्णांकerrupts क्रम */
	ERRCTRL_SERR_NF	= CPC925_BIT(0), /* प्रणाली error */
	ERRCTRL_CRC_NF	= CPC925_BIT(1), /* CRC error */
	ERRCTRL_RSP_NF	= CPC925_BIT(2), /* Response error */
	ERRCTRL_EOC_NF	= CPC925_BIT(3), /* End-Of-Chain error */
	ERRCTRL_OVF_NF	= CPC925_BIT(4), /* Overflow error */
	ERRCTRL_PROT_NF	= CPC925_BIT(5), /* Protocol error */

	ERRCTRL_RSP_ERR	= CPC925_BIT(6), /* Response error received */
	ERRCTRL_CHN_FAL = CPC925_BIT(7), /* Sync flooding detected */

	HT_ERRCTRL_ENABLE = (ERRCTRL_SERR_NF | ERRCTRL_CRC_NF |
			     ERRCTRL_RSP_NF | ERRCTRL_EOC_NF |
			     ERRCTRL_OVF_NF | ERRCTRL_PROT_NF),
	HT_ERRCTRL_DETECTED = (ERRCTRL_RSP_ERR | ERRCTRL_CHN_FAL),
पूर्ण;

/************************************************************
 *  Link Configuration and Link Control Register (LINKCTRL)
 ************************************************************/
#घोषणा REG_LINKCTRL_OFFSET	0x70110
क्रमागत linkctrl_bits अणु
	LINKCTRL_CRC_ERR	= (CPC925_BIT(22) | CPC925_BIT(23)),
	LINKCTRL_LINK_FAIL	= CPC925_BIT(27),

	HT_LINKCTRL_DETECTED	= (LINKCTRL_CRC_ERR | LINKCTRL_LINK_FAIL),
पूर्ण;

/************************************************************
 *  Link FreqCap/Error/Freq/Revision ID Register (LINKERR)
 ************************************************************/
#घोषणा REG_LINKERR_OFFSET	0x70120
क्रमागत linkerr_bits अणु
	LINKERR_EOC_ERR		= CPC925_BIT(17), /* End-Of-Chain error */
	LINKERR_OVF_ERR		= CPC925_BIT(18), /* Receive Buffer Overflow */
	LINKERR_PROT_ERR	= CPC925_BIT(19), /* Protocol error */

	HT_LINKERR_DETECTED	= (LINKERR_EOC_ERR | LINKERR_OVF_ERR |
				   LINKERR_PROT_ERR),
पूर्ण;

/************************************************************
 *	Bridge Control Register (BRGCTRL)
 ************************************************************/
#घोषणा REG_BRGCTRL_OFFSET	0x70300
क्रमागत brgctrl_bits अणु
	BRGCTRL_DETSERR = CPC925_BIT(0), /* SERR on Secondary Bus */
	BRGCTRL_SECBUSRESET = CPC925_BIT(9), /* Secondary Bus Reset */
पूर्ण;

/* Private काष्ठाure क्रम edac memory controller */
काष्ठा cpc925_mc_pdata अणु
	व्योम __iomem *vbase;
	अचिन्हित दीर्घ total_mem;
	स्थिर अक्षर *name;
	पूर्णांक edac_idx;
पूर्ण;

/* Private काष्ठाure क्रम common edac device */
काष्ठा cpc925_dev_info अणु
	व्योम __iomem *vbase;
	काष्ठा platक्रमm_device *pdev;
	अक्षर *ctl_name;
	पूर्णांक edac_idx;
	काष्ठा edac_device_ctl_info *edac_dev;
	व्योम (*init)(काष्ठा cpc925_dev_info *dev_info);
	व्योम (*निकास)(काष्ठा cpc925_dev_info *dev_info);
	व्योम (*check)(काष्ठा edac_device_ctl_info *edac_dev);
पूर्ण;

/* Get total memory size from Open Firmware DTB */
अटल व्योम get_total_mem(काष्ठा cpc925_mc_pdata *pdata)
अणु
	काष्ठा device_node *np = शून्य;
	स्थिर अचिन्हित पूर्णांक *reg, *reg_end;
	पूर्णांक len, sw, aw;
	अचिन्हित दीर्घ start, size;

	np = of_find_node_by_type(शून्य, "memory");
	अगर (!np)
		वापस;

	aw = of_n_addr_cells(np);
	sw = of_n_size_cells(np);
	reg = (स्थिर अचिन्हित पूर्णांक *)of_get_property(np, "reg", &len);
	reg_end = reg + len/4;

	pdata->total_mem = 0;
	करो अणु
		start = of_पढ़ो_number(reg, aw);
		reg += aw;
		size = of_पढ़ो_number(reg, sw);
		reg += sw;
		edac_dbg(1, "start 0x%lx, size 0x%lx\n", start, size);
		pdata->total_mem += size;
	पूर्ण जबतक (reg < reg_end);

	of_node_put(np);
	edac_dbg(0, "total_mem 0x%lx\n", pdata->total_mem);
पूर्ण

अटल व्योम cpc925_init_csrows(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा cpc925_mc_pdata *pdata = mci->pvt_info;
	काष्ठा csrow_info *csrow;
	काष्ठा dimm_info *dimm;
	क्रमागत dev_type dtype;
	पूर्णांक index, j;
	u32 mbmr, mbbar, bba, grain;
	अचिन्हित दीर्घ row_size, nr_pages, last_nr_pages = 0;

	get_total_mem(pdata);

	क्रम (index = 0; index < mci->nr_csrows; index++) अणु
		mbmr = __raw_पढ़ोl(pdata->vbase + REG_MBMR_OFFSET +
				   0x20 * index);
		mbbar = __raw_पढ़ोl(pdata->vbase + REG_MBBAR_OFFSET +
				   0x20 + index);
		bba = (((mbmr & MBMR_BBA_MASK) >> MBMR_BBA_SHIFT) << 8) |
		       ((mbbar & MBBAR_BBA_MASK) >> MBBAR_BBA_SHIFT);

		अगर (bba == 0)
			जारी; /* not populated */

		csrow = mci->csrows[index];

		row_size = bba * (1UL << 28);	/* 256M */
		csrow->first_page = last_nr_pages;
		nr_pages = row_size >> PAGE_SHIFT;
		csrow->last_page = csrow->first_page + nr_pages - 1;
		last_nr_pages = csrow->last_page + 1;

		चयन (csrow->nr_channels) अणु
		हाल 1: /* Single channel */
			grain = 32; /* four-beat burst of 32 bytes */
			अवरोध;
		हाल 2: /* Dual channel */
		शेष:
			grain = 64; /* four-beat burst of 64 bytes */
			अवरोध;
		पूर्ण
		चयन ((mbmr & MBMR_MODE_MASK) >> MBMR_MODE_SHIFT) अणु
		हाल 6: /* 0110, no way to dअगरferentiate X8 VS X16 */
		हाल 5:	/* 0101 */
		हाल 8: /* 1000 */
			dtype = DEV_X16;
			अवरोध;
		हाल 7: /* 0111 */
		हाल 9: /* 1001 */
			dtype = DEV_X8;
			अवरोध;
		शेष:
			dtype = DEV_UNKNOWN;
		अवरोध;
		पूर्ण
		क्रम (j = 0; j < csrow->nr_channels; j++) अणु
			dimm = csrow->channels[j]->dimm;
			dimm->nr_pages = nr_pages / csrow->nr_channels;
			dimm->mtype = MEM_RDDR;
			dimm->edac_mode = EDAC_SECDED;
			dimm->grain = grain;
			dimm->dtype = dtype;
		पूर्ण
	पूर्ण
पूर्ण

/* Enable memory controller ECC detection */
अटल व्योम cpc925_mc_init(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा cpc925_mc_pdata *pdata = mci->pvt_info;
	u32 apimask;
	u32 mccr;

	/* Enable various ECC error exceptions */
	apimask = __raw_पढ़ोl(pdata->vbase + REG_APIMASK_OFFSET);
	अगर ((apimask & ECC_MASK_ENABLE) == 0) अणु
		apimask |= ECC_MASK_ENABLE;
		__raw_ग_लिखोl(apimask, pdata->vbase + REG_APIMASK_OFFSET);
	पूर्ण

	/* Enable ECC detection */
	mccr = __raw_पढ़ोl(pdata->vbase + REG_MCCR_OFFSET);
	अगर ((mccr & MCCR_ECC_EN) == 0) अणु
		mccr |= MCCR_ECC_EN;
		__raw_ग_लिखोl(mccr, pdata->vbase + REG_MCCR_OFFSET);
	पूर्ण
पूर्ण

/* Disable memory controller ECC detection */
अटल व्योम cpc925_mc_निकास(काष्ठा mem_ctl_info *mci)
अणु
	/*
	 * WARNING:
	 * We are supposed to clear the ECC error detection bits,
	 * and it will be no problem to करो so. However, once they
	 * are cleared here अगर we want to re-install CPC925 EDAC
	 * module later, setting them up in cpc925_mc_init() will
	 * trigger machine check exception.
	 * Also, it's ok to leave ECC error detection bits enabled,
	 * since they are reset to 1 by शेष or by boot loader.
	 */

	वापस;
पूर्ण

/*
 * Revert DDR column/row/bank addresses पूर्णांकo page frame number and
 * offset in page.
 *
 * Suppose memory mode is 0x0111(128-bit mode, identical DIMM pairs),
 * physical address(PA) bits to column address(CA) bits mappings are:
 * CA	0   1   2   3   4   5   6   7   8   9   10
 * PA	59  58  57  56  55  54  53  52  51  50  49
 *
 * physical address(PA) bits to bank address(BA) bits mappings are:
 * BA	0   1
 * PA	43  44
 *
 * physical address(PA) bits to row address(RA) bits mappings are:
 * RA	0   1   2   3   4   5   6   7   8   9   10   11   12
 * PA	36  35  34  48  47  46  45  40  41  42  39   38   37
 */
अटल व्योम cpc925_mc_get_pfn(काष्ठा mem_ctl_info *mci, u32 mear,
		अचिन्हित दीर्घ *pfn, अचिन्हित दीर्घ *offset, पूर्णांक *csrow)
अणु
	u32 bcnt, rank, col, bank, row;
	u32 c;
	अचिन्हित दीर्घ pa;
	पूर्णांक i;

	bcnt = (mear & MEAR_BCNT_MASK) >> MEAR_BCNT_SHIFT;
	rank = (mear & MEAR_RANK_MASK) >> MEAR_RANK_SHIFT;
	col = (mear & MEAR_COL_MASK) >> MEAR_COL_SHIFT;
	bank = (mear & MEAR_BANK_MASK) >> MEAR_BANK_SHIFT;
	row = mear & MEAR_ROW_MASK;

	*csrow = rank;

#अगर_घोषित CONFIG_EDAC_DEBUG
	अगर (mci->csrows[rank]->first_page == 0) अणु
		cpc925_mc_prपूर्णांकk(mci, KERN_ERR, "ECC occurs in a "
			"non-populated csrow, broken hardware?\n");
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* Revert csrow number */
	pa = mci->csrows[rank]->first_page << PAGE_SHIFT;

	/* Revert column address */
	col += bcnt;
	क्रम (i = 0; i < 11; i++) अणु
		c = col & 0x1;
		col >>= 1;
		pa |= c << (14 - i);
	पूर्ण

	/* Revert bank address */
	pa |= bank << 19;

	/* Revert row address, in 4 steps */
	क्रम (i = 0; i < 3; i++) अणु
		c = row & 0x1;
		row >>= 1;
		pa |= c << (26 - i);
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		c = row & 0x1;
		row >>= 1;
		pa |= c << (21 + i);
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		c = row & 0x1;
		row >>= 1;
		pa |= c << (18 - i);
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		c = row & 0x1;
		row >>= 1;
		pa |= c << (29 - i);
	पूर्ण

	*offset = pa & (PAGE_SIZE - 1);
	*pfn = pa >> PAGE_SHIFT;

	edac_dbg(0, "ECC physical address 0x%lx\n", pa);
पूर्ण

अटल पूर्णांक cpc925_mc_find_channel(काष्ठा mem_ctl_info *mci, u16 syndrome)
अणु
	अगर ((syndrome & MESR_ECC_SYN_H_MASK) == 0)
		वापस 0;

	अगर ((syndrome & MESR_ECC_SYN_L_MASK) == 0)
		वापस 1;

	cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "Unexpected syndrome value: 0x%x\n",
			 syndrome);
	वापस 1;
पूर्ण

/* Check memory controller रेजिस्टरs क्रम ECC errors */
अटल व्योम cpc925_mc_check(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा cpc925_mc_pdata *pdata = mci->pvt_info;
	u32 apiexcp;
	u32 mear;
	u32 mesr;
	u16 syndrome;
	अचिन्हित दीर्घ pfn = 0, offset = 0;
	पूर्णांक csrow = 0, channel = 0;

	/* APIEXCP is cleared when पढ़ो */
	apiexcp = __raw_पढ़ोl(pdata->vbase + REG_APIEXCP_OFFSET);
	अगर ((apiexcp & ECC_EXCP_DETECTED) == 0)
		वापस;

	mesr = __raw_पढ़ोl(pdata->vbase + REG_MESR_OFFSET);
	syndrome = mesr | (MESR_ECC_SYN_H_MASK | MESR_ECC_SYN_L_MASK);

	mear = __raw_पढ़ोl(pdata->vbase + REG_MEAR_OFFSET);

	/* Revert column/row addresses पूर्णांकo page frame number, etc */
	cpc925_mc_get_pfn(mci, mear, &pfn, &offset, &csrow);

	अगर (apiexcp & CECC_EXCP_DETECTED) अणु
		cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "DRAM CECC Fault\n");
		channel = cpc925_mc_find_channel(mci, syndrome);
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
				     pfn, offset, syndrome,
				     csrow, channel, -1,
				     mci->ctl_name, "");
	पूर्ण

	अगर (apiexcp & UECC_EXCP_DETECTED) अणु
		cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "DRAM UECC Fault\n");
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     pfn, offset, 0,
				     csrow, -1, -1,
				     mci->ctl_name, "");
	पूर्ण

	cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "Dump registers:\n");
	cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "APIMASK		0x%08x\n",
		__raw_पढ़ोl(pdata->vbase + REG_APIMASK_OFFSET));
	cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "APIEXCP		0x%08x\n",
		apiexcp);
	cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "Mem Scrub Ctrl	0x%08x\n",
		__raw_पढ़ोl(pdata->vbase + REG_MSCR_OFFSET));
	cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "Mem Scrub Rge Start	0x%08x\n",
		__raw_पढ़ोl(pdata->vbase + REG_MSRSR_OFFSET));
	cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "Mem Scrub Rge End	0x%08x\n",
		__raw_पढ़ोl(pdata->vbase + REG_MSRER_OFFSET));
	cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "Mem Scrub Pattern	0x%08x\n",
		__raw_पढ़ोl(pdata->vbase + REG_MSPR_OFFSET));
	cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "Mem Chk Ctrl		0x%08x\n",
		__raw_पढ़ोl(pdata->vbase + REG_MCCR_OFFSET));
	cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "Mem Chk Rge End	0x%08x\n",
		__raw_पढ़ोl(pdata->vbase + REG_MCRER_OFFSET));
	cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "Mem Err Address	0x%08x\n",
		mesr);
	cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "Mem Err Syndrome	0x%08x\n",
		syndrome);
पूर्ण

/******************** CPU err device********************************/
अटल u32 cpc925_cpu_mask_disabled(व्योम)
अणु
	काष्ठा device_node *cpunode;
	अटल u32 mask = 0;

	/* use cached value अगर available */
	अगर (mask != 0)
		वापस mask;

	mask = APIMASK_ADI0 | APIMASK_ADI1;

	क्रम_each_of_cpu_node(cpunode) अणु
		स्थिर u32 *reg = of_get_property(cpunode, "reg", शून्य);
		अगर (reg == शून्य || *reg > 2) अणु
			cpc925_prपूर्णांकk(KERN_ERR, "Bad reg value at %pOF\n", cpunode);
			जारी;
		पूर्ण

		mask &= ~APIMASK_ADI(*reg);
	पूर्ण

	अगर (mask != (APIMASK_ADI0 | APIMASK_ADI1)) अणु
		/* We assume that each CPU sits on it's own PI and that
		 * क्रम present CPUs the reg property equals to the PI
		 * पूर्णांकerface id */
		cpc925_prपूर्णांकk(KERN_WARNING,
				"Assuming PI id is equal to CPU MPIC id!\n");
	पूर्ण

	वापस mask;
पूर्ण

/* Enable CPU Errors detection */
अटल व्योम cpc925_cpu_init(काष्ठा cpc925_dev_info *dev_info)
अणु
	u32 apimask;
	u32 cpumask;

	apimask = __raw_पढ़ोl(dev_info->vbase + REG_APIMASK_OFFSET);

	cpumask = cpc925_cpu_mask_disabled();
	अगर (apimask & cpumask) अणु
		cpc925_prपूर्णांकk(KERN_WARNING, "CPU(s) not present, "
				"but enabled in APIMASK, disabling\n");
		apimask &= ~cpumask;
	पूर्ण

	अगर ((apimask & CPU_MASK_ENABLE) == 0)
		apimask |= CPU_MASK_ENABLE;

	__raw_ग_लिखोl(apimask, dev_info->vbase + REG_APIMASK_OFFSET);
पूर्ण

/* Disable CPU Errors detection */
अटल व्योम cpc925_cpu_निकास(काष्ठा cpc925_dev_info *dev_info)
अणु
	/*
	 * WARNING:
	 * We are supposed to clear the CPU error detection bits,
	 * and it will be no problem to करो so. However, once they
	 * are cleared here अगर we want to re-install CPC925 EDAC
	 * module later, setting them up in cpc925_cpu_init() will
	 * trigger machine check exception.
	 * Also, it's ok to leave CPU error detection bits enabled,
	 * since they are reset to 1 by शेष.
	 */

	वापस;
पूर्ण

/* Check क्रम CPU Errors */
अटल व्योम cpc925_cpu_check(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा cpc925_dev_info *dev_info = edac_dev->pvt_info;
	u32 apiexcp;
	u32 apimask;

	/* APIEXCP is cleared when पढ़ो */
	apiexcp = __raw_पढ़ोl(dev_info->vbase + REG_APIEXCP_OFFSET);
	अगर ((apiexcp & CPU_EXCP_DETECTED) == 0)
		वापस;

	अगर ((apiexcp & ~cpc925_cpu_mask_disabled()) == 0)
		वापस;

	apimask = __raw_पढ़ोl(dev_info->vbase + REG_APIMASK_OFFSET);
	cpc925_prपूर्णांकk(KERN_INFO, "Processor Interface Fault\n"
				 "Processor Interface register dump:\n");
	cpc925_prपूर्णांकk(KERN_INFO, "APIMASK		0x%08x\n", apimask);
	cpc925_prपूर्णांकk(KERN_INFO, "APIEXCP		0x%08x\n", apiexcp);

	edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
पूर्ण

/******************** HT Link err device****************************/
/* Enable HyperTransport Link Error detection */
अटल व्योम cpc925_htlink_init(काष्ठा cpc925_dev_info *dev_info)
अणु
	u32 ht_errctrl;

	ht_errctrl = __raw_पढ़ोl(dev_info->vbase + REG_ERRCTRL_OFFSET);
	अगर ((ht_errctrl & HT_ERRCTRL_ENABLE) == 0) अणु
		ht_errctrl |= HT_ERRCTRL_ENABLE;
		__raw_ग_लिखोl(ht_errctrl, dev_info->vbase + REG_ERRCTRL_OFFSET);
	पूर्ण
पूर्ण

/* Disable HyperTransport Link Error detection */
अटल व्योम cpc925_htlink_निकास(काष्ठा cpc925_dev_info *dev_info)
अणु
	u32 ht_errctrl;

	ht_errctrl = __raw_पढ़ोl(dev_info->vbase + REG_ERRCTRL_OFFSET);
	ht_errctrl &= ~HT_ERRCTRL_ENABLE;
	__raw_ग_लिखोl(ht_errctrl, dev_info->vbase + REG_ERRCTRL_OFFSET);
पूर्ण

/* Check क्रम HyperTransport Link errors */
अटल व्योम cpc925_htlink_check(काष्ठा edac_device_ctl_info *edac_dev)
अणु
	काष्ठा cpc925_dev_info *dev_info = edac_dev->pvt_info;
	u32 brgctrl = __raw_पढ़ोl(dev_info->vbase + REG_BRGCTRL_OFFSET);
	u32 linkctrl = __raw_पढ़ोl(dev_info->vbase + REG_LINKCTRL_OFFSET);
	u32 errctrl = __raw_पढ़ोl(dev_info->vbase + REG_ERRCTRL_OFFSET);
	u32 linkerr = __raw_पढ़ोl(dev_info->vbase + REG_LINKERR_OFFSET);

	अगर (!((brgctrl & BRGCTRL_DETSERR) ||
	      (linkctrl & HT_LINKCTRL_DETECTED) ||
	      (errctrl & HT_ERRCTRL_DETECTED) ||
	      (linkerr & HT_LINKERR_DETECTED)))
		वापस;

	cpc925_prपूर्णांकk(KERN_INFO, "HT Link Fault\n"
				 "HT register dump:\n");
	cpc925_prपूर्णांकk(KERN_INFO, "Bridge Ctrl			0x%08x\n",
		      brgctrl);
	cpc925_prपूर्णांकk(KERN_INFO, "Link Config Ctrl		0x%08x\n",
		      linkctrl);
	cpc925_prपूर्णांकk(KERN_INFO, "Error Enum and Ctrl		0x%08x\n",
		      errctrl);
	cpc925_prपूर्णांकk(KERN_INFO, "Link Error			0x%08x\n",
		      linkerr);

	/* Clear by ग_लिखो 1 */
	अगर (brgctrl & BRGCTRL_DETSERR)
		__raw_ग_लिखोl(BRGCTRL_DETSERR,
				dev_info->vbase + REG_BRGCTRL_OFFSET);

	अगर (linkctrl & HT_LINKCTRL_DETECTED)
		__raw_ग_लिखोl(HT_LINKCTRL_DETECTED,
				dev_info->vbase + REG_LINKCTRL_OFFSET);

	/* Initiate Secondary Bus Reset to clear the chain failure */
	अगर (errctrl & ERRCTRL_CHN_FAL)
		__raw_ग_लिखोl(BRGCTRL_SECBUSRESET,
				dev_info->vbase + REG_BRGCTRL_OFFSET);

	अगर (errctrl & ERRCTRL_RSP_ERR)
		__raw_ग_लिखोl(ERRCTRL_RSP_ERR,
				dev_info->vbase + REG_ERRCTRL_OFFSET);

	अगर (linkerr & HT_LINKERR_DETECTED)
		__raw_ग_लिखोl(HT_LINKERR_DETECTED,
				dev_info->vbase + REG_LINKERR_OFFSET);

	edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);
पूर्ण

अटल काष्ठा cpc925_dev_info cpc925_devs[] = अणु
	अणु
	.ctl_name = CPC925_CPU_ERR_DEV,
	.init = cpc925_cpu_init,
	.निकास = cpc925_cpu_निकास,
	.check = cpc925_cpu_check,
	पूर्ण,
	अणु
	.ctl_name = CPC925_HT_LINK_DEV,
	.init = cpc925_htlink_init,
	.निकास = cpc925_htlink_निकास,
	.check = cpc925_htlink_check,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * Add CPU Err detection and HyperTransport Link Err detection
 * as common "edac_device", they have no corresponding device
 * nodes in the Open Firmware DTB and we have to add platक्रमm
 * devices क्रम them. Also, they will share the MMIO with that
 * of memory controller.
 */
अटल व्योम cpc925_add_edac_devices(व्योम __iomem *vbase)
अणु
	काष्ठा cpc925_dev_info *dev_info;

	अगर (!vbase) अणु
		cpc925_prपूर्णांकk(KERN_ERR, "MMIO not established yet\n");
		वापस;
	पूर्ण

	क्रम (dev_info = &cpc925_devs[0]; dev_info->init; dev_info++) अणु
		dev_info->vbase = vbase;
		dev_info->pdev = platक्रमm_device_रेजिस्टर_simple(
					dev_info->ctl_name, 0, शून्य, 0);
		अगर (IS_ERR(dev_info->pdev)) अणु
			cpc925_prपूर्णांकk(KERN_ERR,
				"Can't register platform device for %s\n",
				dev_info->ctl_name);
			जारी;
		पूर्ण

		/*
		 * Don't have to allocate निजी काष्ठाure but
		 * make use of cpc925_devs[] instead.
		 */
		dev_info->edac_idx = edac_device_alloc_index();
		dev_info->edac_dev =
			edac_device_alloc_ctl_info(0, dev_info->ctl_name,
				1, शून्य, 0, 0, शून्य, 0, dev_info->edac_idx);
		अगर (!dev_info->edac_dev) अणु
			cpc925_prपूर्णांकk(KERN_ERR, "No memory for edac device\n");
			जाओ err1;
		पूर्ण

		dev_info->edac_dev->pvt_info = dev_info;
		dev_info->edac_dev->dev = &dev_info->pdev->dev;
		dev_info->edac_dev->ctl_name = dev_info->ctl_name;
		dev_info->edac_dev->mod_name = CPC925_EDAC_MOD_STR;
		dev_info->edac_dev->dev_name = dev_name(&dev_info->pdev->dev);

		अगर (edac_op_state == EDAC_OPSTATE_POLL)
			dev_info->edac_dev->edac_check = dev_info->check;

		अगर (dev_info->init)
			dev_info->init(dev_info);

		अगर (edac_device_add_device(dev_info->edac_dev) > 0) अणु
			cpc925_prपूर्णांकk(KERN_ERR,
				"Unable to add edac device for %s\n",
				dev_info->ctl_name);
			जाओ err2;
		पूर्ण

		edac_dbg(0, "Successfully added edac device for %s\n",
			 dev_info->ctl_name);

		जारी;

err2:
		अगर (dev_info->निकास)
			dev_info->निकास(dev_info);
		edac_device_मुक्त_ctl_info(dev_info->edac_dev);
err1:
		platक्रमm_device_unरेजिस्टर(dev_info->pdev);
	पूर्ण
पूर्ण

/*
 * Delete the common "edac_device" क्रम CPU Err Detection
 * and HyperTransport Link Err Detection
 */
अटल व्योम cpc925_del_edac_devices(व्योम)
अणु
	काष्ठा cpc925_dev_info *dev_info;

	क्रम (dev_info = &cpc925_devs[0]; dev_info->init; dev_info++) अणु
		अगर (dev_info->edac_dev) अणु
			edac_device_del_device(dev_info->edac_dev->dev);
			edac_device_मुक्त_ctl_info(dev_info->edac_dev);
			platक्रमm_device_unरेजिस्टर(dev_info->pdev);
		पूर्ण

		अगर (dev_info->निकास)
			dev_info->निकास(dev_info);

		edac_dbg(0, "Successfully deleted edac device for %s\n",
			 dev_info->ctl_name);
	पूर्ण
पूर्ण

/* Convert current back-ground scrub rate पूर्णांकo byte/sec bandwidth */
अटल पूर्णांक cpc925_get_sdram_scrub_rate(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा cpc925_mc_pdata *pdata = mci->pvt_info;
	पूर्णांक bw;
	u32 mscr;
	u8 si;

	mscr = __raw_पढ़ोl(pdata->vbase + REG_MSCR_OFFSET);
	si = (mscr & MSCR_SI_MASK) >> MSCR_SI_SHIFT;

	edac_dbg(0, "Mem Scrub Ctrl Register 0x%x\n", mscr);

	अगर (((mscr & MSCR_SCRUB_MOD_MASK) != MSCR_BACKGR_SCRUB) ||
	    (si == 0)) अणु
		cpc925_mc_prपूर्णांकk(mci, KERN_INFO, "Scrub mode not enabled\n");
		bw = 0;
	पूर्ण अन्यथा
		bw = CPC925_SCRUB_BLOCK_SIZE * 0xFA67 / si;

	वापस bw;
पूर्ण

/* Return 0 क्रम single channel; 1 क्रम dual channel */
अटल पूर्णांक cpc925_mc_get_channels(व्योम __iomem *vbase)
अणु
	पूर्णांक dual = 0;
	u32 mbcr;

	mbcr = __raw_पढ़ोl(vbase + REG_MBCR_OFFSET);

	/*
	 * Dual channel only when 128-bit wide physical bus
	 * and 128-bit configuration.
	 */
	अगर (((mbcr & MBCR_64BITCFG_MASK) == 0) &&
	    ((mbcr & MBCR_64BITBUS_MASK) == 0))
		dual = 1;

	edac_dbg(0, "%s channel\n", (dual > 0) ? "Dual" : "Single");

	वापस dual;
पूर्ण

अटल पूर्णांक cpc925_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अटल पूर्णांक edac_mc_idx;
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	व्योम __iomem *vbase;
	काष्ठा cpc925_mc_pdata *pdata;
	काष्ठा resource *r;
	पूर्णांक res = 0, nr_channels;

	edac_dbg(0, "%s platform device found!\n", pdev->name);

	अगर (!devres_खोलो_group(&pdev->dev, cpc925_probe, GFP_KERNEL)) अणु
		res = -ENOMEM;
		जाओ out;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		cpc925_prपूर्णांकk(KERN_ERR, "Unable to get resource\n");
		res = -ENOENT;
		जाओ err1;
	पूर्ण

	अगर (!devm_request_mem_region(&pdev->dev,
				     r->start,
				     resource_size(r),
				     pdev->name)) अणु
		cpc925_prपूर्णांकk(KERN_ERR, "Unable to request mem region\n");
		res = -EBUSY;
		जाओ err1;
	पूर्ण

	vbase = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (!vbase) अणु
		cpc925_prपूर्णांकk(KERN_ERR, "Unable to ioremap device\n");
		res = -ENOMEM;
		जाओ err2;
	पूर्ण

	nr_channels = cpc925_mc_get_channels(vbase) + 1;

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = CPC925_NR_CSROWS;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = nr_channels;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(edac_mc_idx, ARRAY_SIZE(layers), layers,
			    माप(काष्ठा cpc925_mc_pdata));
	अगर (!mci) अणु
		cpc925_prपूर्णांकk(KERN_ERR, "No memory for mem_ctl_info\n");
		res = -ENOMEM;
		जाओ err2;
	पूर्ण

	pdata = mci->pvt_info;
	pdata->vbase = vbase;
	pdata->edac_idx = edac_mc_idx++;
	pdata->name = pdev->name;

	mci->pdev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, mci);
	mci->dev_name = dev_name(&pdev->dev);
	mci->mtype_cap = MEM_FLAG_RDDR | MEM_FLAG_DDR;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->mod_name = CPC925_EDAC_MOD_STR;
	mci->ctl_name = pdev->name;

	अगर (edac_op_state == EDAC_OPSTATE_POLL)
		mci->edac_check = cpc925_mc_check;

	mci->ctl_page_to_phys = शून्य;
	mci->scrub_mode = SCRUB_SW_SRC;
	mci->set_sdram_scrub_rate = शून्य;
	mci->get_sdram_scrub_rate = cpc925_get_sdram_scrub_rate;

	cpc925_init_csrows(mci);

	/* Setup memory controller रेजिस्टरs */
	cpc925_mc_init(mci);

	अगर (edac_mc_add_mc(mci) > 0) अणु
		cpc925_mc_prपूर्णांकk(mci, KERN_ERR, "Failed edac_mc_add_mc()\n");
		जाओ err3;
	पूर्ण

	cpc925_add_edac_devices(vbase);

	/* get this far and it's successful */
	edac_dbg(0, "success\n");

	res = 0;
	जाओ out;

err3:
	cpc925_mc_निकास(mci);
	edac_mc_मुक्त(mci);
err2:
	devm_release_mem_region(&pdev->dev, r->start, resource_size(r));
err1:
	devres_release_group(&pdev->dev, cpc925_probe);
out:
	वापस res;
पूर्ण

अटल पूर्णांक cpc925_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mem_ctl_info *mci = platक्रमm_get_drvdata(pdev);

	/*
	 * Delete common edac devices beक्रमe edac mc, because
	 * the क्रमmer share the MMIO of the latter.
	 */
	cpc925_del_edac_devices();
	cpc925_mc_निकास(mci);

	edac_mc_del_mc(&pdev->dev);
	edac_mc_मुक्त(mci);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cpc925_edac_driver = अणु
	.probe = cpc925_probe,
	.हटाओ = cpc925_हटाओ,
	.driver = अणु
		   .name = "cpc925_edac",
	पूर्ण
पूर्ण;

अटल पूर्णांक __init cpc925_edac_init(व्योम)
अणु
	पूर्णांक ret = 0;

	prपूर्णांकk(KERN_INFO "IBM CPC925 EDAC driver " CPC925_EDAC_REVISION "\n");
	prपूर्णांकk(KERN_INFO "\t(c) 2008 Wind River Systems, Inc\n");

	/* Only support POLL mode so far */
	edac_op_state = EDAC_OPSTATE_POLL;

	ret = platक्रमm_driver_रेजिस्टर(&cpc925_edac_driver);
	अगर (ret) अणु
		prपूर्णांकk(KERN_WARNING "Failed to register %s\n",
			CPC925_EDAC_MOD_STR);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास cpc925_edac_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&cpc925_edac_driver);
पूर्ण

module_init(cpc925_edac_init);
module_निकास(cpc925_edac_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cao Qingtao <qingtao.cao@windriver.com>");
MODULE_DESCRIPTION("IBM CPC925 Bridge and MC EDAC kernel module");
