<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KERNEL_PRINTK__
#घोषणा __KERNEL_PRINTK__

#समावेश <मानकतर्क.स>
#समावेश <linux/init.h>
#समावेश <linux/kern_levels.h>
#समावेश <linux/linkage.h>
#समावेश <linux/cache.h>
#समावेश <linux/ratelimit_types.h>

बाह्य स्थिर अक्षर linux_banner[];
बाह्य स्थिर अक्षर linux_proc_banner[];

बाह्य पूर्णांक oops_in_progress;	/* If set, an oops, panic(), BUG() or die() is in progress */

#घोषणा PRINTK_MAX_SINGLE_HEADER_LEN 2

अटल अंतरभूत पूर्णांक prपूर्णांकk_get_level(स्थिर अक्षर *buffer)
अणु
	अगर (buffer[0] == KERN_SOH_ASCII && buffer[1]) अणु
		चयन (buffer[1]) अणु
		हाल '0' ... '7':
		हाल 'c':	/* KERN_CONT */
			वापस buffer[1];
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *prपूर्णांकk_skip_level(स्थिर अक्षर *buffer)
अणु
	अगर (prपूर्णांकk_get_level(buffer))
		वापस buffer + 2;

	वापस buffer;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *prपूर्णांकk_skip_headers(स्थिर अक्षर *buffer)
अणु
	जबतक (prपूर्णांकk_get_level(buffer))
		buffer = prपूर्णांकk_skip_level(buffer);

	वापस buffer;
पूर्ण

#घोषणा CONSOLE_EXT_LOG_MAX	8192

/* prपूर्णांकk's without a loglevel use this.. */
#घोषणा MESSAGE_LOGLEVEL_DEFAULT CONFIG_MESSAGE_LOGLEVEL_DEFAULT

/* We show everything that is MORE important than this.. */
#घोषणा CONSOLE_LOGLEVEL_SILENT  0 /* Mum's the word */
#घोषणा CONSOLE_LOGLEVEL_MIN	 1 /* Minimum loglevel we let people use */
#घोषणा CONSOLE_LOGLEVEL_DEBUG	10 /* issue debug messages */
#घोषणा CONSOLE_LOGLEVEL_MOTORMOUTH 15	/* You can't shut this one up */

/*
 * Default used to be hard-coded at 7, quiet used to be hardcoded at 4,
 * we're now allowing both to be set from kernel config.
 */
#घोषणा CONSOLE_LOGLEVEL_DEFAULT CONFIG_CONSOLE_LOGLEVEL_DEFAULT
#घोषणा CONSOLE_LOGLEVEL_QUIET	 CONFIG_CONSOLE_LOGLEVEL_QUIET

बाह्य पूर्णांक console_prपूर्णांकk[];

#घोषणा console_loglevel (console_prपूर्णांकk[0])
#घोषणा शेष_message_loglevel (console_prपूर्णांकk[1])
#घोषणा minimum_console_loglevel (console_prपूर्णांकk[2])
#घोषणा शेष_console_loglevel (console_prपूर्णांकk[3])

अटल अंतरभूत व्योम console_silent(व्योम)
अणु
	console_loglevel = CONSOLE_LOGLEVEL_SILENT;
पूर्ण

अटल अंतरभूत व्योम console_verbose(व्योम)
अणु
	अगर (console_loglevel)
		console_loglevel = CONSOLE_LOGLEVEL_MOTORMOUTH;
पूर्ण

/* म_माप("ratelimit") + 1 */
#घोषणा DEVKMSG_STR_MAX_SIZE 10
बाह्य अक्षर devkmsg_log_str[];
काष्ठा ctl_table;

बाह्य पूर्णांक suppress_prपूर्णांकk;

काष्ठा va_क्रमmat अणु
	स्थिर अक्षर *fmt;
	बहु_सूची *va;
पूर्ण;

/*
 * FW_BUG
 * Add this to a message where you are sure the firmware is buggy or behaves
 * really stupid or out of spec. Be aware that the responsible BIOS developer
 * should be able to fix this issue or at least get a concrete idea of the
 * problem by पढ़ोing your message without the need of looking at the kernel
 * code.
 *
 * Use it क्रम definite and high priority BIOS bugs.
 *
 * FW_WARN
 * Use it क्रम not that clear (e.g. could the kernel messed up things alपढ़ोy?)
 * and medium priority BIOS bugs.
 *
 * FW_INFO
 * Use this one अगर you want to tell the user or venकरोr about something
 * suspicious, but generally harmless related to the firmware.
 *
 * Use it क्रम inक्रमmation or very low priority BIOS bugs.
 */
#घोषणा FW_BUG		"[Firmware Bug]: "
#घोषणा FW_WARN		"[Firmware Warn]: "
#घोषणा FW_INFO		"[Firmware Info]: "

/*
 * HW_ERR
 * Add this to a message क्रम hardware errors, so that user can report
 * it to hardware venकरोr instead of LKML or software venकरोr.
 */
#घोषणा HW_ERR		"[Hardware Error]: "

/*
 * DEPRECATED
 * Add this to a message whenever you want to warn user space about the use
 * of a deprecated aspect of an API so they can stop using it
 */
#घोषणा DEPRECATED	"[Deprecated]: "

/*
 * Dummy prपूर्णांकk क्रम disabled debugging statements to use whilst मुख्यtaining
 * gcc's क्रमmat checking.
 */
#घोषणा no_prपूर्णांकk(fmt, ...)				\
(अणु							\
	अगर (0)						\
		prपूर्णांकk(fmt, ##__VA_ARGS__);		\
	0;						\
पूर्ण)

#अगर_घोषित CONFIG_EARLY_PRINTK
बाह्य यंत्रlinkage __म_लिखो(1, 2)
व्योम early_prपूर्णांकk(स्थिर अक्षर *fmt, ...);
#अन्यथा
अटल अंतरभूत __म_लिखो(1, 2) __cold
व्योम early_prपूर्णांकk(स्थिर अक्षर *s, ...) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PRINTK_NMI
बाह्य व्योम prपूर्णांकk_nmi_enter(व्योम);
बाह्य व्योम prपूर्णांकk_nmi_निकास(व्योम);
बाह्य व्योम prपूर्णांकk_nmi_direct_enter(व्योम);
बाह्य व्योम prपूर्णांकk_nmi_direct_निकास(व्योम);
#अन्यथा
अटल अंतरभूत व्योम prपूर्णांकk_nmi_enter(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम prपूर्णांकk_nmi_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम prपूर्णांकk_nmi_direct_enter(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम prपूर्णांकk_nmi_direct_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर /* PRINTK_NMI */

काष्ठा dev_prपूर्णांकk_info;

#अगर_घोषित CONFIG_PRINTK
यंत्रlinkage __म_लिखो(4, 0)
पूर्णांक vprपूर्णांकk_emit(पूर्णांक facility, पूर्णांक level,
		 स्थिर काष्ठा dev_prपूर्णांकk_info *dev_info,
		 स्थिर अक्षर *fmt, बहु_सूची args);

यंत्रlinkage __म_लिखो(1, 0)
पूर्णांक vprपूर्णांकk(स्थिर अक्षर *fmt, बहु_सूची args);

यंत्रlinkage __म_लिखो(1, 2) __cold
पूर्णांक prपूर्णांकk(स्थिर अक्षर *fmt, ...);

/*
 * Special prपूर्णांकk facility क्रम scheduler/समयkeeping use only, _DO_NOT_USE_ !
 */
__म_लिखो(1, 2) __cold पूर्णांक prपूर्णांकk_deferred(स्थिर अक्षर *fmt, ...);

/*
 * Please करोn't use prपूर्णांकk_ratelimit(), because it shares ratelimiting state
 * with all other unrelated prपूर्णांकk_ratelimit() callsites.  Instead use
 * prपूर्णांकk_ratelimited() or plain old __ratelimit().
 */
बाह्य पूर्णांक __prपूर्णांकk_ratelimit(स्थिर अक्षर *func);
#घोषणा prपूर्णांकk_ratelimit() __prपूर्णांकk_ratelimit(__func__)
बाह्य bool prपूर्णांकk_समयd_ratelimit(अचिन्हित दीर्घ *caller_jअगरfies,
				   अचिन्हित पूर्णांक पूर्णांकerval_msec);

बाह्य पूर्णांक prपूर्णांकk_delay_msec;
बाह्य पूर्णांक dmesg_restrict;

बाह्य पूर्णांक
devkmsg_sysctl_set_loglvl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buf,
			  माप_प्रकार *lenp, loff_t *ppos);

बाह्य व्योम wake_up_klogd(व्योम);

अक्षर *log_buf_addr_get(व्योम);
u32 log_buf_len_get(व्योम);
व्योम log_buf_vmcoreinfo_setup(व्योम);
व्योम __init setup_log_buf(पूर्णांक early);
__म_लिखो(1, 2) व्योम dump_stack_set_arch_desc(स्थिर अक्षर *fmt, ...);
व्योम dump_stack_prपूर्णांक_info(स्थिर अक्षर *log_lvl);
व्योम show_regs_prपूर्णांक_info(स्थिर अक्षर *log_lvl);
बाह्य यंत्रlinkage व्योम dump_stack(व्योम) __cold;
बाह्य व्योम prपूर्णांकk_safe_flush(व्योम);
बाह्य व्योम prपूर्णांकk_safe_flush_on_panic(व्योम);
#अन्यथा
अटल अंतरभूत __म_लिखो(1, 0)
पूर्णांक vprपूर्णांकk(स्थिर अक्षर *s, बहु_सूची args)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत __म_लिखो(1, 2) __cold
पूर्णांक prपूर्णांकk(स्थिर अक्षर *s, ...)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत __म_लिखो(1, 2) __cold
पूर्णांक prपूर्णांकk_deferred(स्थिर अक्षर *s, ...)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक prपूर्णांकk_ratelimit(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत bool prपूर्णांकk_समयd_ratelimit(अचिन्हित दीर्घ *caller_jअगरfies,
					  अचिन्हित पूर्णांक पूर्णांकerval_msec)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम wake_up_klogd(व्योम)
अणु
पूर्ण

अटल अंतरभूत अक्षर *log_buf_addr_get(व्योम)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत u32 log_buf_len_get(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम log_buf_vmcoreinfo_setup(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम setup_log_buf(पूर्णांक early)
अणु
पूर्ण

अटल अंतरभूत __म_लिखो(1, 2) व्योम dump_stack_set_arch_desc(स्थिर अक्षर *fmt, ...)
अणु
पूर्ण

अटल अंतरभूत व्योम dump_stack_prपूर्णांक_info(स्थिर अक्षर *log_lvl)
अणु
पूर्ण

अटल अंतरभूत व्योम show_regs_prपूर्णांक_info(स्थिर अक्षर *log_lvl)
अणु
पूर्ण

अटल अंतरभूत व्योम dump_stack(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम prपूर्णांकk_safe_flush(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम prपूर्णांकk_safe_flush_on_panic(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक kptr_restrict;

/**
 * pr_fmt - used by the pr_*() macros to generate the prपूर्णांकk क्रमmat string
 * @fmt: क्रमmat string passed from a pr_*() macro
 *
 * This macro can be used to generate a unअगरied क्रमmat string क्रम pr_*()
 * macros. A common use is to prefix all pr_*() messages in a file with a common
 * string. For example, defining this at the top of a source file:
 *
 *        #घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 *
 * would prefix all pr_info, pr_emerg... messages in the file with the module
 * name.
 */
#अगर_अघोषित pr_fmt
#घोषणा pr_fmt(fmt) fmt
#पूर्ण_अगर

/**
 * pr_emerg - Prपूर्णांक an emergency-level message
 * @fmt: क्रमmat string
 * @...: arguments क्रम the क्रमmat string
 *
 * This macro expands to a prपूर्णांकk with KERN_EMERG loglevel. It uses pr_fmt() to
 * generate the क्रमmat string.
 */
#घोषणा pr_emerg(fmt, ...) \
	prपूर्णांकk(KERN_EMERG pr_fmt(fmt), ##__VA_ARGS__)
/**
 * pr_alert - Prपूर्णांक an alert-level message
 * @fmt: क्रमmat string
 * @...: arguments क्रम the क्रमmat string
 *
 * This macro expands to a prपूर्णांकk with KERN_ALERT loglevel. It uses pr_fmt() to
 * generate the क्रमmat string.
 */
#घोषणा pr_alert(fmt, ...) \
	prपूर्णांकk(KERN_ALERT pr_fmt(fmt), ##__VA_ARGS__)
/**
 * pr_crit - Prपूर्णांक a critical-level message
 * @fmt: क्रमmat string
 * @...: arguments क्रम the क्रमmat string
 *
 * This macro expands to a prपूर्णांकk with KERN_CRIT loglevel. It uses pr_fmt() to
 * generate the क्रमmat string.
 */
#घोषणा pr_crit(fmt, ...) \
	prपूर्णांकk(KERN_CRIT pr_fmt(fmt), ##__VA_ARGS__)
/**
 * pr_err - Prपूर्णांक an error-level message
 * @fmt: क्रमmat string
 * @...: arguments क्रम the क्रमmat string
 *
 * This macro expands to a prपूर्णांकk with KERN_ERR loglevel. It uses pr_fmt() to
 * generate the क्रमmat string.
 */
#घोषणा pr_err(fmt, ...) \
	prपूर्णांकk(KERN_ERR pr_fmt(fmt), ##__VA_ARGS__)
/**
 * pr_warn - Prपूर्णांक a warning-level message
 * @fmt: क्रमmat string
 * @...: arguments क्रम the क्रमmat string
 *
 * This macro expands to a prपूर्णांकk with KERN_WARNING loglevel. It uses pr_fmt()
 * to generate the क्रमmat string.
 */
#घोषणा pr_warn(fmt, ...) \
	prपूर्णांकk(KERN_WARNING pr_fmt(fmt), ##__VA_ARGS__)
/**
 * pr_notice - Prपूर्णांक a notice-level message
 * @fmt: क्रमmat string
 * @...: arguments क्रम the क्रमmat string
 *
 * This macro expands to a prपूर्णांकk with KERN_NOTICE loglevel. It uses pr_fmt() to
 * generate the क्रमmat string.
 */
#घोषणा pr_notice(fmt, ...) \
	prपूर्णांकk(KERN_NOTICE pr_fmt(fmt), ##__VA_ARGS__)
/**
 * pr_info - Prपूर्णांक an info-level message
 * @fmt: क्रमmat string
 * @...: arguments क्रम the क्रमmat string
 *
 * This macro expands to a prपूर्णांकk with KERN_INFO loglevel. It uses pr_fmt() to
 * generate the क्रमmat string.
 */
#घोषणा pr_info(fmt, ...) \
	prपूर्णांकk(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)

/**
 * pr_cont - Continues a previous log message in the same line.
 * @fmt: क्रमmat string
 * @...: arguments क्रम the क्रमmat string
 *
 * This macro expands to a prपूर्णांकk with KERN_CONT loglevel. It should only be
 * used when continuing a log message with no newline ('\n') enबंदd. Otherwise
 * it शेषs back to KERN_DEFAULT loglevel.
 */
#घोषणा pr_cont(fmt, ...) \
	prपूर्णांकk(KERN_CONT fmt, ##__VA_ARGS__)

/**
 * pr_devel - Prपूर्णांक a debug-level message conditionally
 * @fmt: क्रमmat string
 * @...: arguments क्रम the क्रमmat string
 *
 * This macro expands to a prपूर्णांकk with KERN_DEBUG loglevel अगर DEBUG is
 * defined. Otherwise it करोes nothing.
 *
 * It uses pr_fmt() to generate the क्रमmat string.
 */
#अगर_घोषित DEBUG
#घोषणा pr_devel(fmt, ...) \
	prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#अन्यथा
#घोषणा pr_devel(fmt, ...) \
	no_prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#पूर्ण_अगर


/* If you are writing a driver, please use dev_dbg instead */
#अगर defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_CORE) && defined(DYNAMIC_DEBUG_MODULE))
#समावेश <linux/dynamic_debug.h>

/**
 * pr_debug - Prपूर्णांक a debug-level message conditionally
 * @fmt: क्रमmat string
 * @...: arguments क्रम the क्रमmat string
 *
 * This macro expands to dynamic_pr_debug() अगर CONFIG_DYNAMIC_DEBUG is
 * set. Otherwise, अगर DEBUG is defined, it's equivalent to a prपूर्णांकk with
 * KERN_DEBUG loglevel. If DEBUG is not defined it करोes nothing.
 *
 * It uses pr_fmt() to generate the क्रमmat string (dynamic_pr_debug() uses
 * pr_fmt() पूर्णांकernally).
 */
#घोषणा pr_debug(fmt, ...)			\
	dynamic_pr_debug(fmt, ##__VA_ARGS__)
#या_अगर defined(DEBUG)
#घोषणा pr_debug(fmt, ...) \
	prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#अन्यथा
#घोषणा pr_debug(fmt, ...) \
	no_prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#पूर्ण_अगर

/*
 * Prपूर्णांक a one-समय message (analogous to WARN_ONCE() et al):
 */

#अगर_घोषित CONFIG_PRINTK
#घोषणा prपूर्णांकk_once(fmt, ...)					\
(अणु								\
	अटल bool __section(".data.once") __prपूर्णांक_once;	\
	bool __ret_prपूर्णांक_once = !__prपूर्णांक_once;			\
								\
	अगर (!__prपूर्णांक_once) अणु					\
		__prपूर्णांक_once = true;				\
		prपूर्णांकk(fmt, ##__VA_ARGS__);			\
	पूर्ण							\
	unlikely(__ret_prपूर्णांक_once);				\
पूर्ण)
#घोषणा prपूर्णांकk_deferred_once(fmt, ...)				\
(अणु								\
	अटल bool __section(".data.once") __prपूर्णांक_once;	\
	bool __ret_prपूर्णांक_once = !__prपूर्णांक_once;			\
								\
	अगर (!__prपूर्णांक_once) अणु					\
		__prपूर्णांक_once = true;				\
		prपूर्णांकk_deferred(fmt, ##__VA_ARGS__);		\
	पूर्ण							\
	unlikely(__ret_prपूर्णांक_once);				\
पूर्ण)
#अन्यथा
#घोषणा prपूर्णांकk_once(fmt, ...)					\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#घोषणा prपूर्णांकk_deferred_once(fmt, ...)				\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#घोषणा pr_emerg_once(fmt, ...)					\
	prपूर्णांकk_once(KERN_EMERG pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_alert_once(fmt, ...)					\
	prपूर्णांकk_once(KERN_ALERT pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_crit_once(fmt, ...)					\
	prपूर्णांकk_once(KERN_CRIT pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_err_once(fmt, ...)					\
	prपूर्णांकk_once(KERN_ERR pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_warn_once(fmt, ...)					\
	prपूर्णांकk_once(KERN_WARNING pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_notice_once(fmt, ...)				\
	prपूर्णांकk_once(KERN_NOTICE pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_info_once(fmt, ...)					\
	prपूर्णांकk_once(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)
/* no pr_cont_once, करोn't करो that... */

#अगर defined(DEBUG)
#घोषणा pr_devel_once(fmt, ...)					\
	prपूर्णांकk_once(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#अन्यथा
#घोषणा pr_devel_once(fmt, ...)					\
	no_prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#पूर्ण_अगर

/* If you are writing a driver, please use dev_dbg instead */
#अगर defined(DEBUG)
#घोषणा pr_debug_once(fmt, ...)					\
	prपूर्णांकk_once(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#अन्यथा
#घोषणा pr_debug_once(fmt, ...)					\
	no_prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#पूर्ण_अगर

/*
 * ratelimited messages with local ratelimit_state,
 * no local ratelimit_state used in the !PRINTK हाल
 */
#अगर_घोषित CONFIG_PRINTK
#घोषणा prपूर्णांकk_ratelimited(fmt, ...)					\
(अणु									\
	अटल DEFINE_RATELIMIT_STATE(_rs,				\
				      DEFAULT_RATELIMIT_INTERVAL,	\
				      DEFAULT_RATELIMIT_BURST);		\
									\
	अगर (__ratelimit(&_rs))						\
		prपूर्णांकk(fmt, ##__VA_ARGS__);				\
पूर्ण)
#अन्यथा
#घोषणा prपूर्णांकk_ratelimited(fmt, ...)					\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#घोषणा pr_emerg_ratelimited(fmt, ...)					\
	prपूर्णांकk_ratelimited(KERN_EMERG pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_alert_ratelimited(fmt, ...)					\
	prपूर्णांकk_ratelimited(KERN_ALERT pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_crit_ratelimited(fmt, ...)					\
	prपूर्णांकk_ratelimited(KERN_CRIT pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_err_ratelimited(fmt, ...)					\
	prपूर्णांकk_ratelimited(KERN_ERR pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_warn_ratelimited(fmt, ...)					\
	prपूर्णांकk_ratelimited(KERN_WARNING pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_notice_ratelimited(fmt, ...)					\
	prपूर्णांकk_ratelimited(KERN_NOTICE pr_fmt(fmt), ##__VA_ARGS__)
#घोषणा pr_info_ratelimited(fmt, ...)					\
	prपूर्णांकk_ratelimited(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)
/* no pr_cont_ratelimited, करोn't करो that... */

#अगर defined(DEBUG)
#घोषणा pr_devel_ratelimited(fmt, ...)					\
	prपूर्णांकk_ratelimited(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#अन्यथा
#घोषणा pr_devel_ratelimited(fmt, ...)					\
	no_prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#पूर्ण_अगर

/* If you are writing a driver, please use dev_dbg instead */
#अगर defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_CORE) && defined(DYNAMIC_DEBUG_MODULE))
/* descriptor check is first to prevent flooding with "callbacks suppressed" */
#घोषणा pr_debug_ratelimited(fmt, ...)					\
करो अणु									\
	अटल DEFINE_RATELIMIT_STATE(_rs,				\
				      DEFAULT_RATELIMIT_INTERVAL,	\
				      DEFAULT_RATELIMIT_BURST);		\
	DEFINE_DYNAMIC_DEBUG_METADATA(descriptor, pr_fmt(fmt));		\
	अगर (DYNAMIC_DEBUG_BRANCH(descriptor) &&				\
	    __ratelimit(&_rs))						\
		__dynamic_pr_debug(&descriptor, pr_fmt(fmt), ##__VA_ARGS__);	\
पूर्ण जबतक (0)
#या_अगर defined(DEBUG)
#घोषणा pr_debug_ratelimited(fmt, ...)					\
	prपूर्णांकk_ratelimited(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#अन्यथा
#घोषणा pr_debug_ratelimited(fmt, ...) \
	no_prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#पूर्ण_अगर

बाह्य स्थिर काष्ठा file_operations kmsg_fops;

क्रमागत अणु
	DUMP_PREFIX_NONE,
	DUMP_PREFIX_ADDRESS,
	DUMP_PREFIX_OFFSET
पूर्ण;
बाह्य पूर्णांक hex_dump_to_buffer(स्थिर व्योम *buf, माप_प्रकार len, पूर्णांक rowsize,
			      पूर्णांक groupsize, अक्षर *linebuf, माप_प्रकार linebuflen,
			      bool ascii);
#अगर_घोषित CONFIG_PRINTK
बाह्य व्योम prपूर्णांक_hex_dump(स्थिर अक्षर *level, स्थिर अक्षर *prefix_str,
			   पूर्णांक prefix_type, पूर्णांक rowsize, पूर्णांक groupsize,
			   स्थिर व्योम *buf, माप_प्रकार len, bool ascii);
#अन्यथा
अटल अंतरभूत व्योम prपूर्णांक_hex_dump(स्थिर अक्षर *level, स्थिर अक्षर *prefix_str,
				  पूर्णांक prefix_type, पूर्णांक rowsize, पूर्णांक groupsize,
				  स्थिर व्योम *buf, माप_प्रकार len, bool ascii)
अणु
पूर्ण
अटल अंतरभूत व्योम prपूर्णांक_hex_dump_bytes(स्थिर अक्षर *prefix_str, पूर्णांक prefix_type,
					स्थिर व्योम *buf, माप_प्रकार len)
अणु
पूर्ण

#पूर्ण_अगर

#अगर defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_CORE) && defined(DYNAMIC_DEBUG_MODULE))
#घोषणा prपूर्णांक_hex_dump_debug(prefix_str, prefix_type, rowsize,	\
			     groupsize, buf, len, ascii)	\
	dynamic_hex_dump(prefix_str, prefix_type, rowsize,	\
			 groupsize, buf, len, ascii)
#या_अगर defined(DEBUG)
#घोषणा prपूर्णांक_hex_dump_debug(prefix_str, prefix_type, rowsize,		\
			     groupsize, buf, len, ascii)		\
	prपूर्णांक_hex_dump(KERN_DEBUG, prefix_str, prefix_type, rowsize,	\
		       groupsize, buf, len, ascii)
#अन्यथा
अटल अंतरभूत व्योम prपूर्णांक_hex_dump_debug(स्थिर अक्षर *prefix_str, पूर्णांक prefix_type,
					पूर्णांक rowsize, पूर्णांक groupsize,
					स्थिर व्योम *buf, माप_प्रकार len, bool ascii)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * prपूर्णांक_hex_dump_bytes - लघुhand क्रमm of prपूर्णांक_hex_dump() with शेष params
 * @prefix_str: string to prefix each line with;
 *  caller supplies trailing spaces क्रम alignment अगर desired
 * @prefix_type: controls whether prefix of an offset, address, or none
 *  is prपूर्णांकed (%DUMP_PREFIX_OFFSET, %DUMP_PREFIX_ADDRESS, %DUMP_PREFIX_NONE)
 * @buf: data blob to dump
 * @len: number of bytes in the @buf
 *
 * Calls prपूर्णांक_hex_dump(), with log level of KERN_DEBUG,
 * rowsize of 16, groupsize of 1, and ASCII output included.
 */
#घोषणा prपूर्णांक_hex_dump_bytes(prefix_str, prefix_type, buf, len)	\
	prपूर्णांक_hex_dump_debug(prefix_str, prefix_type, 16, 1, buf, len, true)

#पूर्ण_अगर
