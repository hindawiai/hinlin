<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * direct.c - Low-level direct PCI config space access
 */

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/dmi.h>
#समावेश <यंत्र/pci_x86.h>

/*
 * Functions क्रम accessing PCI base (first 256 bytes) and extended
 * (4096 bytes per PCI function) configuration space with type 1
 * accesses.
 */

#घोषणा PCI_CONF1_ADDRESS(bus, devfn, reg) \
	(0x80000000 | ((reg & 0xF00) << 16) | (bus << 16) \
	| (devfn << 8) | (reg & 0xFC))

अटल पूर्णांक pci_conf1_पढ़ो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			  अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 *value)
अणु
	अचिन्हित दीर्घ flags;

	अगर (seg || (bus > 255) || (devfn > 255) || (reg > 4095)) अणु
		*value = -1;
		वापस -EINVAL;
	पूर्ण

	raw_spin_lock_irqsave(&pci_config_lock, flags);

	outl(PCI_CONF1_ADDRESS(bus, devfn, reg), 0xCF8);

	चयन (len) अणु
	हाल 1:
		*value = inb(0xCFC + (reg & 3));
		अवरोध;
	हाल 2:
		*value = inw(0xCFC + (reg & 2));
		अवरोध;
	हाल 4:
		*value = inl(0xCFC);
		अवरोध;
	पूर्ण

	raw_spin_unlock_irqrestore(&pci_config_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_conf1_ग_लिखो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			   अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 value)
अणु
	अचिन्हित दीर्घ flags;

	अगर (seg || (bus > 255) || (devfn > 255) || (reg > 4095))
		वापस -EINVAL;

	raw_spin_lock_irqsave(&pci_config_lock, flags);

	outl(PCI_CONF1_ADDRESS(bus, devfn, reg), 0xCF8);

	चयन (len) अणु
	हाल 1:
		outb((u8)value, 0xCFC + (reg & 3));
		अवरोध;
	हाल 2:
		outw((u16)value, 0xCFC + (reg & 2));
		अवरोध;
	हाल 4:
		outl((u32)value, 0xCFC);
		अवरोध;
	पूर्ण

	raw_spin_unlock_irqrestore(&pci_config_lock, flags);

	वापस 0;
पूर्ण

#अघोषित PCI_CONF1_ADDRESS

स्थिर काष्ठा pci_raw_ops pci_direct_conf1 = अणु
	.पढ़ो =		pci_conf1_पढ़ो,
	.ग_लिखो =	pci_conf1_ग_लिखो,
पूर्ण;


/*
 * Functions क्रम accessing PCI configuration space with type 2 accesses
 */

#घोषणा PCI_CONF2_ADDRESS(dev, reg)	(u16)(0xC000 | (dev << 8) | reg)

अटल पूर्णांक pci_conf2_पढ़ो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			  अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 *value)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक dev, fn;

	WARN_ON(seg);
	अगर ((bus > 255) || (devfn > 255) || (reg > 255)) अणु
		*value = -1;
		वापस -EINVAL;
	पूर्ण

	dev = PCI_SLOT(devfn);
	fn = PCI_FUNC(devfn);

	अगर (dev & 0x10) 
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	raw_spin_lock_irqsave(&pci_config_lock, flags);

	outb((u8)(0xF0 | (fn << 1)), 0xCF8);
	outb((u8)bus, 0xCFA);

	चयन (len) अणु
	हाल 1:
		*value = inb(PCI_CONF2_ADDRESS(dev, reg));
		अवरोध;
	हाल 2:
		*value = inw(PCI_CONF2_ADDRESS(dev, reg));
		अवरोध;
	हाल 4:
		*value = inl(PCI_CONF2_ADDRESS(dev, reg));
		अवरोध;
	पूर्ण

	outb(0, 0xCF8);

	raw_spin_unlock_irqrestore(&pci_config_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_conf2_ग_लिखो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			   अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 value)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक dev, fn;

	WARN_ON(seg);
	अगर ((bus > 255) || (devfn > 255) || (reg > 255)) 
		वापस -EINVAL;

	dev = PCI_SLOT(devfn);
	fn = PCI_FUNC(devfn);

	अगर (dev & 0x10) 
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	raw_spin_lock_irqsave(&pci_config_lock, flags);

	outb((u8)(0xF0 | (fn << 1)), 0xCF8);
	outb((u8)bus, 0xCFA);

	चयन (len) अणु
	हाल 1:
		outb((u8)value, PCI_CONF2_ADDRESS(dev, reg));
		अवरोध;
	हाल 2:
		outw((u16)value, PCI_CONF2_ADDRESS(dev, reg));
		अवरोध;
	हाल 4:
		outl((u32)value, PCI_CONF2_ADDRESS(dev, reg));
		अवरोध;
	पूर्ण

	outb(0, 0xCF8);    

	raw_spin_unlock_irqrestore(&pci_config_lock, flags);

	वापस 0;
पूर्ण

#अघोषित PCI_CONF2_ADDRESS

अटल स्थिर काष्ठा pci_raw_ops pci_direct_conf2 = अणु
	.पढ़ो =		pci_conf2_पढ़ो,
	.ग_लिखो =	pci_conf2_ग_लिखो,
पूर्ण;


/*
 * Beक्रमe we decide to use direct hardware access mechanisms, we try to करो some
 * trivial checks to ensure it at least _seems_ to be working -- we just test
 * whether bus 00 contains a host bridge (this is similar to checking
 * techniques used in XFree86, but ours should be more reliable since we
 * attempt to make use of direct access hपूर्णांकs provided by the PCI BIOS).
 *
 * This should be बंद to trivial, but it isn't, because there are buggy
 * chipsets (yes, you guessed it, by Intel and Compaq) that have no class ID.
 */
अटल पूर्णांक __init pci_sanity_check(स्थिर काष्ठा pci_raw_ops *o)
अणु
	u32 x = 0;
	पूर्णांक devfn;

	अगर (pci_probe & PCI_NO_CHECKS)
		वापस 1;
	/* Assume Type 1 works क्रम newer प्रणालीs.
	   This handles machines that करोn't have anything on PCI Bus 0. */
	अगर (dmi_get_bios_year() >= 2001)
		वापस 1;

	क्रम (devfn = 0; devfn < 0x100; devfn++) अणु
		अगर (o->पढ़ो(0, 0, devfn, PCI_CLASS_DEVICE, 2, &x))
			जारी;
		अगर (x == PCI_CLASS_BRIDGE_HOST || x == PCI_CLASS_DISPLAY_VGA)
			वापस 1;

		अगर (o->पढ़ो(0, 0, devfn, PCI_VENDOR_ID, 2, &x))
			जारी;
		अगर (x == PCI_VENDOR_ID_INTEL || x == PCI_VENDOR_ID_COMPAQ)
			वापस 1;
	पूर्ण

	DBG(KERN_WARNING "PCI: Sanity check failed\n");
	वापस 0;
पूर्ण

अटल पूर्णांक __init pci_check_type1(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक works = 0;

	local_irq_save(flags);

	outb(0x01, 0xCFB);
	पंचांगp = inl(0xCF8);
	outl(0x80000000, 0xCF8);
	अगर (inl(0xCF8) == 0x80000000 && pci_sanity_check(&pci_direct_conf1)) अणु
		works = 1;
	पूर्ण
	outl(पंचांगp, 0xCF8);
	local_irq_restore(flags);

	वापस works;
पूर्ण

अटल पूर्णांक __init pci_check_type2(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक works = 0;

	local_irq_save(flags);

	outb(0x00, 0xCFB);
	outb(0x00, 0xCF8);
	outb(0x00, 0xCFA);
	अगर (inb(0xCF8) == 0x00 && inb(0xCFA) == 0x00 &&
	    pci_sanity_check(&pci_direct_conf2)) अणु
		works = 1;
	पूर्ण

	local_irq_restore(flags);

	वापस works;
पूर्ण

व्योम __init pci_direct_init(पूर्णांक type)
अणु
	अगर (type == 0)
		वापस;
	prपूर्णांकk(KERN_INFO "PCI: Using configuration type %d for base access\n",
		 type);
	अगर (type == 1) अणु
		raw_pci_ops = &pci_direct_conf1;
		अगर (raw_pci_ext_ops)
			वापस;
		अगर (!(pci_probe & PCI_HAS_IO_ECS))
			वापस;
		prपूर्णांकk(KERN_INFO "PCI: Using configuration type 1 "
		       "for extended access\n");
		raw_pci_ext_ops = &pci_direct_conf1;
		वापस;
	पूर्ण
	raw_pci_ops = &pci_direct_conf2;
पूर्ण

पूर्णांक __init pci_direct_probe(व्योम)
अणु
	अगर ((pci_probe & PCI_PROBE_CONF1) == 0)
		जाओ type2;
	अगर (!request_region(0xCF8, 8, "PCI conf1"))
		जाओ type2;

	अगर (pci_check_type1()) अणु
		raw_pci_ops = &pci_direct_conf1;
		port_cf9_safe = true;
		वापस 1;
	पूर्ण
	release_region(0xCF8, 8);

 type2:
	अगर ((pci_probe & PCI_PROBE_CONF2) == 0)
		वापस 0;
	अगर (!request_region(0xCF8, 4, "PCI conf2"))
		वापस 0;
	अगर (!request_region(0xC000, 0x1000, "PCI conf2"))
		जाओ fail2;

	अगर (pci_check_type2()) अणु
		raw_pci_ops = &pci_direct_conf2;
		port_cf9_safe = true;
		वापस 2;
	पूर्ण

	release_region(0xC000, 0x1000);
 fail2:
	release_region(0xCF8, 4);
	वापस 0;
पूर्ण
