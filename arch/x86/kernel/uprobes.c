<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * User-space Probes (UProbes) क्रम x86
 *
 * Copyright (C) IBM Corporation, 2008-2011
 * Authors:
 *	Srikar Dronamraju
 *	Jim Keniston
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/kdebug.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/mmu_context.h>

/* Post-execution fixups. */

/* Adjust IP back to vicinity of actual insn */
#घोषणा UPROBE_FIX_IP		0x01

/* Adjust the वापस address of a call insn */
#घोषणा UPROBE_FIX_CALL		0x02

/* Inकाष्ठाion will modअगरy TF, करोn't change it */
#घोषणा UPROBE_FIX_SETF		0x04

#घोषणा UPROBE_FIX_RIP_SI	0x08
#घोषणा UPROBE_FIX_RIP_DI	0x10
#घोषणा UPROBE_FIX_RIP_BX	0x20
#घोषणा UPROBE_FIX_RIP_MASK	\
	(UPROBE_FIX_RIP_SI | UPROBE_FIX_RIP_DI | UPROBE_FIX_RIP_BX)

#घोषणा	UPROBE_TRAP_NR		अच_पूर्णांक_उच्च

/* Adaptations क्रम mhiramat x86 decoder v14. */
#घोषणा OPCODE1(insn)		((insn)->opcode.bytes[0])
#घोषणा OPCODE2(insn)		((insn)->opcode.bytes[1])
#घोषणा OPCODE3(insn)		((insn)->opcode.bytes[2])
#घोषणा MODRM_REG(insn)		X86_MODRM_REG((insn)->modrm.value)

#घोषणा W(row, b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, ba, bb, bc, bd, be, bf)\
	(((b0##UL << 0x0)|(b1##UL << 0x1)|(b2##UL << 0x2)|(b3##UL << 0x3) |   \
	  (b4##UL << 0x4)|(b5##UL << 0x5)|(b6##UL << 0x6)|(b7##UL << 0x7) |   \
	  (b8##UL << 0x8)|(b9##UL << 0x9)|(ba##UL << 0xa)|(bb##UL << 0xb) |   \
	  (bc##UL << 0xc)|(bd##UL << 0xd)|(be##UL << 0xe)|(bf##UL << 0xf))    \
	 << (row % 32))

/*
 * Good-inकाष्ठाion tables क्रम 32-bit apps.  This is non-स्थिर and अस्थिर
 * to keep gcc from अटलally optimizing it out, as variable_test_bit makes
 * some versions of gcc to think only *(अचिन्हित दीर्घ*) is used.
 *
 * Opcodes we'll probably never support:
 * 6c-6f - ins,outs. SEGVs अगर used in userspace
 * e4-e7 - in,out imm. SEGVs अगर used in userspace
 * ec-ef - in,out acc. SEGVs अगर used in userspace
 * cc - पूर्णांक3. SIGTRAP अगर used in userspace
 * ce - पूर्णांकo. Not used in userspace - no kernel support to make it useful. SEGVs
 *	(why we support bound (62) then? it's similar, and similarly unused...)
 * f1 - पूर्णांक1. SIGTRAP अगर used in userspace
 * f4 - hlt. SEGVs अगर used in userspace
 * fa - cli. SEGVs अगर used in userspace
 * fb - sti. SEGVs अगर used in userspace
 *
 * Opcodes which need some work to be supported:
 * 07,17,1f - pop es/ss/ds
 *	Normally not used in userspace, but would execute अगर used.
 *	Can cause GP or stack exception अगर tries to load wrong segment descriptor.
 *	We hesitate to run them under single step since kernel's handling
 *	of userspace single-stepping (TF flag) is fragile.
 *	We can easily refuse to support push es/cs/ss/ds (06/0e/16/1e)
 *	on the same grounds that they are never used.
 * cd - पूर्णांक N.
 *	Used by userspace क्रम "int 80" syscall entry. (Other "int N"
 *	cause GP -> SEGV since their IDT gates करोn't allow calls from CPL 3).
 *	Not supported since kernel's handling of userspace single-stepping
 *	(TF flag) is fragile.
 * cf - iret. Normally not used in userspace. Doesn't SEGV unless arguments are bad
 */
#अगर defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMULATION)
अटल अस्थिर u32 good_insns_32[256 / 32] = अणु
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f         */
	/*      ----------------------------------------------         */
	W(0x00, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1) | /* 00 */
	W(0x10, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0) , /* 10 */
	W(0x20, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 20 */
	W(0x30, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 30 */
	W(0x40, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 40 */
	W(0x50, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 50 */
	W(0x60, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0) | /* 60 */
	W(0x70, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 70 */
	W(0x80, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 80 */
	W(0x90, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 90 */
	W(0xa0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* a0 */
	W(0xb0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* b0 */
	W(0xc0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0) | /* c0 */
	W(0xd0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* d0 */
	W(0xe0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0) | /* e0 */
	W(0xf0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1)   /* f0 */
	/*      ----------------------------------------------         */
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f         */
पूर्ण;
#अन्यथा
#घोषणा good_insns_32	शून्य
#पूर्ण_अगर

/* Good-inकाष्ठाion tables क्रम 64-bit apps.
 *
 * Genuinely invalid opcodes:
 * 06,07 - क्रमmerly push/pop es
 * 0e - क्रमmerly push cs
 * 16,17 - क्रमmerly push/pop ss
 * 1e,1f - क्रमmerly push/pop ds
 * 27,2f,37,3f - क्रमmerly daa/das/aaa/aas
 * 60,61 - क्रमmerly pusha/popa
 * 62 - क्रमmerly bound. EVEX prefix क्रम AVX512 (not yet supported)
 * 82 - क्रमmerly redundant encoding of Group1
 * 9a - क्रमmerly call seg:ofs
 * ce - क्रमmerly पूर्णांकo
 * d4,d5 - क्रमmerly aam/aad
 * d6 - क्रमmerly unकरोcumented salc
 * ea - क्रमmerly jmp seg:ofs
 *
 * Opcodes we'll probably never support:
 * 6c-6f - ins,outs. SEGVs अगर used in userspace
 * e4-e7 - in,out imm. SEGVs अगर used in userspace
 * ec-ef - in,out acc. SEGVs अगर used in userspace
 * cc - पूर्णांक3. SIGTRAP अगर used in userspace
 * f1 - पूर्णांक1. SIGTRAP अगर used in userspace
 * f4 - hlt. SEGVs अगर used in userspace
 * fa - cli. SEGVs अगर used in userspace
 * fb - sti. SEGVs अगर used in userspace
 *
 * Opcodes which need some work to be supported:
 * cd - पूर्णांक N.
 *	Used by userspace क्रम "int 80" syscall entry. (Other "int N"
 *	cause GP -> SEGV since their IDT gates करोn't allow calls from CPL 3).
 *	Not supported since kernel's handling of userspace single-stepping
 *	(TF flag) is fragile.
 * cf - iret. Normally not used in userspace. Doesn't SEGV unless arguments are bad
 */
#अगर defined(CONFIG_X86_64)
अटल अस्थिर u32 good_insns_64[256 / 32] = अणु
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f         */
	/*      ----------------------------------------------         */
	W(0x00, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1) | /* 00 */
	W(0x10, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0) , /* 10 */
	W(0x20, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0) | /* 20 */
	W(0x30, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0) , /* 30 */
	W(0x40, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 40 */
	W(0x50, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 50 */
	W(0x60, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0) | /* 60 */
	W(0x70, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 70 */
	W(0x80, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 80 */
	W(0x90, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1) , /* 90 */
	W(0xa0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* a0 */
	W(0xb0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* b0 */
	W(0xc0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0) | /* c0 */
	W(0xd0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* d0 */
	W(0xe0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0) | /* e0 */
	W(0xf0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1)   /* f0 */
	/*      ----------------------------------------------         */
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f         */
पूर्ण;
#अन्यथा
#घोषणा good_insns_64	शून्य
#पूर्ण_अगर

/* Using this क्रम both 64-bit and 32-bit apps.
 * Opcodes we करोn't support:
 * 0f 00 - SLDT/STR/LLDT/LTR/VERR/VERW/-/- group. System insns
 * 0f 01 - SGDT/SIDT/LGDT/LIDT/SMSW/-/LMSW/INVLPG group.
 *	Also encodes tons of other प्रणाली insns अगर mod=11.
 *	Some are in fact non-प्रणाली: xend, xtest, rdtscp, maybe more
 * 0f 05 - syscall
 * 0f 06 - clts (CPL0 insn)
 * 0f 07 - sysret
 * 0f 08 - invd (CPL0 insn)
 * 0f 09 - wbinvd (CPL0 insn)
 * 0f 0b - ud2
 * 0f 30 - wrmsr (CPL0 insn) (then why rdmsr is allowed, it's also CPL0 insn?)
 * 0f 34 - sysenter
 * 0f 35 - sysनिकास
 * 0f 37 - माला_लोec
 * 0f 78 - vmपढ़ो (Intel VMX. CPL0 insn)
 * 0f 79 - vmग_लिखो (Intel VMX. CPL0 insn)
 *	Note: with prefixes, these two opcodes are
 *	extrq/insertq/AVX512 convert vector ops.
 * 0f ae - group15: [f]xsave,[f]xrstor,[v]अणुld,stपूर्णmxcsr,clflush[opt],
 *	अणुrd,wrपूर्णअणुfs,gsपूर्णbase,अणुs,l,mपूर्णfence.
 *	Why? They are all user-executable.
 */
अटल अस्थिर u32 good_2byte_insns[256 / 32] = अणु
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f         */
	/*      ----------------------------------------------         */
	W(0x00, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1) | /* 00 */
	W(0x10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 10 */
	W(0x20, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 20 */
	W(0x30, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1) , /* 30 */
	W(0x40, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 40 */
	W(0x50, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 50 */
	W(0x60, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 60 */
	W(0x70, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1) , /* 70 */
	W(0x80, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 80 */
	W(0x90, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 90 */
	W(0xa0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1) | /* a0 */
	W(0xb0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* b0 */
	W(0xc0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* c0 */
	W(0xd0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* d0 */
	W(0xe0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* e0 */
	W(0xf0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)   /* f0 */
	/*      ----------------------------------------------         */
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f         */
पूर्ण;
#अघोषित W

/*
 * opcodes we may need to refine support क्रम:
 *
 *  0f - 2-byte inकाष्ठाions: For many of these inकाष्ठाions, the validity
 *  depends on the prefix and/or the reg field.  On such inकाष्ठाions, we
 *  just consider the opcode combination valid अगर it corresponds to any
 *  valid inकाष्ठाion.
 *
 *  8f - Group 1 - only reg = 0 is OK
 *  c6-c7 - Group 11 - only reg = 0 is OK
 *  d9-df - fpu insns with some illegal encodings
 *  f2, f3 - repnz, repz prefixes.  These are also the first byte क्रम
 *  certain भग्नing-poपूर्णांक inकाष्ठाions, such as addsd.
 *
 *  fe - Group 4 - only reg = 0 or 1 is OK
 *  ff - Group 5 - only reg = 0-6 is OK
 *
 * others -- Do we need to support these?
 *
 *  0f - (भग्नing-poपूर्णांक?) prefetch inकाष्ठाions
 *  07, 17, 1f - pop es, pop ss, pop ds
 *  26, 2e, 36, 3e - es:, cs:, ss:, ds: segment prefixes --
 *	but 64 and 65 (fs: and gs:) seem to be used, so we support them
 *  67 - addr16 prefix
 *  ce - पूर्णांकo
 *  f0 - lock prefix
 */

/*
 * TODO:
 * - Where necessary, examine the modrm byte and allow only valid inकाष्ठाions
 * in the dअगरferent Groups and fpu inकाष्ठाions.
 */

अटल bool is_prefix_bad(काष्ठा insn *insn)
अणु
	insn_byte_t p;
	पूर्णांक i;

	क्रम_each_insn_prefix(insn, i, p) अणु
		insn_attr_t attr;

		attr = inat_get_opcode_attribute(p);
		चयन (attr) अणु
		हाल INAT_MAKE_PREFIX(INAT_PFX_ES):
		हाल INAT_MAKE_PREFIX(INAT_PFX_CS):
		हाल INAT_MAKE_PREFIX(INAT_PFX_DS):
		हाल INAT_MAKE_PREFIX(INAT_PFX_SS):
		हाल INAT_MAKE_PREFIX(INAT_PFX_LOCK):
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक uprobe_init_insn(काष्ठा arch_uprobe *auprobe, काष्ठा insn *insn, bool x86_64)
अणु
	क्रमागत insn_mode m = x86_64 ? INSN_MODE_64 : INSN_MODE_32;
	u32 अस्थिर *good_insns;
	पूर्णांक ret;

	ret = insn_decode(insn, auprobe->insn, माप(auprobe->insn), m);
	अगर (ret < 0)
		वापस -ENOEXEC;

	अगर (is_prefix_bad(insn))
		वापस -ENOTSUPP;

	/* We should not singlestep on the exception masking inकाष्ठाions */
	अगर (insn_masking_exception(insn))
		वापस -ENOTSUPP;

	अगर (x86_64)
		good_insns = good_insns_64;
	अन्यथा
		good_insns = good_insns_32;

	अगर (test_bit(OPCODE1(insn), (अचिन्हित दीर्घ *)good_insns))
		वापस 0;

	अगर (insn->opcode.nbytes == 2) अणु
		अगर (test_bit(OPCODE2(insn), (अचिन्हित दीर्घ *)good_2byte_insns))
			वापस 0;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

#अगर_घोषित CONFIG_X86_64
/*
 * If arch_uprobe->insn करोesn't use rip-relative addressing, वापस
 * immediately.  Otherwise, reग_लिखो the inकाष्ठाion so that it accesses
 * its memory opeअक्रम indirectly through a scratch रेजिस्टर.  Set
 * defparam->fixups accordingly. (The contents of the scratch रेजिस्टर
 * will be saved beक्रमe we single-step the modअगरied inकाष्ठाion,
 * and restored afterward).
 *
 * We करो this because a rip-relative inकाष्ठाion can access only a
 * relatively small area (+/- 2 GB from the inकाष्ठाion), and the XOL
 * area typically lies beyond that area.  At least क्रम inकाष्ठाions
 * that store to memory, we can't execute the original inकाष्ठाion
 * and "fix things up" later, because the misdirected store could be
 * disastrous.
 *
 * Some useful facts about rip-relative inकाष्ठाions:
 *
 *  - There's always a modrm byte with bit layout "00 reg 101".
 *  - There's never a SIB byte.
 *  - The displacement is always 4 bytes.
 *  - REX.B=1 bit in REX prefix, which normally extends r/m field,
 *    has no effect on rip-relative mode. It करोesn't make modrm byte
 *    with r/m=101 refer to रेजिस्टर 1101 = R13.
 */
अटल व्योम riprel_analyze(काष्ठा arch_uprobe *auprobe, काष्ठा insn *insn)
अणु
	u8 *cursor;
	u8 reg;
	u8 reg2;

	अगर (!insn_rip_relative(insn))
		वापस;

	/*
	 * insn_rip_relative() would have decoded rex_prefix, vex_prefix, modrm.
	 * Clear REX.b bit (extension of MODRM.rm field):
	 * we want to encode low numbered reg, not r8+.
	 */
	अगर (insn->rex_prefix.nbytes) अणु
		cursor = auprobe->insn + insn_offset_rex_prefix(insn);
		/* REX byte has 0100wrxb layout, clearing REX.b bit */
		*cursor &= 0xfe;
	पूर्ण
	/*
	 * Similar treaपंचांगent क्रम VEX3/EVEX prefix.
	 * TODO: add XOP treaपंचांगent when insn decoder supports them
	 */
	अगर (insn->vex_prefix.nbytes >= 3) अणु
		/*
		 * vex2:     c5    rvvvvLpp   (has no b bit)
		 * vex3/xop: c4/8f rxbmmmmm wvvvvLpp
		 * evex:     62    rxbR00mm wvvvv1pp zllBVaaa
		 * Setting VEX3.b (setting because it has inverted meaning).
		 * Setting EVEX.x since (in non-SIB encoding) EVEX.x
		 * is the 4th bit of MODRM.rm, and needs the same treaपंचांगent.
		 * For VEX3-encoded insns, VEX3.x value has no effect in
		 * non-SIB encoding, the change is superfluous but harmless.
		 */
		cursor = auprobe->insn + insn_offset_vex_prefix(insn) + 1;
		*cursor |= 0x60;
	पूर्ण

	/*
	 * Convert from rip-relative addressing to रेजिस्टर-relative addressing
	 * via a scratch रेजिस्टर.
	 *
	 * This is tricky since there are insns with modrm byte
	 * which also use रेजिस्टरs not encoded in modrm byte:
	 * [i]भाग/[i]mul: implicitly use dx:ax
	 * shअगरt ops: implicitly use cx
	 * cmpxchg: implicitly uses ax
	 * cmpxchg8/16b: implicitly uses dx:ax and bx:cx
	 *   Encoding: 0f c7/1 modrm
	 *   The code below thinks that reg=1 (cx), chooses si as scratch.
	 * mulx: implicitly uses dx: mulx r/m,r1,r2 करोes r1:r2 = dx * r/m.
	 *   First appeared in Haswell (BMI2 insn). It is vex-encoded.
	 *   Example where none of bx,cx,dx can be used as scratch reg:
	 *   c4 e2 63 f6 0d disp32   mulx disp32(%rip),%ebx,%ecx
	 * [v]pcmpistri: implicitly uses cx, xmm0
	 * [v]pcmpistrm: implicitly uses xmm0
	 * [v]pcmpestri: implicitly uses ax, dx, cx, xmm0
	 * [v]pcmpestrm: implicitly uses ax, dx, xmm0
	 *   Evil SSE4.2 string comparison ops from hell.
	 * maskmovq/[v]maskmovdqu: implicitly uses (ds:rdi) as destination.
	 *   Encoding: 0f f7 modrm, 66 0f f7 modrm, vex-encoded: c5 f9 f7 modrm.
	 *   Store op1, byte-masked by op2 msb's in each byte, to (ds:rdi).
	 *   AMD says it has no 3-opeअक्रम क्रमm (vex.vvvv must be 1111)
	 *   and that it can have only रेजिस्टर opeअक्रमs, not mem
	 *   (its modrm byte must have mode=11).
	 *   If these restrictions will ever be lअगरted,
	 *   we'll need code to prevent selection of di as scratch reg!
	 *
	 * Summary: I करोn't know any insns with modrm byte which
	 * use SI रेजिस्टर implicitly. DI रेजिस्टर is used only
	 * by one insn (maskmovq) and BX रेजिस्टर is used
	 * only by one too (cmpxchg8b).
	 * BP is stack-segment based (may be a problem?).
	 * AX, DX, CX are off-limits (many implicit users).
	 * SP is unusable (it's stack poपूर्णांकer - think about "pop mem";
	 * also, rsp+disp32 needs sib encoding -> insn length change).
	 */

	reg = MODRM_REG(insn);	/* Fetch modrm.reg */
	reg2 = 0xff;		/* Fetch vex.vvvv */
	अगर (insn->vex_prefix.nbytes)
		reg2 = insn->vex_prefix.bytes[2];
	/*
	 * TODO: add XOP vvvv पढ़ोing.
	 *
	 * vex.vvvv field is in bits 6-3, bits are inverted.
	 * But in 32-bit mode, high-order bit may be ignored.
	 * Thereक्रमe, let's consider only 3 low-order bits.
	 */
	reg2 = ((reg2 >> 3) & 0x7) ^ 0x7;
	/*
	 * Register numbering is ax,cx,dx,bx, sp,bp,si,di, r8..r15.
	 *
	 * Choose scratch reg. Order is important: must not select bx
	 * अगर we can use si (cmpxchg8b हाल!)
	 */
	अगर (reg != 6 && reg2 != 6) अणु
		reg2 = 6;
		auprobe->defparam.fixups |= UPROBE_FIX_RIP_SI;
	पूर्ण अन्यथा अगर (reg != 7 && reg2 != 7) अणु
		reg2 = 7;
		auprobe->defparam.fixups |= UPROBE_FIX_RIP_DI;
		/* TODO (paranoia): क्रमce maskmovq to not use di */
	पूर्ण अन्यथा अणु
		reg2 = 3;
		auprobe->defparam.fixups |= UPROBE_FIX_RIP_BX;
	पूर्ण
	/*
	 * Poपूर्णांक cursor at the modrm byte.  The next 4 bytes are the
	 * displacement.  Beyond the displacement, क्रम some inकाष्ठाions,
	 * is the immediate opeअक्रम.
	 */
	cursor = auprobe->insn + insn_offset_modrm(insn);
	/*
	 * Change modrm from "00 reg 101" to "10 reg reg2". Example:
	 * 89 05 disp32  mov %eax,disp32(%rip) becomes
	 * 89 86 disp32  mov %eax,disp32(%rsi)
	 */
	*cursor = 0x80 | (reg << 3) | reg2;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *
scratch_reg(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	अगर (auprobe->defparam.fixups & UPROBE_FIX_RIP_SI)
		वापस &regs->si;
	अगर (auprobe->defparam.fixups & UPROBE_FIX_RIP_DI)
		वापस &regs->di;
	वापस &regs->bx;
पूर्ण

/*
 * If we're emulating a rip-relative inकाष्ठाion, save the contents
 * of the scratch रेजिस्टर and store the target address in that रेजिस्टर.
 */
अटल व्योम riprel_pre_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	अगर (auprobe->defparam.fixups & UPROBE_FIX_RIP_MASK) अणु
		काष्ठा uprobe_task *utask = current->utask;
		अचिन्हित दीर्घ *sr = scratch_reg(auprobe, regs);

		utask->autask.saved_scratch_रेजिस्टर = *sr;
		*sr = utask->vaddr + auprobe->defparam.ilen;
	पूर्ण
पूर्ण

अटल व्योम riprel_post_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	अगर (auprobe->defparam.fixups & UPROBE_FIX_RIP_MASK) अणु
		काष्ठा uprobe_task *utask = current->utask;
		अचिन्हित दीर्घ *sr = scratch_reg(auprobe, regs);

		*sr = utask->autask.saved_scratch_रेजिस्टर;
	पूर्ण
पूर्ण
#अन्यथा /* 32-bit: */
/*
 * No RIP-relative addressing on 32-bit
 */
अटल व्योम riprel_analyze(काष्ठा arch_uprobe *auprobe, काष्ठा insn *insn)
अणु
पूर्ण
अटल व्योम riprel_pre_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
पूर्ण
अटल व्योम riprel_post_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_64 */

काष्ठा uprobe_xol_ops अणु
	bool	(*emulate)(काष्ठा arch_uprobe *, काष्ठा pt_regs *);
	पूर्णांक	(*pre_xol)(काष्ठा arch_uprobe *, काष्ठा pt_regs *);
	पूर्णांक	(*post_xol)(काष्ठा arch_uprobe *, काष्ठा pt_regs *);
	व्योम	(*पात)(काष्ठा arch_uprobe *, काष्ठा pt_regs *);
पूर्ण;

अटल अंतरभूत पूर्णांक माप_दीर्घ(काष्ठा pt_regs *regs)
अणु
	/*
	 * Check रेजिस्टरs क्रम mode as in_xxx_syscall() करोes not apply here.
	 */
	वापस user_64bit_mode(regs) ? 8 : 4;
पूर्ण

अटल पूर्णांक शेष_pre_xol_op(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	riprel_pre_xol(auprobe, regs);
	वापस 0;
पूर्ण

अटल पूर्णांक emulate_push_stack(काष्ठा pt_regs *regs, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ new_sp = regs->sp - माप_दीर्घ(regs);

	अगर (copy_to_user((व्योम __user *)new_sp, &val, माप_दीर्घ(regs)))
		वापस -EFAULT;

	regs->sp = new_sp;
	वापस 0;
पूर्ण

/*
 * We have to fix things up as follows:
 *
 * Typically, the new ip is relative to the copied inकाष्ठाion.  We need
 * to make it relative to the original inकाष्ठाion (FIX_IP).  Exceptions
 * are वापस inकाष्ठाions and असलolute or indirect jump or call inकाष्ठाions.
 *
 * If the single-stepped inकाष्ठाion was a call, the वापस address that
 * is atop the stack is the address following the copied inकाष्ठाion.  We
 * need to make it the address following the original inकाष्ठाion (FIX_CALL).
 *
 * If the original inकाष्ठाion was a rip-relative inकाष्ठाion such as
 * "movl %edx,0xnnnn(%rip)", we have instead executed an equivalent
 * inकाष्ठाion using a scratch रेजिस्टर -- e.g., "movl %edx,0xnnnn(%rsi)".
 * We need to restore the contents of the scratch रेजिस्टर
 * (FIX_RIP_reg).
 */
अटल पूर्णांक शेष_post_xol_op(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	riprel_post_xol(auprobe, regs);
	अगर (auprobe->defparam.fixups & UPROBE_FIX_IP) अणु
		दीर्घ correction = utask->vaddr - utask->xol_vaddr;
		regs->ip += correction;
	पूर्ण अन्यथा अगर (auprobe->defparam.fixups & UPROBE_FIX_CALL) अणु
		regs->sp += माप_दीर्घ(regs); /* Pop incorrect वापस address */
		अगर (emulate_push_stack(regs, utask->vaddr + auprobe->defparam.ilen))
			वापस -ERESTART;
	पूर्ण
	/* popf; tell the caller to not touch TF */
	अगर (auprobe->defparam.fixups & UPROBE_FIX_SETF)
		utask->autask.saved_tf = true;

	वापस 0;
पूर्ण

अटल व्योम शेष_पात_op(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	riprel_post_xol(auprobe, regs);
पूर्ण

अटल स्थिर काष्ठा uprobe_xol_ops शेष_xol_ops = अणु
	.pre_xol  = शेष_pre_xol_op,
	.post_xol = शेष_post_xol_op,
	.पात	  = शेष_पात_op,
पूर्ण;

अटल bool branch_is_call(काष्ठा arch_uprobe *auprobe)
अणु
	वापस auprobe->branch.opc1 == 0xe8;
पूर्ण

#घोषणा CASE_COND					\
	COND(70, 71, XF(OF))				\
	COND(72, 73, XF(CF))				\
	COND(74, 75, XF(ZF))				\
	COND(78, 79, XF(SF))				\
	COND(7a, 7b, XF(PF))				\
	COND(76, 77, XF(CF) || XF(ZF))			\
	COND(7c, 7d, XF(SF) != XF(OF))			\
	COND(7e, 7f, XF(ZF) || XF(SF) != XF(OF))

#घोषणा COND(op_y, op_n, expr)				\
	हाल 0x ## op_y: DO((expr) != 0)		\
	हाल 0x ## op_n: DO((expr) == 0)

#घोषणा XF(xf)	(!!(flags & X86_EFLAGS_ ## xf))

अटल bool is_cond_jmp_opcode(u8 opcode)
अणु
	चयन (opcode) अणु
	#घोषणा DO(expr)	\
		वापस true;
	CASE_COND
	#अघोषित	DO

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool check_jmp_cond(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags = regs->flags;

	चयन (auprobe->branch.opc1) अणु
	#घोषणा DO(expr)	\
		वापस expr;
	CASE_COND
	#अघोषित	DO

	शेष:	/* not a conditional jmp */
		वापस true;
	पूर्ण
पूर्ण

#अघोषित	XF
#अघोषित	COND
#अघोषित	CASE_COND

अटल bool branch_emulate_op(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ new_ip = regs->ip += auprobe->branch.ilen;
	अचिन्हित दीर्घ offs = (दीर्घ)auprobe->branch.offs;

	अगर (branch_is_call(auprobe)) अणु
		/*
		 * If it fails we execute this (mangled, see the comment in
		 * branch_clear_offset) insn out-of-line. In the likely हाल
		 * this should trigger the trap, and the probed application
		 * should die or restart the same insn after it handles the
		 * संकेत, arch_uprobe_post_xol() won't be even called.
		 *
		 * But there is corner हाल, see the comment in ->post_xol().
		 */
		अगर (emulate_push_stack(regs, new_ip))
			वापस false;
	पूर्ण अन्यथा अगर (!check_jmp_cond(auprobe, regs)) अणु
		offs = 0;
	पूर्ण

	regs->ip = new_ip + offs;
	वापस true;
पूर्ण

अटल bool push_emulate_op(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ *src_ptr = (व्योम *)regs + auprobe->push.reg_offset;

	अगर (emulate_push_stack(regs, *src_ptr))
		वापस false;
	regs->ip += auprobe->push.ilen;
	वापस true;
पूर्ण

अटल पूर्णांक branch_post_xol_op(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	BUG_ON(!branch_is_call(auprobe));
	/*
	 * We can only get here अगर branch_emulate_op() failed to push the ret
	 * address _and_ another thपढ़ो expanded our stack beक्रमe the (mangled)
	 * "call" insn was executed out-of-line. Just restore ->sp and restart.
	 * We could also restore ->ip and try to call branch_emulate_op() again.
	 */
	regs->sp += माप_दीर्घ(regs);
	वापस -ERESTART;
पूर्ण

अटल व्योम branch_clear_offset(काष्ठा arch_uprobe *auprobe, काष्ठा insn *insn)
अणु
	/*
	 * Turn this insn पूर्णांकo "call 1f; 1:", this is what we will execute
	 * out-of-line अगर ->emulate() fails. We only need this to generate
	 * a trap, so that the probed task receives the correct संकेत with
	 * the properly filled siginfo.
	 *
	 * But see the comment in ->post_xol(), in the unlikely हाल it can
	 * succeed. So we need to ensure that the new ->ip can not fall पूर्णांकo
	 * the non-canonical area and trigger #GP.
	 *
	 * We could turn it पूर्णांकo (say) "pushf", but then we would need to
	 * भागorce ->insn[] and ->ixol[]. We need to preserve the 1st byte
	 * of ->insn[] क्रम set_orig_insn().
	 */
	स_रखो(auprobe->insn + insn_offset_immediate(insn),
		0, insn->immediate.nbytes);
पूर्ण

अटल स्थिर काष्ठा uprobe_xol_ops branch_xol_ops = अणु
	.emulate  = branch_emulate_op,
	.post_xol = branch_post_xol_op,
पूर्ण;

अटल स्थिर काष्ठा uprobe_xol_ops push_xol_ops = अणु
	.emulate  = push_emulate_op,
पूर्ण;

/* Returns -ENOSYS अगर branch_xol_ops करोesn't handle this insn */
अटल पूर्णांक branch_setup_xol_ops(काष्ठा arch_uprobe *auprobe, काष्ठा insn *insn)
अणु
	u8 opc1 = OPCODE1(insn);
	insn_byte_t p;
	पूर्णांक i;

	चयन (opc1) अणु
	हाल 0xeb:	/* jmp 8 */
	हाल 0xe9:	/* jmp 32 */
	हाल 0x90:	/* prefix* + nop; same as jmp with .offs = 0 */
		अवरोध;

	हाल 0xe8:	/* call relative */
		branch_clear_offset(auprobe, insn);
		अवरोध;

	हाल 0x0f:
		अगर (insn->opcode.nbytes != 2)
			वापस -ENOSYS;
		/*
		 * If it is a "near" conditional jmp, OPCODE2() - 0x10 matches
		 * OPCODE1() of the "short" jmp which checks the same condition.
		 */
		opc1 = OPCODE2(insn) - 0x10;
		fallthrough;
	शेष:
		अगर (!is_cond_jmp_opcode(opc1))
			वापस -ENOSYS;
	पूर्ण

	/*
	 * 16-bit overrides such as CALLW (66 e8 nn nn) are not supported.
	 * Intel and AMD behavior dअगरfer in 64-bit mode: Intel ignores 66 prefix.
	 * No one uses these insns, reject any branch insns with such prefix.
	 */
	क्रम_each_insn_prefix(insn, i, p) अणु
		अगर (p == 0x66)
			वापस -ENOTSUPP;
	पूर्ण

	auprobe->branch.opc1 = opc1;
	auprobe->branch.ilen = insn->length;
	auprobe->branch.offs = insn->immediate.value;

	auprobe->ops = &branch_xol_ops;
	वापस 0;
पूर्ण

/* Returns -ENOSYS अगर push_xol_ops करोesn't handle this insn */
अटल पूर्णांक push_setup_xol_ops(काष्ठा arch_uprobe *auprobe, काष्ठा insn *insn)
अणु
	u8 opc1 = OPCODE1(insn), reg_offset = 0;

	अगर (opc1 < 0x50 || opc1 > 0x57)
		वापस -ENOSYS;

	अगर (insn->length > 2)
		वापस -ENOSYS;
	अगर (insn->length == 2) अणु
		/* only support rex_prefix 0x41 (x64 only) */
#अगर_घोषित CONFIG_X86_64
		अगर (insn->rex_prefix.nbytes != 1 ||
		    insn->rex_prefix.bytes[0] != 0x41)
			वापस -ENOSYS;

		चयन (opc1) अणु
		हाल 0x50:
			reg_offset = दुरत्व(काष्ठा pt_regs, r8);
			अवरोध;
		हाल 0x51:
			reg_offset = दुरत्व(काष्ठा pt_regs, r9);
			अवरोध;
		हाल 0x52:
			reg_offset = दुरत्व(काष्ठा pt_regs, r10);
			अवरोध;
		हाल 0x53:
			reg_offset = दुरत्व(काष्ठा pt_regs, r11);
			अवरोध;
		हाल 0x54:
			reg_offset = दुरत्व(काष्ठा pt_regs, r12);
			अवरोध;
		हाल 0x55:
			reg_offset = दुरत्व(काष्ठा pt_regs, r13);
			अवरोध;
		हाल 0x56:
			reg_offset = दुरत्व(काष्ठा pt_regs, r14);
			अवरोध;
		हाल 0x57:
			reg_offset = दुरत्व(काष्ठा pt_regs, r15);
			अवरोध;
		पूर्ण
#अन्यथा
		वापस -ENOSYS;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		चयन (opc1) अणु
		हाल 0x50:
			reg_offset = दुरत्व(काष्ठा pt_regs, ax);
			अवरोध;
		हाल 0x51:
			reg_offset = दुरत्व(काष्ठा pt_regs, cx);
			अवरोध;
		हाल 0x52:
			reg_offset = दुरत्व(काष्ठा pt_regs, dx);
			अवरोध;
		हाल 0x53:
			reg_offset = दुरत्व(काष्ठा pt_regs, bx);
			अवरोध;
		हाल 0x54:
			reg_offset = दुरत्व(काष्ठा pt_regs, sp);
			अवरोध;
		हाल 0x55:
			reg_offset = दुरत्व(काष्ठा pt_regs, bp);
			अवरोध;
		हाल 0x56:
			reg_offset = दुरत्व(काष्ठा pt_regs, si);
			अवरोध;
		हाल 0x57:
			reg_offset = दुरत्व(काष्ठा pt_regs, di);
			अवरोध;
		पूर्ण
	पूर्ण

	auprobe->push.reg_offset = reg_offset;
	auprobe->push.ilen = insn->length;
	auprobe->ops = &push_xol_ops;
	वापस 0;
पूर्ण

/**
 * arch_uprobe_analyze_insn - inकाष्ठाion analysis including validity and fixups.
 * @auprobe: the probepoपूर्णांक inक्रमmation.
 * @mm: the probed address space.
 * @addr: भव address at which to install the probepoपूर्णांक
 * Return 0 on success or a -ve number on error.
 */
पूर्णांक arch_uprobe_analyze_insn(काष्ठा arch_uprobe *auprobe, काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	काष्ठा insn insn;
	u8 fix_ip_or_call = UPROBE_FIX_IP;
	पूर्णांक ret;

	ret = uprobe_init_insn(auprobe, &insn, is_64bit_mm(mm));
	अगर (ret)
		वापस ret;

	ret = branch_setup_xol_ops(auprobe, &insn);
	अगर (ret != -ENOSYS)
		वापस ret;

	ret = push_setup_xol_ops(auprobe, &insn);
	अगर (ret != -ENOSYS)
		वापस ret;

	/*
	 * Figure out which fixups शेष_post_xol_op() will need to perक्रमm,
	 * and annotate defparam->fixups accordingly.
	 */
	चयन (OPCODE1(&insn)) अणु
	हाल 0x9d:		/* popf */
		auprobe->defparam.fixups |= UPROBE_FIX_SETF;
		अवरोध;
	हाल 0xc3:		/* ret or lret -- ip is correct */
	हाल 0xcb:
	हाल 0xc2:
	हाल 0xca:
	हाल 0xea:		/* jmp असलolute -- ip is correct */
		fix_ip_or_call = 0;
		अवरोध;
	हाल 0x9a:		/* call असलolute - Fix वापस addr, not ip */
		fix_ip_or_call = UPROBE_FIX_CALL;
		अवरोध;
	हाल 0xff:
		चयन (MODRM_REG(&insn)) अणु
		हाल 2: हाल 3:			/* call or lcall, indirect */
			fix_ip_or_call = UPROBE_FIX_CALL;
			अवरोध;
		हाल 4: हाल 5:			/* jmp or ljmp, indirect */
			fix_ip_or_call = 0;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		riprel_analyze(auprobe, &insn);
	पूर्ण

	auprobe->defparam.ilen = insn.length;
	auprobe->defparam.fixups |= fix_ip_or_call;

	auprobe->ops = &शेष_xol_ops;
	वापस 0;
पूर्ण

/*
 * arch_uprobe_pre_xol - prepare to execute out of line.
 * @auprobe: the probepoपूर्णांक inक्रमmation.
 * @regs: reflects the saved user state of current task.
 */
पूर्णांक arch_uprobe_pre_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	अगर (auprobe->ops->pre_xol) अणु
		पूर्णांक err = auprobe->ops->pre_xol(auprobe, regs);
		अगर (err)
			वापस err;
	पूर्ण

	regs->ip = utask->xol_vaddr;
	utask->autask.saved_trap_nr = current->thपढ़ो.trap_nr;
	current->thपढ़ो.trap_nr = UPROBE_TRAP_NR;

	utask->autask.saved_tf = !!(regs->flags & X86_EFLAGS_TF);
	regs->flags |= X86_EFLAGS_TF;
	अगर (test_tsk_thपढ़ो_flag(current, TIF_BLOCKSTEP))
		set_task_blockstep(current, false);

	वापस 0;
पूर्ण

/*
 * If xol insn itself traps and generates a संकेत(Say,
 * संक_अवैध/संक_अंश/etc), then detect the हाल where a singlestepped
 * inकाष्ठाion jumps back to its own address. It is assumed that anything
 * like करो_page_fault/करो_trap/etc sets thपढ़ो.trap_nr != -1.
 *
 * arch_uprobe_pre_xol/arch_uprobe_post_xol save/restore thपढ़ो.trap_nr,
 * arch_uprobe_xol_was_trapped() simply checks that ->trap_nr is not equal to
 * UPROBE_TRAP_NR == -1 set by arch_uprobe_pre_xol().
 */
bool arch_uprobe_xol_was_trapped(काष्ठा task_काष्ठा *t)
अणु
	अगर (t->thपढ़ो.trap_nr != UPROBE_TRAP_NR)
		वापस true;

	वापस false;
पूर्ण

/*
 * Called after single-stepping. To aव्योम the SMP problems that can
 * occur when we temporarily put back the original opcode to
 * single-step, we single-stepped a copy of the inकाष्ठाion.
 *
 * This function prepares to resume execution after the single-step.
 */
पूर्णांक arch_uprobe_post_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;
	bool send_sigtrap = utask->autask.saved_tf;
	पूर्णांक err = 0;

	WARN_ON_ONCE(current->thपढ़ो.trap_nr != UPROBE_TRAP_NR);
	current->thपढ़ो.trap_nr = utask->autask.saved_trap_nr;

	अगर (auprobe->ops->post_xol) अणु
		err = auprobe->ops->post_xol(auprobe, regs);
		अगर (err) अणु
			/*
			 * Restore ->ip क्रम restart or post mortem analysis.
			 * ->post_xol() must not वापस -ERESTART unless this
			 * is really possible.
			 */
			regs->ip = utask->vaddr;
			अगर (err == -ERESTART)
				err = 0;
			send_sigtrap = false;
		पूर्ण
	पूर्ण
	/*
	 * arch_uprobe_pre_xol() करोesn't save the state of TIF_BLOCKSTEP
	 * so we can get an extra SIGTRAP अगर we करो not clear TF. We need
	 * to examine the opcode to make it right.
	 */
	अगर (send_sigtrap)
		send_sig(SIGTRAP, current, 0);

	अगर (!utask->autask.saved_tf)
		regs->flags &= ~X86_EFLAGS_TF;

	वापस err;
पूर्ण

/* callback routine क्रम handling exceptions. */
पूर्णांक arch_uprobe_exception_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा die_args *args = data;
	काष्ठा pt_regs *regs = args->regs;
	पूर्णांक ret = NOTIFY_DONE;

	/* We are only पूर्णांकerested in userspace traps */
	अगर (regs && !user_mode(regs))
		वापस NOTIFY_DONE;

	चयन (val) अणु
	हाल DIE_INT3:
		अगर (uprobe_pre_sstep_notअगरier(regs))
			ret = NOTIFY_STOP;

		अवरोध;

	हाल DIE_DEBUG:
		अगर (uprobe_post_sstep_notअगरier(regs))
			ret = NOTIFY_STOP;

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function माला_लो called when XOL inकाष्ठाion either माला_लो trapped or
 * the thपढ़ो has a fatal संकेत. Reset the inकाष्ठाion poपूर्णांकer to its
 * probed address क्रम the potential restart or क्रम post mortem analysis.
 */
व्योम arch_uprobe_पात_xol(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	अगर (auprobe->ops->पात)
		auprobe->ops->पात(auprobe, regs);

	current->thपढ़ो.trap_nr = utask->autask.saved_trap_nr;
	regs->ip = utask->vaddr;
	/* clear TF अगर it was set by us in arch_uprobe_pre_xol() */
	अगर (!utask->autask.saved_tf)
		regs->flags &= ~X86_EFLAGS_TF;
पूर्ण

अटल bool __skip_sstep(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	अगर (auprobe->ops->emulate)
		वापस auprobe->ops->emulate(auprobe, regs);
	वापस false;
पूर्ण

bool arch_uprobe_skip_sstep(काष्ठा arch_uprobe *auprobe, काष्ठा pt_regs *regs)
अणु
	bool ret = __skip_sstep(auprobe, regs);
	अगर (ret && (regs->flags & X86_EFLAGS_TF))
		send_sig(SIGTRAP, current, 0);
	वापस ret;
पूर्ण

अचिन्हित दीर्घ
arch_uretprobe_hijack_वापस_addr(अचिन्हित दीर्घ trampoline_vaddr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rasize = माप_दीर्घ(regs), nleft;
	अचिन्हित दीर्घ orig_ret_vaddr = 0; /* clear high bits क्रम 32-bit apps */

	अगर (copy_from_user(&orig_ret_vaddr, (व्योम __user *)regs->sp, rasize))
		वापस -1;

	/* check whether address has been alपढ़ोy hijacked */
	अगर (orig_ret_vaddr == trampoline_vaddr)
		वापस orig_ret_vaddr;

	nleft = copy_to_user((व्योम __user *)regs->sp, &trampoline_vaddr, rasize);
	अगर (likely(!nleft))
		वापस orig_ret_vaddr;

	अगर (nleft != rasize) अणु
		pr_err("return address clobbered: pid=%d, %%sp=%#lx, %%ip=%#lx\n",
		       current->pid, regs->sp, regs->ip);

		क्रमce_sig(संक_अंश);
	पूर्ण

	वापस -1;
पूर्ण

bool arch_uretprobe_is_alive(काष्ठा वापस_instance *ret, क्रमागत rp_check ctx,
				काष्ठा pt_regs *regs)
अणु
	अगर (ctx == RP_CHECK_CALL) /* sp was just decremented by "call" insn */
		वापस regs->sp < ret->stack;
	अन्यथा
		वापस regs->sp <= ret->stack;
पूर्ण
