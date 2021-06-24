<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/usb/isp116x.h>
#समावेश <linux/delay.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <यंत्र/machvec.h>
#समावेश <mach-se/mach/se7343.h>
#समावेश <यंत्र/heartbeat.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>

अटल काष्ठा resource heartbeat_resource = अणु
	.start	= PA_LED,
	.end	= PA_LED,
	.flags	= IORESOURCE_MEM | IORESOURCE_MEM_16BIT,
पूर्ण;

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name		= "heartbeat",
	.id		= -1,
	.num_resources	= 1,
	.resource	= &heartbeat_resource,
पूर्ण;

अटल काष्ठा mtd_partition nor_flash_partitions[] = अणु
	अणु
		.name		= "loader",
		.offset		= 0x00000000,
		.size		= 128 * 1024,
	पूर्ण,
	अणु
		.name		= "rootfs",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 31 * 1024 * 1024,
	पूर्ण,
	अणु
		.name		= "data",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data nor_flash_data = अणु
	.width		= 2,
	.parts		= nor_flash_partitions,
	.nr_parts	= ARRAY_SIZE(nor_flash_partitions),
पूर्ण;

अटल काष्ठा resource nor_flash_resources[] = अणु
	[0]	= अणु
		.start	= 0x00000000,
		.end	= 0x01ffffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device nor_flash_device = अणु
	.name		= "physmap-flash",
	.dev		= अणु
		.platक्रमm_data	= &nor_flash_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(nor_flash_resources),
	.resource	= nor_flash_resources,
पूर्ण;

#घोषणा ST16C2550C_FLAGS (UPF_BOOT_AUTOCONF | UPF_IOREMAP)

अटल काष्ठा plat_serial8250_port serial_platक्रमm_data[] = अणु
	[0] = अणु
		.iotype		= UPIO_MEM,
		.mapbase	= 0x16000000,
		.regshअगरt	= 1,
		.flags		= ST16C2550C_FLAGS,
		.uartclk	= 7372800,
	पूर्ण,
	[1] = अणु
		.iotype		= UPIO_MEM,
		.mapbase	= 0x17000000,
		.regshअगरt	= 1,
		.flags		= ST16C2550C_FLAGS,
		.uartclk	= 7372800,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device uart_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= serial_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल व्योम isp116x_delay(काष्ठा device *dev, पूर्णांक delay)
अणु
	ndelay(delay);
पूर्ण

अटल काष्ठा resource usb_resources[] = अणु
	[0] = अणु
		.start  = 0x11800000,
		.end    = 0x11800001,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = 0x11800002,
		.end    = 0x11800003,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		/* Filled in later */
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा isp116x_platक्रमm_data usb_platक्रमm_data = अणु
	.sel15Kres		= 1,
	.oc_enable		= 1,
	.पूर्णांक_act_high		= 0,
	.पूर्णांक_edge_triggered	= 0,
	.remote_wakeup_enable	= 0,
	.delay			= isp116x_delay,
पूर्ण;

अटल काष्ठा platक्रमm_device usb_device = अणु
	.name			= "isp116x-hcd",
	.id			= -1,
	.num_resources		= ARRAY_SIZE(usb_resources),
	.resource		= usb_resources,
	.dev			= अणु
		.platक्रमm_data	= &usb_platक्रमm_data,
	पूर्ण,

पूर्ण;

अटल काष्ठा platक्रमm_device *sh7343se_platक्रमm_devices[] __initdata = अणु
	&heartbeat_device,
	&nor_flash_device,
	&uart_device,
	&usb_device,
पूर्ण;

अटल पूर्णांक __init sh7343se_devices_setup(व्योम)
अणु
	/* Wire-up dynamic vectors */
	serial_platक्रमm_data[0].irq = irq_find_mapping(se7343_irq_करोमुख्य,
						       SE7343_FPGA_IRQ_UARTA);
	serial_platक्रमm_data[1].irq = irq_find_mapping(se7343_irq_करोमुख्य,
						       SE7343_FPGA_IRQ_UARTB);
	usb_resources[2].start = usb_resources[2].end =
		irq_find_mapping(se7343_irq_करोमुख्य, SE7343_FPGA_IRQ_USB);

	वापस platक्रमm_add_devices(sh7343se_platक्रमm_devices,
				    ARRAY_SIZE(sh7343se_platक्रमm_devices));
पूर्ण
device_initcall(sh7343se_devices_setup);

/*
 * Initialize the board
 */
अटल व्योम __init sh7343se_setup(अक्षर **cmdline_p)
अणु
	__raw_ग_लिखोw(0xf900, FPGA_OUT);	/* FPGA */

	__raw_ग_लिखोw(0x0002, PORT_PECR);	/* PORT E 1 = IRQ5 */
	__raw_ग_लिखोw(0x0020, PORT_PSELD);

	prपूर्णांकk(KERN_INFO "MS7343CP01 Setup...done\n");
पूर्ण

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_7343se __iniपंचांगv = अणु
	.mv_name = "SolutionEngine 7343",
	.mv_setup = sh7343se_setup,
	.mv_init_irq = init_7343se_IRQ,
पूर्ण;
