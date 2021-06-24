<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cp1emu.c: a MIPS coprocessor 1 (FPU) inकाष्ठाion emulator
 *
 * MIPS भग्नing poपूर्णांक support
 * Copyright (C) 1994-2000 Algorithmics Ltd.
 *
 * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000  MIPS Technologies, Inc.
 *
 * A complete emulator क्रम MIPS coprocessor 1 inकाष्ठाions.  This is
 * required क्रम #भग्न(चयन) or #भग्न(trap), where it catches all
 * COP1 inकाष्ठाions via the "CoProcessor Unusable" exception.
 *
 * More surprisingly it is also required क्रम #भग्न(ieee), to help out
 * the hardware FPU at the boundaries of the IEEE-754 representation
 * (denormalised values, infinities, underflow, etc).  It is made
 * quite nasty because emulation of some non-COP1 inकाष्ठाions is
 * required, e.g. in branch delay slots.
 *
 * Note अगर you know that you won't have an FPU, then you'll get much
 * better perक्रमmance by compiling with -msoft-भग्न!
 */
#समावेश <linux/sched.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/percpu-defs.h>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/संकेत.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/cpu-info.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/fpu_emulator.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/mips-r2-to-r6-emul.h>

#समावेश "ieee754.h"

/* Function which emulates a भग्नing poपूर्णांक inकाष्ठाion. */

अटल पूर्णांक fpu_emu(काष्ठा pt_regs *, काष्ठा mips_fpu_काष्ठा *,
	mips_inकाष्ठाion);

अटल पूर्णांक fpux_emu(काष्ठा pt_regs *,
	काष्ठा mips_fpu_काष्ठा *, mips_inकाष्ठाion, व्योम __user **);

/* Control रेजिस्टरs */

#घोषणा FPCREG_RID	0	/* $0  = revision id */
#घोषणा FPCREG_FCCR	25	/* $25 = fccr */
#घोषणा FPCREG_FEXR	26	/* $26 = fexr */
#घोषणा FPCREG_FENR	28	/* $28 = fenr */
#घोषणा FPCREG_CSR	31	/* $31 = csr */

/* convert condition code रेजिस्टर number to csr bit */
स्थिर अचिन्हित पूर्णांक fpucondbit[8] = अणु
	FPU_CSR_COND,
	FPU_CSR_COND1,
	FPU_CSR_COND2,
	FPU_CSR_COND3,
	FPU_CSR_COND4,
	FPU_CSR_COND5,
	FPU_CSR_COND6,
	FPU_CSR_COND7
पूर्ण;

/* (microMIPS) Convert certain microMIPS inकाष्ठाions to MIPS32 क्रमmat. */
अटल स्थिर पूर्णांक sd_क्रमmat[] = अणु16, 17, 0, 0, 0, 0, 0, 0पूर्ण;
अटल स्थिर पूर्णांक sdps_क्रमmat[] = अणु16, 17, 22, 0, 0, 0, 0, 0पूर्ण;
अटल स्थिर पूर्णांक dwl_क्रमmat[] = अणु17, 20, 21, 0, 0, 0, 0, 0पूर्ण;
अटल स्थिर पूर्णांक swl_क्रमmat[] = अणु16, 20, 21, 0, 0, 0, 0, 0पूर्ण;

/*
 * This functions translates a 32-bit microMIPS inकाष्ठाion
 * पूर्णांकo a 32-bit MIPS32 inकाष्ठाion. Returns 0 on success
 * and संक_अवैध otherwise.
 */
अटल पूर्णांक microMIPS32_to_MIPS32(जोड़ mips_inकाष्ठाion *insn_ptr)
अणु
	जोड़ mips_inकाष्ठाion insn = *insn_ptr;
	जोड़ mips_inकाष्ठाion mips32_insn = insn;
	पूर्णांक func, fmt, op;

	चयन (insn.mm_i_क्रमmat.opcode) अणु
	हाल mm_ldc132_op:
		mips32_insn.mm_i_क्रमmat.opcode = ldc1_op;
		mips32_insn.mm_i_क्रमmat.rt = insn.mm_i_क्रमmat.rs;
		mips32_insn.mm_i_क्रमmat.rs = insn.mm_i_क्रमmat.rt;
		अवरोध;
	हाल mm_lwc132_op:
		mips32_insn.mm_i_क्रमmat.opcode = lwc1_op;
		mips32_insn.mm_i_क्रमmat.rt = insn.mm_i_क्रमmat.rs;
		mips32_insn.mm_i_क्रमmat.rs = insn.mm_i_क्रमmat.rt;
		अवरोध;
	हाल mm_sdc132_op:
		mips32_insn.mm_i_क्रमmat.opcode = sdc1_op;
		mips32_insn.mm_i_क्रमmat.rt = insn.mm_i_क्रमmat.rs;
		mips32_insn.mm_i_क्रमmat.rs = insn.mm_i_क्रमmat.rt;
		अवरोध;
	हाल mm_swc132_op:
		mips32_insn.mm_i_क्रमmat.opcode = swc1_op;
		mips32_insn.mm_i_क्रमmat.rt = insn.mm_i_क्रमmat.rs;
		mips32_insn.mm_i_क्रमmat.rs = insn.mm_i_क्रमmat.rt;
		अवरोध;
	हाल mm_pool32i_op:
		/* NOTE: offset is << by 1 अगर in microMIPS mode. */
		अगर ((insn.mm_i_क्रमmat.rt == mm_bc1f_op) ||
		    (insn.mm_i_क्रमmat.rt == mm_bc1t_op)) अणु
			mips32_insn.fb_क्रमmat.opcode = cop1_op;
			mips32_insn.fb_क्रमmat.bc = bc_op;
			mips32_insn.fb_क्रमmat.flag =
				(insn.mm_i_क्रमmat.rt == mm_bc1t_op) ? 1 : 0;
		पूर्ण अन्यथा
			वापस संक_अवैध;
		अवरोध;
	हाल mm_pool32f_op:
		चयन (insn.mm_fp0_क्रमmat.func) अणु
		हाल mm_32f_01_op:
		हाल mm_32f_11_op:
		हाल mm_32f_02_op:
		हाल mm_32f_12_op:
		हाल mm_32f_41_op:
		हाल mm_32f_51_op:
		हाल mm_32f_42_op:
		हाल mm_32f_52_op:
			op = insn.mm_fp0_क्रमmat.func;
			अगर (op == mm_32f_01_op)
				func = madd_s_op;
			अन्यथा अगर (op == mm_32f_11_op)
				func = madd_d_op;
			अन्यथा अगर (op == mm_32f_02_op)
				func = nmadd_s_op;
			अन्यथा अगर (op == mm_32f_12_op)
				func = nmadd_d_op;
			अन्यथा अगर (op == mm_32f_41_op)
				func = msub_s_op;
			अन्यथा अगर (op == mm_32f_51_op)
				func = msub_d_op;
			अन्यथा अगर (op == mm_32f_42_op)
				func = nmsub_s_op;
			अन्यथा
				func = nmsub_d_op;
			mips32_insn.fp6_क्रमmat.opcode = cop1x_op;
			mips32_insn.fp6_क्रमmat.fr = insn.mm_fp6_क्रमmat.fr;
			mips32_insn.fp6_क्रमmat.ft = insn.mm_fp6_क्रमmat.ft;
			mips32_insn.fp6_क्रमmat.fs = insn.mm_fp6_क्रमmat.fs;
			mips32_insn.fp6_क्रमmat.fd = insn.mm_fp6_क्रमmat.fd;
			mips32_insn.fp6_क्रमmat.func = func;
			अवरोध;
		हाल mm_32f_10_op:
			func = -1;	/* Invalid */
			op = insn.mm_fp5_क्रमmat.op & 0x7;
			अगर (op == mm_ldxc1_op)
				func = ldxc1_op;
			अन्यथा अगर (op == mm_sdxc1_op)
				func = sdxc1_op;
			अन्यथा अगर (op == mm_lwxc1_op)
				func = lwxc1_op;
			अन्यथा अगर (op == mm_swxc1_op)
				func = swxc1_op;

			अगर (func != -1) अणु
				mips32_insn.r_क्रमmat.opcode = cop1x_op;
				mips32_insn.r_क्रमmat.rs =
					insn.mm_fp5_क्रमmat.base;
				mips32_insn.r_क्रमmat.rt =
					insn.mm_fp5_क्रमmat.index;
				mips32_insn.r_क्रमmat.rd = 0;
				mips32_insn.r_क्रमmat.re = insn.mm_fp5_क्रमmat.fd;
				mips32_insn.r_क्रमmat.func = func;
			पूर्ण अन्यथा
				वापस संक_अवैध;
			अवरोध;
		हाल mm_32f_40_op:
			op = -1;	/* Invalid */
			अगर (insn.mm_fp2_क्रमmat.op == mm_fmovt_op)
				op = 1;
			अन्यथा अगर (insn.mm_fp2_क्रमmat.op == mm_fmovf_op)
				op = 0;
			अगर (op != -1) अणु
				mips32_insn.fp0_क्रमmat.opcode = cop1_op;
				mips32_insn.fp0_क्रमmat.fmt =
					sdps_क्रमmat[insn.mm_fp2_क्रमmat.fmt];
				mips32_insn.fp0_क्रमmat.ft =
					(insn.mm_fp2_क्रमmat.cc<<2) + op;
				mips32_insn.fp0_क्रमmat.fs =
					insn.mm_fp2_क्रमmat.fs;
				mips32_insn.fp0_क्रमmat.fd =
					insn.mm_fp2_क्रमmat.fd;
				mips32_insn.fp0_क्रमmat.func = fmovc_op;
			पूर्ण अन्यथा
				वापस संक_अवैध;
			अवरोध;
		हाल mm_32f_60_op:
			func = -1;	/* Invalid */
			अगर (insn.mm_fp0_क्रमmat.op == mm_fadd_op)
				func = fadd_op;
			अन्यथा अगर (insn.mm_fp0_क्रमmat.op == mm_fsub_op)
				func = fsub_op;
			अन्यथा अगर (insn.mm_fp0_क्रमmat.op == mm_fmul_op)
				func = fmul_op;
			अन्यथा अगर (insn.mm_fp0_क्रमmat.op == mm_fभाग_op)
				func = fभाग_op;
			अगर (func != -1) अणु
				mips32_insn.fp0_क्रमmat.opcode = cop1_op;
				mips32_insn.fp0_क्रमmat.fmt =
					sdps_क्रमmat[insn.mm_fp0_क्रमmat.fmt];
				mips32_insn.fp0_क्रमmat.ft =
					insn.mm_fp0_क्रमmat.ft;
				mips32_insn.fp0_क्रमmat.fs =
					insn.mm_fp0_क्रमmat.fs;
				mips32_insn.fp0_क्रमmat.fd =
					insn.mm_fp0_क्रमmat.fd;
				mips32_insn.fp0_क्रमmat.func = func;
			पूर्ण अन्यथा
				वापस संक_अवैध;
			अवरोध;
		हाल mm_32f_70_op:
			func = -1;	/* Invalid */
			अगर (insn.mm_fp0_क्रमmat.op == mm_fmovn_op)
				func = fmovn_op;
			अन्यथा अगर (insn.mm_fp0_क्रमmat.op == mm_fmovz_op)
				func = fmovz_op;
			अगर (func != -1) अणु
				mips32_insn.fp0_क्रमmat.opcode = cop1_op;
				mips32_insn.fp0_क्रमmat.fmt =
					sdps_क्रमmat[insn.mm_fp0_क्रमmat.fmt];
				mips32_insn.fp0_क्रमmat.ft =
					insn.mm_fp0_क्रमmat.ft;
				mips32_insn.fp0_क्रमmat.fs =
					insn.mm_fp0_क्रमmat.fs;
				mips32_insn.fp0_क्रमmat.fd =
					insn.mm_fp0_क्रमmat.fd;
				mips32_insn.fp0_क्रमmat.func = func;
			पूर्ण अन्यथा
				वापस संक_अवैध;
			अवरोध;
		हाल mm_32f_73_op:    /* POOL32FXF */
			चयन (insn.mm_fp1_क्रमmat.op) अणु
			हाल mm_movf0_op:
			हाल mm_movf1_op:
			हाल mm_movt0_op:
			हाल mm_movt1_op:
				अगर ((insn.mm_fp1_क्रमmat.op & 0x7f) ==
				    mm_movf0_op)
					op = 0;
				अन्यथा
					op = 1;
				mips32_insn.r_क्रमmat.opcode = spec_op;
				mips32_insn.r_क्रमmat.rs = insn.mm_fp4_क्रमmat.fs;
				mips32_insn.r_क्रमmat.rt =
					(insn.mm_fp4_क्रमmat.cc << 2) + op;
				mips32_insn.r_क्रमmat.rd = insn.mm_fp4_क्रमmat.rt;
				mips32_insn.r_क्रमmat.re = 0;
				mips32_insn.r_क्रमmat.func = movc_op;
				अवरोध;
			हाल mm_fcvtd0_op:
			हाल mm_fcvtd1_op:
			हाल mm_fcvts0_op:
			हाल mm_fcvts1_op:
				अगर ((insn.mm_fp1_क्रमmat.op & 0x7f) ==
				    mm_fcvtd0_op) अणु
					func = fcvtd_op;
					fmt = swl_क्रमmat[insn.mm_fp3_क्रमmat.fmt];
				पूर्ण अन्यथा अणु
					func = fcvts_op;
					fmt = dwl_क्रमmat[insn.mm_fp3_क्रमmat.fmt];
				पूर्ण
				mips32_insn.fp0_क्रमmat.opcode = cop1_op;
				mips32_insn.fp0_क्रमmat.fmt = fmt;
				mips32_insn.fp0_क्रमmat.ft = 0;
				mips32_insn.fp0_क्रमmat.fs =
					insn.mm_fp3_क्रमmat.fs;
				mips32_insn.fp0_क्रमmat.fd =
					insn.mm_fp3_क्रमmat.rt;
				mips32_insn.fp0_क्रमmat.func = func;
				अवरोध;
			हाल mm_fmov0_op:
			हाल mm_fmov1_op:
			हाल mm_भ_असल0_op:
			हाल mm_भ_असल1_op:
			हाल mm_fneg0_op:
			हाल mm_fneg1_op:
				अगर ((insn.mm_fp1_क्रमmat.op & 0x7f) ==
				    mm_fmov0_op)
					func = fmov_op;
				अन्यथा अगर ((insn.mm_fp1_क्रमmat.op & 0x7f) ==
					 mm_भ_असल0_op)
					func = भ_असल_op;
				अन्यथा
					func = fneg_op;
				mips32_insn.fp0_क्रमmat.opcode = cop1_op;
				mips32_insn.fp0_क्रमmat.fmt =
					sdps_क्रमmat[insn.mm_fp3_क्रमmat.fmt];
				mips32_insn.fp0_क्रमmat.ft = 0;
				mips32_insn.fp0_क्रमmat.fs =
					insn.mm_fp3_क्रमmat.fs;
				mips32_insn.fp0_क्रमmat.fd =
					insn.mm_fp3_क्रमmat.rt;
				mips32_insn.fp0_क्रमmat.func = func;
				अवरोध;
			हाल mm_fन्यूनमानl_op:
			हाल mm_fन्यूनमानw_op:
			हाल mm_fउच्चमानl_op:
			हाल mm_fउच्चमानw_op:
			हाल mm_ftruncl_op:
			हाल mm_ftruncw_op:
			हाल mm_froundl_op:
			हाल mm_froundw_op:
			हाल mm_fcvtl_op:
			हाल mm_fcvtw_op:
				अगर (insn.mm_fp1_क्रमmat.op == mm_fन्यूनमानl_op)
					func = fन्यूनमानl_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_fन्यूनमानw_op)
					func = fन्यूनमान_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_fउच्चमानl_op)
					func = fउच्चमानl_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_fउच्चमानw_op)
					func = fउच्चमान_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_ftruncl_op)
					func = ftruncl_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_ftruncw_op)
					func = ftrunc_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_froundl_op)
					func = froundl_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_froundw_op)
					func = fround_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_fcvtl_op)
					func = fcvtl_op;
				अन्यथा
					func = fcvtw_op;
				mips32_insn.fp0_क्रमmat.opcode = cop1_op;
				mips32_insn.fp0_क्रमmat.fmt =
					sd_क्रमmat[insn.mm_fp1_क्रमmat.fmt];
				mips32_insn.fp0_क्रमmat.ft = 0;
				mips32_insn.fp0_क्रमmat.fs =
					insn.mm_fp1_क्रमmat.fs;
				mips32_insn.fp0_क्रमmat.fd =
					insn.mm_fp1_क्रमmat.rt;
				mips32_insn.fp0_क्रमmat.func = func;
				अवरोध;
			हाल mm_frवर्ग_मूल_op:
			हाल mm_fवर्ग_मूल_op:
			हाल mm_frecip_op:
				अगर (insn.mm_fp1_क्रमmat.op == mm_frवर्ग_मूल_op)
					func = frवर्ग_मूल_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_fवर्ग_मूल_op)
					func = fवर्ग_मूल_op;
				अन्यथा
					func = frecip_op;
				mips32_insn.fp0_क्रमmat.opcode = cop1_op;
				mips32_insn.fp0_क्रमmat.fmt =
					sdps_क्रमmat[insn.mm_fp1_क्रमmat.fmt];
				mips32_insn.fp0_क्रमmat.ft = 0;
				mips32_insn.fp0_क्रमmat.fs =
					insn.mm_fp1_क्रमmat.fs;
				mips32_insn.fp0_क्रमmat.fd =
					insn.mm_fp1_क्रमmat.rt;
				mips32_insn.fp0_क्रमmat.func = func;
				अवरोध;
			हाल mm_mfc1_op:
			हाल mm_mtc1_op:
			हाल mm_cfc1_op:
			हाल mm_ctc1_op:
			हाल mm_mfhc1_op:
			हाल mm_mthc1_op:
				अगर (insn.mm_fp1_क्रमmat.op == mm_mfc1_op)
					op = mfc_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_mtc1_op)
					op = mtc_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_cfc1_op)
					op = cfc_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_ctc1_op)
					op = ctc_op;
				अन्यथा अगर (insn.mm_fp1_क्रमmat.op == mm_mfhc1_op)
					op = mfhc_op;
				अन्यथा
					op = mthc_op;
				mips32_insn.fp1_क्रमmat.opcode = cop1_op;
				mips32_insn.fp1_क्रमmat.op = op;
				mips32_insn.fp1_क्रमmat.rt =
					insn.mm_fp1_क्रमmat.rt;
				mips32_insn.fp1_क्रमmat.fs =
					insn.mm_fp1_क्रमmat.fs;
				mips32_insn.fp1_क्रमmat.fd = 0;
				mips32_insn.fp1_क्रमmat.func = 0;
				अवरोध;
			शेष:
				वापस संक_अवैध;
			पूर्ण
			अवरोध;
		हाल mm_32f_74_op:	/* c.cond.fmt */
			mips32_insn.fp0_क्रमmat.opcode = cop1_op;
			mips32_insn.fp0_क्रमmat.fmt =
				sdps_क्रमmat[insn.mm_fp4_क्रमmat.fmt];
			mips32_insn.fp0_क्रमmat.ft = insn.mm_fp4_क्रमmat.rt;
			mips32_insn.fp0_क्रमmat.fs = insn.mm_fp4_क्रमmat.fs;
			mips32_insn.fp0_क्रमmat.fd = insn.mm_fp4_क्रमmat.cc << 2;
			mips32_insn.fp0_क्रमmat.func =
				insn.mm_fp4_क्रमmat.cond | MM_MIPS32_COND_FC;
			अवरोध;
		शेष:
			वापस संक_अवैध;
		पूर्ण
		अवरोध;
	शेष:
		वापस संक_अवैध;
	पूर्ण

	*insn_ptr = mips32_insn;
	वापस 0;
पूर्ण

/*
 * Redundant with logic alपढ़ोy in kernel/branch.c,
 * embedded in compute_वापस_epc.  At some poपूर्णांक,
 * a single subroutine should be used across both
 * modules.
 */
पूर्णांक isBranchInstr(काष्ठा pt_regs *regs, काष्ठा mm_decoded_insn dec_insn,
		  अचिन्हित दीर्घ *contpc)
अणु
	जोड़ mips_inकाष्ठाion insn = (जोड़ mips_inकाष्ठाion)dec_insn.insn;
	अचिन्हित पूर्णांक fcr31;
	अचिन्हित पूर्णांक bit = 0;
	अचिन्हित पूर्णांक bit0;
	जोड़ fpureg *fpr;

	चयन (insn.i_क्रमmat.opcode) अणु
	हाल spec_op:
		चयन (insn.r_क्रमmat.func) अणु
		हाल jalr_op:
			अगर (insn.r_क्रमmat.rd != 0) अणु
				regs->regs[insn.r_क्रमmat.rd] =
					regs->cp0_epc + dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			पूर्ण
			fallthrough;
		हाल jr_op:
			/* For R6, JR alपढ़ोy emulated in jalr_op */
			अगर (NO_R6EMU && insn.r_क्रमmat.func == jr_op)
				अवरोध;
			*contpc = regs->regs[insn.r_क्रमmat.rs];
			वापस 1;
		पूर्ण
		अवरोध;
	हाल bcond_op:
		चयन (insn.i_क्रमmat.rt) अणु
		हाल bltzal_op:
		हाल bltzall_op:
			अगर (NO_R6EMU && (insn.i_क्रमmat.rs ||
			    insn.i_क्रमmat.rt == bltzall_op))
				अवरोध;

			regs->regs[31] = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
			fallthrough;
		हाल bltzl_op:
			अगर (NO_R6EMU)
				अवरोध;
			fallthrough;
		हाल bltz_op:
			अगर ((दीर्घ)regs->regs[insn.i_क्रमmat.rs] < 0)
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					(insn.i_क्रमmat.simmediate << 2);
			अन्यथा
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			वापस 1;
		हाल bgezal_op:
		हाल bgezall_op:
			अगर (NO_R6EMU && (insn.i_क्रमmat.rs ||
			    insn.i_क्रमmat.rt == bgezall_op))
				अवरोध;

			regs->regs[31] = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
			fallthrough;
		हाल bgezl_op:
			अगर (NO_R6EMU)
				अवरोध;
			fallthrough;
		हाल bgez_op:
			अगर ((दीर्घ)regs->regs[insn.i_क्रमmat.rs] >= 0)
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					(insn.i_क्रमmat.simmediate << 2);
			अन्यथा
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			वापस 1;
		पूर्ण
		अवरोध;
	हाल jalx_op:
		set_isa16_mode(bit);
		fallthrough;
	हाल jal_op:
		regs->regs[31] = regs->cp0_epc +
			dec_insn.pc_inc +
			dec_insn.next_pc_inc;
		fallthrough;
	हाल j_op:
		*contpc = regs->cp0_epc + dec_insn.pc_inc;
		*contpc >>= 28;
		*contpc <<= 28;
		*contpc |= (insn.j_क्रमmat.target << 2);
		/* Set microMIPS mode bit: XOR क्रम jalx. */
		*contpc ^= bit;
		वापस 1;
	हाल beql_op:
		अगर (NO_R6EMU)
			अवरोध;
		fallthrough;
	हाल beq_op:
		अगर (regs->regs[insn.i_क्रमmat.rs] ==
		    regs->regs[insn.i_क्रमmat.rt])
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				(insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
		वापस 1;
	हाल bnel_op:
		अगर (NO_R6EMU)
			अवरोध;
		fallthrough;
	हाल bne_op:
		अगर (regs->regs[insn.i_क्रमmat.rs] !=
		    regs->regs[insn.i_क्रमmat.rt])
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				(insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
		वापस 1;
	हाल blezl_op:
		अगर (!insn.i_क्रमmat.rt && NO_R6EMU)
			अवरोध;
		fallthrough;
	हाल blez_op:

		/*
		 * Compact branches क्रम R6 क्रम the
		 * blez and blezl opcodes.
		 * BLEZ  | rs = 0 | rt != 0  == BLEZALC
		 * BLEZ  | rs = rt != 0      == BGEZALC
		 * BLEZ  | rs != 0 | rt != 0 == BGEUC
		 * BLEZL | rs = 0 | rt != 0  == BLEZC
		 * BLEZL | rs = rt != 0      == BGEZC
		 * BLEZL | rs != 0 | rt != 0 == BGEC
		 *
		 * For real BLEZअणु,Lपूर्ण, rt is always 0.
		 */
		अगर (cpu_has_mips_r6 && insn.i_क्रमmat.rt) अणु
			अगर ((insn.i_क्रमmat.opcode == blez_op) &&
			    ((!insn.i_क्रमmat.rs && insn.i_क्रमmat.rt) ||
			     (insn.i_क्रमmat.rs == insn.i_क्रमmat.rt)))
				regs->regs[31] = regs->cp0_epc +
					dec_insn.pc_inc;
			*contpc = regs->cp0_epc + dec_insn.pc_inc +
				dec_insn.next_pc_inc;

			वापस 1;
		पूर्ण
		अगर ((दीर्घ)regs->regs[insn.i_क्रमmat.rs] <= 0)
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				(insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
		वापस 1;
	हाल bgtzl_op:
		अगर (!insn.i_क्रमmat.rt && NO_R6EMU)
			अवरोध;
		fallthrough;
	हाल bgtz_op:
		/*
		 * Compact branches क्रम R6 क्रम the
		 * bgtz and bgtzl opcodes.
		 * BGTZ  | rs = 0 | rt != 0  == BGTZALC
		 * BGTZ  | rs = rt != 0      == BLTZALC
		 * BGTZ  | rs != 0 | rt != 0 == BLTUC
		 * BGTZL | rs = 0 | rt != 0  == BGTZC
		 * BGTZL | rs = rt != 0      == BLTZC
		 * BGTZL | rs != 0 | rt != 0 == BLTC
		 *
		 * *ZALC varपूर्णांक क्रम BGTZ &&& rt != 0
		 * For real GTZअणु,Lपूर्ण, rt is always 0.
		 */
		अगर (cpu_has_mips_r6 && insn.i_क्रमmat.rt) अणु
			अगर ((insn.i_क्रमmat.opcode == blez_op) &&
			    ((!insn.i_क्रमmat.rs && insn.i_क्रमmat.rt) ||
			     (insn.i_क्रमmat.rs == insn.i_क्रमmat.rt)))
				regs->regs[31] = regs->cp0_epc +
					dec_insn.pc_inc;
			*contpc = regs->cp0_epc + dec_insn.pc_inc +
				dec_insn.next_pc_inc;

			वापस 1;
		पूर्ण

		अगर ((दीर्घ)regs->regs[insn.i_क्रमmat.rs] > 0)
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				(insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
		वापस 1;
	हाल pop10_op:
	हाल pop30_op:
		अगर (!cpu_has_mips_r6)
			अवरोध;
		अगर (insn.i_क्रमmat.rt && !insn.i_क्रमmat.rs)
			regs->regs[31] = regs->cp0_epc + 4;
		*contpc = regs->cp0_epc + dec_insn.pc_inc +
			dec_insn.next_pc_inc;

		वापस 1;
#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
	हाल lwc2_op: /* This is bbit0 on Octeon */
		अगर ((regs->regs[insn.i_क्रमmat.rs] & (1ull<<insn.i_क्रमmat.rt)) == 0)
			*contpc = regs->cp0_epc + 4 + (insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			*contpc = regs->cp0_epc + 8;
		वापस 1;
	हाल ldc2_op: /* This is bbit032 on Octeon */
		अगर ((regs->regs[insn.i_क्रमmat.rs] & (1ull<<(insn.i_क्रमmat.rt + 32))) == 0)
			*contpc = regs->cp0_epc + 4 + (insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			*contpc = regs->cp0_epc + 8;
		वापस 1;
	हाल swc2_op: /* This is bbit1 on Octeon */
		अगर (regs->regs[insn.i_क्रमmat.rs] & (1ull<<insn.i_क्रमmat.rt))
			*contpc = regs->cp0_epc + 4 + (insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			*contpc = regs->cp0_epc + 8;
		वापस 1;
	हाल sdc2_op: /* This is bbit132 on Octeon */
		अगर (regs->regs[insn.i_क्रमmat.rs] & (1ull<<(insn.i_क्रमmat.rt + 32)))
			*contpc = regs->cp0_epc + 4 + (insn.i_क्रमmat.simmediate << 2);
		अन्यथा
			*contpc = regs->cp0_epc + 8;
		वापस 1;
#अन्यथा
	हाल bc6_op:
		/*
		 * Only valid क्रम MIPS R6 but we can still end up
		 * here from a broken userland so just tell emulator
		 * this is not a branch and let it अवरोध later on.
		 */
		अगर  (!cpu_has_mips_r6)
			अवरोध;
		*contpc = regs->cp0_epc + dec_insn.pc_inc +
			dec_insn.next_pc_inc;

		वापस 1;
	हाल balc6_op:
		अगर (!cpu_has_mips_r6)
			अवरोध;
		regs->regs[31] = regs->cp0_epc + 4;
		*contpc = regs->cp0_epc + dec_insn.pc_inc +
			dec_insn.next_pc_inc;

		वापस 1;
	हाल pop66_op:
		अगर (!cpu_has_mips_r6)
			अवरोध;
		*contpc = regs->cp0_epc + dec_insn.pc_inc +
			dec_insn.next_pc_inc;

		वापस 1;
	हाल pop76_op:
		अगर (!cpu_has_mips_r6)
			अवरोध;
		अगर (!insn.i_क्रमmat.rs)
			regs->regs[31] = regs->cp0_epc + 4;
		*contpc = regs->cp0_epc + dec_insn.pc_inc +
			dec_insn.next_pc_inc;

		वापस 1;
#पूर्ण_अगर
	हाल cop0_op:
	हाल cop1_op:
		/* Need to check क्रम R6 bc1nez and bc1eqz branches */
		अगर (cpu_has_mips_r6 &&
		    ((insn.i_क्रमmat.rs == bc1eqz_op) ||
		     (insn.i_क्रमmat.rs == bc1nez_op))) अणु
			bit = 0;
			fpr = &current->thपढ़ो.fpu.fpr[insn.i_क्रमmat.rt];
			bit0 = get_fpr32(fpr, 0) & 0x1;
			चयन (insn.i_क्रमmat.rs) अणु
			हाल bc1eqz_op:
				bit = bit0 == 0;
				अवरोध;
			हाल bc1nez_op:
				bit = bit0 != 0;
				अवरोध;
			पूर्ण
			अगर (bit)
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					(insn.i_क्रमmat.simmediate << 2);
			अन्यथा
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;

			वापस 1;
		पूर्ण
		/* R2/R6 compatible cop1 inकाष्ठाion */
		fallthrough;
	हाल cop2_op:
	हाल cop1x_op:
		अगर (insn.i_क्रमmat.rs == bc_op) अणु
			preempt_disable();
			अगर (is_fpu_owner())
			        fcr31 = पढ़ो_32bit_cp1_रेजिस्टर(CP1_STATUS);
			अन्यथा
				fcr31 = current->thपढ़ो.fpu.fcr31;
			preempt_enable();

			bit = (insn.i_क्रमmat.rt >> 2);
			bit += (bit != 0);
			bit += 23;
			चयन (insn.i_क्रमmat.rt & 3) अणु
			हाल 0:	/* bc1f */
			हाल 2:	/* bc1fl */
				अगर (~fcr31 & (1 << bit))
					*contpc = regs->cp0_epc +
						dec_insn.pc_inc +
						(insn.i_क्रमmat.simmediate << 2);
				अन्यथा
					*contpc = regs->cp0_epc +
						dec_insn.pc_inc +
						dec_insn.next_pc_inc;
				वापस 1;
			हाल 1:	/* bc1t */
			हाल 3:	/* bc1tl */
				अगर (fcr31 & (1 << bit))
					*contpc = regs->cp0_epc +
						dec_insn.pc_inc +
						(insn.i_क्रमmat.simmediate << 2);
				अन्यथा
					*contpc = regs->cp0_epc +
						dec_insn.pc_inc +
						dec_insn.next_pc_inc;
				वापस 1;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * In the Linux kernel, we support selection of FPR क्रमmat on the
 * basis of the Status.FR bit.	If an FPU is not present, the FR bit
 * is hardwired to zero, which would imply a 32-bit FPU even क्रम
 * 64-bit CPUs so we rather look at TIF_32BIT_FPREGS.
 * FPU emu is slow and bulky and optimizing this function offers fairly
 * sizeable benefits so we try to be clever and make this function वापस
 * a स्थिरant whenever possible, that is on 64-bit kernels without O32
 * compatibility enabled and on 32-bit without 64-bit FPU support.
 */
अटल अंतरभूत पूर्णांक cop1_64bit(काष्ठा pt_regs *xcp)
अणु
	अगर (IS_ENABLED(CONFIG_64BIT) && !IS_ENABLED(CONFIG_MIPS32_O32))
		वापस 1;
	अन्यथा अगर (IS_ENABLED(CONFIG_32BIT) &&
		 !IS_ENABLED(CONFIG_MIPS_O32_FP64_SUPPORT))
		वापस 0;

	वापस !test_thपढ़ो_flag(TIF_32BIT_FPREGS);
पूर्ण

अटल अंतरभूत bool hybrid_fprs(व्योम)
अणु
	वापस test_thपढ़ो_flag(TIF_HYBRID_FPREGS);
पूर्ण

#घोषणा SIFROMREG(si, x)						\
करो अणु									\
	अगर (cop1_64bit(xcp) && !hybrid_fprs())				\
		(si) = (पूर्णांक)get_fpr32(&ctx->fpr[x], 0);			\
	अन्यथा								\
		(si) = (पूर्णांक)get_fpr32(&ctx->fpr[(x) & ~1], (x) & 1);	\
पूर्ण जबतक (0)

#घोषणा SITOREG(si, x)							\
करो अणु									\
	अगर (cop1_64bit(xcp) && !hybrid_fprs()) अणु			\
		अचिन्हित पूर्णांक i;						\
		set_fpr32(&ctx->fpr[x], 0, si);				\
		क्रम (i = 1; i < ARRAY_SIZE(ctx->fpr[x].val32); i++)	\
			set_fpr32(&ctx->fpr[x], i, 0);			\
	पूर्ण अन्यथा अणु							\
		set_fpr32(&ctx->fpr[(x) & ~1], (x) & 1, si);		\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा SIFROMHREG(si, x)	((si) = (पूर्णांक)get_fpr32(&ctx->fpr[x], 1))

#घोषणा SITOHREG(si, x)							\
करो अणु									\
	अचिन्हित पूर्णांक i;							\
	set_fpr32(&ctx->fpr[x], 1, si);					\
	क्रम (i = 2; i < ARRAY_SIZE(ctx->fpr[x].val32); i++)		\
		set_fpr32(&ctx->fpr[x], i, 0);				\
पूर्ण जबतक (0)

#घोषणा DIFROMREG(di, x)						\
	((di) = get_fpr64(&ctx->fpr[(x) & ~(cop1_64bit(xcp) ^ 1)], 0))

#घोषणा DITOREG(di, x)							\
करो अणु									\
	अचिन्हित पूर्णांक fpr, i;						\
	fpr = (x) & ~(cop1_64bit(xcp) ^ 1);				\
	set_fpr64(&ctx->fpr[fpr], 0, di);				\
	क्रम (i = 1; i < ARRAY_SIZE(ctx->fpr[x].val64); i++)		\
		set_fpr64(&ctx->fpr[fpr], i, 0);			\
पूर्ण जबतक (0)

#घोषणा SPFROMREG(sp, x) SIFROMREG((sp).bits, x)
#घोषणा SPTOREG(sp, x)	SITOREG((sp).bits, x)
#घोषणा DPFROMREG(dp, x)	DIFROMREG((dp).bits, x)
#घोषणा DPTOREG(dp, x)	DITOREG((dp).bits, x)

/*
 * Emulate a CFC1 inकाष्ठाion.
 */
अटल अंतरभूत व्योम cop1_cfc(काष्ठा pt_regs *xcp, काष्ठा mips_fpu_काष्ठा *ctx,
			    mips_inकाष्ठाion ir)
अणु
	u32 fcr31 = ctx->fcr31;
	u32 value = 0;

	चयन (MIPSInst_RD(ir)) अणु
	हाल FPCREG_CSR:
		value = fcr31;
		pr_debug("%p gpr[%d]<-csr=%08x\n",
			 (व्योम *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		अवरोध;

	हाल FPCREG_FENR:
		अगर (!cpu_has_mips_r)
			अवरोध;
		value = (fcr31 >> (FPU_CSR_FS_S - MIPS_FENR_FS_S)) &
			MIPS_FENR_FS;
		value |= fcr31 & (FPU_CSR_ALL_E | FPU_CSR_RM);
		pr_debug("%p gpr[%d]<-enr=%08x\n",
			 (व्योम *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		अवरोध;

	हाल FPCREG_FEXR:
		अगर (!cpu_has_mips_r)
			अवरोध;
		value = fcr31 & (FPU_CSR_ALL_X | FPU_CSR_ALL_S);
		pr_debug("%p gpr[%d]<-exr=%08x\n",
			 (व्योम *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		अवरोध;

	हाल FPCREG_FCCR:
		अगर (!cpu_has_mips_r)
			अवरोध;
		value = (fcr31 >> (FPU_CSR_COND_S - MIPS_FCCR_COND0_S)) &
			MIPS_FCCR_COND0;
		value |= (fcr31 >> (FPU_CSR_COND1_S - MIPS_FCCR_COND1_S)) &
			 (MIPS_FCCR_CONDX & ~MIPS_FCCR_COND0);
		pr_debug("%p gpr[%d]<-ccr=%08x\n",
			 (व्योम *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		अवरोध;

	हाल FPCREG_RID:
		value = boot_cpu_data.fpu_id;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (MIPSInst_RT(ir))
		xcp->regs[MIPSInst_RT(ir)] = value;
पूर्ण

/*
 * Emulate a CTC1 inकाष्ठाion.
 */
अटल अंतरभूत व्योम cop1_ctc(काष्ठा pt_regs *xcp, काष्ठा mips_fpu_काष्ठा *ctx,
			    mips_inकाष्ठाion ir)
अणु
	u32 fcr31 = ctx->fcr31;
	u32 value;
	u32 mask;

	अगर (MIPSInst_RT(ir) == 0)
		value = 0;
	अन्यथा
		value = xcp->regs[MIPSInst_RT(ir)];

	चयन (MIPSInst_RD(ir)) अणु
	हाल FPCREG_CSR:
		pr_debug("%p gpr[%d]->csr=%08x\n",
			 (व्योम *)xcp->cp0_epc, MIPSInst_RT(ir), value);

		/* Preserve पढ़ो-only bits.  */
		mask = boot_cpu_data.fpu_msk31;
		fcr31 = (value & ~mask) | (fcr31 & mask);
		अवरोध;

	हाल FPCREG_FENR:
		अगर (!cpu_has_mips_r)
			अवरोध;
		pr_debug("%p gpr[%d]->enr=%08x\n",
			 (व्योम *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		fcr31 &= ~(FPU_CSR_FS | FPU_CSR_ALL_E | FPU_CSR_RM);
		fcr31 |= (value << (FPU_CSR_FS_S - MIPS_FENR_FS_S)) &
			 FPU_CSR_FS;
		fcr31 |= value & (FPU_CSR_ALL_E | FPU_CSR_RM);
		अवरोध;

	हाल FPCREG_FEXR:
		अगर (!cpu_has_mips_r)
			अवरोध;
		pr_debug("%p gpr[%d]->exr=%08x\n",
			 (व्योम *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		fcr31 &= ~(FPU_CSR_ALL_X | FPU_CSR_ALL_S);
		fcr31 |= value & (FPU_CSR_ALL_X | FPU_CSR_ALL_S);
		अवरोध;

	हाल FPCREG_FCCR:
		अगर (!cpu_has_mips_r)
			अवरोध;
		pr_debug("%p gpr[%d]->ccr=%08x\n",
			 (व्योम *)xcp->cp0_epc, MIPSInst_RT(ir), value);
		fcr31 &= ~(FPU_CSR_CONDX | FPU_CSR_COND);
		fcr31 |= (value << (FPU_CSR_COND_S - MIPS_FCCR_COND0_S)) &
			 FPU_CSR_COND;
		fcr31 |= (value << (FPU_CSR_COND1_S - MIPS_FCCR_COND1_S)) &
			 FPU_CSR_CONDX;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	ctx->fcr31 = fcr31;
पूर्ण

/*
 * Emulate the single भग्नing poपूर्णांक inकाष्ठाion poपूर्णांकed at by EPC.
 * Two inकाष्ठाions अगर the inकाष्ठाion is in a branch delay slot.
 */

अटल पूर्णांक cop1Emulate(काष्ठा pt_regs *xcp, काष्ठा mips_fpu_काष्ठा *ctx,
		काष्ठा mm_decoded_insn dec_insn, व्योम __user **fault_addr)
अणु
	अचिन्हित दीर्घ contpc = xcp->cp0_epc + dec_insn.pc_inc;
	अचिन्हित पूर्णांक cond, cbit, bit0;
	mips_inकाष्ठाion ir;
	पूर्णांक likely, pc_inc;
	जोड़ fpureg *fpr;
	u32 __user *wva;
	u64 __user *dva;
	u32 wval;
	u64 dval;
	पूर्णांक sig;

	/*
	 * These are giving gcc a gentle hपूर्णांक about what to expect in
	 * dec_inst in order to करो better optimization.
	 */
	अगर (!cpu_has_mmips && dec_insn.micro_mips_mode)
		unreachable();

	/* XXX NEC Vr54xx bug workaround */
	अगर (delay_slot(xcp)) अणु
		अगर (dec_insn.micro_mips_mode) अणु
			अगर (!mm_isBranchInstr(xcp, dec_insn, &contpc))
				clear_delay_slot(xcp);
		पूर्ण अन्यथा अणु
			अगर (!isBranchInstr(xcp, dec_insn, &contpc))
				clear_delay_slot(xcp);
		पूर्ण
	पूर्ण

	अगर (delay_slot(xcp)) अणु
		/*
		 * The inकाष्ठाion to be emulated is in a branch delay slot
		 * which means that we have to	emulate the branch inकाष्ठाion
		 * BEFORE we करो the cop1 inकाष्ठाion.
		 *
		 * This branch could be a COP1 branch, but in that हाल we
		 * would have had a trap क्रम that inकाष्ठाion, and would not
		 * come through this route.
		 *
		 * Linux MIPS branch emulator operates on context, updating the
		 * cp0_epc.
		 */
		ir = dec_insn.next_insn;  /* process delay slot instr */
		pc_inc = dec_insn.next_pc_inc;
	पूर्ण अन्यथा अणु
		ir = dec_insn.insn;       /* process current instr */
		pc_inc = dec_insn.pc_inc;
	पूर्ण

	/*
	 * Since microMIPS FPU inकाष्ठाios are a subset of MIPS32 FPU
	 * inकाष्ठाions, we want to convert microMIPS FPU inकाष्ठाions
	 * पूर्णांकo MIPS32 inकाष्ठाions so that we could reuse all of the
	 * FPU emulation code.
	 *
	 * NOTE: We cannot करो this क्रम branch inकाष्ठाions since they
	 *       are not a subset. Example: Cannot emulate a 16-bit
	 *       aligned target address with a MIPS32 inकाष्ठाion.
	 */
	अगर (dec_insn.micro_mips_mode) अणु
		/*
		 * If next inकाष्ठाion is a 16-bit inकाष्ठाion, then it
		 * it cannot be a FPU inकाष्ठाion. This could happen
		 * since we can be called क्रम non-FPU inकाष्ठाions.
		 */
		अगर ((pc_inc == 2) ||
			(microMIPS32_to_MIPS32((जोड़ mips_inकाष्ठाion *)&ir)
			 == संक_अवैध))
			वापस संक_अवैध;
	पूर्ण

emul:
	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, xcp, 0);
	MIPS_FPU_EMU_INC_STATS(emulated);
	चयन (MIPSInst_OPCODE(ir)) अणु
	हाल ldc1_op:
		dva = (u64 __user *) (xcp->regs[MIPSInst_RS(ir)] +
				     MIPSInst_SIMM(ir));
		MIPS_FPU_EMU_INC_STATS(loads);

		अगर (!access_ok(dva, माप(u64))) अणु
			MIPS_FPU_EMU_INC_STATS(errors);
			*fault_addr = dva;
			वापस SIGBUS;
		पूर्ण
		अगर (__get_user(dval, dva)) अणु
			MIPS_FPU_EMU_INC_STATS(errors);
			*fault_addr = dva;
			वापस संक_अंश;
		पूर्ण
		DITOREG(dval, MIPSInst_RT(ir));
		अवरोध;

	हाल sdc1_op:
		dva = (u64 __user *) (xcp->regs[MIPSInst_RS(ir)] +
				      MIPSInst_SIMM(ir));
		MIPS_FPU_EMU_INC_STATS(stores);
		DIFROMREG(dval, MIPSInst_RT(ir));
		अगर (!access_ok(dva, माप(u64))) अणु
			MIPS_FPU_EMU_INC_STATS(errors);
			*fault_addr = dva;
			वापस SIGBUS;
		पूर्ण
		अगर (__put_user(dval, dva)) अणु
			MIPS_FPU_EMU_INC_STATS(errors);
			*fault_addr = dva;
			वापस संक_अंश;
		पूर्ण
		अवरोध;

	हाल lwc1_op:
		wva = (u32 __user *) (xcp->regs[MIPSInst_RS(ir)] +
				      MIPSInst_SIMM(ir));
		MIPS_FPU_EMU_INC_STATS(loads);
		अगर (!access_ok(wva, माप(u32))) अणु
			MIPS_FPU_EMU_INC_STATS(errors);
			*fault_addr = wva;
			वापस SIGBUS;
		पूर्ण
		अगर (__get_user(wval, wva)) अणु
			MIPS_FPU_EMU_INC_STATS(errors);
			*fault_addr = wva;
			वापस संक_अंश;
		पूर्ण
		SITOREG(wval, MIPSInst_RT(ir));
		अवरोध;

	हाल swc1_op:
		wva = (u32 __user *) (xcp->regs[MIPSInst_RS(ir)] +
				      MIPSInst_SIMM(ir));
		MIPS_FPU_EMU_INC_STATS(stores);
		SIFROMREG(wval, MIPSInst_RT(ir));
		अगर (!access_ok(wva, माप(u32))) अणु
			MIPS_FPU_EMU_INC_STATS(errors);
			*fault_addr = wva;
			वापस SIGBUS;
		पूर्ण
		अगर (__put_user(wval, wva)) अणु
			MIPS_FPU_EMU_INC_STATS(errors);
			*fault_addr = wva;
			वापस संक_अंश;
		पूर्ण
		अवरोध;

	हाल cop1_op:
		चयन (MIPSInst_RS(ir)) अणु
		हाल dmfc_op:
			अगर (!cpu_has_mips_3_4_5 && !cpu_has_mips64)
				वापस संक_अवैध;

			/* copरेजिस्टर fs -> gpr[rt] */
			अगर (MIPSInst_RT(ir) != 0) अणु
				DIFROMREG(xcp->regs[MIPSInst_RT(ir)],
					MIPSInst_RD(ir));
			पूर्ण
			अवरोध;

		हाल dmtc_op:
			अगर (!cpu_has_mips_3_4_5 && !cpu_has_mips64)
				वापस संक_अवैध;

			/* copरेजिस्टर fs <- rt */
			DITOREG(xcp->regs[MIPSInst_RT(ir)], MIPSInst_RD(ir));
			अवरोध;

		हाल mfhc_op:
			अगर (!cpu_has_mips_r2_r6)
				वापस संक_अवैध;

			/* copरेजिस्टर rd -> gpr[rt] */
			अगर (MIPSInst_RT(ir) != 0) अणु
				SIFROMHREG(xcp->regs[MIPSInst_RT(ir)],
					MIPSInst_RD(ir));
			पूर्ण
			अवरोध;

		हाल mthc_op:
			अगर (!cpu_has_mips_r2_r6)
				वापस संक_अवैध;

			/* copरेजिस्टर rd <- gpr[rt] */
			SITOHREG(xcp->regs[MIPSInst_RT(ir)], MIPSInst_RD(ir));
			अवरोध;

		हाल mfc_op:
			/* copरेजिस्टर rd -> gpr[rt] */
			अगर (MIPSInst_RT(ir) != 0) अणु
				SIFROMREG(xcp->regs[MIPSInst_RT(ir)],
					MIPSInst_RD(ir));
			पूर्ण
			अवरोध;

		हाल mtc_op:
			/* copरेजिस्टर rd <- rt */
			SITOREG(xcp->regs[MIPSInst_RT(ir)], MIPSInst_RD(ir));
			अवरोध;

		हाल cfc_op:
			/* cop control रेजिस्टर rd -> gpr[rt] */
			cop1_cfc(xcp, ctx, ir);
			अवरोध;

		हाल ctc_op:
			/* copरेजिस्टर rd <- rt */
			cop1_ctc(xcp, ctx, ir);
			अगर ((ctx->fcr31 >> 5) & ctx->fcr31 & FPU_CSR_ALL_E) अणु
				वापस संक_भ_त्रुटि;
			पूर्ण
			अवरोध;

		हाल bc1eqz_op:
		हाल bc1nez_op:
			अगर (!cpu_has_mips_r6 || delay_slot(xcp))
				वापस संक_अवैध;

			likely = 0;
			cond = 0;
			fpr = &current->thपढ़ो.fpu.fpr[MIPSInst_RT(ir)];
			bit0 = get_fpr32(fpr, 0) & 0x1;
			चयन (MIPSInst_RS(ir)) अणु
			हाल bc1eqz_op:
				MIPS_FPU_EMU_INC_STATS(bc1eqz);
				cond = bit0 == 0;
				अवरोध;
			हाल bc1nez_op:
				MIPS_FPU_EMU_INC_STATS(bc1nez);
				cond = bit0 != 0;
				अवरोध;
			पूर्ण
			जाओ branch_common;

		हाल bc_op:
			अगर (delay_slot(xcp))
				वापस संक_अवैध;

			अगर (cpu_has_mips_4_5_r)
				cbit = fpucondbit[MIPSInst_RT(ir) >> 2];
			अन्यथा
				cbit = FPU_CSR_COND;
			cond = ctx->fcr31 & cbit;

			likely = 0;
			चयन (MIPSInst_RT(ir) & 3) अणु
			हाल bcfl_op:
				अगर (cpu_has_mips_2_3_4_5_r)
					likely = 1;
				fallthrough;
			हाल bcf_op:
				cond = !cond;
				अवरोध;
			हाल bctl_op:
				अगर (cpu_has_mips_2_3_4_5_r)
					likely = 1;
				fallthrough;
			हाल bct_op:
				अवरोध;
			पूर्ण
branch_common:
			MIPS_FPU_EMU_INC_STATS(branches);
			set_delay_slot(xcp);
			अगर (cond) अणु
				/*
				 * Branch taken: emulate dslot inकाष्ठाion
				 */
				अचिन्हित दीर्घ bcpc;

				/*
				 * Remember EPC at the branch to poपूर्णांक back
				 * at so that any delay-slot inकाष्ठाion
				 * संकेत is not silently ignored.
				 */
				bcpc = xcp->cp0_epc;
				xcp->cp0_epc += dec_insn.pc_inc;

				contpc = MIPSInst_SIMM(ir);
				ir = dec_insn.next_insn;
				अगर (dec_insn.micro_mips_mode) अणु
					contpc = (xcp->cp0_epc + (contpc << 1));

					/* If 16-bit inकाष्ठाion, not FPU. */
					अगर ((dec_insn.next_pc_inc == 2) ||
						(microMIPS32_to_MIPS32((जोड़ mips_inकाष्ठाion *)&ir) == संक_अवैध)) अणु

						/*
						 * Since this inकाष्ठाion will
						 * be put on the stack with
						 * 32-bit words, get around
						 * this problem by putting a
						 * NOP16 as the second one.
						 */
						अगर (dec_insn.next_pc_inc == 2)
							ir = (ir & (~0xffff)) | MM_NOP16;

						/*
						 * Single step the non-CP1
						 * inकाष्ठाion in the dslot.
						 */
						sig = mips_dsemul(xcp, ir,
								  bcpc, contpc);
						अगर (sig < 0)
							अवरोध;
						अगर (sig)
							xcp->cp0_epc = bcpc;
						/*
						 * संक_अवैध क्रमces out of
						 * the emulation loop.
						 */
						वापस sig ? sig : संक_अवैध;
					पूर्ण
				पूर्ण अन्यथा
					contpc = (xcp->cp0_epc + (contpc << 2));

				चयन (MIPSInst_OPCODE(ir)) अणु
				हाल lwc1_op:
				हाल swc1_op:
					जाओ emul;

				हाल ldc1_op:
				हाल sdc1_op:
					अगर (cpu_has_mips_2_3_4_5_r)
						जाओ emul;

					जाओ bc_sigill;

				हाल cop1_op:
					जाओ emul;

				हाल cop1x_op:
					अगर (cpu_has_mips_4_5_64_r2_r6)
						/* its one of ours */
						जाओ emul;

					जाओ bc_sigill;

				हाल spec_op:
					चयन (MIPSInst_FUNC(ir)) अणु
					हाल movc_op:
						अगर (cpu_has_mips_4_5_r)
							जाओ emul;

						जाओ bc_sigill;
					पूर्ण
					अवरोध;

				bc_sigill:
					xcp->cp0_epc = bcpc;
					वापस संक_अवैध;
				पूर्ण

				/*
				 * Single step the non-cp1
				 * inकाष्ठाion in the dslot
				 */
				sig = mips_dsemul(xcp, ir, bcpc, contpc);
				अगर (sig < 0)
					अवरोध;
				अगर (sig)
					xcp->cp0_epc = bcpc;
				/* संक_अवैध क्रमces out of the emulation loop.  */
				वापस sig ? sig : संक_अवैध;
			पूर्ण अन्यथा अगर (likely) अणु	/* branch not taken */
				/*
				 * branch likely nullअगरies
				 * dslot अगर not taken
				 */
				xcp->cp0_epc += dec_insn.pc_inc;
				contpc += dec_insn.pc_inc;
				/*
				 * अन्यथा जारी & execute
				 * dslot as normal insn
				 */
			पूर्ण
			अवरोध;

		शेष:
			अगर (!(MIPSInst_RS(ir) & 0x10))
				वापस संक_अवैध;

			/* a real fpu computation inकाष्ठाion */
			sig = fpu_emu(xcp, ctx, ir);
			अगर (sig)
				वापस sig;
		पूर्ण
		अवरोध;

	हाल cop1x_op:
		अगर (!cpu_has_mips_4_5_64_r2_r6)
			वापस संक_अवैध;

		sig = fpux_emu(xcp, ctx, ir, fault_addr);
		अगर (sig)
			वापस sig;
		अवरोध;

	हाल spec_op:
		अगर (!cpu_has_mips_4_5_r)
			वापस संक_अवैध;

		अगर (MIPSInst_FUNC(ir) != movc_op)
			वापस संक_अवैध;
		cond = fpucondbit[MIPSInst_RT(ir) >> 2];
		अगर (((ctx->fcr31 & cond) != 0) == ((MIPSInst_RT(ir) & 1) != 0))
			xcp->regs[MIPSInst_RD(ir)] =
				xcp->regs[MIPSInst_RS(ir)];
		अवरोध;
	शेष:
		वापस संक_अवैध;
	पूर्ण

	/* we did it !! */
	xcp->cp0_epc = contpc;
	clear_delay_slot(xcp);

	वापस 0;
पूर्ण

/*
 * Conversion table from MIPS compare ops 48-63
 * cond = ieee754dp_cmp(x,y,IEEE754_UN,sig);
 */
अटल स्थिर अचिन्हित अक्षर cmptab[8] = अणु
	0,			/* cmp_0 (sig) cmp_sf */
	IEEE754_CUN,		/* cmp_un (sig) cmp_ngle */
	IEEE754_CEQ,		/* cmp_eq (sig) cmp_seq */
	IEEE754_CEQ | IEEE754_CUN,	/* cmp_ueq (sig) cmp_ngl  */
	IEEE754_CLT,		/* cmp_olt (sig) cmp_lt */
	IEEE754_CLT | IEEE754_CUN,	/* cmp_ult (sig) cmp_nge */
	IEEE754_CLT | IEEE754_CEQ,	/* cmp_ole (sig) cmp_le */
	IEEE754_CLT | IEEE754_CEQ | IEEE754_CUN,	/* cmp_ule (sig) cmp_ngt */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर negative_cmptab[8] = अणु
	0, /* Reserved */
	IEEE754_CLT | IEEE754_CGT | IEEE754_CEQ,
	IEEE754_CLT | IEEE754_CGT | IEEE754_CUN,
	IEEE754_CLT | IEEE754_CGT,
	/* Reserved */
पूर्ण;


/*
 * Additional MIPS4 inकाष्ठाions
 */

#घोषणा DEF3OP(name, p, f1, f2, f3)					\
अटल जोड़ ieee754##p fpemu_##p##_##name(जोड़ ieee754##p r,		\
	जोड़ ieee754##p s, जोड़ ieee754##p t)				\
अणु									\
	काष्ठा _ieee754_csr ieee754_csr_save;				\
	s = f1(s, t);							\
	ieee754_csr_save = ieee754_csr;					\
	s = f2(s, r);							\
	ieee754_csr_save.cx |= ieee754_csr.cx;				\
	ieee754_csr_save.sx |= ieee754_csr.sx;				\
	s = f3(s);							\
	ieee754_csr.cx |= ieee754_csr_save.cx;				\
	ieee754_csr.sx |= ieee754_csr_save.sx;				\
	वापस s;							\
पूर्ण

अटल जोड़ ieee754dp fpemu_dp_recip(जोड़ ieee754dp d)
अणु
	वापस ieee754dp_भाग(ieee754dp_one(0), d);
पूर्ण

अटल जोड़ ieee754dp fpemu_dp_rवर्ग_मूल(जोड़ ieee754dp d)
अणु
	वापस ieee754dp_भाग(ieee754dp_one(0), ieee754dp_वर्ग_मूल(d));
पूर्ण

अटल जोड़ ieee754sp fpemu_sp_recip(जोड़ ieee754sp s)
अणु
	वापस ieee754sp_भाग(ieee754sp_one(0), s);
पूर्ण

अटल जोड़ ieee754sp fpemu_sp_rवर्ग_मूल(जोड़ ieee754sp s)
अणु
	वापस ieee754sp_भाग(ieee754sp_one(0), ieee754sp_वर्ग_मूल(s));
पूर्ण

DEF3OP(madd, sp, ieee754sp_mul, ieee754sp_add, );
DEF3OP(msub, sp, ieee754sp_mul, ieee754sp_sub, );
DEF3OP(nmadd, sp, ieee754sp_mul, ieee754sp_add, ieee754sp_neg);
DEF3OP(nmsub, sp, ieee754sp_mul, ieee754sp_sub, ieee754sp_neg);
DEF3OP(madd, dp, ieee754dp_mul, ieee754dp_add, );
DEF3OP(msub, dp, ieee754dp_mul, ieee754dp_sub, );
DEF3OP(nmadd, dp, ieee754dp_mul, ieee754dp_add, ieee754dp_neg);
DEF3OP(nmsub, dp, ieee754dp_mul, ieee754dp_sub, ieee754dp_neg);

अटल पूर्णांक fpux_emu(काष्ठा pt_regs *xcp, काष्ठा mips_fpu_काष्ठा *ctx,
	mips_inकाष्ठाion ir, व्योम __user **fault_addr)
अणु
	अचिन्हित पूर्णांक rcsr = 0;	/* resulting csr */

	MIPS_FPU_EMU_INC_STATS(cp1xops);

	चयन (MIPSInst_FMA_FFMT(ir)) अणु
	हाल s_fmt:अणु		/* 0 */

		जोड़ ieee754sp(*handler) (जोड़ ieee754sp, जोड़ ieee754sp, जोड़ ieee754sp);
		जोड़ ieee754sp fd, fr, fs, ft;
		u32 __user *va;
		u32 val;

		चयन (MIPSInst_FUNC(ir)) अणु
		हाल lwxc1_op:
			va = (व्योम __user *) (xcp->regs[MIPSInst_FR(ir)] +
				xcp->regs[MIPSInst_FT(ir)]);

			MIPS_FPU_EMU_INC_STATS(loads);
			अगर (!access_ok(va, माप(u32))) अणु
				MIPS_FPU_EMU_INC_STATS(errors);
				*fault_addr = va;
				वापस SIGBUS;
			पूर्ण
			अगर (__get_user(val, va)) अणु
				MIPS_FPU_EMU_INC_STATS(errors);
				*fault_addr = va;
				वापस संक_अंश;
			पूर्ण
			SITOREG(val, MIPSInst_FD(ir));
			अवरोध;

		हाल swxc1_op:
			va = (व्योम __user *) (xcp->regs[MIPSInst_FR(ir)] +
				xcp->regs[MIPSInst_FT(ir)]);

			MIPS_FPU_EMU_INC_STATS(stores);

			SIFROMREG(val, MIPSInst_FS(ir));
			अगर (!access_ok(va, माप(u32))) अणु
				MIPS_FPU_EMU_INC_STATS(errors);
				*fault_addr = va;
				वापस SIGBUS;
			पूर्ण
			अगर (put_user(val, va)) अणु
				MIPS_FPU_EMU_INC_STATS(errors);
				*fault_addr = va;
				वापस संक_अंश;
			पूर्ण
			अवरोध;

		हाल madd_s_op:
			अगर (cpu_has_mac2008_only)
				handler = ieee754sp_madd;
			अन्यथा
				handler = fpemu_sp_madd;
			जाओ scoptop;
		हाल msub_s_op:
			अगर (cpu_has_mac2008_only)
				handler = ieee754sp_msub;
			अन्यथा
				handler = fpemu_sp_msub;
			जाओ scoptop;
		हाल nmadd_s_op:
			अगर (cpu_has_mac2008_only)
				handler = ieee754sp_nmadd;
			अन्यथा
				handler = fpemu_sp_nmadd;
			जाओ scoptop;
		हाल nmsub_s_op:
			अगर (cpu_has_mac2008_only)
				handler = ieee754sp_nmsub;
			अन्यथा
				handler = fpemu_sp_nmsub;
			जाओ scoptop;

		      scoptop:
			SPFROMREG(fr, MIPSInst_FR(ir));
			SPFROMREG(fs, MIPSInst_FS(ir));
			SPFROMREG(ft, MIPSInst_FT(ir));
			fd = (*handler) (fr, fs, ft);
			SPTOREG(fd, MIPSInst_FD(ir));

		      copcsr:
			अगर (ieee754_cxtest(IEEE754_INEXACT)) अणु
				MIPS_FPU_EMU_INC_STATS(ieee754_inexact);
				rcsr |= FPU_CSR_INE_X | FPU_CSR_INE_S;
			पूर्ण
			अगर (ieee754_cxtest(IEEE754_UNDERFLOW)) अणु
				MIPS_FPU_EMU_INC_STATS(ieee754_underflow);
				rcsr |= FPU_CSR_UDF_X | FPU_CSR_UDF_S;
			पूर्ण
			अगर (ieee754_cxtest(IEEE754_OVERFLOW)) अणु
				MIPS_FPU_EMU_INC_STATS(ieee754_overflow);
				rcsr |= FPU_CSR_OVF_X | FPU_CSR_OVF_S;
			पूर्ण
			अगर (ieee754_cxtest(IEEE754_INVALID_OPERATION)) अणु
				MIPS_FPU_EMU_INC_STATS(ieee754_invaliकरोp);
				rcsr |= FPU_CSR_INV_X | FPU_CSR_INV_S;
			पूर्ण

			ctx->fcr31 = (ctx->fcr31 & ~FPU_CSR_ALL_X) | rcsr;
			अगर ((ctx->fcr31 >> 5) & ctx->fcr31 & FPU_CSR_ALL_E) अणु
				/*prपूर्णांकk ("SIGFPE: FPU csr = %08x\n",
				   ctx->fcr31); */
				वापस संक_भ_त्रुटि;
			पूर्ण

			अवरोध;

		शेष:
			वापस संक_अवैध;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल d_fmt:अणु		/* 1 */
		जोड़ ieee754dp(*handler) (जोड़ ieee754dp, जोड़ ieee754dp, जोड़ ieee754dp);
		जोड़ ieee754dp fd, fr, fs, ft;
		u64 __user *va;
		u64 val;

		चयन (MIPSInst_FUNC(ir)) अणु
		हाल ldxc1_op:
			va = (व्योम __user *) (xcp->regs[MIPSInst_FR(ir)] +
				xcp->regs[MIPSInst_FT(ir)]);

			MIPS_FPU_EMU_INC_STATS(loads);
			अगर (!access_ok(va, माप(u64))) अणु
				MIPS_FPU_EMU_INC_STATS(errors);
				*fault_addr = va;
				वापस SIGBUS;
			पूर्ण
			अगर (__get_user(val, va)) अणु
				MIPS_FPU_EMU_INC_STATS(errors);
				*fault_addr = va;
				वापस संक_अंश;
			पूर्ण
			DITOREG(val, MIPSInst_FD(ir));
			अवरोध;

		हाल sdxc1_op:
			va = (व्योम __user *) (xcp->regs[MIPSInst_FR(ir)] +
				xcp->regs[MIPSInst_FT(ir)]);

			MIPS_FPU_EMU_INC_STATS(stores);
			DIFROMREG(val, MIPSInst_FS(ir));
			अगर (!access_ok(va, माप(u64))) अणु
				MIPS_FPU_EMU_INC_STATS(errors);
				*fault_addr = va;
				वापस SIGBUS;
			पूर्ण
			अगर (__put_user(val, va)) अणु
				MIPS_FPU_EMU_INC_STATS(errors);
				*fault_addr = va;
				वापस संक_अंश;
			पूर्ण
			अवरोध;

		हाल madd_d_op:
			अगर (cpu_has_mac2008_only)
				handler = ieee754dp_madd;
			अन्यथा
				handler = fpemu_dp_madd;
			जाओ dcoptop;
		हाल msub_d_op:
			अगर (cpu_has_mac2008_only)
				handler = ieee754dp_msub;
			अन्यथा
				handler = fpemu_dp_msub;
			जाओ dcoptop;
		हाल nmadd_d_op:
			अगर (cpu_has_mac2008_only)
				handler = ieee754dp_nmadd;
			अन्यथा
				handler = fpemu_dp_nmadd;
			जाओ dcoptop;
		हाल nmsub_d_op:
			अगर (cpu_has_mac2008_only)
				handler = ieee754dp_nmsub;
			अन्यथा
			handler = fpemu_dp_nmsub;
			जाओ dcoptop;

		      dcoptop:
			DPFROMREG(fr, MIPSInst_FR(ir));
			DPFROMREG(fs, MIPSInst_FS(ir));
			DPFROMREG(ft, MIPSInst_FT(ir));
			fd = (*handler) (fr, fs, ft);
			DPTOREG(fd, MIPSInst_FD(ir));
			जाओ copcsr;

		शेष:
			वापस संक_अवैध;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल 0x3:
		अगर (MIPSInst_FUNC(ir) != pfetch_op)
			वापस संक_अवैध;

		/* ignore prefx operation */
		अवरोध;

	शेष:
		वापस संक_अवैध;
	पूर्ण

	वापस 0;
पूर्ण



/*
 * Emulate a single COP1 arithmetic inकाष्ठाion.
 */
अटल पूर्णांक fpu_emu(काष्ठा pt_regs *xcp, काष्ठा mips_fpu_काष्ठा *ctx,
	mips_inकाष्ठाion ir)
अणु
	पूर्णांक rfmt;		/* resulting क्रमmat */
	अचिन्हित पूर्णांक rcsr = 0;	/* resulting csr */
	अचिन्हित पूर्णांक oldrm;
	अचिन्हित पूर्णांक cbit;
	अचिन्हित पूर्णांक cond;
	जोड़ अणु
		जोड़ ieee754dp d;
		जोड़ ieee754sp s;
		पूर्णांक w;
		s64 l;
	पूर्ण rv;			/* resulting value */
	u64 bits;

	MIPS_FPU_EMU_INC_STATS(cp1ops);
	चयन (rfmt = (MIPSInst_FFMT(ir) & 0xf)) अणु
	हाल s_fmt: अणु		/* 0 */
		जोड़ अणु
			जोड़ ieee754sp(*b) (जोड़ ieee754sp, जोड़ ieee754sp);
			जोड़ ieee754sp(*u) (जोड़ ieee754sp);
		पूर्ण handler;
		जोड़ ieee754sp fd, fs, ft;

		चयन (MIPSInst_FUNC(ir)) अणु
			/* binary ops */
		हाल fadd_op:
			MIPS_FPU_EMU_INC_STATS(add_s);
			handler.b = ieee754sp_add;
			जाओ scopbop;
		हाल fsub_op:
			MIPS_FPU_EMU_INC_STATS(sub_s);
			handler.b = ieee754sp_sub;
			जाओ scopbop;
		हाल fmul_op:
			MIPS_FPU_EMU_INC_STATS(mul_s);
			handler.b = ieee754sp_mul;
			जाओ scopbop;
		हाल fभाग_op:
			MIPS_FPU_EMU_INC_STATS(भाग_s);
			handler.b = ieee754sp_भाग;
			जाओ scopbop;

			/* unary  ops */
		हाल fवर्ग_मूल_op:
			अगर (!cpu_has_mips_2_3_4_5_r)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(वर्ग_मूल_s);
			handler.u = ieee754sp_वर्ग_मूल;
			जाओ scopuop;

		/*
		 * Note that on some MIPS IV implementations such as the
		 * R5000 and R8000 the FSQRT and FRECIP inकाष्ठाions करो not
		 * achieve full IEEE-754 accuracy - however this emulator करोes.
		 */
		हाल frवर्ग_मूल_op:
			अगर (!cpu_has_mips_4_5_64_r2_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(rवर्ग_मूल_s);
			handler.u = fpemu_sp_rवर्ग_मूल;
			जाओ scopuop;

		हाल frecip_op:
			अगर (!cpu_has_mips_4_5_64_r2_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(recip_s);
			handler.u = fpemu_sp_recip;
			जाओ scopuop;

		हाल fmovc_op:
			अगर (!cpu_has_mips_4_5_r)
				वापस संक_अवैध;

			cond = fpucondbit[MIPSInst_FT(ir) >> 2];
			अगर (((ctx->fcr31 & cond) != 0) !=
				((MIPSInst_FT(ir) & 1) != 0))
				वापस 0;
			SPFROMREG(rv.s, MIPSInst_FS(ir));
			अवरोध;

		हाल fmovz_op:
			अगर (!cpu_has_mips_4_5_r)
				वापस संक_अवैध;

			अगर (xcp->regs[MIPSInst_FT(ir)] != 0)
				वापस 0;
			SPFROMREG(rv.s, MIPSInst_FS(ir));
			अवरोध;

		हाल fmovn_op:
			अगर (!cpu_has_mips_4_5_r)
				वापस संक_अवैध;

			अगर (xcp->regs[MIPSInst_FT(ir)] == 0)
				वापस 0;
			SPFROMREG(rv.s, MIPSInst_FS(ir));
			अवरोध;

		हाल fseleqz_op:
			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(seleqz_s);
			SPFROMREG(rv.s, MIPSInst_FT(ir));
			अगर (rv.w & 0x1)
				rv.w = 0;
			अन्यथा
				SPFROMREG(rv.s, MIPSInst_FS(ir));
			अवरोध;

		हाल fselnez_op:
			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(selnez_s);
			SPFROMREG(rv.s, MIPSInst_FT(ir));
			अगर (rv.w & 0x1)
				SPFROMREG(rv.s, MIPSInst_FS(ir));
			अन्यथा
				rv.w = 0;
			अवरोध;

		हाल fmaddf_op: अणु
			जोड़ ieee754sp ft, fs, fd;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(maddf_s);
			SPFROMREG(ft, MIPSInst_FT(ir));
			SPFROMREG(fs, MIPSInst_FS(ir));
			SPFROMREG(fd, MIPSInst_FD(ir));
			rv.s = ieee754sp_maddf(fd, fs, ft);
			जाओ copcsr;
		पूर्ण

		हाल fmsubf_op: अणु
			जोड़ ieee754sp ft, fs, fd;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(msubf_s);
			SPFROMREG(ft, MIPSInst_FT(ir));
			SPFROMREG(fs, MIPSInst_FS(ir));
			SPFROMREG(fd, MIPSInst_FD(ir));
			rv.s = ieee754sp_msubf(fd, fs, ft);
			जाओ copcsr;
		पूर्ण

		हाल frपूर्णांक_op: अणु
			जोड़ ieee754sp fs;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(rपूर्णांक_s);
			SPFROMREG(fs, MIPSInst_FS(ir));
			rv.s = ieee754sp_rपूर्णांक(fs);
			जाओ copcsr;
		पूर्ण

		हाल fclass_op: अणु
			जोड़ ieee754sp fs;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(class_s);
			SPFROMREG(fs, MIPSInst_FS(ir));
			rv.w = ieee754sp_2008class(fs);
			rfmt = w_fmt;
			जाओ copcsr;
		पूर्ण

		हाल fmin_op: अणु
			जोड़ ieee754sp fs, ft;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(min_s);
			SPFROMREG(ft, MIPSInst_FT(ir));
			SPFROMREG(fs, MIPSInst_FS(ir));
			rv.s = ieee754sp_fmin(fs, ft);
			जाओ copcsr;
		पूर्ण

		हाल fmina_op: अणु
			जोड़ ieee754sp fs, ft;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(mina_s);
			SPFROMREG(ft, MIPSInst_FT(ir));
			SPFROMREG(fs, MIPSInst_FS(ir));
			rv.s = ieee754sp_fmina(fs, ft);
			जाओ copcsr;
		पूर्ण

		हाल fmax_op: अणु
			जोड़ ieee754sp fs, ft;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(max_s);
			SPFROMREG(ft, MIPSInst_FT(ir));
			SPFROMREG(fs, MIPSInst_FS(ir));
			rv.s = ieee754sp_fmax(fs, ft);
			जाओ copcsr;
		पूर्ण

		हाल fmaxa_op: अणु
			जोड़ ieee754sp fs, ft;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(maxa_s);
			SPFROMREG(ft, MIPSInst_FT(ir));
			SPFROMREG(fs, MIPSInst_FS(ir));
			rv.s = ieee754sp_fmaxa(fs, ft);
			जाओ copcsr;
		पूर्ण

		हाल भ_असल_op:
			MIPS_FPU_EMU_INC_STATS(असल_s);
			handler.u = ieee754sp_असल;
			जाओ scopuop;

		हाल fneg_op:
			MIPS_FPU_EMU_INC_STATS(neg_s);
			handler.u = ieee754sp_neg;
			जाओ scopuop;

		हाल fmov_op:
			/* an easy one */
			MIPS_FPU_EMU_INC_STATS(mov_s);
			SPFROMREG(rv.s, MIPSInst_FS(ir));
			जाओ copcsr;

			/* binary op on handler */
scopbop:
			SPFROMREG(fs, MIPSInst_FS(ir));
			SPFROMREG(ft, MIPSInst_FT(ir));

			rv.s = (*handler.b) (fs, ft);
			जाओ copcsr;
scopuop:
			SPFROMREG(fs, MIPSInst_FS(ir));
			rv.s = (*handler.u) (fs);
			जाओ copcsr;
copcsr:
			अगर (ieee754_cxtest(IEEE754_INEXACT)) अणु
				MIPS_FPU_EMU_INC_STATS(ieee754_inexact);
				rcsr |= FPU_CSR_INE_X | FPU_CSR_INE_S;
			पूर्ण
			अगर (ieee754_cxtest(IEEE754_UNDERFLOW)) अणु
				MIPS_FPU_EMU_INC_STATS(ieee754_underflow);
				rcsr |= FPU_CSR_UDF_X | FPU_CSR_UDF_S;
			पूर्ण
			अगर (ieee754_cxtest(IEEE754_OVERFLOW)) अणु
				MIPS_FPU_EMU_INC_STATS(ieee754_overflow);
				rcsr |= FPU_CSR_OVF_X | FPU_CSR_OVF_S;
			पूर्ण
			अगर (ieee754_cxtest(IEEE754_ZERO_DIVIDE)) अणु
				MIPS_FPU_EMU_INC_STATS(ieee754_zeroभाग);
				rcsr |= FPU_CSR_DIV_X | FPU_CSR_DIV_S;
			पूर्ण
			अगर (ieee754_cxtest(IEEE754_INVALID_OPERATION)) अणु
				MIPS_FPU_EMU_INC_STATS(ieee754_invaliकरोp);
				rcsr |= FPU_CSR_INV_X | FPU_CSR_INV_S;
			पूर्ण
			अवरोध;

			/* unary conv ops */
		हाल fcvts_op:
			वापस संक_अवैध;	/* not defined */

		हाल fcvtd_op:
			MIPS_FPU_EMU_INC_STATS(cvt_d_s);
			SPFROMREG(fs, MIPSInst_FS(ir));
			rv.d = ieee754dp_fsp(fs);
			rfmt = d_fmt;
			जाओ copcsr;

		हाल fcvtw_op:
			MIPS_FPU_EMU_INC_STATS(cvt_w_s);
			SPFROMREG(fs, MIPSInst_FS(ir));
			rv.w = ieee754sp_tपूर्णांक(fs);
			rfmt = w_fmt;
			जाओ copcsr;

		हाल fround_op:
		हाल ftrunc_op:
		हाल fउच्चमान_op:
		हाल fन्यूनमान_op:
			अगर (!cpu_has_mips_2_3_4_5_r)
				वापस संक_अवैध;

			अगर (MIPSInst_FUNC(ir) == fउच्चमान_op)
				MIPS_FPU_EMU_INC_STATS(उच्चमान_w_s);
			अगर (MIPSInst_FUNC(ir) == fन्यूनमान_op)
				MIPS_FPU_EMU_INC_STATS(न्यूनमान_w_s);
			अगर (MIPSInst_FUNC(ir) == fround_op)
				MIPS_FPU_EMU_INC_STATS(round_w_s);
			अगर (MIPSInst_FUNC(ir) == ftrunc_op)
				MIPS_FPU_EMU_INC_STATS(trunc_w_s);

			oldrm = ieee754_csr.rm;
			SPFROMREG(fs, MIPSInst_FS(ir));
			ieee754_csr.rm = MIPSInst_FUNC(ir);
			rv.w = ieee754sp_tपूर्णांक(fs);
			ieee754_csr.rm = oldrm;
			rfmt = w_fmt;
			जाओ copcsr;

		हाल fsel_op:
			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(sel_s);
			SPFROMREG(fd, MIPSInst_FD(ir));
			अगर (fd.bits & 0x1)
				SPFROMREG(rv.s, MIPSInst_FT(ir));
			अन्यथा
				SPFROMREG(rv.s, MIPSInst_FS(ir));
			अवरोध;

		हाल fcvtl_op:
			अगर (!cpu_has_mips_3_4_5_64_r2_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(cvt_l_s);
			SPFROMREG(fs, MIPSInst_FS(ir));
			rv.l = ieee754sp_tदीर्घ(fs);
			rfmt = l_fmt;
			जाओ copcsr;

		हाल froundl_op:
		हाल ftruncl_op:
		हाल fउच्चमानl_op:
		हाल fन्यूनमानl_op:
			अगर (!cpu_has_mips_3_4_5_64_r2_r6)
				वापस संक_अवैध;

			अगर (MIPSInst_FUNC(ir) == fउच्चमानl_op)
				MIPS_FPU_EMU_INC_STATS(उच्चमान_l_s);
			अगर (MIPSInst_FUNC(ir) == fन्यूनमानl_op)
				MIPS_FPU_EMU_INC_STATS(न्यूनमान_l_s);
			अगर (MIPSInst_FUNC(ir) == froundl_op)
				MIPS_FPU_EMU_INC_STATS(round_l_s);
			अगर (MIPSInst_FUNC(ir) == ftruncl_op)
				MIPS_FPU_EMU_INC_STATS(trunc_l_s);

			oldrm = ieee754_csr.rm;
			SPFROMREG(fs, MIPSInst_FS(ir));
			ieee754_csr.rm = MIPSInst_FUNC(ir);
			rv.l = ieee754sp_tदीर्घ(fs);
			ieee754_csr.rm = oldrm;
			rfmt = l_fmt;
			जाओ copcsr;

		शेष:
			अगर (!NO_R6EMU && MIPSInst_FUNC(ir) >= fcmp_op) अणु
				अचिन्हित पूर्णांक cmpop;
				जोड़ ieee754sp fs, ft;

				cmpop = MIPSInst_FUNC(ir) - fcmp_op;
				SPFROMREG(fs, MIPSInst_FS(ir));
				SPFROMREG(ft, MIPSInst_FT(ir));
				rv.w = ieee754sp_cmp(fs, ft,
					cmptab[cmpop & 0x7], cmpop & 0x8);
				rfmt = -1;
				अगर ((cmpop & 0x8) && ieee754_cxtest
					(IEEE754_INVALID_OPERATION))
					rcsr = FPU_CSR_INV_X | FPU_CSR_INV_S;
				अन्यथा
					जाओ copcsr;

			पूर्ण अन्यथा
				वापस संक_अवैध;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल d_fmt: अणु
		जोड़ ieee754dp fd, fs, ft;
		जोड़ अणु
			जोड़ ieee754dp(*b) (जोड़ ieee754dp, जोड़ ieee754dp);
			जोड़ ieee754dp(*u) (जोड़ ieee754dp);
		पूर्ण handler;

		चयन (MIPSInst_FUNC(ir)) अणु
			/* binary ops */
		हाल fadd_op:
			MIPS_FPU_EMU_INC_STATS(add_d);
			handler.b = ieee754dp_add;
			जाओ dcopbop;
		हाल fsub_op:
			MIPS_FPU_EMU_INC_STATS(sub_d);
			handler.b = ieee754dp_sub;
			जाओ dcopbop;
		हाल fmul_op:
			MIPS_FPU_EMU_INC_STATS(mul_d);
			handler.b = ieee754dp_mul;
			जाओ dcopbop;
		हाल fभाग_op:
			MIPS_FPU_EMU_INC_STATS(भाग_d);
			handler.b = ieee754dp_भाग;
			जाओ dcopbop;

			/* unary  ops */
		हाल fवर्ग_मूल_op:
			अगर (!cpu_has_mips_2_3_4_5_r)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(वर्ग_मूल_d);
			handler.u = ieee754dp_वर्ग_मूल;
			जाओ dcopuop;
		/*
		 * Note that on some MIPS IV implementations such as the
		 * R5000 and R8000 the FSQRT and FRECIP inकाष्ठाions करो not
		 * achieve full IEEE-754 accuracy - however this emulator करोes.
		 */
		हाल frवर्ग_मूल_op:
			अगर (!cpu_has_mips_4_5_64_r2_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(rवर्ग_मूल_d);
			handler.u = fpemu_dp_rवर्ग_मूल;
			जाओ dcopuop;
		हाल frecip_op:
			अगर (!cpu_has_mips_4_5_64_r2_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(recip_d);
			handler.u = fpemu_dp_recip;
			जाओ dcopuop;
		हाल fmovc_op:
			अगर (!cpu_has_mips_4_5_r)
				वापस संक_अवैध;

			cond = fpucondbit[MIPSInst_FT(ir) >> 2];
			अगर (((ctx->fcr31 & cond) != 0) !=
				((MIPSInst_FT(ir) & 1) != 0))
				वापस 0;
			DPFROMREG(rv.d, MIPSInst_FS(ir));
			अवरोध;
		हाल fmovz_op:
			अगर (!cpu_has_mips_4_5_r)
				वापस संक_अवैध;

			अगर (xcp->regs[MIPSInst_FT(ir)] != 0)
				वापस 0;
			DPFROMREG(rv.d, MIPSInst_FS(ir));
			अवरोध;
		हाल fmovn_op:
			अगर (!cpu_has_mips_4_5_r)
				वापस संक_अवैध;

			अगर (xcp->regs[MIPSInst_FT(ir)] == 0)
				वापस 0;
			DPFROMREG(rv.d, MIPSInst_FS(ir));
			अवरोध;

		हाल fseleqz_op:
			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(seleqz_d);
			DPFROMREG(rv.d, MIPSInst_FT(ir));
			अगर (rv.l & 0x1)
				rv.l = 0;
			अन्यथा
				DPFROMREG(rv.d, MIPSInst_FS(ir));
			अवरोध;

		हाल fselnez_op:
			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(selnez_d);
			DPFROMREG(rv.d, MIPSInst_FT(ir));
			अगर (rv.l & 0x1)
				DPFROMREG(rv.d, MIPSInst_FS(ir));
			अन्यथा
				rv.l = 0;
			अवरोध;

		हाल fmaddf_op: अणु
			जोड़ ieee754dp ft, fs, fd;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(maddf_d);
			DPFROMREG(ft, MIPSInst_FT(ir));
			DPFROMREG(fs, MIPSInst_FS(ir));
			DPFROMREG(fd, MIPSInst_FD(ir));
			rv.d = ieee754dp_maddf(fd, fs, ft);
			जाओ copcsr;
		पूर्ण

		हाल fmsubf_op: अणु
			जोड़ ieee754dp ft, fs, fd;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(msubf_d);
			DPFROMREG(ft, MIPSInst_FT(ir));
			DPFROMREG(fs, MIPSInst_FS(ir));
			DPFROMREG(fd, MIPSInst_FD(ir));
			rv.d = ieee754dp_msubf(fd, fs, ft);
			जाओ copcsr;
		पूर्ण

		हाल frपूर्णांक_op: अणु
			जोड़ ieee754dp fs;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(rपूर्णांक_d);
			DPFROMREG(fs, MIPSInst_FS(ir));
			rv.d = ieee754dp_rपूर्णांक(fs);
			जाओ copcsr;
		पूर्ण

		हाल fclass_op: अणु
			जोड़ ieee754dp fs;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(class_d);
			DPFROMREG(fs, MIPSInst_FS(ir));
			rv.l = ieee754dp_2008class(fs);
			rfmt = l_fmt;
			जाओ copcsr;
		पूर्ण

		हाल fmin_op: अणु
			जोड़ ieee754dp fs, ft;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(min_d);
			DPFROMREG(ft, MIPSInst_FT(ir));
			DPFROMREG(fs, MIPSInst_FS(ir));
			rv.d = ieee754dp_fmin(fs, ft);
			जाओ copcsr;
		पूर्ण

		हाल fmina_op: अणु
			जोड़ ieee754dp fs, ft;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(mina_d);
			DPFROMREG(ft, MIPSInst_FT(ir));
			DPFROMREG(fs, MIPSInst_FS(ir));
			rv.d = ieee754dp_fmina(fs, ft);
			जाओ copcsr;
		पूर्ण

		हाल fmax_op: अणु
			जोड़ ieee754dp fs, ft;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(max_d);
			DPFROMREG(ft, MIPSInst_FT(ir));
			DPFROMREG(fs, MIPSInst_FS(ir));
			rv.d = ieee754dp_fmax(fs, ft);
			जाओ copcsr;
		पूर्ण

		हाल fmaxa_op: अणु
			जोड़ ieee754dp fs, ft;

			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(maxa_d);
			DPFROMREG(ft, MIPSInst_FT(ir));
			DPFROMREG(fs, MIPSInst_FS(ir));
			rv.d = ieee754dp_fmaxa(fs, ft);
			जाओ copcsr;
		पूर्ण

		हाल भ_असल_op:
			MIPS_FPU_EMU_INC_STATS(असल_d);
			handler.u = ieee754dp_असल;
			जाओ dcopuop;

		हाल fneg_op:
			MIPS_FPU_EMU_INC_STATS(neg_d);
			handler.u = ieee754dp_neg;
			जाओ dcopuop;

		हाल fmov_op:
			/* an easy one */
			MIPS_FPU_EMU_INC_STATS(mov_d);
			DPFROMREG(rv.d, MIPSInst_FS(ir));
			जाओ copcsr;

			/* binary op on handler */
dcopbop:
			DPFROMREG(fs, MIPSInst_FS(ir));
			DPFROMREG(ft, MIPSInst_FT(ir));

			rv.d = (*handler.b) (fs, ft);
			जाओ copcsr;
dcopuop:
			DPFROMREG(fs, MIPSInst_FS(ir));
			rv.d = (*handler.u) (fs);
			जाओ copcsr;

		/*
		 * unary conv ops
		 */
		हाल fcvts_op:
			MIPS_FPU_EMU_INC_STATS(cvt_s_d);
			DPFROMREG(fs, MIPSInst_FS(ir));
			rv.s = ieee754sp_fdp(fs);
			rfmt = s_fmt;
			जाओ copcsr;

		हाल fcvtd_op:
			वापस संक_अवैध;	/* not defined */

		हाल fcvtw_op:
			MIPS_FPU_EMU_INC_STATS(cvt_w_d);
			DPFROMREG(fs, MIPSInst_FS(ir));
			rv.w = ieee754dp_tपूर्णांक(fs);	/* wrong */
			rfmt = w_fmt;
			जाओ copcsr;

		हाल fround_op:
		हाल ftrunc_op:
		हाल fउच्चमान_op:
		हाल fन्यूनमान_op:
			अगर (!cpu_has_mips_2_3_4_5_r)
				वापस संक_अवैध;

			अगर (MIPSInst_FUNC(ir) == fउच्चमान_op)
				MIPS_FPU_EMU_INC_STATS(उच्चमान_w_d);
			अगर (MIPSInst_FUNC(ir) == fन्यूनमान_op)
				MIPS_FPU_EMU_INC_STATS(न्यूनमान_w_d);
			अगर (MIPSInst_FUNC(ir) == fround_op)
				MIPS_FPU_EMU_INC_STATS(round_w_d);
			अगर (MIPSInst_FUNC(ir) == ftrunc_op)
				MIPS_FPU_EMU_INC_STATS(trunc_w_d);

			oldrm = ieee754_csr.rm;
			DPFROMREG(fs, MIPSInst_FS(ir));
			ieee754_csr.rm = MIPSInst_FUNC(ir);
			rv.w = ieee754dp_tपूर्णांक(fs);
			ieee754_csr.rm = oldrm;
			rfmt = w_fmt;
			जाओ copcsr;

		हाल fsel_op:
			अगर (!cpu_has_mips_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(sel_d);
			DPFROMREG(fd, MIPSInst_FD(ir));
			अगर (fd.bits & 0x1)
				DPFROMREG(rv.d, MIPSInst_FT(ir));
			अन्यथा
				DPFROMREG(rv.d, MIPSInst_FS(ir));
			अवरोध;

		हाल fcvtl_op:
			अगर (!cpu_has_mips_3_4_5_64_r2_r6)
				वापस संक_अवैध;

			MIPS_FPU_EMU_INC_STATS(cvt_l_d);
			DPFROMREG(fs, MIPSInst_FS(ir));
			rv.l = ieee754dp_tदीर्घ(fs);
			rfmt = l_fmt;
			जाओ copcsr;

		हाल froundl_op:
		हाल ftruncl_op:
		हाल fउच्चमानl_op:
		हाल fन्यूनमानl_op:
			अगर (!cpu_has_mips_3_4_5_64_r2_r6)
				वापस संक_अवैध;

			अगर (MIPSInst_FUNC(ir) == fउच्चमानl_op)
				MIPS_FPU_EMU_INC_STATS(उच्चमान_l_d);
			अगर (MIPSInst_FUNC(ir) == fन्यूनमानl_op)
				MIPS_FPU_EMU_INC_STATS(न्यूनमान_l_d);
			अगर (MIPSInst_FUNC(ir) == froundl_op)
				MIPS_FPU_EMU_INC_STATS(round_l_d);
			अगर (MIPSInst_FUNC(ir) == ftruncl_op)
				MIPS_FPU_EMU_INC_STATS(trunc_l_d);

			oldrm = ieee754_csr.rm;
			DPFROMREG(fs, MIPSInst_FS(ir));
			ieee754_csr.rm = MIPSInst_FUNC(ir);
			rv.l = ieee754dp_tदीर्घ(fs);
			ieee754_csr.rm = oldrm;
			rfmt = l_fmt;
			जाओ copcsr;

		शेष:
			अगर (!NO_R6EMU && MIPSInst_FUNC(ir) >= fcmp_op) अणु
				अचिन्हित पूर्णांक cmpop;
				जोड़ ieee754dp fs, ft;

				cmpop = MIPSInst_FUNC(ir) - fcmp_op;
				DPFROMREG(fs, MIPSInst_FS(ir));
				DPFROMREG(ft, MIPSInst_FT(ir));
				rv.w = ieee754dp_cmp(fs, ft,
					cmptab[cmpop & 0x7], cmpop & 0x8);
				rfmt = -1;
				अगर ((cmpop & 0x8)
					&&
					ieee754_cxtest
					(IEEE754_INVALID_OPERATION))
					rcsr = FPU_CSR_INV_X | FPU_CSR_INV_S;
				अन्यथा
					जाओ copcsr;

			पूर्ण
			अन्यथा अणु
				वापस संक_अवैध;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल w_fmt: अणु
		जोड़ ieee754dp fs;

		चयन (MIPSInst_FUNC(ir)) अणु
		हाल fcvts_op:
			/* convert word to single precision real */
			MIPS_FPU_EMU_INC_STATS(cvt_s_w);
			SPFROMREG(fs, MIPSInst_FS(ir));
			rv.s = ieee754sp_fपूर्णांक(fs.bits);
			rfmt = s_fmt;
			जाओ copcsr;
		हाल fcvtd_op:
			/* convert word to द्विगुन precision real */
			MIPS_FPU_EMU_INC_STATS(cvt_d_w);
			SPFROMREG(fs, MIPSInst_FS(ir));
			rv.d = ieee754dp_fपूर्णांक(fs.bits);
			rfmt = d_fmt;
			जाओ copcsr;
		शेष: अणु
			/* Emulating the new CMP.condn.fmt R6 inकाष्ठाion */
#घोषणा CMPOP_MASK	0x7
#घोषणा SIGN_BIT	(0x1 << 3)
#घोषणा PREDICATE_BIT	(0x1 << 4)

			पूर्णांक cmpop = MIPSInst_FUNC(ir) & CMPOP_MASK;
			पूर्णांक sig = MIPSInst_FUNC(ir) & SIGN_BIT;
			जोड़ ieee754sp fs, ft;

			/* This is an R6 only inकाष्ठाion */
			अगर (!cpu_has_mips_r6 ||
			    (MIPSInst_FUNC(ir) & 0x20))
				वापस संक_अवैध;

			अगर (!sig) अणु
				अगर (!(MIPSInst_FUNC(ir) & PREDICATE_BIT)) अणु
					चयन (cmpop) अणु
					हाल 0:
					MIPS_FPU_EMU_INC_STATS(cmp_af_s);
					अवरोध;
					हाल 1:
					MIPS_FPU_EMU_INC_STATS(cmp_un_s);
					अवरोध;
					हाल 2:
					MIPS_FPU_EMU_INC_STATS(cmp_eq_s);
					अवरोध;
					हाल 3:
					MIPS_FPU_EMU_INC_STATS(cmp_ueq_s);
					अवरोध;
					हाल 4:
					MIPS_FPU_EMU_INC_STATS(cmp_lt_s);
					अवरोध;
					हाल 5:
					MIPS_FPU_EMU_INC_STATS(cmp_ult_s);
					अवरोध;
					हाल 6:
					MIPS_FPU_EMU_INC_STATS(cmp_le_s);
					अवरोध;
					हाल 7:
					MIPS_FPU_EMU_INC_STATS(cmp_ule_s);
					अवरोध;
					पूर्ण
				पूर्ण अन्यथा अणु
					चयन (cmpop) अणु
					हाल 1:
					MIPS_FPU_EMU_INC_STATS(cmp_or_s);
					अवरोध;
					हाल 2:
					MIPS_FPU_EMU_INC_STATS(cmp_une_s);
					अवरोध;
					हाल 3:
					MIPS_FPU_EMU_INC_STATS(cmp_ne_s);
					अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (!(MIPSInst_FUNC(ir) & PREDICATE_BIT)) अणु
					चयन (cmpop) अणु
					हाल 0:
					MIPS_FPU_EMU_INC_STATS(cmp_saf_s);
					अवरोध;
					हाल 1:
					MIPS_FPU_EMU_INC_STATS(cmp_sun_s);
					अवरोध;
					हाल 2:
					MIPS_FPU_EMU_INC_STATS(cmp_seq_s);
					अवरोध;
					हाल 3:
					MIPS_FPU_EMU_INC_STATS(cmp_sueq_s);
					अवरोध;
					हाल 4:
					MIPS_FPU_EMU_INC_STATS(cmp_slt_s);
					अवरोध;
					हाल 5:
					MIPS_FPU_EMU_INC_STATS(cmp_sult_s);
					अवरोध;
					हाल 6:
					MIPS_FPU_EMU_INC_STATS(cmp_sle_s);
					अवरोध;
					हाल 7:
					MIPS_FPU_EMU_INC_STATS(cmp_sule_s);
					अवरोध;
					पूर्ण
				पूर्ण अन्यथा अणु
					चयन (cmpop) अणु
					हाल 1:
					MIPS_FPU_EMU_INC_STATS(cmp_sor_s);
					अवरोध;
					हाल 2:
					MIPS_FPU_EMU_INC_STATS(cmp_sune_s);
					अवरोध;
					हाल 3:
					MIPS_FPU_EMU_INC_STATS(cmp_sne_s);
					अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			/* fmt is w_fmt क्रम single precision so fix it */
			rfmt = s_fmt;
			/* शेष to false */
			rv.w = 0;

			/* CMP.condn.S */
			SPFROMREG(fs, MIPSInst_FS(ir));
			SPFROMREG(ft, MIPSInst_FT(ir));

			/* positive predicates */
			अगर (!(MIPSInst_FUNC(ir) & PREDICATE_BIT)) अणु
				अगर (ieee754sp_cmp(fs, ft, cmptab[cmpop],
						  sig))
				    rv.w = -1; /* true, all 1s */
				अगर ((sig) &&
				    ieee754_cxtest(IEEE754_INVALID_OPERATION))
					rcsr = FPU_CSR_INV_X | FPU_CSR_INV_S;
				अन्यथा
					जाओ copcsr;
			पूर्ण अन्यथा अणु
				/* negative predicates */
				चयन (cmpop) अणु
				हाल 1:
				हाल 2:
				हाल 3:
					अगर (ieee754sp_cmp(fs, ft,
							  negative_cmptab[cmpop],
							  sig))
						rv.w = -1; /* true, all 1s */
					अगर (sig &&
					    ieee754_cxtest(IEEE754_INVALID_OPERATION))
						rcsr = FPU_CSR_INV_X | FPU_CSR_INV_S;
					अन्यथा
						जाओ copcsr;
					अवरोध;
				शेष:
					/* Reserved R6 ops */
					वापस संक_अवैध;
				पूर्ण
			पूर्ण
			अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	हाल l_fmt:

		अगर (!cpu_has_mips_3_4_5_64_r2_r6)
			वापस संक_अवैध;

		DIFROMREG(bits, MIPSInst_FS(ir));

		चयन (MIPSInst_FUNC(ir)) अणु
		हाल fcvts_op:
			/* convert दीर्घ to single precision real */
			MIPS_FPU_EMU_INC_STATS(cvt_s_l);
			rv.s = ieee754sp_fदीर्घ(bits);
			rfmt = s_fmt;
			जाओ copcsr;
		हाल fcvtd_op:
			/* convert दीर्घ to द्विगुन precision real */
			MIPS_FPU_EMU_INC_STATS(cvt_d_l);
			rv.d = ieee754dp_fदीर्घ(bits);
			rfmt = d_fmt;
			जाओ copcsr;
		शेष: अणु
			/* Emulating the new CMP.condn.fmt R6 inकाष्ठाion */
			पूर्णांक cmpop = MIPSInst_FUNC(ir) & CMPOP_MASK;
			पूर्णांक sig = MIPSInst_FUNC(ir) & SIGN_BIT;
			जोड़ ieee754dp fs, ft;

			अगर (!cpu_has_mips_r6 ||
			    (MIPSInst_FUNC(ir) & 0x20))
				वापस संक_अवैध;

			अगर (!sig) अणु
				अगर (!(MIPSInst_FUNC(ir) & PREDICATE_BIT)) अणु
					चयन (cmpop) अणु
					हाल 0:
					MIPS_FPU_EMU_INC_STATS(cmp_af_d);
					अवरोध;
					हाल 1:
					MIPS_FPU_EMU_INC_STATS(cmp_un_d);
					अवरोध;
					हाल 2:
					MIPS_FPU_EMU_INC_STATS(cmp_eq_d);
					अवरोध;
					हाल 3:
					MIPS_FPU_EMU_INC_STATS(cmp_ueq_d);
					अवरोध;
					हाल 4:
					MIPS_FPU_EMU_INC_STATS(cmp_lt_d);
					अवरोध;
					हाल 5:
					MIPS_FPU_EMU_INC_STATS(cmp_ult_d);
					अवरोध;
					हाल 6:
					MIPS_FPU_EMU_INC_STATS(cmp_le_d);
					अवरोध;
					हाल 7:
					MIPS_FPU_EMU_INC_STATS(cmp_ule_d);
					अवरोध;
					पूर्ण
				पूर्ण अन्यथा अणु
					चयन (cmpop) अणु
					हाल 1:
					MIPS_FPU_EMU_INC_STATS(cmp_or_d);
					अवरोध;
					हाल 2:
					MIPS_FPU_EMU_INC_STATS(cmp_une_d);
					अवरोध;
					हाल 3:
					MIPS_FPU_EMU_INC_STATS(cmp_ne_d);
					अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (!(MIPSInst_FUNC(ir) & PREDICATE_BIT)) अणु
					चयन (cmpop) अणु
					हाल 0:
					MIPS_FPU_EMU_INC_STATS(cmp_saf_d);
					अवरोध;
					हाल 1:
					MIPS_FPU_EMU_INC_STATS(cmp_sun_d);
					अवरोध;
					हाल 2:
					MIPS_FPU_EMU_INC_STATS(cmp_seq_d);
					अवरोध;
					हाल 3:
					MIPS_FPU_EMU_INC_STATS(cmp_sueq_d);
					अवरोध;
					हाल 4:
					MIPS_FPU_EMU_INC_STATS(cmp_slt_d);
					अवरोध;
					हाल 5:
					MIPS_FPU_EMU_INC_STATS(cmp_sult_d);
					अवरोध;
					हाल 6:
					MIPS_FPU_EMU_INC_STATS(cmp_sle_d);
					अवरोध;
					हाल 7:
					MIPS_FPU_EMU_INC_STATS(cmp_sule_d);
					अवरोध;
					पूर्ण
				पूर्ण अन्यथा अणु
					चयन (cmpop) अणु
					हाल 1:
					MIPS_FPU_EMU_INC_STATS(cmp_sor_d);
					अवरोध;
					हाल 2:
					MIPS_FPU_EMU_INC_STATS(cmp_sune_d);
					अवरोध;
					हाल 3:
					MIPS_FPU_EMU_INC_STATS(cmp_sne_d);
					अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			/* fmt is l_fmt क्रम द्विगुन precision so fix it */
			rfmt = d_fmt;
			/* शेष to false */
			rv.l = 0;

			/* CMP.condn.D */
			DPFROMREG(fs, MIPSInst_FS(ir));
			DPFROMREG(ft, MIPSInst_FT(ir));

			/* positive predicates */
			अगर (!(MIPSInst_FUNC(ir) & PREDICATE_BIT)) अणु
				अगर (ieee754dp_cmp(fs, ft,
						  cmptab[cmpop], sig))
				    rv.l = -1LL; /* true, all 1s */
				अगर (sig &&
				    ieee754_cxtest(IEEE754_INVALID_OPERATION))
					rcsr = FPU_CSR_INV_X | FPU_CSR_INV_S;
				अन्यथा
					जाओ copcsr;
			पूर्ण अन्यथा अणु
				/* negative predicates */
				चयन (cmpop) अणु
				हाल 1:
				हाल 2:
				हाल 3:
					अगर (ieee754dp_cmp(fs, ft,
							  negative_cmptab[cmpop],
							  sig))
						rv.l = -1LL; /* true, all 1s */
					अगर (sig &&
					    ieee754_cxtest(IEEE754_INVALID_OPERATION))
						rcsr = FPU_CSR_INV_X | FPU_CSR_INV_S;
					अन्यथा
						जाओ copcsr;
					अवरोध;
				शेष:
					/* Reserved R6 ops */
					वापस संक_अवैध;
				पूर्ण
			पूर्ण
			अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		वापस संक_अवैध;
	पूर्ण

	/*
	 * Update the fpu CSR रेजिस्टर क्रम this operation.
	 * If an exception is required, generate a tidy संक_भ_त्रुटि exception,
	 * without updating the result रेजिस्टर.
	 * Note: cause exception bits करो not accumulate, they are rewritten
	 * क्रम each op; only the flag/sticky bits accumulate.
	 */
	ctx->fcr31 = (ctx->fcr31 & ~FPU_CSR_ALL_X) | rcsr;
	अगर ((ctx->fcr31 >> 5) & ctx->fcr31 & FPU_CSR_ALL_E) अणु
		/*prपूर्णांकk ("SIGFPE: FPU csr = %08x\n",ctx->fcr31); */
		वापस संक_भ_त्रुटि;
	पूर्ण

	/*
	 * Now we can safely ग_लिखो the result back to the रेजिस्टर file.
	 */
	चयन (rfmt) अणु
	हाल -1:

		अगर (cpu_has_mips_4_5_r)
			cbit = fpucondbit[MIPSInst_FD(ir) >> 2];
		अन्यथा
			cbit = FPU_CSR_COND;
		अगर (rv.w)
			ctx->fcr31 |= cbit;
		अन्यथा
			ctx->fcr31 &= ~cbit;
		अवरोध;

	हाल d_fmt:
		DPTOREG(rv.d, MIPSInst_FD(ir));
		अवरोध;
	हाल s_fmt:
		SPTOREG(rv.s, MIPSInst_FD(ir));
		अवरोध;
	हाल w_fmt:
		SITOREG(rv.w, MIPSInst_FD(ir));
		अवरोध;
	हाल l_fmt:
		अगर (!cpu_has_mips_3_4_5_64_r2_r6)
			वापस संक_अवैध;

		DITOREG(rv.l, MIPSInst_FD(ir));
		अवरोध;
	शेष:
		वापस संक_अवैध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Emulate FPU inकाष्ठाions.
 *
 * If we use FPU hardware, then we have been typically called to handle
 * an unimplemented operation, such as where an opeअक्रम is a NaN or
 * denormalized.  In that हाल निकास the emulation loop after a single
 * iteration so as to let hardware execute any subsequent inकाष्ठाions.
 *
 * If we have no FPU hardware or it has been disabled, then जारी
 * emulating भग्नing-poपूर्णांक inकाष्ठाions until one of these conditions
 * has occurred:
 *
 * - a non-FPU inकाष्ठाion has been encountered,
 *
 * - an attempt to emulate has ended with a संकेत,
 *
 * - the ISA mode has been चयनed.
 *
 * We need to terminate the emulation loop अगर we got चयनed to the
 * MIPS16 mode, whether supported or not, so that we करो not attempt
 * to emulate a MIPS16 inकाष्ठाion as a regular MIPS FPU inकाष्ठाion.
 * Similarly अगर we got चयनed to the microMIPS mode and only the
 * regular MIPS mode is supported, so that we करो not attempt to emulate
 * a microMIPS inकाष्ठाion as a regular MIPS FPU inकाष्ठाion.  Or अगर
 * we got चयनed to the regular MIPS mode and only the microMIPS mode
 * is supported, so that we करो not attempt to emulate a regular MIPS
 * inकाष्ठाion that should cause an Address Error exception instead.
 * For simplicity we always terminate upon an ISA mode चयन.
 */
पूर्णांक fpu_emulator_cop1Handler(काष्ठा pt_regs *xcp, काष्ठा mips_fpu_काष्ठा *ctx,
	पूर्णांक has_fpu, व्योम __user **fault_addr)
अणु
	अचिन्हित दीर्घ oldepc, prevepc;
	काष्ठा mm_decoded_insn dec_insn;
	u16 instr[4];
	u16 *instr_ptr;
	पूर्णांक sig = 0;

	/*
	 * Initialize context अगर it hasn't been used alपढ़ोy, otherwise ensure
	 * it has been saved to काष्ठा thपढ़ो_काष्ठा.
	 */
	अगर (!init_fp_ctx(current))
		lose_fpu(1);

	oldepc = xcp->cp0_epc;
	करो अणु
		prevepc = xcp->cp0_epc;

		अगर (get_isa16_mode(prevepc) && cpu_has_mmips) अणु
			/*
			 * Get next 2 microMIPS inकाष्ठाions and convert them
			 * पूर्णांकo 32-bit inकाष्ठाions.
			 */
			अगर ((get_user(instr[0], (u16 __user *)msk_isa16_mode(xcp->cp0_epc))) ||
			    (get_user(instr[1], (u16 __user *)msk_isa16_mode(xcp->cp0_epc + 2))) ||
			    (get_user(instr[2], (u16 __user *)msk_isa16_mode(xcp->cp0_epc + 4))) ||
			    (get_user(instr[3], (u16 __user *)msk_isa16_mode(xcp->cp0_epc + 6)))) अणु
				MIPS_FPU_EMU_INC_STATS(errors);
				वापस SIGBUS;
			पूर्ण
			instr_ptr = instr;

			/* Get first inकाष्ठाion. */
			अगर (mm_insn_16bit(*instr_ptr)) अणु
				/* Duplicate the half-word. */
				dec_insn.insn = (*instr_ptr << 16) |
					(*instr_ptr);
				/* 16-bit inकाष्ठाion. */
				dec_insn.pc_inc = 2;
				instr_ptr += 1;
			पूर्ण अन्यथा अणु
				dec_insn.insn = (*instr_ptr << 16) |
					*(instr_ptr+1);
				/* 32-bit inकाष्ठाion. */
				dec_insn.pc_inc = 4;
				instr_ptr += 2;
			पूर्ण
			/* Get second inकाष्ठाion. */
			अगर (mm_insn_16bit(*instr_ptr)) अणु
				/* Duplicate the half-word. */
				dec_insn.next_insn = (*instr_ptr << 16) |
					(*instr_ptr);
				/* 16-bit inकाष्ठाion. */
				dec_insn.next_pc_inc = 2;
			पूर्ण अन्यथा अणु
				dec_insn.next_insn = (*instr_ptr << 16) |
					*(instr_ptr+1);
				/* 32-bit inकाष्ठाion. */
				dec_insn.next_pc_inc = 4;
			पूर्ण
			dec_insn.micro_mips_mode = 1;
		पूर्ण अन्यथा अणु
			अगर ((get_user(dec_insn.insn,
			    (mips_inकाष्ठाion __user *) xcp->cp0_epc)) ||
			    (get_user(dec_insn.next_insn,
			    (mips_inकाष्ठाion __user *)(xcp->cp0_epc+4)))) अणु
				MIPS_FPU_EMU_INC_STATS(errors);
				वापस SIGBUS;
			पूर्ण
			dec_insn.pc_inc = 4;
			dec_insn.next_pc_inc = 4;
			dec_insn.micro_mips_mode = 0;
		पूर्ण

		अगर ((dec_insn.insn == 0) ||
		   ((dec_insn.pc_inc == 2) &&
		   ((dec_insn.insn & 0xffff) == MM_NOP16)))
			xcp->cp0_epc += dec_insn.pc_inc;	/* Skip NOPs */
		अन्यथा अणु
			/*
			 * The 'ieee754_csr' is an alias of ctx->fcr31.
			 * No need to copy ctx->fcr31 to ieee754_csr.
			 */
			sig = cop1Emulate(xcp, ctx, dec_insn, fault_addr);
		पूर्ण

		अगर (has_fpu)
			अवरोध;
		अगर (sig)
			अवरोध;
		/*
		 * We have to check क्रम the ISA bit explicitly here,
		 * because `get_isa16_mode' may वापस 0 अगर support
		 * क्रम code compression has been globally disabled,
		 * or otherwise we may produce the wrong संकेत or
		 * even proceed successfully where we must not.
		 */
		अगर ((xcp->cp0_epc ^ prevepc) & 0x1)
			अवरोध;

		cond_resched();
	पूर्ण जबतक (xcp->cp0_epc > prevepc);

	/* संक_अवैध indicates a non-fpu inकाष्ठाion */
	अगर (sig == संक_अवैध && xcp->cp0_epc != oldepc)
		/* but अगर EPC has advanced, then ignore it */
		sig = 0;

	वापस sig;
पूर्ण
