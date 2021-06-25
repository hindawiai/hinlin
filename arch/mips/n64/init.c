<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Nपूर्णांकenकरो 64 init.
 *
 *  Copyright (C) 2021	Lauri Kasanen
 */
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/memblock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/simplefb.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/fw/fw.h>
#समावेश <यंत्र/समय.स>

#घोषणा IO_MEM_RESOURCE_START	0UL
#घोषणा IO_MEM_RESOURCE_END	0x1fffffffUL

/*
 * System-specअगरc irq names क्रम clarity
 */
#घोषणा MIPS_CPU_IRQ(x)		(MIPS_CPU_IRQ_BASE + (x))
#घोषणा MIPS_SOFTINT0_IRQ	MIPS_CPU_IRQ(0)
#घोषणा MIPS_SOFTINT1_IRQ	MIPS_CPU_IRQ(1)
#घोषणा RCP_IRQ			MIPS_CPU_IRQ(2)
#घोषणा CART_IRQ		MIPS_CPU_IRQ(3)
#घोषणा PRENMI_IRQ		MIPS_CPU_IRQ(4)
#घोषणा RDBR_IRQ		MIPS_CPU_IRQ(5)
#घोषणा RDBW_IRQ		MIPS_CPU_IRQ(6)
#घोषणा TIMER_IRQ		MIPS_CPU_IRQ(7)

अटल व्योम __init iomem_resource_init(व्योम)
अणु
	iomem_resource.start = IO_MEM_RESOURCE_START;
	iomem_resource.end = IO_MEM_RESOURCE_END;
पूर्ण

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस "Nintendo 64";
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	fw_init_cmdline();
पूर्ण

#घोषणा W 320
#घोषणा H 240
#घोषणा REG_BASE ((u32 *) CKSEG1ADDR(0x4400000))

अटल व्योम __init n64rdp_ग_लिखो_reg(स्थिर u8 reg, स्थिर u32 value)
अणु
	__raw_ग_लिखोl(value, REG_BASE + reg);
पूर्ण

#अघोषित REG_BASE

अटल स्थिर u32 ntsc_320[] __initस्थिर = अणु
	0x00013212, 0x00000000, 0x00000140, 0x00000200,
	0x00000000, 0x03e52239, 0x0000020d, 0x00000c15,
	0x0c150c15, 0x006c02ec, 0x002501ff, 0x000e0204,
	0x00000200, 0x00000400
पूर्ण;

#घोषणा MI_REG_BASE 0x4300000
#घोषणा NUM_MI_REGS 4
#घोषणा AI_REG_BASE 0x4500000
#घोषणा NUM_AI_REGS 6
#घोषणा PI_REG_BASE 0x4600000
#घोषणा NUM_PI_REGS 5
#घोषणा SI_REG_BASE 0x4800000
#घोषणा NUM_SI_REGS 7

अटल पूर्णांक __init n64_platक्रमm_init(व्योम)
अणु
	अटल स्थिर अक्षर simplefb_resname[] = "FB";
	अटल स्थिर काष्ठा simplefb_platक्रमm_data mode = अणु
		.width = W,
		.height = H,
		.stride = W * 2,
		.क्रमmat = "r5g5b5a1"
	पूर्ण;
	काष्ठा resource res[3];
	व्योम *orig;
	अचिन्हित दीर्घ phys;
	अचिन्हित i;

	स_रखो(res, 0, माप(काष्ठा resource) * 3);
	res[0].flags = IORESOURCE_MEM;
	res[0].start = MI_REG_BASE;
	res[0].end = MI_REG_BASE + NUM_MI_REGS * 4 - 1;

	res[1].flags = IORESOURCE_MEM;
	res[1].start = AI_REG_BASE;
	res[1].end = AI_REG_BASE + NUM_AI_REGS * 4 - 1;

	res[2].flags = IORESOURCE_IRQ;
	res[2].start = RCP_IRQ;
	res[2].end = RCP_IRQ;

	platक्रमm_device_रेजिस्टर_simple("n64audio", -1, res, 3);

	स_रखो(&res[0], 0, माप(res[0]));
	res[0].flags = IORESOURCE_MEM;
	res[0].start = PI_REG_BASE;
	res[0].end = PI_REG_BASE + NUM_PI_REGS * 4 - 1;

	platक्रमm_device_रेजिस्टर_simple("n64cart", -1, res, 1);

	स_रखो(&res[0], 0, माप(res[0]));
	res[0].flags = IORESOURCE_MEM;
	res[0].start = SI_REG_BASE;
	res[0].end = SI_REG_BASE + NUM_SI_REGS * 4 - 1;

	platक्रमm_device_रेजिस्टर_simple("n64joy", -1, res, 1);

	/* The framebuffer needs 64-byte alignment */
	orig = kzalloc(W * H * 2 + 63, GFP_DMA | GFP_KERNEL);
	अगर (!orig)
		वापस -ENOMEM;
	phys = virt_to_phys(orig);
	phys += 63;
	phys &= ~63;

	क्रम (i = 0; i < ARRAY_SIZE(ntsc_320); i++) अणु
		अगर (i == 1)
			n64rdp_ग_लिखो_reg(i, phys);
		अन्यथा
			n64rdp_ग_लिखो_reg(i, ntsc_320[i]);
	पूर्ण

	/* setup IORESOURCE_MEM as framebuffer memory */
	स_रखो(&res[0], 0, माप(res[0]));
	res[0].flags = IORESOURCE_MEM;
	res[0].name = simplefb_resname;
	res[0].start = phys;
	res[0].end = phys + W * H * 2 - 1;

	platक्रमm_device_रेजिस्टर_resndata(शून्य, "simple-framebuffer", 0,
					  &res[0], 1, &mode, माप(mode));

	वापस 0;
पूर्ण

#अघोषित W
#अघोषित H

arch_initcall(n64_platक्रमm_init);

व्योम __init plat_mem_setup(व्योम)
अणु
	iomem_resource_init();
	memblock_add(0x0, 8 * 1024 * 1024); /* Bootloader blocks the 4mb config */
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	/* 93.75 MHz cpu, count रेजिस्टर runs at half rate */
	mips_hpt_frequency = 93750000 / 2;
पूर्ण
