<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux/PA-RISC Project (http://www.parisc-linux.org/)
 *
 * Floating-poपूर्णांक emulation code
 *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) <bame@debian.org>
 */
/*
 * BEGIN_DESC
 *
 *  File:
 *	@(#)	pa/fp/fpudispatch.c		$Revision: 1.1 $
 *
 *  Purpose:
 *	<<please update with a synopsis of the functionality provided by this file>>
 *
 *  External Interfaces:
 *	<<the following list was स्वतःgenerated, please review>>
 *	emfpudispatch(ir, dummy1, dummy2, fpregs)
 *	fpudispatch(ir, excp_code, holder, fpregs)
 *
 *  Internal Interfaces:
 *	<<the following list was स्वतःgenerated, please review>>
 *	अटल u_पूर्णांक decode_06(u_पूर्णांक, u_पूर्णांक *)
 *	अटल u_पूर्णांक decode_0c(u_पूर्णांक, u_पूर्णांक, u_पूर्णांक, u_पूर्णांक *)
 *	अटल u_पूर्णांक decode_0e(u_पूर्णांक, u_पूर्णांक, u_पूर्णांक, u_पूर्णांक *)
 *	अटल u_पूर्णांक decode_26(u_पूर्णांक, u_पूर्णांक *)
 *	अटल u_पूर्णांक decode_2e(u_पूर्णांक, u_पूर्णांक *)
 *	अटल व्योम update_status_cbit(u_पूर्णांक *, u_पूर्णांक, u_पूर्णांक, u_पूर्णांक)
 *
 *  Theory:
 *	<<please update with a overview of the operation of this file>>
 *
 * END_DESC
*/

#घोषणा FPUDEBUG 0

#समावेश "float.h"
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/processor.h>
/* #समावेश <sys/debug.h> */
/* #समावेश <machine/sys/mdep_निजी.h> */

#घोषणा COPR_INST 0x30000000

/*
 * definition of extru macro.  If pos and len are स्थिरants, the compiler
 * will generate an extru inकाष्ठाion when optimized
 */
#घोषणा extru(r,pos,len)	(((r) >> (31-(pos))) & (( 1 << (len)) - 1))
/* definitions of bit field locations in the inकाष्ठाion */
#घोषणा fpmajorpos 5
#घोषणा fpr1pos	10
#घोषणा fpr2pos 15
#घोषणा fptpos	31
#घोषणा fpsubpos 18
#घोषणा fpclass1subpos 16
#घोषणा fpclasspos 22
#घोषणा fpfmtpos 20
#घोषणा fpdfpos 18
#घोषणा fpnulpos 26
/*
 * the following are the extra bits क्रम the 0E major op
 */
#घोषणा fpxr1pos 24
#घोषणा fpxr2pos 19
#घोषणा fpxtpos 25
#घोषणा fpxpos 23
#घोषणा fp0efmtpos 20
/*
 * the following are क्रम the multi-ops
 */
#घोषणा fprm1pos 10
#घोषणा fprm2pos 15
#घोषणा fpपंचांगpos 31
#घोषणा fprapos 25
#घोषणा fptapos 20
#घोषणा fpmultअगरmt 26
/*
 * the following are क्रम the fused FP inकाष्ठाions
 */
     /* fprm1pos 10 */
     /* fprm2pos 15 */
#घोषणा fpraupos 18
#घोषणा fpxrm2pos 19
     /* fpfmtpos 20 */
#घोषणा fpralpos 23
#घोषणा fpxrm1pos 24
     /* fpxtpos 25 */
#घोषणा fpfusedsubop 26
     /* fptpos	31 */

/*
 * offset to स्थिरant zero in the FP emulation रेजिस्टरs
 */
#घोषणा fpzeroreg (32*माप(द्विगुन)/माप(u_पूर्णांक))

/*
 * extract the major opcode from the inकाष्ठाion
 */
#घोषणा get_major(op) extru(op,fpmajorpos,6)
/*
 * extract the two bit class field from the FP inकाष्ठाion. The class is at bit
 * positions 21-22
 */
#घोषणा get_class(op) extru(op,fpclasspos,2)
/*
 * extract the 3 bit subop field.  For all but class 1 inकाष्ठाions, it is
 * located at bit positions 16-18
 */
#घोषणा get_subop(op) extru(op,fpsubpos,3)
/*
 * extract the 2 or 3 bit subop field from class 1 inकाष्ठाions.  It is located
 * at bit positions 15-16 (PA1.1) or 14-16 (PA2.0)
 */
#घोषणा get_subop1_PA1_1(op) extru(op,fpclass1subpos,2)	/* PA89 (1.1) fmt */
#घोषणा get_subop1_PA2_0(op) extru(op,fpclass1subpos,3)	/* PA 2.0 fmt */

/* definitions of unimplemented exceptions */
#घोषणा MAJOR_0C_EXCP	0x09
#घोषणा MAJOR_0E_EXCP	0x0b
#घोषणा MAJOR_06_EXCP	0x03
#घोषणा MAJOR_26_EXCP	0x23
#घोषणा MAJOR_2E_EXCP	0x2b
#घोषणा PA83_UNIMP_EXCP	0x01

/*
 * Special Defines क्रम TIMEX specअगरic code
 */

#घोषणा FPU_TYPE_FLAG_POS (EM_FPU_TYPE_OFFSET>>2)
#घोषणा TIMEX_ROLEX_FPU_MASK (TIMEX_EXTEN_FLAG|ROLEX_EXTEN_FLAG)

/*
 * Static function definitions
 */
#घोषणा _PROTOTYPES
#अगर defined(_PROTOTYPES) || defined(_lपूर्णांक)
अटल u_पूर्णांक decode_0c(u_पूर्णांक, u_पूर्णांक, u_पूर्णांक, u_पूर्णांक *);
अटल u_पूर्णांक decode_0e(u_पूर्णांक, u_पूर्णांक, u_पूर्णांक, u_पूर्णांक *);
अटल u_पूर्णांक decode_06(u_पूर्णांक, u_पूर्णांक *);
अटल u_पूर्णांक decode_26(u_पूर्णांक, u_पूर्णांक *);
अटल u_पूर्णांक decode_2e(u_पूर्णांक, u_पूर्णांक *);
अटल व्योम update_status_cbit(u_पूर्णांक *, u_पूर्णांक, u_पूर्णांक, u_पूर्णांक);
#अन्यथा /* !_PROTOTYPES&&!_lपूर्णांक */
अटल u_पूर्णांक decode_0c();
अटल u_पूर्णांक decode_0e();
अटल u_पूर्णांक decode_06();
अटल u_पूर्णांक decode_26();
अटल u_पूर्णांक decode_2e();
अटल व्योम update_status_cbit();
#पूर्ण_अगर /* _PROTOTYPES&&!_lपूर्णांक */

#घोषणा VASSERT(x)

अटल व्योम parisc_linux_get_fpu_type(u_पूर्णांक fpregs[])
अणु
	/* on pa-linux the fpu type is not filled in by the
	 * caller; it is स्थिरructed here  
	 */ 
	अगर (boot_cpu_data.cpu_type == pcxs)
		fpregs[FPU_TYPE_FLAG_POS] = TIMEX_EXTEN_FLAG;
	अन्यथा अगर (boot_cpu_data.cpu_type == pcxt ||
	         boot_cpu_data.cpu_type == pcxt_)
		fpregs[FPU_TYPE_FLAG_POS] = ROLEX_EXTEN_FLAG;
	अन्यथा अगर (boot_cpu_data.cpu_type >= pcxu)
		fpregs[FPU_TYPE_FLAG_POS] = PA2_0_FPU_FLAG;
पूर्ण

/*
 * this routine will decode the excepting भग्नing poपूर्णांक inकाष्ठाion and
 * call the appropriate emulation routine.
 * It is called by decode_fpu with the following parameters:
 * fpudispatch(current_ir, unimplemented_code, 0, &Fpu_रेजिस्टर)
 * where current_ir is the inकाष्ठाion to be emulated,
 * unimplemented_code is the exception_code that the hardware generated
 * and &Fpu_रेजिस्टर is the address of emulated FP reg 0.
 */
u_पूर्णांक
fpudispatch(u_पूर्णांक ir, u_पूर्णांक excp_code, u_पूर्णांक holder, u_पूर्णांक fpregs[])
अणु
	u_पूर्णांक class, subop;
	u_पूर्णांक fpu_type_flags;

	/* All FP emulation code assumes that पूर्णांकs are 4-bytes in length */
	VASSERT(माप(पूर्णांक) == 4);

	parisc_linux_get_fpu_type(fpregs);

	fpu_type_flags=fpregs[FPU_TYPE_FLAG_POS];  /* get fpu type flags */

	class = get_class(ir);
	अगर (class == 1) अणु
		अगर  (fpu_type_flags & PA2_0_FPU_FLAG)
			subop = get_subop1_PA2_0(ir);
		अन्यथा
			subop = get_subop1_PA1_1(ir);
	पूर्ण
	अन्यथा
		subop = get_subop(ir);

	अगर (FPUDEBUG) prपूर्णांकk("class %d subop %d\n", class, subop);

	चयन (excp_code) अणु
		हाल MAJOR_0C_EXCP:
		हाल PA83_UNIMP_EXCP:
			वापस(decode_0c(ir,class,subop,fpregs));
		हाल MAJOR_0E_EXCP:
			वापस(decode_0e(ir,class,subop,fpregs));
		हाल MAJOR_06_EXCP:
			वापस(decode_06(ir,fpregs));
		हाल MAJOR_26_EXCP:
			वापस(decode_26(ir,fpregs));
		हाल MAJOR_2E_EXCP:
			वापस(decode_2e(ir,fpregs));
		शेष:
			/* "crashme Night Gallery paपूर्णांकing nr 2. (यंत्र_crash.s).
			 * This was fixed क्रम multi-user kernels, but
			 * workstation kernels had a panic here.  This allowed
			 * any arbitrary user to panic the kernel by executing
			 * setting the FP exception रेजिस्टरs to strange values
			 * and generating an emulation trap.  The emulation and
			 * exception code must never be able to panic the
			 * kernel.
			 */
			वापस(UNIMPLEMENTEDEXCEPTION);
	पूर्ण
पूर्ण

/*
 * this routine is called by $emulation_trap to emulate a coprocessor
 * inकाष्ठाion अगर one करोesn't exist
 */
u_पूर्णांक
emfpudispatch(u_पूर्णांक ir, u_पूर्णांक dummy1, u_पूर्णांक dummy2, u_पूर्णांक fpregs[])
अणु
	u_पूर्णांक class, subop, major;
	u_पूर्णांक fpu_type_flags;

	/* All FP emulation code assumes that पूर्णांकs are 4-bytes in length */
	VASSERT(माप(पूर्णांक) == 4);

	fpu_type_flags=fpregs[FPU_TYPE_FLAG_POS];  /* get fpu type flags */

	major = get_major(ir);
	class = get_class(ir);
	अगर (class == 1) अणु
		अगर  (fpu_type_flags & PA2_0_FPU_FLAG)
			subop = get_subop1_PA2_0(ir);
		अन्यथा
			subop = get_subop1_PA1_1(ir);
	पूर्ण
	अन्यथा
		subop = get_subop(ir);
	चयन (major) अणु
		हाल 0x0C:
			वापस(decode_0c(ir,class,subop,fpregs));
		हाल 0x0E:
			वापस(decode_0e(ir,class,subop,fpregs));
		हाल 0x06:
			वापस(decode_06(ir,fpregs));
		हाल 0x26:
			वापस(decode_26(ir,fpregs));
		हाल 0x2E:
			वापस(decode_2e(ir,fpregs));
		शेष:
			वापस(PA83_UNIMP_EXCP);
	पूर्ण
पूर्ण
	

अटल u_पूर्णांक
decode_0c(u_पूर्णांक ir, u_पूर्णांक class, u_पूर्णांक subop, u_पूर्णांक fpregs[])
अणु
	u_पूर्णांक r1,r2,t;		/* opeअक्रम रेजिस्टर offsets */ 
	u_पूर्णांक fmt;		/* also sf क्रम class 1 conversions */
	u_पूर्णांक  df;		/* क्रम class 1 conversions */
	u_पूर्णांक *status;
	u_पूर्णांक retval, local_status;
	u_पूर्णांक fpu_type_flags;

	अगर (ir == COPR_INST) अणु
		fpregs[0] = EMULATION_VERSION << 11;
		वापस(NOEXCEPTION);
	पूर्ण
	status = &fpregs[0];	/* fp status रेजिस्टर */
	local_status = fpregs[0]; /* and local copy */
	r1 = extru(ir,fpr1pos,5) * माप(द्विगुन)/माप(u_पूर्णांक);
	अगर (r1 == 0)		/* map fr0 source to स्थिरant zero */
		r1 = fpzeroreg;
	t = extru(ir,fptpos,5) * माप(द्विगुन)/माप(u_पूर्णांक);
	अगर (t == 0 && class != 2)	/* करोn't allow fr0 as a dest */
		वापस(MAJOR_0C_EXCP);
	fmt = extru(ir,fpfmtpos,2);	/* get fmt completer */

	चयन (class) अणु
	    हाल 0:
		चयन (subop) अणु
			हाल 0:	/* COPR 0,0 emulated above*/
			हाल 1:
				वापस(MAJOR_0C_EXCP);
			हाल 2:	/* FCPY */
				चयन (fmt) अणु
				    हाल 2: /* illegal */
					वापस(MAJOR_0C_EXCP);
				    हाल 3: /* quad */
					t &= ~3;  /* क्रमce to even reg #s */
					r1 &= ~3;
					fpregs[t+3] = fpregs[r1+3];
					fpregs[t+2] = fpregs[r1+2];
				    हाल 1: /* द्विगुन */
					fpregs[t+1] = fpregs[r1+1];
				    हाल 0: /* single */
					fpregs[t] = fpregs[r1];
					वापस(NOEXCEPTION);
				पूर्ण
			हाल 3: /* FABS */
				चयन (fmt) अणु
				    हाल 2: /* illegal */
					वापस(MAJOR_0C_EXCP);
				    हाल 3: /* quad */
					t &= ~3;  /* क्रमce to even reg #s */
					r1 &= ~3;
					fpregs[t+3] = fpregs[r1+3];
					fpregs[t+2] = fpregs[r1+2];
				    हाल 1: /* द्विगुन */
					fpregs[t+1] = fpregs[r1+1];
				    हाल 0: /* single */
					/* copy and clear sign bit */
					fpregs[t] = fpregs[r1] & 0x7fffffff;
					वापस(NOEXCEPTION);
				पूर्ण
			हाल 6: /* FNEG */
				चयन (fmt) अणु
				    हाल 2: /* illegal */
					वापस(MAJOR_0C_EXCP);
				    हाल 3: /* quad */
					t &= ~3;  /* क्रमce to even reg #s */
					r1 &= ~3;
					fpregs[t+3] = fpregs[r1+3];
					fpregs[t+2] = fpregs[r1+2];
				    हाल 1: /* द्विगुन */
					fpregs[t+1] = fpregs[r1+1];
				    हाल 0: /* single */
					/* copy and invert sign bit */
					fpregs[t] = fpregs[r1] ^ 0x80000000;
					वापस(NOEXCEPTION);
				पूर्ण
			हाल 7: /* FNEGABS */
				चयन (fmt) अणु
				    हाल 2: /* illegal */
					वापस(MAJOR_0C_EXCP);
				    हाल 3: /* quad */
					t &= ~3;  /* क्रमce to even reg #s */
					r1 &= ~3;
					fpregs[t+3] = fpregs[r1+3];
					fpregs[t+2] = fpregs[r1+2];
				    हाल 1: /* द्विगुन */
					fpregs[t+1] = fpregs[r1+1];
				    हाल 0: /* single */
					/* copy and set sign bit */
					fpregs[t] = fpregs[r1] | 0x80000000;
					वापस(NOEXCEPTION);
				पूर्ण
			हाल 4: /* FSQRT */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_fवर्ग_मूल(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1:
					वापस(dbl_fवर्ग_मूल(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2:
				    हाल 3: /* quad not implemented */
					वापस(MAJOR_0C_EXCP);
				पूर्ण
			हाल 5: /* FRND */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_frnd(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1:
					वापस(dbl_frnd(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2:
				    हाल 3: /* quad not implemented */
					वापस(MAJOR_0C_EXCP);
				पूर्ण
		पूर्ण /* end of चयन (subop) */

	हाल 1: /* class 1 */
		df = extru(ir,fpdfpos,2); /* get dest क्रमmat */
		अगर ((df & 2) || (fmt & 2)) अणु
			/*
			 * fmt's 2 and 3 are illegal of not implemented
			 * quad conversions
			 */
			वापस(MAJOR_0C_EXCP);
		पूर्ण
		/*
		 * encode source and dest क्रमmats पूर्णांकo 2 bits.
		 * high bit is source, low bit is dest.
		 * bit = 1 --> द्विगुन precision
		 */
		fmt = (fmt << 1) | df;
		चयन (subop) अणु
			हाल 0: /* FCNVFF */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(MAJOR_0C_EXCP);
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvff(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvff(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(MAJOR_0C_EXCP);
				पूर्ण
			हाल 1: /* FCNVXF */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(sgl_to_sgl_fcnvxf(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvxf(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvxf(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(dbl_to_dbl_fcnvxf(&fpregs[r1],0,
						&fpregs[t],status));
				पूर्ण
			हाल 2: /* FCNVFX */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(sgl_to_sgl_fcnvfx(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvfx(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvfx(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(dbl_to_dbl_fcnvfx(&fpregs[r1],0,
						&fpregs[t],status));
				पूर्ण
			हाल 3: /* FCNVFXT */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(sgl_to_sgl_fcnvfxt(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvfxt(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvfxt(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(dbl_to_dbl_fcnvfxt(&fpregs[r1],0,
						&fpregs[t],status));
				पूर्ण
			हाल 5: /* FCNVUF (PA2.0 only) */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(sgl_to_sgl_fcnvuf(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvuf(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvuf(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(dbl_to_dbl_fcnvuf(&fpregs[r1],0,
						&fpregs[t],status));
				पूर्ण
			हाल 6: /* FCNVFU (PA2.0 only) */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(sgl_to_sgl_fcnvfu(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvfu(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvfu(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(dbl_to_dbl_fcnvfu(&fpregs[r1],0,
						&fpregs[t],status));
				पूर्ण
			हाल 7: /* FCNVFUT (PA2.0 only) */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(sgl_to_sgl_fcnvfut(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvfut(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvfut(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(dbl_to_dbl_fcnvfut(&fpregs[r1],0,
						&fpregs[t],status));
				पूर्ण
			हाल 4: /* undefined */
				वापस(MAJOR_0C_EXCP);
		पूर्ण /* end of चयन subop */

	हाल 2: /* class 2 */
		fpu_type_flags=fpregs[FPU_TYPE_FLAG_POS];
		r2 = extru(ir, fpr2pos, 5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (r2 == 0)
			r2 = fpzeroreg;
		अगर  (fpu_type_flags & PA2_0_FPU_FLAG) अणु
			/* FTEST अगर nullअगरy bit set, otherwise FCMP */
			अगर (extru(ir, fpnulpos, 1)) अणु  /* FTEST */
				चयन (fmt) अणु
				    हाल 0:
					/*
					 * arg0 is not used
					 * second param is the t field used क्रम
					 * ftest,acc and ftest,rej
					 * third param is the subop (y-field)
					 */
					BUG();
					/* Unsupported
					 * वापस(ftest(0L,extru(ir,fptpos,5),
					 *	 &fpregs[0],subop));
					 */
				    हाल 1:
				    हाल 2:
				    हाल 3:
					वापस(MAJOR_0C_EXCP);
				पूर्ण
			पूर्ण अन्यथा अणु  /* FCMP */
				चयन (fmt) अणु
				    हाल 0:
					retval = sgl_fcmp(&fpregs[r1],
						&fpregs[r2],extru(ir,fptpos,5),
						&local_status);
					update_status_cbit(status,local_status,
						fpu_type_flags, subop);
					वापस(retval);
				    हाल 1:
					retval = dbl_fcmp(&fpregs[r1],
						&fpregs[r2],extru(ir,fptpos,5),
						&local_status);
					update_status_cbit(status,local_status,
						fpu_type_flags, subop);
					वापस(retval);
				    हाल 2: /* illegal */
				    हाल 3: /* quad not implemented */
					वापस(MAJOR_0C_EXCP);
				पूर्ण
			पूर्ण
		पूर्ण  /* end of अगर क्रम PA2.0 */
		अन्यथा अणु	/* PA1.0 & PA1.1 */
		    चयन (subop) अणु
			हाल 2:
			हाल 3:
			हाल 4:
			हाल 5:
			हाल 6:
			हाल 7:
				वापस(MAJOR_0C_EXCP);
			हाल 0: /* FCMP */
				चयन (fmt) अणु
				    हाल 0:
					retval = sgl_fcmp(&fpregs[r1],
						&fpregs[r2],extru(ir,fptpos,5),
						&local_status);
					update_status_cbit(status,local_status,
						fpu_type_flags, subop);
					वापस(retval);
				    हाल 1:
					retval = dbl_fcmp(&fpregs[r1],
						&fpregs[r2],extru(ir,fptpos,5),
						&local_status);
					update_status_cbit(status,local_status,
						fpu_type_flags, subop);
					वापस(retval);
				    हाल 2: /* illegal */
				    हाल 3: /* quad not implemented */
					वापस(MAJOR_0C_EXCP);
				पूर्ण
			हाल 1: /* FTEST */
				चयन (fmt) अणु
				    हाल 0:
					/*
					 * arg0 is not used
					 * second param is the t field used क्रम
					 * ftest,acc and ftest,rej
					 * third param is the subop (y-field)
					 */
					BUG();
					/* unsupported
					 * वापस(ftest(0L,extru(ir,fptpos,5),
					 *     &fpregs[0],subop));
					 */
				    हाल 1:
				    हाल 2:
				    हाल 3:
					वापस(MAJOR_0C_EXCP);
				पूर्ण
		    पूर्ण /* end of चयन subop */
		पूर्ण /* end of अन्यथा क्रम PA1.0 & PA1.1 */
	हाल 3: /* class 3 */
		r2 = extru(ir,fpr2pos,5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (r2 == 0)
			r2 = fpzeroreg;
		चयन (subop) अणु
			हाल 5:
			हाल 6:
			हाल 7:
				वापस(MAJOR_0C_EXCP);
			
			हाल 0: /* FADD */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_fadd(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 1:
					वापस(dbl_fadd(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 2: /* illegal */
				    हाल 3: /* quad not implemented */
					वापस(MAJOR_0C_EXCP);
				पूर्ण
			हाल 1: /* FSUB */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_fsub(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 1:
					वापस(dbl_fsub(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 2: /* illegal */
				    हाल 3: /* quad not implemented */
					वापस(MAJOR_0C_EXCP);
				पूर्ण
			हाल 2: /* FMPY */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_fmpy(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 1:
					वापस(dbl_fmpy(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 2: /* illegal */
				    हाल 3: /* quad not implemented */
					वापस(MAJOR_0C_EXCP);
				पूर्ण
			हाल 3: /* FDIV */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_fभाग(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 1:
					वापस(dbl_fभाग(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 2: /* illegal */
				    हाल 3: /* quad not implemented */
					वापस(MAJOR_0C_EXCP);
				पूर्ण
			हाल 4: /* FREM */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_frem(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 1:
					वापस(dbl_frem(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 2: /* illegal */
				    हाल 3: /* quad not implemented */
					वापस(MAJOR_0C_EXCP);
				पूर्ण
		पूर्ण /* end of class 3 चयन */
	पूर्ण /* end of चयन(class) */

	/* If we get here, something is really wrong! */
	वापस(MAJOR_0C_EXCP);
पूर्ण

अटल u_पूर्णांक
decode_0e(ir,class,subop,fpregs)
u_पूर्णांक ir,class,subop;
u_पूर्णांक fpregs[];
अणु
	u_पूर्णांक r1,r2,t;		/* opeअक्रम रेजिस्टर offsets */
	u_पूर्णांक fmt;		/* also sf क्रम class 1 conversions */
	u_पूर्णांक df;		/* dest क्रमmat क्रम class 1 conversions */
	u_पूर्णांक *status;
	u_पूर्णांक retval, local_status;
	u_पूर्णांक fpu_type_flags;

	status = &fpregs[0];
	local_status = fpregs[0];
	r1 = ((extru(ir,fpr1pos,5)<<1)|(extru(ir,fpxr1pos,1)));
	अगर (r1 == 0)
		r1 = fpzeroreg;
	t = ((extru(ir,fptpos,5)<<1)|(extru(ir,fpxtpos,1)));
	अगर (t == 0 && class != 2)
		वापस(MAJOR_0E_EXCP);
	अगर (class < 2)		/* class 0 or 1 has 2 bit fmt */
		fmt = extru(ir,fpfmtpos,2);
	अन्यथा 			/* class 2 and 3 have 1 bit fmt */
		fmt = extru(ir,fp0efmtpos,1);
	/*
	 * An undefined combination, द्विगुन precision accessing the
	 * right half of a FPR, can get us पूर्णांकo trouble.  
	 * Let's just क्रमce proper alignment on it.
	 */
	अगर (fmt == DBL) अणु
		r1 &= ~1;
		अगर (class != 1)
			t &= ~1;
	पूर्ण

	चयन (class) अणु
	    हाल 0:
		चयन (subop) अणु
			हाल 0: /* unimplemented */
			हाल 1:
				वापस(MAJOR_0E_EXCP);
			हाल 2: /* FCPY */
				चयन (fmt) अणु
				    हाल 2:
				    हाल 3:
					वापस(MAJOR_0E_EXCP);
				    हाल 1: /* द्विगुन */
					fpregs[t+1] = fpregs[r1+1];
				    हाल 0: /* single */
					fpregs[t] = fpregs[r1];
					वापस(NOEXCEPTION);
				पूर्ण
			हाल 3: /* FABS */
				चयन (fmt) अणु
				    हाल 2:
				    हाल 3:
					वापस(MAJOR_0E_EXCP);
				    हाल 1: /* द्विगुन */
					fpregs[t+1] = fpregs[r1+1];
				    हाल 0: /* single */
					fpregs[t] = fpregs[r1] & 0x7fffffff;
					वापस(NOEXCEPTION);
				पूर्ण
			हाल 6: /* FNEG */
				चयन (fmt) अणु
				    हाल 2:
				    हाल 3:
					वापस(MAJOR_0E_EXCP);
				    हाल 1: /* द्विगुन */
					fpregs[t+1] = fpregs[r1+1];
				    हाल 0: /* single */
					fpregs[t] = fpregs[r1] ^ 0x80000000;
					वापस(NOEXCEPTION);
				पूर्ण
			हाल 7: /* FNEGABS */
				चयन (fmt) अणु
				    हाल 2:
				    हाल 3:
					वापस(MAJOR_0E_EXCP);
				    हाल 1: /* द्विगुन */
					fpregs[t+1] = fpregs[r1+1];
				    हाल 0: /* single */
					fpregs[t] = fpregs[r1] | 0x80000000;
					वापस(NOEXCEPTION);
				पूर्ण
			हाल 4: /* FSQRT */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_fवर्ग_मूल(&fpregs[r1],0,
						&fpregs[t], status));
				    हाल 1:
					वापस(dbl_fवर्ग_मूल(&fpregs[r1],0,
						&fpregs[t], status));
				    हाल 2:
				    हाल 3:
					वापस(MAJOR_0E_EXCP);
				पूर्ण
			हाल 5: /* FRMD */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_frnd(&fpregs[r1],0,
						&fpregs[t], status));
				    हाल 1:
					वापस(dbl_frnd(&fpregs[r1],0,
						&fpregs[t], status));
				    हाल 2:
				    हाल 3:
					वापस(MAJOR_0E_EXCP);
				पूर्ण
		पूर्ण /* end of चयन (subop */
	
	हाल 1: /* class 1 */
		df = extru(ir,fpdfpos,2); /* get dest क्रमmat */
		/*
		 * Fix Crashme problem (writing to 31R in द्विगुन precision)
		 * here too.
		 */
		अगर (df == DBL) अणु
			t &= ~1;
		पूर्ण
		अगर ((df & 2) || (fmt & 2))
			वापस(MAJOR_0E_EXCP);
		
		fmt = (fmt << 1) | df;
		चयन (subop) अणु
			हाल 0: /* FCNVFF */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(MAJOR_0E_EXCP);
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvff(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvff(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(MAJOR_0E_EXCP);
				पूर्ण
			हाल 1: /* FCNVXF */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(sgl_to_sgl_fcnvxf(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvxf(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvxf(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(dbl_to_dbl_fcnvxf(&fpregs[r1],0,
						&fpregs[t],status));
				पूर्ण
			हाल 2: /* FCNVFX */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(sgl_to_sgl_fcnvfx(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvfx(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvfx(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(dbl_to_dbl_fcnvfx(&fpregs[r1],0,
						&fpregs[t],status));
				पूर्ण
			हाल 3: /* FCNVFXT */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(sgl_to_sgl_fcnvfxt(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvfxt(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvfxt(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(dbl_to_dbl_fcnvfxt(&fpregs[r1],0,
						&fpregs[t],status));
				पूर्ण
			हाल 5: /* FCNVUF (PA2.0 only) */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(sgl_to_sgl_fcnvuf(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvuf(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvuf(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(dbl_to_dbl_fcnvuf(&fpregs[r1],0,
						&fpregs[t],status));
				पूर्ण
			हाल 6: /* FCNVFU (PA2.0 only) */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(sgl_to_sgl_fcnvfu(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvfu(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvfu(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(dbl_to_dbl_fcnvfu(&fpregs[r1],0,
						&fpregs[t],status));
				पूर्ण
			हाल 7: /* FCNVFUT (PA2.0 only) */
				चयन(fmt) अणु
				    हाल 0: /* sgl/sgl */
					वापस(sgl_to_sgl_fcnvfut(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 1: /* sgl/dbl */
					वापस(sgl_to_dbl_fcnvfut(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 2: /* dbl/sgl */
					वापस(dbl_to_sgl_fcnvfut(&fpregs[r1],0,
						&fpregs[t],status));
				    हाल 3: /* dbl/dbl */
					वापस(dbl_to_dbl_fcnvfut(&fpregs[r1],0,
						&fpregs[t],status));
				पूर्ण
			हाल 4: /* undefined */
				वापस(MAJOR_0C_EXCP);
		पूर्ण /* end of चयन subop */
	हाल 2: /* class 2 */
		/*
		 * Be careful out there.
		 * Crashme can generate हालs where FR31R is specअगरied
		 * as the source or target of a द्विगुन precision operation.
		 * Since we just pass the address of the भग्नing-poपूर्णांक
		 * रेजिस्टर to the emulation routines, this can cause
		 * corruption of fpzeroreg.
		 */
		अगर (fmt == DBL)
			r2 = (extru(ir,fpr2pos,5)<<1);
		अन्यथा
			r2 = ((extru(ir,fpr2pos,5)<<1)|(extru(ir,fpxr2pos,1)));
		fpu_type_flags=fpregs[FPU_TYPE_FLAG_POS];
		अगर (r2 == 0)
			r2 = fpzeroreg;
		अगर  (fpu_type_flags & PA2_0_FPU_FLAG) अणु
			/* FTEST अगर nullअगरy bit set, otherwise FCMP */
			अगर (extru(ir, fpnulpos, 1)) अणु  /* FTEST */
				/* not legal */
				वापस(MAJOR_0E_EXCP);
			पूर्ण अन्यथा अणु  /* FCMP */
			चयन (fmt) अणु
				    /*
				     * fmt is only 1 bit दीर्घ
				     */
				    हाल 0:
					retval = sgl_fcmp(&fpregs[r1],
						&fpregs[r2],extru(ir,fptpos,5),
						&local_status);
					update_status_cbit(status,local_status,
						fpu_type_flags, subop);
					वापस(retval);
				    हाल 1:
					retval = dbl_fcmp(&fpregs[r1],
						&fpregs[r2],extru(ir,fptpos,5),
						&local_status);
					update_status_cbit(status,local_status,
						fpu_type_flags, subop);
					वापस(retval);
				पूर्ण
			पूर्ण
		पूर्ण  /* end of अगर क्रम PA2.0 */
		अन्यथा अणु  /* PA1.0 & PA1.1 */
		    चयन (subop) अणु
			हाल 1:
			हाल 2:
			हाल 3:
			हाल 4:
			हाल 5:
			हाल 6:
			हाल 7:
				वापस(MAJOR_0E_EXCP);
			हाल 0: /* FCMP */
				चयन (fmt) अणु
				    /*
				     * fmt is only 1 bit दीर्घ
				     */
				    हाल 0:
					retval = sgl_fcmp(&fpregs[r1],
						&fpregs[r2],extru(ir,fptpos,5),
						&local_status);
					update_status_cbit(status,local_status,
						fpu_type_flags, subop);
					वापस(retval);
				    हाल 1:
					retval = dbl_fcmp(&fpregs[r1],
						&fpregs[r2],extru(ir,fptpos,5),
						&local_status);
					update_status_cbit(status,local_status,
						fpu_type_flags, subop);
					वापस(retval);
				पूर्ण
		    पूर्ण /* end of चयन subop */
		पूर्ण /* end of अन्यथा क्रम PA1.0 & PA1.1 */
	हाल 3: /* class 3 */
		/*
		 * Be careful out there.
		 * Crashme can generate हालs where FR31R is specअगरied
		 * as the source or target of a द्विगुन precision operation.
		 * Since we just pass the address of the भग्नing-poपूर्णांक
		 * रेजिस्टर to the emulation routines, this can cause
		 * corruption of fpzeroreg.
		 */
		अगर (fmt == DBL)
			r2 = (extru(ir,fpr2pos,5)<<1);
		अन्यथा
			r2 = ((extru(ir,fpr2pos,5)<<1)|(extru(ir,fpxr2pos,1)));
		अगर (r2 == 0)
			r2 = fpzeroreg;
		चयन (subop) अणु
			हाल 5:
			हाल 6:
			हाल 7:
				वापस(MAJOR_0E_EXCP);
			
			/*
			 * Note that fmt is only 1 bit क्रम class 3 */
			हाल 0: /* FADD */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_fadd(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 1:
					वापस(dbl_fadd(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				पूर्ण
			हाल 1: /* FSUB */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_fsub(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 1:
					वापस(dbl_fsub(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				पूर्ण
			हाल 2: /* FMPY or XMPYU */
				/*
				 * check क्रम पूर्णांकeger multiply (x bit set)
				 */
				अगर (extru(ir,fpxpos,1)) अणु
				    /*
				     * emulate XMPYU
				     */
				    चयन (fmt) अणु
					हाल 0:
					    /*
					     * bad inकाष्ठाion अगर t specअगरies
					     * the right half of a रेजिस्टर
					     */
					    अगर (t & 1)
						वापस(MAJOR_0E_EXCP);
					    BUG();
					    /* unsupported
					     * impyu(&fpregs[r1],&fpregs[r2],
						 * &fpregs[t]);
					     */
					    वापस(NOEXCEPTION);
					हाल 1:
						वापस(MAJOR_0E_EXCP);
				    पूर्ण
				पूर्ण
				अन्यथा अणु /* FMPY */
				    चयन (fmt) अणु
				        हाल 0:
					    वापस(sgl_fmpy(&fpregs[r1],
					       &fpregs[r2],&fpregs[t],status));
				        हाल 1:
					    वापस(dbl_fmpy(&fpregs[r1],
					       &fpregs[r2],&fpregs[t],status));
				    पूर्ण
				पूर्ण
			हाल 3: /* FDIV */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_fभाग(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 1:
					वापस(dbl_fभाग(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				पूर्ण
			हाल 4: /* FREM */
				चयन (fmt) अणु
				    हाल 0:
					वापस(sgl_frem(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				    हाल 1:
					वापस(dbl_frem(&fpregs[r1],&fpregs[r2],
						&fpregs[t],status));
				पूर्ण
		पूर्ण /* end of class 3 चयन */
	पूर्ण /* end of चयन(class) */

	/* If we get here, something is really wrong! */
	वापस(MAJOR_0E_EXCP);
पूर्ण


/*
 * routine to decode the 06 (FMPYADD and FMPYCFXT) inकाष्ठाion
 */
अटल u_पूर्णांक
decode_06(ir,fpregs)
u_पूर्णांक ir;
u_पूर्णांक fpregs[];
अणु
	u_पूर्णांक rm1, rm2, पंचांग, ra, ta; /* opeअक्रमs */
	u_पूर्णांक fmt;
	u_पूर्णांक error = 0;
	u_पूर्णांक status;
	u_पूर्णांक fpu_type_flags;
	जोड़ अणु
		द्विगुन dbl;
		भग्न flt;
		काष्ठा अणु u_पूर्णांक i1; u_पूर्णांक i2; पूर्ण पूर्णांकs;
	पूर्ण mपंचांगp, aपंचांगp;


	status = fpregs[0];		/* use a local copy of status reg */
	fpu_type_flags=fpregs[FPU_TYPE_FLAG_POS];  /* get fpu type flags */
	fmt = extru(ir, fpmultअगरmt, 1);	/* get sgl/dbl flag */
	अगर (fmt == 0) अणु /* DBL */
		rm1 = extru(ir, fprm1pos, 5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (rm1 == 0)
			rm1 = fpzeroreg;
		rm2 = extru(ir, fprm2pos, 5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (rm2 == 0)
			rm2 = fpzeroreg;
		पंचांग = extru(ir, fpपंचांगpos, 5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (पंचांग == 0)
			वापस(MAJOR_06_EXCP);
		ra = extru(ir, fprapos, 5) * माप(द्विगुन)/माप(u_पूर्णांक);
		ta = extru(ir, fptapos, 5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (ta == 0)
			वापस(MAJOR_06_EXCP);

		अगर  (fpu_type_flags & TIMEX_ROLEX_FPU_MASK)  अणु

			अगर (ra == 0) अणु
			 	/* special हाल FMPYCFXT, see sgl हाल below */
				अगर (dbl_fmpy(&fpregs[rm1],&fpregs[rm2],
					&mपंचांगp.पूर्णांकs.i1,&status))
					error = 1;
				अगर (dbl_to_sgl_fcnvfxt(&fpregs[ta],
					&aपंचांगp.पूर्णांकs.i1,&aपंचांगp.पूर्णांकs.i1,&status))
					error = 1;
				पूर्ण
			अन्यथा अणु

			अगर (dbl_fmpy(&fpregs[rm1],&fpregs[rm2],&mपंचांगp.पूर्णांकs.i1,
					&status))
				error = 1;
			अगर (dbl_fadd(&fpregs[ta], &fpregs[ra], &aपंचांगp.पूर्णांकs.i1,
					&status))
				error = 1;
				पूर्ण
			पूर्ण

		अन्यथा

			अणु
			अगर (ra == 0)
				ra = fpzeroreg;

			अगर (dbl_fmpy(&fpregs[rm1],&fpregs[rm2],&mपंचांगp.पूर्णांकs.i1,
					&status))
				error = 1;
			अगर (dbl_fadd(&fpregs[ta], &fpregs[ra], &aपंचांगp.पूर्णांकs.i1,
					&status))
				error = 1;

			पूर्ण

		अगर (error)
			वापस(MAJOR_06_EXCP);
		अन्यथा अणु
			/* copy results */
			fpregs[पंचांग] = mपंचांगp.पूर्णांकs.i1;
			fpregs[पंचांग+1] = mपंचांगp.पूर्णांकs.i2;
			fpregs[ta] = aपंचांगp.पूर्णांकs.i1;
			fpregs[ta+1] = aपंचांगp.पूर्णांकs.i2;
			fpregs[0] = status;
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण
	अन्यथा अणु /* SGL */
		/*
		 * calculate offsets क्रम single precision numbers
		 * See table 6-14 in PA-89 architecture क्रम mapping
		 */
		rm1 = (extru(ir,fprm1pos,4) | 0x10 ) << 1;	/* get offset */
		rm1 |= extru(ir,fprm1pos-4,1);	/* add right word offset */

		rm2 = (extru(ir,fprm2pos,4) | 0x10 ) << 1;	/* get offset */
		rm2 |= extru(ir,fprm2pos-4,1);	/* add right word offset */

		पंचांग = (extru(ir,fpपंचांगpos,4) | 0x10 ) << 1;	/* get offset */
		पंचांग |= extru(ir,fpपंचांगpos-4,1);	/* add right word offset */

		ra = (extru(ir,fprapos,4) | 0x10 ) << 1;	/* get offset */
		ra |= extru(ir,fprapos-4,1);	/* add right word offset */

		ta = (extru(ir,fptapos,4) | 0x10 ) << 1;	/* get offset */
		ta |= extru(ir,fptapos-4,1);	/* add right word offset */
		
		अगर (ra == 0x20 &&(fpu_type_flags & TIMEX_ROLEX_FPU_MASK)) अणु
			/* special हाल FMPYCFXT (really 0)
			  * This inकाष्ठाion is only present on the Timex and
			  * Rolex fpu's in so अगर it is the special हाल and
			  * one of these fpu's we run the FMPYCFXT inकाष्ठाion
			  */
			अगर (sgl_fmpy(&fpregs[rm1],&fpregs[rm2],&mपंचांगp.पूर्णांकs.i1,
					&status))
				error = 1;
			अगर (sgl_to_sgl_fcnvfxt(&fpregs[ta],&aपंचांगp.पूर्णांकs.i1,
				&aपंचांगp.पूर्णांकs.i1,&status))
				error = 1;
		पूर्ण
		अन्यथा अणु
			अगर (sgl_fmpy(&fpregs[rm1],&fpregs[rm2],&mपंचांगp.पूर्णांकs.i1,
					&status))
				error = 1;
			अगर (sgl_fadd(&fpregs[ta], &fpregs[ra], &aपंचांगp.पूर्णांकs.i1,
					&status))
				error = 1;
		पूर्ण
		अगर (error)
			वापस(MAJOR_06_EXCP);
		अन्यथा अणु
			/* copy results */
			fpregs[पंचांग] = mपंचांगp.पूर्णांकs.i1;
			fpregs[ta] = aपंचांगp.पूर्णांकs.i1;
			fpregs[0] = status;
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * routine to decode the 26 (FMPYSUB) inकाष्ठाion
 */
अटल u_पूर्णांक
decode_26(ir,fpregs)
u_पूर्णांक ir;
u_पूर्णांक fpregs[];
अणु
	u_पूर्णांक rm1, rm2, पंचांग, ra, ta; /* opeअक्रमs */
	u_पूर्णांक fmt;
	u_पूर्णांक error = 0;
	u_पूर्णांक status;
	जोड़ अणु
		द्विगुन dbl;
		भग्न flt;
		काष्ठा अणु u_पूर्णांक i1; u_पूर्णांक i2; पूर्ण पूर्णांकs;
	पूर्ण mपंचांगp, aपंचांगp;


	status = fpregs[0];
	fmt = extru(ir, fpmultअगरmt, 1);	/* get sgl/dbl flag */
	अगर (fmt == 0) अणु /* DBL */
		rm1 = extru(ir, fprm1pos, 5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (rm1 == 0)
			rm1 = fpzeroreg;
		rm2 = extru(ir, fprm2pos, 5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (rm2 == 0)
			rm2 = fpzeroreg;
		पंचांग = extru(ir, fpपंचांगpos, 5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (पंचांग == 0)
			वापस(MAJOR_26_EXCP);
		ra = extru(ir, fprapos, 5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (ra == 0)
			वापस(MAJOR_26_EXCP);
		ta = extru(ir, fptapos, 5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (ta == 0)
			वापस(MAJOR_26_EXCP);
		
		अगर (dbl_fmpy(&fpregs[rm1],&fpregs[rm2],&mपंचांगp.पूर्णांकs.i1,&status))
			error = 1;
		अगर (dbl_fsub(&fpregs[ta], &fpregs[ra], &aपंचांगp.पूर्णांकs.i1,&status))
			error = 1;
		अगर (error)
			वापस(MAJOR_26_EXCP);
		अन्यथा अणु
			/* copy results */
			fpregs[पंचांग] = mपंचांगp.पूर्णांकs.i1;
			fpregs[पंचांग+1] = mपंचांगp.पूर्णांकs.i2;
			fpregs[ta] = aपंचांगp.पूर्णांकs.i1;
			fpregs[ta+1] = aपंचांगp.पूर्णांकs.i2;
			fpregs[0] = status;
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण
	अन्यथा अणु /* SGL */
		/*
		 * calculate offsets क्रम single precision numbers
		 * See table 6-14 in PA-89 architecture क्रम mapping
		 */
		rm1 = (extru(ir,fprm1pos,4) | 0x10 ) << 1;	/* get offset */
		rm1 |= extru(ir,fprm1pos-4,1);	/* add right word offset */

		rm2 = (extru(ir,fprm2pos,4) | 0x10 ) << 1;	/* get offset */
		rm2 |= extru(ir,fprm2pos-4,1);	/* add right word offset */

		पंचांग = (extru(ir,fpपंचांगpos,4) | 0x10 ) << 1;	/* get offset */
		पंचांग |= extru(ir,fpपंचांगpos-4,1);	/* add right word offset */

		ra = (extru(ir,fprapos,4) | 0x10 ) << 1;	/* get offset */
		ra |= extru(ir,fprapos-4,1);	/* add right word offset */

		ta = (extru(ir,fptapos,4) | 0x10 ) << 1;	/* get offset */
		ta |= extru(ir,fptapos-4,1);	/* add right word offset */
		
		अगर (sgl_fmpy(&fpregs[rm1],&fpregs[rm2],&mपंचांगp.पूर्णांकs.i1,&status))
			error = 1;
		अगर (sgl_fsub(&fpregs[ta], &fpregs[ra], &aपंचांगp.पूर्णांकs.i1,&status))
			error = 1;
		अगर (error)
			वापस(MAJOR_26_EXCP);
		अन्यथा अणु
			/* copy results */
			fpregs[पंचांग] = mपंचांगp.पूर्णांकs.i1;
			fpregs[ta] = aपंचांगp.पूर्णांकs.i1;
			fpregs[0] = status;
			वापस(NOEXCEPTION);
		पूर्ण
	पूर्ण

पूर्ण

/*
 * routine to decode the 2E (FMPYFADD,FMPYNFADD) inकाष्ठाions
 */
अटल u_पूर्णांक
decode_2e(ir,fpregs)
u_पूर्णांक ir;
u_पूर्णांक fpregs[];
अणु
	u_पूर्णांक rm1, rm2, ra, t; /* opeअक्रमs */
	u_पूर्णांक fmt;

	fmt = extru(ir,fpfmtpos,1);	/* get fmt completer */
	अगर (fmt == DBL) अणु /* DBL */
		rm1 = extru(ir,fprm1pos,5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (rm1 == 0)
			rm1 = fpzeroreg;
		rm2 = extru(ir,fprm2pos,5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (rm2 == 0)
			rm2 = fpzeroreg;
		ra = ((extru(ir,fpraupos,3)<<2)|(extru(ir,fpralpos,3)>>1)) *
		     माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (ra == 0)
			ra = fpzeroreg;
		t = extru(ir,fptpos,5) * माप(द्विगुन)/माप(u_पूर्णांक);
		अगर (t == 0)
			वापस(MAJOR_2E_EXCP);

		अगर (extru(ir,fpfusedsubop,1)) अणु /* fmpyfadd or fmpynfadd? */
			वापस(dbl_fmpynfadd(&fpregs[rm1], &fpregs[rm2],
					&fpregs[ra], &fpregs[0], &fpregs[t]));
		पूर्ण अन्यथा अणु
			वापस(dbl_fmpyfadd(&fpregs[rm1], &fpregs[rm2],
					&fpregs[ra], &fpregs[0], &fpregs[t]));
		पूर्ण
	पूर्ण /* end DBL */
	अन्यथा अणु /* SGL */
		rm1 = (extru(ir,fprm1pos,5)<<1)|(extru(ir,fpxrm1pos,1));
		अगर (rm1 == 0)
			rm1 = fpzeroreg;
		rm2 = (extru(ir,fprm2pos,5)<<1)|(extru(ir,fpxrm2pos,1));
		अगर (rm2 == 0)
			rm2 = fpzeroreg;
		ra = (extru(ir,fpraupos,3)<<3)|extru(ir,fpralpos,3);
		अगर (ra == 0)
			ra = fpzeroreg;
		t = ((extru(ir,fptpos,5)<<1)|(extru(ir,fpxtpos,1)));
		अगर (t == 0)
			वापस(MAJOR_2E_EXCP);

		अगर (extru(ir,fpfusedsubop,1)) अणु /* fmpyfadd or fmpynfadd? */
			वापस(sgl_fmpynfadd(&fpregs[rm1], &fpregs[rm2],
					&fpregs[ra], &fpregs[0], &fpregs[t]));
		पूर्ण अन्यथा अणु
			वापस(sgl_fmpyfadd(&fpregs[rm1], &fpregs[rm2],
					&fpregs[ra], &fpregs[0], &fpregs[t]));
		पूर्ण
	पूर्ण /* end SGL */
पूर्ण

/*
 * update_status_cbit
 *
 *	This routine वापसs the correct FP status रेजिस्टर value in
 *	*status, based on the C-bit & V-bit वापसed by the FCMP
 *	emulation routine in new_status.  The architecture type
 *	(PA83, PA89 or PA2.0) is available in fpu_type.  The y_field
 *	and the architecture type are used to determine what flavor
 *	of FCMP is being emulated.
 */
अटल व्योम
update_status_cbit(status, new_status, fpu_type, y_field)
u_पूर्णांक *status, new_status;
u_पूर्णांक fpu_type;
u_पूर्णांक y_field;
अणु
	/*
	 * For PA89 FPU's which implement the Compare Queue and
	 * क्रम PA2.0 FPU's, update the Compare Queue अगर the y-field = 0,
	 * otherwise update the specअगरied bit in the Compare Array.
	 * Note that the y-field will always be 0 क्रम non-PA2.0 FPU's.
	 */
	अगर ((fpu_type & TIMEX_EXTEN_FLAG) || 
	    (fpu_type & ROLEX_EXTEN_FLAG) ||
	    (fpu_type & PA2_0_FPU_FLAG)) अणु
		अगर (y_field == 0) अणु
			*status = ((*status & 0x04000000) >> 5) | /* old Cbit */
				  ((*status & 0x003ff000) >> 1) | /* old CQ   */
				  (new_status & 0xffc007ff); /* all other bits*/
		पूर्ण अन्यथा अणु
			*status = (*status & 0x04000000) |     /* old Cbit */
				  ((new_status & 0x04000000) >> (y_field+4)) |
				  (new_status & ~0x04000000 &  /* other bits */
				   ~(0x04000000 >> (y_field+4)));
		पूर्ण
	पूर्ण
	/* अगर PA83, just update the C-bit */
	अन्यथा अणु
		*status = new_status;
	पूर्ण
पूर्ण
