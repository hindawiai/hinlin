<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BUG_H
#घोषणा _ASM_GENERIC_BUG_H

#समावेश <linux/compiler.h>
#समावेश <linux/instrumentation.h>

#घोषणा CUT_HERE		"------------[ cut here ]------------\n"

#अगर_घोषित CONFIG_GENERIC_BUG
#घोषणा BUGFLAG_WARNING		(1 << 0)
#घोषणा BUGFLAG_ONCE		(1 << 1)
#घोषणा BUGFLAG_DONE		(1 << 2)
#घोषणा BUGFLAG_NO_CUT_HERE	(1 << 3)	/* CUT_HERE alपढ़ोy sent */
#घोषणा BUGFLAG_TAINT(taपूर्णांक)	((taपूर्णांक) << 8)
#घोषणा BUG_GET_TAINT(bug)	((bug)->flags >> 8)
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/kernel.h>

#अगर_घोषित CONFIG_BUG

#अगर_घोषित CONFIG_GENERIC_BUG
काष्ठा bug_entry अणु
#अगर_अघोषित CONFIG_GENERIC_BUG_RELATIVE_POINTERS
	अचिन्हित दीर्घ	bug_addr;
#अन्यथा
	चिन्हित पूर्णांक	bug_addr_disp;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_BUGVERBOSE
#अगर_अघोषित CONFIG_GENERIC_BUG_RELATIVE_POINTERS
	स्थिर अक्षर	*file;
#अन्यथा
	चिन्हित पूर्णांक	file_disp;
#पूर्ण_अगर
	अचिन्हित लघु	line;
#पूर्ण_अगर
	अचिन्हित लघु	flags;
पूर्ण;
#पूर्ण_अगर	/* CONFIG_GENERIC_BUG */

/*
 * Don't use BUG() or BUG_ON() unless there's really no way out; one
 * example might be detecting data काष्ठाure corruption in the middle
 * of an operation that can't be backed out of.  If the (sub)प्रणाली
 * can somehow जारी operating, perhaps with reduced functionality,
 * it's probably not BUG-worthy.
 *
 * If you're tempted to BUG(), think again:  is completely giving up
 * really the *only* solution?  There are usually better options, where
 * users करोn't need to reboot ASAP and can mostly shut करोwn cleanly.
 */
#अगर_अघोषित HAVE_ARCH_BUG
#घोषणा BUG() करो अणु \
	prपूर्णांकk("BUG: failure at %s:%d/%s()!\n", __खाता__, __LINE__, __func__); \
	barrier_beक्रमe_unreachable(); \
	panic("BUG!"); \
पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित HAVE_ARCH_BUG_ON
#घोषणा BUG_ON(condition) करो अणु अगर (unlikely(condition)) BUG(); पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * WARN(), WARN_ON(), WARN_ON_ONCE, and so on can be used to report
 * signअगरicant kernel issues that need prompt attention अगर they should ever
 * appear at runसमय.
 *
 * Do not use these macros when checking क्रम invalid बाह्यal inमाला_दो
 * (e.g. invalid प्रणाली call arguments, or invalid data coming from
 * network/devices), and on transient conditions like ENOMEM or EAGAIN.
 * These macros should be used क्रम recoverable kernel issues only.
 * For invalid बाह्यal inमाला_दो, transient conditions, etc use
 * pr_err[_once/_ratelimited]() followed by dump_stack(), अगर necessary.
 * Do not include "BUG"/"WARNING" in क्रमmat strings manually to make these
 * conditions distinguishable from kernel issues.
 *
 * Use the versions with prपूर्णांकk क्रमmat strings to provide better diagnostics.
 */
#अगर_अघोषित __WARN_FLAGS
बाह्य __म_लिखो(4, 5)
व्योम warn_slowpath_fmt(स्थिर अक्षर *file, स्थिर पूर्णांक line, अचिन्हित taपूर्णांक,
		       स्थिर अक्षर *fmt, ...);
#घोषणा __WARN()		__WARN_म_लिखो(TAINT_WARN, शून्य)
#घोषणा __WARN_म_लिखो(taपूर्णांक, arg...) करो अणु				\
		instrumentation_begin();				\
		warn_slowpath_fmt(__खाता__, __LINE__, taपूर्णांक, arg);	\
		instrumentation_end();					\
	पूर्ण जबतक (0)
#अन्यथा
बाह्य __म_लिखो(1, 2) व्योम __warn_prपूर्णांकk(स्थिर अक्षर *fmt, ...);
#घोषणा __WARN()		__WARN_FLAGS(BUGFLAG_TAINT(TAINT_WARN))
#घोषणा __WARN_म_लिखो(taपूर्णांक, arg...) करो अणु				\
		instrumentation_begin();				\
		__warn_prपूर्णांकk(arg);					\
		__WARN_FLAGS(BUGFLAG_NO_CUT_HERE | BUGFLAG_TAINT(taपूर्णांक));\
		instrumentation_end();					\
	पूर्ण जबतक (0)
#घोषणा WARN_ON_ONCE(condition) (अणु				\
	पूर्णांक __ret_warn_on = !!(condition);			\
	अगर (unlikely(__ret_warn_on))				\
		__WARN_FLAGS(BUGFLAG_ONCE |			\
			     BUGFLAG_TAINT(TAINT_WARN));	\
	unlikely(__ret_warn_on);				\
पूर्ण)
#पूर्ण_अगर

/* used पूर्णांकernally by panic.c */
काष्ठा warn_args;
काष्ठा pt_regs;

व्योम __warn(स्थिर अक्षर *file, पूर्णांक line, व्योम *caller, अचिन्हित taपूर्णांक,
	    काष्ठा pt_regs *regs, काष्ठा warn_args *args);

#अगर_अघोषित WARN_ON
#घोषणा WARN_ON(condition) (अणु						\
	पूर्णांक __ret_warn_on = !!(condition);				\
	अगर (unlikely(__ret_warn_on))					\
		__WARN();						\
	unlikely(__ret_warn_on);					\
पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित WARN
#घोषणा WARN(condition, क्रमmat...) (अणु					\
	पूर्णांक __ret_warn_on = !!(condition);				\
	अगर (unlikely(__ret_warn_on))					\
		__WARN_म_लिखो(TAINT_WARN, क्रमmat);			\
	unlikely(__ret_warn_on);					\
पूर्ण)
#पूर्ण_अगर

#घोषणा WARN_TAINT(condition, taपूर्णांक, क्रमmat...) (अणु			\
	पूर्णांक __ret_warn_on = !!(condition);				\
	अगर (unlikely(__ret_warn_on))					\
		__WARN_म_लिखो(taपूर्णांक, क्रमmat);				\
	unlikely(__ret_warn_on);					\
पूर्ण)

#अगर_अघोषित WARN_ON_ONCE
#घोषणा WARN_ON_ONCE(condition)	(अणु				\
	अटल bool __section(".data.once") __warned;		\
	पूर्णांक __ret_warn_once = !!(condition);			\
								\
	अगर (unlikely(__ret_warn_once && !__warned)) अणु		\
		__warned = true;				\
		WARN_ON(1);					\
	पूर्ण							\
	unlikely(__ret_warn_once);				\
पूर्ण)
#पूर्ण_अगर

#घोषणा WARN_ONCE(condition, क्रमmat...)	(अणु			\
	अटल bool __section(".data.once") __warned;		\
	पूर्णांक __ret_warn_once = !!(condition);			\
								\
	अगर (unlikely(__ret_warn_once && !__warned)) अणु		\
		__warned = true;				\
		WARN(1, क्रमmat);				\
	पूर्ण							\
	unlikely(__ret_warn_once);				\
पूर्ण)

#घोषणा WARN_TAINT_ONCE(condition, taपूर्णांक, क्रमmat...)	(अणु	\
	अटल bool __section(".data.once") __warned;		\
	पूर्णांक __ret_warn_once = !!(condition);			\
								\
	अगर (unlikely(__ret_warn_once && !__warned)) अणु		\
		__warned = true;				\
		WARN_TAINT(1, taपूर्णांक, क्रमmat);			\
	पूर्ण							\
	unlikely(__ret_warn_once);				\
पूर्ण)

#अन्यथा /* !CONFIG_BUG */
#अगर_अघोषित HAVE_ARCH_BUG
#घोषणा BUG() करो अणुपूर्ण जबतक (1)
#पूर्ण_अगर

#अगर_अघोषित HAVE_ARCH_BUG_ON
#घोषणा BUG_ON(condition) करो अणु अगर (unlikely(condition)) BUG(); पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित HAVE_ARCH_WARN_ON
#घोषणा WARN_ON(condition) (अणु						\
	पूर्णांक __ret_warn_on = !!(condition);				\
	unlikely(__ret_warn_on);					\
पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित WARN
#घोषणा WARN(condition, क्रमmat...) (अणु					\
	पूर्णांक __ret_warn_on = !!(condition);				\
	no_prपूर्णांकk(क्रमmat);						\
	unlikely(__ret_warn_on);					\
पूर्ण)
#पूर्ण_अगर

#घोषणा WARN_ON_ONCE(condition) WARN_ON(condition)
#घोषणा WARN_ONCE(condition, क्रमmat...) WARN(condition, क्रमmat)
#घोषणा WARN_TAINT(condition, taपूर्णांक, क्रमmat...) WARN(condition, क्रमmat)
#घोषणा WARN_TAINT_ONCE(condition, taपूर्णांक, क्रमmat...) WARN(condition, क्रमmat)

#पूर्ण_अगर

/*
 * WARN_ON_SMP() is क्रम हालs that the warning is either
 * meaningless क्रम !SMP or may even cause failures.
 * It can also be used with values that are only defined
 * on SMP:
 *
 * काष्ठा foo अणु
 *  [...]
 * #अगर_घोषित CONFIG_SMP
 *	पूर्णांक bar;
 * #पूर्ण_अगर
 * पूर्ण;
 *
 * व्योम func(काष्ठा foo *zoot)
 * अणु
 *	WARN_ON_SMP(!zoot->bar);
 *
 * For CONFIG_SMP, WARN_ON_SMP() should act the same as WARN_ON(),
 * and should be a nop and वापस false क्रम uniprocessor.
 *
 * अगर (WARN_ON_SMP(x)) वापसs true only when CONFIG_SMP is set
 * and x is true.
 */
#अगर_घोषित CONFIG_SMP
# define WARN_ON_SMP(x)			WARN_ON(x)
#अन्यथा
/*
 * Use of (अणु0;पूर्ण) because WARN_ON_SMP(x) may be used either as
 * a stand alone line statement or as a condition in an अगर ()
 * statement.
 * A simple "0" would cause gcc to give a "statement has no effect"
 * warning.
 */
# define WARN_ON_SMP(x)			(अणु0;पूर्ण)
#पूर्ण_अगर

/*
 * WARN_ON_FUNCTION_MISMATCH() warns अगर a value करोesn't match a
 * function address, and can be useful क्रम catching issues with
 * callback functions, क्रम example.
 *
 * With CONFIG_CFI_CLANG, the warning is disabled because the
 * compiler replaces function addresses taken in C code with
 * local jump table addresses, which अवरोधs cross-module function
 * address equality.
 */
#अगर defined(CONFIG_CFI_CLANG) && defined(CONFIG_MODULES)
# define WARN_ON_FUNCTION_MISMATCH(x, fn) (अणु 0; पूर्ण)
#अन्यथा
# define WARN_ON_FUNCTION_MISMATCH(x, fn) WARN_ON_ONCE((x) != (fn))
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
