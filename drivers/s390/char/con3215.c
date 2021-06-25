<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * 3215 line mode terminal driver.
 *
 * Copyright IBM Corp. 1999, 2009
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 *
 * Updated:
 *  Aug-2000: Added tab support
 *	      Dan Morrison, IBM Corporation <dmorriso@cse.buffalo.edu>
 */

#समावेश <linux/types.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/reboot.h>
#समावेश <linux/serial.h> /* ASYNC_* flags */
#समावेश <linux/slab.h>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/ebcdic.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/cpcmd.h>
#समावेश <यंत्र/setup.h>

#समावेश "ctrlchar.h"

#घोषणा NR_3215		    1
#घोषणा NR_3215_REQ	    (4*NR_3215)
#घोषणा RAW3215_BUFFER_SIZE 65536     /* output buffer size */
#घोषणा RAW3215_INBUF_SIZE  256	      /* input buffer size */
#घोषणा RAW3215_MIN_SPACE   128	      /* minimum मुक्त space क्रम wakeup */
#घोषणा RAW3215_MIN_WRITE   1024      /* min. length क्रम immediate output */
#घोषणा RAW3215_MAX_BYTES   3968      /* max. bytes to ग_लिखो with one ssch */
#घोषणा RAW3215_MAX_NEWLINE 50	      /* max. lines to ग_लिखो with one ssch */
#घोषणा RAW3215_NR_CCWS	    3
#घोषणा RAW3215_TIMEOUT	    HZ/10     /* समय क्रम delayed output */

#घोषणा RAW3215_FIXED	    1	      /* 3215 console device is not be मुक्तd */
#घोषणा RAW3215_WORKING	    4	      /* set अगर a request is being worked on */
#घोषणा RAW3215_THROTTLED   8	      /* set अगर पढ़ोing is disabled */
#घोषणा RAW3215_STOPPED	    16	      /* set अगर writing is disabled */
#घोषणा RAW3215_TIMER_RUNS  64	      /* set अगर the output delay समयr is on */
#घोषणा RAW3215_FLUSHING    128	      /* set to flush buffer (no delay) */

#घोषणा TAB_STOP_SIZE	    8	      /* tab stop size */

/*
 * Request types क्रम a 3215 device
 */
क्रमागत raw3215_type अणु
	RAW3215_FREE, RAW3215_READ, RAW3215_WRITE
पूर्ण;

/*
 * Request काष्ठाure क्रम a 3215 device
 */
काष्ठा raw3215_req अणु
	क्रमागत raw3215_type type;	      /* type of the request */
	पूर्णांक start, len;		      /* start index & len in output buffer */
	पूर्णांक delayable;		      /* indication to रुको क्रम more data */
	पूर्णांक residual;		      /* residual count क्रम पढ़ो request */
	काष्ठा ccw1 ccws[RAW3215_NR_CCWS]; /* space क्रम the channel program */
	काष्ठा raw3215_info *info;    /* poपूर्णांकer to मुख्य काष्ठाure */
	काष्ठा raw3215_req *next;     /* poपूर्णांकer to next request */
पूर्ण __attribute__ ((aligned(8)));

काष्ठा raw3215_info अणु
	काष्ठा tty_port port;
	काष्ठा ccw_device *cdev;      /* device क्रम tty driver */
	spinlock_t *lock;	      /* poपूर्णांकer to irq lock */
	पूर्णांक flags;		      /* state flags */
	अक्षर *buffer;		      /* poपूर्णांकer to output buffer */
	अक्षर *inbuf;		      /* poपूर्णांकer to input buffer */
	पूर्णांक head;		      /* first मुक्त byte in output buffer */
	पूर्णांक count;		      /* number of bytes in output buffer */
	पूर्णांक written;		      /* number of bytes in ग_लिखो requests */
	काष्ठा raw3215_req *queued_पढ़ो; /* poपूर्णांकer to queued पढ़ो requests */
	काष्ठा raw3215_req *queued_ग_लिखो;/* poपूर्णांकer to queued ग_लिखो requests */
	रुको_queue_head_t empty_रुको; /* रुको queue क्रम flushing */
	काष्ठा समयr_list समयr;      /* समयr क्रम delayed output */
	पूर्णांक line_pos;		      /* position on the line (क्रम tअसल) */
	अक्षर ubuffer[80];	      /* copy_from_user buffer */
पूर्ण;

/* array of 3215 devices काष्ठाures */
अटल काष्ठा raw3215_info *raw3215[NR_3215];
/* spinlock to protect the raw3215 array */
अटल DEFINE_SPINLOCK(raw3215_device_lock);
/* list of मुक्त request काष्ठाures */
अटल काष्ठा raw3215_req *raw3215_मुक्तlist;
/* spinlock to protect मुक्त list */
अटल DEFINE_SPINLOCK(raw3215_मुक्तlist_lock);

अटल काष्ठा tty_driver *tty3215_driver;

/*
 * Get a request काष्ठाure from the मुक्त list
 */
अटल अंतरभूत काष्ठा raw3215_req *raw3215_alloc_req(व्योम)
अणु
	काष्ठा raw3215_req *req;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&raw3215_मुक्तlist_lock, flags);
	req = raw3215_मुक्तlist;
	raw3215_मुक्तlist = req->next;
	spin_unlock_irqrestore(&raw3215_मुक्तlist_lock, flags);
	वापस req;
पूर्ण

/*
 * Put a request काष्ठाure back to the मुक्त list
 */
अटल अंतरभूत व्योम raw3215_मुक्त_req(काष्ठा raw3215_req *req)
अणु
	अचिन्हित दीर्घ flags;

	अगर (req->type == RAW3215_FREE)
		वापस;		/* करोn't मुक्त a मुक्त request */
	req->type = RAW3215_FREE;
	spin_lock_irqsave(&raw3215_मुक्तlist_lock, flags);
	req->next = raw3215_मुक्तlist;
	raw3215_मुक्तlist = req;
	spin_unlock_irqrestore(&raw3215_मुक्तlist_lock, flags);
पूर्ण

/*
 * Set up a पढ़ो request that पढ़ोs up to 160 byte from the 3215 device.
 * If there is a queued पढ़ो request it is used, but that shouldn't happen
 * because a 3215 terminal won't accept a new पढ़ो beक्रमe the old one is
 * completed.
 */
अटल व्योम raw3215_mk_पढ़ो_req(काष्ठा raw3215_info *raw)
अणु
	काष्ठा raw3215_req *req;
	काष्ठा ccw1 *ccw;

	/* there can only be ONE पढ़ो request at a समय */
	req = raw->queued_पढ़ो;
	अगर (req == शून्य) अणु
		/* no queued पढ़ो request, use new req काष्ठाure */
		req = raw3215_alloc_req();
		req->type = RAW3215_READ;
		req->info = raw;
		raw->queued_पढ़ो = req;
	पूर्ण

	ccw = req->ccws;
	ccw->cmd_code = 0x0A; /* पढ़ो inquiry */
	ccw->flags = 0x20;    /* ignore incorrect length */
	ccw->count = 160;
	ccw->cda = (__u32) __pa(raw->inbuf);
पूर्ण

/*
 * Set up a ग_लिखो request with the inक्रमmation from the मुख्य काष्ठाure.
 * A ccw chain is created that ग_लिखोs as much as possible from the output
 * buffer to the 3215 device. If a queued ग_लिखो exists it is replaced by
 * the new, probably lengthened request.
 */
अटल व्योम raw3215_mk_ग_लिखो_req(काष्ठा raw3215_info *raw)
अणु
	काष्ठा raw3215_req *req;
	काष्ठा ccw1 *ccw;
	पूर्णांक len, count, ix, lines;

	अगर (raw->count <= raw->written)
		वापस;
	/* check अगर there is a queued ग_लिखो request */
	req = raw->queued_ग_लिखो;
	अगर (req == शून्य) अणु
		/* no queued ग_लिखो request, use new req काष्ठाure */
		req = raw3215_alloc_req();
		req->type = RAW3215_WRITE;
		req->info = raw;
		raw->queued_ग_लिखो = req;
	पूर्ण अन्यथा अणु
		raw->written -= req->len;
	पूर्ण

	ccw = req->ccws;
	req->start = (raw->head - raw->count + raw->written) &
		     (RAW3215_BUFFER_SIZE - 1);
	/*
	 * now we have to count newlines. We can at max accept
	 * RAW3215_MAX_NEWLINE newlines in a single ssch due to
	 * a restriction in VM
	 */
	lines = 0;
	ix = req->start;
	जबतक (lines < RAW3215_MAX_NEWLINE && ix != raw->head) अणु
		अगर (raw->buffer[ix] == 0x15)
			lines++;
		ix = (ix + 1) & (RAW3215_BUFFER_SIZE - 1);
	पूर्ण
	len = ((ix - 1 - req->start) & (RAW3215_BUFFER_SIZE - 1)) + 1;
	अगर (len > RAW3215_MAX_BYTES)
		len = RAW3215_MAX_BYTES;
	req->len = len;
	raw->written += len;

	/* set the indication अगर we should try to enlarge this request */
	req->delayable = (ix == raw->head) && (len < RAW3215_MIN_WRITE);

	ix = req->start;
	जबतक (len > 0) अणु
		अगर (ccw > req->ccws)
			ccw[-1].flags |= 0x40; /* use command chaining */
		ccw->cmd_code = 0x01; /* ग_लिखो, स्वतः carrier वापस */
		ccw->flags = 0x20;    /* ignore incorrect length ind.  */
		ccw->cda =
			(__u32) __pa(raw->buffer + ix);
		count = len;
		अगर (ix + count > RAW3215_BUFFER_SIZE)
			count = RAW3215_BUFFER_SIZE - ix;
		ccw->count = count;
		len -= count;
		ix = (ix + count) & (RAW3215_BUFFER_SIZE - 1);
		ccw++;
	पूर्ण
	/*
	 * Add a NOP to the channel program. 3215 devices are purely
	 * emulated and its much better to aव्योम the channel end
	 * पूर्णांकerrupt in this हाल.
	 */
	अगर (ccw > req->ccws)
		ccw[-1].flags |= 0x40; /* use command chaining */
	ccw->cmd_code = 0x03; /* NOP */
	ccw->flags = 0;
	ccw->cda = 0;
	ccw->count = 1;
पूर्ण

/*
 * Start a पढ़ो or a ग_लिखो request
 */
अटल व्योम raw3215_start_io(काष्ठा raw3215_info *raw)
अणु
	काष्ठा raw3215_req *req;
	पूर्णांक res;

	req = raw->queued_पढ़ो;
	अगर (req != शून्य &&
	    !(raw->flags & (RAW3215_WORKING | RAW3215_THROTTLED))) अणु
		/* dequeue request */
		raw->queued_पढ़ो = शून्य;
		res = ccw_device_start(raw->cdev, req->ccws,
				       (अचिन्हित दीर्घ) req, 0, 0);
		अगर (res != 0) अणु
			/* करो_IO failed, put request back to queue */
			raw->queued_पढ़ो = req;
		पूर्ण अन्यथा अणु
			raw->flags |= RAW3215_WORKING;
		पूर्ण
	पूर्ण
	req = raw->queued_ग_लिखो;
	अगर (req != शून्य &&
	    !(raw->flags & (RAW3215_WORKING | RAW3215_STOPPED))) अणु
		/* dequeue request */
		raw->queued_ग_लिखो = शून्य;
		res = ccw_device_start(raw->cdev, req->ccws,
				       (अचिन्हित दीर्घ) req, 0, 0);
		अगर (res != 0) अणु
			/* करो_IO failed, put request back to queue */
			raw->queued_ग_लिखो = req;
		पूर्ण अन्यथा अणु
			raw->flags |= RAW3215_WORKING;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Function to start a delayed output after RAW3215_TIMEOUT seconds
 */
अटल व्योम raw3215_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा raw3215_info *raw = from_समयr(raw, t, समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	raw->flags &= ~RAW3215_TIMER_RUNS;
	raw3215_mk_ग_लिखो_req(raw);
	raw3215_start_io(raw);
	अगर ((raw->queued_पढ़ो || raw->queued_ग_लिखो) &&
	    !(raw->flags & RAW3215_WORKING) &&
	    !(raw->flags & RAW3215_TIMER_RUNS)) अणु
		raw->समयr.expires = RAW3215_TIMEOUT + jअगरfies;
		add_समयr(&raw->समयr);
		raw->flags |= RAW3215_TIMER_RUNS;
	पूर्ण
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
पूर्ण

/*
 * Function to conditionally start an IO. A पढ़ो is started immediately,
 * a ग_लिखो is only started immediately अगर the flush flag is on or the
 * amount of data is bigger than RAW3215_MIN_WRITE. If a ग_लिखो is not
 * करोne immediately a समयr is started with a delay of RAW3215_TIMEOUT.
 */
अटल अंतरभूत व्योम raw3215_try_io(काष्ठा raw3215_info *raw)
अणु
	अगर (!tty_port_initialized(&raw->port))
		वापस;
	अगर (raw->queued_पढ़ो != शून्य)
		raw3215_start_io(raw);
	अन्यथा अगर (raw->queued_ग_लिखो != शून्य) अणु
		अगर ((raw->queued_ग_लिखो->delayable == 0) ||
		    (raw->flags & RAW3215_FLUSHING)) अणु
			/* execute ग_लिखो requests bigger than minimum size */
			raw3215_start_io(raw);
		पूर्ण
	पूर्ण
	अगर ((raw->queued_पढ़ो || raw->queued_ग_लिखो) &&
	    !(raw->flags & RAW3215_WORKING) &&
	    !(raw->flags & RAW3215_TIMER_RUNS)) अणु
		raw->समयr.expires = RAW3215_TIMEOUT + jअगरfies;
		add_समयr(&raw->समयr);
		raw->flags |= RAW3215_TIMER_RUNS;
	पूर्ण
पूर्ण

/*
 * Try to start the next IO and wake up processes रुकोing on the tty.
 */
अटल व्योम raw3215_next_io(काष्ठा raw3215_info *raw, काष्ठा tty_काष्ठा *tty)
अणु
	raw3215_mk_ग_लिखो_req(raw);
	raw3215_try_io(raw);
	अगर (tty && RAW3215_BUFFER_SIZE - raw->count >= RAW3215_MIN_SPACE)
		tty_wakeup(tty);
पूर्ण

/*
 * Interrupt routine, called from common io layer
 */
अटल व्योम raw3215_irq(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ पूर्णांकparm,
			काष्ठा irb *irb)
अणु
	काष्ठा raw3215_info *raw;
	काष्ठा raw3215_req *req;
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक cstat, dstat;
	पूर्णांक count;

	raw = dev_get_drvdata(&cdev->dev);
	req = (काष्ठा raw3215_req *) पूर्णांकparm;
	tty = tty_port_tty_get(&raw->port);
	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;
	अगर (cstat != 0)
		raw3215_next_io(raw, tty);
	अगर (dstat & 0x01) अणु /* we got a unit exception */
		dstat &= ~0x01;	 /* we can ignore it */
	पूर्ण
	चयन (dstat) अणु
	हाल 0x80:
		अगर (cstat != 0)
			अवरोध;
		/* Attention पूर्णांकerrupt, someone hit the enter key */
		raw3215_mk_पढ़ो_req(raw);
		raw3215_next_io(raw, tty);
		अवरोध;
	हाल 0x08:
	हाल 0x0C:
		/* Channel end पूर्णांकerrupt. */
		अगर ((raw = req->info) == शून्य)
			जाओ put_tty;	     /* That shouldn't happen ... */
		अगर (req->type == RAW3215_READ) अणु
			/* store residual count, then रुको क्रम device end */
			req->residual = irb->scsw.cmd.count;
		पूर्ण
		अगर (dstat == 0x08)
			अवरोध;
		fallthrough;
	हाल 0x04:
		/* Device end पूर्णांकerrupt. */
		अगर ((raw = req->info) == शून्य)
			जाओ put_tty;	     /* That shouldn't happen ... */
		अगर (req->type == RAW3215_READ && tty != शून्य) अणु
			अचिन्हित पूर्णांक cअक्षर;

			count = 160 - req->residual;
			EBCASC(raw->inbuf, count);
			cअक्षर = ctrlअक्षर_handle(raw->inbuf, count, tty);
			चयन (cअक्षर & CTRLCHAR_MASK) अणु
			हाल CTRLCHAR_SYSRQ:
				अवरोध;

			हाल CTRLCHAR_CTRL:
				tty_insert_flip_अक्षर(&raw->port, cअक्षर,
						TTY_NORMAL);
				tty_flip_buffer_push(&raw->port);
				अवरोध;

			हाल CTRLCHAR_NONE:
				अगर (count < 2 ||
				    (म_भेदन(raw->inbuf+count-2, "\252n", 2) &&
				     म_भेदन(raw->inbuf+count-2, "^n", 2)) ) अणु
					/* add the स्वतः \न */
					raw->inbuf[count] = '\n';
					count++;
				पूर्ण अन्यथा
					count -= 2;
				tty_insert_flip_string(&raw->port, raw->inbuf,
						count);
				tty_flip_buffer_push(&raw->port);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (req->type == RAW3215_WRITE) अणु
			raw->count -= req->len;
			raw->written -= req->len;
		पूर्ण
		raw->flags &= ~RAW3215_WORKING;
		raw3215_मुक्त_req(req);
		/* check क्रम empty रुको */
		अगर (रुकोqueue_active(&raw->empty_रुको) &&
		    raw->queued_ग_लिखो == शून्य &&
		    raw->queued_पढ़ो == शून्य) अणु
			wake_up_पूर्णांकerruptible(&raw->empty_रुको);
		पूर्ण
		raw3215_next_io(raw, tty);
		अवरोध;
	शेष:
		/* Strange पूर्णांकerrupt, I'll करो my best to clean up */
		अगर (req != शून्य && req->type != RAW3215_FREE) अणु
			अगर (req->type == RAW3215_WRITE) अणु
				raw->count -= req->len;
				raw->written -= req->len;
			पूर्ण
			raw->flags &= ~RAW3215_WORKING;
			raw3215_मुक्त_req(req);
		पूर्ण
		raw3215_next_io(raw, tty);
	पूर्ण
put_tty:
	tty_kref_put(tty);
पूर्ण

/*
 * Wait until length bytes are available पूर्णांक the output buffer.
 * Has to be called with the s390irq lock held. Can be called
 * disabled.
 */
अटल व्योम raw3215_make_room(काष्ठा raw3215_info *raw, अचिन्हित पूर्णांक length)
अणु
	जबतक (RAW3215_BUFFER_SIZE - raw->count < length) अणु
		/* there might be a request pending */
		raw->flags |= RAW3215_FLUSHING;
		raw3215_mk_ग_लिखो_req(raw);
		raw3215_try_io(raw);
		raw->flags &= ~RAW3215_FLUSHING;
#अगर_घोषित CONFIG_TN3215_CONSOLE
		ccw_device_रुको_idle(raw->cdev);
#पूर्ण_अगर
		/* Enough room मुक्तd up ? */
		अगर (RAW3215_BUFFER_SIZE - raw->count >= length)
			अवरोध;
		/* there might be another cpu रुकोing क्रम the lock */
		spin_unlock(get_ccwdev_lock(raw->cdev));
		udelay(100);
		spin_lock(get_ccwdev_lock(raw->cdev));
	पूर्ण
पूर्ण

/*
 * String ग_लिखो routine क्रम 3215 devices
 */
अटल व्योम raw3215_ग_लिखो(काष्ठा raw3215_info *raw, स्थिर अक्षर *str,
			  अचिन्हित पूर्णांक length)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक c, count;

	जबतक (length > 0) अणु
		spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
		count = (length > RAW3215_BUFFER_SIZE) ?
					     RAW3215_BUFFER_SIZE : length;
		length -= count;

		raw3215_make_room(raw, count);

		/* copy string to output buffer and convert it to EBCDIC */
		जबतक (1) अणु
			c = min_t(पूर्णांक, count,
				  min(RAW3215_BUFFER_SIZE - raw->count,
				      RAW3215_BUFFER_SIZE - raw->head));
			अगर (c <= 0)
				अवरोध;
			स_नकल(raw->buffer + raw->head, str, c);
			ASCEBC(raw->buffer + raw->head, c);
			raw->head = (raw->head + c) & (RAW3215_BUFFER_SIZE - 1);
			raw->count += c;
			raw->line_pos += c;
			str += c;
			count -= c;
		पूर्ण
		अगर (!(raw->flags & RAW3215_WORKING)) अणु
			raw3215_mk_ग_लिखो_req(raw);
			/* start or queue request */
			raw3215_try_io(raw);
		पूर्ण
		spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
	पूर्ण
पूर्ण

/*
 * Put अक्षरacter routine क्रम 3215 devices
 */
अटल व्योम raw3215_अक्षर_दो(काष्ठा raw3215_info *raw, अचिन्हित अक्षर ch)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक length, i;

	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	अगर (ch == '\t') अणु
		length = TAB_STOP_SIZE - (raw->line_pos%TAB_STOP_SIZE);
		raw->line_pos += length;
		ch = ' ';
	पूर्ण अन्यथा अगर (ch == '\n') अणु
		length = 1;
		raw->line_pos = 0;
	पूर्ण अन्यथा अणु
		length = 1;
		raw->line_pos++;
	पूर्ण
	raw3215_make_room(raw, length);

	क्रम (i = 0; i < length; i++) अणु
		raw->buffer[raw->head] = (अक्षर) _ascebc[(पूर्णांक) ch];
		raw->head = (raw->head + 1) & (RAW3215_BUFFER_SIZE - 1);
		raw->count++;
	पूर्ण
	अगर (!(raw->flags & RAW3215_WORKING)) अणु
		raw3215_mk_ग_लिखो_req(raw);
		/* start or queue request */
		raw3215_try_io(raw);
	पूर्ण
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
पूर्ण

/*
 * Flush routine, it simply sets the flush flag and tries to start
 * pending IO.
 */
अटल व्योम raw3215_flush_buffer(काष्ठा raw3215_info *raw)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	अगर (raw->count > 0) अणु
		raw->flags |= RAW3215_FLUSHING;
		raw3215_try_io(raw);
		raw->flags &= ~RAW3215_FLUSHING;
	पूर्ण
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
पूर्ण

/*
 * Fire up a 3215 device.
 */
अटल पूर्णांक raw3215_startup(काष्ठा raw3215_info *raw)
अणु
	अचिन्हित दीर्घ flags;

	अगर (tty_port_initialized(&raw->port))
		वापस 0;
	raw->line_pos = 0;
	tty_port_set_initialized(&raw->port, 1);
	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	raw3215_try_io(raw);
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);

	वापस 0;
पूर्ण

/*
 * Shutकरोwn a 3215 device.
 */
अटल व्योम raw3215_shutकरोwn(काष्ठा raw3215_info *raw)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	अचिन्हित दीर्घ flags;

	अगर (!tty_port_initialized(&raw->port) || (raw->flags & RAW3215_FIXED))
		वापस;
	/* Wait क्रम outstanding requests, then मुक्त irq */
	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	अगर ((raw->flags & RAW3215_WORKING) ||
	    raw->queued_ग_लिखो != शून्य ||
	    raw->queued_पढ़ो != शून्य) अणु
		add_रुको_queue(&raw->empty_रुको, &रुको);
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
		schedule();
		spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
		हटाओ_रुको_queue(&raw->empty_रुको, &रुको);
		set_current_state(TASK_RUNNING);
		tty_port_set_initialized(&raw->port, 1);
	पूर्ण
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
पूर्ण

अटल काष्ठा raw3215_info *raw3215_alloc_info(व्योम)
अणु
	काष्ठा raw3215_info *info;

	info = kzalloc(माप(काष्ठा raw3215_info), GFP_KERNEL | GFP_DMA);
	अगर (!info)
		वापस शून्य;

	info->buffer = kzalloc(RAW3215_BUFFER_SIZE, GFP_KERNEL | GFP_DMA);
	info->inbuf = kzalloc(RAW3215_INBUF_SIZE, GFP_KERNEL | GFP_DMA);
	अगर (!info->buffer || !info->inbuf) अणु
		kमुक्त(info->inbuf);
		kमुक्त(info->buffer);
		kमुक्त(info);
		वापस शून्य;
	पूर्ण

	समयr_setup(&info->समयr, raw3215_समयout, 0);
	init_रुकोqueue_head(&info->empty_रुको);
	tty_port_init(&info->port);

	वापस info;
पूर्ण

अटल व्योम raw3215_मुक्त_info(काष्ठा raw3215_info *raw)
अणु
	kमुक्त(raw->inbuf);
	kमुक्त(raw->buffer);
	tty_port_destroy(&raw->port);
	kमुक्त(raw);
पूर्ण

अटल पूर्णांक raw3215_probe (काष्ठा ccw_device *cdev)
अणु
	काष्ठा raw3215_info *raw;
	पूर्णांक line;

	/* Console is special. */
	अगर (raw3215[0] && (raw3215[0] == dev_get_drvdata(&cdev->dev)))
		वापस 0;

	raw = raw3215_alloc_info();
	अगर (raw == शून्य)
		वापस -ENOMEM;

	raw->cdev = cdev;
	dev_set_drvdata(&cdev->dev, raw);
	cdev->handler = raw3215_irq;

	spin_lock(&raw3215_device_lock);
	क्रम (line = 0; line < NR_3215; line++) अणु
		अगर (!raw3215[line]) अणु
			raw3215[line] = raw;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&raw3215_device_lock);
	अगर (line == NR_3215) अणु
		raw3215_मुक्त_info(raw);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम raw3215_हटाओ (काष्ठा ccw_device *cdev)
अणु
	काष्ठा raw3215_info *raw;
	अचिन्हित पूर्णांक line;

	ccw_device_set_offline(cdev);
	raw = dev_get_drvdata(&cdev->dev);
	अगर (raw) अणु
		spin_lock(&raw3215_device_lock);
		क्रम (line = 0; line < NR_3215; line++)
			अगर (raw3215[line] == raw)
				अवरोध;
		raw3215[line] = शून्य;
		spin_unlock(&raw3215_device_lock);
		dev_set_drvdata(&cdev->dev, शून्य);
		raw3215_मुक्त_info(raw);
	पूर्ण
पूर्ण

अटल पूर्णांक raw3215_set_online (काष्ठा ccw_device *cdev)
अणु
	काष्ठा raw3215_info *raw;

	raw = dev_get_drvdata(&cdev->dev);
	अगर (!raw)
		वापस -ENODEV;

	वापस raw3215_startup(raw);
पूर्ण

अटल पूर्णांक raw3215_set_offline (काष्ठा ccw_device *cdev)
अणु
	काष्ठा raw3215_info *raw;

	raw = dev_get_drvdata(&cdev->dev);
	अगर (!raw)
		वापस -ENODEV;

	raw3215_shutकरोwn(raw);

	वापस 0;
पूर्ण

अटल काष्ठा ccw_device_id raw3215_id[] = अणु
	अणु CCW_DEVICE(0x3215, 0) पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

अटल काष्ठा ccw_driver raw3215_ccw_driver = अणु
	.driver = अणु
		.name	= "3215",
		.owner	= THIS_MODULE,
	पूर्ण,
	.ids		= raw3215_id,
	.probe		= &raw3215_probe,
	.हटाओ		= &raw3215_हटाओ,
	.set_online	= &raw3215_set_online,
	.set_offline	= &raw3215_set_offline,
	.पूर्णांक_class	= IRQIO_C15,
पूर्ण;

#अगर_घोषित CONFIG_TN3215_CONSOLE
/*
 * Write a string to the 3215 console
 */
अटल व्योम con3215_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *str,
			  अचिन्हित पूर्णांक count)
अणु
	काष्ठा raw3215_info *raw;
	पूर्णांक i;

	अगर (count <= 0)
		वापस;
	raw = raw3215[0];	/* console 3215 is the first one */
	जबतक (count > 0) अणु
		क्रम (i = 0; i < count; i++)
			अगर (str[i] == '\t' || str[i] == '\n')
				अवरोध;
		raw3215_ग_लिखो(raw, str, i);
		count -= i;
		str += i;
		अगर (count > 0) अणु
			raw3215_अक्षर_दो(raw, *str);
			count--;
			str++;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा tty_driver *con3215_device(काष्ठा console *c, पूर्णांक *index)
अणु
	*index = c->index;
	वापस tty3215_driver;
पूर्ण

/*
 * panic() calls con3215_flush through a panic_notअगरier
 * beक्रमe the प्रणाली enters a disabled, endless loop.
 */
अटल व्योम con3215_flush(व्योम)
अणु
	काष्ठा raw3215_info *raw;
	अचिन्हित दीर्घ flags;

	raw = raw3215[0];  /* console 3215 is the first one */
	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	raw3215_make_room(raw, RAW3215_BUFFER_SIZE);
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
पूर्ण

अटल पूर्णांक con3215_notअगरy(काष्ठा notअगरier_block *self,
			  अचिन्हित दीर्घ event, व्योम *data)
अणु
	con3215_flush();
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block on_panic_nb = अणु
	.notअगरier_call = con3215_notअगरy,
	.priority = 0,
पूर्ण;

अटल काष्ठा notअगरier_block on_reboot_nb = अणु
	.notअगरier_call = con3215_notअगरy,
	.priority = 0,
पूर्ण;

/*
 *  The console काष्ठाure क्रम the 3215 console
 */
अटल काष्ठा console con3215 = अणु
	.name	 = "ttyS",
	.ग_लिखो	 = con3215_ग_लिखो,
	.device	 = con3215_device,
	.flags	 = CON_PRINTBUFFER,
पूर्ण;

/*
 * 3215 console initialization code called from console_init().
 */
अटल पूर्णांक __init con3215_init(व्योम)
अणु
	काष्ठा ccw_device *cdev;
	काष्ठा raw3215_info *raw;
	काष्ठा raw3215_req *req;
	पूर्णांक i;

	/* Check अगर 3215 is to be the console */
	अगर (!CONSOLE_IS_3215)
		वापस -ENODEV;

	/* Set the console mode क्रम VM */
	अगर (MACHINE_IS_VM) अणु
		cpcmd("TERM CONMODE 3215", शून्य, 0, शून्य);
		cpcmd("TERM AUTOCR OFF", शून्य, 0, शून्य);
	पूर्ण

	/* allocate 3215 request काष्ठाures */
	raw3215_मुक्तlist = शून्य;
	क्रम (i = 0; i < NR_3215_REQ; i++) अणु
		req = kzalloc(माप(काष्ठा raw3215_req), GFP_KERNEL | GFP_DMA);
		अगर (!req)
			वापस -ENOMEM;
		req->next = raw3215_मुक्तlist;
		raw3215_मुक्तlist = req;
	पूर्ण

	cdev = ccw_device_create_console(&raw3215_ccw_driver);
	अगर (IS_ERR(cdev))
		वापस -ENODEV;

	raw3215[0] = raw = raw3215_alloc_info();
	raw->cdev = cdev;
	dev_set_drvdata(&cdev->dev, raw);
	cdev->handler = raw3215_irq;

	raw->flags |= RAW3215_FIXED;
	अगर (ccw_device_enable_console(cdev)) अणु
		ccw_device_destroy_console(cdev);
		raw3215_मुक्त_info(raw);
		raw3215[0] = शून्य;
		वापस -ENODEV;
	पूर्ण

	/* Request the console irq */
	अगर (raw3215_startup(raw) != 0) अणु
		raw3215_मुक्त_info(raw);
		raw3215[0] = शून्य;
		वापस -ENODEV;
	पूर्ण
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &on_panic_nb);
	रेजिस्टर_reboot_notअगरier(&on_reboot_nb);
	रेजिस्टर_console(&con3215);
	वापस 0;
पूर्ण
console_initcall(con3215_init);
#पूर्ण_अगर

अटल पूर्णांक tty3215_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा raw3215_info *raw;

	raw = raw3215[tty->index];
	अगर (raw == शून्य)
		वापस -ENODEV;

	tty->driver_data = raw;

	वापस tty_port_install(&raw->port, driver, tty);
पूर्ण

/*
 * tty3215_खोलो
 *
 * This routine is called whenever a 3215 tty is खोलोed.
 */
अटल पूर्णांक tty3215_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	काष्ठा raw3215_info *raw = tty->driver_data;

	tty_port_tty_set(&raw->port, tty);

	/*
	 * Start up 3215 device
	 */
	वापस raw3215_startup(raw);
पूर्ण

/*
 * tty3215_बंद()
 *
 * This routine is called when the 3215 tty is बंदd. We रुको
 * क्रम the reमुख्यing request to be completed. Then we clean up.
 */
अटल व्योम tty3215_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file * filp)
अणु
	काष्ठा raw3215_info *raw = tty->driver_data;

	अगर (raw == शून्य || tty->count > 1)
		वापस;
	tty->closing = 1;
	/* Shutकरोwn the terminal */
	raw3215_shutकरोwn(raw);
	tty->closing = 0;
	tty_port_tty_set(&raw->port, शून्य);
पूर्ण

/*
 * Returns the amount of मुक्त space in the output buffer.
 */
अटल पूर्णांक tty3215_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा raw3215_info *raw = tty->driver_data;

	/* Subtract TAB_STOP_SIZE to allow क्रम a tab, 8 <<< 64K */
	अगर ((RAW3215_BUFFER_SIZE - raw->count - TAB_STOP_SIZE) >= 0)
		वापस RAW3215_BUFFER_SIZE - raw->count - TAB_STOP_SIZE;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * String ग_लिखो routine क्रम 3215 ttys
 */
अटल पूर्णांक tty3215_ग_लिखो(काष्ठा tty_काष्ठा * tty,
			 स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा raw3215_info *raw = tty->driver_data;
	पूर्णांक i, written;

	written = count;
	जबतक (count > 0) अणु
		क्रम (i = 0; i < count; i++)
			अगर (buf[i] == '\t' || buf[i] == '\n')
				अवरोध;
		raw3215_ग_लिखो(raw, buf, i);
		count -= i;
		buf += i;
		अगर (count > 0) अणु
			raw3215_अक्षर_दो(raw, *buf);
			count--;
			buf++;
		पूर्ण
	पूर्ण
	वापस written;
पूर्ण

/*
 * Put अक्षरacter routine क्रम 3215 ttys
 */
अटल पूर्णांक tty3215_put_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर ch)
अणु
	काष्ठा raw3215_info *raw = tty->driver_data;

	raw3215_अक्षर_दो(raw, ch);

	वापस 1;
पूर्ण

अटल व्योम tty3215_flush_अक्षरs(काष्ठा tty_काष्ठा *tty)
अणु
पूर्ण

/*
 * Returns the number of अक्षरacters in the output buffer
 */
अटल पूर्णांक tty3215_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा raw3215_info *raw = tty->driver_data;

	वापस raw->count;
पूर्ण

अटल व्योम tty3215_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा raw3215_info *raw = tty->driver_data;

	raw3215_flush_buffer(raw);
	tty_wakeup(tty);
पूर्ण

/*
 * Disable पढ़ोing from a 3215 tty
 */
अटल व्योम tty3215_throttle(काष्ठा tty_काष्ठा * tty)
अणु
	काष्ठा raw3215_info *raw = tty->driver_data;

	raw->flags |= RAW3215_THROTTLED;
पूर्ण

/*
 * Enable पढ़ोing from a 3215 tty
 */
अटल व्योम tty3215_unthrottle(काष्ठा tty_काष्ठा * tty)
अणु
	काष्ठा raw3215_info *raw = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (raw->flags & RAW3215_THROTTLED) अणु
		spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
		raw->flags &= ~RAW3215_THROTTLED;
		raw3215_try_io(raw);
		spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
	पूर्ण
पूर्ण

/*
 * Disable writing to a 3215 tty
 */
अटल व्योम tty3215_stop(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा raw3215_info *raw = tty->driver_data;

	raw->flags |= RAW3215_STOPPED;
पूर्ण

/*
 * Enable writing to a 3215 tty
 */
अटल व्योम tty3215_start(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा raw3215_info *raw = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (raw->flags & RAW3215_STOPPED) अणु
		spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
		raw->flags &= ~RAW3215_STOPPED;
		raw3215_try_io(raw);
		spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा tty_operations tty3215_ops = अणु
	.install = tty3215_install,
	.खोलो = tty3215_खोलो,
	.बंद = tty3215_बंद,
	.ग_लिखो = tty3215_ग_लिखो,
	.put_अक्षर = tty3215_put_अक्षर,
	.flush_अक्षरs = tty3215_flush_अक्षरs,
	.ग_लिखो_room = tty3215_ग_लिखो_room,
	.अक्षरs_in_buffer = tty3215_अक्षरs_in_buffer,
	.flush_buffer = tty3215_flush_buffer,
	.throttle = tty3215_throttle,
	.unthrottle = tty3215_unthrottle,
	.stop = tty3215_stop,
	.start = tty3215_start,
पूर्ण;

/*
 * 3215 tty registration code called from tty_init().
 * Most kernel services (incl. kदो_स्मृति) are available at this poimt.
 */
अटल पूर्णांक __init tty3215_init(व्योम)
अणु
	काष्ठा tty_driver *driver;
	पूर्णांक ret;

	अगर (!CONSOLE_IS_3215)
		वापस 0;

	driver = alloc_tty_driver(NR_3215);
	अगर (!driver)
		वापस -ENOMEM;

	ret = ccw_driver_रेजिस्टर(&raw3215_ccw_driver);
	अगर (ret) अणु
		put_tty_driver(driver);
		वापस ret;
	पूर्ण
	/*
	 * Initialize the tty_driver काष्ठाure
	 * Entries in tty3215_driver that are NOT initialized:
	 * proc_entry, set_termios, flush_buffer, set_ldisc, ग_लिखो_proc
	 */

	driver->driver_name = "tty3215";
	driver->name = "ttyS";
	driver->major = TTY_MAJOR;
	driver->minor_start = 64;
	driver->type = TTY_DRIVER_TYPE_SYSTEM;
	driver->subtype = SYSTEM_TYPE_TTY;
	driver->init_termios = tty_std_termios;
	driver->init_termios.c_अगरlag = IGNBRK | IGNPAR;
	driver->init_termios.c_oflag = ONLCR;
	driver->init_termios.c_lflag = ISIG;
	driver->flags = TTY_DRIVER_REAL_RAW;
	tty_set_operations(driver, &tty3215_ops);
	ret = tty_रेजिस्टर_driver(driver);
	अगर (ret) अणु
		put_tty_driver(driver);
		वापस ret;
	पूर्ण
	tty3215_driver = driver;
	वापस 0;
पूर्ण
device_initcall(tty3215_init);
