<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/ptrace.h>
#समावेश <linux/uaccess.h>
#समावेश <abi/reg_ops.h>

#घोषणा MTCR_MASK	0xFC00FFE0
#घोषणा MFCR_MASK	0xFC00FFE0
#घोषणा MTCR_DIST	0xC0006420
#घोषणा MFCR_DIST	0xC0006020

/*
 * fpu_libc_helper() is to help libc to excute:
 *  - mfcr %a, cr<1, 2>
 *  - mfcr %a, cr<2, 2>
 *  - mtcr %a, cr<1, 2>
 *  - mtcr %a, cr<2, 2>
 */
पूर्णांक fpu_libc_helper(काष्ठा pt_regs *regs)
अणु
	पूर्णांक fault;
	अचिन्हित दीर्घ instrptr, regx = 0;
	अचिन्हित दीर्घ index = 0, पंचांगp = 0;
	अचिन्हित दीर्घ tinstr = 0;
	u16 instr_hi, instr_low;

	instrptr = inकाष्ठाion_poपूर्णांकer(regs);
	अगर (instrptr & 1)
		वापस 0;

	fault = __get_user(instr_low, (u16 *)instrptr);
	अगर (fault)
		वापस 0;

	fault = __get_user(instr_hi, (u16 *)(instrptr + 2));
	अगर (fault)
		वापस 0;

	tinstr = instr_hi | ((अचिन्हित दीर्घ)instr_low << 16);

	अगर (((tinstr >> 21) & 0x1F) != 2)
		वापस 0;

	अगर ((tinstr & MTCR_MASK) == MTCR_DIST) अणु
		index = (tinstr >> 16) & 0x1F;
		अगर (index > 13)
			वापस 0;

		पंचांगp = tinstr & 0x1F;
		अगर (पंचांगp > 2)
			वापस 0;

		regx =  *(&regs->a0 + index);

		अगर (पंचांगp == 1)
			mtcr("cr<1, 2>", regx);
		अन्यथा अगर (पंचांगp == 2)
			mtcr("cr<2, 2>", regx);
		अन्यथा
			वापस 0;

		regs->pc += 4;
		वापस 1;
	पूर्ण

	अगर ((tinstr & MFCR_MASK) == MFCR_DIST) अणु
		index = tinstr & 0x1F;
		अगर (index > 13)
			वापस 0;

		पंचांगp = ((tinstr >> 16) & 0x1F);
		अगर (पंचांगp > 2)
			वापस 0;

		अगर (पंचांगp == 1)
			regx = mfcr("cr<1, 2>");
		अन्यथा अगर (पंचांगp == 2)
			regx = mfcr("cr<2, 2>");
		अन्यथा
			वापस 0;

		*(&regs->a0 + index) = regx;

		regs->pc += 4;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम fpu_fpe(काष्ठा pt_regs *regs)
अणु
	पूर्णांक sig, code;
	अचिन्हित पूर्णांक fesr;

	fesr = mfcr("cr<2, 2>");

	sig = संक_भ_त्रुटि;
	code = FPE_FLTUNK;

	अगर (fesr & FPE_ILLE) अणु
		sig = संक_अवैध;
		code = ILL_ILLOPC;
	पूर्ण अन्यथा अगर (fesr & FPE_IDC) अणु
		sig = संक_अवैध;
		code = ILL_ILLOPN;
	पूर्ण अन्यथा अगर (fesr & FPE_FEC) अणु
		sig = संक_भ_त्रुटि;
		अगर (fesr & FPE_IOC)
			code = FPE_FLTINV;
		अन्यथा अगर (fesr & FPE_DZC)
			code = FPE_FLTDIV;
		अन्यथा अगर (fesr & FPE_UFC)
			code = FPE_FLTUND;
		अन्यथा अगर (fesr & FPE_OFC)
			code = FPE_FLTOVF;
		अन्यथा अगर (fesr & FPE_IXC)
			code = FPE_FLTRES;
	पूर्ण

	क्रमce_sig_fault(sig, code, (व्योम __user *)regs->pc);
पूर्ण

#घोषणा FMFVR_FPU_REGS(vrx, vry)	\
	"fmfvrl %0, "#vrx"\n"		\
	"fmfvrh %1, "#vrx"\n"		\
	"fmfvrl %2, "#vry"\n"		\
	"fmfvrh %3, "#vry"\n"

#घोषणा FMTVR_FPU_REGS(vrx, vry)	\
	"fmtvrl "#vrx", %0\n"		\
	"fmtvrh "#vrx", %1\n"		\
	"fmtvrl "#vry", %2\n"		\
	"fmtvrh "#vry", %3\n"

#घोषणा STW_FPU_REGS(a, b, c, d)	\
	"stw    %0, (%4, "#a")\n"	\
	"stw    %1, (%4, "#b")\n"	\
	"stw    %2, (%4, "#c")\n"	\
	"stw    %3, (%4, "#d")\n"

#घोषणा LDW_FPU_REGS(a, b, c, d)	\
	"ldw    %0, (%4, "#a")\n"	\
	"ldw    %1, (%4, "#b")\n"	\
	"ldw    %2, (%4, "#c")\n"	\
	"ldw    %3, (%4, "#d")\n"

व्योम save_to_user_fp(काष्ठा user_fp *user_fp)
अणु
	अचिन्हित दीर्घ flg;
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;
	अचिन्हित दीर्घ *fpregs;

	local_irq_save(flg);

	पंचांगp1 = mfcr("cr<1, 2>");
	पंचांगp2 = mfcr("cr<2, 2>");

	user_fp->fcr = पंचांगp1;
	user_fp->fesr = पंचांगp2;

	fpregs = &user_fp->vr[0];
#अगर_घोषित CONFIG_CPU_HAS_FPUV2
#अगर_घोषित CONFIG_CPU_HAS_VDSP
	यंत्र अस्थिर(
		"vstmu.32    vr0-vr3,   (%0)\n"
		"vstmu.32    vr4-vr7,   (%0)\n"
		"vstmu.32    vr8-vr11,  (%0)\n"
		"vstmu.32    vr12-vr15, (%0)\n"
		"fstmu.64    vr16-vr31, (%0)\n"
		: "+a"(fpregs)
		::"memory");
#अन्यथा
	यंत्र अस्थिर(
		"fstmu.64    vr0-vr31,  (%0)\n"
		: "+a"(fpregs)
		::"memory");
#पूर्ण_अगर
#अन्यथा
	अणु
	अचिन्हित दीर्घ पंचांगp3, पंचांगp4;

	यंत्र अस्थिर(
		FMFVR_FPU_REGS(vr0, vr1)
		STW_FPU_REGS(0, 4, 16, 20)
		FMFVR_FPU_REGS(vr2, vr3)
		STW_FPU_REGS(32, 36, 48, 52)
		FMFVR_FPU_REGS(vr4, vr5)
		STW_FPU_REGS(64, 68, 80, 84)
		FMFVR_FPU_REGS(vr6, vr7)
		STW_FPU_REGS(96, 100, 112, 116)
		"addi	%4, 128\n"
		FMFVR_FPU_REGS(vr8, vr9)
		STW_FPU_REGS(0, 4, 16, 20)
		FMFVR_FPU_REGS(vr10, vr11)
		STW_FPU_REGS(32, 36, 48, 52)
		FMFVR_FPU_REGS(vr12, vr13)
		STW_FPU_REGS(64, 68, 80, 84)
		FMFVR_FPU_REGS(vr14, vr15)
		STW_FPU_REGS(96, 100, 112, 116)
		: "=a"(पंचांगp1), "=a"(पंचांगp2), "=a"(पंचांगp3),
		  "=a"(पंचांगp4), "+a"(fpregs)
		::"memory");
	पूर्ण
#पूर्ण_अगर

	local_irq_restore(flg);
पूर्ण

व्योम restore_from_user_fp(काष्ठा user_fp *user_fp)
अणु
	अचिन्हित दीर्घ flg;
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;
	अचिन्हित दीर्घ *fpregs;

	local_irq_save(flg);

	पंचांगp1 = user_fp->fcr;
	पंचांगp2 = user_fp->fesr;

	mtcr("cr<1, 2>", पंचांगp1);
	mtcr("cr<2, 2>", पंचांगp2);

	fpregs = &user_fp->vr[0];
#अगर_घोषित CONFIG_CPU_HAS_FPUV2
#अगर_घोषित CONFIG_CPU_HAS_VDSP
	यंत्र अस्थिर(
		"vldmu.32    vr0-vr3,   (%0)\n"
		"vldmu.32    vr4-vr7,   (%0)\n"
		"vldmu.32    vr8-vr11,  (%0)\n"
		"vldmu.32    vr12-vr15, (%0)\n"
		"fldmu.64    vr16-vr31, (%0)\n"
		: "+a"(fpregs)
		::"memory");
#अन्यथा
	यंत्र अस्थिर(
		"fldmu.64    vr0-vr31,  (%0)\n"
		: "+a"(fpregs)
		::"memory");
#पूर्ण_अगर
#अन्यथा
	अणु
	अचिन्हित दीर्घ पंचांगp3, पंचांगp4;

	यंत्र अस्थिर(
		LDW_FPU_REGS(0, 4, 16, 20)
		FMTVR_FPU_REGS(vr0, vr1)
		LDW_FPU_REGS(32, 36, 48, 52)
		FMTVR_FPU_REGS(vr2, vr3)
		LDW_FPU_REGS(64, 68, 80, 84)
		FMTVR_FPU_REGS(vr4, vr5)
		LDW_FPU_REGS(96, 100, 112, 116)
		FMTVR_FPU_REGS(vr6, vr7)
		"addi	%4, 128\n"
		LDW_FPU_REGS(0, 4, 16, 20)
		FMTVR_FPU_REGS(vr8, vr9)
		LDW_FPU_REGS(32, 36, 48, 52)
		FMTVR_FPU_REGS(vr10, vr11)
		LDW_FPU_REGS(64, 68, 80, 84)
		FMTVR_FPU_REGS(vr12, vr13)
		LDW_FPU_REGS(96, 100, 112, 116)
		FMTVR_FPU_REGS(vr14, vr15)
		: "=a"(पंचांगp1), "=a"(पंचांगp2), "=a"(पंचांगp3),
		  "=a"(पंचांगp4), "+a"(fpregs)
		::"memory");
	पूर्ण
#पूर्ण_अगर
	local_irq_restore(flg);
पूर्ण
