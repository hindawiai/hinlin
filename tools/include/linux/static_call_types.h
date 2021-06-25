<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _STATIC_CALL_TYPES_H
#घोषणा _STATIC_CALL_TYPES_H

#समावेश <linux/types.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/compiler.h>

#घोषणा STATIC_CALL_KEY_PREFIX		__SCK__
#घोषणा STATIC_CALL_KEY_PREFIX_STR	__stringअगरy(STATIC_CALL_KEY_PREFIX)
#घोषणा STATIC_CALL_KEY_PREFIX_LEN	(माप(STATIC_CALL_KEY_PREFIX_STR) - 1)
#घोषणा STATIC_CALL_KEY(name)		__PASTE(STATIC_CALL_KEY_PREFIX, name)
#घोषणा STATIC_CALL_KEY_STR(name)	__stringअगरy(STATIC_CALL_KEY(name))

#घोषणा STATIC_CALL_TRAMP_PREFIX	__SCT__
#घोषणा STATIC_CALL_TRAMP_PREFIX_STR	__stringअगरy(STATIC_CALL_TRAMP_PREFIX)
#घोषणा STATIC_CALL_TRAMP_PREFIX_LEN	(माप(STATIC_CALL_TRAMP_PREFIX_STR) - 1)
#घोषणा STATIC_CALL_TRAMP(name)		__PASTE(STATIC_CALL_TRAMP_PREFIX, name)
#घोषणा STATIC_CALL_TRAMP_STR(name)	__stringअगरy(STATIC_CALL_TRAMP(name))

/*
 * Flags in the low bits of अटल_call_site::key.
 */
#घोषणा STATIC_CALL_SITE_TAIL 1UL	/* tail call */
#घोषणा STATIC_CALL_SITE_INIT 2UL	/* init section */
#घोषणा STATIC_CALL_SITE_FLAGS 3UL

/*
 * The अटल call site table needs to be created by बाह्यal tooling (objtool
 * or a compiler plugin).
 */
काष्ठा अटल_call_site अणु
	s32 addr;
	s32 key;
पूर्ण;

#घोषणा DECLARE_STATIC_CALL(name, func)					\
	बाह्य काष्ठा अटल_call_key STATIC_CALL_KEY(name);		\
	बाह्य typeof(func) STATIC_CALL_TRAMP(name);

#अगर_घोषित CONFIG_HAVE_STATIC_CALL

#घोषणा __raw_अटल_call(name)	(&STATIC_CALL_TRAMP(name))

#अगर_घोषित CONFIG_HAVE_STATIC_CALL_INLINE

/*
 * __ADDRESSABLE() is used to ensure the key symbol करोesn't get stripped from
 * the symbol table so that objtool can reference it when it generates the
 * .अटल_call_sites section.
 */
#घोषणा __STATIC_CALL_ADDRESSABLE(name) \
	__ADDRESSABLE(STATIC_CALL_KEY(name))

#घोषणा __अटल_call(name)						\
(अणु									\
	__STATIC_CALL_ADDRESSABLE(name);				\
	__raw_अटल_call(name);					\
पूर्ण)

काष्ठा अटल_call_key अणु
	व्योम *func;
	जोड़ अणु
		/* bit 0: 0 = mods, 1 = sites */
		अचिन्हित दीर्घ type;
		काष्ठा अटल_call_mod *mods;
		काष्ठा अटल_call_site *sites;
	पूर्ण;
पूर्ण;

#अन्यथा /* !CONFIG_HAVE_STATIC_CALL_INLINE */

#घोषणा __STATIC_CALL_ADDRESSABLE(name)
#घोषणा __अटल_call(name)	__raw_अटल_call(name)

काष्ठा अटल_call_key अणु
	व्योम *func;
पूर्ण;

#पूर्ण_अगर /* CONFIG_HAVE_STATIC_CALL_INLINE */

#अगर_घोषित MODULE
#घोषणा __STATIC_CALL_MOD_ADDRESSABLE(name)
#घोषणा अटल_call_mod(name)	__raw_अटल_call(name)
#अन्यथा
#घोषणा __STATIC_CALL_MOD_ADDRESSABLE(name) __STATIC_CALL_ADDRESSABLE(name)
#घोषणा अटल_call_mod(name)	__अटल_call(name)
#पूर्ण_अगर

#घोषणा अटल_call(name)	__अटल_call(name)

#अन्यथा

काष्ठा अटल_call_key अणु
	व्योम *func;
पूर्ण;

#घोषणा अटल_call(name)						\
	((typeof(STATIC_CALL_TRAMP(name))*)(STATIC_CALL_KEY(name).func))

#पूर्ण_अगर /* CONFIG_HAVE_STATIC_CALL */

#पूर्ण_अगर /* _STATIC_CALL_TYPES_H */
