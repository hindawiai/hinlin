<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017, Gustavo Romero, IBM Corp.
 *
 * Check अगर thपढ़ो endianness is flipped inadvertently to BE on trap
 * caught in TM whilst MSR.FP and MSR.VEC are zero (i.e. just after
 * load_fp and load_vec overflowed).
 *
 * The issue can be checked on LE machines simply by zeroing load_fp
 * and load_vec and then causing a trap in TM. Since the endianness
 * changes to BE on वापस from the संकेत handler, 'nop' is
 * thपढ़ो as an illegal inकाष्ठाion in following sequence:
 *	tbegin.
 *	beq 1f
 *	trap
 *	tend.
 * 1:	nop
 *
 * However, although the issue is also present on BE machines, it's a
 * bit trickier to check it on BE machines because MSR.LE bit is set
 * to zero which determines a BE endianness that is the native
 * endianness on BE machines, so nothing notably critical happens,
 * i.e. no illegal inकाष्ठाion is observed immediately after वापसing
 * from the संकेत handler (as it happens on LE machines). Thus to test
 * it on BE machines LE endianness is क्रमced after a first trap and then
 * the endianness is verअगरied on subsequent traps to determine अगर the
 * endianness "flipped back" to the native endianness (BE).
 */

#घोषणा _GNU_SOURCE
#समावेश <error.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <hपंचांगपूर्णांकrin.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <stdbool.h>

#समावेश "tm.h"
#समावेश "utils.h"

#घोषणा pr_error(error_code, क्रमmat, ...) \
	error_at_line(1, error_code, __खाता__, __LINE__, क्रमmat, ##__VA_ARGS__)

#घोषणा MSR_LE 1UL
#घोषणा LE     1UL

pthपढ़ो_t t0_ping;
pthपढ़ो_t t1_pong;

पूर्णांक निकास_from_pong;

पूर्णांक trap_event;
पूर्णांक le;

bool success;

व्योम trap_संकेत_handler(पूर्णांक signo, siginfo_t *si, व्योम *uc)
अणु
	ucontext_t *ucp = uc;
	uपूर्णांक64_t thपढ़ो_endianness;

	/* Get thपढ़ो endianness: extract bit LE from MSR */
	thपढ़ो_endianness = MSR_LE & ucp->uc_mcontext.gp_regs[PT_MSR];

	/*
	 * Little-Endian Machine
	 */

	अगर (le) अणु
		/* First trap event */
		अगर (trap_event == 0) अणु
			/* Do nothing. Since it is वापसing from this trap
			 * event that endianness is flipped by the bug, so just
			 * let the process वापस from the संकेत handler and
			 * check on the second trap event अगर endianness is
			 * flipped or not.
			 */
		पूर्ण
		/* Second trap event */
		अन्यथा अगर (trap_event == 1) अणु
			/*
			 * Since trap was caught in TM on first trap event, अगर
			 * endianness was still LE (not flipped inadvertently)
			 * after वापसing from the संकेत handler inकाष्ठाion
			 * (1) is executed (basically a 'nop'), as it's located
			 * at address of tbegin. +4 (rollback addr). As (1) on
			 * LE endianness करोes in effect nothing, inकाष्ठाion (2)
			 * is then executed again as 'trap', generating a second
			 * trap event (note that in that हाल 'trap' is caught
			 * not in transacional mode). On te other hand, अगर after
			 * the वापस from the संकेत handler the endianness in-
			 * advertently flipped, inकाष्ठाion (1) is tपढ़ो as a
			 * branch inकाष्ठाion, i.e. b .+8, hence inकाष्ठाion (3)
			 * and (4) are executed (tbegin.; trap;) and we get sim-
			 * ilaly on the trap संकेत handler, but now in TM mode.
			 * Either way, it's now possible to check the MSR LE bit
			 * once in the trap handler to verअगरy अगर endianness was
			 * flipped or not after the वापस from the second trap
			 * event. If endianness is flipped, the bug is present.
			 * Finally, getting a trap in TM mode or not is just
			 * worth noting because it affects the math to determine
			 * the offset added to the NIP on वापस: the NIP क्रम a
			 * trap caught in TM is the rollback address, i.e. the
			 * next inकाष्ठाion after 'tbegin.', whilst the NIP क्रम
			 * a trap caught in non-transactional mode is the very
			 * same address of the 'trap' inकाष्ठाion that generated
			 * the trap event.
			 */

			अगर (thपढ़ो_endianness == LE) अणु
				/* Go to 'success', i.e. inकाष्ठाion (6) */
				ucp->uc_mcontext.gp_regs[PT_NIP] += 16;
			पूर्ण अन्यथा अणु
				/*
				 * Thपढ़ो endianness is BE, so it flipped
				 * inadvertently. Thus we flip back to LE and
				 * set NIP to go to 'failure', inकाष्ठाion (5).
				 */
				ucp->uc_mcontext.gp_regs[PT_MSR] |= 1UL;
				ucp->uc_mcontext.gp_regs[PT_NIP] += 4;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Big-Endian Machine
	 */

	अन्यथा अणु
		/* First trap event */
		अगर (trap_event == 0) अणु
			/*
			 * Force thपढ़ो endianness to be LE. Inकाष्ठाions (1),
			 * (3), and (4) will be executed, generating a second
			 * trap in TM mode.
			 */
			ucp->uc_mcontext.gp_regs[PT_MSR] |= 1UL;
		पूर्ण
		/* Second trap event */
		अन्यथा अगर (trap_event == 1) अणु
			/*
			 * Do nothing. If bug is present on वापस from this
			 * second trap event endianness will flip back "स्वतःmat-
			 * ically" to BE, otherwise thपढ़ो endianness will
			 * जारी to be LE, just as it was set above.
			 */
		पूर्ण
		/* A third trap event */
		अन्यथा अणु
			/*
			 * Once here it means that after वापसing from the sec-
			 * ond trap event inकाष्ठाion (4) (trap) was executed
			 * as LE, generating a third trap event. In that हाल
			 * endianness is still LE as set on वापस from the
			 * first trap event, hence no bug. Otherwise, bug
			 * flipped back to BE on वापस from the second trap
			 * event and inकाष्ठाion (4) was executed as 'tdi' (so
			 * basically a 'nop') and branch to 'failure' in
			 * inकाष्ठाion (5) was taken to indicate failure and we
			 * never get here.
			 */

			/*
			 * Flip back to BE and go to inकाष्ठाion (6), i.e. go to
			 * 'success'.
			 */
			ucp->uc_mcontext.gp_regs[PT_MSR] &= ~1UL;
			ucp->uc_mcontext.gp_regs[PT_NIP] += 8;
		पूर्ण
	पूर्ण

	trap_event++;
पूर्ण

व्योम usr1_संकेत_handler(पूर्णांक signo, siginfo_t *si, व्योम *not_used)
अणु
	/* Got a USR1 संकेत from ping(), so just tell pong() to निकास */
	निकास_from_pong = 1;
पूर्ण

व्योम *ping(व्योम *not_used)
अणु
	uपूर्णांक64_t i;

	trap_event = 0;

	/*
	 * Wait an amount of context चयनes so load_fp and load_vec overflows
	 * and MSR_[FP|VEC|V] is 0.
	 */
	क्रम (i = 0; i < 1024*1024*512; i++)
		;

	यंत्र जाओ(
		/*
		 * [NA] means "Native Endianness", i.e. it tells how a
		 * inकाष्ठाion is executed on machine's native endianness (in
		 * other words, native endianness matches kernel endianness).
		 * [OP] means "Opposite Endianness", i.e. on a BE machine, it
		 * tells how a inकाष्ठाion is executed as a LE inकाष्ठाion; con-
		 * versely, on a LE machine, it tells how a inकाष्ठाion is
		 * executed as a BE inकाष्ठाion. When [NA] is omitted, it means
		 * that the native पूर्णांकerpretation of a given inकाष्ठाion is not
		 * relevant क्रम the test. Likewise when [OP] is omitted.
		 */

		" tbegin.        ;" /* (0) tbegin. [NA]                    */
		" tdi  0, 0, 0x48;" /* (1) nop     [NA]; b (3) [OP]        */
		" trap           ;" /* (2) trap    [NA]                    */
		".long 0x1D05007C;" /* (3) tbegin. [OP]                    */
		".long 0x0800E07F;" /* (4) trap    [OP]; nop   [NA]        */
		" b %l[failure]  ;" /* (5) b [NA]; MSR.LE flipped (bug)    */
		" b %l[success]  ;" /* (6) b [NA]; MSR.LE did not flip (ok)*/

		: : : : failure, success);

failure:
	success = false;
	जाओ निकास_from_ping;

success:
	success = true;

निकास_from_ping:
	/* Tell pong() to निकास beक्रमe leaving */
	pthपढ़ो_समाप्त(t1_pong, SIGUSR1);
	वापस शून्य;
पूर्ण

व्योम *pong(व्योम *not_used)
अणु
	जबतक (!निकास_from_pong)
		/*
		 * Induce context चयनes on ping() thपढ़ो
		 * until ping() finishes its job and signs
		 * to निकास from this loop.
		 */
		sched_yield();

	वापस शून्य;
पूर्ण

पूर्णांक पंचांग_trap_test(व्योम)
अणु
	uपूर्णांक16_t k = 1;
	पूर्णांक cpu, rc;

	pthपढ़ो_attr_t attr;
	cpu_set_t cpuset;

	काष्ठा sigaction trap_sa;

	SKIP_IF(!have_hपंचांग());

	trap_sa.sa_flags = SA_SIGINFO;
	trap_sa.sa_sigaction = trap_संकेत_handler;
	sigaction(SIGTRAP, &trap_sa, शून्य);

	काष्ठा sigaction usr1_sa;

	usr1_sa.sa_flags = SA_SIGINFO;
	usr1_sa.sa_sigaction = usr1_संकेत_handler;
	sigaction(SIGUSR1, &usr1_sa, शून्य);

	cpu = pick_online_cpu();
	FAIL_IF(cpu < 0);

	// Set only one CPU in the mask. Both thपढ़ोs will be bound to that CPU.
	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);

	/* Init pthपढ़ो attribute */
	rc = pthपढ़ो_attr_init(&attr);
	अगर (rc)
		pr_error(rc, "pthread_attr_init()");

	/*
	 * Bind thपढ़ो ping() and pong() both to CPU 0 so they ping-pong and
	 * speed up context चयनes on ping() thपढ़ो, speeding up the load_fp
	 * and load_vec overflow.
	 */
	rc = pthपढ़ो_attr_setaffinity_np(&attr, माप(cpu_set_t), &cpuset);
	अगर (rc)
		pr_error(rc, "pthread_attr_setaffinity()");

	/* Figure out the machine endianness */
	le = (पूर्णांक) *(uपूर्णांक8_t *)&k;

	म_लिखो("%s machine detected. Checking if endianness flips %s",
		le ? "Little-Endian" : "Big-Endian",
		"inadvertently on trap in TM... ");

	rc = ख_साफ(0);
	अगर (rc)
		pr_error(rc, "fflush()");

	/* Launch ping() */
	rc = pthपढ़ो_create(&t0_ping, &attr, ping, शून्य);
	अगर (rc)
		pr_error(rc, "pthread_create()");

	निकास_from_pong = 0;

	/* Launch pong() */
	rc = pthपढ़ो_create(&t1_pong, &attr, pong, शून्य);
	अगर (rc)
		pr_error(rc, "pthread_create()");

	rc = pthपढ़ो_join(t0_ping, शून्य);
	अगर (rc)
		pr_error(rc, "pthread_join()");

	rc = pthपढ़ो_join(t1_pong, शून्य);
	अगर (rc)
		pr_error(rc, "pthread_join()");

	अगर (success) अणु
		म_लिखो("no.\n"); /* no, endianness did not flip inadvertently */
		वापस निकास_सफल;
	पूर्ण

	म_लिखो("yes!\n"); /* yes, endianness did flip inadvertently */
	वापस निकास_त्रुटि;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	वापस test_harness(पंचांग_trap_test, "tm_trap_test");
पूर्ण
