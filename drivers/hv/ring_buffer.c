<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (c) 2009, Microsoft Corporation.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 *   K. Y. Srinivasan <kys@microsoft.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/uपन.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/prefetch.h>

#समावेश "hyperv_vmbus.h"

#घोषणा VMBUS_PKT_TRAILER	8

/*
 * When we ग_लिखो to the ring buffer, check अगर the host needs to
 * be संकेतed. Here is the details of this protocol:
 *
 *	1. The host guarantees that जबतक it is draining the
 *	   ring buffer, it will set the पूर्णांकerrupt_mask to
 *	   indicate it करोes not need to be पूर्णांकerrupted when
 *	   new data is placed.
 *
 *	2. The host guarantees that it will completely drain
 *	   the ring buffer beक्रमe निकासing the पढ़ो loop. Further,
 *	   once the ring buffer is empty, it will clear the
 *	   पूर्णांकerrupt_mask and re-check to see अगर new data has
 *	   arrived.
 *
 * KYS: Oct. 30, 2016:
 * It looks like Winकरोws hosts have logic to deal with DOS attacks that
 * can be triggered अगर it receives पूर्णांकerrupts when it is not expecting
 * the पूर्णांकerrupt. The host expects पूर्णांकerrupts only when the ring
 * transitions from empty to non-empty (or full to non full on the guest
 * to host ring).
 * So, base the संकेतing decision solely on the ring state until the
 * host logic is fixed.
 */

अटल व्योम hv_संकेत_on_ग_लिखो(u32 old_ग_लिखो, काष्ठा vmbus_channel *channel)
अणु
	काष्ठा hv_ring_buffer_info *rbi = &channel->outbound;

	virt_mb();
	अगर (READ_ONCE(rbi->ring_buffer->पूर्णांकerrupt_mask))
		वापस;

	/* check पूर्णांकerrupt_mask beक्रमe पढ़ो_index */
	virt_rmb();
	/*
	 * This is the only हाल we need to संकेत when the
	 * ring transitions from being empty to non-empty.
	 */
	अगर (old_ग_लिखो == READ_ONCE(rbi->ring_buffer->पढ़ो_index)) अणु
		++channel->पूर्णांकr_out_empty;
		vmbus_setevent(channel);
	पूर्ण
पूर्ण

/* Get the next ग_लिखो location क्रम the specअगरied ring buffer. */
अटल अंतरभूत u32
hv_get_next_ग_लिखो_location(काष्ठा hv_ring_buffer_info *ring_info)
अणु
	u32 next = ring_info->ring_buffer->ग_लिखो_index;

	वापस next;
पूर्ण

/* Set the next ग_लिखो location क्रम the specअगरied ring buffer. */
अटल अंतरभूत व्योम
hv_set_next_ग_लिखो_location(काष्ठा hv_ring_buffer_info *ring_info,
		     u32 next_ग_लिखो_location)
अणु
	ring_info->ring_buffer->ग_लिखो_index = next_ग_लिखो_location;
पूर्ण

/* Get the size of the ring buffer. */
अटल अंतरभूत u32
hv_get_ring_buffersize(स्थिर काष्ठा hv_ring_buffer_info *ring_info)
अणु
	वापस ring_info->ring_datasize;
पूर्ण

/* Get the पढ़ो and ग_लिखो indices as u64 of the specअगरied ring buffer. */
अटल अंतरभूत u64
hv_get_ring_bufferindices(काष्ठा hv_ring_buffer_info *ring_info)
अणु
	वापस (u64)ring_info->ring_buffer->ग_लिखो_index << 32;
पूर्ण

/*
 * Helper routine to copy from source to ring buffer.
 * Assume there is enough room. Handles wrap-around in dest हाल only!!
 */
अटल u32 hv_copyto_ringbuffer(
	काष्ठा hv_ring_buffer_info	*ring_info,
	u32				start_ग_लिखो_offset,
	स्थिर व्योम			*src,
	u32				srclen)
अणु
	व्योम *ring_buffer = hv_get_ring_buffer(ring_info);
	u32 ring_buffer_size = hv_get_ring_buffersize(ring_info);

	स_नकल(ring_buffer + start_ग_लिखो_offset, src, srclen);

	start_ग_लिखो_offset += srclen;
	अगर (start_ग_लिखो_offset >= ring_buffer_size)
		start_ग_लिखो_offset -= ring_buffer_size;

	वापस start_ग_लिखो_offset;
पूर्ण

/*
 *
 * hv_get_ringbuffer_availbytes()
 *
 * Get number of bytes available to पढ़ो and to ग_लिखो to
 * क्रम the specअगरied ring buffer
 */
अटल व्योम
hv_get_ringbuffer_availbytes(स्थिर काष्ठा hv_ring_buffer_info *rbi,
			     u32 *पढ़ो, u32 *ग_लिखो)
अणु
	u32 पढ़ो_loc, ग_लिखो_loc, dsize;

	/* Capture the पढ़ो/ग_लिखो indices beक्रमe they changed */
	पढ़ो_loc = READ_ONCE(rbi->ring_buffer->पढ़ो_index);
	ग_लिखो_loc = READ_ONCE(rbi->ring_buffer->ग_लिखो_index);
	dsize = rbi->ring_datasize;

	*ग_लिखो = ग_लिखो_loc >= पढ़ो_loc ? dsize - (ग_लिखो_loc - पढ़ो_loc) :
		पढ़ो_loc - ग_लिखो_loc;
	*पढ़ो = dsize - *ग_लिखो;
पूर्ण

/* Get various debug metrics क्रम the specअगरied ring buffer. */
पूर्णांक hv_ringbuffer_get_debuginfo(काष्ठा hv_ring_buffer_info *ring_info,
				काष्ठा hv_ring_buffer_debug_info *debug_info)
अणु
	u32 bytes_avail_toग_लिखो;
	u32 bytes_avail_toपढ़ो;

	mutex_lock(&ring_info->ring_buffer_mutex);

	अगर (!ring_info->ring_buffer) अणु
		mutex_unlock(&ring_info->ring_buffer_mutex);
		वापस -EINVAL;
	पूर्ण

	hv_get_ringbuffer_availbytes(ring_info,
				     &bytes_avail_toपढ़ो,
				     &bytes_avail_toग_लिखो);
	debug_info->bytes_avail_toपढ़ो = bytes_avail_toपढ़ो;
	debug_info->bytes_avail_toग_लिखो = bytes_avail_toग_लिखो;
	debug_info->current_पढ़ो_index = ring_info->ring_buffer->पढ़ो_index;
	debug_info->current_ग_लिखो_index = ring_info->ring_buffer->ग_लिखो_index;
	debug_info->current_पूर्णांकerrupt_mask
		= ring_info->ring_buffer->पूर्णांकerrupt_mask;
	mutex_unlock(&ring_info->ring_buffer_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hv_ringbuffer_get_debuginfo);

/* Initialize a channel's ring buffer info mutex locks */
व्योम hv_ringbuffer_pre_init(काष्ठा vmbus_channel *channel)
अणु
	mutex_init(&channel->inbound.ring_buffer_mutex);
	mutex_init(&channel->outbound.ring_buffer_mutex);
पूर्ण

/* Initialize the ring buffer. */
पूर्णांक hv_ringbuffer_init(काष्ठा hv_ring_buffer_info *ring_info,
		       काष्ठा page *pages, u32 page_cnt)
अणु
	पूर्णांक i;
	काष्ठा page **pages_wraparound;

	BUILD_BUG_ON((माप(काष्ठा hv_ring_buffer) != PAGE_SIZE));

	/*
	 * First page holds काष्ठा hv_ring_buffer, करो wraparound mapping क्रम
	 * the rest.
	 */
	pages_wraparound = kसुस्मृति(page_cnt * 2 - 1, माप(काष्ठा page *),
				   GFP_KERNEL);
	अगर (!pages_wraparound)
		वापस -ENOMEM;

	pages_wraparound[0] = pages;
	क्रम (i = 0; i < 2 * (page_cnt - 1); i++)
		pages_wraparound[i + 1] = &pages[i % (page_cnt - 1) + 1];

	ring_info->ring_buffer = (काष्ठा hv_ring_buffer *)
		vmap(pages_wraparound, page_cnt * 2 - 1, VM_MAP, PAGE_KERNEL);

	kमुक्त(pages_wraparound);


	अगर (!ring_info->ring_buffer)
		वापस -ENOMEM;

	ring_info->ring_buffer->पढ़ो_index =
		ring_info->ring_buffer->ग_लिखो_index = 0;

	/* Set the feature bit क्रम enabling flow control. */
	ring_info->ring_buffer->feature_bits.value = 1;

	ring_info->ring_size = page_cnt << PAGE_SHIFT;
	ring_info->ring_size_भाग10_reciprocal =
		reciprocal_value(ring_info->ring_size / 10);
	ring_info->ring_datasize = ring_info->ring_size -
		माप(काष्ठा hv_ring_buffer);
	ring_info->priv_पढ़ो_index = 0;

	spin_lock_init(&ring_info->ring_lock);

	वापस 0;
पूर्ण

/* Cleanup the ring buffer. */
व्योम hv_ringbuffer_cleanup(काष्ठा hv_ring_buffer_info *ring_info)
अणु
	mutex_lock(&ring_info->ring_buffer_mutex);
	vunmap(ring_info->ring_buffer);
	ring_info->ring_buffer = शून्य;
	mutex_unlock(&ring_info->ring_buffer_mutex);
पूर्ण

/* Write to the ring buffer. */
पूर्णांक hv_ringbuffer_ग_लिखो(काष्ठा vmbus_channel *channel,
			स्थिर काष्ठा kvec *kv_list, u32 kv_count,
			u64 requestid)
अणु
	पूर्णांक i;
	u32 bytes_avail_toग_लिखो;
	u32 totalbytes_toग_लिखो = माप(u64);
	u32 next_ग_लिखो_location;
	u32 old_ग_लिखो;
	u64 prev_indices;
	अचिन्हित दीर्घ flags;
	काष्ठा hv_ring_buffer_info *outring_info = &channel->outbound;
	काष्ठा vmpacket_descriptor *desc = kv_list[0].iov_base;
	u64 rqst_id = VMBUS_NO_RQSTOR;

	अगर (channel->rescind)
		वापस -ENODEV;

	क्रम (i = 0; i < kv_count; i++)
		totalbytes_toग_लिखो += kv_list[i].iov_len;

	spin_lock_irqsave(&outring_info->ring_lock, flags);

	bytes_avail_toग_लिखो = hv_get_bytes_to_ग_लिखो(outring_info);

	/*
	 * If there is only room क्रम the packet, assume it is full.
	 * Otherwise, the next समय around, we think the ring buffer
	 * is empty since the पढ़ो index == ग_लिखो index.
	 */
	अगर (bytes_avail_toग_लिखो <= totalbytes_toग_लिखो) अणु
		++channel->out_full_total;

		अगर (!channel->out_full_flag) अणु
			++channel->out_full_first;
			channel->out_full_flag = true;
		पूर्ण

		spin_unlock_irqrestore(&outring_info->ring_lock, flags);
		वापस -EAGAIN;
	पूर्ण

	channel->out_full_flag = false;

	/* Write to the ring buffer */
	next_ग_लिखो_location = hv_get_next_ग_लिखो_location(outring_info);

	old_ग_लिखो = next_ग_लिखो_location;

	क्रम (i = 0; i < kv_count; i++) अणु
		next_ग_लिखो_location = hv_copyto_ringbuffer(outring_info,
						     next_ग_लिखो_location,
						     kv_list[i].iov_base,
						     kv_list[i].iov_len);
	पूर्ण

	/*
	 * Allocate the request ID after the data has been copied पूर्णांकo the
	 * ring buffer.  Once this request ID is allocated, the completion
	 * path could find the data and मुक्त it.
	 */

	अगर (desc->flags == VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED) अणु
		rqst_id = vmbus_next_request_id(&channel->requestor, requestid);
		अगर (rqst_id == VMBUS_RQST_ERROR) अणु
			spin_unlock_irqrestore(&outring_info->ring_lock, flags);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण
	desc = hv_get_ring_buffer(outring_info) + old_ग_लिखो;
	desc->trans_id = (rqst_id == VMBUS_NO_RQSTOR) ? requestid : rqst_id;

	/* Set previous packet start */
	prev_indices = hv_get_ring_bufferindices(outring_info);

	next_ग_लिखो_location = hv_copyto_ringbuffer(outring_info,
					     next_ग_लिखो_location,
					     &prev_indices,
					     माप(u64));

	/* Issue a full memory barrier beक्रमe updating the ग_लिखो index */
	virt_mb();

	/* Now, update the ग_लिखो location */
	hv_set_next_ग_लिखो_location(outring_info, next_ग_लिखो_location);


	spin_unlock_irqrestore(&outring_info->ring_lock, flags);

	hv_संकेत_on_ग_लिखो(old_ग_लिखो, channel);

	अगर (channel->rescind) अणु
		अगर (rqst_id != VMBUS_NO_RQSTOR) अणु
			/* Reclaim request ID to aव्योम leak of IDs */
			vmbus_request_addr(&channel->requestor, rqst_id);
		पूर्ण
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hv_ringbuffer_पढ़ो(काष्ठा vmbus_channel *channel,
		       व्योम *buffer, u32 buflen, u32 *buffer_actual_len,
		       u64 *requestid, bool raw)
अणु
	काष्ठा vmpacket_descriptor *desc;
	u32 packetlen, offset;

	अगर (unlikely(buflen == 0))
		वापस -EINVAL;

	*buffer_actual_len = 0;
	*requestid = 0;

	/* Make sure there is something to पढ़ो */
	desc = hv_pkt_iter_first(channel);
	अगर (desc == शून्य) अणु
		/*
		 * No error is set when there is even no header, drivers are
		 * supposed to analyze buffer_actual_len.
		 */
		वापस 0;
	पूर्ण

	offset = raw ? 0 : (desc->offset8 << 3);
	packetlen = (desc->len8 << 3) - offset;
	*buffer_actual_len = packetlen;
	*requestid = desc->trans_id;

	अगर (unlikely(packetlen > buflen))
		वापस -ENOBUFS;

	/* since ring is द्विगुन mapped, only one copy is necessary */
	स_नकल(buffer, (स्थिर अक्षर *)desc + offset, packetlen);

	/* Advance ring index to next packet descriptor */
	__hv_pkt_iter_next(channel, desc);

	/* Notअगरy host of update */
	hv_pkt_iter_बंद(channel);

	वापस 0;
पूर्ण

/*
 * Determine number of bytes available in ring buffer after
 * the current iterator (priv_पढ़ो_index) location.
 *
 * This is similar to hv_get_bytes_to_पढ़ो but with निजी
 * पढ़ो index instead.
 */
अटल u32 hv_pkt_iter_avail(स्थिर काष्ठा hv_ring_buffer_info *rbi)
अणु
	u32 priv_पढ़ो_loc = rbi->priv_पढ़ो_index;
	u32 ग_लिखो_loc = READ_ONCE(rbi->ring_buffer->ग_लिखो_index);

	अगर (ग_लिखो_loc >= priv_पढ़ो_loc)
		वापस ग_लिखो_loc - priv_पढ़ो_loc;
	अन्यथा
		वापस (rbi->ring_datasize - priv_पढ़ो_loc) + ग_लिखो_loc;
पूर्ण

/*
 * Get first vmbus packet from ring buffer after पढ़ो_index
 *
 * If ring buffer is empty, वापसs शून्य and no other action needed.
 */
काष्ठा vmpacket_descriptor *hv_pkt_iter_first(काष्ठा vmbus_channel *channel)
अणु
	काष्ठा hv_ring_buffer_info *rbi = &channel->inbound;
	काष्ठा vmpacket_descriptor *desc;

	hv_debug_delay_test(channel, MESSAGE_DELAY);
	अगर (hv_pkt_iter_avail(rbi) < माप(काष्ठा vmpacket_descriptor))
		वापस शून्य;

	desc = hv_get_ring_buffer(rbi) + rbi->priv_पढ़ो_index;
	अगर (desc)
		prefetch((अक्षर *)desc + (desc->len8 << 3));

	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(hv_pkt_iter_first);

/*
 * Get next vmbus packet from ring buffer.
 *
 * Advances the current location (priv_पढ़ो_index) and checks क्रम more
 * data. If the end of the ring buffer is reached, then वापस शून्य.
 */
काष्ठा vmpacket_descriptor *
__hv_pkt_iter_next(काष्ठा vmbus_channel *channel,
		   स्थिर काष्ठा vmpacket_descriptor *desc)
अणु
	काष्ठा hv_ring_buffer_info *rbi = &channel->inbound;
	u32 packetlen = desc->len8 << 3;
	u32 dsize = rbi->ring_datasize;

	hv_debug_delay_test(channel, MESSAGE_DELAY);
	/* bump offset to next potential packet */
	rbi->priv_पढ़ो_index += packetlen + VMBUS_PKT_TRAILER;
	अगर (rbi->priv_पढ़ो_index >= dsize)
		rbi->priv_पढ़ो_index -= dsize;

	/* more data? */
	वापस hv_pkt_iter_first(channel);
पूर्ण
EXPORT_SYMBOL_GPL(__hv_pkt_iter_next);

/* How many bytes were पढ़ो in this iterator cycle */
अटल u32 hv_pkt_iter_bytes_पढ़ो(स्थिर काष्ठा hv_ring_buffer_info *rbi,
					u32 start_पढ़ो_index)
अणु
	अगर (rbi->priv_पढ़ो_index >= start_पढ़ो_index)
		वापस rbi->priv_पढ़ो_index - start_पढ़ो_index;
	अन्यथा
		वापस rbi->ring_datasize - start_पढ़ो_index +
			rbi->priv_पढ़ो_index;
पूर्ण

/*
 * Update host ring buffer after iterating over packets. If the host has
 * stopped queuing new entries because it found the ring buffer full, and
 * sufficient space is being मुक्तd up, संकेत the host. But be careful to
 * only संकेत the host when necessary, both क्रम perक्रमmance reasons and
 * because Hyper-V protects itself by throttling guests that संकेत
 * inappropriately.
 *
 * Determining when to संकेत is tricky. There are three key data inमाला_दो
 * that must be handled in this order to aव्योम race conditions:
 *
 * 1. Update the पढ़ो_index
 * 2. Read the pending_send_sz
 * 3. Read the current ग_लिखो_index
 *
 * The पूर्णांकerrupt_mask is not used to determine when to संकेत. The
 * पूर्णांकerrupt_mask is used only on the guest->host ring buffer when
 * sending requests to the host. The host करोes not use it on the host->
 * guest ring buffer to indicate whether it should be संकेतed.
 */
व्योम hv_pkt_iter_बंद(काष्ठा vmbus_channel *channel)
अणु
	काष्ठा hv_ring_buffer_info *rbi = &channel->inbound;
	u32 curr_ग_लिखो_sz, pending_sz, bytes_पढ़ो, start_पढ़ो_index;

	/*
	 * Make sure all पढ़ोs are करोne beक्रमe we update the पढ़ो index since
	 * the ग_लिखोr may start writing to the पढ़ो area once the पढ़ो index
	 * is updated.
	 */
	virt_rmb();
	start_पढ़ो_index = rbi->ring_buffer->पढ़ो_index;
	rbi->ring_buffer->पढ़ो_index = rbi->priv_पढ़ो_index;

	/*
	 * Older versions of Hyper-V (beक्रमe WS2102 and Win8) करो not
	 * implement pending_send_sz and simply poll अगर the host->guest
	 * ring buffer is full.  No संकेतing is needed or expected.
	 */
	अगर (!rbi->ring_buffer->feature_bits.feat_pending_send_sz)
		वापस;

	/*
	 * Issue a full memory barrier beक्रमe making the संकेतing decision.
	 * If पढ़ोing pending_send_sz were to be reordered and happen
	 * beक्रमe we commit the new पढ़ो_index, a race could occur.  If the
	 * host were to set the pending_send_sz after we have sampled
	 * pending_send_sz, and the ring buffer blocks beक्रमe we commit the
	 * पढ़ो index, we could miss sending the पूर्णांकerrupt. Issue a full
	 * memory barrier to address this.
	 */
	virt_mb();

	/*
	 * If the pending_send_sz is zero, then the ring buffer is not
	 * blocked and there is no need to संकेत.  This is far by the
	 * most common हाल, so निकास quickly क्रम best perक्रमmance.
	 */
	pending_sz = READ_ONCE(rbi->ring_buffer->pending_send_sz);
	अगर (!pending_sz)
		वापस;

	/*
	 * Ensure the पढ़ो of ग_लिखो_index in hv_get_bytes_to_ग_लिखो()
	 * happens after the पढ़ो of pending_send_sz.
	 */
	virt_rmb();
	curr_ग_लिखो_sz = hv_get_bytes_to_ग_लिखो(rbi);
	bytes_पढ़ो = hv_pkt_iter_bytes_पढ़ो(rbi, start_पढ़ो_index);

	/*
	 * We want to संकेत the host only अगर we're transitioning
	 * from a "not enough free space" state to a "enough मुक्त
	 * space" state.  For example, it's possible that this function
	 * could run and मुक्त up enough space to संकेत the host, and then
	 * run again and मुक्त up additional space beक्रमe the host has a
	 * chance to clear the pending_send_sz.  The 2nd invocation would
	 * be a null transition from "enough free space" to "enough मुक्त
	 * space", which करोesn't warrant a संकेत.
	 *
	 * Exactly filling the ring buffer is treated as "not enough
	 * space". The ring buffer always must have at least one byte
	 * empty so the empty and full conditions are distinguishable.
	 * hv_get_bytes_to_ग_लिखो() करोesn't fully tell the truth in
	 * this regard.
	 *
	 * So first check अगर we were in the "enough free space" state
	 * beक्रमe we began the iteration. If so, the host was not
	 * blocked, and there's no need to संकेत.
	 */
	अगर (curr_ग_लिखो_sz - bytes_पढ़ो > pending_sz)
		वापस;

	/*
	 * Similarly, अगर the new state is "not enough space", then
	 * there's no need to संकेत.
	 */
	अगर (curr_ग_लिखो_sz <= pending_sz)
		वापस;

	++channel->पूर्णांकr_in_full;
	vmbus_setevent(channel);
पूर्ण
EXPORT_SYMBOL_GPL(hv_pkt_iter_बंद);
