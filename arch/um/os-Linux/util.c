<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <termios.h>
#समावेश <sys/रुको.h>
#समावेश <sys/mman.h>
#समावेश <sys/utsname.h>
#समावेश <init.h>
#समावेश <os.h>

व्योम stack_protections(अचिन्हित दीर्घ address)
अणु
	अगर (mprotect((व्योम *) address, UM_THREAD_SIZE,
		    PROT_READ | PROT_WRITE | PROT_EXEC) < 0)
		panic("protecting stack failed, errno = %d", त्रुटि_सं);
पूर्ण

पूर्णांक raw(पूर्णांक fd)
अणु
	काष्ठा termios tt;
	पूर्णांक err;

	CATCH_EINTR(err = tcgetattr(fd, &tt));
	अगर (err < 0)
		वापस -त्रुटि_सं;

	cfmakeraw(&tt);

	CATCH_EINTR(err = tcsetattr(fd, TCSADRAIN, &tt));
	अगर (err < 0)
		वापस -त्रुटि_सं;

	/*
	 * XXX tcsetattr could have applied only some changes
	 * (and cfmakeraw() is a set of changes)
	 */
	वापस 0;
पूर्ण

व्योम setup_machinename(अक्षर *machine_out)
अणु
	काष्ठा utsname host;

	uname(&host);
#अगर_घोषित UML_CONFIG_UML_X86
# अगरndef UML_CONFIG_64BIT
	अगर (!म_भेद(host.machine, "x86_64")) अणु
		म_नकल(machine_out, "i686");
		वापस;
	पूर्ण
# अन्यथा
	अगर (!म_भेद(host.machine, "i686")) अणु
		म_नकल(machine_out, "x86_64");
		वापस;
	पूर्ण
# endअगर
#पूर्ण_अगर
	म_नकल(machine_out, host.machine);
पूर्ण

व्योम setup_hostinfo(अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा utsname host;

	uname(&host);
	snम_लिखो(buf, len, "%s %s %s %s %s", host.sysname, host.nodename,
		 host.release, host.version, host.machine);
पूर्ण

/*
 * We cannot use glibc's पात(). It makes use of tgसमाप्त() which
 * has no effect within UML's kernel thपढ़ोs.
 * After that glibc would execute an invalid inकाष्ठाion to समाप्त
 * the calling process and UML crashes with संक_अंश.
 */
अटल अंतरभूत व्योम __attribute__ ((noवापस)) uml_पात(व्योम)
अणु
	sigset_t sig;

	ख_साफ(शून्य);

	अगर (!sigemptyset(&sig) && !sigaddset(&sig, SIGABRT))
		sigprocmask(SIG_UNBLOCK, &sig, 0);

	क्रम (;;)
		अगर (समाप्त(getpid(), SIGABRT) < 0)
			निकास(127);
पूर्ण

/*
 * UML helper thपढ़ोs must not handle SIGWINCH/INT/TERM
 */
व्योम os_fix_helper_संकेतs(व्योम)
अणु
	संकेत(SIGWINCH, संक_छोड़ो);
	संकेत(संक_विघ्न, संक_पूर्व);
	संकेत(संक_इति, संक_पूर्व);
पूर्ण

व्योम os_dump_core(व्योम)
अणु
	पूर्णांक pid;

	संकेत(संक_अंश, संक_पूर्व);

	/*
	 * We are about to संक_इति this entire process group to ensure that
	 * nothing is around to run after the kernel निकासs.  The
	 * kernel wants to पात, not die through संक_इति, so we
	 * ignore it here.
	 */

	संकेत(संक_इति, संक_छोड़ो);
	समाप्त(0, संक_इति);
	/*
	 * Most of the other processes associated with this UML are
	 * likely sTopped, so give them a SIGCONT so they see the
	 * संक_इति.
	 */
	समाप्त(0, SIGCONT);

	/*
	 * Now, having sent संकेतs to everyone but us, make sure they
	 * die by ptrace.  Processes can survive what's been करोne to
	 * them so far - the mechanism I understand is receiving a
	 * संक_अंश and segfaulting immediately upon वापस.  There is
	 * always a संक_अंश pending, and (I'm guessing) संकेतs are
	 * processed in numeric order so the संक_इति (संकेत 15 vs
	 * संक_अंश being संकेत 11) is never handled.
	 *
	 * Run a रुकोpid loop until we get some kind of error.
	 * Hopefully, it's ECHILD, but there's not a lot we can करो अगर
	 * it's something अन्यथा.  Tell os_समाप्त_ptraced_process not to
	 * रुको क्रम the child to report its death because there's
	 * nothing reasonable to करो अगर that fails.
	 */

	जबतक ((pid = रुकोpid(-1, शून्य, WNOHANG | __WALL)) > 0)
		os_समाप्त_ptraced_process(pid, 0);

	uml_पात();
पूर्ण

व्योम um_early_prपूर्णांकk(स्थिर अक्षर *s, अचिन्हित पूर्णांक n)
अणु
	म_लिखो("%.*s", n, s);
पूर्ण

अटल पूर्णांक quiet_info;

अटल पूर्णांक __init quiet_cmd_param(अक्षर *str, पूर्णांक *add)
अणु
	quiet_info = 1;
	वापस 0;
पूर्ण

__uml_setup("quiet", quiet_cmd_param,
"quiet\n"
"    Turns off information messages during boot.\n\n");

व्योम os_info(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची list;

	अगर (quiet_info)
		वापस;

	बहु_शुरू(list, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, list);
	बहु_पूर्ण(list);
पूर्ण

व्योम os_warn(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची list;

	बहु_शुरू(list, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, list);
	बहु_पूर्ण(list);
पूर्ण
