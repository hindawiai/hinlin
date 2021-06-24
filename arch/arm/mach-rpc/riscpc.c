<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-rpc/riscpc.c
 *
 *  Copyright (C) 1998-2001 Russell King
 *
 *  Architecture specअगरic fixups.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/hardware/iomd.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/करोमुख्य.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>

बाह्य व्योम rpc_init_irq(व्योम);

अचिन्हित पूर्णांक vram_size;
अचिन्हित पूर्णांक memc_ctrl_reg;
अचिन्हित पूर्णांक number_mfm_drives;

अटल पूर्णांक __init parse_tag_acorn(स्थिर काष्ठा tag *tag)
अणु
	memc_ctrl_reg = tag->u.acorn.memc_control_reg;
	number_mfm_drives = tag->u.acorn.adfsdrives;

	चयन (tag->u.acorn.vram_pages) अणु
	हाल 512:
		vram_size += PAGE_SIZE * 256;
		fallthrough;	/* ??? */
	हाल 256:
		vram_size += PAGE_SIZE * 256;
	शेष:
		अवरोध;
	पूर्ण
#अगर 0
	अगर (vram_size) अणु
		desc->video_start = 0x02000000;
		desc->video_end   = 0x02000000 + vram_size;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

__tagtable(ATAG_ACORN, parse_tag_acorn);

अटल काष्ठा map_desc rpc_io_desc[] __initdata = अणु
 	अणु	/* VRAM		*/
		.भव	=  SCREEN_BASE,
		.pfn		= __phys_to_pfn(SCREEN_START),
		.length		= 	2*1048576,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* IO space	*/
		.भव	=  (u32)IO_BASE,
		.pfn		= __phys_to_pfn(IO_START),
		.length		= 	IO_SIZE	 ,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* EASI space	*/
		.भव	= (अचिन्हित दीर्घ)EASI_BASE,
		.pfn		= __phys_to_pfn(EASI_START),
		.length		= EASI_SIZE,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init rpc_map_io(व्योम)
अणु
	iotable_init(rpc_io_desc, ARRAY_SIZE(rpc_io_desc));

	/*
	 * Turn off floppy.
	 */
	ग_लिखोb(0xc, PCIO_BASE + (0x3f2 << 2));

	/*
	 * RiscPC can't handle half-word loads and stores
	 */
	elf_hwcap &= ~HWCAP_HALF;
पूर्ण

अटल काष्ठा resource acornfb_resources[] = अणु
	/* VIDC */
	DEFINE_RES_MEM(0x03400000, 0x00200000),
	DEFINE_RES_IRQ(IRQ_VSYNCPULSE),
पूर्ण;

अटल काष्ठा platक्रमm_device acornfb_device = अणु
	.name			= "acornfb",
	.id			= -1,
	.dev			= अणु
		.coherent_dma_mask = 0xffffffff,
	पूर्ण,
	.num_resources		= ARRAY_SIZE(acornfb_resources),
	.resource		= acornfb_resources,
पूर्ण;

अटल काष्ठा resource iomd_resources[] = अणु
	DEFINE_RES_MEM(0x03200000, 0x10000),
पूर्ण;

अटल काष्ठा platक्रमm_device iomd_device = अणु
	.name			= "iomd",
	.id			= -1,
	.num_resources		= ARRAY_SIZE(iomd_resources),
	.resource		= iomd_resources,
पूर्ण;

अटल काष्ठा resource iomd_kart_resources[] = अणु
	DEFINE_RES_IRQ(IRQ_KEYBOARDRX),
	DEFINE_RES_IRQ(IRQ_KEYBOARDTX),
पूर्ण;

अटल काष्ठा platक्रमm_device kbd_device = अणु
	.name			= "kart",
	.id			= -1,
	.dev			= अणु
		.parent 	= &iomd_device.dev,
	पूर्ण,
	.num_resources		= ARRAY_SIZE(iomd_kart_resources),
	.resource		= iomd_kart_resources,
पूर्ण;

अटल काष्ठा plat_serial8250_port serial_platक्रमm_data[] = अणु
	अणु
		.mapbase	= 0x03010fe0,
		.irq		= IRQ_SERIALPORT,
		.uartclk	= 1843200,
		.regshअगरt	= 2,
		.iotype		= UPIO_MEM,
		.flags		= UPF_BOOT_AUTOCONF | UPF_IOREMAP | UPF_SKIP_TEST,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device serial_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= serial_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा pata_platक्रमm_info pata_platक्रमm_data = अणु
	.ioport_shअगरt		= 2,
पूर्ण;

अटल काष्ठा resource pata_resources[] = अणु
	DEFINE_RES_MEM(0x030107c0, 0x20),
	DEFINE_RES_MEM(0x03010fd8, 0x04),
	DEFINE_RES_IRQ(IRQ_HARDDISK),
पूर्ण;

अटल काष्ठा platक्रमm_device pata_device = अणु
	.name			= "pata_platform",
	.id			= -1,
	.num_resources		= ARRAY_SIZE(pata_resources),
	.resource		= pata_resources,
	.dev			= अणु
		.platक्रमm_data	= &pata_platक्रमm_data,
		.coherent_dma_mask = ~0,	/* grumble */
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *devs[] __initdata = अणु
	&iomd_device,
	&kbd_device,
	&serial_device,
	&acornfb_device,
	&pata_device,
पूर्ण;

अटल काष्ठा i2c_board_info i2c_rtc = अणु
	I2C_BOARD_INFO("pcf8583", 0x50)
पूर्ण;

अटल पूर्णांक __init rpc_init(व्योम)
अणु
	i2c_रेजिस्टर_board_info(0, &i2c_rtc, 1);
	वापस platक्रमm_add_devices(devs, ARRAY_SIZE(devs));
पूर्ण

arch_initcall(rpc_init);

अटल व्योम rpc_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	iomd_ग_लिखोb(0, IOMD_ROMCR0);

	/*
	 * Jump पूर्णांकo the ROM
	 */
	soft_restart(0);
पूर्ण

व्योम ioc_समयr_init(व्योम);

MACHINE_START(RISCPC, "Acorn-RiscPC")
	/* Maपूर्णांकainer: Russell King */
	.atag_offset	= 0x100,
	.reserve_lp0	= 1,
	.reserve_lp1	= 1,
	.map_io		= rpc_map_io,
	.init_irq	= rpc_init_irq,
	.init_समय	= ioc_समयr_init,
	.restart	= rpc_restart,
MACHINE_END
