<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ARC_KPROBES_H
#घोषणा _ARC_KPROBES_H

#समावेश <यंत्र-generic/kprobes.h>

#अगर_घोषित CONFIG_KPROBES

प्रकार u16 kprobe_opcode_t;

#घोषणा UNIMP_S_INSTRUCTION 0x79e0
#घोषणा TRAP_S_2_INSTRUCTION 0x785e

#घोषणा MAX_INSN_SIZE   8
#घोषणा MAX_STACK_SIZE  64

काष्ठा arch_specअगरic_insn अणु
	पूर्णांक is_लघु;
	kprobe_opcode_t *t1_addr, *t2_addr;
	kprobe_opcode_t t1_opcode, t2_opcode;
पूर्ण;

#घोषणा flush_insn_slot(p)  करो अणु  पूर्ण जबतक (0)

#घोषणा kretprobe_blacklist_size    0

काष्ठा kprobe;

व्योम arch_हटाओ_kprobe(काष्ठा kprobe *p);

पूर्णांक kprobe_exceptions_notअगरy(काष्ठा notअगरier_block *self,
			     अचिन्हित दीर्घ val, व्योम *data);

काष्ठा prev_kprobe अणु
	काष्ठा kprobe *kp;
	अचिन्हित दीर्घ status;
पूर्ण;

काष्ठा kprobe_ctlblk अणु
	अचिन्हित पूर्णांक kprobe_status;
	काष्ठा prev_kprobe prev_kprobe;
पूर्ण;

पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, अचिन्हित दीर्घ cause);
व्योम kretprobe_trampoline(व्योम);
व्योम trap_is_kprobe(अचिन्हित दीर्घ address, काष्ठा pt_regs *regs);
#अन्यथा
#घोषणा trap_is_kprobe(address, regs)
#पूर्ण_अगर /* CONFIG_KPROBES */

#पूर्ण_अगर /* _ARC_KPROBES_H */
