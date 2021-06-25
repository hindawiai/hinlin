<शैली गुरु>
/*
 *    ptrace cpu depend helper functions
 *
 *  Copyright 2003, 2015 Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of
 * this archive क्रम more details.
 */

#समावेश <linux/linkage.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <यंत्र/ptrace.h>

#घोषणा BREAKINST 0x5730 /* trapa #3 */

/* disable singlestep */
व्योम user_disable_single_step(काष्ठा task_काष्ठा *child)
अणु
	अगर ((दीर्घ)child->thपढ़ो.अवरोधinfo.addr != -1L) अणु
		*(child->thपढ़ो.अवरोधinfo.addr) = child->thपढ़ो.अवरोधinfo.inst;
		child->thपढ़ो.अवरोधinfo.addr = (अचिन्हित लघु *)-1L;
	पूर्ण
पूर्ण

/* calculate next pc */
क्रमागत jump_type अणुnone,	 /* normal inकाष्ठाion */
		jअसल,	 /* असलolute address jump */
		ind,	 /* indirect address jump */
		ret,	 /* वापस to subrutine */
		reg,	 /* रेजिस्टर indexed jump */
		relb,	 /* pc relative jump (byte offset) */
		relw,	 /* pc relative jump (word offset) */
	       पूर्ण;

/* opcode decode table define
   ptn: opcode pattern
   msk: opcode biपंचांगask
   len: inकाष्ठाion length (<0 next table index)
   jmp: jump operation mode */
काष्ठा optable अणु
	अचिन्हित अक्षर bitpattern;
	अचिन्हित अक्षर biपंचांगask;
	चिन्हित अक्षर length;
	चिन्हित अक्षर type;
पूर्ण __packed __aligned(1);

#घोषणा OPTABLE(ptn, msk, len, jmp)	\
	अणु				\
		.bitpattern = ptn,	\
		.biपंचांगask    = msk,	\
		.length	    = len,	\
		.type	    = jmp,	\
	पूर्ण

अटल स्थिर काष्ठा optable optable_0[] = अणु
	OPTABLE(0x00, 0xff,  1, none), /* 0x00 */
	OPTABLE(0x01, 0xff, -1, none), /* 0x01 */
	OPTABLE(0x02, 0xfe,  1, none), /* 0x02-0x03 */
	OPTABLE(0x04, 0xee,  1, none), /* 0x04-0x05/0x14-0x15 */
	OPTABLE(0x06, 0xfe,  1, none), /* 0x06-0x07 */
	OPTABLE(0x08, 0xea,  1, none), /* 0x08-0x09/0x0c-0x0d/0x18-0x19/0x1c-0x1d */
	OPTABLE(0x0a, 0xee,  1, none), /* 0x0a-0x0b/0x1a-0x1b */
	OPTABLE(0x0e, 0xee,  1, none), /* 0x0e-0x0f/0x1e-0x1f */
	OPTABLE(0x10, 0xfc,  1, none), /* 0x10-0x13 */
	OPTABLE(0x16, 0xfe,  1, none), /* 0x16-0x17 */
	OPTABLE(0x20, 0xe0,  1, none), /* 0x20-0x3f */
	OPTABLE(0x40, 0xf0,  1, relb), /* 0x40-0x4f */
	OPTABLE(0x50, 0xfc,  1, none), /* 0x50-0x53 */
	OPTABLE(0x54, 0xfd,  1, ret), /* 0x54/0x56 */
	OPTABLE(0x55, 0xff,  1, relb), /* 0x55 */
	OPTABLE(0x57, 0xff,  1, none), /* 0x57 */
	OPTABLE(0x58, 0xfb,  2, relw), /* 0x58/0x5c */
	OPTABLE(0x59, 0xfb,  1, reg), /* 0x59/0x5b */
	OPTABLE(0x5a, 0xfb,  2, jअसल), /* 0x5a/0x5e */
	OPTABLE(0x5b, 0xfb,  2, ind), /* 0x5b/0x5f */
	OPTABLE(0x60, 0xe8,  1, none), /* 0x60-0x67/0x70-0x77 */
	OPTABLE(0x68, 0xfa,  1, none), /* 0x68-0x69/0x6c-0x6d */
	OPTABLE(0x6a, 0xfe, -2, none), /* 0x6a-0x6b */
	OPTABLE(0x6e, 0xfe,  2, none), /* 0x6e-0x6f */
	OPTABLE(0x78, 0xff,  4, none), /* 0x78 */
	OPTABLE(0x79, 0xff,  2, none), /* 0x79 */
	OPTABLE(0x7a, 0xff,  3, none), /* 0x7a */
	OPTABLE(0x7b, 0xff,  2, none), /* 0x7b */
	OPTABLE(0x7c, 0xfc,  2, none), /* 0x7c-0x7f */
	OPTABLE(0x80, 0x80,  1, none), /* 0x80-0xff */
पूर्ण;

अटल स्थिर काष्ठा optable optable_1[] = अणु
	OPTABLE(0x00, 0xff, -3, none), /* 0x0100 */
	OPTABLE(0x40, 0xf0, -3, none), /* 0x0140-0x14f */
	OPTABLE(0x80, 0xf0,  1, none), /* 0x0180-0x018f */
	OPTABLE(0xc0, 0xc0,  2, none), /* 0x01c0-0x01ff */
पूर्ण;

अटल स्थिर काष्ठा optable optable_2[] = अणु
	OPTABLE(0x00, 0x20,  2, none), /* 0x6a0?/0x6a8?/0x6b0?/0x6b8? */
	OPTABLE(0x20, 0x20,  3, none), /* 0x6a2?/0x6aa?/0x6b2?/0x6ba? */
पूर्ण;

अटल स्थिर काष्ठा optable optable_3[] = अणु
	OPTABLE(0x69, 0xfb,  2, none), /* 0x010069/0x01006d/014069/0x01406d */
	OPTABLE(0x6b, 0xff, -4, none), /* 0x01006b/0x01406b */
	OPTABLE(0x6f, 0xff,  3, none), /* 0x01006f/0x01406f */
	OPTABLE(0x78, 0xff,  5, none), /* 0x010078/0x014078 */
पूर्ण;

अटल स्थिर काष्ठा optable optable_4[] = अणु
/* 0x0100690?/0x01006d0?/0140690?/0x01406d0?/
   0x0100698?/0x01006d8?/0140698?/0x01406d8? */
	OPTABLE(0x00, 0x78, 3, none),
/* 0x0100692?/0x01006d2?/0140692?/0x01406d2?/
   0x010069a?/0x01006da?/014069a?/0x01406da? */
	OPTABLE(0x20, 0x78, 4, none),
पूर्ण;

अटल स्थिर काष्ठा optables_list अणु
	स्थिर काष्ठा optable *ptr;
	पूर्णांक size;
पूर्ण optables[] = अणु
#घोषणा OPTABLES(no)                                                   \
	अणु                                                              \
		.ptr  = optable_##no,                                  \
		.size = माप(optable_##no) / माप(काष्ठा optable), \
	पूर्ण
	OPTABLES(0),
	OPTABLES(1),
	OPTABLES(2),
	OPTABLES(3),
	OPTABLES(4),

पूर्ण;

स्थिर अचिन्हित अक्षर condmask[] = अणु
	0x00, 0x40, 0x01, 0x04, 0x02, 0x08, 0x10, 0x20
पूर्ण;

अटल पूर्णांक isbranch(काष्ठा task_काष्ठा *task, पूर्णांक reson)
अणु
	अचिन्हित अक्षर cond = h8300_get_reg(task, PT_CCR);

	/* encode complex conditions */
	/* B4: N^V
	   B5: Z|(N^V)
	   B6: C|Z */
	__यंत्र__("bld #3,%w0\n\t"
		"bxor #1,%w0\n\t"
		"bst #4,%w0\n\t"
		"bor #2,%w0\n\t"
		"bst #5,%w0\n\t"
		"bld #2,%w0\n\t"
		"bor #0,%w0\n\t"
		"bst #6,%w0\n\t"
		: "=&r"(cond) : "0"(cond) : "cc");
	cond &= condmask[reson >> 1];
	अगर (!(reson & 1))
		वापस cond == 0;
	अन्यथा
		वापस cond != 0;
पूर्ण

अटल अचिन्हित लघु *decode(काष्ठा task_काष्ठा *child,
			      स्थिर काष्ठा optable *op,
			      अक्षर *fetch_p, अचिन्हित लघु *pc,
			      अचिन्हित अक्षर inst)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ *sp;
	पूर्णांक regno;

	चयन (op->type) अणु
	हाल none:
		वापस (अचिन्हित लघु *)pc + op->length;
	हाल jअसल:
		addr = *(अचिन्हित दीर्घ *)pc;
		वापस (अचिन्हित लघु *)(addr & 0x00ffffff);
	हाल ind:
		addr = *pc & 0xff;
		वापस (अचिन्हित लघु *)(*(अचिन्हित दीर्घ *)addr);
	हाल ret:
		sp = (अचिन्हित दीर्घ *)h8300_get_reg(child, PT_USP);
		/* user stack frames
		   |   er0  | temporary saved
		   +--------+
		   |   exp  | exception stack frames
		   +--------+
		   | ret pc | userspace वापस address
		*/
		वापस (अचिन्हित लघु *)(*(sp+2) & 0x00ffffff);
	हाल reg:
		regno = (*pc >> 4) & 0x07;
		अगर (regno == 0)
			addr = h8300_get_reg(child, PT_ER0);
		अन्यथा
			addr = h8300_get_reg(child, regno-1 + PT_ER1);
		वापस (अचिन्हित लघु *)addr;
	हाल relb:
		अगर (inst == 0x55 || isbranch(child, inst & 0x0f))
			pc = (अचिन्हित लघु *)((अचिन्हित दीर्घ)pc +
						((चिन्हित अक्षर)(*fetch_p)));
		वापस pc+1; /* skip myself */
	हाल relw:
		अगर (inst == 0x5c || isbranch(child, (*fetch_p & 0xf0) >> 4))
			pc = (अचिन्हित लघु *)((अचिन्हित दीर्घ)pc +
						((चिन्हित लघु)(*(pc+1))));
		वापस pc+2; /* skip myself */
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल अचिन्हित लघु *nextpc(काष्ठा task_काष्ठा *child, अचिन्हित लघु *pc)
अणु
	स्थिर काष्ठा optable *op;
	अचिन्हित अक्षर *fetch_p;
	पूर्णांक op_len;
	अचिन्हित अक्षर inst;

	op = optables[0].ptr;
	op_len = optables[0].size;
	fetch_p = (अचिन्हित अक्षर *)pc;
	inst = *fetch_p++;
	करो अणु
		अगर ((inst & op->biपंचांगask) == op->bitpattern) अणु
			अगर (op->length < 0) अणु
				op = optables[-op->length].ptr;
				op_len = optables[-op->length].size + 1;
				inst = *fetch_p++;
			पूर्ण अन्यथा
				वापस decode(child, op, fetch_p, pc, inst);
		पूर्ण अन्यथा
			op++;
	पूर्ण जबतक (--op_len > 0);
	वापस शून्य;
पूर्ण

/* Set अवरोधpoपूर्णांक(s) to simulate a single step from the current PC.  */

व्योम user_enable_single_step(काष्ठा task_काष्ठा *child)
अणु
	अचिन्हित लघु *next;

	next = nextpc(child, (अचिन्हित लघु *)h8300_get_reg(child, PT_PC));
	child->thपढ़ो.अवरोधinfo.addr = next;
	child->thपढ़ो.अवरोधinfo.inst = *next;
	*next = BREAKINST;
पूर्ण

यंत्रlinkage व्योम trace_trap(अचिन्हित दीर्घ bp)
अणु
	अगर ((अचिन्हित दीर्घ)current->thपढ़ो.अवरोधinfo.addr == bp) अणु
		user_disable_single_step(current);
		क्रमce_sig(SIGTRAP);
	पूर्ण अन्यथा
		क्रमce_sig(संक_अवैध);
पूर्ण
