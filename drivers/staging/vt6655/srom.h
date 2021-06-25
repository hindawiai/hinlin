<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: srom.h
 *
 * Purpose: Implement functions to access eeprom
 *
 * Author: Jerry Chen
 *
 * Date: Jan 29, 2003
 */

#अगर_अघोषित __SROM_H__
#घोषणा __SROM_H__

/*---------------------  Export Definitions -------------------------*/

#घोषणा EEP_MAX_CONTEXT_SIZE    256

#घोषणा CB_EEPROM_READBYTE_WAIT 900     /* us */

#घोषणा W_MAX_I2CRETRY          0x0fff

/* Contents in the EEPROM */
#घोषणा EEP_OFS_PAR         0x00        /* physical address */
#घोषणा EEP_OFS_ANTENNA     0x16
#घोषणा EEP_OFS_RADIOCTL    0x17
#घोषणा EEP_OFS_RFTYPE      0x1B        /* क्रम select RF */
#घोषणा EEP_OFS_MINCHANNEL  0x1C        /* Min Channel # */
#घोषणा EEP_OFS_MAXCHANNEL  0x1D        /* Max Channel # */
#घोषणा EEP_OFS_SIGNATURE   0x1E
#घोषणा EEP_OFS_ZONETYPE    0x1F
#घोषणा EEP_OFS_RFTABLE     0x20        /* RF POWER TABLE */
#घोषणा EEP_OFS_PWR_CCK     0x20
#घोषणा EEP_OFS_SETPT_CCK   0x21
#घोषणा EEP_OFS_PWR_OFDMG   0x23
#घोषणा EEP_OFS_SETPT_OFDMG 0x24
#घोषणा EEP_OFS_PWR_FORMULA_OST  0x26
#घोषणा EEP_OFS_MAJOR_VER 0x2E
#घोषणा EEP_OFS_MINOR_VER 0x2F
#घोषणा EEP_OFS_CCK_PWR_TBL     0x30
#घोषणा EEP_OFS_CCK_PWR_dBm     0x3F
#घोषणा EEP_OFS_OFDM_PWR_TBL    0x40
#घोषणा EEP_OFS_OFDM_PWR_dBm    0x4F
/*अणुअणु RobertYu: 20041124 */
#घोषणा EEP_OFS_SETPT_OFDMA         0x4E
#घोषणा EEP_OFS_OFDMA_PWR_TBL       0x50
/*पूर्णपूर्ण*/
#घोषणा EEP_OFS_OFDMA_PWR_dBm       0xD2

/*----------need to हटाओ --------------------*/
#घोषणा EEP_OFS_BBTAB_LEN   0x70        /* BB Table Length */
#घोषणा EEP_OFS_BBTAB_ADR   0x71        /* BB Table Offset */
#घोषणा EEP_OFS_CHECKSUM    0xFF        /* reserved area क्रम baseband 28h~78h */

#घोषणा EEP_I2C_DEV_ID      0x50        /* EEPROM device address on I2C bus */

/* Bits in EEP_OFS_ANTENNA */
#घोषणा EEP_ANTENNA_MAIN    0x01
#घोषणा EEP_ANTENNA_AUX     0x02
#घोषणा EEP_ANTINV          0x04

/* Bits in EEP_OFS_RADIOCTL */
#घोषणा EEP_RADIOCTL_ENABLE 0x80
#घोषणा EEP_RADIOCTL_INV    0x01

/*---------------------  Export Types  ------------------------------*/

/*---------------------  Export Macros ------------------------------*/

/*---------------------  Export Classes  ----------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Functions  --------------------------*/

अचिन्हित अक्षर SROMbyReadEmbedded(व्योम __iomem *iobase,
				 अचिन्हित अक्षर byContntOffset);

व्योम SROMvReadAllContents(व्योम __iomem *iobase, अचिन्हित अक्षर *pbyEepromRegs);

व्योम SROMvReadEtherAddress(व्योम __iomem *iobase,
			   अचिन्हित अक्षर *pbyEtherAddress);

#पूर्ण_अगर /* __EEPROM_H__*/
