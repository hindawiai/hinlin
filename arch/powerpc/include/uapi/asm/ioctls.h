<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_POWERPC_IOCTLS_H
#घोषणा _ASM_POWERPC_IOCTLS_H

#समावेश <यंत्र/ioctl.h>

#घोषणा FIOCLEX		_IO('f', 1)
#घोषणा FIONCLEX	_IO('f', 2)
#घोषणा FIOASYNC	_IOW('f', 125, पूर्णांक)
#घोषणा FIONBIO		_IOW('f', 126, पूर्णांक)
#घोषणा FIONREAD	_IOR('f', 127, पूर्णांक)
#घोषणा TIOCINQ		FIONREAD
#घोषणा FIOQSIZE	_IOR('f', 128, loff_t)

#घोषणा TIOCGETP	_IOR('t', 8, काष्ठा sgttyb)
#घोषणा TIOCSETP	_IOW('t', 9, काष्ठा sgttyb)
#घोषणा TIOCSETN	_IOW('t', 10, काष्ठा sgttyb)	/* TIOCSETP wo flush */

#घोषणा TIOCSETC	_IOW('t', 17, काष्ठा tअक्षरs)
#घोषणा TIOCGETC	_IOR('t', 18, काष्ठा tअक्षरs)
#घोषणा TCGETS		_IOR('t', 19, काष्ठा termios)
#घोषणा TCSETS		_IOW('t', 20, काष्ठा termios)
#घोषणा TCSETSW		_IOW('t', 21, काष्ठा termios)
#घोषणा TCSETSF		_IOW('t', 22, काष्ठा termios)

#घोषणा TCGETA		_IOR('t', 23, काष्ठा termio)
#घोषणा TCSETA		_IOW('t', 24, काष्ठा termio)
#घोषणा TCSETAW		_IOW('t', 25, काष्ठा termio)
#घोषणा TCSETAF		_IOW('t', 28, काष्ठा termio)

#घोषणा TCSBRK		_IO('t', 29)
#घोषणा TCXONC		_IO('t', 30)
#घोषणा TCFLSH		_IO('t', 31)

#घोषणा TIOCSWINSZ	_IOW('t', 103, काष्ठा winsize)
#घोषणा TIOCGWINSZ	_IOR('t', 104, काष्ठा winsize)
#घोषणा	TIOCSTART	_IO('t', 110)		/* start output, like ^Q */
#घोषणा	TIOCSTOP	_IO('t', 111)		/* stop output, like ^S */
#घोषणा TIOCOUTQ        _IOR('t', 115, पूर्णांक)     /* output queue size */

#घोषणा TIOCGLTC	_IOR('t', 116, काष्ठा ltअक्षरs)
#घोषणा TIOCSLTC	_IOW('t', 117, काष्ठा ltअक्षरs)
#घोषणा TIOCSPGRP	_IOW('t', 118, पूर्णांक)
#घोषणा TIOCGPGRP	_IOR('t', 119, पूर्णांक)

#घोषणा TIOCEXCL	0x540C
#घोषणा TIOCNXCL	0x540D
#घोषणा TIOCSCTTY	0x540E

#घोषणा TIOCSTI		0x5412
#घोषणा TIOCMGET	0x5415
#घोषणा TIOCMBIS	0x5416
#घोषणा TIOCMBIC	0x5417
#घोषणा TIOCMSET	0x5418
# define TIOCM_LE	0x001
# define TIOCM_DTR	0x002
# define TIOCM_RTS	0x004
# define TIOCM_ST	0x008
# define TIOCM_SR	0x010
# define TIOCM_CTS	0x020
# define TIOCM_CAR	0x040
# define TIOCM_RNG	0x080
# define TIOCM_DSR	0x100
# define TIOCM_CD	TIOCM_CAR
# define TIOCM_RI	TIOCM_RNG
#घोषणा TIOCM_OUT1	0x2000
#घोषणा TIOCM_OUT2	0x4000
#घोषणा TIOCM_LOOP	0x8000

#घोषणा TIOCGSOFTCAR	0x5419
#घोषणा TIOCSSOFTCAR	0x541A
#घोषणा TIOCLINUX	0x541C
#घोषणा TIOCCONS	0x541D
#घोषणा TIOCGSERIAL	0x541E
#घोषणा TIOCSSERIAL	0x541F
#घोषणा TIOCPKT		0x5420
# define TIOCPKT_DATA		 0
# define TIOCPKT_FLUSHREAD	 1
# define TIOCPKT_FLUSHWRITE	 2
# define TIOCPKT_STOP		 4
# define TIOCPKT_START		 8
# define TIOCPKT_NOSTOP		16
# define TIOCPKT_DOSTOP		32
# define TIOCPKT_IOCTL		64


#घोषणा TIOCNOTTY	0x5422
#घोषणा TIOCSETD	0x5423
#घोषणा TIOCGETD	0x5424
#घोषणा TCSBRKP		0x5425	/* Needed क्रम POSIX tcsendअवरोध() */
#घोषणा TIOCSBRK	0x5427  /* BSD compatibility */
#घोषणा TIOCCBRK	0x5428  /* BSD compatibility */
#घोषणा TIOCGSID	0x5429  /* Return the session ID of FD */
#घोषणा TIOCGRS485	0x542e
#घोषणा TIOCSRS485	0x542f
#घोषणा TIOCGPTN	_IOR('T',0x30, अचिन्हित पूर्णांक) /* Get Pty Number (of pty-mux device) */
#घोषणा TIOCSPTLCK	_IOW('T',0x31, पूर्णांक)  /* Lock/unlock Pty */
#घोषणा TIOCGDEV	_IOR('T',0x32, अचिन्हित पूर्णांक) /* Get primary device node of /dev/console */
#घोषणा TIOCSIG		_IOW('T',0x36, पूर्णांक)  /* Generate संकेत on Pty slave */
#घोषणा TIOCVHANGUP	0x5437
#घोषणा TIOCGPKT	_IOR('T', 0x38, पूर्णांक) /* Get packet mode state */
#घोषणा TIOCGPTLCK	_IOR('T', 0x39, पूर्णांक) /* Get Pty lock state */
#घोषणा TIOCGEXCL	_IOR('T', 0x40, पूर्णांक) /* Get exclusive mode state */
#घोषणा TIOCGPTPEER	_IO('T', 0x41) /* Safely खोलो the slave */
#घोषणा TIOCGISO7816	_IOR('T', 0x42, काष्ठा serial_iso7816)
#घोषणा TIOCSISO7816	_IOWR('T', 0x43, काष्ठा serial_iso7816)

#घोषणा TIOCSERCONFIG	0x5453
#घोषणा TIOCSERGWILD	0x5454
#घोषणा TIOCSERSWILD	0x5455
#घोषणा TIOCGLCKTRMIOS	0x5456
#घोषणा TIOCSLCKTRMIOS	0x5457
#घोषणा TIOCSERGSTRUCT	0x5458 /* For debugging only */
#घोषणा TIOCSERGETLSR   0x5459 /* Get line status रेजिस्टर */
  /* ioctl (fd, TIOCSERGETLSR, &result) where result may be as below */
# define TIOCSER_TEMT    0x01	/* Transmitter physically empty */
#घोषणा TIOCSERGETMULTI 0x545A /* Get multiport config  */
#घोषणा TIOCSERSETMULTI 0x545B /* Set multiport config */

#घोषणा TIOCMIWAIT	0x545C	/* रुको क्रम a change on serial input line(s) */
#घोषणा TIOCGICOUNT	0x545D	/* पढ़ो serial port अंतरभूत पूर्णांकerrupt counts */

#पूर्ण_अगर	/* _ASM_POWERPC_IOCTLS_H */
