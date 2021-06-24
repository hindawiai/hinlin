<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/nospec-branch.h>

#घोषणा MAX_PATCH_LEN (255 - 1)

अटल पूर्णांक __initdata_or_module alt_instr_disabled;

अटल पूर्णांक __init disable_alternative_inकाष्ठाions(अक्षर *str)
अणु
	alt_instr_disabled = 1;
	वापस 0;
पूर्ण

early_param("noaltinstr", disable_alternative_inकाष्ठाions);

काष्ठा brcl_insn अणु
	u16 opc;
	s32 disp;
पूर्ण __packed;

अटल u16 __initdata_or_module nop16 = 0x0700;
अटल u32 __initdata_or_module nop32 = 0x47000000;
अटल काष्ठा brcl_insn __initdata_or_module nop48 = अणु
	0xc004, 0
पूर्ण;

अटल स्थिर व्योम *nops[] __initdata_or_module = अणु
	&nop16,
	&nop32,
	&nop48
पूर्ण;

अटल व्योम __init_or_module add_jump_padding(व्योम *insns, अचिन्हित पूर्णांक len)
अणु
	काष्ठा brcl_insn brcl = अणु
		0xc0f4,
		len / 2
	पूर्ण;

	स_नकल(insns, &brcl, माप(brcl));
	insns += माप(brcl);
	len -= माप(brcl);

	जबतक (len > 0) अणु
		स_नकल(insns, &nop16, 2);
		insns += 2;
		len -= 2;
	पूर्ण
पूर्ण

अटल व्योम __init_or_module add_padding(व्योम *insns, अचिन्हित पूर्णांक len)
अणु
	अगर (len > 6)
		add_jump_padding(insns, len);
	अन्यथा अगर (len >= 2)
		स_नकल(insns, nops[len / 2 - 1], len);
पूर्ण

अटल व्योम __init_or_module __apply_alternatives(काष्ठा alt_instr *start,
						  काष्ठा alt_instr *end)
अणु
	काष्ठा alt_instr *a;
	u8 *instr, *replacement;
	u8 insnbuf[MAX_PATCH_LEN];

	/*
	 * The scan order should be from start to end. A later scanned
	 * alternative code can overग_लिखो previously scanned alternative code.
	 */
	क्रम (a = start; a < end; a++) अणु
		पूर्णांक insnbuf_sz = 0;

		instr = (u8 *)&a->instr_offset + a->instr_offset;
		replacement = (u8 *)&a->repl_offset + a->repl_offset;

		अगर (!__test_facility(a->facility,
				     S390_lowcore.alt_stfle_fac_list))
			जारी;

		अगर (unlikely(a->inम_माप % 2 || a->replacementlen % 2)) अणु
			WARN_ONCE(1, "cpu alternatives instructions length is "
				     "odd, skipping patching\n");
			जारी;
		पूर्ण

		स_नकल(insnbuf, replacement, a->replacementlen);
		insnbuf_sz = a->replacementlen;

		अगर (a->inम_माप > a->replacementlen) अणु
			add_padding(insnbuf + a->replacementlen,
				    a->inम_माप - a->replacementlen);
			insnbuf_sz += a->inम_माप - a->replacementlen;
		पूर्ण

		s390_kernel_ग_लिखो(instr, insnbuf, insnbuf_sz);
	पूर्ण
पूर्ण

व्योम __init_or_module apply_alternatives(काष्ठा alt_instr *start,
					 काष्ठा alt_instr *end)
अणु
	अगर (!alt_instr_disabled)
		__apply_alternatives(start, end);
पूर्ण

बाह्य काष्ठा alt_instr __alt_inकाष्ठाions[], __alt_inकाष्ठाions_end[];
व्योम __init apply_alternative_inकाष्ठाions(व्योम)
अणु
	apply_alternatives(__alt_inकाष्ठाions, __alt_inकाष्ठाions_end);
पूर्ण
