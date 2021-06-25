<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#समावेश <संकेत.स>

अटल माप_प्रकार syscall_arg__scnम_लिखो_signum(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "SIG";
	पूर्णांक sig = arg->val;

	चयन (sig) अणु
#घोषणा	P_SIGNUM(n) हाल SIG##n: वापस scnम_लिखो(bf, size, "%s%s", show_prefix ? prefix : "", #n)
	P_SIGNUM(HUP);
	P_SIGNUM(INT);
	P_SIGNUM(QUIT);
	P_SIGNUM(ILL);
	P_SIGNUM(TRAP);
	P_SIGNUM(ABRT);
	P_SIGNUM(BUS);
	P_SIGNUM(FPE);
	P_SIGNUM(KILL);
	P_SIGNUM(USR1);
	P_SIGNUM(SEGV);
	P_SIGNUM(USR2);
	P_SIGNUM(PIPE);
	P_SIGNUM(ALRM);
	P_SIGNUM(TERM);
	P_SIGNUM(CHLD);
	P_SIGNUM(CONT);
	P_SIGNUM(STOP);
	P_SIGNUM(TSTP);
	P_SIGNUM(TTIN);
	P_SIGNUM(TTOU);
	P_SIGNUM(URG);
	P_SIGNUM(XCPU);
	P_SIGNUM(XFSZ);
	P_SIGNUM(VTALRM);
	P_SIGNUM(PROF);
	P_SIGNUM(WINCH);
	P_SIGNUM(IO);
	P_SIGNUM(PWR);
	P_SIGNUM(SYS);
#अगर_घोषित SIGEMT
	P_SIGNUM(EMT);
#पूर्ण_अगर
#अगर_घोषित SIGSTKFLT
	P_SIGNUM(STKFLT);
#पूर्ण_अगर
#अगर_घोषित SIGSWI
	P_SIGNUM(SWI);
#पूर्ण_अगर
	शेष: अवरोध;
	पूर्ण

	वापस scnम_लिखो(bf, size, "%#x", sig);
पूर्ण

#घोषणा SCA_SIGNUM syscall_arg__scnम_लिखो_signum
