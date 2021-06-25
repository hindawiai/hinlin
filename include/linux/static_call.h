<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_STATIC_CALL_H
#घोषणा _LINUX_STATIC_CALL_H

/*
 * Static call support
 *
 * Static calls use code patching to hard-code function poपूर्णांकers पूर्णांकo direct
 * branch inकाष्ठाions. They give the flexibility of function poपूर्णांकers, but
 * with improved perक्रमmance. This is especially important क्रम हालs where
 * retpolines would otherwise be used, as retpolines can signअगरicantly impact
 * perक्रमmance.
 *
 *
 * API overview:
 *
 *   DECLARE_STATIC_CALL(name, func);
 *   DEFINE_STATIC_CALL(name, func);
 *   DEFINE_STATIC_CALL_शून्य(name, typename);
 *   अटल_call(name)(args...);
 *   अटल_call_cond(name)(args...);
 *   अटल_call_update(name, func);
 *   अटल_call_query(name);
 *
 * Usage example:
 *
 *   # Start with the following functions (with identical prototypes):
 *   पूर्णांक func_a(पूर्णांक arg1, पूर्णांक arg2);
 *   पूर्णांक func_b(पूर्णांक arg1, पूर्णांक arg2);
 *
 *   # Define a 'my_name' reference, associated with func_a() by शेष
 *   DEFINE_STATIC_CALL(my_name, func_a);
 *
 *   # Call func_a()
 *   अटल_call(my_name)(arg1, arg2);
 *
 *   # Update 'my_name' to poपूर्णांक to func_b()
 *   अटल_call_update(my_name, &func_b);
 *
 *   # Call func_b()
 *   अटल_call(my_name)(arg1, arg2);
 *
 *
 * Implementation details:
 *
 *   This requires some arch-specअगरic code (CONFIG_HAVE_STATIC_CALL).
 *   Otherwise basic indirect calls are used (with function poपूर्णांकers).
 *
 *   Each अटल_call() site calls पूर्णांकo a trampoline associated with the name.
 *   The trampoline has a direct branch to the शेष function.  Updates to a
 *   name will modअगरy the trampoline's branch destination.
 *
 *   If the arch has CONFIG_HAVE_STATIC_CALL_INLINE, then the call sites
 *   themselves will be patched at runसमय to call the functions directly,
 *   rather than calling through the trampoline.  This requires objtool or a
 *   compiler plugin to detect all the अटल_call() sites and annotate them
 *   in the .अटल_call_sites section.
 *
 *
 * Notes on शून्य function poपूर्णांकers:
 *
 *   Static_call()s support शून्य functions, with many of the caveats that
 *   regular function poपूर्णांकers have.
 *
 *   Clearly calling a शून्य function poपूर्णांकer is 'BAD', so too क्रम
 *   अटल_call()s (although when HAVE_STATIC_CALL it might not be immediately
 *   fatal). A शून्य अटल_call can be the result of:
 *
 *     DECLARE_STATIC_CALL_शून्य(my_अटल_call, व्योम (*)(पूर्णांक));
 *
 *   which is equivalent to declaring a शून्य function poपूर्णांकer with just a
 *   typename:
 *
 *     व्योम (*my_func_ptr)(पूर्णांक arg1) = शून्य;
 *
 *   or using अटल_call_update() with a शून्य function. In both हालs the
 *   HAVE_STATIC_CALL implementation will patch the trampoline with a RET
 *   inकाष्ठाion, instead of an immediate tail-call JMP. HAVE_STATIC_CALL_INLINE
 *   architectures can patch the trampoline call to a NOP.
 *
 *   In all हालs, any argument evaluation is unconditional. Unlike a regular
 *   conditional function poपूर्णांकer call:
 *
 *     अगर (my_func_ptr)
 *         my_func_ptr(arg1)
 *
 *   where the argument evaludation also depends on the poपूर्णांकer value.
 *
 *   When calling a अटल_call that can be शून्य, use:
 *
 *     अटल_call_cond(name)(arg1);
 *
 *   which will include the required value tests to aव्योम शून्य-poपूर्णांकer
 *   dereferences.
 *
 *   To query which function is currently set to be called, use:
 *
 *   func = अटल_call_query(name);
 */

#समावेश <linux/types.h>
#समावेश <linux/cpu.h>
#समावेश <linux/अटल_call_types.h>

#अगर_घोषित CONFIG_HAVE_STATIC_CALL
#समावेश <यंत्र/अटल_call.h>

/*
 * Either @site or @tramp can be शून्य.
 */
बाह्य व्योम arch_अटल_call_transक्रमm(व्योम *site, व्योम *tramp, व्योम *func, bool tail);

#घोषणा STATIC_CALL_TRAMP_ADDR(name) &STATIC_CALL_TRAMP(name)

#अन्यथा
#घोषणा STATIC_CALL_TRAMP_ADDR(name) शून्य
#पूर्ण_अगर

#घोषणा अटल_call_update(name, func)					\
(अणु									\
	typeof(&STATIC_CALL_TRAMP(name)) __F = (func);			\
	__अटल_call_update(&STATIC_CALL_KEY(name),			\
			     STATIC_CALL_TRAMP_ADDR(name), __F);	\
पूर्ण)

#घोषणा अटल_call_query(name) (READ_ONCE(STATIC_CALL_KEY(name).func))

#अगर_घोषित CONFIG_HAVE_STATIC_CALL_INLINE

बाह्य पूर्णांक __init अटल_call_init(व्योम);

काष्ठा अटल_call_mod अणु
	काष्ठा अटल_call_mod *next;
	काष्ठा module *mod; /* क्रम vmlinux, mod == शून्य */
	काष्ठा अटल_call_site *sites;
पूर्ण;

/* For finding the key associated with a trampoline */
काष्ठा अटल_call_tramp_key अणु
	s32 tramp;
	s32 key;
पूर्ण;

बाह्य व्योम __अटल_call_update(काष्ठा अटल_call_key *key, व्योम *tramp, व्योम *func);
बाह्य पूर्णांक अटल_call_mod_init(काष्ठा module *mod);
बाह्य पूर्णांक अटल_call_text_reserved(व्योम *start, व्योम *end);

बाह्य दीर्घ __अटल_call_वापस0(व्योम);

#घोषणा __DEFINE_STATIC_CALL(name, _func, _func_init)			\
	DECLARE_STATIC_CALL(name, _func);				\
	काष्ठा अटल_call_key STATIC_CALL_KEY(name) = अणु		\
		.func = _func_init,					\
		.type = 1,						\
	पूर्ण;								\
	ARCH_DEFINE_STATIC_CALL_TRAMP(name, _func_init)

#घोषणा DEFINE_STATIC_CALL_शून्य(name, _func)				\
	DECLARE_STATIC_CALL(name, _func);				\
	काष्ठा अटल_call_key STATIC_CALL_KEY(name) = अणु		\
		.func = शून्य,						\
		.type = 1,						\
	पूर्ण;								\
	ARCH_DEFINE_STATIC_CALL_शून्य_TRAMP(name)

#घोषणा अटल_call_cond(name)	(व्योम)__अटल_call(name)

#घोषणा EXPORT_STATIC_CALL(name)					\
	EXPORT_SYMBOL(STATIC_CALL_KEY(name));				\
	EXPORT_SYMBOL(STATIC_CALL_TRAMP(name))
#घोषणा EXPORT_STATIC_CALL_GPL(name)					\
	EXPORT_SYMBOL_GPL(STATIC_CALL_KEY(name));			\
	EXPORT_SYMBOL_GPL(STATIC_CALL_TRAMP(name))

/* Leave the key unexported, so modules can't change अटल call tarमाला_लो: */
#घोषणा EXPORT_STATIC_CALL_TRAMP(name)					\
	EXPORT_SYMBOL(STATIC_CALL_TRAMP(name));				\
	ARCH_ADD_TRAMP_KEY(name)
#घोषणा EXPORT_STATIC_CALL_TRAMP_GPL(name)				\
	EXPORT_SYMBOL_GPL(STATIC_CALL_TRAMP(name));			\
	ARCH_ADD_TRAMP_KEY(name)

#या_अगर defined(CONFIG_HAVE_STATIC_CALL)

अटल अंतरभूत पूर्णांक अटल_call_init(व्योम) अणु वापस 0; पूर्ण

#घोषणा __DEFINE_STATIC_CALL(name, _func, _func_init)			\
	DECLARE_STATIC_CALL(name, _func);				\
	काष्ठा अटल_call_key STATIC_CALL_KEY(name) = अणु		\
		.func = _func_init,					\
	पूर्ण;								\
	ARCH_DEFINE_STATIC_CALL_TRAMP(name, _func_init)

#घोषणा DEFINE_STATIC_CALL_शून्य(name, _func)				\
	DECLARE_STATIC_CALL(name, _func);				\
	काष्ठा अटल_call_key STATIC_CALL_KEY(name) = अणु		\
		.func = शून्य,						\
	पूर्ण;								\
	ARCH_DEFINE_STATIC_CALL_शून्य_TRAMP(name)


#घोषणा अटल_call_cond(name)	(व्योम)__अटल_call(name)

अटल अंतरभूत
व्योम __अटल_call_update(काष्ठा अटल_call_key *key, व्योम *tramp, व्योम *func)
अणु
	cpus_पढ़ो_lock();
	WRITE_ONCE(key->func, func);
	arch_अटल_call_transक्रमm(शून्य, tramp, func, false);
	cpus_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत पूर्णांक अटल_call_text_reserved(व्योम *start, व्योम *end)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत दीर्घ __अटल_call_वापस0(व्योम)
अणु
	वापस 0;
पूर्ण

#घोषणा EXPORT_STATIC_CALL(name)					\
	EXPORT_SYMBOL(STATIC_CALL_KEY(name));				\
	EXPORT_SYMBOL(STATIC_CALL_TRAMP(name))
#घोषणा EXPORT_STATIC_CALL_GPL(name)					\
	EXPORT_SYMBOL_GPL(STATIC_CALL_KEY(name));			\
	EXPORT_SYMBOL_GPL(STATIC_CALL_TRAMP(name))

/* Leave the key unexported, so modules can't change अटल call tarमाला_लो: */
#घोषणा EXPORT_STATIC_CALL_TRAMP(name)					\
	EXPORT_SYMBOL(STATIC_CALL_TRAMP(name))
#घोषणा EXPORT_STATIC_CALL_TRAMP_GPL(name)				\
	EXPORT_SYMBOL_GPL(STATIC_CALL_TRAMP(name))

#अन्यथा /* Generic implementation */

अटल अंतरभूत पूर्णांक अटल_call_init(व्योम) अणु वापस 0; पूर्ण

अटल अंतरभूत दीर्घ __अटल_call_वापस0(व्योम)
अणु
	वापस 0;
पूर्ण

#घोषणा __DEFINE_STATIC_CALL(name, _func, _func_init)			\
	DECLARE_STATIC_CALL(name, _func);				\
	काष्ठा अटल_call_key STATIC_CALL_KEY(name) = अणु		\
		.func = _func_init,					\
	पूर्ण

#घोषणा DEFINE_STATIC_CALL_शून्य(name, _func)				\
	DECLARE_STATIC_CALL(name, _func);				\
	काष्ठा अटल_call_key STATIC_CALL_KEY(name) = अणु		\
		.func = शून्य,						\
	पूर्ण

अटल अंतरभूत व्योम __अटल_call_nop(व्योम) अणु पूर्ण

/*
 * This horrअगरic hack takes care of two things:
 *
 *  - it ensures the compiler will only load the function poपूर्णांकer ONCE,
 *    which aव्योमs a reload race.
 *
 *  - it ensures the argument evaluation is unconditional, similar
 *    to the HAVE_STATIC_CALL variant.
 *
 * Sadly current GCC/Clang (10 क्रम both) करो not optimize this properly
 * and will emit an indirect call क्रम the शून्य हाल :-(
 */
#घोषणा __अटल_call_cond(name)					\
(अणु									\
	व्योम *func = READ_ONCE(STATIC_CALL_KEY(name).func);		\
	अगर (!func)							\
		func = &__अटल_call_nop;				\
	(typeof(STATIC_CALL_TRAMP(name))*)func;				\
पूर्ण)

#घोषणा अटल_call_cond(name)	(व्योम)__अटल_call_cond(name)

अटल अंतरभूत
व्योम __अटल_call_update(काष्ठा अटल_call_key *key, व्योम *tramp, व्योम *func)
अणु
	WRITE_ONCE(key->func, func);
पूर्ण

अटल अंतरभूत पूर्णांक अटल_call_text_reserved(व्योम *start, व्योम *end)
अणु
	वापस 0;
पूर्ण

#घोषणा EXPORT_STATIC_CALL(name)	EXPORT_SYMBOL(STATIC_CALL_KEY(name))
#घोषणा EXPORT_STATIC_CALL_GPL(name)	EXPORT_SYMBOL_GPL(STATIC_CALL_KEY(name))

#पूर्ण_अगर /* CONFIG_HAVE_STATIC_CALL */

#घोषणा DEFINE_STATIC_CALL(name, _func)					\
	__DEFINE_STATIC_CALL(name, _func, _func)

#घोषणा DEFINE_STATIC_CALL_RET0(name, _func)				\
	__DEFINE_STATIC_CALL(name, _func, __अटल_call_वापस0)

#पूर्ण_अगर /* _LINUX_STATIC_CALL_H */
