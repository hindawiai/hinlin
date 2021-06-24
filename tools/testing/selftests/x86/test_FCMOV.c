<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE 1
#अघोषित __USE_GNU
#घोषणा __USE_GNU 1
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <संकेत.स>
#समावेश <sys/types.h>
#समावेश <sys/select.h>
#समावेश <sys/समय.स>
#समावेश <sys/रुको.h>

#घोषणा TEST(insn) \
दीर्घ द्विगुन __attribute__((noअंतरभूत)) insn(दीर्घ flags) \
अणु						\
	दीर्घ द्विगुन out;			\
	यंत्र ("\n"				\
	"	push	%1""\n"			\
	"	popf""\n"			\
	"	fldpi""\n"			\
	"	fld1""\n"			\
	"	" #insn " %%st(1), %%st" "\n"	\
	"	ffree	%%st(1)" "\n"		\
	: "=t" (out)				\
	: "r" (flags)				\
	);					\
	वापस out;				\
पूर्ण

TEST(fcmovb)
TEST(fcmove)
TEST(fcmovbe)
TEST(fcmovu)
TEST(fcmovnb)
TEST(fcmovne)
TEST(fcmovnbe)
TEST(fcmovnu)

क्रमागत अणु
	CF = 1 << 0,
	PF = 1 << 2,
	ZF = 1 << 6,
पूर्ण;

व्योम sighandler(पूर्णांक sig)
अणु
	म_लिखो("[FAIL]\tGot signal %d, exiting\n", sig);
	निकास(1);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv, अक्षर **envp)
अणु
	पूर्णांक err = 0;

	/* संक_अवैध triggers on 32-bit kernels w/o fcomi emulation
	 * when run with "no387 nofxsr". Other संकेतs are caught
	 * just in हाल.
	 */
	संकेत(संक_अवैध, sighandler);
	संकेत(संक_भ_त्रुटि, sighandler);
	संकेत(संक_अंश, sighandler);

	म_लिखो("[RUN]\tTesting fcmovCC instructions\n");
	/* If fcmovCC() वापसs 1.0, the move wasn't करोne */
	err |= !(fcmovb(0)   == 1.0); err |= !(fcmovnb(0)  != 1.0);
	err |= !(fcmove(0)   == 1.0); err |= !(fcmovne(0)  != 1.0);
	err |= !(fcmovbe(0)  == 1.0); err |= !(fcmovnbe(0) != 1.0);
	err |= !(fcmovu(0)   == 1.0); err |= !(fcmovnu(0)  != 1.0);

	err |= !(fcmovb(CF)  != 1.0); err |= !(fcmovnb(CF)  == 1.0);
	err |= !(fcmove(CF)  == 1.0); err |= !(fcmovne(CF)  != 1.0);
	err |= !(fcmovbe(CF) != 1.0); err |= !(fcmovnbe(CF) == 1.0);
	err |= !(fcmovu(CF)  == 1.0); err |= !(fcmovnu(CF)  != 1.0);

	err |= !(fcmovb(ZF)  == 1.0); err |= !(fcmovnb(ZF)  != 1.0);
	err |= !(fcmove(ZF)  != 1.0); err |= !(fcmovne(ZF)  == 1.0);
	err |= !(fcmovbe(ZF) != 1.0); err |= !(fcmovnbe(ZF) == 1.0);
	err |= !(fcmovu(ZF)  == 1.0); err |= !(fcmovnu(ZF)  != 1.0);

	err |= !(fcmovb(PF)  == 1.0); err |= !(fcmovnb(PF)  != 1.0);
	err |= !(fcmove(PF)  == 1.0); err |= !(fcmovne(PF)  != 1.0);
	err |= !(fcmovbe(PF) == 1.0); err |= !(fcmovnbe(PF) != 1.0);
	err |= !(fcmovu(PF)  != 1.0); err |= !(fcmovnu(PF)  == 1.0);

        अगर (!err)
                म_लिखो("[OK]\tfcmovCC\n");
	अन्यथा
		म_लिखो("[FAIL]\tfcmovCC errors: %d\n", err);

	वापस err;
पूर्ण
