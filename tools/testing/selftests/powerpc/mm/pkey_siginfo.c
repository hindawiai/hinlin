<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2020, Sandipan Das, IBM Corp.
 *
 * Test अगर the संकेत inक्रमmation reports the correct memory protection
 * key upon getting a key access violation fault क्रम a page that was
 * attempted to be रक्षित by two dअगरferent keys from two competing
 * thपढ़ोs at the same समय.
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <संकेत.स>

#समावेश <unistd.h>
#समावेश <pthपढ़ो.h>
#समावेश <sys/mman.h>

#समावेश "pkeys.h"

#घोषणा PPC_INST_NOP	0x60000000
#घोषणा PPC_INST_BLR	0x4e800020
#घोषणा PROT_RWX	(PROT_READ | PROT_WRITE | PROT_EXEC)

#घोषणा NUM_ITERATIONS	1000000

अटल अस्थिर संक_पूर्ण_प्रकार perm_pkey, rest_pkey;
अटल अस्थिर संक_पूर्ण_प्रकार rights, fault_count;
अटल अस्थिर अचिन्हित पूर्णांक *अस्थिर fault_addr;
अटल pthपढ़ो_barrier_t iteration_barrier;

अटल व्योम segv_handler(पूर्णांक signum, siginfo_t *sinfo, व्योम *ctx)
अणु
	व्योम *pgstart;
	माप_प्रकार pgsize;
	पूर्णांक pkey;

	pkey = siginfo_pkey(sinfo);

	/* Check अगर this fault originated from a pkey access violation */
	अगर (sinfo->si_code != SEGV_PKUERR) अणु
		sigsafe_err("got a fault for an unexpected reason\n");
		_निकास(1);
	पूर्ण

	/* Check अगर this fault originated from the expected address */
	अगर (sinfo->si_addr != (व्योम *) fault_addr) अणु
		sigsafe_err("got a fault for an unexpected address\n");
		_निकास(1);
	पूर्ण

	/* Check अगर this fault originated from the restrictive pkey */
	अगर (pkey != rest_pkey) अणु
		sigsafe_err("got a fault for an unexpected pkey\n");
		_निकास(1);
	पूर्ण

	/* Check अगर too many faults have occurred क्रम the same iteration */
	अगर (fault_count > 0) अणु
		sigsafe_err("got too many faults for the same address\n");
		_निकास(1);
	पूर्ण

	pgsize = getpagesize();
	pgstart = (व्योम *) ((अचिन्हित दीर्घ) fault_addr & ~(pgsize - 1));

	/*
	 * If the current fault occurred due to lack of execute rights,
	 * reassociate the page with the exec-only pkey since execute
	 * rights cannot be changed directly क्रम the faulting pkey as
	 * IAMR is inaccessible from userspace.
	 *
	 * Otherwise, अगर the current fault occurred due to lack of
	 * पढ़ो-ग_लिखो rights, change the AMR permission bits क्रम the
	 * pkey.
	 *
	 * This will let the test जारी.
	 */
	अगर (rights == PKEY_DISABLE_EXECUTE &&
	    mprotect(pgstart, pgsize, PROT_EXEC))
		_निकास(1);
	अन्यथा
		pkey_set_rights(pkey, 0);

	fault_count++;
पूर्ण

काष्ठा region अणु
	अचिन्हित दीर्घ rights;
	अचिन्हित पूर्णांक *base;
	माप_प्रकार size;
पूर्ण;

अटल व्योम *protect(व्योम *p)
अणु
	अचिन्हित दीर्घ rights;
	अचिन्हित पूर्णांक *base;
	माप_प्रकार size;
	पूर्णांक tid, i;

	tid = gettid();
	base = ((काष्ठा region *) p)->base;
	size = ((काष्ठा region *) p)->size;
	FAIL_IF_EXIT(!base);

	/* No पढ़ो, ग_लिखो and execute restrictions */
	rights = 0;

	म_लिखो("tid %d, pkey permissions are %s\n", tid, pkey_rights(rights));

	/* Allocate the permissive pkey */
	perm_pkey = sys_pkey_alloc(0, rights);
	FAIL_IF_EXIT(perm_pkey < 0);

	/*
	 * Repeatedly try to protect the common region with a permissive
	 * pkey
	 */
	क्रम (i = 0; i < NUM_ITERATIONS; i++) अणु
		/*
		 * Wait until the other thपढ़ो has finished allocating the
		 * restrictive pkey or until the next iteration has begun
		 */
		pthपढ़ो_barrier_रुको(&iteration_barrier);

		/* Try to associate the permissive pkey with the region */
		FAIL_IF_EXIT(sys_pkey_mprotect(base, size, PROT_RWX,
					       perm_pkey));
	पूर्ण

	/* Free the permissive pkey */
	sys_pkey_मुक्त(perm_pkey);

	वापस शून्य;
पूर्ण

अटल व्योम *protect_access(व्योम *p)
अणु
	माप_प्रकार size, numinsns;
	अचिन्हित पूर्णांक *base;
	पूर्णांक tid, i;

	tid = gettid();
	base = ((काष्ठा region *) p)->base;
	size = ((काष्ठा region *) p)->size;
	rights = ((काष्ठा region *) p)->rights;
	numinsns = size / माप(base[0]);
	FAIL_IF_EXIT(!base);

	/* Allocate the restrictive pkey */
	rest_pkey = sys_pkey_alloc(0, rights);
	FAIL_IF_EXIT(rest_pkey < 0);

	म_लिखो("tid %d, pkey permissions are %s\n", tid, pkey_rights(rights));
	म_लिखो("tid %d, %s randomly in range [%p, %p]\n", tid,
	       (rights == PKEY_DISABLE_EXECUTE) ? "execute" :
	       (rights == PKEY_DISABLE_WRITE)  ? "write" : "read",
	       base, base + numinsns);

	/*
	 * Repeatedly try to protect the common region with a restrictive
	 * pkey and पढ़ो, ग_लिखो or execute from it
	 */
	क्रम (i = 0; i < NUM_ITERATIONS; i++) अणु
		/*
		 * Wait until the other thपढ़ो has finished allocating the
		 * permissive pkey or until the next iteration has begun
		 */
		pthपढ़ो_barrier_रुको(&iteration_barrier);

		/* Try to associate the restrictive pkey with the region */
		FAIL_IF_EXIT(sys_pkey_mprotect(base, size, PROT_RWX,
					       rest_pkey));

		/* Choose a अक्रमom inकाष्ठाion word address from the region */
		fault_addr = base + (अक्रम() % numinsns);
		fault_count = 0;

		चयन (rights) अणु
		/* Read protection test */
		हाल PKEY_DISABLE_ACCESS:
			/*
			 * Read an inकाष्ठाion word from the region and
			 * verअगरy अगर it has not been overwritten to
			 * something unexpected
			 */
			FAIL_IF_EXIT(*fault_addr != PPC_INST_NOP &&
				     *fault_addr != PPC_INST_BLR);
			अवरोध;

		/* Write protection test */
		हाल PKEY_DISABLE_WRITE:
			/*
			 * Write an inकाष्ठाion word to the region and
			 * verअगरy अगर the overग_लिखो has succeeded
			 */
			*fault_addr = PPC_INST_BLR;
			FAIL_IF_EXIT(*fault_addr != PPC_INST_BLR);
			अवरोध;

		/* Execute protection test */
		हाल PKEY_DISABLE_EXECUTE:
			/* Jump to the region and execute inकाष्ठाions */
			यंत्र अस्थिर(
				"mtctr	%0; bctrl"
				: : "r"(fault_addr) : "ctr", "lr");
			अवरोध;
		पूर्ण

		/*
		 * Restore the restrictions originally imposed by the
		 * restrictive pkey as the संकेत handler would have
		 * cleared out the corresponding AMR bits
		 */
		pkey_set_rights(rest_pkey, rights);
	पूर्ण

	/* Free restrictive pkey */
	sys_pkey_मुक्त(rest_pkey);

	वापस शून्य;
पूर्ण

अटल व्योम reset_pkeys(अचिन्हित दीर्घ rights)
अणु
	पूर्णांक pkeys[NR_PKEYS], i;

	/* Exhaustively allocate all available pkeys */
	क्रम (i = 0; i < NR_PKEYS; i++)
		pkeys[i] = sys_pkey_alloc(0, rights);

	/* Free all allocated pkeys */
	क्रम (i = 0; i < NR_PKEYS; i++)
		sys_pkey_मुक्त(pkeys[i]);
पूर्ण

अटल पूर्णांक test(व्योम)
अणु
	pthपढ़ो_t prot_thपढ़ो, pacc_thपढ़ो;
	काष्ठा sigaction act;
	pthपढ़ो_attr_t attr;
	माप_प्रकार numinsns;
	काष्ठा region r;
	पूर्णांक ret, i;

	बेक्रम(समय(शून्य));
	ret = pkeys_unsupported();
	अगर (ret)
		वापस ret;

	/* Allocate the region */
	r.size = getpagesize();
	r.base = mmap(शून्य, r.size, PROT_RWX,
		      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	FAIL_IF(r.base == MAP_FAILED);

	/*
	 * Fill the region with no-ops with a branch at the end
	 * क्रम वापसing to the caller
	 */
	numinsns = r.size / माप(r.base[0]);
	क्रम (i = 0; i < numinsns - 1; i++)
		r.base[i] = PPC_INST_NOP;
	r.base[i] = PPC_INST_BLR;

	/* Setup संक_अंश handler */
	act.sa_handler = 0;
	act.sa_sigaction = segv_handler;
	FAIL_IF(sigprocmask(SIG_SETMASK, 0, &act.sa_mask) != 0);
	act.sa_flags = SA_SIGINFO;
	act.sa_restorer = 0;
	FAIL_IF(sigaction(संक_अंश, &act, शून्य) != 0);

	/*
	 * For these tests, the parent process should clear all bits of
	 * AMR and IAMR, i.e. impose no restrictions, क्रम all available
	 * pkeys. This will be the base क्रम the initial AMR and IAMR
	 * values क्रम all the test thपढ़ो pairs.
	 *
	 * If the AMR and IAMR bits of all available pkeys are cleared
	 * beक्रमe running the tests and a fault is generated when
	 * attempting to पढ़ो, ग_लिखो or execute inकाष्ठाions from a
	 * pkey रक्षित region, the pkey responsible क्रम this must be
	 * the one from the protect-and-access thपढ़ो since the other
	 * one is fully permissive. Despite that, अगर the pkey reported
	 * by siginfo is not the restrictive pkey, then there must be a
	 * kernel bug.
	 */
	reset_pkeys(0);

	/* Setup barrier क्रम protect and protect-and-access thपढ़ोs */
	FAIL_IF(pthपढ़ो_attr_init(&attr) != 0);
	FAIL_IF(pthपढ़ो_barrier_init(&iteration_barrier, शून्य, 2) != 0);

	/* Setup and start protect and protect-and-पढ़ो thपढ़ोs */
	माला_दो("starting thread pair (protect, protect-and-read)");
	r.rights = PKEY_DISABLE_ACCESS;
	FAIL_IF(pthपढ़ो_create(&prot_thपढ़ो, &attr, &protect, &r) != 0);
	FAIL_IF(pthपढ़ो_create(&pacc_thपढ़ो, &attr, &protect_access, &r) != 0);
	FAIL_IF(pthपढ़ो_join(prot_thपढ़ो, शून्य) != 0);
	FAIL_IF(pthपढ़ो_join(pacc_thपढ़ो, शून्य) != 0);

	/* Setup and start protect and protect-and-ग_लिखो thपढ़ोs */
	माला_दो("starting thread pair (protect, protect-and-write)");
	r.rights = PKEY_DISABLE_WRITE;
	FAIL_IF(pthपढ़ो_create(&prot_thपढ़ो, &attr, &protect, &r) != 0);
	FAIL_IF(pthपढ़ो_create(&pacc_thपढ़ो, &attr, &protect_access, &r) != 0);
	FAIL_IF(pthपढ़ो_join(prot_thपढ़ो, शून्य) != 0);
	FAIL_IF(pthपढ़ो_join(pacc_thपढ़ो, शून्य) != 0);

	/* Setup and start protect and protect-and-execute thपढ़ोs */
	माला_दो("starting thread pair (protect, protect-and-execute)");
	r.rights = PKEY_DISABLE_EXECUTE;
	FAIL_IF(pthपढ़ो_create(&prot_thपढ़ो, &attr, &protect, &r) != 0);
	FAIL_IF(pthपढ़ो_create(&pacc_thपढ़ो, &attr, &protect_access, &r) != 0);
	FAIL_IF(pthपढ़ो_join(prot_thपढ़ो, शून्य) != 0);
	FAIL_IF(pthपढ़ो_join(pacc_thपढ़ो, शून्य) != 0);

	/* Cleanup */
	FAIL_IF(pthपढ़ो_attr_destroy(&attr) != 0);
	FAIL_IF(pthपढ़ो_barrier_destroy(&iteration_barrier) != 0);
	munmap(r.base, r.size);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test, "pkey_siginfo");
पूर्ण
