<शैली गुरु>
/*
 * Copyright 2011, Netlogic Microप्रणालीs.
 * Copyright 2004, Matt Porter <mporter@kernel.crashing.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/resource.h>
#समावेश <linux/spi/flash.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/platnand.h>

#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/xlr/iomap.h>
#समावेश <यंत्र/netlogic/xlr/flash.h>
#समावेश <यंत्र/netlogic/xlr/bridge.h>
#समावेश <यंत्र/netlogic/xlr/gpपन.स>
#समावेश <यंत्र/netlogic/xlr/xlr.h>

/*
 * Default NOR partition layout
 */
अटल काष्ठा mtd_partition xlr_nor_parts[] = अणु
	अणु
		.name = "User FS",
		.offset = 0x800000,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

/*
 * Default न_अंकD partition layout
 */
अटल काष्ठा mtd_partition xlr_nand_parts[] = अणु
	अणु
		.name	= "Root Filesystem",
		.offset = 64 * 64 * 2048,
		.size	= 432 * 64 * 2048,
	पूर्ण,
	अणु
		.name	= "Home Filesystem",
		.offset = MTDPART_OFS_APPEND,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

/* Use PHYSMAP flash क्रम NOR */
काष्ठा physmap_flash_data xlr_nor_data = अणु
	.width		= 2,
	.parts		= xlr_nor_parts,
	.nr_parts	= ARRAY_SIZE(xlr_nor_parts),
पूर्ण;

अटल काष्ठा resource xlr_nor_res[] = अणु
	अणु
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device xlr_nor_dev = अणु
	.name	= "physmap-flash",
	.dev	= अणु
		.platक्रमm_data	= &xlr_nor_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(xlr_nor_res),
	.resource	= xlr_nor_res,
पूर्ण;

/*
 * Use "gen_nand" driver क्रम न_अंकD flash
 *
 * There seems to be no way to store a निजी poपूर्णांकer containing
 * platक्रमm specअगरic info in gen_nand drivier. We will use a global
 * काष्ठा क्रम now, since we currently have only one न_अंकD chip per board.
 */
काष्ठा xlr_nand_flash_priv अणु
	पूर्णांक cs;
	uपूर्णांक64_t flash_mmio;
पूर्ण;

अटल काष्ठा xlr_nand_flash_priv nand_priv;

अटल व्योम xlr_nand_ctrl(काष्ठा nand_chip *chip, पूर्णांक cmd,
			  अचिन्हित पूर्णांक ctrl)
अणु
	अगर (ctrl & न_अंकD_CLE)
		nlm_ग_लिखो_reg(nand_priv.flash_mmio,
			FLASH_न_अंकD_CLE(nand_priv.cs), cmd);
	अन्यथा अगर (ctrl & न_अंकD_ALE)
		nlm_ग_लिखो_reg(nand_priv.flash_mmio,
			FLASH_न_अंकD_ALE(nand_priv.cs), cmd);
पूर्ण

काष्ठा platक्रमm_nand_data xlr_nand_data = अणु
	.chip = अणु
		.nr_chips	= 1,
		.nr_partitions	= ARRAY_SIZE(xlr_nand_parts),
		.chip_delay	= 50,
		.partitions	= xlr_nand_parts,
	पूर्ण,
	.ctrl = अणु
		.cmd_ctrl	= xlr_nand_ctrl,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource xlr_nand_res[] = अणु
	अणु
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device xlr_nand_dev = अणु
	.name		= "gen_nand",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(xlr_nand_res),
	.resource	= xlr_nand_res,
	.dev		= अणु
		.platक्रमm_data	= &xlr_nand_data,
	पूर्ण
पूर्ण;

/*
 * XLR/XLS supports upto 8 devices on its FLASH पूर्णांकerface. The value in
 * FLASH_BAR (on the MEM/IO bridge) gives the base क्रम mapping all the
 * flash devices.
 * Under this, each flash device has an offset and size given by the
 * CSBASE_ADDR and CSBASE_MASK रेजिस्टरs क्रम the device.
 *
 * The CSBASE_ रेजिस्टरs are expected to be setup by the bootloader.
 */
अटल व्योम setup_flash_resource(uपूर्णांक64_t flash_mmio,
	uपूर्णांक64_t flash_map_base, पूर्णांक cs, काष्ठा resource *res)
अणु
	u32 base, mask;

	base = nlm_पढ़ो_reg(flash_mmio, FLASH_CSBASE_ADDR(cs));
	mask = nlm_पढ़ो_reg(flash_mmio, FLASH_CSADDR_MASK(cs));

	res->start = flash_map_base + ((अचिन्हित दीर्घ)base << 16);
	res->end = res->start + (mask + 1) * 64 * 1024;
पूर्ण

अटल पूर्णांक __init xlr_flash_init(व्योम)
अणु
	uपूर्णांक64_t gpio_mmio, flash_mmio, flash_map_base;
	u32 gpio_resetcfg, flash_bar;
	पूर्णांक cs, boot_nand, boot_nor;

	/* Flash address bits 39:24 is in bridge flash BAR */
	flash_bar = nlm_पढ़ो_reg(nlm_io_base, BRIDGE_FLASH_BAR);
	flash_map_base = (flash_bar & 0xffff0000) << 8;

	gpio_mmio = nlm_mmio_base(NETLOGIC_IO_GPIO_OFFSET);
	flash_mmio = nlm_mmio_base(NETLOGIC_IO_FLASH_OFFSET);

	/* Get the chip reset config */
	gpio_resetcfg = nlm_पढ़ो_reg(gpio_mmio, GPIO_PWRON_RESET_CFG_REG);

	/* Check क्रम boot flash type */
	boot_nor = boot_nand = 0;
	अगर (nlm_chip_is_xls()) अणु
		/* On XLS, check boot from न_अंकD bit (GPIO reset reg bit 16) */
		अगर (gpio_resetcfg & (1 << 16))
			boot_nand = 1;

		/* check boot from PCMCIA, (GPIO reset reg bit 15 */
		अगर ((gpio_resetcfg & (1 << 15)) == 0)
			boot_nor = 1;	/* not set, booted from NOR */
	पूर्ण अन्यथा अणु /* XLR */
		/* check boot from PCMCIA (bit 16 in GPIO reset on XLR) */
		अगर ((gpio_resetcfg & (1 << 16)) == 0)
			boot_nor = 1;	/* not set, booted from NOR */
	पूर्ण

	/* boot flash at chip select 0 */
	cs = 0;

	अगर (boot_nand) अणु
		nand_priv.cs = cs;
		nand_priv.flash_mmio = flash_mmio;
		setup_flash_resource(flash_mmio, flash_map_base, cs,
			 xlr_nand_res);

		/* Initialize न_अंकD flash at CS 0 */
		nlm_ग_लिखो_reg(flash_mmio, FLASH_CSDEV_PARM(cs),
				FLASH_न_अंकD_CSDEV_PARAM);
		nlm_ग_लिखो_reg(flash_mmio, FLASH_CSTIME_PARMA(cs),
				FLASH_न_अंकD_CSTIME_PARAMA);
		nlm_ग_लिखो_reg(flash_mmio, FLASH_CSTIME_PARMB(cs),
				FLASH_न_अंकD_CSTIME_PARAMB);

		pr_info("ChipSelect %d: NAND Flash %pR\n", cs, xlr_nand_res);
		वापस platक्रमm_device_रेजिस्टर(&xlr_nand_dev);
	पूर्ण

	अगर (boot_nor) अणु
		setup_flash_resource(flash_mmio, flash_map_base, cs,
			xlr_nor_res);
		pr_info("ChipSelect %d: NOR Flash %pR\n", cs, xlr_nor_res);
		वापस platक्रमm_device_रेजिस्टर(&xlr_nor_dev);
	पूर्ण
	वापस 0;
पूर्ण

arch_initcall(xlr_flash_init);
