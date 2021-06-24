<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/opcodes.h>

अटल अचिन्हित दीर्घ
__arm_gen_branch_thumb2(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ addr, bool link)
अणु
	अचिन्हित दीर्घ s, j1, j2, i1, i2, imm10, imm11;
	अचिन्हित दीर्घ first, second;
	दीर्घ offset;

	offset = (दीर्घ)addr - (दीर्घ)(pc + 4);
	अगर (offset < -16777216 || offset > 16777214) अणु
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण

	s	= (offset >> 24) & 0x1;
	i1	= (offset >> 23) & 0x1;
	i2	= (offset >> 22) & 0x1;
	imm10	= (offset >> 12) & 0x3ff;
	imm11	= (offset >>  1) & 0x7ff;

	j1 = (!i1) ^ s;
	j2 = (!i2) ^ s;

	first = 0xf000 | (s << 10) | imm10;
	second = 0x9000 | (j1 << 13) | (j2 << 11) | imm11;
	अगर (link)
		second |= 1 << 14;

	वापस __opcode_thumb32_compose(first, second);
पूर्ण

अटल अचिन्हित दीर्घ
__arm_gen_branch_arm(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ addr, bool link)
अणु
	अचिन्हित दीर्घ opcode = 0xea000000;
	दीर्घ offset;

	अगर (link)
		opcode |= 1 << 24;

	offset = (दीर्घ)addr - (दीर्घ)(pc + 8);
	अगर (unlikely(offset < -33554432 || offset > 33554428)) अणु
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण

	offset = (offset >> 2) & 0x00ffffff;

	वापस opcode | offset;
पूर्ण

अचिन्हित दीर्घ
__arm_gen_branch(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ addr, bool link)
अणु
	अगर (IS_ENABLED(CONFIG_THUMB2_KERNEL))
		वापस __arm_gen_branch_thumb2(pc, addr, link);
	अन्यथा
		वापस __arm_gen_branch_arm(pc, addr, link);
पूर्ण
