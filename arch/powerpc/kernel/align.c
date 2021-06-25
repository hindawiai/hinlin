<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* align.c - handle alignment exceptions क्रम the Power PC.
 *
 * Copyright (c) 1996 Paul Mackerras <paulus@cs.anu.edu.au>
 * Copyright (c) 1998-1999 TiVo, Inc.
 *   PowerPC 403GCX modअगरications.
 * Copyright (c) 1999 Grant Erickson <grant@lcse.umn.edu>
 *   PowerPC 403GCX/405GP modअगरications.
 * Copyright (c) 2001-2002 PPC64 team, IBM Corp
 *   64-bit and Power4 support
 * Copyright (c) 2005 Benjamin Herrenschmidt, IBM Corp
 *                    <benh@kernel.crashing.org>
 *   Merge ppc32 and ppc64 implementations
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/emulated_ops.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/disassemble.h>
#समावेश <यंत्र/cpu_has_feature.h>
#समावेश <यंत्र/sstep.h>
#समावेश <यंत्र/inst.h>

काष्ठा aligninfo अणु
	अचिन्हित अक्षर len;
	अचिन्हित अक्षर flags;
पूर्ण;


#घोषणा INVALID	अणु 0, 0 पूर्ण

/* Bits in the flags field */
#घोषणा LD	0	/* load */
#घोषणा ST	1	/* store */
#घोषणा SE	2	/* sign-extend value, or FP ld/st as word */
#घोषणा SW	0x20	/* byte swap */
#घोषणा E4	0x40	/* SPE endianness is word */
#घोषणा E8	0x80	/* SPE endianness is द्विगुन word */

#अगर_घोषित CONFIG_SPE

अटल काष्ठा aligninfo spe_aligninfo[32] = अणु
	अणु 8, LD+E8 पूर्ण,		/* 0 00 00: evldd[x] */
	अणु 8, LD+E4 पूर्ण,		/* 0 00 01: evldw[x] */
	अणु 8, LD पूर्ण,		/* 0 00 10: evldh[x] */
	INVALID,		/* 0 00 11 */
	अणु 2, LD पूर्ण,		/* 0 01 00: evlhhesplat[x] */
	INVALID,		/* 0 01 01 */
	अणु 2, LD पूर्ण,		/* 0 01 10: evlhhousplat[x] */
	अणु 2, LD+SE पूर्ण,		/* 0 01 11: evlhhossplat[x] */
	अणु 4, LD पूर्ण,		/* 0 10 00: evlwhe[x] */
	INVALID,		/* 0 10 01 */
	अणु 4, LD पूर्ण,		/* 0 10 10: evlwhou[x] */
	अणु 4, LD+SE पूर्ण,		/* 0 10 11: evlwhos[x] */
	अणु 4, LD+E4 पूर्ण,		/* 0 11 00: evlwwsplat[x] */
	INVALID,		/* 0 11 01 */
	अणु 4, LD पूर्ण,		/* 0 11 10: evlwhsplat[x] */
	INVALID,		/* 0 11 11 */

	अणु 8, ST+E8 पूर्ण,		/* 1 00 00: evstdd[x] */
	अणु 8, ST+E4 पूर्ण,		/* 1 00 01: evstdw[x] */
	अणु 8, ST पूर्ण,		/* 1 00 10: evstdh[x] */
	INVALID,		/* 1 00 11 */
	INVALID,		/* 1 01 00 */
	INVALID,		/* 1 01 01 */
	INVALID,		/* 1 01 10 */
	INVALID,		/* 1 01 11 */
	अणु 4, ST पूर्ण,		/* 1 10 00: evstwhe[x] */
	INVALID,		/* 1 10 01 */
	अणु 4, ST पूर्ण,		/* 1 10 10: evstwho[x] */
	INVALID,		/* 1 10 11 */
	अणु 4, ST+E4 पूर्ण,		/* 1 11 00: evstwwe[x] */
	INVALID,		/* 1 11 01 */
	अणु 4, ST+E4 पूर्ण,		/* 1 11 10: evstwwo[x] */
	INVALID,		/* 1 11 11 */
पूर्ण;

#घोषणा	EVLDD		0x00
#घोषणा	EVLDW		0x01
#घोषणा	EVLDH		0x02
#घोषणा	EVLHHESPLAT	0x04
#घोषणा	EVLHHOUSPLAT	0x06
#घोषणा	EVLHHOSSPLAT	0x07
#घोषणा	EVLWHE		0x08
#घोषणा	EVLWHOU		0x0A
#घोषणा	EVLWHOS		0x0B
#घोषणा	EVLWWSPLAT	0x0C
#घोषणा	EVLWHSPLAT	0x0E
#घोषणा	EVSTDD		0x10
#घोषणा	EVSTDW		0x11
#घोषणा	EVSTDH		0x12
#घोषणा	EVSTWHE		0x18
#घोषणा	EVSTWHO		0x1A
#घोषणा	EVSTWWE		0x1C
#घोषणा	EVSTWWO		0x1E

/*
 * Emulate SPE loads and stores.
 * Only Book-E has these inकाष्ठाions, and it करोes true little-endian,
 * so we करोn't need the address swizzling.
 */
अटल पूर्णांक emulate_spe(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक reg,
		       काष्ठा ppc_inst ppc_instr)
अणु
	जोड़ अणु
		u64 ll;
		u32 w[2];
		u16 h[4];
		u8 v[8];
	पूर्ण data, temp;
	अचिन्हित अक्षर __user *p, *addr;
	अचिन्हित दीर्घ *evr = &current->thपढ़ो.evr[reg];
	अचिन्हित पूर्णांक nb, flags, instr;

	instr = ppc_inst_val(ppc_instr);
	instr = (instr >> 1) & 0x1f;

	/* DAR has the opeअक्रम effective address */
	addr = (अचिन्हित अक्षर __user *)regs->dar;

	nb = spe_aligninfo[instr].len;
	flags = spe_aligninfo[instr].flags;

	/* userland only */
	अगर (unlikely(!user_mode(regs)))
		वापस 0;

	flush_spe_to_thपढ़ो(current);

	/* If we are loading, get the data from user space, अन्यथा
	 * get it from रेजिस्टर values
	 */
	अगर (flags & ST) अणु
		data.ll = 0;
		चयन (instr) अणु
		हाल EVSTDD:
		हाल EVSTDW:
		हाल EVSTDH:
			data.w[0] = *evr;
			data.w[1] = regs->gpr[reg];
			अवरोध;
		हाल EVSTWHE:
			data.h[2] = *evr >> 16;
			data.h[3] = regs->gpr[reg] >> 16;
			अवरोध;
		हाल EVSTWHO:
			data.h[2] = *evr & 0xffff;
			data.h[3] = regs->gpr[reg] & 0xffff;
			अवरोध;
		हाल EVSTWWE:
			data.w[1] = *evr;
			अवरोध;
		हाल EVSTWWO:
			data.w[1] = regs->gpr[reg];
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		temp.ll = data.ll = 0;
		p = addr;

		अगर (!user_पढ़ो_access_begin(addr, nb))
			वापस -EFAULT;

		चयन (nb) अणु
		हाल 8:
			unsafe_get_user(temp.v[0], p++, Efault_पढ़ो);
			unsafe_get_user(temp.v[1], p++, Efault_पढ़ो);
			unsafe_get_user(temp.v[2], p++, Efault_पढ़ो);
			unsafe_get_user(temp.v[3], p++, Efault_पढ़ो);
			fallthrough;
		हाल 4:
			unsafe_get_user(temp.v[4], p++, Efault_पढ़ो);
			unsafe_get_user(temp.v[5], p++, Efault_पढ़ो);
			fallthrough;
		हाल 2:
			unsafe_get_user(temp.v[6], p++, Efault_पढ़ो);
			unsafe_get_user(temp.v[7], p++, Efault_पढ़ो);
		पूर्ण
		user_पढ़ो_access_end();

		चयन (instr) अणु
		हाल EVLDD:
		हाल EVLDW:
		हाल EVLDH:
			data.ll = temp.ll;
			अवरोध;
		हाल EVLHHESPLAT:
			data.h[0] = temp.h[3];
			data.h[2] = temp.h[3];
			अवरोध;
		हाल EVLHHOUSPLAT:
		हाल EVLHHOSSPLAT:
			data.h[1] = temp.h[3];
			data.h[3] = temp.h[3];
			अवरोध;
		हाल EVLWHE:
			data.h[0] = temp.h[2];
			data.h[2] = temp.h[3];
			अवरोध;
		हाल EVLWHOU:
		हाल EVLWHOS:
			data.h[1] = temp.h[2];
			data.h[3] = temp.h[3];
			अवरोध;
		हाल EVLWWSPLAT:
			data.w[0] = temp.w[1];
			data.w[1] = temp.w[1];
			अवरोध;
		हाल EVLWHSPLAT:
			data.h[0] = temp.h[2];
			data.h[1] = temp.h[2];
			data.h[2] = temp.h[3];
			data.h[3] = temp.h[3];
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (flags & SW) अणु
		चयन (flags & 0xf0) अणु
		हाल E8:
			data.ll = swab64(data.ll);
			अवरोध;
		हाल E4:
			data.w[0] = swab32(data.w[0]);
			data.w[1] = swab32(data.w[1]);
			अवरोध;
		/* Its half word endian */
		शेष:
			data.h[0] = swab16(data.h[0]);
			data.h[1] = swab16(data.h[1]);
			data.h[2] = swab16(data.h[2]);
			data.h[3] = swab16(data.h[3]);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (flags & SE) अणु
		data.w[0] = (s16)data.h[1];
		data.w[1] = (s16)data.h[3];
	पूर्ण

	/* Store result to memory or update रेजिस्टरs */
	अगर (flags & ST) अणु
		p = addr;

		अगर (!user_ग_लिखो_access_begin(addr, nb))
			वापस -EFAULT;

		चयन (nb) अणु
		हाल 8:
			unsafe_put_user(data.v[0], p++, Efault_ग_लिखो);
			unsafe_put_user(data.v[1], p++, Efault_ग_लिखो);
			unsafe_put_user(data.v[2], p++, Efault_ग_लिखो);
			unsafe_put_user(data.v[3], p++, Efault_ग_लिखो);
			fallthrough;
		हाल 4:
			unsafe_put_user(data.v[4], p++, Efault_ग_लिखो);
			unsafe_put_user(data.v[5], p++, Efault_ग_लिखो);
			fallthrough;
		हाल 2:
			unsafe_put_user(data.v[6], p++, Efault_ग_लिखो);
			unsafe_put_user(data.v[7], p++, Efault_ग_लिखो);
		पूर्ण
		user_ग_लिखो_access_end();
	पूर्ण अन्यथा अणु
		*evr = data.w[0];
		regs->gpr[reg] = data.w[1];
	पूर्ण

	वापस 1;

Efault_पढ़ो:
	user_पढ़ो_access_end();
	वापस -EFAULT;

Efault_ग_लिखो:
	user_ग_लिखो_access_end();
	वापस -EFAULT;
पूर्ण
#पूर्ण_अगर /* CONFIG_SPE */

/*
 * Called on alignment exception. Attempts to fixup
 *
 * Return 1 on success
 * Return 0 अगर unable to handle the पूर्णांकerrupt
 * Return -EFAULT अगर data address is bad
 * Other negative वापस values indicate that the inकाष्ठाion can't
 * be emulated, and the process should be given a SIGBUS.
 */

पूर्णांक fix_alignment(काष्ठा pt_regs *regs)
अणु
	काष्ठा ppc_inst instr;
	काष्ठा inकाष्ठाion_op op;
	पूर्णांक r, type;

	अगर (is_kernel_addr(regs->nip))
		r = copy_inst_from_kernel_nofault(&instr, (व्योम *)regs->nip);
	अन्यथा
		r = __get_user_instr(instr, (व्योम __user *)regs->nip);

	अगर (unlikely(r))
		वापस -EFAULT;
	अगर ((regs->msr & MSR_LE) != (MSR_KERNEL & MSR_LE)) अणु
		/* We करोn't handle PPC little-endian any more... */
		अगर (cpu_has_feature(CPU_FTR_PPC_LE))
			वापस -EIO;
		instr = ppc_inst_swab(instr);
	पूर्ण

#अगर_घोषित CONFIG_SPE
	अगर (ppc_inst_primary_opcode(instr) == 0x4) अणु
		पूर्णांक reg = (ppc_inst_val(instr) >> 21) & 0x1f;
		PPC_WARN_ALIGNMENT(spe, regs);
		वापस emulate_spe(regs, reg, instr);
	पूर्ण
#पूर्ण_अगर


	/*
	 * ISA 3.0 (such as P9) copy, copy_first, paste and paste_last alignment
	 * check.
	 *
	 * Send a SIGBUS to the process that caused the fault.
	 *
	 * We करो not emulate these because paste may contain additional metadata
	 * when pasting to a co-processor. Furthermore, paste_last is the
	 * synchronisation poपूर्णांक क्रम preceding copy/paste sequences.
	 */
	अगर ((ppc_inst_val(instr) & 0xfc0006fe) == (PPC_INST_COPY & 0xfc0006fe))
		वापस -EIO;

	r = analyse_instr(&op, regs, instr);
	अगर (r < 0)
		वापस -EINVAL;

	type = GETTYPE(op.type);
	अगर (!OP_IS_LOAD_STORE(type)) अणु
		अगर (op.type != CACHEOP + DCBZ)
			वापस -EINVAL;
		PPC_WARN_ALIGNMENT(dcbz, regs);
		r = emulate_dcbz(op.ea, regs);
	पूर्ण अन्यथा अणु
		अगर (type == LARX || type == STCX)
			वापस -EIO;
		PPC_WARN_ALIGNMENT(unaligned, regs);
		r = emulate_loadstore(regs, &op);
	पूर्ण

	अगर (!r)
		वापस 1;
	वापस r;
पूर्ण
