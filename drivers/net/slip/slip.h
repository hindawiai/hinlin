<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * slip.h	Define the SLIP device driver पूर्णांकerface and स्थिरants.
 *
 * NOTE:	THIS खाता WILL BE MOVED TO THE LINUX INCLUDE सूचीECTORY
 *		AS SOON AS POSSIBLE!
 *
 * Version:	@(#)slip.h	1.2.0	03/28/93
 *
 * Fixes:
 *		Alan Cox	: 	Added slip mtu field.
 *		Matt Dillon	:	Prपूर्णांकable slip (borrowed from net2e)
 *		Alan Cox	:	Added SL_SLIP_LOTS
 *	Dmitry Gorodchanin	:	A lot of changes in the 'struct slip'
 *	Dmitry Gorodchanin	:	Added CSLIP statistics.
 *	Stanislav Voronyi	:	Make line checking as created by
 *					Igor Chechik, RELCOM Corp.
 *	Craig Schlenter		:	Fixed #घोषणा bug that caused
 *					CSLIP telnets to hang in 1.3.61-6
 *
 * Author:	Fred N. van Kempen, <waltje@uwalt.nl.mugnet.org>
 */
#अगर_अघोषित _LINUX_SLIP_H
#घोषणा _LINUX_SLIP_H


#अगर defined(CONFIG_INET) && defined(CONFIG_SLIP_COMPRESSED)
# define SL_INCLUDE_CSLIP
#पूर्ण_अगर

#अगर_घोषित SL_INCLUDE_CSLIP
# define SL_MODE_DEFAULT SL_MODE_ADAPTIVE
#अन्यथा
# define SL_MODE_DEFAULT SL_MODE_SLIP
#पूर्ण_अगर

/* SLIP configuration. */
#घोषणा SL_NRUNIT	256		/* MAX number of SLIP channels;
					   This can be overridden with
					   insmod -oslip_maxdev=nnn	*/
#घोषणा SL_MTU		296		/* 296; I am used to 600- FvK	*/

/* SLIP protocol अक्षरacters. */
#घोषणा END             0300		/* indicates end of frame	*/
#घोषणा ESC             0333		/* indicates byte stuffing	*/
#घोषणा ESC_END         0334		/* ESC ESC_END means END 'data'	*/
#घोषणा ESC_ESC         0335		/* ESC ESC_ESC means ESC 'data'	*/


काष्ठा slip अणु
  पूर्णांक			magic;

  /* Various fields. */
  काष्ठा tty_काष्ठा	*tty;		/* ptr to TTY काष्ठाure		*/
  काष्ठा net_device	*dev;		/* easy क्रम पूर्णांकr handling	*/
  spinlock_t		lock;
  काष्ठा work_काष्ठा	tx_work;	/* Flushes transmit buffer	*/

#अगर_घोषित SL_INCLUDE_CSLIP
  काष्ठा slcompress	*slcomp;	/* क्रम header compression 	*/
  अचिन्हित अक्षर		*cbuff;		/* compression buffer		*/
#पूर्ण_अगर

  /* These are poपूर्णांकers to the दो_स्मृति()ed frame buffers. */
  अचिन्हित अक्षर		*rbuff;		/* receiver buffer		*/
  पूर्णांक                   rcount;         /* received अक्षरs counter       */
  अचिन्हित अक्षर		*xbuff;		/* transmitter buffer		*/
  अचिन्हित अक्षर         *xhead;         /* poपूर्णांकer to next byte to XMIT */
  पूर्णांक                   xleft;          /* bytes left in XMIT queue     */
  पूर्णांक			mtu;		/* Our mtu (to spot changes!)   */
  पूर्णांक                   buffsize;       /* Max buffers sizes            */

#अगर_घोषित CONFIG_SLIP_MODE_SLIP6
  पूर्णांक			xdata, xbits;	/* 6 bit slip controls 		*/
#पूर्ण_अगर

  अचिन्हित दीर्घ		flags;		/* Flag values/ mode etc	*/
#घोषणा SLF_INUSE	0		/* Channel in use               */
#घोषणा SLF_ESCAPE	1               /* ESC received                 */
#घोषणा SLF_ERROR	2               /* Parity, etc. error           */
#घोषणा SLF_KEEPTEST	3		/* Keepalive test flag		*/
#घोषणा SLF_OUTWAIT	4		/* is outpacket was flag	*/

  अचिन्हित अक्षर		mode;		/* SLIP mode			*/
  अचिन्हित अक्षर		leased;
  pid_t			pid;
#घोषणा SL_MODE_SLIP	0
#घोषणा SL_MODE_CSLIP	1
#घोषणा SL_MODE_SLIP6	2		/* Matt Dillon's prपूर्णांकable slip */
#घोषणा SL_MODE_CSLIP6	(SL_MODE_SLIP6|SL_MODE_CSLIP)
#घोषणा SL_MODE_AX25	4
#घोषणा SL_MODE_ADAPTIVE 8
#अगर_घोषित CONFIG_SLIP_SMART
  अचिन्हित अक्षर		outfill;	/* # of sec between outfill packet */
  अचिन्हित अक्षर		keepalive;	/* keepalive seconds		*/
  काष्ठा समयr_list	outfill_समयr;
  काष्ठा समयr_list	keepalive_समयr;
#पूर्ण_अगर
पूर्ण;

#घोषणा SLIP_MAGIC 0x5302

#पूर्ण_अगर	/* _LINUX_SLIP.H */
