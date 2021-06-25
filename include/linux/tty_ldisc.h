<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TTY_LDISC_H
#घोषणा _LINUX_TTY_LDISC_H

/*
 * This काष्ठाure defines the पूर्णांकerface between the tty line discipline
 * implementation and the tty routines.  The following routines can be
 * defined; unless noted otherwise, they are optional, and can be
 * filled in with a null poपूर्णांकer.
 *
 * पूर्णांक	(*खोलो)(काष्ठा tty_काष्ठा *);
 *
 *	This function is called when the line discipline is associated
 *	with the tty.  The line discipline can use this as an
 *	opportunity to initialize any state needed by the ldisc routines.
 *
 * व्योम	(*बंद)(काष्ठा tty_काष्ठा *);
 *
 *	This function is called when the line discipline is being
 *	shutकरोwn, either because the tty is being बंदd or because
 *	the tty is being changed to use a new line discipline
 *
 * व्योम	(*flush_buffer)(काष्ठा tty_काष्ठा *tty);
 *
 *	This function inकाष्ठाs the line discipline to clear its
 *	buffers of any input अक्षरacters it may have queued to be
 *	delivered to the user mode process.
 *
 * sमाप_प्रकार (*पढ़ो)(काष्ठा tty_काष्ठा * tty, काष्ठा file * file,
 *		   अचिन्हित अक्षर * buf, माप_प्रकार nr);
 *
 *	This function is called when the user requests to पढ़ो from
 *	the tty.  The line discipline will वापस whatever अक्षरacters
 *	it has buffered up क्रम the user.  If this function is not
 *	defined, the user will receive an EIO error.
 *
 * sमाप_प्रकार (*ग_लिखो)(काष्ठा tty_काष्ठा * tty, काष्ठा file * file,
 *		    स्थिर अचिन्हित अक्षर * buf, माप_प्रकार nr);
 *
 *	This function is called when the user requests to ग_लिखो to the
 *	tty.  The line discipline will deliver the अक्षरacters to the
 *	low-level tty device क्रम transmission, optionally perक्रमming
 *	some processing on the अक्षरacters first.  If this function is
 *	not defined, the user will receive an EIO error.
 *
 * पूर्णांक	(*ioctl)(काष्ठा tty_काष्ठा * tty, काष्ठा file * file,
 *		 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
 *
 *	This function is called when the user requests an ioctl which
 *	is not handled by the tty layer or the low-level tty driver.
 *	It is पूर्णांकended क्रम ioctls which affect line discpline
 *	operation.  Note that the search order क्रम ioctls is (1) tty
 *	layer, (2) tty low-level driver, (3) line discpline.  So a
 *	low-level driver can "grab" an ioctl request beक्रमe the line
 *	discpline has a chance to see it.
 *
 * पूर्णांक	(*compat_ioctl)(काष्ठा tty_काष्ठा * tty, काष्ठा file * file,
 *		        अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
 *
 *	Process ioctl calls from 32-bit process on 64-bit प्रणाली
 *
 *	NOTE: only ioctls that are neither "poपूर्णांकer to compatible
 *	काष्ठाure" nor tty-generic.  Something निजी that takes
 *	an पूर्णांकeger or a poपूर्णांकer to wordsize-sensitive काष्ठाure
 *	beदीर्घs here, but most of ldiscs will happily leave
 *	it शून्य.
 *
 * व्योम	(*set_termios)(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios * old);
 *
 *	This function notअगरies the line discpline that a change has
 *	been made to the termios काष्ठाure.
 *
 * पूर्णांक	(*poll)(काष्ठा tty_काष्ठा * tty, काष्ठा file * file,
 *		  poll_table *रुको);
 *
 *	This function is called when a user attempts to select/poll on a
 *	tty device.  It is solely the responsibility of the line
 *	discipline to handle poll requests.
 *
 * व्योम	(*receive_buf)(काष्ठा tty_काष्ठा *, स्थिर अचिन्हित अक्षर *cp,
 *		       अक्षर *fp, पूर्णांक count);
 *
 *	This function is called by the low-level tty driver to send
 *	अक्षरacters received by the hardware to the line discpline क्रम
 *	processing.  <cp> is a poपूर्णांकer to the buffer of input
 *	अक्षरacter received by the device.  <fp> is a poपूर्णांकer to a
 *	poपूर्णांकer of flag bytes which indicate whether a अक्षरacter was
 *	received with a parity error, etc. <fp> may be शून्य to indicate
 *	all data received is TTY_NORMAL.
 *
 * व्योम	(*ग_लिखो_wakeup)(काष्ठा tty_काष्ठा *);
 *
 *	This function is called by the low-level tty driver to संकेत
 *	that line discpline should try to send more अक्षरacters to the
 *	low-level driver क्रम transmission.  If the line discpline करोes
 *	not have any more data to send, it can just वापस. If the line
 *	discipline करोes have some data to send, please arise a tasklet
 *	or workqueue to करो the real data transfer. Do not send data in
 *	this hook, it may leads to a deadlock.
 *
 * पूर्णांक (*hangup)(काष्ठा tty_काष्ठा *)
 *
 *	Called on a hangup. Tells the discipline that it should
 *	cease I/O to the tty driver. Can sleep. The driver should
 *	seek to perक्रमm this action quickly but should रुको until
 *	any pending driver I/O is completed.
 *
 * व्योम (*dcd_change)(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक status)
 *
 *	Tells the discipline that the DCD pin has changed its status.
 *	Used exclusively by the N_PPS (Pulse-Per-Second) line discipline.
 *
 * पूर्णांक	(*receive_buf2)(काष्ठा tty_काष्ठा *, स्थिर अचिन्हित अक्षर *cp,
 *			अक्षर *fp, पूर्णांक count);
 *
 *	This function is called by the low-level tty driver to send
 *	अक्षरacters received by the hardware to the line discpline क्रम
 *	processing.  <cp> is a poपूर्णांकer to the buffer of input
 *	अक्षरacter received by the device.  <fp> is a poपूर्णांकer to a
 *	poपूर्णांकer of flag bytes which indicate whether a अक्षरacter was
 *	received with a parity error, etc. <fp> may be शून्य to indicate
 *	all data received is TTY_NORMAL.
 *	If asचिन्हित, prefer this function क्रम स्वतःmatic flow control.
 */

#समावेश <linux/fs.h>
#समावेश <linux/रुको.h>
#समावेश <linux/atomic.h>

/*
 * the semaphore definition
 */
काष्ठा ld_semaphore अणु
	atomic_दीर्घ_t		count;
	raw_spinlock_t		रुको_lock;
	अचिन्हित पूर्णांक		रुको_पढ़ोers;
	काष्ठा list_head	पढ़ो_रुको;
	काष्ठा list_head	ग_लिखो_रुको;
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map	dep_map;
#पूर्ण_अगर
पूर्ण;

बाह्य व्योम __init_ldsem(काष्ठा ld_semaphore *sem, स्थिर अक्षर *name,
			 काष्ठा lock_class_key *key);

#घोषणा init_ldsem(sem)						\
करो अणु								\
	अटल काष्ठा lock_class_key __key;			\
								\
	__init_ldsem((sem), #sem, &__key);			\
पूर्ण जबतक (0)


बाह्य पूर्णांक ldsem_करोwn_पढ़ो(काष्ठा ld_semaphore *sem, दीर्घ समयout);
बाह्य पूर्णांक ldsem_करोwn_पढ़ो_trylock(काष्ठा ld_semaphore *sem);
बाह्य पूर्णांक ldsem_करोwn_ग_लिखो(काष्ठा ld_semaphore *sem, दीर्घ समयout);
बाह्य पूर्णांक ldsem_करोwn_ग_लिखो_trylock(काष्ठा ld_semaphore *sem);
बाह्य व्योम ldsem_up_पढ़ो(काष्ठा ld_semaphore *sem);
बाह्य व्योम ldsem_up_ग_लिखो(काष्ठा ld_semaphore *sem);

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
बाह्य पूर्णांक ldsem_करोwn_पढ़ो_nested(काष्ठा ld_semaphore *sem, पूर्णांक subclass,
				  दीर्घ समयout);
बाह्य पूर्णांक ldsem_करोwn_ग_लिखो_nested(काष्ठा ld_semaphore *sem, पूर्णांक subclass,
				   दीर्घ समयout);
#अन्यथा
# define ldsem_करोwn_पढ़ो_nested(sem, subclass, समयout)		\
		ldsem_करोwn_पढ़ो(sem, समयout)
# define ldsem_करोwn_ग_लिखो_nested(sem, subclass, समयout)	\
		ldsem_करोwn_ग_लिखो(sem, समयout)
#पूर्ण_अगर


काष्ठा tty_ldisc_ops अणु
	अक्षर	*name;
	पूर्णांक	num;
	पूर्णांक	flags;

	/*
	 * The following routines are called from above.
	 */
	पूर्णांक	(*खोलो)(काष्ठा tty_काष्ठा *);
	व्योम	(*बंद)(काष्ठा tty_काष्ठा *);
	व्योम	(*flush_buffer)(काष्ठा tty_काष्ठा *tty);
	sमाप_प्रकार	(*पढ़ो)(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			अचिन्हित अक्षर *buf, माप_प्रकार nr,
			व्योम **cookie, अचिन्हित दीर्घ offset);
	sमाप_प्रकार	(*ग_लिखो)(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			 स्थिर अचिन्हित अक्षर *buf, माप_प्रकार nr);
	पूर्णांक	(*ioctl)(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
	पूर्णांक	(*compat_ioctl)(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
	व्योम	(*set_termios)(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old);
	__poll_t (*poll)(काष्ठा tty_काष्ठा *, काष्ठा file *,
			     काष्ठा poll_table_काष्ठा *);
	पूर्णांक	(*hangup)(काष्ठा tty_काष्ठा *tty);

	/*
	 * The following routines are called from below.
	 */
	व्योम	(*receive_buf)(काष्ठा tty_काष्ठा *, स्थिर अचिन्हित अक्षर *cp,
			       अक्षर *fp, पूर्णांक count);
	व्योम	(*ग_लिखो_wakeup)(काष्ठा tty_काष्ठा *);
	व्योम	(*dcd_change)(काष्ठा tty_काष्ठा *, अचिन्हित पूर्णांक);
	पूर्णांक	(*receive_buf2)(काष्ठा tty_काष्ठा *, स्थिर अचिन्हित अक्षर *cp,
				अक्षर *fp, पूर्णांक count);

	काष्ठा  module *owner;

	पूर्णांक refcount;
पूर्ण;

काष्ठा tty_ldisc अणु
	काष्ठा tty_ldisc_ops *ops;
	काष्ठा tty_काष्ठा *tty;
पूर्ण;

#घोषणा LDISC_FLAG_DEFINED	0x00000001

#घोषणा MODULE_ALIAS_LDISC(ldisc) \
	MODULE_ALIAS("tty-ldisc-" __stringअगरy(ldisc))

#पूर्ण_अगर /* _LINUX_TTY_LDISC_H */
