<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * spu management operations क्रम of based platक्रमms
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 * Copyright 2006 Sony Corp.
 * (C) Copyright 2007 TOSHIBA CORPORATION
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/export.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>

#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_priv1.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/prom.h>

#समावेश "spufs/spufs.h"
#समावेश "interrupt.h"

काष्ठा device_node *spu_devnode(काष्ठा spu *spu)
अणु
	वापस spu->devnode;
पूर्ण

EXPORT_SYMBOL_GPL(spu_devnode);

अटल u64 __init find_spu_unit_number(काष्ठा device_node *spe)
अणु
	स्थिर अचिन्हित पूर्णांक *prop;
	पूर्णांक proplen;

	/* new device trees should provide the physical-id attribute */
	prop = of_get_property(spe, "physical-id", &proplen);
	अगर (proplen == 4)
		वापस (u64)*prop;

	/* celleb device tree provides the unit-id */
	prop = of_get_property(spe, "unit-id", &proplen);
	अगर (proplen == 4)
		वापस (u64)*prop;

	/* legacy device trees provide the id in the reg attribute */
	prop = of_get_property(spe, "reg", &proplen);
	अगर (proplen == 4)
		वापस (u64)*prop;

	वापस 0;
पूर्ण

अटल व्योम spu_unmap(काष्ठा spu *spu)
अणु
	अगर (!firmware_has_feature(FW_FEATURE_LPAR))
		iounmap(spu->priv1);
	iounmap(spu->priv2);
	iounmap(spu->problem);
	iounmap((__क्रमce u8 __iomem *)spu->local_store);
पूर्ण

अटल पूर्णांक __init spu_map_पूर्णांकerrupts_old(काष्ठा spu *spu,
	काष्ठा device_node *np)
अणु
	अचिन्हित पूर्णांक isrc;
	स्थिर u32 *पंचांगp;
	पूर्णांक nid;

	/* Get the पूर्णांकerrupt source unit from the device-tree */
	पंचांगp = of_get_property(np, "isrc", शून्य);
	अगर (!पंचांगp)
		वापस -ENODEV;
	isrc = पंचांगp[0];

	पंचांगp = of_get_property(np->parent->parent, "node-id", शून्य);
	अगर (!पंचांगp) अणु
		prपूर्णांकk(KERN_WARNING "%s: can't find node-id\n", __func__);
		nid = spu->node;
	पूर्ण अन्यथा
		nid = पंचांगp[0];

	/* Add the node number */
	isrc |= nid << IIC_IRQ_NODE_SHIFT;

	/* Now map पूर्णांकerrupts of all 3 classes */
	spu->irqs[0] = irq_create_mapping(शून्य, IIC_IRQ_CLASS_0 | isrc);
	spu->irqs[1] = irq_create_mapping(शून्य, IIC_IRQ_CLASS_1 | isrc);
	spu->irqs[2] = irq_create_mapping(शून्य, IIC_IRQ_CLASS_2 | isrc);

	/* Right now, we only fail अगर class 2 failed */
	अगर (!spu->irqs[2])
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम __iomem * __init spu_map_prop_old(काष्ठा spu *spu,
					      काष्ठा device_node *n,
					      स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा address_prop अणु
		अचिन्हित दीर्घ address;
		अचिन्हित पूर्णांक len;
	पूर्ण __attribute__((packed)) *prop;
	पूर्णांक proplen;

	prop = of_get_property(n, name, &proplen);
	अगर (prop == शून्य || proplen != माप (काष्ठा address_prop))
		वापस शून्य;

	वापस ioremap(prop->address, prop->len);
पूर्ण

अटल पूर्णांक __init spu_map_device_old(काष्ठा spu *spu)
अणु
	काष्ठा device_node *node = spu->devnode;
	स्थिर अक्षर *prop;
	पूर्णांक ret;

	ret = -ENODEV;
	spu->name = of_get_property(node, "name", शून्य);
	अगर (!spu->name)
		जाओ out;

	prop = of_get_property(node, "local-store", शून्य);
	अगर (!prop)
		जाओ out;
	spu->local_store_phys = *(अचिन्हित दीर्घ *)prop;

	/* we use local store as ram, not io memory */
	spu->local_store = (व्योम __क्रमce *)
		spu_map_prop_old(spu, node, "local-store");
	अगर (!spu->local_store)
		जाओ out;

	prop = of_get_property(node, "problem", शून्य);
	अगर (!prop)
		जाओ out_unmap;
	spu->problem_phys = *(अचिन्हित दीर्घ *)prop;

	spu->problem = spu_map_prop_old(spu, node, "problem");
	अगर (!spu->problem)
		जाओ out_unmap;

	spu->priv2 = spu_map_prop_old(spu, node, "priv2");
	अगर (!spu->priv2)
		जाओ out_unmap;

	अगर (!firmware_has_feature(FW_FEATURE_LPAR)) अणु
		spu->priv1 = spu_map_prop_old(spu, node, "priv1");
		अगर (!spu->priv1)
			जाओ out_unmap;
	पूर्ण

	ret = 0;
	जाओ out;

out_unmap:
	spu_unmap(spu);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक __init spu_map_पूर्णांकerrupts(काष्ठा spu *spu, काष्ठा device_node *np)
अणु
	पूर्णांक i;

	क्रम (i=0; i < 3; i++) अणु
		spu->irqs[i] = irq_of_parse_and_map(np, i);
		अगर (!spu->irqs[i])
			जाओ err;
	पूर्ण
	वापस 0;

err:
	pr_debug("failed to map irq %x for spu %s\n", i, spu->name);
	क्रम (; i >= 0; i--) अणु
		अगर (spu->irqs[i])
			irq_dispose_mapping(spu->irqs[i]);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक spu_map_resource(काष्ठा spu *spu, पूर्णांक nr,
			    व्योम __iomem** virt, अचिन्हित दीर्घ *phys)
अणु
	काष्ठा device_node *np = spu->devnode;
	काष्ठा resource resource = अणु पूर्ण;
	अचिन्हित दीर्घ len;
	पूर्णांक ret;

	ret = of_address_to_resource(np, nr, &resource);
	अगर (ret)
		वापस ret;
	अगर (phys)
		*phys = resource.start;
	len = resource_size(&resource);
	*virt = ioremap(resource.start, len);
	अगर (!*virt)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक __init spu_map_device(काष्ठा spu *spu)
अणु
	काष्ठा device_node *np = spu->devnode;
	पूर्णांक ret = -ENODEV;

	spu->name = of_get_property(np, "name", शून्य);
	अगर (!spu->name)
		जाओ out;

	ret = spu_map_resource(spu, 0, (व्योम __iomem**)&spu->local_store,
			       &spu->local_store_phys);
	अगर (ret) अणु
		pr_debug("spu_new: failed to map %pOF resource 0\n",
			 np);
		जाओ out;
	पूर्ण
	ret = spu_map_resource(spu, 1, (व्योम __iomem**)&spu->problem,
			       &spu->problem_phys);
	अगर (ret) अणु
		pr_debug("spu_new: failed to map %pOF resource 1\n",
			 np);
		जाओ out_unmap;
	पूर्ण
	ret = spu_map_resource(spu, 2, (व्योम __iomem**)&spu->priv2, शून्य);
	अगर (ret) अणु
		pr_debug("spu_new: failed to map %pOF resource 2\n",
			 np);
		जाओ out_unmap;
	पूर्ण
	अगर (!firmware_has_feature(FW_FEATURE_LPAR))
		ret = spu_map_resource(spu, 3,
			       (व्योम __iomem**)&spu->priv1, शून्य);
	अगर (ret) अणु
		pr_debug("spu_new: failed to map %pOF resource 3\n",
			 np);
		जाओ out_unmap;
	पूर्ण
	pr_debug("spu_new: %pOF maps:\n", np);
	pr_debug("  local store   : 0x%016lx -> 0x%p\n",
		 spu->local_store_phys, spu->local_store);
	pr_debug("  problem state : 0x%016lx -> 0x%p\n",
		 spu->problem_phys, spu->problem);
	pr_debug("  priv2         :                       0x%p\n", spu->priv2);
	pr_debug("  priv1         :                       0x%p\n", spu->priv1);

	वापस 0;

out_unmap:
	spu_unmap(spu);
out:
	pr_debug("failed to map spe %s: %d\n", spu->name, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक __init of_क्रमागतerate_spus(पूर्णांक (*fn)(व्योम *data))
अणु
	पूर्णांक ret;
	काष्ठा device_node *node;
	अचिन्हित पूर्णांक n = 0;

	ret = -ENODEV;
	क्रम_each_node_by_type(node, "spe") अणु
		ret = fn(node);
		अगर (ret) अणु
			prपूर्णांकk(KERN_WARNING "%s: Error initializing %pOFn\n",
				__func__, node);
			of_node_put(node);
			अवरोध;
		पूर्ण
		n++;
	पूर्ण
	वापस ret ? ret : n;
पूर्ण

अटल पूर्णांक __init of_create_spu(काष्ठा spu *spu, व्योम *data)
अणु
	पूर्णांक ret;
	काष्ठा device_node *spe = (काष्ठा device_node *)data;
	अटल पूर्णांक legacy_map = 0, legacy_irq = 0;

	spu->devnode = of_node_get(spe);
	spu->spe_id = find_spu_unit_number(spe);

	spu->node = of_node_to_nid(spe);
	अगर (spu->node >= MAX_NUMNODES) अणु
		prपूर्णांकk(KERN_WARNING "SPE %pOF on node %d ignored,"
		       " node number too big\n", spe, spu->node);
		prपूर्णांकk(KERN_WARNING "Check if CONFIG_NUMA is enabled.\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ret = spu_map_device(spu);
	अगर (ret) अणु
		अगर (!legacy_map) अणु
			legacy_map = 1;
			prपूर्णांकk(KERN_WARNING "%s: Legacy device tree found, "
				"trying to map old style\n", __func__);
		पूर्ण
		ret = spu_map_device_old(spu);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "Unable to map %s\n",
				spu->name);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = spu_map_पूर्णांकerrupts(spu, spe);
	अगर (ret) अणु
		अगर (!legacy_irq) अणु
			legacy_irq = 1;
			prपूर्णांकk(KERN_WARNING "%s: Legacy device tree found, "
				"trying old style irq\n", __func__);
		पूर्ण
		ret = spu_map_पूर्णांकerrupts_old(spu, spe);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: could not map interrupts\n",
				spu->name);
			जाओ out_unmap;
		पूर्ण
	पूर्ण

	pr_debug("Using SPE %s %p %p %p %p %d\n", spu->name,
		spu->local_store, spu->problem, spu->priv1,
		spu->priv2, spu->number);
	जाओ out;

out_unmap:
	spu_unmap(spu);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक of_destroy_spu(काष्ठा spu *spu)
अणु
	spu_unmap(spu);
	of_node_put(spu->devnode);
	वापस 0;
पूर्ण

अटल व्योम enable_spu_by_master_run(काष्ठा spu_context *ctx)
अणु
	ctx->ops->master_start(ctx);
पूर्ण

अटल व्योम disable_spu_by_master_run(काष्ठा spu_context *ctx)
अणु
	ctx->ops->master_stop(ctx);
पूर्ण

/* Hardcoded affinity idxs क्रम qs20 */
#घोषणा QS20_SPES_PER_BE 8
अटल पूर्णांक qs20_reg_idxs[QS20_SPES_PER_BE] =   अणु 0, 2, 4, 6, 7, 5, 3, 1 पूर्ण;
अटल पूर्णांक qs20_reg_memory[QS20_SPES_PER_BE] = अणु 1, 1, 0, 0, 0, 0, 0, 0 पूर्ण;

अटल काष्ठा spu *spu_lookup_reg(पूर्णांक node, u32 reg)
अणु
	काष्ठा spu *spu;
	स्थिर u32 *spu_reg;

	list_क्रम_each_entry(spu, &cbe_spu_info[node].spus, cbe_list) अणु
		spu_reg = of_get_property(spu_devnode(spu), "reg", शून्य);
		अगर (*spu_reg == reg)
			वापस spu;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम init_affinity_qs20_harcoded(व्योम)
अणु
	पूर्णांक node, i;
	काष्ठा spu *last_spu, *spu;
	u32 reg;

	क्रम (node = 0; node < MAX_NUMNODES; node++) अणु
		last_spu = शून्य;
		क्रम (i = 0; i < QS20_SPES_PER_BE; i++) अणु
			reg = qs20_reg_idxs[i];
			spu = spu_lookup_reg(node, reg);
			अगर (!spu)
				जारी;
			spu->has_mem_affinity = qs20_reg_memory[reg];
			अगर (last_spu)
				list_add_tail(&spu->aff_list,
						&last_spu->aff_list);
			last_spu = spu;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक of_has_vicinity(व्योम)
अणु
	काष्ठा device_node *dn;

	क्रम_each_node_by_type(dn, "spe") अणु
		अगर (of_find_property(dn, "vicinity", शून्य))  अणु
			of_node_put(dn);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा spu *devnode_spu(पूर्णांक cbe, काष्ठा device_node *dn)
अणु
	काष्ठा spu *spu;

	list_क्रम_each_entry(spu, &cbe_spu_info[cbe].spus, cbe_list)
		अगर (spu_devnode(spu) == dn)
			वापस spu;
	वापस शून्य;
पूर्ण

अटल काष्ठा spu *
neighbour_spu(पूर्णांक cbe, काष्ठा device_node *target, काष्ठा device_node *aव्योम)
अणु
	काष्ठा spu *spu;
	काष्ठा device_node *spu_dn;
	स्थिर phandle *vic_handles;
	पूर्णांक lenp, i;

	list_क्रम_each_entry(spu, &cbe_spu_info[cbe].spus, cbe_list) अणु
		spu_dn = spu_devnode(spu);
		अगर (spu_dn == aव्योम)
			जारी;
		vic_handles = of_get_property(spu_dn, "vicinity", &lenp);
		क्रम (i=0; i < (lenp / माप(phandle)); i++) अणु
			अगर (vic_handles[i] == target->phandle)
				वापस spu;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम init_affinity_node(पूर्णांक cbe)
अणु
	काष्ठा spu *spu, *last_spu;
	काष्ठा device_node *vic_dn, *last_spu_dn;
	phandle aव्योम_ph;
	स्थिर phandle *vic_handles;
	पूर्णांक lenp, i, added;

	last_spu = list_first_entry(&cbe_spu_info[cbe].spus, काष्ठा spu,
								cbe_list);
	aव्योम_ph = 0;
	क्रम (added = 1; added < cbe_spu_info[cbe].n_spus; added++) अणु
		last_spu_dn = spu_devnode(last_spu);
		vic_handles = of_get_property(last_spu_dn, "vicinity", &lenp);

		/*
		 * Walk through each phandle in vicinity property of the spu
		 * (tipically two vicinity phandles per spe node)
		 */
		क्रम (i = 0; i < (lenp / माप(phandle)); i++) अणु
			अगर (vic_handles[i] == aव्योम_ph)
				जारी;

			vic_dn = of_find_node_by_phandle(vic_handles[i]);
			अगर (!vic_dn)
				जारी;

			अगर (of_node_name_eq(vic_dn, "spe") ) अणु
				spu = devnode_spu(cbe, vic_dn);
				aव्योम_ph = last_spu_dn->phandle;
			पूर्ण अन्यथा अणु
				/*
				 * "mic-tm" and "bif0" nodes करो not have
				 * vicinity property. So we need to find the
				 * spe which has vic_dn as neighbour, but
				 * skipping the one we came from (last_spu_dn)
				 */
				spu = neighbour_spu(cbe, vic_dn, last_spu_dn);
				अगर (!spu)
					जारी;
				अगर (of_node_name_eq(vic_dn, "mic-tm")) अणु
					last_spu->has_mem_affinity = 1;
					spu->has_mem_affinity = 1;
				पूर्ण
				aव्योम_ph = vic_dn->phandle;
			पूर्ण

			list_add_tail(&spu->aff_list, &last_spu->aff_list);
			last_spu = spu;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम init_affinity_fw(व्योम)
अणु
	पूर्णांक cbe;

	क्रम (cbe = 0; cbe < MAX_NUMNODES; cbe++)
		init_affinity_node(cbe);
पूर्ण

अटल पूर्णांक __init init_affinity(व्योम)
अणु
	अगर (of_has_vicinity()) अणु
		init_affinity_fw();
	पूर्ण अन्यथा अणु
		अगर (of_machine_is_compatible("IBM,CPBW-1.0"))
			init_affinity_qs20_harcoded();
		अन्यथा
			prपूर्णांकk("No affinity configuration found\n");
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा spu_management_ops spu_management_of_ops = अणु
	.क्रमागतerate_spus = of_क्रमागतerate_spus,
	.create_spu = of_create_spu,
	.destroy_spu = of_destroy_spu,
	.enable_spu = enable_spu_by_master_run,
	.disable_spu = disable_spu_by_master_run,
	.init_affinity = init_affinity,
पूर्ण;
