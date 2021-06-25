<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/cpumask.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/msi.h>
#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/hpet.h>

#समावेश "irq_remapping.h"

पूर्णांक irq_remapping_enabled;
पूर्णांक irq_remap_broken;
पूर्णांक disable_sourceid_checking;
पूर्णांक no_x2apic_optout;

पूर्णांक disable_irq_post = 0;

अटल पूर्णांक disable_irq_remap;
अटल काष्ठा irq_remap_ops *remap_ops;

अटल व्योम irq_remapping_restore_boot_irq_mode(व्योम)
अणु
	/*
	 * With पूर्णांकerrupt-remapping, क्रम now we will use भव wire A
	 * mode, as भव wire B is little complex (need to configure
	 * both IOAPIC RTE as well as पूर्णांकerrupt-remapping table entry).
	 * As this माला_लो called during crash dump, keep this simple क्रम
	 * now.
	 */
	अगर (boot_cpu_has(X86_FEATURE_APIC) || apic_from_smp_config())
		disconnect_bsp_APIC(0);
पूर्ण

अटल व्योम __init irq_remapping_modअगरy_x86_ops(व्योम)
अणु
	x86_apic_ops.restore = irq_remapping_restore_boot_irq_mode;
पूर्ण

अटल __init पूर्णांक setup_noपूर्णांकremap(अक्षर *str)
अणु
	disable_irq_remap = 1;
	वापस 0;
पूर्ण
early_param("nointremap", setup_noपूर्णांकremap);

अटल __init पूर्णांक setup_irqremap(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;

	जबतक (*str) अणु
		अगर (!म_भेदन(str, "on", 2)) अणु
			disable_irq_remap = 0;
			disable_irq_post = 0;
		पूर्ण अन्यथा अगर (!म_भेदन(str, "off", 3)) अणु
			disable_irq_remap = 1;
			disable_irq_post = 1;
		पूर्ण अन्यथा अगर (!म_भेदन(str, "nosid", 5))
			disable_sourceid_checking = 1;
		अन्यथा अगर (!म_भेदन(str, "no_x2apic_optout", 16))
			no_x2apic_optout = 1;
		अन्यथा अगर (!म_भेदन(str, "nopost", 6))
			disable_irq_post = 1;

		str += म_खोज(str, ",");
		जबतक (*str == ',')
			str++;
	पूर्ण

	वापस 0;
पूर्ण
early_param("intremap", setup_irqremap);

व्योम set_irq_remapping_broken(व्योम)
अणु
	irq_remap_broken = 1;
पूर्ण

bool irq_remapping_cap(क्रमागत irq_remap_cap cap)
अणु
	अगर (!remap_ops || disable_irq_post)
		वापस false;

	वापस (remap_ops->capability & (1 << cap));
पूर्ण
EXPORT_SYMBOL_GPL(irq_remapping_cap);

पूर्णांक __init irq_remapping_prepare(व्योम)
अणु
	अगर (disable_irq_remap)
		वापस -ENOSYS;

	अगर (पूर्णांकel_irq_remap_ops.prepare() == 0)
		remap_ops = &पूर्णांकel_irq_remap_ops;
	अन्यथा अगर (IS_ENABLED(CONFIG_AMD_IOMMU) &&
		 amd_iommu_irq_ops.prepare() == 0)
		remap_ops = &amd_iommu_irq_ops;
	अन्यथा अगर (IS_ENABLED(CONFIG_HYPERV_IOMMU) &&
		 hyperv_irq_remap_ops.prepare() == 0)
		remap_ops = &hyperv_irq_remap_ops;
	अन्यथा
		वापस -ENOSYS;

	वापस 0;
पूर्ण

पूर्णांक __init irq_remapping_enable(व्योम)
अणु
	पूर्णांक ret;

	अगर (!remap_ops->enable)
		वापस -ENODEV;

	ret = remap_ops->enable();

	अगर (irq_remapping_enabled)
		irq_remapping_modअगरy_x86_ops();

	वापस ret;
पूर्ण

व्योम irq_remapping_disable(व्योम)
अणु
	अगर (irq_remapping_enabled && remap_ops->disable)
		remap_ops->disable();
पूर्ण

पूर्णांक irq_remapping_reenable(पूर्णांक mode)
अणु
	अगर (irq_remapping_enabled && remap_ops->reenable)
		वापस remap_ops->reenable(mode);

	वापस 0;
पूर्ण

पूर्णांक __init irq_remap_enable_fault_handling(व्योम)
अणु
	अगर (!irq_remapping_enabled)
		वापस 0;

	अगर (!remap_ops->enable_faulting)
		वापस -ENODEV;

	वापस remap_ops->enable_faulting();
पूर्ण

व्योम panic_अगर_irq_remap(स्थिर अक्षर *msg)
अणु
	अगर (irq_remapping_enabled)
		panic(msg);
पूर्ण
