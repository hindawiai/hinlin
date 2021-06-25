<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>

प्रकार अचिन्हित पूर्णांक instr;

#घोषणा MAJOR_OP	0xfc000000
#घोषणा LDA_OP		0x20000000
#घोषणा STQ_OP		0xb4000000
#घोषणा BR_OP		0xc0000000

#घोषणा STK_ALLOC_1	0x23de8000 /* lda $30,-X($30) */
#घोषणा STK_ALLOC_1M	0xffff8000
#घोषणा STK_ALLOC_2	0x43c0153e /* subq $30,X,$30 */
#घोषणा STK_ALLOC_2M	0xffe01fff

#घोषणा MEM_REG		0x03e00000
#घोषणा MEM_BASE	0x001f0000
#घोषणा MEM_OFF		0x0000ffff
#घोषणा MEM_OFF_SIGN	0x00008000
#घोषणा	BASE_SP		0x001e0000

#घोषणा STK_ALLOC_MATCH(INSTR)			\
  (((INSTR) & STK_ALLOC_1M) == STK_ALLOC_1	\
   || ((INSTR) & STK_ALLOC_2M) == STK_ALLOC_2)
#घोषणा STK_PUSH_MATCH(INSTR) \
  (((INSTR) & (MAJOR_OP | MEM_BASE | MEM_OFF_SIGN)) == (STQ_OP | BASE_SP))
#घोषणा MEM_OP_OFFSET(INSTR) \
  (((दीर्घ)((INSTR) & MEM_OFF) << 48) >> 48)
#घोषणा MEM_OP_REG(INSTR) \
  (((INSTR) & MEM_REG) >> 22)

/* Branches, jumps, PAL calls, and illegal opcodes end a basic block. */
#घोषणा BB_END(INSTR)						\
  (((instr)(INSTR) >= BR_OP) | ((instr)(INSTR) < LDA_OP) |	\
   ((((instr)(INSTR) ^ 0x60000000) < 0x20000000) &		\
    (((instr)(INSTR) & 0x0c000000) != 0)))

#घोषणा IS_KERNEL_TEXT(PC) ((अचिन्हित दीर्घ)(PC) > START_ADDR)

अटल अक्षर reg_name[][4] = अणु
	"v0 ", "t0 ", "t1 ", "t2 ", "t3 ", "t4 ", "t5 ", "t6 ", "t7 ",
	"s0 ", "s1 ", "s2 ", "s3 ", "s4 ", "s5 ", "s6 ", "a0 ", "a1 ",
	"a2 ", "a3 ", "a4 ", "a5 ", "t8 ", "t9 ", "t10", "t11", "ra ",
	"pv ", "at ", "gp ", "sp ", "0"
पूर्ण;


अटल instr *
display_stored_regs(instr * pro_pc, अचिन्हित अक्षर * sp)
अणु
	instr * ret_pc = 0;
	पूर्णांक reg;
	अचिन्हित दीर्घ value;

	prपूर्णांकk("Prologue [<%p>], Frame %p:\n", pro_pc, sp);
	जबतक (!BB_END(*pro_pc))
		अगर (STK_PUSH_MATCH(*pro_pc)) अणु
			reg = (*pro_pc & MEM_REG) >> 21;
			value = *(अचिन्हित दीर्घ *)(sp + (*pro_pc & MEM_OFF));
			अगर (reg == 26)
				ret_pc = (instr *)value;
			prपूर्णांकk("\t\t%s / 0x%016lx\n", reg_name[reg], value);
		पूर्ण
	वापस ret_pc;
पूर्ण

अटल instr *
seek_prologue(instr * pc)
अणु
	जबतक (!STK_ALLOC_MATCH(*pc))
		--pc;
	जबतक (!BB_END(*(pc - 1)))
		--pc;
	वापस pc;
पूर्ण

अटल दीर्घ
stack_increment(instr * prologue_pc)
अणु
	जबतक (!STK_ALLOC_MATCH(*prologue_pc))
		++prologue_pc;

	/* Count the bytes allocated. */
	अगर ((*prologue_pc & STK_ALLOC_1M) == STK_ALLOC_1M)
		वापस -(((दीर्घ)(*prologue_pc) << 48) >> 48);
	अन्यथा
		वापस (*prologue_pc >> 13) & 0xff;
पूर्ण

व्योम
stacktrace(व्योम)
अणु
	instr * ret_pc;
	instr * prologue = (instr *)stacktrace;
	रेजिस्टर अचिन्हित अक्षर * sp __यंत्र__ ("$30");

	prपूर्णांकk("\tstack trace:\n");
	करो अणु
		ret_pc = display_stored_regs(prologue, sp);
		sp += stack_increment(prologue);
		prologue = seek_prologue(ret_pc);
	पूर्ण जबतक (IS_KERNEL_TEXT(ret_pc));
पूर्ण
