<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_SPI_H
#घोषणा _UAPI_SPI_H

#समावेश <linux/स्थिर.h>

#घोषणा	SPI_CPHA		_BITUL(0)	/* घड़ी phase */
#घोषणा	SPI_CPOL		_BITUL(1)	/* घड़ी polarity */

#घोषणा	SPI_MODE_0		(0|0)		/* (original MicroWire) */
#घोषणा	SPI_MODE_1		(0|SPI_CPHA)
#घोषणा	SPI_MODE_2		(SPI_CPOL|0)
#घोषणा	SPI_MODE_3		(SPI_CPOL|SPI_CPHA)
#घोषणा	SPI_MODE_X_MASK		(SPI_CPOL|SPI_CPHA)

#घोषणा	SPI_CS_HIGH		_BITUL(2)	/* chipselect active high? */
#घोषणा	SPI_LSB_FIRST		_BITUL(3)	/* per-word bits-on-wire */
#घोषणा	SPI_3WIRE		_BITUL(4)	/* SI/SO संकेतs shared */
#घोषणा	SPI_LOOP		_BITUL(5)	/* loopback mode */
#घोषणा	SPI_NO_CS		_BITUL(6)	/* 1 dev/bus, no chipselect */
#घोषणा	SPI_READY		_BITUL(7)	/* slave pulls low to छोड़ो */
#घोषणा	SPI_TX_DUAL		_BITUL(8)	/* transmit with 2 wires */
#घोषणा	SPI_TX_QUAD		_BITUL(9)	/* transmit with 4 wires */
#घोषणा	SPI_RX_DUAL		_BITUL(10)	/* receive with 2 wires */
#घोषणा	SPI_RX_QUAD		_BITUL(11)	/* receive with 4 wires */
#घोषणा	SPI_CS_WORD		_BITUL(12)	/* toggle cs after each word */
#घोषणा	SPI_TX_OCTAL		_BITUL(13)	/* transmit with 8 wires */
#घोषणा	SPI_RX_OCTAL		_BITUL(14)	/* receive with 8 wires */
#घोषणा	SPI_3WIRE_HIZ		_BITUL(15)	/* high impedance turnaround */

/*
 * All the bits defined above should be covered by SPI_MODE_USER_MASK.
 * The SPI_MODE_USER_MASK has the SPI_MODE_KERNEL_MASK counterpart in
 * 'include/linux/spi/spi.h'. The bits defined here are from bit 0 upwards
 * जबतक in SPI_MODE_KERNEL_MASK they are from the other end करोwnwards.
 * These bits must not overlap. A अटल निश्चित check should make sure of that.
 * If adding extra bits, make sure to increase the bit index below as well.
 */
#घोषणा SPI_MODE_USER_MASK	(_BITUL(16) - 1)

#पूर्ण_अगर /* _UAPI_SPI_H */
