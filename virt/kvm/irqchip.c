<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * irqchip.c: Common API क्रम in kernel पूर्णांकerrupt controllers
 * Copyright (c) 2007, Intel Corporation.
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 * Copyright (c) 2013, Alexander Graf <agraf@suse.de>
 *
 * This file is derived from virt/kvm/irq_comm.c.
 *
 * Authors:
 *   Yaozu (Eddie) Dong <Eddie.करोng@पूर्णांकel.com>
 *   Alexander Graf <agraf@suse.de>
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/slab.h>
#समावेश <linux/srcu.h>
#समावेश <linux/export.h>
#समावेश <trace/events/kvm.h>
#समावेश "irq.h"

पूर्णांक kvm_irq_map_gsi(काष्ठा kvm *kvm,
		    काष्ठा kvm_kernel_irq_routing_entry *entries, पूर्णांक gsi)
अणु
	काष्ठा kvm_irq_routing_table *irq_rt;
	काष्ठा kvm_kernel_irq_routing_entry *e;
	पूर्णांक n = 0;

	irq_rt = srcu_dereference_check(kvm->irq_routing, &kvm->irq_srcu,
					lockdep_is_held(&kvm->irq_lock));
	अगर (irq_rt && gsi < irq_rt->nr_rt_entries) अणु
		hlist_क्रम_each_entry(e, &irq_rt->map[gsi], link) अणु
			entries[n] = *e;
			++n;
		पूर्ण
	पूर्ण

	वापस n;
पूर्ण

पूर्णांक kvm_irq_map_chip_pin(काष्ठा kvm *kvm, अचिन्हित irqchip, अचिन्हित pin)
अणु
	काष्ठा kvm_irq_routing_table *irq_rt;

	irq_rt = srcu_dereference(kvm->irq_routing, &kvm->irq_srcu);
	वापस irq_rt->chip[irqchip][pin];
पूर्ण

पूर्णांक kvm_send_userspace_msi(काष्ठा kvm *kvm, काष्ठा kvm_msi *msi)
अणु
	काष्ठा kvm_kernel_irq_routing_entry route;

	अगर (!irqchip_in_kernel(kvm) || (msi->flags & ~KVM_MSI_VALID_DEVID))
		वापस -EINVAL;

	route.msi.address_lo = msi->address_lo;
	route.msi.address_hi = msi->address_hi;
	route.msi.data = msi->data;
	route.msi.flags = msi->flags;
	route.msi.devid = msi->devid;

	वापस kvm_set_msi(&route, kvm, KVM_USERSPACE_IRQ_SOURCE_ID, 1, false);
पूर्ण

/*
 * Return value:
 *  < 0   Interrupt was ignored (masked or not delivered क्रम other reasons)
 *  = 0   Interrupt was coalesced (previous irq is still pending)
 *  > 0   Number of CPUs पूर्णांकerrupt was delivered to
 */
पूर्णांक kvm_set_irq(काष्ठा kvm *kvm, पूर्णांक irq_source_id, u32 irq, पूर्णांक level,
		bool line_status)
अणु
	काष्ठा kvm_kernel_irq_routing_entry irq_set[KVM_NR_IRQCHIPS];
	पूर्णांक ret = -1, i, idx;

	trace_kvm_set_irq(irq, level, irq_source_id);

	/* Not possible to detect अगर the guest uses the PIC or the
	 * IOAPIC.  So set the bit in both. The guest will ignore
	 * ग_लिखोs to the unused one.
	 */
	idx = srcu_पढ़ो_lock(&kvm->irq_srcu);
	i = kvm_irq_map_gsi(kvm, irq_set, irq);
	srcu_पढ़ो_unlock(&kvm->irq_srcu, idx);

	जबतक (i--) अणु
		पूर्णांक r;
		r = irq_set[i].set(&irq_set[i], kvm, irq_source_id, level,
				   line_status);
		अगर (r < 0)
			जारी;

		ret = r + ((ret < 0) ? 0 : ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम मुक्त_irq_routing_table(काष्ठा kvm_irq_routing_table *rt)
अणु
	पूर्णांक i;

	अगर (!rt)
		वापस;

	क्रम (i = 0; i < rt->nr_rt_entries; ++i) अणु
		काष्ठा kvm_kernel_irq_routing_entry *e;
		काष्ठा hlist_node *n;

		hlist_क्रम_each_entry_safe(e, n, &rt->map[i], link) अणु
			hlist_del(&e->link);
			kमुक्त(e);
		पूर्ण
	पूर्ण

	kमुक्त(rt);
पूर्ण

व्योम kvm_मुक्त_irq_routing(काष्ठा kvm *kvm)
अणु
	/* Called only during vm deकाष्ठाion. Nobody can use the poपूर्णांकer
	   at this stage */
	काष्ठा kvm_irq_routing_table *rt = rcu_access_poपूर्णांकer(kvm->irq_routing);
	मुक्त_irq_routing_table(rt);
पूर्ण

अटल पूर्णांक setup_routing_entry(काष्ठा kvm *kvm,
			       काष्ठा kvm_irq_routing_table *rt,
			       काष्ठा kvm_kernel_irq_routing_entry *e,
			       स्थिर काष्ठा kvm_irq_routing_entry *ue)
अणु
	काष्ठा kvm_kernel_irq_routing_entry *ei;
	पूर्णांक r;
	u32 gsi = array_index_nospec(ue->gsi, KVM_MAX_IRQ_ROUTES);

	/*
	 * Do not allow GSI to be mapped to the same irqchip more than once.
	 * Allow only one to one mapping between GSI and non-irqchip routing.
	 */
	hlist_क्रम_each_entry(ei, &rt->map[gsi], link)
		अगर (ei->type != KVM_IRQ_ROUTING_IRQCHIP ||
		    ue->type != KVM_IRQ_ROUTING_IRQCHIP ||
		    ue->u.irqchip.irqchip == ei->irqchip.irqchip)
			वापस -EINVAL;

	e->gsi = gsi;
	e->type = ue->type;
	r = kvm_set_routing_entry(kvm, e, ue);
	अगर (r)
		वापस r;
	अगर (e->type == KVM_IRQ_ROUTING_IRQCHIP)
		rt->chip[e->irqchip.irqchip][e->irqchip.pin] = e->gsi;

	hlist_add_head(&e->link, &rt->map[e->gsi]);

	वापस 0;
पूर्ण

व्योम __attribute__((weak)) kvm_arch_irq_routing_update(काष्ठा kvm *kvm)
अणु
पूर्ण

bool __weak kvm_arch_can_set_irq_routing(काष्ठा kvm *kvm)
अणु
	वापस true;
पूर्ण

पूर्णांक kvm_set_irq_routing(काष्ठा kvm *kvm,
			स्थिर काष्ठा kvm_irq_routing_entry *ue,
			अचिन्हित nr,
			अचिन्हित flags)
अणु
	काष्ठा kvm_irq_routing_table *new, *old;
	काष्ठा kvm_kernel_irq_routing_entry *e;
	u32 i, j, nr_rt_entries = 0;
	पूर्णांक r;

	क्रम (i = 0; i < nr; ++i) अणु
		अगर (ue[i].gsi >= KVM_MAX_IRQ_ROUTES)
			वापस -EINVAL;
		nr_rt_entries = max(nr_rt_entries, ue[i].gsi);
	पूर्ण

	nr_rt_entries += 1;

	new = kzalloc(काष्ठा_size(new, map, nr_rt_entries), GFP_KERNEL_ACCOUNT);
	अगर (!new)
		वापस -ENOMEM;

	new->nr_rt_entries = nr_rt_entries;
	क्रम (i = 0; i < KVM_NR_IRQCHIPS; i++)
		क्रम (j = 0; j < KVM_IRQCHIP_NUM_PINS; j++)
			new->chip[i][j] = -1;

	क्रम (i = 0; i < nr; ++i) अणु
		r = -ENOMEM;
		e = kzalloc(माप(*e), GFP_KERNEL_ACCOUNT);
		अगर (!e)
			जाओ out;

		r = -EINVAL;
		चयन (ue->type) अणु
		हाल KVM_IRQ_ROUTING_MSI:
			अगर (ue->flags & ~KVM_MSI_VALID_DEVID)
				जाओ मुक्त_entry;
			अवरोध;
		शेष:
			अगर (ue->flags)
				जाओ मुक्त_entry;
			अवरोध;
		पूर्ण
		r = setup_routing_entry(kvm, new, e, ue);
		अगर (r)
			जाओ मुक्त_entry;
		++ue;
	पूर्ण

	mutex_lock(&kvm->irq_lock);
	old = rcu_dereference_रक्षित(kvm->irq_routing, 1);
	rcu_assign_poपूर्णांकer(kvm->irq_routing, new);
	kvm_irq_routing_update(kvm);
	kvm_arch_irq_routing_update(kvm);
	mutex_unlock(&kvm->irq_lock);

	kvm_arch_post_irq_routing_update(kvm);

	synchronize_srcu_expedited(&kvm->irq_srcu);

	new = old;
	r = 0;
	जाओ out;

मुक्त_entry:
	kमुक्त(e);
out:
	मुक्त_irq_routing_table(new);

	वापस r;
पूर्ण
