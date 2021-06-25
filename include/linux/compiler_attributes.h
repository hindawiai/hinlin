<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_COMPILER_ATTRIBUTES_H
#घोषणा __LINUX_COMPILER_ATTRIBUTES_H

/*
 * The attributes in this file are unconditionally defined and they directly
 * map to compiler attribute(s), unless one of the compilers करोes not support
 * the attribute. In that हाल, __has_attribute is used to check क्रम support
 * and the reason is stated in its comment ("Optional: ...").
 *
 * Any other "attributes" (i.e. those that depend on a configuration option,
 * on a compiler, on an architecture, on plugins, on other attributes...)
 * should be defined अन्यथाwhere (e.g. compiler_types.h or compiler-*.h).
 * The पूर्णांकention is to keep this file as simple as possible, as well as
 * compiler- and version-agnostic (e.g. aव्योमing GCC_VERSION checks).
 *
 * This file is meant to be sorted (by actual attribute name,
 * not by #घोषणा identअगरier). Use the __attribute__((__name__)) syntax
 * (i.e. with underscores) to aव्योम future collisions with other macros.
 * Provide links to the करोcumentation of each supported compiler, अगर it exists.
 */

/*
 * __has_attribute is supported on gcc >= 5, clang >= 2.9 and icc >= 17.
 * In the meanसमय, to support gcc < 5, we implement __has_attribute
 * by hand.
 */
#अगर_अघोषित __has_attribute
# define __has_attribute(x) __GCC4_has_attribute_##x
# define __GCC4_has_attribute___assume_aligned__      (__GNUC_MINOR__ >= 9)
# define __GCC4_has_attribute___copy__                0
# define __GCC4_has_attribute___designated_init__     0
# define __GCC4_has_attribute___बाह्यally_visible__  1
# define __GCC4_has_attribute___no_caller_saved_रेजिस्टरs__ 0
# define __GCC4_has_attribute___noclone__             1
# define __GCC4_has_attribute___nonstring__           0
# define __GCC4_has_attribute___no_sanitize_address__ (__GNUC_MINOR__ >= 8)
# define __GCC4_has_attribute___no_sanitize_undefined__ (__GNUC_MINOR__ >= 9)
# define __GCC4_has_attribute___fallthrough__         0
#पूर्ण_अगर

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-alias-function-attribute
 */
#घोषणा __alias(symbol)                 __attribute__((__alias__(#symbol)))

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-aligned-function-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Type-Attributes.hपंचांगl#index-aligned-type-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Variable-Attributes.hपंचांगl#index-aligned-variable-attribute
 */
#घोषणा __aligned(x)                    __attribute__((__aligned__(x)))
#घोषणा __aligned_largest               __attribute__((__aligned__))

/*
 * Note: users of __always_अंतरभूत currently करो not ग_लिखो "inline" themselves,
 * which seems to be required by gcc to apply the attribute according
 * to its करोcs (and also "warning: always_अंतरभूत function might not be
 * inlinable [-Wattributes]" is emitted).
 *
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-always_005fअंतरभूत-function-attribute
 * clang: mentioned
 */
#घोषणा __always_अंतरभूत                 अंतरभूत __attribute__((__always_अंतरभूत__))

/*
 * The second argument is optional (शेष 0), so we use a variadic macro
 * to make the लघुhand.
 *
 * Beware: Do not apply this to functions which may वापस
 * ERR_PTRs. Also, it is probably unwise to apply it to functions
 * वापसing extra inक्रमmation in the low bits (but in that हाल the
 * compiler should see some alignment anyway, when the वापस value is
 * massaged by 'flags = ptr & 3; ptr &= ~3;').
 *
 * Optional: only supported since gcc >= 4.9
 * Optional: not supported by icc
 *
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-assume_005faligned-function-attribute
 * clang: https://clang.llvm.org/करोcs/AttributeReference.hपंचांगl#assume-aligned
 */
#अगर __has_attribute(__assume_aligned__)
# define __assume_aligned(a, ...)       __attribute__((__assume_aligned__(a, ## __VA_ARGS__)))
#अन्यथा
# define __assume_aligned(a, ...)
#पूर्ण_अगर

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-cold-function-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Label-Attributes.hपंचांगl#index-cold-label-attribute
 */
#घोषणा __cold                          __attribute__((__cold__))

/*
 * Note the दीर्घ name.
 *
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-स्थिर-function-attribute
 */
#घोषणा __attribute_स्थिर__             __attribute__((__स्थिर__))

/*
 * Optional: only supported since gcc >= 9
 * Optional: not supported by clang
 * Optional: not supported by icc
 *
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-copy-function-attribute
 */
#अगर __has_attribute(__copy__)
# define __copy(symbol)                 __attribute__((__copy__(symbol)))
#अन्यथा
# define __copy(symbol)
#पूर्ण_अगर

/*
 * Don't. Just don't. See commit 771c035372a0 ("deprecate the '__deprecated'
 * attribute warnings entirely and क्रम good") क्रम more inक्रमmation.
 *
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-deprecated-function-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Type-Attributes.hपंचांगl#index-deprecated-type-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Variable-Attributes.hपंचांगl#index-deprecated-variable-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Enumerator-Attributes.hपंचांगl#index-deprecated-क्रमागतerator-attribute
 * clang: https://clang.llvm.org/करोcs/AttributeReference.hपंचांगl#deprecated
 */
#घोषणा __deprecated

/*
 * Optional: only supported since gcc >= 5.1
 * Optional: not supported by clang
 * Optional: not supported by icc
 *
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Type-Attributes.hपंचांगl#index-designated_005finit-type-attribute
 */
#अगर __has_attribute(__designated_init__)
# define __designated_init              __attribute__((__designated_init__))
#अन्यथा
# define __designated_init
#पूर्ण_अगर

/*
 * Optional: not supported by clang
 *
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-बाह्यally_005fvisible-function-attribute
 */
#अगर __has_attribute(__बाह्यally_visible__)
# define __visible                      __attribute__((__बाह्यally_visible__))
#अन्यथा
# define __visible
#पूर्ण_अगर

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-क्रमmat-function-attribute
 * clang: https://clang.llvm.org/करोcs/AttributeReference.hपंचांगl#क्रमmat
 */
#घोषणा __म_लिखो(a, b)                  __attribute__((__क्रमmat__(म_लिखो, a, b)))
#घोषणा __म_पूछो(a, b)                   __attribute__((__क्रमmat__(म_पूछो, a, b)))

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-gnu_005fअंतरभूत-function-attribute
 * clang: https://clang.llvm.org/करोcs/AttributeReference.hपंचांगl#gnu-अंतरभूत
 */
#घोषणा __gnu_अंतरभूत                    __attribute__((__gnu_अंतरभूत__))

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-दो_स्मृति-function-attribute
 */
#घोषणा __दो_स्मृति                        __attribute__((__दो_स्मृति__))

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Type-Attributes.hपंचांगl#index-mode-type-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Variable-Attributes.hपंचांगl#index-mode-variable-attribute
 */
#घोषणा __mode(x)                       __attribute__((__mode__(x)))

/*
 * Optional: only supported since gcc >= 7
 *
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/x86-Function-Attributes.hपंचांगl#index-no_005fcaller_005fsaved_005fरेजिस्टरs-function-attribute_002c-x86
 * clang: https://clang.llvm.org/करोcs/AttributeReference.hपंचांगl#no-caller-saved-रेजिस्टरs
 */
#अगर __has_attribute(__no_caller_saved_रेजिस्टरs__)
# define __no_caller_saved_रेजिस्टरs	__attribute__((__no_caller_saved_रेजिस्टरs__))
#अन्यथा
# define __no_caller_saved_रेजिस्टरs
#पूर्ण_अगर

/*
 * Optional: not supported by clang
 *
 *  gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-noclone-function-attribute
 */
#अगर __has_attribute(__noclone__)
# define __noclone                      __attribute__((__noclone__))
#अन्यथा
# define __noclone
#पूर्ण_अगर

/*
 * Add the pseuकरो keyword 'fallthrough' so हाल statement blocks
 * must end with any of these keywords:
 *   अवरोध;
 *   fallthrough;
 *   जारी;
 *   जाओ <label>;
 *   वापस [expression];
 *
 *  gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Statement-Attributes.hपंचांगl#Statement-Attributes
 */
#अगर __has_attribute(__fallthrough__)
# define fallthrough                    __attribute__((__fallthrough__))
#अन्यथा
# define fallthrough                    करो अणुपूर्ण जबतक (0)  /* fallthrough */
#पूर्ण_अगर

/*
 * gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#Common-Function-Attributes
 * clang: https://clang.llvm.org/करोcs/AttributeReference.hपंचांगl#flatten
 */
# define __flatten			__attribute__((flatten))

/*
 * Note the missing underscores.
 *
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-noअंतरभूत-function-attribute
 * clang: mentioned
 */
#घोषणा   noअंतरभूत                      __attribute__((__noअंतरभूत__))

/*
 * Optional: only supported since gcc >= 8
 * Optional: not supported by clang
 * Optional: not supported by icc
 *
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Variable-Attributes.hपंचांगl#index-nonstring-variable-attribute
 */
#अगर __has_attribute(__nonstring__)
# define __nonstring                    __attribute__((__nonstring__))
#अन्यथा
# define __nonstring
#पूर्ण_अगर

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-noवापस-function-attribute
 * clang: https://clang.llvm.org/करोcs/AttributeReference.hपंचांगl#noवापस
 * clang: https://clang.llvm.org/करोcs/AttributeReference.hपंचांगl#id1
 */
#घोषणा __noवापस                      __attribute__((__noवापस__))

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Type-Attributes.hपंचांगl#index-packed-type-attribute
 * clang: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Variable-Attributes.hपंचांगl#index-packed-variable-attribute
 */
#घोषणा __packed                        __attribute__((__packed__))

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-pure-function-attribute
 */
#घोषणा __pure                          __attribute__((__pure__))

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-section-function-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Variable-Attributes.hपंचांगl#index-section-variable-attribute
 * clang: https://clang.llvm.org/करोcs/AttributeReference.hपंचांगl#section-declspec-allocate
 */
#घोषणा __section(section)              __attribute__((__section__(section)))

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-unused-function-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Type-Attributes.hपंचांगl#index-unused-type-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Variable-Attributes.hपंचांगl#index-unused-variable-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Label-Attributes.hपंचांगl#index-unused-label-attribute
 * clang: https://clang.llvm.org/करोcs/AttributeReference.hपंचांगl#maybe-unused-unused
 */
#घोषणा __always_unused                 __attribute__((__unused__))
#घोषणा __maybe_unused                  __attribute__((__unused__))

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-used-function-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Variable-Attributes.hपंचांगl#index-used-variable-attribute
 */
#घोषणा __used                          __attribute__((__used__))

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-warn_005funused_005fresult-function-attribute
 * clang: https://clang.llvm.org/करोcs/AttributeReference.hपंचांगl#nodiscard-warn-unused-result
 */
#घोषणा __must_check                    __attribute__((__warn_unused_result__))

/*
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Function-Attributes.hपंचांगl#index-weak-function-attribute
 *   gcc: https://gcc.gnu.org/onlineकरोcs/gcc/Common-Variable-Attributes.hपंचांगl#index-weak-variable-attribute
 */
#घोषणा __weak                          __attribute__((__weak__))

#पूर्ण_अगर /* __LINUX_COMPILER_ATTRIBUTES_H */
