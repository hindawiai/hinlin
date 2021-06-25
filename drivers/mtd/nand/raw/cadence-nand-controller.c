<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Cadence न_अंकD flash controller driver
 *
 * Copyright (C) 2019 Cadence
 *
 * Author: Piotr Sroka <piotrs@cadence.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/of_device.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/slab.h>

/*
 * HPNFC can work in 3 modes:
 * -  PIO - can work in master or slave DMA
 * -  CDMA - needs Master DMA क्रम accessing command descriptors.
 * -  Generic mode - can use only slave DMA.
 * CDMA and PIO modes can be used to execute only base commands.
 * Generic mode can be used to execute any command
 * on न_अंकD flash memory. Driver uses CDMA mode क्रम
 * block erasing, page पढ़ोing, page programing.
 * Generic mode is used क्रम executing rest of commands.
 */

#घोषणा MAX_ADDRESS_CYC		6
#घोषणा MAX_ERASE_ADDRESS_CYC	3
#घोषणा MAX_DATA_SIZE		0xFFFC
#घोषणा DMA_DATA_SIZE_ALIGN	8

/* Register definition. */
/*
 * Command रेजिस्टर 0.
 * Writing data to this रेजिस्टर will initiate a new transaction
 * of the NF controller.
 */
#घोषणा CMD_REG0			0x0000
/* Command type field mask. */
#घोषणा		CMD_REG0_CT		GENMASK(31, 30)
/* Command type CDMA. */
#घोषणा		CMD_REG0_CT_CDMA	0uL
/* Command type generic. */
#घोषणा		CMD_REG0_CT_GEN		3uL
/* Command thपढ़ो number field mask. */
#घोषणा		CMD_REG0_TN		GENMASK(27, 24)

/* Command रेजिस्टर 2. */
#घोषणा CMD_REG2			0x0008
/* Command रेजिस्टर 3. */
#घोषणा CMD_REG3			0x000C
/* Poपूर्णांकer रेजिस्टर to select which thपढ़ो status will be selected. */
#घोषणा CMD_STATUS_PTR			0x0010
/* Command status रेजिस्टर क्रम selected thपढ़ो. */
#घोषणा CMD_STATUS			0x0014

/* Interrupt status रेजिस्टर. */
#घोषणा INTR_STATUS			0x0110
#घोषणा		INTR_STATUS_SDMA_ERR	BIT(22)
#घोषणा		INTR_STATUS_SDMA_TRIGG	BIT(21)
#घोषणा		INTR_STATUS_UNSUPP_CMD	BIT(19)
#घोषणा		INTR_STATUS_DDMA_TERR	BIT(18)
#घोषणा		INTR_STATUS_CDMA_TERR	BIT(17)
#घोषणा		INTR_STATUS_CDMA_IDL	BIT(16)

/* Interrupt enable रेजिस्टर. */
#घोषणा INTR_ENABLE				0x0114
#घोषणा		INTR_ENABLE_INTR_EN		BIT(31)
#घोषणा		INTR_ENABLE_SDMA_ERR_EN		BIT(22)
#घोषणा		INTR_ENABLE_SDMA_TRIGG_EN	BIT(21)
#घोषणा		INTR_ENABLE_UNSUPP_CMD_EN	BIT(19)
#घोषणा		INTR_ENABLE_DDMA_TERR_EN	BIT(18)
#घोषणा		INTR_ENABLE_CDMA_TERR_EN	BIT(17)
#घोषणा		INTR_ENABLE_CDMA_IDLE_EN	BIT(16)

/* Controller पूर्णांकernal state. */
#घोषणा CTRL_STATUS				0x0118
#घोषणा		CTRL_STATUS_INIT_COMP		BIT(9)
#घोषणा		CTRL_STATUS_CTRL_BUSY		BIT(8)

/* Command Engine thपढ़ोs state. */
#घोषणा TRD_STATUS				0x0120

/* Command Engine पूर्णांकerrupt thपढ़ो error status. */
#घोषणा TRD_ERR_INT_STATUS			0x0128
/* Command Engine पूर्णांकerrupt thपढ़ो error enable. */
#घोषणा TRD_ERR_INT_STATUS_EN			0x0130
/* Command Engine पूर्णांकerrupt thपढ़ो complete status. */
#घोषणा TRD_COMP_INT_STATUS			0x0138

/*
 * Transfer config 0 रेजिस्टर.
 * Configures data transfer parameters.
 */
#घोषणा TRAN_CFG_0				0x0400
/* Offset value from the beginning of the page. */
#घोषणा		TRAN_CFG_0_OFFSET		GENMASK(31, 16)
/* Numbers of sectors to transfer within singlNF device's page. */
#घोषणा		TRAN_CFG_0_SEC_CNT		GENMASK(7, 0)

/*
 * Transfer config 1 रेजिस्टर.
 * Configures data transfer parameters.
 */
#घोषणा TRAN_CFG_1				0x0404
/* Size of last data sector. */
#घोषणा		TRAN_CFG_1_LAST_SEC_SIZE	GENMASK(31, 16)
/* Size of not-last data sector. */
#घोषणा		TRAN_CFG_1_SECTOR_SIZE		GENMASK(15, 0)

/* ECC engine configuration रेजिस्टर 0. */
#घोषणा ECC_CONFIG_0				0x0428
/* Correction strength. */
#घोषणा		ECC_CONFIG_0_CORR_STR		GENMASK(10, 8)
/* Enable erased pages detection mechanism. */
#घोषणा		ECC_CONFIG_0_ERASE_DET_EN	BIT(1)
/* Enable controller ECC check bits generation and correction. */
#घोषणा		ECC_CONFIG_0_ECC_EN		BIT(0)

/* ECC engine configuration रेजिस्टर 1. */
#घोषणा ECC_CONFIG_1				0x042C

/* Multiplane settings रेजिस्टर. */
#घोषणा MULTIPLANE_CFG				0x0434
/* Cache operation settings. */
#घोषणा CACHE_CFG				0x0438

/* DMA settings रेजिस्टर. */
#घोषणा DMA_SETINGS				0x043C
/* Enable SDMA error report on access unprepared slave DMA पूर्णांकerface. */
#घोषणा		DMA_SETINGS_SDMA_ERR_RSP	BIT(17)

/* Transferred data block size क्रम the slave DMA module. */
#घोषणा SDMA_SIZE				0x0440

/* Thपढ़ो number associated with transferred data block
 * क्रम the slave DMA module.
 */
#घोषणा SDMA_TRD_NUM				0x0444
/* Thपढ़ो number mask. */
#घोषणा		SDMA_TRD_NUM_SDMA_TRD		GENMASK(2, 0)

#घोषणा CONTROL_DATA_CTRL			0x0494
/* Thपढ़ो number mask. */
#घोषणा		CONTROL_DATA_CTRL_SIZE		GENMASK(15, 0)

#घोषणा CTRL_VERSION				0x800
#घोषणा		CTRL_VERSION_REV		GENMASK(7, 0)

/* Available hardware features of the controller. */
#घोषणा CTRL_FEATURES				0x804
/* Support क्रम NV-DDR2/3 work mode. */
#घोषणा		CTRL_FEATURES_NVDDR_2_3		BIT(28)
/* Support क्रम NV-DDR work mode. */
#घोषणा		CTRL_FEATURES_NVDDR		BIT(27)
/* Support क्रम asynchronous work mode. */
#घोषणा		CTRL_FEATURES_ASYNC		BIT(26)
/* Support क्रम asynchronous work mode. */
#घोषणा		CTRL_FEATURES_N_BANKS		GENMASK(25, 24)
/* Slave and Master DMA data width. */
#घोषणा		CTRL_FEATURES_DMA_DWITH64	BIT(21)
/* Availability of Control Data feature.*/
#घोषणा		CTRL_FEATURES_CONTROL_DATA	BIT(10)

/* BCH Engine identअगरication रेजिस्टर 0 - correction strengths. */
#घोषणा BCH_CFG_0				0x838
#घोषणा		BCH_CFG_0_CORR_CAP_0		GENMASK(7, 0)
#घोषणा		BCH_CFG_0_CORR_CAP_1		GENMASK(15, 8)
#घोषणा		BCH_CFG_0_CORR_CAP_2		GENMASK(23, 16)
#घोषणा		BCH_CFG_0_CORR_CAP_3		GENMASK(31, 24)

/* BCH Engine identअगरication रेजिस्टर 1 - correction strengths. */
#घोषणा BCH_CFG_1				0x83C
#घोषणा		BCH_CFG_1_CORR_CAP_4		GENMASK(7, 0)
#घोषणा		BCH_CFG_1_CORR_CAP_5		GENMASK(15, 8)
#घोषणा		BCH_CFG_1_CORR_CAP_6		GENMASK(23, 16)
#घोषणा		BCH_CFG_1_CORR_CAP_7		GENMASK(31, 24)

/* BCH Engine identअगरication रेजिस्टर 2 - sector sizes. */
#घोषणा BCH_CFG_2				0x840
#घोषणा		BCH_CFG_2_SECT_0		GENMASK(15, 0)
#घोषणा		BCH_CFG_2_SECT_1		GENMASK(31, 16)

/* BCH Engine identअगरication रेजिस्टर 3. */
#घोषणा BCH_CFG_3				0x844
#घोषणा		BCH_CFG_3_METADATA_SIZE		GENMASK(23, 16)

/* Ready/Busy# line status. */
#घोषणा RBN_SETINGS				0x1004

/* Common settings. */
#घोषणा COMMON_SET				0x1008
/* 16 bit device connected to the न_अंकD Flash पूर्णांकerface. */
#घोषणा		COMMON_SET_DEVICE_16BIT		BIT(8)

/* Skip_bytes रेजिस्टरs. */
#घोषणा SKIP_BYTES_CONF				0x100C
#घोषणा		SKIP_BYTES_MARKER_VALUE		GENMASK(31, 16)
#घोषणा		SKIP_BYTES_NUM_OF_BYTES		GENMASK(7, 0)

#घोषणा SKIP_BYTES_OFFSET			0x1010
#घोषणा		 SKIP_BYTES_OFFSET_VALUE	GENMASK(23, 0)

/* Timings configuration. */
#घोषणा ASYNC_TOGGLE_TIMINGS			0x101c
#घोषणा		ASYNC_TOGGLE_TIMINGS_TRH	GENMASK(28, 24)
#घोषणा		ASYNC_TOGGLE_TIMINGS_TRP	GENMASK(20, 16)
#घोषणा		ASYNC_TOGGLE_TIMINGS_TWH	GENMASK(12, 8)
#घोषणा		ASYNC_TOGGLE_TIMINGS_TWP	GENMASK(4, 0)

#घोषणा	TIMINGS0				0x1024
#घोषणा		TIMINGS0_TADL			GENMASK(31, 24)
#घोषणा		TIMINGS0_TCCS			GENMASK(23, 16)
#घोषणा		TIMINGS0_TWHR			GENMASK(15, 8)
#घोषणा		TIMINGS0_TRHW			GENMASK(7, 0)

#घोषणा	TIMINGS1				0x1028
#घोषणा		TIMINGS1_TRHZ			GENMASK(31, 24)
#घोषणा		TIMINGS1_TWB			GENMASK(23, 16)
#घोषणा		TIMINGS1_TVDLY			GENMASK(7, 0)

#घोषणा	TIMINGS2				0x102c
#घोषणा		TIMINGS2_TFEAT			GENMASK(25, 16)
#घोषणा		TIMINGS2_CS_HOLD_TIME		GENMASK(13, 8)
#घोषणा		TIMINGS2_CS_SETUP_TIME		GENMASK(5, 0)

/* Configuration of the resynchronization of slave DLL of PHY. */
#घोषणा DLL_PHY_CTRL				0x1034
#घोषणा		DLL_PHY_CTRL_DLL_RST_N		BIT(24)
#घोषणा		DLL_PHY_CTRL_EXTENDED_WR_MODE	BIT(17)
#घोषणा		DLL_PHY_CTRL_EXTENDED_RD_MODE	BIT(16)
#घोषणा		DLL_PHY_CTRL_RS_HIGH_WAIT_CNT	GENMASK(11, 8)
#घोषणा		DLL_PHY_CTRL_RS_IDLE_CNT	GENMASK(7, 0)

/* Register controlling DQ related timing. */
#घोषणा PHY_DQ_TIMING				0x2000
/* Register controlling DSQ related timing.  */
#घोषणा PHY_DQS_TIMING				0x2004
#घोषणा		PHY_DQS_TIMING_DQS_SEL_OE_END	GENMASK(3, 0)
#घोषणा		PHY_DQS_TIMING_PHONY_DQS_SEL	BIT(16)
#घोषणा		PHY_DQS_TIMING_USE_PHONY_DQS	BIT(20)

/* Register controlling the gate and loopback control related timing. */
#घोषणा PHY_GATE_LPBK_CTRL			0x2008
#घोषणा		PHY_GATE_LPBK_CTRL_RDS		GENMASK(24, 19)

/* Register holds the control क्रम the master DLL logic. */
#घोषणा PHY_DLL_MASTER_CTRL			0x200C
#घोषणा		PHY_DLL_MASTER_CTRL_BYPASS_MODE	BIT(23)

/* Register holds the control क्रम the slave DLL logic. */
#घोषणा PHY_DLL_SLAVE_CTRL			0x2010

/* This रेजिस्टर handles the global control settings क्रम the PHY. */
#घोषणा PHY_CTRL				0x2080
#घोषणा		PHY_CTRL_SDR_DQS		BIT(14)
#घोषणा		PHY_CTRL_PHONY_DQS		GENMASK(9, 4)

/*
 * This रेजिस्टर handles the global control settings
 * क्रम the termination selects क्रम पढ़ोs.
 */
#घोषणा PHY_TSEL				0x2084

/* Generic command layout. */
#घोषणा GCMD_LAY_CS			GENMASK_ULL(11, 8)
/*
 * This bit inक्रमms the minicotroller अगर it has to रुको क्रम tWB
 * after sending the last CMD/ADDR/DATA in the sequence.
 */
#घोषणा GCMD_LAY_TWB			BIT_ULL(6)
/* Type of generic inकाष्ठाion. */
#घोषणा GCMD_LAY_INSTR			GENMASK_ULL(5, 0)

/* Generic CMD sequence type. */
#घोषणा		GCMD_LAY_INSTR_CMD	0
/* Generic ADDR sequence type. */
#घोषणा		GCMD_LAY_INSTR_ADDR	1
/* Generic data transfer sequence type. */
#घोषणा		GCMD_LAY_INSTR_DATA	2

/* Input part of generic command type of input is command. */
#घोषणा GCMD_LAY_INPUT_CMD		GENMASK_ULL(23, 16)

/* Generic command address sequence - address fields. */
#घोषणा GCMD_LAY_INPUT_ADDR		GENMASK_ULL(63, 16)
/* Generic command address sequence - address size. */
#घोषणा GCMD_LAY_INPUT_ADDR_SIZE	GENMASK_ULL(13, 11)

/* Transfer direction field of generic command data sequence. */
#घोषणा GCMD_सूची			BIT_ULL(11)
/* Read transfer direction of generic command data sequence. */
#घोषणा		GCMD_सूची_READ		0
/* Write transfer direction of generic command data sequence. */
#घोषणा		GCMD_सूची_WRITE		1

/* ECC enabled flag of generic command data sequence - ECC enabled. */
#घोषणा GCMD_ECC_EN			BIT_ULL(12)
/* Generic command data sequence - sector size. */
#घोषणा GCMD_SECT_SIZE			GENMASK_ULL(31, 16)
/* Generic command data sequence - sector count. */
#घोषणा GCMD_SECT_CNT			GENMASK_ULL(39, 32)
/* Generic command data sequence - last sector size. */
#घोषणा GCMD_LAST_SIZE			GENMASK_ULL(55, 40)

/* CDMA descriptor fields. */
/* Erase command type of CDMA descriptor. */
#घोषणा CDMA_CT_ERASE		0x1000
/* Program page command type of CDMA descriptor. */
#घोषणा CDMA_CT_WR		0x2100
/* Read page command type of CDMA descriptor. */
#घोषणा CDMA_CT_RD		0x2200

/* Flash poपूर्णांकer memory shअगरt. */
#घोषणा CDMA_CFPTR_MEM_SHIFT	24
/* Flash poपूर्णांकer memory mask. */
#घोषणा CDMA_CFPTR_MEM		GENMASK(26, 24)

/*
 * Command DMA descriptor flags. If set causes issue पूर्णांकerrupt after
 * the completion of descriptor processing.
 */
#घोषणा CDMA_CF_INT		BIT(8)
/*
 * Command DMA descriptor flags - the next descriptor
 * address field is valid and descriptor processing should जारी.
 */
#घोषणा CDMA_CF_CONT		BIT(9)
/* DMA master flag of command DMA descriptor. */
#घोषणा CDMA_CF_DMA_MASTER	BIT(10)

/* Operation complete status of command descriptor. */
#घोषणा CDMA_CS_COMP		BIT(15)
/* Operation complete status of command descriptor. */
/* Command descriptor status - operation fail. */
#घोषणा CDMA_CS_FAIL		BIT(14)
/* Command descriptor status - page erased. */
#घोषणा CDMA_CS_ERP		BIT(11)
/* Command descriptor status - समयout occurred. */
#घोषणा CDMA_CS_TOUT		BIT(10)
/*
 * Maximum amount of correction applied to one ECC sector.
 * It is part of command descriptor status.
 */
#घोषणा CDMA_CS_MAXERR		GENMASK(9, 2)
/* Command descriptor status - uncorrectable ECC error. */
#घोषणा CDMA_CS_UNCE		BIT(1)
/* Command descriptor status - descriptor error. */
#घोषणा CDMA_CS_ERR		BIT(0)

/* Status of operation - OK. */
#घोषणा STAT_OK			0
/* Status of operation - FAIL. */
#घोषणा STAT_FAIL		2
/* Status of operation - uncorrectable ECC error. */
#घोषणा STAT_ECC_UNCORR		3
/* Status of operation - page erased. */
#घोषणा STAT_ERASED		5
/* Status of operation - correctable ECC error. */
#घोषणा STAT_ECC_CORR		6
/* Status of operation - unsuspected state. */
#घोषणा STAT_UNKNOWN		7
/* Status of operation - operation is not completed yet. */
#घोषणा STAT_BUSY		0xFF

#घोषणा BCH_MAX_NUM_CORR_CAPS		8
#घोषणा BCH_MAX_NUM_SECTOR_SIZES	2

काष्ठा cadence_nand_timings अणु
	u32 async_toggle_timings;
	u32 timings0;
	u32 timings1;
	u32 timings2;
	u32 dll_phy_ctrl;
	u32 phy_ctrl;
	u32 phy_dqs_timing;
	u32 phy_gate_lpbk_ctrl;
पूर्ण;

/* Command DMA descriptor. */
काष्ठा cadence_nand_cdma_desc अणु
	/* Next descriptor address. */
	u64 next_poपूर्णांकer;

	/* Flash address is a 32-bit address comprising of BANK and ROW ADDR. */
	u32 flash_poपूर्णांकer;
	/*field appears in HPNFC version 13*/
	u16 bank;
	u16 rsvd0;

	/* Operation the controller needs to perक्रमm. */
	u16 command_type;
	u16 rsvd1;
	/* Flags क्रम operation of this command. */
	u16 command_flags;
	u16 rsvd2;

	/* System/host memory address required क्रम data DMA commands. */
	u64 memory_poपूर्णांकer;

	/* Status of operation. */
	u32 status;
	u32 rsvd3;

	/* Address poपूर्णांकer to sync buffer location. */
	u64 sync_flag_poपूर्णांकer;

	/* Controls the buffer sync mechanism. */
	u32 sync_arguments;
	u32 rsvd4;

	/* Control data poपूर्णांकer. */
	u64 ctrl_data_ptr;
पूर्ण;

/* Interrupt status. */
काष्ठा cadence_nand_irq_status अणु
	/* Thपढ़ो operation complete status. */
	u32 trd_status;
	/* Thपढ़ो operation error. */
	u32 trd_error;
	/* Controller status. */
	u32 status;
पूर्ण;

/* Cadence न_अंकD flash controller capabilities get from driver data. */
काष्ठा cadence_nand_dt_devdata अणु
	/* Skew value of the output संकेतs of the न_अंकD Flash पूर्णांकerface. */
	u32 अगर_skew;
	/* It inक्रमms अगर slave DMA पूर्णांकerface is connected to DMA engine. */
	अचिन्हित पूर्णांक has_dma:1;
पूर्ण;

/* Cadence न_अंकD flash controller capabilities पढ़ो from रेजिस्टरs. */
काष्ठा cdns_nand_caps अणु
	/* Maximum number of banks supported by hardware. */
	u8 max_banks;
	/* Slave and Master DMA data width in bytes (4 or 8). */
	u8 data_dma_width;
	/* Control Data feature supported. */
	bool data_control_supp;
	/* Is PHY type DLL. */
	bool is_phy_type_dll;
पूर्ण;

काष्ठा cdns_nand_ctrl अणु
	काष्ठा device *dev;
	काष्ठा nand_controller controller;
	काष्ठा cadence_nand_cdma_desc *cdma_desc;
	/* IP capability. */
	स्थिर काष्ठा cadence_nand_dt_devdata *caps1;
	काष्ठा cdns_nand_caps caps2;
	u8 ctrl_rev;
	dma_addr_t dma_cdma_desc;
	u8 *buf;
	u32 buf_size;
	u8 curr_corr_str_idx;

	/* Register पूर्णांकerface. */
	व्योम __iomem *reg;

	काष्ठा अणु
		व्योम __iomem *virt;
		dma_addr_t dma;
	पूर्ण io;

	पूर्णांक irq;
	/* Interrupts that have happened. */
	काष्ठा cadence_nand_irq_status irq_status;
	/* Interrupts we are रुकोing क्रम. */
	काष्ठा cadence_nand_irq_status irq_mask;
	काष्ठा completion complete;
	/* Protect irq_mask and irq_status. */
	spinlock_t irq_lock;

	पूर्णांक ecc_strengths[BCH_MAX_NUM_CORR_CAPS];
	काष्ठा nand_ecc_step_info ecc_stepinfos[BCH_MAX_NUM_SECTOR_SIZES];
	काष्ठा nand_ecc_caps ecc_caps;

	पूर्णांक curr_trans_type;

	काष्ठा dma_chan *dmac;

	u32 nf_clk_rate;
	/*
	 * Estimated Board delay. The value includes the total
	 * round trip delay क्रम the संकेतs and is used क्रम deciding on values
	 * associated with data पढ़ो capture.
	 */
	u32 board_delay;

	काष्ठा nand_chip *selected_chip;

	अचिन्हित दीर्घ asचिन्हित_cs;
	काष्ठा list_head chips;
	u8 bch_metadata_size;
पूर्ण;

काष्ठा cdns_nand_chip अणु
	काष्ठा cadence_nand_timings timings;
	काष्ठा nand_chip chip;
	u8 nsels;
	काष्ठा list_head node;

	/*
	 * part of oob area of न_अंकD flash memory page.
	 * This part is available क्रम user to पढ़ो or ग_लिखो.
	 */
	u32 avail_oob_size;

	/* Sector size. There are few sectors per mtd->ग_लिखोsize */
	u32 sector_size;
	u32 sector_count;

	/* Offset of BBM. */
	u8 bbm_offs;
	/* Number of bytes reserved क्रम BBM. */
	u8 bbm_len;
	/* ECC strength index. */
	u8 corr_str_idx;

	u8 cs[];
पूर्ण;

काष्ठा ecc_info अणु
	पूर्णांक (*calc_ecc_bytes)(पूर्णांक step_size, पूर्णांक strength);
	पूर्णांक max_step_size;
पूर्ण;

अटल अंतरभूत काष्ठा
cdns_nand_chip *to_cdns_nand_chip(काष्ठा nand_chip *chip)
अणु
	वापस container_of(chip, काष्ठा cdns_nand_chip, chip);
पूर्ण

अटल अंतरभूत काष्ठा
cdns_nand_ctrl *to_cdns_nand_ctrl(काष्ठा nand_controller *controller)
अणु
	वापस container_of(controller, काष्ठा cdns_nand_ctrl, controller);
पूर्ण

अटल bool
cadence_nand_dma_buf_ok(काष्ठा cdns_nand_ctrl *cdns_ctrl, स्थिर व्योम *buf,
			u32 buf_len)
अणु
	u8 data_dma_width = cdns_ctrl->caps2.data_dma_width;

	वापस buf && virt_addr_valid(buf) &&
		likely(IS_ALIGNED((uपूर्णांकptr_t)buf, data_dma_width)) &&
		likely(IS_ALIGNED(buf_len, DMA_DATA_SIZE_ALIGN));
पूर्ण

अटल पूर्णांक cadence_nand_रुको_क्रम_value(काष्ठा cdns_nand_ctrl *cdns_ctrl,
				       u32 reg_offset, u32 समयout_us,
				       u32 mask, bool is_clear)
अणु
	u32 val;
	पूर्णांक ret;

	ret = पढ़ोl_relaxed_poll_समयout(cdns_ctrl->reg + reg_offset,
					 val, !(val & mask) == is_clear,
					 10, समयout_us);

	अगर (ret < 0) अणु
		dev_err(cdns_ctrl->dev,
			"Timeout while waiting for reg %x with mask %x is clear %d\n",
			reg_offset, mask, is_clear);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cadence_nand_set_ecc_enable(काष्ठा cdns_nand_ctrl *cdns_ctrl,
				       bool enable)
अणु
	u32 reg;

	अगर (cadence_nand_रुको_क्रम_value(cdns_ctrl, CTRL_STATUS,
					1000000,
					CTRL_STATUS_CTRL_BUSY, true))
		वापस -ETIMEDOUT;

	reg = पढ़ोl_relaxed(cdns_ctrl->reg + ECC_CONFIG_0);

	अगर (enable)
		reg |= ECC_CONFIG_0_ECC_EN;
	अन्यथा
		reg &= ~ECC_CONFIG_0_ECC_EN;

	ग_लिखोl_relaxed(reg, cdns_ctrl->reg + ECC_CONFIG_0);

	वापस 0;
पूर्ण

अटल व्योम cadence_nand_set_ecc_strength(काष्ठा cdns_nand_ctrl *cdns_ctrl,
					  u8 corr_str_idx)
अणु
	u32 reg;

	अगर (cdns_ctrl->curr_corr_str_idx == corr_str_idx)
		वापस;

	reg = पढ़ोl_relaxed(cdns_ctrl->reg + ECC_CONFIG_0);
	reg &= ~ECC_CONFIG_0_CORR_STR;
	reg |= FIELD_PREP(ECC_CONFIG_0_CORR_STR, corr_str_idx);
	ग_लिखोl_relaxed(reg, cdns_ctrl->reg + ECC_CONFIG_0);

	cdns_ctrl->curr_corr_str_idx = corr_str_idx;
पूर्ण

अटल पूर्णांक cadence_nand_get_ecc_strength_idx(काष्ठा cdns_nand_ctrl *cdns_ctrl,
					     u8 strength)
अणु
	पूर्णांक i, corr_str_idx = -1;

	क्रम (i = 0; i < BCH_MAX_NUM_CORR_CAPS; i++) अणु
		अगर (cdns_ctrl->ecc_strengths[i] == strength) अणु
			corr_str_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस corr_str_idx;
पूर्ण

अटल पूर्णांक cadence_nand_set_skip_marker_val(काष्ठा cdns_nand_ctrl *cdns_ctrl,
					    u16 marker_value)
अणु
	u32 reg;

	अगर (cadence_nand_रुको_क्रम_value(cdns_ctrl, CTRL_STATUS,
					1000000,
					CTRL_STATUS_CTRL_BUSY, true))
		वापस -ETIMEDOUT;

	reg = पढ़ोl_relaxed(cdns_ctrl->reg + SKIP_BYTES_CONF);
	reg &= ~SKIP_BYTES_MARKER_VALUE;
	reg |= FIELD_PREP(SKIP_BYTES_MARKER_VALUE,
			  marker_value);

	ग_लिखोl_relaxed(reg, cdns_ctrl->reg + SKIP_BYTES_CONF);

	वापस 0;
पूर्ण

अटल पूर्णांक cadence_nand_set_skip_bytes_conf(काष्ठा cdns_nand_ctrl *cdns_ctrl,
					    u8 num_of_bytes,
					    u32 offset_value,
					    पूर्णांक enable)
अणु
	u32 reg, skip_bytes_offset;

	अगर (cadence_nand_रुको_क्रम_value(cdns_ctrl, CTRL_STATUS,
					1000000,
					CTRL_STATUS_CTRL_BUSY, true))
		वापस -ETIMEDOUT;

	अगर (!enable) अणु
		num_of_bytes = 0;
		offset_value = 0;
	पूर्ण

	reg = पढ़ोl_relaxed(cdns_ctrl->reg + SKIP_BYTES_CONF);
	reg &= ~SKIP_BYTES_NUM_OF_BYTES;
	reg |= FIELD_PREP(SKIP_BYTES_NUM_OF_BYTES,
			  num_of_bytes);
	skip_bytes_offset = FIELD_PREP(SKIP_BYTES_OFFSET_VALUE,
				       offset_value);

	ग_लिखोl_relaxed(reg, cdns_ctrl->reg + SKIP_BYTES_CONF);
	ग_लिखोl_relaxed(skip_bytes_offset, cdns_ctrl->reg + SKIP_BYTES_OFFSET);

	वापस 0;
पूर्ण

/* Functions enables/disables hardware detection of erased data */
अटल व्योम cadence_nand_set_erase_detection(काष्ठा cdns_nand_ctrl *cdns_ctrl,
					     bool enable,
					     u8 bitflips_threshold)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(cdns_ctrl->reg + ECC_CONFIG_0);

	अगर (enable)
		reg |= ECC_CONFIG_0_ERASE_DET_EN;
	अन्यथा
		reg &= ~ECC_CONFIG_0_ERASE_DET_EN;

	ग_लिखोl_relaxed(reg, cdns_ctrl->reg + ECC_CONFIG_0);
	ग_लिखोl_relaxed(bitflips_threshold, cdns_ctrl->reg + ECC_CONFIG_1);
पूर्ण

अटल पूर्णांक cadence_nand_set_access_width16(काष्ठा cdns_nand_ctrl *cdns_ctrl,
					   bool bit_bus16)
अणु
	u32 reg;

	अगर (cadence_nand_रुको_क्रम_value(cdns_ctrl, CTRL_STATUS,
					1000000,
					CTRL_STATUS_CTRL_BUSY, true))
		वापस -ETIMEDOUT;

	reg = पढ़ोl_relaxed(cdns_ctrl->reg + COMMON_SET);

	अगर (!bit_bus16)
		reg &= ~COMMON_SET_DEVICE_16BIT;
	अन्यथा
		reg |= COMMON_SET_DEVICE_16BIT;
	ग_लिखोl_relaxed(reg, cdns_ctrl->reg + COMMON_SET);

	वापस 0;
पूर्ण

अटल व्योम
cadence_nand_clear_पूर्णांकerrupt(काष्ठा cdns_nand_ctrl *cdns_ctrl,
			     काष्ठा cadence_nand_irq_status *irq_status)
अणु
	ग_लिखोl_relaxed(irq_status->status, cdns_ctrl->reg + INTR_STATUS);
	ग_लिखोl_relaxed(irq_status->trd_status,
		       cdns_ctrl->reg + TRD_COMP_INT_STATUS);
	ग_लिखोl_relaxed(irq_status->trd_error,
		       cdns_ctrl->reg + TRD_ERR_INT_STATUS);
पूर्ण

अटल व्योम
cadence_nand_पढ़ो_पूर्णांक_status(काष्ठा cdns_nand_ctrl *cdns_ctrl,
			     काष्ठा cadence_nand_irq_status *irq_status)
अणु
	irq_status->status = पढ़ोl_relaxed(cdns_ctrl->reg + INTR_STATUS);
	irq_status->trd_status = पढ़ोl_relaxed(cdns_ctrl->reg
					       + TRD_COMP_INT_STATUS);
	irq_status->trd_error = पढ़ोl_relaxed(cdns_ctrl->reg
					      + TRD_ERR_INT_STATUS);
पूर्ण

अटल u32 irq_detected(काष्ठा cdns_nand_ctrl *cdns_ctrl,
			काष्ठा cadence_nand_irq_status *irq_status)
अणु
	cadence_nand_पढ़ो_पूर्णांक_status(cdns_ctrl, irq_status);

	वापस irq_status->status || irq_status->trd_status ||
		irq_status->trd_error;
पूर्ण

अटल व्योम cadence_nand_reset_irq(काष्ठा cdns_nand_ctrl *cdns_ctrl)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cdns_ctrl->irq_lock, flags);
	स_रखो(&cdns_ctrl->irq_status, 0, माप(cdns_ctrl->irq_status));
	स_रखो(&cdns_ctrl->irq_mask, 0, माप(cdns_ctrl->irq_mask));
	spin_unlock_irqrestore(&cdns_ctrl->irq_lock, flags);
पूर्ण

/*
 * This is the पूर्णांकerrupt service routine. It handles all पूर्णांकerrupts
 * sent to this device.
 */
अटल irqवापस_t cadence_nand_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = dev_id;
	काष्ठा cadence_nand_irq_status irq_status;
	irqवापस_t result = IRQ_NONE;

	spin_lock(&cdns_ctrl->irq_lock);

	अगर (irq_detected(cdns_ctrl, &irq_status)) अणु
		/* Handle पूर्णांकerrupt. */
		/* First acknowledge it. */
		cadence_nand_clear_पूर्णांकerrupt(cdns_ctrl, &irq_status);
		/* Status in the device context क्रम someone to पढ़ो. */
		cdns_ctrl->irq_status.status |= irq_status.status;
		cdns_ctrl->irq_status.trd_status |= irq_status.trd_status;
		cdns_ctrl->irq_status.trd_error |= irq_status.trd_error;
		/* Notअगरy anyone who cares that it happened. */
		complete(&cdns_ctrl->complete);
		/* Tell the OS that we've handled this. */
		result = IRQ_HANDLED;
	पूर्ण
	spin_unlock(&cdns_ctrl->irq_lock);

	वापस result;
पूर्ण

अटल व्योम cadence_nand_set_irq_mask(काष्ठा cdns_nand_ctrl *cdns_ctrl,
				      काष्ठा cadence_nand_irq_status *irq_mask)
अणु
	ग_लिखोl_relaxed(INTR_ENABLE_INTR_EN | irq_mask->status,
		       cdns_ctrl->reg + INTR_ENABLE);

	ग_लिखोl_relaxed(irq_mask->trd_error,
		       cdns_ctrl->reg + TRD_ERR_INT_STATUS_EN);
पूर्ण

अटल व्योम
cadence_nand_रुको_क्रम_irq(काष्ठा cdns_nand_ctrl *cdns_ctrl,
			  काष्ठा cadence_nand_irq_status *irq_mask,
			  काष्ठा cadence_nand_irq_status *irq_status)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(10000);
	अचिन्हित दीर्घ समय_left;

	समय_left = रुको_क्रम_completion_समयout(&cdns_ctrl->complete,
						समयout);

	*irq_status = cdns_ctrl->irq_status;
	अगर (समय_left == 0) अणु
		/* Timeout error. */
		dev_err(cdns_ctrl->dev, "timeout occurred:\n");
		dev_err(cdns_ctrl->dev, "\tstatus = 0x%x, mask = 0x%x\n",
			irq_status->status, irq_mask->status);
		dev_err(cdns_ctrl->dev,
			"\ttrd_status = 0x%x, trd_status mask = 0x%x\n",
			irq_status->trd_status, irq_mask->trd_status);
		dev_err(cdns_ctrl->dev,
			"\t trd_error = 0x%x, trd_error mask = 0x%x\n",
			irq_status->trd_error, irq_mask->trd_error);
	पूर्ण
पूर्ण

/* Execute generic command on न_अंकD controller. */
अटल पूर्णांक cadence_nand_generic_cmd_send(काष्ठा cdns_nand_ctrl *cdns_ctrl,
					 u8 chip_nr,
					 u64 mini_ctrl_cmd)
अणु
	u32 mini_ctrl_cmd_l, mini_ctrl_cmd_h, reg;

	mini_ctrl_cmd |= FIELD_PREP(GCMD_LAY_CS, chip_nr);
	mini_ctrl_cmd_l = mini_ctrl_cmd & 0xFFFFFFFF;
	mini_ctrl_cmd_h = mini_ctrl_cmd >> 32;

	अगर (cadence_nand_रुको_क्रम_value(cdns_ctrl, CTRL_STATUS,
					1000000,
					CTRL_STATUS_CTRL_BUSY, true))
		वापस -ETIMEDOUT;

	cadence_nand_reset_irq(cdns_ctrl);

	ग_लिखोl_relaxed(mini_ctrl_cmd_l, cdns_ctrl->reg + CMD_REG2);
	ग_लिखोl_relaxed(mini_ctrl_cmd_h, cdns_ctrl->reg + CMD_REG3);

	/* Select generic command. */
	reg = FIELD_PREP(CMD_REG0_CT, CMD_REG0_CT_GEN);
	/* Thपढ़ो number. */
	reg |= FIELD_PREP(CMD_REG0_TN, 0);

	/* Issue command. */
	ग_लिखोl_relaxed(reg, cdns_ctrl->reg + CMD_REG0);

	वापस 0;
पूर्ण

/* Wait क्रम data on slave DMA पूर्णांकerface. */
अटल पूर्णांक cadence_nand_रुको_on_sdma(काष्ठा cdns_nand_ctrl *cdns_ctrl,
				     u8 *out_sdma_trd,
				     u32 *out_sdma_size)
अणु
	काष्ठा cadence_nand_irq_status irq_mask, irq_status;

	irq_mask.trd_status = 0;
	irq_mask.trd_error = 0;
	irq_mask.status = INTR_STATUS_SDMA_TRIGG
		| INTR_STATUS_SDMA_ERR
		| INTR_STATUS_UNSUPP_CMD;

	cadence_nand_set_irq_mask(cdns_ctrl, &irq_mask);
	cadence_nand_रुको_क्रम_irq(cdns_ctrl, &irq_mask, &irq_status);
	अगर (irq_status.status == 0) अणु
		dev_err(cdns_ctrl->dev, "Timeout while waiting for SDMA\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (irq_status.status & INTR_STATUS_SDMA_TRIGG) अणु
		*out_sdma_size = पढ़ोl_relaxed(cdns_ctrl->reg + SDMA_SIZE);
		*out_sdma_trd  = पढ़ोl_relaxed(cdns_ctrl->reg + SDMA_TRD_NUM);
		*out_sdma_trd =
			FIELD_GET(SDMA_TRD_NUM_SDMA_TRD, *out_sdma_trd);
	पूर्ण अन्यथा अणु
		dev_err(cdns_ctrl->dev, "SDMA error - irq_status %x\n",
			irq_status.status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cadence_nand_get_caps(काष्ठा cdns_nand_ctrl *cdns_ctrl)
अणु
	u32  reg;

	reg = पढ़ोl_relaxed(cdns_ctrl->reg + CTRL_FEATURES);

	cdns_ctrl->caps2.max_banks = 1 << FIELD_GET(CTRL_FEATURES_N_BANKS, reg);

	अगर (FIELD_GET(CTRL_FEATURES_DMA_DWITH64, reg))
		cdns_ctrl->caps2.data_dma_width = 8;
	अन्यथा
		cdns_ctrl->caps2.data_dma_width = 4;

	अगर (reg & CTRL_FEATURES_CONTROL_DATA)
		cdns_ctrl->caps2.data_control_supp = true;

	अगर (reg & (CTRL_FEATURES_NVDDR_2_3
		   | CTRL_FEATURES_NVDDR))
		cdns_ctrl->caps2.is_phy_type_dll = true;
पूर्ण

/* Prepare CDMA descriptor. */
अटल व्योम
cadence_nand_cdma_desc_prepare(काष्ठा cdns_nand_ctrl *cdns_ctrl,
			       अक्षर nf_mem, u32 flash_ptr, dma_addr_t mem_ptr,
				   dma_addr_t ctrl_data_ptr, u16 ctype)
अणु
	काष्ठा cadence_nand_cdma_desc *cdma_desc = cdns_ctrl->cdma_desc;

	स_रखो(cdma_desc, 0, माप(काष्ठा cadence_nand_cdma_desc));

	/* Set fields क्रम one descriptor. */
	cdma_desc->flash_poपूर्णांकer = flash_ptr;
	अगर (cdns_ctrl->ctrl_rev >= 13)
		cdma_desc->bank = nf_mem;
	अन्यथा
		cdma_desc->flash_poपूर्णांकer |= (nf_mem << CDMA_CFPTR_MEM_SHIFT);

	cdma_desc->command_flags |= CDMA_CF_DMA_MASTER;
	cdma_desc->command_flags  |= CDMA_CF_INT;

	cdma_desc->memory_poपूर्णांकer = mem_ptr;
	cdma_desc->status = 0;
	cdma_desc->sync_flag_poपूर्णांकer = 0;
	cdma_desc->sync_arguments = 0;

	cdma_desc->command_type = ctype;
	cdma_desc->ctrl_data_ptr = ctrl_data_ptr;
पूर्ण

अटल u8 cadence_nand_check_desc_error(काष्ठा cdns_nand_ctrl *cdns_ctrl,
					u32 desc_status)
अणु
	अगर (desc_status & CDMA_CS_ERP)
		वापस STAT_ERASED;

	अगर (desc_status & CDMA_CS_UNCE)
		वापस STAT_ECC_UNCORR;

	अगर (desc_status & CDMA_CS_ERR) अणु
		dev_err(cdns_ctrl->dev, ":CDMA desc error flag detected.\n");
		वापस STAT_FAIL;
	पूर्ण

	अगर (FIELD_GET(CDMA_CS_MAXERR, desc_status))
		वापस STAT_ECC_CORR;

	वापस STAT_FAIL;
पूर्ण

अटल पूर्णांक cadence_nand_cdma_finish(काष्ठा cdns_nand_ctrl *cdns_ctrl)
अणु
	काष्ठा cadence_nand_cdma_desc *desc_ptr = cdns_ctrl->cdma_desc;
	u8 status = STAT_BUSY;

	अगर (desc_ptr->status & CDMA_CS_FAIL) अणु
		status = cadence_nand_check_desc_error(cdns_ctrl,
						       desc_ptr->status);
		dev_err(cdns_ctrl->dev, ":CDMA error %x\n", desc_ptr->status);
	पूर्ण अन्यथा अगर (desc_ptr->status & CDMA_CS_COMP) अणु
		/* Descriptor finished with no errors. */
		अगर (desc_ptr->command_flags & CDMA_CF_CONT) अणु
			dev_info(cdns_ctrl->dev, "DMA unsupported flag is set");
			status = STAT_UNKNOWN;
		पूर्ण अन्यथा अणु
			/* Last descriptor.  */
			status = STAT_OK;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक cadence_nand_cdma_send(काष्ठा cdns_nand_ctrl *cdns_ctrl,
				  u8 thपढ़ो)
अणु
	u32 reg;
	पूर्णांक status;

	/* Wait क्रम thपढ़ो पढ़ोy. */
	status = cadence_nand_रुको_क्रम_value(cdns_ctrl, TRD_STATUS,
					     1000000,
					     BIT(thपढ़ो), true);
	अगर (status)
		वापस status;

	cadence_nand_reset_irq(cdns_ctrl);
	reinit_completion(&cdns_ctrl->complete);

	ग_लिखोl_relaxed((u32)cdns_ctrl->dma_cdma_desc,
		       cdns_ctrl->reg + CMD_REG2);
	ग_लिखोl_relaxed(0, cdns_ctrl->reg + CMD_REG3);

	/* Select CDMA mode. */
	reg = FIELD_PREP(CMD_REG0_CT, CMD_REG0_CT_CDMA);
	/* Thपढ़ो number. */
	reg |= FIELD_PREP(CMD_REG0_TN, thपढ़ो);
	/* Issue command. */
	ग_लिखोl_relaxed(reg, cdns_ctrl->reg + CMD_REG0);

	वापस 0;
पूर्ण

/* Send SDMA command and रुको क्रम finish. */
अटल u32
cadence_nand_cdma_send_and_रुको(काष्ठा cdns_nand_ctrl *cdns_ctrl,
				u8 thपढ़ो)
अणु
	काष्ठा cadence_nand_irq_status irq_mask, irq_status = अणु0पूर्ण;
	पूर्णांक status;

	irq_mask.trd_status = BIT(thपढ़ो);
	irq_mask.trd_error = BIT(thपढ़ो);
	irq_mask.status = INTR_STATUS_CDMA_TERR;

	cadence_nand_set_irq_mask(cdns_ctrl, &irq_mask);

	status = cadence_nand_cdma_send(cdns_ctrl, thपढ़ो);
	अगर (status)
		वापस status;

	cadence_nand_रुको_क्रम_irq(cdns_ctrl, &irq_mask, &irq_status);

	अगर (irq_status.status == 0 && irq_status.trd_status == 0 &&
	    irq_status.trd_error == 0) अणु
		dev_err(cdns_ctrl->dev, "CDMA command timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (irq_status.status & irq_mask.status) अणु
		dev_err(cdns_ctrl->dev, "CDMA command failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ECC size depends on configured ECC strength and on maximum supported
 * ECC step size.
 */
अटल पूर्णांक cadence_nand_calc_ecc_bytes(पूर्णांक max_step_size, पूर्णांक strength)
अणु
	पूर्णांक nbytes = DIV_ROUND_UP(fls(8 * max_step_size) * strength, 8);

	वापस ALIGN(nbytes, 2);
पूर्ण

#घोषणा CADENCE_न_अंकD_CALC_ECC_BYTES(max_step_size) \
	अटल पूर्णांक \
	cadence_nand_calc_ecc_bytes_##max_step_size(पूर्णांक step_size, \
						    पूर्णांक strength)\
	अणु\
		वापस cadence_nand_calc_ecc_bytes(max_step_size, strength);\
	पूर्ण

CADENCE_न_अंकD_CALC_ECC_BYTES(256)
CADENCE_न_अंकD_CALC_ECC_BYTES(512)
CADENCE_न_अंकD_CALC_ECC_BYTES(1024)
CADENCE_न_अंकD_CALC_ECC_BYTES(2048)
CADENCE_न_अंकD_CALC_ECC_BYTES(4096)

/* Function पढ़ोs BCH capabilities. */
अटल पूर्णांक cadence_nand_पढ़ो_bch_caps(काष्ठा cdns_nand_ctrl *cdns_ctrl)
अणु
	काष्ठा nand_ecc_caps *ecc_caps = &cdns_ctrl->ecc_caps;
	पूर्णांक max_step_size = 0, nstrengths, i;
	u32 reg;

	reg = पढ़ोl_relaxed(cdns_ctrl->reg + BCH_CFG_3);
	cdns_ctrl->bch_metadata_size = FIELD_GET(BCH_CFG_3_METADATA_SIZE, reg);
	अगर (cdns_ctrl->bch_metadata_size < 4) अणु
		dev_err(cdns_ctrl->dev,
			"Driver needs at least 4 bytes of BCH meta data\n");
		वापस -EIO;
	पूर्ण

	reg = पढ़ोl_relaxed(cdns_ctrl->reg + BCH_CFG_0);
	cdns_ctrl->ecc_strengths[0] = FIELD_GET(BCH_CFG_0_CORR_CAP_0, reg);
	cdns_ctrl->ecc_strengths[1] = FIELD_GET(BCH_CFG_0_CORR_CAP_1, reg);
	cdns_ctrl->ecc_strengths[2] = FIELD_GET(BCH_CFG_0_CORR_CAP_2, reg);
	cdns_ctrl->ecc_strengths[3] = FIELD_GET(BCH_CFG_0_CORR_CAP_3, reg);

	reg = पढ़ोl_relaxed(cdns_ctrl->reg + BCH_CFG_1);
	cdns_ctrl->ecc_strengths[4] = FIELD_GET(BCH_CFG_1_CORR_CAP_4, reg);
	cdns_ctrl->ecc_strengths[5] = FIELD_GET(BCH_CFG_1_CORR_CAP_5, reg);
	cdns_ctrl->ecc_strengths[6] = FIELD_GET(BCH_CFG_1_CORR_CAP_6, reg);
	cdns_ctrl->ecc_strengths[7] = FIELD_GET(BCH_CFG_1_CORR_CAP_7, reg);

	reg = पढ़ोl_relaxed(cdns_ctrl->reg + BCH_CFG_2);
	cdns_ctrl->ecc_stepinfos[0].stepsize =
		FIELD_GET(BCH_CFG_2_SECT_0, reg);

	cdns_ctrl->ecc_stepinfos[1].stepsize =
		FIELD_GET(BCH_CFG_2_SECT_1, reg);

	nstrengths = 0;
	क्रम (i = 0; i < BCH_MAX_NUM_CORR_CAPS; i++) अणु
		अगर (cdns_ctrl->ecc_strengths[i] != 0)
			nstrengths++;
	पूर्ण

	ecc_caps->nstepinfos = 0;
	क्रम (i = 0; i < BCH_MAX_NUM_SECTOR_SIZES; i++) अणु
		/* ECC strengths are common क्रम all step infos. */
		cdns_ctrl->ecc_stepinfos[i].nstrengths = nstrengths;
		cdns_ctrl->ecc_stepinfos[i].strengths =
			cdns_ctrl->ecc_strengths;

		अगर (cdns_ctrl->ecc_stepinfos[i].stepsize != 0)
			ecc_caps->nstepinfos++;

		अगर (cdns_ctrl->ecc_stepinfos[i].stepsize > max_step_size)
			max_step_size = cdns_ctrl->ecc_stepinfos[i].stepsize;
	पूर्ण
	ecc_caps->stepinfos = &cdns_ctrl->ecc_stepinfos[0];

	चयन (max_step_size) अणु
	हाल 256:
		ecc_caps->calc_ecc_bytes = &cadence_nand_calc_ecc_bytes_256;
		अवरोध;
	हाल 512:
		ecc_caps->calc_ecc_bytes = &cadence_nand_calc_ecc_bytes_512;
		अवरोध;
	हाल 1024:
		ecc_caps->calc_ecc_bytes = &cadence_nand_calc_ecc_bytes_1024;
		अवरोध;
	हाल 2048:
		ecc_caps->calc_ecc_bytes = &cadence_nand_calc_ecc_bytes_2048;
		अवरोध;
	हाल 4096:
		ecc_caps->calc_ecc_bytes = &cadence_nand_calc_ecc_bytes_4096;
		अवरोध;
	शेष:
		dev_err(cdns_ctrl->dev,
			"Unsupported sector size(ecc step size) %d\n",
			max_step_size);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/* Hardware initialization. */
अटल पूर्णांक cadence_nand_hw_init(काष्ठा cdns_nand_ctrl *cdns_ctrl)
अणु
	पूर्णांक status;
	u32 reg;

	status = cadence_nand_रुको_क्रम_value(cdns_ctrl, CTRL_STATUS,
					     1000000,
					     CTRL_STATUS_INIT_COMP, false);
	अगर (status)
		वापस status;

	reg = पढ़ोl_relaxed(cdns_ctrl->reg + CTRL_VERSION);
	cdns_ctrl->ctrl_rev = FIELD_GET(CTRL_VERSION_REV, reg);

	dev_info(cdns_ctrl->dev,
		 "%s: cadence nand controller version reg %x\n",
		 __func__, reg);

	/* Disable cache and multiplane. */
	ग_लिखोl_relaxed(0, cdns_ctrl->reg + MULTIPLANE_CFG);
	ग_लिखोl_relaxed(0, cdns_ctrl->reg + CACHE_CFG);

	/* Clear all पूर्णांकerrupts. */
	ग_लिखोl_relaxed(0xFFFFFFFF, cdns_ctrl->reg + INTR_STATUS);

	cadence_nand_get_caps(cdns_ctrl);
	अगर (cadence_nand_पढ़ो_bch_caps(cdns_ctrl))
		वापस -EIO;

	/*
	 * Set IO width access to 8.
	 * It is because during SW device discovering width access
	 * is expected to be 8.
	 */
	status = cadence_nand_set_access_width16(cdns_ctrl, false);

	वापस status;
पूर्ण

#घोषणा TT_MAIN_OOB_AREAS	2
#घोषणा TT_RAW_PAGE		3
#घोषणा TT_BBM			4
#घोषणा TT_MAIN_OOB_AREA_EXT	5

/* Prepare size of data to transfer. */
अटल व्योम
cadence_nand_prepare_data_size(काष्ठा nand_chip *chip,
			       पूर्णांक transfer_type)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	u32 sec_size = 0, offset = 0, sec_cnt = 1;
	u32 last_sec_size = cdns_chip->sector_size;
	u32 data_ctrl_size = 0;
	u32 reg = 0;

	अगर (cdns_ctrl->curr_trans_type == transfer_type)
		वापस;

	चयन (transfer_type) अणु
	हाल TT_MAIN_OOB_AREA_EXT:
		sec_cnt = cdns_chip->sector_count;
		sec_size = cdns_chip->sector_size;
		data_ctrl_size = cdns_chip->avail_oob_size;
		अवरोध;
	हाल TT_MAIN_OOB_AREAS:
		sec_cnt = cdns_chip->sector_count;
		last_sec_size = cdns_chip->sector_size
			+ cdns_chip->avail_oob_size;
		sec_size = cdns_chip->sector_size;
		अवरोध;
	हाल TT_RAW_PAGE:
		last_sec_size = mtd->ग_लिखोsize + mtd->oobsize;
		अवरोध;
	हाल TT_BBM:
		offset = mtd->ग_लिखोsize + cdns_chip->bbm_offs;
		last_sec_size = 8;
		अवरोध;
	पूर्ण

	reg = 0;
	reg |= FIELD_PREP(TRAN_CFG_0_OFFSET, offset);
	reg |= FIELD_PREP(TRAN_CFG_0_SEC_CNT, sec_cnt);
	ग_लिखोl_relaxed(reg, cdns_ctrl->reg + TRAN_CFG_0);

	reg = 0;
	reg |= FIELD_PREP(TRAN_CFG_1_LAST_SEC_SIZE, last_sec_size);
	reg |= FIELD_PREP(TRAN_CFG_1_SECTOR_SIZE, sec_size);
	ग_लिखोl_relaxed(reg, cdns_ctrl->reg + TRAN_CFG_1);

	अगर (cdns_ctrl->caps2.data_control_supp) अणु
		reg = पढ़ोl_relaxed(cdns_ctrl->reg + CONTROL_DATA_CTRL);
		reg &= ~CONTROL_DATA_CTRL_SIZE;
		reg |= FIELD_PREP(CONTROL_DATA_CTRL_SIZE, data_ctrl_size);
		ग_लिखोl_relaxed(reg, cdns_ctrl->reg + CONTROL_DATA_CTRL);
	पूर्ण

	cdns_ctrl->curr_trans_type = transfer_type;
पूर्ण

अटल पूर्णांक
cadence_nand_cdma_transfer(काष्ठा cdns_nand_ctrl *cdns_ctrl, u8 chip_nr,
			   पूर्णांक page, व्योम *buf, व्योम *ctrl_dat, u32 buf_size,
			   u32 ctrl_dat_size, क्रमागत dma_data_direction dir,
			   bool with_ecc)
अणु
	dma_addr_t dma_buf, dma_ctrl_dat = 0;
	u8 thपढ़ो_nr = chip_nr;
	पूर्णांक status;
	u16 ctype;

	अगर (dir == DMA_FROM_DEVICE)
		ctype = CDMA_CT_RD;
	अन्यथा
		ctype = CDMA_CT_WR;

	cadence_nand_set_ecc_enable(cdns_ctrl, with_ecc);

	dma_buf = dma_map_single(cdns_ctrl->dev, buf, buf_size, dir);
	अगर (dma_mapping_error(cdns_ctrl->dev, dma_buf)) अणु
		dev_err(cdns_ctrl->dev, "Failed to map DMA buffer\n");
		वापस -EIO;
	पूर्ण

	अगर (ctrl_dat && ctrl_dat_size) अणु
		dma_ctrl_dat = dma_map_single(cdns_ctrl->dev, ctrl_dat,
					      ctrl_dat_size, dir);
		अगर (dma_mapping_error(cdns_ctrl->dev, dma_ctrl_dat)) अणु
			dma_unmap_single(cdns_ctrl->dev, dma_buf,
					 buf_size, dir);
			dev_err(cdns_ctrl->dev, "Failed to map DMA buffer\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	cadence_nand_cdma_desc_prepare(cdns_ctrl, chip_nr, page,
				       dma_buf, dma_ctrl_dat, ctype);

	status = cadence_nand_cdma_send_and_रुको(cdns_ctrl, thपढ़ो_nr);

	dma_unmap_single(cdns_ctrl->dev, dma_buf,
			 buf_size, dir);

	अगर (ctrl_dat && ctrl_dat_size)
		dma_unmap_single(cdns_ctrl->dev, dma_ctrl_dat,
				 ctrl_dat_size, dir);
	अगर (status)
		वापस status;

	वापस cadence_nand_cdma_finish(cdns_ctrl);
पूर्ण

अटल व्योम cadence_nand_set_timings(काष्ठा cdns_nand_ctrl *cdns_ctrl,
				     काष्ठा cadence_nand_timings *t)
अणु
	ग_लिखोl_relaxed(t->async_toggle_timings,
		       cdns_ctrl->reg + ASYNC_TOGGLE_TIMINGS);
	ग_लिखोl_relaxed(t->timings0, cdns_ctrl->reg + TIMINGS0);
	ग_लिखोl_relaxed(t->timings1, cdns_ctrl->reg + TIMINGS1);
	ग_लिखोl_relaxed(t->timings2, cdns_ctrl->reg + TIMINGS2);

	अगर (cdns_ctrl->caps2.is_phy_type_dll)
		ग_लिखोl_relaxed(t->dll_phy_ctrl, cdns_ctrl->reg + DLL_PHY_CTRL);

	ग_लिखोl_relaxed(t->phy_ctrl, cdns_ctrl->reg + PHY_CTRL);

	अगर (cdns_ctrl->caps2.is_phy_type_dll) अणु
		ग_लिखोl_relaxed(0, cdns_ctrl->reg + PHY_TSEL);
		ग_लिखोl_relaxed(2, cdns_ctrl->reg + PHY_DQ_TIMING);
		ग_लिखोl_relaxed(t->phy_dqs_timing,
			       cdns_ctrl->reg + PHY_DQS_TIMING);
		ग_लिखोl_relaxed(t->phy_gate_lpbk_ctrl,
			       cdns_ctrl->reg + PHY_GATE_LPBK_CTRL);
		ग_लिखोl_relaxed(PHY_DLL_MASTER_CTRL_BYPASS_MODE,
			       cdns_ctrl->reg + PHY_DLL_MASTER_CTRL);
		ग_लिखोl_relaxed(0, cdns_ctrl->reg + PHY_DLL_SLAVE_CTRL);
	पूर्ण
पूर्ण

अटल पूर्णांक cadence_nand_select_target(काष्ठा nand_chip *chip)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);

	अगर (chip == cdns_ctrl->selected_chip)
		वापस 0;

	अगर (cadence_nand_रुको_क्रम_value(cdns_ctrl, CTRL_STATUS,
					1000000,
					CTRL_STATUS_CTRL_BUSY, true))
		वापस -ETIMEDOUT;

	cadence_nand_set_timings(cdns_ctrl, &cdns_chip->timings);

	cadence_nand_set_ecc_strength(cdns_ctrl,
				      cdns_chip->corr_str_idx);

	cadence_nand_set_erase_detection(cdns_ctrl, true,
					 chip->ecc.strength);

	cdns_ctrl->curr_trans_type = -1;
	cdns_ctrl->selected_chip = chip;

	वापस 0;
पूर्ण

अटल पूर्णांक cadence_nand_erase(काष्ठा nand_chip *chip, u32 page)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	पूर्णांक status;
	u8 thपढ़ो_nr = cdns_chip->cs[chip->cur_cs];

	cadence_nand_cdma_desc_prepare(cdns_ctrl,
				       cdns_chip->cs[chip->cur_cs],
				       page, 0, 0,
				       CDMA_CT_ERASE);
	status = cadence_nand_cdma_send_and_रुको(cdns_ctrl, thपढ़ो_nr);
	अगर (status) अणु
		dev_err(cdns_ctrl->dev, "erase operation failed\n");
		वापस -EIO;
	पूर्ण

	status = cadence_nand_cdma_finish(cdns_ctrl);
	अगर (status)
		वापस status;

	वापस 0;
पूर्ण

अटल पूर्णांक cadence_nand_पढ़ो_bbm(काष्ठा nand_chip *chip, पूर्णांक page, u8 *buf)
अणु
	पूर्णांक status;
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	cadence_nand_prepare_data_size(chip, TT_BBM);

	cadence_nand_set_skip_bytes_conf(cdns_ctrl, 0, 0, 0);

	/*
	 * Read only bad block marker from offset
	 * defined by a memory manufacturer.
	 */
	status = cadence_nand_cdma_transfer(cdns_ctrl,
					    cdns_chip->cs[chip->cur_cs],
					    page, cdns_ctrl->buf, शून्य,
					    mtd->oobsize,
					    0, DMA_FROM_DEVICE, false);
	अगर (status) अणु
		dev_err(cdns_ctrl->dev, "read BBM failed\n");
		वापस -EIO;
	पूर्ण

	स_नकल(buf + cdns_chip->bbm_offs, cdns_ctrl->buf, cdns_chip->bbm_len);

	वापस 0;
पूर्ण

अटल पूर्णांक cadence_nand_ग_लिखो_page(काष्ठा nand_chip *chip,
				   स्थिर u8 *buf, पूर्णांक oob_required,
				   पूर्णांक page)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक status;
	u16 marker_val = 0xFFFF;

	status = cadence_nand_select_target(chip);
	अगर (status)
		वापस status;

	cadence_nand_set_skip_bytes_conf(cdns_ctrl, cdns_chip->bbm_len,
					 mtd->ग_लिखोsize
					 + cdns_chip->bbm_offs,
					 1);

	अगर (oob_required) अणु
		marker_val = *(u16 *)(chip->oob_poi
				      + cdns_chip->bbm_offs);
	पूर्ण अन्यथा अणु
		/* Set oob data to 0xFF. */
		स_रखो(cdns_ctrl->buf + mtd->ग_लिखोsize, 0xFF,
		       cdns_chip->avail_oob_size);
	पूर्ण

	cadence_nand_set_skip_marker_val(cdns_ctrl, marker_val);

	cadence_nand_prepare_data_size(chip, TT_MAIN_OOB_AREA_EXT);

	अगर (cadence_nand_dma_buf_ok(cdns_ctrl, buf, mtd->ग_लिखोsize) &&
	    cdns_ctrl->caps2.data_control_supp) अणु
		u8 *oob;

		अगर (oob_required)
			oob = chip->oob_poi;
		अन्यथा
			oob = cdns_ctrl->buf + mtd->ग_लिखोsize;

		status = cadence_nand_cdma_transfer(cdns_ctrl,
						    cdns_chip->cs[chip->cur_cs],
						    page, (व्योम *)buf, oob,
						    mtd->ग_लिखोsize,
						    cdns_chip->avail_oob_size,
						    DMA_TO_DEVICE, true);
		अगर (status) अणु
			dev_err(cdns_ctrl->dev, "write page failed\n");
			वापस -EIO;
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (oob_required) अणु
		/* Transfer the data to the oob area. */
		स_नकल(cdns_ctrl->buf + mtd->ग_लिखोsize, chip->oob_poi,
		       cdns_chip->avail_oob_size);
	पूर्ण

	स_नकल(cdns_ctrl->buf, buf, mtd->ग_लिखोsize);

	cadence_nand_prepare_data_size(chip, TT_MAIN_OOB_AREAS);

	वापस cadence_nand_cdma_transfer(cdns_ctrl,
					  cdns_chip->cs[chip->cur_cs],
					  page, cdns_ctrl->buf, शून्य,
					  mtd->ग_लिखोsize
					  + cdns_chip->avail_oob_size,
					  0, DMA_TO_DEVICE, true);
पूर्ण

अटल पूर्णांक cadence_nand_ग_लिखो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	स_रखो(cdns_ctrl->buf, 0xFF, mtd->ग_लिखोsize);

	वापस cadence_nand_ग_लिखो_page(chip, cdns_ctrl->buf, 1, page);
पूर्ण

अटल पूर्णांक cadence_nand_ग_लिखो_page_raw(काष्ठा nand_chip *chip,
				       स्थिर u8 *buf, पूर्णांक oob_required,
				       पूर्णांक page)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ग_लिखोsize = mtd->ग_लिखोsize;
	पूर्णांक oobsize = mtd->oobsize;
	पूर्णांक ecc_steps = chip->ecc.steps;
	पूर्णांक ecc_size = chip->ecc.size;
	पूर्णांक ecc_bytes = chip->ecc.bytes;
	व्योम *पंचांगp_buf = cdns_ctrl->buf;
	पूर्णांक oob_skip = cdns_chip->bbm_len;
	माप_प्रकार size = ग_लिखोsize + oobsize;
	पूर्णांक i, pos, len;
	पूर्णांक status = 0;

	status = cadence_nand_select_target(chip);
	अगर (status)
		वापस status;

	/*
	 * Fill the buffer with 0xff first except the full page transfer.
	 * This simplअगरies the logic.
	 */
	अगर (!buf || !oob_required)
		स_रखो(पंचांगp_buf, 0xff, size);

	cadence_nand_set_skip_bytes_conf(cdns_ctrl, 0, 0, 0);

	/* Arrange the buffer क्रम syndrome payload/ecc layout. */
	अगर (buf) अणु
		क्रम (i = 0; i < ecc_steps; i++) अणु
			pos = i * (ecc_size + ecc_bytes);
			len = ecc_size;

			अगर (pos >= ग_लिखोsize)
				pos += oob_skip;
			अन्यथा अगर (pos + len > ग_लिखोsize)
				len = ग_लिखोsize - pos;

			स_नकल(पंचांगp_buf + pos, buf, len);
			buf += len;
			अगर (len < ecc_size) अणु
				len = ecc_size - len;
				स_नकल(पंचांगp_buf + ग_लिखोsize + oob_skip, buf,
				       len);
				buf += len;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (oob_required) अणु
		स्थिर u8 *oob = chip->oob_poi;
		u32 oob_data_offset = (cdns_chip->sector_count - 1) *
			(cdns_chip->sector_size + chip->ecc.bytes)
			+ cdns_chip->sector_size + oob_skip;

		/* BBM at the beginning of the OOB area. */
		स_नकल(पंचांगp_buf + ग_लिखोsize, oob, oob_skip);

		/* OOB मुक्त. */
		स_नकल(पंचांगp_buf + oob_data_offset, oob,
		       cdns_chip->avail_oob_size);
		oob += cdns_chip->avail_oob_size;

		/* OOB ECC. */
		क्रम (i = 0; i < ecc_steps; i++) अणु
			pos = ecc_size + i * (ecc_size + ecc_bytes);
			अगर (i == (ecc_steps - 1))
				pos += cdns_chip->avail_oob_size;

			len = ecc_bytes;

			अगर (pos >= ग_लिखोsize)
				pos += oob_skip;
			अन्यथा अगर (pos + len > ग_लिखोsize)
				len = ग_लिखोsize - pos;

			स_नकल(पंचांगp_buf + pos, oob, len);
			oob += len;
			अगर (len < ecc_bytes) अणु
				len = ecc_bytes - len;
				स_नकल(पंचांगp_buf + ग_लिखोsize + oob_skip, oob,
				       len);
				oob += len;
			पूर्ण
		पूर्ण
	पूर्ण

	cadence_nand_prepare_data_size(chip, TT_RAW_PAGE);

	वापस cadence_nand_cdma_transfer(cdns_ctrl,
					  cdns_chip->cs[chip->cur_cs],
					  page, cdns_ctrl->buf, शून्य,
					  mtd->ग_लिखोsize +
					  mtd->oobsize,
					  0, DMA_TO_DEVICE, false);
पूर्ण

अटल पूर्णांक cadence_nand_ग_लिखो_oob_raw(काष्ठा nand_chip *chip,
				      पूर्णांक page)
अणु
	वापस cadence_nand_ग_लिखो_page_raw(chip, शून्य, true, page);
पूर्ण

अटल पूर्णांक cadence_nand_पढ़ो_page(काष्ठा nand_chip *chip,
				  u8 *buf, पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक status = 0;
	पूर्णांक ecc_err_count = 0;

	status = cadence_nand_select_target(chip);
	अगर (status)
		वापस status;

	cadence_nand_set_skip_bytes_conf(cdns_ctrl, cdns_chip->bbm_len,
					 mtd->ग_लिखोsize
					 + cdns_chip->bbm_offs, 1);

	/*
	 * If data buffer can be accessed by DMA and data_control feature
	 * is supported then transfer data and oob directly.
	 */
	अगर (cadence_nand_dma_buf_ok(cdns_ctrl, buf, mtd->ग_लिखोsize) &&
	    cdns_ctrl->caps2.data_control_supp) अणु
		u8 *oob;

		अगर (oob_required)
			oob = chip->oob_poi;
		अन्यथा
			oob = cdns_ctrl->buf + mtd->ग_लिखोsize;

		cadence_nand_prepare_data_size(chip, TT_MAIN_OOB_AREA_EXT);
		status = cadence_nand_cdma_transfer(cdns_ctrl,
						    cdns_chip->cs[chip->cur_cs],
						    page, buf, oob,
						    mtd->ग_लिखोsize,
						    cdns_chip->avail_oob_size,
						    DMA_FROM_DEVICE, true);
	/* Otherwise use bounce buffer. */
	पूर्ण अन्यथा अणु
		cadence_nand_prepare_data_size(chip, TT_MAIN_OOB_AREAS);
		status = cadence_nand_cdma_transfer(cdns_ctrl,
						    cdns_chip->cs[chip->cur_cs],
						    page, cdns_ctrl->buf,
						    शून्य, mtd->ग_लिखोsize
						    + cdns_chip->avail_oob_size,
						    0, DMA_FROM_DEVICE, true);

		स_नकल(buf, cdns_ctrl->buf, mtd->ग_लिखोsize);
		अगर (oob_required)
			स_नकल(chip->oob_poi,
			       cdns_ctrl->buf + mtd->ग_लिखोsize,
			       mtd->oobsize);
	पूर्ण

	चयन (status) अणु
	हाल STAT_ECC_UNCORR:
		mtd->ecc_stats.failed++;
		ecc_err_count++;
		अवरोध;
	हाल STAT_ECC_CORR:
		ecc_err_count = FIELD_GET(CDMA_CS_MAXERR,
					  cdns_ctrl->cdma_desc->status);
		mtd->ecc_stats.corrected += ecc_err_count;
		अवरोध;
	हाल STAT_ERASED:
	हाल STAT_OK:
		अवरोध;
	शेष:
		dev_err(cdns_ctrl->dev, "read page failed\n");
		वापस -EIO;
	पूर्ण

	अगर (oob_required)
		अगर (cadence_nand_पढ़ो_bbm(chip, page, chip->oob_poi))
			वापस -EIO;

	वापस ecc_err_count;
पूर्ण

/* Reads OOB data from the device. */
अटल पूर्णांक cadence_nand_पढ़ो_oob(काष्ठा nand_chip *chip, पूर्णांक page)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);

	वापस cadence_nand_पढ़ो_page(chip, cdns_ctrl->buf, 1, page);
पूर्ण

अटल पूर्णांक cadence_nand_पढ़ो_page_raw(काष्ठा nand_chip *chip,
				      u8 *buf, पूर्णांक oob_required, पूर्णांक page)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक oob_skip = cdns_chip->bbm_len;
	पूर्णांक ग_लिखोsize = mtd->ग_लिखोsize;
	पूर्णांक ecc_steps = chip->ecc.steps;
	पूर्णांक ecc_size = chip->ecc.size;
	पूर्णांक ecc_bytes = chip->ecc.bytes;
	व्योम *पंचांगp_buf = cdns_ctrl->buf;
	पूर्णांक i, pos, len;
	पूर्णांक status = 0;

	status = cadence_nand_select_target(chip);
	अगर (status)
		वापस status;

	cadence_nand_set_skip_bytes_conf(cdns_ctrl, 0, 0, 0);

	cadence_nand_prepare_data_size(chip, TT_RAW_PAGE);
	status = cadence_nand_cdma_transfer(cdns_ctrl,
					    cdns_chip->cs[chip->cur_cs],
					    page, cdns_ctrl->buf, शून्य,
					    mtd->ग_लिखोsize
					    + mtd->oobsize,
					    0, DMA_FROM_DEVICE, false);

	चयन (status) अणु
	हाल STAT_ERASED:
	हाल STAT_OK:
		अवरोध;
	शेष:
		dev_err(cdns_ctrl->dev, "read raw page failed\n");
		वापस -EIO;
	पूर्ण

	/* Arrange the buffer क्रम syndrome payload/ecc layout. */
	अगर (buf) अणु
		क्रम (i = 0; i < ecc_steps; i++) अणु
			pos = i * (ecc_size + ecc_bytes);
			len = ecc_size;

			अगर (pos >= ग_लिखोsize)
				pos += oob_skip;
			अन्यथा अगर (pos + len > ग_लिखोsize)
				len = ग_लिखोsize - pos;

			स_नकल(buf, पंचांगp_buf + pos, len);
			buf += len;
			अगर (len < ecc_size) अणु
				len = ecc_size - len;
				स_नकल(buf, पंचांगp_buf + ग_लिखोsize + oob_skip,
				       len);
				buf += len;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (oob_required) अणु
		u8 *oob = chip->oob_poi;
		u32 oob_data_offset = (cdns_chip->sector_count - 1) *
			(cdns_chip->sector_size + chip->ecc.bytes)
			+ cdns_chip->sector_size + oob_skip;

		/* OOB मुक्त. */
		स_नकल(oob, पंचांगp_buf + oob_data_offset,
		       cdns_chip->avail_oob_size);

		/* BBM at the beginning of the OOB area. */
		स_नकल(oob, पंचांगp_buf + ग_लिखोsize, oob_skip);

		oob += cdns_chip->avail_oob_size;

		/* OOB ECC */
		क्रम (i = 0; i < ecc_steps; i++) अणु
			pos = ecc_size + i * (ecc_size + ecc_bytes);
			len = ecc_bytes;

			अगर (i == (ecc_steps - 1))
				pos += cdns_chip->avail_oob_size;

			अगर (pos >= ग_लिखोsize)
				pos += oob_skip;
			अन्यथा अगर (pos + len > ग_लिखोsize)
				len = ग_लिखोsize - pos;

			स_नकल(oob, पंचांगp_buf + pos, len);
			oob += len;
			अगर (len < ecc_bytes) अणु
				len = ecc_bytes - len;
				स_नकल(oob, पंचांगp_buf + ग_लिखोsize + oob_skip,
				       len);
				oob += len;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cadence_nand_पढ़ो_oob_raw(काष्ठा nand_chip *chip,
				     पूर्णांक page)
अणु
	वापस cadence_nand_पढ़ो_page_raw(chip, शून्य, true, page);
पूर्ण

अटल व्योम cadence_nand_slave_dma_transfer_finished(व्योम *data)
अणु
	काष्ठा completion *finished = data;

	complete(finished);
पूर्ण

अटल पूर्णांक cadence_nand_slave_dma_transfer(काष्ठा cdns_nand_ctrl *cdns_ctrl,
					   व्योम *buf,
					   dma_addr_t dev_dma, माप_प्रकार len,
					   क्रमागत dma_data_direction dir)
अणु
	DECLARE_COMPLETION_ONSTACK(finished);
	काष्ठा dma_chan *chan;
	काष्ठा dma_device *dma_dev;
	dma_addr_t src_dma, dst_dma, buf_dma;
	काष्ठा dma_async_tx_descriptor *tx;
	dma_cookie_t cookie;

	chan = cdns_ctrl->dmac;
	dma_dev = chan->device;

	buf_dma = dma_map_single(dma_dev->dev, buf, len, dir);
	अगर (dma_mapping_error(dma_dev->dev, buf_dma)) अणु
		dev_err(cdns_ctrl->dev, "Failed to map DMA buffer\n");
		जाओ err;
	पूर्ण

	अगर (dir == DMA_FROM_DEVICE) अणु
		src_dma = cdns_ctrl->io.dma;
		dst_dma = buf_dma;
	पूर्ण अन्यथा अणु
		src_dma = buf_dma;
		dst_dma = cdns_ctrl->io.dma;
	पूर्ण

	tx = dmaengine_prep_dma_स_नकल(cdns_ctrl->dmac, dst_dma, src_dma, len,
				       DMA_CTRL_ACK | DMA_PREP_INTERRUPT);
	अगर (!tx) अणु
		dev_err(cdns_ctrl->dev, "Failed to prepare DMA memcpy\n");
		जाओ err_unmap;
	पूर्ण

	tx->callback = cadence_nand_slave_dma_transfer_finished;
	tx->callback_param = &finished;

	cookie = dmaengine_submit(tx);
	अगर (dma_submit_error(cookie)) अणु
		dev_err(cdns_ctrl->dev, "Failed to do DMA tx_submit\n");
		जाओ err_unmap;
	पूर्ण

	dma_async_issue_pending(cdns_ctrl->dmac);
	रुको_क्रम_completion(&finished);

	dma_unmap_single(cdns_ctrl->dev, buf_dma, len, dir);

	वापस 0;

err_unmap:
	dma_unmap_single(cdns_ctrl->dev, buf_dma, len, dir);

err:
	dev_dbg(cdns_ctrl->dev, "Fall back to CPU I/O\n");

	वापस -EIO;
पूर्ण

अटल पूर्णांक cadence_nand_पढ़ो_buf(काष्ठा cdns_nand_ctrl *cdns_ctrl,
				 u8 *buf, पूर्णांक len)
अणु
	u8 thपढ़ो_nr = 0;
	u32 sdma_size;
	पूर्णांक status;

	/* Wait until slave DMA पूर्णांकerface is पढ़ोy to data transfer. */
	status = cadence_nand_रुको_on_sdma(cdns_ctrl, &thपढ़ो_nr, &sdma_size);
	अगर (status)
		वापस status;

	अगर (!cdns_ctrl->caps1->has_dma) अणु
		पूर्णांक len_in_words = len >> 2;

		/* पढ़ो alingment data */
		ioपढ़ो32_rep(cdns_ctrl->io.virt, buf, len_in_words);
		अगर (sdma_size > len) अणु
			/* पढ़ो rest data from slave DMA पूर्णांकerface अगर any */
			ioपढ़ो32_rep(cdns_ctrl->io.virt, cdns_ctrl->buf,
				     sdma_size / 4 - len_in_words);
			/* copy rest of data */
			स_नकल(buf + (len_in_words << 2), cdns_ctrl->buf,
			       len - (len_in_words << 2));
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (cadence_nand_dma_buf_ok(cdns_ctrl, buf, len)) अणु
		status = cadence_nand_slave_dma_transfer(cdns_ctrl, buf,
							 cdns_ctrl->io.dma,
							 len, DMA_FROM_DEVICE);
		अगर (status == 0)
			वापस 0;

		dev_warn(cdns_ctrl->dev,
			 "Slave DMA transfer failed. Try again using bounce buffer.");
	पूर्ण

	/* If DMA transfer is not possible or failed then use bounce buffer. */
	status = cadence_nand_slave_dma_transfer(cdns_ctrl, cdns_ctrl->buf,
						 cdns_ctrl->io.dma,
						 sdma_size, DMA_FROM_DEVICE);

	अगर (status) अणु
		dev_err(cdns_ctrl->dev, "Slave DMA transfer failed");
		वापस status;
	पूर्ण

	स_नकल(buf, cdns_ctrl->buf, len);

	वापस 0;
पूर्ण

अटल पूर्णांक cadence_nand_ग_लिखो_buf(काष्ठा cdns_nand_ctrl *cdns_ctrl,
				  स्थिर u8 *buf, पूर्णांक len)
अणु
	u8 thपढ़ो_nr = 0;
	u32 sdma_size;
	पूर्णांक status;

	/* Wait until slave DMA पूर्णांकerface is पढ़ोy to data transfer. */
	status = cadence_nand_रुको_on_sdma(cdns_ctrl, &thपढ़ो_nr, &sdma_size);
	अगर (status)
		वापस status;

	अगर (!cdns_ctrl->caps1->has_dma) अणु
		पूर्णांक len_in_words = len >> 2;

		ioग_लिखो32_rep(cdns_ctrl->io.virt, buf, len_in_words);
		अगर (sdma_size > len) अणु
			/* copy rest of data */
			स_नकल(cdns_ctrl->buf, buf + (len_in_words << 2),
			       len - (len_in_words << 2));
			/* ग_लिखो all expected by nand controller data */
			ioग_लिखो32_rep(cdns_ctrl->io.virt, cdns_ctrl->buf,
				      sdma_size / 4 - len_in_words);
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (cadence_nand_dma_buf_ok(cdns_ctrl, buf, len)) अणु
		status = cadence_nand_slave_dma_transfer(cdns_ctrl, (व्योम *)buf,
							 cdns_ctrl->io.dma,
							 len, DMA_TO_DEVICE);
		अगर (status == 0)
			वापस 0;

		dev_warn(cdns_ctrl->dev,
			 "Slave DMA transfer failed. Try again using bounce buffer.");
	पूर्ण

	/* If DMA transfer is not possible or failed then use bounce buffer. */
	स_नकल(cdns_ctrl->buf, buf, len);

	status = cadence_nand_slave_dma_transfer(cdns_ctrl, cdns_ctrl->buf,
						 cdns_ctrl->io.dma,
						 sdma_size, DMA_TO_DEVICE);

	अगर (status)
		dev_err(cdns_ctrl->dev, "Slave DMA transfer failed");

	वापस status;
पूर्ण

अटल पूर्णांक cadence_nand_क्रमce_byte_access(काष्ठा nand_chip *chip,
					  bool क्रमce_8bit)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	पूर्णांक status;

	/*
	 * Callers of this function करो not verअगरy अगर the न_अंकD is using a 16-bit
	 * an 8-bit bus क्रम normal operations, so we need to take care of that
	 * here by leaving the configuration unchanged अगर the न_अंकD करोes not have
	 * the न_अंकD_BUSWIDTH_16 flag set.
	 */
	अगर (!(chip->options & न_अंकD_BUSWIDTH_16))
		वापस 0;

	status = cadence_nand_set_access_width16(cdns_ctrl, !क्रमce_8bit);

	वापस status;
पूर्ण

अटल पूर्णांक cadence_nand_cmd_opcode(काष्ठा nand_chip *chip,
				   स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	स्थिर काष्ठा nand_op_instr *instr;
	अचिन्हित पूर्णांक op_id = 0;
	u64 mini_ctrl_cmd = 0;
	पूर्णांक ret;

	instr = &subop->instrs[op_id];

	अगर (instr->delay_ns > 0)
		mini_ctrl_cmd |= GCMD_LAY_TWB;

	mini_ctrl_cmd |= FIELD_PREP(GCMD_LAY_INSTR,
				    GCMD_LAY_INSTR_CMD);
	mini_ctrl_cmd |= FIELD_PREP(GCMD_LAY_INPUT_CMD,
				    instr->ctx.cmd.opcode);

	ret = cadence_nand_generic_cmd_send(cdns_ctrl,
					    cdns_chip->cs[chip->cur_cs],
					    mini_ctrl_cmd);
	अगर (ret)
		dev_err(cdns_ctrl->dev, "send cmd %x failed\n",
			instr->ctx.cmd.opcode);

	वापस ret;
पूर्ण

अटल पूर्णांक cadence_nand_cmd_address(काष्ठा nand_chip *chip,
				    स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	स्थिर काष्ठा nand_op_instr *instr;
	अचिन्हित पूर्णांक op_id = 0;
	u64 mini_ctrl_cmd = 0;
	अचिन्हित पूर्णांक offset, naddrs;
	u64 address = 0;
	स्थिर u8 *addrs;
	पूर्णांक ret;
	पूर्णांक i;

	instr = &subop->instrs[op_id];

	अगर (instr->delay_ns > 0)
		mini_ctrl_cmd |= GCMD_LAY_TWB;

	mini_ctrl_cmd |= FIELD_PREP(GCMD_LAY_INSTR,
				    GCMD_LAY_INSTR_ADDR);

	offset = nand_subop_get_addr_start_off(subop, op_id);
	naddrs = nand_subop_get_num_addr_cyc(subop, op_id);
	addrs = &instr->ctx.addr.addrs[offset];

	क्रम (i = 0; i < naddrs; i++)
		address |= (u64)addrs[i] << (8 * i);

	mini_ctrl_cmd |= FIELD_PREP(GCMD_LAY_INPUT_ADDR,
				    address);
	mini_ctrl_cmd |= FIELD_PREP(GCMD_LAY_INPUT_ADDR_SIZE,
				    naddrs - 1);

	ret = cadence_nand_generic_cmd_send(cdns_ctrl,
					    cdns_chip->cs[chip->cur_cs],
					    mini_ctrl_cmd);
	अगर (ret)
		dev_err(cdns_ctrl->dev, "send address %llx failed\n", address);

	वापस ret;
पूर्ण

अटल पूर्णांक cadence_nand_cmd_erase(काष्ठा nand_chip *chip,
				  स्थिर काष्ठा nand_subop *subop)
अणु
	अचिन्हित पूर्णांक op_id;

	अगर (subop->instrs[0].ctx.cmd.opcode == न_अंकD_CMD_ERASE1) अणु
		पूर्णांक i;
		स्थिर काष्ठा nand_op_instr *instr = शून्य;
		अचिन्हित पूर्णांक offset, naddrs;
		स्थिर u8 *addrs;
		u32 page = 0;

		instr = &subop->instrs[1];
		offset = nand_subop_get_addr_start_off(subop, 1);
		naddrs = nand_subop_get_num_addr_cyc(subop, 1);
		addrs = &instr->ctx.addr.addrs[offset];

		क्रम (i = 0; i < naddrs; i++)
			page |= (u32)addrs[i] << (8 * i);

		वापस cadence_nand_erase(chip, page);
	पूर्ण

	/*
	 * If it is not an erase operation then handle operation
	 * by calling exec_op function.
	 */
	क्रम (op_id = 0; op_id < subop->ninstrs; op_id++) अणु
		पूर्णांक ret;
		स्थिर काष्ठा nand_operation nand_op = अणु
			.cs = chip->cur_cs,
			.instrs =  &subop->instrs[op_id],
			.ninstrs = 1पूर्ण;
		ret = chip->controller->ops->exec_op(chip, &nand_op, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cadence_nand_cmd_data(काष्ठा nand_chip *chip,
				 स्थिर काष्ठा nand_subop *subop)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	स्थिर काष्ठा nand_op_instr *instr;
	अचिन्हित पूर्णांक offset, op_id = 0;
	u64 mini_ctrl_cmd = 0;
	पूर्णांक len = 0;
	पूर्णांक ret;

	instr = &subop->instrs[op_id];

	अगर (instr->delay_ns > 0)
		mini_ctrl_cmd |= GCMD_LAY_TWB;

	mini_ctrl_cmd |= FIELD_PREP(GCMD_LAY_INSTR,
				    GCMD_LAY_INSTR_DATA);

	अगर (instr->type == न_अंकD_OP_DATA_OUT_INSTR)
		mini_ctrl_cmd |= FIELD_PREP(GCMD_सूची,
					    GCMD_सूची_WRITE);

	len = nand_subop_get_data_len(subop, op_id);
	offset = nand_subop_get_data_start_off(subop, op_id);
	mini_ctrl_cmd |= FIELD_PREP(GCMD_SECT_CNT, 1);
	mini_ctrl_cmd |= FIELD_PREP(GCMD_LAST_SIZE, len);
	अगर (instr->ctx.data.क्रमce_8bit) अणु
		ret = cadence_nand_क्रमce_byte_access(chip, true);
		अगर (ret) अणु
			dev_err(cdns_ctrl->dev,
				"cannot change byte access generic data cmd failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = cadence_nand_generic_cmd_send(cdns_ctrl,
					    cdns_chip->cs[chip->cur_cs],
					    mini_ctrl_cmd);
	अगर (ret) अणु
		dev_err(cdns_ctrl->dev, "send generic data cmd failed\n");
		वापस ret;
	पूर्ण

	अगर (instr->type == न_अंकD_OP_DATA_IN_INSTR) अणु
		व्योम *buf = instr->ctx.data.buf.in + offset;

		ret = cadence_nand_पढ़ो_buf(cdns_ctrl, buf, len);
	पूर्ण अन्यथा अणु
		स्थिर व्योम *buf = instr->ctx.data.buf.out + offset;

		ret = cadence_nand_ग_लिखो_buf(cdns_ctrl, buf, len);
	पूर्ण

	अगर (ret) अणु
		dev_err(cdns_ctrl->dev, "data transfer failed for generic command\n");
		वापस ret;
	पूर्ण

	अगर (instr->ctx.data.क्रमce_8bit) अणु
		ret = cadence_nand_क्रमce_byte_access(chip, false);
		अगर (ret) अणु
			dev_err(cdns_ctrl->dev,
				"cannot change byte access generic data cmd failed\n");
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cadence_nand_cmd_रुकोrdy(काष्ठा nand_chip *chip,
				    स्थिर काष्ठा nand_subop *subop)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक op_id = 0;
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	स्थिर काष्ठा nand_op_instr *instr = &subop->instrs[op_id];
	u32 समयout_us = instr->ctx.रुकोrdy.समयout_ms * 1000;

	status = cadence_nand_रुको_क्रम_value(cdns_ctrl, RBN_SETINGS,
					     समयout_us,
					     BIT(cdns_chip->cs[chip->cur_cs]),
					     false);
	वापस status;
पूर्ण

अटल स्थिर काष्ठा nand_op_parser cadence_nand_op_parser = न_अंकD_OP_PARSER(
	न_अंकD_OP_PARSER_PATTERN(
		cadence_nand_cmd_erase,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(false, MAX_ERASE_ADDRESS_CYC),
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false),
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(false)),
	न_अंकD_OP_PARSER_PATTERN(
		cadence_nand_cmd_opcode,
		न_अंकD_OP_PARSER_PAT_CMD_ELEM(false)),
	न_अंकD_OP_PARSER_PATTERN(
		cadence_nand_cmd_address,
		न_अंकD_OP_PARSER_PAT_ADDR_ELEM(false, MAX_ADDRESS_CYC)),
	न_अंकD_OP_PARSER_PATTERN(
		cadence_nand_cmd_data,
		न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(false, MAX_DATA_SIZE)),
	न_अंकD_OP_PARSER_PATTERN(
		cadence_nand_cmd_data,
		न_अंकD_OP_PARSER_PAT_DATA_OUT_ELEM(false, MAX_DATA_SIZE)),
	न_अंकD_OP_PARSER_PATTERN(
		cadence_nand_cmd_रुकोrdy,
		न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(false))
	);

अटल पूर्णांक cadence_nand_exec_op(काष्ठा nand_chip *chip,
				स्थिर काष्ठा nand_operation *op,
				bool check_only)
अणु
	अगर (!check_only) अणु
		पूर्णांक status = cadence_nand_select_target(chip);

		अगर (status)
			वापस status;
	पूर्ण

	वापस nand_op_parser_exec_op(chip, &cadence_nand_op_parser, op,
				      check_only);
पूर्ण

अटल पूर्णांक cadence_nand_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				       काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);

	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = cdns_chip->bbm_len;
	oobregion->length = cdns_chip->avail_oob_size
		- cdns_chip->bbm_len;

	वापस 0;
पूर्ण

अटल पूर्णांक cadence_nand_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				      काष्ठा mtd_oob_region *oobregion)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);

	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = cdns_chip->avail_oob_size;
	oobregion->length = chip->ecc.total;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops cadence_nand_ooblayout_ops = अणु
	.मुक्त = cadence_nand_ooblayout_मुक्त,
	.ecc = cadence_nand_ooblayout_ecc,
पूर्ण;

अटल पूर्णांक calc_cycl(u32 timing, u32 घड़ी)
अणु
	अगर (timing == 0 || घड़ी == 0)
		वापस 0;

	अगर ((timing % घड़ी) > 0)
		वापस timing / घड़ी;
	अन्यथा
		वापस timing / घड़ी - 1;
पूर्ण

/* Calculate max data valid winकरोw. */
अटल अंतरभूत u32 calc_tdvw_max(u32 trp_cnt, u32 clk_period, u32 trhoh_min,
				u32 board_delay_skew_min, u32 ext_mode)
अणु
	अगर (ext_mode == 0)
		clk_period /= 2;

	वापस (trp_cnt + 1) * clk_period + trhoh_min +
		board_delay_skew_min;
पूर्ण

/* Calculate data valid winकरोw. */
अटल अंतरभूत u32 calc_tdvw(u32 trp_cnt, u32 clk_period, u32 trhoh_min,
			    u32 trea_max, u32 ext_mode)
अणु
	अगर (ext_mode == 0)
		clk_period /= 2;

	वापस (trp_cnt + 1) * clk_period + trhoh_min - trea_max;
पूर्ण

अटल पूर्णांक
cadence_nand_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक chipnr,
			     स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	स्थिर काष्ठा nand_sdr_timings *sdr;
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	काष्ठा cadence_nand_timings *t = &cdns_chip->timings;
	u32 reg;
	u32 board_delay = cdns_ctrl->board_delay;
	u32 clk_period = DIV_ROUND_DOWN_ULL(1000000000000ULL,
					    cdns_ctrl->nf_clk_rate);
	u32 tceh_cnt, tcs_cnt, tadl_cnt, tccs_cnt;
	u32 tfeat_cnt, trhz_cnt, tvdly_cnt;
	u32 trhw_cnt, twb_cnt, twh_cnt = 0, twhr_cnt;
	u32 twp_cnt = 0, trp_cnt = 0, trh_cnt = 0;
	u32 अगर_skew = cdns_ctrl->caps1->अगर_skew;
	u32 board_delay_skew_min = board_delay - अगर_skew;
	u32 board_delay_skew_max = board_delay + अगर_skew;
	u32 dqs_sampl_res, phony_dqs_mod;
	u32 tdvw, tdvw_min, tdvw_max;
	u32 ext_rd_mode, ext_wr_mode;
	u32 dll_phy_dqs_timing = 0, phony_dqs_timing = 0, rd_del_sel = 0;
	u32 sampling_poपूर्णांक;

	sdr = nand_get_sdr_timings(conf);
	अगर (IS_ERR(sdr))
		वापस PTR_ERR(sdr);

	स_रखो(t, 0, माप(*t));
	/* Sampling poपूर्णांक calculation. */

	अगर (cdns_ctrl->caps2.is_phy_type_dll)
		phony_dqs_mod = 2;
	अन्यथा
		phony_dqs_mod = 1;

	dqs_sampl_res = clk_period / phony_dqs_mod;

	tdvw_min = sdr->tREA_max + board_delay_skew_max;
	/*
	 * The idea of those calculation is to get the optimum value
	 * क्रम tRP and tRH timings. If it is NOT possible to sample data
	 * with optimal tRP/tRH settings, the parameters will be extended.
	 * If clk_period is 50ns (the lowest value) this condition is met
	 * क्रम asynchronous timing modes 1, 2, 3, 4 and 5.
	 * If clk_period is 20ns the condition is met only
	 * क्रम asynchronous timing mode 5.
	 */
	अगर (sdr->tRC_min <= clk_period &&
	    sdr->tRP_min <= (clk_period / 2) &&
	    sdr->tREH_min <= (clk_period / 2)) अणु
		/* Perक्रमmance mode. */
		ext_rd_mode = 0;
		tdvw = calc_tdvw(trp_cnt, clk_period, sdr->tRHOH_min,
				 sdr->tREA_max, ext_rd_mode);
		tdvw_max = calc_tdvw_max(trp_cnt, clk_period, sdr->tRHOH_min,
					 board_delay_skew_min,
					 ext_rd_mode);
		/*
		 * Check अगर data valid winकरोw and sampling poपूर्णांक can be found
		 * and is not on the edge (ie. we have hold margin).
		 * If not extend the tRP timings.
		 */
		अगर (tdvw > 0) अणु
			अगर (tdvw_max <= tdvw_min ||
			    (tdvw_max % dqs_sampl_res) == 0) अणु
				/*
				 * No valid sampling poपूर्णांक so the RE pulse need
				 * to be widen widening by half घड़ी cycle.
				 */
				ext_rd_mode = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * There is no valid winकरोw
			 * to be able to sample data the tRP need to be widen.
			 * Very safe calculations are perक्रमmed here.
			 */
			trp_cnt = (sdr->tREA_max + board_delay_skew_max
				   + dqs_sampl_res) / clk_period;
			ext_rd_mode = 1;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* Extended पढ़ो mode. */
		u32 trh;

		ext_rd_mode = 1;
		trp_cnt = calc_cycl(sdr->tRP_min, clk_period);
		trh = sdr->tRC_min - ((trp_cnt + 1) * clk_period);
		अगर (sdr->tREH_min >= trh)
			trh_cnt = calc_cycl(sdr->tREH_min, clk_period);
		अन्यथा
			trh_cnt = calc_cycl(trh, clk_period);

		tdvw = calc_tdvw(trp_cnt, clk_period, sdr->tRHOH_min,
				 sdr->tREA_max, ext_rd_mode);
		/*
		 * Check अगर data valid winकरोw and sampling poपूर्णांक can be found
		 * or अगर it is at the edge check अगर previous is valid
		 * - अगर not extend the tRP timings.
		 */
		अगर (tdvw > 0) अणु
			tdvw_max = calc_tdvw_max(trp_cnt, clk_period,
						 sdr->tRHOH_min,
						 board_delay_skew_min,
						 ext_rd_mode);

			अगर ((((tdvw_max / dqs_sampl_res)
			      * dqs_sampl_res) <= tdvw_min) ||
			    (((tdvw_max % dqs_sampl_res) == 0) &&
			     (((tdvw_max / dqs_sampl_res - 1)
			       * dqs_sampl_res) <= tdvw_min))) अणु
				/*
				 * Data valid winकरोw width is lower than
				 * sampling resolution and करो not hit any
				 * sampling poपूर्णांक to be sure the sampling poपूर्णांक
				 * will be found the RE low pulse width will be
				 *  extended by one घड़ी cycle.
				 */
				trp_cnt = trp_cnt + 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * There is no valid winकरोw to be able to sample data.
			 * The tRP need to be widen.
			 * Very safe calculations are perक्रमmed here.
			 */
			trp_cnt = (sdr->tREA_max + board_delay_skew_max
				   + dqs_sampl_res) / clk_period;
		पूर्ण
	पूर्ण

	tdvw_max = calc_tdvw_max(trp_cnt, clk_period,
				 sdr->tRHOH_min,
				 board_delay_skew_min, ext_rd_mode);

	अगर (sdr->tWC_min <= clk_period &&
	    (sdr->tWP_min + अगर_skew) <= (clk_period / 2) &&
	    (sdr->tWH_min + अगर_skew) <= (clk_period / 2)) अणु
		ext_wr_mode = 0;
	पूर्ण अन्यथा अणु
		u32 twh;

		ext_wr_mode = 1;
		twp_cnt = calc_cycl(sdr->tWP_min + अगर_skew, clk_period);
		अगर ((twp_cnt + 1) * clk_period < (sdr->tALS_min + अगर_skew))
			twp_cnt = calc_cycl(sdr->tALS_min + अगर_skew,
					    clk_period);

		twh = (sdr->tWC_min - (twp_cnt + 1) * clk_period);
		अगर (sdr->tWH_min >= twh)
			twh = sdr->tWH_min;

		twh_cnt = calc_cycl(twh + अगर_skew, clk_period);
	पूर्ण

	reg = FIELD_PREP(ASYNC_TOGGLE_TIMINGS_TRH, trh_cnt);
	reg |= FIELD_PREP(ASYNC_TOGGLE_TIMINGS_TRP, trp_cnt);
	reg |= FIELD_PREP(ASYNC_TOGGLE_TIMINGS_TWH, twh_cnt);
	reg |= FIELD_PREP(ASYNC_TOGGLE_TIMINGS_TWP, twp_cnt);
	t->async_toggle_timings = reg;
	dev_dbg(cdns_ctrl->dev, "ASYNC_TOGGLE_TIMINGS_SDR\t%x\n", reg);

	tadl_cnt = calc_cycl((sdr->tADL_min + अगर_skew), clk_period);
	tccs_cnt = calc_cycl((sdr->tCCS_min + अगर_skew), clk_period);
	twhr_cnt = calc_cycl((sdr->tWHR_min + अगर_skew), clk_period);
	trhw_cnt = calc_cycl((sdr->tRHW_min + अगर_skew), clk_period);
	reg = FIELD_PREP(TIMINGS0_TADL, tadl_cnt);

	/*
	 * If timing exceeds delay field in timing रेजिस्टर
	 * then use maximum value.
	 */
	अगर (FIELD_FIT(TIMINGS0_TCCS, tccs_cnt))
		reg |= FIELD_PREP(TIMINGS0_TCCS, tccs_cnt);
	अन्यथा
		reg |= TIMINGS0_TCCS;

	reg |= FIELD_PREP(TIMINGS0_TWHR, twhr_cnt);
	reg |= FIELD_PREP(TIMINGS0_TRHW, trhw_cnt);
	t->timings0 = reg;
	dev_dbg(cdns_ctrl->dev, "TIMINGS0_SDR\t%x\n", reg);

	/* The following is related to single संकेत so skew is not needed. */
	trhz_cnt = calc_cycl(sdr->tRHZ_max, clk_period);
	trhz_cnt = trhz_cnt + 1;
	twb_cnt = calc_cycl((sdr->tWB_max + board_delay), clk_period);
	/*
	 * Because of the two stage syncflop the value must be increased by 3
	 * first value is related with sync, second value is related
	 * with output अगर delay.
	 */
	twb_cnt = twb_cnt + 3 + 5;
	/*
	 * The following is related to the we edge of the अक्रमom data input
	 * sequence so skew is not needed.
	 */
	tvdly_cnt = calc_cycl(500000 + अगर_skew, clk_period);
	reg = FIELD_PREP(TIMINGS1_TRHZ, trhz_cnt);
	reg |= FIELD_PREP(TIMINGS1_TWB, twb_cnt);
	reg |= FIELD_PREP(TIMINGS1_TVDLY, tvdly_cnt);
	t->timings1 = reg;
	dev_dbg(cdns_ctrl->dev, "TIMINGS1_SDR\t%x\n", reg);

	tfeat_cnt = calc_cycl(sdr->tFEAT_max, clk_period);
	अगर (tfeat_cnt < twb_cnt)
		tfeat_cnt = twb_cnt;

	tceh_cnt = calc_cycl(sdr->tCEH_min, clk_period);
	tcs_cnt = calc_cycl((sdr->tCS_min + अगर_skew), clk_period);

	reg = FIELD_PREP(TIMINGS2_TFEAT, tfeat_cnt);
	reg |= FIELD_PREP(TIMINGS2_CS_HOLD_TIME, tceh_cnt);
	reg |= FIELD_PREP(TIMINGS2_CS_SETUP_TIME, tcs_cnt);
	t->timings2 = reg;
	dev_dbg(cdns_ctrl->dev, "TIMINGS2_SDR\t%x\n", reg);

	अगर (cdns_ctrl->caps2.is_phy_type_dll) अणु
		reg = DLL_PHY_CTRL_DLL_RST_N;
		अगर (ext_wr_mode)
			reg |= DLL_PHY_CTRL_EXTENDED_WR_MODE;
		अगर (ext_rd_mode)
			reg |= DLL_PHY_CTRL_EXTENDED_RD_MODE;

		reg |= FIELD_PREP(DLL_PHY_CTRL_RS_HIGH_WAIT_CNT, 7);
		reg |= FIELD_PREP(DLL_PHY_CTRL_RS_IDLE_CNT, 7);
		t->dll_phy_ctrl = reg;
		dev_dbg(cdns_ctrl->dev, "DLL_PHY_CTRL_SDR\t%x\n", reg);
	पूर्ण

	/* Sampling poपूर्णांक calculation. */
	अगर ((tdvw_max % dqs_sampl_res) > 0)
		sampling_poपूर्णांक = tdvw_max / dqs_sampl_res;
	अन्यथा
		sampling_poपूर्णांक = (tdvw_max / dqs_sampl_res - 1);

	अगर (sampling_poपूर्णांक * dqs_sampl_res > tdvw_min) अणु
		dll_phy_dqs_timing =
			FIELD_PREP(PHY_DQS_TIMING_DQS_SEL_OE_END, 4);
		dll_phy_dqs_timing |= PHY_DQS_TIMING_USE_PHONY_DQS;
		phony_dqs_timing = sampling_poपूर्णांक / phony_dqs_mod;

		अगर ((sampling_poपूर्णांक % 2) > 0) अणु
			dll_phy_dqs_timing |= PHY_DQS_TIMING_PHONY_DQS_SEL;
			अगर ((tdvw_max % dqs_sampl_res) == 0)
				/*
				 * Calculation क्रम sampling poपूर्णांक at the edge
				 * of data and being odd number.
				 */
				phony_dqs_timing = (tdvw_max / dqs_sampl_res)
					/ phony_dqs_mod - 1;

			अगर (!cdns_ctrl->caps2.is_phy_type_dll)
				phony_dqs_timing--;

		पूर्ण अन्यथा अणु
			phony_dqs_timing--;
		पूर्ण
		rd_del_sel = phony_dqs_timing + 3;
	पूर्ण अन्यथा अणु
		dev_warn(cdns_ctrl->dev,
			 "ERROR : cannot find valid sampling point\n");
	पूर्ण

	reg = FIELD_PREP(PHY_CTRL_PHONY_DQS, phony_dqs_timing);
	अगर (cdns_ctrl->caps2.is_phy_type_dll)
		reg  |= PHY_CTRL_SDR_DQS;
	t->phy_ctrl = reg;
	dev_dbg(cdns_ctrl->dev, "PHY_CTRL_REG_SDR\t%x\n", reg);

	अगर (cdns_ctrl->caps2.is_phy_type_dll) अणु
		dev_dbg(cdns_ctrl->dev, "PHY_TSEL_REG_SDR\t%x\n", 0);
		dev_dbg(cdns_ctrl->dev, "PHY_DQ_TIMING_REG_SDR\t%x\n", 2);
		dev_dbg(cdns_ctrl->dev, "PHY_DQS_TIMING_REG_SDR\t%x\n",
			dll_phy_dqs_timing);
		t->phy_dqs_timing = dll_phy_dqs_timing;

		reg = FIELD_PREP(PHY_GATE_LPBK_CTRL_RDS, rd_del_sel);
		dev_dbg(cdns_ctrl->dev, "PHY_GATE_LPBK_CTRL_REG_SDR\t%x\n",
			reg);
		t->phy_gate_lpbk_ctrl = reg;

		dev_dbg(cdns_ctrl->dev, "PHY_DLL_MASTER_CTRL_REG_SDR\t%lx\n",
			PHY_DLL_MASTER_CTRL_BYPASS_MODE);
		dev_dbg(cdns_ctrl->dev, "PHY_DLL_SLAVE_CTRL_REG_SDR\t%x\n", 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cadence_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा cdns_nand_ctrl *cdns_ctrl = to_cdns_nand_ctrl(chip->controller);
	काष्ठा cdns_nand_chip *cdns_chip = to_cdns_nand_chip(chip);
	u32 ecc_size;
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	पूर्णांक ret;

	अगर (chip->options & न_अंकD_BUSWIDTH_16) अणु
		ret = cadence_nand_set_access_width16(cdns_ctrl, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	chip->bbt_options |= न_अंकD_BBT_USE_FLASH;
	chip->bbt_options |= न_अंकD_BBT_NO_OOB;
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;

	chip->options |= न_अंकD_NO_SUBPAGE_WRITE;

	cdns_chip->bbm_offs = chip->badblockpos;
	cdns_chip->bbm_offs &= ~0x01;
	/* this value should be even number */
	cdns_chip->bbm_len = 2;

	ret = nand_ecc_choose_conf(chip,
				   &cdns_ctrl->ecc_caps,
				   mtd->oobsize - cdns_chip->bbm_len);
	अगर (ret) अणु
		dev_err(cdns_ctrl->dev, "ECC configuration failed\n");
		वापस ret;
	पूर्ण

	dev_dbg(cdns_ctrl->dev,
		"chosen ECC settings: step=%d, strength=%d, bytes=%d\n",
		chip->ecc.size, chip->ecc.strength, chip->ecc.bytes);

	/* Error correction configuration. */
	cdns_chip->sector_size = chip->ecc.size;
	cdns_chip->sector_count = mtd->ग_लिखोsize / cdns_chip->sector_size;
	ecc_size = cdns_chip->sector_count * chip->ecc.bytes;

	cdns_chip->avail_oob_size = mtd->oobsize - ecc_size;

	अगर (cdns_chip->avail_oob_size > cdns_ctrl->bch_metadata_size)
		cdns_chip->avail_oob_size = cdns_ctrl->bch_metadata_size;

	अगर ((cdns_chip->avail_oob_size + cdns_chip->bbm_len + ecc_size)
	    > mtd->oobsize)
		cdns_chip->avail_oob_size -= 4;

	ret = cadence_nand_get_ecc_strength_idx(cdns_ctrl, chip->ecc.strength);
	अगर (ret < 0)
		वापस -EINVAL;

	cdns_chip->corr_str_idx = (u8)ret;

	अगर (cadence_nand_रुको_क्रम_value(cdns_ctrl, CTRL_STATUS,
					1000000,
					CTRL_STATUS_CTRL_BUSY, true))
		वापस -ETIMEDOUT;

	cadence_nand_set_ecc_strength(cdns_ctrl,
				      cdns_chip->corr_str_idx);

	cadence_nand_set_erase_detection(cdns_ctrl, true,
					 chip->ecc.strength);

	/* Override the शेष पढ़ो operations. */
	chip->ecc.पढ़ो_page = cadence_nand_पढ़ो_page;
	chip->ecc.पढ़ो_page_raw = cadence_nand_पढ़ो_page_raw;
	chip->ecc.ग_लिखो_page = cadence_nand_ग_लिखो_page;
	chip->ecc.ग_लिखो_page_raw = cadence_nand_ग_लिखो_page_raw;
	chip->ecc.पढ़ो_oob = cadence_nand_पढ़ो_oob;
	chip->ecc.ग_लिखो_oob = cadence_nand_ग_लिखो_oob;
	chip->ecc.पढ़ो_oob_raw = cadence_nand_पढ़ो_oob_raw;
	chip->ecc.ग_लिखो_oob_raw = cadence_nand_ग_लिखो_oob_raw;

	अगर ((mtd->ग_लिखोsize + mtd->oobsize) > cdns_ctrl->buf_size)
		cdns_ctrl->buf_size = mtd->ग_लिखोsize + mtd->oobsize;

	/* Is 32-bit DMA supported? */
	ret = dma_set_mask(cdns_ctrl->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(cdns_ctrl->dev, "no usable DMA configuration\n");
		वापस ret;
	पूर्ण

	mtd_set_ooblayout(mtd, &cadence_nand_ooblayout_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops cadence_nand_controller_ops = अणु
	.attach_chip = cadence_nand_attach_chip,
	.exec_op = cadence_nand_exec_op,
	.setup_पूर्णांकerface = cadence_nand_setup_पूर्णांकerface,
पूर्ण;

अटल पूर्णांक cadence_nand_chip_init(काष्ठा cdns_nand_ctrl *cdns_ctrl,
				  काष्ठा device_node *np)
अणु
	काष्ठा cdns_nand_chip *cdns_chip;
	काष्ठा mtd_info *mtd;
	काष्ठा nand_chip *chip;
	पूर्णांक nsels, ret, i;
	u32 cs;

	nsels = of_property_count_elems_of_size(np, "reg", माप(u32));
	अगर (nsels <= 0) अणु
		dev_err(cdns_ctrl->dev, "missing/invalid reg property\n");
		वापस -EINVAL;
	पूर्ण

	/* Allocate the nand chip काष्ठाure. */
	cdns_chip = devm_kzalloc(cdns_ctrl->dev, माप(*cdns_chip) +
				 (nsels * माप(u8)),
				 GFP_KERNEL);
	अगर (!cdns_chip) अणु
		dev_err(cdns_ctrl->dev, "could not allocate chip structure\n");
		वापस -ENOMEM;
	पूर्ण

	cdns_chip->nsels = nsels;

	क्रम (i = 0; i < nsels; i++) अणु
		/* Retrieve CS id. */
		ret = of_property_पढ़ो_u32_index(np, "reg", i, &cs);
		अगर (ret) अणु
			dev_err(cdns_ctrl->dev,
				"could not retrieve reg property: %d\n",
				ret);
			वापस ret;
		पूर्ण

		अगर (cs >= cdns_ctrl->caps2.max_banks) अणु
			dev_err(cdns_ctrl->dev,
				"invalid reg value: %u (max CS = %d)\n",
				cs, cdns_ctrl->caps2.max_banks);
			वापस -EINVAL;
		पूर्ण

		अगर (test_and_set_bit(cs, &cdns_ctrl->asचिन्हित_cs)) अणु
			dev_err(cdns_ctrl->dev,
				"CS %d already assigned\n", cs);
			वापस -EINVAL;
		पूर्ण

		cdns_chip->cs[i] = cs;
	पूर्ण

	chip = &cdns_chip->chip;
	chip->controller = &cdns_ctrl->controller;
	nand_set_flash_node(chip, np);

	mtd = nand_to_mtd(chip);
	mtd->dev.parent = cdns_ctrl->dev;

	/*
	 * Default to HW ECC engine mode. If the nand-ecc-mode property is given
	 * in the DT node, this entry will be overwritten in nand_scan_ident().
	 */
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_HOST;

	ret = nand_scan(chip, cdns_chip->nsels);
	अगर (ret) अणु
		dev_err(cdns_ctrl->dev, "could not scan the nand chip\n");
		वापस ret;
	पूर्ण

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret) अणु
		dev_err(cdns_ctrl->dev,
			"failed to register mtd device: %d\n", ret);
		nand_cleanup(chip);
		वापस ret;
	पूर्ण

	list_add_tail(&cdns_chip->node, &cdns_ctrl->chips);

	वापस 0;
पूर्ण

अटल व्योम cadence_nand_chips_cleanup(काष्ठा cdns_nand_ctrl *cdns_ctrl)
अणु
	काष्ठा cdns_nand_chip *entry, *temp;
	काष्ठा nand_chip *chip;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(entry, temp, &cdns_ctrl->chips, node) अणु
		chip = &entry->chip;
		ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
		WARN_ON(ret);
		nand_cleanup(chip);
		list_del(&entry->node);
	पूर्ण
पूर्ण

अटल पूर्णांक cadence_nand_chips_init(काष्ठा cdns_nand_ctrl *cdns_ctrl)
अणु
	काष्ठा device_node *np = cdns_ctrl->dev->of_node;
	काष्ठा device_node *nand_np;
	पूर्णांक max_cs = cdns_ctrl->caps2.max_banks;
	पूर्णांक nchips, ret;

	nchips = of_get_child_count(np);

	अगर (nchips > max_cs) अणु
		dev_err(cdns_ctrl->dev,
			"too many NAND chips: %d (max = %d CS)\n",
			nchips, max_cs);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_child_of_node(np, nand_np) अणु
		ret = cadence_nand_chip_init(cdns_ctrl, nand_np);
		अगर (ret) अणु
			of_node_put(nand_np);
			cadence_nand_chips_cleanup(cdns_ctrl);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
cadence_nand_irq_cleanup(पूर्णांक irqnum, काष्ठा cdns_nand_ctrl *cdns_ctrl)
अणु
	/* Disable पूर्णांकerrupts. */
	ग_लिखोl_relaxed(INTR_ENABLE_INTR_EN, cdns_ctrl->reg + INTR_ENABLE);
पूर्ण

अटल पूर्णांक cadence_nand_init(काष्ठा cdns_nand_ctrl *cdns_ctrl)
अणु
	dma_cap_mask_t mask;
	पूर्णांक ret;

	cdns_ctrl->cdma_desc = dma_alloc_coherent(cdns_ctrl->dev,
						  माप(*cdns_ctrl->cdma_desc),
						  &cdns_ctrl->dma_cdma_desc,
						  GFP_KERNEL);
	अगर (!cdns_ctrl->dma_cdma_desc)
		वापस -ENOMEM;

	cdns_ctrl->buf_size = SZ_16K;
	cdns_ctrl->buf = kदो_स्मृति(cdns_ctrl->buf_size, GFP_KERNEL);
	अगर (!cdns_ctrl->buf) अणु
		ret = -ENOMEM;
		जाओ मुक्त_buf_desc;
	पूर्ण

	अगर (devm_request_irq(cdns_ctrl->dev, cdns_ctrl->irq, cadence_nand_isr,
			     IRQF_SHARED, "cadence-nand-controller",
			     cdns_ctrl)) अणु
		dev_err(cdns_ctrl->dev, "Unable to allocate IRQ\n");
		ret = -ENODEV;
		जाओ मुक्त_buf;
	पूर्ण

	spin_lock_init(&cdns_ctrl->irq_lock);
	init_completion(&cdns_ctrl->complete);

	ret = cadence_nand_hw_init(cdns_ctrl);
	अगर (ret)
		जाओ disable_irq;

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	अगर (cdns_ctrl->caps1->has_dma) अणु
		cdns_ctrl->dmac = dma_request_channel(mask, शून्य, शून्य);
		अगर (!cdns_ctrl->dmac) अणु
			dev_err(cdns_ctrl->dev,
				"Unable to get a DMA channel\n");
			ret = -EBUSY;
			जाओ disable_irq;
		पूर्ण
	पूर्ण

	nand_controller_init(&cdns_ctrl->controller);
	INIT_LIST_HEAD(&cdns_ctrl->chips);

	cdns_ctrl->controller.ops = &cadence_nand_controller_ops;
	cdns_ctrl->curr_corr_str_idx = 0xFF;

	ret = cadence_nand_chips_init(cdns_ctrl);
	अगर (ret) अणु
		dev_err(cdns_ctrl->dev, "Failed to register MTD: %d\n",
			ret);
		जाओ dma_release_chnl;
	पूर्ण

	kमुक्त(cdns_ctrl->buf);
	cdns_ctrl->buf = kzalloc(cdns_ctrl->buf_size, GFP_KERNEL);
	अगर (!cdns_ctrl->buf) अणु
		ret = -ENOMEM;
		जाओ dma_release_chnl;
	पूर्ण

	वापस 0;

dma_release_chnl:
	अगर (cdns_ctrl->dmac)
		dma_release_channel(cdns_ctrl->dmac);

disable_irq:
	cadence_nand_irq_cleanup(cdns_ctrl->irq, cdns_ctrl);

मुक्त_buf:
	kमुक्त(cdns_ctrl->buf);

मुक्त_buf_desc:
	dma_मुक्त_coherent(cdns_ctrl->dev, माप(काष्ठा cadence_nand_cdma_desc),
			  cdns_ctrl->cdma_desc, cdns_ctrl->dma_cdma_desc);

	वापस ret;
पूर्ण

/* Driver निकास poपूर्णांक. */
अटल व्योम cadence_nand_हटाओ(काष्ठा cdns_nand_ctrl *cdns_ctrl)
अणु
	cadence_nand_chips_cleanup(cdns_ctrl);
	cadence_nand_irq_cleanup(cdns_ctrl->irq, cdns_ctrl);
	kमुक्त(cdns_ctrl->buf);
	dma_मुक्त_coherent(cdns_ctrl->dev, माप(काष्ठा cadence_nand_cdma_desc),
			  cdns_ctrl->cdma_desc, cdns_ctrl->dma_cdma_desc);

	अगर (cdns_ctrl->dmac)
		dma_release_channel(cdns_ctrl->dmac);
पूर्ण

काष्ठा cadence_nand_dt अणु
	काष्ठा cdns_nand_ctrl cdns_ctrl;
	काष्ठा clk *clk;
पूर्ण;

अटल स्थिर काष्ठा cadence_nand_dt_devdata cadence_nand_शेष = अणु
	.अगर_skew = 0,
	.has_dma = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cadence_nand_dt_ids[] = अणु
	अणु
		.compatible = "cdns,hp-nfc",
		.data = &cadence_nand_शेष
	पूर्ण, अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, cadence_nand_dt_ids);

अटल पूर्णांक cadence_nand_dt_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा resource *res;
	काष्ठा cadence_nand_dt *dt;
	काष्ठा cdns_nand_ctrl *cdns_ctrl;
	पूर्णांक ret;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा cadence_nand_dt_devdata *devdata;
	u32 val;

	of_id = of_match_device(cadence_nand_dt_ids, &ofdev->dev);
	अगर (of_id) अणु
		ofdev->id_entry = of_id->data;
		devdata = of_id->data;
	पूर्ण अन्यथा अणु
		pr_err("Failed to find the right device id.\n");
		वापस -ENOMEM;
	पूर्ण

	dt = devm_kzalloc(&ofdev->dev, माप(*dt), GFP_KERNEL);
	अगर (!dt)
		वापस -ENOMEM;

	cdns_ctrl = &dt->cdns_ctrl;
	cdns_ctrl->caps1 = devdata;

	cdns_ctrl->dev = &ofdev->dev;
	cdns_ctrl->irq = platक्रमm_get_irq(ofdev, 0);
	अगर (cdns_ctrl->irq < 0)
		वापस cdns_ctrl->irq;

	dev_info(cdns_ctrl->dev, "IRQ: nr %d\n", cdns_ctrl->irq);

	cdns_ctrl->reg = devm_platक्रमm_ioremap_resource(ofdev, 0);
	अगर (IS_ERR(cdns_ctrl->reg))
		वापस PTR_ERR(cdns_ctrl->reg);

	res = platक्रमm_get_resource(ofdev, IORESOURCE_MEM, 1);
	cdns_ctrl->io.dma = res->start;
	cdns_ctrl->io.virt = devm_ioremap_resource(&ofdev->dev, res);
	अगर (IS_ERR(cdns_ctrl->io.virt))
		वापस PTR_ERR(cdns_ctrl->io.virt);

	dt->clk = devm_clk_get(cdns_ctrl->dev, "nf_clk");
	अगर (IS_ERR(dt->clk))
		वापस PTR_ERR(dt->clk);

	cdns_ctrl->nf_clk_rate = clk_get_rate(dt->clk);

	ret = of_property_पढ़ो_u32(ofdev->dev.of_node,
				   "cdns,board-delay-ps", &val);
	अगर (ret) अणु
		val = 4830;
		dev_info(cdns_ctrl->dev,
			 "missing cdns,board-delay-ps property, %d was set\n",
			 val);
	पूर्ण
	cdns_ctrl->board_delay = val;

	ret = cadence_nand_init(cdns_ctrl);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(ofdev, dt);
	वापस 0;
पूर्ण

अटल पूर्णांक cadence_nand_dt_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा cadence_nand_dt *dt = platक्रमm_get_drvdata(ofdev);

	cadence_nand_हटाओ(&dt->cdns_ctrl);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cadence_nand_dt_driver = अणु
	.probe		= cadence_nand_dt_probe,
	.हटाओ		= cadence_nand_dt_हटाओ,
	.driver		= अणु
		.name	= "cadence-nand-controller",
		.of_match_table = cadence_nand_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cadence_nand_dt_driver);

MODULE_AUTHOR("Piotr Sroka <piotrs@cadence.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Driver for Cadence NAND flash controller");

