<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  fpu_entry.c                                                              |
 |                                                                           |
 | The entry functions क्रम wm-FPU-emu                                        |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1996,1997                                    |
 |                  W. Metzenthen, 22 Parker St, Ormond, Vic 3163, Australia |
 |                  E-mail   billm@suburbia.net                              |
 |                                                                           |
 | See the files "README" and "COPYING" क्रम further copyright and warranty   |
 | inक्रमmation.                                                              |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | Note:                                                                     |
 |    The file contains code which accesses user memory.                     |
 |    Emulator अटल data may change when user memory is accessed, due to   |
 |    other processes using the emulator जबतक swapping is in progress.      |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | math_emulate(), restore_i387_soft() and save_i387_soft() are the only     |
 | entry poपूर्णांकs क्रम wm-FPU-emu.                                              |
 +---------------------------------------------------------------------------*/

#समावेश <linux/संकेत.स>
#समावेश <linux/regset.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/user.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>

#समावेश "fpu_system.h"
#समावेश "fpu_emu.h"
#समावेश "exception.h"
#समावेश "control_w.h"
#समावेश "status_w.h"

#घोषणा __BAD__ FPU_illegal	/* Illegal on an 80486, causes संक_अवैध */

/* fcmovCC and f(u)comi(p) are enabled अगर CPUID(1).EDX(15) "cmov" is set */

/* WARNING: "u" entries are not करोcumented by Intel in their 80486 manual
   and may not work on FPU clones or later Intel FPUs.
   Changes to support them provided by Linus Torvalds. */

अटल FUNC स्थिर st_instr_table[64] = अणु
/* Opcode:	d8		d9		da		db */
/*		dc		dd		de		df */
/* c0..7 */	fadd__,		fld_i_,		fcmovb,		fcmovnb,
/* c0..7 */	fadd_i,		fमुक्त_,		faddp_,		fमुक्तp,/*u*/
/* c8..f */	fmul__,		fxch_i,		fcmove,		fcmovne,
/* c8..f */	fmul_i,		fxch_i,/*u*/	fmulp_,		fxch_i,/*u*/
/* d0..7 */	fcom_st,	fp_nop,		fcmovbe,	fcmovnbe,
/* d0..7 */	fcom_st,/*u*/	fst_i_,		fcompst,/*u*/	fstp_i,/*u*/
/* d8..f */	fcompst,	fstp_i,/*u*/	fcmovu,		fcmovnu,
/* d8..f */	fcompst,/*u*/	fstp_i,		fcompp,		fstp_i,/*u*/
/* e0..7 */	fsub__,		FPU_etc,	__BAD__,	finit_,
/* e0..7 */	fsubri,		fucom_,		fsubrp,		fstsw_,
/* e8..f */	fsubr_,		fस्थिर,		fucompp,	fucomi_,
/* e8..f */	fsub_i,		fucomp,		fsubp_,		fucomip,
/* f0..7 */	fभाग__,		FPU_triga,	__BAD__,	fcomi_,
/* f0..7 */	fभागri,		__BAD__,	fभागrp,		fcomip,
/* f8..f */	fभागr_,		FPU_trigb,	__BAD__,	__BAD__,
/* f8..f */	fभाग_i,		__BAD__,	fभागp_,		__BAD__,
पूर्ण;

#घोषणा _NONE_ 0		/* Take no special action */
#घोषणा _REG0_ 1		/* Need to check क्रम not empty st(0) */
#घोषणा _REGI_ 2		/* Need to check क्रम not empty st(0) and st(rm) */
#घोषणा _REGi_ 0		/* Uses st(rm) */
#घोषणा _PUSH_ 3		/* Need to check क्रम space to push onto stack */
#घोषणा _null_ 4		/* Function illegal or not implemented */
#घोषणा _REGIi 5		/* Uses st(0) and st(rm), result to st(rm) */
#घोषणा _REGIp 6		/* Uses st(0) and st(rm), result to st(rm) then pop */
#घोषणा _REGIc 0		/* Compare st(0) and st(rm) */
#घोषणा _REGIn 0		/* Uses st(0) and st(rm), but handle checks later */

अटल u_अक्षर स्थिर type_table[64] = अणु
/* Opcode:	d8	d9	da	db	dc	dd	de	df */
/* c0..7 */	_REGI_, _NONE_, _REGIn, _REGIn, _REGIi, _REGi_, _REGIp, _REGi_,
/* c8..f */	_REGI_, _REGIn, _REGIn, _REGIn, _REGIi, _REGI_, _REGIp, _REGI_,
/* d0..7 */	_REGIc, _NONE_, _REGIn, _REGIn, _REGIc, _REG0_, _REGIc, _REG0_,
/* d8..f */	_REGIc, _REG0_, _REGIn, _REGIn, _REGIc, _REG0_, _REGIc, _REG0_,
/* e0..7 */	_REGI_, _NONE_, _null_, _NONE_, _REGIi, _REGIc, _REGIp, _NONE_,
/* e8..f */	_REGI_, _NONE_, _REGIc, _REGIc, _REGIi, _REGIc, _REGIp, _REGIc,
/* f0..7 */	_REGI_, _NONE_, _null_, _REGIc, _REGIi, _null_, _REGIp, _REGIc,
/* f8..f */	_REGI_, _NONE_, _null_, _null_, _REGIi, _null_, _REGIp, _null_,
पूर्ण;

#अगर_घोषित RE_ENTRANT_CHECKING
u_अक्षर emulating = 0;
#पूर्ण_अगर /* RE_ENTRANT_CHECKING */

अटल पूर्णांक valid_prefix(u_अक्षर *Byte, u_अक्षर __user ** fpu_eip,
			overrides * override);

व्योम math_emulate(काष्ठा math_emu_info *info)
अणु
	u_अक्षर FPU_modrm, byte1;
	अचिन्हित लघु code;
	fpu_addr_modes addr_modes;
	पूर्णांक unmasked;
	FPU_REG loaded_data;
	FPU_REG *st0_ptr;
	u_अक्षर loaded_tag, st0_tag;
	व्योम __user *data_address;
	काष्ठा address data_sel_off;
	काष्ठा address entry_sel_off;
	अचिन्हित दीर्घ code_base = 0;
	अचिन्हित दीर्घ code_limit = 0;	/* Initialized to stop compiler warnings */
	काष्ठा desc_काष्ठा code_descriptor;

#अगर_घोषित RE_ENTRANT_CHECKING
	अगर (emulating) अणु
		prपूर्णांकk("ERROR: wm-FPU-emu is not RE-ENTRANT!\n");
	पूर्ण
	RE_ENTRANT_CHECK_ON;
#पूर्ण_अगर /* RE_ENTRANT_CHECKING */

	FPU_info = info;

	FPU_ORIG_EIP = FPU_EIP;

	अगर ((FPU_EFLAGS & 0x00020000) != 0) अणु
		/* Virtual 8086 mode */
		addr_modes.शेष_mode = VM86;
		FPU_EIP += code_base = FPU_CS << 4;
		code_limit = code_base + 0xffff;	/* Assumes code_base <= 0xffff0000 */
	पूर्ण अन्यथा अगर (FPU_CS == __USER_CS && FPU_DS == __USER_DS) अणु
		addr_modes.शेष_mode = 0;
	पूर्ण अन्यथा अगर (FPU_CS == __KERNEL_CS) अणु
		prपूर्णांकk("math_emulate: %04x:%08lx\n", FPU_CS, FPU_EIP);
		panic("Math emulation needed in kernel");
	पूर्ण अन्यथा अणु

		अगर ((FPU_CS & 4) != 4) अणु	/* Must be in the LDT */
			/* Can only handle segmented addressing via the LDT
			   क्रम now, and it must be 16 bit */
			prपूर्णांकk("FPU emulator: Unsupported addressing mode\n");
			math_पात(FPU_info, संक_अवैध);
		पूर्ण

		code_descriptor = FPU_get_ldt_descriptor(FPU_CS);
		अगर (code_descriptor.d) अणु
			/* The above test may be wrong, the book is not clear */
			/* Segmented 32 bit रक्षित mode */
			addr_modes.शेष_mode = SEG32;
		पूर्ण अन्यथा अणु
			/* 16 bit रक्षित mode */
			addr_modes.शेष_mode = PM16;
		पूर्ण
		FPU_EIP += code_base = seg_get_base(&code_descriptor);
		code_limit = seg_get_limit(&code_descriptor) + 1;
		code_limit *= seg_get_granularity(&code_descriptor);
		code_limit += code_base - 1;
		अगर (code_limit < code_base)
			code_limit = 0xffffffff;
	पूर्ण

	FPU_lookahead = !(FPU_EFLAGS & X86_EFLAGS_TF);

	अगर (!valid_prefix(&byte1, (u_अक्षर __user **) & FPU_EIP,
			  &addr_modes.override)) अणु
		RE_ENTRANT_CHECK_OFF;
		prपूर्णांकk
		    ("FPU emulator: Unknown prefix byte 0x%02x, probably due to\n"
		     "FPU emulator: self-modifying code! (emulation impossible)\n",
		     byte1);
		RE_ENTRANT_CHECK_ON;
		EXCEPTION(EX_INTERNAL | 0x126);
		math_पात(FPU_info, संक_अवैध);
	पूर्ण

      करो_another_FPU_inकाष्ठाion:

	no_ip_update = 0;

	FPU_EIP++;		/* We have fetched the prefix and first code bytes. */

	अगर (addr_modes.शेष_mode) अणु
		/* This checks क्रम the minimum inकाष्ठाion bytes.
		   We also need to check any extra (address mode) code access. */
		अगर (FPU_EIP > code_limit)
			math_पात(FPU_info, संक_अंश);
	पूर्ण

	अगर ((byte1 & 0xf8) != 0xd8) अणु
		अगर (byte1 == FWAIT_OPCODE) अणु
			अगर (partial_status & SW_Summary)
				जाओ करो_the_FPU_पूर्णांकerrupt;
			अन्यथा
				जाओ FPU_fरुको_करोne;
		पूर्ण
#अगर_घोषित PARANOID
		EXCEPTION(EX_INTERNAL | 0x128);
		math_पात(FPU_info, संक_अवैध);
#पूर्ण_अगर /* PARANOID */
	पूर्ण

	RE_ENTRANT_CHECK_OFF;
	FPU_code_access_ok(1);
	FPU_get_user(FPU_modrm, (u_अक्षर __user *) FPU_EIP);
	RE_ENTRANT_CHECK_ON;
	FPU_EIP++;

	अगर (partial_status & SW_Summary) अणु
		/* Ignore the error क्रम now अगर the current inकाष्ठाion is a no-रुको
		   control inकाष्ठाion */
		/* The 80486 manual contradicts itself on this topic,
		   but a real 80486 uses the following inकाष्ठाions:
		   fninit, fnstenv, fnsave, fnstsw, fnstenv, fnclex.
		 */
		code = (FPU_modrm << 8) | byte1;
		अगर (!((((code & 0xf803) == 0xe003) ||	/* fnclex, fninit, fnstsw */
		       (((code & 0x3003) == 0x3001) &&	/* fnsave, fnstcw, fnstenv,
							   fnstsw */
			((code & 0xc000) != 0xc000))))) अणु
			/*
			 *  We need to simulate the action of the kernel to FPU
			 *  पूर्णांकerrupts here.
			 */
		      करो_the_FPU_पूर्णांकerrupt:

			FPU_EIP = FPU_ORIG_EIP;	/* Poपूर्णांक to current FPU inकाष्ठाion. */

			RE_ENTRANT_CHECK_OFF;
			current->thपढ़ो.trap_nr = X86_TRAP_MF;
			current->thपढ़ो.error_code = 0;
			send_sig(संक_भ_त्रुटि, current, 1);
			वापस;
		पूर्ण
	पूर्ण

	entry_sel_off.offset = FPU_ORIG_EIP;
	entry_sel_off.selector = FPU_CS;
	entry_sel_off.opcode = (byte1 << 8) | FPU_modrm;
	entry_sel_off.empty = 0;

	FPU_rm = FPU_modrm & 7;

	अगर (FPU_modrm < 0300) अणु
		/* All of these inकाष्ठाions use the mod/rm byte to get a data address */

		अगर ((addr_modes.शेष_mode & SIXTEEN)
		    ^ (addr_modes.override.address_size == ADDR_SIZE_PREFIX))
			data_address =
			    FPU_get_address_16(FPU_modrm, &FPU_EIP,
					       &data_sel_off, addr_modes);
		अन्यथा
			data_address =
			    FPU_get_address(FPU_modrm, &FPU_EIP, &data_sel_off,
					    addr_modes);

		अगर (addr_modes.शेष_mode) अणु
			अगर (FPU_EIP - 1 > code_limit)
				math_पात(FPU_info, संक_अंश);
		पूर्ण

		अगर (!(byte1 & 1)) अणु
			अचिन्हित लघु status1 = partial_status;

			st0_ptr = &st(0);
			st0_tag = FPU_gettag0();

			/* Stack underflow has priority */
			अगर (NOT_EMPTY_ST0) अणु
				अगर (addr_modes.शेष_mode & PROTECTED) अणु
					/* This table works क्रम 16 and 32 bit रक्षित mode */
					अगर (access_limit <
					    data_sizes_16[(byte1 >> 1) & 3])
						math_पात(FPU_info, संक_अंश);
				पूर्ण

				unmasked = 0;	/* Do this here to stop compiler warnings. */
				चयन ((byte1 >> 1) & 3) अणु
				हाल 0:
					unmasked =
					    FPU_load_single((भग्न __user *)
							    data_address,
							    &loaded_data);
					loaded_tag = unmasked & 0xff;
					unmasked &= ~0xff;
					अवरोध;
				हाल 1:
					loaded_tag =
					    FPU_load_पूर्णांक32((दीर्घ __user *)
							   data_address,
							   &loaded_data);
					अवरोध;
				हाल 2:
					unmasked =
					    FPU_load_द्विगुन((द्विगुन __user *)
							    data_address,
							    &loaded_data);
					loaded_tag = unmasked & 0xff;
					unmasked &= ~0xff;
					अवरोध;
				हाल 3:
				शेष:	/* Used here to suppress gcc warnings. */
					loaded_tag =
					    FPU_load_पूर्णांक16((लघु __user *)
							   data_address,
							   &loaded_data);
					अवरोध;
				पूर्ण

				/* No more access to user memory, it is safe
				   to use अटल data now */

				/* NaN opeअक्रमs have the next priority. */
				/* We have to delay looking at st(0) until after
				   loading the data, because that data might contain an SNaN */
				अगर (((st0_tag == TAG_Special) && isNaN(st0_ptr))
				    || ((loaded_tag == TAG_Special)
					&& isNaN(&loaded_data))) अणु
					/* Restore the status word; we might have loaded a
					   denormal. */
					partial_status = status1;
					अगर ((FPU_modrm & 0x30) == 0x10) अणु
						/* fcom or fcomp */
						EXCEPTION(EX_Invalid);
						setcc(SW_C3 | SW_C2 | SW_C0);
						अगर ((FPU_modrm & 0x08)
						    && (control_word &
							CW_Invalid))
							FPU_pop();	/* fcomp, masked, so we pop. */
					पूर्ण अन्यथा अणु
						अगर (loaded_tag == TAG_Special)
							loaded_tag =
							    FPU_Special
							    (&loaded_data);
#अगर_घोषित PECULIAR_486
						/* This is not really needed, but gives behaviour
						   identical to an 80486 */
						अगर ((FPU_modrm & 0x28) == 0x20)
							/* fभाग or fsub */
							real_2op_NaN
							    (&loaded_data,
							     loaded_tag, 0,
							     &loaded_data);
						अन्यथा
#पूर्ण_अगर /* PECULIAR_486 */
							/* fadd, fभागr, fmul, or fsubr */
							real_2op_NaN
							    (&loaded_data,
							     loaded_tag, 0,
							     st0_ptr);
					पूर्ण
					जाओ reg_mem_instr_करोne;
				पूर्ण

				अगर (unmasked && !((FPU_modrm & 0x30) == 0x10)) अणु
					/* Is not a comparison inकाष्ठाion. */
					अगर ((FPU_modrm & 0x38) == 0x38) अणु
						/* fभागr */
						अगर ((st0_tag == TAG_Zero) &&
						    ((loaded_tag == TAG_Valid)
						     || (loaded_tag ==
							 TAG_Special
							 &&
							 isdenormal
							 (&loaded_data)))) अणु
							अगर (FPU_भागide_by_zero
							    (0,
							     माला_लोign
							     (&loaded_data))
							    < 0) अणु
								/* We use the fact here that the unmasked
								   exception in the loaded data was क्रम a
								   denormal opeअक्रम */
								/* Restore the state of the denormal op bit */
								partial_status
								    &=
								    ~SW_Denorm_Op;
								partial_status
								    |=
								    status1 &
								    SW_Denorm_Op;
							पूर्ण अन्यथा
								setsign(st0_ptr,
									माला_लोign
									(&loaded_data));
						पूर्ण
					पूर्ण
					जाओ reg_mem_instr_करोne;
				पूर्ण

				चयन ((FPU_modrm >> 3) & 7) अणु
				हाल 0:	/* fadd */
					clear_C1();
					FPU_add(&loaded_data, loaded_tag, 0,
						control_word);
					अवरोध;
				हाल 1:	/* fmul */
					clear_C1();
					FPU_mul(&loaded_data, loaded_tag, 0,
						control_word);
					अवरोध;
				हाल 2:	/* fcom */
					FPU_compare_st_data(&loaded_data,
							    loaded_tag);
					अवरोध;
				हाल 3:	/* fcomp */
					अगर (!FPU_compare_st_data
					    (&loaded_data, loaded_tag)
					    && !unmasked)
						FPU_pop();
					अवरोध;
				हाल 4:	/* fsub */
					clear_C1();
					FPU_sub(LOADED | loaded_tag,
						(पूर्णांक)&loaded_data,
						control_word);
					अवरोध;
				हाल 5:	/* fsubr */
					clear_C1();
					FPU_sub(REV | LOADED | loaded_tag,
						(पूर्णांक)&loaded_data,
						control_word);
					अवरोध;
				हाल 6:	/* fभाग */
					clear_C1();
					FPU_भाग(LOADED | loaded_tag,
						(पूर्णांक)&loaded_data,
						control_word);
					अवरोध;
				हाल 7:	/* fभागr */
					clear_C1();
					अगर (st0_tag == TAG_Zero)
						partial_status = status1;	/* Unकरो any denorm tag,
										   zero-भागide has priority. */
					FPU_भाग(REV | LOADED | loaded_tag,
						(पूर्णांक)&loaded_data,
						control_word);
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर ((FPU_modrm & 0x30) == 0x10) अणु
					/* The inकाष्ठाion is fcom or fcomp */
					EXCEPTION(EX_StackUnder);
					setcc(SW_C3 | SW_C2 | SW_C0);
					अगर ((FPU_modrm & 0x08)
					    && (control_word & CW_Invalid))
						FPU_pop();	/* fcomp */
				पूर्ण अन्यथा
					FPU_stack_underflow();
			पूर्ण
		      reg_mem_instr_करोne:
			opeअक्रम_address = data_sel_off;
		पूर्ण अन्यथा अणु
			अगर (!(no_ip_update =
			      FPU_load_store(((FPU_modrm & 0x38) | (byte1 & 6))
					     >> 1, addr_modes, data_address))) अणु
				opeअक्रम_address = data_sel_off;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		/* None of these inकाष्ठाions access user memory */
		u_अक्षर instr_index = (FPU_modrm & 0x38) | (byte1 & 7);

#अगर_घोषित PECULIAR_486
		/* This is supposed to be undefined, but a real 80486 seems
		   to करो this: */
		opeअक्रम_address.offset = 0;
		opeअक्रम_address.selector = FPU_DS;
#पूर्ण_अगर /* PECULIAR_486 */

		st0_ptr = &st(0);
		st0_tag = FPU_gettag0();
		चयन (type_table[(पूर्णांक)instr_index]) अणु
		हाल _NONE_:	/* also _REGIc: _REGIn */
			अवरोध;
		हाल _REG0_:
			अगर (!NOT_EMPTY_ST0) अणु
				FPU_stack_underflow();
				जाओ FPU_inकाष्ठाion_करोne;
			पूर्ण
			अवरोध;
		हाल _REGIi:
			अगर (!NOT_EMPTY_ST0 || !NOT_EMPTY(FPU_rm)) अणु
				FPU_stack_underflow_i(FPU_rm);
				जाओ FPU_inकाष्ठाion_करोne;
			पूर्ण
			अवरोध;
		हाल _REGIp:
			अगर (!NOT_EMPTY_ST0 || !NOT_EMPTY(FPU_rm)) अणु
				FPU_stack_underflow_pop(FPU_rm);
				जाओ FPU_inकाष्ठाion_करोne;
			पूर्ण
			अवरोध;
		हाल _REGI_:
			अगर (!NOT_EMPTY_ST0 || !NOT_EMPTY(FPU_rm)) अणु
				FPU_stack_underflow();
				जाओ FPU_inकाष्ठाion_करोne;
			पूर्ण
			अवरोध;
		हाल _PUSH_:	/* Only used by the fld st(i) inकाष्ठाion */
			अवरोध;
		हाल _null_:
			FPU_illegal();
			जाओ FPU_inकाष्ठाion_करोne;
		शेष:
			EXCEPTION(EX_INTERNAL | 0x111);
			जाओ FPU_inकाष्ठाion_करोne;
		पूर्ण
		(*st_instr_table[(पूर्णांक)instr_index]) ();

	      FPU_inकाष्ठाion_करोne:
		;
	पूर्ण

	अगर (!no_ip_update)
		inकाष्ठाion_address = entry_sel_off;

      FPU_fरुको_करोne:

#अगर_घोषित DEBUG
	RE_ENTRANT_CHECK_OFF;
	FPU_prपूर्णांकall();
	RE_ENTRANT_CHECK_ON;
#पूर्ण_अगर /* DEBUG */

	अगर (FPU_lookahead && !need_resched()) अणु
		FPU_ORIG_EIP = FPU_EIP - code_base;
		अगर (valid_prefix(&byte1, (u_अक्षर __user **) & FPU_EIP,
				 &addr_modes.override))
			जाओ करो_another_FPU_inकाष्ठाion;
	पूर्ण

	अगर (addr_modes.शेष_mode)
		FPU_EIP -= code_base;

	RE_ENTRANT_CHECK_OFF;
पूर्ण

/* Support क्रम prefix bytes is not yet complete. To properly handle
   all prefix bytes, further changes are needed in the emulator code
   which accesses user address space. Access to separate segments is
   important क्रम msकरोs emulation. */
अटल पूर्णांक valid_prefix(u_अक्षर *Byte, u_अक्षर __user **fpu_eip,
			overrides * override)
अणु
	u_अक्षर byte;
	u_अक्षर __user *ip = *fpu_eip;

	*override = (overrides) अणु
	0, 0, PREFIX_DEFAULTपूर्ण;	/* शेषs */

	RE_ENTRANT_CHECK_OFF;
	FPU_code_access_ok(1);
	FPU_get_user(byte, ip);
	RE_ENTRANT_CHECK_ON;

	जबतक (1) अणु
		चयन (byte) अणु
		हाल ADDR_SIZE_PREFIX:
			override->address_size = ADDR_SIZE_PREFIX;
			जाओ करो_next_byte;

		हाल OP_SIZE_PREFIX:
			override->opeअक्रम_size = OP_SIZE_PREFIX;
			जाओ करो_next_byte;

		हाल PREFIX_CS:
			override->segment = PREFIX_CS_;
			जाओ करो_next_byte;
		हाल PREFIX_ES:
			override->segment = PREFIX_ES_;
			जाओ करो_next_byte;
		हाल PREFIX_SS:
			override->segment = PREFIX_SS_;
			जाओ करो_next_byte;
		हाल PREFIX_FS:
			override->segment = PREFIX_FS_;
			जाओ करो_next_byte;
		हाल PREFIX_GS:
			override->segment = PREFIX_GS_;
			जाओ करो_next_byte;
		हाल PREFIX_DS:
			override->segment = PREFIX_DS_;
			जाओ करो_next_byte;

/* lock is not a valid prefix क्रम FPU inकाष्ठाions,
   let the cpu handle it to generate a संक_अवैध. */
/*	हाल PREFIX_LOCK: */

			/* rep.. prefixes have no meaning क्रम FPU inकाष्ठाions */
		हाल PREFIX_REPE:
		हाल PREFIX_REPNE:

		      करो_next_byte:
			ip++;
			RE_ENTRANT_CHECK_OFF;
			FPU_code_access_ok(1);
			FPU_get_user(byte, ip);
			RE_ENTRANT_CHECK_ON;
			अवरोध;
		हाल FWAIT_OPCODE:
			*Byte = byte;
			वापस 1;
		शेष:
			अगर ((byte & 0xf8) == 0xd8) अणु
				*Byte = byte;
				*fpu_eip = ip;
				वापस 1;
			पूर्ण अन्यथा अणु
				/* Not a valid sequence of prefix bytes followed by
				   an FPU inकाष्ठाion. */
				*Byte = byte;	/* Needed क्रम error message. */
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम math_पात(काष्ठा math_emu_info *info, अचिन्हित पूर्णांक संकेत)
अणु
	FPU_EIP = FPU_ORIG_EIP;
	current->thपढ़ो.trap_nr = X86_TRAP_MF;
	current->thपढ़ो.error_code = 0;
	send_sig(संकेत, current, 1);
	RE_ENTRANT_CHECK_OFF;
      __यंत्र__("movl %0,%%esp ; ret": :"g"(((दीर्घ)info) - 4));
#अगर_घोषित PARANOID
	prपूर्णांकk("ERROR: wm-FPU-emu math_abort failed!\n");
#पूर्ण_अगर /* PARANOID */
पूर्ण

#घोषणा S387 ((काष्ठा swregs_state *)s387)
#घोषणा sstatus_word() \
  ((S387->swd & ~SW_Top & 0xffff) | ((S387->ftop << SW_Top_Shअगरt) & SW_Top))

पूर्णांक fpregs_soft_set(काष्ठा task_काष्ठा *target,
		    स्थिर काष्ठा user_regset *regset,
		    अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		    स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा swregs_state *s387 = &target->thपढ़ो.fpu.state.soft;
	व्योम *space = s387->st_space;
	पूर्णांक ret;
	पूर्णांक offset, other, i, tags, regnr, tag, newtop;

	RE_ENTRANT_CHECK_OFF;
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, s387, 0,
				 दुरत्व(काष्ठा swregs_state, st_space));
	RE_ENTRANT_CHECK_ON;

	अगर (ret)
		वापस ret;

	S387->ftop = (S387->swd >> SW_Top_Shअगरt) & 7;
	offset = (S387->ftop & 7) * 10;
	other = 80 - offset;

	RE_ENTRANT_CHECK_OFF;

	/* Copy all रेजिस्टरs in stack order. */
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 space + offset, 0, other);
	अगर (!ret && offset)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 space, 0, offset);

	RE_ENTRANT_CHECK_ON;

	/* The tags may need to be corrected now. */
	tags = S387->twd;
	newtop = S387->ftop;
	क्रम (i = 0; i < 8; i++) अणु
		regnr = (i + newtop) & 7;
		अगर (((tags >> ((regnr & 7) * 2)) & 3) != TAG_Empty) अणु
			/* The loaded data over-rides all other हालs. */
			tag =
			    FPU_tagof((FPU_REG *) ((u_अक्षर *) S387->st_space +
						   10 * regnr));
			tags &= ~(3 << (regnr * 2));
			tags |= (tag & 3) << (regnr * 2);
		पूर्ण
	पूर्ण
	S387->twd = tags;

	वापस ret;
पूर्ण

पूर्णांक fpregs_soft_get(काष्ठा task_काष्ठा *target,
		    स्थिर काष्ठा user_regset *regset,
		    काष्ठा membuf to)
अणु
	काष्ठा swregs_state *s387 = &target->thपढ़ो.fpu.state.soft;
	स्थिर व्योम *space = s387->st_space;
	पूर्णांक offset = (S387->ftop & 7) * 10, other = 80 - offset;

	RE_ENTRANT_CHECK_OFF;

#अगर_घोषित PECULIAR_486
	S387->cwd &= ~0xe080;
	/* An 80486 sets nearly all of the reserved bits to 1. */
	S387->cwd |= 0xffff0040;
	S387->swd = sstatus_word() | 0xffff0000;
	S387->twd |= 0xffff0000;
	S387->fcs &= ~0xf8000000;
	S387->fos |= 0xffff0000;
#पूर्ण_अगर /* PECULIAR_486 */

	membuf_ग_लिखो(&to, s387, दुरत्व(काष्ठा swregs_state, st_space));
	membuf_ग_लिखो(&to, space + offset, other);
	membuf_ग_लिखो(&to, space, offset);

	RE_ENTRANT_CHECK_ON;

	वापस 0;
पूर्ण
