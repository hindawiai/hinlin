<शैली गुरु>
/*
 * Populate sysfs with topology inक्रमmation
 *
 * Written by: Matthew Dobson, IBM Corporation
 * Original Code: Paul Dorwin, IBM Corporation, Patrick Mochel, OSDL
 *
 * Copyright (C) 2002, IBM Corp.
 *
 * All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Send feedback to <colpatch@us.ibm.com>
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/export.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/cpu.h>

अटल DEFINE_PER_CPU(काष्ठा x86_cpu, cpu_devices);

#अगर_घोषित CONFIG_HOTPLUG_CPU

#अगर_घोषित CONFIG_BOOTPARAM_HOTPLUG_CPU0
अटल पूर्णांक cpu0_hotpluggable = 1;
#अन्यथा
अटल पूर्णांक cpu0_hotpluggable;
अटल पूर्णांक __init enable_cpu0_hotplug(अक्षर *str)
अणु
	cpu0_hotpluggable = 1;
	वापस 1;
पूर्ण

__setup("cpu0_hotplug", enable_cpu0_hotplug);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_HOTPLUG_CPU0
/*
 * This function offlines a CPU as early as possible and allows userspace to
 * boot up without the CPU. The CPU can be onlined back by user after boot.
 *
 * This is only called क्रम debugging CPU offline/online feature.
 */
पूर्णांक _debug_hotplug_cpu(पूर्णांक cpu, पूर्णांक action)
अणु
	पूर्णांक ret;

	अगर (!cpu_is_hotpluggable(cpu))
		वापस -EINVAL;

	चयन (action) अणु
	हाल 0:
		ret = हटाओ_cpu(cpu);
		अगर (!ret)
			pr_info("DEBUG_HOTPLUG_CPU0: CPU %u is now offline\n", cpu);
		अन्यथा
			pr_debug("Can't offline CPU%d.\n", cpu);
		अवरोध;
	हाल 1:
		ret = add_cpu(cpu);
		अगर (ret)
			pr_debug("Can't online CPU%d.\n", cpu);

		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init debug_hotplug_cpu(व्योम)
अणु
	_debug_hotplug_cpu(0, 0);
	वापस 0;
पूर्ण

late_initcall_sync(debug_hotplug_cpu);
#पूर्ण_अगर /* CONFIG_DEBUG_HOTPLUG_CPU0 */

पूर्णांक arch_रेजिस्टर_cpu(पूर्णांक num)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(num);

	/*
	 * Currently CPU0 is only hotpluggable on Intel platक्रमms. Other
	 * venकरोrs can add hotplug support later.
	 * Xen PV guests करोn't support CPU0 hotplug at all.
	 */
	अगर (c->x86_venकरोr != X86_VENDOR_INTEL ||
	    boot_cpu_has(X86_FEATURE_XENPV))
		cpu0_hotpluggable = 0;

	/*
	 * Two known BSP/CPU0 dependencies: Resume from suspend/hibernate
	 * depends on BSP. PIC पूर्णांकerrupts depend on BSP.
	 *
	 * If the BSP dependencies are under control, one can tell kernel to
	 * enable BSP hotplug. This basically adds a control file and
	 * one can attempt to offline BSP.
	 */
	अगर (num == 0 && cpu0_hotpluggable) अणु
		अचिन्हित पूर्णांक irq;
		/*
		 * We won't take करोwn the boot processor on i386 अगर some
		 * पूर्णांकerrupts only are able to be serviced by the BSP in PIC.
		 */
		क्रम_each_active_irq(irq) अणु
			अगर (!IO_APIC_IRQ(irq) && irq_has_action(irq)) अणु
				cpu0_hotpluggable = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (num || cpu0_hotpluggable)
		per_cpu(cpu_devices, num).cpu.hotpluggable = 1;

	वापस रेजिस्टर_cpu(&per_cpu(cpu_devices, num).cpu, num);
पूर्ण
EXPORT_SYMBOL(arch_रेजिस्टर_cpu);

व्योम arch_unरेजिस्टर_cpu(पूर्णांक num)
अणु
	unरेजिस्टर_cpu(&per_cpu(cpu_devices, num).cpu);
पूर्ण
EXPORT_SYMBOL(arch_unरेजिस्टर_cpu);
#अन्यथा /* CONFIG_HOTPLUG_CPU */

अटल पूर्णांक __init arch_रेजिस्टर_cpu(पूर्णांक num)
अणु
	वापस रेजिस्टर_cpu(&per_cpu(cpu_devices, num).cpu, num);
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

अटल पूर्णांक __init topology_init(व्योम)
अणु
	पूर्णांक i;

#अगर_घोषित CONFIG_NUMA
	क्रम_each_online_node(i)
		रेजिस्टर_one_node(i);
#पूर्ण_अगर

	क्रम_each_present_cpu(i)
		arch_रेजिस्टर_cpu(i);

	वापस 0;
पूर्ण
subsys_initcall(topology_init);
