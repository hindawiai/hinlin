<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *	nv_tco:	TCO समयr driver क्रम nVidia chipsets.
 *
 *	(c) Copyright 2005 Google Inc., All Rights Reserved.
 *
 *	Supported Chipsets:
 *		- MCP51/MCP55
 *
 *	(c) Copyright 2000 kernel concepts <nils@kernelconcepts.de>, All Rights
 *	Reserved.
 *				https://www.kernelconcepts.de
 *
 *	Neither kernel concepts nor Nils Faerber admit liability nor provide
 *	warranty क्रम any of this software. This material is provided
 *	"AS-IS" and at no अक्षरge.
 *
 *	(c) Copyright 2000	kernel concepts <nils@kernelconcepts.de>
 *				developed क्रम
 *                              Jentro AG, Haar/Munich (Germany)
 *
 *	TCO समयr driver क्रम NV chipsets
 *	based on softकरोg.c by Alan Cox <alan@redhat.com>
 */

/*
 * Some address definitions क्रम the TCO
 */

#घोषणा TCO_RLD(base)	((base) + 0x00)	/* TCO Timer Reload and Current Value */
#घोषणा TCO_TMR(base)	((base) + 0x01)	/* TCO Timer Initial Value	*/

#घोषणा TCO_STS(base)	((base) + 0x04)	/* TCO Status Register		*/
/*
 * TCO Boot Status bit: set on TCO reset, reset by software or standby
 * घातer-good (survives reboots), unक्रमtunately this bit is never
 * set.
 */
#  define TCO_STS_BOOT_STS	(1 << 9)
/*
 * first and 2nd समयout status bits, these also survive a warm boot,
 * and they work, so we use them.
 */
#  define TCO_STS_TCO_INT_STS	(1 << 1)
#  define TCO_STS_TCO2TO_STS	(1 << 10)
#  define TCO_STS_RESET		(TCO_STS_BOOT_STS | TCO_STS_TCO2TO_STS | \
				 TCO_STS_TCO_INT_STS)

#घोषणा TCO_CNT(base)	((base) + 0x08)	/* TCO Control Register	*/
#  define TCO_CNT_TCOHALT	(1 << 12)

#घोषणा MCP51_SMBUS_SETUP_B 0xe8
#  define MCP51_SMBUS_SETUP_B_TCO_REBOOT (1 << 25)

/*
 * The SMI_EN रेजिस्टर is at the base io address + 0x04,
 * जबतक TCOBASE is + 0x40.
 */
#घोषणा MCP51_SMI_EN(base)	((base) - 0x40 + 0x04)
#  define MCP51_SMI_EN_TCO	((1 << 4) | (1 << 5))
