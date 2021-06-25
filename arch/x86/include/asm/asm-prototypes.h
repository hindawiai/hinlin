<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <यंत्र/ftrace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/माला.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/checksum.h>
#समावेश <यंत्र/mce.h>

#समावेश <यंत्र-generic/यंत्र-prototypes.h>

#समावेश <यंत्र/special_insns.h>
#समावेश <यंत्र/preempt.h>
#समावेश <यंत्र/यंत्र.h>

#अगर_अघोषित CONFIG_X86_CMPXCHG64
बाह्य व्योम cmpxchg8b_emu(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_RETPOLINE

#अघोषित GEN
#घोषणा GEN(reg) \
	बाह्य यंत्रlinkage व्योम __x86_indirect_thunk_ ## reg (व्योम);
#समावेश <यंत्र/GEN-क्रम-each-reg.h>

#अघोषित GEN
#घोषणा GEN(reg) \
	बाह्य यंत्रlinkage व्योम __x86_indirect_alt_call_ ## reg (व्योम);
#समावेश <यंत्र/GEN-क्रम-each-reg.h>

#अघोषित GEN
#घोषणा GEN(reg) \
	बाह्य यंत्रlinkage व्योम __x86_indirect_alt_jmp_ ## reg (व्योम);
#समावेश <यंत्र/GEN-क्रम-each-reg.h>

#पूर्ण_अगर /* CONFIG_RETPOLINE */
