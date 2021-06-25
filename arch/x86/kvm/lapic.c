<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Local APIC भवization
 *
 * Copyright (C) 2006 Qumranet, Inc.
 * Copyright (C) 2007 Novell
 * Copyright (C) 2007 Intel
 * Copyright 2009 Red Hat, Inc. and/or its affiliates.
 *
 * Authors:
 *   Dor Laor <करोr.laor@qumranet.com>
 *   Gregory Haskins <ghaskins@novell.com>
 *   Yaozu (Eddie) Dong <eddie.करोng@पूर्णांकel.com>
 *
 * Based on Xen 3.1 code, Copyright (c) 2004, Intel Corporation.
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/kvm.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/smp.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <linux/math64.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/apicdef.h>
#समावेश <यंत्र/delay.h>
#समावेश <linux/atomic.h>
#समावेश <linux/jump_label.h>
#समावेश "kvm_cache_regs.h"
#समावेश "irq.h"
#समावेश "ioapic.h"
#समावेश "trace.h"
#समावेश "x86.h"
#समावेश "cpuid.h"
#समावेश "hyperv.h"

#अगर_अघोषित CONFIG_X86_64
#घोषणा mod_64(x, y) ((x) - (y) * भाग64_u64(x, y))
#अन्यथा
#घोषणा mod_64(x, y) ((x) % (y))
#पूर्ण_अगर

#घोषणा PRId64 "d"
#घोषणा PRIx64 "llx"
#घोषणा PRIu64 "u"
#घोषणा PRIo64 "o"

/* 14 is the version क्रम Xeon and Pentium 8.4.8*/
#घोषणा APIC_VERSION			(0x14UL | ((KVM_APIC_LVT_NUM - 1) << 16))
#घोषणा LAPIC_MMIO_LENGTH		(1 << 12)
/* followed define is not in apicdef.h */
#घोषणा MAX_APIC_VECTOR			256
#घोषणा APIC_VECTORS_PER_REG		32

अटल bool lapic_समयr_advance_dynamic __पढ़ो_mostly;
#घोषणा LAPIC_TIMER_ADVANCE_ADJUST_MIN	100	/* घड़ी cycles */
#घोषणा LAPIC_TIMER_ADVANCE_ADJUST_MAX	10000	/* घड़ी cycles */
#घोषणा LAPIC_TIMER_ADVANCE_NS_INIT	1000
#घोषणा LAPIC_TIMER_ADVANCE_NS_MAX     5000
/* step-by-step approximation to mitigate fluctuation */
#घोषणा LAPIC_TIMER_ADVANCE_ADJUST_STEP 8

अटल अंतरभूत पूर्णांक apic_test_vector(पूर्णांक vec, व्योम *biपंचांगap)
अणु
	वापस test_bit(VEC_POS(vec), (biपंचांगap) + REG_POS(vec));
पूर्ण

bool kvm_apic_pending_eoi(काष्ठा kvm_vcpu *vcpu, पूर्णांक vector)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	वापस apic_test_vector(vector, apic->regs + APIC_ISR) ||
		apic_test_vector(vector, apic->regs + APIC_IRR);
पूर्ण

अटल अंतरभूत पूर्णांक __apic_test_and_set_vector(पूर्णांक vec, व्योम *biपंचांगap)
अणु
	वापस __test_and_set_bit(VEC_POS(vec), (biपंचांगap) + REG_POS(vec));
पूर्ण

अटल अंतरभूत पूर्णांक __apic_test_and_clear_vector(पूर्णांक vec, व्योम *biपंचांगap)
अणु
	वापस __test_and_clear_bit(VEC_POS(vec), (biपंचांगap) + REG_POS(vec));
पूर्ण

__पढ़ो_mostly DEFINE_STATIC_KEY_DEFERRED_FALSE(apic_hw_disabled, HZ);
__पढ़ो_mostly DEFINE_STATIC_KEY_DEFERRED_FALSE(apic_sw_disabled, HZ);

अटल अंतरभूत पूर्णांक apic_enabled(काष्ठा kvm_lapic *apic)
अणु
	वापस kvm_apic_sw_enabled(apic) &&	kvm_apic_hw_enabled(apic);
पूर्ण

#घोषणा LVT_MASK	\
	(APIC_LVT_MASKED | APIC_SEND_PENDING | APIC_VECTOR_MASK)

#घोषणा LINT_MASK	\
	(LVT_MASK | APIC_MODE_MASK | APIC_INPUT_POLARITY | \
	 APIC_LVT_REMOTE_IRR | APIC_LVT_LEVEL_TRIGGER)

अटल अंतरभूत u32 kvm_x2apic_id(काष्ठा kvm_lapic *apic)
अणु
	वापस apic->vcpu->vcpu_id;
पूर्ण

अटल bool kvm_can_post_समयr_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस pi_inject_समयr && kvm_vcpu_apicv_active(vcpu);
पूर्ण

bool kvm_can_use_hv_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_x86_ops.set_hv_समयr
	       && !(kvm_mरुको_in_guest(vcpu->kvm) ||
		    kvm_can_post_समयr_पूर्णांकerrupt(vcpu));
पूर्ण
EXPORT_SYMBOL_GPL(kvm_can_use_hv_समयr);

अटल bool kvm_use_posted_समयr_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_can_post_समयr_पूर्णांकerrupt(vcpu) && vcpu->mode == IN_GUEST_MODE;
पूर्ण

अटल अंतरभूत bool kvm_apic_map_get_logical_dest(काष्ठा kvm_apic_map *map,
		u32 dest_id, काष्ठा kvm_lapic ***cluster, u16 *mask) अणु
	चयन (map->mode) अणु
	हाल KVM_APIC_MODE_X2APIC: अणु
		u32 offset = (dest_id >> 16) * 16;
		u32 max_apic_id = map->max_apic_id;

		अगर (offset <= max_apic_id) अणु
			u8 cluster_size = min(max_apic_id - offset + 1, 16U);

			offset = array_index_nospec(offset, map->max_apic_id + 1);
			*cluster = &map->phys_map[offset];
			*mask = dest_id & (0xffff >> (16 - cluster_size));
		पूर्ण अन्यथा अणु
			*mask = 0;
		पूर्ण

		वापस true;
		पूर्ण
	हाल KVM_APIC_MODE_XAPIC_FLAT:
		*cluster = map->xapic_flat_map;
		*mask = dest_id & 0xff;
		वापस true;
	हाल KVM_APIC_MODE_XAPIC_CLUSTER:
		*cluster = map->xapic_cluster_map[(dest_id >> 4) & 0xf];
		*mask = dest_id & 0xf;
		वापस true;
	शेष:
		/* Not optimized. */
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम kvm_apic_map_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा kvm_apic_map *map = container_of(rcu, काष्ठा kvm_apic_map, rcu);

	kvमुक्त(map);
पूर्ण

/*
 * CLEAN -> सूचीTY and UPDATE_IN_PROGRESS -> सूचीTY changes happen without a lock.
 *
 * सूचीTY -> UPDATE_IN_PROGRESS and UPDATE_IN_PROGRESS -> CLEAN happen with
 * apic_map_lock_held.
 */
क्रमागत अणु
	CLEAN,
	UPDATE_IN_PROGRESS,
	सूचीTY
पूर्ण;

व्योम kvm_recalculate_apic_map(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_apic_map *new, *old = शून्य;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;
	u32 max_id = 255; /* enough space क्रम any xAPIC ID */

	/* Read kvm->arch.apic_map_dirty beक्रमe kvm->arch.apic_map.  */
	अगर (atomic_पढ़ो_acquire(&kvm->arch.apic_map_dirty) == CLEAN)
		वापस;

	mutex_lock(&kvm->arch.apic_map_lock);
	/*
	 * Read kvm->arch.apic_map_dirty beक्रमe kvm->arch.apic_map
	 * (अगर clean) or the APIC रेजिस्टरs (अगर dirty).
	 */
	अगर (atomic_cmpxchg_acquire(&kvm->arch.apic_map_dirty,
				   सूचीTY, UPDATE_IN_PROGRESS) == CLEAN) अणु
		/* Someone अन्यथा has updated the map. */
		mutex_unlock(&kvm->arch.apic_map_lock);
		वापस;
	पूर्ण

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		अगर (kvm_apic_present(vcpu))
			max_id = max(max_id, kvm_x2apic_id(vcpu->arch.apic));

	new = kvzalloc(माप(काष्ठा kvm_apic_map) +
	                   माप(काष्ठा kvm_lapic *) * ((u64)max_id + 1),
			   GFP_KERNEL_ACCOUNT);

	अगर (!new)
		जाओ out;

	new->max_apic_id = max_id;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		काष्ठा kvm_lapic *apic = vcpu->arch.apic;
		काष्ठा kvm_lapic **cluster;
		u16 mask;
		u32 ldr;
		u8 xapic_id;
		u32 x2apic_id;

		अगर (!kvm_apic_present(vcpu))
			जारी;

		xapic_id = kvm_xapic_id(apic);
		x2apic_id = kvm_x2apic_id(apic);

		/* Hotplug hack: see kvm_apic_match_physical_addr(), ... */
		अगर ((apic_x2apic_mode(apic) || x2apic_id > 0xff) &&
				x2apic_id <= new->max_apic_id)
			new->phys_map[x2apic_id] = apic;
		/*
		 * ... xAPIC ID of VCPUs with APIC ID > 0xff will wrap-around,
		 * prevent them from masking VCPUs with APIC ID <= 0xff.
		 */
		अगर (!apic_x2apic_mode(apic) && !new->phys_map[xapic_id])
			new->phys_map[xapic_id] = apic;

		अगर (!kvm_apic_sw_enabled(apic))
			जारी;

		ldr = kvm_lapic_get_reg(apic, APIC_LDR);

		अगर (apic_x2apic_mode(apic)) अणु
			new->mode |= KVM_APIC_MODE_X2APIC;
		पूर्ण अन्यथा अगर (ldr) अणु
			ldr = GET_APIC_LOGICAL_ID(ldr);
			अगर (kvm_lapic_get_reg(apic, APIC_DFR) == APIC_DFR_FLAT)
				new->mode |= KVM_APIC_MODE_XAPIC_FLAT;
			अन्यथा
				new->mode |= KVM_APIC_MODE_XAPIC_CLUSTER;
		पूर्ण

		अगर (!kvm_apic_map_get_logical_dest(new, ldr, &cluster, &mask))
			जारी;

		अगर (mask)
			cluster[ffs(mask) - 1] = apic;
	पूर्ण
out:
	old = rcu_dereference_रक्षित(kvm->arch.apic_map,
			lockdep_is_held(&kvm->arch.apic_map_lock));
	rcu_assign_poपूर्णांकer(kvm->arch.apic_map, new);
	/*
	 * Write kvm->arch.apic_map beक्रमe clearing apic->apic_map_dirty.
	 * If another update has come in, leave it सूचीTY.
	 */
	atomic_cmpxchg_release(&kvm->arch.apic_map_dirty,
			       UPDATE_IN_PROGRESS, CLEAN);
	mutex_unlock(&kvm->arch.apic_map_lock);

	अगर (old)
		call_rcu(&old->rcu, kvm_apic_map_मुक्त);

	kvm_make_scan_ioapic_request(kvm);
पूर्ण

अटल अंतरभूत व्योम apic_set_spiv(काष्ठा kvm_lapic *apic, u32 val)
अणु
	bool enabled = val & APIC_SPIV_APIC_ENABLED;

	kvm_lapic_set_reg(apic, APIC_SPIV, val);

	अगर (enabled != apic->sw_enabled) अणु
		apic->sw_enabled = enabled;
		अगर (enabled)
			अटल_branch_slow_dec_deferred(&apic_sw_disabled);
		अन्यथा
			अटल_branch_inc(&apic_sw_disabled.key);

		atomic_set_release(&apic->vcpu->kvm->arch.apic_map_dirty, सूचीTY);
	पूर्ण

	/* Check अगर there are APF page पढ़ोy requests pending */
	अगर (enabled)
		kvm_make_request(KVM_REQ_APF_READY, apic->vcpu);
पूर्ण

अटल अंतरभूत व्योम kvm_apic_set_xapic_id(काष्ठा kvm_lapic *apic, u8 id)
अणु
	kvm_lapic_set_reg(apic, APIC_ID, id << 24);
	atomic_set_release(&apic->vcpu->kvm->arch.apic_map_dirty, सूचीTY);
पूर्ण

अटल अंतरभूत व्योम kvm_apic_set_ldr(काष्ठा kvm_lapic *apic, u32 id)
अणु
	kvm_lapic_set_reg(apic, APIC_LDR, id);
	atomic_set_release(&apic->vcpu->kvm->arch.apic_map_dirty, सूचीTY);
पूर्ण

अटल अंतरभूत व्योम kvm_apic_set_dfr(काष्ठा kvm_lapic *apic, u32 val)
अणु
	kvm_lapic_set_reg(apic, APIC_DFR, val);
	atomic_set_release(&apic->vcpu->kvm->arch.apic_map_dirty, सूचीTY);
पूर्ण

अटल अंतरभूत u32 kvm_apic_calc_x2apic_ldr(u32 id)
अणु
	वापस ((id >> 4) << 16) | (1 << (id & 0xf));
पूर्ण

अटल अंतरभूत व्योम kvm_apic_set_x2apic_id(काष्ठा kvm_lapic *apic, u32 id)
अणु
	u32 ldr = kvm_apic_calc_x2apic_ldr(id);

	WARN_ON_ONCE(id != apic->vcpu->vcpu_id);

	kvm_lapic_set_reg(apic, APIC_ID, id);
	kvm_lapic_set_reg(apic, APIC_LDR, ldr);
	atomic_set_release(&apic->vcpu->kvm->arch.apic_map_dirty, सूचीTY);
पूर्ण

अटल अंतरभूत पूर्णांक apic_lvt_enabled(काष्ठा kvm_lapic *apic, पूर्णांक lvt_type)
अणु
	वापस !(kvm_lapic_get_reg(apic, lvt_type) & APIC_LVT_MASKED);
पूर्ण

अटल अंतरभूत पूर्णांक apic_lvtt_oneshot(काष्ठा kvm_lapic *apic)
अणु
	वापस apic->lapic_समयr.समयr_mode == APIC_LVT_TIMER_ONESHOT;
पूर्ण

अटल अंतरभूत पूर्णांक apic_lvtt_period(काष्ठा kvm_lapic *apic)
अणु
	वापस apic->lapic_समयr.समयr_mode == APIC_LVT_TIMER_PERIODIC;
पूर्ण

अटल अंतरभूत पूर्णांक apic_lvtt_tscdeadline(काष्ठा kvm_lapic *apic)
अणु
	वापस apic->lapic_समयr.समयr_mode == APIC_LVT_TIMER_TSCDEADLINE;
पूर्ण

अटल अंतरभूत पूर्णांक apic_lvt_nmi_mode(u32 lvt_val)
अणु
	वापस (lvt_val & (APIC_MODE_MASK | APIC_LVT_MASKED)) == APIC_DM_NMI;
पूर्ण

व्योम kvm_apic_set_version(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	u32 v = APIC_VERSION;

	अगर (!lapic_in_kernel(vcpu))
		वापस;

	/*
	 * KVM emulates 82093AA datasheet (with in-kernel IOAPIC implementation)
	 * which करोesn't have EOI रेजिस्टर; Some buggy OSes (e.g. Winकरोws with
	 * Hyper-V role) disable EOI broadcast in lapic not checking क्रम IOAPIC
	 * version first and level-triggered पूर्णांकerrupts never get EOIed in
	 * IOAPIC.
	 */
	अगर (guest_cpuid_has(vcpu, X86_FEATURE_X2APIC) &&
	    !ioapic_in_kernel(vcpu->kvm))
		v |= APIC_LVR_सूचीECTED_EOI;
	kvm_lapic_set_reg(apic, APIC_LVR, v);
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक apic_lvt_mask[KVM_APIC_LVT_NUM] = अणु
	LVT_MASK ,      /* part LVTT mask, समयr mode mask added at runसमय */
	LVT_MASK | APIC_MODE_MASK,	/* LVTTHMR */
	LVT_MASK | APIC_MODE_MASK,	/* LVTPC */
	LINT_MASK, LINT_MASK,	/* LVT0-1 */
	LVT_MASK		/* LVTERR */
पूर्ण;

अटल पूर्णांक find_highest_vector(व्योम *biपंचांगap)
अणु
	पूर्णांक vec;
	u32 *reg;

	क्रम (vec = MAX_APIC_VECTOR - APIC_VECTORS_PER_REG;
	     vec >= 0; vec -= APIC_VECTORS_PER_REG) अणु
		reg = biपंचांगap + REG_POS(vec);
		अगर (*reg)
			वापस __fls(*reg) + vec;
	पूर्ण

	वापस -1;
पूर्ण

अटल u8 count_vectors(व्योम *biपंचांगap)
अणु
	पूर्णांक vec;
	u32 *reg;
	u8 count = 0;

	क्रम (vec = 0; vec < MAX_APIC_VECTOR; vec += APIC_VECTORS_PER_REG) अणु
		reg = biपंचांगap + REG_POS(vec);
		count += hweight32(*reg);
	पूर्ण

	वापस count;
पूर्ण

bool __kvm_apic_update_irr(u32 *pir, व्योम *regs, पूर्णांक *max_irr)
अणु
	u32 i, vec;
	u32 pir_val, irr_val, prev_irr_val;
	पूर्णांक max_updated_irr;

	max_updated_irr = -1;
	*max_irr = -1;

	क्रम (i = vec = 0; i <= 7; i++, vec += 32) अणु
		pir_val = READ_ONCE(pir[i]);
		irr_val = *((u32 *)(regs + APIC_IRR + i * 0x10));
		अगर (pir_val) अणु
			prev_irr_val = irr_val;
			irr_val |= xchg(&pir[i], 0);
			*((u32 *)(regs + APIC_IRR + i * 0x10)) = irr_val;
			अगर (prev_irr_val != irr_val) अणु
				max_updated_irr =
					__fls(irr_val ^ prev_irr_val) + vec;
			पूर्ण
		पूर्ण
		अगर (irr_val)
			*max_irr = __fls(irr_val) + vec;
	पूर्ण

	वापस ((max_updated_irr != -1) &&
		(max_updated_irr == *max_irr));
पूर्ण
EXPORT_SYMBOL_GPL(__kvm_apic_update_irr);

bool kvm_apic_update_irr(काष्ठा kvm_vcpu *vcpu, u32 *pir, पूर्णांक *max_irr)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	वापस __kvm_apic_update_irr(pir, apic->regs, max_irr);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_apic_update_irr);

अटल अंतरभूत पूर्णांक apic_search_irr(काष्ठा kvm_lapic *apic)
अणु
	वापस find_highest_vector(apic->regs + APIC_IRR);
पूर्ण

अटल अंतरभूत पूर्णांक apic_find_highest_irr(काष्ठा kvm_lapic *apic)
अणु
	पूर्णांक result;

	/*
	 * Note that irr_pending is just a hपूर्णांक. It will be always
	 * true with भव पूर्णांकerrupt delivery enabled.
	 */
	अगर (!apic->irr_pending)
		वापस -1;

	result = apic_search_irr(apic);
	ASSERT(result == -1 || result >= 16);

	वापस result;
पूर्ण

अटल अंतरभूत व्योम apic_clear_irr(पूर्णांक vec, काष्ठा kvm_lapic *apic)
अणु
	काष्ठा kvm_vcpu *vcpu;

	vcpu = apic->vcpu;

	अगर (unlikely(vcpu->arch.apicv_active)) अणु
		/* need to update RVI */
		kvm_lapic_clear_vector(vec, apic->regs + APIC_IRR);
		अटल_call(kvm_x86_hwapic_irr_update)(vcpu,
				apic_find_highest_irr(apic));
	पूर्ण अन्यथा अणु
		apic->irr_pending = false;
		kvm_lapic_clear_vector(vec, apic->regs + APIC_IRR);
		अगर (apic_search_irr(apic) != -1)
			apic->irr_pending = true;
	पूर्ण
पूर्ण

व्योम kvm_apic_clear_irr(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec)
अणु
	apic_clear_irr(vec, vcpu->arch.apic);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_apic_clear_irr);

अटल अंतरभूत व्योम apic_set_isr(पूर्णांक vec, काष्ठा kvm_lapic *apic)
अणु
	काष्ठा kvm_vcpu *vcpu;

	अगर (__apic_test_and_set_vector(vec, apic->regs + APIC_ISR))
		वापस;

	vcpu = apic->vcpu;

	/*
	 * With APIC भवization enabled, all caching is disabled
	 * because the processor can modअगरy ISR under the hood.  Instead
	 * just set SVI.
	 */
	अगर (unlikely(vcpu->arch.apicv_active))
		अटल_call(kvm_x86_hwapic_isr_update)(vcpu, vec);
	अन्यथा अणु
		++apic->isr_count;
		BUG_ON(apic->isr_count > MAX_APIC_VECTOR);
		/*
		 * ISR (in service रेजिस्टर) bit is set when injecting an पूर्णांकerrupt.
		 * The highest vector is injected. Thus the latest bit set matches
		 * the highest bit in ISR.
		 */
		apic->highest_isr_cache = vec;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक apic_find_highest_isr(काष्ठा kvm_lapic *apic)
अणु
	पूर्णांक result;

	/*
	 * Note that isr_count is always 1, and highest_isr_cache
	 * is always -1, with APIC भवization enabled.
	 */
	अगर (!apic->isr_count)
		वापस -1;
	अगर (likely(apic->highest_isr_cache != -1))
		वापस apic->highest_isr_cache;

	result = find_highest_vector(apic->regs + APIC_ISR);
	ASSERT(result == -1 || result >= 16);

	वापस result;
पूर्ण

अटल अंतरभूत व्योम apic_clear_isr(पूर्णांक vec, काष्ठा kvm_lapic *apic)
अणु
	काष्ठा kvm_vcpu *vcpu;
	अगर (!__apic_test_and_clear_vector(vec, apic->regs + APIC_ISR))
		वापस;

	vcpu = apic->vcpu;

	/*
	 * We करो get here क्रम APIC भवization enabled अगर the guest
	 * uses the Hyper-V APIC enlightenment.  In this हाल we may need
	 * to trigger a new पूर्णांकerrupt delivery by writing the SVI field;
	 * on the other hand isr_count and highest_isr_cache are unused
	 * and must be left alone.
	 */
	अगर (unlikely(vcpu->arch.apicv_active))
		अटल_call(kvm_x86_hwapic_isr_update)(vcpu,
						apic_find_highest_isr(apic));
	अन्यथा अणु
		--apic->isr_count;
		BUG_ON(apic->isr_count < 0);
		apic->highest_isr_cache = -1;
	पूर्ण
पूर्ण

पूर्णांक kvm_lapic_find_highest_irr(काष्ठा kvm_vcpu *vcpu)
अणु
	/* This may race with setting of irr in __apic_accept_irq() and
	 * value वापसed may be wrong, but kvm_vcpu_kick() in __apic_accept_irq
	 * will cause vmनिकास immediately and the value will be recalculated
	 * on the next vmentry.
	 */
	वापस apic_find_highest_irr(vcpu->arch.apic);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_lapic_find_highest_irr);

अटल पूर्णांक __apic_accept_irq(काष्ठा kvm_lapic *apic, पूर्णांक delivery_mode,
			     पूर्णांक vector, पूर्णांक level, पूर्णांक trig_mode,
			     काष्ठा dest_map *dest_map);

पूर्णांक kvm_apic_set_irq(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_lapic_irq *irq,
		     काष्ठा dest_map *dest_map)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	वापस __apic_accept_irq(apic, irq->delivery_mode, irq->vector,
			irq->level, irq->trig_mode, dest_map);
पूर्ण

अटल पूर्णांक __pv_send_ipi(अचिन्हित दीर्घ *ipi_biपंचांगap, काष्ठा kvm_apic_map *map,
			 काष्ठा kvm_lapic_irq *irq, u32 min)
अणु
	पूर्णांक i, count = 0;
	काष्ठा kvm_vcpu *vcpu;

	अगर (min > map->max_apic_id)
		वापस 0;

	क्रम_each_set_bit(i, ipi_biपंचांगap,
		min((u32)BITS_PER_LONG, (map->max_apic_id - min + 1))) अणु
		अगर (map->phys_map[min + i]) अणु
			vcpu = map->phys_map[min + i]->vcpu;
			count += kvm_apic_set_irq(vcpu, irq, शून्य);
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

पूर्णांक kvm_pv_send_ipi(काष्ठा kvm *kvm, अचिन्हित दीर्घ ipi_biपंचांगap_low,
		    अचिन्हित दीर्घ ipi_biपंचांगap_high, u32 min,
		    अचिन्हित दीर्घ icr, पूर्णांक op_64_bit)
अणु
	काष्ठा kvm_apic_map *map;
	काष्ठा kvm_lapic_irq irq = अणु0पूर्ण;
	पूर्णांक cluster_size = op_64_bit ? 64 : 32;
	पूर्णांक count;

	अगर (icr & (APIC_DEST_MASK | APIC_SHORT_MASK))
		वापस -KVM_EINVAL;

	irq.vector = icr & APIC_VECTOR_MASK;
	irq.delivery_mode = icr & APIC_MODE_MASK;
	irq.level = (icr & APIC_INT_ASSERT) != 0;
	irq.trig_mode = icr & APIC_INT_LEVELTRIG;

	rcu_पढ़ो_lock();
	map = rcu_dereference(kvm->arch.apic_map);

	count = -EOPNOTSUPP;
	अगर (likely(map)) अणु
		count = __pv_send_ipi(&ipi_biपंचांगap_low, map, &irq, min);
		min += cluster_size;
		count += __pv_send_ipi(&ipi_biपंचांगap_high, map, &irq, min);
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस count;
पूर्ण

अटल पूर्णांक pv_eoi_put_user(काष्ठा kvm_vcpu *vcpu, u8 val)
अणु

	वापस kvm_ग_लिखो_guest_cached(vcpu->kvm, &vcpu->arch.pv_eoi.data, &val,
				      माप(val));
पूर्ण

अटल पूर्णांक pv_eoi_get_user(काष्ठा kvm_vcpu *vcpu, u8 *val)
अणु

	वापस kvm_पढ़ो_guest_cached(vcpu->kvm, &vcpu->arch.pv_eoi.data, val,
				      माप(*val));
पूर्ण

अटल अंतरभूत bool pv_eoi_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.pv_eoi.msr_val & KVM_MSR_ENABLED;
पूर्ण

अटल bool pv_eoi_get_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	u8 val;
	अगर (pv_eoi_get_user(vcpu, &val) < 0) अणु
		prपूर्णांकk(KERN_WARNING "Can't read EOI MSR value: 0x%llx\n",
			   (अचिन्हित दीर्घ दीर्घ)vcpu->arch.pv_eoi.msr_val);
		वापस false;
	पूर्ण
	वापस val & KVM_PV_EOI_ENABLED;
पूर्ण

अटल व्योम pv_eoi_set_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (pv_eoi_put_user(vcpu, KVM_PV_EOI_ENABLED) < 0) अणु
		prपूर्णांकk(KERN_WARNING "Can't set EOI MSR value: 0x%llx\n",
			   (अचिन्हित दीर्घ दीर्घ)vcpu->arch.pv_eoi.msr_val);
		वापस;
	पूर्ण
	__set_bit(KVM_APIC_PV_EOI_PENDING, &vcpu->arch.apic_attention);
पूर्ण

अटल व्योम pv_eoi_clr_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (pv_eoi_put_user(vcpu, KVM_PV_EOI_DISABLED) < 0) अणु
		prपूर्णांकk(KERN_WARNING "Can't clear EOI MSR value: 0x%llx\n",
			   (अचिन्हित दीर्घ दीर्घ)vcpu->arch.pv_eoi.msr_val);
		वापस;
	पूर्ण
	__clear_bit(KVM_APIC_PV_EOI_PENDING, &vcpu->arch.apic_attention);
पूर्ण

अटल पूर्णांक apic_has_पूर्णांकerrupt_क्रम_ppr(काष्ठा kvm_lapic *apic, u32 ppr)
अणु
	पूर्णांक highest_irr;
	अगर (apic->vcpu->arch.apicv_active)
		highest_irr = अटल_call(kvm_x86_sync_pir_to_irr)(apic->vcpu);
	अन्यथा
		highest_irr = apic_find_highest_irr(apic);
	अगर (highest_irr == -1 || (highest_irr & 0xF0) <= ppr)
		वापस -1;
	वापस highest_irr;
पूर्ण

अटल bool __apic_update_ppr(काष्ठा kvm_lapic *apic, u32 *new_ppr)
अणु
	u32 tpr, isrv, ppr, old_ppr;
	पूर्णांक isr;

	old_ppr = kvm_lapic_get_reg(apic, APIC_PROCPRI);
	tpr = kvm_lapic_get_reg(apic, APIC_TASKPRI);
	isr = apic_find_highest_isr(apic);
	isrv = (isr != -1) ? isr : 0;

	अगर ((tpr & 0xf0) >= (isrv & 0xf0))
		ppr = tpr & 0xff;
	अन्यथा
		ppr = isrv & 0xf0;

	*new_ppr = ppr;
	अगर (old_ppr != ppr)
		kvm_lapic_set_reg(apic, APIC_PROCPRI, ppr);

	वापस ppr < old_ppr;
पूर्ण

अटल व्योम apic_update_ppr(काष्ठा kvm_lapic *apic)
अणु
	u32 ppr;

	अगर (__apic_update_ppr(apic, &ppr) &&
	    apic_has_पूर्णांकerrupt_क्रम_ppr(apic, ppr) != -1)
		kvm_make_request(KVM_REQ_EVENT, apic->vcpu);
पूर्ण

व्योम kvm_apic_update_ppr(काष्ठा kvm_vcpu *vcpu)
अणु
	apic_update_ppr(vcpu->arch.apic);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_apic_update_ppr);

अटल व्योम apic_set_tpr(काष्ठा kvm_lapic *apic, u32 tpr)
अणु
	kvm_lapic_set_reg(apic, APIC_TASKPRI, tpr);
	apic_update_ppr(apic);
पूर्ण

अटल bool kvm_apic_broadcast(काष्ठा kvm_lapic *apic, u32 mda)
अणु
	वापस mda == (apic_x2apic_mode(apic) ?
			X2APIC_BROADCAST : APIC_BROADCAST);
पूर्ण

अटल bool kvm_apic_match_physical_addr(काष्ठा kvm_lapic *apic, u32 mda)
अणु
	अगर (kvm_apic_broadcast(apic, mda))
		वापस true;

	अगर (apic_x2apic_mode(apic))
		वापस mda == kvm_x2apic_id(apic);

	/*
	 * Hotplug hack: Make LAPIC in xAPIC mode also accept पूर्णांकerrupts as अगर
	 * it were in x2APIC mode.  Hotplugged VCPUs start in xAPIC mode and
	 * this allows unique addressing of VCPUs with APIC ID over 0xff.
	 * The 0xff condition is needed because ग_लिखोable xAPIC ID.
	 */
	अगर (kvm_x2apic_id(apic) > 0xff && mda == kvm_x2apic_id(apic))
		वापस true;

	वापस mda == kvm_xapic_id(apic);
पूर्ण

अटल bool kvm_apic_match_logical_addr(काष्ठा kvm_lapic *apic, u32 mda)
अणु
	u32 logical_id;

	अगर (kvm_apic_broadcast(apic, mda))
		वापस true;

	logical_id = kvm_lapic_get_reg(apic, APIC_LDR);

	अगर (apic_x2apic_mode(apic))
		वापस ((logical_id >> 16) == (mda >> 16))
		       && (logical_id & mda & 0xffff) != 0;

	logical_id = GET_APIC_LOGICAL_ID(logical_id);

	चयन (kvm_lapic_get_reg(apic, APIC_DFR)) अणु
	हाल APIC_DFR_FLAT:
		वापस (logical_id & mda) != 0;
	हाल APIC_DFR_CLUSTER:
		वापस ((logical_id >> 4) == (mda >> 4))
		       && (logical_id & mda & 0xf) != 0;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* The KVM local APIC implementation has two quirks:
 *
 *  - Real hardware delivers पूर्णांकerrupts destined to x2APIC ID > 0xff to LAPICs
 *    in xAPIC mode अगर the "destination & 0xff" matches its xAPIC ID.
 *    KVM करोesn't करो that aliasing.
 *
 *  - in-kernel IOAPIC messages have to be delivered directly to
 *    x2APIC, because the kernel करोes not support पूर्णांकerrupt remapping.
 *    In order to support broadcast without पूर्णांकerrupt remapping, x2APIC
 *    reग_लिखोs the destination of non-IPI messages from APIC_BROADCAST
 *    to X2APIC_BROADCAST.
 *
 * The broadcast quirk can be disabled with KVM_CAP_X2APIC_API.  This is
 * important when userspace wants to use x2APIC-क्रमmat MSIs, because
 * APIC_BROADCAST (0xff) is a legal route क्रम "cluster 0, CPUs 0-7".
 */
अटल u32 kvm_apic_mda(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक dest_id,
		काष्ठा kvm_lapic *source, काष्ठा kvm_lapic *target)
अणु
	bool ipi = source != शून्य;

	अगर (!vcpu->kvm->arch.x2apic_broadcast_quirk_disabled &&
	    !ipi && dest_id == APIC_BROADCAST && apic_x2apic_mode(target))
		वापस X2APIC_BROADCAST;

	वापस dest_id;
पूर्ण

bool kvm_apic_match_dest(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_lapic *source,
			   पूर्णांक लघुhand, अचिन्हित पूर्णांक dest, पूर्णांक dest_mode)
अणु
	काष्ठा kvm_lapic *target = vcpu->arch.apic;
	u32 mda = kvm_apic_mda(vcpu, dest, source, target);

	ASSERT(target);
	चयन (लघुhand) अणु
	हाल APIC_DEST_NOSHORT:
		अगर (dest_mode == APIC_DEST_PHYSICAL)
			वापस kvm_apic_match_physical_addr(target, mda);
		अन्यथा
			वापस kvm_apic_match_logical_addr(target, mda);
	हाल APIC_DEST_SELF:
		वापस target == source;
	हाल APIC_DEST_ALLINC:
		वापस true;
	हाल APIC_DEST_ALLBUT:
		वापस target != source;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kvm_apic_match_dest);

पूर्णांक kvm_vector_to_index(u32 vector, u32 dest_vcpus,
		       स्थिर अचिन्हित दीर्घ *biपंचांगap, u32 biपंचांगap_size)
अणु
	u32 mod;
	पूर्णांक i, idx = -1;

	mod = vector % dest_vcpus;

	क्रम (i = 0; i <= mod; i++) अणु
		idx = find_next_bit(biपंचांगap, biपंचांगap_size, idx + 1);
		BUG_ON(idx == biपंचांगap_size);
	पूर्ण

	वापस idx;
पूर्ण

अटल व्योम kvm_apic_disabled_lapic_found(काष्ठा kvm *kvm)
अणु
	अगर (!kvm->arch.disabled_lapic_found) अणु
		kvm->arch.disabled_lapic_found = true;
		prपूर्णांकk(KERN_INFO
		       "Disabled LAPIC found during irq injection\n");
	पूर्ण
पूर्ण

अटल bool kvm_apic_is_broadcast_dest(काष्ठा kvm *kvm, काष्ठा kvm_lapic **src,
		काष्ठा kvm_lapic_irq *irq, काष्ठा kvm_apic_map *map)
अणु
	अगर (kvm->arch.x2apic_broadcast_quirk_disabled) अणु
		अगर ((irq->dest_id == APIC_BROADCAST &&
				map->mode != KVM_APIC_MODE_X2APIC))
			वापस true;
		अगर (irq->dest_id == X2APIC_BROADCAST)
			वापस true;
	पूर्ण अन्यथा अणु
		bool x2apic_ipi = src && *src && apic_x2apic_mode(*src);
		अगर (irq->dest_id == (x2apic_ipi ?
		                     X2APIC_BROADCAST : APIC_BROADCAST))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Return true अगर the पूर्णांकerrupt can be handled by using *biपंचांगap as index mask
 * क्रम valid destinations in *dst array.
 * Return false अगर kvm_apic_map_get_dest_lapic did nothing useful.
 * Note: we may have zero kvm_lapic destinations when we वापस true, which
 * means that the पूर्णांकerrupt should be dropped.  In this हाल, *biपंचांगap would be
 * zero and *dst undefined.
 */
अटल अंतरभूत bool kvm_apic_map_get_dest_lapic(काष्ठा kvm *kvm,
		काष्ठा kvm_lapic **src, काष्ठा kvm_lapic_irq *irq,
		काष्ठा kvm_apic_map *map, काष्ठा kvm_lapic ***dst,
		अचिन्हित दीर्घ *biपंचांगap)
अणु
	पूर्णांक i, lowest;

	अगर (irq->लघुhand == APIC_DEST_SELF && src) अणु
		*dst = src;
		*biपंचांगap = 1;
		वापस true;
	पूर्ण अन्यथा अगर (irq->लघुhand)
		वापस false;

	अगर (!map || kvm_apic_is_broadcast_dest(kvm, src, irq, map))
		वापस false;

	अगर (irq->dest_mode == APIC_DEST_PHYSICAL) अणु
		अगर (irq->dest_id > map->max_apic_id) अणु
			*biपंचांगap = 0;
		पूर्ण अन्यथा अणु
			u32 dest_id = array_index_nospec(irq->dest_id, map->max_apic_id + 1);
			*dst = &map->phys_map[dest_id];
			*biपंचांगap = 1;
		पूर्ण
		वापस true;
	पूर्ण

	*biपंचांगap = 0;
	अगर (!kvm_apic_map_get_logical_dest(map, irq->dest_id, dst,
				(u16 *)biपंचांगap))
		वापस false;

	अगर (!kvm_lowest_prio_delivery(irq))
		वापस true;

	अगर (!kvm_vector_hashing_enabled()) अणु
		lowest = -1;
		क्रम_each_set_bit(i, biपंचांगap, 16) अणु
			अगर (!(*dst)[i])
				जारी;
			अगर (lowest < 0)
				lowest = i;
			अन्यथा अगर (kvm_apic_compare_prio((*dst)[i]->vcpu,
						(*dst)[lowest]->vcpu) < 0)
				lowest = i;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!*biपंचांगap)
			वापस true;

		lowest = kvm_vector_to_index(irq->vector, hweight16(*biपंचांगap),
				biपंचांगap, 16);

		अगर (!(*dst)[lowest]) अणु
			kvm_apic_disabled_lapic_found(kvm);
			*biपंचांगap = 0;
			वापस true;
		पूर्ण
	पूर्ण

	*biपंचांगap = (lowest >= 0) ? 1 << lowest : 0;

	वापस true;
पूर्ण

bool kvm_irq_delivery_to_apic_fast(काष्ठा kvm *kvm, काष्ठा kvm_lapic *src,
		काष्ठा kvm_lapic_irq *irq, पूर्णांक *r, काष्ठा dest_map *dest_map)
अणु
	काष्ठा kvm_apic_map *map;
	अचिन्हित दीर्घ biपंचांगap;
	काष्ठा kvm_lapic **dst = शून्य;
	पूर्णांक i;
	bool ret;

	*r = -1;

	अगर (irq->लघुhand == APIC_DEST_SELF) अणु
		*r = kvm_apic_set_irq(src->vcpu, irq, dest_map);
		वापस true;
	पूर्ण

	rcu_पढ़ो_lock();
	map = rcu_dereference(kvm->arch.apic_map);

	ret = kvm_apic_map_get_dest_lapic(kvm, &src, irq, map, &dst, &biपंचांगap);
	अगर (ret) अणु
		*r = 0;
		क्रम_each_set_bit(i, &biपंचांगap, 16) अणु
			अगर (!dst[i])
				जारी;
			*r += kvm_apic_set_irq(dst[i]->vcpu, irq, dest_map);
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/*
 * This routine tries to handle पूर्णांकerrupts in posted mode, here is how
 * it deals with dअगरferent हालs:
 * - For single-destination पूर्णांकerrupts, handle it in posted mode
 * - Else अगर vector hashing is enabled and it is a lowest-priority
 *   पूर्णांकerrupt, handle it in posted mode and use the following mechanism
 *   to find the destination vCPU.
 *	1. For lowest-priority पूर्णांकerrupts, store all the possible
 *	   destination vCPUs in an array.
 *	2. Use "guest vector % max number of destination vCPUs" to find
 *	   the right destination vCPU in the array क्रम the lowest-priority
 *	   पूर्णांकerrupt.
 * - Otherwise, use remapped mode to inject the पूर्णांकerrupt.
 */
bool kvm_पूर्णांकr_is_single_vcpu_fast(काष्ठा kvm *kvm, काष्ठा kvm_lapic_irq *irq,
			काष्ठा kvm_vcpu **dest_vcpu)
अणु
	काष्ठा kvm_apic_map *map;
	अचिन्हित दीर्घ biपंचांगap;
	काष्ठा kvm_lapic **dst = शून्य;
	bool ret = false;

	अगर (irq->लघुhand)
		वापस false;

	rcu_पढ़ो_lock();
	map = rcu_dereference(kvm->arch.apic_map);

	अगर (kvm_apic_map_get_dest_lapic(kvm, शून्य, irq, map, &dst, &biपंचांगap) &&
			hweight16(biपंचांगap) == 1) अणु
		अचिन्हित दीर्घ i = find_first_bit(&biपंचांगap, 16);

		अगर (dst[i]) अणु
			*dest_vcpu = dst[i]->vcpu;
			ret = true;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/*
 * Add a pending IRQ पूर्णांकo lapic.
 * Return 1 अगर successfully added and 0 अगर discarded.
 */
अटल पूर्णांक __apic_accept_irq(काष्ठा kvm_lapic *apic, पूर्णांक delivery_mode,
			     पूर्णांक vector, पूर्णांक level, पूर्णांक trig_mode,
			     काष्ठा dest_map *dest_map)
अणु
	पूर्णांक result = 0;
	काष्ठा kvm_vcpu *vcpu = apic->vcpu;

	trace_kvm_apic_accept_irq(vcpu->vcpu_id, delivery_mode,
				  trig_mode, vector);
	चयन (delivery_mode) अणु
	हाल APIC_DM_LOWEST:
		vcpu->arch.apic_arb_prio++;
		fallthrough;
	हाल APIC_DM_FIXED:
		अगर (unlikely(trig_mode && !level))
			अवरोध;

		/* FIXME add logic क्रम vcpu on reset */
		अगर (unlikely(!apic_enabled(apic)))
			अवरोध;

		result = 1;

		अगर (dest_map) अणु
			__set_bit(vcpu->vcpu_id, dest_map->map);
			dest_map->vectors[vcpu->vcpu_id] = vector;
		पूर्ण

		अगर (apic_test_vector(vector, apic->regs + APIC_TMR) != !!trig_mode) अणु
			अगर (trig_mode)
				kvm_lapic_set_vector(vector,
						     apic->regs + APIC_TMR);
			अन्यथा
				kvm_lapic_clear_vector(vector,
						       apic->regs + APIC_TMR);
		पूर्ण

		अगर (अटल_call(kvm_x86_deliver_posted_पूर्णांकerrupt)(vcpu, vector)) अणु
			kvm_lapic_set_irr(vector, apic);
			kvm_make_request(KVM_REQ_EVENT, vcpu);
			kvm_vcpu_kick(vcpu);
		पूर्ण
		अवरोध;

	हाल APIC_DM_REMRD:
		result = 1;
		vcpu->arch.pv.pv_unhalted = 1;
		kvm_make_request(KVM_REQ_EVENT, vcpu);
		kvm_vcpu_kick(vcpu);
		अवरोध;

	हाल APIC_DM_SMI:
		result = 1;
		kvm_make_request(KVM_REQ_SMI, vcpu);
		kvm_vcpu_kick(vcpu);
		अवरोध;

	हाल APIC_DM_NMI:
		result = 1;
		kvm_inject_nmi(vcpu);
		kvm_vcpu_kick(vcpu);
		अवरोध;

	हाल APIC_DM_INIT:
		अगर (!trig_mode || level) अणु
			result = 1;
			/* assumes that there are only KVM_APIC_INIT/SIPI */
			apic->pending_events = (1UL << KVM_APIC_INIT);
			kvm_make_request(KVM_REQ_EVENT, vcpu);
			kvm_vcpu_kick(vcpu);
		पूर्ण
		अवरोध;

	हाल APIC_DM_STARTUP:
		result = 1;
		apic->sipi_vector = vector;
		/* make sure sipi_vector is visible क्रम the receiver */
		smp_wmb();
		set_bit(KVM_APIC_SIPI, &apic->pending_events);
		kvm_make_request(KVM_REQ_EVENT, vcpu);
		kvm_vcpu_kick(vcpu);
		अवरोध;

	हाल APIC_DM_EXTINT:
		/*
		 * Should only be called by kvm_apic_local_deliver() with LVT0,
		 * beक्रमe NMI watchकरोg was enabled. Alपढ़ोy handled by
		 * kvm_apic_accept_pic_पूर्णांकr().
		 */
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "TODO: unsupported delivery mode %x\n",
		       delivery_mode);
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

/*
 * This routine identअगरies the destination vcpus mask meant to receive the
 * IOAPIC पूर्णांकerrupts. It either uses kvm_apic_map_get_dest_lapic() to find
 * out the destination vcpus array and set the biपंचांगap or it traverses to
 * each available vcpu to identअगरy the same.
 */
व्योम kvm_biपंचांगap_or_dest_vcpus(काष्ठा kvm *kvm, काष्ठा kvm_lapic_irq *irq,
			      अचिन्हित दीर्घ *vcpu_biपंचांगap)
अणु
	काष्ठा kvm_lapic **dest_vcpu = शून्य;
	काष्ठा kvm_lapic *src = शून्य;
	काष्ठा kvm_apic_map *map;
	काष्ठा kvm_vcpu *vcpu;
	अचिन्हित दीर्घ biपंचांगap;
	पूर्णांक i, vcpu_idx;
	bool ret;

	rcu_पढ़ो_lock();
	map = rcu_dereference(kvm->arch.apic_map);

	ret = kvm_apic_map_get_dest_lapic(kvm, &src, irq, map, &dest_vcpu,
					  &biपंचांगap);
	अगर (ret) अणु
		क्रम_each_set_bit(i, &biपंचांगap, 16) अणु
			अगर (!dest_vcpu[i])
				जारी;
			vcpu_idx = dest_vcpu[i]->vcpu->vcpu_idx;
			__set_bit(vcpu_idx, vcpu_biपंचांगap);
		पूर्ण
	पूर्ण अन्यथा अणु
		kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
			अगर (!kvm_apic_present(vcpu))
				जारी;
			अगर (!kvm_apic_match_dest(vcpu, शून्य,
						 irq->लघुhand,
						 irq->dest_id,
						 irq->dest_mode))
				जारी;
			__set_bit(i, vcpu_biपंचांगap);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक kvm_apic_compare_prio(काष्ठा kvm_vcpu *vcpu1, काष्ठा kvm_vcpu *vcpu2)
अणु
	वापस vcpu1->arch.apic_arb_prio - vcpu2->arch.apic_arb_prio;
पूर्ण

अटल bool kvm_ioapic_handles_vector(काष्ठा kvm_lapic *apic, पूर्णांक vector)
अणु
	वापस test_bit(vector, apic->vcpu->arch.ioapic_handled_vectors);
पूर्ण

अटल व्योम kvm_ioapic_send_eoi(काष्ठा kvm_lapic *apic, पूर्णांक vector)
अणु
	पूर्णांक trigger_mode;

	/* Eoi the ioapic only अगर the ioapic करोesn't own the vector. */
	अगर (!kvm_ioapic_handles_vector(apic, vector))
		वापस;

	/* Request a KVM निकास to inक्रमm the userspace IOAPIC. */
	अगर (irqchip_split(apic->vcpu->kvm)) अणु
		apic->vcpu->arch.pending_ioapic_eoi = vector;
		kvm_make_request(KVM_REQ_IOAPIC_EOI_EXIT, apic->vcpu);
		वापस;
	पूर्ण

	अगर (apic_test_vector(vector, apic->regs + APIC_TMR))
		trigger_mode = IOAPIC_LEVEL_TRIG;
	अन्यथा
		trigger_mode = IOAPIC_EDGE_TRIG;

	kvm_ioapic_update_eoi(apic->vcpu, vector, trigger_mode);
पूर्ण

अटल पूर्णांक apic_set_eoi(काष्ठा kvm_lapic *apic)
अणु
	पूर्णांक vector = apic_find_highest_isr(apic);

	trace_kvm_eoi(apic, vector);

	/*
	 * Not every ग_लिखो EOI will has corresponding ISR,
	 * one example is when Kernel check समयr on setup_IO_APIC
	 */
	अगर (vector == -1)
		वापस vector;

	apic_clear_isr(vector, apic);
	apic_update_ppr(apic);

	अगर (to_hv_vcpu(apic->vcpu) &&
	    test_bit(vector, to_hv_synic(apic->vcpu)->vec_biपंचांगap))
		kvm_hv_synic_send_eoi(apic->vcpu, vector);

	kvm_ioapic_send_eoi(apic, vector);
	kvm_make_request(KVM_REQ_EVENT, apic->vcpu);
	वापस vector;
पूर्ण

/*
 * this पूर्णांकerface assumes a trap-like निकास, which has alपढ़ोy finished
 * desired side effect including vISR and vPPR update.
 */
व्योम kvm_apic_set_eoi_accelerated(काष्ठा kvm_vcpu *vcpu, पूर्णांक vector)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	trace_kvm_eoi(apic, vector);

	kvm_ioapic_send_eoi(apic, vector);
	kvm_make_request(KVM_REQ_EVENT, apic->vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_apic_set_eoi_accelerated);

व्योम kvm_apic_send_ipi(काष्ठा kvm_lapic *apic, u32 icr_low, u32 icr_high)
अणु
	काष्ठा kvm_lapic_irq irq;

	irq.vector = icr_low & APIC_VECTOR_MASK;
	irq.delivery_mode = icr_low & APIC_MODE_MASK;
	irq.dest_mode = icr_low & APIC_DEST_MASK;
	irq.level = (icr_low & APIC_INT_ASSERT) != 0;
	irq.trig_mode = icr_low & APIC_INT_LEVELTRIG;
	irq.लघुhand = icr_low & APIC_SHORT_MASK;
	irq.msi_redir_hपूर्णांक = false;
	अगर (apic_x2apic_mode(apic))
		irq.dest_id = icr_high;
	अन्यथा
		irq.dest_id = GET_APIC_DEST_FIELD(icr_high);

	trace_kvm_apic_ipi(icr_low, irq.dest_id);

	kvm_irq_delivery_to_apic(apic->vcpu->kvm, apic, &irq, शून्य);
पूर्ण

अटल u32 apic_get_पंचांगcct(काष्ठा kvm_lapic *apic)
अणु
	kसमय_प्रकार reमुख्यing, now;
	s64 ns;
	u32 पंचांगcct;

	ASSERT(apic != शून्य);

	/* अगर initial count is 0, current count should also be 0 */
	अगर (kvm_lapic_get_reg(apic, APIC_TMICT) == 0 ||
		apic->lapic_समयr.period == 0)
		वापस 0;

	now = kसमय_get();
	reमुख्यing = kसमय_sub(apic->lapic_समयr.target_expiration, now);
	अगर (kसमय_प्रकारo_ns(reमुख्यing) < 0)
		reमुख्यing = 0;

	ns = mod_64(kसमय_प्रकारo_ns(reमुख्यing), apic->lapic_समयr.period);
	पंचांगcct = भाग64_u64(ns,
			 (APIC_BUS_CYCLE_NS * apic->भागide_count));

	वापस पंचांगcct;
पूर्ण

अटल व्योम __report_tpr_access(काष्ठा kvm_lapic *apic, bool ग_लिखो)
अणु
	काष्ठा kvm_vcpu *vcpu = apic->vcpu;
	काष्ठा kvm_run *run = vcpu->run;

	kvm_make_request(KVM_REQ_REPORT_TPR_ACCESS, vcpu);
	run->tpr_access.rip = kvm_rip_पढ़ो(vcpu);
	run->tpr_access.is_ग_लिखो = ग_लिखो;
पूर्ण

अटल अंतरभूत व्योम report_tpr_access(काष्ठा kvm_lapic *apic, bool ग_लिखो)
अणु
	अगर (apic->vcpu->arch.tpr_access_reporting)
		__report_tpr_access(apic, ग_लिखो);
पूर्ण

अटल u32 __apic_पढ़ो(काष्ठा kvm_lapic *apic, अचिन्हित पूर्णांक offset)
अणु
	u32 val = 0;

	अगर (offset >= LAPIC_MMIO_LENGTH)
		वापस 0;

	चयन (offset) अणु
	हाल APIC_ARBPRI:
		अवरोध;

	हाल APIC_TMCCT:	/* Timer CCR */
		अगर (apic_lvtt_tscdeadline(apic))
			वापस 0;

		val = apic_get_पंचांगcct(apic);
		अवरोध;
	हाल APIC_PROCPRI:
		apic_update_ppr(apic);
		val = kvm_lapic_get_reg(apic, offset);
		अवरोध;
	हाल APIC_TASKPRI:
		report_tpr_access(apic, false);
		fallthrough;
	शेष:
		val = kvm_lapic_get_reg(apic, offset);
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

अटल अंतरभूत काष्ठा kvm_lapic *to_lapic(काष्ठा kvm_io_device *dev)
अणु
	वापस container_of(dev, काष्ठा kvm_lapic, dev);
पूर्ण

#घोषणा APIC_REG_MASK(reg)	(1ull << ((reg) >> 4))
#घोषणा APIC_REGS_MASK(first, count) \
	(APIC_REG_MASK(first) * ((1ull << (count)) - 1))

पूर्णांक kvm_lapic_reg_पढ़ो(काष्ठा kvm_lapic *apic, u32 offset, पूर्णांक len,
		व्योम *data)
अणु
	अचिन्हित अक्षर alignment = offset & 0xf;
	u32 result;
	/* this biपंचांगask has a bit cleared क्रम each reserved रेजिस्टर */
	u64 valid_reg_mask =
		APIC_REG_MASK(APIC_ID) |
		APIC_REG_MASK(APIC_LVR) |
		APIC_REG_MASK(APIC_TASKPRI) |
		APIC_REG_MASK(APIC_PROCPRI) |
		APIC_REG_MASK(APIC_LDR) |
		APIC_REG_MASK(APIC_DFR) |
		APIC_REG_MASK(APIC_SPIV) |
		APIC_REGS_MASK(APIC_ISR, APIC_ISR_NR) |
		APIC_REGS_MASK(APIC_TMR, APIC_ISR_NR) |
		APIC_REGS_MASK(APIC_IRR, APIC_ISR_NR) |
		APIC_REG_MASK(APIC_ESR) |
		APIC_REG_MASK(APIC_ICR) |
		APIC_REG_MASK(APIC_ICR2) |
		APIC_REG_MASK(APIC_LVTT) |
		APIC_REG_MASK(APIC_LVTTHMR) |
		APIC_REG_MASK(APIC_LVTPC) |
		APIC_REG_MASK(APIC_LVT0) |
		APIC_REG_MASK(APIC_LVT1) |
		APIC_REG_MASK(APIC_LVTERR) |
		APIC_REG_MASK(APIC_TMICT) |
		APIC_REG_MASK(APIC_TMCCT) |
		APIC_REG_MASK(APIC_TDCR);

	/* ARBPRI is not valid on x2APIC */
	अगर (!apic_x2apic_mode(apic))
		valid_reg_mask |= APIC_REG_MASK(APIC_ARBPRI);

	अगर (alignment + len > 4)
		वापस 1;

	अगर (offset > 0x3f0 || !(valid_reg_mask & APIC_REG_MASK(offset)))
		वापस 1;

	result = __apic_पढ़ो(apic, offset & ~0xf);

	trace_kvm_apic_पढ़ो(offset, result);

	चयन (len) अणु
	हाल 1:
	हाल 2:
	हाल 4:
		स_नकल(data, (अक्षर *)&result + alignment, len);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Local APIC read with len = %x, "
		       "should be 1,2, or 4 instead\n", len);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_lapic_reg_पढ़ो);

अटल पूर्णांक apic_mmio_in_range(काष्ठा kvm_lapic *apic, gpa_t addr)
अणु
	वापस addr >= apic->base_address &&
		addr < apic->base_address + LAPIC_MMIO_LENGTH;
पूर्ण

अटल पूर्णांक apic_mmio_पढ़ो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *this,
			   gpa_t address, पूर्णांक len, व्योम *data)
अणु
	काष्ठा kvm_lapic *apic = to_lapic(this);
	u32 offset = address - apic->base_address;

	अगर (!apic_mmio_in_range(apic, address))
		वापस -EOPNOTSUPP;

	अगर (!kvm_apic_hw_enabled(apic) || apic_x2apic_mode(apic)) अणु
		अगर (!kvm_check_has_quirk(vcpu->kvm,
					 KVM_X86_QUIRK_LAPIC_MMIO_HOLE))
			वापस -EOPNOTSUPP;

		स_रखो(data, 0xff, len);
		वापस 0;
	पूर्ण

	kvm_lapic_reg_पढ़ो(apic, offset, len, data);

	वापस 0;
पूर्ण

अटल व्योम update_भागide_count(काष्ठा kvm_lapic *apic)
अणु
	u32 पंचांगp1, पंचांगp2, tdcr;

	tdcr = kvm_lapic_get_reg(apic, APIC_TDCR);
	पंचांगp1 = tdcr & 0xf;
	पंचांगp2 = ((पंचांगp1 & 0x3) | ((पंचांगp1 & 0x8) >> 1)) + 1;
	apic->भागide_count = 0x1 << (पंचांगp2 & 0x7);
पूर्ण

अटल व्योम limit_periodic_समयr_frequency(काष्ठा kvm_lapic *apic)
अणु
	/*
	 * Do not allow the guest to program periodic समयrs with small
	 * पूर्णांकerval, since the hrसमयrs are not throttled by the host
	 * scheduler.
	 */
	अगर (apic_lvtt_period(apic) && apic->lapic_समयr.period) अणु
		s64 min_period = min_समयr_period_us * 1000LL;

		अगर (apic->lapic_समयr.period < min_period) अणु
			pr_info_ratelimited(
			    "kvm: vcpu %i: requested %lld ns "
			    "lapic timer period limited to %lld ns\n",
			    apic->vcpu->vcpu_id,
			    apic->lapic_समयr.period, min_period);
			apic->lapic_समयr.period = min_period;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cancel_hv_समयr(काष्ठा kvm_lapic *apic);

अटल व्योम cancel_apic_समयr(काष्ठा kvm_lapic *apic)
अणु
	hrसमयr_cancel(&apic->lapic_समयr.समयr);
	preempt_disable();
	अगर (apic->lapic_समयr.hv_समयr_in_use)
		cancel_hv_समयr(apic);
	preempt_enable();
पूर्ण

अटल व्योम apic_update_lvtt(काष्ठा kvm_lapic *apic)
अणु
	u32 समयr_mode = kvm_lapic_get_reg(apic, APIC_LVTT) &
			apic->lapic_समयr.समयr_mode_mask;

	अगर (apic->lapic_समयr.समयr_mode != समयr_mode) अणु
		अगर (apic_lvtt_tscdeadline(apic) != (समयr_mode ==
				APIC_LVT_TIMER_TSCDEADLINE)) अणु
			cancel_apic_समयr(apic);
			kvm_lapic_set_reg(apic, APIC_TMICT, 0);
			apic->lapic_समयr.period = 0;
			apic->lapic_समयr.tscdeadline = 0;
		पूर्ण
		apic->lapic_समयr.समयr_mode = समयr_mode;
		limit_periodic_समयr_frequency(apic);
	पूर्ण
पूर्ण

/*
 * On APICv, this test will cause a busy रुको
 * during a higher-priority task.
 */

अटल bool lapic_समयr_पूर्णांक_injected(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	u32 reg = kvm_lapic_get_reg(apic, APIC_LVTT);

	अगर (kvm_apic_hw_enabled(apic)) अणु
		पूर्णांक vec = reg & APIC_VECTOR_MASK;
		व्योम *biपंचांगap = apic->regs + APIC_ISR;

		अगर (vcpu->arch.apicv_active)
			biपंचांगap = apic->regs + APIC_IRR;

		अगर (apic_test_vector(vec, biपंचांगap))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत व्योम __रुको_lapic_expire(काष्ठा kvm_vcpu *vcpu, u64 guest_cycles)
अणु
	u64 समयr_advance_ns = vcpu->arch.apic->lapic_समयr.समयr_advance_ns;

	/*
	 * If the guest TSC is running at a dअगरferent ratio than the host, then
	 * convert the delay to nanoseconds to achieve an accurate delay.  Note
	 * that __delay() uses delay_tsc whenever the hardware has TSC, thus
	 * always क्रम VMX enabled hardware.
	 */
	अगर (vcpu->arch.tsc_scaling_ratio == kvm_शेष_tsc_scaling_ratio) अणु
		__delay(min(guest_cycles,
			nsec_to_cycles(vcpu, समयr_advance_ns)));
	पूर्ण अन्यथा अणु
		u64 delay_ns = guest_cycles * 1000000ULL;
		करो_भाग(delay_ns, vcpu->arch.भव_tsc_khz);
		ndelay(min_t(u32, delay_ns, समयr_advance_ns));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम adjust_lapic_समयr_advance(काष्ठा kvm_vcpu *vcpu,
					      s64 advance_expire_delta)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	u32 समयr_advance_ns = apic->lapic_समयr.समयr_advance_ns;
	u64 ns;

	/* Do not adjust क्रम tiny fluctuations or large अक्रमom spikes. */
	अगर (असल(advance_expire_delta) > LAPIC_TIMER_ADVANCE_ADJUST_MAX ||
	    असल(advance_expire_delta) < LAPIC_TIMER_ADVANCE_ADJUST_MIN)
		वापस;

	/* too early */
	अगर (advance_expire_delta < 0) अणु
		ns = -advance_expire_delta * 1000000ULL;
		करो_भाग(ns, vcpu->arch.भव_tsc_khz);
		समयr_advance_ns -= ns/LAPIC_TIMER_ADVANCE_ADJUST_STEP;
	पूर्ण अन्यथा अणु
	/* too late */
		ns = advance_expire_delta * 1000000ULL;
		करो_भाग(ns, vcpu->arch.भव_tsc_khz);
		समयr_advance_ns += ns/LAPIC_TIMER_ADVANCE_ADJUST_STEP;
	पूर्ण

	अगर (unlikely(समयr_advance_ns > LAPIC_TIMER_ADVANCE_NS_MAX))
		समयr_advance_ns = LAPIC_TIMER_ADVANCE_NS_INIT;
	apic->lapic_समयr.समयr_advance_ns = समयr_advance_ns;
पूर्ण

अटल व्योम __kvm_रुको_lapic_expire(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	u64 guest_tsc, tsc_deadline;

	tsc_deadline = apic->lapic_समयr.expired_tscdeadline;
	apic->lapic_समयr.expired_tscdeadline = 0;
	guest_tsc = kvm_पढ़ो_l1_tsc(vcpu, rdtsc());
	apic->lapic_समयr.advance_expire_delta = guest_tsc - tsc_deadline;

	अगर (lapic_समयr_advance_dynamic) अणु
		adjust_lapic_समयr_advance(vcpu, apic->lapic_समयr.advance_expire_delta);
		/*
		 * If the समयr fired early, reपढ़ो the TSC to account क्रम the
		 * overhead of the above adjusपंचांगent to aव्योम रुकोing दीर्घer
		 * than is necessary.
		 */
		अगर (guest_tsc < tsc_deadline)
			guest_tsc = kvm_पढ़ो_l1_tsc(vcpu, rdtsc());
	पूर्ण

	अगर (guest_tsc < tsc_deadline)
		__रुको_lapic_expire(vcpu, tsc_deadline - guest_tsc);
पूर्ण

व्योम kvm_रुको_lapic_expire(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (lapic_in_kernel(vcpu) &&
	    vcpu->arch.apic->lapic_समयr.expired_tscdeadline &&
	    vcpu->arch.apic->lapic_समयr.समयr_advance_ns &&
	    lapic_समयr_पूर्णांक_injected(vcpu))
		__kvm_रुको_lapic_expire(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_रुको_lapic_expire);

अटल व्योम kvm_apic_inject_pending_समयr_irqs(काष्ठा kvm_lapic *apic)
अणु
	काष्ठा kvm_समयr *kसमयr = &apic->lapic_समयr;

	kvm_apic_local_deliver(apic, APIC_LVTT);
	अगर (apic_lvtt_tscdeadline(apic)) अणु
		kसमयr->tscdeadline = 0;
	पूर्ण अन्यथा अगर (apic_lvtt_oneshot(apic)) अणु
		kसमयr->tscdeadline = 0;
		kसमयr->target_expiration = 0;
	पूर्ण
पूर्ण

अटल व्योम apic_समयr_expired(काष्ठा kvm_lapic *apic, bool from_समयr_fn)
अणु
	काष्ठा kvm_vcpu *vcpu = apic->vcpu;
	काष्ठा kvm_समयr *kसमयr = &apic->lapic_समयr;

	अगर (atomic_पढ़ो(&apic->lapic_समयr.pending))
		वापस;

	अगर (apic_lvtt_tscdeadline(apic) || kसमयr->hv_समयr_in_use)
		kसमयr->expired_tscdeadline = kसमयr->tscdeadline;

	अगर (!from_समयr_fn && vcpu->arch.apicv_active) अणु
		WARN_ON(kvm_get_running_vcpu() != vcpu);
		kvm_apic_inject_pending_समयr_irqs(apic);
		वापस;
	पूर्ण

	अगर (kvm_use_posted_समयr_पूर्णांकerrupt(apic->vcpu)) अणु
		/*
		 * Ensure the guest's समयr has truly expired beक्रमe posting an
		 * पूर्णांकerrupt.  Open code the relevant checks to aव्योम querying
		 * lapic_समयr_पूर्णांक_injected(), which will be false since the
		 * पूर्णांकerrupt isn't yet injected.  Waiting until after injecting
		 * is not an option since that won't help a posted पूर्णांकerrupt.
		 */
		अगर (vcpu->arch.apic->lapic_समयr.expired_tscdeadline &&
		    vcpu->arch.apic->lapic_समयr.समयr_advance_ns)
			__kvm_रुको_lapic_expire(vcpu);
		kvm_apic_inject_pending_समयr_irqs(apic);
		वापस;
	पूर्ण

	atomic_inc(&apic->lapic_समयr.pending);
	kvm_make_request(KVM_REQ_UNBLOCK, vcpu);
	अगर (from_समयr_fn)
		kvm_vcpu_kick(vcpu);
पूर्ण

अटल व्योम start_sw_tscdeadline(काष्ठा kvm_lapic *apic)
अणु
	काष्ठा kvm_समयr *kसमयr = &apic->lapic_समयr;
	u64 guest_tsc, tscdeadline = kसमयr->tscdeadline;
	u64 ns = 0;
	kसमय_प्रकार expire;
	काष्ठा kvm_vcpu *vcpu = apic->vcpu;
	अचिन्हित दीर्घ this_tsc_khz = vcpu->arch.भव_tsc_khz;
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार now;

	अगर (unlikely(!tscdeadline || !this_tsc_khz))
		वापस;

	local_irq_save(flags);

	now = kसमय_get();
	guest_tsc = kvm_पढ़ो_l1_tsc(vcpu, rdtsc());

	ns = (tscdeadline - guest_tsc) * 1000000ULL;
	करो_भाग(ns, this_tsc_khz);

	अगर (likely(tscdeadline > guest_tsc) &&
	    likely(ns > apic->lapic_समयr.समयr_advance_ns)) अणु
		expire = kसमय_add_ns(now, ns);
		expire = kसमय_sub_ns(expire, kसमयr->समयr_advance_ns);
		hrसमयr_start(&kसमयr->समयr, expire, HRTIMER_MODE_ABS_HARD);
	पूर्ण अन्यथा
		apic_समयr_expired(apic, false);

	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत u64 पंचांगict_to_ns(काष्ठा kvm_lapic *apic, u32 पंचांगict)
अणु
	वापस (u64)पंचांगict * APIC_BUS_CYCLE_NS * (u64)apic->भागide_count;
पूर्ण

अटल व्योम update_target_expiration(काष्ठा kvm_lapic *apic, uपूर्णांक32_t old_भागisor)
अणु
	kसमय_प्रकार now, reमुख्यing;
	u64 ns_reमुख्यing_old, ns_reमुख्यing_new;

	apic->lapic_समयr.period =
			पंचांगict_to_ns(apic, kvm_lapic_get_reg(apic, APIC_TMICT));
	limit_periodic_समयr_frequency(apic);

	now = kसमय_get();
	reमुख्यing = kसमय_sub(apic->lapic_समयr.target_expiration, now);
	अगर (kसमय_प्रकारo_ns(reमुख्यing) < 0)
		reमुख्यing = 0;

	ns_reमुख्यing_old = kसमय_प्रकारo_ns(reमुख्यing);
	ns_reमुख्यing_new = mul_u64_u32_भाग(ns_reमुख्यing_old,
	                                   apic->भागide_count, old_भागisor);

	apic->lapic_समयr.tscdeadline +=
		nsec_to_cycles(apic->vcpu, ns_reमुख्यing_new) -
		nsec_to_cycles(apic->vcpu, ns_reमुख्यing_old);
	apic->lapic_समयr.target_expiration = kसमय_add_ns(now, ns_reमुख्यing_new);
पूर्ण

अटल bool set_target_expiration(काष्ठा kvm_lapic *apic, u32 count_reg)
अणु
	kसमय_प्रकार now;
	u64 tscl = rdtsc();
	s64 deadline;

	now = kसमय_get();
	apic->lapic_समयr.period =
			पंचांगict_to_ns(apic, kvm_lapic_get_reg(apic, APIC_TMICT));

	अगर (!apic->lapic_समयr.period) अणु
		apic->lapic_समयr.tscdeadline = 0;
		वापस false;
	पूर्ण

	limit_periodic_समयr_frequency(apic);
	deadline = apic->lapic_समयr.period;

	अगर (apic_lvtt_period(apic) || apic_lvtt_oneshot(apic)) अणु
		अगर (unlikely(count_reg != APIC_TMICT)) अणु
			deadline = पंचांगict_to_ns(apic,
				     kvm_lapic_get_reg(apic, count_reg));
			अगर (unlikely(deadline <= 0))
				deadline = apic->lapic_समयr.period;
			अन्यथा अगर (unlikely(deadline > apic->lapic_समयr.period)) अणु
				pr_info_ratelimited(
				    "kvm: vcpu %i: requested lapic timer restore with "
				    "starting count register %#x=%u (%lld ns) > initial count (%lld ns). "
				    "Using initial count to start timer.\n",
				    apic->vcpu->vcpu_id,
				    count_reg,
				    kvm_lapic_get_reg(apic, count_reg),
				    deadline, apic->lapic_समयr.period);
				kvm_lapic_set_reg(apic, count_reg, 0);
				deadline = apic->lapic_समयr.period;
			पूर्ण
		पूर्ण
	पूर्ण

	apic->lapic_समयr.tscdeadline = kvm_पढ़ो_l1_tsc(apic->vcpu, tscl) +
		nsec_to_cycles(apic->vcpu, deadline);
	apic->lapic_समयr.target_expiration = kसमय_add_ns(now, deadline);

	वापस true;
पूर्ण

अटल व्योम advance_periodic_target_expiration(काष्ठा kvm_lapic *apic)
अणु
	kसमय_प्रकार now = kसमय_get();
	u64 tscl = rdtsc();
	kसमय_प्रकार delta;

	/*
	 * Synchronize both deadlines to the same समय source or
	 * dअगरferences in the periods (caused by dअगरferences in the
	 * underlying घड़ीs or numerical approximation errors) will
	 * cause the two to drअगरt apart over समय as the errors
	 * accumulate.
	 */
	apic->lapic_समयr.target_expiration =
		kसमय_add_ns(apic->lapic_समयr.target_expiration,
				apic->lapic_समयr.period);
	delta = kसमय_sub(apic->lapic_समयr.target_expiration, now);
	apic->lapic_समयr.tscdeadline = kvm_पढ़ो_l1_tsc(apic->vcpu, tscl) +
		nsec_to_cycles(apic->vcpu, delta);
पूर्ण

अटल व्योम start_sw_period(काष्ठा kvm_lapic *apic)
अणु
	अगर (!apic->lapic_समयr.period)
		वापस;

	अगर (kसमय_after(kसमय_get(),
			apic->lapic_समयr.target_expiration)) अणु
		apic_समयr_expired(apic, false);

		अगर (apic_lvtt_oneshot(apic))
			वापस;

		advance_periodic_target_expiration(apic);
	पूर्ण

	hrसमयr_start(&apic->lapic_समयr.समयr,
		apic->lapic_समयr.target_expiration,
		HRTIMER_MODE_ABS_HARD);
पूर्ण

bool kvm_lapic_hv_समयr_in_use(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!lapic_in_kernel(vcpu))
		वापस false;

	वापस vcpu->arch.apic->lapic_समयr.hv_समयr_in_use;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_lapic_hv_समयr_in_use);

अटल व्योम cancel_hv_समयr(काष्ठा kvm_lapic *apic)
अणु
	WARN_ON(preemptible());
	WARN_ON(!apic->lapic_समयr.hv_समयr_in_use);
	अटल_call(kvm_x86_cancel_hv_समयr)(apic->vcpu);
	apic->lapic_समयr.hv_समयr_in_use = false;
पूर्ण

अटल bool start_hv_समयr(काष्ठा kvm_lapic *apic)
अणु
	काष्ठा kvm_समयr *kसमयr = &apic->lapic_समयr;
	काष्ठा kvm_vcpu *vcpu = apic->vcpu;
	bool expired;

	WARN_ON(preemptible());
	अगर (!kvm_can_use_hv_समयr(vcpu))
		वापस false;

	अगर (!kसमयr->tscdeadline)
		वापस false;

	अगर (अटल_call(kvm_x86_set_hv_समयr)(vcpu, kसमयr->tscdeadline, &expired))
		वापस false;

	kसमयr->hv_समयr_in_use = true;
	hrसमयr_cancel(&kसमयr->समयr);

	/*
	 * To simplअगरy handling the periodic समयr, leave the hv समयr running
	 * even अगर the deadline समयr has expired, i.e. rely on the resulting
	 * VM-Exit to recompute the periodic समयr's target expiration.
	 */
	अगर (!apic_lvtt_period(apic)) अणु
		/*
		 * Cancel the hv समयr अगर the sw समयr fired जबतक the hv समयr
		 * was being programmed, or अगर the hv समयr itself expired.
		 */
		अगर (atomic_पढ़ो(&kसमयr->pending)) अणु
			cancel_hv_समयr(apic);
		पूर्ण अन्यथा अगर (expired) अणु
			apic_समयr_expired(apic, false);
			cancel_hv_समयr(apic);
		पूर्ण
	पूर्ण

	trace_kvm_hv_समयr_state(vcpu->vcpu_id, kसमयr->hv_समयr_in_use);

	वापस true;
पूर्ण

अटल व्योम start_sw_समयr(काष्ठा kvm_lapic *apic)
अणु
	काष्ठा kvm_समयr *kसमयr = &apic->lapic_समयr;

	WARN_ON(preemptible());
	अगर (apic->lapic_समयr.hv_समयr_in_use)
		cancel_hv_समयr(apic);
	अगर (!apic_lvtt_period(apic) && atomic_पढ़ो(&kसमयr->pending))
		वापस;

	अगर (apic_lvtt_period(apic) || apic_lvtt_oneshot(apic))
		start_sw_period(apic);
	अन्यथा अगर (apic_lvtt_tscdeadline(apic))
		start_sw_tscdeadline(apic);
	trace_kvm_hv_समयr_state(apic->vcpu->vcpu_id, false);
पूर्ण

अटल व्योम restart_apic_समयr(काष्ठा kvm_lapic *apic)
अणु
	preempt_disable();

	अगर (!apic_lvtt_period(apic) && atomic_पढ़ो(&apic->lapic_समयr.pending))
		जाओ out;

	अगर (!start_hv_समयr(apic))
		start_sw_समयr(apic);
out:
	preempt_enable();
पूर्ण

व्योम kvm_lapic_expired_hv_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	preempt_disable();
	/* If the preempt notअगरier has alपढ़ोy run, it also called apic_समयr_expired */
	अगर (!apic->lapic_समयr.hv_समयr_in_use)
		जाओ out;
	WARN_ON(rcuरुको_active(&vcpu->रुको));
	apic_समयr_expired(apic, false);
	cancel_hv_समयr(apic);

	अगर (apic_lvtt_period(apic) && apic->lapic_समयr.period) अणु
		advance_periodic_target_expiration(apic);
		restart_apic_समयr(apic);
	पूर्ण
out:
	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(kvm_lapic_expired_hv_समयr);

व्योम kvm_lapic_चयन_to_hv_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	restart_apic_समयr(vcpu->arch.apic);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_lapic_चयन_to_hv_समयr);

व्योम kvm_lapic_चयन_to_sw_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	preempt_disable();
	/* Possibly the TSC deadline समयr is not enabled yet */
	अगर (apic->lapic_समयr.hv_समयr_in_use)
		start_sw_समयr(apic);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(kvm_lapic_चयन_to_sw_समयr);

व्योम kvm_lapic_restart_hv_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	WARN_ON(!apic->lapic_समयr.hv_समयr_in_use);
	restart_apic_समयr(apic);
पूर्ण

अटल व्योम __start_apic_समयr(काष्ठा kvm_lapic *apic, u32 count_reg)
अणु
	atomic_set(&apic->lapic_समयr.pending, 0);

	अगर ((apic_lvtt_period(apic) || apic_lvtt_oneshot(apic))
	    && !set_target_expiration(apic, count_reg))
		वापस;

	restart_apic_समयr(apic);
पूर्ण

अटल व्योम start_apic_समयr(काष्ठा kvm_lapic *apic)
अणु
	__start_apic_समयr(apic, APIC_TMICT);
पूर्ण

अटल व्योम apic_manage_nmi_watchकरोg(काष्ठा kvm_lapic *apic, u32 lvt0_val)
अणु
	bool lvt0_in_nmi_mode = apic_lvt_nmi_mode(lvt0_val);

	अगर (apic->lvt0_in_nmi_mode != lvt0_in_nmi_mode) अणु
		apic->lvt0_in_nmi_mode = lvt0_in_nmi_mode;
		अगर (lvt0_in_nmi_mode) अणु
			atomic_inc(&apic->vcpu->kvm->arch.vapics_in_nmi_mode);
		पूर्ण अन्यथा
			atomic_dec(&apic->vcpu->kvm->arch.vapics_in_nmi_mode);
	पूर्ण
पूर्ण

पूर्णांक kvm_lapic_reg_ग_लिखो(काष्ठा kvm_lapic *apic, u32 reg, u32 val)
अणु
	पूर्णांक ret = 0;

	trace_kvm_apic_ग_लिखो(reg, val);

	चयन (reg) अणु
	हाल APIC_ID:		/* Local APIC ID */
		अगर (!apic_x2apic_mode(apic))
			kvm_apic_set_xapic_id(apic, val >> 24);
		अन्यथा
			ret = 1;
		अवरोध;

	हाल APIC_TASKPRI:
		report_tpr_access(apic, true);
		apic_set_tpr(apic, val & 0xff);
		अवरोध;

	हाल APIC_EOI:
		apic_set_eoi(apic);
		अवरोध;

	हाल APIC_LDR:
		अगर (!apic_x2apic_mode(apic))
			kvm_apic_set_ldr(apic, val & APIC_LDR_MASK);
		अन्यथा
			ret = 1;
		अवरोध;

	हाल APIC_DFR:
		अगर (!apic_x2apic_mode(apic))
			kvm_apic_set_dfr(apic, val | 0x0FFFFFFF);
		अन्यथा
			ret = 1;
		अवरोध;

	हाल APIC_SPIV: अणु
		u32 mask = 0x3ff;
		अगर (kvm_lapic_get_reg(apic, APIC_LVR) & APIC_LVR_सूचीECTED_EOI)
			mask |= APIC_SPIV_सूचीECTED_EOI;
		apic_set_spiv(apic, val & mask);
		अगर (!(val & APIC_SPIV_APIC_ENABLED)) अणु
			पूर्णांक i;
			u32 lvt_val;

			क्रम (i = 0; i < KVM_APIC_LVT_NUM; i++) अणु
				lvt_val = kvm_lapic_get_reg(apic,
						       APIC_LVTT + 0x10 * i);
				kvm_lapic_set_reg(apic, APIC_LVTT + 0x10 * i,
					     lvt_val | APIC_LVT_MASKED);
			पूर्ण
			apic_update_lvtt(apic);
			atomic_set(&apic->lapic_समयr.pending, 0);

		पूर्ण
		अवरोध;
	पूर्ण
	हाल APIC_ICR:
		/* No delay here, so we always clear the pending bit */
		val &= ~(1 << 12);
		kvm_apic_send_ipi(apic, val, kvm_lapic_get_reg(apic, APIC_ICR2));
		kvm_lapic_set_reg(apic, APIC_ICR, val);
		अवरोध;

	हाल APIC_ICR2:
		अगर (!apic_x2apic_mode(apic))
			val &= 0xff000000;
		kvm_lapic_set_reg(apic, APIC_ICR2, val);
		अवरोध;

	हाल APIC_LVT0:
		apic_manage_nmi_watchकरोg(apic, val);
		fallthrough;
	हाल APIC_LVTTHMR:
	हाल APIC_LVTPC:
	हाल APIC_LVT1:
	हाल APIC_LVTERR: अणु
		/* TODO: Check vector */
		माप_प्रकार size;
		u32 index;

		अगर (!kvm_apic_sw_enabled(apic))
			val |= APIC_LVT_MASKED;
		size = ARRAY_SIZE(apic_lvt_mask);
		index = array_index_nospec(
				(reg - APIC_LVTT) >> 4, size);
		val &= apic_lvt_mask[index];
		kvm_lapic_set_reg(apic, reg, val);
		अवरोध;
	पूर्ण

	हाल APIC_LVTT:
		अगर (!kvm_apic_sw_enabled(apic))
			val |= APIC_LVT_MASKED;
		val &= (apic_lvt_mask[0] | apic->lapic_समयr.समयr_mode_mask);
		kvm_lapic_set_reg(apic, APIC_LVTT, val);
		apic_update_lvtt(apic);
		अवरोध;

	हाल APIC_TMICT:
		अगर (apic_lvtt_tscdeadline(apic))
			अवरोध;

		cancel_apic_समयr(apic);
		kvm_lapic_set_reg(apic, APIC_TMICT, val);
		start_apic_समयr(apic);
		अवरोध;

	हाल APIC_TDCR: अणु
		uपूर्णांक32_t old_भागisor = apic->भागide_count;

		kvm_lapic_set_reg(apic, APIC_TDCR, val & 0xb);
		update_भागide_count(apic);
		अगर (apic->भागide_count != old_भागisor &&
				apic->lapic_समयr.period) अणु
			hrसमयr_cancel(&apic->lapic_समयr.समयr);
			update_target_expiration(apic, old_भागisor);
			restart_apic_समयr(apic);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल APIC_ESR:
		अगर (apic_x2apic_mode(apic) && val != 0)
			ret = 1;
		अवरोध;

	हाल APIC_SELF_IPI:
		अगर (apic_x2apic_mode(apic)) अणु
			kvm_lapic_reg_ग_लिखो(apic, APIC_ICR,
					    APIC_DEST_SELF | (val & APIC_VECTOR_MASK));
		पूर्ण अन्यथा
			ret = 1;
		अवरोध;
	शेष:
		ret = 1;
		अवरोध;
	पूर्ण

	kvm_recalculate_apic_map(apic->vcpu->kvm);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_lapic_reg_ग_लिखो);

अटल पूर्णांक apic_mmio_ग_लिखो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *this,
			    gpa_t address, पूर्णांक len, स्थिर व्योम *data)
अणु
	काष्ठा kvm_lapic *apic = to_lapic(this);
	अचिन्हित पूर्णांक offset = address - apic->base_address;
	u32 val;

	अगर (!apic_mmio_in_range(apic, address))
		वापस -EOPNOTSUPP;

	अगर (!kvm_apic_hw_enabled(apic) || apic_x2apic_mode(apic)) अणु
		अगर (!kvm_check_has_quirk(vcpu->kvm,
					 KVM_X86_QUIRK_LAPIC_MMIO_HOLE))
			वापस -EOPNOTSUPP;

		वापस 0;
	पूर्ण

	/*
	 * APIC रेजिस्टर must be aligned on 128-bits boundary.
	 * 32/64/128 bits रेजिस्टरs must be accessed thru 32 bits.
	 * Refer SDM 8.4.1
	 */
	अगर (len != 4 || (offset & 0xf))
		वापस 0;

	val = *(u32*)data;

	kvm_lapic_reg_ग_लिखो(apic, offset & 0xff0, val);

	वापस 0;
पूर्ण

व्योम kvm_lapic_set_eoi(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_lapic_reg_ग_लिखो(vcpu->arch.apic, APIC_EOI, 0);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_lapic_set_eoi);

/* emulate APIC access in a trap manner */
व्योम kvm_apic_ग_लिखो_nodecode(काष्ठा kvm_vcpu *vcpu, u32 offset)
अणु
	u32 val = 0;

	/* hw has करोne the conditional check and inst decode */
	offset &= 0xff0;

	kvm_lapic_reg_पढ़ो(vcpu->arch.apic, offset, 4, &val);

	/* TODO: optimize to just emulate side effect w/o one more ग_लिखो */
	kvm_lapic_reg_ग_लिखो(vcpu->arch.apic, offset, val);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_apic_ग_लिखो_nodecode);

व्योम kvm_मुक्त_lapic(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	अगर (!vcpu->arch.apic)
		वापस;

	hrसमयr_cancel(&apic->lapic_समयr.समयr);

	अगर (!(vcpu->arch.apic_base & MSR_IA32_APICBASE_ENABLE))
		अटल_branch_slow_dec_deferred(&apic_hw_disabled);

	अगर (!apic->sw_enabled)
		अटल_branch_slow_dec_deferred(&apic_sw_disabled);

	अगर (apic->regs)
		मुक्त_page((अचिन्हित दीर्घ)apic->regs);

	kमुक्त(apic);
पूर्ण

/*
 *----------------------------------------------------------------------
 * LAPIC पूर्णांकerface
 *----------------------------------------------------------------------
 */
u64 kvm_get_lapic_tscdeadline_msr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	अगर (!kvm_apic_present(vcpu) || !apic_lvtt_tscdeadline(apic))
		वापस 0;

	वापस apic->lapic_समयr.tscdeadline;
पूर्ण

व्योम kvm_set_lapic_tscdeadline_msr(काष्ठा kvm_vcpu *vcpu, u64 data)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	अगर (!kvm_apic_present(vcpu) || !apic_lvtt_tscdeadline(apic))
		वापस;

	hrसमयr_cancel(&apic->lapic_समयr.समयr);
	apic->lapic_समयr.tscdeadline = data;
	start_apic_समयr(apic);
पूर्ण

व्योम kvm_lapic_set_tpr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr8)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	apic_set_tpr(apic, ((cr8 & 0x0f) << 4)
		     | (kvm_lapic_get_reg(apic, APIC_TASKPRI) & 4));
पूर्ण

u64 kvm_lapic_get_cr8(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 tpr;

	tpr = (u64) kvm_lapic_get_reg(vcpu->arch.apic, APIC_TASKPRI);

	वापस (tpr & 0xf0) >> 4;
पूर्ण

व्योम kvm_lapic_set_base(काष्ठा kvm_vcpu *vcpu, u64 value)
अणु
	u64 old_value = vcpu->arch.apic_base;
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	अगर (!apic)
		value |= MSR_IA32_APICBASE_BSP;

	vcpu->arch.apic_base = value;

	अगर ((old_value ^ value) & MSR_IA32_APICBASE_ENABLE)
		kvm_update_cpuid_runसमय(vcpu);

	अगर (!apic)
		वापस;

	/* update jump label अगर enable bit changes */
	अगर ((old_value ^ value) & MSR_IA32_APICBASE_ENABLE) अणु
		अगर (value & MSR_IA32_APICBASE_ENABLE) अणु
			kvm_apic_set_xapic_id(apic, vcpu->vcpu_id);
			अटल_branch_slow_dec_deferred(&apic_hw_disabled);
			/* Check अगर there are APF page पढ़ोy requests pending */
			kvm_make_request(KVM_REQ_APF_READY, vcpu);
		पूर्ण अन्यथा अणु
			अटल_branch_inc(&apic_hw_disabled.key);
			atomic_set_release(&apic->vcpu->kvm->arch.apic_map_dirty, सूचीTY);
		पूर्ण
	पूर्ण

	अगर (((old_value ^ value) & X2APIC_ENABLE) && (value & X2APIC_ENABLE))
		kvm_apic_set_x2apic_id(apic, vcpu->vcpu_id);

	अगर ((old_value ^ value) & (MSR_IA32_APICBASE_ENABLE | X2APIC_ENABLE))
		अटल_call(kvm_x86_set_भव_apic_mode)(vcpu);

	apic->base_address = apic->vcpu->arch.apic_base &
			     MSR_IA32_APICBASE_BASE;

	अगर ((value & MSR_IA32_APICBASE_ENABLE) &&
	     apic->base_address != APIC_DEFAULT_PHYS_BASE)
		pr_warn_once("APIC base relocation is unsupported by KVM");
पूर्ण

व्योम kvm_apic_update_apicv(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	अगर (vcpu->arch.apicv_active) अणु
		/* irr_pending is always true when apicv is activated. */
		apic->irr_pending = true;
		apic->isr_count = 1;
	पूर्ण अन्यथा अणु
		apic->irr_pending = (apic_search_irr(apic) != -1);
		apic->isr_count = count_vectors(apic->regs + APIC_ISR);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kvm_apic_update_apicv);

व्योम kvm_lapic_reset(काष्ठा kvm_vcpu *vcpu, bool init_event)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	पूर्णांक i;

	अगर (!apic)
		वापस;

	/* Stop the समयr in हाल it's a reset to an active apic */
	hrसमयr_cancel(&apic->lapic_समयr.समयr);

	अगर (!init_event) अणु
		kvm_lapic_set_base(vcpu, APIC_DEFAULT_PHYS_BASE |
		                         MSR_IA32_APICBASE_ENABLE);
		kvm_apic_set_xapic_id(apic, vcpu->vcpu_id);
	पूर्ण
	kvm_apic_set_version(apic->vcpu);

	क्रम (i = 0; i < KVM_APIC_LVT_NUM; i++)
		kvm_lapic_set_reg(apic, APIC_LVTT + 0x10 * i, APIC_LVT_MASKED);
	apic_update_lvtt(apic);
	अगर (kvm_vcpu_is_reset_bsp(vcpu) &&
	    kvm_check_has_quirk(vcpu->kvm, KVM_X86_QUIRK_LINT0_REENABLED))
		kvm_lapic_set_reg(apic, APIC_LVT0,
			     SET_APIC_DELIVERY_MODE(0, APIC_MODE_EXTINT));
	apic_manage_nmi_watchकरोg(apic, kvm_lapic_get_reg(apic, APIC_LVT0));

	kvm_apic_set_dfr(apic, 0xffffffffU);
	apic_set_spiv(apic, 0xff);
	kvm_lapic_set_reg(apic, APIC_TASKPRI, 0);
	अगर (!apic_x2apic_mode(apic))
		kvm_apic_set_ldr(apic, 0);
	kvm_lapic_set_reg(apic, APIC_ESR, 0);
	kvm_lapic_set_reg(apic, APIC_ICR, 0);
	kvm_lapic_set_reg(apic, APIC_ICR2, 0);
	kvm_lapic_set_reg(apic, APIC_TDCR, 0);
	kvm_lapic_set_reg(apic, APIC_TMICT, 0);
	क्रम (i = 0; i < 8; i++) अणु
		kvm_lapic_set_reg(apic, APIC_IRR + 0x10 * i, 0);
		kvm_lapic_set_reg(apic, APIC_ISR + 0x10 * i, 0);
		kvm_lapic_set_reg(apic, APIC_TMR + 0x10 * i, 0);
	पूर्ण
	kvm_apic_update_apicv(vcpu);
	apic->highest_isr_cache = -1;
	update_भागide_count(apic);
	atomic_set(&apic->lapic_समयr.pending, 0);
	अगर (kvm_vcpu_is_bsp(vcpu))
		kvm_lapic_set_base(vcpu,
				vcpu->arch.apic_base | MSR_IA32_APICBASE_BSP);
	vcpu->arch.pv_eoi.msr_val = 0;
	apic_update_ppr(apic);
	अगर (vcpu->arch.apicv_active) अणु
		अटल_call(kvm_x86_apicv_post_state_restore)(vcpu);
		अटल_call(kvm_x86_hwapic_irr_update)(vcpu, -1);
		अटल_call(kvm_x86_hwapic_isr_update)(vcpu, -1);
	पूर्ण

	vcpu->arch.apic_arb_prio = 0;
	vcpu->arch.apic_attention = 0;

	kvm_recalculate_apic_map(vcpu->kvm);
पूर्ण

/*
 *----------------------------------------------------------------------
 * समयr पूर्णांकerface
 *----------------------------------------------------------------------
 */

अटल bool lapic_is_periodic(काष्ठा kvm_lapic *apic)
अणु
	वापस apic_lvtt_period(apic);
पूर्ण

पूर्णांक apic_has_pending_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	अगर (apic_enabled(apic) && apic_lvt_enabled(apic, APIC_LVTT))
		वापस atomic_पढ़ो(&apic->lapic_समयr.pending);

	वापस 0;
पूर्ण

पूर्णांक kvm_apic_local_deliver(काष्ठा kvm_lapic *apic, पूर्णांक lvt_type)
अणु
	u32 reg = kvm_lapic_get_reg(apic, lvt_type);
	पूर्णांक vector, mode, trig_mode;

	अगर (kvm_apic_hw_enabled(apic) && !(reg & APIC_LVT_MASKED)) अणु
		vector = reg & APIC_VECTOR_MASK;
		mode = reg & APIC_MODE_MASK;
		trig_mode = reg & APIC_LVT_LEVEL_TRIGGER;
		वापस __apic_accept_irq(apic, mode, vector, 1, trig_mode,
					शून्य);
	पूर्ण
	वापस 0;
पूर्ण

व्योम kvm_apic_nmi_wd_deliver(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	अगर (apic)
		kvm_apic_local_deliver(apic, APIC_LVT0);
पूर्ण

अटल स्थिर काष्ठा kvm_io_device_ops apic_mmio_ops = अणु
	.पढ़ो     = apic_mmio_पढ़ो,
	.ग_लिखो    = apic_mmio_ग_लिखो,
पूर्ण;

अटल क्रमागत hrसमयr_restart apic_समयr_fn(काष्ठा hrसमयr *data)
अणु
	काष्ठा kvm_समयr *kसमयr = container_of(data, काष्ठा kvm_समयr, समयr);
	काष्ठा kvm_lapic *apic = container_of(kसमयr, काष्ठा kvm_lapic, lapic_समयr);

	apic_समयr_expired(apic, true);

	अगर (lapic_is_periodic(apic)) अणु
		advance_periodic_target_expiration(apic);
		hrसमयr_add_expires_ns(&kसमयr->समयr, kसमयr->period);
		वापस HRTIMER_RESTART;
	पूर्ण अन्यथा
		वापस HRTIMER_NORESTART;
पूर्ण

पूर्णांक kvm_create_lapic(काष्ठा kvm_vcpu *vcpu, पूर्णांक समयr_advance_ns)
अणु
	काष्ठा kvm_lapic *apic;

	ASSERT(vcpu != शून्य);

	apic = kzalloc(माप(*apic), GFP_KERNEL_ACCOUNT);
	अगर (!apic)
		जाओ nomem;

	vcpu->arch.apic = apic;

	apic->regs = (व्योम *)get_zeroed_page(GFP_KERNEL_ACCOUNT);
	अगर (!apic->regs) अणु
		prपूर्णांकk(KERN_ERR "malloc apic regs error for vcpu %x\n",
		       vcpu->vcpu_id);
		जाओ nomem_मुक्त_apic;
	पूर्ण
	apic->vcpu = vcpu;

	hrसमयr_init(&apic->lapic_समयr.समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_ABS_HARD);
	apic->lapic_समयr.समयr.function = apic_समयr_fn;
	अगर (समयr_advance_ns == -1) अणु
		apic->lapic_समयr.समयr_advance_ns = LAPIC_TIMER_ADVANCE_NS_INIT;
		lapic_समयr_advance_dynamic = true;
	पूर्ण अन्यथा अणु
		apic->lapic_समयr.समयr_advance_ns = समयr_advance_ns;
		lapic_समयr_advance_dynamic = false;
	पूर्ण

	/*
	 * APIC is created enabled. This will prevent kvm_lapic_set_base from
	 * thinking that APIC state has changed.
	 */
	vcpu->arch.apic_base = MSR_IA32_APICBASE_ENABLE;
	अटल_branch_inc(&apic_sw_disabled.key); /* sw disabled at reset */
	kvm_iodevice_init(&apic->dev, &apic_mmio_ops);

	वापस 0;
nomem_मुक्त_apic:
	kमुक्त(apic);
	vcpu->arch.apic = शून्य;
nomem:
	वापस -ENOMEM;
पूर्ण

पूर्णांक kvm_apic_has_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	u32 ppr;

	अगर (!kvm_apic_present(vcpu))
		वापस -1;

	__apic_update_ppr(apic, &ppr);
	वापस apic_has_पूर्णांकerrupt_क्रम_ppr(apic, ppr);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_apic_has_पूर्णांकerrupt);

पूर्णांक kvm_apic_accept_pic_पूर्णांकr(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 lvt0 = kvm_lapic_get_reg(vcpu->arch.apic, APIC_LVT0);

	अगर (!kvm_apic_hw_enabled(vcpu->arch.apic))
		वापस 1;
	अगर ((lvt0 & APIC_LVT_MASKED) == 0 &&
	    GET_APIC_DELIVERY_MODE(lvt0) == APIC_MODE_EXTINT)
		वापस 1;
	वापस 0;
पूर्ण

व्योम kvm_inject_apic_समयr_irqs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	अगर (atomic_पढ़ो(&apic->lapic_समयr.pending) > 0) अणु
		kvm_apic_inject_pending_समयr_irqs(apic);
		atomic_set(&apic->lapic_समयr.pending, 0);
	पूर्ण
पूर्ण

पूर्णांक kvm_get_apic_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक vector = kvm_apic_has_पूर्णांकerrupt(vcpu);
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	u32 ppr;

	अगर (vector == -1)
		वापस -1;

	/*
	 * We get here even with APIC भवization enabled, अगर करोing
	 * nested भवization and L1 runs with the "acknowledge पूर्णांकerrupt
	 * on निकास" mode.  Then we cannot inject the पूर्णांकerrupt via RVI,
	 * because the process would deliver it through the IDT.
	 */

	apic_clear_irr(vector, apic);
	अगर (to_hv_vcpu(vcpu) && test_bit(vector, to_hv_synic(vcpu)->स्वतः_eoi_biपंचांगap)) अणु
		/*
		 * For स्वतः-EOI पूर्णांकerrupts, there might be another pending
		 * पूर्णांकerrupt above PPR, so check whether to उठाओ another
		 * KVM_REQ_EVENT.
		 */
		apic_update_ppr(apic);
	पूर्ण अन्यथा अणु
		/*
		 * For normal पूर्णांकerrupts, PPR has been उठाओd and there cannot
		 * be a higher-priority pending पूर्णांकerrupt---except अगर there was
		 * a concurrent पूर्णांकerrupt injection, but that would have
		 * triggered KVM_REQ_EVENT alपढ़ोy.
		 */
		apic_set_isr(vector, apic);
		__apic_update_ppr(apic, &ppr);
	पूर्ण

	वापस vector;
पूर्ण

अटल पूर्णांक kvm_apic_state_fixup(काष्ठा kvm_vcpu *vcpu,
		काष्ठा kvm_lapic_state *s, bool set)
अणु
	अगर (apic_x2apic_mode(vcpu->arch.apic)) अणु
		u32 *id = (u32 *)(s->regs + APIC_ID);
		u32 *ldr = (u32 *)(s->regs + APIC_LDR);

		अगर (vcpu->kvm->arch.x2apic_क्रमmat) अणु
			अगर (*id != vcpu->vcpu_id)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (set)
				*id >>= 24;
			अन्यथा
				*id <<= 24;
		पूर्ण

		/* In x2APIC mode, the LDR is fixed and based on the id */
		अगर (set)
			*ldr = kvm_apic_calc_x2apic_ldr(*id);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक kvm_apic_get_state(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_lapic_state *s)
अणु
	स_नकल(s->regs, vcpu->arch.apic->regs, माप(*s));

	/*
	 * Get calculated समयr current count क्रम reमुख्यing समयr period (अगर
	 * any) and store it in the वापसed रेजिस्टर set.
	 */
	__kvm_lapic_set_reg(s->regs, APIC_TMCCT,
			    __apic_पढ़ो(vcpu->arch.apic, APIC_TMCCT));

	वापस kvm_apic_state_fixup(vcpu, s, false);
पूर्ण

पूर्णांक kvm_apic_set_state(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_lapic_state *s)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	पूर्णांक r;

	kvm_lapic_set_base(vcpu, vcpu->arch.apic_base);
	/* set SPIV separately to get count of SW disabled APICs right */
	apic_set_spiv(apic, *((u32 *)(s->regs + APIC_SPIV)));

	r = kvm_apic_state_fixup(vcpu, s, true);
	अगर (r) अणु
		kvm_recalculate_apic_map(vcpu->kvm);
		वापस r;
	पूर्ण
	स_नकल(vcpu->arch.apic->regs, s->regs, माप(*s));

	atomic_set_release(&apic->vcpu->kvm->arch.apic_map_dirty, सूचीTY);
	kvm_recalculate_apic_map(vcpu->kvm);
	kvm_apic_set_version(vcpu);

	apic_update_ppr(apic);
	hrसमयr_cancel(&apic->lapic_समयr.समयr);
	apic->lapic_समयr.expired_tscdeadline = 0;
	apic_update_lvtt(apic);
	apic_manage_nmi_watchकरोg(apic, kvm_lapic_get_reg(apic, APIC_LVT0));
	update_भागide_count(apic);
	__start_apic_समयr(apic, APIC_TMCCT);
	kvm_apic_update_apicv(vcpu);
	apic->highest_isr_cache = -1;
	अगर (vcpu->arch.apicv_active) अणु
		अटल_call(kvm_x86_apicv_post_state_restore)(vcpu);
		अटल_call(kvm_x86_hwapic_irr_update)(vcpu,
				apic_find_highest_irr(apic));
		अटल_call(kvm_x86_hwapic_isr_update)(vcpu,
				apic_find_highest_isr(apic));
	पूर्ण
	kvm_make_request(KVM_REQ_EVENT, vcpu);
	अगर (ioapic_in_kernel(vcpu->kvm))
		kvm_rtc_eoi_tracking_restore_one(vcpu);

	vcpu->arch.apic_arb_prio = 0;

	वापस 0;
पूर्ण

व्योम __kvm_migrate_apic_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा hrसमयr *समयr;

	अगर (!lapic_in_kernel(vcpu) ||
		kvm_can_post_समयr_पूर्णांकerrupt(vcpu))
		वापस;

	समयr = &vcpu->arch.apic->lapic_समयr.समयr;
	अगर (hrसमयr_cancel(समयr))
		hrसमयr_start_expires(समयr, HRTIMER_MODE_ABS_HARD);
पूर्ण

/*
 * apic_sync_pv_eoi_from_guest - called on vmनिकास or cancel पूर्णांकerrupt
 *
 * Detect whether guest triggered PV EOI since the
 * last entry. If yes, set EOI on guests's behalf.
 * Clear PV EOI in guest memory in any हाल.
 */
अटल व्योम apic_sync_pv_eoi_from_guest(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_lapic *apic)
अणु
	bool pending;
	पूर्णांक vector;
	/*
	 * PV EOI state is derived from KVM_APIC_PV_EOI_PENDING in host
	 * and KVM_PV_EOI_ENABLED in guest memory as follows:
	 *
	 * KVM_APIC_PV_EOI_PENDING is unset:
	 * 	-> host disabled PV EOI.
	 * KVM_APIC_PV_EOI_PENDING is set, KVM_PV_EOI_ENABLED is set:
	 * 	-> host enabled PV EOI, guest did not execute EOI yet.
	 * KVM_APIC_PV_EOI_PENDING is set, KVM_PV_EOI_ENABLED is unset:
	 * 	-> host enabled PV EOI, guest executed EOI.
	 */
	BUG_ON(!pv_eoi_enabled(vcpu));
	pending = pv_eoi_get_pending(vcpu);
	/*
	 * Clear pending bit in any हाल: it will be set again on vmentry.
	 * While this might not be ideal from perक्रमmance poपूर्णांक of view,
	 * this makes sure pv eoi is only enabled when we know it's safe.
	 */
	pv_eoi_clr_pending(vcpu);
	अगर (pending)
		वापस;
	vector = apic_set_eoi(apic);
	trace_kvm_pv_eoi(apic, vector);
पूर्ण

व्योम kvm_lapic_sync_from_vapic(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 data;

	अगर (test_bit(KVM_APIC_PV_EOI_PENDING, &vcpu->arch.apic_attention))
		apic_sync_pv_eoi_from_guest(vcpu, vcpu->arch.apic);

	अगर (!test_bit(KVM_APIC_CHECK_VAPIC, &vcpu->arch.apic_attention))
		वापस;

	अगर (kvm_पढ़ो_guest_cached(vcpu->kvm, &vcpu->arch.apic->vapic_cache, &data,
				  माप(u32)))
		वापस;

	apic_set_tpr(vcpu->arch.apic, data & 0xff);
पूर्ण

/*
 * apic_sync_pv_eoi_to_guest - called beक्रमe vmentry
 *
 * Detect whether it's safe to enable PV EOI and
 * अगर yes करो so.
 */
अटल व्योम apic_sync_pv_eoi_to_guest(काष्ठा kvm_vcpu *vcpu,
					काष्ठा kvm_lapic *apic)
अणु
	अगर (!pv_eoi_enabled(vcpu) ||
	    /* IRR set or many bits in ISR: could be nested. */
	    apic->irr_pending ||
	    /* Cache not set: could be safe but we करोn't bother. */
	    apic->highest_isr_cache == -1 ||
	    /* Need EOI to update ioapic. */
	    kvm_ioapic_handles_vector(apic, apic->highest_isr_cache)) अणु
		/*
		 * PV EOI was disabled by apic_sync_pv_eoi_from_guest
		 * so we need not करो anything here.
		 */
		वापस;
	पूर्ण

	pv_eoi_set_pending(apic->vcpu);
पूर्ण

व्योम kvm_lapic_sync_to_vapic(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 data, tpr;
	पूर्णांक max_irr, max_isr;
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	apic_sync_pv_eoi_to_guest(vcpu, apic);

	अगर (!test_bit(KVM_APIC_CHECK_VAPIC, &vcpu->arch.apic_attention))
		वापस;

	tpr = kvm_lapic_get_reg(apic, APIC_TASKPRI) & 0xff;
	max_irr = apic_find_highest_irr(apic);
	अगर (max_irr < 0)
		max_irr = 0;
	max_isr = apic_find_highest_isr(apic);
	अगर (max_isr < 0)
		max_isr = 0;
	data = (tpr & 0xff) | ((max_isr & 0xf0) << 8) | (max_irr << 24);

	kvm_ग_लिखो_guest_cached(vcpu->kvm, &vcpu->arch.apic->vapic_cache, &data,
				माप(u32));
पूर्ण

पूर्णांक kvm_lapic_set_vapic_addr(काष्ठा kvm_vcpu *vcpu, gpa_t vapic_addr)
अणु
	अगर (vapic_addr) अणु
		अगर (kvm_gfn_to_hva_cache_init(vcpu->kvm,
					&vcpu->arch.apic->vapic_cache,
					vapic_addr, माप(u32)))
			वापस -EINVAL;
		__set_bit(KVM_APIC_CHECK_VAPIC, &vcpu->arch.apic_attention);
	पूर्ण अन्यथा अणु
		__clear_bit(KVM_APIC_CHECK_VAPIC, &vcpu->arch.apic_attention);
	पूर्ण

	vcpu->arch.apic->vapic_addr = vapic_addr;
	वापस 0;
पूर्ण

पूर्णांक kvm_x2apic_msr_ग_लिखो(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 data)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	u32 reg = (msr - APIC_BASE_MSR) << 4;

	अगर (!lapic_in_kernel(vcpu) || !apic_x2apic_mode(apic))
		वापस 1;

	अगर (reg == APIC_ICR2)
		वापस 1;

	/* अगर this is ICR ग_लिखो vector beक्रमe command */
	अगर (reg == APIC_ICR)
		kvm_lapic_reg_ग_लिखो(apic, APIC_ICR2, (u32)(data >> 32));
	वापस kvm_lapic_reg_ग_लिखो(apic, reg, (u32)data);
पूर्ण

पूर्णांक kvm_x2apic_msr_पढ़ो(काष्ठा kvm_vcpu *vcpu, u32 msr, u64 *data)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	u32 reg = (msr - APIC_BASE_MSR) << 4, low, high = 0;

	अगर (!lapic_in_kernel(vcpu) || !apic_x2apic_mode(apic))
		वापस 1;

	अगर (reg == APIC_DFR || reg == APIC_ICR2)
		वापस 1;

	अगर (kvm_lapic_reg_पढ़ो(apic, reg, 4, &low))
		वापस 1;
	अगर (reg == APIC_ICR)
		kvm_lapic_reg_पढ़ो(apic, APIC_ICR2, 4, &high);

	*data = (((u64)high) << 32) | low;

	वापस 0;
पूर्ण

पूर्णांक kvm_hv_vapic_msr_ग_लिखो(काष्ठा kvm_vcpu *vcpu, u32 reg, u64 data)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	अगर (!lapic_in_kernel(vcpu))
		वापस 1;

	/* अगर this is ICR ग_लिखो vector beक्रमe command */
	अगर (reg == APIC_ICR)
		kvm_lapic_reg_ग_लिखो(apic, APIC_ICR2, (u32)(data >> 32));
	वापस kvm_lapic_reg_ग_लिखो(apic, reg, (u32)data);
पूर्ण

पूर्णांक kvm_hv_vapic_msr_पढ़ो(काष्ठा kvm_vcpu *vcpu, u32 reg, u64 *data)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	u32 low, high = 0;

	अगर (!lapic_in_kernel(vcpu))
		वापस 1;

	अगर (kvm_lapic_reg_पढ़ो(apic, reg, 4, &low))
		वापस 1;
	अगर (reg == APIC_ICR)
		kvm_lapic_reg_पढ़ो(apic, APIC_ICR2, 4, &high);

	*data = (((u64)high) << 32) | low;

	वापस 0;
पूर्ण

पूर्णांक kvm_lapic_enable_pv_eoi(काष्ठा kvm_vcpu *vcpu, u64 data, अचिन्हित दीर्घ len)
अणु
	u64 addr = data & ~KVM_MSR_ENABLED;
	काष्ठा gfn_to_hva_cache *ghc = &vcpu->arch.pv_eoi.data;
	अचिन्हित दीर्घ new_len;

	अगर (!IS_ALIGNED(addr, 4))
		वापस 1;

	vcpu->arch.pv_eoi.msr_val = data;
	अगर (!pv_eoi_enabled(vcpu))
		वापस 0;

	अगर (addr == ghc->gpa && len <= ghc->len)
		new_len = ghc->len;
	अन्यथा
		new_len = len;

	वापस kvm_gfn_to_hva_cache_init(vcpu->kvm, ghc, addr, new_len);
पूर्ण

व्योम kvm_apic_accept_events(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	u8 sipi_vector;
	पूर्णांक r;
	अचिन्हित दीर्घ pe;

	अगर (!lapic_in_kernel(vcpu))
		वापस;

	/*
	 * Read pending events beक्रमe calling the check_events
	 * callback.
	 */
	pe = smp_load_acquire(&apic->pending_events);
	अगर (!pe)
		वापस;

	अगर (is_guest_mode(vcpu)) अणु
		r = kvm_check_nested_events(vcpu);
		अगर (r < 0)
			वापस;
		/*
		 * If an event has happened and caused a vmनिकास,
		 * we know INITs are latched and thereक्रमe
		 * we will not incorrectly deliver an APIC
		 * event instead of a vmनिकास.
		 */
	पूर्ण

	/*
	 * INITs are latched जबतक CPU is in specअगरic states
	 * (SMM, VMX root mode, SVM with GIF=0).
	 * Because a CPU cannot be in these states immediately
	 * after it has processed an INIT संकेत (and thus in
	 * KVM_MP_STATE_INIT_RECEIVED state), just eat SIPIs
	 * and leave the INIT pending.
	 */
	अगर (kvm_vcpu_latch_init(vcpu)) अणु
		WARN_ON_ONCE(vcpu->arch.mp_state == KVM_MP_STATE_INIT_RECEIVED);
		अगर (test_bit(KVM_APIC_SIPI, &pe))
			clear_bit(KVM_APIC_SIPI, &apic->pending_events);
		वापस;
	पूर्ण

	अगर (test_bit(KVM_APIC_INIT, &pe)) अणु
		clear_bit(KVM_APIC_INIT, &apic->pending_events);
		kvm_vcpu_reset(vcpu, true);
		अगर (kvm_vcpu_is_bsp(apic->vcpu))
			vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;
		अन्यथा
			vcpu->arch.mp_state = KVM_MP_STATE_INIT_RECEIVED;
	पूर्ण
	अगर (test_bit(KVM_APIC_SIPI, &pe)) अणु
		clear_bit(KVM_APIC_SIPI, &apic->pending_events);
		अगर (vcpu->arch.mp_state == KVM_MP_STATE_INIT_RECEIVED) अणु
			/* evaluate pending_events beक्रमe पढ़ोing the vector */
			smp_rmb();
			sipi_vector = apic->sipi_vector;
			kvm_x86_ops.vcpu_deliver_sipi_vector(vcpu, sipi_vector);
			vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;
		पूर्ण
	पूर्ण
पूर्ण

व्योम kvm_lapic_निकास(व्योम)
अणु
	अटल_key_deferred_flush(&apic_hw_disabled);
	अटल_key_deferred_flush(&apic_sw_disabled);
पूर्ण
