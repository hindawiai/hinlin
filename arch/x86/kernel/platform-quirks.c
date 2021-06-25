<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/bios_ebda.h>

व्योम __init x86_early_init_platक्रमm_quirks(व्योम)
अणु
	x86_platक्रमm.legacy.i8042 = X86_LEGACY_I8042_EXPECTED_PRESENT;
	x86_platक्रमm.legacy.rtc = 1;
	x86_platक्रमm.legacy.warm_reset = 1;
	x86_platक्रमm.legacy.reserve_bios_regions = 0;
	x86_platक्रमm.legacy.devices.pnpbios = 1;

	चयन (boot_params.hdr.hardware_subarch) अणु
	हाल X86_SUBARCH_PC:
		x86_platक्रमm.legacy.reserve_bios_regions = 1;
		अवरोध;
	हाल X86_SUBARCH_XEN:
		x86_platक्रमm.legacy.devices.pnpbios = 0;
		x86_platक्रमm.legacy.rtc = 0;
		अवरोध;
	हाल X86_SUBARCH_INTEL_MID:
	हाल X86_SUBARCH_CE4100:
		x86_platक्रमm.legacy.devices.pnpbios = 0;
		x86_platक्रमm.legacy.rtc = 0;
		x86_platक्रमm.legacy.i8042 = X86_LEGACY_I8042_PLATFORM_ABSENT;
		अवरोध;
	पूर्ण

	अगर (x86_platक्रमm.set_legacy_features)
		x86_platक्रमm.set_legacy_features();
पूर्ण

bool __init x86_pnpbios_disabled(व्योम)
अणु
	वापस x86_platक्रमm.legacy.devices.pnpbios == 0;
पूर्ण

#अगर defined(CONFIG_PNPBIOS)
bool __init arch_pnpbios_disabled(व्योम)
अणु
	वापस x86_pnpbios_disabled();
पूर्ण
#पूर्ण_अगर
