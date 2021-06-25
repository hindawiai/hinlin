<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Procedures क्रम creating, accessing and पूर्णांकerpreting the device tree.
 *
 * Paul Mackerras	August 1996.
 * Copyright (C) 1996-2005 Paul Mackerras.
 * 
 *  Adapted क्रम 64bit PowerPC by Dave Engebretsen and Peter Bergner.
 *    अणुengebret|bergnerपूर्ण@us.ibm.com 
 *
 *  Adapted क्रम sparc64 by David S. Miller davem@davemloft.net
 */

#समावेश <linux/memblock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/cpu.h>
#समावेश <linux/mm.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/upa.h>
#समावेश <यंत्र/smp.h>

#समावेश "prom.h"

व्योम * __init prom_early_alloc(अचिन्हित दीर्घ size)
अणु
	व्योम *ret = memblock_alloc(size, SMP_CACHE_BYTES);

	अगर (!ret) अणु
		prom_म_लिखो("prom_early_alloc(%lu) failed\n", size);
		prom_halt();
	पूर्ण

	prom_early_allocated += size;

	वापस ret;
पूर्ण

/* The following routines deal with the black magic of fully naming a
 * node.
 *
 * Certain well known named nodes are just the simple name string.
 *
 * Actual devices have an address specअगरier appended to the base name
 * string, like this "foo@addr".  The "addr" can be in any number of
 * क्रमmats, and the platक्रमm plus the type of the node determine the
 * क्रमmat and how it is स्थिरructed.
 *
 * For children of the ROOT node, the naming convention is fixed and
 * determined by whether this is a sun4u or sun4v प्रणाली.
 *
 * For children of other nodes, it is bus type specअगरic.  So
 * we walk up the tree until we discover a "device_type" property
 * we recognize and we go from there.
 *
 * As an example, the boot device on my workstation has a full path:
 *
 *	/pci@1e,600000/ide@d/disk@0,0:c
 */
अटल व्योम __init sun4v_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा linux_prom64_रेजिस्टरs *regs;
	काष्ठा property *rprop;
	u32 high_bits, low_bits, type;

	rprop = of_find_property(dp, "reg", शून्य);
	अगर (!rprop)
		वापस;

	regs = rprop->value;
	अगर (!of_node_is_root(dp->parent)) अणु
		प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
			name,
			(अचिन्हित पूर्णांक) (regs->phys_addr >> 32UL),
			(अचिन्हित पूर्णांक) (regs->phys_addr & 0xffffffffUL));
		वापस;
	पूर्ण

	type = regs->phys_addr >> 60UL;
	high_bits = (regs->phys_addr >> 32UL) & 0x0fffffffUL;
	low_bits = (regs->phys_addr & 0xffffffffUL);

	अगर (type == 0 || type == 8) अणु
		स्थिर अक्षर *prefix = (type == 0) ? "m" : "i";

		अगर (low_bits)
			प्र_लिखो(पंचांगp_buf, "%s@%s%x,%x",
				name, prefix,
				high_bits, low_bits);
		अन्यथा
			प्र_लिखो(पंचांगp_buf, "%s@%s%x",
				name,
				prefix,
				high_bits);
	पूर्ण अन्यथा अगर (type == 12) अणु
		प्र_लिखो(पंचांगp_buf, "%s@%x",
			name, high_bits);
	पूर्ण
पूर्ण

अटल व्योम __init sun4u_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा linux_prom64_रेजिस्टरs *regs;
	काष्ठा property *prop;

	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop)
		वापस;

	regs = prop->value;
	अगर (!of_node_is_root(dp->parent)) अणु
		प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
			name,
			(अचिन्हित पूर्णांक) (regs->phys_addr >> 32UL),
			(अचिन्हित पूर्णांक) (regs->phys_addr & 0xffffffffUL));
		वापस;
	पूर्ण

	prop = of_find_property(dp, "upa-portid", शून्य);
	अगर (!prop)
		prop = of_find_property(dp, "portid", शून्य);
	अगर (prop) अणु
		अचिन्हित दीर्घ mask = 0xffffffffUL;

		अगर (tlb_type >= cheetah)
			mask = 0x7fffff;

		प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
			name,
			*(u32 *)prop->value,
			(अचिन्हित पूर्णांक) (regs->phys_addr & mask));
	पूर्ण
पूर्ण

/* "name@slot,offset"  */
अटल व्योम __init sbus_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा linux_prom_रेजिस्टरs *regs;
	काष्ठा property *prop;

	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop)
		वापस;

	regs = prop->value;
	प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
		name,
		regs->which_io,
		regs->phys_addr);
पूर्ण

/* "name@devnum[,func]" */
अटल व्योम __init pci_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा linux_prom_pci_रेजिस्टरs *regs;
	काष्ठा property *prop;
	अचिन्हित पूर्णांक devfn;

	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop)
		वापस;

	regs = prop->value;
	devfn = (regs->phys_hi >> 8) & 0xff;
	अगर (devfn & 0x07) अणु
		प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
			name,
			devfn >> 3,
			devfn & 0x07);
	पूर्ण अन्यथा अणु
		प्र_लिखो(पंचांगp_buf, "%s@%x",
			name,
			devfn >> 3);
	पूर्ण
पूर्ण

/* "name@UPA_PORTID,offset" */
अटल व्योम __init upa_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा linux_prom64_रेजिस्टरs *regs;
	काष्ठा property *prop;

	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop)
		वापस;

	regs = prop->value;

	prop = of_find_property(dp, "upa-portid", शून्य);
	अगर (!prop)
		वापस;

	प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
		name,
		*(u32 *) prop->value,
		(अचिन्हित पूर्णांक) (regs->phys_addr & 0xffffffffUL));
पूर्ण

/* "name@reg" */
अटल व्योम __init vdev_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा property *prop;
	u32 *regs;

	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop)
		वापस;

	regs = prop->value;

	प्र_लिखो(पंचांगp_buf, "%s@%x", name, *regs);
पूर्ण

/* "name@addrhi,addrlo" */
अटल व्योम __init ebus_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा linux_prom64_रेजिस्टरs *regs;
	काष्ठा property *prop;

	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop)
		वापस;

	regs = prop->value;

	प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
		name,
		(अचिन्हित पूर्णांक) (regs->phys_addr >> 32UL),
		(अचिन्हित पूर्णांक) (regs->phys_addr & 0xffffffffUL));
पूर्ण

/* "name@bus,addr" */
अटल व्योम __init i2c_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा property *prop;
	u32 *regs;

	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop)
		वापस;

	regs = prop->value;

	/* This actually isn't right... should look at the #address-cells
	 * property of the i2c bus node etc. etc.
	 */
	प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
		name, regs[0], regs[1]);
पूर्ण

/* "name@reg0[,reg1]" */
अटल व्योम __init usb_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा property *prop;
	u32 *regs;

	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop)
		वापस;

	regs = prop->value;

	अगर (prop->length == माप(u32) || regs[1] == 1) अणु
		प्र_लिखो(पंचांगp_buf, "%s@%x",
			name, regs[0]);
	पूर्ण अन्यथा अणु
		प्र_लिखो(पंचांगp_buf, "%s@%x,%x",
			name, regs[0], regs[1]);
	पूर्ण
पूर्ण

/* "name@reg0reg1[,reg2reg3]" */
अटल व्योम __init ieee1394_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	काष्ठा property *prop;
	u32 *regs;

	prop = of_find_property(dp, "reg", शून्य);
	अगर (!prop)
		वापस;

	regs = prop->value;

	अगर (regs[2] || regs[3]) अणु
		प्र_लिखो(पंचांगp_buf, "%s@%08x%08x,%04x%08x",
			name, regs[0], regs[1], regs[2], regs[3]);
	पूर्ण अन्यथा अणु
		प्र_लिखो(पंचांगp_buf, "%s@%08x%08x",
			name, regs[0], regs[1]);
	पूर्ण
पूर्ण

अटल व्योम __init __build_path_component(काष्ठा device_node *dp, अक्षर *पंचांगp_buf)
अणु
	काष्ठा device_node *parent = dp->parent;

	अगर (parent != शून्य) अणु
		अगर (of_node_is_type(parent, "pci") ||
		    of_node_is_type(parent, "pciex")) अणु
			pci_path_component(dp, पंचांगp_buf);
			वापस;
		पूर्ण
		अगर (of_node_is_type(parent, "sbus")) अणु
			sbus_path_component(dp, पंचांगp_buf);
			वापस;
		पूर्ण
		अगर (of_node_is_type(parent, "upa")) अणु
			upa_path_component(dp, पंचांगp_buf);
			वापस;
		पूर्ण
		अगर (of_node_is_type(parent, "ebus")) अणु
			ebus_path_component(dp, पंचांगp_buf);
			वापस;
		पूर्ण
		अगर (of_node_name_eq(parent, "usb") ||
		    of_node_name_eq(parent, "hub")) अणु
			usb_path_component(dp, पंचांगp_buf);
			वापस;
		पूर्ण
		अगर (of_node_is_type(parent, "i2c")) अणु
			i2c_path_component(dp, पंचांगp_buf);
			वापस;
		पूर्ण
		अगर (of_node_is_type(parent, "firewire")) अणु
			ieee1394_path_component(dp, पंचांगp_buf);
			वापस;
		पूर्ण
		अगर (of_node_is_type(parent, "virtual-devices")) अणु
			vdev_path_component(dp, पंचांगp_buf);
			वापस;
		पूर्ण
		/* "isa" is handled with platक्रमm naming */
	पूर्ण

	/* Use platक्रमm naming convention.  */
	अगर (tlb_type == hypervisor) अणु
		sun4v_path_component(dp, पंचांगp_buf);
		वापस;
	पूर्ण अन्यथा अणु
		sun4u_path_component(dp, पंचांगp_buf);
	पूर्ण
पूर्ण

अक्षर * __init build_path_component(काष्ठा device_node *dp)
अणु
	स्थिर अक्षर *name = of_get_property(dp, "name", शून्य);
	अक्षर पंचांगp_buf[64], *n;

	पंचांगp_buf[0] = '\0';
	__build_path_component(dp, पंचांगp_buf);
	अगर (पंचांगp_buf[0] == '\0')
		म_नकल(पंचांगp_buf, name);

	n = prom_early_alloc(म_माप(पंचांगp_buf) + 1);
	म_नकल(n, पंचांगp_buf);

	वापस n;
पूर्ण

अटल स्थिर अक्षर *get_mid_prop(व्योम)
अणु
	वापस (tlb_type == spitfire ? "upa-portid" : "portid");
पूर्ण

bool arch_find_n_match_cpu_physical_id(काष्ठा device_node *cpun,
				       पूर्णांक cpu, अचिन्हित पूर्णांक *thपढ़ो)
अणु
	स्थिर अक्षर *mid_prop = get_mid_prop();
	पूर्णांक this_cpu_id;

	/* On hypervisor based platक्रमms we पूर्णांकerrogate the 'reg'
	 * property.  On everything अन्यथा we look क्रम a 'upa-portid',
	 * 'portid', or 'cpuid' property.
	 */

	अगर (tlb_type == hypervisor) अणु
		काष्ठा property *prop = of_find_property(cpun, "reg", शून्य);
		u32 *regs;

		अगर (!prop) अणु
			pr_warn("CPU node missing reg property\n");
			वापस false;
		पूर्ण
		regs = prop->value;
		this_cpu_id = regs[0] & 0x0fffffff;
	पूर्ण अन्यथा अणु
		this_cpu_id = of_getपूर्णांकprop_शेष(cpun, mid_prop, -1);

		अगर (this_cpu_id < 0) अणु
			mid_prop = "cpuid";
			this_cpu_id = of_getपूर्णांकprop_शेष(cpun, mid_prop, -1);
		पूर्ण
		अगर (this_cpu_id < 0) अणु
			pr_warn("CPU node missing cpu ID property\n");
			वापस false;
		पूर्ण
	पूर्ण
	अगर (this_cpu_id == cpu) अणु
		अगर (thपढ़ो) अणु
			पूर्णांक proc_id = cpu_data(cpu).proc_id;

			/* On sparc64, the cpu thपढ़ो inक्रमmation is obtained
			 * either from OBP or the machine description.  We've
			 * actually probed this inक्रमmation alपढ़ोy दीर्घ beक्रमe
			 * this पूर्णांकerface माला_लो called so instead of पूर्णांकerrogating
			 * both the OF node and the MDESC again, just use what
			 * we discovered alपढ़ोy.
			 */
			अगर (proc_id < 0)
				proc_id = 0;
			*thपढ़ो = proc_id;
		पूर्ण
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम *of_iterate_over_cpus(व्योम *(*func)(काष्ठा device_node *, पूर्णांक, पूर्णांक), पूर्णांक arg)
अणु
	काष्ठा device_node *dp;
	स्थिर अक्षर *mid_prop;

	mid_prop = get_mid_prop();
	क्रम_each_node_by_type(dp, "cpu") अणु
		पूर्णांक cpuid = of_getपूर्णांकprop_शेष(dp, mid_prop, -1);
		स्थिर अक्षर *this_mid_prop = mid_prop;
		व्योम *ret;

		अगर (cpuid < 0) अणु
			this_mid_prop = "cpuid";
			cpuid = of_getपूर्णांकprop_शेष(dp, this_mid_prop, -1);
		पूर्ण
		अगर (cpuid < 0) अणु
			prom_म_लिखो("OF: Serious problem, cpu lacks "
				    "%s property", this_mid_prop);
			prom_halt();
		पूर्ण
#अगर_घोषित CONFIG_SMP
		अगर (cpuid >= NR_CPUS) अणु
			prपूर्णांकk(KERN_WARNING "Ignoring CPU %d which is "
			       ">= NR_CPUS (%d)\n",
			       cpuid, NR_CPUS);
			जारी;
		पूर्ण
#पूर्ण_अगर
		ret = func(dp, cpuid, arg);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *check_cpu_node(काष्ठा device_node *dp, पूर्णांक cpuid, पूर्णांक id)
अणु
	अगर (id == cpuid)
		वापस dp;
	वापस शून्य;
पूर्ण

काष्ठा device_node *of_find_node_by_cpuid(पूर्णांक cpuid)
अणु
	वापस of_iterate_over_cpus(check_cpu_node, cpuid);
पूर्ण

अटल व्योम *record_one_cpu(काष्ठा device_node *dp, पूर्णांक cpuid, पूर्णांक arg)
अणु
	ncpus_probed++;
#अगर_घोषित CONFIG_SMP
	set_cpu_present(cpuid, true);
	set_cpu_possible(cpuid, true);
#पूर्ण_अगर
	वापस शून्य;
पूर्ण

व्योम __init of_populate_present_mask(व्योम)
अणु
	अगर (tlb_type == hypervisor)
		वापस;

	ncpus_probed = 0;
	of_iterate_over_cpus(record_one_cpu, 0);
पूर्ण

अटल व्योम *fill_in_one_cpu(काष्ठा device_node *dp, पूर्णांक cpuid, पूर्णांक arg)
अणु
	काष्ठा device_node *portid_parent = शून्य;
	पूर्णांक portid = -1;

	अगर (of_find_property(dp, "cpuid", शून्य)) अणु
		पूर्णांक limit = 2;

		portid_parent = dp;
		जबतक (limit--) अणु
			portid_parent = portid_parent->parent;
			अगर (!portid_parent)
				अवरोध;
			portid = of_getपूर्णांकprop_शेष(portid_parent,
						       "portid", -1);
			अगर (portid >= 0)
				अवरोध;
		पूर्ण
	पूर्ण

#अगर_अघोषित CONFIG_SMP
	/* On uniprocessor we only want the values क्रम the
	 * real physical cpu the kernel booted onto, however
	 * cpu_data() only has one entry at index 0.
	 */
	अगर (cpuid != real_hard_smp_processor_id())
		वापस शून्य;
	cpuid = 0;
#पूर्ण_अगर

	cpu_data(cpuid).घड़ी_प्रकारick =
		of_getपूर्णांकprop_शेष(dp, "clock-frequency", 0);

	अगर (portid_parent) अणु
		cpu_data(cpuid).dcache_size =
			of_getपूर्णांकprop_शेष(dp, "l1-dcache-size",
					      16 * 1024);
		cpu_data(cpuid).dcache_line_size =
			of_getपूर्णांकprop_शेष(dp, "l1-dcache-line-size",
					      32);
		cpu_data(cpuid).icache_size =
			of_getपूर्णांकprop_शेष(dp, "l1-icache-size",
					      8 * 1024);
		cpu_data(cpuid).icache_line_size =
			of_getपूर्णांकprop_शेष(dp, "l1-icache-line-size",
					      32);
		cpu_data(cpuid).ecache_size =
			of_getपूर्णांकprop_शेष(dp, "l2-cache-size", 0);
		cpu_data(cpuid).ecache_line_size =
			of_getपूर्णांकprop_शेष(dp, "l2-cache-line-size", 0);
		अगर (!cpu_data(cpuid).ecache_size ||
		    !cpu_data(cpuid).ecache_line_size) अणु
			cpu_data(cpuid).ecache_size =
				of_getपूर्णांकprop_शेष(portid_parent,
						      "l2-cache-size",
						      (4 * 1024 * 1024));
			cpu_data(cpuid).ecache_line_size =
				of_getपूर्णांकprop_शेष(portid_parent,
						      "l2-cache-line-size", 64);
		पूर्ण

		cpu_data(cpuid).core_id = portid + 1;
		cpu_data(cpuid).proc_id = portid;
	पूर्ण अन्यथा अणु
		cpu_data(cpuid).dcache_size =
			of_getपूर्णांकprop_शेष(dp, "dcache-size", 16 * 1024);
		cpu_data(cpuid).dcache_line_size =
			of_getपूर्णांकprop_शेष(dp, "dcache-line-size", 32);

		cpu_data(cpuid).icache_size =
			of_getपूर्णांकprop_शेष(dp, "icache-size", 16 * 1024);
		cpu_data(cpuid).icache_line_size =
			of_getपूर्णांकprop_शेष(dp, "icache-line-size", 32);

		cpu_data(cpuid).ecache_size =
			of_getपूर्णांकprop_शेष(dp, "ecache-size",
					      (4 * 1024 * 1024));
		cpu_data(cpuid).ecache_line_size =
			of_getपूर्णांकprop_शेष(dp, "ecache-line-size", 64);

		cpu_data(cpuid).core_id = 0;
		cpu_data(cpuid).proc_id = -1;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम __init of_fill_in_cpu_data(व्योम)
अणु
	अगर (tlb_type == hypervisor)
		वापस;

	of_iterate_over_cpus(fill_in_one_cpu, 0);

	smp_fill_in_sib_core_maps();
पूर्ण

व्योम __init of_console_init(व्योम)
अणु
	अक्षर *msg = "OF stdout device is: %s\n";
	काष्ठा device_node *dp;
	phandle node;

	of_console_path = prom_early_alloc(256);
	अगर (prom_ihandle2path(prom_मानक_निकास, of_console_path, 256) < 0) अणु
		prom_म_लिखो("Cannot obtain path of stdout.\n");
		prom_halt();
	पूर्ण
	of_console_options = म_खोजप(of_console_path, ':');
	अगर (of_console_options) अणु
		of_console_options++;
		अगर (*of_console_options == '\0')
			of_console_options = शून्य;
	पूर्ण

	node = prom_inst2pkg(prom_मानक_निकास);
	अगर (!node) अणु
		prom_म_लिखो("Cannot resolve stdout node from "
			    "instance %08x.\n", prom_मानक_निकास);
		prom_halt();
	पूर्ण

	dp = of_find_node_by_phandle(node);

	अगर (!of_node_is_type(dp, "display") && !of_node_is_type(dp, "serial")) अणु
		prom_म_लिखो("Console device_type is neither display "
			    "nor serial.\n");
		prom_halt();
	पूर्ण

	of_console_device = dp;

	prपूर्णांकk(msg, of_console_path);
पूर्ण
