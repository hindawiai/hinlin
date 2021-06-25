<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2010-2015 Broadcom Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/ioport.h>
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mm.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/log2.h>

#समावेश "brcmnand.h"

/*
 * This flag controls अगर WP stays on between erase/ग_लिखो commands to mitigate
 * flash corruption due to घातer glitches. Values:
 * 0: न_अंकD_WP is not used or not available
 * 1: न_अंकD_WP is set by शेष, cleared क्रम erase/ग_लिखो operations
 * 2: न_अंकD_WP is always cleared
 */
अटल पूर्णांक wp_on = 1;
module_param(wp_on, पूर्णांक, 0444);

/***********************************************************************
 * Definitions
 ***********************************************************************/

#घोषणा DRV_NAME			"brcmnand"

#घोषणा CMD_शून्य			0x00
#घोषणा CMD_PAGE_READ			0x01
#घोषणा CMD_SPARE_AREA_READ		0x02
#घोषणा CMD_STATUS_READ			0x03
#घोषणा CMD_PROGRAM_PAGE		0x04
#घोषणा CMD_PROGRAM_SPARE_AREA		0x05
#घोषणा CMD_COPY_BACK			0x06
#घोषणा CMD_DEVICE_ID_READ		0x07
#घोषणा CMD_BLOCK_ERASE			0x08
#घोषणा CMD_FLASH_RESET			0x09
#घोषणा CMD_BLOCKS_LOCK			0x0a
#घोषणा CMD_BLOCKS_LOCK_DOWN		0x0b
#घोषणा CMD_BLOCKS_UNLOCK		0x0c
#घोषणा CMD_READ_BLOCKS_LOCK_STATUS	0x0d
#घोषणा CMD_PARAMETER_READ		0x0e
#घोषणा CMD_PARAMETER_CHANGE_COL	0x0f
#घोषणा CMD_LOW_LEVEL_OP		0x10

काष्ठा brcm_nand_dma_desc अणु
	u32 next_desc;
	u32 next_desc_ext;
	u32 cmd_irq;
	u32 dram_addr;
	u32 dram_addr_ext;
	u32 tfr_len;
	u32 total_len;
	u32 flash_addr;
	u32 flash_addr_ext;
	u32 cs;
	u32 pad2[5];
	u32 status_valid;
पूर्ण __packed;

/* Bitfields क्रम brcm_nand_dma_desc::status_valid */
#घोषणा FLASH_DMA_ECC_ERROR	(1 << 8)
#घोषणा FLASH_DMA_CORR_ERROR	(1 << 9)

/* Bitfields क्रम DMA_MODE */
#घोषणा FLASH_DMA_MODE_STOP_ON_ERROR	BIT(1) /* stop in Uncorr ECC error */
#घोषणा FLASH_DMA_MODE_MODE		BIT(0) /* link list */
#घोषणा FLASH_DMA_MODE_MASK		(FLASH_DMA_MODE_STOP_ON_ERROR |	\
						FLASH_DMA_MODE_MODE)

/* 512B flash cache in the न_अंकD controller HW */
#घोषणा FC_SHIFT		9U
#घोषणा FC_BYTES		512U
#घोषणा FC_WORDS		(FC_BYTES >> 2)

#घोषणा BRCMन_अंकD_MIN_PAGESIZE	512
#घोषणा BRCMन_अंकD_MIN_BLOCKSIZE	(8 * 1024)
#घोषणा BRCMन_अंकD_MIN_DEVSIZE	(4ULL * 1024 * 1024)

#घोषणा न_अंकD_CTRL_RDY			(INTFC_CTLR_READY | INTFC_FLASH_READY)
#घोषणा न_अंकD_POLL_STATUS_TIMEOUT_MS	100

#घोषणा EDU_CMD_WRITE          0x00
#घोषणा EDU_CMD_READ           0x01
#घोषणा EDU_STATUS_ACTIVE      BIT(0)
#घोषणा EDU_ERR_STATUS_ERRACK  BIT(0)
#घोषणा EDU_DONE_MASK		GENMASK(1, 0)

#घोषणा EDU_CONFIG_MODE_न_अंकD   BIT(0)
#घोषणा EDU_CONFIG_SWAP_BYTE   BIT(1)
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा EDU_CONFIG_SWAP_CFG     EDU_CONFIG_SWAP_BYTE
#अन्यथा
#घोषणा EDU_CONFIG_SWAP_CFG     0
#पूर्ण_अगर

/* edu रेजिस्टरs */
क्रमागत edu_reg अणु
	EDU_CONFIG = 0,
	EDU_DRAM_ADDR,
	EDU_EXT_ADDR,
	EDU_LENGTH,
	EDU_CMD,
	EDU_STOP,
	EDU_STATUS,
	EDU_DONE,
	EDU_ERR_STATUS,
पूर्ण;

अटल स्थिर u16  edu_regs[] = अणु
	[EDU_CONFIG] = 0x00,
	[EDU_DRAM_ADDR] = 0x04,
	[EDU_EXT_ADDR] = 0x08,
	[EDU_LENGTH] = 0x0c,
	[EDU_CMD] = 0x10,
	[EDU_STOP] = 0x14,
	[EDU_STATUS] = 0x18,
	[EDU_DONE] = 0x1c,
	[EDU_ERR_STATUS] = 0x20,
पूर्ण;

/* flash_dma रेजिस्टरs */
क्रमागत flash_dma_reg अणु
	FLASH_DMA_REVISION = 0,
	FLASH_DMA_FIRST_DESC,
	FLASH_DMA_FIRST_DESC_EXT,
	FLASH_DMA_CTRL,
	FLASH_DMA_MODE,
	FLASH_DMA_STATUS,
	FLASH_DMA_INTERRUPT_DESC,
	FLASH_DMA_INTERRUPT_DESC_EXT,
	FLASH_DMA_ERROR_STATUS,
	FLASH_DMA_CURRENT_DESC,
	FLASH_DMA_CURRENT_DESC_EXT,
पूर्ण;

/* flash_dma रेजिस्टरs v0*/
अटल स्थिर u16 flash_dma_regs_v0[] = अणु
	[FLASH_DMA_REVISION]		= 0x00,
	[FLASH_DMA_FIRST_DESC]		= 0x04,
	[FLASH_DMA_CTRL]		= 0x08,
	[FLASH_DMA_MODE]		= 0x0c,
	[FLASH_DMA_STATUS]		= 0x10,
	[FLASH_DMA_INTERRUPT_DESC]	= 0x14,
	[FLASH_DMA_ERROR_STATUS]	= 0x18,
	[FLASH_DMA_CURRENT_DESC]	= 0x1c,
पूर्ण;

/* flash_dma रेजिस्टरs v1*/
अटल स्थिर u16 flash_dma_regs_v1[] = अणु
	[FLASH_DMA_REVISION]		= 0x00,
	[FLASH_DMA_FIRST_DESC]		= 0x04,
	[FLASH_DMA_FIRST_DESC_EXT]	= 0x08,
	[FLASH_DMA_CTRL]		= 0x0c,
	[FLASH_DMA_MODE]		= 0x10,
	[FLASH_DMA_STATUS]		= 0x14,
	[FLASH_DMA_INTERRUPT_DESC]	= 0x18,
	[FLASH_DMA_INTERRUPT_DESC_EXT]	= 0x1c,
	[FLASH_DMA_ERROR_STATUS]	= 0x20,
	[FLASH_DMA_CURRENT_DESC]	= 0x24,
	[FLASH_DMA_CURRENT_DESC_EXT]	= 0x28,
पूर्ण;

/* flash_dma रेजिस्टरs v4 */
अटल स्थिर u16 flash_dma_regs_v4[] = अणु
	[FLASH_DMA_REVISION]		= 0x00,
	[FLASH_DMA_FIRST_DESC]		= 0x08,
	[FLASH_DMA_FIRST_DESC_EXT]	= 0x0c,
	[FLASH_DMA_CTRL]		= 0x10,
	[FLASH_DMA_MODE]		= 0x14,
	[FLASH_DMA_STATUS]		= 0x18,
	[FLASH_DMA_INTERRUPT_DESC]	= 0x20,
	[FLASH_DMA_INTERRUPT_DESC_EXT]	= 0x24,
	[FLASH_DMA_ERROR_STATUS]	= 0x28,
	[FLASH_DMA_CURRENT_DESC]	= 0x30,
	[FLASH_DMA_CURRENT_DESC_EXT]	= 0x34,
पूर्ण;

/* Controller feature flags */
क्रमागत अणु
	BRCMन_अंकD_HAS_1K_SECTORS			= BIT(0),
	BRCMन_अंकD_HAS_PREFETCH			= BIT(1),
	BRCMन_अंकD_HAS_CACHE_MODE			= BIT(2),
	BRCMन_अंकD_HAS_WP				= BIT(3),
पूर्ण;

काष्ठा brcmnand_host;

काष्ठा brcmnand_controller अणु
	काष्ठा device		*dev;
	काष्ठा nand_controller	controller;
	व्योम __iomem		*nand_base;
	व्योम __iomem		*nand_fc; /* flash cache */
	व्योम __iomem		*flash_dma_base;
	अचिन्हित पूर्णांक		irq;
	अचिन्हित पूर्णांक		dma_irq;
	पूर्णांक			nand_version;

	/* Some SoCs provide custom पूर्णांकerrupt status रेजिस्टर(s) */
	काष्ठा brcmnand_soc	*soc;

	/* Some SoCs have a gateable घड़ी क्रम the controller */
	काष्ठा clk		*clk;

	पूर्णांक			cmd_pending;
	bool			dma_pending;
	bool                    edu_pending;
	काष्ठा completion	करोne;
	काष्ठा completion	dma_करोne;
	काष्ठा completion       edu_करोne;

	/* List of न_अंकD hosts (one क्रम each chip-select) */
	काष्ठा list_head host_list;

	/* EDU info, per-transaction */
	स्थिर u16               *edu_offsets;
	व्योम __iomem            *edu_base;
	पूर्णांक			edu_irq;
	पूर्णांक                     edu_count;
	u64                     edu_dram_addr;
	u32                     edu_ext_addr;
	u32                     edu_cmd;
	u32                     edu_config;
	पूर्णांक			sas; /* spare area size, per flash cache */
	पूर्णांक			sector_size_1k;
	u8			*oob;

	/* flash_dma reg */
	स्थिर u16		*flash_dma_offsets;
	काष्ठा brcm_nand_dma_desc *dma_desc;
	dma_addr_t		dma_pa;

	पूर्णांक (*dma_trans)(काष्ठा brcmnand_host *host, u64 addr, u32 *buf,
			 u8 *oob, u32 len, u8 dma_cmd);

	/* in-memory cache of the FLASH_CACHE, used only क्रम some commands */
	u8			flash_cache[FC_BYTES];

	/* Controller revision details */
	स्थिर u16		*reg_offsets;
	अचिन्हित पूर्णांक		reg_spacing; /* between CS1, CS2, ... regs */
	स्थिर u8		*cs_offsets; /* within each chip-select */
	स्थिर u8		*cs0_offsets; /* within CS0, अगर dअगरferent */
	अचिन्हित पूर्णांक		max_block_size;
	स्थिर अचिन्हित पूर्णांक	*block_sizes;
	अचिन्हित पूर्णांक		max_page_size;
	स्थिर अचिन्हित पूर्णांक	*page_sizes;
	अचिन्हित पूर्णांक		page_size_shअगरt;
	अचिन्हित पूर्णांक		max_oob;
	u32			features;

	/* क्रम low-घातer standby/resume only */
	u32			nand_cs_nand_select;
	u32			nand_cs_nand_xor;
	u32			corr_stat_threshold;
	u32			flash_dma_mode;
	u32                     flash_edu_mode;
	bool			pio_poll_mode;
पूर्ण;

काष्ठा brcmnand_cfg अणु
	u64			device_size;
	अचिन्हित पूर्णांक		block_size;
	अचिन्हित पूर्णांक		page_size;
	अचिन्हित पूर्णांक		spare_area_size;
	अचिन्हित पूर्णांक		device_width;
	अचिन्हित पूर्णांक		col_adr_bytes;
	अचिन्हित पूर्णांक		blk_adr_bytes;
	अचिन्हित पूर्णांक		ful_adr_bytes;
	अचिन्हित पूर्णांक		sector_size_1k;
	अचिन्हित पूर्णांक		ecc_level;
	/* use क्रम low-घातer standby/resume only */
	u32			acc_control;
	u32			config;
	u32			config_ext;
	u32			timing_1;
	u32			timing_2;
पूर्ण;

काष्ठा brcmnand_host अणु
	काष्ठा list_head	node;

	काष्ठा nand_chip	chip;
	काष्ठा platक्रमm_device	*pdev;
	पूर्णांक			cs;

	अचिन्हित पूर्णांक		last_cmd;
	अचिन्हित पूर्णांक		last_byte;
	u64			last_addr;
	काष्ठा brcmnand_cfg	hwcfg;
	काष्ठा brcmnand_controller *ctrl;
पूर्ण;

क्रमागत brcmnand_reg अणु
	BRCMन_अंकD_CMD_START = 0,
	BRCMन_अंकD_CMD_EXT_ADDRESS,
	BRCMन_अंकD_CMD_ADDRESS,
	BRCMन_अंकD_INTFC_STATUS,
	BRCMन_अंकD_CS_SELECT,
	BRCMन_अंकD_CS_XOR,
	BRCMन_अंकD_LL_OP,
	BRCMन_अंकD_CS0_BASE,
	BRCMन_अंकD_CS1_BASE,		/* CS1 regs, अगर non-contiguous */
	BRCMन_अंकD_CORR_THRESHOLD,
	BRCMन_अंकD_CORR_THRESHOLD_EXT,
	BRCMन_अंकD_UNCORR_COUNT,
	BRCMन_अंकD_CORR_COUNT,
	BRCMन_अंकD_CORR_EXT_ADDR,
	BRCMन_अंकD_CORR_ADDR,
	BRCMन_अंकD_UNCORR_EXT_ADDR,
	BRCMन_अंकD_UNCORR_ADDR,
	BRCMन_अंकD_SEMAPHORE,
	BRCMन_अंकD_ID,
	BRCMन_अंकD_ID_EXT,
	BRCMन_अंकD_LL_RDATA,
	BRCMन_अंकD_OOB_READ_BASE,
	BRCMन_अंकD_OOB_READ_10_BASE,	/* offset 0x10, अगर non-contiguous */
	BRCMन_अंकD_OOB_WRITE_BASE,
	BRCMन_अंकD_OOB_WRITE_10_BASE,	/* offset 0x10, अगर non-contiguous */
	BRCMन_अंकD_FC_BASE,
पूर्ण;

/* BRCMन_अंकD v2.1-v2.2 */
अटल स्थिर u16 brcmnand_regs_v21[] = अणु
	[BRCMन_अंकD_CMD_START]		=  0x04,
	[BRCMन_अंकD_CMD_EXT_ADDRESS]	=  0x08,
	[BRCMन_अंकD_CMD_ADDRESS]		=  0x0c,
	[BRCMन_अंकD_INTFC_STATUS]		=  0x5c,
	[BRCMन_अंकD_CS_SELECT]		=  0x14,
	[BRCMन_अंकD_CS_XOR]		=  0x18,
	[BRCMन_अंकD_LL_OP]		=     0,
	[BRCMन_अंकD_CS0_BASE]		=  0x40,
	[BRCMन_अंकD_CS1_BASE]		=     0,
	[BRCMन_अंकD_CORR_THRESHOLD]	=     0,
	[BRCMन_अंकD_CORR_THRESHOLD_EXT]	=     0,
	[BRCMन_अंकD_UNCORR_COUNT]		=     0,
	[BRCMन_अंकD_CORR_COUNT]		=     0,
	[BRCMन_अंकD_CORR_EXT_ADDR]	=  0x60,
	[BRCMन_अंकD_CORR_ADDR]		=  0x64,
	[BRCMन_अंकD_UNCORR_EXT_ADDR]	=  0x68,
	[BRCMन_अंकD_UNCORR_ADDR]		=  0x6c,
	[BRCMन_अंकD_SEMAPHORE]		=  0x50,
	[BRCMन_अंकD_ID]			=  0x54,
	[BRCMन_अंकD_ID_EXT]		=     0,
	[BRCMन_अंकD_LL_RDATA]		=     0,
	[BRCMन_अंकD_OOB_READ_BASE]	=  0x20,
	[BRCMन_अंकD_OOB_READ_10_BASE]	=     0,
	[BRCMन_अंकD_OOB_WRITE_BASE]	=  0x30,
	[BRCMन_अंकD_OOB_WRITE_10_BASE]	=     0,
	[BRCMन_अंकD_FC_BASE]		= 0x200,
पूर्ण;

/* BRCMन_अंकD v3.3-v4.0 */
अटल स्थिर u16 brcmnand_regs_v33[] = अणु
	[BRCMन_अंकD_CMD_START]		=  0x04,
	[BRCMन_अंकD_CMD_EXT_ADDRESS]	=  0x08,
	[BRCMन_अंकD_CMD_ADDRESS]		=  0x0c,
	[BRCMन_अंकD_INTFC_STATUS]		=  0x6c,
	[BRCMन_अंकD_CS_SELECT]		=  0x14,
	[BRCMन_अंकD_CS_XOR]		=  0x18,
	[BRCMन_अंकD_LL_OP]		= 0x178,
	[BRCMन_अंकD_CS0_BASE]		=  0x40,
	[BRCMन_अंकD_CS1_BASE]		=  0xd0,
	[BRCMन_अंकD_CORR_THRESHOLD]	=  0x84,
	[BRCMन_अंकD_CORR_THRESHOLD_EXT]	=     0,
	[BRCMन_अंकD_UNCORR_COUNT]		=     0,
	[BRCMन_अंकD_CORR_COUNT]		=     0,
	[BRCMन_अंकD_CORR_EXT_ADDR]	=  0x70,
	[BRCMन_अंकD_CORR_ADDR]		=  0x74,
	[BRCMन_अंकD_UNCORR_EXT_ADDR]	=  0x78,
	[BRCMन_अंकD_UNCORR_ADDR]		=  0x7c,
	[BRCMन_अंकD_SEMAPHORE]		=  0x58,
	[BRCMन_अंकD_ID]			=  0x60,
	[BRCMन_अंकD_ID_EXT]		=  0x64,
	[BRCMन_अंकD_LL_RDATA]		= 0x17c,
	[BRCMन_अंकD_OOB_READ_BASE]	=  0x20,
	[BRCMन_अंकD_OOB_READ_10_BASE]	= 0x130,
	[BRCMन_अंकD_OOB_WRITE_BASE]	=  0x30,
	[BRCMन_अंकD_OOB_WRITE_10_BASE]	=     0,
	[BRCMन_अंकD_FC_BASE]		= 0x200,
पूर्ण;

/* BRCMन_अंकD v5.0 */
अटल स्थिर u16 brcmnand_regs_v50[] = अणु
	[BRCMन_अंकD_CMD_START]		=  0x04,
	[BRCMन_अंकD_CMD_EXT_ADDRESS]	=  0x08,
	[BRCMन_अंकD_CMD_ADDRESS]		=  0x0c,
	[BRCMन_अंकD_INTFC_STATUS]		=  0x6c,
	[BRCMन_अंकD_CS_SELECT]		=  0x14,
	[BRCMन_अंकD_CS_XOR]		=  0x18,
	[BRCMन_अंकD_LL_OP]		= 0x178,
	[BRCMन_अंकD_CS0_BASE]		=  0x40,
	[BRCMन_अंकD_CS1_BASE]		=  0xd0,
	[BRCMन_अंकD_CORR_THRESHOLD]	=  0x84,
	[BRCMन_अंकD_CORR_THRESHOLD_EXT]	=     0,
	[BRCMन_अंकD_UNCORR_COUNT]		=     0,
	[BRCMन_अंकD_CORR_COUNT]		=     0,
	[BRCMन_अंकD_CORR_EXT_ADDR]	=  0x70,
	[BRCMन_अंकD_CORR_ADDR]		=  0x74,
	[BRCMन_अंकD_UNCORR_EXT_ADDR]	=  0x78,
	[BRCMन_अंकD_UNCORR_ADDR]		=  0x7c,
	[BRCMन_अंकD_SEMAPHORE]		=  0x58,
	[BRCMन_अंकD_ID]			=  0x60,
	[BRCMन_अंकD_ID_EXT]		=  0x64,
	[BRCMन_अंकD_LL_RDATA]		= 0x17c,
	[BRCMन_अंकD_OOB_READ_BASE]	=  0x20,
	[BRCMन_अंकD_OOB_READ_10_BASE]	= 0x130,
	[BRCMन_अंकD_OOB_WRITE_BASE]	=  0x30,
	[BRCMन_अंकD_OOB_WRITE_10_BASE]	= 0x140,
	[BRCMन_अंकD_FC_BASE]		= 0x200,
पूर्ण;

/* BRCMन_अंकD v6.0 - v7.1 */
अटल स्थिर u16 brcmnand_regs_v60[] = अणु
	[BRCMन_अंकD_CMD_START]		=  0x04,
	[BRCMन_अंकD_CMD_EXT_ADDRESS]	=  0x08,
	[BRCMन_अंकD_CMD_ADDRESS]		=  0x0c,
	[BRCMन_अंकD_INTFC_STATUS]		=  0x14,
	[BRCMन_अंकD_CS_SELECT]		=  0x18,
	[BRCMन_अंकD_CS_XOR]		=  0x1c,
	[BRCMन_अंकD_LL_OP]		=  0x20,
	[BRCMन_अंकD_CS0_BASE]		=  0x50,
	[BRCMन_अंकD_CS1_BASE]		=     0,
	[BRCMन_अंकD_CORR_THRESHOLD]	=  0xc0,
	[BRCMन_अंकD_CORR_THRESHOLD_EXT]	=  0xc4,
	[BRCMन_अंकD_UNCORR_COUNT]		=  0xfc,
	[BRCMन_अंकD_CORR_COUNT]		= 0x100,
	[BRCMन_अंकD_CORR_EXT_ADDR]	= 0x10c,
	[BRCMन_अंकD_CORR_ADDR]		= 0x110,
	[BRCMन_अंकD_UNCORR_EXT_ADDR]	= 0x114,
	[BRCMन_अंकD_UNCORR_ADDR]		= 0x118,
	[BRCMन_अंकD_SEMAPHORE]		= 0x150,
	[BRCMन_अंकD_ID]			= 0x194,
	[BRCMन_अंकD_ID_EXT]		= 0x198,
	[BRCMन_अंकD_LL_RDATA]		= 0x19c,
	[BRCMन_अंकD_OOB_READ_BASE]	= 0x200,
	[BRCMन_अंकD_OOB_READ_10_BASE]	=     0,
	[BRCMन_अंकD_OOB_WRITE_BASE]	= 0x280,
	[BRCMन_अंकD_OOB_WRITE_10_BASE]	=     0,
	[BRCMन_अंकD_FC_BASE]		= 0x400,
पूर्ण;

/* BRCMन_अंकD v7.1 */
अटल स्थिर u16 brcmnand_regs_v71[] = अणु
	[BRCMन_अंकD_CMD_START]		=  0x04,
	[BRCMन_अंकD_CMD_EXT_ADDRESS]	=  0x08,
	[BRCMन_अंकD_CMD_ADDRESS]		=  0x0c,
	[BRCMन_अंकD_INTFC_STATUS]		=  0x14,
	[BRCMन_अंकD_CS_SELECT]		=  0x18,
	[BRCMन_अंकD_CS_XOR]		=  0x1c,
	[BRCMन_अंकD_LL_OP]		=  0x20,
	[BRCMन_अंकD_CS0_BASE]		=  0x50,
	[BRCMन_अंकD_CS1_BASE]		=     0,
	[BRCMन_अंकD_CORR_THRESHOLD]	=  0xdc,
	[BRCMन_अंकD_CORR_THRESHOLD_EXT]	=  0xe0,
	[BRCMन_अंकD_UNCORR_COUNT]		=  0xfc,
	[BRCMन_अंकD_CORR_COUNT]		= 0x100,
	[BRCMन_अंकD_CORR_EXT_ADDR]	= 0x10c,
	[BRCMन_अंकD_CORR_ADDR]		= 0x110,
	[BRCMन_अंकD_UNCORR_EXT_ADDR]	= 0x114,
	[BRCMन_अंकD_UNCORR_ADDR]		= 0x118,
	[BRCMन_अंकD_SEMAPHORE]		= 0x150,
	[BRCMन_अंकD_ID]			= 0x194,
	[BRCMन_अंकD_ID_EXT]		= 0x198,
	[BRCMन_अंकD_LL_RDATA]		= 0x19c,
	[BRCMन_अंकD_OOB_READ_BASE]	= 0x200,
	[BRCMन_अंकD_OOB_READ_10_BASE]	=     0,
	[BRCMन_अंकD_OOB_WRITE_BASE]	= 0x280,
	[BRCMन_अंकD_OOB_WRITE_10_BASE]	=     0,
	[BRCMन_अंकD_FC_BASE]		= 0x400,
पूर्ण;

/* BRCMन_अंकD v7.2 */
अटल स्थिर u16 brcmnand_regs_v72[] = अणु
	[BRCMन_अंकD_CMD_START]		=  0x04,
	[BRCMन_अंकD_CMD_EXT_ADDRESS]	=  0x08,
	[BRCMन_अंकD_CMD_ADDRESS]		=  0x0c,
	[BRCMन_अंकD_INTFC_STATUS]		=  0x14,
	[BRCMन_अंकD_CS_SELECT]		=  0x18,
	[BRCMन_अंकD_CS_XOR]		=  0x1c,
	[BRCMन_अंकD_LL_OP]		=  0x20,
	[BRCMन_अंकD_CS0_BASE]		=  0x50,
	[BRCMन_अंकD_CS1_BASE]		=     0,
	[BRCMन_अंकD_CORR_THRESHOLD]	=  0xdc,
	[BRCMन_अंकD_CORR_THRESHOLD_EXT]	=  0xe0,
	[BRCMन_अंकD_UNCORR_COUNT]		=  0xfc,
	[BRCMन_अंकD_CORR_COUNT]		= 0x100,
	[BRCMन_अंकD_CORR_EXT_ADDR]	= 0x10c,
	[BRCMन_अंकD_CORR_ADDR]		= 0x110,
	[BRCMन_अंकD_UNCORR_EXT_ADDR]	= 0x114,
	[BRCMन_अंकD_UNCORR_ADDR]		= 0x118,
	[BRCMन_अंकD_SEMAPHORE]		= 0x150,
	[BRCMन_अंकD_ID]			= 0x194,
	[BRCMन_अंकD_ID_EXT]		= 0x198,
	[BRCMन_अंकD_LL_RDATA]		= 0x19c,
	[BRCMन_अंकD_OOB_READ_BASE]	= 0x200,
	[BRCMन_अंकD_OOB_READ_10_BASE]	=     0,
	[BRCMन_अंकD_OOB_WRITE_BASE]	= 0x400,
	[BRCMन_अंकD_OOB_WRITE_10_BASE]	=     0,
	[BRCMन_अंकD_FC_BASE]		= 0x600,
पूर्ण;

क्रमागत brcmnand_cs_reg अणु
	BRCMन_अंकD_CS_CFG_EXT = 0,
	BRCMन_अंकD_CS_CFG,
	BRCMन_अंकD_CS_ACC_CONTROL,
	BRCMन_अंकD_CS_TIMING1,
	BRCMन_अंकD_CS_TIMING2,
पूर्ण;

/* Per chip-select offsets क्रम v7.1 */
अटल स्थिर u8 brcmnand_cs_offsets_v71[] = अणु
	[BRCMन_अंकD_CS_ACC_CONTROL]	= 0x00,
	[BRCMन_अंकD_CS_CFG_EXT]		= 0x04,
	[BRCMन_अंकD_CS_CFG]		= 0x08,
	[BRCMन_अंकD_CS_TIMING1]		= 0x0c,
	[BRCMन_अंकD_CS_TIMING2]		= 0x10,
पूर्ण;

/* Per chip-select offsets क्रम pre v7.1, except CS0 on <= v5.0 */
अटल स्थिर u8 brcmnand_cs_offsets[] = अणु
	[BRCMन_अंकD_CS_ACC_CONTROL]	= 0x00,
	[BRCMन_अंकD_CS_CFG_EXT]		= 0x04,
	[BRCMन_अंकD_CS_CFG]		= 0x04,
	[BRCMन_अंकD_CS_TIMING1]		= 0x08,
	[BRCMन_अंकD_CS_TIMING2]		= 0x0c,
पूर्ण;

/* Per chip-select offset क्रम <= v5.0 on CS0 only */
अटल स्थिर u8 brcmnand_cs_offsets_cs0[] = अणु
	[BRCMन_अंकD_CS_ACC_CONTROL]	= 0x00,
	[BRCMन_अंकD_CS_CFG_EXT]		= 0x08,
	[BRCMन_अंकD_CS_CFG]		= 0x08,
	[BRCMन_अंकD_CS_TIMING1]		= 0x10,
	[BRCMन_अंकD_CS_TIMING2]		= 0x14,
पूर्ण;

/*
 * Bitfields क्रम the CFG and CFG_EXT रेजिस्टरs. Pre-v7.1 controllers only had
 * one config रेजिस्टर, but once the bitfields overflowed, newer controllers
 * (v7.1 and newer) added a CFG_EXT रेजिस्टर and shuffled a few fields around.
 */
क्रमागत अणु
	CFG_BLK_ADR_BYTES_SHIFT		= 8,
	CFG_COL_ADR_BYTES_SHIFT		= 12,
	CFG_FUL_ADR_BYTES_SHIFT		= 16,
	CFG_BUS_WIDTH_SHIFT		= 23,
	CFG_BUS_WIDTH			= BIT(CFG_BUS_WIDTH_SHIFT),
	CFG_DEVICE_SIZE_SHIFT		= 24,

	/* Only क्रम v2.1 */
	CFG_PAGE_SIZE_SHIFT_v2_1	= 30,

	/* Only क्रम pre-v7.1 (with no CFG_EXT रेजिस्टर) */
	CFG_PAGE_SIZE_SHIFT		= 20,
	CFG_BLK_SIZE_SHIFT		= 28,

	/* Only क्रम v7.1+ (with CFG_EXT रेजिस्टर) */
	CFG_EXT_PAGE_SIZE_SHIFT		= 0,
	CFG_EXT_BLK_SIZE_SHIFT		= 4,
पूर्ण;

/* BRCMन_अंकD_INTFC_STATUS */
क्रमागत अणु
	INTFC_FLASH_STATUS		= GENMASK(7, 0),

	INTFC_ERASED			= BIT(27),
	INTFC_OOB_VALID			= BIT(28),
	INTFC_CACHE_VALID		= BIT(29),
	INTFC_FLASH_READY		= BIT(30),
	INTFC_CTLR_READY		= BIT(31),
पूर्ण;

अटल अंतरभूत u32 nand_पढ़ोreg(काष्ठा brcmnand_controller *ctrl, u32 offs)
अणु
	वापस brcmnand_पढ़ोl(ctrl->nand_base + offs);
पूर्ण

अटल अंतरभूत व्योम nand_ग_लिखोreg(काष्ठा brcmnand_controller *ctrl, u32 offs,
				 u32 val)
अणु
	brcmnand_ग_लिखोl(val, ctrl->nand_base + offs);
पूर्ण

अटल पूर्णांक brcmnand_revision_init(काष्ठा brcmnand_controller *ctrl)
अणु
	अटल स्थिर अचिन्हित पूर्णांक block_sizes_v6[] = अणु 8, 16, 128, 256, 512, 1024, 2048, 0 पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक block_sizes_v4[] = अणु 16, 128, 8, 512, 256, 1024, 2048, 0 पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक block_sizes_v2_2[] = अणु 16, 128, 8, 512, 256, 0 पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक block_sizes_v2_1[] = अणु 16, 128, 8, 512, 0 पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक page_sizes_v3_4[] = अणु 512, 2048, 4096, 8192, 0 पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक page_sizes_v2_2[] = अणु 512, 2048, 4096, 0 पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक page_sizes_v2_1[] = अणु 512, 2048, 0 पूर्ण;

	ctrl->nand_version = nand_पढ़ोreg(ctrl, 0) & 0xffff;

	/* Only support v2.1+ */
	अगर (ctrl->nand_version < 0x0201) अणु
		dev_err(ctrl->dev, "version %#x not supported\n",
			ctrl->nand_version);
		वापस -ENODEV;
	पूर्ण

	/* Register offsets */
	अगर (ctrl->nand_version >= 0x0702)
		ctrl->reg_offsets = brcmnand_regs_v72;
	अन्यथा अगर (ctrl->nand_version == 0x0701)
		ctrl->reg_offsets = brcmnand_regs_v71;
	अन्यथा अगर (ctrl->nand_version >= 0x0600)
		ctrl->reg_offsets = brcmnand_regs_v60;
	अन्यथा अगर (ctrl->nand_version >= 0x0500)
		ctrl->reg_offsets = brcmnand_regs_v50;
	अन्यथा अगर (ctrl->nand_version >= 0x0303)
		ctrl->reg_offsets = brcmnand_regs_v33;
	अन्यथा अगर (ctrl->nand_version >= 0x0201)
		ctrl->reg_offsets = brcmnand_regs_v21;

	/* Chip-select stride */
	अगर (ctrl->nand_version >= 0x0701)
		ctrl->reg_spacing = 0x14;
	अन्यथा
		ctrl->reg_spacing = 0x10;

	/* Per chip-select रेजिस्टरs */
	अगर (ctrl->nand_version >= 0x0701) अणु
		ctrl->cs_offsets = brcmnand_cs_offsets_v71;
	पूर्ण अन्यथा अणु
		ctrl->cs_offsets = brcmnand_cs_offsets;

		/* v3.3-5.0 have a dअगरferent CS0 offset layout */
		अगर (ctrl->nand_version >= 0x0303 &&
		    ctrl->nand_version <= 0x0500)
			ctrl->cs0_offsets = brcmnand_cs_offsets_cs0;
	पूर्ण

	/* Page / block sizes */
	अगर (ctrl->nand_version >= 0x0701) अणु
		/* >= v7.1 use nice घातer-of-2 values! */
		ctrl->max_page_size = 16 * 1024;
		ctrl->max_block_size = 2 * 1024 * 1024;
	पूर्ण अन्यथा अणु
		अगर (ctrl->nand_version >= 0x0304)
			ctrl->page_sizes = page_sizes_v3_4;
		अन्यथा अगर (ctrl->nand_version >= 0x0202)
			ctrl->page_sizes = page_sizes_v2_2;
		अन्यथा
			ctrl->page_sizes = page_sizes_v2_1;

		अगर (ctrl->nand_version >= 0x0202)
			ctrl->page_size_shअगरt = CFG_PAGE_SIZE_SHIFT;
		अन्यथा
			ctrl->page_size_shअगरt = CFG_PAGE_SIZE_SHIFT_v2_1;

		अगर (ctrl->nand_version >= 0x0600)
			ctrl->block_sizes = block_sizes_v6;
		अन्यथा अगर (ctrl->nand_version >= 0x0400)
			ctrl->block_sizes = block_sizes_v4;
		अन्यथा अगर (ctrl->nand_version >= 0x0202)
			ctrl->block_sizes = block_sizes_v2_2;
		अन्यथा
			ctrl->block_sizes = block_sizes_v2_1;

		अगर (ctrl->nand_version < 0x0400) अणु
			अगर (ctrl->nand_version < 0x0202)
				ctrl->max_page_size = 2048;
			अन्यथा
				ctrl->max_page_size = 4096;
			ctrl->max_block_size = 512 * 1024;
		पूर्ण
	पूर्ण

	/* Maximum spare area sector size (per 512B) */
	अगर (ctrl->nand_version == 0x0702)
		ctrl->max_oob = 128;
	अन्यथा अगर (ctrl->nand_version >= 0x0600)
		ctrl->max_oob = 64;
	अन्यथा अगर (ctrl->nand_version >= 0x0500)
		ctrl->max_oob = 32;
	अन्यथा
		ctrl->max_oob = 16;

	/* v6.0 and newer (except v6.1) have prefetch support */
	अगर (ctrl->nand_version >= 0x0600 && ctrl->nand_version != 0x0601)
		ctrl->features |= BRCMन_अंकD_HAS_PREFETCH;

	/*
	 * v6.x has cache mode, but it's implemented dअगरferently. Ignore it क्रम
	 * now.
	 */
	अगर (ctrl->nand_version >= 0x0700)
		ctrl->features |= BRCMन_अंकD_HAS_CACHE_MODE;

	अगर (ctrl->nand_version >= 0x0500)
		ctrl->features |= BRCMन_अंकD_HAS_1K_SECTORS;

	अगर (ctrl->nand_version >= 0x0700)
		ctrl->features |= BRCMन_अंकD_HAS_WP;
	अन्यथा अगर (of_property_पढ़ो_bool(ctrl->dev->of_node, "brcm,nand-has-wp"))
		ctrl->features |= BRCMन_अंकD_HAS_WP;

	वापस 0;
पूर्ण

अटल व्योम brcmnand_flash_dma_revision_init(काष्ठा brcmnand_controller *ctrl)
अणु
	/* flash_dma रेजिस्टर offsets */
	अगर (ctrl->nand_version >= 0x0703)
		ctrl->flash_dma_offsets = flash_dma_regs_v4;
	अन्यथा अगर (ctrl->nand_version == 0x0602)
		ctrl->flash_dma_offsets = flash_dma_regs_v0;
	अन्यथा
		ctrl->flash_dma_offsets = flash_dma_regs_v1;
पूर्ण

अटल अंतरभूत u32 brcmnand_पढ़ो_reg(काष्ठा brcmnand_controller *ctrl,
		क्रमागत brcmnand_reg reg)
अणु
	u16 offs = ctrl->reg_offsets[reg];

	अगर (offs)
		वापस nand_पढ़ोreg(ctrl, offs);
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत व्योम brcmnand_ग_लिखो_reg(काष्ठा brcmnand_controller *ctrl,
				      क्रमागत brcmnand_reg reg, u32 val)
अणु
	u16 offs = ctrl->reg_offsets[reg];

	अगर (offs)
		nand_ग_लिखोreg(ctrl, offs, val);
पूर्ण

अटल अंतरभूत व्योम brcmnand_rmw_reg(काष्ठा brcmnand_controller *ctrl,
				    क्रमागत brcmnand_reg reg, u32 mask, अचिन्हित
				    पूर्णांक shअगरt, u32 val)
अणु
	u32 पंचांगp = brcmnand_पढ़ो_reg(ctrl, reg);

	पंचांगp &= ~mask;
	पंचांगp |= val << shअगरt;
	brcmnand_ग_लिखो_reg(ctrl, reg, पंचांगp);
पूर्ण

अटल अंतरभूत u32 brcmnand_पढ़ो_fc(काष्ठा brcmnand_controller *ctrl, पूर्णांक word)
अणु
	वापस __raw_पढ़ोl(ctrl->nand_fc + word * 4);
पूर्ण

अटल अंतरभूत व्योम brcmnand_ग_लिखो_fc(काष्ठा brcmnand_controller *ctrl,
				     पूर्णांक word, u32 val)
अणु
	__raw_ग_लिखोl(val, ctrl->nand_fc + word * 4);
पूर्ण

अटल अंतरभूत व्योम edu_ग_लिखोl(काष्ठा brcmnand_controller *ctrl,
			      क्रमागत edu_reg reg, u32 val)
अणु
	u16 offs = ctrl->edu_offsets[reg];

	brcmnand_ग_लिखोl(val, ctrl->edu_base + offs);
पूर्ण

अटल अंतरभूत u32 edu_पढ़ोl(काष्ठा brcmnand_controller *ctrl,
			    क्रमागत edu_reg reg)
अणु
	u16 offs = ctrl->edu_offsets[reg];

	वापस brcmnand_पढ़ोl(ctrl->edu_base + offs);
पूर्ण

अटल व्योम brcmnand_clear_ecc_addr(काष्ठा brcmnand_controller *ctrl)
अणु

	/* Clear error addresses */
	brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_UNCORR_ADDR, 0);
	brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_CORR_ADDR, 0);
	brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_UNCORR_EXT_ADDR, 0);
	brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_CORR_EXT_ADDR, 0);
पूर्ण

अटल u64 brcmnand_get_uncorrecc_addr(काष्ठा brcmnand_controller *ctrl)
अणु
	u64 err_addr;

	err_addr = brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_UNCORR_ADDR);
	err_addr |= ((u64)(brcmnand_पढ़ो_reg(ctrl,
					     BRCMन_अंकD_UNCORR_EXT_ADDR)
					     & 0xffff) << 32);

	वापस err_addr;
पूर्ण

अटल u64 brcmnand_get_correcc_addr(काष्ठा brcmnand_controller *ctrl)
अणु
	u64 err_addr;

	err_addr = brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_CORR_ADDR);
	err_addr |= ((u64)(brcmnand_पढ़ो_reg(ctrl,
					     BRCMन_अंकD_CORR_EXT_ADDR)
					     & 0xffff) << 32);

	वापस err_addr;
पूर्ण

अटल व्योम brcmnand_set_cmd_addr(काष्ठा mtd_info *mtd, u64 addr)
अणु
	काष्ठा nand_chip *chip =  mtd_to_nand(mtd);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_controller *ctrl = host->ctrl;

	brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_CMD_EXT_ADDRESS,
			   (host->cs << 16) | ((addr >> 32) & 0xffff));
	(व्योम)brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_CMD_EXT_ADDRESS);
	brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_CMD_ADDRESS,
			   lower_32_bits(addr));
	(व्योम)brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_CMD_ADDRESS);
पूर्ण

अटल अंतरभूत u16 brcmnand_cs_offset(काष्ठा brcmnand_controller *ctrl, पूर्णांक cs,
				     क्रमागत brcmnand_cs_reg reg)
अणु
	u16 offs_cs0 = ctrl->reg_offsets[BRCMन_अंकD_CS0_BASE];
	u16 offs_cs1 = ctrl->reg_offsets[BRCMन_अंकD_CS1_BASE];
	u8 cs_offs;

	अगर (cs == 0 && ctrl->cs0_offsets)
		cs_offs = ctrl->cs0_offsets[reg];
	अन्यथा
		cs_offs = ctrl->cs_offsets[reg];

	अगर (cs && offs_cs1)
		वापस offs_cs1 + (cs - 1) * ctrl->reg_spacing + cs_offs;

	वापस offs_cs0 + cs * ctrl->reg_spacing + cs_offs;
पूर्ण

अटल अंतरभूत u32 brcmnand_count_corrected(काष्ठा brcmnand_controller *ctrl)
अणु
	अगर (ctrl->nand_version < 0x0600)
		वापस 1;
	वापस brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_CORR_COUNT);
पूर्ण

अटल व्योम brcmnand_wr_corr_thresh(काष्ठा brcmnand_host *host, u8 val)
अणु
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	अचिन्हित पूर्णांक shअगरt = 0, bits;
	क्रमागत brcmnand_reg reg = BRCMन_अंकD_CORR_THRESHOLD;
	पूर्णांक cs = host->cs;

	अगर (!ctrl->reg_offsets[reg])
		वापस;

	अगर (ctrl->nand_version == 0x0702)
		bits = 7;
	अन्यथा अगर (ctrl->nand_version >= 0x0600)
		bits = 6;
	अन्यथा अगर (ctrl->nand_version >= 0x0500)
		bits = 5;
	अन्यथा
		bits = 4;

	अगर (ctrl->nand_version >= 0x0702) अणु
		अगर (cs >= 4)
			reg = BRCMन_अंकD_CORR_THRESHOLD_EXT;
		shअगरt = (cs % 4) * bits;
	पूर्ण अन्यथा अगर (ctrl->nand_version >= 0x0600) अणु
		अगर (cs >= 5)
			reg = BRCMन_अंकD_CORR_THRESHOLD_EXT;
		shअगरt = (cs % 5) * bits;
	पूर्ण
	brcmnand_rmw_reg(ctrl, reg, (bits - 1) << shअगरt, shअगरt, val);
पूर्ण

अटल अंतरभूत पूर्णांक brcmnand_cmd_shअगरt(काष्ठा brcmnand_controller *ctrl)
अणु
	अगर (ctrl->nand_version < 0x0602)
		वापस 24;
	वापस 0;
पूर्ण

/***********************************************************************
 * न_अंकD ACC CONTROL bitfield
 *
 * Some bits have reमुख्यed स्थिरant throughout hardware revision, जबतक
 * others have shअगरted around.
 ***********************************************************************/

/* Constant क्रम all versions (where supported) */
क्रमागत अणु
	/* See BRCMन_अंकD_HAS_CACHE_MODE */
	ACC_CONTROL_CACHE_MODE				= BIT(22),

	/* See BRCMन_अंकD_HAS_PREFETCH */
	ACC_CONTROL_PREFETCH				= BIT(23),

	ACC_CONTROL_PAGE_HIT				= BIT(24),
	ACC_CONTROL_WR_PREEMPT				= BIT(25),
	ACC_CONTROL_PARTIAL_PAGE			= BIT(26),
	ACC_CONTROL_RD_ERASED				= BIT(27),
	ACC_CONTROL_FAST_PGM_RDIN			= BIT(28),
	ACC_CONTROL_WR_ECC				= BIT(30),
	ACC_CONTROL_RD_ECC				= BIT(31),
पूर्ण;

अटल अंतरभूत u32 brcmnand_spare_area_mask(काष्ठा brcmnand_controller *ctrl)
अणु
	अगर (ctrl->nand_version == 0x0702)
		वापस GENMASK(7, 0);
	अन्यथा अगर (ctrl->nand_version >= 0x0600)
		वापस GENMASK(6, 0);
	अन्यथा अगर (ctrl->nand_version >= 0x0303)
		वापस GENMASK(5, 0);
	अन्यथा
		वापस GENMASK(4, 0);
पूर्ण

#घोषणा न_अंकD_ACC_CONTROL_ECC_SHIFT	16
#घोषणा न_अंकD_ACC_CONTROL_ECC_EXT_SHIFT	13

अटल अंतरभूत u32 brcmnand_ecc_level_mask(काष्ठा brcmnand_controller *ctrl)
अणु
	u32 mask = (ctrl->nand_version >= 0x0600) ? 0x1f : 0x0f;

	mask <<= न_अंकD_ACC_CONTROL_ECC_SHIFT;

	/* v7.2 includes additional ECC levels */
	अगर (ctrl->nand_version >= 0x0702)
		mask |= 0x7 << न_अंकD_ACC_CONTROL_ECC_EXT_SHIFT;

	वापस mask;
पूर्ण

अटल व्योम brcmnand_set_ecc_enabled(काष्ठा brcmnand_host *host, पूर्णांक en)
अणु
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	u16 offs = brcmnand_cs_offset(ctrl, host->cs, BRCMन_अंकD_CS_ACC_CONTROL);
	u32 acc_control = nand_पढ़ोreg(ctrl, offs);
	u32 ecc_flags = ACC_CONTROL_WR_ECC | ACC_CONTROL_RD_ECC;

	अगर (en) अणु
		acc_control |= ecc_flags; /* enable RD/WR ECC */
		acc_control |= host->hwcfg.ecc_level
			       << न_अंकD_ACC_CONTROL_ECC_SHIFT;
	पूर्ण अन्यथा अणु
		acc_control &= ~ecc_flags; /* disable RD/WR ECC */
		acc_control &= ~brcmnand_ecc_level_mask(ctrl);
	पूर्ण

	nand_ग_लिखोreg(ctrl, offs, acc_control);
पूर्ण

अटल अंतरभूत पूर्णांक brcmnand_sector_1k_shअगरt(काष्ठा brcmnand_controller *ctrl)
अणु
	अगर (ctrl->nand_version >= 0x0702)
		वापस 9;
	अन्यथा अगर (ctrl->nand_version >= 0x0600)
		वापस 7;
	अन्यथा अगर (ctrl->nand_version >= 0x0500)
		वापस 6;
	अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक brcmnand_get_sector_size_1k(काष्ठा brcmnand_host *host)
अणु
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	पूर्णांक shअगरt = brcmnand_sector_1k_shअगरt(ctrl);
	u16 acc_control_offs = brcmnand_cs_offset(ctrl, host->cs,
						  BRCMन_अंकD_CS_ACC_CONTROL);

	अगर (shअगरt < 0)
		वापस 0;

	वापस (nand_पढ़ोreg(ctrl, acc_control_offs) >> shअगरt) & 0x1;
पूर्ण

अटल व्योम brcmnand_set_sector_size_1k(काष्ठा brcmnand_host *host, पूर्णांक val)
अणु
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	पूर्णांक shअगरt = brcmnand_sector_1k_shअगरt(ctrl);
	u16 acc_control_offs = brcmnand_cs_offset(ctrl, host->cs,
						  BRCMन_अंकD_CS_ACC_CONTROL);
	u32 पंचांगp;

	अगर (shअगरt < 0)
		वापस;

	पंचांगp = nand_पढ़ोreg(ctrl, acc_control_offs);
	पंचांगp &= ~(1 << shअगरt);
	पंचांगp |= (!!val) << shअगरt;
	nand_ग_लिखोreg(ctrl, acc_control_offs, पंचांगp);
पूर्ण

/***********************************************************************
 * CS_न_अंकD_SELECT
 ***********************************************************************/

क्रमागत अणु
	CS_SELECT_न_अंकD_WP			= BIT(29),
	CS_SELECT_AUTO_DEVICE_ID_CFG		= BIT(30),
पूर्ण;

अटल पूर्णांक bcmnand_ctrl_poll_status(काष्ठा brcmnand_controller *ctrl,
				    u32 mask, u32 expected_val,
				    अचिन्हित दीर्घ समयout_ms)
अणु
	अचिन्हित दीर्घ limit;
	u32 val;

	अगर (!समयout_ms)
		समयout_ms = न_अंकD_POLL_STATUS_TIMEOUT_MS;

	limit = jअगरfies + msecs_to_jअगरfies(समयout_ms);
	करो अणु
		val = brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_INTFC_STATUS);
		अगर ((val & mask) == expected_val)
			वापस 0;

		cpu_relax();
	पूर्ण जबतक (समय_after(limit, jअगरfies));

	dev_warn(ctrl->dev, "timeout on status poll (expected %x got %x)\n",
		 expected_val, val & mask);

	वापस -ETIMEDOUT;
पूर्ण

अटल अंतरभूत व्योम brcmnand_set_wp(काष्ठा brcmnand_controller *ctrl, bool en)
अणु
	u32 val = en ? CS_SELECT_न_अंकD_WP : 0;

	brcmnand_rmw_reg(ctrl, BRCMन_अंकD_CS_SELECT, CS_SELECT_न_अंकD_WP, 0, val);
पूर्ण

/***********************************************************************
 * Flash DMA
 ***********************************************************************/

अटल अंतरभूत bool has_flash_dma(काष्ठा brcmnand_controller *ctrl)
अणु
	वापस ctrl->flash_dma_base;
पूर्ण

अटल अंतरभूत bool has_edu(काष्ठा brcmnand_controller *ctrl)
अणु
	वापस ctrl->edu_base;
पूर्ण

अटल अंतरभूत bool use_dma(काष्ठा brcmnand_controller *ctrl)
अणु
	वापस has_flash_dma(ctrl) || has_edu(ctrl);
पूर्ण

अटल अंतरभूत व्योम disable_ctrl_irqs(काष्ठा brcmnand_controller *ctrl)
अणु
	अगर (ctrl->pio_poll_mode)
		वापस;

	अगर (has_flash_dma(ctrl)) अणु
		ctrl->flash_dma_base = शून्य;
		disable_irq(ctrl->dma_irq);
	पूर्ण

	disable_irq(ctrl->irq);
	ctrl->pio_poll_mode = true;
पूर्ण

अटल अंतरभूत bool flash_dma_buf_ok(स्थिर व्योम *buf)
अणु
	वापस buf && !is_vदो_स्मृति_addr(buf) &&
		likely(IS_ALIGNED((uपूर्णांकptr_t)buf, 4));
पूर्ण

अटल अंतरभूत व्योम flash_dma_ग_लिखोl(काष्ठा brcmnand_controller *ctrl,
				    क्रमागत flash_dma_reg dma_reg, u32 val)
अणु
	u16 offs = ctrl->flash_dma_offsets[dma_reg];

	brcmnand_ग_लिखोl(val, ctrl->flash_dma_base + offs);
पूर्ण

अटल अंतरभूत u32 flash_dma_पढ़ोl(काष्ठा brcmnand_controller *ctrl,
				  क्रमागत flash_dma_reg dma_reg)
अणु
	u16 offs = ctrl->flash_dma_offsets[dma_reg];

	वापस brcmnand_पढ़ोl(ctrl->flash_dma_base + offs);
पूर्ण

/* Low-level operation types: command, address, ग_लिखो, or पढ़ो */
क्रमागत brcmnand_llop_type अणु
	LL_OP_CMD,
	LL_OP_ADDR,
	LL_OP_WR,
	LL_OP_RD,
पूर्ण;

/***********************************************************************
 * Internal support functions
 ***********************************************************************/

अटल अंतरभूत bool is_hamming_ecc(काष्ठा brcmnand_controller *ctrl,
				  काष्ठा brcmnand_cfg *cfg)
अणु
	अगर (ctrl->nand_version <= 0x0701)
		वापस cfg->sector_size_1k == 0 && cfg->spare_area_size == 16 &&
			cfg->ecc_level == 15;
	अन्यथा
		वापस cfg->sector_size_1k == 0 && ((cfg->spare_area_size == 16 &&
			cfg->ecc_level == 15) ||
			(cfg->spare_area_size == 28 && cfg->ecc_level == 16));
पूर्ण

/*
 * Set mtd->ooblayout to the appropriate mtd_ooblayout_ops given
 * the layout/configuration.
 * Returns -ERRCODE on failure.
 */
अटल पूर्णांक brcmnand_hamming_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
					  काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_cfg *cfg = &host->hwcfg;
	पूर्णांक sas = cfg->spare_area_size << cfg->sector_size_1k;
	पूर्णांक sectors = cfg->page_size / (512 << cfg->sector_size_1k);

	अगर (section >= sectors)
		वापस -दुस्फल;

	oobregion->offset = (section * sas) + 6;
	oobregion->length = 3;

	वापस 0;
पूर्ण

अटल पूर्णांक brcmnand_hamming_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
					   काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_cfg *cfg = &host->hwcfg;
	पूर्णांक sas = cfg->spare_area_size << cfg->sector_size_1k;
	पूर्णांक sectors = cfg->page_size / (512 << cfg->sector_size_1k);
	u32 next;

	अगर (section > sectors)
		वापस -दुस्फल;

	next = (section * sas);
	अगर (section < sectors)
		next += 6;

	अगर (section) अणु
		oobregion->offset = ((section - 1) * sas) + 9;
	पूर्ण अन्यथा अणु
		अगर (cfg->page_size > 512) अणु
			/* Large page न_अंकD uses first 2 bytes क्रम BBI */
			oobregion->offset = 2;
		पूर्ण अन्यथा अणु
			/* Small page न_अंकD uses last byte beक्रमe ECC क्रम BBI */
			oobregion->offset = 0;
			next--;
		पूर्ण
	पूर्ण

	oobregion->length = next - oobregion->offset;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops brcmnand_hamming_ooblayout_ops = अणु
	.ecc = brcmnand_hamming_ooblayout_ecc,
	.मुक्त = brcmnand_hamming_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक brcmnand_bch_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				      काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_cfg *cfg = &host->hwcfg;
	पूर्णांक sas = cfg->spare_area_size << cfg->sector_size_1k;
	पूर्णांक sectors = cfg->page_size / (512 << cfg->sector_size_1k);

	अगर (section >= sectors)
		वापस -दुस्फल;

	oobregion->offset = ((section + 1) * sas) - chip->ecc.bytes;
	oobregion->length = chip->ecc.bytes;

	वापस 0;
पूर्ण

अटल पूर्णांक brcmnand_bch_ooblayout_मुक्त_lp(काष्ठा mtd_info *mtd, पूर्णांक section,
					  काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_cfg *cfg = &host->hwcfg;
	पूर्णांक sas = cfg->spare_area_size << cfg->sector_size_1k;
	पूर्णांक sectors = cfg->page_size / (512 << cfg->sector_size_1k);

	अगर (section >= sectors)
		वापस -दुस्फल;

	अगर (sas <= chip->ecc.bytes)
		वापस 0;

	oobregion->offset = section * sas;
	oobregion->length = sas - chip->ecc.bytes;

	अगर (!section) अणु
		oobregion->offset++;
		oobregion->length--;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक brcmnand_bch_ooblayout_मुक्त_sp(काष्ठा mtd_info *mtd, पूर्णांक section,
					  काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_cfg *cfg = &host->hwcfg;
	पूर्णांक sas = cfg->spare_area_size << cfg->sector_size_1k;

	अगर (section > 1 || sas - chip->ecc.bytes < 6 ||
	    (section && sas - chip->ecc.bytes == 6))
		वापस -दुस्फल;

	अगर (!section) अणु
		oobregion->offset = 0;
		oobregion->length = 5;
	पूर्ण अन्यथा अणु
		oobregion->offset = 6;
		oobregion->length = sas - chip->ecc.bytes - 6;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops brcmnand_bch_lp_ooblayout_ops = अणु
	.ecc = brcmnand_bch_ooblayout_ecc,
	.मुक्त = brcmnand_bch_ooblayout_मुक्त_lp,
पूर्ण;

अटल स्थिर काष्ठा mtd_ooblayout_ops brcmnand_bch_sp_ooblayout_ops = अणु
	.ecc = brcmnand_bch_ooblayout_ecc,
	.मुक्त = brcmnand_bch_ooblayout_मुक्त_sp,
पूर्ण;

अटल पूर्णांक brcmstb_choose_ecc_layout(काष्ठा brcmnand_host *host)
अणु
	काष्ठा brcmnand_cfg *p = &host->hwcfg;
	काष्ठा mtd_info *mtd = nand_to_mtd(&host->chip);
	काष्ठा nand_ecc_ctrl *ecc = &host->chip.ecc;
	अचिन्हित पूर्णांक ecc_level = p->ecc_level;
	पूर्णांक sas = p->spare_area_size << p->sector_size_1k;
	पूर्णांक sectors = p->page_size / (512 << p->sector_size_1k);

	अगर (p->sector_size_1k)
		ecc_level <<= 1;

	अगर (is_hamming_ecc(host->ctrl, p)) अणु
		ecc->bytes = 3 * sectors;
		mtd_set_ooblayout(mtd, &brcmnand_hamming_ooblayout_ops);
		वापस 0;
	पूर्ण

	/*
	 * CONTROLLER_VERSION:
	 *   < v5.0: ECC_REQ = उच्चमान(BCH_T * 13/8)
	 *  >= v5.0: ECC_REQ = उच्चमान(BCH_T * 14/8)
	 * But we will just be conservative.
	 */
	ecc->bytes = DIV_ROUND_UP(ecc_level * 14, 8);
	अगर (p->page_size == 512)
		mtd_set_ooblayout(mtd, &brcmnand_bch_sp_ooblayout_ops);
	अन्यथा
		mtd_set_ooblayout(mtd, &brcmnand_bch_lp_ooblayout_ops);

	अगर (ecc->bytes >= sas) अणु
		dev_err(&host->pdev->dev,
			"error: ECC too large for OOB (ECC bytes %d, spare sector %d)\n",
			ecc->bytes, sas);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम brcmnand_wp(काष्ठा mtd_info *mtd, पूर्णांक wp)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_controller *ctrl = host->ctrl;

	अगर ((ctrl->features & BRCMन_अंकD_HAS_WP) && wp_on == 1) अणु
		अटल पूर्णांक old_wp = -1;
		पूर्णांक ret;

		अगर (old_wp != wp) अणु
			dev_dbg(ctrl->dev, "WP %s\n", wp ? "on" : "off");
			old_wp = wp;
		पूर्ण

		/*
		 * make sure ctrl/flash पढ़ोy beक्रमe and after
		 * changing state of #WP pin
		 */
		ret = bcmnand_ctrl_poll_status(ctrl, न_अंकD_CTRL_RDY |
					       न_अंकD_STATUS_READY,
					       न_अंकD_CTRL_RDY |
					       न_अंकD_STATUS_READY, 0);
		अगर (ret)
			वापस;

		brcmnand_set_wp(ctrl, wp);
		nand_status_op(chip, शून्य);
		/* न_अंकD_STATUS_WP 0x00 = रक्षित, 0x80 = not रक्षित */
		ret = bcmnand_ctrl_poll_status(ctrl,
					       न_अंकD_CTRL_RDY |
					       न_अंकD_STATUS_READY |
					       न_अंकD_STATUS_WP,
					       न_अंकD_CTRL_RDY |
					       न_अंकD_STATUS_READY |
					       (wp ? 0 : न_अंकD_STATUS_WP), 0);

		अगर (ret)
			dev_err_ratelimited(&host->pdev->dev,
					    "nand #WP expected %s\n",
					    wp ? "on" : "off");
	पूर्ण
पूर्ण

/* Helper functions क्रम पढ़ोing and writing OOB रेजिस्टरs */
अटल अंतरभूत u8 oob_reg_पढ़ो(काष्ठा brcmnand_controller *ctrl, u32 offs)
अणु
	u16 offset0, offset10, reg_offs;

	offset0 = ctrl->reg_offsets[BRCMन_अंकD_OOB_READ_BASE];
	offset10 = ctrl->reg_offsets[BRCMन_अंकD_OOB_READ_10_BASE];

	अगर (offs >= ctrl->max_oob)
		वापस 0x77;

	अगर (offs >= 16 && offset10)
		reg_offs = offset10 + ((offs - 0x10) & ~0x03);
	अन्यथा
		reg_offs = offset0 + (offs & ~0x03);

	वापस nand_पढ़ोreg(ctrl, reg_offs) >> (24 - ((offs & 0x03) << 3));
पूर्ण

अटल अंतरभूत व्योम oob_reg_ग_लिखो(काष्ठा brcmnand_controller *ctrl, u32 offs,
				 u32 data)
अणु
	u16 offset0, offset10, reg_offs;

	offset0 = ctrl->reg_offsets[BRCMन_अंकD_OOB_WRITE_BASE];
	offset10 = ctrl->reg_offsets[BRCMन_अंकD_OOB_WRITE_10_BASE];

	अगर (offs >= ctrl->max_oob)
		वापस;

	अगर (offs >= 16 && offset10)
		reg_offs = offset10 + ((offs - 0x10) & ~0x03);
	अन्यथा
		reg_offs = offset0 + (offs & ~0x03);

	nand_ग_लिखोreg(ctrl, reg_offs, data);
पूर्ण

/*
 * पढ़ो_oob_from_regs - पढ़ो data from OOB रेजिस्टरs
 * @ctrl: न_अंकD controller
 * @i: sub-page sector index
 * @oob: buffer to पढ़ो to
 * @sas: spare area sector size (i.e., OOB size per FLASH_CACHE)
 * @sector_1k: 1 क्रम 1KiB sectors, 0 क्रम 512B, other values are illegal
 */
अटल पूर्णांक पढ़ो_oob_from_regs(काष्ठा brcmnand_controller *ctrl, पूर्णांक i, u8 *oob,
			      पूर्णांक sas, पूर्णांक sector_1k)
अणु
	पूर्णांक tbytes = sas << sector_1k;
	पूर्णांक j;

	/* Adjust OOB values क्रम 1K sector size */
	अगर (sector_1k && (i & 0x01))
		tbytes = max(0, tbytes - (पूर्णांक)ctrl->max_oob);
	tbytes = min_t(पूर्णांक, tbytes, ctrl->max_oob);

	क्रम (j = 0; j < tbytes; j++)
		oob[j] = oob_reg_पढ़ो(ctrl, j);
	वापस tbytes;
पूर्ण

/*
 * ग_लिखो_oob_to_regs - ग_लिखो data to OOB रेजिस्टरs
 * @i: sub-page sector index
 * @oob: buffer to ग_लिखो from
 * @sas: spare area sector size (i.e., OOB size per FLASH_CACHE)
 * @sector_1k: 1 क्रम 1KiB sectors, 0 क्रम 512B, other values are illegal
 */
अटल पूर्णांक ग_लिखो_oob_to_regs(काष्ठा brcmnand_controller *ctrl, पूर्णांक i,
			     स्थिर u8 *oob, पूर्णांक sas, पूर्णांक sector_1k)
अणु
	पूर्णांक tbytes = sas << sector_1k;
	पूर्णांक j;

	/* Adjust OOB values क्रम 1K sector size */
	अगर (sector_1k && (i & 0x01))
		tbytes = max(0, tbytes - (पूर्णांक)ctrl->max_oob);
	tbytes = min_t(पूर्णांक, tbytes, ctrl->max_oob);

	क्रम (j = 0; j < tbytes; j += 4)
		oob_reg_ग_लिखो(ctrl, j,
				(oob[j + 0] << 24) |
				(oob[j + 1] << 16) |
				(oob[j + 2] <<  8) |
				(oob[j + 3] <<  0));
	वापस tbytes;
पूर्ण

अटल व्योम brcmnand_edu_init(काष्ठा brcmnand_controller *ctrl)
अणु
	/* initialize edu */
	edu_ग_लिखोl(ctrl, EDU_ERR_STATUS, 0);
	edu_पढ़ोl(ctrl, EDU_ERR_STATUS);
	edu_ग_लिखोl(ctrl, EDU_DONE, 0);
	edu_ग_लिखोl(ctrl, EDU_DONE, 0);
	edu_ग_लिखोl(ctrl, EDU_DONE, 0);
	edu_ग_लिखोl(ctrl, EDU_DONE, 0);
	edu_पढ़ोl(ctrl, EDU_DONE);
पूर्ण

/* edu irq */
अटल irqवापस_t brcmnand_edu_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा brcmnand_controller *ctrl = data;

	अगर (ctrl->edu_count) अणु
		ctrl->edu_count--;
		जबतक (!(edu_पढ़ोl(ctrl, EDU_DONE) & EDU_DONE_MASK))
			udelay(1);
		edu_ग_लिखोl(ctrl, EDU_DONE, 0);
		edu_पढ़ोl(ctrl, EDU_DONE);
	पूर्ण

	अगर (ctrl->edu_count) अणु
		ctrl->edu_dram_addr += FC_BYTES;
		ctrl->edu_ext_addr += FC_BYTES;

		edu_ग_लिखोl(ctrl, EDU_DRAM_ADDR, (u32)ctrl->edu_dram_addr);
		edu_पढ़ोl(ctrl, EDU_DRAM_ADDR);
		edu_ग_लिखोl(ctrl, EDU_EXT_ADDR, ctrl->edu_ext_addr);
		edu_पढ़ोl(ctrl, EDU_EXT_ADDR);

		अगर (ctrl->oob) अणु
			अगर (ctrl->edu_cmd == EDU_CMD_READ) अणु
				ctrl->oob += पढ़ो_oob_from_regs(ctrl,
							ctrl->edu_count + 1,
							ctrl->oob, ctrl->sas,
							ctrl->sector_size_1k);
			पूर्ण अन्यथा अणु
				brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_CMD_ADDRESS,
						   ctrl->edu_ext_addr);
				brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_CMD_ADDRESS);
				ctrl->oob += ग_लिखो_oob_to_regs(ctrl,
							       ctrl->edu_count,
							       ctrl->oob, ctrl->sas,
							       ctrl->sector_size_1k);
			पूर्ण
		पूर्ण

		mb(); /* flush previous ग_लिखोs */
		edu_ग_लिखोl(ctrl, EDU_CMD, ctrl->edu_cmd);
		edu_पढ़ोl(ctrl, EDU_CMD);

		वापस IRQ_HANDLED;
	पूर्ण

	complete(&ctrl->edu_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t brcmnand_ctlrdy_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा brcmnand_controller *ctrl = data;

	/* Discard all न_अंकD_CTLRDY पूर्णांकerrupts during DMA */
	अगर (ctrl->dma_pending)
		वापस IRQ_HANDLED;

	/* check अगर you need to piggy back on the ctrlrdy irq */
	अगर (ctrl->edu_pending) अणु
		अगर (irq == ctrl->irq && ((पूर्णांक)ctrl->edu_irq >= 0))
	/* Discard पूर्णांकerrupts जबतक using dedicated edu irq */
			वापस IRQ_HANDLED;

	/* no रेजिस्टरed edu irq, call handler */
		वापस brcmnand_edu_irq(irq, data);
	पूर्ण

	complete(&ctrl->करोne);
	वापस IRQ_HANDLED;
पूर्ण

/* Handle SoC-specअगरic पूर्णांकerrupt hardware */
अटल irqवापस_t brcmnand_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा brcmnand_controller *ctrl = data;

	अगर (ctrl->soc->ctlrdy_ack(ctrl->soc))
		वापस brcmnand_ctlrdy_irq(irq, data);

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t brcmnand_dma_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा brcmnand_controller *ctrl = data;

	complete(&ctrl->dma_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम brcmnand_send_cmd(काष्ठा brcmnand_host *host, पूर्णांक cmd)
अणु
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	पूर्णांक ret;
	u64 cmd_addr;

	cmd_addr = brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_CMD_ADDRESS);

	dev_dbg(ctrl->dev, "send native cmd %d addr 0x%llx\n", cmd, cmd_addr);

	BUG_ON(ctrl->cmd_pending != 0);
	ctrl->cmd_pending = cmd;

	ret = bcmnand_ctrl_poll_status(ctrl, न_अंकD_CTRL_RDY, न_अंकD_CTRL_RDY, 0);
	WARN_ON(ret);

	mb(); /* flush previous ग_लिखोs */
	brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_CMD_START,
			   cmd << brcmnand_cmd_shअगरt(ctrl));
पूर्ण

/***********************************************************************
 * न_अंकD MTD API: पढ़ो/program/erase
 ***********************************************************************/

अटल व्योम brcmnand_cmd_ctrl(काष्ठा nand_chip *chip, पूर्णांक dat,
			      अचिन्हित पूर्णांक ctrl)
अणु
	/* पूर्णांकentionally left blank */
पूर्ण

अटल bool brcmstb_nand_रुको_क्रम_completion(काष्ठा nand_chip *chip)
अणु
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	bool err = false;
	पूर्णांक sts;

	अगर (mtd->oops_panic_ग_लिखो) अणु
		/* चयन to पूर्णांकerrupt polling and PIO mode */
		disable_ctrl_irqs(ctrl);
		sts = bcmnand_ctrl_poll_status(ctrl, न_अंकD_CTRL_RDY,
					       न_अंकD_CTRL_RDY, 0);
		err = (sts < 0) ? true : false;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ समयo = msecs_to_jअगरfies(
						न_अंकD_POLL_STATUS_TIMEOUT_MS);
		/* रुको क्रम completion पूर्णांकerrupt */
		sts = रुको_क्रम_completion_समयout(&ctrl->करोne, समयo);
		err = (sts <= 0) ? true : false;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक brcmnand_रुकोfunc(काष्ठा nand_chip *chip)
अणु
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	bool err = false;

	dev_dbg(ctrl->dev, "wait on native cmd %d\n", ctrl->cmd_pending);
	अगर (ctrl->cmd_pending)
		err = brcmstb_nand_रुको_क्रम_completion(chip);

	अगर (err) अणु
		u32 cmd = brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_CMD_START)
					>> brcmnand_cmd_shअगरt(ctrl);

		dev_err_ratelimited(ctrl->dev,
			"timeout waiting for command %#02x\n", cmd);
		dev_err_ratelimited(ctrl->dev, "intfc status %08x\n",
			brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_INTFC_STATUS));
	पूर्ण
	ctrl->cmd_pending = 0;
	वापस brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_INTFC_STATUS) &
				 INTFC_FLASH_STATUS;
पूर्ण

क्रमागत अणु
	LLOP_RE				= BIT(16),
	LLOP_WE				= BIT(17),
	LLOP_ALE			= BIT(18),
	LLOP_CLE			= BIT(19),
	LLOP_RETURN_IDLE		= BIT(31),

	LLOP_DATA_MASK			= GENMASK(15, 0),
पूर्ण;

अटल पूर्णांक brcmnand_low_level_op(काष्ठा brcmnand_host *host,
				 क्रमागत brcmnand_llop_type type, u32 data,
				 bool last_op)
अणु
	काष्ठा nand_chip *chip = &host->chip;
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	u32 पंचांगp;

	पंचांगp = data & LLOP_DATA_MASK;
	चयन (type) अणु
	हाल LL_OP_CMD:
		पंचांगp |= LLOP_WE | LLOP_CLE;
		अवरोध;
	हाल LL_OP_ADDR:
		/* WE | ALE */
		पंचांगp |= LLOP_WE | LLOP_ALE;
		अवरोध;
	हाल LL_OP_WR:
		/* WE */
		पंचांगp |= LLOP_WE;
		अवरोध;
	हाल LL_OP_RD:
		/* RE */
		पंचांगp |= LLOP_RE;
		अवरोध;
	पूर्ण
	अगर (last_op)
		/* RETURN_IDLE */
		पंचांगp |= LLOP_RETURN_IDLE;

	dev_dbg(ctrl->dev, "ll_op cmd %#x\n", पंचांगp);

	brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_LL_OP, पंचांगp);
	(व्योम)brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_LL_OP);

	brcmnand_send_cmd(host, CMD_LOW_LEVEL_OP);
	वापस brcmnand_रुकोfunc(chip);
पूर्ण

अटल व्योम brcmnand_cmdfunc(काष्ठा nand_chip *chip, अचिन्हित command,
			     पूर्णांक column, पूर्णांक page_addr)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	u64 addr = (u64)page_addr << chip->page_shअगरt;
	पूर्णांक native_cmd = 0;

	अगर (command == न_अंकD_CMD_READID || command == न_अंकD_CMD_PARAM ||
			command == न_अंकD_CMD_RNDOUT)
		addr = (u64)column;
	/* Aव्योम propagating a negative, करोn't-care address */
	अन्यथा अगर (page_addr < 0)
		addr = 0;

	dev_dbg(ctrl->dev, "cmd 0x%x addr 0x%llx\n", command,
		(अचिन्हित दीर्घ दीर्घ)addr);

	host->last_cmd = command;
	host->last_byte = 0;
	host->last_addr = addr;

	चयन (command) अणु
	हाल न_अंकD_CMD_RESET:
		native_cmd = CMD_FLASH_RESET;
		अवरोध;
	हाल न_अंकD_CMD_STATUS:
		native_cmd = CMD_STATUS_READ;
		अवरोध;
	हाल न_अंकD_CMD_READID:
		native_cmd = CMD_DEVICE_ID_READ;
		अवरोध;
	हाल न_अंकD_CMD_READOOB:
		native_cmd = CMD_SPARE_AREA_READ;
		अवरोध;
	हाल न_अंकD_CMD_ERASE1:
		native_cmd = CMD_BLOCK_ERASE;
		brcmnand_wp(mtd, 0);
		अवरोध;
	हाल न_अंकD_CMD_PARAM:
		native_cmd = CMD_PARAMETER_READ;
		अवरोध;
	हाल न_अंकD_CMD_SET_FEATURES:
	हाल न_अंकD_CMD_GET_FEATURES:
		brcmnand_low_level_op(host, LL_OP_CMD, command, false);
		brcmnand_low_level_op(host, LL_OP_ADDR, column, false);
		अवरोध;
	हाल न_अंकD_CMD_RNDOUT:
		native_cmd = CMD_PARAMETER_CHANGE_COL;
		addr &= ~((u64)(FC_BYTES - 1));
		/*
		 * HW quirk: PARAMETER_CHANGE_COL requires SECTOR_SIZE_1K=0
		 * NB: hwcfg.sector_size_1k may not be initialized yet
		 */
		अगर (brcmnand_get_sector_size_1k(host)) अणु
			host->hwcfg.sector_size_1k =
				brcmnand_get_sector_size_1k(host);
			brcmnand_set_sector_size_1k(host, 0);
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (!native_cmd)
		वापस;

	brcmnand_set_cmd_addr(mtd, addr);
	brcmnand_send_cmd(host, native_cmd);
	brcmnand_रुकोfunc(chip);

	अगर (native_cmd == CMD_PARAMETER_READ ||
			native_cmd == CMD_PARAMETER_CHANGE_COL) अणु
		/* Copy flash cache word-wise */
		u32 *flash_cache = (u32 *)ctrl->flash_cache;
		पूर्णांक i;

		brcmnand_soc_data_bus_prepare(ctrl->soc, true);

		/*
		 * Must cache the FLASH_CACHE now, since changes in
		 * SECTOR_SIZE_1K may invalidate it
		 */
		क्रम (i = 0; i < FC_WORDS; i++)
			/*
			 * Flash cache is big endian क्रम parameter pages, at
			 * least on STB SoCs
			 */
			flash_cache[i] = be32_to_cpu(brcmnand_पढ़ो_fc(ctrl, i));

		brcmnand_soc_data_bus_unprepare(ctrl->soc, true);

		/* Cleanup from HW quirk: restore SECTOR_SIZE_1K */
		अगर (host->hwcfg.sector_size_1k)
			brcmnand_set_sector_size_1k(host,
						    host->hwcfg.sector_size_1k);
	पूर्ण

	/* Re-enable protection is necessary only after erase */
	अगर (command == न_अंकD_CMD_ERASE1)
		brcmnand_wp(mtd, 1);
पूर्ण

अटल uपूर्णांक8_t brcmnand_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	uपूर्णांक8_t ret = 0;
	पूर्णांक addr, offs;

	चयन (host->last_cmd) अणु
	हाल न_अंकD_CMD_READID:
		अगर (host->last_byte < 4)
			ret = brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_ID) >>
				(24 - (host->last_byte << 3));
		अन्यथा अगर (host->last_byte < 8)
			ret = brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_ID_EXT) >>
				(56 - (host->last_byte << 3));
		अवरोध;

	हाल न_अंकD_CMD_READOOB:
		ret = oob_reg_पढ़ो(ctrl, host->last_byte);
		अवरोध;

	हाल न_अंकD_CMD_STATUS:
		ret = brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_INTFC_STATUS) &
					INTFC_FLASH_STATUS;
		अगर (wp_on) /* hide WP status */
			ret |= न_अंकD_STATUS_WP;
		अवरोध;

	हाल न_अंकD_CMD_PARAM:
	हाल न_अंकD_CMD_RNDOUT:
		addr = host->last_addr + host->last_byte;
		offs = addr & (FC_BYTES - 1);

		/* At FC_BYTES boundary, चयन to next column */
		अगर (host->last_byte > 0 && offs == 0)
			nand_change_पढ़ो_column_op(chip, addr, शून्य, 0, false);

		ret = ctrl->flash_cache[offs];
		अवरोध;
	हाल न_अंकD_CMD_GET_FEATURES:
		अगर (host->last_byte >= ONFI_SUBFEATURE_PARAM_LEN) अणु
			ret = 0;
		पूर्ण अन्यथा अणु
			bool last = host->last_byte ==
				ONFI_SUBFEATURE_PARAM_LEN - 1;
			brcmnand_low_level_op(host, LL_OP_RD, 0, last);
			ret = brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_LL_RDATA) & 0xff;
		पूर्ण
	पूर्ण

	dev_dbg(ctrl->dev, "read byte = 0x%02x\n", ret);
	host->last_byte++;

	वापस ret;
पूर्ण

अटल व्योम brcmnand_पढ़ो_buf(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++, buf++)
		*buf = brcmnand_पढ़ो_byte(chip);
पूर्ण

अटल व्योम brcmnand_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
			       पूर्णांक len)
अणु
	पूर्णांक i;
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);

	चयन (host->last_cmd) अणु
	हाल न_अंकD_CMD_SET_FEATURES:
		क्रम (i = 0; i < len; i++)
			brcmnand_low_level_op(host, LL_OP_WR, buf[i],
						  (i + 1) == len);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

/*
 *  Kick EDU engine
 */
अटल पूर्णांक brcmnand_edu_trans(काष्ठा brcmnand_host *host, u64 addr, u32 *buf,
			      u8 *oob, u32 len, u8 cmd)
अणु
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	काष्ठा brcmnand_cfg *cfg = &host->hwcfg;
	अचिन्हित दीर्घ समयo = msecs_to_jअगरfies(200);
	पूर्णांक ret = 0;
	पूर्णांक dir = (cmd == CMD_PAGE_READ ? DMA_FROM_DEVICE : DMA_TO_DEVICE);
	u8 edu_cmd = (cmd == CMD_PAGE_READ ? EDU_CMD_READ : EDU_CMD_WRITE);
	अचिन्हित पूर्णांक trans = len >> FC_SHIFT;
	dma_addr_t pa;

	dev_dbg(ctrl->dev, "EDU %s %p:%p\n", ((edu_cmd == EDU_CMD_READ) ?
					      "read" : "write"), buf, oob);

	pa = dma_map_single(ctrl->dev, buf, len, dir);
	अगर (dma_mapping_error(ctrl->dev, pa)) अणु
		dev_err(ctrl->dev, "unable to map buffer for EDU DMA\n");
		वापस -ENOMEM;
	पूर्ण

	ctrl->edu_pending = true;
	ctrl->edu_dram_addr = pa;
	ctrl->edu_ext_addr = addr;
	ctrl->edu_cmd = edu_cmd;
	ctrl->edu_count = trans;
	ctrl->sas = cfg->spare_area_size;
	ctrl->oob = oob;

	edu_ग_लिखोl(ctrl, EDU_DRAM_ADDR, (u32)ctrl->edu_dram_addr);
	edu_पढ़ोl(ctrl,  EDU_DRAM_ADDR);
	edu_ग_लिखोl(ctrl, EDU_EXT_ADDR, ctrl->edu_ext_addr);
	edu_पढ़ोl(ctrl, EDU_EXT_ADDR);
	edu_ग_लिखोl(ctrl, EDU_LENGTH, FC_BYTES);
	edu_पढ़ोl(ctrl, EDU_LENGTH);

	अगर (ctrl->oob && (ctrl->edu_cmd == EDU_CMD_WRITE)) अणु
		brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_CMD_ADDRESS,
				   ctrl->edu_ext_addr);
		brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_CMD_ADDRESS);
		ctrl->oob += ग_लिखो_oob_to_regs(ctrl,
					       1,
					       ctrl->oob, ctrl->sas,
					       ctrl->sector_size_1k);
	पूर्ण

	/* Start edu engine */
	mb(); /* flush previous ग_लिखोs */
	edu_ग_लिखोl(ctrl, EDU_CMD, ctrl->edu_cmd);
	edu_पढ़ोl(ctrl, EDU_CMD);

	अगर (रुको_क्रम_completion_समयout(&ctrl->edu_करोne, समयo) <= 0) अणु
		dev_err(ctrl->dev,
			"timeout waiting for EDU; status %#x, error status %#x\n",
			edu_पढ़ोl(ctrl, EDU_STATUS),
			edu_पढ़ोl(ctrl, EDU_ERR_STATUS));
	पूर्ण

	dma_unmap_single(ctrl->dev, pa, len, dir);

	/* पढ़ो last subpage oob */
	अगर (ctrl->oob && (ctrl->edu_cmd == EDU_CMD_READ)) अणु
		ctrl->oob += पढ़ो_oob_from_regs(ctrl,
						1,
						ctrl->oob, ctrl->sas,
						ctrl->sector_size_1k);
	पूर्ण

	/* क्रम program page check न_अंकD status */
	अगर (((brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_INTFC_STATUS) &
	      INTFC_FLASH_STATUS) & न_अंकD_STATUS_FAIL) &&
	    edu_cmd == EDU_CMD_WRITE) अणु
		dev_info(ctrl->dev, "program failed at %llx\n",
			 (अचिन्हित दीर्घ दीर्घ)addr);
		ret = -EIO;
	पूर्ण

	/* Make sure the EDU status is clean */
	अगर (edu_पढ़ोl(ctrl, EDU_STATUS) & EDU_STATUS_ACTIVE)
		dev_warn(ctrl->dev, "EDU still active: %#x\n",
			 edu_पढ़ोl(ctrl, EDU_STATUS));

	अगर (unlikely(edu_पढ़ोl(ctrl, EDU_ERR_STATUS) & EDU_ERR_STATUS_ERRACK)) अणु
		dev_warn(ctrl->dev, "EDU RBUS error at addr %llx\n",
			 (अचिन्हित दीर्घ दीर्घ)addr);
		ret = -EIO;
	पूर्ण

	ctrl->edu_pending = false;
	brcmnand_edu_init(ctrl);
	edu_ग_लिखोl(ctrl, EDU_STOP, 0); /* क्रमce stop */
	edu_पढ़ोl(ctrl, EDU_STOP);

	अगर (!ret && edu_cmd == EDU_CMD_READ) अणु
		u64 err_addr = 0;

		/*
		 * check क्रम ECC errors here, subpage ECC errors are
		 * retained in ECC error address रेजिस्टर
		 */
		err_addr = brcmnand_get_uncorrecc_addr(ctrl);
		अगर (!err_addr) अणु
			err_addr = brcmnand_get_correcc_addr(ctrl);
			अगर (err_addr)
				ret = -EUCLEAN;
		पूर्ण अन्यथा
			ret = -EBADMSG;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Conकाष्ठा a FLASH_DMA descriptor as part of a linked list. You must know the
 * following ahead of समय:
 *  - Is this descriptor the beginning or end of a linked list?
 *  - What is the (DMA) address of the next descriptor in the linked list?
 */
अटल पूर्णांक brcmnand_fill_dma_desc(काष्ठा brcmnand_host *host,
				  काष्ठा brcm_nand_dma_desc *desc, u64 addr,
				  dma_addr_t buf, u32 len, u8 dma_cmd,
				  bool begin, bool end,
				  dma_addr_t next_desc)
अणु
	स_रखो(desc, 0, माप(*desc));
	/* Descriptors are written in native byte order (wordwise) */
	desc->next_desc = lower_32_bits(next_desc);
	desc->next_desc_ext = upper_32_bits(next_desc);
	desc->cmd_irq = (dma_cmd << 24) |
		(end ? (0x03 << 8) : 0) | /* IRQ | STOP */
		(!!begin) | ((!!end) << 1); /* head, tail */
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	desc->cmd_irq |= 0x01 << 12;
#पूर्ण_अगर
	desc->dram_addr = lower_32_bits(buf);
	desc->dram_addr_ext = upper_32_bits(buf);
	desc->tfr_len = len;
	desc->total_len = len;
	desc->flash_addr = lower_32_bits(addr);
	desc->flash_addr_ext = upper_32_bits(addr);
	desc->cs = host->cs;
	desc->status_valid = 0x01;
	वापस 0;
पूर्ण

/*
 * Kick the FLASH_DMA engine, with a given DMA descriptor
 */
अटल व्योम brcmnand_dma_run(काष्ठा brcmnand_host *host, dma_addr_t desc)
अणु
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	अचिन्हित दीर्घ समयo = msecs_to_jअगरfies(100);

	flash_dma_ग_लिखोl(ctrl, FLASH_DMA_FIRST_DESC, lower_32_bits(desc));
	(व्योम)flash_dma_पढ़ोl(ctrl, FLASH_DMA_FIRST_DESC);
	अगर (ctrl->nand_version > 0x0602) अणु
		flash_dma_ग_लिखोl(ctrl, FLASH_DMA_FIRST_DESC_EXT,
				 upper_32_bits(desc));
		(व्योम)flash_dma_पढ़ोl(ctrl, FLASH_DMA_FIRST_DESC_EXT);
	पूर्ण

	/* Start FLASH_DMA engine */
	ctrl->dma_pending = true;
	mb(); /* flush previous ग_लिखोs */
	flash_dma_ग_लिखोl(ctrl, FLASH_DMA_CTRL, 0x03); /* wake | run */

	अगर (रुको_क्रम_completion_समयout(&ctrl->dma_करोne, समयo) <= 0) अणु
		dev_err(ctrl->dev,
				"timeout waiting for DMA; status %#x, error status %#x\n",
				flash_dma_पढ़ोl(ctrl, FLASH_DMA_STATUS),
				flash_dma_पढ़ोl(ctrl, FLASH_DMA_ERROR_STATUS));
	पूर्ण
	ctrl->dma_pending = false;
	flash_dma_ग_लिखोl(ctrl, FLASH_DMA_CTRL, 0); /* क्रमce stop */
पूर्ण

अटल पूर्णांक brcmnand_dma_trans(काष्ठा brcmnand_host *host, u64 addr, u32 *buf,
			      u8 *oob, u32 len, u8 dma_cmd)
अणु
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	dma_addr_t buf_pa;
	पूर्णांक dir = dma_cmd == CMD_PAGE_READ ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

	buf_pa = dma_map_single(ctrl->dev, buf, len, dir);
	अगर (dma_mapping_error(ctrl->dev, buf_pa)) अणु
		dev_err(ctrl->dev, "unable to map buffer for DMA\n");
		वापस -ENOMEM;
	पूर्ण

	brcmnand_fill_dma_desc(host, ctrl->dma_desc, addr, buf_pa, len,
				   dma_cmd, true, true, 0);

	brcmnand_dma_run(host, ctrl->dma_pa);

	dma_unmap_single(ctrl->dev, buf_pa, len, dir);

	अगर (ctrl->dma_desc->status_valid & FLASH_DMA_ECC_ERROR)
		वापस -EBADMSG;
	अन्यथा अगर (ctrl->dma_desc->status_valid & FLASH_DMA_CORR_ERROR)
		वापस -EUCLEAN;

	वापस 0;
पूर्ण

/*
 * Assumes proper CS is alपढ़ोy set
 */
अटल पूर्णांक brcmnand_पढ़ो_by_pio(काष्ठा mtd_info *mtd, काष्ठा nand_chip *chip,
				u64 addr, अचिन्हित पूर्णांक trans, u32 *buf,
				u8 *oob, u64 *err_addr)
अणु
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	पूर्णांक i, j, ret = 0;

	brcmnand_clear_ecc_addr(ctrl);

	क्रम (i = 0; i < trans; i++, addr += FC_BYTES) अणु
		brcmnand_set_cmd_addr(mtd, addr);
		/* SPARE_AREA_READ करोes not use ECC, so just use PAGE_READ */
		brcmnand_send_cmd(host, CMD_PAGE_READ);
		brcmnand_रुकोfunc(chip);

		अगर (likely(buf)) अणु
			brcmnand_soc_data_bus_prepare(ctrl->soc, false);

			क्रम (j = 0; j < FC_WORDS; j++, buf++)
				*buf = brcmnand_पढ़ो_fc(ctrl, j);

			brcmnand_soc_data_bus_unprepare(ctrl->soc, false);
		पूर्ण

		अगर (oob)
			oob += पढ़ो_oob_from_regs(ctrl, i, oob,
					mtd->oobsize / trans,
					host->hwcfg.sector_size_1k);

		अगर (!ret) अणु
			*err_addr = brcmnand_get_uncorrecc_addr(ctrl);

			अगर (*err_addr)
				ret = -EBADMSG;
		पूर्ण

		अगर (!ret) अणु
			*err_addr = brcmnand_get_correcc_addr(ctrl);

			अगर (*err_addr)
				ret = -EUCLEAN;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Check a page to see अगर it is erased (w/ bitflips) after an uncorrectable ECC
 * error
 *
 * Because the HW ECC संकेतs an ECC error अगर an erase paged has even a single
 * bitflip, we must check each ECC error to see अगर it is actually an erased
 * page with bitflips, not a truly corrupted page.
 *
 * On a real error, वापस a negative error code (-EBADMSG क्रम ECC error), and
 * buf will contain raw data.
 * Otherwise, buf माला_लो filled with 0xffs and वापस the maximum number of
 * bitflips-per-ECC-sector to the caller.
 *
 */
अटल पूर्णांक brcmstb_nand_verअगरy_erased_page(काष्ठा mtd_info *mtd,
		  काष्ठा nand_chip *chip, व्योम *buf, u64 addr)
अणु
	काष्ठा mtd_oob_region ecc;
	पूर्णांक i;
	पूर्णांक bitflips = 0;
	पूर्णांक page = addr >> chip->page_shअगरt;
	पूर्णांक ret;
	व्योम *ecc_bytes;
	व्योम *ecc_chunk;

	अगर (!buf)
		buf = nand_get_data_buf(chip);

	/* पढ़ो without ecc क्रम verअगरication */
	ret = chip->ecc.पढ़ो_page_raw(chip, buf, true, page);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < chip->ecc.steps; i++) अणु
		ecc_chunk = buf + chip->ecc.size * i;

		mtd_ooblayout_ecc(mtd, i, &ecc);
		ecc_bytes = chip->oob_poi + ecc.offset;

		ret = nand_check_erased_ecc_chunk(ecc_chunk, chip->ecc.size,
						  ecc_bytes, ecc.length,
						  शून्य, 0,
						  chip->ecc.strength);
		अगर (ret < 0)
			वापस ret;

		bitflips = max(bitflips, ret);
	पूर्ण

	वापस bitflips;
पूर्ण

अटल पूर्णांक brcmnand_पढ़ो(काष्ठा mtd_info *mtd, काष्ठा nand_chip *chip,
			 u64 addr, अचिन्हित पूर्णांक trans, u32 *buf, u8 *oob)
अणु
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	u64 err_addr = 0;
	पूर्णांक err;
	bool retry = true;
	bool edu_err = false;

	dev_dbg(ctrl->dev, "read %llx -> %p\n", (अचिन्हित दीर्घ दीर्घ)addr, buf);

try_dmaपढ़ो:
	brcmnand_clear_ecc_addr(ctrl);

	अगर (ctrl->dma_trans && (has_edu(ctrl) || !oob) &&
	    flash_dma_buf_ok(buf)) अणु
		err = ctrl->dma_trans(host, addr, buf, oob,
				      trans * FC_BYTES,
				      CMD_PAGE_READ);

		अगर (err) अणु
			अगर (mtd_is_bitflip_or_eccerr(err))
				err_addr = addr;
			अन्यथा
				वापस -EIO;
		पूर्ण

		अगर (has_edu(ctrl) && err_addr)
			edu_err = true;

	पूर्ण अन्यथा अणु
		अगर (oob)
			स_रखो(oob, 0x99, mtd->oobsize);

		err = brcmnand_पढ़ो_by_pio(mtd, chip, addr, trans, buf,
					       oob, &err_addr);
	पूर्ण

	अगर (mtd_is_eccerr(err)) अणु
		/*
		 * On controller version and 7.0, 7.1 , DMA पढ़ो after a
		 * prior PIO पढ़ो that reported uncorrectable error,
		 * the DMA engine captures this error following DMA पढ़ो
		 * cleared only on subsequent DMA पढ़ो, so just retry once
		 * to clear a possible false error reported क्रम current DMA
		 * पढ़ो
		 */
		अगर ((ctrl->nand_version == 0x0700) ||
		    (ctrl->nand_version == 0x0701)) अणु
			अगर (retry) अणु
				retry = false;
				जाओ try_dmaपढ़ो;
			पूर्ण
		पूर्ण

		/*
		 * Controller version 7.2 has hw encoder to detect erased page
		 * bitflips, apply sw verअगरication क्रम older controllers only
		 */
		अगर (ctrl->nand_version < 0x0702) अणु
			err = brcmstb_nand_verअगरy_erased_page(mtd, chip, buf,
							      addr);
			/* erased page bitflips corrected */
			अगर (err >= 0)
				वापस err;
		पूर्ण

		dev_dbg(ctrl->dev, "uncorrectable error at 0x%llx\n",
			(अचिन्हित दीर्घ दीर्घ)err_addr);
		mtd->ecc_stats.failed++;
		/* न_अंकD layer expects zero on ECC errors */
		वापस 0;
	पूर्ण

	अगर (mtd_is_bitflip(err)) अणु
		अचिन्हित पूर्णांक corrected = brcmnand_count_corrected(ctrl);

		/* in हाल of EDU correctable error we पढ़ो again using PIO */
		अगर (edu_err)
			err = brcmnand_पढ़ो_by_pio(mtd, chip, addr, trans, buf,
						   oob, &err_addr);

		dev_dbg(ctrl->dev, "corrected error at 0x%llx\n",
			(अचिन्हित दीर्घ दीर्घ)err_addr);
		mtd->ecc_stats.corrected += corrected;
		/* Always exceed the software-imposed threshold */
		वापस max(mtd->bitflip_threshold, corrected);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक brcmnand_पढ़ो_page(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
			      पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	u8 *oob = oob_required ? (u8 *)chip->oob_poi : शून्य;

	nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);

	वापस brcmnand_पढ़ो(mtd, chip, host->last_addr,
			mtd->ग_लिखोsize >> FC_SHIFT, (u32 *)buf, oob);
पूर्ण

अटल पूर्णांक brcmnand_पढ़ो_page_raw(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				  पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u8 *oob = oob_required ? (u8 *)chip->oob_poi : शून्य;
	पूर्णांक ret;

	nand_पढ़ो_page_op(chip, page, 0, शून्य, 0);

	brcmnand_set_ecc_enabled(host, 0);
	ret = brcmnand_पढ़ो(mtd, chip, host->last_addr,
			mtd->ग_लिखोsize >> FC_SHIFT, (u32 *)buf, oob);
	brcmnand_set_ecc_enabled(host, 1);
	वापस ret;
पूर्ण

अटल पूर्णांक brcmnand_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	वापस brcmnand_पढ़ो(mtd, chip, (u64)page << chip->page_shअगरt,
			mtd->ग_लिखोsize >> FC_SHIFT,
			शून्य, (u8 *)chip->oob_poi);
पूर्ण

अटल पूर्णांक brcmnand_पढ़ो_oob_raw(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);

	brcmnand_set_ecc_enabled(host, 0);
	brcmnand_पढ़ो(mtd, chip, (u64)page << chip->page_shअगरt,
		mtd->ग_लिखोsize >> FC_SHIFT,
		शून्य, (u8 *)chip->oob_poi);
	brcmnand_set_ecc_enabled(host, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक brcmnand_ग_लिखो(काष्ठा mtd_info *mtd, काष्ठा nand_chip *chip,
			  u64 addr, स्थिर u32 *buf, u8 *oob)
अणु
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	अचिन्हित पूर्णांक i, j, trans = mtd->ग_लिखोsize >> FC_SHIFT;
	पूर्णांक status, ret = 0;

	dev_dbg(ctrl->dev, "write %llx <- %p\n", (अचिन्हित दीर्घ दीर्घ)addr, buf);

	अगर (unlikely((अचिन्हित दीर्घ)buf & 0x03)) अणु
		dev_warn(ctrl->dev, "unaligned buffer: %p\n", buf);
		buf = (u32 *)((अचिन्हित दीर्घ)buf & ~0x03);
	पूर्ण

	brcmnand_wp(mtd, 0);

	क्रम (i = 0; i < ctrl->max_oob; i += 4)
		oob_reg_ग_लिखो(ctrl, i, 0xffffffff);

	अगर (mtd->oops_panic_ग_लिखो)
		/* चयन to पूर्णांकerrupt polling and PIO mode */
		disable_ctrl_irqs(ctrl);

	अगर (use_dma(ctrl) && (has_edu(ctrl) || !oob) && flash_dma_buf_ok(buf)) अणु
		अगर (ctrl->dma_trans(host, addr, (u32 *)buf, oob, mtd->ग_लिखोsize,
				    CMD_PROGRAM_PAGE))

			ret = -EIO;

		जाओ out;
	पूर्ण

	क्रम (i = 0; i < trans; i++, addr += FC_BYTES) अणु
		/* full address MUST be set beक्रमe populating FC */
		brcmnand_set_cmd_addr(mtd, addr);

		अगर (buf) अणु
			brcmnand_soc_data_bus_prepare(ctrl->soc, false);

			क्रम (j = 0; j < FC_WORDS; j++, buf++)
				brcmnand_ग_लिखो_fc(ctrl, j, *buf);

			brcmnand_soc_data_bus_unprepare(ctrl->soc, false);
		पूर्ण अन्यथा अगर (oob) अणु
			क्रम (j = 0; j < FC_WORDS; j++)
				brcmnand_ग_लिखो_fc(ctrl, j, 0xffffffff);
		पूर्ण

		अगर (oob) अणु
			oob += ग_लिखो_oob_to_regs(ctrl, i, oob,
					mtd->oobsize / trans,
					host->hwcfg.sector_size_1k);
		पूर्ण

		/* we cannot use SPARE_AREA_PROGRAM when PARTIAL_PAGE_EN=0 */
		brcmnand_send_cmd(host, CMD_PROGRAM_PAGE);
		status = brcmnand_रुकोfunc(chip);

		अगर (status & न_अंकD_STATUS_FAIL) अणु
			dev_info(ctrl->dev, "program failed at %llx\n",
				(अचिन्हित दीर्घ दीर्घ)addr);
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	brcmnand_wp(mtd, 1);
	वापस ret;
पूर्ण

अटल पूर्णांक brcmnand_ग_लिखो_page(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
			       पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	व्योम *oob = oob_required ? chip->oob_poi : शून्य;

	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);
	brcmnand_ग_लिखो(mtd, chip, host->last_addr, (स्थिर u32 *)buf, oob);

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक brcmnand_ग_लिखो_page_raw(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				   पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	व्योम *oob = oob_required ? chip->oob_poi : शून्य;

	nand_prog_page_begin_op(chip, page, 0, शून्य, 0);
	brcmnand_set_ecc_enabled(host, 0);
	brcmnand_ग_लिखो(mtd, chip, host->last_addr, (स्थिर u32 *)buf, oob);
	brcmnand_set_ecc_enabled(host, 1);

	वापस nand_prog_page_end_op(chip);
पूर्ण

अटल पूर्णांक brcmnand_ग_लिखो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	वापस brcmnand_ग_लिखो(nand_to_mtd(chip), chip,
			      (u64)page << chip->page_shअगरt, शून्य,
			      chip->oob_poi);
पूर्ण

अटल पूर्णांक brcmnand_ग_लिखो_oob_raw(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	पूर्णांक ret;

	brcmnand_set_ecc_enabled(host, 0);
	ret = brcmnand_ग_लिखो(mtd, chip, (u64)page << chip->page_shअगरt, शून्य,
				 (u8 *)chip->oob_poi);
	brcmnand_set_ecc_enabled(host, 1);

	वापस ret;
पूर्ण

/***********************************************************************
 * Per-CS setup (1 न_अंकD device)
 ***********************************************************************/

अटल पूर्णांक brcmnand_set_cfg(काष्ठा brcmnand_host *host,
			    काष्ठा brcmnand_cfg *cfg)
अणु
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	काष्ठा nand_chip *chip = &host->chip;
	u16 cfg_offs = brcmnand_cs_offset(ctrl, host->cs, BRCMन_अंकD_CS_CFG);
	u16 cfg_ext_offs = brcmnand_cs_offset(ctrl, host->cs,
			BRCMन_अंकD_CS_CFG_EXT);
	u16 acc_control_offs = brcmnand_cs_offset(ctrl, host->cs,
			BRCMन_अंकD_CS_ACC_CONTROL);
	u8 block_size = 0, page_size = 0, device_size = 0;
	u32 पंचांगp;

	अगर (ctrl->block_sizes) अणु
		पूर्णांक i, found;

		क्रम (i = 0, found = 0; ctrl->block_sizes[i]; i++)
			अगर (ctrl->block_sizes[i] * 1024 == cfg->block_size) अणु
				block_size = i;
				found = 1;
			पूर्ण
		अगर (!found) अणु
			dev_warn(ctrl->dev, "invalid block size %u\n",
					cfg->block_size);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		block_size = ffs(cfg->block_size) - ffs(BRCMन_अंकD_MIN_BLOCKSIZE);
	पूर्ण

	अगर (cfg->block_size < BRCMन_अंकD_MIN_BLOCKSIZE || (ctrl->max_block_size &&
				cfg->block_size > ctrl->max_block_size)) अणु
		dev_warn(ctrl->dev, "invalid block size %u\n",
				cfg->block_size);
		block_size = 0;
	पूर्ण

	अगर (ctrl->page_sizes) अणु
		पूर्णांक i, found;

		क्रम (i = 0, found = 0; ctrl->page_sizes[i]; i++)
			अगर (ctrl->page_sizes[i] == cfg->page_size) अणु
				page_size = i;
				found = 1;
			पूर्ण
		अगर (!found) अणु
			dev_warn(ctrl->dev, "invalid page size %u\n",
					cfg->page_size);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		page_size = ffs(cfg->page_size) - ffs(BRCMन_अंकD_MIN_PAGESIZE);
	पूर्ण

	अगर (cfg->page_size < BRCMन_अंकD_MIN_PAGESIZE || (ctrl->max_page_size &&
				cfg->page_size > ctrl->max_page_size)) अणु
		dev_warn(ctrl->dev, "invalid page size %u\n", cfg->page_size);
		वापस -EINVAL;
	पूर्ण

	अगर (fls64(cfg->device_size) < fls64(BRCMन_अंकD_MIN_DEVSIZE)) अणु
		dev_warn(ctrl->dev, "invalid device size 0x%llx\n",
			(अचिन्हित दीर्घ दीर्घ)cfg->device_size);
		वापस -EINVAL;
	पूर्ण
	device_size = fls64(cfg->device_size) - fls64(BRCMन_अंकD_MIN_DEVSIZE);

	पंचांगp = (cfg->blk_adr_bytes << CFG_BLK_ADR_BYTES_SHIFT) |
		(cfg->col_adr_bytes << CFG_COL_ADR_BYTES_SHIFT) |
		(cfg->ful_adr_bytes << CFG_FUL_ADR_BYTES_SHIFT) |
		(!!(cfg->device_width == 16) << CFG_BUS_WIDTH_SHIFT) |
		(device_size << CFG_DEVICE_SIZE_SHIFT);
	अगर (cfg_offs == cfg_ext_offs) अणु
		पंचांगp |= (page_size << ctrl->page_size_shअगरt) |
		       (block_size << CFG_BLK_SIZE_SHIFT);
		nand_ग_लिखोreg(ctrl, cfg_offs, पंचांगp);
	पूर्ण अन्यथा अणु
		nand_ग_लिखोreg(ctrl, cfg_offs, पंचांगp);
		पंचांगp = (page_size << CFG_EXT_PAGE_SIZE_SHIFT) |
		      (block_size << CFG_EXT_BLK_SIZE_SHIFT);
		nand_ग_लिखोreg(ctrl, cfg_ext_offs, पंचांगp);
	पूर्ण

	पंचांगp = nand_पढ़ोreg(ctrl, acc_control_offs);
	पंचांगp &= ~brcmnand_ecc_level_mask(ctrl);
	पंचांगp &= ~brcmnand_spare_area_mask(ctrl);
	अगर (ctrl->nand_version >= 0x0302) अणु
		पंचांगp |= cfg->ecc_level << न_अंकD_ACC_CONTROL_ECC_SHIFT;
		पंचांगp |= cfg->spare_area_size;
	पूर्ण
	nand_ग_लिखोreg(ctrl, acc_control_offs, पंचांगp);

	brcmnand_set_sector_size_1k(host, cfg->sector_size_1k);

	/* threshold = उच्चमान(BCH-level * 0.75) */
	brcmnand_wr_corr_thresh(host, DIV_ROUND_UP(chip->ecc.strength * 3, 4));

	वापस 0;
पूर्ण

अटल व्योम brcmnand_prपूर्णांक_cfg(काष्ठा brcmnand_host *host,
			       अक्षर *buf, काष्ठा brcmnand_cfg *cfg)
अणु
	buf += प्र_लिखो(buf,
		"%lluMiB total, %uKiB blocks, %u%s pages, %uB OOB, %u-bit",
		(अचिन्हित दीर्घ दीर्घ)cfg->device_size >> 20,
		cfg->block_size >> 10,
		cfg->page_size >= 1024 ? cfg->page_size >> 10 : cfg->page_size,
		cfg->page_size >= 1024 ? "KiB" : "B",
		cfg->spare_area_size, cfg->device_width);

	/* Account क्रम Hamming ECC and क्रम BCH 512B vs 1KiB sectors */
	अगर (is_hamming_ecc(host->ctrl, cfg))
		प्र_लिखो(buf, ", Hamming ECC");
	अन्यथा अगर (cfg->sector_size_1k)
		प्र_लिखो(buf, ", BCH-%u (1KiB sector)", cfg->ecc_level << 1);
	अन्यथा
		प्र_लिखो(buf, ", BCH-%u", cfg->ecc_level);
पूर्ण

/*
 * Minimum number of bytes to address a page. Calculated as:
 *     roundup(log2(size / page-size) / 8)
 *
 * NB: the following करोes not "round up" क्रम non-घातer-of-2 'size'; but this is
 *     OK because many other things will अवरोध अगर 'size' is irregular...
 */
अटल अंतरभूत पूर्णांक get_blk_adr_bytes(u64 size, u32 ग_लिखोsize)
अणु
	वापस ALIGN(ilog2(size) - ilog2(ग_लिखोsize), 8) >> 3;
पूर्ण

अटल पूर्णांक brcmnand_setup_dev(काष्ठा brcmnand_host *host)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(&host->chip);
	काष्ठा nand_chip *chip = &host->chip;
	स्थिर काष्ठा nand_ecc_props *requirements =
		nanddev_get_ecc_requirements(&chip->base);
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	काष्ठा brcmnand_cfg *cfg = &host->hwcfg;
	अक्षर msg[128];
	u32 offs, पंचांगp, oob_sector;
	पूर्णांक ret;

	स_रखो(cfg, 0, माप(*cfg));

	ret = of_property_पढ़ो_u32(nand_get_flash_node(chip),
				   "brcm,nand-oob-sector-size",
				   &oob_sector);
	अगर (ret) अणु
		/* Use detected size */
		cfg->spare_area_size = mtd->oobsize /
					(mtd->ग_लिखोsize >> FC_SHIFT);
	पूर्ण अन्यथा अणु
		cfg->spare_area_size = oob_sector;
	पूर्ण
	अगर (cfg->spare_area_size > ctrl->max_oob)
		cfg->spare_area_size = ctrl->max_oob;
	/*
	 * Set oobsize to be consistent with controller's spare_area_size, as
	 * the rest is inaccessible.
	 */
	mtd->oobsize = cfg->spare_area_size * (mtd->ग_लिखोsize >> FC_SHIFT);

	cfg->device_size = mtd->size;
	cfg->block_size = mtd->erasesize;
	cfg->page_size = mtd->ग_लिखोsize;
	cfg->device_width = (chip->options & न_अंकD_BUSWIDTH_16) ? 16 : 8;
	cfg->col_adr_bytes = 2;
	cfg->blk_adr_bytes = get_blk_adr_bytes(mtd->size, mtd->ग_लिखोsize);

	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST) अणु
		dev_err(ctrl->dev, "only HW ECC supported; selected: %d\n",
			chip->ecc.engine_type);
		वापस -EINVAL;
	पूर्ण

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_UNKNOWN) अणु
		अगर (chip->ecc.strength == 1 && chip->ecc.size == 512)
			/* Default to Hamming क्रम 1-bit ECC, अगर unspecअगरied */
			chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;
		अन्यथा
			/* Otherwise, BCH */
			chip->ecc.algo = न_अंकD_ECC_ALGO_BCH;
	पूर्ण

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_HAMMING &&
	    (chip->ecc.strength != 1 || chip->ecc.size != 512)) अणु
		dev_err(ctrl->dev, "invalid Hamming params: %d bits per %d bytes\n",
			chip->ecc.strength, chip->ecc.size);
		वापस -EINVAL;
	पूर्ण

	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_NONE &&
	    (!chip->ecc.size || !chip->ecc.strength)) अणु
		अगर (requirements->step_size && requirements->strength) अणु
			/* use detected ECC parameters */
			chip->ecc.size = requirements->step_size;
			chip->ecc.strength = requirements->strength;
			dev_info(ctrl->dev, "Using ECC step-size %d, strength %d\n",
				chip->ecc.size, chip->ecc.strength);
		पूर्ण
	पूर्ण

	चयन (chip->ecc.size) अणु
	हाल 512:
		अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_HAMMING)
			cfg->ecc_level = 15;
		अन्यथा
			cfg->ecc_level = chip->ecc.strength;
		cfg->sector_size_1k = 0;
		अवरोध;
	हाल 1024:
		अगर (!(ctrl->features & BRCMन_अंकD_HAS_1K_SECTORS)) अणु
			dev_err(ctrl->dev, "1KB sectors not supported\n");
			वापस -EINVAL;
		पूर्ण
		अगर (chip->ecc.strength & 0x1) अणु
			dev_err(ctrl->dev,
				"odd ECC not supported with 1KB sectors\n");
			वापस -EINVAL;
		पूर्ण

		cfg->ecc_level = chip->ecc.strength >> 1;
		cfg->sector_size_1k = 1;
		अवरोध;
	शेष:
		dev_err(ctrl->dev, "unsupported ECC size: %d\n",
			chip->ecc.size);
		वापस -EINVAL;
	पूर्ण

	cfg->ful_adr_bytes = cfg->blk_adr_bytes;
	अगर (mtd->ग_लिखोsize > 512)
		cfg->ful_adr_bytes += cfg->col_adr_bytes;
	अन्यथा
		cfg->ful_adr_bytes += 1;

	ret = brcmnand_set_cfg(host, cfg);
	अगर (ret)
		वापस ret;

	brcmnand_set_ecc_enabled(host, 1);

	brcmnand_prपूर्णांक_cfg(host, msg, cfg);
	dev_info(ctrl->dev, "detected %s\n", msg);

	/* Configure ACC_CONTROL */
	offs = brcmnand_cs_offset(ctrl, host->cs, BRCMन_अंकD_CS_ACC_CONTROL);
	पंचांगp = nand_पढ़ोreg(ctrl, offs);
	पंचांगp &= ~ACC_CONTROL_PARTIAL_PAGE;
	पंचांगp &= ~ACC_CONTROL_RD_ERASED;

	/* We need to turn on Read from erased paged रक्षित by ECC */
	अगर (ctrl->nand_version >= 0x0702)
		पंचांगp |= ACC_CONTROL_RD_ERASED;
	पंचांगp &= ~ACC_CONTROL_FAST_PGM_RDIN;
	अगर (ctrl->features & BRCMन_अंकD_HAS_PREFETCH)
		पंचांगp &= ~ACC_CONTROL_PREFETCH;

	nand_ग_लिखोreg(ctrl, offs, पंचांगp);

	वापस 0;
पूर्ण

अटल पूर्णांक brcmnand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा brcmnand_host *host = nand_get_controller_data(chip);
	पूर्णांक ret;

	chip->options |= न_अंकD_NO_SUBPAGE_WRITE;
	/*
	 * Aव्योम (क्रम instance) kmap()'d buffers from JFFS2, which we can't DMA
	 * to/from, and have nand_base pass us a bounce buffer instead, as
	 * needed.
	 */
	chip->options |= न_अंकD_USES_DMA;

	अगर (chip->bbt_options & न_अंकD_BBT_USE_FLASH)
		chip->bbt_options |= न_अंकD_BBT_NO_OOB;

	अगर (brcmnand_setup_dev(host))
		वापस -ENXIO;

	chip->ecc.size = host->hwcfg.sector_size_1k ? 1024 : 512;

	/* only use our पूर्णांकernal HW threshold */
	mtd->bitflip_threshold = 1;

	ret = brcmstb_choose_ecc_layout(host);

	/* If OOB is written with ECC enabled it will cause ECC errors */
	अगर (is_hamming_ecc(host->ctrl, &host->hwcfg)) अणु
		chip->ecc.ग_लिखो_oob = brcmnand_ग_लिखो_oob_raw;
		chip->ecc.पढ़ो_oob = brcmnand_पढ़ो_oob_raw;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops brcmnand_controller_ops = अणु
	.attach_chip = brcmnand_attach_chip,
पूर्ण;

अटल पूर्णांक brcmnand_init_cs(काष्ठा brcmnand_host *host, काष्ठा device_node *dn)
अणु
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	काष्ठा platक्रमm_device *pdev = host->pdev;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;
	u16 cfg_offs;

	ret = of_property_पढ़ो_u32(dn, "reg", &host->cs);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't get chip-select\n");
		वापस -ENXIO;
	पूर्ण

	mtd = nand_to_mtd(&host->chip);
	chip = &host->chip;

	nand_set_flash_node(chip, dn);
	nand_set_controller_data(chip, host);
	mtd->name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "brcmnand.%d",
				   host->cs);
	अगर (!mtd->name)
		वापस -ENOMEM;

	mtd->owner = THIS_MODULE;
	mtd->dev.parent = &pdev->dev;

	chip->legacy.cmd_ctrl = brcmnand_cmd_ctrl;
	chip->legacy.cmdfunc = brcmnand_cmdfunc;
	chip->legacy.रुकोfunc = brcmnand_रुकोfunc;
	chip->legacy.पढ़ो_byte = brcmnand_पढ़ो_byte;
	chip->legacy.पढ़ो_buf = brcmnand_पढ़ो_buf;
	chip->legacy.ग_लिखो_buf = brcmnand_ग_लिखो_buf;

	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;
	chip->ecc.पढ़ो_page = brcmnand_पढ़ो_page;
	chip->ecc.ग_लिखो_page = brcmnand_ग_लिखो_page;
	chip->ecc.पढ़ो_page_raw = brcmnand_पढ़ो_page_raw;
	chip->ecc.ग_लिखो_page_raw = brcmnand_ग_लिखो_page_raw;
	chip->ecc.ग_लिखो_oob_raw = brcmnand_ग_लिखो_oob_raw;
	chip->ecc.पढ़ो_oob_raw = brcmnand_पढ़ो_oob_raw;
	chip->ecc.पढ़ो_oob = brcmnand_पढ़ो_oob;
	chip->ecc.ग_लिखो_oob = brcmnand_ग_लिखो_oob;

	chip->controller = &ctrl->controller;

	/*
	 * The bootloader might have configured 16bit mode but
	 * न_अंकD READID command only works in 8bit mode. We क्रमce
	 * 8bit mode here to ensure that न_अंकD READID commands works.
	 */
	cfg_offs = brcmnand_cs_offset(ctrl, host->cs, BRCMन_अंकD_CS_CFG);
	nand_ग_लिखोreg(ctrl, cfg_offs,
		      nand_पढ़ोreg(ctrl, cfg_offs) & ~CFG_BUS_WIDTH);

	ret = nand_scan(chip, 1);
	अगर (ret)
		वापस ret;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret)
		nand_cleanup(chip);

	वापस ret;
पूर्ण

अटल व्योम brcmnand_save_restore_cs_config(काष्ठा brcmnand_host *host,
					    पूर्णांक restore)
अणु
	काष्ठा brcmnand_controller *ctrl = host->ctrl;
	u16 cfg_offs = brcmnand_cs_offset(ctrl, host->cs, BRCMन_अंकD_CS_CFG);
	u16 cfg_ext_offs = brcmnand_cs_offset(ctrl, host->cs,
			BRCMन_अंकD_CS_CFG_EXT);
	u16 acc_control_offs = brcmnand_cs_offset(ctrl, host->cs,
			BRCMन_अंकD_CS_ACC_CONTROL);
	u16 t1_offs = brcmnand_cs_offset(ctrl, host->cs, BRCMन_अंकD_CS_TIMING1);
	u16 t2_offs = brcmnand_cs_offset(ctrl, host->cs, BRCMन_अंकD_CS_TIMING2);

	अगर (restore) अणु
		nand_ग_लिखोreg(ctrl, cfg_offs, host->hwcfg.config);
		अगर (cfg_offs != cfg_ext_offs)
			nand_ग_लिखोreg(ctrl, cfg_ext_offs,
				      host->hwcfg.config_ext);
		nand_ग_लिखोreg(ctrl, acc_control_offs, host->hwcfg.acc_control);
		nand_ग_लिखोreg(ctrl, t1_offs, host->hwcfg.timing_1);
		nand_ग_लिखोreg(ctrl, t2_offs, host->hwcfg.timing_2);
	पूर्ण अन्यथा अणु
		host->hwcfg.config = nand_पढ़ोreg(ctrl, cfg_offs);
		अगर (cfg_offs != cfg_ext_offs)
			host->hwcfg.config_ext =
				nand_पढ़ोreg(ctrl, cfg_ext_offs);
		host->hwcfg.acc_control = nand_पढ़ोreg(ctrl, acc_control_offs);
		host->hwcfg.timing_1 = nand_पढ़ोreg(ctrl, t1_offs);
		host->hwcfg.timing_2 = nand_पढ़ोreg(ctrl, t2_offs);
	पूर्ण
पूर्ण

अटल पूर्णांक brcmnand_suspend(काष्ठा device *dev)
अणु
	काष्ठा brcmnand_controller *ctrl = dev_get_drvdata(dev);
	काष्ठा brcmnand_host *host;

	list_क्रम_each_entry(host, &ctrl->host_list, node)
		brcmnand_save_restore_cs_config(host, 0);

	ctrl->nand_cs_nand_select = brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_CS_SELECT);
	ctrl->nand_cs_nand_xor = brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_CS_XOR);
	ctrl->corr_stat_threshold =
		brcmnand_पढ़ो_reg(ctrl, BRCMन_अंकD_CORR_THRESHOLD);

	अगर (has_flash_dma(ctrl))
		ctrl->flash_dma_mode = flash_dma_पढ़ोl(ctrl, FLASH_DMA_MODE);
	अन्यथा अगर (has_edu(ctrl))
		ctrl->edu_config = edu_पढ़ोl(ctrl, EDU_CONFIG);

	वापस 0;
पूर्ण

अटल पूर्णांक brcmnand_resume(काष्ठा device *dev)
अणु
	काष्ठा brcmnand_controller *ctrl = dev_get_drvdata(dev);
	काष्ठा brcmnand_host *host;

	अगर (has_flash_dma(ctrl)) अणु
		flash_dma_ग_लिखोl(ctrl, FLASH_DMA_MODE, ctrl->flash_dma_mode);
		flash_dma_ग_लिखोl(ctrl, FLASH_DMA_ERROR_STATUS, 0);
	पूर्ण

	अगर (has_edu(ctrl)) अणु
		ctrl->edu_config = edu_पढ़ोl(ctrl, EDU_CONFIG);
		edu_ग_लिखोl(ctrl, EDU_CONFIG, ctrl->edu_config);
		edu_पढ़ोl(ctrl, EDU_CONFIG);
		brcmnand_edu_init(ctrl);
	पूर्ण

	brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_CS_SELECT, ctrl->nand_cs_nand_select);
	brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_CS_XOR, ctrl->nand_cs_nand_xor);
	brcmnand_ग_लिखो_reg(ctrl, BRCMन_अंकD_CORR_THRESHOLD,
			ctrl->corr_stat_threshold);
	अगर (ctrl->soc) अणु
		/* Clear/re-enable पूर्णांकerrupt */
		ctrl->soc->ctlrdy_ack(ctrl->soc);
		ctrl->soc->ctlrdy_set_enabled(ctrl->soc, true);
	पूर्ण

	list_क्रम_each_entry(host, &ctrl->host_list, node) अणु
		काष्ठा nand_chip *chip = &host->chip;

		brcmnand_save_restore_cs_config(host, 1);

		/* Reset the chip, required by some chips after घातer-up */
		nand_reset_op(chip);
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा dev_pm_ops brcmnand_pm_ops = अणु
	.suspend		= brcmnand_suspend,
	.resume			= brcmnand_resume,
पूर्ण;
EXPORT_SYMBOL_GPL(brcmnand_pm_ops);

अटल स्थिर काष्ठा of_device_id brcmnand_of_match[] = अणु
	अणु .compatible = "brcm,brcmnand-v2.1" पूर्ण,
	अणु .compatible = "brcm,brcmnand-v2.2" पूर्ण,
	अणु .compatible = "brcm,brcmnand-v4.0" पूर्ण,
	अणु .compatible = "brcm,brcmnand-v5.0" पूर्ण,
	अणु .compatible = "brcm,brcmnand-v6.0" पूर्ण,
	अणु .compatible = "brcm,brcmnand-v6.1" पूर्ण,
	अणु .compatible = "brcm,brcmnand-v6.2" पूर्ण,
	अणु .compatible = "brcm,brcmnand-v7.0" पूर्ण,
	अणु .compatible = "brcm,brcmnand-v7.1" पूर्ण,
	अणु .compatible = "brcm,brcmnand-v7.2" पूर्ण,
	अणु .compatible = "brcm,brcmnand-v7.3" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, brcmnand_of_match);

/***********************************************************************
 * Platक्रमm driver setup (per controller)
 ***********************************************************************/
अटल पूर्णांक brcmnand_edu_setup(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा brcmnand_controller *ctrl = dev_get_drvdata(&pdev->dev);
	काष्ठा resource *res;
	पूर्णांक ret;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "flash-edu");
	अगर (res) अणु
		ctrl->edu_base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(ctrl->edu_base))
			वापस PTR_ERR(ctrl->edu_base);

		ctrl->edu_offsets = edu_regs;

		edu_ग_लिखोl(ctrl, EDU_CONFIG, EDU_CONFIG_MODE_न_अंकD |
			   EDU_CONFIG_SWAP_CFG);
		edu_पढ़ोl(ctrl, EDU_CONFIG);

		/* initialize edu */
		brcmnand_edu_init(ctrl);

		ctrl->edu_irq = platक्रमm_get_irq_optional(pdev, 1);
		अगर (ctrl->edu_irq < 0) अणु
			dev_warn(dev,
				 "FLASH EDU enabled, using ctlrdy irq\n");
		पूर्ण अन्यथा अणु
			ret = devm_request_irq(dev, ctrl->edu_irq,
					       brcmnand_edu_irq, 0,
					       "brcmnand-edu", ctrl);
			अगर (ret < 0) अणु
				dev_err(ctrl->dev, "can't allocate IRQ %d: error %d\n",
					ctrl->edu_irq, ret);
				वापस ret;
			पूर्ण

			dev_info(dev, "FLASH EDU enabled using irq %u\n",
				 ctrl->edu_irq);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक brcmnand_probe(काष्ठा platक्रमm_device *pdev, काष्ठा brcmnand_soc *soc)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *dn = dev->of_node, *child;
	काष्ठा brcmnand_controller *ctrl;
	काष्ठा resource *res;
	पूर्णांक ret;

	/* We only support device-tree instantiation */
	अगर (!dn)
		वापस -ENODEV;

	अगर (!of_match_node(brcmnand_of_match, dn))
		वापस -ENODEV;

	ctrl = devm_kzalloc(dev, माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस -ENOMEM;

	dev_set_drvdata(dev, ctrl);
	ctrl->dev = dev;

	init_completion(&ctrl->करोne);
	init_completion(&ctrl->dma_करोne);
	init_completion(&ctrl->edu_करोne);
	nand_controller_init(&ctrl->controller);
	ctrl->controller.ops = &brcmnand_controller_ops;
	INIT_LIST_HEAD(&ctrl->host_list);

	/* न_अंकD रेजिस्टर range */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ctrl->nand_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ctrl->nand_base))
		वापस PTR_ERR(ctrl->nand_base);

	/* Enable घड़ी beक्रमe using न_अंकD रेजिस्टरs */
	ctrl->clk = devm_clk_get(dev, "nand");
	अगर (!IS_ERR(ctrl->clk)) अणु
		ret = clk_prepare_enable(ctrl->clk);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = PTR_ERR(ctrl->clk);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;

		ctrl->clk = शून्य;
	पूर्ण

	/* Initialize न_अंकD revision */
	ret = brcmnand_revision_init(ctrl);
	अगर (ret)
		जाओ err;

	/*
	 * Most chips have this cache at a fixed offset within 'nand' block.
	 * Some must specअगरy this region separately.
	 */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "nand-cache");
	अगर (res) अणु
		ctrl->nand_fc = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(ctrl->nand_fc)) अणु
			ret = PTR_ERR(ctrl->nand_fc);
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctrl->nand_fc = ctrl->nand_base +
				ctrl->reg_offsets[BRCMन_अंकD_FC_BASE];
	पूर्ण

	/* FLASH_DMA */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "flash-dma");
	अगर (res) अणु
		ctrl->flash_dma_base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(ctrl->flash_dma_base)) अणु
			ret = PTR_ERR(ctrl->flash_dma_base);
			जाओ err;
		पूर्ण

		/* initialize the dma version */
		brcmnand_flash_dma_revision_init(ctrl);

		ret = -EIO;
		अगर (ctrl->nand_version >= 0x0700)
			ret = dma_set_mask_and_coherent(&pdev->dev,
							DMA_BIT_MASK(40));
		अगर (ret)
			ret = dma_set_mask_and_coherent(&pdev->dev,
							DMA_BIT_MASK(32));
		अगर (ret)
			जाओ err;

		/* linked-list and stop on error */
		flash_dma_ग_लिखोl(ctrl, FLASH_DMA_MODE, FLASH_DMA_MODE_MASK);
		flash_dma_ग_लिखोl(ctrl, FLASH_DMA_ERROR_STATUS, 0);

		/* Allocate descriptor(s) */
		ctrl->dma_desc = dmam_alloc_coherent(dev,
						     माप(*ctrl->dma_desc),
						     &ctrl->dma_pa, GFP_KERNEL);
		अगर (!ctrl->dma_desc) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		ctrl->dma_irq = platक्रमm_get_irq(pdev, 1);
		अगर ((पूर्णांक)ctrl->dma_irq < 0) अणु
			dev_err(dev, "missing FLASH_DMA IRQ\n");
			ret = -ENODEV;
			जाओ err;
		पूर्ण

		ret = devm_request_irq(dev, ctrl->dma_irq,
				brcmnand_dma_irq, 0, DRV_NAME,
				ctrl);
		अगर (ret < 0) अणु
			dev_err(dev, "can't allocate IRQ %d: error %d\n",
					ctrl->dma_irq, ret);
			जाओ err;
		पूर्ण

		dev_info(dev, "enabling FLASH_DMA\n");
		/* set flash dma transfer function to call */
		ctrl->dma_trans = brcmnand_dma_trans;
	पूर्ण अन्यथा	अणु
		ret = brcmnand_edu_setup(pdev);
		अगर (ret < 0)
			जाओ err;

		अगर (has_edu(ctrl))
			/* set edu transfer function to call */
			ctrl->dma_trans = brcmnand_edu_trans;
	पूर्ण

	/* Disable स्वतःmatic device ID config, direct addressing */
	brcmnand_rmw_reg(ctrl, BRCMन_अंकD_CS_SELECT,
			 CS_SELECT_AUTO_DEVICE_ID_CFG | 0xff, 0, 0);
	/* Disable XOR addressing */
	brcmnand_rmw_reg(ctrl, BRCMन_अंकD_CS_XOR, 0xff, 0, 0);

	अगर (ctrl->features & BRCMन_अंकD_HAS_WP) अणु
		/* Permanently disable ग_लिखो protection */
		अगर (wp_on == 2)
			brcmnand_set_wp(ctrl, false);
	पूर्ण अन्यथा अणु
		wp_on = 0;
	पूर्ण

	/* IRQ */
	ctrl->irq = platक्रमm_get_irq(pdev, 0);
	अगर ((पूर्णांक)ctrl->irq < 0) अणु
		dev_err(dev, "no IRQ defined\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/*
	 * Some SoCs पूर्णांकegrate this controller (e.g., its पूर्णांकerrupt bits) in
	 * पूर्णांकeresting ways
	 */
	अगर (soc) अणु
		ctrl->soc = soc;

		ret = devm_request_irq(dev, ctrl->irq, brcmnand_irq, 0,
				       DRV_NAME, ctrl);

		/* Enable पूर्णांकerrupt */
		ctrl->soc->ctlrdy_ack(ctrl->soc);
		ctrl->soc->ctlrdy_set_enabled(ctrl->soc, true);
	पूर्ण अन्यथा अणु
		/* Use standard पूर्णांकerrupt infraकाष्ठाure */
		ret = devm_request_irq(dev, ctrl->irq, brcmnand_ctlrdy_irq, 0,
				       DRV_NAME, ctrl);
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(dev, "can't allocate IRQ %d: error %d\n",
			ctrl->irq, ret);
		जाओ err;
	पूर्ण

	क्रम_each_available_child_of_node(dn, child) अणु
		अगर (of_device_is_compatible(child, "brcm,nandcs")) अणु
			काष्ठा brcmnand_host *host;

			host = devm_kzalloc(dev, माप(*host), GFP_KERNEL);
			अगर (!host) अणु
				of_node_put(child);
				ret = -ENOMEM;
				जाओ err;
			पूर्ण
			host->pdev = pdev;
			host->ctrl = ctrl;

			ret = brcmnand_init_cs(host, child);
			अगर (ret) अणु
				devm_kमुक्त(dev, host);
				जारी; /* Try all chip-selects */
			पूर्ण

			list_add_tail(&host->node, &ctrl->host_list);
		पूर्ण
	पूर्ण

	/* No chip-selects could initialize properly */
	अगर (list_empty(&ctrl->host_list)) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	वापस 0;

err:
	clk_disable_unprepare(ctrl->clk);
	वापस ret;

पूर्ण
EXPORT_SYMBOL_GPL(brcmnand_probe);

पूर्णांक brcmnand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा brcmnand_controller *ctrl = dev_get_drvdata(&pdev->dev);
	काष्ठा brcmnand_host *host;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;

	list_क्रम_each_entry(host, &ctrl->host_list, node) अणु
		chip = &host->chip;
		ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
		WARN_ON(ret);
		nand_cleanup(chip);
	पूर्ण

	clk_disable_unprepare(ctrl->clk);

	dev_set_drvdata(&pdev->dev, शून्य);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(brcmnand_हटाओ);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Kevin Cernekee");
MODULE_AUTHOR("Brian Norris");
MODULE_DESCRIPTION("NAND driver for Broadcom chips");
MODULE_ALIAS("platform:brcmnand");
