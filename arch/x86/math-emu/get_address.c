<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*---------------------------------------------------------------------------+
 |  get_address.c                                                            |
 |                                                                           |
 | Get the effective address from an FPU inकाष्ठाion.                        |
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

#समावेश <linux/मानकघोष.स>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/vm86.h>

#समावेश "fpu_system.h"
#समावेश "exception.h"
#समावेश "fpu_emu.h"

#घोषणा FPU_WRITE_BIT 0x10

अटल पूर्णांक reg_offset[] = अणु
	दुरत्व(काष्ठा pt_regs, ax),
	दुरत्व(काष्ठा pt_regs, cx),
	दुरत्व(काष्ठा pt_regs, dx),
	दुरत्व(काष्ठा pt_regs, bx),
	दुरत्व(काष्ठा pt_regs, sp),
	दुरत्व(काष्ठा pt_regs, bp),
	दुरत्व(काष्ठा pt_regs, si),
	दुरत्व(काष्ठा pt_regs, di)
पूर्ण;

#घोषणा REG_(x) (*(दीर्घ *)(reg_offset[(x)] + (u_अक्षर *)FPU_info->regs))

अटल पूर्णांक reg_offset_vm86[] = अणु
	दुरत्व(काष्ठा pt_regs, cs),
	दुरत्व(काष्ठा kernel_vm86_regs, ds),
	दुरत्व(काष्ठा kernel_vm86_regs, es),
	दुरत्व(काष्ठा kernel_vm86_regs, fs),
	दुरत्व(काष्ठा kernel_vm86_regs, gs),
	दुरत्व(काष्ठा pt_regs, ss),
	दुरत्व(काष्ठा kernel_vm86_regs, ds)
पूर्ण;

#घोषणा VM86_REG_(x) (*(अचिन्हित लघु *) \
		(reg_offset_vm86[((अचिन्हित)x)] + (u_अक्षर *)FPU_info->regs))

अटल पूर्णांक reg_offset_pm[] = अणु
	दुरत्व(काष्ठा pt_regs, cs),
	दुरत्व(काष्ठा pt_regs, ds),
	दुरत्व(काष्ठा pt_regs, es),
	दुरत्व(काष्ठा pt_regs, fs),
	दुरत्व(काष्ठा pt_regs, ds),	/* dummy, not saved on stack */
	दुरत्व(काष्ठा pt_regs, ss),
	दुरत्व(काष्ठा pt_regs, ds)
पूर्ण;

#घोषणा PM_REG_(x) (*(अचिन्हित लघु *) \
		(reg_offset_pm[((अचिन्हित)x)] + (u_अक्षर *)FPU_info->regs))

/* Decode the SIB byte. This function assumes mod != 0 */
अटल पूर्णांक sib(पूर्णांक mod, अचिन्हित दीर्घ *fpu_eip)
अणु
	u_अक्षर ss, index, base;
	दीर्घ offset;

	RE_ENTRANT_CHECK_OFF;
	FPU_code_access_ok(1);
	FPU_get_user(base, (u_अक्षर __user *) (*fpu_eip));	/* The SIB byte */
	RE_ENTRANT_CHECK_ON;
	(*fpu_eip)++;
	ss = base >> 6;
	index = (base >> 3) & 7;
	base &= 7;

	अगर ((mod == 0) && (base == 5))
		offset = 0;	/* No base रेजिस्टर */
	अन्यथा
		offset = REG_(base);

	अगर (index == 4) अणु
		/* No index रेजिस्टर */
		/* A non-zero ss is illegal */
		अगर (ss)
			EXCEPTION(EX_Invalid);
	पूर्ण अन्यथा अणु
		offset += (REG_(index)) << ss;
	पूर्ण

	अगर (mod == 1) अणु
		/* 8 bit चिन्हित displacement */
		दीर्घ displacement;
		RE_ENTRANT_CHECK_OFF;
		FPU_code_access_ok(1);
		FPU_get_user(displacement, (चिन्हित अक्षर __user *)(*fpu_eip));
		offset += displacement;
		RE_ENTRANT_CHECK_ON;
		(*fpu_eip)++;
	पूर्ण अन्यथा अगर (mod == 2 || base == 5) अणु	/* The second condition also has mod==0 */
		/* 32 bit displacement */
		दीर्घ displacement;
		RE_ENTRANT_CHECK_OFF;
		FPU_code_access_ok(4);
		FPU_get_user(displacement, (दीर्घ __user *)(*fpu_eip));
		offset += displacement;
		RE_ENTRANT_CHECK_ON;
		(*fpu_eip) += 4;
	पूर्ण

	वापस offset;
पूर्ण

अटल अचिन्हित दीर्घ vm86_segment(u_अक्षर segment, काष्ठा address *addr)
अणु
	segment--;
#अगर_घोषित PARANOID
	अगर (segment > PREFIX_SS_) अणु
		EXCEPTION(EX_INTERNAL | 0x130);
		math_पात(FPU_info, संक_अंश);
	पूर्ण
#पूर्ण_अगर /* PARANOID */
	addr->selector = VM86_REG_(segment);
	वापस (अचिन्हित दीर्घ)VM86_REG_(segment) << 4;
पूर्ण

/* This should work क्रम 16 and 32 bit रक्षित mode. */
अटल दीर्घ pm_address(u_अक्षर FPU_modrm, u_अक्षर segment,
		       काष्ठा address *addr, दीर्घ offset)
अणु
	काष्ठा desc_काष्ठा descriptor;
	अचिन्हित दीर्घ base_address, limit, address, seg_top;

	segment--;

#अगर_घोषित PARANOID
	/* segment is अचिन्हित, so this also detects अगर segment was 0: */
	अगर (segment > PREFIX_SS_) अणु
		EXCEPTION(EX_INTERNAL | 0x132);
		math_पात(FPU_info, संक_अंश);
	पूर्ण
#पूर्ण_अगर /* PARANOID */

	चयन (segment) अणु
	हाल PREFIX_GS_ - 1:
		/* user gs handling can be lazy, use special accessors */
		addr->selector = get_user_gs(FPU_info->regs);
		अवरोध;
	शेष:
		addr->selector = PM_REG_(segment);
	पूर्ण

	descriptor = FPU_get_ldt_descriptor(addr->selector);
	base_address = seg_get_base(&descriptor);
	address = base_address + offset;
	limit = seg_get_limit(&descriptor) + 1;
	limit *= seg_get_granularity(&descriptor);
	limit += base_address - 1;
	अगर (limit < base_address)
		limit = 0xffffffff;

	अगर (seg_expands_करोwn(&descriptor)) अणु
		अगर (descriptor.g) अणु
			seg_top = 0xffffffff;
		पूर्ण अन्यथा अणु
			seg_top = base_address + (1 << 20);
			अगर (seg_top < base_address)
				seg_top = 0xffffffff;
		पूर्ण
		access_limit =
		    (address <= limit) || (address >= seg_top) ? 0 :
		    ((seg_top - address) >= 255 ? 255 : seg_top - address);
	पूर्ण अन्यथा अणु
		access_limit =
		    (address > limit) || (address < base_address) ? 0 :
		    ((limit - address) >= 254 ? 255 : limit - address + 1);
	पूर्ण
	अगर (seg_execute_only(&descriptor) ||
	    (!seg_writable(&descriptor) && (FPU_modrm & FPU_WRITE_BIT))) अणु
		access_limit = 0;
	पूर्ण
	वापस address;
पूर्ण

/*
       MOD R/M byte:  MOD == 3 has a special use क्रम the FPU
                      SIB byte used अगरf R/M = 100b

       7   6   5   4   3   2   1   0
       .....   .........   .........
        MOD    OPCODE(2)     R/M

       SIB byte

       7   6   5   4   3   2   1   0
       .....   .........   .........
        SS      INDEX        BASE

*/

व्योम __user *FPU_get_address(u_अक्षर FPU_modrm, अचिन्हित दीर्घ *fpu_eip,
			     काष्ठा address *addr, fpu_addr_modes addr_modes)
अणु
	u_अक्षर mod;
	अचिन्हित rm = FPU_modrm & 7;
	दीर्घ *cpu_reg_ptr;
	पूर्णांक address = 0;	/* Initialized just to stop compiler warnings. */

	/* Memory accessed via the cs selector is ग_लिखो रक्षित
	   in `non-segmented' 32 bit रक्षित mode. */
	अगर (!addr_modes.शेष_mode && (FPU_modrm & FPU_WRITE_BIT)
	    && (addr_modes.override.segment == PREFIX_CS_)) अणु
		math_पात(FPU_info, संक_अंश);
	पूर्ण

	addr->selector = FPU_DS;	/* Default, क्रम 32 bit non-segmented mode. */

	mod = (FPU_modrm >> 6) & 3;

	अगर (rm == 4 && mod != 3) अणु
		address = sib(mod, fpu_eip);
	पूर्ण अन्यथा अणु
		cpu_reg_ptr = &REG_(rm);
		चयन (mod) अणु
		हाल 0:
			अगर (rm == 5) अणु
				/* Special हाल: disp32 */
				RE_ENTRANT_CHECK_OFF;
				FPU_code_access_ok(4);
				FPU_get_user(address,
					     (अचिन्हित दीर्घ __user
					      *)(*fpu_eip));
				(*fpu_eip) += 4;
				RE_ENTRANT_CHECK_ON;
				addr->offset = address;
				वापस (व्योम __user *)address;
			पूर्ण अन्यथा अणु
				address = *cpu_reg_ptr;	/* Just वापस the contents
							   of the cpu रेजिस्टर */
				addr->offset = address;
				वापस (व्योम __user *)address;
			पूर्ण
		हाल 1:
			/* 8 bit चिन्हित displacement */
			RE_ENTRANT_CHECK_OFF;
			FPU_code_access_ok(1);
			FPU_get_user(address, (चिन्हित अक्षर __user *)(*fpu_eip));
			RE_ENTRANT_CHECK_ON;
			(*fpu_eip)++;
			अवरोध;
		हाल 2:
			/* 32 bit displacement */
			RE_ENTRANT_CHECK_OFF;
			FPU_code_access_ok(4);
			FPU_get_user(address, (दीर्घ __user *)(*fpu_eip));
			(*fpu_eip) += 4;
			RE_ENTRANT_CHECK_ON;
			अवरोध;
		हाल 3:
			/* Not legal क्रम the FPU */
			EXCEPTION(EX_Invalid);
		पूर्ण
		address += *cpu_reg_ptr;
	पूर्ण

	addr->offset = address;

	चयन (addr_modes.शेष_mode) अणु
	हाल 0:
		अवरोध;
	हाल VM86:
		address += vm86_segment(addr_modes.override.segment, addr);
		अवरोध;
	हाल PM16:
	हाल SEG32:
		address = pm_address(FPU_modrm, addr_modes.override.segment,
				     addr, address);
		अवरोध;
	शेष:
		EXCEPTION(EX_INTERNAL | 0x133);
	पूर्ण

	वापस (व्योम __user *)address;
पूर्ण

व्योम __user *FPU_get_address_16(u_अक्षर FPU_modrm, अचिन्हित दीर्घ *fpu_eip,
				काष्ठा address *addr, fpu_addr_modes addr_modes)
अणु
	u_अक्षर mod;
	अचिन्हित rm = FPU_modrm & 7;
	पूर्णांक address = 0;	/* Default used क्रम mod == 0 */

	/* Memory accessed via the cs selector is ग_लिखो रक्षित
	   in `non-segmented' 32 bit रक्षित mode. */
	अगर (!addr_modes.शेष_mode && (FPU_modrm & FPU_WRITE_BIT)
	    && (addr_modes.override.segment == PREFIX_CS_)) अणु
		math_पात(FPU_info, संक_अंश);
	पूर्ण

	addr->selector = FPU_DS;	/* Default, क्रम 32 bit non-segmented mode. */

	mod = (FPU_modrm >> 6) & 3;

	चयन (mod) अणु
	हाल 0:
		अगर (rm == 6) अणु
			/* Special हाल: disp16 */
			RE_ENTRANT_CHECK_OFF;
			FPU_code_access_ok(2);
			FPU_get_user(address,
				     (अचिन्हित लघु __user *)(*fpu_eip));
			(*fpu_eip) += 2;
			RE_ENTRANT_CHECK_ON;
			जाओ add_segment;
		पूर्ण
		अवरोध;
	हाल 1:
		/* 8 bit चिन्हित displacement */
		RE_ENTRANT_CHECK_OFF;
		FPU_code_access_ok(1);
		FPU_get_user(address, (चिन्हित अक्षर __user *)(*fpu_eip));
		RE_ENTRANT_CHECK_ON;
		(*fpu_eip)++;
		अवरोध;
	हाल 2:
		/* 16 bit displacement */
		RE_ENTRANT_CHECK_OFF;
		FPU_code_access_ok(2);
		FPU_get_user(address, (अचिन्हित लघु __user *)(*fpu_eip));
		(*fpu_eip) += 2;
		RE_ENTRANT_CHECK_ON;
		अवरोध;
	हाल 3:
		/* Not legal क्रम the FPU */
		EXCEPTION(EX_Invalid);
		अवरोध;
	पूर्ण
	चयन (rm) अणु
	हाल 0:
		address += FPU_info->regs->bx + FPU_info->regs->si;
		अवरोध;
	हाल 1:
		address += FPU_info->regs->bx + FPU_info->regs->di;
		अवरोध;
	हाल 2:
		address += FPU_info->regs->bp + FPU_info->regs->si;
		अगर (addr_modes.override.segment == PREFIX_DEFAULT)
			addr_modes.override.segment = PREFIX_SS_;
		अवरोध;
	हाल 3:
		address += FPU_info->regs->bp + FPU_info->regs->di;
		अगर (addr_modes.override.segment == PREFIX_DEFAULT)
			addr_modes.override.segment = PREFIX_SS_;
		अवरोध;
	हाल 4:
		address += FPU_info->regs->si;
		अवरोध;
	हाल 5:
		address += FPU_info->regs->di;
		अवरोध;
	हाल 6:
		address += FPU_info->regs->bp;
		अगर (addr_modes.override.segment == PREFIX_DEFAULT)
			addr_modes.override.segment = PREFIX_SS_;
		अवरोध;
	हाल 7:
		address += FPU_info->regs->bx;
		अवरोध;
	पूर्ण

      add_segment:
	address &= 0xffff;

	addr->offset = address;

	चयन (addr_modes.शेष_mode) अणु
	हाल 0:
		अवरोध;
	हाल VM86:
		address += vm86_segment(addr_modes.override.segment, addr);
		अवरोध;
	हाल PM16:
	हाल SEG32:
		address = pm_address(FPU_modrm, addr_modes.override.segment,
				     addr, address);
		अवरोध;
	शेष:
		EXCEPTION(EX_INTERNAL | 0x131);
	पूर्ण

	वापस (व्योम __user *)address;
पूर्ण
