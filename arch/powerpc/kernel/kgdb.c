<शैली गुरु>
/*
 * PowerPC backend to the KGDB stub.
 *
 * 1998 (c) Michael AK Tesch (tesch@cs.wisc.edu)
 * Copyright (C) 2003 Timesys Corporation.
 * Copyright (C) 2004-2006 MontaVista Software, Inc.
 * PPC64 Mods (C) 2005 Frank Rowand (frowand@mvista.com)
 * PPC32 support restored by Vitaly Wool <vwool@ru.mvista.com> and
 * Sergei Shtylyov <sshtylyov@ru.mvista.com>
 * Copyright (C) 2007-2008 Wind River Systems, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program as licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/smp.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/kdebug.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/inst.h>

/*
 * This table contains the mapping between PowerPC hardware trap types, and
 * संकेतs, which are primarily what GDB understands.  GDB and the kernel
 * करोn't always agree on values, so we use स्थिरants taken from gdb-6.2.
 */
अटल काष्ठा hard_trap_info
अणु
	अचिन्हित पूर्णांक tt;		/* Trap type code क्रम घातerpc */
	अचिन्हित अक्षर signo;		/* Signal that we map this trap पूर्णांकo */
पूर्ण hard_trap_info[] = अणु
	अणु 0x0100, 0x02 /* संक_विघ्न */  पूर्ण,		/* प्रणाली reset */
	अणु 0x0200, 0x0b /* संक_अंश */ पूर्ण,		/* machine check */
	अणु 0x0300, 0x0b /* संक_अंश */ पूर्ण,		/* data access */
	अणु 0x0400, 0x0b /* संक_अंश */ पूर्ण,		/* inकाष्ठाion access */
	अणु 0x0500, 0x02 /* संक_विघ्न */  पूर्ण,		/* बाह्यal पूर्णांकerrupt */
	अणु 0x0600, 0x0a /* SIGBUS */  पूर्ण,		/* alignment */
	अणु 0x0700, 0x05 /* SIGTRAP */ पूर्ण,		/* program check */
	अणु 0x0800, 0x08 /* संक_भ_त्रुटि */  पूर्ण,		/* fp unavailable */
	अणु 0x0900, 0x0e /* SIGALRM */ पूर्ण,		/* decrementer */
	अणु 0x0c00, 0x14 /* SIGCHLD */ पूर्ण,		/* प्रणाली call */
#अगर defined(CONFIG_40x) || defined(CONFIG_BOOKE)
	अणु 0x2002, 0x05 /* SIGTRAP */ पूर्ण,		/* debug */
#अगर defined(CONFIG_FSL_BOOKE)
	अणु 0x2010, 0x08 /* संक_भ_त्रुटि */  पूर्ण,		/* spe unavailable */
	अणु 0x2020, 0x08 /* संक_भ_त्रुटि */  पूर्ण,		/* spe unavailable */
	अणु 0x2030, 0x08 /* संक_भ_त्रुटि */  पूर्ण,		/* spe fp data */
	अणु 0x2040, 0x08 /* संक_भ_त्रुटि */  पूर्ण,		/* spe fp data */
	अणु 0x2050, 0x08 /* संक_भ_त्रुटि */  पूर्ण,		/* spe fp round */
	अणु 0x2060, 0x0e /* संक_अवैध */  पूर्ण,		/* perक्रमmance monitor */
	अणु 0x2900, 0x08 /* संक_भ_त्रुटि */  पूर्ण,		/* apu unavailable */
	अणु 0x3100, 0x0e /* SIGALRM */ पूर्ण,		/* fixed पूर्णांकerval समयr */
	अणु 0x3200, 0x02 /* संक_विघ्न */  पूर्ण, 	/* watchकरोg */
#अन्यथा /* ! CONFIG_FSL_BOOKE */
	अणु 0x1000, 0x0e /* SIGALRM */ पूर्ण,		/* prog पूर्णांकerval समयr */
	अणु 0x1010, 0x0e /* SIGALRM */ पूर्ण,		/* fixed पूर्णांकerval समयr */
	अणु 0x1020, 0x02 /* संक_विघ्न */  पूर्ण, 	/* watchकरोg */
	अणु 0x2010, 0x08 /* संक_भ_त्रुटि */  पूर्ण,		/* fp unavailable */
	अणु 0x2020, 0x08 /* संक_भ_त्रुटि */  पूर्ण,		/* ap unavailable */
#पूर्ण_अगर
#अन्यथा /* ! (defined(CONFIG_40x) || defined(CONFIG_BOOKE)) */
	अणु 0x0d00, 0x05 /* SIGTRAP */ पूर्ण,		/* single-step */
#अगर defined(CONFIG_PPC_8xx)
	अणु 0x1000, 0x04 /* संक_अवैध */  पूर्ण,		/* software emulation */
#अन्यथा /* ! CONFIG_PPC_8xx */
	अणु 0x0f00, 0x04 /* संक_अवैध */  पूर्ण,		/* perक्रमmance monitor */
	अणु 0x0f20, 0x08 /* संक_भ_त्रुटि */  पूर्ण,		/* altivec unavailable */
	अणु 0x1300, 0x05 /* SIGTRAP */ पूर्ण, 	/* inकाष्ठाion address अवरोध */
#अगर defined(CONFIG_PPC64)
	अणु 0x1200, 0x05 /* संक_अवैध */  पूर्ण,		/* प्रणाली error */
	अणु 0x1500, 0x04 /* संक_अवैध */  पूर्ण,		/* soft patch */
	अणु 0x1600, 0x04 /* संक_अवैध */  पूर्ण,		/* मुख्यtenance */
	अणु 0x1700, 0x08 /* संक_भ_त्रुटि */  पूर्ण,		/* altivec assist */
	अणु 0x1800, 0x04 /* संक_अवैध */  पूर्ण,		/* thermal */
#अन्यथा /* ! CONFIG_PPC64 */
	अणु 0x1400, 0x02 /* संक_विघ्न */  पूर्ण,		/* SMI */
	अणु 0x1600, 0x08 /* संक_भ_त्रुटि */  पूर्ण,		/* altivec assist */
	अणु 0x1700, 0x04 /* संक_अवैध */  पूर्ण,		/* TAU */
	अणु 0x2000, 0x05 /* SIGTRAP */ पूर्ण,		/* run mode */
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर
	अणु 0x0000, 0x00 पूर्ण			/* Must be last */
पूर्ण;

अटल पूर्णांक computeSignal(अचिन्हित पूर्णांक tt)
अणु
	काष्ठा hard_trap_info *ht;

	क्रम (ht = hard_trap_info; ht->tt && ht->signo; ht++)
		अगर (ht->tt == tt)
			वापस ht->signo;

	वापस SIGHUP;		/* शेष क्रम things we करोn't know about */
पूर्ण

/**
 *
 *	kgdb_skipexception - Bail out of KGDB when we've been triggered.
 *	@exception: Exception vector number
 *	@regs: Current &काष्ठा pt_regs.
 *
 *	On some architectures we need to skip a अवरोधpoपूर्णांक exception when
 *	it occurs after a अवरोधpoपूर्णांक has been हटाओd.
 *
 */
पूर्णांक kgdb_skipexception(पूर्णांक exception, काष्ठा pt_regs *regs)
अणु
	वापस kgdb_isहटाओdअवरोध(regs->nip);
पूर्ण

अटल पूर्णांक kgdb_debugger_ipi(काष्ठा pt_regs *regs)
अणु
	kgdb_nmicallback(raw_smp_processor_id(), regs);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम kgdb_roundup_cpus(व्योम)
अणु
	smp_send_debugger_अवरोध();
पूर्ण
#पूर्ण_अगर

/* KGDB functions to use existing PowerPC64 hooks. */
अटल पूर्णांक kgdb_debugger(काष्ठा pt_regs *regs)
अणु
	वापस !kgdb_handle_exception(1, computeSignal(TRAP(regs)),
				      DIE_OOPS, regs);
पूर्ण

अटल पूर्णांक kgdb_handle_अवरोधpoपूर्णांक(काष्ठा pt_regs *regs)
अणु
	अगर (user_mode(regs))
		वापस 0;

	अगर (kgdb_handle_exception(1, SIGTRAP, 0, regs) != 0)
		वापस 0;

	अगर (*(u32 *)regs->nip == BREAK_INSTR)
		regs->nip += BREAK_INSTR_SIZE;

	वापस 1;
पूर्ण

अटल पूर्णांक kgdb_singlestep(काष्ठा pt_regs *regs)
अणु
	अगर (user_mode(regs))
		वापस 0;

	kgdb_handle_exception(0, SIGTRAP, 0, regs);

	वापस 1;
पूर्ण

अटल पूर्णांक kgdb_iabr_match(काष्ठा pt_regs *regs)
अणु
	अगर (user_mode(regs))
		वापस 0;

	अगर (kgdb_handle_exception(0, computeSignal(TRAP(regs)), 0, regs) != 0)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक kgdb_अवरोध_match(काष्ठा pt_regs *regs)
अणु
	अगर (user_mode(regs))
		वापस 0;

	अगर (kgdb_handle_exception(0, computeSignal(TRAP(regs)), 0, regs) != 0)
		वापस 0;
	वापस 1;
पूर्ण

#घोषणा PACK64(ptr, src) करो अणु *(ptr++) = (src); पूर्ण जबतक (0)

#घोषणा PACK32(ptr, src) करो अणु          \
	u32 *ptr32;                   \
	ptr32 = (u32 *)ptr;           \
	*(ptr32++) = (src);           \
	ptr = (अचिन्हित दीर्घ *)ptr32; \
	पूर्ण जबतक (0)

व्योम sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा task_काष्ठा *p)
अणु
	काष्ठा pt_regs *regs = (काष्ठा pt_regs *)(p->thपढ़ो.ksp +
						  STACK_FRAME_OVERHEAD);
	अचिन्हित दीर्घ *ptr = gdb_regs;
	पूर्णांक reg;

	स_रखो(gdb_regs, 0, NUMREGBYTES);

	/* Regs GPR0-2 */
	क्रम (reg = 0; reg < 3; reg++)
		PACK64(ptr, regs->gpr[reg]);

	/* Regs GPR3-13 are caller saved, not in regs->gpr[] */
	ptr += 11;

	/* Regs GPR14-31 */
	क्रम (reg = 14; reg < 32; reg++)
		PACK64(ptr, regs->gpr[reg]);

#अगर_घोषित CONFIG_FSL_BOOKE
#अगर_घोषित CONFIG_SPE
	क्रम (reg = 0; reg < 32; reg++)
		PACK64(ptr, p->thपढ़ो.evr[reg]);
#अन्यथा
	ptr += 32;
#पूर्ण_अगर
#अन्यथा
	/* fp रेजिस्टरs not used by kernel, leave zero */
	ptr += 32 * 8 / माप(दीर्घ);
#पूर्ण_अगर

	PACK64(ptr, regs->nip);
	PACK64(ptr, regs->msr);
	PACK32(ptr, regs->ccr);
	PACK64(ptr, regs->link);
	PACK64(ptr, regs->ctr);
	PACK32(ptr, regs->xer);

	BUG_ON((अचिन्हित दीर्घ)ptr >
	       (अचिन्हित दीर्घ)(((व्योम *)gdb_regs) + NUMREGBYTES));
पूर्ण

#घोषणा GDB_SIZखातापूर्ण_REG माप(अचिन्हित दीर्घ)
#घोषणा GDB_SIZखातापूर्ण_REG_U32 माप(u32)

#अगर_घोषित CONFIG_FSL_BOOKE
#घोषणा GDB_SIZखातापूर्ण_FLOAT_REG माप(अचिन्हित दीर्घ)
#अन्यथा
#घोषणा GDB_SIZखातापूर्ण_FLOAT_REG माप(u64)
#पूर्ण_अगर

काष्ठा dbg_reg_def_t dbg_reg_def[DBG_MAX_REG_NUM] =
अणु
	अणु "r0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[0]) पूर्ण,
	अणु "r1", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[1]) पूर्ण,
	अणु "r2", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[2]) पूर्ण,
	अणु "r3", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[3]) पूर्ण,
	अणु "r4", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[4]) पूर्ण,
	अणु "r5", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[5]) पूर्ण,
	अणु "r6", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[6]) पूर्ण,
	अणु "r7", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[7]) पूर्ण,
	अणु "r8", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[8]) पूर्ण,
	अणु "r9", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[9]) पूर्ण,
	अणु "r10", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[10]) पूर्ण,
	अणु "r11", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[11]) पूर्ण,
	अणु "r12", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[12]) पूर्ण,
	अणु "r13", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[13]) पूर्ण,
	अणु "r14", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[14]) पूर्ण,
	अणु "r15", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[15]) पूर्ण,
	अणु "r16", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[16]) पूर्ण,
	अणु "r17", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[17]) पूर्ण,
	अणु "r18", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[18]) पूर्ण,
	अणु "r19", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[19]) पूर्ण,
	अणु "r20", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[20]) पूर्ण,
	अणु "r21", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[21]) पूर्ण,
	अणु "r22", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[22]) पूर्ण,
	अणु "r23", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[23]) पूर्ण,
	अणु "r24", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[24]) पूर्ण,
	अणु "r25", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[25]) पूर्ण,
	अणु "r26", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[26]) पूर्ण,
	अणु "r27", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[27]) पूर्ण,
	अणु "r28", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[28]) पूर्ण,
	अणु "r29", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[29]) पूर्ण,
	अणु "r30", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[30]) पूर्ण,
	अणु "r31", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gpr[31]) पूर्ण,

	अणु "f0", GDB_SIZखातापूर्ण_FLOAT_REG, 0 पूर्ण,
	अणु "f1", GDB_SIZखातापूर्ण_FLOAT_REG, 1 पूर्ण,
	अणु "f2", GDB_SIZखातापूर्ण_FLOAT_REG, 2 पूर्ण,
	अणु "f3", GDB_SIZखातापूर्ण_FLOAT_REG, 3 पूर्ण,
	अणु "f4", GDB_SIZखातापूर्ण_FLOAT_REG, 4 पूर्ण,
	अणु "f5", GDB_SIZखातापूर्ण_FLOAT_REG, 5 पूर्ण,
	अणु "f6", GDB_SIZखातापूर्ण_FLOAT_REG, 6 पूर्ण,
	अणु "f7", GDB_SIZखातापूर्ण_FLOAT_REG, 7 पूर्ण,
	अणु "f8", GDB_SIZखातापूर्ण_FLOAT_REG, 8 पूर्ण,
	अणु "f9", GDB_SIZखातापूर्ण_FLOAT_REG, 9 पूर्ण,
	अणु "f10", GDB_SIZखातापूर्ण_FLOAT_REG, 10 पूर्ण,
	अणु "f11", GDB_SIZखातापूर्ण_FLOAT_REG, 11 पूर्ण,
	अणु "f12", GDB_SIZखातापूर्ण_FLOAT_REG, 12 पूर्ण,
	अणु "f13", GDB_SIZखातापूर्ण_FLOAT_REG, 13 पूर्ण,
	अणु "f14", GDB_SIZखातापूर्ण_FLOAT_REG, 14 पूर्ण,
	अणु "f15", GDB_SIZखातापूर्ण_FLOAT_REG, 15 पूर्ण,
	अणु "f16", GDB_SIZखातापूर्ण_FLOAT_REG, 16 पूर्ण,
	अणु "f17", GDB_SIZखातापूर्ण_FLOAT_REG, 17 पूर्ण,
	अणु "f18", GDB_SIZखातापूर्ण_FLOAT_REG, 18 पूर्ण,
	अणु "f19", GDB_SIZखातापूर्ण_FLOAT_REG, 19 पूर्ण,
	अणु "f20", GDB_SIZखातापूर्ण_FLOAT_REG, 20 पूर्ण,
	अणु "f21", GDB_SIZखातापूर्ण_FLOAT_REG, 21 पूर्ण,
	अणु "f22", GDB_SIZखातापूर्ण_FLOAT_REG, 22 पूर्ण,
	अणु "f23", GDB_SIZखातापूर्ण_FLOAT_REG, 23 पूर्ण,
	अणु "f24", GDB_SIZखातापूर्ण_FLOAT_REG, 24 पूर्ण,
	अणु "f25", GDB_SIZखातापूर्ण_FLOAT_REG, 25 पूर्ण,
	अणु "f26", GDB_SIZखातापूर्ण_FLOAT_REG, 26 पूर्ण,
	अणु "f27", GDB_SIZखातापूर्ण_FLOAT_REG, 27 पूर्ण,
	अणु "f28", GDB_SIZखातापूर्ण_FLOAT_REG, 28 पूर्ण,
	अणु "f29", GDB_SIZखातापूर्ण_FLOAT_REG, 29 पूर्ण,
	अणु "f30", GDB_SIZखातापूर्ण_FLOAT_REG, 30 पूर्ण,
	अणु "f31", GDB_SIZखातापूर्ण_FLOAT_REG, 31 पूर्ण,

	अणु "pc", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, nip) पूर्ण,
	अणु "msr", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, msr) पूर्ण,
	अणु "cr", GDB_SIZखातापूर्ण_REG_U32, दुरत्व(काष्ठा pt_regs, ccr) पूर्ण,
	अणु "lr", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, link) पूर्ण,
	अणु "ctr", GDB_SIZखातापूर्ण_REG_U32, दुरत्व(काष्ठा pt_regs, ctr) पूर्ण,
	अणु "xer", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, xer) पूर्ण,
पूर्ण;

अक्षर *dbg_get_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस शून्य;

	अगर (regno < 32 || regno >= 64)
		/* First 0 -> 31 gpr रेजिस्टरs*/
		/* pc, msr, ls... रेजिस्टरs 64 -> 69 */
		स_नकल(mem, (व्योम *)regs + dbg_reg_def[regno].offset,
				dbg_reg_def[regno].size);

	अगर (regno >= 32 && regno < 64) अणु
		/* FP रेजिस्टरs 32 -> 63 */
#अगर defined(CONFIG_FSL_BOOKE) && defined(CONFIG_SPE)
		अगर (current)
			स_नकल(mem, &current->thपढ़ो.evr[regno-32],
					dbg_reg_def[regno].size);
#अन्यथा
		/* fp रेजिस्टरs not used by kernel, leave zero */
		स_रखो(mem, 0, dbg_reg_def[regno].size);
#पूर्ण_अगर
	पूर्ण

	वापस dbg_reg_def[regno].name;
पूर्ण

पूर्णांक dbg_set_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस -EINVAL;

	अगर (regno < 32 || regno >= 64)
		/* First 0 -> 31 gpr रेजिस्टरs*/
		/* pc, msr, ls... रेजिस्टरs 64 -> 69 */
		स_नकल((व्योम *)regs + dbg_reg_def[regno].offset, mem,
				dbg_reg_def[regno].size);

	अगर (regno >= 32 && regno < 64) अणु
		/* FP रेजिस्टरs 32 -> 63 */
#अगर defined(CONFIG_FSL_BOOKE) && defined(CONFIG_SPE)
		स_नकल(&current->thपढ़ो.evr[regno-32], mem,
				dbg_reg_def[regno].size);
#अन्यथा
		/* fp रेजिस्टरs not used by kernel, leave zero */
		वापस 0;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc)
अणु
	regs->nip = pc;
पूर्ण

/*
 * This function करोes PowerPC specअगरic processing क्रम पूर्णांकerfacing to gdb.
 */
पूर्णांक kgdb_arch_handle_exception(पूर्णांक vector, पूर्णांक signo, पूर्णांक err_code,
			       अक्षर *remcom_in_buffer, अक्षर *remcom_out_buffer,
			       काष्ठा pt_regs *linux_regs)
अणु
	अक्षर *ptr = &remcom_in_buffer[1];
	अचिन्हित दीर्घ addr;

	चयन (remcom_in_buffer[0]) अणु
		/*
		 * sAA..AA   Step one inकाष्ठाion from AA..AA
		 * This will वापस an error to gdb ..
		 */
	हाल 's':
	हाल 'c':
		/* handle the optional parameter */
		अगर (kgdb_hex2दीर्घ(&ptr, &addr))
			linux_regs->nip = addr;

		atomic_set(&kgdb_cpu_करोing_single_step, -1);
		/* set the trace bit अगर we're stepping */
		अगर (remcom_in_buffer[0] == 's') अणु
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
			mtspr(SPRN_DBCR0,
			      mfspr(SPRN_DBCR0) | DBCR0_IC | DBCR0_IDM);
			linux_regs->msr |= MSR_DE;
#अन्यथा
			linux_regs->msr |= MSR_SE;
#पूर्ण_अगर
			atomic_set(&kgdb_cpu_करोing_single_step,
				   raw_smp_processor_id());
		पूर्ण
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक kgdb_arch_set_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक instr;
	काष्ठा ppc_inst *addr = (काष्ठा ppc_inst *)bpt->bpt_addr;

	err = get_kernel_nofault(instr, (अचिन्हित *) addr);
	अगर (err)
		वापस err;

	err = patch_inकाष्ठाion(addr, ppc_inst(BREAK_INSTR));
	अगर (err)
		वापस -EFAULT;

	*(अचिन्हित पूर्णांक *)bpt->saved_instr = instr;

	वापस 0;
पूर्ण

पूर्णांक kgdb_arch_हटाओ_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक instr = *(अचिन्हित पूर्णांक *)bpt->saved_instr;
	काष्ठा ppc_inst *addr = (काष्ठा ppc_inst *)bpt->bpt_addr;

	err = patch_inकाष्ठाion(addr, ppc_inst(instr));
	अगर (err)
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * Global data
 */
स्थिर काष्ठा kgdb_arch arch_kgdb_ops;

अटल पूर्णांक kgdb_not_implemented(काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण

अटल व्योम *old__debugger_ipi;
अटल व्योम *old__debugger;
अटल व्योम *old__debugger_bpt;
अटल व्योम *old__debugger_sstep;
अटल व्योम *old__debugger_iabr_match;
अटल व्योम *old__debugger_अवरोध_match;
अटल व्योम *old__debugger_fault_handler;

पूर्णांक kgdb_arch_init(व्योम)
अणु
	old__debugger_ipi = __debugger_ipi;
	old__debugger = __debugger;
	old__debugger_bpt = __debugger_bpt;
	old__debugger_sstep = __debugger_sstep;
	old__debugger_iabr_match = __debugger_iabr_match;
	old__debugger_अवरोध_match = __debugger_अवरोध_match;
	old__debugger_fault_handler = __debugger_fault_handler;

	__debugger_ipi = kgdb_debugger_ipi;
	__debugger = kgdb_debugger;
	__debugger_bpt = kgdb_handle_अवरोधpoपूर्णांक;
	__debugger_sstep = kgdb_singlestep;
	__debugger_iabr_match = kgdb_iabr_match;
	__debugger_अवरोध_match = kgdb_अवरोध_match;
	__debugger_fault_handler = kgdb_not_implemented;

	वापस 0;
पूर्ण

व्योम kgdb_arch_निकास(व्योम)
अणु
	__debugger_ipi = old__debugger_ipi;
	__debugger = old__debugger;
	__debugger_bpt = old__debugger_bpt;
	__debugger_sstep = old__debugger_sstep;
	__debugger_iabr_match = old__debugger_iabr_match;
	__debugger_अवरोध_match = old__debugger_अवरोध_match;
	__debugger_fault_handler = old__debugger_fault_handler;
पूर्ण
