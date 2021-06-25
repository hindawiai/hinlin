<शैली गुरु>
#अगर_अघोषित _KDB_H
#घोषणा _KDB_H

/*
 * Kernel Debugger Architecture Independent Global Headers
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2000-2007 Silicon Graphics, Inc.  All Rights Reserved.
 * Copyright (C) 2000 Stephane Eranian <eranian@hpl.hp.com>
 * Copyright (C) 2009 Jason Wessel <jason.wessel@windriver.com>
 */

/* Shअगरted versions of the command enable bits are be used अगर the command
 * has no arguments (see kdb_check_flags). This allows commands, such as
 * go, to have dअगरferent permissions depending upon whether it is called
 * with an argument.
 */
#घोषणा KDB_ENABLE_NO_ARGS_SHIFT 10

प्रकार क्रमागत अणु
	KDB_ENABLE_ALL = (1 << 0), /* Enable everything */
	KDB_ENABLE_MEM_READ = (1 << 1),
	KDB_ENABLE_MEM_WRITE = (1 << 2),
	KDB_ENABLE_REG_READ = (1 << 3),
	KDB_ENABLE_REG_WRITE = (1 << 4),
	KDB_ENABLE_INSPECT = (1 << 5),
	KDB_ENABLE_FLOW_CTRL = (1 << 6),
	KDB_ENABLE_SIGNAL = (1 << 7),
	KDB_ENABLE_REBOOT = (1 << 8),
	/* User exposed values stop here, all reमुख्यing flags are
	 * exclusively used to describe a commands behaviour.
	 */

	KDB_ENABLE_ALWAYS_SAFE = (1 << 9),
	KDB_ENABLE_MASK = (1 << KDB_ENABLE_NO_ARGS_SHIFT) - 1,

	KDB_ENABLE_ALL_NO_ARGS = KDB_ENABLE_ALL << KDB_ENABLE_NO_ARGS_SHIFT,
	KDB_ENABLE_MEM_READ_NO_ARGS = KDB_ENABLE_MEM_READ
				      << KDB_ENABLE_NO_ARGS_SHIFT,
	KDB_ENABLE_MEM_WRITE_NO_ARGS = KDB_ENABLE_MEM_WRITE
				       << KDB_ENABLE_NO_ARGS_SHIFT,
	KDB_ENABLE_REG_READ_NO_ARGS = KDB_ENABLE_REG_READ
				      << KDB_ENABLE_NO_ARGS_SHIFT,
	KDB_ENABLE_REG_WRITE_NO_ARGS = KDB_ENABLE_REG_WRITE
				       << KDB_ENABLE_NO_ARGS_SHIFT,
	KDB_ENABLE_INSPECT_NO_ARGS = KDB_ENABLE_INSPECT
				     << KDB_ENABLE_NO_ARGS_SHIFT,
	KDB_ENABLE_FLOW_CTRL_NO_ARGS = KDB_ENABLE_FLOW_CTRL
				       << KDB_ENABLE_NO_ARGS_SHIFT,
	KDB_ENABLE_SIGNAL_NO_ARGS = KDB_ENABLE_SIGNAL
				    << KDB_ENABLE_NO_ARGS_SHIFT,
	KDB_ENABLE_REBOOT_NO_ARGS = KDB_ENABLE_REBOOT
				    << KDB_ENABLE_NO_ARGS_SHIFT,
	KDB_ENABLE_ALWAYS_SAFE_NO_ARGS = KDB_ENABLE_ALWAYS_SAFE
					 << KDB_ENABLE_NO_ARGS_SHIFT,
	KDB_ENABLE_MASK_NO_ARGS = KDB_ENABLE_MASK << KDB_ENABLE_NO_ARGS_SHIFT,

	KDB_REPEAT_NO_ARGS = 0x40000000, /* Repeat the command w/o arguments */
	KDB_REPEAT_WITH_ARGS = 0x80000000, /* Repeat the command with args */
पूर्ण kdb_cmdflags_t;

प्रकार पूर्णांक (*kdb_func_t)(पूर्णांक, स्थिर अक्षर **);

#अगर_घोषित	CONFIG_KGDB_KDB
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/atomic.h>

#घोषणा KDB_POLL_FUNC_MAX	5
बाह्य पूर्णांक kdb_poll_idx;

/*
 * kdb_initial_cpu is initialized to -1, and is set to the cpu
 * number whenever the kernel debugger is entered.
 */
बाह्य पूर्णांक kdb_initial_cpu;

/* Types and messages used क्रम dynamically added kdb shell commands */

#घोषणा KDB_MAXARGS    16 /* Maximum number of arguments to a function  */

/* KDB वापस codes from a command or पूर्णांकernal kdb function */
#घोषणा KDB_NOTFOUND	(-1)
#घोषणा KDB_ARGCOUNT	(-2)
#घोषणा KDB_BADWIDTH	(-3)
#घोषणा KDB_BADRADIX	(-4)
#घोषणा KDB_NOTENV	(-5)
#घोषणा KDB_NOENVVALUE	(-6)
#घोषणा KDB_NOTIMP	(-7)
#घोषणा KDB_ENVFULL	(-8)
#घोषणा KDB_ENVBUFFULL	(-9)
#घोषणा KDB_TOOMANYBPT	(-10)
#घोषणा KDB_TOOMANYDBREGS (-11)
#घोषणा KDB_DUPBPT	(-12)
#घोषणा KDB_BPTNOTFOUND	(-13)
#घोषणा KDB_BADMODE	(-14)
#घोषणा KDB_BADINT	(-15)
#घोषणा KDB_INVADDRFMT  (-16)
#घोषणा KDB_BADREG      (-17)
#घोषणा KDB_BADCPUNUM   (-18)
#घोषणा KDB_BADLENGTH	(-19)
#घोषणा KDB_NOBP	(-20)
#घोषणा KDB_BADADDR	(-21)
#घोषणा KDB_NOPERM	(-22)

/*
 * kdb_diemsg
 *
 *	Contains a poपूर्णांकer to the last string supplied to the
 *	kernel 'die' panic function.
 */
बाह्य स्थिर अक्षर *kdb_diemsg;

#घोषणा KDB_FLAG_EARLYKDB	(1 << 0) /* set from boot parameter kdb=early */
#घोषणा KDB_FLAG_CATASTROPHIC	(1 << 1) /* A catastrophic event has occurred */
#घोषणा KDB_FLAG_CMD_INTERRUPT	(1 << 2) /* Previous command was पूर्णांकerrupted */
#घोषणा KDB_FLAG_NOIPI		(1 << 3) /* Do not send IPIs */
#घोषणा KDB_FLAG_NO_CONSOLE	(1 << 5) /* No console is available,
					  * kdb is disabled */
#घोषणा KDB_FLAG_NO_VT_CONSOLE	(1 << 6) /* No VT console is available, करो
					  * not use keyboard */
#घोषणा KDB_FLAG_NO_I8042	(1 << 7) /* No i8042 chip is available, करो
					  * not use keyboard */

बाह्य अचिन्हित पूर्णांक kdb_flags;	/* Global flags, see kdb_state क्रम per cpu state */

बाह्य व्योम kdb_save_flags(व्योम);
बाह्य व्योम kdb_restore_flags(व्योम);

#घोषणा KDB_FLAG(flag)		(kdb_flags & KDB_FLAG_##flag)
#घोषणा KDB_FLAG_SET(flag)	((व्योम)(kdb_flags |= KDB_FLAG_##flag))
#घोषणा KDB_FLAG_CLEAR(flag)	((व्योम)(kdb_flags &= ~KDB_FLAG_##flag))

/*
 * External entry poपूर्णांक क्रम the kernel debugger.  The pt_regs
 * at the समय of entry are supplied aदीर्घ with the reason क्रम
 * entry to the kernel debugger.
 */

प्रकार क्रमागत अणु
	KDB_REASON_ENTER = 1,	/* KDB_ENTER() trap/fault - regs valid */
	KDB_REASON_ENTER_SLAVE,	/* KDB_ENTER_SLAVE() trap/fault - regs valid */
	KDB_REASON_BREAK,	/* Breakpoपूर्णांक inst. - regs valid */
	KDB_REASON_DEBUG,	/* Debug Fault - regs valid */
	KDB_REASON_OOPS,	/* Kernel Oops - regs valid */
	KDB_REASON_SWITCH,	/* CPU चयन - regs valid*/
	KDB_REASON_KEYBOARD,	/* Keyboard entry - regs valid */
	KDB_REASON_NMI,		/* Non-maskable पूर्णांकerrupt; regs valid */
	KDB_REASON_RECURSE,	/* Recursive entry to kdb;
				 * regs probably valid */
	KDB_REASON_SSTEP,	/* Single Step trap. - regs valid */
	KDB_REASON_SYSTEM_NMI,	/* In NMI due to SYSTEM cmd; regs valid */
पूर्ण kdb_reason_t;

क्रमागत kdb_msgsrc अणु
	KDB_MSGSRC_INTERNAL, /* direct call to kdb_म_लिखो() */
	KDB_MSGSRC_PRINTK, /* trapped from prपूर्णांकk() */
पूर्ण;

बाह्य पूर्णांक kdb_trap_prपूर्णांकk;
बाह्य पूर्णांक kdb_म_लिखो_cpu;
बाह्य __म_लिखो(2, 0) पूर्णांक vkdb_म_लिखो(क्रमागत kdb_msgsrc src, स्थिर अक्षर *fmt,
				      बहु_सूची args);
बाह्य __म_लिखो(1, 2) पूर्णांक kdb_म_लिखो(स्थिर अक्षर *, ...);
प्रकार __म_लिखो(1, 2) पूर्णांक (*kdb_म_लिखो_t)(स्थिर अक्षर *, ...);

बाह्य व्योम kdb_init(पूर्णांक level);

/* Access to kdb specअगरic polling devices */
प्रकार पूर्णांक (*get_अक्षर_func)(व्योम);
बाह्य get_अक्षर_func kdb_poll_funcs[];
बाह्य पूर्णांक kdb_get_kbd_अक्षर(व्योम);

अटल अंतरभूत
पूर्णांक kdb_process_cpu(स्थिर काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित पूर्णांक cpu = task_cpu(p);
	अगर (cpu > num_possible_cpus())
		cpu = 0;
	वापस cpu;
पूर्ण

#अगर_घोषित CONFIG_KALLSYMS
बाह्य स्थिर अक्षर *kdb_walk_kallsyms(loff_t *pos);
#अन्यथा /* ! CONFIG_KALLSYMS */
अटल अंतरभूत स्थिर अक्षर *kdb_walk_kallsyms(loff_t *pos)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* ! CONFIG_KALLSYMS */

/* Dynamic kdb shell command registration */
बाह्य पूर्णांक kdb_रेजिस्टर(अक्षर *, kdb_func_t, अक्षर *, अक्षर *, लघु);
बाह्य पूर्णांक kdb_रेजिस्टर_flags(अक्षर *, kdb_func_t, अक्षर *, अक्षर *,
			      लघु, kdb_cmdflags_t);
बाह्य पूर्णांक kdb_unरेजिस्टर(अक्षर *);
#अन्यथा /* ! CONFIG_KGDB_KDB */
अटल अंतरभूत __म_लिखो(1, 2) पूर्णांक kdb_म_लिखो(स्थिर अक्षर *fmt, ...) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम kdb_init(पूर्णांक level) अणुपूर्ण
अटल अंतरभूत पूर्णांक kdb_रेजिस्टर(अक्षर *cmd, kdb_func_t func, अक्षर *usage,
			       अक्षर *help, लघु minlen) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक kdb_रेजिस्टर_flags(अक्षर *cmd, kdb_func_t func, अक्षर *usage,
				     अक्षर *help, लघु minlen,
				     kdb_cmdflags_t flags) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक kdb_unरेजिस्टर(अक्षर *cmd) अणु वापस 0; पूर्ण
#पूर्ण_अगर	/* CONFIG_KGDB_KDB */
क्रमागत अणु
	KDB_NOT_INITIALIZED,
	KDB_INIT_EARLY,
	KDB_INIT_FULL,
पूर्ण;

बाह्य पूर्णांक kdbgetपूर्णांकenv(स्थिर अक्षर *, पूर्णांक *);
बाह्य पूर्णांक kdb_set(पूर्णांक, स्थिर अक्षर **);

#पूर्ण_अगर	/* !_KDB_H */
