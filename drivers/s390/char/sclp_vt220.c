<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SCLP VT220 terminal driver.
 *
 * Copyright IBM Corp. 2003, 2009
 *
 * Author(s): Peter Oberparleiter <Peter.Oberparleiter@de.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/major.h>
#समावेश <linux/console.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>

#समावेश <linux/uaccess.h>
#समावेश "sclp.h"
#समावेश "ctrlchar.h"

#घोषणा SCLP_VT220_MAJOR		TTY_MAJOR
#घोषणा SCLP_VT220_MINOR		65
#घोषणा SCLP_VT220_DRIVER_NAME		"sclp_vt220"
#घोषणा SCLP_VT220_DEVICE_NAME		"ttysclp"
#घोषणा SCLP_VT220_CONSOLE_NAME		"ttyS"
#घोषणा SCLP_VT220_CONSOLE_INDEX	1	/* console=ttyS1 */

/* Representation of a single ग_लिखो request */
काष्ठा sclp_vt220_request अणु
	काष्ठा list_head list;
	काष्ठा sclp_req sclp_req;
	पूर्णांक retry_count;
पूर्ण;

/* VT220 SCCB */
काष्ठा sclp_vt220_sccb अणु
	काष्ठा sccb_header header;
	काष्ठा evbuf_header evbuf;
पूर्ण;

#घोषणा SCLP_VT220_MAX_CHARS_PER_BUFFER	(PAGE_SIZE - \
					 माप(काष्ठा sclp_vt220_request) - \
					 माप(काष्ठा sclp_vt220_sccb))

/* Structures and data needed to रेजिस्टर tty driver */
अटल काष्ठा tty_driver *sclp_vt220_driver;

अटल काष्ठा tty_port sclp_vt220_port;

/* Lock to protect पूर्णांकernal data from concurrent access */
अटल DEFINE_SPINLOCK(sclp_vt220_lock);

/* List of empty pages to be used as ग_लिखो request buffers */
अटल LIST_HEAD(sclp_vt220_empty);

/* List of pending requests */
अटल LIST_HEAD(sclp_vt220_outqueue);

/* Suspend mode flag */
अटल पूर्णांक sclp_vt220_suspended;

/* Flag that output queue is currently running */
अटल पूर्णांक sclp_vt220_queue_running;

/* Timer used क्रम delaying ग_लिखो requests to merge subsequent messages पूर्णांकo
 * a single buffer */
अटल काष्ठा समयr_list sclp_vt220_समयr;

/* Poपूर्णांकer to current request buffer which has been partially filled but not
 * yet sent */
अटल काष्ठा sclp_vt220_request *sclp_vt220_current_request;

/* Number of अक्षरacters in current request buffer */
अटल पूर्णांक sclp_vt220_buffered_अक्षरs;

/* Counter controlling core driver initialization. */
अटल पूर्णांक __initdata sclp_vt220_init_count;

/* Flag indicating that sclp_vt220_current_request should really
 * have been alपढ़ोy queued but wasn't because the SCLP was processing
 * another buffer */
अटल पूर्णांक sclp_vt220_flush_later;

अटल व्योम sclp_vt220_receiver_fn(काष्ठा evbuf_header *evbuf);
अटल व्योम sclp_vt220_pm_event_fn(काष्ठा sclp_रेजिस्टर *reg,
				   क्रमागत sclp_pm_event sclp_pm_event);
अटल पूर्णांक __sclp_vt220_emit(काष्ठा sclp_vt220_request *request);
अटल व्योम sclp_vt220_emit_current(व्योम);

/* Registration काष्ठाure क्रम SCLP output event buffers */
अटल काष्ठा sclp_रेजिस्टर sclp_vt220_रेजिस्टर = अणु
	.send_mask		= EVTYP_VT220MSG_MASK,
	.pm_event_fn		= sclp_vt220_pm_event_fn,
पूर्ण;

/* Registration काष्ठाure क्रम SCLP input event buffers */
अटल काष्ठा sclp_रेजिस्टर sclp_vt220_रेजिस्टर_input = अणु
	.receive_mask		= EVTYP_VT220MSG_MASK,
	.receiver_fn		= sclp_vt220_receiver_fn,
पूर्ण;


/*
 * Put provided request buffer back पूर्णांकo queue and check emit pending
 * buffers अगर necessary.
 */
अटल व्योम
sclp_vt220_process_queue(काष्ठा sclp_vt220_request *request)
अणु
	अचिन्हित दीर्घ flags;
	व्योम *page;

	करो अणु
		/* Put buffer back to list of empty buffers */
		page = request->sclp_req.sccb;
		spin_lock_irqsave(&sclp_vt220_lock, flags);
		/* Move request from outqueue to empty queue */
		list_del(&request->list);
		list_add_tail((काष्ठा list_head *) page, &sclp_vt220_empty);
		/* Check अगर there is a pending buffer on the out queue. */
		request = शून्य;
		अगर (!list_empty(&sclp_vt220_outqueue))
			request = list_entry(sclp_vt220_outqueue.next,
					     काष्ठा sclp_vt220_request, list);
		अगर (!request || sclp_vt220_suspended) अणु
			sclp_vt220_queue_running = 0;
			spin_unlock_irqrestore(&sclp_vt220_lock, flags);
			अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&sclp_vt220_lock, flags);
	पूर्ण जबतक (__sclp_vt220_emit(request));
	अगर (request == शून्य && sclp_vt220_flush_later)
		sclp_vt220_emit_current();
	tty_port_tty_wakeup(&sclp_vt220_port);
पूर्ण

#घोषणा SCLP_BUFFER_MAX_RETRY		1

/*
 * Callback through which the result of a ग_लिखो request is reported by the
 * SCLP.
 */
अटल व्योम
sclp_vt220_callback(काष्ठा sclp_req *request, व्योम *data)
अणु
	काष्ठा sclp_vt220_request *vt220_request;
	काष्ठा sclp_vt220_sccb *sccb;

	vt220_request = (काष्ठा sclp_vt220_request *) data;
	अगर (request->status == SCLP_REQ_FAILED) अणु
		sclp_vt220_process_queue(vt220_request);
		वापस;
	पूर्ण
	sccb = (काष्ठा sclp_vt220_sccb *) vt220_request->sclp_req.sccb;

	/* Check SCLP response code and choose suitable action	*/
	चयन (sccb->header.response_code) अणु
	हाल 0x0020 :
		अवरोध;

	हाल 0x05f0: /* Target resource in improper state */
		अवरोध;

	हाल 0x0340: /* Contained SCLP equipment check */
		अगर (++vt220_request->retry_count > SCLP_BUFFER_MAX_RETRY)
			अवरोध;
		/* Remove processed buffers and requeue rest */
		अगर (sclp_हटाओ_processed((काष्ठा sccb_header *) sccb) > 0) अणु
			/* Not all buffers were processed */
			sccb->header.response_code = 0x0000;
			vt220_request->sclp_req.status = SCLP_REQ_FILLED;
			अगर (sclp_add_request(request) == 0)
				वापस;
		पूर्ण
		अवरोध;

	हाल 0x0040: /* SCLP equipment check */
		अगर (++vt220_request->retry_count > SCLP_BUFFER_MAX_RETRY)
			अवरोध;
		sccb->header.response_code = 0x0000;
		vt220_request->sclp_req.status = SCLP_REQ_FILLED;
		अगर (sclp_add_request(request) == 0)
			वापस;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	sclp_vt220_process_queue(vt220_request);
पूर्ण

/*
 * Emit vt220 request buffer to SCLP. Return zero on success, non-zero
 * otherwise.
 */
अटल पूर्णांक
__sclp_vt220_emit(काष्ठा sclp_vt220_request *request)
अणु
	request->sclp_req.command = SCLP_CMDW_WRITE_EVENT_DATA;
	request->sclp_req.status = SCLP_REQ_FILLED;
	request->sclp_req.callback = sclp_vt220_callback;
	request->sclp_req.callback_data = (व्योम *) request;

	वापस sclp_add_request(&request->sclp_req);
पूर्ण

/*
 * Queue and emit current request.
 */
अटल व्योम
sclp_vt220_emit_current(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sclp_vt220_request *request;
	काष्ठा sclp_vt220_sccb *sccb;

	spin_lock_irqsave(&sclp_vt220_lock, flags);
	अगर (sclp_vt220_current_request) अणु
		sccb = (काष्ठा sclp_vt220_sccb *) 
				sclp_vt220_current_request->sclp_req.sccb;
		/* Only emit buffers with content */
		अगर (sccb->header.length != माप(काष्ठा sclp_vt220_sccb)) अणु
			list_add_tail(&sclp_vt220_current_request->list,
				      &sclp_vt220_outqueue);
			sclp_vt220_current_request = शून्य;
			अगर (समयr_pending(&sclp_vt220_समयr))
				del_समयr(&sclp_vt220_समयr);
		पूर्ण
		sclp_vt220_flush_later = 0;
	पूर्ण
	अगर (sclp_vt220_queue_running || sclp_vt220_suspended)
		जाओ out_unlock;
	अगर (list_empty(&sclp_vt220_outqueue))
		जाओ out_unlock;
	request = list_first_entry(&sclp_vt220_outqueue,
				   काष्ठा sclp_vt220_request, list);
	sclp_vt220_queue_running = 1;
	spin_unlock_irqrestore(&sclp_vt220_lock, flags);

	अगर (__sclp_vt220_emit(request))
		sclp_vt220_process_queue(request);
	वापस;
out_unlock:
	spin_unlock_irqrestore(&sclp_vt220_lock, flags);
पूर्ण

#घोषणा SCLP_NORMAL_WRITE	0x00

/*
 * Helper function to initialize a page with the sclp request काष्ठाure.
 */
अटल काष्ठा sclp_vt220_request *
sclp_vt220_initialize_page(व्योम *page)
अणु
	काष्ठा sclp_vt220_request *request;
	काष्ठा sclp_vt220_sccb *sccb;

	/* Place request काष्ठाure at end of page */
	request = ((काष्ठा sclp_vt220_request *)
			((addr_t) page + PAGE_SIZE)) - 1;
	request->retry_count = 0;
	request->sclp_req.sccb = page;
	/* SCCB goes at start of page */
	sccb = (काष्ठा sclp_vt220_sccb *) page;
	स_रखो((व्योम *) sccb, 0, माप(काष्ठा sclp_vt220_sccb));
	sccb->header.length = माप(काष्ठा sclp_vt220_sccb);
	sccb->header.function_code = SCLP_NORMAL_WRITE;
	sccb->header.response_code = 0x0000;
	sccb->evbuf.type = EVTYP_VT220MSG;
	sccb->evbuf.length = माप(काष्ठा evbuf_header);

	वापस request;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
sclp_vt220_space_left(काष्ठा sclp_vt220_request *request)
अणु
	काष्ठा sclp_vt220_sccb *sccb;
	sccb = (काष्ठा sclp_vt220_sccb *) request->sclp_req.sccb;
	वापस PAGE_SIZE - माप(काष्ठा sclp_vt220_request) -
	       sccb->header.length;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
sclp_vt220_अक्षरs_stored(काष्ठा sclp_vt220_request *request)
अणु
	काष्ठा sclp_vt220_sccb *sccb;
	sccb = (काष्ठा sclp_vt220_sccb *) request->sclp_req.sccb;
	वापस sccb->evbuf.length - माप(काष्ठा evbuf_header);
पूर्ण

/*
 * Add msg to buffer associated with request. Return the number of अक्षरacters
 * added.
 */
अटल पूर्णांक
sclp_vt220_add_msg(काष्ठा sclp_vt220_request *request,
		   स्थिर अचिन्हित अक्षर *msg, पूर्णांक count, पूर्णांक convertlf)
अणु
	काष्ठा sclp_vt220_sccb *sccb;
	व्योम *buffer;
	अचिन्हित अक्षर c;
	पूर्णांक from;
	पूर्णांक to;

	अगर (count > sclp_vt220_space_left(request))
		count = sclp_vt220_space_left(request);
	अगर (count <= 0)
		वापस 0;

	sccb = (काष्ठा sclp_vt220_sccb *) request->sclp_req.sccb;
	buffer = (व्योम *) ((addr_t) sccb + sccb->header.length);

	अगर (convertlf) अणु
		/* Perक्रमm Linefeed conversion (0x0a -> 0x0a 0x0d)*/
		क्रम (from=0, to=0;
		     (from < count) && (to < sclp_vt220_space_left(request));
		     from++) अणु
			/* Retrieve अक्षरacter */
			c = msg[from];
			/* Perक्रमm conversion */
			अगर (c == 0x0a) अणु
				अगर (to + 1 < sclp_vt220_space_left(request)) अणु
					((अचिन्हित अक्षर *) buffer)[to++] = c;
					((अचिन्हित अक्षर *) buffer)[to++] = 0x0d;
				पूर्ण अन्यथा
					अवरोध;

			पूर्ण अन्यथा
				((अचिन्हित अक्षर *) buffer)[to++] = c;
		पूर्ण
		sccb->header.length += to;
		sccb->evbuf.length += to;
		वापस from;
	पूर्ण अन्यथा अणु
		स_नकल(buffer, (स्थिर व्योम *) msg, count);
		sccb->header.length += count;
		sccb->evbuf.length += count;
		वापस count;
	पूर्ण
पूर्ण

/*
 * Emit buffer after having रुकोed दीर्घ enough क्रम more data to arrive.
 */
अटल व्योम
sclp_vt220_समयout(काष्ठा समयr_list *unused)
अणु
	sclp_vt220_emit_current();
पूर्ण

#घोषणा BUFFER_MAX_DELAY	HZ/20

/*
 * Drop oldest console buffer अगर sclp_con_drop is set
 */
अटल पूर्णांक
sclp_vt220_drop_buffer(व्योम)
अणु
	काष्ठा list_head *list;
	काष्ठा sclp_vt220_request *request;
	व्योम *page;

	अगर (!sclp_console_drop)
		वापस 0;
	list = sclp_vt220_outqueue.next;
	अगर (sclp_vt220_queue_running)
		/* The first element is in I/O */
		list = list->next;
	अगर (list == &sclp_vt220_outqueue)
		वापस 0;
	list_del(list);
	request = list_entry(list, काष्ठा sclp_vt220_request, list);
	page = request->sclp_req.sccb;
	list_add_tail((काष्ठा list_head *) page, &sclp_vt220_empty);
	वापस 1;
पूर्ण

/* 
 * Internal implementation of the ग_लिखो function. Write COUNT bytes of data
 * from memory at BUF
 * to the SCLP पूर्णांकerface. In हाल that the data करोes not fit पूर्णांकo the current
 * ग_लिखो buffer, emit the current one and allocate a new one. If there are no
 * more empty buffers available, रुको until one माला_लो emptied. If DO_SCHEDULE
 * is non-zero, the buffer will be scheduled क्रम emitting after a समयout -
 * otherwise the user has to explicitly call the flush function.
 * A non-zero CONVERTLF parameter indicates that 0x0a अक्षरacters in the message
 * buffer should be converted to 0x0a 0x0d. After completion, वापस the number
 * of bytes written.
 */
अटल पूर्णांक
__sclp_vt220_ग_लिखो(स्थिर अचिन्हित अक्षर *buf, पूर्णांक count, पूर्णांक करो_schedule,
		   पूर्णांक convertlf, पूर्णांक may_fail)
अणु
	अचिन्हित दीर्घ flags;
	व्योम *page;
	पूर्णांक written;
	पूर्णांक overall_written;

	अगर (count <= 0)
		वापस 0;
	overall_written = 0;
	spin_lock_irqsave(&sclp_vt220_lock, flags);
	करो अणु
		/* Create an sclp output buffer अगर none exists yet */
		अगर (sclp_vt220_current_request == शून्य) अणु
			अगर (list_empty(&sclp_vt220_empty))
				sclp_console_full++;
			जबतक (list_empty(&sclp_vt220_empty)) अणु
				अगर (may_fail || sclp_vt220_suspended)
					जाओ out;
				अगर (sclp_vt220_drop_buffer())
					अवरोध;
				spin_unlock_irqrestore(&sclp_vt220_lock, flags);

				sclp_sync_रुको();
				spin_lock_irqsave(&sclp_vt220_lock, flags);
			पूर्ण
			page = (व्योम *) sclp_vt220_empty.next;
			list_del((काष्ठा list_head *) page);
			sclp_vt220_current_request =
				sclp_vt220_initialize_page(page);
		पूर्ण
		/* Try to ग_लिखो the string to the current request buffer */
		written = sclp_vt220_add_msg(sclp_vt220_current_request,
					     buf, count, convertlf);
		overall_written += written;
		अगर (written == count)
			अवरोध;
		/*
		 * Not all अक्षरacters could be written to the current
		 * output buffer. Emit the buffer, create a new buffer
		 * and then output the rest of the string.
		 */
		spin_unlock_irqrestore(&sclp_vt220_lock, flags);
		sclp_vt220_emit_current();
		spin_lock_irqsave(&sclp_vt220_lock, flags);
		buf += written;
		count -= written;
	पूर्ण जबतक (count > 0);
	/* Setup समयr to output current console buffer after some समय */
	अगर (sclp_vt220_current_request != शून्य &&
	    !समयr_pending(&sclp_vt220_समयr) && करो_schedule) अणु
		sclp_vt220_समयr.expires = jअगरfies + BUFFER_MAX_DELAY;
		add_समयr(&sclp_vt220_समयr);
	पूर्ण
out:
	spin_unlock_irqrestore(&sclp_vt220_lock, flags);
	वापस overall_written;
पूर्ण

/*
 * This routine is called by the kernel to ग_लिखो a series of
 * अक्षरacters to the tty device.  The अक्षरacters may come from
 * user space or kernel space.  This routine will वापस the
 * number of अक्षरacters actually accepted क्रम writing.
 */
अटल पूर्णांक
sclp_vt220_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	वापस __sclp_vt220_ग_लिखो(buf, count, 1, 0, 1);
पूर्ण

#घोषणा SCLP_VT220_SESSION_ENDED	0x01
#घोषणा	SCLP_VT220_SESSION_STARTED	0x80
#घोषणा SCLP_VT220_SESSION_DATA		0x00

#अगर_घोषित CONFIG_MAGIC_SYSRQ

अटल पूर्णांक sysrq_pressed;
अटल काष्ठा sysrq_work sysrq;

अटल व्योम sclp_vt220_reset_session(व्योम)
अणु
	sysrq_pressed = 0;
पूर्ण

अटल व्योम sclp_vt220_handle_input(स्थिर अक्षर *buffer, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		/* Handle magic sys request */
		अगर (buffer[i] == ('O' ^ 0100)) अणु /* CTRL-O */
			/*
			 * If pressed again, reset sysrq_pressed
			 * and flip CTRL-O अक्षरacter
			 */
			sysrq_pressed = !sysrq_pressed;
			अगर (sysrq_pressed)
				जारी;
		पूर्ण अन्यथा अगर (sysrq_pressed) अणु
			sysrq.key = buffer[i];
			schedule_sysrq_work(&sysrq);
			sysrq_pressed = 0;
			जारी;
		पूर्ण
		tty_insert_flip_अक्षर(&sclp_vt220_port, buffer[i], 0);
	पूर्ण
पूर्ण

#अन्यथा

अटल व्योम sclp_vt220_reset_session(व्योम)
अणु
पूर्ण

अटल व्योम sclp_vt220_handle_input(स्थिर अक्षर *buffer, अचिन्हित पूर्णांक count)
अणु
	tty_insert_flip_string(&sclp_vt220_port, buffer, count);
पूर्ण

#पूर्ण_अगर

/*
 * Called by the SCLP to report incoming event buffers.
 */
अटल व्योम
sclp_vt220_receiver_fn(काष्ठा evbuf_header *evbuf)
अणु
	अक्षर *buffer;
	अचिन्हित पूर्णांक count;

	buffer = (अक्षर *) ((addr_t) evbuf + माप(काष्ठा evbuf_header));
	count = evbuf->length - माप(काष्ठा evbuf_header);

	चयन (*buffer) अणु
	हाल SCLP_VT220_SESSION_ENDED:
	हाल SCLP_VT220_SESSION_STARTED:
		sclp_vt220_reset_session();
		अवरोध;
	हाल SCLP_VT220_SESSION_DATA:
		/* Send input to line discipline */
		buffer++;
		count--;
		sclp_vt220_handle_input(buffer, count);
		tty_flip_buffer_push(&sclp_vt220_port);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * This routine is called when a particular tty device is खोलोed.
 */
अटल पूर्णांक
sclp_vt220_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	अगर (tty->count == 1) अणु
		tty_port_tty_set(&sclp_vt220_port, tty);
		अगर (!tty->winsize.ws_row && !tty->winsize.ws_col) अणु
			tty->winsize.ws_row = 24;
			tty->winsize.ws_col = 80;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This routine is called when a particular tty device is बंदd.
 */
अटल व्योम
sclp_vt220_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	अगर (tty->count == 1)
		tty_port_tty_set(&sclp_vt220_port, शून्य);
पूर्ण

/*
 * This routine is called by the kernel to ग_लिखो a single
 * अक्षरacter to the tty device.  If the kernel uses this routine,
 * it must call the flush_अक्षरs() routine (अगर defined) when it is
 * करोne stuffing अक्षरacters पूर्णांकo the driver.
 */
अटल पूर्णांक
sclp_vt220_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	वापस __sclp_vt220_ग_लिखो(&ch, 1, 0, 0, 1);
पूर्ण

/*
 * This routine is called by the kernel after it has written a
 * series of अक्षरacters to the tty device using put_अक्षर().  
 */
अटल व्योम
sclp_vt220_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (!sclp_vt220_queue_running)
		sclp_vt220_emit_current();
	अन्यथा
		sclp_vt220_flush_later = 1;
पूर्ण

/*
 * This routine वापसs the numbers of अक्षरacters the tty driver
 * will accept क्रम queuing to be written.  This number is subject
 * to change as output buffers get emptied, or अगर the output flow
 * control is acted.
 */
अटल पूर्णांक
sclp_vt220_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *l;
	पूर्णांक count;

	spin_lock_irqsave(&sclp_vt220_lock, flags);
	count = 0;
	अगर (sclp_vt220_current_request != शून्य)
		count = sclp_vt220_space_left(sclp_vt220_current_request);
	list_क्रम_each(l, &sclp_vt220_empty)
		count += SCLP_VT220_MAX_CHARS_PER_BUFFER;
	spin_unlock_irqrestore(&sclp_vt220_lock, flags);
	वापस count;
पूर्ण

/*
 * Return number of buffered अक्षरs.
 */
अटल पूर्णांक
sclp_vt220_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *l;
	काष्ठा sclp_vt220_request *r;
	पूर्णांक count;

	spin_lock_irqsave(&sclp_vt220_lock, flags);
	count = 0;
	अगर (sclp_vt220_current_request != शून्य)
		count = sclp_vt220_अक्षरs_stored(sclp_vt220_current_request);
	list_क्रम_each(l, &sclp_vt220_outqueue) अणु
		r = list_entry(l, काष्ठा sclp_vt220_request, list);
		count += sclp_vt220_अक्षरs_stored(r);
	पूर्ण
	spin_unlock_irqrestore(&sclp_vt220_lock, flags);
	वापस count;
पूर्ण

/*
 * Pass on all buffers to the hardware. Return only when there are no more
 * buffers pending.
 */
अटल व्योम
sclp_vt220_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	sclp_vt220_emit_current();
पूर्ण

/* Release allocated pages. */
अटल व्योम __init __sclp_vt220_मुक्त_pages(व्योम)
अणु
	काष्ठा list_head *page, *p;

	list_क्रम_each_safe(page, p, &sclp_vt220_empty) अणु
		list_del(page);
		मुक्त_page((अचिन्हित दीर्घ) page);
	पूर्ण
पूर्ण

/* Release memory and unरेजिस्टर from sclp core. Controlled by init counting -
 * only the last invoker will actually perक्रमm these actions. */
अटल व्योम __init __sclp_vt220_cleanup(व्योम)
अणु
	sclp_vt220_init_count--;
	अगर (sclp_vt220_init_count != 0)
		वापस;
	sclp_unरेजिस्टर(&sclp_vt220_रेजिस्टर);
	__sclp_vt220_मुक्त_pages();
	tty_port_destroy(&sclp_vt220_port);
पूर्ण

/* Allocate buffer pages and रेजिस्टर with sclp core. Controlled by init
 * counting - only the first invoker will actually perक्रमm these actions. */
अटल पूर्णांक __init __sclp_vt220_init(पूर्णांक num_pages)
अणु
	व्योम *page;
	पूर्णांक i;
	पूर्णांक rc;

	sclp_vt220_init_count++;
	अगर (sclp_vt220_init_count != 1)
		वापस 0;
	समयr_setup(&sclp_vt220_समयr, sclp_vt220_समयout, 0);
	tty_port_init(&sclp_vt220_port);
	sclp_vt220_current_request = शून्य;
	sclp_vt220_buffered_अक्षरs = 0;
	sclp_vt220_flush_later = 0;

	/* Allocate pages क्रम output buffering */
	rc = -ENOMEM;
	क्रम (i = 0; i < num_pages; i++) अणु
		page = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
		अगर (!page)
			जाओ out;
		list_add_tail(page, &sclp_vt220_empty);
	पूर्ण
	rc = sclp_रेजिस्टर(&sclp_vt220_रेजिस्टर);
out:
	अगर (rc) अणु
		__sclp_vt220_मुक्त_pages();
		sclp_vt220_init_count--;
		tty_port_destroy(&sclp_vt220_port);
	पूर्ण
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा tty_operations sclp_vt220_ops = अणु
	.खोलो = sclp_vt220_खोलो,
	.बंद = sclp_vt220_बंद,
	.ग_लिखो = sclp_vt220_ग_लिखो,
	.put_अक्षर = sclp_vt220_put_अक्षर,
	.flush_अक्षरs = sclp_vt220_flush_अक्षरs,
	.ग_लिखो_room = sclp_vt220_ग_लिखो_room,
	.अक्षरs_in_buffer = sclp_vt220_अक्षरs_in_buffer,
	.flush_buffer = sclp_vt220_flush_buffer,
पूर्ण;

/*
 * Register driver with SCLP and Linux and initialize पूर्णांकernal tty काष्ठाures.
 */
अटल पूर्णांक __init sclp_vt220_tty_init(व्योम)
अणु
	काष्ठा tty_driver *driver;
	पूर्णांक rc;

	/* Note: we're not testing क्रम CONSOLE_IS_SCLP here to preserve
	 * symmetry between VM and LPAR प्रणालीs regarding ttyS1. */
	driver = alloc_tty_driver(1);
	अगर (!driver)
		वापस -ENOMEM;
	rc = __sclp_vt220_init(MAX_KMEM_PAGES);
	अगर (rc)
		जाओ out_driver;

	driver->driver_name = SCLP_VT220_DRIVER_NAME;
	driver->name = SCLP_VT220_DEVICE_NAME;
	driver->major = SCLP_VT220_MAJOR;
	driver->minor_start = SCLP_VT220_MINOR;
	driver->type = TTY_DRIVER_TYPE_SYSTEM;
	driver->subtype = SYSTEM_TYPE_TTY;
	driver->init_termios = tty_std_termios;
	driver->flags = TTY_DRIVER_REAL_RAW;
	tty_set_operations(driver, &sclp_vt220_ops);
	tty_port_link_device(&sclp_vt220_port, driver, 0);

	rc = tty_रेजिस्टर_driver(driver);
	अगर (rc)
		जाओ out_init;
	rc = sclp_रेजिस्टर(&sclp_vt220_रेजिस्टर_input);
	अगर (rc)
		जाओ out_reg;
	sclp_vt220_driver = driver;
	वापस 0;

out_reg:
	tty_unरेजिस्टर_driver(driver);
out_init:
	__sclp_vt220_cleanup();
out_driver:
	put_tty_driver(driver);
	वापस rc;
पूर्ण
__initcall(sclp_vt220_tty_init);

अटल व्योम __sclp_vt220_flush_buffer(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	sclp_vt220_emit_current();
	spin_lock_irqsave(&sclp_vt220_lock, flags);
	अगर (समयr_pending(&sclp_vt220_समयr))
		del_समयr(&sclp_vt220_समयr);
	जबतक (sclp_vt220_queue_running) अणु
		spin_unlock_irqrestore(&sclp_vt220_lock, flags);
		sclp_sync_रुको();
		spin_lock_irqsave(&sclp_vt220_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&sclp_vt220_lock, flags);
पूर्ण

/*
 * Resume console: If there are cached messages, emit them.
 */
अटल व्योम sclp_vt220_resume(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sclp_vt220_lock, flags);
	sclp_vt220_suspended = 0;
	spin_unlock_irqrestore(&sclp_vt220_lock, flags);
	sclp_vt220_emit_current();
पूर्ण

/*
 * Suspend console: Set suspend flag and flush console
 */
अटल व्योम sclp_vt220_suspend(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sclp_vt220_lock, flags);
	sclp_vt220_suspended = 1;
	spin_unlock_irqrestore(&sclp_vt220_lock, flags);
	__sclp_vt220_flush_buffer();
पूर्ण

अटल व्योम sclp_vt220_pm_event_fn(काष्ठा sclp_रेजिस्टर *reg,
				   क्रमागत sclp_pm_event sclp_pm_event)
अणु
	चयन (sclp_pm_event) अणु
	हाल SCLP_PM_EVENT_FREEZE:
		sclp_vt220_suspend();
		अवरोध;
	हाल SCLP_PM_EVENT_RESTORE:
	हाल SCLP_PM_EVENT_THAW:
		sclp_vt220_resume();
		अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SCLP_VT220_CONSOLE

अटल व्योम
sclp_vt220_con_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *buf, अचिन्हित पूर्णांक count)
अणु
	__sclp_vt220_ग_लिखो((स्थिर अचिन्हित अक्षर *) buf, count, 1, 1, 0);
पूर्ण

अटल काष्ठा tty_driver *
sclp_vt220_con_device(काष्ठा console *c, पूर्णांक *index)
अणु
	*index = 0;
	वापस sclp_vt220_driver;
पूर्ण

अटल पूर्णांक
sclp_vt220_notअगरy(काष्ठा notअगरier_block *self,
			  अचिन्हित दीर्घ event, व्योम *data)
अणु
	__sclp_vt220_flush_buffer();
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block on_panic_nb = अणु
	.notअगरier_call = sclp_vt220_notअगरy,
	.priority = 1,
पूर्ण;

अटल काष्ठा notअगरier_block on_reboot_nb = अणु
	.notअगरier_call = sclp_vt220_notअगरy,
	.priority = 1,
पूर्ण;

/* Structure needed to रेजिस्टर with prपूर्णांकk */
अटल काष्ठा console sclp_vt220_console =
अणु
	.name = SCLP_VT220_CONSOLE_NAME,
	.ग_लिखो = sclp_vt220_con_ग_लिखो,
	.device = sclp_vt220_con_device,
	.flags = CON_PRINTBUFFER,
	.index = SCLP_VT220_CONSOLE_INDEX
पूर्ण;

अटल पूर्णांक __init
sclp_vt220_con_init(व्योम)
अणु
	पूर्णांक rc;

	rc = __sclp_vt220_init(sclp_console_pages);
	अगर (rc)
		वापस rc;
	/* Attach linux console */
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &on_panic_nb);
	रेजिस्टर_reboot_notअगरier(&on_reboot_nb);
	रेजिस्टर_console(&sclp_vt220_console);
	वापस 0;
पूर्ण

console_initcall(sclp_vt220_con_init);
#पूर्ण_अगर /* CONFIG_SCLP_VT220_CONSOLE */

