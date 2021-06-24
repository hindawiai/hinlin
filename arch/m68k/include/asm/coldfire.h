<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	coldfire.h -- Motorola ColdFire CPU sepecअगरic defines
 *
 *	(C) Copyright 1999-2006, Greg Ungerer (gerg@snapgear.com)
 *	(C) Copyright 2000, Lineo (www.lineo.com)
 */

/****************************************************************************/
#अगर_अघोषित	coldfire_h
#घोषणा	coldfire_h
/****************************************************************************/


/*
 *	Define master घड़ी frequency. This is करोne at config समय now.
 *	No poपूर्णांक क्रमागतerating करोzens of possible घड़ी options here. And
 *	in any हाल new boards come aदीर्घ from समय to समय that have yet
 *	another dअगरferent घड़ीing frequency.
 */
#अगर_घोषित CONFIG_CLOCK_FREQ
#घोषणा	MCF_CLK		CONFIG_CLOCK_FREQ
#अन्यथा
#त्रुटि "Don't know what your ColdFire CPU clock frequency is??"
#पूर्ण_अगर

/*
 *	Define the processor पूर्णांकernal peripherals base address.
 *
 *	The majority of ColdFire parts use an MBAR रेजिस्टर to set
 *	the base address. Some have an IPSBAR रेजिस्टर instead, and it
 *	has slightly dअगरferent rules on its size and alignment. Some
 *	parts have fixed addresses and the पूर्णांकernal peripherals cannot
 *	be relocated in the CPU address space.
 *
 *	The value of MBAR or IPSBAR is config समय selectable, we no
 *	दीर्घer hard define it here. No MBAR or IPSBAR will be defined अगर
 *	this part has a fixed peripheral address map.
 */
#अगर_घोषित CONFIG_MBAR
#घोषणा	MCF_MBAR	CONFIG_MBAR
#पूर्ण_अगर
#अगर_घोषित CONFIG_IPSBAR
#घोषणा	MCF_IPSBAR	CONFIG_IPSBAR
#पूर्ण_अगर

/****************************************************************************/
#पूर्ण_अगर	/* coldfire_h */
