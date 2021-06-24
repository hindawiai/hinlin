<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm64/kernel/probes/decode-insn.c
 *
 * Copyright (C) 2013 Linaro Limited.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/module.h>
#समावेश <linux/kallsyms.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/sections.h>

#समावेश "decode-insn.h"
#समावेश "simulate-insn.h"

अटल bool __kprobes aarch64_insn_is_steppable(u32 insn)
अणु
	/*
	 * Branch inकाष्ठाions will ग_लिखो a new value पूर्णांकo the PC which is
	 * likely to be relative to the XOL address and thereक्रमe invalid.
	 * Deliberate generation of an exception during stepping is also not
	 * currently safe. Lastly, MSR inकाष्ठाions can करो any number of nasty
	 * things we can't handle during single-stepping.
	 */
	अगर (aarch64_get_insn_class(insn) == AARCH64_INSN_CLS_BR_SYS) अणु
		अगर (aarch64_insn_is_branch(insn) ||
		    aarch64_insn_is_msr_imm(insn) ||
		    aarch64_insn_is_msr_reg(insn) ||
		    aarch64_insn_is_exception(insn) ||
		    aarch64_insn_is_eret(insn) ||
		    aarch64_insn_is_eret_auth(insn))
			वापस false;

		/*
		 * The MRS inकाष्ठाion may not वापस a correct value when
		 * executing in the single-stepping environment. We करो make one
		 * exception, क्रम पढ़ोing the DAIF bits.
		 */
		अगर (aarch64_insn_is_mrs(insn))
			वापस aarch64_insn_extract_प्रणाली_reg(insn)
			     != AARCH64_INSN_SPCLREG_DAIF;

		/*
		 * The HINT inकाष्ठाion is steppable only अगर it is in whitelist
		 * and the rest of other such inकाष्ठाions are blocked क्रम
		 * single stepping as they may cause exception or other
		 * unपूर्णांकended behaviour.
		 */
		अगर (aarch64_insn_is_hपूर्णांक(insn))
			वापस aarch64_insn_is_steppable_hपूर्णांक(insn);

		वापस true;
	पूर्ण

	/*
	 * Inकाष्ठाions which load PC relative literals are not going to work
	 * when executed from an XOL slot. Inकाष्ठाions करोing an exclusive
	 * load/store are not going to complete successfully when single-step
	 * exception handling happens in the middle of the sequence.
	 */
	अगर (aarch64_insn_uses_literal(insn) ||
	    aarch64_insn_is_exclusive(insn))
		वापस false;

	वापस true;
पूर्ण

/* Return:
 *   INSN_REJECTED     If inकाष्ठाion is one not allowed to kprobe,
 *   INSN_GOOD         If inकाष्ठाion is supported and uses inकाष्ठाion slot,
 *   INSN_GOOD_NO_SLOT If inकाष्ठाion is supported but करोesn't use its slot.
 */
क्रमागत probe_insn __kprobes
arm_probe_decode_insn(probe_opcode_t insn, काष्ठा arch_probe_insn *api)
अणु
	/*
	 * Inकाष्ठाions पढ़ोing or modअगरying the PC won't work from the XOL
	 * slot.
	 */
	अगर (aarch64_insn_is_steppable(insn))
		वापस INSN_GOOD;

	अगर (aarch64_insn_is_bcond(insn)) अणु
		api->handler = simulate_b_cond;
	पूर्ण अन्यथा अगर (aarch64_insn_is_cbz(insn) ||
	    aarch64_insn_is_cbnz(insn)) अणु
		api->handler = simulate_cbz_cbnz;
	पूर्ण अन्यथा अगर (aarch64_insn_is_tbz(insn) ||
	    aarch64_insn_is_tbnz(insn)) अणु
		api->handler = simulate_tbz_tbnz;
	पूर्ण अन्यथा अगर (aarch64_insn_is_adr_adrp(insn)) अणु
		api->handler = simulate_adr_adrp;
	पूर्ण अन्यथा अगर (aarch64_insn_is_b(insn) ||
	    aarch64_insn_is_bl(insn)) अणु
		api->handler = simulate_b_bl;
	पूर्ण अन्यथा अगर (aarch64_insn_is_br(insn) ||
	    aarch64_insn_is_blr(insn) ||
	    aarch64_insn_is_ret(insn)) अणु
		api->handler = simulate_br_blr_ret;
	पूर्ण अन्यथा अगर (aarch64_insn_is_ldr_lit(insn)) अणु
		api->handler = simulate_ldr_literal;
	पूर्ण अन्यथा अगर (aarch64_insn_is_ldrsw_lit(insn)) अणु
		api->handler = simulate_ldrsw_literal;
	पूर्ण अन्यथा अणु
		/*
		 * Inकाष्ठाion cannot be stepped out-of-line and we करोn't
		 * (yet) simulate it.
		 */
		वापस INSN_REJECTED;
	पूर्ण

	वापस INSN_GOOD_NO_SLOT;
पूर्ण

#अगर_घोषित CONFIG_KPROBES
अटल bool __kprobes
is_probed_address_atomic(kprobe_opcode_t *scan_start, kprobe_opcode_t *scan_end)
अणु
	जबतक (scan_start >= scan_end) अणु
		/*
		 * atomic region starts from exclusive load and ends with
		 * exclusive store.
		 */
		अगर (aarch64_insn_is_store_ex(le32_to_cpu(*scan_start)))
			वापस false;
		अन्यथा अगर (aarch64_insn_is_load_ex(le32_to_cpu(*scan_start)))
			वापस true;
		scan_start--;
	पूर्ण

	वापस false;
पूर्ण

क्रमागत probe_insn __kprobes
arm_kprobe_decode_insn(kprobe_opcode_t *addr, काष्ठा arch_specअगरic_insn *asi)
अणु
	क्रमागत probe_insn decoded;
	probe_opcode_t insn = le32_to_cpu(*addr);
	probe_opcode_t *scan_end = शून्य;
	अचिन्हित दीर्घ size = 0, offset = 0;

	/*
	 * If there's a symbol defined in front of and near enough to
	 * the probe address assume it is the entry poपूर्णांक to this
	 * code and use it to further limit how far back we search
	 * when determining अगर we're in an atomic sequence. If we could
	 * not find any symbol skip the atomic test altogether as we
	 * could otherwise end up searching irrelevant text/literals.
	 * KPROBES depends on KALLSYMS so this last हाल should never
	 * happen.
	 */
	अगर (kallsyms_lookup_size_offset((अचिन्हित दीर्घ) addr, &size, &offset)) अणु
		अगर (offset < (MAX_ATOMIC_CONTEXT_SIZE*माप(kprobe_opcode_t)))
			scan_end = addr - (offset / माप(kprobe_opcode_t));
		अन्यथा
			scan_end = addr - MAX_ATOMIC_CONTEXT_SIZE;
	पूर्ण
	decoded = arm_probe_decode_insn(insn, &asi->api);

	अगर (decoded != INSN_REJECTED && scan_end)
		अगर (is_probed_address_atomic(addr - 1, scan_end))
			वापस INSN_REJECTED;

	वापस decoded;
पूर्ण
#पूर्ण_अगर
