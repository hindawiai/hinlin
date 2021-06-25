<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Audio Mute LED trigger
//

#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>

अटल काष्ठा led_trigger *ledtrig_audio[NUM_AUDIO_LEDS];
अटल क्रमागत led_brightness audio_state[NUM_AUDIO_LEDS];

क्रमागत led_brightness ledtrig_audio_get(क्रमागत led_audio type)
अणु
	वापस audio_state[type];
पूर्ण
EXPORT_SYMBOL_GPL(ledtrig_audio_get);

व्योम ledtrig_audio_set(क्रमागत led_audio type, क्रमागत led_brightness state)
अणु
	audio_state[type] = state;
	led_trigger_event(ledtrig_audio[type], state);
पूर्ण
EXPORT_SYMBOL_GPL(ledtrig_audio_set);

अटल पूर्णांक __init ledtrig_audio_init(व्योम)
अणु
	led_trigger_रेजिस्टर_simple("audio-mute",
				    &ledtrig_audio[LED_AUDIO_MUTE]);
	led_trigger_रेजिस्टर_simple("audio-micmute",
				    &ledtrig_audio[LED_AUDIO_MICMUTE]);
	वापस 0;
पूर्ण
module_init(ledtrig_audio_init);

अटल व्योम __निकास ledtrig_audio_निकास(व्योम)
अणु
	led_trigger_unरेजिस्टर_simple(ledtrig_audio[LED_AUDIO_MUTE]);
	led_trigger_unरेजिस्टर_simple(ledtrig_audio[LED_AUDIO_MICMUTE]);
पूर्ण
module_निकास(ledtrig_audio_निकास);

MODULE_DESCRIPTION("LED trigger for audio mute control");
MODULE_LICENSE("GPL v2");
