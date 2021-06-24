<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * pcic.c: MicroSPARC-IIep PCI controller support
 *
 * Copyright (C) 1998 V. Roganov and G. Raiko
 *
 * Code is derived from Ultra/PCI PSYCHO controller support, see that
 * क्रम author info.
 *
 * Support क्रम भागerse IIep based platक्रमms by Pete Zaitcev.
 * CP-1200 by Eric Brower.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>

#समावेश <यंत्र/swअगरt.h> /* क्रम cache flushing. */
#समावेश <यंत्र/पन.स>

#समावेश <linux/प्रकार.स>
#समावेश <linux/pci.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pcic.h>
#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/समयr.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/irq_regs.h>

#समावेश "kernel.h"
#समावेश "irq.h"

/*
 * I studied dअगरferent करोcuments and many live PROMs both from 2.30
 * family and 3.xx versions. I came to the amazing conclusion: there is
 * असलolutely no way to route पूर्णांकerrupts in IIep प्रणालीs relying on
 * inक्रमmation which PROM presents. We must hardcode पूर्णांकerrupt routing
 * schematics. And this actually sucks.   -- zaitcev 1999/05/12
 *
 * To find irq क्रम a device we determine which routing map
 * is in effect or, in other words, on which machine we are running.
 * We use PROM name क्रम this although other techniques may be used
 * in special हालs (Gleb reports a PROMless IIep based प्रणाली).
 * Once we know the map we take device configuration address and
 * find PCIC pin number where INT line goes. Then we may either program
 * preferred irq पूर्णांकo the PCIC or supply the preexisting irq to the device.
 */
काष्ठा pcic_ca2irq अणु
	अचिन्हित अक्षर busno;		/* PCI bus number */
	अचिन्हित अक्षर devfn;		/* Configuration address */
	अचिन्हित अक्षर pin;		/* PCIC बाह्यal पूर्णांकerrupt pin */
	अचिन्हित अक्षर irq;		/* Preferred IRQ (mappable in PCIC) */
	अचिन्हित पूर्णांक क्रमce;		/* Enक्रमce preferred IRQ */
पूर्ण;

काष्ठा pcic_sn2list अणु
	अक्षर *sysname;
	काष्ठा pcic_ca2irq *पूर्णांकmap;
	पूर्णांक mapdim;
पूर्ण;

/*
 * JavaEngine-1 apparently has dअगरferent versions.
 *
 * According to communications with Sun folks, क्रम P2 build 501-4628-03:
 * pin 0 - parallel, audio;
 * pin 1 - Ethernet;
 * pin 2 - su;
 * pin 3 - PS/2 kbd and mouse.
 *
 * OEM manual (805-1486):
 * pin 0: Ethernet
 * pin 1: All EBus
 * pin 2: IGA (unused)
 * pin 3: Not connected
 * OEM manual says that 501-4628 & 501-4811 are the same thing,
 * only the latter has न_अंकD flash in place.
 *
 * So far unofficial Sun wins over the OEM manual. Poor OEMs...
 */
अटल काष्ठा pcic_ca2irq pcic_i_je1a[] = अणु	/* 501-4811-03 */
	अणु 0, 0x00, 2, 12, 0 पूर्ण,		/* EBus: hogs all */
	अणु 0, 0x01, 1,  6, 1 पूर्ण,		/* Happy Meal */
	अणु 0, 0x80, 0,  7, 0 पूर्ण,		/* IGA (unused) */
पूर्ण;

/* XXX JS-E entry is incomplete - PCI Slot 2 address (pin 7)? */
अटल काष्ठा pcic_ca2irq pcic_i_jse[] = अणु
	अणु 0, 0x00, 0, 13, 0 पूर्ण,		/* Ebus - serial and keyboard */
	अणु 0, 0x01, 1,  6, 0 पूर्ण,		/* hme */
	अणु 0, 0x08, 2,  9, 0 पूर्ण,		/* VGA - we hope not used :) */
	अणु 0, 0x10, 6,  8, 0 पूर्ण,		/* PCI INTA# in Slot 1 */
	अणु 0, 0x18, 7, 12, 0 पूर्ण,		/* PCI INTA# in Slot 2, shared w. RTC */
	अणु 0, 0x38, 4,  9, 0 पूर्ण,		/* All ISA devices. Read 8259. */
	अणु 0, 0x80, 5, 11, 0 पूर्ण,		/* EIDE */
	/* अणु0,0x88, 0,0,0पूर्ण - unknown device... PMU? Probably no पूर्णांकerrupt. */
	अणु 0, 0xA0, 4,  9, 0 पूर्ण,		/* USB */
	/*
	 * Some pins beदीर्घ to non-PCI devices, we hardcode them in drivers.
	 * sun4m समयrs - irq 10, 14
	 * PC style RTC - pin 7, irq 4 ?
	 * Smart card, Parallel - pin 4 shared with USB, ISA
	 * audio - pin 3, irq 5 ?
	 */
पूर्ण;

/* SPARCengine-6 was the original release name of CP1200.
 * The करोcumentation dअगरfers between the two versions
 */
अटल काष्ठा pcic_ca2irq pcic_i_se6[] = अणु
	अणु 0, 0x08, 0,  2, 0 पूर्ण,		/* SCSI	*/
	अणु 0, 0x01, 1,  6, 0 पूर्ण,		/* HME	*/
	अणु 0, 0x00, 3, 13, 0 पूर्ण,		/* EBus	*/
पूर्ण;

/*
 * Krups (courtesy of Varol Kaptan)
 * No करोcumentation available, but it was easy to guess
 * because it was very similar to Espresso.
 *  
 * pin 0 - kbd, mouse, serial;
 * pin 1 - Ethernet;
 * pin 2 - igs (we करो not use it);
 * pin 3 - audio;
 * pin 4,5,6 - unused;
 * pin 7 - RTC (from P2 onwards as David B. says).
 */
अटल काष्ठा pcic_ca2irq pcic_i_jk[] = अणु
	अणु 0, 0x00, 0, 13, 0 पूर्ण,		/* Ebus - serial and keyboard */
	अणु 0, 0x01, 1,  6, 0 पूर्ण,		/* hme */
पूर्ण;

/*
 * Several entries in this list may poपूर्णांक to the same routing map
 * as several PROMs may be installed on the same physical board.
 */
#घोषणा SN2L_INIT(name, map)	\
  अणु name, map, ARRAY_SIZE(map) पूर्ण

अटल काष्ठा pcic_sn2list pcic_known_sysnames[] = अणु
	SN2L_INIT("SUNW,JavaEngine1", pcic_i_je1a),	/* JE1, PROM 2.32 */
	SN2L_INIT("SUNW,JS-E", pcic_i_jse),	/* PROLL JavaStation-E */
	SN2L_INIT("SUNW,SPARCengine-6", pcic_i_se6), /* SPARCengine-6/CP-1200 */
	SN2L_INIT("SUNW,JS-NC", pcic_i_jk),	/* PROLL JavaStation-NC */
	SN2L_INIT("SUNW,JSIIep", pcic_i_jk),	/* OBP JavaStation-NC */
	अणु शून्य, शून्य, 0 पूर्ण
पूर्ण;

/*
 * Only one PCIC per IIep,
 * and since we have no SMP IIep, only one per प्रणाली.
 */
अटल पूर्णांक pcic0_up;
अटल काष्ठा linux_pcic pcic0;

व्योम __iomem *pcic_regs;
अटल अस्थिर पूर्णांक pcic_speculative;
अटल अस्थिर पूर्णांक pcic_trapped;

/* क्रमward */
अचिन्हित पूर्णांक pcic_build_device_irq(काष्ठा platक्रमm_device *op,
                                   अचिन्हित पूर्णांक real_irq);

#घोषणा CONFIG_CMD(bus, device_fn, where) (0x80000000 | (((अचिन्हित पूर्णांक)bus) << 16) | (((अचिन्हित पूर्णांक)device_fn) << 8) | (where & ~3))

अटल पूर्णांक pcic_पढ़ो_config_dword(अचिन्हित पूर्णांक busno, अचिन्हित पूर्णांक devfn,
    पूर्णांक where, u32 *value)
अणु
	काष्ठा linux_pcic *pcic;
	अचिन्हित दीर्घ flags;

	pcic = &pcic0;

	local_irq_save(flags);
#अगर 0 /* करोes not fail here */
	pcic_speculative = 1;
	pcic_trapped = 0;
#पूर्ण_अगर
	ग_लिखोl(CONFIG_CMD(busno, devfn, where), pcic->pcic_config_space_addr);
#अगर 0 /* करोes not fail here */
	nop();
	अगर (pcic_trapped) अणु
		local_irq_restore(flags);
		*value = ~0;
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	pcic_speculative = 2;
	pcic_trapped = 0;
	*value = पढ़ोl(pcic->pcic_config_space_data + (where&4));
	nop();
	अगर (pcic_trapped) अणु
		pcic_speculative = 0;
		local_irq_restore(flags);
		*value = ~0;
		वापस 0;
	पूर्ण
	pcic_speculative = 0;
	local_irq_restore(flags);
	वापस 0;
पूर्ण

अटल पूर्णांक pcic_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
   पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	अचिन्हित पूर्णांक v;

	अगर (bus->number != 0) वापस -EINVAL;
	चयन (size) अणु
	हाल 1:
		pcic_पढ़ो_config_dword(bus->number, devfn, where&~3, &v);
		*val = 0xff & (v >> (8*(where & 3)));
		वापस 0;
	हाल 2:
		अगर (where&1) वापस -EINVAL;
		pcic_पढ़ो_config_dword(bus->number, devfn, where&~3, &v);
		*val = 0xffff & (v >> (8*(where & 3)));
		वापस 0;
	हाल 4:
		अगर (where&3) वापस -EINVAL;
		pcic_पढ़ो_config_dword(bus->number, devfn, where&~3, val);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pcic_ग_लिखो_config_dword(अचिन्हित पूर्णांक busno, अचिन्हित पूर्णांक devfn,
    पूर्णांक where, u32 value)
अणु
	काष्ठा linux_pcic *pcic;
	अचिन्हित दीर्घ flags;

	pcic = &pcic0;

	local_irq_save(flags);
	ग_लिखोl(CONFIG_CMD(busno, devfn, where), pcic->pcic_config_space_addr);
	ग_लिखोl(value, pcic->pcic_config_space_data + (where&4));
	local_irq_restore(flags);
	वापस 0;
पूर्ण

अटल पूर्णांक pcic_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
   पूर्णांक where, पूर्णांक size, u32 val)
अणु
	अचिन्हित पूर्णांक v;

	अगर (bus->number != 0) वापस -EINVAL;
	चयन (size) अणु
	हाल 1:
		pcic_पढ़ो_config_dword(bus->number, devfn, where&~3, &v);
		v = (v & ~(0xff << (8*(where&3)))) |
		    ((0xff&val) << (8*(where&3)));
		वापस pcic_ग_लिखो_config_dword(bus->number, devfn, where&~3, v);
	हाल 2:
		अगर (where&1) वापस -EINVAL;
		pcic_पढ़ो_config_dword(bus->number, devfn, where&~3, &v);
		v = (v & ~(0xffff << (8*(where&3)))) |
		    ((0xffff&val) << (8*(where&3)));
		वापस pcic_ग_लिखो_config_dword(bus->number, devfn, where&~3, v);
	हाल 4:
		अगर (where&3) वापस -EINVAL;
		वापस pcic_ग_लिखो_config_dword(bus->number, devfn, where, val);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल काष्ठा pci_ops pcic_ops = अणु
	.पढ़ो =		pcic_पढ़ो_config,
	.ग_लिखो =	pcic_ग_लिखो_config,
पूर्ण;

/*
 * On sparc64 pcibios_init() calls pci_controller_probe().
 * We want PCIC probed little ahead so that पूर्णांकerrupt controller
 * would be operational.
 */
पूर्णांक __init pcic_probe(व्योम)
अणु
	काष्ठा linux_pcic *pcic;
	काष्ठा linux_prom_रेजिस्टरs regs[PROMREG_MAX];
	काष्ठा linux_pbm_info* pbm;
	अक्षर namebuf[64];
	phandle node;
	पूर्णांक err;

	अगर (pcic0_up) अणु
		prom_म_लिखो("PCIC: called twice!\n");
		prom_halt();
	पूर्ण
	pcic = &pcic0;

	node = prom_अ_लोhild (prom_root_node);
	node = prom_searchsiblings (node, "pci");
	अगर (node == 0)
		वापस -ENODEV;
	/*
	 * Map in PCIC रेजिस्टर set, config space, and IO base
	 */
	err = prom_getproperty(node, "reg", (अक्षर*)regs, माप(regs));
	अगर (err == 0 || err == -1) अणु
		prom_म_लिखो("PCIC: Error, cannot get PCIC registers "
			    "from PROM.\n");
		prom_halt();
	पूर्ण

	pcic0_up = 1;

	pcic->pcic_res_regs.name = "pcic_registers";
	pcic->pcic_regs = ioremap(regs[0].phys_addr, regs[0].reg_size);
	अगर (!pcic->pcic_regs) अणु
		prom_म_लिखो("PCIC: Error, cannot map PCIC registers.\n");
		prom_halt();
	पूर्ण

	pcic->pcic_res_io.name = "pcic_io";
	अगर ((pcic->pcic_io = (अचिन्हित दीर्घ)
	    ioremap(regs[1].phys_addr, 0x10000)) == 0) अणु
		prom_म_लिखो("PCIC: Error, cannot map PCIC IO Base.\n");
		prom_halt();
	पूर्ण

	pcic->pcic_res_cfg_addr.name = "pcic_cfg_addr";
	अगर ((pcic->pcic_config_space_addr =
	    ioremap(regs[2].phys_addr, regs[2].reg_size * 2)) == शून्य) अणु
		prom_म_लिखो("PCIC: Error, cannot map "
			    "PCI Configuration Space Address.\n");
		prom_halt();
	पूर्ण

	/*
	 * Docs say three least signअगरicant bits in address and data
	 * must be the same. Thus, we need adjust size of data.
	 */
	pcic->pcic_res_cfg_data.name = "pcic_cfg_data";
	अगर ((pcic->pcic_config_space_data =
	    ioremap(regs[3].phys_addr, regs[3].reg_size * 2)) == शून्य) अणु
		prom_म_लिखो("PCIC: Error, cannot map "
			    "PCI Configuration Space Data.\n");
		prom_halt();
	पूर्ण

	pbm = &pcic->pbm;
	pbm->prom_node = node;
	prom_माला_लोtring(node, "name", namebuf, 63);  namebuf[63] = 0;
	म_नकल(pbm->prom_name, namebuf);

	अणु
		बाह्य पूर्णांक pcic_nmi_trap_patch[4];

		t_nmi[0] = pcic_nmi_trap_patch[0];
		t_nmi[1] = pcic_nmi_trap_patch[1];
		t_nmi[2] = pcic_nmi_trap_patch[2];
		t_nmi[3] = pcic_nmi_trap_patch[3];
		swअगरt_flush_dcache();
		pcic_regs = pcic->pcic_regs;
	पूर्ण

	prom_माला_लोtring(prom_root_node, "name", namebuf, 63);  namebuf[63] = 0;
	अणु
		काष्ठा pcic_sn2list *p;

		क्रम (p = pcic_known_sysnames; p->sysname != शून्य; p++) अणु
			अगर (म_भेद(namebuf, p->sysname) == 0)
				अवरोध;
		पूर्ण
		pcic->pcic_imap = p->पूर्णांकmap;
		pcic->pcic_imdim = p->mapdim;
	पूर्ण
	अगर (pcic->pcic_imap == शून्य) अणु
		/*
		 * We करो not panic here क्रम the sake of embedded प्रणालीs.
		 */
		prपूर्णांकk("PCIC: System %s is unknown, cannot route interrupts\n",
		    namebuf);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init pcic_pbm_scan_bus(काष्ठा linux_pcic *pcic)
अणु
	काष्ठा linux_pbm_info *pbm = &pcic->pbm;

	pbm->pci_bus = pci_scan_bus(pbm->pci_first_busno, &pcic_ops, pbm);
	अगर (!pbm->pci_bus)
		वापस;

#अगर 0 /* deadwood transplanted from sparc64 */
	pci_fill_in_pbm_cookies(pbm->pci_bus, pbm, pbm->prom_node);
	pci_record_assignments(pbm, pbm->pci_bus);
	pci_assign_unasचिन्हित(pbm, pbm->pci_bus);
	pci_fixup_irq(pbm, pbm->pci_bus);
#पूर्ण_अगर
	pci_bus_add_devices(pbm->pci_bus);
पूर्ण

/*
 * Main entry poपूर्णांक from the PCI subप्रणाली.
 */
अटल पूर्णांक __init pcic_init(व्योम)
अणु
	काष्ठा linux_pcic *pcic;

	/*
	 * PCIC should be initialized at start of the समयr.
	 * So, here we report the presence of PCIC and करो some magic passes.
	 */
	अगर(!pcic0_up)
		वापस 0;
	pcic = &pcic0;

	/*
	 *      Switch off IOTLB translation.
	 */
	ग_लिखोb(PCI_DVMA_CONTROL_IOTLB_DISABLE, 
	       pcic->pcic_regs+PCI_DVMA_CONTROL);

	/*
	 *      Increase mapped size क्रम PCI memory space (DMA access).
	 *      Should be करोne in that order (size first, address second).
	 *      Why we couldn't set up 4GB and क्रमget about it? XXX
	 */
	ग_लिखोl(0xF0000000UL, pcic->pcic_regs+PCI_SIZE_0);
	ग_लिखोl(0+PCI_BASE_ADDRESS_SPACE_MEMORY, 
	       pcic->pcic_regs+PCI_BASE_ADDRESS_0);

	pcic_pbm_scan_bus(pcic);

	वापस 0;
पूर्ण

पूर्णांक pcic_present(व्योम)
अणु
	वापस pcic0_up;
पूर्ण

अटल पूर्णांक pdev_to_pnode(काष्ठा linux_pbm_info *pbm, काष्ठा pci_dev *pdev)
अणु
	काष्ठा linux_prom_pci_रेजिस्टरs regs[PROMREG_MAX];
	पूर्णांक err;
	phandle node = prom_अ_लोhild(pbm->prom_node);

	जबतक(node) अणु
		err = prom_getproperty(node, "reg", 
				       (अक्षर *)&regs[0], माप(regs));
		अगर(err != 0 && err != -1) अणु
			अचिन्हित दीर्घ devfn = (regs[0].which_io >> 8) & 0xff;
			अगर(devfn == pdev->devfn)
				वापस node;
		पूर्ण
		node = prom_माला_लोibling(node);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा pcidev_cookie *pci_devcookie_alloc(व्योम)
अणु
	वापस kदो_स्मृति(माप(काष्ठा pcidev_cookie), GFP_ATOMIC);
पूर्ण

अटल व्योम pcic_map_pci_device(काष्ठा linux_pcic *pcic,
    काष्ठा pci_dev *dev, पूर्णांक node)
अणु
	अक्षर namebuf[64];
	अचिन्हित दीर्घ address;
	अचिन्हित दीर्घ flags;
	पूर्णांक j;

	अगर (node == 0 || node == -1) अणु
		म_नकल(namebuf, "???");
	पूर्ण अन्यथा अणु
		prom_माला_लोtring(node, "name", namebuf, 63); namebuf[63] = 0;
	पूर्ण

	क्रम (j = 0; j < 6; j++) अणु
		address = dev->resource[j].start;
		अगर (address == 0) अवरोध;	/* are sequential */
		flags = dev->resource[j].flags;
		अगर ((flags & IORESOURCE_IO) != 0) अणु
			अगर (address < 0x10000) अणु
				/*
				 * A device responds to I/O cycles on PCI.
				 * We generate these cycles with memory
				 * access पूर्णांकo the fixed map (phys 0x30000000).
				 *
				 * Since a device driver करोes not want to
				 * करो ioremap() beक्रमe accessing PC-style I/O,
				 * we supply भव, पढ़ोy to access address.
				 *
				 * Note that request_region()
				 * works क्रम these devices.
				 *
				 * XXX Neat trick, but it's a *bad* idea
				 * to shit पूर्णांकo regions like that.
				 * What अगर we want to allocate one more
				 * PCI base address...
				 */
				dev->resource[j].start =
				    pcic->pcic_io + address;
				dev->resource[j].end = 1;  /* XXX */
				dev->resource[j].flags =
				    (flags & ~IORESOURCE_IO) | IORESOURCE_MEM;
			पूर्ण अन्यथा अणु
				/*
				 * OOPS... PCI Spec allows this. Sun करोes
				 * not have any devices getting above 64K
				 * so it must be user with a weird I/O
				 * board in a PCI slot. We must remap it
				 * under 64K but it is not करोne yet. XXX
				 */
				pci_info(dev, "PCIC: Skipping I/O space at "
					 "0x%lx, this will Oops if a driver "
					 "attaches device '%s'\n", address,
					 namebuf);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
pcic_fill_irq(काष्ठा linux_pcic *pcic, काष्ठा pci_dev *dev, पूर्णांक node)
अणु
	काष्ठा pcic_ca2irq *p;
	अचिन्हित पूर्णांक real_irq;
	पूर्णांक i, ivec;
	अक्षर namebuf[64];

	अगर (node == 0 || node == -1) अणु
		म_नकल(namebuf, "???");
	पूर्ण अन्यथा अणु
		prom_माला_लोtring(node, "name", namebuf, माप(namebuf));
	पूर्ण

	अगर ((p = pcic->pcic_imap) == शून्य) अणु
		dev->irq = 0;
		वापस;
	पूर्ण
	क्रम (i = 0; i < pcic->pcic_imdim; i++) अणु
		अगर (p->busno == dev->bus->number && p->devfn == dev->devfn)
			अवरोध;
		p++;
	पूर्ण
	अगर (i >= pcic->pcic_imdim) अणु
		pci_info(dev, "PCIC: device %s not found in %d\n", namebuf,
			 pcic->pcic_imdim);
		dev->irq = 0;
		वापस;
	पूर्ण

	i = p->pin;
	अगर (i >= 0 && i < 4) अणु
		ivec = पढ़ोw(pcic->pcic_regs+PCI_INT_SELECT_LO);
		real_irq = ivec >> (i << 2) & 0xF;
	पूर्ण अन्यथा अगर (i >= 4 && i < 8) अणु
		ivec = पढ़ोw(pcic->pcic_regs+PCI_INT_SELECT_HI);
		real_irq = ivec >> ((i-4) << 2) & 0xF;
	पूर्ण अन्यथा अणु					/* Corrupted map */
		pci_info(dev, "PCIC: BAD PIN %d\n", i); क्रम (;;) अणुपूर्ण
	पूर्ण
/* P3 */ /* prपूर्णांकk("PCIC: device %s pin %d ivec 0x%x irq %x\n", namebuf, i, ivec, dev->irq); */

	/* real_irq means PROM did not bother to program the upper
	 * half of PCIC. This happens on JS-E with PROM 3.11, क्रम instance.
	 */
	अगर (real_irq == 0 || p->क्रमce) अणु
		अगर (p->irq == 0 || p->irq >= 15) अणु	/* Corrupted map */
			pci_info(dev, "PCIC: BAD IRQ %d\n", p->irq); क्रम (;;) अणुपूर्ण
		पूर्ण
		pci_info(dev, "PCIC: setting irq %d at pin %d\n", p->irq,
			 p->pin);
		real_irq = p->irq;

		i = p->pin;
		अगर (i >= 4) अणु
			ivec = पढ़ोw(pcic->pcic_regs+PCI_INT_SELECT_HI);
			ivec &= ~(0xF << ((i - 4) << 2));
			ivec |= p->irq << ((i - 4) << 2);
			ग_लिखोw(ivec, pcic->pcic_regs+PCI_INT_SELECT_HI);
		पूर्ण अन्यथा अणु
			ivec = पढ़ोw(pcic->pcic_regs+PCI_INT_SELECT_LO);
			ivec &= ~(0xF << (i << 2));
			ivec |= p->irq << (i << 2);
			ग_लिखोw(ivec, pcic->pcic_regs+PCI_INT_SELECT_LO);
		पूर्ण
	पूर्ण
	dev->irq = pcic_build_device_irq(शून्य, real_irq);
पूर्ण

/*
 * Normally called from अणुकरो_पूर्णpci_scan_bus...
 */
व्योम pcibios_fixup_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा linux_pcic *pcic;
	/* काष्ठा linux_pbm_info* pbm = &pcic->pbm; */
	पूर्णांक node;
	काष्ठा pcidev_cookie *pcp;

	अगर (!pcic0_up) अणु
		pci_info(bus, "pcibios_fixup_bus: no PCIC\n");
		वापस;
	पूर्ण
	pcic = &pcic0;

	/*
	 * Next crud is an equivalent of pbm = pcic_bus_to_pbm(bus);
	 */
	अगर (bus->number != 0) अणु
		pci_info(bus, "pcibios_fixup_bus: nonzero bus 0x%x\n",
			 bus->number);
		वापस;
	पूर्ण

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		node = pdev_to_pnode(&pcic->pbm, dev);
		अगर(node == 0)
			node = -1;

		/* cookies */
		pcp = pci_devcookie_alloc();
		pcp->pbm = &pcic->pbm;
		pcp->prom_node = of_find_node_by_phandle(node);
		dev->sysdata = pcp;

		/* fixing I/O to look like memory */
		अगर ((dev->class>>16) != PCI_BASE_CLASS_BRIDGE)
			pcic_map_pci_device(pcic, dev, node);

		pcic_fill_irq(pcic, dev, node);
	पूर्ण
पूर्ण

पूर्णांक pcibios_enable_device(काष्ठा pci_dev *dev, पूर्णांक mask)
अणु
	u16 cmd, oldcmd;
	पूर्णांक i;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	oldcmd = cmd;

	क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
		काष्ठा resource *res = &dev->resource[i];

		/* Only set up the requested stuff */
		अगर (!(mask & (1<<i)))
			जारी;

		अगर (res->flags & IORESOURCE_IO)
			cmd |= PCI_COMMAND_IO;
		अगर (res->flags & IORESOURCE_MEM)
			cmd |= PCI_COMMAND_MEMORY;
	पूर्ण

	अगर (cmd != oldcmd) अणु
		pci_info(dev, "enabling device (%04x -> %04x)\n", oldcmd, cmd);
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
	पूर्ण
	वापस 0;
पूर्ण

/* Makes compiler happy */
अटल अस्थिर पूर्णांक pcic_समयr_dummy;

अटल व्योम pcic_clear_घड़ी_irq(व्योम)
अणु
	pcic_समयr_dummy = पढ़ोl(pcic0.pcic_regs+PCI_SYS_LIMIT);
पूर्ण

/* CPU frequency is 100 MHz, समयr increments every 4 CPU घड़ीs */
#घोषणा USECS_PER_JIFFY  (1000000 / HZ)
#घोषणा TICK_TIMER_LIMIT ((100 * 1000000 / 4) / HZ)

अटल अचिन्हित पूर्णांक pcic_cycles_offset(व्योम)
अणु
	u32 value, count;

	value = पढ़ोl(pcic0.pcic_regs + PCI_SYS_COUNTER);
	count = value & ~PCI_SYS_COUNTER_OVERFLOW;

	अगर (value & PCI_SYS_COUNTER_OVERFLOW)
		count += TICK_TIMER_LIMIT;
	/*
	 * We भागide all by HZ
	 * to have microsecond resolution and to aव्योम overflow
	 */
	count = ((count / HZ) * USECS_PER_JIFFY) / (TICK_TIMER_LIMIT / HZ);

	/* Coordinate with the sparc_config.घड़ी_rate setting */
	वापस count * 2;
पूर्ण

व्योम __init pci_समय_init(व्योम)
अणु
	काष्ठा linux_pcic *pcic = &pcic0;
	अचिन्हित दीर्घ v;
	पूर्णांक समयr_irq, irq;
	पूर्णांक err;

#अगर_अघोषित CONFIG_SMP
	/*
	 * The घड़ी_rate is in SBUS dimension.
	 * We take पूर्णांकo account this in pcic_cycles_offset()
	 */
	sparc_config.घड़ी_rate = SBUS_CLOCK_RATE / HZ;
	sparc_config.features |= FEAT_L10_CLOCKEVENT;
#पूर्ण_अगर
	sparc_config.features |= FEAT_L10_CLOCKSOURCE;
	sparc_config.get_cycles_offset = pcic_cycles_offset;

	ग_लिखोl (TICK_TIMER_LIMIT, pcic->pcic_regs+PCI_SYS_LIMIT);
	/* PROM should set appropriate irq */
	v = पढ़ोb(pcic->pcic_regs+PCI_COUNTER_IRQ);
	समयr_irq = PCI_COUNTER_IRQ_SYS(v);
	ग_लिखोl (PCI_COUNTER_IRQ_SET(समयr_irq, 0),
		pcic->pcic_regs+PCI_COUNTER_IRQ);
	irq = pcic_build_device_irq(शून्य, समयr_irq);
	err = request_irq(irq, समयr_पूर्णांकerrupt,
			  IRQF_TIMER, "timer", शून्य);
	अगर (err) अणु
		prom_म_लिखो("time_init: unable to attach IRQ%d\n", समयr_irq);
		prom_halt();
	पूर्ण
	local_irq_enable();
पूर्ण


#अगर 0
अटल व्योम watchकरोg_reset() अणु
	ग_लिखोb(0, pcic->pcic_regs+PCI_SYS_STATUS);
पूर्ण
#पूर्ण_अगर

/*
 * NMI
 */
व्योम pcic_nmi(अचिन्हित पूर्णांक pend, काष्ठा pt_regs *regs)
अणु
	pend = swab32(pend);

	अगर (!pcic_speculative || (pend & PCI_SYS_INT_PENDING_PIO) == 0) अणु
		/*
		 * XXX On CP-1200 PCI #SERR may happen, we करो not know
		 * what to करो about it yet.
		 */
		prपूर्णांकk("Aiee, NMI pend 0x%x pc 0x%x spec %d, hanging\n",
		    pend, (पूर्णांक)regs->pc, pcic_speculative);
		क्रम (;;) अणु पूर्ण
	पूर्ण
	pcic_speculative = 0;
	pcic_trapped = 1;
	regs->pc = regs->npc;
	regs->npc += 4;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_irqmask(पूर्णांक irq_nr)
अणु
	वापस 1 << irq_nr;
पूर्ण

अटल व्योम pcic_mask_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ mask, flags;

	mask = (अचिन्हित दीर्घ)data->chip_data;
	local_irq_save(flags);
	ग_लिखोl(mask, pcic0.pcic_regs+PCI_SYS_INT_TARGET_MASK_SET);
	local_irq_restore(flags);
पूर्ण

अटल व्योम pcic_unmask_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ mask, flags;

	mask = (अचिन्हित दीर्घ)data->chip_data;
	local_irq_save(flags);
	ग_लिखोl(mask, pcic0.pcic_regs+PCI_SYS_INT_TARGET_MASK_CLEAR);
	local_irq_restore(flags);
पूर्ण

अटल अचिन्हित पूर्णांक pcic_startup_irq(काष्ठा irq_data *data)
अणु
	irq_link(data->irq);
	pcic_unmask_irq(data);
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip pcic_irq = अणु
	.name		= "pcic",
	.irq_startup	= pcic_startup_irq,
	.irq_mask	= pcic_mask_irq,
	.irq_unmask	= pcic_unmask_irq,
पूर्ण;

अचिन्हित पूर्णांक pcic_build_device_irq(काष्ठा platक्रमm_device *op,
                                   अचिन्हित पूर्णांक real_irq)
अणु
	अचिन्हित पूर्णांक irq;
	अचिन्हित दीर्घ mask;

	irq = 0;
	mask = get_irqmask(real_irq);
	अगर (mask == 0)
		जाओ out;

	irq = irq_alloc(real_irq, real_irq);
	अगर (irq == 0)
		जाओ out;

	irq_set_chip_and_handler_name(irq, &pcic_irq,
	                              handle_level_irq, "PCIC");
	irq_set_chip_data(irq, (व्योम *)mask);

out:
	वापस irq;
पूर्ण


अटल व्योम pcic_load_profile_irq(पूर्णांक cpu, अचिन्हित पूर्णांक limit)
अणु
	prपूर्णांकk("PCIC: unimplemented code: FILE=%s LINE=%d", __खाता__, __LINE__);
पूर्ण

व्योम __init sun4m_pci_init_IRQ(व्योम)
अणु
	sparc_config.build_device_irq = pcic_build_device_irq;
	sparc_config.clear_घड़ी_irq  = pcic_clear_घड़ी_irq;
	sparc_config.load_profile_irq = pcic_load_profile_irq;
पूर्ण

subsys_initcall(pcic_init);
