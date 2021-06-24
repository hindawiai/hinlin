<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    SCLP line mode terminal driver.
 *
 *  S390 version
 *    Copyright IBM Corp. 1999
 *    Author(s): Martin Peschke <mpeschke@de.ibm.com>
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/kmod.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gfp.h>
#समावेश <linux/uaccess.h>

#समावेश "ctrlchar.h"
#समावेश "sclp.h"
#समावेश "sclp_rw.h"
#समावेश "sclp_tty.h"

/*
 * size of a buffer that collects single अक्षरacters coming in
 * via sclp_tty_put_अक्षर()
 */
#घोषणा SCLP_TTY_BUF_SIZE 512

/*
 * There is exactly one SCLP terminal, so we can keep things simple
 * and allocate all variables अटलally.
 */

/* Lock to guard over changes to global variables. */
अटल DEFINE_SPINLOCK(sclp_tty_lock);
/* List of मुक्त pages that can be used क्रम console output buffering. */
अटल LIST_HEAD(sclp_tty_pages);
/* List of full काष्ठा sclp_buffer काष्ठाures पढ़ोy क्रम output. */
अटल LIST_HEAD(sclp_tty_outqueue);
/* Counter how many buffers are emitted. */
अटल पूर्णांक sclp_tty_buffer_count;
/* Poपूर्णांकer to current console buffer. */
अटल काष्ठा sclp_buffer *sclp_ttybuf;
/* Timer क्रम delayed output of console messages. */
अटल काष्ठा समयr_list sclp_tty_समयr;

अटल काष्ठा tty_port sclp_port;
अटल अचिन्हित अक्षर sclp_tty_अक्षरs[SCLP_TTY_BUF_SIZE];
अटल अचिन्हित लघु पूर्णांक sclp_tty_अक्षरs_count;

काष्ठा tty_driver *sclp_tty_driver;

अटल पूर्णांक sclp_tty_छोटे;

#घोषणा SCLP_TTY_COLUMNS 320
#घोषणा SPACES_PER_TAB 8
#घोषणा CASE_DELIMITER 0x6c /* to separate upper and lower हाल (% in EBCDIC) */

/* This routine is called whenever we try to खोलो a SCLP terminal. */
अटल पूर्णांक
sclp_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	tty_port_tty_set(&sclp_port, tty);
	tty->driver_data = शून्य;
	वापस 0;
पूर्ण

/* This routine is called when the SCLP terminal is बंदd. */
अटल व्योम
sclp_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	अगर (tty->count > 1)
		वापस;
	tty_port_tty_set(&sclp_port, शून्य);
पूर्ण

/*
 * This routine वापसs the numbers of अक्षरacters the tty driver
 * will accept क्रम queuing to be written.  This number is subject
 * to change as output buffers get emptied, or अगर the output flow
 * control is acted. This is not an exact number because not every
 * अक्षरacter needs the same space in the sccb. The worst हाल is
 * a string of newlines. Every newline creates a new message which
 * needs 82 bytes.
 */
अटल पूर्णांक
sclp_tty_ग_लिखो_room (काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *l;
	पूर्णांक count;

	spin_lock_irqsave(&sclp_tty_lock, flags);
	count = 0;
	अगर (sclp_ttybuf != शून्य)
		count = sclp_buffer_space(sclp_ttybuf) / माप(काष्ठा msg_buf);
	list_क्रम_each(l, &sclp_tty_pages)
		count += NR_EMPTY_MSG_PER_SCCB;
	spin_unlock_irqrestore(&sclp_tty_lock, flags);
	वापस count;
पूर्ण

अटल व्योम
sclp_ttybuf_callback(काष्ठा sclp_buffer *buffer, पूर्णांक rc)
अणु
	अचिन्हित दीर्घ flags;
	व्योम *page;

	करो अणु
		page = sclp_unmake_buffer(buffer);
		spin_lock_irqsave(&sclp_tty_lock, flags);
		/* Remove buffer from outqueue */
		list_del(&buffer->list);
		sclp_tty_buffer_count--;
		list_add_tail((काष्ठा list_head *) page, &sclp_tty_pages);
		/* Check अगर there is a pending buffer on the out queue. */
		buffer = शून्य;
		अगर (!list_empty(&sclp_tty_outqueue))
			buffer = list_entry(sclp_tty_outqueue.next,
					    काष्ठा sclp_buffer, list);
		spin_unlock_irqrestore(&sclp_tty_lock, flags);
	पूर्ण जबतक (buffer && sclp_emit_buffer(buffer, sclp_ttybuf_callback));

	tty_port_tty_wakeup(&sclp_port);
पूर्ण

अटल अंतरभूत व्योम
__sclp_ttybuf_emit(काष्ठा sclp_buffer *buffer)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक count;
	पूर्णांक rc;

	spin_lock_irqsave(&sclp_tty_lock, flags);
	list_add_tail(&buffer->list, &sclp_tty_outqueue);
	count = sclp_tty_buffer_count++;
	spin_unlock_irqrestore(&sclp_tty_lock, flags);
	अगर (count)
		वापस;
	rc = sclp_emit_buffer(buffer, sclp_ttybuf_callback);
	अगर (rc)
		sclp_ttybuf_callback(buffer, rc);
पूर्ण

/*
 * When this routine is called from the समयr then we flush the
 * temporary ग_लिखो buffer.
 */
अटल व्योम
sclp_tty_समयout(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sclp_buffer *buf;

	spin_lock_irqsave(&sclp_tty_lock, flags);
	buf = sclp_ttybuf;
	sclp_ttybuf = शून्य;
	spin_unlock_irqrestore(&sclp_tty_lock, flags);

	अगर (buf != शून्य) अणु
		__sclp_ttybuf_emit(buf);
	पूर्ण
पूर्ण

/*
 * Write a string to the sclp tty.
 */
अटल पूर्णांक sclp_tty_ग_लिखो_string(स्थिर अचिन्हित अक्षर *str, पूर्णांक count, पूर्णांक may_fail)
अणु
	अचिन्हित दीर्घ flags;
	व्योम *page;
	पूर्णांक written;
	पूर्णांक overall_written;
	काष्ठा sclp_buffer *buf;

	अगर (count <= 0)
		वापस 0;
	overall_written = 0;
	spin_lock_irqsave(&sclp_tty_lock, flags);
	करो अणु
		/* Create a sclp output buffer अगर none exists yet */
		अगर (sclp_ttybuf == शून्य) अणु
			जबतक (list_empty(&sclp_tty_pages)) अणु
				spin_unlock_irqrestore(&sclp_tty_lock, flags);
				अगर (may_fail)
					जाओ out;
				अन्यथा
					sclp_sync_रुको();
				spin_lock_irqsave(&sclp_tty_lock, flags);
			पूर्ण
			page = sclp_tty_pages.next;
			list_del((काष्ठा list_head *) page);
			sclp_ttybuf = sclp_make_buffer(page, SCLP_TTY_COLUMNS,
						       SPACES_PER_TAB);
		पूर्ण
		/* try to ग_लिखो the string to the current output buffer */
		written = sclp_ग_लिखो(sclp_ttybuf, str, count);
		overall_written += written;
		अगर (written == count)
			अवरोध;
		/*
		 * Not all अक्षरacters could be written to the current
		 * output buffer. Emit the buffer, create a new buffer
		 * and then output the rest of the string.
		 */
		buf = sclp_ttybuf;
		sclp_ttybuf = शून्य;
		spin_unlock_irqrestore(&sclp_tty_lock, flags);
		__sclp_ttybuf_emit(buf);
		spin_lock_irqsave(&sclp_tty_lock, flags);
		str += written;
		count -= written;
	पूर्ण जबतक (count > 0);
	/* Setup समयr to output current console buffer after 1/10 second */
	अगर (sclp_ttybuf && sclp_अक्षरs_in_buffer(sclp_ttybuf) &&
	    !समयr_pending(&sclp_tty_समयr)) अणु
		mod_समयr(&sclp_tty_समयr, jअगरfies + HZ / 10);
	पूर्ण
	spin_unlock_irqrestore(&sclp_tty_lock, flags);
out:
	वापस overall_written;
पूर्ण

/*
 * This routine is called by the kernel to ग_लिखो a series of अक्षरacters to the
 * tty device. The अक्षरacters may come from user space or kernel space. This
 * routine will वापस the number of अक्षरacters actually accepted क्रम writing.
 */
अटल पूर्णांक
sclp_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	अगर (sclp_tty_अक्षरs_count > 0) अणु
		sclp_tty_ग_लिखो_string(sclp_tty_अक्षरs, sclp_tty_अक्षरs_count, 0);
		sclp_tty_अक्षरs_count = 0;
	पूर्ण
	वापस sclp_tty_ग_लिखो_string(buf, count, 1);
पूर्ण

/*
 * This routine is called by the kernel to ग_लिखो a single अक्षरacter to the tty
 * device. If the kernel uses this routine, it must call the flush_अक्षरs()
 * routine (अगर defined) when it is करोne stuffing अक्षरacters पूर्णांकo the driver.
 *
 * Characters provided to sclp_tty_put_अक्षर() are buffered by the SCLP driver.
 * If the given अक्षरacter is a '\n' the contents of the SCLP ग_लिखो buffer
 * - including previous अक्षरacters from sclp_tty_put_अक्षर() and strings from
 * sclp_ग_लिखो() without final '\n' - will be written.
 */
अटल पूर्णांक
sclp_tty_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	sclp_tty_अक्षरs[sclp_tty_अक्षरs_count++] = ch;
	अगर (ch == '\n' || sclp_tty_अक्षरs_count >= SCLP_TTY_BUF_SIZE) अणु
		sclp_tty_ग_लिखो_string(sclp_tty_अक्षरs, sclp_tty_अक्षरs_count, 0);
		sclp_tty_अक्षरs_count = 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * This routine is called by the kernel after it has written a series of
 * अक्षरacters to the tty device using put_अक्षर().
 */
अटल व्योम
sclp_tty_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (sclp_tty_अक्षरs_count > 0) अणु
		sclp_tty_ग_लिखो_string(sclp_tty_अक्षरs, sclp_tty_अक्षरs_count, 0);
		sclp_tty_अक्षरs_count = 0;
	पूर्ण
पूर्ण

/*
 * This routine वापसs the number of अक्षरacters in the ग_लिखो buffer of the
 * SCLP driver. The provided number includes all अक्षरacters that are stored
 * in the SCCB (will be written next समय the SCLP is not busy) as well as
 * अक्षरacters in the ग_लिखो buffer (will not be written as दीर्घ as there is a
 * final line feed missing).
 */
अटल पूर्णांक
sclp_tty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *l;
	काष्ठा sclp_buffer *t;
	पूर्णांक count;

	spin_lock_irqsave(&sclp_tty_lock, flags);
	count = 0;
	अगर (sclp_ttybuf != शून्य)
		count = sclp_अक्षरs_in_buffer(sclp_ttybuf);
	list_क्रम_each(l, &sclp_tty_outqueue) अणु
		t = list_entry(l, काष्ठा sclp_buffer, list);
		count += sclp_अक्षरs_in_buffer(t);
	पूर्ण
	spin_unlock_irqrestore(&sclp_tty_lock, flags);
	वापस count;
पूर्ण

/*
 * हटाओs all content from buffers of low level driver
 */
अटल व्योम
sclp_tty_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (sclp_tty_अक्षरs_count > 0) अणु
		sclp_tty_ग_लिखो_string(sclp_tty_अक्षरs, sclp_tty_अक्षरs_count, 0);
		sclp_tty_अक्षरs_count = 0;
	पूर्ण
पूर्ण

/*
 * push input to tty
 */
अटल व्योम
sclp_tty_input(अचिन्हित अक्षर* buf, अचिन्हित पूर्णांक count)
अणु
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&sclp_port);
	अचिन्हित पूर्णांक cअक्षर;

	/*
	 * If this tty driver is currently बंदd
	 * then throw the received input away.
	 */
	अगर (tty == शून्य)
		वापस;
	cअक्षर = ctrlअक्षर_handle(buf, count, tty);
	चयन (cअक्षर & CTRLCHAR_MASK) अणु
	हाल CTRLCHAR_SYSRQ:
		अवरोध;
	हाल CTRLCHAR_CTRL:
		tty_insert_flip_अक्षर(&sclp_port, cअक्षर, TTY_NORMAL);
		tty_flip_buffer_push(&sclp_port);
		अवरोध;
	हाल CTRLCHAR_NONE:
		/* send (normal) input to line discipline */
		अगर (count < 2 ||
		    (म_भेदन((स्थिर अक्षर *) buf + count - 2, "^n", 2) &&
		     म_भेदन((स्थिर अक्षर *) buf + count - 2, "\252n", 2))) अणु
			/* add the स्वतः \न */
			tty_insert_flip_string(&sclp_port, buf, count);
			tty_insert_flip_अक्षर(&sclp_port, '\n', TTY_NORMAL);
		पूर्ण अन्यथा
			tty_insert_flip_string(&sclp_port, buf, count - 2);
		tty_flip_buffer_push(&sclp_port);
		अवरोध;
	पूर्ण
	tty_kref_put(tty);
पूर्ण

/*
 * get a EBCDIC string in upper/lower हाल,
 * find out अक्षरacters in lower/upper हाल separated by a special अक्षरacter,
 * modअगरiy original string,
 * वापसs length of resulting string
 */
अटल पूर्णांक sclp_चयन_हालs(अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	अचिन्हित अक्षर *ip, *op;
	पूर्णांक toggle;

	/* initially changing हाल is off */
	toggle = 0;
	ip = op = buf;
	जबतक (count-- > 0) अणु
		/* compare with special अक्षरacter */
		अगर (*ip == CASE_DELIMITER) अणु
			/* followed by another special अक्षरacter? */
			अगर (count && ip[1] == CASE_DELIMITER) अणु
				/*
				 * ... then put a single copy of the special
				 * अक्षरacter to the output string
				 */
				*op++ = *ip++;
				count--;
			पूर्ण अन्यथा
				/*
				 * ... special अक्षरacter follower by a normal
				 * अक्षरacter toggles the हाल change behaviour
				 */
				toggle = ~toggle;
			/* skip special अक्षरacter */
			ip++;
		पूर्ण अन्यथा
			/* not the special अक्षरacter */
			अगर (toggle)
				/* but हाल चयनing is on */
				अगर (sclp_tty_छोटे)
					/* चयन to upperहाल */
					*op++ = _ebc_बड़े[(पूर्णांक) *ip++];
				अन्यथा
					/* चयन to lowerहाल */
					*op++ = _ebc_छोटे[(पूर्णांक) *ip++];
			अन्यथा
				/* no हाल चयनing, copy the अक्षरacter */
				*op++ = *ip++;
	पूर्ण
	/* वापस length of reक्रमmatted string. */
	वापस op - buf;
पूर्ण

अटल व्योम sclp_get_input(काष्ठा gds_subvector *sv)
अणु
	अचिन्हित अक्षर *str;
	पूर्णांक count;

	str = (अचिन्हित अक्षर *) (sv + 1);
	count = sv->length - माप(*sv);
	अगर (sclp_tty_छोटे)
		EBC_TOLOWER(str, count);
	count = sclp_चयन_हालs(str, count);
	/* convert EBCDIC to ASCII (modअगरy original input in SCCB) */
	sclp_ebcasc_str(str, count);

	/* transfer input to high level driver */
	sclp_tty_input(str, count);
पूर्ण

अटल अंतरभूत व्योम sclp_eval_selfdeftexपंचांगsg(काष्ठा gds_subvector *sv)
अणु
	व्योम *end;

	end = (व्योम *) sv + sv->length;
	क्रम (sv = sv + 1; (व्योम *) sv < end; sv = (व्योम *) sv + sv->length)
		अगर (sv->key == 0x30)
			sclp_get_input(sv);
पूर्ण

अटल अंतरभूत व्योम sclp_eval_textcmd(काष्ठा gds_vector *v)
अणु
	काष्ठा gds_subvector *sv;
	व्योम *end;

	end = (व्योम *) v + v->length;
	क्रम (sv = (काष्ठा gds_subvector *) (v + 1);
	     (व्योम *) sv < end; sv = (व्योम *) sv + sv->length)
		अगर (sv->key == GDS_KEY_SELFDEFTEXTMSG)
			sclp_eval_selfdeftexपंचांगsg(sv);

पूर्ण

अटल अंतरभूत व्योम sclp_eval_cpmsu(काष्ठा gds_vector *v)
अणु
	व्योम *end;

	end = (व्योम *) v + v->length;
	क्रम (v = v + 1; (व्योम *) v < end; v = (व्योम *) v + v->length)
		अगर (v->gds_id == GDS_ID_TEXTCMD)
			sclp_eval_textcmd(v);
पूर्ण


अटल अंतरभूत व्योम sclp_eval_mdsmu(काष्ठा gds_vector *v)
अणु
	v = sclp_find_gds_vector(v + 1, (व्योम *) v + v->length, GDS_ID_CPMSU);
	अगर (v)
		sclp_eval_cpmsu(v);
पूर्ण

अटल व्योम sclp_tty_receiver(काष्ठा evbuf_header *evbuf)
अणु
	काष्ठा gds_vector *v;

	v = sclp_find_gds_vector(evbuf + 1, (व्योम *) evbuf + evbuf->length,
				 GDS_ID_MDSMU);
	अगर (v)
		sclp_eval_mdsmu(v);
पूर्ण

अटल व्योम
sclp_tty_state_change(काष्ठा sclp_रेजिस्टर *reg)
अणु
पूर्ण

अटल काष्ठा sclp_रेजिस्टर sclp_input_event =
अणु
	.receive_mask = EVTYP_OPCMD_MASK | EVTYP_PMSGCMD_MASK,
	.state_change_fn = sclp_tty_state_change,
	.receiver_fn = sclp_tty_receiver
पूर्ण;

अटल स्थिर काष्ठा tty_operations sclp_ops = अणु
	.खोलो = sclp_tty_खोलो,
	.बंद = sclp_tty_बंद,
	.ग_लिखो = sclp_tty_ग_लिखो,
	.put_अक्षर = sclp_tty_put_अक्षर,
	.flush_अक्षरs = sclp_tty_flush_अक्षरs,
	.ग_लिखो_room = sclp_tty_ग_लिखो_room,
	.अक्षरs_in_buffer = sclp_tty_अक्षरs_in_buffer,
	.flush_buffer = sclp_tty_flush_buffer,
पूर्ण;

अटल पूर्णांक __init
sclp_tty_init(व्योम)
अणु
	काष्ठा tty_driver *driver;
	व्योम *page;
	पूर्णांक i;
	पूर्णांक rc;

	/* z/VM multiplexes the line mode output on the 32xx screen */
	अगर (MACHINE_IS_VM && !CONSOLE_IS_SCLP)
		वापस 0;
	अगर (!sclp.has_linemode)
		वापस 0;
	driver = alloc_tty_driver(1);
	अगर (!driver)
		वापस -ENOMEM;

	rc = sclp_rw_init();
	अगर (rc) अणु
		put_tty_driver(driver);
		वापस rc;
	पूर्ण
	/* Allocate pages क्रम output buffering */
	क्रम (i = 0; i < MAX_KMEM_PAGES; i++) अणु
		page = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
		अगर (page == शून्य) अणु
			put_tty_driver(driver);
			वापस -ENOMEM;
		पूर्ण
		list_add_tail((काष्ठा list_head *) page, &sclp_tty_pages);
	पूर्ण
	समयr_setup(&sclp_tty_समयr, sclp_tty_समयout, 0);
	sclp_ttybuf = शून्य;
	sclp_tty_buffer_count = 0;
	अगर (MACHINE_IS_VM) अणु
		/* हाल input lines to lowerहाल */
		sclp_tty_छोटे = 1;
	पूर्ण
	sclp_tty_अक्षरs_count = 0;

	rc = sclp_रेजिस्टर(&sclp_input_event);
	अगर (rc) अणु
		put_tty_driver(driver);
		वापस rc;
	पूर्ण

	tty_port_init(&sclp_port);

	driver->driver_name = "sclp_line";
	driver->name = "sclp_line";
	driver->major = TTY_MAJOR;
	driver->minor_start = 64;
	driver->type = TTY_DRIVER_TYPE_SYSTEM;
	driver->subtype = SYSTEM_TYPE_TTY;
	driver->init_termios = tty_std_termios;
	driver->init_termios.c_अगरlag = IGNBRK | IGNPAR;
	driver->init_termios.c_oflag = ONLCR;
	driver->init_termios.c_lflag = ISIG | ECHO;
	driver->flags = TTY_DRIVER_REAL_RAW;
	tty_set_operations(driver, &sclp_ops);
	tty_port_link_device(&sclp_port, driver, 0);
	rc = tty_रेजिस्टर_driver(driver);
	अगर (rc) अणु
		put_tty_driver(driver);
		tty_port_destroy(&sclp_port);
		वापस rc;
	पूर्ण
	sclp_tty_driver = driver;
	वापस 0;
पूर्ण
device_initcall(sclp_tty_init);
