<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * TTY core पूर्णांकernal functions
 */

#अगर_अघोषित _TTY_INTERNAL_H
#घोषणा _TTY_INTERNAL_H

#घोषणा tty_msg(fn, tty, f, ...) \
	fn("%s %s: " f, tty_driver_name(tty), tty_name(tty), ##__VA_ARGS__)

#घोषणा tty_debug(tty, f, ...)	tty_msg(pr_debug, tty, f, ##__VA_ARGS__)
#घोषणा tty_notice(tty, f, ...)	tty_msg(pr_notice, tty, f, ##__VA_ARGS__)
#घोषणा tty_warn(tty, f, ...)	tty_msg(pr_warn, tty, f, ##__VA_ARGS__)
#घोषणा tty_err(tty, f, ...)	tty_msg(pr_err, tty, f, ##__VA_ARGS__)

#घोषणा tty_info_ratelimited(tty, f, ...) \
		tty_msg(pr_info_ratelimited, tty, f, ##__VA_ARGS__)

/*
 * Lock subclasses क्रम tty locks
 *
 * TTY_LOCK_NORMAL is क्रम normal ttys and master ptys.
 * TTY_LOCK_SLAVE is क्रम slave ptys only.
 *
 * Lock subclasses are necessary क्रम handling nested locking with pty pairs.
 * tty locks which use nested locking:
 *
 * legacy_mutex - Nested tty locks are necessary क्रम releasing pty pairs.
 *		  The stable lock order is master pty first, then slave pty.
 * termios_rwsem - The stable lock order is tty_buffer lock->termios_rwsem.
 *		   Subclassing this lock enables the slave pty to hold its
 *		   termios_rwsem when claiming the master tty_buffer lock.
 * tty_buffer lock - slave ptys can claim nested buffer lock when handling
 *		     संकेत अक्षरs. The stable lock order is slave pty, then
 *		     master.
 */
क्रमागत अणु
	TTY_LOCK_NORMAL = 0,
	TTY_LOCK_SLAVE,
पूर्ण;

/* Values क्रम tty->flow_change */
#घोषणा TTY_THROTTLE_SAFE	1
#घोषणा TTY_UNTHROTTLE_SAFE	2

अटल अंतरभूत व्योम __tty_set_flow_change(काष्ठा tty_काष्ठा *tty, पूर्णांक val)
अणु
	tty->flow_change = val;
पूर्ण

अटल अंतरभूत व्योम tty_set_flow_change(काष्ठा tty_काष्ठा *tty, पूर्णांक val)
अणु
	tty->flow_change = val;
	smp_mb();
पूर्ण

पूर्णांक tty_ldisc_lock(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ समयout);
व्योम tty_ldisc_unlock(काष्ठा tty_काष्ठा *tty);

पूर्णांक __tty_check_change(काष्ठा tty_काष्ठा *tty, पूर्णांक sig);
पूर्णांक tty_check_change(काष्ठा tty_काष्ठा *tty);
व्योम __stop_tty(काष्ठा tty_काष्ठा *tty);
व्योम __start_tty(काष्ठा tty_काष्ठा *tty);
व्योम tty_vhangup_session(काष्ठा tty_काष्ठा *tty);
व्योम tty_खोलो_proc_set_tty(काष्ठा file *filp, काष्ठा tty_काष्ठा *tty);
पूर्णांक tty_संकेत_session_leader(काष्ठा tty_काष्ठा *tty, पूर्णांक निकास_session);
व्योम session_clear_tty(काष्ठा pid *session);
व्योम tty_buffer_मुक्त_all(काष्ठा tty_port *port);
व्योम tty_buffer_flush(काष्ठा tty_काष्ठा *tty, काष्ठा tty_ldisc *ld);
व्योम tty_buffer_init(काष्ठा tty_port *port);
व्योम tty_buffer_set_lock_subclass(काष्ठा tty_port *port);
bool tty_buffer_restart_work(काष्ठा tty_port *port);
bool tty_buffer_cancel_work(काष्ठा tty_port *port);
व्योम tty_buffer_flush_work(काष्ठा tty_port *port);
speed_t tty_termios_input_baud_rate(काष्ठा ktermios *termios);
व्योम tty_ldisc_hangup(काष्ठा tty_काष्ठा *tty, bool reset);
पूर्णांक tty_ldisc_reinit(काष्ठा tty_काष्ठा *tty, पूर्णांक disc);
दीर्घ tty_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
दीर्घ tty_jobctrl_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा tty_काष्ठा *real_tty,
		       काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
व्योम tty_शेष_fops(काष्ठा file_operations *fops);
काष्ठा tty_काष्ठा *alloc_tty_काष्ठा(काष्ठा tty_driver *driver, पूर्णांक idx);
पूर्णांक tty_alloc_file(काष्ठा file *file);
व्योम tty_add_file(काष्ठा tty_काष्ठा *tty, काष्ठा file *file);
व्योम tty_मुक्त_file(काष्ठा file *file);
पूर्णांक tty_release(काष्ठा inode *inode, काष्ठा file *filp);

#घोषणा tty_is_ग_लिखोlocked(tty)  (mutex_is_locked(&tty->atomic_ग_लिखो_lock))

पूर्णांक tty_ldisc_setup(काष्ठा tty_काष्ठा *tty, काष्ठा tty_काष्ठा *o_tty);
व्योम tty_ldisc_release(काष्ठा tty_काष्ठा *tty);
पूर्णांक __must_check tty_ldisc_init(काष्ठा tty_काष्ठा *tty);
व्योम tty_ldisc_deinit(काष्ठा tty_काष्ठा *tty);

व्योम tty_sysctl_init(व्योम);

/* tty_audit.c */
#अगर_घोषित CONFIG_AUDIT
व्योम tty_audit_add_data(काष्ठा tty_काष्ठा *tty, स्थिर व्योम *data, माप_प्रकार size);
व्योम tty_audit_tiocsti(काष्ठा tty_काष्ठा *tty, अक्षर ch);
#अन्यथा
अटल अंतरभूत व्योम tty_audit_add_data(काष्ठा tty_काष्ठा *tty, स्थिर व्योम *data,
				      माप_प्रकार size)
अणु
पूर्ण
अटल अंतरभूत व्योम tty_audit_tiocsti(काष्ठा tty_काष्ठा *tty, अक्षर ch)
अणु
पूर्ण
#पूर्ण_अगर

sमाप_प्रकार redirected_tty_ग_लिखो(काष्ठा kiocb *, काष्ठा iov_iter *);

#पूर्ण_अगर
