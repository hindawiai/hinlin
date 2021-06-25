<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma/qcom_bam_dma.h>

/* न_अंकDc reg offsets */
#घोषणा	न_अंकD_FLASH_CMD			0x00
#घोषणा	न_अंकD_ADDR0			0x04
#घोषणा	न_अंकD_ADDR1			0x08
#घोषणा	न_अंकD_FLASH_CHIP_SELECT		0x0c
#घोषणा	न_अंकD_EXEC_CMD			0x10
#घोषणा	न_अंकD_FLASH_STATUS		0x14
#घोषणा	न_अंकD_BUFFER_STATUS		0x18
#घोषणा	न_अंकD_DEV0_CFG0			0x20
#घोषणा	न_अंकD_DEV0_CFG1			0x24
#घोषणा	न_अंकD_DEV0_ECC_CFG		0x28
#घोषणा	न_अंकD_AUTO_STATUS_EN		0x2c
#घोषणा	न_अंकD_DEV1_CFG0			0x30
#घोषणा	न_अंकD_DEV1_CFG1			0x34
#घोषणा	न_अंकD_READ_ID			0x40
#घोषणा	न_अंकD_READ_STATUS		0x44
#घोषणा	न_अंकD_DEV_CMD0			0xa0
#घोषणा	न_अंकD_DEV_CMD1			0xa4
#घोषणा	न_अंकD_DEV_CMD2			0xa8
#घोषणा	न_अंकD_DEV_CMD_VLD		0xac
#घोषणा	SFLASHC_BURST_CFG		0xe0
#घोषणा	न_अंकD_ERASED_CW_DETECT_CFG	0xe8
#घोषणा	न_अंकD_ERASED_CW_DETECT_STATUS	0xec
#घोषणा	न_अंकD_EBI2_ECC_BUF_CFG		0xf0
#घोषणा	FLASH_BUF_ACC			0x100

#घोषणा	न_अंकD_CTRL			0xf00
#घोषणा	न_अंकD_VERSION			0xf08
#घोषणा	न_अंकD_READ_LOCATION_0		0xf20
#घोषणा	न_अंकD_READ_LOCATION_1		0xf24
#घोषणा	न_अंकD_READ_LOCATION_2		0xf28
#घोषणा	न_अंकD_READ_LOCATION_3		0xf2c
#घोषणा	न_अंकD_READ_LOCATION_LAST_CW_0	0xf40
#घोषणा	न_अंकD_READ_LOCATION_LAST_CW_1	0xf44
#घोषणा	न_अंकD_READ_LOCATION_LAST_CW_2	0xf48
#घोषणा	न_अंकD_READ_LOCATION_LAST_CW_3	0xf4c

/* dummy रेजिस्टर offsets, used by ग_लिखो_reg_dma */
#घोषणा	न_अंकD_DEV_CMD1_RESTORE		0xdead
#घोषणा	न_अंकD_DEV_CMD_VLD_RESTORE	0xbeef

/* न_अंकD_FLASH_CMD bits */
#घोषणा	PAGE_ACC			BIT(4)
#घोषणा	LAST_PAGE			BIT(5)

/* न_अंकD_FLASH_CHIP_SELECT bits */
#घोषणा	न_अंकD_DEV_SEL			0
#घोषणा	DM_EN				BIT(2)

/* न_अंकD_FLASH_STATUS bits */
#घोषणा	FS_OP_ERR			BIT(4)
#घोषणा	FS_READY_BSY_N			BIT(5)
#घोषणा	FS_MPU_ERR			BIT(8)
#घोषणा	FS_DEVICE_STS_ERR		BIT(16)
#घोषणा	FS_DEVICE_WP			BIT(23)

/* न_अंकD_BUFFER_STATUS bits */
#घोषणा	BS_UNCORRECTABLE_BIT		BIT(8)
#घोषणा	BS_CORRECTABLE_ERR_MSK		0x1f

/* न_अंकD_DEVn_CFG0 bits */
#घोषणा	DISABLE_STATUS_AFTER_WRITE	4
#घोषणा	CW_PER_PAGE			6
#घोषणा	UD_SIZE_BYTES			9
#घोषणा	ECC_PARITY_SIZE_BYTES_RS	19
#घोषणा	SPARE_SIZE_BYTES		23
#घोषणा	NUM_ADDR_CYCLES			27
#घोषणा	STATUS_BFR_READ			30
#घोषणा	SET_RD_MODE_AFTER_STATUS	31

/* न_अंकD_DEVn_CFG0 bits */
#घोषणा	DEV0_CFG1_ECC_DISABLE		0
#घोषणा	WIDE_FLASH			1
#घोषणा	न_अंकD_RECOVERY_CYCLES		2
#घोषणा	CS_ACTIVE_BSY			5
#घोषणा	BAD_BLOCK_BYTE_NUM		6
#घोषणा	BAD_BLOCK_IN_SPARE_AREA		16
#घोषणा	WR_RD_BSY_GAP			17
#घोषणा	ENABLE_BCH_ECC			27

/* न_अंकD_DEV0_ECC_CFG bits */
#घोषणा	ECC_CFG_ECC_DISABLE		0
#घोषणा	ECC_SW_RESET			1
#घोषणा	ECC_MODE			4
#घोषणा	ECC_PARITY_SIZE_BYTES_BCH	8
#घोषणा	ECC_NUM_DATA_BYTES		16
#घोषणा	ECC_FORCE_CLK_OPEN		30

/* न_अंकD_DEV_CMD1 bits */
#घोषणा	READ_ADDR			0

/* न_अंकD_DEV_CMD_VLD bits */
#घोषणा	READ_START_VLD			BIT(0)
#घोषणा	READ_STOP_VLD			BIT(1)
#घोषणा	WRITE_START_VLD			BIT(2)
#घोषणा	ERASE_START_VLD			BIT(3)
#घोषणा	SEQ_READ_START_VLD		BIT(4)

/* न_अंकD_EBI2_ECC_BUF_CFG bits */
#घोषणा	NUM_STEPS			0

/* न_अंकD_ERASED_CW_DETECT_CFG bits */
#घोषणा	ERASED_CW_ECC_MASK		1
#घोषणा	AUTO_DETECT_RES			0
#घोषणा	MASK_ECC			(1 << ERASED_CW_ECC_MASK)
#घोषणा	RESET_ERASED_DET		(1 << AUTO_DETECT_RES)
#घोषणा	ACTIVE_ERASED_DET		(0 << AUTO_DETECT_RES)
#घोषणा	CLR_ERASED_PAGE_DET		(RESET_ERASED_DET | MASK_ECC)
#घोषणा	SET_ERASED_PAGE_DET		(ACTIVE_ERASED_DET | MASK_ECC)

/* न_अंकD_ERASED_CW_DETECT_STATUS bits */
#घोषणा	PAGE_ALL_ERASED			BIT(7)
#घोषणा	CODEWORD_ALL_ERASED		BIT(6)
#घोषणा	PAGE_ERASED			BIT(5)
#घोषणा	CODEWORD_ERASED			BIT(4)
#घोषणा	ERASED_PAGE			(PAGE_ALL_ERASED | PAGE_ERASED)
#घोषणा	ERASED_CW			(CODEWORD_ALL_ERASED | CODEWORD_ERASED)

/* न_अंकD_READ_LOCATION_n bits */
#घोषणा READ_LOCATION_OFFSET		0
#घोषणा READ_LOCATION_SIZE		16
#घोषणा READ_LOCATION_LAST		31

/* Version Mask */
#घोषणा	न_अंकD_VERSION_MAJOR_MASK		0xf0000000
#घोषणा	न_अंकD_VERSION_MAJOR_SHIFT	28
#घोषणा	न_अंकD_VERSION_MINOR_MASK		0x0fff0000
#घोषणा	न_अंकD_VERSION_MINOR_SHIFT	16

/* न_अंकD OP_CMDs */
#घोषणा	OP_PAGE_READ			0x2
#घोषणा	OP_PAGE_READ_WITH_ECC		0x3
#घोषणा	OP_PAGE_READ_WITH_ECC_SPARE	0x4
#घोषणा	OP_PAGE_READ_ONFI_READ		0x5
#घोषणा	OP_PROGRAM_PAGE			0x6
#घोषणा	OP_PAGE_PROGRAM_WITH_ECC	0x7
#घोषणा	OP_PROGRAM_PAGE_SPARE		0x9
#घोषणा	OP_BLOCK_ERASE			0xa
#घोषणा	OP_FETCH_ID			0xb
#घोषणा	OP_RESET_DEVICE			0xd

/* Default Value क्रम न_अंकD_DEV_CMD_VLD */
#घोषणा न_अंकD_DEV_CMD_VLD_VAL		(READ_START_VLD | WRITE_START_VLD | \
					 ERASE_START_VLD | SEQ_READ_START_VLD)

/* न_अंकD_CTRL bits */
#घोषणा	BAM_MODE_EN			BIT(0)

/*
 * the न_अंकD controller perक्रमms पढ़ोs/ग_लिखोs with ECC in 516 byte chunks.
 * the driver calls the chunks 'step' or 'codeword' पूर्णांकerchangeably
 */
#घोषणा	न_अंकDC_STEP_SIZE			512

/*
 * the largest page size we support is 8K, this will have 16 steps/codewords
 * of 512 bytes each
 */
#घोषणा	MAX_NUM_STEPS			(SZ_8K / न_अंकDC_STEP_SIZE)

/* we पढ़ो at most 3 रेजिस्टरs per codeword scan */
#घोषणा	MAX_REG_RD			(3 * MAX_NUM_STEPS)

/* ECC modes supported by the controller */
#घोषणा	ECC_NONE	BIT(0)
#घोषणा	ECC_RS_4BIT	BIT(1)
#घोषणा	ECC_BCH_4BIT	BIT(2)
#घोषणा	ECC_BCH_8BIT	BIT(3)

#घोषणा nandc_set_पढ़ो_loc_first(chip, reg, cw_offset, पढ़ो_size, is_last_पढ़ो_loc)	\
nandc_set_reg(chip, reg,			\
	      ((cw_offset) << READ_LOCATION_OFFSET) |		\
	      ((पढ़ो_size) << READ_LOCATION_SIZE) |			\
	      ((is_last_पढ़ो_loc) << READ_LOCATION_LAST))

#घोषणा nandc_set_पढ़ो_loc_last(chip, reg, cw_offset, पढ़ो_size, is_last_पढ़ो_loc)	\
nandc_set_reg(chip, reg,			\
	      ((cw_offset) << READ_LOCATION_OFFSET) |		\
	      ((पढ़ो_size) << READ_LOCATION_SIZE) |			\
	      ((is_last_पढ़ो_loc) << READ_LOCATION_LAST))
/*
 * Returns the actual रेजिस्टर address क्रम all न_अंकD_DEV_ रेजिस्टरs
 * (i.e. न_अंकD_DEV_CMD0, न_अंकD_DEV_CMD1, न_अंकD_DEV_CMD2 and न_अंकD_DEV_CMD_VLD)
 */
#घोषणा dev_cmd_reg_addr(nandc, reg) ((nandc)->props->dev_cmd_reg_start + (reg))

/* Returns the न_अंकD रेजिस्टर physical address */
#घोषणा nandc_reg_phys(chip, offset) ((chip)->base_phys + (offset))

/* Returns the dma address क्रम reg पढ़ो buffer */
#घोषणा reg_buf_dma_addr(chip, vaddr) \
	((chip)->reg_पढ़ो_dma + \
	((uपूर्णांक8_t *)(vaddr) - (uपूर्णांक8_t *)(chip)->reg_पढ़ो_buf))

#घोषणा QPIC_PER_CW_CMD_ELEMENTS	32
#घोषणा QPIC_PER_CW_CMD_SGL		32
#घोषणा QPIC_PER_CW_DATA_SGL		8

#घोषणा QPIC_न_अंकD_COMPLETION_TIMEOUT	msecs_to_jअगरfies(2000)

/*
 * Flags used in DMA descriptor preparation helper functions
 * (i.e. पढ़ो_reg_dma/ग_लिखो_reg_dma/पढ़ो_data_dma/ग_लिखो_data_dma)
 */
/* Don't set the EOT in current tx BAM sgl */
#घोषणा न_अंकD_BAM_NO_EOT			BIT(0)
/* Set the NWD flag in current BAM sgl */
#घोषणा न_अंकD_BAM_NWD			BIT(1)
/* Finish writing in the current BAM sgl and start writing in another BAM sgl */
#घोषणा न_अंकD_BAM_NEXT_SGL		BIT(2)
/*
 * Erased codeword status is being used two बार in single transfer so this
 * flag will determine the current value of erased codeword status रेजिस्टर
 */
#घोषणा न_अंकD_ERASED_CW_SET		BIT(4)

/*
 * This data type corresponds to the BAM transaction which will be used क्रम all
 * न_अंकD transfers.
 * @bam_ce - the array of BAM command elements
 * @cmd_sgl - sgl क्रम न_अंकD BAM command pipe
 * @data_sgl - sgl क्रम न_अंकD BAM consumer/producer pipe
 * @bam_ce_pos - the index in bam_ce which is available क्रम next sgl
 * @bam_ce_start - the index in bam_ce which marks the start position ce
 *		   क्रम current sgl. It will be used क्रम size calculation
 *		   क्रम current sgl
 * @cmd_sgl_pos - current index in command sgl.
 * @cmd_sgl_start - start index in command sgl.
 * @tx_sgl_pos - current index in data sgl क्रम tx.
 * @tx_sgl_start - start index in data sgl क्रम tx.
 * @rx_sgl_pos - current index in data sgl क्रम rx.
 * @rx_sgl_start - start index in data sgl क्रम rx.
 * @रुको_second_completion - रुको क्रम second DMA desc completion beक्रमe making
 *			     the न_अंकD transfer completion.
 * @txn_करोne - completion क्रम न_अंकD transfer.
 * @last_data_desc - last DMA desc in data channel (tx/rx).
 * @last_cmd_desc - last DMA desc in command channel.
 */
काष्ठा bam_transaction अणु
	काष्ठा bam_cmd_element *bam_ce;
	काष्ठा scatterlist *cmd_sgl;
	काष्ठा scatterlist *data_sgl;
	u32 bam_ce_pos;
	u32 bam_ce_start;
	u32 cmd_sgl_pos;
	u32 cmd_sgl_start;
	u32 tx_sgl_pos;
	u32 tx_sgl_start;
	u32 rx_sgl_pos;
	u32 rx_sgl_start;
	bool रुको_second_completion;
	काष्ठा completion txn_करोne;
	काष्ठा dma_async_tx_descriptor *last_data_desc;
	काष्ठा dma_async_tx_descriptor *last_cmd_desc;
पूर्ण;

/*
 * This data type corresponds to the nand dma descriptor
 * @list - list क्रम desc_info
 * @dir - DMA transfer direction
 * @adm_sgl - sgl which will be used क्रम single sgl dma descriptor. Only used by
 *	      ADM
 * @bam_sgl - sgl which will be used क्रम dma descriptor. Only used by BAM
 * @sgl_cnt - number of SGL in bam_sgl. Only used by BAM
 * @dma_desc - low level DMA engine descriptor
 */
काष्ठा desc_info अणु
	काष्ठा list_head node;

	क्रमागत dma_data_direction dir;
	जोड़ अणु
		काष्ठा scatterlist adm_sgl;
		काष्ठा अणु
			काष्ठा scatterlist *bam_sgl;
			पूर्णांक sgl_cnt;
		पूर्ण;
	पूर्ण;
	काष्ठा dma_async_tx_descriptor *dma_desc;
पूर्ण;

/*
 * holds the current रेजिस्टर values that we want to ग_लिखो. acts as a contiguous
 * chunk of memory which we use to ग_लिखो the controller रेजिस्टरs through DMA.
 */
काष्ठा nandc_regs अणु
	__le32 cmd;
	__le32 addr0;
	__le32 addr1;
	__le32 chip_sel;
	__le32 exec;

	__le32 cfg0;
	__le32 cfg1;
	__le32 ecc_bch_cfg;

	__le32 clrflashstatus;
	__le32 clrपढ़ोstatus;

	__le32 cmd1;
	__le32 vld;

	__le32 orig_cmd1;
	__le32 orig_vld;

	__le32 ecc_buf_cfg;
	__le32 पढ़ो_location0;
	__le32 पढ़ो_location1;
	__le32 पढ़ो_location2;
	__le32 पढ़ो_location3;
	__le32 पढ़ो_location_last0;
	__le32 पढ़ो_location_last1;
	__le32 पढ़ो_location_last2;
	__le32 पढ़ो_location_last3;

	__le32 erased_cw_detect_cfg_clr;
	__le32 erased_cw_detect_cfg_set;
पूर्ण;

/*
 * न_अंकD controller data काष्ठा
 *
 * @controller:			base controller काष्ठाure
 * @host_list:			list containing all the chips attached to the
 *				controller
 * @dev:			parent device
 * @base:			MMIO base
 * @base_phys:			physical base address of controller रेजिस्टरs
 * @base_dma:			dma base address of controller रेजिस्टरs
 * @core_clk:			controller घड़ी
 * @aon_clk:			another controller घड़ी
 *
 * @chan:			dma channel
 * @cmd_crci:			ADM DMA CRCI क्रम command flow control
 * @data_crci:			ADM DMA CRCI क्रम data flow control
 * @desc_list:			DMA descriptor list (list of desc_infos)
 *
 * @data_buffer:		our local DMA buffer क्रम page पढ़ो/ग_लिखोs,
 *				used when we can't use the buffer provided
 *				by upper layers directly
 * @buf_size/count/start:	markers क्रम chip->legacy.पढ़ो_buf/ग_लिखो_buf
 *				functions
 * @reg_पढ़ो_buf:		local buffer क्रम पढ़ोing back रेजिस्टरs via DMA
 * @reg_पढ़ो_dma:		contains dma address क्रम रेजिस्टर पढ़ो buffer
 * @reg_पढ़ो_pos:		marker क्रम data पढ़ो in reg_पढ़ो_buf
 *
 * @regs:			a contiguous chunk of memory क्रम DMA रेजिस्टर
 *				ग_लिखोs. contains the रेजिस्टर values to be
 *				written to controller
 * @cmd1/vld:			some fixed controller रेजिस्टर values
 * @props:			properties of current न_अंकD controller,
 *				initialized via DT match data
 * @max_cwperpage:		maximum QPIC codewords required. calculated
 *				from all connected न_अंकD devices pagesize
 */
काष्ठा qcom_nand_controller अणु
	काष्ठा nand_controller controller;
	काष्ठा list_head host_list;

	काष्ठा device *dev;

	व्योम __iomem *base;
	phys_addr_t base_phys;
	dma_addr_t base_dma;

	काष्ठा clk *core_clk;
	काष्ठा clk *aon_clk;

	जोड़ अणु
		/* will be used only by QPIC क्रम BAM DMA */
		काष्ठा अणु
			काष्ठा dma_chan *tx_chan;
			काष्ठा dma_chan *rx_chan;
			काष्ठा dma_chan *cmd_chan;
		पूर्ण;

		/* will be used only by EBI2 क्रम ADM DMA */
		काष्ठा अणु
			काष्ठा dma_chan *chan;
			अचिन्हित पूर्णांक cmd_crci;
			अचिन्हित पूर्णांक data_crci;
		पूर्ण;
	पूर्ण;

	काष्ठा list_head desc_list;
	काष्ठा bam_transaction *bam_txn;

	u8		*data_buffer;
	पूर्णांक		buf_size;
	पूर्णांक		buf_count;
	पूर्णांक		buf_start;
	अचिन्हित पूर्णांक	max_cwperpage;

	__le32 *reg_पढ़ो_buf;
	dma_addr_t reg_पढ़ो_dma;
	पूर्णांक reg_पढ़ो_pos;

	काष्ठा nandc_regs *regs;

	u32 cmd1, vld;
	स्थिर काष्ठा qcom_nandc_props *props;
पूर्ण;

/*
 * न_अंकD chip काष्ठाure
 *
 * @chip:			base न_अंकD chip काष्ठाure
 * @node:			list node to add itself to host_list in
 *				qcom_nand_controller
 *
 * @cs:				chip select value क्रम this chip
 * @cw_size:			the number of bytes in a single step/codeword
 *				of a page, consisting of all data, ecc, spare
 *				and reserved bytes
 * @cw_data:			the number of bytes within a codeword रक्षित
 *				by ECC
 * @use_ecc:			request the controller to use ECC क्रम the
 *				upcoming पढ़ो/ग_लिखो
 * @bch_enabled:		flag to tell whether BCH ECC mode is used
 * @ecc_bytes_hw:		ECC bytes used by controller hardware क्रम this
 *				chip
 * @status:			value to be वापसed अगर न_अंकD_CMD_STATUS command
 *				is executed
 * @last_command:		keeps track of last command on this chip. used
 *				क्रम पढ़ोing correct status
 *
 * @cfg0, cfg1, cfg0_raw..:	न_अंकDc रेजिस्टर configurations needed क्रम
 *				ecc/non-ecc mode क्रम the current nand flash
 *				device
 */
काष्ठा qcom_nand_host अणु
	काष्ठा nand_chip chip;
	काष्ठा list_head node;

	पूर्णांक cs;
	पूर्णांक cw_size;
	पूर्णांक cw_data;
	bool use_ecc;
	bool bch_enabled;
	पूर्णांक ecc_bytes_hw;
	पूर्णांक spare_bytes;
	पूर्णांक bbm_size;
	u8 status;
	पूर्णांक last_command;

	u32 cfg0, cfg1;
	u32 cfg0_raw, cfg1_raw;
	u32 ecc_buf_cfg;
	u32 ecc_bch_cfg;
	u32 clrflashstatus;
	u32 clrपढ़ोstatus;
पूर्ण;

/*
 * This data type corresponds to the न_अंकD controller properties which varies
 * among dअगरferent न_अंकD controllers.
 * @ecc_modes - ecc mode क्रम न_अंकD
 * @is_bam - whether न_अंकD controller is using BAM
 * @is_qpic - whether न_अंकD CTRL is part of qpic IP
 * @qpic_v2 - flag to indicate QPIC IP version 2
 * @dev_cmd_reg_start - न_अंकD_DEV_CMD_* रेजिस्टरs starting offset
 */
काष्ठा qcom_nandc_props अणु
	u32 ecc_modes;
	bool is_bam;
	bool is_qpic;
	bool qpic_v2;
	u32 dev_cmd_reg_start;
पूर्ण;

/* Frees the BAM transaction memory */
अटल व्योम मुक्त_bam_transaction(काष्ठा qcom_nand_controller *nandc)
अणु
	काष्ठा bam_transaction *bam_txn = nandc->bam_txn;

	devm_kमुक्त(nandc->dev, bam_txn);
पूर्ण

/* Allocates and Initializes the BAM transaction */
अटल काष्ठा bam_transaction *
alloc_bam_transaction(काष्ठा qcom_nand_controller *nandc)
अणु
	काष्ठा bam_transaction *bam_txn;
	माप_प्रकार bam_txn_size;
	अचिन्हित पूर्णांक num_cw = nandc->max_cwperpage;
	व्योम *bam_txn_buf;

	bam_txn_size =
		माप(*bam_txn) + num_cw *
		((माप(*bam_txn->bam_ce) * QPIC_PER_CW_CMD_ELEMENTS) +
		(माप(*bam_txn->cmd_sgl) * QPIC_PER_CW_CMD_SGL) +
		(माप(*bam_txn->data_sgl) * QPIC_PER_CW_DATA_SGL));

	bam_txn_buf = devm_kzalloc(nandc->dev, bam_txn_size, GFP_KERNEL);
	अगर (!bam_txn_buf)
		वापस शून्य;

	bam_txn = bam_txn_buf;
	bam_txn_buf += माप(*bam_txn);

	bam_txn->bam_ce = bam_txn_buf;
	bam_txn_buf +=
		माप(*bam_txn->bam_ce) * QPIC_PER_CW_CMD_ELEMENTS * num_cw;

	bam_txn->cmd_sgl = bam_txn_buf;
	bam_txn_buf +=
		माप(*bam_txn->cmd_sgl) * QPIC_PER_CW_CMD_SGL * num_cw;

	bam_txn->data_sgl = bam_txn_buf;

	init_completion(&bam_txn->txn_करोne);

	वापस bam_txn;
पूर्ण

/* Clears the BAM transaction indexes */
अटल व्योम clear_bam_transaction(काष्ठा qcom_nand_controller *nandc)
अणु
	काष्ठा bam_transaction *bam_txn = nandc->bam_txn;

	अगर (!nandc->props->is_bam)
		वापस;

	bam_txn->bam_ce_pos = 0;
	bam_txn->bam_ce_start = 0;
	bam_txn->cmd_sgl_pos = 0;
	bam_txn->cmd_sgl_start = 0;
	bam_txn->tx_sgl_pos = 0;
	bam_txn->tx_sgl_start = 0;
	bam_txn->rx_sgl_pos = 0;
	bam_txn->rx_sgl_start = 0;
	bam_txn->last_data_desc = शून्य;
	bam_txn->रुको_second_completion = false;

	sg_init_table(bam_txn->cmd_sgl, nandc->max_cwperpage *
		      QPIC_PER_CW_CMD_SGL);
	sg_init_table(bam_txn->data_sgl, nandc->max_cwperpage *
		      QPIC_PER_CW_DATA_SGL);

	reinit_completion(&bam_txn->txn_करोne);
पूर्ण

/* Callback क्रम DMA descriptor completion */
अटल व्योम qpic_bam_dma_करोne(व्योम *data)
अणु
	काष्ठा bam_transaction *bam_txn = data;

	/*
	 * In हाल of data transfer with न_अंकD, 2 callbacks will be generated.
	 * One क्रम command channel and another one क्रम data channel.
	 * If current transaction has data descriptors
	 * (i.e. रुको_second_completion is true), then set this to false
	 * and रुको क्रम second DMA descriptor completion.
	 */
	अगर (bam_txn->रुको_second_completion)
		bam_txn->रुको_second_completion = false;
	अन्यथा
		complete(&bam_txn->txn_करोne);
पूर्ण

अटल अंतरभूत काष्ठा qcom_nand_host *to_qcom_nand_host(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip, काष्ठा qcom_nand_host, chip);
पूर्ण

अटल अंतरभूत काष्ठा qcom_nand_controller *
get_qcom_nand_controller(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip->controller, काष्ठा qcom_nand_controller,
			    controller);
पूर्ण

अटल अंतरभूत u32 nandc_पढ़ो(काष्ठा qcom_nand_controller *nandc, पूर्णांक offset)
अणु
	वापस ioपढ़ो32(nandc->base + offset);
पूर्ण

अटल अंतरभूत व्योम nandc_ग_लिखो(काष्ठा qcom_nand_controller *nandc, पूर्णांक offset,
			       u32 val)
अणु
	ioग_लिखो32(val, nandc->base + offset);
पूर्ण

अटल अंतरभूत व्योम nandc_पढ़ो_buffer_sync(काष्ठा qcom_nand_controller *nandc,
					  bool is_cpu)
अणु
	अगर (!nandc->props->is_bam)
		वापस;

	अगर (is_cpu)
		dma_sync_single_क्रम_cpu(nandc->dev, nandc->reg_पढ़ो_dma,
					MAX_REG_RD *
					माप(*nandc->reg_पढ़ो_buf),
					DMA_FROM_DEVICE);
	अन्यथा
		dma_sync_single_क्रम_device(nandc->dev, nandc->reg_पढ़ो_dma,
					   MAX_REG_RD *
					   माप(*nandc->reg_पढ़ो_buf),
					   DMA_FROM_DEVICE);
पूर्ण

अटल __le32 *offset_to_nandc_reg(काष्ठा nandc_regs *regs, पूर्णांक offset)
अणु
	चयन (offset) अणु
	हाल न_अंकD_FLASH_CMD:
		वापस &regs->cmd;
	हाल न_अंकD_ADDR0:
		वापस &regs->addr0;
	हाल न_अंकD_ADDR1:
		वापस &regs->addr1;
	हाल न_अंकD_FLASH_CHIP_SELECT:
		वापस &regs->chip_sel;
	हाल न_अंकD_EXEC_CMD:
		वापस &regs->exec;
	हाल न_अंकD_FLASH_STATUS:
		वापस &regs->clrflashstatus;
	हाल न_अंकD_DEV0_CFG0:
		वापस &regs->cfg0;
	हाल न_अंकD_DEV0_CFG1:
		वापस &regs->cfg1;
	हाल न_अंकD_DEV0_ECC_CFG:
		वापस &regs->ecc_bch_cfg;
	हाल न_अंकD_READ_STATUS:
		वापस &regs->clrपढ़ोstatus;
	हाल न_अंकD_DEV_CMD1:
		वापस &regs->cmd1;
	हाल न_अंकD_DEV_CMD1_RESTORE:
		वापस &regs->orig_cmd1;
	हाल न_अंकD_DEV_CMD_VLD:
		वापस &regs->vld;
	हाल न_अंकD_DEV_CMD_VLD_RESTORE:
		वापस &regs->orig_vld;
	हाल न_अंकD_EBI2_ECC_BUF_CFG:
		वापस &regs->ecc_buf_cfg;
	हाल न_अंकD_READ_LOCATION_0:
		वापस &regs->पढ़ो_location0;
	हाल न_अंकD_READ_LOCATION_1:
		वापस &regs->पढ़ो_location1;
	हाल न_अंकD_READ_LOCATION_2:
		वापस &regs->पढ़ो_location2;
	हाल न_अंकD_READ_LOCATION_3:
		वापस &regs->पढ़ो_location3;
	हाल न_अंकD_READ_LOCATION_LAST_CW_0:
		वापस &regs->पढ़ो_location_last0;
	हाल न_अंकD_READ_LOCATION_LAST_CW_1:
		वापस &regs->पढ़ो_location_last1;
	हाल न_अंकD_READ_LOCATION_LAST_CW_2:
		वापस &regs->पढ़ो_location_last2;
	हाल न_अंकD_READ_LOCATION_LAST_CW_3:
		वापस &regs->पढ़ो_location_last3;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम nandc_set_reg(काष्ठा nand_chip *chip, पूर्णांक offset,
			  u32 val)
अणु
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nandc_regs *regs = nandc->regs;
	__le32 *reg;

	reg = offset_to_nandc_reg(regs, offset);

	अगर (reg)
		*reg = cpu_to_le32(val);
पूर्ण

/* Helper to check the code word, whether it is last cw or not */
अटल bool qcom_nandc_is_last_cw(काष्ठा nand_ecc_ctrl *ecc, पूर्णांक cw)
अणु
	वापस cw == (ecc->steps - 1);
पूर्ण

/* helper to configure location रेजिस्टर values */
अटल व्योम nandc_set_पढ़ो_loc(काष्ठा nand_chip *chip, पूर्णांक cw, पूर्णांक reg,
			       पूर्णांक cw_offset, पूर्णांक पढ़ो_size, पूर्णांक is_last_पढ़ो_loc)
अणु
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक reg_base = न_अंकD_READ_LOCATION_0;

	अगर (nandc->props->qpic_v2 && qcom_nandc_is_last_cw(ecc, cw))
		reg_base = न_अंकD_READ_LOCATION_LAST_CW_0;

	reg_base += reg * 4;

	अगर (nandc->props->qpic_v2 && qcom_nandc_is_last_cw(ecc, cw))
		वापस nandc_set_पढ़ो_loc_last(chip, reg_base, cw_offset,
				पढ़ो_size, is_last_पढ़ो_loc);
	अन्यथा
		वापस nandc_set_पढ़ो_loc_first(chip, reg_base, cw_offset,
				पढ़ो_size, is_last_पढ़ो_loc);
पूर्ण

/* helper to configure address रेजिस्टर values */
अटल व्योम set_address(काष्ठा qcom_nand_host *host, u16 column, पूर्णांक page)
अणु
	काष्ठा nand_chip *chip = &host->chip;

	अगर (chip->options & न_अंकD_BUSWIDTH_16)
		column >>= 1;

	nandc_set_reg(chip, न_अंकD_ADDR0, page << 16 | column);
	nandc_set_reg(chip, न_अंकD_ADDR1, page >> 16 & 0xff);
पूर्ण

/*
 * update_rw_regs:	set up पढ़ो/ग_लिखो रेजिस्टर values, these will be
 *			written to the न_अंकD controller रेजिस्टरs via DMA
 *
 * @num_cw:		number of steps क्रम the पढ़ो/ग_लिखो operation
 * @पढ़ो:		पढ़ो or ग_लिखो operation
 * @cw	:		which code word
 */
अटल व्योम update_rw_regs(काष्ठा qcom_nand_host *host, पूर्णांक num_cw, bool पढ़ो, पूर्णांक cw)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	u32 cmd, cfg0, cfg1, ecc_bch_cfg;

	अगर (पढ़ो) अणु
		अगर (host->use_ecc)
			cmd = OP_PAGE_READ_WITH_ECC | PAGE_ACC | LAST_PAGE;
		अन्यथा
			cmd = OP_PAGE_READ | PAGE_ACC | LAST_PAGE;
	पूर्ण अन्यथा अणु
		cmd = OP_PROGRAM_PAGE | PAGE_ACC | LAST_PAGE;
	पूर्ण

	अगर (host->use_ecc) अणु
		cfg0 = (host->cfg0 & ~(7U << CW_PER_PAGE)) |
				(num_cw - 1) << CW_PER_PAGE;

		cfg1 = host->cfg1;
		ecc_bch_cfg = host->ecc_bch_cfg;
	पूर्ण अन्यथा अणु
		cfg0 = (host->cfg0_raw & ~(7U << CW_PER_PAGE)) |
				(num_cw - 1) << CW_PER_PAGE;

		cfg1 = host->cfg1_raw;
		ecc_bch_cfg = 1 << ECC_CFG_ECC_DISABLE;
	पूर्ण

	nandc_set_reg(chip, न_अंकD_FLASH_CMD, cmd);
	nandc_set_reg(chip, न_अंकD_DEV0_CFG0, cfg0);
	nandc_set_reg(chip, न_अंकD_DEV0_CFG1, cfg1);
	nandc_set_reg(chip, न_अंकD_DEV0_ECC_CFG, ecc_bch_cfg);
	nandc_set_reg(chip, न_अंकD_EBI2_ECC_BUF_CFG, host->ecc_buf_cfg);
	nandc_set_reg(chip, न_अंकD_FLASH_STATUS, host->clrflashstatus);
	nandc_set_reg(chip, न_अंकD_READ_STATUS, host->clrपढ़ोstatus);
	nandc_set_reg(chip, न_अंकD_EXEC_CMD, 1);

	अगर (पढ़ो)
		nandc_set_पढ़ो_loc(chip, cw, 0, 0, host->use_ecc ?
				   host->cw_data : host->cw_size, 1);
पूर्ण

/*
 * Maps the scatter gather list क्रम DMA transfer and क्रमms the DMA descriptor
 * क्रम BAM. This descriptor will be added in the न_अंकD DMA descriptor queue
 * which will be submitted to DMA engine.
 */
अटल पूर्णांक prepare_bam_async_desc(काष्ठा qcom_nand_controller *nandc,
				  काष्ठा dma_chan *chan,
				  अचिन्हित दीर्घ flags)
अणु
	काष्ठा desc_info *desc;
	काष्ठा scatterlist *sgl;
	अचिन्हित पूर्णांक sgl_cnt;
	पूर्णांक ret;
	काष्ठा bam_transaction *bam_txn = nandc->bam_txn;
	क्रमागत dma_transfer_direction dir_eng;
	काष्ठा dma_async_tx_descriptor *dma_desc;

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	अगर (chan == nandc->cmd_chan) अणु
		sgl = &bam_txn->cmd_sgl[bam_txn->cmd_sgl_start];
		sgl_cnt = bam_txn->cmd_sgl_pos - bam_txn->cmd_sgl_start;
		bam_txn->cmd_sgl_start = bam_txn->cmd_sgl_pos;
		dir_eng = DMA_MEM_TO_DEV;
		desc->dir = DMA_TO_DEVICE;
	पूर्ण अन्यथा अगर (chan == nandc->tx_chan) अणु
		sgl = &bam_txn->data_sgl[bam_txn->tx_sgl_start];
		sgl_cnt = bam_txn->tx_sgl_pos - bam_txn->tx_sgl_start;
		bam_txn->tx_sgl_start = bam_txn->tx_sgl_pos;
		dir_eng = DMA_MEM_TO_DEV;
		desc->dir = DMA_TO_DEVICE;
	पूर्ण अन्यथा अणु
		sgl = &bam_txn->data_sgl[bam_txn->rx_sgl_start];
		sgl_cnt = bam_txn->rx_sgl_pos - bam_txn->rx_sgl_start;
		bam_txn->rx_sgl_start = bam_txn->rx_sgl_pos;
		dir_eng = DMA_DEV_TO_MEM;
		desc->dir = DMA_FROM_DEVICE;
	पूर्ण

	sg_mark_end(sgl + sgl_cnt - 1);
	ret = dma_map_sg(nandc->dev, sgl, sgl_cnt, desc->dir);
	अगर (ret == 0) अणु
		dev_err(nandc->dev, "failure in mapping desc\n");
		kमुक्त(desc);
		वापस -ENOMEM;
	पूर्ण

	desc->sgl_cnt = sgl_cnt;
	desc->bam_sgl = sgl;

	dma_desc = dmaengine_prep_slave_sg(chan, sgl, sgl_cnt, dir_eng,
					   flags);

	अगर (!dma_desc) अणु
		dev_err(nandc->dev, "failure in prep desc\n");
		dma_unmap_sg(nandc->dev, sgl, sgl_cnt, desc->dir);
		kमुक्त(desc);
		वापस -EINVAL;
	पूर्ण

	desc->dma_desc = dma_desc;

	/* update last data/command descriptor */
	अगर (chan == nandc->cmd_chan)
		bam_txn->last_cmd_desc = dma_desc;
	अन्यथा
		bam_txn->last_data_desc = dma_desc;

	list_add_tail(&desc->node, &nandc->desc_list);

	वापस 0;
पूर्ण

/*
 * Prepares the command descriptor क्रम BAM DMA which will be used क्रम न_अंकD
 * रेजिस्टर पढ़ोs and ग_लिखोs. The command descriptor requires the command
 * to be क्रमmed in command element type so this function uses the command
 * element from bam transaction ce array and fills the same with required
 * data. A single SGL can contain multiple command elements so
 * न_अंकD_BAM_NEXT_SGL will be used क्रम starting the separate SGL
 * after the current command element.
 */
अटल पूर्णांक prep_bam_dma_desc_cmd(काष्ठा qcom_nand_controller *nandc, bool पढ़ो,
				 पूर्णांक reg_off, स्थिर व्योम *vaddr,
				 पूर्णांक size, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक bam_ce_size;
	पूर्णांक i, ret;
	काष्ठा bam_cmd_element *bam_ce_buffer;
	काष्ठा bam_transaction *bam_txn = nandc->bam_txn;

	bam_ce_buffer = &bam_txn->bam_ce[bam_txn->bam_ce_pos];

	/* fill the command desc */
	क्रम (i = 0; i < size; i++) अणु
		अगर (पढ़ो)
			bam_prep_ce(&bam_ce_buffer[i],
				    nandc_reg_phys(nandc, reg_off + 4 * i),
				    BAM_READ_COMMAND,
				    reg_buf_dma_addr(nandc,
						     (__le32 *)vaddr + i));
		अन्यथा
			bam_prep_ce_le32(&bam_ce_buffer[i],
					 nandc_reg_phys(nandc, reg_off + 4 * i),
					 BAM_WRITE_COMMAND,
					 *((__le32 *)vaddr + i));
	पूर्ण

	bam_txn->bam_ce_pos += size;

	/* use the separate sgl after this command */
	अगर (flags & न_अंकD_BAM_NEXT_SGL) अणु
		bam_ce_buffer = &bam_txn->bam_ce[bam_txn->bam_ce_start];
		bam_ce_size = (bam_txn->bam_ce_pos -
				bam_txn->bam_ce_start) *
				माप(काष्ठा bam_cmd_element);
		sg_set_buf(&bam_txn->cmd_sgl[bam_txn->cmd_sgl_pos],
			   bam_ce_buffer, bam_ce_size);
		bam_txn->cmd_sgl_pos++;
		bam_txn->bam_ce_start = bam_txn->bam_ce_pos;

		अगर (flags & न_अंकD_BAM_NWD) अणु
			ret = prepare_bam_async_desc(nandc, nandc->cmd_chan,
						     DMA_PREP_FENCE |
						     DMA_PREP_CMD);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Prepares the data descriptor क्रम BAM DMA which will be used क्रम न_अंकD
 * data पढ़ोs and ग_लिखोs.
 */
अटल पूर्णांक prep_bam_dma_desc_data(काष्ठा qcom_nand_controller *nandc, bool पढ़ो,
				  स्थिर व्योम *vaddr,
				  पूर्णांक size, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;
	काष्ठा bam_transaction *bam_txn = nandc->bam_txn;

	अगर (पढ़ो) अणु
		sg_set_buf(&bam_txn->data_sgl[bam_txn->rx_sgl_pos],
			   vaddr, size);
		bam_txn->rx_sgl_pos++;
	पूर्ण अन्यथा अणु
		sg_set_buf(&bam_txn->data_sgl[bam_txn->tx_sgl_pos],
			   vaddr, size);
		bam_txn->tx_sgl_pos++;

		/*
		 * BAM will only set EOT क्रम DMA_PREP_INTERRUPT so अगर this flag
		 * is not set, क्रमm the DMA descriptor
		 */
		अगर (!(flags & न_अंकD_BAM_NO_EOT)) अणु
			ret = prepare_bam_async_desc(nandc, nandc->tx_chan,
						     DMA_PREP_INTERRUPT);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक prep_adm_dma_desc(काष्ठा qcom_nand_controller *nandc, bool पढ़ो,
			     पूर्णांक reg_off, स्थिर व्योम *vaddr, पूर्णांक size,
			     bool flow_control)
अणु
	काष्ठा desc_info *desc;
	काष्ठा dma_async_tx_descriptor *dma_desc;
	काष्ठा scatterlist *sgl;
	काष्ठा dma_slave_config slave_conf;
	क्रमागत dma_transfer_direction dir_eng;
	पूर्णांक ret;

	desc = kzalloc(माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	sgl = &desc->adm_sgl;

	sg_init_one(sgl, vaddr, size);

	अगर (पढ़ो) अणु
		dir_eng = DMA_DEV_TO_MEM;
		desc->dir = DMA_FROM_DEVICE;
	पूर्ण अन्यथा अणु
		dir_eng = DMA_MEM_TO_DEV;
		desc->dir = DMA_TO_DEVICE;
	पूर्ण

	ret = dma_map_sg(nandc->dev, sgl, 1, desc->dir);
	अगर (ret == 0) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	स_रखो(&slave_conf, 0x00, माप(slave_conf));

	slave_conf.device_fc = flow_control;
	अगर (पढ़ो) अणु
		slave_conf.src_maxburst = 16;
		slave_conf.src_addr = nandc->base_dma + reg_off;
		slave_conf.slave_id = nandc->data_crci;
	पूर्ण अन्यथा अणु
		slave_conf.dst_maxburst = 16;
		slave_conf.dst_addr = nandc->base_dma + reg_off;
		slave_conf.slave_id = nandc->cmd_crci;
	पूर्ण

	ret = dmaengine_slave_config(nandc->chan, &slave_conf);
	अगर (ret) अणु
		dev_err(nandc->dev, "failed to configure dma channel\n");
		जाओ err;
	पूर्ण

	dma_desc = dmaengine_prep_slave_sg(nandc->chan, sgl, 1, dir_eng, 0);
	अगर (!dma_desc) अणु
		dev_err(nandc->dev, "failed to prepare desc\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	desc->dma_desc = dma_desc;

	list_add_tail(&desc->node, &nandc->desc_list);

	वापस 0;
err:
	kमुक्त(desc);

	वापस ret;
पूर्ण

/*
 * पढ़ो_reg_dma:	prepares a descriptor to पढ़ो a given number of
 *			contiguous रेजिस्टरs to the reg_पढ़ो_buf poपूर्णांकer
 *
 * @first:		offset of the first रेजिस्टर in the contiguous block
 * @num_regs:		number of रेजिस्टरs to पढ़ो
 * @flags:		flags to control DMA descriptor preparation
 */
अटल पूर्णांक पढ़ो_reg_dma(काष्ठा qcom_nand_controller *nandc, पूर्णांक first,
			पूर्णांक num_regs, अचिन्हित पूर्णांक flags)
अणु
	bool flow_control = false;
	व्योम *vaddr;

	vaddr = nandc->reg_पढ़ो_buf + nandc->reg_पढ़ो_pos;
	nandc->reg_पढ़ो_pos += num_regs;

	अगर (first == न_अंकD_DEV_CMD_VLD || first == न_अंकD_DEV_CMD1)
		first = dev_cmd_reg_addr(nandc, first);

	अगर (nandc->props->is_bam)
		वापस prep_bam_dma_desc_cmd(nandc, true, first, vaddr,
					     num_regs, flags);

	अगर (first == न_अंकD_READ_ID || first == न_अंकD_FLASH_STATUS)
		flow_control = true;

	वापस prep_adm_dma_desc(nandc, true, first, vaddr,
				 num_regs * माप(u32), flow_control);
पूर्ण

/*
 * ग_लिखो_reg_dma:	prepares a descriptor to ग_लिखो a given number of
 *			contiguous रेजिस्टरs
 *
 * @first:		offset of the first रेजिस्टर in the contiguous block
 * @num_regs:		number of रेजिस्टरs to ग_लिखो
 * @flags:		flags to control DMA descriptor preparation
 */
अटल पूर्णांक ग_लिखो_reg_dma(काष्ठा qcom_nand_controller *nandc, पूर्णांक first,
			 पूर्णांक num_regs, अचिन्हित पूर्णांक flags)
अणु
	bool flow_control = false;
	काष्ठा nandc_regs *regs = nandc->regs;
	व्योम *vaddr;

	vaddr = offset_to_nandc_reg(regs, first);

	अगर (first == न_अंकD_ERASED_CW_DETECT_CFG) अणु
		अगर (flags & न_अंकD_ERASED_CW_SET)
			vaddr = &regs->erased_cw_detect_cfg_set;
		अन्यथा
			vaddr = &regs->erased_cw_detect_cfg_clr;
	पूर्ण

	अगर (first == न_अंकD_EXEC_CMD)
		flags |= न_अंकD_BAM_NWD;

	अगर (first == न_अंकD_DEV_CMD1_RESTORE || first == न_अंकD_DEV_CMD1)
		first = dev_cmd_reg_addr(nandc, न_अंकD_DEV_CMD1);

	अगर (first == न_अंकD_DEV_CMD_VLD_RESTORE || first == न_अंकD_DEV_CMD_VLD)
		first = dev_cmd_reg_addr(nandc, न_अंकD_DEV_CMD_VLD);

	अगर (nandc->props->is_bam)
		वापस prep_bam_dma_desc_cmd(nandc, false, first, vaddr,
					     num_regs, flags);

	अगर (first == न_अंकD_FLASH_CMD)
		flow_control = true;

	वापस prep_adm_dma_desc(nandc, false, first, vaddr,
				 num_regs * माप(u32), flow_control);
पूर्ण

/*
 * पढ़ो_data_dma:	prepares a DMA descriptor to transfer data from the
 *			controller's internal buffer to the buffer 'vaddr'
 *
 * @reg_off:		offset within the controller's data buffer
 * @vaddr:		भव address of the buffer we want to ग_लिखो to
 * @size:		DMA transaction size in bytes
 * @flags:		flags to control DMA descriptor preparation
 */
अटल पूर्णांक पढ़ो_data_dma(काष्ठा qcom_nand_controller *nandc, पूर्णांक reg_off,
			 स्थिर u8 *vaddr, पूर्णांक size, अचिन्हित पूर्णांक flags)
अणु
	अगर (nandc->props->is_bam)
		वापस prep_bam_dma_desc_data(nandc, true, vaddr, size, flags);

	वापस prep_adm_dma_desc(nandc, true, reg_off, vaddr, size, false);
पूर्ण

/*
 * ग_लिखो_data_dma:	prepares a DMA descriptor to transfer data from
 *			'vaddr' to the controller's पूर्णांकernal buffer
 *
 * @reg_off:		offset within the controller's data buffer
 * @vaddr:		भव address of the buffer we want to पढ़ो from
 * @size:		DMA transaction size in bytes
 * @flags:		flags to control DMA descriptor preparation
 */
अटल पूर्णांक ग_लिखो_data_dma(काष्ठा qcom_nand_controller *nandc, पूर्णांक reg_off,
			  स्थिर u8 *vaddr, पूर्णांक size, अचिन्हित पूर्णांक flags)
अणु
	अगर (nandc->props->is_bam)
		वापस prep_bam_dma_desc_data(nandc, false, vaddr, size, flags);

	वापस prep_adm_dma_desc(nandc, false, reg_off, vaddr, size, false);
पूर्ण

/*
 * Helper to prepare DMA descriptors क्रम configuring रेजिस्टरs
 * beक्रमe पढ़ोing a न_अंकD page.
 */
अटल व्योम config_nand_page_पढ़ो(काष्ठा nand_chip *chip)
अणु
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	ग_लिखो_reg_dma(nandc, न_अंकD_ADDR0, 2, 0);
	ग_लिखो_reg_dma(nandc, न_अंकD_DEV0_CFG0, 3, 0);
	ग_लिखो_reg_dma(nandc, न_अंकD_EBI2_ECC_BUF_CFG, 1, 0);
	ग_लिखो_reg_dma(nandc, न_अंकD_ERASED_CW_DETECT_CFG, 1, 0);
	ग_लिखो_reg_dma(nandc, न_अंकD_ERASED_CW_DETECT_CFG, 1,
		      न_अंकD_ERASED_CW_SET | न_अंकD_BAM_NEXT_SGL);
पूर्ण

/*
 * Helper to prepare DMA descriptors क्रम configuring रेजिस्टरs
 * beक्रमe पढ़ोing each codeword in न_अंकD page.
 */
अटल व्योम
config_nand_cw_पढ़ो(काष्ठा nand_chip *chip, bool use_ecc, पूर्णांक cw)
अणु
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;

	पूर्णांक reg = न_अंकD_READ_LOCATION_0;

	अगर (nandc->props->qpic_v2 && qcom_nandc_is_last_cw(ecc, cw))
		reg = न_अंकD_READ_LOCATION_LAST_CW_0;

	अगर (nandc->props->is_bam)
		ग_लिखो_reg_dma(nandc, reg, 4, न_अंकD_BAM_NEXT_SGL);

	ग_लिखो_reg_dma(nandc, न_अंकD_FLASH_CMD, 1, न_अंकD_BAM_NEXT_SGL);
	ग_लिखो_reg_dma(nandc, न_अंकD_EXEC_CMD, 1, न_अंकD_BAM_NEXT_SGL);

	अगर (use_ecc) अणु
		पढ़ो_reg_dma(nandc, न_अंकD_FLASH_STATUS, 2, 0);
		पढ़ो_reg_dma(nandc, न_अंकD_ERASED_CW_DETECT_STATUS, 1,
			     न_अंकD_BAM_NEXT_SGL);
	पूर्ण अन्यथा अणु
		पढ़ो_reg_dma(nandc, न_अंकD_FLASH_STATUS, 1, न_अंकD_BAM_NEXT_SGL);
	पूर्ण
पूर्ण

/*
 * Helper to prepare dma descriptors to configure रेजिस्टरs needed क्रम पढ़ोing a
 * single codeword in page
 */
अटल व्योम
config_nand_single_cw_page_पढ़ो(काष्ठा nand_chip *chip,
				bool use_ecc, पूर्णांक cw)
अणु
	config_nand_page_पढ़ो(chip);
	config_nand_cw_पढ़ो(chip, use_ecc, cw);
पूर्ण

/*
 * Helper to prepare DMA descriptors used to configure रेजिस्टरs needed क्रम
 * beक्रमe writing a न_अंकD page.
 */
अटल व्योम config_nand_page_ग_लिखो(काष्ठा nand_chip *chip)
अणु
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	ग_लिखो_reg_dma(nandc, न_अंकD_ADDR0, 2, 0);
	ग_लिखो_reg_dma(nandc, न_अंकD_DEV0_CFG0, 3, 0);
	ग_लिखो_reg_dma(nandc, न_अंकD_EBI2_ECC_BUF_CFG, 1,
		      न_अंकD_BAM_NEXT_SGL);
पूर्ण

/*
 * Helper to prepare DMA descriptors क्रम configuring रेजिस्टरs
 * beक्रमe writing each codeword in न_अंकD page.
 */
अटल व्योम config_nand_cw_ग_लिखो(काष्ठा nand_chip *chip)
अणु
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	ग_लिखो_reg_dma(nandc, न_अंकD_FLASH_CMD, 1, न_अंकD_BAM_NEXT_SGL);
	ग_लिखो_reg_dma(nandc, न_अंकD_EXEC_CMD, 1, न_अंकD_BAM_NEXT_SGL);

	पढ़ो_reg_dma(nandc, न_अंकD_FLASH_STATUS, 1, न_अंकD_BAM_NEXT_SGL);

	ग_लिखो_reg_dma(nandc, न_अंकD_FLASH_STATUS, 1, 0);
	ग_लिखो_reg_dma(nandc, न_अंकD_READ_STATUS, 1, न_अंकD_BAM_NEXT_SGL);
पूर्ण

/*
 * the following functions are used within chip->legacy.cmdfunc() to
 * perक्रमm dअगरferent न_अंकD_CMD_* commands
 */

/* sets up descriptors क्रम न_अंकD_CMD_PARAM */
अटल पूर्णांक nandc_param(काष्ठा qcom_nand_host *host)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	/*
	 * न_अंकD_CMD_PARAM is called beक्रमe we know much about the FLASH chip
	 * in use. we configure the controller to perक्रमm a raw पढ़ो of 512
	 * bytes to पढ़ो onfi params
	 */
	अगर (nandc->props->qpic_v2)
		nandc_set_reg(chip, न_अंकD_FLASH_CMD, OP_PAGE_READ_ONFI_READ |
			      PAGE_ACC | LAST_PAGE);
	अन्यथा
		nandc_set_reg(chip, न_अंकD_FLASH_CMD, OP_PAGE_READ |
			      PAGE_ACC | LAST_PAGE);

	nandc_set_reg(chip, न_अंकD_ADDR0, 0);
	nandc_set_reg(chip, न_अंकD_ADDR1, 0);
	nandc_set_reg(chip, न_अंकD_DEV0_CFG0, 0 << CW_PER_PAGE
					| 512 << UD_SIZE_BYTES
					| 5 << NUM_ADDR_CYCLES
					| 0 << SPARE_SIZE_BYTES);
	nandc_set_reg(chip, न_अंकD_DEV0_CFG1, 7 << न_अंकD_RECOVERY_CYCLES
					| 0 << CS_ACTIVE_BSY
					| 17 << BAD_BLOCK_BYTE_NUM
					| 1 << BAD_BLOCK_IN_SPARE_AREA
					| 2 << WR_RD_BSY_GAP
					| 0 << WIDE_FLASH
					| 1 << DEV0_CFG1_ECC_DISABLE);
	nandc_set_reg(chip, न_अंकD_EBI2_ECC_BUF_CFG, 1 << ECC_CFG_ECC_DISABLE);

	/* configure CMD1 and VLD क्रम ONFI param probing in QPIC v1 */
	अगर (!nandc->props->qpic_v2) अणु
		nandc_set_reg(chip, न_अंकD_DEV_CMD_VLD,
			      (nandc->vld & ~READ_START_VLD));
		nandc_set_reg(chip, न_अंकD_DEV_CMD1,
			      (nandc->cmd1 & ~(0xFF << READ_ADDR))
			      | न_अंकD_CMD_PARAM << READ_ADDR);
	पूर्ण

	nandc_set_reg(chip, न_अंकD_EXEC_CMD, 1);

	अगर (!nandc->props->qpic_v2) अणु
		nandc_set_reg(chip, न_अंकD_DEV_CMD1_RESTORE, nandc->cmd1);
		nandc_set_reg(chip, न_अंकD_DEV_CMD_VLD_RESTORE, nandc->vld);
	पूर्ण

	nandc_set_पढ़ो_loc(chip, 0, 0, 0, 512, 1);

	अगर (!nandc->props->qpic_v2) अणु
		ग_लिखो_reg_dma(nandc, न_अंकD_DEV_CMD_VLD, 1, 0);
		ग_लिखो_reg_dma(nandc, न_अंकD_DEV_CMD1, 1, न_अंकD_BAM_NEXT_SGL);
	पूर्ण

	nandc->buf_count = 512;
	स_रखो(nandc->data_buffer, 0xff, nandc->buf_count);

	config_nand_single_cw_page_पढ़ो(chip, false, 0);

	पढ़ो_data_dma(nandc, FLASH_BUF_ACC, nandc->data_buffer,
		      nandc->buf_count, 0);

	/* restore CMD1 and VLD regs */
	अगर (!nandc->props->qpic_v2) अणु
		ग_लिखो_reg_dma(nandc, न_अंकD_DEV_CMD1_RESTORE, 1, 0);
		ग_लिखो_reg_dma(nandc, न_अंकD_DEV_CMD_VLD_RESTORE, 1, न_अंकD_BAM_NEXT_SGL);
	पूर्ण

	वापस 0;
पूर्ण

/* sets up descriptors क्रम न_अंकD_CMD_ERASE1 */
अटल पूर्णांक erase_block(काष्ठा qcom_nand_host *host, पूर्णांक page_addr)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	nandc_set_reg(chip, न_अंकD_FLASH_CMD,
		      OP_BLOCK_ERASE | PAGE_ACC | LAST_PAGE);
	nandc_set_reg(chip, न_अंकD_ADDR0, page_addr);
	nandc_set_reg(chip, न_अंकD_ADDR1, 0);
	nandc_set_reg(chip, न_अंकD_DEV0_CFG0,
		      host->cfg0_raw & ~(7 << CW_PER_PAGE));
	nandc_set_reg(chip, न_अंकD_DEV0_CFG1, host->cfg1_raw);
	nandc_set_reg(chip, न_अंकD_EXEC_CMD, 1);
	nandc_set_reg(chip, न_अंकD_FLASH_STATUS, host->clrflashstatus);
	nandc_set_reg(chip, न_अंकD_READ_STATUS, host->clrपढ़ोstatus);

	ग_लिखो_reg_dma(nandc, न_अंकD_FLASH_CMD, 3, न_अंकD_BAM_NEXT_SGL);
	ग_लिखो_reg_dma(nandc, न_अंकD_DEV0_CFG0, 2, न_अंकD_BAM_NEXT_SGL);
	ग_लिखो_reg_dma(nandc, न_अंकD_EXEC_CMD, 1, न_अंकD_BAM_NEXT_SGL);

	पढ़ो_reg_dma(nandc, न_अंकD_FLASH_STATUS, 1, न_अंकD_BAM_NEXT_SGL);

	ग_लिखो_reg_dma(nandc, न_अंकD_FLASH_STATUS, 1, 0);
	ग_लिखो_reg_dma(nandc, न_अंकD_READ_STATUS, 1, न_अंकD_BAM_NEXT_SGL);

	वापस 0;
पूर्ण

/* sets up descriptors क्रम न_अंकD_CMD_READID */
अटल पूर्णांक पढ़ो_id(काष्ठा qcom_nand_host *host, पूर्णांक column)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	अगर (column == -1)
		वापस 0;

	nandc_set_reg(chip, न_अंकD_FLASH_CMD, OP_FETCH_ID);
	nandc_set_reg(chip, न_अंकD_ADDR0, column);
	nandc_set_reg(chip, न_अंकD_ADDR1, 0);
	nandc_set_reg(chip, न_अंकD_FLASH_CHIP_SELECT,
		      nandc->props->is_bam ? 0 : DM_EN);
	nandc_set_reg(chip, न_अंकD_EXEC_CMD, 1);

	ग_लिखो_reg_dma(nandc, न_अंकD_FLASH_CMD, 4, न_अंकD_BAM_NEXT_SGL);
	ग_लिखो_reg_dma(nandc, न_अंकD_EXEC_CMD, 1, न_अंकD_BAM_NEXT_SGL);

	पढ़ो_reg_dma(nandc, न_अंकD_READ_ID, 1, न_अंकD_BAM_NEXT_SGL);

	वापस 0;
पूर्ण

/* sets up descriptors क्रम न_अंकD_CMD_RESET */
अटल पूर्णांक reset(काष्ठा qcom_nand_host *host)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	nandc_set_reg(chip, न_अंकD_FLASH_CMD, OP_RESET_DEVICE);
	nandc_set_reg(chip, न_अंकD_EXEC_CMD, 1);

	ग_लिखो_reg_dma(nandc, न_अंकD_FLASH_CMD, 1, न_अंकD_BAM_NEXT_SGL);
	ग_लिखो_reg_dma(nandc, न_अंकD_EXEC_CMD, 1, न_अंकD_BAM_NEXT_SGL);

	पढ़ो_reg_dma(nandc, न_अंकD_FLASH_STATUS, 1, न_अंकD_BAM_NEXT_SGL);

	वापस 0;
पूर्ण

/* helpers to submit/मुक्त our list of dma descriptors */
अटल पूर्णांक submit_descs(काष्ठा qcom_nand_controller *nandc)
अणु
	काष्ठा desc_info *desc;
	dma_cookie_t cookie = 0;
	काष्ठा bam_transaction *bam_txn = nandc->bam_txn;
	पूर्णांक r;

	अगर (nandc->props->is_bam) अणु
		अगर (bam_txn->rx_sgl_pos > bam_txn->rx_sgl_start) अणु
			r = prepare_bam_async_desc(nandc, nandc->rx_chan, 0);
			अगर (r)
				वापस r;
		पूर्ण

		अगर (bam_txn->tx_sgl_pos > bam_txn->tx_sgl_start) अणु
			r = prepare_bam_async_desc(nandc, nandc->tx_chan,
						   DMA_PREP_INTERRUPT);
			अगर (r)
				वापस r;
		पूर्ण

		अगर (bam_txn->cmd_sgl_pos > bam_txn->cmd_sgl_start) अणु
			r = prepare_bam_async_desc(nandc, nandc->cmd_chan,
						   DMA_PREP_CMD);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(desc, &nandc->desc_list, node)
		cookie = dmaengine_submit(desc->dma_desc);

	अगर (nandc->props->is_bam) अणु
		bam_txn->last_cmd_desc->callback = qpic_bam_dma_करोne;
		bam_txn->last_cmd_desc->callback_param = bam_txn;
		अगर (bam_txn->last_data_desc) अणु
			bam_txn->last_data_desc->callback = qpic_bam_dma_करोne;
			bam_txn->last_data_desc->callback_param = bam_txn;
			bam_txn->रुको_second_completion = true;
		पूर्ण

		dma_async_issue_pending(nandc->tx_chan);
		dma_async_issue_pending(nandc->rx_chan);
		dma_async_issue_pending(nandc->cmd_chan);

		अगर (!रुको_क्रम_completion_समयout(&bam_txn->txn_करोne,
						 QPIC_न_अंकD_COMPLETION_TIMEOUT))
			वापस -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		अगर (dma_sync_रुको(nandc->chan, cookie) != DMA_COMPLETE)
			वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम मुक्त_descs(काष्ठा qcom_nand_controller *nandc)
अणु
	काष्ठा desc_info *desc, *n;

	list_क्रम_each_entry_safe(desc, n, &nandc->desc_list, node) अणु
		list_del(&desc->node);

		अगर (nandc->props->is_bam)
			dma_unmap_sg(nandc->dev, desc->bam_sgl,
				     desc->sgl_cnt, desc->dir);
		अन्यथा
			dma_unmap_sg(nandc->dev, &desc->adm_sgl, 1,
				     desc->dir);

		kमुक्त(desc);
	पूर्ण
पूर्ण

/* reset the रेजिस्टर पढ़ो buffer क्रम next न_अंकD operation */
अटल व्योम clear_पढ़ो_regs(काष्ठा qcom_nand_controller *nandc)
अणु
	nandc->reg_पढ़ो_pos = 0;
	nandc_पढ़ो_buffer_sync(nandc, false);
पूर्ण

अटल व्योम pre_command(काष्ठा qcom_nand_host *host, पूर्णांक command)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	nandc->buf_count = 0;
	nandc->buf_start = 0;
	host->use_ecc = false;
	host->last_command = command;

	clear_पढ़ो_regs(nandc);

	अगर (command == न_अंकD_CMD_RESET || command == न_अंकD_CMD_READID ||
	    command == न_अंकD_CMD_PARAM || command == न_अंकD_CMD_ERASE1)
		clear_bam_transaction(nandc);
पूर्ण

/*
 * this is called after न_अंकD_CMD_PAGEPROG and न_अंकD_CMD_ERASE1 to set our
 * निजीly मुख्यtained status byte, this status byte can be पढ़ो after
 * न_अंकD_CMD_STATUS is called
 */
अटल व्योम parse_erase_ग_लिखो_errors(काष्ठा qcom_nand_host *host, पूर्णांक command)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक num_cw;
	पूर्णांक i;

	num_cw = command == न_अंकD_CMD_PAGEPROG ? ecc->steps : 1;
	nandc_पढ़ो_buffer_sync(nandc, true);

	क्रम (i = 0; i < num_cw; i++) अणु
		u32 flash_status = le32_to_cpu(nandc->reg_पढ़ो_buf[i]);

		अगर (flash_status & FS_MPU_ERR)
			host->status &= ~न_अंकD_STATUS_WP;

		अगर (flash_status & FS_OP_ERR || (i == (num_cw - 1) &&
						 (flash_status &
						  FS_DEVICE_STS_ERR)))
			host->status |= न_अंकD_STATUS_FAIL;
	पूर्ण
पूर्ण

अटल व्योम post_command(काष्ठा qcom_nand_host *host, पूर्णांक command)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	चयन (command) अणु
	हाल न_अंकD_CMD_READID:
		nandc_पढ़ो_buffer_sync(nandc, true);
		स_नकल(nandc->data_buffer, nandc->reg_पढ़ो_buf,
		       nandc->buf_count);
		अवरोध;
	हाल न_अंकD_CMD_PAGEPROG:
	हाल न_अंकD_CMD_ERASE1:
		parse_erase_ग_लिखो_errors(host, command);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Implements chip->legacy.cmdfunc. It's  only used क्रम a limited set of
 * commands. The rest of the commands wouldn't be called by upper layers.
 * For example, न_अंकD_CMD_READOOB would never be called because we have our own
 * versions of पढ़ो_oob ops क्रम nand_ecc_ctrl.
 */
अटल व्योम qcom_nandc_command(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक command,
			       पूर्णांक column, पूर्णांक page_addr)
अणु
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	bool रुको = false;
	पूर्णांक ret = 0;

	pre_command(host, command);

	चयन (command) अणु
	हाल न_अंकD_CMD_RESET:
		ret = reset(host);
		रुको = true;
		अवरोध;

	हाल न_अंकD_CMD_READID:
		nandc->buf_count = 4;
		ret = पढ़ो_id(host, column);
		रुको = true;
		अवरोध;

	हाल न_अंकD_CMD_PARAM:
		ret = nandc_param(host);
		रुको = true;
		अवरोध;

	हाल न_अंकD_CMD_ERASE1:
		ret = erase_block(host, page_addr);
		रुको = true;
		अवरोध;

	हाल न_अंकD_CMD_READ0:
		/* we पढ़ो the entire page क्रम now */
		WARN_ON(column != 0);

		host->use_ecc = true;
		set_address(host, 0, page_addr);
		update_rw_regs(host, ecc->steps, true, 0);
		अवरोध;

	हाल न_अंकD_CMD_SEQIN:
		WARN_ON(column != 0);
		set_address(host, 0, page_addr);
		अवरोध;

	हाल न_अंकD_CMD_PAGEPROG:
	हाल न_अंकD_CMD_STATUS:
	हाल न_अंकD_CMD_NONE:
	शेष:
		अवरोध;
	पूर्ण

	अगर (ret) अणु
		dev_err(nandc->dev, "failure executing command %d\n",
			command);
		मुक्त_descs(nandc);
		वापस;
	पूर्ण

	अगर (रुको) अणु
		ret = submit_descs(nandc);
		अगर (ret)
			dev_err(nandc->dev,
				"failure submitting descs for command %d\n",
				command);
	पूर्ण

	मुक्त_descs(nandc);

	post_command(host, command);
पूर्ण

/*
 * when using BCH ECC, the HW flags an error in न_अंकD_FLASH_STATUS अगर it पढ़ो
 * an erased CW, and reports an erased CW in न_अंकD_ERASED_CW_DETECT_STATUS.
 *
 * when using RS ECC, the HW reports the same erros when पढ़ोing an erased CW,
 * but it notअगरies that it is an erased CW by placing special अक्षरacters at
 * certain offsets in the buffer.
 *
 * verअगरy अगर the page is erased or not, and fix up the page क्रम RS ECC by
 * replacing the special अक्षरacters with 0xff.
 */
अटल bool erased_chunk_check_and_fixup(u8 *data_buf, पूर्णांक data_len)
अणु
	u8 empty1, empty2;

	/*
	 * an erased page flags an error in न_अंकD_FLASH_STATUS, check अगर the page
	 * is erased by looking क्रम 0x54s at offsets 3 and 175 from the
	 * beginning of each codeword
	 */

	empty1 = data_buf[3];
	empty2 = data_buf[175];

	/*
	 * अगर the erased codework markers, अगर they exist override them with
	 * 0xffs
	 */
	अगर ((empty1 == 0x54 && empty2 == 0xff) ||
	    (empty1 == 0xff && empty2 == 0x54)) अणु
		data_buf[3] = 0xff;
		data_buf[175] = 0xff;
	पूर्ण

	/*
	 * check अगर the entire chunk contains 0xffs or not. अगर it करोesn't, then
	 * restore the original values at the special offsets
	 */
	अगर (स_प्रथम_inv(data_buf, 0xff, data_len)) अणु
		data_buf[3] = empty1;
		data_buf[175] = empty2;

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

काष्ठा पढ़ो_stats अणु
	__le32 flash;
	__le32 buffer;
	__le32 erased_cw;
पूर्ण;

/* पढ़ोs back FLASH_STATUS रेजिस्टर set by the controller */
अटल पूर्णांक check_flash_errors(काष्ठा qcom_nand_host *host, पूर्णांक cw_cnt)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	पूर्णांक i;

	nandc_पढ़ो_buffer_sync(nandc, true);

	क्रम (i = 0; i < cw_cnt; i++) अणु
		u32 flash = le32_to_cpu(nandc->reg_पढ़ो_buf[i]);

		अगर (flash & (FS_OP_ERR | FS_MPU_ERR))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/* perक्रमms raw पढ़ो क्रम one codeword */
अटल पूर्णांक
qcom_nandc_पढ़ो_cw_raw(काष्ठा mtd_info *mtd, काष्ठा nand_chip *chip,
		       u8 *data_buf, u8 *oob_buf, पूर्णांक page, पूर्णांक cw)
अणु
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक data_size1, data_size2, oob_size1, oob_size2;
	पूर्णांक ret, reg_off = FLASH_BUF_ACC, पढ़ो_loc = 0;

	nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);
	host->use_ecc = false;

	clear_bam_transaction(nandc);
	set_address(host, host->cw_size * cw, page);
	update_rw_regs(host, 1, true, cw);
	config_nand_page_पढ़ो(chip);

	data_size1 = mtd->ग_लिखोsize - host->cw_size * (ecc->steps - 1);
	oob_size1 = host->bbm_size;

	अगर (qcom_nandc_is_last_cw(ecc, cw)) अणु
		data_size2 = ecc->size - data_size1 -
			     ((ecc->steps - 1) * 4);
		oob_size2 = (ecc->steps * 4) + host->ecc_bytes_hw +
			    host->spare_bytes;
	पूर्ण अन्यथा अणु
		data_size2 = host->cw_data - data_size1;
		oob_size2 = host->ecc_bytes_hw + host->spare_bytes;
	पूर्ण

	अगर (nandc->props->is_bam) अणु
		nandc_set_पढ़ो_loc(chip, cw, 0, पढ़ो_loc, data_size1, 0);
		पढ़ो_loc += data_size1;

		nandc_set_पढ़ो_loc(chip, cw, 1, पढ़ो_loc, oob_size1, 0);
		पढ़ो_loc += oob_size1;

		nandc_set_पढ़ो_loc(chip, cw, 2, पढ़ो_loc, data_size2, 0);
		पढ़ो_loc += data_size2;

		nandc_set_पढ़ो_loc(chip, cw, 3, पढ़ो_loc, oob_size2, 1);
	पूर्ण

	config_nand_cw_पढ़ो(chip, false, cw);

	पढ़ो_data_dma(nandc, reg_off, data_buf, data_size1, 0);
	reg_off += data_size1;

	पढ़ो_data_dma(nandc, reg_off, oob_buf, oob_size1, 0);
	reg_off += oob_size1;

	पढ़ो_data_dma(nandc, reg_off, data_buf + data_size1, data_size2, 0);
	reg_off += data_size2;

	पढ़ो_data_dma(nandc, reg_off, oob_buf + oob_size1, oob_size2, 0);

	ret = submit_descs(nandc);
	मुक्त_descs(nandc);
	अगर (ret) अणु
		dev_err(nandc->dev, "failure to read raw cw %d\n", cw);
		वापस ret;
	पूर्ण

	वापस check_flash_errors(host, 1);
पूर्ण

/*
 * Bitflips can happen in erased codewords also so this function counts the
 * number of 0 in each CW क्रम which ECC engine वापसs the uncorrectable
 * error. The page will be assumed as erased अगर this count is less than or
 * equal to the ecc->strength क्रम each CW.
 *
 * 1. Both DATA and OOB need to be checked क्रम number of 0. The
 *    top-level API can be called with only data buf or OOB buf so use
 *    chip->data_buf अगर data buf is null and chip->oob_poi अगर oob buf
 *    is null क्रम copying the raw bytes.
 * 2. Perक्रमm raw पढ़ो क्रम all the CW which has uncorrectable errors.
 * 3. For each CW, check the number of 0 in cw_data and usable OOB bytes.
 *    The BBM and spare bytes bit flip wonै t affect the ECC so करोnै t check
 *    the number of bitflips in this area.
 */
अटल पूर्णांक
check_क्रम_erased_page(काष्ठा qcom_nand_host *host, u8 *data_buf,
		      u8 *oob_buf, अचिन्हित दीर्घ uncorrectable_cws,
		      पूर्णांक page, अचिन्हित पूर्णांक max_bitflips)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	u8 *cw_data_buf, *cw_oob_buf;
	पूर्णांक cw, data_size, oob_size, ret = 0;

	अगर (!data_buf)
		data_buf = nand_get_data_buf(chip);

	अगर (!oob_buf) अणु
		nand_get_data_buf(chip);
		oob_buf = chip->oob_poi;
	पूर्ण

	क्रम_each_set_bit(cw, &uncorrectable_cws, ecc->steps) अणु
		अगर (qcom_nandc_is_last_cw(ecc, cw)) अणु
			data_size = ecc->size - ((ecc->steps - 1) * 4);
			oob_size = (ecc->steps * 4) + host->ecc_bytes_hw;
		पूर्ण अन्यथा अणु
			data_size = host->cw_data;
			oob_size = host->ecc_bytes_hw;
		पूर्ण

		/* determine starting buffer address क्रम current CW */
		cw_data_buf = data_buf + (cw * host->cw_data);
		cw_oob_buf = oob_buf + (cw * ecc->bytes);

		ret = qcom_nandc_पढ़ो_cw_raw(mtd, chip, cw_data_buf,
					     cw_oob_buf, page, cw);
		अगर (ret)
			वापस ret;

		/*
		 * make sure it isn't an erased page reported
		 * as not-erased by HW because of a few bitflips
		 */
		ret = nand_check_erased_ecc_chunk(cw_data_buf, data_size,
						  cw_oob_buf + host->bbm_size,
						  oob_size, शून्य,
						  0, ecc->strength);
		अगर (ret < 0) अणु
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += ret;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, ret);
		पूर्ण
	पूर्ण

	वापस max_bitflips;
पूर्ण

/*
 * पढ़ोs back status रेजिस्टरs set by the controller to notअगरy page पढ़ो
 * errors. this is equivalent to what 'ecc->correct()' would करो.
 */
अटल पूर्णांक parse_पढ़ो_errors(काष्ठा qcom_nand_host *host, u8 *data_buf,
			     u8 *oob_buf, पूर्णांक page)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	अचिन्हित पूर्णांक max_bitflips = 0, uncorrectable_cws = 0;
	काष्ठा पढ़ो_stats *buf;
	bool flash_op_err = false, erased;
	पूर्णांक i;
	u8 *data_buf_start = data_buf, *oob_buf_start = oob_buf;

	buf = (काष्ठा पढ़ो_stats *)nandc->reg_पढ़ो_buf;
	nandc_पढ़ो_buffer_sync(nandc, true);

	क्रम (i = 0; i < ecc->steps; i++, buf++) अणु
		u32 flash, buffer, erased_cw;
		पूर्णांक data_len, oob_len;

		अगर (qcom_nandc_is_last_cw(ecc, i)) अणु
			data_len = ecc->size - ((ecc->steps - 1) << 2);
			oob_len = ecc->steps << 2;
		पूर्ण अन्यथा अणु
			data_len = host->cw_data;
			oob_len = 0;
		पूर्ण

		flash = le32_to_cpu(buf->flash);
		buffer = le32_to_cpu(buf->buffer);
		erased_cw = le32_to_cpu(buf->erased_cw);

		/*
		 * Check ECC failure क्रम each codeword. ECC failure can
		 * happen in either of the following conditions
		 * 1. If number of bitflips are greater than ECC engine
		 *    capability.
		 * 2. If this codeword contains all 0xff क्रम which erased
		 *    codeword detection check will be करोne.
		 */
		अगर ((flash & FS_OP_ERR) && (buffer & BS_UNCORRECTABLE_BIT)) अणु
			/*
			 * For BCH ECC, ignore erased codeword errors, अगर
			 * ERASED_CW bits are set.
			 */
			अगर (host->bch_enabled) अणु
				erased = (erased_cw & ERASED_CW) == ERASED_CW ?
					 true : false;
			/*
			 * For RS ECC, HW reports the erased CW by placing
			 * special अक्षरacters at certain offsets in the buffer.
			 * These special अक्षरacters will be valid only अगर
			 * complete page is पढ़ो i.e. data_buf is not शून्य.
			 */
			पूर्ण अन्यथा अगर (data_buf) अणु
				erased = erased_chunk_check_and_fixup(data_buf,
								      data_len);
			पूर्ण अन्यथा अणु
				erased = false;
			पूर्ण

			अगर (!erased)
				uncorrectable_cws |= BIT(i);
		/*
		 * Check अगर MPU or any other operational error (समयout,
		 * device failure, etc.) happened क्रम this codeword and
		 * make flash_op_err true. If flash_op_err is set, then
		 * EIO will be वापसed क्रम page पढ़ो.
		 */
		पूर्ण अन्यथा अगर (flash & (FS_OP_ERR | FS_MPU_ERR)) अणु
			flash_op_err = true;
		/*
		 * No ECC or operational errors happened. Check the number of
		 * bits corrected and update the ecc_stats.corrected.
		 */
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक stat;

			stat = buffer & BS_CORRECTABLE_ERR_MSK;
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max(max_bitflips, stat);
		पूर्ण

		अगर (data_buf)
			data_buf += data_len;
		अगर (oob_buf)
			oob_buf += oob_len + ecc->bytes;
	पूर्ण

	अगर (flash_op_err)
		वापस -EIO;

	अगर (!uncorrectable_cws)
		वापस max_bitflips;

	वापस check_क्रम_erased_page(host, data_buf_start, oob_buf_start,
				     uncorrectable_cws, page,
				     max_bitflips);
पूर्ण

/*
 * helper to perक्रमm the actual page पढ़ो operation, used by ecc->पढ़ो_page(),
 * ecc->पढ़ो_oob()
 */
अटल पूर्णांक पढ़ो_page_ecc(काष्ठा qcom_nand_host *host, u8 *data_buf,
			 u8 *oob_buf, पूर्णांक page)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	u8 *data_buf_start = data_buf, *oob_buf_start = oob_buf;
	पूर्णांक i, ret;

	config_nand_page_पढ़ो(chip);

	/* queue cmd descs क्रम each codeword */
	क्रम (i = 0; i < ecc->steps; i++) अणु
		पूर्णांक data_size, oob_size;

		अगर (qcom_nandc_is_last_cw(ecc, i)) अणु
			data_size = ecc->size - ((ecc->steps - 1) << 2);
			oob_size = (ecc->steps << 2) + host->ecc_bytes_hw +
				   host->spare_bytes;
		पूर्ण अन्यथा अणु
			data_size = host->cw_data;
			oob_size = host->ecc_bytes_hw + host->spare_bytes;
		पूर्ण

		अगर (nandc->props->is_bam) अणु
			अगर (data_buf && oob_buf) अणु
				nandc_set_पढ़ो_loc(chip, i, 0, 0, data_size, 0);
				nandc_set_पढ़ो_loc(chip, i, 1, data_size,
						   oob_size, 1);
			पूर्ण अन्यथा अगर (data_buf) अणु
				nandc_set_पढ़ो_loc(chip, i, 0, 0, data_size, 1);
			पूर्ण अन्यथा अणु
				nandc_set_पढ़ो_loc(chip, i, 0, data_size,
						   oob_size, 1);
			पूर्ण
		पूर्ण

		config_nand_cw_पढ़ो(chip, true, i);

		अगर (data_buf)
			पढ़ो_data_dma(nandc, FLASH_BUF_ACC, data_buf,
				      data_size, 0);

		/*
		 * when ecc is enabled, the controller करोesn't पढ़ो the real
		 * or dummy bad block markers in each chunk. To मुख्यtain a
		 * consistent layout across RAW and ECC पढ़ोs, we just
		 * leave the real/dummy BBM offsets empty (i.e, filled with
		 * 0xffs)
		 */
		अगर (oob_buf) अणु
			पूर्णांक j;

			क्रम (j = 0; j < host->bbm_size; j++)
				*oob_buf++ = 0xff;

			पढ़ो_data_dma(nandc, FLASH_BUF_ACC + data_size,
				      oob_buf, oob_size, 0);
		पूर्ण

		अगर (data_buf)
			data_buf += data_size;
		अगर (oob_buf)
			oob_buf += oob_size;
	पूर्ण

	ret = submit_descs(nandc);
	मुक्त_descs(nandc);

	अगर (ret) अणु
		dev_err(nandc->dev, "failure to read page/oob\n");
		वापस ret;
	पूर्ण

	वापस parse_पढ़ो_errors(host, data_buf_start, oob_buf_start, page);
पूर्ण

/*
 * a helper that copies the last step/codeword of a page (containing मुक्त oob)
 * पूर्णांकo our local buffer
 */
अटल पूर्णांक copy_last_cw(काष्ठा qcom_nand_host *host, पूर्णांक page)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक size;
	पूर्णांक ret;

	clear_पढ़ो_regs(nandc);

	size = host->use_ecc ? host->cw_data : host->cw_size;

	/* prepare a clean पढ़ो buffer */
	स_रखो(nandc->data_buffer, 0xff, size);

	set_address(host, host->cw_size * (ecc->steps - 1), page);
	update_rw_regs(host, 1, true, ecc->steps - 1);

	config_nand_single_cw_page_पढ़ो(chip, host->use_ecc, ecc->steps - 1);

	पढ़ो_data_dma(nandc, FLASH_BUF_ACC, nandc->data_buffer, size, 0);

	ret = submit_descs(nandc);
	अगर (ret)
		dev_err(nandc->dev, "failed to copy last codeword\n");

	मुक्त_descs(nandc);

	वापस ret;
पूर्ण

/* implements ecc->पढ़ो_page() */
अटल पूर्णांक qcom_nandc_पढ़ो_page(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	u8 *data_buf, *oob_buf = शून्य;

	nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);
	data_buf = buf;
	oob_buf = oob_required ? chip->oob_poi : शून्य;

	clear_bam_transaction(nandc);

	वापस पढ़ो_page_ecc(host, data_buf, oob_buf, page);
पूर्ण

/* implements ecc->पढ़ो_page_raw() */
अटल पूर्णांक qcom_nandc_पढ़ो_page_raw(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				    पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक cw, ret;
	u8 *data_buf = buf, *oob_buf = chip->oob_poi;

	क्रम (cw = 0; cw < ecc->steps; cw++) अणु
		ret = qcom_nandc_पढ़ो_cw_raw(mtd, chip, data_buf, oob_buf,
					     page, cw);
		अगर (ret)
			वापस ret;

		data_buf += host->cw_data;
		oob_buf += ecc->bytes;
	पूर्ण

	वापस 0;
पूर्ण

/* implements ecc->पढ़ो_oob() */
अटल पूर्णांक qcom_nandc_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;

	clear_पढ़ो_regs(nandc);
	clear_bam_transaction(nandc);

	host->use_ecc = true;
	set_address(host, 0, page);
	update_rw_regs(host, ecc->steps, true, 0);

	वापस पढ़ो_page_ecc(host, शून्य, chip->oob_poi, page);
पूर्ण

/* implements ecc->ग_लिखो_page() */
अटल पूर्णांक qcom_nandc_ग_लिखो_page(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				 पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	u8 *data_buf, *oob_buf;
	पूर्णांक i, ret;

	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);

	clear_पढ़ो_regs(nandc);
	clear_bam_transaction(nandc);

	data_buf = (u8 *)buf;
	oob_buf = chip->oob_poi;

	host->use_ecc = true;
	update_rw_regs(host, ecc->steps, false, 0);
	config_nand_page_ग_लिखो(chip);

	क्रम (i = 0; i < ecc->steps; i++) अणु
		पूर्णांक data_size, oob_size;

		अगर (qcom_nandc_is_last_cw(ecc, i)) अणु
			data_size = ecc->size - ((ecc->steps - 1) << 2);
			oob_size = (ecc->steps << 2) + host->ecc_bytes_hw +
				   host->spare_bytes;
		पूर्ण अन्यथा अणु
			data_size = host->cw_data;
			oob_size = ecc->bytes;
		पूर्ण


		ग_लिखो_data_dma(nandc, FLASH_BUF_ACC, data_buf, data_size,
			       i == (ecc->steps - 1) ? न_अंकD_BAM_NO_EOT : 0);

		/*
		 * when ECC is enabled, we करोn't really need to ग_लिखो anything
		 * to oob क्रम the first n - 1 codewords since these oob regions
		 * just contain ECC bytes that's written by the controller
		 * itself. For the last codeword, we skip the bbm positions and
		 * ग_लिखो to the मुक्त oob area.
		 */
		अगर (qcom_nandc_is_last_cw(ecc, i)) अणु
			oob_buf += host->bbm_size;

			ग_लिखो_data_dma(nandc, FLASH_BUF_ACC + data_size,
				       oob_buf, oob_size, 0);
		पूर्ण

		config_nand_cw_ग_लिखो(chip);

		data_buf += data_size;
		oob_buf += oob_size;
	पूर्ण

	ret = submit_descs(nandc);
	अगर (ret)
		dev_err(nandc->dev, "failure to write page\n");

	मुक्त_descs(nandc);

	अगर (!ret)
		ret = nand_prog_page_end_op(chip);

	वापस ret;
पूर्ण

/* implements ecc->ग_लिखो_page_raw() */
अटल पूर्णांक qcom_nandc_ग_लिखो_page_raw(काष्ठा nand_chip *chip,
				     स्थिर uपूर्णांक8_t *buf, पूर्णांक oob_required,
				     पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	u8 *data_buf, *oob_buf;
	पूर्णांक i, ret;

	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);
	clear_पढ़ो_regs(nandc);
	clear_bam_transaction(nandc);

	data_buf = (u8 *)buf;
	oob_buf = chip->oob_poi;

	host->use_ecc = false;
	update_rw_regs(host, ecc->steps, false, 0);
	config_nand_page_ग_लिखो(chip);

	क्रम (i = 0; i < ecc->steps; i++) अणु
		पूर्णांक data_size1, data_size2, oob_size1, oob_size2;
		पूर्णांक reg_off = FLASH_BUF_ACC;

		data_size1 = mtd->ग_लिखोsize - host->cw_size * (ecc->steps - 1);
		oob_size1 = host->bbm_size;

		अगर (qcom_nandc_is_last_cw(ecc, i)) अणु
			data_size2 = ecc->size - data_size1 -
				     ((ecc->steps - 1) << 2);
			oob_size2 = (ecc->steps << 2) + host->ecc_bytes_hw +
				    host->spare_bytes;
		पूर्ण अन्यथा अणु
			data_size2 = host->cw_data - data_size1;
			oob_size2 = host->ecc_bytes_hw + host->spare_bytes;
		पूर्ण

		ग_लिखो_data_dma(nandc, reg_off, data_buf, data_size1,
			       न_अंकD_BAM_NO_EOT);
		reg_off += data_size1;
		data_buf += data_size1;

		ग_लिखो_data_dma(nandc, reg_off, oob_buf, oob_size1,
			       न_अंकD_BAM_NO_EOT);
		reg_off += oob_size1;
		oob_buf += oob_size1;

		ग_लिखो_data_dma(nandc, reg_off, data_buf, data_size2,
			       न_अंकD_BAM_NO_EOT);
		reg_off += data_size2;
		data_buf += data_size2;

		ग_लिखो_data_dma(nandc, reg_off, oob_buf, oob_size2, 0);
		oob_buf += oob_size2;

		config_nand_cw_ग_लिखो(chip);
	पूर्ण

	ret = submit_descs(nandc);
	अगर (ret)
		dev_err(nandc->dev, "failure to write raw page\n");

	मुक्त_descs(nandc);

	अगर (!ret)
		ret = nand_prog_page_end_op(chip);

	वापस ret;
पूर्ण

/*
 * implements ecc->ग_लिखो_oob()
 *
 * the न_अंकD controller cannot ग_लिखो only data or only OOB within a codeword
 * since ECC is calculated क्रम the combined codeword. So update the OOB from
 * chip->oob_poi, and pad the data area with OxFF beक्रमe writing.
 */
अटल पूर्णांक qcom_nandc_ग_लिखो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	u8 *oob = chip->oob_poi;
	पूर्णांक data_size, oob_size;
	पूर्णांक ret;

	host->use_ecc = true;
	clear_bam_transaction(nandc);

	/* calculate the data and oob size क्रम the last codeword/step */
	data_size = ecc->size - ((ecc->steps - 1) << 2);
	oob_size = mtd->oobavail;

	स_रखो(nandc->data_buffer, 0xff, host->cw_data);
	/* override new oob content to last codeword */
	mtd_ooblayout_get_databytes(mtd, nandc->data_buffer + data_size, oob,
				    0, mtd->oobavail);

	set_address(host, host->cw_size * (ecc->steps - 1), page);
	update_rw_regs(host, 1, false, 0);

	config_nand_page_ग_लिखो(chip);
	ग_लिखो_data_dma(nandc, FLASH_BUF_ACC,
		       nandc->data_buffer, data_size + oob_size, 0);
	config_nand_cw_ग_लिखो(chip);

	ret = submit_descs(nandc);

	मुक्त_descs(nandc);

	अगर (ret) अणु
		dev_err(nandc->dev, "failure to write oob\n");
		वापस -EIO;
	पूर्ण

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक qcom_nandc_block_bad(काष्ठा nand_chip *chip, loff_t ofs)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक page, ret, bbpos, bad = 0;

	page = (पूर्णांक)(ofs >> chip->page_shअगरt) & chip->pagemask;

	/*
	 * configure रेजिस्टरs क्रम a raw sub page पढ़ो, the address is set to
	 * the beginning of the last codeword, we करोn't care about पढ़ोing ecc
	 * portion of oob. we just want the first few bytes from this codeword
	 * that contains the BBM
	 */
	host->use_ecc = false;

	clear_bam_transaction(nandc);
	ret = copy_last_cw(host, page);
	अगर (ret)
		जाओ err;

	अगर (check_flash_errors(host, 1)) अणु
		dev_warn(nandc->dev, "error when trying to read BBM\n");
		जाओ err;
	पूर्ण

	bbpos = mtd->ग_लिखोsize - host->cw_size * (ecc->steps - 1);

	bad = nandc->data_buffer[bbpos] != 0xff;

	अगर (chip->options & न_अंकD_BUSWIDTH_16)
		bad = bad || (nandc->data_buffer[bbpos + 1] != 0xff);
err:
	वापस bad;
पूर्ण

अटल पूर्णांक qcom_nandc_block_markbad(काष्ठा nand_chip *chip, loff_t ofs)
अणु
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	पूर्णांक page, ret;

	clear_पढ़ो_regs(nandc);
	clear_bam_transaction(nandc);

	/*
	 * to mark the BBM as bad, we flash the entire last codeword with 0s.
	 * we करोn't care about the rest of the content in the codeword since
	 * we aren't going to use this block again
	 */
	स_रखो(nandc->data_buffer, 0x00, host->cw_size);

	page = (पूर्णांक)(ofs >> chip->page_shअगरt) & chip->pagemask;

	/* prepare ग_लिखो */
	host->use_ecc = false;
	set_address(host, host->cw_size * (ecc->steps - 1), page);
	update_rw_regs(host, 1, false, ecc->steps - 1);

	config_nand_page_ग_लिखो(chip);
	ग_लिखो_data_dma(nandc, FLASH_BUF_ACC,
		       nandc->data_buffer, host->cw_size, 0);
	config_nand_cw_ग_लिखो(chip);

	ret = submit_descs(nandc);

	मुक्त_descs(nandc);

	अगर (ret) अणु
		dev_err(nandc->dev, "failure to update BBM\n");
		वापस -EIO;
	पूर्ण

	वापस nand_prog_page_end_op(chip);
पूर्ण

/*
 * the three functions below implement chip->legacy.पढ़ो_byte(),
 * chip->legacy.पढ़ो_buf() and chip->legacy.ग_लिखो_buf() respectively. these
 * aren't used क्रम पढ़ोing/writing page data, they are used क्रम smaller data
 * like पढ़ोing	id, status etc
 */
अटल uपूर्णांक8_t qcom_nandc_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	u8 *buf = nandc->data_buffer;
	u8 ret = 0x0;

	अगर (host->last_command == न_अंकD_CMD_STATUS) अणु
		ret = host->status;

		host->status = न_अंकD_STATUS_READY | न_अंकD_STATUS_WP;

		वापस ret;
	पूर्ण

	अगर (nandc->buf_start < nandc->buf_count)
		ret = buf[nandc->buf_start++];

	वापस ret;
पूर्ण

अटल व्योम qcom_nandc_पढ़ो_buf(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	पूर्णांक real_len = min_t(माप_प्रकार, len, nandc->buf_count - nandc->buf_start);

	स_नकल(buf, nandc->data_buffer + nandc->buf_start, real_len);
	nandc->buf_start += real_len;
पूर्ण

अटल व्योम qcom_nandc_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				 पूर्णांक len)
अणु
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	पूर्णांक real_len = min_t(माप_प्रकार, len, nandc->buf_count - nandc->buf_start);

	स_नकल(nandc->data_buffer + nandc->buf_start, buf, real_len);

	nandc->buf_start += real_len;
पूर्ण

/* we support only one बाह्यal chip क्रम now */
अटल व्योम qcom_nandc_select_chip(काष्ठा nand_chip *chip, पूर्णांक chipnr)
अणु
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);

	अगर (chipnr <= 0)
		वापस;

	dev_warn(nandc->dev, "invalid chip select\n");
पूर्ण

/*
 * न_अंकD controller page layout info
 *
 * Layout with ECC enabled:
 *
 * |----------------------|  |---------------------------------|
 * |           xx.......yy|  |             *********xx.......yy|
 * |    DATA   xx..ECC..yy|  |    DATA     **SPARE**xx..ECC..yy|
 * |   (516)   xx.......yy|  |  (516-n*4)  **(n*4)**xx.......yy|
 * |           xx.......yy|  |             *********xx.......yy|
 * |----------------------|  |---------------------------------|
 *     codeword 1,2..n-1                  codeword n
 *  <---(528/532 Bytes)-->    <-------(528/532 Bytes)--------->
 *
 * n = Number of codewords in the page
 * . = ECC bytes
 * * = Spare/मुक्त bytes
 * x = Unused byte(s)
 * y = Reserved byte(s)
 *
 * 2K page: n = 4, spare = 16 bytes
 * 4K page: n = 8, spare = 32 bytes
 * 8K page: n = 16, spare = 64 bytes
 *
 * the qcom nand controller operates at a sub page/codeword level. each
 * codeword is 528 and 532 bytes क्रम 4 bit and 8 bit ECC modes respectively.
 * the number of ECC bytes vary based on the ECC strength and the bus width.
 *
 * the first n - 1 codewords contains 516 bytes of user data, the reमुख्यing
 * 12/16 bytes consist of ECC and reserved data. The nth codeword contains
 * both user data and spare(oobavail) bytes that sum up to 516 bytes.
 *
 * When we access a page with ECC enabled, the reserved bytes(s) are not
 * accessible at all. When पढ़ोing, we fill up these unपढ़ोable positions
 * with 0xffs. When writing, the controller skips writing the inaccessible
 * bytes.
 *
 * Layout with ECC disabled:
 *
 * |------------------------------|  |---------------------------------------|
 * |         yy          xx.......|  |         bb          *********xx.......|
 * |  DATA1  yy  DATA2   xx..ECC..|  |  DATA1  bb  DATA2   **SPARE**xx..ECC..|
 * | (size1) yy (size2)  xx.......|  | (size1) bb (size2)  **(n*4)**xx.......|
 * |         yy          xx.......|  |         bb          *********xx.......|
 * |------------------------------|  |---------------------------------------|
 *         codeword 1,2..n-1                        codeword n
 *  <-------(528/532 Bytes)------>    <-----------(528/532 Bytes)----------->
 *
 * n = Number of codewords in the page
 * . = ECC bytes
 * * = Spare/मुक्त bytes
 * x = Unused byte(s)
 * y = Dummy Bad Bock byte(s)
 * b = Real Bad Block byte(s)
 * size1/size2 = function of codeword size and 'n'
 *
 * when the ECC block is disabled, one reserved byte (or two क्रम 16 bit bus
 * width) is now accessible. For the first n - 1 codewords, these are dummy Bad
 * Block Markers. In the last codeword, this position contains the real BBM
 *
 * In order to have a consistent layout between RAW and ECC modes, we assume
 * the following OOB layout arrangement:
 *
 * |-----------|  |--------------------|
 * |yyxx.......|  |bb*********xx.......|
 * |yyxx..ECC..|  |bb*FREEOOB*xx..ECC..|
 * |yyxx.......|  |bb*********xx.......|
 * |yyxx.......|  |bb*********xx.......|
 * |-----------|  |--------------------|
 *  first n - 1       nth OOB region
 *  OOB regions
 *
 * n = Number of codewords in the page
 * . = ECC bytes
 * * = FREE OOB bytes
 * y = Dummy bad block byte(s) (inaccessible when ECC enabled)
 * x = Unused byte(s)
 * b = Real bad block byte(s) (inaccessible when ECC enabled)
 *
 * This layout is पढ़ो as is when ECC is disabled. When ECC is enabled, the
 * inaccessible Bad Block byte(s) are ignored when we ग_लिखो to a page/oob,
 * and assumed as 0xffs when we पढ़ो a page/oob. The ECC, unused and
 * dummy/real bad block bytes are grouped as ecc bytes (i.e, ecc->bytes is
 * the sum of the three).
 */
अटल पूर्णांक qcom_nand_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				   काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;

	अगर (section > 1)
		वापस -दुस्फल;

	अगर (!section) अणु
		oobregion->length = (ecc->bytes * (ecc->steps - 1)) +
				    host->bbm_size;
		oobregion->offset = 0;
	पूर्ण अन्यथा अणु
		oobregion->length = host->ecc_bytes_hw + host->spare_bytes;
		oobregion->offset = mtd->oobsize - oobregion->length;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_nand_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				     काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;

	अगर (section)
		वापस -दुस्फल;

	oobregion->length = ecc->steps * 4;
	oobregion->offset = ((ecc->steps - 1) * ecc->bytes) + host->bbm_size;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops qcom_nand_ooblayout_ops = अणु
	.ecc = qcom_nand_ooblayout_ecc,
	.मुक्त = qcom_nand_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक
qcom_nandc_calc_ecc_bytes(पूर्णांक step_size, पूर्णांक strength)
अणु
	वापस strength == 4 ? 12 : 16;
पूर्ण
न_अंकD_ECC_CAPS_SINGLE(qcom_nandc_ecc_caps, qcom_nandc_calc_ecc_bytes,
		     न_अंकDC_STEP_SIZE, 4, 8);

अटल पूर्णांक qcom_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा qcom_nand_host *host = to_qcom_nand_host(chip);
	काष्ठा nand_ecc_ctrl *ecc = &chip->ecc;
	काष्ठा qcom_nand_controller *nandc = get_qcom_nand_controller(chip);
	पूर्णांक cwperpage, bad_block_byte, ret;
	bool wide_bus;
	पूर्णांक ecc_mode = 1;

	/* controller only supports 512 bytes data steps */
	ecc->size = न_अंकDC_STEP_SIZE;
	wide_bus = chip->options & न_अंकD_BUSWIDTH_16 ? true : false;
	cwperpage = mtd->ग_लिखोsize / न_अंकDC_STEP_SIZE;

	/*
	 * Each CW has 4 available OOB bytes which will be रक्षित with ECC
	 * so reमुख्यing bytes can be used क्रम ECC.
	 */
	ret = nand_ecc_choose_conf(chip, &qcom_nandc_ecc_caps,
				   mtd->oobsize - (cwperpage * 4));
	अगर (ret) अणु
		dev_err(nandc->dev, "No valid ECC settings possible\n");
		वापस ret;
	पूर्ण

	अगर (ecc->strength >= 8) अणु
		/* 8 bit ECC शेषs to BCH ECC on all platक्रमms */
		host->bch_enabled = true;
		ecc_mode = 1;

		अगर (wide_bus) अणु
			host->ecc_bytes_hw = 14;
			host->spare_bytes = 0;
			host->bbm_size = 2;
		पूर्ण अन्यथा अणु
			host->ecc_bytes_hw = 13;
			host->spare_bytes = 2;
			host->bbm_size = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * अगर the controller supports BCH क्रम 4 bit ECC, the controller
		 * uses lesser bytes क्रम ECC. If RS is used, the ECC bytes is
		 * always 10 bytes
		 */
		अगर (nandc->props->ecc_modes & ECC_BCH_4BIT) अणु
			/* BCH */
			host->bch_enabled = true;
			ecc_mode = 0;

			अगर (wide_bus) अणु
				host->ecc_bytes_hw = 8;
				host->spare_bytes = 2;
				host->bbm_size = 2;
			पूर्ण अन्यथा अणु
				host->ecc_bytes_hw = 7;
				host->spare_bytes = 4;
				host->bbm_size = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* RS */
			host->ecc_bytes_hw = 10;

			अगर (wide_bus) अणु
				host->spare_bytes = 0;
				host->bbm_size = 2;
			पूर्ण अन्यथा अणु
				host->spare_bytes = 1;
				host->bbm_size = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * we consider ecc->bytes as the sum of all the non-data content in a
	 * step. It gives us a clean representation of the oob area (even अगर
	 * all the bytes aren't used क्रम ECC).It is always 16 bytes क्रम 8 bit
	 * ECC and 12 bytes क्रम 4 bit ECC
	 */
	ecc->bytes = host->ecc_bytes_hw + host->spare_bytes + host->bbm_size;

	ecc->पढ़ो_page		= qcom_nandc_पढ़ो_page;
	ecc->पढ़ो_page_raw	= qcom_nandc_पढ़ो_page_raw;
	ecc->पढ़ो_oob		= qcom_nandc_पढ़ो_oob;
	ecc->ग_लिखो_page		= qcom_nandc_ग_लिखो_page;
	ecc->ग_लिखो_page_raw	= qcom_nandc_ग_लिखो_page_raw;
	ecc->ग_लिखो_oob		= qcom_nandc_ग_लिखो_oob;

	ecc->engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;

	mtd_set_ooblayout(mtd, &qcom_nand_ooblayout_ops);

	nandc->max_cwperpage = max_t(अचिन्हित पूर्णांक, nandc->max_cwperpage,
				     cwperpage);

	/*
	 * DATA_UD_BYTES varies based on whether the पढ़ो/ग_लिखो command protects
	 * spare data with ECC too. We protect spare data by शेष, so we set
	 * it to मुख्य + spare data, which are 512 and 4 bytes respectively.
	 */
	host->cw_data = 516;

	/*
	 * total bytes in a step, either 528 bytes क्रम 4 bit ECC, or 532 bytes
	 * क्रम 8 bit ECC
	 */
	host->cw_size = host->cw_data + ecc->bytes;
	bad_block_byte = mtd->ग_लिखोsize - host->cw_size * (cwperpage - 1) + 1;

	host->cfg0 = (cwperpage - 1) << CW_PER_PAGE
				| host->cw_data << UD_SIZE_BYTES
				| 0 << DISABLE_STATUS_AFTER_WRITE
				| 5 << NUM_ADDR_CYCLES
				| host->ecc_bytes_hw << ECC_PARITY_SIZE_BYTES_RS
				| 0 << STATUS_BFR_READ
				| 1 << SET_RD_MODE_AFTER_STATUS
				| host->spare_bytes << SPARE_SIZE_BYTES;

	host->cfg1 = 7 << न_अंकD_RECOVERY_CYCLES
				| 0 <<  CS_ACTIVE_BSY
				| bad_block_byte << BAD_BLOCK_BYTE_NUM
				| 0 << BAD_BLOCK_IN_SPARE_AREA
				| 2 << WR_RD_BSY_GAP
				| wide_bus << WIDE_FLASH
				| host->bch_enabled << ENABLE_BCH_ECC;

	host->cfg0_raw = (cwperpage - 1) << CW_PER_PAGE
				| host->cw_size << UD_SIZE_BYTES
				| 5 << NUM_ADDR_CYCLES
				| 0 << SPARE_SIZE_BYTES;

	host->cfg1_raw = 7 << न_अंकD_RECOVERY_CYCLES
				| 0 << CS_ACTIVE_BSY
				| 17 << BAD_BLOCK_BYTE_NUM
				| 1 << BAD_BLOCK_IN_SPARE_AREA
				| 2 << WR_RD_BSY_GAP
				| wide_bus << WIDE_FLASH
				| 1 << DEV0_CFG1_ECC_DISABLE;

	host->ecc_bch_cfg = !host->bch_enabled << ECC_CFG_ECC_DISABLE
				| 0 << ECC_SW_RESET
				| host->cw_data << ECC_NUM_DATA_BYTES
				| 1 << ECC_FORCE_CLK_OPEN
				| ecc_mode << ECC_MODE
				| host->ecc_bytes_hw << ECC_PARITY_SIZE_BYTES_BCH;

	host->ecc_buf_cfg = 0x203 << NUM_STEPS;

	host->clrflashstatus = FS_READY_BSY_N;
	host->clrपढ़ोstatus = 0xc0;
	nandc->regs->erased_cw_detect_cfg_clr =
		cpu_to_le32(CLR_ERASED_PAGE_DET);
	nandc->regs->erased_cw_detect_cfg_set =
		cpu_to_le32(SET_ERASED_PAGE_DET);

	dev_dbg(nandc->dev,
		"cfg0 %x cfg1 %x ecc_buf_cfg %x ecc_bch cfg %x cw_size %d cw_data %d strength %d parity_bytes %d steps %d\n",
		host->cfg0, host->cfg1, host->ecc_buf_cfg, host->ecc_bch_cfg,
		host->cw_size, host->cw_data, ecc->strength, ecc->bytes,
		cwperpage);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops qcom_nandc_ops = अणु
	.attach_chip = qcom_nand_attach_chip,
पूर्ण;

अटल व्योम qcom_nandc_unalloc(काष्ठा qcom_nand_controller *nandc)
अणु
	अगर (nandc->props->is_bam) अणु
		अगर (!dma_mapping_error(nandc->dev, nandc->reg_पढ़ो_dma))
			dma_unmap_single(nandc->dev, nandc->reg_पढ़ो_dma,
					 MAX_REG_RD *
					 माप(*nandc->reg_पढ़ो_buf),
					 DMA_FROM_DEVICE);

		अगर (nandc->tx_chan)
			dma_release_channel(nandc->tx_chan);

		अगर (nandc->rx_chan)
			dma_release_channel(nandc->rx_chan);

		अगर (nandc->cmd_chan)
			dma_release_channel(nandc->cmd_chan);
	पूर्ण अन्यथा अणु
		अगर (nandc->chan)
			dma_release_channel(nandc->chan);
	पूर्ण
पूर्ण

अटल पूर्णांक qcom_nandc_alloc(काष्ठा qcom_nand_controller *nandc)
अणु
	पूर्णांक ret;

	ret = dma_set_coherent_mask(nandc->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(nandc->dev, "failed to set DMA mask\n");
		वापस ret;
	पूर्ण

	/*
	 * we use the पूर्णांकernal buffer क्रम पढ़ोing ONFI params, पढ़ोing small
	 * data like ID and status, and preक्रमming पढ़ो-copy-ग_लिखो operations
	 * when writing to a codeword partially. 532 is the maximum possible
	 * size of a codeword क्रम our nand controller
	 */
	nandc->buf_size = 532;

	nandc->data_buffer = devm_kzalloc(nandc->dev, nandc->buf_size,
					GFP_KERNEL);
	अगर (!nandc->data_buffer)
		वापस -ENOMEM;

	nandc->regs = devm_kzalloc(nandc->dev, माप(*nandc->regs),
					GFP_KERNEL);
	अगर (!nandc->regs)
		वापस -ENOMEM;

	nandc->reg_पढ़ो_buf = devm_kसुस्मृति(nandc->dev,
				MAX_REG_RD, माप(*nandc->reg_पढ़ो_buf),
				GFP_KERNEL);
	अगर (!nandc->reg_पढ़ो_buf)
		वापस -ENOMEM;

	अगर (nandc->props->is_bam) अणु
		nandc->reg_पढ़ो_dma =
			dma_map_single(nandc->dev, nandc->reg_पढ़ो_buf,
				       MAX_REG_RD *
				       माप(*nandc->reg_पढ़ो_buf),
				       DMA_FROM_DEVICE);
		अगर (dma_mapping_error(nandc->dev, nandc->reg_पढ़ो_dma)) अणु
			dev_err(nandc->dev, "failed to DMA MAP reg buffer\n");
			वापस -EIO;
		पूर्ण

		nandc->tx_chan = dma_request_chan(nandc->dev, "tx");
		अगर (IS_ERR(nandc->tx_chan)) अणु
			ret = PTR_ERR(nandc->tx_chan);
			nandc->tx_chan = शून्य;
			dev_err_probe(nandc->dev, ret,
				      "tx DMA channel request failed\n");
			जाओ unalloc;
		पूर्ण

		nandc->rx_chan = dma_request_chan(nandc->dev, "rx");
		अगर (IS_ERR(nandc->rx_chan)) अणु
			ret = PTR_ERR(nandc->rx_chan);
			nandc->rx_chan = शून्य;
			dev_err_probe(nandc->dev, ret,
				      "rx DMA channel request failed\n");
			जाओ unalloc;
		पूर्ण

		nandc->cmd_chan = dma_request_chan(nandc->dev, "cmd");
		अगर (IS_ERR(nandc->cmd_chan)) अणु
			ret = PTR_ERR(nandc->cmd_chan);
			nandc->cmd_chan = शून्य;
			dev_err_probe(nandc->dev, ret,
				      "cmd DMA channel request failed\n");
			जाओ unalloc;
		पूर्ण

		/*
		 * Initially allocate BAM transaction to पढ़ो ONFI param page.
		 * After detecting all the devices, this BAM transaction will
		 * be मुक्तd and the next BAM tranasction will be allocated with
		 * maximum codeword size
		 */
		nandc->max_cwperpage = 1;
		nandc->bam_txn = alloc_bam_transaction(nandc);
		अगर (!nandc->bam_txn) अणु
			dev_err(nandc->dev,
				"failed to allocate bam transaction\n");
			ret = -ENOMEM;
			जाओ unalloc;
		पूर्ण
	पूर्ण अन्यथा अणु
		nandc->chan = dma_request_chan(nandc->dev, "rxtx");
		अगर (IS_ERR(nandc->chan)) अणु
			ret = PTR_ERR(nandc->chan);
			nandc->chan = शून्य;
			dev_err_probe(nandc->dev, ret,
				      "rxtx DMA channel request failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	INIT_LIST_HEAD(&nandc->desc_list);
	INIT_LIST_HEAD(&nandc->host_list);

	nand_controller_init(&nandc->controller);
	nandc->controller.ops = &qcom_nandc_ops;

	वापस 0;
unalloc:
	qcom_nandc_unalloc(nandc);
	वापस ret;
पूर्ण

/* one समय setup of a few nand controller रेजिस्टरs */
अटल पूर्णांक qcom_nandc_setup(काष्ठा qcom_nand_controller *nandc)
अणु
	u32 nand_ctrl;

	/* समाप्त onenand */
	अगर (!nandc->props->is_qpic)
		nandc_ग_लिखो(nandc, SFLASHC_BURST_CFG, 0);

	अगर (!nandc->props->qpic_v2)
		nandc_ग_लिखो(nandc, dev_cmd_reg_addr(nandc, न_अंकD_DEV_CMD_VLD),
			    न_अंकD_DEV_CMD_VLD_VAL);

	/* enable ADM or BAM DMA */
	अगर (nandc->props->is_bam) अणु
		nand_ctrl = nandc_पढ़ो(nandc, न_अंकD_CTRL);

		/*
		 *न_अंकD_CTRL is an operational रेजिस्टरs, and CPU
		 * access to operational रेजिस्टरs are पढ़ो only
		 * in BAM mode. So update the न_अंकD_CTRL रेजिस्टर
		 * only अगर it is not in BAM mode. In most हालs BAM
		 * mode will be enabled in bootloader
		 */
		अगर (!(nand_ctrl & BAM_MODE_EN))
			nandc_ग_लिखो(nandc, न_अंकD_CTRL, nand_ctrl | BAM_MODE_EN);
	पूर्ण अन्यथा अणु
		nandc_ग_लिखो(nandc, न_अंकD_FLASH_CHIP_SELECT, DM_EN);
	पूर्ण

	/* save the original values of these रेजिस्टरs */
	अगर (!nandc->props->qpic_v2) अणु
		nandc->cmd1 = nandc_पढ़ो(nandc, dev_cmd_reg_addr(nandc, न_अंकD_DEV_CMD1));
		nandc->vld = न_अंकD_DEV_CMD_VLD_VAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर probes[] = अणु "qcomsmem", शून्य पूर्ण;

अटल पूर्णांक qcom_nand_host_init_and_रेजिस्टर(काष्ठा qcom_nand_controller *nandc,
					    काष्ठा qcom_nand_host *host,
					    काष्ठा device_node *dn)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा device *dev = nandc->dev;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(dn, "reg", &host->cs);
	अगर (ret) अणु
		dev_err(dev, "can't get chip-select\n");
		वापस -ENXIO;
	पूर्ण

	nand_set_flash_node(chip, dn);
	mtd->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "qcom_nand.%d", host->cs);
	अगर (!mtd->name)
		वापस -ENOMEM;

	mtd->owner = THIS_MODULE;
	mtd->dev.parent = dev;

	chip->legacy.cmdfunc	= qcom_nandc_command;
	chip->legacy.select_chip	= qcom_nandc_select_chip;
	chip->legacy.पढ़ो_byte	= qcom_nandc_पढ़ो_byte;
	chip->legacy.पढ़ो_buf	= qcom_nandc_पढ़ो_buf;
	chip->legacy.ग_लिखो_buf	= qcom_nandc_ग_लिखो_buf;
	chip->legacy.set_features	= nand_get_set_features_notsupp;
	chip->legacy.get_features	= nand_get_set_features_notsupp;

	/*
	 * the bad block marker is पढ़ोable only when we पढ़ो the last codeword
	 * of a page with ECC disabled. currently, the nand_base and nand_bbt
	 * helpers करोn't allow us to पढ़ो BB from a nand chip with ECC
	 * disabled (MTD_OPS_PLACE_OOB is set by शेष). use the block_bad
	 * and block_markbad helpers until we permanently चयन to using
	 * MTD_OPS_RAW क्रम all drivers (with the help of badblockbits)
	 */
	chip->legacy.block_bad		= qcom_nandc_block_bad;
	chip->legacy.block_markbad	= qcom_nandc_block_markbad;

	chip->controller = &nandc->controller;
	chip->options |= न_अंकD_NO_SUBPAGE_WRITE | न_अंकD_USES_DMA |
			 न_अंकD_SKIP_BBTSCAN;

	/* set up initial status value */
	host->status = न_अंकD_STATUS_READY | न_अंकD_STATUS_WP;

	ret = nand_scan(chip, 1);
	अगर (ret)
		वापस ret;

	अगर (nandc->props->is_bam) अणु
		मुक्त_bam_transaction(nandc);
		nandc->bam_txn = alloc_bam_transaction(nandc);
		अगर (!nandc->bam_txn) अणु
			dev_err(nandc->dev,
				"failed to allocate bam transaction\n");
			nand_cleanup(chip);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	ret = mtd_device_parse_रेजिस्टर(mtd, probes, शून्य, शून्य, 0);
	अगर (ret)
		nand_cleanup(chip);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_probe_nand_devices(काष्ठा qcom_nand_controller *nandc)
अणु
	काष्ठा device *dev = nandc->dev;
	काष्ठा device_node *dn = dev->of_node, *child;
	काष्ठा qcom_nand_host *host;
	पूर्णांक ret = -ENODEV;

	क्रम_each_available_child_of_node(dn, child) अणु
		host = devm_kzalloc(dev, माप(*host), GFP_KERNEL);
		अगर (!host) अणु
			of_node_put(child);
			वापस -ENOMEM;
		पूर्ण

		ret = qcom_nand_host_init_and_रेजिस्टर(nandc, host, child);
		अगर (ret) अणु
			devm_kमुक्त(dev, host);
			जारी;
		पूर्ण

		list_add_tail(&host->node, &nandc->host_list);
	पूर्ण

	वापस ret;
पूर्ण

/* parse custom DT properties here */
अटल पूर्णांक qcom_nandc_parse_dt(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_nand_controller *nandc = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *np = nandc->dev->of_node;
	पूर्णांक ret;

	अगर (!nandc->props->is_bam) अणु
		ret = of_property_पढ़ो_u32(np, "qcom,cmd-crci",
					   &nandc->cmd_crci);
		अगर (ret) अणु
			dev_err(nandc->dev, "command CRCI unspecified\n");
			वापस ret;
		पूर्ण

		ret = of_property_पढ़ो_u32(np, "qcom,data-crci",
					   &nandc->data_crci);
		अगर (ret) अणु
			dev_err(nandc->dev, "data CRCI unspecified\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_nandc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_nand_controller *nandc;
	स्थिर व्योम *dev_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक ret;

	nandc = devm_kzalloc(&pdev->dev, माप(*nandc), GFP_KERNEL);
	अगर (!nandc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, nandc);
	nandc->dev = dev;

	dev_data = of_device_get_match_data(dev);
	अगर (!dev_data) अणु
		dev_err(&pdev->dev, "failed to get device data\n");
		वापस -ENODEV;
	पूर्ण

	nandc->props = dev_data;

	nandc->core_clk = devm_clk_get(dev, "core");
	अगर (IS_ERR(nandc->core_clk))
		वापस PTR_ERR(nandc->core_clk);

	nandc->aon_clk = devm_clk_get(dev, "aon");
	अगर (IS_ERR(nandc->aon_clk))
		वापस PTR_ERR(nandc->aon_clk);

	ret = qcom_nandc_parse_dt(pdev);
	अगर (ret)
		वापस ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	nandc->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(nandc->base))
		वापस PTR_ERR(nandc->base);

	nandc->base_phys = res->start;
	nandc->base_dma = dma_map_resource(dev, res->start,
					   resource_size(res),
					   DMA_BIसूचीECTIONAL, 0);
	अगर (dma_mapping_error(dev, nandc->base_dma))
		वापस -ENXIO;

	ret = qcom_nandc_alloc(nandc);
	अगर (ret)
		जाओ err_nandc_alloc;

	ret = clk_prepare_enable(nandc->core_clk);
	अगर (ret)
		जाओ err_core_clk;

	ret = clk_prepare_enable(nandc->aon_clk);
	अगर (ret)
		जाओ err_aon_clk;

	ret = qcom_nandc_setup(nandc);
	अगर (ret)
		जाओ err_setup;

	ret = qcom_probe_nand_devices(nandc);
	अगर (ret)
		जाओ err_setup;

	वापस 0;

err_setup:
	clk_disable_unprepare(nandc->aon_clk);
err_aon_clk:
	clk_disable_unprepare(nandc->core_clk);
err_core_clk:
	qcom_nandc_unalloc(nandc);
err_nandc_alloc:
	dma_unmap_resource(dev, res->start, resource_size(res),
			   DMA_BIसूचीECTIONAL, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_nandc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_nand_controller *nandc = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	काष्ठा qcom_nand_host *host;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;

	list_क्रम_each_entry(host, &nandc->host_list, node) अणु
		chip = &host->chip;
		ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
		WARN_ON(ret);
		nand_cleanup(chip);
	पूर्ण

	qcom_nandc_unalloc(nandc);

	clk_disable_unprepare(nandc->aon_clk);
	clk_disable_unprepare(nandc->core_clk);

	dma_unmap_resource(&pdev->dev, nandc->base_dma, resource_size(res),
			   DMA_BIसूचीECTIONAL, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा qcom_nandc_props ipq806x_nandc_props = अणु
	.ecc_modes = (ECC_RS_4BIT | ECC_BCH_8BIT),
	.is_bam = false,
	.dev_cmd_reg_start = 0x0,
पूर्ण;

अटल स्थिर काष्ठा qcom_nandc_props ipq4019_nandc_props = अणु
	.ecc_modes = (ECC_BCH_4BIT | ECC_BCH_8BIT),
	.is_bam = true,
	.is_qpic = true,
	.dev_cmd_reg_start = 0x0,
पूर्ण;

अटल स्थिर काष्ठा qcom_nandc_props ipq8074_nandc_props = अणु
	.ecc_modes = (ECC_BCH_4BIT | ECC_BCH_8BIT),
	.is_bam = true,
	.is_qpic = true,
	.dev_cmd_reg_start = 0x7000,
पूर्ण;

अटल स्थिर काष्ठा qcom_nandc_props sdx55_nandc_props = अणु
	.ecc_modes = (ECC_BCH_4BIT | ECC_BCH_8BIT),
	.is_bam = true,
	.is_qpic = true,
	.qpic_v2 = true,
	.dev_cmd_reg_start = 0x7000,
पूर्ण;

/*
 * data will hold a काष्ठा poपूर्णांकer containing more dअगरferences once we support
 * more controller variants
 */
अटल स्थिर काष्ठा of_device_id qcom_nandc_of_match[] = अणु
	अणु
		.compatible = "qcom,ipq806x-nand",
		.data = &ipq806x_nandc_props,
	पूर्ण,
	अणु
		.compatible = "qcom,ipq4019-nand",
		.data = &ipq4019_nandc_props,
	पूर्ण,
	अणु
		.compatible = "qcom,ipq6018-nand",
		.data = &ipq8074_nandc_props,
	पूर्ण,
	अणु
		.compatible = "qcom,ipq8074-nand",
		.data = &ipq8074_nandc_props,
	पूर्ण,
	अणु
		.compatible = "qcom,sdx55-nand",
		.data = &sdx55_nandc_props,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_nandc_of_match);

अटल काष्ठा platक्रमm_driver qcom_nandc_driver = अणु
	.driver = अणु
		.name = "qcom-nandc",
		.of_match_table = qcom_nandc_of_match,
	पूर्ण,
	.probe   = qcom_nandc_probe,
	.हटाओ  = qcom_nandc_हटाओ,
पूर्ण;
module_platक्रमm_driver(qcom_nandc_driver);

MODULE_AUTHOR("Archit Taneja <architt@codeaurora.org>");
MODULE_DESCRIPTION("Qualcomm NAND Controller driver");
MODULE_LICENSE("GPL v2");
