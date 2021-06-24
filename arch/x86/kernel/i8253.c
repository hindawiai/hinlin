<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * 8253/PIT functions
 *
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/init.h>
#समावेश <linux/समयx.h>
#समावेश <linux/i8253.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/smp.h>

/*
 * HPET replaces the PIT, when enabled. So we need to know, which of
 * the two समयrs is used
 */
काष्ठा घड़ी_event_device *global_घड़ी_event;

/*
 * Modern chipsets can disable the PIT घड़ी which makes it unusable. It
 * would be possible to enable the घड़ी but the रेजिस्टरs are chipset
 * specअगरic and not discoverable. Aव्योम the whack a mole game.
 *
 * These platक्रमms have discoverable TSC/CPU frequencies but this also
 * requires to know the local APIC समयr frequency as it normally is
 * calibrated against the PIT पूर्णांकerrupt.
 */
अटल bool __init use_pit(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_X86_TSC) || !boot_cpu_has(X86_FEATURE_TSC))
		वापस true;

	/* This also वापसs true when APIC is disabled */
	वापस apic_needs_pit();
पूर्ण

bool __init pit_समयr_init(व्योम)
अणु
	अगर (!use_pit())
		वापस false;

	घड़ीevent_i8253_init(true);
	global_घड़ी_event = &i8253_घड़ीevent;
	वापस true;
पूर्ण

#अगर_अघोषित CONFIG_X86_64
अटल पूर्णांक __init init_pit_घड़ीsource(व्योम)
अणु
	 /*
	  * Several reasons not to रेजिस्टर PIT as a घड़ीsource:
	  *
	  * - On SMP PIT करोes not scale due to i8253_lock
	  * - when HPET is enabled
	  * - when local APIC समयr is active (PIT is चयनed off)
	  */
	अगर (num_possible_cpus() > 1 || is_hpet_enabled() ||
	    !घड़ीevent_state_periodic(&i8253_घड़ीevent))
		वापस 0;

	वापस घड़ीsource_i8253_init();
पूर्ण
arch_initcall(init_pit_घड़ीsource);
#पूर्ण_अगर /* !CONFIG_X86_64 */
