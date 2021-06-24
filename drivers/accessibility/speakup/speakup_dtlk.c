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
 * package it's not a general device driver.
 * This driver is क्रम the RC Systems DoubleTalk PC पूर्णांकernal synthesizer.
 */
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "spk_priv.h"
#समावेश "serialio.h"
#समावेश "speakup_dtlk.h" /* local header file क्रम DoubleTalk values */
#समावेश "speakup.h"

#घोषणा DRV_VERSION "2.10"
#घोषणा PROCSPEECH 0x00

अटल पूर्णांक synth_probe(काष्ठा spk_synth *synth);
अटल व्योम dtlk_release(काष्ठा spk_synth *synth);
अटल स्थिर अक्षर *synth_immediate(काष्ठा spk_synth *synth, स्थिर अक्षर *buf);
अटल व्योम करो_catch_up(काष्ठा spk_synth *synth);
अटल व्योम synth_flush(काष्ठा spk_synth *synth);

अटल पूर्णांक synth_lpc;
अटल पूर्णांक port_क्रमced;
अटल अचिन्हित पूर्णांक synth_portlist[] = अणु
		 0x25e, 0x29e, 0x2de, 0x31e, 0x35e, 0x39e, 0
पूर्ण;

अटल u_अक्षर synth_status;

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
 * These attributes will appear in /sys/accessibility/speakup/dtlk.
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

अटल काष्ठा spk_synth synth_dtlk = अणु
	.name = "dtlk",
	.version = DRV_VERSION,
	.दीर्घ_name = "DoubleTalk PC",
	.init = "\x01@\x01\x31y",
	.procspeech = PROCSPEECH,
	.clear = SYNTH_CLEAR,
	.delay = 500,
	.trigger = 30,
	.jअगरfies = 50,
	.full = 1000,
	.startup = SYNTH_START,
	.checkval = SYNTH_CHECK,
	.vars = vars,
	.io_ops = &spk_serial_io_ops,
	.probe = synth_probe,
	.release = dtlk_release,
	.synth_immediate = synth_immediate,
	.catch_up = करो_catch_up,
	.flush = synth_flush,
	.is_alive = spk_synth_is_alive_nop,
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
		.name = "dtlk",
	पूर्ण,
पूर्ण;

अटल अंतरभूत bool synth_पढ़ोable(व्योम)
अणु
	synth_status = inb_p(speakup_info.port_tts + UART_RX);
	वापस (synth_status & TTS_READABLE) != 0;
पूर्ण

अटल अंतरभूत bool synth_writable(व्योम)
अणु
	synth_status = inb_p(speakup_info.port_tts + UART_RX);
	वापस (synth_status & TTS_WRITABLE) != 0;
पूर्ण

अटल अंतरभूत bool synth_full(व्योम)
अणु
	synth_status = inb_p(speakup_info.port_tts + UART_RX);
	वापस (synth_status & TTS_ALMOST_FULL) != 0;
पूर्ण

अटल व्योम spk_out(स्थिर अक्षर ch)
अणु
	पूर्णांक समयout = SPK_XMITR_TIMEOUT;

	जबतक (!synth_writable()) अणु
		अगर (!--समयout)
			अवरोध;
		udelay(1);
	पूर्ण
	outb_p(ch, speakup_info.port_tts);
	समयout = SPK_XMITR_TIMEOUT;
	जबतक (synth_writable()) अणु
		अगर (!--समयout)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम करो_catch_up(काष्ठा spk_synth *synth)
अणु
	u_अक्षर ch;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ jअगरf_max;
	काष्ठा var_t *jअगरfy_delta;
	काष्ठा var_t *delay_समय;
	पूर्णांक jअगरfy_delta_val;
	पूर्णांक delay_समय_val;

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
		set_current_state(TASK_INTERRUPTIBLE);
		delay_समय_val = delay_समय->u.n.value;
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		अगर (synth_full()) अणु
			schedule_समयout(msecs_to_jअगरfies(delay_समय_val));
			जारी;
		पूर्ण
		set_current_state(TASK_RUNNING);
		spin_lock_irqsave(&speakup_info.spinlock, flags);
		ch = synth_buffer_अ_लो();
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		अगर (ch == '\n')
			ch = PROCSPEECH;
		spk_out(ch);
		अगर (समय_after_eq(jअगरfies, jअगरf_max) && (ch == SPACE)) अणु
			spk_out(PROCSPEECH);
			spin_lock_irqsave(&speakup_info.spinlock, flags);
			delay_समय_val = delay_समय->u.n.value;
			jअगरfy_delta_val = jअगरfy_delta->u.n.value;
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			schedule_समयout(msecs_to_jअगरfies(delay_समय_val));
			jअगरf_max = jअगरfies + jअगरfy_delta_val;
		पूर्ण
	पूर्ण
	spk_out(PROCSPEECH);
पूर्ण

अटल स्थिर अक्षर *synth_immediate(काष्ठा spk_synth *synth, स्थिर अक्षर *buf)
अणु
	u_अक्षर ch;

	जबतक ((ch = (u_अक्षर)*buf)) अणु
		अगर (synth_full())
			वापस buf;
		अगर (ch == '\n')
			ch = PROCSPEECH;
		spk_out(ch);
		buf++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम synth_flush(काष्ठा spk_synth *synth)
अणु
	outb_p(SYNTH_CLEAR, speakup_info.port_tts);
	जबतक (synth_writable())
		cpu_relax();
पूर्ण

अटल अक्षर synth_पढ़ो_tts(व्योम)
अणु
	u_अक्षर ch;

	जबतक (!synth_पढ़ोable())
		cpu_relax();
	ch = synth_status & 0x7f;
	outb_p(ch, speakup_info.port_tts);
	जबतक (synth_पढ़ोable())
		cpu_relax();
	वापस (अक्षर)ch;
पूर्ण

/* पूर्णांकerrogate the DoubleTalk PC and वापस its settings */
अटल काष्ठा synth_settings *synth_पूर्णांकerrogate(काष्ठा spk_synth *synth)
अणु
	u_अक्षर *t;
	अटल अक्षर buf[माप(काष्ठा synth_settings) + 1];
	पूर्णांक total, i;
	अटल काष्ठा synth_settings status;

	synth_immediate(synth, "\x18\x01?");
	क्रम (total = 0, i = 0; i < 50; i++) अणु
		buf[total] = synth_पढ़ो_tts();
		अगर (total > 2 && buf[total] == 0x7f)
			अवरोध;
		अगर (total < माप(काष्ठा synth_settings))
			total++;
	पूर्ण
	t = buf;
	/* serial number is little endian */
	status.serial_number = t[0] + t[1] * 256;
	t += 2;
	क्रम (i = 0; *t != '\r'; t++) अणु
		status.rom_version[i] = *t;
		अगर (i < माप(status.rom_version) - 1)
			i++;
	पूर्ण
	status.rom_version[i] = 0;
	t++;
	status.mode = *t++;
	status.punc_level = *t++;
	status.क्रमmant_freq = *t++;
	status.pitch = *t++;
	status.speed = *t++;
	status.volume = *t++;
	status.tone = *t++;
	status.expression = *t++;
	status.ext_dict_loaded = *t++;
	status.ext_dict_status = *t++;
	status.मुक्त_ram = *t++;
	status.articulation = *t++;
	status.reverb = *t++;
	status.eob = *t++;
	वापस &status;
पूर्ण

अटल पूर्णांक synth_probe(काष्ठा spk_synth *synth)
अणु
	अचिन्हित पूर्णांक port_val = 0;
	पूर्णांक i = 0;
	काष्ठा synth_settings *sp;

	pr_info("Probing for DoubleTalk.\n");
	अगर (port_क्रमced) अणु
		speakup_info.port_tts = port_क्रमced;
		pr_info("probe forced to %x by kernel command line\n",
			speakup_info.port_tts);
		अगर ((port_क्रमced & 0xf) != 0xf)
			pr_info("warning: port base should probably end with f\n");
		अगर (synth_request_region(speakup_info.port_tts - 1,
					 SYNTH_IO_EXTENT)) अणु
			pr_warn("sorry, port already reserved\n");
			वापस -EBUSY;
		पूर्ण
		port_val = inw(speakup_info.port_tts - 1);
		synth_lpc = speakup_info.port_tts - 1;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; synth_portlist[i]; i++) अणु
			अगर (synth_request_region(synth_portlist[i],
						 SYNTH_IO_EXTENT))
				जारी;
			port_val = inw(synth_portlist[i]) & 0xfbff;
			अगर (port_val == 0x107f) अणु
				synth_lpc = synth_portlist[i];
				speakup_info.port_tts = synth_lpc + 1;
				अवरोध;
			पूर्ण
			synth_release_region(synth_portlist[i],
					     SYNTH_IO_EXTENT);
		पूर्ण
	पूर्ण
	port_val &= 0xfbff;
	अगर (port_val != 0x107f) अणु
		pr_info("DoubleTalk PC: not found\n");
		अगर (synth_lpc)
			synth_release_region(synth_lpc, SYNTH_IO_EXTENT);
		वापस -ENODEV;
	पूर्ण
	जबतक (inw_p(synth_lpc) != 0x147f)
		cpu_relax(); /* रुको until it's पढ़ोy */
	sp = synth_पूर्णांकerrogate(synth);
	pr_info("%s: %03x-%03x, ROM ver %s, s/n %u, driver: %s\n",
		synth->दीर्घ_name, synth_lpc, synth_lpc + SYNTH_IO_EXTENT - 1,
		sp->rom_version, sp->serial_number, synth->version);
	synth->alive = 1;
	वापस 0;
पूर्ण

अटल व्योम dtlk_release(काष्ठा spk_synth *synth)
अणु
	spk_stop_serial_पूर्णांकerrupt();
	अगर (speakup_info.port_tts)
		synth_release_region(speakup_info.port_tts - 1,
				     SYNTH_IO_EXTENT);
	speakup_info.port_tts = 0;
पूर्ण

module_param_hw_named(port, port_क्रमced, पूर्णांक, ioport, 0444);
module_param_named(start, synth_dtlk.startup, लघु, 0444);

MODULE_PARM_DESC(port, "Set the port for the synthesizer (override probing).");
MODULE_PARM_DESC(start, "Start the synthesizer once it is loaded.");

module_spk_synth(synth_dtlk);

MODULE_AUTHOR("Kirk Reiser <kirk@braille.uwo.ca>");
MODULE_AUTHOR("David Borowski");
MODULE_DESCRIPTION("Speakup support for DoubleTalk PC synthesizers");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

