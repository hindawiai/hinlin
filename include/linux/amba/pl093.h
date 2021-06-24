<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* linux/amba/pl093.h
 *
 * Copyright (c) 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * AMBA PL093 SSMC (synchronous अटल memory controller)
 *  See DDI0236.pdf (r0p4) क्रम more details
*/

#घोषणा SMB_BANK(x)	((x) * 0x20) /* each bank control set is 0x20 apart */

/* Offsets क्रम SMBxxxxRy रेजिस्टरs */

#घोषणा SMBIDCYR	(0x00)
#घोषणा SMBWSTRDR	(0x04)
#घोषणा SMBWSTWRR	(0x08)
#घोषणा SMBWSTOENR	(0x0C)
#घोषणा SMBWSTWENR	(0x10)
#घोषणा SMBCR		(0x14)
#घोषणा SMBSR		(0x18)
#घोषणा SMBWSTBRDR	(0x1C)

/* Masks क्रम SMB रेजिस्टरs */
#घोषणा IDCY_MASK	(0xf)
#घोषणा WSTRD_MASK	(0xf)
#घोषणा WSTWR_MASK	(0xf)
#घोषणा WSTOEN_MASK	(0xf)
#घोषणा WSTWEN_MASK	(0xf)

/* Notes from datasheet:
 *	WSTOEN <= WSTRD
 *	WSTWEN <= WSTWR
 *
 * WSTOEN is not used with nWAIT
 */

/* SMBCR bit definitions */
#घोषणा SMBCR_BIWRITEEN		(1 << 21)
#घोषणा SMBCR_ADDRVALIDWRITEEN	(1 << 20)
#घोषणा SMBCR_SYNCWRITE		(1 << 17)
#घोषणा SMBCR_BMWRITE		(1 << 16)
#घोषणा SMBCR_WRAPREAD		(1 << 14)
#घोषणा SMBCR_BIREADEN		(1 << 13)
#घोषणा SMBCR_ADDRVALIDREADEN	(1 << 12)
#घोषणा SMBCR_SYNCREAD		(1 << 9)
#घोषणा SMBCR_BMREAD		(1 << 8)
#घोषणा SMBCR_SMBLSPOL		(1 << 6)
#घोषणा SMBCR_WP		(1 << 3)
#घोषणा SMBCR_WAITEN		(1 << 2)
#घोषणा SMBCR_WAITPOL		(1 << 1)
#घोषणा SMBCR_RBLE		(1 << 0)

#घोषणा SMBCR_BURSTLENWRITE_MASK	(3 << 18)
#घोषणा SMBCR_BURSTLENWRITE_4		(0 << 18)
#घोषणा SMBCR_BURSTLENWRITE_8		(1 << 18)
#घोषणा SMBCR_BURSTLENWRITE_RESERVED	(2 << 18)
#घोषणा SMBCR_BURSTLENWRITE_CONTINUOUS	(3 << 18)

#घोषणा SMBCR_BURSTLENREAD_MASK		(3 << 10)
#घोषणा SMBCR_BURSTLENREAD_4		(0 << 10)
#घोषणा SMBCR_BURSTLENREAD_8		(1 << 10)
#घोषणा SMBCR_BURSTLENREAD_16		(2 << 10)
#घोषणा SMBCR_BURSTLENREAD_CONTINUOUS	(3 << 10)

#घोषणा SMBCR_MW_MASK			(3 << 4)
#घोषणा SMBCR_MW_8BIT			(0 << 4)
#घोषणा SMBCR_MW_16BIT			(1 << 4)
#घोषणा SMBCR_MW_M32BIT			(2 << 4)

/* SSMC status रेजिस्टरs */
#घोषणा SSMCCSR		(0x200)
#घोषणा SSMCCR		(0x204)
#घोषणा SSMCITCR	(0x208)
#घोषणा SSMCITIP	(0x20C)
#घोषणा SSMCITIOP	(0x210)
