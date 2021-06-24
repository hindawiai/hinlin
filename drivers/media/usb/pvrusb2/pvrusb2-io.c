<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */

#समावेश "pvrusb2-io.h"
#समावेश "pvrusb2-debug.h"
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

अटल स्थिर अक्षर *pvr2_buffer_state_decode(क्रमागत pvr2_buffer_state);

#घोषणा BUFFER_SIG 0x47653271

// #घोषणा SANITY_CHECK_BUFFERS


#अगर_घोषित SANITY_CHECK_BUFFERS
#घोषणा BUFFER_CHECK(bp) करो अणु \
	अगर ((bp)->signature != BUFFER_SIG) अणु \
		pvr2_trace(PVR2_TRACE_ERROR_LEGS, \
		"Buffer %p is bad at %s:%d", \
		(bp), __खाता__, __LINE__); \
		pvr2_buffer_describe(bp, "BadSig"); \
		BUG(); \
	पूर्ण \
पूर्ण जबतक (0)
#अन्यथा
#घोषणा BUFFER_CHECK(bp) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा pvr2_stream अणु
	/* Buffers queued क्रम पढ़ोing */
	काष्ठा list_head queued_list;
	अचिन्हित पूर्णांक q_count;
	अचिन्हित पूर्णांक q_bcount;
	/* Buffers with retrieved data */
	काष्ठा list_head पढ़ोy_list;
	अचिन्हित पूर्णांक r_count;
	अचिन्हित पूर्णांक r_bcount;
	/* Buffers available क्रम use */
	काष्ठा list_head idle_list;
	अचिन्हित पूर्णांक i_count;
	अचिन्हित पूर्णांक i_bcount;
	/* Poपूर्णांकers to all buffers */
	काष्ठा pvr2_buffer **buffers;
	/* Array size of buffers */
	अचिन्हित पूर्णांक buffer_slot_count;
	/* Total buffers actually in circulation */
	अचिन्हित पूर्णांक buffer_total_count;
	/* Deचिन्हित number of buffers to be in circulation */
	अचिन्हित पूर्णांक buffer_target_count;
	/* Executed when पढ़ोy list become non-empty */
	pvr2_stream_callback callback_func;
	व्योम *callback_data;
	/* Context क्रम transfer endpoपूर्णांक */
	काष्ठा usb_device *dev;
	पूर्णांक endpoपूर्णांक;
	/* Overhead क्रम mutex enक्रमcement */
	spinlock_t list_lock;
	काष्ठा mutex mutex;
	/* Tracking state क्रम tolerating errors */
	अचिन्हित पूर्णांक fail_count;
	अचिन्हित पूर्णांक fail_tolerance;

	अचिन्हित पूर्णांक buffers_processed;
	अचिन्हित पूर्णांक buffers_failed;
	अचिन्हित पूर्णांक bytes_processed;
पूर्ण;

काष्ठा pvr2_buffer अणु
	पूर्णांक id;
	पूर्णांक signature;
	क्रमागत pvr2_buffer_state state;
	व्योम *ptr;               /* Poपूर्णांकer to storage area */
	अचिन्हित पूर्णांक max_count;  /* Size of storage area */
	अचिन्हित पूर्णांक used_count; /* Amount of valid data in storage area */
	पूर्णांक status;              /* Transfer result status */
	काष्ठा pvr2_stream *stream;
	काष्ठा list_head list_overhead;
	काष्ठा urb *purb;
पूर्ण;

अटल स्थिर अक्षर *pvr2_buffer_state_decode(क्रमागत pvr2_buffer_state st)
अणु
	चयन (st) अणु
	हाल pvr2_buffer_state_none: वापस "none";
	हाल pvr2_buffer_state_idle: वापस "idle";
	हाल pvr2_buffer_state_queued: वापस "queued";
	हाल pvr2_buffer_state_पढ़ोy: वापस "ready";
	पूर्ण
	वापस "unknown";
पूर्ण

#अगर_घोषित SANITY_CHECK_BUFFERS
अटल व्योम pvr2_buffer_describe(काष्ठा pvr2_buffer *bp, स्थिर अक्षर *msg)
अणु
	pvr2_trace(PVR2_TRACE_INFO,
		   "buffer%s%s %p state=%s id=%d status=%d stream=%p purb=%p sig=0x%x",
		   (msg ? " " : ""),
		   (msg ? msg : ""),
		   bp,
		   (bp ? pvr2_buffer_state_decode(bp->state) : "(invalid)"),
		   (bp ? bp->id : 0),
		   (bp ? bp->status : 0),
		   (bp ? bp->stream : शून्य),
		   (bp ? bp->purb : शून्य),
		   (bp ? bp->signature : 0));
पूर्ण
#पूर्ण_अगर  /*  SANITY_CHECK_BUFFERS  */

अटल व्योम pvr2_buffer_हटाओ(काष्ठा pvr2_buffer *bp)
अणु
	अचिन्हित पूर्णांक *cnt;
	अचिन्हित पूर्णांक *bcnt;
	अचिन्हित पूर्णांक ccnt;
	काष्ठा pvr2_stream *sp = bp->stream;
	चयन (bp->state) अणु
	हाल pvr2_buffer_state_idle:
		cnt = &sp->i_count;
		bcnt = &sp->i_bcount;
		ccnt = bp->max_count;
		अवरोध;
	हाल pvr2_buffer_state_queued:
		cnt = &sp->q_count;
		bcnt = &sp->q_bcount;
		ccnt = bp->max_count;
		अवरोध;
	हाल pvr2_buffer_state_पढ़ोy:
		cnt = &sp->r_count;
		bcnt = &sp->r_bcount;
		ccnt = bp->used_count;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	list_del_init(&bp->list_overhead);
	(*cnt)--;
	(*bcnt) -= ccnt;
	pvr2_trace(PVR2_TRACE_BUF_FLOW,
		   "/*---TRACE_FLOW---*/ bufferPool	%8s dec cap=%07d cnt=%02d",
		   pvr2_buffer_state_decode(bp->state), *bcnt, *cnt);
	bp->state = pvr2_buffer_state_none;
पूर्ण

अटल व्योम pvr2_buffer_set_none(काष्ठा pvr2_buffer *bp)
अणु
	अचिन्हित दीर्घ irq_flags;
	काष्ठा pvr2_stream *sp;
	BUFFER_CHECK(bp);
	sp = bp->stream;
	pvr2_trace(PVR2_TRACE_BUF_FLOW,
		   "/*---TRACE_FLOW---*/ bufferState    %p %6s --> %6s",
		   bp,
		   pvr2_buffer_state_decode(bp->state),
		   pvr2_buffer_state_decode(pvr2_buffer_state_none));
	spin_lock_irqsave(&sp->list_lock, irq_flags);
	pvr2_buffer_हटाओ(bp);
	spin_unlock_irqrestore(&sp->list_lock, irq_flags);
पूर्ण

अटल पूर्णांक pvr2_buffer_set_पढ़ोy(काष्ठा pvr2_buffer *bp)
अणु
	पूर्णांक fl;
	अचिन्हित दीर्घ irq_flags;
	काष्ठा pvr2_stream *sp;
	BUFFER_CHECK(bp);
	sp = bp->stream;
	pvr2_trace(PVR2_TRACE_BUF_FLOW,
		   "/*---TRACE_FLOW---*/ bufferState    %p %6s --> %6s",
		   bp,
		   pvr2_buffer_state_decode(bp->state),
		   pvr2_buffer_state_decode(pvr2_buffer_state_पढ़ोy));
	spin_lock_irqsave(&sp->list_lock, irq_flags);
	fl = (sp->r_count == 0);
	pvr2_buffer_हटाओ(bp);
	list_add_tail(&bp->list_overhead, &sp->पढ़ोy_list);
	bp->state = pvr2_buffer_state_पढ़ोy;
	(sp->r_count)++;
	sp->r_bcount += bp->used_count;
	pvr2_trace(PVR2_TRACE_BUF_FLOW,
		   "/*---TRACE_FLOW---*/ bufferPool	%8s inc cap=%07d cnt=%02d",
		   pvr2_buffer_state_decode(bp->state),
		   sp->r_bcount, sp->r_count);
	spin_unlock_irqrestore(&sp->list_lock, irq_flags);
	वापस fl;
पूर्ण

अटल व्योम pvr2_buffer_set_idle(काष्ठा pvr2_buffer *bp)
अणु
	अचिन्हित दीर्घ irq_flags;
	काष्ठा pvr2_stream *sp;
	BUFFER_CHECK(bp);
	sp = bp->stream;
	pvr2_trace(PVR2_TRACE_BUF_FLOW,
		   "/*---TRACE_FLOW---*/ bufferState    %p %6s --> %6s",
		   bp,
		   pvr2_buffer_state_decode(bp->state),
		   pvr2_buffer_state_decode(pvr2_buffer_state_idle));
	spin_lock_irqsave(&sp->list_lock, irq_flags);
	pvr2_buffer_हटाओ(bp);
	list_add_tail(&bp->list_overhead, &sp->idle_list);
	bp->state = pvr2_buffer_state_idle;
	(sp->i_count)++;
	sp->i_bcount += bp->max_count;
	pvr2_trace(PVR2_TRACE_BUF_FLOW,
		   "/*---TRACE_FLOW---*/ bufferPool	%8s inc cap=%07d cnt=%02d",
		   pvr2_buffer_state_decode(bp->state),
		   sp->i_bcount, sp->i_count);
	spin_unlock_irqrestore(&sp->list_lock, irq_flags);
पूर्ण

अटल व्योम pvr2_buffer_set_queued(काष्ठा pvr2_buffer *bp)
अणु
	अचिन्हित दीर्घ irq_flags;
	काष्ठा pvr2_stream *sp;
	BUFFER_CHECK(bp);
	sp = bp->stream;
	pvr2_trace(PVR2_TRACE_BUF_FLOW,
		   "/*---TRACE_FLOW---*/ bufferState    %p %6s --> %6s",
		   bp,
		   pvr2_buffer_state_decode(bp->state),
		   pvr2_buffer_state_decode(pvr2_buffer_state_queued));
	spin_lock_irqsave(&sp->list_lock, irq_flags);
	pvr2_buffer_हटाओ(bp);
	list_add_tail(&bp->list_overhead, &sp->queued_list);
	bp->state = pvr2_buffer_state_queued;
	(sp->q_count)++;
	sp->q_bcount += bp->max_count;
	pvr2_trace(PVR2_TRACE_BUF_FLOW,
		   "/*---TRACE_FLOW---*/ bufferPool	%8s inc cap=%07d cnt=%02d",
		   pvr2_buffer_state_decode(bp->state),
		   sp->q_bcount, sp->q_count);
	spin_unlock_irqrestore(&sp->list_lock, irq_flags);
पूर्ण

अटल व्योम pvr2_buffer_wipe(काष्ठा pvr2_buffer *bp)
अणु
	अगर (bp->state == pvr2_buffer_state_queued) अणु
		usb_समाप्त_urb(bp->purb);
	पूर्ण
पूर्ण

अटल पूर्णांक pvr2_buffer_init(काष्ठा pvr2_buffer *bp,
			    काष्ठा pvr2_stream *sp,
			    अचिन्हित पूर्णांक id)
अणु
	स_रखो(bp, 0, माप(*bp));
	bp->signature = BUFFER_SIG;
	bp->id = id;
	pvr2_trace(PVR2_TRACE_BUF_POOL,
		   "/*---TRACE_FLOW---*/ bufferInit     %p stream=%p", bp, sp);
	bp->stream = sp;
	bp->state = pvr2_buffer_state_none;
	INIT_LIST_HEAD(&bp->list_overhead);
	bp->purb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (! bp->purb) वापस -ENOMEM;
#अगर_घोषित SANITY_CHECK_BUFFERS
	pvr2_buffer_describe(bp, "create");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम pvr2_buffer_करोne(काष्ठा pvr2_buffer *bp)
अणु
#अगर_घोषित SANITY_CHECK_BUFFERS
	pvr2_buffer_describe(bp, "delete");
#पूर्ण_अगर
	pvr2_buffer_wipe(bp);
	pvr2_buffer_set_none(bp);
	bp->signature = 0;
	bp->stream = शून्य;
	usb_मुक्त_urb(bp->purb);
	pvr2_trace(PVR2_TRACE_BUF_POOL, "/*---TRACE_FLOW---*/ bufferDone     %p",
		   bp);
पूर्ण

अटल पूर्णांक pvr2_stream_buffer_count(काष्ठा pvr2_stream *sp, अचिन्हित पूर्णांक cnt)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक scnt;

	/* Allocate buffers poपूर्णांकer array in multiples of 32 entries */
	अगर (cnt == sp->buffer_total_count) वापस 0;

	pvr2_trace(PVR2_TRACE_BUF_POOL,
		   "/*---TRACE_FLOW---*/ poolResize	stream=%p cur=%d adj=%+d",
		   sp,
		   sp->buffer_total_count,
		   cnt-sp->buffer_total_count);

	scnt = cnt & ~0x1f;
	अगर (cnt > scnt) scnt += 0x20;

	अगर (cnt > sp->buffer_total_count) अणु
		अगर (scnt > sp->buffer_slot_count) अणु
			काष्ठा pvr2_buffer **nb;

			nb = kदो_स्मृति_array(scnt, माप(*nb), GFP_KERNEL);
			अगर (!nb) वापस -ENOMEM;
			अगर (sp->buffer_slot_count) अणु
				स_नकल(nb, sp->buffers,
				       sp->buffer_slot_count * माप(*nb));
				kमुक्त(sp->buffers);
			पूर्ण
			sp->buffers = nb;
			sp->buffer_slot_count = scnt;
		पूर्ण
		जबतक (sp->buffer_total_count < cnt) अणु
			काष्ठा pvr2_buffer *bp;
			bp = kदो_स्मृति(माप(*bp), GFP_KERNEL);
			अगर (!bp) वापस -ENOMEM;
			ret = pvr2_buffer_init(bp, sp, sp->buffer_total_count);
			अगर (ret) अणु
				kमुक्त(bp);
				वापस -ENOMEM;
			पूर्ण
			sp->buffers[sp->buffer_total_count] = bp;
			(sp->buffer_total_count)++;
			pvr2_buffer_set_idle(bp);
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (sp->buffer_total_count > cnt) अणु
			काष्ठा pvr2_buffer *bp;
			bp = sp->buffers[sp->buffer_total_count - 1];
			/* Paranoia */
			sp->buffers[sp->buffer_total_count - 1] = शून्य;
			(sp->buffer_total_count)--;
			pvr2_buffer_करोne(bp);
			kमुक्त(bp);
		पूर्ण
		अगर (scnt < sp->buffer_slot_count) अणु
			काष्ठा pvr2_buffer **nb = शून्य;
			अगर (scnt) अणु
				nb = kmemdup(sp->buffers, scnt * माप(*nb),
					     GFP_KERNEL);
				अगर (!nb) वापस -ENOMEM;
			पूर्ण
			kमुक्त(sp->buffers);
			sp->buffers = nb;
			sp->buffer_slot_count = scnt;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_stream_achieve_buffer_count(काष्ठा pvr2_stream *sp)
अणु
	काष्ठा pvr2_buffer *bp;
	अचिन्हित पूर्णांक cnt;

	अगर (sp->buffer_total_count == sp->buffer_target_count) वापस 0;

	pvr2_trace(PVR2_TRACE_BUF_POOL,
		   "/*---TRACE_FLOW---*/ poolCheck	stream=%p cur=%d tgt=%d",
		   sp, sp->buffer_total_count, sp->buffer_target_count);

	अगर (sp->buffer_total_count < sp->buffer_target_count) अणु
		वापस pvr2_stream_buffer_count(sp, sp->buffer_target_count);
	पूर्ण

	cnt = 0;
	जबतक ((sp->buffer_total_count - cnt) > sp->buffer_target_count) अणु
		bp = sp->buffers[sp->buffer_total_count - (cnt + 1)];
		अगर (bp->state != pvr2_buffer_state_idle) अवरोध;
		cnt++;
	पूर्ण
	अगर (cnt) अणु
		pvr2_stream_buffer_count(sp, sp->buffer_total_count - cnt);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pvr2_stream_पूर्णांकernal_flush(काष्ठा pvr2_stream *sp)
अणु
	काष्ठा list_head *lp;
	काष्ठा pvr2_buffer *bp1;
	जबतक ((lp = sp->queued_list.next) != &sp->queued_list) अणु
		bp1 = list_entry(lp, काष्ठा pvr2_buffer, list_overhead);
		pvr2_buffer_wipe(bp1);
		/* At this poपूर्णांक, we should be guaranteed that no
		   completion callback may happen on this buffer.  But it's
		   possible that it might have completed after we noticed
		   it but beक्रमe we wiped it.  So द्विगुन check its status
		   here first. */
		अगर (bp1->state != pvr2_buffer_state_queued) जारी;
		pvr2_buffer_set_idle(bp1);
	पूर्ण
	अगर (sp->buffer_total_count != sp->buffer_target_count) अणु
		pvr2_stream_achieve_buffer_count(sp);
	पूर्ण
पूर्ण

अटल व्योम pvr2_stream_init(काष्ठा pvr2_stream *sp)
अणु
	spin_lock_init(&sp->list_lock);
	mutex_init(&sp->mutex);
	INIT_LIST_HEAD(&sp->queued_list);
	INIT_LIST_HEAD(&sp->पढ़ोy_list);
	INIT_LIST_HEAD(&sp->idle_list);
पूर्ण

अटल व्योम pvr2_stream_करोne(काष्ठा pvr2_stream *sp)
अणु
	mutex_lock(&sp->mutex); करो अणु
		pvr2_stream_पूर्णांकernal_flush(sp);
		pvr2_stream_buffer_count(sp, 0);
	पूर्ण जबतक (0); mutex_unlock(&sp->mutex);
पूर्ण

अटल व्योम buffer_complete(काष्ठा urb *urb)
अणु
	काष्ठा pvr2_buffer *bp = urb->context;
	काष्ठा pvr2_stream *sp;
	अचिन्हित दीर्घ irq_flags;
	BUFFER_CHECK(bp);
	sp = bp->stream;
	bp->used_count = 0;
	bp->status = 0;
	pvr2_trace(PVR2_TRACE_BUF_FLOW,
		   "/*---TRACE_FLOW---*/ bufferComplete %p stat=%d cnt=%d",
		   bp, urb->status, urb->actual_length);
	spin_lock_irqsave(&sp->list_lock, irq_flags);
	अगर ((!(urb->status)) ||
	    (urb->status == -ENOENT) ||
	    (urb->status == -ECONNRESET) ||
	    (urb->status == -ESHUTDOWN)) अणु
		(sp->buffers_processed)++;
		sp->bytes_processed += urb->actual_length;
		bp->used_count = urb->actual_length;
		अगर (sp->fail_count) अणु
			pvr2_trace(PVR2_TRACE_TOLERANCE,
				   "stream %p transfer ok - fail count reset",
				   sp);
			sp->fail_count = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (sp->fail_count < sp->fail_tolerance) अणु
		// We can tolerate this error, because we're below the
		// threshold...
		(sp->fail_count)++;
		(sp->buffers_failed)++;
		pvr2_trace(PVR2_TRACE_TOLERANCE,
			   "stream %p ignoring error %d - fail count increased to %u",
			   sp, urb->status, sp->fail_count);
	पूर्ण अन्यथा अणु
		(sp->buffers_failed)++;
		bp->status = urb->status;
	पूर्ण
	spin_unlock_irqrestore(&sp->list_lock, irq_flags);
	pvr2_buffer_set_पढ़ोy(bp);
	अगर (sp->callback_func) अणु
		sp->callback_func(sp->callback_data);
	पूर्ण
पूर्ण

काष्ठा pvr2_stream *pvr2_stream_create(व्योम)
अणु
	काष्ठा pvr2_stream *sp;
	sp = kzalloc(माप(*sp), GFP_KERNEL);
	अगर (!sp) वापस sp;
	pvr2_trace(PVR2_TRACE_INIT, "pvr2_stream_create: sp=%p", sp);
	pvr2_stream_init(sp);
	वापस sp;
पूर्ण

व्योम pvr2_stream_destroy(काष्ठा pvr2_stream *sp)
अणु
	अगर (!sp) वापस;
	pvr2_trace(PVR2_TRACE_INIT, "pvr2_stream_destroy: sp=%p", sp);
	pvr2_stream_करोne(sp);
	kमुक्त(sp);
पूर्ण

व्योम pvr2_stream_setup(काष्ठा pvr2_stream *sp,
		       काष्ठा usb_device *dev,
		       पूर्णांक endpoपूर्णांक,
		       अचिन्हित पूर्णांक tolerance)
अणु
	mutex_lock(&sp->mutex); करो अणु
		pvr2_stream_पूर्णांकernal_flush(sp);
		sp->dev = dev;
		sp->endpoपूर्णांक = endpoपूर्णांक;
		sp->fail_tolerance = tolerance;
	पूर्ण जबतक (0); mutex_unlock(&sp->mutex);
पूर्ण

व्योम pvr2_stream_set_callback(काष्ठा pvr2_stream *sp,
			      pvr2_stream_callback func,
			      व्योम *data)
अणु
	अचिन्हित दीर्घ irq_flags;
	mutex_lock(&sp->mutex);
	करो अणु
		spin_lock_irqsave(&sp->list_lock, irq_flags);
		sp->callback_data = data;
		sp->callback_func = func;
		spin_unlock_irqrestore(&sp->list_lock, irq_flags);
	पूर्ण जबतक (0);
	mutex_unlock(&sp->mutex);
पूर्ण

व्योम pvr2_stream_get_stats(काष्ठा pvr2_stream *sp,
			   काष्ठा pvr2_stream_stats *stats,
			   पूर्णांक zero_counts)
अणु
	अचिन्हित दीर्घ irq_flags;
	spin_lock_irqsave(&sp->list_lock, irq_flags);
	अगर (stats) अणु
		stats->buffers_in_queue = sp->q_count;
		stats->buffers_in_idle = sp->i_count;
		stats->buffers_in_पढ़ोy = sp->r_count;
		stats->buffers_processed = sp->buffers_processed;
		stats->buffers_failed = sp->buffers_failed;
		stats->bytes_processed = sp->bytes_processed;
	पूर्ण
	अगर (zero_counts) अणु
		sp->buffers_processed = 0;
		sp->buffers_failed = 0;
		sp->bytes_processed = 0;
	पूर्ण
	spin_unlock_irqrestore(&sp->list_lock, irq_flags);
पूर्ण

/* Query / set the nominal buffer count */
पूर्णांक pvr2_stream_get_buffer_count(काष्ठा pvr2_stream *sp)
अणु
	वापस sp->buffer_target_count;
पूर्ण

पूर्णांक pvr2_stream_set_buffer_count(काष्ठा pvr2_stream *sp, अचिन्हित पूर्णांक cnt)
अणु
	पूर्णांक ret;
	अगर (sp->buffer_target_count == cnt) वापस 0;
	mutex_lock(&sp->mutex);
	करो अणु
		sp->buffer_target_count = cnt;
		ret = pvr2_stream_achieve_buffer_count(sp);
	पूर्ण जबतक (0);
	mutex_unlock(&sp->mutex);
	वापस ret;
पूर्ण

काष्ठा pvr2_buffer *pvr2_stream_get_idle_buffer(काष्ठा pvr2_stream *sp)
अणु
	काष्ठा list_head *lp = sp->idle_list.next;
	अगर (lp == &sp->idle_list) वापस शून्य;
	वापस list_entry(lp, काष्ठा pvr2_buffer, list_overhead);
पूर्ण

काष्ठा pvr2_buffer *pvr2_stream_get_पढ़ोy_buffer(काष्ठा pvr2_stream *sp)
अणु
	काष्ठा list_head *lp = sp->पढ़ोy_list.next;
	अगर (lp == &sp->पढ़ोy_list) वापस शून्य;
	वापस list_entry(lp, काष्ठा pvr2_buffer, list_overhead);
पूर्ण

काष्ठा pvr2_buffer *pvr2_stream_get_buffer(काष्ठा pvr2_stream *sp, पूर्णांक id)
अणु
	अगर (id < 0) वापस शून्य;
	अगर (id >= sp->buffer_total_count) वापस शून्य;
	वापस sp->buffers[id];
पूर्ण

पूर्णांक pvr2_stream_get_पढ़ोy_count(काष्ठा pvr2_stream *sp)
अणु
	वापस sp->r_count;
पूर्ण

व्योम pvr2_stream_समाप्त(काष्ठा pvr2_stream *sp)
अणु
	काष्ठा pvr2_buffer *bp;
	mutex_lock(&sp->mutex);
	करो अणु
		pvr2_stream_पूर्णांकernal_flush(sp);
		जबतक ((bp = pvr2_stream_get_पढ़ोy_buffer(sp)) != शून्य) अणु
			pvr2_buffer_set_idle(bp);
		पूर्ण
		अगर (sp->buffer_total_count != sp->buffer_target_count) अणु
			pvr2_stream_achieve_buffer_count(sp);
		पूर्ण
	पूर्ण जबतक (0);
	mutex_unlock(&sp->mutex);
पूर्ण

पूर्णांक pvr2_buffer_queue(काष्ठा pvr2_buffer *bp)
अणु
#अघोषित SEED_BUFFER
#अगर_घोषित SEED_BUFFER
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक val;
#पूर्ण_अगर
	पूर्णांक ret = 0;
	काष्ठा pvr2_stream *sp;
	अगर (!bp) वापस -EINVAL;
	sp = bp->stream;
	mutex_lock(&sp->mutex);
	करो अणु
		pvr2_buffer_wipe(bp);
		अगर (!sp->dev) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		pvr2_buffer_set_queued(bp);
#अगर_घोषित SEED_BUFFER
		क्रम (idx = 0; idx < (bp->max_count) / 4; idx++) अणु
			val = bp->id << 24;
			val |= idx;
			((अचिन्हित पूर्णांक *)(bp->ptr))[idx] = val;
		पूर्ण
#पूर्ण_अगर
		bp->status = -EINPROGRESS;
		usb_fill_bulk_urb(bp->purb,      // काष्ठा urb *urb
				  sp->dev,       // काष्ठा usb_device *dev
				  // endpoपूर्णांक (below)
				  usb_rcvbulkpipe(sp->dev, sp->endpoपूर्णांक),
				  bp->ptr,       // व्योम *transfer_buffer
				  bp->max_count, // पूर्णांक buffer_length
				  buffer_complete,
				  bp);
		usb_submit_urb(bp->purb, GFP_KERNEL);
	पूर्ण जबतक (0);
	mutex_unlock(&sp->mutex);
	वापस ret;
पूर्ण

पूर्णांक pvr2_buffer_set_buffer(काष्ठा pvr2_buffer *bp, व्योम *ptr, अचिन्हित पूर्णांक cnt)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ irq_flags;
	काष्ठा pvr2_stream *sp;
	अगर (!bp) वापस -EINVAL;
	sp = bp->stream;
	mutex_lock(&sp->mutex);
	करो अणु
		spin_lock_irqsave(&sp->list_lock, irq_flags);
		अगर (bp->state != pvr2_buffer_state_idle) अणु
			ret = -EPERM;
		पूर्ण अन्यथा अणु
			bp->ptr = ptr;
			bp->stream->i_bcount -= bp->max_count;
			bp->max_count = cnt;
			bp->stream->i_bcount += bp->max_count;
			pvr2_trace(PVR2_TRACE_BUF_FLOW,
				   "/*---TRACE_FLOW---*/ bufferPool	%8s cap cap=%07d cnt=%02d",
				   pvr2_buffer_state_decode(
					   pvr2_buffer_state_idle),
				   bp->stream->i_bcount, bp->stream->i_count);
		पूर्ण
		spin_unlock_irqrestore(&sp->list_lock, irq_flags);
	पूर्ण जबतक (0);
	mutex_unlock(&sp->mutex);
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक pvr2_buffer_get_count(काष्ठा pvr2_buffer *bp)
अणु
	वापस bp->used_count;
पूर्ण

पूर्णांक pvr2_buffer_get_status(काष्ठा pvr2_buffer *bp)
अणु
	वापस bp->status;
पूर्ण

पूर्णांक pvr2_buffer_get_id(काष्ठा pvr2_buffer *bp)
अणु
	वापस bp->id;
पूर्ण
