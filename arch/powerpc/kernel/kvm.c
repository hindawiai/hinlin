<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 SUSE Linux Products GmbH. All rights reserved.
 * Copyright 2010-2011 Freescale Semiconductor, Inc.
 *
 * Authors:
 *     Alexander Graf <agraf@suse.de>
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/kvm_para.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/pagemap.h>

#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/disassemble.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/epapr_hcalls.h>

#घोषणा KVM_MAGIC_PAGE		(-4096L)
#घोषणा magic_var(x) KVM_MAGIC_PAGE + दुरत्व(काष्ठा kvm_vcpu_arch_shared, x)

#घोषणा KVM_INST_LWZ		0x80000000
#घोषणा KVM_INST_STW		0x90000000
#घोषणा KVM_INST_LD		0xe8000000
#घोषणा KVM_INST_STD		0xf8000000
#घोषणा KVM_INST_NOP		0x60000000
#घोषणा KVM_INST_B		0x48000000
#घोषणा KVM_INST_B_MASK		0x03ffffff
#घोषणा KVM_INST_B_MAX		0x01ffffff
#घोषणा KVM_INST_LI		0x38000000

#घोषणा KVM_MASK_RT		0x03e00000
#घोषणा KVM_RT_30		0x03c00000
#घोषणा KVM_MASK_RB		0x0000f800
#घोषणा KVM_INST_MFMSR		0x7c0000a6

#घोषणा SPR_FROM		0
#घोषणा SPR_TO			0x100

#घोषणा KVM_INST_SPR(sprn, moveto) (0x7c0002a6 | \
				    (((sprn) & 0x1f) << 16) | \
				    (((sprn) & 0x3e0) << 6) | \
				    (moveto))

#घोषणा KVM_INST_MFSPR(sprn)	KVM_INST_SPR(sprn, SPR_FROM)
#घोषणा KVM_INST_MTSPR(sprn)	KVM_INST_SPR(sprn, SPR_TO)

#घोषणा KVM_INST_TLBSYNC	0x7c00046c
#घोषणा KVM_INST_MTMSRD_L0	0x7c000164
#घोषणा KVM_INST_MTMSRD_L1	0x7c010164
#घोषणा KVM_INST_MTMSR		0x7c000124

#घोषणा KVM_INST_WRTEE		0x7c000106
#घोषणा KVM_INST_WRTEEI_0	0x7c000146
#घोषणा KVM_INST_WRTEEI_1	0x7c008146

#घोषणा KVM_INST_MTSRIN		0x7c0001e4

अटल bool kvm_patching_worked = true;
बाह्य अक्षर kvm_पंचांगp[];
बाह्य अक्षर kvm_पंचांगp_end[];
अटल पूर्णांक kvm_पंचांगp_index;

अटल व्योम __init kvm_patch_ins(u32 *inst, u32 new_inst)
अणु
	*inst = new_inst;
	flush_icache_range((uदीर्घ)inst, (uदीर्घ)inst + 4);
पूर्ण

अटल व्योम __init kvm_patch_ins_ll(u32 *inst, दीर्घ addr, u32 rt)
अणु
#अगर_घोषित CONFIG_64BIT
	kvm_patch_ins(inst, KVM_INST_LD | rt | (addr & 0x0000fffc));
#अन्यथा
	kvm_patch_ins(inst, KVM_INST_LWZ | rt | (addr & 0x0000fffc));
#पूर्ण_अगर
पूर्ण

अटल व्योम __init kvm_patch_ins_ld(u32 *inst, दीर्घ addr, u32 rt)
अणु
#अगर_घोषित CONFIG_64BIT
	kvm_patch_ins(inst, KVM_INST_LD | rt | (addr & 0x0000fffc));
#अन्यथा
	kvm_patch_ins(inst, KVM_INST_LWZ | rt | ((addr + 4) & 0x0000fffc));
#पूर्ण_अगर
पूर्ण

अटल व्योम __init kvm_patch_ins_lwz(u32 *inst, दीर्घ addr, u32 rt)
अणु
	kvm_patch_ins(inst, KVM_INST_LWZ | rt | (addr & 0x0000ffff));
पूर्ण

अटल व्योम __init kvm_patch_ins_std(u32 *inst, दीर्घ addr, u32 rt)
अणु
#अगर_घोषित CONFIG_64BIT
	kvm_patch_ins(inst, KVM_INST_STD | rt | (addr & 0x0000fffc));
#अन्यथा
	kvm_patch_ins(inst, KVM_INST_STW | rt | ((addr + 4) & 0x0000fffc));
#पूर्ण_अगर
पूर्ण

अटल व्योम __init kvm_patch_ins_stw(u32 *inst, दीर्घ addr, u32 rt)
अणु
	kvm_patch_ins(inst, KVM_INST_STW | rt | (addr & 0x0000fffc));
पूर्ण

अटल व्योम __init kvm_patch_ins_nop(u32 *inst)
अणु
	kvm_patch_ins(inst, KVM_INST_NOP);
पूर्ण

अटल व्योम __init kvm_patch_ins_b(u32 *inst, पूर्णांक addr)
अणु
#अगर defined(CONFIG_RELOCATABLE) && defined(CONFIG_PPC_BOOK3S)
	/* On relocatable kernels पूर्णांकerrupts handlers and our code
	   can be in dअगरferent regions, so we करोn't patch them */

	अगर ((uदीर्घ)inst < (uदीर्घ)&__end_पूर्णांकerrupts)
		वापस;
#पूर्ण_अगर

	kvm_patch_ins(inst, KVM_INST_B | (addr & KVM_INST_B_MASK));
पूर्ण

अटल u32 * __init kvm_alloc(पूर्णांक len)
अणु
	u32 *p;

	अगर ((kvm_पंचांगp_index + len) > (kvm_पंचांगp_end - kvm_पंचांगp)) अणु
		prपूर्णांकk(KERN_ERR "KVM: No more space (%d + %d)\n",
				kvm_पंचांगp_index, len);
		kvm_patching_worked = false;
		वापस शून्य;
	पूर्ण

	p = (व्योम*)&kvm_पंचांगp[kvm_पंचांगp_index];
	kvm_पंचांगp_index += len;

	वापस p;
पूर्ण

बाह्य u32 kvm_emulate_mपंचांगsrd_branch_offs;
बाह्य u32 kvm_emulate_mपंचांगsrd_reg_offs;
बाह्य u32 kvm_emulate_mपंचांगsrd_orig_ins_offs;
बाह्य u32 kvm_emulate_mपंचांगsrd_len;
बाह्य u32 kvm_emulate_mपंचांगsrd[];

अटल व्योम __init kvm_patch_ins_mपंचांगsrd(u32 *inst, u32 rt)
अणु
	u32 *p;
	पूर्णांक distance_start;
	पूर्णांक distance_end;
	uदीर्घ next_inst;

	p = kvm_alloc(kvm_emulate_mपंचांगsrd_len * 4);
	अगर (!p)
		वापस;

	/* Find out where we are and put everything there */
	distance_start = (uदीर्घ)p - (uदीर्घ)inst;
	next_inst = ((uदीर्घ)inst + 4);
	distance_end = next_inst - (uदीर्घ)&p[kvm_emulate_mपंचांगsrd_branch_offs];

	/* Make sure we only ग_लिखो valid b inकाष्ठाions */
	अगर (distance_start > KVM_INST_B_MAX) अणु
		kvm_patching_worked = false;
		वापस;
	पूर्ण

	/* Modअगरy the chunk to fit the invocation */
	स_नकल(p, kvm_emulate_mपंचांगsrd, kvm_emulate_mपंचांगsrd_len * 4);
	p[kvm_emulate_mपंचांगsrd_branch_offs] |= distance_end & KVM_INST_B_MASK;
	चयन (get_rt(rt)) अणु
	हाल 30:
		kvm_patch_ins_ll(&p[kvm_emulate_mपंचांगsrd_reg_offs],
				 magic_var(scratch2), KVM_RT_30);
		अवरोध;
	हाल 31:
		kvm_patch_ins_ll(&p[kvm_emulate_mपंचांगsrd_reg_offs],
				 magic_var(scratch1), KVM_RT_30);
		अवरोध;
	शेष:
		p[kvm_emulate_mपंचांगsrd_reg_offs] |= rt;
		अवरोध;
	पूर्ण

	p[kvm_emulate_mपंचांगsrd_orig_ins_offs] = *inst;
	flush_icache_range((uदीर्घ)p, (uदीर्घ)p + kvm_emulate_mपंचांगsrd_len * 4);

	/* Patch the invocation */
	kvm_patch_ins_b(inst, distance_start);
पूर्ण

बाह्य u32 kvm_emulate_mपंचांगsr_branch_offs;
बाह्य u32 kvm_emulate_mपंचांगsr_reg1_offs;
बाह्य u32 kvm_emulate_mपंचांगsr_reg2_offs;
बाह्य u32 kvm_emulate_mपंचांगsr_orig_ins_offs;
बाह्य u32 kvm_emulate_mपंचांगsr_len;
बाह्य u32 kvm_emulate_mपंचांगsr[];

अटल व्योम __init kvm_patch_ins_mपंचांगsr(u32 *inst, u32 rt)
अणु
	u32 *p;
	पूर्णांक distance_start;
	पूर्णांक distance_end;
	uदीर्घ next_inst;

	p = kvm_alloc(kvm_emulate_mपंचांगsr_len * 4);
	अगर (!p)
		वापस;

	/* Find out where we are and put everything there */
	distance_start = (uदीर्घ)p - (uदीर्घ)inst;
	next_inst = ((uदीर्घ)inst + 4);
	distance_end = next_inst - (uदीर्घ)&p[kvm_emulate_mपंचांगsr_branch_offs];

	/* Make sure we only ग_लिखो valid b inकाष्ठाions */
	अगर (distance_start > KVM_INST_B_MAX) अणु
		kvm_patching_worked = false;
		वापस;
	पूर्ण

	/* Modअगरy the chunk to fit the invocation */
	स_नकल(p, kvm_emulate_mपंचांगsr, kvm_emulate_mपंचांगsr_len * 4);
	p[kvm_emulate_mपंचांगsr_branch_offs] |= distance_end & KVM_INST_B_MASK;

	/* Make clobbered रेजिस्टरs work too */
	चयन (get_rt(rt)) अणु
	हाल 30:
		kvm_patch_ins_ll(&p[kvm_emulate_mपंचांगsr_reg1_offs],
				 magic_var(scratch2), KVM_RT_30);
		kvm_patch_ins_ll(&p[kvm_emulate_mपंचांगsr_reg2_offs],
				 magic_var(scratch2), KVM_RT_30);
		अवरोध;
	हाल 31:
		kvm_patch_ins_ll(&p[kvm_emulate_mपंचांगsr_reg1_offs],
				 magic_var(scratch1), KVM_RT_30);
		kvm_patch_ins_ll(&p[kvm_emulate_mपंचांगsr_reg2_offs],
				 magic_var(scratch1), KVM_RT_30);
		अवरोध;
	शेष:
		p[kvm_emulate_mपंचांगsr_reg1_offs] |= rt;
		p[kvm_emulate_mपंचांगsr_reg2_offs] |= rt;
		अवरोध;
	पूर्ण

	p[kvm_emulate_mपंचांगsr_orig_ins_offs] = *inst;
	flush_icache_range((uदीर्घ)p, (uदीर्घ)p + kvm_emulate_mपंचांगsr_len * 4);

	/* Patch the invocation */
	kvm_patch_ins_b(inst, distance_start);
पूर्ण

#अगर_घोषित CONFIG_BOOKE

बाह्य u32 kvm_emulate_wrtee_branch_offs;
बाह्य u32 kvm_emulate_wrtee_reg_offs;
बाह्य u32 kvm_emulate_wrtee_orig_ins_offs;
बाह्य u32 kvm_emulate_wrtee_len;
बाह्य u32 kvm_emulate_wrtee[];

अटल व्योम __init kvm_patch_ins_wrtee(u32 *inst, u32 rt, पूर्णांक imm_one)
अणु
	u32 *p;
	पूर्णांक distance_start;
	पूर्णांक distance_end;
	uदीर्घ next_inst;

	p = kvm_alloc(kvm_emulate_wrtee_len * 4);
	अगर (!p)
		वापस;

	/* Find out where we are and put everything there */
	distance_start = (uदीर्घ)p - (uदीर्घ)inst;
	next_inst = ((uदीर्घ)inst + 4);
	distance_end = next_inst - (uदीर्घ)&p[kvm_emulate_wrtee_branch_offs];

	/* Make sure we only ग_लिखो valid b inकाष्ठाions */
	अगर (distance_start > KVM_INST_B_MAX) अणु
		kvm_patching_worked = false;
		वापस;
	पूर्ण

	/* Modअगरy the chunk to fit the invocation */
	स_नकल(p, kvm_emulate_wrtee, kvm_emulate_wrtee_len * 4);
	p[kvm_emulate_wrtee_branch_offs] |= distance_end & KVM_INST_B_MASK;

	अगर (imm_one) अणु
		p[kvm_emulate_wrtee_reg_offs] =
			KVM_INST_LI | __PPC_RT(R30) | MSR_EE;
	पूर्ण अन्यथा अणु
		/* Make clobbered रेजिस्टरs work too */
		चयन (get_rt(rt)) अणु
		हाल 30:
			kvm_patch_ins_ll(&p[kvm_emulate_wrtee_reg_offs],
					 magic_var(scratch2), KVM_RT_30);
			अवरोध;
		हाल 31:
			kvm_patch_ins_ll(&p[kvm_emulate_wrtee_reg_offs],
					 magic_var(scratch1), KVM_RT_30);
			अवरोध;
		शेष:
			p[kvm_emulate_wrtee_reg_offs] |= rt;
			अवरोध;
		पूर्ण
	पूर्ण

	p[kvm_emulate_wrtee_orig_ins_offs] = *inst;
	flush_icache_range((uदीर्घ)p, (uदीर्घ)p + kvm_emulate_wrtee_len * 4);

	/* Patch the invocation */
	kvm_patch_ins_b(inst, distance_start);
पूर्ण

बाह्य u32 kvm_emulate_wrteei_0_branch_offs;
बाह्य u32 kvm_emulate_wrteei_0_len;
बाह्य u32 kvm_emulate_wrteei_0[];

अटल व्योम __init kvm_patch_ins_wrteei_0(u32 *inst)
अणु
	u32 *p;
	पूर्णांक distance_start;
	पूर्णांक distance_end;
	uदीर्घ next_inst;

	p = kvm_alloc(kvm_emulate_wrteei_0_len * 4);
	अगर (!p)
		वापस;

	/* Find out where we are and put everything there */
	distance_start = (uदीर्घ)p - (uदीर्घ)inst;
	next_inst = ((uदीर्घ)inst + 4);
	distance_end = next_inst - (uदीर्घ)&p[kvm_emulate_wrteei_0_branch_offs];

	/* Make sure we only ग_लिखो valid b inकाष्ठाions */
	अगर (distance_start > KVM_INST_B_MAX) अणु
		kvm_patching_worked = false;
		वापस;
	पूर्ण

	स_नकल(p, kvm_emulate_wrteei_0, kvm_emulate_wrteei_0_len * 4);
	p[kvm_emulate_wrteei_0_branch_offs] |= distance_end & KVM_INST_B_MASK;
	flush_icache_range((uदीर्घ)p, (uदीर्घ)p + kvm_emulate_wrteei_0_len * 4);

	/* Patch the invocation */
	kvm_patch_ins_b(inst, distance_start);
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_32

बाह्य u32 kvm_emulate_mtsrin_branch_offs;
बाह्य u32 kvm_emulate_mtsrin_reg1_offs;
बाह्य u32 kvm_emulate_mtsrin_reg2_offs;
बाह्य u32 kvm_emulate_mtsrin_orig_ins_offs;
बाह्य u32 kvm_emulate_mtsrin_len;
बाह्य u32 kvm_emulate_mtsrin[];

अटल व्योम __init kvm_patch_ins_mtsrin(u32 *inst, u32 rt, u32 rb)
अणु
	u32 *p;
	पूर्णांक distance_start;
	पूर्णांक distance_end;
	uदीर्घ next_inst;

	p = kvm_alloc(kvm_emulate_mtsrin_len * 4);
	अगर (!p)
		वापस;

	/* Find out where we are and put everything there */
	distance_start = (uदीर्घ)p - (uदीर्घ)inst;
	next_inst = ((uदीर्घ)inst + 4);
	distance_end = next_inst - (uदीर्घ)&p[kvm_emulate_mtsrin_branch_offs];

	/* Make sure we only ग_लिखो valid b inकाष्ठाions */
	अगर (distance_start > KVM_INST_B_MAX) अणु
		kvm_patching_worked = false;
		वापस;
	पूर्ण

	/* Modअगरy the chunk to fit the invocation */
	स_नकल(p, kvm_emulate_mtsrin, kvm_emulate_mtsrin_len * 4);
	p[kvm_emulate_mtsrin_branch_offs] |= distance_end & KVM_INST_B_MASK;
	p[kvm_emulate_mtsrin_reg1_offs] |= (rb << 10);
	p[kvm_emulate_mtsrin_reg2_offs] |= rt;
	p[kvm_emulate_mtsrin_orig_ins_offs] = *inst;
	flush_icache_range((uदीर्घ)p, (uदीर्घ)p + kvm_emulate_mtsrin_len * 4);

	/* Patch the invocation */
	kvm_patch_ins_b(inst, distance_start);
पूर्ण

#पूर्ण_अगर

अटल व्योम __init kvm_map_magic_page(व्योम *data)
अणु
	u32 *features = data;

	uदीर्घ in[8] = अणु0पूर्ण;
	uदीर्घ out[8];

	in[0] = KVM_MAGIC_PAGE;
	in[1] = KVM_MAGIC_PAGE | MAGIC_PAGE_FLAG_NOT_MAPPED_NX;

	epapr_hypercall(in, out, KVM_HCALL_TOKEN(KVM_HC_PPC_MAP_MAGIC_PAGE));

	*features = out[0];
पूर्ण

अटल व्योम __init kvm_check_ins(u32 *inst, u32 features)
अणु
	u32 _inst = *inst;
	u32 inst_no_rt = _inst & ~KVM_MASK_RT;
	u32 inst_rt = _inst & KVM_MASK_RT;

	चयन (inst_no_rt) अणु
	/* Loads */
	हाल KVM_INST_MFMSR:
		kvm_patch_ins_ld(inst, magic_var(msr), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_SPRG0):
		kvm_patch_ins_ld(inst, magic_var(sprg0), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_SPRG1):
		kvm_patch_ins_ld(inst, magic_var(sprg1), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_SPRG2):
		kvm_patch_ins_ld(inst, magic_var(sprg2), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_SPRG3):
		kvm_patch_ins_ld(inst, magic_var(sprg3), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_SRR0):
		kvm_patch_ins_ld(inst, magic_var(srr0), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_SRR1):
		kvm_patch_ins_ld(inst, magic_var(srr1), inst_rt);
		अवरोध;
#अगर_घोषित CONFIG_BOOKE
	हाल KVM_INST_MFSPR(SPRN_DEAR):
#अन्यथा
	हाल KVM_INST_MFSPR(SPRN_DAR):
#पूर्ण_अगर
		kvm_patch_ins_ld(inst, magic_var(dar), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_DSISR):
		kvm_patch_ins_lwz(inst, magic_var(dsisr), inst_rt);
		अवरोध;

#अगर_घोषित CONFIG_PPC_BOOK3E_MMU
	हाल KVM_INST_MFSPR(SPRN_MAS0):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(mas0), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_MAS1):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(mas1), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_MAS2):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_ld(inst, magic_var(mas2), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_MAS3):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(mas7_3) + 4, inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_MAS4):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(mas4), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_MAS6):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(mas6), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_MAS7):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(mas7_3), inst_rt);
		अवरोध;
#पूर्ण_अगर /* CONFIG_PPC_BOOK3E_MMU */

	हाल KVM_INST_MFSPR(SPRN_SPRG4):
#अगर_घोषित CONFIG_BOOKE
	हाल KVM_INST_MFSPR(SPRN_SPRG4R):
#पूर्ण_अगर
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_ld(inst, magic_var(sprg4), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_SPRG5):
#अगर_घोषित CONFIG_BOOKE
	हाल KVM_INST_MFSPR(SPRN_SPRG5R):
#पूर्ण_अगर
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_ld(inst, magic_var(sprg5), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_SPRG6):
#अगर_घोषित CONFIG_BOOKE
	हाल KVM_INST_MFSPR(SPRN_SPRG6R):
#पूर्ण_अगर
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_ld(inst, magic_var(sprg6), inst_rt);
		अवरोध;
	हाल KVM_INST_MFSPR(SPRN_SPRG7):
#अगर_घोषित CONFIG_BOOKE
	हाल KVM_INST_MFSPR(SPRN_SPRG7R):
#पूर्ण_अगर
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_ld(inst, magic_var(sprg7), inst_rt);
		अवरोध;

#अगर_घोषित CONFIG_BOOKE
	हाल KVM_INST_MFSPR(SPRN_ESR):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(esr), inst_rt);
		अवरोध;
#पूर्ण_अगर

	हाल KVM_INST_MFSPR(SPRN_PIR):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_lwz(inst, magic_var(pir), inst_rt);
		अवरोध;


	/* Stores */
	हाल KVM_INST_MTSPR(SPRN_SPRG0):
		kvm_patch_ins_std(inst, magic_var(sprg0), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_SPRG1):
		kvm_patch_ins_std(inst, magic_var(sprg1), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_SPRG2):
		kvm_patch_ins_std(inst, magic_var(sprg2), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_SPRG3):
		kvm_patch_ins_std(inst, magic_var(sprg3), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_SRR0):
		kvm_patch_ins_std(inst, magic_var(srr0), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_SRR1):
		kvm_patch_ins_std(inst, magic_var(srr1), inst_rt);
		अवरोध;
#अगर_घोषित CONFIG_BOOKE
	हाल KVM_INST_MTSPR(SPRN_DEAR):
#अन्यथा
	हाल KVM_INST_MTSPR(SPRN_DAR):
#पूर्ण_अगर
		kvm_patch_ins_std(inst, magic_var(dar), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_DSISR):
		kvm_patch_ins_stw(inst, magic_var(dsisr), inst_rt);
		अवरोध;
#अगर_घोषित CONFIG_PPC_BOOK3E_MMU
	हाल KVM_INST_MTSPR(SPRN_MAS0):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(mas0), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_MAS1):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(mas1), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_MAS2):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_std(inst, magic_var(mas2), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_MAS3):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(mas7_3) + 4, inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_MAS4):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(mas4), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_MAS6):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(mas6), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_MAS7):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(mas7_3), inst_rt);
		अवरोध;
#पूर्ण_अगर /* CONFIG_PPC_BOOK3E_MMU */

	हाल KVM_INST_MTSPR(SPRN_SPRG4):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_std(inst, magic_var(sprg4), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_SPRG5):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_std(inst, magic_var(sprg5), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_SPRG6):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_std(inst, magic_var(sprg6), inst_rt);
		अवरोध;
	हाल KVM_INST_MTSPR(SPRN_SPRG7):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_std(inst, magic_var(sprg7), inst_rt);
		अवरोध;

#अगर_घोषित CONFIG_BOOKE
	हाल KVM_INST_MTSPR(SPRN_ESR):
		अगर (features & KVM_MAGIC_FEAT_MAS0_TO_SPRG7)
			kvm_patch_ins_stw(inst, magic_var(esr), inst_rt);
		अवरोध;
#पूर्ण_अगर

	/* Nops */
	हाल KVM_INST_TLBSYNC:
		kvm_patch_ins_nop(inst);
		अवरोध;

	/* Reग_लिखोs */
	हाल KVM_INST_MTMSRD_L1:
		kvm_patch_ins_mपंचांगsrd(inst, inst_rt);
		अवरोध;
	हाल KVM_INST_MTMSR:
	हाल KVM_INST_MTMSRD_L0:
		kvm_patch_ins_mपंचांगsr(inst, inst_rt);
		अवरोध;
#अगर_घोषित CONFIG_BOOKE
	हाल KVM_INST_WRTEE:
		kvm_patch_ins_wrtee(inst, inst_rt, 0);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	चयन (inst_no_rt & ~KVM_MASK_RB) अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_32
	हाल KVM_INST_MTSRIN:
		अगर (features & KVM_MAGIC_FEAT_SR) अणु
			u32 inst_rb = _inst & KVM_MASK_RB;
			kvm_patch_ins_mtsrin(inst, inst_rt, inst_rb);
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	चयन (_inst) अणु
#अगर_घोषित CONFIG_BOOKE
	हाल KVM_INST_WRTEEI_0:
		kvm_patch_ins_wrteei_0(inst);
		अवरोध;

	हाल KVM_INST_WRTEEI_1:
		kvm_patch_ins_wrtee(inst, 0, 1);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

बाह्य u32 kvm_ढाँचा_start[];
बाह्य u32 kvm_ढाँचा_end[];

अटल व्योम __init kvm_use_magic_page(व्योम)
अणु
	u32 *p;
	u32 *start, *end;
	u32 features;

	/* Tell the host to map the magic page to -4096 on all CPUs */
	on_each_cpu(kvm_map_magic_page, &features, 1);

	/* Quick self-test to see अगर the mapping works */
	अगर (!fault_in_pages_पढ़ोable((स्थिर अक्षर *)KVM_MAGIC_PAGE, माप(u32))) अणु
		kvm_patching_worked = false;
		वापस;
	पूर्ण

	/* Now loop through all code and find inकाष्ठाions */
	start = (व्योम*)_stext;
	end = (व्योम*)_etext;

	/*
	 * Being पूर्णांकerrupted in the middle of patching would
	 * be bad क्रम SPRG4-7, which KVM can't keep in sync
	 * with emulated accesses because पढ़ोs करोn't trap.
	 */
	local_irq_disable();

	क्रम (p = start; p < end; p++) अणु
		/* Aव्योम patching the ढाँचा code */
		अगर (p >= kvm_ढाँचा_start && p < kvm_ढाँचा_end) अणु
			p = kvm_ढाँचा_end - 1;
			जारी;
		पूर्ण
		kvm_check_ins(p, features);
	पूर्ण

	local_irq_enable();

	prपूर्णांकk(KERN_INFO "KVM: Live patching for a fast VM %s\n",
			 kvm_patching_worked ? "worked" : "failed");
पूर्ण

अटल पूर्णांक __init kvm_guest_init(व्योम)
अणु
	अगर (!kvm_para_available())
		वापस 0;

	अगर (!epapr_paravirt_enabled)
		वापस 0;

	अगर (kvm_para_has_feature(KVM_FEATURE_MAGIC_PAGE))
		kvm_use_magic_page();

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/* Enable napping */
	घातersave_nap = 1;
#पूर्ण_अगर

	वापस 0;
पूर्ण

postcore_initcall(kvm_guest_init);
