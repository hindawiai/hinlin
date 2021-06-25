<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>

#समावेश "decode-insn.h"
#समावेश "simulate-insn.h"

अटल अंतरभूत bool csky_insn_reg_get_val(काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ index,
					 अचिन्हित दीर्घ *ptr)
अणु
	अगर (index < 14)
		*ptr = *(&regs->a0 + index);

	अगर (index > 15 && index < 31)
		*ptr = *(&regs->exregs[0] + index - 16);

	चयन (index) अणु
	हाल 14:
		*ptr = regs->usp;
		अवरोध;
	हाल 15:
		*ptr = regs->lr;
		अवरोध;
	हाल 31:
		*ptr = regs->tls;
		अवरोध;
	शेष:
		जाओ fail;
	पूर्ण

	वापस true;
fail:
	वापस false;
पूर्ण

अटल अंतरभूत bool csky_insn_reg_set_val(काष्ठा pt_regs *regs,
					 अचिन्हित दीर्घ index,
					 अचिन्हित दीर्घ val)
अणु
	अगर (index < 14)
		*(&regs->a0 + index) = val;

	अगर (index > 15 && index < 31)
		*(&regs->exregs[0] + index - 16) = val;

	चयन (index) अणु
	हाल 14:
		regs->usp = val;
		अवरोध;
	हाल 15:
		regs->lr = val;
		अवरोध;
	हाल 31:
		regs->tls = val;
		अवरोध;
	शेष:
		जाओ fail;
	पूर्ण

	वापस true;
fail:
	वापस false;
पूर्ण

व्योम __kprobes
simulate_br16(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	inकाष्ठाion_poपूर्णांकer_set(regs,
		addr + sign_extend32((opcode & 0x3ff) << 1, 9));
पूर्ण

व्योम __kprobes
simulate_br32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	inकाष्ठाion_poपूर्णांकer_set(regs,
		addr + sign_extend32((opcode & 0xffff0000) >> 15, 15));
पूर्ण

व्योम __kprobes
simulate_bt16(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अगर (regs->sr & 1)
		inकाष्ठाion_poपूर्णांकer_set(regs,
			addr + sign_extend32((opcode & 0x3ff) << 1, 9));
	अन्यथा
		inकाष्ठाion_poपूर्णांकer_set(regs, addr + 2);
पूर्ण

व्योम __kprobes
simulate_bt32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अगर (regs->sr & 1)
		inकाष्ठाion_poपूर्णांकer_set(regs,
			addr + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	अन्यथा
		inकाष्ठाion_poपूर्णांकer_set(regs, addr + 4);
पूर्ण

व्योम __kprobes
simulate_bf16(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अगर (!(regs->sr & 1))
		inकाष्ठाion_poपूर्णांकer_set(regs,
			addr + sign_extend32((opcode & 0x3ff) << 1, 9));
	अन्यथा
		inकाष्ठाion_poपूर्णांकer_set(regs, addr + 2);
पूर्ण

व्योम __kprobes
simulate_bf32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अगर (!(regs->sr & 1))
		inकाष्ठाion_poपूर्णांकer_set(regs,
			addr + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	अन्यथा
		inकाष्ठाion_poपूर्णांकer_set(regs, addr + 4);
पूर्ण

व्योम __kprobes
simulate_jmp16(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ पंचांगp = (opcode >> 2) & 0xf;

	csky_insn_reg_get_val(regs, पंचांगp, &पंचांगp);

	inकाष्ठाion_poपूर्णांकer_set(regs, पंचांगp & 0xfffffffe);
पूर्ण

व्योम __kprobes
simulate_jmp32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ पंचांगp = opcode & 0x1f;

	csky_insn_reg_get_val(regs, पंचांगp, &पंचांगp);

	inकाष्ठाion_poपूर्णांकer_set(regs, पंचांगp & 0xfffffffe);
पूर्ण

व्योम __kprobes
simulate_jsr16(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ पंचांगp = (opcode >> 2) & 0xf;

	csky_insn_reg_get_val(regs, पंचांगp, &पंचांगp);

	regs->lr = addr + 2;

	inकाष्ठाion_poपूर्णांकer_set(regs, पंचांगp & 0xfffffffe);
पूर्ण

व्योम __kprobes
simulate_jsr32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ पंचांगp = opcode & 0x1f;

	csky_insn_reg_get_val(regs, पंचांगp, &पंचांगp);

	regs->lr = addr + 4;

	inकाष्ठाion_poपूर्णांकer_set(regs, पंचांगp & 0xfffffffe);
पूर्ण

व्योम __kprobes
simulate_lrw16(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ पंचांगp = (opcode & 0x300) >> 3;
	अचिन्हित दीर्घ offset = ((opcode & 0x1f) | पंचांगp) << 2;

	पंचांगp = (opcode & 0xe0) >> 5;

	val = *(अचिन्हित पूर्णांक *)(inकाष्ठाion_poपूर्णांकer(regs) + offset);

	csky_insn_reg_set_val(regs, पंचांगp, val);
पूर्ण

व्योम __kprobes
simulate_lrw32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ offset = (opcode & 0xffff0000) >> 14;
	अचिन्हित दीर्घ पंचांगp = opcode & 0x0000001f;

	val = *(अचिन्हित पूर्णांक *)
		((inकाष्ठाion_poपूर्णांकer(regs) + offset) & 0xfffffffc);

	csky_insn_reg_set_val(regs, पंचांगp, val);
पूर्ण

व्योम __kprobes
simulate_pop16(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ *पंचांगp = (अचिन्हित दीर्घ *)regs->usp;
	पूर्णांक i;

	क्रम (i = 0; i < (opcode & 0xf); i++) अणु
		csky_insn_reg_set_val(regs, i + 4, *पंचांगp);
		पंचांगp += 1;
	पूर्ण

	अगर (opcode & 0x10) अणु
		csky_insn_reg_set_val(regs, 15, *पंचांगp);
		पंचांगp += 1;
	पूर्ण

	regs->usp = (अचिन्हित दीर्घ)पंचांगp;

	inकाष्ठाion_poपूर्णांकer_set(regs, regs->lr);
पूर्ण

व्योम __kprobes
simulate_pop32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ *पंचांगp = (अचिन्हित दीर्घ *)regs->usp;
	पूर्णांक i;

	क्रम (i = 0; i < ((opcode & 0xf0000) >> 16); i++) अणु
		csky_insn_reg_set_val(regs, i + 4, *पंचांगp);
		पंचांगp += 1;
	पूर्ण

	अगर (opcode & 0x100000) अणु
		csky_insn_reg_set_val(regs, 15, *पंचांगp);
		पंचांगp += 1;
	पूर्ण

	क्रम (i = 0; i < ((opcode & 0xe00000) >> 21); i++) अणु
		csky_insn_reg_set_val(regs, i + 16, *पंचांगp);
		पंचांगp += 1;
	पूर्ण

	अगर (opcode & 0x1000000) अणु
		csky_insn_reg_set_val(regs, 29, *पंचांगp);
		पंचांगp += 1;
	पूर्ण

	regs->usp = (अचिन्हित दीर्घ)पंचांगp;

	inकाष्ठाion_poपूर्णांकer_set(regs, regs->lr);
पूर्ण

व्योम __kprobes
simulate_bez32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ पंचांगp = opcode & 0x1f;

	csky_insn_reg_get_val(regs, पंचांगp, &पंचांगp);

	अगर (पंचांगp == 0) अणु
		inकाष्ठाion_poपूर्णांकer_set(regs,
			addr + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	पूर्ण अन्यथा
		inकाष्ठाion_poपूर्णांकer_set(regs, addr + 4);
पूर्ण

व्योम __kprobes
simulate_bnez32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ पंचांगp = opcode & 0x1f;

	csky_insn_reg_get_val(regs, पंचांगp, &पंचांगp);

	अगर (पंचांगp != 0) अणु
		inकाष्ठाion_poपूर्णांकer_set(regs,
			addr + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	पूर्ण अन्यथा
		inकाष्ठाion_poपूर्णांकer_set(regs, addr + 4);
पूर्ण

व्योम __kprobes
simulate_bnezad32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ पंचांगp = opcode & 0x1f;
	दीर्घ val;

	csky_insn_reg_get_val(regs, पंचांगp, (अचिन्हित दीर्घ *)&val);

	val -= 1;

	अगर (val > 0) अणु
		inकाष्ठाion_poपूर्णांकer_set(regs,
			addr + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	पूर्ण अन्यथा
		inकाष्ठाion_poपूर्णांकer_set(regs, addr + 4);

	csky_insn_reg_set_val(regs, पंचांगp, (अचिन्हित दीर्घ)val);
पूर्ण

व्योम __kprobes
simulate_bhsz32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ पंचांगp = opcode & 0x1f;
	अचिन्हित दीर्घ val;

	csky_insn_reg_get_val(regs, पंचांगp, &val);

	अगर ((दीर्घ) val >= 0) अणु
		inकाष्ठाion_poपूर्णांकer_set(regs,
			addr + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	पूर्ण अन्यथा
		inकाष्ठाion_poपूर्णांकer_set(regs, addr + 4);
पूर्ण

व्योम __kprobes
simulate_bhz32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ पंचांगp = opcode & 0x1f;
	अचिन्हित दीर्घ val;

	csky_insn_reg_get_val(regs, पंचांगp, &val);

	अगर ((दीर्घ) val > 0) अणु
		inकाष्ठाion_poपूर्णांकer_set(regs,
			addr + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	पूर्ण अन्यथा
		inकाष्ठाion_poपूर्णांकer_set(regs, addr + 4);
पूर्ण

व्योम __kprobes
simulate_blsz32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ पंचांगp = opcode & 0x1f;
	अचिन्हित दीर्घ val;

	csky_insn_reg_get_val(regs, पंचांगp, &val);

	अगर ((दीर्घ) val <= 0) अणु
		inकाष्ठाion_poपूर्णांकer_set(regs,
			addr + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	पूर्ण अन्यथा
		inकाष्ठाion_poपूर्णांकer_set(regs, addr + 4);
पूर्ण

व्योम __kprobes
simulate_blz32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ पंचांगp = opcode & 0x1f;
	अचिन्हित दीर्घ val;

	csky_insn_reg_get_val(regs, पंचांगp, &val);

	अगर ((दीर्घ) val < 0) अणु
		inकाष्ठाion_poपूर्णांकer_set(regs,
			addr + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	पूर्ण अन्यथा
		inकाष्ठाion_poपूर्णांकer_set(regs, addr + 4);
पूर्ण

व्योम __kprobes
simulate_bsr32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = (opcode & 0xffff) << 16;
	पंचांगp |= (opcode & 0xffff0000) >> 16;

	inकाष्ठाion_poपूर्णांकer_set(regs,
		addr + sign_extend32((पंचांगp & 0x3ffffff) << 1, 15));

	regs->lr = addr + 4;
पूर्ण

व्योम __kprobes
simulate_jmpi32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ offset = ((opcode & 0xffff0000) >> 14);

	val = *(अचिन्हित पूर्णांक *)
		((inकाष्ठाion_poपूर्णांकer(regs) + offset) & 0xfffffffc);

	inकाष्ठाion_poपूर्णांकer_set(regs, val);
पूर्ण

व्योम __kprobes
simulate_jsri32(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ offset = ((opcode & 0xffff0000) >> 14);

	val = *(अचिन्हित पूर्णांक *)
		((inकाष्ठाion_poपूर्णांकer(regs) + offset) & 0xfffffffc);

	regs->lr = addr + 4;

	inकाष्ठाion_poपूर्णांकer_set(regs, val);
पूर्ण
