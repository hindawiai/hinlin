<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * originally written by: Kirk Reiser <kirk@braille.uwo.ca>
 * this version considerably modअगरied by David Borowski, david575@rogers.com
 *
 * Copyright (C) 1998-99  Kirk Reiser.
 * Copyright (C) 2003 David Borowski.
 *
 * this code is specअगरicly written as a driver क्रम the speakup screenreview
 * package and is not a general device driver.
 */
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/serial_reg.h>	/* क्रम UART_MCR* स्थिरants */

#समावेश "spk_priv.h"
#समावेश "speakup.h"

#घोषणा DRV_VERSION "2.21"
#घोषणा SYNTH_CLEAR 0x18
#घोषणा PROCSPEECH '\r'

अटल व्योम करो_catch_up(काष्ठा spk_synth *synth);

अटल काष्ठा var_t vars[] = अणु
	अणु CAPS_START, .u.s = अणु"cap, " पूर्ण पूर्ण,
	अणु CAPS_STOP, .u.s = अणु"" पूर्ण पूर्ण,
	अणु RATE, .u.n = अणु"@W%d", 6, 1, 9, 0, 0, शून्य पूर्ण पूर्ण,
	अणु PITCH, .u.n = अणु"@F%x", 10, 0, 15, 0, 0, शून्य पूर्ण पूर्ण,
	अणु VOL, .u.n = अणु"@A%x", 10, 0, 15, 0, 0, शून्य पूर्ण पूर्ण,
	अणु VOICE, .u.n = अणु"@V%d", 1, 1, 6, 0, 0, शून्य पूर्ण पूर्ण,
	अणु LANG, .u.n = अणु"@=%d,", 1, 1, 4, 0, 0, शून्य पूर्ण पूर्ण,
	अणु सूचीECT, .u.n = अणुशून्य, 0, 0, 1, 0, 0, शून्य पूर्ण पूर्ण,
	V_LAST_VAR
पूर्ण;

/*
 * These attributes will appear in /sys/accessibility/speakup/apollo.
 */
अटल काष्ठा kobj_attribute caps_start_attribute =
	__ATTR(caps_start, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute caps_stop_attribute =
	__ATTR(caps_stop, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute lang_attribute =
	__ATTR(lang, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute pitch_attribute =
	__ATTR(pitch, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute rate_attribute =
	__ATTR(rate, 0644, spk_var_show, spk_var_store);
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
	&lang_attribute.attr,
	&pitch_attribute.attr,
	&rate_attribute.attr,
	&voice_attribute.attr,
	&vol_attribute.attr,
	&delay_समय_attribute.attr,
	&direct_attribute.attr,
	&full_समय_attribute.attr,
	&jअगरfy_delta_attribute.attr,
	&trigger_समय_attribute.attr,
	शून्य,	/* need to शून्य terminate the list of attributes */
पूर्ण;

अटल काष्ठा spk_synth synth_apollo = अणु
	.name = "apollo",
	.version = DRV_VERSION,
	.दीर्घ_name = "Apollo",
	.init = "@R3@D0@K1\r",
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
	.catch_up = करो_catch_up,
	.flush = spk_synth_flush,
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
		.name = "apollo",
	पूर्ण,
पूर्ण;

अटल व्योम करो_catch_up(काष्ठा spk_synth *synth)
अणु
	u_अक्षर ch;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ jअगरf_max;
	काष्ठा var_t *jअगरfy_delta;
	काष्ठा var_t *delay_समय;
	काष्ठा var_t *full_समय;
	पूर्णांक full_समय_val = 0;
	पूर्णांक delay_समय_val = 0;
	पूर्णांक jअगरfy_delta_val = 0;

	jअगरfy_delta = spk_get_var(JIFFY);
	delay_समय = spk_get_var(DELAY);
	full_समय = spk_get_var(FULL);
	spin_lock_irqsave(&speakup_info.spinlock, flags);
	jअगरfy_delta_val = jअगरfy_delta->u.n.value;
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	jअगरf_max = jअगरfies + jअगरfy_delta_val;

	जबतक (!kthपढ़ो_should_stop()) अणु
		spin_lock_irqsave(&speakup_info.spinlock, flags);
		jअगरfy_delta_val = jअगरfy_delta->u.n.value;
		full_समय_val = full_समय->u.n.value;
		delay_समय_val = delay_समय->u.n.value;
		अगर (speakup_info.flushing) अणु
			speakup_info.flushing = 0;
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			synth->flush(synth);
			जारी;
		पूर्ण
		synth_buffer_skip_nonlatin1();
		अगर (synth_buffer_empty()) अणु
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			अवरोध;
		पूर्ण
		ch = synth_buffer_peek();
		set_current_state(TASK_INTERRUPTIBLE);
		full_समय_val = full_समय->u.n.value;
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		अगर (!synth->io_ops->synth_out(synth, ch)) अणु
			synth->io_ops->tiocmset(synth, 0, UART_MCR_RTS);
			synth->io_ops->tiocmset(synth, UART_MCR_RTS, 0);
			schedule_समयout(msecs_to_jअगरfies(full_समय_val));
			जारी;
		पूर्ण
		अगर (समय_after_eq(jअगरfies, jअगरf_max) && (ch == SPACE)) अणु
			spin_lock_irqsave(&speakup_info.spinlock, flags);
			jअगरfy_delta_val = jअगरfy_delta->u.n.value;
			full_समय_val = full_समय->u.n.value;
			delay_समय_val = delay_समय->u.n.value;
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			अगर (synth->io_ops->synth_out(synth, synth->procspeech))
				schedule_समयout(msecs_to_jअगरfies
						 (delay_समय_val));
			अन्यथा
				schedule_समयout(msecs_to_jअगरfies
						 (full_समय_val));
			jअगरf_max = jअगरfies + jअगरfy_delta_val;
		पूर्ण
		set_current_state(TASK_RUNNING);
		spin_lock_irqsave(&speakup_info.spinlock, flags);
		synth_buffer_अ_लो();
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	पूर्ण
	synth->io_ops->synth_out(synth, PROCSPEECH);
पूर्ण

module_param_named(ser, synth_apollo.ser, पूर्णांक, 0444);
module_param_named(dev, synth_apollo.dev_name, अक्षरp, 0444);
module_param_named(start, synth_apollo.startup, लघु, 0444);

MODULE_PARM_DESC(ser, "Set the serial port for the synthesizer (0-based).");
MODULE_PARM_DESC(dev, "Set the device e.g. ttyUSB0, for the synthesizer.");
MODULE_PARM_DESC(start, "Start the synthesizer once it is loaded.");

module_spk_synth(synth_apollo);

MODULE_AUTHOR("Kirk Reiser <kirk@braille.uwo.ca>");
MODULE_AUTHOR("David Borowski");
MODULE_DESCRIPTION("Speakup support for Apollo II synthesizer");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

