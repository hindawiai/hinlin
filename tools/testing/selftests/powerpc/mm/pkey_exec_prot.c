<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * Copyright 2020, Sandipan Das, IBM Corp.
 *
 * Test अगर applying execute protection on pages using memory
 * protection keys works as expected.
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <संकेत.स>

#समावेश <unistd.h>

#समावेश "pkeys.h"

#घोषणा PPC_INST_NOP	0x60000000
#घोषणा PPC_INST_TRAP	0x7fe00008
#घोषणा PPC_INST_BLR	0x4e800020

अटल अस्थिर संक_पूर्ण_प्रकार fault_pkey, fault_code, fault_type;
अटल अस्थिर संक_पूर्ण_प्रकार reमुख्यing_faults;
अटल अस्थिर अचिन्हित पूर्णांक *fault_addr;
अटल अचिन्हित दीर्घ pgsize, numinsns;
अटल अचिन्हित पूर्णांक *insns;

अटल व्योम trap_handler(पूर्णांक signum, siginfo_t *sinfo, व्योम *ctx)
अणु
	/* Check अगर this fault originated from the expected address */
	अगर (sinfo->si_addr != (व्योम *) fault_addr)
		sigsafe_err("got a fault for an unexpected address\n");

	_निकास(1);
पूर्ण

अटल व्योम segv_handler(पूर्णांक signum, siginfo_t *sinfo, व्योम *ctx)
अणु
	पूर्णांक संकेत_pkey;

	संकेत_pkey = siginfo_pkey(sinfo);
	fault_code = sinfo->si_code;

	/* Check अगर this fault originated from the expected address */
	अगर (sinfo->si_addr != (व्योम *) fault_addr) अणु
		sigsafe_err("got a fault for an unexpected address\n");
		_निकास(1);
	पूर्ण

	/* Check अगर too many faults have occurred क्रम a single test हाल */
	अगर (!reमुख्यing_faults) अणु
		sigsafe_err("got too many faults for the same address\n");
		_निकास(1);
	पूर्ण


	/* Restore permissions in order to जारी */
	चयन (fault_code) अणु
	हाल SEGV_ACCERR:
		अगर (mprotect(insns, pgsize, PROT_READ | PROT_WRITE)) अणु
			sigsafe_err("failed to set access permissions\n");
			_निकास(1);
		पूर्ण
		अवरोध;
	हाल SEGV_PKUERR:
		अगर (संकेत_pkey != fault_pkey) अणु
			sigsafe_err("got a fault for an unexpected pkey\n");
			_निकास(1);
		पूर्ण

		चयन (fault_type) अणु
		हाल PKEY_DISABLE_ACCESS:
			pkey_set_rights(fault_pkey, 0);
			अवरोध;
		हाल PKEY_DISABLE_EXECUTE:
			/*
			 * Reassociate the exec-only pkey with the region
			 * to be able to जारी. Unlike AMR, we cannot
			 * set IAMR directly from userspace to restore the
			 * permissions.
			 */
			अगर (mprotect(insns, pgsize, PROT_EXEC)) अणु
				sigsafe_err("failed to set execute permissions\n");
				_निकास(1);
			पूर्ण
			अवरोध;
		शेष:
			sigsafe_err("got a fault with an unexpected type\n");
			_निकास(1);
		पूर्ण
		अवरोध;
	शेष:
		sigsafe_err("got a fault with an unexpected code\n");
		_निकास(1);
	पूर्ण

	reमुख्यing_faults--;
पूर्ण

अटल पूर्णांक test(व्योम)
अणु
	काष्ठा sigaction segv_act, trap_act;
	अचिन्हित दीर्घ rights;
	पूर्णांक pkey, ret, i;

	ret = pkeys_unsupported();
	अगर (ret)
		वापस ret;

	/* Setup संक_अंश handler */
	segv_act.sa_handler = 0;
	segv_act.sa_sigaction = segv_handler;
	FAIL_IF(sigprocmask(SIG_SETMASK, 0, &segv_act.sa_mask) != 0);
	segv_act.sa_flags = SA_SIGINFO;
	segv_act.sa_restorer = 0;
	FAIL_IF(sigaction(संक_अंश, &segv_act, शून्य) != 0);

	/* Setup SIGTRAP handler */
	trap_act.sa_handler = 0;
	trap_act.sa_sigaction = trap_handler;
	FAIL_IF(sigprocmask(SIG_SETMASK, 0, &trap_act.sa_mask) != 0);
	trap_act.sa_flags = SA_SIGINFO;
	trap_act.sa_restorer = 0;
	FAIL_IF(sigaction(SIGTRAP, &trap_act, शून्य) != 0);

	/* Setup executable region */
	pgsize = getpagesize();
	numinsns = pgsize / माप(अचिन्हित पूर्णांक);
	insns = (अचिन्हित पूर्णांक *) mmap(शून्य, pgsize, PROT_READ | PROT_WRITE,
				      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	FAIL_IF(insns == MAP_FAILED);

	/* Write the inकाष्ठाion words */
	क्रम (i = 1; i < numinsns - 1; i++)
		insns[i] = PPC_INST_NOP;

	/*
	 * Set the first inकाष्ठाion as an unconditional trap. If
	 * the last ग_लिखो to this address succeeds, this should
	 * get overwritten by a no-op.
	 */
	insns[0] = PPC_INST_TRAP;

	/*
	 * Later, to jump to the executable region, we use a branch
	 * and link inकाष्ठाion (bctrl) which sets the वापस address
	 * स्वतःmatically in LR. Use that to वापस back.
	 */
	insns[numinsns - 1] = PPC_INST_BLR;

	/* Allocate a pkey that restricts execution */
	rights = PKEY_DISABLE_EXECUTE;
	pkey = sys_pkey_alloc(0, rights);
	FAIL_IF(pkey < 0);

	/*
	 * Pick the first inकाष्ठाion's address from the executable
	 * region.
	 */
	fault_addr = insns;

	/* The following two हालs will aव्योम SEGV_PKUERR */
	fault_type = -1;
	fault_pkey = -1;

	/*
	 * Read an inकाष्ठाion word from the address when AMR bits
	 * are not set i.e. the pkey permits both पढ़ो and ग_लिखो
	 * access.
	 *
	 * This should not generate a fault as having PROT_EXEC
	 * implies PROT_READ on GNU प्रणालीs. The pkey currently
	 * restricts execution only based on the IAMR bits. The
	 * AMR bits are cleared.
	 */
	reमुख्यing_faults = 0;
	FAIL_IF(sys_pkey_mprotect(insns, pgsize, PROT_EXEC, pkey) != 0);
	म_लिखो("read from %p, pkey permissions are %s\n", fault_addr,
	       pkey_rights(rights));
	i = *fault_addr;
	FAIL_IF(reमुख्यing_faults != 0);

	/*
	 * Write an inकाष्ठाion word to the address when AMR bits
	 * are not set i.e. the pkey permits both पढ़ो and ग_लिखो
	 * access.
	 *
	 * This should generate an access fault as having just
	 * PROT_EXEC also restricts ग_लिखोs. The pkey currently
	 * restricts execution only based on the IAMR bits. The
	 * AMR bits are cleared.
	 */
	reमुख्यing_faults = 1;
	FAIL_IF(sys_pkey_mprotect(insns, pgsize, PROT_EXEC, pkey) != 0);
	म_लिखो("write to %p, pkey permissions are %s\n", fault_addr,
	       pkey_rights(rights));
	*fault_addr = PPC_INST_TRAP;
	FAIL_IF(reमुख्यing_faults != 0 || fault_code != SEGV_ACCERR);

	/* The following three हालs will generate SEGV_PKUERR */
	rights |= PKEY_DISABLE_ACCESS;
	fault_type = PKEY_DISABLE_ACCESS;
	fault_pkey = pkey;

	/*
	 * Read an inकाष्ठाion word from the address when AMR bits
	 * are set i.e. the pkey permits neither पढ़ो nor ग_लिखो
	 * access.
	 *
	 * This should generate a pkey fault based on AMR bits only
	 * as having PROT_EXEC implicitly allows पढ़ोs.
	 */
	reमुख्यing_faults = 1;
	FAIL_IF(sys_pkey_mprotect(insns, pgsize, PROT_EXEC, pkey) != 0);
	pkey_set_rights(pkey, rights);
	म_लिखो("read from %p, pkey permissions are %s\n", fault_addr,
	       pkey_rights(rights));
	i = *fault_addr;
	FAIL_IF(reमुख्यing_faults != 0 || fault_code != SEGV_PKUERR);

	/*
	 * Write an inकाष्ठाion word to the address when AMR bits
	 * are set i.e. the pkey permits neither पढ़ो nor ग_लिखो
	 * access.
	 *
	 * This should generate two faults. First, a pkey fault
	 * based on AMR bits and then an access fault since
	 * PROT_EXEC करोes not allow ग_लिखोs.
	 */
	reमुख्यing_faults = 2;
	FAIL_IF(sys_pkey_mprotect(insns, pgsize, PROT_EXEC, pkey) != 0);
	pkey_set_rights(pkey, rights);
	म_लिखो("write to %p, pkey permissions are %s\n", fault_addr,
	       pkey_rights(rights));
	*fault_addr = PPC_INST_NOP;
	FAIL_IF(reमुख्यing_faults != 0 || fault_code != SEGV_ACCERR);

	/* Free the current pkey */
	sys_pkey_मुक्त(pkey);

	rights = 0;
	करो अणु
		/*
		 * Allocate pkeys with all valid combinations of पढ़ो,
		 * ग_लिखो and execute restrictions.
		 */
		pkey = sys_pkey_alloc(0, rights);
		FAIL_IF(pkey < 0);

		/*
		 * Jump to the executable region. AMR bits may or may not
		 * be set but they should not affect execution.
		 *
		 * This should generate pkey faults based on IAMR bits which
		 * may be set to restrict execution.
		 *
		 * The first iteration also checks अगर the overग_लिखो of the
		 * first inकाष्ठाion word from a trap to a no-op succeeded.
		 */
		fault_pkey = pkey;
		fault_type = -1;
		reमुख्यing_faults = 0;
		अगर (rights & PKEY_DISABLE_EXECUTE) अणु
			fault_type = PKEY_DISABLE_EXECUTE;
			reमुख्यing_faults = 1;
		पूर्ण

		FAIL_IF(sys_pkey_mprotect(insns, pgsize, PROT_EXEC, pkey) != 0);
		म_लिखो("execute at %p, pkey permissions are %s\n", fault_addr,
		       pkey_rights(rights));
		यंत्र अस्थिर("mtctr	%0; bctrl" : : "r"(insns));
		FAIL_IF(reमुख्यing_faults != 0);
		अगर (rights & PKEY_DISABLE_EXECUTE)
			FAIL_IF(fault_code != SEGV_PKUERR);

		/* Free the current pkey */
		sys_pkey_मुक्त(pkey);

		/* Find next valid combination of pkey rights */
		rights = next_pkey_rights(rights);
	पूर्ण जबतक (rights);

	/* Cleanup */
	munmap((व्योम *) insns, pgsize);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test, "pkey_exec_prot");
पूर्ण
