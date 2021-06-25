<शैली गुरु>
/*
 * Kernel Debugger Architecture Independent Main Code
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1999-2004 Silicon Graphics, Inc.  All Rights Reserved.
 * Copyright (C) 2000 Stephane Eranian <eranian@hpl.hp.com>
 * Xscale (R) modअगरications copyright (C) 2003 Intel Corporation.
 * Copyright (c) 2009 Wind River Systems, Inc.  All Rights Reserved.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kmsg_dump.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/smp.h>
#समावेश <linux/utsname.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/atomic.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kdb.h>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/nmi.h>
#समावेश <linux/समय.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/cpu.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश "kdb_private.h"

#अघोषित	MODULE_PARAM_PREFIX
#घोषणा	MODULE_PARAM_PREFIX "kdb."

अटल पूर्णांक kdb_cmd_enabled = CONFIG_KDB_DEFAULT_ENABLE;
module_param_named(cmd_enable, kdb_cmd_enabled, पूर्णांक, 0600);

अक्षर kdb_grep_string[KDB_GREP_STRLEN];
पूर्णांक kdb_grepping_flag;
EXPORT_SYMBOL(kdb_grepping_flag);
पूर्णांक kdb_grep_leading;
पूर्णांक kdb_grep_trailing;

/*
 * Kernel debugger state flags
 */
अचिन्हित पूर्णांक kdb_flags;

/*
 * kdb_lock protects updates to kdb_initial_cpu.  Used to
 * single thपढ़ो processors through the kernel debugger.
 */
पूर्णांक kdb_initial_cpu = -1;	/* cpu number that owns kdb */
पूर्णांक kdb_nextline = 1;
पूर्णांक kdb_state;			/* General KDB state */

काष्ठा task_काष्ठा *kdb_current_task;
काष्ठा pt_regs *kdb_current_regs;

स्थिर अक्षर *kdb_diemsg;
अटल पूर्णांक kdb_go_count;
#अगर_घोषित CONFIG_KDB_CONTINUE_CATASTROPHIC
अटल अचिन्हित पूर्णांक kdb_जारी_catastrophic =
	CONFIG_KDB_CONTINUE_CATASTROPHIC;
#अन्यथा
अटल अचिन्हित पूर्णांक kdb_जारी_catastrophic;
#पूर्ण_अगर

/* kdb_cmds_head describes the available commands. */
अटल LIST_HEAD(kdb_cmds_head);

प्रकार काष्ठा _kdbmsg अणु
	पूर्णांक	km_diag;	/* kdb diagnostic */
	अक्षर	*km_msg;	/* Corresponding message text */
पूर्ण kdbmsg_t;

#घोषणा KDBMSG(msgnum, text) \
	अणु KDB_##msgnum, text पूर्ण

अटल kdbmsg_t kdbmsgs[] = अणु
	KDBMSG(NOTFOUND, "Command Not Found"),
	KDBMSG(ARGCOUNT, "Improper argument count, see usage."),
	KDBMSG(BADWIDTH, "Illegal value for BYTESPERWORD use 1, 2, 4 or 8, "
	       "8 is only allowed on 64 bit systems"),
	KDBMSG(BADRADIX, "Illegal value for RADIX use 8, 10 or 16"),
	KDBMSG(NOTENV, "Cannot find environment variable"),
	KDBMSG(NOENVVALUE, "Environment variable should have value"),
	KDBMSG(NOTIMP, "Command not implemented"),
	KDBMSG(ENVFULL, "Environment full"),
	KDBMSG(ENVBUFFULL, "Environment buffer full"),
	KDBMSG(TOOMANYBPT, "Too many breakpoints defined"),
#अगर_घोषित CONFIG_CPU_XSCALE
	KDBMSG(TOOMANYDBREGS, "More breakpoints than ibcr registers defined"),
#अन्यथा
	KDBMSG(TOOMANYDBREGS, "More breakpoints than db registers defined"),
#पूर्ण_अगर
	KDBMSG(DUPBPT, "Duplicate breakpoint address"),
	KDBMSG(BPTNOTFOUND, "Breakpoint not found"),
	KDBMSG(BADMODE, "Invalid IDMODE"),
	KDBMSG(BADINT, "Illegal numeric value"),
	KDBMSG(INVADDRFMT, "Invalid symbolic address format"),
	KDBMSG(BADREG, "Invalid register name"),
	KDBMSG(BADCPUNUM, "Invalid cpu number"),
	KDBMSG(BADLENGTH, "Invalid length field"),
	KDBMSG(NOBP, "No Breakpoint exists"),
	KDBMSG(BADADDR, "Invalid address"),
	KDBMSG(NOPERM, "Permission denied"),
पूर्ण;
#अघोषित KDBMSG

अटल स्थिर पूर्णांक __nkdb_err = ARRAY_SIZE(kdbmsgs);


/*
 * Initial environment.   This is all kept अटल and local to
 * this file.   We करोn't want to rely on the memory allocation
 * mechanisms in the kernel, so we use a very limited allocate-only
 * heap क्रम new and altered environment variables.  The entire
 * environment is limited to a fixed number of entries (add more
 * to __env[] अगर required) and a fixed amount of heap (add more to
 * KDB_ENVबफ_मानE अगर required).
 */

अटल अक्षर *__env[31] = अणु
#अगर defined(CONFIG_SMP)
	"PROMPT=[%d]kdb> ",
#अन्यथा
	"PROMPT=kdb> ",
#पूर्ण_अगर
	"MOREPROMPT=more> ",
	"RADIX=16",
	"MDCOUNT=8",		/* lines of md output */
	KDB_PLATFORM_ENV,
	"DTABCOUNT=30",
	"NOSECT=1",
पूर्ण;

अटल स्थिर पूर्णांक __nenv = ARRAY_SIZE(__env);

काष्ठा task_काष्ठा *kdb_curr_task(पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *p = curr_task(cpu);
#अगर_घोषित	_TIF_MCA_INIT
	अगर ((task_thपढ़ो_info(p)->flags & _TIF_MCA_INIT) && KDB_TSK(cpu))
		p = krp->p;
#पूर्ण_अगर
	वापस p;
पूर्ण

/*
 * Check whether the flags of the current command and the permissions
 * of the kdb console has allow a command to be run.
 */
अटल अंतरभूत bool kdb_check_flags(kdb_cmdflags_t flags, पूर्णांक permissions,
				   bool no_args)
अणु
	/* permissions comes from userspace so needs massaging slightly */
	permissions &= KDB_ENABLE_MASK;
	permissions |= KDB_ENABLE_ALWAYS_SAFE;

	/* some commands change group when launched with no arguments */
	अगर (no_args)
		permissions |= permissions << KDB_ENABLE_NO_ARGS_SHIFT;

	flags |= KDB_ENABLE_ALL;

	वापस permissions & flags;
पूर्ण

/*
 * kdbदो_पर्या - This function will वापस the अक्षरacter string value of
 *	an environment variable.
 * Parameters:
 *	match	A अक्षरacter string representing an environment variable.
 * Returns:
 *	शून्य	No environment variable matches 'match'
 *	अक्षर*	Poपूर्णांकer to string value of environment variable.
 */
अक्षर *kdbदो_पर्या(स्थिर अक्षर *match)
अणु
	अक्षर **ep = __env;
	पूर्णांक matchlen = म_माप(match);
	पूर्णांक i;

	क्रम (i = 0; i < __nenv; i++) अणु
		अक्षर *e = *ep++;

		अगर (!e)
			जारी;

		अगर ((म_भेदन(match, e, matchlen) == 0)
		 && ((e[matchlen] == '\0')
		   || (e[matchlen] == '='))) अणु
			अक्षर *cp = म_अक्षर(e, '=');
			वापस cp ? ++cp : "";
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * kdballocenv - This function is used to allocate bytes क्रम
 *	environment entries.
 * Parameters:
 *	match	A अक्षरacter string representing a numeric value
 * Outमाला_दो:
 *	*value  the अचिन्हित दीर्घ representation of the env variable 'match'
 * Returns:
 *	Zero on success, a kdb diagnostic on failure.
 * Remarks:
 *	We use a अटल environment buffer (envbuffer) to hold the values
 *	of dynamically generated environment variables (see kdb_set).  Buffer
 *	space once allocated is never मुक्त'd, so over समय, the amount of space
 *	(currently 512 bytes) will be exhausted अगर env variables are changed
 *	frequently.
 */
अटल अक्षर *kdballocenv(माप_प्रकार bytes)
अणु
#घोषणा	KDB_ENVबफ_मानE	512
	अटल अक्षर envbuffer[KDB_ENVबफ_मानE];
	अटल पूर्णांक envbufsize;
	अक्षर *ep = शून्य;

	अगर ((KDB_ENVबफ_मानE - envbufsize) >= bytes) अणु
		ep = &envbuffer[envbufsize];
		envbufsize += bytes;
	पूर्ण
	वापस ep;
पूर्ण

/*
 * kdbgetulenv - This function will वापस the value of an अचिन्हित
 *	दीर्घ-valued environment variable.
 * Parameters:
 *	match	A अक्षरacter string representing a numeric value
 * Outमाला_दो:
 *	*value  the अचिन्हित दीर्घ represntation of the env variable 'match'
 * Returns:
 *	Zero on success, a kdb diagnostic on failure.
 */
अटल पूर्णांक kdbgetulenv(स्थिर अक्षर *match, अचिन्हित दीर्घ *value)
अणु
	अक्षर *ep;

	ep = kdbदो_पर्या(match);
	अगर (!ep)
		वापस KDB_NOTENV;
	अगर (म_माप(ep) == 0)
		वापस KDB_NOENVVALUE;

	*value = simple_म_से_अदीर्घ(ep, शून्य, 0);

	वापस 0;
पूर्ण

/*
 * kdbgetपूर्णांकenv - This function will वापस the value of an
 *	पूर्णांकeger-valued environment variable.
 * Parameters:
 *	match	A अक्षरacter string representing an पूर्णांकeger-valued env variable
 * Outमाला_दो:
 *	*value  the पूर्णांकeger representation of the environment variable 'match'
 * Returns:
 *	Zero on success, a kdb diagnostic on failure.
 */
पूर्णांक kdbgetपूर्णांकenv(स्थिर अक्षर *match, पूर्णांक *value)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक diag;

	diag = kdbgetulenv(match, &val);
	अगर (!diag)
		*value = (पूर्णांक) val;
	वापस diag;
पूर्ण

/*
 * kdb_setenv() - Alter an existing environment variable or create a new one.
 * @var: Name of the variable
 * @val: Value of the variable
 *
 * Return: Zero on success, a kdb diagnostic on failure.
 */
अटल पूर्णांक kdb_setenv(स्थिर अक्षर *var, स्थिर अक्षर *val)
अणु
	पूर्णांक i;
	अक्षर *ep;
	माप_प्रकार varlen, vallen;

	varlen = म_माप(var);
	vallen = म_माप(val);
	ep = kdballocenv(varlen + vallen + 2);
	अगर (ep == (अक्षर *)0)
		वापस KDB_ENVBUFFULL;

	प्र_लिखो(ep, "%s=%s", var, val);

	क्रम (i = 0; i < __nenv; i++) अणु
		अगर (__env[i]
		 && ((म_भेदन(__env[i], var, varlen) == 0)
		   && ((__env[i][varlen] == '\0')
		    || (__env[i][varlen] == '=')))) अणु
			__env[i] = ep;
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * Wasn't existing variable.  Fit पूर्णांकo slot.
	 */
	क्रम (i = 0; i < __nenv-1; i++) अणु
		अगर (__env[i] == (अक्षर *)0) अणु
			__env[i] = ep;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस KDB_ENVFULL;
पूर्ण

/*
 * kdb_prपूर्णांकenv() - Display the current environment variables.
 */
अटल व्योम kdb_prपूर्णांकenv(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < __nenv; i++) अणु
		अगर (__env[i])
			kdb_म_लिखो("%s\n", __env[i]);
	पूर्ण
पूर्ण

/*
 * kdbgetularg - This function will convert a numeric string पूर्णांकo an
 *	अचिन्हित दीर्घ value.
 * Parameters:
 *	arg	A अक्षरacter string representing a numeric value
 * Outमाला_दो:
 *	*value  the अचिन्हित दीर्घ represntation of arg.
 * Returns:
 *	Zero on success, a kdb diagnostic on failure.
 */
पूर्णांक kdbgetularg(स्थिर अक्षर *arg, अचिन्हित दीर्घ *value)
अणु
	अक्षर *endp;
	अचिन्हित दीर्घ val;

	val = simple_म_से_अदीर्घ(arg, &endp, 0);

	अगर (endp == arg) अणु
		/*
		 * Also try base 16, क्रम us folks too lazy to type the
		 * leading 0x...
		 */
		val = simple_म_से_अदीर्घ(arg, &endp, 16);
		अगर (endp == arg)
			वापस KDB_BADINT;
	पूर्ण

	*value = val;

	वापस 0;
पूर्ण

पूर्णांक kdbgetu64arg(स्थिर अक्षर *arg, u64 *value)
अणु
	अक्षर *endp;
	u64 val;

	val = simple_म_से_अदीर्घl(arg, &endp, 0);

	अगर (endp == arg) अणु

		val = simple_म_से_अदीर्घl(arg, &endp, 16);
		अगर (endp == arg)
			वापस KDB_BADINT;
	पूर्ण

	*value = val;

	वापस 0;
पूर्ण

/*
 * kdb_set - This function implements the 'set' command.  Alter an
 *	existing environment variable or create a new one.
 */
पूर्णांक kdb_set(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	/*
	 * we can be invoked two ways:
	 *   set var=value    argv[1]="var", argv[2]="value"
	 *   set var = value  argv[1]="var", argv[2]="=", argv[3]="value"
	 * - अगर the latter, shअगरt 'em करोwn.
	 */
	अगर (argc == 3) अणु
		argv[2] = argv[3];
		argc--;
	पूर्ण

	अगर (argc != 2)
		वापस KDB_ARGCOUNT;

	/*
	 * Censor sensitive variables
	 */
	अगर (म_भेद(argv[1], "PROMPT") == 0 &&
	    !kdb_check_flags(KDB_ENABLE_MEM_READ, kdb_cmd_enabled, false))
		वापस KDB_NOPERM;

	/*
	 * Check क्रम पूर्णांकernal variables
	 */
	अगर (म_भेद(argv[1], "KDBDEBUG") == 0) अणु
		अचिन्हित पूर्णांक debugflags;
		अक्षर *cp;

		debugflags = simple_म_से_अदीर्घ(argv[2], &cp, 0);
		अगर (cp == argv[2] || debugflags & ~KDB_DEBUG_FLAG_MASK) अणु
			kdb_म_लिखो("kdb: illegal debug flags '%s'\n",
				    argv[2]);
			वापस 0;
		पूर्ण
		kdb_flags = (kdb_flags & ~KDB_DEBUG(MASK))
			| (debugflags << KDB_DEBUG_FLAG_SHIFT);

		वापस 0;
	पूर्ण

	/*
	 * Tokenizer squashed the '=' sign.  argv[1] is variable
	 * name, argv[2] = value.
	 */
	वापस kdb_setenv(argv[1], argv[2]);
पूर्ण

अटल पूर्णांक kdb_check_regs(व्योम)
अणु
	अगर (!kdb_current_regs) अणु
		kdb_म_लिखो("No current kdb registers."
			   "  You may need to select another task\n");
		वापस KDB_BADREG;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * kdbgetaddrarg - This function is responsible क्रम parsing an
 *	address-expression and वापसing the value of the expression,
 *	symbol name, and offset to the caller.
 *
 *	The argument may consist of a numeric value (decimal or
 *	hexidecimal), a symbol name, a रेजिस्टर name (preceded by the
 *	percent sign), an environment variable with a numeric value
 *	(preceded by a करोllar sign) or a simple arithmetic expression
 *	consisting of a symbol name, +/-, and a numeric स्थिरant value
 *	(offset).
 * Parameters:
 *	argc	- count of arguments in argv
 *	argv	- argument vector
 *	*nextarg - index to next unparsed argument in argv[]
 *	regs	- Register state at समय of KDB entry
 * Outमाला_दो:
 *	*value	- receives the value of the address-expression
 *	*offset - receives the offset specअगरied, अगर any
 *	*name   - receives the symbol name, अगर any
 *	*nextarg - index to next unparsed argument in argv[]
 * Returns:
 *	zero is वापसed on success, a kdb diagnostic code is
 *      वापसed on error.
 */
पूर्णांक kdbgetaddrarg(पूर्णांक argc, स्थिर अक्षर **argv, पूर्णांक *nextarg,
		  अचिन्हित दीर्घ *value,  दीर्घ *offset,
		  अक्षर **name)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ off = 0;
	पूर्णांक positive;
	पूर्णांक diag;
	पूर्णांक found = 0;
	अक्षर *symname;
	अक्षर symbol = '\0';
	अक्षर *cp;
	kdb_symtab_t symtab;

	/*
	 * If the enable flags prohibit both arbitrary memory access
	 * and flow control then there are no reasonable grounds to
	 * provide symbol lookup.
	 */
	अगर (!kdb_check_flags(KDB_ENABLE_MEM_READ | KDB_ENABLE_FLOW_CTRL,
			     kdb_cmd_enabled, false))
		वापस KDB_NOPERM;

	/*
	 * Process arguments which follow the following syntax:
	 *
	 *  symbol | numeric-address [+/- numeric-offset]
	 *  %रेजिस्टर
	 *  $environment-variable
	 */

	अगर (*nextarg > argc)
		वापस KDB_ARGCOUNT;

	symname = (अक्षर *)argv[*nextarg];

	/*
	 * If there is no whitespace between the symbol
	 * or address and the '+' or '-' symbols, we
	 * remember the अक्षरacter and replace it with a
	 * null so the symbol/value can be properly parsed
	 */
	cp = strpbrk(symname, "+-");
	अगर (cp != शून्य) अणु
		symbol = *cp;
		*cp++ = '\0';
	पूर्ण

	अगर (symname[0] == '$') अणु
		diag = kdbgetulenv(&symname[1], &addr);
		अगर (diag)
			वापस diag;
	पूर्ण अन्यथा अगर (symname[0] == '%') अणु
		diag = kdb_check_regs();
		अगर (diag)
			वापस diag;
		/* Implement रेजिस्टर values with % at a later समय as it is
		 * arch optional.
		 */
		वापस KDB_NOTIMP;
	पूर्ण अन्यथा अणु
		found = kdbमाला_लोymval(symname, &symtab);
		अगर (found) अणु
			addr = symtab.sym_start;
		पूर्ण अन्यथा अणु
			diag = kdbgetularg(argv[*nextarg], &addr);
			अगर (diag)
				वापस diag;
		पूर्ण
	पूर्ण

	अगर (!found)
		found = kdbnearsym(addr, &symtab);

	(*nextarg)++;

	अगर (name)
		*name = symname;
	अगर (value)
		*value = addr;
	अगर (offset && name && *name)
		*offset = addr - symtab.sym_start;

	अगर ((*nextarg > argc)
	 && (symbol == '\0'))
		वापस 0;

	/*
	 * check क्रम +/- and offset
	 */

	अगर (symbol == '\0') अणु
		अगर ((argv[*nextarg][0] != '+')
		 && (argv[*nextarg][0] != '-')) अणु
			/*
			 * Not our argument.  Return.
			 */
			वापस 0;
		पूर्ण अन्यथा अणु
			positive = (argv[*nextarg][0] == '+');
			(*nextarg)++;
		पूर्ण
	पूर्ण अन्यथा
		positive = (symbol == '+');

	/*
	 * Now there must be an offset!
	 */
	अगर ((*nextarg > argc)
	 && (symbol == '\0')) अणु
		वापस KDB_INVADDRFMT;
	पूर्ण

	अगर (!symbol) अणु
		cp = (अक्षर *)argv[*nextarg];
		(*nextarg)++;
	पूर्ण

	diag = kdbgetularg(cp, &off);
	अगर (diag)
		वापस diag;

	अगर (!positive)
		off = -off;

	अगर (offset)
		*offset += off;

	अगर (value)
		*value += off;

	वापस 0;
पूर्ण

अटल व्योम kdb_cmderror(पूर्णांक diag)
अणु
	पूर्णांक i;

	अगर (diag >= 0) अणु
		kdb_म_लिखो("no error detected (diagnostic is %d)\n", diag);
		वापस;
	पूर्ण

	क्रम (i = 0; i < __nkdb_err; i++) अणु
		अगर (kdbmsgs[i].km_diag == diag) अणु
			kdb_म_लिखो("diag: %d: %s\n", diag, kdbmsgs[i].km_msg);
			वापस;
		पूर्ण
	पूर्ण

	kdb_म_लिखो("Unknown diag %d\n", -diag);
पूर्ण

/*
 * kdb_defcmd, kdb_defcmd2 - This function implements the 'defcmd'
 *	command which defines one command as a set of other commands,
 *	terminated by endefcmd.  kdb_defcmd processes the initial
 *	'defcmd' command, kdb_defcmd2 is invoked from kdb_parse क्रम
 *	the following commands until 'endefcmd'.
 * Inमाला_दो:
 *	argc	argument count
 *	argv	argument vector
 * Returns:
 *	zero क्रम success, a kdb diagnostic अगर error
 */
काष्ठा defcmd_set अणु
	पूर्णांक count;
	bool usable;
	अक्षर *name;
	अक्षर *usage;
	अक्षर *help;
	अक्षर **command;
पूर्ण;
अटल काष्ठा defcmd_set *defcmd_set;
अटल पूर्णांक defcmd_set_count;
अटल bool defcmd_in_progress;

/* Forward references */
अटल पूर्णांक kdb_exec_defcmd(पूर्णांक argc, स्थिर अक्षर **argv);

अटल पूर्णांक kdb_defcmd2(स्थिर अक्षर *cmdstr, स्थिर अक्षर *argv0)
अणु
	काष्ठा defcmd_set *s = defcmd_set + defcmd_set_count - 1;
	अक्षर **save_command = s->command;
	अगर (म_भेद(argv0, "endefcmd") == 0) अणु
		defcmd_in_progress = false;
		अगर (!s->count)
			s->usable = false;
		अगर (s->usable)
			/* macros are always safe because when executed each
			 * पूर्णांकernal command re-enters kdb_parse() and is
			 * safety checked inभागidually.
			 */
			kdb_रेजिस्टर_flags(s->name, kdb_exec_defcmd, s->usage,
					   s->help, 0,
					   KDB_ENABLE_ALWAYS_SAFE);
		वापस 0;
	पूर्ण
	अगर (!s->usable)
		वापस KDB_NOTIMP;
	s->command = kसुस्मृति(s->count + 1, माप(*(s->command)), GFP_KDB);
	अगर (!s->command) अणु
		kdb_म_लिखो("Could not allocate new kdb_defcmd table for %s\n",
			   cmdstr);
		s->usable = false;
		वापस KDB_NOTIMP;
	पूर्ण
	स_नकल(s->command, save_command, s->count * माप(*(s->command)));
	s->command[s->count++] = kdb_strdup(cmdstr, GFP_KDB);
	kमुक्त(save_command);
	वापस 0;
पूर्ण

अटल पूर्णांक kdb_defcmd(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा defcmd_set *save_defcmd_set = defcmd_set, *s;
	अगर (defcmd_in_progress) अणु
		kdb_म_लिखो("kdb: nested defcmd detected, assuming missing "
			   "endefcmd\n");
		kdb_defcmd2("endefcmd", "endefcmd");
	पूर्ण
	अगर (argc == 0) अणु
		पूर्णांक i;
		क्रम (s = defcmd_set; s < defcmd_set + defcmd_set_count; ++s) अणु
			kdb_म_लिखो("defcmd %s \"%s\" \"%s\"\n", s->name,
				   s->usage, s->help);
			क्रम (i = 0; i < s->count; ++i)
				kdb_म_लिखो("%s", s->command[i]);
			kdb_म_लिखो("endefcmd\n");
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (argc != 3)
		वापस KDB_ARGCOUNT;
	अगर (in_dbg_master()) अणु
		kdb_म_लिखो("Command only available during kdb_init()\n");
		वापस KDB_NOTIMP;
	पूर्ण
	defcmd_set = kदो_स्मृति_array(defcmd_set_count + 1, माप(*defcmd_set),
				   GFP_KDB);
	अगर (!defcmd_set)
		जाओ fail_defcmd;
	स_नकल(defcmd_set, save_defcmd_set,
	       defcmd_set_count * माप(*defcmd_set));
	s = defcmd_set + defcmd_set_count;
	स_रखो(s, 0, माप(*s));
	s->usable = true;
	s->name = kdb_strdup(argv[1], GFP_KDB);
	अगर (!s->name)
		जाओ fail_name;
	s->usage = kdb_strdup(argv[2], GFP_KDB);
	अगर (!s->usage)
		जाओ fail_usage;
	s->help = kdb_strdup(argv[3], GFP_KDB);
	अगर (!s->help)
		जाओ fail_help;
	अगर (s->usage[0] == '"') अणु
		म_नकल(s->usage, argv[2]+1);
		s->usage[म_माप(s->usage)-1] = '\0';
	पूर्ण
	अगर (s->help[0] == '"') अणु
		म_नकल(s->help, argv[3]+1);
		s->help[म_माप(s->help)-1] = '\0';
	पूर्ण
	++defcmd_set_count;
	defcmd_in_progress = true;
	kमुक्त(save_defcmd_set);
	वापस 0;
fail_help:
	kमुक्त(s->usage);
fail_usage:
	kमुक्त(s->name);
fail_name:
	kमुक्त(defcmd_set);
fail_defcmd:
	kdb_म_लिखो("Could not allocate new defcmd_set entry for %s\n", argv[1]);
	defcmd_set = save_defcmd_set;
	वापस KDB_NOTIMP;
पूर्ण

/*
 * kdb_exec_defcmd - Execute the set of commands associated with this
 *	defcmd name.
 * Inमाला_दो:
 *	argc	argument count
 *	argv	argument vector
 * Returns:
 *	zero क्रम success, a kdb diagnostic अगर error
 */
अटल पूर्णांक kdb_exec_defcmd(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक i, ret;
	काष्ठा defcmd_set *s;
	अगर (argc != 0)
		वापस KDB_ARGCOUNT;
	क्रम (s = defcmd_set, i = 0; i < defcmd_set_count; ++i, ++s) अणु
		अगर (म_भेद(s->name, argv[0]) == 0)
			अवरोध;
	पूर्ण
	अगर (i == defcmd_set_count) अणु
		kdb_म_लिखो("kdb_exec_defcmd: could not find commands for %s\n",
			   argv[0]);
		वापस KDB_NOTIMP;
	पूर्ण
	क्रम (i = 0; i < s->count; ++i) अणु
		/* Recursive use of kdb_parse, करो not use argv after
		 * this poपूर्णांक */
		argv = शून्य;
		kdb_म_लिखो("[%s]kdb> %s\n", s->name, s->command[i]);
		ret = kdb_parse(s->command[i]);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* Command history */
#घोषणा KDB_CMD_HISTORY_COUNT	32
#घोषणा CMD_BUFLEN		200	/* kdb_म_लिखो: max prपूर्णांकline
					 * size == 256 */
अटल अचिन्हित पूर्णांक cmd_head, cmd_tail;
अटल अचिन्हित पूर्णांक cmdptr;
अटल अक्षर cmd_hist[KDB_CMD_HISTORY_COUNT][CMD_BUFLEN];
अटल अक्षर cmd_cur[CMD_BUFLEN];

/*
 * The "str" argument may poपूर्णांक to something like  | grep xyz
 */
अटल व्योम parse_grep(स्थिर अक्षर *str)
अणु
	पूर्णांक	len;
	अक्षर	*cp = (अक्षर *)str, *cp2;

	/* sanity check: we should have been called with the \ first */
	अगर (*cp != '|')
		वापस;
	cp++;
	जबतक (है_खाली(*cp))
		cp++;
	अगर (!str_has_prefix(cp, "grep ")) अणु
		kdb_म_लिखो("invalid 'pipe', see grephelp\n");
		वापस;
	पूर्ण
	cp += 5;
	जबतक (है_खाली(*cp))
		cp++;
	cp2 = म_अक्षर(cp, '\n');
	अगर (cp2)
		*cp2 = '\0'; /* हटाओ the trailing newline */
	len = म_माप(cp);
	अगर (len == 0) अणु
		kdb_म_लिखो("invalid 'pipe', see grephelp\n");
		वापस;
	पूर्ण
	/* now cp poपूर्णांकs to a nonzero length search string */
	अगर (*cp == '"') अणु
		/* allow it be "x y z" by removing the "'s - there must
		   be two of them */
		cp++;
		cp2 = म_अक्षर(cp, '"');
		अगर (!cp2) अणु
			kdb_म_लिखो("invalid quoted string, see grephelp\n");
			वापस;
		पूर्ण
		*cp2 = '\0'; /* end the string where the 2nd " was */
	पूर्ण
	kdb_grep_leading = 0;
	अगर (*cp == '^') अणु
		kdb_grep_leading = 1;
		cp++;
	पूर्ण
	len = म_माप(cp);
	kdb_grep_trailing = 0;
	अगर (*(cp+len-1) == '$') अणु
		kdb_grep_trailing = 1;
		*(cp+len-1) = '\0';
	पूर्ण
	len = म_माप(cp);
	अगर (!len)
		वापस;
	अगर (len >= KDB_GREP_STRLEN) अणु
		kdb_म_लिखो("search string too long\n");
		वापस;
	पूर्ण
	म_नकल(kdb_grep_string, cp);
	kdb_grepping_flag++;
	वापस;
पूर्ण

/*
 * kdb_parse - Parse the command line, search the command table क्रम a
 *	matching command and invoke the command function.  This
 *	function may be called recursively, अगर it is, the second call
 *	will overग_लिखो argv and cbuf.  It is the caller's
 *	responsibility to save their argv अगर they recursively call
 *	kdb_parse().
 * Parameters:
 *      cmdstr	The input command line to be parsed.
 *	regs	The रेजिस्टरs at the समय kdb was entered.
 * Returns:
 *	Zero क्रम success, a kdb diagnostic अगर failure.
 * Remarks:
 *	Limited to 20 tokens.
 *
 *	Real rudimentary tokenization. Basically only whitespace
 *	is considered a token delimeter (but special consideration
 *	is taken of the '=' sign as used by the 'set' command).
 *
 *	The algorithm used to tokenize the input string relies on
 *	there being at least one whitespace (or otherwise useless)
 *	अक्षरacter between tokens as the अक्षरacter immediately following
 *	the token is altered in-place to a null-byte to terminate the
 *	token string.
 */

#घोषणा MAXARGC	20

पूर्णांक kdb_parse(स्थिर अक्षर *cmdstr)
अणु
	अटल अक्षर *argv[MAXARGC];
	अटल पूर्णांक argc;
	अटल अक्षर cbuf[CMD_BUFLEN+2];
	अक्षर *cp;
	अक्षर *cpp, quoted;
	kdbtab_t *tp;
	पूर्णांक escaped, ignore_errors = 0, check_grep = 0;

	/*
	 * First tokenize the command string.
	 */
	cp = (अक्षर *)cmdstr;

	अगर (KDB_FLAG(CMD_INTERRUPT)) अणु
		/* Previous command was पूर्णांकerrupted, newline must not
		 * repeat the command */
		KDB_FLAG_CLEAR(CMD_INTERRUPT);
		KDB_STATE_SET(PAGER);
		argc = 0;	/* no repeat */
	पूर्ण

	अगर (*cp != '\n' && *cp != '\0') अणु
		argc = 0;
		cpp = cbuf;
		जबतक (*cp) अणु
			/* skip whitespace */
			जबतक (है_खाली(*cp))
				cp++;
			अगर ((*cp == '\0') || (*cp == '\n') ||
			    (*cp == '#' && !defcmd_in_progress))
				अवरोध;
			/* special हाल: check क्रम | grep pattern */
			अगर (*cp == '|') अणु
				check_grep++;
				अवरोध;
			पूर्ण
			अगर (cpp >= cbuf + CMD_BUFLEN) अणु
				kdb_म_लिखो("kdb_parse: command buffer "
					   "overflow, command ignored\n%s\n",
					   cmdstr);
				वापस KDB_NOTFOUND;
			पूर्ण
			अगर (argc >= MAXARGC - 1) अणु
				kdb_म_लिखो("kdb_parse: too many arguments, "
					   "command ignored\n%s\n", cmdstr);
				वापस KDB_NOTFOUND;
			पूर्ण
			argv[argc++] = cpp;
			escaped = 0;
			quoted = '\0';
			/* Copy to next unquoted and unescaped
			 * whitespace or '=' */
			जबतक (*cp && *cp != '\n' &&
			       (escaped || quoted || !है_खाली(*cp))) अणु
				अगर (cpp >= cbuf + CMD_BUFLEN)
					अवरोध;
				अगर (escaped) अणु
					escaped = 0;
					*cpp++ = *cp++;
					जारी;
				पूर्ण
				अगर (*cp == '\\') अणु
					escaped = 1;
					++cp;
					जारी;
				पूर्ण
				अगर (*cp == quoted)
					quoted = '\0';
				अन्यथा अगर (*cp == '\'' || *cp == '"')
					quoted = *cp;
				*cpp = *cp++;
				अगर (*cpp == '=' && !quoted)
					अवरोध;
				++cpp;
			पूर्ण
			*cpp++ = '\0';	/* Squash a ws or '=' अक्षरacter */
		पूर्ण
	पूर्ण
	अगर (!argc)
		वापस 0;
	अगर (check_grep)
		parse_grep(cp);
	अगर (defcmd_in_progress) अणु
		पूर्णांक result = kdb_defcmd2(cmdstr, argv[0]);
		अगर (!defcmd_in_progress) अणु
			argc = 0;	/* aव्योम repeat on endefcmd */
			*(argv[0]) = '\0';
		पूर्ण
		वापस result;
	पूर्ण
	अगर (argv[0][0] == '-' && argv[0][1] &&
	    (argv[0][1] < '0' || argv[0][1] > '9')) अणु
		ignore_errors = 1;
		++argv[0];
	पूर्ण

	list_क्रम_each_entry(tp, &kdb_cmds_head, list_node) अणु
		/*
		 * If this command is allowed to be abbreviated,
		 * check to see अगर this is it.
		 */
		अगर (tp->cmd_minlen && (म_माप(argv[0]) <= tp->cmd_minlen) &&
		    (म_भेदन(argv[0], tp->cmd_name, tp->cmd_minlen) == 0))
			अवरोध;

		अगर (म_भेद(argv[0], tp->cmd_name) == 0)
			अवरोध;
	पूर्ण

	/*
	 * If we करोn't find a command by this name, see अगर the first
	 * few अक्षरacters of this match any of the known commands.
	 * e.g., md1c20 should match md.
	 */
	अगर (list_entry_is_head(tp, &kdb_cmds_head, list_node)) अणु
		list_क्रम_each_entry(tp, &kdb_cmds_head, list_node) अणु
			अगर (म_भेदन(argv[0], tp->cmd_name,
				    म_माप(tp->cmd_name)) == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (!list_entry_is_head(tp, &kdb_cmds_head, list_node)) अणु
		पूर्णांक result;

		अगर (!kdb_check_flags(tp->cmd_flags, kdb_cmd_enabled, argc <= 1))
			वापस KDB_NOPERM;

		KDB_STATE_SET(CMD);
		result = (*tp->cmd_func)(argc-1, (स्थिर अक्षर **)argv);
		अगर (result && ignore_errors && result > KDB_CMD_GO)
			result = 0;
		KDB_STATE_CLEAR(CMD);

		अगर (tp->cmd_flags & KDB_REPEAT_WITH_ARGS)
			वापस result;

		argc = tp->cmd_flags & KDB_REPEAT_NO_ARGS ? 1 : 0;
		अगर (argv[argc])
			*(argv[argc]) = '\0';
		वापस result;
	पूर्ण

	/*
	 * If the input with which we were presented करोes not
	 * map to an existing command, attempt to parse it as an
	 * address argument and display the result.   Useful क्रम
	 * obtaining the address of a variable, or the nearest symbol
	 * to an address contained in a रेजिस्टर.
	 */
	अणु
		अचिन्हित दीर्घ value;
		अक्षर *name = शून्य;
		दीर्घ offset;
		पूर्णांक nextarg = 0;

		अगर (kdbgetaddrarg(0, (स्थिर अक्षर **)argv, &nextarg,
				  &value, &offset, &name)) अणु
			वापस KDB_NOTFOUND;
		पूर्ण

		kdb_म_लिखो("%s = ", argv[0]);
		kdb_symbol_prपूर्णांक(value, शून्य, KDB_SP_DEFAULT);
		kdb_म_लिखो("\n");
		वापस 0;
	पूर्ण
पूर्ण


अटल पूर्णांक handle_ctrl_cmd(अक्षर *cmd)
अणु
#घोषणा CTRL_P	16
#घोषणा CTRL_N	14

	/* initial situation */
	अगर (cmd_head == cmd_tail)
		वापस 0;
	चयन (*cmd) अणु
	हाल CTRL_P:
		अगर (cmdptr != cmd_tail)
			cmdptr = (cmdptr + KDB_CMD_HISTORY_COUNT - 1) %
				 KDB_CMD_HISTORY_COUNT;
		strscpy(cmd_cur, cmd_hist[cmdptr], CMD_BUFLEN);
		वापस 1;
	हाल CTRL_N:
		अगर (cmdptr != cmd_head)
			cmdptr = (cmdptr+1) % KDB_CMD_HISTORY_COUNT;
		strscpy(cmd_cur, cmd_hist[cmdptr], CMD_BUFLEN);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * kdb_reboot - This function implements the 'reboot' command.  Reboot
 *	the प्रणाली immediately, or loop क्रम ever on failure.
 */
अटल पूर्णांक kdb_reboot(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	emergency_restart();
	kdb_म_लिखो("Hmm, kdb_reboot did not reboot, spinning here\n");
	जबतक (1)
		cpu_relax();
	/* NOTREACHED */
	वापस 0;
पूर्ण

अटल व्योम kdb_dumpregs(काष्ठा pt_regs *regs)
अणु
	पूर्णांक old_lvl = console_loglevel;
	console_loglevel = CONSOLE_LOGLEVEL_MOTORMOUTH;
	kdb_trap_prपूर्णांकk++;
	show_regs(regs);
	kdb_trap_prपूर्णांकk--;
	kdb_म_लिखो("\n");
	console_loglevel = old_lvl;
पूर्ण

अटल व्योम kdb_set_current_task(काष्ठा task_काष्ठा *p)
अणु
	kdb_current_task = p;

	अगर (kdb_task_has_cpu(p)) अणु
		kdb_current_regs = KDB_TSKREGS(kdb_process_cpu(p));
		वापस;
	पूर्ण
	kdb_current_regs = शून्य;
पूर्ण

अटल व्योम drop_newline(अक्षर *buf)
अणु
	माप_प्रकार len = म_माप(buf);

	अगर (len == 0)
		वापस;
	अगर (*(buf + len - 1) == '\n')
		*(buf + len - 1) = '\0';
पूर्ण

/*
 * kdb_local - The मुख्य code क्रम kdb.  This routine is invoked on a
 *	specअगरic processor, it is not global.  The मुख्य kdb() routine
 *	ensures that only one processor at a समय is in this routine.
 *	This code is called with the real reason code on the first
 *	entry to a kdb session, thereafter it is called with reason
 *	SWITCH, even अगर the user goes back to the original cpu.
 * Inमाला_दो:
 *	reason		The reason KDB was invoked
 *	error		The hardware-defined error code
 *	regs		The exception frame at समय of fault/अवरोधpoपूर्णांक.
 *	db_result	Result code from the अवरोध or debug poपूर्णांक.
 * Returns:
 *	0	KDB was invoked क्रम an event which it wasn't responsible
 *	1	KDB handled the event क्रम which it was invoked.
 *	KDB_CMD_GO	User typed 'go'.
 *	KDB_CMD_CPU	User चयनed to another cpu.
 *	KDB_CMD_SS	Single step.
 */
अटल पूर्णांक kdb_local(kdb_reason_t reason, पूर्णांक error, काष्ठा pt_regs *regs,
		     kdb_dbtrap_t db_result)
अणु
	अक्षर *cmdbuf;
	पूर्णांक diag;
	काष्ठा task_काष्ठा *kdb_current =
		kdb_curr_task(raw_smp_processor_id());

	KDB_DEBUG_STATE("kdb_local 1", reason);
	kdb_go_count = 0;
	अगर (reason == KDB_REASON_DEBUG) अणु
		/* special हाल below */
	पूर्ण अन्यथा अणु
		kdb_म_लिखो("\nEntering kdb (current=0x%px, pid %d) ",
			   kdb_current, kdb_current ? kdb_current->pid : 0);
#अगर defined(CONFIG_SMP)
		kdb_म_लिखो("on processor %d ", raw_smp_processor_id());
#पूर्ण_अगर
	पूर्ण

	चयन (reason) अणु
	हाल KDB_REASON_DEBUG:
	अणु
		/*
		 * If re-entering kdb after a single step
		 * command, करोn't prपूर्णांक the message.
		 */
		चयन (db_result) अणु
		हाल KDB_DB_BPT:
			kdb_म_लिखो("\nEntering kdb (0x%px, pid %d) ",
				   kdb_current, kdb_current->pid);
#अगर defined(CONFIG_SMP)
			kdb_म_लिखो("on processor %d ", raw_smp_processor_id());
#पूर्ण_अगर
			kdb_म_लिखो("due to Debug @ " kdb_machreg_fmt "\n",
				   inकाष्ठाion_poपूर्णांकer(regs));
			अवरोध;
		हाल KDB_DB_SS:
			अवरोध;
		हाल KDB_DB_SSBPT:
			KDB_DEBUG_STATE("kdb_local 4", reason);
			वापस 1;	/* kdba_db_trap did the work */
		शेष:
			kdb_म_लिखो("kdb: Bad result from kdba_db_trap: %d\n",
				   db_result);
			अवरोध;
		पूर्ण

	पूर्ण
		अवरोध;
	हाल KDB_REASON_ENTER:
		अगर (KDB_STATE(KEYBOARD))
			kdb_म_लिखो("due to Keyboard Entry\n");
		अन्यथा
			kdb_म_लिखो("due to KDB_ENTER()\n");
		अवरोध;
	हाल KDB_REASON_KEYBOARD:
		KDB_STATE_SET(KEYBOARD);
		kdb_म_लिखो("due to Keyboard Entry\n");
		अवरोध;
	हाल KDB_REASON_ENTER_SLAVE:
		/* drop through, slaves only get released via cpu चयन */
	हाल KDB_REASON_SWITCH:
		kdb_म_लिखो("due to cpu switch\n");
		अवरोध;
	हाल KDB_REASON_OOPS:
		kdb_म_लिखो("Oops: %s\n", kdb_diemsg);
		kdb_म_लिखो("due to oops @ " kdb_machreg_fmt "\n",
			   inकाष्ठाion_poपूर्णांकer(regs));
		kdb_dumpregs(regs);
		अवरोध;
	हाल KDB_REASON_SYSTEM_NMI:
		kdb_म_लिखो("due to System NonMaskable Interrupt\n");
		अवरोध;
	हाल KDB_REASON_NMI:
		kdb_म_लिखो("due to NonMaskable Interrupt @ "
			   kdb_machreg_fmt "\n",
			   inकाष्ठाion_poपूर्णांकer(regs));
		अवरोध;
	हाल KDB_REASON_SSTEP:
	हाल KDB_REASON_BREAK:
		kdb_म_लिखो("due to %s @ " kdb_machreg_fmt "\n",
			   reason == KDB_REASON_BREAK ?
			   "Breakpoint" : "SS trap", inकाष्ठाion_poपूर्णांकer(regs));
		/*
		 * Determine अगर this अवरोधpoपूर्णांक is one that we
		 * are पूर्णांकerested in.
		 */
		अगर (db_result != KDB_DB_BPT) अणु
			kdb_म_लिखो("kdb: error return from kdba_bp_trap: %d\n",
				   db_result);
			KDB_DEBUG_STATE("kdb_local 6", reason);
			वापस 0;	/* Not क्रम us, dismiss it */
		पूर्ण
		अवरोध;
	हाल KDB_REASON_RECURSE:
		kdb_म_लिखो("due to Recursion @ " kdb_machreg_fmt "\n",
			   inकाष्ठाion_poपूर्णांकer(regs));
		अवरोध;
	शेष:
		kdb_म_लिखो("kdb: unexpected reason code: %d\n", reason);
		KDB_DEBUG_STATE("kdb_local 8", reason);
		वापस 0;	/* Not क्रम us, dismiss it */
	पूर्ण

	जबतक (1) अणु
		/*
		 * Initialize pager context.
		 */
		kdb_nextline = 1;
		KDB_STATE_CLEAR(SUPPRESS);
		kdb_grepping_flag = 0;
		/* ensure the old search करोes not leak पूर्णांकo '/' commands */
		kdb_grep_string[0] = '\0';

		cmdbuf = cmd_cur;
		*cmdbuf = '\0';
		*(cmd_hist[cmd_head]) = '\0';

करो_full_माला_लोtr:
		/* PROMPT can only be set अगर we have MEM_READ permission. */
		snम_लिखो(kdb_prompt_str, CMD_BUFLEN, kdbदो_पर्या("PROMPT"),
			 raw_smp_processor_id());
		अगर (defcmd_in_progress)
			म_जोड़न(kdb_prompt_str, "[defcmd]", CMD_BUFLEN);

		/*
		 * Fetch command from keyboard
		 */
		cmdbuf = kdb_माला_लोtr(cmdbuf, CMD_BUFLEN, kdb_prompt_str);
		अगर (*cmdbuf != '\n') अणु
			अगर (*cmdbuf < 32) अणु
				अगर (cmdptr == cmd_head) अणु
					strscpy(cmd_hist[cmd_head], cmd_cur,
						CMD_BUFLEN);
					*(cmd_hist[cmd_head] +
					  म_माप(cmd_hist[cmd_head])-1) = '\0';
				पूर्ण
				अगर (!handle_ctrl_cmd(cmdbuf))
					*(cmd_cur+म_माप(cmd_cur)-1) = '\0';
				cmdbuf = cmd_cur;
				जाओ करो_full_माला_लोtr;
			पूर्ण अन्यथा अणु
				strscpy(cmd_hist[cmd_head], cmd_cur,
					CMD_BUFLEN);
			पूर्ण

			cmd_head = (cmd_head+1) % KDB_CMD_HISTORY_COUNT;
			अगर (cmd_head == cmd_tail)
				cmd_tail = (cmd_tail+1) % KDB_CMD_HISTORY_COUNT;
		पूर्ण

		cmdptr = cmd_head;
		diag = kdb_parse(cmdbuf);
		अगर (diag == KDB_NOTFOUND) अणु
			drop_newline(cmdbuf);
			kdb_म_लिखो("Unknown kdb command: '%s'\n", cmdbuf);
			diag = 0;
		पूर्ण
		अगर (diag == KDB_CMD_GO
		 || diag == KDB_CMD_CPU
		 || diag == KDB_CMD_SS
		 || diag == KDB_CMD_KGDB)
			अवरोध;

		अगर (diag)
			kdb_cmderror(diag);
	पूर्ण
	KDB_DEBUG_STATE("kdb_local 9", diag);
	वापस diag;
पूर्ण


/*
 * kdb_prपूर्णांक_state - Prपूर्णांक the state data क्रम the current processor
 *	क्रम debugging.
 * Inमाला_दो:
 *	text		Identअगरies the debug poपूर्णांक
 *	value		Any पूर्णांकeger value to be prपूर्णांकed, e.g. reason code.
 */
व्योम kdb_prपूर्णांक_state(स्थिर अक्षर *text, पूर्णांक value)
अणु
	kdb_म_लिखो("state: %s cpu %d value %d initial %d state %x\n",
		   text, raw_smp_processor_id(), value, kdb_initial_cpu,
		   kdb_state);
पूर्ण

/*
 * kdb_मुख्य_loop - After initial setup and assignment of the
 *	controlling cpu, all cpus are in this loop.  One cpu is in
 *	control and will issue the kdb prompt, the others will spin
 *	until 'go' or cpu चयन.
 *
 *	To get a consistent view of the kernel stacks क्रम all
 *	processes, this routine is invoked from the मुख्य kdb code via
 *	an architecture specअगरic routine.  kdba_मुख्य_loop is
 *	responsible क्रम making the kernel stacks consistent क्रम all
 *	processes, there should be no dअगरference between a blocked
 *	process and a running process as far as kdb is concerned.
 * Inमाला_दो:
 *	reason		The reason KDB was invoked
 *	error		The hardware-defined error code
 *	reason2		kdb's current reason code.
 *			Initially error but can change
 *			according to kdb state.
 *	db_result	Result code from अवरोध or debug poपूर्णांक.
 *	regs		The exception frame at समय of fault/अवरोधpoपूर्णांक.
 *			should always be valid.
 * Returns:
 *	0	KDB was invoked क्रम an event which it wasn't responsible
 *	1	KDB handled the event क्रम which it was invoked.
 */
पूर्णांक kdb_मुख्य_loop(kdb_reason_t reason, kdb_reason_t reason2, पूर्णांक error,
	      kdb_dbtrap_t db_result, काष्ठा pt_regs *regs)
अणु
	पूर्णांक result = 1;
	/* Stay in kdb() until 'go', 'ss[b]' or an error */
	जबतक (1) अणु
		/*
		 * All processors except the one that is in control
		 * will spin here.
		 */
		KDB_DEBUG_STATE("kdb_main_loop 1", reason);
		जबतक (KDB_STATE(HOLD_CPU)) अणु
			/* state KDB is turned off by kdb_cpu to see अगर the
			 * other cpus are still live, each cpu in this loop
			 * turns it back on.
			 */
			अगर (!KDB_STATE(KDB))
				KDB_STATE_SET(KDB);
		पूर्ण

		KDB_STATE_CLEAR(SUPPRESS);
		KDB_DEBUG_STATE("kdb_main_loop 2", reason);
		अगर (KDB_STATE(LEAVING))
			अवरोध;	/* Another cpu said 'go' */
		/* Still using kdb, this processor is in control */
		result = kdb_local(reason2, error, regs, db_result);
		KDB_DEBUG_STATE("kdb_main_loop 3", result);

		अगर (result == KDB_CMD_CPU)
			अवरोध;

		अगर (result == KDB_CMD_SS) अणु
			KDB_STATE_SET(DOING_SS);
			अवरोध;
		पूर्ण

		अगर (result == KDB_CMD_KGDB) अणु
			अगर (!KDB_STATE(DOING_KGDB))
				kdb_म_लिखो("Entering please attach debugger "
					   "or use $D#44+ or $3#33\n");
			अवरोध;
		पूर्ण
		अगर (result && result != 1 && result != KDB_CMD_GO)
			kdb_म_लिखो("\nUnexpected kdb_local return code %d\n",
				   result);
		KDB_DEBUG_STATE("kdb_main_loop 4", reason);
		अवरोध;
	पूर्ण
	अगर (KDB_STATE(DOING_SS))
		KDB_STATE_CLEAR(SSBPT);

	/* Clean up any keyboard devices beक्रमe leaving */
	kdb_kbd_cleanup_state();

	वापस result;
पूर्ण

/*
 * kdb_mdr - This function implements the guts of the 'mdr', memory
 * पढ़ो command.
 *	mdr  <addr arg>,<byte count>
 * Inमाला_दो:
 *	addr	Start address
 *	count	Number of bytes
 * Returns:
 *	Always 0.  Any errors are detected and prपूर्णांकed by kdb_getarea.
 */
अटल पूर्णांक kdb_mdr(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित अक्षर c;
	जबतक (count--) अणु
		अगर (kdb_getarea(c, addr))
			वापस 0;
		kdb_म_लिखो("%02x", c);
		addr++;
	पूर्ण
	kdb_म_लिखो("\n");
	वापस 0;
पूर्ण

/*
 * kdb_md - This function implements the 'md', 'md1', 'md2', 'md4',
 *	'md8' 'mdr' and 'mds' commands.
 *
 *	md|mds  [<addr arg> [<line count> [<radix>]]]
 *	mdWcN	[<addr arg> [<line count> [<radix>]]]
 *		where W = is the width (1, 2, 4 or 8) and N is the count.
 *		क्रम eg., md1c20 पढ़ोs 20 bytes, 1 at a समय.
 *	mdr  <addr arg>,<byte count>
 */
अटल व्योम kdb_md_line(स्थिर अक्षर *fmtstr, अचिन्हित दीर्घ addr,
			पूर्णांक symbolic, पूर्णांक nosect, पूर्णांक bytesperword,
			पूर्णांक num, पूर्णांक repeat, पूर्णांक phys)
अणु
	/* prपूर्णांक just one line of data */
	kdb_symtab_t symtab;
	अक्षर cbuf[32];
	अक्षर *c = cbuf;
	पूर्णांक i;
	पूर्णांक j;
	अचिन्हित दीर्घ word;

	स_रखो(cbuf, '\0', माप(cbuf));
	अगर (phys)
		kdb_म_लिखो("phys " kdb_machreg_fmt0 " ", addr);
	अन्यथा
		kdb_म_लिखो(kdb_machreg_fmt0 " ", addr);

	क्रम (i = 0; i < num && repeat--; i++) अणु
		अगर (phys) अणु
			अगर (kdb_getphysword(&word, addr, bytesperword))
				अवरोध;
		पूर्ण अन्यथा अगर (kdb_getword(&word, addr, bytesperword))
			अवरोध;
		kdb_म_लिखो(fmtstr, word);
		अगर (symbolic)
			kdbnearsym(word, &symtab);
		अन्यथा
			स_रखो(&symtab, 0, माप(symtab));
		अगर (symtab.sym_name) अणु
			kdb_symbol_prपूर्णांक(word, &symtab, 0);
			अगर (!nosect) अणु
				kdb_म_लिखो("\n");
				kdb_म_लिखो("                       %s %s "
					   kdb_machreg_fmt " "
					   kdb_machreg_fmt " "
					   kdb_machreg_fmt, symtab.mod_name,
					   symtab.sec_name, symtab.sec_start,
					   symtab.sym_start, symtab.sym_end);
			पूर्ण
			addr += bytesperword;
		पूर्ण अन्यथा अणु
			जोड़ अणु
				u64 word;
				अचिन्हित अक्षर c[8];
			पूर्ण wc;
			अचिन्हित अक्षर *cp;
#अगर_घोषित	__BIG_ENDIAN
			cp = wc.c + 8 - bytesperword;
#अन्यथा
			cp = wc.c;
#पूर्ण_अगर
			wc.word = word;
#घोषणा prपूर्णांकable_अक्षर(c) \
	(अणुअचिन्हित अक्षर __c = c; isascii(__c) && है_छाप(__c) ? __c : '.'; पूर्ण)
			क्रम (j = 0; j < bytesperword; j++)
				*c++ = prपूर्णांकable_अक्षर(*cp++);
			addr += bytesperword;
#अघोषित prपूर्णांकable_अक्षर
		पूर्ण
	पूर्ण
	kdb_म_लिखो("%*s %s\n", (पूर्णांक)((num-i)*(2*bytesperword + 1)+1),
		   " ", cbuf);
पूर्ण

अटल पूर्णांक kdb_md(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अटल अचिन्हित दीर्घ last_addr;
	अटल पूर्णांक last_radix, last_bytesperword, last_repeat;
	पूर्णांक radix = 16, mdcount = 8, bytesperword = KDB_WORD_SIZE, repeat;
	पूर्णांक nosect = 0;
	अक्षर fmtअक्षर, fmtstr[64];
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ word;
	दीर्घ offset = 0;
	पूर्णांक symbolic = 0;
	पूर्णांक valid = 0;
	पूर्णांक phys = 0;
	पूर्णांक raw = 0;

	kdbgetपूर्णांकenv("MDCOUNT", &mdcount);
	kdbgetपूर्णांकenv("RADIX", &radix);
	kdbgetपूर्णांकenv("BYTESPERWORD", &bytesperword);

	/* Assume 'md <addr>' and start with environment values */
	repeat = mdcount * 16 / bytesperword;

	अगर (म_भेद(argv[0], "mdr") == 0) अणु
		अगर (argc == 2 || (argc == 0 && last_addr != 0))
			valid = raw = 1;
		अन्यथा
			वापस KDB_ARGCOUNT;
	पूर्ण अन्यथा अगर (है_अंक(argv[0][2])) अणु
		bytesperword = (पूर्णांक)(argv[0][2] - '0');
		अगर (bytesperword == 0) अणु
			bytesperword = last_bytesperword;
			अगर (bytesperword == 0)
				bytesperword = 4;
		पूर्ण
		last_bytesperword = bytesperword;
		repeat = mdcount * 16 / bytesperword;
		अगर (!argv[0][3])
			valid = 1;
		अन्यथा अगर (argv[0][3] == 'c' && argv[0][4]) अणु
			अक्षर *p;
			repeat = simple_म_से_अदीर्घ(argv[0] + 4, &p, 10);
			mdcount = ((repeat * bytesperword) + 15) / 16;
			valid = !*p;
		पूर्ण
		last_repeat = repeat;
	पूर्ण अन्यथा अगर (म_भेद(argv[0], "md") == 0)
		valid = 1;
	अन्यथा अगर (म_भेद(argv[0], "mds") == 0)
		valid = 1;
	अन्यथा अगर (म_भेद(argv[0], "mdp") == 0) अणु
		phys = valid = 1;
	पूर्ण
	अगर (!valid)
		वापस KDB_NOTFOUND;

	अगर (argc == 0) अणु
		अगर (last_addr == 0)
			वापस KDB_ARGCOUNT;
		addr = last_addr;
		radix = last_radix;
		bytesperword = last_bytesperword;
		repeat = last_repeat;
		अगर (raw)
			mdcount = repeat;
		अन्यथा
			mdcount = ((repeat * bytesperword) + 15) / 16;
	पूर्ण

	अगर (argc) अणु
		अचिन्हित दीर्घ val;
		पूर्णांक diag, nextarg = 1;
		diag = kdbgetaddrarg(argc, argv, &nextarg, &addr,
				     &offset, शून्य);
		अगर (diag)
			वापस diag;
		अगर (argc > nextarg+2)
			वापस KDB_ARGCOUNT;

		अगर (argc >= nextarg) अणु
			diag = kdbgetularg(argv[nextarg], &val);
			अगर (!diag) अणु
				mdcount = (पूर्णांक) val;
				अगर (raw)
					repeat = mdcount;
				अन्यथा
					repeat = mdcount * 16 / bytesperword;
			पूर्ण
		पूर्ण
		अगर (argc >= nextarg+1) अणु
			diag = kdbgetularg(argv[nextarg+1], &val);
			अगर (!diag)
				radix = (पूर्णांक) val;
		पूर्ण
	पूर्ण

	अगर (म_भेद(argv[0], "mdr") == 0) अणु
		पूर्णांक ret;
		last_addr = addr;
		ret = kdb_mdr(addr, mdcount);
		last_addr += mdcount;
		last_repeat = mdcount;
		last_bytesperword = bytesperword; // to make REPEAT happy
		वापस ret;
	पूर्ण

	चयन (radix) अणु
	हाल 10:
		fmtअक्षर = 'd';
		अवरोध;
	हाल 16:
		fmtअक्षर = 'x';
		अवरोध;
	हाल 8:
		fmtअक्षर = 'o';
		अवरोध;
	शेष:
		वापस KDB_BADRADIX;
	पूर्ण

	last_radix = radix;

	अगर (bytesperword > KDB_WORD_SIZE)
		वापस KDB_BADWIDTH;

	चयन (bytesperword) अणु
	हाल 8:
		प्र_लिखो(fmtstr, "%%16.16l%c ", fmtअक्षर);
		अवरोध;
	हाल 4:
		प्र_लिखो(fmtstr, "%%8.8l%c ", fmtअक्षर);
		अवरोध;
	हाल 2:
		प्र_लिखो(fmtstr, "%%4.4l%c ", fmtअक्षर);
		अवरोध;
	हाल 1:
		प्र_लिखो(fmtstr, "%%2.2l%c ", fmtअक्षर);
		अवरोध;
	शेष:
		वापस KDB_BADWIDTH;
	पूर्ण

	last_repeat = repeat;
	last_bytesperword = bytesperword;

	अगर (म_भेद(argv[0], "mds") == 0) अणु
		symbolic = 1;
		/* Do not save these changes as last_*, they are temporary mds
		 * overrides.
		 */
		bytesperword = KDB_WORD_SIZE;
		repeat = mdcount;
		kdbgetपूर्णांकenv("NOSECT", &nosect);
	पूर्ण

	/* Round address करोwn modulo BYTESPERWORD */

	addr &= ~(bytesperword-1);

	जबतक (repeat > 0) अणु
		अचिन्हित दीर्घ a;
		पूर्णांक n, z, num = (symbolic ? 1 : (16 / bytesperword));

		अगर (KDB_FLAG(CMD_INTERRUPT))
			वापस 0;
		क्रम (a = addr, z = 0; z < repeat; a += bytesperword, ++z) अणु
			अगर (phys) अणु
				अगर (kdb_getphysword(&word, a, bytesperword)
						|| word)
					अवरोध;
			पूर्ण अन्यथा अगर (kdb_getword(&word, a, bytesperword) || word)
				अवरोध;
		पूर्ण
		n = min(num, repeat);
		kdb_md_line(fmtstr, addr, symbolic, nosect, bytesperword,
			    num, repeat, phys);
		addr += bytesperword * n;
		repeat -= n;
		z = (z + num - 1) / num;
		अगर (z > 2) अणु
			पूर्णांक s = num * (z-2);
			kdb_म_लिखो(kdb_machreg_fmt0 "-" kdb_machreg_fmt0
				   " zero suppressed\n",
				addr, addr + bytesperword * s - 1);
			addr += bytesperword * s;
			repeat -= s;
		पूर्ण
	पूर्ण
	last_addr = addr;

	वापस 0;
पूर्ण

/*
 * kdb_mm - This function implements the 'mm' command.
 *	mm address-expression new-value
 * Remarks:
 *	mm works on machine words, mmW works on bytes.
 */
अटल पूर्णांक kdb_mm(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक diag;
	अचिन्हित दीर्घ addr;
	दीर्घ offset = 0;
	अचिन्हित दीर्घ contents;
	पूर्णांक nextarg;
	पूर्णांक width;

	अगर (argv[0][2] && !है_अंक(argv[0][2]))
		वापस KDB_NOTFOUND;

	अगर (argc < 2)
		वापस KDB_ARGCOUNT;

	nextarg = 1;
	diag = kdbgetaddrarg(argc, argv, &nextarg, &addr, &offset, शून्य);
	अगर (diag)
		वापस diag;

	अगर (nextarg > argc)
		वापस KDB_ARGCOUNT;
	diag = kdbgetaddrarg(argc, argv, &nextarg, &contents, शून्य, शून्य);
	अगर (diag)
		वापस diag;

	अगर (nextarg != argc + 1)
		वापस KDB_ARGCOUNT;

	width = argv[0][2] ? (argv[0][2] - '0') : (KDB_WORD_SIZE);
	diag = kdb_putword(addr, contents, width);
	अगर (diag)
		वापस diag;

	kdb_म_लिखो(kdb_machreg_fmt " = " kdb_machreg_fmt "\n", addr, contents);

	वापस 0;
पूर्ण

/*
 * kdb_go - This function implements the 'go' command.
 *	go [address-expression]
 */
अटल पूर्णांक kdb_go(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अचिन्हित दीर्घ addr;
	पूर्णांक diag;
	पूर्णांक nextarg;
	दीर्घ offset;

	अगर (raw_smp_processor_id() != kdb_initial_cpu) अणु
		kdb_म_लिखो("go must execute on the entry cpu, "
			   "please use \"cpu %d\" and then execute go\n",
			   kdb_initial_cpu);
		वापस KDB_BADCPUNUM;
	पूर्ण
	अगर (argc == 1) अणु
		nextarg = 1;
		diag = kdbgetaddrarg(argc, argv, &nextarg,
				     &addr, &offset, शून्य);
		अगर (diag)
			वापस diag;
	पूर्ण अन्यथा अगर (argc) अणु
		वापस KDB_ARGCOUNT;
	पूर्ण

	diag = KDB_CMD_GO;
	अगर (KDB_FLAG(CATASTROPHIC)) अणु
		kdb_म_लिखो("Catastrophic error detected\n");
		kdb_म_लिखो("kdb_continue_catastrophic=%d, ",
			kdb_जारी_catastrophic);
		अगर (kdb_जारी_catastrophic == 0 && kdb_go_count++ == 0) अणु
			kdb_म_लिखो("type go a second time if you really want "
				   "to continue\n");
			वापस 0;
		पूर्ण
		अगर (kdb_जारी_catastrophic == 2) अणु
			kdb_म_लिखो("forcing reboot\n");
			kdb_reboot(0, शून्य);
		पूर्ण
		kdb_म_लिखो("attempting to continue\n");
	पूर्ण
	वापस diag;
पूर्ण

/*
 * kdb_rd - This function implements the 'rd' command.
 */
अटल पूर्णांक kdb_rd(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक len = kdb_check_regs();
#अगर DBG_MAX_REG_NUM > 0
	पूर्णांक i;
	अक्षर *rname;
	पूर्णांक rsize;
	u64 reg64;
	u32 reg32;
	u16 reg16;
	u8 reg8;

	अगर (len)
		वापस len;

	क्रम (i = 0; i < DBG_MAX_REG_NUM; i++) अणु
		rsize = dbg_reg_def[i].size * 2;
		अगर (rsize > 16)
			rsize = 2;
		अगर (len + म_माप(dbg_reg_def[i].name) + 4 + rsize > 80) अणु
			len = 0;
			kdb_म_लिखो("\n");
		पूर्ण
		अगर (len)
			len += kdb_म_लिखो("  ");
		चयन(dbg_reg_def[i].size * 8) अणु
		हाल 8:
			rname = dbg_get_reg(i, &reg8, kdb_current_regs);
			अगर (!rname)
				अवरोध;
			len += kdb_म_लिखो("%s: %02x", rname, reg8);
			अवरोध;
		हाल 16:
			rname = dbg_get_reg(i, &reg16, kdb_current_regs);
			अगर (!rname)
				अवरोध;
			len += kdb_म_लिखो("%s: %04x", rname, reg16);
			अवरोध;
		हाल 32:
			rname = dbg_get_reg(i, &reg32, kdb_current_regs);
			अगर (!rname)
				अवरोध;
			len += kdb_म_लिखो("%s: %08x", rname, reg32);
			अवरोध;
		हाल 64:
			rname = dbg_get_reg(i, &reg64, kdb_current_regs);
			अगर (!rname)
				अवरोध;
			len += kdb_म_लिखो("%s: %016llx", rname, reg64);
			अवरोध;
		शेष:
			len += kdb_म_लिखो("%s: ??", dbg_reg_def[i].name);
		पूर्ण
	पूर्ण
	kdb_म_लिखो("\n");
#अन्यथा
	अगर (len)
		वापस len;

	kdb_dumpregs(kdb_current_regs);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * kdb_rm - This function implements the 'rm' (रेजिस्टर modअगरy)  command.
 *	rm रेजिस्टर-name new-contents
 * Remarks:
 *	Allows रेजिस्टर modअगरication with the same restrictions as gdb
 */
अटल पूर्णांक kdb_rm(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
#अगर DBG_MAX_REG_NUM > 0
	पूर्णांक diag;
	स्थिर अक्षर *rname;
	पूर्णांक i;
	u64 reg64;
	u32 reg32;
	u16 reg16;
	u8 reg8;

	अगर (argc != 2)
		वापस KDB_ARGCOUNT;
	/*
	 * Allow presence or असलence of leading '%' symbol.
	 */
	rname = argv[1];
	अगर (*rname == '%')
		rname++;

	diag = kdbgetu64arg(argv[2], &reg64);
	अगर (diag)
		वापस diag;

	diag = kdb_check_regs();
	अगर (diag)
		वापस diag;

	diag = KDB_BADREG;
	क्रम (i = 0; i < DBG_MAX_REG_NUM; i++) अणु
		अगर (म_भेद(rname, dbg_reg_def[i].name) == 0) अणु
			diag = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!diag) अणु
		चयन(dbg_reg_def[i].size * 8) अणु
		हाल 8:
			reg8 = reg64;
			dbg_set_reg(i, &reg8, kdb_current_regs);
			अवरोध;
		हाल 16:
			reg16 = reg64;
			dbg_set_reg(i, &reg16, kdb_current_regs);
			अवरोध;
		हाल 32:
			reg32 = reg64;
			dbg_set_reg(i, &reg32, kdb_current_regs);
			अवरोध;
		हाल 64:
			dbg_set_reg(i, &reg64, kdb_current_regs);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस diag;
#अन्यथा
	kdb_म_लिखो("ERROR: Register set currently not implemented\n");
    वापस 0;
#पूर्ण_अगर
पूर्ण

#अगर defined(CONFIG_MAGIC_SYSRQ)
/*
 * kdb_sr - This function implements the 'sr' (SYSRQ key) command
 *	which पूर्णांकerfaces to the soi-disant MAGIC SYSRQ functionality.
 *		sr <magic-sysrq-code>
 */
अटल पूर्णांक kdb_sr(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	bool check_mask =
	    !kdb_check_flags(KDB_ENABLE_ALL, kdb_cmd_enabled, false);

	अगर (argc != 1)
		वापस KDB_ARGCOUNT;

	kdb_trap_prपूर्णांकk++;
	__handle_sysrq(*argv[1], check_mask);
	kdb_trap_prपूर्णांकk--;

	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_MAGIC_SYSRQ */

/*
 * kdb_ef - This function implements the 'regs' (display exception
 *	frame) command.  This command takes an address and expects to
 *	find an exception frame at that address, क्रमmats and prपूर्णांकs
 *	it.
 *		regs address-expression
 * Remarks:
 *	Not करोne yet.
 */
अटल पूर्णांक kdb_ef(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक diag;
	अचिन्हित दीर्घ addr;
	दीर्घ offset;
	पूर्णांक nextarg;

	अगर (argc != 1)
		वापस KDB_ARGCOUNT;

	nextarg = 1;
	diag = kdbgetaddrarg(argc, argv, &nextarg, &addr, &offset, शून्य);
	अगर (diag)
		वापस diag;
	show_regs((काष्ठा pt_regs *)addr);
	वापस 0;
पूर्ण

#अगर defined(CONFIG_MODULES)
/*
 * kdb_lsmod - This function implements the 'lsmod' command.  Lists
 *	currently loaded kernel modules.
 *	Mostly taken from userland lsmod.
 */
अटल पूर्णांक kdb_lsmod(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा module *mod;

	अगर (argc != 0)
		वापस KDB_ARGCOUNT;

	kdb_म_लिखो("Module                  Size  modstruct     Used by\n");
	list_क्रम_each_entry(mod, kdb_modules, list) अणु
		अगर (mod->state == MODULE_STATE_UNFORMED)
			जारी;

		kdb_म_लिखो("%-20s%8u  0x%px ", mod->name,
			   mod->core_layout.size, (व्योम *)mod);
#अगर_घोषित CONFIG_MODULE_UNLOAD
		kdb_म_लिखो("%4d ", module_refcount(mod));
#पूर्ण_अगर
		अगर (mod->state == MODULE_STATE_GOING)
			kdb_म_लिखो(" (Unloading)");
		अन्यथा अगर (mod->state == MODULE_STATE_COMING)
			kdb_म_लिखो(" (Loading)");
		अन्यथा
			kdb_म_लिखो(" (Live)");
		kdb_म_लिखो(" 0x%px", mod->core_layout.base);

#अगर_घोषित CONFIG_MODULE_UNLOAD
		अणु
			काष्ठा module_use *use;
			kdb_म_लिखो(" [ ");
			list_क्रम_each_entry(use, &mod->source_list,
					    source_list)
				kdb_म_लिखो("%s ", use->target->name);
			kdb_म_लिखो("]\n");
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर	/* CONFIG_MODULES */

/*
 * kdb_env - This function implements the 'env' command.  Display the
 *	current environment variables.
 */

अटल पूर्णांक kdb_env(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	kdb_prपूर्णांकenv();

	अगर (KDB_DEBUG(MASK))
		kdb_म_लिखो("KDBDEBUG=0x%x\n",
			(kdb_flags & KDB_DEBUG(MASK)) >> KDB_DEBUG_FLAG_SHIFT);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PRINTK
/*
 * kdb_dmesg - This function implements the 'dmesg' command to display
 *	the contents of the syslog buffer.
 *		dmesg [lines] [adjust]
 */
अटल पूर्णांक kdb_dmesg(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक diag;
	पूर्णांक logging;
	पूर्णांक lines = 0;
	पूर्णांक adjust = 0;
	पूर्णांक n = 0;
	पूर्णांक skip = 0;
	काष्ठा kmsg_dump_iter iter;
	माप_प्रकार len;
	अक्षर buf[201];

	अगर (argc > 2)
		वापस KDB_ARGCOUNT;
	अगर (argc) अणु
		अक्षर *cp;
		lines = simple_म_से_दीर्घ(argv[1], &cp, 0);
		अगर (*cp)
			lines = 0;
		अगर (argc > 1) अणु
			adjust = simple_म_से_अदीर्घ(argv[2], &cp, 0);
			अगर (*cp || adjust < 0)
				adjust = 0;
		पूर्ण
	पूर्ण

	/* disable LOGGING अगर set */
	diag = kdbgetपूर्णांकenv("LOGGING", &logging);
	अगर (!diag && logging) अणु
		स्थिर अक्षर *setargs[] = अणु "set", "LOGGING", "0" पूर्ण;
		kdb_set(2, setargs);
	पूर्ण

	kmsg_dump_शुरुआत(&iter);
	जबतक (kmsg_dump_get_line(&iter, 1, शून्य, 0, शून्य))
		n++;

	अगर (lines < 0) अणु
		अगर (adjust >= n)
			kdb_म_लिखो("buffer only contains %d lines, nothing "
				   "printed\n", n);
		अन्यथा अगर (adjust - lines >= n)
			kdb_म_लिखो("buffer only contains %d lines, last %d "
				   "lines printed\n", n, n - adjust);
		skip = adjust;
		lines = असल(lines);
	पूर्ण अन्यथा अगर (lines > 0) अणु
		skip = n - lines - adjust;
		lines = असल(lines);
		अगर (adjust >= n) अणु
			kdb_म_लिखो("buffer only contains %d lines, "
				   "nothing printed\n", n);
			skip = n;
		पूर्ण अन्यथा अगर (skip < 0) अणु
			lines += skip;
			skip = 0;
			kdb_म_लिखो("buffer only contains %d lines, first "
				   "%d lines printed\n", n, lines);
		पूर्ण
	पूर्ण अन्यथा अणु
		lines = n;
	पूर्ण

	अगर (skip >= n || skip < 0)
		वापस 0;

	kmsg_dump_शुरुआत(&iter);
	जबतक (kmsg_dump_get_line(&iter, 1, buf, माप(buf), &len)) अणु
		अगर (skip) अणु
			skip--;
			जारी;
		पूर्ण
		अगर (!lines--)
			अवरोध;
		अगर (KDB_FLAG(CMD_INTERRUPT))
			वापस 0;

		kdb_म_लिखो("%.*s\n", (पूर्णांक)len - 1, buf);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PRINTK */

/* Make sure we balance enable/disable calls, must disable first. */
अटल atomic_t kdb_nmi_disabled;

अटल पूर्णांक kdb_disable_nmi(पूर्णांक argc, स्थिर अक्षर *argv[])
अणु
	अगर (atomic_पढ़ो(&kdb_nmi_disabled))
		वापस 0;
	atomic_set(&kdb_nmi_disabled, 1);
	arch_kgdb_ops.enable_nmi(0);
	वापस 0;
पूर्ण

अटल पूर्णांक kdb_param_enable_nmi(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!atomic_add_unless(&kdb_nmi_disabled, -1, 0))
		वापस -EINVAL;
	arch_kgdb_ops.enable_nmi(1);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops kdb_param_ops_enable_nmi = अणु
	.set = kdb_param_enable_nmi,
पूर्ण;
module_param_cb(enable_nmi, &kdb_param_ops_enable_nmi, शून्य, 0600);

/*
 * kdb_cpu - This function implements the 'cpu' command.
 *	cpu	[<cpunum>]
 * Returns:
 *	KDB_CMD_CPU क्रम success, a kdb diagnostic अगर error
 */
अटल व्योम kdb_cpu_status(व्योम)
अणु
	पूर्णांक i, start_cpu, first_prपूर्णांक = 1;
	अक्षर state, prev_state = '?';

	kdb_म_लिखो("Currently on cpu %d\n", raw_smp_processor_id());
	kdb_म_लिखो("Available cpus: ");
	क्रम (start_cpu = -1, i = 0; i < NR_CPUS; i++) अणु
		अगर (!cpu_online(i)) अणु
			state = 'F';	/* cpu is offline */
		पूर्ण अन्यथा अगर (!kgdb_info[i].enter_kgdb) अणु
			state = 'D';	/* cpu is online but unresponsive */
		पूर्ण अन्यथा अणु
			state = ' ';	/* cpu is responding to kdb */
			अगर (kdb_task_state_अक्षर(KDB_TSK(i)) == 'I')
				state = 'I';	/* idle task */
		पूर्ण
		अगर (state != prev_state) अणु
			अगर (prev_state != '?') अणु
				अगर (!first_prपूर्णांक)
					kdb_म_लिखो(", ");
				first_prपूर्णांक = 0;
				kdb_म_लिखो("%d", start_cpu);
				अगर (start_cpu < i-1)
					kdb_म_लिखो("-%d", i-1);
				अगर (prev_state != ' ')
					kdb_म_लिखो("(%c)", prev_state);
			पूर्ण
			prev_state = state;
			start_cpu = i;
		पूर्ण
	पूर्ण
	/* prपूर्णांक the trailing cpus, ignoring them अगर they are all offline */
	अगर (prev_state != 'F') अणु
		अगर (!first_prपूर्णांक)
			kdb_म_लिखो(", ");
		kdb_म_लिखो("%d", start_cpu);
		अगर (start_cpu < i-1)
			kdb_म_लिखो("-%d", i-1);
		अगर (prev_state != ' ')
			kdb_म_लिखो("(%c)", prev_state);
	पूर्ण
	kdb_म_लिखो("\n");
पूर्ण

अटल पूर्णांक kdb_cpu(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अचिन्हित दीर्घ cpunum;
	पूर्णांक diag;

	अगर (argc == 0) अणु
		kdb_cpu_status();
		वापस 0;
	पूर्ण

	अगर (argc != 1)
		वापस KDB_ARGCOUNT;

	diag = kdbgetularg(argv[1], &cpunum);
	अगर (diag)
		वापस diag;

	/*
	 * Validate cpunum
	 */
	अगर ((cpunum >= CONFIG_NR_CPUS) || !kgdb_info[cpunum].enter_kgdb)
		वापस KDB_BADCPUNUM;

	dbg_चयन_cpu = cpunum;

	/*
	 * Switch to other cpu
	 */
	वापस KDB_CMD_CPU;
पूर्ण

/* The user may not realize that ps/bta with no parameters करोes not prपूर्णांक idle
 * or sleeping प्रणाली daemon processes, so tell them how many were suppressed.
 */
व्योम kdb_ps_suppressed(व्योम)
अणु
	पूर्णांक idle = 0, daemon = 0;
	अचिन्हित दीर्घ mask_I = kdb_task_state_string("I"),
		      mask_M = kdb_task_state_string("M");
	अचिन्हित दीर्घ cpu;
	स्थिर काष्ठा task_काष्ठा *p, *g;
	क्रम_each_online_cpu(cpu) अणु
		p = kdb_curr_task(cpu);
		अगर (kdb_task_state(p, mask_I))
			++idle;
	पूर्ण
	क्रम_each_process_thपढ़ो(g, p) अणु
		अगर (kdb_task_state(p, mask_M))
			++daemon;
	पूर्ण
	अगर (idle || daemon) अणु
		अगर (idle)
			kdb_म_लिखो("%d idle process%s (state I)%s\n",
				   idle, idle == 1 ? "" : "es",
				   daemon ? " and " : "");
		अगर (daemon)
			kdb_म_लिखो("%d sleeping system daemon (state M) "
				   "process%s", daemon,
				   daemon == 1 ? "" : "es");
		kdb_म_लिखो(" suppressed,\nuse 'ps A' to see all.\n");
	पूर्ण
पूर्ण

/*
 * kdb_ps - This function implements the 'ps' command which shows a
 *	list of the active processes.
 *		ps [DRSTCZEUIMA]   All processes, optionally filtered by state
 */
व्योम kdb_ps1(स्थिर काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ पंचांगp;

	अगर (!p ||
	    copy_from_kernel_nofault(&पंचांगp, (अक्षर *)p, माप(अचिन्हित दीर्घ)))
		वापस;

	cpu = kdb_process_cpu(p);
	kdb_म_लिखो("0x%px %8d %8d  %d %4d   %c  0x%px %c%s\n",
		   (व्योम *)p, p->pid, p->parent->pid,
		   kdb_task_has_cpu(p), kdb_process_cpu(p),
		   kdb_task_state_अक्षर(p),
		   (व्योम *)(&p->thपढ़ो),
		   p == kdb_curr_task(raw_smp_processor_id()) ? '*' : ' ',
		   p->comm);
	अगर (kdb_task_has_cpu(p)) अणु
		अगर (!KDB_TSK(cpu)) अणु
			kdb_म_लिखो("  Error: no saved data for this cpu\n");
		पूर्ण अन्यथा अणु
			अगर (KDB_TSK(cpu) != p)
				kdb_म_लिखो("  Error: does not match running "
				   "process table (0x%px)\n", KDB_TSK(cpu));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक kdb_ps(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा task_काष्ठा *g, *p;
	अचिन्हित दीर्घ mask, cpu;

	अगर (argc == 0)
		kdb_ps_suppressed();
	kdb_म_लिखो("%-*s      Pid   Parent [*] cpu State %-*s Command\n",
		(पूर्णांक)(2*माप(व्योम *))+2, "Task Addr",
		(पूर्णांक)(2*माप(व्योम *))+2, "Thread");
	mask = kdb_task_state_string(argc ? argv[1] : शून्य);
	/* Run the active tasks first */
	क्रम_each_online_cpu(cpu) अणु
		अगर (KDB_FLAG(CMD_INTERRUPT))
			वापस 0;
		p = kdb_curr_task(cpu);
		अगर (kdb_task_state(p, mask))
			kdb_ps1(p);
	पूर्ण
	kdb_म_लिखो("\n");
	/* Now the real tasks */
	क्रम_each_process_thपढ़ो(g, p) अणु
		अगर (KDB_FLAG(CMD_INTERRUPT))
			वापस 0;
		अगर (kdb_task_state(p, mask))
			kdb_ps1(p);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * kdb_pid - This function implements the 'pid' command which चयनes
 *	the currently active process.
 *		pid [<pid> | R]
 */
अटल पूर्णांक kdb_pid(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा task_काष्ठा *p;
	अचिन्हित दीर्घ val;
	पूर्णांक diag;

	अगर (argc > 1)
		वापस KDB_ARGCOUNT;

	अगर (argc) अणु
		अगर (म_भेद(argv[1], "R") == 0) अणु
			p = KDB_TSK(kdb_initial_cpu);
		पूर्ण अन्यथा अणु
			diag = kdbgetularg(argv[1], &val);
			अगर (diag)
				वापस KDB_BADINT;

			p = find_task_by_pid_ns((pid_t)val,	&init_pid_ns);
			अगर (!p) अणु
				kdb_म_लिखो("No task with pid=%d\n", (pid_t)val);
				वापस 0;
			पूर्ण
		पूर्ण
		kdb_set_current_task(p);
	पूर्ण
	kdb_म_लिखो("KDB current process is %s(pid=%d)\n",
		   kdb_current_task->comm,
		   kdb_current_task->pid);

	वापस 0;
पूर्ण

अटल पूर्णांक kdb_kgdb(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	वापस KDB_CMD_KGDB;
पूर्ण

/*
 * kdb_help - This function implements the 'help' and '?' commands.
 */
अटल पूर्णांक kdb_help(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	kdbtab_t *kt;

	kdb_म_लिखो("%-15.15s %-20.20s %s\n", "Command", "Usage", "Description");
	kdb_म_लिखो("-----------------------------"
		   "-----------------------------\n");
	list_क्रम_each_entry(kt, &kdb_cmds_head, list_node) अणु
		अक्षर *space = "";
		अगर (KDB_FLAG(CMD_INTERRUPT))
			वापस 0;
		अगर (!kdb_check_flags(kt->cmd_flags, kdb_cmd_enabled, true))
			जारी;
		अगर (म_माप(kt->cmd_usage) > 20)
			space = "\n                                    ";
		kdb_म_लिखो("%-15.15s %-20s%s%s\n", kt->cmd_name,
			   kt->cmd_usage, space, kt->cmd_help);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * kdb_समाप्त - This function implements the 'kill' commands.
 */
अटल पूर्णांक kdb_समाप्त(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	दीर्घ sig, pid;
	अक्षर *endp;
	काष्ठा task_काष्ठा *p;

	अगर (argc != 2)
		वापस KDB_ARGCOUNT;

	sig = simple_म_से_दीर्घ(argv[1], &endp, 0);
	अगर (*endp)
		वापस KDB_BADINT;
	अगर ((sig >= 0) || !valid_संकेत(-sig)) अणु
		kdb_म_लिखो("Invalid signal parameter.<-signal>\n");
		वापस 0;
	पूर्ण
	sig = -sig;

	pid = simple_म_से_दीर्घ(argv[2], &endp, 0);
	अगर (*endp)
		वापस KDB_BADINT;
	अगर (pid <= 0) अणु
		kdb_म_लिखो("Process ID must be large than 0.\n");
		वापस 0;
	पूर्ण

	/* Find the process. */
	p = find_task_by_pid_ns(pid, &init_pid_ns);
	अगर (!p) अणु
		kdb_म_लिखो("The specified process isn't found.\n");
		वापस 0;
	पूर्ण
	p = p->group_leader;
	kdb_send_sig(p, sig);
	वापस 0;
पूर्ण

/*
 * Most of this code has been lअगरted from kernel/समयr.c::sys_sysinfo().
 * I cannot call that code directly from kdb, it has an unconditional
 * cli()/sti() and calls routines that take locks which can stop the debugger.
 */
अटल व्योम kdb_sysinfo(काष्ठा sysinfo *val)
अणु
	u64 upसमय = kसमय_get_mono_fast_ns();

	स_रखो(val, 0, माप(*val));
	val->upसमय = भाग_u64(upसमय, NSEC_PER_SEC);
	val->loads[0] = avenrun[0];
	val->loads[1] = avenrun[1];
	val->loads[2] = avenrun[2];
	val->procs = nr_thपढ़ोs-1;
	si_meminfo(val);

	वापस;
पूर्ण

/*
 * kdb_summary - This function implements the 'summary' command.
 */
अटल पूर्णांक kdb_summary(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	समय64_t now;
	काष्ठा पंचांग पंचांग;
	काष्ठा sysinfo val;

	अगर (argc)
		वापस KDB_ARGCOUNT;

	kdb_म_लिखो("sysname    %s\n", init_uts_ns.name.sysname);
	kdb_म_लिखो("release    %s\n", init_uts_ns.name.release);
	kdb_म_लिखो("version    %s\n", init_uts_ns.name.version);
	kdb_म_लिखो("machine    %s\n", init_uts_ns.name.machine);
	kdb_म_लिखो("nodename   %s\n", init_uts_ns.name.nodename);
	kdb_म_लिखो("domainname %s\n", init_uts_ns.name.करोमुख्यname);

	now = __kसमय_get_real_seconds();
	समय64_to_पंचांग(now, 0, &पंचांग);
	kdb_म_लिखो("date       %04ld-%02d-%02d %02d:%02d:%02d "
		   "tz_minuteswest %d\n",
		1900+पंचांग.पंचांग_year, पंचांग.पंचांग_mon+1, पंचांग.पंचांग_mday,
		पंचांग.पंचांग_hour, पंचांग.पंचांग_min, पंचांग.पंचांग_sec,
		sys_tz.tz_minuteswest);

	kdb_sysinfo(&val);
	kdb_म_लिखो("uptime     ");
	अगर (val.upसमय > (24*60*60)) अणु
		पूर्णांक days = val.upसमय / (24*60*60);
		val.upसमय %= (24*60*60);
		kdb_म_लिखो("%d day%s ", days, days == 1 ? "" : "s");
	पूर्ण
	kdb_म_लिखो("%02ld:%02ld\n", val.upसमय/(60*60), (val.upसमय/60)%60);

	kdb_म_लिखो("load avg   %ld.%02ld %ld.%02ld %ld.%02ld\n",
		LOAD_INT(val.loads[0]), LOAD_FRAC(val.loads[0]),
		LOAD_INT(val.loads[1]), LOAD_FRAC(val.loads[1]),
		LOAD_INT(val.loads[2]), LOAD_FRAC(val.loads[2]));

	/* Display in kilobytes */
#घोषणा K(x) ((x) << (PAGE_SHIFT - 10))
	kdb_म_लिखो("\nMemTotal:       %8lu kB\nMemFree:        %8lu kB\n"
		   "Buffers:        %8lu kB\n",
		   K(val.totalram), K(val.मुक्तram), K(val.bufferram));
	वापस 0;
पूर्ण

/*
 * kdb_per_cpu - This function implements the 'per_cpu' command.
 */
अटल पूर्णांक kdb_per_cpu(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अक्षर fmtstr[64];
	पूर्णांक cpu, diag, nextarg = 1;
	अचिन्हित दीर्घ addr, symaddr, val, bytesperword = 0, whichcpu = ~0UL;

	अगर (argc < 1 || argc > 3)
		वापस KDB_ARGCOUNT;

	diag = kdbgetaddrarg(argc, argv, &nextarg, &symaddr, शून्य, शून्य);
	अगर (diag)
		वापस diag;

	अगर (argc >= 2) अणु
		diag = kdbgetularg(argv[2], &bytesperword);
		अगर (diag)
			वापस diag;
	पूर्ण
	अगर (!bytesperword)
		bytesperword = KDB_WORD_SIZE;
	अन्यथा अगर (bytesperword > KDB_WORD_SIZE)
		वापस KDB_BADWIDTH;
	प्र_लिखो(fmtstr, "%%0%dlx ", (पूर्णांक)(2*bytesperword));
	अगर (argc >= 3) अणु
		diag = kdbgetularg(argv[3], &whichcpu);
		अगर (diag)
			वापस diag;
		अगर (whichcpu >= nr_cpu_ids || !cpu_online(whichcpu)) अणु
			kdb_म_लिखो("cpu %ld is not online\n", whichcpu);
			वापस KDB_BADCPUNUM;
		पूर्ण
	पूर्ण

	/* Most architectures use __per_cpu_offset[cpu], some use
	 * __per_cpu_offset(cpu), smp has no __per_cpu_offset.
	 */
#अगर_घोषित	__per_cpu_offset
#घोषणा KDB_PCU(cpu) __per_cpu_offset(cpu)
#अन्यथा
#अगर_घोषित	CONFIG_SMP
#घोषणा KDB_PCU(cpu) __per_cpu_offset[cpu]
#अन्यथा
#घोषणा KDB_PCU(cpu) 0
#पूर्ण_अगर
#पूर्ण_अगर
	क्रम_each_online_cpu(cpu) अणु
		अगर (KDB_FLAG(CMD_INTERRUPT))
			वापस 0;

		अगर (whichcpu != ~0UL && whichcpu != cpu)
			जारी;
		addr = symaddr + KDB_PCU(cpu);
		diag = kdb_getword(&val, addr, bytesperword);
		अगर (diag) अणु
			kdb_म_लिखो("%5d " kdb_bfd_vma_fmt0 " - unable to "
				   "read, diag=%d\n", cpu, addr, diag);
			जारी;
		पूर्ण
		kdb_म_लिखो("%5d ", cpu);
		kdb_md_line(fmtstr, addr,
			bytesperword == KDB_WORD_SIZE,
			1, bytesperword, 1, 1, 0);
	पूर्ण
#अघोषित KDB_PCU
	वापस 0;
पूर्ण

/*
 * display help क्रम the use of cmd | grep pattern
 */
अटल पूर्णांक kdb_grep_help(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	kdb_म_लिखो("Usage of  cmd args | grep pattern:\n");
	kdb_म_लिखो("  Any command's output may be filtered through an ");
	kdb_म_लिखो("emulated 'pipe'.\n");
	kdb_म_लिखो("  'grep' is just a key word.\n");
	kdb_म_लिखो("  The pattern may include a very limited set of "
		   "metacharacters:\n");
	kdb_म_लिखो("   pattern or ^pattern or pattern$ or ^pattern$\न");
	kdb_म_लिखो("  And if there are spaces in the pattern, you may "
		   "quote it:\n");
	kdb_म_लिखो("   \"pat tern\" or \"^pat tern\" or \"pat tern$\""
		   " or \"^pat tern$\"\n");
	वापस 0;
पूर्ण

/*
 * kdb_रेजिस्टर_flags - This function is used to रेजिस्टर a kernel
 * 	debugger command.
 * Inमाला_दो:
 *	cmd	Command name
 *	func	Function to execute the command
 *	usage	A simple usage string showing arguments
 *	help	A simple help string describing command
 *	repeat	Does the command स्वतः repeat on enter?
 * Returns:
 *	zero क्रम success, one अगर a duplicate command.
 */
पूर्णांक kdb_रेजिस्टर_flags(अक्षर *cmd,
		       kdb_func_t func,
		       अक्षर *usage,
		       अक्षर *help,
		       लघु minlen,
		       kdb_cmdflags_t flags)
अणु
	kdbtab_t *kp;

	list_क्रम_each_entry(kp, &kdb_cmds_head, list_node) अणु
		अगर (म_भेद(kp->cmd_name, cmd) == 0) अणु
			kdb_म_लिखो("Duplicate kdb command registered: "
				"%s, func %px help %s\n", cmd, func, help);
			वापस 1;
		पूर्ण
	पूर्ण

	kp = kदो_स्मृति(माप(*kp), GFP_KDB);
	अगर (!kp) अणु
		kdb_म_लिखो("Could not allocate new kdb_command table\n");
		वापस 1;
	पूर्ण

	kp->cmd_name   = cmd;
	kp->cmd_func   = func;
	kp->cmd_usage  = usage;
	kp->cmd_help   = help;
	kp->cmd_minlen = minlen;
	kp->cmd_flags  = flags;
	kp->is_dynamic = true;

	list_add_tail(&kp->list_node, &kdb_cmds_head);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kdb_रेजिस्टर_flags);

/*
 * kdb_रेजिस्टर_table() - This function is used to रेजिस्टर a kdb command
 *                        table.
 * @kp: poपूर्णांकer to kdb command table
 * @len: length of kdb command table
 */
व्योम kdb_रेजिस्टर_table(kdbtab_t *kp, माप_प्रकार len)
अणु
	जबतक (len--) अणु
		list_add_tail(&kp->list_node, &kdb_cmds_head);
		kp++;
	पूर्ण
पूर्ण

/*
 * kdb_रेजिस्टर - Compatibility रेजिस्टर function क्रम commands that करो
 *	not need to specअगरy a repeat state.  Equivalent to
 *	kdb_रेजिस्टर_flags with flags set to 0.
 * Inमाला_दो:
 *	cmd	Command name
 *	func	Function to execute the command
 *	usage	A simple usage string showing arguments
 *	help	A simple help string describing command
 * Returns:
 *	zero क्रम success, one अगर a duplicate command.
 */
पूर्णांक kdb_रेजिस्टर(अक्षर *cmd,
	     kdb_func_t func,
	     अक्षर *usage,
	     अक्षर *help,
	     लघु minlen)
अणु
	वापस kdb_रेजिस्टर_flags(cmd, func, usage, help, minlen, 0);
पूर्ण
EXPORT_SYMBOL_GPL(kdb_रेजिस्टर);

/*
 * kdb_unरेजिस्टर - This function is used to unरेजिस्टर a kernel
 *	debugger command.  It is generally called when a module which
 *	implements kdb commands is unloaded.
 * Inमाला_दो:
 *	cmd	Command name
 * Returns:
 *	zero क्रम success, one command not रेजिस्टरed.
 */
पूर्णांक kdb_unरेजिस्टर(अक्षर *cmd)
अणु
	kdbtab_t *kp;

	/*
	 *  find the command.
	 */
	list_क्रम_each_entry(kp, &kdb_cmds_head, list_node) अणु
		अगर (म_भेद(kp->cmd_name, cmd) == 0) अणु
			list_del(&kp->list_node);
			अगर (kp->is_dynamic)
				kमुक्त(kp);
			वापस 0;
		पूर्ण
	पूर्ण

	/* Couldn't find it.  */
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(kdb_unरेजिस्टर);

अटल kdbtab_t मुख्यtab[] = अणु
	अणु	.cmd_name = "md",
		.cmd_func = kdb_md,
		.cmd_usage = "<vaddr>",
		.cmd_help = "Display Memory Contents, also mdWcN, e.g. md8c1",
		.cmd_minlen = 1,
		.cmd_flags = KDB_ENABLE_MEM_READ | KDB_REPEAT_NO_ARGS,
	पूर्ण,
	अणु	.cmd_name = "mdr",
		.cmd_func = kdb_md,
		.cmd_usage = "<vaddr> <bytes>",
		.cmd_help = "Display Raw Memory",
		.cmd_flags = KDB_ENABLE_MEM_READ | KDB_REPEAT_NO_ARGS,
	पूर्ण,
	अणु	.cmd_name = "mdp",
		.cmd_func = kdb_md,
		.cmd_usage = "<paddr> <bytes>",
		.cmd_help = "Display Physical Memory",
		.cmd_flags = KDB_ENABLE_MEM_READ | KDB_REPEAT_NO_ARGS,
	पूर्ण,
	अणु	.cmd_name = "mds",
		.cmd_func = kdb_md,
		.cmd_usage = "<vaddr>",
		.cmd_help = "Display Memory Symbolically",
		.cmd_flags = KDB_ENABLE_MEM_READ | KDB_REPEAT_NO_ARGS,
	पूर्ण,
	अणु	.cmd_name = "mm",
		.cmd_func = kdb_mm,
		.cmd_usage = "<vaddr> <contents>",
		.cmd_help = "Modify Memory Contents",
		.cmd_flags = KDB_ENABLE_MEM_WRITE | KDB_REPEAT_NO_ARGS,
	पूर्ण,
	अणु	.cmd_name = "go",
		.cmd_func = kdb_go,
		.cmd_usage = "[<vaddr>]",
		.cmd_help = "Continue Execution",
		.cmd_minlen = 1,
		.cmd_flags = KDB_ENABLE_REG_WRITE |
			     KDB_ENABLE_ALWAYS_SAFE_NO_ARGS,
	पूर्ण,
	अणु	.cmd_name = "rd",
		.cmd_func = kdb_rd,
		.cmd_usage = "",
		.cmd_help = "Display Registers",
		.cmd_flags = KDB_ENABLE_REG_READ,
	पूर्ण,
	अणु	.cmd_name = "rm",
		.cmd_func = kdb_rm,
		.cmd_usage = "<reg> <contents>",
		.cmd_help = "Modify Registers",
		.cmd_flags = KDB_ENABLE_REG_WRITE,
	पूर्ण,
	अणु	.cmd_name = "ef",
		.cmd_func = kdb_ef,
		.cmd_usage = "<vaddr>",
		.cmd_help = "Display exception frame",
		.cmd_flags = KDB_ENABLE_MEM_READ,
	पूर्ण,
	अणु	.cmd_name = "bt",
		.cmd_func = kdb_bt,
		.cmd_usage = "[<vaddr>]",
		.cmd_help = "Stack traceback",
		.cmd_minlen = 1,
		.cmd_flags = KDB_ENABLE_MEM_READ | KDB_ENABLE_INSPECT_NO_ARGS,
	पूर्ण,
	अणु	.cmd_name = "btp",
		.cmd_func = kdb_bt,
		.cmd_usage = "<pid>",
		.cmd_help = "Display stack for process <pid>",
		.cmd_flags = KDB_ENABLE_INSPECT,
	पूर्ण,
	अणु	.cmd_name = "bta",
		.cmd_func = kdb_bt,
		.cmd_usage = "[D|R|S|T|C|Z|E|U|I|M|A]",
		.cmd_help = "Backtrace all processes matching state flag",
		.cmd_flags = KDB_ENABLE_INSPECT,
	पूर्ण,
	अणु	.cmd_name = "btc",
		.cmd_func = kdb_bt,
		.cmd_usage = "",
		.cmd_help = "Backtrace current process on each cpu",
		.cmd_flags = KDB_ENABLE_INSPECT,
	पूर्ण,
	अणु	.cmd_name = "btt",
		.cmd_func = kdb_bt,
		.cmd_usage = "<vaddr>",
		.cmd_help = "Backtrace process given its struct task address",
		.cmd_flags = KDB_ENABLE_MEM_READ | KDB_ENABLE_INSPECT_NO_ARGS,
	पूर्ण,
	अणु	.cmd_name = "env",
		.cmd_func = kdb_env,
		.cmd_usage = "",
		.cmd_help = "Show environment variables",
		.cmd_flags = KDB_ENABLE_ALWAYS_SAFE,
	पूर्ण,
	अणु	.cmd_name = "set",
		.cmd_func = kdb_set,
		.cmd_usage = "",
		.cmd_help = "Set environment variables",
		.cmd_flags = KDB_ENABLE_ALWAYS_SAFE,
	पूर्ण,
	अणु	.cmd_name = "help",
		.cmd_func = kdb_help,
		.cmd_usage = "",
		.cmd_help = "Display Help Message",
		.cmd_minlen = 1,
		.cmd_flags = KDB_ENABLE_ALWAYS_SAFE,
	पूर्ण,
	अणु	.cmd_name = "?",
		.cmd_func = kdb_help,
		.cmd_usage = "",
		.cmd_help = "Display Help Message",
		.cmd_flags = KDB_ENABLE_ALWAYS_SAFE,
	पूर्ण,
	अणु	.cmd_name = "cpu",
		.cmd_func = kdb_cpu,
		.cmd_usage = "<cpunum>",
		.cmd_help = "Switch to new cpu",
		.cmd_flags = KDB_ENABLE_ALWAYS_SAFE_NO_ARGS,
	पूर्ण,
	अणु	.cmd_name = "kgdb",
		.cmd_func = kdb_kgdb,
		.cmd_usage = "",
		.cmd_help = "Enter kgdb mode",
		.cmd_flags = 0,
	पूर्ण,
	अणु	.cmd_name = "ps",
		.cmd_func = kdb_ps,
		.cmd_usage = "[<flags>|A]",
		.cmd_help = "Display active task list",
		.cmd_flags = KDB_ENABLE_INSPECT,
	पूर्ण,
	अणु	.cmd_name = "pid",
		.cmd_func = kdb_pid,
		.cmd_usage = "<pidnum>",
		.cmd_help = "Switch to another task",
		.cmd_flags = KDB_ENABLE_INSPECT,
	पूर्ण,
	अणु	.cmd_name = "reboot",
		.cmd_func = kdb_reboot,
		.cmd_usage = "",
		.cmd_help = "Reboot the machine immediately",
		.cmd_flags = KDB_ENABLE_REBOOT,
	पूर्ण,
#अगर defined(CONFIG_MODULES)
	अणु	.cmd_name = "lsmod",
		.cmd_func = kdb_lsmod,
		.cmd_usage = "",
		.cmd_help = "List loaded kernel modules",
		.cmd_flags = KDB_ENABLE_INSPECT,
	पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_MAGIC_SYSRQ)
	अणु	.cmd_name = "sr",
		.cmd_func = kdb_sr,
		.cmd_usage = "<key>",
		.cmd_help = "Magic SysRq key",
		.cmd_flags = KDB_ENABLE_ALWAYS_SAFE,
	पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_PRINTK)
	अणु	.cmd_name = "dmesg",
		.cmd_func = kdb_dmesg,
		.cmd_usage = "[lines]",
		.cmd_help = "Display syslog buffer",
		.cmd_flags = KDB_ENABLE_ALWAYS_SAFE,
	पूर्ण,
#पूर्ण_अगर
	अणु	.cmd_name = "defcmd",
		.cmd_func = kdb_defcmd,
		.cmd_usage = "name \"usage\" \"help\"",
		.cmd_help = "Define a set of commands, down to endefcmd",
		.cmd_flags = KDB_ENABLE_ALWAYS_SAFE,
	पूर्ण,
	अणु	.cmd_name = "kill",
		.cmd_func = kdb_समाप्त,
		.cmd_usage = "<-signal> <pid>",
		.cmd_help = "Send a signal to a process",
		.cmd_flags = KDB_ENABLE_SIGNAL,
	पूर्ण,
	अणु	.cmd_name = "summary",
		.cmd_func = kdb_summary,
		.cmd_usage = "",
		.cmd_help = "Summarize the system",
		.cmd_minlen = 4,
		.cmd_flags = KDB_ENABLE_ALWAYS_SAFE,
	पूर्ण,
	अणु	.cmd_name = "per_cpu",
		.cmd_func = kdb_per_cpu,
		.cmd_usage = "<sym> [<bytes>] [<cpu>]",
		.cmd_help = "Display per_cpu variables",
		.cmd_minlen = 3,
		.cmd_flags = KDB_ENABLE_MEM_READ,
	पूर्ण,
	अणु	.cmd_name = "grephelp",
		.cmd_func = kdb_grep_help,
		.cmd_usage = "",
		.cmd_help = "Display help on | grep",
		.cmd_flags = KDB_ENABLE_ALWAYS_SAFE,
	पूर्ण,
पूर्ण;

अटल kdbtab_t nmicmd = अणु
	.cmd_name = "disable_nmi",
	.cmd_func = kdb_disable_nmi,
	.cmd_usage = "",
	.cmd_help = "Disable NMI entry to KDB",
	.cmd_flags = KDB_ENABLE_ALWAYS_SAFE,
पूर्ण;

/* Initialize the kdb command table. */
अटल व्योम __init kdb_inittab(व्योम)
अणु
	kdb_रेजिस्टर_table(मुख्यtab, ARRAY_SIZE(मुख्यtab));
	अगर (arch_kgdb_ops.enable_nmi)
		kdb_रेजिस्टर_table(&nmicmd, 1);
पूर्ण

/* Execute any commands defined in kdb_cmds.  */
अटल व्योम __init kdb_cmd_init(व्योम)
अणु
	पूर्णांक i, diag;
	क्रम (i = 0; kdb_cmds[i]; ++i) अणु
		diag = kdb_parse(kdb_cmds[i]);
		अगर (diag)
			kdb_म_लिखो("kdb command %s failed, kdb diag %d\n",
				kdb_cmds[i], diag);
	पूर्ण
	अगर (defcmd_in_progress) अणु
		kdb_म_लिखो("Incomplete 'defcmd' set, forcing endefcmd\n");
		kdb_parse("endefcmd");
	पूर्ण
पूर्ण

/* Initialize kdb_म_लिखो, अवरोधpoपूर्णांक tables and kdb state */
व्योम __init kdb_init(पूर्णांक lvl)
अणु
	अटल पूर्णांक kdb_init_lvl = KDB_NOT_INITIALIZED;
	पूर्णांक i;

	अगर (kdb_init_lvl == KDB_INIT_FULL || lvl <= kdb_init_lvl)
		वापस;
	क्रम (i = kdb_init_lvl; i < lvl; i++) अणु
		चयन (i) अणु
		हाल KDB_NOT_INITIALIZED:
			kdb_inittab();		/* Initialize Command Table */
			kdb_initbptab();	/* Initialize Breakpoपूर्णांकs */
			अवरोध;
		हाल KDB_INIT_EARLY:
			kdb_cmd_init();		/* Build kdb_cmds tables */
			अवरोध;
		पूर्ण
	पूर्ण
	kdb_init_lvl = lvl;
पूर्ण
