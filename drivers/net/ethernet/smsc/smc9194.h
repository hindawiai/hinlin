<शैली गुरु>
/*------------------------------------------------------------------------
 . smc9194.h
 . Copyright (C) 1996 by Erik Stahlman
 .
 . This software may be used and distributed according to the terms
 . of the GNU General Public License, incorporated herein by reference.
 .
 . This file contains रेजिस्टर inक्रमmation and access macros क्रम
 . the SMC91xxx chipset.
 .
 . Inक्रमmation contained in this file was obtained from the SMC91C94
 . manual from SMC.  To get a copy, अगर you really want one, you can find
 . inक्रमmation under www.smc.com in the components भागision.
 . ( this thanks to advice from Donald Becker ).
 .
 . Authors
 . 	Erik Stahlman				( erik@vt.edu )
 .
 . History
 . 01/06/96		 Erik Stahlman   moved definitions here from मुख्य .c file
 . 01/19/96		 Erik Stahlman	  polished this up some, and added better
 .										  error handling
 .
 ---------------------------------------------------------------------------*/
#अगर_अघोषित _SMC9194_H_
#घोषणा _SMC9194_H_

/* I want some simple types */

प्रकार अचिन्हित अक्षर			byte;
प्रकार अचिन्हित लघु			word;
प्रकार अचिन्हित दीर्घ पूर्णांक 		dword;


/* Because of bank चयनing, the SMC91xxx uses only 16 I/O ports */

#घोषणा SMC_IO_EXTENT	16


/*---------------------------------------------------------------
 .
 . A description of the SMC रेजिस्टरs is probably in order here,
 . although क्रम details, the SMC datasheet is invaluable.
 .
 . Basically, the chip has 4 banks of रेजिस्टरs ( 0 to 3 ), which
 . are accessed by writing a number पूर्णांकo the BANK_SELECT रेजिस्टर
 . ( I also use a SMC_SELECT_BANK macro क्रम this ).
 .
 . The banks are configured so that क्रम most purposes, bank 2 is all
 . that is needed क्रम simple run समय tasks.
 -----------------------------------------------------------------------*/

/*
 . Bank Select Register:
 .
 .		yyyy yyyy 0000 00xx
 .		xx 		= bank number
 .		yyyy yyyy	= 0x33, क्रम identअगरication purposes.
*/
#घोषणा	BANK_SELECT		14

/* BANK 0  */

#घोषणा	TCR 		0    	/* transmit control रेजिस्टर */
#घोषणा TCR_ENABLE	0x0001	/* अगर this is 1, we can transmit */
#घोषणा TCR_FDUPLX    	0x0800  /* receive packets sent out */
#घोषणा TCR_STP_SQET	0x1000	/* stop transmitting अगर Signal quality error */
#घोषणा	TCR_MON_CNS	0x0400	/* monitors the carrier status */
#घोषणा	TCR_PAD_ENABLE	0x0080	/* pads लघु packets to 64 bytes */

#घोषणा	TCR_CLEAR	0	/* करो NOTHING */
/* the normal settings क्रम the TCR रेजिस्टर : */
/* QUESTION: करो I want to enable padding of लघु packets ? */
#घोषणा	TCR_NORMAL  	TCR_ENABLE


#घोषणा EPH_STATUS	2
#घोषणा ES_LINK_OK	0x4000	/* is the link पूर्णांकegrity ok ? */

#घोषणा	RCR		4
#घोषणा RCR_SOFTRESET	0x8000 	/* resets the chip */
#घोषणा	RCR_STRIP_CRC	0x200	/* strips CRC */
#घोषणा RCR_ENABLE	0x100	/* IFF this is set, we can receive packets */
#घोषणा RCR_ALMUL	0x4 	/* receive all multicast packets */
#घोषणा	RCR_PROMISC	0x2	/* enable promiscuous mode */

/* the normal settings क्रम the RCR रेजिस्टर : */
#घोषणा	RCR_NORMAL	(RCR_STRIP_CRC | RCR_ENABLE)
#घोषणा RCR_CLEAR	0x0		/* set it to a base state */

#घोषणा	COUNTER		6
#घोषणा	MIR		8
#घोषणा	MCR		10
/* 12 is reserved */

/* BANK 1 */
#घोषणा CONFIG			0
#घोषणा CFG_AUI_SELECT	 	0x100
#घोषणा	BASE			2
#घोषणा	ADDR0			4
#घोषणा	ADDR1			6
#घोषणा	ADDR2			8
#घोषणा	GENERAL			10
#घोषणा	CONTROL			12
#घोषणा	CTL_POWERDOWN		0x2000
#घोषणा	CTL_LE_ENABLE		0x80
#घोषणा	CTL_CR_ENABLE		0x40
#घोषणा	CTL_TE_ENABLE		0x0020
#घोषणा CTL_AUTO_RELEASE	0x0800
#घोषणा	CTL_EPROM_ACCESS	0x0003 /* high अगर Eprom is being पढ़ो */

/* BANK 2 */
#घोषणा MMU_CMD		0
#घोषणा MC_BUSY		1	/* only पढ़ोable bit in the रेजिस्टर */
#घोषणा MC_NOP		0
#घोषणा	MC_ALLOC	0x20  	/* or with number of 256 byte packets */
#घोषणा	MC_RESET	0x40
#घोषणा	MC_REMOVE	0x60  	/* हटाओ the current rx packet */
#घोषणा MC_RELEASE  	0x80  	/* हटाओ and release the current rx packet */
#घोषणा MC_FREEPKT  	0xA0  	/* Release packet in PNR रेजिस्टर */
#घोषणा MC_ENQUEUE	0xC0 	/* Enqueue the packet क्रम transmit */

#घोषणा	PNR_ARR		2
#घोषणा FIFO_PORTS	4

#घोषणा FP_RXEMPTY  0x8000
#घोषणा FP_TXEMPTY  0x80

#घोषणा	POINTER		6
#घोषणा PTR_READ	0x2000
#घोषणा	PTR_RCV		0x8000
#घोषणा	PTR_AUTOINC 	0x4000
#घोषणा PTR_AUTO_INC	0x0040

#घोषणा	DATA_1		8
#घोषणा	DATA_2		10
#घोषणा	INTERRUPT	12

#घोषणा INT_MASK	13
#घोषणा IM_RCV_INT	0x1
#घोषणा	IM_TX_INT	0x2
#घोषणा	IM_TX_EMPTY_INT	0x4
#घोषणा	IM_ALLOC_INT	0x8
#घोषणा	IM_RX_OVRN_INT	0x10
#घोषणा	IM_EPH_INT	0x20
#घोषणा	IM_ERCV_INT	0x40 /* not on SMC9192 */

/* BANK 3 */
#घोषणा	MULTICAST1	0
#घोषणा	MULTICAST2	2
#घोषणा	MULTICAST3	4
#घोषणा	MULTICAST4	6
#घोषणा	MGMT		8
#घोषणा	REVISION	10 /* ( hi: chip id   low: rev # ) */


/* this is NOT on SMC9192 */
#घोषणा	ERCV		12

#घोषणा CHIP_9190	3
#घोषणा CHIP_9194	4
#घोषणा CHIP_9195	5
#घोषणा CHIP_91100	7

अटल स्थिर अक्षर * chip_ids[ 15 ] =  अणु
	शून्य, शून्य, शून्य,
	/* 3 */ "SMC91C90/91C92",
	/* 4 */ "SMC91C94",
	/* 5 */ "SMC91C95",
	शून्य,
	/* 7 */ "SMC91C100",
	/* 8 */ "SMC91C100FD",
	शून्य, शून्य, शून्य,
	शून्य, शून्य, शून्यपूर्ण;

/*
 . Transmit status bits
*/
#घोषणा TS_SUCCESS 0x0001
#घोषणा TS_LOSTCAR 0x0400
#घोषणा TS_LATCOL  0x0200
#घोषणा TS_16COL   0x0010

/*
 . Receive status bits
*/
#घोषणा RS_ALGNERR	0x8000
#घोषणा RS_BADCRC	0x2000
#घोषणा RS_ODDFRAME	0x1000
#घोषणा RS_TOOLONG	0x0800
#घोषणा RS_TOOSHORT	0x0400
#घोषणा RS_MULTICAST	0x0001
#घोषणा RS_ERRORS	(RS_ALGNERR | RS_BADCRC | RS_TOOLONG | RS_TOOSHORT)

अटल स्थिर अक्षर * पूर्णांकerfaces[ 2 ] = अणु "TP", "AUI" पूर्ण;

/*-------------------------------------------------------------------------
 .  I define some macros to make it easier to करो somewhat common
 . or slightly complicated, repeated tasks.
 --------------------------------------------------------------------------*/

/* select a रेजिस्टर bank, 0 to 3  */

#घोषणा SMC_SELECT_BANK(x)  अणु outw( x, ioaddr + BANK_SELECT ); पूर्ण

/* define a small delay क्रम the reset */
#घोषणा SMC_DELAY() अणु inw( ioaddr + RCR );\
			inw( ioaddr + RCR );\
			inw( ioaddr + RCR );  पूर्ण

/* this enables an पूर्णांकerrupt in the पूर्णांकerrupt mask रेजिस्टर */
#घोषणा SMC_ENABLE_INT(x) अणु\
		अचिन्हित अक्षर mask;\
		SMC_SELECT_BANK(2);\
		mask = inb( ioaddr + INT_MASK );\
		mask |= (x);\
		outb( mask, ioaddr + INT_MASK ); \
पूर्ण

/* this disables an पूर्णांकerrupt from the पूर्णांकerrupt mask रेजिस्टर */

#घोषणा SMC_DISABLE_INT(x) अणु\
		अचिन्हित अक्षर mask;\
		SMC_SELECT_BANK(2);\
		mask = inb( ioaddr + INT_MASK );\
		mask &= ~(x);\
		outb( mask, ioaddr + INT_MASK ); \
पूर्ण

/*----------------------------------------------------------------------
 . Define the पूर्णांकerrupts that I want to receive from the card
 .
 . I want:
 .  IM_EPH_INT, क्रम nasty errors
 .  IM_RCV_INT, क्रम happy received packets
 .  IM_RX_OVRN_INT, because I have to kick the receiver
 --------------------------------------------------------------------------*/
#घोषणा SMC_INTERRUPT_MASK   (IM_EPH_INT | IM_RX_OVRN_INT | IM_RCV_INT)

#पूर्ण_अगर  /* _SMC_9194_H_ */

