<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * setup.c - boot समय setup code
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/समय.स>
#समावेश <linux/ioport.h>

#समावेश <यंत्र/mach-rc32434/rb.h>
#समावेश <यंत्र/mach-rc32434/pci.h>

काष्ठा pci_reg __iomem *pci_reg;
EXPORT_SYMBOL(pci_reg);

अटल काष्ठा resource pci0_res[] = अणु
	अणु
		.name = "pci_reg0",
		.start = PCI0_BASE_ADDR,
		.end = PCI0_BASE_ADDR + माप(काष्ठा pci_reg),
		.flags = IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल व्योम rb_machine_restart(अक्षर *command)
अणु
	/* just jump to the reset vector */
	ग_लिखोl(0x80000001, IDT434_REG_BASE + RST);
	((व्योम (*)(व्योम)) KSEG1ADDR(0x1FC00000u))();
पूर्ण

अटल व्योम rb_machine_halt(व्योम)
अणु
	क्रम (;;)
		जारी;
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	u32 val;

	_machine_restart = rb_machine_restart;
	_machine_halt = rb_machine_halt;
	pm_घातer_off = rb_machine_halt;

	set_io_port_base(KSEG1);

	pci_reg = ioremap(pci0_res[0].start,
				pci0_res[0].end - pci0_res[0].start);
	अगर (!pci_reg) अणु
		prपूर्णांकk(KERN_ERR "Could not remap PCI registers\n");
		वापस;
	पूर्ण

	val = __raw_पढ़ोl(&pci_reg->pcic);
	val &= 0xFFFFFF7;
	__raw_ग_लिखोl(val, (व्योम *)&pci_reg->pcic);

#अगर_घोषित CONFIG_PCI
	/* Enable PCI पूर्णांकerrupts in EPLD Mask रेजिस्टर */
	*epld_mask = 0x0;
	*(epld_mask + 1) = 0x0;
#पूर्ण_अगर
	ग_लिखो_c0_wired(0);
पूर्ण

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	चयन (mips_machtype) अणु
	हाल MACH_MIKROTIK_RB532A:
		वापस "Mikrotik RB532A";
		अवरोध;
	शेष:
		वापस "Mikrotik RB532";
		अवरोध;
	पूर्ण
पूर्ण
