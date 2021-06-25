<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mii.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "net_driver.h"
#समावेश "bitfield.h"
#समावेश "efx.h"
#समावेश "nic.h"
#समावेश "farch_regs.h"
#समावेश "io.h"
#समावेश "phy.h"
#समावेश "workarounds.h"
#समावेश "selftest.h"
#समावेश "mdio_10g.h"

/* Hardware control क्रम SFC4000 (aka Falcon). */

/**************************************************************************
 *
 * NIC stats
 *
 **************************************************************************
 */

#घोषणा FALCON_MAC_STATS_SIZE 0x100

#घोषणा XgRxOctets_offset 0x0
#घोषणा XgRxOctets_WIDTH 48
#घोषणा XgRxOctetsOK_offset 0x8
#घोषणा XgRxOctetsOK_WIDTH 48
#घोषणा XgRxPkts_offset 0x10
#घोषणा XgRxPkts_WIDTH 32
#घोषणा XgRxPktsOK_offset 0x14
#घोषणा XgRxPktsOK_WIDTH 32
#घोषणा XgRxBroadcastPkts_offset 0x18
#घोषणा XgRxBroadcastPkts_WIDTH 32
#घोषणा XgRxMulticastPkts_offset 0x1C
#घोषणा XgRxMulticastPkts_WIDTH 32
#घोषणा XgRxUnicastPkts_offset 0x20
#घोषणा XgRxUnicastPkts_WIDTH 32
#घोषणा XgRxUndersizePkts_offset 0x24
#घोषणा XgRxUndersizePkts_WIDTH 32
#घोषणा XgRxOversizePkts_offset 0x28
#घोषणा XgRxOversizePkts_WIDTH 32
#घोषणा XgRxJabberPkts_offset 0x2C
#घोषणा XgRxJabberPkts_WIDTH 32
#घोषणा XgRxUndersizeFCSerrorPkts_offset 0x30
#घोषणा XgRxUndersizeFCSerrorPkts_WIDTH 32
#घोषणा XgRxDropEvents_offset 0x34
#घोषणा XgRxDropEvents_WIDTH 32
#घोषणा XgRxFCSerrorPkts_offset 0x38
#घोषणा XgRxFCSerrorPkts_WIDTH 32
#घोषणा XgRxAlignError_offset 0x3C
#घोषणा XgRxAlignError_WIDTH 32
#घोषणा XgRxSymbolError_offset 0x40
#घोषणा XgRxSymbolError_WIDTH 32
#घोषणा XgRxInternalMACError_offset 0x44
#घोषणा XgRxInternalMACError_WIDTH 32
#घोषणा XgRxControlPkts_offset 0x48
#घोषणा XgRxControlPkts_WIDTH 32
#घोषणा XgRxPausePkts_offset 0x4C
#घोषणा XgRxPausePkts_WIDTH 32
#घोषणा XgRxPkts64Octets_offset 0x50
#घोषणा XgRxPkts64Octets_WIDTH 32
#घोषणा XgRxPkts65to127Octets_offset 0x54
#घोषणा XgRxPkts65to127Octets_WIDTH 32
#घोषणा XgRxPkts128to255Octets_offset 0x58
#घोषणा XgRxPkts128to255Octets_WIDTH 32
#घोषणा XgRxPkts256to511Octets_offset 0x5C
#घोषणा XgRxPkts256to511Octets_WIDTH 32
#घोषणा XgRxPkts512to1023Octets_offset 0x60
#घोषणा XgRxPkts512to1023Octets_WIDTH 32
#घोषणा XgRxPkts1024to15xxOctets_offset 0x64
#घोषणा XgRxPkts1024to15xxOctets_WIDTH 32
#घोषणा XgRxPkts15xxtoMaxOctets_offset 0x68
#घोषणा XgRxPkts15xxtoMaxOctets_WIDTH 32
#घोषणा XgRxLengthError_offset 0x6C
#घोषणा XgRxLengthError_WIDTH 32
#घोषणा XgTxPkts_offset 0x80
#घोषणा XgTxPkts_WIDTH 32
#घोषणा XgTxOctets_offset 0x88
#घोषणा XgTxOctets_WIDTH 48
#घोषणा XgTxMulticastPkts_offset 0x90
#घोषणा XgTxMulticastPkts_WIDTH 32
#घोषणा XgTxBroadcastPkts_offset 0x94
#घोषणा XgTxBroadcastPkts_WIDTH 32
#घोषणा XgTxUnicastPkts_offset 0x98
#घोषणा XgTxUnicastPkts_WIDTH 32
#घोषणा XgTxControlPkts_offset 0x9C
#घोषणा XgTxControlPkts_WIDTH 32
#घोषणा XgTxPausePkts_offset 0xA0
#घोषणा XgTxPausePkts_WIDTH 32
#घोषणा XgTxPkts64Octets_offset 0xA4
#घोषणा XgTxPkts64Octets_WIDTH 32
#घोषणा XgTxPkts65to127Octets_offset 0xA8
#घोषणा XgTxPkts65to127Octets_WIDTH 32
#घोषणा XgTxPkts128to255Octets_offset 0xAC
#घोषणा XgTxPkts128to255Octets_WIDTH 32
#घोषणा XgTxPkts256to511Octets_offset 0xB0
#घोषणा XgTxPkts256to511Octets_WIDTH 32
#घोषणा XgTxPkts512to1023Octets_offset 0xB4
#घोषणा XgTxPkts512to1023Octets_WIDTH 32
#घोषणा XgTxPkts1024to15xxOctets_offset 0xB8
#घोषणा XgTxPkts1024to15xxOctets_WIDTH 32
#घोषणा XgTxPkts1519toMaxOctets_offset 0xBC
#घोषणा XgTxPkts1519toMaxOctets_WIDTH 32
#घोषणा XgTxUndersizePkts_offset 0xC0
#घोषणा XgTxUndersizePkts_WIDTH 32
#घोषणा XgTxOversizePkts_offset 0xC4
#घोषणा XgTxOversizePkts_WIDTH 32
#घोषणा XgTxNonTcpUdpPkt_offset 0xC8
#घोषणा XgTxNonTcpUdpPkt_WIDTH 16
#घोषणा XgTxMacSrcErrPkt_offset 0xCC
#घोषणा XgTxMacSrcErrPkt_WIDTH 16
#घोषणा XgTxIpSrcErrPkt_offset 0xD0
#घोषणा XgTxIpSrcErrPkt_WIDTH 16
#घोषणा XgDmaDone_offset 0xD4
#घोषणा XgDmaDone_WIDTH 32

#घोषणा FALCON_XMAC_STATS_DMA_FLAG(efx)				\
	(*(u32 *)((efx)->stats_buffer.addr + XgDmaDone_offset))

#घोषणा FALCON_DMA_STAT(ext_name, hw_name)				\
	[FALCON_STAT_ ## ext_name] =					\
	अणु #ext_name,							\
	  /* 48-bit stats are zero-padded to 64 on DMA */		\
	  hw_name ## _ ## WIDTH == 48 ? 64 : hw_name ## _ ## WIDTH,	\
	  hw_name ## _ ## offset पूर्ण
#घोषणा FALCON_OTHER_STAT(ext_name)					\
	[FALCON_STAT_ ## ext_name] = अणु #ext_name, 0, 0 पूर्ण
#घोषणा GENERIC_SW_STAT(ext_name)				\
	[GENERIC_STAT_ ## ext_name] = अणु #ext_name, 0, 0 पूर्ण

अटल स्थिर काष्ठा ef4_hw_stat_desc falcon_stat_desc[FALCON_STAT_COUNT] = अणु
	FALCON_DMA_STAT(tx_bytes, XgTxOctets),
	FALCON_DMA_STAT(tx_packets, XgTxPkts),
	FALCON_DMA_STAT(tx_छोड़ो, XgTxPausePkts),
	FALCON_DMA_STAT(tx_control, XgTxControlPkts),
	FALCON_DMA_STAT(tx_unicast, XgTxUnicastPkts),
	FALCON_DMA_STAT(tx_multicast, XgTxMulticastPkts),
	FALCON_DMA_STAT(tx_broadcast, XgTxBroadcastPkts),
	FALCON_DMA_STAT(tx_lt64, XgTxUndersizePkts),
	FALCON_DMA_STAT(tx_64, XgTxPkts64Octets),
	FALCON_DMA_STAT(tx_65_to_127, XgTxPkts65to127Octets),
	FALCON_DMA_STAT(tx_128_to_255, XgTxPkts128to255Octets),
	FALCON_DMA_STAT(tx_256_to_511, XgTxPkts256to511Octets),
	FALCON_DMA_STAT(tx_512_to_1023, XgTxPkts512to1023Octets),
	FALCON_DMA_STAT(tx_1024_to_15xx, XgTxPkts1024to15xxOctets),
	FALCON_DMA_STAT(tx_15xx_to_jumbo, XgTxPkts1519toMaxOctets),
	FALCON_DMA_STAT(tx_gtjumbo, XgTxOversizePkts),
	FALCON_DMA_STAT(tx_non_tcpudp, XgTxNonTcpUdpPkt),
	FALCON_DMA_STAT(tx_mac_src_error, XgTxMacSrcErrPkt),
	FALCON_DMA_STAT(tx_ip_src_error, XgTxIpSrcErrPkt),
	FALCON_DMA_STAT(rx_bytes, XgRxOctets),
	FALCON_DMA_STAT(rx_good_bytes, XgRxOctetsOK),
	FALCON_OTHER_STAT(rx_bad_bytes),
	FALCON_DMA_STAT(rx_packets, XgRxPkts),
	FALCON_DMA_STAT(rx_good, XgRxPktsOK),
	FALCON_DMA_STAT(rx_bad, XgRxFCSerrorPkts),
	FALCON_DMA_STAT(rx_छोड़ो, XgRxPausePkts),
	FALCON_DMA_STAT(rx_control, XgRxControlPkts),
	FALCON_DMA_STAT(rx_unicast, XgRxUnicastPkts),
	FALCON_DMA_STAT(rx_multicast, XgRxMulticastPkts),
	FALCON_DMA_STAT(rx_broadcast, XgRxBroadcastPkts),
	FALCON_DMA_STAT(rx_lt64, XgRxUndersizePkts),
	FALCON_DMA_STAT(rx_64, XgRxPkts64Octets),
	FALCON_DMA_STAT(rx_65_to_127, XgRxPkts65to127Octets),
	FALCON_DMA_STAT(rx_128_to_255, XgRxPkts128to255Octets),
	FALCON_DMA_STAT(rx_256_to_511, XgRxPkts256to511Octets),
	FALCON_DMA_STAT(rx_512_to_1023, XgRxPkts512to1023Octets),
	FALCON_DMA_STAT(rx_1024_to_15xx, XgRxPkts1024to15xxOctets),
	FALCON_DMA_STAT(rx_15xx_to_jumbo, XgRxPkts15xxtoMaxOctets),
	FALCON_DMA_STAT(rx_gtjumbo, XgRxOversizePkts),
	FALCON_DMA_STAT(rx_bad_lt64, XgRxUndersizeFCSerrorPkts),
	FALCON_DMA_STAT(rx_bad_gtjumbo, XgRxJabberPkts),
	FALCON_DMA_STAT(rx_overflow, XgRxDropEvents),
	FALCON_DMA_STAT(rx_symbol_error, XgRxSymbolError),
	FALCON_DMA_STAT(rx_align_error, XgRxAlignError),
	FALCON_DMA_STAT(rx_length_error, XgRxLengthError),
	FALCON_DMA_STAT(rx_पूर्णांकernal_error, XgRxInternalMACError),
	FALCON_OTHER_STAT(rx_nodesc_drop_cnt),
	GENERIC_SW_STAT(rx_nodesc_trunc),
	GENERIC_SW_STAT(rx_noskb_drops),
पूर्ण;
अटल स्थिर अचिन्हित दीर्घ falcon_stat_mask[] = अणु
	[0 ... BITS_TO_LONGS(FALCON_STAT_COUNT) - 1] = ~0UL,
पूर्ण;

/**************************************************************************
 *
 * Basic SPI command set and bit definitions
 *
 *************************************************************************/

#घोषणा SPI_WRSR 0x01		/* Write status रेजिस्टर */
#घोषणा SPI_WRITE 0x02		/* Write data to memory array */
#घोषणा SPI_READ 0x03		/* Read data from memory array */
#घोषणा SPI_WRDI 0x04		/* Reset ग_लिखो enable latch */
#घोषणा SPI_RDSR 0x05		/* Read status रेजिस्टर */
#घोषणा SPI_WREN 0x06		/* Set ग_लिखो enable latch */
#घोषणा SPI_SST_EWSR 0x50	/* SST: Enable ग_लिखो to status रेजिस्टर */

#घोषणा SPI_STATUS_WPEN 0x80	/* Write-protect pin enabled */
#घोषणा SPI_STATUS_BP2 0x10	/* Block protection bit 2 */
#घोषणा SPI_STATUS_BP1 0x08	/* Block protection bit 1 */
#घोषणा SPI_STATUS_BP0 0x04	/* Block protection bit 0 */
#घोषणा SPI_STATUS_WEN 0x02	/* State of the ग_लिखो enable latch */
#घोषणा SPI_STATUS_NRDY 0x01	/* Device busy flag */

/**************************************************************************
 *
 * Non-अस्थिर memory layout
 *
 **************************************************************************
 */

/* SFC4000 flash is partitioned पूर्णांकo:
 *     0-0x400       chip and board config (see काष्ठा falcon_nvconfig)
 *     0x400-0x8000  unused (or may contain VPD अगर EEPROM not present)
 *     0x8000-end    boot code (mapped to PCI expansion ROM)
 * SFC4000 small EEPROM (size < 0x400) is used क्रम VPD only.
 * SFC4000 large EEPROM (size >= 0x400) is partitioned पूर्णांकo:
 *     0-0x400       chip and board config
 *     configurable  VPD
 *     0x800-0x1800  boot config
 * Aside from the chip and board config, all of these are optional and may
 * be असलent or truncated depending on the devices used.
 */
#घोषणा FALCON_NVCONFIG_END 0x400U
#घोषणा FALCON_FLASH_BOOTCODE_START 0x8000U
#घोषणा FALCON_EEPROM_BOOTCONFIG_START 0x800U
#घोषणा FALCON_EEPROM_BOOTCONFIG_END 0x1800U

/* Board configuration v2 (v1 is obsolete; later versions are compatible) */
काष्ठा falcon_nvconfig_board_v2 अणु
	__le16 nports;
	u8 port0_phy_addr;
	u8 port0_phy_type;
	u8 port1_phy_addr;
	u8 port1_phy_type;
	__le16 asic_sub_revision;
	__le16 board_revision;
पूर्ण __packed;

/* Board configuration v3 extra inक्रमmation */
काष्ठा falcon_nvconfig_board_v3 अणु
	__le32 spi_device_type[2];
पूर्ण __packed;

/* Bit numbers क्रम spi_device_type */
#घोषणा SPI_DEV_TYPE_SIZE_LBN 0
#घोषणा SPI_DEV_TYPE_SIZE_WIDTH 5
#घोषणा SPI_DEV_TYPE_ADDR_LEN_LBN 6
#घोषणा SPI_DEV_TYPE_ADDR_LEN_WIDTH 2
#घोषणा SPI_DEV_TYPE_ERASE_CMD_LBN 8
#घोषणा SPI_DEV_TYPE_ERASE_CMD_WIDTH 8
#घोषणा SPI_DEV_TYPE_ERASE_SIZE_LBN 16
#घोषणा SPI_DEV_TYPE_ERASE_SIZE_WIDTH 5
#घोषणा SPI_DEV_TYPE_BLOCK_SIZE_LBN 24
#घोषणा SPI_DEV_TYPE_BLOCK_SIZE_WIDTH 5
#घोषणा SPI_DEV_TYPE_FIELD(type, field)					\
	(((type) >> EF4_LOW_BIT(field)) & EF4_MASK32(EF4_WIDTH(field)))

#घोषणा FALCON_NVCONFIG_OFFSET 0x300

#घोषणा FALCON_NVCONFIG_BOARD_MAGIC_NUM 0xFA1C
काष्ठा falcon_nvconfig अणु
	ef4_oword_t ee_vpd_cfg_reg;			/* 0x300 */
	u8 mac_address[2][8];			/* 0x310 */
	ef4_oword_t pcie_sd_ctl0123_reg;		/* 0x320 */
	ef4_oword_t pcie_sd_ctl45_reg;			/* 0x330 */
	ef4_oword_t pcie_pcs_ctl_stat_reg;		/* 0x340 */
	ef4_oword_t hw_init_reg;			/* 0x350 */
	ef4_oword_t nic_stat_reg;			/* 0x360 */
	ef4_oword_t glb_ctl_reg;			/* 0x370 */
	ef4_oword_t srm_cfg_reg;			/* 0x380 */
	ef4_oword_t spare_reg;				/* 0x390 */
	__le16 board_magic_num;			/* 0x3A0 */
	__le16 board_काष्ठा_ver;
	__le16 board_checksum;
	काष्ठा falcon_nvconfig_board_v2 board_v2;
	ef4_oword_t ee_base_page_reg;			/* 0x3B0 */
	काष्ठा falcon_nvconfig_board_v3 board_v3;	/* 0x3C0 */
पूर्ण __packed;

/*************************************************************************/

अटल पूर्णांक falcon_reset_hw(काष्ठा ef4_nic *efx, क्रमागत reset_type method);
अटल व्योम falcon_reconfigure_mac_wrapper(काष्ठा ef4_nic *efx);

अटल स्थिर अचिन्हित पूर्णांक
/* "Large" EEPROM device: Aपंचांगel AT25640 or similar
 * 8 KB, 16-bit address, 32 B ग_लिखो block */
large_eeprom_type = ((13 << SPI_DEV_TYPE_SIZE_LBN)
		     | (2 << SPI_DEV_TYPE_ADDR_LEN_LBN)
		     | (5 << SPI_DEV_TYPE_BLOCK_SIZE_LBN)),
/* Default flash device: Aपंचांगel AT25F1024
 * 128 KB, 24-bit address, 32 KB erase block, 256 B ग_लिखो block */
शेष_flash_type = ((17 << SPI_DEV_TYPE_SIZE_LBN)
		      | (3 << SPI_DEV_TYPE_ADDR_LEN_LBN)
		      | (0x52 << SPI_DEV_TYPE_ERASE_CMD_LBN)
		      | (15 << SPI_DEV_TYPE_ERASE_SIZE_LBN)
		      | (8 << SPI_DEV_TYPE_BLOCK_SIZE_LBN));

/**************************************************************************
 *
 * I2C bus - this is a bit-bashing पूर्णांकerface using GPIO pins
 * Note that it uses the output enables to tristate the outमाला_दो
 * SDA is the data pin and SCL is the घड़ी
 *
 **************************************************************************
 */
अटल व्योम falcon_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा ef4_nic *efx = (काष्ठा ef4_nic *)data;
	ef4_oword_t reg;

	ef4_पढ़ोo(efx, &reg, FR_AB_GPIO_CTL);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_GPIO3_OEN, !state);
	ef4_ग_लिखोo(efx, &reg, FR_AB_GPIO_CTL);
पूर्ण

अटल व्योम falcon_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा ef4_nic *efx = (काष्ठा ef4_nic *)data;
	ef4_oword_t reg;

	ef4_पढ़ोo(efx, &reg, FR_AB_GPIO_CTL);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_GPIO0_OEN, !state);
	ef4_ग_लिखोo(efx, &reg, FR_AB_GPIO_CTL);
पूर्ण

अटल पूर्णांक falcon_माला_लोda(व्योम *data)
अणु
	काष्ठा ef4_nic *efx = (काष्ठा ef4_nic *)data;
	ef4_oword_t reg;

	ef4_पढ़ोo(efx, &reg, FR_AB_GPIO_CTL);
	वापस EF4_OWORD_FIELD(reg, FRF_AB_GPIO3_IN);
पूर्ण

अटल पूर्णांक falcon_माला_लोcl(व्योम *data)
अणु
	काष्ठा ef4_nic *efx = (काष्ठा ef4_nic *)data;
	ef4_oword_t reg;

	ef4_पढ़ोo(efx, &reg, FR_AB_GPIO_CTL);
	वापस EF4_OWORD_FIELD(reg, FRF_AB_GPIO0_IN);
पूर्ण

अटल स्थिर काष्ठा i2c_algo_bit_data falcon_i2c_bit_operations = अणु
	.setsda		= falcon_setsda,
	.setscl		= falcon_setscl,
	.माला_लोda		= falcon_माला_लोda,
	.माला_लोcl		= falcon_माला_लोcl,
	.udelay		= 5,
	/* Wait up to 50 ms क्रम slave to let us pull SCL high */
	.समयout	= DIV_ROUND_UP(HZ, 20),
पूर्ण;

अटल व्योम falcon_push_irq_moderation(काष्ठा ef4_channel *channel)
अणु
	ef4_dword_t समयr_cmd;
	काष्ठा ef4_nic *efx = channel->efx;

	/* Set समयr रेजिस्टर */
	अगर (channel->irq_moderation_us) अणु
		अचिन्हित पूर्णांक ticks;

		ticks = ef4_usecs_to_ticks(efx, channel->irq_moderation_us);
		EF4_POPULATE_DWORD_2(समयr_cmd,
				     FRF_AB_TC_TIMER_MODE,
				     FFE_BB_TIMER_MODE_INT_HLDOFF,
				     FRF_AB_TC_TIMER_VAL,
				     ticks - 1);
	पूर्ण अन्यथा अणु
		EF4_POPULATE_DWORD_2(समयr_cmd,
				     FRF_AB_TC_TIMER_MODE,
				     FFE_BB_TIMER_MODE_DIS,
				     FRF_AB_TC_TIMER_VAL, 0);
	पूर्ण
	BUILD_BUG_ON(FR_AA_TIMER_COMMAND_KER != FR_BZ_TIMER_COMMAND_P0);
	ef4_ग_लिखोd_page_locked(efx, &समयr_cmd, FR_BZ_TIMER_COMMAND_P0,
			       channel->channel);
पूर्ण

अटल व्योम falcon_deconfigure_mac_wrapper(काष्ठा ef4_nic *efx);

अटल व्योम falcon_prepare_flush(काष्ठा ef4_nic *efx)
अणु
	falcon_deconfigure_mac_wrapper(efx);

	/* Wait क्रम the tx and rx fअगरo's to get to the next packet boundary
	 * (~1ms without back-pressure), then to drain the reमुख्यder of the
	 * fअगरo's at data path speeds (negligible), with a healthy margin. */
	msleep(10);
पूर्ण

/* Acknowledge a legacy पूर्णांकerrupt from Falcon
 *
 * This acknowledges a legacy (not MSI) पूर्णांकerrupt via INT_ACK_KER_REG.
 *
 * Due to SFC bug 3706 (silicon revision <=A1) पढ़ोs can be duplicated in the
 * BIU. Interrupt acknowledge is पढ़ो sensitive so must ग_लिखो instead
 * (then पढ़ो to ensure the BIU collector is flushed)
 *
 * NB most hardware supports MSI पूर्णांकerrupts
 */
अटल अंतरभूत व्योम falcon_irq_ack_a1(काष्ठा ef4_nic *efx)
अणु
	ef4_dword_t reg;

	EF4_POPULATE_DWORD_1(reg, FRF_AA_INT_ACK_KER_FIELD, 0xb7eb7e);
	ef4_ग_लिखोd(efx, &reg, FR_AA_INT_ACK_KER);
	ef4_पढ़ोd(efx, &reg, FR_AA_WORK_AROUND_BROKEN_PCI_READS);
पूर्ण

अटल irqवापस_t falcon_legacy_पूर्णांकerrupt_a1(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ef4_nic *efx = dev_id;
	ef4_oword_t *पूर्णांक_ker = efx->irq_status.addr;
	पूर्णांक syserr;
	पूर्णांक queues;

	/* Check to see अगर this is our पूर्णांकerrupt.  If it isn't, we
	 * निकास without having touched the hardware.
	 */
	अगर (unlikely(EF4_OWORD_IS_ZERO(*पूर्णांक_ker))) अणु
		netअगर_vdbg(efx, पूर्णांकr, efx->net_dev,
			   "IRQ %d on CPU %d not for me\n", irq,
			   raw_smp_processor_id());
		वापस IRQ_NONE;
	पूर्ण
	efx->last_irq_cpu = raw_smp_processor_id();
	netअगर_vdbg(efx, पूर्णांकr, efx->net_dev,
		   "IRQ %d on CPU %d status " EF4_OWORD_FMT "\n",
		   irq, raw_smp_processor_id(), EF4_OWORD_VAL(*पूर्णांक_ker));

	अगर (!likely(READ_ONCE(efx->irq_soft_enabled)))
		वापस IRQ_HANDLED;

	/* Check to see अगर we have a serious error condition */
	syserr = EF4_OWORD_FIELD(*पूर्णांक_ker, FSF_AZ_NET_IVEC_FATAL_INT);
	अगर (unlikely(syserr))
		वापस ef4_farch_fatal_पूर्णांकerrupt(efx);

	/* Determine पूर्णांकerrupting queues, clear पूर्णांकerrupt status
	 * रेजिस्टर and acknowledge the device पूर्णांकerrupt.
	 */
	BUILD_BUG_ON(FSF_AZ_NET_IVEC_INT_Q_WIDTH > EF4_MAX_CHANNELS);
	queues = EF4_OWORD_FIELD(*पूर्णांक_ker, FSF_AZ_NET_IVEC_INT_Q);
	EF4_ZERO_OWORD(*पूर्णांक_ker);
	wmb(); /* Ensure the vector is cleared beक्रमe पूर्णांकerrupt ack */
	falcon_irq_ack_a1(efx);

	अगर (queues & 1)
		ef4_schedule_channel_irq(ef4_get_channel(efx, 0));
	अगर (queues & 2)
		ef4_schedule_channel_irq(ef4_get_channel(efx, 1));
	वापस IRQ_HANDLED;
पूर्ण

/**************************************************************************
 *
 * RSS
 *
 **************************************************************************
 */
अटल पूर्णांक dummy_rx_push_rss_config(काष्ठा ef4_nic *efx, bool user,
				    स्थिर u32 *rx_indir_table)
अणु
	(व्योम) efx;
	(व्योम) user;
	(व्योम) rx_indir_table;
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक falcon_b0_rx_push_rss_config(काष्ठा ef4_nic *efx, bool user,
					स्थिर u32 *rx_indir_table)
अणु
	ef4_oword_t temp;

	(व्योम) user;
	/* Set hash key क्रम IPv4 */
	स_नकल(&temp, efx->rx_hash_key, माप(temp));
	ef4_ग_लिखोo(efx, &temp, FR_BZ_RX_RSS_TKEY);

	स_नकल(efx->rx_indir_table, rx_indir_table,
	       माप(efx->rx_indir_table));
	ef4_farch_rx_push_indir_table(efx);
	वापस 0;
पूर्ण

/**************************************************************************
 *
 * EEPROM/flash
 *
 **************************************************************************
 */

#घोषणा FALCON_SPI_MAX_LEN माप(ef4_oword_t)

अटल पूर्णांक falcon_spi_poll(काष्ठा ef4_nic *efx)
अणु
	ef4_oword_t reg;
	ef4_पढ़ोo(efx, &reg, FR_AB_EE_SPI_HCMD);
	वापस EF4_OWORD_FIELD(reg, FRF_AB_EE_SPI_HCMD_CMD_EN) ? -EBUSY : 0;
पूर्ण

/* Wait क्रम SPI command completion */
अटल पूर्णांक falcon_spi_रुको(काष्ठा ef4_nic *efx)
अणु
	/* Most commands will finish quickly, so we start polling at
	 * very लघु पूर्णांकervals.  Someबार the command may have to
	 * रुको क्रम VPD or expansion ROM access outside of our
	 * control, so we allow up to 100 ms. */
	अचिन्हित दीर्घ समयout = jअगरfies + 1 + DIV_ROUND_UP(HZ, 10);
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु
		अगर (!falcon_spi_poll(efx))
			वापस 0;
		udelay(10);
	पूर्ण

	क्रम (;;) अणु
		अगर (!falcon_spi_poll(efx))
			वापस 0;
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			netअगर_err(efx, hw, efx->net_dev,
				  "timed out waiting for SPI\n");
			वापस -ETIMEDOUT;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
पूर्ण

अटल पूर्णांक
falcon_spi_cmd(काष्ठा ef4_nic *efx, स्थिर काष्ठा falcon_spi_device *spi,
	       अचिन्हित पूर्णांक command, पूर्णांक address,
	       स्थिर व्योम *in, व्योम *out, माप_प्रकार len)
अणु
	bool addressed = (address >= 0);
	bool पढ़ोing = (out != शून्य);
	ef4_oword_t reg;
	पूर्णांक rc;

	/* Input validation */
	अगर (len > FALCON_SPI_MAX_LEN)
		वापस -EINVAL;

	/* Check that previous command is not still running */
	rc = falcon_spi_poll(efx);
	अगर (rc)
		वापस rc;

	/* Program address रेजिस्टर, अगर we have an address */
	अगर (addressed) अणु
		EF4_POPULATE_OWORD_1(reg, FRF_AB_EE_SPI_HADR_ADR, address);
		ef4_ग_लिखोo(efx, &reg, FR_AB_EE_SPI_HADR);
	पूर्ण

	/* Program data रेजिस्टर, अगर we have data */
	अगर (in != शून्य) अणु
		स_नकल(&reg, in, len);
		ef4_ग_लिखोo(efx, &reg, FR_AB_EE_SPI_HDATA);
	पूर्ण

	/* Issue पढ़ो/ग_लिखो command */
	EF4_POPULATE_OWORD_7(reg,
			     FRF_AB_EE_SPI_HCMD_CMD_EN, 1,
			     FRF_AB_EE_SPI_HCMD_SF_SEL, spi->device_id,
			     FRF_AB_EE_SPI_HCMD_DABCNT, len,
			     FRF_AB_EE_SPI_HCMD_READ, पढ़ोing,
			     FRF_AB_EE_SPI_HCMD_DUBCNT, 0,
			     FRF_AB_EE_SPI_HCMD_ADBCNT,
			     (addressed ? spi->addr_len : 0),
			     FRF_AB_EE_SPI_HCMD_ENC, command);
	ef4_ग_लिखोo(efx, &reg, FR_AB_EE_SPI_HCMD);

	/* Wait क्रम पढ़ो/ग_लिखो to complete */
	rc = falcon_spi_रुको(efx);
	अगर (rc)
		वापस rc;

	/* Read data */
	अगर (out != शून्य) अणु
		ef4_पढ़ोo(efx, &reg, FR_AB_EE_SPI_HDATA);
		स_नकल(out, &reg, len);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u8
falcon_spi_munge_command(स्थिर काष्ठा falcon_spi_device *spi,
			 स्थिर u8 command, स्थिर अचिन्हित पूर्णांक address)
अणु
	वापस command | (((address >> 8) & spi->munge_address) << 3);
पूर्ण

अटल पूर्णांक
falcon_spi_पढ़ो(काष्ठा ef4_nic *efx, स्थिर काष्ठा falcon_spi_device *spi,
		loff_t start, माप_प्रकार len, माप_प्रकार *retlen, u8 *buffer)
अणु
	माप_प्रकार block_len, pos = 0;
	अचिन्हित पूर्णांक command;
	पूर्णांक rc = 0;

	जबतक (pos < len) अणु
		block_len = min(len - pos, FALCON_SPI_MAX_LEN);

		command = falcon_spi_munge_command(spi, SPI_READ, start + pos);
		rc = falcon_spi_cmd(efx, spi, command, start + pos, शून्य,
				    buffer + pos, block_len);
		अगर (rc)
			अवरोध;
		pos += block_len;

		/* Aव्योम locking up the प्रणाली */
		cond_resched();
		अगर (संकेत_pending(current)) अणु
			rc = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (retlen)
		*retlen = pos;
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_SFC_FALCON_MTD

काष्ठा falcon_mtd_partition अणु
	काष्ठा ef4_mtd_partition common;
	स्थिर काष्ठा falcon_spi_device *spi;
	माप_प्रकार offset;
पूर्ण;

#घोषणा to_falcon_mtd_partition(mtd)				\
	container_of(mtd, काष्ठा falcon_mtd_partition, common.mtd)

अटल माप_प्रकार
falcon_spi_ग_लिखो_limit(स्थिर काष्ठा falcon_spi_device *spi, माप_प्रकार start)
अणु
	वापस min(FALCON_SPI_MAX_LEN,
		   (spi->block_size - (start & (spi->block_size - 1))));
पूर्ण

/* Wait up to 10 ms क्रम buffered ग_लिखो completion */
अटल पूर्णांक
falcon_spi_रुको_ग_लिखो(काष्ठा ef4_nic *efx, स्थिर काष्ठा falcon_spi_device *spi)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + 1 + DIV_ROUND_UP(HZ, 100);
	u8 status;
	पूर्णांक rc;

	क्रम (;;) अणु
		rc = falcon_spi_cmd(efx, spi, SPI_RDSR, -1, शून्य,
				    &status, माप(status));
		अगर (rc)
			वापस rc;
		अगर (!(status & SPI_STATUS_NRDY))
			वापस 0;
		अगर (समय_after_eq(jअगरfies, समयout)) अणु
			netअगर_err(efx, hw, efx->net_dev,
				  "SPI write timeout on device %d"
				  " last status=0x%02x\n",
				  spi->device_id, status);
			वापस -ETIMEDOUT;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
पूर्ण

अटल पूर्णांक
falcon_spi_ग_लिखो(काष्ठा ef4_nic *efx, स्थिर काष्ठा falcon_spi_device *spi,
		 loff_t start, माप_प्रकार len, माप_प्रकार *retlen, स्थिर u8 *buffer)
अणु
	u8 verअगरy_buffer[FALCON_SPI_MAX_LEN];
	माप_प्रकार block_len, pos = 0;
	अचिन्हित पूर्णांक command;
	पूर्णांक rc = 0;

	जबतक (pos < len) अणु
		rc = falcon_spi_cmd(efx, spi, SPI_WREN, -1, शून्य, शून्य, 0);
		अगर (rc)
			अवरोध;

		block_len = min(len - pos,
				falcon_spi_ग_लिखो_limit(spi, start + pos));
		command = falcon_spi_munge_command(spi, SPI_WRITE, start + pos);
		rc = falcon_spi_cmd(efx, spi, command, start + pos,
				    buffer + pos, शून्य, block_len);
		अगर (rc)
			अवरोध;

		rc = falcon_spi_रुको_ग_लिखो(efx, spi);
		अगर (rc)
			अवरोध;

		command = falcon_spi_munge_command(spi, SPI_READ, start + pos);
		rc = falcon_spi_cmd(efx, spi, command, start + pos,
				    शून्य, verअगरy_buffer, block_len);
		अगर (स_भेद(verअगरy_buffer, buffer + pos, block_len)) अणु
			rc = -EIO;
			अवरोध;
		पूर्ण

		pos += block_len;

		/* Aव्योम locking up the प्रणाली */
		cond_resched();
		अगर (संकेत_pending(current)) अणु
			rc = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (retlen)
		*retlen = pos;
	वापस rc;
पूर्ण

अटल पूर्णांक
falcon_spi_slow_रुको(काष्ठा falcon_mtd_partition *part, bool unपूर्णांकerruptible)
अणु
	स्थिर काष्ठा falcon_spi_device *spi = part->spi;
	काष्ठा ef4_nic *efx = part->common.mtd.priv;
	u8 status;
	पूर्णांक rc, i;

	/* Wait up to 4s क्रम flash/EEPROM to finish a slow operation. */
	क्रम (i = 0; i < 40; i++) अणु
		__set_current_state(unपूर्णांकerruptible ?
				    TASK_UNINTERRUPTIBLE : TASK_INTERRUPTIBLE);
		schedule_समयout(HZ / 10);
		rc = falcon_spi_cmd(efx, spi, SPI_RDSR, -1, शून्य,
				    &status, माप(status));
		अगर (rc)
			वापस rc;
		अगर (!(status & SPI_STATUS_NRDY))
			वापस 0;
		अगर (संकेत_pending(current))
			वापस -EINTR;
	पूर्ण
	pr_err("%s: timed out waiting for %s\n",
	       part->common.name, part->common.dev_type_name);
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
falcon_spi_unlock(काष्ठा ef4_nic *efx, स्थिर काष्ठा falcon_spi_device *spi)
अणु
	स्थिर u8 unlock_mask = (SPI_STATUS_BP2 | SPI_STATUS_BP1 |
				SPI_STATUS_BP0);
	u8 status;
	पूर्णांक rc;

	rc = falcon_spi_cmd(efx, spi, SPI_RDSR, -1, शून्य,
			    &status, माप(status));
	अगर (rc)
		वापस rc;

	अगर (!(status & unlock_mask))
		वापस 0; /* alपढ़ोy unlocked */

	rc = falcon_spi_cmd(efx, spi, SPI_WREN, -1, शून्य, शून्य, 0);
	अगर (rc)
		वापस rc;
	rc = falcon_spi_cmd(efx, spi, SPI_SST_EWSR, -1, शून्य, शून्य, 0);
	अगर (rc)
		वापस rc;

	status &= ~unlock_mask;
	rc = falcon_spi_cmd(efx, spi, SPI_WRSR, -1, &status,
			    शून्य, माप(status));
	अगर (rc)
		वापस rc;
	rc = falcon_spi_रुको_ग_लिखो(efx, spi);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

#घोषणा FALCON_SPI_VERIFY_BUF_LEN 16

अटल पूर्णांक
falcon_spi_erase(काष्ठा falcon_mtd_partition *part, loff_t start, माप_प्रकार len)
अणु
	स्थिर काष्ठा falcon_spi_device *spi = part->spi;
	काष्ठा ef4_nic *efx = part->common.mtd.priv;
	अचिन्हित pos, block_len;
	u8 empty[FALCON_SPI_VERIFY_BUF_LEN];
	u8 buffer[FALCON_SPI_VERIFY_BUF_LEN];
	पूर्णांक rc;

	अगर (len != spi->erase_size)
		वापस -EINVAL;

	अगर (spi->erase_command == 0)
		वापस -EOPNOTSUPP;

	rc = falcon_spi_unlock(efx, spi);
	अगर (rc)
		वापस rc;
	rc = falcon_spi_cmd(efx, spi, SPI_WREN, -1, शून्य, शून्य, 0);
	अगर (rc)
		वापस rc;
	rc = falcon_spi_cmd(efx, spi, spi->erase_command, start, शून्य,
			    शून्य, 0);
	अगर (rc)
		वापस rc;
	rc = falcon_spi_slow_रुको(part, false);

	/* Verअगरy the entire region has been wiped */
	स_रखो(empty, 0xff, माप(empty));
	क्रम (pos = 0; pos < len; pos += block_len) अणु
		block_len = min(len - pos, माप(buffer));
		rc = falcon_spi_पढ़ो(efx, spi, start + pos, block_len,
				     शून्य, buffer);
		अगर (rc)
			वापस rc;
		अगर (स_भेद(empty, buffer, block_len))
			वापस -EIO;

		/* Aव्योम locking up the प्रणाली */
		cond_resched();
		अगर (संकेत_pending(current))
			वापस -EINTR;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम falcon_mtd_नाम(काष्ठा ef4_mtd_partition *part)
अणु
	काष्ठा ef4_nic *efx = part->mtd.priv;

	snम_लिखो(part->name, माप(part->name), "%s %s",
		 efx->name, part->type_name);
पूर्ण

अटल पूर्णांक falcon_mtd_पढ़ो(काष्ठा mtd_info *mtd, loff_t start,
			   माप_प्रकार len, माप_प्रकार *retlen, u8 *buffer)
अणु
	काष्ठा falcon_mtd_partition *part = to_falcon_mtd_partition(mtd);
	काष्ठा ef4_nic *efx = mtd->priv;
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

	rc = mutex_lock_पूर्णांकerruptible(&nic_data->spi_lock);
	अगर (rc)
		वापस rc;
	rc = falcon_spi_पढ़ो(efx, part->spi, part->offset + start,
			     len, retlen, buffer);
	mutex_unlock(&nic_data->spi_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक falcon_mtd_erase(काष्ठा mtd_info *mtd, loff_t start, माप_प्रकार len)
अणु
	काष्ठा falcon_mtd_partition *part = to_falcon_mtd_partition(mtd);
	काष्ठा ef4_nic *efx = mtd->priv;
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

	rc = mutex_lock_पूर्णांकerruptible(&nic_data->spi_lock);
	अगर (rc)
		वापस rc;
	rc = falcon_spi_erase(part, part->offset + start, len);
	mutex_unlock(&nic_data->spi_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक falcon_mtd_ग_लिखो(काष्ठा mtd_info *mtd, loff_t start,
			    माप_प्रकार len, माप_प्रकार *retlen, स्थिर u8 *buffer)
अणु
	काष्ठा falcon_mtd_partition *part = to_falcon_mtd_partition(mtd);
	काष्ठा ef4_nic *efx = mtd->priv;
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

	rc = mutex_lock_पूर्णांकerruptible(&nic_data->spi_lock);
	अगर (rc)
		वापस rc;
	rc = falcon_spi_ग_लिखो(efx, part->spi, part->offset + start,
			      len, retlen, buffer);
	mutex_unlock(&nic_data->spi_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक falcon_mtd_sync(काष्ठा mtd_info *mtd)
अणु
	काष्ठा falcon_mtd_partition *part = to_falcon_mtd_partition(mtd);
	काष्ठा ef4_nic *efx = mtd->priv;
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

	mutex_lock(&nic_data->spi_lock);
	rc = falcon_spi_slow_रुको(part, true);
	mutex_unlock(&nic_data->spi_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक falcon_mtd_probe(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	काष्ठा falcon_mtd_partition *parts;
	काष्ठा falcon_spi_device *spi;
	माप_प्रकार n_parts;
	पूर्णांक rc = -ENODEV;

	ASSERT_RTNL();

	/* Allocate space क्रम maximum number of partitions */
	parts = kसुस्मृति(2, माप(*parts), GFP_KERNEL);
	अगर (!parts)
		वापस -ENOMEM;
	n_parts = 0;

	spi = &nic_data->spi_flash;
	अगर (falcon_spi_present(spi) && spi->size > FALCON_FLASH_BOOTCODE_START) अणु
		parts[n_parts].spi = spi;
		parts[n_parts].offset = FALCON_FLASH_BOOTCODE_START;
		parts[n_parts].common.dev_type_name = "flash";
		parts[n_parts].common.type_name = "sfc_flash_bootrom";
		parts[n_parts].common.mtd.type = MTD_NORFLASH;
		parts[n_parts].common.mtd.flags = MTD_CAP_NORFLASH;
		parts[n_parts].common.mtd.size = spi->size - FALCON_FLASH_BOOTCODE_START;
		parts[n_parts].common.mtd.erasesize = spi->erase_size;
		n_parts++;
	पूर्ण

	spi = &nic_data->spi_eeprom;
	अगर (falcon_spi_present(spi) && spi->size > FALCON_EEPROM_BOOTCONFIG_START) अणु
		parts[n_parts].spi = spi;
		parts[n_parts].offset = FALCON_EEPROM_BOOTCONFIG_START;
		parts[n_parts].common.dev_type_name = "EEPROM";
		parts[n_parts].common.type_name = "sfc_bootconfig";
		parts[n_parts].common.mtd.type = MTD_RAM;
		parts[n_parts].common.mtd.flags = MTD_CAP_RAM;
		parts[n_parts].common.mtd.size =
			min(spi->size, FALCON_EEPROM_BOOTCONFIG_END) -
			FALCON_EEPROM_BOOTCONFIG_START;
		parts[n_parts].common.mtd.erasesize = spi->erase_size;
		n_parts++;
	पूर्ण

	rc = ef4_mtd_add(efx, &parts[0].common, n_parts, माप(*parts));
	अगर (rc)
		kमुक्त(parts);
	वापस rc;
पूर्ण

#पूर्ण_अगर /* CONFIG_SFC_FALCON_MTD */

/**************************************************************************
 *
 * XMAC operations
 *
 **************************************************************************
 */

/* Configure the XAUI driver that is an output from Falcon */
अटल व्योम falcon_setup_xaui(काष्ठा ef4_nic *efx)
अणु
	ef4_oword_t sdctl, txdrv;

	/* Move the XAUI पूर्णांकo low घातer, unless there is no PHY, in
	 * which हाल the XAUI will have to drive a cable. */
	अगर (efx->phy_type == PHY_TYPE_NONE)
		वापस;

	ef4_पढ़ोo(efx, &sdctl, FR_AB_XX_SD_CTL);
	EF4_SET_OWORD_FIELD(sdctl, FRF_AB_XX_HIDRVD, FFE_AB_XX_SD_CTL_DRV_DEF);
	EF4_SET_OWORD_FIELD(sdctl, FRF_AB_XX_LODRVD, FFE_AB_XX_SD_CTL_DRV_DEF);
	EF4_SET_OWORD_FIELD(sdctl, FRF_AB_XX_HIDRVC, FFE_AB_XX_SD_CTL_DRV_DEF);
	EF4_SET_OWORD_FIELD(sdctl, FRF_AB_XX_LODRVC, FFE_AB_XX_SD_CTL_DRV_DEF);
	EF4_SET_OWORD_FIELD(sdctl, FRF_AB_XX_HIDRVB, FFE_AB_XX_SD_CTL_DRV_DEF);
	EF4_SET_OWORD_FIELD(sdctl, FRF_AB_XX_LODRVB, FFE_AB_XX_SD_CTL_DRV_DEF);
	EF4_SET_OWORD_FIELD(sdctl, FRF_AB_XX_HIDRVA, FFE_AB_XX_SD_CTL_DRV_DEF);
	EF4_SET_OWORD_FIELD(sdctl, FRF_AB_XX_LODRVA, FFE_AB_XX_SD_CTL_DRV_DEF);
	ef4_ग_लिखोo(efx, &sdctl, FR_AB_XX_SD_CTL);

	EF4_POPULATE_OWORD_8(txdrv,
			     FRF_AB_XX_DEQD, FFE_AB_XX_TXDRV_DEQ_DEF,
			     FRF_AB_XX_DEQC, FFE_AB_XX_TXDRV_DEQ_DEF,
			     FRF_AB_XX_DEQB, FFE_AB_XX_TXDRV_DEQ_DEF,
			     FRF_AB_XX_DEQA, FFE_AB_XX_TXDRV_DEQ_DEF,
			     FRF_AB_XX_DTXD, FFE_AB_XX_TXDRV_DTX_DEF,
			     FRF_AB_XX_DTXC, FFE_AB_XX_TXDRV_DTX_DEF,
			     FRF_AB_XX_DTXB, FFE_AB_XX_TXDRV_DTX_DEF,
			     FRF_AB_XX_DTXA, FFE_AB_XX_TXDRV_DTX_DEF);
	ef4_ग_लिखोo(efx, &txdrv, FR_AB_XX_TXDRV_CTL);
पूर्ण

पूर्णांक falcon_reset_xaui(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	ef4_oword_t reg;
	पूर्णांक count;

	/* Don't fetch MAC statistics over an XMAC reset */
	WARN_ON(nic_data->stats_disable_count == 0);

	/* Start reset sequence */
	EF4_POPULATE_OWORD_1(reg, FRF_AB_XX_RST_XX_EN, 1);
	ef4_ग_लिखोo(efx, &reg, FR_AB_XX_PWR_RST);

	/* Wait up to 10 ms क्रम completion, then reinitialise */
	क्रम (count = 0; count < 1000; count++) अणु
		ef4_पढ़ोo(efx, &reg, FR_AB_XX_PWR_RST);
		अगर (EF4_OWORD_FIELD(reg, FRF_AB_XX_RST_XX_EN) == 0 &&
		    EF4_OWORD_FIELD(reg, FRF_AB_XX_SD_RST_ACT) == 0) अणु
			falcon_setup_xaui(efx);
			वापस 0;
		पूर्ण
		udelay(10);
	पूर्ण
	netअगर_err(efx, hw, efx->net_dev,
		  "timed out waiting for XAUI/XGXS reset\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम falcon_ack_status_पूर्णांकr(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	ef4_oword_t reg;

	अगर ((ef4_nic_rev(efx) != EF4_REV_FALCON_B0) || LOOPBACK_INTERNAL(efx))
		वापस;

	/* We expect xgmii faults अगर the wireside link is करोwn */
	अगर (!efx->link_state.up)
		वापस;

	/* We can only use this पूर्णांकerrupt to संकेत the negative edge of
	 * xaui_align [we have to poll the positive edge]. */
	अगर (nic_data->xmac_poll_required)
		वापस;

	ef4_पढ़ोo(efx, &reg, FR_AB_XM_MGT_INT_MSK);
पूर्ण

अटल bool falcon_xgxs_link_ok(काष्ठा ef4_nic *efx)
अणु
	ef4_oword_t reg;
	bool align_करोne, link_ok = false;
	पूर्णांक sync_status;

	/* Read link status */
	ef4_पढ़ोo(efx, &reg, FR_AB_XX_CORE_STAT);

	align_करोne = EF4_OWORD_FIELD(reg, FRF_AB_XX_ALIGN_DONE);
	sync_status = EF4_OWORD_FIELD(reg, FRF_AB_XX_SYNC_STAT);
	अगर (align_करोne && (sync_status == FFE_AB_XX_STAT_ALL_LANES))
		link_ok = true;

	/* Clear link status पढ़ोy क्रम next पढ़ो */
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_COMMA_DET, FFE_AB_XX_STAT_ALL_LANES);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_CHAR_ERR, FFE_AB_XX_STAT_ALL_LANES);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_DISPERR, FFE_AB_XX_STAT_ALL_LANES);
	ef4_ग_लिखोo(efx, &reg, FR_AB_XX_CORE_STAT);

	वापस link_ok;
पूर्ण

अटल bool falcon_xmac_link_ok(काष्ठा ef4_nic *efx)
अणु
	/*
	 * Check MAC's XGXS link status except when using XGMII loopback
	 * which bypasses the XGXS block.
	 * If possible, check PHY's XGXS link status except when using
	 * MAC loopback.
	 */
	वापस (efx->loopback_mode == LOOPBACK_XGMII ||
		falcon_xgxs_link_ok(efx)) &&
		(!(efx->mdio.mmds & (1 << MDIO_MMD_PHYXS)) ||
		 LOOPBACK_INTERNAL(efx) ||
		 ef4_mdio_phyxgxs_lane_sync(efx));
पूर्ण

अटल व्योम falcon_reconfigure_xmac_core(काष्ठा ef4_nic *efx)
अणु
	अचिन्हित पूर्णांक max_frame_len;
	ef4_oword_t reg;
	bool rx_fc = !!(efx->link_state.fc & EF4_FC_RX);
	bool tx_fc = !!(efx->link_state.fc & EF4_FC_TX);

	/* Configure MAC  - cut-thru mode is hard wired on */
	EF4_POPULATE_OWORD_3(reg,
			     FRF_AB_XM_RX_JUMBO_MODE, 1,
			     FRF_AB_XM_TX_STAT_EN, 1,
			     FRF_AB_XM_RX_STAT_EN, 1);
	ef4_ग_लिखोo(efx, &reg, FR_AB_XM_GLB_CFG);

	/* Configure TX */
	EF4_POPULATE_OWORD_6(reg,
			     FRF_AB_XM_TXEN, 1,
			     FRF_AB_XM_TX_PRMBL, 1,
			     FRF_AB_XM_AUTO_PAD, 1,
			     FRF_AB_XM_TXCRC, 1,
			     FRF_AB_XM_FCNTL, tx_fc,
			     FRF_AB_XM_IPG, 0x3);
	ef4_ग_लिखोo(efx, &reg, FR_AB_XM_TX_CFG);

	/* Configure RX */
	EF4_POPULATE_OWORD_5(reg,
			     FRF_AB_XM_RXEN, 1,
			     FRF_AB_XM_AUTO_DEPAD, 0,
			     FRF_AB_XM_ACPT_ALL_MCAST, 1,
			     FRF_AB_XM_ACPT_ALL_UCAST, !efx->unicast_filter,
			     FRF_AB_XM_PASS_CRC_ERR, 1);
	ef4_ग_लिखोo(efx, &reg, FR_AB_XM_RX_CFG);

	/* Set frame length */
	max_frame_len = EF4_MAX_FRAME_LEN(efx->net_dev->mtu);
	EF4_POPULATE_OWORD_1(reg, FRF_AB_XM_MAX_RX_FRM_SIZE, max_frame_len);
	ef4_ग_लिखोo(efx, &reg, FR_AB_XM_RX_PARAM);
	EF4_POPULATE_OWORD_2(reg,
			     FRF_AB_XM_MAX_TX_FRM_SIZE, max_frame_len,
			     FRF_AB_XM_TX_JUMBO_MODE, 1);
	ef4_ग_लिखोo(efx, &reg, FR_AB_XM_TX_PARAM);

	EF4_POPULATE_OWORD_2(reg,
			     FRF_AB_XM_PAUSE_TIME, 0xfffe, /* MAX PAUSE TIME */
			     FRF_AB_XM_DIS_FCNTL, !rx_fc);
	ef4_ग_लिखोo(efx, &reg, FR_AB_XM_FC);

	/* Set MAC address */
	स_नकल(&reg, &efx->net_dev->dev_addr[0], 4);
	ef4_ग_लिखोo(efx, &reg, FR_AB_XM_ADR_LO);
	स_नकल(&reg, &efx->net_dev->dev_addr[4], 2);
	ef4_ग_लिखोo(efx, &reg, FR_AB_XM_ADR_HI);
पूर्ण

अटल व्योम falcon_reconfigure_xgxs_core(काष्ठा ef4_nic *efx)
अणु
	ef4_oword_t reg;
	bool xgxs_loopback = (efx->loopback_mode == LOOPBACK_XGXS);
	bool xaui_loopback = (efx->loopback_mode == LOOPBACK_XAUI);
	bool xgmii_loopback = (efx->loopback_mode == LOOPBACK_XGMII);
	bool old_xgmii_loopback, old_xgxs_loopback, old_xaui_loopback;

	/* XGXS block is flaky and will need to be reset अगर moving
	 * पूर्णांकo our out of XGMII, XGXS or XAUI loopbacks. */
	ef4_पढ़ोo(efx, &reg, FR_AB_XX_CORE_STAT);
	old_xgxs_loopback = EF4_OWORD_FIELD(reg, FRF_AB_XX_XGXS_LB_EN);
	old_xgmii_loopback = EF4_OWORD_FIELD(reg, FRF_AB_XX_XGMII_LB_EN);

	ef4_पढ़ोo(efx, &reg, FR_AB_XX_SD_CTL);
	old_xaui_loopback = EF4_OWORD_FIELD(reg, FRF_AB_XX_LPBKA);

	/* The PHY driver may have turned XAUI off */
	अगर ((xgxs_loopback != old_xgxs_loopback) ||
	    (xaui_loopback != old_xaui_loopback) ||
	    (xgmii_loopback != old_xgmii_loopback))
		falcon_reset_xaui(efx);

	ef4_पढ़ोo(efx, &reg, FR_AB_XX_CORE_STAT);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_FORCE_SIG,
			    (xgxs_loopback || xaui_loopback) ?
			    FFE_AB_XX_FORCE_SIG_ALL_LANES : 0);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_XGXS_LB_EN, xgxs_loopback);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_XGMII_LB_EN, xgmii_loopback);
	ef4_ग_लिखोo(efx, &reg, FR_AB_XX_CORE_STAT);

	ef4_पढ़ोo(efx, &reg, FR_AB_XX_SD_CTL);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_LPBKD, xaui_loopback);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_LPBKC, xaui_loopback);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_LPBKB, xaui_loopback);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_XX_LPBKA, xaui_loopback);
	ef4_ग_लिखोo(efx, &reg, FR_AB_XX_SD_CTL);
पूर्ण


/* Try to bring up the Falcon side of the Falcon-Phy XAUI link */
अटल bool falcon_xmac_link_ok_retry(काष्ठा ef4_nic *efx, पूर्णांक tries)
अणु
	bool mac_up = falcon_xmac_link_ok(efx);

	अगर (LOOPBACK_MASK(efx) & LOOPBACKS_EXTERNAL(efx) & LOOPBACKS_WS ||
	    ef4_phy_mode_disabled(efx->phy_mode))
		/* XAUI link is expected to be करोwn */
		वापस mac_up;

	falcon_stop_nic_stats(efx);

	जबतक (!mac_up && tries) अणु
		netअगर_dbg(efx, hw, efx->net_dev, "bashing xaui\n");
		falcon_reset_xaui(efx);
		udelay(200);

		mac_up = falcon_xmac_link_ok(efx);
		--tries;
	पूर्ण

	falcon_start_nic_stats(efx);

	वापस mac_up;
पूर्ण

अटल bool falcon_xmac_check_fault(काष्ठा ef4_nic *efx)
अणु
	वापस !falcon_xmac_link_ok_retry(efx, 5);
पूर्ण

अटल पूर्णांक falcon_reconfigure_xmac(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;

	ef4_farch_filter_sync_rx_mode(efx);

	falcon_reconfigure_xgxs_core(efx);
	falcon_reconfigure_xmac_core(efx);

	falcon_reconfigure_mac_wrapper(efx);

	nic_data->xmac_poll_required = !falcon_xmac_link_ok_retry(efx, 5);
	falcon_ack_status_पूर्णांकr(efx);

	वापस 0;
पूर्ण

अटल व्योम falcon_poll_xmac(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;

	/* We expect xgmii faults अगर the wireside link is करोwn */
	अगर (!efx->link_state.up || !nic_data->xmac_poll_required)
		वापस;

	nic_data->xmac_poll_required = !falcon_xmac_link_ok_retry(efx, 1);
	falcon_ack_status_पूर्णांकr(efx);
पूर्ण

/**************************************************************************
 *
 * MAC wrapper
 *
 **************************************************************************
 */

अटल व्योम falcon_push_multicast_hash(काष्ठा ef4_nic *efx)
अणु
	जोड़ ef4_multicast_hash *mc_hash = &efx->multicast_hash;

	WARN_ON(!mutex_is_locked(&efx->mac_lock));

	ef4_ग_लिखोo(efx, &mc_hash->oword[0], FR_AB_MAC_MC_HASH_REG0);
	ef4_ग_लिखोo(efx, &mc_hash->oword[1], FR_AB_MAC_MC_HASH_REG1);
पूर्ण

अटल व्योम falcon_reset_macs(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	ef4_oword_t reg, mac_ctrl;
	पूर्णांक count;

	अगर (ef4_nic_rev(efx) < EF4_REV_FALCON_B0) अणु
		/* It's not safe to use GLB_CTL_REG to reset the
		 * macs, so instead use the पूर्णांकernal MAC resets
		 */
		EF4_POPULATE_OWORD_1(reg, FRF_AB_XM_CORE_RST, 1);
		ef4_ग_लिखोo(efx, &reg, FR_AB_XM_GLB_CFG);

		क्रम (count = 0; count < 10000; count++) अणु
			ef4_पढ़ोo(efx, &reg, FR_AB_XM_GLB_CFG);
			अगर (EF4_OWORD_FIELD(reg, FRF_AB_XM_CORE_RST) ==
			    0)
				वापस;
			udelay(10);
		पूर्ण

		netअगर_err(efx, hw, efx->net_dev,
			  "timed out waiting for XMAC core reset\n");
	पूर्ण

	/* Mac stats will fail whist the TX fअगरo is draining */
	WARN_ON(nic_data->stats_disable_count == 0);

	ef4_पढ़ोo(efx, &mac_ctrl, FR_AB_MAC_CTRL);
	EF4_SET_OWORD_FIELD(mac_ctrl, FRF_BB_TXFIFO_DRAIN_EN, 1);
	ef4_ग_लिखोo(efx, &mac_ctrl, FR_AB_MAC_CTRL);

	ef4_पढ़ोo(efx, &reg, FR_AB_GLB_CTL);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_RST_XGTX, 1);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_RST_XGRX, 1);
	EF4_SET_OWORD_FIELD(reg, FRF_AB_RST_EM, 1);
	ef4_ग_लिखोo(efx, &reg, FR_AB_GLB_CTL);

	count = 0;
	जबतक (1) अणु
		ef4_पढ़ोo(efx, &reg, FR_AB_GLB_CTL);
		अगर (!EF4_OWORD_FIELD(reg, FRF_AB_RST_XGTX) &&
		    !EF4_OWORD_FIELD(reg, FRF_AB_RST_XGRX) &&
		    !EF4_OWORD_FIELD(reg, FRF_AB_RST_EM)) अणु
			netअगर_dbg(efx, hw, efx->net_dev,
				  "Completed MAC reset after %d loops\n",
				  count);
			अवरोध;
		पूर्ण
		अगर (count > 20) अणु
			netअगर_err(efx, hw, efx->net_dev, "MAC reset failed\n");
			अवरोध;
		पूर्ण
		count++;
		udelay(10);
	पूर्ण

	/* Ensure the correct MAC is selected beक्रमe statistics
	 * are re-enabled by the caller */
	ef4_ग_लिखोo(efx, &mac_ctrl, FR_AB_MAC_CTRL);

	falcon_setup_xaui(efx);
पूर्ण

अटल व्योम falcon_drain_tx_fअगरo(काष्ठा ef4_nic *efx)
अणु
	ef4_oword_t reg;

	अगर ((ef4_nic_rev(efx) < EF4_REV_FALCON_B0) ||
	    (efx->loopback_mode != LOOPBACK_NONE))
		वापस;

	ef4_पढ़ोo(efx, &reg, FR_AB_MAC_CTRL);
	/* There is no poपूर्णांक in draining more than once */
	अगर (EF4_OWORD_FIELD(reg, FRF_BB_TXFIFO_DRAIN_EN))
		वापस;

	falcon_reset_macs(efx);
पूर्ण

अटल व्योम falcon_deconfigure_mac_wrapper(काष्ठा ef4_nic *efx)
अणु
	ef4_oword_t reg;

	अगर (ef4_nic_rev(efx) < EF4_REV_FALCON_B0)
		वापस;

	/* Isolate the MAC -> RX */
	ef4_पढ़ोo(efx, &reg, FR_AZ_RX_CFG);
	EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_INGR_EN, 0);
	ef4_ग_लिखोo(efx, &reg, FR_AZ_RX_CFG);

	/* Isolate TX -> MAC */
	falcon_drain_tx_fअगरo(efx);
पूर्ण

अटल व्योम falcon_reconfigure_mac_wrapper(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_link_state *link_state = &efx->link_state;
	ef4_oword_t reg;
	पूर्णांक link_speed, isolate;

	isolate = !!READ_ONCE(efx->reset_pending);

	चयन (link_state->speed) अणु
	हाल 10000: link_speed = 3; अवरोध;
	हाल 1000:  link_speed = 2; अवरोध;
	हाल 100:   link_speed = 1; अवरोध;
	शेष:    link_speed = 0; अवरोध;
	पूर्ण

	/* MAC_LINK_STATUS controls MAC backpressure but करोesn't work
	 * as advertised.  Disable to ensure packets are not
	 * indefinitely held and TX queue can be flushed at any poपूर्णांक
	 * जबतक the link is करोwn. */
	EF4_POPULATE_OWORD_5(reg,
			     FRF_AB_MAC_XOFF_VAL, 0xffff /* max छोड़ो समय */,
			     FRF_AB_MAC_BCAD_ACPT, 1,
			     FRF_AB_MAC_UC_PROM, !efx->unicast_filter,
			     FRF_AB_MAC_LINK_STATUS, 1, /* always set */
			     FRF_AB_MAC_SPEED, link_speed);
	/* On B0, MAC backpressure can be disabled and packets get
	 * discarded. */
	अगर (ef4_nic_rev(efx) >= EF4_REV_FALCON_B0) अणु
		EF4_SET_OWORD_FIELD(reg, FRF_BB_TXFIFO_DRAIN_EN,
				    !link_state->up || isolate);
	पूर्ण

	ef4_ग_लिखोo(efx, &reg, FR_AB_MAC_CTRL);

	/* Restore the multicast hash रेजिस्टरs. */
	falcon_push_multicast_hash(efx);

	ef4_पढ़ोo(efx, &reg, FR_AZ_RX_CFG);
	/* Enable XOFF संकेत from RX FIFO (we enabled it during NIC
	 * initialisation but it may पढ़ो back as 0) */
	EF4_SET_OWORD_FIELD(reg, FRF_AZ_RX_XOFF_MAC_EN, 1);
	/* Unisolate the MAC -> RX */
	अगर (ef4_nic_rev(efx) >= EF4_REV_FALCON_B0)
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_INGR_EN, !isolate);
	ef4_ग_लिखोo(efx, &reg, FR_AZ_RX_CFG);
पूर्ण

अटल व्योम falcon_stats_request(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	ef4_oword_t reg;

	WARN_ON(nic_data->stats_pending);
	WARN_ON(nic_data->stats_disable_count);

	FALCON_XMAC_STATS_DMA_FLAG(efx) = 0;
	nic_data->stats_pending = true;
	wmb(); /* ensure करोne flag is clear */

	/* Initiate DMA transfer of stats */
	EF4_POPULATE_OWORD_2(reg,
			     FRF_AB_MAC_STAT_DMA_CMD, 1,
			     FRF_AB_MAC_STAT_DMA_ADR,
			     efx->stats_buffer.dma_addr);
	ef4_ग_लिखोo(efx, &reg, FR_AB_MAC_STAT_DMA);

	mod_समयr(&nic_data->stats_समयr, round_jअगरfies_up(jअगरfies + HZ / 2));
पूर्ण

अटल व्योम falcon_stats_complete(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;

	अगर (!nic_data->stats_pending)
		वापस;

	nic_data->stats_pending = false;
	अगर (FALCON_XMAC_STATS_DMA_FLAG(efx)) अणु
		rmb(); /* पढ़ो the करोne flag beक्रमe the stats */
		ef4_nic_update_stats(falcon_stat_desc, FALCON_STAT_COUNT,
				     falcon_stat_mask, nic_data->stats,
				     efx->stats_buffer.addr, true);
	पूर्ण अन्यथा अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "timed out waiting for statistics\n");
	पूर्ण
पूर्ण

अटल व्योम falcon_stats_समयr_func(काष्ठा समयr_list *t)
अणु
	काष्ठा falcon_nic_data *nic_data = from_समयr(nic_data, t,
						      stats_समयr);
	काष्ठा ef4_nic *efx = nic_data->efx;

	spin_lock(&efx->stats_lock);

	falcon_stats_complete(efx);
	अगर (nic_data->stats_disable_count == 0)
		falcon_stats_request(efx);

	spin_unlock(&efx->stats_lock);
पूर्ण

अटल bool falcon_loopback_link_poll(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_link_state old_state = efx->link_state;

	WARN_ON(!mutex_is_locked(&efx->mac_lock));
	WARN_ON(!LOOPBACK_INTERNAL(efx));

	efx->link_state.fd = true;
	efx->link_state.fc = efx->wanted_fc;
	efx->link_state.up = true;
	efx->link_state.speed = 10000;

	वापस !ef4_link_state_equal(&efx->link_state, &old_state);
पूर्ण

अटल पूर्णांक falcon_reconfigure_port(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;

	WARN_ON(ef4_nic_rev(efx) > EF4_REV_FALCON_B0);

	/* Poll the PHY link state *beक्रमe* reconfiguring it. This means we
	 * will pick up the correct speed (in loopback) to select the correct
	 * MAC.
	 */
	अगर (LOOPBACK_INTERNAL(efx))
		falcon_loopback_link_poll(efx);
	अन्यथा
		efx->phy_op->poll(efx);

	falcon_stop_nic_stats(efx);
	falcon_deconfigure_mac_wrapper(efx);

	falcon_reset_macs(efx);

	efx->phy_op->reconfigure(efx);
	rc = falcon_reconfigure_xmac(efx);
	BUG_ON(rc);

	falcon_start_nic_stats(efx);

	/* Synchronise efx->link_state with the kernel */
	ef4_link_status_changed(efx);

	वापस 0;
पूर्ण

/* TX flow control may स्वतःmatically turn itself off अगर the link
 * partner (पूर्णांकermittently) stops responding to छोड़ो frames. There
 * isn't any indication that this has happened, so the best we करो is
 * leave it up to the user to spot this and fix it by cycling transmit
 * flow control on this end.
 */

अटल व्योम falcon_a1_prepare_enable_fc_tx(काष्ठा ef4_nic *efx)
अणु
	/* Schedule a reset to recover */
	ef4_schedule_reset(efx, RESET_TYPE_INVISIBLE);
पूर्ण

अटल व्योम falcon_b0_prepare_enable_fc_tx(काष्ठा ef4_nic *efx)
अणु
	/* Recover by resetting the EM block */
	falcon_stop_nic_stats(efx);
	falcon_drain_tx_fअगरo(efx);
	falcon_reconfigure_xmac(efx);
	falcon_start_nic_stats(efx);
पूर्ण

/**************************************************************************
 *
 * PHY access via GMII
 *
 **************************************************************************
 */

/* Wait क्रम GMII access to complete */
अटल पूर्णांक falcon_gmii_रुको(काष्ठा ef4_nic *efx)
अणु
	ef4_oword_t md_stat;
	पूर्णांक count;

	/* रुको up to 50ms - taken max from datasheet */
	क्रम (count = 0; count < 5000; count++) अणु
		ef4_पढ़ोo(efx, &md_stat, FR_AB_MD_STAT);
		अगर (EF4_OWORD_FIELD(md_stat, FRF_AB_MD_BSY) == 0) अणु
			अगर (EF4_OWORD_FIELD(md_stat, FRF_AB_MD_LNFL) != 0 ||
			    EF4_OWORD_FIELD(md_stat, FRF_AB_MD_BSERR) != 0) अणु
				netअगर_err(efx, hw, efx->net_dev,
					  "error from GMII access "
					  EF4_OWORD_FMT"\n",
					  EF4_OWORD_VAL(md_stat));
				वापस -EIO;
			पूर्ण
			वापस 0;
		पूर्ण
		udelay(10);
	पूर्ण
	netअगर_err(efx, hw, efx->net_dev, "timed out waiting for GMII\n");
	वापस -ETIMEDOUT;
पूर्ण

/* Write an MDIO रेजिस्टर of a PHY connected to Falcon. */
अटल पूर्णांक falcon_mdio_ग_लिखो(काष्ठा net_device *net_dev,
			     पूर्णांक prtad, पूर्णांक devad, u16 addr, u16 value)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	ef4_oword_t reg;
	पूर्णांक rc;

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "writing MDIO %d register %d.%d with 0x%04x\n",
		    prtad, devad, addr, value);

	mutex_lock(&nic_data->mdio_lock);

	/* Check MDIO not currently being accessed */
	rc = falcon_gmii_रुको(efx);
	अगर (rc)
		जाओ out;

	/* Write the address/ID रेजिस्टर */
	EF4_POPULATE_OWORD_1(reg, FRF_AB_MD_PHY_ADR, addr);
	ef4_ग_लिखोo(efx, &reg, FR_AB_MD_PHY_ADR);

	EF4_POPULATE_OWORD_2(reg, FRF_AB_MD_PRT_ADR, prtad,
			     FRF_AB_MD_DEV_ADR, devad);
	ef4_ग_लिखोo(efx, &reg, FR_AB_MD_ID);

	/* Write data */
	EF4_POPULATE_OWORD_1(reg, FRF_AB_MD_TXD, value);
	ef4_ग_लिखोo(efx, &reg, FR_AB_MD_TXD);

	EF4_POPULATE_OWORD_2(reg,
			     FRF_AB_MD_WRC, 1,
			     FRF_AB_MD_GC, 0);
	ef4_ग_लिखोo(efx, &reg, FR_AB_MD_CS);

	/* Wait क्रम data to be written */
	rc = falcon_gmii_रुको(efx);
	अगर (rc) अणु
		/* Abort the ग_लिखो operation */
		EF4_POPULATE_OWORD_2(reg,
				     FRF_AB_MD_WRC, 0,
				     FRF_AB_MD_GC, 1);
		ef4_ग_लिखोo(efx, &reg, FR_AB_MD_CS);
		udelay(10);
	पूर्ण

out:
	mutex_unlock(&nic_data->mdio_lock);
	वापस rc;
पूर्ण

/* Read an MDIO रेजिस्टर of a PHY connected to Falcon. */
अटल पूर्णांक falcon_mdio_पढ़ो(काष्ठा net_device *net_dev,
			    पूर्णांक prtad, पूर्णांक devad, u16 addr)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	ef4_oword_t reg;
	पूर्णांक rc;

	mutex_lock(&nic_data->mdio_lock);

	/* Check MDIO not currently being accessed */
	rc = falcon_gmii_रुको(efx);
	अगर (rc)
		जाओ out;

	EF4_POPULATE_OWORD_1(reg, FRF_AB_MD_PHY_ADR, addr);
	ef4_ग_लिखोo(efx, &reg, FR_AB_MD_PHY_ADR);

	EF4_POPULATE_OWORD_2(reg, FRF_AB_MD_PRT_ADR, prtad,
			     FRF_AB_MD_DEV_ADR, devad);
	ef4_ग_लिखोo(efx, &reg, FR_AB_MD_ID);

	/* Request data to be पढ़ो */
	EF4_POPULATE_OWORD_2(reg, FRF_AB_MD_RDC, 1, FRF_AB_MD_GC, 0);
	ef4_ग_लिखोo(efx, &reg, FR_AB_MD_CS);

	/* Wait क्रम data to become available */
	rc = falcon_gmii_रुको(efx);
	अगर (rc == 0) अणु
		ef4_पढ़ोo(efx, &reg, FR_AB_MD_RXD);
		rc = EF4_OWORD_FIELD(reg, FRF_AB_MD_RXD);
		netअगर_vdbg(efx, hw, efx->net_dev,
			   "read from MDIO %d register %d.%d, got %04x\n",
			   prtad, devad, addr, rc);
	पूर्ण अन्यथा अणु
		/* Abort the पढ़ो operation */
		EF4_POPULATE_OWORD_2(reg,
				     FRF_AB_MD_RIC, 0,
				     FRF_AB_MD_GC, 1);
		ef4_ग_लिखोo(efx, &reg, FR_AB_MD_CS);

		netअगर_dbg(efx, hw, efx->net_dev,
			  "read from MDIO %d register %d.%d, got error %d\n",
			  prtad, devad, addr, rc);
	पूर्ण

out:
	mutex_unlock(&nic_data->mdio_lock);
	वापस rc;
पूर्ण

/* This call is responsible क्रम hooking in the MAC and PHY operations */
अटल पूर्णांक falcon_probe_port(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

	चयन (efx->phy_type) अणु
	हाल PHY_TYPE_SFX7101:
		efx->phy_op = &falcon_sfx7101_phy_ops;
		अवरोध;
	हाल PHY_TYPE_QT2022C2:
	हाल PHY_TYPE_QT2025C:
		efx->phy_op = &falcon_qt202x_phy_ops;
		अवरोध;
	हाल PHY_TYPE_TXC43128:
		efx->phy_op = &falcon_txc_phy_ops;
		अवरोध;
	शेष:
		netअगर_err(efx, probe, efx->net_dev, "Unknown PHY type %d\n",
			  efx->phy_type);
		वापस -ENODEV;
	पूर्ण

	/* Fill out MDIO काष्ठाure and loopback modes */
	mutex_init(&nic_data->mdio_lock);
	efx->mdio.mdio_पढ़ो = falcon_mdio_पढ़ो;
	efx->mdio.mdio_ग_लिखो = falcon_mdio_ग_लिखो;
	rc = efx->phy_op->probe(efx);
	अगर (rc != 0)
		वापस rc;

	/* Initial assumption */
	efx->link_state.speed = 10000;
	efx->link_state.fd = true;

	/* Hardware flow ctrl. FalconA RX FIFO too small क्रम छोड़ो generation */
	अगर (ef4_nic_rev(efx) >= EF4_REV_FALCON_B0)
		efx->wanted_fc = EF4_FC_RX | EF4_FC_TX;
	अन्यथा
		efx->wanted_fc = EF4_FC_RX;
	अगर (efx->mdio.mmds & MDIO_DEVS_AN)
		efx->wanted_fc |= EF4_FC_AUTO;

	/* Allocate buffer क्रम stats */
	rc = ef4_nic_alloc_buffer(efx, &efx->stats_buffer,
				  FALCON_MAC_STATS_SIZE, GFP_KERNEL);
	अगर (rc)
		वापस rc;
	netअगर_dbg(efx, probe, efx->net_dev,
		  "stats buffer at %llx (virt %p phys %llx)\n",
		  (u64)efx->stats_buffer.dma_addr,
		  efx->stats_buffer.addr,
		  (u64)virt_to_phys(efx->stats_buffer.addr));

	वापस 0;
पूर्ण

अटल व्योम falcon_हटाओ_port(काष्ठा ef4_nic *efx)
अणु
	efx->phy_op->हटाओ(efx);
	ef4_nic_मुक्त_buffer(efx, &efx->stats_buffer);
पूर्ण

/* Global events are basically PHY events */
अटल bool
falcon_handle_global_event(काष्ठा ef4_channel *channel, ef4_qword_t *event)
अणु
	काष्ठा ef4_nic *efx = channel->efx;
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;

	अगर (EF4_QWORD_FIELD(*event, FSF_AB_GLB_EV_G_PHY0_INTR) ||
	    EF4_QWORD_FIELD(*event, FSF_AB_GLB_EV_XG_PHY0_INTR) ||
	    EF4_QWORD_FIELD(*event, FSF_AB_GLB_EV_XFP_PHY0_INTR))
		/* Ignored */
		वापस true;

	अगर ((ef4_nic_rev(efx) == EF4_REV_FALCON_B0) &&
	    EF4_QWORD_FIELD(*event, FSF_BB_GLB_EV_XG_MGT_INTR)) अणु
		nic_data->xmac_poll_required = true;
		वापस true;
	पूर्ण

	अगर (ef4_nic_rev(efx) <= EF4_REV_FALCON_A1 ?
	    EF4_QWORD_FIELD(*event, FSF_AA_GLB_EV_RX_RECOVERY) :
	    EF4_QWORD_FIELD(*event, FSF_BB_GLB_EV_RX_RECOVERY)) अणु
		netअगर_err(efx, rx_err, efx->net_dev,
			  "channel %d seen global RX_RESET event. Resetting.\n",
			  channel->channel);

		atomic_inc(&efx->rx_reset);
		ef4_schedule_reset(efx, EF4_WORKAROUND_6555(efx) ?
				   RESET_TYPE_RX_RECOVERY : RESET_TYPE_DISABLE);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**************************************************************************
 *
 * Falcon test code
 *
 **************************************************************************/

अटल पूर्णांक
falcon_पढ़ो_nvram(काष्ठा ef4_nic *efx, काष्ठा falcon_nvconfig *nvconfig_out)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	काष्ठा falcon_nvconfig *nvconfig;
	काष्ठा falcon_spi_device *spi;
	व्योम *region;
	पूर्णांक rc, magic_num, काष्ठा_ver;
	__le16 *word, *limit;
	u32 csum;

	अगर (falcon_spi_present(&nic_data->spi_flash))
		spi = &nic_data->spi_flash;
	अन्यथा अगर (falcon_spi_present(&nic_data->spi_eeprom))
		spi = &nic_data->spi_eeprom;
	अन्यथा
		वापस -EINVAL;

	region = kदो_स्मृति(FALCON_NVCONFIG_END, GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;
	nvconfig = region + FALCON_NVCONFIG_OFFSET;

	mutex_lock(&nic_data->spi_lock);
	rc = falcon_spi_पढ़ो(efx, spi, 0, FALCON_NVCONFIG_END, शून्य, region);
	mutex_unlock(&nic_data->spi_lock);
	अगर (rc) अणु
		netअगर_err(efx, hw, efx->net_dev, "Failed to read %s\n",
			  falcon_spi_present(&nic_data->spi_flash) ?
			  "flash" : "EEPROM");
		rc = -EIO;
		जाओ out;
	पूर्ण

	magic_num = le16_to_cpu(nvconfig->board_magic_num);
	काष्ठा_ver = le16_to_cpu(nvconfig->board_काष्ठा_ver);

	rc = -EINVAL;
	अगर (magic_num != FALCON_NVCONFIG_BOARD_MAGIC_NUM) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "NVRAM bad magic 0x%x\n", magic_num);
		जाओ out;
	पूर्ण
	अगर (काष्ठा_ver < 2) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "NVRAM has ancient version 0x%x\n", काष्ठा_ver);
		जाओ out;
	पूर्ण अन्यथा अगर (काष्ठा_ver < 4) अणु
		word = &nvconfig->board_magic_num;
		limit = (__le16 *) (nvconfig + 1);
	पूर्ण अन्यथा अणु
		word = region;
		limit = region + FALCON_NVCONFIG_END;
	पूर्ण
	क्रम (csum = 0; word < limit; ++word)
		csum += le16_to_cpu(*word);

	अगर (~csum & 0xffff) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "NVRAM has incorrect checksum\n");
		जाओ out;
	पूर्ण

	rc = 0;
	अगर (nvconfig_out)
		स_नकल(nvconfig_out, nvconfig, माप(*nvconfig));

 out:
	kमुक्त(region);
	वापस rc;
पूर्ण

अटल पूर्णांक falcon_test_nvram(काष्ठा ef4_nic *efx)
अणु
	वापस falcon_पढ़ो_nvram(efx, शून्य);
पूर्ण

अटल स्थिर काष्ठा ef4_farch_रेजिस्टर_test falcon_b0_रेजिस्टर_tests[] = अणु
	अणु FR_AZ_ADR_REGION,
	  EF4_OWORD32(0x0003FFFF, 0x0003FFFF, 0x0003FFFF, 0x0003FFFF) पूर्ण,
	अणु FR_AZ_RX_CFG,
	  EF4_OWORD32(0xFFFFFFFE, 0x00017FFF, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AZ_TX_CFG,
	  EF4_OWORD32(0x7FFF0037, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AZ_TX_RESERVED,
	  EF4_OWORD32(0xFFFEFE80, 0x1FFFFFFF, 0x020000FE, 0x007FFFFF) पूर्ण,
	अणु FR_AB_MAC_CTRL,
	  EF4_OWORD32(0xFFFF0000, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AZ_SRM_TX_DC_CFG,
	  EF4_OWORD32(0x001FFFFF, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AZ_RX_DC_CFG,
	  EF4_OWORD32(0x0000000F, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AZ_RX_DC_PF_WM,
	  EF4_OWORD32(0x000003FF, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_BZ_DP_CTRL,
	  EF4_OWORD32(0x00000FFF, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AB_GM_CFG2,
	  EF4_OWORD32(0x00007337, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AB_GMF_CFG0,
	  EF4_OWORD32(0x00001F1F, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AB_XM_GLB_CFG,
	  EF4_OWORD32(0x00000C68, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AB_XM_TX_CFG,
	  EF4_OWORD32(0x00080164, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AB_XM_RX_CFG,
	  EF4_OWORD32(0x07100A0C, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AB_XM_RX_PARAM,
	  EF4_OWORD32(0x00001FF8, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AB_XM_FC,
	  EF4_OWORD32(0xFFFF0001, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AB_XM_ADR_LO,
	  EF4_OWORD32(0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
	अणु FR_AB_XX_SD_CTL,
	  EF4_OWORD32(0x0003FF0F, 0x00000000, 0x00000000, 0x00000000) पूर्ण,
पूर्ण;

अटल पूर्णांक
falcon_b0_test_chip(काष्ठा ef4_nic *efx, काष्ठा ef4_self_tests *tests)
अणु
	क्रमागत reset_type reset_method = RESET_TYPE_INVISIBLE;
	पूर्णांक rc, rc2;

	mutex_lock(&efx->mac_lock);
	अगर (efx->loopback_modes) अणु
		/* We need the 312 घड़ी from the PHY to test the XMAC
		 * रेजिस्टरs, so move पूर्णांकo XGMII loopback अगर available */
		अगर (efx->loopback_modes & (1 << LOOPBACK_XGMII))
			efx->loopback_mode = LOOPBACK_XGMII;
		अन्यथा
			efx->loopback_mode = __ffs(efx->loopback_modes);
	पूर्ण
	__ef4_reconfigure_port(efx);
	mutex_unlock(&efx->mac_lock);

	ef4_reset_करोwn(efx, reset_method);

	tests->रेजिस्टरs =
		ef4_farch_test_रेजिस्टरs(efx, falcon_b0_रेजिस्टर_tests,
					 ARRAY_SIZE(falcon_b0_रेजिस्टर_tests))
		? -1 : 1;

	rc = falcon_reset_hw(efx, reset_method);
	rc2 = ef4_reset_up(efx, reset_method, rc == 0);
	वापस rc ? rc : rc2;
पूर्ण

/**************************************************************************
 *
 * Device reset
 *
 **************************************************************************
 */

अटल क्रमागत reset_type falcon_map_reset_reason(क्रमागत reset_type reason)
अणु
	चयन (reason) अणु
	हाल RESET_TYPE_RX_RECOVERY:
	हाल RESET_TYPE_DMA_ERROR:
	हाल RESET_TYPE_TX_SKIP:
		/* These can occasionally occur due to hardware bugs.
		 * We try to reset without disrupting the link.
		 */
		वापस RESET_TYPE_INVISIBLE;
	शेष:
		वापस RESET_TYPE_ALL;
	पूर्ण
पूर्ण

अटल पूर्णांक falcon_map_reset_flags(u32 *flags)
अणु
	क्रमागत अणु
		FALCON_RESET_INVISIBLE = (ETH_RESET_DMA | ETH_RESET_FILTER |
					  ETH_RESET_OFFLOAD | ETH_RESET_MAC),
		FALCON_RESET_ALL = FALCON_RESET_INVISIBLE | ETH_RESET_PHY,
		FALCON_RESET_WORLD = FALCON_RESET_ALL | ETH_RESET_IRQ,
	पूर्ण;

	अगर ((*flags & FALCON_RESET_WORLD) == FALCON_RESET_WORLD) अणु
		*flags &= ~FALCON_RESET_WORLD;
		वापस RESET_TYPE_WORLD;
	पूर्ण

	अगर ((*flags & FALCON_RESET_ALL) == FALCON_RESET_ALL) अणु
		*flags &= ~FALCON_RESET_ALL;
		वापस RESET_TYPE_ALL;
	पूर्ण

	अगर ((*flags & FALCON_RESET_INVISIBLE) == FALCON_RESET_INVISIBLE) अणु
		*flags &= ~FALCON_RESET_INVISIBLE;
		वापस RESET_TYPE_INVISIBLE;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Resets NIC to known state.  This routine must be called in process
 * context and is allowed to sleep. */
अटल पूर्णांक __falcon_reset_hw(काष्ठा ef4_nic *efx, क्रमागत reset_type method)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	ef4_oword_t glb_ctl_reg_ker;
	पूर्णांक rc;

	netअगर_dbg(efx, hw, efx->net_dev, "performing %s hardware reset\n",
		  RESET_TYPE(method));

	/* Initiate device reset */
	अगर (method == RESET_TYPE_WORLD) अणु
		rc = pci_save_state(efx->pci_dev);
		अगर (rc) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "failed to backup PCI state of primary "
				  "function prior to hardware reset\n");
			जाओ fail1;
		पूर्ण
		अगर (ef4_nic_is_dual_func(efx)) अणु
			rc = pci_save_state(nic_data->pci_dev2);
			अगर (rc) अणु
				netअगर_err(efx, drv, efx->net_dev,
					  "failed to backup PCI state of "
					  "secondary function prior to "
					  "hardware reset\n");
				जाओ fail2;
			पूर्ण
		पूर्ण

		EF4_POPULATE_OWORD_2(glb_ctl_reg_ker,
				     FRF_AB_EXT_PHY_RST_DUR,
				     FFE_AB_EXT_PHY_RST_DUR_10240US,
				     FRF_AB_SWRST, 1);
	पूर्ण अन्यथा अणु
		EF4_POPULATE_OWORD_7(glb_ctl_reg_ker,
				     /* exclude PHY from "invisible" reset */
				     FRF_AB_EXT_PHY_RST_CTL,
				     method == RESET_TYPE_INVISIBLE,
				     /* exclude EEPROM/flash and PCIe */
				     FRF_AB_PCIE_CORE_RST_CTL, 1,
				     FRF_AB_PCIE_NSTKY_RST_CTL, 1,
				     FRF_AB_PCIE_SD_RST_CTL, 1,
				     FRF_AB_EE_RST_CTL, 1,
				     FRF_AB_EXT_PHY_RST_DUR,
				     FFE_AB_EXT_PHY_RST_DUR_10240US,
				     FRF_AB_SWRST, 1);
	पूर्ण
	ef4_ग_लिखोo(efx, &glb_ctl_reg_ker, FR_AB_GLB_CTL);

	netअगर_dbg(efx, hw, efx->net_dev, "waiting for hardware reset\n");
	schedule_समयout_unपूर्णांकerruptible(HZ / 20);

	/* Restore PCI configuration अगर needed */
	अगर (method == RESET_TYPE_WORLD) अणु
		अगर (ef4_nic_is_dual_func(efx))
			pci_restore_state(nic_data->pci_dev2);
		pci_restore_state(efx->pci_dev);
		netअगर_dbg(efx, drv, efx->net_dev,
			  "successfully restored PCI config\n");
	पूर्ण

	/* Assert that reset complete */
	ef4_पढ़ोo(efx, &glb_ctl_reg_ker, FR_AB_GLB_CTL);
	अगर (EF4_OWORD_FIELD(glb_ctl_reg_ker, FRF_AB_SWRST) != 0) अणु
		rc = -ETIMEDOUT;
		netअगर_err(efx, hw, efx->net_dev,
			  "timed out waiting for hardware reset\n");
		जाओ fail3;
	पूर्ण
	netअगर_dbg(efx, hw, efx->net_dev, "hardware reset complete\n");

	वापस 0;

	/* pci_save_state() and pci_restore_state() MUST be called in pairs */
fail2:
	pci_restore_state(efx->pci_dev);
fail1:
fail3:
	वापस rc;
पूर्ण

अटल पूर्णांक falcon_reset_hw(काष्ठा ef4_nic *efx, क्रमागत reset_type method)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

	mutex_lock(&nic_data->spi_lock);
	rc = __falcon_reset_hw(efx, method);
	mutex_unlock(&nic_data->spi_lock);

	वापस rc;
पूर्ण

अटल व्योम falcon_monitor(काष्ठा ef4_nic *efx)
अणु
	bool link_changed;
	पूर्णांक rc;

	BUG_ON(!mutex_is_locked(&efx->mac_lock));

	rc = falcon_board(efx)->type->monitor(efx);
	अगर (rc) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "Board sensor %s; shutting down PHY\n",
			  (rc == -दुस्फल) ? "reported fault" : "failed");
		efx->phy_mode |= PHY_MODE_LOW_POWER;
		rc = __ef4_reconfigure_port(efx);
		WARN_ON(rc);
	पूर्ण

	अगर (LOOPBACK_INTERNAL(efx))
		link_changed = falcon_loopback_link_poll(efx);
	अन्यथा
		link_changed = efx->phy_op->poll(efx);

	अगर (link_changed) अणु
		falcon_stop_nic_stats(efx);
		falcon_deconfigure_mac_wrapper(efx);

		falcon_reset_macs(efx);
		rc = falcon_reconfigure_xmac(efx);
		BUG_ON(rc);

		falcon_start_nic_stats(efx);

		ef4_link_status_changed(efx);
	पूर्ण

	falcon_poll_xmac(efx);
पूर्ण

/* Zeroes out the SRAM contents.  This routine must be called in
 * process context and is allowed to sleep.
 */
अटल पूर्णांक falcon_reset_sram(काष्ठा ef4_nic *efx)
अणु
	ef4_oword_t srm_cfg_reg_ker, gpio_cfg_reg_ker;
	पूर्णांक count;

	/* Set the SRAM wake/sleep GPIO appropriately. */
	ef4_पढ़ोo(efx, &gpio_cfg_reg_ker, FR_AB_GPIO_CTL);
	EF4_SET_OWORD_FIELD(gpio_cfg_reg_ker, FRF_AB_GPIO1_OEN, 1);
	EF4_SET_OWORD_FIELD(gpio_cfg_reg_ker, FRF_AB_GPIO1_OUT, 1);
	ef4_ग_लिखोo(efx, &gpio_cfg_reg_ker, FR_AB_GPIO_CTL);

	/* Initiate SRAM reset */
	EF4_POPULATE_OWORD_2(srm_cfg_reg_ker,
			     FRF_AZ_SRM_INIT_EN, 1,
			     FRF_AZ_SRM_NB_SZ, 0);
	ef4_ग_लिखोo(efx, &srm_cfg_reg_ker, FR_AZ_SRM_CFG);

	/* Wait क्रम SRAM reset to complete */
	count = 0;
	करो अणु
		netअगर_dbg(efx, hw, efx->net_dev,
			  "waiting for SRAM reset (attempt %d)...\n", count);

		/* SRAM reset is slow; expect around 16ms */
		schedule_समयout_unपूर्णांकerruptible(HZ / 50);

		/* Check क्रम reset complete */
		ef4_पढ़ोo(efx, &srm_cfg_reg_ker, FR_AZ_SRM_CFG);
		अगर (!EF4_OWORD_FIELD(srm_cfg_reg_ker, FRF_AZ_SRM_INIT_EN)) अणु
			netअगर_dbg(efx, hw, efx->net_dev,
				  "SRAM reset complete\n");

			वापस 0;
		पूर्ण
	पूर्ण जबतक (++count < 20);	/* रुको up to 0.4 sec */

	netअगर_err(efx, hw, efx->net_dev, "timed out waiting for SRAM reset\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम falcon_spi_device_init(काष्ठा ef4_nic *efx,
				  काष्ठा falcon_spi_device *spi_device,
				  अचिन्हित पूर्णांक device_id, u32 device_type)
अणु
	अगर (device_type != 0) अणु
		spi_device->device_id = device_id;
		spi_device->size =
			1 << SPI_DEV_TYPE_FIELD(device_type, SPI_DEV_TYPE_SIZE);
		spi_device->addr_len =
			SPI_DEV_TYPE_FIELD(device_type, SPI_DEV_TYPE_ADDR_LEN);
		spi_device->munge_address = (spi_device->size == 1 << 9 &&
					     spi_device->addr_len == 1);
		spi_device->erase_command =
			SPI_DEV_TYPE_FIELD(device_type, SPI_DEV_TYPE_ERASE_CMD);
		spi_device->erase_size =
			1 << SPI_DEV_TYPE_FIELD(device_type,
						SPI_DEV_TYPE_ERASE_SIZE);
		spi_device->block_size =
			1 << SPI_DEV_TYPE_FIELD(device_type,
						SPI_DEV_TYPE_BLOCK_SIZE);
	पूर्ण अन्यथा अणु
		spi_device->size = 0;
	पूर्ण
पूर्ण

/* Extract non-अस्थिर configuration */
अटल पूर्णांक falcon_probe_nvconfig(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	काष्ठा falcon_nvconfig *nvconfig;
	पूर्णांक rc;

	nvconfig = kदो_स्मृति(माप(*nvconfig), GFP_KERNEL);
	अगर (!nvconfig)
		वापस -ENOMEM;

	rc = falcon_पढ़ो_nvram(efx, nvconfig);
	अगर (rc)
		जाओ out;

	efx->phy_type = nvconfig->board_v2.port0_phy_type;
	efx->mdio.prtad = nvconfig->board_v2.port0_phy_addr;

	अगर (le16_to_cpu(nvconfig->board_काष्ठा_ver) >= 3) अणु
		falcon_spi_device_init(
			efx, &nic_data->spi_flash, FFE_AB_SPI_DEVICE_FLASH,
			le32_to_cpu(nvconfig->board_v3
				    .spi_device_type[FFE_AB_SPI_DEVICE_FLASH]));
		falcon_spi_device_init(
			efx, &nic_data->spi_eeprom, FFE_AB_SPI_DEVICE_EEPROM,
			le32_to_cpu(nvconfig->board_v3
				    .spi_device_type[FFE_AB_SPI_DEVICE_EEPROM]));
	पूर्ण

	/* Read the MAC addresses */
	ether_addr_copy(efx->net_dev->perm_addr, nvconfig->mac_address[0]);

	netअगर_dbg(efx, probe, efx->net_dev, "PHY is %d phy_id %d\n",
		  efx->phy_type, efx->mdio.prtad);

	rc = falcon_probe_board(efx,
				le16_to_cpu(nvconfig->board_v2.board_revision));
out:
	kमुक्त(nvconfig);
	वापस rc;
पूर्ण

अटल पूर्णांक falcon_dimension_resources(काष्ठा ef4_nic *efx)
अणु
	efx->rx_dc_base = 0x20000;
	efx->tx_dc_base = 0x26000;
	वापस 0;
पूर्ण

/* Probe all SPI devices on the NIC */
अटल व्योम falcon_probe_spi_devices(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	ef4_oword_t nic_stat, gpio_ctl, ee_vpd_cfg;
	पूर्णांक boot_dev;

	ef4_पढ़ोo(efx, &gpio_ctl, FR_AB_GPIO_CTL);
	ef4_पढ़ोo(efx, &nic_stat, FR_AB_NIC_STAT);
	ef4_पढ़ोo(efx, &ee_vpd_cfg, FR_AB_EE_VPD_CFG0);

	अगर (EF4_OWORD_FIELD(gpio_ctl, FRF_AB_GPIO3_PWRUP_VALUE)) अणु
		boot_dev = (EF4_OWORD_FIELD(nic_stat, FRF_AB_SF_PRST) ?
			    FFE_AB_SPI_DEVICE_FLASH : FFE_AB_SPI_DEVICE_EEPROM);
		netअगर_dbg(efx, probe, efx->net_dev, "Booted from %s\n",
			  boot_dev == FFE_AB_SPI_DEVICE_FLASH ?
			  "flash" : "EEPROM");
	पूर्ण अन्यथा अणु
		/* Disable VPD and set घड़ी भागiders to safe
		 * values क्रम initial programming. */
		boot_dev = -1;
		netअगर_dbg(efx, probe, efx->net_dev,
			  "Booted from internal ASIC settings;"
			  " setting SPI config\n");
		EF4_POPULATE_OWORD_3(ee_vpd_cfg, FRF_AB_EE_VPD_EN, 0,
				     /* 125 MHz / 7 ~= 20 MHz */
				     FRF_AB_EE_SF_CLOCK_DIV, 7,
				     /* 125 MHz / 63 ~= 2 MHz */
				     FRF_AB_EE_EE_CLOCK_DIV, 63);
		ef4_ग_लिखोo(efx, &ee_vpd_cfg, FR_AB_EE_VPD_CFG0);
	पूर्ण

	mutex_init(&nic_data->spi_lock);

	अगर (boot_dev == FFE_AB_SPI_DEVICE_FLASH)
		falcon_spi_device_init(efx, &nic_data->spi_flash,
				       FFE_AB_SPI_DEVICE_FLASH,
				       शेष_flash_type);
	अगर (boot_dev == FFE_AB_SPI_DEVICE_EEPROM)
		falcon_spi_device_init(efx, &nic_data->spi_eeprom,
				       FFE_AB_SPI_DEVICE_EEPROM,
				       large_eeprom_type);
पूर्ण

अटल अचिन्हित पूर्णांक falcon_a1_mem_map_size(काष्ठा ef4_nic *efx)
अणु
	वापस 0x20000;
पूर्ण

अटल अचिन्हित पूर्णांक falcon_b0_mem_map_size(काष्ठा ef4_nic *efx)
अणु
	/* Map everything up to and including the RSS indirection table.
	 * The PCI core takes care of mapping the MSI-X tables.
	 */
	वापस FR_BZ_RX_INसूचीECTION_TBL +
		FR_BZ_RX_INसूचीECTION_TBL_STEP * FR_BZ_RX_INसूचीECTION_TBL_ROWS;
पूर्ण

अटल पूर्णांक falcon_probe_nic(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data;
	काष्ठा falcon_board *board;
	पूर्णांक rc;

	efx->primary = efx; /* only one usable function per controller */

	/* Allocate storage क्रम hardware specअगरic data */
	nic_data = kzalloc(माप(*nic_data), GFP_KERNEL);
	अगर (!nic_data)
		वापस -ENOMEM;
	efx->nic_data = nic_data;
	nic_data->efx = efx;

	rc = -ENODEV;

	अगर (ef4_farch_fpga_ver(efx) != 0) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "Falcon FPGA not supported\n");
		जाओ fail1;
	पूर्ण

	अगर (ef4_nic_rev(efx) <= EF4_REV_FALCON_A1) अणु
		ef4_oword_t nic_stat;
		काष्ठा pci_dev *dev;
		u8 pci_rev = efx->pci_dev->revision;

		अगर ((pci_rev == 0xff) || (pci_rev == 0)) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "Falcon rev A0 not supported\n");
			जाओ fail1;
		पूर्ण
		ef4_पढ़ोo(efx, &nic_stat, FR_AB_NIC_STAT);
		अगर (EF4_OWORD_FIELD(nic_stat, FRF_AB_STRAP_10G) == 0) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "Falcon rev A1 1G not supported\n");
			जाओ fail1;
		पूर्ण
		अगर (EF4_OWORD_FIELD(nic_stat, FRF_AA_STRAP_PCIE) == 0) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "Falcon rev A1 PCI-X not supported\n");
			जाओ fail1;
		पूर्ण

		dev = pci_dev_get(efx->pci_dev);
		जबतक ((dev = pci_get_device(PCI_VENDOR_ID_SOLARFLARE,
					     PCI_DEVICE_ID_SOLARFLARE_SFC4000A_1,
					     dev))) अणु
			अगर (dev->bus == efx->pci_dev->bus &&
			    dev->devfn == efx->pci_dev->devfn + 1) अणु
				nic_data->pci_dev2 = dev;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!nic_data->pci_dev2) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "failed to find secondary function\n");
			rc = -ENODEV;
			जाओ fail2;
		पूर्ण
	पूर्ण

	/* Now we can reset the NIC */
	rc = __falcon_reset_hw(efx, RESET_TYPE_ALL);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev, "failed to reset NIC\n");
		जाओ fail3;
	पूर्ण

	/* Allocate memory क्रम INT_KER */
	rc = ef4_nic_alloc_buffer(efx, &efx->irq_status, माप(ef4_oword_t),
				  GFP_KERNEL);
	अगर (rc)
		जाओ fail4;
	BUG_ON(efx->irq_status.dma_addr & 0x0f);

	netअगर_dbg(efx, probe, efx->net_dev,
		  "INT_KER at %llx (virt %p phys %llx)\n",
		  (u64)efx->irq_status.dma_addr,
		  efx->irq_status.addr,
		  (u64)virt_to_phys(efx->irq_status.addr));

	falcon_probe_spi_devices(efx);

	/* Read in the non-अस्थिर configuration */
	rc = falcon_probe_nvconfig(efx);
	अगर (rc) अणु
		अगर (rc == -EINVAL)
			netअगर_err(efx, probe, efx->net_dev, "NVRAM is invalid\n");
		जाओ fail5;
	पूर्ण

	efx->max_channels = (ef4_nic_rev(efx) <= EF4_REV_FALCON_A1 ? 4 :
			     EF4_MAX_CHANNELS);
	efx->max_tx_channels = efx->max_channels;
	efx->समयr_quantum_ns = 4968; /* 621 cycles */
	efx->समयr_max_ns = efx->type->समयr_period_max *
			    efx->समयr_quantum_ns;

	/* Initialise I2C adapter */
	board = falcon_board(efx);
	board->i2c_adap.owner = THIS_MODULE;
	board->i2c_data = falcon_i2c_bit_operations;
	board->i2c_data.data = efx;
	board->i2c_adap.algo_data = &board->i2c_data;
	board->i2c_adap.dev.parent = &efx->pci_dev->dev;
	strlcpy(board->i2c_adap.name, "SFC4000 GPIO",
		माप(board->i2c_adap.name));
	rc = i2c_bit_add_bus(&board->i2c_adap);
	अगर (rc)
		जाओ fail5;

	rc = falcon_board(efx)->type->init(efx);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "failed to initialise board\n");
		जाओ fail6;
	पूर्ण

	nic_data->stats_disable_count = 1;
	समयr_setup(&nic_data->stats_समयr, falcon_stats_समयr_func, 0);

	वापस 0;

 fail6:
	i2c_del_adapter(&board->i2c_adap);
	स_रखो(&board->i2c_adap, 0, माप(board->i2c_adap));
 fail5:
	ef4_nic_मुक्त_buffer(efx, &efx->irq_status);
 fail4:
 fail3:
	अगर (nic_data->pci_dev2) अणु
		pci_dev_put(nic_data->pci_dev2);
		nic_data->pci_dev2 = शून्य;
	पूर्ण
 fail2:
 fail1:
	kमुक्त(efx->nic_data);
	वापस rc;
पूर्ण

अटल व्योम falcon_init_rx_cfg(काष्ठा ef4_nic *efx)
अणु
	/* RX control FIFO thresholds (32 entries) */
	स्थिर अचिन्हित ctrl_xon_thr = 20;
	स्थिर अचिन्हित ctrl_xoff_thr = 25;
	ef4_oword_t reg;

	ef4_पढ़ोo(efx, &reg, FR_AZ_RX_CFG);
	अगर (ef4_nic_rev(efx) <= EF4_REV_FALCON_A1) अणु
		/* Data FIFO size is 5.5K.  The RX DMA engine only
		 * supports scattering क्रम user-mode queues, but will
		 * split DMA ग_लिखोs at पूर्णांकervals of RX_USR_BUF_SIZE
		 * (32-byte units) even क्रम kernel-mode queues.  We
		 * set it to be so large that that never happens.
		 */
		EF4_SET_OWORD_FIELD(reg, FRF_AA_RX_DESC_PUSH_EN, 0);
		EF4_SET_OWORD_FIELD(reg, FRF_AA_RX_USR_BUF_SIZE,
				    (3 * 4096) >> 5);
		EF4_SET_OWORD_FIELD(reg, FRF_AA_RX_XON_MAC_TH, 512 >> 8);
		EF4_SET_OWORD_FIELD(reg, FRF_AA_RX_XOFF_MAC_TH, 2048 >> 8);
		EF4_SET_OWORD_FIELD(reg, FRF_AA_RX_XON_TX_TH, ctrl_xon_thr);
		EF4_SET_OWORD_FIELD(reg, FRF_AA_RX_XOFF_TX_TH, ctrl_xoff_thr);
	पूर्ण अन्यथा अणु
		/* Data FIFO size is 80K; रेजिस्टर fields moved */
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_DESC_PUSH_EN, 0);
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_USR_BUF_SIZE,
				    EF4_RX_USR_BUF_SIZE >> 5);
		/* Send XON and XOFF at ~3 * max MTU away from empty/full */
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_XON_MAC_TH, 27648 >> 8);
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_XOFF_MAC_TH, 54272 >> 8);
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_XON_TX_TH, ctrl_xon_thr);
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_XOFF_TX_TH, ctrl_xoff_thr);
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_INGR_EN, 1);

		/* Enable hash insertion. This is broken क्रम the
		 * 'Falcon' hash so also select Toeplitz TCP/IPv4 and
		 * IPv4 hashes. */
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_HASH_INSRT_HDR, 1);
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_HASH_ALG, 1);
		EF4_SET_OWORD_FIELD(reg, FRF_BZ_RX_IP_HASH, 1);
	पूर्ण
	/* Always enable XOFF संकेत from RX FIFO.  We enable
	 * or disable transmission of छोड़ो frames at the MAC. */
	EF4_SET_OWORD_FIELD(reg, FRF_AZ_RX_XOFF_MAC_EN, 1);
	ef4_ग_लिखोo(efx, &reg, FR_AZ_RX_CFG);
पूर्ण

/* This call perक्रमms hardware-specअगरic global initialisation, such as
 * defining the descriptor cache sizes and number of RSS channels.
 * It करोes not set up any buffers, descriptor rings or event queues.
 */
अटल पूर्णांक falcon_init_nic(काष्ठा ef4_nic *efx)
अणु
	ef4_oword_t temp;
	पूर्णांक rc;

	/* Use on-chip SRAM */
	ef4_पढ़ोo(efx, &temp, FR_AB_NIC_STAT);
	EF4_SET_OWORD_FIELD(temp, FRF_AB_ONCHIP_SRAM, 1);
	ef4_ग_लिखोo(efx, &temp, FR_AB_NIC_STAT);

	rc = falcon_reset_sram(efx);
	अगर (rc)
		वापस rc;

	/* Clear the parity enables on the TX data fअगरos as
	 * they produce false parity errors because of timing issues
	 */
	अगर (EF4_WORKAROUND_5129(efx)) अणु
		ef4_पढ़ोo(efx, &temp, FR_AZ_CSR_SPARE);
		EF4_SET_OWORD_FIELD(temp, FRF_AB_MEM_PERR_EN_TX_DATA, 0);
		ef4_ग_लिखोo(efx, &temp, FR_AZ_CSR_SPARE);
	पूर्ण

	अगर (EF4_WORKAROUND_7244(efx)) अणु
		ef4_पढ़ोo(efx, &temp, FR_BZ_RX_FILTER_CTL);
		EF4_SET_OWORD_FIELD(temp, FRF_BZ_UDP_FULL_SRCH_LIMIT, 8);
		EF4_SET_OWORD_FIELD(temp, FRF_BZ_UDP_WILD_SRCH_LIMIT, 8);
		EF4_SET_OWORD_FIELD(temp, FRF_BZ_TCP_FULL_SRCH_LIMIT, 8);
		EF4_SET_OWORD_FIELD(temp, FRF_BZ_TCP_WILD_SRCH_LIMIT, 8);
		ef4_ग_लिखोo(efx, &temp, FR_BZ_RX_FILTER_CTL);
	पूर्ण

	/* XXX This is करोcumented only क्रम Falcon A0/A1 */
	/* Setup RX.  Wait क्रम descriptor is broken and must
	 * be disabled.  RXDP recovery shouldn't be needed, but is.
	 */
	ef4_पढ़ोo(efx, &temp, FR_AA_RX_SELF_RST);
	EF4_SET_OWORD_FIELD(temp, FRF_AA_RX_NODESC_WAIT_DIS, 1);
	EF4_SET_OWORD_FIELD(temp, FRF_AA_RX_SELF_RST_EN, 1);
	अगर (EF4_WORKAROUND_5583(efx))
		EF4_SET_OWORD_FIELD(temp, FRF_AA_RX_ISCSI_DIS, 1);
	ef4_ग_लिखोo(efx, &temp, FR_AA_RX_SELF_RST);

	/* Do not enable TX_NO_EOP_DISC_EN, since it limits packets to 16
	 * descriptors (which is bad).
	 */
	ef4_पढ़ोo(efx, &temp, FR_AZ_TX_CFG);
	EF4_SET_OWORD_FIELD(temp, FRF_AZ_TX_NO_EOP_DISC_EN, 0);
	ef4_ग_लिखोo(efx, &temp, FR_AZ_TX_CFG);

	falcon_init_rx_cfg(efx);

	अगर (ef4_nic_rev(efx) >= EF4_REV_FALCON_B0) अणु
		falcon_b0_rx_push_rss_config(efx, false, efx->rx_indir_table);

		/* Set destination of both TX and RX Flush events */
		EF4_POPULATE_OWORD_1(temp, FRF_BZ_FLS_EVQ_ID, 0);
		ef4_ग_लिखोo(efx, &temp, FR_BZ_DP_CTRL);
	पूर्ण

	ef4_farch_init_common(efx);

	वापस 0;
पूर्ण

अटल व्योम falcon_हटाओ_nic(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	काष्ठा falcon_board *board = falcon_board(efx);

	board->type->fini(efx);

	/* Remove I2C adapter and clear it in preparation क्रम a retry */
	i2c_del_adapter(&board->i2c_adap);
	स_रखो(&board->i2c_adap, 0, माप(board->i2c_adap));

	ef4_nic_मुक्त_buffer(efx, &efx->irq_status);

	__falcon_reset_hw(efx, RESET_TYPE_ALL);

	/* Release the second function after the reset */
	अगर (nic_data->pci_dev2) अणु
		pci_dev_put(nic_data->pci_dev2);
		nic_data->pci_dev2 = शून्य;
	पूर्ण

	/* Tear करोwn the निजी nic state */
	kमुक्त(efx->nic_data);
	efx->nic_data = शून्य;
पूर्ण

अटल माप_प्रकार falcon_describe_nic_stats(काष्ठा ef4_nic *efx, u8 *names)
अणु
	वापस ef4_nic_describe_stats(falcon_stat_desc, FALCON_STAT_COUNT,
				      falcon_stat_mask, names);
पूर्ण

अटल माप_प्रकार falcon_update_nic_stats(काष्ठा ef4_nic *efx, u64 *full_stats,
				      काष्ठा rtnl_link_stats64 *core_stats)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	u64 *stats = nic_data->stats;
	ef4_oword_t cnt;

	अगर (!nic_data->stats_disable_count) अणु
		ef4_पढ़ोo(efx, &cnt, FR_AZ_RX_NODESC_DROP);
		stats[FALCON_STAT_rx_nodesc_drop_cnt] +=
			EF4_OWORD_FIELD(cnt, FRF_AB_RX_NODESC_DROP_CNT);

		अगर (nic_data->stats_pending &&
		    FALCON_XMAC_STATS_DMA_FLAG(efx)) अणु
			nic_data->stats_pending = false;
			rmb(); /* पढ़ो the करोne flag beक्रमe the stats */
			ef4_nic_update_stats(
				falcon_stat_desc, FALCON_STAT_COUNT,
				falcon_stat_mask,
				stats, efx->stats_buffer.addr, true);
		पूर्ण

		/* Update derived statistic */
		ef4_update_dअगरf_stat(&stats[FALCON_STAT_rx_bad_bytes],
				     stats[FALCON_STAT_rx_bytes] -
				     stats[FALCON_STAT_rx_good_bytes] -
				     stats[FALCON_STAT_rx_control] * 64);
		ef4_update_sw_stats(efx, stats);
	पूर्ण

	अगर (full_stats)
		स_नकल(full_stats, stats, माप(u64) * FALCON_STAT_COUNT);

	अगर (core_stats) अणु
		core_stats->rx_packets = stats[FALCON_STAT_rx_packets];
		core_stats->tx_packets = stats[FALCON_STAT_tx_packets];
		core_stats->rx_bytes = stats[FALCON_STAT_rx_bytes];
		core_stats->tx_bytes = stats[FALCON_STAT_tx_bytes];
		core_stats->rx_dropped = stats[FALCON_STAT_rx_nodesc_drop_cnt] +
					 stats[GENERIC_STAT_rx_nodesc_trunc] +
					 stats[GENERIC_STAT_rx_noskb_drops];
		core_stats->multicast = stats[FALCON_STAT_rx_multicast];
		core_stats->rx_length_errors =
			stats[FALCON_STAT_rx_gtjumbo] +
			stats[FALCON_STAT_rx_length_error];
		core_stats->rx_crc_errors = stats[FALCON_STAT_rx_bad];
		core_stats->rx_frame_errors = stats[FALCON_STAT_rx_align_error];
		core_stats->rx_fअगरo_errors = stats[FALCON_STAT_rx_overflow];

		core_stats->rx_errors = (core_stats->rx_length_errors +
					 core_stats->rx_crc_errors +
					 core_stats->rx_frame_errors +
					 stats[FALCON_STAT_rx_symbol_error]);
	पूर्ण

	वापस FALCON_STAT_COUNT;
पूर्ण

व्योम falcon_start_nic_stats(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;

	spin_lock_bh(&efx->stats_lock);
	अगर (--nic_data->stats_disable_count == 0)
		falcon_stats_request(efx);
	spin_unlock_bh(&efx->stats_lock);
पूर्ण

/* We करोn't acutally pull stats on falcon. Wait 10ms so that
 * they arrive when we call this just after start_stats
 */
अटल व्योम falcon_pull_nic_stats(काष्ठा ef4_nic *efx)
अणु
	msleep(10);
पूर्ण

व्योम falcon_stop_nic_stats(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	पूर्णांक i;

	might_sleep();

	spin_lock_bh(&efx->stats_lock);
	++nic_data->stats_disable_count;
	spin_unlock_bh(&efx->stats_lock);

	del_समयr_sync(&nic_data->stats_समयr);

	/* Wait enough समय क्रम the most recent transfer to
	 * complete. */
	क्रम (i = 0; i < 4 && nic_data->stats_pending; i++) अणु
		अगर (FALCON_XMAC_STATS_DMA_FLAG(efx))
			अवरोध;
		msleep(1);
	पूर्ण

	spin_lock_bh(&efx->stats_lock);
	falcon_stats_complete(efx);
	spin_unlock_bh(&efx->stats_lock);
पूर्ण

अटल व्योम falcon_set_id_led(काष्ठा ef4_nic *efx, क्रमागत ef4_led_mode mode)
अणु
	falcon_board(efx)->type->set_id_led(efx, mode);
पूर्ण

/**************************************************************************
 *
 * Wake on LAN
 *
 **************************************************************************
 */

अटल व्योम falcon_get_wol(काष्ठा ef4_nic *efx, काष्ठा ethtool_wolinfo *wol)
अणु
	wol->supported = 0;
	wol->wolopts = 0;
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण

अटल पूर्णांक falcon_set_wol(काष्ठा ef4_nic *efx, u32 type)
अणु
	अगर (type != 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**************************************************************************
 *
 * Revision-dependent attributes used by efx.c and nic.c
 *
 **************************************************************************
 */

स्थिर काष्ठा ef4_nic_type falcon_a1_nic_type = अणु
	.mem_bar = EF4_MEM_BAR,
	.mem_map_size = falcon_a1_mem_map_size,
	.probe = falcon_probe_nic,
	.हटाओ = falcon_हटाओ_nic,
	.init = falcon_init_nic,
	.dimension_resources = falcon_dimension_resources,
	.fini = falcon_irq_ack_a1,
	.monitor = falcon_monitor,
	.map_reset_reason = falcon_map_reset_reason,
	.map_reset_flags = falcon_map_reset_flags,
	.reset = falcon_reset_hw,
	.probe_port = falcon_probe_port,
	.हटाओ_port = falcon_हटाओ_port,
	.handle_global_event = falcon_handle_global_event,
	.fini_dmaq = ef4_farch_fini_dmaq,
	.prepare_flush = falcon_prepare_flush,
	.finish_flush = ef4_port_dummy_op_व्योम,
	.prepare_flr = ef4_port_dummy_op_व्योम,
	.finish_flr = ef4_farch_finish_flr,
	.describe_stats = falcon_describe_nic_stats,
	.update_stats = falcon_update_nic_stats,
	.start_stats = falcon_start_nic_stats,
	.pull_stats = falcon_pull_nic_stats,
	.stop_stats = falcon_stop_nic_stats,
	.set_id_led = falcon_set_id_led,
	.push_irq_moderation = falcon_push_irq_moderation,
	.reconfigure_port = falcon_reconfigure_port,
	.prepare_enable_fc_tx = falcon_a1_prepare_enable_fc_tx,
	.reconfigure_mac = falcon_reconfigure_xmac,
	.check_mac_fault = falcon_xmac_check_fault,
	.get_wol = falcon_get_wol,
	.set_wol = falcon_set_wol,
	.resume_wol = ef4_port_dummy_op_व्योम,
	.test_nvram = falcon_test_nvram,
	.irq_enable_master = ef4_farch_irq_enable_master,
	.irq_test_generate = ef4_farch_irq_test_generate,
	.irq_disable_non_ev = ef4_farch_irq_disable_master,
	.irq_handle_msi = ef4_farch_msi_पूर्णांकerrupt,
	.irq_handle_legacy = falcon_legacy_पूर्णांकerrupt_a1,
	.tx_probe = ef4_farch_tx_probe,
	.tx_init = ef4_farch_tx_init,
	.tx_हटाओ = ef4_farch_tx_हटाओ,
	.tx_ग_लिखो = ef4_farch_tx_ग_लिखो,
	.tx_limit_len = ef4_farch_tx_limit_len,
	.rx_push_rss_config = dummy_rx_push_rss_config,
	.rx_probe = ef4_farch_rx_probe,
	.rx_init = ef4_farch_rx_init,
	.rx_हटाओ = ef4_farch_rx_हटाओ,
	.rx_ग_लिखो = ef4_farch_rx_ग_लिखो,
	.rx_defer_refill = ef4_farch_rx_defer_refill,
	.ev_probe = ef4_farch_ev_probe,
	.ev_init = ef4_farch_ev_init,
	.ev_fini = ef4_farch_ev_fini,
	.ev_हटाओ = ef4_farch_ev_हटाओ,
	.ev_process = ef4_farch_ev_process,
	.ev_पढ़ो_ack = ef4_farch_ev_पढ़ो_ack,
	.ev_test_generate = ef4_farch_ev_test_generate,

	/* We करोn't expose the filter table on Falcon A1 as it is not
	 * mapped पूर्णांकo function 0, but these implementations still
	 * work with a degenerate हाल of all tables set to size 0.
	 */
	.filter_table_probe = ef4_farch_filter_table_probe,
	.filter_table_restore = ef4_farch_filter_table_restore,
	.filter_table_हटाओ = ef4_farch_filter_table_हटाओ,
	.filter_insert = ef4_farch_filter_insert,
	.filter_हटाओ_safe = ef4_farch_filter_हटाओ_safe,
	.filter_get_safe = ef4_farch_filter_get_safe,
	.filter_clear_rx = ef4_farch_filter_clear_rx,
	.filter_count_rx_used = ef4_farch_filter_count_rx_used,
	.filter_get_rx_id_limit = ef4_farch_filter_get_rx_id_limit,
	.filter_get_rx_ids = ef4_farch_filter_get_rx_ids,

#अगर_घोषित CONFIG_SFC_FALCON_MTD
	.mtd_probe = falcon_mtd_probe,
	.mtd_नाम = falcon_mtd_नाम,
	.mtd_पढ़ो = falcon_mtd_पढ़ो,
	.mtd_erase = falcon_mtd_erase,
	.mtd_ग_लिखो = falcon_mtd_ग_लिखो,
	.mtd_sync = falcon_mtd_sync,
#पूर्ण_अगर

	.revision = EF4_REV_FALCON_A1,
	.txd_ptr_tbl_base = FR_AA_TX_DESC_PTR_TBL_KER,
	.rxd_ptr_tbl_base = FR_AA_RX_DESC_PTR_TBL_KER,
	.buf_tbl_base = FR_AA_BUF_FULL_TBL_KER,
	.evq_ptr_tbl_base = FR_AA_EVQ_PTR_TBL_KER,
	.evq_rptr_tbl_base = FR_AA_EVQ_RPTR_KER,
	.max_dma_mask = DMA_BIT_MASK(FSF_AZ_TX_KER_BUF_ADDR_WIDTH),
	.rx_buffer_padding = 0x24,
	.can_rx_scatter = false,
	.max_पूर्णांकerrupt_mode = EF4_INT_MODE_MSI,
	.समयr_period_max =  1 << FRF_AB_TC_TIMER_VAL_WIDTH,
	.offload_features = NETIF_F_IP_CSUM,
पूर्ण;

स्थिर काष्ठा ef4_nic_type falcon_b0_nic_type = अणु
	.mem_bar = EF4_MEM_BAR,
	.mem_map_size = falcon_b0_mem_map_size,
	.probe = falcon_probe_nic,
	.हटाओ = falcon_हटाओ_nic,
	.init = falcon_init_nic,
	.dimension_resources = falcon_dimension_resources,
	.fini = ef4_port_dummy_op_व्योम,
	.monitor = falcon_monitor,
	.map_reset_reason = falcon_map_reset_reason,
	.map_reset_flags = falcon_map_reset_flags,
	.reset = falcon_reset_hw,
	.probe_port = falcon_probe_port,
	.हटाओ_port = falcon_हटाओ_port,
	.handle_global_event = falcon_handle_global_event,
	.fini_dmaq = ef4_farch_fini_dmaq,
	.prepare_flush = falcon_prepare_flush,
	.finish_flush = ef4_port_dummy_op_व्योम,
	.prepare_flr = ef4_port_dummy_op_व्योम,
	.finish_flr = ef4_farch_finish_flr,
	.describe_stats = falcon_describe_nic_stats,
	.update_stats = falcon_update_nic_stats,
	.start_stats = falcon_start_nic_stats,
	.pull_stats = falcon_pull_nic_stats,
	.stop_stats = falcon_stop_nic_stats,
	.set_id_led = falcon_set_id_led,
	.push_irq_moderation = falcon_push_irq_moderation,
	.reconfigure_port = falcon_reconfigure_port,
	.prepare_enable_fc_tx = falcon_b0_prepare_enable_fc_tx,
	.reconfigure_mac = falcon_reconfigure_xmac,
	.check_mac_fault = falcon_xmac_check_fault,
	.get_wol = falcon_get_wol,
	.set_wol = falcon_set_wol,
	.resume_wol = ef4_port_dummy_op_व्योम,
	.test_chip = falcon_b0_test_chip,
	.test_nvram = falcon_test_nvram,
	.irq_enable_master = ef4_farch_irq_enable_master,
	.irq_test_generate = ef4_farch_irq_test_generate,
	.irq_disable_non_ev = ef4_farch_irq_disable_master,
	.irq_handle_msi = ef4_farch_msi_पूर्णांकerrupt,
	.irq_handle_legacy = ef4_farch_legacy_पूर्णांकerrupt,
	.tx_probe = ef4_farch_tx_probe,
	.tx_init = ef4_farch_tx_init,
	.tx_हटाओ = ef4_farch_tx_हटाओ,
	.tx_ग_लिखो = ef4_farch_tx_ग_लिखो,
	.tx_limit_len = ef4_farch_tx_limit_len,
	.rx_push_rss_config = falcon_b0_rx_push_rss_config,
	.rx_probe = ef4_farch_rx_probe,
	.rx_init = ef4_farch_rx_init,
	.rx_हटाओ = ef4_farch_rx_हटाओ,
	.rx_ग_लिखो = ef4_farch_rx_ग_लिखो,
	.rx_defer_refill = ef4_farch_rx_defer_refill,
	.ev_probe = ef4_farch_ev_probe,
	.ev_init = ef4_farch_ev_init,
	.ev_fini = ef4_farch_ev_fini,
	.ev_हटाओ = ef4_farch_ev_हटाओ,
	.ev_process = ef4_farch_ev_process,
	.ev_पढ़ो_ack = ef4_farch_ev_पढ़ो_ack,
	.ev_test_generate = ef4_farch_ev_test_generate,
	.filter_table_probe = ef4_farch_filter_table_probe,
	.filter_table_restore = ef4_farch_filter_table_restore,
	.filter_table_हटाओ = ef4_farch_filter_table_हटाओ,
	.filter_update_rx_scatter = ef4_farch_filter_update_rx_scatter,
	.filter_insert = ef4_farch_filter_insert,
	.filter_हटाओ_safe = ef4_farch_filter_हटाओ_safe,
	.filter_get_safe = ef4_farch_filter_get_safe,
	.filter_clear_rx = ef4_farch_filter_clear_rx,
	.filter_count_rx_used = ef4_farch_filter_count_rx_used,
	.filter_get_rx_id_limit = ef4_farch_filter_get_rx_id_limit,
	.filter_get_rx_ids = ef4_farch_filter_get_rx_ids,
#अगर_घोषित CONFIG_RFS_ACCEL
	.filter_rfs_insert = ef4_farch_filter_rfs_insert,
	.filter_rfs_expire_one = ef4_farch_filter_rfs_expire_one,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SFC_FALCON_MTD
	.mtd_probe = falcon_mtd_probe,
	.mtd_नाम = falcon_mtd_नाम,
	.mtd_पढ़ो = falcon_mtd_पढ़ो,
	.mtd_erase = falcon_mtd_erase,
	.mtd_ग_लिखो = falcon_mtd_ग_लिखो,
	.mtd_sync = falcon_mtd_sync,
#पूर्ण_अगर

	.revision = EF4_REV_FALCON_B0,
	.txd_ptr_tbl_base = FR_BZ_TX_DESC_PTR_TBL,
	.rxd_ptr_tbl_base = FR_BZ_RX_DESC_PTR_TBL,
	.buf_tbl_base = FR_BZ_BUF_FULL_TBL,
	.evq_ptr_tbl_base = FR_BZ_EVQ_PTR_TBL,
	.evq_rptr_tbl_base = FR_BZ_EVQ_RPTR,
	.max_dma_mask = DMA_BIT_MASK(FSF_AZ_TX_KER_BUF_ADDR_WIDTH),
	.rx_prefix_size = FS_BZ_RX_PREFIX_SIZE,
	.rx_hash_offset = FS_BZ_RX_PREFIX_HASH_OFST,
	.rx_buffer_padding = 0,
	.can_rx_scatter = true,
	.max_पूर्णांकerrupt_mode = EF4_INT_MODE_MSIX,
	.समयr_period_max =  1 << FRF_AB_TC_TIMER_VAL_WIDTH,
	.offload_features = NETIF_F_IP_CSUM | NETIF_F_RXHASH | NETIF_F_NTUPLE,
	.max_rx_ip_filters = FR_BZ_RX_FILTER_TBL0_ROWS,
पूर्ण;
