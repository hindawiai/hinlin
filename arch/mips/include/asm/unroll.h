<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __ASM_UNROLL_H__
#घोषणा __ASM_UNROLL_H__

/*
 * Explicitly unroll a loop, क्रम use in हालs where करोing so is perक्रमmance
 * critical.
 *
 * Ideally we'd rely upon the compiler to provide this but there's no commonly
 * available means to करो so. For example GCC's "#pragma GCC unroll"
 * functionality would be ideal but is only available from GCC 8 onwards. Using
 * -funroll-loops is an option but GCC tends to make poor choices when
 * compiling our string functions. -funroll-all-loops leads to massive code
 * bloat, even अगर only applied to the string functions.
 */
#घोषणा unroll(बार, fn, ...) करो अणु				\
	बाह्य व्योम bad_unroll(व्योम)				\
		__compileसमय_error("Unsupported unroll");	\
								\
	/*							\
	 * We can't unroll if the number of iterations isn't	\
	 * compile-समय स्थिरant. Unक्रमtunately clang versions	\
	 * up until 8.0 tend to miss obvious स्थिरants & cause	\
	 * this check to fail, even though they go on to	\
	 * generate reasonable code क्रम the चयन statement,	\
	 * so we skip the sanity check क्रम those compilers.	\
	 */							\
	BUILD_BUG_ON(!__builtin_स्थिरant_p(बार));		\
								\
	चयन (बार) अणु					\
	हाल 32: fn(__VA_ARGS__); fallthrough;			\
	हाल 31: fn(__VA_ARGS__); fallthrough;			\
	हाल 30: fn(__VA_ARGS__); fallthrough;			\
	हाल 29: fn(__VA_ARGS__); fallthrough;			\
	हाल 28: fn(__VA_ARGS__); fallthrough;			\
	हाल 27: fn(__VA_ARGS__); fallthrough;			\
	हाल 26: fn(__VA_ARGS__); fallthrough;			\
	हाल 25: fn(__VA_ARGS__); fallthrough;			\
	हाल 24: fn(__VA_ARGS__); fallthrough;			\
	हाल 23: fn(__VA_ARGS__); fallthrough;			\
	हाल 22: fn(__VA_ARGS__); fallthrough;			\
	हाल 21: fn(__VA_ARGS__); fallthrough;			\
	हाल 20: fn(__VA_ARGS__); fallthrough;			\
	हाल 19: fn(__VA_ARGS__); fallthrough;			\
	हाल 18: fn(__VA_ARGS__); fallthrough;			\
	हाल 17: fn(__VA_ARGS__); fallthrough;			\
	हाल 16: fn(__VA_ARGS__); fallthrough;			\
	हाल 15: fn(__VA_ARGS__); fallthrough;			\
	हाल 14: fn(__VA_ARGS__); fallthrough;			\
	हाल 13: fn(__VA_ARGS__); fallthrough;			\
	हाल 12: fn(__VA_ARGS__); fallthrough;			\
	हाल 11: fn(__VA_ARGS__); fallthrough;			\
	हाल 10: fn(__VA_ARGS__); fallthrough;			\
	हाल 9: fn(__VA_ARGS__); fallthrough;			\
	हाल 8: fn(__VA_ARGS__); fallthrough;			\
	हाल 7: fn(__VA_ARGS__); fallthrough;			\
	हाल 6: fn(__VA_ARGS__); fallthrough;			\
	हाल 5: fn(__VA_ARGS__); fallthrough;			\
	हाल 4: fn(__VA_ARGS__); fallthrough;			\
	हाल 3: fn(__VA_ARGS__); fallthrough;			\
	हाल 2: fn(__VA_ARGS__); fallthrough;			\
	हाल 1: fn(__VA_ARGS__); fallthrough;			\
	हाल 0: अवरोध;						\
								\
	शेष:						\
		/*						\
		 * Either the iteration count is unreasonable	\
		 * or we need to add more हालs above.		\
		 */						\
		bad_unroll();					\
		अवरोध;						\
	पूर्ण							\
पूर्ण जबतक (0)

#पूर्ण_अगर /* __ASM_UNROLL_H__ */
