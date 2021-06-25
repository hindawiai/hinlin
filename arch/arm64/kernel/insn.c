<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Huawei Ltd.
 * Author: Jiang Liu <liuj97@gmail.com>
 *
 * Copyright (C) 2014-2016 Zi Shen Lim <zlim.lnx@gmail.com>
 */
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/sections.h>

#घोषणा AARCH64_INSN_SF_BIT	BIT(31)
#घोषणा AARCH64_INSN_N_BIT	BIT(22)
#घोषणा AARCH64_INSN_LSL_12	BIT(22)

अटल स्थिर पूर्णांक aarch64_insn_encoding_class[] = अणु
	AARCH64_INSN_CLS_UNKNOWN,
	AARCH64_INSN_CLS_UNKNOWN,
	AARCH64_INSN_CLS_UNKNOWN,
	AARCH64_INSN_CLS_UNKNOWN,
	AARCH64_INSN_CLS_LDST,
	AARCH64_INSN_CLS_DP_REG,
	AARCH64_INSN_CLS_LDST,
	AARCH64_INSN_CLS_DP_FPSIMD,
	AARCH64_INSN_CLS_DP_IMM,
	AARCH64_INSN_CLS_DP_IMM,
	AARCH64_INSN_CLS_BR_SYS,
	AARCH64_INSN_CLS_BR_SYS,
	AARCH64_INSN_CLS_LDST,
	AARCH64_INSN_CLS_DP_REG,
	AARCH64_INSN_CLS_LDST,
	AARCH64_INSN_CLS_DP_FPSIMD,
पूर्ण;

क्रमागत aarch64_insn_encoding_class __kprobes aarch64_get_insn_class(u32 insn)
अणु
	वापस aarch64_insn_encoding_class[(insn >> 25) & 0xf];
पूर्ण

bool __kprobes aarch64_insn_is_steppable_hपूर्णांक(u32 insn)
अणु
	अगर (!aarch64_insn_is_hपूर्णांक(insn))
		वापस false;

	चयन (insn & 0xFE0) अणु
	हाल AARCH64_INSN_HINT_XPACLRI:
	हाल AARCH64_INSN_HINT_PACIA_1716:
	हाल AARCH64_INSN_HINT_PACIB_1716:
	हाल AARCH64_INSN_HINT_PACIAZ:
	हाल AARCH64_INSN_HINT_PACIASP:
	हाल AARCH64_INSN_HINT_PACIBZ:
	हाल AARCH64_INSN_HINT_PACIBSP:
	हाल AARCH64_INSN_HINT_BTI:
	हाल AARCH64_INSN_HINT_BTIC:
	हाल AARCH64_INSN_HINT_BTIJ:
	हाल AARCH64_INSN_HINT_BTIJC:
	हाल AARCH64_INSN_HINT_NOP:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

bool aarch64_insn_is_branch_imm(u32 insn)
अणु
	वापस (aarch64_insn_is_b(insn) || aarch64_insn_is_bl(insn) ||
		aarch64_insn_is_tbz(insn) || aarch64_insn_is_tbnz(insn) ||
		aarch64_insn_is_cbz(insn) || aarch64_insn_is_cbnz(insn) ||
		aarch64_insn_is_bcond(insn));
पूर्ण

अटल DEFINE_RAW_SPINLOCK(patch_lock);

अटल bool is_निकास_text(अचिन्हित दीर्घ addr)
अणु
	/* discarded with init text/data */
	वापस प्रणाली_state < SYSTEM_RUNNING &&
		addr >= (अचिन्हित दीर्घ)__निकासtext_begin &&
		addr < (अचिन्हित दीर्घ)__निकासtext_end;
पूर्ण

अटल bool is_image_text(अचिन्हित दीर्घ addr)
अणु
	वापस core_kernel_text(addr) || is_निकास_text(addr);
पूर्ण

अटल व्योम __kprobes *patch_map(व्योम *addr, पूर्णांक fixmap)
अणु
	अचिन्हित दीर्घ uपूर्णांकaddr = (uपूर्णांकptr_t) addr;
	bool image = is_image_text(uपूर्णांकaddr);
	काष्ठा page *page;

	अगर (image)
		page = phys_to_page(__pa_symbol(addr));
	अन्यथा अगर (IS_ENABLED(CONFIG_STRICT_MODULE_RWX))
		page = vदो_स्मृति_to_page(addr);
	अन्यथा
		वापस addr;

	BUG_ON(!page);
	वापस (व्योम *)set_fixmap_offset(fixmap, page_to_phys(page) +
			(uपूर्णांकaddr & ~PAGE_MASK));
पूर्ण

अटल व्योम __kprobes patch_unmap(पूर्णांक fixmap)
अणु
	clear_fixmap(fixmap);
पूर्ण
/*
 * In ARMv8-A, A64 inकाष्ठाions have a fixed length of 32 bits and are always
 * little-endian.
 */
पूर्णांक __kprobes aarch64_insn_पढ़ो(व्योम *addr, u32 *insnp)
अणु
	पूर्णांक ret;
	__le32 val;

	ret = copy_from_kernel_nofault(&val, addr, AARCH64_INSN_SIZE);
	अगर (!ret)
		*insnp = le32_to_cpu(val);

	वापस ret;
पूर्ण

अटल पूर्णांक __kprobes __aarch64_insn_ग_लिखो(व्योम *addr, __le32 insn)
अणु
	व्योम *waddr = addr;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	raw_spin_lock_irqsave(&patch_lock, flags);
	waddr = patch_map(addr, FIX_TEXT_POKE0);

	ret = copy_to_kernel_nofault(waddr, &insn, AARCH64_INSN_SIZE);

	patch_unmap(FIX_TEXT_POKE0);
	raw_spin_unlock_irqrestore(&patch_lock, flags);

	वापस ret;
पूर्ण

पूर्णांक __kprobes aarch64_insn_ग_लिखो(व्योम *addr, u32 insn)
अणु
	वापस __aarch64_insn_ग_लिखो(addr, cpu_to_le32(insn));
पूर्ण

bool __kprobes aarch64_insn_uses_literal(u32 insn)
अणु
	/* ldr/ldrsw (literal), prfm */

	वापस aarch64_insn_is_ldr_lit(insn) ||
		aarch64_insn_is_ldrsw_lit(insn) ||
		aarch64_insn_is_adr_adrp(insn) ||
		aarch64_insn_is_prfm_lit(insn);
पूर्ण

bool __kprobes aarch64_insn_is_branch(u32 insn)
अणु
	/* b, bl, cb*, tb*, ret*, b.cond, br*, blr* */

	वापस aarch64_insn_is_b(insn) ||
		aarch64_insn_is_bl(insn) ||
		aarch64_insn_is_cbz(insn) ||
		aarch64_insn_is_cbnz(insn) ||
		aarch64_insn_is_tbz(insn) ||
		aarch64_insn_is_tbnz(insn) ||
		aarch64_insn_is_ret(insn) ||
		aarch64_insn_is_ret_auth(insn) ||
		aarch64_insn_is_br(insn) ||
		aarch64_insn_is_br_auth(insn) ||
		aarch64_insn_is_blr(insn) ||
		aarch64_insn_is_blr_auth(insn) ||
		aarch64_insn_is_bcond(insn);
पूर्ण

पूर्णांक __kprobes aarch64_insn_patch_text_nosync(व्योम *addr, u32 insn)
अणु
	u32 *tp = addr;
	पूर्णांक ret;

	/* A64 inकाष्ठाions must be word aligned */
	अगर ((uपूर्णांकptr_t)tp & 0x3)
		वापस -EINVAL;

	ret = aarch64_insn_ग_लिखो(tp, insn);
	अगर (ret == 0)
		__flush_icache_range((uपूर्णांकptr_t)tp,
				     (uपूर्णांकptr_t)tp + AARCH64_INSN_SIZE);

	वापस ret;
पूर्ण

काष्ठा aarch64_insn_patch अणु
	व्योम		**text_addrs;
	u32		*new_insns;
	पूर्णांक		insn_cnt;
	atomic_t	cpu_count;
पूर्ण;

अटल पूर्णांक __kprobes aarch64_insn_patch_text_cb(व्योम *arg)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा aarch64_insn_patch *pp = arg;

	/* The first CPU becomes master */
	अगर (atomic_inc_वापस(&pp->cpu_count) == 1) अणु
		क्रम (i = 0; ret == 0 && i < pp->insn_cnt; i++)
			ret = aarch64_insn_patch_text_nosync(pp->text_addrs[i],
							     pp->new_insns[i]);
		/* Notअगरy other processors with an additional increment. */
		atomic_inc(&pp->cpu_count);
	पूर्ण अन्यथा अणु
		जबतक (atomic_पढ़ो(&pp->cpu_count) <= num_online_cpus())
			cpu_relax();
		isb();
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक __kprobes aarch64_insn_patch_text(व्योम *addrs[], u32 insns[], पूर्णांक cnt)
अणु
	काष्ठा aarch64_insn_patch patch = अणु
		.text_addrs = addrs,
		.new_insns = insns,
		.insn_cnt = cnt,
		.cpu_count = ATOMIC_INIT(0),
	पूर्ण;

	अगर (cnt <= 0)
		वापस -EINVAL;

	वापस stop_machine_cpuslocked(aarch64_insn_patch_text_cb, &patch,
				       cpu_online_mask);
पूर्ण

अटल पूर्णांक __kprobes aarch64_get_imm_shअगरt_mask(क्रमागत aarch64_insn_imm_type type,
						u32 *maskp, पूर्णांक *shअगरtp)
अणु
	u32 mask;
	पूर्णांक shअगरt;

	चयन (type) अणु
	हाल AARCH64_INSN_IMM_26:
		mask = BIT(26) - 1;
		shअगरt = 0;
		अवरोध;
	हाल AARCH64_INSN_IMM_19:
		mask = BIT(19) - 1;
		shअगरt = 5;
		अवरोध;
	हाल AARCH64_INSN_IMM_16:
		mask = BIT(16) - 1;
		shअगरt = 5;
		अवरोध;
	हाल AARCH64_INSN_IMM_14:
		mask = BIT(14) - 1;
		shअगरt = 5;
		अवरोध;
	हाल AARCH64_INSN_IMM_12:
		mask = BIT(12) - 1;
		shअगरt = 10;
		अवरोध;
	हाल AARCH64_INSN_IMM_9:
		mask = BIT(9) - 1;
		shअगरt = 12;
		अवरोध;
	हाल AARCH64_INSN_IMM_7:
		mask = BIT(7) - 1;
		shअगरt = 15;
		अवरोध;
	हाल AARCH64_INSN_IMM_6:
	हाल AARCH64_INSN_IMM_S:
		mask = BIT(6) - 1;
		shअगरt = 10;
		अवरोध;
	हाल AARCH64_INSN_IMM_R:
		mask = BIT(6) - 1;
		shअगरt = 16;
		अवरोध;
	हाल AARCH64_INSN_IMM_N:
		mask = 1;
		shअगरt = 22;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*maskp = mask;
	*shअगरtp = shअगरt;

	वापस 0;
पूर्ण

#घोषणा ADR_IMM_HILOSPLIT	2
#घोषणा ADR_IMM_SIZE		SZ_2M
#घोषणा ADR_IMM_LOMASK		((1 << ADR_IMM_HILOSPLIT) - 1)
#घोषणा ADR_IMM_HIMASK		((ADR_IMM_SIZE >> ADR_IMM_HILOSPLIT) - 1)
#घोषणा ADR_IMM_LOSHIFT		29
#घोषणा ADR_IMM_HISHIFT		5

u64 aarch64_insn_decode_immediate(क्रमागत aarch64_insn_imm_type type, u32 insn)
अणु
	u32 immlo, immhi, mask;
	पूर्णांक shअगरt;

	चयन (type) अणु
	हाल AARCH64_INSN_IMM_ADR:
		shअगरt = 0;
		immlo = (insn >> ADR_IMM_LOSHIFT) & ADR_IMM_LOMASK;
		immhi = (insn >> ADR_IMM_HISHIFT) & ADR_IMM_HIMASK;
		insn = (immhi << ADR_IMM_HILOSPLIT) | immlo;
		mask = ADR_IMM_SIZE - 1;
		अवरोध;
	शेष:
		अगर (aarch64_get_imm_shअगरt_mask(type, &mask, &shअगरt) < 0) अणु
			pr_err("aarch64_insn_decode_immediate: unknown immediate encoding %d\n",
			       type);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस (insn >> shअगरt) & mask;
पूर्ण

u32 __kprobes aarch64_insn_encode_immediate(क्रमागत aarch64_insn_imm_type type,
				  u32 insn, u64 imm)
अणु
	u32 immlo, immhi, mask;
	पूर्णांक shअगरt;

	अगर (insn == AARCH64_BREAK_FAULT)
		वापस AARCH64_BREAK_FAULT;

	चयन (type) अणु
	हाल AARCH64_INSN_IMM_ADR:
		shअगरt = 0;
		immlo = (imm & ADR_IMM_LOMASK) << ADR_IMM_LOSHIFT;
		imm >>= ADR_IMM_HILOSPLIT;
		immhi = (imm & ADR_IMM_HIMASK) << ADR_IMM_HISHIFT;
		imm = immlo | immhi;
		mask = ((ADR_IMM_LOMASK << ADR_IMM_LOSHIFT) |
			(ADR_IMM_HIMASK << ADR_IMM_HISHIFT));
		अवरोध;
	शेष:
		अगर (aarch64_get_imm_shअगरt_mask(type, &mask, &shअगरt) < 0) अणु
			pr_err("aarch64_insn_encode_immediate: unknown immediate encoding %d\n",
			       type);
			वापस AARCH64_BREAK_FAULT;
		पूर्ण
	पूर्ण

	/* Update the immediate field. */
	insn &= ~(mask << shअगरt);
	insn |= (imm & mask) << shअगरt;

	वापस insn;
पूर्ण

u32 aarch64_insn_decode_रेजिस्टर(क्रमागत aarch64_insn_रेजिस्टर_type type,
					u32 insn)
अणु
	पूर्णांक shअगरt;

	चयन (type) अणु
	हाल AARCH64_INSN_REGTYPE_RT:
	हाल AARCH64_INSN_REGTYPE_RD:
		shअगरt = 0;
		अवरोध;
	हाल AARCH64_INSN_REGTYPE_RN:
		shअगरt = 5;
		अवरोध;
	हाल AARCH64_INSN_REGTYPE_RT2:
	हाल AARCH64_INSN_REGTYPE_RA:
		shअगरt = 10;
		अवरोध;
	हाल AARCH64_INSN_REGTYPE_RM:
		shअगरt = 16;
		अवरोध;
	शेष:
		pr_err("%s: unknown register type encoding %d\n", __func__,
		       type);
		वापस 0;
	पूर्ण

	वापस (insn >> shअगरt) & GENMASK(4, 0);
पूर्ण

अटल u32 aarch64_insn_encode_रेजिस्टर(क्रमागत aarch64_insn_रेजिस्टर_type type,
					u32 insn,
					क्रमागत aarch64_insn_रेजिस्टर reg)
अणु
	पूर्णांक shअगरt;

	अगर (insn == AARCH64_BREAK_FAULT)
		वापस AARCH64_BREAK_FAULT;

	अगर (reg < AARCH64_INSN_REG_0 || reg > AARCH64_INSN_REG_SP) अणु
		pr_err("%s: unknown register encoding %d\n", __func__, reg);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (type) अणु
	हाल AARCH64_INSN_REGTYPE_RT:
	हाल AARCH64_INSN_REGTYPE_RD:
		shअगरt = 0;
		अवरोध;
	हाल AARCH64_INSN_REGTYPE_RN:
		shअगरt = 5;
		अवरोध;
	हाल AARCH64_INSN_REGTYPE_RT2:
	हाल AARCH64_INSN_REGTYPE_RA:
		shअगरt = 10;
		अवरोध;
	हाल AARCH64_INSN_REGTYPE_RM:
	हाल AARCH64_INSN_REGTYPE_RS:
		shअगरt = 16;
		अवरोध;
	शेष:
		pr_err("%s: unknown register type encoding %d\n", __func__,
		       type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn &= ~(GENMASK(4, 0) << shअगरt);
	insn |= reg << shअगरt;

	वापस insn;
पूर्ण

अटल u32 aarch64_insn_encode_ldst_size(क्रमागत aarch64_insn_माप_प्रकारype type,
					 u32 insn)
अणु
	u32 size;

	चयन (type) अणु
	हाल AARCH64_INSN_SIZE_8:
		size = 0;
		अवरोध;
	हाल AARCH64_INSN_SIZE_16:
		size = 1;
		अवरोध;
	हाल AARCH64_INSN_SIZE_32:
		size = 2;
		अवरोध;
	हाल AARCH64_INSN_SIZE_64:
		size = 3;
		अवरोध;
	शेष:
		pr_err("%s: unknown size encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn &= ~GENMASK(31, 30);
	insn |= size << 30;

	वापस insn;
पूर्ण

अटल अंतरभूत दीर्घ branch_imm_common(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ addr,
				     दीर्घ range)
अणु
	दीर्घ offset;

	अगर ((pc & 0x3) || (addr & 0x3)) अणु
		pr_err("%s: A64 instructions must be word aligned\n", __func__);
		वापस range;
	पूर्ण

	offset = ((दीर्घ)addr - (दीर्घ)pc);

	अगर (offset < -range || offset >= range) अणु
		pr_err("%s: offset out of range\n", __func__);
		वापस range;
	पूर्ण

	वापस offset;
पूर्ण

u32 __kprobes aarch64_insn_gen_branch_imm(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ addr,
					  क्रमागत aarch64_insn_branch_type type)
अणु
	u32 insn;
	दीर्घ offset;

	/*
	 * B/BL support [-128M, 128M) offset
	 * ARM64 भव address arrangement guarantees all kernel and module
	 * texts are within +/-128M.
	 */
	offset = branch_imm_common(pc, addr, SZ_128M);
	अगर (offset >= SZ_128M)
		वापस AARCH64_BREAK_FAULT;

	चयन (type) अणु
	हाल AARCH64_INSN_BRANCH_LINK:
		insn = aarch64_insn_get_bl_value();
		अवरोध;
	हाल AARCH64_INSN_BRANCH_NOLINK:
		insn = aarch64_insn_get_b_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown branch encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_26, insn,
					     offset >> 2);
पूर्ण

u32 aarch64_insn_gen_comp_branch_imm(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ addr,
				     क्रमागत aarch64_insn_रेजिस्टर reg,
				     क्रमागत aarch64_insn_variant variant,
				     क्रमागत aarch64_insn_branch_type type)
अणु
	u32 insn;
	दीर्घ offset;

	offset = branch_imm_common(pc, addr, SZ_1M);
	अगर (offset >= SZ_1M)
		वापस AARCH64_BREAK_FAULT;

	चयन (type) अणु
	हाल AARCH64_INSN_BRANCH_COMP_ZERO:
		insn = aarch64_insn_get_cbz_value();
		अवरोध;
	हाल AARCH64_INSN_BRANCH_COMP_NONZERO:
		insn = aarch64_insn_get_cbnz_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown branch encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (variant) अणु
	हाल AARCH64_INSN_VARIANT_32BIT:
		अवरोध;
	हाल AARCH64_INSN_VARIANT_64BIT:
		insn |= AARCH64_INSN_SF_BIT;
		अवरोध;
	शेष:
		pr_err("%s: unknown variant encoding %d\n", __func__, variant);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RT, insn, reg);

	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_19, insn,
					     offset >> 2);
पूर्ण

u32 aarch64_insn_gen_cond_branch_imm(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ addr,
				     क्रमागत aarch64_insn_condition cond)
अणु
	u32 insn;
	दीर्घ offset;

	offset = branch_imm_common(pc, addr, SZ_1M);

	insn = aarch64_insn_get_bcond_value();

	अगर (cond < AARCH64_INSN_COND_EQ || cond > AARCH64_INSN_COND_AL) अणु
		pr_err("%s: unknown condition encoding %d\n", __func__, cond);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण
	insn |= cond;

	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_19, insn,
					     offset >> 2);
पूर्ण

u32 __kprobes aarch64_insn_gen_hपूर्णांक(क्रमागत aarch64_insn_hपूर्णांक_cr_op op)
अणु
	वापस aarch64_insn_get_hपूर्णांक_value() | op;
पूर्ण

u32 __kprobes aarch64_insn_gen_nop(व्योम)
अणु
	वापस aarch64_insn_gen_hपूर्णांक(AARCH64_INSN_HINT_NOP);
पूर्ण

u32 aarch64_insn_gen_branch_reg(क्रमागत aarch64_insn_रेजिस्टर reg,
				क्रमागत aarch64_insn_branch_type type)
अणु
	u32 insn;

	चयन (type) अणु
	हाल AARCH64_INSN_BRANCH_NOLINK:
		insn = aarch64_insn_get_br_value();
		अवरोध;
	हाल AARCH64_INSN_BRANCH_LINK:
		insn = aarch64_insn_get_blr_value();
		अवरोध;
	हाल AARCH64_INSN_BRANCH_RETURN:
		insn = aarch64_insn_get_ret_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown branch encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	वापस aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn, reg);
पूर्ण

u32 aarch64_insn_gen_load_store_reg(क्रमागत aarch64_insn_रेजिस्टर reg,
				    क्रमागत aarch64_insn_रेजिस्टर base,
				    क्रमागत aarch64_insn_रेजिस्टर offset,
				    क्रमागत aarch64_insn_माप_प्रकारype size,
				    क्रमागत aarch64_insn_ldst_type type)
अणु
	u32 insn;

	चयन (type) अणु
	हाल AARCH64_INSN_LDST_LOAD_REG_OFFSET:
		insn = aarch64_insn_get_ldr_reg_value();
		अवरोध;
	हाल AARCH64_INSN_LDST_STORE_REG_OFFSET:
		insn = aarch64_insn_get_str_reg_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown load/store encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn = aarch64_insn_encode_ldst_size(size, insn);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RT, insn, reg);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn,
					    base);

	वापस aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RM, insn,
					    offset);
पूर्ण

u32 aarch64_insn_gen_load_store_pair(क्रमागत aarch64_insn_रेजिस्टर reg1,
				     क्रमागत aarch64_insn_रेजिस्टर reg2,
				     क्रमागत aarch64_insn_रेजिस्टर base,
				     पूर्णांक offset,
				     क्रमागत aarch64_insn_variant variant,
				     क्रमागत aarch64_insn_ldst_type type)
अणु
	u32 insn;
	पूर्णांक shअगरt;

	चयन (type) अणु
	हाल AARCH64_INSN_LDST_LOAD_PAIR_PRE_INDEX:
		insn = aarch64_insn_get_ldp_pre_value();
		अवरोध;
	हाल AARCH64_INSN_LDST_STORE_PAIR_PRE_INDEX:
		insn = aarch64_insn_get_stp_pre_value();
		अवरोध;
	हाल AARCH64_INSN_LDST_LOAD_PAIR_POST_INDEX:
		insn = aarch64_insn_get_ldp_post_value();
		अवरोध;
	हाल AARCH64_INSN_LDST_STORE_PAIR_POST_INDEX:
		insn = aarch64_insn_get_stp_post_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown load/store encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (variant) अणु
	हाल AARCH64_INSN_VARIANT_32BIT:
		अगर ((offset & 0x3) || (offset < -256) || (offset > 252)) अणु
			pr_err("%s: offset must be multiples of 4 in the range of [-256, 252] %d\n",
			       __func__, offset);
			वापस AARCH64_BREAK_FAULT;
		पूर्ण
		shअगरt = 2;
		अवरोध;
	हाल AARCH64_INSN_VARIANT_64BIT:
		अगर ((offset & 0x7) || (offset < -512) || (offset > 504)) अणु
			pr_err("%s: offset must be multiples of 8 in the range of [-512, 504] %d\n",
			       __func__, offset);
			वापस AARCH64_BREAK_FAULT;
		पूर्ण
		shअगरt = 3;
		insn |= AARCH64_INSN_SF_BIT;
		अवरोध;
	शेष:
		pr_err("%s: unknown variant encoding %d\n", __func__, variant);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RT, insn,
					    reg1);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RT2, insn,
					    reg2);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn,
					    base);

	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_7, insn,
					     offset >> shअगरt);
पूर्ण

u32 aarch64_insn_gen_load_store_ex(क्रमागत aarch64_insn_रेजिस्टर reg,
				   क्रमागत aarch64_insn_रेजिस्टर base,
				   क्रमागत aarch64_insn_रेजिस्टर state,
				   क्रमागत aarch64_insn_माप_प्रकारype size,
				   क्रमागत aarch64_insn_ldst_type type)
अणु
	u32 insn;

	चयन (type) अणु
	हाल AARCH64_INSN_LDST_LOAD_EX:
		insn = aarch64_insn_get_load_ex_value();
		अवरोध;
	हाल AARCH64_INSN_LDST_STORE_EX:
		insn = aarch64_insn_get_store_ex_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown load/store exclusive encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn = aarch64_insn_encode_ldst_size(size, insn);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RT, insn,
					    reg);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn,
					    base);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RT2, insn,
					    AARCH64_INSN_REG_ZR);

	वापस aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RS, insn,
					    state);
पूर्ण

u32 aarch64_insn_gen_ldadd(क्रमागत aarch64_insn_रेजिस्टर result,
			   क्रमागत aarch64_insn_रेजिस्टर address,
			   क्रमागत aarch64_insn_रेजिस्टर value,
			   क्रमागत aarch64_insn_माप_प्रकारype size)
अणु
	u32 insn = aarch64_insn_get_ldadd_value();

	चयन (size) अणु
	हाल AARCH64_INSN_SIZE_32:
	हाल AARCH64_INSN_SIZE_64:
		अवरोध;
	शेष:
		pr_err("%s: unimplemented size encoding %d\n", __func__, size);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn = aarch64_insn_encode_ldst_size(size, insn);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RT, insn,
					    result);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn,
					    address);

	वापस aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RS, insn,
					    value);
पूर्ण

u32 aarch64_insn_gen_stadd(क्रमागत aarch64_insn_रेजिस्टर address,
			   क्रमागत aarch64_insn_रेजिस्टर value,
			   क्रमागत aarch64_insn_माप_प्रकारype size)
अणु
	/*
	 * STADD is simply encoded as an alias क्रम LDADD with XZR as
	 * the destination रेजिस्टर.
	 */
	वापस aarch64_insn_gen_ldadd(AARCH64_INSN_REG_ZR, address,
				      value, size);
पूर्ण

अटल u32 aarch64_insn_encode_prfm_imm(क्रमागत aarch64_insn_prfm_type type,
					क्रमागत aarch64_insn_prfm_target target,
					क्रमागत aarch64_insn_prfm_policy policy,
					u32 insn)
अणु
	u32 imm_type = 0, imm_target = 0, imm_policy = 0;

	चयन (type) अणु
	हाल AARCH64_INSN_PRFM_TYPE_PLD:
		अवरोध;
	हाल AARCH64_INSN_PRFM_TYPE_PLI:
		imm_type = BIT(0);
		अवरोध;
	हाल AARCH64_INSN_PRFM_TYPE_PST:
		imm_type = BIT(1);
		अवरोध;
	शेष:
		pr_err("%s: unknown prfm type encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (target) अणु
	हाल AARCH64_INSN_PRFM_TARGET_L1:
		अवरोध;
	हाल AARCH64_INSN_PRFM_TARGET_L2:
		imm_target = BIT(0);
		अवरोध;
	हाल AARCH64_INSN_PRFM_TARGET_L3:
		imm_target = BIT(1);
		अवरोध;
	शेष:
		pr_err("%s: unknown prfm target encoding %d\n", __func__, target);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (policy) अणु
	हाल AARCH64_INSN_PRFM_POLICY_KEEP:
		अवरोध;
	हाल AARCH64_INSN_PRFM_POLICY_STRM:
		imm_policy = BIT(0);
		अवरोध;
	शेष:
		pr_err("%s: unknown prfm policy encoding %d\n", __func__, policy);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	/* In this हाल, imm5 is encoded पूर्णांकo Rt field. */
	insn &= ~GENMASK(4, 0);
	insn |= imm_policy | (imm_target << 1) | (imm_type << 3);

	वापस insn;
पूर्ण

u32 aarch64_insn_gen_prefetch(क्रमागत aarch64_insn_रेजिस्टर base,
			      क्रमागत aarch64_insn_prfm_type type,
			      क्रमागत aarch64_insn_prfm_target target,
			      क्रमागत aarch64_insn_prfm_policy policy)
अणु
	u32 insn = aarch64_insn_get_prfm_value();

	insn = aarch64_insn_encode_ldst_size(AARCH64_INSN_SIZE_64, insn);

	insn = aarch64_insn_encode_prfm_imm(type, target, policy, insn);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn,
					    base);

	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_12, insn, 0);
पूर्ण

u32 aarch64_insn_gen_add_sub_imm(क्रमागत aarch64_insn_रेजिस्टर dst,
				 क्रमागत aarch64_insn_रेजिस्टर src,
				 पूर्णांक imm, क्रमागत aarch64_insn_variant variant,
				 क्रमागत aarch64_insn_adsb_type type)
अणु
	u32 insn;

	चयन (type) अणु
	हाल AARCH64_INSN_ADSB_ADD:
		insn = aarch64_insn_get_add_imm_value();
		अवरोध;
	हाल AARCH64_INSN_ADSB_SUB:
		insn = aarch64_insn_get_sub_imm_value();
		अवरोध;
	हाल AARCH64_INSN_ADSB_ADD_SETFLAGS:
		insn = aarch64_insn_get_adds_imm_value();
		अवरोध;
	हाल AARCH64_INSN_ADSB_SUB_SETFLAGS:
		insn = aarch64_insn_get_subs_imm_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown add/sub encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (variant) अणु
	हाल AARCH64_INSN_VARIANT_32BIT:
		अवरोध;
	हाल AARCH64_INSN_VARIANT_64BIT:
		insn |= AARCH64_INSN_SF_BIT;
		अवरोध;
	शेष:
		pr_err("%s: unknown variant encoding %d\n", __func__, variant);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	/* We can't encode more than a 24bit value (12bit + 12bit shअगरt) */
	अगर (imm & ~(BIT(24) - 1))
		जाओ out;

	/* If we have something in the top 12 bits... */
	अगर (imm & ~(SZ_4K - 1)) अणु
		/* ... and in the low 12 bits -> error */
		अगर (imm & (SZ_4K - 1))
			जाओ out;

		imm >>= 12;
		insn |= AARCH64_INSN_LSL_12;
	पूर्ण

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, insn, dst);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn, src);

	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_12, insn, imm);

out:
	pr_err("%s: invalid immediate encoding %d\n", __func__, imm);
	वापस AARCH64_BREAK_FAULT;
पूर्ण

u32 aarch64_insn_gen_bitfield(क्रमागत aarch64_insn_रेजिस्टर dst,
			      क्रमागत aarch64_insn_रेजिस्टर src,
			      पूर्णांक immr, पूर्णांक imms,
			      क्रमागत aarch64_insn_variant variant,
			      क्रमागत aarch64_insn_bitfield_type type)
अणु
	u32 insn;
	u32 mask;

	चयन (type) अणु
	हाल AARCH64_INSN_BITFIELD_MOVE:
		insn = aarch64_insn_get_bfm_value();
		अवरोध;
	हाल AARCH64_INSN_BITFIELD_MOVE_UNSIGNED:
		insn = aarch64_insn_get_ubfm_value();
		अवरोध;
	हाल AARCH64_INSN_BITFIELD_MOVE_SIGNED:
		insn = aarch64_insn_get_sbfm_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown bitfield encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (variant) अणु
	हाल AARCH64_INSN_VARIANT_32BIT:
		mask = GENMASK(4, 0);
		अवरोध;
	हाल AARCH64_INSN_VARIANT_64BIT:
		insn |= AARCH64_INSN_SF_BIT | AARCH64_INSN_N_BIT;
		mask = GENMASK(5, 0);
		अवरोध;
	शेष:
		pr_err("%s: unknown variant encoding %d\n", __func__, variant);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	अगर (immr & ~mask) अणु
		pr_err("%s: invalid immr encoding %d\n", __func__, immr);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण
	अगर (imms & ~mask) अणु
		pr_err("%s: invalid imms encoding %d\n", __func__, imms);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, insn, dst);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn, src);

	insn = aarch64_insn_encode_immediate(AARCH64_INSN_IMM_R, insn, immr);

	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_S, insn, imms);
पूर्ण

u32 aarch64_insn_gen_movewide(क्रमागत aarch64_insn_रेजिस्टर dst,
			      पूर्णांक imm, पूर्णांक shअगरt,
			      क्रमागत aarch64_insn_variant variant,
			      क्रमागत aarch64_insn_movewide_type type)
अणु
	u32 insn;

	चयन (type) अणु
	हाल AARCH64_INSN_MOVEWIDE_ZERO:
		insn = aarch64_insn_get_movz_value();
		अवरोध;
	हाल AARCH64_INSN_MOVEWIDE_KEEP:
		insn = aarch64_insn_get_movk_value();
		अवरोध;
	हाल AARCH64_INSN_MOVEWIDE_INVERSE:
		insn = aarch64_insn_get_movn_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown movewide encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	अगर (imm & ~(SZ_64K - 1)) अणु
		pr_err("%s: invalid immediate encoding %d\n", __func__, imm);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (variant) अणु
	हाल AARCH64_INSN_VARIANT_32BIT:
		अगर (shअगरt != 0 && shअगरt != 16) अणु
			pr_err("%s: invalid shift encoding %d\n", __func__,
			       shअगरt);
			वापस AARCH64_BREAK_FAULT;
		पूर्ण
		अवरोध;
	हाल AARCH64_INSN_VARIANT_64BIT:
		insn |= AARCH64_INSN_SF_BIT;
		अगर (shअगरt != 0 && shअगरt != 16 && shअगरt != 32 && shअगरt != 48) अणु
			pr_err("%s: invalid shift encoding %d\n", __func__,
			       shअगरt);
			वापस AARCH64_BREAK_FAULT;
		पूर्ण
		अवरोध;
	शेष:
		pr_err("%s: unknown variant encoding %d\n", __func__, variant);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn |= (shअगरt >> 4) << 21;

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, insn, dst);

	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_16, insn, imm);
पूर्ण

u32 aarch64_insn_gen_add_sub_shअगरted_reg(क्रमागत aarch64_insn_रेजिस्टर dst,
					 क्रमागत aarch64_insn_रेजिस्टर src,
					 क्रमागत aarch64_insn_रेजिस्टर reg,
					 पूर्णांक shअगरt,
					 क्रमागत aarch64_insn_variant variant,
					 क्रमागत aarch64_insn_adsb_type type)
अणु
	u32 insn;

	चयन (type) अणु
	हाल AARCH64_INSN_ADSB_ADD:
		insn = aarch64_insn_get_add_value();
		अवरोध;
	हाल AARCH64_INSN_ADSB_SUB:
		insn = aarch64_insn_get_sub_value();
		अवरोध;
	हाल AARCH64_INSN_ADSB_ADD_SETFLAGS:
		insn = aarch64_insn_get_adds_value();
		अवरोध;
	हाल AARCH64_INSN_ADSB_SUB_SETFLAGS:
		insn = aarch64_insn_get_subs_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown add/sub encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (variant) अणु
	हाल AARCH64_INSN_VARIANT_32BIT:
		अगर (shअगरt & ~(SZ_32 - 1)) अणु
			pr_err("%s: invalid shift encoding %d\n", __func__,
			       shअगरt);
			वापस AARCH64_BREAK_FAULT;
		पूर्ण
		अवरोध;
	हाल AARCH64_INSN_VARIANT_64BIT:
		insn |= AARCH64_INSN_SF_BIT;
		अगर (shअगरt & ~(SZ_64 - 1)) अणु
			pr_err("%s: invalid shift encoding %d\n", __func__,
			       shअगरt);
			वापस AARCH64_BREAK_FAULT;
		पूर्ण
		अवरोध;
	शेष:
		pr_err("%s: unknown variant encoding %d\n", __func__, variant);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण


	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, insn, dst);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn, src);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RM, insn, reg);

	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_6, insn, shअगरt);
पूर्ण

u32 aarch64_insn_gen_data1(क्रमागत aarch64_insn_रेजिस्टर dst,
			   क्रमागत aarch64_insn_रेजिस्टर src,
			   क्रमागत aarch64_insn_variant variant,
			   क्रमागत aarch64_insn_data1_type type)
अणु
	u32 insn;

	चयन (type) अणु
	हाल AARCH64_INSN_DATA1_REVERSE_16:
		insn = aarch64_insn_get_rev16_value();
		अवरोध;
	हाल AARCH64_INSN_DATA1_REVERSE_32:
		insn = aarch64_insn_get_rev32_value();
		अवरोध;
	हाल AARCH64_INSN_DATA1_REVERSE_64:
		अगर (variant != AARCH64_INSN_VARIANT_64BIT) अणु
			pr_err("%s: invalid variant for reverse64 %d\n",
			       __func__, variant);
			वापस AARCH64_BREAK_FAULT;
		पूर्ण
		insn = aarch64_insn_get_rev64_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown data1 encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (variant) अणु
	हाल AARCH64_INSN_VARIANT_32BIT:
		अवरोध;
	हाल AARCH64_INSN_VARIANT_64BIT:
		insn |= AARCH64_INSN_SF_BIT;
		अवरोध;
	शेष:
		pr_err("%s: unknown variant encoding %d\n", __func__, variant);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, insn, dst);

	वापस aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn, src);
पूर्ण

u32 aarch64_insn_gen_data2(क्रमागत aarch64_insn_रेजिस्टर dst,
			   क्रमागत aarch64_insn_रेजिस्टर src,
			   क्रमागत aarch64_insn_रेजिस्टर reg,
			   क्रमागत aarch64_insn_variant variant,
			   क्रमागत aarch64_insn_data2_type type)
अणु
	u32 insn;

	चयन (type) अणु
	हाल AARCH64_INSN_DATA2_UDIV:
		insn = aarch64_insn_get_uभाग_value();
		अवरोध;
	हाल AARCH64_INSN_DATA2_SDIV:
		insn = aarch64_insn_get_sभाग_value();
		अवरोध;
	हाल AARCH64_INSN_DATA2_LSLV:
		insn = aarch64_insn_get_lslv_value();
		अवरोध;
	हाल AARCH64_INSN_DATA2_LSRV:
		insn = aarch64_insn_get_lsrv_value();
		अवरोध;
	हाल AARCH64_INSN_DATA2_ASRV:
		insn = aarch64_insn_get_asrv_value();
		अवरोध;
	हाल AARCH64_INSN_DATA2_RORV:
		insn = aarch64_insn_get_rorv_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown data2 encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (variant) अणु
	हाल AARCH64_INSN_VARIANT_32BIT:
		अवरोध;
	हाल AARCH64_INSN_VARIANT_64BIT:
		insn |= AARCH64_INSN_SF_BIT;
		अवरोध;
	शेष:
		pr_err("%s: unknown variant encoding %d\n", __func__, variant);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, insn, dst);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn, src);

	वापस aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RM, insn, reg);
पूर्ण

u32 aarch64_insn_gen_data3(क्रमागत aarch64_insn_रेजिस्टर dst,
			   क्रमागत aarch64_insn_रेजिस्टर src,
			   क्रमागत aarch64_insn_रेजिस्टर reg1,
			   क्रमागत aarch64_insn_रेजिस्टर reg2,
			   क्रमागत aarch64_insn_variant variant,
			   क्रमागत aarch64_insn_data3_type type)
अणु
	u32 insn;

	चयन (type) अणु
	हाल AARCH64_INSN_DATA3_MADD:
		insn = aarch64_insn_get_madd_value();
		अवरोध;
	हाल AARCH64_INSN_DATA3_MSUB:
		insn = aarch64_insn_get_msub_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown data3 encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (variant) अणु
	हाल AARCH64_INSN_VARIANT_32BIT:
		अवरोध;
	हाल AARCH64_INSN_VARIANT_64BIT:
		insn |= AARCH64_INSN_SF_BIT;
		अवरोध;
	शेष:
		pr_err("%s: unknown variant encoding %d\n", __func__, variant);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, insn, dst);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RA, insn, src);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn,
					    reg1);

	वापस aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RM, insn,
					    reg2);
पूर्ण

u32 aarch64_insn_gen_logical_shअगरted_reg(क्रमागत aarch64_insn_रेजिस्टर dst,
					 क्रमागत aarch64_insn_रेजिस्टर src,
					 क्रमागत aarch64_insn_रेजिस्टर reg,
					 पूर्णांक shअगरt,
					 क्रमागत aarch64_insn_variant variant,
					 क्रमागत aarch64_insn_logic_type type)
अणु
	u32 insn;

	चयन (type) अणु
	हाल AARCH64_INSN_LOGIC_AND:
		insn = aarch64_insn_get_and_value();
		अवरोध;
	हाल AARCH64_INSN_LOGIC_BIC:
		insn = aarch64_insn_get_bic_value();
		अवरोध;
	हाल AARCH64_INSN_LOGIC_ORR:
		insn = aarch64_insn_get_orr_value();
		अवरोध;
	हाल AARCH64_INSN_LOGIC_ORN:
		insn = aarch64_insn_get_orn_value();
		अवरोध;
	हाल AARCH64_INSN_LOGIC_EOR:
		insn = aarch64_insn_get_eor_value();
		अवरोध;
	हाल AARCH64_INSN_LOGIC_EON:
		insn = aarch64_insn_get_eon_value();
		अवरोध;
	हाल AARCH64_INSN_LOGIC_AND_SETFLAGS:
		insn = aarch64_insn_get_ands_value();
		अवरोध;
	हाल AARCH64_INSN_LOGIC_BIC_SETFLAGS:
		insn = aarch64_insn_get_bics_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown logical encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	चयन (variant) अणु
	हाल AARCH64_INSN_VARIANT_32BIT:
		अगर (shअगरt & ~(SZ_32 - 1)) अणु
			pr_err("%s: invalid shift encoding %d\n", __func__,
			       shअगरt);
			वापस AARCH64_BREAK_FAULT;
		पूर्ण
		अवरोध;
	हाल AARCH64_INSN_VARIANT_64BIT:
		insn |= AARCH64_INSN_SF_BIT;
		अगर (shअगरt & ~(SZ_64 - 1)) अणु
			pr_err("%s: invalid shift encoding %d\n", __func__,
			       shअगरt);
			वापस AARCH64_BREAK_FAULT;
		पूर्ण
		अवरोध;
	शेष:
		pr_err("%s: unknown variant encoding %d\n", __func__, variant);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण


	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, insn, dst);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn, src);

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RM, insn, reg);

	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_6, insn, shअगरt);
पूर्ण

/*
 * MOV (रेजिस्टर) is architecturally an alias of ORR (shअगरted रेजिस्टर) where
 * MOV <*d>, <*m> is equivalent to ORR <*d>, <*ZR>, <*m>
 */
u32 aarch64_insn_gen_move_reg(क्रमागत aarch64_insn_रेजिस्टर dst,
			      क्रमागत aarch64_insn_रेजिस्टर src,
			      क्रमागत aarch64_insn_variant variant)
अणु
	वापस aarch64_insn_gen_logical_shअगरted_reg(dst, AARCH64_INSN_REG_ZR,
						    src, 0, variant,
						    AARCH64_INSN_LOGIC_ORR);
पूर्ण

u32 aarch64_insn_gen_adr(अचिन्हित दीर्घ pc, अचिन्हित दीर्घ addr,
			 क्रमागत aarch64_insn_रेजिस्टर reg,
			 क्रमागत aarch64_insn_adr_type type)
अणु
	u32 insn;
	s32 offset;

	चयन (type) अणु
	हाल AARCH64_INSN_ADR_TYPE_ADR:
		insn = aarch64_insn_get_adr_value();
		offset = addr - pc;
		अवरोध;
	हाल AARCH64_INSN_ADR_TYPE_ADRP:
		insn = aarch64_insn_get_adrp_value();
		offset = (addr - ALIGN_DOWN(pc, SZ_4K)) >> 12;
		अवरोध;
	शेष:
		pr_err("%s: unknown adr encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	अगर (offset < -SZ_1M || offset >= SZ_1M)
		वापस AARCH64_BREAK_FAULT;

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, insn, reg);

	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_ADR, insn, offset);
पूर्ण

/*
 * Decode the imm field of a branch, and वापस the byte offset as a
 * चिन्हित value (so it can be used when computing a new branch
 * target).
 */
s32 aarch64_get_branch_offset(u32 insn)
अणु
	s32 imm;

	अगर (aarch64_insn_is_b(insn) || aarch64_insn_is_bl(insn)) अणु
		imm = aarch64_insn_decode_immediate(AARCH64_INSN_IMM_26, insn);
		वापस (imm << 6) >> 4;
	पूर्ण

	अगर (aarch64_insn_is_cbz(insn) || aarch64_insn_is_cbnz(insn) ||
	    aarch64_insn_is_bcond(insn)) अणु
		imm = aarch64_insn_decode_immediate(AARCH64_INSN_IMM_19, insn);
		वापस (imm << 13) >> 11;
	पूर्ण

	अगर (aarch64_insn_is_tbz(insn) || aarch64_insn_is_tbnz(insn)) अणु
		imm = aarch64_insn_decode_immediate(AARCH64_INSN_IMM_14, insn);
		वापस (imm << 18) >> 16;
	पूर्ण

	/* Unhandled inकाष्ठाion */
	BUG();
पूर्ण

/*
 * Encode the displacement of a branch in the imm field and वापस the
 * updated inकाष्ठाion.
 */
u32 aarch64_set_branch_offset(u32 insn, s32 offset)
अणु
	अगर (aarch64_insn_is_b(insn) || aarch64_insn_is_bl(insn))
		वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_26, insn,
						     offset >> 2);

	अगर (aarch64_insn_is_cbz(insn) || aarch64_insn_is_cbnz(insn) ||
	    aarch64_insn_is_bcond(insn))
		वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_19, insn,
						     offset >> 2);

	अगर (aarch64_insn_is_tbz(insn) || aarch64_insn_is_tbnz(insn))
		वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_14, insn,
						     offset >> 2);

	/* Unhandled inकाष्ठाion */
	BUG();
पूर्ण

s32 aarch64_insn_adrp_get_offset(u32 insn)
अणु
	BUG_ON(!aarch64_insn_is_adrp(insn));
	वापस aarch64_insn_decode_immediate(AARCH64_INSN_IMM_ADR, insn) << 12;
पूर्ण

u32 aarch64_insn_adrp_set_offset(u32 insn, s32 offset)
अणु
	BUG_ON(!aarch64_insn_is_adrp(insn));
	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_ADR, insn,
						offset >> 12);
पूर्ण

/*
 * Extract the Op/CR data from a msr/mrs inकाष्ठाion.
 */
u32 aarch64_insn_extract_प्रणाली_reg(u32 insn)
अणु
	वापस (insn & 0x1FFFE0) >> 5;
पूर्ण

bool aarch32_insn_is_wide(u32 insn)
अणु
	वापस insn >= 0xe800;
पूर्ण

/*
 * Macros/defines क्रम extracting रेजिस्टर numbers from inकाष्ठाion.
 */
u32 aarch32_insn_extract_reg_num(u32 insn, पूर्णांक offset)
अणु
	वापस (insn & (0xf << offset)) >> offset;
पूर्ण

#घोषणा OPC2_MASK	0x7
#घोषणा OPC2_OFFSET	5
u32 aarch32_insn_mcr_extract_opc2(u32 insn)
अणु
	वापस (insn & (OPC2_MASK << OPC2_OFFSET)) >> OPC2_OFFSET;
पूर्ण

#घोषणा CRM_MASK	0xf
u32 aarch32_insn_mcr_extract_crm(u32 insn)
अणु
	वापस insn & CRM_MASK;
पूर्ण

अटल bool __kprobes __check_eq(अचिन्हित दीर्घ pstate)
अणु
	वापस (pstate & PSR_Z_BIT) != 0;
पूर्ण

अटल bool __kprobes __check_ne(अचिन्हित दीर्घ pstate)
अणु
	वापस (pstate & PSR_Z_BIT) == 0;
पूर्ण

अटल bool __kprobes __check_cs(अचिन्हित दीर्घ pstate)
अणु
	वापस (pstate & PSR_C_BIT) != 0;
पूर्ण

अटल bool __kprobes __check_cc(अचिन्हित दीर्घ pstate)
अणु
	वापस (pstate & PSR_C_BIT) == 0;
पूर्ण

अटल bool __kprobes __check_mi(अचिन्हित दीर्घ pstate)
अणु
	वापस (pstate & PSR_N_BIT) != 0;
पूर्ण

अटल bool __kprobes __check_pl(अचिन्हित दीर्घ pstate)
अणु
	वापस (pstate & PSR_N_BIT) == 0;
पूर्ण

अटल bool __kprobes __check_vs(अचिन्हित दीर्घ pstate)
अणु
	वापस (pstate & PSR_V_BIT) != 0;
पूर्ण

अटल bool __kprobes __check_vc(अचिन्हित दीर्घ pstate)
अणु
	वापस (pstate & PSR_V_BIT) == 0;
पूर्ण

अटल bool __kprobes __check_hi(अचिन्हित दीर्घ pstate)
अणु
	pstate &= ~(pstate >> 1);	/* PSR_C_BIT &= ~PSR_Z_BIT */
	वापस (pstate & PSR_C_BIT) != 0;
पूर्ण

अटल bool __kprobes __check_ls(अचिन्हित दीर्घ pstate)
अणु
	pstate &= ~(pstate >> 1);	/* PSR_C_BIT &= ~PSR_Z_BIT */
	वापस (pstate & PSR_C_BIT) == 0;
पूर्ण

अटल bool __kprobes __check_ge(अचिन्हित दीर्घ pstate)
अणु
	pstate ^= (pstate << 3);	/* PSR_N_BIT ^= PSR_V_BIT */
	वापस (pstate & PSR_N_BIT) == 0;
पूर्ण

अटल bool __kprobes __check_lt(अचिन्हित दीर्घ pstate)
अणु
	pstate ^= (pstate << 3);	/* PSR_N_BIT ^= PSR_V_BIT */
	वापस (pstate & PSR_N_BIT) != 0;
पूर्ण

अटल bool __kprobes __check_gt(अचिन्हित दीर्घ pstate)
अणु
	/*PSR_N_BIT ^= PSR_V_BIT */
	अचिन्हित दीर्घ temp = pstate ^ (pstate << 3);

	temp |= (pstate << 1);	/*PSR_N_BIT |= PSR_Z_BIT */
	वापस (temp & PSR_N_BIT) == 0;
पूर्ण

अटल bool __kprobes __check_le(अचिन्हित दीर्घ pstate)
अणु
	/*PSR_N_BIT ^= PSR_V_BIT */
	अचिन्हित दीर्घ temp = pstate ^ (pstate << 3);

	temp |= (pstate << 1);	/*PSR_N_BIT |= PSR_Z_BIT */
	वापस (temp & PSR_N_BIT) != 0;
पूर्ण

अटल bool __kprobes __check_al(अचिन्हित दीर्घ pstate)
अणु
	वापस true;
पूर्ण

/*
 * Note that the ARMv8 ARM calls condition code 0b1111 "nv", but states that
 * it behaves identically to 0b1110 ("al").
 */
pstate_check_t * स्थिर aarch32_opcode_cond_checks[16] = अणु
	__check_eq, __check_ne, __check_cs, __check_cc,
	__check_mi, __check_pl, __check_vs, __check_vc,
	__check_hi, __check_ls, __check_ge, __check_lt,
	__check_gt, __check_le, __check_al, __check_al
पूर्ण;

अटल bool range_of_ones(u64 val)
अणु
	/* Doesn't handle full ones or full zeroes */
	u64 sval = val >> __ffs64(val);

	/* One of Sean Eron Anderson's bithack tricks */
	वापस ((sval + 1) & (sval)) == 0;
पूर्ण

अटल u32 aarch64_encode_immediate(u64 imm,
				    क्रमागत aarch64_insn_variant variant,
				    u32 insn)
अणु
	अचिन्हित पूर्णांक immr, imms, n, ones, ror, esz, पंचांगp;
	u64 mask;

	चयन (variant) अणु
	हाल AARCH64_INSN_VARIANT_32BIT:
		esz = 32;
		अवरोध;
	हाल AARCH64_INSN_VARIANT_64BIT:
		insn |= AARCH64_INSN_SF_BIT;
		esz = 64;
		अवरोध;
	शेष:
		pr_err("%s: unknown variant encoding %d\n", __func__, variant);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	mask = GENMASK(esz - 1, 0);

	/* Can't encode full zeroes, full ones, or value wider than the mask */
	अगर (!imm || imm == mask || imm & ~mask)
		वापस AARCH64_BREAK_FAULT;

	/*
	 * Inverse of Replicate(). Try to spot a repeating pattern
	 * with a घात2 stride.
	 */
	क्रम (पंचांगp = esz / 2; पंचांगp >= 2; पंचांगp /= 2) अणु
		u64 emask = BIT(पंचांगp) - 1;

		अगर ((imm & emask) != ((imm >> पंचांगp) & emask))
			अवरोध;

		esz = पंचांगp;
		mask = emask;
	पूर्ण

	/* N is only set अगर we're encoding a 64bit value */
	n = esz == 64;

	/* Trim imm to the element size */
	imm &= mask;

	/* That's how many ones we need to encode */
	ones = hweight64(imm);

	/*
	 * imms is set to (ones - 1), prefixed with a string of ones
	 * and a zero अगर they fit. Cap it to 6 bits.
	 */
	imms  = ones - 1;
	imms |= 0xf << ffs(esz);
	imms &= BIT(6) - 1;

	/* Compute the rotation */
	अगर (range_of_ones(imm)) अणु
		/*
		 * Pattern: 0..01..10..0
		 *
		 * Compute how many rotate we need to align it right
		 */
		ror = __ffs64(imm);
	पूर्ण अन्यथा अणु
		/*
		 * Pattern: 0..01..10..01..1
		 *
		 * Fill the unused top bits with ones, and check अगर
		 * the result is a valid immediate (all ones with a
		 * contiguous ranges of zeroes).
		 */
		imm |= ~mask;
		अगर (!range_of_ones(~imm))
			वापस AARCH64_BREAK_FAULT;

		/*
		 * Compute the rotation to get a continuous set of
		 * ones, with the first bit set at position 0
		 */
		ror = fls(~imm);
	पूर्ण

	/*
	 * immr is the number of bits we need to rotate back to the
	 * original set of ones. Note that this is relative to the
	 * element size...
	 */
	immr = (esz - ror) % esz;

	insn = aarch64_insn_encode_immediate(AARCH64_INSN_IMM_N, insn, n);
	insn = aarch64_insn_encode_immediate(AARCH64_INSN_IMM_R, insn, immr);
	वापस aarch64_insn_encode_immediate(AARCH64_INSN_IMM_S, insn, imms);
पूर्ण

u32 aarch64_insn_gen_logical_immediate(क्रमागत aarch64_insn_logic_type type,
				       क्रमागत aarch64_insn_variant variant,
				       क्रमागत aarch64_insn_रेजिस्टर Rn,
				       क्रमागत aarch64_insn_रेजिस्टर Rd,
				       u64 imm)
अणु
	u32 insn;

	चयन (type) अणु
	हाल AARCH64_INSN_LOGIC_AND:
		insn = aarch64_insn_get_and_imm_value();
		अवरोध;
	हाल AARCH64_INSN_LOGIC_ORR:
		insn = aarch64_insn_get_orr_imm_value();
		अवरोध;
	हाल AARCH64_INSN_LOGIC_EOR:
		insn = aarch64_insn_get_eor_imm_value();
		अवरोध;
	हाल AARCH64_INSN_LOGIC_AND_SETFLAGS:
		insn = aarch64_insn_get_ands_imm_value();
		अवरोध;
	शेष:
		pr_err("%s: unknown logical encoding %d\n", __func__, type);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, insn, Rd);
	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn, Rn);
	वापस aarch64_encode_immediate(imm, variant, insn);
पूर्ण

u32 aarch64_insn_gen_extr(क्रमागत aarch64_insn_variant variant,
			  क्रमागत aarch64_insn_रेजिस्टर Rm,
			  क्रमागत aarch64_insn_रेजिस्टर Rn,
			  क्रमागत aarch64_insn_रेजिस्टर Rd,
			  u8 lsb)
अणु
	u32 insn;

	insn = aarch64_insn_get_extr_value();

	चयन (variant) अणु
	हाल AARCH64_INSN_VARIANT_32BIT:
		अगर (lsb > 31)
			वापस AARCH64_BREAK_FAULT;
		अवरोध;
	हाल AARCH64_INSN_VARIANT_64BIT:
		अगर (lsb > 63)
			वापस AARCH64_BREAK_FAULT;
		insn |= AARCH64_INSN_SF_BIT;
		insn = aarch64_insn_encode_immediate(AARCH64_INSN_IMM_N, insn, 1);
		अवरोध;
	शेष:
		pr_err("%s: unknown variant encoding %d\n", __func__, variant);
		वापस AARCH64_BREAK_FAULT;
	पूर्ण

	insn = aarch64_insn_encode_immediate(AARCH64_INSN_IMM_S, insn, lsb);
	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, insn, Rd);
	insn = aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, insn, Rn);
	वापस aarch64_insn_encode_रेजिस्टर(AARCH64_INSN_REGTYPE_RM, insn, Rm);
पूर्ण
