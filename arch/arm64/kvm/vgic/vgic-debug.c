<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Linaro
 * Author: Christoffer Dall <christoffer.dall@linaro.org>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/seq_file.h>
#समावेश <kvm/arm_vgic.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश "vgic.h"

/*
 * Structure to control looping through the entire vgic state.  We start at
 * zero क्रम each field and move upwards.  So, अगर dist_id is 0 we prपूर्णांक the
 * distributor info.  When dist_id is 1, we have alपढ़ोy prपूर्णांकed it and move
 * on.
 *
 * When vcpu_id < nr_cpus we prपूर्णांक the vcpu info until vcpu_id == nr_cpus and
 * so on.
 */
काष्ठा vgic_state_iter अणु
	पूर्णांक nr_cpus;
	पूर्णांक nr_spis;
	पूर्णांक nr_lpis;
	पूर्णांक dist_id;
	पूर्णांक vcpu_id;
	पूर्णांक पूर्णांकid;
	पूर्णांक lpi_idx;
	u32 *lpi_array;
पूर्ण;

अटल व्योम iter_next(काष्ठा vgic_state_iter *iter)
अणु
	अगर (iter->dist_id == 0) अणु
		iter->dist_id++;
		वापस;
	पूर्ण

	iter->पूर्णांकid++;
	अगर (iter->पूर्णांकid == VGIC_NR_PRIVATE_IRQS &&
	    ++iter->vcpu_id < iter->nr_cpus)
		iter->पूर्णांकid = 0;

	अगर (iter->पूर्णांकid >= (iter->nr_spis + VGIC_NR_PRIVATE_IRQS)) अणु
		अगर (iter->lpi_idx < iter->nr_lpis)
			iter->पूर्णांकid = iter->lpi_array[iter->lpi_idx];
		iter->lpi_idx++;
	पूर्ण
पूर्ण

अटल व्योम iter_init(काष्ठा kvm *kvm, काष्ठा vgic_state_iter *iter,
		      loff_t pos)
अणु
	पूर्णांक nr_cpus = atomic_पढ़ो(&kvm->online_vcpus);

	स_रखो(iter, 0, माप(*iter));

	iter->nr_cpus = nr_cpus;
	iter->nr_spis = kvm->arch.vgic.nr_spis;
	अगर (kvm->arch.vgic.vgic_model == KVM_DEV_TYPE_ARM_VGIC_V3) अणु
		iter->nr_lpis = vgic_copy_lpi_list(kvm, शून्य, &iter->lpi_array);
		अगर (iter->nr_lpis < 0)
			iter->nr_lpis = 0;
	पूर्ण

	/* Fast क्रमward to the right position अगर needed */
	जबतक (pos--)
		iter_next(iter);
पूर्ण

अटल bool end_of_vgic(काष्ठा vgic_state_iter *iter)
अणु
	वापस iter->dist_id > 0 &&
		iter->vcpu_id == iter->nr_cpus &&
		iter->पूर्णांकid >= (iter->nr_spis + VGIC_NR_PRIVATE_IRQS) &&
		iter->lpi_idx > iter->nr_lpis;
पूर्ण

अटल व्योम *vgic_debug_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा kvm *kvm = (काष्ठा kvm *)s->निजी;
	काष्ठा vgic_state_iter *iter;

	mutex_lock(&kvm->lock);
	iter = kvm->arch.vgic.iter;
	अगर (iter) अणु
		iter = ERR_PTR(-EBUSY);
		जाओ out;
	पूर्ण

	iter = kदो_स्मृति(माप(*iter), GFP_KERNEL);
	अगर (!iter) अणु
		iter = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	iter_init(kvm, iter, *pos);
	kvm->arch.vgic.iter = iter;

	अगर (end_of_vgic(iter))
		iter = शून्य;
out:
	mutex_unlock(&kvm->lock);
	वापस iter;
पूर्ण

अटल व्योम *vgic_debug_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा kvm *kvm = (काष्ठा kvm *)s->निजी;
	काष्ठा vgic_state_iter *iter = kvm->arch.vgic.iter;

	++*pos;
	iter_next(iter);
	अगर (end_of_vgic(iter))
		iter = शून्य;
	वापस iter;
पूर्ण

अटल व्योम vgic_debug_stop(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा kvm *kvm = (काष्ठा kvm *)s->निजी;
	काष्ठा vgic_state_iter *iter;

	/*
	 * If the seq file wasn't properly opened, there's nothing to clearn
	 * up.
	 */
	अगर (IS_ERR(v))
		वापस;

	mutex_lock(&kvm->lock);
	iter = kvm->arch.vgic.iter;
	kमुक्त(iter->lpi_array);
	kमुक्त(iter);
	kvm->arch.vgic.iter = शून्य;
	mutex_unlock(&kvm->lock);
पूर्ण

अटल व्योम prपूर्णांक_dist_state(काष्ठा seq_file *s, काष्ठा vgic_dist *dist)
अणु
	bool v3 = dist->vgic_model == KVM_DEV_TYPE_ARM_VGIC_V3;

	seq_म_लिखो(s, "Distributor\n");
	seq_म_लिखो(s, "===========\n");
	seq_म_लिखो(s, "vgic_model:\t%s\n", v3 ? "GICv3" : "GICv2");
	seq_म_लिखो(s, "nr_spis:\t%d\n", dist->nr_spis);
	अगर (v3)
		seq_म_लिखो(s, "nr_lpis:\t%d\n", dist->lpi_list_count);
	seq_म_लिखो(s, "enabled:\t%d\n", dist->enabled);
	seq_म_लिखो(s, "\n");

	seq_म_लिखो(s, "P=pending_latch, L=line_level, A=active\n");
	seq_म_लिखो(s, "E=enabled, H=hw, C=config (level=1, edge=0)\n");
	seq_म_लिखो(s, "G=group\n");
पूर्ण

अटल व्योम prपूर्णांक_header(काष्ठा seq_file *s, काष्ठा vgic_irq *irq,
			 काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक id = 0;
	अक्षर *hdr = "SPI ";

	अगर (vcpu) अणु
		hdr = "VCPU";
		id = vcpu->vcpu_id;
	पूर्ण

	seq_म_लिखो(s, "\n");
	seq_म_लिखो(s, "%s%2d TYP   ID TGT_ID PLAEHCG     HWID   TARGET SRC PRI VCPU_ID\n", hdr, id);
	seq_म_लिखो(s, "----------------------------------------------------------------\n");
पूर्ण

अटल व्योम prपूर्णांक_irq_state(काष्ठा seq_file *s, काष्ठा vgic_irq *irq,
			    काष्ठा kvm_vcpu *vcpu)
अणु
	अक्षर *type;
	bool pending;

	अगर (irq->पूर्णांकid < VGIC_NR_SGIS)
		type = "SGI";
	अन्यथा अगर (irq->पूर्णांकid < VGIC_NR_PRIVATE_IRQS)
		type = "PPI";
	अन्यथा अगर (irq->पूर्णांकid < VGIC_MAX_SPI)
		type = "SPI";
	अन्यथा
		type = "LPI";

	अगर (irq->पूर्णांकid ==0 || irq->पूर्णांकid == VGIC_NR_PRIVATE_IRQS)
		prपूर्णांक_header(s, irq, vcpu);

	pending = irq->pending_latch;
	अगर (irq->hw && vgic_irq_is_sgi(irq->पूर्णांकid)) अणु
		पूर्णांक err;

		err = irq_get_irqchip_state(irq->host_irq,
					    IRQCHIP_STATE_PENDING,
					    &pending);
		WARN_ON_ONCE(err);
	पूर्ण

	seq_म_लिखो(s, "       %s %4d "
		      "    %2d "
		      "%d%d%d%d%d%d%d "
		      "%8d "
		      "%8x "
		      " %2x "
		      "%3d "
		      "     %2d "
		      "\n",
			type, irq->पूर्णांकid,
			(irq->target_vcpu) ? irq->target_vcpu->vcpu_id : -1,
			pending,
			irq->line_level,
			irq->active,
			irq->enabled,
			irq->hw,
			irq->config == VGIC_CONFIG_LEVEL,
			irq->group,
			irq->hwपूर्णांकid,
			irq->mpidr,
			irq->source,
			irq->priority,
			(irq->vcpu) ? irq->vcpu->vcpu_id : -1);
पूर्ण

अटल पूर्णांक vgic_debug_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा kvm *kvm = (काष्ठा kvm *)s->निजी;
	काष्ठा vgic_state_iter *iter = (काष्ठा vgic_state_iter *)v;
	काष्ठा vgic_irq *irq;
	काष्ठा kvm_vcpu *vcpu = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (iter->dist_id == 0) अणु
		prपूर्णांक_dist_state(s, &kvm->arch.vgic);
		वापस 0;
	पूर्ण

	अगर (!kvm->arch.vgic.initialized)
		वापस 0;

	अगर (iter->vcpu_id < iter->nr_cpus)
		vcpu = kvm_get_vcpu(kvm, iter->vcpu_id);

	irq = vgic_get_irq(kvm, vcpu, iter->पूर्णांकid);
	अगर (!irq) अणु
		seq_म_लिखो(s, "       LPI %4d freed\n", iter->पूर्णांकid);
		वापस 0;
	पूर्ण

	raw_spin_lock_irqsave(&irq->irq_lock, flags);
	prपूर्णांक_irq_state(s, irq, vcpu);
	raw_spin_unlock_irqrestore(&irq->irq_lock, flags);

	vgic_put_irq(kvm, irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations vgic_debug_sops = अणु
	.start = vgic_debug_start,
	.next  = vgic_debug_next,
	.stop  = vgic_debug_stop,
	.show  = vgic_debug_show
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(vgic_debug);

व्योम vgic_debug_init(काष्ठा kvm *kvm)
अणु
	debugfs_create_file("vgic-state", 0444, kvm->debugfs_dentry, kvm,
			    &vgic_debug_fops);
पूर्ण

व्योम vgic_debug_destroy(काष्ठा kvm *kvm)
अणु
पूर्ण
