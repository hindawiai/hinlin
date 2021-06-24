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
#समावेश "speakup.h"
#समावेश "spk_priv.h"
#समावेश "speakup_dtlk.h" /* local header file क्रम LiteTalk values */

#घोषणा DRV_VERSION "2.11"
#घोषणा PROCSPEECH 0x0d

अटल पूर्णांक synth_probe(काष्ठा spk_synth *synth);

अटल काष्ठा var_t vars[] = अणु
	अणु CAPS_START, .u.s = अणु"\x01+35p" पूर्ण पूर्ण,
	अणु CAPS_STOP, .u.s = अणु"\x01-35p" पूर्ण पूर्ण,
	अणु RATE, .u.n = अणु"\x01%ds", 8, 0, 9, 0, 0, शून्य पूर्ण पूर्ण,
	अणु PITCH, .u.n = अणु"\x01%dp", 50, 0, 99, 0, 0, शून्य पूर्ण पूर्ण,
	अणु VOL, .u.n = अणु"\x01%dv", 5, 0, 9, 0, 0, शून्य पूर्ण पूर्ण,
	अणु TONE, .u.n = अणु"\x01%dx", 1, 0, 2, 0, 0, शून्य पूर्ण पूर्ण,
	अणु PUNCT, .u.n = अणु"\x01%db", 7, 0, 15, 0, 0, शून्य पूर्ण पूर्ण,
	अणु VOICE, .u.n = अणु"\x01%do", 0, 0, 7, 0, 0, शून्य पूर्ण पूर्ण,
	अणु FREQUENCY, .u.n = अणु"\x01%df", 5, 0, 9, 0, 0, शून्य पूर्ण पूर्ण,
	अणु सूचीECT, .u.n = अणुशून्य, 0, 0, 1, 0, 0, शून्य पूर्ण पूर्ण,
	V_LAST_VAR
पूर्ण;

/*
 * These attributes will appear in /sys/accessibility/speakup/ltlk.
 */
अटल काष्ठा kobj_attribute caps_start_attribute =
	__ATTR(caps_start, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute caps_stop_attribute =
	__ATTR(caps_stop, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute freq_attribute =
	__ATTR(freq, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute pitch_attribute =
	__ATTR(pitch, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute punct_attribute =
	__ATTR(punct, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute rate_attribute =
	__ATTR(rate, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute tone_attribute =
	__ATTR(tone, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute voice_attribute =
	__ATTR(voice, 0644, spk_var_show, spk_var_store);
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
	&freq_attribute.attr,
	&pitch_attribute.attr,
	&punct_attribute.attr,
	&rate_attribute.attr,
	&tone_attribute.attr,
	&voice_attribute.attr,
	&vol_attribute.attr,
	&delay_समय_attribute.attr,
	&direct_attribute.attr,
	&full_समय_attribute.attr,
	&jअगरfy_delta_attribute.attr,
	&trigger_समय_attribute.attr,
	शून्य,	/* need to शून्य terminate the list of attributes */
पूर्ण;

अटल काष्ठा spk_synth synth_ltlk = अणु
	.name = "ltlk",
	.version = DRV_VERSION,
	.दीर्घ_name = "LiteTalk",
	.init = "\01@\x01\x31y\n\0",
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
	.probe = synth_probe,
	.release = spk_ttyio_release,
	.synth_immediate = spk_ttyio_synth_immediate,
	.catch_up = spk_करो_catch_up,
	.flush = spk_synth_flush,
	.is_alive = spk_synth_is_alive_restart,
	.synth_adjust = शून्य,
	.पढ़ो_buff_add = शून्य,
	.get_index = spk_synth_get_index,
	.indexing = अणु
		.command = "\x01%di",
		.lowindex = 1,
		.highindex = 5,
		.currindex = 1,
	पूर्ण,
	.attributes = अणु
		.attrs = synth_attrs,
		.name = "ltlk",
	पूर्ण,
पूर्ण;

/* पूर्णांकerrogate the LiteTalk and prपूर्णांक its settings */
अटल व्योम synth_पूर्णांकerrogate(काष्ठा spk_synth *synth)
अणु
	अचिन्हित अक्षर *t, i;
	अचिन्हित अक्षर buf[50], rom_v[20];

	synth->synth_immediate(synth, "\x18\x01?");
	क्रम (i = 0; i < 50; i++) अणु
		buf[i] = synth->io_ops->synth_in(synth);
		अगर (i > 2 && buf[i] == 0x7f)
			अवरोध;
	पूर्ण
	t = buf + 2;
	क्रम (i = 0; *t != '\r'; t++) अणु
		rom_v[i] = *t;
		अगर (++i >= 19)
			अवरोध;
	पूर्ण
	rom_v[i] = 0;
	pr_info("%s: ROM version: %s\n", synth->दीर्घ_name, rom_v);
पूर्ण

अटल पूर्णांक synth_probe(काष्ठा spk_synth *synth)
अणु
	पूर्णांक failed = 0;

	failed = spk_ttyio_synth_probe(synth);
	अगर (failed == 0)
		synth_पूर्णांकerrogate(synth);
	synth->alive = !failed;
	वापस failed;
पूर्ण

module_param_named(ser, synth_ltlk.ser, पूर्णांक, 0444);
module_param_named(dev, synth_ltlk.dev_name, अक्षरp, 0444);
module_param_named(start, synth_ltlk.startup, लघु, 0444);

MODULE_PARM_DESC(ser, "Set the serial port for the synthesizer (0-based).");
MODULE_PARM_DESC(dev, "Set the device e.g. ttyUSB0, for the synthesizer.");
MODULE_PARM_DESC(start, "Start the synthesizer once it is loaded.");

module_spk_synth(synth_ltlk);

MODULE_AUTHOR("Kirk Reiser <kirk@braille.uwo.ca>");
MODULE_AUTHOR("David Borowski");
MODULE_DESCRIPTION("Speakup support for DoubleTalk LT/LiteTalk synthesizers");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

