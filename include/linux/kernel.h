<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_KERNEL_H
#घोषणा _LINUX_KERNEL_H

#समावेश <मानकतर्क.स>
#समावेश <linux/align.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/linkage.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/bitops.h>
#समावेश <linux/log2.h>
#समावेश <linux/गणित.स>
#समावेश <linux/minmax.h>
#समावेश <linux/typecheck.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/build_bug.h>
#समावेश <linux/अटल_call_types.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <uapi/linux/kernel.h>

#घोषणा STACK_MAGIC	0xdeadbeef

/**
 * REPEAT_BYTE - repeat the value @x multiple बार as an अचिन्हित दीर्घ value
 * @x: value to repeat
 *
 * NOTE: @x is not checked क्रम > 0xff; larger values produce odd results.
 */
#घोषणा REPEAT_BYTE(x)	((~0ul / 0xff) * (x))

/* generic data direction definitions */
#घोषणा READ			0
#घोषणा WRITE			1

/**
 * ARRAY_SIZE - get the number of elements in array @arr
 * @arr: array to be sized
 */
#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]) + __must_be_array(arr))

#घोषणा PTR_IF(cond, ptr)	((cond) ? (ptr) : शून्य)

#घोषणा u64_to_user_ptr(x) (		\
अणु					\
	typecheck(u64, (x));		\
	(व्योम __user *)(uपूर्णांकptr_t)(x);	\
पूर्ण					\
)

#घोषणा typeof_member(T, m)	typeof(((T*)0)->m)

#घोषणा _RET_IP_		(अचिन्हित दीर्घ)__builtin_वापस_address(0)
#घोषणा _THIS_IP_  (अणु __label__ __here; __here: (अचिन्हित दीर्घ)&&__here; पूर्ण)

/**
 * upper_32_bits - वापस bits 32-63 of a number
 * @n: the number we're accessing
 *
 * A basic shअगरt-right of a 64- or 32-bit quantity.  Use this to suppress
 * the "right shift count >= width of type" warning when that quantity is
 * 32-bits.
 */
#घोषणा upper_32_bits(n) ((u32)(((n) >> 16) >> 16))

/**
 * lower_32_bits - वापस bits 0-31 of a number
 * @n: the number we're accessing
 */
#घोषणा lower_32_bits(n) ((u32)((n) & 0xffffffff))

काष्ठा completion;
काष्ठा pt_regs;
काष्ठा user;

#अगर_घोषित CONFIG_PREEMPT_VOLUNTARY

बाह्य पूर्णांक __cond_resched(व्योम);
# define might_resched() __cond_resched()

#या_अगर defined(CONFIG_PREEMPT_DYNAMIC)

बाह्य पूर्णांक __cond_resched(व्योम);

DECLARE_STATIC_CALL(might_resched, __cond_resched);

अटल __always_अंतरभूत व्योम might_resched(व्योम)
अणु
	अटल_call_mod(might_resched)();
पूर्ण

#अन्यथा

# define might_resched() करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_PREEMPT_* */

#अगर_घोषित CONFIG_DEBUG_ATOMIC_SLEEP
बाह्य व्योम ___might_sleep(स्थिर अक्षर *file, पूर्णांक line, पूर्णांक preempt_offset);
बाह्य व्योम __might_sleep(स्थिर अक्षर *file, पूर्णांक line, पूर्णांक preempt_offset);
बाह्य व्योम __cant_sleep(स्थिर अक्षर *file, पूर्णांक line, पूर्णांक preempt_offset);
बाह्य व्योम __cant_migrate(स्थिर अक्षर *file, पूर्णांक line);

/**
 * might_sleep - annotation क्रम functions that can sleep
 *
 * this macro will prपूर्णांक a stack trace अगर it is executed in an atomic
 * context (spinlock, irq-handler, ...). Additional sections where blocking is
 * not allowed can be annotated with non_block_start() and non_block_end()
 * pairs.
 *
 * This is a useful debugging help to be able to catch problems early and not
 * be bitten later when the calling function happens to sleep when it is not
 * supposed to.
 */
# define might_sleep() \
	करो अणु __might_sleep(__खाता__, __LINE__, 0); might_resched(); पूर्ण जबतक (0)
/**
 * cant_sleep - annotation क्रम functions that cannot sleep
 *
 * this macro will prपूर्णांक a stack trace अगर it is executed with preemption enabled
 */
# define cant_sleep() \
	करो अणु __cant_sleep(__खाता__, __LINE__, 0); पूर्ण जबतक (0)
# define sched_annotate_sleep()	(current->task_state_change = 0)

/**
 * cant_migrate - annotation क्रम functions that cannot migrate
 *
 * Will prपूर्णांक a stack trace अगर executed in code which is migratable
 */
# define cant_migrate()							\
	करो अणु								\
		अगर (IS_ENABLED(CONFIG_SMP))				\
			__cant_migrate(__खाता__, __LINE__);		\
	पूर्ण जबतक (0)

/**
 * non_block_start - annotate the start of section where sleeping is prohibited
 *
 * This is on behalf of the oom reaper, specअगरically when it is calling the mmu
 * notअगरiers. The problem is that अगर the notअगरier were to block on, क्रम example,
 * mutex_lock() and अगर the process which holds that mutex were to perक्रमm a
 * sleeping memory allocation, the oom reaper is now blocked on completion of
 * that memory allocation. Other blocking calls like रुको_event() pose similar
 * issues.
 */
# define non_block_start() (current->non_block_count++)
/**
 * non_block_end - annotate the end of section where sleeping is prohibited
 *
 * Closes a section खोलोed by non_block_start().
 */
# define non_block_end() WARN_ON(current->non_block_count-- == 0)
#अन्यथा
  अटल अंतरभूत व्योम ___might_sleep(स्थिर अक्षर *file, पूर्णांक line,
				   पूर्णांक preempt_offset) अणु पूर्ण
  अटल अंतरभूत व्योम __might_sleep(स्थिर अक्षर *file, पूर्णांक line,
				   पूर्णांक preempt_offset) अणु पूर्ण
# define might_sleep() करो अणु might_resched(); पूर्ण जबतक (0)
# define cant_sleep() करो अणु पूर्ण जबतक (0)
# define cant_migrate()		करो अणु पूर्ण जबतक (0)
# define sched_annotate_sleep() करो अणु पूर्ण जबतक (0)
# define non_block_start() करो अणु पूर्ण जबतक (0)
# define non_block_end() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा might_sleep_अगर(cond) करो अणु अगर (cond) might_sleep(); पूर्ण जबतक (0)

#अगर defined(CONFIG_MMU) && \
	(defined(CONFIG_PROVE_LOCKING) || defined(CONFIG_DEBUG_ATOMIC_SLEEP))
#घोषणा might_fault() __might_fault(__खाता__, __LINE__)
व्योम __might_fault(स्थिर अक्षर *file, पूर्णांक line);
#अन्यथा
अटल अंतरभूत व्योम might_fault(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य काष्ठा atomic_notअगरier_head panic_notअगरier_list;
बाह्य दीर्घ (*panic_blink)(पूर्णांक state);
__म_लिखो(1, 2)
व्योम panic(स्थिर अक्षर *fmt, ...) __noवापस __cold;
व्योम nmi_panic(काष्ठा pt_regs *regs, स्थिर अक्षर *msg);
बाह्य व्योम oops_enter(व्योम);
बाह्य व्योम oops_निकास(व्योम);
बाह्य bool oops_may_prपूर्णांक(व्योम);
व्योम करो_निकास(दीर्घ error_code) __noवापस;
व्योम complete_and_निकास(काष्ठा completion *, दीर्घ) __noवापस;

/* Internal, करो not use. */
पूर्णांक __must_check _kम_से_अदीर्घ(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ *res);
पूर्णांक __must_check _kम_से_दीर्घ(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, दीर्घ *res);

पूर्णांक __must_check kम_से_अदीर्घl(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ दीर्घ *res);
पूर्णांक __must_check kम_से_दीर्घl(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, दीर्घ दीर्घ *res);

/**
 * kम_से_अदीर्घ - convert a string to an अचिन्हित दीर्घ
 * @s: The start of the string. The string must be null-terminated, and may also
 *  include a single newline beक्रमe its terminating null. The first अक्षरacter
 *  may also be a plus sign, but not a minus sign.
 * @base: The number base to use. The maximum supported base is 16. If base is
 *  given as 0, then the base of the string is स्वतःmatically detected with the
 *  conventional semantics - If it begins with 0x the number will be parsed as a
 *  hexadecimal (हाल insensitive), अगर it otherwise begins with 0, it will be
 *  parsed as an octal number. Otherwise it will be parsed as a decimal.
 * @res: Where to ग_लिखो the result of the conversion on success.
 *
 * Returns 0 on success, -दुस्फल on overflow and -EINVAL on parsing error.
 * Preferred over simple_म_से_अदीर्घ(). Return code must be checked.
*/
अटल अंतरभूत पूर्णांक __must_check kम_से_अदीर्घ(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ *res)
अणु
	/*
	 * We want to लघुcut function call, but
	 * __builtin_types_compatible_p(अचिन्हित दीर्घ, अचिन्हित दीर्घ दीर्घ) = 0.
	 */
	अगर (माप(अचिन्हित दीर्घ) == माप(अचिन्हित दीर्घ दीर्घ) &&
	    __alignof__(अचिन्हित दीर्घ) == __alignof__(अचिन्हित दीर्घ दीर्घ))
		वापस kम_से_अदीर्घl(s, base, (अचिन्हित दीर्घ दीर्घ *)res);
	अन्यथा
		वापस _kम_से_अदीर्घ(s, base, res);
पूर्ण

/**
 * kम_से_दीर्घ - convert a string to a दीर्घ
 * @s: The start of the string. The string must be null-terminated, and may also
 *  include a single newline beक्रमe its terminating null. The first अक्षरacter
 *  may also be a plus sign or a minus sign.
 * @base: The number base to use. The maximum supported base is 16. If base is
 *  given as 0, then the base of the string is स्वतःmatically detected with the
 *  conventional semantics - If it begins with 0x the number will be parsed as a
 *  hexadecimal (हाल insensitive), अगर it otherwise begins with 0, it will be
 *  parsed as an octal number. Otherwise it will be parsed as a decimal.
 * @res: Where to ग_लिखो the result of the conversion on success.
 *
 * Returns 0 on success, -दुस्फल on overflow and -EINVAL on parsing error.
 * Preferred over simple_म_से_दीर्घ(). Return code must be checked.
 */
अटल अंतरभूत पूर्णांक __must_check kम_से_दीर्घ(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, दीर्घ *res)
अणु
	/*
	 * We want to लघुcut function call, but
	 * __builtin_types_compatible_p(दीर्घ, दीर्घ दीर्घ) = 0.
	 */
	अगर (माप(दीर्घ) == माप(दीर्घ दीर्घ) &&
	    __alignof__(दीर्घ) == __alignof__(दीर्घ दीर्घ))
		वापस kम_से_दीर्घl(s, base, (दीर्घ दीर्घ *)res);
	अन्यथा
		वापस _kम_से_दीर्घ(s, base, res);
पूर्ण

पूर्णांक __must_check kstrtouपूर्णांक(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक *res);
पूर्णांक __must_check kstrtoपूर्णांक(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, पूर्णांक *res);

अटल अंतरभूत पूर्णांक __must_check kstrtou64(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, u64 *res)
अणु
	वापस kम_से_अदीर्घl(s, base, res);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check kstrtos64(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, s64 *res)
अणु
	वापस kम_से_दीर्घl(s, base, res);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check kstrtou32(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, u32 *res)
अणु
	वापस kstrtouपूर्णांक(s, base, res);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check kstrtos32(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, s32 *res)
अणु
	वापस kstrtoपूर्णांक(s, base, res);
पूर्ण

पूर्णांक __must_check kstrtou16(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, u16 *res);
पूर्णांक __must_check kstrtos16(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, s16 *res);
पूर्णांक __must_check kstrtou8(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, u8 *res);
पूर्णांक __must_check kstrtos8(स्थिर अक्षर *s, अचिन्हित पूर्णांक base, s8 *res);
पूर्णांक __must_check kstrtobool(स्थिर अक्षर *s, bool *res);

पूर्णांक __must_check kम_से_अदीर्घl_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ दीर्घ *res);
पूर्णांक __must_check kम_से_दीर्घl_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, दीर्घ दीर्घ *res);
पूर्णांक __must_check kम_से_अदीर्घ_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, अचिन्हित दीर्घ *res);
पूर्णांक __must_check kम_से_दीर्घ_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, दीर्घ *res);
पूर्णांक __must_check kstrtouपूर्णांक_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक *res);
पूर्णांक __must_check kstrtoपूर्णांक_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, पूर्णांक *res);
पूर्णांक __must_check kstrtou16_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, u16 *res);
पूर्णांक __must_check kstrtos16_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, s16 *res);
पूर्णांक __must_check kstrtou8_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, u8 *res);
पूर्णांक __must_check kstrtos8_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, s8 *res);
पूर्णांक __must_check kstrtobool_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, bool *res);

अटल अंतरभूत पूर्णांक __must_check kstrtou64_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, u64 *res)
अणु
	वापस kम_से_अदीर्घl_from_user(s, count, base, res);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check kstrtos64_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, s64 *res)
अणु
	वापस kम_से_दीर्घl_from_user(s, count, base, res);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check kstrtou32_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, u32 *res)
अणु
	वापस kstrtouपूर्णांक_from_user(s, count, base, res);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check kstrtos32_from_user(स्थिर अक्षर __user *s, माप_प्रकार count, अचिन्हित पूर्णांक base, s32 *res)
अणु
	वापस kstrtoपूर्णांक_from_user(s, count, base, res);
पूर्ण

/*
 * Use kstrto<foo> instead.
 *
 * NOTE: simple_strto<foo> करोes not check क्रम the range overflow and,
 *	 depending on the input, may give पूर्णांकeresting results.
 *
 * Use these functions अगर and only अगर you cannot use kstrto<foo>, because
 * the conversion ends on the first non-digit अक्षरacter, which may be far
 * beyond the supported range. It might be useful to parse the strings like
 * 10x50 or 12:21 without altering original string or temporary buffer in use.
 * Keep in mind above caveat.
 */

बाह्य अचिन्हित दीर्घ simple_म_से_अदीर्घ(स्थिर अक्षर *,अक्षर **,अचिन्हित पूर्णांक);
बाह्य दीर्घ simple_म_से_दीर्घ(स्थिर अक्षर *,अक्षर **,अचिन्हित पूर्णांक);
बाह्य अचिन्हित दीर्घ दीर्घ simple_म_से_अदीर्घl(स्थिर अक्षर *,अक्षर **,अचिन्हित पूर्णांक);
बाह्य दीर्घ दीर्घ simple_म_से_दीर्घl(स्थिर अक्षर *,अक्षर **,अचिन्हित पूर्णांक);

बाह्य पूर्णांक num_to_str(अक्षर *buf, पूर्णांक size,
		      अचिन्हित दीर्घ दीर्घ num, अचिन्हित पूर्णांक width);

/* lib/म_लिखो utilities */

बाह्य __म_लिखो(2, 3) पूर्णांक प्र_लिखो(अक्षर *buf, स्थिर अक्षर * fmt, ...);
बाह्य __म_लिखो(2, 0) पूर्णांक भम_लिखो(अक्षर *buf, स्थिर अक्षर *, बहु_सूची);
बाह्य __म_लिखो(3, 4)
पूर्णांक snम_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(3, 0)
पूर्णांक vsnम_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, बहु_सूची args);
बाह्य __म_लिखो(3, 4)
पूर्णांक scnम_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(3, 0)
पूर्णांक vscnम_लिखो(अक्षर *buf, माप_प्रकार size, स्थिर अक्षर *fmt, बहु_सूची args);
बाह्य __म_लिखो(2, 3) __दो_स्मृति
अक्षर *kaप्र_लिखो(gfp_t gfp, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(2, 0) __दो_स्मृति
अक्षर *kvaप्र_लिखो(gfp_t gfp, स्थिर अक्षर *fmt, बहु_सूची args);
बाह्य __म_लिखो(2, 0)
स्थिर अक्षर *kvaप्र_लिखो_स्थिर(gfp_t gfp, स्थिर अक्षर *fmt, बहु_सूची args);

बाह्य __म_पूछो(2, 3)
पूर्णांक माला_पूछो(स्थिर अक्षर *, स्थिर अक्षर *, ...);
बाह्य __म_पूछो(2, 0)
पूर्णांक vमाला_पूछो(स्थिर अक्षर *, स्थिर अक्षर *, बहु_सूची);

बाह्य पूर्णांक get_option(अक्षर **str, पूर्णांक *pपूर्णांक);
बाह्य अक्षर *get_options(स्थिर अक्षर *str, पूर्णांक nपूर्णांकs, पूर्णांक *पूर्णांकs);
बाह्य अचिन्हित दीर्घ दीर्घ memparse(स्थिर अक्षर *ptr, अक्षर **retptr);
बाह्य bool parse_option_str(स्थिर अक्षर *str, स्थिर अक्षर *option);
बाह्य अक्षर *next_arg(अक्षर *args, अक्षर **param, अक्षर **val);

बाह्य पूर्णांक core_kernel_text(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक init_kernel_text(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक core_kernel_data(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक __kernel_text_address(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक kernel_text_address(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक func_ptr_is_kernel_text(व्योम *ptr);

#अगर_घोषित CONFIG_SMP
बाह्य अचिन्हित पूर्णांक sysctl_oops_all_cpu_backtrace;
#अन्यथा
#घोषणा sysctl_oops_all_cpu_backtrace 0
#पूर्ण_अगर /* CONFIG_SMP */

बाह्य व्योम bust_spinlocks(पूर्णांक yes);
बाह्य पूर्णांक panic_समयout;
बाह्य अचिन्हित दीर्घ panic_prपूर्णांक;
बाह्य पूर्णांक panic_on_oops;
बाह्य पूर्णांक panic_on_unrecovered_nmi;
बाह्य पूर्णांक panic_on_io_nmi;
बाह्य पूर्णांक panic_on_warn;
बाह्य अचिन्हित दीर्घ panic_on_taपूर्णांक;
बाह्य bool panic_on_taपूर्णांक_nousertaपूर्णांक;
बाह्य पूर्णांक sysctl_panic_on_rcu_stall;
बाह्य पूर्णांक sysctl_max_rcu_stall_to_panic;
बाह्य पूर्णांक sysctl_panic_on_stackoverflow;

बाह्य bool crash_kexec_post_notअगरiers;

/*
 * panic_cpu is used क्रम synchronizing panic() and crash_kexec() execution. It
 * holds a CPU number which is executing panic() currently. A value of
 * PANIC_CPU_INVALID means no CPU has entered panic() or crash_kexec().
 */
बाह्य atomic_t panic_cpu;
#घोषणा PANIC_CPU_INVALID	-1

/*
 * Only to be used by arch init code. If the user over-wrote the शेष
 * CONFIG_PANIC_TIMEOUT, honor it.
 */
अटल अंतरभूत व्योम set_arch_panic_समयout(पूर्णांक समयout, पूर्णांक arch_शेष_समयout)
अणु
	अगर (panic_समयout == arch_शेष_समयout)
		panic_समयout = समयout;
पूर्ण
बाह्य स्थिर अक्षर *prपूर्णांक_taपूर्णांकed(व्योम);
क्रमागत lockdep_ok अणु
	LOCKDEP_STILL_OK,
	LOCKDEP_NOW_UNRELIABLE
पूर्ण;
बाह्य व्योम add_taपूर्णांक(अचिन्हित flag, क्रमागत lockdep_ok);
बाह्य पूर्णांक test_taपूर्णांक(अचिन्हित flag);
बाह्य अचिन्हित दीर्घ get_taपूर्णांक(व्योम);
बाह्य पूर्णांक root_mountflags;

बाह्य bool early_boot_irqs_disabled;

/*
 * Values used क्रम प्रणाली_state. Ordering of the states must not be changed
 * as code checks क्रम <, <=, >, >= STATE.
 */
बाह्य क्रमागत प्रणाली_states अणु
	SYSTEM_BOOTING,
	SYSTEM_SCHEDULING,
	SYSTEM_RUNNING,
	SYSTEM_HALT,
	SYSTEM_POWER_OFF,
	SYSTEM_RESTART,
	SYSTEM_SUSPEND,
पूर्ण प्रणाली_state;

/* This cannot be an क्रमागत because some may be used in assembly source. */
#घोषणा TAINT_PROPRIETARY_MODULE	0
#घोषणा TAINT_FORCED_MODULE		1
#घोषणा TAINT_CPU_OUT_OF_SPEC		2
#घोषणा TAINT_FORCED_RMMOD		3
#घोषणा TAINT_MACHINE_CHECK		4
#घोषणा TAINT_BAD_PAGE			5
#घोषणा TAINT_USER			6
#घोषणा TAINT_DIE			7
#घोषणा TAINT_OVERRIDDEN_ACPI_TABLE	8
#घोषणा TAINT_WARN			9
#घोषणा TAINT_CRAP			10
#घोषणा TAINT_FIRMWARE_WORKAROUND	11
#घोषणा TAINT_OOT_MODULE		12
#घोषणा TAINT_UNSIGNED_MODULE		13
#घोषणा TAINT_SOFTLOCKUP		14
#घोषणा TAINT_LIVEPATCH			15
#घोषणा TAINT_AUX			16
#घोषणा TAINT_RANDSTRUCT		17
#घोषणा TAINT_FLAGS_COUNT		18
#घोषणा TAINT_FLAGS_MAX			((1UL << TAINT_FLAGS_COUNT) - 1)

काष्ठा taपूर्णांक_flag अणु
	अक्षर c_true;	/* अक्षरacter prपूर्णांकed when taपूर्णांकed */
	अक्षर c_false;	/* अक्षरacter prपूर्णांकed when not taपूर्णांकed */
	bool module;	/* also show as a per-module taपूर्णांक flag */
पूर्ण;

बाह्य स्थिर काष्ठा taपूर्णांक_flag taपूर्णांक_flags[TAINT_FLAGS_COUNT];

बाह्य स्थिर अक्षर hex_asc[];
#घोषणा hex_asc_lo(x)	hex_asc[((x) & 0x0f)]
#घोषणा hex_asc_hi(x)	hex_asc[((x) & 0xf0) >> 4]

अटल अंतरभूत अक्षर *hex_byte_pack(अक्षर *buf, u8 byte)
अणु
	*buf++ = hex_asc_hi(byte);
	*buf++ = hex_asc_lo(byte);
	वापस buf;
पूर्ण

बाह्य स्थिर अक्षर hex_asc_upper[];
#घोषणा hex_asc_upper_lo(x)	hex_asc_upper[((x) & 0x0f)]
#घोषणा hex_asc_upper_hi(x)	hex_asc_upper[((x) & 0xf0) >> 4]

अटल अंतरभूत अक्षर *hex_byte_pack_upper(अक्षर *buf, u8 byte)
अणु
	*buf++ = hex_asc_upper_hi(byte);
	*buf++ = hex_asc_upper_lo(byte);
	वापस buf;
पूर्ण

बाह्य पूर्णांक hex_to_bin(अक्षर ch);
बाह्य पूर्णांक __must_check hex2bin(u8 *dst, स्थिर अक्षर *src, माप_प्रकार count);
बाह्य अक्षर *bin2hex(अक्षर *dst, स्थिर व्योम *src, माप_प्रकार count);

bool mac_pton(स्थिर अक्षर *s, u8 *mac);

/*
 * General tracing related utility functions - trace_prपूर्णांकk(),
 * tracing_on/tracing_off and tracing_start()/tracing_stop
 *
 * Use tracing_on/tracing_off when you want to quickly turn on or off
 * tracing. It simply enables or disables the recording of the trace events.
 * This also corresponds to the user space /sys/kernel/debug/tracing/tracing_on
 * file, which gives a means क्रम the kernel and userspace to पूर्णांकeract.
 * Place a tracing_off() in the kernel where you want tracing to end.
 * From user space, examine the trace, and then echo 1 > tracing_on
 * to जारी tracing.
 *
 * tracing_stop/tracing_start has slightly more overhead. It is used
 * by things like suspend to ram where disabling the recording of the
 * trace is not enough, but tracing must actually stop because things
 * like calling smp_processor_id() may crash the प्रणाली.
 *
 * Most likely, you want to use tracing_on/tracing_off.
 */

क्रमागत ftrace_dump_mode अणु
	DUMP_NONE,
	DUMP_ALL,
	DUMP_ORIG,
पूर्ण;

#अगर_घोषित CONFIG_TRACING
व्योम tracing_on(व्योम);
व्योम tracing_off(व्योम);
पूर्णांक tracing_is_on(व्योम);
व्योम tracing_snapshot(व्योम);
व्योम tracing_snapshot_alloc(व्योम);

बाह्य व्योम tracing_start(व्योम);
बाह्य व्योम tracing_stop(व्योम);

अटल अंतरभूत __म_लिखो(1, 2)
व्योम ____trace_prपूर्णांकk_check_क्रमmat(स्थिर अक्षर *fmt, ...)
अणु
पूर्ण
#घोषणा __trace_prपूर्णांकk_check_क्रमmat(fmt, args...)			\
करो अणु									\
	अगर (0)								\
		____trace_prपूर्णांकk_check_क्रमmat(fmt, ##args);		\
पूर्ण जबतक (0)

/**
 * trace_prपूर्णांकk - म_लिखो क्रमmatting in the ftrace buffer
 * @fmt: the म_लिखो क्रमmat क्रम prपूर्णांकing
 *
 * Note: __trace_prपूर्णांकk is an पूर्णांकernal function क्रम trace_prपूर्णांकk() and
 *       the @ip is passed in via the trace_prपूर्णांकk() macro.
 *
 * This function allows a kernel developer to debug fast path sections
 * that prपूर्णांकk is not appropriate क्रम. By scattering in various
 * prपूर्णांकk like tracing in the code, a developer can quickly see
 * where problems are occurring.
 *
 * This is पूर्णांकended as a debugging tool क्रम the developer only.
 * Please refrain from leaving trace_prपूर्णांकks scattered around in
 * your code. (Extra memory is used क्रम special buffers that are
 * allocated when trace_prपूर्णांकk() is used.)
 *
 * A little optimization trick is करोne here. If there's only one
 * argument, there's no need to scan the string क्रम म_लिखो क्रमmats.
 * The trace_माला_दो() will suffice. But how can we take advantage of
 * using trace_माला_दो() when trace_prपूर्णांकk() has only one argument?
 * By stringअगरying the args and checking the size we can tell
 * whether or not there are args. __stringअगरy((__VA_ARGS__)) will
 * turn पूर्णांकo "()\0" with a size of 3 when there are no args, anything
 * अन्यथा will be bigger. All we need to करो is define a string to this,
 * and then take its size and compare to 3. If it's bigger, use
 * करो_trace_prपूर्णांकk() otherwise, optimize it to trace_माला_दो(). Then just
 * let gcc optimize the rest.
 */

#घोषणा trace_prपूर्णांकk(fmt, ...)				\
करो अणु							\
	अक्षर _______STR[] = __stringअगरy((__VA_ARGS__));	\
	अगर (माप(_______STR) > 3)			\
		करो_trace_prपूर्णांकk(fmt, ##__VA_ARGS__);	\
	अन्यथा						\
		trace_माला_दो(fmt);			\
पूर्ण जबतक (0)

#घोषणा करो_trace_prपूर्णांकk(fmt, args...)					\
करो अणु									\
	अटल स्थिर अक्षर *trace_prपूर्णांकk_fmt __used			\
		__section("__trace_printk_fmt") =			\
		__builtin_स्थिरant_p(fmt) ? fmt : शून्य;			\
									\
	__trace_prपूर्णांकk_check_क्रमmat(fmt, ##args);			\
									\
	अगर (__builtin_स्थिरant_p(fmt))					\
		__trace_bprपूर्णांकk(_THIS_IP_, trace_prपूर्णांकk_fmt, ##args);	\
	अन्यथा								\
		__trace_prपूर्णांकk(_THIS_IP_, fmt, ##args);			\
पूर्ण जबतक (0)

बाह्य __म_लिखो(2, 3)
पूर्णांक __trace_bprपूर्णांकk(अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, ...);

बाह्य __म_लिखो(2, 3)
पूर्णांक __trace_prपूर्णांकk(अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, ...);

/**
 * trace_माला_दो - ग_लिखो a string पूर्णांकo the ftrace buffer
 * @str: the string to record
 *
 * Note: __trace_bमाला_दो is an पूर्णांकernal function क्रम trace_माला_दो and
 *       the @ip is passed in via the trace_माला_दो macro.
 *
 * This is similar to trace_prपूर्णांकk() but is made क्रम those really fast
 * paths that a developer wants the least amount of "Heisenbug" effects,
 * where the processing of the prपूर्णांक क्रमmat is still too much.
 *
 * This function allows a kernel developer to debug fast path sections
 * that prपूर्णांकk is not appropriate क्रम. By scattering in various
 * prपूर्णांकk like tracing in the code, a developer can quickly see
 * where problems are occurring.
 *
 * This is पूर्णांकended as a debugging tool क्रम the developer only.
 * Please refrain from leaving trace_माला_दो scattered around in
 * your code. (Extra memory is used क्रम special buffers that are
 * allocated when trace_माला_दो() is used.)
 *
 * Returns: 0 अगर nothing was written, positive # अगर string was.
 *  (1 when __trace_bमाला_दो is used, म_माप(str) when __trace_माला_दो is used)
 */

#घोषणा trace_माला_दो(str) (अणु						\
	अटल स्थिर अक्षर *trace_prपूर्णांकk_fmt __used			\
		__section("__trace_printk_fmt") =			\
		__builtin_स्थिरant_p(str) ? str : शून्य;			\
									\
	अगर (__builtin_स्थिरant_p(str))					\
		__trace_bमाला_दो(_THIS_IP_, trace_prपूर्णांकk_fmt);		\
	अन्यथा								\
		__trace_माला_दो(_THIS_IP_, str, म_माप(str));		\
पूर्ण)
बाह्य पूर्णांक __trace_bमाला_दो(अचिन्हित दीर्घ ip, स्थिर अक्षर *str);
बाह्य पूर्णांक __trace_माला_दो(अचिन्हित दीर्घ ip, स्थिर अक्षर *str, पूर्णांक size);

बाह्य व्योम trace_dump_stack(पूर्णांक skip);

/*
 * The द्विगुन __builtin_स्थिरant_p is because gcc will give us an error
 * अगर we try to allocate the अटल variable to fmt अगर it is not a
 * स्थिरant. Even with the outer अगर statement.
 */
#घोषणा ftrace_vprपूर्णांकk(fmt, vargs)					\
करो अणु									\
	अगर (__builtin_स्थिरant_p(fmt)) अणु				\
		अटल स्थिर अक्षर *trace_prपूर्णांकk_fmt __used		\
		  __section("__trace_printk_fmt") =			\
			__builtin_स्थिरant_p(fmt) ? fmt : शून्य;		\
									\
		__ftrace_vbprपूर्णांकk(_THIS_IP_, trace_prपूर्णांकk_fmt, vargs);	\
	पूर्ण अन्यथा								\
		__ftrace_vprपूर्णांकk(_THIS_IP_, fmt, vargs);		\
पूर्ण जबतक (0)

बाह्य __म_लिखो(2, 0) पूर्णांक
__ftrace_vbprपूर्णांकk(अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, बहु_सूची ap);

बाह्य __म_लिखो(2, 0) पूर्णांक
__ftrace_vprपूर्णांकk(अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, बहु_सूची ap);

बाह्य व्योम ftrace_dump(क्रमागत ftrace_dump_mode oops_dump_mode);
#अन्यथा
अटल अंतरभूत व्योम tracing_start(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tracing_stop(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम trace_dump_stack(पूर्णांक skip) अणु पूर्ण

अटल अंतरभूत व्योम tracing_on(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tracing_off(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक tracing_is_on(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम tracing_snapshot(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tracing_snapshot_alloc(व्योम) अणु पूर्ण

अटल अंतरभूत __म_लिखो(1, 2)
पूर्णांक trace_prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	वापस 0;
पूर्ण
अटल __म_लिखो(1, 0) अंतरभूत पूर्णांक
ftrace_vprपूर्णांकk(स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ftrace_dump(क्रमागत ftrace_dump_mode oops_dump_mode) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_TRACING */

/* This counts to 12. Any more, it will वापस 13th argument. */
#घोषणा __COUNT_ARGS(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _n, X...) _n
#घोषणा COUNT_ARGS(X...) __COUNT_ARGS(, ##X, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#घोषणा __CONCAT(a, b) a ## b
#घोषणा CONCATENATE(a, b) __CONCAT(a, b)

/**
 * container_of - cast a member of a काष्ठाure out to the containing काष्ठाure
 * @ptr:	the poपूर्णांकer to the member.
 * @type:	the type of the container काष्ठा this is embedded in.
 * @member:	the name of the member within the काष्ठा.
 *
 */
#घोषणा container_of(ptr, type, member) (अणु				\
	व्योम *__mptr = (व्योम *)(ptr);					\
	BUILD_BUG_ON_MSG(!__same_type(*(ptr), ((type *)0)->member) &&	\
			 !__same_type(*(ptr), व्योम),			\
			 "pointer type mismatch in container_of()");	\
	((type *)(__mptr - दुरत्व(type, member))); पूर्ण)

/**
 * container_of_safe - cast a member of a काष्ठाure out to the containing काष्ठाure
 * @ptr:	the poपूर्णांकer to the member.
 * @type:	the type of the container काष्ठा this is embedded in.
 * @member:	the name of the member within the काष्ठा.
 *
 * If IS_ERR_OR_शून्य(ptr), ptr is वापसed unchanged.
 */
#घोषणा container_of_safe(ptr, type, member) (अणु				\
	व्योम *__mptr = (व्योम *)(ptr);					\
	BUILD_BUG_ON_MSG(!__same_type(*(ptr), ((type *)0)->member) &&	\
			 !__same_type(*(ptr), व्योम),			\
			 "pointer type mismatch in container_of()");	\
	IS_ERR_OR_शून्य(__mptr) ? ERR_CAST(__mptr) :			\
		((type *)(__mptr - दुरत्व(type, member))); पूर्ण)

/* Rebuild everything on CONFIG_FTRACE_MCOUNT_RECORD */
#अगर_घोषित CONFIG_FTRACE_MCOUNT_RECORD
# define REBUILD_DUE_TO_FTRACE_MCOUNT_RECORD
#पूर्ण_अगर

/* Permissions on a sysfs file: you didn't miss the 0 prefix did you? */
#घोषणा VERIFY_OCTAL_PERMISSIONS(perms)						\
	(BUILD_BUG_ON_ZERO((perms) < 0) +					\
	 BUILD_BUG_ON_ZERO((perms) > 0777) +					\
	 /* USER_READABLE >= GROUP_READABLE >= OTHER_READABLE */		\
	 BUILD_BUG_ON_ZERO((((perms) >> 6) & 4) < (((perms) >> 3) & 4)) +	\
	 BUILD_BUG_ON_ZERO((((perms) >> 3) & 4) < ((perms) & 4)) +		\
	 /* USER_WRITABLE >= GROUP_WRITABLE */					\
	 BUILD_BUG_ON_ZERO((((perms) >> 6) & 2) < (((perms) >> 3) & 2)) +	\
	 /* OTHER_WRITABLE?  Generally considered a bad idea. */		\
	 BUILD_BUG_ON_ZERO((perms) & 2) +					\
	 (perms))
#पूर्ण_अगर
