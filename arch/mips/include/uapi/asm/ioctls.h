<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1996, 2001 Ralf Baechle
 * Copyright (C) 2001 MIPS Technologies, Inc.
 */
#अगर_अघोषित __ASM_IOCTLS_H
#घोषणा __ASM_IOCTLS_H

#समावेश <यंत्र/ioctl.h>

#घोषणा TCGETA		0x5401
#घोषणा TCSETA		0x5402	/* Clashes with SNDCTL_TMR_START sound ioctl */
#घोषणा TCSETAW		0x5403
#घोषणा TCSETAF		0x5404

#घोषणा TCSBRK		0x5405
#घोषणा TCXONC		0x5406
#घोषणा TCFLSH		0x5407

#घोषणा TCGETS		0x540d
#घोषणा TCSETS		0x540e
#घोषणा TCSETSW		0x540f
#घोषणा TCSETSF		0x5410

#घोषणा TIOCEXCL	0x740d		/* set exclusive use of tty */
#घोषणा TIOCNXCL	0x740e		/* reset exclusive use of tty */
#घोषणा TIOCOUTQ	0x7472		/* output queue size */
#घोषणा TIOCSTI		0x5472		/* simulate terminal input */
#घोषणा TIOCMGET	0x741d		/* get all modem bits */
#घोषणा TIOCMBIS	0x741b		/* bis modem bits */
#घोषणा TIOCMBIC	0x741c		/* bic modem bits */
#घोषणा TIOCMSET	0x741a		/* set all modem bits */
#घोषणा TIOCPKT		0x5470		/* pty: set/clear packet mode */
#घोषणा	 TIOCPKT_DATA		0x00	/* data packet */
#घोषणा	 TIOCPKT_FLUSHREAD	0x01	/* flush packet */
#घोषणा	 TIOCPKT_FLUSHWRITE	0x02	/* flush packet */
#घोषणा	 TIOCPKT_STOP		0x04	/* stop output */
#घोषणा	 TIOCPKT_START		0x08	/* start output */
#घोषणा	 TIOCPKT_NOSTOP		0x10	/* no more ^S, ^Q */
#घोषणा	 TIOCPKT_DOSTOP		0x20	/* now करो ^S ^Q */
#घोषणा	 TIOCPKT_IOCTL		0x40	/* state change of pty driver */
#घोषणा TIOCSWINSZ	_IOW('t', 103, काष्ठा winsize)	/* set winकरोw size */
#घोषणा TIOCGWINSZ	_IOR('t', 104, काष्ठा winsize)	/* get winकरोw size */
#घोषणा TIOCNOTTY	0x5471		/* व्योम tty association */
#घोषणा TIOCSETD	0x7401
#घोषणा TIOCGETD	0x7400

#घोषणा FIOCLEX		0x6601
#घोषणा FIONCLEX	0x6602
#घोषणा FIOASYNC	0x667d
#घोषणा FIONBIO		0x667e
#घोषणा FIOQSIZE	0x667f

#घोषणा TIOCGLTC	0x7474			/* get special local अक्षरs */
#घोषणा TIOCSLTC	0x7475			/* set special local अक्षरs */
#घोषणा TIOCSPGRP	_IOW('t', 118, पूर्णांक)	/* set pgrp of tty */
#घोषणा TIOCGPGRP	_IOR('t', 119, पूर्णांक)	/* get pgrp of tty */
#घोषणा TIOCCONS	_IOW('t', 120, पूर्णांक)	/* become भव console */

#घोषणा FIONREAD	0x467f
#घोषणा TIOCINQ		FIONREAD

#घोषणा TIOCGETP	0x7408
#घोषणा TIOCSETP	0x7409
#घोषणा TIOCSETN	0x740a			/* TIOCSETP wo flush */

/* #घोषणा TIOCSETA	_IOW('t', 20, काष्ठा termios) set termios काष्ठा */
/* #घोषणा TIOCSETAW	_IOW('t', 21, काष्ठा termios) drain output, set */
/* #घोषणा TIOCSETAF	_IOW('t', 22, काष्ठा termios) drn out, fls in, set */
/* #घोषणा TIOCGETD	_IOR('t', 26, पूर्णांक)	get line discipline */
/* #घोषणा TIOCSETD	_IOW('t', 27, पूर्णांक)	set line discipline */
						/* 127-124 compat */

#घोषणा TIOCSBRK	0x5427	/* BSD compatibility */
#घोषणा TIOCCBRK	0x5428	/* BSD compatibility */
#घोषणा TIOCGSID	0x7416	/* Return the session ID of FD */
#घोषणा TCGETS2		_IOR('T', 0x2A, काष्ठा termios2)
#घोषणा TCSETS2		_IOW('T', 0x2B, काष्ठा termios2)
#घोषणा TCSETSW2	_IOW('T', 0x2C, काष्ठा termios2)
#घोषणा TCSETSF2	_IOW('T', 0x2D, काष्ठा termios2)
#घोषणा TIOCGRS485	_IOR('T', 0x2E, काष्ठा serial_rs485)
#घोषणा TIOCSRS485	_IOWR('T', 0x2F, काष्ठा serial_rs485)
#घोषणा TIOCGPTN	_IOR('T', 0x30, अचिन्हित पूर्णांक) /* Get Pty Number (of pty-mux device) */
#घोषणा TIOCSPTLCK	_IOW('T', 0x31, पूर्णांक)  /* Lock/unlock Pty */
#घोषणा TIOCGDEV	_IOR('T', 0x32, अचिन्हित पूर्णांक) /* Get primary device node of /dev/console */
#घोषणा TIOCSIG		_IOW('T', 0x36, पूर्णांक)  /* Generate संकेत on Pty slave */
#घोषणा TIOCVHANGUP	0x5437
#घोषणा TIOCGPKT	_IOR('T', 0x38, पूर्णांक) /* Get packet mode state */
#घोषणा TIOCGPTLCK	_IOR('T', 0x39, पूर्णांक) /* Get Pty lock state */
#घोषणा TIOCGEXCL	_IOR('T', 0x40, पूर्णांक) /* Get exclusive mode state */
#घोषणा TIOCGPTPEER	_IO('T', 0x41) /* Safely खोलो the slave */
#घोषणा TIOCGISO7816	_IOR('T', 0x42, काष्ठा serial_iso7816)
#घोषणा TIOCSISO7816	_IOWR('T', 0x43, काष्ठा serial_iso7816)

/* I hope the range from 0x5480 on is मुक्त ... */
#घोषणा TIOCSCTTY	0x5480		/* become controlling tty */
#घोषणा TIOCGSOFTCAR	0x5481
#घोषणा TIOCSSOFTCAR	0x5482
#घोषणा TIOCLINUX	0x5483
#घोषणा TIOCGSERIAL	0x5484
#घोषणा TIOCSSERIAL	0x5485
#घोषणा TCSBRKP		0x5486	/* Needed क्रम POSIX tcsendअवरोध() */
#घोषणा TIOCSERCONFIG	0x5488
#घोषणा TIOCSERGWILD	0x5489
#घोषणा TIOCSERSWILD	0x548a
#घोषणा TIOCGLCKTRMIOS	0x548b
#घोषणा TIOCSLCKTRMIOS	0x548c
#घोषणा TIOCSERGSTRUCT	0x548d /* For debugging only */
#घोषणा TIOCSERGETLSR	0x548e /* Get line status रेजिस्टर */
#घोषणा TIOCSERGETMULTI 0x548f /* Get multiport config	*/
#घोषणा TIOCSERSETMULTI 0x5490 /* Set multiport config */
#घोषणा TIOCMIWAIT	0x5491 /* रुको क्रम a change on serial input line(s) */
#घोषणा TIOCGICOUNT	0x5492 /* पढ़ो serial port अंतरभूत पूर्णांकerrupt counts */

#पूर्ण_अगर /* __ASM_IOCTLS_H */
