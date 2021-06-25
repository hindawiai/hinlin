<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/armksyms.c
 *
 *  Copyright (C) 2000 Russell King
 */
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/in6.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/arm-smccc.h>

#समावेश <यंत्र/checksum.h>
#समावेश <यंत्र/ftrace.h>

/*
 * libgcc functions - functions that are used पूर्णांकernally by the
 * compiler...  (prototypes are not correct though, but that
 * करोesn't really matter since they're not versioned).
 */
बाह्य व्योम __ashldi3(व्योम);
बाह्य व्योम __ashrdi3(व्योम);
बाह्य व्योम __भागsi3(व्योम);
बाह्य व्योम __lshrdi3(व्योम);
बाह्य व्योम __modsi3(व्योम);
बाह्य व्योम __muldi3(व्योम);
बाह्य व्योम __ucmpdi2(व्योम);
बाह्य व्योम __uभागsi3(व्योम);
बाह्य व्योम __umodsi3(व्योम);
बाह्य व्योम __करो_भाग64(व्योम);
बाह्य व्योम __bswapsi2(व्योम);
बाह्य व्योम __bswapdi2(व्योम);

बाह्य व्योम __aeabi_iभाग(व्योम);
बाह्य व्योम __aeabi_iभागmod(व्योम);
बाह्य व्योम __aeabi_lasr(व्योम);
बाह्य व्योम __aeabi_llsl(व्योम);
बाह्य व्योम __aeabi_llsr(व्योम);
बाह्य व्योम __aeabi_lmul(व्योम);
बाह्य व्योम __aeabi_uiभाग(व्योम);
बाह्य व्योम __aeabi_uiभागmod(व्योम);
बाह्य व्योम __aeabi_ulcmp(व्योम);

बाह्य व्योम fpundefinstr(व्योम);

व्योम mmioset(व्योम *, अचिन्हित पूर्णांक, माप_प्रकार);
व्योम mmiocpy(व्योम *, स्थिर व्योम *, माप_प्रकार);

	/* platक्रमm dependent support */
EXPORT_SYMBOL(arm_delay_ops);

	/* networking */
EXPORT_SYMBOL(csum_partial);
EXPORT_SYMBOL(csum_partial_copy_from_user);
EXPORT_SYMBOL(csum_partial_copy_nocheck);
EXPORT_SYMBOL(__csum_ipv6_magic);

	/* io */
#अगर_अघोषित __raw_पढ़ोsb
EXPORT_SYMBOL(__raw_पढ़ोsb);
#पूर्ण_अगर
#अगर_अघोषित __raw_पढ़ोsw
EXPORT_SYMBOL(__raw_पढ़ोsw);
#पूर्ण_अगर
#अगर_अघोषित __raw_पढ़ोsl
EXPORT_SYMBOL(__raw_पढ़ोsl);
#पूर्ण_अगर
#अगर_अघोषित __raw_ग_लिखोsb
EXPORT_SYMBOL(__raw_ग_लिखोsb);
#पूर्ण_अगर
#अगर_अघोषित __raw_ग_लिखोsw
EXPORT_SYMBOL(__raw_ग_लिखोsw);
#पूर्ण_अगर
#अगर_अघोषित __raw_ग_लिखोsl
EXPORT_SYMBOL(__raw_ग_लिखोsl);
#पूर्ण_अगर

	/* string / mem functions */
EXPORT_SYMBOL(म_अक्षर);
EXPORT_SYMBOL(म_खोजप);
EXPORT_SYMBOL(स_रखो);
EXPORT_SYMBOL(__स_रखो32);
EXPORT_SYMBOL(__स_रखो64);
EXPORT_SYMBOL(स_नकल);
EXPORT_SYMBOL(स_हटाओ);
EXPORT_SYMBOL(स_प्रथम);

EXPORT_SYMBOL(mmioset);
EXPORT_SYMBOL(mmiocpy);

#अगर_घोषित CONFIG_MMU
EXPORT_SYMBOL(copy_page);

EXPORT_SYMBOL(arm_copy_from_user);
EXPORT_SYMBOL(arm_copy_to_user);
EXPORT_SYMBOL(arm_clear_user);

EXPORT_SYMBOL(__get_user_1);
EXPORT_SYMBOL(__get_user_2);
EXPORT_SYMBOL(__get_user_4);
EXPORT_SYMBOL(__get_user_8);

#अगर_घोषित __ARMEB__
EXPORT_SYMBOL(__get_user_64t_1);
EXPORT_SYMBOL(__get_user_64t_2);
EXPORT_SYMBOL(__get_user_64t_4);
EXPORT_SYMBOL(__get_user_32t_8);
#पूर्ण_अगर

EXPORT_SYMBOL(__put_user_1);
EXPORT_SYMBOL(__put_user_2);
EXPORT_SYMBOL(__put_user_4);
EXPORT_SYMBOL(__put_user_8);
#पूर्ण_अगर

	/* gcc lib functions */
EXPORT_SYMBOL(__ashldi3);
EXPORT_SYMBOL(__ashrdi3);
EXPORT_SYMBOL(__भागsi3);
EXPORT_SYMBOL(__lshrdi3);
EXPORT_SYMBOL(__modsi3);
EXPORT_SYMBOL(__muldi3);
EXPORT_SYMBOL(__ucmpdi2);
EXPORT_SYMBOL(__uभागsi3);
EXPORT_SYMBOL(__umodsi3);
EXPORT_SYMBOL(__करो_भाग64);
EXPORT_SYMBOL(__bswapsi2);
EXPORT_SYMBOL(__bswapdi2);

#अगर_घोषित CONFIG_AEABI
EXPORT_SYMBOL(__aeabi_iभाग);
EXPORT_SYMBOL(__aeabi_iभागmod);
EXPORT_SYMBOL(__aeabi_lasr);
EXPORT_SYMBOL(__aeabi_llsl);
EXPORT_SYMBOL(__aeabi_llsr);
EXPORT_SYMBOL(__aeabi_lmul);
EXPORT_SYMBOL(__aeabi_uiभाग);
EXPORT_SYMBOL(__aeabi_uiभागmod);
EXPORT_SYMBOL(__aeabi_ulcmp);
#पूर्ण_अगर

	/* bitops */
EXPORT_SYMBOL(_set_bit);
EXPORT_SYMBOL(_test_and_set_bit);
EXPORT_SYMBOL(_clear_bit);
EXPORT_SYMBOL(_test_and_clear_bit);
EXPORT_SYMBOL(_change_bit);
EXPORT_SYMBOL(_test_and_change_bit);
EXPORT_SYMBOL(_find_first_zero_bit_le);
EXPORT_SYMBOL(_find_next_zero_bit_le);
EXPORT_SYMBOL(_find_first_bit_le);
EXPORT_SYMBOL(_find_next_bit_le);

#अगर_घोषित __ARMEB__
EXPORT_SYMBOL(_find_first_zero_bit_be);
EXPORT_SYMBOL(_find_next_zero_bit_be);
EXPORT_SYMBOL(_find_first_bit_be);
EXPORT_SYMBOL(_find_next_bit_be);
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_TRACER
EXPORT_SYMBOL(__gnu_mcount_nc);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM_PATCH_PHYS_VIRT
EXPORT_SYMBOL(__pv_phys_pfn_offset);
EXPORT_SYMBOL(__pv_offset);
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_ARM_SMCCC
EXPORT_SYMBOL(__arm_smccc_smc);
EXPORT_SYMBOL(__arm_smccc_hvc);
#पूर्ण_अगर
