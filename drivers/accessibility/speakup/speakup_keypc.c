<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * written by David Borowski
 *
 * Copyright (C) 2003 David Borowski.
 *
 * specअगरicly written as a driver क्रम the speakup screenreview
 * package it's not a general device driver.
 * This driver is क्रम the Keynote Gold पूर्णांकernal synthesizer.
 */
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/serial_reg.h>

#समावेश "spk_priv.h"
#समावेश "speakup.h"

#घोषणा DRV_VERSION "2.10"
#घोषणा SYNTH_IO_EXTENT	0x04
#घोषणा SWAIT udelay(70)
#घोषणा PROCSPEECH 0x1f
#घोषणा SYNTH_CLEAR 0x03

अटल पूर्णांक synth_probe(काष्ठा spk_synth *synth);
अटल व्योम keynote_release(काष्ठा spk_synth *synth);
अटल स्थिर अक्षर *synth_immediate(काष्ठा spk_synth *synth, स्थिर अक्षर *buf);
अटल व्योम करो_catch_up(काष्ठा spk_synth *synth);
अटल व्योम synth_flush(काष्ठा spk_synth *synth);

अटल पूर्णांक synth_port;
अटल पूर्णांक port_क्रमced;
अटल अचिन्हित पूर्णांक synth_portlist[] = अणु 0x2a8, 0 पूर्ण;

अटल काष्ठा var_t vars[] = अणु
	अणु CAPS_START, .u.s = अणु"[f130]" पूर्ण पूर्ण,
	अणु CAPS_STOP, .u.s = अणु"[f90]" पूर्ण पूर्ण,
	अणु RATE, .u.n = अणु"\04%c ", 8, 0, 10, 81, -8, शून्य पूर्ण पूर्ण,
	अणु PITCH, .u.n = अणु"[f%d]", 5, 0, 9, 40, 10, शून्य पूर्ण पूर्ण,
	अणु सूचीECT, .u.n = अणुशून्य, 0, 0, 1, 0, 0, शून्य पूर्ण पूर्ण,
	V_LAST_VAR
पूर्ण;

/*
 * These attributes will appear in /sys/accessibility/speakup/keypc.
 */
अटल काष्ठा kobj_attribute caps_start_attribute =
	__ATTR(caps_start, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute caps_stop_attribute =
	__ATTR(caps_stop, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute pitch_attribute =
	__ATTR(pitch, 0644, spk_var_show, spk_var_store);
अटल काष्ठा kobj_attribute rate_attribute =
	__ATTR(rate, 0644, spk_var_show, spk_var_store);

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
	&rate_attribute.attr,
	&delay_समय_attribute.attr,
	&direct_attribute.attr,
	&full_समय_attribute.attr,
	&jअगरfy_delta_attribute.attr,
	&trigger_समय_attribute.attr,
	शून्य,	/* need to शून्य terminate the list of attributes */
पूर्ण;

अटल काष्ठा spk_synth synth_keypc = अणु
	.name = "keypc",
	.version = DRV_VERSION,
	.दीर्घ_name = "Keynote PC",
	.init = "[t][n7,1][n8,0]",
	.procspeech = PROCSPEECH,
	.clear = SYNTH_CLEAR,
	.delay = 500,
	.trigger = 50,
	.jअगरfies = 50,
	.full = 1000,
	.startup = SYNTH_START,
	.checkval = SYNTH_CHECK,
	.vars = vars,
	.io_ops = &spk_serial_io_ops,
	.probe = synth_probe,
	.release = keynote_release,
	.synth_immediate = synth_immediate,
	.catch_up = करो_catch_up,
	.flush = synth_flush,
	.is_alive = spk_synth_is_alive_nop,
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
		.name = "keypc",
	पूर्ण,
पूर्ण;

अटल अंतरभूत bool synth_writable(व्योम)
अणु
	वापस (inb_p(synth_port + UART_RX) & 0x10) != 0;
पूर्ण

अटल अंतरभूत bool synth_full(व्योम)
अणु
	वापस (inb_p(synth_port + UART_RX) & 0x80) == 0;
पूर्ण

अटल अक्षर *oops(व्योम)
अणु
	पूर्णांक s1, s2, s3, s4;

	s1 = inb_p(synth_port);
	s2 = inb_p(synth_port + 1);
	s3 = inb_p(synth_port + 2);
	s4 = inb_p(synth_port + 3);
	pr_warn("synth timeout %d %d %d %d\n", s1, s2, s3, s4);
	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *synth_immediate(काष्ठा spk_synth *synth, स्थिर अक्षर *buf)
अणु
	u_अक्षर ch;
	पूर्णांक समयout;

	जबतक ((ch = *buf)) अणु
		अगर (ch == '\n')
			ch = PROCSPEECH;
		अगर (synth_full())
			वापस buf;
		समयout = 1000;
		जबतक (synth_writable())
			अगर (--समयout <= 0)
				वापस oops();
		outb_p(ch, synth_port);
		udelay(70);
		buf++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम करो_catch_up(काष्ठा spk_synth *synth)
अणु
	u_अक्षर ch;
	पूर्णांक समयout;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ jअगरf_max;
	काष्ठा var_t *jअगरfy_delta;
	काष्ठा var_t *delay_समय;
	काष्ठा var_t *full_समय;
	पूर्णांक delay_समय_val;
	पूर्णांक full_समय_val;
	पूर्णांक jअगरfy_delta_val;

	jअगरfy_delta = spk_get_var(JIFFY);
	delay_समय = spk_get_var(DELAY);
	full_समय = spk_get_var(FULL);
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
		full_समय_val = full_समय->u.n.value;
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		अगर (synth_full()) अणु
			schedule_समयout(msecs_to_jअगरfies(full_समय_val));
			जारी;
		पूर्ण
		set_current_state(TASK_RUNNING);
		समयout = 1000;
		जबतक (synth_writable())
			अगर (--समयout <= 0)
				अवरोध;
		अगर (समयout <= 0) अणु
			oops();
			अवरोध;
		पूर्ण
		spin_lock_irqsave(&speakup_info.spinlock, flags);
		ch = synth_buffer_अ_लो();
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		अगर (ch == '\n')
			ch = PROCSPEECH;
		outb_p(ch, synth_port);
		SWAIT;
		अगर (समय_after_eq(jअगरfies, jअगरf_max) && (ch == SPACE)) अणु
			समयout = 1000;
			जबतक (synth_writable())
				अगर (--समयout <= 0)
					अवरोध;
			अगर (समयout <= 0) अणु
				oops();
				अवरोध;
			पूर्ण
			outb_p(PROCSPEECH, synth_port);
			spin_lock_irqsave(&speakup_info.spinlock, flags);
			jअगरfy_delta_val = jअगरfy_delta->u.n.value;
			delay_समय_val = delay_समय->u.n.value;
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			schedule_समयout(msecs_to_jअगरfies(delay_समय_val));
			jअगरf_max = jअगरfies + jअगरfy_delta_val;
		पूर्ण
	पूर्ण
	समयout = 1000;
	जबतक (synth_writable())
		अगर (--समयout <= 0)
			अवरोध;
	अगर (समयout <= 0)
		oops();
	अन्यथा
		outb_p(PROCSPEECH, synth_port);
पूर्ण

अटल व्योम synth_flush(काष्ठा spk_synth *synth)
अणु
	outb_p(SYNTH_CLEAR, synth_port);
पूर्ण

अटल पूर्णांक synth_probe(काष्ठा spk_synth *synth)
अणु
	अचिन्हित पूर्णांक port_val = 0;
	पूर्णांक i = 0;

	pr_info("Probing for %s.\n", synth->दीर्घ_name);
	अगर (port_क्रमced) अणु
		synth_port = port_क्रमced;
		pr_info("probe forced to %x by kernel command line\n",
			synth_port);
		अगर (synth_request_region(synth_port - 1, SYNTH_IO_EXTENT)) अणु
			pr_warn("sorry, port already reserved\n");
			वापस -EBUSY;
		पूर्ण
		port_val = inb(synth_port);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; synth_portlist[i]; i++) अणु
			अगर (synth_request_region(synth_portlist[i],
						 SYNTH_IO_EXTENT)) अणु
				pr_warn
				    ("request_region: failed with 0x%x, %d\n",
				     synth_portlist[i], SYNTH_IO_EXTENT);
				जारी;
			पूर्ण
			port_val = inb(synth_portlist[i]);
			अगर (port_val == 0x80) अणु
				synth_port = synth_portlist[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (port_val != 0x80) अणु
		pr_info("%s: not found\n", synth->दीर्घ_name);
		synth_release_region(synth_port, SYNTH_IO_EXTENT);
		synth_port = 0;
		वापस -ENODEV;
	पूर्ण
	pr_info("%s: %03x-%03x, driver version %s,\n", synth->दीर्घ_name,
		synth_port, synth_port + SYNTH_IO_EXTENT - 1,
		synth->version);
	synth->alive = 1;
	वापस 0;
पूर्ण

अटल व्योम keynote_release(काष्ठा spk_synth *synth)
अणु
	spk_stop_serial_पूर्णांकerrupt();
	अगर (synth_port)
		synth_release_region(synth_port, SYNTH_IO_EXTENT);
	synth_port = 0;
पूर्ण

module_param_hw_named(port, port_क्रमced, पूर्णांक, ioport, 0444);
module_param_named(start, synth_keypc.startup, लघु, 0444);

MODULE_PARM_DESC(port, "Set the port for the synthesizer (override probing).");
MODULE_PARM_DESC(start, "Start the synthesizer once it is loaded.");

module_spk_synth(synth_keypc);

MODULE_AUTHOR("David Borowski");
MODULE_DESCRIPTION("Speakup support for Keynote Gold PC synthesizers");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

