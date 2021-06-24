<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

#अगर_अघोषित _RISCV_KERNEL_PROBES_SIMULATE_INSN_H
#घोषणा _RISCV_KERNEL_PROBES_SIMULATE_INSN_H

#घोषणा __RISCV_INSN_FUNCS(name, mask, val)				\
अटल __always_अंतरभूत bool riscv_insn_is_##name(probe_opcode_t code)	\
अणु									\
	BUILD_BUG_ON(~(mask) & (val));					\
	वापस (code & (mask)) == (val);				\
पूर्ण									\
bool simulate_##name(u32 opcode, अचिन्हित दीर्घ addr,			\
		     काष्ठा pt_regs *regs)

#घोषणा RISCV_INSN_REJECTED(name, code)					\
	करो अणु								\
		अगर (riscv_insn_is_##name(code)) अणु			\
			वापस INSN_REJECTED;				\
		पूर्ण							\
	पूर्ण जबतक (0)

__RISCV_INSN_FUNCS(प्रणाली,	0x7f, 0x73);
__RISCV_INSN_FUNCS(fence,	0x7f, 0x0f);

#घोषणा RISCV_INSN_SET_SIMULATE(name, code)				\
	करो अणु								\
		अगर (riscv_insn_is_##name(code)) अणु			\
			api->handler = simulate_##name;			\
			वापस INSN_GOOD_NO_SLOT;			\
		पूर्ण							\
	पूर्ण जबतक (0)

__RISCV_INSN_FUNCS(c_j,		0xe003, 0xa001);
__RISCV_INSN_FUNCS(c_jr,	0xf007, 0x8002);
__RISCV_INSN_FUNCS(c_jal,	0xe003, 0x2001);
__RISCV_INSN_FUNCS(c_jalr,	0xf007, 0x9002);
__RISCV_INSN_FUNCS(c_beqz,	0xe003, 0xc001);
__RISCV_INSN_FUNCS(c_bnez,	0xe003, 0xe001);
__RISCV_INSN_FUNCS(c_eअवरोध,	0xffff, 0x9002);

__RISCV_INSN_FUNCS(auipc,	0x7f, 0x17);
__RISCV_INSN_FUNCS(branch,	0x7f, 0x63);

__RISCV_INSN_FUNCS(jal,		0x7f, 0x6f);
__RISCV_INSN_FUNCS(jalr,	0x707f, 0x67);

#पूर्ण_अगर /* _RISCV_KERNEL_PROBES_SIMULATE_INSN_H */
