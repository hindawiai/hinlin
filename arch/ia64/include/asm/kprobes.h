<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_KPROBES_H
#घोषणा _ASM_KPROBES_H
/*
 *  Kernel Probes (KProbes)
 *
 * Copyright (C) IBM Corporation, 2002, 2004
 * Copyright (C) Intel Corporation, 2005
 *
 * 2005-Apr     Rusty Lynch <rusty.lynch@पूर्णांकel.com> and Anil S Keshavamurthy
 *              <anil.s.keshavamurthy@पूर्णांकel.com> adapted from i386
 */
#समावेश <यंत्र-generic/kprobes.h>
#समावेश <यंत्र/अवरोध.h>

#घोषणा BREAK_INST	(दीर्घ)(__IA64_BREAK_KPROBE << 6)

#अगर_घोषित CONFIG_KPROBES

#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/percpu.h>

#घोषणा __ARCH_WANT_KPROBES_INSN_SLOT
#घोषणा MAX_INSN_SIZE   2	/* last half is क्रम kprobe-booster */
#घोषणा NOP_M_INST	(दीर्घ)(1<<27)
#घोषणा BRL_INST(i1, i2) ((दीर्घ)((0xcL << 37) |	/* brl */ \
				(0x1L << 12) |	/* many */ \
				(((i1) & 1) << 36) | ((i2) << 13))) /* imm */

प्रकार जोड़ cmp_inst अणु
	काष्ठा अणु
	अचिन्हित दीर्घ दीर्घ qp : 6;
	अचिन्हित दीर्घ दीर्घ p1 : 6;
	अचिन्हित दीर्घ दीर्घ c  : 1;
	अचिन्हित दीर्घ दीर्घ r2 : 7;
	अचिन्हित दीर्घ दीर्घ r3 : 7;
	अचिन्हित दीर्घ दीर्घ p2 : 6;
	अचिन्हित दीर्घ दीर्घ ta : 1;
	अचिन्हित दीर्घ दीर्घ x2 : 2;
	अचिन्हित दीर्घ दीर्घ tb : 1;
	अचिन्हित दीर्घ दीर्घ opcode : 4;
	अचिन्हित दीर्घ दीर्घ reserved : 23;
	पूर्णf;
	अचिन्हित दीर्घ दीर्घ l;
पूर्ण cmp_inst_t;

काष्ठा kprobe;

प्रकार काष्ठा _bundle अणु
	काष्ठा अणु
		अचिन्हित दीर्घ दीर्घ ढाँचा : 5;
		अचिन्हित दीर्घ दीर्घ slot0 : 41;
		अचिन्हित दीर्घ दीर्घ slot1_p0 : 64-46;
	पूर्ण quad0;
	काष्ठा अणु
		अचिन्हित दीर्घ दीर्घ slot1_p1 : 41 - (64-46);
		अचिन्हित दीर्घ दीर्घ slot2 : 41;
	पूर्ण quad1;
पूर्ण __attribute__((__aligned__(16)))  bundle_t;

काष्ठा prev_kprobe अणु
	काष्ठा kprobe *kp;
	अचिन्हित दीर्घ status;
पूर्ण;

#घोषणा	MAX_PARAM_RSE_SIZE	(0x60+0x60/0x3f)
/* per-cpu kprobe control block */
#घोषणा ARCH_PREV_KPROBE_SZ 2
काष्ठा kprobe_ctlblk अणु
	अचिन्हित दीर्घ kprobe_status;
	अचिन्हित दीर्घ *bsp;
	अचिन्हित दीर्घ cfm;
	atomic_t prev_kprobe_index;
	काष्ठा prev_kprobe prev_kprobe[ARCH_PREV_KPROBE_SZ];
पूर्ण;

#घोषणा kretprobe_blacklist_size 0

#घोषणा SLOT0_OPCODE_SHIFT	(37)
#घोषणा SLOT1_p1_OPCODE_SHIFT	(37 - (64-46))
#घोषणा SLOT2_OPCODE_SHIFT 	(37)

#घोषणा INसूचीECT_CALL_OPCODE		(1)
#घोषणा IP_RELATIVE_CALL_OPCODE		(5)
#घोषणा IP_RELATIVE_BRANCH_OPCODE	(4)
#घोषणा IP_RELATIVE_PREDICT_OPCODE	(7)
#घोषणा LONG_BRANCH_OPCODE		(0xC)
#घोषणा LONG_CALL_OPCODE		(0xD)
#घोषणा flush_insn_slot(p)		करो अणु पूर्ण जबतक (0)

प्रकार काष्ठा kprobe_opcode अणु
	bundle_t bundle;
पूर्ण kprobe_opcode_t;

/* Architecture specअगरic copy of original inकाष्ठाion*/
काष्ठा arch_specअगरic_insn अणु
	/* copy of the inकाष्ठाion to be emulated */
	kprobe_opcode_t *insn;
 #घोषणा INST_FLAG_FIX_RELATIVE_IP_ADDR		1
 #घोषणा INST_FLAG_FIX_BRANCH_REG		2
 #घोषणा INST_FLAG_BREAK_INST			4
 #घोषणा INST_FLAG_BOOSTABLE			8
 	अचिन्हित दीर्घ inst_flag;
 	अचिन्हित लघु target_br_reg;
	अचिन्हित लघु slot;
पूर्ण;

बाह्य पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr);
बाह्य पूर्णांक kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
				    अचिन्हित दीर्घ val, व्योम *data);

बाह्य व्योम invalidate_stacked_regs(व्योम);
बाह्य व्योम flush_रेजिस्टर_stack(व्योम);
बाह्य व्योम arch_हटाओ_kprobe(काष्ठा kprobe *p);

#पूर्ण_अगर /* CONFIG_KPROBES */
#पूर्ण_अगर /* _ASM_KPROBES_H */
