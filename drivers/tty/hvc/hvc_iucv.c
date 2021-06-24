<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * z/VM IUCV hypervisor console (HVC) device driver
 *
 * This HVC device driver provides terminal access using
 * z/VM IUCV communication paths.
 *
 * Copyright IBM Corp. 2008, 2013
 *
 * Author(s):	Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 */
#घोषणा KMSG_COMPONENT		"hvc_iucv"
#घोषणा pr_fmt(fmt)		KMSG_COMPONENT ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/mempool.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/tty.h>
#समावेश <linux/रुको.h>
#समावेश <net/iucv/iucv.h>

#समावेश "hvc_console.h"


/* General device driver settings */
#घोषणा HVC_IUCV_MAGIC		0xc9e4c3e5
#घोषणा MAX_HVC_IUCV_LINES	HVC_ALLOC_TTY_ADAPTERS
#घोषणा MEMPOOL_MIN_NR		(PAGE_SIZE / माप(काष्ठा iucv_tty_buffer)/4)

/* IUCV TTY message  */
#घोषणा MSG_VERSION		0x02	/* Message version */
#घोषणा MSG_TYPE_ERROR		0x01	/* Error message */
#घोषणा MSG_TYPE_TERMENV	0x02	/* Terminal environment variable */
#घोषणा MSG_TYPE_TERMIOS	0x04	/* Terminal IO काष्ठा update */
#घोषणा MSG_TYPE_WINSIZE	0x08	/* Terminal winकरोw size update */
#घोषणा MSG_TYPE_DATA		0x10	/* Terminal data */

काष्ठा iucv_tty_msg अणु
	u8	version;		/* Message version */
	u8	type;			/* Message type */
#घोषणा MSG_MAX_DATALEN		((u16)(~0))
	u16	datalen;		/* Payload length */
	u8	data[];			/* Payload buffer */
पूर्ण __attribute__((packed));
#घोषणा MSG_SIZE(s)		((s) + दुरत्व(काष्ठा iucv_tty_msg, data))

क्रमागत iucv_state_t अणु
	IUCV_DISCONN	= 0,
	IUCV_CONNECTED	= 1,
	IUCV_SEVERED	= 2,
पूर्ण;

क्रमागत tty_state_t अणु
	TTY_CLOSED	= 0,
	TTY_OPENED	= 1,
पूर्ण;

काष्ठा hvc_iucv_निजी अणु
	काष्ठा hvc_काष्ठा	*hvc;		/* HVC काष्ठा reference */
	u8			srv_name[8];	/* IUCV service name (ebcdic) */
	अचिन्हित अक्षर		is_console;	/* Linux console usage flag */
	क्रमागत iucv_state_t	iucv_state;	/* IUCV connection status */
	क्रमागत tty_state_t	tty_state;	/* TTY status */
	काष्ठा iucv_path	*path;		/* IUCV path poपूर्णांकer */
	spinlock_t		lock;		/* hvc_iucv_निजी lock */
#घोषणा SNDBUF_SIZE		(PAGE_SIZE)	/* must be < MSG_MAX_DATALEN */
	व्योम			*sndbuf;	/* send buffer		  */
	माप_प्रकार			sndbuf_len;	/* length of send buffer  */
#घोषणा QUEUE_SNDBUF_DELAY	(HZ / 25)
	काष्ठा delayed_work	sndbuf_work;	/* work: send iucv msg(s) */
	रुको_queue_head_t	sndbuf_रुकोq;	/* रुको क्रम send completion */
	काष्ठा list_head	tty_outqueue;	/* outgoing IUCV messages */
	काष्ठा list_head	tty_inqueue;	/* incoming IUCV messages */
	काष्ठा device		*dev;		/* device काष्ठाure */
	u8			info_path[16];	/* IUCV path info (dev attr) */
पूर्ण;

काष्ठा iucv_tty_buffer अणु
	काष्ठा list_head	list;	/* list poपूर्णांकer */
	काष्ठा iucv_message	msg;	/* store an IUCV message */
	माप_प्रकार			offset;	/* data buffer offset */
	काष्ठा iucv_tty_msg	*mbuf;	/* buffer to store input/output data */
पूर्ण;

/* IUCV callback handler */
अटल	पूर्णांक hvc_iucv_path_pending(काष्ठा iucv_path *, u8 *, u8 *);
अटल व्योम hvc_iucv_path_severed(काष्ठा iucv_path *, u8 *);
अटल व्योम hvc_iucv_msg_pending(काष्ठा iucv_path *, काष्ठा iucv_message *);
अटल व्योम hvc_iucv_msg_complete(काष्ठा iucv_path *, काष्ठा iucv_message *);


/* Kernel module parameter: use one terminal device as शेष */
अटल अचिन्हित दीर्घ hvc_iucv_devices = 1;

/* Array of allocated hvc iucv tty lines... */
अटल काष्ठा hvc_iucv_निजी *hvc_iucv_table[MAX_HVC_IUCV_LINES];
#घोषणा IUCV_HVC_CON_IDX	(0)
/* List of z/VM user ID filter entries (काष्ठा iucv_vmid_filter) */
#घोषणा MAX_VMID_FILTER		(500)
#घोषणा FILTER_WILDCARD_CHAR	'*'
अटल माप_प्रकार hvc_iucv_filter_size;
अटल व्योम *hvc_iucv_filter;
अटल स्थिर अक्षर *hvc_iucv_filter_string;
अटल DEFINE_RWLOCK(hvc_iucv_filter_lock);

/* Kmem cache and mempool क्रम iucv_tty_buffer elements */
अटल काष्ठा kmem_cache *hvc_iucv_buffer_cache;
अटल mempool_t *hvc_iucv_mempool;

/* IUCV handler callback functions */
अटल काष्ठा iucv_handler hvc_iucv_handler = अणु
	.path_pending  = hvc_iucv_path_pending,
	.path_severed  = hvc_iucv_path_severed,
	.message_complete = hvc_iucv_msg_complete,
	.message_pending  = hvc_iucv_msg_pending,
पूर्ण;


/**
 * hvc_iucv_get_निजी() - Return a काष्ठा hvc_iucv_निजी instance.
 * @num:	The HVC भव terminal number (vtermno)
 *
 * This function वापसs the काष्ठा hvc_iucv_निजी instance that corresponds
 * to the HVC भव terminal number specअगरied as parameter @num.
 */
अटल काष्ठा hvc_iucv_निजी *hvc_iucv_get_निजी(uपूर्णांक32_t num)
अणु
	अगर ((num < HVC_IUCV_MAGIC) || (num - HVC_IUCV_MAGIC > hvc_iucv_devices))
		वापस शून्य;
	वापस hvc_iucv_table[num - HVC_IUCV_MAGIC];
पूर्ण

/**
 * alloc_tty_buffer() - Return a new काष्ठा iucv_tty_buffer element.
 * @size:	Size of the पूर्णांकernal buffer used to store data.
 * @flags:	Memory allocation flags passed to mempool.
 *
 * This function allocates a new काष्ठा iucv_tty_buffer element and, optionally,
 * allocates an पूर्णांकernal data buffer with the specअगरied size @size.
 * The पूर्णांकernal data buffer is always allocated with GFP_DMA which is
 * required क्रम receiving and sending data with IUCV.
 * Note: The total message size arises from the पूर्णांकernal buffer size and the
 *	 members of the iucv_tty_msg काष्ठाure.
 * The function वापसs शून्य अगर memory allocation has failed.
 */
अटल काष्ठा iucv_tty_buffer *alloc_tty_buffer(माप_प्रकार size, gfp_t flags)
अणु
	काष्ठा iucv_tty_buffer *bufp;

	bufp = mempool_alloc(hvc_iucv_mempool, flags);
	अगर (!bufp)
		वापस शून्य;
	स_रखो(bufp, 0, माप(*bufp));

	अगर (size > 0) अणु
		bufp->msg.length = MSG_SIZE(size);
		bufp->mbuf = kदो_स्मृति(bufp->msg.length, flags | GFP_DMA);
		अगर (!bufp->mbuf) अणु
			mempool_मुक्त(bufp, hvc_iucv_mempool);
			वापस शून्य;
		पूर्ण
		bufp->mbuf->version = MSG_VERSION;
		bufp->mbuf->type    = MSG_TYPE_DATA;
		bufp->mbuf->datalen = (u16) size;
	पूर्ण
	वापस bufp;
पूर्ण

/**
 * destroy_tty_buffer() - destroy काष्ठा iucv_tty_buffer element.
 * @bufp:	Poपूर्णांकer to a काष्ठा iucv_tty_buffer element, SHALL NOT be शून्य.
 */
अटल व्योम destroy_tty_buffer(काष्ठा iucv_tty_buffer *bufp)
अणु
	kमुक्त(bufp->mbuf);
	mempool_मुक्त(bufp, hvc_iucv_mempool);
पूर्ण

/**
 * destroy_tty_buffer_list() - call destroy_tty_buffer() क्रम each list element.
 * @list:	List containing काष्ठा iucv_tty_buffer elements.
 */
अटल व्योम destroy_tty_buffer_list(काष्ठा list_head *list)
अणु
	काष्ठा iucv_tty_buffer *ent, *next;

	list_क्रम_each_entry_safe(ent, next, list, list) अणु
		list_del(&ent->list);
		destroy_tty_buffer(ent);
	पूर्ण
पूर्ण

/**
 * hvc_iucv_ग_लिखो() - Receive IUCV message & ग_लिखो data to HVC buffer.
 * @priv:		Poपूर्णांकer to काष्ठा hvc_iucv_निजी
 * @buf:		HVC buffer क्रम writing received terminal data.
 * @count:		HVC buffer size.
 * @has_more_data:	Poपूर्णांकer to an पूर्णांक variable.
 *
 * The function picks up pending messages from the input queue and receives
 * the message data that is then written to the specअगरied buffer @buf.
 * If the buffer size @count is less than the data message size, the
 * message is kept on the input queue and @has_more_data is set to 1.
 * If all message data has been written, the message is हटाओd from
 * the input queue.
 *
 * The function वापसs the number of bytes written to the terminal, zero अगर
 * there are no pending data messages available or अगर there is no established
 * IUCV path.
 * If the IUCV path has been severed, then -EPIPE is वापसed to cause a
 * hang up (that is issued by the HVC layer).
 */
अटल पूर्णांक hvc_iucv_ग_लिखो(काष्ठा hvc_iucv_निजी *priv,
			  अक्षर *buf, पूर्णांक count, पूर्णांक *has_more_data)
अणु
	काष्ठा iucv_tty_buffer *rb;
	पूर्णांक written;
	पूर्णांक rc;

	/* immediately वापस अगर there is no IUCV connection */
	अगर (priv->iucv_state == IUCV_DISCONN)
		वापस 0;

	/* अगर the IUCV path has been severed, वापस -EPIPE to inक्रमm the
	 * HVC layer to hang up the tty device. */
	अगर (priv->iucv_state == IUCV_SEVERED)
		वापस -EPIPE;

	/* check अगर there are pending messages */
	अगर (list_empty(&priv->tty_inqueue))
		वापस 0;

	/* receive an iucv message and flip data to the tty (ldisc) */
	rb = list_first_entry(&priv->tty_inqueue, काष्ठा iucv_tty_buffer, list);

	written = 0;
	अगर (!rb->mbuf) अणु /* message not yet received ... */
		/* allocate mem to store msg data; अगर no memory is available
		 * then leave the buffer on the list and re-try later */
		rb->mbuf = kदो_स्मृति(rb->msg.length, GFP_ATOMIC | GFP_DMA);
		अगर (!rb->mbuf)
			वापस -ENOMEM;

		rc = __iucv_message_receive(priv->path, &rb->msg, 0,
					    rb->mbuf, rb->msg.length, शून्य);
		चयन (rc) अणु
		हाल 0: /* Successful	    */
			अवरोध;
		हाल 2:	/* No message found */
		हाल 9: /* Message purged   */
			अवरोध;
		शेष:
			written = -EIO;
		पूर्ण
		/* हटाओ buffer अगर an error has occurred or received data
		 * is not correct */
		अगर (rc || (rb->mbuf->version != MSG_VERSION) ||
			  (rb->msg.length    != MSG_SIZE(rb->mbuf->datalen)))
			जाओ out_हटाओ_buffer;
	पूर्ण

	चयन (rb->mbuf->type) अणु
	हाल MSG_TYPE_DATA:
		written = min_t(पूर्णांक, rb->mbuf->datalen - rb->offset, count);
		स_नकल(buf, rb->mbuf->data + rb->offset, written);
		अगर (written < (rb->mbuf->datalen - rb->offset)) अणु
			rb->offset += written;
			*has_more_data = 1;
			जाओ out_written;
		पूर्ण
		अवरोध;

	हाल MSG_TYPE_WINSIZE:
		अगर (rb->mbuf->datalen != माप(काष्ठा winsize))
			अवरोध;
		/* The caller must ensure that the hvc is locked, which
		 * is the हाल when called from hvc_iucv_get_अक्षरs() */
		__hvc_resize(priv->hvc, *((काष्ठा winsize *) rb->mbuf->data));
		अवरोध;

	हाल MSG_TYPE_ERROR:	/* ignored ... */
	हाल MSG_TYPE_TERMENV:	/* ignored ... */
	हाल MSG_TYPE_TERMIOS:	/* ignored ... */
		अवरोध;
	पूर्ण

out_हटाओ_buffer:
	list_del(&rb->list);
	destroy_tty_buffer(rb);
	*has_more_data = !list_empty(&priv->tty_inqueue);

out_written:
	वापस written;
पूर्ण

/**
 * hvc_iucv_get_अक्षरs() - HVC get_अक्षरs operation.
 * @vtermno:	HVC भव terminal number.
 * @buf:	Poपूर्णांकer to a buffer to store data
 * @count:	Size of buffer available क्रम writing
 *
 * The HVC thपढ़ो calls this method to पढ़ो अक्षरacters from the back-end.
 * If an IUCV communication path has been established, pending IUCV messages
 * are received and data is copied पूर्णांकo buffer @buf up to @count bytes.
 *
 * Locking:	The routine माला_लो called under an irqsave() spinlock; and
 *		the routine locks the काष्ठा hvc_iucv_निजी->lock to call
 *		helper functions.
 */
अटल पूर्णांक hvc_iucv_get_अक्षरs(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvc_iucv_निजी *priv = hvc_iucv_get_निजी(vtermno);
	पूर्णांक written;
	पूर्णांक has_more_data;

	अगर (count <= 0)
		वापस 0;

	अगर (!priv)
		वापस -ENODEV;

	spin_lock(&priv->lock);
	has_more_data = 0;
	written = hvc_iucv_ग_लिखो(priv, buf, count, &has_more_data);
	spin_unlock(&priv->lock);

	/* अगर there are still messages on the queue... schedule another run */
	अगर (has_more_data)
		hvc_kick();

	वापस written;
पूर्ण

/**
 * hvc_iucv_queue() - Buffer terminal data क्रम sending.
 * @priv:	Poपूर्णांकer to काष्ठा hvc_iucv_निजी instance.
 * @buf:	Buffer containing data to send.
 * @count:	Size of buffer and amount of data to send.
 *
 * The function queues data क्रम sending. To actually send the buffered data,
 * a work queue function is scheduled (with QUEUE_SNDBUF_DELAY).
 * The function वापसs the number of data bytes that has been buffered.
 *
 * If the device is not connected, data is ignored and the function वापसs
 * @count.
 * If the buffer is full, the function वापसs 0.
 * If an existing IUCV communicaton path has been severed, -EPIPE is वापसed
 * (that can be passed to HVC layer to cause a tty hangup).
 */
अटल पूर्णांक hvc_iucv_queue(काष्ठा hvc_iucv_निजी *priv, स्थिर अक्षर *buf,
			  पूर्णांक count)
अणु
	माप_प्रकार len;

	अगर (priv->iucv_state == IUCV_DISCONN)
		वापस count;			/* ignore data */

	अगर (priv->iucv_state == IUCV_SEVERED)
		वापस -EPIPE;

	len = min_t(माप_प्रकार, count, SNDBUF_SIZE - priv->sndbuf_len);
	अगर (!len)
		वापस 0;

	स_नकल(priv->sndbuf + priv->sndbuf_len, buf, len);
	priv->sndbuf_len += len;

	अगर (priv->iucv_state == IUCV_CONNECTED)
		schedule_delayed_work(&priv->sndbuf_work, QUEUE_SNDBUF_DELAY);

	वापस len;
पूर्ण

/**
 * hvc_iucv_send() - Send an IUCV message containing terminal data.
 * @priv:	Poपूर्णांकer to काष्ठा hvc_iucv_निजी instance.
 *
 * If an IUCV communication path has been established, the buffered output data
 * is sent via an IUCV message and the number of bytes sent is वापसed.
 * Returns 0 अगर there is no established IUCV communication path or
 * -EPIPE अगर an existing IUCV communicaton path has been severed.
 */
अटल पूर्णांक hvc_iucv_send(काष्ठा hvc_iucv_निजी *priv)
अणु
	काष्ठा iucv_tty_buffer *sb;
	पूर्णांक rc, len;

	अगर (priv->iucv_state == IUCV_SEVERED)
		वापस -EPIPE;

	अगर (priv->iucv_state == IUCV_DISCONN)
		वापस -EIO;

	अगर (!priv->sndbuf_len)
		वापस 0;

	/* allocate पूर्णांकernal buffer to store msg data and also compute total
	 * message length */
	sb = alloc_tty_buffer(priv->sndbuf_len, GFP_ATOMIC);
	अगर (!sb)
		वापस -ENOMEM;

	स_नकल(sb->mbuf->data, priv->sndbuf, priv->sndbuf_len);
	sb->mbuf->datalen = (u16) priv->sndbuf_len;
	sb->msg.length = MSG_SIZE(sb->mbuf->datalen);

	list_add_tail(&sb->list, &priv->tty_outqueue);

	rc = __iucv_message_send(priv->path, &sb->msg, 0, 0,
				 (व्योम *) sb->mbuf, sb->msg.length);
	अगर (rc) अणु
		/* drop the message here; however we might want to handle
		 * 0x03 (msg limit reached) by trying again... */
		list_del(&sb->list);
		destroy_tty_buffer(sb);
	पूर्ण
	len = priv->sndbuf_len;
	priv->sndbuf_len = 0;

	वापस len;
पूर्ण

/**
 * hvc_iucv_sndbuf_work() - Send buffered data over IUCV
 * @work:	Work काष्ठाure.
 *
 * This work queue function sends buffered output data over IUCV and,
 * अगर not all buffered data could be sent, reschedules itself.
 */
अटल व्योम hvc_iucv_sndbuf_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hvc_iucv_निजी *priv;

	priv = container_of(work, काष्ठा hvc_iucv_निजी, sndbuf_work.work);
	अगर (!priv)
		वापस;

	spin_lock_bh(&priv->lock);
	hvc_iucv_send(priv);
	spin_unlock_bh(&priv->lock);
पूर्ण

/**
 * hvc_iucv_put_अक्षरs() - HVC put_अक्षरs operation.
 * @vtermno:	HVC भव terminal number.
 * @buf:	Poपूर्णांकer to an buffer to पढ़ो data from
 * @count:	Size of buffer available क्रम पढ़ोing
 *
 * The HVC thपढ़ो calls this method to ग_लिखो अक्षरacters to the back-end.
 * The function calls hvc_iucv_queue() to queue terminal data क्रम sending.
 *
 * Locking:	The method माला_लो called under an irqsave() spinlock; and
 *		locks काष्ठा hvc_iucv_निजी->lock.
 */
अटल पूर्णांक hvc_iucv_put_अक्षरs(uपूर्णांक32_t vtermno, स्थिर अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvc_iucv_निजी *priv = hvc_iucv_get_निजी(vtermno);
	पूर्णांक queued;

	अगर (count <= 0)
		वापस 0;

	अगर (!priv)
		वापस -ENODEV;

	spin_lock(&priv->lock);
	queued = hvc_iucv_queue(priv, buf, count);
	spin_unlock(&priv->lock);

	वापस queued;
पूर्ण

/**
 * hvc_iucv_notअगरier_add() - HVC notअगरier क्रम खोलोing a TTY क्रम the first समय.
 * @hp:	Poपूर्णांकer to the HVC device (काष्ठा hvc_काष्ठा)
 * @id:	Additional data (originally passed to hvc_alloc): the index of an काष्ठा
 *	hvc_iucv_निजी instance.
 *
 * The function sets the tty state to TTY_OPENED क्रम the काष्ठा hvc_iucv_निजी
 * instance that is derived from @id. Always वापसs 0.
 *
 * Locking:	काष्ठा hvc_iucv_निजी->lock, spin_lock_bh
 */
अटल पूर्णांक hvc_iucv_notअगरier_add(काष्ठा hvc_काष्ठा *hp, पूर्णांक id)
अणु
	काष्ठा hvc_iucv_निजी *priv;

	priv = hvc_iucv_get_निजी(id);
	अगर (!priv)
		वापस 0;

	spin_lock_bh(&priv->lock);
	priv->tty_state = TTY_OPENED;
	spin_unlock_bh(&priv->lock);

	वापस 0;
पूर्ण

/**
 * hvc_iucv_cleanup() - Clean up and reset a z/VM IUCV HVC instance.
 * @priv:	Poपूर्णांकer to the काष्ठा hvc_iucv_निजी instance.
 */
अटल व्योम hvc_iucv_cleanup(काष्ठा hvc_iucv_निजी *priv)
अणु
	destroy_tty_buffer_list(&priv->tty_outqueue);
	destroy_tty_buffer_list(&priv->tty_inqueue);

	priv->tty_state = TTY_CLOSED;
	priv->iucv_state = IUCV_DISCONN;

	priv->sndbuf_len = 0;
पूर्ण

/**
 * tty_outqueue_empty() - Test अगर the tty outq is empty
 * @priv:	Poपूर्णांकer to काष्ठा hvc_iucv_निजी instance.
 */
अटल अंतरभूत पूर्णांक tty_outqueue_empty(काष्ठा hvc_iucv_निजी *priv)
अणु
	पूर्णांक rc;

	spin_lock_bh(&priv->lock);
	rc = list_empty(&priv->tty_outqueue);
	spin_unlock_bh(&priv->lock);

	वापस rc;
पूर्ण

/**
 * flush_sndbuf_sync() - Flush send buffer and रुको क्रम completion
 * @priv:	Poपूर्णांकer to काष्ठा hvc_iucv_निजी instance.
 *
 * The routine cancels a pending sndbuf work, calls hvc_iucv_send()
 * to flush any buffered terminal output data and रुकोs क्रम completion.
 */
अटल व्योम flush_sndbuf_sync(काष्ठा hvc_iucv_निजी *priv)
अणु
	पूर्णांक sync_रुको;

	cancel_delayed_work_sync(&priv->sndbuf_work);

	spin_lock_bh(&priv->lock);
	hvc_iucv_send(priv);		/* क्रमce sending buffered data */
	sync_रुको = !list_empty(&priv->tty_outqueue); /* anything queued ? */
	spin_unlock_bh(&priv->lock);

	अगर (sync_रुको)
		रुको_event_समयout(priv->sndbuf_रुकोq,
				   tty_outqueue_empty(priv), HZ/10);
पूर्ण

/**
 * hvc_iucv_hangup() - Sever IUCV path and schedule hvc tty hang up
 * @priv:	Poपूर्णांकer to hvc_iucv_निजी काष्ठाure
 *
 * This routine severs an existing IUCV communication path and hangs
 * up the underlying HVC terminal device.
 * The hang-up occurs only अगर an IUCV communication path is established;
 * otherwise there is no need to hang up the terminal device.
 *
 * The IUCV HVC hang-up is separated पूर्णांकo two steps:
 * 1. After the IUCV path has been severed, the iucv_state is set to
 *    IUCV_SEVERED.
 * 2. Later, when the HVC thपढ़ो calls hvc_iucv_get_अक्षरs(), the
 *    IUCV_SEVERED state causes the tty hang-up in the HVC layer.
 *
 * If the tty has not yet been खोलोed, clean up the hvc_iucv_निजी
 * काष्ठाure to allow re-connects.
 * If the tty has been खोलोed, let get_अक्षरs() वापस -EPIPE to संकेत
 * the HVC layer to hang up the tty and, अगर so, wake up the HVC thपढ़ो
 * to call get_अक्षरs()...
 *
 * Special notes on hanging up a HVC terminal instantiated as console:
 * Hang-up:	1. करो_tty_hangup() replaces file ops (= hung_up_tty_fops)
 *		2. करो_tty_hangup() calls tty->ops->बंद() क्रम console_filp
 *			=> no hangup notअगरier is called by HVC (शेष)
 *		2. hvc_बंद() वापसs because of tty_hung_up_p(filp)
 *			=> no delete notअगरier is called!
 * Finally, the back-end is not being notअगरied, thus, the tty session is
 * kept active (TTY_OPEN) to be पढ़ोy क्रम re-connects.
 *
 * Locking:	spin_lock(&priv->lock) w/o disabling bh
 */
अटल व्योम hvc_iucv_hangup(काष्ठा hvc_iucv_निजी *priv)
अणु
	काष्ठा iucv_path *path;

	path = शून्य;
	spin_lock(&priv->lock);
	अगर (priv->iucv_state == IUCV_CONNECTED) अणु
		path = priv->path;
		priv->path = शून्य;
		priv->iucv_state = IUCV_SEVERED;
		अगर (priv->tty_state == TTY_CLOSED)
			hvc_iucv_cleanup(priv);
		अन्यथा
			/* console is special (see above) */
			अगर (priv->is_console) अणु
				hvc_iucv_cleanup(priv);
				priv->tty_state = TTY_OPENED;
			पूर्ण अन्यथा
				hvc_kick();
	पूर्ण
	spin_unlock(&priv->lock);

	/* finally sever path (outside of priv->lock due to lock ordering) */
	अगर (path) अणु
		iucv_path_sever(path, शून्य);
		iucv_path_मुक्त(path);
	पूर्ण
पूर्ण

/**
 * hvc_iucv_notअगरier_hangup() - HVC notअगरier क्रम TTY hangups.
 * @hp:		Poपूर्णांकer to the HVC device (काष्ठा hvc_काष्ठा)
 * @id:		Additional data (originally passed to hvc_alloc):
 *		the index of an काष्ठा hvc_iucv_निजी instance.
 *
 * This routine notअगरies the HVC back-end that a tty hangup (carrier loss,
 * भव or otherwise) has occurred.
 * The z/VM IUCV HVC device driver ignores भव hangups (vhangup())
 * to keep an existing IUCV communication path established.
 * (Background: vhangup() is called from user space (by getty or login) to
 *		disable writing to the tty by other applications).
 * If the tty has been खोलोed and an established IUCV path has been severed
 * (we caused the tty hangup), the function calls hvc_iucv_cleanup().
 *
 * Locking:	काष्ठा hvc_iucv_निजी->lock
 */
अटल व्योम hvc_iucv_notअगरier_hangup(काष्ठा hvc_काष्ठा *hp, पूर्णांक id)
अणु
	काष्ठा hvc_iucv_निजी *priv;

	priv = hvc_iucv_get_निजी(id);
	अगर (!priv)
		वापस;

	flush_sndbuf_sync(priv);

	spin_lock_bh(&priv->lock);
	/* NOTE: If the hangup was scheduled by ourself (from the iucv
	 *	 path_servered callback [IUCV_SEVERED]), we have to clean up
	 *	 our काष्ठाure and to set state to TTY_CLOSED.
	 *	 If the tty was hung up otherwise (e.g. vhangup()), then we
	 *	 ignore this hangup and keep an established IUCV path खोलो...
	 *	 (...the reason is that we are not able to connect back to the
	 *	 client अगर we disconnect on hang up) */
	priv->tty_state = TTY_CLOSED;

	अगर (priv->iucv_state == IUCV_SEVERED)
		hvc_iucv_cleanup(priv);
	spin_unlock_bh(&priv->lock);
पूर्ण

/**
 * hvc_iucv_dtr_rts() - HVC notअगरier क्रम handling DTR/RTS
 * @hp:		Poपूर्णांकer the HVC device (काष्ठा hvc_काष्ठा)
 * @उठाओ:	Non-zero to उठाओ or zero to lower DTR/RTS lines
 *
 * This routine notअगरies the HVC back-end to उठाओ or lower DTR/RTS
 * lines.  Raising DTR/RTS is ignored.  Lowering DTR/RTS indicates to
 * drop the IUCV connection (similar to hang up the modem).
 */
अटल व्योम hvc_iucv_dtr_rts(काष्ठा hvc_काष्ठा *hp, पूर्णांक उठाओ)
अणु
	काष्ठा hvc_iucv_निजी *priv;
	काष्ठा iucv_path        *path;

	/* Raising the DTR/RTS is ignored as IUCV connections can be
	 * established at any बार.
	 */
	अगर (उठाओ)
		वापस;

	priv = hvc_iucv_get_निजी(hp->vtermno);
	अगर (!priv)
		वापस;

	/* Lowering the DTR/RTS lines disconnects an established IUCV
	 * connection.
	 */
	flush_sndbuf_sync(priv);

	spin_lock_bh(&priv->lock);
	path = priv->path;		/* save reference to IUCV path */
	priv->path = शून्य;
	priv->iucv_state = IUCV_DISCONN;
	spin_unlock_bh(&priv->lock);

	/* Sever IUCV path outside of priv->lock due to lock ordering of:
	 * priv->lock <--> iucv_table_lock */
	अगर (path) अणु
		iucv_path_sever(path, शून्य);
		iucv_path_मुक्त(path);
	पूर्ण
पूर्ण

/**
 * hvc_iucv_notअगरier_del() - HVC notअगरier क्रम closing a TTY क्रम the last समय.
 * @hp:		Poपूर्णांकer to the HVC device (काष्ठा hvc_काष्ठा)
 * @id:		Additional data (originally passed to hvc_alloc):
 *		the index of an काष्ठा hvc_iucv_निजी instance.
 *
 * This routine notअगरies the HVC back-end that the last tty device fd has been
 * बंदd.  The function cleans up tty resources.  The clean-up of the IUCV
 * connection is करोne in hvc_iucv_dtr_rts() and depends on the HUPCL termios
 * control setting.
 *
 * Locking:	काष्ठा hvc_iucv_निजी->lock
 */
अटल व्योम hvc_iucv_notअगरier_del(काष्ठा hvc_काष्ठा *hp, पूर्णांक id)
अणु
	काष्ठा hvc_iucv_निजी *priv;

	priv = hvc_iucv_get_निजी(id);
	अगर (!priv)
		वापस;

	flush_sndbuf_sync(priv);

	spin_lock_bh(&priv->lock);
	destroy_tty_buffer_list(&priv->tty_outqueue);
	destroy_tty_buffer_list(&priv->tty_inqueue);
	priv->tty_state = TTY_CLOSED;
	priv->sndbuf_len = 0;
	spin_unlock_bh(&priv->lock);
पूर्ण

/**
 * hvc_iucv_filter_connreq() - Filter connection request based on z/VM user ID
 * @ipvmid:	Originating z/VM user ID (right padded with blanks)
 *
 * Returns 0 अगर the z/VM user ID that is specअगरied with @ipvmid is permitted to
 * connect, otherwise non-zero.
 */
अटल पूर्णांक hvc_iucv_filter_connreq(u8 ipvmid[8])
अणु
	स्थिर अक्षर *wildcard, *filter_entry;
	माप_प्रकार i, len;

	/* Note: शेष policy is ACCEPT अगर no filter is set */
	अगर (!hvc_iucv_filter_size)
		वापस 0;

	क्रम (i = 0; i < hvc_iucv_filter_size; i++) अणु
		filter_entry = hvc_iucv_filter + (8 * i);

		/* If a filter entry contains the filter wildcard अक्षरacter,
		 * reduce the length to match the leading portion of the user
		 * ID only (wildcard match).  Characters following the wildcard
		 * are ignored.
		 */
		wildcard = strnchr(filter_entry, 8, FILTER_WILDCARD_CHAR);
		len = (wildcard) ? wildcard - filter_entry : 8;
		अगर (0 == स_भेद(ipvmid, filter_entry, len))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/**
 * hvc_iucv_path_pending() - IUCV handler to process a connection request.
 * @path:	Pending path (काष्ठा iucv_path)
 * @ipvmid:	z/VM प्रणाली identअगरier of originator
 * @ipuser:	User specअगरied data क्रम this path
 *		(AF_IUCV: port/service name and originator port)
 *
 * The function uses the @ipuser data to determine अगर the pending path beदीर्घs
 * to a terminal managed by this device driver.
 * If the path beदीर्घs to this driver, ensure that the terminal is not accessed
 * multiple बार (only one connection to a terminal is allowed).
 * If the terminal is not yet connected, the pending path is accepted and is
 * associated to the appropriate काष्ठा hvc_iucv_निजी instance.
 *
 * Returns 0 अगर @path beदीर्घs to a terminal managed by the this device driver;
 * otherwise वापसs -ENODEV in order to dispatch this path to other handlers.
 *
 * Locking:	काष्ठा hvc_iucv_निजी->lock
 */
अटल	पूर्णांक hvc_iucv_path_pending(काष्ठा iucv_path *path, u8 *ipvmid,
				  u8 *ipuser)
अणु
	काष्ठा hvc_iucv_निजी *priv, *पंचांगp;
	u8 wildcard[9] = "lnxhvc  ";
	पूर्णांक i, rc, find_unused;
	u8 nuser_data[16];
	u8 vm_user_id[9];

	ASCEBC(wildcard, माप(wildcard));
	find_unused = !स_भेद(wildcard, ipuser, 8);

	/* First, check अगर the pending path request is managed by this
	 * IUCV handler:
	 * - find a disconnected device अगर ipuser contains the wildcard
	 * - find the device that matches the terminal ID in ipuser
	 */
	priv = शून्य;
	क्रम (i = 0; i < hvc_iucv_devices; i++) अणु
		पंचांगp = hvc_iucv_table[i];
		अगर (!पंचांगp)
			जारी;

		अगर (find_unused) अणु
			spin_lock(&पंचांगp->lock);
			अगर (पंचांगp->iucv_state == IUCV_DISCONN)
				priv = पंचांगp;
			spin_unlock(&पंचांगp->lock);

		पूर्ण अन्यथा अगर (!स_भेद(पंचांगp->srv_name, ipuser, 8))
				priv = पंचांगp;
		अगर (priv)
			अवरोध;
	पूर्ण
	अगर (!priv)
		वापस -ENODEV;

	/* Enक्रमce that ipvmid is allowed to connect to us */
	पढ़ो_lock(&hvc_iucv_filter_lock);
	rc = hvc_iucv_filter_connreq(ipvmid);
	पढ़ो_unlock(&hvc_iucv_filter_lock);
	अगर (rc) अणु
		iucv_path_sever(path, ipuser);
		iucv_path_मुक्त(path);
		स_नकल(vm_user_id, ipvmid, 8);
		vm_user_id[8] = 0;
		pr_info("A connection request from z/VM user ID %s "
			"was refused\n", vm_user_id);
		वापस 0;
	पूर्ण

	spin_lock(&priv->lock);

	/* If the terminal is alपढ़ोy connected or being severed, then sever
	 * this path to enक्रमce that there is only ONE established communication
	 * path per terminal. */
	अगर (priv->iucv_state != IUCV_DISCONN) अणु
		iucv_path_sever(path, ipuser);
		iucv_path_मुक्त(path);
		जाओ out_path_handled;
	पूर्ण

	/* accept path */
	स_नकल(nuser_data, ipuser + 8, 8);  /* remote service (क्रम af_iucv) */
	स_नकल(nuser_data + 8, ipuser, 8);  /* local service  (क्रम af_iucv) */
	path->msglim = 0xffff;		    /* IUCV MSGLIMIT */
	path->flags &= ~IUCV_IPRMDATA;	    /* TODO: use IUCV_IPRMDATA */
	rc = iucv_path_accept(path, &hvc_iucv_handler, nuser_data, priv);
	अगर (rc) अणु
		iucv_path_sever(path, ipuser);
		iucv_path_मुक्त(path);
		जाओ out_path_handled;
	पूर्ण
	priv->path = path;
	priv->iucv_state = IUCV_CONNECTED;

	/* store path inक्रमmation */
	स_नकल(priv->info_path, ipvmid, 8);
	स_नकल(priv->info_path + 8, ipuser + 8, 8);

	/* flush buffered output data... */
	schedule_delayed_work(&priv->sndbuf_work, 5);

out_path_handled:
	spin_unlock(&priv->lock);
	वापस 0;
पूर्ण

/**
 * hvc_iucv_path_severed() - IUCV handler to process a path sever.
 * @path:	Pending path (काष्ठा iucv_path)
 * @ipuser:	User specअगरied data क्रम this path
 *		(AF_IUCV: port/service name and originator port)
 *
 * This function calls the hvc_iucv_hangup() function क्रम the
 * respective IUCV HVC terminal.
 *
 * Locking:	काष्ठा hvc_iucv_निजी->lock
 */
अटल व्योम hvc_iucv_path_severed(काष्ठा iucv_path *path, u8 *ipuser)
अणु
	काष्ठा hvc_iucv_निजी *priv = path->निजी;

	hvc_iucv_hangup(priv);
पूर्ण

/**
 * hvc_iucv_msg_pending() - IUCV handler to process an incoming IUCV message.
 * @path:	Pending path (काष्ठा iucv_path)
 * @msg:	Poपूर्णांकer to the IUCV message
 *
 * The function माला_दो an incoming message on the input queue क्रम later
 * processing (by hvc_iucv_get_अक्षरs() / hvc_iucv_ग_लिखो()).
 * If the tty has not yet been खोलोed, the message is rejected.
 *
 * Locking:	काष्ठा hvc_iucv_निजी->lock
 */
अटल व्योम hvc_iucv_msg_pending(काष्ठा iucv_path *path,
				 काष्ठा iucv_message *msg)
अणु
	काष्ठा hvc_iucv_निजी *priv = path->निजी;
	काष्ठा iucv_tty_buffer *rb;

	/* reject messages that exceed max size of iucv_tty_msg->datalen */
	अगर (msg->length > MSG_SIZE(MSG_MAX_DATALEN)) अणु
		iucv_message_reject(path, msg);
		वापस;
	पूर्ण

	spin_lock(&priv->lock);

	/* reject messages अगर tty has not yet been खोलोed */
	अगर (priv->tty_state == TTY_CLOSED) अणु
		iucv_message_reject(path, msg);
		जाओ unlock_वापस;
	पूर्ण

	/* allocate tty buffer to save iucv msg only */
	rb = alloc_tty_buffer(0, GFP_ATOMIC);
	अगर (!rb) अणु
		iucv_message_reject(path, msg);
		जाओ unlock_वापस;	/* -ENOMEM */
	पूर्ण
	rb->msg = *msg;

	list_add_tail(&rb->list, &priv->tty_inqueue);

	hvc_kick();	/* wake up hvc thपढ़ो */

unlock_वापस:
	spin_unlock(&priv->lock);
पूर्ण

/**
 * hvc_iucv_msg_complete() - IUCV handler to process message completion
 * @path:	Pending path (काष्ठा iucv_path)
 * @msg:	Poपूर्णांकer to the IUCV message
 *
 * The function is called upon completion of message delivery to हटाओ the
 * message from the outqueue. Additional delivery inक्रमmation can be found
 * msg->audit: rejected messages (0x040000 (IPADRJCT)), and
 *	       purged messages	 (0x010000 (IPADPGNR)).
 *
 * Locking:	काष्ठा hvc_iucv_निजी->lock
 */
अटल व्योम hvc_iucv_msg_complete(काष्ठा iucv_path *path,
				  काष्ठा iucv_message *msg)
अणु
	काष्ठा hvc_iucv_निजी *priv = path->निजी;
	काष्ठा iucv_tty_buffer	*ent, *next;
	LIST_HEAD(list_हटाओ);

	spin_lock(&priv->lock);
	list_क्रम_each_entry_safe(ent, next, &priv->tty_outqueue, list)
		अगर (ent->msg.id == msg->id) अणु
			list_move(&ent->list, &list_हटाओ);
			अवरोध;
		पूर्ण
	wake_up(&priv->sndbuf_रुकोq);
	spin_unlock(&priv->lock);
	destroy_tty_buffer_list(&list_हटाओ);
पूर्ण

/**
 * hvc_iucv_pm_मुक्तze() - Freeze PM callback
 * @dev:	IUVC HVC terminal device
 *
 * Sever an established IUCV communication path and
 * trigger a hang-up of the underlying HVC terminal.
 */
अटल पूर्णांक hvc_iucv_pm_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा hvc_iucv_निजी *priv = dev_get_drvdata(dev);

	local_bh_disable();
	hvc_iucv_hangup(priv);
	local_bh_enable();

	वापस 0;
पूर्ण

/**
 * hvc_iucv_pm_restore_thaw() - Thaw and restore PM callback
 * @dev:	IUVC HVC terminal device
 *
 * Wake up the HVC thपढ़ो to trigger hang-up and respective
 * HVC back-end notअगरier invocations.
 */
अटल पूर्णांक hvc_iucv_pm_restore_thaw(काष्ठा device *dev)
अणु
	hvc_kick();
	वापस 0;
पूर्ण

अटल sमाप_प्रकार hvc_iucv_dev_termid_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा hvc_iucv_निजी *priv = dev_get_drvdata(dev);
	माप_प्रकार len;

	len = माप(priv->srv_name);
	स_नकल(buf, priv->srv_name, len);
	EBCASC(buf, len);
	buf[len++] = '\n';
	वापस len;
पूर्ण

अटल sमाप_प्रकार hvc_iucv_dev_state_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा hvc_iucv_निजी *priv = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%u:%u\n", priv->iucv_state, priv->tty_state);
पूर्ण

अटल sमाप_प्रकार hvc_iucv_dev_peer_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा hvc_iucv_निजी *priv = dev_get_drvdata(dev);
	अक्षर vmid[9], ipuser[9];

	स_रखो(vmid, 0, माप(vmid));
	स_रखो(ipuser, 0, माप(ipuser));

	spin_lock_bh(&priv->lock);
	अगर (priv->iucv_state == IUCV_CONNECTED) अणु
		स_नकल(vmid, priv->info_path, 8);
		स_नकल(ipuser, priv->info_path + 8, 8);
	पूर्ण
	spin_unlock_bh(&priv->lock);
	EBCASC(ipuser, 8);

	वापस प्र_लिखो(buf, "%s:%s\n", vmid, ipuser);
पूर्ण


/* HVC operations */
अटल स्थिर काष्ठा hv_ops hvc_iucv_ops = अणु
	.get_अक्षरs = hvc_iucv_get_अक्षरs,
	.put_अक्षरs = hvc_iucv_put_अक्षरs,
	.notअगरier_add = hvc_iucv_notअगरier_add,
	.notअगरier_del = hvc_iucv_notअगरier_del,
	.notअगरier_hangup = hvc_iucv_notअगरier_hangup,
	.dtr_rts = hvc_iucv_dtr_rts,
पूर्ण;

/* Suspend / resume device operations */
अटल स्थिर काष्ठा dev_pm_ops hvc_iucv_pm_ops = अणु
	.मुक्तze	  = hvc_iucv_pm_मुक्तze,
	.thaw	  = hvc_iucv_pm_restore_thaw,
	.restore  = hvc_iucv_pm_restore_thaw,
पूर्ण;

/* IUCV HVC device driver */
अटल काष्ठा device_driver hvc_iucv_driver = अणु
	.name = KMSG_COMPONENT,
	.bus  = &iucv_bus,
	.pm   = &hvc_iucv_pm_ops,
पूर्ण;

/* IUCV HVC device attributes */
अटल DEVICE_ATTR(termid, 0640, hvc_iucv_dev_termid_show, शून्य);
अटल DEVICE_ATTR(state, 0640, hvc_iucv_dev_state_show, शून्य);
अटल DEVICE_ATTR(peer, 0640, hvc_iucv_dev_peer_show, शून्य);
अटल काष्ठा attribute *hvc_iucv_dev_attrs[] = अणु
	&dev_attr_termid.attr,
	&dev_attr_state.attr,
	&dev_attr_peer.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group hvc_iucv_dev_attr_group = अणु
	.attrs = hvc_iucv_dev_attrs,
पूर्ण;
अटल स्थिर काष्ठा attribute_group *hvc_iucv_dev_attr_groups[] = अणु
	&hvc_iucv_dev_attr_group,
	शून्य,
पूर्ण;


/**
 * hvc_iucv_alloc() - Allocates a new काष्ठा hvc_iucv_निजी instance
 * @id:			hvc_iucv_table index
 * @is_console:		Flag अगर the instance is used as Linux console
 *
 * This function allocates a new hvc_iucv_निजी काष्ठाure and stores
 * the instance in hvc_iucv_table at index @id.
 * Returns 0 on success; otherwise non-zero.
 */
अटल पूर्णांक __init hvc_iucv_alloc(पूर्णांक id, अचिन्हित पूर्णांक is_console)
अणु
	काष्ठा hvc_iucv_निजी *priv;
	अक्षर name[9];
	पूर्णांक rc;

	priv = kzalloc(माप(काष्ठा hvc_iucv_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);
	INIT_LIST_HEAD(&priv->tty_outqueue);
	INIT_LIST_HEAD(&priv->tty_inqueue);
	INIT_DELAYED_WORK(&priv->sndbuf_work, hvc_iucv_sndbuf_work);
	init_रुकोqueue_head(&priv->sndbuf_रुकोq);

	priv->sndbuf = (व्योम *) get_zeroed_page(GFP_KERNEL);
	अगर (!priv->sndbuf) अणु
		kमुक्त(priv);
		वापस -ENOMEM;
	पूर्ण

	/* set console flag */
	priv->is_console = is_console;

	/* allocate hvc device */
	priv->hvc = hvc_alloc(HVC_IUCV_MAGIC + id, /*		  PAGE_SIZE */
			      HVC_IUCV_MAGIC + id, &hvc_iucv_ops, 256);
	अगर (IS_ERR(priv->hvc)) अणु
		rc = PTR_ERR(priv->hvc);
		जाओ out_error_hvc;
	पूर्ण

	/* notअगरy HVC thपढ़ो instead of using polling */
	priv->hvc->irq_requested = 1;

	/* setup iucv related inक्रमmation */
	snम_लिखो(name, 9, "lnxhvc%-2d", id);
	स_नकल(priv->srv_name, name, 8);
	ASCEBC(priv->srv_name, 8);

	/* create and setup device */
	priv->dev = kzalloc(माप(*priv->dev), GFP_KERNEL);
	अगर (!priv->dev) अणु
		rc = -ENOMEM;
		जाओ out_error_dev;
	पूर्ण
	dev_set_name(priv->dev, "hvc_iucv%d", id);
	dev_set_drvdata(priv->dev, priv);
	priv->dev->bus = &iucv_bus;
	priv->dev->parent = iucv_root;
	priv->dev->driver = &hvc_iucv_driver;
	priv->dev->groups = hvc_iucv_dev_attr_groups;
	priv->dev->release = (व्योम (*)(काष्ठा device *)) kमुक्त;
	rc = device_रेजिस्टर(priv->dev);
	अगर (rc) अणु
		put_device(priv->dev);
		जाओ out_error_dev;
	पूर्ण

	hvc_iucv_table[id] = priv;
	वापस 0;

out_error_dev:
	hvc_हटाओ(priv->hvc);
out_error_hvc:
	मुक्त_page((अचिन्हित दीर्घ) priv->sndbuf);
	kमुक्त(priv);

	वापस rc;
पूर्ण

/**
 * hvc_iucv_destroy() - Destroy and मुक्त hvc_iucv_निजी instances
 */
अटल व्योम __init hvc_iucv_destroy(काष्ठा hvc_iucv_निजी *priv)
अणु
	hvc_हटाओ(priv->hvc);
	device_unरेजिस्टर(priv->dev);
	मुक्त_page((अचिन्हित दीर्घ) priv->sndbuf);
	kमुक्त(priv);
पूर्ण

/**
 * hvc_iucv_parse_filter() - Parse filter क्रम a single z/VM user ID
 * @filter:	String containing a comma-separated list of z/VM user IDs
 * @dest:	Location where to store the parsed z/VM user ID
 */
अटल स्थिर अक्षर *hvc_iucv_parse_filter(स्थिर अक्षर *filter, अक्षर *dest)
अणु
	स्थिर अक्षर *nextdelim, *residual;
	माप_प्रकार len;

	nextdelim = म_अक्षर(filter, ',');
	अगर (nextdelim) अणु
		len = nextdelim - filter;
		residual = nextdelim + 1;
	पूर्ण अन्यथा अणु
		len = म_माप(filter);
		residual = filter + len;
	पूर्ण

	अगर (len == 0)
		वापस ERR_PTR(-EINVAL);

	/* check क्रम '\n' (अगर called from sysfs) */
	अगर (filter[len - 1] == '\n')
		len--;

	/* prohibit filter entries containing the wildcard अक्षरacter only */
	अगर (len == 1 && *filter == FILTER_WILDCARD_CHAR)
		वापस ERR_PTR(-EINVAL);

	अगर (len > 8)
		वापस ERR_PTR(-EINVAL);

	/* pad with blanks and save upper हाल version of user ID */
	स_रखो(dest, ' ', 8);
	जबतक (len--)
		dest[len] = बड़े(filter[len]);
	वापस residual;
पूर्ण

/**
 * hvc_iucv_setup_filter() - Set up z/VM user ID filter
 * @filter:	String consisting of a comma-separated list of z/VM user IDs
 *
 * The function parses the @filter string and creates an array containing
 * the list of z/VM user ID filter entries.
 * Return code 0 means success, -EINVAL अगर the filter is syntactically
 * incorrect, -ENOMEM अगर there was not enough memory to allocate the
 * filter list array, or -ENOSPC अगर too many z/VM user IDs have been specअगरied.
 */
अटल पूर्णांक hvc_iucv_setup_filter(स्थिर अक्षर *val)
अणु
	स्थिर अक्षर *residual;
	पूर्णांक err;
	माप_प्रकार size, count;
	व्योम *array, *old_filter;

	count = म_माप(val);
	अगर (count == 0 || (count == 1 && val[0] == '\n')) अणु
		size  = 0;
		array = शून्य;
		जाओ out_replace_filter;	/* clear filter */
	पूर्ण

	/* count user IDs in order to allocate sufficient memory */
	size = 1;
	residual = val;
	जबतक ((residual = म_अक्षर(residual, ',')) != शून्य) अणु
		residual++;
		size++;
	पूर्ण

	/* check अगर the specअगरied list exceeds the filter limit */
	अगर (size > MAX_VMID_FILTER)
		वापस -ENOSPC;

	array = kसुस्मृति(size, 8, GFP_KERNEL);
	अगर (!array)
		वापस -ENOMEM;

	count = size;
	residual = val;
	जबतक (*residual && count) अणु
		residual = hvc_iucv_parse_filter(residual,
						 array + ((size - count) * 8));
		अगर (IS_ERR(residual)) अणु
			err = PTR_ERR(residual);
			kमुक्त(array);
			जाओ out_err;
		पूर्ण
		count--;
	पूर्ण

out_replace_filter:
	ग_लिखो_lock_bh(&hvc_iucv_filter_lock);
	old_filter = hvc_iucv_filter;
	hvc_iucv_filter_size = size;
	hvc_iucv_filter = array;
	ग_लिखो_unlock_bh(&hvc_iucv_filter_lock);
	kमुक्त(old_filter);

	err = 0;
out_err:
	वापस err;
पूर्ण

/**
 * param_set_vmidfilter() - Set z/VM user ID filter parameter
 * @val:	String consisting of a comma-separated list of z/VM user IDs
 * @kp:		Kernel parameter poपूर्णांकing to hvc_iucv_filter array
 *
 * The function sets up the z/VM user ID filter specअगरied as comma-separated
 * list of user IDs in @val.
 * Note: If it is called early in the boot process, @val is stored and
 *	 parsed later in hvc_iucv_init().
 */
अटल पूर्णांक param_set_vmidfilter(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक rc;

	अगर (!MACHINE_IS_VM || !hvc_iucv_devices)
		वापस -ENODEV;

	अगर (!val)
		वापस -EINVAL;

	rc = 0;
	अगर (slab_is_available())
		rc = hvc_iucv_setup_filter(val);
	अन्यथा
		hvc_iucv_filter_string = val;	/* defer... */
	वापस rc;
पूर्ण

/**
 * param_get_vmidfilter() - Get z/VM user ID filter
 * @buffer:	Buffer to store z/VM user ID filter,
 *		(buffer size assumption PAGE_SIZE)
 * @kp:		Kernel parameter poपूर्णांकing to the hvc_iucv_filter array
 *
 * The function stores the filter as a comma-separated list of z/VM user IDs
 * in @buffer. Typically, sysfs routines call this function क्रम attr show.
 */
अटल पूर्णांक param_get_vmidfilter(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक rc;
	माप_प्रकार index, len;
	व्योम *start, *end;

	अगर (!MACHINE_IS_VM || !hvc_iucv_devices)
		वापस -ENODEV;

	rc = 0;
	पढ़ो_lock_bh(&hvc_iucv_filter_lock);
	क्रम (index = 0; index < hvc_iucv_filter_size; index++) अणु
		start = hvc_iucv_filter + (8 * index);
		end   = स_प्रथम(start, ' ', 8);
		len   = (end) ? end - start : 8;
		स_नकल(buffer + rc, start, len);
		rc += len;
		buffer[rc++] = ',';
	पूर्ण
	पढ़ो_unlock_bh(&hvc_iucv_filter_lock);
	अगर (rc)
		buffer[--rc] = '\0';	/* replace last comma and update rc */
	वापस rc;
पूर्ण

#घोषणा param_check_vmidfilter(name, p) __param_check(name, p, व्योम)

अटल स्थिर काष्ठा kernel_param_ops param_ops_vmidfilter = अणु
	.set = param_set_vmidfilter,
	.get = param_get_vmidfilter,
पूर्ण;

/**
 * hvc_iucv_init() - z/VM IUCV HVC device driver initialization
 */
अटल पूर्णांक __init hvc_iucv_init(व्योम)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक i;

	अगर (!hvc_iucv_devices)
		वापस -ENODEV;

	अगर (!MACHINE_IS_VM) अणु
		pr_notice("The z/VM IUCV HVC device driver cannot "
			   "be used without z/VM\n");
		rc = -ENODEV;
		जाओ out_error;
	पूर्ण

	अगर (hvc_iucv_devices > MAX_HVC_IUCV_LINES) अणु
		pr_err("%lu is not a valid value for the hvc_iucv= "
			"kernel parameter\n", hvc_iucv_devices);
		rc = -EINVAL;
		जाओ out_error;
	पूर्ण

	/* रेजिस्टर IUCV HVC device driver */
	rc = driver_रेजिस्टर(&hvc_iucv_driver);
	अगर (rc)
		जाओ out_error;

	/* parse hvc_iucv_allow string and create z/VM user ID filter list */
	अगर (hvc_iucv_filter_string) अणु
		rc = hvc_iucv_setup_filter(hvc_iucv_filter_string);
		चयन (rc) अणु
		हाल 0:
			अवरोध;
		हाल -ENOMEM:
			pr_err("Allocating memory failed with "
				"reason code=%d\n", 3);
			जाओ out_error;
		हाल -EINVAL:
			pr_err("hvc_iucv_allow= does not specify a valid "
				"z/VM user ID list\n");
			जाओ out_error;
		हाल -ENOSPC:
			pr_err("hvc_iucv_allow= specifies too many "
				"z/VM user IDs\n");
			जाओ out_error;
		शेष:
			जाओ out_error;
		पूर्ण
	पूर्ण

	hvc_iucv_buffer_cache = kmem_cache_create(KMSG_COMPONENT,
					   माप(काष्ठा iucv_tty_buffer),
					   0, 0, शून्य);
	अगर (!hvc_iucv_buffer_cache) अणु
		pr_err("Allocating memory failed with reason code=%d\n", 1);
		rc = -ENOMEM;
		जाओ out_error;
	पूर्ण

	hvc_iucv_mempool = mempool_create_slab_pool(MEMPOOL_MIN_NR,
						    hvc_iucv_buffer_cache);
	अगर (!hvc_iucv_mempool) अणु
		pr_err("Allocating memory failed with reason code=%d\n", 2);
		kmem_cache_destroy(hvc_iucv_buffer_cache);
		rc = -ENOMEM;
		जाओ out_error;
	पूर्ण

	/* रेजिस्टर the first terminal device as console
	 * (must be करोne beक्रमe allocating hvc terminal devices) */
	rc = hvc_instantiate(HVC_IUCV_MAGIC, IUCV_HVC_CON_IDX, &hvc_iucv_ops);
	अगर (rc) अणु
		pr_err("Registering HVC terminal device as "
		       "Linux console failed\n");
		जाओ out_error_memory;
	पूर्ण

	/* allocate hvc_iucv_निजी काष्ठाs */
	क्रम (i = 0; i < hvc_iucv_devices; i++) अणु
		rc = hvc_iucv_alloc(i, (i == IUCV_HVC_CON_IDX) ? 1 : 0);
		अगर (rc) अणु
			pr_err("Creating a new HVC terminal device "
				"failed with error code=%d\n", rc);
			जाओ out_error_hvc;
		पूर्ण
	पूर्ण

	/* रेजिस्टर IUCV callback handler */
	rc = iucv_रेजिस्टर(&hvc_iucv_handler, 0);
	अगर (rc) अणु
		pr_err("Registering IUCV handlers failed with error code=%d\n",
			rc);
		जाओ out_error_hvc;
	पूर्ण

	वापस 0;

out_error_hvc:
	क्रम (i = 0; i < hvc_iucv_devices; i++)
		अगर (hvc_iucv_table[i])
			hvc_iucv_destroy(hvc_iucv_table[i]);
out_error_memory:
	mempool_destroy(hvc_iucv_mempool);
	kmem_cache_destroy(hvc_iucv_buffer_cache);
out_error:
	kमुक्त(hvc_iucv_filter);
	hvc_iucv_devices = 0; /* ensure that we करो not provide any device */
	वापस rc;
पूर्ण

/**
 * hvc_iucv_config() - Parsing of hvc_iucv=  kernel command line parameter
 * @val:	Parameter value (numeric)
 */
अटल	पूर्णांक __init hvc_iucv_config(अक्षर *val)
अणु
	 वापस kम_से_अदीर्घ(val, 10, &hvc_iucv_devices);
पूर्ण


device_initcall(hvc_iucv_init);
__setup("hvc_iucv=", hvc_iucv_config);
core_param(hvc_iucv_allow, hvc_iucv_filter, vmidfilter, 0640);
