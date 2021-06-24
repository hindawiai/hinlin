<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_UACCESS_H__
#घोषणा __LINUX_UACCESS_H__

#समावेश <linux/fault-inject-usercopy.h>
#समावेश <linux/instrumented.h>
#समावेश <linux/minmax.h>
#समावेश <linux/sched.h>
#समावेश <linux/thपढ़ो_info.h>

#समावेश <यंत्र/uaccess.h>

#अगर_घोषित CONFIG_SET_FS
/*
 * Force the uaccess routines to be wired up क्रम actual userspace access,
 * overriding any possible set_fs(KERNEL_DS) still lingering around.  Unकरोne
 * using क्रमce_uaccess_end below.
 */
अटल अंतरभूत mm_segment_t क्रमce_uaccess_begin(व्योम)
अणु
	mm_segment_t fs = get_fs();

	set_fs(USER_DS);
	वापस fs;
पूर्ण

अटल अंतरभूत व्योम क्रमce_uaccess_end(mm_segment_t oldfs)
अणु
	set_fs(oldfs);
पूर्ण
#अन्यथा /* CONFIG_SET_FS */
प्रकार काष्ठा अणु
	/* empty dummy */
पूर्ण mm_segment_t;

#अगर_अघोषित TASK_SIZE_MAX
#घोषणा TASK_SIZE_MAX			TASK_SIZE
#पूर्ण_अगर

#घोषणा uaccess_kernel()		(false)
#घोषणा user_addr_max()			(TASK_SIZE_MAX)

अटल अंतरभूत mm_segment_t क्रमce_uaccess_begin(व्योम)
अणु
	वापस (mm_segment_t) अणु पूर्ण;
पूर्ण

अटल अंतरभूत व्योम क्रमce_uaccess_end(mm_segment_t oldfs)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SET_FS */

/*
 * Architectures should provide two primitives (raw_copy_अणुto,fromपूर्ण_user())
 * and get rid of their निजी instances of copy_अणुto,fromपूर्ण_user() and
 * __copy_अणुto,fromपूर्ण_userअणु,_inatomicपूर्ण().
 *
 * raw_copy_अणुto,fromपूर्ण_user(to, from, size) should copy up to size bytes and
 * वापस the amount left to copy.  They should assume that access_ok() has
 * alपढ़ोy been checked (and succeeded); they should *not* zero-pad anything.
 * No KASAN or object size checks either - those beदीर्घ here.
 *
 * Both of these functions should attempt to copy size bytes starting at from
 * पूर्णांकo the area starting at to.  They must not fetch or store anything
 * outside of those areas.  Return value must be between 0 (everything
 * copied successfully) and size (nothing copied).
 *
 * If raw_copy_अणुto,fromपूर्ण_user(to, from, size) वापसs N, size - N bytes starting
 * at to must become equal to the bytes fetched from the corresponding area
 * starting at from.  All data past to + size - N must be left unmodअगरied.
 *
 * If copying succeeds, the वापस value must be 0.  If some data cannot be
 * fetched, it is permitted to copy less than had been fetched; the only
 * hard requirement is that not storing anything at all (i.e. वापसing size)
 * should happen only when nothing could be copied.  In other words, you करोn't
 * have to squeeze as much as possible - it is allowed, but not necessary.
 *
 * For raw_copy_from_user() to always poपूर्णांकs to kernel memory and no faults
 * on store should happen.  Interpretation of from is affected by set_fs().
 * For raw_copy_to_user() it's the other way round.
 *
 * Both can be अंतरभूतd - it's up to architectures whether it wants to bother
 * with that.  They should not be used directly; they are used to implement
 * the 6 functions (copy_अणुto,fromपूर्ण_user(), __copy_अणुto,fromपूर्ण_user_inatomic())
 * that are used instead.  Out of those, __... ones are अंतरभूतd.  Plain
 * copy_अणुto,fromपूर्ण_user() might or might not be अंतरभूतd.  If you want them
 * अंतरभूतd, have यंत्र/uaccess.h define INLINE_COPY_अणुTO,FROMपूर्ण_USER.
 *
 * NOTE: only copy_from_user() zero-pads the destination in हाल of लघु copy.
 * Neither __copy_from_user() nor __copy_from_user_inatomic() zero anything
 * at all; their callers असलolutely must check the वापस value.
 *
 * Biarch ones should also provide raw_copy_in_user() - similar to the above,
 * but both source and destination are __user poपूर्णांकers (affected by set_fs()
 * as usual) and both source and destination can trigger faults.
 */

अटल __always_अंतरभूत __must_check अचिन्हित दीर्घ
__copy_from_user_inatomic(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	instrument_copy_from_user(to, from, n);
	check_object_size(to, n, false);
	वापस raw_copy_from_user(to, from, n);
पूर्ण

अटल __always_अंतरभूत __must_check अचिन्हित दीर्घ
__copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	might_fault();
	अगर (should_fail_usercopy())
		वापस n;
	instrument_copy_from_user(to, from, n);
	check_object_size(to, n, false);
	वापस raw_copy_from_user(to, from, n);
पूर्ण

/**
 * __copy_to_user_inatomic: - Copy a block of data पूर्णांकo user space, with less checking.
 * @to:   Destination address, in user space.
 * @from: Source address, in kernel space.
 * @n:    Number of bytes to copy.
 *
 * Context: User context only.
 *
 * Copy data from kernel space to user space.  Caller must check
 * the specअगरied block with access_ok() beक्रमe calling this function.
 * The caller should also make sure he pins the user space address
 * so that we करोn't result in page fault and sleep.
 */
अटल __always_अंतरभूत __must_check अचिन्हित दीर्घ
__copy_to_user_inatomic(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	अगर (should_fail_usercopy())
		वापस n;
	instrument_copy_to_user(to, from, n);
	check_object_size(from, n, true);
	वापस raw_copy_to_user(to, from, n);
पूर्ण

अटल __always_अंतरभूत __must_check अचिन्हित दीर्घ
__copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	might_fault();
	अगर (should_fail_usercopy())
		वापस n;
	instrument_copy_to_user(to, from, n);
	check_object_size(from, n, true);
	वापस raw_copy_to_user(to, from, n);
पूर्ण

#अगर_घोषित INLINE_COPY_FROM_USER
अटल अंतरभूत __must_check अचिन्हित दीर्घ
_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ res = n;
	might_fault();
	अगर (!should_fail_usercopy() && likely(access_ok(from, n))) अणु
		instrument_copy_from_user(to, from, n);
		res = raw_copy_from_user(to, from, n);
	पूर्ण
	अगर (unlikely(res))
		स_रखो(to + (n - res), 0, res);
	वापस res;
पूर्ण
#अन्यथा
बाह्य __must_check अचिन्हित दीर्घ
_copy_from_user(व्योम *, स्थिर व्योम __user *, अचिन्हित दीर्घ);
#पूर्ण_अगर

#अगर_घोषित INLINE_COPY_TO_USER
अटल अंतरभूत __must_check अचिन्हित दीर्घ
_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	might_fault();
	अगर (should_fail_usercopy())
		वापस n;
	अगर (access_ok(to, n)) अणु
		instrument_copy_to_user(to, from, n);
		n = raw_copy_to_user(to, from, n);
	पूर्ण
	वापस n;
पूर्ण
#अन्यथा
बाह्य __must_check अचिन्हित दीर्घ
_copy_to_user(व्योम __user *, स्थिर व्योम *, अचिन्हित दीर्घ);
#पूर्ण_अगर

अटल __always_अंतरभूत अचिन्हित दीर्घ __must_check
copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	अगर (likely(check_copy_size(to, n, false)))
		n = _copy_from_user(to, from, n);
	वापस n;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ __must_check
copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	अगर (likely(check_copy_size(from, n, true)))
		n = _copy_to_user(to, from, n);
	वापस n;
पूर्ण
#अगर_घोषित CONFIG_COMPAT
अटल __always_अंतरभूत अचिन्हित दीर्घ __must_check
copy_in_user(व्योम __user *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	might_fault();
	अगर (access_ok(to, n) && access_ok(from, n))
		n = raw_copy_in_user(to, from, n);
	वापस n;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित copy_mc_to_kernel
/*
 * Without arch opt-in this generic copy_mc_to_kernel() will not handle
 * #MC (or arch equivalent) during source पढ़ो.
 */
अटल अंतरभूत अचिन्हित दीर्घ __must_check
copy_mc_to_kernel(व्योम *dst, स्थिर व्योम *src, माप_प्रकार cnt)
अणु
	स_नकल(dst, src, cnt);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल __always_अंतरभूत व्योम pagefault_disabled_inc(व्योम)
अणु
	current->pagefault_disabled++;
पूर्ण

अटल __always_अंतरभूत व्योम pagefault_disabled_dec(व्योम)
अणु
	current->pagefault_disabled--;
पूर्ण

/*
 * These routines enable/disable the pagefault handler. If disabled, it will
 * not take any locks and go straight to the fixup table.
 *
 * User access methods will not sleep when called from a pagefault_disabled()
 * environment.
 */
अटल अंतरभूत व्योम pagefault_disable(व्योम)
अणु
	pagefault_disabled_inc();
	/*
	 * make sure to have issued the store beक्रमe a pagefault
	 * can hit.
	 */
	barrier();
पूर्ण

अटल अंतरभूत व्योम pagefault_enable(व्योम)
अणु
	/*
	 * make sure to issue those last loads/stores beक्रमe enabling
	 * the pagefault handler again.
	 */
	barrier();
	pagefault_disabled_dec();
पूर्ण

/*
 * Is the pagefault handler disabled? If so, user access methods will not sleep.
 */
अटल अंतरभूत bool pagefault_disabled(व्योम)
अणु
	वापस current->pagefault_disabled != 0;
पूर्ण

/*
 * The pagefault handler is in general disabled by pagefault_disable() or
 * when in irq context (via in_atomic()).
 *
 * This function should only be used by the fault handlers. Other users should
 * stick to pagefault_disabled().
 * Please NEVER use preempt_disable() to disable the fault handler. With
 * !CONFIG_PREEMPT_COUNT, this is like a NOP. So the handler won't be disabled.
 * in_atomic() will report dअगरferent values based on !CONFIG_PREEMPT_COUNT.
 */
#घोषणा faulthandler_disabled() (pagefault_disabled() || in_atomic())

#अगर_अघोषित ARCH_HAS_NOCACHE_UACCESS

अटल अंतरभूत __must_check अचिन्हित दीर्घ
__copy_from_user_inatomic_nocache(व्योम *to, स्थिर व्योम __user *from,
				  अचिन्हित दीर्घ n)
अणु
	वापस __copy_from_user_inatomic(to, from, n);
पूर्ण

#पूर्ण_अगर		/* ARCH_HAS_NOCACHE_UACCESS */

बाह्य __must_check पूर्णांक check_zeroed_user(स्थिर व्योम __user *from, माप_प्रकार size);

/**
 * copy_काष्ठा_from_user: copy a काष्ठा from userspace
 * @dst:   Destination address, in kernel space. This buffer must be @ksize
 *         bytes दीर्घ.
 * @ksize: Size of @dst काष्ठा.
 * @src:   Source address, in userspace.
 * @usize: (Alleged) size of @src काष्ठा.
 *
 * Copies a काष्ठा from userspace to kernel space, in a way that guarantees
 * backwards-compatibility क्रम काष्ठा syscall arguments (as दीर्घ as future
 * काष्ठा extensions are made such that all new fields are *appended* to the
 * old काष्ठा, and zeroed-out new fields have the same meaning as the old
 * काष्ठा).
 *
 * @ksize is just माप(*dst), and @usize should've been passed by userspace.
 * The recommended usage is something like the following:
 *
 *   SYSCALL_DEFINE2(foobar, स्थिर काष्ठा foo __user *, uarg, माप_प्रकार, usize)
 *   अणु
 *      पूर्णांक err;
 *      काष्ठा foo karg = अणुपूर्ण;
 *
 *      अगर (usize > PAGE_SIZE)
 *        वापस -E2BIG;
 *      अगर (usize < FOO_SIZE_VER0)
 *        वापस -EINVAL;
 *
 *      err = copy_काष्ठा_from_user(&karg, माप(karg), uarg, usize);
 *      अगर (err)
 *        वापस err;
 *
 *      // ...
 *   पूर्ण
 *
 * There are three हालs to consider:
 *  * If @usize == @ksize, then it's copied verbatim.
 *  * If @usize < @ksize, then the userspace has passed an old काष्ठा to a
 *    newer kernel. The rest of the trailing bytes in @dst (@ksize - @usize)
 *    are to be zero-filled.
 *  * If @usize > @ksize, then the userspace has passed a new काष्ठा to an
 *    older kernel. The trailing bytes unknown to the kernel (@usize - @ksize)
 *    are checked to ensure they are zeroed, otherwise -E2BIG is वापसed.
 *
 * Returns (in all हालs, some data may have been copied):
 *  * -E2BIG:  (@usize > @ksize) and there are non-zero trailing bytes in @src.
 *  * -EFAULT: access to userspace failed.
 */
अटल __always_अंतरभूत __must_check पूर्णांक
copy_काष्ठा_from_user(व्योम *dst, माप_प्रकार ksize, स्थिर व्योम __user *src,
		      माप_प्रकार usize)
अणु
	माप_प्रकार size = min(ksize, usize);
	माप_प्रकार rest = max(ksize, usize) - size;

	/* Deal with trailing bytes. */
	अगर (usize < ksize) अणु
		स_रखो(dst + size, 0, rest);
	पूर्ण अन्यथा अगर (usize > ksize) अणु
		पूर्णांक ret = check_zeroed_user(src + size, rest);
		अगर (ret <= 0)
			वापस ret ?: -E2BIG;
	पूर्ण
	/* Copy the पूर्णांकeroperable parts of the काष्ठा. */
	अगर (copy_from_user(dst, src, size))
		वापस -EFAULT;
	वापस 0;
पूर्ण

bool copy_from_kernel_nofault_allowed(स्थिर व्योम *unsafe_src, माप_प्रकार size);

दीर्घ copy_from_kernel_nofault(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size);
दीर्घ notrace copy_to_kernel_nofault(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size);

दीर्घ copy_from_user_nofault(व्योम *dst, स्थिर व्योम __user *src, माप_प्रकार size);
दीर्घ notrace copy_to_user_nofault(व्योम __user *dst, स्थिर व्योम *src,
		माप_प्रकार size);

दीर्घ म_नकलन_from_kernel_nofault(अक्षर *dst, स्थिर व्योम *unsafe_addr,
		दीर्घ count);

दीर्घ म_नकलन_from_user_nofault(अक्षर *dst, स्थिर व्योम __user *unsafe_addr,
		दीर्घ count);
दीर्घ strnlen_user_nofault(स्थिर व्योम __user *unsafe_addr, दीर्घ count);

/**
 * get_kernel_nofault(): safely attempt to पढ़ो from a location
 * @val: पढ़ो पूर्णांकo this variable
 * @ptr: address to पढ़ो from
 *
 * Returns 0 on success, or -EFAULT.
 */
#घोषणा get_kernel_nofault(val, ptr) (अणु				\
	स्थिर typeof(val) *__gk_ptr = (ptr);			\
	copy_from_kernel_nofault(&(val), __gk_ptr, माप(val));\
पूर्ण)

#अगर_अघोषित user_access_begin
#घोषणा user_access_begin(ptr,len) access_ok(ptr, len)
#घोषणा user_access_end() करो अणु पूर्ण जबतक (0)
#घोषणा unsafe_op_wrap(op, err) करो अणु अगर (unlikely(op)) जाओ err; पूर्ण जबतक (0)
#घोषणा unsafe_get_user(x,p,e) unsafe_op_wrap(__get_user(x,p),e)
#घोषणा unsafe_put_user(x,p,e) unsafe_op_wrap(__put_user(x,p),e)
#घोषणा unsafe_copy_to_user(d,s,l,e) unsafe_op_wrap(__copy_to_user(d,s,l),e)
#घोषणा unsafe_copy_from_user(d,s,l,e) unsafe_op_wrap(__copy_from_user(d,s,l),e)
अटल अंतरभूत अचिन्हित दीर्घ user_access_save(व्योम) अणु वापस 0UL; पूर्ण
अटल अंतरभूत व्योम user_access_restore(अचिन्हित दीर्घ flags) अणु पूर्ण
#पूर्ण_अगर
#अगर_अघोषित user_ग_लिखो_access_begin
#घोषणा user_ग_लिखो_access_begin user_access_begin
#घोषणा user_ग_लिखो_access_end user_access_end
#पूर्ण_अगर
#अगर_अघोषित user_पढ़ो_access_begin
#घोषणा user_पढ़ो_access_begin user_access_begin
#घोषणा user_पढ़ो_access_end user_access_end
#पूर्ण_अगर

#अगर_घोषित CONFIG_HARDENED_USERCOPY
व्योम usercopy_warn(स्थिर अक्षर *name, स्थिर अक्षर *detail, bool to_user,
		   अचिन्हित दीर्घ offset, अचिन्हित दीर्घ len);
व्योम __noवापस usercopy_पात(स्थिर अक्षर *name, स्थिर अक्षर *detail,
			       bool to_user, अचिन्हित दीर्घ offset,
			       अचिन्हित दीर्घ len);
#पूर्ण_अगर

#पूर्ण_अगर		/* __LINUX_UACCESS_H__ */
