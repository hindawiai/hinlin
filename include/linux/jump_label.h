<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_JUMP_LABEL_H
#घोषणा _LINUX_JUMP_LABEL_H

/*
 * Jump label support
 *
 * Copyright (C) 2009-2012 Jason Baron <jbaron@redhat.com>
 * Copyright (C) 2011-2012 Red Hat, Inc., Peter Zijlstra
 *
 * DEPRECATED API:
 *
 * The use of 'struct static_key' directly, is now DEPRECATED. In addition
 * अटल_key_अणुtrue,falseपूर्ण() is also DEPRECATED. IE DO NOT use the following:
 *
 * काष्ठा अटल_key false = STATIC_KEY_INIT_FALSE;
 * काष्ठा अटल_key true = STATIC_KEY_INIT_TRUE;
 * अटल_key_true()
 * अटल_key_false()
 *
 * The updated API replacements are:
 *
 * DEFINE_STATIC_KEY_TRUE(key);
 * DEFINE_STATIC_KEY_FALSE(key);
 * DEFINE_STATIC_KEY_ARRAY_TRUE(keys, count);
 * DEFINE_STATIC_KEY_ARRAY_FALSE(keys, count);
 * अटल_branch_likely()
 * अटल_branch_unlikely()
 *
 * Jump labels provide an पूर्णांकerface to generate dynamic branches using
 * self-modअगरying code. Assuming toolchain and architecture support, अगर we
 * define a "key" that is initially false via "DEFINE_STATIC_KEY_FALSE(key)",
 * an "if (static_branch_unlikely(&key))" statement is an unconditional branch
 * (which शेषs to false - and the true block is placed out of line).
 * Similarly, we can define an initially true key via
 * "DEFINE_STATIC_KEY_TRUE(key)", and use it in the same
 * "if (static_branch_unlikely(&key))", in which हाल we will generate an
 * unconditional branch to the out-of-line true branch. Keys that are
 * initially true or false can be using in both अटल_branch_unlikely()
 * and अटल_branch_likely() statements.
 *
 * At runसमय we can change the branch target by setting the key
 * to true via a call to अटल_branch_enable(), or false using
 * अटल_branch_disable(). If the direction of the branch is चयनed by
 * these calls then we run-समय modअगरy the branch target via a
 * no-op -> jump or jump -> no-op conversion. For example, क्रम an
 * initially false key that is used in an "if (static_branch_unlikely(&key))"
 * statement, setting the key to true requires us to patch in a jump
 * to the out-of-line of true branch.
 *
 * In addition to अटल_branch_अणुenable,disableपूर्ण, we can also reference count
 * the key or branch direction via अटल_branch_अणुinc,decपूर्ण. Thus,
 * अटल_branch_inc() can be thought of as a 'make more true' and
 * अटल_branch_dec() as a 'make more false'.
 *
 * Since this relies on modअगरying code, the branch modअगरying functions
 * must be considered असलolute slow paths (machine wide synchronization etc.).
 * OTOH, since the affected branches are unconditional, their runसमय overhead
 * will be असलolutely minimal, esp. in the शेष (off) हाल where the total
 * effect is a single NOP of appropriate size. The on हाल will patch in a jump
 * to the out-of-line block.
 *
 * When the control is directly exposed to userspace, it is prudent to delay the
 * decrement to aव्योम high frequency code modअगरications which can (and करो)
 * cause signअगरicant perक्रमmance degradation. Struct अटल_key_deferred and
 * अटल_key_slow_dec_deferred() provide क्रम this.
 *
 * Lacking toolchain and or architecture support, अटल keys fall back to a
 * simple conditional branch.
 *
 * Additional babbling in: Documentation/staging/अटल-keys.rst
 */

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

बाह्य bool अटल_key_initialized;

#घोषणा STATIC_KEY_CHECK_USE(key) WARN(!अटल_key_initialized,		      \
				    "%s(): static key '%pS' used before call to jump_label_init()", \
				    __func__, (key))

#अगर_घोषित CONFIG_JUMP_LABEL

काष्ठा अटल_key अणु
	atomic_t enabled;
/*
 * Note:
 *   To make anonymous जोड़s work with old compilers, the अटल
 *   initialization of them requires brackets. This creates a dependency
 *   on the order of the काष्ठा with the initializers. If any fields
 *   are added, STATIC_KEY_INIT_TRUE and STATIC_KEY_INIT_FALSE may need
 *   to be modअगरied.
 *
 * bit 0 => 1 अगर key is initially true
 *	    0 अगर initially false
 * bit 1 => 1 अगर poपूर्णांकs to काष्ठा अटल_key_mod
 *	    0 अगर poपूर्णांकs to काष्ठा jump_entry
 */
	जोड़ अणु
		अचिन्हित दीर्घ type;
		काष्ठा jump_entry *entries;
		काष्ठा अटल_key_mod *next;
	पूर्ण;
पूर्ण;

#अन्यथा
काष्ठा अटल_key अणु
	atomic_t enabled;
पूर्ण;
#पूर्ण_अगर	/* CONFIG_JUMP_LABEL */
#पूर्ण_अगर /* __ASSEMBLY__ */

#अगर_घोषित CONFIG_JUMP_LABEL
#समावेश <यंत्र/jump_label.h>

#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित CONFIG_HAVE_ARCH_JUMP_LABEL_RELATIVE

काष्ठा jump_entry अणु
	s32 code;
	s32 target;
	दीर्घ key;	// key may be far away from the core kernel under KASLR
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ jump_entry_code(स्थिर काष्ठा jump_entry *entry)
अणु
	वापस (अचिन्हित दीर्घ)&entry->code + entry->code;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ jump_entry_target(स्थिर काष्ठा jump_entry *entry)
अणु
	वापस (अचिन्हित दीर्घ)&entry->target + entry->target;
पूर्ण

अटल अंतरभूत काष्ठा अटल_key *jump_entry_key(स्थिर काष्ठा jump_entry *entry)
अणु
	दीर्घ offset = entry->key & ~3L;

	वापस (काष्ठा अटल_key *)((अचिन्हित दीर्घ)&entry->key + offset);
पूर्ण

#अन्यथा

अटल अंतरभूत अचिन्हित दीर्घ jump_entry_code(स्थिर काष्ठा jump_entry *entry)
अणु
	वापस entry->code;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ jump_entry_target(स्थिर काष्ठा jump_entry *entry)
अणु
	वापस entry->target;
पूर्ण

अटल अंतरभूत काष्ठा अटल_key *jump_entry_key(स्थिर काष्ठा jump_entry *entry)
अणु
	वापस (काष्ठा अटल_key *)((अचिन्हित दीर्घ)entry->key & ~3UL);
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत bool jump_entry_is_branch(स्थिर काष्ठा jump_entry *entry)
अणु
	वापस (अचिन्हित दीर्घ)entry->key & 1UL;
पूर्ण

अटल अंतरभूत bool jump_entry_is_init(स्थिर काष्ठा jump_entry *entry)
अणु
	वापस (अचिन्हित दीर्घ)entry->key & 2UL;
पूर्ण

अटल अंतरभूत व्योम jump_entry_set_init(काष्ठा jump_entry *entry)
अणु
	entry->key |= 2;
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

क्रमागत jump_label_type अणु
	JUMP_LABEL_NOP = 0,
	JUMP_LABEL_JMP,
पूर्ण;

काष्ठा module;

#अगर_घोषित CONFIG_JUMP_LABEL

#घोषणा JUMP_TYPE_FALSE		0UL
#घोषणा JUMP_TYPE_TRUE		1UL
#घोषणा JUMP_TYPE_LINKED	2UL
#घोषणा JUMP_TYPE_MASK		3UL

अटल __always_अंतरभूत bool अटल_key_false(काष्ठा अटल_key *key)
अणु
	वापस arch_अटल_branch(key, false);
पूर्ण

अटल __always_अंतरभूत bool अटल_key_true(काष्ठा अटल_key *key)
अणु
	वापस !arch_अटल_branch(key, true);
पूर्ण

बाह्य काष्ठा jump_entry __start___jump_table[];
बाह्य काष्ठा jump_entry __stop___jump_table[];

बाह्य व्योम jump_label_init(व्योम);
बाह्य व्योम jump_label_lock(व्योम);
बाह्य व्योम jump_label_unlock(व्योम);
बाह्य व्योम arch_jump_label_transक्रमm(काष्ठा jump_entry *entry,
				      क्रमागत jump_label_type type);
बाह्य व्योम arch_jump_label_transक्रमm_अटल(काष्ठा jump_entry *entry,
					     क्रमागत jump_label_type type);
बाह्य bool arch_jump_label_transक्रमm_queue(काष्ठा jump_entry *entry,
					    क्रमागत jump_label_type type);
बाह्य व्योम arch_jump_label_transक्रमm_apply(व्योम);
बाह्य पूर्णांक jump_label_text_reserved(व्योम *start, व्योम *end);
बाह्य व्योम अटल_key_slow_inc(काष्ठा अटल_key *key);
बाह्य व्योम अटल_key_slow_dec(काष्ठा अटल_key *key);
बाह्य व्योम अटल_key_slow_inc_cpuslocked(काष्ठा अटल_key *key);
बाह्य व्योम अटल_key_slow_dec_cpuslocked(काष्ठा अटल_key *key);
बाह्य व्योम jump_label_apply_nops(काष्ठा module *mod);
बाह्य पूर्णांक अटल_key_count(काष्ठा अटल_key *key);
बाह्य व्योम अटल_key_enable(काष्ठा अटल_key *key);
बाह्य व्योम अटल_key_disable(काष्ठा अटल_key *key);
बाह्य व्योम अटल_key_enable_cpuslocked(काष्ठा अटल_key *key);
बाह्य व्योम अटल_key_disable_cpuslocked(काष्ठा अटल_key *key);

/*
 * We should be using ATOMIC_INIT() क्रम initializing .enabled, but
 * the inclusion of atomic.h is problematic क्रम inclusion of jump_label.h
 * in 'low-level' headers. Thus, we are initializing .enabled with a
 * raw value, but have added a BUILD_BUG_ON() to catch any issues in
 * jump_label_init() see: kernel/jump_label.c.
 */
#घोषणा STATIC_KEY_INIT_TRUE					\
	अणु .enabled = अणु 1 पूर्ण,					\
	  अणु .entries = (व्योम *)JUMP_TYPE_TRUE पूर्ण पूर्ण
#घोषणा STATIC_KEY_INIT_FALSE					\
	अणु .enabled = अणु 0 पूर्ण,					\
	  अणु .entries = (व्योम *)JUMP_TYPE_FALSE पूर्ण पूर्ण

#अन्यथा  /* !CONFIG_JUMP_LABEL */

#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>

अटल अंतरभूत पूर्णांक अटल_key_count(काष्ठा अटल_key *key)
अणु
	वापस atomic_पढ़ो(&key->enabled);
पूर्ण

अटल __always_अंतरभूत व्योम jump_label_init(व्योम)
अणु
	अटल_key_initialized = true;
पूर्ण

अटल __always_अंतरभूत bool अटल_key_false(काष्ठा अटल_key *key)
अणु
	अगर (unlikely_notrace(अटल_key_count(key) > 0))
		वापस true;
	वापस false;
पूर्ण

अटल __always_अंतरभूत bool अटल_key_true(काष्ठा अटल_key *key)
अणु
	अगर (likely_notrace(अटल_key_count(key) > 0))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत व्योम अटल_key_slow_inc(काष्ठा अटल_key *key)
अणु
	STATIC_KEY_CHECK_USE(key);
	atomic_inc(&key->enabled);
पूर्ण

अटल अंतरभूत व्योम अटल_key_slow_dec(काष्ठा अटल_key *key)
अणु
	STATIC_KEY_CHECK_USE(key);
	atomic_dec(&key->enabled);
पूर्ण

#घोषणा अटल_key_slow_inc_cpuslocked(key) अटल_key_slow_inc(key)
#घोषणा अटल_key_slow_dec_cpuslocked(key) अटल_key_slow_dec(key)

अटल अंतरभूत पूर्णांक jump_label_text_reserved(व्योम *start, व्योम *end)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम jump_label_lock(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम jump_label_unlock(व्योम) अणुपूर्ण

अटल अंतरभूत पूर्णांक jump_label_apply_nops(काष्ठा module *mod)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम अटल_key_enable(काष्ठा अटल_key *key)
अणु
	STATIC_KEY_CHECK_USE(key);

	अगर (atomic_पढ़ो(&key->enabled) != 0) अणु
		WARN_ON_ONCE(atomic_पढ़ो(&key->enabled) != 1);
		वापस;
	पूर्ण
	atomic_set(&key->enabled, 1);
पूर्ण

अटल अंतरभूत व्योम अटल_key_disable(काष्ठा अटल_key *key)
अणु
	STATIC_KEY_CHECK_USE(key);

	अगर (atomic_पढ़ो(&key->enabled) != 1) अणु
		WARN_ON_ONCE(atomic_पढ़ो(&key->enabled) != 0);
		वापस;
	पूर्ण
	atomic_set(&key->enabled, 0);
पूर्ण

#घोषणा अटल_key_enable_cpuslocked(k)		अटल_key_enable((k))
#घोषणा अटल_key_disable_cpuslocked(k)	अटल_key_disable((k))

#घोषणा STATIC_KEY_INIT_TRUE	अणु .enabled = ATOMIC_INIT(1) पूर्ण
#घोषणा STATIC_KEY_INIT_FALSE	अणु .enabled = ATOMIC_INIT(0) पूर्ण

#पूर्ण_अगर	/* CONFIG_JUMP_LABEL */

#घोषणा STATIC_KEY_INIT STATIC_KEY_INIT_FALSE
#घोषणा jump_label_enabled अटल_key_enabled

/* -------------------------------------------------------------------------- */

/*
 * Two type wrappers around अटल_key, such that we can use compile समय
 * type dअगरferentiation to emit the right code.
 *
 * All the below code is macros in order to play type games.
 */

काष्ठा अटल_key_true अणु
	काष्ठा अटल_key key;
पूर्ण;

काष्ठा अटल_key_false अणु
	काष्ठा अटल_key key;
पूर्ण;

#घोषणा STATIC_KEY_TRUE_INIT  (काष्ठा अटल_key_true) अणु .key = STATIC_KEY_INIT_TRUE,  पूर्ण
#घोषणा STATIC_KEY_FALSE_INIT (काष्ठा अटल_key_false)अणु .key = STATIC_KEY_INIT_FALSE, पूर्ण

#घोषणा DEFINE_STATIC_KEY_TRUE(name)	\
	काष्ठा अटल_key_true name = STATIC_KEY_TRUE_INIT

#घोषणा DEFINE_STATIC_KEY_TRUE_RO(name)	\
	काष्ठा अटल_key_true name __ro_after_init = STATIC_KEY_TRUE_INIT

#घोषणा DECLARE_STATIC_KEY_TRUE(name)	\
	बाह्य काष्ठा अटल_key_true name

#घोषणा DEFINE_STATIC_KEY_FALSE(name)	\
	काष्ठा अटल_key_false name = STATIC_KEY_FALSE_INIT

#घोषणा DEFINE_STATIC_KEY_FALSE_RO(name)	\
	काष्ठा अटल_key_false name __ro_after_init = STATIC_KEY_FALSE_INIT

#घोषणा DECLARE_STATIC_KEY_FALSE(name)	\
	बाह्य काष्ठा अटल_key_false name

#घोषणा DEFINE_STATIC_KEY_ARRAY_TRUE(name, count)		\
	काष्ठा अटल_key_true name[count] = अणु			\
		[0 ... (count) - 1] = STATIC_KEY_TRUE_INIT,	\
	पूर्ण

#घोषणा DEFINE_STATIC_KEY_ARRAY_FALSE(name, count)		\
	काष्ठा अटल_key_false name[count] = अणु			\
		[0 ... (count) - 1] = STATIC_KEY_FALSE_INIT,	\
	पूर्ण

#घोषणा _DEFINE_STATIC_KEY_1(name)	DEFINE_STATIC_KEY_TRUE(name)
#घोषणा _DEFINE_STATIC_KEY_0(name)	DEFINE_STATIC_KEY_FALSE(name)
#घोषणा DEFINE_STATIC_KEY_MAYBE(cfg, name)			\
	__PASTE(_DEFINE_STATIC_KEY_, IS_ENABLED(cfg))(name)

#घोषणा _DEFINE_STATIC_KEY_RO_1(name)	DEFINE_STATIC_KEY_TRUE_RO(name)
#घोषणा _DEFINE_STATIC_KEY_RO_0(name)	DEFINE_STATIC_KEY_FALSE_RO(name)
#घोषणा DEFINE_STATIC_KEY_MAYBE_RO(cfg, name)			\
	__PASTE(_DEFINE_STATIC_KEY_RO_, IS_ENABLED(cfg))(name)

#घोषणा _DECLARE_STATIC_KEY_1(name)	DECLARE_STATIC_KEY_TRUE(name)
#घोषणा _DECLARE_STATIC_KEY_0(name)	DECLARE_STATIC_KEY_FALSE(name)
#घोषणा DECLARE_STATIC_KEY_MAYBE(cfg, name)			\
	__PASTE(_DECLARE_STATIC_KEY_, IS_ENABLED(cfg))(name)

बाह्य bool ____wrong_branch_error(व्योम);

#घोषणा अटल_key_enabled(x)							\
(अणु										\
	अगर (!__builtin_types_compatible_p(typeof(*x), काष्ठा अटल_key) &&	\
	    !__builtin_types_compatible_p(typeof(*x), काष्ठा अटल_key_true) &&\
	    !__builtin_types_compatible_p(typeof(*x), काष्ठा अटल_key_false))	\
		____wrong_branch_error();					\
	अटल_key_count((काष्ठा अटल_key *)x) > 0;				\
पूर्ण)

#अगर_घोषित CONFIG_JUMP_LABEL

/*
 * Combine the right initial value (type) with the right branch order
 * to generate the desired result.
 *
 *
 * type\मranch|	likely (1)	      |	unlikely (0)
 * -----------+-----------------------+------------------
 *            |                       |
 *  true (1)  |	   ...		      |	   ...
 *            |    NOP		      |	   JMP L
 *            |    <br-sपंचांगts>	      |	1: ...
 *            |	L: ...		      |
 *            |			      |
 *            |			      |	L: <br-sपंचांगts>
 *            |			      |	   jmp 1b
 *            |                       |
 * -----------+-----------------------+------------------
 *            |                       |
 *  false (0) |	   ...		      |	   ...
 *            |    JMP L	      |	   NOP
 *            |    <br-sपंचांगts>	      |	1: ...
 *            |	L: ...		      |
 *            |			      |
 *            |			      |	L: <br-sपंचांगts>
 *            |			      |	   jmp 1b
 *            |                       |
 * -----------+-----------------------+------------------
 *
 * The initial value is encoded in the LSB of अटल_key::entries,
 * type: 0 = false, 1 = true.
 *
 * The branch type is encoded in the LSB of jump_entry::key,
 * branch: 0 = unlikely, 1 = likely.
 *
 * This gives the following logic table:
 *
 *	enabled	type	branch	  instuction
 * -----------------------------+-----------
 *	0	0	0	| NOP
 *	0	0	1	| JMP
 *	0	1	0	| NOP
 *	0	1	1	| JMP
 *
 *	1	0	0	| JMP
 *	1	0	1	| NOP
 *	1	1	0	| JMP
 *	1	1	1	| NOP
 *
 * Which gives the following functions:
 *
 *   dynamic: inकाष्ठाion = enabled ^ branch
 *   अटल:  inकाष्ठाion = type ^ branch
 *
 * See jump_label_type() / jump_label_init_type().
 */

#घोषणा अटल_branch_likely(x)							\
(अणु										\
	bool branch;								\
	अगर (__builtin_types_compatible_p(typeof(*x), काष्ठा अटल_key_true))	\
		branch = !arch_अटल_branch(&(x)->key, true);			\
	अन्यथा अगर (__builtin_types_compatible_p(typeof(*x), काष्ठा अटल_key_false)) \
		branch = !arch_अटल_branch_jump(&(x)->key, true);		\
	अन्यथा									\
		branch = ____wrong_branch_error();				\
	likely_notrace(branch);								\
पूर्ण)

#घोषणा अटल_branch_unlikely(x)						\
(अणु										\
	bool branch;								\
	अगर (__builtin_types_compatible_p(typeof(*x), काष्ठा अटल_key_true))	\
		branch = arch_अटल_branch_jump(&(x)->key, false);		\
	अन्यथा अगर (__builtin_types_compatible_p(typeof(*x), काष्ठा अटल_key_false)) \
		branch = arch_अटल_branch(&(x)->key, false);			\
	अन्यथा									\
		branch = ____wrong_branch_error();				\
	unlikely_notrace(branch);							\
पूर्ण)

#अन्यथा /* !CONFIG_JUMP_LABEL */

#घोषणा अटल_branch_likely(x)		likely_notrace(अटल_key_enabled(&(x)->key))
#घोषणा अटल_branch_unlikely(x)	unlikely_notrace(अटल_key_enabled(&(x)->key))

#पूर्ण_अगर /* CONFIG_JUMP_LABEL */

#घोषणा अटल_branch_maybe(config, x)					\
	(IS_ENABLED(config) ? अटल_branch_likely(x)			\
			    : अटल_branch_unlikely(x))

/*
 * Advanced usage; refcount, branch is enabled when: count != 0
 */

#घोषणा अटल_branch_inc(x)		अटल_key_slow_inc(&(x)->key)
#घोषणा अटल_branch_dec(x)		अटल_key_slow_dec(&(x)->key)
#घोषणा अटल_branch_inc_cpuslocked(x)	अटल_key_slow_inc_cpuslocked(&(x)->key)
#घोषणा अटल_branch_dec_cpuslocked(x)	अटल_key_slow_dec_cpuslocked(&(x)->key)

/*
 * Normal usage; boolean enable/disable.
 */

#घोषणा अटल_branch_enable(x)			अटल_key_enable(&(x)->key)
#घोषणा अटल_branch_disable(x)		अटल_key_disable(&(x)->key)
#घोषणा अटल_branch_enable_cpuslocked(x)	अटल_key_enable_cpuslocked(&(x)->key)
#घोषणा अटल_branch_disable_cpuslocked(x)	अटल_key_disable_cpuslocked(&(x)->key)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर	/* _LINUX_JUMP_LABEL_H */
