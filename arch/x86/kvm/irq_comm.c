<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * irq_comm.c: Common API क्रम in kernel पूर्णांकerrupt controller
 * Copyright (c) 2007, Intel Corporation.
 *
 * Authors:
 *   Yaozu (Eddie) Dong <Eddie.करोng@पूर्णांकel.com>
 *
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/rculist.h>

#समावेश <trace/events/kvm.h>

#समावेश "irq.h"

#समावेश "ioapic.h"

#समावेश "lapic.h"

#समावेश "hyperv.h"
#समावेश "x86.h"

अटल पूर्णांक kvm_set_pic_irq(काष्ठा kvm_kernel_irq_routing_entry *e,
			   काष्ठा kvm *kvm, पूर्णांक irq_source_id, पूर्णांक level,
			   bool line_status)
अणु
	काष्ठा kvm_pic *pic = kvm->arch.vpic;
	वापस kvm_pic_set_irq(pic, e->irqchip.pin, irq_source_id, level);
पूर्ण

अटल पूर्णांक kvm_set_ioapic_irq(काष्ठा kvm_kernel_irq_routing_entry *e,
			      काष्ठा kvm *kvm, पूर्णांक irq_source_id, पूर्णांक level,
			      bool line_status)
अणु
	काष्ठा kvm_ioapic *ioapic = kvm->arch.vioapic;
	वापस kvm_ioapic_set_irq(ioapic, e->irqchip.pin, irq_source_id, level,
				line_status);
पूर्ण

पूर्णांक kvm_irq_delivery_to_apic(काष्ठा kvm *kvm, काष्ठा kvm_lapic *src,
		काष्ठा kvm_lapic_irq *irq, काष्ठा dest_map *dest_map)
अणु
	पूर्णांक i, r = -1;
	काष्ठा kvm_vcpu *vcpu, *lowest = शून्य;
	अचिन्हित दीर्घ dest_vcpu_biपंचांगap[BITS_TO_LONGS(KVM_MAX_VCPUS)];
	अचिन्हित पूर्णांक dest_vcpus = 0;

	अगर (kvm_irq_delivery_to_apic_fast(kvm, src, irq, &r, dest_map))
		वापस r;

	अगर (irq->dest_mode == APIC_DEST_PHYSICAL &&
	    irq->dest_id == 0xff && kvm_lowest_prio_delivery(irq)) अणु
		prपूर्णांकk(KERN_INFO "kvm: apic: phys broadcast and lowest prio\n");
		irq->delivery_mode = APIC_DM_FIXED;
	पूर्ण

	स_रखो(dest_vcpu_biपंचांगap, 0, माप(dest_vcpu_biपंचांगap));

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (!kvm_apic_present(vcpu))
			जारी;

		अगर (!kvm_apic_match_dest(vcpu, src, irq->लघुhand,
					irq->dest_id, irq->dest_mode))
			जारी;

		अगर (!kvm_lowest_prio_delivery(irq)) अणु
			अगर (r < 0)
				r = 0;
			r += kvm_apic_set_irq(vcpu, irq, dest_map);
		पूर्ण अन्यथा अगर (kvm_apic_sw_enabled(vcpu->arch.apic)) अणु
			अगर (!kvm_vector_hashing_enabled()) अणु
				अगर (!lowest)
					lowest = vcpu;
				अन्यथा अगर (kvm_apic_compare_prio(vcpu, lowest) < 0)
					lowest = vcpu;
			पूर्ण अन्यथा अणु
				__set_bit(i, dest_vcpu_biपंचांगap);
				dest_vcpus++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dest_vcpus != 0) अणु
		पूर्णांक idx = kvm_vector_to_index(irq->vector, dest_vcpus,
					dest_vcpu_biपंचांगap, KVM_MAX_VCPUS);

		lowest = kvm_get_vcpu(kvm, idx);
	पूर्ण

	अगर (lowest)
		r = kvm_apic_set_irq(lowest, irq, dest_map);

	वापस r;
पूर्ण

व्योम kvm_set_msi_irq(काष्ठा kvm *kvm, काष्ठा kvm_kernel_irq_routing_entry *e,
		     काष्ठा kvm_lapic_irq *irq)
अणु
	काष्ठा msi_msg msg = अणु .address_lo = e->msi.address_lo,
			       .address_hi = e->msi.address_hi,
			       .data = e->msi.data पूर्ण;

	trace_kvm_msi_set_irq(msg.address_lo | (kvm->arch.x2apic_क्रमmat ?
			      (u64)msg.address_hi << 32 : 0), msg.data);

	irq->dest_id = x86_msi_msg_get_destid(&msg, kvm->arch.x2apic_क्रमmat);
	irq->vector = msg.arch_data.vector;
	irq->dest_mode = kvm_lapic_irq_dest_mode(msg.arch_addr_lo.dest_mode_logical);
	irq->trig_mode = msg.arch_data.is_level;
	irq->delivery_mode = msg.arch_data.delivery_mode << 8;
	irq->msi_redir_hपूर्णांक = msg.arch_addr_lo.redirect_hपूर्णांक;
	irq->level = 1;
	irq->लघुhand = APIC_DEST_NOSHORT;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_msi_irq);

अटल अंतरभूत bool kvm_msi_route_invalid(काष्ठा kvm *kvm,
		काष्ठा kvm_kernel_irq_routing_entry *e)
अणु
	वापस kvm->arch.x2apic_क्रमmat && (e->msi.address_hi & 0xff);
पूर्ण

पूर्णांक kvm_set_msi(काष्ठा kvm_kernel_irq_routing_entry *e,
		काष्ठा kvm *kvm, पूर्णांक irq_source_id, पूर्णांक level, bool line_status)
अणु
	काष्ठा kvm_lapic_irq irq;

	अगर (kvm_msi_route_invalid(kvm, e))
		वापस -EINVAL;

	अगर (!level)
		वापस -1;

	kvm_set_msi_irq(kvm, e, &irq);

	वापस kvm_irq_delivery_to_apic(kvm, शून्य, &irq, शून्य);
पूर्ण


अटल पूर्णांक kvm_hv_set_sपूर्णांक(काष्ठा kvm_kernel_irq_routing_entry *e,
		    काष्ठा kvm *kvm, पूर्णांक irq_source_id, पूर्णांक level,
		    bool line_status)
अणु
	अगर (!level)
		वापस -1;

	वापस kvm_hv_synic_set_irq(kvm, e->hv_sपूर्णांक.vcpu, e->hv_sपूर्णांक.sपूर्णांक);
पूर्ण

पूर्णांक kvm_arch_set_irq_inatomic(काष्ठा kvm_kernel_irq_routing_entry *e,
			      काष्ठा kvm *kvm, पूर्णांक irq_source_id, पूर्णांक level,
			      bool line_status)
अणु
	काष्ठा kvm_lapic_irq irq;
	पूर्णांक r;

	चयन (e->type) अणु
	हाल KVM_IRQ_ROUTING_HV_SINT:
		वापस kvm_hv_set_sपूर्णांक(e, kvm, irq_source_id, level,
				       line_status);

	हाल KVM_IRQ_ROUTING_MSI:
		अगर (kvm_msi_route_invalid(kvm, e))
			वापस -EINVAL;

		kvm_set_msi_irq(kvm, e, &irq);

		अगर (kvm_irq_delivery_to_apic_fast(kvm, शून्य, &irq, &r, शून्य))
			वापस r;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EWOULDBLOCK;
पूर्ण

पूर्णांक kvm_request_irq_source_id(काष्ठा kvm *kvm)
अणु
	अचिन्हित दीर्घ *biपंचांगap = &kvm->arch.irq_sources_biपंचांगap;
	पूर्णांक irq_source_id;

	mutex_lock(&kvm->irq_lock);
	irq_source_id = find_first_zero_bit(biपंचांगap, BITS_PER_LONG);

	अगर (irq_source_id >= BITS_PER_LONG) अणु
		prपूर्णांकk(KERN_WARNING "kvm: exhaust allocatable IRQ sources!\n");
		irq_source_id = -EFAULT;
		जाओ unlock;
	पूर्ण

	ASSERT(irq_source_id != KVM_USERSPACE_IRQ_SOURCE_ID);
	ASSERT(irq_source_id != KVM_IRQFD_RESAMPLE_IRQ_SOURCE_ID);
	set_bit(irq_source_id, biपंचांगap);
unlock:
	mutex_unlock(&kvm->irq_lock);

	वापस irq_source_id;
पूर्ण

व्योम kvm_मुक्त_irq_source_id(काष्ठा kvm *kvm, पूर्णांक irq_source_id)
अणु
	ASSERT(irq_source_id != KVM_USERSPACE_IRQ_SOURCE_ID);
	ASSERT(irq_source_id != KVM_IRQFD_RESAMPLE_IRQ_SOURCE_ID);

	mutex_lock(&kvm->irq_lock);
	अगर (irq_source_id < 0 ||
	    irq_source_id >= BITS_PER_LONG) अणु
		prपूर्णांकk(KERN_ERR "kvm: IRQ source ID out of range!\n");
		जाओ unlock;
	पूर्ण
	clear_bit(irq_source_id, &kvm->arch.irq_sources_biपंचांगap);
	अगर (!irqchip_kernel(kvm))
		जाओ unlock;

	kvm_ioapic_clear_all(kvm->arch.vioapic, irq_source_id);
	kvm_pic_clear_all(kvm->arch.vpic, irq_source_id);
unlock:
	mutex_unlock(&kvm->irq_lock);
पूर्ण

व्योम kvm_रेजिस्टर_irq_mask_notअगरier(काष्ठा kvm *kvm, पूर्णांक irq,
				    काष्ठा kvm_irq_mask_notअगरier *kimn)
अणु
	mutex_lock(&kvm->irq_lock);
	kimn->irq = irq;
	hlist_add_head_rcu(&kimn->link, &kvm->arch.mask_notअगरier_list);
	mutex_unlock(&kvm->irq_lock);
पूर्ण

व्योम kvm_unरेजिस्टर_irq_mask_notअगरier(काष्ठा kvm *kvm, पूर्णांक irq,
				      काष्ठा kvm_irq_mask_notअगरier *kimn)
अणु
	mutex_lock(&kvm->irq_lock);
	hlist_del_rcu(&kimn->link);
	mutex_unlock(&kvm->irq_lock);
	synchronize_srcu(&kvm->irq_srcu);
पूर्ण

व्योम kvm_fire_mask_notअगरiers(काष्ठा kvm *kvm, अचिन्हित irqchip, अचिन्हित pin,
			     bool mask)
अणु
	काष्ठा kvm_irq_mask_notअगरier *kimn;
	पूर्णांक idx, gsi;

	idx = srcu_पढ़ो_lock(&kvm->irq_srcu);
	gsi = kvm_irq_map_chip_pin(kvm, irqchip, pin);
	अगर (gsi != -1)
		hlist_क्रम_each_entry_rcu(kimn, &kvm->arch.mask_notअगरier_list, link)
			अगर (kimn->irq == gsi)
				kimn->func(kimn, mask);
	srcu_पढ़ो_unlock(&kvm->irq_srcu, idx);
पूर्ण

bool kvm_arch_can_set_irq_routing(काष्ठा kvm *kvm)
अणु
	वापस irqchip_in_kernel(kvm);
पूर्ण

पूर्णांक kvm_set_routing_entry(काष्ठा kvm *kvm,
			  काष्ठा kvm_kernel_irq_routing_entry *e,
			  स्थिर काष्ठा kvm_irq_routing_entry *ue)
अणु
	/* We can't check irqchip_in_kernel() here as some callers are
	 * currently initializing the irqchip. Other callers should thereक्रमe
	 * check kvm_arch_can_set_irq_routing() beक्रमe calling this function.
	 */
	चयन (ue->type) अणु
	हाल KVM_IRQ_ROUTING_IRQCHIP:
		अगर (irqchip_split(kvm))
			वापस -EINVAL;
		e->irqchip.pin = ue->u.irqchip.pin;
		चयन (ue->u.irqchip.irqchip) अणु
		हाल KVM_IRQCHIP_PIC_SLAVE:
			e->irqchip.pin += PIC_NUM_PINS / 2;
			fallthrough;
		हाल KVM_IRQCHIP_PIC_MASTER:
			अगर (ue->u.irqchip.pin >= PIC_NUM_PINS / 2)
				वापस -EINVAL;
			e->set = kvm_set_pic_irq;
			अवरोध;
		हाल KVM_IRQCHIP_IOAPIC:
			अगर (ue->u.irqchip.pin >= KVM_IOAPIC_NUM_PINS)
				वापस -EINVAL;
			e->set = kvm_set_ioapic_irq;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		e->irqchip.irqchip = ue->u.irqchip.irqchip;
		अवरोध;
	हाल KVM_IRQ_ROUTING_MSI:
		e->set = kvm_set_msi;
		e->msi.address_lo = ue->u.msi.address_lo;
		e->msi.address_hi = ue->u.msi.address_hi;
		e->msi.data = ue->u.msi.data;

		अगर (kvm_msi_route_invalid(kvm, e))
			वापस -EINVAL;
		अवरोध;
	हाल KVM_IRQ_ROUTING_HV_SINT:
		e->set = kvm_hv_set_sपूर्णांक;
		e->hv_sपूर्णांक.vcpu = ue->u.hv_sपूर्णांक.vcpu;
		e->hv_sपूर्णांक.sपूर्णांक = ue->u.hv_sपूर्णांक.sपूर्णांक;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

bool kvm_पूर्णांकr_is_single_vcpu(काष्ठा kvm *kvm, काष्ठा kvm_lapic_irq *irq,
			     काष्ठा kvm_vcpu **dest_vcpu)
अणु
	पूर्णांक i, r = 0;
	काष्ठा kvm_vcpu *vcpu;

	अगर (kvm_पूर्णांकr_is_single_vcpu_fast(kvm, irq, dest_vcpu))
		वापस true;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (!kvm_apic_present(vcpu))
			जारी;

		अगर (!kvm_apic_match_dest(vcpu, शून्य, irq->लघुhand,
					irq->dest_id, irq->dest_mode))
			जारी;

		अगर (++r == 2)
			वापस false;

		*dest_vcpu = vcpu;
	पूर्ण

	वापस r == 1;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_पूर्णांकr_is_single_vcpu);

#घोषणा IOAPIC_ROUTING_ENTRY(irq) \
	अणु .gsi = irq, .type = KVM_IRQ_ROUTING_IRQCHIP,	\
	  .u.irqchip = अणु .irqchip = KVM_IRQCHIP_IOAPIC, .pin = (irq) पूर्ण पूर्ण
#घोषणा ROUTING_ENTRY1(irq) IOAPIC_ROUTING_ENTRY(irq)

#घोषणा PIC_ROUTING_ENTRY(irq) \
	अणु .gsi = irq, .type = KVM_IRQ_ROUTING_IRQCHIP,	\
	  .u.irqchip = अणु .irqchip = SELECT_PIC(irq), .pin = (irq) % 8 पूर्ण पूर्ण
#घोषणा ROUTING_ENTRY2(irq) \
	IOAPIC_ROUTING_ENTRY(irq), PIC_ROUTING_ENTRY(irq)

अटल स्थिर काष्ठा kvm_irq_routing_entry शेष_routing[] = अणु
	ROUTING_ENTRY2(0), ROUTING_ENTRY2(1),
	ROUTING_ENTRY2(2), ROUTING_ENTRY2(3),
	ROUTING_ENTRY2(4), ROUTING_ENTRY2(5),
	ROUTING_ENTRY2(6), ROUTING_ENTRY2(7),
	ROUTING_ENTRY2(8), ROUTING_ENTRY2(9),
	ROUTING_ENTRY2(10), ROUTING_ENTRY2(11),
	ROUTING_ENTRY2(12), ROUTING_ENTRY2(13),
	ROUTING_ENTRY2(14), ROUTING_ENTRY2(15),
	ROUTING_ENTRY1(16), ROUTING_ENTRY1(17),
	ROUTING_ENTRY1(18), ROUTING_ENTRY1(19),
	ROUTING_ENTRY1(20), ROUTING_ENTRY1(21),
	ROUTING_ENTRY1(22), ROUTING_ENTRY1(23),
पूर्ण;

पूर्णांक kvm_setup_शेष_irq_routing(काष्ठा kvm *kvm)
अणु
	वापस kvm_set_irq_routing(kvm, शेष_routing,
				   ARRAY_SIZE(शेष_routing), 0);
पूर्ण

अटल स्थिर काष्ठा kvm_irq_routing_entry empty_routing[] = अणुपूर्ण;

पूर्णांक kvm_setup_empty_irq_routing(काष्ठा kvm *kvm)
अणु
	वापस kvm_set_irq_routing(kvm, empty_routing, 0, 0);
पूर्ण

व्योम kvm_arch_post_irq_routing_update(काष्ठा kvm *kvm)
अणु
	अगर (!irqchip_split(kvm))
		वापस;
	kvm_make_scan_ioapic_request(kvm);
पूर्ण

व्योम kvm_scan_ioapic_routes(काष्ठा kvm_vcpu *vcpu,
			    uदीर्घ *ioapic_handled_vectors)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_kernel_irq_routing_entry *entry;
	काष्ठा kvm_irq_routing_table *table;
	u32 i, nr_ioapic_pins;
	पूर्णांक idx;

	idx = srcu_पढ़ो_lock(&kvm->irq_srcu);
	table = srcu_dereference(kvm->irq_routing, &kvm->irq_srcu);
	nr_ioapic_pins = min_t(u32, table->nr_rt_entries,
			       kvm->arch.nr_reserved_ioapic_pins);
	क्रम (i = 0; i < nr_ioapic_pins; ++i) अणु
		hlist_क्रम_each_entry(entry, &table->map[i], link) अणु
			काष्ठा kvm_lapic_irq irq;

			अगर (entry->type != KVM_IRQ_ROUTING_MSI)
				जारी;

			kvm_set_msi_irq(vcpu->kvm, entry, &irq);

			अगर (irq.trig_mode &&
			    kvm_apic_match_dest(vcpu, शून्य, APIC_DEST_NOSHORT,
						irq.dest_id, irq.dest_mode))
				__set_bit(irq.vector, ioapic_handled_vectors);
		पूर्ण
	पूर्ण
	srcu_पढ़ो_unlock(&kvm->irq_srcu, idx);
पूर्ण

व्योम kvm_arch_irq_routing_update(काष्ठा kvm *kvm)
अणु
	kvm_hv_irq_routing_update(kvm);
पूर्ण
