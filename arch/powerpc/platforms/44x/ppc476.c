<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerPC 476FPE board specअगरic routines
 *
 * Copyright तऊ 2013 Tony Breeds IBM Corporation
 * Copyright तऊ 2013 Alistair Popple IBM Corporation
 *
 * Based on earlier code:
 *    Matt Porter <mporter@kernel.crashing.org>
 *    Copyright 2002-2005 MontaVista Software Inc.
 *
 *    Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *    Copyright (c) 2003-2005 Zultys Technologies
 *
 *    Rewritten and ported to the merged घातerpc tree:
 *    Copyright 2007 David Gibson <dwg@au1.ibm.com>, IBM Corporation.
 *    Copyright तऊ 2011 David Kliekamp IBM Corporation
 */

#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/rtc.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/uic.h>
#समावेश <यंत्र/ppc4xx.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/swiotlb.h>

#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>

अटल स्थिर काष्ठा of_device_id ppc47x_of_bus[] __initस्थिर = अणु
	अणु .compatible = "ibm,plb4", पूर्ण,
	अणु .compatible = "ibm,plb6", पूर्ण,
	अणु .compatible = "ibm,opb", पूर्ण,
	अणु .compatible = "ibm,ebc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

/* The EEPROM is missing and the शेष values are bogus.  This क्रमces USB in
 * to EHCI mode */
अटल व्योम quirk_ppc_currituck_usb_fixup(काष्ठा pci_dev *dev)
अणु
	अगर (of_machine_is_compatible("ibm,currituck")) अणु
		pci_ग_लिखो_config_dword(dev, 0xe0, 0x0114231f);
		pci_ग_लिखो_config_dword(dev, 0xe4, 0x00006c40);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(0x1033, 0x0035, quirk_ppc_currituck_usb_fixup);

/* Akebono has an AVR microcontroller attached to the I2C bus
 * which is used to घातer off/reset the प्रणाली. */

/* AVR I2C Commands */
#घोषणा AVR_PWRCTL_CMD (0x26)

/* Flags क्रम the घातer control I2C commands */
#घोषणा AVR_PWRCTL_PWROFF (0x01)
#घोषणा AVR_PWRCTL_RESET (0x02)

अटल काष्ठा i2c_client *avr_i2c_client;
अटल व्योम __noवापस avr_halt_प्रणाली(पूर्णांक pwrctl_flags)
अणु
	/* Request the AVR to reset the प्रणाली */
	i2c_smbus_ग_लिखो_byte_data(avr_i2c_client,
				  AVR_PWRCTL_CMD, pwrctl_flags);

	/* Wait क्रम प्रणाली to be reset */
	जबतक (1)
		;
पूर्ण

अटल व्योम avr_घातer_off_प्रणाली(व्योम)
अणु
	avr_halt_प्रणाली(AVR_PWRCTL_PWROFF);
पूर्ण

अटल व्योम __noवापस avr_reset_प्रणाली(अक्षर *cmd)
अणु
	avr_halt_प्रणाली(AVR_PWRCTL_RESET);
पूर्ण

अटल पूर्णांक avr_probe(काष्ठा i2c_client *client)
अणु
	avr_i2c_client = client;
	ppc_md.restart = avr_reset_प्रणाली;
	pm_घातer_off = avr_घातer_off_प्रणाली;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id avr_id[] = अणु
	अणु "akebono-avr", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver avr_driver = अणु
	.driver = अणु
		.name = "akebono-avr",
	पूर्ण,
	.probe_new = avr_probe,
	.id_table = avr_id,
पूर्ण;

अटल पूर्णांक __init ppc47x_device_probe(व्योम)
अणु
	i2c_add_driver(&avr_driver);
	of_platक्रमm_bus_probe(शून्य, ppc47x_of_bus, शून्य);

	वापस 0;
पूर्ण
machine_device_initcall(ppc47x, ppc47x_device_probe);

अटल व्योम __init ppc47x_init_irq(व्योम)
अणु
	काष्ठा device_node *np;

	/* Find top level पूर्णांकerrupt controller */
	क्रम_each_node_with_property(np, "interrupt-controller") अणु
		अगर (of_get_property(np, "interrupts", शून्य) == शून्य)
			अवरोध;
	पूर्ण
	अगर (np == शून्य)
		panic("Can't find top level interrupt controller");

	/* Check type and करो appropriate initialization */
	अगर (of_device_is_compatible(np, "chrp,open-pic")) अणु
		/* The MPIC driver will get everything it needs from the
		 * device-tree, just pass 0 to all arguments
		 */
		काष्ठा mpic *mpic =
			mpic_alloc(np, 0, MPIC_NO_RESET, 0, 0, " MPIC     ");
		BUG_ON(mpic == शून्य);
		mpic_init(mpic);
		ppc_md.get_irq = mpic_get_irq;
	पूर्ण अन्यथा
		panic("Unrecognized top level interrupt controller");
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम smp_ppc47x_setup_cpu(पूर्णांक cpu)
अणु
	mpic_setup_this_cpu();
पूर्ण

अटल पूर्णांक smp_ppc47x_kick_cpu(पूर्णांक cpu)
अणु
	काष्ठा device_node *cpunode = of_get_cpu_node(cpu, शून्य);
	स्थिर u64 *spin_table_addr_prop;
	u32 *spin_table;
	बाह्य व्योम start_secondary_47x(व्योम);

	BUG_ON(cpunode == शून्य);

	/* Assume spin table. We could test क्रम the enable-method in
	 * the device-tree but currently there's little point as it's
	 * our only supported method
	 */
	spin_table_addr_prop =
		of_get_property(cpunode, "cpu-release-addr", शून्य);

	अगर (spin_table_addr_prop == शून्य) अणु
		pr_err("CPU%d: Can't start, missing cpu-release-addr !\n",
		       cpu);
		वापस 1;
	पूर्ण

	/* Assume it's mapped as part of the linear mapping. This is a bit
	 * fishy but will work fine क्रम now
	 *
	 * XXX: Is there any reason to assume dअगरferently?
	 */
	spin_table = (u32 *)__va(*spin_table_addr_prop);
	pr_debug("CPU%d: Spin table mapped at %p\n", cpu, spin_table);

	spin_table[3] = cpu;
	smp_wmb();
	spin_table[1] = __pa(start_secondary_47x);
	mb();

	वापस 0;
पूर्ण

अटल काष्ठा smp_ops_t ppc47x_smp_ops = अणु
	.probe		= smp_mpic_probe,
	.message_pass	= smp_mpic_message_pass,
	.setup_cpu	= smp_ppc47x_setup_cpu,
	.kick_cpu	= smp_ppc47x_kick_cpu,
	.give_समयbase	= smp_generic_give_समयbase,
	.take_समयbase	= smp_generic_take_समयbase,
पूर्ण;

अटल व्योम __init ppc47x_smp_init(व्योम)
अणु
	अगर (mmu_has_feature(MMU_FTR_TYPE_47x))
		smp_ops = &ppc47x_smp_ops;
पूर्ण

#अन्यथा /* CONFIG_SMP */
अटल व्योम __init ppc47x_smp_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम __init ppc47x_setup_arch(व्योम)
अणु

	/* No need to check the DMA config as we /know/ our winकरोws are all of
	 * RAM.  Lets hope that करोesn't change */
	swiotlb_detect_4g();

	ppc47x_smp_init();
पूर्ण

अटल पूर्णांक board_rev = -1;
अटल पूर्णांक __init ppc47x_get_board_rev(व्योम)
अणु
	पूर्णांक reg;
	u8 *fpga;
	काष्ठा device_node *np = शून्य;

	अगर (of_machine_is_compatible("ibm,currituck")) अणु
		np = of_find_compatible_node(शून्य, शून्य, "ibm,currituck-fpga");
		reg = 0;
	पूर्ण अन्यथा अगर (of_machine_is_compatible("ibm,akebono")) अणु
		np = of_find_compatible_node(शून्य, शून्य, "ibm,akebono-fpga");
		reg = 2;
	पूर्ण

	अगर (!np)
		जाओ fail;

	fpga = (u8 *) of_iomap(np, 0);
	of_node_put(np);
	अगर (!fpga)
		जाओ fail;

	board_rev = ioपढ़ो8(fpga + reg) & 0x03;
	pr_info("%s: Found board revision %d\n", __func__, board_rev);
	iounmap(fpga);
	वापस 0;

fail:
	pr_info("%s: Unable to find board revision\n", __func__);
	वापस 0;
पूर्ण
machine_arch_initcall(ppc47x, ppc47x_get_board_rev);

/* Use USB controller should have been hardware swizzled but it wasn't :( */
अटल व्योम ppc47x_pci_irq_fixup(काष्ठा pci_dev *dev)
अणु
	अगर (dev->venकरोr == 0x1033 && (dev->device == 0x0035 ||
				      dev->device == 0x00e0)) अणु
		अगर (board_rev == 0) अणु
			dev->irq = irq_create_mapping(शून्य, 47);
			pr_info("%s: Mapping irq %d\n", __func__, dev->irq);
		पूर्ण अन्यथा अगर (board_rev == 2) अणु
			dev->irq = irq_create_mapping(शून्य, 49);
			pr_info("%s: Mapping irq %d\n", __func__, dev->irq);
		पूर्ण अन्यथा अणु
			pr_alert("%s: Unknown board revision\n", __func__);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init ppc47x_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("ibm,akebono"))
		वापस 1;

	अगर (of_machine_is_compatible("ibm,currituck")) अणु
		ppc_md.pci_irq_fixup = ppc47x_pci_irq_fixup;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

define_machine(ppc47x) अणु
	.name			= "PowerPC 47x",
	.probe			= ppc47x_probe,
	.progress		= udbg_progress,
	.init_IRQ		= ppc47x_init_irq,
	.setup_arch		= ppc47x_setup_arch,
	.restart		= ppc4xx_reset_प्रणाली,
	.calibrate_decr		= generic_calibrate_decr,
पूर्ण;
