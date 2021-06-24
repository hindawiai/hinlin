<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <संकेत.स>
#समावेश "subcmd-util.h"
#समावेश "sigchain.h"

#घोषणा SIGCHAIN_MAX_SIGNALS 32

काष्ठा sigchain_संकेत अणु
	sigchain_fun *old;
	पूर्णांक n;
	पूर्णांक alloc;
पूर्ण;
अटल काष्ठा sigchain_संकेत संकेतs[SIGCHAIN_MAX_SIGNALS];

अटल व्योम check_signum(पूर्णांक sig)
अणु
	अगर (sig < 1 || sig >= SIGCHAIN_MAX_SIGNALS)
		die("BUG: signal out of range: %d", sig);
पूर्ण

अटल पूर्णांक sigchain_push(पूर्णांक sig, sigchain_fun f)
अणु
	काष्ठा sigchain_संकेत *s = संकेतs + sig;
	check_signum(sig);

	ALLOC_GROW(s->old, s->n + 1, s->alloc);
	s->old[s->n] = संकेत(sig, f);
	अगर (s->old[s->n] == संक_त्रुटि)
		वापस -1;
	s->n++;
	वापस 0;
पूर्ण

पूर्णांक sigchain_pop(पूर्णांक sig)
अणु
	काष्ठा sigchain_संकेत *s = संकेतs + sig;
	check_signum(sig);
	अगर (s->n < 1)
		वापस 0;

	अगर (संकेत(sig, s->old[s->n - 1]) == संक_त्रुटि)
		वापस -1;
	s->n--;
	वापस 0;
पूर्ण

व्योम sigchain_push_common(sigchain_fun f)
अणु
	sigchain_push(संक_विघ्न, f);
	sigchain_push(SIGHUP, f);
	sigchain_push(संक_इति, f);
	sigchain_push(SIGQUIT, f);
	sigchain_push(SIGPIPE, f);
पूर्ण
