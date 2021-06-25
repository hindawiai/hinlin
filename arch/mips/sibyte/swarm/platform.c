<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>

#समावेश <यंत्र/sibyte/board.h>
#समावेश <यंत्र/sibyte/sb1250_genbus.h>
#समावेश <यंत्र/sibyte/sb1250_regs.h>

#अगर defined(CONFIG_SIBYTE_SWARM) || defined(CONFIG_SIBYTE_LITTLESUR)

#घोषणा DRV_NAME	"pata-swarm"

#घोषणा SWARM_IDE_SHIFT 5
#घोषणा SWARM_IDE_BASE	0x1f0
#घोषणा SWARM_IDE_CTRL	0x3f6

अटल काष्ठा resource swarm_pata_resource[] = अणु
	अणु
		.name	= "Swarm GenBus IDE",
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.name	= "Swarm GenBus IDE",
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.name	= "Swarm GenBus IDE",
		.flags	= IORESOURCE_IRQ,
		.start	= K_INT_GB_IDE,
		.end	= K_INT_GB_IDE,
	पूर्ण,
पूर्ण;

अटल काष्ठा pata_platक्रमm_info pata_platक्रमm_data = अणु
	.ioport_shअगरt	= SWARM_IDE_SHIFT,
पूर्ण;

अटल काष्ठा platक्रमm_device swarm_pata_device = अणु
	.name		= "pata_platform",
	.id		= -1,
	.resource	= swarm_pata_resource,
	.num_resources	= ARRAY_SIZE(swarm_pata_resource),
	.dev  = अणु
		.platक्रमm_data		= &pata_platक्रमm_data,
		.coherent_dma_mask	= ~0,	/* grumble */
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init swarm_pata_init(व्योम)
अणु
	u8 __iomem *base;
	phys_addr_t offset, size;
	काष्ठा resource *r;

	अगर (!SIBYTE_HAVE_IDE)
		वापस -ENODEV;

	base = ioremap(A_IO_EXT_BASE, 0x800);
	offset = __raw_पढ़ोq(base + R_IO_EXT_REG(R_IO_EXT_START_ADDR, IDE_CS));
	size = __raw_पढ़ोq(base + R_IO_EXT_REG(R_IO_EXT_MULT_SIZE, IDE_CS));
	iounmap(base);

	offset = G_IO_START_ADDR(offset) << S_IO_ADDRBASE;
	size = (G_IO_MULT_SIZE(size) + 1) << S_IO_REGSIZE;
	अगर (offset < A_PHYS_GENBUS || offset >= A_PHYS_GENBUS_END) अणु
		pr_info(DRV_NAME ": PATA interface at GenBus disabled\n");

		वापस -EBUSY;
	पूर्ण

	pr_info(DRV_NAME ": PATA interface at GenBus slot %i\n", IDE_CS);

	r = swarm_pata_resource;
	r[0].start = offset + (SWARM_IDE_BASE << SWARM_IDE_SHIFT);
	r[0].end   = offset + ((SWARM_IDE_BASE + 8) << SWARM_IDE_SHIFT) - 1;
	r[1].start = offset + (SWARM_IDE_CTRL << SWARM_IDE_SHIFT);
	r[1].end   = offset + ((SWARM_IDE_CTRL + 1) << SWARM_IDE_SHIFT) - 1;

	वापस platक्रमm_device_रेजिस्टर(&swarm_pata_device);
पूर्ण

device_initcall(swarm_pata_init);

#पूर्ण_अगर /* defined(CONFIG_SIBYTE_SWARM) || defined(CONFIG_SIBYTE_LITTLESUR) */

#घोषणा sb1250_dev_काष्ठा(num) \
	अटल काष्ठा resource sb1250_res##num = अणु		\
		.name = "SB1250 MAC " __stringअगरy(num),		\
		.flags = IORESOURCE_MEM,		\
		.start = A_MAC_CHANNEL_BASE(num),	\
		.end = A_MAC_CHANNEL_BASE(num + 1) -1,	\
	पूर्ण;\
	अटल काष्ठा platक्रमm_device sb1250_dev##num = अणु	\
		.name = "sb1250-mac",			\
	.id = num,					\
	.resource = &sb1250_res##num,			\
	.num_resources = 1,				\
	पूर्ण

sb1250_dev_काष्ठा(0);
sb1250_dev_काष्ठा(1);
sb1250_dev_काष्ठा(2);
sb1250_dev_काष्ठा(3);

अटल काष्ठा platक्रमm_device *sb1250_devs[] __initdata = अणु
	&sb1250_dev0,
	&sb1250_dev1,
	&sb1250_dev2,
	&sb1250_dev3,
पूर्ण;

अटल पूर्णांक __init sb1250_device_init(व्योम)
अणु
	पूर्णांक ret;

	/* Set the number of available units based on the SOC type.  */
	चयन (soc_type) अणु
	हाल K_SYS_SOC_TYPE_BCM1250:
	हाल K_SYS_SOC_TYPE_BCM1250_ALT:
		ret = platक्रमm_add_devices(sb1250_devs, 3);
		अवरोध;
	हाल K_SYS_SOC_TYPE_BCM1120:
	हाल K_SYS_SOC_TYPE_BCM1125:
	हाल K_SYS_SOC_TYPE_BCM1125H:
	हाल K_SYS_SOC_TYPE_BCM1250_ALT2:	/* Hybrid */
		ret = platक्रमm_add_devices(sb1250_devs, 2);
		अवरोध;
	हाल K_SYS_SOC_TYPE_BCM1x55:
	हाल K_SYS_SOC_TYPE_BCM1x80:
		ret = platक्रमm_add_devices(sb1250_devs, 4);
		अवरोध;
	शेष:
		ret = -ENODEV;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
device_initcall(sb1250_device_init);
