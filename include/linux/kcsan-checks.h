<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * KCSAN access checks and modअगरiers. These can be used to explicitly check
 * uninstrumented accesses, or change KCSAN checking behaviour of accesses.
 *
 * Copyright (C) 2019, Google LLC.
 */

#अगर_अघोषित _LINUX_KCSAN_CHECKS_H
#घोषणा _LINUX_KCSAN_CHECKS_H

/* Note: Only include what is alपढ़ोy included by compiler.h. */
#समावेश <linux/compiler_attributes.h>
#समावेश <linux/types.h>

/* Access types -- अगर KCSAN_ACCESS_WRITE is not set, the access is a पढ़ो. */
#घोषणा KCSAN_ACCESS_WRITE	(1 << 0) /* Access is a ग_लिखो. */
#घोषणा KCSAN_ACCESS_COMPOUND	(1 << 1) /* Compounded पढ़ो-ग_लिखो instrumentation. */
#घोषणा KCSAN_ACCESS_ATOMIC	(1 << 2) /* Access is atomic. */
/* The following are special, and never due to compiler instrumentation. */
#घोषणा KCSAN_ACCESS_ASSERT	(1 << 3) /* Access is an निश्चितion. */
#घोषणा KCSAN_ACCESS_SCOPED	(1 << 4) /* Access is a scoped access. */

/*
 * __kcsan_*: Always calls पूर्णांकo the runसमय when KCSAN is enabled. This may be used
 * even in compilation units that selectively disable KCSAN, but must use KCSAN
 * to validate access to an address. Never use these in header files!
 */
#अगर_घोषित CONFIG_KCSAN
/**
 * __kcsan_check_access - check generic access क्रम races
 *
 * @ptr: address of access
 * @size: size of access
 * @type: access type modअगरier
 */
व्योम __kcsan_check_access(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक type);

/**
 * kcsan_disable_current - disable KCSAN क्रम the current context
 *
 * Supports nesting.
 */
व्योम kcsan_disable_current(व्योम);

/**
 * kcsan_enable_current - re-enable KCSAN क्रम the current context
 *
 * Supports nesting.
 */
व्योम kcsan_enable_current(व्योम);
व्योम kcsan_enable_current_nowarn(व्योम); /* Safe in uaccess regions. */

/**
 * kcsan_nestable_atomic_begin - begin nestable atomic region
 *
 * Accesses within the atomic region may appear to race with other accesses but
 * should be considered atomic.
 */
व्योम kcsan_nestable_atomic_begin(व्योम);

/**
 * kcsan_nestable_atomic_end - end nestable atomic region
 */
व्योम kcsan_nestable_atomic_end(व्योम);

/**
 * kcsan_flat_atomic_begin - begin flat atomic region
 *
 * Accesses within the atomic region may appear to race with other accesses but
 * should be considered atomic.
 */
व्योम kcsan_flat_atomic_begin(व्योम);

/**
 * kcsan_flat_atomic_end - end flat atomic region
 */
व्योम kcsan_flat_atomic_end(व्योम);

/**
 * kcsan_atomic_next - consider following accesses as atomic
 *
 * Force treating the next n memory accesses क्रम the current context as atomic
 * operations.
 *
 * @n: number of following memory accesses to treat as atomic.
 */
व्योम kcsan_atomic_next(पूर्णांक n);

/**
 * kcsan_set_access_mask - set access mask
 *
 * Set the access mask क्रम all accesses क्रम the current context अगर non-zero.
 * Only value changes to bits set in the mask will be reported.
 *
 * @mask: biपंचांगask
 */
व्योम kcsan_set_access_mask(अचिन्हित दीर्घ mask);

/* Scoped access inक्रमmation. */
काष्ठा kcsan_scoped_access अणु
	काष्ठा list_head list;
	स्थिर अस्थिर व्योम *ptr;
	माप_प्रकार size;
	पूर्णांक type;
पूर्ण;
/*
 * Automatically call kcsan_end_scoped_access() when kcsan_scoped_access goes
 * out of scope; relies on attribute "cleanup", which is supported by all
 * compilers that support KCSAN.
 */
#घोषणा __kcsan_cleanup_scoped                                                 \
	__maybe_unused __attribute__((__cleanup__(kcsan_end_scoped_access)))

/**
 * kcsan_begin_scoped_access - begin scoped access
 *
 * Begin scoped access and initialize @sa, which will cause KCSAN to
 * continuously check the memory range in the current thपढ़ो until
 * kcsan_end_scoped_access() is called क्रम @sa.
 *
 * Scoped accesses are implemented by appending @sa to an पूर्णांकernal list क्रम the
 * current execution context, and then checked on every call पूर्णांकo the KCSAN
 * runसमय.
 *
 * @ptr: address of access
 * @size: size of access
 * @type: access type modअगरier
 * @sa: काष्ठा kcsan_scoped_access to use क्रम the scope of the access
 */
काष्ठा kcsan_scoped_access *
kcsan_begin_scoped_access(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक type,
			  काष्ठा kcsan_scoped_access *sa);

/**
 * kcsan_end_scoped_access - end scoped access
 *
 * End a scoped access, which will stop KCSAN checking the memory range.
 * Requires that kcsan_begin_scoped_access() was previously called once क्रम @sa.
 *
 * @sa: a previously initialized काष्ठा kcsan_scoped_access
 */
व्योम kcsan_end_scoped_access(काष्ठा kcsan_scoped_access *sa);


#अन्यथा /* CONFIG_KCSAN */

अटल अंतरभूत व्योम __kcsan_check_access(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size,
					पूर्णांक type) अणु पूर्ण

अटल अंतरभूत व्योम kcsan_disable_current(व्योम)		अणु पूर्ण
अटल अंतरभूत व्योम kcsan_enable_current(व्योम)		अणु पूर्ण
अटल अंतरभूत व्योम kcsan_enable_current_nowarn(व्योम)	अणु पूर्ण
अटल अंतरभूत व्योम kcsan_nestable_atomic_begin(व्योम)	अणु पूर्ण
अटल अंतरभूत व्योम kcsan_nestable_atomic_end(व्योम)	अणु पूर्ण
अटल अंतरभूत व्योम kcsan_flat_atomic_begin(व्योम)	अणु पूर्ण
अटल अंतरभूत व्योम kcsan_flat_atomic_end(व्योम)		अणु पूर्ण
अटल अंतरभूत व्योम kcsan_atomic_next(पूर्णांक n)		अणु पूर्ण
अटल अंतरभूत व्योम kcsan_set_access_mask(अचिन्हित दीर्घ mask) अणु पूर्ण

काष्ठा kcsan_scoped_access अणु पूर्ण;
#घोषणा __kcsan_cleanup_scoped __maybe_unused
अटल अंतरभूत काष्ठा kcsan_scoped_access *
kcsan_begin_scoped_access(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक type,
			  काष्ठा kcsan_scoped_access *sa) अणु वापस sa; पूर्ण
अटल अंतरभूत व्योम kcsan_end_scoped_access(काष्ठा kcsan_scoped_access *sa) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_KCSAN */

#अगर_घोषित __SANITIZE_THREAD__
/*
 * Only calls पूर्णांकo the runसमय when the particular compilation unit has KCSAN
 * instrumentation enabled. May be used in header files.
 */
#घोषणा kcsan_check_access __kcsan_check_access

/*
 * Only use these to disable KCSAN क्रम accesses in the current compilation unit;
 * calls पूर्णांकo libraries may still perक्रमm KCSAN checks.
 */
#घोषणा __kcsan_disable_current kcsan_disable_current
#घोषणा __kcsan_enable_current kcsan_enable_current_nowarn
#अन्यथा
अटल अंतरभूत व्योम kcsan_check_access(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size,
				      पूर्णांक type) अणु पूर्ण
अटल अंतरभूत व्योम __kcsan_enable_current(व्योम)  अणु पूर्ण
अटल अंतरभूत व्योम __kcsan_disable_current(व्योम) अणु पूर्ण
#पूर्ण_अगर

/**
 * __kcsan_check_पढ़ो - check regular पढ़ो access क्रम races
 *
 * @ptr: address of access
 * @size: size of access
 */
#घोषणा __kcsan_check_पढ़ो(ptr, size) __kcsan_check_access(ptr, size, 0)

/**
 * __kcsan_check_ग_लिखो - check regular ग_लिखो access क्रम races
 *
 * @ptr: address of access
 * @size: size of access
 */
#घोषणा __kcsan_check_ग_लिखो(ptr, size)                                         \
	__kcsan_check_access(ptr, size, KCSAN_ACCESS_WRITE)

/**
 * __kcsan_check_पढ़ो_ग_लिखो - check regular पढ़ो-ग_लिखो access क्रम races
 *
 * @ptr: address of access
 * @size: size of access
 */
#घोषणा __kcsan_check_पढ़ो_ग_लिखो(ptr, size)                                    \
	__kcsan_check_access(ptr, size, KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WRITE)

/**
 * kcsan_check_पढ़ो - check regular पढ़ो access क्रम races
 *
 * @ptr: address of access
 * @size: size of access
 */
#घोषणा kcsan_check_पढ़ो(ptr, size) kcsan_check_access(ptr, size, 0)

/**
 * kcsan_check_ग_लिखो - check regular ग_लिखो access क्रम races
 *
 * @ptr: address of access
 * @size: size of access
 */
#घोषणा kcsan_check_ग_लिखो(ptr, size)                                           \
	kcsan_check_access(ptr, size, KCSAN_ACCESS_WRITE)

/**
 * kcsan_check_पढ़ो_ग_लिखो - check regular पढ़ो-ग_लिखो access क्रम races
 *
 * @ptr: address of access
 * @size: size of access
 */
#घोषणा kcsan_check_पढ़ो_ग_लिखो(ptr, size)                                      \
	kcsan_check_access(ptr, size, KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WRITE)

/*
 * Check क्रम atomic accesses: अगर atomic accesses are not ignored, this simply
 * aliases to kcsan_check_access(), otherwise becomes a no-op.
 */
#अगर_घोषित CONFIG_KCSAN_IGNORE_ATOMICS
#घोषणा kcsan_check_atomic_पढ़ो(...)		करो अणु पूर्ण जबतक (0)
#घोषणा kcsan_check_atomic_ग_लिखो(...)		करो अणु पूर्ण जबतक (0)
#घोषणा kcsan_check_atomic_पढ़ो_ग_लिखो(...)	करो अणु पूर्ण जबतक (0)
#अन्यथा
#घोषणा kcsan_check_atomic_पढ़ो(ptr, size)                                     \
	kcsan_check_access(ptr, size, KCSAN_ACCESS_ATOMIC)
#घोषणा kcsan_check_atomic_ग_लिखो(ptr, size)                                    \
	kcsan_check_access(ptr, size, KCSAN_ACCESS_ATOMIC | KCSAN_ACCESS_WRITE)
#घोषणा kcsan_check_atomic_पढ़ो_ग_लिखो(ptr, size)                               \
	kcsan_check_access(ptr, size, KCSAN_ACCESS_ATOMIC | KCSAN_ACCESS_WRITE | KCSAN_ACCESS_COMPOUND)
#पूर्ण_अगर

/**
 * ASSERT_EXCLUSIVE_WRITER - निश्चित no concurrent ग_लिखोs to @var
 *
 * Assert that there are no concurrent ग_लिखोs to @var; other पढ़ोers are
 * allowed. This निश्चितion can be used to specअगरy properties of concurrent code,
 * where violation cannot be detected as a normal data race.
 *
 * For example, अगर we only have a single ग_लिखोr, but multiple concurrent
 * पढ़ोers, to aव्योम data races, all these accesses must be marked; even
 * concurrent marked ग_लिखोs racing with the single ग_लिखोr are bugs.
 * Unक्रमtunately, due to being marked, they are no दीर्घer data races. For हालs
 * like these, we can use the macro as follows:
 *
 * .. code-block:: c
 *
 *	व्योम ग_लिखोr(व्योम) अणु
 *		spin_lock(&update_foo_lock);
 *		ASSERT_EXCLUSIVE_WRITER(shared_foo);
 *		WRITE_ONCE(shared_foo, ...);
 *		spin_unlock(&update_foo_lock);
 *	पूर्ण
 *	व्योम पढ़ोer(व्योम) अणु
 *		// update_foo_lock करोes not need to be held!
 *		... = READ_ONCE(shared_foo);
 *	पूर्ण
 *
 * Note: ASSERT_EXCLUSIVE_WRITER_SCOPED(), अगर applicable, perक्रमms more thorough
 * checking अगर a clear scope where no concurrent ग_लिखोs are expected exists.
 *
 * @var: variable to निश्चित on
 */
#घोषणा ASSERT_EXCLUSIVE_WRITER(var)                                           \
	__kcsan_check_access(&(var), माप(var), KCSAN_ACCESS_ASSERT)

/*
 * Helper macros क्रम implementation of क्रम ASSERT_EXCLUSIVE_*_SCOPED(). @id is
 * expected to be unique क्रम the scope in which instances of kcsan_scoped_access
 * are declared.
 */
#घोषणा __kcsan_scoped_name(c, suffix) __kcsan_scoped_##c##suffix
#घोषणा __ASSERT_EXCLUSIVE_SCOPED(var, type, id)                               \
	काष्ठा kcsan_scoped_access __kcsan_scoped_name(id, _)                  \
		__kcsan_cleanup_scoped;                                        \
	काष्ठा kcsan_scoped_access *__kcsan_scoped_name(id, _dummy_p)          \
		__maybe_unused = kcsan_begin_scoped_access(                    \
			&(var), माप(var), KCSAN_ACCESS_SCOPED | (type),     \
			&__kcsan_scoped_name(id, _))

/**
 * ASSERT_EXCLUSIVE_WRITER_SCOPED - निश्चित no concurrent ग_लिखोs to @var in scope
 *
 * Scoped variant of ASSERT_EXCLUSIVE_WRITER().
 *
 * Assert that there are no concurrent ग_लिखोs to @var क्रम the duration of the
 * scope in which it is पूर्णांकroduced. This provides a better way to fully cover
 * the enclosing scope, compared to multiple ASSERT_EXCLUSIVE_WRITER(), and
 * increases the likelihood क्रम KCSAN to detect racing accesses.
 *
 * For example, it allows finding race-condition bugs that only occur due to
 * state changes within the scope itself:
 *
 * .. code-block:: c
 *
 *	व्योम ग_लिखोr(व्योम) अणु
 *		spin_lock(&update_foo_lock);
 *		अणु
 *			ASSERT_EXCLUSIVE_WRITER_SCOPED(shared_foo);
 *			WRITE_ONCE(shared_foo, 42);
 *			...
 *			// shared_foo should still be 42 here!
 *		पूर्ण
 *		spin_unlock(&update_foo_lock);
 *	पूर्ण
 *	व्योम buggy(व्योम) अणु
 *		अगर (READ_ONCE(shared_foo) == 42)
 *			WRITE_ONCE(shared_foo, 1); // bug!
 *	पूर्ण
 *
 * @var: variable to निश्चित on
 */
#घोषणा ASSERT_EXCLUSIVE_WRITER_SCOPED(var)                                    \
	__ASSERT_EXCLUSIVE_SCOPED(var, KCSAN_ACCESS_ASSERT, __COUNTER__)

/**
 * ASSERT_EXCLUSIVE_ACCESS - निश्चित no concurrent accesses to @var
 *
 * Assert that there are no concurrent accesses to @var (no पढ़ोers nor
 * ग_लिखोrs). This निश्चितion can be used to specअगरy properties of concurrent
 * code, where violation cannot be detected as a normal data race.
 *
 * For example, where exclusive access is expected after determining no other
 * users of an object are left, but the object is not actually मुक्तd. We can
 * check that this property actually holds as follows:
 *
 * .. code-block:: c
 *
 *	अगर (refcount_dec_and_test(&obj->refcnt)) अणु
 *		ASSERT_EXCLUSIVE_ACCESS(*obj);
 *		करो_some_cleanup(obj);
 *		release_क्रम_reuse(obj);
 *	पूर्ण
 *
 * Note:
 *
 * 1. ASSERT_EXCLUSIVE_ACCESS_SCOPED(), अगर applicable, perक्रमms more thorough
 *    checking अगर a clear scope where no concurrent accesses are expected exists.
 *
 * 2. For हालs where the object is मुक्तd, `KASAN <kasan.hपंचांगl>`_ is a better
 *    fit to detect use-after-मुक्त bugs.
 *
 * @var: variable to निश्चित on
 */
#घोषणा ASSERT_EXCLUSIVE_ACCESS(var)                                           \
	__kcsan_check_access(&(var), माप(var), KCSAN_ACCESS_WRITE | KCSAN_ACCESS_ASSERT)

/**
 * ASSERT_EXCLUSIVE_ACCESS_SCOPED - निश्चित no concurrent accesses to @var in scope
 *
 * Scoped variant of ASSERT_EXCLUSIVE_ACCESS().
 *
 * Assert that there are no concurrent accesses to @var (no पढ़ोers nor ग_लिखोrs)
 * क्रम the entire duration of the scope in which it is पूर्णांकroduced. This provides
 * a better way to fully cover the enclosing scope, compared to multiple
 * ASSERT_EXCLUSIVE_ACCESS(), and increases the likelihood क्रम KCSAN to detect
 * racing accesses.
 *
 * @var: variable to निश्चित on
 */
#घोषणा ASSERT_EXCLUSIVE_ACCESS_SCOPED(var)                                    \
	__ASSERT_EXCLUSIVE_SCOPED(var, KCSAN_ACCESS_WRITE | KCSAN_ACCESS_ASSERT, __COUNTER__)

/**
 * ASSERT_EXCLUSIVE_BITS - निश्चित no concurrent ग_लिखोs to subset of bits in @var
 *
 * Bit-granular variant of ASSERT_EXCLUSIVE_WRITER().
 *
 * Assert that there are no concurrent ग_लिखोs to a subset of bits in @var;
 * concurrent पढ़ोers are permitted. This निश्चितion captures more detailed
 * bit-level properties, compared to the other (word granularity) निश्चितions.
 * Only the bits set in @mask are checked क्रम concurrent modअगरications, जबतक
 * ignoring the reमुख्यing bits, i.e. concurrent ग_लिखोs (or पढ़ोs) to ~mask bits
 * are ignored.
 *
 * Use this क्रम variables, where some bits must not be modअगरied concurrently,
 * yet other bits are expected to be modअगरied concurrently.
 *
 * For example, variables where, after initialization, some bits are पढ़ो-only,
 * but other bits may still be modअगरied concurrently. A पढ़ोer may wish to
 * निश्चित that this is true as follows:
 *
 * .. code-block:: c
 *
 *	ASSERT_EXCLUSIVE_BITS(flags, READ_ONLY_MASK);
 *	foo = (READ_ONCE(flags) & READ_ONLY_MASK) >> READ_ONLY_SHIFT;
 *
 * Note: The access that immediately follows ASSERT_EXCLUSIVE_BITS() is assumed
 * to access the masked bits only, and KCSAN optimistically assumes it is
 * thereक्रमe safe, even in the presence of data races, and marking it with
 * READ_ONCE() is optional from KCSAN's poपूर्णांक-of-view. We caution, however, that
 * it may still be advisable to करो so, since we cannot reason about all compiler
 * optimizations when it comes to bit manipulations (on the पढ़ोer and ग_लिखोr
 * side). If you are sure nothing can go wrong, we can ग_लिखो the above simply
 * as:
 *
 * .. code-block:: c
 *
 *	ASSERT_EXCLUSIVE_BITS(flags, READ_ONLY_MASK);
 *	foo = (flags & READ_ONLY_MASK) >> READ_ONLY_SHIFT;
 *
 * Another example, where this may be used, is when certain bits of @var may
 * only be modअगरied when holding the appropriate lock, but other bits may still
 * be modअगरied concurrently. Writers, where other bits may change concurrently,
 * could use the निश्चितion as follows:
 *
 * .. code-block:: c
 *
 *	spin_lock(&foo_lock);
 *	ASSERT_EXCLUSIVE_BITS(flags, FOO_MASK);
 *	old_flags = flags;
 *	new_flags = (old_flags & ~FOO_MASK) | (new_foo << FOO_SHIFT);
 *	अगर (cmpxchg(&flags, old_flags, new_flags) != old_flags) अणु ... पूर्ण
 *	spin_unlock(&foo_lock);
 *
 * @var: variable to निश्चित on
 * @mask: only check क्रम modअगरications to bits set in @mask
 */
#घोषणा ASSERT_EXCLUSIVE_BITS(var, mask)                                       \
	करो अणु                                                                   \
		kcsan_set_access_mask(mask);                                   \
		__kcsan_check_access(&(var), माप(var), KCSAN_ACCESS_ASSERT);\
		kcsan_set_access_mask(0);                                      \
		kcsan_atomic_next(1);                                          \
	पूर्ण जबतक (0)

#पूर्ण_अगर /* _LINUX_KCSAN_CHECKS_H */
