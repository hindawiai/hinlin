<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell न_अंकD flash controller driver
 *
 * Copyright (C) 2017 Marvell
 * Author: Miquel RAYNAL <miquel.raynal@मुक्त-electrons.com>
 *
 *
 * This न_अंकD controller driver handles two versions of the hardware,
 * one is called NFCv1 and is available on PXA SoCs and the other is
 * called NFCv2 and is available on Armada SoCs.
 *
 * The मुख्य visible dअगरference is that NFCv1 only has Hamming ECC
 * capabilities, जबतक NFCv2 also embeds a BCH ECC engine. Also, DMA
 * is not used with NFCv2.
 *
 * The ECC layouts are depicted in details in Marvell AN-379, but here
 * is a brief description.
 *
 * When using Hamming, the data is split in 512B chunks (either 1, 2
 * or 4) and each chunk will have its own ECC "digest" of 6B at the
 * beginning of the OOB area and eventually the reमुख्यing मुक्त OOB
 * bytes (also called "spare" bytes in the driver). This engine
 * corrects up to 1 bit per chunk and detects reliably an error अगर
 * there are at most 2 bitflips. Here is the page layout used by the
 * controller when Hamming is chosen:
 *
 * +-------------------------------------------------------------+
 * | Data 1 | ... | Data N | ECC 1 | ... | ECCN | Free OOB bytes |
 * +-------------------------------------------------------------+
 *
 * When using the BCH engine, there are N identical (data + मुक्त OOB +
 * ECC) sections and potentially an extra one to deal with
 * configurations where the chosen (data + मुक्त OOB + ECC) sizes करो
 * not align with the page (data + OOB) size. ECC bytes are always
 * 30B per ECC chunk. Here is the page layout used by the controller
 * when BCH is chosen:
 *
 * +-----------------------------------------
 * | Data 1 | Free OOB bytes 1 | ECC 1 | ...
 * +-----------------------------------------
 *
 *      -------------------------------------------
 *       ... | Data N | Free OOB bytes N | ECC N |
 *      -------------------------------------------
 *
 *           --------------------------------------------+
 *            Last Data | Last Free OOB bytes | Last ECC |
 *           --------------------------------------------+
 *
 * In both हालs, the layout seen by the user is always: all data
 * first, then all मुक्त OOB bytes and finally all ECC bytes. With BCH,
 * ECC bytes are 30B दीर्घ and are padded with 0xFF to align on 32
 * bytes.
 *
 * The controller has certain limitations that are handled by the
 * driver:
 *   - It can only पढ़ो 2k at a समय. To overcome this limitation, the
 *     driver issues data cycles on the bus, without issuing new
 *     CMD + ADDR cycles. The Marvell term is "naked" operations.
 *   - The ECC strength in BCH mode cannot be tuned. It is fixed 16
 *     bits. What can be tuned is the ECC block size as दीर्घ as it
 *     stays between 512B and 2kiB. It's usually chosen based on the
 *     chip ECC requirements. For instance, using 2kiB ECC chunks
 *     provides 4b/512B correctability.
 *   - The controller will always treat data bytes, मुक्त OOB bytes
 *     and ECC bytes in that order, no matter what the real layout is
 *     (which is usually all data then all OOB bytes). The
 *     marvell_nfc_layouts array below contains the currently
 *     supported layouts.
 *   - Because of these weird layouts, the Bad Block Markers can be
 *     located in data section. In this हाल, the न_अंकD_BBT_NO_OOB_BBM
 *     option must be set to prevent scanning/writing bad block
 *     markers.
 */

#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dma/pxa-dma.h>
#समावेश <linux/platक्रमm_data/mtd-nand-pxa3xx.h>

/* Data FIFO granularity, FIFO पढ़ोs/ग_लिखोs must be a multiple of this length */
#घोषणा FIFO_DEPTH		8
#घोषणा FIFO_REP(x)		(x / माप(u32))
#घोषणा BCH_SEQ_READS		(32 / FIFO_DEPTH)
/* NFC करोes not support transfers of larger chunks at a समय */
#घोषणा MAX_CHUNK_SIZE		2112
/* NFCv1 cannot पढ़ो more that 7 bytes of ID */
#घोषणा NFCV1_READID_LEN	7
/* Polling is करोne at a pace of POLL_PERIOD us until POLL_TIMEOUT is reached */
#घोषणा POLL_PERIOD		0
#घोषणा POLL_TIMEOUT		100000
/* Interrupt maximum रुको period in ms */
#घोषणा IRQ_TIMEOUT		1000
/* Latency in घड़ी cycles between SoC pins and NFC logic */
#घोषणा MIN_RD_DEL_CNT		3
/* Maximum number of contiguous address cycles */
#घोषणा MAX_ADDRESS_CYC_NFCV1	5
#घोषणा MAX_ADDRESS_CYC_NFCV2	7
/* System control रेजिस्टरs/bits to enable the न_अंकD controller on some SoCs */
#घोषणा GENCONF_SOC_DEVICE_MUX	0x208
#घोषणा GENCONF_SOC_DEVICE_MUX_NFC_EN BIT(0)
#घोषणा GENCONF_SOC_DEVICE_MUX_ECC_CLK_RST BIT(20)
#घोषणा GENCONF_SOC_DEVICE_MUX_ECC_CORE_RST BIT(21)
#घोषणा GENCONF_SOC_DEVICE_MUX_NFC_INT_EN BIT(25)
#घोषणा GENCONF_CLK_GATING_CTRL	0x220
#घोषणा GENCONF_CLK_GATING_CTRL_ND_GATE BIT(2)
#घोषणा GENCONF_ND_CLK_CTRL	0x700
#घोषणा GENCONF_ND_CLK_CTRL_EN	BIT(0)

/* न_अंकD controller data flash control रेजिस्टर */
#घोषणा NDCR			0x00
#घोषणा NDCR_ALL_INT		GENMASK(11, 0)
#घोषणा NDCR_CS1_CMDDM		BIT(7)
#घोषणा NDCR_CS0_CMDDM		BIT(8)
#घोषणा NDCR_RDYM		BIT(11)
#घोषणा NDCR_ND_ARB_EN		BIT(12)
#घोषणा NDCR_RA_START		BIT(15)
#घोषणा NDCR_RD_ID_CNT(x)	(min_t(अचिन्हित पूर्णांक, x, 0x7) << 16)
#घोषणा NDCR_PAGE_SZ(x)		(x >= 2048 ? BIT(24) : 0)
#घोषणा NDCR_DWIDTH_M		BIT(26)
#घोषणा NDCR_DWIDTH_C		BIT(27)
#घोषणा NDCR_ND_RUN		BIT(28)
#घोषणा NDCR_DMA_EN		BIT(29)
#घोषणा NDCR_ECC_EN		BIT(30)
#घोषणा NDCR_SPARE_EN		BIT(31)
#घोषणा NDCR_GENERIC_FIELDS_MASK (~(NDCR_RA_START | NDCR_PAGE_SZ(2048) | \
				    NDCR_DWIDTH_M | NDCR_DWIDTH_C))

/* न_अंकD पूर्णांकerface timing parameter 0 रेजिस्टर */
#घोषणा NDTR0			0x04
#घोषणा NDTR0_TRP(x)		((min_t(अचिन्हित पूर्णांक, x, 0xF) & 0x7) << 0)
#घोषणा NDTR0_TRH(x)		(min_t(अचिन्हित पूर्णांक, x, 0x7) << 3)
#घोषणा NDTR0_ETRP(x)		((min_t(अचिन्हित पूर्णांक, x, 0xF) & 0x8) << 3)
#घोषणा NDTR0_SEL_NRE_EDGE	BIT(7)
#घोषणा NDTR0_TWP(x)		(min_t(अचिन्हित पूर्णांक, x, 0x7) << 8)
#घोषणा NDTR0_TWH(x)		(min_t(अचिन्हित पूर्णांक, x, 0x7) << 11)
#घोषणा NDTR0_TCS(x)		(min_t(अचिन्हित पूर्णांक, x, 0x7) << 16)
#घोषणा NDTR0_TCH(x)		(min_t(अचिन्हित पूर्णांक, x, 0x7) << 19)
#घोषणा NDTR0_RD_CNT_DEL(x)	(min_t(अचिन्हित पूर्णांक, x, 0xF) << 22)
#घोषणा NDTR0_SELCNTR		BIT(26)
#घोषणा NDTR0_TADL(x)		(min_t(अचिन्हित पूर्णांक, x, 0x1F) << 27)

/* न_अंकD पूर्णांकerface timing parameter 1 रेजिस्टर */
#घोषणा NDTR1			0x0C
#घोषणा NDTR1_TAR(x)		(min_t(अचिन्हित पूर्णांक, x, 0xF) << 0)
#घोषणा NDTR1_TWHR(x)		(min_t(अचिन्हित पूर्णांक, x, 0xF) << 4)
#घोषणा NDTR1_TRHW(x)		(min_t(अचिन्हित पूर्णांक, x / 16, 0x3) << 8)
#घोषणा NDTR1_PRESCALE		BIT(14)
#घोषणा NDTR1_WAIT_MODE		BIT(15)
#घोषणा NDTR1_TR(x)		(min_t(अचिन्हित पूर्णांक, x, 0xFFFF) << 16)

/* न_अंकD controller status रेजिस्टर */
#घोषणा NDSR			0x14
#घोषणा NDSR_WRCMDREQ		BIT(0)
#घोषणा NDSR_RDDREQ		BIT(1)
#घोषणा NDSR_WRDREQ		BIT(2)
#घोषणा NDSR_CORERR		BIT(3)
#घोषणा NDSR_UNCERR		BIT(4)
#घोषणा NDSR_CMDD(cs)		BIT(8 - cs)
#घोषणा NDSR_RDY(rb)		BIT(11 + rb)
#घोषणा NDSR_ERRCNT(x)		((x >> 16) & 0x1F)

/* न_अंकD ECC control रेजिस्टर */
#घोषणा NDECCCTRL		0x28
#घोषणा NDECCCTRL_BCH_EN	BIT(0)

/* न_अंकD controller data buffer रेजिस्टर */
#घोषणा NDDB			0x40

/* न_अंकD controller command buffer 0 रेजिस्टर */
#घोषणा NDCB0			0x48
#घोषणा NDCB0_CMD1(x)		((x & 0xFF) << 0)
#घोषणा NDCB0_CMD2(x)		((x & 0xFF) << 8)
#घोषणा NDCB0_ADDR_CYC(x)	((x & 0x7) << 16)
#घोषणा NDCB0_ADDR_GET_NUM_CYC(x) (((x) >> 16) & 0x7)
#घोषणा NDCB0_DBC		BIT(19)
#घोषणा NDCB0_CMD_TYPE(x)	((x & 0x7) << 21)
#घोषणा NDCB0_CSEL		BIT(24)
#घोषणा NDCB0_RDY_BYP		BIT(27)
#घोषणा NDCB0_LEN_OVRD		BIT(28)
#घोषणा NDCB0_CMD_XTYPE(x)	((x & 0x7) << 29)

/* न_अंकD controller command buffer 1 रेजिस्टर */
#घोषणा NDCB1			0x4C
#घोषणा NDCB1_COLS(x)		((x & 0xFFFF) << 0)
#घोषणा NDCB1_ADDRS_PAGE(x)	(x << 16)

/* न_अंकD controller command buffer 2 रेजिस्टर */
#घोषणा NDCB2			0x50
#घोषणा NDCB2_ADDR5_PAGE(x)	(((x >> 16) & 0xFF) << 0)
#घोषणा NDCB2_ADDR5_CYC(x)	((x & 0xFF) << 0)

/* न_अंकD controller command buffer 3 रेजिस्टर */
#घोषणा NDCB3			0x54
#घोषणा NDCB3_ADDR6_CYC(x)	((x & 0xFF) << 16)
#घोषणा NDCB3_ADDR7_CYC(x)	((x & 0xFF) << 24)

/* न_अंकD controller command buffer 0 रेजिस्टर 'type' and 'xtype' fields */
#घोषणा TYPE_READ		0
#घोषणा TYPE_WRITE		1
#घोषणा TYPE_ERASE		2
#घोषणा TYPE_READ_ID		3
#घोषणा TYPE_STATUS		4
#घोषणा TYPE_RESET		5
#घोषणा TYPE_NAKED_CMD		6
#घोषणा TYPE_NAKED_ADDR		7
#घोषणा TYPE_MASK		7
#घोषणा XTYPE_MONOLITHIC_RW	0
#घोषणा XTYPE_LAST_NAKED_RW	1
#घोषणा XTYPE_FINAL_COMMAND	3
#घोषणा XTYPE_READ		4
#घोषणा XTYPE_WRITE_DISPATCH	4
#घोषणा XTYPE_NAKED_RW		5
#घोषणा XTYPE_COMMAND_DISPATCH	6
#घोषणा XTYPE_MASK		7

/**
 * काष्ठा marvell_hw_ecc_layout - layout of Marvell ECC
 *
 * Marvell ECC engine works dअगरferently than the others, in order to limit the
 * size of the IP, hardware engineers chose to set a fixed strength at 16 bits
 * per subpage, and depending on a the desired strength needed by the न_अंकD chip,
 * a particular layout mixing data/spare/ecc is defined, with a possible last
 * chunk smaller that the others.
 *
 * @ग_लिखोsize:		Full page size on which the layout applies
 * @chunk:		Desired ECC chunk size on which the layout applies
 * @strength:		Desired ECC strength (per chunk size bytes) on which the
 *			layout applies
 * @nchunks:		Total number of chunks
 * @full_chunk_cnt:	Number of full-sized chunks, which is the number of
 *			repetitions of the pattern:
 *			(data_bytes + spare_bytes + ecc_bytes).
 * @data_bytes:		Number of data bytes per chunk
 * @spare_bytes:	Number of spare bytes per chunk
 * @ecc_bytes:		Number of ecc bytes per chunk
 * @last_data_bytes:	Number of data bytes in the last chunk
 * @last_spare_bytes:	Number of spare bytes in the last chunk
 * @last_ecc_bytes:	Number of ecc bytes in the last chunk
 */
काष्ठा marvell_hw_ecc_layout अणु
	/* Constraपूर्णांकs */
	पूर्णांक ग_लिखोsize;
	पूर्णांक chunk;
	पूर्णांक strength;
	/* Corresponding layout */
	पूर्णांक nchunks;
	पूर्णांक full_chunk_cnt;
	पूर्णांक data_bytes;
	पूर्णांक spare_bytes;
	पूर्णांक ecc_bytes;
	पूर्णांक last_data_bytes;
	पूर्णांक last_spare_bytes;
	पूर्णांक last_ecc_bytes;
पूर्ण;

#घोषणा MARVELL_LAYOUT(ws, dc, ds, nc, fcc, db, sb, eb, ldb, lsb, leb)	\
	अणु								\
		.ग_लिखोsize = ws,					\
		.chunk = dc,						\
		.strength = ds,						\
		.nchunks = nc,						\
		.full_chunk_cnt = fcc,					\
		.data_bytes = db,					\
		.spare_bytes = sb,					\
		.ecc_bytes = eb,					\
		.last_data_bytes = ldb,					\
		.last_spare_bytes = lsb,				\
		.last_ecc_bytes = leb,					\
	पूर्ण

/* Layouts explained in AN-379_Marvell_SoC_NFC_ECC */
अटल स्थिर काष्ठा marvell_hw_ecc_layout marvell_nfc_layouts[] = अणु
	MARVELL_LAYOUT(  512,   512,  1,  1,  1,  512,  8,  8,  0,  0,  0),
	MARVELL_LAYOUT( 2048,   512,  1,  1,  1, 2048, 40, 24,  0,  0,  0),
	MARVELL_LAYOUT( 2048,   512,  4,  1,  1, 2048, 32, 30,  0,  0,  0),
	MARVELL_LAYOUT( 2048,   512,  8,  2,  1, 1024,  0, 30,1024,32, 30),
	MARVELL_LAYOUT( 4096,   512,  4,  2,  2, 2048, 32, 30,  0,  0,  0),
	MARVELL_LAYOUT( 4096,   512,  8,  5,  4, 1024,  0, 30,  0, 64, 30),
	MARVELL_LAYOUT( 8192,   512,  4,  4,  4, 2048,  0, 30,  0,  0,  0),
	MARVELL_LAYOUT( 8192,   512,  8,  9,  8, 1024,  0, 30,  0, 160, 30),
पूर्ण;

/**
 * काष्ठा marvell_nand_chip_sel - CS line description
 *
 * The Nand Flash Controller has up to 4 CE and 2 RB pins. The CE selection
 * is made by a field in NDCB0 रेजिस्टर, and in another field in NDCB2 रेजिस्टर.
 * The datasheet describes the logic with an error: ADDR5 field is once
 * declared at the beginning of NDCB2, and another समय at its end. Because the
 * ADDR5 field of NDCB2 may be used by other bytes, it would be more logical
 * to use the last bit of this field instead of the first ones.
 *
 * @cs:			Wanted CE lane.
 * @ndcb0_csel:		Value of the NDCB0 रेजिस्टर with or without the flag
 *			selecting the wanted CE lane. This is set once when
 *			the Device Tree is probed.
 * @rb:			Ready/Busy pin क्रम the flash chip
 */
काष्ठा marvell_nand_chip_sel अणु
	अचिन्हित पूर्णांक cs;
	u32 ndcb0_csel;
	अचिन्हित पूर्णांक rb;
पूर्ण;

/**
 * काष्ठा marvell_nand_chip - stores न_अंकD chip device related inक्रमmation
 *
 * @chip:		Base न_अंकD chip काष्ठाure
 * @node:		Used to store न_अंकD chips पूर्णांकo a list
 * @layout:		न_अंकD layout when using hardware ECC
 * @ndcr:		Controller रेजिस्टर value क्रम this न_अंकD chip
 * @ndtr0:		Timing रेजिस्टरs 0 value क्रम this न_अंकD chip
 * @ndtr1:		Timing रेजिस्टरs 1 value क्रम this न_अंकD chip
 * @addr_cyc:		Amount of cycles needed to pass column address
 * @selected_die:	Current active CS
 * @nsels:		Number of CS lines required by the न_अंकD chip
 * @sels:		Array of CS lines descriptions
 */
काष्ठा marvell_nand_chip अणु
	काष्ठा nand_chip chip;
	काष्ठा list_head node;
	स्थिर काष्ठा marvell_hw_ecc_layout *layout;
	u32 ndcr;
	u32 ndtr0;
	u32 ndtr1;
	पूर्णांक addr_cyc;
	पूर्णांक selected_die;
	अचिन्हित पूर्णांक nsels;
	काष्ठा marvell_nand_chip_sel sels[];
पूर्ण;

अटल अंतरभूत काष्ठा marvell_nand_chip *to_marvell_nand(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip, काष्ठा marvell_nand_chip, chip);
पूर्ण

अटल अंतरभूत काष्ठा marvell_nand_chip_sel *to_nand_sel(काष्ठा marvell_nand_chip
							*nand)
अणु
	वापस &nand->sels[nand->selected_die];
पूर्ण

/**
 * काष्ठा marvell_nfc_caps - न_अंकD controller capabilities क्रम distinction
 *                           between compatible strings
 *
 * @max_cs_nb:		Number of Chip Select lines available
 * @max_rb_nb:		Number of Ready/Busy lines available
 * @need_प्रणाली_controller: Indicates अगर the SoC needs to have access to the
 *                      प्रणाली controller (ie. to enable the न_अंकD controller)
 * @legacy_of_bindings:	Indicates अगर DT parsing must be करोne using the old
 *			fashion way
 * @is_nfcv2:		NFCv2 has numerous enhancements compared to NFCv1, ie.
 *			BCH error detection and correction algorithm,
 *			NDCB3 रेजिस्टर has been added
 * @use_dma:		Use dma क्रम data transfers
 */
काष्ठा marvell_nfc_caps अणु
	अचिन्हित पूर्णांक max_cs_nb;
	अचिन्हित पूर्णांक max_rb_nb;
	bool need_प्रणाली_controller;
	bool legacy_of_bindings;
	bool is_nfcv2;
	bool use_dma;
पूर्ण;

/**
 * काष्ठा marvell_nfc - stores Marvell न_अंकD controller inक्रमmation
 *
 * @controller:		Base controller काष्ठाure
 * @dev:		Parent device (used to prपूर्णांक error messages)
 * @regs:		न_अंकD controller रेजिस्टरs
 * @core_clk:		Core घड़ी
 * @reg_clk:		Registers घड़ी
 * @complete:		Completion object to रुको क्रम न_अंकD controller events
 * @asचिन्हित_cs:	Biपंचांगask describing alपढ़ोy asचिन्हित CS lines
 * @chips:		List containing all the न_अंकD chips attached to
 *			this न_अंकD controller
 * @selected_chip:	Currently selected target chip
 * @caps:		न_अंकD controller capabilities क्रम each compatible string
 * @use_dma:		Whetner DMA is used
 * @dma_chan:		DMA channel (NFCv1 only)
 * @dma_buf:		32-bit aligned buffer क्रम DMA transfers (NFCv1 only)
 */
काष्ठा marvell_nfc अणु
	काष्ठा nand_controller controller;
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा clk *core_clk;
	काष्ठा clk *reg_clk;
	काष्ठा completion complete;
	अचिन्हित दीर्घ asचिन्हित_cs;
	काष्ठा list_head chips;
	काष्ठा nand_chip *selected_chip;
	स्थिर काष्ठा marvell_nfc_caps *caps;

	/* DMA (NFCv1 only) */
	bool use_dma;
	काष्ठा dma_chan *dma_chan;
	u8 *dma_buf;
पूर्ण;

अटल अंतरभूत काष्ठा marvell_nfc *to_marvell_nfc(काष्ठा nand_controller *ctrl)
अणु
	वापस container_of(ctrl, काष्ठा marvell_nfc, controller);
पूर्ण

/**
 * काष्ठा marvell_nfc_timings - न_अंकD controller timings expressed in न_अंकD
 *                              Controller घड़ी cycles
 *
 * @tRP:		ND_nRE pulse width
 * @tRH:		ND_nRE high duration
 * @tWP:		ND_nWE pulse समय
 * @tWH:		ND_nWE high duration
 * @tCS:		Enable संकेत setup समय
 * @tCH:		Enable संकेत hold समय
 * @tADL:		Address to ग_लिखो data delay
 * @tAR:		ND_ALE low to ND_nRE low delay
 * @tWHR:		ND_nWE high to ND_nRE low क्रम status पढ़ो
 * @tRHW:		ND_nRE high duration, पढ़ो to ग_लिखो delay
 * @tR:			ND_nWE high to ND_nRE low क्रम पढ़ो
 */
काष्ठा marvell_nfc_timings अणु
	/* NDTR0 fields */
	अचिन्हित पूर्णांक tRP;
	अचिन्हित पूर्णांक tRH;
	अचिन्हित पूर्णांक tWP;
	अचिन्हित पूर्णांक tWH;
	अचिन्हित पूर्णांक tCS;
	अचिन्हित पूर्णांक tCH;
	अचिन्हित पूर्णांक tADL;
	/* NDTR1 fields */
	अचिन्हित पूर्णांक tAR;
	अचिन्हित पूर्णांक tWHR;
	अचिन्हित पूर्णांक tRHW;
	अचिन्हित पूर्णांक tR;
पूर्ण;

/**
 * Derives a duration in numbers of घड़ी cycles.
 *
 * @ps: Duration in pico-seconds
 * @period_ns:  Clock period in nano-seconds
 *
 * Convert the duration in nano-seconds, then भागide by the period and
 * वापस the number of घड़ी periods.
 */
#घोषणा TO_CYCLES(ps, period_ns) (DIV_ROUND_UP(ps / 1000, period_ns))
#घोषणा TO_CYCLES64(ps, period_ns) (DIV_ROUND_UP_ULL(भाग_u64(ps, 1000), \
						     period_ns))

/**
 * काष्ठा marvell_nfc_op - filled during the parsing of the ->exec_op()
 *                         subop subset of inकाष्ठाions.
 *
 * @ndcb:		Array of values written to NDCBx रेजिस्टरs
 * @cle_ale_delay_ns:	Optional delay after the last CMD or ADDR cycle
 * @rdy_समयout_ms:	Timeout क्रम रुकोs on Ready/Busy pin
 * @rdy_delay_ns:	Optional delay after रुकोing क्रम the RB pin
 * @data_delay_ns:	Optional delay after the data xfer
 * @data_instr_idx:	Index of the data inकाष्ठाion in the subop
 * @data_instr:		Poपूर्णांकer to the data inकाष्ठाion in the subop
 */
काष्ठा marvell_nfc_op अणु
	u32 ndcb[4];
	अचिन्हित पूर्णांक cle_ale_delay_ns;
	अचिन्हित पूर्णांक rdy_समयout_ms;
	अचिन्हित पूर्णांक rdy_delay_ns;
	अचिन्हित पूर्णांक data_delay_ns;
	अचिन्हित पूर्णांक data_instr_idx;
	स्थिर काष्ठा nand_op_instr *data_instr;
पूर्ण;

/*
 * Internal helper to conditionnally apply a delay (from the above काष्ठाure,
 * most of the समय).
 */
अटल व्योम cond_delay(अचिन्हित पूर्णांक ns)
अणु
	अगर (!ns)
		वापस;

	अगर (ns < 10000)
		ndelay(ns);
	अन्यथा
		udelay(DIV_ROUND_UP(ns, 1000));
पूर्ण

/*
 * The controller has many flags that could generate पूर्णांकerrupts, most of them
 * are disabled and polling is used. For the very slow संकेतs, using पूर्णांकerrupts
 * may relax the CPU अक्षरge.
 */
अटल व्योम marvell_nfc_disable_पूर्णांक(काष्ठा marvell_nfc *nfc, u32 पूर्णांक_mask)
अणु
	u32 reg;

	/* Writing 1 disables the पूर्णांकerrupt */
	reg = पढ़ोl_relaxed(nfc->regs + NDCR);
	ग_लिखोl_relaxed(reg | पूर्णांक_mask, nfc->regs + NDCR);
पूर्ण

अटल व्योम marvell_nfc_enable_पूर्णांक(काष्ठा marvell_nfc *nfc, u32 पूर्णांक_mask)
अणु
	u32 reg;

	/* Writing 0 enables the पूर्णांकerrupt */
	reg = पढ़ोl_relaxed(nfc->regs + NDCR);
	ग_लिखोl_relaxed(reg & ~पूर्णांक_mask, nfc->regs + NDCR);
पूर्ण

अटल u32 marvell_nfc_clear_पूर्णांक(काष्ठा marvell_nfc *nfc, u32 पूर्णांक_mask)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(nfc->regs + NDSR);
	ग_लिखोl_relaxed(पूर्णांक_mask, nfc->regs + NDSR);

	वापस reg & पूर्णांक_mask;
पूर्ण

अटल व्योम marvell_nfc_क्रमce_byte_access(काष्ठा nand_chip *chip,
					  bool क्रमce_8bit)
अणु
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 ndcr;

	/*
	 * Callers of this function करो not verअगरy अगर the न_अंकD is using a 16-bit
	 * an 8-bit bus क्रम normal operations, so we need to take care of that
	 * here by leaving the configuration unchanged अगर the न_अंकD करोes not have
	 * the न_अंकD_BUSWIDTH_16 flag set.
	 */
	अगर (!(chip->options & न_अंकD_BUSWIDTH_16))
		वापस;

	ndcr = पढ़ोl_relaxed(nfc->regs + NDCR);

	अगर (क्रमce_8bit)
		ndcr &= ~(NDCR_DWIDTH_M | NDCR_DWIDTH_C);
	अन्यथा
		ndcr |= NDCR_DWIDTH_M | NDCR_DWIDTH_C;

	ग_लिखोl_relaxed(ndcr, nfc->regs + NDCR);
पूर्ण

अटल पूर्णांक marvell_nfc_रुको_ndrun(काष्ठा nand_chip *chip)
अणु
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 val;
	पूर्णांक ret;

	/*
	 * The command is being processed, रुको क्रम the ND_RUN bit to be
	 * cleared by the NFC. If not, we must clear it by hand.
	 */
	ret = पढ़ोl_relaxed_poll_समयout(nfc->regs + NDCR, val,
					 (val & NDCR_ND_RUN) == 0,
					 POLL_PERIOD, POLL_TIMEOUT);
	अगर (ret) अणु
		dev_err(nfc->dev, "Timeout on NAND controller run mode\n");
		ग_लिखोl_relaxed(पढ़ोl(nfc->regs + NDCR) & ~NDCR_ND_RUN,
			       nfc->regs + NDCR);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Any समय a command has to be sent to the controller, the following sequence
 * has to be followed:
 * - call marvell_nfc_prepare_cmd()
 *      -> activate the ND_RUN bit that will kind of 'start a job'
 *      -> रुको the संकेत indicating the NFC is रुकोing क्रम a command
 * - send the command (cmd and address cycles)
 * - enventually send or receive the data
 * - call marvell_nfc_end_cmd() with the corresponding flag
 *      -> रुको the flag to be triggered or cancel the job with a समयout
 *
 * The following helpers are here to factorize the code a bit so that
 * specialized functions responsible क्रम executing the actual न_अंकD
 * operations करो not have to replicate the same code blocks.
 */
अटल पूर्णांक marvell_nfc_prepare_cmd(काष्ठा nand_chip *chip)
अणु
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 ndcr, val;
	पूर्णांक ret;

	/* Poll ND_RUN and clear NDSR beक्रमe issuing any command */
	ret = marvell_nfc_रुको_ndrun(chip);
	अगर (ret) अणु
		dev_err(nfc->dev, "Last operation did not succeed\n");
		वापस ret;
	पूर्ण

	ndcr = पढ़ोl_relaxed(nfc->regs + NDCR);
	ग_लिखोl_relaxed(पढ़ोl(nfc->regs + NDSR), nfc->regs + NDSR);

	/* Assert ND_RUN bit and रुको the NFC to be पढ़ोy */
	ग_लिखोl_relaxed(ndcr | NDCR_ND_RUN, nfc->regs + NDCR);
	ret = पढ़ोl_relaxed_poll_समयout(nfc->regs + NDSR, val,
					 val & NDSR_WRCMDREQ,
					 POLL_PERIOD, POLL_TIMEOUT);
	अगर (ret) अणु
		dev_err(nfc->dev, "Timeout on WRCMDRE\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* Command may be written, clear WRCMDREQ status bit */
	ग_लिखोl_relaxed(NDSR_WRCMDREQ, nfc->regs + NDSR);

	वापस 0;
पूर्ण

अटल व्योम marvell_nfc_send_cmd(काष्ठा nand_chip *chip,
				 काष्ठा marvell_nfc_op *nfc_op)
अणु
	काष्ठा marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);

	dev_dbg(nfc->dev, "\nNDCR:  0x%08x\n"
		"NDCB0: 0x%08x\nNDCB1: 0x%08x\nNDCB2: 0x%08x\nNDCB3: 0x%08x\n",
		(u32)पढ़ोl_relaxed(nfc->regs + NDCR), nfc_op->ndcb[0],
		nfc_op->ndcb[1], nfc_op->ndcb[2], nfc_op->ndcb[3]);

	ग_लिखोl_relaxed(to_nand_sel(marvell_nand)->ndcb0_csel | nfc_op->ndcb[0],
		       nfc->regs + NDCB0);
	ग_लिखोl_relaxed(nfc_op->ndcb[1], nfc->regs + NDCB0);
	ग_लिखोl(nfc_op->ndcb[2], nfc->regs + NDCB0);

	/*
	 * Write NDCB0 four बार only अगर LEN_OVRD is set or अगर ADDR6 or ADDR7
	 * fields are used (only available on NFCv2).
	 */
	अगर (nfc_op->ndcb[0] & NDCB0_LEN_OVRD ||
	    NDCB0_ADDR_GET_NUM_CYC(nfc_op->ndcb[0]) >= 6) अणु
		अगर (!WARN_ON_ONCE(!nfc->caps->is_nfcv2))
			ग_लिखोl(nfc_op->ndcb[3], nfc->regs + NDCB0);
	पूर्ण
पूर्ण

अटल पूर्णांक marvell_nfc_end_cmd(काष्ठा nand_chip *chip, पूर्णांक flag,
			       स्थिर अक्षर *label)
अणु
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 val;
	पूर्णांक ret;

	ret = पढ़ोl_relaxed_poll_समयout(nfc->regs + NDSR, val,
					 val & flag,
					 POLL_PERIOD, POLL_TIMEOUT);

	अगर (ret) अणु
		dev_err(nfc->dev, "Timeout on %s (NDSR: 0x%08x)\n",
			label, val);
		अगर (nfc->dma_chan)
			dmaengine_terminate_all(nfc->dma_chan);
		वापस ret;
	पूर्ण

	/*
	 * DMA function uses this helper to poll on CMDD bits without wanting
	 * them to be cleared.
	 */
	अगर (nfc->use_dma && (पढ़ोl_relaxed(nfc->regs + NDCR) & NDCR_DMA_EN))
		वापस 0;

	ग_लिखोl_relaxed(flag, nfc->regs + NDSR);

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nfc_रुको_cmdd(काष्ठा nand_chip *chip)
अणु
	काष्ठा marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	पूर्णांक cs_flag = NDSR_CMDD(to_nand_sel(marvell_nand)->ndcb0_csel);

	वापस marvell_nfc_end_cmd(chip, cs_flag, "CMDD");
पूर्ण

अटल पूर्णांक marvell_nfc_poll_status(काष्ठा marvell_nfc *nfc, u32 mask,
				   u32 expected_val, अचिन्हित दीर्घ समयout_ms)
अणु
	अचिन्हित दीर्घ limit;
	u32 st;

	limit = jअगरfies + msecs_to_jअगरfies(समयout_ms);
	करो अणु
		st = पढ़ोl_relaxed(nfc->regs + NDSR);
		अगर (st & NDSR_RDY(1))
			st |= NDSR_RDY(0);

		अगर ((st & mask) == expected_val)
			वापस 0;

		cpu_relax();
	पूर्ण जबतक (समय_after(limit, jअगरfies));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक marvell_nfc_रुको_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक समयout_ms)
अणु
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u32 pending;
	पूर्णांक ret;

	/* Timeout is expressed in ms */
	अगर (!समयout_ms)
		समयout_ms = IRQ_TIMEOUT;

	अगर (mtd->oops_panic_ग_लिखो) अणु
		ret = marvell_nfc_poll_status(nfc, NDSR_RDY(0),
					      NDSR_RDY(0),
					      समयout_ms);
	पूर्ण अन्यथा अणु
		init_completion(&nfc->complete);

		marvell_nfc_enable_पूर्णांक(nfc, NDCR_RDYM);
		ret = रुको_क्रम_completion_समयout(&nfc->complete,
						  msecs_to_jअगरfies(समयout_ms));
		marvell_nfc_disable_पूर्णांक(nfc, NDCR_RDYM);
	पूर्ण
	pending = marvell_nfc_clear_पूर्णांक(nfc, NDSR_RDY(0) | NDSR_RDY(1));

	/*
	 * In हाल the पूर्णांकerrupt was not served in the required समय frame,
	 * check अगर the ISR was not served or अगर something went actually wrong.
	 */
	अगर (!ret && !pending) अणु
		dev_err(nfc->dev, "Timeout waiting for RB signal\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम marvell_nfc_select_target(काष्ठा nand_chip *chip,
				      अचिन्हित पूर्णांक die_nr)
अणु
	काष्ठा marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 ndcr_generic;

	/*
	 * Reset the NDCR रेजिस्टर to a clean state क्रम this particular chip,
	 * also clear ND_RUN bit.
	 */
	ndcr_generic = पढ़ोl_relaxed(nfc->regs + NDCR) &
		       NDCR_GENERIC_FIELDS_MASK & ~NDCR_ND_RUN;
	ग_लिखोl_relaxed(ndcr_generic | marvell_nand->ndcr, nfc->regs + NDCR);

	/* Also reset the पूर्णांकerrupt status रेजिस्टर */
	marvell_nfc_clear_पूर्णांक(nfc, NDCR_ALL_INT);

	अगर (chip == nfc->selected_chip && die_nr == marvell_nand->selected_die)
		वापस;

	ग_लिखोl_relaxed(marvell_nand->ndtr0, nfc->regs + NDTR0);
	ग_लिखोl_relaxed(marvell_nand->ndtr1, nfc->regs + NDTR1);

	nfc->selected_chip = chip;
	marvell_nand->selected_die = die_nr;
पूर्ण

अटल irqवापस_t marvell_nfc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा marvell_nfc *nfc = dev_id;
	u32 st = पढ़ोl_relaxed(nfc->regs + NDSR);
	u32 ien = (~पढ़ोl_relaxed(nfc->regs + NDCR)) & NDCR_ALL_INT;

	/*
	 * RDY पूर्णांकerrupt mask is one bit in NDCR जबतक there are two status
	 * bit in NDSR (RDY[cs0/cs2] and RDY[cs1/cs3]).
	 */
	अगर (st & NDSR_RDY(1))
		st |= NDSR_RDY(0);

	अगर (!(st & ien))
		वापस IRQ_NONE;

	marvell_nfc_disable_पूर्णांक(nfc, st & NDCR_ALL_INT);

	अगर (st & (NDSR_RDY(0) | NDSR_RDY(1)))
		complete(&nfc->complete);

	वापस IRQ_HANDLED;
पूर्ण

/* HW ECC related functions */
अटल व्योम marvell_nfc_enable_hw_ecc(काष्ठा nand_chip *chip)
अणु
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 ndcr = पढ़ोl_relaxed(nfc->regs + NDCR);

	अगर (!(ndcr & NDCR_ECC_EN)) अणु
		ग_लिखोl_relaxed(ndcr | NDCR_ECC_EN, nfc->regs + NDCR);

		/*
		 * When enabling BCH, set threshold to 0 to always know the
		 * number of corrected bitflips.
		 */
		अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_BCH)
			ग_लिखोl_relaxed(NDECCCTRL_BCH_EN, nfc->regs + NDECCCTRL);
	पूर्ण
पूर्ण

अटल व्योम marvell_nfc_disable_hw_ecc(काष्ठा nand_chip *chip)
अणु
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 ndcr = पढ़ोl_relaxed(nfc->regs + NDCR);

	अगर (ndcr & NDCR_ECC_EN) अणु
		ग_लिखोl_relaxed(ndcr & ~NDCR_ECC_EN, nfc->regs + NDCR);
		अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_BCH)
			ग_लिखोl_relaxed(0, nfc->regs + NDECCCTRL);
	पूर्ण
पूर्ण

/* DMA related helpers */
अटल व्योम marvell_nfc_enable_dma(काष्ठा marvell_nfc *nfc)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(nfc->regs + NDCR);
	ग_लिखोl_relaxed(reg | NDCR_DMA_EN, nfc->regs + NDCR);
पूर्ण

अटल व्योम marvell_nfc_disable_dma(काष्ठा marvell_nfc *nfc)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(nfc->regs + NDCR);
	ग_लिखोl_relaxed(reg & ~NDCR_DMA_EN, nfc->regs + NDCR);
पूर्ण

/* Read/ग_लिखो PIO/DMA accessors */
अटल पूर्णांक marvell_nfc_xfer_data_dma(काष्ठा marvell_nfc *nfc,
				     क्रमागत dma_data_direction direction,
				     अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक dma_len = min_t(पूर्णांक, ALIGN(len, 32), MAX_CHUNK_SIZE);
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा scatterlist sg;
	dma_cookie_t cookie;
	पूर्णांक ret;

	marvell_nfc_enable_dma(nfc);
	/* Prepare the DMA transfer */
	sg_init_one(&sg, nfc->dma_buf, dma_len);
	dma_map_sg(nfc->dma_chan->device->dev, &sg, 1, direction);
	tx = dmaengine_prep_slave_sg(nfc->dma_chan, &sg, 1,
				     direction == DMA_FROM_DEVICE ?
				     DMA_DEV_TO_MEM : DMA_MEM_TO_DEV,
				     DMA_PREP_INTERRUPT);
	अगर (!tx) अणु
		dev_err(nfc->dev, "Could not prepare DMA S/G list\n");
		वापस -ENXIO;
	पूर्ण

	/* Do the task and रुको क्रम it to finish */
	cookie = dmaengine_submit(tx);
	ret = dma_submit_error(cookie);
	अगर (ret)
		वापस -EIO;

	dma_async_issue_pending(nfc->dma_chan);
	ret = marvell_nfc_रुको_cmdd(nfc->selected_chip);
	dma_unmap_sg(nfc->dma_chan->device->dev, &sg, 1, direction);
	marvell_nfc_disable_dma(nfc);
	अगर (ret) अणु
		dev_err(nfc->dev, "Timeout waiting for DMA (status: %d)\n",
			dmaengine_tx_status(nfc->dma_chan, cookie, शून्य));
		dmaengine_terminate_all(nfc->dma_chan);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nfc_xfer_data_in_pio(काष्ठा marvell_nfc *nfc, u8 *in,
					अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक last_len = len % FIFO_DEPTH;
	अचिन्हित पूर्णांक last_full_offset = round_करोwn(len, FIFO_DEPTH);
	पूर्णांक i;

	क्रम (i = 0; i < last_full_offset; i += FIFO_DEPTH)
		ioपढ़ो32_rep(nfc->regs + NDDB, in + i, FIFO_REP(FIFO_DEPTH));

	अगर (last_len) अणु
		u8 पंचांगp_buf[FIFO_DEPTH];

		ioपढ़ो32_rep(nfc->regs + NDDB, पंचांगp_buf, FIFO_REP(FIFO_DEPTH));
		स_नकल(in + last_full_offset, पंचांगp_buf, last_len);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nfc_xfer_data_out_pio(काष्ठा marvell_nfc *nfc, स्थिर u8 *out,
					 अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक last_len = len % FIFO_DEPTH;
	अचिन्हित पूर्णांक last_full_offset = round_करोwn(len, FIFO_DEPTH);
	पूर्णांक i;

	क्रम (i = 0; i < last_full_offset; i += FIFO_DEPTH)
		ioग_लिखो32_rep(nfc->regs + NDDB, out + i, FIFO_REP(FIFO_DEPTH));

	अगर (last_len) अणु
		u8 पंचांगp_buf[FIFO_DEPTH];

		स_नकल(पंचांगp_buf, out + last_full_offset, last_len);
		ioग_लिखो32_rep(nfc->regs + NDDB, पंचांगp_buf, FIFO_REP(FIFO_DEPTH));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम marvell_nfc_check_empty_chunk(काष्ठा nand_chip *chip,
					  u8 *data, पूर्णांक data_len,
					  u8 *spare, पूर्णांक spare_len,
					  u8 *ecc, पूर्णांक ecc_len,
					  अचिन्हित पूर्णांक *max_bitflips)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक bf;

	/*
	 * Blank pages (all 0xFF) that have not been written may be recognized
	 * as bad अगर bitflips occur, so whenever an uncorrectable error occurs,
	 * check अगर the entire page (with ECC bytes) is actually blank or not.
	 */
	अगर (!data)
		data_len = 0;
	अगर (!spare)
		spare_len = 0;
	अगर (!ecc)
		ecc_len = 0;

	bf = nand_check_erased_ecc_chunk(data, data_len, ecc, ecc_len,
					 spare, spare_len, chip->ecc.strength);
	अगर (bf < 0) अणु
		mtd->ecc_stats.failed++;
		वापस;
	पूर्ण

	/* Update the stats and max_bitflips */
	mtd->ecc_stats.corrected += bf;
	*max_bitflips = max_t(अचिन्हित पूर्णांक, *max_bitflips, bf);
पूर्ण

/*
 * Check अगर a chunk is correct or not according to the hardware ECC engine.
 * mtd->ecc_stats.corrected is updated, as well as max_bitflips, however
 * mtd->ecc_stats.failure is not, the function will instead वापस a non-zero
 * value indicating that a check on the emptyness of the subpage must be
 * perक्रमmed beक्रमe actually declaring the subpage as "corrupted".
 */
अटल पूर्णांक marvell_nfc_hw_ecc_check_bitflips(काष्ठा nand_chip *chip,
					     अचिन्हित पूर्णांक *max_bitflips)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	पूर्णांक bf = 0;
	u32 ndsr;

	ndsr = पढ़ोl_relaxed(nfc->regs + NDSR);

	/* Check uncorrectable error flag */
	अगर (ndsr & NDSR_UNCERR) अणु
		ग_लिखोl_relaxed(ndsr, nfc->regs + NDSR);

		/*
		 * Do not increment ->ecc_stats.failed now, instead, वापस a
		 * non-zero value to indicate that this chunk was apparently
		 * bad, and it should be check to see अगर it empty or not. If
		 * the chunk (with ECC bytes) is not declared empty, the calling
		 * function must increment the failure count.
		 */
		वापस -EBADMSG;
	पूर्ण

	/* Check correctable error flag */
	अगर (ndsr & NDSR_CORERR) अणु
		ग_लिखोl_relaxed(ndsr, nfc->regs + NDSR);

		अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_BCH)
			bf = NDSR_ERRCNT(ndsr);
		अन्यथा
			bf = 1;
	पूर्ण

	/* Update the stats and max_bitflips */
	mtd->ecc_stats.corrected += bf;
	*max_bitflips = max_t(अचिन्हित पूर्णांक, *max_bitflips, bf);

	वापस 0;
पूर्ण

/* Hamming पढ़ो helpers */
अटल पूर्णांक marvell_nfc_hw_ecc_hmg_करो_पढ़ो_page(काष्ठा nand_chip *chip,
					       u8 *data_buf, u8 *oob_buf,
					       bool raw, पूर्णांक page)
अणु
	काष्ठा marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	स्थिर काष्ठा marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	काष्ठा marvell_nfc_op nfc_op = अणु
		.ndcb[0] = NDCB0_CMD_TYPE(TYPE_READ) |
			   NDCB0_ADDR_CYC(marvell_nand->addr_cyc) |
			   NDCB0_DBC |
			   NDCB0_CMD1(न_अंकD_CMD_READ0) |
			   NDCB0_CMD2(न_अंकD_CMD_READSTART),
		.ndcb[1] = NDCB1_ADDRS_PAGE(page),
		.ndcb[2] = NDCB2_ADDR5_PAGE(page),
	पूर्ण;
	अचिन्हित पूर्णांक oob_bytes = lt->spare_bytes + (raw ? lt->ecc_bytes : 0);
	पूर्णांक ret;

	/* NFCv2 needs more inक्रमmation about the operation being executed */
	अगर (nfc->caps->is_nfcv2)
		nfc_op.ndcb[0] |= NDCB0_CMD_XTYPE(XTYPE_MONOLITHIC_RW);

	ret = marvell_nfc_prepare_cmd(chip);
	अगर (ret)
		वापस ret;

	marvell_nfc_send_cmd(chip, &nfc_op);
	ret = marvell_nfc_end_cmd(chip, NDSR_RDDREQ,
				  "RDDREQ while draining FIFO (data/oob)");
	अगर (ret)
		वापस ret;

	/*
	 * Read the page then the OOB area. Unlike what is shown in current
	 * करोcumentation, spare bytes are रक्षित by the ECC engine, and must
	 * be at the beginning of the OOB area or running this driver on legacy
	 * प्रणालीs will prevent the discovery of the BBM/BBT.
	 */
	अगर (nfc->use_dma) अणु
		marvell_nfc_xfer_data_dma(nfc, DMA_FROM_DEVICE,
					  lt->data_bytes + oob_bytes);
		स_नकल(data_buf, nfc->dma_buf, lt->data_bytes);
		स_नकल(oob_buf, nfc->dma_buf + lt->data_bytes, oob_bytes);
	पूर्ण अन्यथा अणु
		marvell_nfc_xfer_data_in_pio(nfc, data_buf, lt->data_bytes);
		marvell_nfc_xfer_data_in_pio(nfc, oob_buf, oob_bytes);
	पूर्ण

	ret = marvell_nfc_रुको_cmdd(chip);
	वापस ret;
पूर्ण

अटल पूर्णांक marvell_nfc_hw_ecc_hmg_पढ़ो_page_raw(काष्ठा nand_chip *chip, u8 *buf,
						पूर्णांक oob_required, पूर्णांक page)
अणु
	marvell_nfc_select_target(chip, chip->cur_cs);
	वापस marvell_nfc_hw_ecc_hmg_करो_पढ़ो_page(chip, buf, chip->oob_poi,
						   true, page);
पूर्ण

अटल पूर्णांक marvell_nfc_hw_ecc_hmg_पढ़ो_page(काष्ठा nand_chip *chip, u8 *buf,
					    पूर्णांक oob_required, पूर्णांक page)
अणु
	स्थिर काष्ठा marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	अचिन्हित पूर्णांक full_sz = lt->data_bytes + lt->spare_bytes + lt->ecc_bytes;
	पूर्णांक max_bitflips = 0, ret;
	u8 *raw_buf;

	marvell_nfc_select_target(chip, chip->cur_cs);
	marvell_nfc_enable_hw_ecc(chip);
	marvell_nfc_hw_ecc_hmg_करो_पढ़ो_page(chip, buf, chip->oob_poi, false,
					    page);
	ret = marvell_nfc_hw_ecc_check_bitflips(chip, &max_bitflips);
	marvell_nfc_disable_hw_ecc(chip);

	अगर (!ret)
		वापस max_bitflips;

	/*
	 * When ECC failures are detected, check अगर the full page has been
	 * written or not. Ignore the failure अगर it is actually empty.
	 */
	raw_buf = kदो_स्मृति(full_sz, GFP_KERNEL);
	अगर (!raw_buf)
		वापस -ENOMEM;

	marvell_nfc_hw_ecc_hmg_करो_पढ़ो_page(chip, raw_buf, raw_buf +
					    lt->data_bytes, true, page);
	marvell_nfc_check_empty_chunk(chip, raw_buf, full_sz, शून्य, 0, शून्य, 0,
				      &max_bitflips);
	kमुक्त(raw_buf);

	वापस max_bitflips;
पूर्ण

/*
 * Spare area in Hamming layouts is not रक्षित by the ECC engine (even अगर
 * it appears beक्रमe the ECC bytes when पढ़ोing), the ->पढ़ो_oob_raw() function
 * also stands क्रम ->पढ़ो_oob().
 */
अटल पूर्णांक marvell_nfc_hw_ecc_hmg_पढ़ो_oob_raw(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	u8 *buf = nand_get_data_buf(chip);

	marvell_nfc_select_target(chip, chip->cur_cs);
	वापस marvell_nfc_hw_ecc_hmg_करो_पढ़ो_page(chip, buf, chip->oob_poi,
						   true, page);
पूर्ण

/* Hamming ग_लिखो helpers */
अटल पूर्णांक marvell_nfc_hw_ecc_hmg_करो_ग_लिखो_page(काष्ठा nand_chip *chip,
						स्थिर u8 *data_buf,
						स्थिर u8 *oob_buf, bool raw,
						पूर्णांक page)
अणु
	स्थिर काष्ठा nand_sdr_timings *sdr =
		nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
	काष्ठा marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	स्थिर काष्ठा marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	काष्ठा marvell_nfc_op nfc_op = अणु
		.ndcb[0] = NDCB0_CMD_TYPE(TYPE_WRITE) |
			   NDCB0_ADDR_CYC(marvell_nand->addr_cyc) |
			   NDCB0_CMD1(न_अंकD_CMD_SEQIN) |
			   NDCB0_CMD2(न_अंकD_CMD_PAGEPROG) |
			   NDCB0_DBC,
		.ndcb[1] = NDCB1_ADDRS_PAGE(page),
		.ndcb[2] = NDCB2_ADDR5_PAGE(page),
	पूर्ण;
	अचिन्हित पूर्णांक oob_bytes = lt->spare_bytes + (raw ? lt->ecc_bytes : 0);
	पूर्णांक ret;

	/* NFCv2 needs more inक्रमmation about the operation being executed */
	अगर (nfc->caps->is_nfcv2)
		nfc_op.ndcb[0] |= NDCB0_CMD_XTYPE(XTYPE_MONOLITHIC_RW);

	ret = marvell_nfc_prepare_cmd(chip);
	अगर (ret)
		वापस ret;

	marvell_nfc_send_cmd(chip, &nfc_op);
	ret = marvell_nfc_end_cmd(chip, NDSR_WRDREQ,
				  "WRDREQ while loading FIFO (data)");
	अगर (ret)
		वापस ret;

	/* Write the page then the OOB area */
	अगर (nfc->use_dma) अणु
		स_नकल(nfc->dma_buf, data_buf, lt->data_bytes);
		स_नकल(nfc->dma_buf + lt->data_bytes, oob_buf, oob_bytes);
		marvell_nfc_xfer_data_dma(nfc, DMA_TO_DEVICE, lt->data_bytes +
					  lt->ecc_bytes + lt->spare_bytes);
	पूर्ण अन्यथा अणु
		marvell_nfc_xfer_data_out_pio(nfc, data_buf, lt->data_bytes);
		marvell_nfc_xfer_data_out_pio(nfc, oob_buf, oob_bytes);
	पूर्ण

	ret = marvell_nfc_रुको_cmdd(chip);
	अगर (ret)
		वापस ret;

	ret = marvell_nfc_रुको_op(chip,
				  PSEC_TO_MSEC(sdr->tPROG_max));
	वापस ret;
पूर्ण

अटल पूर्णांक marvell_nfc_hw_ecc_hmg_ग_लिखो_page_raw(काष्ठा nand_chip *chip,
						 स्थिर u8 *buf,
						 पूर्णांक oob_required, पूर्णांक page)
अणु
	marvell_nfc_select_target(chip, chip->cur_cs);
	वापस marvell_nfc_hw_ecc_hmg_करो_ग_लिखो_page(chip, buf, chip->oob_poi,
						    true, page);
पूर्ण

अटल पूर्णांक marvell_nfc_hw_ecc_hmg_ग_लिखो_page(काष्ठा nand_chip *chip,
					     स्थिर u8 *buf,
					     पूर्णांक oob_required, पूर्णांक page)
अणु
	पूर्णांक ret;

	marvell_nfc_select_target(chip, chip->cur_cs);
	marvell_nfc_enable_hw_ecc(chip);
	ret = marvell_nfc_hw_ecc_hmg_करो_ग_लिखो_page(chip, buf, chip->oob_poi,
						   false, page);
	marvell_nfc_disable_hw_ecc(chip);

	वापस ret;
पूर्ण

/*
 * Spare area in Hamming layouts is not रक्षित by the ECC engine (even अगर
 * it appears beक्रमe the ECC bytes when पढ़ोing), the ->ग_लिखो_oob_raw() function
 * also stands क्रम ->ग_लिखो_oob().
 */
अटल पूर्णांक marvell_nfc_hw_ecc_hmg_ग_लिखो_oob_raw(काष्ठा nand_chip *chip,
						पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u8 *buf = nand_get_data_buf(chip);

	स_रखो(buf, 0xFF, mtd->ग_लिखोsize);

	marvell_nfc_select_target(chip, chip->cur_cs);
	वापस marvell_nfc_hw_ecc_hmg_करो_ग_लिखो_page(chip, buf, chip->oob_poi,
						    true, page);
पूर्ण

/* BCH पढ़ो helpers */
अटल पूर्णांक marvell_nfc_hw_ecc_bch_पढ़ो_page_raw(काष्ठा nand_chip *chip, u8 *buf,
						पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	स्थिर काष्ठा marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	u8 *oob = chip->oob_poi;
	पूर्णांक chunk_size = lt->data_bytes + lt->spare_bytes + lt->ecc_bytes;
	पूर्णांक ecc_offset = (lt->full_chunk_cnt * lt->spare_bytes) +
		lt->last_spare_bytes;
	पूर्णांक data_len = lt->data_bytes;
	पूर्णांक spare_len = lt->spare_bytes;
	पूर्णांक ecc_len = lt->ecc_bytes;
	पूर्णांक chunk;

	marvell_nfc_select_target(chip, chip->cur_cs);

	अगर (oob_required)
		स_रखो(chip->oob_poi, 0xFF, mtd->oobsize);

	nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);

	क्रम (chunk = 0; chunk < lt->nchunks; chunk++) अणु
		/* Update last chunk length */
		अगर (chunk >= lt->full_chunk_cnt) अणु
			data_len = lt->last_data_bytes;
			spare_len = lt->last_spare_bytes;
			ecc_len = lt->last_ecc_bytes;
		पूर्ण

		/* Read data bytes*/
		nand_change_पढ़ो_column_op(chip, chunk * chunk_size,
					   buf + (lt->data_bytes * chunk),
					   data_len, false);

		/* Read spare bytes */
		nand_पढ़ो_data_op(chip, oob + (lt->spare_bytes * chunk),
				  spare_len, false, false);

		/* Read ECC bytes */
		nand_पढ़ो_data_op(chip, oob + ecc_offset +
				  (ALIGN(lt->ecc_bytes, 32) * chunk),
				  ecc_len, false, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम marvell_nfc_hw_ecc_bch_पढ़ो_chunk(काष्ठा nand_chip *chip, पूर्णांक chunk,
					      u8 *data, अचिन्हित पूर्णांक data_len,
					      u8 *spare, अचिन्हित पूर्णांक spare_len,
					      पूर्णांक page)
अणु
	काष्ठा marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	स्थिर काष्ठा marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	पूर्णांक i, ret;
	काष्ठा marvell_nfc_op nfc_op = अणु
		.ndcb[0] = NDCB0_CMD_TYPE(TYPE_READ) |
			   NDCB0_ADDR_CYC(marvell_nand->addr_cyc) |
			   NDCB0_LEN_OVRD,
		.ndcb[1] = NDCB1_ADDRS_PAGE(page),
		.ndcb[2] = NDCB2_ADDR5_PAGE(page),
		.ndcb[3] = data_len + spare_len,
	पूर्ण;

	ret = marvell_nfc_prepare_cmd(chip);
	अगर (ret)
		वापस;

	अगर (chunk == 0)
		nfc_op.ndcb[0] |= NDCB0_DBC |
				  NDCB0_CMD1(न_अंकD_CMD_READ0) |
				  NDCB0_CMD2(न_अंकD_CMD_READSTART);

	/*
	 * Trigger the monolithic पढ़ो on the first chunk, then naked पढ़ो on
	 * पूर्णांकermediate chunks and finally a last naked पढ़ो on the last chunk.
	 */
	अगर (chunk == 0)
		nfc_op.ndcb[0] |= NDCB0_CMD_XTYPE(XTYPE_MONOLITHIC_RW);
	अन्यथा अगर (chunk < lt->nchunks - 1)
		nfc_op.ndcb[0] |= NDCB0_CMD_XTYPE(XTYPE_NAKED_RW);
	अन्यथा
		nfc_op.ndcb[0] |= NDCB0_CMD_XTYPE(XTYPE_LAST_NAKED_RW);

	marvell_nfc_send_cmd(chip, &nfc_op);

	/*
	 * According to the datasheet, when पढ़ोing from NDDB
	 * with BCH enabled, after each 32 bytes पढ़ोs, we
	 * have to make sure that the NDSR.RDDREQ bit is set.
	 *
	 * Drain the FIFO, 8 32-bit पढ़ोs at a समय, and skip
	 * the polling on the last पढ़ो.
	 *
	 * Length is a multiple of 32 bytes, hence it is a multiple of 8 too.
	 */
	क्रम (i = 0; i < data_len; i += FIFO_DEPTH * BCH_SEQ_READS) अणु
		marvell_nfc_end_cmd(chip, NDSR_RDDREQ,
				    "RDDREQ while draining FIFO (data)");
		marvell_nfc_xfer_data_in_pio(nfc, data,
					     FIFO_DEPTH * BCH_SEQ_READS);
		data += FIFO_DEPTH * BCH_SEQ_READS;
	पूर्ण

	क्रम (i = 0; i < spare_len; i += FIFO_DEPTH * BCH_SEQ_READS) अणु
		marvell_nfc_end_cmd(chip, NDSR_RDDREQ,
				    "RDDREQ while draining FIFO (OOB)");
		marvell_nfc_xfer_data_in_pio(nfc, spare,
					     FIFO_DEPTH * BCH_SEQ_READS);
		spare += FIFO_DEPTH * BCH_SEQ_READS;
	पूर्ण
पूर्ण

अटल पूर्णांक marvell_nfc_hw_ecc_bch_पढ़ो_page(काष्ठा nand_chip *chip,
					    u8 *buf, पूर्णांक oob_required,
					    पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	स्थिर काष्ठा marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	पूर्णांक data_len = lt->data_bytes, spare_len = lt->spare_bytes;
	u8 *data = buf, *spare = chip->oob_poi;
	पूर्णांक max_bitflips = 0;
	u32 failure_mask = 0;
	पूर्णांक chunk, ret;

	marvell_nfc_select_target(chip, chip->cur_cs);

	/*
	 * With BCH, OOB is not fully used (and thus not पढ़ो entirely), not
	 * expected bytes could show up at the end of the OOB buffer अगर not
	 * explicitly erased.
	 */
	अगर (oob_required)
		स_रखो(chip->oob_poi, 0xFF, mtd->oobsize);

	marvell_nfc_enable_hw_ecc(chip);

	क्रम (chunk = 0; chunk < lt->nchunks; chunk++) अणु
		/* Update length क्रम the last chunk */
		अगर (chunk >= lt->full_chunk_cnt) अणु
			data_len = lt->last_data_bytes;
			spare_len = lt->last_spare_bytes;
		पूर्ण

		/* Read the chunk and detect number of bitflips */
		marvell_nfc_hw_ecc_bch_पढ़ो_chunk(chip, chunk, data, data_len,
						  spare, spare_len, page);
		ret = marvell_nfc_hw_ecc_check_bitflips(chip, &max_bitflips);
		अगर (ret)
			failure_mask |= BIT(chunk);

		data += data_len;
		spare += spare_len;
	पूर्ण

	marvell_nfc_disable_hw_ecc(chip);

	अगर (!failure_mask)
		वापस max_bitflips;

	/*
	 * Please note that dumping the ECC bytes during a normal पढ़ो with OOB
	 * area would add a signअगरicant overhead as ECC bytes are "consumed" by
	 * the controller in normal mode and must be re-पढ़ो in raw mode. To
	 * aव्योम dropping the perक्रमmances, we prefer not to include them. The
	 * user should re-पढ़ो the page in raw mode अगर ECC bytes are required.
	 */

	/*
	 * In हाल there is any subpage पढ़ो error, we usually re-पढ़ो only ECC
	 * bytes in raw mode and check अगर the whole page is empty. In this हाल,
	 * it is normal that the ECC check failed and we just ignore the error.
	 *
	 * However, it has been empirically observed that क्रम some layouts (e.g
	 * 2k page, 8b strength per 512B chunk), the controller tries to correct
	 * bits and may create itself bitflips in the erased area. To overcome
	 * this strange behavior, the whole page is re-पढ़ो in raw mode, not
	 * only the ECC bytes.
	 */
	क्रम (chunk = 0; chunk < lt->nchunks; chunk++) अणु
		पूर्णांक data_off_in_page, spare_off_in_page, ecc_off_in_page;
		पूर्णांक data_off, spare_off, ecc_off;
		पूर्णांक data_len, spare_len, ecc_len;

		/* No failure reported क्रम this chunk, move to the next one */
		अगर (!(failure_mask & BIT(chunk)))
			जारी;

		data_off_in_page = chunk * (lt->data_bytes + lt->spare_bytes +
					    lt->ecc_bytes);
		spare_off_in_page = data_off_in_page +
			(chunk < lt->full_chunk_cnt ? lt->data_bytes :
						      lt->last_data_bytes);
		ecc_off_in_page = spare_off_in_page +
			(chunk < lt->full_chunk_cnt ? lt->spare_bytes :
						      lt->last_spare_bytes);

		data_off = chunk * lt->data_bytes;
		spare_off = chunk * lt->spare_bytes;
		ecc_off = (lt->full_chunk_cnt * lt->spare_bytes) +
			  lt->last_spare_bytes +
			  (chunk * (lt->ecc_bytes + 2));

		data_len = chunk < lt->full_chunk_cnt ? lt->data_bytes :
							lt->last_data_bytes;
		spare_len = chunk < lt->full_chunk_cnt ? lt->spare_bytes :
							 lt->last_spare_bytes;
		ecc_len = chunk < lt->full_chunk_cnt ? lt->ecc_bytes :
						       lt->last_ecc_bytes;

		/*
		 * Only re-पढ़ो the ECC bytes, unless we are using the 2k/8b
		 * layout which is buggy in the sense that the ECC engine will
		 * try to correct data bytes anyway, creating bitflips. In this
		 * हाल, re-पढ़ो the entire page.
		 */
		अगर (lt->ग_लिखोsize == 2048 && lt->strength == 8) अणु
			nand_change_पढ़ो_column_op(chip, data_off_in_page,
						   buf + data_off, data_len,
						   false);
			nand_change_पढ़ो_column_op(chip, spare_off_in_page,
						   chip->oob_poi + spare_off, spare_len,
						   false);
		पूर्ण

		nand_change_पढ़ो_column_op(chip, ecc_off_in_page,
					   chip->oob_poi + ecc_off, ecc_len,
					   false);

		/* Check the entire chunk (data + spare + ecc) क्रम emptyness */
		marvell_nfc_check_empty_chunk(chip, buf + data_off, data_len,
					      chip->oob_poi + spare_off, spare_len,
					      chip->oob_poi + ecc_off, ecc_len,
					      &max_bitflips);
	पूर्ण

	वापस max_bitflips;
पूर्ण

अटल पूर्णांक marvell_nfc_hw_ecc_bch_पढ़ो_oob_raw(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	u8 *buf = nand_get_data_buf(chip);

	वापस chip->ecc.पढ़ो_page_raw(chip, buf, true, page);
पूर्ण

अटल पूर्णांक marvell_nfc_hw_ecc_bch_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	u8 *buf = nand_get_data_buf(chip);

	वापस chip->ecc.पढ़ो_page(chip, buf, true, page);
पूर्ण

/* BCH ग_लिखो helpers */
अटल पूर्णांक marvell_nfc_hw_ecc_bch_ग_लिखो_page_raw(काष्ठा nand_chip *chip,
						 स्थिर u8 *buf,
						 पूर्णांक oob_required, पूर्णांक page)
अणु
	स्थिर काष्ठा marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	पूर्णांक full_chunk_size = lt->data_bytes + lt->spare_bytes + lt->ecc_bytes;
	पूर्णांक data_len = lt->data_bytes;
	पूर्णांक spare_len = lt->spare_bytes;
	पूर्णांक ecc_len = lt->ecc_bytes;
	पूर्णांक spare_offset = 0;
	पूर्णांक ecc_offset = (lt->full_chunk_cnt * lt->spare_bytes) +
		lt->last_spare_bytes;
	पूर्णांक chunk;

	marvell_nfc_select_target(chip, chip->cur_cs);

	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);

	क्रम (chunk = 0; chunk < lt->nchunks; chunk++) अणु
		अगर (chunk >= lt->full_chunk_cnt) अणु
			data_len = lt->last_data_bytes;
			spare_len = lt->last_spare_bytes;
			ecc_len = lt->last_ecc_bytes;
		पूर्ण

		/* Poपूर्णांक to the column of the next chunk */
		nand_change_ग_लिखो_column_op(chip, chunk * full_chunk_size,
					    शून्य, 0, false);

		/* Write the data */
		nand_ग_लिखो_data_op(chip, buf + (chunk * lt->data_bytes),
				   data_len, false);

		अगर (!oob_required)
			जारी;

		/* Write the spare bytes */
		अगर (spare_len)
			nand_ग_लिखो_data_op(chip, chip->oob_poi + spare_offset,
					   spare_len, false);

		/* Write the ECC bytes */
		अगर (ecc_len)
			nand_ग_लिखो_data_op(chip, chip->oob_poi + ecc_offset,
					   ecc_len, false);

		spare_offset += spare_len;
		ecc_offset += ALIGN(ecc_len, 32);
	पूर्ण

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक
marvell_nfc_hw_ecc_bch_ग_लिखो_chunk(काष्ठा nand_chip *chip, पूर्णांक chunk,
				   स्थिर u8 *data, अचिन्हित पूर्णांक data_len,
				   स्थिर u8 *spare, अचिन्हित पूर्णांक spare_len,
				   पूर्णांक page)
अणु
	काष्ठा marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	स्थिर काष्ठा marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	u32 xtype;
	पूर्णांक ret;
	काष्ठा marvell_nfc_op nfc_op = अणु
		.ndcb[0] = NDCB0_CMD_TYPE(TYPE_WRITE) | NDCB0_LEN_OVRD,
		.ndcb[3] = data_len + spare_len,
	पूर्ण;

	/*
	 * First operation dispatches the CMD_SEQIN command, issue the address
	 * cycles and asks क्रम the first chunk of data.
	 * All operations in the middle (अगर any) will issue a naked ग_लिखो and
	 * also ask क्रम data.
	 * Last operation (अगर any) asks क्रम the last chunk of data through a
	 * last naked ग_लिखो.
	 */
	अगर (chunk == 0) अणु
		अगर (lt->nchunks == 1)
			xtype = XTYPE_MONOLITHIC_RW;
		अन्यथा
			xtype = XTYPE_WRITE_DISPATCH;

		nfc_op.ndcb[0] |= NDCB0_CMD_XTYPE(xtype) |
				  NDCB0_ADDR_CYC(marvell_nand->addr_cyc) |
				  NDCB0_CMD1(न_अंकD_CMD_SEQIN);
		nfc_op.ndcb[1] |= NDCB1_ADDRS_PAGE(page);
		nfc_op.ndcb[2] |= NDCB2_ADDR5_PAGE(page);
	पूर्ण अन्यथा अगर (chunk < lt->nchunks - 1) अणु
		nfc_op.ndcb[0] |= NDCB0_CMD_XTYPE(XTYPE_NAKED_RW);
	पूर्ण अन्यथा अणु
		nfc_op.ndcb[0] |= NDCB0_CMD_XTYPE(XTYPE_LAST_NAKED_RW);
	पूर्ण

	/* Always dispatch the PAGEPROG command on the last chunk */
	अगर (chunk == lt->nchunks - 1)
		nfc_op.ndcb[0] |= NDCB0_CMD2(न_अंकD_CMD_PAGEPROG) | NDCB0_DBC;

	ret = marvell_nfc_prepare_cmd(chip);
	अगर (ret)
		वापस ret;

	marvell_nfc_send_cmd(chip, &nfc_op);
	ret = marvell_nfc_end_cmd(chip, NDSR_WRDREQ,
				  "WRDREQ while loading FIFO (data)");
	अगर (ret)
		वापस ret;

	/* Transfer the contents */
	ioग_लिखो32_rep(nfc->regs + NDDB, data, FIFO_REP(data_len));
	ioग_लिखो32_rep(nfc->regs + NDDB, spare, FIFO_REP(spare_len));

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nfc_hw_ecc_bch_ग_लिखो_page(काष्ठा nand_chip *chip,
					     स्थिर u8 *buf,
					     पूर्णांक oob_required, पूर्णांक page)
अणु
	स्थिर काष्ठा nand_sdr_timings *sdr =
		nand_get_sdr_timings(nand_get_पूर्णांकerface_config(chip));
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	स्थिर काष्ठा marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	स्थिर u8 *data = buf;
	स्थिर u8 *spare = chip->oob_poi;
	पूर्णांक data_len = lt->data_bytes;
	पूर्णांक spare_len = lt->spare_bytes;
	पूर्णांक chunk, ret;

	marvell_nfc_select_target(chip, chip->cur_cs);

	/* Spare data will be written anyway, so clear it to aव्योम garbage */
	अगर (!oob_required)
		स_रखो(chip->oob_poi, 0xFF, mtd->oobsize);

	marvell_nfc_enable_hw_ecc(chip);

	क्रम (chunk = 0; chunk < lt->nchunks; chunk++) अणु
		अगर (chunk >= lt->full_chunk_cnt) अणु
			data_len = lt->last_data_bytes;
			spare_len = lt->last_spare_bytes;
		पूर्ण

		marvell_nfc_hw_ecc_bch_ग_लिखो_chunk(chip, chunk, data, data_len,
						   spare, spare_len, page);
		data += data_len;
		spare += spare_len;

		/*
		 * Waiting only क्रम CMDD or PAGED is not enough, ECC are
		 * partially written. No flag is set once the operation is
		 * really finished but the ND_RUN bit is cleared, so रुको क्रम it
		 * beक्रमe stepping पूर्णांकo the next command.
		 */
		marvell_nfc_रुको_ndrun(chip);
	पूर्ण

	ret = marvell_nfc_रुको_op(chip, PSEC_TO_MSEC(sdr->tPROG_max));

	marvell_nfc_disable_hw_ecc(chip);

	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nfc_hw_ecc_bch_ग_लिखो_oob_raw(काष्ठा nand_chip *chip,
						पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u8 *buf = nand_get_data_buf(chip);

	स_रखो(buf, 0xFF, mtd->ग_लिखोsize);

	वापस chip->ecc.ग_लिखो_page_raw(chip, buf, true, page);
पूर्ण

अटल पूर्णांक marvell_nfc_hw_ecc_bch_ग_लिखो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u8 *buf = nand_get_data_buf(chip);

	स_रखो(buf, 0xFF, mtd->ग_लिखोsize);

	वापस chip->ecc.ग_लिखो_page(chip, buf, true, page);
पूर्ण

/* न_अंकD framework ->exec_op() hooks and related helpers */
अटल व्योम marvell_nfc_parse_inकाष्ठाions(काष्ठा nand_chip *chip,
					   स्थिर काष्ठा nand_subop *subop,
					   काष्ठा marvell_nfc_op *nfc_op)
अणु
	स्थिर काष्ठा nand_op_instr *instr = शून्य;
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	bool first_cmd = true;
	अचिन्हित पूर्णांक op_id;
	पूर्णांक i;

	/* Reset the input काष्ठाure as most of its fields will be OR'ed */
	स_रखो(nfc_op, 0, माप(काष्ठा marvell_nfc_op));

	क्रम (op_id = 0; op_id < subop->ninstrs; op_id++) अणु
		अचिन्हित पूर्णांक offset, naddrs;
		स्थिर u8 *addrs;
		पूर्णांक len;

		instr = &subop->instrs[op_id];

		चयन (instr->type) अणु
		हाल न_अंकD_OP_CMD_INSTR:
			अगर (first_cmd)
				nfc_op->ndcb[0] |=
					NDCB0_CMD1(instr->ctx.cmd.opcode);
			अन्यथा
				nfc_op->ndcb[0] |=
					NDCB0_CMD2(instr->ctx.cmd.opcode) |
					NDCB0_DBC;

			nfc_op->cle_ale_delay_ns = instr->delay_ns;
			first_cmd = false;
			अवरोध;

		हाल न_अंकD_OP_ADDR_INSTR:
			offset = nand_subop_get_addr_start_off(subop, op_id);
			naddrs = nand_subop_get_num_addr_cyc(subop, op_id);
			addrs = &instr->ctx.addr.addrs[offset];

			nfc_op->ndcb[0] |= NDCB0_ADDR_CYC(naddrs);

			क्रम (i = 0; i < min_t(अचिन्हित पूर्णांक, 4, naddrs); i++)
				nfc_op->ndcb[1] |= addrs[i] << (8 * i);

			अगर (naddrs >= 5)
				nfc_op->ndcb[2] |= NDCB2_ADDR5_CYC(addrs[4]);
			अगर (naddrs >= 6)
				nfc_op->ndcb[3] |= NDCB3_ADDR6_CYC(addrs[5]);
			अगर (naddrs == 7)
				nfc_op->ndcb[3] |= NDCB3_ADDR7_CYC(addrs[6]);

			nfc_op->cle_ale_delay_ns = instr->delay_ns;
			अवरोध;

		हाल न_अंकD_OP_DATA_IN_INSTR:
			nfc_op->data_instr = instr;
			nfc_op->data_instr_idx = op_id;
			nfc_op->ndcb[0] |= NDCB0_CMD_TYPE(TYPE_READ);
			अगर (nfc->caps->is_nfcv2) अणु
				nfc_op->ndcb[0] |=
					NDCB0_CMD_XTYPE(XTYPE_MONOLITHIC_RW) |
					NDCB0_LEN_OVRD;
				len = nand_subop_get_data_len(subop, op_id);
				nfc_op->ndcb[3] |= round_up(len, FIFO_DEPTH);
			पूर्ण
			nfc_op->data_delay_ns = instr->delay_ns;
			अवरोध;

		हाल न_अंकD_OP_DATA_OUT_INSTR:
			nfc_op->data_instr = instr;
			nfc_op->data_instr_idx = op_id;
			nfc_op->ndcb[0] |= NDCB0_CMD_TYPE(TYPE_WRITE);
			अगर (nfc->caps->is_nfcv2) अणु
				nfc_op->ndcb[0] |=
					NDCB0_CMD_XTYPE(XTYPE_MONOLITHIC_RW) |
					NDCB0_LEN_OVRD;
				len = nand_subop_get_data_len(subop, op_id);
				nfc_op->ndcb[3] |= round_up(len, FIFO_DEPTH);
			पूर्ण
			nfc_op->data_delay_ns = instr->delay_ns;
			अवरोध;

		हाल न_अंकD_OP_WAITRDY_INSTR:
			nfc_op->rdy_समयout_ms = instr->ctx.रुकोrdy.समयout_ms;
			nfc_op->rdy_delay_ns = instr->delay_ns;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक marvell_nfc_xfer_data_pio(काष्ठा nand_chip *chip,
				     स्थिर काष्ठा nand_subop *subop,
				     काष्ठा marvell_nfc_op *nfc_op)
अणु
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	स्थिर काष्ठा nand_op_instr *instr = nfc_op->data_instr;
	अचिन्हित पूर्णांक op_id = nfc_op->data_instr_idx;
	अचिन्हित पूर्णांक len = nand_subop_get_data_len(subop, op_id);
	अचिन्हित पूर्णांक offset = nand_subop_get_data_start_off(subop, op_id);
	bool पढ़ोing = (instr->type == न_अंकD_OP_DATA_IN_INSTR);
	पूर्णांक ret;

	अगर (instr->ctx.data.क्रमce_8bit)
		marvell_nfc_क्रमce_byte_access(chip, true);

	अगर (पढ़ोing) अणु
		u8 *in = instr->ctx.data.buf.in + offset;

		ret = marvell_nfc_xfer_data_in_pio(nfc, in, len);
	पूर्ण अन्यथा अणु
		स्थिर u8 *out = instr->ctx.data.buf.out + offset;

		ret = marvell_nfc_xfer_data_out_pio(nfc, out, len);
	पूर्ण

	अगर (instr->ctx.data.क्रमce_8bit)
		marvell_nfc_क्रमce_byte_access(chip, false);

	वापस ret;
पूर्ण

अटल पूर्णांक marvell_nfc_monolithic_access_exec(काष्ठा nand_chip *chip,
					      स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा marvell_nfc_op nfc_op;
	bool पढ़ोing;
	पूर्णांक ret;

	marvell_nfc_parse_inकाष्ठाions(chip, subop, &nfc_op);
	पढ़ोing = (nfc_op.data_instr->type == न_अंकD_OP_DATA_IN_INSTR);

	ret = marvell_nfc_prepare_cmd(chip);
	अगर (ret)
		वापस ret;

	marvell_nfc_send_cmd(chip, &nfc_op);
	ret = marvell_nfc_end_cmd(chip, NDSR_RDDREQ | NDSR_WRDREQ,
				  "RDDREQ/WRDREQ while draining raw data");
	अगर (ret)
		वापस ret;

	cond_delay(nfc_op.cle_ale_delay_ns);

	अगर (पढ़ोing) अणु
		अगर (nfc_op.rdy_समयout_ms) अणु
			ret = marvell_nfc_रुको_op(chip, nfc_op.rdy_समयout_ms);
			अगर (ret)
				वापस ret;
		पूर्ण

		cond_delay(nfc_op.rdy_delay_ns);
	पूर्ण

	marvell_nfc_xfer_data_pio(chip, subop, &nfc_op);
	ret = marvell_nfc_रुको_cmdd(chip);
	अगर (ret)
		वापस ret;

	cond_delay(nfc_op.data_delay_ns);

	अगर (!पढ़ोing) अणु
		अगर (nfc_op.rdy_समयout_ms) अणु
			ret = marvell_nfc_रुको_op(chip, nfc_op.rdy_समयout_ms);
			अगर (ret)
				वापस ret;
		पूर्ण

		cond_delay(nfc_op.rdy_delay_ns);
	पूर्ण

	/*
	 * NDCR ND_RUN bit should be cleared स्वतःmatically at the end of each
	 * operation but experience shows that the behavior is buggy when it
	 * comes to ग_लिखोs (with LEN_OVRD). Clear it by hand in this हाल.
	 */
	अगर (!पढ़ोing) अणु
		काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);

		ग_लिखोl_relaxed(पढ़ोl(nfc->regs + NDCR) & ~NDCR_ND_RUN,
			       nfc->regs + NDCR);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nfc_naked_access_exec(काष्ठा nand_chip *chip,
					 स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा marvell_nfc_op nfc_op;
	पूर्णांक ret;

	marvell_nfc_parse_inकाष्ठाions(chip, subop, &nfc_op);

	/*
	 * Naked access are dअगरferent in that they need to be flagged as naked
	 * by the controller. Reset the controller रेजिस्टरs fields that inक्रमm
	 * on the type and refill them according to the ongoing operation.
	 */
	nfc_op.ndcb[0] &= ~(NDCB0_CMD_TYPE(TYPE_MASK) |
			    NDCB0_CMD_XTYPE(XTYPE_MASK));
	चयन (subop->instrs[0].type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_NAKED_CMD);
		अवरोध;
	हाल न_अंकD_OP_ADDR_INSTR:
		nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_NAKED_ADDR);
		अवरोध;
	हाल न_अंकD_OP_DATA_IN_INSTR:
		nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_READ) |
				  NDCB0_CMD_XTYPE(XTYPE_LAST_NAKED_RW);
		अवरोध;
	हाल न_अंकD_OP_DATA_OUT_INSTR:
		nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_WRITE) |
				  NDCB0_CMD_XTYPE(XTYPE_LAST_NAKED_RW);
		अवरोध;
	शेष:
		/* This should never happen */
		अवरोध;
	पूर्ण

	ret = marvell_nfc_prepare_cmd(chip);
	अगर (ret)
		वापस ret;

	marvell_nfc_send_cmd(chip, &nfc_op);

	अगर (!nfc_op.data_instr) अणु
		ret = marvell_nfc_रुको_cmdd(chip);
		cond_delay(nfc_op.cle_ale_delay_ns);
		वापस ret;
	पूर्ण

	ret = marvell_nfc_end_cmd(chip, NDSR_RDDREQ | NDSR_WRDREQ,
				  "RDDREQ/WRDREQ while draining raw data");
	अगर (ret)
		वापस ret;

	marvell_nfc_xfer_data_pio(chip, subop, &nfc_op);
	ret = marvell_nfc_रुको_cmdd(chip);
	अगर (ret)
		वापस ret;

	/*
	 * NDCR ND_RUN bit should be cleared स्वतःmatically at the end of each
	 * operation but experience shows that the behavior is buggy when it
	 * comes to ग_लिखोs (with LEN_OVRD). Clear it by hand in this हाल.
	 */
	अगर (subop->instrs[0].type == न_अंकD_OP_DATA_OUT_INSTR) अणु
		काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);

		ग_लिखोl_relaxed(पढ़ोl(nfc->regs + NDCR) & ~NDCR_ND_RUN,
			       nfc->regs + NDCR);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nfc_naked_रुकोrdy_exec(काष्ठा nand_chip *chip,
					  स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा marvell_nfc_op nfc_op;
	पूर्णांक ret;

	marvell_nfc_parse_inकाष्ठाions(chip, subop, &nfc_op);

	ret = marvell_nfc_रुको_op(chip, nfc_op.rdy_समयout_ms);
	cond_delay(nfc_op.rdy_delay_ns);

	वापस ret;
पूर्ण

अटल पूर्णांक marvell_nfc_पढ़ो_id_type_exec(काष्ठा nand_chip *chip,
					 स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा marvell_nfc_op nfc_op;
	पूर्णांक ret;

	marvell_nfc_parse_inकाष्ठाions(chip, subop, &nfc_op);
	nfc_op.ndcb[0] &= ~NDCB0_CMD_TYPE(TYPE_READ);
	nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_READ_ID);

	ret = marvell_nfc_prepare_cmd(chip);
	अगर (ret)
		वापस ret;

	marvell_nfc_send_cmd(chip, &nfc_op);
	ret = marvell_nfc_end_cmd(chip, NDSR_RDDREQ,
				  "RDDREQ while reading ID");
	अगर (ret)
		वापस ret;

	cond_delay(nfc_op.cle_ale_delay_ns);

	अगर (nfc_op.rdy_समयout_ms) अणु
		ret = marvell_nfc_रुको_op(chip, nfc_op.rdy_समयout_ms);
		अगर (ret)
			वापस ret;
	पूर्ण

	cond_delay(nfc_op.rdy_delay_ns);

	marvell_nfc_xfer_data_pio(chip, subop, &nfc_op);
	ret = marvell_nfc_रुको_cmdd(chip);
	अगर (ret)
		वापस ret;

	cond_delay(nfc_op.data_delay_ns);

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nfc_पढ़ो_status_exec(काष्ठा nand_chip *chip,
					स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा marvell_nfc_op nfc_op;
	पूर्णांक ret;

	marvell_nfc_parse_inकाष्ठाions(chip, subop, &nfc_op);
	nfc_op.ndcb[0] &= ~NDCB0_CMD_TYPE(TYPE_READ);
	nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_STATUS);

	ret = marvell_nfc_prepare_cmd(chip);
	अगर (ret)
		वापस ret;

	marvell_nfc_send_cmd(chip, &nfc_op);
	ret = marvell_nfc_end_cmd(chip, NDSR_RDDREQ,
				  "RDDREQ while reading status");
	अगर (ret)
		वापस ret;

	cond_delay(nfc_op.cle_ale_delay_ns);

	अगर (nfc_op.rdy_समयout_ms) अणु
		ret = marvell_nfc_रुको_op(chip, nfc_op.rdy_समयout_ms);
		अगर (ret)
			वापस ret;
	पूर्ण

	cond_delay(nfc_op.rdy_delay_ns);

	marvell_nfc_xfer_data_pio(chip, subop, &nfc_op);
	ret = marvell_nfc_रुको_cmdd(chip);
	अगर (ret)
		वापस ret;

	cond_delay(nfc_op.data_delay_ns);

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nfc_reset_cmd_type_exec(काष्ठा nand_chip *chip,
					   स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा marvell_nfc_op nfc_op;
	पूर्णांक ret;

	marvell_nfc_parse_inकाष्ठाions(chip, subop, &nfc_op);
	nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_RESET);

	ret = marvell_nfc_prepare_cmd(chip);
	अगर (ret)
		वापस ret;

	marvell_nfc_send_cmd(chip, &nfc_op);
	ret = marvell_nfc_रुको_cmdd(chip);
	अगर (ret)
		वापस ret;

	cond_delay(nfc_op.cle_ale_delay_ns);

	ret = marvell_nfc_रुको_op(chip, nfc_op.rdy_समयout_ms);
	अगर (ret)
		वापस ret;

	cond_delay(nfc_op.rdy_delay_ns);

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nfc_erase_cmd_type_exec(काष्ठा nand_chip *chip,
					   स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा marvell_nfc_op nfc_op;
	पूर्णांक ret;

	marvell_nfc_parse_inकाष्ठाions(chip, subop, &nfc_op);
	nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_ERASE);

	ret = marvell_nfc_prepare_cmd(chip);
	अगर (ret)
		वापस ret;

	marvell_nfc_send_cmd(chip, &nfc_op);
	ret = marvell_nfc_रुको_cmdd(chip);
	अगर (ret)
		वापस ret;

	cond_delay(nfc_op.cle_ale_delay_ns);

	ret = marvell_nfc_रुको_op(chip, nfc_op.rdy_समयout_ms);
	अगर (ret)
		वापस ret;

	cond_delay(nfc_op.rdy_delay_ns);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_op_parser marvell_nfcv2_op_parser = न_अंकD_OP_PARSER(
	/* Monolithic पढ़ोs/ग_लिखोs */
	न_अंकD_OP_PARSER_PATTERN(
		marvell_nfc_monolithic_access_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(true, MAX_ADDRESS_CYC_NFCV2),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(true),
		न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(false, MAX_CHUNK_SIZE)),
	न_अंकD_OP_PARSER_PATTERN(
		marvell_nfc_monolithic_access_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(false, MAX_ADDRESS_CYC_NFCV2),
		न_अंकD_OP_PARSER_PAT_DATA_OUT_ELEM(false, MAX_CHUNK_SIZE),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(true),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(true)),
	/* Naked commands */
	न_अंकD_OP_PARSER_PATTERN(
		marvell_nfc_naked_access_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false)),
	न_अंकD_OP_PARSER_PATTERN(
		marvell_nfc_naked_access_exec,
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(false, MAX_ADDRESS_CYC_NFCV2)),
	न_अंकD_OP_PARSER_PATTERN(
		marvell_nfc_naked_access_exec,
		न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(false, MAX_CHUNK_SIZE)),
	न_अंकD_OP_PARSER_PATTERN(
		marvell_nfc_naked_access_exec,
		न_अंकD_OP_PARSER_PAT_DATA_OUT_ELEM(false, MAX_CHUNK_SIZE)),
	न_अंकD_OP_PARSER_PATTERN(
		marvell_nfc_naked_रुकोrdy_exec,
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(false)),
	);

अटल स्थिर काष्ठा nand_op_parser marvell_nfcv1_op_parser = न_अंकD_OP_PARSER(
	/* Naked commands not supported, use a function क्रम each pattern */
	न_अंकD_OP_PARSER_PATTERN(
		marvell_nfc_पढ़ो_id_type_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(false, MAX_ADDRESS_CYC_NFCV1),
		न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(false, 8)),
	न_अंकD_OP_PARSER_PATTERN(
		marvell_nfc_erase_cmd_type_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(false, MAX_ADDRESS_CYC_NFCV1),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(false)),
	न_अंकD_OP_PARSER_PATTERN(
		marvell_nfc_पढ़ो_status_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(false, 1)),
	न_अंकD_OP_PARSER_PATTERN(
		marvell_nfc_reset_cmd_type_exec,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(false)),
	न_अंकD_OP_PARSER_PATTERN(
		marvell_nfc_naked_रुकोrdy_exec,
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(false)),
	);

अटल पूर्णांक marvell_nfc_exec_op(काष्ठा nand_chip *chip,
			       स्थिर काष्ठा nand_operation *op,
			       bool check_only)
अणु
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);

	अगर (!check_only)
		marvell_nfc_select_target(chip, op->cs);

	अगर (nfc->caps->is_nfcv2)
		वापस nand_op_parser_exec_op(chip, &marvell_nfcv2_op_parser,
					      op, check_only);
	अन्यथा
		वापस nand_op_parser_exec_op(chip, &marvell_nfcv1_op_parser,
					      op, check_only);
पूर्ण

/*
 * Layouts were broken in old pxa3xx_nand driver, these are supposed to be
 * usable.
 */
अटल पूर्णांक marvell_nand_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				      काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	स्थिर काष्ठा marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;

	अगर (section)
		वापस -दुस्फल;

	oobregion->length = (lt->full_chunk_cnt * lt->ecc_bytes) +
			    lt->last_ecc_bytes;
	oobregion->offset = mtd->oobsize - oobregion->length;

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nand_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				       काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	स्थिर काष्ठा marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;

	अगर (section)
		वापस -दुस्फल;

	/*
	 * Bootrom looks in bytes 0 & 5 क्रम bad blocks क्रम the
	 * 4KB page / 4bit BCH combination.
	 */
	अगर (mtd->ग_लिखोsize == SZ_4K && lt->data_bytes == SZ_2K)
		oobregion->offset = 6;
	अन्यथा
		oobregion->offset = 2;

	oobregion->length = (lt->full_chunk_cnt * lt->spare_bytes) +
			    lt->last_spare_bytes - oobregion->offset;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops marvell_nand_ooblayout_ops = अणु
	.ecc = marvell_nand_ooblayout_ecc,
	.मुक्त = marvell_nand_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक marvell_nand_hw_ecc_controller_init(काष्ठा mtd_info *mtd,
					       काष्ठा nand_ecc_ctrl *ecc)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	स्थिर काष्ठा marvell_hw_ecc_layout *l;
	पूर्णांक i;

	अगर (!nfc->caps->is_nfcv2 &&
	    (mtd->ग_लिखोsize + mtd->oobsize > MAX_CHUNK_SIZE)) अणु
		dev_err(nfc->dev,
			"NFCv1: writesize (%d) cannot be bigger than a chunk (%d)\n",
			mtd->ग_लिखोsize, MAX_CHUNK_SIZE - mtd->oobsize);
		वापस -ENOTSUPP;
	पूर्ण

	to_marvell_nand(chip)->layout = शून्य;
	क्रम (i = 0; i < ARRAY_SIZE(marvell_nfc_layouts); i++) अणु
		l = &marvell_nfc_layouts[i];
		अगर (mtd->ग_लिखोsize == l->ग_लिखोsize &&
		    ecc->size == l->chunk && ecc->strength == l->strength) अणु
			to_marvell_nand(chip)->layout = l;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!to_marvell_nand(chip)->layout ||
	    (!nfc->caps->is_nfcv2 && ecc->strength > 1)) अणु
		dev_err(nfc->dev,
			"ECC strength %d at page size %d is not supported\n",
			ecc->strength, mtd->ग_लिखोsize);
		वापस -ENOTSUPP;
	पूर्ण

	/* Special care क्रम the layout 2k/8-bit/512B  */
	अगर (l->ग_लिखोsize == 2048 && l->strength == 8) अणु
		अगर (mtd->oobsize < 128) अणु
			dev_err(nfc->dev, "Requested layout needs at least 128 OOB bytes\n");
			वापस -ENOTSUPP;
		पूर्ण अन्यथा अणु
			chip->bbt_options |= न_अंकD_BBT_NO_OOB_BBM;
		पूर्ण
	पूर्ण

	mtd_set_ooblayout(mtd, &marvell_nand_ooblayout_ops);
	ecc->steps = l->nchunks;
	ecc->size = l->data_bytes;

	अगर (ecc->strength == 1) अणु
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;
		ecc->पढ़ो_page_raw = marvell_nfc_hw_ecc_hmg_पढ़ो_page_raw;
		ecc->पढ़ो_page = marvell_nfc_hw_ecc_hmg_पढ़ो_page;
		ecc->पढ़ो_oob_raw = marvell_nfc_hw_ecc_hmg_पढ़ो_oob_raw;
		ecc->पढ़ो_oob = ecc->पढ़ो_oob_raw;
		ecc->ग_लिखो_page_raw = marvell_nfc_hw_ecc_hmg_ग_लिखो_page_raw;
		ecc->ग_लिखो_page = marvell_nfc_hw_ecc_hmg_ग_लिखो_page;
		ecc->ग_लिखो_oob_raw = marvell_nfc_hw_ecc_hmg_ग_लिखो_oob_raw;
		ecc->ग_लिखो_oob = ecc->ग_लिखो_oob_raw;
	पूर्ण अन्यथा अणु
		chip->ecc.algo = न_अंकD_ECC_ALGO_BCH;
		ecc->strength = 16;
		ecc->पढ़ो_page_raw = marvell_nfc_hw_ecc_bch_पढ़ो_page_raw;
		ecc->पढ़ो_page = marvell_nfc_hw_ecc_bch_पढ़ो_page;
		ecc->पढ़ो_oob_raw = marvell_nfc_hw_ecc_bch_पढ़ो_oob_raw;
		ecc->पढ़ो_oob = marvell_nfc_hw_ecc_bch_पढ़ो_oob;
		ecc->ग_लिखो_page_raw = marvell_nfc_hw_ecc_bch_ग_लिखो_page_raw;
		ecc->ग_लिखो_page = marvell_nfc_hw_ecc_bch_ग_लिखो_page;
		ecc->ग_लिखो_oob_raw = marvell_nfc_hw_ecc_bch_ग_लिखो_oob_raw;
		ecc->ग_लिखो_oob = marvell_nfc_hw_ecc_bch_ग_लिखो_oob;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nand_ecc_init(काष्ठा mtd_info *mtd,
				 काष्ठा nand_ecc_ctrl *ecc)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	स्थिर काष्ठा nand_ecc_props *requirements =
		nanddev_get_ecc_requirements(&chip->base);
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	पूर्णांक ret;

	अगर (ecc->engine_type != न_अंकD_ECC_ENGINE_TYPE_NONE &&
	    (!ecc->size || !ecc->strength)) अणु
		अगर (requirements->step_size && requirements->strength) अणु
			ecc->size = requirements->step_size;
			ecc->strength = requirements->strength;
		पूर्ण अन्यथा अणु
			dev_info(nfc->dev,
				 "No minimum ECC strength, using 1b/512B\n");
			ecc->size = 512;
			ecc->strength = 1;
		पूर्ण
	पूर्ण

	चयन (ecc->engine_type) अणु
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		ret = marvell_nand_hw_ecc_controller_init(mtd, ecc);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल न_अंकD_ECC_ENGINE_TYPE_NONE:
	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
	हाल न_अंकD_ECC_ENGINE_TYPE_ON_DIE:
		अगर (!nfc->caps->is_nfcv2 && mtd->ग_लिखोsize != SZ_512 &&
		    mtd->ग_लिखोsize != SZ_2K) अणु
			dev_err(nfc->dev, "NFCv1 cannot write %d bytes pages\n",
				mtd->ग_लिखोsize);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 bbt_pattern[] = अणु'M', 'V', 'B', 'b', 't', '0' पूर्ण;
अटल u8 bbt_mirror_pattern[] = अणु'1', 't', 'b', 'B', 'V', 'M' पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_मुख्य_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE |
		   न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION,
	.offs =	8,
	.len = 6,
	.veroffs = 14,
	.maxblocks = 8,	/* Last 8 blocks in each chip */
	.pattern = bbt_pattern
पूर्ण;

अटल काष्ठा nand_bbt_descr bbt_mirror_descr = अणु
	.options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_CREATE | न_अंकD_BBT_WRITE |
		   न_अंकD_BBT_2BIT | न_अंकD_BBT_VERSION,
	.offs =	8,
	.len = 6,
	.veroffs = 14,
	.maxblocks = 8,	/* Last 8 blocks in each chip */
	.pattern = bbt_mirror_pattern
पूर्ण;

अटल पूर्णांक marvell_nfc_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक chipnr,
				       स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	अचिन्हित पूर्णांक period_ns = 1000000000 / clk_get_rate(nfc->core_clk) * 2;
	स्थिर काष्ठा nand_sdr_timings *sdr;
	काष्ठा marvell_nfc_timings nfc_पंचांगg;
	पूर्णांक पढ़ो_delay;

	sdr = nand_get_sdr_timings(conf);
	अगर (IS_ERR(sdr))
		वापस PTR_ERR(sdr);

	/*
	 * SDR timings are given in pico-seconds जबतक NFC timings must be
	 * expressed in न_अंकD controller घड़ी cycles, which is half of the
	 * frequency of the accessible ECC घड़ी retrieved by clk_get_rate().
	 * This is not written anywhere in the datasheet but was observed
	 * with an oscilloscope.
	 *
	 * NFC datasheet gives equations from which thoses calculations
	 * are derived, they tend to be slightly more restrictives than the
	 * given core timings and may improve the overall speed.
	 */
	nfc_पंचांगg.tRP = TO_CYCLES(DIV_ROUND_UP(sdr->tRC_min, 2), period_ns) - 1;
	nfc_पंचांगg.tRH = nfc_पंचांगg.tRP;
	nfc_पंचांगg.tWP = TO_CYCLES(DIV_ROUND_UP(sdr->tWC_min, 2), period_ns) - 1;
	nfc_पंचांगg.tWH = nfc_पंचांगg.tWP;
	nfc_पंचांगg.tCS = TO_CYCLES(sdr->tCS_min, period_ns);
	nfc_पंचांगg.tCH = TO_CYCLES(sdr->tCH_min, period_ns) - 1;
	nfc_पंचांगg.tADL = TO_CYCLES(sdr->tADL_min, period_ns);
	/*
	 * Read delay is the समय of propagation from SoC pins to NFC पूर्णांकernal
	 * logic. With non-EDO timings, this is MIN_RD_DEL_CNT घड़ी cycles. In
	 * EDO mode, an additional delay of tRH must be taken पूर्णांकo account so
	 * the data is sampled on the falling edge instead of the rising edge.
	 */
	पढ़ो_delay = sdr->tRC_min >= 30000 ?
		MIN_RD_DEL_CNT : MIN_RD_DEL_CNT + nfc_पंचांगg.tRH;

	nfc_पंचांगg.tAR = TO_CYCLES(sdr->tAR_min, period_ns);
	/*
	 * tWHR and tRHW are supposed to be पढ़ो to ग_लिखो delays (and vice
	 * versa) but in some हालs, ie. when करोing a change column, they must
	 * be greater than that to be sure tCCS delay is respected.
	 */
	nfc_पंचांगg.tWHR = TO_CYCLES(max_t(पूर्णांक, sdr->tWHR_min, sdr->tCCS_min),
				 period_ns) - 2;
	nfc_पंचांगg.tRHW = TO_CYCLES(max_t(पूर्णांक, sdr->tRHW_min, sdr->tCCS_min),
				 period_ns);

	/*
	 * NFCv2: Use WAIT_MODE (रुको क्रम RB line), करो not rely only on delays.
	 * NFCv1: No WAIT_MODE, tR must be maximal.
	 */
	अगर (nfc->caps->is_nfcv2) अणु
		nfc_पंचांगg.tR = TO_CYCLES(sdr->tWB_max, period_ns);
	पूर्ण अन्यथा अणु
		nfc_पंचांगg.tR = TO_CYCLES64(sdr->tWB_max + sdr->tR_max,
					 period_ns);
		अगर (nfc_पंचांगg.tR + 3 > nfc_पंचांगg.tCH)
			nfc_पंचांगg.tR = nfc_पंचांगg.tCH - 3;
		अन्यथा
			nfc_पंचांगg.tR = 0;
	पूर्ण

	अगर (chipnr < 0)
		वापस 0;

	marvell_nand->ndtr0 =
		NDTR0_TRP(nfc_पंचांगg.tRP) |
		NDTR0_TRH(nfc_पंचांगg.tRH) |
		NDTR0_ETRP(nfc_पंचांगg.tRP) |
		NDTR0_TWP(nfc_पंचांगg.tWP) |
		NDTR0_TWH(nfc_पंचांगg.tWH) |
		NDTR0_TCS(nfc_पंचांगg.tCS) |
		NDTR0_TCH(nfc_पंचांगg.tCH);

	marvell_nand->ndtr1 =
		NDTR1_TAR(nfc_पंचांगg.tAR) |
		NDTR1_TWHR(nfc_पंचांगg.tWHR) |
		NDTR1_TR(nfc_पंचांगg.tR);

	अगर (nfc->caps->is_nfcv2) अणु
		marvell_nand->ndtr0 |=
			NDTR0_RD_CNT_DEL(पढ़ो_delay) |
			NDTR0_SELCNTR |
			NDTR0_TADL(nfc_पंचांगg.tADL);

		marvell_nand->ndtr1 |=
			NDTR1_TRHW(nfc_पंचांगg.tRHW) |
			NDTR1_WAIT_MODE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	काष्ठा marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	काष्ठा pxa3xx_nand_platक्रमm_data *pdata = dev_get_platdata(nfc->dev);
	पूर्णांक ret;

	अगर (pdata && pdata->flash_bbt)
		chip->bbt_options |= न_अंकD_BBT_USE_FLASH;

	अगर (chip->bbt_options & न_अंकD_BBT_USE_FLASH) अणु
		/*
		 * We'll use a bad block table stored in-flash and don't
		 * allow writing the bad block marker to the flash.
		 */
		chip->bbt_options |= न_अंकD_BBT_NO_OOB_BBM;
		chip->bbt_td = &bbt_मुख्य_descr;
		chip->bbt_md = &bbt_mirror_descr;
	पूर्ण

	/* Save the chip-specअगरic fields of NDCR */
	marvell_nand->ndcr = NDCR_PAGE_SZ(mtd->ग_लिखोsize);
	अगर (chip->options & न_अंकD_BUSWIDTH_16)
		marvell_nand->ndcr |= NDCR_DWIDTH_M | NDCR_DWIDTH_C;

	/*
	 * On small page न_अंकDs, only one cycle is needed to pass the
	 * column address.
	 */
	अगर (mtd->ग_लिखोsize <= 512) अणु
		marvell_nand->addr_cyc = 1;
	पूर्ण अन्यथा अणु
		marvell_nand->addr_cyc = 2;
		marvell_nand->ndcr |= NDCR_RA_START;
	पूर्ण

	/*
	 * Now add the number of cycles needed to pass the row
	 * address.
	 *
	 * Addressing a chip using CS 2 or 3 should also need the third row
	 * cycle but due to inconsistance in the करोcumentation and lack of
	 * hardware to test this situation, this हाल is not supported.
	 */
	अगर (chip->options & न_अंकD_ROW_ADDR_3)
		marvell_nand->addr_cyc += 3;
	अन्यथा
		marvell_nand->addr_cyc += 2;

	अगर (pdata) अणु
		chip->ecc.size = pdata->ecc_step_size;
		chip->ecc.strength = pdata->ecc_strength;
	पूर्ण

	ret = marvell_nand_ecc_init(mtd, &chip->ecc);
	अगर (ret) अणु
		dev_err(nfc->dev, "ECC init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (chip->ecc.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_HOST) अणु
		/*
		 * Subpage ग_लिखो not available with hardware ECC, prohibit also
		 * subpage पढ़ो as in userspace subpage access would still be
		 * allowed and subpage ग_लिखो, अगर used, would lead to numerous
		 * uncorrectable ECC errors.
		 */
		chip->options |= न_अंकD_NO_SUBPAGE_WRITE;
	पूर्ण

	अगर (pdata || nfc->caps->legacy_of_bindings) अणु
		/*
		 * We keep the MTD name unchanged to aव्योम अवरोधing platक्रमms
		 * where the MTD cmdline parser is used and the bootloader
		 * has not been updated to use the new naming scheme.
		 */
		mtd->name = "pxa3xx_nand-0";
	पूर्ण अन्यथा अगर (!mtd->name) अणु
		/*
		 * If the new bindings are used and the bootloader has not been
		 * updated to pass a new mtdparts parameter on the cmdline, you
		 * should define the following property in your न_अंकD node, ie:
		 *
		 *	label = "main-storage";
		 *
		 * This way, mtd->name will be set by the core when
		 * nand_set_flash_node() is called.
		 */
		mtd->name = devm_kaप्र_लिखो(nfc->dev, GFP_KERNEL,
					   "%s:nand.%d", dev_name(nfc->dev),
					   marvell_nand->sels[0].cs);
		अगर (!mtd->name) अणु
			dev_err(nfc->dev, "Failed to allocate mtd->name\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops marvell_nand_controller_ops = अणु
	.attach_chip = marvell_nand_attach_chip,
	.exec_op = marvell_nfc_exec_op,
	.setup_पूर्णांकerface = marvell_nfc_setup_पूर्णांकerface,
पूर्ण;

अटल पूर्णांक marvell_nand_chip_init(काष्ठा device *dev, काष्ठा marvell_nfc *nfc,
				  काष्ठा device_node *np)
अणु
	काष्ठा pxa3xx_nand_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा marvell_nand_chip *marvell_nand;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *chip;
	पूर्णांक nsels, ret, i;
	u32 cs, rb;

	/*
	 * The legacy "num-cs" property indicates the number of CS on the only
	 * chip connected to the controller (legacy bindings करोes not support
	 * more than one chip). The CS and RB pins are always the #0.
	 *
	 * When not using legacy bindings, a couple of "reg" and "nand-rb"
	 * properties must be filled. For each chip, expressed as a subnode,
	 * "reg" poपूर्णांकs to the CS lines and "nand-rb" to the RB line.
	 */
	अगर (pdata || nfc->caps->legacy_of_bindings) अणु
		nsels = 1;
	पूर्ण अन्यथा अणु
		nsels = of_property_count_elems_of_size(np, "reg", माप(u32));
		अगर (nsels <= 0) अणु
			dev_err(dev, "missing/invalid reg property\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Alloc the nand chip काष्ठाure */
	marvell_nand = devm_kzalloc(dev,
				    काष्ठा_size(marvell_nand, sels, nsels),
				    GFP_KERNEL);
	अगर (!marvell_nand) अणु
		dev_err(dev, "could not allocate chip structure\n");
		वापस -ENOMEM;
	पूर्ण

	marvell_nand->nsels = nsels;
	marvell_nand->selected_die = -1;

	क्रम (i = 0; i < nsels; i++) अणु
		अगर (pdata || nfc->caps->legacy_of_bindings) अणु
			/*
			 * Legacy bindings use the CS lines in natural
			 * order (0, 1, ...)
			 */
			cs = i;
		पूर्ण अन्यथा अणु
			/* Retrieve CS id */
			ret = of_property_पढ़ो_u32_index(np, "reg", i, &cs);
			अगर (ret) अणु
				dev_err(dev, "could not retrieve reg property: %d\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण

		अगर (cs >= nfc->caps->max_cs_nb) अणु
			dev_err(dev, "invalid reg value: %u (max CS = %d)\n",
				cs, nfc->caps->max_cs_nb);
			वापस -EINVAL;
		पूर्ण

		अगर (test_and_set_bit(cs, &nfc->asचिन्हित_cs)) अणु
			dev_err(dev, "CS %d already assigned\n", cs);
			वापस -EINVAL;
		पूर्ण

		/*
		 * The cs variable represents the chip select id, which must be
		 * converted in bit fields क्रम NDCB0 and NDCB2 to select the
		 * right chip. Unक्रमtunately, due to a lack of inक्रमmation on
		 * the subject and incoherent करोcumentation, the user should not
		 * use CS1 and CS3 at all as निश्चितing them is not supported in
		 * a reliable way (due to multiplexing inside ADDR5 field).
		 */
		marvell_nand->sels[i].cs = cs;
		चयन (cs) अणु
		हाल 0:
		हाल 2:
			marvell_nand->sels[i].ndcb0_csel = 0;
			अवरोध;
		हाल 1:
		हाल 3:
			marvell_nand->sels[i].ndcb0_csel = NDCB0_CSEL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		/* Retrieve RB id */
		अगर (pdata || nfc->caps->legacy_of_bindings) अणु
			/* Legacy bindings always use RB #0 */
			rb = 0;
		पूर्ण अन्यथा अणु
			ret = of_property_पढ़ो_u32_index(np, "nand-rb", i,
							 &rb);
			अगर (ret) अणु
				dev_err(dev,
					"could not retrieve RB property: %d\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण

		अगर (rb >= nfc->caps->max_rb_nb) अणु
			dev_err(dev, "invalid reg value: %u (max RB = %d)\n",
				rb, nfc->caps->max_rb_nb);
			वापस -EINVAL;
		पूर्ण

		marvell_nand->sels[i].rb = rb;
	पूर्ण

	chip = &marvell_nand->chip;
	chip->controller = &nfc->controller;
	nand_set_flash_node(chip, np);

	अगर (!of_property_पढ़ो_bool(np, "marvell,nand-keep-config"))
		chip->options |= न_अंकD_KEEP_TIMINGS;

	mtd = nand_to_mtd(chip);
	mtd->dev.parent = dev;

	/*
	 * Save a reference value क्रम timing रेजिस्टरs beक्रमe
	 * ->setup_पूर्णांकerface() is called.
	 */
	marvell_nand->ndtr0 = पढ़ोl_relaxed(nfc->regs + NDTR0);
	marvell_nand->ndtr1 = पढ़ोl_relaxed(nfc->regs + NDTR1);

	chip->options |= न_अंकD_BUSWIDTH_AUTO;

	ret = nand_scan(chip, marvell_nand->nsels);
	अगर (ret) अणु
		dev_err(dev, "could not scan the nand chip\n");
		वापस ret;
	पूर्ण

	अगर (pdata)
		/* Legacy bindings support only one chip */
		ret = mtd_device_रेजिस्टर(mtd, pdata->parts, pdata->nr_parts);
	अन्यथा
		ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret) अणु
		dev_err(dev, "failed to register mtd device: %d\n", ret);
		nand_cleanup(chip);
		वापस ret;
	पूर्ण

	list_add_tail(&marvell_nand->node, &nfc->chips);

	वापस 0;
पूर्ण

अटल व्योम marvell_nand_chips_cleanup(काष्ठा marvell_nfc *nfc)
अणु
	काष्ठा marvell_nand_chip *entry, *temp;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(entry, temp, &nfc->chips, node) अणु
		chip = &entry->chip;
		ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
		WARN_ON(ret);
		nand_cleanup(chip);
		list_del(&entry->node);
	पूर्ण
पूर्ण

अटल पूर्णांक marvell_nand_chips_init(काष्ठा device *dev, काष्ठा marvell_nfc *nfc)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *nand_np;
	पूर्णांक max_cs = nfc->caps->max_cs_nb;
	पूर्णांक nchips;
	पूर्णांक ret;

	अगर (!np)
		nchips = 1;
	अन्यथा
		nchips = of_get_child_count(np);

	अगर (nchips > max_cs) अणु
		dev_err(dev, "too many NAND chips: %d (max = %d CS)\n", nchips,
			max_cs);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Legacy bindings करो not use child nodes to exhibit न_अंकD chip
	 * properties and layout. Instead, न_अंकD properties are mixed with the
	 * controller ones, and partitions are defined as direct subnodes of the
	 * न_अंकD controller node.
	 */
	अगर (nfc->caps->legacy_of_bindings) अणु
		ret = marvell_nand_chip_init(dev, nfc, np);
		वापस ret;
	पूर्ण

	क्रम_each_child_of_node(np, nand_np) अणु
		ret = marvell_nand_chip_init(dev, nfc, nand_np);
		अगर (ret) अणु
			of_node_put(nand_np);
			जाओ cleanup_chips;
		पूर्ण
	पूर्ण

	वापस 0;

cleanup_chips:
	marvell_nand_chips_cleanup(nfc);

	वापस ret;
पूर्ण

अटल पूर्णांक marvell_nfc_init_dma(काष्ठा marvell_nfc *nfc)
अणु
	काष्ठा platक्रमm_device *pdev = container_of(nfc->dev,
						    काष्ठा platक्रमm_device,
						    dev);
	काष्ठा dma_slave_config config = अणुपूर्ण;
	काष्ठा resource *r;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_PXA_DMA)) अणु
		dev_warn(nfc->dev,
			 "DMA not enabled in configuration\n");
		वापस -ENOTSUPP;
	पूर्ण

	ret = dma_set_mask_and_coherent(nfc->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	nfc->dma_chan =	dma_request_chan(nfc->dev, "data");
	अगर (IS_ERR(nfc->dma_chan)) अणु
		ret = PTR_ERR(nfc->dma_chan);
		nfc->dma_chan = शून्य;
		वापस dev_err_probe(nfc->dev, ret, "DMA channel request failed\n");
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		ret = -ENXIO;
		जाओ release_channel;
	पूर्ण

	config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	config.src_addr = r->start + NDDB;
	config.dst_addr = r->start + NDDB;
	config.src_maxburst = 32;
	config.dst_maxburst = 32;
	ret = dmaengine_slave_config(nfc->dma_chan, &config);
	अगर (ret < 0) अणु
		dev_err(nfc->dev, "Failed to configure DMA channel\n");
		जाओ release_channel;
	पूर्ण

	/*
	 * DMA must act on length multiple of 32 and this length may be
	 * bigger than the destination buffer. Use this buffer instead
	 * क्रम DMA transfers and then copy the desired amount of data to
	 * the provided buffer.
	 */
	nfc->dma_buf = kदो_स्मृति(MAX_CHUNK_SIZE, GFP_KERNEL | GFP_DMA);
	अगर (!nfc->dma_buf) अणु
		ret = -ENOMEM;
		जाओ release_channel;
	पूर्ण

	nfc->use_dma = true;

	वापस 0;

release_channel:
	dma_release_channel(nfc->dma_chan);
	nfc->dma_chan = शून्य;

	वापस ret;
पूर्ण

अटल व्योम marvell_nfc_reset(काष्ठा marvell_nfc *nfc)
अणु
	/*
	 * ECC operations and पूर्णांकerruptions are only enabled when specअगरically
	 * needed. ECC shall not be activated in the early stages (fails probe).
	 * Arbiter flag, even अगर marked as "reserved", must be set (empirical).
	 * SPARE_EN bit must always be set or ECC bytes will not be at the same
	 * offset in the पढ़ो page and this will fail the protection.
	 */
	ग_लिखोl_relaxed(NDCR_ALL_INT | NDCR_ND_ARB_EN | NDCR_SPARE_EN |
		       NDCR_RD_ID_CNT(NFCV1_READID_LEN), nfc->regs + NDCR);
	ग_लिखोl_relaxed(0xFFFFFFFF, nfc->regs + NDSR);
	ग_लिखोl_relaxed(0, nfc->regs + NDECCCTRL);
पूर्ण

अटल पूर्णांक marvell_nfc_init(काष्ठा marvell_nfc *nfc)
अणु
	काष्ठा device_node *np = nfc->dev->of_node;

	/*
	 * Some SoCs like A7k/A8k need to enable manually the न_अंकD
	 * controller, gated घड़ीs and reset bits to aव्योम being bootloader
	 * dependent. This is करोne through the use of the System Functions
	 * रेजिस्टरs.
	 */
	अगर (nfc->caps->need_प्रणाली_controller) अणु
		काष्ठा regmap *sysctrl_base =
			syscon_regmap_lookup_by_phandle(np,
							"marvell,system-controller");

		अगर (IS_ERR(sysctrl_base))
			वापस PTR_ERR(sysctrl_base);

		regmap_ग_लिखो(sysctrl_base, GENCONF_SOC_DEVICE_MUX,
			     GENCONF_SOC_DEVICE_MUX_NFC_EN |
			     GENCONF_SOC_DEVICE_MUX_ECC_CLK_RST |
			     GENCONF_SOC_DEVICE_MUX_ECC_CORE_RST |
			     GENCONF_SOC_DEVICE_MUX_NFC_INT_EN);

		regmap_update_bits(sysctrl_base, GENCONF_CLK_GATING_CTRL,
				   GENCONF_CLK_GATING_CTRL_ND_GATE,
				   GENCONF_CLK_GATING_CTRL_ND_GATE);

		regmap_update_bits(sysctrl_base, GENCONF_ND_CLK_CTRL,
				   GENCONF_ND_CLK_CTRL_EN,
				   GENCONF_ND_CLK_CTRL_EN);
	पूर्ण

	/* Configure the DMA अगर appropriate */
	अगर (!nfc->caps->is_nfcv2)
		marvell_nfc_init_dma(nfc);

	marvell_nfc_reset(nfc);

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_nfc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा marvell_nfc *nfc;
	पूर्णांक ret;
	पूर्णांक irq;

	nfc = devm_kzalloc(&pdev->dev, माप(काष्ठा marvell_nfc),
			   GFP_KERNEL);
	अगर (!nfc)
		वापस -ENOMEM;

	nfc->dev = dev;
	nand_controller_init(&nfc->controller);
	nfc->controller.ops = &marvell_nand_controller_ops;
	INIT_LIST_HEAD(&nfc->chips);

	nfc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(nfc->regs))
		वापस PTR_ERR(nfc->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	nfc->core_clk = devm_clk_get(&pdev->dev, "core");

	/* Managed the legacy हाल (when the first घड़ी was not named) */
	अगर (nfc->core_clk == ERR_PTR(-ENOENT))
		nfc->core_clk = devm_clk_get(&pdev->dev, शून्य);

	अगर (IS_ERR(nfc->core_clk))
		वापस PTR_ERR(nfc->core_clk);

	ret = clk_prepare_enable(nfc->core_clk);
	अगर (ret)
		वापस ret;

	nfc->reg_clk = devm_clk_get(&pdev->dev, "reg");
	अगर (IS_ERR(nfc->reg_clk)) अणु
		अगर (PTR_ERR(nfc->reg_clk) != -ENOENT) अणु
			ret = PTR_ERR(nfc->reg_clk);
			जाओ unprepare_core_clk;
		पूर्ण

		nfc->reg_clk = शून्य;
	पूर्ण

	ret = clk_prepare_enable(nfc->reg_clk);
	अगर (ret)
		जाओ unprepare_core_clk;

	marvell_nfc_disable_पूर्णांक(nfc, NDCR_ALL_INT);
	marvell_nfc_clear_पूर्णांक(nfc, NDCR_ALL_INT);
	ret = devm_request_irq(dev, irq, marvell_nfc_isr,
			       0, "marvell-nfc", nfc);
	अगर (ret)
		जाओ unprepare_reg_clk;

	/* Get न_अंकD controller capabilities */
	अगर (pdev->id_entry)
		nfc->caps = (व्योम *)pdev->id_entry->driver_data;
	अन्यथा
		nfc->caps = of_device_get_match_data(&pdev->dev);

	अगर (!nfc->caps) अणु
		dev_err(dev, "Could not retrieve NFC caps\n");
		ret = -EINVAL;
		जाओ unprepare_reg_clk;
	पूर्ण

	/* Init the controller and then probe the chips */
	ret = marvell_nfc_init(nfc);
	अगर (ret)
		जाओ unprepare_reg_clk;

	platक्रमm_set_drvdata(pdev, nfc);

	ret = marvell_nand_chips_init(dev, nfc);
	अगर (ret)
		जाओ release_dma;

	वापस 0;

release_dma:
	अगर (nfc->use_dma)
		dma_release_channel(nfc->dma_chan);
unprepare_reg_clk:
	clk_disable_unprepare(nfc->reg_clk);
unprepare_core_clk:
	clk_disable_unprepare(nfc->core_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक marvell_nfc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा marvell_nfc *nfc = platक्रमm_get_drvdata(pdev);

	marvell_nand_chips_cleanup(nfc);

	अगर (nfc->use_dma) अणु
		dmaengine_terminate_all(nfc->dma_chan);
		dma_release_channel(nfc->dma_chan);
	पूर्ण

	clk_disable_unprepare(nfc->reg_clk);
	clk_disable_unprepare(nfc->core_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused marvell_nfc_suspend(काष्ठा device *dev)
अणु
	काष्ठा marvell_nfc *nfc = dev_get_drvdata(dev);
	काष्ठा marvell_nand_chip *chip;

	list_क्रम_each_entry(chip, &nfc->chips, node)
		marvell_nfc_रुको_ndrun(&chip->chip);

	clk_disable_unprepare(nfc->reg_clk);
	clk_disable_unprepare(nfc->core_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused marvell_nfc_resume(काष्ठा device *dev)
अणु
	काष्ठा marvell_nfc *nfc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(nfc->core_clk);
	अगर (ret < 0)
		वापस ret;

	ret = clk_prepare_enable(nfc->reg_clk);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Reset nfc->selected_chip so the next command will cause the timing
	 * रेजिस्टरs to be restored in marvell_nfc_select_target().
	 */
	nfc->selected_chip = शून्य;

	/* Reset रेजिस्टरs that have lost their contents */
	marvell_nfc_reset(nfc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops marvell_nfc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(marvell_nfc_suspend, marvell_nfc_resume)
पूर्ण;

अटल स्थिर काष्ठा marvell_nfc_caps marvell_armada_8k_nfc_caps = अणु
	.max_cs_nb = 4,
	.max_rb_nb = 2,
	.need_प्रणाली_controller = true,
	.is_nfcv2 = true,
पूर्ण;

अटल स्थिर काष्ठा marvell_nfc_caps marvell_armada370_nfc_caps = अणु
	.max_cs_nb = 4,
	.max_rb_nb = 2,
	.is_nfcv2 = true,
पूर्ण;

अटल स्थिर काष्ठा marvell_nfc_caps marvell_pxa3xx_nfc_caps = अणु
	.max_cs_nb = 2,
	.max_rb_nb = 1,
	.use_dma = true,
पूर्ण;

अटल स्थिर काष्ठा marvell_nfc_caps marvell_armada_8k_nfc_legacy_caps = अणु
	.max_cs_nb = 4,
	.max_rb_nb = 2,
	.need_प्रणाली_controller = true,
	.legacy_of_bindings = true,
	.is_nfcv2 = true,
पूर्ण;

अटल स्थिर काष्ठा marvell_nfc_caps marvell_armada370_nfc_legacy_caps = अणु
	.max_cs_nb = 4,
	.max_rb_nb = 2,
	.legacy_of_bindings = true,
	.is_nfcv2 = true,
पूर्ण;

अटल स्थिर काष्ठा marvell_nfc_caps marvell_pxa3xx_nfc_legacy_caps = अणु
	.max_cs_nb = 2,
	.max_rb_nb = 1,
	.legacy_of_bindings = true,
	.use_dma = true,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id marvell_nfc_platक्रमm_ids[] = अणु
	अणु
		.name = "pxa3xx-nand",
		.driver_data = (kernel_uदीर्घ_t)&marvell_pxa3xx_nfc_legacy_caps,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, marvell_nfc_platक्रमm_ids);

अटल स्थिर काष्ठा of_device_id marvell_nfc_of_ids[] = अणु
	अणु
		.compatible = "marvell,armada-8k-nand-controller",
		.data = &marvell_armada_8k_nfc_caps,
	पूर्ण,
	अणु
		.compatible = "marvell,armada370-nand-controller",
		.data = &marvell_armada370_nfc_caps,
	पूर्ण,
	अणु
		.compatible = "marvell,pxa3xx-nand-controller",
		.data = &marvell_pxa3xx_nfc_caps,
	पूर्ण,
	/* Support क्रम old/deprecated bindings: */
	अणु
		.compatible = "marvell,armada-8k-nand",
		.data = &marvell_armada_8k_nfc_legacy_caps,
	पूर्ण,
	अणु
		.compatible = "marvell,armada370-nand",
		.data = &marvell_armada370_nfc_legacy_caps,
	पूर्ण,
	अणु
		.compatible = "marvell,pxa3xx-nand",
		.data = &marvell_pxa3xx_nfc_legacy_caps,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, marvell_nfc_of_ids);

अटल काष्ठा platक्रमm_driver marvell_nfc_driver = अणु
	.driver	= अणु
		.name		= "marvell-nfc",
		.of_match_table = marvell_nfc_of_ids,
		.pm		= &marvell_nfc_pm_ops,
	पूर्ण,
	.id_table = marvell_nfc_platक्रमm_ids,
	.probe = marvell_nfc_probe,
	.हटाओ	= marvell_nfc_हटाओ,
पूर्ण;
module_platक्रमm_driver(marvell_nfc_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Marvell NAND controller driver");
