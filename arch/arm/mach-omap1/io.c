<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/io.c
 *
 * OMAP1 I/O mapping code
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/mux.h>
#समावेश <mach/tc.h>
#समावेश <linux/omap-dma.h>

#समावेश "iomap.h"
#समावेश "common.h"
#समावेश "clock.h"

/*
 * The machine specअगरic code may provide the extra mapping besides the
 * शेष mapping provided here.
 */
अटल काष्ठा map_desc omap_io_desc[] __initdata = अणु
	अणु
		.भव	= OMAP1_IO_VIRT,
		.pfn		= __phys_to_pfn(OMAP1_IO_PHYS),
		.length		= OMAP1_IO_SIZE,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

#अगर defined (CONFIG_ARCH_OMAP730) || defined (CONFIG_ARCH_OMAP850)
अटल काष्ठा map_desc omap7xx_io_desc[] __initdata = अणु
	अणु
		.भव	= OMAP7XX_DSP_BASE,
		.pfn		= __phys_to_pfn(OMAP7XX_DSP_START),
		.length		= OMAP7XX_DSP_SIZE,
		.type		= MT_DEVICE
	पूर्ण, अणु
		.भव	= OMAP7XX_DSPREG_BASE,
		.pfn		= __phys_to_pfn(OMAP7XX_DSPREG_START),
		.length		= OMAP7XX_DSPREG_SIZE,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP15XX
अटल काष्ठा map_desc omap1510_io_desc[] __initdata = अणु
	अणु
		.भव	= OMAP1510_DSP_BASE,
		.pfn		= __phys_to_pfn(OMAP1510_DSP_START),
		.length		= OMAP1510_DSP_SIZE,
		.type		= MT_DEVICE
	पूर्ण, अणु
		.भव	= OMAP1510_DSPREG_BASE,
		.pfn		= __phys_to_pfn(OMAP1510_DSPREG_START),
		.length		= OMAP1510_DSPREG_SIZE,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_OMAP16XX)
अटल काष्ठा map_desc omap16xx_io_desc[] __initdata = अणु
	अणु
		.भव	= OMAP16XX_DSP_BASE,
		.pfn		= __phys_to_pfn(OMAP16XX_DSP_START),
		.length		= OMAP16XX_DSP_SIZE,
		.type		= MT_DEVICE
	पूर्ण, अणु
		.भव	= OMAP16XX_DSPREG_BASE,
		.pfn		= __phys_to_pfn(OMAP16XX_DSPREG_START),
		.length		= OMAP16XX_DSPREG_SIZE,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;
#पूर्ण_अगर

/*
 * Maps common IO regions क्रम omap1
 */
अटल व्योम __init omap1_map_common_io(व्योम)
अणु
	iotable_init(omap_io_desc, ARRAY_SIZE(omap_io_desc));
पूर्ण

#अगर defined (CONFIG_ARCH_OMAP730) || defined (CONFIG_ARCH_OMAP850)
व्योम __init omap7xx_map_io(व्योम)
अणु
	omap1_map_common_io();
	iotable_init(omap7xx_io_desc, ARRAY_SIZE(omap7xx_io_desc));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP15XX
व्योम __init omap15xx_map_io(व्योम)
अणु
	omap1_map_common_io();
	iotable_init(omap1510_io_desc, ARRAY_SIZE(omap1510_io_desc));
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_OMAP16XX)
व्योम __init omap16xx_map_io(व्योम)
अणु
	omap1_map_common_io();
	iotable_init(omap16xx_io_desc, ARRAY_SIZE(omap16xx_io_desc));
पूर्ण
#पूर्ण_अगर

/*
 * Common low-level hardware init क्रम omap1.
 */
व्योम __init omap1_init_early(व्योम)
अणु
	omap_check_revision();

	/* REVISIT: Refer to OMAP5910 Errata, Advisory SYS_1: "Timeout Abort
	 * on a Posted Write in the TIPB Bridge".
	 */
	omap_ग_लिखोw(0x0, MPU_PUBLIC_TIPB_CNTL);
	omap_ग_लिखोw(0x0, MPU_PRIVATE_TIPB_CNTL);

	/* Must init घड़ीs early to assure that समयr पूर्णांकerrupt works
	 */
	omap1_clk_init();
	omap1_mux_init();
पूर्ण

व्योम __init omap1_init_late(व्योम)
अणु
	omap_serial_wakeup_init();
पूर्ण

/*
 * NOTE: Please use ioremap + __raw_पढ़ो/ग_लिखो where possible instead of these
 */

u8 omap_पढ़ोb(u32 pa)
अणु
	वापस __raw_पढ़ोb(OMAP1_IO_ADDRESS(pa));
पूर्ण
EXPORT_SYMBOL(omap_पढ़ोb);

u16 omap_पढ़ोw(u32 pa)
अणु
	वापस __raw_पढ़ोw(OMAP1_IO_ADDRESS(pa));
पूर्ण
EXPORT_SYMBOL(omap_पढ़ोw);

u32 omap_पढ़ोl(u32 pa)
अणु
	वापस __raw_पढ़ोl(OMAP1_IO_ADDRESS(pa));
पूर्ण
EXPORT_SYMBOL(omap_पढ़ोl);

व्योम omap_ग_लिखोb(u8 v, u32 pa)
अणु
	__raw_ग_लिखोb(v, OMAP1_IO_ADDRESS(pa));
पूर्ण
EXPORT_SYMBOL(omap_ग_लिखोb);

व्योम omap_ग_लिखोw(u16 v, u32 pa)
अणु
	__raw_ग_लिखोw(v, OMAP1_IO_ADDRESS(pa));
पूर्ण
EXPORT_SYMBOL(omap_ग_लिखोw);

व्योम omap_ग_लिखोl(u32 v, u32 pa)
अणु
	__raw_ग_लिखोl(v, OMAP1_IO_ADDRESS(pa));
पूर्ण
EXPORT_SYMBOL(omap_ग_लिखोl);
