<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * This is the DECtalk PC speakup driver
 *
 * Some स्थिरants from DEC's DOS driver:
 *      Copyright (c) by Digital Equipment Corp.
 *
 * 386BSD DECtalk PC driver:
 *      Copyright (c) 1996 Brian Buhrow <buhrow@lothlorien.nfbcal.org>
 *
 * Linux DECtalk PC driver:
 *      Copyright (c) 1997 Nicolas Pitre <nico@cam.org>
 *
 * speakup DECtalk PC Internal driver:
 *      Copyright (c) 2003 David Borowski <david575@golden.net>
 *
 * All rights reserved.
 */
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "spk_priv.h"
#समावेश "speakup.h"

#घोषणा	MODULE_init		0x0dec	/* module in boot code */
#घोषणा	MODULE_self_test	0x8800	/* module in self-test */
#घोषणा	MODULE_reset		0xffff	/* reinit the whole module */

#घोषणा	MODE_mask		0xf000	/* mode bits in high nibble */
#घोषणा	MODE_null		0x0000
#घोषणा	MODE_test		0x2000	/* in testing mode */
#घोषणा	MODE_status		0x8000
#घोषणा	STAT_पूर्णांक		0x0001	/* running in पूर्णांकerrupt mode */
#घोषणा	STAT_tr_अक्षर		0x0002	/* अक्षरacter data to transmit */
#घोषणा	STAT_rr_अक्षर		0x0004	/* पढ़ोy to receive अक्षर data */
#घोषणा	STAT_cmd_पढ़ोy		0x0008	/* पढ़ोy to accept commands */
#घोषणा	STAT_dma_पढ़ोy		0x0010	/* dma command पढ़ोy */
#घोषणा	STAT_digitized		0x0020	/* spc in digitized mode */
#घोषणा	STAT_new_index		0x0040	/* new last index पढ़ोy */
#घोषणा	STAT_new_status		0x0080	/* new status posted */
#घोषणा	STAT_dma_state		0x0100	/* dma state toggle */
#घोषणा	STAT_index_valid	0x0200	/* indexs are valid */
#घोषणा	STAT_flushing		0x0400	/* flush in progress */
#घोषणा	STAT_self_test		0x0800	/* module in self test */
#घोषणा	MODE_पढ़ोy		0xc000	/* module पढ़ोy क्रम next phase */
#घोषणा	READY_boot		0x0000
#घोषणा	READY_kernel		0x0001
#घोषणा	MODE_error		0xf000

#घोषणा	CMD_mask		0xf000	/* mask क्रम command nibble */
#घोषणा	CMD_null		0x0000	/* post status */
#घोषणा	CMD_control		0x1000	/* hard control command */
#घोषणा	CTRL_mask		0x0F00	/* mask off control nibble */
#घोषणा	CTRL_data		0x00FF	/* mask to get data byte */
#घोषणा	CTRL_null		0x0000	/* null control */
#घोषणा	CTRL_vol_up		0x0100	/* increase volume */
#घोषणा	CTRL_vol_करोwn		0x0200	/* decrease volume */
#घोषणा	CTRL_vol_set		0x0300	/* set volume */
#घोषणा	CTRL_छोड़ो		0x0400	/* छोड़ो spc */
#घोषणा	CTRL_resume		0x0500	/* resume spc घड़ी */
#घोषणा	CTRL_resume_spc		0x0001	/* resume spc soft छोड़ो */
#घोषणा	CTRL_flush		0x0600	/* flush all buffers */
#घोषणा	CTRL_पूर्णांक_enable		0x0700	/* enable status change पूर्णांकs */
#घोषणा	CTRL_buff_मुक्त		0x0800	/* buffer reमुख्य count */
#घोषणा	CTRL_buff_used		0x0900	/* buffer in use */
#घोषणा	CTRL_speech		0x0a00	/* immediate speech change */
#घोषणा	CTRL_SP_voice		0x0001	/* voice change */
#घोषणा	CTRL_SP_rate		0x0002	/* rate change */
#घोषणा	CTRL_SP_comma		0x0003	/* comma छोड़ो change */
#घोषणा	CTRL_SP_period		0x0004	/* period छोड़ो change */
#घोषणा	CTRL_SP_rate_delta	0x0005	/* delta rate change */
#घोषणा	CTRL_SP_get_param	0x0006	/* वापस the desired parameter */
#घोषणा	CTRL_last_index		0x0b00	/* get last index spoken */
#घोषणा	CTRL_io_priority	0x0c00	/* change i/o priority */
#घोषणा	CTRL_मुक्त_mem		0x0d00	/* get मुक्त paragraphs on module */
#घोषणा	CTRL_get_lang		0x0e00	/* वापस biपंचांगask of loaded languages */
#घोषणा	CMD_test		0x2000	/* self-test request */
#घोषणा	TEST_mask		0x0F00	/* isolate test field */
#घोषणा	TEST_null		0x0000	/* no test requested */
#घोषणा	TEST_isa_पूर्णांक		0x0100	/* निश्चित isa irq */
#घोषणा	TEST_echo		0x0200	/* make data in == data out */
#घोषणा	TEST_seg		0x0300	/* set peek/poke segment */
#घोषणा	TEST_off		0x0400	/* set peek/poke offset */
#घोषणा	TEST_peek		0x0500	/* data out == *peek */
#घोषणा	TEST_poke		0x0600	/* *peek == data in */
#घोषणा	TEST_sub_code		0x00FF	/* user defined test sub codes */
#घोषणा	CMD_id			0x3000	/* वापस software id */
#घोषणा	ID_null			0x0000	/* null id */
#घोषणा	ID_kernel		0x0100	/* kernel code executing */
#घोषणा	ID_boot			0x0200	/* boot code executing */
#घोषणा	CMD_dma			0x4000	/* क्रमce a dma start */
#घोषणा	CMD_reset		0x5000	/* reset module status */
#घोषणा	CMD_sync		0x6000	/* kernel sync command */
#घोषणा	CMD_अक्षर_in		0x7000	/* single अक्षरacter send */
#घोषणा	CMD_अक्षर_out		0x8000	/* single अक्षरacter get */
#घोषणा	CHAR_count_1		0x0100	/* one अक्षर in cmd_low */
#घोषणा	CHAR_count_2		0x0200	/* the second in data_low */
#घोषणा	CHAR_count_3		0x0300	/* the third in data_high */
#घोषणा	CMD_spc_mode		0x9000	/* change spc mode */
#घोषणा	CMD_spc_to_text		0x0100	/* set to text mode */
#घोषणा	CMD_spc_to_digit	0x0200	/* set to digital mode */
#घोषणा	CMD_spc_rate		0x0400	/* change spc data rate */
#घोषणा	CMD_error		0xf000	/* severe error */

क्रमागत अणु	PRIMARY_DIC	= 0, USER_DIC, COMMAND_DIC, ABBREV_DIC पूर्ण;

#घोषणा	DMA_single_in		0x01
#घोषणा	DMA_single_out		0x02
#घोषणा	DMA_buff_in		0x03
#घोषणा	DMA_buff_out		0x04
#घोषणा	DMA_control		0x05
#घोषणा	DT_MEM_ALLOC		0x03
#घोषणा	DT_SET_DIC		0x04
#घोषणा	DT_START_TASK		0x05
#घोषणा	DT_LOAD_MEM		0x06
#घोषणा	DT_READ_MEM		0x07
#घोषणा	DT_DIGITAL_IN		0x08
#घोषणा	DMA_sync		0x06
#घोषणा	DMA_sync_अक्षर		0x07

#घोषणा DRV_VERSION "2.12"
#घोषणा PROCSPEECH 0x0b
#घोषणा SYNTH_IO_EXTENT 8

अटल पूर्णांक synth_probe(काष्ठा spk_synth *synth);
अटल व्योम dtpc_release(काष्ठा spk_synth *synth);
अटल स्थिर अक्षर *synth_immediate(काष्ठा spk_synth *synth, स्थिर अक्षर *buf);
अटल व्योम करो_catch_up(काष्ठा spk_synth *synth);
अटल व्योम synth_flush(काष्ठा spk_synth *synth);

अटल पूर्णांक synth_portlist[] = अणु 0x340, 0x350, 0x240, 0x250, 0 पूर्ण;
अटल पूर्णांक in_escape, is_flushing;
अटल पूर्णांक dt_stat, dma_state;

अटल काष्ठा var_t vars[] = अणु
	अणु CAPS_START, .u.s = अणु"[:dv ap 200]" पूर्ण पूर्ण,
	अणु CAPS_STOP, .u.s = अणु"[:dv ap 100]" पूर्ण पूर्ण,
	अणु RATE, .u.n = अणु"[:ra %d]", 9, 0, 18, 150, 25, शून्य पूर्ण पूर्ण,
	अणु PITCH, .u.n = अणु"[:dv ap %d]", 80, 0, 100, 20, 0, शून्य पूर्ण पूर्ण,
	अणु INFLECTION, .u.n = अणु"[:dv pr %d] ", 100, 0, 10000, 0, 0, शून्य पूर्ण पूर्ण,
	अणु VOL, .u.n = अणु"[:vo se %d]", 5, 0, 9, 5, 10, शून्य पूर्ण पूर्ण,
	अणु PUNCT, .u.n = अणु"[:pu %c]", 0, 0, 2, 0, 0, "nsa" पूर्ण पूर्ण,
	अणु VOICE, .u.n = अणु"[:n%c]", 0, 0, 9, 0, 0, "phfdburwkv" पूर्ण पूर्ण,
	अणु सूचीECT, .u.n = अणुशून्य, 0, 0, 1, 0, 0, शून्य पूर्ण पूर्ण,
	V_LAST_VAR
पूर्ण;

/*
 * These attributes will appear in /sys/accessibility/speakup/decpc.
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

अटल काष्ठा spk_synth synth_dec_pc = अणु
	.name = "decpc",
	.version = DRV_VERSION,
	.दीर्घ_name = "Dectalk PC",
	.init = "[:pe -380]",
	.procspeech = PROCSPEECH,
	.delay = 500,
	.trigger = 50,
	.jअगरfies = 50,
	.full = 1000,
	.flags = SF_DEC,
	.startup = SYNTH_START,
	.checkval = SYNTH_CHECK,
	.vars = vars,
	.io_ops = &spk_serial_io_ops,
	.probe = synth_probe,
	.release = dtpc_release,
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
		.name = "decpc",
	पूर्ण,
पूर्ण;

अटल पूर्णांक dt_माला_लोtatus(व्योम)
अणु
	dt_stat = inb_p(speakup_info.port_tts) |
		 (inb_p(speakup_info.port_tts + 1) << 8);
	वापस dt_stat;
पूर्ण

अटल व्योम dt_sendcmd(u_पूर्णांक cmd)
अणु
	outb_p(cmd & 0xFF, speakup_info.port_tts);
	outb_p((cmd >> 8) & 0xFF, speakup_info.port_tts + 1);
पूर्ण

अटल पूर्णांक dt_रुकोbit(पूर्णांक bit)
अणु
	पूर्णांक समयout = 100;

	जबतक (--समयout > 0) अणु
		अगर ((dt_माला_लोtatus() & bit) == bit)
			वापस 1;
		udelay(50);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dt_रुको_dma(व्योम)
अणु
	पूर्णांक समयout = 100, state = dma_state;

	अगर (!dt_रुकोbit(STAT_dma_पढ़ोy))
		वापस 0;
	जबतक (--समयout > 0) अणु
		अगर ((dt_माला_लोtatus() & STAT_dma_state) == state)
			वापस 1;
		udelay(50);
	पूर्ण
	dma_state = dt_माला_लोtatus() & STAT_dma_state;
	वापस 1;
पूर्ण

अटल पूर्णांक dt_ctrl(u_पूर्णांक cmd)
अणु
	पूर्णांक समयout = 10;

	अगर (!dt_रुकोbit(STAT_cmd_पढ़ोy))
		वापस -1;
	outb_p(0, speakup_info.port_tts + 2);
	outb_p(0, speakup_info.port_tts + 3);
	dt_माला_लोtatus();
	dt_sendcmd(CMD_control | cmd);
	outb_p(0, speakup_info.port_tts + 6);
	जबतक (dt_माला_लोtatus() & STAT_cmd_पढ़ोy) अणु
		udelay(20);
		अगर (--समयout == 0)
			अवरोध;
	पूर्ण
	dt_sendcmd(CMD_null);
	वापस 0;
पूर्ण

अटल व्योम synth_flush(काष्ठा spk_synth *synth)
अणु
	पूर्णांक समयout = 10;

	अगर (is_flushing)
		वापस;
	is_flushing = 4;
	in_escape = 0;
	जबतक (dt_ctrl(CTRL_flush)) अणु
		अगर (--समयout == 0)
			अवरोध;
		udelay(50);
	पूर्ण
	क्रम (समयout = 0; समयout < 10; समयout++) अणु
		अगर (dt_रुकोbit(STAT_dma_पढ़ोy))
			अवरोध;
		udelay(50);
	पूर्ण
	outb_p(DMA_sync, speakup_info.port_tts + 4);
	outb_p(0, speakup_info.port_tts + 4);
	udelay(100);
	क्रम (समयout = 0; समयout < 10; समयout++) अणु
		अगर (!(dt_माला_लोtatus() & STAT_flushing))
			अवरोध;
		udelay(50);
	पूर्ण
	dma_state = dt_माला_लोtatus() & STAT_dma_state;
	dma_state ^= STAT_dma_state;
	is_flushing = 0;
पूर्ण

अटल पूर्णांक dt_sendअक्षर(अक्षर ch)
अणु
	अगर (!dt_रुको_dma())
		वापस -1;
	अगर (!(dt_stat & STAT_rr_अक्षर))
		वापस -2;
	outb_p(DMA_single_in, speakup_info.port_tts + 4);
	outb_p(ch, speakup_info.port_tts + 4);
	dma_state ^= STAT_dma_state;
	वापस 0;
पूर्ण

अटल पूर्णांक testkernel(व्योम)
अणु
	पूर्णांक status = 0;

	अगर (dt_माला_लोtatus() == 0xffff) अणु
		status = -1;
		जाओ oops;
	पूर्ण
	dt_sendcmd(CMD_sync);
	अगर (!dt_रुकोbit(STAT_cmd_पढ़ोy))
		status = -2;
	अन्यथा अगर (dt_stat & 0x8000)
		वापस 0;
	अन्यथा अगर (dt_stat == 0x0dec)
		pr_warn("dec_pc at 0x%x, software not loaded\n",
			speakup_info.port_tts);
	status = -3;
oops:	synth_release_region(speakup_info.port_tts, SYNTH_IO_EXTENT);
	speakup_info.port_tts = 0;
	वापस status;
पूर्ण

अटल व्योम करो_catch_up(काष्ठा spk_synth *synth)
अणु
	u_अक्षर ch;
	अटल u_अक्षर last;
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
		ch = synth_buffer_peek();
		set_current_state(TASK_INTERRUPTIBLE);
		delay_समय_val = delay_समय->u.n.value;
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		अगर (ch == '\n')
			ch = 0x0D;
		अगर (dt_sendअक्षर(ch)) अणु
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
				dt_sendअक्षर(PROCSPEECH);
			अगर (समय_after_eq(jअगरfies, jअगरf_max)) अणु
				अगर (!in_escape)
					dt_sendअक्षर(PROCSPEECH);
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
		ch = 0;
	पूर्ण
	अगर (!in_escape)
		dt_sendअक्षर(PROCSPEECH);
पूर्ण

अटल स्थिर अक्षर *synth_immediate(काष्ठा spk_synth *synth, स्थिर अक्षर *buf)
अणु
	u_अक्षर ch;

	जबतक ((ch = *buf)) अणु
		अगर (ch == '\n')
			ch = PROCSPEECH;
		अगर (dt_sendअक्षर(ch))
			वापस buf;
		buf++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक synth_probe(काष्ठा spk_synth *synth)
अणु
	पूर्णांक i = 0, failed = 0;

	pr_info("Probing for %s.\n", synth->दीर्घ_name);
	क्रम (i = 0; synth_portlist[i]; i++) अणु
		अगर (synth_request_region(synth_portlist[i], SYNTH_IO_EXTENT)) अणु
			pr_warn("request_region: failed with 0x%x, %d\n",
				synth_portlist[i], SYNTH_IO_EXTENT);
			जारी;
		पूर्ण
		speakup_info.port_tts = synth_portlist[i];
		failed = testkernel();
		अगर (failed == 0)
			अवरोध;
	पूर्ण
	अगर (failed) अणु
		pr_info("%s: not found\n", synth->दीर्घ_name);
		वापस -ENODEV;
	पूर्ण
	pr_info("%s: %03x-%03x, Driver Version %s,\n", synth->दीर्घ_name,
		speakup_info.port_tts, speakup_info.port_tts + 7,
		synth->version);
	synth->alive = 1;
	वापस 0;
पूर्ण

अटल व्योम dtpc_release(काष्ठा spk_synth *synth)
अणु
	spk_stop_serial_पूर्णांकerrupt();
	अगर (speakup_info.port_tts)
		synth_release_region(speakup_info.port_tts, SYNTH_IO_EXTENT);
	speakup_info.port_tts = 0;
पूर्ण

module_param_named(start, synth_dec_pc.startup, लघु, 0444);

MODULE_PARM_DESC(start, "Start the synthesizer once it is loaded.");

module_spk_synth(synth_dec_pc);

MODULE_AUTHOR("Kirk Reiser <kirk@braille.uwo.ca>");
MODULE_AUTHOR("David Borowski");
MODULE_DESCRIPTION("Speakup support for DECtalk PC synthesizers");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
