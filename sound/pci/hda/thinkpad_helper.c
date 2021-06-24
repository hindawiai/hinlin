<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Helper functions क्रम Thinkpad LED control;
 * to be included from codec driver
 */

#अगर IS_ENABLED(CONFIG_THINKPAD_ACPI)

#समावेश <linux/acpi.h>
#समावेश <linux/leds.h>

अटल bool is_thinkpad(काष्ठा hda_codec *codec)
अणु
	वापस (codec->core.subप्रणाली_id >> 16 == 0x17aa) &&
	       (acpi_dev_found("LEN0068") || acpi_dev_found("LEN0268") ||
		acpi_dev_found("IBM0068"));
पूर्ण

अटल व्योम hda_fixup_thinkpad_acpi(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		अगर (!is_thinkpad(codec))
			वापस;
		snd_hda_gen_add_mute_led_cdev(codec, शून्य);
		snd_hda_gen_add_micmute_led_cdev(codec, शून्य);
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_THINKPAD_ACPI */

अटल व्योम hda_fixup_thinkpad_acpi(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_THINKPAD_ACPI */
