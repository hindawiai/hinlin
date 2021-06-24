<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * atusb.h - Definitions shared between kernel and ATUSB firmware
 *
 * Written 2013 by Werner Almesberger <werner@almesberger.net>
 *
 * (at your option) any later version.
 *
 * This file should be identical क्रम kernel and firmware.
 * Kernel: drivers/net/ieee802154/atusb.h
 * Firmware: ben-wpan/atusb/fw/include/atusb/atusb.h
 */

#अगर_अघोषित	_ATUSB_H
#घोषणा	_ATUSB_H

#घोषणा ATUSB_VENDOR_ID	0x20b7	/* Qi Hardware*/
#घोषणा ATUSB_PRODUCT_ID 0x1540	/* 802.15.4, device 0 */
				/*     -- -         - */

#घोषणा ATUSB_BUILD_SIZE 256	/* maximum build version/date message length */

/* Commands to our device. Make sure this is synced with the firmware */
क्रमागत atusb_requests अणु
	ATUSB_ID			= 0x00,	/* प्रणाली status/control grp */
	ATUSB_BUILD,
	ATUSB_RESET,
	ATUSB_RF_RESET			= 0x10,	/* debug/test group */
	ATUSB_POLL_INT,
	ATUSB_TEST,			/* atusb-sil only */
	ATUSB_TIMER,
	ATUSB_GPIO,
	ATUSB_SLP_TR,
	ATUSB_GPIO_CLEANUP,
	ATUSB_REG_WRITE			= 0x20,	/* transceiver group */
	ATUSB_REG_READ,
	ATUSB_BUF_WRITE,
	ATUSB_BUF_READ,
	ATUSB_SRAM_WRITE,
	ATUSB_SRAM_READ,
	ATUSB_SPI_WRITE			= 0x30,	/* SPI group */
	ATUSB_SPI_READ1,
	ATUSB_SPI_READ2,
	ATUSB_SPI_WRITE2_SYNC,
	ATUSB_RX_MODE			= 0x40, /* HardMAC group */
	ATUSB_TX,
	ATUSB_EUI64_WRITE		= 0x50, /* Parameter in EEPROM grp */
	ATUSB_EUI64_READ,
पूर्ण;

क्रमागत अणु
	ATUSB_HW_TYPE_100813,	/* 2010-08-13 */
	ATUSB_HW_TYPE_101216,	/* 2010-12-16 */
	ATUSB_HW_TYPE_110131,	/* 2011-01-31, ATmega32U2-based */
	ATUSB_HW_TYPE_RZUSB,	/* Aपंचांगel Raven USB करोngle with at86rf230 */
	ATUSB_HW_TYPE_HULUSB,	/* Busware HUL USB करोngle with at86rf212 */
पूर्ण;

/*
 * Direction	bRequest		wValue		wIndex	wLength
 *
 * ->host	ATUSB_ID		-		-	3
 * ->host	ATUSB_BUILD		-		-	#bytes
 * host->	ATUSB_RESET		-		-	0
 *
 * host->	ATUSB_RF_RESET		-		-	0
 * ->host	ATUSB_POLL_INT		-		-	1
 * host->	ATUSB_TEST		-		-	0
 * ->host	ATUSB_TIMER		-		-	#bytes (6)
 * ->host	ATUSB_GPIO		dir+data	mask+p#	3
 * host->	ATUSB_SLP_TR		-		-	0
 * host->	ATUSB_GPIO_CLEANUP	-		-	0
 *
 * host->	ATUSB_REG_WRITE		value		addr	0
 * ->host	ATUSB_REG_READ		-		addr	1
 * host->	ATUSB_BUF_WRITE		-		-	#bytes
 * ->host	ATUSB_BUF_READ		-		-	#bytes
 * host->	ATUSB_SRAM_WRITE	-		addr	#bytes
 * ->host	ATUSB_SRAM_READ		-		addr	#bytes
 *
 * host->	ATUSB_SPI_WRITE		byte0		byte1	#bytes
 * ->host	ATUSB_SPI_READ1		byte0		-	#bytes
 * ->host	ATUSB_SPI_READ2		byte0		byte1	#bytes
 * ->host	ATUSB_SPI_WRITE2_SYNC	byte0		byte1	0/1
 *
 * host->	ATUSB_RX_MODE		on		-	0
 * host->	ATUSB_TX		flags		ack_seq	#bytes
 * host->	ATUSB_EUI64_WRITE	-		-	#bytes (8)
 * ->host	ATUSB_EUI64_READ	-		-	#bytes (8)
 */

#घोषणा ATUSB_REQ_FROM_DEV	(USB_TYPE_VENDOR | USB_सूची_IN)
#घोषणा ATUSB_REQ_TO_DEV	(USB_TYPE_VENDOR | USB_सूची_OUT)

#पूर्ण_अगर /* !_ATUSB_H */
