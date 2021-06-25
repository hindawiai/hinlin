<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * rseq.c
 *
 * Copyright (C) 2016 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 *
 * This library is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; only
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License क्रम more details.
 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <syscall.h>
#समावेश <निश्चित.स>
#समावेश <संकेत.स>
#समावेश <सीमा.स>

#समावेश "rseq.h"

#घोषणा ARRAY_SIZE(arr)	(माप(arr) / माप((arr)[0]))

__thपढ़ो अस्थिर काष्ठा rseq __rseq_abi = अणु
	.cpu_id = RSEQ_CPU_ID_UNINITIALIZED,
पूर्ण;

/*
 * Shared with other libraries. This library may take rseq ownership अगर it is
 * still 0 when executing the library स्थिरructor. Set to 1 by library
 * स्थिरructor when handling rseq. Set to 0 in deकाष्ठाor अगर handling rseq.
 */
पूर्णांक __rseq_handled;

/* Whether this library have ownership of rseq registration. */
अटल पूर्णांक rseq_ownership;

अटल __thपढ़ो अस्थिर uपूर्णांक32_t __rseq_refcount;

अटल व्योम संकेत_off_save(sigset_t *oldset)
अणु
	sigset_t set;
	पूर्णांक ret;

	sigfillset(&set);
	ret = pthपढ़ो_sigmask(SIG_BLOCK, &set, oldset);
	अगर (ret)
		पात();
पूर्ण

अटल व्योम संकेत_restore(sigset_t oldset)
अणु
	पूर्णांक ret;

	ret = pthपढ़ो_sigmask(SIG_SETMASK, &oldset, शून्य);
	अगर (ret)
		पात();
पूर्ण

अटल पूर्णांक sys_rseq(अस्थिर काष्ठा rseq *rseq_abi, uपूर्णांक32_t rseq_len,
		    पूर्णांक flags, uपूर्णांक32_t sig)
अणु
	वापस syscall(__NR_rseq, rseq_abi, rseq_len, flags, sig);
पूर्ण

पूर्णांक rseq_रेजिस्टर_current_thपढ़ो(व्योम)
अणु
	पूर्णांक rc, ret = 0;
	sigset_t oldset;

	अगर (!rseq_ownership)
		वापस 0;
	संकेत_off_save(&oldset);
	अगर (__rseq_refcount == अच_पूर्णांक_उच्च) अणु
		ret = -1;
		जाओ end;
	पूर्ण
	अगर (__rseq_refcount++)
		जाओ end;
	rc = sys_rseq(&__rseq_abi, माप(काष्ठा rseq), 0, RSEQ_SIG);
	अगर (!rc) अणु
		निश्चित(rseq_current_cpu_raw() >= 0);
		जाओ end;
	पूर्ण
	अगर (त्रुटि_सं != EBUSY)
		__rseq_abi.cpu_id = RSEQ_CPU_ID_REGISTRATION_FAILED;
	ret = -1;
	__rseq_refcount--;
end:
	संकेत_restore(oldset);
	वापस ret;
पूर्ण

पूर्णांक rseq_unरेजिस्टर_current_thपढ़ो(व्योम)
अणु
	पूर्णांक rc, ret = 0;
	sigset_t oldset;

	अगर (!rseq_ownership)
		वापस 0;
	संकेत_off_save(&oldset);
	अगर (!__rseq_refcount) अणु
		ret = -1;
		जाओ end;
	पूर्ण
	अगर (--__rseq_refcount)
		जाओ end;
	rc = sys_rseq(&__rseq_abi, माप(काष्ठा rseq),
		      RSEQ_FLAG_UNREGISTER, RSEQ_SIG);
	अगर (!rc)
		जाओ end;
	__rseq_refcount = 1;
	ret = -1;
end:
	संकेत_restore(oldset);
	वापस ret;
पूर्ण

पूर्णांक32_t rseq_fallback_current_cpu(व्योम)
अणु
	पूर्णांक32_t cpu;

	cpu = sched_अ_लोpu();
	अगर (cpu < 0) अणु
		लिखो_त्रुटि("sched_getcpu()");
		पात();
	पूर्ण
	वापस cpu;
पूर्ण

व्योम __attribute__((स्थिरructor)) rseq_init(व्योम)
अणु
	/* Check whether rseq is handled by another library. */
	अगर (__rseq_handled)
		वापस;
	__rseq_handled = 1;
	rseq_ownership = 1;
पूर्ण

व्योम __attribute__((deकाष्ठाor)) rseq_fini(व्योम)
अणु
	अगर (!rseq_ownership)
		वापस;
	__rseq_handled = 0;
	rseq_ownership = 0;
पूर्ण
