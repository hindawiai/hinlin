<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * न_अंकD Flash Controller Device Driver
 * Copyright (c) 2009 - 2010, Intel Corporation and its suppliers.
 */

#अगर_अघोषित __DENALI_H__
#घोषणा __DENALI_H__

#समावेश <linux/bits.h>
#समावेश <linux/completion.h>
#समावेश <linux/list.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/types.h>

#घोषणा DEVICE_RESET				0x0
#घोषणा     DEVICE_RESET__BANK(bank)			BIT(bank)

#घोषणा TRANSFER_SPARE_REG			0x10
#घोषणा     TRANSFER_SPARE_REG__FLAG			BIT(0)

#घोषणा LOAD_WAIT_CNT				0x20
#घोषणा     LOAD_WAIT_CNT__VALUE			GENMASK(15, 0)

#घोषणा PROGRAM_WAIT_CNT			0x30
#घोषणा     PROGRAM_WAIT_CNT__VALUE			GENMASK(15, 0)

#घोषणा ERASE_WAIT_CNT				0x40
#घोषणा     ERASE_WAIT_CNT__VALUE			GENMASK(15, 0)

#घोषणा INT_MON_CYCCNT				0x50
#घोषणा     INT_MON_CYCCNT__VALUE			GENMASK(15, 0)

#घोषणा RB_PIN_ENABLED				0x60
#घोषणा     RB_PIN_ENABLED__BANK(bank)			BIT(bank)

#घोषणा MULTIPLANE_OPERATION			0x70
#घोषणा     MULTIPLANE_OPERATION__FLAG			BIT(0)

#घोषणा MULTIPLANE_READ_ENABLE			0x80
#घोषणा     MULTIPLANE_READ_ENABLE__FLAG		BIT(0)

#घोषणा COPYBACK_DISABLE			0x90
#घोषणा     COPYBACK_DISABLE__FLAG			BIT(0)

#घोषणा CACHE_WRITE_ENABLE			0xa0
#घोषणा     CACHE_WRITE_ENABLE__FLAG			BIT(0)

#घोषणा CACHE_READ_ENABLE			0xb0
#घोषणा     CACHE_READ_ENABLE__FLAG			BIT(0)

#घोषणा PREFETCH_MODE				0xc0
#घोषणा     PREFETCH_MODE__PREFETCH_EN			BIT(0)
#घोषणा     PREFETCH_MODE__PREFETCH_BURST_LENGTH	GENMASK(15, 4)

#घोषणा CHIP_ENABLE_DONT_CARE			0xd0
#घोषणा     CHIP_EN_DONT_CARE__FLAG			BIT(0)

#घोषणा ECC_ENABLE				0xe0
#घोषणा     ECC_ENABLE__FLAG				BIT(0)

#घोषणा GLOBAL_INT_ENABLE			0xf0
#घोषणा     GLOBAL_INT_EN_FLAG				BIT(0)

#घोषणा TWHR2_AND_WE_2_RE			0x100
#घोषणा     TWHR2_AND_WE_2_RE__WE_2_RE			GENMASK(5, 0)
#घोषणा     TWHR2_AND_WE_2_RE__TWHR2			GENMASK(13, 8)

#घोषणा TCWAW_AND_ADDR_2_DATA			0x110
/* The width of ADDR_2_DATA is 6 bit क्रम old IP, 7 bit क्रम new IP */
#घोषणा     TCWAW_AND_ADDR_2_DATA__ADDR_2_DATA		GENMASK(6, 0)
#घोषणा     TCWAW_AND_ADDR_2_DATA__TCWAW		GENMASK(13, 8)

#घोषणा RE_2_WE					0x120
#घोषणा     RE_2_WE__VALUE				GENMASK(5, 0)

#घोषणा ACC_CLKS				0x130
#घोषणा     ACC_CLKS__VALUE				GENMASK(3, 0)

#घोषणा NUMBER_OF_PLANES			0x140
#घोषणा     NUMBER_OF_PLANES__VALUE			GENMASK(2, 0)

#घोषणा PAGES_PER_BLOCK				0x150
#घोषणा     PAGES_PER_BLOCK__VALUE			GENMASK(15, 0)

#घोषणा DEVICE_WIDTH				0x160
#घोषणा     DEVICE_WIDTH__VALUE				GENMASK(1, 0)

#घोषणा DEVICE_MAIN_AREA_SIZE			0x170
#घोषणा     DEVICE_MAIN_AREA_SIZE__VALUE		GENMASK(15, 0)

#घोषणा DEVICE_SPARE_AREA_SIZE			0x180
#घोषणा     DEVICE_SPARE_AREA_SIZE__VALUE		GENMASK(15, 0)

#घोषणा TWO_ROW_ADDR_CYCLES			0x190
#घोषणा     TWO_ROW_ADDR_CYCLES__FLAG			BIT(0)

#घोषणा MULTIPLANE_ADDR_RESTRICT		0x1a0
#घोषणा     MULTIPLANE_ADDR_RESTRICT__FLAG		BIT(0)

#घोषणा ECC_CORRECTION				0x1b0
#घोषणा     ECC_CORRECTION__VALUE			GENMASK(4, 0)
#घोषणा     ECC_CORRECTION__ERASE_THRESHOLD		GENMASK(31, 16)

#घोषणा READ_MODE				0x1c0
#घोषणा     READ_MODE__VALUE				GENMASK(3, 0)

#घोषणा WRITE_MODE				0x1d0
#घोषणा     WRITE_MODE__VALUE				GENMASK(3, 0)

#घोषणा COPYBACK_MODE				0x1e0
#घोषणा     COPYBACK_MODE__VALUE			GENMASK(3, 0)

#घोषणा RDWR_EN_LO_CNT				0x1f0
#घोषणा     RDWR_EN_LO_CNT__VALUE			GENMASK(4, 0)

#घोषणा RDWR_EN_HI_CNT				0x200
#घोषणा     RDWR_EN_HI_CNT__VALUE			GENMASK(4, 0)

#घोषणा MAX_RD_DELAY				0x210
#घोषणा     MAX_RD_DELAY__VALUE				GENMASK(3, 0)

#घोषणा CS_SETUP_CNT				0x220
#घोषणा     CS_SETUP_CNT__VALUE				GENMASK(4, 0)
#घोषणा     CS_SETUP_CNT__TWB				GENMASK(17, 12)

#घोषणा SPARE_AREA_SKIP_BYTES			0x230
#घोषणा     SPARE_AREA_SKIP_BYTES__VALUE		GENMASK(5, 0)

#घोषणा SPARE_AREA_MARKER			0x240
#घोषणा     SPARE_AREA_MARKER__VALUE			GENMASK(15, 0)

#घोषणा DEVICES_CONNECTED			0x250
#घोषणा     DEVICES_CONNECTED__VALUE			GENMASK(2, 0)

#घोषणा DIE_MASK				0x260
#घोषणा     DIE_MASK__VALUE				GENMASK(7, 0)

#घोषणा FIRST_BLOCK_OF_NEXT_PLANE		0x270
#घोषणा     FIRST_BLOCK_OF_NEXT_PLANE__VALUE		GENMASK(15, 0)

#घोषणा WRITE_PROTECT				0x280
#घोषणा     WRITE_PROTECT__FLAG				BIT(0)

#घोषणा RE_2_RE					0x290
#घोषणा     RE_2_RE__VALUE				GENMASK(5, 0)

#घोषणा MANUFACTURER_ID				0x300
#घोषणा     MANUFACTURER_ID__VALUE			GENMASK(7, 0)

#घोषणा DEVICE_ID				0x310
#घोषणा     DEVICE_ID__VALUE				GENMASK(7, 0)

#घोषणा DEVICE_PARAM_0				0x320
#घोषणा     DEVICE_PARAM_0__VALUE			GENMASK(7, 0)

#घोषणा DEVICE_PARAM_1				0x330
#घोषणा     DEVICE_PARAM_1__VALUE			GENMASK(7, 0)

#घोषणा DEVICE_PARAM_2				0x340
#घोषणा     DEVICE_PARAM_2__VALUE			GENMASK(7, 0)

#घोषणा LOGICAL_PAGE_DATA_SIZE			0x350
#घोषणा     LOGICAL_PAGE_DATA_SIZE__VALUE		GENMASK(15, 0)

#घोषणा LOGICAL_PAGE_SPARE_SIZE			0x360
#घोषणा     LOGICAL_PAGE_SPARE_SIZE__VALUE		GENMASK(15, 0)

#घोषणा REVISION				0x370
#घोषणा     REVISION__VALUE				GENMASK(15, 0)

#घोषणा ONFI_DEVICE_FEATURES			0x380
#घोषणा     ONFI_DEVICE_FEATURES__VALUE			GENMASK(5, 0)

#घोषणा ONFI_OPTIONAL_COMMANDS			0x390
#घोषणा     ONFI_OPTIONAL_COMMANDS__VALUE		GENMASK(5, 0)

#घोषणा ONFI_TIMING_MODE			0x3a0
#घोषणा     ONFI_TIMING_MODE__VALUE			GENMASK(5, 0)

#घोषणा ONFI_PGM_CACHE_TIMING_MODE		0x3b0
#घोषणा     ONFI_PGM_CACHE_TIMING_MODE__VALUE		GENMASK(5, 0)

#घोषणा ONFI_DEVICE_NO_OF_LUNS			0x3c0
#घोषणा     ONFI_DEVICE_NO_OF_LUNS__NO_OF_LUNS		GENMASK(7, 0)
#घोषणा     ONFI_DEVICE_NO_OF_LUNS__ONFI_DEVICE		BIT(8)

#घोषणा ONFI_DEVICE_NO_OF_BLOCKS_PER_LUN_L	0x3d0
#घोषणा     ONFI_DEVICE_NO_OF_BLOCKS_PER_LUN_L__VALUE	GENMASK(15, 0)

#घोषणा ONFI_DEVICE_NO_OF_BLOCKS_PER_LUN_U	0x3e0
#घोषणा     ONFI_DEVICE_NO_OF_BLOCKS_PER_LUN_U__VALUE	GENMASK(15, 0)

#घोषणा FEATURES				0x3f0
#घोषणा     FEATURES__N_BANKS				GENMASK(1, 0)
#घोषणा     FEATURES__ECC_MAX_ERR			GENMASK(5, 2)
#घोषणा     FEATURES__DMA				BIT(6)
#घोषणा     FEATURES__CMD_DMA				BIT(7)
#घोषणा     FEATURES__PARTITION				BIT(8)
#घोषणा     FEATURES__XDMA_SIDEBAND			BIT(9)
#घोषणा     FEATURES__GPREG				BIT(10)
#घोषणा     FEATURES__INDEX_ADDR			BIT(11)

#घोषणा TRANSFER_MODE				0x400
#घोषणा     TRANSFER_MODE__VALUE			GENMASK(1, 0)

#घोषणा INTR_STATUS(bank)			(0x410 + (bank) * 0x50)
#घोषणा INTR_EN(bank)				(0x420 + (bank) * 0x50)
/* bit[1:0] is used dअगरferently depending on IP version */
#घोषणा     INTR__ECC_UNCOR_ERR				BIT(0)	/* new IP */
#घोषणा     INTR__ECC_TRANSACTION_DONE			BIT(0)	/* old IP */
#घोषणा     INTR__ECC_ERR				BIT(1)	/* old IP */
#घोषणा     INTR__DMA_CMD_COMP				BIT(2)
#घोषणा     INTR__TIME_OUT				BIT(3)
#घोषणा     INTR__PROGRAM_FAIL				BIT(4)
#घोषणा     INTR__ERASE_FAIL				BIT(5)
#घोषणा     INTR__LOAD_COMP				BIT(6)
#घोषणा     INTR__PROGRAM_COMP				BIT(7)
#घोषणा     INTR__ERASE_COMP				BIT(8)
#घोषणा     INTR__PIPE_CPYBCK_CMD_COMP			BIT(9)
#घोषणा     INTR__LOCKED_BLK				BIT(10)
#घोषणा     INTR__UNSUP_CMD				BIT(11)
#घोषणा     INTR__INT_ACT				BIT(12)
#घोषणा     INTR__RST_COMP				BIT(13)
#घोषणा     INTR__PIPE_CMD_ERR				BIT(14)
#घोषणा     INTR__PAGE_XFER_INC				BIT(15)
#घोषणा     INTR__ERASED_PAGE				BIT(16)

#घोषणा PAGE_CNT(bank)				(0x430 + (bank) * 0x50)
#घोषणा ERR_PAGE_ADDR(bank)			(0x440 + (bank) * 0x50)
#घोषणा ERR_BLOCK_ADDR(bank)			(0x450 + (bank) * 0x50)

#घोषणा ECC_THRESHOLD				0x600
#घोषणा     ECC_THRESHOLD__VALUE			GENMASK(9, 0)

#घोषणा ECC_ERROR_BLOCK_ADDRESS			0x610
#घोषणा     ECC_ERROR_BLOCK_ADDRESS__VALUE		GENMASK(15, 0)

#घोषणा ECC_ERROR_PAGE_ADDRESS			0x620
#घोषणा     ECC_ERROR_PAGE_ADDRESS__VALUE		GENMASK(11, 0)
#घोषणा     ECC_ERROR_PAGE_ADDRESS__BANK		GENMASK(15, 12)

#घोषणा ECC_ERROR_ADDRESS			0x630
#घोषणा     ECC_ERROR_ADDRESS__OFFSET			GENMASK(11, 0)
#घोषणा     ECC_ERROR_ADDRESS__SECTOR			GENMASK(15, 12)

#घोषणा ERR_CORRECTION_INFO			0x640
#घोषणा     ERR_CORRECTION_INFO__BYTE			GENMASK(7, 0)
#घोषणा     ERR_CORRECTION_INFO__DEVICE			GENMASK(11, 8)
#घोषणा     ERR_CORRECTION_INFO__UNCOR			BIT(14)
#घोषणा     ERR_CORRECTION_INFO__LAST_ERR		BIT(15)

#घोषणा ECC_COR_INFO(bank)			(0x650 + (bank) / 2 * 0x10)
#घोषणा     ECC_COR_INFO__SHIFT(bank)			((bank) % 2 * 8)
#घोषणा     ECC_COR_INFO__MAX_ERRORS			GENMASK(6, 0)
#घोषणा     ECC_COR_INFO__UNCOR_ERR			BIT(7)

#घोषणा CFG_DATA_BLOCK_SIZE			0x6b0

#घोषणा CFG_LAST_DATA_BLOCK_SIZE		0x6c0

#घोषणा CFG_NUM_DATA_BLOCKS			0x6d0

#घोषणा CFG_META_DATA_SIZE			0x6e0

#घोषणा DMA_ENABLE				0x700
#घोषणा     DMA_ENABLE__FLAG				BIT(0)

#घोषणा IGNORE_ECC_DONE				0x710
#घोषणा     IGNORE_ECC_DONE__FLAG			BIT(0)

#घोषणा DMA_INTR				0x720
#घोषणा DMA_INTR_EN				0x730
#घोषणा     DMA_INTR__TARGET_ERROR			BIT(0)
#घोषणा     DMA_INTR__DESC_COMP_CHANNEL0		BIT(1)
#घोषणा     DMA_INTR__DESC_COMP_CHANNEL1		BIT(2)
#घोषणा     DMA_INTR__DESC_COMP_CHANNEL2		BIT(3)
#घोषणा     DMA_INTR__DESC_COMP_CHANNEL3		BIT(4)
#घोषणा     DMA_INTR__MEMCOPY_DESC_COMP			BIT(5)

#घोषणा TARGET_ERR_ADDR_LO			0x740
#घोषणा     TARGET_ERR_ADDR_LO__VALUE			GENMASK(15, 0)

#घोषणा TARGET_ERR_ADDR_HI			0x750
#घोषणा     TARGET_ERR_ADDR_HI__VALUE			GENMASK(15, 0)

#घोषणा CHNL_ACTIVE				0x760
#घोषणा     CHNL_ACTIVE__CHANNEL0			BIT(0)
#घोषणा     CHNL_ACTIVE__CHANNEL1			BIT(1)
#घोषणा     CHNL_ACTIVE__CHANNEL2			BIT(2)
#घोषणा     CHNL_ACTIVE__CHANNEL3			BIT(3)

/**
 * काष्ठा denali_chip_sel - per-CS data of Denali न_अंकD
 *
 * @bank:                  bank id of the controller this CS is connected to
 * @hwhr2_and_we_2_re:     value of timing रेजिस्टर HWHR2_AND_WE_2_RE
 * @tcwaw_and_addr_2_data: value of timing रेजिस्टर TCWAW_AND_ADDR_2_DATA
 * @re_2_we:               value of timing रेजिस्टर RE_2_WE
 * @acc_clks:              value of timing रेजिस्टर ACC_CLKS
 * @rdwr_en_lo_cnt:        value of timing रेजिस्टर RDWR_EN_LO_CNT
 * @rdwr_en_hi_cnt:        value of timing रेजिस्टर RDWR_EN_HI_CNT
 * @cs_setup_cnt:          value of timing रेजिस्टर CS_SETUP_CNT
 * @re_2_re:               value of timing रेजिस्टर RE_2_RE
 */
काष्ठा denali_chip_sel अणु
	पूर्णांक bank;
	u32 hwhr2_and_we_2_re;
	u32 tcwaw_and_addr_2_data;
	u32 re_2_we;
	u32 acc_clks;
	u32 rdwr_en_lo_cnt;
	u32 rdwr_en_hi_cnt;
	u32 cs_setup_cnt;
	u32 re_2_re;
पूर्ण;

/**
 * काष्ठा denali_chip - per-chip data of Denali न_अंकD
 *
 * @chip:  base न_अंकD chip काष्ठाure
 * @node:  node to be used to associate this chip with the controller
 * @nsels: the number of CS lines of this chip
 * @sels:  the array of per-cs data
 */
काष्ठा denali_chip अणु
	काष्ठा nand_chip chip;
	काष्ठा list_head node;
	अचिन्हित पूर्णांक nsels;
	काष्ठा denali_chip_sel sels[];
पूर्ण;

/**
 * काष्ठा denali_controller - Denali न_अंकD controller data
 *
 * @controller:     base न_अंकD controller काष्ठाure
 * @dev:            device
 * @chips:          the list of chips attached to this controller
 * @clk_rate:       frequency of core घड़ी
 * @clk_x_rate:     frequency of bus पूर्णांकerface घड़ी
 * @reg:            base of Register Interface
 * @host:           base of Host Data/Command पूर्णांकerface
 * @complete:       completion used to रुको क्रम पूर्णांकerrupts
 * @irq:            पूर्णांकerrupt number
 * @irq_mask:       पूर्णांकerrupt bits the controller is रुकोing क्रम
 * @irq_status:     पूर्णांकerrupt bits of events that have happened
 * @irq_lock:       lock to protect @irq_mask and @irq_status
 * @dma_avail:      set अगर DMA engine is available
 * @devs_per_cs:    number of devices connected in parallel
 * @oob_skip_bytes: number of bytes in OOB skipped by the ECC engine
 * @active_bank:    active bank id
 * @nbanks:         the number of banks supported by this controller
 * @revision:       IP revision
 * @caps:           controller capabilities that cannot be detected run-समय
 * @ecc_caps:       ECC engine capabilities
 * @host_पढ़ो:      callback क्रम पढ़ो access of Host Data/Command Interface
 * @host_ग_लिखो:     callback क्रम ग_लिखो access of Host Data/Command Interface
 * @setup_dma:      callback क्रम setup of the Data DMA
 */
काष्ठा denali_controller अणु
	काष्ठा nand_controller controller;
	काष्ठा device *dev;
	काष्ठा list_head chips;
	अचिन्हित दीर्घ clk_rate;
	अचिन्हित दीर्घ clk_x_rate;
	व्योम __iomem *reg;
	व्योम __iomem *host;
	काष्ठा completion complete;
	पूर्णांक irq;
	u32 irq_mask;
	u32 irq_status;
	spinlock_t irq_lock;
	bool dma_avail;
	पूर्णांक devs_per_cs;
	पूर्णांक oob_skip_bytes;
	पूर्णांक active_bank;
	पूर्णांक nbanks;
	अचिन्हित पूर्णांक revision;
	अचिन्हित पूर्णांक caps;
	स्थिर काष्ठा nand_ecc_caps *ecc_caps;
	u32 (*host_पढ़ो)(काष्ठा denali_controller *denali, u32 addr);
	व्योम (*host_ग_लिखो)(काष्ठा denali_controller *denali, u32 addr,
			   u32 data);
	व्योम (*setup_dma)(काष्ठा denali_controller *denali, dma_addr_t dma_addr,
			  पूर्णांक page, bool ग_लिखो);
पूर्ण;

#घोषणा DENALI_CAP_HW_ECC_FIXUP			BIT(0)
#घोषणा DENALI_CAP_DMA_64BIT			BIT(1)

पूर्णांक denali_calc_ecc_bytes(पूर्णांक step_size, पूर्णांक strength);
पूर्णांक denali_chip_init(काष्ठा denali_controller *denali,
		     काष्ठा denali_chip *dchip);
पूर्णांक denali_init(काष्ठा denali_controller *denali);
व्योम denali_हटाओ(काष्ठा denali_controller *denali);

#पूर्ण_अगर /* __DENALI_H__ */
