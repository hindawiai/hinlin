<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IXP4xx Device Tree boot support
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/hardware.h>
#समावेश <mach/ixp4xx-regs.h>

अटल काष्ठा map_desc ixp4xx_of_io_desc[] __initdata = अणु
	/*
	 * This is needed क्रम runसमय प्रणाली configuration checks,
	 * such as पढ़ोing अगर hardware so-and-so is present. This
	 * could eventually be converted पूर्णांकo a syscon once all boards
	 * are converted to device tree.
	 */
	अणु
		.भव = IXP4XX_EXP_CFG_BASE_VIRT,
		.pfn = __phys_to_pfn(IXP4XX_EXP_CFG_BASE_PHYS),
		.length = SZ_4K,
		.type = MT_DEVICE,
	पूर्ण,
#अगर_घोषित CONFIG_DEBUG_UART_8250
	/* This is needed क्रम LL-debug/earlyprपूर्णांकk/debug-macro.S */
	अणु
		.भव = CONFIG_DEBUG_UART_VIRT,
		.pfn = __phys_to_pfn(CONFIG_DEBUG_UART_PHYS),
		.length = SZ_4K,
		.type = MT_DEVICE,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल व्योम __init ixp4xx_of_map_io(व्योम)
अणु
	iotable_init(ixp4xx_of_io_desc, ARRAY_SIZE(ixp4xx_of_io_desc));
पूर्ण

/*
 * We handle 4 dअगरferen SoC families. These compatible strings are enough
 * to provide the core so that dअगरferent boards can add their more detailed
 * specअगरics.
 */
अटल स्थिर अक्षर *ixp4xx_of_board_compat[] = अणु
	"intel,ixp42x",
	"intel,ixp43x",
	"intel,ixp45x",
	"intel,ixp46x",
	शून्य,
पूर्ण;

DT_MACHINE_START(IXP4XX_DT, "IXP4xx (Device Tree)")
	.map_io		= ixp4xx_of_map_io,
	.dt_compat	= ixp4xx_of_board_compat,
MACHINE_END
