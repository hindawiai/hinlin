<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SDK7786 FPGA PCIe mux handling
 *
 * Copyright (C) 2010  Paul Mundt
 */
#घोषणा pr_fmt(fmt) "PCI: " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <mach/fpga.h>

/*
 * The SDK7786 FPGA supports mangling of most of the slots in some way or
 * another. Slots 3/4 are special in that only one can be supported at a
 * समय, and both appear on port 3 to the PCI bus scan. Enabling slot 4
 * (the horizontal edge connector) will disable slot 3 entirely.
 *
 * Misconfigurations can be detected through the FPGA via the slot
 * resistors to determine card presence. Hotplug reमुख्यs unsupported.
 */
अटल अचिन्हित पूर्णांक slot4en __initdata;

अक्षर *__init pcibios_setup(अक्षर *str)
अणु
	अगर (म_भेद(str, "slot4en") == 0) अणु
		slot4en = 1;
		वापस शून्य;
	पूर्ण

	वापस str;
पूर्ण

अटल पूर्णांक __init sdk7786_pci_init(व्योम)
अणु
	u16 data = fpga_पढ़ो_reg(PCIECR);

	/*
	 * Enable slot #4 अगर it's been specअगरied on the command line.
	 *
	 * Optionally reroute अगर slot #4 has a card present जबतक slot #3
	 * करोes not, regardless of command line value.
	 *
	 * Card presence is logically inverted.
	 */
	slot4en ?: (!(data & PCIECR_PRST4) && (data & PCIECR_PRST3));
	अगर (slot4en) अणु
		pr_info("Activating PCIe slot#4 (disabling slot#3)\n");

		data &= ~PCIECR_PCIEMUX1;
		fpga_ग_लिखो_reg(data, PCIECR);

		/* Warn about क्रमced rerouting अगर slot#3 is occupied */
		अगर ((data & PCIECR_PRST3) == 0) अणु
			pr_warn("Unreachable card detected in slot#3\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा
		pr_info("PCIe slot#4 disabled\n");

	वापस 0;
पूर्ण
postcore_initcall(sdk7786_pci_init);
