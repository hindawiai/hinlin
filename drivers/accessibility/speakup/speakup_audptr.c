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
#घोषणा SYNTH_CLEAR 0x18 /* flush synth buffer */
#घोषणा PROCSPEECH '\r' /* start synth processing speech अक्षर */

अटल पूर्णांक synth_probe(काष्ठा spk_synth *synth);
अटल व्योम synth_flush(काष्ठा spk_synth *synth);

अटल काष्ठा var_t vars[] = अणु
	अणु CAPS_START, .u.s = अणु"\x05[f99]" पूर्ण पूर्ण,
	अणु CAPS_STOP, .u.s = अणु"\x05[f80]" पूर्ण पूर्ण,
	अणु RATE, .u.n = अणु"\x05[r%d]", 10, 0, 20, 100, -10, शून्य पूर्ण पूर्ण,
	अणु PITCH, .u.n = अणु"\x05[f%d]", 80, 39, 4500, 0, 0, शून्य पूर्ण पूर्ण,
	अणु VOL, .u.n = अणु"\x05[g%d]", 21, 0, 40, 0, 0, शून्य पूर्ण पूर्ण,
	अणु TONE, .u.n = अणु"\x05[s%d]", 9, 0, 63, 0, 0, शून्य पूर्ण पूर्ण,
	अणु PUNCT, .u.n = अणु"\x05[A%c]", 0, 0, 3, 0, 0, "nmsa" पूर्ण पूर्ण,
	अणु सूचीECT, .u.n = अणुशून्य, 0, 0, 1, 0, 0, शून्य पूर्ण पूर्ण,
	V_LAST_VAR
पूर्ण;

/*
 * These attributes will appear in /sys/accessibility/speakup/audptr.
 */
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

अटल काष्ठा spk_synth synth_audptr = अणु
	.name = "audptr",
	.version = DRV_VERSION,
	.दीर्घ_name = "Audapter",
	.init = "\x05[D1]\x05[Ol]",
	.procspeech = PROCSPEECH,
	.clear = SYNTH_CLEAR,
	.delay = 400,
	.trigger = 50,
	.jअगरfies = 30,
	.full = 18000,
	.dev_name = SYNTH_DEFAULT_DEV,
	.startup = SYNTH_START,
	.checkval = SYNTH_CHECK,
	.vars = vars,
	.io_ops = &spk_ttyio_ops,
	.probe = synth_probe,
	.release = spk_ttyio_release,
	.synth_immediate = spk_ttyio_synth_immediate,
	.catch_up = spk_करो_catch_up,
	.flush = synth_flush,
	.is_alive = spk_synth_is_alive_restart,
	.synth_adjust = शून्य,
	.पढ़ो_buff_add = शून्य,
	.get_index = शून्य,
	.indexing = अणु
		.command = शून्य,
		.lowindex = 0,
		.highindex = 0,
		.currindex = 0,
	पूर्ण,
	.attributes = अणु
		.attrs = synth_attrs,
		.name = "audptr",
	पूर्ण,
पूर्ण;

अटल व्योम synth_flush(काष्ठा spk_synth *synth)
अणु
	synth->io_ops->flush_buffer(synth);
	synth->io_ops->send_xअक्षर(synth, SYNTH_CLEAR);
	synth->io_ops->synth_out(synth, PROCSPEECH);
पूर्ण

अटल व्योम synth_version(काष्ठा spk_synth *synth)
अणु
	अचिन्हित अक्षर test = 0;
	अक्षर synth_id[40] = "";

	synth->synth_immediate(synth, "\x05[Q]");
	synth_id[test] = synth->io_ops->synth_in(synth);
	अगर (synth_id[test] == 'A') अणु
		करो अणु
			/* पढ़ो version string from synth */
			synth_id[++test] = synth->io_ops->synth_in(synth);
		पूर्ण जबतक (synth_id[test] != '\n' && test < 32);
		synth_id[++test] = 0x00;
	पूर्ण
	अगर (synth_id[0] == 'A')
		pr_info("%s version: %s", synth->दीर्घ_name, synth_id);
पूर्ण

अटल पूर्णांक synth_probe(काष्ठा spk_synth *synth)
अणु
	पूर्णांक failed;

	failed = spk_ttyio_synth_probe(synth);
	अगर (failed == 0)
		synth_version(synth);
	synth->alive = !failed;
	वापस 0;
पूर्ण

module_param_named(ser, synth_audptr.ser, पूर्णांक, 0444);
module_param_named(dev, synth_audptr.dev_name, अक्षरp, 0444);
module_param_named(start, synth_audptr.startup, लघु, 0444);

MODULE_PARM_DESC(ser, "Set the serial port for the synthesizer (0-based).");
MODULE_PARM_DESC(dev, "Set the device e.g. ttyUSB0, for the synthesizer.");
MODULE_PARM_DESC(start, "Start the synthesizer once it is loaded.");

module_spk_synth(synth_audptr);

MODULE_AUTHOR("Kirk Reiser <kirk@braille.uwo.ca>");
MODULE_AUTHOR("David Borowski");
MODULE_DESCRIPTION("Speakup support for Audapter synthesizer");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

