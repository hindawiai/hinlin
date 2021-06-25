<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BIOS32 and PCI BIOS handling.
 */

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/e820/types.h>
#समावेश <यंत्र/pci-functions.h>
#समावेश <यंत्र/set_memory.h>

/* BIOS32 signature: "_32_" */
#घोषणा BIOS32_SIGNATURE	(('_' << 0) + ('3' << 8) + ('2' << 16) + ('_' << 24))

/* PCI signature: "PCI " */
#घोषणा PCI_SIGNATURE		(('P' << 0) + ('C' << 8) + ('I' << 16) + (' ' << 24))

/* PCI service signature: "$PCI" */
#घोषणा PCI_SERVICE		(('$' << 0) + ('P' << 8) + ('C' << 16) + ('I' << 24))

/* PCI BIOS hardware mechanism flags */
#घोषणा PCIBIOS_HW_TYPE1		0x01
#घोषणा PCIBIOS_HW_TYPE2		0x02
#घोषणा PCIBIOS_HW_TYPE1_SPEC		0x10
#घोषणा PCIBIOS_HW_TYPE2_SPEC		0x20

पूर्णांक pcibios_enabled;

/* According to the BIOS specअगरication at:
 * http://members.datafast.net.au/dft0802/specs/bios21.pdf, we could
 * restrict the x zone to some pages and make it ro. But this may be
 * broken on some bios, complex to handle with अटल_protections.
 * We could make the 0xe0000-0x100000 range rox, but this can अवरोध
 * some ISA mapping.
 *
 * So we let's an rw and x hole when pcibios is used. This shouldn't
 * happen क्रम modern प्रणाली with mmconfig, and अगर you करोn't want it
 * you could disable pcibios...
 */
अटल अंतरभूत व्योम set_bios_x(व्योम)
अणु
	pcibios_enabled = 1;
	set_memory_x(PAGE_OFFSET + BIOS_BEGIN, (BIOS_END - BIOS_BEGIN) >> PAGE_SHIFT);
	अगर (__supported_pte_mask & _PAGE_NX)
		prपूर्णांकk(KERN_INFO "PCI: PCI BIOS area is rw and x. Use pci=nobios if you want it NX.\n");
पूर्ण

/*
 * This is the standard काष्ठाure used to identअगरy the entry poपूर्णांक
 * to the BIOS32 Service Directory, as करोcumented in
 * 	Standard BIOS 32-bit Service Directory Proposal
 * 	Revision 0.4 May 24, 1993
 * 	Phoenix Technologies Ltd.
 *	Norwood, MA
 * and the PCI BIOS specअगरication.
 */

जोड़ bios32 अणु
	काष्ठा अणु
		अचिन्हित दीर्घ signature;	/* _32_ */
		अचिन्हित दीर्घ entry;		/* 32 bit physical address */
		अचिन्हित अक्षर revision;		/* Revision level, 0 */
		अचिन्हित अक्षर length;		/* Length in paragraphs should be 01 */
		अचिन्हित अक्षर checksum;		/* All bytes must add up to zero */
		अचिन्हित अक्षर reserved[5]; 	/* Must be zero */
	पूर्ण fields;
	अक्षर अक्षरs[16];
पूर्ण;

/*
 * Physical address of the service directory.  I करोn't know if we're
 * allowed to have more than one of these or not, so just in हाल
 * we'll make pcibios_present() take a memory start parameter and store
 * the array there.
 */

अटल काष्ठा अणु
	अचिन्हित दीर्घ address;
	अचिन्हित लघु segment;
पूर्ण bios32_indirect __initdata = अणु 0, __KERNEL_CS पूर्ण;

/*
 * Returns the entry poपूर्णांक क्रम the given service, शून्य on error
 */

अटल अचिन्हित दीर्घ __init bios32_service(अचिन्हित दीर्घ service)
अणु
	अचिन्हित अक्षर वापस_code;	/* %al */
	अचिन्हित दीर्घ address;		/* %ebx */
	अचिन्हित दीर्घ length;		/* %ecx */
	अचिन्हित दीर्घ entry;		/* %edx */
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__यंत्र__("lcall *(%%edi); cld"
		: "=a" (वापस_code),
		  "=b" (address),
		  "=c" (length),
		  "=d" (entry)
		: "0" (service),
		  "1" (0),
		  "D" (&bios32_indirect));
	local_irq_restore(flags);

	चयन (वापस_code) अणु
		हाल 0:
			वापस address + entry;
		हाल 0x80:	/* Not present */
			prपूर्णांकk(KERN_WARNING "bios32_service(0x%lx): not present\n", service);
			वापस 0;
		शेष: /* Shouldn't happen */
			prपूर्णांकk(KERN_WARNING "bios32_service(0x%lx): returned 0x%x -- BIOS bug!\n",
				service, वापस_code);
			वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा अणु
	अचिन्हित दीर्घ address;
	अचिन्हित लघु segment;
पूर्ण pci_indirect __ro_after_init = अणु
	.address = 0,
	.segment = __KERNEL_CS,
पूर्ण;

अटल पूर्णांक pci_bios_present __ro_after_init;

अटल पूर्णांक __init check_pcibios(व्योम)
अणु
	u32 signature, eax, ebx, ecx;
	u8 status, major_ver, minor_ver, hw_mech;
	अचिन्हित दीर्घ flags, pcibios_entry;

	अगर ((pcibios_entry = bios32_service(PCI_SERVICE))) अणु
		pci_indirect.address = pcibios_entry + PAGE_OFFSET;

		local_irq_save(flags);
		__यंत्र__(
			"lcall *(%%edi); cld\n\t"
			"jc 1f\n\t"
			"xor %%ah, %%ah\n"
			"1:"
			: "=d" (signature),
			  "=a" (eax),
			  "=b" (ebx),
			  "=c" (ecx)
			: "1" (PCIBIOS_PCI_BIOS_PRESENT),
			  "D" (&pci_indirect)
			: "memory");
		local_irq_restore(flags);

		status = (eax >> 8) & 0xff;
		hw_mech = eax & 0xff;
		major_ver = (ebx >> 8) & 0xff;
		minor_ver = ebx & 0xff;
		अगर (pcibios_last_bus < 0)
			pcibios_last_bus = ecx & 0xff;
		DBG("PCI: BIOS probe returned s=%02x hw=%02x ver=%02x.%02x l=%02x\n",
			status, hw_mech, major_ver, minor_ver, pcibios_last_bus);
		अगर (status || signature != PCI_SIGNATURE) अणु
			prपूर्णांकk (KERN_ERR "PCI: BIOS BUG #%x[%08x] found\n",
				status, signature);
			वापस 0;
		पूर्ण
		prपूर्णांकk(KERN_INFO "PCI: PCI BIOS revision %x.%02x entry at 0x%lx, last bus=%d\n",
			major_ver, minor_ver, pcibios_entry, pcibios_last_bus);
#अगर_घोषित CONFIG_PCI_सूचीECT
		अगर (!(hw_mech & PCIBIOS_HW_TYPE1))
			pci_probe &= ~PCI_PROBE_CONF1;
		अगर (!(hw_mech & PCIBIOS_HW_TYPE2))
			pci_probe &= ~PCI_PROBE_CONF2;
#पूर्ण_अगर
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pci_bios_पढ़ो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			 अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 *value)
अणु
	अचिन्हित दीर्घ result = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ bx = (bus << 8) | devfn;
	u16 number = 0, mask = 0;

	WARN_ON(seg);
	अगर (!value || (bus > 255) || (devfn > 255) || (reg > 255))
		वापस -EINVAL;

	raw_spin_lock_irqsave(&pci_config_lock, flags);

	चयन (len) अणु
	हाल 1:
		number = PCIBIOS_READ_CONFIG_BYTE;
		mask = 0xff;
		अवरोध;
	हाल 2:
		number = PCIBIOS_READ_CONFIG_WORD;
		mask = 0xffff;
		अवरोध;
	हाल 4:
		number = PCIBIOS_READ_CONFIG_DWORD;
		अवरोध;
	पूर्ण

	__यंत्र__("lcall *(%%esi); cld\n\t"
		"jc 1f\n\t"
		"xor %%ah, %%ah\n"
		"1:"
		: "=c" (*value),
		  "=a" (result)
		: "1" (number),
		  "b" (bx),
		  "D" ((दीर्घ)reg),
		  "S" (&pci_indirect));
	/*
	 * Zero-extend the result beyond 8 or 16 bits, करो not trust the
	 * BIOS having करोne it:
	 */
	अगर (mask)
		*value &= mask;

	raw_spin_unlock_irqrestore(&pci_config_lock, flags);

	वापस (पूर्णांक)((result & 0xff00) >> 8);
पूर्ण

अटल पूर्णांक pci_bios_ग_लिखो(अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक bus,
			  अचिन्हित पूर्णांक devfn, पूर्णांक reg, पूर्णांक len, u32 value)
अणु
	अचिन्हित दीर्घ result = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ bx = (bus << 8) | devfn;
	u16 number = 0;

	WARN_ON(seg);
	अगर ((bus > 255) || (devfn > 255) || (reg > 255)) 
		वापस -EINVAL;

	raw_spin_lock_irqsave(&pci_config_lock, flags);

	चयन (len) अणु
	हाल 1:
		number = PCIBIOS_WRITE_CONFIG_BYTE;
		अवरोध;
	हाल 2:
		number = PCIBIOS_WRITE_CONFIG_WORD;
		अवरोध;
	हाल 4:
		number = PCIBIOS_WRITE_CONFIG_DWORD;
		अवरोध;
	पूर्ण

	__यंत्र__("lcall *(%%esi); cld\n\t"
		"jc 1f\n\t"
		"xor %%ah, %%ah\n"
		"1:"
		: "=a" (result)
		: "0" (number),
		  "c" (value),
		  "b" (bx),
		  "D" ((दीर्घ)reg),
		  "S" (&pci_indirect));

	raw_spin_unlock_irqrestore(&pci_config_lock, flags);

	वापस (पूर्णांक)((result & 0xff00) >> 8);
पूर्ण


/*
 * Function table क्रम BIOS32 access
 */

अटल स्थिर काष्ठा pci_raw_ops pci_bios_access = अणु
	.पढ़ो =		pci_bios_पढ़ो,
	.ग_लिखो =	pci_bios_ग_लिखो
पूर्ण;

/*
 * Try to find PCI BIOS.
 */

अटल स्थिर काष्ठा pci_raw_ops *__init pci_find_bios(व्योम)
अणु
	जोड़ bios32 *check;
	अचिन्हित अक्षर sum;
	पूर्णांक i, length;

	/*
	 * Follow the standard procedure क्रम locating the BIOS32 Service
	 * directory by scanning the permissible address range from
	 * 0xe0000 through 0xfffff क्रम a valid BIOS32 काष्ठाure.
	 */

	क्रम (check = (जोड़ bios32 *) __va(0xe0000);
	     check <= (जोड़ bios32 *) __va(0xffff0);
	     ++check) अणु
		दीर्घ sig;
		अगर (get_kernel_nofault(sig, &check->fields.signature))
			जारी;

		अगर (check->fields.signature != BIOS32_SIGNATURE)
			जारी;
		length = check->fields.length * 16;
		अगर (!length)
			जारी;
		sum = 0;
		क्रम (i = 0; i < length ; ++i)
			sum += check->अक्षरs[i];
		अगर (sum != 0)
			जारी;
		अगर (check->fields.revision != 0) अणु
			prपूर्णांकk("PCI: unsupported BIOS32 revision %d at 0x%p\n",
				check->fields.revision, check);
			जारी;
		पूर्ण
		DBG("PCI: BIOS32 Service Directory structure at 0x%p\n", check);
		अगर (check->fields.entry >= 0x100000) अणु
			prपूर्णांकk("PCI: BIOS32 entry (0x%p) in high memory, "
					"cannot use.\n", check);
			वापस शून्य;
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ bios32_entry = check->fields.entry;
			DBG("PCI: BIOS32 Service Directory entry at 0x%lx\n",
					bios32_entry);
			bios32_indirect.address = bios32_entry + PAGE_OFFSET;
			set_bios_x();
			अगर (check_pcibios())
				वापस &pci_bios_access;
		पूर्ण
		अवरोध;	/* Hopefully more than one BIOS32 cannot happen... */
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 *  BIOS Functions क्रम IRQ Routing
 */

काष्ठा irq_routing_options अणु
	u16 size;
	काष्ठा irq_info *table;
	u16 segment;
पूर्ण __attribute__((packed));

काष्ठा irq_routing_table * pcibios_get_irq_routing_table(व्योम)
अणु
	काष्ठा irq_routing_options opt;
	काष्ठा irq_routing_table *rt = शून्य;
	पूर्णांक ret, map;
	अचिन्हित दीर्घ page;

	अगर (!pci_bios_present)
		वापस शून्य;
	page = __get_मुक्त_page(GFP_KERNEL);
	अगर (!page)
		वापस शून्य;
	opt.table = (काष्ठा irq_info *) page;
	opt.size = PAGE_SIZE;
	opt.segment = __KERNEL_DS;

	DBG("PCI: Fetching IRQ routing table... ");
	__यंत्र__("push %%es\n\t"
		"push %%ds\n\t"
		"pop  %%es\n\t"
		"lcall *(%%esi); cld\n\t"
		"pop %%es\n\t"
		"jc 1f\n\t"
		"xor %%ah, %%ah\n"
		"1:"
		: "=a" (ret),
		  "=b" (map),
		  "=m" (opt)
		: "0" (PCIBIOS_GET_ROUTING_OPTIONS),
		  "1" (0),
		  "D" ((दीर्घ) &opt),
		  "S" (&pci_indirect),
		  "m" (opt)
		: "memory");
	DBG("OK  ret=%d, size=%d, map=%x\n", ret, opt.size, map);
	अगर (ret & 0xff00)
		prपूर्णांकk(KERN_ERR "PCI: Error %02x when fetching IRQ routing table.\n", (ret >> 8) & 0xff);
	अन्यथा अगर (opt.size) अणु
		rt = kदो_स्मृति(माप(काष्ठा irq_routing_table) + opt.size, GFP_KERNEL);
		अगर (rt) अणु
			स_रखो(rt, 0, माप(काष्ठा irq_routing_table));
			rt->size = opt.size + माप(काष्ठा irq_routing_table);
			rt->exclusive_irqs = map;
			स_नकल(rt->slots, (व्योम *) page, opt.size);
			prपूर्णांकk(KERN_INFO "PCI: Using BIOS Interrupt Routing Table\n");
		पूर्ण
	पूर्ण
	मुक्त_page(page);
	वापस rt;
पूर्ण
EXPORT_SYMBOL(pcibios_get_irq_routing_table);

पूर्णांक pcibios_set_irq_routing(काष्ठा pci_dev *dev, पूर्णांक pin, पूर्णांक irq)
अणु
	पूर्णांक ret;

	__यंत्र__("lcall *(%%esi); cld\n\t"
		"jc 1f\n\t"
		"xor %%ah, %%ah\n"
		"1:"
		: "=a" (ret)
		: "0" (PCIBIOS_SET_PCI_HW_INT),
		  "b" ((dev->bus->number << 8) | dev->devfn),
		  "c" ((irq << 8) | (pin + 10)),
		  "S" (&pci_indirect));
	वापस !(ret & 0xff00);
पूर्ण
EXPORT_SYMBOL(pcibios_set_irq_routing);

व्योम __init pci_pcbios_init(व्योम)
अणु
	अगर ((pci_probe & PCI_PROBE_BIOS) 
		&& ((raw_pci_ops = pci_find_bios()))) अणु
		pci_bios_present = 1;
	पूर्ण
पूर्ण

