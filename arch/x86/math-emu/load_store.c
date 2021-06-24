<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  load_store.c                                                             |
 |                                                                           |
 | This file contains most of the code to पूर्णांकerpret the FPU inकाष्ठाions     |
 | which load and store from user memory.                                    |
 |                                                                           |
 | Copyright (C) 1992,1993,1994,1997                                         |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail   billm@suburbia.net             |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | Note:                                                                     |
 |    The file contains code which accesses user memory.                     |
 |    Emulator अटल data may change when user memory is accessed, due to   |
 |    other processes using the emulator जबतक swapping is in progress.      |
 +---------------------------------------------------------------------------*/

#समावेश <linux/uaccess.h>

#समावेश "fpu_system.h"
#समावेश "exception.h"
#समावेश "fpu_emu.h"
#समावेश "status_w.h"
#समावेश "control_w.h"

#घोषणा _NONE_ 0		/* st0_ptr etc not needed */
#घोषणा _REG0_ 1		/* Will be storing st(0) */
#घोषणा _PUSH_ 3		/* Need to check क्रम space to push onto stack */
#घोषणा _null_ 4		/* Function illegal or not implemented */

#घोषणा pop_0()	अणु FPU_settag0(TAG_Empty); top++; पूर्ण

/* index is a 5-bit value: (3-bit FPU_modrm.reg field | opcode[2,1]) */
अटल u_अक्षर स्थिर type_table[32] = अणु
	_PUSH_, _PUSH_, _PUSH_, _PUSH_, /* /0: d9:fld f32,  db:fild m32,  dd:fld f64,  df:fild m16 */
	_null_, _REG0_, _REG0_, _REG0_, /* /1: d9:undef,    db,dd,df:fisttp m32/64/16 */
	_REG0_, _REG0_, _REG0_, _REG0_, /* /2: d9:fst f32,  db:fist m32,  dd:fst f64,  df:fist m16 */
	_REG0_, _REG0_, _REG0_, _REG0_, /* /3: d9:fstp f32, db:fistp m32, dd:fstp f64, df:fistp m16 */
	_NONE_, _null_, _NONE_, _PUSH_,
	_NONE_, _PUSH_, _null_, _PUSH_,
	_NONE_, _null_, _NONE_, _REG0_,
	_NONE_, _REG0_, _NONE_, _REG0_
पूर्ण;

u_अक्षर स्थिर data_sizes_16[32] = अणु
	4, 4, 8, 2,
	0, 4, 8, 2, /* /1: d9:undef, db,dd,df:fisttp */
	4, 4, 8, 2,
	4, 4, 8, 2,
	14, 0, 94, 10, 2, 10, 0, 8,
	14, 0, 94, 10, 2, 10, 2, 8
पूर्ण;

अटल u_अक्षर स्थिर data_sizes_32[32] = अणु
	4, 4, 8, 2,
	0, 4, 8, 2, /* /1: d9:undef, db,dd,df:fisttp */
	4, 4, 8, 2,
	4, 4, 8, 2,
	28, 0, 108, 10, 2, 10, 0, 8,
	28, 0, 108, 10, 2, 10, 2, 8
पूर्ण;

पूर्णांक FPU_load_store(u_अक्षर type, fpu_addr_modes addr_modes,
		   व्योम __user * data_address)
अणु
	FPU_REG loaded_data;
	FPU_REG *st0_ptr;
	u_अक्षर st0_tag = TAG_Empty;	/* This is just to stop a gcc warning. */
	u_अक्षर loaded_tag;
	पूर्णांक sv_cw;

	st0_ptr = शून्य;		/* Initialized just to stop compiler warnings. */

	अगर (addr_modes.शेष_mode & PROTECTED) अणु
		अगर (addr_modes.शेष_mode == SEG32) अणु
			अगर (access_limit < data_sizes_32[type])
				math_पात(FPU_info, संक_अंश);
		पूर्ण अन्यथा अगर (addr_modes.शेष_mode == PM16) अणु
			अगर (access_limit < data_sizes_16[type])
				math_पात(FPU_info, संक_अंश);
		पूर्ण
#अगर_घोषित PARANOID
		अन्यथा
			EXCEPTION(EX_INTERNAL | 0x140);
#पूर्ण_अगर /* PARANOID */
	पूर्ण

	चयन (type_table[type]) अणु
	हाल _NONE_:
		अवरोध;
	हाल _REG0_:
		st0_ptr = &st(0);	/* Some of these inकाष्ठाions pop after
					   storing */
		st0_tag = FPU_gettag0();
		अवरोध;
	हाल _PUSH_:
		अणु
			अगर (FPU_gettagi(-1) != TAG_Empty) अणु
				FPU_stack_overflow();
				वापस 0;
			पूर्ण
			top--;
			st0_ptr = &st(0);
		पूर्ण
		अवरोध;
	हाल _null_:
		FPU_illegal();
		वापस 0;
#अगर_घोषित PARANOID
	शेष:
		EXCEPTION(EX_INTERNAL | 0x141);
		वापस 0;
#पूर्ण_अगर /* PARANOID */
	पूर्ण

	चयन (type) अणु
	/* type is a 5-bit value: (3-bit FPU_modrm.reg field | opcode[2,1]) */
	हाल 000:		/* fld m32real (d9 /0) */
		clear_C1();
		loaded_tag =
		    FPU_load_single((भग्न __user *)data_address, &loaded_data);
		अगर ((loaded_tag == TAG_Special)
		    && isNaN(&loaded_data)
		    && (real_1op_NaN(&loaded_data) < 0)) अणु
			top++;
			अवरोध;
		पूर्ण
		FPU_copy_to_reg0(&loaded_data, loaded_tag);
		अवरोध;
	हाल 001:		/* fild m32पूर्णांक (db /0) */
		clear_C1();
		loaded_tag =
		    FPU_load_पूर्णांक32((दीर्घ __user *)data_address, &loaded_data);
		FPU_copy_to_reg0(&loaded_data, loaded_tag);
		अवरोध;
	हाल 002:		/* fld m64real (dd /0) */
		clear_C1();
		loaded_tag =
		    FPU_load_द्विगुन((द्विगुन __user *)data_address,
				    &loaded_data);
		अगर ((loaded_tag == TAG_Special)
		    && isNaN(&loaded_data)
		    && (real_1op_NaN(&loaded_data) < 0)) अणु
			top++;
			अवरोध;
		पूर्ण
		FPU_copy_to_reg0(&loaded_data, loaded_tag);
		अवरोध;
	हाल 003:		/* fild m16पूर्णांक (df /0) */
		clear_C1();
		loaded_tag =
		    FPU_load_पूर्णांक16((लघु __user *)data_address, &loaded_data);
		FPU_copy_to_reg0(&loaded_data, loaded_tag);
		अवरोध;
	/* हाल 004: undefined (d9 /1) */
	/* fisttp are enabled अगर CPUID(1).ECX(0) "sse3" is set */
	हाल 005:		/* fisttp m32पूर्णांक (db /1) */
		clear_C1();
		sv_cw = control_word;
		control_word |= RC_CHOP;
		अगर (FPU_store_पूर्णांक32
		    (st0_ptr, st0_tag, (दीर्घ __user *)data_address))
			pop_0();	/* pop only अगर the number was actually stored
					   (see the 80486 manual p16-28) */
		control_word = sv_cw;
		अवरोध;
	हाल 006:		/* fisttp m64पूर्णांक (dd /1) */
		clear_C1();
		sv_cw = control_word;
		control_word |= RC_CHOP;
		अगर (FPU_store_पूर्णांक64
		    (st0_ptr, st0_tag, (दीर्घ दीर्घ __user *)data_address))
			pop_0();	/* pop only अगर the number was actually stored
					   (see the 80486 manual p16-28) */
		control_word = sv_cw;
		अवरोध;
	हाल 007:		/* fisttp m16पूर्णांक (df /1) */
		clear_C1();
		sv_cw = control_word;
		control_word |= RC_CHOP;
		अगर (FPU_store_पूर्णांक16
		    (st0_ptr, st0_tag, (लघु __user *)data_address))
			pop_0();	/* pop only अगर the number was actually stored
					   (see the 80486 manual p16-28) */
		control_word = sv_cw;
		अवरोध;
	हाल 010:		/* fst m32real */
		clear_C1();
		FPU_store_single(st0_ptr, st0_tag,
				 (भग्न __user *)data_address);
		अवरोध;
	हाल 011:		/* fist m32पूर्णांक */
		clear_C1();
		FPU_store_पूर्णांक32(st0_ptr, st0_tag, (दीर्घ __user *)data_address);
		अवरोध;
	हाल 012:		/* fst m64real */
		clear_C1();
		FPU_store_द्विगुन(st0_ptr, st0_tag,
				 (द्विगुन __user *)data_address);
		अवरोध;
	हाल 013:		/* fist m16पूर्णांक */
		clear_C1();
		FPU_store_पूर्णांक16(st0_ptr, st0_tag, (लघु __user *)data_address);
		अवरोध;
	हाल 014:		/* fstp m32real */
		clear_C1();
		अगर (FPU_store_single
		    (st0_ptr, st0_tag, (भग्न __user *)data_address))
			pop_0();	/* pop only अगर the number was actually stored
					   (see the 80486 manual p16-28) */
		अवरोध;
	हाल 015:		/* fistp m32पूर्णांक */
		clear_C1();
		अगर (FPU_store_पूर्णांक32
		    (st0_ptr, st0_tag, (दीर्घ __user *)data_address))
			pop_0();	/* pop only अगर the number was actually stored
					   (see the 80486 manual p16-28) */
		अवरोध;
	हाल 016:		/* fstp m64real */
		clear_C1();
		अगर (FPU_store_द्विगुन
		    (st0_ptr, st0_tag, (द्विगुन __user *)data_address))
			pop_0();	/* pop only अगर the number was actually stored
					   (see the 80486 manual p16-28) */
		अवरोध;
	हाल 017:		/* fistp m16पूर्णांक */
		clear_C1();
		अगर (FPU_store_पूर्णांक16
		    (st0_ptr, st0_tag, (लघु __user *)data_address))
			pop_0();	/* pop only अगर the number was actually stored
					   (see the 80486 manual p16-28) */
		अवरोध;
	हाल 020:		/* fldenv  m14/28byte */
		fldenv(addr_modes, (u_अक्षर __user *) data_address);
		/* Ensure that the values just loaded are not changed by
		   fix-up operations. */
		वापस 1;
	हाल 022:		/* frstor m94/108byte */
		frstor(addr_modes, (u_अक्षर __user *) data_address);
		/* Ensure that the values just loaded are not changed by
		   fix-up operations. */
		वापस 1;
	हाल 023:		/* fbld m80dec */
		clear_C1();
		loaded_tag = FPU_load_bcd((u_अक्षर __user *) data_address);
		FPU_settag0(loaded_tag);
		अवरोध;
	हाल 024:		/* fldcw */
		RE_ENTRANT_CHECK_OFF;
		FPU_access_ok(data_address, 2);
		FPU_get_user(control_word,
			     (अचिन्हित लघु __user *)data_address);
		RE_ENTRANT_CHECK_ON;
		अगर (partial_status & ~control_word & CW_Exceptions)
			partial_status |= (SW_Summary | SW_Backward);
		अन्यथा
			partial_status &= ~(SW_Summary | SW_Backward);
#अगर_घोषित PECULIAR_486
		control_word |= 0x40;	/* An 80486 appears to always set this bit */
#पूर्ण_अगर /* PECULIAR_486 */
		वापस 1;
	हाल 025:		/* fld m80real */
		clear_C1();
		loaded_tag =
		    FPU_load_extended((दीर्घ द्विगुन __user *)data_address, 0);
		FPU_settag0(loaded_tag);
		अवरोध;
	हाल 027:		/* fild m64पूर्णांक */
		clear_C1();
		loaded_tag = FPU_load_पूर्णांक64((दीर्घ दीर्घ __user *)data_address);
		अगर (loaded_tag == TAG_Error)
			वापस 0;
		FPU_settag0(loaded_tag);
		अवरोध;
	हाल 030:		/* fstenv  m14/28byte */
		fstenv(addr_modes, (u_अक्षर __user *) data_address);
		वापस 1;
	हाल 032:		/* fsave */
		fsave(addr_modes, (u_अक्षर __user *) data_address);
		वापस 1;
	हाल 033:		/* fbstp m80dec */
		clear_C1();
		अगर (FPU_store_bcd
		    (st0_ptr, st0_tag, (u_अक्षर __user *) data_address))
			pop_0();	/* pop only अगर the number was actually stored
					   (see the 80486 manual p16-28) */
		अवरोध;
	हाल 034:		/* fstcw m16पूर्णांक */
		RE_ENTRANT_CHECK_OFF;
		FPU_access_ok(data_address, 2);
		FPU_put_user(control_word,
			     (अचिन्हित लघु __user *)data_address);
		RE_ENTRANT_CHECK_ON;
		वापस 1;
	हाल 035:		/* fstp m80real */
		clear_C1();
		अगर (FPU_store_extended
		    (st0_ptr, st0_tag, (दीर्घ द्विगुन __user *)data_address))
			pop_0();	/* pop only अगर the number was actually stored
					   (see the 80486 manual p16-28) */
		अवरोध;
	हाल 036:		/* fstsw m2byte */
		RE_ENTRANT_CHECK_OFF;
		FPU_access_ok(data_address, 2);
		FPU_put_user(status_word(),
			     (अचिन्हित लघु __user *)data_address);
		RE_ENTRANT_CHECK_ON;
		वापस 1;
	हाल 037:		/* fistp m64पूर्णांक */
		clear_C1();
		अगर (FPU_store_पूर्णांक64
		    (st0_ptr, st0_tag, (दीर्घ दीर्घ __user *)data_address))
			pop_0();	/* pop only अगर the number was actually stored
					   (see the 80486 manual p16-28) */
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
