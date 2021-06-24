<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GICv3 ITS emulation
 *
 * Copyright (C) 2015,2016 ARM Ltd.
 * Author: Andre Przywara <andre.przywara@arm.com>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/list_sort.h>

#समावेश <linux/irqchip/arm-gic-v3.h>

#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_arm.h>
#समावेश <यंत्र/kvm_mmu.h>

#समावेश "vgic.h"
#समावेश "vgic-mmio.h"

अटल पूर्णांक vgic_its_save_tables_v0(काष्ठा vgic_its *its);
अटल पूर्णांक vgic_its_restore_tables_v0(काष्ठा vgic_its *its);
अटल पूर्णांक vgic_its_commit_v0(काष्ठा vgic_its *its);
अटल पूर्णांक update_lpi_config(काष्ठा kvm *kvm, काष्ठा vgic_irq *irq,
			     काष्ठा kvm_vcpu *filter_vcpu, bool needs_inv);

/*
 * Creates a new (reference to a) काष्ठा vgic_irq क्रम a given LPI.
 * If this LPI is alपढ़ोy mapped on another ITS, we increase its refcount
 * and वापस a poपूर्णांकer to the existing काष्ठाure.
 * If this is a "new" LPI, we allocate and initialize a new काष्ठा vgic_irq.
 * This function वापसs a poपूर्णांकer to the _unlocked_ काष्ठाure.
 */
अटल काष्ठा vgic_irq *vgic_add_lpi(काष्ठा kvm *kvm, u32 पूर्णांकid,
				     काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा vgic_irq *irq = vgic_get_irq(kvm, शून्य, पूर्णांकid), *oldirq;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* In this हाल there is no put, since we keep the reference. */
	अगर (irq)
		वापस irq;

	irq = kzalloc(माप(काष्ठा vgic_irq), GFP_KERNEL);
	अगर (!irq)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&irq->lpi_list);
	INIT_LIST_HEAD(&irq->ap_list);
	raw_spin_lock_init(&irq->irq_lock);

	irq->config = VGIC_CONFIG_EDGE;
	kref_init(&irq->refcount);
	irq->पूर्णांकid = पूर्णांकid;
	irq->target_vcpu = vcpu;
	irq->group = 1;

	raw_spin_lock_irqsave(&dist->lpi_list_lock, flags);

	/*
	 * There could be a race with another vgic_add_lpi(), so we need to
	 * check that we करोn't add a second list entry with the same LPI.
	 */
	list_क्रम_each_entry(oldirq, &dist->lpi_list_head, lpi_list) अणु
		अगर (oldirq->पूर्णांकid != पूर्णांकid)
			जारी;

		/* Someone was faster with adding this LPI, lets use that. */
		kमुक्त(irq);
		irq = oldirq;

		/*
		 * This increases the refcount, the caller is expected to
		 * call vgic_put_irq() on the वापसed poपूर्णांकer once it's
		 * finished with the IRQ.
		 */
		vgic_get_irq_kref(irq);

		जाओ out_unlock;
	पूर्ण

	list_add_tail(&irq->lpi_list, &dist->lpi_list_head);
	dist->lpi_list_count++;

out_unlock:
	raw_spin_unlock_irqrestore(&dist->lpi_list_lock, flags);

	/*
	 * We "cache" the configuration table entries in our काष्ठा vgic_irq's.
	 * However we only have those काष्ठाs क्रम mapped IRQs, so we पढ़ो in
	 * the respective config data from memory here upon mapping the LPI.
	 *
	 * Should any of these fail, behave as अगर we couldn't create the LPI
	 * by dropping the refcount and वापसing the error.
	 */
	ret = update_lpi_config(kvm, irq, शून्य, false);
	अगर (ret) अणु
		vgic_put_irq(kvm, irq);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = vgic_v3_lpi_sync_pending_status(kvm, irq);
	अगर (ret) अणु
		vgic_put_irq(kvm, irq);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस irq;
पूर्ण

काष्ठा its_device अणु
	काष्ठा list_head dev_list;

	/* the head क्रम the list of ITTEs */
	काष्ठा list_head itt_head;
	u32 num_eventid_bits;
	gpa_t itt_addr;
	u32 device_id;
पूर्ण;

#घोषणा COLLECTION_NOT_MAPPED ((u32)~0)

काष्ठा its_collection अणु
	काष्ठा list_head coll_list;

	u32 collection_id;
	u32 target_addr;
पूर्ण;

#घोषणा its_is_collection_mapped(coll) ((coll) && \
				((coll)->target_addr != COLLECTION_NOT_MAPPED))

काष्ठा its_ite अणु
	काष्ठा list_head ite_list;

	काष्ठा vgic_irq *irq;
	काष्ठा its_collection *collection;
	u32 event_id;
पूर्ण;

काष्ठा vgic_translation_cache_entry अणु
	काष्ठा list_head	entry;
	phys_addr_t		db;
	u32			devid;
	u32			eventid;
	काष्ठा vgic_irq		*irq;
पूर्ण;

/**
 * काष्ठा vgic_its_abi - ITS abi ops and settings
 * @cte_esz: collection table entry size
 * @dte_esz: device table entry size
 * @ite_esz: पूर्णांकerrupt translation table entry size
 * @save tables: save the ITS tables पूर्णांकo guest RAM
 * @restore_tables: restore the ITS पूर्णांकernal काष्ठाs from tables
 *  stored in guest RAM
 * @commit: initialize the रेजिस्टरs which expose the ABI settings,
 *  especially the entry sizes
 */
काष्ठा vgic_its_abi अणु
	पूर्णांक cte_esz;
	पूर्णांक dte_esz;
	पूर्णांक ite_esz;
	पूर्णांक (*save_tables)(काष्ठा vgic_its *its);
	पूर्णांक (*restore_tables)(काष्ठा vgic_its *its);
	पूर्णांक (*commit)(काष्ठा vgic_its *its);
पूर्ण;

#घोषणा ABI_0_ESZ	8
#घोषणा ESZ_MAX		ABI_0_ESZ

अटल स्थिर काष्ठा vgic_its_abi its_table_abi_versions[] = अणु
	[0] = अणु
	 .cte_esz = ABI_0_ESZ,
	 .dte_esz = ABI_0_ESZ,
	 .ite_esz = ABI_0_ESZ,
	 .save_tables = vgic_its_save_tables_v0,
	 .restore_tables = vgic_its_restore_tables_v0,
	 .commit = vgic_its_commit_v0,
	पूर्ण,
पूर्ण;

#घोषणा NR_ITS_ABIS	ARRAY_SIZE(its_table_abi_versions)

अंतरभूत स्थिर काष्ठा vgic_its_abi *vgic_its_get_abi(काष्ठा vgic_its *its)
अणु
	वापस &its_table_abi_versions[its->abi_rev];
पूर्ण

अटल पूर्णांक vgic_its_set_abi(काष्ठा vgic_its *its, u32 rev)
अणु
	स्थिर काष्ठा vgic_its_abi *abi;

	its->abi_rev = rev;
	abi = vgic_its_get_abi(its);
	वापस abi->commit(its);
पूर्ण

/*
 * Find and वापसs a device in the device table क्रम an ITS.
 * Must be called with the its_lock mutex held.
 */
अटल काष्ठा its_device *find_its_device(काष्ठा vgic_its *its, u32 device_id)
अणु
	काष्ठा its_device *device;

	list_क्रम_each_entry(device, &its->device_list, dev_list)
		अगर (device_id == device->device_id)
			वापस device;

	वापस शून्य;
पूर्ण

/*
 * Find and वापसs an पूर्णांकerrupt translation table entry (ITTE) क्रम a given
 * Device ID/Event ID pair on an ITS.
 * Must be called with the its_lock mutex held.
 */
अटल काष्ठा its_ite *find_ite(काष्ठा vgic_its *its, u32 device_id,
				  u32 event_id)
अणु
	काष्ठा its_device *device;
	काष्ठा its_ite *ite;

	device = find_its_device(its, device_id);
	अगर (device == शून्य)
		वापस शून्य;

	list_क्रम_each_entry(ite, &device->itt_head, ite_list)
		अगर (ite->event_id == event_id)
			वापस ite;

	वापस शून्य;
पूर्ण

/* To be used as an iterator this macro misses the enclosing parentheses */
#घोषणा क्रम_each_lpi_its(dev, ite, its) \
	list_क्रम_each_entry(dev, &(its)->device_list, dev_list) \
		list_क्रम_each_entry(ite, &(dev)->itt_head, ite_list)

#घोषणा GIC_LPI_OFFSET 8192

#घोषणा VITS_TYPER_IDBITS 16
#घोषणा VITS_TYPER_DEVBITS 16
#घोषणा VITS_DTE_MAX_DEVID_OFFSET	(BIT(14) - 1)
#घोषणा VITS_ITE_MAX_EVENTID_OFFSET	(BIT(16) - 1)

/*
 * Finds and वापसs a collection in the ITS collection table.
 * Must be called with the its_lock mutex held.
 */
अटल काष्ठा its_collection *find_collection(काष्ठा vgic_its *its, पूर्णांक coll_id)
अणु
	काष्ठा its_collection *collection;

	list_क्रम_each_entry(collection, &its->collection_list, coll_list) अणु
		अगर (coll_id == collection->collection_id)
			वापस collection;
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा LPI_PROP_ENABLE_BIT(p)	((p) & LPI_PROP_ENABLED)
#घोषणा LPI_PROP_PRIORITY(p)	((p) & 0xfc)

/*
 * Reads the configuration data क्रम a given LPI from guest memory and
 * updates the fields in काष्ठा vgic_irq.
 * If filter_vcpu is not शून्य, applies only अगर the IRQ is targeting this
 * VCPU. Unconditionally applies अगर filter_vcpu is शून्य.
 */
अटल पूर्णांक update_lpi_config(काष्ठा kvm *kvm, काष्ठा vgic_irq *irq,
			     काष्ठा kvm_vcpu *filter_vcpu, bool needs_inv)
अणु
	u64 propbase = GICR_PROPBASER_ADDRESS(kvm->arch.vgic.propbaser);
	u8 prop;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	ret = kvm_पढ़ो_guest_lock(kvm, propbase + irq->पूर्णांकid - GIC_LPI_OFFSET,
				  &prop, 1);

	अगर (ret)
		वापस ret;

	raw_spin_lock_irqsave(&irq->irq_lock, flags);

	अगर (!filter_vcpu || filter_vcpu == irq->target_vcpu) अणु
		irq->priority = LPI_PROP_PRIORITY(prop);
		irq->enabled = LPI_PROP_ENABLE_BIT(prop);

		अगर (!irq->hw) अणु
			vgic_queue_irq_unlock(kvm, irq, flags);
			वापस 0;
		पूर्ण
	पूर्ण

	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

	अगर (irq->hw)
		वापस its_prop_update_vlpi(irq->host_irq, prop, needs_inv);

	वापस 0;
पूर्ण

/*
 * Create a snapshot of the current LPIs targeting @vcpu, so that we can
 * क्रमागतerate those LPIs without holding any lock.
 * Returns their number and माला_दो the kदो_स्मृति'ed array पूर्णांकo पूर्णांकid_ptr.
 */
पूर्णांक vgic_copy_lpi_list(काष्ठा kvm *kvm, काष्ठा kvm_vcpu *vcpu, u32 **पूर्णांकid_ptr)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा vgic_irq *irq;
	अचिन्हित दीर्घ flags;
	u32 *पूर्णांकids;
	पूर्णांक irq_count, i = 0;

	/*
	 * There is an obvious race between allocating the array and LPIs
	 * being mapped/unmapped. If we ended up here as a result of a
	 * command, we're safe (locks are held, preventing another
	 * command). If coming from another path (such as enabling LPIs),
	 * we must be careful not to overrun the array.
	 */
	irq_count = READ_ONCE(dist->lpi_list_count);
	पूर्णांकids = kदो_स्मृति_array(irq_count, माप(पूर्णांकids[0]), GFP_KERNEL);
	अगर (!पूर्णांकids)
		वापस -ENOMEM;

	raw_spin_lock_irqsave(&dist->lpi_list_lock, flags);
	list_क्रम_each_entry(irq, &dist->lpi_list_head, lpi_list) अणु
		अगर (i == irq_count)
			अवरोध;
		/* We करोn't need to "get" the IRQ, as we hold the list lock. */
		अगर (vcpu && irq->target_vcpu != vcpu)
			जारी;
		पूर्णांकids[i++] = irq->पूर्णांकid;
	पूर्ण
	raw_spin_unlock_irqrestore(&dist->lpi_list_lock, flags);

	*पूर्णांकid_ptr = पूर्णांकids;
	वापस i;
पूर्ण

अटल पूर्णांक update_affinity(काष्ठा vgic_irq *irq, काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	irq->target_vcpu = vcpu;
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

	अगर (irq->hw) अणु
		काष्ठा its_vlpi_map map;

		ret = its_get_vlpi(irq->host_irq, &map);
		अगर (ret)
			वापस ret;

		अगर (map.vpe)
			atomic_dec(&map.vpe->vlpi_count);
		map.vpe = &vcpu->arch.vgic_cpu.vgic_v3.its_vpe;
		atomic_inc(&map.vpe->vlpi_count);

		ret = its_map_vlpi(irq->host_irq, &map);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Promotes the ITS view of affinity of an ITTE (which redistributor this LPI
 * is targeting) to the VGIC's view, which deals with target VCPUs.
 * Needs to be called whenever either the collection क्रम a LPIs has
 * changed or the collection itself got retargeted.
 */
अटल व्योम update_affinity_ite(काष्ठा kvm *kvm, काष्ठा its_ite *ite)
अणु
	काष्ठा kvm_vcpu *vcpu;

	अगर (!its_is_collection_mapped(ite->collection))
		वापस;

	vcpu = kvm_get_vcpu(kvm, ite->collection->target_addr);
	update_affinity(ite->irq, vcpu);
पूर्ण

/*
 * Updates the target VCPU क्रम every LPI targeting this collection.
 * Must be called with the its_lock mutex held.
 */
अटल व्योम update_affinity_collection(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				       काष्ठा its_collection *coll)
अणु
	काष्ठा its_device *device;
	काष्ठा its_ite *ite;

	क्रम_each_lpi_its(device, ite, its) अणु
		अगर (!ite->collection || coll != ite->collection)
			जारी;

		update_affinity_ite(kvm, ite);
	पूर्ण
पूर्ण

अटल u32 max_lpis_propbaser(u64 propbaser)
अणु
	पूर्णांक nr_idbits = (propbaser & 0x1f) + 1;

	वापस 1U << min(nr_idbits, INTERRUPT_ID_BITS_ITS);
पूर्ण

/*
 * Sync the pending table pending bit of LPIs targeting @vcpu
 * with our own data काष्ठाures. This relies on the LPI being
 * mapped beक्रमe.
 */
अटल पूर्णांक its_sync_lpi_pending_table(काष्ठा kvm_vcpu *vcpu)
अणु
	gpa_t pendbase = GICR_PENDBASER_ADDRESS(vcpu->arch.vgic_cpu.pendbaser);
	काष्ठा vgic_irq *irq;
	पूर्णांक last_byte_offset = -1;
	पूर्णांक ret = 0;
	u32 *पूर्णांकids;
	पूर्णांक nr_irqs, i;
	अचिन्हित दीर्घ flags;
	u8 pendmask;

	nr_irqs = vgic_copy_lpi_list(vcpu->kvm, vcpu, &पूर्णांकids);
	अगर (nr_irqs < 0)
		वापस nr_irqs;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		पूर्णांक byte_offset, bit_nr;

		byte_offset = पूर्णांकids[i] / BITS_PER_BYTE;
		bit_nr = पूर्णांकids[i] % BITS_PER_BYTE;

		/*
		 * For contiguously allocated LPIs chances are we just पढ़ो
		 * this very same byte in the last iteration. Reuse that.
		 */
		अगर (byte_offset != last_byte_offset) अणु
			ret = kvm_पढ़ो_guest_lock(vcpu->kvm,
						  pendbase + byte_offset,
						  &pendmask, 1);
			अगर (ret) अणु
				kमुक्त(पूर्णांकids);
				वापस ret;
			पूर्ण
			last_byte_offset = byte_offset;
		पूर्ण

		irq = vgic_get_irq(vcpu->kvm, शून्य, पूर्णांकids[i]);
		raw_spin_lock_irqsave(&irq->irq_lock, flags);
		irq->pending_latch = pendmask & (1U << bit_nr);
		vgic_queue_irq_unlock(vcpu->kvm, irq, flags);
		vgic_put_irq(vcpu->kvm, irq);
	पूर्ण

	kमुक्त(पूर्णांकids);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_its_typer(काष्ठा kvm *kvm,
					      काष्ठा vgic_its *its,
					      gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	स्थिर काष्ठा vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 reg = GITS_TYPER_PLPIS;

	/*
	 * We use linear CPU numbers क्रम redistributor addressing,
	 * so GITS_TYPER.PTA is 0.
	 * Also we क्रमce all PROPBASER रेजिस्टरs to be the same, so
	 * CommonLPIAff is 0 as well.
	 * To aव्योम memory waste in the guest, we keep the number of IDBits and
	 * DevBits low - as least क्रम the समय being.
	 */
	reg |= GIC_ENCODE_SZ(VITS_TYPER_DEVBITS, 5) << GITS_TYPER_DEVBITS_SHIFT;
	reg |= GIC_ENCODE_SZ(VITS_TYPER_IDBITS, 5) << GITS_TYPER_IDBITS_SHIFT;
	reg |= GIC_ENCODE_SZ(abi->ite_esz, 4) << GITS_TYPER_ITT_ENTRY_SIZE_SHIFT;

	वापस extract_bytes(reg, addr & 7, len);
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_its_iidr(काष्ठा kvm *kvm,
					     काष्ठा vgic_its *its,
					     gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u32 val;

	val = (its->abi_rev << GITS_IIDR_REV_SHIFT) & GITS_IIDR_REV_MASK;
	val |= (PRODUCT_ID_KVM << GITS_IIDR_PRODUCTID_SHIFT) | IMPLEMENTER_ARM;
	वापस val;
पूर्ण

अटल पूर्णांक vgic_mmio_uaccess_ग_लिखो_its_iidr(काष्ठा kvm *kvm,
					    काष्ठा vgic_its *its,
					    gpa_t addr, अचिन्हित पूर्णांक len,
					    अचिन्हित दीर्घ val)
अणु
	u32 rev = GITS_IIDR_REV(val);

	अगर (rev >= NR_ITS_ABIS)
		वापस -EINVAL;
	वापस vgic_its_set_abi(its, rev);
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_its_idregs(काष्ठा kvm *kvm,
					       काष्ठा vgic_its *its,
					       gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	चयन (addr & 0xffff) अणु
	हाल GITS_PIDR0:
		वापस 0x92;	/* part number, bits[7:0] */
	हाल GITS_PIDR1:
		वापस 0xb4;	/* part number, bits[11:8] */
	हाल GITS_PIDR2:
		वापस GIC_PIDR2_ARCH_GICv3 | 0x0b;
	हाल GITS_PIDR4:
		वापस 0x40;	/* This is a 64K software visible page */
	/* The following are the ID रेजिस्टरs क्रम (any) GIC. */
	हाल GITS_CIDR0:
		वापस 0x0d;
	हाल GITS_CIDR1:
		वापस 0xf0;
	हाल GITS_CIDR2:
		वापस 0x05;
	हाल GITS_CIDR3:
		वापस 0xb1;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा vgic_irq *__vgic_its_check_cache(काष्ठा vgic_dist *dist,
					       phys_addr_t db,
					       u32 devid, u32 eventid)
अणु
	काष्ठा vgic_translation_cache_entry *cte;

	list_क्रम_each_entry(cte, &dist->lpi_translation_cache, entry) अणु
		/*
		 * If we hit a शून्य entry, there is nothing after this
		 * poपूर्णांक.
		 */
		अगर (!cte->irq)
			अवरोध;

		अगर (cte->db != db || cte->devid != devid ||
		    cte->eventid != eventid)
			जारी;

		/*
		 * Move this entry to the head, as it is the most
		 * recently used.
		 */
		अगर (!list_is_first(&cte->entry, &dist->lpi_translation_cache))
			list_move(&cte->entry, &dist->lpi_translation_cache);

		वापस cte->irq;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा vgic_irq *vgic_its_check_cache(काष्ठा kvm *kvm, phys_addr_t db,
					     u32 devid, u32 eventid)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा vgic_irq *irq;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&dist->lpi_list_lock, flags);
	irq = __vgic_its_check_cache(dist, db, devid, eventid);
	raw_spin_unlock_irqrestore(&dist->lpi_list_lock, flags);

	वापस irq;
पूर्ण

अटल व्योम vgic_its_cache_translation(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				       u32 devid, u32 eventid,
				       काष्ठा vgic_irq *irq)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा vgic_translation_cache_entry *cte;
	अचिन्हित दीर्घ flags;
	phys_addr_t db;

	/* Do not cache a directly injected पूर्णांकerrupt */
	अगर (irq->hw)
		वापस;

	raw_spin_lock_irqsave(&dist->lpi_list_lock, flags);

	अगर (unlikely(list_empty(&dist->lpi_translation_cache)))
		जाओ out;

	/*
	 * We could have raced with another CPU caching the same
	 * translation behind our back, so let's check it is not in
	 * alपढ़ोy
	 */
	db = its->vgic_its_base + GITS_TRANSLATER;
	अगर (__vgic_its_check_cache(dist, db, devid, eventid))
		जाओ out;

	/* Always reuse the last entry (LRU policy) */
	cte = list_last_entry(&dist->lpi_translation_cache,
			      typeof(*cte), entry);

	/*
	 * Caching the translation implies having an extra reference
	 * to the पूर्णांकerrupt, so drop the potential reference on what
	 * was in the cache, and increment it on the new पूर्णांकerrupt.
	 */
	अगर (cte->irq)
		__vgic_put_lpi_locked(kvm, cte->irq);

	vgic_get_irq_kref(irq);

	cte->db		= db;
	cte->devid	= devid;
	cte->eventid	= eventid;
	cte->irq	= irq;

	/* Move the new translation to the head of the list */
	list_move(&cte->entry, &dist->lpi_translation_cache);

out:
	raw_spin_unlock_irqrestore(&dist->lpi_list_lock, flags);
पूर्ण

व्योम vgic_its_invalidate_cache(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा vgic_translation_cache_entry *cte;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&dist->lpi_list_lock, flags);

	list_क्रम_each_entry(cte, &dist->lpi_translation_cache, entry) अणु
		/*
		 * If we hit a शून्य entry, there is nothing after this
		 * poपूर्णांक.
		 */
		अगर (!cte->irq)
			अवरोध;

		__vgic_put_lpi_locked(kvm, cte->irq);
		cte->irq = शून्य;
	पूर्ण

	raw_spin_unlock_irqrestore(&dist->lpi_list_lock, flags);
पूर्ण

पूर्णांक vgic_its_resolve_lpi(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
			 u32 devid, u32 eventid, काष्ठा vgic_irq **irq)
अणु
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा its_ite *ite;

	अगर (!its->enabled)
		वापस -EBUSY;

	ite = find_ite(its, devid, eventid);
	अगर (!ite || !its_is_collection_mapped(ite->collection))
		वापस E_ITS_INT_UNMAPPED_INTERRUPT;

	vcpu = kvm_get_vcpu(kvm, ite->collection->target_addr);
	अगर (!vcpu)
		वापस E_ITS_INT_UNMAPPED_INTERRUPT;

	अगर (!vcpu->arch.vgic_cpu.lpis_enabled)
		वापस -EBUSY;

	vgic_its_cache_translation(kvm, its, devid, eventid, ite->irq);

	*irq = ite->irq;
	वापस 0;
पूर्ण

काष्ठा vgic_its *vgic_msi_to_its(काष्ठा kvm *kvm, काष्ठा kvm_msi *msi)
अणु
	u64 address;
	काष्ठा kvm_io_device *kvm_io_dev;
	काष्ठा vgic_io_device *iodev;

	अगर (!vgic_has_its(kvm))
		वापस ERR_PTR(-ENODEV);

	अगर (!(msi->flags & KVM_MSI_VALID_DEVID))
		वापस ERR_PTR(-EINVAL);

	address = (u64)msi->address_hi << 32 | msi->address_lo;

	kvm_io_dev = kvm_io_bus_get_dev(kvm, KVM_MMIO_BUS, address);
	अगर (!kvm_io_dev)
		वापस ERR_PTR(-EINVAL);

	अगर (kvm_io_dev->ops != &kvm_io_gic_ops)
		वापस ERR_PTR(-EINVAL);

	iodev = container_of(kvm_io_dev, काष्ठा vgic_io_device, dev);
	अगर (iodev->iodev_type != IODEV_ITS)
		वापस ERR_PTR(-EINVAL);

	वापस iodev->its;
पूर्ण

/*
 * Find the target VCPU and the LPI number क्रम a given devid/eventid pair
 * and make this IRQ pending, possibly injecting it.
 * Must be called with the its_lock mutex held.
 * Returns 0 on success, a positive error value क्रम any ITS mapping
 * related errors and negative error values क्रम generic errors.
 */
अटल पूर्णांक vgic_its_trigger_msi(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				u32 devid, u32 eventid)
अणु
	काष्ठा vgic_irq *irq = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	err = vgic_its_resolve_lpi(kvm, its, devid, eventid, &irq);
	अगर (err)
		वापस err;

	अगर (irq->hw)
		वापस irq_set_irqchip_state(irq->host_irq,
					     IRQCHIP_STATE_PENDING, true);

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	irq->pending_latch = true;
	vgic_queue_irq_unlock(kvm, irq, flags);

	वापस 0;
पूर्ण

पूर्णांक vgic_its_inject_cached_translation(काष्ठा kvm *kvm, काष्ठा kvm_msi *msi)
अणु
	काष्ठा vgic_irq *irq;
	अचिन्हित दीर्घ flags;
	phys_addr_t db;

	db = (u64)msi->address_hi << 32 | msi->address_lo;
	irq = vgic_its_check_cache(kvm, db, msi->devid, msi->data);
	अगर (!irq)
		वापस -EWOULDBLOCK;

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	irq->pending_latch = true;
	vgic_queue_irq_unlock(kvm, irq, flags);

	वापस 0;
पूर्ण

/*
 * Queries the KVM IO bus framework to get the ITS poपूर्णांकer from the given
 * करोorbell address.
 * We then call vgic_its_trigger_msi() with the decoded data.
 * According to the KVM_SIGNAL_MSI API description वापसs 1 on success.
 */
पूर्णांक vgic_its_inject_msi(काष्ठा kvm *kvm, काष्ठा kvm_msi *msi)
अणु
	काष्ठा vgic_its *its;
	पूर्णांक ret;

	अगर (!vgic_its_inject_cached_translation(kvm, msi))
		वापस 1;

	its = vgic_msi_to_its(kvm, msi);
	अगर (IS_ERR(its))
		वापस PTR_ERR(its);

	mutex_lock(&its->its_lock);
	ret = vgic_its_trigger_msi(kvm, its, msi->devid, msi->data);
	mutex_unlock(&its->its_lock);

	अगर (ret < 0)
		वापस ret;

	/*
	 * KVM_SIGNAL_MSI demands a वापस value > 0 क्रम success and 0
	 * अगर the guest has blocked the MSI. So we map any LPI mapping
	 * related error to that.
	 */
	अगर (ret)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

/* Requires the its_lock to be held. */
अटल व्योम its_मुक्त_ite(काष्ठा kvm *kvm, काष्ठा its_ite *ite)
अणु
	list_del(&ite->ite_list);

	/* This put matches the get in vgic_add_lpi. */
	अगर (ite->irq) अणु
		अगर (ite->irq->hw)
			WARN_ON(its_unmap_vlpi(ite->irq->host_irq));

		vgic_put_irq(kvm, ite->irq);
	पूर्ण

	kमुक्त(ite);
पूर्ण

अटल u64 its_cmd_mask_field(u64 *its_cmd, पूर्णांक word, पूर्णांक shअगरt, पूर्णांक size)
अणु
	वापस (le64_to_cpu(its_cmd[word]) >> shअगरt) & (BIT_ULL(size) - 1);
पूर्ण

#घोषणा its_cmd_get_command(cmd)	its_cmd_mask_field(cmd, 0,  0,  8)
#घोषणा its_cmd_get_deviceid(cmd)	its_cmd_mask_field(cmd, 0, 32, 32)
#घोषणा its_cmd_get_size(cmd)		(its_cmd_mask_field(cmd, 1,  0,  5) + 1)
#घोषणा its_cmd_get_id(cmd)		its_cmd_mask_field(cmd, 1,  0, 32)
#घोषणा its_cmd_get_physical_id(cmd)	its_cmd_mask_field(cmd, 1, 32, 32)
#घोषणा its_cmd_get_collection(cmd)	its_cmd_mask_field(cmd, 2,  0, 16)
#घोषणा its_cmd_get_ittaddr(cmd)	(its_cmd_mask_field(cmd, 2,  8, 44) << 8)
#घोषणा its_cmd_get_target_addr(cmd)	its_cmd_mask_field(cmd, 2, 16, 32)
#घोषणा its_cmd_get_validbit(cmd)	its_cmd_mask_field(cmd, 2, 63,  1)

/*
 * The DISCARD command मुक्तs an Interrupt Translation Table Entry (ITTE).
 * Must be called with the its_lock mutex held.
 */
अटल पूर्णांक vgic_its_cmd_handle_discard(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				       u64 *its_cmd)
अणु
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	काष्ठा its_ite *ite;

	ite = find_ite(its, device_id, event_id);
	अगर (ite && its_is_collection_mapped(ite->collection)) अणु
		/*
		 * Though the spec talks about removing the pending state, we
		 * करोn't bother here since we clear the ITTE anyway and the
		 * pending state is a property of the ITTE काष्ठा.
		 */
		vgic_its_invalidate_cache(kvm);

		its_मुक्त_ite(kvm, ite);
		वापस 0;
	पूर्ण

	वापस E_ITS_DISCARD_UNMAPPED_INTERRUPT;
पूर्ण

/*
 * The MOVI command moves an ITTE to a dअगरferent collection.
 * Must be called with the its_lock mutex held.
 */
अटल पूर्णांक vgic_its_cmd_handle_movi(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				    u64 *its_cmd)
अणु
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	u32 coll_id = its_cmd_get_collection(its_cmd);
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा its_ite *ite;
	काष्ठा its_collection *collection;

	ite = find_ite(its, device_id, event_id);
	अगर (!ite)
		वापस E_ITS_MOVI_UNMAPPED_INTERRUPT;

	अगर (!its_is_collection_mapped(ite->collection))
		वापस E_ITS_MOVI_UNMAPPED_COLLECTION;

	collection = find_collection(its, coll_id);
	अगर (!its_is_collection_mapped(collection))
		वापस E_ITS_MOVI_UNMAPPED_COLLECTION;

	ite->collection = collection;
	vcpu = kvm_get_vcpu(kvm, collection->target_addr);

	vgic_its_invalidate_cache(kvm);

	वापस update_affinity(ite->irq, vcpu);
पूर्ण

/*
 * Check whether an ID can be stored पूर्णांकo the corresponding guest table.
 * For a direct table this is pretty easy, but माला_लो a bit nasty क्रम
 * indirect tables. We check whether the resulting guest physical address
 * is actually valid (covered by a memslot and guest accessible).
 * For this we have to पढ़ो the respective first level entry.
 */
अटल bool vgic_its_check_id(काष्ठा vgic_its *its, u64 baser, u32 id,
			      gpa_t *eaddr)
अणु
	पूर्णांक l1_tbl_size = GITS_BASER_NR_PAGES(baser) * SZ_64K;
	u64 indirect_ptr, type = GITS_BASER_TYPE(baser);
	phys_addr_t base = GITS_BASER_ADDR_48_to_52(baser);
	पूर्णांक esz = GITS_BASER_ENTRY_SIZE(baser);
	पूर्णांक index, idx;
	gfn_t gfn;
	bool ret;

	चयन (type) अणु
	हाल GITS_BASER_TYPE_DEVICE:
		अगर (id >= BIT_ULL(VITS_TYPER_DEVBITS))
			वापस false;
		अवरोध;
	हाल GITS_BASER_TYPE_COLLECTION:
		/* as GITS_TYPER.CIL == 0, ITS supports 16-bit collection ID */
		अगर (id >= BIT_ULL(16))
			वापस false;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (!(baser & GITS_BASER_INसूचीECT)) अणु
		phys_addr_t addr;

		अगर (id >= (l1_tbl_size / esz))
			वापस false;

		addr = base + id * esz;
		gfn = addr >> PAGE_SHIFT;

		अगर (eaddr)
			*eaddr = addr;

		जाओ out;
	पूर्ण

	/* calculate and check the index पूर्णांकo the 1st level */
	index = id / (SZ_64K / esz);
	अगर (index >= (l1_tbl_size / माप(u64)))
		वापस false;

	/* Each 1st level entry is represented by a 64-bit value. */
	अगर (kvm_पढ़ो_guest_lock(its->dev->kvm,
			   base + index * माप(indirect_ptr),
			   &indirect_ptr, माप(indirect_ptr)))
		वापस false;

	indirect_ptr = le64_to_cpu(indirect_ptr);

	/* check the valid bit of the first level entry */
	अगर (!(indirect_ptr & BIT_ULL(63)))
		वापस false;

	/* Mask the guest physical address and calculate the frame number. */
	indirect_ptr &= GENMASK_ULL(51, 16);

	/* Find the address of the actual entry */
	index = id % (SZ_64K / esz);
	indirect_ptr += index * esz;
	gfn = indirect_ptr >> PAGE_SHIFT;

	अगर (eaddr)
		*eaddr = indirect_ptr;

out:
	idx = srcu_पढ़ो_lock(&its->dev->kvm->srcu);
	ret = kvm_is_visible_gfn(its->dev->kvm, gfn);
	srcu_पढ़ो_unlock(&its->dev->kvm->srcu, idx);
	वापस ret;
पूर्ण

अटल पूर्णांक vgic_its_alloc_collection(काष्ठा vgic_its *its,
				     काष्ठा its_collection **colp,
				     u32 coll_id)
अणु
	काष्ठा its_collection *collection;

	अगर (!vgic_its_check_id(its, its->baser_coll_table, coll_id, शून्य))
		वापस E_ITS_MAPC_COLLECTION_OOR;

	collection = kzalloc(माप(*collection), GFP_KERNEL);
	अगर (!collection)
		वापस -ENOMEM;

	collection->collection_id = coll_id;
	collection->target_addr = COLLECTION_NOT_MAPPED;

	list_add_tail(&collection->coll_list, &its->collection_list);
	*colp = collection;

	वापस 0;
पूर्ण

अटल व्योम vgic_its_मुक्त_collection(काष्ठा vgic_its *its, u32 coll_id)
अणु
	काष्ठा its_collection *collection;
	काष्ठा its_device *device;
	काष्ठा its_ite *ite;

	/*
	 * Clearing the mapping क्रम that collection ID हटाओs the
	 * entry from the list. If there wasn't any beक्रमe, we can
	 * go home early.
	 */
	collection = find_collection(its, coll_id);
	अगर (!collection)
		वापस;

	क्रम_each_lpi_its(device, ite, its)
		अगर (ite->collection &&
		    ite->collection->collection_id == coll_id)
			ite->collection = शून्य;

	list_del(&collection->coll_list);
	kमुक्त(collection);
पूर्ण

/* Must be called with its_lock mutex held */
अटल काष्ठा its_ite *vgic_its_alloc_ite(काष्ठा its_device *device,
					  काष्ठा its_collection *collection,
					  u32 event_id)
अणु
	काष्ठा its_ite *ite;

	ite = kzalloc(माप(*ite), GFP_KERNEL);
	अगर (!ite)
		वापस ERR_PTR(-ENOMEM);

	ite->event_id	= event_id;
	ite->collection = collection;

	list_add_tail(&ite->ite_list, &device->itt_head);
	वापस ite;
पूर्ण

/*
 * The MAPTI and MAPI commands map LPIs to ITTEs.
 * Must be called with its_lock mutex held.
 */
अटल पूर्णांक vgic_its_cmd_handle_mapi(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				    u64 *its_cmd)
अणु
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	u32 coll_id = its_cmd_get_collection(its_cmd);
	काष्ठा its_ite *ite;
	काष्ठा kvm_vcpu *vcpu = शून्य;
	काष्ठा its_device *device;
	काष्ठा its_collection *collection, *new_coll = शून्य;
	काष्ठा vgic_irq *irq;
	पूर्णांक lpi_nr;

	device = find_its_device(its, device_id);
	अगर (!device)
		वापस E_ITS_MAPTI_UNMAPPED_DEVICE;

	अगर (event_id >= BIT_ULL(device->num_eventid_bits))
		वापस E_ITS_MAPTI_ID_OOR;

	अगर (its_cmd_get_command(its_cmd) == GITS_CMD_MAPTI)
		lpi_nr = its_cmd_get_physical_id(its_cmd);
	अन्यथा
		lpi_nr = event_id;
	अगर (lpi_nr < GIC_LPI_OFFSET ||
	    lpi_nr >= max_lpis_propbaser(kvm->arch.vgic.propbaser))
		वापस E_ITS_MAPTI_PHYSICALID_OOR;

	/* If there is an existing mapping, behavior is UNPREDICTABLE. */
	अगर (find_ite(its, device_id, event_id))
		वापस 0;

	collection = find_collection(its, coll_id);
	अगर (!collection) अणु
		पूर्णांक ret = vgic_its_alloc_collection(its, &collection, coll_id);
		अगर (ret)
			वापस ret;
		new_coll = collection;
	पूर्ण

	ite = vgic_its_alloc_ite(device, collection, event_id);
	अगर (IS_ERR(ite)) अणु
		अगर (new_coll)
			vgic_its_मुक्त_collection(its, coll_id);
		वापस PTR_ERR(ite);
	पूर्ण

	अगर (its_is_collection_mapped(collection))
		vcpu = kvm_get_vcpu(kvm, collection->target_addr);

	irq = vgic_add_lpi(kvm, lpi_nr, vcpu);
	अगर (IS_ERR(irq)) अणु
		अगर (new_coll)
			vgic_its_मुक्त_collection(its, coll_id);
		its_मुक्त_ite(kvm, ite);
		वापस PTR_ERR(irq);
	पूर्ण
	ite->irq = irq;

	वापस 0;
पूर्ण

/* Requires the its_lock to be held. */
अटल व्योम vgic_its_मुक्त_device(काष्ठा kvm *kvm, काष्ठा its_device *device)
अणु
	काष्ठा its_ite *ite, *temp;

	/*
	 * The spec says that unmapping a device with still valid
	 * ITTEs associated is UNPREDICTABLE. We हटाओ all ITTEs,
	 * since we cannot leave the memory unreferenced.
	 */
	list_क्रम_each_entry_safe(ite, temp, &device->itt_head, ite_list)
		its_मुक्त_ite(kvm, ite);

	vgic_its_invalidate_cache(kvm);

	list_del(&device->dev_list);
	kमुक्त(device);
पूर्ण

/* its lock must be held */
अटल व्योम vgic_its_मुक्त_device_list(काष्ठा kvm *kvm, काष्ठा vgic_its *its)
अणु
	काष्ठा its_device *cur, *temp;

	list_क्रम_each_entry_safe(cur, temp, &its->device_list, dev_list)
		vgic_its_मुक्त_device(kvm, cur);
पूर्ण

/* its lock must be held */
अटल व्योम vgic_its_मुक्त_collection_list(काष्ठा kvm *kvm, काष्ठा vgic_its *its)
अणु
	काष्ठा its_collection *cur, *temp;

	list_क्रम_each_entry_safe(cur, temp, &its->collection_list, coll_list)
		vgic_its_मुक्त_collection(its, cur->collection_id);
पूर्ण

/* Must be called with its_lock mutex held */
अटल काष्ठा its_device *vgic_its_alloc_device(काष्ठा vgic_its *its,
						u32 device_id, gpa_t itt_addr,
						u8 num_eventid_bits)
अणु
	काष्ठा its_device *device;

	device = kzalloc(माप(*device), GFP_KERNEL);
	अगर (!device)
		वापस ERR_PTR(-ENOMEM);

	device->device_id = device_id;
	device->itt_addr = itt_addr;
	device->num_eventid_bits = num_eventid_bits;
	INIT_LIST_HEAD(&device->itt_head);

	list_add_tail(&device->dev_list, &its->device_list);
	वापस device;
पूर्ण

/*
 * MAPD maps or unmaps a device ID to Interrupt Translation Tables (ITTs).
 * Must be called with the its_lock mutex held.
 */
अटल पूर्णांक vgic_its_cmd_handle_mapd(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				    u64 *its_cmd)
अणु
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	bool valid = its_cmd_get_validbit(its_cmd);
	u8 num_eventid_bits = its_cmd_get_size(its_cmd);
	gpa_t itt_addr = its_cmd_get_ittaddr(its_cmd);
	काष्ठा its_device *device;

	अगर (!vgic_its_check_id(its, its->baser_device_table, device_id, शून्य))
		वापस E_ITS_MAPD_DEVICE_OOR;

	अगर (valid && num_eventid_bits > VITS_TYPER_IDBITS)
		वापस E_ITS_MAPD_ITTSIZE_OOR;

	device = find_its_device(its, device_id);

	/*
	 * The spec says that calling MAPD on an alपढ़ोy mapped device
	 * invalidates all cached data क्रम this device. We implement this
	 * by removing the mapping and re-establishing it.
	 */
	अगर (device)
		vgic_its_मुक्त_device(kvm, device);

	/*
	 * The spec करोes not say whether unmapping a not-mapped device
	 * is an error, so we are करोne in any हाल.
	 */
	अगर (!valid)
		वापस 0;

	device = vgic_its_alloc_device(its, device_id, itt_addr,
				       num_eventid_bits);

	वापस PTR_ERR_OR_ZERO(device);
पूर्ण

/*
 * The MAPC command maps collection IDs to redistributors.
 * Must be called with the its_lock mutex held.
 */
अटल पूर्णांक vgic_its_cmd_handle_mapc(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				    u64 *its_cmd)
अणु
	u16 coll_id;
	u32 target_addr;
	काष्ठा its_collection *collection;
	bool valid;

	valid = its_cmd_get_validbit(its_cmd);
	coll_id = its_cmd_get_collection(its_cmd);
	target_addr = its_cmd_get_target_addr(its_cmd);

	अगर (target_addr >= atomic_पढ़ो(&kvm->online_vcpus))
		वापस E_ITS_MAPC_PROCNUM_OOR;

	अगर (!valid) अणु
		vgic_its_मुक्त_collection(its, coll_id);
		vgic_its_invalidate_cache(kvm);
	पूर्ण अन्यथा अणु
		collection = find_collection(its, coll_id);

		अगर (!collection) अणु
			पूर्णांक ret;

			ret = vgic_its_alloc_collection(its, &collection,
							coll_id);
			अगर (ret)
				वापस ret;
			collection->target_addr = target_addr;
		पूर्ण अन्यथा अणु
			collection->target_addr = target_addr;
			update_affinity_collection(kvm, its, collection);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The CLEAR command हटाओs the pending state क्रम a particular LPI.
 * Must be called with the its_lock mutex held.
 */
अटल पूर्णांक vgic_its_cmd_handle_clear(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				     u64 *its_cmd)
अणु
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	काष्ठा its_ite *ite;


	ite = find_ite(its, device_id, event_id);
	अगर (!ite)
		वापस E_ITS_CLEAR_UNMAPPED_INTERRUPT;

	ite->irq->pending_latch = false;

	अगर (ite->irq->hw)
		वापस irq_set_irqchip_state(ite->irq->host_irq,
					     IRQCHIP_STATE_PENDING, false);

	वापस 0;
पूर्ण

/*
 * The INV command syncs the configuration bits from the memory table.
 * Must be called with the its_lock mutex held.
 */
अटल पूर्णांक vgic_its_cmd_handle_inv(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				   u64 *its_cmd)
अणु
	u32 device_id = its_cmd_get_deviceid(its_cmd);
	u32 event_id = its_cmd_get_id(its_cmd);
	काष्ठा its_ite *ite;


	ite = find_ite(its, device_id, event_id);
	अगर (!ite)
		वापस E_ITS_INV_UNMAPPED_INTERRUPT;

	वापस update_lpi_config(kvm, ite->irq, शून्य, true);
पूर्ण

/*
 * The INVALL command requests flushing of all IRQ data in this collection.
 * Find the VCPU mapped to that collection, then iterate over the VM's list
 * of mapped LPIs and update the configuration क्रम each IRQ which tarमाला_लो
 * the specअगरied vcpu. The configuration will be पढ़ो from the in-memory
 * configuration table.
 * Must be called with the its_lock mutex held.
 */
अटल पूर्णांक vgic_its_cmd_handle_invall(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				      u64 *its_cmd)
अणु
	u32 coll_id = its_cmd_get_collection(its_cmd);
	काष्ठा its_collection *collection;
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा vgic_irq *irq;
	u32 *पूर्णांकids;
	पूर्णांक irq_count, i;

	collection = find_collection(its, coll_id);
	अगर (!its_is_collection_mapped(collection))
		वापस E_ITS_INVALL_UNMAPPED_COLLECTION;

	vcpu = kvm_get_vcpu(kvm, collection->target_addr);

	irq_count = vgic_copy_lpi_list(kvm, vcpu, &पूर्णांकids);
	अगर (irq_count < 0)
		वापस irq_count;

	क्रम (i = 0; i < irq_count; i++) अणु
		irq = vgic_get_irq(kvm, शून्य, पूर्णांकids[i]);
		अगर (!irq)
			जारी;
		update_lpi_config(kvm, irq, vcpu, false);
		vgic_put_irq(kvm, irq);
	पूर्ण

	kमुक्त(पूर्णांकids);

	अगर (vcpu->arch.vgic_cpu.vgic_v3.its_vpe.its_vm)
		its_invall_vpe(&vcpu->arch.vgic_cpu.vgic_v3.its_vpe);

	वापस 0;
पूर्ण

/*
 * The MOVALL command moves the pending state of all IRQs targeting one
 * redistributor to another. We करोn't hold the pending state in the VCPUs,
 * but in the IRQs instead, so there is really not much to करो क्रम us here.
 * However the spec says that no IRQ must target the old redistributor
 * afterwards, so we make sure that no LPI is using the associated target_vcpu.
 * This command affects all LPIs in the प्रणाली that target that redistributor.
 */
अटल पूर्णांक vgic_its_cmd_handle_movall(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				      u64 *its_cmd)
अणु
	u32 target1_addr = its_cmd_get_target_addr(its_cmd);
	u32 target2_addr = its_cmd_mask_field(its_cmd, 3, 16, 32);
	काष्ठा kvm_vcpu *vcpu1, *vcpu2;
	काष्ठा vgic_irq *irq;
	u32 *पूर्णांकids;
	पूर्णांक irq_count, i;

	अगर (target1_addr >= atomic_पढ़ो(&kvm->online_vcpus) ||
	    target2_addr >= atomic_पढ़ो(&kvm->online_vcpus))
		वापस E_ITS_MOVALL_PROCNUM_OOR;

	अगर (target1_addr == target2_addr)
		वापस 0;

	vcpu1 = kvm_get_vcpu(kvm, target1_addr);
	vcpu2 = kvm_get_vcpu(kvm, target2_addr);

	irq_count = vgic_copy_lpi_list(kvm, vcpu1, &पूर्णांकids);
	अगर (irq_count < 0)
		वापस irq_count;

	क्रम (i = 0; i < irq_count; i++) अणु
		irq = vgic_get_irq(kvm, शून्य, पूर्णांकids[i]);

		update_affinity(irq, vcpu2);

		vgic_put_irq(kvm, irq);
	पूर्ण

	vgic_its_invalidate_cache(kvm);

	kमुक्त(पूर्णांकids);
	वापस 0;
पूर्ण

/*
 * The INT command injects the LPI associated with that DevID/EvID pair.
 * Must be called with the its_lock mutex held.
 */
अटल पूर्णांक vgic_its_cmd_handle_पूर्णांक(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				   u64 *its_cmd)
अणु
	u32 msi_data = its_cmd_get_id(its_cmd);
	u64 msi_devid = its_cmd_get_deviceid(its_cmd);

	वापस vgic_its_trigger_msi(kvm, its, msi_devid, msi_data);
पूर्ण

/*
 * This function is called with the its_cmd lock held, but the ITS data
 * काष्ठाure lock dropped.
 */
अटल पूर्णांक vgic_its_handle_command(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				   u64 *its_cmd)
अणु
	पूर्णांक ret = -ENODEV;

	mutex_lock(&its->its_lock);
	चयन (its_cmd_get_command(its_cmd)) अणु
	हाल GITS_CMD_MAPD:
		ret = vgic_its_cmd_handle_mapd(kvm, its, its_cmd);
		अवरोध;
	हाल GITS_CMD_MAPC:
		ret = vgic_its_cmd_handle_mapc(kvm, its, its_cmd);
		अवरोध;
	हाल GITS_CMD_MAPI:
		ret = vgic_its_cmd_handle_mapi(kvm, its, its_cmd);
		अवरोध;
	हाल GITS_CMD_MAPTI:
		ret = vgic_its_cmd_handle_mapi(kvm, its, its_cmd);
		अवरोध;
	हाल GITS_CMD_MOVI:
		ret = vgic_its_cmd_handle_movi(kvm, its, its_cmd);
		अवरोध;
	हाल GITS_CMD_DISCARD:
		ret = vgic_its_cmd_handle_discard(kvm, its, its_cmd);
		अवरोध;
	हाल GITS_CMD_CLEAR:
		ret = vgic_its_cmd_handle_clear(kvm, its, its_cmd);
		अवरोध;
	हाल GITS_CMD_MOVALL:
		ret = vgic_its_cmd_handle_movall(kvm, its, its_cmd);
		अवरोध;
	हाल GITS_CMD_INT:
		ret = vgic_its_cmd_handle_पूर्णांक(kvm, its, its_cmd);
		अवरोध;
	हाल GITS_CMD_INV:
		ret = vgic_its_cmd_handle_inv(kvm, its, its_cmd);
		अवरोध;
	हाल GITS_CMD_INVALL:
		ret = vgic_its_cmd_handle_invall(kvm, its, its_cmd);
		अवरोध;
	हाल GITS_CMD_SYNC:
		/* we ignore this command: we are in sync all of the समय */
		ret = 0;
		अवरोध;
	पूर्ण
	mutex_unlock(&its->its_lock);

	वापस ret;
पूर्ण

अटल u64 vgic_sanitise_its_baser(u64 reg)
अणु
	reg = vgic_sanitise_field(reg, GITS_BASER_SHAREABILITY_MASK,
				  GITS_BASER_SHAREABILITY_SHIFT,
				  vgic_sanitise_shareability);
	reg = vgic_sanitise_field(reg, GITS_BASER_INNER_CACHEABILITY_MASK,
				  GITS_BASER_INNER_CACHEABILITY_SHIFT,
				  vgic_sanitise_inner_cacheability);
	reg = vgic_sanitise_field(reg, GITS_BASER_OUTER_CACHEABILITY_MASK,
				  GITS_BASER_OUTER_CACHEABILITY_SHIFT,
				  vgic_sanitise_outer_cacheability);

	/* We support only one (ITS) page size: 64K */
	reg = (reg & ~GITS_BASER_PAGE_SIZE_MASK) | GITS_BASER_PAGE_SIZE_64K;

	वापस reg;
पूर्ण

अटल u64 vgic_sanitise_its_cbaser(u64 reg)
अणु
	reg = vgic_sanitise_field(reg, GITS_CBASER_SHAREABILITY_MASK,
				  GITS_CBASER_SHAREABILITY_SHIFT,
				  vgic_sanitise_shareability);
	reg = vgic_sanitise_field(reg, GITS_CBASER_INNER_CACHEABILITY_MASK,
				  GITS_CBASER_INNER_CACHEABILITY_SHIFT,
				  vgic_sanitise_inner_cacheability);
	reg = vgic_sanitise_field(reg, GITS_CBASER_OUTER_CACHEABILITY_MASK,
				  GITS_CBASER_OUTER_CACHEABILITY_SHIFT,
				  vgic_sanitise_outer_cacheability);

	/* Sanitise the physical address to be 64k aligned. */
	reg &= ~GENMASK_ULL(15, 12);

	वापस reg;
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_its_cbaser(काष्ठा kvm *kvm,
					       काष्ठा vgic_its *its,
					       gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	वापस extract_bytes(its->cbaser, addr & 7, len);
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_its_cbaser(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				       gpa_t addr, अचिन्हित पूर्णांक len,
				       अचिन्हित दीर्घ val)
अणु
	/* When GITS_CTLR.Enable is 1, this रेजिस्टर is RO. */
	अगर (its->enabled)
		वापस;

	mutex_lock(&its->cmd_lock);
	its->cbaser = update_64bit_reg(its->cbaser, addr & 7, len, val);
	its->cbaser = vgic_sanitise_its_cbaser(its->cbaser);
	its->cपढ़ोr = 0;
	/*
	 * CWRITER is architecturally UNKNOWN on reset, but we need to reset
	 * it to CREADR to make sure we start with an empty command buffer.
	 */
	its->cग_लिखोr = its->cपढ़ोr;
	mutex_unlock(&its->cmd_lock);
पूर्ण

#घोषणा ITS_CMD_BUFFER_SIZE(baser)	((((baser) & 0xff) + 1) << 12)
#घोषणा ITS_CMD_SIZE			32
#घोषणा ITS_CMD_OFFSET(reg)		((reg) & GENMASK(19, 5))

/* Must be called with the cmd_lock held. */
अटल व्योम vgic_its_process_commands(काष्ठा kvm *kvm, काष्ठा vgic_its *its)
अणु
	gpa_t cbaser;
	u64 cmd_buf[4];

	/* Commands are only processed when the ITS is enabled. */
	अगर (!its->enabled)
		वापस;

	cbaser = GITS_CBASER_ADDRESS(its->cbaser);

	जबतक (its->cग_लिखोr != its->cपढ़ोr) अणु
		पूर्णांक ret = kvm_पढ़ो_guest_lock(kvm, cbaser + its->cपढ़ोr,
					      cmd_buf, ITS_CMD_SIZE);
		/*
		 * If kvm_पढ़ो_guest() fails, this could be due to the guest
		 * programming a bogus value in CBASER or something अन्यथा going
		 * wrong from which we cannot easily recover.
		 * According to section 6.3.2 in the GICv3 spec we can just
		 * ignore that command then.
		 */
		अगर (!ret)
			vgic_its_handle_command(kvm, its, cmd_buf);

		its->cपढ़ोr += ITS_CMD_SIZE;
		अगर (its->cपढ़ोr == ITS_CMD_BUFFER_SIZE(its->cbaser))
			its->cपढ़ोr = 0;
	पूर्ण
पूर्ण

/*
 * By writing to CWRITER the guest announces new commands to be processed.
 * To aव्योम any races in the first place, we take the its_cmd lock, which
 * protects our ring buffer variables, so that there is only one user
 * per ITS handling commands at a given समय.
 */
अटल व्योम vgic_mmio_ग_लिखो_its_cग_लिखोr(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
					gpa_t addr, अचिन्हित पूर्णांक len,
					अचिन्हित दीर्घ val)
अणु
	u64 reg;

	अगर (!its)
		वापस;

	mutex_lock(&its->cmd_lock);

	reg = update_64bit_reg(its->cग_लिखोr, addr & 7, len, val);
	reg = ITS_CMD_OFFSET(reg);
	अगर (reg >= ITS_CMD_BUFFER_SIZE(its->cbaser)) अणु
		mutex_unlock(&its->cmd_lock);
		वापस;
	पूर्ण
	its->cग_लिखोr = reg;

	vgic_its_process_commands(kvm, its);

	mutex_unlock(&its->cmd_lock);
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_its_cग_लिखोr(काष्ठा kvm *kvm,
						काष्ठा vgic_its *its,
						gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	वापस extract_bytes(its->cग_लिखोr, addr & 0x7, len);
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_its_cपढ़ोr(काष्ठा kvm *kvm,
					       काष्ठा vgic_its *its,
					       gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	वापस extract_bytes(its->cपढ़ोr, addr & 0x7, len);
पूर्ण

अटल पूर्णांक vgic_mmio_uaccess_ग_लिखो_its_cपढ़ोr(काष्ठा kvm *kvm,
					      काष्ठा vgic_its *its,
					      gpa_t addr, अचिन्हित पूर्णांक len,
					      अचिन्हित दीर्घ val)
अणु
	u32 cmd_offset;
	पूर्णांक ret = 0;

	mutex_lock(&its->cmd_lock);

	अगर (its->enabled) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	cmd_offset = ITS_CMD_OFFSET(val);
	अगर (cmd_offset >= ITS_CMD_BUFFER_SIZE(its->cbaser)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	its->cपढ़ोr = cmd_offset;
out:
	mutex_unlock(&its->cmd_lock);
	वापस ret;
पूर्ण

#घोषणा BASER_INDEX(addr) (((addr) / माप(u64)) & 0x7)
अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_its_baser(काष्ठा kvm *kvm,
					      काष्ठा vgic_its *its,
					      gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u64 reg;

	चयन (BASER_INDEX(addr)) अणु
	हाल 0:
		reg = its->baser_device_table;
		अवरोध;
	हाल 1:
		reg = its->baser_coll_table;
		अवरोध;
	शेष:
		reg = 0;
		अवरोध;
	पूर्ण

	वापस extract_bytes(reg, addr & 7, len);
पूर्ण

#घोषणा GITS_BASER_RO_MASK	(GENMASK_ULL(52, 48) | GENMASK_ULL(58, 56))
अटल व्योम vgic_mmio_ग_लिखो_its_baser(काष्ठा kvm *kvm,
				      काष्ठा vgic_its *its,
				      gpa_t addr, अचिन्हित पूर्णांक len,
				      अचिन्हित दीर्घ val)
अणु
	स्थिर काष्ठा vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 entry_size, table_type;
	u64 reg, *regptr, clearbits = 0;

	/* When GITS_CTLR.Enable is 1, we ignore ग_लिखो accesses. */
	अगर (its->enabled)
		वापस;

	चयन (BASER_INDEX(addr)) अणु
	हाल 0:
		regptr = &its->baser_device_table;
		entry_size = abi->dte_esz;
		table_type = GITS_BASER_TYPE_DEVICE;
		अवरोध;
	हाल 1:
		regptr = &its->baser_coll_table;
		entry_size = abi->cte_esz;
		table_type = GITS_BASER_TYPE_COLLECTION;
		clearbits = GITS_BASER_INसूचीECT;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	reg = update_64bit_reg(*regptr, addr & 7, len, val);
	reg &= ~GITS_BASER_RO_MASK;
	reg &= ~clearbits;

	reg |= (entry_size - 1) << GITS_BASER_ENTRY_SIZE_SHIFT;
	reg |= table_type << GITS_BASER_TYPE_SHIFT;
	reg = vgic_sanitise_its_baser(reg);

	*regptr = reg;

	अगर (!(reg & GITS_BASER_VALID)) अणु
		/* Take the its_lock to prevent a race with a save/restore */
		mutex_lock(&its->its_lock);
		चयन (table_type) अणु
		हाल GITS_BASER_TYPE_DEVICE:
			vgic_its_मुक्त_device_list(kvm, its);
			अवरोध;
		हाल GITS_BASER_TYPE_COLLECTION:
			vgic_its_मुक्त_collection_list(kvm, its);
			अवरोध;
		पूर्ण
		mutex_unlock(&its->its_lock);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ vgic_mmio_पढ़ो_its_ctlr(काष्ठा kvm *vcpu,
					     काष्ठा vgic_its *its,
					     gpa_t addr, अचिन्हित पूर्णांक len)
अणु
	u32 reg = 0;

	mutex_lock(&its->cmd_lock);
	अगर (its->cपढ़ोr == its->cग_लिखोr)
		reg |= GITS_CTLR_QUIESCENT;
	अगर (its->enabled)
		reg |= GITS_CTLR_ENABLE;
	mutex_unlock(&its->cmd_lock);

	वापस reg;
पूर्ण

अटल व्योम vgic_mmio_ग_लिखो_its_ctlr(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				     gpa_t addr, अचिन्हित पूर्णांक len,
				     अचिन्हित दीर्घ val)
अणु
	mutex_lock(&its->cmd_lock);

	/*
	 * It is UNPREDICTABLE to enable the ITS अगर any of the CBASER or
	 * device/collection BASER are invalid
	 */
	अगर (!its->enabled && (val & GITS_CTLR_ENABLE) &&
		(!(its->baser_device_table & GITS_BASER_VALID) ||
		 !(its->baser_coll_table & GITS_BASER_VALID) ||
		 !(its->cbaser & GITS_CBASER_VALID)))
		जाओ out;

	its->enabled = !!(val & GITS_CTLR_ENABLE);
	अगर (!its->enabled)
		vgic_its_invalidate_cache(kvm);

	/*
	 * Try to process any pending commands. This function bails out early
	 * अगर the ITS is disabled or no commands have been queued.
	 */
	vgic_its_process_commands(kvm, its);

out:
	mutex_unlock(&its->cmd_lock);
पूर्ण

#घोषणा REGISTER_ITS_DESC(off, rd, wr, length, acc)		\
अणु								\
	.reg_offset = off,					\
	.len = length,						\
	.access_flags = acc,					\
	.its_पढ़ो = rd,						\
	.its_ग_लिखो = wr,					\
पूर्ण

#घोषणा REGISTER_ITS_DESC_UACCESS(off, rd, wr, uwr, length, acc)\
अणु								\
	.reg_offset = off,					\
	.len = length,						\
	.access_flags = acc,					\
	.its_पढ़ो = rd,						\
	.its_ग_लिखो = wr,					\
	.uaccess_its_ग_लिखो = uwr,				\
पूर्ण

अटल व्योम its_mmio_ग_लिखो_wi(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
			      gpa_t addr, अचिन्हित पूर्णांक len, अचिन्हित दीर्घ val)
अणु
	/* Ignore */
पूर्ण

अटल काष्ठा vgic_रेजिस्टर_region its_रेजिस्टरs[] = अणु
	REGISTER_ITS_DESC(GITS_CTLR,
		vgic_mmio_पढ़ो_its_ctlr, vgic_mmio_ग_लिखो_its_ctlr, 4,
		VGIC_ACCESS_32bit),
	REGISTER_ITS_DESC_UACCESS(GITS_IIDR,
		vgic_mmio_पढ़ो_its_iidr, its_mmio_ग_लिखो_wi,
		vgic_mmio_uaccess_ग_लिखो_its_iidr, 4,
		VGIC_ACCESS_32bit),
	REGISTER_ITS_DESC(GITS_TYPER,
		vgic_mmio_पढ़ो_its_typer, its_mmio_ग_लिखो_wi, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	REGISTER_ITS_DESC(GITS_CBASER,
		vgic_mmio_पढ़ो_its_cbaser, vgic_mmio_ग_लिखो_its_cbaser, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	REGISTER_ITS_DESC(GITS_CWRITER,
		vgic_mmio_पढ़ो_its_cग_लिखोr, vgic_mmio_ग_लिखो_its_cग_लिखोr, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	REGISTER_ITS_DESC_UACCESS(GITS_CREADR,
		vgic_mmio_पढ़ो_its_cपढ़ोr, its_mmio_ग_लिखो_wi,
		vgic_mmio_uaccess_ग_लिखो_its_cपढ़ोr, 8,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	REGISTER_ITS_DESC(GITS_BASER,
		vgic_mmio_पढ़ो_its_baser, vgic_mmio_ग_लिखो_its_baser, 0x40,
		VGIC_ACCESS_64bit | VGIC_ACCESS_32bit),
	REGISTER_ITS_DESC(GITS_IDREGS_BASE,
		vgic_mmio_पढ़ो_its_idregs, its_mmio_ग_लिखो_wi, 0x30,
		VGIC_ACCESS_32bit),
पूर्ण;

/* This is called on setting the LPI enable bit in the redistributor. */
व्योम vgic_enable_lpis(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!(vcpu->arch.vgic_cpu.pendbaser & GICR_PENDBASER_PTZ))
		its_sync_lpi_pending_table(vcpu);
पूर्ण

अटल पूर्णांक vgic_रेजिस्टर_its_iodev(काष्ठा kvm *kvm, काष्ठा vgic_its *its,
				   u64 addr)
अणु
	काष्ठा vgic_io_device *iodev = &its->iodev;
	पूर्णांक ret;

	mutex_lock(&kvm->slots_lock);
	अगर (!IS_VGIC_ADDR_UNDEF(its->vgic_its_base)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	its->vgic_its_base = addr;
	iodev->regions = its_रेजिस्टरs;
	iodev->nr_regions = ARRAY_SIZE(its_रेजिस्टरs);
	kvm_iodevice_init(&iodev->dev, &kvm_io_gic_ops);

	iodev->base_addr = its->vgic_its_base;
	iodev->iodev_type = IODEV_ITS;
	iodev->its = its;
	ret = kvm_io_bus_रेजिस्टर_dev(kvm, KVM_MMIO_BUS, iodev->base_addr,
				      KVM_VGIC_V3_ITS_SIZE, &iodev->dev);
out:
	mutex_unlock(&kvm->slots_lock);

	वापस ret;
पूर्ण

/* Default is 16 cached LPIs per vcpu */
#घोषणा LPI_DEFAULT_PCPU_CACHE_SIZE	16

व्योम vgic_lpi_translation_cache_init(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	अचिन्हित पूर्णांक sz;
	पूर्णांक i;

	अगर (!list_empty(&dist->lpi_translation_cache))
		वापस;

	sz = atomic_पढ़ो(&kvm->online_vcpus) * LPI_DEFAULT_PCPU_CACHE_SIZE;

	क्रम (i = 0; i < sz; i++) अणु
		काष्ठा vgic_translation_cache_entry *cte;

		/* An allocation failure is not fatal */
		cte = kzalloc(माप(*cte), GFP_KERNEL);
		अगर (WARN_ON(!cte))
			अवरोध;

		INIT_LIST_HEAD(&cte->entry);
		list_add(&cte->entry, &dist->lpi_translation_cache);
	पूर्ण
पूर्ण

व्योम vgic_lpi_translation_cache_destroy(काष्ठा kvm *kvm)
अणु
	काष्ठा vgic_dist *dist = &kvm->arch.vgic;
	काष्ठा vgic_translation_cache_entry *cte, *पंचांगp;

	vgic_its_invalidate_cache(kvm);

	list_क्रम_each_entry_safe(cte, पंचांगp,
				 &dist->lpi_translation_cache, entry) अणु
		list_del(&cte->entry);
		kमुक्त(cte);
	पूर्ण
पूर्ण

#घोषणा INITIAL_BASER_VALUE						  \
	(GIC_BASER_CACHEABILITY(GITS_BASER, INNER, RaWb)		| \
	 GIC_BASER_CACHEABILITY(GITS_BASER, OUTER, SameAsInner)		| \
	 GIC_BASER_SHAREABILITY(GITS_BASER, InnerShareable)		| \
	 GITS_BASER_PAGE_SIZE_64K)

#घोषणा INITIAL_PROPBASER_VALUE						  \
	(GIC_BASER_CACHEABILITY(GICR_PROPBASER, INNER, RaWb)		| \
	 GIC_BASER_CACHEABILITY(GICR_PROPBASER, OUTER, SameAsInner)	| \
	 GIC_BASER_SHAREABILITY(GICR_PROPBASER, InnerShareable))

अटल पूर्णांक vgic_its_create(काष्ठा kvm_device *dev, u32 type)
अणु
	काष्ठा vgic_its *its;

	अगर (type != KVM_DEV_TYPE_ARM_VGIC_ITS)
		वापस -ENODEV;

	its = kzalloc(माप(काष्ठा vgic_its), GFP_KERNEL);
	अगर (!its)
		वापस -ENOMEM;

	अगर (vgic_initialized(dev->kvm)) अणु
		पूर्णांक ret = vgic_v4_init(dev->kvm);
		अगर (ret < 0) अणु
			kमुक्त(its);
			वापस ret;
		पूर्ण

		vgic_lpi_translation_cache_init(dev->kvm);
	पूर्ण

	mutex_init(&its->its_lock);
	mutex_init(&its->cmd_lock);

	its->vgic_its_base = VGIC_ADDR_UNDEF;

	INIT_LIST_HEAD(&its->device_list);
	INIT_LIST_HEAD(&its->collection_list);

	dev->kvm->arch.vgic.msis_require_devid = true;
	dev->kvm->arch.vgic.has_its = true;
	its->enabled = false;
	its->dev = dev;

	its->baser_device_table = INITIAL_BASER_VALUE			|
		((u64)GITS_BASER_TYPE_DEVICE << GITS_BASER_TYPE_SHIFT);
	its->baser_coll_table = INITIAL_BASER_VALUE |
		((u64)GITS_BASER_TYPE_COLLECTION << GITS_BASER_TYPE_SHIFT);
	dev->kvm->arch.vgic.propbaser = INITIAL_PROPBASER_VALUE;

	dev->निजी = its;

	वापस vgic_its_set_abi(its, NR_ITS_ABIS - 1);
पूर्ण

अटल व्योम vgic_its_destroy(काष्ठा kvm_device *kvm_dev)
अणु
	काष्ठा kvm *kvm = kvm_dev->kvm;
	काष्ठा vgic_its *its = kvm_dev->निजी;

	mutex_lock(&its->its_lock);

	vgic_its_मुक्त_device_list(kvm, its);
	vgic_its_मुक्त_collection_list(kvm, its);

	mutex_unlock(&its->its_lock);
	kमुक्त(its);
	kमुक्त(kvm_dev);/* alloc by kvm_ioctl_create_device, मुक्त by .destroy */
पूर्ण

अटल पूर्णांक vgic_its_has_attr_regs(काष्ठा kvm_device *dev,
				  काष्ठा kvm_device_attr *attr)
अणु
	स्थिर काष्ठा vgic_रेजिस्टर_region *region;
	gpa_t offset = attr->attr;
	पूर्णांक align;

	align = (offset < GITS_TYPER) || (offset >= GITS_PIDR4) ? 0x3 : 0x7;

	अगर (offset & align)
		वापस -EINVAL;

	region = vgic_find_mmio_region(its_रेजिस्टरs,
				       ARRAY_SIZE(its_रेजिस्टरs),
				       offset);
	अगर (!region)
		वापस -ENXIO;

	वापस 0;
पूर्ण

अटल पूर्णांक vgic_its_attr_regs_access(काष्ठा kvm_device *dev,
				     काष्ठा kvm_device_attr *attr,
				     u64 *reg, bool is_ग_लिखो)
अणु
	स्थिर काष्ठा vgic_रेजिस्टर_region *region;
	काष्ठा vgic_its *its;
	gpa_t addr, offset;
	अचिन्हित पूर्णांक len;
	पूर्णांक align, ret = 0;

	its = dev->निजी;
	offset = attr->attr;

	/*
	 * Although the spec supports upper/lower 32-bit accesses to
	 * 64-bit ITS रेजिस्टरs, the userspace ABI requires 64-bit
	 * accesses to all 64-bit wide रेजिस्टरs. We thereक्रमe only
	 * support 32-bit accesses to GITS_CTLR, GITS_IIDR and GITS ID
	 * रेजिस्टरs
	 */
	अगर ((offset < GITS_TYPER) || (offset >= GITS_PIDR4))
		align = 0x3;
	अन्यथा
		align = 0x7;

	अगर (offset & align)
		वापस -EINVAL;

	mutex_lock(&dev->kvm->lock);

	अगर (IS_VGIC_ADDR_UNDEF(its->vgic_its_base)) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	region = vgic_find_mmio_region(its_रेजिस्टरs,
				       ARRAY_SIZE(its_रेजिस्टरs),
				       offset);
	अगर (!region) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	अगर (!lock_all_vcpus(dev->kvm)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	addr = its->vgic_its_base + offset;

	len = region->access_flags & VGIC_ACCESS_64bit ? 8 : 4;

	अगर (is_ग_लिखो) अणु
		अगर (region->uaccess_its_ग_लिखो)
			ret = region->uaccess_its_ग_लिखो(dev->kvm, its, addr,
							len, *reg);
		अन्यथा
			region->its_ग_लिखो(dev->kvm, its, addr, len, *reg);
	पूर्ण अन्यथा अणु
		*reg = region->its_पढ़ो(dev->kvm, its, addr, len);
	पूर्ण
	unlock_all_vcpus(dev->kvm);
out:
	mutex_unlock(&dev->kvm->lock);
	वापस ret;
पूर्ण

अटल u32 compute_next_devid_offset(काष्ठा list_head *h,
				     काष्ठा its_device *dev)
अणु
	काष्ठा its_device *next;
	u32 next_offset;

	अगर (list_is_last(&dev->dev_list, h))
		वापस 0;
	next = list_next_entry(dev, dev_list);
	next_offset = next->device_id - dev->device_id;

	वापस min_t(u32, next_offset, VITS_DTE_MAX_DEVID_OFFSET);
पूर्ण

अटल u32 compute_next_eventid_offset(काष्ठा list_head *h, काष्ठा its_ite *ite)
अणु
	काष्ठा its_ite *next;
	u32 next_offset;

	अगर (list_is_last(&ite->ite_list, h))
		वापस 0;
	next = list_next_entry(ite, ite_list);
	next_offset = next->event_id - ite->event_id;

	वापस min_t(u32, next_offset, VITS_ITE_MAX_EVENTID_OFFSET);
पूर्ण

/**
 * entry_fn_t - Callback called on a table entry restore path
 * @its: its handle
 * @id: id of the entry
 * @entry: poपूर्णांकer to the entry
 * @opaque: poपूर्णांकer to an opaque data
 *
 * Return: < 0 on error, 0 अगर last element was identअगरied, id offset to next
 * element otherwise
 */
प्रकार पूर्णांक (*entry_fn_t)(काष्ठा vgic_its *its, u32 id, व्योम *entry,
			  व्योम *opaque);

/**
 * scan_its_table - Scan a contiguous table in guest RAM and applies a function
 * to each entry
 *
 * @its: its handle
 * @base: base gpa of the table
 * @size: size of the table in bytes
 * @esz: entry size in bytes
 * @start_id: the ID of the first entry in the table
 * (non zero क्रम 2d level tables)
 * @fn: function to apply on each entry
 *
 * Return: < 0 on error, 0 अगर last element was identअगरied, 1 otherwise
 * (the last element may not be found on second level tables)
 */
अटल पूर्णांक scan_its_table(काष्ठा vgic_its *its, gpa_t base, पूर्णांक size, u32 esz,
			  पूर्णांक start_id, entry_fn_t fn, व्योम *opaque)
अणु
	काष्ठा kvm *kvm = its->dev->kvm;
	अचिन्हित दीर्घ len = size;
	पूर्णांक id = start_id;
	gpa_t gpa = base;
	अक्षर entry[ESZ_MAX];
	पूर्णांक ret;

	स_रखो(entry, 0, esz);

	जबतक (len > 0) अणु
		पूर्णांक next_offset;
		माप_प्रकार byte_offset;

		ret = kvm_पढ़ो_guest_lock(kvm, gpa, entry, esz);
		अगर (ret)
			वापस ret;

		next_offset = fn(its, id, entry, opaque);
		अगर (next_offset <= 0)
			वापस next_offset;

		byte_offset = next_offset * esz;
		id += next_offset;
		gpa += byte_offset;
		len -= byte_offset;
	पूर्ण
	वापस 1;
पूर्ण

/**
 * vgic_its_save_ite - Save an पूर्णांकerrupt translation entry at @gpa
 */
अटल पूर्णांक vgic_its_save_ite(काष्ठा vgic_its *its, काष्ठा its_device *dev,
			      काष्ठा its_ite *ite, gpa_t gpa, पूर्णांक ite_esz)
अणु
	काष्ठा kvm *kvm = its->dev->kvm;
	u32 next_offset;
	u64 val;

	next_offset = compute_next_eventid_offset(&dev->itt_head, ite);
	val = ((u64)next_offset << KVM_ITS_ITE_NEXT_SHIFT) |
	       ((u64)ite->irq->पूर्णांकid << KVM_ITS_ITE_PINTID_SHIFT) |
		ite->collection->collection_id;
	val = cpu_to_le64(val);
	वापस kvm_ग_लिखो_guest_lock(kvm, gpa, &val, ite_esz);
पूर्ण

/**
 * vgic_its_restore_ite - restore an पूर्णांकerrupt translation entry
 * @event_id: id used क्रम indexing
 * @ptr: poपूर्णांकer to the ITE entry
 * @opaque: poपूर्णांकer to the its_device
 */
अटल पूर्णांक vgic_its_restore_ite(काष्ठा vgic_its *its, u32 event_id,
				व्योम *ptr, व्योम *opaque)
अणु
	काष्ठा its_device *dev = (काष्ठा its_device *)opaque;
	काष्ठा its_collection *collection;
	काष्ठा kvm *kvm = its->dev->kvm;
	काष्ठा kvm_vcpu *vcpu = शून्य;
	u64 val;
	u64 *p = (u64 *)ptr;
	काष्ठा vgic_irq *irq;
	u32 coll_id, lpi_id;
	काष्ठा its_ite *ite;
	u32 offset;

	val = *p;

	val = le64_to_cpu(val);

	coll_id = val & KVM_ITS_ITE_ICID_MASK;
	lpi_id = (val & KVM_ITS_ITE_PINTID_MASK) >> KVM_ITS_ITE_PINTID_SHIFT;

	अगर (!lpi_id)
		वापस 1; /* invalid entry, no choice but to scan next entry */

	अगर (lpi_id < VGIC_MIN_LPI)
		वापस -EINVAL;

	offset = val >> KVM_ITS_ITE_NEXT_SHIFT;
	अगर (event_id + offset >= BIT_ULL(dev->num_eventid_bits))
		वापस -EINVAL;

	collection = find_collection(its, coll_id);
	अगर (!collection)
		वापस -EINVAL;

	ite = vgic_its_alloc_ite(dev, collection, event_id);
	अगर (IS_ERR(ite))
		वापस PTR_ERR(ite);

	अगर (its_is_collection_mapped(collection))
		vcpu = kvm_get_vcpu(kvm, collection->target_addr);

	irq = vgic_add_lpi(kvm, lpi_id, vcpu);
	अगर (IS_ERR(irq))
		वापस PTR_ERR(irq);
	ite->irq = irq;

	वापस offset;
पूर्ण

अटल पूर्णांक vgic_its_ite_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
			    स्थिर काष्ठा list_head *b)
अणु
	काष्ठा its_ite *itea = container_of(a, काष्ठा its_ite, ite_list);
	काष्ठा its_ite *iteb = container_of(b, काष्ठा its_ite, ite_list);

	अगर (itea->event_id < iteb->event_id)
		वापस -1;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक vgic_its_save_itt(काष्ठा vgic_its *its, काष्ठा its_device *device)
अणु
	स्थिर काष्ठा vgic_its_abi *abi = vgic_its_get_abi(its);
	gpa_t base = device->itt_addr;
	काष्ठा its_ite *ite;
	पूर्णांक ret;
	पूर्णांक ite_esz = abi->ite_esz;

	list_sort(शून्य, &device->itt_head, vgic_its_ite_cmp);

	list_क्रम_each_entry(ite, &device->itt_head, ite_list) अणु
		gpa_t gpa = base + ite->event_id * ite_esz;

		/*
		 * If an LPI carries the HW bit, this means that this
		 * पूर्णांकerrupt is controlled by GICv4, and we करो not
		 * have direct access to that state without GICv4.1.
		 * Let's simply fail the save operation...
		 */
		अगर (ite->irq->hw && !kvm_vgic_global_state.has_gicv4_1)
			वापस -EACCES;

		ret = vgic_its_save_ite(its, device, ite, gpa, ite_esz);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * vgic_its_restore_itt - restore the ITT of a device
 *
 * @its: its handle
 * @dev: device handle
 *
 * Return 0 on success, < 0 on error
 */
अटल पूर्णांक vgic_its_restore_itt(काष्ठा vgic_its *its, काष्ठा its_device *dev)
अणु
	स्थिर काष्ठा vgic_its_abi *abi = vgic_its_get_abi(its);
	gpa_t base = dev->itt_addr;
	पूर्णांक ret;
	पूर्णांक ite_esz = abi->ite_esz;
	माप_प्रकार max_size = BIT_ULL(dev->num_eventid_bits) * ite_esz;

	ret = scan_its_table(its, base, max_size, ite_esz, 0,
			     vgic_its_restore_ite, dev);

	/* scan_its_table वापसs +1 अगर all ITEs are invalid */
	अगर (ret > 0)
		ret = 0;

	वापस ret;
पूर्ण

/**
 * vgic_its_save_dte - Save a device table entry at a given GPA
 *
 * @its: ITS handle
 * @dev: ITS device
 * @ptr: GPA
 */
अटल पूर्णांक vgic_its_save_dte(काष्ठा vgic_its *its, काष्ठा its_device *dev,
			     gpa_t ptr, पूर्णांक dte_esz)
अणु
	काष्ठा kvm *kvm = its->dev->kvm;
	u64 val, itt_addr_field;
	u32 next_offset;

	itt_addr_field = dev->itt_addr >> 8;
	next_offset = compute_next_devid_offset(&its->device_list, dev);
	val = (1ULL << KVM_ITS_DTE_VALID_SHIFT |
	       ((u64)next_offset << KVM_ITS_DTE_NEXT_SHIFT) |
	       (itt_addr_field << KVM_ITS_DTE_ITTADDR_SHIFT) |
		(dev->num_eventid_bits - 1));
	val = cpu_to_le64(val);
	वापस kvm_ग_लिखो_guest_lock(kvm, ptr, &val, dte_esz);
पूर्ण

/**
 * vgic_its_restore_dte - restore a device table entry
 *
 * @its: its handle
 * @id: device id the DTE corresponds to
 * @ptr: kernel VA where the 8 byte DTE is located
 * @opaque: unused
 *
 * Return: < 0 on error, 0 अगर the dte is the last one, id offset to the
 * next dte otherwise
 */
अटल पूर्णांक vgic_its_restore_dte(काष्ठा vgic_its *its, u32 id,
				व्योम *ptr, व्योम *opaque)
अणु
	काष्ठा its_device *dev;
	gpa_t itt_addr;
	u8 num_eventid_bits;
	u64 entry = *(u64 *)ptr;
	bool valid;
	u32 offset;
	पूर्णांक ret;

	entry = le64_to_cpu(entry);

	valid = entry >> KVM_ITS_DTE_VALID_SHIFT;
	num_eventid_bits = (entry & KVM_ITS_DTE_SIZE_MASK) + 1;
	itt_addr = ((entry & KVM_ITS_DTE_ITTADDR_MASK)
			>> KVM_ITS_DTE_ITTADDR_SHIFT) << 8;

	अगर (!valid)
		वापस 1;

	/* dte entry is valid */
	offset = (entry & KVM_ITS_DTE_NEXT_MASK) >> KVM_ITS_DTE_NEXT_SHIFT;

	dev = vgic_its_alloc_device(its, id, itt_addr, num_eventid_bits);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);

	ret = vgic_its_restore_itt(its, dev);
	अगर (ret) अणु
		vgic_its_मुक्त_device(its->dev->kvm, dev);
		वापस ret;
	पूर्ण

	वापस offset;
पूर्ण

अटल पूर्णांक vgic_its_device_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
			       स्थिर काष्ठा list_head *b)
अणु
	काष्ठा its_device *deva = container_of(a, काष्ठा its_device, dev_list);
	काष्ठा its_device *devb = container_of(b, काष्ठा its_device, dev_list);

	अगर (deva->device_id < devb->device_id)
		वापस -1;
	अन्यथा
		वापस 1;
पूर्ण

/**
 * vgic_its_save_device_tables - Save the device table and all ITT
 * पूर्णांकo guest RAM
 *
 * L1/L2 handling is hidden by vgic_its_check_id() helper which directly
 * वापसs the GPA of the device entry
 */
अटल पूर्णांक vgic_its_save_device_tables(काष्ठा vgic_its *its)
अणु
	स्थिर काष्ठा vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 baser = its->baser_device_table;
	काष्ठा its_device *dev;
	पूर्णांक dte_esz = abi->dte_esz;

	अगर (!(baser & GITS_BASER_VALID))
		वापस 0;

	list_sort(शून्य, &its->device_list, vgic_its_device_cmp);

	list_क्रम_each_entry(dev, &its->device_list, dev_list) अणु
		पूर्णांक ret;
		gpa_t eaddr;

		अगर (!vgic_its_check_id(its, baser,
				       dev->device_id, &eaddr))
			वापस -EINVAL;

		ret = vgic_its_save_itt(its, dev);
		अगर (ret)
			वापस ret;

		ret = vgic_its_save_dte(its, dev, eaddr, dte_esz);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * handle_l1_dte - callback used क्रम L1 device table entries (2 stage हाल)
 *
 * @its: its handle
 * @id: index of the entry in the L1 table
 * @addr: kernel VA
 * @opaque: unused
 *
 * L1 table entries are scanned by steps of 1 entry
 * Return < 0 अगर error, 0 अगर last dte was found when scanning the L2
 * table, +1 otherwise (meaning next L1 entry must be scanned)
 */
अटल पूर्णांक handle_l1_dte(काष्ठा vgic_its *its, u32 id, व्योम *addr,
			 व्योम *opaque)
अणु
	स्थिर काष्ठा vgic_its_abi *abi = vgic_its_get_abi(its);
	पूर्णांक l2_start_id = id * (SZ_64K / abi->dte_esz);
	u64 entry = *(u64 *)addr;
	पूर्णांक dte_esz = abi->dte_esz;
	gpa_t gpa;
	पूर्णांक ret;

	entry = le64_to_cpu(entry);

	अगर (!(entry & KVM_ITS_L1E_VALID_MASK))
		वापस 1;

	gpa = entry & KVM_ITS_L1E_ADDR_MASK;

	ret = scan_its_table(its, gpa, SZ_64K, dte_esz,
			     l2_start_id, vgic_its_restore_dte, शून्य);

	वापस ret;
पूर्ण

/**
 * vgic_its_restore_device_tables - Restore the device table and all ITT
 * from guest RAM to पूर्णांकernal data काष्ठाs
 */
अटल पूर्णांक vgic_its_restore_device_tables(काष्ठा vgic_its *its)
अणु
	स्थिर काष्ठा vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 baser = its->baser_device_table;
	पूर्णांक l1_esz, ret;
	पूर्णांक l1_tbl_size = GITS_BASER_NR_PAGES(baser) * SZ_64K;
	gpa_t l1_gpa;

	अगर (!(baser & GITS_BASER_VALID))
		वापस 0;

	l1_gpa = GITS_BASER_ADDR_48_to_52(baser);

	अगर (baser & GITS_BASER_INसूचीECT) अणु
		l1_esz = GITS_LVL1_ENTRY_SIZE;
		ret = scan_its_table(its, l1_gpa, l1_tbl_size, l1_esz, 0,
				     handle_l1_dte, शून्य);
	पूर्ण अन्यथा अणु
		l1_esz = abi->dte_esz;
		ret = scan_its_table(its, l1_gpa, l1_tbl_size, l1_esz, 0,
				     vgic_its_restore_dte, शून्य);
	पूर्ण

	/* scan_its_table वापसs +1 अगर all entries are invalid */
	अगर (ret > 0)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक vgic_its_save_cte(काष्ठा vgic_its *its,
			     काष्ठा its_collection *collection,
			     gpa_t gpa, पूर्णांक esz)
अणु
	u64 val;

	val = (1ULL << KVM_ITS_CTE_VALID_SHIFT |
	       ((u64)collection->target_addr << KVM_ITS_CTE_RDBASE_SHIFT) |
	       collection->collection_id);
	val = cpu_to_le64(val);
	वापस kvm_ग_लिखो_guest_lock(its->dev->kvm, gpa, &val, esz);
पूर्ण

अटल पूर्णांक vgic_its_restore_cte(काष्ठा vgic_its *its, gpa_t gpa, पूर्णांक esz)
अणु
	काष्ठा its_collection *collection;
	काष्ठा kvm *kvm = its->dev->kvm;
	u32 target_addr, coll_id;
	u64 val;
	पूर्णांक ret;

	BUG_ON(esz > माप(val));
	ret = kvm_पढ़ो_guest_lock(kvm, gpa, &val, esz);
	अगर (ret)
		वापस ret;
	val = le64_to_cpu(val);
	अगर (!(val & KVM_ITS_CTE_VALID_MASK))
		वापस 0;

	target_addr = (u32)(val >> KVM_ITS_CTE_RDBASE_SHIFT);
	coll_id = val & KVM_ITS_CTE_ICID_MASK;

	अगर (target_addr != COLLECTION_NOT_MAPPED &&
	    target_addr >= atomic_पढ़ो(&kvm->online_vcpus))
		वापस -EINVAL;

	collection = find_collection(its, coll_id);
	अगर (collection)
		वापस -EEXIST;
	ret = vgic_its_alloc_collection(its, &collection, coll_id);
	अगर (ret)
		वापस ret;
	collection->target_addr = target_addr;
	वापस 1;
पूर्ण

/**
 * vgic_its_save_collection_table - Save the collection table पूर्णांकo
 * guest RAM
 */
अटल पूर्णांक vgic_its_save_collection_table(काष्ठा vgic_its *its)
अणु
	स्थिर काष्ठा vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 baser = its->baser_coll_table;
	gpa_t gpa = GITS_BASER_ADDR_48_to_52(baser);
	काष्ठा its_collection *collection;
	u64 val;
	माप_प्रकार max_size, filled = 0;
	पूर्णांक ret, cte_esz = abi->cte_esz;

	अगर (!(baser & GITS_BASER_VALID))
		वापस 0;

	max_size = GITS_BASER_NR_PAGES(baser) * SZ_64K;

	list_क्रम_each_entry(collection, &its->collection_list, coll_list) अणु
		ret = vgic_its_save_cte(its, collection, gpa, cte_esz);
		अगर (ret)
			वापस ret;
		gpa += cte_esz;
		filled += cte_esz;
	पूर्ण

	अगर (filled == max_size)
		वापस 0;

	/*
	 * table is not fully filled, add a last dummy element
	 * with valid bit unset
	 */
	val = 0;
	BUG_ON(cte_esz > माप(val));
	ret = kvm_ग_लिखो_guest_lock(its->dev->kvm, gpa, &val, cte_esz);
	वापस ret;
पूर्ण

/**
 * vgic_its_restore_collection_table - पढ़ोs the collection table
 * in guest memory and restores the ITS पूर्णांकernal state. Requires the
 * BASER रेजिस्टरs to be restored beक्रमe.
 */
अटल पूर्णांक vgic_its_restore_collection_table(काष्ठा vgic_its *its)
अणु
	स्थिर काष्ठा vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 baser = its->baser_coll_table;
	पूर्णांक cte_esz = abi->cte_esz;
	माप_प्रकार max_size, पढ़ो = 0;
	gpa_t gpa;
	पूर्णांक ret;

	अगर (!(baser & GITS_BASER_VALID))
		वापस 0;

	gpa = GITS_BASER_ADDR_48_to_52(baser);

	max_size = GITS_BASER_NR_PAGES(baser) * SZ_64K;

	जबतक (पढ़ो < max_size) अणु
		ret = vgic_its_restore_cte(its, gpa, cte_esz);
		अगर (ret <= 0)
			अवरोध;
		gpa += cte_esz;
		पढ़ो += cte_esz;
	पूर्ण

	अगर (ret > 0)
		वापस 0;

	वापस ret;
पूर्ण

/**
 * vgic_its_save_tables_v0 - Save the ITS tables पूर्णांकo guest ARM
 * according to v0 ABI
 */
अटल पूर्णांक vgic_its_save_tables_v0(काष्ठा vgic_its *its)
अणु
	पूर्णांक ret;

	ret = vgic_its_save_device_tables(its);
	अगर (ret)
		वापस ret;

	वापस vgic_its_save_collection_table(its);
पूर्ण

/**
 * vgic_its_restore_tables_v0 - Restore the ITS tables from guest RAM
 * to पूर्णांकernal data काष्ठाs according to V0 ABI
 *
 */
अटल पूर्णांक vgic_its_restore_tables_v0(काष्ठा vgic_its *its)
अणु
	पूर्णांक ret;

	ret = vgic_its_restore_collection_table(its);
	अगर (ret)
		वापस ret;

	वापस vgic_its_restore_device_tables(its);
पूर्ण

अटल पूर्णांक vgic_its_commit_v0(काष्ठा vgic_its *its)
अणु
	स्थिर काष्ठा vgic_its_abi *abi;

	abi = vgic_its_get_abi(its);
	its->baser_coll_table &= ~GITS_BASER_ENTRY_SIZE_MASK;
	its->baser_device_table &= ~GITS_BASER_ENTRY_SIZE_MASK;

	its->baser_coll_table |= (GIC_ENCODE_SZ(abi->cte_esz, 5)
					<< GITS_BASER_ENTRY_SIZE_SHIFT);

	its->baser_device_table |= (GIC_ENCODE_SZ(abi->dte_esz, 5)
					<< GITS_BASER_ENTRY_SIZE_SHIFT);
	वापस 0;
पूर्ण

अटल व्योम vgic_its_reset(काष्ठा kvm *kvm, काष्ठा vgic_its *its)
अणु
	/* We need to keep the ABI specअगरic field values */
	its->baser_coll_table &= ~GITS_BASER_VALID;
	its->baser_device_table &= ~GITS_BASER_VALID;
	its->cbaser = 0;
	its->cपढ़ोr = 0;
	its->cग_लिखोr = 0;
	its->enabled = 0;
	vgic_its_मुक्त_device_list(kvm, its);
	vgic_its_मुक्त_collection_list(kvm, its);
पूर्ण

अटल पूर्णांक vgic_its_has_attr(काष्ठा kvm_device *dev,
			     काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_ADDR:
		चयन (attr->attr) अणु
		हाल KVM_VGIC_ITS_ADDR_TYPE:
			वापस 0;
		पूर्ण
		अवरोध;
	हाल KVM_DEV_ARM_VGIC_GRP_CTRL:
		चयन (attr->attr) अणु
		हाल KVM_DEV_ARM_VGIC_CTRL_INIT:
			वापस 0;
		हाल KVM_DEV_ARM_ITS_CTRL_RESET:
			वापस 0;
		हाल KVM_DEV_ARM_ITS_SAVE_TABLES:
			वापस 0;
		हाल KVM_DEV_ARM_ITS_RESTORE_TABLES:
			वापस 0;
		पूर्ण
		अवरोध;
	हाल KVM_DEV_ARM_VGIC_GRP_ITS_REGS:
		वापस vgic_its_has_attr_regs(dev, attr);
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक vgic_its_ctrl(काष्ठा kvm *kvm, काष्ठा vgic_its *its, u64 attr)
अणु
	स्थिर काष्ठा vgic_its_abi *abi = vgic_its_get_abi(its);
	पूर्णांक ret = 0;

	अगर (attr == KVM_DEV_ARM_VGIC_CTRL_INIT) /* Nothing to करो */
		वापस 0;

	mutex_lock(&kvm->lock);
	mutex_lock(&its->its_lock);

	अगर (!lock_all_vcpus(kvm)) अणु
		mutex_unlock(&its->its_lock);
		mutex_unlock(&kvm->lock);
		वापस -EBUSY;
	पूर्ण

	चयन (attr) अणु
	हाल KVM_DEV_ARM_ITS_CTRL_RESET:
		vgic_its_reset(kvm, its);
		अवरोध;
	हाल KVM_DEV_ARM_ITS_SAVE_TABLES:
		ret = abi->save_tables(its);
		अवरोध;
	हाल KVM_DEV_ARM_ITS_RESTORE_TABLES:
		ret = abi->restore_tables(its);
		अवरोध;
	पूर्ण

	unlock_all_vcpus(kvm);
	mutex_unlock(&its->its_lock);
	mutex_unlock(&kvm->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vgic_its_set_attr(काष्ठा kvm_device *dev,
			     काष्ठा kvm_device_attr *attr)
अणु
	काष्ठा vgic_its *its = dev->निजी;
	पूर्णांक ret;

	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_ADDR: अणु
		u64 __user *uaddr = (u64 __user *)(दीर्घ)attr->addr;
		अचिन्हित दीर्घ type = (अचिन्हित दीर्घ)attr->attr;
		u64 addr;

		अगर (type != KVM_VGIC_ITS_ADDR_TYPE)
			वापस -ENODEV;

		अगर (copy_from_user(&addr, uaddr, माप(addr)))
			वापस -EFAULT;

		ret = vgic_check_ioaddr(dev->kvm, &its->vgic_its_base,
					addr, SZ_64K);
		अगर (ret)
			वापस ret;

		वापस vgic_रेजिस्टर_its_iodev(dev->kvm, its, addr);
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_CTRL:
		वापस vgic_its_ctrl(dev->kvm, its, attr->attr);
	हाल KVM_DEV_ARM_VGIC_GRP_ITS_REGS: अणु
		u64 __user *uaddr = (u64 __user *)(दीर्घ)attr->addr;
		u64 reg;

		अगर (get_user(reg, uaddr))
			वापस -EFAULT;

		वापस vgic_its_attr_regs_access(dev, attr, &reg, true);
	पूर्ण
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक vgic_its_get_attr(काष्ठा kvm_device *dev,
			     काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_ADDR: अणु
		काष्ठा vgic_its *its = dev->निजी;
		u64 addr = its->vgic_its_base;
		u64 __user *uaddr = (u64 __user *)(दीर्घ)attr->addr;
		अचिन्हित दीर्घ type = (अचिन्हित दीर्घ)attr->attr;

		अगर (type != KVM_VGIC_ITS_ADDR_TYPE)
			वापस -ENODEV;

		अगर (copy_to_user(uaddr, &addr, माप(addr)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_ITS_REGS: अणु
		u64 __user *uaddr = (u64 __user *)(दीर्घ)attr->addr;
		u64 reg;
		पूर्णांक ret;

		ret = vgic_its_attr_regs_access(dev, attr, &reg, false);
		अगर (ret)
			वापस ret;
		वापस put_user(reg, uaddr);
	पूर्ण
	शेष:
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा kvm_device_ops kvm_arm_vgic_its_ops = अणु
	.name = "kvm-arm-vgic-its",
	.create = vgic_its_create,
	.destroy = vgic_its_destroy,
	.set_attr = vgic_its_set_attr,
	.get_attr = vgic_its_get_attr,
	.has_attr = vgic_its_has_attr,
पूर्ण;

पूर्णांक kvm_vgic_रेजिस्टर_its_device(व्योम)
अणु
	वापस kvm_रेजिस्टर_device_ops(&kvm_arm_vgic_its_ops,
				       KVM_DEV_TYPE_ARM_VGIC_ITS);
पूर्ण
