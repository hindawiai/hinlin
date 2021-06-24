<शैली गुरु>
/*
 * Utility functions क्रम x86 opeअक्रम and address decoding
 *
 * Copyright (C) Intel Corporation 2017
 */
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/ratelimit.h>
#समावेश <linux/mmu_context.h>
#समावेश <यंत्र/desc_defs.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/inat.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/insn-eval.h>
#समावेश <यंत्र/ldt.h>
#समावेश <यंत्र/vm86.h>

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "insn: " fmt

क्रमागत reg_type अणु
	REG_TYPE_RM = 0,
	REG_TYPE_REG,
	REG_TYPE_INDEX,
	REG_TYPE_BASE,
पूर्ण;

/**
 * is_string_insn() - Determine अगर inकाष्ठाion is a string inकाष्ठाion
 * @insn:	Inकाष्ठाion containing the opcode to inspect
 *
 * Returns:
 *
 * true अगर the inकाष्ठाion, determined by the opcode, is any of the
 * string inकाष्ठाions as defined in the Intel Software Development manual.
 * False otherwise.
 */
अटल bool is_string_insn(काष्ठा insn *insn)
अणु
	insn_get_opcode(insn);

	/* All string inकाष्ठाions have a 1-byte opcode. */
	अगर (insn->opcode.nbytes != 1)
		वापस false;

	चयन (insn->opcode.bytes[0]) अणु
	हाल 0x6c ... 0x6f:	/* INS, OUTS */
	हाल 0xa4 ... 0xa7:	/* MOVS, CMPS */
	हाल 0xaa ... 0xaf:	/* STOS, LODS, SCAS */
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * insn_has_rep_prefix() - Determine अगर inकाष्ठाion has a REP prefix
 * @insn:	Inकाष्ठाion containing the prefix to inspect
 *
 * Returns:
 *
 * true अगर the inकाष्ठाion has a REP prefix, false अगर not.
 */
bool insn_has_rep_prefix(काष्ठा insn *insn)
अणु
	insn_byte_t p;
	पूर्णांक i;

	insn_get_prefixes(insn);

	क्रम_each_insn_prefix(insn, i, p) अणु
		अगर (p == 0xf2 || p == 0xf3)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * get_seg_reg_override_idx() - obtain segment रेजिस्टर override index
 * @insn:	Valid inकाष्ठाion with segment override prefixes
 *
 * Inspect the inकाष्ठाion prefixes in @insn and find segment overrides, अगर any.
 *
 * Returns:
 *
 * A स्थिरant identअगरying the segment रेजिस्टर to use, among CS, SS, DS,
 * ES, FS, or GS. INAT_SEG_REG_DEFAULT is वापसed अगर no segment override
 * prefixes were found.
 *
 * -EINVAL in हाल of error.
 */
अटल पूर्णांक get_seg_reg_override_idx(काष्ठा insn *insn)
अणु
	पूर्णांक idx = INAT_SEG_REG_DEFAULT;
	पूर्णांक num_overrides = 0, i;
	insn_byte_t p;

	insn_get_prefixes(insn);

	/* Look क्रम any segment override prefixes. */
	क्रम_each_insn_prefix(insn, i, p) अणु
		insn_attr_t attr;

		attr = inat_get_opcode_attribute(p);
		चयन (attr) अणु
		हाल INAT_MAKE_PREFIX(INAT_PFX_CS):
			idx = INAT_SEG_REG_CS;
			num_overrides++;
			अवरोध;
		हाल INAT_MAKE_PREFIX(INAT_PFX_SS):
			idx = INAT_SEG_REG_SS;
			num_overrides++;
			अवरोध;
		हाल INAT_MAKE_PREFIX(INAT_PFX_DS):
			idx = INAT_SEG_REG_DS;
			num_overrides++;
			अवरोध;
		हाल INAT_MAKE_PREFIX(INAT_PFX_ES):
			idx = INAT_SEG_REG_ES;
			num_overrides++;
			अवरोध;
		हाल INAT_MAKE_PREFIX(INAT_PFX_FS):
			idx = INAT_SEG_REG_FS;
			num_overrides++;
			अवरोध;
		हाल INAT_MAKE_PREFIX(INAT_PFX_GS):
			idx = INAT_SEG_REG_GS;
			num_overrides++;
			अवरोध;
		/* No शेष action needed. */
		पूर्ण
	पूर्ण

	/* More than one segment override prefix leads to undefined behavior. */
	अगर (num_overrides > 1)
		वापस -EINVAL;

	वापस idx;
पूर्ण

/**
 * check_seg_overrides() - check अगर segment override prefixes are allowed
 * @insn:	Valid inकाष्ठाion with segment override prefixes
 * @regoff:	Opeअक्रम offset, in pt_regs, क्रम which the check is perक्रमmed
 *
 * For a particular रेजिस्टर used in रेजिस्टर-indirect addressing, determine अगर
 * segment override prefixes can be used. Specअगरically, no overrides are allowed
 * क्रम rDI अगर used with a string inकाष्ठाion.
 *
 * Returns:
 *
 * True अगर segment override prefixes can be used with the रेजिस्टर indicated
 * in @regoff. False अगर otherwise.
 */
अटल bool check_seg_overrides(काष्ठा insn *insn, पूर्णांक regoff)
अणु
	अगर (regoff == दुरत्व(काष्ठा pt_regs, di) && is_string_insn(insn))
		वापस false;

	वापस true;
पूर्ण

/**
 * resolve_शेष_seg() - resolve शेष segment रेजिस्टर index क्रम an opeअक्रम
 * @insn:	Inकाष्ठाion with opcode and address size. Must be valid.
 * @regs:	Register values as seen when entering kernel mode
 * @off:	Opeअक्रम offset, in pt_regs, क्रम which resolution is needed
 *
 * Resolve the शेष segment रेजिस्टर index associated with the inकाष्ठाion
 * opeअक्रम रेजिस्टर indicated by @off. Such index is resolved based on शेषs
 * described in the Intel Software Development Manual.
 *
 * Returns:
 *
 * If in रक्षित mode, a स्थिरant identअगरying the segment रेजिस्टर to use,
 * among CS, SS, ES or DS. If in दीर्घ mode, INAT_SEG_REG_IGNORE.
 *
 * -EINVAL in हाल of error.
 */
अटल पूर्णांक resolve_शेष_seg(काष्ठा insn *insn, काष्ठा pt_regs *regs, पूर्णांक off)
अणु
	अगर (any_64bit_mode(regs))
		वापस INAT_SEG_REG_IGNORE;
	/*
	 * Resolve the शेष segment रेजिस्टर as described in Section 3.7.4
	 * of the Intel Software Development Manual Vol. 1:
	 *
	 *  + DS क्रम all references involving r[ABCD]X, and rSI.
	 *  + If used in a string inकाष्ठाion, ES क्रम rDI. Otherwise, DS.
	 *  + AX, CX and DX are not valid रेजिस्टर opeअक्रमs in 16-bit address
	 *    encodings but are valid क्रम 32-bit and 64-bit encodings.
	 *  + -गलत_तर्क is reserved to identअगरy क्रम हालs in which no रेजिस्टर
	 *    is used (i.e., displacement-only addressing). Use DS.
	 *  + SS क्रम rSP or rBP.
	 *  + CS क्रम rIP.
	 */

	चयन (off) अणु
	हाल दुरत्व(काष्ठा pt_regs, ax):
	हाल दुरत्व(काष्ठा pt_regs, cx):
	हाल दुरत्व(काष्ठा pt_regs, dx):
		/* Need insn to verअगरy address size. */
		अगर (insn->addr_bytes == 2)
			वापस -EINVAL;

		fallthrough;

	हाल -गलत_तर्क:
	हाल दुरत्व(काष्ठा pt_regs, bx):
	हाल दुरत्व(काष्ठा pt_regs, si):
		वापस INAT_SEG_REG_DS;

	हाल दुरत्व(काष्ठा pt_regs, di):
		अगर (is_string_insn(insn))
			वापस INAT_SEG_REG_ES;
		वापस INAT_SEG_REG_DS;

	हाल दुरत्व(काष्ठा pt_regs, bp):
	हाल दुरत्व(काष्ठा pt_regs, sp):
		वापस INAT_SEG_REG_SS;

	हाल दुरत्व(काष्ठा pt_regs, ip):
		वापस INAT_SEG_REG_CS;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * resolve_seg_reg() - obtain segment रेजिस्टर index
 * @insn:	Inकाष्ठाion with opeअक्रमs
 * @regs:	Register values as seen when entering kernel mode
 * @regoff:	Opeअक्रम offset, in pt_regs, used to determine segment रेजिस्टर
 *
 * Determine the segment रेजिस्टर associated with the opeअक्रमs and, अगर
 * applicable, prefixes and the inकाष्ठाion poपूर्णांकed by @insn.
 *
 * The segment रेजिस्टर associated to an opeअक्रम used in रेजिस्टर-indirect
 * addressing depends on:
 *
 * a) Whether running in दीर्घ mode (in such a हाल segments are ignored, except
 * अगर FS or GS are used).
 *
 * b) Whether segment override prefixes can be used. Certain inकाष्ठाions and
 *    रेजिस्टरs करो not allow override prefixes.
 *
 * c) Whether segment overrides prefixes are found in the inकाष्ठाion prefixes.
 *
 * d) If there are not segment override prefixes or they cannot be used, the
 *    शेष segment रेजिस्टर associated with the opeअक्रम रेजिस्टर is used.
 *
 * The function checks first अगर segment override prefixes can be used with the
 * opeअक्रम indicated by @regoff. If allowed, obtain such overridden segment
 * रेजिस्टर index. Lastly, अगर not prefixes were found or cannot be used, resolve
 * the segment रेजिस्टर index to use based on the शेषs described in the
 * Intel करोcumentation. In दीर्घ mode, all segment रेजिस्टर indexes will be
 * ignored, except अगर overrides were found क्रम FS or GS. All these operations
 * are करोne using helper functions.
 *
 * The opeअक्रम रेजिस्टर, @regoff, is represented as the offset from the base of
 * pt_regs.
 *
 * As stated, the मुख्य use of this function is to determine the segment रेजिस्टर
 * index based on the inकाष्ठाion, its opeअक्रमs and prefixes. Hence, @insn
 * must be valid. However, अगर @regoff indicates rIP, we करोn't need to inspect
 * @insn at all as in this हाल CS is used in all हालs. This हाल is checked
 * beक्रमe proceeding further.
 *
 * Please note that this function करोes not वापस the value in the segment
 * रेजिस्टर (i.e., the segment selector) but our defined index. The segment
 * selector needs to be obtained using get_segment_selector() and passing the
 * segment रेजिस्टर index resolved by this function.
 *
 * Returns:
 *
 * An index identअगरying the segment रेजिस्टर to use, among CS, SS, DS,
 * ES, FS, or GS. INAT_SEG_REG_IGNORE is वापसed अगर running in दीर्घ mode.
 *
 * -EINVAL in हाल of error.
 */
अटल पूर्णांक resolve_seg_reg(काष्ठा insn *insn, काष्ठा pt_regs *regs, पूर्णांक regoff)
अणु
	पूर्णांक idx;

	/*
	 * In the unlikely event of having to resolve the segment रेजिस्टर
	 * index क्रम rIP, करो it first. Segment override prefixes should not
	 * be used. Hence, it is not necessary to inspect the inकाष्ठाion,
	 * which may be invalid at this poपूर्णांक.
	 */
	अगर (regoff == दुरत्व(काष्ठा pt_regs, ip)) अणु
		अगर (any_64bit_mode(regs))
			वापस INAT_SEG_REG_IGNORE;
		अन्यथा
			वापस INAT_SEG_REG_CS;
	पूर्ण

	अगर (!insn)
		वापस -EINVAL;

	अगर (!check_seg_overrides(insn, regoff))
		वापस resolve_शेष_seg(insn, regs, regoff);

	idx = get_seg_reg_override_idx(insn);
	अगर (idx < 0)
		वापस idx;

	अगर (idx == INAT_SEG_REG_DEFAULT)
		वापस resolve_शेष_seg(insn, regs, regoff);

	/*
	 * In दीर्घ mode, segment override prefixes are ignored, except क्रम
	 * overrides क्रम FS and GS.
	 */
	अगर (any_64bit_mode(regs)) अणु
		अगर (idx != INAT_SEG_REG_FS &&
		    idx != INAT_SEG_REG_GS)
			idx = INAT_SEG_REG_IGNORE;
	पूर्ण

	वापस idx;
पूर्ण

/**
 * get_segment_selector() - obtain segment selector
 * @regs:		Register values as seen when entering kernel mode
 * @seg_reg_idx:	Segment रेजिस्टर index to use
 *
 * Obtain the segment selector from any of the CS, SS, DS, ES, FS, GS segment
 * रेजिस्टरs. In CONFIG_X86_32, the segment is obtained from either pt_regs or
 * kernel_vm86_regs as applicable. In CONFIG_X86_64, CS and SS are obtained
 * from pt_regs. DS, ES, FS and GS are obtained by पढ़ोing the actual CPU
 * रेजिस्टरs. This करोne क्रम only क्रम completeness as in CONFIG_X86_64 segment
 * रेजिस्टरs are ignored.
 *
 * Returns:
 *
 * Value of the segment selector, including null when running in
 * दीर्घ mode.
 *
 * -EINVAL on error.
 */
अटल लघु get_segment_selector(काष्ठा pt_regs *regs, पूर्णांक seg_reg_idx)
अणु
#अगर_घोषित CONFIG_X86_64
	अचिन्हित लघु sel;

	चयन (seg_reg_idx) अणु
	हाल INAT_SEG_REG_IGNORE:
		वापस 0;
	हाल INAT_SEG_REG_CS:
		वापस (अचिन्हित लघु)(regs->cs & 0xffff);
	हाल INAT_SEG_REG_SS:
		वापस (अचिन्हित लघु)(regs->ss & 0xffff);
	हाल INAT_SEG_REG_DS:
		savesegment(ds, sel);
		वापस sel;
	हाल INAT_SEG_REG_ES:
		savesegment(es, sel);
		वापस sel;
	हाल INAT_SEG_REG_FS:
		savesegment(fs, sel);
		वापस sel;
	हाल INAT_SEG_REG_GS:
		savesegment(gs, sel);
		वापस sel;
	शेष:
		वापस -EINVAL;
	पूर्ण
#अन्यथा /* CONFIG_X86_32 */
	काष्ठा kernel_vm86_regs *vm86regs = (काष्ठा kernel_vm86_regs *)regs;

	अगर (v8086_mode(regs)) अणु
		चयन (seg_reg_idx) अणु
		हाल INAT_SEG_REG_CS:
			वापस (अचिन्हित लघु)(regs->cs & 0xffff);
		हाल INAT_SEG_REG_SS:
			वापस (अचिन्हित लघु)(regs->ss & 0xffff);
		हाल INAT_SEG_REG_DS:
			वापस vm86regs->ds;
		हाल INAT_SEG_REG_ES:
			वापस vm86regs->es;
		हाल INAT_SEG_REG_FS:
			वापस vm86regs->fs;
		हाल INAT_SEG_REG_GS:
			वापस vm86regs->gs;
		हाल INAT_SEG_REG_IGNORE:
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	चयन (seg_reg_idx) अणु
	हाल INAT_SEG_REG_CS:
		वापस (अचिन्हित लघु)(regs->cs & 0xffff);
	हाल INAT_SEG_REG_SS:
		वापस (अचिन्हित लघु)(regs->ss & 0xffff);
	हाल INAT_SEG_REG_DS:
		वापस (अचिन्हित लघु)(regs->ds & 0xffff);
	हाल INAT_SEG_REG_ES:
		वापस (अचिन्हित लघु)(regs->es & 0xffff);
	हाल INAT_SEG_REG_FS:
		वापस (अचिन्हित लघु)(regs->fs & 0xffff);
	हाल INAT_SEG_REG_GS:
		वापस get_user_gs(regs);
	हाल INAT_SEG_REG_IGNORE:
	शेष:
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर /* CONFIG_X86_64 */
पूर्ण

अटल पूर्णांक get_reg_offset(काष्ठा insn *insn, काष्ठा pt_regs *regs,
			  क्रमागत reg_type type)
अणु
	पूर्णांक regno = 0;

	अटल स्थिर पूर्णांक regoff[] = अणु
		दुरत्व(काष्ठा pt_regs, ax),
		दुरत्व(काष्ठा pt_regs, cx),
		दुरत्व(काष्ठा pt_regs, dx),
		दुरत्व(काष्ठा pt_regs, bx),
		दुरत्व(काष्ठा pt_regs, sp),
		दुरत्व(काष्ठा pt_regs, bp),
		दुरत्व(काष्ठा pt_regs, si),
		दुरत्व(काष्ठा pt_regs, di),
#अगर_घोषित CONFIG_X86_64
		दुरत्व(काष्ठा pt_regs, r8),
		दुरत्व(काष्ठा pt_regs, r9),
		दुरत्व(काष्ठा pt_regs, r10),
		दुरत्व(काष्ठा pt_regs, r11),
		दुरत्व(काष्ठा pt_regs, r12),
		दुरत्व(काष्ठा pt_regs, r13),
		दुरत्व(काष्ठा pt_regs, r14),
		दुरत्व(काष्ठा pt_regs, r15),
#पूर्ण_अगर
	पूर्ण;
	पूर्णांक nr_रेजिस्टरs = ARRAY_SIZE(regoff);
	/*
	 * Don't possibly decode a 32-bit inकाष्ठाions as
	 * पढ़ोing a 64-bit-only रेजिस्टर.
	 */
	अगर (IS_ENABLED(CONFIG_X86_64) && !insn->x86_64)
		nr_रेजिस्टरs -= 8;

	चयन (type) अणु
	हाल REG_TYPE_RM:
		regno = X86_MODRM_RM(insn->modrm.value);

		/*
		 * ModRM.mod == 0 and ModRM.rm == 5 means a 32-bit displacement
		 * follows the ModRM byte.
		 */
		अगर (!X86_MODRM_MOD(insn->modrm.value) && regno == 5)
			वापस -गलत_तर्क;

		अगर (X86_REX_B(insn->rex_prefix.value))
			regno += 8;
		अवरोध;

	हाल REG_TYPE_REG:
		regno = X86_MODRM_REG(insn->modrm.value);

		अगर (X86_REX_R(insn->rex_prefix.value))
			regno += 8;
		अवरोध;

	हाल REG_TYPE_INDEX:
		regno = X86_SIB_INDEX(insn->sib.value);
		अगर (X86_REX_X(insn->rex_prefix.value))
			regno += 8;

		/*
		 * If ModRM.mod != 3 and SIB.index = 4 the scale*index
		 * portion of the address computation is null. This is
		 * true only अगर REX.X is 0. In such a हाल, the SIB index
		 * is used in the address computation.
		 */
		अगर (X86_MODRM_MOD(insn->modrm.value) != 3 && regno == 4)
			वापस -गलत_तर्क;
		अवरोध;

	हाल REG_TYPE_BASE:
		regno = X86_SIB_BASE(insn->sib.value);
		/*
		 * If ModRM.mod is 0 and SIB.base == 5, the base of the
		 * रेजिस्टर-indirect addressing is 0. In this हाल, a
		 * 32-bit displacement follows the SIB byte.
		 */
		अगर (!X86_MODRM_MOD(insn->modrm.value) && regno == 5)
			वापस -गलत_तर्क;

		अगर (X86_REX_B(insn->rex_prefix.value))
			regno += 8;
		अवरोध;

	शेष:
		pr_err_ratelimited("invalid register type: %d\n", type);
		वापस -EINVAL;
	पूर्ण

	अगर (regno >= nr_रेजिस्टरs) अणु
		WARN_ONCE(1, "decoded an instruction with an invalid register");
		वापस -EINVAL;
	पूर्ण
	वापस regoff[regno];
पूर्ण

/**
 * get_reg_offset_16() - Obtain offset of रेजिस्टर indicated by inकाष्ठाion
 * @insn:	Inकाष्ठाion containing ModRM byte
 * @regs:	Register values as seen when entering kernel mode
 * @offs1:	Offset of the first opeअक्रम रेजिस्टर
 * @offs2:	Offset of the second opeअक्रम रेजिस्टर, अगर applicable
 *
 * Obtain the offset, in pt_regs, of the रेजिस्टरs indicated by the ModRM byte
 * in @insn. This function is to be used with 16-bit address encodings. The
 * @offs1 and @offs2 will be written with the offset of the two रेजिस्टरs
 * indicated by the inकाष्ठाion. In हालs where any of the रेजिस्टरs is not
 * referenced by the inकाष्ठाion, the value will be set to -गलत_तर्क.
 *
 * Returns:
 *
 * 0 on success, -EINVAL on error.
 */
अटल पूर्णांक get_reg_offset_16(काष्ठा insn *insn, काष्ठा pt_regs *regs,
			     पूर्णांक *offs1, पूर्णांक *offs2)
अणु
	/*
	 * 16-bit addressing can use one or two रेजिस्टरs. Specअगरics of
	 * encodings are given in Table 2-1. "16-Bit Addressing Forms with the
	 * ModR/M Byte" of the Intel Software Development Manual.
	 */
	अटल स्थिर पूर्णांक regoff1[] = अणु
		दुरत्व(काष्ठा pt_regs, bx),
		दुरत्व(काष्ठा pt_regs, bx),
		दुरत्व(काष्ठा pt_regs, bp),
		दुरत्व(काष्ठा pt_regs, bp),
		दुरत्व(काष्ठा pt_regs, si),
		दुरत्व(काष्ठा pt_regs, di),
		दुरत्व(काष्ठा pt_regs, bp),
		दुरत्व(काष्ठा pt_regs, bx),
	पूर्ण;

	अटल स्थिर पूर्णांक regoff2[] = अणु
		दुरत्व(काष्ठा pt_regs, si),
		दुरत्व(काष्ठा pt_regs, di),
		दुरत्व(काष्ठा pt_regs, si),
		दुरत्व(काष्ठा pt_regs, di),
		-गलत_तर्क,
		-गलत_तर्क,
		-गलत_तर्क,
		-गलत_तर्क,
	पूर्ण;

	अगर (!offs1 || !offs2)
		वापस -EINVAL;

	/* Opeअक्रम is a रेजिस्टर, use the generic function. */
	अगर (X86_MODRM_MOD(insn->modrm.value) == 3) अणु
		*offs1 = insn_get_modrm_rm_off(insn, regs);
		*offs2 = -गलत_तर्क;
		वापस 0;
	पूर्ण

	*offs1 = regoff1[X86_MODRM_RM(insn->modrm.value)];
	*offs2 = regoff2[X86_MODRM_RM(insn->modrm.value)];

	/*
	 * If ModRM.mod is 0 and ModRM.rm is 110b, then we use displacement-
	 * only addressing. This means that no रेजिस्टरs are involved in
	 * computing the effective address. Thus, ensure that the first
	 * रेजिस्टर offset is invalid. The second रेजिस्टर offset is alपढ़ोy
	 * invalid under the aक्रमementioned conditions.
	 */
	अगर ((X86_MODRM_MOD(insn->modrm.value) == 0) &&
	    (X86_MODRM_RM(insn->modrm.value) == 6))
		*offs1 = -गलत_तर्क;

	वापस 0;
पूर्ण

/**
 * get_desc() - Obtain contents of a segment descriptor
 * @out:	Segment descriptor contents on success
 * @sel:	Segment selector
 *
 * Given a segment selector, obtain a poपूर्णांकer to the segment descriptor.
 * Both global and local descriptor tables are supported.
 *
 * Returns:
 *
 * True on success, false on failure.
 *
 * शून्य on error.
 */
अटल bool get_desc(काष्ठा desc_काष्ठा *out, अचिन्हित लघु sel)
अणु
	काष्ठा desc_ptr gdt_desc = अणु0, 0पूर्ण;
	अचिन्हित दीर्घ desc_base;

#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
	अगर ((sel & SEGMENT_TI_MASK) == SEGMENT_LDT) अणु
		bool success = false;
		काष्ठा ldt_काष्ठा *ldt;

		/* Bits [15:3] contain the index of the desired entry. */
		sel >>= 3;

		mutex_lock(&current->active_mm->context.lock);
		ldt = current->active_mm->context.ldt;
		अगर (ldt && sel < ldt->nr_entries) अणु
			*out = ldt->entries[sel];
			success = true;
		पूर्ण

		mutex_unlock(&current->active_mm->context.lock);

		वापस success;
	पूर्ण
#पूर्ण_अगर
	native_store_gdt(&gdt_desc);

	/*
	 * Segment descriptors have a size of 8 bytes. Thus, the index is
	 * multiplied by 8 to obtain the memory offset of the desired descriptor
	 * from the base of the GDT. As bits [15:3] of the segment selector
	 * contain the index, it can be regarded as multiplied by 8 alपढ़ोy.
	 * All that reमुख्यs is to clear bits [2:0].
	 */
	desc_base = sel & ~(SEGMENT_RPL_MASK | SEGMENT_TI_MASK);

	अगर (desc_base > gdt_desc.size)
		वापस false;

	*out = *(काष्ठा desc_काष्ठा *)(gdt_desc.address + desc_base);
	वापस true;
पूर्ण

/**
 * insn_get_seg_base() - Obtain base address of segment descriptor.
 * @regs:		Register values as seen when entering kernel mode
 * @seg_reg_idx:	Index of the segment रेजिस्टर poपूर्णांकing to seg descriptor
 *
 * Obtain the base address of the segment as indicated by the segment descriptor
 * poपूर्णांकed by the segment selector. The segment selector is obtained from the
 * input segment रेजिस्टर index @seg_reg_idx.
 *
 * Returns:
 *
 * In रक्षित mode, base address of the segment. Zero in दीर्घ mode,
 * except when FS or GS are used. In भव-8086 mode, the segment
 * selector shअगरted 4 bits to the right.
 *
 * -1L in हाल of error.
 */
अचिन्हित दीर्घ insn_get_seg_base(काष्ठा pt_regs *regs, पूर्णांक seg_reg_idx)
अणु
	काष्ठा desc_काष्ठा desc;
	लघु sel;

	sel = get_segment_selector(regs, seg_reg_idx);
	अगर (sel < 0)
		वापस -1L;

	अगर (v8086_mode(regs))
		/*
		 * Base is simply the segment selector shअगरted 4
		 * bits to the right.
		 */
		वापस (अचिन्हित दीर्घ)(sel << 4);

	अगर (any_64bit_mode(regs)) अणु
		/*
		 * Only FS or GS will have a base address, the rest of
		 * the segments' bases are क्रमced to 0.
		 */
		अचिन्हित दीर्घ base;

		अगर (seg_reg_idx == INAT_SEG_REG_FS) अणु
			rdmsrl(MSR_FS_BASE, base);
		पूर्ण अन्यथा अगर (seg_reg_idx == INAT_SEG_REG_GS) अणु
			/*
			 * swapgs was called at the kernel entry poपूर्णांक. Thus,
			 * MSR_KERNEL_GS_BASE will have the user-space GS base.
			 */
			अगर (user_mode(regs))
				rdmsrl(MSR_KERNEL_GS_BASE, base);
			अन्यथा
				rdmsrl(MSR_GS_BASE, base);
		पूर्ण अन्यथा अणु
			base = 0;
		पूर्ण
		वापस base;
	पूर्ण

	/* In रक्षित mode the segment selector cannot be null. */
	अगर (!sel)
		वापस -1L;

	अगर (!get_desc(&desc, sel))
		वापस -1L;

	वापस get_desc_base(&desc);
पूर्ण

/**
 * get_seg_limit() - Obtain the limit of a segment descriptor
 * @regs:		Register values as seen when entering kernel mode
 * @seg_reg_idx:	Index of the segment रेजिस्टर poपूर्णांकing to seg descriptor
 *
 * Obtain the limit of the segment as indicated by the segment descriptor
 * poपूर्णांकed by the segment selector. The segment selector is obtained from the
 * input segment रेजिस्टर index @seg_reg_idx.
 *
 * Returns:
 *
 * In रक्षित mode, the limit of the segment descriptor in bytes.
 * In दीर्घ mode and भव-8086 mode, segment limits are not enक्रमced. Thus,
 * limit is वापसed as -1L to imply a limit-less segment.
 *
 * Zero is वापसed on error.
 */
अटल अचिन्हित दीर्घ get_seg_limit(काष्ठा pt_regs *regs, पूर्णांक seg_reg_idx)
अणु
	काष्ठा desc_काष्ठा desc;
	अचिन्हित दीर्घ limit;
	लघु sel;

	sel = get_segment_selector(regs, seg_reg_idx);
	अगर (sel < 0)
		वापस 0;

	अगर (any_64bit_mode(regs) || v8086_mode(regs))
		वापस -1L;

	अगर (!sel)
		वापस 0;

	अगर (!get_desc(&desc, sel))
		वापस 0;

	/*
	 * If the granularity bit is set, the limit is given in multiples
	 * of 4096. This also means that the 12 least signअगरicant bits are
	 * not tested when checking the segment limits. In practice,
	 * this means that the segment ends in (limit << 12) + 0xfff.
	 */
	limit = get_desc_limit(&desc);
	अगर (desc.g)
		limit = (limit << 12) + 0xfff;

	वापस limit;
पूर्ण

/**
 * insn_get_code_seg_params() - Obtain code segment parameters
 * @regs:	Structure with रेजिस्टर values as seen when entering kernel mode
 *
 * Obtain address and opeअक्रम sizes of the code segment. It is obtained from the
 * selector contained in the CS रेजिस्टर in regs. In रक्षित mode, the शेष
 * address is determined by inspecting the L and D bits of the segment
 * descriptor. In भव-8086 mode, the शेष is always two bytes क्रम both
 * address and opeअक्रम sizes.
 *
 * Returns:
 *
 * An पूर्णांक containing ORed-in शेष parameters on success.
 *
 * -EINVAL on error.
 */
पूर्णांक insn_get_code_seg_params(काष्ठा pt_regs *regs)
अणु
	काष्ठा desc_काष्ठा desc;
	लघु sel;

	अगर (v8086_mode(regs))
		/* Address and opeअक्रम size are both 16-bit. */
		वापस INSN_CODE_SEG_PARAMS(2, 2);

	sel = get_segment_selector(regs, INAT_SEG_REG_CS);
	अगर (sel < 0)
		वापस sel;

	अगर (!get_desc(&desc, sel))
		वापस -EINVAL;

	/*
	 * The most signअगरicant byte of the Type field of the segment descriptor
	 * determines whether a segment contains data or code. If this is a data
	 * segment, वापस error.
	 */
	अगर (!(desc.type & BIT(3)))
		वापस -EINVAL;

	चयन ((desc.l << 1) | desc.d) अणु
	हाल 0: /*
		 * Legacy mode. CS.L=0, CS.D=0. Address and opeअक्रम size are
		 * both 16-bit.
		 */
		वापस INSN_CODE_SEG_PARAMS(2, 2);
	हाल 1: /*
		 * Legacy mode. CS.L=0, CS.D=1. Address and opeअक्रम size are
		 * both 32-bit.
		 */
		वापस INSN_CODE_SEG_PARAMS(4, 4);
	हाल 2: /*
		 * IA-32e 64-bit mode. CS.L=1, CS.D=0. Address size is 64-bit;
		 * opeअक्रम size is 32-bit.
		 */
		वापस INSN_CODE_SEG_PARAMS(4, 8);
	हाल 3: /* Invalid setting. CS.L=1, CS.D=1 */
		fallthrough;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * insn_get_modrm_rm_off() - Obtain रेजिस्टर in r/m part of the ModRM byte
 * @insn:	Inकाष्ठाion containing the ModRM byte
 * @regs:	Register values as seen when entering kernel mode
 *
 * Returns:
 *
 * The रेजिस्टर indicated by the r/m part of the ModRM byte. The
 * रेजिस्टर is obtained as an offset from the base of pt_regs. In specअगरic
 * हालs, the वापसed value can be -गलत_तर्क to indicate that the particular value
 * of ModRM करोes not refer to a रेजिस्टर and shall be ignored.
 */
पूर्णांक insn_get_modrm_rm_off(काष्ठा insn *insn, काष्ठा pt_regs *regs)
अणु
	वापस get_reg_offset(insn, regs, REG_TYPE_RM);
पूर्ण

/**
 * insn_get_modrm_reg_off() - Obtain रेजिस्टर in reg part of the ModRM byte
 * @insn:	Inकाष्ठाion containing the ModRM byte
 * @regs:	Register values as seen when entering kernel mode
 *
 * Returns:
 *
 * The रेजिस्टर indicated by the reg part of the ModRM byte. The
 * रेजिस्टर is obtained as an offset from the base of pt_regs.
 */
पूर्णांक insn_get_modrm_reg_off(काष्ठा insn *insn, काष्ठा pt_regs *regs)
अणु
	वापस get_reg_offset(insn, regs, REG_TYPE_REG);
पूर्ण

/**
 * get_seg_base_limit() - obtain base address and limit of a segment
 * @insn:	Inकाष्ठाion. Must be valid.
 * @regs:	Register values as seen when entering kernel mode
 * @regoff:	Opeअक्रम offset, in pt_regs, used to resolve segment descriptor
 * @base:	Obtained segment base
 * @limit:	Obtained segment limit
 *
 * Obtain the base address and limit of the segment associated with the opeअक्रम
 * @regoff and, अगर any or allowed, override prefixes in @insn. This function is
 * dअगरferent from insn_get_seg_base() as the latter करोes not resolve the segment
 * associated with the inकाष्ठाion opeअक्रम. If a limit is not needed (e.g.,
 * when running in दीर्घ mode), @limit can be शून्य.
 *
 * Returns:
 *
 * 0 on success. @base and @limit will contain the base address and of the
 * resolved segment, respectively.
 *
 * -EINVAL on error.
 */
अटल पूर्णांक get_seg_base_limit(काष्ठा insn *insn, काष्ठा pt_regs *regs,
			      पूर्णांक regoff, अचिन्हित दीर्घ *base,
			      अचिन्हित दीर्घ *limit)
अणु
	पूर्णांक seg_reg_idx;

	अगर (!base)
		वापस -EINVAL;

	seg_reg_idx = resolve_seg_reg(insn, regs, regoff);
	अगर (seg_reg_idx < 0)
		वापस seg_reg_idx;

	*base = insn_get_seg_base(regs, seg_reg_idx);
	अगर (*base == -1L)
		वापस -EINVAL;

	अगर (!limit)
		वापस 0;

	*limit = get_seg_limit(regs, seg_reg_idx);
	अगर (!(*limit))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * get_eff_addr_reg() - Obtain effective address from रेजिस्टर opeअक्रम
 * @insn:	Inकाष्ठाion. Must be valid.
 * @regs:	Register values as seen when entering kernel mode
 * @regoff:	Obtained opeअक्रम offset, in pt_regs, with the effective address
 * @eff_addr:	Obtained effective address
 *
 * Obtain the effective address stored in the रेजिस्टर opeअक्रम as indicated by
 * the ModRM byte. This function is to be used only with रेजिस्टर addressing
 * (i.e.,  ModRM.mod is 3). The effective address is saved in @eff_addr. The
 * रेजिस्टर opeअक्रम, as an offset from the base of pt_regs, is saved in @regoff;
 * such offset can then be used to resolve the segment associated with the
 * opeअक्रम. This function can be used with any of the supported address sizes
 * in x86.
 *
 * Returns:
 *
 * 0 on success. @eff_addr will have the effective address stored in the
 * opeअक्रम indicated by ModRM. @regoff will have such opeअक्रम as an offset from
 * the base of pt_regs.
 *
 * -EINVAL on error.
 */
अटल पूर्णांक get_eff_addr_reg(काष्ठा insn *insn, काष्ठा pt_regs *regs,
			    पूर्णांक *regoff, दीर्घ *eff_addr)
अणु
	पूर्णांक ret;

	ret = insn_get_modrm(insn);
	अगर (ret)
		वापस ret;

	अगर (X86_MODRM_MOD(insn->modrm.value) != 3)
		वापस -EINVAL;

	*regoff = get_reg_offset(insn, regs, REG_TYPE_RM);
	अगर (*regoff < 0)
		वापस -EINVAL;

	/* Ignore bytes that are outside the address size. */
	अगर (insn->addr_bytes == 2)
		*eff_addr = regs_get_रेजिस्टर(regs, *regoff) & 0xffff;
	अन्यथा अगर (insn->addr_bytes == 4)
		*eff_addr = regs_get_रेजिस्टर(regs, *regoff) & 0xffffffff;
	अन्यथा /* 64-bit address */
		*eff_addr = regs_get_रेजिस्टर(regs, *regoff);

	वापस 0;
पूर्ण

/**
 * get_eff_addr_modrm() - Obtain referenced effective address via ModRM
 * @insn:	Inकाष्ठाion. Must be valid.
 * @regs:	Register values as seen when entering kernel mode
 * @regoff:	Obtained opeअक्रम offset, in pt_regs, associated with segment
 * @eff_addr:	Obtained effective address
 *
 * Obtain the effective address referenced by the ModRM byte of @insn. After
 * identअगरying the रेजिस्टरs involved in the रेजिस्टर-indirect memory reference,
 * its value is obtained from the opeअक्रमs in @regs. The computed address is
 * stored @eff_addr. Also, the रेजिस्टर opeअक्रम that indicates the associated
 * segment is stored in @regoff, this parameter can later be used to determine
 * such segment.
 *
 * Returns:
 *
 * 0 on success. @eff_addr will have the referenced effective address. @regoff
 * will have a रेजिस्टर, as an offset from the base of pt_regs, that can be used
 * to resolve the associated segment.
 *
 * -EINVAL on error.
 */
अटल पूर्णांक get_eff_addr_modrm(काष्ठा insn *insn, काष्ठा pt_regs *regs,
			      पूर्णांक *regoff, दीर्घ *eff_addr)
अणु
	दीर्घ पंचांगp;
	पूर्णांक ret;

	अगर (insn->addr_bytes != 8 && insn->addr_bytes != 4)
		वापस -EINVAL;

	ret = insn_get_modrm(insn);
	अगर (ret)
		वापस ret;

	अगर (X86_MODRM_MOD(insn->modrm.value) > 2)
		वापस -EINVAL;

	*regoff = get_reg_offset(insn, regs, REG_TYPE_RM);

	/*
	 * -गलत_तर्क means that we must ignore the address_offset. In such a हाल,
	 * in 64-bit mode the effective address relative to the rIP of the
	 * following inकाष्ठाion.
	 */
	अगर (*regoff == -गलत_तर्क) अणु
		अगर (any_64bit_mode(regs))
			पंचांगp = regs->ip + insn->length;
		अन्यथा
			पंचांगp = 0;
	पूर्ण अन्यथा अगर (*regoff < 0) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		पंचांगp = regs_get_रेजिस्टर(regs, *regoff);
	पूर्ण

	अगर (insn->addr_bytes == 4) अणु
		पूर्णांक addr32 = (पूर्णांक)(पंचांगp & 0xffffffff) + insn->displacement.value;

		*eff_addr = addr32 & 0xffffffff;
	पूर्ण अन्यथा अणु
		*eff_addr = पंचांगp + insn->displacement.value;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * get_eff_addr_modrm_16() - Obtain referenced effective address via ModRM
 * @insn:	Inकाष्ठाion. Must be valid.
 * @regs:	Register values as seen when entering kernel mode
 * @regoff:	Obtained opeअक्रम offset, in pt_regs, associated with segment
 * @eff_addr:	Obtained effective address
 *
 * Obtain the 16-bit effective address referenced by the ModRM byte of @insn.
 * After identअगरying the रेजिस्टरs involved in the रेजिस्टर-indirect memory
 * reference, its value is obtained from the opeअक्रमs in @regs. The computed
 * address is stored @eff_addr. Also, the रेजिस्टर opeअक्रम that indicates
 * the associated segment is stored in @regoff, this parameter can later be used
 * to determine such segment.
 *
 * Returns:
 *
 * 0 on success. @eff_addr will have the referenced effective address. @regoff
 * will have a रेजिस्टर, as an offset from the base of pt_regs, that can be used
 * to resolve the associated segment.
 *
 * -EINVAL on error.
 */
अटल पूर्णांक get_eff_addr_modrm_16(काष्ठा insn *insn, काष्ठा pt_regs *regs,
				 पूर्णांक *regoff, लघु *eff_addr)
अणु
	पूर्णांक addr_offset1, addr_offset2, ret;
	लघु addr1 = 0, addr2 = 0, displacement;

	अगर (insn->addr_bytes != 2)
		वापस -EINVAL;

	insn_get_modrm(insn);

	अगर (!insn->modrm.nbytes)
		वापस -EINVAL;

	अगर (X86_MODRM_MOD(insn->modrm.value) > 2)
		वापस -EINVAL;

	ret = get_reg_offset_16(insn, regs, &addr_offset1, &addr_offset2);
	अगर (ret < 0)
		वापस -EINVAL;

	/*
	 * Don't fail on invalid offset values. They might be invalid because
	 * they cannot be used क्रम this particular value of ModRM. Instead, use
	 * them in the computation only अगर they contain a valid value.
	 */
	अगर (addr_offset1 != -गलत_तर्क)
		addr1 = regs_get_रेजिस्टर(regs, addr_offset1) & 0xffff;

	अगर (addr_offset2 != -गलत_तर्क)
		addr2 = regs_get_रेजिस्टर(regs, addr_offset2) & 0xffff;

	displacement = insn->displacement.value & 0xffff;
	*eff_addr = addr1 + addr2 + displacement;

	/*
	 * The first opeअक्रम रेजिस्टर could indicate to use of either SS or DS
	 * रेजिस्टरs to obtain the segment selector.  The second opeअक्रम
	 * रेजिस्टर can only indicate the use of DS. Thus, the first opeअक्रम
	 * will be used to obtain the segment selector.
	 */
	*regoff = addr_offset1;

	वापस 0;
पूर्ण

/**
 * get_eff_addr_sib() - Obtain referenced effective address via SIB
 * @insn:	Inकाष्ठाion. Must be valid.
 * @regs:	Register values as seen when entering kernel mode
 * @regoff:	Obtained opeअक्रम offset, in pt_regs, associated with segment
 * @eff_addr:	Obtained effective address
 *
 * Obtain the effective address referenced by the SIB byte of @insn. After
 * identअगरying the रेजिस्टरs involved in the indexed, रेजिस्टर-indirect memory
 * reference, its value is obtained from the opeअक्रमs in @regs. The computed
 * address is stored @eff_addr. Also, the रेजिस्टर opeअक्रम that indicates the
 * associated segment is stored in @regoff, this parameter can later be used to
 * determine such segment.
 *
 * Returns:
 *
 * 0 on success. @eff_addr will have the referenced effective address.
 * @base_offset will have a रेजिस्टर, as an offset from the base of pt_regs,
 * that can be used to resolve the associated segment.
 *
 * Negative value on error.
 */
अटल पूर्णांक get_eff_addr_sib(काष्ठा insn *insn, काष्ठा pt_regs *regs,
			    पूर्णांक *base_offset, दीर्घ *eff_addr)
अणु
	दीर्घ base, indx;
	पूर्णांक indx_offset;
	पूर्णांक ret;

	अगर (insn->addr_bytes != 8 && insn->addr_bytes != 4)
		वापस -EINVAL;

	ret = insn_get_modrm(insn);
	अगर (ret)
		वापस ret;

	अगर (!insn->modrm.nbytes)
		वापस -EINVAL;

	अगर (X86_MODRM_MOD(insn->modrm.value) > 2)
		वापस -EINVAL;

	ret = insn_get_sib(insn);
	अगर (ret)
		वापस ret;

	अगर (!insn->sib.nbytes)
		वापस -EINVAL;

	*base_offset = get_reg_offset(insn, regs, REG_TYPE_BASE);
	indx_offset = get_reg_offset(insn, regs, REG_TYPE_INDEX);

	/*
	 * Negative values in the base and index offset means an error when
	 * decoding the SIB byte. Except -गलत_तर्क, which means that the रेजिस्टरs
	 * should not be used in the address computation.
	 */
	अगर (*base_offset == -गलत_तर्क)
		base = 0;
	अन्यथा अगर (*base_offset < 0)
		वापस -EINVAL;
	अन्यथा
		base = regs_get_रेजिस्टर(regs, *base_offset);

	अगर (indx_offset == -गलत_तर्क)
		indx = 0;
	अन्यथा अगर (indx_offset < 0)
		वापस -EINVAL;
	अन्यथा
		indx = regs_get_रेजिस्टर(regs, indx_offset);

	अगर (insn->addr_bytes == 4) अणु
		पूर्णांक addr32, base32, idx32;

		base32 = base & 0xffffffff;
		idx32 = indx & 0xffffffff;

		addr32 = base32 + idx32 * (1 << X86_SIB_SCALE(insn->sib.value));
		addr32 += insn->displacement.value;

		*eff_addr = addr32 & 0xffffffff;
	पूर्ण अन्यथा अणु
		*eff_addr = base + indx * (1 << X86_SIB_SCALE(insn->sib.value));
		*eff_addr += insn->displacement.value;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * get_addr_ref_16() - Obtain the 16-bit address referred by inकाष्ठाion
 * @insn:	Inकाष्ठाion containing ModRM byte and displacement
 * @regs:	Register values as seen when entering kernel mode
 *
 * This function is to be used with 16-bit address encodings. Obtain the memory
 * address referred by the inकाष्ठाion's ModRM and displacement bytes. Also, the
 * segment used as base is determined by either any segment override prefixes in
 * @insn or the शेष segment of the रेजिस्टरs involved in the address
 * computation. In रक्षित mode, segment limits are enक्रमced.
 *
 * Returns:
 *
 * Linear address referenced by the inकाष्ठाion opeअक्रमs on success.
 *
 * -1L on error.
 */
अटल व्योम __user *get_addr_ref_16(काष्ठा insn *insn, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ linear_addr = -1L, seg_base, seg_limit;
	पूर्णांक ret, regoff;
	लघु eff_addr;
	दीर्घ पंचांगp;

	अगर (insn_get_displacement(insn))
		जाओ out;

	अगर (insn->addr_bytes != 2)
		जाओ out;

	अगर (X86_MODRM_MOD(insn->modrm.value) == 3) अणु
		ret = get_eff_addr_reg(insn, regs, &regoff, &पंचांगp);
		अगर (ret)
			जाओ out;

		eff_addr = पंचांगp;
	पूर्ण अन्यथा अणु
		ret = get_eff_addr_modrm_16(insn, regs, &regoff, &eff_addr);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = get_seg_base_limit(insn, regs, regoff, &seg_base, &seg_limit);
	अगर (ret)
		जाओ out;

	/*
	 * Beक्रमe computing the linear address, make sure the effective address
	 * is within the limits of the segment. In भव-8086 mode, segment
	 * limits are not enक्रमced. In such a हाल, the segment limit is -1L to
	 * reflect this fact.
	 */
	अगर ((अचिन्हित दीर्घ)(eff_addr & 0xffff) > seg_limit)
		जाओ out;

	linear_addr = (अचिन्हित दीर्घ)(eff_addr & 0xffff) + seg_base;

	/* Limit linear address to 20 bits */
	अगर (v8086_mode(regs))
		linear_addr &= 0xfffff;

out:
	वापस (व्योम __user *)linear_addr;
पूर्ण

/**
 * get_addr_ref_32() - Obtain a 32-bit linear address
 * @insn:	Inकाष्ठाion with ModRM, SIB bytes and displacement
 * @regs:	Register values as seen when entering kernel mode
 *
 * This function is to be used with 32-bit address encodings to obtain the
 * linear memory address referred by the inकाष्ठाion's ModRM, SIB,
 * displacement bytes and segment base address, as applicable. If in रक्षित
 * mode, segment limits are enक्रमced.
 *
 * Returns:
 *
 * Linear address referenced by inकाष्ठाion and रेजिस्टरs on success.
 *
 * -1L on error.
 */
अटल व्योम __user *get_addr_ref_32(काष्ठा insn *insn, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ linear_addr = -1L, seg_base, seg_limit;
	पूर्णांक eff_addr, regoff;
	दीर्घ पंचांगp;
	पूर्णांक ret;

	अगर (insn->addr_bytes != 4)
		जाओ out;

	अगर (X86_MODRM_MOD(insn->modrm.value) == 3) अणु
		ret = get_eff_addr_reg(insn, regs, &regoff, &पंचांगp);
		अगर (ret)
			जाओ out;

		eff_addr = पंचांगp;

	पूर्ण अन्यथा अणु
		अगर (insn->sib.nbytes) अणु
			ret = get_eff_addr_sib(insn, regs, &regoff, &पंचांगp);
			अगर (ret)
				जाओ out;

			eff_addr = पंचांगp;
		पूर्ण अन्यथा अणु
			ret = get_eff_addr_modrm(insn, regs, &regoff, &पंचांगp);
			अगर (ret)
				जाओ out;

			eff_addr = पंचांगp;
		पूर्ण
	पूर्ण

	ret = get_seg_base_limit(insn, regs, regoff, &seg_base, &seg_limit);
	अगर (ret)
		जाओ out;

	/*
	 * In रक्षित mode, beक्रमe computing the linear address, make sure
	 * the effective address is within the limits of the segment.
	 * 32-bit addresses can be used in दीर्घ and भव-8086 modes अगर an
	 * address override prefix is used. In such हालs, segment limits are
	 * not enक्रमced. When in भव-8086 mode, the segment limit is -1L
	 * to reflect this situation.
	 *
	 * After computed, the effective address is treated as an अचिन्हित
	 * quantity.
	 */
	अगर (!any_64bit_mode(regs) && ((अचिन्हित पूर्णांक)eff_addr > seg_limit))
		जाओ out;

	/*
	 * Even though 32-bit address encodings are allowed in भव-8086
	 * mode, the address range is still limited to [0x-0xffff].
	 */
	अगर (v8086_mode(regs) && (eff_addr & ~0xffff))
		जाओ out;

	/*
	 * Data type दीर्घ could be 64 bits in size. Ensure that our 32-bit
	 * effective address is not sign-extended when computing the linear
	 * address.
	 */
	linear_addr = (अचिन्हित दीर्घ)(eff_addr & 0xffffffff) + seg_base;

	/* Limit linear address to 20 bits */
	अगर (v8086_mode(regs))
		linear_addr &= 0xfffff;

out:
	वापस (व्योम __user *)linear_addr;
पूर्ण

/**
 * get_addr_ref_64() - Obtain a 64-bit linear address
 * @insn:	Inकाष्ठाion काष्ठा with ModRM and SIB bytes and displacement
 * @regs:	Structure with रेजिस्टर values as seen when entering kernel mode
 *
 * This function is to be used with 64-bit address encodings to obtain the
 * linear memory address referred by the inकाष्ठाion's ModRM, SIB,
 * displacement bytes and segment base address, as applicable.
 *
 * Returns:
 *
 * Linear address referenced by inकाष्ठाion and रेजिस्टरs on success.
 *
 * -1L on error.
 */
#अगर_अघोषित CONFIG_X86_64
अटल व्योम __user *get_addr_ref_64(काष्ठा insn *insn, काष्ठा pt_regs *regs)
अणु
	वापस (व्योम __user *)-1L;
पूर्ण
#अन्यथा
अटल व्योम __user *get_addr_ref_64(काष्ठा insn *insn, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ linear_addr = -1L, seg_base;
	पूर्णांक regoff, ret;
	दीर्घ eff_addr;

	अगर (insn->addr_bytes != 8)
		जाओ out;

	अगर (X86_MODRM_MOD(insn->modrm.value) == 3) अणु
		ret = get_eff_addr_reg(insn, regs, &regoff, &eff_addr);
		अगर (ret)
			जाओ out;

	पूर्ण अन्यथा अणु
		अगर (insn->sib.nbytes) अणु
			ret = get_eff_addr_sib(insn, regs, &regoff, &eff_addr);
			अगर (ret)
				जाओ out;
		पूर्ण अन्यथा अणु
			ret = get_eff_addr_modrm(insn, regs, &regoff, &eff_addr);
			अगर (ret)
				जाओ out;
		पूर्ण

	पूर्ण

	ret = get_seg_base_limit(insn, regs, regoff, &seg_base, शून्य);
	अगर (ret)
		जाओ out;

	linear_addr = (अचिन्हित दीर्घ)eff_addr + seg_base;

out:
	वापस (व्योम __user *)linear_addr;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_64 */

/**
 * insn_get_addr_ref() - Obtain the linear address referred by inकाष्ठाion
 * @insn:	Inकाष्ठाion काष्ठाure containing ModRM byte and displacement
 * @regs:	Structure with रेजिस्टर values as seen when entering kernel mode
 *
 * Obtain the linear address referred by the inकाष्ठाion's ModRM, SIB and
 * displacement bytes, and segment base, as applicable. In रक्षित mode,
 * segment limits are enक्रमced.
 *
 * Returns:
 *
 * Linear address referenced by inकाष्ठाion and रेजिस्टरs on success.
 *
 * -1L on error.
 */
व्योम __user *insn_get_addr_ref(काष्ठा insn *insn, काष्ठा pt_regs *regs)
अणु
	अगर (!insn || !regs)
		वापस (व्योम __user *)-1L;

	चयन (insn->addr_bytes) अणु
	हाल 2:
		वापस get_addr_ref_16(insn, regs);
	हाल 4:
		वापस get_addr_ref_32(insn, regs);
	हाल 8:
		वापस get_addr_ref_64(insn, regs);
	शेष:
		वापस (व्योम __user *)-1L;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ insn_get_effective_ip(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ seg_base = 0;

	/*
	 * If not in user-space दीर्घ mode, a custom code segment could be in
	 * use. This is true in रक्षित mode (अगर the process defined a local
	 * descriptor table), or भव-8086 mode. In most of the हालs
	 * seg_base will be zero as in USER_CS.
	 */
	अगर (!user_64bit_mode(regs)) अणु
		seg_base = insn_get_seg_base(regs, INAT_SEG_REG_CS);
		अगर (seg_base == -1L)
			वापस 0;
	पूर्ण

	वापस seg_base + regs->ip;
पूर्ण

/**
 * insn_fetch_from_user() - Copy inकाष्ठाion bytes from user-space memory
 * @regs:	Structure with रेजिस्टर values as seen when entering kernel mode
 * @buf:	Array to store the fetched inकाष्ठाion
 *
 * Gets the linear address of the inकाष्ठाion and copies the inकाष्ठाion bytes
 * to the buf.
 *
 * Returns:
 *
 * Number of inकाष्ठाion bytes copied.
 *
 * 0 अगर nothing was copied.
 */
पूर्णांक insn_fetch_from_user(काष्ठा pt_regs *regs, अचिन्हित अक्षर buf[MAX_INSN_SIZE])
अणु
	अचिन्हित दीर्घ ip;
	पूर्णांक not_copied;

	ip = insn_get_effective_ip(regs);
	अगर (!ip)
		वापस 0;

	not_copied = copy_from_user(buf, (व्योम __user *)ip, MAX_INSN_SIZE);

	वापस MAX_INSN_SIZE - not_copied;
पूर्ण

/**
 * insn_fetch_from_user_inatomic() - Copy inकाष्ठाion bytes from user-space memory
 *                                   जबतक in atomic code
 * @regs:	Structure with रेजिस्टर values as seen when entering kernel mode
 * @buf:	Array to store the fetched inकाष्ठाion
 *
 * Gets the linear address of the inकाष्ठाion and copies the inकाष्ठाion bytes
 * to the buf. This function must be used in atomic context.
 *
 * Returns:
 *
 * Number of inकाष्ठाion bytes copied.
 *
 * 0 अगर nothing was copied.
 */
पूर्णांक insn_fetch_from_user_inatomic(काष्ठा pt_regs *regs, अचिन्हित अक्षर buf[MAX_INSN_SIZE])
अणु
	अचिन्हित दीर्घ ip;
	पूर्णांक not_copied;

	ip = insn_get_effective_ip(regs);
	अगर (!ip)
		वापस 0;

	not_copied = __copy_from_user_inatomic(buf, (व्योम __user *)ip, MAX_INSN_SIZE);

	वापस MAX_INSN_SIZE - not_copied;
पूर्ण

/**
 * insn_decode_from_regs() - Decode an inकाष्ठाion
 * @insn:	Structure to store decoded inकाष्ठाion
 * @regs:	Structure with रेजिस्टर values as seen when entering kernel mode
 * @buf:	Buffer containing the inकाष्ठाion bytes
 * @buf_size:   Number of inकाष्ठाion bytes available in buf
 *
 * Decodes the inकाष्ठाion provided in buf and stores the decoding results in
 * insn. Also determines the correct address and opeअक्रम sizes.
 *
 * Returns:
 *
 * True अगर inकाष्ठाion was decoded, False otherwise.
 */
bool insn_decode_from_regs(काष्ठा insn *insn, काष्ठा pt_regs *regs,
			   अचिन्हित अक्षर buf[MAX_INSN_SIZE], पूर्णांक buf_size)
अणु
	पूर्णांक seg_defs;

	insn_init(insn, buf, buf_size, user_64bit_mode(regs));

	/*
	 * Override the शेष opeअक्रम and address sizes with what is specअगरied
	 * in the code segment descriptor. The inकाष्ठाion decoder only sets
	 * the address size it to either 4 or 8 address bytes and करोes nothing
	 * क्रम the opeअक्रम bytes. This OK क्रम most of the हालs, but we could
	 * have special हालs where, क्रम instance, a 16-bit code segment
	 * descriptor is used.
	 * If there is an address override prefix, the inकाष्ठाion decoder
	 * correctly updates these values, even क्रम 16-bit शेषs.
	 */
	seg_defs = insn_get_code_seg_params(regs);
	अगर (seg_defs == -EINVAL)
		वापस false;

	insn->addr_bytes = INSN_CODE_SEG_ADDR_SZ(seg_defs);
	insn->opnd_bytes = INSN_CODE_SEG_OPND_SZ(seg_defs);

	अगर (insn_get_length(insn))
		वापस false;

	अगर (buf_size < insn->length)
		वापस false;

	वापस true;
पूर्ण
