<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 ARM Ltd.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/memory.h>

/*
 * The LSB of the HYP VA tag
 */
अटल u8 tag_lsb;
/*
 * The HYP VA tag value with the region bit
 */
अटल u64 tag_val;
अटल u64 va_mask;

/*
 * Compute HYP VA by using the same computation as kern_hyp_va().
 */
अटल u64 __early_kern_hyp_va(u64 addr)
अणु
	addr &= va_mask;
	addr |= tag_val << tag_lsb;
	वापस addr;
पूर्ण

/*
 * Store a hyp VA <-> PA offset पूर्णांकo a EL2-owned variable.
 */
अटल व्योम init_hyp_physvirt_offset(व्योम)
अणु
	u64 kern_va, hyp_va;

	/* Compute the offset from the hyp VA and PA of a अक्रमom symbol. */
	kern_va = (u64)lm_alias(__hyp_text_start);
	hyp_va = __early_kern_hyp_va(kern_va);
	hyp_physvirt_offset = (s64)__pa(kern_va) - (s64)hyp_va;
पूर्ण

/*
 * We want to generate a hyp VA with the following क्रमmat (with V ==
 * vabits_actual):
 *
 *  63 ... V |     V-1    | V-2 .. tag_lsb | tag_lsb - 1 .. 0
 *  ---------------------------------------------------------
 * | 0000000 | hyp_va_msb |   अक्रमom tag   |  kern linear VA |
 *           |--------- tag_val -----------|----- va_mask ---|
 *
 * which करोes not conflict with the idmap regions.
 */
__init व्योम kvm_compute_layout(व्योम)
अणु
	phys_addr_t idmap_addr = __pa_symbol(__hyp_idmap_text_start);
	u64 hyp_va_msb;

	/* Where is my RAM region? */
	hyp_va_msb  = idmap_addr & BIT(vabits_actual - 1);
	hyp_va_msb ^= BIT(vabits_actual - 1);

	tag_lsb = fls64((u64)phys_to_virt(memblock_start_of_DRAM()) ^
			(u64)(high_memory - 1));

	va_mask = GENMASK_ULL(tag_lsb - 1, 0);
	tag_val = hyp_va_msb;

	अगर (IS_ENABLED(CONFIG_RANDOMIZE_BASE) && tag_lsb != (vabits_actual - 1)) अणु
		/* We have some मुक्त bits to insert a अक्रमom tag. */
		tag_val |= get_अक्रमom_दीर्घ() & GENMASK_ULL(vabits_actual - 2, tag_lsb);
	पूर्ण
	tag_val >>= tag_lsb;

	init_hyp_physvirt_offset();
पूर्ण

/*
 * The .hyp.reloc ELF section contains a list of kimg positions that
 * contains kimg VAs but will be accessed only in hyp execution context.
 * Convert them to hyp VAs. See gen-hyprel.c क्रम more details.
 */
__init व्योम kvm_apply_hyp_relocations(व्योम)
अणु
	पूर्णांक32_t *rel;
	पूर्णांक32_t *begin = (पूर्णांक32_t *)__hyp_reloc_begin;
	पूर्णांक32_t *end = (पूर्णांक32_t *)__hyp_reloc_end;

	क्रम (rel = begin; rel < end; ++rel) अणु
		uपूर्णांकptr_t *ptr, kimg_va;

		/*
		 * Each entry contains a 32-bit relative offset from itself
		 * to a kimg VA position.
		 */
		ptr = (uपूर्णांकptr_t *)lm_alias((अक्षर *)rel + *rel);

		/* Read the kimg VA value at the relocation address. */
		kimg_va = *ptr;

		/* Convert to hyp VA and store back to the relocation address. */
		*ptr = __early_kern_hyp_va((uपूर्णांकptr_t)lm_alias(kimg_va));
	पूर्ण
पूर्ण

अटल u32 compute_inकाष्ठाion(पूर्णांक n, u32 rd, u32 rn)
अणु
	u32 insn = AARCH64_BREAK_FAULT;

	चयन (n) अणु
	हाल 0:
		insn = aarch64_insn_gen_logical_immediate(AARCH64_INSN_LOGIC_AND,
							  AARCH64_INSN_VARIANT_64BIT,
							  rn, rd, va_mask);
		अवरोध;

	हाल 1:
		/* ROR is a variant of EXTR with Rm = Rn */
		insn = aarch64_insn_gen_extr(AARCH64_INSN_VARIANT_64BIT,
					     rn, rn, rd,
					     tag_lsb);
		अवरोध;

	हाल 2:
		insn = aarch64_insn_gen_add_sub_imm(rd, rn,
						    tag_val & GENMASK(11, 0),
						    AARCH64_INSN_VARIANT_64BIT,
						    AARCH64_INSN_ADSB_ADD);
		अवरोध;

	हाल 3:
		insn = aarch64_insn_gen_add_sub_imm(rd, rn,
						    tag_val & GENMASK(23, 12),
						    AARCH64_INSN_VARIANT_64BIT,
						    AARCH64_INSN_ADSB_ADD);
		अवरोध;

	हाल 4:
		/* ROR is a variant of EXTR with Rm = Rn */
		insn = aarch64_insn_gen_extr(AARCH64_INSN_VARIANT_64BIT,
					     rn, rn, rd, 64 - tag_lsb);
		अवरोध;
	पूर्ण

	वापस insn;
पूर्ण

व्योम __init kvm_update_va_mask(काष्ठा alt_instr *alt,
			       __le32 *origptr, __le32 *updptr, पूर्णांक nr_inst)
अणु
	पूर्णांक i;

	BUG_ON(nr_inst != 5);

	क्रम (i = 0; i < nr_inst; i++) अणु
		u32 rd, rn, insn, oinsn;

		/*
		 * VHE करोesn't need any address translation, let's NOP
		 * everything.
		 *
		 * Alternatively, अगर the tag is zero (because the layout
		 * dictates it and we करोn't have any spare bits in the
		 * address), NOP everything after masking the kernel VA.
		 */
		अगर (has_vhe() || (!tag_val && i > 0)) अणु
			updptr[i] = cpu_to_le32(aarch64_insn_gen_nop());
			जारी;
		पूर्ण

		oinsn = le32_to_cpu(origptr[i]);
		rd = aarch64_insn_decode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, oinsn);
		rn = aarch64_insn_decode_रेजिस्टर(AARCH64_INSN_REGTYPE_RN, oinsn);

		insn = compute_inकाष्ठाion(i, rd, rn);
		BUG_ON(insn == AARCH64_BREAK_FAULT);

		updptr[i] = cpu_to_le32(insn);
	पूर्ण
पूर्ण

व्योम kvm_patch_vector_branch(काष्ठा alt_instr *alt,
			     __le32 *origptr, __le32 *updptr, पूर्णांक nr_inst)
अणु
	u64 addr;
	u32 insn;

	BUG_ON(nr_inst != 4);

	अगर (!cpus_have_स्थिर_cap(ARM64_SPECTRE_V3A) || WARN_ON_ONCE(has_vhe()))
		वापस;

	/*
	 * Compute HYP VA by using the same computation as kern_hyp_va()
	 */
	addr = __early_kern_hyp_va((u64)kvm_ksym_ref(__kvm_hyp_vector));

	/* Use PC[10:7] to branch to the same vector in KVM */
	addr |= ((u64)origptr & GENMASK_ULL(10, 7));

	/*
	 * Branch over the preamble in order to aव्योम the initial store on
	 * the stack (which we alपढ़ोy perक्रमm in the hardening vectors).
	 */
	addr += KVM_VECTOR_PREAMBLE;

	/* movz x0, #(addr & 0xffff) */
	insn = aarch64_insn_gen_movewide(AARCH64_INSN_REG_0,
					 (u16)addr,
					 0,
					 AARCH64_INSN_VARIANT_64BIT,
					 AARCH64_INSN_MOVEWIDE_ZERO);
	*updptr++ = cpu_to_le32(insn);

	/* movk x0, #((addr >> 16) & 0xffff), lsl #16 */
	insn = aarch64_insn_gen_movewide(AARCH64_INSN_REG_0,
					 (u16)(addr >> 16),
					 16,
					 AARCH64_INSN_VARIANT_64BIT,
					 AARCH64_INSN_MOVEWIDE_KEEP);
	*updptr++ = cpu_to_le32(insn);

	/* movk x0, #((addr >> 32) & 0xffff), lsl #32 */
	insn = aarch64_insn_gen_movewide(AARCH64_INSN_REG_0,
					 (u16)(addr >> 32),
					 32,
					 AARCH64_INSN_VARIANT_64BIT,
					 AARCH64_INSN_MOVEWIDE_KEEP);
	*updptr++ = cpu_to_le32(insn);

	/* br x0 */
	insn = aarch64_insn_gen_branch_reg(AARCH64_INSN_REG_0,
					   AARCH64_INSN_BRANCH_NOLINK);
	*updptr++ = cpu_to_le32(insn);
पूर्ण

अटल व्योम generate_mov_q(u64 val, __le32 *origptr, __le32 *updptr, पूर्णांक nr_inst)
अणु
	u32 insn, oinsn, rd;

	BUG_ON(nr_inst != 4);

	/* Compute target रेजिस्टर */
	oinsn = le32_to_cpu(*origptr);
	rd = aarch64_insn_decode_रेजिस्टर(AARCH64_INSN_REGTYPE_RD, oinsn);

	/* movz rd, #(val & 0xffff) */
	insn = aarch64_insn_gen_movewide(rd,
					 (u16)val,
					 0,
					 AARCH64_INSN_VARIANT_64BIT,
					 AARCH64_INSN_MOVEWIDE_ZERO);
	*updptr++ = cpu_to_le32(insn);

	/* movk rd, #((val >> 16) & 0xffff), lsl #16 */
	insn = aarch64_insn_gen_movewide(rd,
					 (u16)(val >> 16),
					 16,
					 AARCH64_INSN_VARIANT_64BIT,
					 AARCH64_INSN_MOVEWIDE_KEEP);
	*updptr++ = cpu_to_le32(insn);

	/* movk rd, #((val >> 32) & 0xffff), lsl #32 */
	insn = aarch64_insn_gen_movewide(rd,
					 (u16)(val >> 32),
					 32,
					 AARCH64_INSN_VARIANT_64BIT,
					 AARCH64_INSN_MOVEWIDE_KEEP);
	*updptr++ = cpu_to_le32(insn);

	/* movk rd, #((val >> 48) & 0xffff), lsl #48 */
	insn = aarch64_insn_gen_movewide(rd,
					 (u16)(val >> 48),
					 48,
					 AARCH64_INSN_VARIANT_64BIT,
					 AARCH64_INSN_MOVEWIDE_KEEP);
	*updptr++ = cpu_to_le32(insn);
पूर्ण

व्योम kvm_get_kimage_voffset(काष्ठा alt_instr *alt,
			    __le32 *origptr, __le32 *updptr, पूर्णांक nr_inst)
अणु
	generate_mov_q(kimage_voffset, origptr, updptr, nr_inst);
पूर्ण

व्योम kvm_compute_final_ctr_el0(काष्ठा alt_instr *alt,
			       __le32 *origptr, __le32 *updptr, पूर्णांक nr_inst)
अणु
	generate_mov_q(पढ़ो_sanitised_ftr_reg(SYS_CTR_EL0),
		       origptr, updptr, nr_inst);
पूर्ण
