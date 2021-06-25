<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * originally written by: Kirk Reiser <kirk@braille.uwo.ca>
 * this version considerably modअगरied by David Borowski, david575@rogers.com
 *
 * Copyright (C) 1998-99  Kirk Reiser.
 * Copyright (C) 2003 David Borowski.
 *
 * specअगरicly written as a driver क्रम the speakup screenreview
 * s not a general device driver.
 */
#समावेश "spk_priv.h"
#समावेश "speakup.h"

#घोषणा DRV_VERSION "2.11"
#घोषणा SYNTH_CLEAR 0x18
#घोषणा PROCSPEECH '\r'

अटल व्योम synth_flush(काष्ठा spk_synth *synth);

अटल काष्ठा var_t vars[] = अणु
	अणु CAPS_START, .u.s = अणु"\x05P+" पूर्ण पूर्ण,
	अणु CAPS_STOP, .u.s = अणु"\x05P-" पूर्ण पूर्ण,
	अणु RATE, .u.n = अणु"\x05R%d", 7, 0, 9, 0, 0, शून्य पूर्ण पूर्ण,
	अणु PITCH, .u.n = अणु"\x05P%d", 3, 0, 9, 0, 0, शून्य पूर्ण पूर्ण,
	अणु VOL, .u.n = अणु"\x05V%d", 9, 0, 9, 0, 0, शून्य पूर्ण पूर्ण,
	अणु TONE, .u.n = अणु"\x05T%c", 8, 0, 25, 65, 0, शून्य पूर्ण पूर्ण,
	अणु PUNCT, .u.n = अणु"\x05M%c", 0, 0, 3, 0, 0, "nsma" पूर्ण पूर्ण,
	अणु सूचीECT, .u.n = अणुशून्य, 0, 0, 1, 0, 0, शून्य पूर्ण पूर्ण,
	V_LAST_VAR
पूर्ण;

/* These attributes will appear in /sys/accessibility/speakup/spkout. */

अटल काष्ठा kobj_attribute caps_start_attribute =
	__ATTR(caps_start, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute caps_stop_attribute =
	__ATTR(caps_stop, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute pitch_attribute =
	__ATTR(pitch, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute punct_attribute =
	__ATTR(punct, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute rate_attribute =
	__ATTR(rate, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute tone_attribute =
	__ATTR(tone, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute vol_attribute =
	__ATTR(vol, 0644, spk_var_show, spk_var_store);

अटल काष्ठा kobj_attribute delay_समय_attribute =
	__ATTR(delay_समय, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute direct_attribute =
	__ATTR(direct, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute full_समय_attribute =
	__ATTR(full_समय, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute jअगरfy_delta_attribute =
	__ATTR(jअगरfy_delta, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute trigger_समय_attribute =
	__ATTR(trigger_समय, 0644, spk_var_show, spk_var_store);

/*
 * Create a group of attributes so that we can create and destroy them all
 * at once.
 */
अटल काष्ठा attribute *synth_attrs[] = अणु
	&caps_start_attribute.attr,
	&caps_stop_attribute.attr,
	&pitch_attribute.attr,
	&punct_attribute.attr,
	&rate_attribute.attr,
	&tone_attribute.attr,
	&vol_attribute.attr,
	&delay_समय_attribute.attr,
	&direct_attribute.attr,
	&full_समय_attribute.attr,
	&jअगरfy_delta_attribute.attr,
	&trigger_समय_attribute.attr,
	शून्य,	/* need to शून्य terminate the list of attributes */
पूर्ण;

अटल काष्ठा spk_synth synth_spkout = अणु
	.name = "spkout",
	.version = DRV_VERSION,
	.दीर्घ_name = "Speakout",
	.init = "\005W1\005I2\005C3",
	.procspeech = PROCSPEECH,
	.clear = SYNTH_CLEAR,
	.delay = 500,
	.trigger = 50,
	.jअगरfies = 50,
	.full = 40000,
	.dev_name = SYNTH_DEFAULT_DEV,
	.startup = SYNTH_START,
	.checkval = SYNTH_CHECK,
	.vars = vars,
	.io_ops = &spk_ttyio_ops,
	.probe = spk_ttyio_synth_probe,
	.release = spk_ttyio_release,
	.synth_immediate = spk_ttyio_synth_immediate,
	.catch_up = spk_करो_catch_up,
	.flush = synth_flush,
	.is_alive = spk_synth_is_alive_restart,
	.synth_adjust = शून्य,
	.पढ़ो_buff_add = शून्य,
	.get_index = spk_synth_get_index,
	.indexing = अणु
		.command = "\x05[%c",
		.lowindex = 1,
		.highindex = 5,
		.currindex = 1,
	पूर्ण,
	.attributes = अणु
		.attrs = synth_attrs,
		.name = "spkout",
	पूर्ण,
पूर्ण;

अटल व्योम synth_flush(काष्ठा spk_synth *synth)
अणु
	synth->io_ops->flush_buffer(synth);
	synth->io_ops->send_xअक्षर(synth, SYNTH_CLEAR);
पूर्ण

module_param_named(ser, synth_spkout.ser, पूर्णांक, 0444);
module_param_named(dev, synth_spkout.dev_name, अक्षरp, 0444);
module_param_named(start, synth_spkout.startup, लघु, 0444);

MODULE_PARM_DESC(ser, "Set the serial port for the synthesizer (0-based).");
MODULE_PARM_DESC(dev, "Set the device e.g. ttyUSB0, for the synthesizer.");
MODULE_PARM_DESC(start, "Start the synthesizer once it is loaded.");

module_spk_synth(synth_spkout);

MODULE_AUTHOR("Kirk Reiser <kirk@braille.uwo.ca>");
MODULE_AUTHOR("David Borowski");
MODULE_DESCRIPTION("Speakup support for Speak Out synthesizers");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

