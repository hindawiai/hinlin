<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1995  Linus Torvalds
 *  Adapted from 'alpha' version by Gary Thomas
 *  Modअगरied by Cort Dougan (cort@cs.nmt.edu)
 */

/*
 * bootup setup stuff..
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/tty.h>
#समावेश <linux/major.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <generated/utsrelease.h>
#समावेश <linux/adb.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/console.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/initrd.h>
#समावेश <linux/समयr.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hydra.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/xmon.h>

#समावेश "chrp.h"
#समावेश "gg2.h"

व्योम rtas_indicator_progress(अक्षर *, अचिन्हित लघु);

पूर्णांक _chrp_type;
EXPORT_SYMBOL(_chrp_type);

अटल काष्ठा mpic *chrp_mpic;

/* Used क्रम करोing CHRP event-scans */
DEFINE_PER_CPU(काष्ठा समयr_list, heartbeat_समयr);
अचिन्हित दीर्घ event_scan_पूर्णांकerval;

बाह्य अचिन्हित दीर्घ loops_per_jअगरfy;

/* To be replaced by RTAS when available */
अटल अचिन्हित पूर्णांक __iomem *briq_SPOR;

#अगर_घोषित CONFIG_SMP
बाह्य काष्ठा smp_ops_t chrp_smp_ops;
#पूर्ण_अगर

अटल स्थिर अक्षर *gg2_memtypes[4] = अणु
	"FPM", "SDRAM", "EDO", "BEDO"
पूर्ण;
अटल स्थिर अक्षर *gg2_cachesizes[4] = अणु
	"256 KB", "512 KB", "1 MB", "Reserved"
पूर्ण;
अटल स्थिर अक्षर *gg2_cachetypes[4] = अणु
	"Asynchronous", "Reserved", "Flow-Through Synchronous",
	"Pipelined Synchronous"
पूर्ण;
अटल स्थिर अक्षर *gg2_cachemodes[4] = अणु
	"Disabled", "Write-Through", "Copy-Back", "Transparent Mode"
पूर्ण;

अटल स्थिर अक्षर *chrp_names[] = अणु
	"Unknown",
	"","","",
	"Motorola",
	"IBM or Longtrail",
	"Genesi Pegasos",
	"Total Impact Briq"
पूर्ण;

अटल व्योम chrp_show_cpuinfo(काष्ठा seq_file *m)
अणु
	पूर्णांक i, sdramen;
	अचिन्हित पूर्णांक t;
	काष्ठा device_node *root;
	स्थिर अक्षर *model = "";

	root = of_find_node_by_path("/");
	अगर (root)
		model = of_get_property(root, "model", शून्य);
	seq_म_लिखो(m, "machine\t\t: CHRP %s\n", model);

	/* दीर्घtrail (goldengate) stuff */
	अगर (model && !म_भेदन(model, "IBM,LongTrail", 13)) अणु
		/* VLSI VAS96011/12 `Golden Gate 2' */
		/* Memory banks */
		sdramen = (in_le32(gg2_pci_config_base + GG2_PCI_DRAM_CTRL)
			   >>31) & 1;
		क्रम (i = 0; i < (sdramen ? 4 : 6); i++) अणु
			t = in_le32(gg2_pci_config_base+
						 GG2_PCI_DRAM_BANK0+
						 i*4);
			अगर (!(t & 1))
				जारी;
			चयन ((t>>8) & 0x1f) अणु
			हाल 0x1f:
				model = "4 MB";
				अवरोध;
			हाल 0x1e:
				model = "8 MB";
				अवरोध;
			हाल 0x1c:
				model = "16 MB";
				अवरोध;
			हाल 0x18:
				model = "32 MB";
				अवरोध;
			हाल 0x10:
				model = "64 MB";
				अवरोध;
			हाल 0x00:
				model = "128 MB";
				अवरोध;
			शेष:
				model = "Reserved";
				अवरोध;
			पूर्ण
			seq_म_लिखो(m, "memory bank %d\t: %s %s\n", i, model,
				   gg2_memtypes[sdramen ? 1 : ((t>>1) & 3)]);
		पूर्ण
		/* L2 cache */
		t = in_le32(gg2_pci_config_base+GG2_PCI_CC_CTRL);
		seq_म_लिखो(m, "board l2\t: %s %s (%s)\n",
			   gg2_cachesizes[(t>>7) & 3],
			   gg2_cachetypes[(t>>2) & 3],
			   gg2_cachemodes[t & 3]);
	पूर्ण
	of_node_put(root);
पूर्ण

/*
 *  Fixes क्रम the National Semiconductor PC78308VUL SuperI/O
 *
 *  Some versions of Open Firmware incorrectly initialize the IRQ settings
 *  क्रम keyboard and mouse
 */
अटल अंतरभूत व्योम __init sio_ग_लिखो(u8 val, u8 index)
अणु
	outb(index, 0x15c);
	outb(val, 0x15d);
पूर्ण

अटल अंतरभूत u8 __init sio_पढ़ो(u8 index)
अणु
	outb(index, 0x15c);
	वापस inb(0x15d);
पूर्ण

अटल व्योम __init sio_fixup_irq(स्थिर अक्षर *name, u8 device, u8 level,
				     u8 type)
अणु
	u8 level0, type0, active;

	/* select logical device */
	sio_ग_लिखो(device, 0x07);
	active = sio_पढ़ो(0x30);
	level0 = sio_पढ़ो(0x70);
	type0 = sio_पढ़ो(0x71);
	अगर (level0 != level || type0 != type || !active) अणु
		prपूर्णांकk(KERN_WARNING "sio: %s irq level %d, type %d, %sactive: "
		       "remapping to level %d, type %d, active\n",
		       name, level0, type0, !active ? "in" : "", level, type);
		sio_ग_लिखो(0x01, 0x30);
		sio_ग_लिखो(level, 0x70);
		sio_ग_लिखो(type, 0x71);
	पूर्ण
पूर्ण

अटल व्योम __init sio_init(व्योम)
अणु
	काष्ठा device_node *root;
	स्थिर अक्षर *model;

	root = of_find_node_by_path("/");
	अगर (!root)
		वापस;

	model = of_get_property(root, "model", शून्य);
	अगर (model && !म_भेदन(model, "IBM,LongTrail", 13)) अणु
		/* logical device 0 (KBC/Keyboard) */
		sio_fixup_irq("keyboard", 0, 1, 2);
		/* select logical device 1 (KBC/Mouse) */
		sio_fixup_irq("mouse", 1, 12, 2);
	पूर्ण

	of_node_put(root);
पूर्ण


अटल व्योम __init pegasos_set_l2cr(व्योम)
अणु
	काष्ठा device_node *np;

	/* On Pegasos, enable the l2 cache अगर needed, as the OF क्रममाला_लो it */
	अगर (_chrp_type != _CHRP_Pegasos)
		वापस;

	/* Enable L2 cache अगर needed */
	np = of_find_node_by_type(शून्य, "cpu");
	अगर (np != शून्य) अणु
		स्थिर अचिन्हित पूर्णांक *l2cr = of_get_property(np, "l2cr", शून्य);
		अगर (l2cr == शून्य) अणु
			prपूर्णांकk ("Pegasos l2cr : no cpu l2cr property found\n");
			जाओ out;
		पूर्ण
		अगर (!((*l2cr) & 0x80000000)) अणु
			prपूर्णांकk ("Pegasos l2cr : L2 cache was not active, "
				"activating\n");
			_set_L2CR(0);
			_set_L2CR((*l2cr) | 0x80000000);
		पूर्ण
	पूर्ण
out:
	of_node_put(np);
पूर्ण

अटल व्योम __noवापस briq_restart(अक्षर *cmd)
अणु
	local_irq_disable();
	अगर (briq_SPOR)
		out_be32(briq_SPOR, 0);
	क्रम(;;);
पूर्ण

/*
 * Per शेष, input/output-device poपूर्णांकs to the keyboard/screen
 * If no card is installed, the built-in serial port is used as a fallback.
 * But unक्रमtunately, the firmware करोes not connect /chosen/अणुमानक_निवेश,मानक_निकासपूर्ण
 * the the built-in serial node. Instead, a /failsafe node is created.
 */
अटल __init व्योम chrp_init(व्योम)
अणु
	काष्ठा device_node *node;
	स्थिर अक्षर *property;

	अगर (म_माला(boot_command_line, "console="))
		वापस;
	/* find the boot console from /chosen/मानक_निकास */
	अगर (!of_chosen)
		वापस;
	node = of_find_node_by_path("/");
	अगर (!node)
		वापस;
	property = of_get_property(node, "model", शून्य);
	अगर (!property)
		जाओ out_put;
	अगर (म_भेद(property, "Pegasos2"))
		जाओ out_put;
	/* this is a Pegasos2 */
	property = of_get_property(of_chosen, "linux,stdout-path", शून्य);
	अगर (!property)
		जाओ out_put;
	of_node_put(node);
	node = of_find_node_by_path(property);
	अगर (!node)
		वापस;
	अगर (!of_node_is_type(node, "serial"))
		जाओ out_put;
	/*
	 * The 9pin connector is either /failsafe
	 * or /pci@80000000/isa@C/serial@i2F8
	 * The optional graphics card has also type 'serial' in VGA mode.
	 */
	अगर (of_node_name_eq(node, "failsafe") || of_node_name_eq(node, "serial"))
		add_preferred_console("ttyS", 0, शून्य);
out_put:
	of_node_put(node);
पूर्ण

अटल व्योम __init chrp_setup_arch(व्योम)
अणु
	काष्ठा device_node *root = of_find_node_by_path("/");
	स्थिर अक्षर *machine = शून्य;

	/* init to some ~sane value until calibrate_delay() runs */
	loops_per_jअगरfy = 50000000/HZ;

	अगर (root)
		machine = of_get_property(root, "model", शून्य);
	अगर (machine && म_भेदन(machine, "Pegasos", 7) == 0) अणु
		_chrp_type = _CHRP_Pegasos;
	पूर्ण अन्यथा अगर (machine && म_भेदन(machine, "IBM", 3) == 0) अणु
		_chrp_type = _CHRP_IBM;
	पूर्ण अन्यथा अगर (machine && म_भेदन(machine, "MOT", 3) == 0) अणु
		_chrp_type = _CHRP_Motorola;
	पूर्ण अन्यथा अगर (machine && म_भेदन(machine, "TotalImpact,BRIQ-1", 18) == 0) अणु
		_chrp_type = _CHRP_briq;
		/* Map the SPOR रेजिस्टर on briq and change the restart hook */
		briq_SPOR = ioremap(0xff0000e8, 4);
		ppc_md.restart = briq_restart;
	पूर्ण अन्यथा अणु
		/* Let's assume it is an IBM chrp अगर all अन्यथा fails */
		_chrp_type = _CHRP_IBM;
	पूर्ण
	of_node_put(root);
	prपूर्णांकk("chrp type = %x [%s]\n", _chrp_type, chrp_names[_chrp_type]);

	rtas_initialize();
	अगर (rtas_token("display-character") >= 0)
		ppc_md.progress = rtas_progress;

	/* use RTAS समय-of-day routines अगर available */
	अगर (rtas_token("get-time-of-day") != RTAS_UNKNOWN_SERVICE) अणु
		ppc_md.get_boot_समय	= rtas_get_boot_समय;
		ppc_md.get_rtc_समय	= rtas_get_rtc_समय;
		ppc_md.set_rtc_समय	= rtas_set_rtc_समय;
	पूर्ण

	/* On pegasos, enable the L2 cache अगर not alपढ़ोy करोne by OF */
	pegasos_set_l2cr();

	/*
	 *  Fix the Super I/O configuration
	 */
	sio_init();

	/*
	 * Prपूर्णांक the banner, then scroll करोwn so boot progress
	 * can be prपूर्णांकed.  -- Cort
	 */
	अगर (ppc_md.progress) ppc_md.progress("Linux/PPC "UTS_RELEASE"\n", 0x0);
पूर्ण

अटल व्योम chrp_8259_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक cascade_irq = i8259_irq();

	अगर (cascade_irq)
		generic_handle_irq(cascade_irq);

	chip->irq_eoi(&desc->irq_data);
पूर्ण

/*
 * Finds the खोलो-pic node and sets up the mpic driver.
 */
अटल व्योम __init chrp_find_खोलोpic(व्योम)
अणु
	काष्ठा device_node *np, *root;
	पूर्णांक len, i, j;
	पूर्णांक isu_size;
	स्थिर अचिन्हित पूर्णांक *iranges, *opprop = शून्य;
	पूर्णांक oplen = 0;
	अचिन्हित दीर्घ opaddr;
	पूर्णांक na = 1;

	np = of_find_node_by_type(शून्य, "open-pic");
	अगर (np == शून्य)
		वापस;
	root = of_find_node_by_path("/");
	अगर (root) अणु
		opprop = of_get_property(root, "platform-open-pic", &oplen);
		na = of_n_addr_cells(root);
	पूर्ण
	अगर (opprop && oplen >= na * माप(अचिन्हित पूर्णांक)) अणु
		opaddr = opprop[na-1];	/* assume 32-bit */
		oplen /= na * माप(अचिन्हित पूर्णांक);
	पूर्ण अन्यथा अणु
		काष्ठा resource r;
		अगर (of_address_to_resource(np, 0, &r)) अणु
			जाओ bail;
		पूर्ण
		opaddr = r.start;
		oplen = 0;
	पूर्ण

	prपूर्णांकk(KERN_INFO "OpenPIC at %lx\n", opaddr);

	iranges = of_get_property(np, "interrupt-ranges", &len);
	अगर (iranges == शून्य)
		len = 0;	/* non-distributed mpic */
	अन्यथा
		len /= 2 * माप(अचिन्हित पूर्णांक);

	/*
	 * The first pair of cells in पूर्णांकerrupt-ranges refers to the
	 * IDU; subsequent pairs refer to the ISUs.
	 */
	अगर (oplen < len) अणु
		prपूर्णांकk(KERN_ERR "Insufficient addresses for distributed"
		       " OpenPIC (%d < %d)\n", oplen, len);
		len = oplen;
	पूर्ण

	isu_size = 0;
	अगर (len > 0 && iranges[1] != 0) अणु
		prपूर्णांकk(KERN_INFO "OpenPIC irqs %d..%d in IDU\n",
		       iranges[0], iranges[0] + iranges[1] - 1);
	पूर्ण
	अगर (len > 1)
		isu_size = iranges[3];

	chrp_mpic = mpic_alloc(np, opaddr, MPIC_NO_RESET,
			isu_size, 0, " MPIC    ");
	अगर (chrp_mpic == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Failed to allocate MPIC structure\n");
		जाओ bail;
	पूर्ण
	j = na - 1;
	क्रम (i = 1; i < len; ++i) अणु
		iranges += 2;
		j += na;
		prपूर्णांकk(KERN_INFO "OpenPIC irqs %d..%d in ISU at %x\n",
		       iranges[0], iranges[0] + iranges[1] - 1,
		       opprop[j]);
		mpic_assign_isu(chrp_mpic, i - 1, opprop[j]);
	पूर्ण

	mpic_init(chrp_mpic);
	ppc_md.get_irq = mpic_get_irq;
 bail:
	of_node_put(root);
	of_node_put(np);
पूर्ण

अटल व्योम __init chrp_find_8259(व्योम)
अणु
	काष्ठा device_node *np, *pic = शून्य;
	अचिन्हित दीर्घ chrp_पूर्णांक_ack = 0;
	अचिन्हित पूर्णांक cascade_irq;

	/* Look क्रम cascade */
	क्रम_each_node_by_type(np, "interrupt-controller")
		अगर (of_device_is_compatible(np, "chrp,iic")) अणु
			pic = np;
			अवरोध;
		पूर्ण
	/* Ok, 8259 wasn't found. We need to handle the हाल where
	 * we have a pegasos that claims to be chrp but करोesn't have
	 * a proper पूर्णांकerrupt tree
	 */
	अगर (pic == शून्य && chrp_mpic != शून्य) अणु
		prपूर्णांकk(KERN_ERR "i8259: Not found in device-tree"
		       " assuming no legacy interrupts\n");
		वापस;
	पूर्ण

	/* Look क्रम पूर्णांकack. In a perfect world, we would look क्रम it on
	 * the ISA bus that holds the 8259 but heh... Works that way. If
	 * we ever see a problem, we can try to re-use the pSeries code here.
	 * Also, Pegasos-type platक्रमms करोn't have a proper node to start
	 * from anyway
	 */
	क्रम_each_node_by_name(np, "pci") अणु
		स्थिर अचिन्हित पूर्णांक *addrp = of_get_property(np,
				"8259-interrupt-acknowledge", शून्य);

		अगर (addrp == शून्य)
			जारी;
		chrp_पूर्णांक_ack = addrp[of_n_addr_cells(np)-1];
		अवरोध;
	पूर्ण
	of_node_put(np);
	अगर (np == शून्य)
		prपूर्णांकk(KERN_WARNING "Cannot find PCI interrupt acknowledge"
		       " address, polling\n");

	i8259_init(pic, chrp_पूर्णांक_ack);
	अगर (ppc_md.get_irq == शून्य) अणु
		ppc_md.get_irq = i8259_irq;
		irq_set_शेष_host(i8259_get_host());
	पूर्ण
	अगर (chrp_mpic != शून्य) अणु
		cascade_irq = irq_of_parse_and_map(pic, 0);
		अगर (!cascade_irq)
			prपूर्णांकk(KERN_ERR "i8259: failed to map cascade irq\n");
		अन्यथा
			irq_set_chained_handler(cascade_irq,
						chrp_8259_cascade);
	पूर्ण
पूर्ण

अटल व्योम __init chrp_init_IRQ(व्योम)
अणु
#अगर defined(CONFIG_VT) && defined(CONFIG_INPUT_ADBHID) && defined(CONFIG_XMON)
	काष्ठा device_node *kbd;
#पूर्ण_अगर
	chrp_find_खोलोpic();
	chrp_find_8259();

#अगर_घोषित CONFIG_SMP
	/* Pegasos has no MPIC, those ops would make it crash. It might be an
	 * option to move setting them to after we probe the PIC though
	 */
	अगर (chrp_mpic != शून्य)
		smp_ops = &chrp_smp_ops;
#पूर्ण_अगर /* CONFIG_SMP */

	अगर (_chrp_type == _CHRP_Pegasos)
		ppc_md.get_irq        = i8259_irq;

#अगर defined(CONFIG_VT) && defined(CONFIG_INPUT_ADBHID) && defined(CONFIG_XMON)
	/* see अगर there is a keyboard in the device tree
	   with a parent of type "adb" */
	क्रम_each_node_by_name(kbd, "keyboard")
		अगर (of_node_is_type(kbd->parent, "adb"))
			अवरोध;
	of_node_put(kbd);
	अगर (kbd) अणु
		अगर (request_irq(HYDRA_INT_ADB_NMI, xmon_irq, 0, "XMON break",
				शून्य))
			pr_err("Failed to register XMON break interrupt\n");
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init
chrp_init2(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_NVRAM)
	chrp_nvram_init();
#पूर्ण_अगर

	request_region(0x20,0x20,"pic1");
	request_region(0xa0,0x20,"pic2");
	request_region(0x00,0x20,"dma1");
	request_region(0x40,0x20,"timer");
	request_region(0x80,0x10,"dma page reg");
	request_region(0xc0,0x20,"dma2");

	अगर (ppc_md.progress)
		ppc_md.progress("  Have fun!    ", 0x7777);
पूर्ण

अटल पूर्णांक __init chrp_probe(व्योम)
अणु
	स्थिर अक्षर *dtype = of_get_flat_dt_prop(of_get_flat_dt_root(),
						"device_type", शून्य);
 	अगर (dtype == शून्य)
 		वापस 0;
 	अगर (म_भेद(dtype, "chrp"))
		वापस 0;

	DMA_MODE_READ = 0x44;
	DMA_MODE_WRITE = 0x48;

	pm_घातer_off = rtas_घातer_off;

	chrp_init();

	वापस 1;
पूर्ण

define_machine(chrp) अणु
	.name			= "CHRP",
	.probe			= chrp_probe,
	.setup_arch		= chrp_setup_arch,
	.discover_phbs		= chrp_find_bridges,
	.init			= chrp_init2,
	.show_cpuinfo		= chrp_show_cpuinfo,
	.init_IRQ		= chrp_init_IRQ,
	.restart		= rtas_restart,
	.halt			= rtas_halt,
	.समय_init		= chrp_समय_init,
	.set_rtc_समय		= chrp_set_rtc_समय,
	.get_rtc_समय		= chrp_get_rtc_समय,
	.calibrate_decr		= generic_calibrate_decr,
	.phys_mem_access_prot	= pci_phys_mem_access_prot,
पूर्ण;
