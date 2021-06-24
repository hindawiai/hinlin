<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/kernel/prपूर्णांकk.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 * Modअगरied to make sys_syslog() more flexible: added commands to
 * वापस the last 4k of kernel messages, regardless of whether
 * they've been read or not.  Added option to suppress kernel printk's
 * to the console.  Added hook क्रम sending the console messages
 * अन्यथाwhere, in preparation क्रम a serial line console (someday).
 * Ted Ts'o, 2/11/93.
 * Modअगरied क्रम sysctl support, 1/8/97, Chris Horn.
 * Fixed SMP synchronization, 08/08/99, Manfred Spraul
 *     manfred@colorfullअगरe.com
 * Rewrote bits to get rid of console_lock
 *	01Mar01 Andrew Morton
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/nmi.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/delay.h>
#समावेश <linux/smp.h>
#समावेश <linux/security.h>
#समावेश <linux/memblock.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/crash_core.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/kmsg_dump.h>
#समावेश <linux/syslog.h>
#समावेश <linux/cpu.h>
#समावेश <linux/rculist.h>
#समावेश <linux/poll.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/uपन.स>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/sections.h>

#समावेश <trace/events/initcall.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/prपूर्णांकk.h>

#समावेश "printk_ringbuffer.h"
#समावेश "console_cmdline.h"
#समावेश "braille.h"
#समावेश "internal.h"

पूर्णांक console_prपूर्णांकk[4] = अणु
	CONSOLE_LOGLEVEL_DEFAULT,	/* console_loglevel */
	MESSAGE_LOGLEVEL_DEFAULT,	/* शेष_message_loglevel */
	CONSOLE_LOGLEVEL_MIN,		/* minimum_console_loglevel */
	CONSOLE_LOGLEVEL_DEFAULT,	/* शेष_console_loglevel */
पूर्ण;
EXPORT_SYMBOL_GPL(console_prपूर्णांकk);

atomic_t ignore_console_lock_warning __पढ़ो_mostly = ATOMIC_INIT(0);
EXPORT_SYMBOL(ignore_console_lock_warning);

/*
 * Low level drivers may need that to know अगर they can schedule in
 * their unblank() callback or not. So let's export it.
 */
पूर्णांक oops_in_progress;
EXPORT_SYMBOL(oops_in_progress);

/*
 * console_sem protects the console_drivers list, and also
 * provides serialisation क्रम access to the entire console
 * driver प्रणाली.
 */
अटल DEFINE_SEMAPHORE(console_sem);
काष्ठा console *console_drivers;
EXPORT_SYMBOL_GPL(console_drivers);

/*
 * System may need to suppress prपूर्णांकk message under certain
 * circumstances, like after kernel panic happens.
 */
पूर्णांक __पढ़ो_mostly suppress_prपूर्णांकk;

#अगर_घोषित CONFIG_LOCKDEP
अटल काष्ठा lockdep_map console_lock_dep_map = अणु
	.name = "console_lock"
पूर्ण;
#पूर्ण_अगर

क्रमागत devkmsg_log_bits अणु
	__DEVKMSG_LOG_BIT_ON = 0,
	__DEVKMSG_LOG_BIT_OFF,
	__DEVKMSG_LOG_BIT_LOCK,
पूर्ण;

क्रमागत devkmsg_log_masks अणु
	DEVKMSG_LOG_MASK_ON             = BIT(__DEVKMSG_LOG_BIT_ON),
	DEVKMSG_LOG_MASK_OFF            = BIT(__DEVKMSG_LOG_BIT_OFF),
	DEVKMSG_LOG_MASK_LOCK           = BIT(__DEVKMSG_LOG_BIT_LOCK),
पूर्ण;

/* Keep both the 'on' and 'off' bits clear, i.e. ratelimit by शेष: */
#घोषणा DEVKMSG_LOG_MASK_DEFAULT	0

अटल अचिन्हित पूर्णांक __पढ़ो_mostly devkmsg_log = DEVKMSG_LOG_MASK_DEFAULT;

अटल पूर्णांक __control_devkmsg(अक्षर *str)
अणु
	माप_प्रकार len;

	अगर (!str)
		वापस -EINVAL;

	len = str_has_prefix(str, "on");
	अगर (len) अणु
		devkmsg_log = DEVKMSG_LOG_MASK_ON;
		वापस len;
	पूर्ण

	len = str_has_prefix(str, "off");
	अगर (len) अणु
		devkmsg_log = DEVKMSG_LOG_MASK_OFF;
		वापस len;
	पूर्ण

	len = str_has_prefix(str, "ratelimit");
	अगर (len) अणु
		devkmsg_log = DEVKMSG_LOG_MASK_DEFAULT;
		वापस len;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __init control_devkmsg(अक्षर *str)
अणु
	अगर (__control_devkmsg(str) < 0)
		वापस 1;

	/*
	 * Set sysctl string accordingly:
	 */
	अगर (devkmsg_log == DEVKMSG_LOG_MASK_ON)
		म_नकल(devkmsg_log_str, "on");
	अन्यथा अगर (devkmsg_log == DEVKMSG_LOG_MASK_OFF)
		म_नकल(devkmsg_log_str, "off");
	/* अन्यथा "ratelimit" which is set by शेष. */

	/*
	 * Sysctl cannot change it anymore. The kernel command line setting of
	 * this parameter is to क्रमce the setting to be permanent throughout the
	 * runसमय of the प्रणाली. This is a precation measure against userspace
	 * trying to be a smarta** and attempting to change it up on us.
	 */
	devkmsg_log |= DEVKMSG_LOG_MASK_LOCK;

	वापस 0;
पूर्ण
__setup("printk.devkmsg=", control_devkmsg);

अक्षर devkmsg_log_str[DEVKMSG_STR_MAX_SIZE] = "ratelimit";

पूर्णांक devkmsg_sysctl_set_loglvl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			      व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अक्षर old_str[DEVKMSG_STR_MAX_SIZE];
	अचिन्हित पूर्णांक old;
	पूर्णांक err;

	अगर (ग_लिखो) अणु
		अगर (devkmsg_log & DEVKMSG_LOG_MASK_LOCK)
			वापस -EINVAL;

		old = devkmsg_log;
		म_नकलन(old_str, devkmsg_log_str, DEVKMSG_STR_MAX_SIZE);
	पूर्ण

	err = proc_करोstring(table, ग_लिखो, buffer, lenp, ppos);
	अगर (err)
		वापस err;

	अगर (ग_लिखो) अणु
		err = __control_devkmsg(devkmsg_log_str);

		/*
		 * Do not accept an unknown string OR a known string with
		 * trailing crap...
		 */
		अगर (err < 0 || (err + 1 != *lenp)) अणु

			/* ... and restore old setting. */
			devkmsg_log = old;
			म_नकलन(devkmsg_log_str, old_str, DEVKMSG_STR_MAX_SIZE);

			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Number of रेजिस्टरed extended console drivers. */
अटल पूर्णांक nr_ext_console_drivers;

/*
 * Helper macros to handle lockdep when locking/unlocking console_sem. We use
 * macros instead of functions so that _RET_IP_ contains useful inक्रमmation.
 */
#घोषणा करोwn_console_sem() करो अणु \
	करोwn(&console_sem);\
	mutex_acquire(&console_lock_dep_map, 0, 0, _RET_IP_);\
पूर्ण जबतक (0)

अटल पूर्णांक __करोwn_trylock_console_sem(अचिन्हित दीर्घ ip)
अणु
	पूर्णांक lock_failed;
	अचिन्हित दीर्घ flags;

	/*
	 * Here and in __up_console_sem() we need to be in safe mode,
	 * because spindump/WARN/etc from under console ->lock will
	 * deadlock in prपूर्णांकk()->करोwn_trylock_console_sem() otherwise.
	 */
	prपूर्णांकk_safe_enter_irqsave(flags);
	lock_failed = करोwn_trylock(&console_sem);
	prपूर्णांकk_safe_निकास_irqrestore(flags);

	अगर (lock_failed)
		वापस 1;
	mutex_acquire(&console_lock_dep_map, 0, 1, ip);
	वापस 0;
पूर्ण
#घोषणा करोwn_trylock_console_sem() __करोwn_trylock_console_sem(_RET_IP_)

अटल व्योम __up_console_sem(अचिन्हित दीर्घ ip)
अणु
	अचिन्हित दीर्घ flags;

	mutex_release(&console_lock_dep_map, ip);

	prपूर्णांकk_safe_enter_irqsave(flags);
	up(&console_sem);
	prपूर्णांकk_safe_निकास_irqrestore(flags);
पूर्ण
#घोषणा up_console_sem() __up_console_sem(_RET_IP_)

/*
 * This is used क्रम debugging the mess that is the VT code by
 * keeping track अगर we have the console semaphore held. It's
 * definitely not the perfect debug tool (we करोn't know अगर _WE_
 * hold it and are racing, but it helps tracking those weird code
 * paths in the console code where we end up in places I want
 * locked without the console semaphore held).
 */
अटल पूर्णांक console_locked, console_suspended;

/*
 * If exclusive_console is non-शून्य then only this console is to be prपूर्णांकed to.
 */
अटल काष्ठा console *exclusive_console;

/*
 *	Array of consoles built from command line options (console=)
 */

#घोषणा MAX_CMDLINECONSOLES 8

अटल काष्ठा console_cmdline console_cmdline[MAX_CMDLINECONSOLES];

अटल पूर्णांक preferred_console = -1;
अटल bool has_preferred_console;
पूर्णांक console_set_on_cmdline;
EXPORT_SYMBOL(console_set_on_cmdline);

/* Flag: console code may call schedule() */
अटल पूर्णांक console_may_schedule;

क्रमागत con_msg_क्रमmat_flags अणु
	MSG_FORMAT_DEFAULT	= 0,
	MSG_FORMAT_SYSLOG	= (1 << 0),
पूर्ण;

अटल पूर्णांक console_msg_क्रमmat = MSG_FORMAT_DEFAULT;

/*
 * The prपूर्णांकk log buffer consists of a sequenced collection of records, each
 * containing variable length message text. Every record also contains its
 * own meta-data (@info).
 *
 * Every record meta-data carries the बारtamp in microseconds, as well as
 * the standard userspace syslog level and syslog facility. The usual kernel
 * messages use LOG_KERN; userspace-injected messages always carry a matching
 * syslog facility, by शेष LOG_USER. The origin of every message can be
 * reliably determined that way.
 *
 * The human पढ़ोable log message of a record is available in @text, the
 * length of the message text in @text_len. The stored message is not
 * terminated.
 *
 * Optionally, a record can carry a dictionary of properties (key/value
 * pairs), to provide userspace with a machine-पढ़ोable message context.
 *
 * Examples क्रम well-defined, commonly used property names are:
 *   DEVICE=b12:8               device identअगरier
 *                                b12:8         block dev_t
 *                                c127:3        अक्षर dev_t
 *                                n8            netdev अगरindex
 *                                +sound:card0  subप्रणाली:devname
 *   SUBSYSTEM=pci              driver-core subप्रणाली name
 *
 * Valid अक्षरacters in property names are [a-zA-Z0-9.-_]. Property names
 * and values are terminated by a '\0' अक्षरacter.
 *
 * Example of record values:
 *   record.text_buf                = "it's a line" (unterminated)
 *   record.info.seq                = 56
 *   record.info.ts_nsec            = 36863
 *   record.info.text_len           = 11
 *   record.info.facility           = 0 (LOG_KERN)
 *   record.info.flags              = 0
 *   record.info.level              = 3 (LOG_ERR)
 *   record.info.caller_id          = 299 (task 299)
 *   record.info.dev_info.subप्रणाली = "pci" (terminated)
 *   record.info.dev_info.device    = "+pci:0000:00:01.0" (terminated)
 *
 * The 'struct printk_info' buffer must never be directly exported to
 * userspace, it is a kernel-निजी implementation detail that might
 * need to be changed in the future, when the requirements change.
 *
 * /dev/kmsg exports the काष्ठाured data in the following line क्रमmat:
 *   "<level>,<sequnum>,<timestamp>,<contflag>[,additional_values, ... ];<message text>\n"
 *
 * Users of the export क्रमmat should ignore possible additional values
 * separated by ',', and find the message after the ';' अक्षरacter.
 *
 * The optional key/value pairs are attached as continuation lines starting
 * with a space अक्षरacter and terminated by a newline. All possible
 * non-prinatable अक्षरacters are escaped in the "\xff" notation.
 */

क्रमागत log_flags अणु
	LOG_NEWLINE	= 2,	/* text ended with a newline */
	LOG_CONT	= 8,	/* text is a fragment of a continuation line */
पूर्ण;

/* syslog_lock protects syslog_* variables and ग_लिखो access to clear_seq. */
अटल DEFINE_RAW_SPINLOCK(syslog_lock);

#अगर_घोषित CONFIG_PRINTK
DECLARE_WAIT_QUEUE_HEAD(log_रुको);
/* All 3 रक्षित by @syslog_lock. */
/* the next prपूर्णांकk record to पढ़ो by syslog(READ) or /proc/kmsg */
अटल u64 syslog_seq;
अटल माप_प्रकार syslog_partial;
अटल bool syslog_समय;

/* All 3 रक्षित by @console_sem. */
/* the next prपूर्णांकk record to ग_लिखो to the console */
अटल u64 console_seq;
अटल u64 exclusive_console_stop_seq;
अटल अचिन्हित दीर्घ console_dropped;

काष्ठा latched_seq अणु
	seqcount_latch_t	latch;
	u64			val[2];
पूर्ण;

/*
 * The next prपूर्णांकk record to पढ़ो after the last 'clear' command. There are
 * two copies (updated with seqcount_latch) so that पढ़ोs can locklessly
 * access a valid value. Writers are synchronized by @syslog_lock.
 */
अटल काष्ठा latched_seq clear_seq = अणु
	.latch		= SEQCNT_LATCH_ZERO(clear_seq.latch),
	.val[0]		= 0,
	.val[1]		= 0,
पूर्ण;

#अगर_घोषित CONFIG_PRINTK_CALLER
#घोषणा PREFIX_MAX		48
#अन्यथा
#घोषणा PREFIX_MAX		32
#पूर्ण_अगर

/* the maximum size of a क्रमmatted record (i.e. with prefix added per line) */
#घोषणा CONSOLE_LOG_MAX		1024

/* the maximum size allowed to be reserved क्रम a record */
#घोषणा LOG_LINE_MAX		(CONSOLE_LOG_MAX - PREFIX_MAX)

#घोषणा LOG_LEVEL(v)		((v) & 0x07)
#घोषणा LOG_FACILITY(v)		((v) >> 3 & 0xff)

/* record buffer */
#घोषणा LOG_ALIGN __alignof__(अचिन्हित दीर्घ)
#घोषणा __LOG_BUF_LEN (1 << CONFIG_LOG_BUF_SHIFT)
#घोषणा LOG_BUF_LEN_MAX (u32)(1 << 31)
अटल अक्षर __log_buf[__LOG_BUF_LEN] __aligned(LOG_ALIGN);
अटल अक्षर *log_buf = __log_buf;
अटल u32 log_buf_len = __LOG_BUF_LEN;

/*
 * Define the average message size. This only affects the number of
 * descriptors that will be available. Underestimating is better than
 * overestimating (too many available descriptors is better than not enough).
 */
#घोषणा PRB_AVGBITS 5	/* 32 अक्षरacter average length */

#अगर CONFIG_LOG_BUF_SHIFT <= PRB_AVGBITS
#त्रुटि CONFIG_LOG_BUF_SHIFT value too small.
#पूर्ण_अगर
_DEFINE_PRINTKRB(prपूर्णांकk_rb_अटल, CONFIG_LOG_BUF_SHIFT - PRB_AVGBITS,
		 PRB_AVGBITS, &__log_buf[0]);

अटल काष्ठा prपूर्णांकk_ringbuffer prपूर्णांकk_rb_dynamic;

अटल काष्ठा prपूर्णांकk_ringbuffer *prb = &prपूर्णांकk_rb_अटल;

/*
 * We cannot access per-CPU data (e.g. per-CPU flush irq_work) beक्रमe
 * per_cpu_areas are initialised. This variable is set to true when
 * it's safe to access per-CPU data.
 */
अटल bool __prपूर्णांकk_percpu_data_पढ़ोy __पढ़ो_mostly;

bool prपूर्णांकk_percpu_data_पढ़ोy(व्योम)
अणु
	वापस __prपूर्णांकk_percpu_data_पढ़ोy;
पूर्ण

/* Must be called under syslog_lock. */
अटल व्योम latched_seq_ग_लिखो(काष्ठा latched_seq *ls, u64 val)
अणु
	raw_ग_लिखो_seqcount_latch(&ls->latch);
	ls->val[0] = val;
	raw_ग_लिखो_seqcount_latch(&ls->latch);
	ls->val[1] = val;
पूर्ण

/* Can be called from any context. */
अटल u64 latched_seq_पढ़ो_nolock(काष्ठा latched_seq *ls)
अणु
	अचिन्हित पूर्णांक seq;
	अचिन्हित पूर्णांक idx;
	u64 val;

	करो अणु
		seq = raw_पढ़ो_seqcount_latch(&ls->latch);
		idx = seq & 0x1;
		val = ls->val[idx];
	पूर्ण जबतक (पढ़ो_seqcount_latch_retry(&ls->latch, seq));

	वापस val;
पूर्ण

/* Return log buffer address */
अक्षर *log_buf_addr_get(व्योम)
अणु
	वापस log_buf;
पूर्ण

/* Return log buffer size */
u32 log_buf_len_get(व्योम)
अणु
	वापस log_buf_len;
पूर्ण

/*
 * Define how much of the log buffer we could take at maximum. The value
 * must be greater than two. Note that only half of the buffer is available
 * when the index poपूर्णांकs to the middle.
 */
#घोषणा MAX_LOG_TAKE_PART 4
अटल स्थिर अक्षर trunc_msg[] = "<truncated>";

अटल व्योम truncate_msg(u16 *text_len, u16 *trunc_msg_len)
अणु
	/*
	 * The message should not take the whole buffer. Otherwise, it might
	 * get हटाओd too soon.
	 */
	u32 max_text_len = log_buf_len / MAX_LOG_TAKE_PART;

	अगर (*text_len > max_text_len)
		*text_len = max_text_len;

	/* enable the warning message (अगर there is room) */
	*trunc_msg_len = म_माप(trunc_msg);
	अगर (*text_len >= *trunc_msg_len)
		*text_len -= *trunc_msg_len;
	अन्यथा
		*trunc_msg_len = 0;
पूर्ण

पूर्णांक dmesg_restrict = IS_ENABLED(CONFIG_SECURITY_DMESG_RESTRICT);

अटल पूर्णांक syslog_action_restricted(पूर्णांक type)
अणु
	अगर (dmesg_restrict)
		वापस 1;
	/*
	 * Unless restricted, we allow "read all" and "get buffer size"
	 * क्रम everybody.
	 */
	वापस type != SYSLOG_ACTION_READ_ALL &&
	       type != SYSLOG_ACTION_SIZE_BUFFER;
पूर्ण

अटल पूर्णांक check_syslog_permissions(पूर्णांक type, पूर्णांक source)
अणु
	/*
	 * If this is from /proc/kmsg and we've already opened it, then we've
	 * alपढ़ोy करोne the capabilities checks at खोलो समय.
	 */
	अगर (source == SYSLOG_FROM_PROC && type != SYSLOG_ACTION_OPEN)
		जाओ ok;

	अगर (syslog_action_restricted(type)) अणु
		अगर (capable(CAP_SYSLOG))
			जाओ ok;
		/*
		 * For historical reasons, accept CAP_SYS_ADMIN too, with
		 * a warning.
		 */
		अगर (capable(CAP_SYS_ADMIN)) अणु
			pr_warn_once("%s (%d): Attempt to access syslog with "
				     "CAP_SYS_ADMIN but no CAP_SYSLOG "
				     "(deprecated).\n",
				 current->comm, task_pid_nr(current));
			जाओ ok;
		पूर्ण
		वापस -EPERM;
	पूर्ण
ok:
	वापस security_syslog(type);
पूर्ण

अटल व्योम append_अक्षर(अक्षर **pp, अक्षर *e, अक्षर c)
अणु
	अगर (*pp < e)
		*(*pp)++ = c;
पूर्ण

अटल sमाप_प्रकार info_prपूर्णांक_ext_header(अक्षर *buf, माप_प्रकार size,
				     काष्ठा prपूर्णांकk_info *info)
अणु
	u64 ts_usec = info->ts_nsec;
	अक्षर caller[20];
#अगर_घोषित CONFIG_PRINTK_CALLER
	u32 id = info->caller_id;

	snम_लिखो(caller, माप(caller), ",caller=%c%u",
		 id & 0x80000000 ? 'C' : 'T', id & ~0x80000000);
#अन्यथा
	caller[0] = '\0';
#पूर्ण_अगर

	करो_भाग(ts_usec, 1000);

	वापस scnम_लिखो(buf, size, "%u,%llu,%llu,%c%s;",
			 (info->facility << 3) | info->level, info->seq,
			 ts_usec, info->flags & LOG_CONT ? 'c' : '-', caller);
पूर्ण

अटल sमाप_प्रकार msg_add_ext_text(अक्षर *buf, माप_प्रकार size,
				स्थिर अक्षर *text, माप_प्रकार text_len,
				अचिन्हित अक्षर endc)
अणु
	अक्षर *p = buf, *e = buf + size;
	माप_प्रकार i;

	/* escape non-prपूर्णांकable अक्षरacters */
	क्रम (i = 0; i < text_len; i++) अणु
		अचिन्हित अक्षर c = text[i];

		अगर (c < ' ' || c >= 127 || c == '\\')
			p += scnम_लिखो(p, e - p, "\\x%02x", c);
		अन्यथा
			append_अक्षर(&p, e, c);
	पूर्ण
	append_अक्षर(&p, e, endc);

	वापस p - buf;
पूर्ण

अटल sमाप_प्रकार msg_add_dict_text(अक्षर *buf, माप_प्रकार size,
				 स्थिर अक्षर *key, स्थिर अक्षर *val)
अणु
	माप_प्रकार val_len = म_माप(val);
	sमाप_प्रकार len;

	अगर (!val_len)
		वापस 0;

	len = msg_add_ext_text(buf, size, "", 0, ' ');	/* dict prefix */
	len += msg_add_ext_text(buf + len, size - len, key, म_माप(key), '=');
	len += msg_add_ext_text(buf + len, size - len, val, val_len, '\n');

	वापस len;
पूर्ण

अटल sमाप_प्रकार msg_prपूर्णांक_ext_body(अक्षर *buf, माप_प्रकार size,
				  अक्षर *text, माप_प्रकार text_len,
				  काष्ठा dev_prपूर्णांकk_info *dev_info)
अणु
	sमाप_प्रकार len;

	len = msg_add_ext_text(buf, size, text, text_len, '\n');

	अगर (!dev_info)
		जाओ out;

	len += msg_add_dict_text(buf + len, size - len, "SUBSYSTEM",
				 dev_info->subप्रणाली);
	len += msg_add_dict_text(buf + len, size - len, "DEVICE",
				 dev_info->device);
out:
	वापस len;
पूर्ण

/* /dev/kmsg - userspace message inject/listen पूर्णांकerface */
काष्ठा devkmsg_user अणु
	atomic64_t seq;
	काष्ठा ratelimit_state rs;
	काष्ठा mutex lock;
	अक्षर buf[CONSOLE_EXT_LOG_MAX];

	काष्ठा prपूर्णांकk_info info;
	अक्षर text_buf[CONSOLE_EXT_LOG_MAX];
	काष्ठा prपूर्णांकk_record record;
पूर्ण;

अटल __म_लिखो(3, 4) __cold
पूर्णांक devkmsg_emit(पूर्णांक facility, पूर्णांक level, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक r;

	बहु_शुरू(args, fmt);
	r = vprपूर्णांकk_emit(facility, level, शून्य, fmt, args);
	बहु_पूर्ण(args);

	वापस r;
पूर्ण

अटल sमाप_प्रकार devkmsg_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	अक्षर *buf, *line;
	पूर्णांक level = शेष_message_loglevel;
	पूर्णांक facility = 1;	/* LOG_USER */
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा devkmsg_user *user = file->निजी_data;
	माप_प्रकार len = iov_iter_count(from);
	sमाप_प्रकार ret = len;

	अगर (!user || len > LOG_LINE_MAX)
		वापस -EINVAL;

	/* Ignore when user logging is disabled. */
	अगर (devkmsg_log & DEVKMSG_LOG_MASK_OFF)
		वापस len;

	/* Ratelimit when not explicitly enabled. */
	अगर (!(devkmsg_log & DEVKMSG_LOG_MASK_ON)) अणु
		अगर (!___ratelimit(&user->rs, current->comm))
			वापस ret;
	पूर्ण

	buf = kदो_स्मृति(len+1, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	buf[len] = '\0';
	अगर (!copy_from_iter_full(buf, len, from)) अणु
		kमुक्त(buf);
		वापस -EFAULT;
	पूर्ण

	/*
	 * Extract and skip the syslog prefix <[0-9]*>. Coming from userspace
	 * the decimal value represents 32bit, the lower 3 bit are the log
	 * level, the rest are the log facility.
	 *
	 * If no prefix or no userspace facility is specअगरied, we
	 * enक्रमce LOG_USER, to be able to reliably distinguish
	 * kernel-generated messages from userspace-injected ones.
	 */
	line = buf;
	अगर (line[0] == '<') अणु
		अक्षर *endp = शून्य;
		अचिन्हित पूर्णांक u;

		u = simple_म_से_अदीर्घ(line + 1, &endp, 10);
		अगर (endp && endp[0] == '>') अणु
			level = LOG_LEVEL(u);
			अगर (LOG_FACILITY(u) != 0)
				facility = LOG_FACILITY(u);
			endp++;
			line = endp;
		पूर्ण
	पूर्ण

	devkmsg_emit(facility, level, "%s", line);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार devkmsg_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा devkmsg_user *user = file->निजी_data;
	काष्ठा prपूर्णांकk_record *r = &user->record;
	माप_प्रकार len;
	sमाप_प्रकार ret;

	अगर (!user)
		वापस -EBADF;

	ret = mutex_lock_पूर्णांकerruptible(&user->lock);
	अगर (ret)
		वापस ret;

	prपूर्णांकk_safe_enter_irq();
	अगर (!prb_पढ़ो_valid(prb, atomic64_पढ़ो(&user->seq), r)) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			ret = -EAGAIN;
			prपूर्णांकk_safe_निकास_irq();
			जाओ out;
		पूर्ण

		prपूर्णांकk_safe_निकास_irq();
		ret = रुको_event_पूर्णांकerruptible(log_रुको,
				prb_पढ़ो_valid(prb, atomic64_पढ़ो(&user->seq), r));
		अगर (ret)
			जाओ out;
		prपूर्णांकk_safe_enter_irq();
	पूर्ण

	अगर (r->info->seq != atomic64_पढ़ो(&user->seq)) अणु
		/* our last seen message is gone, वापस error and reset */
		atomic64_set(&user->seq, r->info->seq);
		ret = -EPIPE;
		prपूर्णांकk_safe_निकास_irq();
		जाओ out;
	पूर्ण

	len = info_prपूर्णांक_ext_header(user->buf, माप(user->buf), r->info);
	len += msg_prपूर्णांक_ext_body(user->buf + len, माप(user->buf) - len,
				  &r->text_buf[0], r->info->text_len,
				  &r->info->dev_info);

	atomic64_set(&user->seq, r->info->seq + 1);
	prपूर्णांकk_safe_निकास_irq();

	अगर (len > count) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (copy_to_user(buf, user->buf, len)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	ret = len;
out:
	mutex_unlock(&user->lock);
	वापस ret;
पूर्ण

/*
 * Be careful when modअगरying this function!!!
 *
 * Only few operations are supported because the device works only with the
 * entire variable length messages (records). Non-standard values are
 * वापसed in the other हालs and has been this way क्रम quite some समय.
 * User space applications might depend on this behavior.
 */
अटल loff_t devkmsg_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा devkmsg_user *user = file->निजी_data;
	loff_t ret = 0;

	अगर (!user)
		वापस -EBADF;
	अगर (offset)
		वापस -ESPIPE;

	prपूर्णांकk_safe_enter_irq();
	चयन (whence) अणु
	हाल शुरू_से:
		/* the first record */
		atomic64_set(&user->seq, prb_first_valid_seq(prb));
		अवरोध;
	हाल SEEK_DATA:
		/*
		 * The first record after the last SYSLOG_ACTION_CLEAR,
		 * like issued by 'dmesg -c'. Reading /dev/kmsg itself
		 * changes no global state, and करोes not clear anything.
		 */
		atomic64_set(&user->seq, latched_seq_पढ़ो_nolock(&clear_seq));
		अवरोध;
	हाल अंत_से:
		/* after the last record */
		atomic64_set(&user->seq, prb_next_seq(prb));
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	prपूर्णांकk_safe_निकास_irq();
	वापस ret;
पूर्ण

अटल __poll_t devkmsg_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा devkmsg_user *user = file->निजी_data;
	काष्ठा prपूर्णांकk_info info;
	__poll_t ret = 0;

	अगर (!user)
		वापस EPOLLERR|EPOLLNVAL;

	poll_रुको(file, &log_रुको, रुको);

	prपूर्णांकk_safe_enter_irq();
	अगर (prb_पढ़ो_valid_info(prb, atomic64_पढ़ो(&user->seq), &info, शून्य)) अणु
		/* वापस error when data has vanished underneath us */
		अगर (info.seq != atomic64_पढ़ो(&user->seq))
			ret = EPOLLIN|EPOLLRDNORM|EPOLLERR|EPOLLPRI;
		अन्यथा
			ret = EPOLLIN|EPOLLRDNORM;
	पूर्ण
	prपूर्णांकk_safe_निकास_irq();

	वापस ret;
पूर्ण

अटल पूर्णांक devkmsg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा devkmsg_user *user;
	पूर्णांक err;

	अगर (devkmsg_log & DEVKMSG_LOG_MASK_OFF)
		वापस -EPERM;

	/* ग_लिखो-only करोes not need any file context */
	अगर ((file->f_flags & O_ACCMODE) != O_WRONLY) अणु
		err = check_syslog_permissions(SYSLOG_ACTION_READ_ALL,
					       SYSLOG_FROM_READER);
		अगर (err)
			वापस err;
	पूर्ण

	user = kदो_स्मृति(माप(काष्ठा devkmsg_user), GFP_KERNEL);
	अगर (!user)
		वापस -ENOMEM;

	ratelimit_शेष_init(&user->rs);
	ratelimit_set_flags(&user->rs, RATELIMIT_MSG_ON_RELEASE);

	mutex_init(&user->lock);

	prb_rec_init_rd(&user->record, &user->info,
			&user->text_buf[0], माप(user->text_buf));

	prपूर्णांकk_safe_enter_irq();
	atomic64_set(&user->seq, prb_first_valid_seq(prb));
	prपूर्णांकk_safe_निकास_irq();

	file->निजी_data = user;
	वापस 0;
पूर्ण

अटल पूर्णांक devkmsg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा devkmsg_user *user = file->निजी_data;

	अगर (!user)
		वापस 0;

	ratelimit_state_निकास(&user->rs);

	mutex_destroy(&user->lock);
	kमुक्त(user);
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations kmsg_fops = अणु
	.खोलो = devkmsg_खोलो,
	.पढ़ो = devkmsg_पढ़ो,
	.ग_लिखो_iter = devkmsg_ग_लिखो,
	.llseek = devkmsg_llseek,
	.poll = devkmsg_poll,
	.release = devkmsg_release,
पूर्ण;

#अगर_घोषित CONFIG_CRASH_CORE
/*
 * This appends the listed symbols to /proc/vmcore
 *
 * /proc/vmcore is used by various utilities, like crash and makedumpfile to
 * obtain access to symbols that are otherwise very dअगरficult to locate.  These
 * symbols are specअगरically used so that utilities can access and extract the
 * dmesg log from a vmcore file after a crash.
 */
व्योम log_buf_vmcoreinfo_setup(व्योम)
अणु
	काष्ठा dev_prपूर्णांकk_info *dev_info = शून्य;

	VMCOREINFO_SYMBOL(prb);
	VMCOREINFO_SYMBOL(prपूर्णांकk_rb_अटल);
	VMCOREINFO_SYMBOL(clear_seq);

	/*
	 * Export काष्ठा size and field offsets. User space tools can
	 * parse it and detect any changes to काष्ठाure करोwn the line.
	 */

	VMCOREINFO_STRUCT_SIZE(prपूर्णांकk_ringbuffer);
	VMCOREINFO_OFFSET(prपूर्णांकk_ringbuffer, desc_ring);
	VMCOREINFO_OFFSET(prपूर्णांकk_ringbuffer, text_data_ring);
	VMCOREINFO_OFFSET(prपूर्णांकk_ringbuffer, fail);

	VMCOREINFO_STRUCT_SIZE(prb_desc_ring);
	VMCOREINFO_OFFSET(prb_desc_ring, count_bits);
	VMCOREINFO_OFFSET(prb_desc_ring, descs);
	VMCOREINFO_OFFSET(prb_desc_ring, infos);
	VMCOREINFO_OFFSET(prb_desc_ring, head_id);
	VMCOREINFO_OFFSET(prb_desc_ring, tail_id);

	VMCOREINFO_STRUCT_SIZE(prb_desc);
	VMCOREINFO_OFFSET(prb_desc, state_var);
	VMCOREINFO_OFFSET(prb_desc, text_blk_lpos);

	VMCOREINFO_STRUCT_SIZE(prb_data_blk_lpos);
	VMCOREINFO_OFFSET(prb_data_blk_lpos, begin);
	VMCOREINFO_OFFSET(prb_data_blk_lpos, next);

	VMCOREINFO_STRUCT_SIZE(prपूर्णांकk_info);
	VMCOREINFO_OFFSET(prपूर्णांकk_info, seq);
	VMCOREINFO_OFFSET(prपूर्णांकk_info, ts_nsec);
	VMCOREINFO_OFFSET(prपूर्णांकk_info, text_len);
	VMCOREINFO_OFFSET(prपूर्णांकk_info, caller_id);
	VMCOREINFO_OFFSET(prपूर्णांकk_info, dev_info);

	VMCOREINFO_STRUCT_SIZE(dev_prपूर्णांकk_info);
	VMCOREINFO_OFFSET(dev_prपूर्णांकk_info, subप्रणाली);
	VMCOREINFO_LENGTH(prपूर्णांकk_info_subप्रणाली, माप(dev_info->subप्रणाली));
	VMCOREINFO_OFFSET(dev_prपूर्णांकk_info, device);
	VMCOREINFO_LENGTH(prपूर्णांकk_info_device, माप(dev_info->device));

	VMCOREINFO_STRUCT_SIZE(prb_data_ring);
	VMCOREINFO_OFFSET(prb_data_ring, size_bits);
	VMCOREINFO_OFFSET(prb_data_ring, data);
	VMCOREINFO_OFFSET(prb_data_ring, head_lpos);
	VMCOREINFO_OFFSET(prb_data_ring, tail_lpos);

	VMCOREINFO_SIZE(atomic_दीर्घ_t);
	VMCOREINFO_TYPE_OFFSET(atomic_दीर्घ_t, counter);

	VMCOREINFO_STRUCT_SIZE(latched_seq);
	VMCOREINFO_OFFSET(latched_seq, val);
पूर्ण
#पूर्ण_अगर

/* requested log_buf_len from kernel cmdline */
अटल अचिन्हित दीर्घ __initdata new_log_buf_len;

/* we practice scaling the ring buffer by घातers of 2 */
अटल व्योम __init log_buf_len_update(u64 size)
अणु
	अगर (size > (u64)LOG_BUF_LEN_MAX) अणु
		size = (u64)LOG_BUF_LEN_MAX;
		pr_err("log_buf over 2G is not supported.\n");
	पूर्ण

	अगर (size)
		size = roundup_घात_of_two(size);
	अगर (size > log_buf_len)
		new_log_buf_len = (अचिन्हित दीर्घ)size;
पूर्ण

/* save requested log_buf_len since it's too early to process it */
अटल पूर्णांक __init log_buf_len_setup(अक्षर *str)
अणु
	u64 size;

	अगर (!str)
		वापस -EINVAL;

	size = memparse(str, &str);

	log_buf_len_update(size);

	वापस 0;
पूर्ण
early_param("log_buf_len", log_buf_len_setup);

#अगर_घोषित CONFIG_SMP
#घोषणा __LOG_CPU_MAX_BUF_LEN (1 << CONFIG_LOG_CPU_MAX_BUF_SHIFT)

अटल व्योम __init log_buf_add_cpu(व्योम)
अणु
	अचिन्हित पूर्णांक cpu_extra;

	/*
	 * archs should set up cpu_possible_bits properly with
	 * set_cpu_possible() after setup_arch() but just in
	 * हाल lets ensure this is valid.
	 */
	अगर (num_possible_cpus() == 1)
		वापस;

	cpu_extra = (num_possible_cpus() - 1) * __LOG_CPU_MAX_BUF_LEN;

	/* by शेष this will only जारी through क्रम large > 64 CPUs */
	अगर (cpu_extra <= __LOG_BUF_LEN / 2)
		वापस;

	pr_info("log_buf_len individual max cpu contribution: %d bytes\n",
		__LOG_CPU_MAX_BUF_LEN);
	pr_info("log_buf_len total cpu_extra contributions: %d bytes\n",
		cpu_extra);
	pr_info("log_buf_len min size: %d bytes\n", __LOG_BUF_LEN);

	log_buf_len_update(cpu_extra + __LOG_BUF_LEN);
पूर्ण
#अन्यथा /* !CONFIG_SMP */
अटल अंतरभूत व्योम log_buf_add_cpu(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम __init set_percpu_data_पढ़ोy(व्योम)
अणु
	prपूर्णांकk_safe_init();
	/* Make sure we set this flag only after prपूर्णांकk_safe() init is करोne */
	barrier();
	__prपूर्णांकk_percpu_data_पढ़ोy = true;
पूर्ण

अटल अचिन्हित पूर्णांक __init add_to_rb(काष्ठा prपूर्णांकk_ringbuffer *rb,
				     काष्ठा prपूर्णांकk_record *r)
अणु
	काष्ठा prb_reserved_entry e;
	काष्ठा prपूर्णांकk_record dest_r;

	prb_rec_init_wr(&dest_r, r->info->text_len);

	अगर (!prb_reserve(&e, rb, &dest_r))
		वापस 0;

	स_नकल(&dest_r.text_buf[0], &r->text_buf[0], r->info->text_len);
	dest_r.info->text_len = r->info->text_len;
	dest_r.info->facility = r->info->facility;
	dest_r.info->level = r->info->level;
	dest_r.info->flags = r->info->flags;
	dest_r.info->ts_nsec = r->info->ts_nsec;
	dest_r.info->caller_id = r->info->caller_id;
	स_नकल(&dest_r.info->dev_info, &r->info->dev_info, माप(dest_r.info->dev_info));

	prb_final_commit(&e);

	वापस prb_record_text_space(&e);
पूर्ण

अटल अक्षर setup_text_buf[LOG_LINE_MAX] __initdata;

व्योम __init setup_log_buf(पूर्णांक early)
अणु
	काष्ठा prपूर्णांकk_info *new_infos;
	अचिन्हित पूर्णांक new_descs_count;
	काष्ठा prb_desc *new_descs;
	काष्ठा prपूर्णांकk_info info;
	काष्ठा prपूर्णांकk_record r;
	माप_प्रकार new_descs_size;
	माप_प्रकार new_infos_size;
	अचिन्हित दीर्घ flags;
	अक्षर *new_log_buf;
	अचिन्हित पूर्णांक मुक्त;
	u64 seq;

	/*
	 * Some archs call setup_log_buf() multiple बार - first is very
	 * early, e.g. from setup_arch(), and second - when percpu_areas
	 * are initialised.
	 */
	अगर (!early)
		set_percpu_data_पढ़ोy();

	अगर (log_buf != __log_buf)
		वापस;

	अगर (!early && !new_log_buf_len)
		log_buf_add_cpu();

	अगर (!new_log_buf_len)
		वापस;

	new_descs_count = new_log_buf_len >> PRB_AVGBITS;
	अगर (new_descs_count == 0) अणु
		pr_err("new_log_buf_len: %lu too small\n", new_log_buf_len);
		वापस;
	पूर्ण

	new_log_buf = memblock_alloc(new_log_buf_len, LOG_ALIGN);
	अगर (unlikely(!new_log_buf)) अणु
		pr_err("log_buf_len: %lu text bytes not available\n",
		       new_log_buf_len);
		वापस;
	पूर्ण

	new_descs_size = new_descs_count * माप(काष्ठा prb_desc);
	new_descs = memblock_alloc(new_descs_size, LOG_ALIGN);
	अगर (unlikely(!new_descs)) अणु
		pr_err("log_buf_len: %zu desc bytes not available\n",
		       new_descs_size);
		जाओ err_मुक्त_log_buf;
	पूर्ण

	new_infos_size = new_descs_count * माप(काष्ठा prपूर्णांकk_info);
	new_infos = memblock_alloc(new_infos_size, LOG_ALIGN);
	अगर (unlikely(!new_infos)) अणु
		pr_err("log_buf_len: %zu info bytes not available\n",
		       new_infos_size);
		जाओ err_मुक्त_descs;
	पूर्ण

	prb_rec_init_rd(&r, &info, &setup_text_buf[0], माप(setup_text_buf));

	prb_init(&prपूर्णांकk_rb_dynamic,
		 new_log_buf, ilog2(new_log_buf_len),
		 new_descs, ilog2(new_descs_count),
		 new_infos);

	prपूर्णांकk_safe_enter_irqsave(flags);

	log_buf_len = new_log_buf_len;
	log_buf = new_log_buf;
	new_log_buf_len = 0;

	मुक्त = __LOG_BUF_LEN;
	prb_क्रम_each_record(0, &prपूर्णांकk_rb_अटल, seq, &r)
		मुक्त -= add_to_rb(&prपूर्णांकk_rb_dynamic, &r);

	/*
	 * This is early enough that everything is still running on the
	 * boot CPU and पूर्णांकerrupts are disabled. So no new messages will
	 * appear during the transition to the dynamic buffer.
	 */
	prb = &prपूर्णांकk_rb_dynamic;

	prपूर्णांकk_safe_निकास_irqrestore(flags);

	अगर (seq != prb_next_seq(&prपूर्णांकk_rb_अटल)) अणु
		pr_err("dropped %llu messages\n",
		       prb_next_seq(&prपूर्णांकk_rb_अटल) - seq);
	पूर्ण

	pr_info("log_buf_len: %u bytes\n", log_buf_len);
	pr_info("early log buf free: %u(%u%%)\n",
		मुक्त, (मुक्त * 100) / __LOG_BUF_LEN);
	वापस;

err_मुक्त_descs:
	memblock_मुक्त(__pa(new_descs), new_descs_size);
err_मुक्त_log_buf:
	memblock_मुक्त(__pa(new_log_buf), new_log_buf_len);
पूर्ण

अटल bool __पढ़ो_mostly ignore_loglevel;

अटल पूर्णांक __init ignore_loglevel_setup(अक्षर *str)
अणु
	ignore_loglevel = true;
	pr_info("debug: ignoring loglevel setting.\n");

	वापस 0;
पूर्ण

early_param("ignore_loglevel", ignore_loglevel_setup);
module_param(ignore_loglevel, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ignore_loglevel,
		 "ignore loglevel setting (prints all kernel messages to the console)");

अटल bool suppress_message_prपूर्णांकing(पूर्णांक level)
अणु
	वापस (level >= console_loglevel && !ignore_loglevel);
पूर्ण

#अगर_घोषित CONFIG_BOOT_PRINTK_DELAY

अटल पूर्णांक boot_delay; /* msecs delay after each prपूर्णांकk during bootup */
अटल अचिन्हित दीर्घ दीर्घ loops_per_msec;	/* based on boot_delay */

अटल पूर्णांक __init boot_delay_setup(अक्षर *str)
अणु
	अचिन्हित दीर्घ lpj;

	lpj = preset_lpj ? preset_lpj : 1000000;	/* some guess */
	loops_per_msec = (अचिन्हित दीर्घ दीर्घ)lpj / 1000 * HZ;

	get_option(&str, &boot_delay);
	अगर (boot_delay > 10 * 1000)
		boot_delay = 0;

	pr_debug("boot_delay: %u, preset_lpj: %ld, lpj: %lu, "
		"HZ: %d, loops_per_msec: %llu\n",
		boot_delay, preset_lpj, lpj, HZ, loops_per_msec);
	वापस 0;
पूर्ण
early_param("boot_delay", boot_delay_setup);

अटल व्योम boot_delay_msec(पूर्णांक level)
अणु
	अचिन्हित दीर्घ दीर्घ k;
	अचिन्हित दीर्घ समयout;

	अगर ((boot_delay == 0 || प्रणाली_state >= SYSTEM_RUNNING)
		|| suppress_message_prपूर्णांकing(level)) अणु
		वापस;
	पूर्ण

	k = (अचिन्हित दीर्घ दीर्घ)loops_per_msec * boot_delay;

	समयout = jअगरfies + msecs_to_jअगरfies(boot_delay);
	जबतक (k) अणु
		k--;
		cpu_relax();
		/*
		 * use (अस्थिर) jअगरfies to prevent
		 * compiler reduction; loop termination via jअगरfies
		 * is secondary and may or may not happen.
		 */
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
		touch_nmi_watchकरोg();
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम boot_delay_msec(पूर्णांक level)
अणु
पूर्ण
#पूर्ण_अगर

अटल bool prपूर्णांकk_समय = IS_ENABLED(CONFIG_PRINTK_TIME);
module_param_named(समय, prपूर्णांकk_समय, bool, S_IRUGO | S_IWUSR);

अटल माप_प्रकार prपूर्णांक_syslog(अचिन्हित पूर्णांक level, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "<%u>", level);
पूर्ण

अटल माप_प्रकार prपूर्णांक_समय(u64 ts, अक्षर *buf)
अणु
	अचिन्हित दीर्घ rem_nsec = करो_भाग(ts, 1000000000);

	वापस प्र_लिखो(buf, "[%5lu.%06lu]",
		       (अचिन्हित दीर्घ)ts, rem_nsec / 1000);
पूर्ण

#अगर_घोषित CONFIG_PRINTK_CALLER
अटल माप_प्रकार prपूर्णांक_caller(u32 id, अक्षर *buf)
अणु
	अक्षर caller[12];

	snम_लिखो(caller, माप(caller), "%c%u",
		 id & 0x80000000 ? 'C' : 'T', id & ~0x80000000);
	वापस प्र_लिखो(buf, "[%6s]", caller);
पूर्ण
#अन्यथा
#घोषणा prपूर्णांक_caller(id, buf) 0
#पूर्ण_अगर

अटल माप_प्रकार info_prपूर्णांक_prefix(स्थिर काष्ठा prपूर्णांकk_info  *info, bool syslog,
				bool समय, अक्षर *buf)
अणु
	माप_प्रकार len = 0;

	अगर (syslog)
		len = prपूर्णांक_syslog((info->facility << 3) | info->level, buf);

	अगर (समय)
		len += prपूर्णांक_समय(info->ts_nsec, buf + len);

	len += prपूर्णांक_caller(info->caller_id, buf + len);

	अगर (IS_ENABLED(CONFIG_PRINTK_CALLER) || समय) अणु
		buf[len++] = ' ';
		buf[len] = '\0';
	पूर्ण

	वापस len;
पूर्ण

/*
 * Prepare the record क्रम prपूर्णांकing. The text is shअगरted within the given
 * buffer to aव्योम a need क्रम another one. The following operations are
 * करोne:
 *
 *   - Add prefix क्रम each line.
 *   - Drop truncated lines that no दीर्घer fit पूर्णांकo the buffer.
 *   - Add the trailing newline that has been हटाओd in vprपूर्णांकk_store().
 *   - Add a string terminator.
 *
 * Since the produced string is always terminated, the maximum possible
 * वापस value is @r->text_buf_size - 1;
 *
 * Return: The length of the updated/prepared text, including the added
 * prefixes and the newline. The terminator is not counted. The dropped
 * line(s) are not counted.
 */
अटल माप_प्रकार record_prपूर्णांक_text(काष्ठा prपूर्णांकk_record *r, bool syslog,
				bool समय)
अणु
	माप_प्रकार text_len = r->info->text_len;
	माप_प्रकार buf_size = r->text_buf_size;
	अक्षर *text = r->text_buf;
	अक्षर prefix[PREFIX_MAX];
	bool truncated = false;
	माप_प्रकार prefix_len;
	माप_प्रकार line_len;
	माप_प्रकार len = 0;
	अक्षर *next;

	/*
	 * If the message was truncated because the buffer was not large
	 * enough, treat the available text as अगर it were the full text.
	 */
	अगर (text_len > buf_size)
		text_len = buf_size;

	prefix_len = info_prपूर्णांक_prefix(r->info, syslog, समय, prefix);

	/*
	 * @text_len: bytes of unprocessed text
	 * @line_len: bytes of current line _without_ newline
	 * @text:     poपूर्णांकer to beginning of current line
	 * @len:      number of bytes prepared in r->text_buf
	 */
	क्रम (;;) अणु
		next = स_प्रथम(text, '\n', text_len);
		अगर (next) अणु
			line_len = next - text;
		पूर्ण अन्यथा अणु
			/* Drop truncated line(s). */
			अगर (truncated)
				अवरोध;
			line_len = text_len;
		पूर्ण

		/*
		 * Truncate the text अगर there is not enough space to add the
		 * prefix and a trailing newline and a terminator.
		 */
		अगर (len + prefix_len + text_len + 1 + 1 > buf_size) अणु
			/* Drop even the current line अगर no space. */
			अगर (len + prefix_len + line_len + 1 + 1 > buf_size)
				अवरोध;

			text_len = buf_size - len - prefix_len - 1 - 1;
			truncated = true;
		पूर्ण

		स_हटाओ(text + prefix_len, text, text_len);
		स_नकल(text, prefix, prefix_len);

		/*
		 * Increment the prepared length to include the text and
		 * prefix that were just moved+copied. Also increment क्रम the
		 * newline at the end of this line. If this is the last line,
		 * there is no newline, but it will be added immediately below.
		 */
		len += prefix_len + line_len + 1;
		अगर (text_len == line_len) अणु
			/*
			 * This is the last line. Add the trailing newline
			 * हटाओd in vprपूर्णांकk_store().
			 */
			text[prefix_len + line_len] = '\n';
			अवरोध;
		पूर्ण

		/*
		 * Advance beyond the added prefix and the related line with
		 * its newline.
		 */
		text += prefix_len + line_len + 1;

		/*
		 * The reमुख्यing text has only decreased by the line with its
		 * newline.
		 *
		 * Note that @text_len can become zero. It happens when @text
		 * ended with a newline (either due to truncation or the
		 * original string ending with "\n\n"). The loop is correctly
		 * repeated and (अगर not truncated) an empty line with a prefix
		 * will be prepared.
		 */
		text_len -= line_len + 1;
	पूर्ण

	/*
	 * If a buffer was provided, it will be terminated. Space क्रम the
	 * string terminator is guaranteed to be available. The terminator is
	 * not counted in the वापस value.
	 */
	अगर (buf_size > 0)
		r->text_buf[len] = 0;

	वापस len;
पूर्ण

अटल माप_प्रकार get_record_prपूर्णांक_text_size(काष्ठा prपूर्णांकk_info *info,
					 अचिन्हित पूर्णांक line_count,
					 bool syslog, bool समय)
अणु
	अक्षर prefix[PREFIX_MAX];
	माप_प्रकार prefix_len;

	prefix_len = info_prपूर्णांक_prefix(info, syslog, समय, prefix);

	/*
	 * Each line will be preceded with a prefix. The पूर्णांकermediate
	 * newlines are alपढ़ोy within the text, but a final trailing
	 * newline will be added.
	 */
	वापस ((prefix_len * line_count) + info->text_len + 1);
पूर्ण

/*
 * Beginning with @start_seq, find the first record where it and all following
 * records up to (but not including) @max_seq fit पूर्णांकo @size.
 *
 * @max_seq is simply an upper bound and करोes not need to exist. If the caller
 * करोes not require an upper bound, -1 can be used क्रम @max_seq.
 */
अटल u64 find_first_fitting_seq(u64 start_seq, u64 max_seq, माप_प्रकार size,
				  bool syslog, bool समय)
अणु
	काष्ठा prपूर्णांकk_info info;
	अचिन्हित पूर्णांक line_count;
	माप_प्रकार len = 0;
	u64 seq;

	/* Determine the size of the records up to @max_seq. */
	prb_क्रम_each_info(start_seq, prb, seq, &info, &line_count) अणु
		अगर (info.seq >= max_seq)
			अवरोध;
		len += get_record_prपूर्णांक_text_size(&info, line_count, syslog, समय);
	पूर्ण

	/*
	 * Adjust the upper bound क्रम the next loop to aव्योम subtracting
	 * lengths that were never added.
	 */
	अगर (seq < max_seq)
		max_seq = seq;

	/*
	 * Move first record क्रमward until length fits पूर्णांकo the buffer. Ignore
	 * newest messages that were not counted in the above cycle. Messages
	 * might appear and get lost in the meanसमय. This is a best efक्रमt
	 * that prevents an infinite loop that could occur with a retry.
	 */
	prb_क्रम_each_info(start_seq, prb, seq, &info, &line_count) अणु
		अगर (len <= size || info.seq >= max_seq)
			अवरोध;
		len -= get_record_prपूर्णांक_text_size(&info, line_count, syslog, समय);
	पूर्ण

	वापस seq;
पूर्ण

अटल पूर्णांक syslog_prपूर्णांक(अक्षर __user *buf, पूर्णांक size)
अणु
	काष्ठा prपूर्णांकk_info info;
	काष्ठा prपूर्णांकk_record r;
	अक्षर *text;
	पूर्णांक len = 0;

	text = kदो_स्मृति(CONSOLE_LOG_MAX, GFP_KERNEL);
	अगर (!text)
		वापस -ENOMEM;

	prb_rec_init_rd(&r, &info, text, CONSOLE_LOG_MAX);

	जबतक (size > 0) अणु
		माप_प्रकार n;
		माप_प्रकार skip;

		prपूर्णांकk_safe_enter_irq();
		raw_spin_lock(&syslog_lock);
		अगर (!prb_पढ़ो_valid(prb, syslog_seq, &r)) अणु
			raw_spin_unlock(&syslog_lock);
			prपूर्णांकk_safe_निकास_irq();
			अवरोध;
		पूर्ण
		अगर (r.info->seq != syslog_seq) अणु
			/* message is gone, move to next valid one */
			syslog_seq = r.info->seq;
			syslog_partial = 0;
		पूर्ण

		/*
		 * To keep पढ़ोing/counting partial line consistent,
		 * use prपूर्णांकk_समय value as of the beginning of a line.
		 */
		अगर (!syslog_partial)
			syslog_समय = prपूर्णांकk_समय;

		skip = syslog_partial;
		n = record_prपूर्णांक_text(&r, true, syslog_समय);
		अगर (n - syslog_partial <= size) अणु
			/* message fits पूर्णांकo buffer, move क्रमward */
			syslog_seq = r.info->seq + 1;
			n -= syslog_partial;
			syslog_partial = 0;
		पूर्ण अन्यथा अगर (!len)अणु
			/* partial पढ़ो(), remember position */
			n = size;
			syslog_partial += n;
		पूर्ण अन्यथा
			n = 0;
		raw_spin_unlock(&syslog_lock);
		prपूर्णांकk_safe_निकास_irq();

		अगर (!n)
			अवरोध;

		अगर (copy_to_user(buf, text + skip, n)) अणु
			अगर (!len)
				len = -EFAULT;
			अवरोध;
		पूर्ण

		len += n;
		size -= n;
		buf += n;
	पूर्ण

	kमुक्त(text);
	वापस len;
पूर्ण

अटल पूर्णांक syslog_prपूर्णांक_all(अक्षर __user *buf, पूर्णांक size, bool clear)
अणु
	काष्ठा prपूर्णांकk_info info;
	काष्ठा prपूर्णांकk_record r;
	अक्षर *text;
	पूर्णांक len = 0;
	u64 seq;
	bool समय;

	text = kदो_स्मृति(CONSOLE_LOG_MAX, GFP_KERNEL);
	अगर (!text)
		वापस -ENOMEM;

	समय = prपूर्णांकk_समय;
	prपूर्णांकk_safe_enter_irq();
	/*
	 * Find first record that fits, including all following records,
	 * पूर्णांकo the user-provided buffer क्रम this dump.
	 */
	seq = find_first_fitting_seq(latched_seq_पढ़ो_nolock(&clear_seq), -1,
				     size, true, समय);

	prb_rec_init_rd(&r, &info, text, CONSOLE_LOG_MAX);

	len = 0;
	prb_क्रम_each_record(seq, prb, seq, &r) अणु
		पूर्णांक textlen;

		textlen = record_prपूर्णांक_text(&r, true, समय);

		अगर (len + textlen > size) अणु
			seq--;
			अवरोध;
		पूर्ण

		prपूर्णांकk_safe_निकास_irq();
		अगर (copy_to_user(buf + len, text, textlen))
			len = -EFAULT;
		अन्यथा
			len += textlen;
		prपूर्णांकk_safe_enter_irq();

		अगर (len < 0)
			अवरोध;
	पूर्ण

	अगर (clear) अणु
		raw_spin_lock(&syslog_lock);
		latched_seq_ग_लिखो(&clear_seq, seq);
		raw_spin_unlock(&syslog_lock);
	पूर्ण
	prपूर्णांकk_safe_निकास_irq();

	kमुक्त(text);
	वापस len;
पूर्ण

अटल व्योम syslog_clear(व्योम)
अणु
	prपूर्णांकk_safe_enter_irq();
	raw_spin_lock(&syslog_lock);
	latched_seq_ग_लिखो(&clear_seq, prb_next_seq(prb));
	raw_spin_unlock(&syslog_lock);
	prपूर्णांकk_safe_निकास_irq();
पूर्ण

/* Return a consistent copy of @syslog_seq. */
अटल u64 पढ़ो_syslog_seq_irq(व्योम)
अणु
	u64 seq;

	raw_spin_lock_irq(&syslog_lock);
	seq = syslog_seq;
	raw_spin_unlock_irq(&syslog_lock);

	वापस seq;
पूर्ण

पूर्णांक करो_syslog(पूर्णांक type, अक्षर __user *buf, पूर्णांक len, पूर्णांक source)
अणु
	काष्ठा prपूर्णांकk_info info;
	bool clear = false;
	अटल पूर्णांक saved_console_loglevel = LOGLEVEL_DEFAULT;
	पूर्णांक error;

	error = check_syslog_permissions(type, source);
	अगर (error)
		वापस error;

	चयन (type) अणु
	हाल SYSLOG_ACTION_CLOSE:	/* Close log */
		अवरोध;
	हाल SYSLOG_ACTION_OPEN:	/* Open log */
		अवरोध;
	हाल SYSLOG_ACTION_READ:	/* Read from log */
		अगर (!buf || len < 0)
			वापस -EINVAL;
		अगर (!len)
			वापस 0;
		अगर (!access_ok(buf, len))
			वापस -EFAULT;

		error = रुको_event_पूर्णांकerruptible(log_रुको,
				prb_पढ़ो_valid(prb, पढ़ो_syslog_seq_irq(), शून्य));
		अगर (error)
			वापस error;
		error = syslog_prपूर्णांक(buf, len);
		अवरोध;
	/* Read/clear last kernel messages */
	हाल SYSLOG_ACTION_READ_CLEAR:
		clear = true;
		fallthrough;
	/* Read last kernel messages */
	हाल SYSLOG_ACTION_READ_ALL:
		अगर (!buf || len < 0)
			वापस -EINVAL;
		अगर (!len)
			वापस 0;
		अगर (!access_ok(buf, len))
			वापस -EFAULT;
		error = syslog_prपूर्णांक_all(buf, len, clear);
		अवरोध;
	/* Clear ring buffer */
	हाल SYSLOG_ACTION_CLEAR:
		syslog_clear();
		अवरोध;
	/* Disable logging to console */
	हाल SYSLOG_ACTION_CONSOLE_OFF:
		अगर (saved_console_loglevel == LOGLEVEL_DEFAULT)
			saved_console_loglevel = console_loglevel;
		console_loglevel = minimum_console_loglevel;
		अवरोध;
	/* Enable logging to console */
	हाल SYSLOG_ACTION_CONSOLE_ON:
		अगर (saved_console_loglevel != LOGLEVEL_DEFAULT) अणु
			console_loglevel = saved_console_loglevel;
			saved_console_loglevel = LOGLEVEL_DEFAULT;
		पूर्ण
		अवरोध;
	/* Set level of messages prपूर्णांकed to console */
	हाल SYSLOG_ACTION_CONSOLE_LEVEL:
		अगर (len < 1 || len > 8)
			वापस -EINVAL;
		अगर (len < minimum_console_loglevel)
			len = minimum_console_loglevel;
		console_loglevel = len;
		/* Implicitly re-enable logging to console */
		saved_console_loglevel = LOGLEVEL_DEFAULT;
		अवरोध;
	/* Number of अक्षरs in the log buffer */
	हाल SYSLOG_ACTION_SIZE_UNREAD:
		prपूर्णांकk_safe_enter_irq();
		raw_spin_lock(&syslog_lock);
		अगर (!prb_पढ़ो_valid_info(prb, syslog_seq, &info, शून्य)) अणु
			/* No unपढ़ो messages. */
			raw_spin_unlock(&syslog_lock);
			prपूर्णांकk_safe_निकास_irq();
			वापस 0;
		पूर्ण
		अगर (info.seq != syslog_seq) अणु
			/* messages are gone, move to first one */
			syslog_seq = info.seq;
			syslog_partial = 0;
		पूर्ण
		अगर (source == SYSLOG_FROM_PROC) अणु
			/*
			 * Short-cut क्रम poll(/"proc/kmsg") which simply checks
			 * क्रम pending data, not the size; वापस the count of
			 * records, not the length.
			 */
			error = prb_next_seq(prb) - syslog_seq;
		पूर्ण अन्यथा अणु
			bool समय = syslog_partial ? syslog_समय : prपूर्णांकk_समय;
			अचिन्हित पूर्णांक line_count;
			u64 seq;

			prb_क्रम_each_info(syslog_seq, prb, seq, &info,
					  &line_count) अणु
				error += get_record_prपूर्णांक_text_size(&info, line_count,
								    true, समय);
				समय = prपूर्णांकk_समय;
			पूर्ण
			error -= syslog_partial;
		पूर्ण
		raw_spin_unlock(&syslog_lock);
		prपूर्णांकk_safe_निकास_irq();
		अवरोध;
	/* Size of the log buffer */
	हाल SYSLOG_ACTION_SIZE_BUFFER:
		error = log_buf_len;
		अवरोध;
	शेष:
		error = -EINVAL;
		अवरोध;
	पूर्ण

	वापस error;
पूर्ण

SYSCALL_DEFINE3(syslog, पूर्णांक, type, अक्षर __user *, buf, पूर्णांक, len)
अणु
	वापस करो_syslog(type, buf, len, SYSLOG_FROM_READER);
पूर्ण

/*
 * Special console_lock variants that help to reduce the risk of soft-lockups.
 * They allow to pass console_lock to another prपूर्णांकk() call using a busy रुको.
 */

#अगर_घोषित CONFIG_LOCKDEP
अटल काष्ठा lockdep_map console_owner_dep_map = अणु
	.name = "console_owner"
पूर्ण;
#पूर्ण_अगर

अटल DEFINE_RAW_SPINLOCK(console_owner_lock);
अटल काष्ठा task_काष्ठा *console_owner;
अटल bool console_रुकोer;

/**
 * console_lock_spinning_enable - mark beginning of code where another
 *	thपढ़ो might safely busy रुको
 *
 * This basically converts console_lock पूर्णांकo a spinlock. This marks
 * the section where the console_lock owner can not sleep, because
 * there may be a रुकोer spinning (like a spinlock). Also it must be
 * पढ़ोy to hand over the lock at the end of the section.
 */
अटल व्योम console_lock_spinning_enable(व्योम)
अणु
	raw_spin_lock(&console_owner_lock);
	console_owner = current;
	raw_spin_unlock(&console_owner_lock);

	/* The रुकोer may spin on us after setting console_owner */
	spin_acquire(&console_owner_dep_map, 0, 0, _THIS_IP_);
पूर्ण

/**
 * console_lock_spinning_disable_and_check - mark end of code where another
 *	thपढ़ो was able to busy रुको and check अगर there is a रुकोer
 *
 * This is called at the end of the section where spinning is allowed.
 * It has two functions. First, it is a संकेत that it is no दीर्घer
 * safe to start busy रुकोing क्रम the lock. Second, it checks अगर
 * there is a busy रुकोer and passes the lock rights to her.
 *
 * Important: Callers lose the lock अगर there was a busy रुकोer.
 *	They must not touch items synchronized by console_lock
 *	in this हाल.
 *
 * Return: 1 अगर the lock rights were passed, 0 otherwise.
 */
अटल पूर्णांक console_lock_spinning_disable_and_check(व्योम)
अणु
	पूर्णांक रुकोer;

	raw_spin_lock(&console_owner_lock);
	रुकोer = READ_ONCE(console_रुकोer);
	console_owner = शून्य;
	raw_spin_unlock(&console_owner_lock);

	अगर (!रुकोer) अणु
		spin_release(&console_owner_dep_map, _THIS_IP_);
		वापस 0;
	पूर्ण

	/* The रुकोer is now मुक्त to जारी */
	WRITE_ONCE(console_रुकोer, false);

	spin_release(&console_owner_dep_map, _THIS_IP_);

	/*
	 * Hand off console_lock to रुकोer. The रुकोer will perक्रमm
	 * the up(). After this, the रुकोer is the console_lock owner.
	 */
	mutex_release(&console_lock_dep_map, _THIS_IP_);
	वापस 1;
पूर्ण

/**
 * console_trylock_spinning - try to get console_lock by busy रुकोing
 *
 * This allows to busy रुको क्रम the console_lock when the current
 * owner is running in specially marked sections. It means that
 * the current owner is running and cannot reschedule until it
 * is पढ़ोy to lose the lock.
 *
 * Return: 1 अगर we got the lock, 0 othrewise
 */
अटल पूर्णांक console_trylock_spinning(व्योम)
अणु
	काष्ठा task_काष्ठा *owner = शून्य;
	bool रुकोer;
	bool spin = false;
	अचिन्हित दीर्घ flags;

	अगर (console_trylock())
		वापस 1;

	prपूर्णांकk_safe_enter_irqsave(flags);

	raw_spin_lock(&console_owner_lock);
	owner = READ_ONCE(console_owner);
	रुकोer = READ_ONCE(console_रुकोer);
	अगर (!रुकोer && owner && owner != current) अणु
		WRITE_ONCE(console_रुकोer, true);
		spin = true;
	पूर्ण
	raw_spin_unlock(&console_owner_lock);

	/*
	 * If there is an active prपूर्णांकk() writing to the
	 * consoles, instead of having it ग_लिखो our data too,
	 * see अगर we can offload that load from the active
	 * prपूर्णांकer, and करो some prपूर्णांकing ourselves.
	 * Go पूर्णांकo a spin only अगर there isn't alपढ़ोy a रुकोer
	 * spinning, and there is an active prपूर्णांकer, and
	 * that active prपूर्णांकer isn't us (recursive prपूर्णांकk?).
	 */
	अगर (!spin) अणु
		prपूर्णांकk_safe_निकास_irqrestore(flags);
		वापस 0;
	पूर्ण

	/* We spin रुकोing क्रम the owner to release us */
	spin_acquire(&console_owner_dep_map, 0, 0, _THIS_IP_);
	/* Owner will clear console_रुकोer on hand off */
	जबतक (READ_ONCE(console_रुकोer))
		cpu_relax();
	spin_release(&console_owner_dep_map, _THIS_IP_);

	prपूर्णांकk_safe_निकास_irqrestore(flags);
	/*
	 * The owner passed the console lock to us.
	 * Since we did not spin on console lock, annotate
	 * this as a trylock. Otherwise lockdep will
	 * complain.
	 */
	mutex_acquire(&console_lock_dep_map, 0, 1, _THIS_IP_);

	वापस 1;
पूर्ण

/*
 * Call the console drivers, asking them to ग_लिखो out
 * log_buf[start] to log_buf[end - 1].
 * The console_lock must be held.
 */
अटल व्योम call_console_drivers(स्थिर अक्षर *ext_text, माप_प्रकार ext_len,
				 स्थिर अक्षर *text, माप_प्रकार len)
अणु
	अटल अक्षर dropped_text[64];
	माप_प्रकार dropped_len = 0;
	काष्ठा console *con;

	trace_console_rcuidle(text, len);

	अगर (!console_drivers)
		वापस;

	अगर (console_dropped) अणु
		dropped_len = snम_लिखो(dropped_text, माप(dropped_text),
				       "** %lu printk messages dropped **\n",
				       console_dropped);
		console_dropped = 0;
	पूर्ण

	क्रम_each_console(con) अणु
		अगर (exclusive_console && con != exclusive_console)
			जारी;
		अगर (!(con->flags & CON_ENABLED))
			जारी;
		अगर (!con->ग_लिखो)
			जारी;
		अगर (!cpu_online(smp_processor_id()) &&
		    !(con->flags & CON_ANYTIME))
			जारी;
		अगर (con->flags & CON_EXTENDED)
			con->ग_लिखो(con, ext_text, ext_len);
		अन्यथा अणु
			अगर (dropped_len)
				con->ग_लिखो(con, dropped_text, dropped_len);
			con->ग_लिखो(con, text, len);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक prपूर्णांकk_delay_msec __पढ़ो_mostly;

अटल अंतरभूत व्योम prपूर्णांकk_delay(व्योम)
अणु
	अगर (unlikely(prपूर्णांकk_delay_msec)) अणु
		पूर्णांक m = prपूर्णांकk_delay_msec;

		जबतक (m--) अणु
			mdelay(1);
			touch_nmi_watchकरोg();
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत u32 prपूर्णांकk_caller_id(व्योम)
अणु
	वापस in_task() ? task_pid_nr(current) :
		0x80000000 + raw_smp_processor_id();
पूर्ण

/**
 * parse_prefix - Parse level and control flags.
 *
 * @text:     The terminated text message.
 * @level:    A poपूर्णांकer to the current level value, will be updated.
 * @lflags:   A poपूर्णांकer to the current log flags, will be updated.
 *
 * @level may be शून्य अगर the caller is not पूर्णांकerested in the parsed value.
 * Otherwise the variable poपूर्णांकed to by @level must be set to
 * LOGLEVEL_DEFAULT in order to be updated with the parsed value.
 *
 * @lflags may be शून्य अगर the caller is not पूर्णांकerested in the parsed value.
 * Otherwise the variable poपूर्णांकed to by @lflags will be OR'd with the parsed
 * value.
 *
 * Return: The length of the parsed level and control flags.
 */
अटल u16 parse_prefix(अक्षर *text, पूर्णांक *level, क्रमागत log_flags *lflags)
अणु
	u16 prefix_len = 0;
	पूर्णांक kern_level;

	जबतक (*text) अणु
		kern_level = prपूर्णांकk_get_level(text);
		अगर (!kern_level)
			अवरोध;

		चयन (kern_level) अणु
		हाल '0' ... '7':
			अगर (level && *level == LOGLEVEL_DEFAULT)
				*level = kern_level - '0';
			अवरोध;
		हाल 'c':	/* KERN_CONT */
			अगर (lflags)
				*lflags |= LOG_CONT;
		पूर्ण

		prefix_len += 2;
		text += 2;
	पूर्ण

	वापस prefix_len;
पूर्ण

अटल u16 prपूर्णांकk_sprपूर्णांक(अक्षर *text, u16 size, पूर्णांक facility, क्रमागत log_flags *lflags,
			 स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	u16 text_len;

	text_len = vscnम_लिखो(text, size, fmt, args);

	/* Mark and strip a trailing newline. */
	अगर (text_len && text[text_len - 1] == '\n') अणु
		text_len--;
		*lflags |= LOG_NEWLINE;
	पूर्ण

	/* Strip log level and control flags. */
	अगर (facility == 0) अणु
		u16 prefix_len;

		prefix_len = parse_prefix(text, शून्य, शून्य);
		अगर (prefix_len) अणु
			text_len -= prefix_len;
			स_हटाओ(text, text + prefix_len, text_len);
		पूर्ण
	पूर्ण

	वापस text_len;
पूर्ण

__म_लिखो(4, 0)
पूर्णांक vprपूर्णांकk_store(पूर्णांक facility, पूर्णांक level,
		  स्थिर काष्ठा dev_prपूर्णांकk_info *dev_info,
		  स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	स्थिर u32 caller_id = prपूर्णांकk_caller_id();
	काष्ठा prb_reserved_entry e;
	क्रमागत log_flags lflags = 0;
	काष्ठा prपूर्णांकk_record r;
	u16 trunc_msg_len = 0;
	अक्षर prefix_buf[8];
	u16 reserve_size;
	बहु_सूची args2;
	u16 text_len;
	u64 ts_nsec;

	/*
	 * Since the duration of prपूर्णांकk() can vary depending on the message
	 * and state of the ringbuffer, grab the बारtamp now so that it is
	 * बंद to the call of prपूर्णांकk(). This provides a more deterministic
	 * बारtamp with respect to the caller.
	 */
	ts_nsec = local_घड़ी();

	/*
	 * The प्र_लिखो needs to come first since the syslog prefix might be
	 * passed in as a parameter. An extra byte must be reserved so that
	 * later the vscnम_लिखो() पूर्णांकo the reserved buffer has room क्रम the
	 * terminating '\0', which is not counted by vsnम_लिखो().
	 */
	va_copy(args2, args);
	reserve_size = vsnम_लिखो(&prefix_buf[0], माप(prefix_buf), fmt, args2) + 1;
	बहु_पूर्ण(args2);

	अगर (reserve_size > LOG_LINE_MAX)
		reserve_size = LOG_LINE_MAX;

	/* Extract log level or control flags. */
	अगर (facility == 0)
		parse_prefix(&prefix_buf[0], &level, &lflags);

	अगर (level == LOGLEVEL_DEFAULT)
		level = शेष_message_loglevel;

	अगर (dev_info)
		lflags |= LOG_NEWLINE;

	अगर (lflags & LOG_CONT) अणु
		prb_rec_init_wr(&r, reserve_size);
		अगर (prb_reserve_in_last(&e, prb, &r, caller_id, LOG_LINE_MAX)) अणु
			text_len = prपूर्णांकk_sprपूर्णांक(&r.text_buf[r.info->text_len], reserve_size,
						 facility, &lflags, fmt, args);
			r.info->text_len += text_len;

			अगर (lflags & LOG_NEWLINE) अणु
				r.info->flags |= LOG_NEWLINE;
				prb_final_commit(&e);
			पूर्ण अन्यथा अणु
				prb_commit(&e);
			पूर्ण

			वापस text_len;
		पूर्ण
	पूर्ण

	/*
	 * Explicitly initialize the record beक्रमe every prb_reserve() call.
	 * prb_reserve_in_last() and prb_reserve() purposely invalidate the
	 * काष्ठाure when they fail.
	 */
	prb_rec_init_wr(&r, reserve_size);
	अगर (!prb_reserve(&e, prb, &r)) अणु
		/* truncate the message अगर it is too दीर्घ क्रम empty buffer */
		truncate_msg(&reserve_size, &trunc_msg_len);

		prb_rec_init_wr(&r, reserve_size + trunc_msg_len);
		अगर (!prb_reserve(&e, prb, &r))
			वापस 0;
	पूर्ण

	/* fill message */
	text_len = prपूर्णांकk_sprपूर्णांक(&r.text_buf[0], reserve_size, facility, &lflags, fmt, args);
	अगर (trunc_msg_len)
		स_नकल(&r.text_buf[text_len], trunc_msg, trunc_msg_len);
	r.info->text_len = text_len + trunc_msg_len;
	r.info->facility = facility;
	r.info->level = level & 7;
	r.info->flags = lflags & 0x1f;
	r.info->ts_nsec = ts_nsec;
	r.info->caller_id = caller_id;
	अगर (dev_info)
		स_नकल(&r.info->dev_info, dev_info, माप(r.info->dev_info));

	/* A message without a trailing newline can be जारीd. */
	अगर (!(lflags & LOG_NEWLINE))
		prb_commit(&e);
	अन्यथा
		prb_final_commit(&e);

	वापस (text_len + trunc_msg_len);
पूर्ण

यंत्रlinkage पूर्णांक vprपूर्णांकk_emit(पूर्णांक facility, पूर्णांक level,
			    स्थिर काष्ठा dev_prपूर्णांकk_info *dev_info,
			    स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	पूर्णांक prपूर्णांकed_len;
	bool in_sched = false;
	अचिन्हित दीर्घ flags;

	/* Suppress unimportant messages after panic happens */
	अगर (unlikely(suppress_prपूर्णांकk))
		वापस 0;

	अगर (level == LOGLEVEL_SCHED) अणु
		level = LOGLEVEL_DEFAULT;
		in_sched = true;
	पूर्ण

	boot_delay_msec(level);
	prपूर्णांकk_delay();

	prपूर्णांकk_safe_enter_irqsave(flags);
	prपूर्णांकed_len = vprपूर्णांकk_store(facility, level, dev_info, fmt, args);
	prपूर्णांकk_safe_निकास_irqrestore(flags);

	/* If called from the scheduler, we can not call up(). */
	अगर (!in_sched) अणु
		/*
		 * Disable preemption to aव्योम being preempted जबतक holding
		 * console_sem which would prevent anyone from prपूर्णांकing to
		 * console
		 */
		preempt_disable();
		/*
		 * Try to acquire and then immediately release the console
		 * semaphore.  The release will prपूर्णांक out buffers and wake up
		 * /dev/kmsg and syslog() users.
		 */
		अगर (console_trylock_spinning())
			console_unlock();
		preempt_enable();
	पूर्ण

	wake_up_klogd();
	वापस prपूर्णांकed_len;
पूर्ण
EXPORT_SYMBOL(vprपूर्णांकk_emit);

पूर्णांक vprपूर्णांकk_शेष(स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	वापस vprपूर्णांकk_emit(0, LOGLEVEL_DEFAULT, शून्य, fmt, args);
पूर्ण
EXPORT_SYMBOL_GPL(vprपूर्णांकk_शेष);

/**
 * prपूर्णांकk - prपूर्णांक a kernel message
 * @fmt: क्रमmat string
 *
 * This is prपूर्णांकk(). It can be called from any context. We want it to work.
 *
 * We try to grab the console_lock. If we succeed, it's easy - we log the
 * output and call the console drivers.  If we fail to get the semaphore, we
 * place the output पूर्णांकo the log buffer and वापस. The current holder of
 * the console_sem will notice the new output in console_unlock(); and will
 * send it to the consoles beक्रमe releasing the lock.
 *
 * One effect of this deferred prपूर्णांकing is that code which calls prपूर्णांकk() and
 * then changes console_loglevel may अवरोध. This is because console_loglevel
 * is inspected when the actual prपूर्णांकing occurs.
 *
 * See also:
 * म_लिखो(3)
 *
 * See the vsnम_लिखो() करोcumentation क्रम क्रमmat string extensions over C99.
 */
यंत्रlinkage __visible पूर्णांक prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक r;

	बहु_शुरू(args, fmt);
	r = vprपूर्णांकk(fmt, args);
	बहु_पूर्ण(args);

	वापस r;
पूर्ण
EXPORT_SYMBOL(prपूर्णांकk);

#अन्यथा /* CONFIG_PRINTK */

#घोषणा CONSOLE_LOG_MAX		0
#घोषणा prपूर्णांकk_समय		false

#घोषणा prb_पढ़ो_valid(rb, seq, r)	false
#घोषणा prb_first_valid_seq(rb)		0

अटल u64 syslog_seq;
अटल u64 console_seq;
अटल u64 exclusive_console_stop_seq;
अटल अचिन्हित दीर्घ console_dropped;

अटल माप_प्रकार record_prपूर्णांक_text(स्थिर काष्ठा prपूर्णांकk_record *r,
				bool syslog, bool समय)
अणु
	वापस 0;
पूर्ण
अटल sमाप_प्रकार info_prपूर्णांक_ext_header(अक्षर *buf, माप_प्रकार size,
				     काष्ठा prपूर्णांकk_info *info)
अणु
	वापस 0;
पूर्ण
अटल sमाप_प्रकार msg_prपूर्णांक_ext_body(अक्षर *buf, माप_प्रकार size,
				  अक्षर *text, माप_प्रकार text_len,
				  काष्ठा dev_prपूर्णांकk_info *dev_info) अणु वापस 0; पूर्ण
अटल व्योम console_lock_spinning_enable(व्योम) अणु पूर्ण
अटल पूर्णांक console_lock_spinning_disable_and_check(व्योम) अणु वापस 0; पूर्ण
अटल व्योम call_console_drivers(स्थिर अक्षर *ext_text, माप_प्रकार ext_len,
				 स्थिर अक्षर *text, माप_प्रकार len) अणुपूर्ण
अटल bool suppress_message_prपूर्णांकing(पूर्णांक level) अणु वापस false; पूर्ण

#पूर्ण_अगर /* CONFIG_PRINTK */

#अगर_घोषित CONFIG_EARLY_PRINTK
काष्ठा console *early_console;

यंत्रlinkage __visible व्योम early_prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	अक्षर buf[512];
	पूर्णांक n;

	अगर (!early_console)
		वापस;

	बहु_शुरू(ap, fmt);
	n = vscnम_लिखो(buf, माप(buf), fmt, ap);
	बहु_पूर्ण(ap);

	early_console->ग_लिखो(early_console, buf, n);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __add_preferred_console(अक्षर *name, पूर्णांक idx, अक्षर *options,
				   अक्षर *brl_options, bool user_specअगरied)
अणु
	काष्ठा console_cmdline *c;
	पूर्णांक i;

	/*
	 *	See अगर this tty is not yet रेजिस्टरed, and
	 *	अगर we have a slot मुक्त.
	 */
	क्रम (i = 0, c = console_cmdline;
	     i < MAX_CMDLINECONSOLES && c->name[0];
	     i++, c++) अणु
		अगर (म_भेद(c->name, name) == 0 && c->index == idx) अणु
			अगर (!brl_options)
				preferred_console = i;
			अगर (user_specअगरied)
				c->user_specअगरied = true;
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (i == MAX_CMDLINECONSOLES)
		वापस -E2BIG;
	अगर (!brl_options)
		preferred_console = i;
	strlcpy(c->name, name, माप(c->name));
	c->options = options;
	c->user_specअगरied = user_specअगरied;
	braille_set_options(c, brl_options);

	c->index = idx;
	वापस 0;
पूर्ण

अटल पूर्णांक __init console_msg_क्रमmat_setup(अक्षर *str)
अणु
	अगर (!म_भेद(str, "syslog"))
		console_msg_क्रमmat = MSG_FORMAT_SYSLOG;
	अगर (!म_भेद(str, "default"))
		console_msg_क्रमmat = MSG_FORMAT_DEFAULT;
	वापस 1;
पूर्ण
__setup("console_msg_format=", console_msg_क्रमmat_setup);

/*
 * Set up a console.  Called via करो_early_param() in init/मुख्य.c
 * क्रम each "console=" parameter in the boot command line.
 */
अटल पूर्णांक __init console_setup(अक्षर *str)
अणु
	अक्षर buf[माप(console_cmdline[0].name) + 4]; /* 4 क्रम "ttyS" */
	अक्षर *s, *options, *brl_options = शून्य;
	पूर्णांक idx;

	/*
	 * console="" or console=null have been suggested as a way to
	 * disable console output. Use ttynull that has been created
	 * क्रम exactly this purpose.
	 */
	अगर (str[0] == 0 || म_भेद(str, "null") == 0) अणु
		__add_preferred_console("ttynull", 0, शून्य, शून्य, true);
		वापस 1;
	पूर्ण

	अगर (_braille_console_setup(&str, &brl_options))
		वापस 1;

	/*
	 * Decode str पूर्णांकo name, index, options.
	 */
	अगर (str[0] >= '0' && str[0] <= '9') अणु
		म_नकल(buf, "ttyS");
		म_नकलन(buf + 4, str, माप(buf) - 5);
	पूर्ण अन्यथा अणु
		म_नकलन(buf, str, माप(buf) - 1);
	पूर्ण
	buf[माप(buf) - 1] = 0;
	options = म_अक्षर(str, ',');
	अगर (options)
		*(options++) = 0;
#अगर_घोषित __sparc__
	अगर (!म_भेद(str, "ttya"))
		म_नकल(buf, "ttyS0");
	अगर (!म_भेद(str, "ttyb"))
		म_नकल(buf, "ttyS1");
#पूर्ण_अगर
	क्रम (s = buf; *s; s++)
		अगर (है_अंक(*s) || *s == ',')
			अवरोध;
	idx = simple_म_से_अदीर्घ(s, शून्य, 10);
	*s = 0;

	__add_preferred_console(buf, idx, options, brl_options, true);
	console_set_on_cmdline = 1;
	वापस 1;
पूर्ण
__setup("console=", console_setup);

/**
 * add_preferred_console - add a device to the list of preferred consoles.
 * @name: device name
 * @idx: device index
 * @options: options क्रम this console
 *
 * The last preferred console added will be used क्रम kernel messages
 * and मानक_निवेश/out/err क्रम init.  Normally this is used by console_setup
 * above to handle user-supplied console arguments; however it can also
 * be used by arch-specअगरic code either to override the user or more
 * commonly to provide a शेष console (ie from PROM variables) when
 * the user has not supplied one.
 */
पूर्णांक add_preferred_console(अक्षर *name, पूर्णांक idx, अक्षर *options)
अणु
	वापस __add_preferred_console(name, idx, options, शून्य, false);
पूर्ण

bool console_suspend_enabled = true;
EXPORT_SYMBOL(console_suspend_enabled);

अटल पूर्णांक __init console_suspend_disable(अक्षर *str)
अणु
	console_suspend_enabled = false;
	वापस 1;
पूर्ण
__setup("no_console_suspend", console_suspend_disable);
module_param_named(console_suspend, console_suspend_enabled,
		bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(console_suspend, "suspend console during suspend"
	" and hibernate operations");

/**
 * suspend_console - suspend the console subप्रणाली
 *
 * This disables prपूर्णांकk() जबतक we go पूर्णांकo suspend states
 */
व्योम suspend_console(व्योम)
अणु
	अगर (!console_suspend_enabled)
		वापस;
	pr_info("Suspending console(s) (use no_console_suspend to debug)\n");
	console_lock();
	console_suspended = 1;
	up_console_sem();
पूर्ण

व्योम resume_console(व्योम)
अणु
	अगर (!console_suspend_enabled)
		वापस;
	करोwn_console_sem();
	console_suspended = 0;
	console_unlock();
पूर्ण

/**
 * console_cpu_notअगरy - prपूर्णांक deferred console messages after CPU hotplug
 * @cpu: unused
 *
 * If prपूर्णांकk() is called from a CPU that is not online yet, the messages
 * will be prपूर्णांकed on the console only अगर there are CON_ANYTIME consoles.
 * This function is called when a new CPU comes online (or fails to come
 * up) or goes offline.
 */
अटल पूर्णांक console_cpu_notअगरy(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!cpuhp_tasks_frozen) अणु
		/* If trylock fails, someone अन्यथा is करोing the prपूर्णांकing */
		अगर (console_trylock())
			console_unlock();
	पूर्ण
	वापस 0;
पूर्ण

/**
 * console_lock - lock the console प्रणाली क्रम exclusive use.
 *
 * Acquires a lock which guarantees that the caller has
 * exclusive access to the console प्रणाली and the console_drivers list.
 *
 * Can sleep, वापसs nothing.
 */
व्योम console_lock(व्योम)
अणु
	might_sleep();

	करोwn_console_sem();
	अगर (console_suspended)
		वापस;
	console_locked = 1;
	console_may_schedule = 1;
पूर्ण
EXPORT_SYMBOL(console_lock);

/**
 * console_trylock - try to lock the console प्रणाली क्रम exclusive use.
 *
 * Try to acquire a lock which guarantees that the caller has exclusive
 * access to the console प्रणाली and the console_drivers list.
 *
 * वापसs 1 on success, and 0 on failure to acquire the lock.
 */
पूर्णांक console_trylock(व्योम)
अणु
	अगर (करोwn_trylock_console_sem())
		वापस 0;
	अगर (console_suspended) अणु
		up_console_sem();
		वापस 0;
	पूर्ण
	console_locked = 1;
	console_may_schedule = 0;
	वापस 1;
पूर्ण
EXPORT_SYMBOL(console_trylock);

पूर्णांक is_console_locked(व्योम)
अणु
	वापस console_locked;
पूर्ण
EXPORT_SYMBOL(is_console_locked);

/*
 * Check अगर we have any console that is capable of prपूर्णांकing जबतक cpu is
 * booting or shutting करोwn. Requires console_sem.
 */
अटल पूर्णांक have_callable_console(व्योम)
अणु
	काष्ठा console *con;

	क्रम_each_console(con)
		अगर ((con->flags & CON_ENABLED) &&
				(con->flags & CON_ANYTIME))
			वापस 1;

	वापस 0;
पूर्ण

/*
 * Can we actually use the console at this समय on this cpu?
 *
 * Console drivers may assume that per-cpu resources have been allocated. So
 * unless they're explicitly marked as being able to cope (CON_ANYTIME) don't
 * call them until this CPU is officially up.
 */
अटल अंतरभूत पूर्णांक can_use_console(व्योम)
अणु
	वापस cpu_online(raw_smp_processor_id()) || have_callable_console();
पूर्ण

/**
 * console_unlock - unlock the console प्रणाली
 *
 * Releases the console_lock which the caller holds on the console प्रणाली
 * and the console driver list.
 *
 * While the console_lock was held, console output may have been buffered
 * by prपूर्णांकk().  If this is the हाल, console_unlock(); emits
 * the output prior to releasing the lock.
 *
 * If there is output रुकोing, we wake /dev/kmsg and syslog() users.
 *
 * console_unlock(); may be called from any context.
 */
व्योम console_unlock(व्योम)
अणु
	अटल अक्षर ext_text[CONSOLE_EXT_LOG_MAX];
	अटल अक्षर text[CONSOLE_LOG_MAX];
	अचिन्हित दीर्घ flags;
	bool करो_cond_resched, retry;
	काष्ठा prपूर्णांकk_info info;
	काष्ठा prपूर्णांकk_record r;

	अगर (console_suspended) अणु
		up_console_sem();
		वापस;
	पूर्ण

	prb_rec_init_rd(&r, &info, text, माप(text));

	/*
	 * Console drivers are called with पूर्णांकerrupts disabled, so
	 * @console_may_schedule should be cleared beक्रमe; however, we may
	 * end up dumping a lot of lines, क्रम example, अगर called from
	 * console registration path, and should invoke cond_resched()
	 * between lines अगर allowable.  Not करोing so can cause a very दीर्घ
	 * scheduling stall on a slow console leading to RCU stall and
	 * softlockup warnings which exacerbate the issue with more
	 * messages practically incapacitating the प्रणाली.
	 *
	 * console_trylock() is not able to detect the preemptive
	 * context reliably. Thereक्रमe the value must be stored beक्रमe
	 * and cleared after the "again" जाओ label.
	 */
	करो_cond_resched = console_may_schedule;
again:
	console_may_schedule = 0;

	/*
	 * We released the console_sem lock, so we need to recheck अगर
	 * cpu is online and (अगर not) is there at least one CON_ANYTIME
	 * console.
	 */
	अगर (!can_use_console()) अणु
		console_locked = 0;
		up_console_sem();
		वापस;
	पूर्ण

	क्रम (;;) अणु
		माप_प्रकार ext_len = 0;
		माप_प्रकार len;

		prपूर्णांकk_safe_enter_irqsave(flags);
skip:
		अगर (!prb_पढ़ो_valid(prb, console_seq, &r))
			अवरोध;

		अगर (console_seq != r.info->seq) अणु
			console_dropped += r.info->seq - console_seq;
			console_seq = r.info->seq;
		पूर्ण

		अगर (suppress_message_prपूर्णांकing(r.info->level)) अणु
			/*
			 * Skip record we have buffered and alपढ़ोy prपूर्णांकed
			 * directly to the console when we received it, and
			 * record that has level above the console loglevel.
			 */
			console_seq++;
			जाओ skip;
		पूर्ण

		/* Output to all consoles once old messages replayed. */
		अगर (unlikely(exclusive_console &&
			     console_seq >= exclusive_console_stop_seq)) अणु
			exclusive_console = शून्य;
		पूर्ण

		/*
		 * Handle extended console text first because later
		 * record_prपूर्णांक_text() will modअगरy the record buffer in-place.
		 */
		अगर (nr_ext_console_drivers) अणु
			ext_len = info_prपूर्णांक_ext_header(ext_text,
						माप(ext_text),
						r.info);
			ext_len += msg_prपूर्णांक_ext_body(ext_text + ext_len,
						माप(ext_text) - ext_len,
						&r.text_buf[0],
						r.info->text_len,
						&r.info->dev_info);
		पूर्ण
		len = record_prपूर्णांक_text(&r,
				console_msg_क्रमmat & MSG_FORMAT_SYSLOG,
				prपूर्णांकk_समय);
		console_seq++;

		/*
		 * While actively prपूर्णांकing out messages, अगर another prपूर्णांकk()
		 * were to occur on another CPU, it may रुको क्रम this one to
		 * finish. This task can not be preempted अगर there is a
		 * रुकोer रुकोing to take over.
		 */
		console_lock_spinning_enable();

		stop_critical_timings();	/* करोn't trace prपूर्णांक latency */
		call_console_drivers(ext_text, ext_len, text, len);
		start_critical_timings();

		अगर (console_lock_spinning_disable_and_check()) अणु
			prपूर्णांकk_safe_निकास_irqrestore(flags);
			वापस;
		पूर्ण

		prपूर्णांकk_safe_निकास_irqrestore(flags);

		अगर (करो_cond_resched)
			cond_resched();
	पूर्ण

	console_locked = 0;

	up_console_sem();

	/*
	 * Someone could have filled up the buffer again, so re-check अगर there's
	 * something to flush. In हाल we cannot trylock the console_sem again,
	 * there's a new owner and the console_unlock() from them will करो the
	 * flush, no worries.
	 */
	retry = prb_पढ़ो_valid(prb, console_seq, शून्य);
	prपूर्णांकk_safe_निकास_irqrestore(flags);

	अगर (retry && console_trylock())
		जाओ again;
पूर्ण
EXPORT_SYMBOL(console_unlock);

/**
 * console_conditional_schedule - yield the CPU अगर required
 *
 * If the console code is currently allowed to sleep, and
 * अगर this CPU should yield the CPU to another task, करो
 * so here.
 *
 * Must be called within console_lock();.
 */
व्योम __sched console_conditional_schedule(व्योम)
अणु
	अगर (console_may_schedule)
		cond_resched();
पूर्ण
EXPORT_SYMBOL(console_conditional_schedule);

व्योम console_unblank(व्योम)
अणु
	काष्ठा console *c;

	/*
	 * console_unblank can no दीर्घer be called in पूर्णांकerrupt context unless
	 * oops_in_progress is set to 1..
	 */
	अगर (oops_in_progress) अणु
		अगर (करोwn_trylock_console_sem() != 0)
			वापस;
	पूर्ण अन्यथा
		console_lock();

	console_locked = 1;
	console_may_schedule = 0;
	क्रम_each_console(c)
		अगर ((c->flags & CON_ENABLED) && c->unblank)
			c->unblank();
	console_unlock();
पूर्ण

/**
 * console_flush_on_panic - flush console content on panic
 * @mode: flush all messages in buffer or just the pending ones
 *
 * Immediately output all pending messages no matter what.
 */
व्योम console_flush_on_panic(क्रमागत con_flush_mode mode)
अणु
	/*
	 * If someone अन्यथा is holding the console lock, trylock will fail
	 * and may_schedule may be set.  Ignore and proceed to unlock so
	 * that messages are flushed out.  As this can be called from any
	 * context and we करोn't want to get preempted जबतक flushing,
	 * ensure may_schedule is cleared.
	 */
	console_trylock();
	console_may_schedule = 0;

	अगर (mode == CONSOLE_REPLAY_ALL) अणु
		अचिन्हित दीर्घ flags;

		prपूर्णांकk_safe_enter_irqsave(flags);
		console_seq = prb_first_valid_seq(prb);
		prपूर्णांकk_safe_निकास_irqrestore(flags);
	पूर्ण
	console_unlock();
पूर्ण

/*
 * Return the console tty driver काष्ठाure and its associated index
 */
काष्ठा tty_driver *console_device(पूर्णांक *index)
अणु
	काष्ठा console *c;
	काष्ठा tty_driver *driver = शून्य;

	console_lock();
	क्रम_each_console(c) अणु
		अगर (!c->device)
			जारी;
		driver = c->device(c, index);
		अगर (driver)
			अवरोध;
	पूर्ण
	console_unlock();
	वापस driver;
पूर्ण

/*
 * Prevent further output on the passed console device so that (क्रम example)
 * serial drivers can disable console output beक्रमe suspending a port, and can
 * re-enable output afterwards.
 */
व्योम console_stop(काष्ठा console *console)
अणु
	console_lock();
	console->flags &= ~CON_ENABLED;
	console_unlock();
पूर्ण
EXPORT_SYMBOL(console_stop);

व्योम console_start(काष्ठा console *console)
अणु
	console_lock();
	console->flags |= CON_ENABLED;
	console_unlock();
पूर्ण
EXPORT_SYMBOL(console_start);

अटल पूर्णांक __पढ़ो_mostly keep_bootcon;

अटल पूर्णांक __init keep_bootcon_setup(अक्षर *str)
अणु
	keep_bootcon = 1;
	pr_info("debug: skip boot console de-registration.\n");

	वापस 0;
पूर्ण

early_param("keep_bootcon", keep_bootcon_setup);

/*
 * This is called by रेजिस्टर_console() to try to match
 * the newly रेजिस्टरed console with any of the ones selected
 * by either the command line or add_preferred_console() and
 * setup/enable it.
 *
 * Care need to be taken with consoles that are अटलally
 * enabled such as netconsole
 */
अटल पूर्णांक try_enable_new_console(काष्ठा console *newcon, bool user_specअगरied)
अणु
	काष्ठा console_cmdline *c;
	पूर्णांक i, err;

	क्रम (i = 0, c = console_cmdline;
	     i < MAX_CMDLINECONSOLES && c->name[0];
	     i++, c++) अणु
		अगर (c->user_specअगरied != user_specअगरied)
			जारी;
		अगर (!newcon->match ||
		    newcon->match(newcon, c->name, c->index, c->options) != 0) अणु
			/* शेष matching */
			BUILD_BUG_ON(माप(c->name) != माप(newcon->name));
			अगर (म_भेद(c->name, newcon->name) != 0)
				जारी;
			अगर (newcon->index >= 0 &&
			    newcon->index != c->index)
				जारी;
			अगर (newcon->index < 0)
				newcon->index = c->index;

			अगर (_braille_रेजिस्टर_console(newcon, c))
				वापस 0;

			अगर (newcon->setup &&
			    (err = newcon->setup(newcon, c->options)) != 0)
				वापस err;
		पूर्ण
		newcon->flags |= CON_ENABLED;
		अगर (i == preferred_console) अणु
			newcon->flags |= CON_CONSDEV;
			has_preferred_console = true;
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * Some consoles, such as pstore and netconsole, can be enabled even
	 * without matching. Accept the pre-enabled consoles only when match()
	 * and setup() had a chance to be called.
	 */
	अगर (newcon->flags & CON_ENABLED && c->user_specअगरied ==	user_specअगरied)
		वापस 0;

	वापस -ENOENT;
पूर्ण

/*
 * The console driver calls this routine during kernel initialization
 * to रेजिस्टर the console prपूर्णांकing procedure with prपूर्णांकk() and to
 * prपूर्णांक any messages that were prपूर्णांकed by the kernel beक्रमe the
 * console driver was initialized.
 *
 * This can happen pretty early during the boot process (because of
 * early_prपूर्णांकk) - someबार beक्रमe setup_arch() completes - be careful
 * of what kernel features are used - they may not be initialised yet.
 *
 * There are two types of consoles - bootconsoles (early_prपूर्णांकk) and
 * "real" consoles (everything which is not a bootconsole) which are
 * handled dअगरferently.
 *  - Any number of bootconsoles can be रेजिस्टरed at any समय.
 *  - As soon as a "real" console is रेजिस्टरed, all bootconsoles
 *    will be unरेजिस्टरed स्वतःmatically.
 *  - Once a "real" console is रेजिस्टरed, any attempt to रेजिस्टर a
 *    bootconsoles will be rejected
 */
व्योम रेजिस्टर_console(काष्ठा console *newcon)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा console *bcon = शून्य;
	पूर्णांक err;

	क्रम_each_console(bcon) अणु
		अगर (WARN(bcon == newcon, "console '%s%d' already registered\n",
					 bcon->name, bcon->index))
			वापस;
	पूर्ण

	/*
	 * beक्रमe we रेजिस्टर a new CON_BOOT console, make sure we करोn't
	 * alपढ़ोy have a valid console
	 */
	अगर (newcon->flags & CON_BOOT) अणु
		क्रम_each_console(bcon) अणु
			अगर (!(bcon->flags & CON_BOOT)) अणु
				pr_info("Too late to register bootconsole %s%d\n",
					newcon->name, newcon->index);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (console_drivers && console_drivers->flags & CON_BOOT)
		bcon = console_drivers;

	अगर (!has_preferred_console || bcon || !console_drivers)
		has_preferred_console = preferred_console >= 0;

	/*
	 *	See अगर we want to use this console driver. If we
	 *	didn't select a console we take the first one
	 *	that रेजिस्टरs here.
	 */
	अगर (!has_preferred_console) अणु
		अगर (newcon->index < 0)
			newcon->index = 0;
		अगर (newcon->setup == शून्य ||
		    newcon->setup(newcon, शून्य) == 0) अणु
			newcon->flags |= CON_ENABLED;
			अगर (newcon->device) अणु
				newcon->flags |= CON_CONSDEV;
				has_preferred_console = true;
			पूर्ण
		पूर्ण
	पूर्ण

	/* See अगर this console matches one we selected on the command line */
	err = try_enable_new_console(newcon, true);

	/* If not, try to match against the platक्रमm शेष(s) */
	अगर (err == -ENOENT)
		err = try_enable_new_console(newcon, false);

	/* prपूर्णांकk() messages are not prपूर्णांकed to the Braille console. */
	अगर (err || newcon->flags & CON_BRL)
		वापस;

	/*
	 * If we have a bootconsole, and are चयनing to a real console,
	 * करोn't prपूर्णांक everything out again, since when the boot console, and
	 * the real console are the same physical device, it's annoying to
	 * see the beginning boot messages twice
	 */
	अगर (bcon && ((newcon->flags & (CON_CONSDEV | CON_BOOT)) == CON_CONSDEV))
		newcon->flags &= ~CON_PRINTBUFFER;

	/*
	 *	Put this console in the list - keep the
	 *	preferred driver at the head of the list.
	 */
	console_lock();
	अगर ((newcon->flags & CON_CONSDEV) || console_drivers == शून्य) अणु
		newcon->next = console_drivers;
		console_drivers = newcon;
		अगर (newcon->next)
			newcon->next->flags &= ~CON_CONSDEV;
		/* Ensure this flag is always set क्रम the head of the list */
		newcon->flags |= CON_CONSDEV;
	पूर्ण अन्यथा अणु
		newcon->next = console_drivers->next;
		console_drivers->next = newcon;
	पूर्ण

	अगर (newcon->flags & CON_EXTENDED)
		nr_ext_console_drivers++;

	अगर (newcon->flags & CON_PRINTBUFFER) अणु
		/*
		 * console_unlock(); will prपूर्णांक out the buffered messages
		 * क्रम us.
		 *
		 * We're about to replay the log buffer.  Only करो this to the
		 * just-रेजिस्टरed console to aव्योम excessive message spam to
		 * the alपढ़ोy-रेजिस्टरed consoles.
		 *
		 * Set exclusive_console with disabled पूर्णांकerrupts to reduce
		 * race winकरोw with eventual console_flush_on_panic() that
		 * ignores console_lock.
		 */
		exclusive_console = newcon;
		exclusive_console_stop_seq = console_seq;

		/* Get a consistent copy of @syslog_seq. */
		raw_spin_lock_irqsave(&syslog_lock, flags);
		console_seq = syslog_seq;
		raw_spin_unlock_irqrestore(&syslog_lock, flags);
	पूर्ण
	console_unlock();
	console_sysfs_notअगरy();

	/*
	 * By unरेजिस्टरing the bootconsoles after we enable the real console
	 * we get the "console xxx enabled" message on all the consoles -
	 * boot consoles, real consoles, etc - this is to ensure that end
	 * users know there might be something in the kernel's log buffer that
	 * went to the bootconsole (that they करो not see on the real console)
	 */
	pr_info("%sconsole [%s%d] enabled\n",
		(newcon->flags & CON_BOOT) ? "boot" : "" ,
		newcon->name, newcon->index);
	अगर (bcon &&
	    ((newcon->flags & (CON_CONSDEV | CON_BOOT)) == CON_CONSDEV) &&
	    !keep_bootcon) अणु
		/* We need to iterate through all boot consoles, to make
		 * sure we prपूर्णांक everything out, beक्रमe we unरेजिस्टर them.
		 */
		क्रम_each_console(bcon)
			अगर (bcon->flags & CON_BOOT)
				unरेजिस्टर_console(bcon);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_console);

पूर्णांक unरेजिस्टर_console(काष्ठा console *console)
अणु
	काष्ठा console *con;
	पूर्णांक res;

	pr_info("%sconsole [%s%d] disabled\n",
		(console->flags & CON_BOOT) ? "boot" : "" ,
		console->name, console->index);

	res = _braille_unरेजिस्टर_console(console);
	अगर (res < 0)
		वापस res;
	अगर (res > 0)
		वापस 0;

	res = -ENODEV;
	console_lock();
	अगर (console_drivers == console) अणु
		console_drivers=console->next;
		res = 0;
	पूर्ण अन्यथा अणु
		क्रम_each_console(con) अणु
			अगर (con->next == console) अणु
				con->next = console->next;
				res = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (res)
		जाओ out_disable_unlock;

	अगर (console->flags & CON_EXTENDED)
		nr_ext_console_drivers--;

	/*
	 * If this isn't the last console and it has CON_CONSDEV set, we
	 * need to set it on the next preferred console.
	 */
	अगर (console_drivers != शून्य && console->flags & CON_CONSDEV)
		console_drivers->flags |= CON_CONSDEV;

	console->flags &= ~CON_ENABLED;
	console_unlock();
	console_sysfs_notअगरy();

	अगर (console->निकास)
		res = console->निकास(console);

	वापस res;

out_disable_unlock:
	console->flags &= ~CON_ENABLED;
	console_unlock();

	वापस res;
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_console);

/*
 * Initialize the console device. This is called *early*, so
 * we can't necessarily depend on lots of kernel help here.
 * Just करो some early initializations, and करो the complex setup
 * later.
 */
व्योम __init console_init(व्योम)
अणु
	पूर्णांक ret;
	initcall_t call;
	initcall_entry_t *ce;

	/* Setup the शेष TTY line discipline. */
	n_tty_init();

	/*
	 * set up the console device so that later boot sequences can
	 * inक्रमm about problems etc..
	 */
	ce = __con_initcall_start;
	trace_initcall_level("console");
	जबतक (ce < __con_initcall_end) अणु
		call = initcall_from_entry(ce);
		trace_initcall_start(call);
		ret = call();
		trace_initcall_finish(call, ret);
		ce++;
	पूर्ण
पूर्ण

/*
 * Some boot consoles access data that is in the init section and which will
 * be discarded after the initcalls have been run. To make sure that no code
 * will access this data, unरेजिस्टर the boot consoles in a late initcall.
 *
 * If क्रम some reason, such as deferred probe or the driver being a loadable
 * module, the real console hasn't रेजिस्टरed yet at this poपूर्णांक, there will
 * be a brief पूर्णांकerval in which no messages are logged to the console, which
 * makes it dअगरficult to diagnose problems that occur during this समय.
 *
 * To mitigate this problem somewhat, only unरेजिस्टर consoles whose memory
 * पूर्णांकersects with the init section. Note that all other boot consoles will
 * get unरेजिस्टरed when the real preferred console is रेजिस्टरed.
 */
अटल पूर्णांक __init prपूर्णांकk_late_init(व्योम)
अणु
	काष्ठा console *con;
	पूर्णांक ret;

	क्रम_each_console(con) अणु
		अगर (!(con->flags & CON_BOOT))
			जारी;

		/* Check addresses that might be used क्रम enabled consoles. */
		अगर (init_section_पूर्णांकersects(con, माप(*con)) ||
		    init_section_contains(con->ग_लिखो, 0) ||
		    init_section_contains(con->पढ़ो, 0) ||
		    init_section_contains(con->device, 0) ||
		    init_section_contains(con->unblank, 0) ||
		    init_section_contains(con->data, 0)) अणु
			/*
			 * Please, consider moving the reported consoles out
			 * of the init section.
			 */
			pr_warn("bootconsole [%s%d] uses init memory and must be disabled even before the real one is ready\n",
				con->name, con->index);
			unरेजिस्टर_console(con);
		पूर्ण
	पूर्ण
	ret = cpuhp_setup_state_nocalls(CPUHP_PRINTK_DEAD, "printk:dead", शून्य,
					console_cpu_notअगरy);
	WARN_ON(ret < 0);
	ret = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN, "printk:online",
					console_cpu_notअगरy, शून्य);
	WARN_ON(ret < 0);
	वापस 0;
पूर्ण
late_initcall(prपूर्णांकk_late_init);

#अगर defined CONFIG_PRINTK
/*
 * Delayed prपूर्णांकk version, क्रम scheduler-पूर्णांकernal messages:
 */
#घोषणा PRINTK_PENDING_WAKEUP	0x01
#घोषणा PRINTK_PENDING_OUTPUT	0x02

अटल DEFINE_PER_CPU(पूर्णांक, prपूर्णांकk_pending);

अटल व्योम wake_up_klogd_work_func(काष्ठा irq_work *irq_work)
अणु
	पूर्णांक pending = __this_cpu_xchg(prपूर्णांकk_pending, 0);

	अगर (pending & PRINTK_PENDING_OUTPUT) अणु
		/* If trylock fails, someone अन्यथा is करोing the prपूर्णांकing */
		अगर (console_trylock())
			console_unlock();
	पूर्ण

	अगर (pending & PRINTK_PENDING_WAKEUP)
		wake_up_पूर्णांकerruptible(&log_रुको);
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा irq_work, wake_up_klogd_work) =
	IRQ_WORK_INIT_LAZY(wake_up_klogd_work_func);

व्योम wake_up_klogd(व्योम)
अणु
	अगर (!prपूर्णांकk_percpu_data_पढ़ोy())
		वापस;

	preempt_disable();
	अगर (रुकोqueue_active(&log_रुको)) अणु
		this_cpu_or(prपूर्णांकk_pending, PRINTK_PENDING_WAKEUP);
		irq_work_queue(this_cpu_ptr(&wake_up_klogd_work));
	पूर्ण
	preempt_enable();
पूर्ण

व्योम defer_console_output(व्योम)
अणु
	अगर (!prपूर्णांकk_percpu_data_पढ़ोy())
		वापस;

	preempt_disable();
	__this_cpu_or(prपूर्णांकk_pending, PRINTK_PENDING_OUTPUT);
	irq_work_queue(this_cpu_ptr(&wake_up_klogd_work));
	preempt_enable();
पूर्ण

पूर्णांक vprपूर्णांकk_deferred(स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	पूर्णांक r;

	r = vprपूर्णांकk_emit(0, LOGLEVEL_SCHED, शून्य, fmt, args);
	defer_console_output();

	वापस r;
पूर्ण

पूर्णांक prपूर्णांकk_deferred(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक r;

	बहु_शुरू(args, fmt);
	r = vprपूर्णांकk_deferred(fmt, args);
	बहु_पूर्ण(args);

	वापस r;
पूर्ण

/*
 * prपूर्णांकk rate limiting, lअगरted from the networking subप्रणाली.
 *
 * This enक्रमces a rate limit: not more than 10 kernel messages
 * every 5s to make a denial-of-service attack impossible.
 */
DEFINE_RATELIMIT_STATE(prपूर्णांकk_ratelimit_state, 5 * HZ, 10);

पूर्णांक __prपूर्णांकk_ratelimit(स्थिर अक्षर *func)
अणु
	वापस ___ratelimit(&prपूर्णांकk_ratelimit_state, func);
पूर्ण
EXPORT_SYMBOL(__prपूर्णांकk_ratelimit);

/**
 * prपूर्णांकk_समयd_ratelimit - caller-controlled prपूर्णांकk ratelimiting
 * @caller_jअगरfies: poपूर्णांकer to caller's state
 * @पूर्णांकerval_msecs: minimum पूर्णांकerval between prपूर्णांकs
 *
 * prपूर्णांकk_समयd_ratelimit() वापसs true अगर more than @पूर्णांकerval_msecs
 * milliseconds have elapsed since the last समय prपूर्णांकk_समयd_ratelimit()
 * वापसed true.
 */
bool prपूर्णांकk_समयd_ratelimit(अचिन्हित दीर्घ *caller_jअगरfies,
			अचिन्हित पूर्णांक पूर्णांकerval_msecs)
अणु
	अचिन्हित दीर्घ elapsed = jअगरfies - *caller_jअगरfies;

	अगर (*caller_jअगरfies && elapsed <= msecs_to_jअगरfies(पूर्णांकerval_msecs))
		वापस false;

	*caller_jअगरfies = jअगरfies;
	वापस true;
पूर्ण
EXPORT_SYMBOL(prपूर्णांकk_समयd_ratelimit);

अटल DEFINE_SPINLOCK(dump_list_lock);
अटल LIST_HEAD(dump_list);

/**
 * kmsg_dump_रेजिस्टर - रेजिस्टर a kernel log dumper.
 * @dumper: poपूर्णांकer to the kmsg_dumper काष्ठाure
 *
 * Adds a kernel log dumper to the प्रणाली. The dump callback in the
 * काष्ठाure will be called when the kernel oopses or panics and must be
 * set. Returns zero on success and %-EINVAL or %-EBUSY otherwise.
 */
पूर्णांक kmsg_dump_रेजिस्टर(काष्ठा kmsg_dumper *dumper)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -EBUSY;

	/* The dump callback needs to be set */
	अगर (!dumper->dump)
		वापस -EINVAL;

	spin_lock_irqsave(&dump_list_lock, flags);
	/* Don't allow रेजिस्टरing multiple बार */
	अगर (!dumper->रेजिस्टरed) अणु
		dumper->रेजिस्टरed = 1;
		list_add_tail_rcu(&dumper->list, &dump_list);
		err = 0;
	पूर्ण
	spin_unlock_irqrestore(&dump_list_lock, flags);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(kmsg_dump_रेजिस्टर);

/**
 * kmsg_dump_unरेजिस्टर - unरेजिस्टर a kmsg dumper.
 * @dumper: poपूर्णांकer to the kmsg_dumper काष्ठाure
 *
 * Removes a dump device from the प्रणाली. Returns zero on success and
 * %-EINVAL otherwise.
 */
पूर्णांक kmsg_dump_unरेजिस्टर(काष्ठा kmsg_dumper *dumper)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -EINVAL;

	spin_lock_irqsave(&dump_list_lock, flags);
	अगर (dumper->रेजिस्टरed) अणु
		dumper->रेजिस्टरed = 0;
		list_del_rcu(&dumper->list);
		err = 0;
	पूर्ण
	spin_unlock_irqrestore(&dump_list_lock, flags);
	synchronize_rcu();

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(kmsg_dump_unरेजिस्टर);

अटल bool always_kmsg_dump;
module_param_named(always_kmsg_dump, always_kmsg_dump, bool, S_IRUGO | S_IWUSR);

स्थिर अक्षर *kmsg_dump_reason_str(क्रमागत kmsg_dump_reason reason)
अणु
	चयन (reason) अणु
	हाल KMSG_DUMP_PANIC:
		वापस "Panic";
	हाल KMSG_DUMP_OOPS:
		वापस "Oops";
	हाल KMSG_DUMP_EMERG:
		वापस "Emergency";
	हाल KMSG_DUMP_SHUTDOWN:
		वापस "Shutdown";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kmsg_dump_reason_str);

/**
 * kmsg_dump - dump kernel log to kernel message dumpers.
 * @reason: the reason (oops, panic etc) क्रम dumping
 *
 * Call each of the रेजिस्टरed dumper's dump() callback, which can
 * retrieve the kmsg records with kmsg_dump_get_line() or
 * kmsg_dump_get_buffer().
 */
व्योम kmsg_dump(क्रमागत kmsg_dump_reason reason)
अणु
	काष्ठा kmsg_dumper *dumper;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(dumper, &dump_list, list) अणु
		क्रमागत kmsg_dump_reason max_reason = dumper->max_reason;

		/*
		 * If client has not provided a specअगरic max_reason, शेष
		 * to KMSG_DUMP_OOPS, unless always_kmsg_dump was set.
		 */
		अगर (max_reason == KMSG_DUMP_UNDEF) अणु
			max_reason = always_kmsg_dump ? KMSG_DUMP_MAX :
							KMSG_DUMP_OOPS;
		पूर्ण
		अगर (reason > max_reason)
			जारी;

		/* invoke dumper which will iterate over records */
		dumper->dump(dumper, reason);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * kmsg_dump_get_line - retrieve one kmsg log line
 * @iter: kmsg dump iterator
 * @syslog: include the "<4>" prefixes
 * @line: buffer to copy the line to
 * @size: maximum size of the buffer
 * @len: length of line placed पूर्णांकo buffer
 *
 * Start at the beginning of the kmsg buffer, with the oldest kmsg
 * record, and copy one record पूर्णांकo the provided buffer.
 *
 * Consecutive calls will वापस the next available record moving
 * towards the end of the buffer with the youngest messages.
 *
 * A वापस value of FALSE indicates that there are no more records to
 * पढ़ो.
 */
bool kmsg_dump_get_line(काष्ठा kmsg_dump_iter *iter, bool syslog,
			अक्षर *line, माप_प्रकार size, माप_प्रकार *len)
अणु
	u64 min_seq = latched_seq_पढ़ो_nolock(&clear_seq);
	काष्ठा prपूर्णांकk_info info;
	अचिन्हित पूर्णांक line_count;
	काष्ठा prपूर्णांकk_record r;
	अचिन्हित दीर्घ flags;
	माप_प्रकार l = 0;
	bool ret = false;

	अगर (iter->cur_seq < min_seq)
		iter->cur_seq = min_seq;

	prपूर्णांकk_safe_enter_irqsave(flags);
	prb_rec_init_rd(&r, &info, line, size);

	/* Read text or count text lines? */
	अगर (line) अणु
		अगर (!prb_पढ़ो_valid(prb, iter->cur_seq, &r))
			जाओ out;
		l = record_prपूर्णांक_text(&r, syslog, prपूर्णांकk_समय);
	पूर्ण अन्यथा अणु
		अगर (!prb_पढ़ो_valid_info(prb, iter->cur_seq,
					 &info, &line_count)) अणु
			जाओ out;
		पूर्ण
		l = get_record_prपूर्णांक_text_size(&info, line_count, syslog,
					       prपूर्णांकk_समय);

	पूर्ण

	iter->cur_seq = r.info->seq + 1;
	ret = true;
out:
	prपूर्णांकk_safe_निकास_irqrestore(flags);
	अगर (len)
		*len = l;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kmsg_dump_get_line);

/**
 * kmsg_dump_get_buffer - copy kmsg log lines
 * @iter: kmsg dump iterator
 * @syslog: include the "<4>" prefixes
 * @buf: buffer to copy the line to
 * @size: maximum size of the buffer
 * @len_out: length of line placed पूर्णांकo buffer
 *
 * Start at the end of the kmsg buffer and fill the provided buffer
 * with as many of the *youngest* kmsg records that fit पूर्णांकo it.
 * If the buffer is large enough, all available kmsg records will be
 * copied with a single call.
 *
 * Consecutive calls will fill the buffer with the next block of
 * available older records, not including the earlier retrieved ones.
 *
 * A वापस value of FALSE indicates that there are no more records to
 * पढ़ो.
 */
bool kmsg_dump_get_buffer(काष्ठा kmsg_dump_iter *iter, bool syslog,
			  अक्षर *buf, माप_प्रकार size, माप_प्रकार *len_out)
अणु
	u64 min_seq = latched_seq_पढ़ो_nolock(&clear_seq);
	काष्ठा prपूर्णांकk_info info;
	काष्ठा prपूर्णांकk_record r;
	अचिन्हित दीर्घ flags;
	u64 seq;
	u64 next_seq;
	माप_प्रकार len = 0;
	bool ret = false;
	bool समय = prपूर्णांकk_समय;

	अगर (!buf || !size)
		जाओ out;

	अगर (iter->cur_seq < min_seq)
		iter->cur_seq = min_seq;

	prपूर्णांकk_safe_enter_irqsave(flags);
	अगर (prb_पढ़ो_valid_info(prb, iter->cur_seq, &info, शून्य)) अणु
		अगर (info.seq != iter->cur_seq) अणु
			/* messages are gone, move to first available one */
			iter->cur_seq = info.seq;
		पूर्ण
	पूर्ण

	/* last entry */
	अगर (iter->cur_seq >= iter->next_seq) अणु
		prपूर्णांकk_safe_निकास_irqrestore(flags);
		जाओ out;
	पूर्ण

	/*
	 * Find first record that fits, including all following records,
	 * पूर्णांकo the user-provided buffer क्रम this dump. Pass in size-1
	 * because this function (by way of record_prपूर्णांक_text()) will
	 * not ग_लिखो more than size-1 bytes of text पूर्णांकo @buf.
	 */
	seq = find_first_fitting_seq(iter->cur_seq, iter->next_seq,
				     size - 1, syslog, समय);

	/*
	 * Next kmsg_dump_get_buffer() invocation will dump block of
	 * older records stored right beक्रमe this one.
	 */
	next_seq = seq;

	prb_rec_init_rd(&r, &info, buf, size);

	len = 0;
	prb_क्रम_each_record(seq, prb, seq, &r) अणु
		अगर (r.info->seq >= iter->next_seq)
			अवरोध;

		len += record_prपूर्णांक_text(&r, syslog, समय);

		/* Adjust record to store to reमुख्यing buffer space. */
		prb_rec_init_rd(&r, &info, buf + len, size - len);
	पूर्ण

	iter->next_seq = next_seq;
	ret = true;
	prपूर्णांकk_safe_निकास_irqrestore(flags);
out:
	अगर (len_out)
		*len_out = len;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kmsg_dump_get_buffer);

/**
 * kmsg_dump_शुरुआत - reset the iterator
 * @iter: kmsg dump iterator
 *
 * Reset the dumper's iterator so that kmsg_dump_get_line() and
 * kmsg_dump_get_buffer() can be called again and used multiple
 * बार within the same dumper.dump() callback.
 */
व्योम kmsg_dump_शुरुआत(काष्ठा kmsg_dump_iter *iter)
अणु
	अचिन्हित दीर्घ flags;

	prपूर्णांकk_safe_enter_irqsave(flags);
	iter->cur_seq = latched_seq_पढ़ो_nolock(&clear_seq);
	iter->next_seq = prb_next_seq(prb);
	prपूर्णांकk_safe_निकास_irqrestore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(kmsg_dump_शुरुआत);

#पूर्ण_अगर
