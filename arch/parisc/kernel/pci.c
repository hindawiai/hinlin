<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1997, 1998 Ralf Baechle
 * Copyright (C) 1999 SuSE GmbH
 * Copyright (C) 1999-2001 Hewlett-Packard Company
 * Copyright (C) 1999-2001 Grant Grundler
 */
#समावेश <linux/eisa.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/superपन.स>

#घोषणा DEBUG_RESOURCES 0
#घोषणा DEBUG_CONFIG 0

#अगर DEBUG_CONFIG
# define DBGC(x...)	prपूर्णांकk(KERN_DEBUG x)
#अन्यथा
# define DBGC(x...)
#पूर्ण_अगर


#अगर DEBUG_RESOURCES
#घोषणा DBG_RES(x...)	prपूर्णांकk(KERN_DEBUG x)
#अन्यथा
#घोषणा DBG_RES(x...)
#पूर्ण_अगर

काष्ठा pci_port_ops *pci_port __ro_after_init;
काष्ठा pci_bios_ops *pci_bios __ro_after_init;

अटल पूर्णांक pci_hba_count __ro_after_init;

/* parisc_pci_hba used by pci_port->in/out() ops to lookup bus data.  */
#घोषणा PCI_HBA_MAX 32
अटल काष्ठा pci_hba_data *parisc_pci_hba[PCI_HBA_MAX] __ro_after_init;


/********************************************************************
**
** I/O port space support
**
*********************************************************************/

/* EISA port numbers and PCI port numbers share the same पूर्णांकerface.  Some
 * machines have both EISA and PCI adapters installed.  Rather than turn
 * pci_port पूर्णांकo an array, we reserve bus 0 क्रम EISA and call the EISA
 * routines अगर the access is to a port on bus 0.  We करोn't want to fix
 * EISA and ISA drivers which assume port space is <= 0xffff.
 */

#अगर_घोषित CONFIG_EISA
#घोषणा EISA_IN(size) अगर (EISA_bus && (b == 0)) वापस eisa_in##size(addr)
#घोषणा EISA_OUT(size) अगर (EISA_bus && (b == 0)) वापस eisa_out##size(d, addr)
#अन्यथा
#घोषणा EISA_IN(size)
#घोषणा EISA_OUT(size)
#पूर्ण_अगर

#घोषणा PCI_PORT_IN(type, size) \
u##size in##type (पूर्णांक addr) \
अणु \
	पूर्णांक b = PCI_PORT_HBA(addr); \
	EISA_IN(size); \
	अगर (!parisc_pci_hba[b]) वापस (u##size) -1; \
	वापस pci_port->in##type(parisc_pci_hba[b], PCI_PORT_ADDR(addr)); \
पूर्ण \
EXPORT_SYMBOL(in##type);

PCI_PORT_IN(b,  8)
PCI_PORT_IN(w, 16)
PCI_PORT_IN(l, 32)


#घोषणा PCI_PORT_OUT(type, size) \
व्योम out##type (u##size d, पूर्णांक addr) \
अणु \
	पूर्णांक b = PCI_PORT_HBA(addr); \
	EISA_OUT(size); \
	अगर (!parisc_pci_hba[b]) वापस; \
	pci_port->out##type(parisc_pci_hba[b], PCI_PORT_ADDR(addr), d); \
पूर्ण \
EXPORT_SYMBOL(out##type);

PCI_PORT_OUT(b,  8)
PCI_PORT_OUT(w, 16)
PCI_PORT_OUT(l, 32)



/*
 * BIOS32 replacement.
 */
अटल पूर्णांक __init pcibios_init(व्योम)
अणु
	अगर (!pci_bios)
		वापस -1;

	अगर (pci_bios->init) अणु
		pci_bios->init();
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "pci_bios != NULL but init() is!\n");
	पूर्ण

	/* Set the CLS क्रम PCI as early as possible. */
	pci_cache_line_size = pci_dfl_cache_line_size;

	वापस 0;
पूर्ण


/* Called from pci_करो_scan_bus() *after* walking a bus but beक्रमe walking PPBs. */
व्योम pcibios_fixup_bus(काष्ठा pci_bus *bus)
अणु
	अगर (pci_bios->fixup_bus) अणु
		pci_bios->fixup_bus(bus);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "pci_bios != NULL but fixup_bus() is!\n");
	पूर्ण
पूर्ण


/*
 * Called by pci_set_master() - a driver पूर्णांकerface.
 *
 * Legacy PDC guarantees to set:
 *	Map Memory BAR's पूर्णांकo PA IO space.
 *	Map Expansion ROM BAR पूर्णांकo one common PA IO space per bus.
 *	Map IO BAR's पूर्णांकo PCI IO space.
 *	Command (see below)
 *	Cache Line Size
 *	Latency Timer
 *	Interrupt Line
 *	PPB: secondary latency समयr, io/mmio base/limit,
 *		bus numbers, bridge control
 *
 */
व्योम pcibios_set_master(काष्ठा pci_dev *dev)
अणु
	u8 lat;

	/* If someone alपढ़ोy mucked with this, करोn't touch it. */
	pci_पढ़ो_config_byte(dev, PCI_LATENCY_TIMER, &lat);
	अगर (lat >= 16) वापस;

	/*
	** HP generally has fewer devices on the bus than other architectures.
	** upper byte is PCI_LATENCY_TIMER.
	*/
	pci_ग_लिखो_config_word(dev, PCI_CACHE_LINE_SIZE,
			      (0x80 << 8) | pci_cache_line_size);
पूर्ण

/*
 * pcibios_init_bridge() initializes cache line and शेष latency
 * क्रम pci controllers and pci-pci bridges
 */
व्योम __ref pcibios_init_bridge(काष्ठा pci_dev *dev)
अणु
	अचिन्हित लघु bridge_ctl, bridge_ctl_new;

	/* We deal only with pci controllers and pci-pci bridges. */
	अगर (!dev || (dev->class >> 8) != PCI_CLASS_BRIDGE_PCI)
		वापस;

	/* PCI-PCI bridge - set the cache line and शेष latency
	 * (32) क्रम primary and secondary buses.
	 */
	pci_ग_लिखो_config_byte(dev, PCI_SEC_LATENCY_TIMER, 32);

	pci_पढ़ो_config_word(dev, PCI_BRIDGE_CONTROL, &bridge_ctl);

	bridge_ctl_new = bridge_ctl | PCI_BRIDGE_CTL_PARITY |
		PCI_BRIDGE_CTL_SERR | PCI_BRIDGE_CTL_MASTER_ABORT;
	dev_info(&dev->dev, "Changing bridge control from 0x%08x to 0x%08x\n",
		bridge_ctl, bridge_ctl_new);

	pci_ग_लिखो_config_word(dev, PCI_BRIDGE_CONTROL, bridge_ctl_new);
पूर्ण

/*
 * pcibios align resources() is called every समय generic PCI code
 * wants to generate a new address. The process of looking क्रम
 * an available address, each candidate is first "aligned" and
 * then checked अगर the resource is available until a match is found.
 *
 * Since we are just checking candidates, करोn't use any fields other
 * than res->start.
 */
resource_माप_प्रकार pcibios_align_resource(व्योम *data, स्थिर काष्ठा resource *res,
				resource_माप_प्रकार size, resource_माप_प्रकार alignment)
अणु
	resource_माप_प्रकार mask, align, start = res->start;

	DBG_RES("pcibios_align_resource(%s, (%p) [%lx,%lx]/%x, 0x%lx, 0x%lx)\n",
		pci_name(((काष्ठा pci_dev *) data)),
		res->parent, res->start, res->end,
		(पूर्णांक) res->flags, size, alignment);

	/* If it's not IO, then it's gotta be MEM */
	align = (res->flags & IORESOURCE_IO) ? PCIBIOS_MIN_IO : PCIBIOS_MIN_MEM;

	/* Align to largest of MIN or input size */
	mask = max(alignment, align) - 1;
	start += mask;
	start &= ~mask;

	वापस start;
पूर्ण

/*
 * A driver is enabling the device.  We make sure that all the appropriate
 * bits are set to allow the device to operate as the driver is expecting.
 * We enable the port IO and memory IO bits अगर the device has any BARs of
 * that type, and we enable the PERR and SERR bits unconditionally.
 * Drivers that करो not need parity (eg graphics and possibly networking)
 * can clear these bits अगर they want.
 */
पूर्णांक pcibios_enable_device(काष्ठा pci_dev *dev, पूर्णांक mask)
अणु
	पूर्णांक err;
	u16 cmd, old_cmd;

	err = pci_enable_resources(dev, mask);
	अगर (err < 0)
		वापस err;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	old_cmd = cmd;

	cmd |= (PCI_COMMAND_SERR | PCI_COMMAND_PARITY);

#अगर 0
	/* If bridge/bus controller has FBB enabled, child must too. */
	अगर (dev->bus->bridge_ctl & PCI_BRIDGE_CTL_FAST_BACK)
		cmd |= PCI_COMMAND_FAST_BACK;
#पूर्ण_अगर

	अगर (cmd != old_cmd) अणु
		dev_info(&dev->dev, "enabling SERR and PARITY (%04x -> %04x)\n",
			old_cmd, cmd);
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
	पूर्ण
	वापस 0;
पूर्ण


/* PA-RISC specअगरic */
व्योम pcibios_रेजिस्टर_hba(काष्ठा pci_hba_data *hba)
अणु
	अगर (pci_hba_count >= PCI_HBA_MAX) अणु
		prपूर्णांकk(KERN_ERR "PCI: Too many Host Bus Adapters\n");
		वापस;
	पूर्ण

	parisc_pci_hba[pci_hba_count] = hba;
	hba->hba_num = pci_hba_count++;
पूर्ण

subsys_initcall(pcibios_init);
