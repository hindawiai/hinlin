<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: srom.c
 *
 * Purpose:Implement functions to access eeprom
 *
 * Author: Jerry Chen
 *
 * Date: Jan 29, 2003
 *
 * Functions:
 *      SROMbyReadEmbedded - Embedded पढ़ो eeprom via MAC
 *      SROMbWriteEmbedded - Embedded ग_लिखो eeprom via MAC
 *      SROMvRegBitsOn - Set Bits On in eeprom
 *      SROMvRegBitsOff - Clear Bits Off in eeprom
 *      SROMbIsRegBitsOn - Test अगर Bits On in eeprom
 *      SROMbIsRegBitsOff - Test अगर Bits Off in eeprom
 *      SROMvReadAllContents - Read all contents in eeprom
 *      SROMvWriteAllContents - Write all contents in eeprom
 *      SROMvReadEtherAddress - Read Ethernet Address in eeprom
 *      SROMvWriteEtherAddress - Write Ethernet Address in eeprom
 *      SROMvReadSubSysVenId - Read Sub_VID and Sub_SysId in eeprom
 *      SROMbAutoLoad - Auto Load eeprom to MAC रेजिस्टर
 *
 * Revision History:
 *
 */

#समावेश "upc.h"
#समावेश "tmacro.h"
#समावेश "mac.h"
#समावेश "srom.h"

/*---------------------  Static Definitions -------------------------*/

/*---------------------  Static Classes  ----------------------------*/

/*---------------------  Static Variables  --------------------------*/

/*---------------------  Static Functions  --------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Functions  --------------------------*/

/*
 * Description: Read a byte from EEPROM, by MAC I2C
 *
 * Parameters:
 *  In:
 *      iobase          - I/O base address
 *      byContntOffset  - address of EEPROM
 *  Out:
 *      none
 *
 * Return Value: data पढ़ो
 *
 */
अचिन्हित अक्षर SROMbyReadEmbedded(व्योम __iomem *iobase,
				 अचिन्हित अक्षर byContntOffset)
अणु
	अचिन्हित लघु wDelay, wNoACK;
	अचिन्हित अक्षर byWait;
	अचिन्हित अक्षर byData;
	अचिन्हित अक्षर byOrg;

	byData = 0xFF;
	VNSvInPortB(iobase + MAC_REG_I2MCFG, &byOrg);
	/* turn off hardware retry क्रम getting NACK */
	VNSvOutPortB(iobase + MAC_REG_I2MCFG, (byOrg & (~I2MCFG_NORETRY)));
	क्रम (wNoACK = 0; wNoACK < W_MAX_I2CRETRY; wNoACK++) अणु
		VNSvOutPortB(iobase + MAC_REG_I2MTGID, EEP_I2C_DEV_ID);
		VNSvOutPortB(iobase + MAC_REG_I2MTGAD, byContntOffset);

		/* issue पढ़ो command */
		VNSvOutPortB(iobase + MAC_REG_I2MCSR, I2MCSR_EEMR);
		/* रुको DONE be set */
		क्रम (wDelay = 0; wDelay < W_MAX_TIMEOUT; wDelay++) अणु
			VNSvInPortB(iobase + MAC_REG_I2MCSR, &byWait);
			अगर (byWait & (I2MCSR_DONE | I2MCSR_NACK))
				अवरोध;
			PCAvDelayByIO(CB_DELAY_LOOP_WAIT);
		पूर्ण
		अगर ((wDelay < W_MAX_TIMEOUT) &&
		    (!(byWait & I2MCSR_NACK))) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	VNSvInPortB(iobase + MAC_REG_I2MDIPT, &byData);
	VNSvOutPortB(iobase + MAC_REG_I2MCFG, byOrg);
	वापस byData;
पूर्ण

/*
 * Description: Read all contents of eeprom to buffer
 *
 * Parameters:
 *  In:
 *      iobase          - I/O base address
 *  Out:
 *      pbyEepromRegs   - EEPROM content Buffer
 *
 * Return Value: none
 *
 */
व्योम SROMvReadAllContents(व्योम __iomem *iobase, अचिन्हित अक्षर *pbyEepromRegs)
अणु
	पूर्णांक     ii;

	/* ii = Rom Address */
	क्रम (ii = 0; ii < EEP_MAX_CONTEXT_SIZE; ii++) अणु
		*pbyEepromRegs = SROMbyReadEmbedded(iobase,
						    (अचिन्हित अक्षर)ii);
		pbyEepromRegs++;
	पूर्ण
पूर्ण

/*
 * Description: Read Ethernet Address from eeprom to buffer
 *
 * Parameters:
 *  In:
 *      iobase          - I/O base address
 *  Out:
 *      pbyEtherAddress - Ethernet Address buffer
 *
 * Return Value: none
 *
 */
व्योम SROMvReadEtherAddress(व्योम __iomem *iobase,
			   अचिन्हित अक्षर *pbyEtherAddress)
अणु
	अचिन्हित अक्षर ii;

	/* ii = Rom Address */
	क्रम (ii = 0; ii < ETH_ALEN; ii++) अणु
		*pbyEtherAddress = SROMbyReadEmbedded(iobase, ii);
		pbyEtherAddress++;
	पूर्ण
पूर्ण
