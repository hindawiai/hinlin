<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2018 Andes Technology Corporation

#समावेश <यंत्र/bitfield.h>
#समावेश <यंत्र/uaccess.h>
#समावेश <यंत्र/sfp-machine.h>
#समावेश <यंत्र/fpuemu.h>
#समावेश <यंत्र/nds32_fpu_inst.h>

#घोषणा DPFROMREG(dp, x) (dp = (व्योम *)((अचिन्हित दीर्घ *)fpu_reg + 2*x))
#अगर_घोषित __NDS32_EL__
#घोषणा SPFROMREG(sp, x)\
	((sp) = (व्योम *)((अचिन्हित दीर्घ *)fpu_reg + (x^1)))
#अन्यथा
#घोषणा SPFROMREG(sp, x) ((sp) = (व्योम *)((अचिन्हित दीर्घ *)fpu_reg + x))
#पूर्ण_अगर

#घोषणा DEF3OP(name, p, f1, f2) \
व्योम fpemu_##name##p(व्योम *ft, व्योम *fa, व्योम *fb) \
अणु \
	f1(fa, fa, fb); \
	f2(ft, ft, fa); \
पूर्ण

#घोषणा DEF3OPNEG(name, p, f1, f2, f3) \
व्योम fpemu_##name##p(व्योम *ft, व्योम *fa, व्योम *fb) \
अणु \
	f1(fa, fa, fb); \
	f2(ft, ft, fa); \
	f3(ft, ft); \
पूर्ण
DEF3OP(fmadd, s, fmuls, fadds);
DEF3OP(fmsub, s, fmuls, fsubs);
DEF3OP(fmadd, d, fmuld, faddd);
DEF3OP(fmsub, d, fmuld, fsubd);
DEF3OPNEG(fnmadd, s, fmuls, fadds, fnegs);
DEF3OPNEG(fnmsub, s, fmuls, fsubs, fnegs);
DEF3OPNEG(fnmadd, d, fmuld, faddd, fnegd);
DEF3OPNEG(fnmsub, d, fmuld, fsubd, fnegd);

अटल स्थिर अचिन्हित अक्षर cmptab[8] = अणु
	SF_CEQ,
	SF_CEQ,
	SF_CLT,
	SF_CLT,
	SF_CLT | SF_CEQ,
	SF_CLT | SF_CEQ,
	SF_CUN,
	SF_CUN
पूर्ण;

क्रमागत ARGTYPE अणु
	S1S = 1,
	S2S,
	S1D,
	CS,
	D1D,
	D2D,
	D1S,
	CD
पूर्ण;
जोड़ func_t अणु
	व्योम (*t)(व्योम *ft, व्योम *fa, व्योम *fb);
	व्योम (*b)(व्योम *ft, व्योम *fa);
पूर्ण;
/*
 * Emulate a single FPU arithmetic inकाष्ठाion.
 */
अटल पूर्णांक fpu_emu(काष्ठा fpu_काष्ठा *fpu_reg, अचिन्हित दीर्घ insn)
अणु
	पूर्णांक rfmt;		/* resulting क्रमmat */
	जोड़ func_t func;
	पूर्णांक ftype = 0;

	चयन (rfmt = NDS32Insn_OPCODE_COP0(insn)) अणु
	हाल fs1_op:अणु
			चयन (NDS32Insn_OPCODE_BIT69(insn)) अणु
			हाल fadds_op:
				func.t = fadds;
				ftype = S2S;
				अवरोध;
			हाल fsubs_op:
				func.t = fsubs;
				ftype = S2S;
				अवरोध;
			हाल fmadds_op:
				func.t = fpemu_fmadds;
				ftype = S2S;
				अवरोध;
			हाल fmsubs_op:
				func.t = fpemu_fmsubs;
				ftype = S2S;
				अवरोध;
			हाल fnmadds_op:
				func.t = fpemu_fnmadds;
				ftype = S2S;
				अवरोध;
			हाल fnmsubs_op:
				func.t = fpemu_fnmsubs;
				ftype = S2S;
				अवरोध;
			हाल fmuls_op:
				func.t = fmuls;
				ftype = S2S;
				अवरोध;
			हाल fभागs_op:
				func.t = fभागs;
				ftype = S2S;
				अवरोध;
			हाल fs1_f2op_op:
				चयन (NDS32Insn_OPCODE_BIT1014(insn)) अणु
				हाल fs2d_op:
					func.b = fs2d;
					ftype = S1D;
					अवरोध;
				हाल fs2si_op:
					func.b = fs2si;
					ftype = S1S;
					अवरोध;
				हाल fs2si_z_op:
					func.b = fs2si_z;
					ftype = S1S;
					अवरोध;
				हाल fs2ui_op:
					func.b = fs2ui;
					ftype = S1S;
					अवरोध;
				हाल fs2ui_z_op:
					func.b = fs2ui_z;
					ftype = S1S;
					अवरोध;
				हाल fsi2s_op:
					func.b = fsi2s;
					ftype = S1S;
					अवरोध;
				हाल fui2s_op:
					func.b = fui2s;
					ftype = S1S;
					अवरोध;
				हाल fवर्ग_मूलs_op:
					func.b = fवर्ग_मूलs;
					ftype = S1S;
					अवरोध;
				शेष:
					वापस संक_अवैध;
				पूर्ण
				अवरोध;
			शेष:
				वापस संक_अवैध;
			पूर्ण
			अवरोध;
		पूर्ण
	हाल fs2_op:
		चयन (NDS32Insn_OPCODE_BIT69(insn)) अणु
		हाल fcmpeqs_op:
		हाल fcmpeqs_e_op:
		हाल fcmplts_op:
		हाल fcmplts_e_op:
		हाल fcmples_op:
		हाल fcmples_e_op:
		हाल fcmpuns_op:
		हाल fcmpuns_e_op:
			ftype = CS;
			अवरोध;
		शेष:
			वापस संक_अवैध;
		पूर्ण
		अवरोध;
	हाल fd1_op:अणु
			चयन (NDS32Insn_OPCODE_BIT69(insn)) अणु
			हाल faddd_op:
				func.t = faddd;
				ftype = D2D;
				अवरोध;
			हाल fsubd_op:
				func.t = fsubd;
				ftype = D2D;
				अवरोध;
			हाल fmaddd_op:
				func.t = fpemu_fmaddd;
				ftype = D2D;
				अवरोध;
			हाल fmsubd_op:
				func.t = fpemu_fmsubd;
				ftype = D2D;
				अवरोध;
			हाल fnmaddd_op:
				func.t = fpemu_fnmaddd;
				ftype = D2D;
				अवरोध;
			हाल fnmsubd_op:
				func.t = fpemu_fnmsubd;
				ftype = D2D;
				अवरोध;
			हाल fmuld_op:
				func.t = fmuld;
				ftype = D2D;
				अवरोध;
			हाल fभागd_op:
				func.t = fभागd;
				ftype = D2D;
				अवरोध;
			हाल fd1_f2op_op:
				चयन (NDS32Insn_OPCODE_BIT1014(insn)) अणु
				हाल fd2s_op:
					func.b = fd2s;
					ftype = D1S;
					अवरोध;
				हाल fd2si_op:
					func.b = fd2si;
					ftype = D1S;
					अवरोध;
				हाल fd2si_z_op:
					func.b = fd2si_z;
					ftype = D1S;
					अवरोध;
				हाल fd2ui_op:
					func.b = fd2ui;
					ftype = D1S;
					अवरोध;
				हाल fd2ui_z_op:
					func.b = fd2ui_z;
					ftype = D1S;
					अवरोध;
				हाल fsi2d_op:
					func.b = fsi2d;
					ftype = D1S;
					अवरोध;
				हाल fui2d_op:
					func.b = fui2d;
					ftype = D1S;
					अवरोध;
				हाल fवर्ग_मूलd_op:
					func.b = fवर्ग_मूलd;
					ftype = D1D;
					अवरोध;
				शेष:
					वापस संक_अवैध;
				पूर्ण
				अवरोध;
			शेष:
				वापस संक_अवैध;

			पूर्ण
			अवरोध;
		पूर्ण

	हाल fd2_op:
		चयन (NDS32Insn_OPCODE_BIT69(insn)) अणु
		हाल fcmpeqd_op:
		हाल fcmpeqd_e_op:
		हाल fcmpltd_op:
		हाल fcmpltd_e_op:
		हाल fcmpled_op:
		हाल fcmpled_e_op:
		हाल fcmpund_op:
		हाल fcmpund_e_op:
			ftype = CD;
			अवरोध;
		शेष:
			वापस संक_अवैध;
		पूर्ण
		अवरोध;

	शेष:
		वापस संक_अवैध;
	पूर्ण

	चयन (ftype) अणु
	हाल S1S:अणु
			व्योम *ft, *fa;

			SPFROMREG(ft, NDS32Insn_OPCODE_Rt(insn));
			SPFROMREG(fa, NDS32Insn_OPCODE_Ra(insn));
			func.b(ft, fa);
			अवरोध;
		पूर्ण
	हाल S2S:अणु
			व्योम *ft, *fa, *fb;

			SPFROMREG(ft, NDS32Insn_OPCODE_Rt(insn));
			SPFROMREG(fa, NDS32Insn_OPCODE_Ra(insn));
			SPFROMREG(fb, NDS32Insn_OPCODE_Rb(insn));
			func.t(ft, fa, fb);
			अवरोध;
		पूर्ण
	हाल S1D:अणु
			व्योम *ft, *fa;

			DPFROMREG(ft, NDS32Insn_OPCODE_Rt(insn));
			SPFROMREG(fa, NDS32Insn_OPCODE_Ra(insn));
			func.b(ft, fa);
			अवरोध;
		पूर्ण
	हाल CS:अणु
			अचिन्हित पूर्णांक cmpop = NDS32Insn_OPCODE_BIT69(insn);
			व्योम *ft, *fa, *fb;

			SPFROMREG(ft, NDS32Insn_OPCODE_Rt(insn));
			SPFROMREG(fa, NDS32Insn_OPCODE_Ra(insn));
			SPFROMREG(fb, NDS32Insn_OPCODE_Rb(insn));
			अगर (cmpop < 0x8) अणु
				cmpop = cmptab[cmpop];
				fcmps(ft, fa, fb, cmpop);
			पूर्ण अन्यथा
				वापस संक_अवैध;
			अवरोध;
		पूर्ण
	हाल D1D:अणु
			व्योम *ft, *fa;

			DPFROMREG(ft, NDS32Insn_OPCODE_Rt(insn));
			DPFROMREG(fa, NDS32Insn_OPCODE_Ra(insn));
			func.b(ft, fa);
			अवरोध;
		पूर्ण
	हाल D2D:अणु
			व्योम *ft, *fa, *fb;

			DPFROMREG(ft, NDS32Insn_OPCODE_Rt(insn));
			DPFROMREG(fa, NDS32Insn_OPCODE_Ra(insn));
			DPFROMREG(fb, NDS32Insn_OPCODE_Rb(insn));
			func.t(ft, fa, fb);
			अवरोध;
		पूर्ण
	हाल D1S:अणु
			व्योम *ft, *fa;

			SPFROMREG(ft, NDS32Insn_OPCODE_Rt(insn));
			DPFROMREG(fa, NDS32Insn_OPCODE_Ra(insn));
			func.b(ft, fa);
			अवरोध;
		पूर्ण
	हाल CD:अणु
			अचिन्हित पूर्णांक cmpop = NDS32Insn_OPCODE_BIT69(insn);
			व्योम *ft, *fa, *fb;

			SPFROMREG(ft, NDS32Insn_OPCODE_Rt(insn));
			DPFROMREG(fa, NDS32Insn_OPCODE_Ra(insn));
			DPFROMREG(fb, NDS32Insn_OPCODE_Rb(insn));
			अगर (cmpop < 0x8) अणु
				cmpop = cmptab[cmpop];
				fcmpd(ft, fa, fb, cmpop);
			पूर्ण अन्यथा
				वापस संक_अवैध;
			अवरोध;
		पूर्ण
	शेष:
		वापस संक_अवैध;
	पूर्ण

	/*
	 * If an exception is required, generate a tidy संक_भ_त्रुटि exception.
	 */
#अगर IS_ENABLED(CONFIG_SUPPORT_DENORMAL_ARITHMETIC)
	अगर (((fpu_reg->fpcsr << 5) & fpu_reg->fpcsr & FPCSR_mskALLE_NO_UDF_IEXE)
	    || ((fpu_reg->fpcsr << 5) & (fpu_reg->UDF_IEX_trap))) अणु
#अन्यथा
	अगर ((fpu_reg->fpcsr << 5) & fpu_reg->fpcsr & FPCSR_mskALLE) अणु
#पूर्ण_अगर
		वापस संक_भ_त्रुटि;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक करो_fpuemu(काष्ठा pt_regs *regs, काष्ठा fpu_काष्ठा *fpu)
अणु
	अचिन्हित दीर्घ insn = 0, addr = regs->ipc;
	अचिन्हित दीर्घ emulpc, contpc;
	अचिन्हित अक्षर *pc = (व्योम *)&insn;
	अक्षर c;
	पूर्णांक i = 0, ret;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (__get_user(c, (अचिन्हित अक्षर *)addr++))
			वापस SIGBUS;
		*pc++ = c;
	पूर्ण

	insn = be32_to_cpu(insn);

	emulpc = regs->ipc;
	contpc = regs->ipc + 4;

	अगर (NDS32Insn_OPCODE(insn) != cop0_op)
		वापस संक_अवैध;

	चयन (NDS32Insn_OPCODE_COP0(insn)) अणु
	हाल fs1_op:
	हाल fs2_op:
	हाल fd1_op:
	हाल fd2_op:
		अणु
			/* a real fpu computation inकाष्ठाion */
			ret = fpu_emu(fpu, insn);
			अगर (!ret)
				regs->ipc = contpc;
		पूर्ण
		अवरोध;

	शेष:
		वापस संक_अवैध;
	पूर्ण

	वापस ret;
पूर्ण
