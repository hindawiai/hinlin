<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_INसूचीECT_CALL_WRAPPER_H
#घोषणा _LINUX_INसूचीECT_CALL_WRAPPER_H

#अगर_घोषित CONFIG_RETPOLINE

/*
 * INसूचीECT_CALL_$NR - wrapper क्रम indirect calls with $NR known builtin
 *  @f: function poपूर्णांकer
 *  @f$NR: builtin functions names, up to $NR of them
 *  @__VA_ARGS__: arguments क्रम @f
 *
 * Aव्योम retpoline overhead क्रम known builtin, checking @f vs each of them and
 * eventually invoking directly the builtin function. The functions are check
 * in the given order. Fallback to the indirect call.
 */
#घोषणा INसूचीECT_CALL_1(f, f1, ...)					\
	(अणु								\
		likely(f == f1) ? f1(__VA_ARGS__) : f(__VA_ARGS__);	\
	पूर्ण)
#घोषणा INसूचीECT_CALL_2(f, f2, f1, ...)					\
	(अणु								\
		likely(f == f2) ? f2(__VA_ARGS__) :			\
				  INसूचीECT_CALL_1(f, f1, __VA_ARGS__);	\
	पूर्ण)
#घोषणा INसूचीECT_CALL_3(f, f3, f2, f1, ...)					\
	(अणु									\
		likely(f == f3) ? f3(__VA_ARGS__) :				\
				  INसूचीECT_CALL_2(f, f2, f1, __VA_ARGS__);	\
	पूर्ण)
#घोषणा INसूचीECT_CALL_4(f, f4, f3, f2, f1, ...)					\
	(अणु									\
		likely(f == f4) ? f4(__VA_ARGS__) :				\
				  INसूचीECT_CALL_3(f, f3, f2, f1, __VA_ARGS__);	\
	पूर्ण)

#घोषणा INसूचीECT_CALLABLE_DECLARE(f)	f
#घोषणा INसूचीECT_CALLABLE_SCOPE
#घोषणा EXPORT_INसूचीECT_CALLABLE(f)	EXPORT_SYMBOL(f)

#अन्यथा
#घोषणा INसूचीECT_CALL_1(f, f1, ...) f(__VA_ARGS__)
#घोषणा INसूचीECT_CALL_2(f, f2, f1, ...) f(__VA_ARGS__)
#घोषणा INसूचीECT_CALL_3(f, f3, f2, f1, ...) f(__VA_ARGS__)
#घोषणा INसूचीECT_CALL_4(f, f4, f3, f2, f1, ...) f(__VA_ARGS__)
#घोषणा INसूचीECT_CALLABLE_DECLARE(f)
#घोषणा INसूचीECT_CALLABLE_SCOPE		अटल
#घोषणा EXPORT_INसूचीECT_CALLABLE(f)
#पूर्ण_अगर

/*
 * We can use INसूचीECT_CALL_$NR क्रम ipv6 related functions only अगर ipv6 is
 * builtin, this macro simplअगरy dealing with indirect calls with only ipv4/ipv6
 * alternatives
 */
#अगर IS_BUILTIN(CONFIG_IPV6)
#घोषणा INसूचीECT_CALL_INET(f, f2, f1, ...) \
	INसूचीECT_CALL_2(f, f2, f1, __VA_ARGS__)
#या_अगर IS_ENABLED(CONFIG_INET)
#घोषणा INसूचीECT_CALL_INET(f, f2, f1, ...) INसूचीECT_CALL_1(f, f1, __VA_ARGS__)
#अन्यथा
#घोषणा INसूचीECT_CALL_INET(f, f2, f1, ...) f(__VA_ARGS__)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_INET)
#घोषणा INसूचीECT_CALL_INET_1(f, f1, ...) INसूचीECT_CALL_1(f, f1, __VA_ARGS__)
#अन्यथा
#घोषणा INसूचीECT_CALL_INET_1(f, f1, ...) f(__VA_ARGS__)
#पूर्ण_अगर

#पूर्ण_अगर
