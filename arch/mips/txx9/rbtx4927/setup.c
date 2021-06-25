<शैली गुरु>
/*
 * Toshiba rbtx4927 specअगरic setup
 *
 * Author: MontaVista Software, Inc.
 *	   source@mvista.com
 *
 * Copyright 2001-2002 MontaVista Software Inc.
 *
 * Copyright (C) 1996, 97, 2001, 04  Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2000 RidgeRun, Inc.
 * Author: RidgeRun, Inc.
 *   glonnon@ridgerun.com, skranz@ridgerun.com, stevej@ridgerun.com
 *
 * Copyright 2001 MontaVista Software Inc.
 * Author: jsun@mvista.com or jsun@junsun.net
 *
 * Copyright 2002 MontaVista Software Inc.
 * Author: Michael Pruznick, michael_pruznick@mvista.com
 *
 * Copyright (C) 2000-2001 Toshiba Corporation
 *
 * Copyright (C) 2004 MontaVista Software Inc.
 * Author: Manish Lachwani, mlachwani@mvista.com
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/leds.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/txx9pपन.स>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/pci.h>
#समावेश <यंत्र/txx9/rbtx4927.h>
#समावेश <यंत्र/txx9/tx4938.h>	/* क्रम TX4937 */

#अगर_घोषित CONFIG_PCI
अटल व्योम __init tx4927_pci_setup(व्योम)
अणु
	पूर्णांक extarb = !(__raw_पढ़ोq(&tx4927_ccfgptr->ccfg) & TX4927_CCFG_PCIARB);
	काष्ठा pci_controller *c = &txx9_primary_pcic;

	रेजिस्टर_pci_controller(c);

	अगर (__raw_पढ़ोq(&tx4927_ccfgptr->ccfg) & TX4927_CCFG_PCI66)
		txx9_pci_option =
			(txx9_pci_option & ~TXX9_PCI_OPT_CLK_MASK) |
			TXX9_PCI_OPT_CLK_66; /* alपढ़ोy configured */

	/* Reset PCI Bus */
	ग_लिखोb(1, rbtx4927_pcireset_addr);
	/* Reset PCIC */
	txx9_set64(&tx4927_ccfgptr->clkctr, TX4927_CLKCTR_PCIRST);
	अगर ((txx9_pci_option & TXX9_PCI_OPT_CLK_MASK) ==
	    TXX9_PCI_OPT_CLK_66)
		tx4927_pciclk66_setup();
	mdelay(10);
	/* clear PCIC reset */
	txx9_clear64(&tx4927_ccfgptr->clkctr, TX4927_CLKCTR_PCIRST);
	ग_लिखोb(0, rbtx4927_pcireset_addr);
	iob();

	tx4927_report_pciclk();
	tx4927_pcic_setup(tx4927_pcicptr, c, extarb);
	अगर ((txx9_pci_option & TXX9_PCI_OPT_CLK_MASK) ==
	    TXX9_PCI_OPT_CLK_AUTO &&
	    txx9_pci66_check(c, 0, 0)) अणु
		/* Reset PCI Bus */
		ग_लिखोb(1, rbtx4927_pcireset_addr);
		/* Reset PCIC */
		txx9_set64(&tx4927_ccfgptr->clkctr, TX4927_CLKCTR_PCIRST);
		tx4927_pciclk66_setup();
		mdelay(10);
		/* clear PCIC reset */
		txx9_clear64(&tx4927_ccfgptr->clkctr, TX4927_CLKCTR_PCIRST);
		ग_लिखोb(0, rbtx4927_pcireset_addr);
		iob();
		/* Reinitialize PCIC */
		tx4927_report_pciclk();
		tx4927_pcic_setup(tx4927_pcicptr, c, extarb);
	पूर्ण
	tx4927_setup_pcierr_irq();
पूर्ण

अटल व्योम __init tx4937_pci_setup(व्योम)
अणु
	पूर्णांक extarb = !(__raw_पढ़ोq(&tx4938_ccfgptr->ccfg) & TX4938_CCFG_PCIARB);
	काष्ठा pci_controller *c = &txx9_primary_pcic;

	रेजिस्टर_pci_controller(c);

	अगर (__raw_पढ़ोq(&tx4938_ccfgptr->ccfg) & TX4938_CCFG_PCI66)
		txx9_pci_option =
			(txx9_pci_option & ~TXX9_PCI_OPT_CLK_MASK) |
			TXX9_PCI_OPT_CLK_66; /* alपढ़ोy configured */

	/* Reset PCI Bus */
	ग_लिखोb(1, rbtx4927_pcireset_addr);
	/* Reset PCIC */
	txx9_set64(&tx4938_ccfgptr->clkctr, TX4938_CLKCTR_PCIRST);
	अगर ((txx9_pci_option & TXX9_PCI_OPT_CLK_MASK) ==
	    TXX9_PCI_OPT_CLK_66)
		tx4938_pciclk66_setup();
	mdelay(10);
	/* clear PCIC reset */
	txx9_clear64(&tx4938_ccfgptr->clkctr, TX4938_CLKCTR_PCIRST);
	ग_लिखोb(0, rbtx4927_pcireset_addr);
	iob();

	tx4938_report_pciclk();
	tx4927_pcic_setup(tx4938_pcicptr, c, extarb);
	अगर ((txx9_pci_option & TXX9_PCI_OPT_CLK_MASK) ==
	    TXX9_PCI_OPT_CLK_AUTO &&
	    txx9_pci66_check(c, 0, 0)) अणु
		/* Reset PCI Bus */
		ग_लिखोb(1, rbtx4927_pcireset_addr);
		/* Reset PCIC */
		txx9_set64(&tx4938_ccfgptr->clkctr, TX4938_CLKCTR_PCIRST);
		tx4938_pciclk66_setup();
		mdelay(10);
		/* clear PCIC reset */
		txx9_clear64(&tx4938_ccfgptr->clkctr, TX4938_CLKCTR_PCIRST);
		ग_लिखोb(0, rbtx4927_pcireset_addr);
		iob();
		/* Reinitialize PCIC */
		tx4938_report_pciclk();
		tx4927_pcic_setup(tx4938_pcicptr, c, extarb);
	पूर्ण
	tx4938_setup_pcierr_irq();
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम tx4927_pci_setup(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम tx4937_pci_setup(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

अटल व्योम __init rbtx4927_gpio_init(व्योम)
अणु
	/* TX4927-SIO DTR on (PIO[15]) */
	gpio_request(15, "sio-dtr");
	gpio_direction_output(15, 1);

	tx4927_sio_init(0, 0);
पूर्ण

अटल व्योम __init rbtx4927_arch_init(व्योम)
अणु
	txx9_gpio_init(TX4927_PIO_REG & 0xfffffffffULL, 0, TX4927_NUM_PIO);

	rbtx4927_gpio_init();

	tx4927_pci_setup();
पूर्ण

अटल व्योम __init rbtx4937_arch_init(व्योम)
अणु
	txx9_gpio_init(TX4938_PIO_REG & 0xfffffffffULL, 0, TX4938_NUM_PIO);

	rbtx4927_gpio_init();

	tx4937_pci_setup();
पूर्ण

अटल व्योम toshiba_rbtx4927_restart(अक्षर *command)
अणु
	/* enable the s/w reset रेजिस्टर */
	ग_लिखोb(1, rbtx4927_softresetlock_addr);

	/* रुको क्रम enable to be seen */
	जबतक (!(पढ़ोb(rbtx4927_softresetlock_addr) & 1))
		;

	/* करो a s/w reset */
	ग_लिखोb(1, rbtx4927_softreset_addr);

	/* fallback */
	(*_machine_halt)();
पूर्ण

अटल व्योम __init rbtx4927_घड़ी_init(व्योम);
अटल व्योम __init rbtx4937_घड़ी_init(व्योम);

अटल व्योम __init rbtx4927_mem_setup(व्योम)
अणु
	अगर (TX4927_REV_PCODE() == 0x4927) अणु
		rbtx4927_घड़ी_init();
		tx4927_setup();
	पूर्ण अन्यथा अणु
		rbtx4937_घड़ी_init();
		tx4938_setup();
	पूर्ण

	_machine_restart = toshiba_rbtx4927_restart;

#अगर_घोषित CONFIG_PCI
	txx9_alloc_pci_controller(&txx9_primary_pcic,
				  RBTX4927_PCIMEM, RBTX4927_PCIMEM_SIZE,
				  RBTX4927_PCIIO, RBTX4927_PCIIO_SIZE);
	txx9_board_pcibios_setup = tx4927_pcibios_setup;
#अन्यथा
	set_io_port_base(KSEG1 + RBTX4927_ISA_IO_OFFSET);
#पूर्ण_अगर
पूर्ण

अटल व्योम __init rbtx4927_घड़ी_init(व्योम)
अणु
	/*
	 * ASSUMPTION: PCIDIVMODE is configured क्रम PCI 33MHz or 66MHz.
	 *
	 * For TX4927:
	 * PCIDIVMODE[12:11]'s initial value is given by S9[4:3] (ON:0, OFF:1).
	 * CPU 166MHz: PCI 66MHz : PCIDIVMODE: 00 (1/2.5)
	 * CPU 200MHz: PCI 66MHz : PCIDIVMODE: 01 (1/3)
	 * CPU 166MHz: PCI 33MHz : PCIDIVMODE: 10 (1/5)
	 * CPU 200MHz: PCI 33MHz : PCIDIVMODE: 11 (1/6)
	 * i.e. S9[3]: ON (83MHz), OFF (100MHz)
	 */
	चयन ((अचिन्हित दीर्घ)__raw_पढ़ोq(&tx4927_ccfgptr->ccfg) &
		TX4927_CCFG_PCIDIVMODE_MASK) अणु
	हाल TX4927_CCFG_PCIDIVMODE_2_5:
	हाल TX4927_CCFG_PCIDIVMODE_5:
		txx9_cpu_घड़ी = 166666666;	/* 166MHz */
		अवरोध;
	शेष:
		txx9_cpu_घड़ी = 200000000;	/* 200MHz */
	पूर्ण
पूर्ण

अटल व्योम __init rbtx4937_घड़ी_init(व्योम)
अणु
	/*
	 * ASSUMPTION: PCIDIVMODE is configured क्रम PCI 33MHz or 66MHz.
	 *
	 * For TX4937:
	 * PCIDIVMODE[12:11]'s initial value is given by S1[5:4] (ON:0, OFF:1)
	 * PCIDIVMODE[10] is 0.
	 * CPU 266MHz: PCI 33MHz : PCIDIVMODE: 000 (1/8)
	 * CPU 266MHz: PCI 66MHz : PCIDIVMODE: 001 (1/4)
	 * CPU 300MHz: PCI 33MHz : PCIDIVMODE: 010 (1/9)
	 * CPU 300MHz: PCI 66MHz : PCIDIVMODE: 011 (1/4.5)
	 * CPU 333MHz: PCI 33MHz : PCIDIVMODE: 100 (1/10)
	 * CPU 333MHz: PCI 66MHz : PCIDIVMODE: 101 (1/5)
	 */
	चयन ((अचिन्हित दीर्घ)__raw_पढ़ोq(&tx4938_ccfgptr->ccfg) &
		TX4938_CCFG_PCIDIVMODE_MASK) अणु
	हाल TX4938_CCFG_PCIDIVMODE_8:
	हाल TX4938_CCFG_PCIDIVMODE_4:
		txx9_cpu_घड़ी = 266666666;	/* 266MHz */
		अवरोध;
	हाल TX4938_CCFG_PCIDIVMODE_9:
	हाल TX4938_CCFG_PCIDIVMODE_4_5:
		txx9_cpu_घड़ी = 300000000;	/* 300MHz */
		अवरोध;
	शेष:
		txx9_cpu_घड़ी = 333333333;	/* 333MHz */
	पूर्ण
पूर्ण

अटल व्योम __init rbtx4927_समय_init(व्योम)
अणु
	tx4927_समय_init(0);
पूर्ण

अटल व्योम __init toshiba_rbtx4927_rtc_init(व्योम)
अणु
	काष्ठा resource res = अणु
		.start	= RBTX4927_BRAMRTC_BASE - IO_BASE,
		.end	= RBTX4927_BRAMRTC_BASE - IO_BASE + 0x800 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण;
	platक्रमm_device_रेजिस्टर_simple("rtc-ds1742", -1, &res, 1);
पूर्ण

अटल व्योम __init rbtx4927_ne_init(व्योम)
अणु
	काष्ठा resource res[] = अणु
		अणु
			.start	= RBTX4927_RTL_8019_BASE,
			.end	= RBTX4927_RTL_8019_BASE + 0x20 - 1,
			.flags	= IORESOURCE_IO,
		पूर्ण, अणु
			.start	= RBTX4927_RTL_8019_IRQ,
			.flags	= IORESOURCE_IRQ,
		पूर्ण
	पूर्ण;
	platक्रमm_device_रेजिस्टर_simple("ne", -1, res, ARRAY_SIZE(res));
पूर्ण

अटल व्योम __init rbtx4927_mtd_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		tx4927_mtd_init(i);
पूर्ण

अटल व्योम __init rbtx4927_gpioled_init(व्योम)
अणु
	अटल स्थिर काष्ठा gpio_led leds[] = अणु
		अणु .name = "gpioled:green:0", .gpio = 0, .active_low = 1, पूर्ण,
		अणु .name = "gpioled:green:1", .gpio = 1, .active_low = 1, पूर्ण,
	पूर्ण;
	अटल काष्ठा gpio_led_platक्रमm_data pdata = अणु
		.num_leds = ARRAY_SIZE(leds),
		.leds = leds,
	पूर्ण;
	काष्ठा platक्रमm_device *pdev = platक्रमm_device_alloc("leds-gpio", 0);

	अगर (!pdev)
		वापस;
	pdev->dev.platक्रमm_data = &pdata;
	अगर (platक्रमm_device_add(pdev))
		platक्रमm_device_put(pdev);
पूर्ण

अटल व्योम __init rbtx4927_device_init(व्योम)
अणु
	toshiba_rbtx4927_rtc_init();
	rbtx4927_ne_init();
	tx4927_wdt_init();
	rbtx4927_mtd_init();
	अगर (TX4927_REV_PCODE() == 0x4927) अणु
		tx4927_dmac_init(2);
		tx4927_aclc_init(0, 1);
	पूर्ण अन्यथा अणु
		tx4938_dmac_init(0, 2);
		tx4938_aclc_init();
	पूर्ण
	platक्रमm_device_रेजिस्टर_simple("txx9aclc-generic", -1, शून्य, 0);
	txx9_iocled_init(RBTX4927_LED_ADDR - IO_BASE, -1, 3, 1, "green", शून्य);
	rbtx4927_gpioled_init();
पूर्ण

काष्ठा txx9_board_vec rbtx4927_vec __initdata = अणु
	.प्रणाली = "Toshiba RBTX4927",
	.prom_init = rbtx4927_prom_init,
	.mem_setup = rbtx4927_mem_setup,
	.irq_setup = rbtx4927_irq_setup,
	.समय_init = rbtx4927_समय_init,
	.device_init = rbtx4927_device_init,
	.arch_init = rbtx4927_arch_init,
#अगर_घोषित CONFIG_PCI
	.pci_map_irq = rbtx4927_pci_map_irq,
#पूर्ण_अगर
पूर्ण;
काष्ठा txx9_board_vec rbtx4937_vec __initdata = अणु
	.प्रणाली = "Toshiba RBTX4937",
	.prom_init = rbtx4927_prom_init,
	.mem_setup = rbtx4927_mem_setup,
	.irq_setup = rbtx4927_irq_setup,
	.समय_init = rbtx4927_समय_init,
	.device_init = rbtx4927_device_init,
	.arch_init = rbtx4937_arch_init,
#अगर_घोषित CONFIG_PCI
	.pci_map_irq = rbtx4927_pci_map_irq,
#पूर्ण_अगर
पूर्ण;
