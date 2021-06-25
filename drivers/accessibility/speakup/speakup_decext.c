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
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "spk_priv.h"
#समावेश "speakup.h"

#घोषणा DRV_VERSION "2.14"
#घोषणा SYNTH_CLEAR 0x03
#घोषणा PROCSPEECH 0x0b

अटल अस्थिर अचिन्हित अक्षर last_अक्षर;

अटल व्योम पढ़ो_buff_add(u_अक्षर ch)
अणु
	last_अक्षर = ch;
पूर्ण

अटल अंतरभूत bool synth_full(व्योम)
अणु
	वापस last_अक्षर == 0x13;
पूर्ण

अटल व्योम करो_catch_up(काष्ठा spk_synth *synth);
अटल व्योम synth_flush(काष्ठा spk_synth *synth);

अटल पूर्णांक in_escape;

अटल काष्ठा var_t vars[] = अणु
	अणु CAPS_START, .u.s = अणु"[:dv ap 222]" पूर्ण पूर्ण,
	अणु CAPS_STOP, .u.s = अणु"[:dv ap 100]" पूर्ण पूर्ण,
	अणु RATE, .u.n = अणु"[:ra %d]", 7, 0, 9, 150, 25, शून्य पूर्ण पूर्ण,
	अणु PITCH, .u.n = अणु"[:dv ap %d]", 100, 0, 100, 0, 0, शून्य पूर्ण पूर्ण,
	अणु INFLECTION, .u.n = अणु"[:dv pr %d] ", 100, 0, 10000, 0, 0, शून्य पूर्ण पूर्ण,
	अणु VOL, .u.n = अणु"[:dv gv %d]", 13, 0, 16, 0, 5, शून्य पूर्ण पूर्ण,
	अणु PUNCT, .u.n = अणु"[:pu %c]", 0, 0, 2, 0, 0, "nsa" पूर्ण पूर्ण,
	अणु VOICE, .u.n = अणु"[:n%c]", 0, 0, 9, 0, 0, "phfdburwkv" पूर्ण पूर्ण,
	अणु सूचीECT, .u.n = अणुशून्य, 0, 0, 1, 0, 0, शून्य पूर्ण पूर्ण,
	V_LAST_VAR
पूर्ण;

/*
 * These attributes will appear in /sys/accessibility/speakup/decext.
 */
अटल काष्ठा kobj_attribute caps_start_attribute =
	__ATTR(caps_start, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute caps_stop_attribute =
	__ATTR(caps_stop, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute pitch_attribute =
	__ATTR(pitch, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute inflection_attribute =
	__ATTR(inflection, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute punct_attribute =
	__ATTR(punct, 0644, spk_var_show, spk_var_store);
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
	&pitch_attribute.attr,
	&inflection_attribute.attr,
	&punct_attribute.attr,
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

अटल काष्ठा spk_synth synth_decext = अणु
	.name = "decext",
	.version = DRV_VERSION,
	.दीर्घ_name = "Dectalk External",
	.init = "[:pe -380]",
	.procspeech = PROCSPEECH,
	.clear = SYNTH_CLEAR,
	.delay = 500,
	.trigger = 50,
	.jअगरfies = 50,
	.full = 40000,
	.flags = SF_DEC,
	.dev_name = SYNTH_DEFAULT_DEV,
	.startup = SYNTH_START,
	.checkval = SYNTH_CHECK,
	.vars = vars,
	.io_ops = &spk_ttyio_ops,
	.probe = spk_ttyio_synth_probe,
	.release = spk_ttyio_release,
	.synth_immediate = spk_ttyio_synth_immediate,
	.catch_up = करो_catch_up,
	.flush = synth_flush,
	.is_alive = spk_synth_is_alive_restart,
	.synth_adjust = शून्य,
	.पढ़ो_buff_add = पढ़ो_buff_add,
	.get_index = शून्य,
	.indexing = अणु
		.command = शून्य,
		.lowindex = 0,
		.highindex = 0,
		.currindex = 0,
	पूर्ण,
	.attributes = अणु
		.attrs = synth_attrs,
		.name = "decext",
	पूर्ण,
पूर्ण;

अटल व्योम करो_catch_up(काष्ठा spk_synth *synth)
अणु
	u_अक्षर ch;
	अटल u_अक्षर last = '\0';
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ jअगरf_max;
	काष्ठा var_t *jअगरfy_delta;
	काष्ठा var_t *delay_समय;
	पूर्णांक jअगरfy_delta_val = 0;
	पूर्णांक delay_समय_val = 0;

	jअगरfy_delta = spk_get_var(JIFFY);
	delay_समय = spk_get_var(DELAY);

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	jअगरfy_delta_val = jअगरfy_delta->u.n.value;
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	jअगरf_max = jअगरfies + jअगरfy_delta_val;

	जबतक (!kthपढ़ो_should_stop()) अणु
		spin_lock_irqsave(&speakup_info.spinlock, flags);
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
		delay_समय_val = delay_समय->u.n.value;
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		अगर (ch == '\n')
			ch = 0x0D;
		अगर (synth_full() || !synth->io_ops->synth_out(synth, ch)) अणु
			schedule_समयout(msecs_to_jअगरfies(delay_समय_val));
			जारी;
		पूर्ण
		set_current_state(TASK_RUNNING);
		spin_lock_irqsave(&speakup_info.spinlock, flags);
		synth_buffer_अ_लो();
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		अगर (ch == '[') अणु
			in_escape = 1;
		पूर्ण अन्यथा अगर (ch == ']') अणु
			in_escape = 0;
		पूर्ण अन्यथा अगर (ch <= SPACE) अणु
			अगर (!in_escape && म_अक्षर(",.!?;:", last))
				synth->io_ops->synth_out(synth, PROCSPEECH);
			अगर (समय_after_eq(jअगरfies, jअगरf_max)) अणु
				अगर (!in_escape)
					synth->io_ops->synth_out(synth,
								 PROCSPEECH);
				spin_lock_irqsave(&speakup_info.spinlock,
						  flags);
				jअगरfy_delta_val = jअगरfy_delta->u.n.value;
				delay_समय_val = delay_समय->u.n.value;
				spin_unlock_irqrestore(&speakup_info.spinlock,
						       flags);
				schedule_समयout(msecs_to_jअगरfies
						 (delay_समय_val));
				jअगरf_max = jअगरfies + jअगरfy_delta_val;
			पूर्ण
		पूर्ण
		last = ch;
	पूर्ण
	अगर (!in_escape)
		synth->io_ops->synth_out(synth, PROCSPEECH);
पूर्ण

अटल व्योम synth_flush(काष्ठा spk_synth *synth)
अणु
	in_escape = 0;
	synth->io_ops->flush_buffer(synth);
	synth->synth_immediate(synth, "\033P;10z\033\\");
पूर्ण

module_param_named(ser, synth_decext.ser, पूर्णांक, 0444);
module_param_named(dev, synth_decext.dev_name, अक्षरp, 0444);
module_param_named(start, synth_decext.startup, लघु, 0444);

MODULE_PARM_DESC(ser, "Set the serial port for the synthesizer (0-based).");
MODULE_PARM_DESC(dev, "Set the device e.g. ttyUSB0, for the synthesizer.");
MODULE_PARM_DESC(start, "Start the synthesizer once it is loaded.");

module_spk_synth(synth_decext);

MODULE_AUTHOR("Kirk Reiser <kirk@braille.uwo.ca>");
MODULE_AUTHOR("David Borowski");
MODULE_DESCRIPTION("Speakup support for DECtalk External synthesizers");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

