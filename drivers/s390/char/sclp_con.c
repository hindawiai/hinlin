<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SCLP line mode console driver
 *
 * Copyright IBM Corp. 1999, 2009
 * Author(s): Martin Peschke <mpeschke@de.ibm.com>
 *	      Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/kmod.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/termios.h>
#समावेश <linux/err.h>
#समावेश <linux/reboot.h>
#समावेश <linux/gfp.h>

#समावेश "sclp.h"
#समावेश "sclp_rw.h"
#समावेश "sclp_tty.h"

#घोषणा sclp_console_major 4		/* TTYAUX_MAJOR */
#घोषणा sclp_console_minor 64
#घोषणा sclp_console_name  "ttyS"

/* Lock to guard over changes to global variables */
अटल DEFINE_SPINLOCK(sclp_con_lock);
/* List of मुक्त pages that can be used क्रम console output buffering */
अटल LIST_HEAD(sclp_con_pages);
/* List of full काष्ठा sclp_buffer काष्ठाures पढ़ोy क्रम output */
अटल LIST_HEAD(sclp_con_outqueue);
/* Poपूर्णांकer to current console buffer */
अटल काष्ठा sclp_buffer *sclp_conbuf;
/* Timer क्रम delayed output of console messages */
अटल काष्ठा समयr_list sclp_con_समयr;
/* Suspend mode flag */
अटल पूर्णांक sclp_con_suspended;
/* Flag that output queue is currently running */
अटल पूर्णांक sclp_con_queue_running;

/* Output क्रमmat क्रम console messages */
#घोषणा SCLP_CON_COLUMNS	320
#घोषणा SPACES_PER_TAB		8

अटल व्योम
sclp_conbuf_callback(काष्ठा sclp_buffer *buffer, पूर्णांक rc)
अणु
	अचिन्हित दीर्घ flags;
	व्योम *page;

	करो अणु
		page = sclp_unmake_buffer(buffer);
		spin_lock_irqsave(&sclp_con_lock, flags);

		/* Remove buffer from outqueue */
		list_del(&buffer->list);
		list_add_tail((काष्ठा list_head *) page, &sclp_con_pages);

		/* Check अगर there is a pending buffer on the out queue. */
		buffer = शून्य;
		अगर (!list_empty(&sclp_con_outqueue))
			buffer = list_first_entry(&sclp_con_outqueue,
						  काष्ठा sclp_buffer, list);
		अगर (!buffer || sclp_con_suspended) अणु
			sclp_con_queue_running = 0;
			spin_unlock_irqrestore(&sclp_con_lock, flags);
			अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&sclp_con_lock, flags);
	पूर्ण जबतक (sclp_emit_buffer(buffer, sclp_conbuf_callback));
पूर्ण

/*
 * Finalize and emit first pending buffer.
 */
अटल व्योम sclp_conbuf_emit(व्योम)
अणु
	काष्ठा sclp_buffer* buffer;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&sclp_con_lock, flags);
	अगर (sclp_conbuf)
		list_add_tail(&sclp_conbuf->list, &sclp_con_outqueue);
	sclp_conbuf = शून्य;
	अगर (sclp_con_queue_running || sclp_con_suspended)
		जाओ out_unlock;
	अगर (list_empty(&sclp_con_outqueue))
		जाओ out_unlock;
	buffer = list_first_entry(&sclp_con_outqueue, काष्ठा sclp_buffer,
				  list);
	sclp_con_queue_running = 1;
	spin_unlock_irqrestore(&sclp_con_lock, flags);

	rc = sclp_emit_buffer(buffer, sclp_conbuf_callback);
	अगर (rc)
		sclp_conbuf_callback(buffer, rc);
	वापस;
out_unlock:
	spin_unlock_irqrestore(&sclp_con_lock, flags);
पूर्ण

/*
 * Wait until out queue is empty
 */
अटल व्योम sclp_console_sync_queue(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sclp_con_lock, flags);
	अगर (समयr_pending(&sclp_con_समयr))
		del_समयr(&sclp_con_समयr);
	जबतक (sclp_con_queue_running) अणु
		spin_unlock_irqrestore(&sclp_con_lock, flags);
		sclp_sync_रुको();
		spin_lock_irqsave(&sclp_con_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&sclp_con_lock, flags);
पूर्ण

/*
 * When this routine is called from the समयr then we flush the
 * temporary ग_लिखो buffer without further रुकोing on a final new line.
 */
अटल व्योम
sclp_console_समयout(काष्ठा समयr_list *unused)
अणु
	sclp_conbuf_emit();
पूर्ण

/*
 * Drop oldest console buffer अगर sclp_con_drop is set
 */
अटल पूर्णांक
sclp_console_drop_buffer(व्योम)
अणु
	काष्ठा list_head *list;
	काष्ठा sclp_buffer *buffer;
	व्योम *page;

	अगर (!sclp_console_drop)
		वापस 0;
	list = sclp_con_outqueue.next;
	अगर (sclp_con_queue_running)
		/* The first element is in I/O */
		list = list->next;
	अगर (list == &sclp_con_outqueue)
		वापस 0;
	list_del(list);
	buffer = list_entry(list, काष्ठा sclp_buffer, list);
	page = sclp_unmake_buffer(buffer);
	list_add_tail((काष्ठा list_head *) page, &sclp_con_pages);
	वापस 1;
पूर्ण

/*
 * Writes the given message to S390 प्रणाली console
 */
अटल व्योम
sclp_console_ग_लिखो(काष्ठा console *console, स्थिर अक्षर *message,
		   अचिन्हित पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;
	व्योम *page;
	पूर्णांक written;

	अगर (count == 0)
		वापस;
	spin_lock_irqsave(&sclp_con_lock, flags);
	/*
	 * process escape अक्षरacters, ग_लिखो message पूर्णांकo buffer,
	 * send buffer to SCLP
	 */
	करो अणु
		/* make sure we have a console output buffer */
		अगर (sclp_conbuf == शून्य) अणु
			अगर (list_empty(&sclp_con_pages))
				sclp_console_full++;
			जबतक (list_empty(&sclp_con_pages)) अणु
				अगर (sclp_con_suspended)
					जाओ out;
				अगर (sclp_console_drop_buffer())
					अवरोध;
				spin_unlock_irqrestore(&sclp_con_lock, flags);
				sclp_sync_रुको();
				spin_lock_irqsave(&sclp_con_lock, flags);
			पूर्ण
			page = sclp_con_pages.next;
			list_del((काष्ठा list_head *) page);
			sclp_conbuf = sclp_make_buffer(page, SCLP_CON_COLUMNS,
						       SPACES_PER_TAB);
		पूर्ण
		/* try to ग_लिखो the string to the current output buffer */
		written = sclp_ग_लिखो(sclp_conbuf, (स्थिर अचिन्हित अक्षर *)
				     message, count);
		अगर (written == count)
			अवरोध;
		/*
		 * Not all अक्षरacters could be written to the current
		 * output buffer. Emit the buffer, create a new buffer
		 * and then output the rest of the string.
		 */
		spin_unlock_irqrestore(&sclp_con_lock, flags);
		sclp_conbuf_emit();
		spin_lock_irqsave(&sclp_con_lock, flags);
		message += written;
		count -= written;
	पूर्ण जबतक (count > 0);
	/* Setup समयr to output current console buffer after 1/10 second */
	अगर (sclp_conbuf != शून्य && sclp_अक्षरs_in_buffer(sclp_conbuf) != 0 &&
	    !समयr_pending(&sclp_con_समयr)) अणु
		mod_समयr(&sclp_con_समयr, jअगरfies + HZ / 10);
	पूर्ण
out:
	spin_unlock_irqrestore(&sclp_con_lock, flags);
पूर्ण

अटल काष्ठा tty_driver *
sclp_console_device(काष्ठा console *c, पूर्णांक *index)
अणु
	*index = c->index;
	वापस sclp_tty_driver;
पूर्ण

/*
 * Make sure that all buffers will be flushed to the SCLP.
 */
अटल व्योम
sclp_console_flush(व्योम)
अणु
	sclp_conbuf_emit();
	sclp_console_sync_queue();
पूर्ण

/*
 * Resume console: If there are cached messages, emit them.
 */
अटल व्योम sclp_console_resume(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sclp_con_lock, flags);
	sclp_con_suspended = 0;
	spin_unlock_irqrestore(&sclp_con_lock, flags);
	sclp_conbuf_emit();
पूर्ण

/*
 * Suspend console: Set suspend flag and flush console
 */
अटल व्योम sclp_console_suspend(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sclp_con_lock, flags);
	sclp_con_suspended = 1;
	spin_unlock_irqrestore(&sclp_con_lock, flags);
	sclp_console_flush();
पूर्ण

अटल पूर्णांक sclp_console_notअगरy(काष्ठा notअगरier_block *self,
			       अचिन्हित दीर्घ event, व्योम *data)
अणु
	sclp_console_flush();
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block on_panic_nb = अणु
	.notअगरier_call = sclp_console_notअगरy,
	.priority = SCLP_PANIC_PRIO_CLIENT,
पूर्ण;

अटल काष्ठा notअगरier_block on_reboot_nb = अणु
	.notअगरier_call = sclp_console_notअगरy,
	.priority = 1,
पूर्ण;

/*
 * used to रेजिस्टर the SCLP console to the kernel and to
 * give prपूर्णांकk necessary inक्रमmation
 */
अटल काष्ठा console sclp_console =
अणु
	.name = sclp_console_name,
	.ग_लिखो = sclp_console_ग_लिखो,
	.device = sclp_console_device,
	.flags = CON_PRINTBUFFER,
	.index = 0 /* ttyS0 */
पूर्ण;

/*
 * This function is called क्रम SCLP suspend and resume events.
 */
व्योम sclp_console_pm_event(क्रमागत sclp_pm_event sclp_pm_event)
अणु
	चयन (sclp_pm_event) अणु
	हाल SCLP_PM_EVENT_FREEZE:
		sclp_console_suspend();
		अवरोध;
	हाल SCLP_PM_EVENT_RESTORE:
	हाल SCLP_PM_EVENT_THAW:
		sclp_console_resume();
		अवरोध;
	पूर्ण
पूर्ण

/*
 * called by console_init() in drivers/अक्षर/tty_io.c at boot-समय.
 */
अटल पूर्णांक __init
sclp_console_init(व्योम)
अणु
	व्योम *page;
	पूर्णांक i;
	पूर्णांक rc;

	/* SCLP consoles are handled together */
	अगर (!(CONSOLE_IS_SCLP || CONSOLE_IS_VT220))
		वापस 0;
	rc = sclp_rw_init();
	अगर (rc)
		वापस rc;
	/* Allocate pages क्रम output buffering */
	क्रम (i = 0; i < sclp_console_pages; i++) अणु
		page = (व्योम *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
		list_add_tail(page, &sclp_con_pages);
	पूर्ण
	sclp_conbuf = शून्य;
	समयr_setup(&sclp_con_समयr, sclp_console_समयout, 0);

	/* enable prपूर्णांकk-access to this driver */
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &on_panic_nb);
	रेजिस्टर_reboot_notअगरier(&on_reboot_nb);
	रेजिस्टर_console(&sclp_console);
	वापस 0;
पूर्ण

console_initcall(sclp_console_init);
