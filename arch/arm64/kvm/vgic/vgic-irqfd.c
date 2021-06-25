<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015, 2016 ARM Ltd.
 */

#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <trace/events/kvm.h>
#समावेश <kvm/arm_vgic.h>
#समावेश "vgic.h"

/**
 * vgic_irqfd_set_irq: inject the IRQ corresponding to the
 * irqchip routing entry
 *
 * This is the entry poपूर्णांक क्रम irqfd IRQ injection
 */
अटल पूर्णांक vgic_irqfd_set_irq(काष्ठा kvm_kernel_irq_routing_entry *e,
			काष्ठा kvm *kvm, पूर्णांक irq_source_id,
			पूर्णांक level, bool line_status)
अणु
	अचिन्हित पूर्णांक spi_id = e->irqchip.pin + VGIC_NR_PRIVATE_IRQS;

	अगर (!vgic_valid_spi(kvm, spi_id))
		वापस -EINVAL;
	वापस kvm_vgic_inject_irq(kvm, 0, spi_id, level, शून्य);
पूर्ण

/**
 * kvm_set_routing_entry: populate a kvm routing entry
 * from a user routing entry
 *
 * @kvm: the VM this entry is applied to
 * @e: kvm kernel routing entry handle
 * @ue: user api routing entry handle
 * वापस 0 on success, -EINVAL on errors.
 */
पूर्णांक kvm_set_routing_entry(काष्ठा kvm *kvm,
			  काष्ठा kvm_kernel_irq_routing_entry *e,
			  स्थिर काष्ठा kvm_irq_routing_entry *ue)
अणु
	पूर्णांक r = -EINVAL;

	चयन (ue->type) अणु
	हाल KVM_IRQ_ROUTING_IRQCHIP:
		e->set = vgic_irqfd_set_irq;
		e->irqchip.irqchip = ue->u.irqchip.irqchip;
		e->irqchip.pin = ue->u.irqchip.pin;
		अगर ((e->irqchip.pin >= KVM_IRQCHIP_NUM_PINS) ||
		    (e->irqchip.irqchip >= KVM_NR_IRQCHIPS))
			जाओ out;
		अवरोध;
	हाल KVM_IRQ_ROUTING_MSI:
		e->set = kvm_set_msi;
		e->msi.address_lo = ue->u.msi.address_lo;
		e->msi.address_hi = ue->u.msi.address_hi;
		e->msi.data = ue->u.msi.data;
		e->msi.flags = ue->flags;
		e->msi.devid = ue->u.msi.devid;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण
	r = 0;
out:
	वापस r;
पूर्ण

अटल व्योम kvm_populate_msi(काष्ठा kvm_kernel_irq_routing_entry *e,
			     काष्ठा kvm_msi *msi)
अणु
	msi->address_lo = e->msi.address_lo;
	msi->address_hi = e->msi.address_hi;
	msi->data = e->msi.data;
	msi->flags = e->msi.flags;
	msi->devid = e->msi.devid;
पूर्ण
/**
 * kvm_set_msi: inject the MSI corresponding to the
 * MSI routing entry
 *
 * This is the entry poपूर्णांक क्रम irqfd MSI injection
 * and userspace MSI injection.
 */
पूर्णांक kvm_set_msi(काष्ठा kvm_kernel_irq_routing_entry *e,
		काष्ठा kvm *kvm, पूर्णांक irq_source_id,
		पूर्णांक level, bool line_status)
अणु
	काष्ठा kvm_msi msi;

	अगर (!vgic_has_its(kvm))
		वापस -ENODEV;

	अगर (!level)
		वापस -1;

	kvm_populate_msi(e, &msi);
	वापस vgic_its_inject_msi(kvm, &msi);
पूर्ण

/**
 * kvm_arch_set_irq_inatomic: fast-path क्रम irqfd injection
 */
पूर्णांक kvm_arch_set_irq_inatomic(काष्ठा kvm_kernel_irq_routing_entry *e,
			      काष्ठा kvm *kvm, पूर्णांक irq_source_id, पूर्णांक level,
			      bool line_status)
अणु
	अगर (!level)
		वापस -EWOULDBLOCK;

	चयन (e->type) अणु
	हाल KVM_IRQ_ROUTING_MSI: अणु
		काष्ठा kvm_msi msi;

		अगर (!vgic_has_its(kvm))
			अवरोध;

		kvm_populate_msi(e, &msi);
		वापस vgic_its_inject_cached_translation(kvm, &msi);
	पूर्ण

	हाल KVM_IRQ_ROUTING_IRQCHIP:
		/*
		 * Injecting SPIs is always possible in atomic context
		 * as दीर्घ as the damn vgic is initialized.
		 */
		अगर (unlikely(!vgic_initialized(kvm)))
			अवरोध;
		वापस vgic_irqfd_set_irq(e, kvm, irq_source_id, 1, line_status);
	पूर्ण

	वापस -EWOULDBLOCK;
पूर्ण

पूर्णांक kvm_vgic_setup_शेष_irq_routing(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_irq_routing_entry *entries;
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	u32 nr = dist->nr_spis;
	पूर्णांक i, ret;

	entries = kसुस्मृति(nr, माप(*entries), GFP_KERNEL);
	अगर (!entries)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr; i++) अणु
		entries[i].gsi = i;
		entries[i].type = KVM_IRQ_ROUTING_IRQCHIP;
		entries[i].u.irqchip.irqchip = 0;
		entries[i].u.irqchip.pin = i;
	पूर्ण
	ret = kvm_set_irq_routing(kvm, entries, nr, 0);
	kमुक्त(entries);
	वापस ret;
पूर्ण
