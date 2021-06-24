<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TTY_H
#घोषणा _LINUX_TTY_H

#समावेश <linux/fs.h>
#समावेश <linux/major.h>
#समावेश <linux/termios.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_ldisc.h>
#समावेश <linux/mutex.h>
#समावेश <linux/tty_flags.h>
#समावेश <linux/seq_file.h>
#समावेश <uapi/linux/tty.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/llist.h>


/*
 * (Note: the *_driver.minor_start values 1, 64, 128, 192 are
 * hardcoded at present.)
 */
#घोषणा NR_UNIX98_PTY_DEFAULT	4096      /* Default maximum क्रम Unix98 ptys */
#घोषणा NR_UNIX98_PTY_RESERVE	1024	  /* Default reserve क्रम मुख्य devpts */
#घोषणा NR_UNIX98_PTY_MAX	(1 << MINORBITS) /* Absolute limit */

/*
 * This अक्षरacter is the same as _POSIX_VDISABLE: it cannot be used as
 * a c_cc[] अक्षरacter, but indicates that a particular special अक्षरacter
 * isn't in use (eg VINTR has no अक्षरacter etc)
 */
#घोषणा __DISABLED_CHAR '\0'

काष्ठा tty_buffer अणु
	जोड़ अणु
		काष्ठा tty_buffer *next;
		काष्ठा llist_node मुक्त;
	पूर्ण;
	पूर्णांक used;
	पूर्णांक size;
	पूर्णांक commit;
	पूर्णांक पढ़ो;
	पूर्णांक flags;
	/* Data poपूर्णांकs here */
	अचिन्हित दीर्घ data[];
पूर्ण;

/* Values क्रम .flags field of tty_buffer */
#घोषणा TTYB_NORMAL	1	/* buffer has no flags buffer */

अटल अंतरभूत अचिन्हित अक्षर *अक्षर_buf_ptr(काष्ठा tty_buffer *b, पूर्णांक ofs)
अणु
	वापस ((अचिन्हित अक्षर *)b->data) + ofs;
पूर्ण

अटल अंतरभूत अक्षर *flag_buf_ptr(काष्ठा tty_buffer *b, पूर्णांक ofs)
अणु
	वापस (अक्षर *)अक्षर_buf_ptr(b, ofs) + b->size;
पूर्ण

काष्ठा tty_bufhead अणु
	काष्ठा tty_buffer *head;	/* Queue head */
	काष्ठा work_काष्ठा work;
	काष्ठा mutex	   lock;
	atomic_t	   priority;
	काष्ठा tty_buffer sentinel;
	काष्ठा llist_head मुक्त;		/* Free queue head */
	atomic_t	   mem_used;    /* In-use buffers excluding मुक्त list */
	पूर्णांक		   mem_limit;
	काष्ठा tty_buffer *tail;	/* Active buffer */
पूर्ण;
/*
 * When a अवरोध, frame error, or parity error happens, these codes are
 * stuffed पूर्णांकo the flags buffer.
 */
#घोषणा TTY_NORMAL	0
#घोषणा TTY_BREAK	1
#घोषणा TTY_FRAME	2
#घोषणा TTY_PARITY	3
#घोषणा TTY_OVERRUN	4

#घोषणा INTR_CHAR(tty) ((tty)->termios.c_cc[VINTR])
#घोषणा QUIT_CHAR(tty) ((tty)->termios.c_cc[VQUIT])
#घोषणा ERASE_CHAR(tty) ((tty)->termios.c_cc[VERASE])
#घोषणा KILL_CHAR(tty) ((tty)->termios.c_cc[VKILL])
#घोषणा खातापूर्ण_CHAR(tty) ((tty)->termios.c_cc[Vखातापूर्ण])
#घोषणा TIME_CHAR(tty) ((tty)->termios.c_cc[VTIME])
#घोषणा MIN_CHAR(tty) ((tty)->termios.c_cc[VMIN])
#घोषणा SWTC_CHAR(tty) ((tty)->termios.c_cc[VSWTC])
#घोषणा START_CHAR(tty) ((tty)->termios.c_cc[VSTART])
#घोषणा STOP_CHAR(tty) ((tty)->termios.c_cc[VSTOP])
#घोषणा SUSP_CHAR(tty) ((tty)->termios.c_cc[VSUSP])
#घोषणा EOL_CHAR(tty) ((tty)->termios.c_cc[VEOL])
#घोषणा REPRINT_CHAR(tty) ((tty)->termios.c_cc[VREPRINT])
#घोषणा DISCARD_CHAR(tty) ((tty)->termios.c_cc[VDISCARD])
#घोषणा WERASE_CHAR(tty) ((tty)->termios.c_cc[VWERASE])
#घोषणा LNEXT_CHAR(tty)	((tty)->termios.c_cc[VLNEXT])
#घोषणा EOL2_CHAR(tty) ((tty)->termios.c_cc[VEOL2])

#घोषणा _I_FLAG(tty, f)	((tty)->termios.c_अगरlag & (f))
#घोषणा _O_FLAG(tty, f)	((tty)->termios.c_oflag & (f))
#घोषणा _C_FLAG(tty, f)	((tty)->termios.c_cflag & (f))
#घोषणा _L_FLAG(tty, f)	((tty)->termios.c_lflag & (f))

#घोषणा I_IGNBRK(tty)	_I_FLAG((tty), IGNBRK)
#घोषणा I_BRKINT(tty)	_I_FLAG((tty), BRKINT)
#घोषणा I_IGNPAR(tty)	_I_FLAG((tty), IGNPAR)
#घोषणा I_PARMRK(tty)	_I_FLAG((tty), PARMRK)
#घोषणा I_INPCK(tty)	_I_FLAG((tty), INPCK)
#घोषणा I_ISTRIP(tty)	_I_FLAG((tty), ISTRIP)
#घोषणा I_INLCR(tty)	_I_FLAG((tty), INLCR)
#घोषणा I_IGNCR(tty)	_I_FLAG((tty), IGNCR)
#घोषणा I_ICRNL(tty)	_I_FLAG((tty), ICRNL)
#घोषणा I_IUCLC(tty)	_I_FLAG((tty), IUCLC)
#घोषणा I_IXON(tty)	_I_FLAG((tty), IXON)
#घोषणा I_IXANY(tty)	_I_FLAG((tty), IXANY)
#घोषणा I_IXOFF(tty)	_I_FLAG((tty), IXOFF)
#घोषणा I_IMAXBEL(tty)	_I_FLAG((tty), IMAXBEL)
#घोषणा I_IUTF8(tty)	_I_FLAG((tty), IUTF8)

#घोषणा O_OPOST(tty)	_O_FLAG((tty), OPOST)
#घोषणा O_OLCUC(tty)	_O_FLAG((tty), OLCUC)
#घोषणा O_ONLCR(tty)	_O_FLAG((tty), ONLCR)
#घोषणा O_OCRNL(tty)	_O_FLAG((tty), OCRNL)
#घोषणा O_ONOCR(tty)	_O_FLAG((tty), ONOCR)
#घोषणा O_ONLRET(tty)	_O_FLAG((tty), ONLRET)
#घोषणा O_OFILL(tty)	_O_FLAG((tty), OFILL)
#घोषणा O_OFDEL(tty)	_O_FLAG((tty), OFDEL)
#घोषणा O_NLDLY(tty)	_O_FLAG((tty), NLDLY)
#घोषणा O_CRDLY(tty)	_O_FLAG((tty), CRDLY)
#घोषणा O_TABDLY(tty)	_O_FLAG((tty), TABDLY)
#घोषणा O_BSDLY(tty)	_O_FLAG((tty), BSDLY)
#घोषणा O_VTDLY(tty)	_O_FLAG((tty), VTDLY)
#घोषणा O_FFDLY(tty)	_O_FLAG((tty), FFDLY)

#घोषणा C_BAUD(tty)	_C_FLAG((tty), CBAUD)
#घोषणा C_CSIZE(tty)	_C_FLAG((tty), CSIZE)
#घोषणा C_CSTOPB(tty)	_C_FLAG((tty), CSTOPB)
#घोषणा C_CREAD(tty)	_C_FLAG((tty), CREAD)
#घोषणा C_PARENB(tty)	_C_FLAG((tty), PARENB)
#घोषणा C_PARODD(tty)	_C_FLAG((tty), PARODD)
#घोषणा C_HUPCL(tty)	_C_FLAG((tty), HUPCL)
#घोषणा C_CLOCAL(tty)	_C_FLAG((tty), CLOCAL)
#घोषणा C_CIBAUD(tty)	_C_FLAG((tty), CIBAUD)
#घोषणा C_CRTSCTS(tty)	_C_FLAG((tty), CRTSCTS)
#घोषणा C_CMSPAR(tty)	_C_FLAG((tty), CMSPAR)

#घोषणा L_ISIG(tty)	_L_FLAG((tty), ISIG)
#घोषणा L_ICANON(tty)	_L_FLAG((tty), ICANON)
#घोषणा L_XCASE(tty)	_L_FLAG((tty), XCASE)
#घोषणा L_ECHO(tty)	_L_FLAG((tty), ECHO)
#घोषणा L_ECHOE(tty)	_L_FLAG((tty), ECHOE)
#घोषणा L_ECHOK(tty)	_L_FLAG((tty), ECHOK)
#घोषणा L_ECHONL(tty)	_L_FLAG((tty), ECHONL)
#घोषणा L_NOFLSH(tty)	_L_FLAG((tty), NOFLSH)
#घोषणा L_TOSTOP(tty)	_L_FLAG((tty), TOSTOP)
#घोषणा L_ECHOCTL(tty)	_L_FLAG((tty), ECHOCTL)
#घोषणा L_ECHOPRT(tty)	_L_FLAG((tty), ECHOPRT)
#घोषणा L_ECHOKE(tty)	_L_FLAG((tty), ECHOKE)
#घोषणा L_FLUSHO(tty)	_L_FLAG((tty), FLUSHO)
#घोषणा L_PENDIN(tty)	_L_FLAG((tty), PENDIN)
#घोषणा L_IEXTEN(tty)	_L_FLAG((tty), IEXTEN)
#घोषणा L_EXTPROC(tty)	_L_FLAG((tty), EXTPROC)

काष्ठा device;
काष्ठा संकेत_काष्ठा;

/*
 * Port level inक्रमmation. Each device keeps its own port level inक्रमmation
 * so provide a common काष्ठाure क्रम those ports wanting to use common support
 * routines.
 *
 * The tty port has a dअगरferent lअगरeसमय to the tty so must be kept apart.
 * In addition be careful as tty -> port mappings are valid क्रम the lअगरe
 * of the tty object but in many हालs port -> tty mappings are valid only
 * until a hangup so करोn't use the wrong path.
 */

काष्ठा tty_port;

काष्ठा tty_port_operations अणु
	/* Return 1 अगर the carrier is उठाओd */
	पूर्णांक (*carrier_उठाओd)(काष्ठा tty_port *port);
	/* Control the DTR line */
	व्योम (*dtr_rts)(काष्ठा tty_port *port, पूर्णांक उठाओ);
	/* Called when the last बंद completes or a hangup finishes
	   IFF the port was initialized. Do not use to मुक्त resources. Called
	   under the port mutex to serialize against activate/shutकरोwns */
	व्योम (*shutकरोwn)(काष्ठा tty_port *port);
	/* Called under the port mutex from tty_port_खोलो, serialized using
	   the port mutex */
        /* FIXME: दीर्घ term getting the tty argument *out* of this would be
           good क्रम consoles */
	पूर्णांक (*activate)(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty);
	/* Called on the final put of a port */
	व्योम (*deकाष्ठा)(काष्ठा tty_port *port);
पूर्ण;

काष्ठा tty_port_client_operations अणु
	पूर्णांक (*receive_buf)(काष्ठा tty_port *port, स्थिर अचिन्हित अक्षर *, स्थिर अचिन्हित अक्षर *, माप_प्रकार);
	व्योम (*ग_लिखो_wakeup)(काष्ठा tty_port *port);
पूर्ण;

बाह्य स्थिर काष्ठा tty_port_client_operations tty_port_शेष_client_ops;

काष्ठा tty_port अणु
	काष्ठा tty_bufhead	buf;		/* Locked पूर्णांकernally */
	काष्ठा tty_काष्ठा	*tty;		/* Back poपूर्णांकer */
	काष्ठा tty_काष्ठा	*itty;		/* पूर्णांकernal back ptr */
	स्थिर काष्ठा tty_port_operations *ops;	/* Port operations */
	स्थिर काष्ठा tty_port_client_operations *client_ops; /* Port client operations */
	spinlock_t		lock;		/* Lock protecting tty field */
	पूर्णांक			blocked_खोलो;	/* Waiting to खोलो */
	पूर्णांक			count;		/* Usage count */
	रुको_queue_head_t	खोलो_रुको;	/* Open रुकोers */
	रुको_queue_head_t	delta_msr_रुको;	/* Modem status change */
	अचिन्हित दीर्घ		flags;		/* User TTY flags ASYNC_ */
	अचिन्हित दीर्घ		अगरlags;		/* Internal flags TTY_PORT_ */
	अचिन्हित अक्षर		console:1;	/* port is a console */
	काष्ठा mutex		mutex;		/* Locking */
	काष्ठा mutex		buf_mutex;	/* Buffer alloc lock */
	अचिन्हित अक्षर		*xmit_buf;	/* Optional buffer */
	अचिन्हित पूर्णांक		बंद_delay;	/* Close port delay */
	अचिन्हित पूर्णांक		closing_रुको;	/* Delay क्रम output */
	पूर्णांक			drain_delay;	/* Set to zero अगर no pure समय
						   based drain is needed अन्यथा
						   set to size of fअगरo */
	काष्ठा kref		kref;		/* Ref counter */
	व्योम 			*client_data;
पूर्ण;

/* tty_port::अगरlags bits -- use atomic bit ops */
#घोषणा TTY_PORT_INITIALIZED	0	/* device is initialized */
#घोषणा TTY_PORT_SUSPENDED	1	/* device is suspended */
#घोषणा TTY_PORT_ACTIVE		2	/* device is खोलो */

/*
 * uart drivers: use the uart_port::status field and the UPSTAT_* defines
 * क्रम s/w-based flow control steering and carrier detection status
 */
#घोषणा TTY_PORT_CTS_FLOW	3	/* h/w flow control enabled */
#घोषणा TTY_PORT_CHECK_CD	4	/* carrier detect enabled */
#घोषणा TTY_PORT_KOPENED	5	/* device exclusively खोलोed by
					   kernel */

/*
 * Where all of the state associated with a tty is kept जबतक the tty
 * is खोलो.  Since the termios state should be kept even अगर the tty
 * has been बंदd --- क्रम things like the baud rate, etc --- it is
 * not stored here, but rather a poपूर्णांकer to the real state is stored
 * here.  Possible the winsize काष्ठाure should have the same
 * treaपंचांगent, but (1) the शेष 80x24 is usually right and (2) it's
 * most often used by a winकरोwing प्रणाली, which will set the correct
 * size each समय the winकरोw is created or resized anyway.
 * 						- TYT, 9/14/92
 */

काष्ठा tty_operations;

काष्ठा tty_काष्ठा अणु
	पूर्णांक	magic;
	काष्ठा kref kref;
	काष्ठा device *dev;	/* class device or शून्य (e.g. ptys, serdev) */
	काष्ठा tty_driver *driver;
	स्थिर काष्ठा tty_operations *ops;
	पूर्णांक index;

	/* Protects ldisc changes: Lock tty not pty */
	काष्ठा ld_semaphore ldisc_sem;
	काष्ठा tty_ldisc *ldisc;

	काष्ठा mutex atomic_ग_लिखो_lock;
	काष्ठा mutex legacy_mutex;
	काष्ठा mutex throttle_mutex;
	काष्ठा rw_semaphore termios_rwsem;
	काष्ठा mutex winsize_mutex;
	spinlock_t ctrl_lock;
	spinlock_t flow_lock;
	/* Termios values are रक्षित by the termios rwsem */
	काष्ठा ktermios termios, termios_locked;
	अक्षर name[64];
	काष्ठा pid *pgrp;		/* Protected by ctrl lock */
	/*
	 * Writes रक्षित by both ctrl lock and legacy mutex, पढ़ोers must use
	 * at least one of them.
	 */
	काष्ठा pid *session;
	अचिन्हित दीर्घ flags;
	पूर्णांक count;
	काष्ठा winsize winsize;		/* winsize_mutex */
	अचिन्हित दीर्घ stopped:1,	/* flow_lock */
		      flow_stopped:1,
		      unused:BITS_PER_LONG - 2;
	पूर्णांक hw_stopped;
	अचिन्हित दीर्घ ctrl_status:8,	/* ctrl_lock */
		      packet:1,
		      unused_ctrl:BITS_PER_LONG - 9;
	अचिन्हित पूर्णांक receive_room;	/* Bytes मुक्त क्रम queue */
	पूर्णांक flow_change;

	काष्ठा tty_काष्ठा *link;
	काष्ठा fasync_काष्ठा *fasync;
	रुको_queue_head_t ग_लिखो_रुको;
	रुको_queue_head_t पढ़ो_रुको;
	काष्ठा work_काष्ठा hangup_work;
	व्योम *disc_data;
	व्योम *driver_data;
	spinlock_t files_lock;		/* protects tty_files list */
	काष्ठा list_head tty_files;

#घोषणा N_TTY_BUF_SIZE 4096

	पूर्णांक closing;
	अचिन्हित अक्षर *ग_लिखो_buf;
	पूर्णांक ग_लिखो_cnt;
	/* If the tty has a pending करो_SAK, queue it here - akpm */
	काष्ठा work_काष्ठा SAK_work;
	काष्ठा tty_port *port;
पूर्ण __अक्रमomize_layout;

/* Each of a tty's खोलो files has निजी_data poपूर्णांकing to tty_file_निजी */
काष्ठा tty_file_निजी अणु
	काष्ठा tty_काष्ठा *tty;
	काष्ठा file *file;
	काष्ठा list_head list;
पूर्ण;

/* tty magic number */
#घोषणा TTY_MAGIC		0x5401

/*
 * These bits are used in the flags field of the tty काष्ठाure.
 *
 * So that पूर्णांकerrupts won't be able to mess up the queues,
 * copy_to_cooked must be atomic with respect to itself, as must
 * tty->ग_लिखो.  Thus, you must use the अंतरभूत functions set_bit() and
 * clear_bit() to make things atomic.
 */
#घोषणा TTY_THROTTLED 		0	/* Call unthrottle() at threshold min */
#घोषणा TTY_IO_ERROR 		1	/* Cause an I/O error (may be no ldisc too) */
#घोषणा TTY_OTHER_CLOSED 	2	/* Other side (अगर any) has बंदd */
#घोषणा TTY_EXCLUSIVE 		3	/* Exclusive खोलो mode */
#घोषणा TTY_DO_WRITE_WAKEUP 	5	/* Call ग_लिखो_wakeup after queuing new */
#घोषणा TTY_LDISC_OPEN	 	11	/* Line discipline is खोलो */
#घोषणा TTY_PTY_LOCK 		16	/* pty निजी */
#घोषणा TTY_NO_WRITE_SPLIT 	17	/* Preserve ग_लिखो boundaries to driver */
#घोषणा TTY_HUPPED 		18	/* Post driver->hangup() */
#घोषणा TTY_HUPPING		19	/* Hangup in progress */
#घोषणा TTY_LDISC_CHANGING	20	/* Change pending - non-block IO */
#घोषणा TTY_LDISC_HALTED	22	/* Line discipline is halted */

अटल अंतरभूत bool tty_io_nonblock(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	वापस file->f_flags & O_NONBLOCK ||
		test_bit(TTY_LDISC_CHANGING, &tty->flags);
पूर्ण

अटल अंतरभूत bool tty_io_error(काष्ठा tty_काष्ठा *tty)
अणु
	वापस test_bit(TTY_IO_ERROR, &tty->flags);
पूर्ण

अटल अंतरभूत bool tty_throttled(काष्ठा tty_काष्ठा *tty)
अणु
	वापस test_bit(TTY_THROTTLED, &tty->flags);
पूर्ण

#अगर_घोषित CONFIG_TTY
बाह्य व्योम tty_kref_put(काष्ठा tty_काष्ठा *tty);
बाह्य काष्ठा pid *tty_get_pgrp(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_vhangup_self(व्योम);
बाह्य व्योम disassociate_ctty(पूर्णांक priv);
बाह्य dev_t tty_devnum(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम proc_clear_tty(काष्ठा task_काष्ठा *p);
बाह्य काष्ठा tty_काष्ठा *get_current_tty(व्योम);
/* tty_io.c */
बाह्य पूर्णांक __init tty_init(व्योम);
बाह्य स्थिर अक्षर *tty_name(स्थिर काष्ठा tty_काष्ठा *tty);
बाह्य काष्ठा tty_काष्ठा *tty_kखोलो_exclusive(dev_t device);
बाह्य काष्ठा tty_काष्ठा *tty_kखोलो_shared(dev_t device);
बाह्य व्योम tty_kबंद(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक tty_dev_name_to_number(स्थिर अक्षर *name, dev_t *number);
#अन्यथा
अटल अंतरभूत व्योम tty_kref_put(काष्ठा tty_काष्ठा *tty)
अणु पूर्ण
अटल अंतरभूत काष्ठा pid *tty_get_pgrp(काष्ठा tty_काष्ठा *tty)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम tty_vhangup_self(व्योम)
अणु पूर्ण
अटल अंतरभूत व्योम disassociate_ctty(पूर्णांक priv)
अणु पूर्ण
अटल अंतरभूत dev_t tty_devnum(काष्ठा tty_काष्ठा *tty)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम proc_clear_tty(काष्ठा task_काष्ठा *p)
अणु पूर्ण
अटल अंतरभूत काष्ठा tty_काष्ठा *get_current_tty(व्योम)
अणु वापस शून्य; पूर्ण
/* tty_io.c */
अटल अंतरभूत पूर्णांक __init tty_init(व्योम)
अणु वापस 0; पूर्ण
अटल अंतरभूत स्थिर अक्षर *tty_name(स्थिर काष्ठा tty_काष्ठा *tty)
अणु वापस "(none)"; पूर्ण
अटल अंतरभूत काष्ठा tty_काष्ठा *tty_kखोलो_exclusive(dev_t device)
अणु वापस ERR_PTR(-ENODEV); पूर्ण
अटल अंतरभूत व्योम tty_kबंद(काष्ठा tty_काष्ठा *tty)
अणु पूर्ण
अटल अंतरभूत पूर्णांक tty_dev_name_to_number(स्थिर अक्षर *name, dev_t *number)
अणु वापस -ENOTSUPP; पूर्ण
#पूर्ण_अगर

बाह्य काष्ठा ktermios tty_std_termios;

बाह्य पूर्णांक vcs_init(व्योम);

बाह्य काष्ठा class *tty_class;

/**
 *	tty_kref_get		-	get a tty reference
 *	@tty: tty device
 *
 *	Return a new reference to a tty object. The caller must hold
 *	sufficient locks/counts to ensure that their existing reference cannot
 *	go away
 */

अटल अंतरभूत काष्ठा tty_काष्ठा *tty_kref_get(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (tty)
		kref_get(&tty->kref);
	वापस tty;
पूर्ण

बाह्य स्थिर अक्षर *tty_driver_name(स्थिर काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_रुको_until_sent(काष्ठा tty_काष्ठा *tty, दीर्घ समयout);
बाह्य व्योम stop_tty(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम start_tty(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक tty_रेजिस्टर_driver(काष्ठा tty_driver *driver);
बाह्य व्योम tty_unरेजिस्टर_driver(काष्ठा tty_driver *driver);
बाह्य काष्ठा device *tty_रेजिस्टर_device(काष्ठा tty_driver *driver,
					  अचिन्हित index, काष्ठा device *dev);
बाह्य काष्ठा device *tty_रेजिस्टर_device_attr(काष्ठा tty_driver *driver,
				अचिन्हित index, काष्ठा device *device,
				व्योम *drvdata,
				स्थिर काष्ठा attribute_group **attr_grp);
बाह्य व्योम tty_unरेजिस्टर_device(काष्ठा tty_driver *driver, अचिन्हित index);
बाह्य व्योम tty_ग_लिखो_message(काष्ठा tty_काष्ठा *tty, अक्षर *msg);
बाह्य पूर्णांक tty_send_xअक्षर(काष्ठा tty_काष्ठा *tty, अक्षर ch);
बाह्य पूर्णांक tty_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर c);
बाह्य पूर्णांक tty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_driver_flush_buffer(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_throttle(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_unthrottle(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक tty_throttle_safe(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक tty_unthrottle_safe(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक tty_करो_resize(काष्ठा tty_काष्ठा *tty, काष्ठा winsize *ws);
बाह्य पूर्णांक tty_get_icount(काष्ठा tty_काष्ठा *tty,
			  काष्ठा serial_icounter_काष्ठा *icount);
बाह्य पूर्णांक is_current_pgrp_orphaned(व्योम);
बाह्य व्योम tty_hangup(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_vhangup(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक tty_hung_up_p(काष्ठा file *filp);
बाह्य व्योम करो_SAK(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम __करो_SAK(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम no_tty(व्योम);
बाह्य speed_t tty_termios_baud_rate(काष्ठा ktermios *termios);
बाह्य व्योम tty_termios_encode_baud_rate(काष्ठा ktermios *termios,
						speed_t ibaud, speed_t obaud);
बाह्य व्योम tty_encode_baud_rate(काष्ठा tty_काष्ठा *tty,
						speed_t ibaud, speed_t obaud);

/**
 *	tty_get_baud_rate	-	get tty bit rates
 *	@tty: tty to query
 *
 *	Returns the baud rate as an पूर्णांकeger क्रम this terminal. The
 *	termios lock must be held by the caller and the terminal bit
 *	flags may be updated.
 *
 *	Locking: none
 */
अटल अंतरभूत speed_t tty_get_baud_rate(काष्ठा tty_काष्ठा *tty)
अणु
	वापस tty_termios_baud_rate(&tty->termios);
पूर्ण

बाह्य व्योम tty_termios_copy_hw(काष्ठा ktermios *new, काष्ठा ktermios *old);
बाह्य पूर्णांक tty_termios_hw_change(स्थिर काष्ठा ktermios *a, स्थिर काष्ठा ktermios *b);
बाह्य पूर्णांक tty_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *kt);

बाह्य काष्ठा tty_ldisc *tty_ldisc_ref(काष्ठा tty_काष्ठा *);
बाह्य व्योम tty_ldisc_deref(काष्ठा tty_ldisc *);
बाह्य काष्ठा tty_ldisc *tty_ldisc_ref_रुको(काष्ठा tty_काष्ठा *);
बाह्य स्थिर काष्ठा seq_operations tty_ldiscs_seq_ops;

बाह्य व्योम tty_wakeup(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_ldisc_flush(काष्ठा tty_काष्ठा *tty);

बाह्य पूर्णांक tty_mode_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
बाह्य पूर्णांक tty_perक्रमm_flush(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ arg);
बाह्य काष्ठा tty_काष्ठा *tty_init_dev(काष्ठा tty_driver *driver, पूर्णांक idx);
बाह्य व्योम tty_release_काष्ठा(काष्ठा tty_काष्ठा *tty, पूर्णांक idx);
बाह्य व्योम tty_init_termios(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_save_termios(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक tty_standard_install(काष्ठा tty_driver *driver,
		काष्ठा tty_काष्ठा *tty);

बाह्य काष्ठा mutex tty_mutex;

बाह्य व्योम tty_port_init(काष्ठा tty_port *port);
बाह्य व्योम tty_port_link_device(काष्ठा tty_port *port,
		काष्ठा tty_driver *driver, अचिन्हित index);
बाह्य काष्ठा device *tty_port_रेजिस्टर_device(काष्ठा tty_port *port,
		काष्ठा tty_driver *driver, अचिन्हित index,
		काष्ठा device *device);
बाह्य काष्ठा device *tty_port_रेजिस्टर_device_attr(काष्ठा tty_port *port,
		काष्ठा tty_driver *driver, अचिन्हित index,
		काष्ठा device *device, व्योम *drvdata,
		स्थिर काष्ठा attribute_group **attr_grp);
बाह्य काष्ठा device *tty_port_रेजिस्टर_device_serdev(काष्ठा tty_port *port,
		काष्ठा tty_driver *driver, अचिन्हित index,
		काष्ठा device *device);
बाह्य काष्ठा device *tty_port_रेजिस्टर_device_attr_serdev(काष्ठा tty_port *port,
		काष्ठा tty_driver *driver, अचिन्हित index,
		काष्ठा device *device, व्योम *drvdata,
		स्थिर काष्ठा attribute_group **attr_grp);
बाह्य व्योम tty_port_unरेजिस्टर_device(काष्ठा tty_port *port,
		काष्ठा tty_driver *driver, अचिन्हित index);
बाह्य पूर्णांक tty_port_alloc_xmit_buf(काष्ठा tty_port *port);
बाह्य व्योम tty_port_मुक्त_xmit_buf(काष्ठा tty_port *port);
बाह्य व्योम tty_port_destroy(काष्ठा tty_port *port);
बाह्य व्योम tty_port_put(काष्ठा tty_port *port);

अटल अंतरभूत काष्ठा tty_port *tty_port_get(काष्ठा tty_port *port)
अणु
	अगर (port && kref_get_unless_zero(&port->kref))
		वापस port;
	वापस शून्य;
पूर्ण

/* If the cts flow control is enabled, वापस true. */
अटल अंतरभूत bool tty_port_cts_enabled(स्थिर काष्ठा tty_port *port)
अणु
	वापस test_bit(TTY_PORT_CTS_FLOW, &port->अगरlags);
पूर्ण

अटल अंतरभूत व्योम tty_port_set_cts_flow(काष्ठा tty_port *port, bool val)
अणु
	assign_bit(TTY_PORT_CTS_FLOW, &port->अगरlags, val);
पूर्ण

अटल अंतरभूत bool tty_port_active(स्थिर काष्ठा tty_port *port)
अणु
	वापस test_bit(TTY_PORT_ACTIVE, &port->अगरlags);
पूर्ण

अटल अंतरभूत व्योम tty_port_set_active(काष्ठा tty_port *port, bool val)
अणु
	assign_bit(TTY_PORT_ACTIVE, &port->अगरlags, val);
पूर्ण

अटल अंतरभूत bool tty_port_check_carrier(स्थिर काष्ठा tty_port *port)
अणु
	वापस test_bit(TTY_PORT_CHECK_CD, &port->अगरlags);
पूर्ण

अटल अंतरभूत व्योम tty_port_set_check_carrier(काष्ठा tty_port *port, bool val)
अणु
	assign_bit(TTY_PORT_CHECK_CD, &port->अगरlags, val);
पूर्ण

अटल अंतरभूत bool tty_port_suspended(स्थिर काष्ठा tty_port *port)
अणु
	वापस test_bit(TTY_PORT_SUSPENDED, &port->अगरlags);
पूर्ण

अटल अंतरभूत व्योम tty_port_set_suspended(काष्ठा tty_port *port, bool val)
अणु
	assign_bit(TTY_PORT_SUSPENDED, &port->अगरlags, val);
पूर्ण

अटल अंतरभूत bool tty_port_initialized(स्थिर काष्ठा tty_port *port)
अणु
	वापस test_bit(TTY_PORT_INITIALIZED, &port->अगरlags);
पूर्ण

अटल अंतरभूत व्योम tty_port_set_initialized(काष्ठा tty_port *port, bool val)
अणु
	assign_bit(TTY_PORT_INITIALIZED, &port->अगरlags, val);
पूर्ण

अटल अंतरभूत bool tty_port_kखोलोed(स्थिर काष्ठा tty_port *port)
अणु
	वापस test_bit(TTY_PORT_KOPENED, &port->अगरlags);
पूर्ण

अटल अंतरभूत व्योम tty_port_set_kखोलोed(काष्ठा tty_port *port, bool val)
अणु
	assign_bit(TTY_PORT_KOPENED, &port->अगरlags, val);
पूर्ण

बाह्य काष्ठा tty_काष्ठा *tty_port_tty_get(काष्ठा tty_port *port);
बाह्य व्योम tty_port_tty_set(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक tty_port_carrier_उठाओd(काष्ठा tty_port *port);
बाह्य व्योम tty_port_उठाओ_dtr_rts(काष्ठा tty_port *port);
बाह्य व्योम tty_port_lower_dtr_rts(काष्ठा tty_port *port);
बाह्य व्योम tty_port_hangup(काष्ठा tty_port *port);
बाह्य व्योम tty_port_tty_hangup(काष्ठा tty_port *port, bool check_clocal);
बाह्य व्योम tty_port_tty_wakeup(काष्ठा tty_port *port);
बाह्य पूर्णांक tty_port_block_til_पढ़ोy(काष्ठा tty_port *port,
				काष्ठा tty_काष्ठा *tty, काष्ठा file *filp);
बाह्य पूर्णांक tty_port_बंद_start(काष्ठा tty_port *port,
				काष्ठा tty_काष्ठा *tty, काष्ठा file *filp);
बाह्य व्योम tty_port_बंद_end(काष्ठा tty_port *port, काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_port_बंद(काष्ठा tty_port *port,
				काष्ठा tty_काष्ठा *tty, काष्ठा file *filp);
बाह्य पूर्णांक tty_port_install(काष्ठा tty_port *port, काष्ठा tty_driver *driver,
				काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक tty_port_खोलो(काष्ठा tty_port *port,
				काष्ठा tty_काष्ठा *tty, काष्ठा file *filp);
अटल अंतरभूत पूर्णांक tty_port_users(काष्ठा tty_port *port)
अणु
	वापस port->count + port->blocked_खोलो;
पूर्ण

बाह्य पूर्णांक tty_रेजिस्टर_ldisc(पूर्णांक disc, काष्ठा tty_ldisc_ops *new_ldisc);
बाह्य पूर्णांक tty_unरेजिस्टर_ldisc(पूर्णांक disc);
बाह्य पूर्णांक tty_set_ldisc(काष्ठा tty_काष्ठा *tty, पूर्णांक disc);
बाह्य पूर्णांक tty_ldisc_receive_buf(काष्ठा tty_ldisc *ld, स्थिर अचिन्हित अक्षर *p,
				 अक्षर *f, पूर्णांक count);

/* n_tty.c */
बाह्य व्योम n_tty_inherit_ops(काष्ठा tty_ldisc_ops *ops);
#अगर_घोषित CONFIG_TTY
बाह्य व्योम __init n_tty_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम n_tty_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

/* tty_audit.c */
#अगर_घोषित CONFIG_AUDIT
बाह्य व्योम tty_audit_निकास(व्योम);
बाह्य व्योम tty_audit_विभाजन(काष्ठा संकेत_काष्ठा *sig);
बाह्य पूर्णांक tty_audit_push(व्योम);
#अन्यथा
अटल अंतरभूत व्योम tty_audit_निकास(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम tty_audit_विभाजन(काष्ठा संकेत_काष्ठा *sig)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक tty_audit_push(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* tty_ioctl.c */
बाह्य पूर्णांक n_tty_ioctl_helper(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

/* vt.c */

बाह्य पूर्णांक vt_ioctl(काष्ठा tty_काष्ठा *tty,
		    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

बाह्य दीर्घ vt_compat_ioctl(काष्ठा tty_काष्ठा *tty,
		     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

/* tty_mutex.c */
/* functions क्रम preparation of BKL removal */
बाह्य व्योम tty_lock(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक  tty_lock_पूर्णांकerruptible(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_unlock(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_lock_slave(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_unlock_slave(काष्ठा tty_काष्ठा *tty);
बाह्य व्योम tty_set_lock_subclass(काष्ठा tty_काष्ठा *tty);

#अगर_घोषित CONFIG_PROC_FS
बाह्य व्योम proc_tty_रेजिस्टर_driver(काष्ठा tty_driver *);
बाह्य व्योम proc_tty_unरेजिस्टर_driver(काष्ठा tty_driver *);
#अन्यथा
अटल अंतरभूत व्योम proc_tty_रेजिस्टर_driver(काष्ठा tty_driver *d) अणुपूर्ण
अटल अंतरभूत व्योम proc_tty_unरेजिस्टर_driver(काष्ठा tty_driver *d) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
