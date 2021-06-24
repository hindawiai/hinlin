<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_RISCV_PROBES_H
#घोषणा _ASM_RISCV_PROBES_H

प्रकार u32 probe_opcode_t;
प्रकार bool (probes_handler_t) (u32 opcode, अचिन्हित दीर्घ addr, काष्ठा pt_regs *);

/* architecture specअगरic copy of original inकाष्ठाion */
काष्ठा arch_probe_insn अणु
	probe_opcode_t *insn;
	probes_handler_t *handler;
	/* restore address after simulation */
	अचिन्हित दीर्घ restore;
पूर्ण;

#अगर_घोषित CONFIG_KPROBES
प्रकार u32 kprobe_opcode_t;
काष्ठा arch_specअगरic_insn अणु
	काष्ठा arch_probe_insn api;
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_RISCV_PROBES_H */
