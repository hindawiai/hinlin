<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Gemini Device Tree boot support
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/proc-fns.h>

#अगर_घोषित CONFIG_DEBUG_GEMINI
/* This is needed क्रम LL-debug/earlyprपूर्णांकk/debug-macro.S */
अटल काष्ठा map_desc gemini_io_desc[] __initdata = अणु
	अणु
		.भव = CONFIG_DEBUG_UART_VIRT,
		.pfn = __phys_to_pfn(CONFIG_DEBUG_UART_PHYS),
		.length = SZ_4K,
		.type = MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल व्योम __init gemini_map_io(व्योम)
अणु
	iotable_init(gemini_io_desc, ARRAY_SIZE(gemini_io_desc));
पूर्ण
#अन्यथा
#घोषणा gemini_map_io शून्य
#पूर्ण_अगर

अटल व्योम gemini_idle(व्योम)
अणु
	/*
	 * Because of broken hardware we have to enable पूर्णांकerrupts or the CPU
	 * will never wakeup... Acctualy it is not very good to enable
	 * पूर्णांकerrupts first since scheduler can miss a tick, but there is
	 * no other way around this. Platक्रमms that needs it क्रम घातer saving
	 * should enable it in init code, since by शेष it is
	 * disabled.
	 */

	/* FIXME: Enabling पूर्णांकerrupts here is racy! */
	local_irq_enable();
	cpu_करो_idle();
पूर्ण

अटल व्योम __init gemini_init_machine(व्योम)
अणु
	arm_pm_idle = gemini_idle;
पूर्ण

अटल स्थिर अक्षर *gemini_board_compat[] = अणु
	"cortina,gemini",
	शून्य,
पूर्ण;

DT_MACHINE_START(GEMINI_DT, "Gemini (Device Tree)")
	.map_io		= gemini_map_io,
	.init_machine	= gemini_init_machine,
	.dt_compat	= gemini_board_compat,
MACHINE_END
