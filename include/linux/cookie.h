<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_COOKIE_H
#घोषणा __LINUX_COOKIE_H

#समावेश <linux/atomic.h>
#समावेश <linux/percpu.h>
#समावेश <यंत्र/local.h>

काष्ठा pcpu_gen_cookie अणु
	local_t nesting;
	u64 last;
पूर्ण __aligned(16);

काष्ठा gen_cookie अणु
	काष्ठा pcpu_gen_cookie __percpu *local;
	atomic64_t क्रमward_last ____cacheline_aligned_in_smp;
	atomic64_t reverse_last;
पूर्ण;

#घोषणा COOKIE_LOCAL_BATCH	4096

#घोषणा DEFINE_COOKIE(name)						\
	अटल DEFINE_PER_CPU(काष्ठा pcpu_gen_cookie, __##name);	\
	अटल काष्ठा gen_cookie name = अणु				\
		.local		= &__##name,				\
		.क्रमward_last	= ATOMIC64_INIT(0),			\
		.reverse_last	= ATOMIC64_INIT(0),			\
	पूर्ण

अटल __always_अंतरभूत u64 gen_cookie_next(काष्ठा gen_cookie *gc)
अणु
	काष्ठा pcpu_gen_cookie *local = this_cpu_ptr(gc->local);
	u64 val;

	अगर (likely(local_inc_वापस(&local->nesting) == 1)) अणु
		val = local->last;
		अगर (__is_defined(CONFIG_SMP) &&
		    unlikely((val & (COOKIE_LOCAL_BATCH - 1)) == 0)) अणु
			s64 next = atomic64_add_वापस(COOKIE_LOCAL_BATCH,
						       &gc->क्रमward_last);
			val = next - COOKIE_LOCAL_BATCH;
		पूर्ण
		local->last = ++val;
	पूर्ण अन्यथा अणु
		val = atomic64_dec_वापस(&gc->reverse_last);
	पूर्ण
	local_dec(&local->nesting);
	वापस val;
पूर्ण

#पूर्ण_अगर /* __LINUX_COOKIE_H */
