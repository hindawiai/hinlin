<शैली गुरु>
/*
 * CCI cache coherent पूर्णांकerconnect driver
 *
 * Copyright (C) 2013 ARM Ltd.
 * Author: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/arm-cci.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>

अटल व्योम __iomem *cci_ctrl_base __ro_after_init;
अटल अचिन्हित दीर्घ cci_ctrl_phys __ro_after_init;

#अगर_घोषित CONFIG_ARM_CCI400_PORT_CTRL
काष्ठा cci_nb_ports अणु
	अचिन्हित पूर्णांक nb_ace;
	अचिन्हित पूर्णांक nb_ace_lite;
पूर्ण;

अटल स्थिर काष्ठा cci_nb_ports cci400_ports = अणु
	.nb_ace = 2,
	.nb_ace_lite = 3
पूर्ण;

#घोषणा CCI400_PORTS_DATA	(&cci400_ports)
#अन्यथा
#घोषणा CCI400_PORTS_DATA	(शून्य)
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id arm_cci_matches[] = अणु
#अगर_घोषित CONFIG_ARM_CCI400_COMMON
	अणु.compatible = "arm,cci-400", .data = CCI400_PORTS_DATA पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM_CCI5xx_PMU
	अणु .compatible = "arm,cci-500", पूर्ण,
	अणु .compatible = "arm,cci-550", पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_dev_auxdata arm_cci_auxdata[] = अणु
	OF_DEV_AUXDATA("arm,cci-400-pmu", 0, शून्य, &cci_ctrl_base),
	OF_DEV_AUXDATA("arm,cci-400-pmu,r0", 0, शून्य, &cci_ctrl_base),
	OF_DEV_AUXDATA("arm,cci-400-pmu,r1", 0, शून्य, &cci_ctrl_base),
	OF_DEV_AUXDATA("arm,cci-500-pmu,r0", 0, शून्य, &cci_ctrl_base),
	OF_DEV_AUXDATA("arm,cci-550-pmu,r0", 0, शून्य, &cci_ctrl_base),
	अणुपूर्ण
पूर्ण;

#घोषणा DRIVER_NAME		"ARM-CCI"

अटल पूर्णांक cci_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (!cci_probed())
		वापस -ENODEV;

	वापस of_platक्रमm_populate(pdev->dev.of_node, शून्य,
				    arm_cci_auxdata, &pdev->dev);
पूर्ण

अटल काष्ठा platक्रमm_driver cci_platक्रमm_driver = अणु
	.driver = अणु
		   .name = DRIVER_NAME,
		   .of_match_table = arm_cci_matches,
		  पूर्ण,
	.probe = cci_platक्रमm_probe,
पूर्ण;

अटल पूर्णांक __init cci_platक्रमm_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&cci_platक्रमm_driver);
पूर्ण

#अगर_घोषित CONFIG_ARM_CCI400_PORT_CTRL

#घोषणा CCI_PORT_CTRL		0x0
#घोषणा CCI_CTRL_STATUS		0xc

#घोषणा CCI_ENABLE_SNOOP_REQ	0x1
#घोषणा CCI_ENABLE_DVM_REQ	0x2
#घोषणा CCI_ENABLE_REQ		(CCI_ENABLE_SNOOP_REQ | CCI_ENABLE_DVM_REQ)

क्रमागत cci_ace_port_type अणु
	ACE_INVALID_PORT = 0x0,
	ACE_PORT,
	ACE_LITE_PORT,
पूर्ण;

काष्ठा cci_ace_port अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ phys;
	क्रमागत cci_ace_port_type type;
	काष्ठा device_node *dn;
पूर्ण;

अटल काष्ठा cci_ace_port *ports;
अटल अचिन्हित पूर्णांक nb_cci_ports;

काष्ठा cpu_port अणु
	u64 mpidr;
	u32 port;
पूर्ण;

/*
 * Use the port MSB as valid flag, shअगरt can be made dynamic
 * by computing number of bits required क्रम port indexes.
 * Code disabling CCI cpu ports runs with D-cache invalidated
 * and SCTLR bit clear so data accesses must be kept to a minimum
 * to improve perक्रमmance; क्रम now shअगरt is left अटल to
 * aव्योम one more data access जबतक disabling the CCI port.
 */
#घोषणा PORT_VALID_SHIFT	31
#घोषणा PORT_VALID		(0x1 << PORT_VALID_SHIFT)

अटल अंतरभूत व्योम init_cpu_port(काष्ठा cpu_port *port, u32 index, u64 mpidr)
अणु
	port->port = PORT_VALID | index;
	port->mpidr = mpidr;
पूर्ण

अटल अंतरभूत bool cpu_port_is_valid(काष्ठा cpu_port *port)
अणु
	वापस !!(port->port & PORT_VALID);
पूर्ण

अटल अंतरभूत bool cpu_port_match(काष्ठा cpu_port *port, u64 mpidr)
अणु
	वापस port->mpidr == (mpidr & MPIDR_HWID_BITMASK);
पूर्ण

अटल काष्ठा cpu_port cpu_port[NR_CPUS];

/**
 * __cci_ace_get_port - Function to retrieve the port index connected to
 *			a cpu or device.
 *
 * @dn: device node of the device to look-up
 * @type: port type
 *
 * Return value:
 *	- CCI port index अगर success
 *	- -ENODEV अगर failure
 */
अटल पूर्णांक __cci_ace_get_port(काष्ठा device_node *dn, पूर्णांक type)
अणु
	पूर्णांक i;
	bool ace_match;
	काष्ठा device_node *cci_portn;

	cci_portn = of_parse_phandle(dn, "cci-control-port", 0);
	क्रम (i = 0; i < nb_cci_ports; i++) अणु
		ace_match = ports[i].type == type;
		अगर (ace_match && cci_portn == ports[i].dn)
			वापस i;
	पूर्ण
	वापस -ENODEV;
पूर्ण

पूर्णांक cci_ace_get_port(काष्ठा device_node *dn)
अणु
	वापस __cci_ace_get_port(dn, ACE_LITE_PORT);
पूर्ण
EXPORT_SYMBOL_GPL(cci_ace_get_port);

अटल व्योम cci_ace_init_ports(व्योम)
अणु
	पूर्णांक port, cpu;
	काष्ठा device_node *cpun;

	/*
	 * Port index look-up speeds up the function disabling ports by CPU,
	 * since the logical to port index mapping is करोne once and करोes
	 * not change after प्रणाली boot.
	 * The stashed index array is initialized क्रम all possible CPUs
	 * at probe समय.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		/* too early to use cpu->of_node */
		cpun = of_get_cpu_node(cpu, शून्य);

		अगर (WARN(!cpun, "Missing cpu device node\n"))
			जारी;

		port = __cci_ace_get_port(cpun, ACE_PORT);
		अगर (port < 0)
			जारी;

		init_cpu_port(&cpu_port[cpu], port, cpu_logical_map(cpu));
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		WARN(!cpu_port_is_valid(&cpu_port[cpu]),
			"CPU %u does not have an associated CCI port\n",
			cpu);
	पूर्ण
पूर्ण
/*
 * Functions to enable/disable a CCI पूर्णांकerconnect slave port
 *
 * They are called by low-level घातer management code to disable slave
 * पूर्णांकerfaces snoops and DVM broadcast.
 * Since they may execute with cache data allocation disabled and
 * after the caches have been cleaned and invalidated the functions provide
 * no explicit locking since they may run with D-cache disabled, so normal
 * cacheable kernel locks based on ldrex/strex may not work.
 * Locking has to be provided by BSP implementations to ensure proper
 * operations.
 */

/**
 * cci_port_control() - function to control a CCI port
 *
 * @port: index of the port to setup
 * @enable: अगर true enables the port, अगर false disables it
 */
अटल व्योम notrace cci_port_control(अचिन्हित पूर्णांक port, bool enable)
अणु
	व्योम __iomem *base = ports[port].base;

	ग_लिखोl_relaxed(enable ? CCI_ENABLE_REQ : 0, base + CCI_PORT_CTRL);
	/*
	 * This function is called from घातer करोwn procedures
	 * and must not execute any inकाष्ठाion that might
	 * cause the processor to be put in a quiescent state
	 * (eg wfi). Hence, cpu_relax() can not be added to this
	 * पढ़ो loop to optimize घातer, since it might hide possibly
	 * disruptive operations.
	 */
	जबतक (पढ़ोl_relaxed(cci_ctrl_base + CCI_CTRL_STATUS) & 0x1)
			;
पूर्ण

/**
 * cci_disable_port_by_cpu() - function to disable a CCI port by CPU
 *			       reference
 *
 * @mpidr: mpidr of the CPU whose CCI port should be disabled
 *
 * Disabling a CCI port क्रम a CPU implies disabling the CCI port
 * controlling that CPU cluster. Code disabling CPU CCI ports
 * must make sure that the CPU running the code is the last active CPU
 * in the cluster ie all other CPUs are quiescent in a low घातer state.
 *
 * Return:
 *	0 on success
 *	-ENODEV on port look-up failure
 */
पूर्णांक notrace cci_disable_port_by_cpu(u64 mpidr)
अणु
	पूर्णांक cpu;
	bool is_valid;
	क्रम (cpu = 0; cpu < nr_cpu_ids; cpu++) अणु
		is_valid = cpu_port_is_valid(&cpu_port[cpu]);
		अगर (is_valid && cpu_port_match(&cpu_port[cpu], mpidr)) अणु
			cci_port_control(cpu_port[cpu].port, false);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(cci_disable_port_by_cpu);

/**
 * cci_enable_port_क्रम_self() - enable a CCI port क्रम calling CPU
 *
 * Enabling a CCI port क्रम the calling CPU implies enabling the CCI
 * port controlling that CPU's cluster. Caller must make sure that the
 * CPU running the code is the first active CPU in the cluster and all
 * other CPUs are quiescent in a low घातer state  or रुकोing क्रम this CPU
 * to complete the CCI initialization.
 *
 * Because this is called when the MMU is still off and with no stack,
 * the code must be position independent and ideally rely on callee
 * clobbered रेजिस्टरs only.  To achieve this we must code this function
 * entirely in assembler.
 *
 * On success this वापसs with the proper CCI port enabled.  In हाल of
 * any failure this never वापसs as the inability to enable the CCI is
 * fatal and there is no possible recovery at this stage.
 */
यंत्रlinkage व्योम __naked cci_enable_port_क्रम_self(व्योम)
अणु
	यंत्र अस्थिर ("\n"
"	.arch armv7-a\n"
"	mrc	p15, 0, r0, c0, c0, 5	@ get MPIDR value \n"
"	and	r0, r0, #"__stringअगरy(MPIDR_HWID_BITMASK)" \n"
"	adr	r1, 5f \n"
"	ldr	r2, [r1] \n"
"	add	r1, r1, r2		@ &cpu_port \n"
"	add	ip, r1, %[sizeof_cpu_port] \n"

	/* Loop over the cpu_port array looking क्रम a matching MPIDR */
"1:	ldr	r2, [r1, %[offsetof_cpu_port_mpidr_lsb]] \n"
"	cmp	r2, r0 			@ compare MPIDR \n"
"	bne	2f \n"

	/* Found a match, now test port validity */
"	ldr	r3, [r1, %[offsetof_cpu_port_port]] \n"
"	tst	r3, #"__stringअगरy(PORT_VALID)" \n"
"	bne	3f \n"

	/* no match, loop with the next cpu_port entry */
"2:	add	r1, r1, %[sizeof_struct_cpu_port] \n"
"	cmp	r1, ip			@ done? \n"
"	blo	1b \n"

	/* CCI port not found -- cheaply try to stall this CPU */
"cci_port_not_found: \n"
"	wfi \n"
"	wfe \n"
"	b	cci_port_not_found \n"

	/* Use matched port index to look up the corresponding ports entry */
"3:	bic	r3, r3, #"__stringअगरy(PORT_VALID)" \n"
"	adr	r0, 6f \n"
"	ldmia	r0, {r1, r2} \n"
"	sub	r1, r1, r0 		@ virt - phys \n"
"	ldr	r0, [r0, r2] 		@ *(&ports) \n"
"	mov	r2, %[sizeof_struct_ace_port] \n"
"	mla	r0, r2, r3, r0		@ &ports[index] \n"
"	sub	r0, r0, r1		@ virt_to_phys() \n"

	/* Enable the CCI port */
"	ldr	r0, [r0, %[offsetof_port_phys]] \n"
"	mov	r3, %[cci_enable_req]\n"		   
"	str	r3, [r0, #"__stringअगरy(CCI_PORT_CTRL)"] \n"

	/* poll the status reg क्रम completion */
"	adr	r1, 7f \n"
"	ldr	r0, [r1] \n"
"	ldr	r0, [r0, r1]		@ cci_ctrl_base \n"
"4:	ldr	r1, [r0, #"__stringअगरy(CCI_CTRL_STATUS)"] \n"
"	tst	r1, %[cci_control_status_bits] \n"			
"	bne	4b \n"

"	mov	r0, #0 \n"
"	bx	lr \n"

"	.align	2 \n"
"5:	.word	cpu_port - . \n"
"6:	.word	. \n"
"	.word	ports - 6b \n"
"7:	.word	cci_ctrl_phys - . \n"
	: :
	[माप_cpu_port] "i" (माप(cpu_port)),
	[cci_enable_req] "i" cpu_to_le32(CCI_ENABLE_REQ),
	[cci_control_status_bits] "i" cpu_to_le32(1),
#अगर_अघोषित __ARMEB__
	[दुरत्व_cpu_port_mpidr_lsb] "i" (दुरत्व(काष्ठा cpu_port, mpidr)),
#अन्यथा
	[दुरत्व_cpu_port_mpidr_lsb] "i" (दुरत्व(काष्ठा cpu_port, mpidr)+4),
#पूर्ण_अगर
	[दुरत्व_cpu_port_port] "i" (दुरत्व(काष्ठा cpu_port, port)),
	[माप_काष्ठा_cpu_port] "i" (माप(काष्ठा cpu_port)),
	[माप_काष्ठा_ace_port] "i" (माप(काष्ठा cci_ace_port)),
	[दुरत्व_port_phys] "i" (दुरत्व(काष्ठा cci_ace_port, phys)) );
पूर्ण

/**
 * __cci_control_port_by_device() - function to control a CCI port by device
 *				    reference
 *
 * @dn: device node poपूर्णांकer of the device whose CCI port should be
 *      controlled
 * @enable: अगर true enables the port, अगर false disables it
 *
 * Return:
 *	0 on success
 *	-ENODEV on port look-up failure
 */
पूर्णांक notrace __cci_control_port_by_device(काष्ठा device_node *dn, bool enable)
अणु
	पूर्णांक port;

	अगर (!dn)
		वापस -ENODEV;

	port = __cci_ace_get_port(dn, ACE_LITE_PORT);
	अगर (WARN_ONCE(port < 0, "node %pOF ACE lite port look-up failure\n",
				dn))
		वापस -ENODEV;
	cci_port_control(port, enable);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__cci_control_port_by_device);

/**
 * __cci_control_port_by_index() - function to control a CCI port by port index
 *
 * @port: port index previously retrieved with cci_ace_get_port()
 * @enable: अगर true enables the port, अगर false disables it
 *
 * Return:
 *	0 on success
 *	-ENODEV on port index out of range
 *	-EPERM अगर operation carried out on an ACE PORT
 */
पूर्णांक notrace __cci_control_port_by_index(u32 port, bool enable)
अणु
	अगर (port >= nb_cci_ports || ports[port].type == ACE_INVALID_PORT)
		वापस -ENODEV;
	/*
	 * CCI control क्रम ports connected to CPUS is extremely fragile
	 * and must be made to go through a specअगरic and controlled
	 * पूर्णांकerface (ie cci_disable_port_by_cpu(); control by general purpose
	 * indexing is thereक्रमe disabled क्रम ACE ports.
	 */
	अगर (ports[port].type == ACE_PORT)
		वापस -EPERM;

	cci_port_control(port, enable);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__cci_control_port_by_index);

अटल स्थिर काष्ठा of_device_id arm_cci_ctrl_अगर_matches[] = अणु
	अणु.compatible = "arm,cci-400-ctrl-if", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक cci_probe_ports(काष्ठा device_node *np)
अणु
	काष्ठा cci_nb_ports स्थिर *cci_config;
	पूर्णांक ret, i, nb_ace = 0, nb_ace_lite = 0;
	काष्ठा device_node *cp;
	काष्ठा resource res;
	स्थिर अक्षर *match_str;
	bool is_ace;


	cci_config = of_match_node(arm_cci_matches, np)->data;
	अगर (!cci_config)
		वापस -ENODEV;

	nb_cci_ports = cci_config->nb_ace + cci_config->nb_ace_lite;

	ports = kसुस्मृति(nb_cci_ports, माप(*ports), GFP_KERNEL);
	अगर (!ports)
		वापस -ENOMEM;

	क्रम_each_available_child_of_node(np, cp) अणु
		अगर (!of_match_node(arm_cci_ctrl_अगर_matches, cp))
			जारी;

		i = nb_ace + nb_ace_lite;

		अगर (i >= nb_cci_ports)
			अवरोध;

		अगर (of_property_पढ़ो_string(cp, "interface-type",
					&match_str)) अणु
			WARN(1, "node %pOF missing interface-type property\n",
				  cp);
			जारी;
		पूर्ण
		is_ace = म_भेद(match_str, "ace") == 0;
		अगर (!is_ace && म_भेद(match_str, "ace-lite")) अणु
			WARN(1, "node %pOF containing invalid interface-type property, skipping it\n",
					cp);
			जारी;
		पूर्ण

		ret = of_address_to_resource(cp, 0, &res);
		अगर (!ret) अणु
			ports[i].base = ioremap(res.start, resource_size(&res));
			ports[i].phys = res.start;
		पूर्ण
		अगर (ret || !ports[i].base) अणु
			WARN(1, "unable to ioremap CCI port %d\n", i);
			जारी;
		पूर्ण

		अगर (is_ace) अणु
			अगर (WARN_ON(nb_ace >= cci_config->nb_ace))
				जारी;
			ports[i].type = ACE_PORT;
			++nb_ace;
		पूर्ण अन्यथा अणु
			अगर (WARN_ON(nb_ace_lite >= cci_config->nb_ace_lite))
				जारी;
			ports[i].type = ACE_LITE_PORT;
			++nb_ace_lite;
		पूर्ण
		ports[i].dn = cp;
	पूर्ण

	/*
	 * If there is no CCI port that is under kernel control
	 * वापस early and report probe status.
	 */
	अगर (!nb_ace && !nb_ace_lite)
		वापस -ENODEV;

	 /* initialize a stashed array of ACE ports to speed-up look-up */
	cci_ace_init_ports();

	/*
	 * Multi-cluster प्रणालीs may need this data when non-coherent, during
	 * cluster घातer-up/घातer-करोwn. Make sure it reaches मुख्य memory.
	 */
	sync_cache_w(&cci_ctrl_base);
	sync_cache_w(&cci_ctrl_phys);
	sync_cache_w(&ports);
	sync_cache_w(&cpu_port);
	__sync_cache_range_w(ports, माप(*ports) * nb_cci_ports);
	pr_info("ARM CCI driver probed\n");

	वापस 0;
पूर्ण
#अन्यथा /* !CONFIG_ARM_CCI400_PORT_CTRL */
अटल अंतरभूत पूर्णांक cci_probe_ports(काष्ठा device_node *np)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM_CCI400_PORT_CTRL */

अटल पूर्णांक cci_probe(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा device_node *np;
	काष्ठा resource res;

	np = of_find_matching_node(शून्य, arm_cci_matches);
	अगर (!of_device_is_available(np))
		वापस -ENODEV;

	ret = of_address_to_resource(np, 0, &res);
	अगर (!ret) अणु
		cci_ctrl_base = ioremap(res.start, resource_size(&res));
		cci_ctrl_phys =	res.start;
	पूर्ण
	अगर (ret || !cci_ctrl_base) अणु
		WARN(1, "unable to ioremap CCI ctrl\n");
		वापस -ENXIO;
	पूर्ण

	वापस cci_probe_ports(np);
पूर्ण

अटल पूर्णांक cci_init_status = -EAGAIN;
अटल DEFINE_MUTEX(cci_probing);

अटल पूर्णांक cci_init(व्योम)
अणु
	अगर (cci_init_status != -EAGAIN)
		वापस cci_init_status;

	mutex_lock(&cci_probing);
	अगर (cci_init_status == -EAGAIN)
		cci_init_status = cci_probe();
	mutex_unlock(&cci_probing);
	वापस cci_init_status;
पूर्ण

/*
 * To sort out early init calls ordering a helper function is provided to
 * check अगर the CCI driver has beed initialized. Function check अगर the driver
 * has been initialized, अगर not it calls the init function that probes
 * the driver and updates the वापस value.
 */
bool cci_probed(व्योम)
अणु
	वापस cci_init() == 0;
पूर्ण
EXPORT_SYMBOL_GPL(cci_probed);

early_initcall(cci_init);
core_initcall(cci_platक्रमm_init);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ARM CCI support");
