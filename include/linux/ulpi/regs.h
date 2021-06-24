<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_ULPI_REGS_H
#घोषणा __LINUX_ULPI_REGS_H

/*
 * Macros क्रम Set and Clear
 * See ULPI 1.1 specअगरication to find the रेजिस्टरs with Set and Clear offsets
 */
#घोषणा ULPI_SET(a)				(a + 1)
#घोषणा ULPI_CLR(a)				(a + 2)

/*
 * Register Map
 */
#घोषणा ULPI_VENDOR_ID_LOW			0x00
#घोषणा ULPI_VENDOR_ID_HIGH			0x01
#घोषणा ULPI_PRODUCT_ID_LOW			0x02
#घोषणा ULPI_PRODUCT_ID_HIGH			0x03
#घोषणा ULPI_FUNC_CTRL				0x04
#घोषणा ULPI_IFC_CTRL				0x07
#घोषणा ULPI_OTG_CTRL				0x0a
#घोषणा ULPI_USB_INT_EN_RISE			0x0d
#घोषणा ULPI_USB_INT_EN_FALL			0x10
#घोषणा ULPI_USB_INT_STS			0x13
#घोषणा ULPI_USB_INT_LATCH			0x14
#घोषणा ULPI_DEBUG				0x15
#घोषणा ULPI_SCRATCH				0x16
/* Optional Carkit Registers */
#घोषणा ULPI_CARKIT_CTRL			0x19
#घोषणा ULPI_CARKIT_INT_DELAY			0x1c
#घोषणा ULPI_CARKIT_INT_EN			0x1d
#घोषणा ULPI_CARKIT_INT_STS			0x20
#घोषणा ULPI_CARKIT_INT_LATCH			0x21
#घोषणा ULPI_CARKIT_PLS_CTRL			0x22
/* Other Optional Registers */
#घोषणा ULPI_TX_POS_WIDTH			0x25
#घोषणा ULPI_TX_NEG_WIDTH			0x26
#घोषणा ULPI_POLARITY_RECOVERY			0x27
/* Access Extended Register Set */
#घोषणा ULPI_ACCESS_EXTENDED			0x2f
/* Venकरोr Specअगरic */
#घोषणा ULPI_VENDOR_SPECIFIC			0x30
/* Extended Registers */
#घोषणा ULPI_EXT_VENDOR_SPECIFIC		0x80

/*
 * Register Bits
 */

/* Function Control */
#घोषणा ULPI_FUNC_CTRL_XCVRSEL			BIT(0)
#घोषणा  ULPI_FUNC_CTRL_XCVRSEL_MASK		0x3
#घोषणा  ULPI_FUNC_CTRL_HIGH_SPEED		0x0
#घोषणा  ULPI_FUNC_CTRL_FULL_SPEED		0x1
#घोषणा  ULPI_FUNC_CTRL_LOW_SPEED		0x2
#घोषणा  ULPI_FUNC_CTRL_FS4LS			0x3
#घोषणा ULPI_FUNC_CTRL_TERMSELECT		BIT(2)
#घोषणा ULPI_FUNC_CTRL_OPMODE			BIT(3)
#घोषणा  ULPI_FUNC_CTRL_OPMODE_MASK		(0x3 << 3)
#घोषणा  ULPI_FUNC_CTRL_OPMODE_NORMAL		(0x0 << 3)
#घोषणा  ULPI_FUNC_CTRL_OPMODE_NONDRIVING	(0x1 << 3)
#घोषणा  ULPI_FUNC_CTRL_OPMODE_DISABLE_NRZI	(0x2 << 3)
#घोषणा  ULPI_FUNC_CTRL_OPMODE_NOSYNC_NOEOP	(0x3 << 3)
#घोषणा ULPI_FUNC_CTRL_RESET			BIT(5)
#घोषणा ULPI_FUNC_CTRL_SUSPENDM			BIT(6)

/* Interface Control */
#घोषणा ULPI_IFC_CTRL_6_PIN_SERIAL_MODE		BIT(0)
#घोषणा ULPI_IFC_CTRL_3_PIN_SERIAL_MODE		BIT(1)
#घोषणा ULPI_IFC_CTRL_CARKITMODE		BIT(2)
#घोषणा ULPI_IFC_CTRL_CLOCKSUSPENDM		BIT(3)
#घोषणा ULPI_IFC_CTRL_AUTORESUME		BIT(4)
#घोषणा ULPI_IFC_CTRL_EXTERNAL_VBUS		BIT(5)
#घोषणा ULPI_IFC_CTRL_PASSTHRU			BIT(6)
#घोषणा ULPI_IFC_CTRL_PROTECT_IFC_DISABLE	BIT(7)

/* OTG Control */
#घोषणा ULPI_OTG_CTRL_ID_PULLUP			BIT(0)
#घोषणा ULPI_OTG_CTRL_DP_PULLDOWN		BIT(1)
#घोषणा ULPI_OTG_CTRL_DM_PULLDOWN		BIT(2)
#घोषणा ULPI_OTG_CTRL_DISCHRGVBUS		BIT(3)
#घोषणा ULPI_OTG_CTRL_CHRGVBUS			BIT(4)
#घोषणा ULPI_OTG_CTRL_DRVVBUS			BIT(5)
#घोषणा ULPI_OTG_CTRL_DRVVBUS_EXT		BIT(6)
#घोषणा ULPI_OTG_CTRL_EXTVBUSIND		BIT(7)

/* USB Interrupt Enable Rising,
 * USB Interrupt Enable Falling,
 * USB Interrupt Status and
 * USB Interrupt Latch
 */
#घोषणा ULPI_INT_HOST_DISCONNECT		BIT(0)
#घोषणा ULPI_INT_VBUS_VALID			BIT(1)
#घोषणा ULPI_INT_SESS_VALID			BIT(2)
#घोषणा ULPI_INT_SESS_END			BIT(3)
#घोषणा ULPI_INT_IDGRD				BIT(4)

/* Debug */
#घोषणा ULPI_DEBUG_LINESTATE0			BIT(0)
#घोषणा ULPI_DEBUG_LINESTATE1			BIT(1)

/* Carkit Control */
#घोषणा ULPI_CARKIT_CTRL_CARKITPWR		BIT(0)
#घोषणा ULPI_CARKIT_CTRL_IDGNDDRV		BIT(1)
#घोषणा ULPI_CARKIT_CTRL_TXDEN			BIT(2)
#घोषणा ULPI_CARKIT_CTRL_RXDEN			BIT(3)
#घोषणा ULPI_CARKIT_CTRL_SPKLEFTEN		BIT(4)
#घोषणा ULPI_CARKIT_CTRL_SPKRIGHTEN		BIT(5)
#घोषणा ULPI_CARKIT_CTRL_MICEN			BIT(6)

/* Carkit Interrupt Enable */
#घोषणा ULPI_CARKIT_INT_EN_IDFLOAT_RISE		BIT(0)
#घोषणा ULPI_CARKIT_INT_EN_IDFLOAT_FALL		BIT(1)
#घोषणा ULPI_CARKIT_INT_EN_CARINTDET		BIT(2)
#घोषणा ULPI_CARKIT_INT_EN_DP_RISE		BIT(3)
#घोषणा ULPI_CARKIT_INT_EN_DP_FALL		BIT(4)

/* Carkit Interrupt Status and
 * Carkit Interrupt Latch
 */
#घोषणा ULPI_CARKIT_INT_IDFLOAT			BIT(0)
#घोषणा ULPI_CARKIT_INT_CARINTDET		BIT(1)
#घोषणा ULPI_CARKIT_INT_DP			BIT(2)

/* Carkit Pulse Control*/
#घोषणा ULPI_CARKIT_PLS_CTRL_TXPLSEN		BIT(0)
#घोषणा ULPI_CARKIT_PLS_CTRL_RXPLSEN		BIT(1)
#घोषणा ULPI_CARKIT_PLS_CTRL_SPKRLEFT_BIASEN	BIT(2)
#घोषणा ULPI_CARKIT_PLS_CTRL_SPKRRIGHT_BIASEN	BIT(3)

#पूर्ण_अगर /* __LINUX_ULPI_REGS_H */
