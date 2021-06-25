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
 *	@(#)	pa/fp/decode_exc.c		$ Revision: $
 *
 *  Purpose:
 *	<<please update with a synopsis of the functionality provided by this file>>
 *
 *  External Interfaces:
 *	<<the following list was स्वतःgenerated, please review>>
 *	decode_fpu(Fpu_रेजिस्टर, trap_counts)
 *
 *  Internal Interfaces:
 *	<<please update>>
 *
 *  Theory:
 *	<<please update with a overview of the operation of this file>>
 *
 * END_DESC
*/

#समावेश <linux/kernel.h>
#समावेश "float.h"
#समावेश "sgl_float.h"
#समावेश "dbl_float.h"
#समावेश "cnv_float.h"
/* #समावेश "types.h" */
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/siginfo.h>
/* #समावेश <machine/sys/mdep_निजी.h> */

#अघोषित Fpustatus_रेजिस्टर
#घोषणा Fpustatus_रेजिस्टर Fpu_रेजिस्टर[0]

/* General definitions */
#घोषणा DOESTRAP 1
#घोषणा NOTRAP 0
#घोषणा SIGNALCODE(संकेत, code) ((संकेत) << 24 | (code))
#घोषणा copropbit	1<<31-2	/* bit position 2 */
#घोषणा opclass		9	/* bits 21 & 22 */
#घोषणा fmt		11	/* bits 19 & 20 */
#घोषणा df		13	/* bits 17 & 18 */
#घोषणा twobits		3	/* mask low-order 2 bits */
#घोषणा fivebits	31	/* mask low-order 5 bits */
#घोषणा MAX_EXCP_REG	7	/* number of excpeption रेजिस्टरs to check */

/* Exception रेजिस्टर definitions */
#घोषणा Excp_type(index) Exceptiontype(Fpu_रेजिस्टर[index])
#घोषणा Excp_instr(index) Inकाष्ठाionfield(Fpu_रेजिस्टर[index])
#घोषणा Clear_excp_रेजिस्टर(index) Allexception(Fpu_रेजिस्टर[index]) = 0
#घोषणा Excp_क्रमmat() \
    (current_ir >> ((current_ir>>opclass & twobits)==1 ? df : fmt) & twobits)

/* Miscellaneous definitions */
#घोषणा Fpu_sgl(index) Fpu_रेजिस्टर[index*2]

#घोषणा Fpu_dblp1(index) Fpu_रेजिस्टर[index*2]
#घोषणा Fpu_dblp2(index) Fpu_रेजिस्टर[(index*2)+1]

#घोषणा Fpu_quadp1(index) Fpu_रेजिस्टर[index*2]
#घोषणा Fpu_quadp2(index) Fpu_रेजिस्टर[(index*2)+1]
#घोषणा Fpu_quadp3(index) Fpu_रेजिस्टर[(index*2)+2]
#घोषणा Fpu_quadp4(index) Fpu_रेजिस्टर[(index*2)+3]

/* Single precision भग्नing-poपूर्णांक definitions */
#अगर_अघोषित Sgl_decrement
# define Sgl_decrement(sgl_value) Sall(sgl_value)--
#पूर्ण_अगर

/* Double precision भग्नing-poपूर्णांक definitions */
#अगर_अघोषित Dbl_decrement
# define Dbl_decrement(dbl_valuep1,dbl_valuep2) \
    अगर ((Dallp2(dbl_valuep2)--) == 0) Dallp1(dbl_valuep1)-- 
#पूर्ण_अगर


#घोषणा update_trap_counts(Fpu_रेजिस्टर, aflags, bflags, trap_counts) अणु	\
	aflags=(Fpu_रेजिस्टर[0])>>27;	/* assumes zero fill. 32 bit */	\
	Fpu_रेजिस्टर[0] |= bflags;					\
पूर्ण

u_पूर्णांक
decode_fpu(अचिन्हित पूर्णांक Fpu_रेजिस्टर[], अचिन्हित पूर्णांक trap_counts[])
अणु
    अचिन्हित पूर्णांक current_ir, excp;
    पूर्णांक target, exception_index = 1;
    boolean inexact;
    अचिन्हित पूर्णांक aflags;
    अचिन्हित पूर्णांक bflags;
    अचिन्हित पूर्णांक excptype;


    /* Keep stats on how many भग्नing poपूर्णांक exceptions (based on type)
     * that happen.  Want to keep this overhead low, but still provide
     * some inक्रमmation to the customer.  All निकासs from this routine
     * need to restore Fpu_रेजिस्टर[0]
    */

    bflags=(Fpu_रेजिस्टर[0] & 0xf8000000);
    Fpu_रेजिस्टर[0] &= 0x07ffffff;

    /* exception_index is used to index the exception रेजिस्टर queue.  It
     *   always poपूर्णांकs at the last रेजिस्टर that contains a valid exception.  A
     *   zero value implies no exceptions (also the initialized value).  Setting
     *   the T-bit resets the exception_index to zero.
     */

    /*
     * Check क्रम reserved-op exception.  A reserved-op exception करोes not 
     * set any exception रेजिस्टरs nor करोes it set the T-bit.  If the T-bit
     * is not set then a reserved-op exception occurred.
     *
     * At some poपूर्णांक, we may want to report reserved op exceptions as
     * illegal inकाष्ठाions.
     */
    
    अगर (!Is_tbit_set()) अणु
	update_trap_counts(Fpu_रेजिस्टर, aflags, bflags, trap_counts);
	वापस SIGNALCODE(संक_अवैध, ILL_COPROC);
    पूर्ण

    /* 
     * Is a coprocessor op. 
     *
     * Now we need to determine what type of exception occurred.
     */
    क्रम (exception_index=1; exception_index<=MAX_EXCP_REG; exception_index++) अणु
	current_ir = Excp_instr(exception_index);
	  /*
	   * On PA89: there are 5 dअगरferent unimplemented exception
	   * codes: 0x1, 0x9, 0xb, 0x3, and 0x23.  PA-RISC 2.0 adds
	   * another, 0x2b.  Only these have the low order bit set.
	   */
	excptype = Excp_type(exception_index);
	अगर (excptype & UNIMPLEMENTEDEXCEPTION) अणु
		/*
		 * Clear T-bit and exception रेजिस्टर so that
		 * we can tell अगर a trap really occurs जबतक 
		 * emulating the inकाष्ठाion.
		 */
		Clear_tbit();
		Clear_excp_रेजिस्टर(exception_index);
		/*
		 * Now emulate this inकाष्ठाion.  If a trap occurs,
		 * fpudispatch will वापस a non-zero number 
		 */
		excp = fpudispatch(current_ir,excptype,0,Fpu_रेजिस्टर);
		/* accumulate the status flags, करोn't lose them as in hpux */
		अगर (excp) अणु
			/*
			 * We now need to make sure that the T-bit and the
			 * exception रेजिस्टर contain the correct values
			 * beक्रमe continuing.
			 */
			/*
			 * Set t-bit since it might still be needed क्रम a
			 * subsequent real trap (I करोn't understand fully -PB)
			 */
			Set_tbit();
			/* some of the following code uses
			 * Excp_type(exception_index) so fix that up */
			Set_exceptiontype_and_instr_field(excp,current_ir,
			 Fpu_रेजिस्टर[exception_index]);
			अगर (excp == UNIMPLEMENTEDEXCEPTION) अणु
				/*
			 	 * it is really unimplemented, so restore the
			 	 * TIMEX extended unimplemented exception code
			 	 */
				excp = excptype;
				update_trap_counts(Fpu_रेजिस्टर, aflags, bflags, 
					   trap_counts);
				वापस SIGNALCODE(संक_अवैध, ILL_COPROC);
			पूर्ण
			/* some of the following code uses excptype, so
			 * fix that up too */
			excptype = excp;
		पूर्ण
		/* handle exceptions other than the real UNIMPLIMENTED the
		 * same way as अगर the hardware had caused them */
		अगर (excp == NOEXCEPTION)
			/* For now use 'break', should technically be 'continue' */
			अवरोध;
	पूर्ण

	  /*
	   * In PA89, the underflow exception has been extended to encode
	   * additional inक्रमmation.  The exception looks like pp01x0,
	   * where x is 1 अगर inexact and pp represent the inexact bit (I)
	   * and the round away bit (RA)
	   */
	अगर (excptype & UNDERFLOWEXCEPTION) अणु
		/* check क्रम underflow trap enabled */
		अगर (Is_underflowtrap_enabled()) अणु
			update_trap_counts(Fpu_रेजिस्टर, aflags, bflags, 
					   trap_counts);
			वापस SIGNALCODE(संक_भ_त्रुटि, FPE_FLTUND);
		पूर्ण अन्यथा अणु
		    /*
		     * Isn't a real trap; we need to 
		     * वापस the शेष value.
		     */
		    target = current_ir & fivebits;
#अगर_अघोषित lपूर्णांक
		    अगर (Ibit(Fpu_रेजिस्टर[exception_index])) inexact = TRUE;
		    अन्यथा inexact = FALSE;
#पूर्ण_अगर
		    चयन (Excp_क्रमmat()) अणु
		      हाल SGL:
		        /*
		         * If ra (round-away) is set, will 
		         * want to unकरो the rounding करोne
		         * by the hardware.
		         */
		        अगर (Rabit(Fpu_रेजिस्टर[exception_index])) 
				Sgl_decrement(Fpu_sgl(target));

			/* now denormalize */
			sgl_denormalize(&Fpu_sgl(target),&inexact,Rounding_mode());
		    	अवरोध;
		      हाल DBL:
		    	/*
		    	 * If ra (round-away) is set, will 
		    	 * want to unकरो the rounding करोne
		    	 * by the hardware.
		    	 */
		    	अगर (Rabit(Fpu_रेजिस्टर[exception_index])) 
				Dbl_decrement(Fpu_dblp1(target),Fpu_dblp2(target));

			/* now denormalize */
			dbl_denormalize(&Fpu_dblp1(target),&Fpu_dblp2(target),
			  &inexact,Rounding_mode());
		    	अवरोध;
		    पूर्ण
		    अगर (inexact) Set_underflowflag();
		    /* 
		     * Underflow can generate an inexact
		     * exception.  If inexact trap is enabled,
		     * want to करो an inexact trap, otherwise 
		     * set inexact flag.
		     */
		    अगर (inexact && Is_inexacttrap_enabled()) अणु
		    	/*
		    	 * Set exception field of exception रेजिस्टर
		    	 * to inexact, parm field to zero.
			 * Underflow bit should be cleared.
		    	 */
		    	Set_exceptiontype(Fpu_रेजिस्टर[exception_index],
			 INEXACTEXCEPTION);
			Set_parmfield(Fpu_रेजिस्टर[exception_index],0);
			update_trap_counts(Fpu_रेजिस्टर, aflags, bflags, 
					   trap_counts);
			वापस SIGNALCODE(संक_भ_त्रुटि, FPE_FLTRES);
		    पूर्ण
		    अन्यथा अणु
		    	/*
		    	 * Exception रेजिस्टर needs to be cleared.  
			 * Inexact flag needs to be set अगर inexact.
		    	 */
		    	Clear_excp_रेजिस्टर(exception_index);
		    	अगर (inexact) Set_inexactflag();
		    पूर्ण
		पूर्ण
		जारी;
	पूर्ण
	चयन(Excp_type(exception_index)) अणु
	  हाल OVERFLOWEXCEPTION:
	  हाल OVERFLOWEXCEPTION | INEXACTEXCEPTION:
		/* check क्रम overflow trap enabled */
			update_trap_counts(Fpu_रेजिस्टर, aflags, bflags, 
					   trap_counts);
		अगर (Is_overflowtrap_enabled()) अणु
			update_trap_counts(Fpu_रेजिस्टर, aflags, bflags, 
					   trap_counts);
			वापस SIGNALCODE(संक_भ_त्रुटि, FPE_FLTOVF);
		पूर्ण अन्यथा अणु
			/*
			 * Isn't a real trap; we need to 
			 * वापस the शेष value.
			 */
			target = current_ir & fivebits;
			चयन (Excp_क्रमmat()) अणु
			  हाल SGL: 
				Sgl_setoverflow(Fpu_sgl(target));
				अवरोध;
			  हाल DBL:
				Dbl_setoverflow(Fpu_dblp1(target),Fpu_dblp2(target));
				अवरोध;
			पूर्ण
			Set_overflowflag();
			/* 
			 * Overflow always generates an inexact
			 * exception.  If inexact trap is enabled,
			 * want to करो an inexact trap, otherwise 
			 * set inexact flag.
			 */
			अगर (Is_inexacttrap_enabled()) अणु
				/*
				 * Set exception field of exception
				 * रेजिस्टर to inexact.  Overflow
				 * bit should be cleared.
				 */
				Set_exceptiontype(Fpu_रेजिस्टर[exception_index],
				 INEXACTEXCEPTION);
				update_trap_counts(Fpu_रेजिस्टर, aflags, bflags,
					   trap_counts);
				वापस SIGNALCODE(संक_भ_त्रुटि, FPE_FLTRES);
			पूर्ण
			अन्यथा अणु
				/*
				 * Exception रेजिस्टर needs to be cleared.  
				 * Inexact flag needs to be set.
				 */
				Clear_excp_रेजिस्टर(exception_index);
				Set_inexactflag();
			पूर्ण
		पूर्ण
		अवरोध;
	  हाल INVALIDEXCEPTION:
	  हाल OPC_2E_INVALIDEXCEPTION:
		update_trap_counts(Fpu_रेजिस्टर, aflags, bflags, trap_counts);
		वापस SIGNALCODE(संक_भ_त्रुटि, FPE_FLTINV);
	  हाल DIVISIONBYZEROEXCEPTION:
		update_trap_counts(Fpu_रेजिस्टर, aflags, bflags, trap_counts);
		Clear_excp_रेजिस्टर(exception_index);
	  	वापस SIGNALCODE(संक_भ_त्रुटि, FPE_FLTDIV);
	  हाल INEXACTEXCEPTION:
		update_trap_counts(Fpu_रेजिस्टर, aflags, bflags, trap_counts);
		वापस SIGNALCODE(संक_भ_त्रुटि, FPE_FLTRES);
	  शेष:
		update_trap_counts(Fpu_रेजिस्टर, aflags, bflags, trap_counts);
		prपूर्णांकk("%s(%d) Unknown FPU exception 0x%x\n", __खाता__,
			__LINE__, Excp_type(exception_index));
		वापस SIGNALCODE(संक_अवैध, ILL_COPROC);
	  हाल NOEXCEPTION:	/* no exception */
		/*
		 * Clear exception रेजिस्टर in हाल 
		 * other fields are non-zero.
		 */
		Clear_excp_रेजिस्टर(exception_index);
		अवरोध;
	पूर्ण
    पूर्ण
    /*
     * No real exceptions occurred.
     */
    Clear_tbit();
    update_trap_counts(Fpu_रेजिस्टर, aflags, bflags, trap_counts);
    वापस(NOTRAP);
पूर्ण
