<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* speakup_soft.c - speakup driver to रेजिस्टर and make available
 * a user space device क्रम software synthesizers.  written by: Kirk
 * Reiser <kirk@braille.uwo.ca>
 *
 * Copyright (C) 2003  Kirk Reiser.
 *
 * this code is specअगरicly written as a driver क्रम the speakup screenreview
 * package and is not a general device driver.
 */

#समावेश <linux/unistd.h>
#समावेश <linux/miscdevice.h>	/* क्रम misc_रेजिस्टर, and MISC_DYNAMIC_MINOR */
#समावेश <linux/poll.h>		/* क्रम poll_रुको() */

/* schedule(), संकेत_pending(), TASK_INTERRUPTIBLE */
#समावेश <linux/sched/संकेत.स>

#समावेश "spk_priv.h"
#समावेश "speakup.h"

#घोषणा DRV_VERSION "2.6"
#घोषणा PROCSPEECH 0x0d
#घोषणा CLEAR_SYNTH 0x18

अटल पूर्णांक softsynth_probe(काष्ठा spk_synth *synth);
अटल व्योम softsynth_release(काष्ठा spk_synth *synth);
अटल पूर्णांक softsynth_is_alive(काष्ठा spk_synth *synth);
अटल अचिन्हित अक्षर get_index(काष्ठा spk_synth *synth);

अटल काष्ठा miscdevice synth_device, synthu_device;
अटल पूर्णांक init_pos;
अटल पूर्णांक misc_रेजिस्टरed;

अटल काष्ठा var_t vars[] = अणु
	अणु CAPS_START, .u.s = अणु"\x01+3p" पूर्ण पूर्ण,
	अणु CAPS_STOP, .u.s = अणु"\x01-3p" पूर्ण पूर्ण,
	अणु PAUSE, .u.n = अणु"\x01P" पूर्ण पूर्ण,
	अणु RATE, .u.n = अणु"\x01%ds", 2, 0, 9, 0, 0, शून्य पूर्ण पूर्ण,
	अणु PITCH, .u.n = अणु"\x01%dp", 5, 0, 9, 0, 0, शून्य पूर्ण पूर्ण,
	अणु INFLECTION, .u.n = अणु"\x01%dr", 5, 0, 9, 0, 0, शून्य पूर्ण पूर्ण,
	अणु VOL, .u.n = अणु"\x01%dv", 5, 0, 9, 0, 0, शून्य पूर्ण पूर्ण,
	अणु TONE, .u.n = अणु"\x01%dx", 1, 0, 2, 0, 0, शून्य पूर्ण पूर्ण,
	अणु PUNCT, .u.n = अणु"\x01%db", 0, 0, 2, 0, 0, शून्य पूर्ण पूर्ण,
	अणु VOICE, .u.n = अणु"\x01%do", 0, 0, 7, 0, 0, शून्य पूर्ण पूर्ण,
	अणु FREQUENCY, .u.n = अणु"\x01%df", 5, 0, 9, 0, 0, शून्य पूर्ण पूर्ण,
	अणु सूचीECT, .u.n = अणुशून्य, 0, 0, 1, 0, 0, शून्य पूर्ण पूर्ण,
	V_LAST_VAR
पूर्ण;

/* These attributes will appear in /sys/accessibility/speakup/soft. */

अटल काष्ठा kobj_attribute caps_start_attribute =
	__ATTR(caps_start, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute caps_stop_attribute =
	__ATTR(caps_stop, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute freq_attribute =
	__ATTR(freq, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute pitch_attribute =
	__ATTR(pitch, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute inflection_attribute =
	__ATTR(inflection, 0644, spk_var_show, spk_var_store);
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

/*
 * We should uncomment the following definition, when we agree on a
 * method of passing a language designation to the software synthesizer.
 * अटल काष्ठा kobj_attribute lang_attribute =
 *	__ATTR(lang, 0644, spk_var_show, spk_var_store);
 */

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
/*	&lang_attribute.attr, */
	&pitch_attribute.attr,
	&inflection_attribute.attr,
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

अटल काष्ठा spk_synth synth_soft = अणु
	.name = "soft",
	.version = DRV_VERSION,
	.दीर्घ_name = "software synth",
	.init = "\01@\x01\x31y\n",
	.procspeech = PROCSPEECH,
	.delay = 0,
	.trigger = 0,
	.jअगरfies = 0,
	.full = 0,
	.startup = SYNTH_START,
	.checkval = SYNTH_CHECK,
	.vars = vars,
	.io_ops = शून्य,
	.probe = softsynth_probe,
	.release = softsynth_release,
	.synth_immediate = शून्य,
	.catch_up = शून्य,
	.flush = शून्य,
	.is_alive = softsynth_is_alive,
	.synth_adjust = शून्य,
	.पढ़ो_buff_add = शून्य,
	.get_index = get_index,
	.indexing = अणु
		.command = "\x01%di",
		.lowindex = 1,
		.highindex = 5,
		.currindex = 1,
	पूर्ण,
	.attributes = अणु
		.attrs = synth_attrs,
		.name = "soft",
	पूर्ण,
पूर्ण;

अटल अक्षर *get_initstring(व्योम)
अणु
	अटल अक्षर buf[40];
	अक्षर *cp;
	काष्ठा var_t *var;

	स_रखो(buf, 0, माप(buf));
	cp = buf;
	var = synth_soft.vars;
	जबतक (var->var_id != MAXVARS) अणु
		अगर (var->var_id != CAPS_START && var->var_id != CAPS_STOP &&
		    var->var_id != PAUSE && var->var_id != सूचीECT)
			cp = cp + प्र_लिखो(cp, var->u.n.synth_fmt,
					  var->u.n.value);
		var++;
	पूर्ण
	cp = cp + प्र_लिखो(cp, "\n");
	वापस buf;
पूर्ण

अटल पूर्णांक softsynth_खोलो(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	अचिन्हित दीर्घ flags;
	/*अगर ((fp->f_flags & O_ACCMODE) != O_RDONLY) */
	/*	वापस -EPERM; */
	spin_lock_irqsave(&speakup_info.spinlock, flags);
	अगर (synth_soft.alive) अणु
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		वापस -EBUSY;
	पूर्ण
	synth_soft.alive = 1;
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक softsynth_बंद(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	synth_soft.alive = 0;
	init_pos = 0;
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	/* Make sure we let applications go beक्रमe leaving */
	speakup_start_ttys();
	वापस 0;
पूर्ण

अटल sमाप_प्रकार softsynthx_पढ़ो(काष्ठा file *fp, अक्षर __user *buf, माप_प्रकार count,
			       loff_t *pos, पूर्णांक unicode)
अणु
	पूर्णांक अक्षरs_sent = 0;
	अक्षर __user *cp;
	अक्षर *init;
	माप_प्रकार bytes_per_ch = unicode ? 3 : 1;
	u16 ch;
	पूर्णांक empty;
	अचिन्हित दीर्घ flags;
	DEFINE_WAIT(रुको);

	अगर (count < bytes_per_ch)
		वापस -EINVAL;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	synth_soft.alive = 1;
	जबतक (1) अणु
		prepare_to_रुको(&speakup_event, &रुको, TASK_INTERRUPTIBLE);
		अगर (synth_current() == &synth_soft) अणु
			अगर (!unicode)
				synth_buffer_skip_nonlatin1();
			अगर (!synth_buffer_empty() || speakup_info.flushing)
				अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		अगर (fp->f_flags & O_NONBLOCK) अणु
			finish_रुको(&speakup_event, &रुको);
			वापस -EAGAIN;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			finish_रुको(&speakup_event, &रुको);
			वापस -ERESTARTSYS;
		पूर्ण
		schedule();
		spin_lock_irqsave(&speakup_info.spinlock, flags);
	पूर्ण
	finish_रुको(&speakup_event, &रुको);

	cp = buf;
	init = get_initstring();

	/* Keep 3 bytes available क्रम a 16bit UTF-8-encoded अक्षरacter */
	जबतक (अक्षरs_sent <= count - bytes_per_ch) अणु
		अगर (synth_current() != &synth_soft)
			अवरोध;
		अगर (speakup_info.flushing) अणु
			speakup_info.flushing = 0;
			ch = '\x18';
		पूर्ण अन्यथा अगर (init[init_pos]) अणु
			ch = init[init_pos++];
		पूर्ण अन्यथा अणु
			अगर (!unicode)
				synth_buffer_skip_nonlatin1();
			अगर (synth_buffer_empty())
				अवरोध;
			ch = synth_buffer_अ_लो();
		पूर्ण
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);

		अगर ((!unicode && ch < 0x100) || (unicode && ch < 0x80)) अणु
			u_अक्षर c = ch;

			अगर (copy_to_user(cp, &c, 1))
				वापस -EFAULT;

			अक्षरs_sent++;
			cp++;
		पूर्ण अन्यथा अगर (unicode && ch < 0x800) अणु
			u_अक्षर s[2] = अणु
				0xc0 | (ch >> 6),
				0x80 | (ch & 0x3f)
			पूर्ण;

			अगर (copy_to_user(cp, s, माप(s)))
				वापस -EFAULT;

			अक्षरs_sent += माप(s);
			cp += माप(s);
		पूर्ण अन्यथा अगर (unicode) अणु
			u_अक्षर s[3] = अणु
				0xe0 | (ch >> 12),
				0x80 | ((ch >> 6) & 0x3f),
				0x80 | (ch & 0x3f)
			पूर्ण;

			अगर (copy_to_user(cp, s, माप(s)))
				वापस -EFAULT;

			अक्षरs_sent += माप(s);
			cp += माप(s);
		पूर्ण

		spin_lock_irqsave(&speakup_info.spinlock, flags);
	पूर्ण
	*pos += अक्षरs_sent;
	empty = synth_buffer_empty();
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	अगर (empty) अणु
		speakup_start_ttys();
		*pos = 0;
	पूर्ण
	वापस अक्षरs_sent;
पूर्ण

अटल sमाप_प्रकार softsynth_पढ़ो(काष्ठा file *fp, अक्षर __user *buf, माप_प्रकार count,
			      loff_t *pos)
अणु
	वापस softsynthx_पढ़ो(fp, buf, count, pos, 0);
पूर्ण

अटल sमाप_प्रकार softsynthu_पढ़ो(काष्ठा file *fp, अक्षर __user *buf, माप_प्रकार count,
			       loff_t *pos)
अणु
	वापस softsynthx_पढ़ो(fp, buf, count, pos, 1);
पूर्ण

अटल पूर्णांक last_index;

अटल sमाप_प्रकार softsynth_ग_लिखो(काष्ठा file *fp, स्थिर अक्षर __user *buf,
			       माप_प्रकार count, loff_t *pos)
अणु
	अचिन्हित दीर्घ supplied_index = 0;
	पूर्णांक converted;

	converted = kम_से_अदीर्घ_from_user(buf, count, 0, &supplied_index);

	अगर (converted < 0)
		वापस converted;

	last_index = supplied_index;
	वापस count;
पूर्ण

अटल __poll_t softsynth_poll(काष्ठा file *fp, काष्ठा poll_table_काष्ठा *रुको)
अणु
	अचिन्हित दीर्घ flags;
	__poll_t ret = 0;

	poll_रुको(fp, &speakup_event, रुको);

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	अगर (synth_current() == &synth_soft &&
	    (!synth_buffer_empty() || speakup_info.flushing))
		ret = EPOLLIN | EPOLLRDNORM;
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	वापस ret;
पूर्ण

अटल अचिन्हित अक्षर get_index(काष्ठा spk_synth *synth)
अणु
	पूर्णांक rv;

	rv = last_index;
	last_index = 0;
	वापस rv;
पूर्ण

अटल स्थिर काष्ठा file_operations softsynth_fops = अणु
	.owner = THIS_MODULE,
	.poll = softsynth_poll,
	.पढ़ो = softsynth_पढ़ो,
	.ग_लिखो = softsynth_ग_लिखो,
	.खोलो = softsynth_खोलो,
	.release = softsynth_बंद,
पूर्ण;

अटल स्थिर काष्ठा file_operations softsynthu_fops = अणु
	.owner = THIS_MODULE,
	.poll = softsynth_poll,
	.पढ़ो = softsynthu_पढ़ो,
	.ग_लिखो = softsynth_ग_लिखो,
	.खोलो = softsynth_खोलो,
	.release = softsynth_बंद,
पूर्ण;

अटल पूर्णांक softsynth_probe(काष्ठा spk_synth *synth)
अणु
	अगर (misc_रेजिस्टरed != 0)
		वापस 0;
	स_रखो(&synth_device, 0, माप(synth_device));
	synth_device.minor = MISC_DYNAMIC_MINOR;
	synth_device.name = "softsynth";
	synth_device.fops = &softsynth_fops;
	अगर (misc_रेजिस्टर(&synth_device)) अणु
		pr_warn("Couldn't initialize miscdevice /dev/softsynth.\n");
		वापस -ENODEV;
	पूर्ण

	स_रखो(&synthu_device, 0, माप(synthu_device));
	synthu_device.minor = MISC_DYNAMIC_MINOR;
	synthu_device.name = "softsynthu";
	synthu_device.fops = &softsynthu_fops;
	अगर (misc_रेजिस्टर(&synthu_device)) अणु
		pr_warn("Couldn't initialize miscdevice /dev/softsynthu.\n");
		वापस -ENODEV;
	पूर्ण

	misc_रेजिस्टरed = 1;
	pr_info("initialized device: /dev/softsynth, node (MAJOR 10, MINOR %d)\n",
		synth_device.minor);
	pr_info("initialized device: /dev/softsynthu, node (MAJOR 10, MINOR %d)\n",
		synthu_device.minor);
	वापस 0;
पूर्ण

अटल व्योम softsynth_release(काष्ठा spk_synth *synth)
अणु
	misc_deरेजिस्टर(&synth_device);
	misc_deरेजिस्टर(&synthu_device);
	misc_रेजिस्टरed = 0;
	pr_info("unregistered /dev/softsynth\n");
	pr_info("unregistered /dev/softsynthu\n");
पूर्ण

अटल पूर्णांक softsynth_is_alive(काष्ठा spk_synth *synth)
अणु
	अगर (synth_soft.alive)
		वापस 1;
	वापस 0;
पूर्ण

module_param_named(start, synth_soft.startup, लघु, 0444);

MODULE_PARM_DESC(start, "Start the synthesizer once it is loaded.");

module_spk_synth(synth_soft);

MODULE_AUTHOR("Kirk Reiser <kirk@braille.uwo.ca>");
MODULE_DESCRIPTION("Speakup userspace software synthesizer support");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
