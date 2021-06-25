<शैली गुरु>
/*
 * Setup poपूर्णांकers to hardware-dependent routines.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 1997, 1998, 2001, 07, 08 by Ralf Baechle
 * Copyright (C) 2001 MIPS Technologies, Inc.
 * Copyright (C) 2007 by Thomas Bogenकरोerfer
 */
#समावेश <linux/eisa.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/console.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/jazz.h>
#समावेश <यंत्र/jazzdma.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/tlbmisc.h>

बाह्य यंत्रlinkage व्योम jazz_handle_पूर्णांक(व्योम);

बाह्य व्योम jazz_machine_restart(अक्षर *command);

अटल काष्ठा resource jazz_io_resources[] = अणु
	अणु
		.start	= 0x00,
		.end	= 0x1f,
		.name	= "dma1",
		.flags	= IORESOURCE_IO | IORESOURCE_BUSY
	पूर्ण, अणु
		.start	= 0x40,
		.end	= 0x5f,
		.name	= "timer",
		.flags	= IORESOURCE_IO | IORESOURCE_BUSY
	पूर्ण, अणु
		.start	= 0x80,
		.end	= 0x8f,
		.name	= "dma page reg",
		.flags	= IORESOURCE_IO | IORESOURCE_BUSY
	पूर्ण, अणु
		.start	= 0xc0,
		.end	= 0xdf,
		.name	= "dma2",
		.flags	= IORESOURCE_IO | IORESOURCE_BUSY
	पूर्ण
पूर्ण;

व्योम __init plat_mem_setup(व्योम)
अणु
	पूर्णांक i;

	/* Map 0xe0000000 -> 0x0:800005C0, 0xe0010000 -> 0x1:30000580 */
	add_wired_entry(0x02000017, 0x03c00017, 0xe0000000, PM_64K);
	/* Map 0xe2000000 -> 0x0:900005C0, 0xe3010000 -> 0x0:910005C0 */
	add_wired_entry(0x02400017, 0x02440017, 0xe2000000, PM_16M);
	/* Map 0xe4000000 -> 0x0:600005C0, 0xe4100000 -> 400005C0 */
	add_wired_entry(0x01800017, 0x01000017, 0xe4000000, PM_4M);

	set_io_port_base(JAZZ_PORT_BASE);
#अगर_घोषित CONFIG_EISA
	EISA_bus = 1;
#पूर्ण_अगर

	/* request I/O space क्रम devices used on all i[345]86 PCs */
	क्रम (i = 0; i < ARRAY_SIZE(jazz_io_resources); i++)
		request_resource(&ioport_resource, jazz_io_resources + i);

	/* The RTC is outside the port address space */

	_machine_restart = jazz_machine_restart;

#अगर_घोषित CONFIG_VT
	screen_info = (काष्ठा screen_info) अणु
		.orig_video_cols	= 160,
		.orig_video_lines	= 64,
		.orig_video_poपूर्णांकs	= 16,
	पूर्ण;
#पूर्ण_अगर

	add_preferred_console("ttyS", 0, "9600");
पूर्ण

#अगर_घोषित CONFIG_OLIVETTI_M700
#घोषणा UART_CLK  1843200
#अन्यथा
/* Some Jazz machines seem to have an 8MHz crystal घड़ी but I करोn't know
   exactly which ones ... XXX */
#घोषणा UART_CLK (8000000 / 16) /* ( 3072000 / 16) */
#पूर्ण_अगर

#घोषणा MEMPORT(_base, _irq)				\
	अणु						\
		.mapbase	= (_base),		\
		.membase	= (व्योम *)(_base),	\
		.irq		= (_irq),		\
		.uartclk	= UART_CLK,		\
		.iotype		= UPIO_MEM,		\
		.flags		= UPF_BOOT_AUTOCONF,	\
	पूर्ण

अटल काष्ठा plat_serial8250_port jazz_serial_data[] = अणु
	MEMPORT(JAZZ_SERIAL1_BASE, JAZZ_SERIAL1_IRQ),
	MEMPORT(JAZZ_SERIAL2_BASE, JAZZ_SERIAL2_IRQ),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device jazz_serial8250_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= jazz_serial_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource jazz_esp_rsrc[] = अणु
	अणु
		.start = JAZZ_SCSI_BASE,
		.end   = JAZZ_SCSI_BASE + 31,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.start = JAZZ_SCSI_DMA,
		.end   = JAZZ_SCSI_DMA,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.start = JAZZ_SCSI_IRQ,
		.end   = JAZZ_SCSI_IRQ,
		.flags = IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल u64 jazz_esp_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device jazz_esp_pdev = अणु
	.name		= "jazz_esp",
	.num_resources	= ARRAY_SIZE(jazz_esp_rsrc),
	.resource	= jazz_esp_rsrc,
	.dev = अणु
		.dma_mask	   = &jazz_esp_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण
पूर्ण;

अटल काष्ठा resource jazz_sonic_rsrc[] = अणु
	अणु
		.start = JAZZ_ETHERNET_BASE,
		.end   = JAZZ_ETHERNET_BASE + 0xff,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.start = JAZZ_ETHERNET_IRQ,
		.end   = JAZZ_ETHERNET_IRQ,
		.flags = IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल u64 jazz_sonic_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device jazz_sonic_pdev = अणु
	.name		= "jazzsonic",
	.num_resources	= ARRAY_SIZE(jazz_sonic_rsrc),
	.resource	= jazz_sonic_rsrc,
	.dev = अणु
		.dma_mask	   = &jazz_sonic_dma_mask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण
पूर्ण;

अटल काष्ठा resource jazz_cmos_rsrc[] = अणु
	अणु
		.start = 0x70,
		.end   = 0x71,
		.flags = IORESOURCE_IO
	पूर्ण,
	अणु
		.start = 8,
		.end   = 8,
		.flags = IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device jazz_cmos_pdev = अणु
	.name		= "rtc_cmos",
	.num_resources	= ARRAY_SIZE(jazz_cmos_rsrc),
	.resource	= jazz_cmos_rsrc
पूर्ण;

अटल काष्ठा platक्रमm_device pcspeaker_pdev = अणु
	.name		= "pcspkr",
	.id		= -1,
पूर्ण;

अटल पूर्णांक __init jazz_setup_devinit(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&jazz_serial8250_device);
	platक्रमm_device_रेजिस्टर(&jazz_esp_pdev);
	platक्रमm_device_रेजिस्टर(&jazz_sonic_pdev);
	platक्रमm_device_रेजिस्टर(&jazz_cmos_pdev);
	platक्रमm_device_रेजिस्टर(&pcspeaker_pdev);

	वापस 0;
पूर्ण

device_initcall(jazz_setup_devinit);
