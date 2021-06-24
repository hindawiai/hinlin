<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1993 Hamish Macकरोnald
 *  Copyright (C) 1999 D. Jeff Dionne
 *  Copyright (C) 2001 Georges Menie, Ken Desmet
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/MC68VZ328.h>

/***************************************************************************/
/*                        Init Drangon Engine hardware                     */
/***************************************************************************/

अटल व्योम dragen2_reset(व्योम)
अणु
	local_irq_disable();

#अगर_घोषित CONFIG_INIT_LCD
	PBDATA |= 0x20;				/* disable CCFL light */
	PKDATA |= 0x4;				/* disable LCD controller */
	LCKCON = 0;
#पूर्ण_अगर

	__यंत्र__ __अस्थिर__(
		"reset\n\t"
		"moveal #0x04000000, %a0\n\t"
		"moveal 0(%a0), %sp\n\t"
		"moveal 4(%a0), %a0\n\t"
		"jmp (%a0)"
	);
पूर्ण

व्योम __init init_dragen2(अक्षर *command, पूर्णांक size)
अणु
	mach_reset = dragen2_reset;

#अगर_घोषित CONFIG_सूचीECT_IO_ACCESS
	SCR = 0x10;					/* allow user access to पूर्णांकernal रेजिस्टरs */
#पूर्ण_अगर

	/* CSGB Init */
	CSGBB = 0x4000;
	CSB = 0x1a1;

	/* CS8900 init */
	/* PK3: hardware sleep function pin, active low */
	PKSEL |= PK(3);				/* select pin as I/O */
	PKसूची |= PK(3);				/* select pin as output */
	PKDATA |= PK(3);			/* set pin high */

	/* PF5: hardware reset function pin, active high */
	PFSEL |= PF(5);				/* select pin as I/O */
	PFसूची |= PF(5);				/* select pin as output */
	PFDATA &= ~PF(5);			/* set pin low */

	/* cs8900 hardware reset */
	PFDATA |= PF(5);
	अणु पूर्णांक i; क्रम (i = 0; i < 32000; ++i); पूर्ण
	PFDATA &= ~PF(5);

	/* INT1 enable (cs8900 IRQ) */
	PDPOL &= ~PD(1);			/* active high संकेत */
	PDIQEG &= ~PD(1);
	PसूचीQEN |= PD(1);			/* IRQ enabled */

#अगर_घोषित CONFIG_INIT_LCD
	/* initialize LCD controller */
	LSSA = (दीर्घ) screen_bits;
	LVPW = 0x14;
	LXMAX = 0x140;
	LYMAX = 0xef;
	LRRA = 0;
	LPXCD = 3;
	LPICF = 0x08;
	LPOLCF = 0;
	LCKCON = 0x80;
	PCPDEN = 0xff;
	PCSEL = 0;

	/* Enable LCD controller */
	PKसूची |= 0x4;
	PKSEL |= 0x4;
	PKDATA &= ~0x4;

	/* Enable CCFL backlighting circuit */
	PBसूची |= 0x20;
	PBSEL |= 0x20;
	PBDATA &= ~0x20;

	/* contrast control रेजिस्टर */
	PFसूची |= 0x1;
	PFSEL &= ~0x1;
	PWMR = 0x037F;
#पूर्ण_अगर
पूर्ण
