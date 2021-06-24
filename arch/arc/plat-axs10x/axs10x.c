<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AXS101/AXS103 Software Development Platक्रमm
 *
 * Copyright (C) 2013-15 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/libfdt.h>

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mach_desc.h>
#समावेश <soc/arc/mcip.h>

#घोषणा AXS_MB_CGU		0xE0010000
#घोषणा AXS_MB_CREG		0xE0011000

#घोषणा CREG_MB_IRQ_MUX		(AXS_MB_CREG + 0x214)
#घोषणा CREG_MB_SW_RESET	(AXS_MB_CREG + 0x220)
#घोषणा CREG_MB_VER		(AXS_MB_CREG + 0x230)
#घोषणा CREG_MB_CONFIG		(AXS_MB_CREG + 0x234)

#घोषणा AXC001_CREG		0xF0001000
#घोषणा AXC001_GPIO_INTC	0xF0003000

अटल व्योम __init axs10x_enable_gpio_पूर्णांकc_wire(व्योम)
अणु
	/*
	 * Peripherals on CPU Card and Mother Board are wired to cpu पूर्णांकc via
	 * पूर्णांकermediate DW APB GPIO blocks (मुख्यly क्रम debouncing)
	 *
	 *         ---------------------
	 *        |  snps,arc700-पूर्णांकc |
	 *        ---------------------
	 *          | #7          | #15
	 * -------------------   -------------------
	 * | snps,dw-apb-gpio |  | snps,dw-apb-gpio |
	 * -------------------   -------------------
	 *        | #12                     |
	 *        |                 [ Debug UART on cpu card ]
	 *        |
	 * ------------------------
	 * | snps,dw-apb-पूर्णांकc (MB)|
	 * ------------------------
	 *  |      |       |      |
	 * [eth] [uart]        [... other perip on Main Board]
	 *
	 * Current implementation of "irq-dw-apb-ictl" driver करोesn't work well
	 * with stacked INTCs. In particular problem happens अगर its master INTC
	 * not yet instantiated. See discussion here -
	 * https://lkml.org/lkml/2015/3/4/755
	 *
	 * So setup the first gpio block as a passive pass thru and hide it from
	 * DT hardware topology - connect MB पूर्णांकc directly to cpu पूर्णांकc
	 * The GPIO "wire" needs to be init nevertheless (here)
	 *
	 * One side adv is that peripheral पूर्णांकerrupt handling aव्योमs one nested
	 * पूर्णांकc ISR hop
	 */
#घोषणा GPIO_INTEN		(AXC001_GPIO_INTC + 0x30)
#घोषणा GPIO_INTMASK		(AXC001_GPIO_INTC + 0x34)
#घोषणा GPIO_INTTYPE_LEVEL	(AXC001_GPIO_INTC + 0x38)
#घोषणा GPIO_INT_POLARITY	(AXC001_GPIO_INTC + 0x3c)
#घोषणा MB_TO_GPIO_IRQ		12

	ioग_लिखो32(~(1 << MB_TO_GPIO_IRQ), (व्योम __iomem *) GPIO_INTMASK);
	ioग_लिखो32(0, (व्योम __iomem *) GPIO_INTTYPE_LEVEL);
	ioग_लिखो32(~0, (व्योम __iomem *) GPIO_INT_POLARITY);
	ioग_लिखो32(1 << MB_TO_GPIO_IRQ, (व्योम __iomem *) GPIO_INTEN);
पूर्ण

अटल व्योम __init axs10x_prपूर्णांक_board_ver(अचिन्हित पूर्णांक creg, स्थिर अक्षर *str)
अणु
	जोड़ ver अणु
		काष्ठा अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
			अचिन्हित पूर्णांक pad:11, y:12, m:4, d:5;
#अन्यथा
			अचिन्हित पूर्णांक d:5, m:4, y:12, pad:11;
#पूर्ण_अगर
		पूर्ण;
		अचिन्हित पूर्णांक val;
	पूर्ण board;

	board.val = ioपढ़ो32((व्योम __iomem *)creg);
	pr_info("AXS: %s FPGA Date: %u-%u-%u\n", str, board.d, board.m,
		board.y);
पूर्ण

अटल व्योम __init axs10x_early_init(व्योम)
अणु
	पूर्णांक mb_rev;
	अक्षर mb[32];

	/* Determine motherboard version */
	अगर (ioपढ़ो32((व्योम __iomem *) CREG_MB_CONFIG) & (1 << 28))
		mb_rev = 3;	/* HT-3 (rev3.0) */
	अन्यथा
		mb_rev = 2;	/* HT-2 (rev2.0) */

	axs10x_enable_gpio_पूर्णांकc_wire();

	scnम_लिखो(mb, 32, "MainBoard v%d", mb_rev);
	axs10x_prपूर्णांक_board_ver(CREG_MB_VER, mb);
पूर्ण

#अगर_घोषित CONFIG_AXS101

#घोषणा CREG_CPU_ADDR_770	(AXC001_CREG + 0x20)
#घोषणा CREG_CPU_ADDR_TUNN	(AXC001_CREG + 0x60)
#घोषणा CREG_CPU_ADDR_770_UPD	(AXC001_CREG + 0x34)
#घोषणा CREG_CPU_ADDR_TUNN_UPD	(AXC001_CREG + 0x74)

#घोषणा CREG_CPU_ARC770_IRQ_MUX	(AXC001_CREG + 0x114)
#घोषणा CREG_CPU_GPIO_UART_MUX	(AXC001_CREG + 0x120)

/*
 * Set up System Memory Map क्रम ARC cpu / peripherals controllers
 *
 * Each AXI master has a 4GB memory map specअगरied as 16 apertures of 256MB, each
 * of which maps to a corresponding 256MB aperture in Target slave memory map.
 *
 * e.g. ARC cpu AXI Master's aperture 8 (0x8000_0000) is mapped to aperture 0
 * (0x0000_0000) of DDR Port 0 (slave #1)
 *
 * Access from cpu to MB controllers such as GMAC is setup using AXI Tunnel:
 * which has master/slaves on both ends.
 * e.g. aperture 14 (0xE000_0000) of ARC cpu is mapped to aperture 14
 * (0xE000_0000) of CPU Card AXI Tunnel slave (slave #3) which is mapped to
 * MB AXI Tunnel Master, which also has a mem map setup
 *
 * In the reverse direction, MB AXI Masters (e.g. GMAC) mem map is setup
 * to map to MB AXI Tunnel slave which connects to CPU Card AXI Tunnel Master
 */
काष्ठा aperture अणु
	अचिन्हित पूर्णांक slave_sel:4, slave_off:4, pad:24;
पूर्ण;

/* CPU Card target slaves */
#घोषणा AXC001_SLV_NONE			0
#घोषणा AXC001_SLV_DDR_PORT0		1
#घोषणा AXC001_SLV_SRAM			2
#घोषणा AXC001_SLV_AXI_TUNNEL		3
#घोषणा AXC001_SLV_AXI2APB		6
#घोषणा AXC001_SLV_DDR_PORT1		7

/* MB AXI Target slaves */
#घोषणा AXS_MB_SLV_NONE			0
#घोषणा AXS_MB_SLV_AXI_TUNNEL_CPU	1
#घोषणा AXS_MB_SLV_AXI_TUNNEL_HAPS	2
#घोषणा AXS_MB_SLV_SRAM			3
#घोषणा AXS_MB_SLV_CONTROL		4

/* MB AXI masters */
#घोषणा AXS_MB_MST_TUNNEL_CPU		0
#घोषणा AXS_MB_MST_USB_OHCI		10

/*
 * memmap क्रम ARC core on CPU Card
 */
अटल स्थिर काष्ठा aperture axc001_memmap[16] = अणु
	अणुAXC001_SLV_AXI_TUNNEL,		0x0पूर्ण,
	अणुAXC001_SLV_AXI_TUNNEL,		0x1पूर्ण,
	अणुAXC001_SLV_SRAM,		0x0पूर्ण, /* 0x2000_0000: Local SRAM */
	अणुAXC001_SLV_NONE,		0x0पूर्ण,
	अणुAXC001_SLV_NONE,		0x0पूर्ण,
	अणुAXC001_SLV_NONE,		0x0पूर्ण,
	अणुAXC001_SLV_NONE,		0x0पूर्ण,
	अणुAXC001_SLV_NONE,		0x0पूर्ण,
	अणुAXC001_SLV_DDR_PORT0,		0x0पूर्ण, /* 0x8000_0000: DDR   0..256M */
	अणुAXC001_SLV_DDR_PORT0,		0x1पूर्ण, /* 0x9000_0000: DDR 256..512M */
	अणुAXC001_SLV_DDR_PORT0,		0x2पूर्ण,
	अणुAXC001_SLV_DDR_PORT0,		0x3पूर्ण,
	अणुAXC001_SLV_NONE,		0x0पूर्ण,
	अणुAXC001_SLV_AXI_TUNNEL,		0xDपूर्ण,
	अणुAXC001_SLV_AXI_TUNNEL,		0xEपूर्ण, /* MB: CREG, CGU... */
	अणुAXC001_SLV_AXI2APB,		0x0पूर्ण, /* CPU Card local CREG, CGU... */
पूर्ण;

/*
 * memmap क्रम CPU Card AXI Tunnel Master (क्रम access by MB controllers)
 * GMAC (MB) -> MB AXI Tunnel slave -> CPU Card AXI Tunnel Master -> DDR
 */
अटल स्थिर काष्ठा aperture axc001_axi_tunnel_memmap[16] = अणु
	अणुAXC001_SLV_AXI_TUNNEL,		0x0पूर्ण,
	अणुAXC001_SLV_AXI_TUNNEL,		0x1पूर्ण,
	अणुAXC001_SLV_SRAM,		0x0पूर्ण,
	अणुAXC001_SLV_NONE,		0x0पूर्ण,
	अणुAXC001_SLV_NONE,		0x0पूर्ण,
	अणुAXC001_SLV_NONE,		0x0पूर्ण,
	अणुAXC001_SLV_NONE,		0x0पूर्ण,
	अणुAXC001_SLV_NONE,		0x0पूर्ण,
	अणुAXC001_SLV_DDR_PORT1,		0x0पूर्ण,
	अणुAXC001_SLV_DDR_PORT1,		0x1पूर्ण,
	अणुAXC001_SLV_DDR_PORT1,		0x2पूर्ण,
	अणुAXC001_SLV_DDR_PORT1,		0x3पूर्ण,
	अणुAXC001_SLV_NONE,		0x0पूर्ण,
	अणुAXC001_SLV_AXI_TUNNEL,		0xDपूर्ण,
	अणुAXC001_SLV_AXI_TUNNEL,		0xEपूर्ण,
	अणुAXC001_SLV_AXI2APB,		0x0पूर्ण,
पूर्ण;

/*
 * memmap क्रम MB AXI Masters
 * Same mem map क्रम all perip controllers as well as MB AXI Tunnel Master
 */
अटल स्थिर काष्ठा aperture axs_mb_memmap[16] = अणु
	अणुAXS_MB_SLV_SRAM,		0x0पूर्ण,
	अणुAXS_MB_SLV_SRAM,		0x0पूर्ण,
	अणुAXS_MB_SLV_NONE,		0x0पूर्ण,
	अणुAXS_MB_SLV_NONE,		0x0पूर्ण,
	अणुAXS_MB_SLV_NONE,		0x0पूर्ण,
	अणुAXS_MB_SLV_NONE,		0x0पूर्ण,
	अणुAXS_MB_SLV_NONE,		0x0पूर्ण,
	अणुAXS_MB_SLV_NONE,		0x0पूर्ण,
	अणुAXS_MB_SLV_AXI_TUNNEL_CPU,	0x8पूर्ण,	/* DDR on CPU Card */
	अणुAXS_MB_SLV_AXI_TUNNEL_CPU,	0x9पूर्ण,	/* DDR on CPU Card */
	अणुAXS_MB_SLV_AXI_TUNNEL_CPU,	0xAपूर्ण,
	अणुAXS_MB_SLV_AXI_TUNNEL_CPU,	0xBपूर्ण,
	अणुAXS_MB_SLV_NONE,		0x0पूर्ण,
	अणुAXS_MB_SLV_AXI_TUNNEL_HAPS,	0xDपूर्ण,
	अणुAXS_MB_SLV_CONTROL,		0x0पूर्ण,	/* MB Local CREG, CGU... */
	अणुAXS_MB_SLV_AXI_TUNNEL_CPU,	0xFपूर्ण,
पूर्ण;

अटल noअंतरभूत व्योम __init
axs101_set_memmap(व्योम __iomem *base, स्थिर काष्ठा aperture map[16])
अणु
	अचिन्हित पूर्णांक slave_select, slave_offset;
	पूर्णांक i;

	slave_select = slave_offset = 0;
	क्रम (i = 0; i < 8; i++) अणु
		slave_select |= map[i].slave_sel << (i << 2);
		slave_offset |= map[i].slave_off << (i << 2);
	पूर्ण

	ioग_लिखो32(slave_select, base + 0x0);	/* SLV0 */
	ioग_लिखो32(slave_offset, base + 0x8);	/* OFFSET0 */

	slave_select = slave_offset = 0;
	क्रम (i = 0; i < 8; i++) अणु
		slave_select |= map[i+8].slave_sel << (i << 2);
		slave_offset |= map[i+8].slave_off << (i << 2);
	पूर्ण

	ioग_लिखो32(slave_select, base + 0x4);	/* SLV1 */
	ioग_लिखो32(slave_offset, base + 0xC);	/* OFFSET1 */
पूर्ण

अटल व्योम __init axs101_early_init(व्योम)
अणु
	पूर्णांक i;

	/* ARC 770D memory view */
	axs101_set_memmap((व्योम __iomem *) CREG_CPU_ADDR_770, axc001_memmap);
	ioग_लिखो32(1, (व्योम __iomem *) CREG_CPU_ADDR_770_UPD);

	/* AXI tunnel memory map (incoming traffic from MB पूर्णांकo CPU Card */
	axs101_set_memmap((व्योम __iomem *) CREG_CPU_ADDR_TUNN,
			      axc001_axi_tunnel_memmap);
	ioग_लिखो32(1, (व्योम __iomem *) CREG_CPU_ADDR_TUNN_UPD);

	/* MB peripherals memory map */
	क्रम (i = AXS_MB_MST_TUNNEL_CPU; i <= AXS_MB_MST_USB_OHCI; i++)
		axs101_set_memmap((व्योम __iomem *) AXS_MB_CREG + (i << 4),
				      axs_mb_memmap);

	ioग_लिखो32(0x3ff, (व्योम __iomem *) AXS_MB_CREG + 0x100); /* Update */

	/* GPIO pins 18 and 19 are used as UART rx and tx, respectively. */
	ioग_लिखो32(0x01, (व्योम __iomem *) CREG_CPU_GPIO_UART_MUX);

	/* Set up the MB पूर्णांकerrupt प्रणाली: mux पूर्णांकerrupts to GPIO7) */
	ioग_लिखो32(0x01, (व्योम __iomem *) CREG_MB_IRQ_MUX);

	/* reset ethernet and ULPI पूर्णांकerfaces */
	ioग_लिखो32(0x18, (व्योम __iomem *) CREG_MB_SW_RESET);

	/* map GPIO 14:10 to ARC 9:5 (IRQ mux change क्रम MB v2 onwards) */
	ioग_लिखो32(0x52, (व्योम __iomem *) CREG_CPU_ARC770_IRQ_MUX);

	axs10x_early_init();
पूर्ण

#पूर्ण_अगर	/* CONFIG_AXS101 */

#अगर_घोषित CONFIG_AXS103

#घोषणा AXC003_CREG	0xF0001000
#घोषणा AXC003_MST_AXI_TUNNEL	0
#घोषणा AXC003_MST_HS38		1

#घोषणा CREG_CPU_AXI_M0_IRQ_MUX	(AXC003_CREG + 0x440)
#घोषणा CREG_CPU_GPIO_UART_MUX	(AXC003_CREG + 0x480)
#घोषणा CREG_CPU_TUN_IO_CTRL	(AXC003_CREG + 0x494)


अटल व्योम __init axs103_early_init(व्योम)
अणु
#अगर_घोषित CONFIG_ARC_MCIP
	/*
	 * AXS103 configurations क्रम SMP/QUAD configurations share device tree
	 * which शेषs to 100 MHz. However recent failures of Quad config
	 * revealed P&R timing violations so clamp it करोwn to safe 50 MHz
	 * Instead of duplicating defconfig/DT क्रम SMP/QUAD, add a small hack
	 * of fudging the freq in DT
	 */
#घोषणा AXS103_QUAD_CORE_CPU_FREQ_HZ	50000000

	अचिन्हित पूर्णांक num_cores = (पढ़ो_aux_reg(ARC_REG_MCIP_BCR) >> 16) & 0x3F;
	अगर (num_cores > 2) अणु
		u32 freq;
		पूर्णांक off = fdt_path_offset(initial_boot_params, "/cpu_card/core_clk");
		स्थिर काष्ठा fdt_property *prop;

		prop = fdt_get_property(initial_boot_params, off,
					"assigned-clock-rates", शून्य);
		freq = be32_to_cpu(*(u32 *)(prop->data));

		/* Patching .dtb in-place with new core घड़ी value */
		अगर (freq != AXS103_QUAD_CORE_CPU_FREQ_HZ) अणु
			freq = cpu_to_be32(AXS103_QUAD_CORE_CPU_FREQ_HZ);
			fdt_setprop_inplace(initial_boot_params, off,
					    "assigned-clock-rates", &freq, माप(freq));
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Memory maps alपढ़ोy config in pre-bootloader */

	/* set GPIO mux to UART */
	ioग_लिखो32(0x01, (व्योम __iomem *) CREG_CPU_GPIO_UART_MUX);

	ioग_लिखो32((0x00100000U | 0x000C0000U | 0x00003322U),
		  (व्योम __iomem *) CREG_CPU_TUN_IO_CTRL);

	/* Set up the AXS_MB पूर्णांकerrupt प्रणाली.*/
	ioग_लिखो32(12, (व्योम __iomem *) (CREG_CPU_AXI_M0_IRQ_MUX
					 + (AXC003_MST_HS38 << 2)));

	/* connect ICTL - Main Board with GPIO line */
	ioग_लिखो32(0x01, (व्योम __iomem *) CREG_MB_IRQ_MUX);

	axs10x_prपूर्णांक_board_ver(AXC003_CREG + 4088, "AXC003 CPU Card");

	axs10x_early_init();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_AXS101

अटल स्थिर अक्षर *axs101_compat[] __initस्थिर = अणु
	"snps,axs101",
	शून्य,
पूर्ण;

MACHINE_START(AXS101, "axs101")
	.dt_compat	= axs101_compat,
	.init_early	= axs101_early_init,
MACHINE_END

#पूर्ण_अगर	/* CONFIG_AXS101 */

#अगर_घोषित CONFIG_AXS103

अटल स्थिर अक्षर *axs103_compat[] __initस्थिर = अणु
	"snps,axs103",
	शून्य,
पूर्ण;

MACHINE_START(AXS103, "axs103")
	.dt_compat	= axs103_compat,
	.init_early	= axs103_early_init,
MACHINE_END

/*
 * For the VDK OS-kit, to get the offset to pid and command fields
 */
अक्षर coware_swa_pid_offset[TASK_PID];
अक्षर coware_swa_comm_offset[TASK_COMM];

#पूर्ण_अगर	/* CONFIG_AXS103 */
