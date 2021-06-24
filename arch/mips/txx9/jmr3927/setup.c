<शैली गुरु>
/*
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Copyright 2001 MontaVista Software Inc.
 * Author: MontaVista Software, Inc.
 *              ahennessy@mvista.com
 *
 * Copyright (C) 2000-2001 Toshiba Corporation
 * Copyright (C) 2007 Ralf Baechle (ralf@linux-mips.org)
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/txx9pपन.स>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/pci.h>
#समावेश <यंत्र/txx9/jmr3927.h>
#समावेश <यंत्र/mipsregs.h>

अटल व्योम jmr3927_machine_restart(अक्षर *command)
अणु
	local_irq_disable();
#अगर 1	/* Resetting PCI bus */
	jmr3927_ioc_reg_out(0, JMR3927_IOC_RESET_ADDR);
	jmr3927_ioc_reg_out(JMR3927_IOC_RESET_PCI, JMR3927_IOC_RESET_ADDR);
	(व्योम)jmr3927_ioc_reg_in(JMR3927_IOC_RESET_ADDR);	/* flush WB */
	mdelay(1);
	jmr3927_ioc_reg_out(0, JMR3927_IOC_RESET_ADDR);
#पूर्ण_अगर
	jmr3927_ioc_reg_out(JMR3927_IOC_RESET_CPU, JMR3927_IOC_RESET_ADDR);
	/* fallback */
	(*_machine_halt)();
पूर्ण

अटल व्योम __init jmr3927_समय_init(व्योम)
अणु
	tx3927_समय_init(0, 1);
पूर्ण

#घोषणा DO_WRITE_THROUGH

अटल व्योम jmr3927_board_init(व्योम);

अटल व्योम __init jmr3927_mem_setup(व्योम)
अणु
	set_io_port_base(JMR3927_PORT_BASE + JMR3927_PCIIO);

	_machine_restart = jmr3927_machine_restart;

	/* cache setup */
	अणु
		अचिन्हित पूर्णांक conf;
#अगर_घोषित DO_WRITE_THROUGH
		पूर्णांक mips_config_cwfon = 0;
		पूर्णांक mips_config_wbon = 0;
#अन्यथा
		पूर्णांक mips_config_cwfon = 1;
		पूर्णांक mips_config_wbon = 1;
#पूर्ण_अगर

		conf = पढ़ो_c0_conf();
		conf &= ~(TX39_CONF_WBON | TX39_CONF_CWFON);
		conf |= mips_config_wbon ? TX39_CONF_WBON : 0;
		conf |= mips_config_cwfon ? TX39_CONF_CWFON : 0;

		ग_लिखो_c0_conf(conf);
		ग_लिखो_c0_cache(0);
	पूर्ण

	/* initialize board */
	jmr3927_board_init();

	tx3927_sio_init(0, 1 << 1); /* ch1: noCTS */
पूर्ण

अटल व्योम __init jmr3927_pci_setup(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	पूर्णांक extarb = !(tx3927_ccfgptr->ccfg & TX3927_CCFG_PCIXARB);
	काष्ठा pci_controller *c;

	c = txx9_alloc_pci_controller(&txx9_primary_pcic,
				      JMR3927_PCIMEM, JMR3927_PCIMEM_SIZE,
				      JMR3927_PCIIO, JMR3927_PCIIO_SIZE);
	रेजिस्टर_pci_controller(c);
	अगर (!extarb) अणु
		/* Reset PCI Bus */
		jmr3927_ioc_reg_out(0, JMR3927_IOC_RESET_ADDR);
		udelay(100);
		jmr3927_ioc_reg_out(JMR3927_IOC_RESET_PCI,
				    JMR3927_IOC_RESET_ADDR);
		udelay(100);
		jmr3927_ioc_reg_out(0, JMR3927_IOC_RESET_ADDR);
	पूर्ण
	tx3927_pcic_setup(c, JMR3927_SDRAM_SIZE, extarb);
	tx3927_setup_pcierr_irq();
#पूर्ण_अगर /* CONFIG_PCI */
पूर्ण

अटल व्योम __init jmr3927_board_init(व्योम)
अणु
	txx9_cpu_घड़ी = JMR3927_CORECLK;
	/* SDRAMC are configured by PROM */

	/* ROMC */
	tx3927_romcptr->cr[1] = JMR3927_ROMCE1 | 0x00030048;
	tx3927_romcptr->cr[2] = JMR3927_ROMCE2 | 0x000064c8;
	tx3927_romcptr->cr[3] = JMR3927_ROMCE3 | 0x0003f698;
	tx3927_romcptr->cr[5] = JMR3927_ROMCE5 | 0x0000f218;

	/* Pin selection */
	tx3927_ccfgptr->pcfg &= ~TX3927_PCFG_SELALL;
	tx3927_ccfgptr->pcfg |=
		TX3927_PCFG_SELSIOC(0) | TX3927_PCFG_SELSIO_ALL |
		(TX3927_PCFG_SELDMA_ALL & ~TX3927_PCFG_SELDMA(1));

	tx3927_setup();

	/* PIO[15:12] connected to LEDs */
	__raw_ग_लिखोl(0x0000f000, &tx3927_pioptr->dir);

	jmr3927_pci_setup();

	/* SIO0 DTR on */
	jmr3927_ioc_reg_out(0, JMR3927_IOC_DTR_ADDR);

	jmr3927_led_set(0);

	pr_info("JMR-TX3927 (Rev %d) --- IOC(Rev %d) DIPSW:%d,%d,%d,%d\n",
		jmr3927_ioc_reg_in(JMR3927_IOC_BREV_ADDR) & JMR3927_REV_MASK,
		jmr3927_ioc_reg_in(JMR3927_IOC_REV_ADDR) & JMR3927_REV_MASK,
		jmr3927_dipsw1(), jmr3927_dipsw2(),
		jmr3927_dipsw3(), jmr3927_dipsw4());
पूर्ण

/* This trick makes rtc-ds1742 driver usable as is. */
अटल अचिन्हित दीर्घ jmr3927_swizzle_addr_b(अचिन्हित दीर्घ port)
अणु
	अगर ((port & 0xffff0000) != JMR3927_IOC_NVRAMB_ADDR)
		वापस port;
	port = (port & 0xffff0000) | (port & 0x7fff << 1);
#अगर_घोषित __BIG_ENDIAN
	वापस port;
#अन्यथा
	वापस port | 1;
#पूर्ण_अगर
पूर्ण

अटल व्योम __init jmr3927_rtc_init(व्योम)
अणु
	अटल काष्ठा resource __initdata res = अणु
		.start	= JMR3927_IOC_NVRAMB_ADDR - IO_BASE,
		.end	= JMR3927_IOC_NVRAMB_ADDR - IO_BASE + 0x800 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण;
	platक्रमm_device_रेजिस्टर_simple("rtc-ds1742", -1, &res, 1);
पूर्ण

अटल व्योम __init jmr3927_mtd_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		tx3927_mtd_init(i);
पूर्ण

अटल व्योम __init jmr3927_device_init(व्योम)
अणु
	अचिन्हित दीर्घ iocled_base = JMR3927_IOC_LED_ADDR - IO_BASE;
#अगर_घोषित __LITTLE_ENDIAN
	iocled_base |= 1;
#पूर्ण_अगर
	__swizzle_addr_b = jmr3927_swizzle_addr_b;
	jmr3927_rtc_init();
	tx3927_wdt_init();
	jmr3927_mtd_init();
	txx9_iocled_init(iocled_base, -1, 8, 1, "green", शून्य);
पूर्ण

अटल व्योम __init jmr3927_arch_init(व्योम)
अणु
	txx9_gpio_init(TX3927_PIO_REG, 0, 16);

	gpio_request(11, "dipsw1");
	gpio_request(10, "dipsw2");
पूर्ण

काष्ठा txx9_board_vec jmr3927_vec __initdata = अणु
	.प्रणाली = "Toshiba JMR_TX3927",
	.prom_init = jmr3927_prom_init,
	.mem_setup = jmr3927_mem_setup,
	.irq_setup = jmr3927_irq_setup,
	.समय_init = jmr3927_समय_init,
	.device_init = jmr3927_device_init,
	.arch_init = jmr3927_arch_init,
#अगर_घोषित CONFIG_PCI
	.pci_map_irq = jmr3927_pci_map_irq,
#पूर्ण_अगर
पूर्ण;
