<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __I915_UTILS_H
#घोषणा __I915_UTILS_H

#समावेश <linux/list.h>
#समावेश <linux/overflow.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

काष्ठा drm_i915_निजी;
काष्ठा समयr_list;

#घोषणा FDO_BUG_URL "https://gitlab.freedesktop.org/drm/intel/-/wikis/How-to-file-i915-bugs"

#अघोषित WARN_ON
/* Many gcc seem to no see through this and fall over :( */
#अगर 0
#घोषणा WARN_ON(x) (अणु \
	bool __i915_warn_cond = (x); \
	अगर (__builtin_स्थिरant_p(__i915_warn_cond)) \
		BUILD_BUG_ON(__i915_warn_cond); \
	WARN(__i915_warn_cond, "WARN_ON(" #x ")"); पूर्ण)
#अन्यथा
#घोषणा WARN_ON(x) WARN((x), "%s", "WARN_ON(" __stringअगरy(x) ")")
#पूर्ण_अगर

#अघोषित WARN_ON_ONCE
#घोषणा WARN_ON_ONCE(x) WARN_ONCE((x), "%s", "WARN_ON_ONCE(" __stringअगरy(x) ")")

#घोषणा MISSING_CASE(x) WARN(1, "Missing case (%s == %ld)\n", \
			     __stringअगरy(x), (दीर्घ)(x))

व्योम __म_लिखो(3, 4)
__i915_prपूर्णांकk(काष्ठा drm_i915_निजी *dev_priv, स्थिर अक्षर *level,
	      स्थिर अक्षर *fmt, ...);

#घोषणा i915_report_error(dev_priv, fmt, ...)				   \
	__i915_prपूर्णांकk(dev_priv, KERN_ERR, fmt, ##__VA_ARGS__)

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG)

पूर्णांक __i915_inject_probe_error(काष्ठा drm_i915_निजी *i915, पूर्णांक err,
			      स्थिर अक्षर *func, पूर्णांक line);
#घोषणा i915_inject_probe_error(_i915, _err) \
	__i915_inject_probe_error((_i915), (_err), __func__, __LINE__)
bool i915_error_injected(व्योम);

#अन्यथा

#घोषणा i915_inject_probe_error(i915, e) (अणु BUILD_BUG_ON_INVALID(i915); 0; पूर्ण)
#घोषणा i915_error_injected() false

#पूर्ण_अगर

#घोषणा i915_inject_probe_failure(i915) i915_inject_probe_error((i915), -ENODEV)

#घोषणा i915_probe_error(i915, fmt, ...)				   \
	__i915_prपूर्णांकk(i915, i915_error_injected() ? KERN_DEBUG : KERN_ERR, \
		      fmt, ##__VA_ARGS__)

#अगर defined(GCC_VERSION) && GCC_VERSION >= 70000
#घोषणा add_overflows_t(T, A, B) \
	__builtin_add_overflow_p((A), (B), (T)0)
#अन्यथा
#घोषणा add_overflows_t(T, A, B) (अणु \
	typeof(A) a = (A); \
	typeof(B) b = (B); \
	(T)(a + b) < a; \
पूर्ण)
#पूर्ण_अगर

#घोषणा add_overflows(A, B) \
	add_overflows_t(typeof((A) + (B)), (A), (B))

#घोषणा range_overflows(start, size, max) (अणु \
	typeof(start) start__ = (start); \
	typeof(size) size__ = (size); \
	typeof(max) max__ = (max); \
	(व्योम)(&start__ == &size__); \
	(व्योम)(&start__ == &max__); \
	start__ >= max__ || size__ > max__ - start__; \
पूर्ण)

#घोषणा range_overflows_t(type, start, size, max) \
	range_overflows((type)(start), (type)(size), (type)(max))

#घोषणा range_overflows_end(start, size, max) (अणु \
	typeof(start) start__ = (start); \
	typeof(size) size__ = (size); \
	typeof(max) max__ = (max); \
	(व्योम)(&start__ == &size__); \
	(व्योम)(&start__ == &max__); \
	start__ > max__ || size__ > max__ - start__; \
पूर्ण)

#घोषणा range_overflows_end_t(type, start, size, max) \
	range_overflows_end((type)(start), (type)(size), (type)(max))

/* Note we करोn't consider signbits :| */
#घोषणा overflows_type(x, T) \
	(माप(x) > माप(T) && (x) >> BITS_PER_TYPE(T))

अटल अंतरभूत bool
__check_काष्ठा_size(माप_प्रकार base, माप_प्रकार arr, माप_प्रकार count, माप_प्रकार *size)
अणु
	माप_प्रकार sz;

	अगर (check_mul_overflow(count, arr, &sz))
		वापस false;

	अगर (check_add_overflow(sz, base, &sz))
		वापस false;

	*size = sz;
	वापस true;
पूर्ण

/**
 * check_काष्ठा_size() - Calculate size of काष्ठाure with trailing array.
 * @p: Poपूर्णांकer to the काष्ठाure.
 * @member: Name of the array member.
 * @n: Number of elements in the array.
 * @sz: Total size of काष्ठाure and array
 *
 * Calculates size of memory needed क्रम काष्ठाure @p followed by an
 * array of @n @member elements, like काष्ठा_size() but reports
 * whether it overflowed, and the resultant size in @sz
 *
 * Return: false अगर the calculation overflowed.
 */
#घोषणा check_काष्ठा_size(p, member, n, sz) \
	likely(__check_काष्ठा_size(माप(*(p)), \
				   माप(*(p)->member) + __must_be_array((p)->member), \
				   n, sz))

#घोषणा ptr_mask_bits(ptr, n) (अणु					\
	अचिन्हित दीर्घ __v = (अचिन्हित दीर्घ)(ptr);			\
	(typeof(ptr))(__v & -BIT(n));					\
पूर्ण)

#घोषणा ptr_unmask_bits(ptr, n) ((अचिन्हित दीर्घ)(ptr) & (BIT(n) - 1))

#घोषणा ptr_unpack_bits(ptr, bits, n) (अणु				\
	अचिन्हित दीर्घ __v = (अचिन्हित दीर्घ)(ptr);			\
	*(bits) = __v & (BIT(n) - 1);					\
	(typeof(ptr))(__v & -BIT(n));					\
पूर्ण)

#घोषणा ptr_pack_bits(ptr, bits, n) (अणु					\
	अचिन्हित दीर्घ __bits = (bits);					\
	GEM_BUG_ON(__bits & -BIT(n));					\
	((typeof(ptr))((अचिन्हित दीर्घ)(ptr) | __bits));			\
पूर्ण)

#घोषणा ptr_dec(ptr) (अणु							\
	अचिन्हित दीर्घ __v = (अचिन्हित दीर्घ)(ptr);			\
	(typeof(ptr))(__v - 1);						\
पूर्ण)

#घोषणा ptr_inc(ptr) (अणु							\
	अचिन्हित दीर्घ __v = (अचिन्हित दीर्घ)(ptr);			\
	(typeof(ptr))(__v + 1);						\
पूर्ण)

#घोषणा page_mask_bits(ptr) ptr_mask_bits(ptr, PAGE_SHIFT)
#घोषणा page_unmask_bits(ptr) ptr_unmask_bits(ptr, PAGE_SHIFT)
#घोषणा page_pack_bits(ptr, bits) ptr_pack_bits(ptr, bits, PAGE_SHIFT)
#घोषणा page_unpack_bits(ptr, bits) ptr_unpack_bits(ptr, bits, PAGE_SHIFT)

#घोषणा काष्ठा_member(T, member) (((T *)0)->member)

#घोषणा ptr_offset(ptr, member) दुरत्व(typeof(*(ptr)), member)

#घोषणा fetch_and_zero(ptr) (अणु						\
	typeof(*ptr) __T = *(ptr);					\
	*(ptr) = (typeof(*ptr))0;					\
	__T;								\
पूर्ण)

/*
 * container_of_user: Extract the superclass from a poपूर्णांकer to a member.
 *
 * Exactly like container_of() with the exception that it plays nicely
 * with sparse क्रम __user @ptr.
 */
#घोषणा container_of_user(ptr, type, member) (अणु				\
	व्योम __user *__mptr = (व्योम __user *)(ptr);			\
	BUILD_BUG_ON_MSG(!__same_type(*(ptr), काष्ठा_member(type, member)) && \
			 !__same_type(*(ptr), व्योम),			\
			 "pointer type mismatch in container_of()");	\
	((type __user *)(__mptr - दुरत्व(type, member))); पूर्ण)

/*
 * check_user_mbz: Check that a user value exists and is zero
 *
 * Frequently in our uABI we reserve space क्रम future extensions, and
 * two ensure that userspace is prepared we enक्रमce that space must
 * be zero. (Then any future extension can safely assume a शेष value
 * of 0.)
 *
 * check_user_mbz() combines checking that the user poपूर्णांकer is accessible
 * and that the contained value is zero.
 *
 * Returns: -EFAULT अगर not accessible, -EINVAL अगर !zero, or 0 on success.
 */
#घोषणा check_user_mbz(U) (अणु						\
	typeof(*(U)) mbz__;						\
	get_user(mbz__, (U)) ? -EFAULT : mbz__ ? -EINVAL : 0;		\
पूर्ण)

अटल अंतरभूत u64 ptr_to_u64(स्थिर व्योम *ptr)
अणु
	वापस (uपूर्णांकptr_t)ptr;
पूर्ण

#घोषणा u64_to_ptr(T, x) (अणु						\
	typecheck(u64, x);						\
	(T *)(uपूर्णांकptr_t)(x);						\
पूर्ण)

#घोषणा __mask_next_bit(mask) (अणु					\
	पूर्णांक __idx = ffs(mask) - 1;					\
	mask &= ~BIT(__idx);						\
	__idx;								\
पूर्ण)

अटल अंतरभूत bool is_घातer_of_2_u64(u64 n)
अणु
	वापस (n != 0 && ((n & (n - 1)) == 0));
पूर्ण

अटल अंतरभूत व्योम __list_del_many(काष्ठा list_head *head,
				   काष्ठा list_head *first)
अणु
	first->prev = head;
	WRITE_ONCE(head->next, first);
पूर्ण

अटल अंतरभूत पूर्णांक list_is_last_rcu(स्थिर काष्ठा list_head *list,
				   स्थिर काष्ठा list_head *head)
अणु
	वापस READ_ONCE(list->next) == head;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ msecs_to_jअगरfies_समयout(स्थिर अचिन्हित पूर्णांक m)
अणु
	अचिन्हित दीर्घ j = msecs_to_jअगरfies(m);

	वापस min_t(अचिन्हित दीर्घ, MAX_JIFFY_OFFSET, j + 1);
पूर्ण

/*
 * If you need to रुको X milliseconds between events A and B, but event B
 * करोesn't happen exactly after event A, you record the बारtamp (jअगरfies) of
 * when event A happened, then just beक्रमe event B you call this function and
 * pass the बारtamp as the first argument, and X as the second argument.
 */
अटल अंतरभूत व्योम
रुको_reमुख्यing_ms_from_jअगरfies(अचिन्हित दीर्घ बारtamp_jअगरfies, पूर्णांक to_रुको_ms)
अणु
	अचिन्हित दीर्घ target_jअगरfies, पंचांगp_jअगरfies, reमुख्यing_jअगरfies;

	/*
	 * Don't re-पढ़ो the value of "jiffies" every समय since it may change
	 * behind our back and अवरोध the math.
	 */
	पंचांगp_jअगरfies = jअगरfies;
	target_jअगरfies = बारtamp_jअगरfies +
			 msecs_to_jअगरfies_समयout(to_रुको_ms);

	अगर (समय_after(target_jअगरfies, पंचांगp_jअगरfies)) अणु
		reमुख्यing_jअगरfies = target_jअगरfies - पंचांगp_jअगरfies;
		जबतक (reमुख्यing_jअगरfies)
			reमुख्यing_jअगरfies =
			    schedule_समयout_unपूर्णांकerruptible(reमुख्यing_jअगरfies);
	पूर्ण
पूर्ण

/**
 * __रुको_क्रम - magic रुको macro
 *
 * Macro to help aव्योम खोलो coding check/रुको/समयout patterns. Note that it's
 * important that we check the condition again after having समयd out, since the
 * समयout could be due to preemption or similar and we've never had a chance to
 * check the condition beक्रमe the समयout.
 */
#घोषणा __रुको_क्रम(OP, COND, US, Wmin, Wmax) (अणु \
	स्थिर kसमय_प्रकार end__ = kसमय_add_ns(kसमय_get_raw(), 1000ll * (US)); \
	दीर्घ रुको__ = (Wmin); /* recommended min क्रम usleep is 10 us */	\
	पूर्णांक ret__;							\
	might_sleep();							\
	क्रम (;;) अणु							\
		स्थिर bool expired__ = kसमय_after(kसमय_get_raw(), end__); \
		OP;							\
		/* Guarantee COND check prior to समयout */		\
		barrier();						\
		अगर (COND) अणु						\
			ret__ = 0;					\
			अवरोध;						\
		पूर्ण							\
		अगर (expired__) अणु					\
			ret__ = -ETIMEDOUT;				\
			अवरोध;						\
		पूर्ण							\
		usleep_range(रुको__, रुको__ * 2);			\
		अगर (रुको__ < (Wmax))					\
			रुको__ <<= 1;					\
	पूर्ण								\
	ret__;								\
पूर्ण)

#घोषणा _रुको_क्रम(COND, US, Wmin, Wmax)	__रुको_क्रम(, (COND), (US), (Wmin), \
						   (Wmax))
#घोषणा रुको_क्रम(COND, MS)		_रुको_क्रम((COND), (MS) * 1000, 10, 1000)

/* If CONFIG_PREEMPT_COUNT is disabled, in_atomic() always reports false. */
#अगर defined(CONFIG_DRM_I915_DEBUG) && defined(CONFIG_PREEMPT_COUNT)
# define _WAIT_FOR_ATOMIC_CHECK(ATOMIC) WARN_ON_ONCE((ATOMIC) && !in_atomic())
#अन्यथा
# define _WAIT_FOR_ATOMIC_CHECK(ATOMIC) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा _रुको_क्रम_atomic(COND, US, ATOMIC) \
(अणु \
	पूर्णांक cpu, ret, समयout = (US) * 1000; \
	u64 base; \
	_WAIT_FOR_ATOMIC_CHECK(ATOMIC); \
	अगर (!(ATOMIC)) अणु \
		preempt_disable(); \
		cpu = smp_processor_id(); \
	पूर्ण \
	base = local_घड़ी(); \
	क्रम (;;) अणु \
		u64 now = local_घड़ी(); \
		अगर (!(ATOMIC)) \
			preempt_enable(); \
		/* Guarantee COND check prior to समयout */ \
		barrier(); \
		अगर (COND) अणु \
			ret = 0; \
			अवरोध; \
		पूर्ण \
		अगर (now - base >= समयout) अणु \
			ret = -ETIMEDOUT; \
			अवरोध; \
		पूर्ण \
		cpu_relax(); \
		अगर (!(ATOMIC)) अणु \
			preempt_disable(); \
			अगर (unlikely(cpu != smp_processor_id())) अणु \
				समयout -= now - base; \
				cpu = smp_processor_id(); \
				base = local_घड़ी(); \
			पूर्ण \
		पूर्ण \
	पूर्ण \
	ret; \
पूर्ण)

#घोषणा रुको_क्रम_us(COND, US) \
(अणु \
	पूर्णांक ret__; \
	BUILD_BUG_ON(!__builtin_स्थिरant_p(US)); \
	अगर ((US) > 10) \
		ret__ = _रुको_क्रम((COND), (US), 10, 10); \
	अन्यथा \
		ret__ = _रुको_क्रम_atomic((COND), (US), 0); \
	ret__; \
पूर्ण)

#घोषणा रुको_क्रम_atomic_us(COND, US) \
(अणु \
	BUILD_BUG_ON(!__builtin_स्थिरant_p(US)); \
	BUILD_BUG_ON((US) > 50000); \
	_रुको_क्रम_atomic((COND), (US), 1); \
पूर्ण)

#घोषणा रुको_क्रम_atomic(COND, MS) रुको_क्रम_atomic_us((COND), (MS) * 1000)

#घोषणा KHz(x) (1000 * (x))
#घोषणा MHz(x) KHz(1000 * (x))

#घोषणा KBps(x) (1000 * (x))
#घोषणा MBps(x) KBps(1000 * (x))
#घोषणा GBps(x) ((u64)1000 * MBps((x)))

अटल अंतरभूत स्थिर अक्षर *yesno(bool v)
अणु
	वापस v ? "yes" : "no";
पूर्ण

अटल अंतरभूत स्थिर अक्षर *onoff(bool v)
अणु
	वापस v ? "on" : "off";
पूर्ण

अटल अंतरभूत स्थिर अक्षर *enableddisabled(bool v)
अणु
	वापस v ? "enabled" : "disabled";
पूर्ण

व्योम add_taपूर्णांक_क्रम_CI(काष्ठा drm_i915_निजी *i915, अचिन्हित पूर्णांक taपूर्णांक);
अटल अंतरभूत व्योम __add_taपूर्णांक_क्रम_CI(अचिन्हित पूर्णांक taपूर्णांक)
अणु
	/*
	 * The प्रणाली is "ok", just about surviving क्रम the user, but
	 * CI results are now unreliable as the HW is very suspect.
	 * CI checks the taपूर्णांक state after every test and will reboot
	 * the machine अगर the kernel is taपूर्णांकed.
	 */
	add_taपूर्णांक(taपूर्णांक, LOCKDEP_STILL_OK);
पूर्ण

व्योम cancel_समयr(काष्ठा समयr_list *t);
व्योम set_समयr_ms(काष्ठा समयr_list *t, अचिन्हित दीर्घ समयout);

अटल अंतरभूत bool समयr_active(स्थिर काष्ठा समयr_list *t)
अणु
	वापस READ_ONCE(t->expires);
पूर्ण

अटल अंतरभूत bool समयr_expired(स्थिर काष्ठा समयr_list *t)
अणु
	वापस समयr_active(t) && !समयr_pending(t);
पूर्ण

/*
 * This is a lookalike क्रम IS_ENABLED() that takes a kconfig value,
 * e.g. CONFIG_DRM_I915_SPIN_REQUEST, and evaluates whether it is non-zero
 * i.e. whether the configuration is active. Wrapping up the config inside
 * a boolean context prevents clang and smatch from complaining about potential
 * issues in confusing logical-&& with bitwise-& क्रम स्थिरants.
 *
 * Sadly IS_ENABLED() itself करोes not work with kconfig values.
 *
 * Returns 0 अगर @config is 0, 1 अगर set to any value.
 */
#घोषणा IS_ACTIVE(config) ((config) != 0)

#पूर्ण_अगर /* !__I915_UTILS_H */
