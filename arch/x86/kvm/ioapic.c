<शैली गुरु>
/*
 *  Copyright (C) 2001  MandrakeSoft S.A.
 *  Copyright 2010 Red Hat, Inc. and/or its affiliates.
 *
 *    MandrakeSoft S.A.
 *    43, rue d'Aboukir
 *    75002 Paris - France
 *    http://www.linux-mandrake.com/
 *    http://www.mandrakesoft.com/
 *
 *  This library is मुक्त software; you can redistribute it and/or
 *  modअगरy it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 *  Yunhong Jiang <yunhong.jiang@पूर्णांकel.com>
 *  Yaozu (Eddie) Dong <eddie.करोng@पूर्णांकel.com>
 *  Based on Xen 3.1 code.
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/kvm.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/smp.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/nospec.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/current.h>
#समावेश <trace/events/kvm.h>

#समावेश "ioapic.h"
#समावेश "lapic.h"
#समावेश "irq.h"

अटल पूर्णांक ioapic_service(काष्ठा kvm_ioapic *vioapic, पूर्णांक irq,
		bool line_status);

अटल व्योम kvm_ioapic_update_eoi_one(काष्ठा kvm_vcpu *vcpu,
				      काष्ठा kvm_ioapic *ioapic,
				      पूर्णांक trigger_mode,
				      पूर्णांक pin);

अटल अचिन्हित दीर्घ ioapic_पढ़ो_indirect(काष्ठा kvm_ioapic *ioapic,
					  अचिन्हित दीर्घ addr,
					  अचिन्हित दीर्घ length)
अणु
	अचिन्हित दीर्घ result = 0;

	चयन (ioapic->ioregsel) अणु
	हाल IOAPIC_REG_VERSION:
		result = ((((IOAPIC_NUM_PINS - 1) & 0xff) << 16)
			  | (IOAPIC_VERSION_ID & 0xff));
		अवरोध;

	हाल IOAPIC_REG_APIC_ID:
	हाल IOAPIC_REG_ARB_ID:
		result = ((ioapic->id & 0xf) << 24);
		अवरोध;

	शेष:
		अणु
			u32 redir_index = (ioapic->ioregsel - 0x10) >> 1;
			u64 redir_content = ~0ULL;

			अगर (redir_index < IOAPIC_NUM_PINS) अणु
				u32 index = array_index_nospec(
					redir_index, IOAPIC_NUM_PINS);

				redir_content = ioapic->redirtbl[index].bits;
			पूर्ण

			result = (ioapic->ioregsel & 0x1) ?
			    (redir_content >> 32) & 0xffffffff :
			    redir_content & 0xffffffff;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम rtc_irq_eoi_tracking_reset(काष्ठा kvm_ioapic *ioapic)
अणु
	ioapic->rtc_status.pending_eoi = 0;
	biपंचांगap_zero(ioapic->rtc_status.dest_map.map, KVM_MAX_VCPU_ID);
पूर्ण

अटल व्योम kvm_rtc_eoi_tracking_restore_all(काष्ठा kvm_ioapic *ioapic);

अटल व्योम rtc_status_pending_eoi_check_valid(काष्ठा kvm_ioapic *ioapic)
अणु
	अगर (WARN_ON(ioapic->rtc_status.pending_eoi < 0))
		kvm_rtc_eoi_tracking_restore_all(ioapic);
पूर्ण

अटल व्योम __rtc_irq_eoi_tracking_restore_one(काष्ठा kvm_vcpu *vcpu)
अणु
	bool new_val, old_val;
	काष्ठा kvm_ioapic *ioapic = vcpu->kvm->arch.vioapic;
	काष्ठा dest_map *dest_map = &ioapic->rtc_status.dest_map;
	जोड़ kvm_ioapic_redirect_entry *e;

	e = &ioapic->redirtbl[RTC_GSI];
	अगर (!kvm_apic_match_dest(vcpu, शून्य, APIC_DEST_NOSHORT,
				 e->fields.dest_id,
				 kvm_lapic_irq_dest_mode(!!e->fields.dest_mode)))
		वापस;

	new_val = kvm_apic_pending_eoi(vcpu, e->fields.vector);
	old_val = test_bit(vcpu->vcpu_id, dest_map->map);

	अगर (new_val == old_val)
		वापस;

	अगर (new_val) अणु
		__set_bit(vcpu->vcpu_id, dest_map->map);
		dest_map->vectors[vcpu->vcpu_id] = e->fields.vector;
		ioapic->rtc_status.pending_eoi++;
	पूर्ण अन्यथा अणु
		__clear_bit(vcpu->vcpu_id, dest_map->map);
		ioapic->rtc_status.pending_eoi--;
		rtc_status_pending_eoi_check_valid(ioapic);
	पूर्ण
पूर्ण

व्योम kvm_rtc_eoi_tracking_restore_one(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_ioapic *ioapic = vcpu->kvm->arch.vioapic;

	spin_lock(&ioapic->lock);
	__rtc_irq_eoi_tracking_restore_one(vcpu);
	spin_unlock(&ioapic->lock);
पूर्ण

अटल व्योम kvm_rtc_eoi_tracking_restore_all(काष्ठा kvm_ioapic *ioapic)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	अगर (RTC_GSI >= IOAPIC_NUM_PINS)
		वापस;

	rtc_irq_eoi_tracking_reset(ioapic);
	kvm_क्रम_each_vcpu(i, vcpu, ioapic->kvm)
	    __rtc_irq_eoi_tracking_restore_one(vcpu);
पूर्ण

अटल व्योम rtc_irq_eoi(काष्ठा kvm_ioapic *ioapic, काष्ठा kvm_vcpu *vcpu,
			पूर्णांक vector)
अणु
	काष्ठा dest_map *dest_map = &ioapic->rtc_status.dest_map;

	/* RTC special handling */
	अगर (test_bit(vcpu->vcpu_id, dest_map->map) &&
	    (vector == dest_map->vectors[vcpu->vcpu_id]) &&
	    (test_and_clear_bit(vcpu->vcpu_id,
				ioapic->rtc_status.dest_map.map))) अणु
		--ioapic->rtc_status.pending_eoi;
		rtc_status_pending_eoi_check_valid(ioapic);
	पूर्ण
पूर्ण

अटल bool rtc_irq_check_coalesced(काष्ठा kvm_ioapic *ioapic)
अणु
	अगर (ioapic->rtc_status.pending_eoi > 0)
		वापस true; /* coalesced */

	वापस false;
पूर्ण

अटल व्योम ioapic_lazy_update_eoi(काष्ठा kvm_ioapic *ioapic, पूर्णांक irq)
अणु
	पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;
	जोड़ kvm_ioapic_redirect_entry *entry = &ioapic->redirtbl[irq];

	kvm_क्रम_each_vcpu(i, vcpu, ioapic->kvm) अणु
		अगर (!kvm_apic_match_dest(vcpu, शून्य, APIC_DEST_NOSHORT,
					 entry->fields.dest_id,
					 entry->fields.dest_mode) ||
		    kvm_apic_pending_eoi(vcpu, entry->fields.vector))
			जारी;

		/*
		 * If no दीर्घer has pending EOI in LAPICs, update
		 * EOI क्रम this vector.
		 */
		rtc_irq_eoi(ioapic, vcpu, entry->fields.vector);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ioapic_set_irq(काष्ठा kvm_ioapic *ioapic, अचिन्हित पूर्णांक irq,
		पूर्णांक irq_level, bool line_status)
अणु
	जोड़ kvm_ioapic_redirect_entry entry;
	u32 mask = 1 << irq;
	u32 old_irr;
	पूर्णांक edge, ret;

	entry = ioapic->redirtbl[irq];
	edge = (entry.fields.trig_mode == IOAPIC_EDGE_TRIG);

	अगर (!irq_level) अणु
		ioapic->irr &= ~mask;
		ret = 1;
		जाओ out;
	पूर्ण

	/*
	 * AMD SVM AVIC accelerate EOI ग_लिखो अगरf the पूर्णांकerrupt is edge
	 * triggered, in which हाल the in-kernel IOAPIC will not be able
	 * to receive the EOI.  In this हाल, we करो a lazy update of the
	 * pending EOI when trying to set IOAPIC irq.
	 */
	अगर (edge && kvm_apicv_activated(ioapic->kvm))
		ioapic_lazy_update_eoi(ioapic, irq);

	/*
	 * Return 0 क्रम coalesced पूर्णांकerrupts; क्रम edge-triggered पूर्णांकerrupts,
	 * this only happens अगर a previous edge has not been delivered due
	 * to masking.  For level पूर्णांकerrupts, the remote_irr field tells
	 * us अगर the पूर्णांकerrupt is रुकोing क्रम an EOI.
	 *
	 * RTC is special: it is edge-triggered, but userspace likes to know
	 * अगर it has been alपढ़ोy ack-ed via EOI because coalesced RTC
	 * पूर्णांकerrupts lead to समय drअगरt in Winकरोws guests.  So we track
	 * EOI manually क्रम the RTC पूर्णांकerrupt.
	 */
	अगर (irq == RTC_GSI && line_status &&
		rtc_irq_check_coalesced(ioapic)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	old_irr = ioapic->irr;
	ioapic->irr |= mask;
	अगर (edge) अणु
		ioapic->irr_delivered &= ~mask;
		अगर (old_irr == ioapic->irr) अणु
			ret = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ioapic_service(ioapic, irq, line_status);

out:
	trace_kvm_ioapic_set_irq(entry.bits, irq, ret == 0);
	वापस ret;
पूर्ण

अटल व्योम kvm_ioapic_inject_all(काष्ठा kvm_ioapic *ioapic, अचिन्हित दीर्घ irr)
अणु
	u32 idx;

	rtc_irq_eoi_tracking_reset(ioapic);
	क्रम_each_set_bit(idx, &irr, IOAPIC_NUM_PINS)
		ioapic_set_irq(ioapic, idx, 1, true);

	kvm_rtc_eoi_tracking_restore_all(ioapic);
पूर्ण


व्योम kvm_ioapic_scan_entry(काष्ठा kvm_vcpu *vcpu, uदीर्घ *ioapic_handled_vectors)
अणु
	काष्ठा kvm_ioapic *ioapic = vcpu->kvm->arch.vioapic;
	काष्ठा dest_map *dest_map = &ioapic->rtc_status.dest_map;
	जोड़ kvm_ioapic_redirect_entry *e;
	पूर्णांक index;

	spin_lock(&ioapic->lock);

	/* Make sure we see any missing RTC EOI */
	अगर (test_bit(vcpu->vcpu_id, dest_map->map))
		__set_bit(dest_map->vectors[vcpu->vcpu_id],
			  ioapic_handled_vectors);

	क्रम (index = 0; index < IOAPIC_NUM_PINS; index++) अणु
		e = &ioapic->redirtbl[index];
		अगर (e->fields.trig_mode == IOAPIC_LEVEL_TRIG ||
		    kvm_irq_has_notअगरier(ioapic->kvm, KVM_IRQCHIP_IOAPIC, index) ||
		    index == RTC_GSI) अणु
			u16 dm = kvm_lapic_irq_dest_mode(!!e->fields.dest_mode);

			अगर (kvm_apic_match_dest(vcpu, शून्य, APIC_DEST_NOSHORT,
						e->fields.dest_id, dm) ||
			    kvm_apic_pending_eoi(vcpu, e->fields.vector))
				__set_bit(e->fields.vector,
					  ioapic_handled_vectors);
		पूर्ण
	पूर्ण
	spin_unlock(&ioapic->lock);
पूर्ण

व्योम kvm_arch_post_irq_ack_notअगरier_list_update(काष्ठा kvm *kvm)
अणु
	अगर (!ioapic_in_kernel(kvm))
		वापस;
	kvm_make_scan_ioapic_request(kvm);
पूर्ण

अटल व्योम ioapic_ग_लिखो_indirect(काष्ठा kvm_ioapic *ioapic, u32 val)
अणु
	अचिन्हित index;
	bool mask_beक्रमe, mask_after;
	जोड़ kvm_ioapic_redirect_entry *e;
	अचिन्हित दीर्घ vcpu_biपंचांगap;
	पूर्णांक old_remote_irr, old_delivery_status, old_dest_id, old_dest_mode;

	चयन (ioapic->ioregsel) अणु
	हाल IOAPIC_REG_VERSION:
		/* Writes are ignored. */
		अवरोध;

	हाल IOAPIC_REG_APIC_ID:
		ioapic->id = (val >> 24) & 0xf;
		अवरोध;

	हाल IOAPIC_REG_ARB_ID:
		अवरोध;

	शेष:
		index = (ioapic->ioregsel - 0x10) >> 1;

		अगर (index >= IOAPIC_NUM_PINS)
			वापस;
		index = array_index_nospec(index, IOAPIC_NUM_PINS);
		e = &ioapic->redirtbl[index];
		mask_beक्रमe = e->fields.mask;
		/* Preserve पढ़ो-only fields */
		old_remote_irr = e->fields.remote_irr;
		old_delivery_status = e->fields.delivery_status;
		old_dest_id = e->fields.dest_id;
		old_dest_mode = e->fields.dest_mode;
		अगर (ioapic->ioregsel & 1) अणु
			e->bits &= 0xffffffff;
			e->bits |= (u64) val << 32;
		पूर्ण अन्यथा अणु
			e->bits &= ~0xffffffffULL;
			e->bits |= (u32) val;
		पूर्ण
		e->fields.remote_irr = old_remote_irr;
		e->fields.delivery_status = old_delivery_status;

		/*
		 * Some OSes (Linux, Xen) assume that Remote IRR bit will
		 * be cleared by IOAPIC hardware when the entry is configured
		 * as edge-triggered. This behavior is used to simulate an
		 * explicit EOI on IOAPICs that करोn't have the EOI रेजिस्टर.
		 */
		अगर (e->fields.trig_mode == IOAPIC_EDGE_TRIG)
			e->fields.remote_irr = 0;

		mask_after = e->fields.mask;
		अगर (mask_beक्रमe != mask_after)
			kvm_fire_mask_notअगरiers(ioapic->kvm, KVM_IRQCHIP_IOAPIC, index, mask_after);
		अगर (e->fields.trig_mode == IOAPIC_LEVEL_TRIG
		    && ioapic->irr & (1 << index))
			ioapic_service(ioapic, index, false);
		अगर (e->fields.delivery_mode == APIC_DM_FIXED) अणु
			काष्ठा kvm_lapic_irq irq;

			irq.vector = e->fields.vector;
			irq.delivery_mode = e->fields.delivery_mode << 8;
			irq.dest_mode =
			    kvm_lapic_irq_dest_mode(!!e->fields.dest_mode);
			irq.level = false;
			irq.trig_mode = e->fields.trig_mode;
			irq.लघुhand = APIC_DEST_NOSHORT;
			irq.dest_id = e->fields.dest_id;
			irq.msi_redir_hपूर्णांक = false;
			biपंचांगap_zero(&vcpu_biपंचांगap, 16);
			kvm_biपंचांगap_or_dest_vcpus(ioapic->kvm, &irq,
						 &vcpu_biपंचांगap);
			अगर (old_dest_mode != e->fields.dest_mode ||
			    old_dest_id != e->fields.dest_id) अणु
				/*
				 * Update vcpu_biपंचांगap with vcpus specअगरied in
				 * the previous request as well. This is करोne to
				 * keep ioapic_handled_vectors synchronized.
				 */
				irq.dest_id = old_dest_id;
				irq.dest_mode =
				    kvm_lapic_irq_dest_mode(
					!!e->fields.dest_mode);
				kvm_biपंचांगap_or_dest_vcpus(ioapic->kvm, &irq,
							 &vcpu_biपंचांगap);
			पूर्ण
			kvm_make_scan_ioapic_request_mask(ioapic->kvm,
							  &vcpu_biपंचांगap);
		पूर्ण अन्यथा अणु
			kvm_make_scan_ioapic_request(ioapic->kvm);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ioapic_service(काष्ठा kvm_ioapic *ioapic, पूर्णांक irq, bool line_status)
अणु
	जोड़ kvm_ioapic_redirect_entry *entry = &ioapic->redirtbl[irq];
	काष्ठा kvm_lapic_irq irqe;
	पूर्णांक ret;

	अगर (entry->fields.mask ||
	    (entry->fields.trig_mode == IOAPIC_LEVEL_TRIG &&
	    entry->fields.remote_irr))
		वापस -1;

	irqe.dest_id = entry->fields.dest_id;
	irqe.vector = entry->fields.vector;
	irqe.dest_mode = kvm_lapic_irq_dest_mode(!!entry->fields.dest_mode);
	irqe.trig_mode = entry->fields.trig_mode;
	irqe.delivery_mode = entry->fields.delivery_mode << 8;
	irqe.level = 1;
	irqe.लघुhand = APIC_DEST_NOSHORT;
	irqe.msi_redir_hपूर्णांक = false;

	अगर (irqe.trig_mode == IOAPIC_EDGE_TRIG)
		ioapic->irr_delivered |= 1 << irq;

	अगर (irq == RTC_GSI && line_status) अणु
		/*
		 * pending_eoi cannot ever become negative (see
		 * rtc_status_pending_eoi_check_valid) and the caller
		 * ensures that it is only called अगर it is >= zero, namely
		 * अगर rtc_irq_check_coalesced वापसs false).
		 */
		BUG_ON(ioapic->rtc_status.pending_eoi != 0);
		ret = kvm_irq_delivery_to_apic(ioapic->kvm, शून्य, &irqe,
					       &ioapic->rtc_status.dest_map);
		ioapic->rtc_status.pending_eoi = (ret < 0 ? 0 : ret);
	पूर्ण अन्यथा
		ret = kvm_irq_delivery_to_apic(ioapic->kvm, शून्य, &irqe, शून्य);

	अगर (ret && irqe.trig_mode == IOAPIC_LEVEL_TRIG)
		entry->fields.remote_irr = 1;

	वापस ret;
पूर्ण

पूर्णांक kvm_ioapic_set_irq(काष्ठा kvm_ioapic *ioapic, पूर्णांक irq, पूर्णांक irq_source_id,
		       पूर्णांक level, bool line_status)
अणु
	पूर्णांक ret, irq_level;

	BUG_ON(irq < 0 || irq >= IOAPIC_NUM_PINS);

	spin_lock(&ioapic->lock);
	irq_level = __kvm_irq_line_state(&ioapic->irq_states[irq],
					 irq_source_id, level);
	ret = ioapic_set_irq(ioapic, irq, irq_level, line_status);

	spin_unlock(&ioapic->lock);

	वापस ret;
पूर्ण

व्योम kvm_ioapic_clear_all(काष्ठा kvm_ioapic *ioapic, पूर्णांक irq_source_id)
अणु
	पूर्णांक i;

	spin_lock(&ioapic->lock);
	क्रम (i = 0; i < KVM_IOAPIC_NUM_PINS; i++)
		__clear_bit(irq_source_id, &ioapic->irq_states[i]);
	spin_unlock(&ioapic->lock);
पूर्ण

अटल व्योम kvm_ioapic_eoi_inject_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक i;
	काष्ठा kvm_ioapic *ioapic = container_of(work, काष्ठा kvm_ioapic,
						 eoi_inject.work);
	spin_lock(&ioapic->lock);
	क्रम (i = 0; i < IOAPIC_NUM_PINS; i++) अणु
		जोड़ kvm_ioapic_redirect_entry *ent = &ioapic->redirtbl[i];

		अगर (ent->fields.trig_mode != IOAPIC_LEVEL_TRIG)
			जारी;

		अगर (ioapic->irr & (1 << i) && !ent->fields.remote_irr)
			ioapic_service(ioapic, i, false);
	पूर्ण
	spin_unlock(&ioapic->lock);
पूर्ण

#घोषणा IOAPIC_SUCCESSIVE_IRQ_MAX_COUNT 10000
अटल व्योम kvm_ioapic_update_eoi_one(काष्ठा kvm_vcpu *vcpu,
				      काष्ठा kvm_ioapic *ioapic,
				      पूर्णांक trigger_mode,
				      पूर्णांक pin)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	जोड़ kvm_ioapic_redirect_entry *ent = &ioapic->redirtbl[pin];

	/*
	 * We are dropping lock जबतक calling ack notअगरiers because ack
	 * notअगरier callbacks क्रम asचिन्हित devices call पूर्णांकo IOAPIC
	 * recursively. Since remote_irr is cleared only after call
	 * to notअगरiers अगर the same vector will be delivered जबतक lock
	 * is dropped it will be put पूर्णांकo irr and will be delivered
	 * after ack notअगरier वापसs.
	 */
	spin_unlock(&ioapic->lock);
	kvm_notअगरy_acked_irq(ioapic->kvm, KVM_IRQCHIP_IOAPIC, pin);
	spin_lock(&ioapic->lock);

	अगर (trigger_mode != IOAPIC_LEVEL_TRIG ||
	    kvm_lapic_get_reg(apic, APIC_SPIV) & APIC_SPIV_सूचीECTED_EOI)
		वापस;

	ASSERT(ent->fields.trig_mode == IOAPIC_LEVEL_TRIG);
	ent->fields.remote_irr = 0;
	अगर (!ent->fields.mask && (ioapic->irr & (1 << pin))) अणु
		++ioapic->irq_eoi[pin];
		अगर (ioapic->irq_eoi[pin] == IOAPIC_SUCCESSIVE_IRQ_MAX_COUNT) अणु
			/*
			 * Real hardware करोes not deliver the पूर्णांकerrupt
			 * immediately during eoi broadcast, and this
			 * lets a buggy guest make slow progress
			 * even अगर it करोes not correctly handle a
			 * level-triggered पूर्णांकerrupt.  Emulate this
			 * behavior अगर we detect an पूर्णांकerrupt storm.
			 */
			schedule_delayed_work(&ioapic->eoi_inject, HZ / 100);
			ioapic->irq_eoi[pin] = 0;
			trace_kvm_ioapic_delayed_eoi_inj(ent->bits);
		पूर्ण अन्यथा अणु
			ioapic_service(ioapic, pin, false);
		पूर्ण
	पूर्ण अन्यथा अणु
		ioapic->irq_eoi[pin] = 0;
	पूर्ण
पूर्ण

व्योम kvm_ioapic_update_eoi(काष्ठा kvm_vcpu *vcpu, पूर्णांक vector, पूर्णांक trigger_mode)
अणु
	पूर्णांक i;
	काष्ठा kvm_ioapic *ioapic = vcpu->kvm->arch.vioapic;

	spin_lock(&ioapic->lock);
	rtc_irq_eoi(ioapic, vcpu, vector);
	क्रम (i = 0; i < IOAPIC_NUM_PINS; i++) अणु
		जोड़ kvm_ioapic_redirect_entry *ent = &ioapic->redirtbl[i];

		अगर (ent->fields.vector != vector)
			जारी;
		kvm_ioapic_update_eoi_one(vcpu, ioapic, trigger_mode, i);
	पूर्ण
	spin_unlock(&ioapic->lock);
पूर्ण

अटल अंतरभूत काष्ठा kvm_ioapic *to_ioapic(काष्ठा kvm_io_device *dev)
अणु
	वापस container_of(dev, काष्ठा kvm_ioapic, dev);
पूर्ण

अटल अंतरभूत पूर्णांक ioapic_in_range(काष्ठा kvm_ioapic *ioapic, gpa_t addr)
अणु
	वापस ((addr >= ioapic->base_address &&
		 (addr < ioapic->base_address + IOAPIC_MEM_LENGTH)));
पूर्ण

अटल पूर्णांक ioapic_mmio_पढ़ो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *this,
				gpa_t addr, पूर्णांक len, व्योम *val)
अणु
	काष्ठा kvm_ioapic *ioapic = to_ioapic(this);
	u32 result;
	अगर (!ioapic_in_range(ioapic, addr))
		वापस -EOPNOTSUPP;

	ASSERT(!(addr & 0xf));	/* check alignment */

	addr &= 0xff;
	spin_lock(&ioapic->lock);
	चयन (addr) अणु
	हाल IOAPIC_REG_SELECT:
		result = ioapic->ioregsel;
		अवरोध;

	हाल IOAPIC_REG_WINDOW:
		result = ioapic_पढ़ो_indirect(ioapic, addr, len);
		अवरोध;

	शेष:
		result = 0;
		अवरोध;
	पूर्ण
	spin_unlock(&ioapic->lock);

	चयन (len) अणु
	हाल 8:
		*(u64 *) val = result;
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 4:
		स_नकल(val, (अक्षर *)&result, len);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "ioapic: wrong length %d\n", len);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ioapic_mmio_ग_लिखो(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_io_device *this,
				 gpa_t addr, पूर्णांक len, स्थिर व्योम *val)
अणु
	काष्ठा kvm_ioapic *ioapic = to_ioapic(this);
	u32 data;
	अगर (!ioapic_in_range(ioapic, addr))
		वापस -EOPNOTSUPP;

	ASSERT(!(addr & 0xf));	/* check alignment */

	चयन (len) अणु
	हाल 8:
	हाल 4:
		data = *(u32 *) val;
		अवरोध;
	हाल 2:
		data = *(u16 *) val;
		अवरोध;
	हाल 1:
		data = *(u8  *) val;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "ioapic: Unsupported size %d\n", len);
		वापस 0;
	पूर्ण

	addr &= 0xff;
	spin_lock(&ioapic->lock);
	चयन (addr) अणु
	हाल IOAPIC_REG_SELECT:
		ioapic->ioregsel = data & 0xFF; /* 8-bit रेजिस्टर */
		अवरोध;

	हाल IOAPIC_REG_WINDOW:
		ioapic_ग_लिखो_indirect(ioapic, data);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	spin_unlock(&ioapic->lock);
	वापस 0;
पूर्ण

अटल व्योम kvm_ioapic_reset(काष्ठा kvm_ioapic *ioapic)
अणु
	पूर्णांक i;

	cancel_delayed_work_sync(&ioapic->eoi_inject);
	क्रम (i = 0; i < IOAPIC_NUM_PINS; i++)
		ioapic->redirtbl[i].fields.mask = 1;
	ioapic->base_address = IOAPIC_DEFAULT_BASE_ADDRESS;
	ioapic->ioregsel = 0;
	ioapic->irr = 0;
	ioapic->irr_delivered = 0;
	ioapic->id = 0;
	स_रखो(ioapic->irq_eoi, 0x00, माप(ioapic->irq_eoi));
	rtc_irq_eoi_tracking_reset(ioapic);
पूर्ण

अटल स्थिर काष्ठा kvm_io_device_ops ioapic_mmio_ops = अणु
	.पढ़ो     = ioapic_mmio_पढ़ो,
	.ग_लिखो    = ioapic_mmio_ग_लिखो,
पूर्ण;

पूर्णांक kvm_ioapic_init(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_ioapic *ioapic;
	पूर्णांक ret;

	ioapic = kzalloc(माप(काष्ठा kvm_ioapic), GFP_KERNEL_ACCOUNT);
	अगर (!ioapic)
		वापस -ENOMEM;
	spin_lock_init(&ioapic->lock);
	INIT_DELAYED_WORK(&ioapic->eoi_inject, kvm_ioapic_eoi_inject_work);
	kvm->arch.vioapic = ioapic;
	kvm_ioapic_reset(ioapic);
	kvm_iodevice_init(&ioapic->dev, &ioapic_mmio_ops);
	ioapic->kvm = kvm;
	mutex_lock(&kvm->slots_lock);
	ret = kvm_io_bus_रेजिस्टर_dev(kvm, KVM_MMIO_BUS, ioapic->base_address,
				      IOAPIC_MEM_LENGTH, &ioapic->dev);
	mutex_unlock(&kvm->slots_lock);
	अगर (ret < 0) अणु
		kvm->arch.vioapic = शून्य;
		kमुक्त(ioapic);
	पूर्ण

	वापस ret;
पूर्ण

व्योम kvm_ioapic_destroy(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_ioapic *ioapic = kvm->arch.vioapic;

	अगर (!ioapic)
		वापस;

	cancel_delayed_work_sync(&ioapic->eoi_inject);
	mutex_lock(&kvm->slots_lock);
	kvm_io_bus_unरेजिस्टर_dev(kvm, KVM_MMIO_BUS, &ioapic->dev);
	mutex_unlock(&kvm->slots_lock);
	kvm->arch.vioapic = शून्य;
	kमुक्त(ioapic);
पूर्ण

व्योम kvm_get_ioapic(काष्ठा kvm *kvm, काष्ठा kvm_ioapic_state *state)
अणु
	काष्ठा kvm_ioapic *ioapic = kvm->arch.vioapic;

	spin_lock(&ioapic->lock);
	स_नकल(state, ioapic, माप(काष्ठा kvm_ioapic_state));
	state->irr &= ~ioapic->irr_delivered;
	spin_unlock(&ioapic->lock);
पूर्ण

व्योम kvm_set_ioapic(काष्ठा kvm *kvm, काष्ठा kvm_ioapic_state *state)
अणु
	काष्ठा kvm_ioapic *ioapic = kvm->arch.vioapic;

	spin_lock(&ioapic->lock);
	स_नकल(ioapic, state, माप(काष्ठा kvm_ioapic_state));
	ioapic->irr = 0;
	ioapic->irr_delivered = 0;
	kvm_make_scan_ioapic_request(kvm);
	kvm_ioapic_inject_all(ioapic, state->irr);
	spin_unlock(&ioapic->lock);
पूर्ण
