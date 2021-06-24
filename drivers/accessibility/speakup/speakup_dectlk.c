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
#समावेश <linux/unistd.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश "speakup.h"
#समावेश "spk_priv.h"

#घोषणा DRV_VERSION "2.20"
#घोषणा SYNTH_CLEAR 0x03
#घोषणा PROCSPEECH 0x0b
अटल पूर्णांक xoff;

अटल अंतरभूत पूर्णांक synth_full(व्योम)
अणु
	वापस xoff;
पूर्ण

अटल व्योम करो_catch_up(काष्ठा spk_synth *synth);
अटल व्योम synth_flush(काष्ठा spk_synth *synth);
अटल व्योम पढ़ो_buff_add(u_अक्षर c);
अटल अचिन्हित अक्षर get_index(काष्ठा spk_synth *synth);

अटल पूर्णांक in_escape;
अटल पूर्णांक is_flushing;

अटल DEFINE_SPINLOCK(flush_lock);
अटल DECLARE_WAIT_QUEUE_HEAD(flush);

अटल काष्ठा var_t vars[] = अणु
	अणु CAPS_START, .u.s = अणु"[:dv ap 160] " पूर्ण पूर्ण,
	अणु CAPS_STOP, .u.s = अणु"[:dv ap 100 ] " पूर्ण पूर्ण,
	अणु RATE, .u.n = अणु"[:ra %d] ", 180, 75, 650, 0, 0, शून्य पूर्ण पूर्ण,
	अणु INFLECTION, .u.n = अणु"[:dv pr %d] ", 100, 0, 10000, 0, 0, शून्य पूर्ण पूर्ण,
	अणु VOL, .u.n = अणु"[:dv g5 %d] ", 86, 60, 86, 0, 0, शून्य पूर्ण पूर्ण,
	अणु PUNCT, .u.n = अणु"[:pu %c] ", 0, 0, 2, 0, 0, "nsa" पूर्ण पूर्ण,
	अणु VOICE, .u.n = अणु"[:n%c] ", 0, 0, 9, 0, 0, "phfdburwkv" पूर्ण पूर्ण,
	अणु सूचीECT, .u.n = अणुशून्य, 0, 0, 1, 0, 0, शून्य पूर्ण पूर्ण,
	V_LAST_VAR
पूर्ण;

/*
 * These attributes will appear in /sys/accessibility/speakup/dectlk.
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
अटल काष्ठा kobj_attribute flush_समय_attribute =
	__ATTR(flush_समय, 0644, spk_var_show, spk_var_store);
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
	&flush_समय_attribute.attr,
	&jअगरfy_delta_attribute.attr,
	&trigger_समय_attribute.attr,
	शून्य,	/* need to शून्य terminate the list of attributes */
पूर्ण;

अटल पूर्णांक ap_शेषs[] = अणु122, 89, 155, 110, 208, 240, 200, 106, 306पूर्ण;
अटल पूर्णांक g5_शेषs[] = अणु86, 81, 86, 84, 81, 80, 83, 83, 73पूर्ण;

अटल काष्ठा spk_synth synth_dectlk = अणु
	.name = "dectlk",
	.version = DRV_VERSION,
	.दीर्घ_name = "Dectalk Express",
	.init = "[:error sp :name paul :rate 180 :tsr off] ",
	.procspeech = PROCSPEECH,
	.clear = SYNTH_CLEAR,
	.delay = 500,
	.trigger = 50,
	.jअगरfies = 50,
	.full = 40000,
	.flush_समय = 4000,
	.dev_name = SYNTH_DEFAULT_DEV,
	.startup = SYNTH_START,
	.checkval = SYNTH_CHECK,
	.vars = vars,
	.शेष_pitch = ap_शेषs,
	.शेष_vol = g5_शेषs,
	.io_ops = &spk_ttyio_ops,
	.probe = spk_ttyio_synth_probe,
	.release = spk_ttyio_release,
	.synth_immediate = spk_ttyio_synth_immediate,
	.catch_up = करो_catch_up,
	.flush = synth_flush,
	.is_alive = spk_synth_is_alive_restart,
	.synth_adjust = शून्य,
	.पढ़ो_buff_add = पढ़ो_buff_add,
	.get_index = get_index,
	.indexing = अणु
		.command = "[:in re %d ] ",
		.lowindex = 1,
		.highindex = 8,
		.currindex = 1,
	पूर्ण,
	.attributes = अणु
		.attrs = synth_attrs,
		.name = "dectlk",
	पूर्ण,
पूर्ण;

अटल पूर्णांक is_indnum(u_अक्षर *ch)
अणु
	अगर ((*ch >= '0') && (*ch <= '9')) अणु
		*ch = *ch - '0';
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल u_अक्षर lastind;

अटल अचिन्हित अक्षर get_index(काष्ठा spk_synth *synth)
अणु
	u_अक्षर rv;

	rv = lastind;
	lastind = 0;
	वापस rv;
पूर्ण

अटल व्योम पढ़ो_buff_add(u_अक्षर c)
अणु
	अटल पूर्णांक ind = -1;

	अगर (c == 0x01) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&flush_lock, flags);
		is_flushing = 0;
		wake_up_पूर्णांकerruptible(&flush);
		spin_unlock_irqrestore(&flush_lock, flags);
	पूर्ण अन्यथा अगर (c == 0x13) अणु
		xoff = 1;
	पूर्ण अन्यथा अगर (c == 0x11) अणु
		xoff = 0;
	पूर्ण अन्यथा अगर (is_indnum(&c)) अणु
		अगर (ind == -1)
			ind = c;
		अन्यथा
			ind = ind * 10 + c;
	पूर्ण अन्यथा अगर ((c > 31) && (c < 127)) अणु
		अगर (ind != -1)
			lastind = (u_अक्षर)ind;
		ind = -1;
	पूर्ण
पूर्ण

अटल व्योम करो_catch_up(काष्ठा spk_synth *synth)
अणु
	पूर्णांक synth_full_val = 0;
	अटल u_अक्षर ch;
	अटल u_अक्षर last = '\0';
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ jअगरf_max;
	अचिन्हित दीर्घ समयout;
	DEFINE_WAIT(रुको);
	काष्ठा var_t *jअगरfy_delta;
	काष्ठा var_t *delay_समय;
	काष्ठा var_t *flush_समय;
	पूर्णांक jअगरfy_delta_val;
	पूर्णांक delay_समय_val;
	पूर्णांक समयout_val;

	jअगरfy_delta = spk_get_var(JIFFY);
	delay_समय = spk_get_var(DELAY);
	flush_समय = spk_get_var(FLUSH);
	spin_lock_irqsave(&speakup_info.spinlock, flags);
	jअगरfy_delta_val = jअगरfy_delta->u.n.value;
	समयout_val = flush_समय->u.n.value;
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	समयout = msecs_to_jअगरfies(समयout_val);
	jअगरf_max = jअगरfies + jअगरfy_delta_val;

	जबतक (!kthपढ़ो_should_stop()) अणु
		/* अगर no ctl-a in 4, send data anyway */
		spin_lock_irqsave(&flush_lock, flags);
		जबतक (is_flushing && समयout) अणु
			prepare_to_रुको(&flush, &रुको, TASK_INTERRUPTIBLE);
			spin_unlock_irqrestore(&flush_lock, flags);
			समयout = schedule_समयout(समयout);
			spin_lock_irqsave(&flush_lock, flags);
		पूर्ण
		finish_रुको(&flush, &रुको);
		is_flushing = 0;
		spin_unlock_irqrestore(&flush_lock, flags);

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
		synth_full_val = synth_full();
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		अगर (ch == '\n')
			ch = 0x0D;
		अगर (synth_full_val || !synth->io_ops->synth_out(synth, ch)) अणु
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
	अगर (in_escape)
		/* अगर in command output ']' so we don't get an error */
		synth->io_ops->synth_out(synth, ']');
	in_escape = 0;
	is_flushing = 1;
	synth->io_ops->flush_buffer(synth);
	synth->io_ops->synth_out(synth, SYNTH_CLEAR);
पूर्ण

module_param_named(ser, synth_dectlk.ser, पूर्णांक, 0444);
module_param_named(dev, synth_dectlk.dev_name, अक्षरp, 0444);
module_param_named(start, synth_dectlk.startup, लघु, 0444);

MODULE_PARM_DESC(ser, "Set the serial port for the synthesizer (0-based).");
MODULE_PARM_DESC(dev, "Set the device e.g. ttyUSB0, for the synthesizer.");
MODULE_PARM_DESC(start, "Start the synthesizer once it is loaded.");

module_spk_synth(synth_dectlk);

MODULE_AUTHOR("Kirk Reiser <kirk@braille.uwo.ca>");
MODULE_AUTHOR("David Borowski");
MODULE_DESCRIPTION("Speakup support for DECtalk Express synthesizers");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

