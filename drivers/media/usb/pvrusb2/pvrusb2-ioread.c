<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */

#समावेश "pvrusb2-ioread.h"
#समावेश "pvrusb2-debug.h"
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>

#घोषणा BUFFER_COUNT 32
#घोषणा BUFFER_SIZE PAGE_ALIGN(0x4000)

काष्ठा pvr2_ioपढ़ो अणु
	काष्ठा pvr2_stream *stream;
	अक्षर *buffer_storage[BUFFER_COUNT];
	अक्षर *sync_key_ptr;
	अचिन्हित पूर्णांक sync_key_len;
	अचिन्हित पूर्णांक sync_buf_offs;
	अचिन्हित पूर्णांक sync_state;
	अचिन्हित पूर्णांक sync_trashed_count;
	पूर्णांक enabled;         // Streaming is on
	पूर्णांक spigot_खोलो;     // OK to pass data to client
	पूर्णांक stream_running;  // Passing data to client now

	/* State relevant to current buffer being पढ़ो */
	काष्ठा pvr2_buffer *c_buf;
	अक्षर *c_data_ptr;
	अचिन्हित पूर्णांक c_data_len;
	अचिन्हित पूर्णांक c_data_offs;
	काष्ठा mutex mutex;
पूर्ण;

अटल पूर्णांक pvr2_ioपढ़ो_init(काष्ठा pvr2_ioपढ़ो *cp)
अणु
	अचिन्हित पूर्णांक idx;

	cp->stream = शून्य;
	mutex_init(&cp->mutex);

	क्रम (idx = 0; idx < BUFFER_COUNT; idx++) अणु
		cp->buffer_storage[idx] = kदो_स्मृति(BUFFER_SIZE,GFP_KERNEL);
		अगर (!(cp->buffer_storage[idx])) अवरोध;
	पूर्ण

	अगर (idx < BUFFER_COUNT) अणु
		// An allocation appears to have failed
		क्रम (idx = 0; idx < BUFFER_COUNT; idx++) अणु
			अगर (!(cp->buffer_storage[idx])) जारी;
			kमुक्त(cp->buffer_storage[idx]);
		पूर्ण
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pvr2_ioपढ़ो_करोne(काष्ठा pvr2_ioपढ़ो *cp)
अणु
	अचिन्हित पूर्णांक idx;

	pvr2_ioपढ़ो_setup(cp,शून्य);
	क्रम (idx = 0; idx < BUFFER_COUNT; idx++) अणु
		अगर (!(cp->buffer_storage[idx])) जारी;
		kमुक्त(cp->buffer_storage[idx]);
	पूर्ण
पूर्ण

काष्ठा pvr2_ioपढ़ो *pvr2_ioपढ़ो_create(व्योम)
अणु
	काष्ठा pvr2_ioपढ़ो *cp;
	cp = kzalloc(माप(*cp),GFP_KERNEL);
	अगर (!cp) वापस शून्य;
	pvr2_trace(PVR2_TRACE_STRUCT,"pvr2_ioread_create id=%p",cp);
	अगर (pvr2_ioपढ़ो_init(cp) < 0) अणु
		kमुक्त(cp);
		वापस शून्य;
	पूर्ण
	वापस cp;
पूर्ण

व्योम pvr2_ioपढ़ो_destroy(काष्ठा pvr2_ioपढ़ो *cp)
अणु
	अगर (!cp) वापस;
	pvr2_ioपढ़ो_करोne(cp);
	pvr2_trace(PVR2_TRACE_STRUCT,"pvr2_ioread_destroy id=%p",cp);
	अगर (cp->sync_key_ptr) अणु
		kमुक्त(cp->sync_key_ptr);
		cp->sync_key_ptr = शून्य;
	पूर्ण
	kमुक्त(cp);
पूर्ण

व्योम pvr2_ioपढ़ो_set_sync_key(काष्ठा pvr2_ioपढ़ो *cp,
			      स्थिर अक्षर *sync_key_ptr,
			      अचिन्हित पूर्णांक sync_key_len)
अणु
	अगर (!cp) वापस;

	अगर (!sync_key_ptr) sync_key_len = 0;
	अगर ((sync_key_len == cp->sync_key_len) &&
	    ((!sync_key_len) ||
	     (!स_भेद(sync_key_ptr,cp->sync_key_ptr,sync_key_len)))) वापस;

	अगर (sync_key_len != cp->sync_key_len) अणु
		अगर (cp->sync_key_ptr) अणु
			kमुक्त(cp->sync_key_ptr);
			cp->sync_key_ptr = शून्य;
		पूर्ण
		cp->sync_key_len = 0;
		अगर (sync_key_len) अणु
			cp->sync_key_ptr = kदो_स्मृति(sync_key_len,GFP_KERNEL);
			अगर (cp->sync_key_ptr) अणु
				cp->sync_key_len = sync_key_len;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!cp->sync_key_len) वापस;
	स_नकल(cp->sync_key_ptr,sync_key_ptr,cp->sync_key_len);
पूर्ण

अटल व्योम pvr2_ioपढ़ो_stop(काष्ठा pvr2_ioपढ़ो *cp)
अणु
	अगर (!(cp->enabled)) वापस;
	pvr2_trace(PVR2_TRACE_START_STOP,
		   "/*---TRACE_READ---*/ pvr2_ioread_stop id=%p",cp);
	pvr2_stream_समाप्त(cp->stream);
	cp->c_buf = शून्य;
	cp->c_data_ptr = शून्य;
	cp->c_data_len = 0;
	cp->c_data_offs = 0;
	cp->enabled = 0;
	cp->stream_running = 0;
	cp->spigot_खोलो = 0;
	अगर (cp->sync_state) अणु
		pvr2_trace(PVR2_TRACE_DATA_FLOW,
			   "/*---TRACE_READ---*/ sync_state <== 0");
		cp->sync_state = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक pvr2_ioपढ़ो_start(काष्ठा pvr2_ioपढ़ो *cp)
अणु
	पूर्णांक stat;
	काष्ठा pvr2_buffer *bp;
	अगर (cp->enabled) वापस 0;
	अगर (!(cp->stream)) वापस 0;
	pvr2_trace(PVR2_TRACE_START_STOP,
		   "/*---TRACE_READ---*/ pvr2_ioread_start id=%p",cp);
	जबतक ((bp = pvr2_stream_get_idle_buffer(cp->stream)) != शून्य) अणु
		stat = pvr2_buffer_queue(bp);
		अगर (stat < 0) अणु
			pvr2_trace(PVR2_TRACE_DATA_FLOW,
				   "/*---TRACE_READ---*/ pvr2_ioread_start id=%p error=%d",
				   cp,stat);
			pvr2_ioपढ़ो_stop(cp);
			वापस stat;
		पूर्ण
	पूर्ण
	cp->enabled = !0;
	cp->c_buf = शून्य;
	cp->c_data_ptr = शून्य;
	cp->c_data_len = 0;
	cp->c_data_offs = 0;
	cp->stream_running = 0;
	अगर (cp->sync_key_len) अणु
		pvr2_trace(PVR2_TRACE_DATA_FLOW,
			   "/*---TRACE_READ---*/ sync_state <== 1");
		cp->sync_state = 1;
		cp->sync_trashed_count = 0;
		cp->sync_buf_offs = 0;
	पूर्ण
	cp->spigot_खोलो = 0;
	वापस 0;
पूर्ण

काष्ठा pvr2_stream *pvr2_ioपढ़ो_get_stream(काष्ठा pvr2_ioपढ़ो *cp)
अणु
	वापस cp->stream;
पूर्ण

पूर्णांक pvr2_ioपढ़ो_setup(काष्ठा pvr2_ioपढ़ो *cp,काष्ठा pvr2_stream *sp)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक idx;
	काष्ठा pvr2_buffer *bp;

	mutex_lock(&cp->mutex);
	करो अणु
		अगर (cp->stream) अणु
			pvr2_trace(PVR2_TRACE_START_STOP,
				   "/*---TRACE_READ---*/ pvr2_ioread_setup (tear-down) id=%p",
				   cp);
			pvr2_ioपढ़ो_stop(cp);
			pvr2_stream_समाप्त(cp->stream);
			अगर (pvr2_stream_get_buffer_count(cp->stream)) अणु
				pvr2_stream_set_buffer_count(cp->stream,0);
			पूर्ण
			cp->stream = शून्य;
		पूर्ण
		अगर (sp) अणु
			pvr2_trace(PVR2_TRACE_START_STOP,
				   "/*---TRACE_READ---*/ pvr2_ioread_setup (setup) id=%p",
				   cp);
			pvr2_stream_समाप्त(sp);
			ret = pvr2_stream_set_buffer_count(sp,BUFFER_COUNT);
			अगर (ret < 0) अणु
				mutex_unlock(&cp->mutex);
				वापस ret;
			पूर्ण
			क्रम (idx = 0; idx < BUFFER_COUNT; idx++) अणु
				bp = pvr2_stream_get_buffer(sp,idx);
				pvr2_buffer_set_buffer(bp,
						       cp->buffer_storage[idx],
						       BUFFER_SIZE);
			पूर्ण
			cp->stream = sp;
		पूर्ण
	पूर्ण जबतक (0);
	mutex_unlock(&cp->mutex);

	वापस 0;
पूर्ण

पूर्णांक pvr2_ioपढ़ो_set_enabled(काष्ठा pvr2_ioपढ़ो *cp,पूर्णांक fl)
अणु
	पूर्णांक ret = 0;
	अगर ((!fl) == (!(cp->enabled))) वापस ret;

	mutex_lock(&cp->mutex);
	करो अणु
		अगर (fl) अणु
			ret = pvr2_ioपढ़ो_start(cp);
		पूर्ण अन्यथा अणु
			pvr2_ioपढ़ो_stop(cp);
		पूर्ण
	पूर्ण जबतक (0);
	mutex_unlock(&cp->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_ioपढ़ो_get_buffer(काष्ठा pvr2_ioपढ़ो *cp)
अणु
	पूर्णांक stat;

	जबतक (cp->c_data_len <= cp->c_data_offs) अणु
		अगर (cp->c_buf) अणु
			// Flush out current buffer first.
			stat = pvr2_buffer_queue(cp->c_buf);
			अगर (stat < 0) अणु
				// Streaming error...
				pvr2_trace(PVR2_TRACE_DATA_FLOW,
					   "/*---TRACE_READ---*/ pvr2_ioread_read id=%p queue_error=%d",
					   cp,stat);
				pvr2_ioपढ़ो_stop(cp);
				वापस 0;
			पूर्ण
			cp->c_buf = शून्य;
			cp->c_data_ptr = शून्य;
			cp->c_data_len = 0;
			cp->c_data_offs = 0;
		पूर्ण
		// Now get a freshly filled buffer.
		cp->c_buf = pvr2_stream_get_पढ़ोy_buffer(cp->stream);
		अगर (!cp->c_buf) अवरोध; // Nothing पढ़ोy; करोne.
		cp->c_data_len = pvr2_buffer_get_count(cp->c_buf);
		अगर (!cp->c_data_len) अणु
			// Nothing transferred.  Was there an error?
			stat = pvr2_buffer_get_status(cp->c_buf);
			अगर (stat < 0) अणु
				// Streaming error...
				pvr2_trace(PVR2_TRACE_DATA_FLOW,
					   "/*---TRACE_READ---*/ pvr2_ioread_read id=%p buffer_error=%d",
					   cp,stat);
				pvr2_ioपढ़ो_stop(cp);
				// Give up.
				वापस 0;
			पूर्ण
			// Start over...
			जारी;
		पूर्ण
		cp->c_data_offs = 0;
		cp->c_data_ptr = cp->buffer_storage[
			pvr2_buffer_get_id(cp->c_buf)];
	पूर्ण
	वापस !0;
पूर्ण

अटल व्योम pvr2_ioपढ़ो_filter(काष्ठा pvr2_ioपढ़ो *cp)
अणु
	अचिन्हित पूर्णांक idx;
	अगर (!cp->enabled) वापस;
	अगर (cp->sync_state != 1) वापस;

	// Search the stream क्रम our synchronization key.  This is made
	// complicated by the fact that in order to be honest with
	// ourselves here we must search across buffer boundaries...
	mutex_lock(&cp->mutex);
	जबतक (1) अणु
		// Ensure we have a buffer
		अगर (!pvr2_ioपढ़ो_get_buffer(cp)) अवरोध;
		अगर (!cp->c_data_len) अवरोध;

		// Now walk the buffer contents until we match the key or
		// run out of buffer data.
		क्रम (idx = cp->c_data_offs; idx < cp->c_data_len; idx++) अणु
			अगर (cp->sync_buf_offs >= cp->sync_key_len) अवरोध;
			अगर (cp->c_data_ptr[idx] ==
			    cp->sync_key_ptr[cp->sync_buf_offs]) अणु
				// Found the next key byte
				(cp->sync_buf_offs)++;
			पूर्ण अन्यथा अणु
				// Whoops, mismatched.  Start key over...
				cp->sync_buf_offs = 0;
			पूर्ण
		पूर्ण

		// Consume what we've walked through
		cp->c_data_offs += idx;
		cp->sync_trashed_count += idx;

		// If we've found the key, then update state and get out.
		अगर (cp->sync_buf_offs >= cp->sync_key_len) अणु
			cp->sync_trashed_count -= cp->sync_key_len;
			pvr2_trace(PVR2_TRACE_DATA_FLOW,
				   "/*---TRACE_READ---*/ sync_state <== 2 (skipped %u bytes)",
				   cp->sync_trashed_count);
			cp->sync_state = 2;
			cp->sync_buf_offs = 0;
			अवरोध;
		पूर्ण

		अगर (cp->c_data_offs < cp->c_data_len) अणु
			// Sanity check - should NEVER get here
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "ERROR: pvr2_ioread filter sync problem len=%u offs=%u",
				   cp->c_data_len,cp->c_data_offs);
			// Get out so we करोn't get stuck in an infinite
			// loop.
			अवरोध;
		पूर्ण

		जारी; // (क्रम clarity)
	पूर्ण
	mutex_unlock(&cp->mutex);
पूर्ण

पूर्णांक pvr2_ioपढ़ो_avail(काष्ठा pvr2_ioपढ़ो *cp)
अणु
	पूर्णांक ret;
	अगर (!(cp->enabled)) अणु
		// Stream is not enabled; so this is an I/O error
		वापस -EIO;
	पूर्ण

	अगर (cp->sync_state == 1) अणु
		pvr2_ioपढ़ो_filter(cp);
		अगर (cp->sync_state == 1) वापस -EAGAIN;
	पूर्ण

	ret = 0;
	अगर (cp->stream_running) अणु
		अगर (!pvr2_stream_get_पढ़ोy_count(cp->stream)) अणु
			// No data available at all right now.
			ret = -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pvr2_stream_get_पढ़ोy_count(cp->stream) < BUFFER_COUNT/2) अणु
			// Haven't buffered up enough yet; try again later
			ret = -EAGAIN;
		पूर्ण
	पूर्ण

	अगर ((!(cp->spigot_खोलो)) != (!(ret == 0))) अणु
		cp->spigot_खोलो = (ret == 0);
		pvr2_trace(PVR2_TRACE_DATA_FLOW,
			   "/*---TRACE_READ---*/ data is %s",
			   cp->spigot_खोलो ? "available" : "pending");
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक pvr2_ioपढ़ो_पढ़ो(काष्ठा pvr2_ioपढ़ो *cp,व्योम __user *buf,अचिन्हित पूर्णांक cnt)
अणु
	अचिन्हित पूर्णांक copied_cnt;
	अचिन्हित पूर्णांक bcnt;
	स्थिर अक्षर *src;
	पूर्णांक stat;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक req_cnt = cnt;

	अगर (!cnt) अणु
		pvr2_trace(PVR2_TRACE_TRAP,
			   "/*---TRACE_READ---*/ pvr2_ioread_read id=%p ZERO Request? Returning zero.",
cp);
		वापस 0;
	पूर्ण

	stat = pvr2_ioपढ़ो_avail(cp);
	अगर (stat < 0) वापस stat;

	cp->stream_running = !0;

	mutex_lock(&cp->mutex);
	करो अणु

		// Suck data out of the buffers and copy to the user
		copied_cnt = 0;
		अगर (!buf) cnt = 0;
		जबतक (1) अणु
			अगर (!pvr2_ioपढ़ो_get_buffer(cp)) अणु
				ret = -EIO;
				अवरोध;
			पूर्ण

			अगर (!cnt) अवरोध;

			अगर (cp->sync_state == 2) अणु
				// We're repeating the sync key data पूर्णांकo
				// the stream.
				src = cp->sync_key_ptr + cp->sync_buf_offs;
				bcnt = cp->sync_key_len - cp->sync_buf_offs;
			पूर्ण अन्यथा अणु
				// Normal buffer copy
				src = cp->c_data_ptr + cp->c_data_offs;
				bcnt = cp->c_data_len - cp->c_data_offs;
			पूर्ण

			अगर (!bcnt) अवरोध;

			// Don't run past user's buffer
			अगर (bcnt > cnt) bcnt = cnt;

			अगर (copy_to_user(buf,src,bcnt)) अणु
				// User supplied a bad poपूर्णांकer?
				// Give up - this *will* cause data
				// to be lost.
				ret = -EFAULT;
				अवरोध;
			पूर्ण
			cnt -= bcnt;
			buf += bcnt;
			copied_cnt += bcnt;

			अगर (cp->sync_state == 2) अणु
				// Update offset inside sync key that we're
				// repeating back out.
				cp->sync_buf_offs += bcnt;
				अगर (cp->sync_buf_offs >= cp->sync_key_len) अणु
					// Consumed entire key; चयन mode
					// to normal.
					pvr2_trace(PVR2_TRACE_DATA_FLOW,
						   "/*---TRACE_READ---*/ sync_state <== 0");
					cp->sync_state = 0;
				पूर्ण
			पूर्ण अन्यथा अणु
				// Update buffer offset.
				cp->c_data_offs += bcnt;
			पूर्ण
		पूर्ण

	पूर्ण जबतक (0);
	mutex_unlock(&cp->mutex);

	अगर (!ret) अणु
		अगर (copied_cnt) अणु
			// If anything was copied, वापस that count
			ret = copied_cnt;
		पूर्ण अन्यथा अणु
			// Nothing copied; suggest to caller that another
			// attempt should be tried again later
			ret = -EAGAIN;
		पूर्ण
	पूर्ण

	pvr2_trace(PVR2_TRACE_DATA_FLOW,
		   "/*---TRACE_READ---*/ pvr2_ioread_read id=%p request=%d result=%d",
		   cp,req_cnt,ret);
	वापस ret;
पूर्ण
