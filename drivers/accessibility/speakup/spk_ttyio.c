<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/slab.h>

#समावेश "speakup.h"
#समावेश "spk_types.h"
#समावेश "spk_priv.h"

काष्ठा spk_ldisc_data अणु
	अक्षर buf;
	काष्ठा completion completion;
	bool buf_मुक्त;
	काष्ठा spk_synth *synth;
पूर्ण;

/*
 * This allows to catch within spk_ttyio_ldisc_खोलो whether it is getting set
 * on क्रम a speakup-driven device.
 */
अटल काष्ठा tty_काष्ठा *speakup_tty;
/* This mutex serializes the use of such global speakup_tty variable */
अटल DEFINE_MUTEX(speakup_tty_mutex);

अटल पूर्णांक ser_to_dev(पूर्णांक ser, dev_t *dev_no)
अणु
	अगर (ser < 0 || ser > (255 - 64)) अणु
		pr_err("speakup: Invalid ser param. Must be between 0 and 191 inclusive.\n");
		वापस -EINVAL;
	पूर्ण

	*dev_no = MKDEV(4, (64 + ser));
	वापस 0;
पूर्ण

अटल पूर्णांक get_dev_to_use(काष्ठा spk_synth *synth, dev_t *dev_no)
अणु
	/* use ser only when dev is not specअगरied */
	अगर (म_भेद(synth->dev_name, SYNTH_DEFAULT_DEV) ||
	    synth->ser == SYNTH_DEFAULT_SER)
		वापस tty_dev_name_to_number(synth->dev_name, dev_no);

	वापस ser_to_dev(synth->ser, dev_no);
पूर्ण

अटल पूर्णांक spk_ttyio_ldisc_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा spk_ldisc_data *ldisc_data;

	अगर (tty != speakup_tty)
		/* Somebody tried to use this line discipline outside speakup */
		वापस -ENODEV;

	अगर (!tty->ops->ग_लिखो)
		वापस -EOPNOTSUPP;

	ldisc_data = kदो_स्मृति(माप(*ldisc_data), GFP_KERNEL);
	अगर (!ldisc_data)
		वापस -ENOMEM;

	init_completion(&ldisc_data->completion);
	ldisc_data->buf_मुक्त = true;
	tty->disc_data = ldisc_data;

	वापस 0;
पूर्ण

अटल व्योम spk_ttyio_ldisc_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	kमुक्त(tty->disc_data);
पूर्ण

अटल पूर्णांक spk_ttyio_receive_buf2(काष्ठा tty_काष्ठा *tty,
				  स्थिर अचिन्हित अक्षर *cp, अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा spk_ldisc_data *ldisc_data = tty->disc_data;
	काष्ठा spk_synth *synth = ldisc_data->synth;

	अगर (synth->पढ़ो_buff_add) अणु
		पूर्णांक i;

		क्रम (i = 0; i < count; i++)
			synth->पढ़ो_buff_add(cp[i]);

		वापस count;
	पूर्ण

	अगर (!ldisc_data->buf_मुक्त)
		/* ttyio_in will tty_schedule_flip */
		वापस 0;

	/* Make sure the consumer has पढ़ो buf beक्रमe we have seen
	 * buf_मुक्त == true and overग_लिखो buf
	 */
	mb();

	ldisc_data->buf = cp[0];
	ldisc_data->buf_मुक्त = false;
	complete(&ldisc_data->completion);

	वापस 1;
पूर्ण

अटल काष्ठा tty_ldisc_ops spk_ttyio_ldisc_ops = अणु
	.owner          = THIS_MODULE,
	.name           = "speakup_ldisc",
	.खोलो           = spk_ttyio_ldisc_खोलो,
	.बंद          = spk_ttyio_ldisc_बंद,
	.receive_buf2	= spk_ttyio_receive_buf2,
पूर्ण;

अटल पूर्णांक spk_ttyio_out(काष्ठा spk_synth *in_synth, स्थिर अक्षर ch);
अटल पूर्णांक spk_ttyio_out_unicode(काष्ठा spk_synth *in_synth, u16 ch);
अटल व्योम spk_ttyio_send_xअक्षर(काष्ठा spk_synth *in_synth, अक्षर ch);
अटल व्योम spk_ttyio_tiocmset(काष्ठा spk_synth *in_synth, अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
अटल अचिन्हित अक्षर spk_ttyio_in(काष्ठा spk_synth *in_synth);
अटल अचिन्हित अक्षर spk_ttyio_in_noरुको(काष्ठा spk_synth *in_synth);
अटल व्योम spk_ttyio_flush_buffer(काष्ठा spk_synth *in_synth);
अटल पूर्णांक spk_ttyio_रुको_क्रम_xmitr(काष्ठा spk_synth *in_synth);

काष्ठा spk_io_ops spk_ttyio_ops = अणु
	.synth_out = spk_ttyio_out,
	.synth_out_unicode = spk_ttyio_out_unicode,
	.send_xअक्षर = spk_ttyio_send_xअक्षर,
	.tiocmset = spk_ttyio_tiocmset,
	.synth_in = spk_ttyio_in,
	.synth_in_noरुको = spk_ttyio_in_noरुको,
	.flush_buffer = spk_ttyio_flush_buffer,
	.रुको_क्रम_xmitr = spk_ttyio_रुको_क्रम_xmitr,
पूर्ण;
EXPORT_SYMBOL_GPL(spk_ttyio_ops);

अटल अंतरभूत व्योम get_termios(काष्ठा tty_काष्ठा *tty,
			       काष्ठा ktermios *out_termios)
अणु
	करोwn_पढ़ो(&tty->termios_rwsem);
	*out_termios = tty->termios;
	up_पढ़ो(&tty->termios_rwsem);
पूर्ण

अटल पूर्णांक spk_ttyio_initialise_ldisc(काष्ठा spk_synth *synth)
अणु
	पूर्णांक ret = 0;
	काष्ठा tty_काष्ठा *tty;
	काष्ठा ktermios पंचांगp_termios;
	dev_t dev;

	ret = get_dev_to_use(synth, &dev);
	अगर (ret)
		वापस ret;

	tty = tty_kखोलो_exclusive(dev);
	अगर (IS_ERR(tty))
		वापस PTR_ERR(tty);

	अगर (tty->ops->खोलो)
		ret = tty->ops->खोलो(tty, शून्य);
	अन्यथा
		ret = -ENODEV;

	अगर (ret) अणु
		tty_unlock(tty);
		वापस ret;
	पूर्ण

	clear_bit(TTY_HUPPED, &tty->flags);
	/* ensure hardware flow control is enabled */
	get_termios(tty, &पंचांगp_termios);
	अगर (!(पंचांगp_termios.c_cflag & CRTSCTS)) अणु
		पंचांगp_termios.c_cflag |= CRTSCTS;
		tty_set_termios(tty, &पंचांगp_termios);
		/*
		 * check c_cflag to see अगर it's updated as tty_set_termios
		 * may not वापस error even when no tty bits are
		 * changed by the request.
		 */
		get_termios(tty, &पंचांगp_termios);
		अगर (!(पंचांगp_termios.c_cflag & CRTSCTS))
			pr_warn("speakup: Failed to set hardware flow control\n");
	पूर्ण

	tty_unlock(tty);

	mutex_lock(&speakup_tty_mutex);
	speakup_tty = tty;
	ret = tty_set_ldisc(tty, N_SPEAKUP);
	speakup_tty = शून्य;
	mutex_unlock(&speakup_tty_mutex);

	अगर (!ret) अणु
		/* Success */
		काष्ठा spk_ldisc_data *ldisc_data = tty->disc_data;

		ldisc_data->synth = synth;
		synth->dev = tty;
		वापस 0;
	पूर्ण

	pr_err("speakup: Failed to set N_SPEAKUP on tty\n");

	tty_lock(tty);
	अगर (tty->ops->बंद)
		tty->ops->बंद(tty, शून्य);
	tty_unlock(tty);

	tty_kबंद(tty);

	वापस ret;
पूर्ण

व्योम spk_ttyio_रेजिस्टर_ldisc(व्योम)
अणु
	अगर (tty_रेजिस्टर_ldisc(N_SPEAKUP, &spk_ttyio_ldisc_ops))
		pr_warn("speakup: Error registering line discipline. Most synths won't work.\n");
पूर्ण

व्योम spk_ttyio_unरेजिस्टर_ldisc(व्योम)
अणु
	अगर (tty_unरेजिस्टर_ldisc(N_SPEAKUP))
		pr_warn("speakup: Couldn't unregister ldisc\n");
पूर्ण

अटल पूर्णांक spk_ttyio_out(काष्ठा spk_synth *in_synth, स्थिर अक्षर ch)
अणु
	काष्ठा tty_काष्ठा *tty = in_synth->dev;
	पूर्णांक ret;

	अगर (!in_synth->alive || !tty->ops->ग_लिखो)
		वापस 0;

	ret = tty->ops->ग_लिखो(tty, &ch, 1);

	अगर (ret == 0)
		/* No room */
		वापस 0;

	अगर (ret > 0)
		/* Success */
		वापस 1;

	pr_warn("%s: I/O error, deactivating speakup\n",
		in_synth->दीर्घ_name);
	/* No synth any more, so nobody will restart TTYs,
	 * and we thus need to करो it ourselves.  Now that there
	 * is no synth we can let application flood anyway
	 */
	in_synth->alive = 0;
	speakup_start_ttys();
	वापस 0;
पूर्ण

अटल पूर्णांक spk_ttyio_out_unicode(काष्ठा spk_synth *in_synth, u16 ch)
अणु
	पूर्णांक ret;

	अगर (ch < 0x80) अणु
		ret = spk_ttyio_out(in_synth, ch);
	पूर्ण अन्यथा अगर (ch < 0x800) अणु
		ret  = spk_ttyio_out(in_synth, 0xc0 | (ch >> 6));
		ret &= spk_ttyio_out(in_synth, 0x80 | (ch & 0x3f));
	पूर्ण अन्यथा अणु
		ret  = spk_ttyio_out(in_synth, 0xe0 | (ch >> 12));
		ret &= spk_ttyio_out(in_synth, 0x80 | ((ch >> 6) & 0x3f));
		ret &= spk_ttyio_out(in_synth, 0x80 | (ch & 0x3f));
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम spk_ttyio_send_xअक्षर(काष्ठा spk_synth *in_synth, अक्षर ch)
अणु
	काष्ठा tty_काष्ठा *tty = in_synth->dev;

	अगर (tty->ops->send_xअक्षर)
		tty->ops->send_xअक्षर(tty, ch);
पूर्ण

अटल व्योम spk_ttyio_tiocmset(काष्ठा spk_synth *in_synth, अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा tty_काष्ठा *tty = in_synth->dev;

	अगर (tty->ops->tiocmset)
		tty->ops->tiocmset(tty, set, clear);
पूर्ण

अटल पूर्णांक spk_ttyio_रुको_क्रम_xmitr(काष्ठा spk_synth *in_synth)
अणु
	वापस 1;
पूर्ण

अटल अचिन्हित अक्षर ttyio_in(काष्ठा spk_synth *in_synth, पूर्णांक समयout)
अणु
	काष्ठा tty_काष्ठा *tty = in_synth->dev;
	काष्ठा spk_ldisc_data *ldisc_data = tty->disc_data;
	अक्षर rv;

	अगर (!समयout) अणु
		अगर (!try_रुको_क्रम_completion(&ldisc_data->completion))
			वापस 0xff;
	पूर्ण अन्यथा अगर (रुको_क्रम_completion_समयout(&ldisc_data->completion,
					usecs_to_jअगरfies(समयout)) == 0) अणु
		pr_warn("spk_ttyio: timeout (%d)  while waiting for input\n",
			समयout);
		वापस 0xff;
	पूर्ण

	rv = ldisc_data->buf;
	/* Make sure we have पढ़ो buf beक्रमe we set buf_मुक्त to let
	 * the producer overग_लिखो it
	 */
	mb();
	ldisc_data->buf_मुक्त = true;
	/* Let TTY push more अक्षरacters */
	tty_schedule_flip(tty->port);

	वापस rv;
पूर्ण

अटल अचिन्हित अक्षर spk_ttyio_in(काष्ठा spk_synth *in_synth)
अणु
	वापस ttyio_in(in_synth, SPK_SYNTH_TIMEOUT);
पूर्ण

अटल अचिन्हित अक्षर spk_ttyio_in_noरुको(काष्ठा spk_synth *in_synth)
अणु
	u8 rv = ttyio_in(in_synth, 0);

	वापस (rv == 0xff) ? 0 : rv;
पूर्ण

अटल व्योम spk_ttyio_flush_buffer(काष्ठा spk_synth *in_synth)
अणु
	काष्ठा tty_काष्ठा *tty = in_synth->dev;

	अगर (tty->ops->flush_buffer)
		tty->ops->flush_buffer(tty);
पूर्ण

पूर्णांक spk_ttyio_synth_probe(काष्ठा spk_synth *synth)
अणु
	पूर्णांक rv = spk_ttyio_initialise_ldisc(synth);

	अगर (rv)
		वापस rv;

	synth->alive = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(spk_ttyio_synth_probe);

व्योम spk_ttyio_release(काष्ठा spk_synth *in_synth)
अणु
	काष्ठा tty_काष्ठा *tty = in_synth->dev;

	tty_lock(tty);

	अगर (tty->ops->बंद)
		tty->ops->बंद(tty, शून्य);

	tty_ldisc_flush(tty);
	tty_unlock(tty);
	tty_kबंद(tty);

	in_synth->dev = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(spk_ttyio_release);

स्थिर अक्षर *spk_ttyio_synth_immediate(काष्ठा spk_synth *in_synth, स्थिर अक्षर *buff)
अणु
	काष्ठा tty_काष्ठा *tty = in_synth->dev;
	u_अक्षर ch;

	जबतक ((ch = *buff)) अणु
		अगर (ch == '\n')
			ch = in_synth->procspeech;
		अगर (tty_ग_लिखो_room(tty) < 1 ||
		    !in_synth->io_ops->synth_out(in_synth, ch))
			वापस buff;
		buff++;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(spk_ttyio_synth_immediate);
