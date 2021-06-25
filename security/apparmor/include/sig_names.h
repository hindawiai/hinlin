<शैली गुरु>
#समावेश <linux/संकेत.स>

#घोषणा SIGUNKNOWN 0
#घोषणा MAXMAPPED_SIG 35
#घोषणा MAXMAPPED_SIGNAME (MAXMAPPED_SIG + 1)
#घोषणा SIGRT_BASE 128

/* provide a mapping of arch संकेत to पूर्णांकernal संकेत # क्रम mediation
 * those that are always an alias SIGCLD क्रम SIGCLHD and SIGPOLL क्रम SIGIO
 * map to the same entry those that may/or may not get a separate entry
 */
अटल स्थिर पूर्णांक sig_map[MAXMAPPED_SIG] = अणु
	[0] = MAXMAPPED_SIG,	/* existence test */
	[SIGHUP] = 1,
	[संक_विघ्न] = 2,
	[SIGQUIT] = 3,
	[संक_अवैध] = 4,
	[SIGTRAP] = 5,		/* -, 5, - */
	[SIGABRT] = 6,		/*  SIGIOT: -, 6, - */
	[SIGBUS] = 7,		/* 10, 7, 10 */
	[संक_भ_त्रुटि] = 8,
	[SIGKILL] = 9,
	[SIGUSR1] = 10,		/* 30, 10, 16 */
	[संक_अंश] = 11,
	[SIGUSR2] = 12,		/* 31, 12, 17 */
	[SIGPIPE] = 13,
	[SIGALRM] = 14,
	[संक_इति] = 15,
#अगर_घोषित SIGSTKFLT
	[SIGSTKFLT] = 16,	/* -, 16, - */
#पूर्ण_अगर
	[SIGCHLD] = 17,		/* 20, 17, 18.  SIGCHLD -, -, 18 */
	[SIGCONT] = 18,		/* 19, 18, 25 */
	[SIGSTOP] = 19,		/* 17, 19, 23 */
	[SIGTSTP] = 20,		/* 18, 20, 24 */
	[SIGTTIN] = 21,		/* 21, 21, 26 */
	[SIGTTOU] = 22,		/* 22, 22, 27 */
	[SIGURG] = 23,		/* 16, 23, 21 */
	[SIGXCPU] = 24,		/* 24, 24, 30 */
	[SIGXFSZ] = 25,		/* 25, 25, 31 */
	[SIGVTALRM] = 26,	/* 26, 26, 28 */
	[SIGPROF] = 27,		/* 27, 27, 29 */
	[SIGWINCH] = 28,	/* 28, 28, 20 */
	[SIGIO] = 29,		/* SIGPOLL: 23, 29, 22 */
	[SIGPWR] = 30,		/* 29, 30, 19.  SIGINFO 29, -, - */
#अगर_घोषित SIGSYS
	[SIGSYS] = 31,		/* 12, 31, 12. often SIG LOST/UNUSED */
#पूर्ण_अगर
#अगर_घोषित SIGEMT
	[SIGEMT] = 32,		/* 7, - , 7 */
#पूर्ण_अगर
#अगर defined(SIGLOST) && SIGPWR != SIGLOST		/* sparc */
	[SIGLOST] = 33,		/* unused on Linux */
#पूर्ण_अगर
#अगर defined(SIGUNUSED) && \
    defined(SIGLOST) && defined(SIGSYS) && SIGLOST != SIGSYS
	[SIGUNUSED] = 34,	/* -, 31, - */
#पूर्ण_अगर
पूर्ण;

/* this table is ordered post sig_map[sig] mapping */
अटल स्थिर अक्षर *स्थिर sig_names[MAXMAPPED_SIGNAME] = अणु
	"unknown",
	"hup",
	"int",
	"quit",
	"ill",
	"trap",
	"abrt",
	"bus",
	"fpe",
	"kill",
	"usr1",
	"segv",
	"usr2",
	"pipe",
	"alrm",
	"term",
	"stkflt",
	"chld",
	"cont",
	"stop",
	"stp",
	"ttin",
	"ttou",
	"urg",
	"xcpu",
	"xfsz",
	"vtalrm",
	"prof",
	"winch",
	"io",
	"pwr",
	"sys",
	"emt",
	"lost",
	"unused",

	"exists",	/* always last existence test mapped to MAXMAPPED_SIG */
पूर्ण;

