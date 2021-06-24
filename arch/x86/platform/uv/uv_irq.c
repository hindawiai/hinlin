<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * SGI UV IRQ functions
 *
 * Copyright (C) 2008 Silicon Graphics, Inc. All rights reserved.
 */

#समावेश <linux/export.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/irqकरोमुख्य.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/uv/uv_irq.h>
#समावेश <यंत्र/uv/uv_hub.h>

/* MMR offset and pnode of hub sourcing पूर्णांकerrupts क्रम a given irq */
काष्ठा uv_irq_2_mmr_pnode अणु
	अचिन्हित दीर्घ		offset;
	पूर्णांक			pnode;
पूर्ण;

अटल व्योम uv_program_mmr(काष्ठा irq_cfg *cfg, काष्ठा uv_irq_2_mmr_pnode *info)
अणु
	अचिन्हित दीर्घ mmr_value;
	काष्ठा uv_IO_APIC_route_entry *entry;

	BUILD_BUG_ON(माप(काष्ठा uv_IO_APIC_route_entry) !=
		     माप(अचिन्हित दीर्घ));

	mmr_value = 0;
	entry = (काष्ठा uv_IO_APIC_route_entry *)&mmr_value;
	entry->vector		= cfg->vector;
	entry->delivery_mode	= apic->delivery_mode;
	entry->dest_mode	= apic->dest_mode_logical;
	entry->polarity		= 0;
	entry->trigger		= 0;
	entry->mask		= 0;
	entry->dest		= cfg->dest_apicid;

	uv_ग_लिखो_global_mmr64(info->pnode, info->offset, mmr_value);
पूर्ण

अटल व्योम uv_noop(काष्ठा irq_data *data) अणु पूर्ण

अटल पूर्णांक
uv_set_irq_affinity(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *mask,
		    bool क्रमce)
अणु
	काष्ठा irq_data *parent = data->parent_data;
	काष्ठा irq_cfg *cfg = irqd_cfg(data);
	पूर्णांक ret;

	ret = parent->chip->irq_set_affinity(parent, mask, क्रमce);
	अगर (ret >= 0) अणु
		uv_program_mmr(cfg, data->chip_data);
		send_cleanup_vector(cfg);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा irq_chip uv_irq_chip = अणु
	.name			= "UV-CORE",
	.irq_mask		= uv_noop,
	.irq_unmask		= uv_noop,
	.irq_eoi		= apic_ack_irq,
	.irq_set_affinity	= uv_set_irq_affinity,
पूर्ण;

अटल पूर्णांक uv_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			   अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा uv_irq_2_mmr_pnode *chip_data;
	काष्ठा irq_alloc_info *info = arg;
	काष्ठा irq_data *irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	पूर्णांक ret;

	अगर (nr_irqs > 1 || !info || info->type != X86_IRQ_ALLOC_TYPE_UV)
		वापस -EINVAL;

	chip_data = kदो_स्मृति_node(माप(*chip_data), GFP_KERNEL,
				 irq_data_get_node(irq_data));
	अगर (!chip_data)
		वापस -ENOMEM;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, arg);
	अगर (ret >= 0) अणु
		अगर (info->uv.limit == UV_AFFINITY_CPU)
			irq_set_status_flags(virq, IRQ_NO_BALANCING);
		अन्यथा
			irq_set_status_flags(virq, IRQ_MOVE_PCNTXT);

		chip_data->pnode = uv_blade_to_pnode(info->uv.blade);
		chip_data->offset = info->uv.offset;
		irq_करोमुख्य_set_info(करोमुख्य, virq, virq, &uv_irq_chip, chip_data,
				    handle_percpu_irq, शून्य, info->uv.name);
	पूर्ण अन्यथा अणु
		kमुक्त(chip_data);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम uv_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			   अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);

	BUG_ON(nr_irqs != 1);
	kमुक्त(irq_data->chip_data);
	irq_clear_status_flags(virq, IRQ_MOVE_PCNTXT);
	irq_clear_status_flags(virq, IRQ_NO_BALANCING);
	irq_करोमुख्य_मुक्त_irqs_top(करोमुख्य, virq, nr_irqs);
पूर्ण

/*
 * Re-target the irq to the specअगरied CPU and enable the specअगरied MMR located
 * on the specअगरied blade to allow the sending of MSIs to the specअगरied CPU.
 */
अटल पूर्णांक uv_करोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
			      काष्ठा irq_data *irq_data, bool reserve)
अणु
	uv_program_mmr(irqd_cfg(irq_data), irq_data->chip_data);
	वापस 0;
पूर्ण

/*
 * Disable the specअगरied MMR located on the specअगरied blade so that MSIs are
 * दीर्घer allowed to be sent.
 */
अटल व्योम uv_करोमुख्य_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
				 काष्ठा irq_data *irq_data)
अणु
	अचिन्हित दीर्घ mmr_value;
	काष्ठा uv_IO_APIC_route_entry *entry;

	mmr_value = 0;
	entry = (काष्ठा uv_IO_APIC_route_entry *)&mmr_value;
	entry->mask = 1;
	uv_program_mmr(irqd_cfg(irq_data), irq_data->chip_data);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops uv_करोमुख्य_ops = अणु
	.alloc		= uv_करोमुख्य_alloc,
	.मुक्त		= uv_करोमुख्य_मुक्त,
	.activate	= uv_करोमुख्य_activate,
	.deactivate	= uv_करोमुख्य_deactivate,
पूर्ण;

अटल काष्ठा irq_करोमुख्य *uv_get_irq_करोमुख्य(व्योम)
अणु
	अटल काष्ठा irq_करोमुख्य *uv_करोमुख्य;
	अटल DEFINE_MUTEX(uv_lock);
	काष्ठा fwnode_handle *fn;

	mutex_lock(&uv_lock);
	अगर (uv_करोमुख्य)
		जाओ out;

	fn = irq_करोमुख्य_alloc_named_fwnode("UV-CORE");
	अगर (!fn)
		जाओ out;

	uv_करोमुख्य = irq_करोमुख्य_create_tree(fn, &uv_करोमुख्य_ops, शून्य);
	अगर (uv_करोमुख्य)
		uv_करोमुख्य->parent = x86_vector_करोमुख्य;
	अन्यथा
		irq_करोमुख्य_मुक्त_fwnode(fn);
out:
	mutex_unlock(&uv_lock);

	वापस uv_करोमुख्य;
पूर्ण

/*
 * Set up a mapping of an available irq and vector, and enable the specअगरied
 * MMR that defines the MSI that is to be sent to the specअगरied CPU when an
 * पूर्णांकerrupt is उठाओd.
 */
पूर्णांक uv_setup_irq(अक्षर *irq_name, पूर्णांक cpu, पूर्णांक mmr_blade,
		 अचिन्हित दीर्घ mmr_offset, पूर्णांक limit)
अणु
	काष्ठा irq_alloc_info info;
	काष्ठा irq_करोमुख्य *करोमुख्य = uv_get_irq_करोमुख्य();

	अगर (!करोमुख्य)
		वापस -ENOMEM;

	init_irq_alloc_info(&info, cpumask_of(cpu));
	info.type = X86_IRQ_ALLOC_TYPE_UV;
	info.uv.limit = limit;
	info.uv.blade = mmr_blade;
	info.uv.offset = mmr_offset;
	info.uv.name = irq_name;

	वापस irq_करोमुख्य_alloc_irqs(करोमुख्य, 1,
				     uv_blade_to_memory_nid(mmr_blade), &info);
पूर्ण
EXPORT_SYMBOL_GPL(uv_setup_irq);

/*
 * Tear करोwn a mapping of an irq and vector, and disable the specअगरied MMR that
 * defined the MSI that was to be sent to the specअगरied CPU when an पूर्णांकerrupt
 * was उठाओd.
 *
 * Set mmr_blade and mmr_offset to what was passed in on uv_setup_irq().
 */
व्योम uv_tearकरोwn_irq(अचिन्हित पूर्णांक irq)
अणु
	irq_करोमुख्य_मुक्त_irqs(irq, 1);
पूर्ण
EXPORT_SYMBOL_GPL(uv_tearकरोwn_irq);
