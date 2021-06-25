<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Cadence Design Systems Inc.

#समावेश <linux/cpu.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memory.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/cacheflush.h>

#घोषणा J_OFFSET_MASK 0x0003ffff
#घोषणा J_SIGN_MASK (~(J_OFFSET_MASK >> 1))

#अगर defined(__XTENSA_EL__)
#घोषणा J_INSN 0x6
#घोषणा NOP_INSN 0x0020f0
#या_अगर defined(__XTENSA_EB__)
#घोषणा J_INSN 0x60000000
#घोषणा NOP_INSN 0x0f020000
#अन्यथा
#त्रुटि Unsupported endianness.
#पूर्ण_अगर

काष्ठा patch अणु
	atomic_t cpu_count;
	अचिन्हित दीर्घ addr;
	माप_प्रकार sz;
	स्थिर व्योम *data;
पूर्ण;

अटल व्योम local_patch_text(अचिन्हित दीर्घ addr, स्थिर व्योम *data, माप_प्रकार sz)
अणु
	स_नकल((व्योम *)addr, data, sz);
	local_flush_icache_range(addr, addr + sz);
पूर्ण

अटल पूर्णांक patch_text_stop_machine(व्योम *data)
अणु
	काष्ठा patch *patch = data;

	अगर (atomic_inc_वापस(&patch->cpu_count) == 1) अणु
		local_patch_text(patch->addr, patch->data, patch->sz);
		atomic_inc(&patch->cpu_count);
	पूर्ण अन्यथा अणु
		जबतक (atomic_पढ़ो(&patch->cpu_count) <= num_online_cpus())
			cpu_relax();
		__invalidate_icache_range(patch->addr, patch->sz);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम patch_text(अचिन्हित दीर्घ addr, स्थिर व्योम *data, माप_प्रकार sz)
अणु
	अगर (IS_ENABLED(CONFIG_SMP)) अणु
		काष्ठा patch patch = अणु
			.cpu_count = ATOMIC_INIT(0),
			.addr = addr,
			.sz = sz,
			.data = data,
		पूर्ण;
		stop_machine_cpuslocked(patch_text_stop_machine,
					&patch, शून्य);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		local_patch_text(addr, data, sz);
		local_irq_restore(flags);
	पूर्ण
पूर्ण

व्योम arch_jump_label_transक्रमm(काष्ठा jump_entry *e,
			       क्रमागत jump_label_type type)
अणु
	u32 d = (jump_entry_target(e) - (jump_entry_code(e) + 4));
	u32 insn;

	/* Jump only works within 128K of the J inकाष्ठाion. */
	BUG_ON(!((d & J_SIGN_MASK) == 0 ||
		 (d & J_SIGN_MASK) == J_SIGN_MASK));

	अगर (type == JUMP_LABEL_JMP) अणु
#अगर defined(__XTENSA_EL__)
		insn = ((d & J_OFFSET_MASK) << 6) | J_INSN;
#या_अगर defined(__XTENSA_EB__)
		insn = ((d & J_OFFSET_MASK) << 8) | J_INSN;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		insn = NOP_INSN;
	पूर्ण

	patch_text(jump_entry_code(e), &insn, JUMP_LABEL_NOP_SIZE);
पूर्ण
