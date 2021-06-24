<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

#अगर_अघोषित __CSKY_KERNEL_PROBES_SIMULATE_INSN_H
#घोषणा __CSKY_KERNEL_PROBES_SIMULATE_INSN_H

#घोषणा __CSKY_INSN_FUNCS(name, mask, val)				\
अटल __always_अंतरभूत bool csky_insn_is_##name(probe_opcode_t code)	\
अणु									\
	BUILD_BUG_ON(~(mask) & (val));					\
	वापस (code & (mask)) == (val);				\
पूर्ण									\
व्योम simulate_##name(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs);

#घोषणा CSKY_INSN_SET_SIMULATE(name, code)				\
	करो अणु								\
		अगर (csky_insn_is_##name(code)) अणु			\
			api->handler = simulate_##name;			\
			वापस INSN_GOOD_NO_SLOT;			\
		पूर्ण							\
	पूर्ण जबतक (0)

__CSKY_INSN_FUNCS(br16,		0xfc00, 0x0400)
__CSKY_INSN_FUNCS(bt16,		0xfc00, 0x0800)
__CSKY_INSN_FUNCS(bf16,		0xfc00, 0x0c00)
__CSKY_INSN_FUNCS(jmp16,	0xffc3, 0x7800)
__CSKY_INSN_FUNCS(jsr16,	0xffc3, 0x7801)
__CSKY_INSN_FUNCS(lrw16,	0xfc00, 0x1000)
__CSKY_INSN_FUNCS(pop16,	0xffe0, 0x1480)

__CSKY_INSN_FUNCS(br32,		0x0000ffff, 0x0000e800)
__CSKY_INSN_FUNCS(bt32,		0x0000ffff, 0x0000e860)
__CSKY_INSN_FUNCS(bf32,		0x0000ffff, 0x0000e840)
__CSKY_INSN_FUNCS(jmp32,	0xffffffe0, 0x0000e8c0)
__CSKY_INSN_FUNCS(jsr32,	0xffffffe0, 0x0000e8e0)
__CSKY_INSN_FUNCS(lrw32,	0x0000ffe0, 0x0000ea80)
__CSKY_INSN_FUNCS(pop32,	0xfe00ffff, 0x0000ebc0)

__CSKY_INSN_FUNCS(bez32,	0x0000ffe0, 0x0000e900)
__CSKY_INSN_FUNCS(bnez32,	0x0000ffe0, 0x0000e920)
__CSKY_INSN_FUNCS(bnezad32,	0x0000ffe0, 0x0000e820)
__CSKY_INSN_FUNCS(bhsz32,	0x0000ffe0, 0x0000e9a0)
__CSKY_INSN_FUNCS(bhz32,	0x0000ffe0, 0x0000e940)
__CSKY_INSN_FUNCS(blsz32,	0x0000ffe0, 0x0000e960)
__CSKY_INSN_FUNCS(blz32,	0x0000ffe0, 0x0000e980)
__CSKY_INSN_FUNCS(bsr32,	0x0000fc00, 0x0000e000)
__CSKY_INSN_FUNCS(jmpi32,	0x0000ffff, 0x0000eac0)
__CSKY_INSN_FUNCS(jsri32,	0x0000ffff, 0x0000eae0)

#पूर्ण_अगर /* __CSKY_KERNEL_PROBES_SIMULATE_INSN_H */
