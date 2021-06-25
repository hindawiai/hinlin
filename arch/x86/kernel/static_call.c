<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/अटल_call.h>
#समावेश <linux/memory.h>
#समावेश <linux/bug.h>
#समावेश <यंत्र/text-patching.h>

क्रमागत insn_type अणु
	CALL = 0, /* site call */
	NOP = 1,  /* site cond-call */
	JMP = 2,  /* tramp / site tail-call */
	RET = 3,  /* tramp / site cond-tail-call */
पूर्ण;

/*
 * data16 data16 xorq %rax, %rax - a single 5 byte inकाष्ठाion that clears %rax
 * The REX.W cancels the effect of any data16.
 */
अटल स्थिर u8 xor5rax[] = अणु 0x66, 0x66, 0x48, 0x31, 0xc0 पूर्ण;

अटल व्योम __ref __अटल_call_transक्रमm(व्योम *insn, क्रमागत insn_type type, व्योम *func)
अणु
	स्थिर व्योम *emulate = शून्य;
	पूर्णांक size = CALL_INSN_SIZE;
	स्थिर व्योम *code;

	चयन (type) अणु
	हाल CALL:
		code = text_gen_insn(CALL_INSN_OPCODE, insn, func);
		अगर (func == &__अटल_call_वापस0) अणु
			emulate = code;
			code = &xor5rax;
		पूर्ण

		अवरोध;

	हाल NOP:
		code = x86_nops[5];
		अवरोध;

	हाल JMP:
		code = text_gen_insn(JMP32_INSN_OPCODE, insn, func);
		अवरोध;

	हाल RET:
		code = text_gen_insn(RET_INSN_OPCODE, insn, func);
		size = RET_INSN_SIZE;
		अवरोध;
	पूर्ण

	अगर (स_भेद(insn, code, size) == 0)
		वापस;

	अगर (unlikely(प्रणाली_state == SYSTEM_BOOTING))
		वापस text_poke_early(insn, code, size);

	text_poke_bp(insn, code, size, emulate);
पूर्ण

अटल व्योम __अटल_call_validate(व्योम *insn, bool tail)
अणु
	u8 opcode = *(u8 *)insn;

	अगर (tail) अणु
		अगर (opcode == JMP32_INSN_OPCODE ||
		    opcode == RET_INSN_OPCODE)
			वापस;
	पूर्ण अन्यथा अणु
		अगर (opcode == CALL_INSN_OPCODE ||
		    !स_भेद(insn, x86_nops[5], 5) ||
		    !स_भेद(insn, xor5rax, 5))
			वापस;
	पूर्ण

	/*
	 * If we ever trigger this, our text is corrupt, we'll probably not live दीर्घ.
	 */
	WARN_ONCE(1, "unexpected static_call insn opcode 0x%x at %pS\n", opcode, insn);
पूर्ण

अटल अंतरभूत क्रमागत insn_type __sc_insn(bool null, bool tail)
अणु
	/*
	 * Encode the following table without branches:
	 *
	 *	tail	null	insn
	 *	-----+-------+------
	 *	  0  |   0   |  CALL
	 *	  0  |   1   |  NOP
	 *	  1  |   0   |  JMP
	 *	  1  |   1   |  RET
	 */
	वापस 2*tail + null;
पूर्ण

व्योम arch_अटल_call_transक्रमm(व्योम *site, व्योम *tramp, व्योम *func, bool tail)
अणु
	mutex_lock(&text_mutex);

	अगर (tramp) अणु
		__अटल_call_validate(tramp, true);
		__अटल_call_transक्रमm(tramp, __sc_insn(!func, true), func);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_HAVE_STATIC_CALL_INLINE) && site) अणु
		__अटल_call_validate(site, tail);
		__अटल_call_transक्रमm(site, __sc_insn(!func, tail), func);
	पूर्ण

	mutex_unlock(&text_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(arch_अटल_call_transक्रमm);
