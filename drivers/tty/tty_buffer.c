<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Tty buffer allocation management
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/ratelimit.h>
#समावेश "tty.h"

#घोषणा MIN_TTYB_SIZE	256
#घोषणा TTYB_ALIGN_MASK	255

/*
 * Byte threshold to limit memory consumption क्रम flip buffers.
 * The actual memory limit is > 2x this amount.
 */
#घोषणा TTYB_DEFAULT_MEM_LIMIT	(640 * 1024UL)

/*
 * We शेष to dicing tty buffer allocations to this many अक्षरacters
 * in order to aव्योम multiple page allocations. We know the size of
 * tty_buffer itself but it must also be taken पूर्णांकo account that the
 * the buffer is 256 byte aligned. See tty_buffer_find क्रम the allocation
 * logic this must match
 */

#घोषणा TTY_BUFFER_PAGE	(((PAGE_SIZE - माप(काष्ठा tty_buffer)) / 2) & ~0xFF)

/**
 *	tty_buffer_lock_exclusive	-	gain exclusive access to buffer
 *	tty_buffer_unlock_exclusive	-	release exclusive access
 *
 *	@port: tty port owning the flip buffer
 *
 *	Guarantees safe use of the line discipline's receive_buf() method by
 *	excluding the buffer work and any pending flush from using the flip
 *	buffer. Data can जारी to be added concurrently to the flip buffer
 *	from the driver side.
 *
 *	On release, the buffer work is restarted अगर there is data in the
 *	flip buffer
 */

व्योम tty_buffer_lock_exclusive(काष्ठा tty_port *port)
अणु
	काष्ठा tty_bufhead *buf = &port->buf;

	atomic_inc(&buf->priority);
	mutex_lock(&buf->lock);
पूर्ण
EXPORT_SYMBOL_GPL(tty_buffer_lock_exclusive);

व्योम tty_buffer_unlock_exclusive(काष्ठा tty_port *port)
अणु
	काष्ठा tty_bufhead *buf = &port->buf;
	पूर्णांक restart;

	restart = buf->head->commit != buf->head->पढ़ो;

	atomic_dec(&buf->priority);
	mutex_unlock(&buf->lock);
	अगर (restart)
		queue_work(प्रणाली_unbound_wq, &buf->work);
पूर्ण
EXPORT_SYMBOL_GPL(tty_buffer_unlock_exclusive);

/**
 *	tty_buffer_space_avail	-	वापस unused buffer space
 *	@port: tty port owning the flip buffer
 *
 *	Returns the # of bytes which can be written by the driver without
 *	reaching the buffer limit.
 *
 *	Note: this करोes not guarantee that memory is available to ग_लिखो
 *	the वापसed # of bytes (use tty_prepare_flip_string_xxx() to
 *	pre-allocate अगर memory guarantee is required).
 */

पूर्णांक tty_buffer_space_avail(काष्ठा tty_port *port)
अणु
	पूर्णांक space = port->buf.mem_limit - atomic_पढ़ो(&port->buf.mem_used);
	वापस max(space, 0);
पूर्ण
EXPORT_SYMBOL_GPL(tty_buffer_space_avail);

अटल व्योम tty_buffer_reset(काष्ठा tty_buffer *p, माप_प्रकार size)
अणु
	p->used = 0;
	p->size = size;
	p->next = शून्य;
	p->commit = 0;
	p->पढ़ो = 0;
	p->flags = 0;
पूर्ण

/**
 *	tty_buffer_मुक्त_all		-	मुक्त buffers used by a tty
 *	@port: tty port to मुक्त from
 *
 *	Remove all the buffers pending on a tty whether queued with data
 *	or in the मुक्त ring. Must be called when the tty is no दीर्घer in use
 */

व्योम tty_buffer_मुक्त_all(काष्ठा tty_port *port)
अणु
	काष्ठा tty_bufhead *buf = &port->buf;
	काष्ठा tty_buffer *p, *next;
	काष्ठा llist_node *llist;
	अचिन्हित पूर्णांक मुक्तd = 0;
	पूर्णांक still_used;

	जबतक ((p = buf->head) != शून्य) अणु
		buf->head = p->next;
		मुक्तd += p->size;
		अगर (p->size > 0)
			kमुक्त(p);
	पूर्ण
	llist = llist_del_all(&buf->मुक्त);
	llist_क्रम_each_entry_safe(p, next, llist, मुक्त)
		kमुक्त(p);

	tty_buffer_reset(&buf->sentinel, 0);
	buf->head = &buf->sentinel;
	buf->tail = &buf->sentinel;

	still_used = atomic_xchg(&buf->mem_used, 0);
	WARN(still_used != मुक्तd, "we still have not freed %d bytes!",
			still_used - मुक्तd);
पूर्ण

/**
 *	tty_buffer_alloc	-	allocate a tty buffer
 *	@port: tty port
 *	@size: desired size (अक्षरacters)
 *
 *	Allocate a new tty buffer to hold the desired number of अक्षरacters.
 *	We round our buffers off in 256 अक्षरacter chunks to get better
 *	allocation behaviour.
 *	Return शून्य अगर out of memory or the allocation would exceed the
 *	per device queue
 */

अटल काष्ठा tty_buffer *tty_buffer_alloc(काष्ठा tty_port *port, माप_प्रकार size)
अणु
	काष्ठा llist_node *मुक्त;
	काष्ठा tty_buffer *p;

	/* Round the buffer size out */
	size = __ALIGN_MASK(size, TTYB_ALIGN_MASK);

	अगर (size <= MIN_TTYB_SIZE) अणु
		मुक्त = llist_del_first(&port->buf.मुक्त);
		अगर (मुक्त) अणु
			p = llist_entry(मुक्त, काष्ठा tty_buffer, मुक्त);
			जाओ found;
		पूर्ण
	पूर्ण

	/* Should possibly check अगर this fails क्रम the largest buffer we
	   have queued and recycle that ? */
	अगर (atomic_पढ़ो(&port->buf.mem_used) > port->buf.mem_limit)
		वापस शून्य;
	p = kदो_स्मृति(माप(काष्ठा tty_buffer) + 2 * size, GFP_ATOMIC);
	अगर (p == शून्य)
		वापस शून्य;

found:
	tty_buffer_reset(p, size);
	atomic_add(size, &port->buf.mem_used);
	वापस p;
पूर्ण

/**
 *	tty_buffer_मुक्त		-	मुक्त a tty buffer
 *	@port: tty port owning the buffer
 *	@b: the buffer to मुक्त
 *
 *	Free a tty buffer, or add it to the मुक्त list according to our
 *	पूर्णांकernal strategy
 */

अटल व्योम tty_buffer_मुक्त(काष्ठा tty_port *port, काष्ठा tty_buffer *b)
अणु
	काष्ठा tty_bufhead *buf = &port->buf;

	/* Dumb strategy क्रम now - should keep some stats */
	WARN_ON(atomic_sub_वापस(b->size, &buf->mem_used) < 0);

	अगर (b->size > MIN_TTYB_SIZE)
		kमुक्त(b);
	अन्यथा अगर (b->size > 0)
		llist_add(&b->मुक्त, &buf->मुक्त);
पूर्ण

/**
 *	tty_buffer_flush		-	flush full tty buffers
 *	@tty: tty to flush
 *	@ld:  optional ldisc ptr (must be referenced)
 *
 *	flush all the buffers containing receive data. If ld != शून्य,
 *	flush the ldisc input buffer.
 *
 *	Locking: takes buffer lock to ensure single-thपढ़ोed flip buffer
 *		 'consumer'
 */

व्योम tty_buffer_flush(काष्ठा tty_काष्ठा *tty, काष्ठा tty_ldisc *ld)
अणु
	काष्ठा tty_port *port = tty->port;
	काष्ठा tty_bufhead *buf = &port->buf;
	काष्ठा tty_buffer *next;

	atomic_inc(&buf->priority);

	mutex_lock(&buf->lock);
	/* paired w/ release in __tty_buffer_request_room; ensures there are
	 * no pending memory accesses to the मुक्तd buffer
	 */
	जबतक ((next = smp_load_acquire(&buf->head->next)) != शून्य) अणु
		tty_buffer_मुक्त(port, buf->head);
		buf->head = next;
	पूर्ण
	buf->head->पढ़ो = buf->head->commit;

	अगर (ld && ld->ops->flush_buffer)
		ld->ops->flush_buffer(tty);

	atomic_dec(&buf->priority);
	mutex_unlock(&buf->lock);
पूर्ण

/**
 *	tty_buffer_request_room		-	grow tty buffer अगर needed
 *	@port: tty port
 *	@size: size desired
 *	@flags: buffer flags अगर new buffer allocated (शेष = 0)
 *
 *	Make at least size bytes of linear space available क्रम the tty
 *	buffer. If we fail वापस the size we managed to find.
 *
 *	Will change over to a new buffer अगर the current buffer is encoded as
 *	TTY_NORMAL (so has no flags buffer) and the new buffer requires
 *	a flags buffer.
 */
अटल पूर्णांक __tty_buffer_request_room(काष्ठा tty_port *port, माप_प्रकार size,
				     पूर्णांक flags)
अणु
	काष्ठा tty_bufhead *buf = &port->buf;
	काष्ठा tty_buffer *b, *n;
	पूर्णांक left, change;

	b = buf->tail;
	अगर (b->flags & TTYB_NORMAL)
		left = 2 * b->size - b->used;
	अन्यथा
		left = b->size - b->used;

	change = (b->flags & TTYB_NORMAL) && (~flags & TTYB_NORMAL);
	अगर (change || left < size) अणु
		/* This is the slow path - looking क्रम new buffers to use */
		n = tty_buffer_alloc(port, size);
		अगर (n != शून्य) अणु
			n->flags = flags;
			buf->tail = n;
			/* paired w/ acquire in flush_to_ldisc(); ensures
			 * flush_to_ldisc() sees buffer data.
			 */
			smp_store_release(&b->commit, b->used);
			/* paired w/ acquire in flush_to_ldisc(); ensures the
			 * latest commit value can be पढ़ो beक्रमe the head is
			 * advanced to the next buffer
			 */
			smp_store_release(&b->next, n);
		पूर्ण अन्यथा अगर (change)
			size = 0;
		अन्यथा
			size = left;
	पूर्ण
	वापस size;
पूर्ण

पूर्णांक tty_buffer_request_room(काष्ठा tty_port *port, माप_प्रकार size)
अणु
	वापस __tty_buffer_request_room(port, size, 0);
पूर्ण
EXPORT_SYMBOL_GPL(tty_buffer_request_room);

/**
 *	tty_insert_flip_string_fixed_flag - Add अक्षरacters to the tty buffer
 *	@port: tty port
 *	@अक्षरs: अक्षरacters
 *	@flag: flag value क्रम each अक्षरacter
 *	@size: size
 *
 *	Queue a series of bytes to the tty buffering. All the अक्षरacters
 *	passed are marked with the supplied flag. Returns the number added.
 */

पूर्णांक tty_insert_flip_string_fixed_flag(काष्ठा tty_port *port,
		स्थिर अचिन्हित अक्षर *अक्षरs, अक्षर flag, माप_प्रकार size)
अणु
	पूर्णांक copied = 0;
	करो अणु
		पूर्णांक goal = min_t(माप_प्रकार, size - copied, TTY_BUFFER_PAGE);
		पूर्णांक flags = (flag == TTY_NORMAL) ? TTYB_NORMAL : 0;
		पूर्णांक space = __tty_buffer_request_room(port, goal, flags);
		काष्ठा tty_buffer *tb = port->buf.tail;
		अगर (unlikely(space == 0))
			अवरोध;
		स_नकल(अक्षर_buf_ptr(tb, tb->used), अक्षरs, space);
		अगर (~tb->flags & TTYB_NORMAL)
			स_रखो(flag_buf_ptr(tb, tb->used), flag, space);
		tb->used += space;
		copied += space;
		अक्षरs += space;
		/* There is a small chance that we need to split the data over
		   several buffers. If this is the हाल we must loop */
	पूर्ण जबतक (unlikely(size > copied));
	वापस copied;
पूर्ण
EXPORT_SYMBOL(tty_insert_flip_string_fixed_flag);

/**
 *	tty_insert_flip_string_flags	-	Add अक्षरacters to the tty buffer
 *	@port: tty port
 *	@अक्षरs: अक्षरacters
 *	@flags: flag bytes
 *	@size: size
 *
 *	Queue a series of bytes to the tty buffering. For each अक्षरacter
 *	the flags array indicates the status of the अक्षरacter. Returns the
 *	number added.
 */

पूर्णांक tty_insert_flip_string_flags(काष्ठा tty_port *port,
		स्थिर अचिन्हित अक्षर *अक्षरs, स्थिर अक्षर *flags, माप_प्रकार size)
अणु
	पूर्णांक copied = 0;
	करो अणु
		पूर्णांक goal = min_t(माप_प्रकार, size - copied, TTY_BUFFER_PAGE);
		पूर्णांक space = tty_buffer_request_room(port, goal);
		काष्ठा tty_buffer *tb = port->buf.tail;
		अगर (unlikely(space == 0))
			अवरोध;
		स_नकल(अक्षर_buf_ptr(tb, tb->used), अक्षरs, space);
		स_नकल(flag_buf_ptr(tb, tb->used), flags, space);
		tb->used += space;
		copied += space;
		अक्षरs += space;
		flags += space;
		/* There is a small chance that we need to split the data over
		   several buffers. If this is the हाल we must loop */
	पूर्ण जबतक (unlikely(size > copied));
	वापस copied;
पूर्ण
EXPORT_SYMBOL(tty_insert_flip_string_flags);

/**
 *	__tty_insert_flip_अक्षर   -	Add one अक्षरacter to the tty buffer
 *	@port: tty port
 *	@ch: अक्षरacter
 *	@flag: flag byte
 *
 *	Queue a single byte to the tty buffering, with an optional flag.
 *	This is the slow path of tty_insert_flip_अक्षर.
 */
पूर्णांक __tty_insert_flip_अक्षर(काष्ठा tty_port *port, अचिन्हित अक्षर ch, अक्षर flag)
अणु
	काष्ठा tty_buffer *tb;
	पूर्णांक flags = (flag == TTY_NORMAL) ? TTYB_NORMAL : 0;

	अगर (!__tty_buffer_request_room(port, 1, flags))
		वापस 0;

	tb = port->buf.tail;
	अगर (~tb->flags & TTYB_NORMAL)
		*flag_buf_ptr(tb, tb->used) = flag;
	*अक्षर_buf_ptr(tb, tb->used++) = ch;

	वापस 1;
पूर्ण
EXPORT_SYMBOL(__tty_insert_flip_अक्षर);

/**
 *	tty_schedule_flip	-	push अक्षरacters to ldisc
 *	@port: tty port to push from
 *
 *	Takes any pending buffers and transfers their ownership to the
 *	ldisc side of the queue. It then schedules those अक्षरacters क्रम
 *	processing by the line discipline.
 */

व्योम tty_schedule_flip(काष्ठा tty_port *port)
अणु
	काष्ठा tty_bufhead *buf = &port->buf;

	/* paired w/ acquire in flush_to_ldisc(); ensures
	 * flush_to_ldisc() sees buffer data.
	 */
	smp_store_release(&buf->tail->commit, buf->tail->used);
	queue_work(प्रणाली_unbound_wq, &buf->work);
पूर्ण
EXPORT_SYMBOL(tty_schedule_flip);

/**
 *	tty_prepare_flip_string		-	make room क्रम अक्षरacters
 *	@port: tty port
 *	@अक्षरs: वापस poपूर्णांकer क्रम अक्षरacter ग_लिखो area
 *	@size: desired size
 *
 *	Prepare a block of space in the buffer क्रम data. Returns the length
 *	available and buffer poपूर्णांकer to the space which is now allocated and
 *	accounted क्रम as पढ़ोy क्रम normal अक्षरacters. This is used क्रम drivers
 *	that need their own block copy routines पूर्णांकo the buffer. There is no
 *	guarantee the buffer is a DMA target!
 */

पूर्णांक tty_prepare_flip_string(काष्ठा tty_port *port, अचिन्हित अक्षर **अक्षरs,
		माप_प्रकार size)
अणु
	पूर्णांक space = __tty_buffer_request_room(port, size, TTYB_NORMAL);
	अगर (likely(space)) अणु
		काष्ठा tty_buffer *tb = port->buf.tail;
		*अक्षरs = अक्षर_buf_ptr(tb, tb->used);
		अगर (~tb->flags & TTYB_NORMAL)
			स_रखो(flag_buf_ptr(tb, tb->used), TTY_NORMAL, space);
		tb->used += space;
	पूर्ण
	वापस space;
पूर्ण
EXPORT_SYMBOL_GPL(tty_prepare_flip_string);

/**
 *	tty_ldisc_receive_buf		-	क्रमward data to line discipline
 *	@ld:	line discipline to process input
 *	@p:	अक्षर buffer
 *	@f:	TTY_* flags buffer
 *	@count:	number of bytes to process
 *
 *	Callers other than flush_to_ldisc() need to exclude the kworker
 *	from concurrent use of the line discipline, see paste_selection().
 *
 *	Returns the number of bytes processed
 */
पूर्णांक tty_ldisc_receive_buf(काष्ठा tty_ldisc *ld, स्थिर अचिन्हित अक्षर *p,
			  अक्षर *f, पूर्णांक count)
अणु
	अगर (ld->ops->receive_buf2)
		count = ld->ops->receive_buf2(ld->tty, p, f, count);
	अन्यथा अणु
		count = min_t(पूर्णांक, count, ld->tty->receive_room);
		अगर (count && ld->ops->receive_buf)
			ld->ops->receive_buf(ld->tty, p, f, count);
	पूर्ण
	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(tty_ldisc_receive_buf);

अटल पूर्णांक
receive_buf(काष्ठा tty_port *port, काष्ठा tty_buffer *head, पूर्णांक count)
अणु
	अचिन्हित अक्षर *p = अक्षर_buf_ptr(head, head->पढ़ो);
	अक्षर	      *f = शून्य;
	पूर्णांक n;

	अगर (~head->flags & TTYB_NORMAL)
		f = flag_buf_ptr(head, head->पढ़ो);

	n = port->client_ops->receive_buf(port, p, f, count);
	अगर (n > 0)
		स_रखो(p, 0, n);
	वापस n;
पूर्ण

/**
 *	flush_to_ldisc
 *	@work: tty काष्ठाure passed from work queue.
 *
 *	This routine is called out of the software पूर्णांकerrupt to flush data
 *	from the buffer chain to the line discipline.
 *
 *	The receive_buf method is single thपढ़ोed क्रम each tty instance.
 *
 *	Locking: takes buffer lock to ensure single-thपढ़ोed flip buffer
 *		 'consumer'
 */

अटल व्योम flush_to_ldisc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tty_port *port = container_of(work, काष्ठा tty_port, buf.work);
	काष्ठा tty_bufhead *buf = &port->buf;

	mutex_lock(&buf->lock);

	जबतक (1) अणु
		काष्ठा tty_buffer *head = buf->head;
		काष्ठा tty_buffer *next;
		पूर्णांक count;

		/* Ldisc or user is trying to gain exclusive access */
		अगर (atomic_पढ़ो(&buf->priority))
			अवरोध;

		/* paired w/ release in __tty_buffer_request_room();
		 * ensures commit value पढ़ो is not stale अगर the head
		 * is advancing to the next buffer
		 */
		next = smp_load_acquire(&head->next);
		/* paired w/ release in __tty_buffer_request_room() or in
		 * tty_buffer_flush(); ensures we see the committed buffer data
		 */
		count = smp_load_acquire(&head->commit) - head->पढ़ो;
		अगर (!count) अणु
			अगर (next == शून्य)
				अवरोध;
			buf->head = next;
			tty_buffer_मुक्त(port, head);
			जारी;
		पूर्ण

		count = receive_buf(port, head, count);
		अगर (!count)
			अवरोध;
		head->पढ़ो += count;
	पूर्ण

	mutex_unlock(&buf->lock);

पूर्ण

/**
 *	tty_flip_buffer_push	-	terminal
 *	@port: tty port to push
 *
 *	Queue a push of the terminal flip buffers to the line discipline.
 *	Can be called from IRQ/atomic context.
 *
 *	In the event of the queue being busy क्रम flipping the work will be
 *	held off and retried later.
 */

व्योम tty_flip_buffer_push(काष्ठा tty_port *port)
अणु
	tty_schedule_flip(port);
पूर्ण
EXPORT_SYMBOL(tty_flip_buffer_push);

/**
 *	tty_buffer_init		-	prepare a tty buffer काष्ठाure
 *	@port: tty port to initialise
 *
 *	Set up the initial state of the buffer management क्रम a tty device.
 *	Must be called beक्रमe the other tty buffer functions are used.
 */

व्योम tty_buffer_init(काष्ठा tty_port *port)
अणु
	काष्ठा tty_bufhead *buf = &port->buf;

	mutex_init(&buf->lock);
	tty_buffer_reset(&buf->sentinel, 0);
	buf->head = &buf->sentinel;
	buf->tail = &buf->sentinel;
	init_llist_head(&buf->मुक्त);
	atomic_set(&buf->mem_used, 0);
	atomic_set(&buf->priority, 0);
	INIT_WORK(&buf->work, flush_to_ldisc);
	buf->mem_limit = TTYB_DEFAULT_MEM_LIMIT;
पूर्ण

/**
 *	tty_buffer_set_limit	-	change the tty buffer memory limit
 *	@port: tty port to change
 *	@limit: memory limit to set
 *
 *	Change the tty buffer memory limit.
 *	Must be called beक्रमe the other tty buffer functions are used.
 */

पूर्णांक tty_buffer_set_limit(काष्ठा tty_port *port, पूर्णांक limit)
अणु
	अगर (limit < MIN_TTYB_SIZE)
		वापस -EINVAL;
	port->buf.mem_limit = limit;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tty_buffer_set_limit);

/* slave ptys can claim nested buffer lock when handling BRK and INTR */
व्योम tty_buffer_set_lock_subclass(काष्ठा tty_port *port)
अणु
	lockdep_set_subclass(&port->buf.lock, TTY_LOCK_SLAVE);
पूर्ण

bool tty_buffer_restart_work(काष्ठा tty_port *port)
अणु
	वापस queue_work(प्रणाली_unbound_wq, &port->buf.work);
पूर्ण

bool tty_buffer_cancel_work(काष्ठा tty_port *port)
अणु
	वापस cancel_work_sync(&port->buf.work);
पूर्ण

व्योम tty_buffer_flush_work(काष्ठा tty_port *port)
अणु
	flush_work(&port->buf.work);
पूर्ण
