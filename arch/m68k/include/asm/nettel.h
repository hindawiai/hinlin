<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	nettel.h -- Lineo (क्रमmerly Moreton Bay) NETtel support.
 *
 *	(C) Copyright 1999-2000, Moreton Bay (www.moretonbay.com)
 * 	(C) Copyright 2000-2001, Lineo Inc. (www.lineo.com) 
 * 	(C) Copyright 2001-2002, SnapGear Inc., (www.snapgear.com) 
 */

/****************************************************************************/
#अगर_अघोषित	nettel_h
#घोषणा	nettel_h
/****************************************************************************/


/****************************************************************************/
#अगर_घोषित CONFIG_NETtel
/****************************************************************************/

#अगर_घोषित CONFIG_COLDFIRE
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/पन.स>
#पूर्ण_अगर

/*---------------------------------------------------------------------------*/
#अगर defined(CONFIG_M5307)
/*
 *	NETtel/5307 based hardware first. DTR/DCD lines are wired to
 *	GPIO lines. Most of the LED's are driver through a latch
 *	connected to CS2.
 */
#घोषणा	MCFPP_DCD1	0x0001
#घोषणा	MCFPP_DCD0	0x0002
#घोषणा	MCFPP_DTR1	0x0004
#घोषणा	MCFPP_DTR0	0x0008

#घोषणा	NETtel_LEDADDR	0x30400000

#अगर_अघोषित __ASSEMBLY__

बाह्य अस्थिर अचिन्हित लघु ppdata;

/*
 *	These functions defined to give quasi generic access to the
 *	PPIO bits used क्रम DTR/DCD.
 */
अटल __अंतरभूत__ अचिन्हित पूर्णांक mcf_getppdata(व्योम)
अणु
	अस्थिर अचिन्हित लघु *pp;
	pp = (अस्थिर अचिन्हित लघु *) MCFSIM_PADAT;
	वापस((अचिन्हित पूर्णांक) *pp);
पूर्ण

अटल __अंतरभूत__ व्योम mcf_setppdata(अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक bits)
अणु
	अस्थिर अचिन्हित लघु *pp;
	pp = (अस्थिर अचिन्हित लघु *) MCFSIM_PADAT;
	ppdata = (ppdata & ~mask) | bits;
	*pp = ppdata;
पूर्ण
#पूर्ण_अगर

/*---------------------------------------------------------------------------*/
#या_अगर defined(CONFIG_M5206e)
/*
 *	NETtel/5206e based hardware has leds on latch on CS3.
 *	No support modem क्रम lines??
 */
#घोषणा	NETtel_LEDADDR	0x50000000

/*---------------------------------------------------------------------------*/
#या_अगर defined(CONFIG_M5272)
/*
 *	NETtel/5272 based hardware. DTR/DCD lines are wired to GPB lines.
 */
#घोषणा	MCFPP_DCD0	0x0080
#घोषणा	MCFPP_DCD1	0x0000		/* Port 1 no DCD support */
#घोषणा	MCFPP_DTR0	0x0040
#घोषणा	MCFPP_DTR1	0x0000		/* Port 1 no DTR support */

#अगर_अघोषित __ASSEMBLY__
/*
 *	These functions defined to give quasi generic access to the
 *	PPIO bits used क्रम DTR/DCD.
 */
अटल __अंतरभूत__ अचिन्हित पूर्णांक mcf_getppdata(व्योम)
अणु
	वापस पढ़ोw(MCFSIM_PBDAT);
पूर्ण

अटल __अंतरभूत__ व्योम mcf_setppdata(अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक bits)
अणु
	ग_लिखोw((पढ़ोw(MCFSIM_PBDAT) & ~mask) | bits, MCFSIM_PBDAT);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
/*---------------------------------------------------------------------------*/

/****************************************************************************/
#पूर्ण_अगर /* CONFIG_NETtel */
/****************************************************************************/
#पूर्ण_अगर	/* nettel_h */
