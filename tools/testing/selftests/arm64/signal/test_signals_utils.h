<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2019 ARM Limited */

#अगर_अघोषित __TEST_SIGNALS_UTILS_H__
#घोषणा __TEST_SIGNALS_UTILS_H__

#समावेश <निश्चित.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>

#समावेश "test_signals.h"

पूर्णांक test_init(काष्ठा tdescr *td);
पूर्णांक test_setup(काष्ठा tdescr *td);
व्योम test_cleanup(काष्ठा tdescr *td);
पूर्णांक test_run(काष्ठा tdescr *td);
व्योम test_result(काष्ठा tdescr *td);

अटल अंतरभूत bool feats_ok(काष्ठा tdescr *td)
अणु
	वापस (td->feats_required & td->feats_supported) == td->feats_required;
पूर्ण

/*
 * Obtaining a valid and full-blown ucontext_t from userspace is tricky:
 * libc अ_लोontext करोes() not save all the regs and messes with some of
 * them (pstate value in particular is not reliable).
 *
 * Here we use a service संकेत to grab the ucontext_t from inside a
 * dedicated संकेत handler, since there, it is populated by Kernel
 * itself in setup_sigframe(). The grabbed context is then stored and
 * made available in td->live_uc.
 *
 * As service-संकेत is used a SIGTRAP induced by a 'brk' inकाष्ठाion,
 * because here we have to aव्योम syscalls to trigger the संकेत since
 * they would cause any SVE sigframe content (अगर any) to be हटाओd.
 *
 * Anyway this function really serves a dual purpose:
 *
 * 1. grab a valid sigcontext पूर्णांकo td->live_uc क्रम result analysis: in
 * such हाल it वापसs 1.
 *
 * 2. detect अगर, somehow, a previously grabbed live_uc context has been
 * used actively with a sigवापस: in such a हाल the execution would have
 * magically resumed in the middle of this function itself (seen_alपढ़ोy==1):
 * in such a हाल वापस 0, since in fact we have not just simply grabbed
 * the context.
 *
 * This latter हाल is useful to detect when a fake_sigवापस test-हाल has
 * unexpectedly survived without hitting a SEGV.
 *
 * Note that the हाल of runसमय dynamically sized sigframes (like in SVE
 * context) is still NOT addressed: sigframe size is supposed to be fixed
 * at माप(ucontext_t).
 */
अटल __always_अंतरभूत bool get_current_context(काष्ठा tdescr *td,
						ucontext_t *dest_uc)
अणु
	अटल अस्थिर bool seen_alपढ़ोy;

	निश्चित(td && dest_uc);
	/* it's a genuine invocation..reinit */
	seen_alपढ़ोy = 0;
	td->live_uc_valid = 0;
	td->live_sz = माप(*dest_uc);
	स_रखो(dest_uc, 0x00, td->live_sz);
	td->live_uc = dest_uc;
	/*
	 * Grab ucontext_t triggering a SIGTRAP.
	 *
	 * Note that:
	 * - live_uc_valid is declared अस्थिर संक_पूर्ण_प्रकार in
	 *   काष्ठा tdescr since it will be changed inside the
	 *   sig_copyctx handler
	 * - the additional 'memory' clobber is there to aव्योम possible
	 *   compiler's assumption on live_uc_valid and the content
	 *   poपूर्णांकed by dest_uc, which are all changed inside the संकेत
	 *   handler
	 * - BRK causes a debug exception which is handled by the Kernel
	 *   and finally causes the SIGTRAP संकेत to be delivered to this
	 *   test thपढ़ो. Since such delivery happens on the ret_to_user()
	 *   /करो_notअगरy_resume() debug exception वापस-path, we are sure
	 *   that the रेजिस्टरed SIGTRAP handler has been run to completion
	 *   beक्रमe the execution path is restored here: as a consequence
	 *   we can be sure that the अस्थिर संक_पूर्ण_प्रकार live_uc_valid
	 *   carries a meaningful result. Being in a single thपढ़ो context
	 *   we'll also be sure that any access to memory modअगरied by the
	 *   handler (namely ucontext_t) will be visible once वापसed.
	 * - note that since we are using a अवरोधpoपूर्णांक inकाष्ठाion here
	 *   to cause a SIGTRAP, the ucontext_t grabbed from the संकेत
	 *   handler would naturally contain a PC poपूर्णांकing exactly to this
	 *   BRK line, which means that, on वापस from the संकेत handler,
	 *   or अगर we place the ucontext_t on the stack to fake a sigवापस,
	 *   we'll end up in an infinite loop of BRK-SIGTRAP-handler.
	 *   For this reason we take care to artअगरicially move क्रमward the
	 *   PC to the next inकाष्ठाion जबतक inside the संकेत handler.
	 */
	यंत्र अस्थिर ("brk #666"
		      : "+m" (*dest_uc)
		      :
		      : "memory");

	/*
	 * If we get here with seen_alपढ़ोy==1 it implies the td->live_uc
	 * context has been used to get back here....this probably means
	 * a test has failed to cause a SEGV...anyway live_uc करोes not
	 * poपूर्णांक to a just acquired copy of ucontext_t...so वापस 0
	 */
	अगर (seen_alपढ़ोy) अणु
		ख_लिखो(मानक_निकास,
			"Unexpected successful sigreturn detected: live_uc is stale !\n");
		वापस 0;
	पूर्ण
	seen_alपढ़ोy = 1;

	वापस td->live_uc_valid;
पूर्ण

पूर्णांक fake_sigवापस(व्योम *sigframe, माप_प्रकार sz, पूर्णांक misalign_bytes);
#पूर्ण_अगर
