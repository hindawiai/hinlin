<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 * Copyright (C) 2008 Florian Fainelli <florian@खोलोwrt.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ssb/ssb.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <bcm63xx_board.h>
#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_dev_uart.h>
#समावेश <bcm63xx_regs.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_nvram.h>
#समावेश <bcm63xx_dev_pci.h>
#समावेश <bcm63xx_dev_enet.h>
#समावेश <bcm63xx_dev_flash.h>
#समावेश <bcm63xx_dev_hsspi.h>
#समावेश <bcm63xx_dev_pcmcia.h>
#समावेश <bcm63xx_dev_spi.h>
#समावेश <bcm63xx_dev_usb_usbd.h>
#समावेश <board_bcm963xx.h>

#समावेश <uapi/linux/bcm933xx_hcs.h>

#घोषणा HCS_OFFSET_128K			0x20000

अटल काष्ठा board_info board;

/*
 * known 3368 boards
 */
#अगर_घोषित CONFIG_BCM63XX_CPU_3368
अटल काष्ठा board_info __initdata board_cvg834g = अणु
	.name = "CVG834G_E15R3921",
	.expected_cpu_id = 0x3368,

	.ephy_reset_gpio = 36,
	.ephy_reset_gpio_flags = GPIOF_INIT_HIGH,
	.has_pci = 1,
	.has_uart0 = 1,
	.has_uart1 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.leds = अणु
		अणु
			.name = "CVG834G:green:power",
			.gpio = 37,
			.शेष_trigger= "default-on",
		पूर्ण,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_BCM63XX_CPU_3368 */

/*
 * known 6328 boards
 */
#अगर_घोषित CONFIG_BCM63XX_CPU_6328
अटल काष्ठा board_info __initdata board_96328avng = अणु
	.name = "96328avng",
	.expected_cpu_id = 0x6328,

	.has_pci = 1,
	.has_uart0 = 1,

	.has_usbd = 0,
	.usbd = अणु
		.use_fullspeed = 0,
		.port_no = 0,
	पूर्ण,

	.leds = अणु
		अणु
			.name = "96328avng::ppp-fail",
			.gpio = 2,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "96328avng::power",
			.gpio = 4,
			.active_low = 1,
			.शेष_trigger = "default-on",
		पूर्ण,
		अणु
			.name = "96328avng::power-fail",
			.gpio = 8,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "96328avng::wps",
			.gpio = 9,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "96328avng::ppp",
			.gpio = 11,
			.active_low = 1,
		पूर्ण,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_BCM63XX_CPU_6328 */

/*
 * known 6338 boards
 */
#अगर_घोषित CONFIG_BCM63XX_CPU_6338
अटल काष्ठा board_info __initdata board_96338gw = अणु
	.name = "96338GW",
	.expected_cpu_id = 0x6338,

	.has_ohci0 = 1,
	.has_uart0 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,

	.leds = अणु
		अणु
			.name = "adsl",
			.gpio = 3,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ses",
			.gpio = 5,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp-fail",
			.gpio = 4,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "power",
			.gpio = 0,
			.active_low = 1,
			.शेष_trigger = "default-on",
		पूर्ण,
		अणु
			.name = "stop",
			.gpio = 1,
			.active_low = 1,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा board_info __initdata board_96338w = अणु
	.name = "96338W",
	.expected_cpu_id = 0x6338,

	.has_uart0 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,

	.leds = अणु
		अणु
			.name = "adsl",
			.gpio = 3,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ses",
			.gpio = 5,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp-fail",
			.gpio = 4,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "power",
			.gpio = 0,
			.active_low = 1,
			.शेष_trigger = "default-on",
		पूर्ण,
		अणु
			.name = "stop",
			.gpio = 1,
			.active_low = 1,
		पूर्ण,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_BCM63XX_CPU_6338 */

/*
 * known 6345 boards
 */
#अगर_घोषित CONFIG_BCM63XX_CPU_6345
अटल काष्ठा board_info __initdata board_96345gw2 = अणु
	.name = "96345GW2",
	.expected_cpu_id = 0x6345,

	.has_uart0 = 1,
पूर्ण;
#पूर्ण_अगर /* CONFIG_BCM63XX_CPU_6345 */

/*
 * known 6348 boards
 */
#अगर_घोषित CONFIG_BCM63XX_CPU_6348
अटल काष्ठा board_info __initdata board_96348r = अणु
	.name = "96348R",
	.expected_cpu_id = 0x6348,

	.has_pci = 1,
	.has_uart0 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.leds = अणु
		अणु
			.name = "adsl-fail",
			.gpio = 2,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp",
			.gpio = 3,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp-fail",
			.gpio = 4,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "power",
			.gpio = 0,
			.active_low = 1,
			.शेष_trigger = "default-on",

		पूर्ण,
		अणु
			.name = "stop",
			.gpio = 1,
			.active_low = 1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा board_info __initdata board_96348gw_10 = अणु
	.name = "96348GW-10",
	.expected_cpu_id = 0x6348,

	.has_ohci0 = 1,
	.has_pccard = 1,
	.has_pci = 1,
	.has_uart0 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.has_enet1 = 1,
	.enet1 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,

	.leds = अणु
		अणु
			.name = "adsl-fail",
			.gpio = 2,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp",
			.gpio = 3,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp-fail",
			.gpio = 4,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "power",
			.gpio = 0,
			.active_low = 1,
			.शेष_trigger = "default-on",
		पूर्ण,
		अणु
			.name = "stop",
			.gpio = 1,
			.active_low = 1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा board_info __initdata board_96348gw_11 = अणु
	.name = "96348GW-11",
	.expected_cpu_id = 0x6348,

	.has_ohci0 = 1,
	.has_pccard = 1,
	.has_pci = 1,
	.has_uart0 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.has_enet1 = 1,
	.enet1 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,

	.leds = अणु
		अणु
			.name = "adsl-fail",
			.gpio = 2,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp",
			.gpio = 3,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp-fail",
			.gpio = 4,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "power",
			.gpio = 0,
			.active_low = 1,
			.शेष_trigger = "default-on",
		पूर्ण,
		अणु
			.name = "stop",
			.gpio = 1,
			.active_low = 1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा board_info __initdata board_96348gw = अणु
	.name = "96348GW",
	.expected_cpu_id = 0x6348,

	.has_ohci0 = 1,
	.has_pci = 1,
	.has_uart0 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.has_enet1 = 1,
	.enet1 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,

	.leds = अणु
		अणु
			.name = "adsl-fail",
			.gpio = 2,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp",
			.gpio = 3,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp-fail",
			.gpio = 4,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "power",
			.gpio = 0,
			.active_low = 1,
			.शेष_trigger = "default-on",
		पूर्ण,
		अणु
			.name = "stop",
			.gpio = 1,
			.active_low = 1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा board_info __initdata board_FAST2404 = अणु
	.name = "F@ST2404",
	.expected_cpu_id = 0x6348,

	.has_ohci0 = 1,
	.has_pccard = 1,
	.has_pci = 1,
	.has_uart0 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.has_enet1 = 1,
	.enet1 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा board_info __initdata board_rta1025w_16 = अणु
	.name = "RTA1025W_16",
	.expected_cpu_id = 0x6348,

	.has_pci = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.has_enet1 = 1,
	.enet1 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा board_info __initdata board_DV201AMR = अणु
	.name = "DV201AMR",
	.expected_cpu_id = 0x6348,

	.has_ohci0 = 1,
	.has_pci = 1,
	.has_uart0 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.has_enet1 = 1,
	.enet1 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा board_info __initdata board_96348gw_a = अणु
	.name = "96348GW-A",
	.expected_cpu_id = 0x6348,

	.has_ohci0 = 1,
	.has_pci = 1,
	.has_uart0 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.has_enet1 = 1,
	.enet1 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_BCM63XX_CPU_6348 */

/*
 * known 6358 boards
 */
#अगर_घोषित CONFIG_BCM63XX_CPU_6358
अटल काष्ठा board_info __initdata board_96358vw = अणु
	.name = "96358VW",
	.expected_cpu_id = 0x6358,

	.has_ehci0 = 1,
	.has_ohci0 = 1,
	.has_pccard = 1,
	.has_pci = 1,
	.has_uart0 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.has_enet1 = 1,
	.enet1 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,

	.leds = अणु
		अणु
			.name = "adsl-fail",
			.gpio = 15,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp",
			.gpio = 22,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp-fail",
			.gpio = 23,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "power",
			.gpio = 4,
			.शेष_trigger = "default-on",
		पूर्ण,
		अणु
			.name = "stop",
			.gpio = 5,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा board_info __initdata board_96358vw2 = अणु
	.name = "96358VW2",
	.expected_cpu_id = 0x6358,

	.has_ehci0 = 1,
	.has_ohci0 = 1,
	.has_pccard = 1,
	.has_pci = 1,
	.has_uart0 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.has_enet1 = 1,
	.enet1 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,

	.leds = अणु
		अणु
			.name = "adsl",
			.gpio = 22,
			.active_low = 1,
		पूर्ण,
		अणु
			.name = "ppp-fail",
			.gpio = 23,
		पूर्ण,
		अणु
			.name = "power",
			.gpio = 5,
			.active_low = 1,
			.शेष_trigger = "default-on",
		पूर्ण,
		अणु
			.name = "stop",
			.gpio = 4,
			.active_low = 1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा board_info __initdata board_AGPFS0 = अणु
	.name = "AGPF-S0",
	.expected_cpu_id = 0x6358,

	.has_ehci0 = 1,
	.has_ohci0 = 1,
	.has_pci = 1,
	.has_uart0 = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.has_enet1 = 1,
	.enet1 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा board_info __initdata board_DWVS0 = अणु
	.name = "DWV-S0",
	.expected_cpu_id = 0x6358,

	.has_ehci0 = 1,
	.has_ohci0 = 1,
	.has_pci = 1,

	.has_enet0 = 1,
	.enet0 = अणु
		.has_phy = 1,
		.use_पूर्णांकernal_phy = 1,
	पूर्ण,

	.has_enet1 = 1,
	.enet1 = अणु
		.क्रमce_speed_100 = 1,
		.क्रमce_duplex_full = 1,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_BCM63XX_CPU_6358 */

/*
 * all boards
 */
अटल स्थिर काष्ठा board_info __initस्थिर *bcm963xx_boards[] = अणु
#अगर_घोषित CONFIG_BCM63XX_CPU_3368
	&board_cvg834g,
#पूर्ण_अगर /* CONFIG_BCM63XX_CPU_3368 */
#अगर_घोषित CONFIG_BCM63XX_CPU_6328
	&board_96328avng,
#पूर्ण_अगर /* CONFIG_BCM63XX_CPU_6328 */
#अगर_घोषित CONFIG_BCM63XX_CPU_6338
	&board_96338gw,
	&board_96338w,
#पूर्ण_अगर /* CONFIG_BCM63XX_CPU_6338 */
#अगर_घोषित CONFIG_BCM63XX_CPU_6345
	&board_96345gw2,
#पूर्ण_अगर /* CONFIG_BCM63XX_CPU_6345 */
#अगर_घोषित CONFIG_BCM63XX_CPU_6348
	&board_96348r,
	&board_96348gw,
	&board_96348gw_10,
	&board_96348gw_11,
	&board_FAST2404,
	&board_DV201AMR,
	&board_96348gw_a,
	&board_rta1025w_16,
#पूर्ण_अगर /* CONFIG_BCM63XX_CPU_6348 */
#अगर_घोषित CONFIG_BCM63XX_CPU_6358
	&board_96358vw,
	&board_96358vw2,
	&board_AGPFS0,
	&board_DWVS0,
#पूर्ण_अगर /* CONFIG_BCM63XX_CPU_6358 */
पूर्ण;

/*
 * Register a sane SPROMv2 to make the on-board
 * bcm4318 WLAN work
 */
#अगर_घोषित CONFIG_SSB_PCIHOST
अटल काष्ठा ssb_sprom bcm63xx_sprom = अणु
	.revision		= 0x02,
	.board_rev		= 0x17,
	.country_code		= 0x0,
	.ant_available_bg	= 0x3,
	.pa0b0			= 0x15ae,
	.pa0b1			= 0xfa85,
	.pa0b2			= 0xfe8d,
	.pa1b0			= 0xffff,
	.pa1b1			= 0xffff,
	.pa1b2			= 0xffff,
	.gpio0			= 0xff,
	.gpio1			= 0xff,
	.gpio2			= 0xff,
	.gpio3			= 0xff,
	.maxpwr_bg		= 0x004c,
	.itssi_bg		= 0x00,
	.boardflags_lo		= 0x2848,
	.boardflags_hi		= 0x0000,
पूर्ण;

पूर्णांक bcm63xx_get_fallback_sprom(काष्ठा ssb_bus *bus, काष्ठा ssb_sprom *out)
अणु
	अगर (bus->bustype == SSB_BUSTYPE_PCI) अणु
		स_नकल(out, &bcm63xx_sprom, माप(काष्ठा ssb_sprom));
		वापस 0;
	पूर्ण अन्यथा अणु
		pr_err("unable to fill SPROM for given bustype\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_PCIHOST */

/*
 * वापस board name क्रम /proc/cpuinfo
 */
स्थिर अक्षर *board_get_name(व्योम)
अणु
	वापस board.name;
पूर्ण

/*
 * early init callback, पढ़ो nvram data from flash and checksum it
 */
व्योम __init board_prom_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	u8 *boot_addr, *cfe;
	अक्षर cfe_version[32];
	अक्षर *board_name = शून्य;
	u32 val;
	काष्ठा bcm_hcs *hcs;

	/* पढ़ो base address of boot chip select (0)
	 * 6328/6362 करो not have MPI but boot from a fixed address
	 */
	अगर (BCMCPU_IS_6328() || BCMCPU_IS_6362()) अणु
		val = 0x18000000;
	पूर्ण अन्यथा अणु
		val = bcm_mpi_पढ़ोl(MPI_CSBASE_REG(0));
		val &= MPI_CSBASE_BASE_MASK;
	पूर्ण
	boot_addr = (u8 *)KSEG1ADDR(val);

	/* dump cfe version */
	cfe = boot_addr + BCM963XX_CFE_VERSION_OFFSET;
	अगर (strstarts(cfe, "cfe-")) अणु
		अगर(cfe[4] == 'v') अणु
			अगर(cfe[5] == 'd')
				snम_लिखो(cfe_version, 11, "%s",
					 (अक्षर *) &cfe[5]);
			अन्यथा अगर (cfe[10] > 0)
				snम_लिखो(cfe_version, माप(cfe_version),
					 "%u.%u.%u-%u.%u-%u", cfe[5], cfe[6],
					 cfe[7], cfe[8], cfe[9], cfe[10]);
			अन्यथा
				snम_लिखो(cfe_version, माप(cfe_version),
					 "%u.%u.%u-%u.%u", cfe[5], cfe[6],
					 cfe[7], cfe[8], cfe[9]);
		पूर्ण अन्यथा अणु
			snम_लिखो(cfe_version, 12, "%s", (अक्षर *) &cfe[4]);
		पूर्ण
	पूर्ण अन्यथा अणु
		म_नकल(cfe_version, "unknown");
	पूर्ण
	pr_info("CFE version: %s\n", cfe_version);

	bcm63xx_nvram_init(boot_addr + BCM963XX_NVRAM_OFFSET);

	अगर (BCMCPU_IS_3368()) अणु
		hcs = (काष्ठा bcm_hcs *)boot_addr;
		board_name = hcs->filename;
	पूर्ण अन्यथा अणु
		board_name = bcm63xx_nvram_get_name();
	पूर्ण
	/* find board by name */
	क्रम (i = 0; i < ARRAY_SIZE(bcm963xx_boards); i++) अणु
		अगर (म_भेदन(board_name, bcm963xx_boards[i]->name, 16))
			जारी;
		/* copy, board desc array is marked initdata */
		स_नकल(&board, bcm963xx_boards[i], माप(board));
		अवरोध;
	पूर्ण

	/* bail out अगर board is not found, will complain later */
	अगर (!board.name[0]) अणु
		अक्षर name[17];
		स_नकल(name, board_name, 16);
		name[16] = 0;
		pr_err("unknown bcm963xx board: %s\n", name);
		वापस;
	पूर्ण

	/* setup pin multiplexing depending on board enabled device,
	 * this has to be करोne this early since PCI init is करोne
	 * inside arch_initcall */
	val = 0;

#अगर_घोषित CONFIG_PCI
	अगर (board.has_pci) अणु
		bcm63xx_pci_enabled = 1;
		अगर (BCMCPU_IS_6348())
			val |= GPIO_MODE_6348_G2_PCI;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

	अगर (board.has_pccard) अणु
		अगर (BCMCPU_IS_6348())
			val |= GPIO_MODE_6348_G1_MII_PCCARD;
	पूर्ण

	अगर (board.has_enet0 && !board.enet0.use_पूर्णांकernal_phy) अणु
		अगर (BCMCPU_IS_6348())
			val |= GPIO_MODE_6348_G3_EXT_MII |
				GPIO_MODE_6348_G0_EXT_MII;
	पूर्ण

	अगर (board.has_enet1 && !board.enet1.use_पूर्णांकernal_phy) अणु
		अगर (BCMCPU_IS_6348())
			val |= GPIO_MODE_6348_G3_EXT_MII |
				GPIO_MODE_6348_G0_EXT_MII;
	पूर्ण

	bcm_gpio_ग_लिखोl(val, GPIO_MODE_REG);
पूर्ण

/*
 * second stage init callback, good समय to panic अगर we couldn't
 * identअगरy on which board we're running since early prपूर्णांकk is working
 */
व्योम __init board_setup(व्योम)
अणु
	अगर (!board.name[0])
		panic("unable to detect bcm963xx board");
	pr_info("board name: %s\n", board.name);

	/* make sure we're running on expected cpu */
	अगर (bcm63xx_get_cpu_id() != board.expected_cpu_id)
		panic("unexpected CPU for bcm963xx board");
पूर्ण

अटल काष्ठा gpio_led_platक्रमm_data bcm63xx_led_data;

अटल काष्ठा platक्रमm_device bcm63xx_gpio_leds = अणु
	.name			= "leds-gpio",
	.id			= 0,
	.dev.platक्रमm_data	= &bcm63xx_led_data,
पूर्ण;

/*
 * third stage init callback, रेजिस्टर all board devices.
 */
पूर्णांक __init board_रेजिस्टर_devices(व्योम)
अणु
	अगर (board.has_uart0)
		bcm63xx_uart_रेजिस्टर(0);

	अगर (board.has_uart1)
		bcm63xx_uart_रेजिस्टर(1);

	अगर (board.has_pccard)
		bcm63xx_pcmcia_रेजिस्टर();

	अगर (board.has_enet0 &&
	    !bcm63xx_nvram_get_mac_address(board.enet0.mac_addr))
		bcm63xx_enet_रेजिस्टर(0, &board.enet0);

	अगर (board.has_enet1 &&
	    !bcm63xx_nvram_get_mac_address(board.enet1.mac_addr))
		bcm63xx_enet_रेजिस्टर(1, &board.enet1);

	अगर (board.has_enetsw &&
	    !bcm63xx_nvram_get_mac_address(board.enetsw.mac_addr))
		bcm63xx_enetsw_रेजिस्टर(&board.enetsw);

	अगर (board.has_usbd)
		bcm63xx_usbd_रेजिस्टर(&board.usbd);

	/* Generate MAC address क्रम WLAN and रेजिस्टर our SPROM,
	 * करो this after रेजिस्टरing enet devices
	 */
#अगर_घोषित CONFIG_SSB_PCIHOST
	अगर (!bcm63xx_nvram_get_mac_address(bcm63xx_sprom.il0mac)) अणु
		स_नकल(bcm63xx_sprom.et0mac, bcm63xx_sprom.il0mac, ETH_ALEN);
		स_नकल(bcm63xx_sprom.et1mac, bcm63xx_sprom.il0mac, ETH_ALEN);
		अगर (ssb_arch_रेजिस्टर_fallback_sprom(
				&bcm63xx_get_fallback_sprom) < 0)
			pr_err("failed to register fallback SPROM\n");
	पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_PCIHOST */

	bcm63xx_spi_रेजिस्टर();

	bcm63xx_hsspi_रेजिस्टर();

	bcm63xx_flash_रेजिस्टर();

	bcm63xx_led_data.num_leds = ARRAY_SIZE(board.leds);
	bcm63xx_led_data.leds = board.leds;

	platक्रमm_device_रेजिस्टर(&bcm63xx_gpio_leds);

	अगर (board.ephy_reset_gpio && board.ephy_reset_gpio_flags)
		gpio_request_one(board.ephy_reset_gpio,
				board.ephy_reset_gpio_flags, "ephy-reset");

	वापस 0;
पूर्ण
