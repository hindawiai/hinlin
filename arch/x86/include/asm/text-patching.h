<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_TEXT_PATCHING_H
#घोषणा _ASM_X86_TEXT_PATCHING_H

#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <यंत्र/ptrace.h>

काष्ठा paravirt_patch_site;
#अगर_घोषित CONFIG_PARAVIRT
व्योम apply_paravirt(काष्ठा paravirt_patch_site *start,
		    काष्ठा paravirt_patch_site *end);
#अन्यथा
अटल अंतरभूत व्योम apply_paravirt(काष्ठा paravirt_patch_site *start,
				  काष्ठा paravirt_patch_site *end)
अणुपूर्ण
#घोषणा __parainकाष्ठाions	शून्य
#घोषणा __parainकाष्ठाions_end	शून्य
#पूर्ण_अगर

/*
 * Currently, the max observed size in the kernel code is
 * JUMP_LABEL_NOP_SIZE/RELATIVEJUMP_SIZE, which are 5.
 * Raise it अगर needed.
 */
#घोषणा POKE_MAX_OPCODE_SIZE	5

बाह्य व्योम text_poke_early(व्योम *addr, स्थिर व्योम *opcode, माप_प्रकार len);

/*
 * Clear and restore the kernel ग_लिखो-protection flag on the local CPU.
 * Allows the kernel to edit पढ़ो-only pages.
 * Side-effect: any पूर्णांकerrupt handler running between save and restore will have
 * the ability to ग_लिखो to पढ़ो-only pages.
 *
 * Warning:
 * Code patching in the UP हाल is safe अगर NMIs and MCE handlers are stopped and
 * no thपढ़ो can be preempted in the inकाष्ठाions being modअगरied (no iret to an
 * invalid inकाष्ठाion possible) or अगर the inकाष्ठाions are changed from a
 * consistent state to another consistent state atomically.
 * On the local CPU you need to be रक्षित against NMI or MCE handlers seeing
 * an inconsistent inकाष्ठाion जबतक you patch.
 */
बाह्य व्योम *text_poke(व्योम *addr, स्थिर व्योम *opcode, माप_प्रकार len);
बाह्य व्योम text_poke_sync(व्योम);
बाह्य व्योम *text_poke_kgdb(व्योम *addr, स्थिर व्योम *opcode, माप_प्रकार len);
बाह्य पूर्णांक poke_पूर्णांक3_handler(काष्ठा pt_regs *regs);
बाह्य व्योम text_poke_bp(व्योम *addr, स्थिर व्योम *opcode, माप_प्रकार len, स्थिर व्योम *emulate);

बाह्य व्योम text_poke_queue(व्योम *addr, स्थिर व्योम *opcode, माप_प्रकार len, स्थिर व्योम *emulate);
बाह्य व्योम text_poke_finish(व्योम);

#घोषणा INT3_INSN_SIZE		1
#घोषणा INT3_INSN_OPCODE	0xCC

#घोषणा RET_INSN_SIZE		1
#घोषणा RET_INSN_OPCODE		0xC3

#घोषणा CALL_INSN_SIZE		5
#घोषणा CALL_INSN_OPCODE	0xE8

#घोषणा JMP32_INSN_SIZE		5
#घोषणा JMP32_INSN_OPCODE	0xE9

#घोषणा JMP8_INSN_SIZE		2
#घोषणा JMP8_INSN_OPCODE	0xEB

#घोषणा DISP32_SIZE		4

अटल __always_अंतरभूत पूर्णांक text_opcode_size(u8 opcode)
अणु
	पूर्णांक size = 0;

#घोषणा __CASE(insn)	\
	हाल insn##_INSN_OPCODE: size = insn##_INSN_SIZE; अवरोध

	चयन(opcode) अणु
	__CASE(INT3);
	__CASE(RET);
	__CASE(CALL);
	__CASE(JMP32);
	__CASE(JMP8);
	पूर्ण

#अघोषित __CASE

	वापस size;
पूर्ण

जोड़ text_poke_insn अणु
	u8 text[POKE_MAX_OPCODE_SIZE];
	काष्ठा अणु
		u8 opcode;
		s32 disp;
	पूर्ण __attribute__((packed));
पूर्ण;

अटल __always_अंतरभूत
व्योम *text_gen_insn(u8 opcode, स्थिर व्योम *addr, स्थिर व्योम *dest)
अणु
	अटल जोड़ text_poke_insn insn; /* per instance */
	पूर्णांक size = text_opcode_size(opcode);

	insn.opcode = opcode;

	अगर (size > 1) अणु
		insn.disp = (दीर्घ)dest - (दीर्घ)(addr + size);
		अगर (size == 2) अणु
			/*
			 * Ensure that क्रम JMP9 the displacement
			 * actually fits the चिन्हित byte.
			 */
			BUG_ON((insn.disp >> 31) != (insn.disp >> 7));
		पूर्ण
	पूर्ण

	वापस &insn.text;
पूर्ण

बाह्य पूर्णांक after_booपंचांगem;
बाह्य __ro_after_init काष्ठा mm_काष्ठा *poking_mm;
बाह्य __ro_after_init अचिन्हित दीर्घ poking_addr;

#अगर_अघोषित CONFIG_UML_X86
अटल __always_अंतरभूत
व्योम पूर्णांक3_emulate_jmp(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ip)
अणु
	regs->ip = ip;
पूर्ण

अटल __always_अंतरभूत
व्योम पूर्णांक3_emulate_push(काष्ठा pt_regs *regs, अचिन्हित दीर्घ val)
अणु
	/*
	 * The पूर्णांक3 handler in entry_64.S adds a gap between the
	 * stack where the अवरोध poपूर्णांक happened, and the saving of
	 * pt_regs. We can extend the original stack because of
	 * this gap. See the idtentry macro's create_gap option.
	 *
	 * Similarly entry_32.S will have a gap on the stack क्रम (any) hardware
	 * exception and pt_regs; see FIXUP_FRAME.
	 */
	regs->sp -= माप(अचिन्हित दीर्घ);
	*(अचिन्हित दीर्घ *)regs->sp = val;
पूर्ण

अटल __always_अंतरभूत
अचिन्हित दीर्घ पूर्णांक3_emulate_pop(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ val = *(अचिन्हित दीर्घ *)regs->sp;
	regs->sp += माप(अचिन्हित दीर्घ);
	वापस val;
पूर्ण

अटल __always_अंतरभूत
व्योम पूर्णांक3_emulate_call(काष्ठा pt_regs *regs, अचिन्हित दीर्घ func)
अणु
	पूर्णांक3_emulate_push(regs, regs->ip - INT3_INSN_SIZE + CALL_INSN_SIZE);
	पूर्णांक3_emulate_jmp(regs, func);
पूर्ण

अटल __always_अंतरभूत
व्योम पूर्णांक3_emulate_ret(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ip = पूर्णांक3_emulate_pop(regs);
	पूर्णांक3_emulate_jmp(regs, ip);
पूर्ण
#पूर्ण_अगर /* !CONFIG_UML_X86 */

#पूर्ण_अगर /* _ASM_X86_TEXT_PATCHING_H */
