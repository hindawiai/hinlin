<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2014 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __LINUX_MTD_SPI_NOR_H
#घोषणा __LINUX_MTD_SPI_NOR_H

#समावेश <linux/bitops.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/spi/spi-स्मृति.स>

/*
 * Note on opcode nomenclature: some opcodes have a क्रमmat like
 * SPINOR_OP_FUNCTIONअणु4,पूर्ण_x_y_z. The numbers x, y, and z stand क्रम the number
 * of I/O lines used क्रम the opcode, address, and data (respectively). The
 * FUNCTION has an optional suffix of '4', to represent an opcode which
 * requires a 4-byte (32-bit) address.
 */

/* Flash opcodes. */
#घोषणा SPINOR_OP_WRDI		0x04	/* Write disable */
#घोषणा SPINOR_OP_WREN		0x06	/* Write enable */
#घोषणा SPINOR_OP_RDSR		0x05	/* Read status रेजिस्टर */
#घोषणा SPINOR_OP_WRSR		0x01	/* Write status रेजिस्टर 1 byte */
#घोषणा SPINOR_OP_RDSR2		0x3f	/* Read status रेजिस्टर 2 */
#घोषणा SPINOR_OP_WRSR2		0x3e	/* Write status रेजिस्टर 2 */
#घोषणा SPINOR_OP_READ		0x03	/* Read data bytes (low frequency) */
#घोषणा SPINOR_OP_READ_FAST	0x0b	/* Read data bytes (high frequency) */
#घोषणा SPINOR_OP_READ_1_1_2	0x3b	/* Read data bytes (Dual Output SPI) */
#घोषणा SPINOR_OP_READ_1_2_2	0xbb	/* Read data bytes (Dual I/O SPI) */
#घोषणा SPINOR_OP_READ_1_1_4	0x6b	/* Read data bytes (Quad Output SPI) */
#घोषणा SPINOR_OP_READ_1_4_4	0xeb	/* Read data bytes (Quad I/O SPI) */
#घोषणा SPINOR_OP_READ_1_1_8	0x8b	/* Read data bytes (Octal Output SPI) */
#घोषणा SPINOR_OP_READ_1_8_8	0xcb	/* Read data bytes (Octal I/O SPI) */
#घोषणा SPINOR_OP_PP		0x02	/* Page program (up to 256 bytes) */
#घोषणा SPINOR_OP_PP_1_1_4	0x32	/* Quad page program */
#घोषणा SPINOR_OP_PP_1_4_4	0x38	/* Quad page program */
#घोषणा SPINOR_OP_PP_1_1_8	0x82	/* Octal page program */
#घोषणा SPINOR_OP_PP_1_8_8	0xc2	/* Octal page program */
#घोषणा SPINOR_OP_BE_4K		0x20	/* Erase 4KiB block */
#घोषणा SPINOR_OP_BE_4K_PMC	0xd7	/* Erase 4KiB block on PMC chips */
#घोषणा SPINOR_OP_BE_32K	0x52	/* Erase 32KiB block */
#घोषणा SPINOR_OP_CHIP_ERASE	0xc7	/* Erase whole flash chip */
#घोषणा SPINOR_OP_SE		0xd8	/* Sector erase (usually 64KiB) */
#घोषणा SPINOR_OP_RDID		0x9f	/* Read JEDEC ID */
#घोषणा SPINOR_OP_RDSFDP	0x5a	/* Read SFDP */
#घोषणा SPINOR_OP_RDCR		0x35	/* Read configuration रेजिस्टर */
#घोषणा SPINOR_OP_RDFSR		0x70	/* Read flag status रेजिस्टर */
#घोषणा SPINOR_OP_CLFSR		0x50	/* Clear flag status रेजिस्टर */
#घोषणा SPINOR_OP_RDEAR		0xc8	/* Read Extended Address Register */
#घोषणा SPINOR_OP_WREAR		0xc5	/* Write Extended Address Register */
#घोषणा SPINOR_OP_SRSTEN	0x66	/* Software Reset Enable */
#घोषणा SPINOR_OP_SRST		0x99	/* Software Reset */
#घोषणा SPINOR_OP_GBULK		0x98    /* Global Block Unlock */

/* 4-byte address opcodes - used on Spansion and some Macronix flashes. */
#घोषणा SPINOR_OP_READ_4B	0x13	/* Read data bytes (low frequency) */
#घोषणा SPINOR_OP_READ_FAST_4B	0x0c	/* Read data bytes (high frequency) */
#घोषणा SPINOR_OP_READ_1_1_2_4B	0x3c	/* Read data bytes (Dual Output SPI) */
#घोषणा SPINOR_OP_READ_1_2_2_4B	0xbc	/* Read data bytes (Dual I/O SPI) */
#घोषणा SPINOR_OP_READ_1_1_4_4B	0x6c	/* Read data bytes (Quad Output SPI) */
#घोषणा SPINOR_OP_READ_1_4_4_4B	0xec	/* Read data bytes (Quad I/O SPI) */
#घोषणा SPINOR_OP_READ_1_1_8_4B	0x7c	/* Read data bytes (Octal Output SPI) */
#घोषणा SPINOR_OP_READ_1_8_8_4B	0xcc	/* Read data bytes (Octal I/O SPI) */
#घोषणा SPINOR_OP_PP_4B		0x12	/* Page program (up to 256 bytes) */
#घोषणा SPINOR_OP_PP_1_1_4_4B	0x34	/* Quad page program */
#घोषणा SPINOR_OP_PP_1_4_4_4B	0x3e	/* Quad page program */
#घोषणा SPINOR_OP_PP_1_1_8_4B	0x84	/* Octal page program */
#घोषणा SPINOR_OP_PP_1_8_8_4B	0x8e	/* Octal page program */
#घोषणा SPINOR_OP_BE_4K_4B	0x21	/* Erase 4KiB block */
#घोषणा SPINOR_OP_BE_32K_4B	0x5c	/* Erase 32KiB block */
#घोषणा SPINOR_OP_SE_4B		0xdc	/* Sector erase (usually 64KiB) */

/* Double Transfer Rate opcodes - defined in JEDEC JESD216B. */
#घोषणा SPINOR_OP_READ_1_1_1_DTR	0x0d
#घोषणा SPINOR_OP_READ_1_2_2_DTR	0xbd
#घोषणा SPINOR_OP_READ_1_4_4_DTR	0xed

#घोषणा SPINOR_OP_READ_1_1_1_DTR_4B	0x0e
#घोषणा SPINOR_OP_READ_1_2_2_DTR_4B	0xbe
#घोषणा SPINOR_OP_READ_1_4_4_DTR_4B	0xee

/* Used क्रम SST flashes only. */
#घोषणा SPINOR_OP_BP		0x02	/* Byte program */
#घोषणा SPINOR_OP_AAI_WP	0xad	/* Auto address increment word program */

/* Used क्रम S3AN flashes only */
#घोषणा SPINOR_OP_XSE		0x50	/* Sector erase */
#घोषणा SPINOR_OP_XPP		0x82	/* Page program */
#घोषणा SPINOR_OP_XRDSR		0xd7	/* Read status रेजिस्टर */

#घोषणा XSR_PAGESIZE		BIT(0)	/* Page size in Po2 or Linear */
#घोषणा XSR_RDY			BIT(7)	/* Ready */


/* Used क्रम Macronix and Winbond flashes. */
#घोषणा SPINOR_OP_EN4B		0xb7	/* Enter 4-byte mode */
#घोषणा SPINOR_OP_EX4B		0xe9	/* Exit 4-byte mode */

/* Used क्रम Spansion flashes only. */
#घोषणा SPINOR_OP_BRWR		0x17	/* Bank रेजिस्टर ग_लिखो */
#घोषणा SPINOR_OP_CLSR		0x30	/* Clear status रेजिस्टर 1 */

/* Used क्रम Micron flashes only. */
#घोषणा SPINOR_OP_RD_EVCR      0x65    /* Read EVCR रेजिस्टर */
#घोषणा SPINOR_OP_WD_EVCR      0x61    /* Write EVCR रेजिस्टर */

/* Used क्रम GigaDevices and Winbond flashes. */
#घोषणा SPINOR_OP_ESECR		0x44	/* Erase Security रेजिस्टरs */
#घोषणा SPINOR_OP_PSECR		0x42	/* Program Security रेजिस्टरs */
#घोषणा SPINOR_OP_RSECR		0x48	/* Read Security रेजिस्टरs */

/* Status Register bits. */
#घोषणा SR_WIP			BIT(0)	/* Write in progress */
#घोषणा SR_WEL			BIT(1)	/* Write enable latch */
/* meaning of other SR_* bits may dअगरfer between venकरोrs */
#घोषणा SR_BP0			BIT(2)	/* Block protect 0 */
#घोषणा SR_BP1			BIT(3)	/* Block protect 1 */
#घोषणा SR_BP2			BIT(4)	/* Block protect 2 */
#घोषणा SR_BP3			BIT(5)	/* Block protect 3 */
#घोषणा SR_TB_BIT5		BIT(5)	/* Top/Bottom protect */
#घोषणा SR_BP3_BIT6		BIT(6)	/* Block protect 3 */
#घोषणा SR_TB_BIT6		BIT(6)	/* Top/Bottom protect */
#घोषणा SR_SRWD			BIT(7)	/* SR ग_लिखो protect */
/* Spansion/Cypress specअगरic status bits */
#घोषणा SR_E_ERR		BIT(5)
#घोषणा SR_P_ERR		BIT(6)

#घोषणा SR1_QUAD_EN_BIT6	BIT(6)

#घोषणा SR_BP_SHIFT		2

/* Enhanced Volatile Configuration Register bits */
#घोषणा EVCR_QUAD_EN_MICRON	BIT(7)	/* Micron Quad I/O */

/* Flag Status Register bits */
#घोषणा FSR_READY		BIT(7)	/* Device status, 0 = Busy, 1 = Ready */
#घोषणा FSR_E_ERR		BIT(5)	/* Erase operation status */
#घोषणा FSR_P_ERR		BIT(4)	/* Program operation status */
#घोषणा FSR_PT_ERR		BIT(1)	/* Protection error bit */

/* Status Register 2 bits. */
#घोषणा SR2_QUAD_EN_BIT1	BIT(1)
#घोषणा SR2_LB1			BIT(3)	/* Security Register Lock Bit 1 */
#घोषणा SR2_LB2			BIT(4)	/* Security Register Lock Bit 2 */
#घोषणा SR2_LB3			BIT(5)	/* Security Register Lock Bit 3 */
#घोषणा SR2_QUAD_EN_BIT7	BIT(7)

/* Supported SPI protocols */
#घोषणा SNOR_PROTO_INST_MASK	GENMASK(23, 16)
#घोषणा SNOR_PROTO_INST_SHIFT	16
#घोषणा SNOR_PROTO_INST(_nbits)	\
	((((अचिन्हित दीर्घ)(_nbits)) << SNOR_PROTO_INST_SHIFT) & \
	 SNOR_PROTO_INST_MASK)

#घोषणा SNOR_PROTO_ADDR_MASK	GENMASK(15, 8)
#घोषणा SNOR_PROTO_ADDR_SHIFT	8
#घोषणा SNOR_PROTO_ADDR(_nbits)	\
	((((अचिन्हित दीर्घ)(_nbits)) << SNOR_PROTO_ADDR_SHIFT) & \
	 SNOR_PROTO_ADDR_MASK)

#घोषणा SNOR_PROTO_DATA_MASK	GENMASK(7, 0)
#घोषणा SNOR_PROTO_DATA_SHIFT	0
#घोषणा SNOR_PROTO_DATA(_nbits)	\
	((((अचिन्हित दीर्घ)(_nbits)) << SNOR_PROTO_DATA_SHIFT) & \
	 SNOR_PROTO_DATA_MASK)

#घोषणा SNOR_PROTO_IS_DTR	BIT(24)	/* Double Transfer Rate */

#घोषणा SNOR_PROTO_STR(_inst_nbits, _addr_nbits, _data_nbits)	\
	(SNOR_PROTO_INST(_inst_nbits) |				\
	 SNOR_PROTO_ADDR(_addr_nbits) |				\
	 SNOR_PROTO_DATA(_data_nbits))
#घोषणा SNOR_PROTO_DTR(_inst_nbits, _addr_nbits, _data_nbits)	\
	(SNOR_PROTO_IS_DTR |					\
	 SNOR_PROTO_STR(_inst_nbits, _addr_nbits, _data_nbits))

क्रमागत spi_nor_protocol अणु
	SNOR_PROTO_1_1_1 = SNOR_PROTO_STR(1, 1, 1),
	SNOR_PROTO_1_1_2 = SNOR_PROTO_STR(1, 1, 2),
	SNOR_PROTO_1_1_4 = SNOR_PROTO_STR(1, 1, 4),
	SNOR_PROTO_1_1_8 = SNOR_PROTO_STR(1, 1, 8),
	SNOR_PROTO_1_2_2 = SNOR_PROTO_STR(1, 2, 2),
	SNOR_PROTO_1_4_4 = SNOR_PROTO_STR(1, 4, 4),
	SNOR_PROTO_1_8_8 = SNOR_PROTO_STR(1, 8, 8),
	SNOR_PROTO_2_2_2 = SNOR_PROTO_STR(2, 2, 2),
	SNOR_PROTO_4_4_4 = SNOR_PROTO_STR(4, 4, 4),
	SNOR_PROTO_8_8_8 = SNOR_PROTO_STR(8, 8, 8),

	SNOR_PROTO_1_1_1_DTR = SNOR_PROTO_DTR(1, 1, 1),
	SNOR_PROTO_1_2_2_DTR = SNOR_PROTO_DTR(1, 2, 2),
	SNOR_PROTO_1_4_4_DTR = SNOR_PROTO_DTR(1, 4, 4),
	SNOR_PROTO_1_8_8_DTR = SNOR_PROTO_DTR(1, 8, 8),
	SNOR_PROTO_8_8_8_DTR = SNOR_PROTO_DTR(8, 8, 8),
पूर्ण;

अटल अंतरभूत bool spi_nor_protocol_is_dtr(क्रमागत spi_nor_protocol proto)
अणु
	वापस !!(proto & SNOR_PROTO_IS_DTR);
पूर्ण

अटल अंतरभूत u8 spi_nor_get_protocol_inst_nbits(क्रमागत spi_nor_protocol proto)
अणु
	वापस ((अचिन्हित दीर्घ)(proto & SNOR_PROTO_INST_MASK)) >>
		SNOR_PROTO_INST_SHIFT;
पूर्ण

अटल अंतरभूत u8 spi_nor_get_protocol_addr_nbits(क्रमागत spi_nor_protocol proto)
अणु
	वापस ((अचिन्हित दीर्घ)(proto & SNOR_PROTO_ADDR_MASK)) >>
		SNOR_PROTO_ADDR_SHIFT;
पूर्ण

अटल अंतरभूत u8 spi_nor_get_protocol_data_nbits(क्रमागत spi_nor_protocol proto)
अणु
	वापस ((अचिन्हित दीर्घ)(proto & SNOR_PROTO_DATA_MASK)) >>
		SNOR_PROTO_DATA_SHIFT;
पूर्ण

अटल अंतरभूत u8 spi_nor_get_protocol_width(क्रमागत spi_nor_protocol proto)
अणु
	वापस spi_nor_get_protocol_data_nbits(proto);
पूर्ण

/**
 * काष्ठा spi_nor_hwcaps - Structure क्रम describing the hardware capabilies
 * supported by the SPI controller (bus master).
 * @mask:		the biपंचांगask listing all the supported hw capabilies
 */
काष्ठा spi_nor_hwcaps अणु
	u32	mask;
पूर्ण;

/*
 *(Fast) Read capabilities.
 * MUST be ordered by priority: the higher bit position, the higher priority.
 * As a matter of perक्रमmances, it is relevant to use Octal SPI protocols first,
 * then Quad SPI protocols beक्रमe Dual SPI protocols, Fast Read and lastly
 * (Slow) Read.
 */
#घोषणा SNOR_HWCAPS_READ_MASK		GENMASK(15, 0)
#घोषणा SNOR_HWCAPS_READ		BIT(0)
#घोषणा SNOR_HWCAPS_READ_FAST		BIT(1)
#घोषणा SNOR_HWCAPS_READ_1_1_1_DTR	BIT(2)

#घोषणा SNOR_HWCAPS_READ_DUAL		GENMASK(6, 3)
#घोषणा SNOR_HWCAPS_READ_1_1_2		BIT(3)
#घोषणा SNOR_HWCAPS_READ_1_2_2		BIT(4)
#घोषणा SNOR_HWCAPS_READ_2_2_2		BIT(5)
#घोषणा SNOR_HWCAPS_READ_1_2_2_DTR	BIT(6)

#घोषणा SNOR_HWCAPS_READ_QUAD		GENMASK(10, 7)
#घोषणा SNOR_HWCAPS_READ_1_1_4		BIT(7)
#घोषणा SNOR_HWCAPS_READ_1_4_4		BIT(8)
#घोषणा SNOR_HWCAPS_READ_4_4_4		BIT(9)
#घोषणा SNOR_HWCAPS_READ_1_4_4_DTR	BIT(10)

#घोषणा SNOR_HWCAPS_READ_OCTAL		GENMASK(15, 11)
#घोषणा SNOR_HWCAPS_READ_1_1_8		BIT(11)
#घोषणा SNOR_HWCAPS_READ_1_8_8		BIT(12)
#घोषणा SNOR_HWCAPS_READ_8_8_8		BIT(13)
#घोषणा SNOR_HWCAPS_READ_1_8_8_DTR	BIT(14)
#घोषणा SNOR_HWCAPS_READ_8_8_8_DTR	BIT(15)

/*
 * Page Program capabilities.
 * MUST be ordered by priority: the higher bit position, the higher priority.
 * Like (Fast) Read capabilities, Octal/Quad SPI protocols are preferred to the
 * legacy SPI 1-1-1 protocol.
 * Note that Dual Page Programs are not supported because there is no existing
 * JEDEC/SFDP standard to define them. Also at this moment no SPI flash memory
 * implements such commands.
 */
#घोषणा SNOR_HWCAPS_PP_MASK		GENMASK(23, 16)
#घोषणा SNOR_HWCAPS_PP			BIT(16)

#घोषणा SNOR_HWCAPS_PP_QUAD		GENMASK(19, 17)
#घोषणा SNOR_HWCAPS_PP_1_1_4		BIT(17)
#घोषणा SNOR_HWCAPS_PP_1_4_4		BIT(18)
#घोषणा SNOR_HWCAPS_PP_4_4_4		BIT(19)

#घोषणा SNOR_HWCAPS_PP_OCTAL		GENMASK(23, 20)
#घोषणा SNOR_HWCAPS_PP_1_1_8		BIT(20)
#घोषणा SNOR_HWCAPS_PP_1_8_8		BIT(21)
#घोषणा SNOR_HWCAPS_PP_8_8_8		BIT(22)
#घोषणा SNOR_HWCAPS_PP_8_8_8_DTR	BIT(23)

#घोषणा SNOR_HWCAPS_X_X_X	(SNOR_HWCAPS_READ_2_2_2 |	\
				 SNOR_HWCAPS_READ_4_4_4 |	\
				 SNOR_HWCAPS_READ_8_8_8 |	\
				 SNOR_HWCAPS_PP_4_4_4 |		\
				 SNOR_HWCAPS_PP_8_8_8)

#घोषणा SNOR_HWCAPS_X_X_X_DTR	(SNOR_HWCAPS_READ_8_8_8_DTR |	\
				 SNOR_HWCAPS_PP_8_8_8_DTR)

#घोषणा SNOR_HWCAPS_DTR		(SNOR_HWCAPS_READ_1_1_1_DTR |	\
				 SNOR_HWCAPS_READ_1_2_2_DTR |	\
				 SNOR_HWCAPS_READ_1_4_4_DTR |	\
				 SNOR_HWCAPS_READ_1_8_8_DTR |	\
				 SNOR_HWCAPS_READ_8_8_8_DTR)

#घोषणा SNOR_HWCAPS_ALL		(SNOR_HWCAPS_READ_MASK |	\
				 SNOR_HWCAPS_PP_MASK)

/* Forward declaration that is used in 'struct spi_nor_controller_ops' */
काष्ठा spi_nor;

/**
 * काष्ठा spi_nor_controller_ops - SPI NOR controller driver specअगरic
 *                                 operations.
 * @prepare:		[OPTIONAL] करो some preparations क्रम the
 *			पढ़ो/ग_लिखो/erase/lock/unlock operations.
 * @unprepare:		[OPTIONAL] करो some post work after the
 *			पढ़ो/ग_लिखो/erase/lock/unlock operations.
 * @पढ़ो_reg:		पढ़ो out the रेजिस्टर.
 * @ग_लिखो_reg:		ग_लिखो data to the रेजिस्टर.
 * @पढ़ो:		पढ़ो data from the SPI NOR.
 * @ग_लिखो:		ग_लिखो data to the SPI NOR.
 * @erase:		erase a sector of the SPI NOR at the offset @offs; अगर
 *			not provided by the driver, SPI NOR will send the erase
 *			opcode via ग_लिखो_reg().
 */
काष्ठा spi_nor_controller_ops अणु
	पूर्णांक (*prepare)(काष्ठा spi_nor *nor);
	व्योम (*unprepare)(काष्ठा spi_nor *nor);
	पूर्णांक (*पढ़ो_reg)(काष्ठा spi_nor *nor, u8 opcode, u8 *buf, माप_प्रकार len);
	पूर्णांक (*ग_लिखो_reg)(काष्ठा spi_nor *nor, u8 opcode, स्थिर u8 *buf,
			 माप_प्रकार len);

	sमाप_प्रकार (*पढ़ो)(काष्ठा spi_nor *nor, loff_t from, माप_प्रकार len, u8 *buf);
	sमाप_प्रकार (*ग_लिखो)(काष्ठा spi_nor *nor, loff_t to, माप_प्रकार len,
			 स्थिर u8 *buf);
	पूर्णांक (*erase)(काष्ठा spi_nor *nor, loff_t offs);
पूर्ण;

/**
 * क्रमागत spi_nor_cmd_ext - describes the command opcode extension in DTR mode
 * @SPI_NOR_EXT_NONE: no extension. This is the शेष, and is used in Legacy
 *		      SPI mode
 * @SPI_NOR_EXT_REPEAT: the extension is same as the opcode
 * @SPI_NOR_EXT_INVERT: the extension is the bitwise inverse of the opcode
 * @SPI_NOR_EXT_HEX: the extension is any hex value. The command and opcode
 *		     combine to क्रमm a 16-bit opcode.
 */
क्रमागत spi_nor_cmd_ext अणु
	SPI_NOR_EXT_NONE = 0,
	SPI_NOR_EXT_REPEAT,
	SPI_NOR_EXT_INVERT,
	SPI_NOR_EXT_HEX,
पूर्ण;

/*
 * Forward declarations that are used पूर्णांकernally by the core and manufacturer
 * drivers.
 */
काष्ठा flash_info;
काष्ठा spi_nor_manufacturer;
काष्ठा spi_nor_flash_parameter;

/**
 * काष्ठा spi_nor - Structure क्रम defining the SPI NOR layer
 * @mtd:		an mtd_info काष्ठाure
 * @lock:		the lock क्रम the पढ़ो/ग_लिखो/erase/lock/unlock operations
 * @dev:		poपूर्णांकer to an SPI device or an SPI NOR controller device
 * @spimem:		poपूर्णांकer to the SPI memory device
 * @bouncebuf:		bounce buffer used when the buffer passed by the MTD
 *                      layer is not DMA-able
 * @bouncebuf_size:	size of the bounce buffer
 * @info:		SPI NOR part JEDEC MFR ID and other info
 * @manufacturer:	SPI NOR manufacturer
 * @page_size:		the page size of the SPI NOR
 * @addr_width:		number of address bytes
 * @erase_opcode:	the opcode क्रम erasing a sector
 * @पढ़ो_opcode:	the पढ़ो opcode
 * @पढ़ो_dummy:		the dummy needed by the पढ़ो operation
 * @program_opcode:	the program opcode
 * @sst_ग_लिखो_second:	used by the SST ग_लिखो operation
 * @flags:		flag options क्रम the current SPI NOR (SNOR_F_*)
 * @cmd_ext_type:	the command opcode extension type क्रम DTR mode.
 * @पढ़ो_proto:		the SPI protocol क्रम पढ़ो operations
 * @ग_लिखो_proto:	the SPI protocol क्रम ग_लिखो operations
 * @reg_proto:		the SPI protocol क्रम पढ़ो_reg/ग_लिखो_reg/erase operations
 * @controller_ops:	SPI NOR controller driver specअगरic operations.
 * @params:		[FLASH-SPECIFIC] SPI NOR flash parameters and settings.
 *                      The काष्ठाure includes legacy flash parameters and
 *                      settings that can be overwritten by the spi_nor_fixups
 *                      hooks, or dynamically when parsing the SFDP tables.
 * @dirmap:		poपूर्णांकers to काष्ठा spi_mem_dirmap_desc क्रम पढ़ोs/ग_लिखोs.
 * @priv:		poपूर्णांकer to the निजी data
 */
काष्ठा spi_nor अणु
	काष्ठा mtd_info		mtd;
	काष्ठा mutex		lock;
	काष्ठा device		*dev;
	काष्ठा spi_mem		*spimem;
	u8			*bouncebuf;
	माप_प्रकार			bouncebuf_size;
	स्थिर काष्ठा flash_info	*info;
	स्थिर काष्ठा spi_nor_manufacturer *manufacturer;
	u32			page_size;
	u8			addr_width;
	u8			erase_opcode;
	u8			पढ़ो_opcode;
	u8			पढ़ो_dummy;
	u8			program_opcode;
	क्रमागत spi_nor_protocol	पढ़ो_proto;
	क्रमागत spi_nor_protocol	ग_लिखो_proto;
	क्रमागत spi_nor_protocol	reg_proto;
	bool			sst_ग_लिखो_second;
	u32			flags;
	क्रमागत spi_nor_cmd_ext	cmd_ext_type;

	स्थिर काष्ठा spi_nor_controller_ops *controller_ops;

	काष्ठा spi_nor_flash_parameter *params;

	काष्ठा अणु
		काष्ठा spi_mem_dirmap_desc *rdesc;
		काष्ठा spi_mem_dirmap_desc *wdesc;
	पूर्ण dirmap;

	व्योम *priv;
पूर्ण;

अटल अंतरभूत व्योम spi_nor_set_flash_node(काष्ठा spi_nor *nor,
					  काष्ठा device_node *np)
अणु
	mtd_set_of_node(&nor->mtd, np);
पूर्ण

अटल अंतरभूत काष्ठा device_node *spi_nor_get_flash_node(काष्ठा spi_nor *nor)
अणु
	वापस mtd_get_of_node(&nor->mtd);
पूर्ण

/**
 * spi_nor_scan() - scan the SPI NOR
 * @nor:	the spi_nor काष्ठाure
 * @name:	the chip type name
 * @hwcaps:	the hardware capabilities supported by the controller driver
 *
 * The drivers can use this function to scan the SPI NOR.
 * In the scanning, it will try to get all the necessary inक्रमmation to
 * fill the mtd_infoअणुपूर्ण and the spi_norअणुपूर्ण.
 *
 * The chip type name can be provided through the @name parameter.
 *
 * Return: 0 क्रम success, others क्रम failure.
 */
पूर्णांक spi_nor_scan(काष्ठा spi_nor *nor, स्थिर अक्षर *name,
		 स्थिर काष्ठा spi_nor_hwcaps *hwcaps);

/**
 * spi_nor_restore_addr_mode() - restore the status of SPI NOR
 * @nor:	the spi_nor काष्ठाure
 */
व्योम spi_nor_restore(काष्ठा spi_nor *nor);

#पूर्ण_अगर
