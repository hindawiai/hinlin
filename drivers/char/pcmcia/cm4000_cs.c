<शैली गुरु>
 /*
  * A driver क्रम the PCMCIA Smartcard Reader "Omnikey CardMan Mobile 4000"
  *
  * cm4000_cs.c support.linux@omnikey.com
  *
  * Tue Oct 23 11:32:43 GMT 2001 herp - cleaned up header files
  * Sun Jan 20 10:11:15 MET 2002 herp - added modversion header files
  * Thu Nov 14 16:34:11 GMT 2002 mh   - added PPS functionality
  * Tue Nov 19 16:36:27 GMT 2002 mh   - added SUSPEND/RESUME functionailty
  * Wed Jul 28 12:55:01 CEST 2004 mh  - kernel 2.6 adjusपंचांगents
  *
  * current version: 2.4.0gm4
  *
  * (C) 2000,2001,2002,2003,2004 Omnikey AG
  *
  * (C) 2005-2006 Harald Welte <laक्रमge@gnumonks.org>
  * 	- Adhere to Kernel process/coding-style.rst
  * 	- Port to 2.6.13 "new" style PCMCIA
  * 	- Check क्रम copy_अणुfrom,toपूर्ण_user वापस values
  * 	- Use nonseekable_खोलो()
  * 	- add class पूर्णांकerface क्रम udev device creation
  *
  * All rights reserved. Licensed under dual BSD/GPL license.
  */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/ds.h>

#समावेश <linux/cm4000_cs.h>

/* #घोषणा ATR_CSUM */

#घोषणा पढ़ोer_to_dev(x)	(&x->p_dev->dev)

/* n (debug level) is ignored */
/* additional debug output may be enabled by re-compiling with
 * CM4000_DEBUG set */
/* #घोषणा CM4000_DEBUG */
#घोषणा DEBUGP(n, rdr, x, args...) करो अणु 		\
		dev_dbg(पढ़ोer_to_dev(rdr), "%s:" x, 	\
			   __func__ , ## args);		\
	पूर्ण जबतक (0)

अटल DEFINE_MUTEX(cmm_mutex);

#घोषणा	T_1SEC		(HZ)
#घोषणा	T_10MSEC	msecs_to_jअगरfies(10)
#घोषणा	T_20MSEC	msecs_to_jअगरfies(20)
#घोषणा	T_40MSEC	msecs_to_jअगरfies(40)
#घोषणा	T_50MSEC	msecs_to_jअगरfies(50)
#घोषणा	T_100MSEC	msecs_to_jअगरfies(100)
#घोषणा	T_500MSEC	msecs_to_jअगरfies(500)

अटल व्योम cm4000_release(काष्ठा pcmcia_device *link);

अटल पूर्णांक major;		/* major number we get from the kernel */

/* note: the first state has to have number 0 always */

#घोषणा	M_FETCH_ATR	0
#घोषणा	M_TIMEOUT_WAIT	1
#घोषणा	M_READ_ATR_LEN	2
#घोषणा	M_READ_ATR	3
#घोषणा	M_ATR_PRESENT	4
#घोषणा	M_BAD_CARD	5
#घोषणा M_CARDOFF	6

#घोषणा	LOCK_IO			0
#घोषणा	LOCK_MONITOR		1

#घोषणा IS_AUTOPPS_ACT		 6
#घोषणा	IS_PROCBYTE_PRESENT	 7
#घोषणा	IS_INVREV		 8
#घोषणा IS_ANY_T0		 9
#घोषणा	IS_ANY_T1		10
#घोषणा	IS_ATR_PRESENT		11
#घोषणा	IS_ATR_VALID		12
#घोषणा	IS_CMM_ABSENT		13
#घोषणा	IS_BAD_LENGTH		14
#घोषणा	IS_BAD_CSUM		15
#घोषणा	IS_BAD_CARD		16

#घोषणा REG_FLAGS0(x)		(x + 0)
#घोषणा REG_FLAGS1(x)		(x + 1)
#घोषणा REG_NUM_BYTES(x)	(x + 2)
#घोषणा REG_BUF_ADDR(x)		(x + 3)
#घोषणा REG_BUF_DATA(x)		(x + 4)
#घोषणा REG_NUM_SEND(x)		(x + 5)
#घोषणा REG_BAUDRATE(x)		(x + 6)
#घोषणा REG_STOPBITS(x)		(x + 7)

काष्ठा cm4000_dev अणु
	काष्ठा pcmcia_device *p_dev;

	अचिन्हित अक्षर atr[MAX_ATR];
	अचिन्हित अक्षर rbuf[512];
	अचिन्हित अक्षर sbuf[512];

	रुको_queue_head_t devq;		/* when removing cardman must not be
					   zeroed! */

	रुको_queue_head_t ioq;		/* अगर IO is locked, रुको on this Q */
	रुको_queue_head_t atrq;		/* रुको क्रम ATR valid */
	रुको_queue_head_t पढ़ोq;	/* used by ग_लिखो to wake blk.पढ़ो */

	/* warning: करो not move this fields.
	 * initialising to zero depends on it - see ZERO_DEV below.  */
	अचिन्हित अक्षर atr_csum;
	अचिन्हित अक्षर atr_len_retry;
	अचिन्हित लघु atr_len;
	अचिन्हित लघु rlen;	/* bytes avail. after ग_लिखो */
	अचिन्हित लघु rpos;	/* latest पढ़ो pos. ग_लिखो zeroes */
	अचिन्हित अक्षर procbyte;	/* T=0 procedure byte */
	अचिन्हित अक्षर mstate;	/* state of card monitor */
	अचिन्हित अक्षर cwarn;	/* slow करोwn warning */
	अचिन्हित अक्षर flags0;	/* cardman IO-flags 0 */
	अचिन्हित अक्षर flags1;	/* cardman IO-flags 1 */
	अचिन्हित पूर्णांक mdelay;	/* variable monitor speeds, in jअगरfies */

	अचिन्हित पूर्णांक baudv;	/* baud value क्रम speed */
	अचिन्हित अक्षर ta1;
	अचिन्हित अक्षर proto;	/* T=0, T=1, ... */
	अचिन्हित दीर्घ flags;	/* lock+flags (MONITOR,IO,ATR) * क्रम concurrent
				   access */

	अचिन्हित अक्षर pts[4];

	काष्ठा समयr_list समयr;	/* used to keep monitor running */
	पूर्णांक monitor_running;
पूर्ण;

#घोषणा	ZERO_DEV(dev)  						\
	स_रखो(&dev->atr_csum,0,				\
		माप(काष्ठा cm4000_dev) - 			\
		दुरत्व(काष्ठा cm4000_dev, atr_csum))

अटल काष्ठा pcmcia_device *dev_table[CM4000_MAX_DEV];
अटल काष्ठा class *cmm_class;

/* This table करोesn't use spaces after the comma between fields and thus
 * violates process/coding-style.rst.  However, I करोn't really think wrapping it around will
 * make it any clearer to पढ़ो -HW */
अटल अचिन्हित अक्षर fi_di_table[10][14] = अणु
/*FI     00   01   02   03   04   05   06   07   08   09   10   11   12   13 */
/*DI */
/* 0 */ अणु0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11पूर्ण,
/* 1 */ अणु0x01,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x91,0x11,0x11,0x11,0x11पूर्ण,
/* 2 */ अणु0x02,0x12,0x22,0x32,0x11,0x11,0x11,0x11,0x11,0x92,0xA2,0xB2,0x11,0x11पूर्ण,
/* 3 */ अणु0x03,0x13,0x23,0x33,0x43,0x53,0x63,0x11,0x11,0x93,0xA3,0xB3,0xC3,0xD3पूर्ण,
/* 4 */ अणु0x04,0x14,0x24,0x34,0x44,0x54,0x64,0x11,0x11,0x94,0xA4,0xB4,0xC4,0xD4पूर्ण,
/* 5 */ अणु0x00,0x15,0x25,0x35,0x45,0x55,0x65,0x11,0x11,0x95,0xA5,0xB5,0xC5,0xD5पूर्ण,
/* 6 */ अणु0x06,0x16,0x26,0x36,0x46,0x56,0x66,0x11,0x11,0x96,0xA6,0xB6,0xC6,0xD6पूर्ण,
/* 7 */ अणु0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11पूर्ण,
/* 8 */ अणु0x08,0x11,0x28,0x38,0x48,0x58,0x68,0x11,0x11,0x98,0xA8,0xB8,0xC8,0xD8पूर्ण,
/* 9 */ अणु0x09,0x19,0x29,0x39,0x49,0x59,0x69,0x11,0x11,0x99,0xA9,0xB9,0xC9,0xD9पूर्ण
पूर्ण;

#अगर_अघोषित CM4000_DEBUG
#घोषणा	xoutb	outb
#घोषणा	xinb	inb
#अन्यथा
अटल अंतरभूत व्योम xoutb(अचिन्हित अक्षर val, अचिन्हित लघु port)
अणु
	pr_debug("outb(val=%.2x,port=%.4x)\n", val, port);
	outb(val, port);
पूर्ण
अटल अंतरभूत अचिन्हित अक्षर xinb(अचिन्हित लघु port)
अणु
	अचिन्हित अक्षर val;

	val = inb(port);
	pr_debug("%.2x=inb(%.4x)\n", val, port);

	वापस val;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित अक्षर invert_revert(अचिन्हित अक्षर ch)
अणु
	वापस bitrev8(~ch);
पूर्ण

अटल व्योम str_invert_revert(अचिन्हित अक्षर *b, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		b[i] = invert_revert(b[i]);
पूर्ण

#घोषणा	ATRLENCK(dev,pos) \
	अगर (pos>=dev->atr_len || pos>=MAX_ATR) \
		जाओ वापस_0;

अटल अचिन्हित पूर्णांक calc_baudv(अचिन्हित अक्षर fidi)
अणु
	अचिन्हित पूर्णांक wcrcf, wbrcf, fi_rfu, di_rfu;

	fi_rfu = 372;
	di_rfu = 1;

	/* FI */
	चयन ((fidi >> 4) & 0x0F) अणु
	हाल 0x00:
		wcrcf = 372;
		अवरोध;
	हाल 0x01:
		wcrcf = 372;
		अवरोध;
	हाल 0x02:
		wcrcf = 558;
		अवरोध;
	हाल 0x03:
		wcrcf = 744;
		अवरोध;
	हाल 0x04:
		wcrcf = 1116;
		अवरोध;
	हाल 0x05:
		wcrcf = 1488;
		अवरोध;
	हाल 0x06:
		wcrcf = 1860;
		अवरोध;
	हाल 0x07:
		wcrcf = fi_rfu;
		अवरोध;
	हाल 0x08:
		wcrcf = fi_rfu;
		अवरोध;
	हाल 0x09:
		wcrcf = 512;
		अवरोध;
	हाल 0x0A:
		wcrcf = 768;
		अवरोध;
	हाल 0x0B:
		wcrcf = 1024;
		अवरोध;
	हाल 0x0C:
		wcrcf = 1536;
		अवरोध;
	हाल 0x0D:
		wcrcf = 2048;
		अवरोध;
	शेष:
		wcrcf = fi_rfu;
		अवरोध;
	पूर्ण

	/* DI */
	चयन (fidi & 0x0F) अणु
	हाल 0x00:
		wbrcf = di_rfu;
		अवरोध;
	हाल 0x01:
		wbrcf = 1;
		अवरोध;
	हाल 0x02:
		wbrcf = 2;
		अवरोध;
	हाल 0x03:
		wbrcf = 4;
		अवरोध;
	हाल 0x04:
		wbrcf = 8;
		अवरोध;
	हाल 0x05:
		wbrcf = 16;
		अवरोध;
	हाल 0x06:
		wbrcf = 32;
		अवरोध;
	हाल 0x07:
		wbrcf = di_rfu;
		अवरोध;
	हाल 0x08:
		wbrcf = 12;
		अवरोध;
	हाल 0x09:
		wbrcf = 20;
		अवरोध;
	शेष:
		wbrcf = di_rfu;
		अवरोध;
	पूर्ण

	वापस (wcrcf / wbrcf);
पूर्ण

अटल अचिन्हित लघु io_पढ़ो_num_rec_bytes(अचिन्हित पूर्णांक iobase,
					    अचिन्हित लघु *s)
अणु
	अचिन्हित लघु पंचांगp;

	पंचांगp = *s = 0;
	करो अणु
		*s = पंचांगp;
		पंचांगp = inb(REG_NUM_BYTES(iobase)) |
				(inb(REG_FLAGS0(iobase)) & 4 ? 0x100 : 0);
	पूर्ण जबतक (पंचांगp != *s);

	वापस *s;
पूर्ण

अटल पूर्णांक parse_atr(काष्ठा cm4000_dev *dev)
अणु
	अचिन्हित अक्षर any_t1, any_t0;
	अचिन्हित अक्षर ch, अगरno;
	पूर्णांक ix, करोne;

	DEBUGP(3, dev, "-> parse_atr: dev->atr_len = %i\n", dev->atr_len);

	अगर (dev->atr_len < 3) अणु
		DEBUGP(5, dev, "parse_atr: atr_len < 3\n");
		वापस 0;
	पूर्ण

	अगर (dev->atr[0] == 0x3f)
		set_bit(IS_INVREV, &dev->flags);
	अन्यथा
		clear_bit(IS_INVREV, &dev->flags);
	ix = 1;
	अगरno = 1;
	ch = dev->atr[1];
	dev->proto = 0;		/* XXX PROTO */
	any_t1 = any_t0 = करोne = 0;
	dev->ta1 = 0x11;	/* शेषs to 9600 baud */
	करो अणु
		अगर (अगरno == 1 && (ch & 0x10)) अणु
			/* पढ़ो first पूर्णांकerface byte and TA1 is present */
			dev->ta1 = dev->atr[2];
			DEBUGP(5, dev, "Card says FiDi is 0x%.2x\n", dev->ta1);
			अगरno++;
		पूर्ण अन्यथा अगर ((अगरno == 2) && (ch & 0x10)) अणु /* TA(2) */
			dev->ta1 = 0x11;
			अगरno++;
		पूर्ण

		DEBUGP(5, dev, "Yi=%.2x\n", ch & 0xf0);
		ix += ((ch & 0x10) >> 4)	/* no of पूर्णांक.face अक्षरs */
		    +((ch & 0x20) >> 5)
		    + ((ch & 0x40) >> 6)
		    + ((ch & 0x80) >> 7);
		/* ATRLENCK(dev,ix); */
		अगर (ch & 0x80) अणु	/* TDi */
			ch = dev->atr[ix];
			अगर ((ch & 0x0f)) अणु
				any_t1 = 1;
				DEBUGP(5, dev, "card is capable of T=1\n");
			पूर्ण अन्यथा अणु
				any_t0 = 1;
				DEBUGP(5, dev, "card is capable of T=0\n");
			पूर्ण
		पूर्ण अन्यथा
			करोne = 1;
	पूर्ण जबतक (!करोne);

	DEBUGP(5, dev, "ix=%d noHist=%d any_t1=%d\n",
	      ix, dev->atr[1] & 15, any_t1);
	अगर (ix + 1 + (dev->atr[1] & 0x0f) + any_t1 != dev->atr_len) अणु
		DEBUGP(5, dev, "length error\n");
		वापस 0;
	पूर्ण
	अगर (any_t0)
		set_bit(IS_ANY_T0, &dev->flags);

	अगर (any_t1) अणु		/* compute csum */
		dev->atr_csum = 0;
#अगर_घोषित ATR_CSUM
		क्रम (i = 1; i < dev->atr_len; i++)
			dev->atr_csum ^= dev->atr[i];
		अगर (dev->atr_csum) अणु
			set_bit(IS_BAD_CSUM, &dev->flags);
			DEBUGP(5, dev, "bad checksum\n");
			जाओ वापस_0;
		पूर्ण
#पूर्ण_अगर
		अगर (any_t0 == 0)
			dev->proto = 1;	/* XXX PROTO */
		set_bit(IS_ANY_T1, &dev->flags);
	पूर्ण

	वापस 1;
पूर्ण

काष्ठा card_fixup अणु
	अक्षर atr[12];
	u_पूर्णांक8_t atr_len;
	u_पूर्णांक8_t stopbits;
पूर्ण;

अटल काष्ठा card_fixup card_fixups[] = अणु
	अणु	/* ACOS */
		.atr = अणु 0x3b, 0xb3, 0x11, 0x00, 0x00, 0x41, 0x01 पूर्ण,
		.atr_len = 7,
		.stopbits = 0x03,
	पूर्ण,
	अणु	/* Motorola */
		.atr = अणु0x3b, 0x76, 0x13, 0x00, 0x00, 0x80, 0x62, 0x07,
			0x41, 0x81, 0x81 पूर्ण,
		.atr_len = 11,
		.stopbits = 0x04,
	पूर्ण,
पूर्ण;

अटल व्योम set_cardparameter(काष्ठा cm4000_dev *dev)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक iobase = dev->p_dev->resource[0]->start;
	u_पूर्णांक8_t stopbits = 0x02; /* ISO शेष */

	DEBUGP(3, dev, "-> set_cardparameter\n");

	dev->flags1 = dev->flags1 | (((dev->baudv - 1) & 0x0100) >> 8);
	xoutb(dev->flags1, REG_FLAGS1(iobase));
	DEBUGP(5, dev, "flags1 = 0x%02x\n", dev->flags1);

	/* set baudrate */
	xoutb((अचिन्हित अक्षर)((dev->baudv - 1) & 0xFF), REG_BAUDRATE(iobase));

	DEBUGP(5, dev, "baudv = %i -> write 0x%02x\n", dev->baudv,
	      ((dev->baudv - 1) & 0xFF));

	/* set stopbits */
	क्रम (i = 0; i < ARRAY_SIZE(card_fixups); i++) अणु
		अगर (!स_भेद(dev->atr, card_fixups[i].atr,
			    card_fixups[i].atr_len))
			stopbits = card_fixups[i].stopbits;
	पूर्ण
	xoutb(stopbits, REG_STOPBITS(iobase));

	DEBUGP(3, dev, "<- set_cardparameter\n");
पूर्ण

अटल पूर्णांक set_protocol(काष्ठा cm4000_dev *dev, काष्ठा ptsreq *ptsreq)
अणु

	अचिन्हित दीर्घ पंचांगp, i;
	अचिन्हित लघु num_bytes_पढ़ो;
	अचिन्हित अक्षर pts_reply[4];
	sमाप_प्रकार rc;
	अचिन्हित पूर्णांक iobase = dev->p_dev->resource[0]->start;

	rc = 0;

	DEBUGP(3, dev, "-> set_protocol\n");
	DEBUGP(5, dev, "ptsreq->Protocol = 0x%.8x, ptsreq->Flags=0x%.8x, "
		 "ptsreq->pts1=0x%.2x, ptsreq->pts2=0x%.2x, "
		 "ptsreq->pts3=0x%.2x\n", (अचिन्हित पूर्णांक)ptsreq->protocol,
		 (अचिन्हित पूर्णांक)ptsreq->flags, ptsreq->pts1, ptsreq->pts2,
		 ptsreq->pts3);

	/* Fill PTS काष्ठाure */
	dev->pts[0] = 0xff;
	dev->pts[1] = 0x00;
	पंचांगp = ptsreq->protocol;
	जबतक ((पंचांगp = (पंचांगp >> 1)) > 0)
		dev->pts[1]++;
	dev->proto = dev->pts[1];	/* Set new protocol */
	dev->pts[1] = (0x01 << 4) | (dev->pts[1]);

	/* Correct Fi/Di according to CM4000 Fi/Di table */
	DEBUGP(5, dev, "Ta(1) from ATR is 0x%.2x\n", dev->ta1);
	/* set Fi/Di according to ATR TA(1) */
	dev->pts[2] = fi_di_table[dev->ta1 & 0x0F][(dev->ta1 >> 4) & 0x0F];

	/* Calculate PCK अक्षरacter */
	dev->pts[3] = dev->pts[0] ^ dev->pts[1] ^ dev->pts[2];

	DEBUGP(5, dev, "pts0=%.2x, pts1=%.2x, pts2=%.2x, pts3=%.2x\n",
	       dev->pts[0], dev->pts[1], dev->pts[2], dev->pts[3]);

	/* check card convention */
	अगर (test_bit(IS_INVREV, &dev->flags))
		str_invert_revert(dev->pts, 4);

	/* reset SM */
	xoutb(0x80, REG_FLAGS0(iobase));

	/* Enable access to the message buffer */
	DEBUGP(5, dev, "Enable access to the messages buffer\n");
	dev->flags1 = 0x20	/* T_Active */
	    | (test_bit(IS_INVREV, &dev->flags) ? 0x02 : 0x00) /* inv parity */
	    | ((dev->baudv >> 8) & 0x01);	/* MSB-baud */
	xoutb(dev->flags1, REG_FLAGS1(iobase));

	DEBUGP(5, dev, "Enable message buffer -> flags1 = 0x%.2x\n",
	       dev->flags1);

	/* ग_लिखो challenge to the buffer */
	DEBUGP(5, dev, "Write challenge to buffer: ");
	क्रम (i = 0; i < 4; i++) अणु
		xoutb(i, REG_BUF_ADDR(iobase));
		xoutb(dev->pts[i], REG_BUF_DATA(iobase));	/* buf data */
#अगर_घोषित CM4000_DEBUG
		pr_debug("0x%.2x ", dev->pts[i]);
	पूर्ण
	pr_debug("\n");
#अन्यथा
	पूर्ण
#पूर्ण_अगर

	/* set number of bytes to ग_लिखो */
	DEBUGP(5, dev, "Set number of bytes to write\n");
	xoutb(0x04, REG_NUM_SEND(iobase));

	/* Trigger CARDMAN CONTROLLER */
	xoutb(0x50, REG_FLAGS0(iobase));

	/* Monitor progress */
	/* रुको क्रम xmit करोne */
	DEBUGP(5, dev, "Waiting for NumRecBytes getting valid\n");

	क्रम (i = 0; i < 100; i++) अणु
		अगर (inb(REG_FLAGS0(iobase)) & 0x08) अणु
			DEBUGP(5, dev, "NumRecBytes is valid\n");
			अवरोध;
		पूर्ण
		usleep_range(10000, 11000);
	पूर्ण
	अगर (i == 100) अणु
		DEBUGP(5, dev, "Timeout waiting for NumRecBytes getting "
		       "valid\n");
		rc = -EIO;
		जाओ निकास_setprotocol;
	पूर्ण

	DEBUGP(5, dev, "Reading NumRecBytes\n");
	क्रम (i = 0; i < 100; i++) अणु
		io_पढ़ो_num_rec_bytes(iobase, &num_bytes_पढ़ो);
		अगर (num_bytes_पढ़ो >= 4) अणु
			DEBUGP(2, dev, "NumRecBytes = %i\n", num_bytes_पढ़ो);
			अवरोध;
		पूर्ण
		usleep_range(10000, 11000);
	पूर्ण

	/* check whether it is a लघु PTS reply? */
	अगर (num_bytes_पढ़ो == 3)
		i = 0;

	अगर (i == 100) अणु
		DEBUGP(5, dev, "Timeout reading num_bytes_read\n");
		rc = -EIO;
		जाओ निकास_setprotocol;
	पूर्ण

	DEBUGP(5, dev, "Reset the CARDMAN CONTROLLER\n");
	xoutb(0x80, REG_FLAGS0(iobase));

	/* Read PPS reply */
	DEBUGP(5, dev, "Read PPS reply\n");
	क्रम (i = 0; i < num_bytes_पढ़ो; i++) अणु
		xoutb(i, REG_BUF_ADDR(iobase));
		pts_reply[i] = inb(REG_BUF_DATA(iobase));
	पूर्ण

#अगर_घोषित CM4000_DEBUG
	DEBUGP(2, dev, "PTSreply: ");
	क्रम (i = 0; i < num_bytes_पढ़ो; i++) अणु
		pr_debug("0x%.2x ", pts_reply[i]);
	पूर्ण
	pr_debug("\n");
#पूर्ण_अगर	/* CM4000_DEBUG */

	DEBUGP(5, dev, "Clear Tactive in Flags1\n");
	xoutb(0x20, REG_FLAGS1(iobase));

	/* Compare ptsreq and ptsreply */
	अगर ((dev->pts[0] == pts_reply[0]) &&
	    (dev->pts[1] == pts_reply[1]) &&
	    (dev->pts[2] == pts_reply[2]) && (dev->pts[3] == pts_reply[3])) अणु
		/* setcardparameter according to PPS */
		dev->baudv = calc_baudv(dev->pts[2]);
		set_cardparameter(dev);
	पूर्ण अन्यथा अगर ((dev->pts[0] == pts_reply[0]) &&
		   ((dev->pts[1] & 0xef) == pts_reply[1]) &&
		   ((pts_reply[0] ^ pts_reply[1]) == pts_reply[2])) अणु
		/* लघु PTS reply, set card parameter to शेष values */
		dev->baudv = calc_baudv(0x11);
		set_cardparameter(dev);
	पूर्ण अन्यथा
		rc = -EIO;

निकास_setprotocol:
	DEBUGP(3, dev, "<- set_protocol\n");
	वापस rc;
पूर्ण

अटल पूर्णांक io_detect_cm4000(अचिन्हित पूर्णांक iobase, काष्ठा cm4000_dev *dev)
अणु

	/* note: statemachine is assumed to be reset */
	अगर (inb(REG_FLAGS0(iobase)) & 8) अणु
		clear_bit(IS_ATR_VALID, &dev->flags);
		set_bit(IS_CMM_ABSENT, &dev->flags);
		वापस 0;	/* detect CMM = 1 -> failure */
	पूर्ण
	/* xoutb(0x40, REG_FLAGS1(iobase)); detectCMM */
	xoutb(dev->flags1 | 0x40, REG_FLAGS1(iobase));
	अगर ((inb(REG_FLAGS0(iobase)) & 8) == 0) अणु
		clear_bit(IS_ATR_VALID, &dev->flags);
		set_bit(IS_CMM_ABSENT, &dev->flags);
		वापस 0;	/* detect CMM=0 -> failure */
	पूर्ण
	/* clear detectCMM again by restoring original flags1 */
	xoutb(dev->flags1, REG_FLAGS1(iobase));
	वापस 1;
पूर्ण

अटल व्योम terminate_monitor(काष्ठा cm4000_dev *dev)
अणु

	/* tell the monitor to stop and रुको until
	 * it terminates.
	 */
	DEBUGP(3, dev, "-> terminate_monitor\n");
	रुको_event_पूर्णांकerruptible(dev->devq,
				 test_and_set_bit(LOCK_MONITOR,
						  (व्योम *)&dev->flags));

	/* now, LOCK_MONITOR has been set.
	 * allow a last cycle in the monitor.
	 * the monitor will indicate that it has
	 * finished by clearing this bit.
	 */
	DEBUGP(5, dev, "Now allow last cycle of monitor!\n");
	जबतक (test_bit(LOCK_MONITOR, (व्योम *)&dev->flags))
		msleep(25);

	DEBUGP(5, dev, "Delete timer\n");
	del_समयr_sync(&dev->समयr);
#अगर_घोषित CM4000_DEBUG
	dev->monitor_running = 0;
#पूर्ण_अगर

	DEBUGP(3, dev, "<- terminate_monitor\n");
पूर्ण

/*
 * monitor the card every 50msec. as a side-effect, retrieve the
 * atr once a card is inserted. another side-effect of retrieving the
 * atr is that the card will be घातered on, so there is no need to
 * घातer on the card explicitly from the application: the driver
 * is alपढ़ोy करोing that क्रम you.
 */

अटल व्योम monitor_card(काष्ठा समयr_list *t)
अणु
	काष्ठा cm4000_dev *dev = from_समयr(dev, t, समयr);
	अचिन्हित पूर्णांक iobase = dev->p_dev->resource[0]->start;
	अचिन्हित लघु s;
	काष्ठा ptsreq ptsreq;
	पूर्णांक i, atrc;

	DEBUGP(7, dev, "->  monitor_card\n");

	/* अगर someone has set the lock क्रम us: we're करोne! */
	अगर (test_and_set_bit(LOCK_MONITOR, &dev->flags)) अणु
		DEBUGP(4, dev, "About to stop monitor\n");
		/* no */
		dev->rlen =
		    dev->rpos =
		    dev->atr_csum = dev->atr_len_retry = dev->cwarn = 0;
		dev->mstate = M_FETCH_ATR;
		clear_bit(LOCK_MONITOR, &dev->flags);
		/* बंद et al. are sleeping on devq, so wake it */
		wake_up_पूर्णांकerruptible(&dev->devq);
		DEBUGP(2, dev, "<- monitor_card (we are done now)\n");
		वापस;
	पूर्ण

	/* try to lock io: अगर it is alपढ़ोy locked, just add another समयr */
	अगर (test_and_set_bit(LOCK_IO, (व्योम *)&dev->flags)) अणु
		DEBUGP(4, dev, "Couldn't get IO lock\n");
		जाओ वापस_with_समयr;
	पूर्ण

	/* is a card/a पढ़ोer inserted at all ? */
	dev->flags0 = xinb(REG_FLAGS0(iobase));
	DEBUGP(7, dev, "dev->flags0 = 0x%2x\n", dev->flags0);
	DEBUGP(7, dev, "smartcard present: %s\n",
	       dev->flags0 & 1 ? "yes" : "no");
	DEBUGP(7, dev, "cardman present: %s\n",
	       dev->flags0 == 0xff ? "no" : "yes");

	अगर ((dev->flags0 & 1) == 0	/* no smartcard inserted */
	    || dev->flags0 == 0xff) अणु	/* no cardman inserted */
		/* no */
		dev->rlen =
		    dev->rpos =
		    dev->atr_csum = dev->atr_len_retry = dev->cwarn = 0;
		dev->mstate = M_FETCH_ATR;

		dev->flags &= 0x000000ff; /* only keep IO and MONITOR locks */

		अगर (dev->flags0 == 0xff) अणु
			DEBUGP(4, dev, "set IS_CMM_ABSENT bit\n");
			set_bit(IS_CMM_ABSENT, &dev->flags);
		पूर्ण अन्यथा अगर (test_bit(IS_CMM_ABSENT, &dev->flags)) अणु
			DEBUGP(4, dev, "clear IS_CMM_ABSENT bit "
			       "(card is removed)\n");
			clear_bit(IS_CMM_ABSENT, &dev->flags);
		पूर्ण

		जाओ release_io;
	पूर्ण अन्यथा अगर ((dev->flags0 & 1) && test_bit(IS_CMM_ABSENT, &dev->flags)) अणु
		/* cardman and card present but cardman was असलent beक्रमe
		 * (after suspend with inserted card) */
		DEBUGP(4, dev, "clear IS_CMM_ABSENT bit (card is inserted)\n");
		clear_bit(IS_CMM_ABSENT, &dev->flags);
	पूर्ण

	अगर (test_bit(IS_ATR_VALID, &dev->flags) == 1) अणु
		DEBUGP(7, dev, "believe ATR is already valid (do nothing)\n");
		जाओ release_io;
	पूर्ण

	चयन (dev->mstate) अणु
	हाल M_CARDOFF: अणु
		अचिन्हित अक्षर flags0;

		DEBUGP(4, dev, "M_CARDOFF\n");
		flags0 = inb(REG_FLAGS0(iobase));
		अगर (flags0 & 0x02) अणु
			/* रुको until Flags0 indicate घातer is off */
			dev->mdelay = T_10MSEC;
		पूर्ण अन्यथा अणु
			/* Flags0 indicate घातer off and no card inserted now;
			 * Reset CARDMAN CONTROLLER */
			xoutb(0x80, REG_FLAGS0(iobase));

			/* prepare क्रम fetching ATR again: after card off ATR
			 * is पढ़ो again स्वतःmatically */
			dev->rlen =
			    dev->rpos =
			    dev->atr_csum =
			    dev->atr_len_retry = dev->cwarn = 0;
			dev->mstate = M_FETCH_ATR;

			/* minimal gap between CARDOFF and पढ़ो ATR is 50msec */
			dev->mdelay = T_50MSEC;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल M_FETCH_ATR:
		DEBUGP(4, dev, "M_FETCH_ATR\n");
		xoutb(0x80, REG_FLAGS0(iobase));
		DEBUGP(4, dev, "Reset BAUDV to 9600\n");
		dev->baudv = 0x173;	/* 9600 */
		xoutb(0x02, REG_STOPBITS(iobase));	/* stopbits=2 */
		xoutb(0x73, REG_BAUDRATE(iobase));	/* baud value */
		xoutb(0x21, REG_FLAGS1(iobase));	/* T_Active=1, baud
							   value */
		/* warm start vs. घातer on: */
		xoutb(dev->flags0 & 2 ? 0x46 : 0x44, REG_FLAGS0(iobase));
		dev->mdelay = T_40MSEC;
		dev->mstate = M_TIMEOUT_WAIT;
		अवरोध;
	हाल M_TIMEOUT_WAIT:
		DEBUGP(4, dev, "M_TIMEOUT_WAIT\n");
		/* numRecBytes */
		io_पढ़ो_num_rec_bytes(iobase, &dev->atr_len);
		dev->mdelay = T_10MSEC;
		dev->mstate = M_READ_ATR_LEN;
		अवरोध;
	हाल M_READ_ATR_LEN:
		DEBUGP(4, dev, "M_READ_ATR_LEN\n");
		/* infinite loop possible, since there is no समयout */

#घोषणा	MAX_ATR_LEN_RETRY	100

		अगर (dev->atr_len == io_पढ़ो_num_rec_bytes(iobase, &s)) अणु
			अगर (dev->atr_len_retry++ >= MAX_ATR_LEN_RETRY) अणु					/* + XX msec */
				dev->mdelay = T_10MSEC;
				dev->mstate = M_READ_ATR;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev->atr_len = s;
			dev->atr_len_retry = 0;	/* set new समयout */
		पूर्ण

		DEBUGP(4, dev, "Current ATR_LEN = %i\n", dev->atr_len);
		अवरोध;
	हाल M_READ_ATR:
		DEBUGP(4, dev, "M_READ_ATR\n");
		xoutb(0x80, REG_FLAGS0(iobase));	/* reset SM */
		क्रम (i = 0; i < dev->atr_len; i++) अणु
			xoutb(i, REG_BUF_ADDR(iobase));
			dev->atr[i] = inb(REG_BUF_DATA(iobase));
		पूर्ण
		/* Deactivate T_Active flags */
		DEBUGP(4, dev, "Deactivate T_Active flags\n");
		dev->flags1 = 0x01;
		xoutb(dev->flags1, REG_FLAGS1(iobase));

		/* atr is present (which करोesn't mean it's valid) */
		set_bit(IS_ATR_PRESENT, &dev->flags);
		अगर (dev->atr[0] == 0x03)
			str_invert_revert(dev->atr, dev->atr_len);
		atrc = parse_atr(dev);
		अगर (atrc == 0) अणु	/* atr invalid */
			dev->mdelay = 0;
			dev->mstate = M_BAD_CARD;
		पूर्ण अन्यथा अणु
			dev->mdelay = T_50MSEC;
			dev->mstate = M_ATR_PRESENT;
			set_bit(IS_ATR_VALID, &dev->flags);
		पूर्ण

		अगर (test_bit(IS_ATR_VALID, &dev->flags) == 1) अणु
			DEBUGP(4, dev, "monitor_card: ATR valid\n");
 			/* अगर ta1 == 0x11, no PPS necessary (शेष values) */
			/* करो not करो PPS with multi protocol cards */
			अगर ((test_bit(IS_AUTOPPS_ACT, &dev->flags) == 0) &&
			    (dev->ta1 != 0x11) &&
			    !(test_bit(IS_ANY_T0, &dev->flags) &&
			    test_bit(IS_ANY_T1, &dev->flags))) अणु
				DEBUGP(4, dev, "Perform AUTOPPS\n");
				set_bit(IS_AUTOPPS_ACT, &dev->flags);
				ptsreq.protocol = (0x01 << dev->proto);
				ptsreq.flags = 0x01;
				ptsreq.pts1 = 0x00;
				ptsreq.pts2 = 0x00;
				ptsreq.pts3 = 0x00;
				अगर (set_protocol(dev, &ptsreq) == 0) अणु
					DEBUGP(4, dev, "AUTOPPS ret SUCC\n");
					clear_bit(IS_AUTOPPS_ACT, &dev->flags);
					wake_up_पूर्णांकerruptible(&dev->atrq);
				पूर्ण अन्यथा अणु
					DEBUGP(4, dev, "AUTOPPS failed: "
					       "repower using defaults\n");
					/* prepare क्रम reघातering  */
					clear_bit(IS_ATR_PRESENT, &dev->flags);
					clear_bit(IS_ATR_VALID, &dev->flags);
					dev->rlen =
					    dev->rpos =
					    dev->atr_csum =
					    dev->atr_len_retry = dev->cwarn = 0;
					dev->mstate = M_FETCH_ATR;

					dev->mdelay = T_50MSEC;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* क्रम cards which use slightly dअगरferent
				 * params (extra guard समय) */
				set_cardparameter(dev);
				अगर (test_bit(IS_AUTOPPS_ACT, &dev->flags) == 1)
					DEBUGP(4, dev, "AUTOPPS already active "
					       "2nd try:use default values\n");
				अगर (dev->ta1 == 0x11)
					DEBUGP(4, dev, "No AUTOPPS necessary "
					       "TA(1)==0x11\n");
				अगर (test_bit(IS_ANY_T0, &dev->flags)
				    && test_bit(IS_ANY_T1, &dev->flags))
					DEBUGP(4, dev, "Do NOT perform AUTOPPS "
					       "with multiprotocol cards\n");
				clear_bit(IS_AUTOPPS_ACT, &dev->flags);
				wake_up_पूर्णांकerruptible(&dev->atrq);
			पूर्ण
		पूर्ण अन्यथा अणु
			DEBUGP(4, dev, "ATR invalid\n");
			wake_up_पूर्णांकerruptible(&dev->atrq);
		पूर्ण
		अवरोध;
	हाल M_BAD_CARD:
		DEBUGP(4, dev, "M_BAD_CARD\n");
		/* slow करोwn warning, but prompt immediately after insertion */
		अगर (dev->cwarn == 0 || dev->cwarn == 10) अणु
			set_bit(IS_BAD_CARD, &dev->flags);
			dev_warn(&dev->p_dev->dev, MODULE_NAME ": ");
			अगर (test_bit(IS_BAD_CSUM, &dev->flags)) अणु
				DEBUGP(4, dev, "ATR checksum (0x%.2x, should "
				       "be zero) failed\n", dev->atr_csum);
			पूर्ण
#अगर_घोषित CM4000_DEBUG
			अन्यथा अगर (test_bit(IS_BAD_LENGTH, &dev->flags)) अणु
				DEBUGP(4, dev, "ATR length error\n");
			पूर्ण अन्यथा अणु
				DEBUGP(4, dev, "card damaged or wrong way "
					"inserted\n");
			पूर्ण
#पूर्ण_अगर
			dev->cwarn = 0;
			wake_up_पूर्णांकerruptible(&dev->atrq);	/* wake खोलो */
		पूर्ण
		dev->cwarn++;
		dev->mdelay = T_100MSEC;
		dev->mstate = M_FETCH_ATR;
		अवरोध;
	शेष:
		DEBUGP(7, dev, "Unknown action\n");
		अवरोध;		/* nothing */
	पूर्ण

release_io:
	DEBUGP(7, dev, "release_io\n");
	clear_bit(LOCK_IO, &dev->flags);
	wake_up_पूर्णांकerruptible(&dev->ioq);	/* whoever needs IO */

वापस_with_समयr:
	DEBUGP(7, dev, "<- monitor_card (returns with timer)\n");
	mod_समयr(&dev->समयr, jअगरfies + dev->mdelay);
	clear_bit(LOCK_MONITOR, &dev->flags);
पूर्ण

/* Interface to userland (file_operations) */

अटल sमाप_प्रकार cmm_पढ़ो(काष्ठा file *filp, __user अक्षर *buf, माप_प्रकार count,
			loff_t *ppos)
अणु
	काष्ठा cm4000_dev *dev = filp->निजी_data;
	अचिन्हित पूर्णांक iobase = dev->p_dev->resource[0]->start;
	sमाप_प्रकार rc;
	पूर्णांक i, j, k;

	DEBUGP(2, dev, "-> cmm_read(%s,%d)\n", current->comm, current->pid);

	अगर (count == 0)		/* according to manpage */
		वापस 0;

	अगर (!pcmcia_dev_present(dev->p_dev) || /* device हटाओd */
	    test_bit(IS_CMM_ABSENT, &dev->flags))
		वापस -ENODEV;

	अगर (test_bit(IS_BAD_CSUM, &dev->flags))
		वापस -EIO;

	/* also see the note about this in cmm_ग_लिखो */
	अगर (रुको_event_पूर्णांकerruptible
	    (dev->atrq,
	     ((filp->f_flags & O_NONBLOCK)
	      || (test_bit(IS_ATR_PRESENT, (व्योम *)&dev->flags) != 0)))) अणु
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		वापस -ERESTARTSYS;
	पूर्ण

	अगर (test_bit(IS_ATR_VALID, &dev->flags) == 0)
		वापस -EIO;

	/* this one implements blocking IO */
	अगर (रुको_event_पूर्णांकerruptible
	    (dev->पढ़ोq,
	     ((filp->f_flags & O_NONBLOCK) || (dev->rpos < dev->rlen)))) अणु
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		वापस -ERESTARTSYS;
	पूर्ण

	/* lock io */
	अगर (रुको_event_पूर्णांकerruptible
	    (dev->ioq,
	     ((filp->f_flags & O_NONBLOCK)
	      || (test_and_set_bit(LOCK_IO, (व्योम *)&dev->flags) == 0)))) अणु
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		वापस -ERESTARTSYS;
	पूर्ण

	rc = 0;
	dev->flags0 = inb(REG_FLAGS0(iobase));
	अगर ((dev->flags0 & 1) == 0	/* no smartcard inserted */
	    || dev->flags0 == 0xff) अणु	/* no cardman inserted */
		clear_bit(IS_ATR_VALID, &dev->flags);
		अगर (dev->flags0 & 1) अणु
			set_bit(IS_CMM_ABSENT, &dev->flags);
			rc = -ENODEV;
		पूर्ण अन्यथा अणु
			rc = -EIO;
		पूर्ण
		जाओ release_io;
	पूर्ण

	DEBUGP(4, dev, "begin read answer\n");
	j = min(count, (माप_प्रकार)(dev->rlen - dev->rpos));
	k = dev->rpos;
	अगर (k + j > 255)
		j = 256 - k;
	DEBUGP(4, dev, "read1 j=%d\n", j);
	क्रम (i = 0; i < j; i++) अणु
		xoutb(k++, REG_BUF_ADDR(iobase));
		dev->rbuf[i] = xinb(REG_BUF_DATA(iobase));
	पूर्ण
	j = min(count, (माप_प्रकार)(dev->rlen - dev->rpos));
	अगर (k + j > 255) अणु
		DEBUGP(4, dev, "read2 j=%d\n", j);
		dev->flags1 |= 0x10;	/* MSB buf addr set */
		xoutb(dev->flags1, REG_FLAGS1(iobase));
		क्रम (; i < j; i++) अणु
			xoutb(k++, REG_BUF_ADDR(iobase));
			dev->rbuf[i] = xinb(REG_BUF_DATA(iobase));
		पूर्ण
	पूर्ण

	अगर (dev->proto == 0 && count > dev->rlen - dev->rpos && i) अणु
		DEBUGP(4, dev, "T=0 and count > buffer\n");
		dev->rbuf[i] = dev->rbuf[i - 1];
		dev->rbuf[i - 1] = dev->procbyte;
		j++;
	पूर्ण
	count = j;

	dev->rpos = dev->rlen + 1;

	/* Clear T1Active */
	DEBUGP(4, dev, "Clear T1Active\n");
	dev->flags1 &= 0xdf;
	xoutb(dev->flags1, REG_FLAGS1(iobase));

	xoutb(0, REG_FLAGS1(iobase));	/* clear detectCMM */
	/* last check beक्रमe निकास */
	अगर (!io_detect_cm4000(iobase, dev)) अणु
		rc = -ENODEV;
		जाओ release_io;
	पूर्ण

	अगर (test_bit(IS_INVREV, &dev->flags) && count > 0)
		str_invert_revert(dev->rbuf, count);

	अगर (copy_to_user(buf, dev->rbuf, count))
		rc = -EFAULT;

release_io:
	clear_bit(LOCK_IO, &dev->flags);
	wake_up_पूर्णांकerruptible(&dev->ioq);

	DEBUGP(2, dev, "<- cmm_read returns: rc = %zi\n",
	       (rc < 0 ? rc : count));
	वापस rc < 0 ? rc : count;
पूर्ण

अटल sमाप_प्रकार cmm_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cm4000_dev *dev = filp->निजी_data;
	अचिन्हित पूर्णांक iobase = dev->p_dev->resource[0]->start;
	अचिन्हित लघु s;
	अचिन्हित अक्षर पंचांगp;
	अचिन्हित अक्षर infolen;
	अचिन्हित अक्षर sendT0;
	अचिन्हित लघु nsend;
	अचिन्हित लघु nr;
	sमाप_प्रकार rc;
	पूर्णांक i;

	DEBUGP(2, dev, "-> cmm_write(%s,%d)\n", current->comm, current->pid);

	अगर (count == 0)		/* according to manpage */
		वापस 0;

	अगर (dev->proto == 0 && count < 4) अणु
		/* T0 must have at least 4 bytes */
		DEBUGP(4, dev, "T0 short write\n");
		वापस -EIO;
	पूर्ण

	nr = count & 0x1ff;	/* max bytes to ग_लिखो */

	sendT0 = dev->proto ? 0 : nr > 5 ? 0x08 : 0;

	अगर (!pcmcia_dev_present(dev->p_dev) || /* device हटाओd */
	    test_bit(IS_CMM_ABSENT, &dev->flags))
		वापस -ENODEV;

	अगर (test_bit(IS_BAD_CSUM, &dev->flags)) अणु
		DEBUGP(4, dev, "bad csum\n");
		वापस -EIO;
	पूर्ण

	/*
	 * रुको क्रम atr to become valid.
	 * note: it is important to lock this code. अगर we करोnt, the monitor
	 * could be run between test_bit and the call to sleep on the
	 * atr-queue.  अगर *then* the monitor detects atr valid, it will wake up
	 * any process on the atr-queue, *but* since we have been पूर्णांकerrupted,
	 * we करो not yet sleep on this queue. this would result in a missed
	 * wake_up and the calling process would sleep क्रमever (until
	 * पूर्णांकerrupted).  also, करो *not* restore_flags beक्रमe sleep_on, because
	 * this could result in the same situation!
	 */
	अगर (रुको_event_पूर्णांकerruptible
	    (dev->atrq,
	     ((filp->f_flags & O_NONBLOCK)
	      || (test_bit(IS_ATR_PRESENT, (व्योम *)&dev->flags) != 0)))) अणु
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		वापस -ERESTARTSYS;
	पूर्ण

	अगर (test_bit(IS_ATR_VALID, &dev->flags) == 0) अणु	/* invalid atr */
		DEBUGP(4, dev, "invalid ATR\n");
		वापस -EIO;
	पूर्ण

	/* lock io */
	अगर (रुको_event_पूर्णांकerruptible
	    (dev->ioq,
	     ((filp->f_flags & O_NONBLOCK)
	      || (test_and_set_bit(LOCK_IO, (व्योम *)&dev->flags) == 0)))) अणु
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		वापस -ERESTARTSYS;
	पूर्ण

	अगर (copy_from_user(dev->sbuf, buf, ((count > 512) ? 512 : count)))
		वापस -EFAULT;

	rc = 0;
	dev->flags0 = inb(REG_FLAGS0(iobase));
	अगर ((dev->flags0 & 1) == 0	/* no smartcard inserted */
	    || dev->flags0 == 0xff) अणु	/* no cardman inserted */
		clear_bit(IS_ATR_VALID, &dev->flags);
		अगर (dev->flags0 & 1) अणु
			set_bit(IS_CMM_ABSENT, &dev->flags);
			rc = -ENODEV;
		पूर्ण अन्यथा अणु
			DEBUGP(4, dev, "IO error\n");
			rc = -EIO;
		पूर्ण
		जाओ release_io;
	पूर्ण

	xoutb(0x80, REG_FLAGS0(iobase));	/* reset SM  */

	अगर (!io_detect_cm4000(iobase, dev)) अणु
		rc = -ENODEV;
		जाओ release_io;
	पूर्ण

	/* reflect T=0 send/पढ़ो mode in flags1 */
	dev->flags1 |= (sendT0);

	set_cardparameter(dev);

	/* dummy पढ़ो, reset flag procedure received */
	पंचांगp = inb(REG_FLAGS1(iobase));

	dev->flags1 = 0x20	/* T_Active */
	    | (sendT0)
	    | (test_bit(IS_INVREV, &dev->flags) ? 2 : 0)/* inverse parity  */
	    | (((dev->baudv - 1) & 0x0100) >> 8);	/* MSB-Baud */
	DEBUGP(1, dev, "set dev->flags1 = 0x%.2x\n", dev->flags1);
	xoutb(dev->flags1, REG_FLAGS1(iobase));

	/* xmit data */
	DEBUGP(4, dev, "Xmit data\n");
	क्रम (i = 0; i < nr; i++) अणु
		अगर (i >= 256) अणु
			dev->flags1 = 0x20	/* T_Active */
			    | (sendT0)	/* SendT0 */
				/* inverse parity: */
			    | (test_bit(IS_INVREV, &dev->flags) ? 2 : 0)
			    | (((dev->baudv - 1) & 0x0100) >> 8) /* MSB-Baud */
			    | 0x10;	/* set address high */
			DEBUGP(4, dev, "dev->flags = 0x%.2x - set address "
			       "high\n", dev->flags1);
			xoutb(dev->flags1, REG_FLAGS1(iobase));
		पूर्ण
		अगर (test_bit(IS_INVREV, &dev->flags)) अणु
			DEBUGP(4, dev, "Apply inverse convention for 0x%.2x "
				"-> 0x%.2x\n", (अचिन्हित अक्षर)dev->sbuf[i],
			      invert_revert(dev->sbuf[i]));
			xoutb(i, REG_BUF_ADDR(iobase));
			xoutb(invert_revert(dev->sbuf[i]),
			      REG_BUF_DATA(iobase));
		पूर्ण अन्यथा अणु
			xoutb(i, REG_BUF_ADDR(iobase));
			xoutb(dev->sbuf[i], REG_BUF_DATA(iobase));
		पूर्ण
	पूर्ण
	DEBUGP(4, dev, "Xmit done\n");

	अगर (dev->proto == 0) अणु
		/* T=0 proto: 0 byte reply  */
		अगर (nr == 4) अणु
			DEBUGP(4, dev, "T=0 assumes 0 byte reply\n");
			xoutb(i, REG_BUF_ADDR(iobase));
			अगर (test_bit(IS_INVREV, &dev->flags))
				xoutb(0xff, REG_BUF_DATA(iobase));
			अन्यथा
				xoutb(0x00, REG_BUF_DATA(iobase));
		पूर्ण

		/* numSendBytes */
		अगर (sendT0)
			nsend = nr;
		अन्यथा अणु
			अगर (nr == 4)
				nsend = 5;
			अन्यथा अणु
				nsend = 5 + (अचिन्हित अक्षर)dev->sbuf[4];
				अगर (dev->sbuf[4] == 0)
					nsend += 0x100;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		nsend = nr;

	/* T0: output procedure byte */
	अगर (test_bit(IS_INVREV, &dev->flags)) अणु
		DEBUGP(4, dev, "T=0 set Procedure byte (inverse-reverse) "
		       "0x%.2x\n", invert_revert(dev->sbuf[1]));
		xoutb(invert_revert(dev->sbuf[1]), REG_NUM_BYTES(iobase));
	पूर्ण अन्यथा अणु
		DEBUGP(4, dev, "T=0 set Procedure byte 0x%.2x\n", dev->sbuf[1]);
		xoutb(dev->sbuf[1], REG_NUM_BYTES(iobase));
	पूर्ण

	DEBUGP(1, dev, "set NumSendBytes = 0x%.2x\n",
	       (अचिन्हित अक्षर)(nsend & 0xff));
	xoutb((अचिन्हित अक्षर)(nsend & 0xff), REG_NUM_SEND(iobase));

	DEBUGP(1, dev, "Trigger CARDMAN CONTROLLER (0x%.2x)\n",
	       0x40	/* SM_Active */
	      | (dev->flags0 & 2 ? 0 : 4)	/* घातer on अगर needed */
	      |(dev->proto ? 0x10 : 0x08)	/* T=1/T=0 */
	      |(nsend & 0x100) >> 8 /* MSB numSendBytes */ );
	xoutb(0x40		/* SM_Active */
	      | (dev->flags0 & 2 ? 0 : 4)	/* घातer on अगर needed */
	      |(dev->proto ? 0x10 : 0x08)	/* T=1/T=0 */
	      |(nsend & 0x100) >> 8,	/* MSB numSendBytes */
	      REG_FLAGS0(iobase));

	/* रुको क्रम xmit करोne */
	अगर (dev->proto == 1) अणु
		DEBUGP(4, dev, "Wait for xmit done\n");
		क्रम (i = 0; i < 1000; i++) अणु
			अगर (inb(REG_FLAGS0(iobase)) & 0x08)
				अवरोध;
			msleep_पूर्णांकerruptible(10);
		पूर्ण
		अगर (i == 1000) अणु
			DEBUGP(4, dev, "timeout waiting for xmit done\n");
			rc = -EIO;
			जाओ release_io;
		पूर्ण
	पूर्ण

	/* T=1: रुको क्रम infoLen */

	infolen = 0;
	अगर (dev->proto) अणु
		/* रुको until infoLen is valid */
		क्रम (i = 0; i < 6000; i++) अणु	/* max रुकोing समय of 1 min */
			io_पढ़ो_num_rec_bytes(iobase, &s);
			अगर (s >= 3) अणु
				infolen = inb(REG_FLAGS1(iobase));
				DEBUGP(4, dev, "infolen=%d\n", infolen);
				अवरोध;
			पूर्ण
			msleep_पूर्णांकerruptible(10);
		पूर्ण
		अगर (i == 6000) अणु
			DEBUGP(4, dev, "timeout waiting for infoLen\n");
			rc = -EIO;
			जाओ release_io;
		पूर्ण
	पूर्ण अन्यथा
		clear_bit(IS_PROCBYTE_PRESENT, &dev->flags);

	/* numRecBytes | bit9 of numRecytes */
	io_पढ़ो_num_rec_bytes(iobase, &dev->rlen);
	क्रम (i = 0; i < 600; i++) अणु	/* max रुकोing समय of 2 sec */
		अगर (dev->proto) अणु
			अगर (dev->rlen >= infolen + 4)
				अवरोध;
		पूर्ण
		msleep_पूर्णांकerruptible(10);
		/* numRecBytes | bit9 of numRecytes */
		io_पढ़ो_num_rec_bytes(iobase, &s);
		अगर (s > dev->rlen) अणु
			DEBUGP(1, dev, "NumRecBytes inc (reset timeout)\n");
			i = 0;	/* reset समयout */
			dev->rlen = s;
		पूर्ण
		/* T=0: we are करोne when numRecBytes करोesn't
		 *      increment any more and NoProcedureByte
		 *      is set and numRecBytes == bytes sent + 6
		 *      (header bytes + data + 1 क्रम sw2)
		 *      except when the card replies an error
		 *      which means, no data will be sent back.
		 */
		अन्यथा अगर (dev->proto == 0) अणु
			अगर ((inb(REG_BUF_ADDR(iobase)) & 0x80)) अणु
				/* no procedure byte received since last पढ़ो */
				DEBUGP(1, dev, "NoProcedure byte set\n");
				/* i=0; */
			पूर्ण अन्यथा अणु
				/* procedure byte received since last पढ़ो */
				DEBUGP(1, dev, "NoProcedure byte unset "
					"(reset timeout)\n");
				dev->procbyte = inb(REG_FLAGS1(iobase));
				DEBUGP(1, dev, "Read procedure byte 0x%.2x\n",
				      dev->procbyte);
				i = 0;	/* reसमय_रखोout */
			पूर्ण
			अगर (inb(REG_FLAGS0(iobase)) & 0x08) अणु
				DEBUGP(1, dev, "T0Done flag (read reply)\n");
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (dev->proto)
			infolen = inb(REG_FLAGS1(iobase));
	पूर्ण
	अगर (i == 600) अणु
		DEBUGP(1, dev, "timeout waiting for numRecBytes\n");
		rc = -EIO;
		जाओ release_io;
	पूर्ण अन्यथा अणु
		अगर (dev->proto == 0) अणु
			DEBUGP(1, dev, "Wait for T0Done bit to be  set\n");
			क्रम (i = 0; i < 1000; i++) अणु
				अगर (inb(REG_FLAGS0(iobase)) & 0x08)
					अवरोध;
				msleep_पूर्णांकerruptible(10);
			पूर्ण
			अगर (i == 1000) अणु
				DEBUGP(1, dev, "timeout waiting for T0Done\n");
				rc = -EIO;
				जाओ release_io;
			पूर्ण

			dev->procbyte = inb(REG_FLAGS1(iobase));
			DEBUGP(4, dev, "Read procedure byte 0x%.2x\n",
			      dev->procbyte);

			io_पढ़ो_num_rec_bytes(iobase, &dev->rlen);
			DEBUGP(4, dev, "Read NumRecBytes = %i\n", dev->rlen);

		पूर्ण
	पूर्ण
	/* T=1: पढ़ो offset=zero, T=0: पढ़ो offset=after challenge */
	dev->rpos = dev->proto ? 0 : nr == 4 ? 5 : nr > dev->rlen ? 5 : nr;
	DEBUGP(4, dev, "dev->rlen = %i,  dev->rpos = %i, nr = %i\n",
	      dev->rlen, dev->rpos, nr);

release_io:
	DEBUGP(4, dev, "Reset SM\n");
	xoutb(0x80, REG_FLAGS0(iobase));	/* reset SM */

	अगर (rc < 0) अणु
		DEBUGP(4, dev, "Write failed but clear T_Active\n");
		dev->flags1 &= 0xdf;
		xoutb(dev->flags1, REG_FLAGS1(iobase));
	पूर्ण

	clear_bit(LOCK_IO, &dev->flags);
	wake_up_पूर्णांकerruptible(&dev->ioq);
	wake_up_पूर्णांकerruptible(&dev->पढ़ोq);	/* tell पढ़ो we have data */

	/* ITSEC E2: clear ग_लिखो buffer */
	स_रखो((अक्षर *)dev->sbuf, 0, 512);

	/* वापस error or actually written bytes */
	DEBUGP(2, dev, "<- cmm_write\n");
	वापस rc < 0 ? rc : nr;
पूर्ण

अटल व्योम start_monitor(काष्ठा cm4000_dev *dev)
अणु
	DEBUGP(3, dev, "-> start_monitor\n");
	अगर (!dev->monitor_running) अणु
		DEBUGP(5, dev, "create, init and add timer\n");
		समयr_setup(&dev->समयr, monitor_card, 0);
		dev->monitor_running = 1;
		mod_समयr(&dev->समयr, jअगरfies);
	पूर्ण अन्यथा
		DEBUGP(5, dev, "monitor already running\n");
	DEBUGP(3, dev, "<- start_monitor\n");
पूर्ण

अटल व्योम stop_monitor(काष्ठा cm4000_dev *dev)
अणु
	DEBUGP(3, dev, "-> stop_monitor\n");
	अगर (dev->monitor_running) अणु
		DEBUGP(5, dev, "stopping monitor\n");
		terminate_monitor(dev);
		/* reset monitor SM */
		clear_bit(IS_ATR_VALID, &dev->flags);
		clear_bit(IS_ATR_PRESENT, &dev->flags);
	पूर्ण अन्यथा
		DEBUGP(5, dev, "monitor already stopped\n");
	DEBUGP(3, dev, "<- stop_monitor\n");
पूर्ण

अटल दीर्घ cmm_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा cm4000_dev *dev = filp->निजी_data;
	अचिन्हित पूर्णांक iobase = dev->p_dev->resource[0]->start;
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा pcmcia_device *link;
	पूर्णांक rc;
	व्योम __user *argp = (व्योम __user *)arg;
#अगर_घोषित CM4000_DEBUG
	अक्षर *ioctl_names[CM_IOC_MAXNR + 1] = अणु
		[_IOC_NR(CM_IOCGSTATUS)] "CM_IOCGSTATUS",
		[_IOC_NR(CM_IOCGATR)] "CM_IOCGATR",
		[_IOC_NR(CM_IOCARDOFF)] "CM_IOCARDOFF",
		[_IOC_NR(CM_IOCSPTS)] "CM_IOCSPTS",
		[_IOC_NR(CM_IOSDBGLVL)] "CM4000_DBGLVL",
	पूर्ण;
	DEBUGP(3, dev, "cmm_ioctl(device=%d.%d) %s\n", imajor(inode),
	       iminor(inode), ioctl_names[_IOC_NR(cmd)]);
#पूर्ण_अगर

	mutex_lock(&cmm_mutex);
	rc = -ENODEV;
	link = dev_table[iminor(inode)];
	अगर (!pcmcia_dev_present(link)) अणु
		DEBUGP(4, dev, "DEV_OK false\n");
		जाओ out;
	पूर्ण

	अगर (test_bit(IS_CMM_ABSENT, &dev->flags)) अणु
		DEBUGP(4, dev, "CMM_ABSENT flag set\n");
		जाओ out;
	पूर्ण
	rc = -EINVAL;

	अगर (_IOC_TYPE(cmd) != CM_IOC_MAGIC) अणु
		DEBUGP(4, dev, "ioctype mismatch\n");
		जाओ out;
	पूर्ण
	अगर (_IOC_NR(cmd) > CM_IOC_MAXNR) अणु
		DEBUGP(4, dev, "iocnr mismatch\n");
		जाओ out;
	पूर्ण
	rc = 0;

	चयन (cmd) अणु
	हाल CM_IOCGSTATUS:
		DEBUGP(4, dev, " ... in CM_IOCGSTATUS\n");
		अणु
			पूर्णांक status;

			/* clear other bits, but leave inserted & घातered as
			 * they are */
			status = dev->flags0 & 3;
			अगर (test_bit(IS_ATR_PRESENT, &dev->flags))
				status |= CM_ATR_PRESENT;
			अगर (test_bit(IS_ATR_VALID, &dev->flags))
				status |= CM_ATR_VALID;
			अगर (test_bit(IS_CMM_ABSENT, &dev->flags))
				status |= CM_NO_READER;
			अगर (test_bit(IS_BAD_CARD, &dev->flags))
				status |= CM_BAD_CARD;
			अगर (copy_to_user(argp, &status, माप(पूर्णांक)))
				rc = -EFAULT;
		पूर्ण
		अवरोध;
	हाल CM_IOCGATR:
		DEBUGP(4, dev, "... in CM_IOCGATR\n");
		अणु
			काष्ठा atreq __user *atreq = argp;
			पूर्णांक पंचांगp;
			/* allow nonblocking io and being पूर्णांकerrupted */
			अगर (रुको_event_पूर्णांकerruptible
			    (dev->atrq,
			     ((filp->f_flags & O_NONBLOCK)
			      || (test_bit(IS_ATR_PRESENT, (व्योम *)&dev->flags)
				  != 0)))) अणु
				अगर (filp->f_flags & O_NONBLOCK)
					rc = -EAGAIN;
				अन्यथा
					rc = -ERESTARTSYS;
				अवरोध;
			पूर्ण

			rc = -EFAULT;
			अगर (test_bit(IS_ATR_VALID, &dev->flags) == 0) अणु
				पंचांगp = -1;
				अगर (copy_to_user(&(atreq->atr_len), &पंचांगp,
						 माप(पूर्णांक)))
					अवरोध;
			पूर्ण अन्यथा अणु
				अगर (copy_to_user(atreq->atr, dev->atr,
						 dev->atr_len))
					अवरोध;

				पंचांगp = dev->atr_len;
				अगर (copy_to_user(&(atreq->atr_len), &पंचांगp, माप(पूर्णांक)))
					अवरोध;
			पूर्ण
			rc = 0;
			अवरोध;
		पूर्ण
	हाल CM_IOCARDOFF:

#अगर_घोषित CM4000_DEBUG
		DEBUGP(4, dev, "... in CM_IOCARDOFF\n");
		अगर (dev->flags0 & 0x01) अणु
			DEBUGP(4, dev, "    Card inserted\n");
		पूर्ण अन्यथा अणु
			DEBUGP(2, dev, "    No card inserted\n");
		पूर्ण
		अगर (dev->flags0 & 0x02) अणु
			DEBUGP(4, dev, "    Card powered\n");
		पूर्ण अन्यथा अणु
			DEBUGP(2, dev, "    Card not powered\n");
		पूर्ण
#पूर्ण_अगर

		/* is a card inserted and घातered? */
		अगर ((dev->flags0 & 0x01) && (dev->flags0 & 0x02)) अणु

			/* get IO lock */
			अगर (रुको_event_पूर्णांकerruptible
			    (dev->ioq,
			     ((filp->f_flags & O_NONBLOCK)
			      || (test_and_set_bit(LOCK_IO, (व्योम *)&dev->flags)
				  == 0)))) अणु
				अगर (filp->f_flags & O_NONBLOCK)
					rc = -EAGAIN;
				अन्यथा
					rc = -ERESTARTSYS;
				अवरोध;
			पूर्ण
			/* Set Flags0 = 0x42 */
			DEBUGP(4, dev, "Set Flags0=0x42 \n");
			xoutb(0x42, REG_FLAGS0(iobase));
			clear_bit(IS_ATR_PRESENT, &dev->flags);
			clear_bit(IS_ATR_VALID, &dev->flags);
			dev->mstate = M_CARDOFF;
			clear_bit(LOCK_IO, &dev->flags);
			अगर (रुको_event_पूर्णांकerruptible
			    (dev->atrq,
			     ((filp->f_flags & O_NONBLOCK)
			      || (test_bit(IS_ATR_VALID, (व्योम *)&dev->flags) !=
				  0)))) अणु
				अगर (filp->f_flags & O_NONBLOCK)
					rc = -EAGAIN;
				अन्यथा
					rc = -ERESTARTSYS;
				अवरोध;
			पूर्ण
		पूर्ण
		/* release lock */
		clear_bit(LOCK_IO, &dev->flags);
		wake_up_पूर्णांकerruptible(&dev->ioq);

		rc = 0;
		अवरोध;
	हाल CM_IOCSPTS:
		अणु
			काष्ठा ptsreq krnptsreq;

			अगर (copy_from_user(&krnptsreq, argp,
					   माप(काष्ठा ptsreq))) अणु
				rc = -EFAULT;
				अवरोध;
			पूर्ण

			rc = 0;
			DEBUGP(4, dev, "... in CM_IOCSPTS\n");
			/* रुको क्रम ATR to get valid */
			अगर (रुको_event_पूर्णांकerruptible
			    (dev->atrq,
			     ((filp->f_flags & O_NONBLOCK)
			      || (test_bit(IS_ATR_PRESENT, (व्योम *)&dev->flags)
				  != 0)))) अणु
				अगर (filp->f_flags & O_NONBLOCK)
					rc = -EAGAIN;
				अन्यथा
					rc = -ERESTARTSYS;
				अवरोध;
			पूर्ण
			/* get IO lock */
			अगर (रुको_event_पूर्णांकerruptible
			    (dev->ioq,
			     ((filp->f_flags & O_NONBLOCK)
			      || (test_and_set_bit(LOCK_IO, (व्योम *)&dev->flags)
				  == 0)))) अणु
				अगर (filp->f_flags & O_NONBLOCK)
					rc = -EAGAIN;
				अन्यथा
					rc = -ERESTARTSYS;
				अवरोध;
			पूर्ण

			अगर ((rc = set_protocol(dev, &krnptsreq)) != 0) अणु
				/* स्वतः घातer_on again */
				dev->mstate = M_FETCH_ATR;
				clear_bit(IS_ATR_VALID, &dev->flags);
			पूर्ण
			/* release lock */
			clear_bit(LOCK_IO, &dev->flags);
			wake_up_पूर्णांकerruptible(&dev->ioq);

		पूर्ण
		अवरोध;
#अगर_घोषित CM4000_DEBUG
	हाल CM_IOSDBGLVL:
		rc = -ENOTTY;
		अवरोध;
#पूर्ण_अगर
	शेष:
		DEBUGP(4, dev, "... in default (unknown IOCTL code)\n");
		rc = -ENOTTY;
	पूर्ण
out:
	mutex_unlock(&cmm_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक cmm_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cm4000_dev *dev;
	काष्ठा pcmcia_device *link;
	पूर्णांक minor = iminor(inode);
	पूर्णांक ret;

	अगर (minor >= CM4000_MAX_DEV)
		वापस -ENODEV;

	mutex_lock(&cmm_mutex);
	link = dev_table[minor];
	अगर (link == शून्य || !pcmcia_dev_present(link)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (link->खोलो) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	dev = link->priv;
	filp->निजी_data = dev;

	DEBUGP(2, dev, "-> cmm_open(device=%d.%d process=%s,%d)\n",
	      imajor(inode), minor, current->comm, current->pid);

	/* init device variables, they may be "polluted" after बंद
	 * or, the device may never have been बंदd (i.e. खोलो failed)
	 */

	ZERO_DEV(dev);

	/* खोलोing will always block since the
	 * monitor will be started by खोलो, which
	 * means we have to रुको क्रम ATR becoming
	 * valid = block until valid (or card
	 * inserted)
	 */
	अगर (filp->f_flags & O_NONBLOCK) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	dev->mdelay = T_50MSEC;

	/* start monitoring the cardstatus */
	start_monitor(dev);

	link->खोलो = 1;		/* only one खोलो per device */

	DEBUGP(2, dev, "<- cmm_open\n");
	ret = stream_खोलो(inode, filp);
out:
	mutex_unlock(&cmm_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cmm_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा cm4000_dev *dev;
	काष्ठा pcmcia_device *link;
	पूर्णांक minor = iminor(inode);

	अगर (minor >= CM4000_MAX_DEV)
		वापस -ENODEV;

	link = dev_table[minor];
	अगर (link == शून्य)
		वापस -ENODEV;

	dev = link->priv;

	DEBUGP(2, dev, "-> cmm_close(maj/min=%d.%d)\n",
	       imajor(inode), minor);

	stop_monitor(dev);

	ZERO_DEV(dev);

	link->खोलो = 0;		/* only one खोलो per device */
	wake_up(&dev->devq);	/* socket हटाओd? */

	DEBUGP(2, dev, "cmm_close\n");
	वापस 0;
पूर्ण

अटल व्योम cmm_cm4000_release(काष्ठा pcmcia_device * link)
अणु
	काष्ठा cm4000_dev *dev = link->priv;

	/* करोnt terminate the monitor, rather rely on
	 * बंद करोing that क्रम us.
	 */
	DEBUGP(3, dev, "-> cmm_cm4000_release\n");
	जबतक (link->खोलो) अणु
		prपूर्णांकk(KERN_INFO MODULE_NAME ": delaying release until "
		       "process has terminated\n");
		/* note: करोn't पूर्णांकerrupt us:
		 * बंद the applications which own
		 * the devices _first_ !
		 */
		रुको_event(dev->devq, (link->खोलो == 0));
	पूर्ण
	/* dev->devq=शून्य;	this cannot be zeroed earlier */
	DEBUGP(3, dev, "<- cmm_cm4000_release\n");
	वापस;
पूर्ण

/*==== Interface to PCMCIA Layer =======================================*/

अटल पूर्णांक cm4000_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	वापस pcmcia_request_io(p_dev);
पूर्ण

अटल पूर्णांक cm4000_config(काष्ठा pcmcia_device * link, पूर्णांक devno)
अणु
	link->config_flags |= CONF_AUTO_SET_IO;

	/* पढ़ो the config-tuples */
	अगर (pcmcia_loop_config(link, cm4000_config_check, शून्य))
		जाओ cs_release;

	अगर (pcmcia_enable_device(link))
		जाओ cs_release;

	वापस 0;

cs_release:
	cm4000_release(link);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक cm4000_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा cm4000_dev *dev;

	dev = link->priv;
	stop_monitor(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cm4000_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा cm4000_dev *dev;

	dev = link->priv;
	अगर (link->खोलो)
		start_monitor(dev);

	वापस 0;
पूर्ण

अटल व्योम cm4000_release(काष्ठा pcmcia_device *link)
अणु
	cmm_cm4000_release(link);	/* delay release until device बंदd */
	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक cm4000_probe(काष्ठा pcmcia_device *link)
अणु
	काष्ठा cm4000_dev *dev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < CM4000_MAX_DEV; i++)
		अगर (dev_table[i] == शून्य)
			अवरोध;

	अगर (i == CM4000_MAX_DEV) अणु
		prपूर्णांकk(KERN_NOTICE MODULE_NAME ": all devices in use\n");
		वापस -ENODEV;
	पूर्ण

	/* create a new cm4000_cs device */
	dev = kzalloc(माप(काष्ठा cm4000_dev), GFP_KERNEL);
	अगर (dev == शून्य)
		वापस -ENOMEM;

	dev->p_dev = link;
	link->priv = dev;
	dev_table[i] = link;

	init_रुकोqueue_head(&dev->devq);
	init_रुकोqueue_head(&dev->ioq);
	init_रुकोqueue_head(&dev->atrq);
	init_रुकोqueue_head(&dev->पढ़ोq);

	ret = cm4000_config(link, i);
	अगर (ret) अणु
		dev_table[i] = शून्य;
		kमुक्त(dev);
		वापस ret;
	पूर्ण

	device_create(cmm_class, शून्य, MKDEV(major, i), शून्य, "cmm%d", i);

	वापस 0;
पूर्ण

अटल व्योम cm4000_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा cm4000_dev *dev = link->priv;
	पूर्णांक devno;

	/* find device */
	क्रम (devno = 0; devno < CM4000_MAX_DEV; devno++)
		अगर (dev_table[devno] == link)
			अवरोध;
	अगर (devno == CM4000_MAX_DEV)
		वापस;

	stop_monitor(dev);

	cm4000_release(link);

	dev_table[devno] = शून्य;
	kमुक्त(dev);

	device_destroy(cmm_class, MKDEV(major, devno));

	वापस;
पूर्ण

अटल स्थिर काष्ठा file_operations cm4000_fops = अणु
	.owner	= THIS_MODULE,
	.पढ़ो	= cmm_पढ़ो,
	.ग_लिखो	= cmm_ग_लिखो,
	.unlocked_ioctl	= cmm_ioctl,
	.खोलो	= cmm_खोलो,
	.release= cmm_बंद,
	.llseek = no_llseek,
पूर्ण;

अटल स्थिर काष्ठा pcmcia_device_id cm4000_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x0223, 0x0002),
	PCMCIA_DEVICE_PROD_ID12("CardMan", "4000", 0x2FB368CA, 0xA2BD8C39),
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, cm4000_ids);

अटल काष्ठा pcmcia_driver cm4000_driver = अणु
	.owner	  = THIS_MODULE,
	.name	  = "cm4000_cs",
	.probe    = cm4000_probe,
	.हटाओ   = cm4000_detach,
	.suspend  = cm4000_suspend,
	.resume   = cm4000_resume,
	.id_table = cm4000_ids,
पूर्ण;

अटल पूर्णांक __init cmm_init(व्योम)
अणु
	पूर्णांक rc;

	cmm_class = class_create(THIS_MODULE, "cardman_4000");
	अगर (IS_ERR(cmm_class))
		वापस PTR_ERR(cmm_class);

	major = रेजिस्टर_chrdev(0, DEVICE_NAME, &cm4000_fops);
	अगर (major < 0) अणु
		prपूर्णांकk(KERN_WARNING MODULE_NAME
			": could not get major number\n");
		class_destroy(cmm_class);
		वापस major;
	पूर्ण

	rc = pcmcia_रेजिस्टर_driver(&cm4000_driver);
	अगर (rc < 0) अणु
		unरेजिस्टर_chrdev(major, DEVICE_NAME);
		class_destroy(cmm_class);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास cmm_निकास(व्योम)
अणु
	pcmcia_unरेजिस्टर_driver(&cm4000_driver);
	unरेजिस्टर_chrdev(major, DEVICE_NAME);
	class_destroy(cmm_class);
पूर्ण;

module_init(cmm_init);
module_निकास(cmm_निकास);
MODULE_LICENSE("Dual BSD/GPL");
