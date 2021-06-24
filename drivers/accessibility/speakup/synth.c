<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/प्रकार.स>	/* क्रम है_अंक() and मित्रs */
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>		/* क्रम verअगरy_area */
#समावेश <linux/त्रुटिसं.स>	/* क्रम -EBUSY */
#समावेश <linux/ioport.h>	/* क्रम check_region, request_region */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>	/* क्रम loops_per_sec */
#समावेश <linux/kmod.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/uaccess.h>	/* क्रम copy_from_user */
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "spk_priv.h"
#समावेश "speakup.h"
#समावेश "serialio.h"

अटल LIST_HEAD(synths);
काष्ठा spk_synth *synth;
अक्षर spk_pitch_buff[32] = "";
अटल पूर्णांक module_status;
bool spk_quiet_boot;

काष्ठा speakup_info_t speakup_info = अणु
	/*
	 * This spinlock is used to protect the entire speakup machinery, and
	 * must be taken at each kernel->speakup transition and released at
	 * each corresponding speakup->kernel transition.
	 *
	 * The progression thपढ़ो only पूर्णांकerferes with the speakup machinery
	 * through the synth buffer, so only needs to take the lock
	 * जबतक tinkering with the buffer.
	 *
	 * We use spin_lock/trylock_irqsave and spin_unlock_irqrestore with this
	 * spinlock because speakup needs to disable the keyboard IRQ.
	 */
	.spinlock = __SPIN_LOCK_UNLOCKED(speakup_info.spinlock),
	.flushing = 0,
पूर्ण;
EXPORT_SYMBOL_GPL(speakup_info);

अटल पूर्णांक करो_synth_init(काष्ठा spk_synth *in_synth);

/*
 * Main loop of the progression thपढ़ो: keep eating from the buffer
 * and push to the serial port, रुकोing as needed
 *
 * For devices that have a "full" notअगरication mechanism, the driver can
 * adapt the loop the way they prefer.
 */
अटल व्योम _spk_करो_catch_up(काष्ठा spk_synth *synth, पूर्णांक unicode)
अणु
	u16 ch;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ jअगरf_max;
	काष्ठा var_t *delay_समय;
	काष्ठा var_t *full_समय;
	काष्ठा var_t *jअगरfy_delta;
	पूर्णांक jअगरfy_delta_val;
	पूर्णांक delay_समय_val;
	पूर्णांक full_समय_val;
	पूर्णांक ret;

	jअगरfy_delta = spk_get_var(JIFFY);
	full_समय = spk_get_var(FULL);
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
		अगर (!unicode)
			synth_buffer_skip_nonlatin1();
		अगर (synth_buffer_empty()) अणु
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			अवरोध;
		पूर्ण
		ch = synth_buffer_peek();
		set_current_state(TASK_INTERRUPTIBLE);
		full_समय_val = full_समय->u.n.value;
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		अगर (ch == '\n')
			ch = synth->procspeech;
		अगर (unicode)
			ret = synth->io_ops->synth_out_unicode(synth, ch);
		अन्यथा
			ret = synth->io_ops->synth_out(synth, ch);
		अगर (!ret) अणु
			schedule_समयout(msecs_to_jअगरfies(full_समय_val));
			जारी;
		पूर्ण
		अगर (समय_after_eq(jअगरfies, jअगरf_max) && (ch == SPACE)) अणु
			spin_lock_irqsave(&speakup_info.spinlock, flags);
			jअगरfy_delta_val = jअगरfy_delta->u.n.value;
			delay_समय_val = delay_समय->u.n.value;
			full_समय_val = full_समय->u.n.value;
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
			अगर (synth->io_ops->synth_out(synth, synth->procspeech))
				schedule_समयout(
					msecs_to_jअगरfies(delay_समय_val));
			अन्यथा
				schedule_समयout(
					msecs_to_jअगरfies(full_समय_val));
			jअगरf_max = jअगरfies + jअगरfy_delta_val;
		पूर्ण
		set_current_state(TASK_RUNNING);
		spin_lock_irqsave(&speakup_info.spinlock, flags);
		synth_buffer_अ_लो();
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	पूर्ण
	synth->io_ops->synth_out(synth, synth->procspeech);
पूर्ण

व्योम spk_करो_catch_up(काष्ठा spk_synth *synth)
अणु
	_spk_करो_catch_up(synth, 0);
पूर्ण
EXPORT_SYMBOL_GPL(spk_करो_catch_up);

व्योम spk_करो_catch_up_unicode(काष्ठा spk_synth *synth)
अणु
	_spk_करो_catch_up(synth, 1);
पूर्ण
EXPORT_SYMBOL_GPL(spk_करो_catch_up_unicode);

व्योम spk_synth_flush(काष्ठा spk_synth *synth)
अणु
	synth->io_ops->flush_buffer(synth);
	synth->io_ops->synth_out(synth, synth->clear);
पूर्ण
EXPORT_SYMBOL_GPL(spk_synth_flush);

अचिन्हित अक्षर spk_synth_get_index(काष्ठा spk_synth *synth)
अणु
	वापस synth->io_ops->synth_in_noरुको(synth);
पूर्ण
EXPORT_SYMBOL_GPL(spk_synth_get_index);

पूर्णांक spk_synth_is_alive_nop(काष्ठा spk_synth *synth)
अणु
	synth->alive = 1;
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(spk_synth_is_alive_nop);

पूर्णांक spk_synth_is_alive_restart(काष्ठा spk_synth *synth)
अणु
	अगर (synth->alive)
		वापस 1;
	अगर (synth->io_ops->रुको_क्रम_xmitr(synth) > 0) अणु
		/* restart */
		synth->alive = 1;
		synth_म_लिखो("%s", synth->init);
		वापस 2; /* reenabled */
	पूर्ण
	pr_warn("%s: can't restart synth\n", synth->दीर्घ_name);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spk_synth_is_alive_restart);

अटल व्योम thपढ़ो_wake_up(काष्ठा समयr_list *unused)
अणु
	wake_up_पूर्णांकerruptible_all(&speakup_event);
पूर्ण

अटल DEFINE_TIMER(thपढ़ो_समयr, thपढ़ो_wake_up);

व्योम synth_start(व्योम)
अणु
	काष्ठा var_t *trigger_समय;

	अगर (!synth->alive) अणु
		synth_buffer_clear();
		वापस;
	पूर्ण
	trigger_समय = spk_get_var(TRIGGER);
	अगर (!समयr_pending(&thपढ़ो_समयr))
		mod_समयr(&thपढ़ो_समयr, jअगरfies +
			msecs_to_jअगरfies(trigger_समय->u.n.value));
पूर्ण

व्योम spk_करो_flush(व्योम)
अणु
	अगर (!synth)
		वापस;

	speakup_info.flushing = 1;
	synth_buffer_clear();
	अगर (synth->alive) अणु
		अगर (spk_pitch_shअगरt) अणु
			synth_म_लिखो("%s", spk_pitch_buff);
			spk_pitch_shअगरt = 0;
		पूर्ण
	पूर्ण
	wake_up_पूर्णांकerruptible_all(&speakup_event);
	wake_up_process(speakup_task);
पूर्ण

व्योम synth_ग_लिखो(स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	जबतक (count--)
		synth_buffer_add(*buf++);
	synth_start();
पूर्ण

व्योम synth_म_लिखो(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अचिन्हित अक्षर buf[160], *p;
	पूर्णांक r;

	बहु_शुरू(args, fmt);
	r = vsnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);
	अगर (r > माप(buf) - 1)
		r = माप(buf) - 1;

	p = buf;
	जबतक (r--)
		synth_buffer_add(*p++);
	synth_start();
पूर्ण
EXPORT_SYMBOL_GPL(synth_म_लिखो);

व्योम synth_putwc(u16 wc)
अणु
	synth_buffer_add(wc);
पूर्ण
EXPORT_SYMBOL_GPL(synth_putwc);

व्योम synth_putwc_s(u16 wc)
अणु
	synth_buffer_add(wc);
	synth_start();
पूर्ण
EXPORT_SYMBOL_GPL(synth_putwc_s);

व्योम synth_putws(स्थिर u16 *buf)
अणु
	स्थिर u16 *p;

	क्रम (p = buf; *p; p++)
		synth_buffer_add(*p);
पूर्ण
EXPORT_SYMBOL_GPL(synth_putws);

व्योम synth_putws_s(स्थिर u16 *buf)
अणु
	synth_putws(buf);
	synth_start();
पूर्ण
EXPORT_SYMBOL_GPL(synth_putws_s);

अटल पूर्णांक index_count;
अटल पूर्णांक sentence_count;

व्योम spk_reset_index_count(पूर्णांक sc)
अणु
	अटल पूर्णांक first = 1;

	अगर (first)
		first = 0;
	अन्यथा
		synth->get_index(synth);
	index_count = 0;
	sentence_count = sc;
पूर्ण

पूर्णांक synth_supports_indexing(व्योम)
अणु
	अगर (synth->get_index)
		वापस 1;
	वापस 0;
पूर्ण

व्योम synth_insert_next_index(पूर्णांक sent_num)
अणु
	पूर्णांक out;

	अगर (synth->alive) अणु
		अगर (sent_num == 0) अणु
			synth->indexing.currindex++;
			index_count++;
			अगर (synth->indexing.currindex >
					synth->indexing.highindex)
				synth->indexing.currindex =
					synth->indexing.lowindex;
		पूर्ण

		out = synth->indexing.currindex * 10 + sent_num;
		synth_म_लिखो(synth->indexing.command, out, out);
	पूर्ण
पूर्ण

व्योम spk_get_index_count(पूर्णांक *linecount, पूर्णांक *sentcount)
अणु
	पूर्णांक ind = synth->get_index(synth);

	अगर (ind) अणु
		sentence_count = ind % 10;

		अगर ((ind / 10) <= synth->indexing.currindex)
			index_count = synth->indexing.currindex - (ind / 10);
		अन्यथा
			index_count = synth->indexing.currindex
				- synth->indexing.lowindex
				+ synth->indexing.highindex - (ind / 10) + 1;
	पूर्ण
	*sentcount = sentence_count;
	*linecount = index_count;
पूर्ण

अटल काष्ठा resource synth_res;

पूर्णांक synth_request_region(अचिन्हित दीर्घ start, अचिन्हित दीर्घ n)
अणु
	काष्ठा resource *parent = &ioport_resource;

	स_रखो(&synth_res, 0, माप(synth_res));
	synth_res.name = synth->name;
	synth_res.start = start;
	synth_res.end = start + n - 1;
	synth_res.flags = IORESOURCE_BUSY;
	वापस request_resource(parent, &synth_res);
पूर्ण
EXPORT_SYMBOL_GPL(synth_request_region);

पूर्णांक synth_release_region(अचिन्हित दीर्घ start, अचिन्हित दीर्घ n)
अणु
	वापस release_resource(&synth_res);
पूर्ण
EXPORT_SYMBOL_GPL(synth_release_region);

काष्ठा var_t synth_समय_vars[] = अणु
	अणु DELAY, .u.n = अणुशून्य, 100, 100, 2000, 0, 0, शून्य पूर्ण पूर्ण,
	अणु TRIGGER, .u.n = अणुशून्य, 20, 10, 2000, 0, 0, शून्य पूर्ण पूर्ण,
	अणु JIFFY, .u.n = अणुशून्य, 50, 20, 200, 0, 0, शून्य पूर्ण पूर्ण,
	अणु FULL, .u.n = अणुशून्य, 400, 200, 60000, 0, 0, शून्य पूर्ण पूर्ण,
	अणु FLUSH, .u.n = अणुशून्य, 4000, 100, 4000, 0, 0, शून्य पूर्ण पूर्ण,
	V_LAST_VAR
पूर्ण;

/* called by: speakup_init() */
पूर्णांक synth_init(अक्षर *synth_name)
अणु
	पूर्णांक ret = 0;
	काष्ठा spk_synth *पंचांगp, *synth = शून्य;

	अगर (!synth_name)
		वापस 0;

	अगर (म_भेद(synth_name, "none") == 0) अणु
		mutex_lock(&spk_mutex);
		synth_release();
		mutex_unlock(&spk_mutex);
		वापस 0;
	पूर्ण

	mutex_lock(&spk_mutex);
	/* First, check अगर we alपढ़ोy have it loaded. */
	list_क्रम_each_entry(पंचांगp, &synths, node) अणु
		अगर (म_भेद(पंचांगp->name, synth_name) == 0)
			synth = पंचांगp;
	पूर्ण

	/* If we got one, initialize it now. */
	अगर (synth)
		ret = करो_synth_init(synth);
	अन्यथा
		ret = -ENODEV;
	mutex_unlock(&spk_mutex);

	वापस ret;
पूर्ण

/* called by: synth_add() */
अटल पूर्णांक करो_synth_init(काष्ठा spk_synth *in_synth)
अणु
	काष्ठा var_t *var;

	synth_release();
	अगर (in_synth->checkval != SYNTH_CHECK)
		वापस -EINVAL;
	synth = in_synth;
	synth->alive = 0;
	pr_warn("synth probe\n");
	अगर (synth->probe(synth) < 0) अणु
		pr_warn("%s: device probe failed\n", in_synth->name);
		synth = शून्य;
		वापस -ENODEV;
	पूर्ण
	synth_समय_vars[0].u.n.value =
		synth_समय_vars[0].u.n.शेष_val = synth->delay;
	synth_समय_vars[1].u.n.value =
		synth_समय_vars[1].u.n.शेष_val = synth->trigger;
	synth_समय_vars[2].u.n.value =
		synth_समय_vars[2].u.n.शेष_val = synth->jअगरfies;
	synth_समय_vars[3].u.n.value =
		synth_समय_vars[3].u.n.शेष_val = synth->full;
	synth_समय_vars[4].u.n.value =
		synth_समय_vars[4].u.n.शेष_val = synth->flush_समय;
	synth_म_लिखो("%s", synth->init);
	क्रम (var = synth->vars;
		(var->var_id >= 0) && (var->var_id < MAXVARS); var++)
		speakup_रेजिस्टर_var(var);
	अगर (!spk_quiet_boot)
		synth_म_लिखो("%s found\n", synth->दीर्घ_name);
	अगर (synth->attributes.name &&
	    sysfs_create_group(speakup_kobj, &synth->attributes) < 0)
		वापस -ENOMEM;
	synth_flags = synth->flags;
	wake_up_पूर्णांकerruptible_all(&speakup_event);
	अगर (speakup_task)
		wake_up_process(speakup_task);
	वापस 0;
पूर्ण

व्योम synth_release(व्योम)
अणु
	काष्ठा var_t *var;
	अचिन्हित दीर्घ flags;

	अगर (!synth)
		वापस;
	spin_lock_irqsave(&speakup_info.spinlock, flags);
	pr_info("releasing synth %s\n", synth->name);
	synth->alive = 0;
	del_समयr(&thपढ़ो_समयr);
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	अगर (synth->attributes.name)
		sysfs_हटाओ_group(speakup_kobj, &synth->attributes);
	क्रम (var = synth->vars; var->var_id != MAXVARS; var++)
		speakup_unरेजिस्टर_var(var->var_id);
	synth->release(synth);
	synth = शून्य;
पूर्ण

/* called by: all_driver_init() */
पूर्णांक synth_add(काष्ठा spk_synth *in_synth)
अणु
	पूर्णांक status = 0;
	काष्ठा spk_synth *पंचांगp;

	mutex_lock(&spk_mutex);

	list_क्रम_each_entry(पंचांगp, &synths, node) अणु
		अगर (पंचांगp == in_synth) अणु
			mutex_unlock(&spk_mutex);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (in_synth->startup)
		status = करो_synth_init(in_synth);

	अगर (!status)
		list_add_tail(&in_synth->node, &synths);

	mutex_unlock(&spk_mutex);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(synth_add);

व्योम synth_हटाओ(काष्ठा spk_synth *in_synth)
अणु
	mutex_lock(&spk_mutex);
	अगर (synth == in_synth)
		synth_release();
	list_del(&in_synth->node);
	module_status = 0;
	mutex_unlock(&spk_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(synth_हटाओ);

काष्ठा spk_synth *synth_current(व्योम)
अणु
	वापस synth;
पूर्ण
EXPORT_SYMBOL_GPL(synth_current);

लघु spk_punc_masks[] = अणु 0, SOME, MOST, PUNC, PUNC | B_SYM पूर्ण;
