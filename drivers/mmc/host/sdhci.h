<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/mmc/host/sdhci.h - Secure Digital Host Controller Interface driver
 *
 * Header file क्रम Host Controller रेजिस्टरs and I/O accessors.
 *
 *  Copyright (C) 2005-2008 Pierre Ossman, All Rights Reserved.
 */
#अगर_अघोषित __SDHCI_HW_H
#घोषणा __SDHCI_HW_H

#समावेश <linux/bits.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/leds.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/mmc/host.h>

/*
 * Controller रेजिस्टरs
 */

#घोषणा SDHCI_DMA_ADDRESS	0x00
#घोषणा SDHCI_ARGUMENT2		SDHCI_DMA_ADDRESS
#घोषणा SDHCI_32BIT_BLK_CNT	SDHCI_DMA_ADDRESS

#घोषणा SDHCI_BLOCK_SIZE	0x04
#घोषणा  SDHCI_MAKE_BLKSZ(dma, blksz) (((dma & 0x7) << 12) | (blksz & 0xFFF))

#घोषणा SDHCI_BLOCK_COUNT	0x06

#घोषणा SDHCI_ARGUMENT		0x08

#घोषणा SDHCI_TRANSFER_MODE	0x0C
#घोषणा  SDHCI_TRNS_DMA		0x01
#घोषणा  SDHCI_TRNS_BLK_CNT_EN	0x02
#घोषणा  SDHCI_TRNS_AUTO_CMD12	0x04
#घोषणा  SDHCI_TRNS_AUTO_CMD23	0x08
#घोषणा  SDHCI_TRNS_AUTO_SEL	0x0C
#घोषणा  SDHCI_TRNS_READ	0x10
#घोषणा  SDHCI_TRNS_MULTI	0x20

#घोषणा SDHCI_COMMAND		0x0E
#घोषणा  SDHCI_CMD_RESP_MASK	0x03
#घोषणा  SDHCI_CMD_CRC		0x08
#घोषणा  SDHCI_CMD_INDEX	0x10
#घोषणा  SDHCI_CMD_DATA		0x20
#घोषणा  SDHCI_CMD_ABORTCMD	0xC0

#घोषणा  SDHCI_CMD_RESP_NONE	0x00
#घोषणा  SDHCI_CMD_RESP_LONG	0x01
#घोषणा  SDHCI_CMD_RESP_SHORT	0x02
#घोषणा  SDHCI_CMD_RESP_SHORT_BUSY 0x03

#घोषणा SDHCI_MAKE_CMD(c, f) (((c & 0xff) << 8) | (f & 0xff))
#घोषणा SDHCI_GET_CMD(c) ((c>>8) & 0x3f)

#घोषणा SDHCI_RESPONSE		0x10

#घोषणा SDHCI_BUFFER		0x20

#घोषणा SDHCI_PRESENT_STATE	0x24
#घोषणा  SDHCI_CMD_INHIBIT	0x00000001
#घोषणा  SDHCI_DATA_INHIBIT	0x00000002
#घोषणा  SDHCI_DOING_WRITE	0x00000100
#घोषणा  SDHCI_DOING_READ	0x00000200
#घोषणा  SDHCI_SPACE_AVAILABLE	0x00000400
#घोषणा  SDHCI_DATA_AVAILABLE	0x00000800
#घोषणा  SDHCI_CARD_PRESENT	0x00010000
#घोषणा   SDHCI_CARD_PRES_SHIFT	16
#घोषणा  SDHCI_CD_STABLE	0x00020000
#घोषणा  SDHCI_CD_LVL		0x00040000
#घोषणा   SDHCI_CD_LVL_SHIFT	18
#घोषणा  SDHCI_WRITE_PROTECT	0x00080000
#घोषणा  SDHCI_DATA_LVL_MASK	0x00F00000
#घोषणा   SDHCI_DATA_LVL_SHIFT	20
#घोषणा   SDHCI_DATA_0_LVL_MASK	0x00100000
#घोषणा  SDHCI_CMD_LVL		0x01000000

#घोषणा SDHCI_HOST_CONTROL	0x28
#घोषणा  SDHCI_CTRL_LED		0x01
#घोषणा  SDHCI_CTRL_4BITBUS	0x02
#घोषणा  SDHCI_CTRL_HISPD	0x04
#घोषणा  SDHCI_CTRL_DMA_MASK	0x18
#घोषणा   SDHCI_CTRL_SDMA	0x00
#घोषणा   SDHCI_CTRL_ADMA1	0x08
#घोषणा   SDHCI_CTRL_ADMA32	0x10
#घोषणा   SDHCI_CTRL_ADMA64	0x18
#घोषणा   SDHCI_CTRL_ADMA3	0x18
#घोषणा  SDHCI_CTRL_8BITBUS	0x20
#घोषणा  SDHCI_CTRL_CDTEST_INS	0x40
#घोषणा  SDHCI_CTRL_CDTEST_EN	0x80

#घोषणा SDHCI_POWER_CONTROL	0x29
#घोषणा  SDHCI_POWER_ON		0x01
#घोषणा  SDHCI_POWER_180	0x0A
#घोषणा  SDHCI_POWER_300	0x0C
#घोषणा  SDHCI_POWER_330	0x0E

#घोषणा SDHCI_BLOCK_GAP_CONTROL	0x2A

#घोषणा SDHCI_WAKE_UP_CONTROL	0x2B
#घोषणा  SDHCI_WAKE_ON_INT	0x01
#घोषणा  SDHCI_WAKE_ON_INSERT	0x02
#घोषणा  SDHCI_WAKE_ON_REMOVE	0x04

#घोषणा SDHCI_CLOCK_CONTROL	0x2C
#घोषणा  SDHCI_DIVIDER_SHIFT	8
#घोषणा  SDHCI_DIVIDER_HI_SHIFT	6
#घोषणा  SDHCI_DIV_MASK	0xFF
#घोषणा  SDHCI_DIV_MASK_LEN	8
#घोषणा  SDHCI_DIV_HI_MASK	0x300
#घोषणा  SDHCI_PROG_CLOCK_MODE	0x0020
#घोषणा  SDHCI_CLOCK_CARD_EN	0x0004
#घोषणा  SDHCI_CLOCK_PLL_EN	0x0008
#घोषणा  SDHCI_CLOCK_INT_STABLE	0x0002
#घोषणा  SDHCI_CLOCK_INT_EN	0x0001

#घोषणा SDHCI_TIMEOUT_CONTROL	0x2E

#घोषणा SDHCI_SOFTWARE_RESET	0x2F
#घोषणा  SDHCI_RESET_ALL	0x01
#घोषणा  SDHCI_RESET_CMD	0x02
#घोषणा  SDHCI_RESET_DATA	0x04

#घोषणा SDHCI_INT_STATUS	0x30
#घोषणा SDHCI_INT_ENABLE	0x34
#घोषणा SDHCI_SIGNAL_ENABLE	0x38
#घोषणा  SDHCI_INT_RESPONSE	0x00000001
#घोषणा  SDHCI_INT_DATA_END	0x00000002
#घोषणा  SDHCI_INT_BLK_GAP	0x00000004
#घोषणा  SDHCI_INT_DMA_END	0x00000008
#घोषणा  SDHCI_INT_SPACE_AVAIL	0x00000010
#घोषणा  SDHCI_INT_DATA_AVAIL	0x00000020
#घोषणा  SDHCI_INT_CARD_INSERT	0x00000040
#घोषणा  SDHCI_INT_CARD_REMOVE	0x00000080
#घोषणा  SDHCI_INT_CARD_INT	0x00000100
#घोषणा  SDHCI_INT_RETUNE	0x00001000
#घोषणा  SDHCI_INT_CQE		0x00004000
#घोषणा  SDHCI_INT_ERROR	0x00008000
#घोषणा  SDHCI_INT_TIMEOUT	0x00010000
#घोषणा  SDHCI_INT_CRC		0x00020000
#घोषणा  SDHCI_INT_END_BIT	0x00040000
#घोषणा  SDHCI_INT_INDEX	0x00080000
#घोषणा  SDHCI_INT_DATA_TIMEOUT	0x00100000
#घोषणा  SDHCI_INT_DATA_CRC	0x00200000
#घोषणा  SDHCI_INT_DATA_END_BIT	0x00400000
#घोषणा  SDHCI_INT_BUS_POWER	0x00800000
#घोषणा  SDHCI_INT_AUTO_CMD_ERR	0x01000000
#घोषणा  SDHCI_INT_ADMA_ERROR	0x02000000

#घोषणा  SDHCI_INT_NORMAL_MASK	0x00007FFF
#घोषणा  SDHCI_INT_ERROR_MASK	0xFFFF8000

#घोषणा  SDHCI_INT_CMD_MASK	(SDHCI_INT_RESPONSE | SDHCI_INT_TIMEOUT | \
		SDHCI_INT_CRC | SDHCI_INT_END_BIT | SDHCI_INT_INDEX | \
		SDHCI_INT_AUTO_CMD_ERR)
#घोषणा  SDHCI_INT_DATA_MASK	(SDHCI_INT_DATA_END | SDHCI_INT_DMA_END | \
		SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL | \
		SDHCI_INT_DATA_TIMEOUT | SDHCI_INT_DATA_CRC | \
		SDHCI_INT_DATA_END_BIT | SDHCI_INT_ADMA_ERROR | \
		SDHCI_INT_BLK_GAP)
#घोषणा SDHCI_INT_ALL_MASK	((अचिन्हित पूर्णांक)-1)

#घोषणा SDHCI_CQE_INT_ERR_MASK ( \
	SDHCI_INT_ADMA_ERROR | SDHCI_INT_BUS_POWER | SDHCI_INT_DATA_END_BIT | \
	SDHCI_INT_DATA_CRC | SDHCI_INT_DATA_TIMEOUT | SDHCI_INT_INDEX | \
	SDHCI_INT_END_BIT | SDHCI_INT_CRC | SDHCI_INT_TIMEOUT)

#घोषणा SDHCI_CQE_INT_MASK (SDHCI_CQE_INT_ERR_MASK | SDHCI_INT_CQE)

#घोषणा SDHCI_AUTO_CMD_STATUS	0x3C
#घोषणा  SDHCI_AUTO_CMD_TIMEOUT	0x00000002
#घोषणा  SDHCI_AUTO_CMD_CRC	0x00000004
#घोषणा  SDHCI_AUTO_CMD_END_BIT	0x00000008
#घोषणा  SDHCI_AUTO_CMD_INDEX	0x00000010

#घोषणा SDHCI_HOST_CONTROL2		0x3E
#घोषणा  SDHCI_CTRL_UHS_MASK		0x0007
#घोषणा   SDHCI_CTRL_UHS_SDR12		0x0000
#घोषणा   SDHCI_CTRL_UHS_SDR25		0x0001
#घोषणा   SDHCI_CTRL_UHS_SDR50		0x0002
#घोषणा   SDHCI_CTRL_UHS_SDR104		0x0003
#घोषणा   SDHCI_CTRL_UHS_DDR50		0x0004
#घोषणा   SDHCI_CTRL_HS400		0x0005 /* Non-standard */
#घोषणा  SDHCI_CTRL_VDD_180		0x0008
#घोषणा  SDHCI_CTRL_DRV_TYPE_MASK	0x0030
#घोषणा   SDHCI_CTRL_DRV_TYPE_B		0x0000
#घोषणा   SDHCI_CTRL_DRV_TYPE_A		0x0010
#घोषणा   SDHCI_CTRL_DRV_TYPE_C		0x0020
#घोषणा   SDHCI_CTRL_DRV_TYPE_D		0x0030
#घोषणा  SDHCI_CTRL_EXEC_TUNING		0x0040
#घोषणा  SDHCI_CTRL_TUNED_CLK		0x0080
#घोषणा  SDHCI_CMD23_ENABLE		0x0800
#घोषणा  SDHCI_CTRL_V4_MODE		0x1000
#घोषणा  SDHCI_CTRL_64BIT_ADDR		0x2000
#घोषणा  SDHCI_CTRL_PRESET_VAL_ENABLE	0x8000

#घोषणा SDHCI_CAPABILITIES	0x40
#घोषणा  SDHCI_TIMEOUT_CLK_MASK		GENMASK(5, 0)
#घोषणा  SDHCI_TIMEOUT_CLK_UNIT	0x00000080
#घोषणा  SDHCI_CLOCK_BASE_MASK		GENMASK(13, 8)
#घोषणा  SDHCI_CLOCK_V3_BASE_MASK	GENMASK(15, 8)
#घोषणा  SDHCI_MAX_BLOCK_MASK	0x00030000
#घोषणा  SDHCI_MAX_BLOCK_SHIFT  16
#घोषणा  SDHCI_CAN_DO_8BIT	0x00040000
#घोषणा  SDHCI_CAN_DO_ADMA2	0x00080000
#घोषणा  SDHCI_CAN_DO_ADMA1	0x00100000
#घोषणा  SDHCI_CAN_DO_HISPD	0x00200000
#घोषणा  SDHCI_CAN_DO_SDMA	0x00400000
#घोषणा  SDHCI_CAN_DO_SUSPEND	0x00800000
#घोषणा  SDHCI_CAN_VDD_330	0x01000000
#घोषणा  SDHCI_CAN_VDD_300	0x02000000
#घोषणा  SDHCI_CAN_VDD_180	0x04000000
#घोषणा  SDHCI_CAN_64BIT_V4	0x08000000
#घोषणा  SDHCI_CAN_64BIT	0x10000000

#घोषणा SDHCI_CAPABILITIES_1	0x44
#घोषणा  SDHCI_SUPPORT_SDR50	0x00000001
#घोषणा  SDHCI_SUPPORT_SDR104	0x00000002
#घोषणा  SDHCI_SUPPORT_DDR50	0x00000004
#घोषणा  SDHCI_DRIVER_TYPE_A	0x00000010
#घोषणा  SDHCI_DRIVER_TYPE_C	0x00000020
#घोषणा  SDHCI_DRIVER_TYPE_D	0x00000040
#घोषणा  SDHCI_RETUNING_TIMER_COUNT_MASK	GENMASK(11, 8)
#घोषणा  SDHCI_USE_SDR50_TUNING			0x00002000
#घोषणा  SDHCI_RETUNING_MODE_MASK		GENMASK(15, 14)
#घोषणा  SDHCI_CLOCK_MUL_MASK			GENMASK(23, 16)
#घोषणा  SDHCI_CAN_DO_ADMA3	0x08000000
#घोषणा  SDHCI_SUPPORT_HS400	0x80000000 /* Non-standard */

#घोषणा SDHCI_MAX_CURRENT		0x48
#घोषणा  SDHCI_MAX_CURRENT_LIMIT	GENMASK(7, 0)
#घोषणा  SDHCI_MAX_CURRENT_330_MASK	GENMASK(7, 0)
#घोषणा  SDHCI_MAX_CURRENT_300_MASK	GENMASK(15, 8)
#घोषणा  SDHCI_MAX_CURRENT_180_MASK	GENMASK(23, 16)
#घोषणा   SDHCI_MAX_CURRENT_MULTIPLIER	4

/* 4C-4F reserved क्रम more max current */

#घोषणा SDHCI_SET_ACMD12_ERROR	0x50
#घोषणा SDHCI_SET_INT_ERROR	0x52

#घोषणा SDHCI_ADMA_ERROR	0x54

/* 55-57 reserved */

#घोषणा SDHCI_ADMA_ADDRESS	0x58
#घोषणा SDHCI_ADMA_ADDRESS_HI	0x5C

/* 60-FB reserved */

#घोषणा SDHCI_PRESET_FOR_SDR12 0x66
#घोषणा SDHCI_PRESET_FOR_SDR25 0x68
#घोषणा SDHCI_PRESET_FOR_SDR50 0x6A
#घोषणा SDHCI_PRESET_FOR_SDR104        0x6C
#घोषणा SDHCI_PRESET_FOR_DDR50 0x6E
#घोषणा SDHCI_PRESET_FOR_HS400 0x74 /* Non-standard */
#घोषणा SDHCI_PRESET_DRV_MASK		GENMASK(15, 14)
#घोषणा SDHCI_PRESET_CLKGEN_SEL		BIT(10)
#घोषणा SDHCI_PRESET_SDCLK_FREQ_MASK	GENMASK(9, 0)

#घोषणा SDHCI_SLOT_INT_STATUS	0xFC

#घोषणा SDHCI_HOST_VERSION	0xFE
#घोषणा  SDHCI_VENDOR_VER_MASK	0xFF00
#घोषणा  SDHCI_VENDOR_VER_SHIFT	8
#घोषणा  SDHCI_SPEC_VER_MASK	0x00FF
#घोषणा  SDHCI_SPEC_VER_SHIFT	0
#घोषणा   SDHCI_SPEC_100	0
#घोषणा   SDHCI_SPEC_200	1
#घोषणा   SDHCI_SPEC_300	2
#घोषणा   SDHCI_SPEC_400	3
#घोषणा   SDHCI_SPEC_410	4
#घोषणा   SDHCI_SPEC_420	5

/*
 * End of controller रेजिस्टरs.
 */

#घोषणा SDHCI_MAX_DIV_SPEC_200	256
#घोषणा SDHCI_MAX_DIV_SPEC_300	2046

/*
 * Host SDMA buffer boundary. Valid values from 4K to 512K in घातers of 2.
 */
#घोषणा SDHCI_DEFAULT_BOUNDARY_SIZE  (512 * 1024)
#घोषणा SDHCI_DEFAULT_BOUNDARY_ARG   (ilog2(SDHCI_DEFAULT_BOUNDARY_SIZE) - 12)

/* ADMA2 32-bit DMA descriptor size */
#घोषणा SDHCI_ADMA2_32_DESC_SZ	8

/* ADMA2 32-bit descriptor */
काष्ठा sdhci_adma2_32_desc अणु
	__le16	cmd;
	__le16	len;
	__le32	addr;
पूर्ण  __packed __aligned(4);

/* ADMA2 data alignment */
#घोषणा SDHCI_ADMA2_ALIGN	4
#घोषणा SDHCI_ADMA2_MASK	(SDHCI_ADMA2_ALIGN - 1)

/*
 * ADMA2 descriptor alignment.  Some controllers (e.g. Intel) require 8 byte
 * alignment क्रम the descriptor table even in 32-bit DMA mode.  Memory
 * allocation is at least 8 byte aligned anyway, so just stipulate 8 always.
 */
#घोषणा SDHCI_ADMA2_DESC_ALIGN	8

/*
 * ADMA2 64-bit DMA descriptor size
 * According to SD Host Controller spec v4.10, there are two kinds of
 * descriptors क्रम 64-bit addressing mode: 96-bit Descriptor and 128-bit
 * Descriptor, अगर Host Version 4 Enable is set in the Host Control 2
 * रेजिस्टर, 128-bit Descriptor will be selected.
 */
#घोषणा SDHCI_ADMA2_64_DESC_SZ(host)	((host)->v4_mode ? 16 : 12)

/*
 * ADMA2 64-bit descriptor. Note 12-byte descriptor can't always be 8-byte
 * aligned.
 */
काष्ठा sdhci_adma2_64_desc अणु
	__le16	cmd;
	__le16	len;
	__le32	addr_lo;
	__le32	addr_hi;
पूर्ण  __packed __aligned(4);

#घोषणा ADMA2_TRAN_VALID	0x21
#घोषणा ADMA2_NOP_END_VALID	0x3
#घोषणा ADMA2_END		0x2

/*
 * Maximum segments assuming a 512KiB maximum requisition size and a minimum
 * 4KiB page size.
 */
#घोषणा SDHCI_MAX_SEGS		128

/* Allow क्रम a a command request and a data request at the same समय */
#घोषणा SDHCI_MAX_MRQS		2

/*
 * 48bit command and 136 bit response in 100KHz घड़ी could take upto 2.48ms.
 * However since the start समय of the command, the समय between
 * command and response, and the समय between response and start of data is
 * not known, set the command transfer समय to 10ms.
 */
#घोषणा MMC_CMD_TRANSFER_TIME	(10 * NSEC_PER_MSEC) /* max 10 ms */

क्रमागत sdhci_cookie अणु
	COOKIE_UNMAPPED,
	COOKIE_PRE_MAPPED,	/* mapped by sdhci_pre_req() */
	COOKIE_MAPPED,		/* mapped by sdhci_prepare_data() */
पूर्ण;

काष्ठा sdhci_host अणु
	/* Data set by hardware पूर्णांकerface driver */
	स्थिर अक्षर *hw_name;	/* Hardware bus name */

	अचिन्हित पूर्णांक quirks;	/* Deviations from spec. */

/* Controller करोesn't honor resets unless we touch the घड़ी रेजिस्टर */
#घोषणा SDHCI_QUIRK_CLOCK_BEFORE_RESET			(1<<0)
/* Controller has bad caps bits, but really supports DMA */
#घोषणा SDHCI_QUIRK_FORCE_DMA				(1<<1)
/* Controller करोesn't like to be reset when there is no card inserted. */
#घोषणा SDHCI_QUIRK_NO_CARD_NO_RESET			(1<<2)
/* Controller करोesn't like clearing the घातer reg beक्रमe a change */
#घोषणा SDHCI_QUIRK_SINGLE_POWER_WRITE			(1<<3)
/* Controller has flaky पूर्णांकernal state so reset it on each ios change */
#घोषणा SDHCI_QUIRK_RESET_CMD_DATA_ON_IOS		(1<<4)
/* Controller has an unusable DMA engine */
#घोषणा SDHCI_QUIRK_BROKEN_DMA				(1<<5)
/* Controller has an unusable ADMA engine */
#घोषणा SDHCI_QUIRK_BROKEN_ADMA				(1<<6)
/* Controller can only DMA from 32-bit aligned addresses */
#घोषणा SDHCI_QUIRK_32BIT_DMA_ADDR			(1<<7)
/* Controller can only DMA chunk sizes that are a multiple of 32 bits */
#घोषणा SDHCI_QUIRK_32BIT_DMA_SIZE			(1<<8)
/* Controller can only ADMA chunks that are a multiple of 32 bits */
#घोषणा SDHCI_QUIRK_32BIT_ADMA_SIZE			(1<<9)
/* Controller needs to be reset after each request to stay stable */
#घोषणा SDHCI_QUIRK_RESET_AFTER_REQUEST			(1<<10)
/* Controller needs voltage and घातer ग_लिखोs to happen separately */
#घोषणा SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER		(1<<11)
/* Controller provides an incorrect समयout value क्रम transfers */
#घोषणा SDHCI_QUIRK_BROKEN_TIMEOUT_VAL			(1<<12)
/* Controller has an issue with buffer bits क्रम small transfers */
#घोषणा SDHCI_QUIRK_BROKEN_SMALL_PIO			(1<<13)
/* Controller करोes not provide transfer-complete पूर्णांकerrupt when not busy */
#घोषणा SDHCI_QUIRK_NO_BUSY_IRQ				(1<<14)
/* Controller has unreliable card detection */
#घोषणा SDHCI_QUIRK_BROKEN_CARD_DETECTION		(1<<15)
/* Controller reports inverted ग_लिखो-protect state */
#घोषणा SDHCI_QUIRK_INVERTED_WRITE_PROTECT		(1<<16)
/* Controller has unusable command queue engine */
#घोषणा SDHCI_QUIRK_BROKEN_CQE				(1<<17)
/* Controller करोes not like fast PIO transfers */
#घोषणा SDHCI_QUIRK_PIO_NEEDS_DELAY			(1<<18)
/* Controller करोes not have a LED */
#घोषणा SDHCI_QUIRK_NO_LED				(1<<19)
/* Controller has to be क्रमced to use block size of 2048 bytes */
#घोषणा SDHCI_QUIRK_FORCE_BLK_SZ_2048			(1<<20)
/* Controller cannot करो multi-block transfers */
#घोषणा SDHCI_QUIRK_NO_MULTIBLOCK			(1<<21)
/* Controller can only handle 1-bit data transfers */
#घोषणा SDHCI_QUIRK_FORCE_1_BIT_DATA			(1<<22)
/* Controller needs 10ms delay between applying घातer and घड़ी */
#घोषणा SDHCI_QUIRK_DELAY_AFTER_POWER			(1<<23)
/* Controller uses SDCLK instead of TMCLK क्रम data समयouts */
#घोषणा SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK		(1<<24)
/* Controller reports wrong base घड़ी capability */
#घोषणा SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN		(1<<25)
/* Controller cannot support End Attribute in NOP ADMA descriptor */
#घोषणा SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC		(1<<26)
/* Controller is missing device caps. Use caps provided by host */
#घोषणा SDHCI_QUIRK_MISSING_CAPS			(1<<27)
/* Controller uses Auto CMD12 command to stop the transfer */
#घोषणा SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12		(1<<28)
/* Controller करोesn't have HISPD bit field in HI-SPEED SD card */
#घोषणा SDHCI_QUIRK_NO_HISPD_BIT			(1<<29)
/* Controller treats ADMA descriptors with length 0000h incorrectly */
#घोषणा SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC		(1<<30)
/* The पढ़ो-only detection via SDHCI_PRESENT_STATE रेजिस्टर is unstable */
#घोषणा SDHCI_QUIRK_UNSTABLE_RO_DETECT			(1<<31)

	अचिन्हित पूर्णांक quirks2;	/* More deviations from spec. */

#घोषणा SDHCI_QUIRK2_HOST_OFF_CARD_ON			(1<<0)
#घोषणा SDHCI_QUIRK2_HOST_NO_CMD23			(1<<1)
/* The प्रणाली physically करोesn't support 1.8v, even अगर the host करोes */
#घोषणा SDHCI_QUIRK2_NO_1_8_V				(1<<2)
#घोषणा SDHCI_QUIRK2_PRESET_VALUE_BROKEN		(1<<3)
#घोषणा SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON		(1<<4)
/* Controller has a non-standard host control रेजिस्टर */
#घोषणा SDHCI_QUIRK2_BROKEN_HOST_CONTROL		(1<<5)
/* Controller करोes not support HS200 */
#घोषणा SDHCI_QUIRK2_BROKEN_HS200			(1<<6)
/* Controller करोes not support DDR50 */
#घोषणा SDHCI_QUIRK2_BROKEN_DDR50			(1<<7)
/* Stop command (CMD12) can set Transfer Complete when not using MMC_RSP_BUSY */
#घोषणा SDHCI_QUIRK2_STOP_WITH_TC			(1<<8)
/* Controller करोes not support 64-bit DMA */
#घोषणा SDHCI_QUIRK2_BROKEN_64_BIT_DMA			(1<<9)
/* need clear transfer mode रेजिस्टर beक्रमe send cmd */
#घोषणा SDHCI_QUIRK2_CLEAR_TRANSFERMODE_REG_BEFORE_CMD	(1<<10)
/* Capability रेजिस्टर bit-63 indicates HS400 support */
#घोषणा SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400		(1<<11)
/* क्रमced tuned घड़ी */
#घोषणा SDHCI_QUIRK2_TUNING_WORK_AROUND			(1<<12)
/* disable the block count क्रम single block transactions */
#घोषणा SDHCI_QUIRK2_SUPPORT_SINGLE			(1<<13)
/* Controller broken with using ACMD23 */
#घोषणा SDHCI_QUIRK2_ACMD23_BROKEN			(1<<14)
/* Broken Clock भागider zero in controller */
#घोषणा SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN		(1<<15)
/* Controller has CRC in 136 bit Command Response */
#घोषणा SDHCI_QUIRK2_RSP_136_HAS_CRC			(1<<16)
/*
 * Disable HW समयout अगर the requested समयout is more than the maximum
 * obtainable समयout.
 */
#घोषणा SDHCI_QUIRK2_DISABLE_HW_TIMEOUT			(1<<17)
/*
 * 32-bit block count may not support eMMC where upper bits of CMD23 are used
 * क्रम other purposes.  Consequently we support 16-bit block count by शेष.
 * Otherwise, SDHCI_QUIRK2_USE_32BIT_BLK_CNT can be selected to use 32-bit
 * block count.
 */
#घोषणा SDHCI_QUIRK2_USE_32BIT_BLK_CNT			(1<<18)

	पूर्णांक irq;		/* Device IRQ */
	व्योम __iomem *ioaddr;	/* Mapped address */
	phys_addr_t mapbase;	/* physical address base */
	अक्षर *bounce_buffer;	/* For packing SDMA पढ़ोs/ग_लिखोs */
	dma_addr_t bounce_addr;
	अचिन्हित पूर्णांक bounce_buffer_size;

	स्थिर काष्ठा sdhci_ops *ops;	/* Low level hw पूर्णांकerface */

	/* Internal data */
	काष्ठा mmc_host *mmc;	/* MMC काष्ठाure */
	काष्ठा mmc_host_ops mmc_host_ops;	/* MMC host ops */
	u64 dma_mask;		/* custom DMA mask */

#अगर IS_ENABLED(CONFIG_LEDS_CLASS)
	काष्ठा led_classdev led;	/* LED control */
	अक्षर led_name[32];
#पूर्ण_अगर

	spinlock_t lock;	/* Mutex */

	पूर्णांक flags;		/* Host attributes */
#घोषणा SDHCI_USE_SDMA		(1<<0)	/* Host is SDMA capable */
#घोषणा SDHCI_USE_ADMA		(1<<1)	/* Host is ADMA capable */
#घोषणा SDHCI_REQ_USE_DMA	(1<<2)	/* Use DMA क्रम this req. */
#घोषणा SDHCI_DEVICE_DEAD	(1<<3)	/* Device unresponsive */
#घोषणा SDHCI_SDR50_NEEDS_TUNING (1<<4)	/* SDR50 needs tuning */
#घोषणा SDHCI_AUTO_CMD12	(1<<6)	/* Auto CMD12 support */
#घोषणा SDHCI_AUTO_CMD23	(1<<7)	/* Auto CMD23 support */
#घोषणा SDHCI_PV_ENABLED	(1<<8)	/* Preset value enabled */
#घोषणा SDHCI_USE_64_BIT_DMA	(1<<12)	/* Use 64-bit DMA */
#घोषणा SDHCI_HS400_TUNING	(1<<13)	/* Tuning क्रम HS400 */
#घोषणा SDHCI_SIGNALING_330	(1<<14)	/* Host is capable of 3.3V संकेतing */
#घोषणा SDHCI_SIGNALING_180	(1<<15)	/* Host is capable of 1.8V संकेतing */
#घोषणा SDHCI_SIGNALING_120	(1<<16)	/* Host is capable of 1.2V संकेतing */

	अचिन्हित पूर्णांक version;	/* SDHCI spec. version */

	अचिन्हित पूर्णांक max_clk;	/* Max possible freq (MHz) */
	अचिन्हित पूर्णांक समयout_clk;	/* Timeout freq (KHz) */
	अचिन्हित पूर्णांक clk_mul;	/* Clock Muliplier value */

	अचिन्हित पूर्णांक घड़ी;	/* Current घड़ी (MHz) */
	u8 pwr;			/* Current voltage */

	bool runसमय_suspended;	/* Host is runसमय suspended */
	bool bus_on;		/* Bus घातer prevents runसमय suspend */
	bool preset_enabled;	/* Preset is enabled */
	bool pending_reset;	/* Cmd/data reset is pending */
	bool irq_wake_enabled;	/* IRQ wakeup is enabled */
	bool v4_mode;		/* Host Version 4 Enable */
	bool use_बाह्यal_dma;	/* Host selects to use बाह्यal DMA */
	bool always_defer_करोne;	/* Always defer to complete requests */

	काष्ठा mmc_request *mrqs_करोne[SDHCI_MAX_MRQS];	/* Requests करोne */
	काष्ठा mmc_command *cmd;	/* Current command */
	काष्ठा mmc_command *data_cmd;	/* Current data command */
	काष्ठा mmc_command *deferred_cmd;	/* Deferred command */
	काष्ठा mmc_data *data;	/* Current data request */
	अचिन्हित पूर्णांक data_early:1;	/* Data finished beक्रमe cmd */

	काष्ठा sg_mapping_iter sg_miter;	/* SG state क्रम PIO */
	अचिन्हित पूर्णांक blocks;	/* reमुख्यing PIO blocks */

	पूर्णांक sg_count;		/* Mapped sg entries */

	व्योम *adma_table;	/* ADMA descriptor table */
	व्योम *align_buffer;	/* Bounce buffer */

	माप_प्रकार adma_table_sz;	/* ADMA descriptor table size */
	माप_प्रकार align_buffer_sz;	/* Bounce buffer size */

	dma_addr_t adma_addr;	/* Mapped ADMA descr. table */
	dma_addr_t align_addr;	/* Mapped bounce buffer */

	अचिन्हित पूर्णांक desc_sz;	/* ADMA current descriptor size */
	अचिन्हित पूर्णांक alloc_desc_sz;	/* ADMA descr. max size host supports */

	काष्ठा workqueue_काष्ठा *complete_wq;	/* Request completion wq */
	काष्ठा work_काष्ठा	complete_work;	/* Request completion work */

	काष्ठा समयr_list समयr;	/* Timer क्रम समयouts */
	काष्ठा समयr_list data_समयr;	/* Timer क्रम data समयouts */

#अगर IS_ENABLED(CONFIG_MMC_SDHCI_EXTERNAL_DMA)
	काष्ठा dma_chan *rx_chan;
	काष्ठा dma_chan *tx_chan;
#पूर्ण_अगर

	u32 caps;		/* CAPABILITY_0 */
	u32 caps1;		/* CAPABILITY_1 */
	bool पढ़ो_caps;		/* Capability flags have been पढ़ो */

	bool sdhci_core_to_disable_vqmmc;  /* sdhci core can disable vqmmc */
	अचिन्हित पूर्णांक            ocr_avail_sdio;	/* OCR bit masks */
	अचिन्हित पूर्णांक            ocr_avail_sd;
	अचिन्हित पूर्णांक            ocr_avail_mmc;
	u32 ocr_mask;		/* available voltages */

	अचिन्हित		timing;		/* Current timing */

	u32			thपढ़ो_isr;

	/* cached रेजिस्टरs */
	u32			ier;

	bool			cqe_on;		/* CQE is operating */
	u32			cqe_ier;	/* CQE पूर्णांकerrupt mask */
	u32			cqe_err_ier;	/* CQE error पूर्णांकerrupt mask */

	रुको_queue_head_t	buf_पढ़ोy_पूर्णांक;	/* Waitqueue क्रम Buffer Read Ready पूर्णांकerrupt */
	अचिन्हित पूर्णांक		tuning_करोne;	/* Condition flag set when CMD19 succeeds */

	अचिन्हित पूर्णांक		tuning_count;	/* Timer count क्रम re-tuning */
	अचिन्हित पूर्णांक		tuning_mode;	/* Re-tuning mode supported by host */
	अचिन्हित पूर्णांक		tuning_err;	/* Error code क्रम re-tuning */
#घोषणा SDHCI_TUNING_MODE_1	0
#घोषणा SDHCI_TUNING_MODE_2	1
#घोषणा SDHCI_TUNING_MODE_3	2
	/* Delay (ms) between tuning commands */
	पूर्णांक			tuning_delay;
	पूर्णांक			tuning_loop_count;

	/* Host SDMA buffer boundary. */
	u32			sdma_boundary;

	/* Host ADMA table count */
	u32			adma_table_cnt;

	u64			data_समयout;

	अचिन्हित दीर्घ निजी[] ____cacheline_aligned;
पूर्ण;

काष्ठा sdhci_ops अणु
#अगर_घोषित CONFIG_MMC_SDHCI_IO_ACCESSORS
	u32		(*पढ़ो_l)(काष्ठा sdhci_host *host, पूर्णांक reg);
	u16		(*पढ़ो_w)(काष्ठा sdhci_host *host, पूर्णांक reg);
	u8		(*पढ़ो_b)(काष्ठा sdhci_host *host, पूर्णांक reg);
	व्योम		(*ग_लिखो_l)(काष्ठा sdhci_host *host, u32 val, पूर्णांक reg);
	व्योम		(*ग_लिखो_w)(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg);
	व्योम		(*ग_लिखो_b)(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg);
#पूर्ण_अगर

	व्योम	(*set_घड़ी)(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी);
	व्योम	(*set_घातer)(काष्ठा sdhci_host *host, अचिन्हित अक्षर mode,
			     अचिन्हित लघु vdd);

	u32		(*irq)(काष्ठा sdhci_host *host, u32 पूर्णांकmask);

	पूर्णांक		(*set_dma_mask)(काष्ठा sdhci_host *host);
	पूर्णांक		(*enable_dma)(काष्ठा sdhci_host *host);
	अचिन्हित पूर्णांक	(*get_max_घड़ी)(काष्ठा sdhci_host *host);
	अचिन्हित पूर्णांक	(*get_min_घड़ी)(काष्ठा sdhci_host *host);
	/* get_समयout_घड़ी should वापस clk rate in unit of Hz */
	अचिन्हित पूर्णांक	(*get_समयout_घड़ी)(काष्ठा sdhci_host *host);
	अचिन्हित पूर्णांक	(*get_max_समयout_count)(काष्ठा sdhci_host *host);
	व्योम		(*set_समयout)(काष्ठा sdhci_host *host,
				       काष्ठा mmc_command *cmd);
	व्योम		(*set_bus_width)(काष्ठा sdhci_host *host, पूर्णांक width);
	व्योम (*platक्रमm_send_init_74_घड़ीs)(काष्ठा sdhci_host *host,
					     u8 घातer_mode);
	अचिन्हित पूर्णांक    (*get_ro)(काष्ठा sdhci_host *host);
	व्योम		(*reset)(काष्ठा sdhci_host *host, u8 mask);
	पूर्णांक	(*platक्रमm_execute_tuning)(काष्ठा sdhci_host *host, u32 opcode);
	व्योम	(*set_uhs_संकेतing)(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक uhs);
	व्योम	(*hw_reset)(काष्ठा sdhci_host *host);
	व्योम    (*adma_workaround)(काष्ठा sdhci_host *host, u32 पूर्णांकmask);
	व्योम    (*card_event)(काष्ठा sdhci_host *host);
	व्योम	(*voltage_चयन)(काष्ठा sdhci_host *host);
	व्योम	(*adma_ग_लिखो_desc)(काष्ठा sdhci_host *host, व्योम **desc,
				   dma_addr_t addr, पूर्णांक len, अचिन्हित पूर्णांक cmd);
	व्योम	(*copy_to_bounce_buffer)(काष्ठा sdhci_host *host,
					 काष्ठा mmc_data *data,
					 अचिन्हित पूर्णांक length);
	व्योम	(*request_करोne)(काष्ठा sdhci_host *host,
				काष्ठा mmc_request *mrq);
	व्योम    (*dump_venकरोr_regs)(काष्ठा sdhci_host *host);
पूर्ण;

#अगर_घोषित CONFIG_MMC_SDHCI_IO_ACCESSORS

अटल अंतरभूत व्योम sdhci_ग_लिखोl(काष्ठा sdhci_host *host, u32 val, पूर्णांक reg)
अणु
	अगर (unlikely(host->ops->ग_लिखो_l))
		host->ops->ग_लिखो_l(host, val, reg);
	अन्यथा
		ग_लिखोl(val, host->ioaddr + reg);
पूर्ण

अटल अंतरभूत व्योम sdhci_ग_लिखोw(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	अगर (unlikely(host->ops->ग_लिखो_w))
		host->ops->ग_लिखो_w(host, val, reg);
	अन्यथा
		ग_लिखोw(val, host->ioaddr + reg);
पूर्ण

अटल अंतरभूत व्योम sdhci_ग_लिखोb(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	अगर (unlikely(host->ops->ग_लिखो_b))
		host->ops->ग_लिखो_b(host, val, reg);
	अन्यथा
		ग_लिखोb(val, host->ioaddr + reg);
पूर्ण

अटल अंतरभूत u32 sdhci_पढ़ोl(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	अगर (unlikely(host->ops->पढ़ो_l))
		वापस host->ops->पढ़ो_l(host, reg);
	अन्यथा
		वापस पढ़ोl(host->ioaddr + reg);
पूर्ण

अटल अंतरभूत u16 sdhci_पढ़ोw(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	अगर (unlikely(host->ops->पढ़ो_w))
		वापस host->ops->पढ़ो_w(host, reg);
	अन्यथा
		वापस पढ़ोw(host->ioaddr + reg);
पूर्ण

अटल अंतरभूत u8 sdhci_पढ़ोb(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	अगर (unlikely(host->ops->पढ़ो_b))
		वापस host->ops->पढ़ो_b(host, reg);
	अन्यथा
		वापस पढ़ोb(host->ioaddr + reg);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम sdhci_ग_लिखोl(काष्ठा sdhci_host *host, u32 val, पूर्णांक reg)
अणु
	ग_लिखोl(val, host->ioaddr + reg);
पूर्ण

अटल अंतरभूत व्योम sdhci_ग_लिखोw(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	ग_लिखोw(val, host->ioaddr + reg);
पूर्ण

अटल अंतरभूत व्योम sdhci_ग_लिखोb(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	ग_लिखोb(val, host->ioaddr + reg);
पूर्ण

अटल अंतरभूत u32 sdhci_पढ़ोl(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	वापस पढ़ोl(host->ioaddr + reg);
पूर्ण

अटल अंतरभूत u16 sdhci_पढ़ोw(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	वापस पढ़ोw(host->ioaddr + reg);
पूर्ण

अटल अंतरभूत u8 sdhci_पढ़ोb(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	वापस पढ़ोb(host->ioaddr + reg);
पूर्ण

#पूर्ण_अगर /* CONFIG_MMC_SDHCI_IO_ACCESSORS */

काष्ठा sdhci_host *sdhci_alloc_host(काष्ठा device *dev, माप_प्रकार priv_size);
व्योम sdhci_मुक्त_host(काष्ठा sdhci_host *host);

अटल अंतरभूत व्योम *sdhci_priv(काष्ठा sdhci_host *host)
अणु
	वापस host->निजी;
पूर्ण

व्योम sdhci_card_detect(काष्ठा sdhci_host *host);
व्योम __sdhci_पढ़ो_caps(काष्ठा sdhci_host *host, स्थिर u16 *ver,
		       स्थिर u32 *caps, स्थिर u32 *caps1);
पूर्णांक sdhci_setup_host(काष्ठा sdhci_host *host);
व्योम sdhci_cleanup_host(काष्ठा sdhci_host *host);
पूर्णांक __sdhci_add_host(काष्ठा sdhci_host *host);
पूर्णांक sdhci_add_host(काष्ठा sdhci_host *host);
व्योम sdhci_हटाओ_host(काष्ठा sdhci_host *host, पूर्णांक dead);

अटल अंतरभूत व्योम sdhci_पढ़ो_caps(काष्ठा sdhci_host *host)
अणु
	__sdhci_पढ़ो_caps(host, शून्य, शून्य, शून्य);
पूर्ण

u16 sdhci_calc_clk(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी,
		   अचिन्हित पूर्णांक *actual_घड़ी);
व्योम sdhci_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी);
व्योम sdhci_enable_clk(काष्ठा sdhci_host *host, u16 clk);
व्योम sdhci_set_घातer(काष्ठा sdhci_host *host, अचिन्हित अक्षर mode,
		     अचिन्हित लघु vdd);
व्योम sdhci_set_घातer_and_bus_voltage(काष्ठा sdhci_host *host,
				     अचिन्हित अक्षर mode,
				     अचिन्हित लघु vdd);
व्योम sdhci_set_घातer_noreg(काष्ठा sdhci_host *host, अचिन्हित अक्षर mode,
			   अचिन्हित लघु vdd);
व्योम sdhci_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq);
पूर्णांक sdhci_request_atomic(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq);
व्योम sdhci_set_bus_width(काष्ठा sdhci_host *host, पूर्णांक width);
व्योम sdhci_reset(काष्ठा sdhci_host *host, u8 mask);
व्योम sdhci_set_uhs_संकेतing(काष्ठा sdhci_host *host, अचिन्हित timing);
पूर्णांक sdhci_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode);
व्योम sdhci_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios);
पूर्णांक sdhci_start_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
				      काष्ठा mmc_ios *ios);
व्योम sdhci_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable);
व्योम sdhci_adma_ग_लिखो_desc(काष्ठा sdhci_host *host, व्योम **desc,
			   dma_addr_t addr, पूर्णांक len, अचिन्हित पूर्णांक cmd);

#अगर_घोषित CONFIG_PM
पूर्णांक sdhci_suspend_host(काष्ठा sdhci_host *host);
पूर्णांक sdhci_resume_host(काष्ठा sdhci_host *host);
पूर्णांक sdhci_runसमय_suspend_host(काष्ठा sdhci_host *host);
पूर्णांक sdhci_runसमय_resume_host(काष्ठा sdhci_host *host, पूर्णांक soft_reset);
#पूर्ण_अगर

व्योम sdhci_cqe_enable(काष्ठा mmc_host *mmc);
व्योम sdhci_cqe_disable(काष्ठा mmc_host *mmc, bool recovery);
bool sdhci_cqe_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask, पूर्णांक *cmd_error,
		   पूर्णांक *data_error);

व्योम sdhci_dumpregs(काष्ठा sdhci_host *host);
व्योम sdhci_enable_v4_mode(काष्ठा sdhci_host *host);

व्योम sdhci_start_tuning(काष्ठा sdhci_host *host);
व्योम sdhci_end_tuning(काष्ठा sdhci_host *host);
व्योम sdhci_reset_tuning(काष्ठा sdhci_host *host);
व्योम sdhci_send_tuning(काष्ठा sdhci_host *host, u32 opcode);
व्योम sdhci_पात_tuning(काष्ठा sdhci_host *host, u32 opcode);
व्योम sdhci_चयन_बाह्यal_dma(काष्ठा sdhci_host *host, bool en);
व्योम sdhci_set_data_समयout_irq(काष्ठा sdhci_host *host, bool enable);
व्योम __sdhci_set_समयout(काष्ठा sdhci_host *host, काष्ठा mmc_command *cmd);

#पूर्ण_अगर /* __SDHCI_HW_H */
