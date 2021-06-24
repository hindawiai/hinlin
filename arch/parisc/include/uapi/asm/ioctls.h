<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ARCH_PARISC_IOCTLS_H__
#घोषणा __ARCH_PARISC_IOCTLS_H__

#समावेश <यंत्र/ioctl.h>

/* 0x54 is just a magic number to make these relatively unique ('T') */

#घोषणा TCGETS		_IOR('T', 16, काष्ठा termios) /* TCGETATTR */
#घोषणा TCSETS		_IOW('T', 17, काष्ठा termios) /* TCSETATTR */
#घोषणा TCSETSW		_IOW('T', 18, काष्ठा termios) /* TCSETATTRD */
#घोषणा TCSETSF		_IOW('T', 19, काष्ठा termios) /* TCSETATTRF */
#घोषणा TCGETA		_IOR('T', 1, काष्ठा termio)
#घोषणा TCSETA		_IOW('T', 2, काष्ठा termio)
#घोषणा TCSETAW		_IOW('T', 3, काष्ठा termio)
#घोषणा TCSETAF		_IOW('T', 4, काष्ठा termio)
#घोषणा TCSBRK		_IO('T', 5)
#घोषणा TCXONC		_IO('T', 6)
#घोषणा TCFLSH		_IO('T', 7)
#घोषणा TIOCEXCL	0x540C
#घोषणा TIOCNXCL	0x540D
#घोषणा TIOCSCTTY	0x540E
#घोषणा TIOCGPGRP	_IOR('T', 30, पूर्णांक)
#घोषणा TIOCSPGRP	_IOW('T', 29, पूर्णांक)
#घोषणा TIOCOUTQ	0x5411
#घोषणा TIOCSTI		0x5412
#घोषणा TIOCGWINSZ	0x5413
#घोषणा TIOCSWINSZ	0x5414
#घोषणा TIOCMGET	0x5415
#घोषणा TIOCMBIS	0x5416
#घोषणा TIOCMBIC	0x5417
#घोषणा TIOCMSET	0x5418
#घोषणा TIOCGSOFTCAR	0x5419
#घोषणा TIOCSSOFTCAR	0x541A
#घोषणा FIONREAD	0x541B
#घोषणा TIOCINQ		FIONREAD
#घोषणा TIOCLINUX	0x541C
#घोषणा TIOCCONS	0x541D
#घोषणा TIOCGSERIAL	0x541E
#घोषणा TIOCSSERIAL	0x541F
#घोषणा TIOCPKT		0x5420
#घोषणा FIONBIO		0x5421
#घोषणा TIOCNOTTY	0x5422
#घोषणा TIOCSETD	0x5423
#घोषणा TIOCGETD	0x5424
#घोषणा TCSBRKP		0x5425	/* Needed क्रम POSIX tcsendअवरोध() */
#घोषणा TIOCSBRK	0x5427  /* BSD compatibility */
#घोषणा TIOCCBRK	0x5428  /* BSD compatibility */
#घोषणा TIOCGSID	_IOR('T', 20, पूर्णांक) /* Return the session ID of FD */
#घोषणा TCGETS2		_IOR('T',0x2A, काष्ठा termios2)
#घोषणा TCSETS2		_IOW('T',0x2B, काष्ठा termios2)
#घोषणा TCSETSW2	_IOW('T',0x2C, काष्ठा termios2)
#घोषणा TCSETSF2	_IOW('T',0x2D, काष्ठा termios2)
#घोषणा TIOCGRS485	_IOR('T', 0x2E, काष्ठा serial_rs485)
#घोषणा TIOCSRS485	_IOWR('T', 0x2F, काष्ठा serial_rs485)
#घोषणा TIOCGPTN	_IOR('T',0x30, अचिन्हित पूर्णांक) /* Get Pty Number (of pty-mux device) */
#घोषणा TIOCSPTLCK	_IOW('T',0x31, पूर्णांक)  /* Lock/unlock Pty */
#घोषणा TIOCGDEV	_IOR('T',0x32, पूर्णांक)  /* Get primary device node of /dev/console */
#घोषणा TIOCSIG		_IOW('T',0x36, पूर्णांक)  /* Generate संकेत on Pty slave */
#घोषणा TIOCVHANGUP	0x5437
#घोषणा TIOCGPKT	_IOR('T', 0x38, पूर्णांक) /* Get packet mode state */
#घोषणा TIOCGPTLCK	_IOR('T', 0x39, पूर्णांक) /* Get Pty lock state */
#घोषणा TIOCGEXCL	_IOR('T', 0x40, पूर्णांक) /* Get exclusive mode state */
#घोषणा TIOCGPTPEER	_IO('T', 0x41) /* Safely खोलो the slave */
#घोषणा TIOCGISO7816	_IOR('T', 0x42, काष्ठा serial_iso7816)
#घोषणा TIOCSISO7816	_IOWR('T', 0x43, काष्ठा serial_iso7816)

#घोषणा FIONCLEX	0x5450  /* these numbers need to be adjusted. */
#घोषणा FIOCLEX		0x5451
#घोषणा FIOASYNC	0x5452
#घोषणा TIOCSERCONFIG	0x5453
#घोषणा TIOCSERGWILD	0x5454
#घोषणा TIOCSERSWILD	0x5455
#घोषणा TIOCGLCKTRMIOS	0x5456
#घोषणा TIOCSLCKTRMIOS	0x5457
#घोषणा TIOCSERGSTRUCT	0x5458 /* For debugging only */
#घोषणा TIOCSERGETLSR   0x5459 /* Get line status रेजिस्टर */
#घोषणा TIOCSERGETMULTI 0x545A /* Get multiport config  */
#घोषणा TIOCSERSETMULTI 0x545B /* Set multiport config */

#घोषणा TIOCMIWAIT	0x545C	/* रुको क्रम a change on serial input line(s) */
#घोषणा TIOCGICOUNT	0x545D	/* पढ़ो serial port अंतरभूत पूर्णांकerrupt counts */
#घोषणा FIOQSIZE	0x5460	/* Get exact space used by quota */

#घोषणा TIOCSTART	0x5461
#घोषणा TIOCSTOP	0x5462
#घोषणा TIOCSLTC	0x5462

/* Used क्रम packet mode */
#घोषणा TIOCPKT_DATA		 0
#घोषणा TIOCPKT_FLUSHREAD	 1
#घोषणा TIOCPKT_FLUSHWRITE	 2
#घोषणा TIOCPKT_STOP		 4
#घोषणा TIOCPKT_START		 8
#घोषणा TIOCPKT_NOSTOP		16
#घोषणा TIOCPKT_DOSTOP		32
#घोषणा TIOCPKT_IOCTL		64

#घोषणा TIOCSER_TEMT    0x01	/* Transmitter physically empty */

#पूर्ण_अगर /* _ASM_PARISC_IOCTLS_H */
