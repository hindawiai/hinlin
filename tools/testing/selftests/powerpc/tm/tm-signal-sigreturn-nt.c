<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018, Breno Leitao, Gustavo Romero, IBM Corp.
 *
 * A test हाल that creates a संकेत and starts a suspended transaction
 * inside the संकेत handler.
 *
 * It वापसs from the संकेत handler with the CPU at suspended state, but
 * without setting usercontext MSR Transaction State (TS) fields.
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>

#समावेश "utils.h"
#समावेश "tm.h"

व्योम trap_संकेत_handler(पूर्णांक signo, siginfo_t *si, व्योम *uc)
अणु
	ucontext_t *ucp = (ucontext_t *) uc;

	यंत्र("tbegin.; tsuspend.;");

	/* Skip 'trap' inकाष्ठाion अगर it succeed */
	ucp->uc_mcontext.regs->nip += 4;
पूर्ण

पूर्णांक पंचांग_संकेत_sigवापस_nt(व्योम)
अणु
	काष्ठा sigaction trap_sa;

	SKIP_IF(!have_hपंचांग());

	trap_sa.sa_flags = SA_SIGINFO;
	trap_sa.sa_sigaction = trap_संकेत_handler;

	sigaction(SIGTRAP, &trap_sa, शून्य);

	उठाओ(SIGTRAP);

	वापस निकास_सफल;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	test_harness(पंचांग_संकेत_sigवापस_nt, "tm_signal_sigreturn_nt");
पूर्ण

