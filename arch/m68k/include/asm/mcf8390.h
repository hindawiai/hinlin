<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	mcf8390.h -- NS8390 support क्रम ColdFire eval boards.
 *
 *	(C) Copyright 1999-2000, Greg Ungerer (gerg@snapgear.com)
 *	(C) Copyright 2000,      Lineo (www.lineo.com)
 *	(C) Copyright 2001,      SnapGear (www.snapgear.com)
 *
 *      19990409 David W. Miller  Converted from m5206ne.h क्रम 5307 eval board
 *
 *      Hacked support क्रम m5206e Cadre III evaluation board
 *      Fred Stevens (fred.stevens@pemstar.com) 13 April 1999
 */

/****************************************************************************/
#अगर_अघोषित	mcf8390_h
#घोषणा	mcf8390_h
/****************************************************************************/


/*
 *	Support क्रम NE2000 clones devices in ColdFire based boards.
 *	Not all boards address these parts the same way, some use a
 *	direct addressing method, others use a side-band address space
 *	to access odd address रेजिस्टरs, some require byte swapping
 *	others करो not.
 */
#घोषणा	BSWAP(w)	(((w) << 8) | ((w) >> 8))
#घोषणा	RSWAP(w)	(w)


/*
 *	Define the basic hardware resources of NE2000 boards.
 */

#अगर defined(CONFIG_ARN5206)
#घोषणा NE2000_ADDR		0x40000300
#घोषणा NE2000_ODDOFFSET	0x00010000
#घोषणा NE2000_ADDRSIZE		0x00020000
#घोषणा	NE2000_IRQ_VECTOR	0xf0
#घोषणा	NE2000_IRQ_PRIORITY	2
#घोषणा	NE2000_IRQ_LEVEL	4
#घोषणा	NE2000_BYTE		अस्थिर अचिन्हित लघु
#पूर्ण_अगर

#अगर defined(CONFIG_M5206eC3)
#घोषणा	NE2000_ADDR		0x40000300
#घोषणा	NE2000_ODDOFFSET	0x00010000
#घोषणा	NE2000_ADDRSIZE		0x00020000
#घोषणा	NE2000_IRQ_VECTOR	0x1c
#घोषणा	NE2000_IRQ_PRIORITY	2
#घोषणा	NE2000_IRQ_LEVEL	4
#घोषणा	NE2000_BYTE		अस्थिर अचिन्हित लघु
#पूर्ण_अगर

#अगर defined(CONFIG_M5206e) && defined(CONFIG_NETtel)
#घोषणा NE2000_ADDR		0x30000300
#घोषणा NE2000_ADDRSIZE		0x00001000
#घोषणा NE2000_IRQ_VECTOR	25
#घोषणा NE2000_IRQ_PRIORITY	1
#घोषणा NE2000_IRQ_LEVEL	3
#घोषणा	NE2000_BYTE		अस्थिर अचिन्हित अक्षर
#पूर्ण_अगर

#अगर defined(CONFIG_M5307C3)
#घोषणा NE2000_ADDR		0x40000300
#घोषणा NE2000_ODDOFFSET	0x00010000
#घोषणा NE2000_ADDRSIZE		0x00020000
#घोषणा NE2000_IRQ_VECTOR	0x1b
#घोषणा	NE2000_BYTE		अस्थिर अचिन्हित लघु
#पूर्ण_अगर

#अगर defined(CONFIG_M5272) && defined(CONFIG_NETtel)
#घोषणा NE2000_ADDR		0x30600300
#घोषणा NE2000_ODDOFFSET	0x00008000
#घोषणा NE2000_ADDRSIZE		0x00010000
#घोषणा NE2000_IRQ_VECTOR	67
#अघोषित	BSWAP
#घोषणा	BSWAP(w)		(w)
#घोषणा	NE2000_BYTE		अस्थिर अचिन्हित लघु
#अघोषित	RSWAP
#घोषणा	RSWAP(w)		(((w) << 8) | ((w) >> 8))
#पूर्ण_अगर

#अगर defined(CONFIG_M5307) && defined(CONFIG_NETtel)
#घोषणा NE2000_ADDR0		0x30600300
#घोषणा NE2000_ADDR1		0x30800300
#घोषणा NE2000_ODDOFFSET	0x00008000
#घोषणा NE2000_ADDRSIZE		0x00010000
#घोषणा NE2000_IRQ_VECTOR0	27
#घोषणा NE2000_IRQ_VECTOR1	29
#अघोषित	BSWAP
#घोषणा	BSWAP(w)		(w)
#घोषणा	NE2000_BYTE		अस्थिर अचिन्हित लघु
#अघोषित	RSWAP
#घोषणा	RSWAP(w)		(((w) << 8) | ((w) >> 8))
#पूर्ण_अगर

#अगर defined(CONFIG_M5307) && defined(CONFIG_SECUREEDGEMP3)
#घोषणा NE2000_ADDR		0x30600300
#घोषणा NE2000_ODDOFFSET	0x00008000
#घोषणा NE2000_ADDRSIZE		0x00010000
#घोषणा NE2000_IRQ_VECTOR	27
#अघोषित	BSWAP
#घोषणा	BSWAP(w)		(w)
#घोषणा	NE2000_BYTE		अस्थिर अचिन्हित लघु
#अघोषित	RSWAP
#घोषणा	RSWAP(w)		(((w) << 8) | ((w) >> 8))
#पूर्ण_अगर

#अगर defined(CONFIG_ARN5307)
#घोषणा NE2000_ADDR		0xfe600300
#घोषणा NE2000_ODDOFFSET	0x00010000
#घोषणा NE2000_ADDRSIZE		0x00020000
#घोषणा NE2000_IRQ_VECTOR	0x1b
#घोषणा NE2000_IRQ_PRIORITY	2
#घोषणा NE2000_IRQ_LEVEL	3
#घोषणा	NE2000_BYTE		अस्थिर अचिन्हित लघु
#पूर्ण_अगर

#अगर defined(CONFIG_M5407C3)
#घोषणा NE2000_ADDR		0x40000300
#घोषणा NE2000_ODDOFFSET	0x00010000
#घोषणा NE2000_ADDRSIZE		0x00020000
#घोषणा NE2000_IRQ_VECTOR	0x1b
#घोषणा	NE2000_BYTE		अस्थिर अचिन्हित लघु
#पूर्ण_अगर

/****************************************************************************/
#पूर्ण_अगर	/* mcf8390_h */
