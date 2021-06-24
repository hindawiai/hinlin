<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * jump label x86 support
 *
 * Copyright (C) 2009 Jason Baron <jbaron@redhat.com>
 *
 */
#समावेश <linux/jump_label.h>
#समावेश <linux/memory.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/jhash.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/text-patching.h>

अटल व्योम bug_at(स्थिर व्योम *ip, पूर्णांक line)
अणु
	/*
	 * The location is not an op that we were expecting.
	 * Something went wrong. Crash the box, as something could be
	 * corrupting the kernel.
	 */
	pr_crit("jump_label: Fatal kernel bug, unexpected op at %pS [%p] (%5ph) %d\n", ip, ip, ip, line);
	BUG();
पूर्ण

अटल स्थिर व्योम *
__jump_label_set_jump_code(काष्ठा jump_entry *entry, क्रमागत jump_label_type type)
अणु
	स्थिर व्योम *expect, *code;
	स्थिर व्योम *addr, *dest;
	पूर्णांक line;

	addr = (व्योम *)jump_entry_code(entry);
	dest = (व्योम *)jump_entry_target(entry);

	code = text_gen_insn(JMP32_INSN_OPCODE, addr, dest);

	अगर (type == JUMP_LABEL_JMP) अणु
		expect = x86_nops[5]; line = __LINE__;
	पूर्ण अन्यथा अणु
		expect = code; line = __LINE__;
	पूर्ण

	अगर (स_भेद(addr, expect, JUMP_LABEL_NOP_SIZE))
		bug_at(addr, line);

	अगर (type == JUMP_LABEL_NOP)
		code = x86_nops[5];

	वापस code;
पूर्ण

अटल अंतरभूत व्योम __jump_label_transक्रमm(काष्ठा jump_entry *entry,
					  क्रमागत jump_label_type type,
					  पूर्णांक init)
अणु
	स्थिर व्योम *opcode = __jump_label_set_jump_code(entry, type);

	/*
	 * As दीर्घ as only a single processor is running and the code is still
	 * not marked as RO, text_poke_early() can be used; Checking that
	 * प्रणाली_state is SYSTEM_BOOTING guarantees it. It will be set to
	 * SYSTEM_SCHEDULING beक्रमe other cores are awaken and beक्रमe the
	 * code is ग_लिखो-रक्षित.
	 *
	 * At the समय the change is being करोne, just ignore whether we
	 * are करोing nop -> jump or jump -> nop transition, and assume
	 * always nop being the 'currently valid' inकाष्ठाion
	 */
	अगर (init || प्रणाली_state == SYSTEM_BOOTING) अणु
		text_poke_early((व्योम *)jump_entry_code(entry), opcode,
				JUMP_LABEL_NOP_SIZE);
		वापस;
	पूर्ण

	text_poke_bp((व्योम *)jump_entry_code(entry), opcode, JUMP_LABEL_NOP_SIZE, शून्य);
पूर्ण

अटल व्योम __ref jump_label_transक्रमm(काष्ठा jump_entry *entry,
				       क्रमागत jump_label_type type,
				       पूर्णांक init)
अणु
	mutex_lock(&text_mutex);
	__jump_label_transक्रमm(entry, type, init);
	mutex_unlock(&text_mutex);
पूर्ण

व्योम arch_jump_label_transक्रमm(काष्ठा jump_entry *entry,
			       क्रमागत jump_label_type type)
अणु
	jump_label_transक्रमm(entry, type, 0);
पूर्ण

bool arch_jump_label_transक्रमm_queue(काष्ठा jump_entry *entry,
				     क्रमागत jump_label_type type)
अणु
	स्थिर व्योम *opcode;

	अगर (प्रणाली_state == SYSTEM_BOOTING) अणु
		/*
		 * Fallback to the non-batching mode.
		 */
		arch_jump_label_transक्रमm(entry, type);
		वापस true;
	पूर्ण

	mutex_lock(&text_mutex);
	opcode = __jump_label_set_jump_code(entry, type);
	text_poke_queue((व्योम *)jump_entry_code(entry),
			opcode, JUMP_LABEL_NOP_SIZE, शून्य);
	mutex_unlock(&text_mutex);
	वापस true;
पूर्ण

व्योम arch_jump_label_transक्रमm_apply(व्योम)
अणु
	mutex_lock(&text_mutex);
	text_poke_finish();
	mutex_unlock(&text_mutex);
पूर्ण

अटल क्रमागत अणु
	JL_STATE_START,
	JL_STATE_NO_UPDATE,
	JL_STATE_UPDATE,
पूर्ण jlstate __initdata_or_module = JL_STATE_START;

__init_or_module व्योम arch_jump_label_transक्रमm_अटल(काष्ठा jump_entry *entry,
				      क्रमागत jump_label_type type)
अणु
	अगर (jlstate == JL_STATE_UPDATE)
		jump_label_transक्रमm(entry, type, 1);
पूर्ण
