<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Fault Injection Test harness (FI)
 *  Copyright (C) Intel Crop.
 */

/*  Id: pf_in.c,v 1.1.1.1 2002/11/12 05:56:32 brlock Exp
 *  Copyright by Intel Crop., 2002
 *  Louis Zhuang (louis.zhuang@पूर्णांकel.com)
 *
 *  Bjorn Steinbrink (B.Steinbrink@gmx.de), 2007
 */

#समावेश <linux/ptrace.h> /* काष्ठा pt_regs */
#समावेश "pf_in.h"

#अगर_घोषित __i386__
/* IA32 Manual 3, 2-1 */
अटल अचिन्हित अक्षर prefix_codes[] = अणु
	0xF0, 0xF2, 0xF3, 0x2E, 0x36, 0x3E, 0x26, 0x64,
	0x65, 0x66, 0x67
पूर्ण;
/* IA32 Manual 3, 3-432*/
अटल अचिन्हित पूर्णांक reg_rop[] = अणु
	0x8A, 0x8B, 0xB60F, 0xB70F, 0xBE0F, 0xBF0F
पूर्ण;
अटल अचिन्हित पूर्णांक reg_wop[] = अणु 0x88, 0x89, 0xAA, 0xAB पूर्ण;
अटल अचिन्हित पूर्णांक imm_wop[] = अणु 0xC6, 0xC7 पूर्ण;
/* IA32 Manual 3, 3-432*/
अटल अचिन्हित पूर्णांक rw8[] = अणु 0x88, 0x8A, 0xC6, 0xAA पूर्ण;
अटल अचिन्हित पूर्णांक rw32[] = अणु
	0x89, 0x8B, 0xC7, 0xB60F, 0xB70F, 0xBE0F, 0xBF0F, 0xAB
पूर्ण;
अटल अचिन्हित पूर्णांक mw8[] = अणु 0x88, 0x8A, 0xC6, 0xB60F, 0xBE0F, 0xAA पूर्ण;
अटल अचिन्हित पूर्णांक mw16[] = अणु 0xB70F, 0xBF0F पूर्ण;
अटल अचिन्हित पूर्णांक mw32[] = अणु 0x89, 0x8B, 0xC7, 0xAB पूर्ण;
अटल अचिन्हित पूर्णांक mw64[] = अणुपूर्ण;
#अन्यथा /* not __i386__ */
अटल अचिन्हित अक्षर prefix_codes[] = अणु
	0x66, 0x67, 0x2E, 0x3E, 0x26, 0x64, 0x65, 0x36,
	0xF0, 0xF3, 0xF2,
	/* REX Prefixes */
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f
पूर्ण;
/* AMD64 Manual 3, Appendix A*/
अटल अचिन्हित पूर्णांक reg_rop[] = अणु
	0x8A, 0x8B, 0xB60F, 0xB70F, 0xBE0F, 0xBF0F
पूर्ण;
अटल अचिन्हित पूर्णांक reg_wop[] = अणु 0x88, 0x89, 0xAA, 0xAB पूर्ण;
अटल अचिन्हित पूर्णांक imm_wop[] = अणु 0xC6, 0xC7 पूर्ण;
अटल अचिन्हित पूर्णांक rw8[] = अणु 0xC6, 0x88, 0x8A, 0xAA पूर्ण;
अटल अचिन्हित पूर्णांक rw32[] = अणु
	0xC7, 0x89, 0x8B, 0xB60F, 0xB70F, 0xBE0F, 0xBF0F, 0xAB
पूर्ण;
/* 8 bit only */
अटल अचिन्हित पूर्णांक mw8[] = अणु 0xC6, 0x88, 0x8A, 0xB60F, 0xBE0F, 0xAA पूर्ण;
/* 16 bit only */
अटल अचिन्हित पूर्णांक mw16[] = अणु 0xB70F, 0xBF0F पूर्ण;
/* 16 or 32 bit */
अटल अचिन्हित पूर्णांक mw32[] = अणु 0xC7 पूर्ण;
/* 16, 32 or 64 bit */
अटल अचिन्हित पूर्णांक mw64[] = अणु 0x89, 0x8B, 0xAB पूर्ण;
#पूर्ण_अगर /* not __i386__ */

काष्ठा prefix_bits अणु
	अचिन्हित लघुed:1;
	अचिन्हित enlarged:1;
	अचिन्हित rexr:1;
	अचिन्हित rex:1;
पूर्ण;

अटल पूर्णांक skip_prefix(अचिन्हित अक्षर *addr, काष्ठा prefix_bits *prf)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर *p = addr;
	prf->लघुed = 0;
	prf->enlarged = 0;
	prf->rexr = 0;
	prf->rex = 0;

restart:
	क्रम (i = 0; i < ARRAY_SIZE(prefix_codes); i++) अणु
		अगर (*p == prefix_codes[i]) अणु
			अगर (*p == 0x66)
				prf->लघुed = 1;
#अगर_घोषित __amd64__
			अगर ((*p & 0xf8) == 0x48)
				prf->enlarged = 1;
			अगर ((*p & 0xf4) == 0x44)
				prf->rexr = 1;
			अगर ((*p & 0xf0) == 0x40)
				prf->rex = 1;
#पूर्ण_अगर
			p++;
			जाओ restart;
		पूर्ण
	पूर्ण

	वापस (p - addr);
पूर्ण

अटल पूर्णांक get_opcode(अचिन्हित अक्षर *addr, अचिन्हित पूर्णांक *opcode)
अणु
	पूर्णांक len;

	अगर (*addr == 0x0F) अणु
		/* 0x0F is extension inकाष्ठाion */
		*opcode = *(अचिन्हित लघु *)addr;
		len = 2;
	पूर्ण अन्यथा अणु
		*opcode = *addr;
		len = 1;
	पूर्ण

	वापस len;
पूर्ण

#घोषणा CHECK_OP_TYPE(opcode, array, type) \
	क्रम (i = 0; i < ARRAY_SIZE(array); i++) अणु \
		अगर (array[i] == opcode) अणु \
			rv = type; \
			जाओ निकास; \
		पूर्ण \
	पूर्ण

क्रमागत reason_type get_ins_type(अचिन्हित दीर्घ ins_addr)
अणु
	अचिन्हित पूर्णांक opcode;
	अचिन्हित अक्षर *p;
	काष्ठा prefix_bits prf;
	पूर्णांक i;
	क्रमागत reason_type rv = OTHERS;

	p = (अचिन्हित अक्षर *)ins_addr;
	p += skip_prefix(p, &prf);
	p += get_opcode(p, &opcode);

	CHECK_OP_TYPE(opcode, reg_rop, REG_READ);
	CHECK_OP_TYPE(opcode, reg_wop, REG_WRITE);
	CHECK_OP_TYPE(opcode, imm_wop, IMM_WRITE);

निकास:
	वापस rv;
पूर्ण
#अघोषित CHECK_OP_TYPE

अटल अचिन्हित पूर्णांक get_ins_reg_width(अचिन्हित दीर्घ ins_addr)
अणु
	अचिन्हित पूर्णांक opcode;
	अचिन्हित अक्षर *p;
	काष्ठा prefix_bits prf;
	पूर्णांक i;

	p = (अचिन्हित अक्षर *)ins_addr;
	p += skip_prefix(p, &prf);
	p += get_opcode(p, &opcode);

	क्रम (i = 0; i < ARRAY_SIZE(rw8); i++)
		अगर (rw8[i] == opcode)
			वापस 1;

	क्रम (i = 0; i < ARRAY_SIZE(rw32); i++)
		अगर (rw32[i] == opcode)
			वापस prf.लघुed ? 2 : (prf.enlarged ? 8 : 4);

	prपूर्णांकk(KERN_ERR "mmiotrace: Unknown opcode 0x%02x\n", opcode);
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक get_ins_mem_width(अचिन्हित दीर्घ ins_addr)
अणु
	अचिन्हित पूर्णांक opcode;
	अचिन्हित अक्षर *p;
	काष्ठा prefix_bits prf;
	पूर्णांक i;

	p = (अचिन्हित अक्षर *)ins_addr;
	p += skip_prefix(p, &prf);
	p += get_opcode(p, &opcode);

	क्रम (i = 0; i < ARRAY_SIZE(mw8); i++)
		अगर (mw8[i] == opcode)
			वापस 1;

	क्रम (i = 0; i < ARRAY_SIZE(mw16); i++)
		अगर (mw16[i] == opcode)
			वापस 2;

	क्रम (i = 0; i < ARRAY_SIZE(mw32); i++)
		अगर (mw32[i] == opcode)
			वापस prf.लघुed ? 2 : 4;

	क्रम (i = 0; i < ARRAY_SIZE(mw64); i++)
		अगर (mw64[i] == opcode)
			वापस prf.लघुed ? 2 : (prf.enlarged ? 8 : 4);

	prपूर्णांकk(KERN_ERR "mmiotrace: Unknown opcode 0x%02x\n", opcode);
	वापस 0;
पूर्ण

/*
 * Define रेजिस्टर ident in mod/rm byte.
 * Note: these are NOT the same as in ptrace-abi.h.
 */
क्रमागत अणु
	arg_AL = 0,
	arg_CL = 1,
	arg_DL = 2,
	arg_BL = 3,
	arg_AH = 4,
	arg_CH = 5,
	arg_DH = 6,
	arg_BH = 7,

	arg_AX = 0,
	arg_CX = 1,
	arg_DX = 2,
	arg_BX = 3,
	arg_SP = 4,
	arg_BP = 5,
	arg_SI = 6,
	arg_DI = 7,
#अगर_घोषित __amd64__
	arg_R8  = 8,
	arg_R9  = 9,
	arg_R10 = 10,
	arg_R11 = 11,
	arg_R12 = 12,
	arg_R13 = 13,
	arg_R14 = 14,
	arg_R15 = 15
#पूर्ण_अगर
पूर्ण;

अटल अचिन्हित अक्षर *get_reg_w8(पूर्णांक no, पूर्णांक rex, काष्ठा pt_regs *regs)
अणु
	अचिन्हित अक्षर *rv = शून्य;

	चयन (no) अणु
	हाल arg_AL:
		rv = (अचिन्हित अक्षर *)&regs->ax;
		अवरोध;
	हाल arg_BL:
		rv = (अचिन्हित अक्षर *)&regs->bx;
		अवरोध;
	हाल arg_CL:
		rv = (अचिन्हित अक्षर *)&regs->cx;
		अवरोध;
	हाल arg_DL:
		rv = (अचिन्हित अक्षर *)&regs->dx;
		अवरोध;
#अगर_घोषित __amd64__
	हाल arg_R8:
		rv = (अचिन्हित अक्षर *)&regs->r8;
		अवरोध;
	हाल arg_R9:
		rv = (अचिन्हित अक्षर *)&regs->r9;
		अवरोध;
	हाल arg_R10:
		rv = (अचिन्हित अक्षर *)&regs->r10;
		अवरोध;
	हाल arg_R11:
		rv = (अचिन्हित अक्षर *)&regs->r11;
		अवरोध;
	हाल arg_R12:
		rv = (अचिन्हित अक्षर *)&regs->r12;
		अवरोध;
	हाल arg_R13:
		rv = (अचिन्हित अक्षर *)&regs->r13;
		अवरोध;
	हाल arg_R14:
		rv = (अचिन्हित अक्षर *)&regs->r14;
		अवरोध;
	हाल arg_R15:
		rv = (अचिन्हित अक्षर *)&regs->r15;
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण

	अगर (rv)
		वापस rv;

	अगर (rex) अणु
		/*
		 * If REX prefix exists, access low bytes of SI etc.
		 * instead of AH etc.
		 */
		चयन (no) अणु
		हाल arg_SI:
			rv = (अचिन्हित अक्षर *)&regs->si;
			अवरोध;
		हाल arg_DI:
			rv = (अचिन्हित अक्षर *)&regs->di;
			अवरोध;
		हाल arg_BP:
			rv = (अचिन्हित अक्षर *)&regs->bp;
			अवरोध;
		हाल arg_SP:
			rv = (अचिन्हित अक्षर *)&regs->sp;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (no) अणु
		हाल arg_AH:
			rv = 1 + (अचिन्हित अक्षर *)&regs->ax;
			अवरोध;
		हाल arg_BH:
			rv = 1 + (अचिन्हित अक्षर *)&regs->bx;
			अवरोध;
		हाल arg_CH:
			rv = 1 + (अचिन्हित अक्षर *)&regs->cx;
			अवरोध;
		हाल arg_DH:
			rv = 1 + (अचिन्हित अक्षर *)&regs->dx;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!rv)
		prपूर्णांकk(KERN_ERR "mmiotrace: Error reg no# %d\n", no);

	वापस rv;
पूर्ण

अटल अचिन्हित दीर्घ *get_reg_w32(पूर्णांक no, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ *rv = शून्य;

	चयन (no) अणु
	हाल arg_AX:
		rv = &regs->ax;
		अवरोध;
	हाल arg_BX:
		rv = &regs->bx;
		अवरोध;
	हाल arg_CX:
		rv = &regs->cx;
		अवरोध;
	हाल arg_DX:
		rv = &regs->dx;
		अवरोध;
	हाल arg_SP:
		rv = &regs->sp;
		अवरोध;
	हाल arg_BP:
		rv = &regs->bp;
		अवरोध;
	हाल arg_SI:
		rv = &regs->si;
		अवरोध;
	हाल arg_DI:
		rv = &regs->di;
		अवरोध;
#अगर_घोषित __amd64__
	हाल arg_R8:
		rv = &regs->r8;
		अवरोध;
	हाल arg_R9:
		rv = &regs->r9;
		अवरोध;
	हाल arg_R10:
		rv = &regs->r10;
		अवरोध;
	हाल arg_R11:
		rv = &regs->r11;
		अवरोध;
	हाल arg_R12:
		rv = &regs->r12;
		अवरोध;
	हाल arg_R13:
		rv = &regs->r13;
		अवरोध;
	हाल arg_R14:
		rv = &regs->r14;
		अवरोध;
	हाल arg_R15:
		rv = &regs->r15;
		अवरोध;
#पूर्ण_अगर
	शेष:
		prपूर्णांकk(KERN_ERR "mmiotrace: Error reg no# %d\n", no);
	पूर्ण

	वापस rv;
पूर्ण

अचिन्हित दीर्घ get_ins_reg_val(अचिन्हित दीर्घ ins_addr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक opcode;
	पूर्णांक reg;
	अचिन्हित अक्षर *p;
	काष्ठा prefix_bits prf;
	पूर्णांक i;

	p = (अचिन्हित अक्षर *)ins_addr;
	p += skip_prefix(p, &prf);
	p += get_opcode(p, &opcode);
	क्रम (i = 0; i < ARRAY_SIZE(reg_rop); i++)
		अगर (reg_rop[i] == opcode)
			जाओ करो_work;

	क्रम (i = 0; i < ARRAY_SIZE(reg_wop); i++)
		अगर (reg_wop[i] == opcode)
			जाओ करो_work;

	prपूर्णांकk(KERN_ERR "mmiotrace: Not a register instruction, opcode "
							"0x%02x\n", opcode);
	जाओ err;

करो_work:
	/* क्रम STOS, source रेजिस्टर is fixed */
	अगर (opcode == 0xAA || opcode == 0xAB) अणु
		reg = arg_AX;
	पूर्ण अन्यथा अणु
		अचिन्हित अक्षर mod_rm = *p;
		reg = ((mod_rm >> 3) & 0x7) | (prf.rexr << 3);
	पूर्ण
	चयन (get_ins_reg_width(ins_addr)) अणु
	हाल 1:
		वापस *get_reg_w8(reg, prf.rex, regs);

	हाल 2:
		वापस *(अचिन्हित लघु *)get_reg_w32(reg, regs);

	हाल 4:
		वापस *(अचिन्हित पूर्णांक *)get_reg_w32(reg, regs);

#अगर_घोषित __amd64__
	हाल 8:
		वापस *(अचिन्हित दीर्घ *)get_reg_w32(reg, regs);
#पूर्ण_अगर

	शेष:
		prपूर्णांकk(KERN_ERR "mmiotrace: Error width# %d\n", reg);
	पूर्ण

err:
	वापस 0;
पूर्ण

अचिन्हित दीर्घ get_ins_imm_val(अचिन्हित दीर्घ ins_addr)
अणु
	अचिन्हित पूर्णांक opcode;
	अचिन्हित अक्षर mod_rm;
	अचिन्हित अक्षर mod;
	अचिन्हित अक्षर *p;
	काष्ठा prefix_bits prf;
	पूर्णांक i;

	p = (अचिन्हित अक्षर *)ins_addr;
	p += skip_prefix(p, &prf);
	p += get_opcode(p, &opcode);
	क्रम (i = 0; i < ARRAY_SIZE(imm_wop); i++)
		अगर (imm_wop[i] == opcode)
			जाओ करो_work;

	prपूर्णांकk(KERN_ERR "mmiotrace: Not an immediate instruction, opcode "
							"0x%02x\n", opcode);
	जाओ err;

करो_work:
	mod_rm = *p;
	mod = mod_rm >> 6;
	p++;
	चयन (mod) अणु
	हाल 0:
		/* अगर r/m is 5 we have a 32 disp (IA32 Manual 3, Table 2-2)  */
		/* AMD64: XXX Check क्रम address size prefix? */
		अगर ((mod_rm & 0x7) == 0x5)
			p += 4;
		अवरोध;

	हाल 1:
		p += 1;
		अवरोध;

	हाल 2:
		p += 4;
		अवरोध;

	हाल 3:
	शेष:
		prपूर्णांकk(KERN_ERR "mmiotrace: not a memory access instruction "
						"at 0x%lx, rm_mod=0x%02x\n",
						ins_addr, mod_rm);
	पूर्ण

	चयन (get_ins_reg_width(ins_addr)) अणु
	हाल 1:
		वापस *(अचिन्हित अक्षर *)p;

	हाल 2:
		वापस *(अचिन्हित लघु *)p;

	हाल 4:
		वापस *(अचिन्हित पूर्णांक *)p;

#अगर_घोषित __amd64__
	हाल 8:
		वापस *(अचिन्हित दीर्घ *)p;
#पूर्ण_अगर

	शेष:
		prपूर्णांकk(KERN_ERR "mmiotrace: Error: width.\n");
	पूर्ण

err:
	वापस 0;
पूर्ण
