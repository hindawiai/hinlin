<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2018, Michael Ellerman, IBM Corp.
 *
 * Test that an out-of-bounds branch to counter behaves as expected.
 */

#समावेश <समलाँघ.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <ucontext.h>
#समावेश <unistd.h>

#समावेश "utils.h"


#घोषणा BAD_NIP	0x788c545a18000000ull

अटल काष्ठा pt_regs संकेत_regs;
अटल लाँघ_बफ बनाओ_लाँघ_env;

अटल व्योम save_regs(ucontext_t *ctxt)
अणु
	काष्ठा pt_regs *regs = ctxt->uc_mcontext.regs;

	स_नकल(&संकेत_regs, regs, माप(संकेत_regs));
पूर्ण

अटल व्योम segv_handler(पूर्णांक signum, siginfo_t *info, व्योम *ctxt_v)
अणु
	save_regs(ctxt_v);
	दीर्घ_लाँघ(बनाओ_लाँघ_env, 1);
पूर्ण

अटल व्योम usr2_handler(पूर्णांक signum, siginfo_t *info, व्योम *ctxt_v)
अणु
	save_regs(ctxt_v);
पूर्ण

अटल पूर्णांक ok(व्योम)
अणु
	म_लिखो("Everything is OK in here.\n");
	वापस 0;
पूर्ण

#घोषणा REG_POISON	0x5a5a
#घोषणा POISONED_REG(n)	((((अचिन्हित दीर्घ)REG_POISON) << 48) | ((n) << 32) | \
			 (((अचिन्हित दीर्घ)REG_POISON) << 16) | (n))

अटल अंतरभूत व्योम poison_regs(व्योम)
अणु
	#घोषणा POISON_REG(n)	\
	  "lis  " __stringअगरy(n) "," __stringअगरy(REG_POISON) ";" \
	  "addi " __stringअगरy(n) "," __stringअगरy(n) "," __stringअगरy(n) ";" \
	  "sldi " __stringअगरy(n) "," __stringअगरy(n) ", 32 ;" \
	  "oris " __stringअगरy(n) "," __stringअगरy(n) "," __stringअगरy(REG_POISON) ";" \
	  "addi " __stringअगरy(n) "," __stringअगरy(n) "," __stringअगरy(n) ";"

	यंत्र (POISON_REG(15)
	     POISON_REG(16)
	     POISON_REG(17)
	     POISON_REG(18)
	     POISON_REG(19)
	     POISON_REG(20)
	     POISON_REG(21)
	     POISON_REG(22)
	     POISON_REG(23)
	     POISON_REG(24)
	     POISON_REG(25)
	     POISON_REG(26)
	     POISON_REG(27)
	     POISON_REG(28)
	     POISON_REG(29)
	     : // inमाला_दो
	     : // outमाला_दो
	     : "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25",
	       "26", "27", "28", "29"
	);
	#अघोषित POISON_REG
पूर्ण

अटल पूर्णांक check_regs(व्योम)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 15; i <= 29; i++)
		FAIL_IF(संकेत_regs.gpr[i] != POISONED_REG(i));

	म_लिखो("Regs OK\n");
	वापस 0;
पूर्ण

अटल व्योम dump_regs(व्योम)
अणु
	क्रम (पूर्णांक i = 0; i < 32; i += 4) अणु
		म_लिखो("r%02d 0x%016lx  r%02d 0x%016lx  " \
		       "r%02d 0x%016lx  r%02d 0x%016lx\n",
		       i, संकेत_regs.gpr[i],
		       i+1, संकेत_regs.gpr[i+1],
		       i+2, संकेत_regs.gpr[i+2],
		       i+3, संकेत_regs.gpr[i+3]);
	पूर्ण
पूर्ण

#अगर_घोषित _CALL_AIXDESC
काष्ठा opd अणु
	अचिन्हित दीर्घ ip;
	अचिन्हित दीर्घ toc;
	अचिन्हित दीर्घ env;
पूर्ण;
अटल काष्ठा opd bad_opd = अणु
	.ip = BAD_NIP,
पूर्ण;
#घोषणा BAD_FUNC (&bad_opd)
#अन्यथा
#घोषणा BAD_FUNC BAD_NIP
#पूर्ण_अगर

पूर्णांक test_wild_bctr(व्योम)
अणु
	पूर्णांक (*func_ptr)(व्योम);
	काष्ठा sigaction segv = अणु
		.sa_sigaction = segv_handler,
		.sa_flags = SA_SIGINFO
	पूर्ण;
	काष्ठा sigaction usr2 = अणु
		.sa_sigaction = usr2_handler,
		.sa_flags = SA_SIGINFO
	पूर्ण;

	FAIL_IF(sigaction(संक_अंश, &segv, शून्य));
	FAIL_IF(sigaction(SIGUSR2, &usr2, शून्य));

	bzero(&संकेत_regs, माप(संकेत_regs));

	अगर (बनाओ_लाँघ(बनाओ_लाँघ_env) == 0) अणु
		func_ptr = ok;
		func_ptr();

		समाप्त(getpid(), SIGUSR2);
		म_लिखो("Regs before:\n");
		dump_regs();
		bzero(&संकेत_regs, माप(संकेत_regs));

		poison_regs();

		func_ptr = (पूर्णांक (*)(व्योम))BAD_FUNC;
		func_ptr();

		FAIL_IF(1); /* we didn't segv? */
	पूर्ण

	FAIL_IF(संकेत_regs.nip != BAD_NIP);

	म_लिखो("All good - took SEGV as expected branching to 0x%llx\n", BAD_NIP);

	dump_regs();
	FAIL_IF(check_regs());

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test_wild_bctr, "wild_bctr");
पूर्ण
