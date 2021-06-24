<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_CPUFEATURE_H
#घोषणा _ASM_X86_CPUFEATURE_H

#समावेश <यंत्र/processor.h>

#अगर defined(__KERNEL__) && !defined(__ASSEMBLY__)

#समावेश <यंत्र/यंत्र.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/alternative.h>

क्रमागत cpuid_leafs
अणु
	CPUID_1_EDX		= 0,
	CPUID_8000_0001_EDX,
	CPUID_8086_0001_EDX,
	CPUID_LNX_1,
	CPUID_1_ECX,
	CPUID_C000_0001_EDX,
	CPUID_8000_0001_ECX,
	CPUID_LNX_2,
	CPUID_LNX_3,
	CPUID_7_0_EBX,
	CPUID_D_1_EAX,
	CPUID_LNX_4,
	CPUID_7_1_EAX,
	CPUID_8000_0008_EBX,
	CPUID_6_EAX,
	CPUID_8000_000A_EDX,
	CPUID_7_ECX,
	CPUID_8000_0007_EBX,
	CPUID_7_EDX,
	CPUID_8000_001F_EAX,
पूर्ण;

#अगर_घोषित CONFIG_X86_FEATURE_NAMES
बाह्य स्थिर अक्षर * स्थिर x86_cap_flags[NCAPINTS*32];
बाह्य स्थिर अक्षर * स्थिर x86_घातer_flags[32];
#घोषणा X86_CAP_FMT "%s"
#घोषणा x86_cap_flag(flag) x86_cap_flags[flag]
#अन्यथा
#घोषणा X86_CAP_FMT "%d:%d"
#घोषणा x86_cap_flag(flag) ((flag) >> 5), ((flag) & 31)
#पूर्ण_अगर

/*
 * In order to save room, we index पूर्णांकo this array by करोing
 * X86_BUG_<name> - NCAPINTS*32.
 */
बाह्य स्थिर अक्षर * स्थिर x86_bug_flags[NBUGINTS*32];

#घोषणा test_cpu_cap(c, bit)						\
	 test_bit(bit, (अचिन्हित दीर्घ *)((c)->x86_capability))

/*
 * There are 32 bits/features in each mask word.  The high bits
 * (selected with (bit>>5) give us the word number and the low 5
 * bits give us the bit/feature number inside the word.
 * (1UL<<((bit)&31) gives us a mask क्रम the feature_bit so we can
 * see अगर it is set in the mask word.
 */
#घोषणा CHECK_BIT_IN_MASK_WORD(maskname, word, bit)	\
	(((bit)>>5)==(word) && (1UL<<((bit)&31) & maskname##word ))

/*
 * अणुREQUIRED,DISABLEDपूर्ण_MASK_CHECK below may seem duplicated with the
 * following BUILD_BUG_ON_ZERO() check but when NCAPINTS माला_लो changed, all
 * header macros which use NCAPINTS need to be changed. The duplicated macro
 * use causes the compiler to issue errors क्रम all headers so that all usage
 * sites can be corrected.
 */
#घोषणा REQUIRED_MASK_BIT_SET(feature_bit)		\
	 ( CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK,  0, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK,  1, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK,  2, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK,  3, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK,  4, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK,  5, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK,  6, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK,  7, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK,  8, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK,  9, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK, 10, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK, 11, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK, 12, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK, 13, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK, 14, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK, 15, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK, 16, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK, 17, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK, 18, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(REQUIRED_MASK, 19, feature_bit) ||	\
	   REQUIRED_MASK_CHECK					  ||	\
	   BUILD_BUG_ON_ZERO(NCAPINTS != 20))

#घोषणा DISABLED_MASK_BIT_SET(feature_bit)				\
	 ( CHECK_BIT_IN_MASK_WORD(DISABLED_MASK,  0, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK,  1, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK,  2, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK,  3, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK,  4, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK,  5, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK,  6, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK,  7, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK,  8, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK,  9, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK, 10, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK, 11, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK, 12, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK, 13, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK, 14, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK, 15, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK, 16, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK, 17, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK, 18, feature_bit) ||	\
	   CHECK_BIT_IN_MASK_WORD(DISABLED_MASK, 19, feature_bit) ||	\
	   DISABLED_MASK_CHECK					  ||	\
	   BUILD_BUG_ON_ZERO(NCAPINTS != 20))

#घोषणा cpu_has(c, bit)							\
	(__builtin_स्थिरant_p(bit) && REQUIRED_MASK_BIT_SET(bit) ? 1 :	\
	 test_cpu_cap(c, bit))

#घोषणा this_cpu_has(bit)						\
	(__builtin_स्थिरant_p(bit) && REQUIRED_MASK_BIT_SET(bit) ? 1 :	\
	 x86_this_cpu_test_bit(bit,					\
		(अचिन्हित दीर्घ __percpu *)&cpu_info.x86_capability))

/*
 * This macro is क्रम detection of features which need kernel
 * infraकाष्ठाure to be used.  It may *not* directly test the CPU
 * itself.  Use the cpu_has() family अगर you want true runसमय
 * testing of CPU features, like in hypervisor code where you are
 * supporting a possible guest feature where host support क्रम it
 * is not relevant.
 */
#घोषणा cpu_feature_enabled(bit)	\
	(__builtin_स्थिरant_p(bit) && DISABLED_MASK_BIT_SET(bit) ? 0 : अटल_cpu_has(bit))

#घोषणा boot_cpu_has(bit)	cpu_has(&boot_cpu_data, bit)

#घोषणा set_cpu_cap(c, bit)	set_bit(bit, (अचिन्हित दीर्घ *)((c)->x86_capability))

बाह्य व्योम setup_clear_cpu_cap(अचिन्हित पूर्णांक bit);
बाह्य व्योम clear_cpu_cap(काष्ठा cpuinfo_x86 *c, अचिन्हित पूर्णांक bit);

#घोषणा setup_क्रमce_cpu_cap(bit) करो अणु \
	set_cpu_cap(&boot_cpu_data, bit);	\
	set_bit(bit, (अचिन्हित दीर्घ *)cpu_caps_set);	\
पूर्ण जबतक (0)

#घोषणा setup_क्रमce_cpu_bug(bit) setup_क्रमce_cpu_cap(bit)

#अगर defined(__clang__) && !defined(CONFIG_CC_HAS_ASM_GOTO)

/*
 * Workaround क्रम the sake of BPF compilation which utilizes kernel
 * headers, but clang करोes not support ASM GOTO and fails the build.
 */
#अगर_अघोषित __BPF_TRACING__
#warning "Compiler lacks ASM_GOTO support. Add -D __BPF_TRACING__ to your compiler arguments"
#पूर्ण_अगर

#घोषणा अटल_cpu_has(bit)            boot_cpu_has(bit)

#अन्यथा

/*
 * Static testing of CPU features. Used the same as boot_cpu_has(). It
 * अटलally patches the target code क्रम additional perक्रमmance. Use
 * अटल_cpu_has() only in fast paths, where every cycle counts. Which
 * means that the boot_cpu_has() variant is alपढ़ोy fast enough क्रम the
 * majority of हालs and you should stick to using it as it is generally
 * only two inकाष्ठाions: a RIP-relative MOV and a TEST.
 */
अटल __always_अंतरभूत bool _अटल_cpu_has(u16 bit)
अणु
	यंत्र_अस्थिर_जाओ(
		ALTERNATIVE_TERNARY("jmp 6f", %P[feature], "", "jmp %l[t_no]")
		".section .altinstr_aux,\"ax\"\n"
		"6:\n"
		" testb %[bitnum],%[cap_byte]\n"
		" jnz %l[t_yes]\n"
		" jmp %l[t_no]\n"
		".previous\n"
		 : : [feature]  "i" (bit),
		     [bitnum]   "i" (1 << (bit & 7)),
		     [cap_byte] "m" (((स्थिर अक्षर *)boot_cpu_data.x86_capability)[bit >> 3])
		 : : t_yes, t_no);
t_yes:
	वापस true;
t_no:
	वापस false;
पूर्ण

#घोषणा अटल_cpu_has(bit)					\
(								\
	__builtin_स्थिरant_p(boot_cpu_has(bit)) ?		\
		boot_cpu_has(bit) :				\
		_अटल_cpu_has(bit)				\
)
#पूर्ण_अगर

#घोषणा cpu_has_bug(c, bit)		cpu_has(c, (bit))
#घोषणा set_cpu_bug(c, bit)		set_cpu_cap(c, (bit))
#घोषणा clear_cpu_bug(c, bit)		clear_cpu_cap(c, (bit))

#घोषणा अटल_cpu_has_bug(bit)		अटल_cpu_has((bit))
#घोषणा boot_cpu_has_bug(bit)		cpu_has_bug(&boot_cpu_data, (bit))
#घोषणा boot_cpu_set_bug(bit)		set_cpu_cap(&boot_cpu_data, (bit))

#घोषणा MAX_CPU_FEATURES		(NCAPINTS * 32)
#घोषणा cpu_have_feature		boot_cpu_has

#घोषणा CPU_FEATURE_TYPEFMT		"x86,ven%04Xfam%04Xmod%04X"
#घोषणा CPU_FEATURE_TYPEVAL		boot_cpu_data.x86_venकरोr, boot_cpu_data.x86, \
					boot_cpu_data.x86_model

#पूर्ण_अगर /* defined(__KERNEL__) && !defined(__ASSEMBLY__) */
#पूर्ण_अगर /* _ASM_X86_CPUFEATURE_H */
