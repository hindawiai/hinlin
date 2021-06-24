<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016,2017 ARM Limited, All Rights Reserved.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/msi.h>
#समावेश <linux/sched.h>

#समावेश <linux/irqchip/arm-gic-v4.h>

/*
 * WARNING: The blurb below assumes that you understand the
 * पूर्णांकricacies of GICv3, GICv4, and how a guest's view of a GICv3 माला_लो
 * translated पूर्णांकo GICv4 commands. So it effectively tarमाला_लो at most
 * two inभागiduals. You know who you are.
 *
 * The core GICv4 code is deचिन्हित to *aव्योम* exposing too much of the
 * core GIC code (that would in turn leak पूर्णांकo the hypervisor code),
 * and instead provide a hypervisor agnostic पूर्णांकerface to the HW (of
 * course, the astute पढ़ोer will quickly realize that hypervisor
 * agnostic actually means KVM-specअगरic - what were you thinking?).
 *
 * In order to achieve a modicum of isolation, we try to hide most of
 * the GICv4 "stuff" behind normal irqchip operations:
 *
 * - Any guest-visible VLPI is backed by a Linux पूर्णांकerrupt (and a
 *   physical LPI which माला_लो unmapped when the guest maps the
 *   VLPI). This allows the same DevID/EventID pair to be either
 *   mapped to the LPI (host) or the VLPI (guest). Note that this is
 *   exclusive, and you cannot have both.
 *
 * - Enabling/disabling a VLPI is करोne by issuing mask/unmask calls.
 *
 * - Guest INT/CLEAR commands are implemented through
 *   irq_set_irqchip_state().
 *
 * - The *bizarre* stuff (mapping/unmapping an पूर्णांकerrupt to a VLPI, or
 *   issuing an INV after changing a priority) माला_लो shoved पूर्णांकo the
 *   irq_set_vcpu_affinity() method. While this is quite horrible
 *   (let's face it, this is the irqchip version of an ioctl), it
 *   confines the crap to a single location. And map/unmap really is
 *   about setting the affinity of a VLPI to a vcpu, so only INV is
 *   majorly out of place. So there.
 *
 * A number of commands are simply not provided by this पूर्णांकerface, as
 * they करो not make direct sense. For example, MAPD is purely local to
 * the भव ITS (because it references a भव device, and the
 * physical ITS is still very much in अक्षरge of the physical
 * device). Same goes क्रम things like MAPC (the physical ITS deals
 * with the actual vPE affinity, and not the braindead concept of
 * collection). SYNC is not provided either, as each and every command
 * is followed by a VSYNC. This could be relaxed in the future, should
 * this be seen as a bottleneck (yes, this means *never*).
 *
 * But handling VLPIs is only one side of the job of the GICv4
 * code. The other (darker) side is to take care of the करोorbell
 * पूर्णांकerrupts which are delivered when a VLPI targeting a non-running
 * vcpu is being made pending.
 *
 * The choice made here is that each vcpu (VPE in old northern GICv4
 * dialect) माला_लो a single करोorbell LPI, no matter how many पूर्णांकerrupts
 * are targeting it. This has a nice property, which is that the
 * पूर्णांकerrupt becomes a handle क्रम the VPE, and that the hypervisor
 * code can manipulate it through the normal पूर्णांकerrupt API:
 *
 * - VMs (or rather the VM असलtraction that matters to the GIC)
 *   contain an irq करोमुख्य where each पूर्णांकerrupt maps to a VPE. In
 *   turn, this करोमुख्य sits on top of the normal LPI allocator, and a
 *   specially crafted irq_chip implementation.
 *
 * - mask/unmask करो what is expected on the करोorbell पूर्णांकerrupt.
 *
 * - irq_set_affinity is used to move a VPE from one redistributor to
 *   another.
 *
 * - irq_set_vcpu_affinity once again माला_लो hijacked क्रम the purpose of
 *   creating a new sub-API, namely scheduling/descheduling a VPE
 *   (which involves programming GICR_VअणुPROP,PENDपूर्णBASER) and
 *   perक्रमming INVALL operations.
 */

अटल काष्ठा irq_करोमुख्य *gic_करोमुख्य;
अटल स्थिर काष्ठा irq_करोमुख्य_ops *vpe_करोमुख्य_ops;
अटल स्थिर काष्ठा irq_करोमुख्य_ops *sgi_करोमुख्य_ops;

#अगर_घोषित CONFIG_ARM64
#समावेश <यंत्र/cpufeature.h>

bool gic_cpuअगर_has_vsgi(व्योम)
अणु
	अचिन्हित दीर्घ fld, reg = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64PFR0_EL1);

	fld = cpuid_feature_extract_अचिन्हित_field(reg, ID_AA64PFR0_GIC_SHIFT);

	वापस fld >= 0x3;
पूर्ण
#अन्यथा
bool gic_cpuअगर_has_vsgi(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल bool has_v4_1(व्योम)
अणु
	वापस !!sgi_करोमुख्य_ops;
पूर्ण

अटल bool has_v4_1_sgi(व्योम)
अणु
	वापस has_v4_1() && gic_cpuअगर_has_vsgi();
पूर्ण

अटल पूर्णांक its_alloc_vcpu_sgis(काष्ठा its_vpe *vpe, पूर्णांक idx)
अणु
	अक्षर *name;
	पूर्णांक sgi_base;

	अगर (!has_v4_1_sgi())
		वापस 0;

	name = kaप्र_लिखो(GFP_KERNEL, "GICv4-sgi-%d", task_pid_nr(current));
	अगर (!name)
		जाओ err;

	vpe->fwnode = irq_करोमुख्य_alloc_named_id_fwnode(name, idx);
	अगर (!vpe->fwnode)
		जाओ err;

	kमुक्त(name);
	name = शून्य;

	vpe->sgi_करोमुख्य = irq_करोमुख्य_create_linear(vpe->fwnode, 16,
						   sgi_करोमुख्य_ops, vpe);
	अगर (!vpe->sgi_करोमुख्य)
		जाओ err;

	sgi_base = __irq_करोमुख्य_alloc_irqs(vpe->sgi_करोमुख्य, -1, 16,
					       NUMA_NO_NODE, vpe,
					       false, शून्य);
	अगर (sgi_base <= 0)
		जाओ err;

	वापस 0;

err:
	अगर (vpe->sgi_करोमुख्य)
		irq_करोमुख्य_हटाओ(vpe->sgi_करोमुख्य);
	अगर (vpe->fwnode)
		irq_करोमुख्य_मुक्त_fwnode(vpe->fwnode);
	kमुक्त(name);
	वापस -ENOMEM;
पूर्ण

पूर्णांक its_alloc_vcpu_irqs(काष्ठा its_vm *vm)
अणु
	पूर्णांक vpe_base_irq, i;

	vm->fwnode = irq_करोमुख्य_alloc_named_id_fwnode("GICv4-vpe",
						      task_pid_nr(current));
	अगर (!vm->fwnode)
		जाओ err;

	vm->करोमुख्य = irq_करोमुख्य_create_hierarchy(gic_करोमुख्य, 0, vm->nr_vpes,
						 vm->fwnode, vpe_करोमुख्य_ops,
						 vm);
	अगर (!vm->करोमुख्य)
		जाओ err;

	क्रम (i = 0; i < vm->nr_vpes; i++) अणु
		vm->vpes[i]->its_vm = vm;
		vm->vpes[i]->idai = true;
	पूर्ण

	vpe_base_irq = __irq_करोमुख्य_alloc_irqs(vm->करोमुख्य, -1, vm->nr_vpes,
					       NUMA_NO_NODE, vm,
					       false, शून्य);
	अगर (vpe_base_irq <= 0)
		जाओ err;

	क्रम (i = 0; i < vm->nr_vpes; i++) अणु
		पूर्णांक ret;
		vm->vpes[i]->irq = vpe_base_irq + i;
		ret = its_alloc_vcpu_sgis(vm->vpes[i], i);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	अगर (vm->करोमुख्य)
		irq_करोमुख्य_हटाओ(vm->करोमुख्य);
	अगर (vm->fwnode)
		irq_करोमुख्य_मुक्त_fwnode(vm->fwnode);

	वापस -ENOMEM;
पूर्ण

अटल व्योम its_मुक्त_sgi_irqs(काष्ठा its_vm *vm)
अणु
	पूर्णांक i;

	अगर (!has_v4_1_sgi())
		वापस;

	क्रम (i = 0; i < vm->nr_vpes; i++) अणु
		अचिन्हित पूर्णांक irq = irq_find_mapping(vm->vpes[i]->sgi_करोमुख्य, 0);

		अगर (WARN_ON(!irq))
			जारी;

		irq_करोमुख्य_मुक्त_irqs(irq, 16);
		irq_करोमुख्य_हटाओ(vm->vpes[i]->sgi_करोमुख्य);
		irq_करोमुख्य_मुक्त_fwnode(vm->vpes[i]->fwnode);
	पूर्ण
पूर्ण

व्योम its_मुक्त_vcpu_irqs(काष्ठा its_vm *vm)
अणु
	its_मुक्त_sgi_irqs(vm);
	irq_करोमुख्य_मुक्त_irqs(vm->vpes[0]->irq, vm->nr_vpes);
	irq_करोमुख्य_हटाओ(vm->करोमुख्य);
	irq_करोमुख्य_मुक्त_fwnode(vm->fwnode);
पूर्ण

अटल पूर्णांक its_send_vpe_cmd(काष्ठा its_vpe *vpe, काष्ठा its_cmd_info *info)
अणु
	वापस irq_set_vcpu_affinity(vpe->irq, info);
पूर्ण

पूर्णांक its_make_vpe_non_resident(काष्ठा its_vpe *vpe, bool db)
अणु
	काष्ठा irq_desc *desc = irq_to_desc(vpe->irq);
	काष्ठा its_cmd_info info = अणु पूर्ण;
	पूर्णांक ret;

	WARN_ON(preemptible());

	info.cmd_type = DESCHEDULE_VPE;
	अगर (has_v4_1()) अणु
		/* GICv4.1 can directly deal with करोorbells */
		info.req_db = db;
	पूर्ण अन्यथा अणु
		/* Unकरो the nested disable_irq() calls... */
		जबतक (db && irqd_irq_disabled(&desc->irq_data))
			enable_irq(vpe->irq);
	पूर्ण

	ret = its_send_vpe_cmd(vpe, &info);
	अगर (!ret)
		vpe->resident = false;

	vpe->पढ़ोy = false;

	वापस ret;
पूर्ण

पूर्णांक its_make_vpe_resident(काष्ठा its_vpe *vpe, bool g0en, bool g1en)
अणु
	काष्ठा its_cmd_info info = अणु पूर्ण;
	पूर्णांक ret;

	WARN_ON(preemptible());

	info.cmd_type = SCHEDULE_VPE;
	अगर (has_v4_1()) अणु
		info.g0en = g0en;
		info.g1en = g1en;
	पूर्ण अन्यथा अणु
		/* Disabled the करोorbell, as we're about to enter the guest */
		disable_irq_nosync(vpe->irq);
	पूर्ण

	ret = its_send_vpe_cmd(vpe, &info);
	अगर (!ret)
		vpe->resident = true;

	वापस ret;
पूर्ण

पूर्णांक its_commit_vpe(काष्ठा its_vpe *vpe)
अणु
	काष्ठा its_cmd_info info = अणु
		.cmd_type = COMMIT_VPE,
	पूर्ण;
	पूर्णांक ret;

	WARN_ON(preemptible());

	ret = its_send_vpe_cmd(vpe, &info);
	अगर (!ret)
		vpe->पढ़ोy = true;

	वापस ret;
पूर्ण


पूर्णांक its_invall_vpe(काष्ठा its_vpe *vpe)
अणु
	काष्ठा its_cmd_info info = अणु
		.cmd_type = INVALL_VPE,
	पूर्ण;

	वापस its_send_vpe_cmd(vpe, &info);
पूर्ण

पूर्णांक its_map_vlpi(पूर्णांक irq, काष्ठा its_vlpi_map *map)
अणु
	काष्ठा its_cmd_info info = अणु
		.cmd_type = MAP_VLPI,
		अणु
			.map      = map,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	/*
	 * The host will never see that पूर्णांकerrupt firing again, so it
	 * is vital that we करोn't करो any lazy masking.
	 */
	irq_set_status_flags(irq, IRQ_DISABLE_UNLAZY);

	ret = irq_set_vcpu_affinity(irq, &info);
	अगर (ret)
		irq_clear_status_flags(irq, IRQ_DISABLE_UNLAZY);

	वापस ret;
पूर्ण

पूर्णांक its_get_vlpi(पूर्णांक irq, काष्ठा its_vlpi_map *map)
अणु
	काष्ठा its_cmd_info info = अणु
		.cmd_type = GET_VLPI,
		अणु
			.map      = map,
		पूर्ण,
	पूर्ण;

	वापस irq_set_vcpu_affinity(irq, &info);
पूर्ण

पूर्णांक its_unmap_vlpi(पूर्णांक irq)
अणु
	irq_clear_status_flags(irq, IRQ_DISABLE_UNLAZY);
	वापस irq_set_vcpu_affinity(irq, शून्य);
पूर्ण

पूर्णांक its_prop_update_vlpi(पूर्णांक irq, u8 config, bool inv)
अणु
	काष्ठा its_cmd_info info = अणु
		.cmd_type = inv ? PROP_UPDATE_AND_INV_VLPI : PROP_UPDATE_VLPI,
		अणु
			.config   = config,
		पूर्ण,
	पूर्ण;

	वापस irq_set_vcpu_affinity(irq, &info);
पूर्ण

पूर्णांक its_prop_update_vsgi(पूर्णांक irq, u8 priority, bool group)
अणु
	काष्ठा its_cmd_info info = अणु
		.cmd_type = PROP_UPDATE_VSGI,
		अणु
			.priority	= priority,
			.group		= group,
		पूर्ण,
	पूर्ण;

	वापस irq_set_vcpu_affinity(irq, &info);
पूर्ण

पूर्णांक its_init_v4(काष्ठा irq_करोमुख्य *करोमुख्य,
		स्थिर काष्ठा irq_करोमुख्य_ops *vpe_ops,
		स्थिर काष्ठा irq_करोमुख्य_ops *sgi_ops)
अणु
	अगर (करोमुख्य) अणु
		pr_info("ITS: Enabling GICv4 support\n");
		gic_करोमुख्य = करोमुख्य;
		vpe_करोमुख्य_ops = vpe_ops;
		sgi_करोमुख्य_ops = sgi_ops;
		वापस 0;
	पूर्ण

	pr_err("ITS: No GICv4 VPE domain allocated\n");
	वापस -ENODEV;
पूर्ण
