<शैली गुरु>
/*
 * Efika 5K2 platक्रमm code
 * Some code really inspired from the lite5200b platक्रमm.
 *
 * Copyright (C) 2006 bplan GmbH
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/init.h>
#समावेश <generated/utsrelease.h>
#समावेश <linux/pci.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/mpc52xx.h>

#घोषणा EFIKA_PLATFORM_NAME "Efika"


/* ------------------------------------------------------------------------ */
/* PCI accesses thru RTAS                                                   */
/* ------------------------------------------------------------------------ */

#अगर_घोषित CONFIG_PCI

/*
 * Access functions क्रम PCI config space using RTAS calls.
 */
अटल पूर्णांक rtas_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक offset,
			    पूर्णांक len, u32 * val)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	अचिन्हित दीर्घ addr = (offset & 0xff) | ((devfn & 0xff) << 8)
	    | (((bus->number - hose->first_busno) & 0xff) << 16)
	    | (hose->global_number << 24);
	पूर्णांक ret = -1;
	पूर्णांक rval;

	rval = rtas_call(rtas_token("read-pci-config"), 2, 2, &ret, addr, len);
	*val = ret;
	वापस rval ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक rtas_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक offset, पूर्णांक len, u32 val)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	अचिन्हित दीर्घ addr = (offset & 0xff) | ((devfn & 0xff) << 8)
	    | (((bus->number - hose->first_busno) & 0xff) << 16)
	    | (hose->global_number << 24);
	पूर्णांक rval;

	rval = rtas_call(rtas_token("write-pci-config"), 3, 1, शून्य,
			 addr, len, val);
	वापस rval ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops rtas_pci_ops = अणु
	.पढ़ो = rtas_पढ़ो_config,
	.ग_लिखो = rtas_ग_लिखो_config,
पूर्ण;


अटल व्योम __init efika_pcisetup(व्योम)
अणु
	स्थिर पूर्णांक *bus_range;
	पूर्णांक len;
	काष्ठा pci_controller *hose;
	काष्ठा device_node *root;
	काष्ठा device_node *pcictrl;

	root = of_find_node_by_path("/");
	अगर (root == शून्य) अणु
		prपूर्णांकk(KERN_WARNING EFIKA_PLATFORM_NAME
		       ": Unable to find the root node\n");
		वापस;
	पूर्ण

	क्रम_each_child_of_node(root, pcictrl)
		अगर (of_node_name_eq(pcictrl, "pci"))
			अवरोध;

	of_node_put(root);

	अगर (pcictrl == शून्य) अणु
		prपूर्णांकk(KERN_WARNING EFIKA_PLATFORM_NAME
		       ": Unable to find the PCI bridge node\n");
		वापस;
	पूर्ण

	bus_range = of_get_property(pcictrl, "bus-range", &len);
	अगर (bus_range == शून्य || len < 2 * माप(पूर्णांक)) अणु
		prपूर्णांकk(KERN_WARNING EFIKA_PLATFORM_NAME
		       ": Can't get bus-range for %pOF\n", pcictrl);
		जाओ out_put;
	पूर्ण

	अगर (bus_range[1] == bus_range[0])
		prपूर्णांकk(KERN_INFO EFIKA_PLATFORM_NAME ": PCI bus %d",
		       bus_range[0]);
	अन्यथा
		prपूर्णांकk(KERN_INFO EFIKA_PLATFORM_NAME ": PCI buses %d..%d",
		       bus_range[0], bus_range[1]);
	prपूर्णांकk(" controlled by %pOF\n", pcictrl);
	prपूर्णांकk("\n");

	hose = pcibios_alloc_controller(pcictrl);
	अगर (!hose) अणु
		prपूर्णांकk(KERN_WARNING EFIKA_PLATFORM_NAME
		       ": Can't allocate PCI controller structure for %pOF\n",
		       pcictrl);
		जाओ out_put;
	पूर्ण

	hose->first_busno = bus_range[0];
	hose->last_busno = bus_range[1];
	hose->ops = &rtas_pci_ops;

	pci_process_bridge_OF_ranges(hose, pcictrl, 0);
	वापस;
out_put:
	of_node_put(pcictrl);
पूर्ण

#अन्यथा
अटल व्योम __init efika_pcisetup(व्योम)
अणुपूर्ण
#पूर्ण_अगर



/* ------------------------------------------------------------------------ */
/* Platक्रमm setup                                                           */
/* ------------------------------------------------------------------------ */

अटल व्योम efika_show_cpuinfo(काष्ठा seq_file *m)
अणु
	काष्ठा device_node *root;
	स्थिर अक्षर *revision;
	स्थिर अक्षर *codegendescription;
	स्थिर अक्षर *codegenvenकरोr;

	root = of_find_node_by_path("/");
	अगर (!root)
		वापस;

	revision = of_get_property(root, "revision", शून्य);
	codegendescription = of_get_property(root, "CODEGEN,description", शून्य);
	codegenvenकरोr = of_get_property(root, "CODEGEN,vendor", शून्य);

	अगर (codegendescription)
		seq_म_लिखो(m, "machine\t\t: %s\n", codegendescription);
	अन्यथा
		seq_म_लिखो(m, "machine\t\t: Efika\n");

	अगर (revision)
		seq_म_लिखो(m, "revision\t: %s\n", revision);

	अगर (codegenvenकरोr)
		seq_म_लिखो(m, "vendor\t\t: %s\n", codegenvenकरोr);

	of_node_put(root);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम efika_suspend_prepare(व्योम __iomem *mbar)
अणु
	u8 pin = 4;	/* GPIO_WKUP_4 (GPIO_PSC6_0 - IRDA_RX) */
	u8 level = 1;	/* wakeup on high level */
	/* IOW. to wake it up, लघु pins 1 and 3 on IRDA connector */
	mpc52xx_set_wakeup_gpio(pin, level);
पूर्ण
#पूर्ण_अगर

अटल व्योम __init efika_setup_arch(व्योम)
अणु
	rtas_initialize();

	/* Map important रेजिस्टरs from the पूर्णांकernal memory map */
	mpc52xx_map_common_devices();

#अगर_घोषित CONFIG_PM
	mpc52xx_suspend.board_suspend_prepare = efika_suspend_prepare;
	mpc52xx_pm_init();
#पूर्ण_अगर

	अगर (ppc_md.progress)
		ppc_md.progress("Linux/PPC " UTS_RELEASE " running on Efika ;-)\n", 0x0);
पूर्ण

अटल पूर्णांक __init efika_probe(व्योम)
अणु
	स्थिर अक्षर *model = of_get_property(of_root, "model", शून्य);

	अगर (model == शून्य)
		वापस 0;
	अगर (म_भेद(model, "EFIKA5K2"))
		वापस 0;

	DMA_MODE_READ = 0x44;
	DMA_MODE_WRITE = 0x48;

	pm_घातer_off = rtas_घातer_off;

	वापस 1;
पूर्ण

define_machine(efika)
अणु
	.name			= EFIKA_PLATFORM_NAME,
	.probe			= efika_probe,
	.setup_arch		= efika_setup_arch,
	.discover_phbs		= efika_pcisetup,
	.init			= mpc52xx_declare_of_platक्रमm_devices,
	.show_cpuinfo		= efika_show_cpuinfo,
	.init_IRQ		= mpc52xx_init_irq,
	.get_irq		= mpc52xx_get_irq,
	.restart		= rtas_restart,
	.halt			= rtas_halt,
	.set_rtc_समय		= rtas_set_rtc_समय,
	.get_rtc_समय		= rtas_get_rtc_समय,
	.progress		= rtas_progress,
	.get_boot_समय		= rtas_get_boot_समय,
	.calibrate_decr		= generic_calibrate_decr,
#अगर_घोषित CONFIG_PCI
	.phys_mem_access_prot	= pci_phys_mem_access_prot,
#पूर्ण_अगर
पूर्ण;

