<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* drivers/aपंचांग/zeprom.h - ZeitNet ZN122x EEPROM (NM93C46) declarations */

/* Written 1995,1996 by Werner Almesberger, EPFL LRC */


#अगर_अघोषित DRIVER_ATM_ZEPROM_H
#घोषणा DRIVER_ATM_ZEPROM_H

/* Dअगरferent versions use dअगरferent control रेजिस्टरs */

#घोषणा ZEPROM_V1_REG	PCI_VENDOR_ID	/* PCI रेजिस्टर */
#घोषणा ZEPROM_V2_REG	0x40

/* Bits in contol रेजिस्टर */

#घोषणा ZEPROM_SK	0x80000000	/* strobe (probably on raising edge) */
#घोषणा ZEPROM_CS	0x40000000	/* Chip Select */
#घोषणा ZEPROM_DI	0x20000000	/* Data Input */
#घोषणा ZEPROM_DO	0x10000000	/* Data Output */

#घोषणा ZEPROM_SIZE	32		/* 32 bytes */
#घोषणा ZEPROM_V1_ESI_OFF 24		/* ESI offset in EEPROM (V1) */
#घोषणा ZEPROM_V2_ESI_OFF 4		/* ESI offset in EEPROM (V2) */

#घोषणा ZEPROM_CMD_LEN	3		/* commands are three bits */
#घोषणा ZEPROM_ADDR_LEN	6		/* addresses are six bits */

/* Commands (3 bits) */

#घोषणा ZEPROM_CMD_READ	6

/* No other commands are needed. */

#पूर्ण_अगर
