<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * SSH packet transport layer.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/atomic.h>
#समावेश <linux/error-injection.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/kref.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/सीमा.स>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/serdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/surface_aggregator/serial_hub.h>

#समावेश "ssh_msgb.h"
#समावेश "ssh_packet_layer.h"
#समावेश "ssh_parser.h"

#समावेश "trace.h"

/*
 * To simplअगरy reasoning about the code below, we define a few concepts. The
 * प्रणाली below is similar to a state-machine क्रम packets, however, there are
 * too many states to explicitly ग_लिखो them करोwn. To (somewhat) manage the
 * states and packets we rely on flags, reference counting, and some simple
 * concepts. State transitions are triggered by actions.
 *
 * >> Actions <<
 *
 * - submit
 * - transmission start (process next item in queue)
 * - transmission finished (guaranteed to never be parallel to transmission
 *   start)
 * - ACK received
 * - NAK received (this is equivalent to issuing re-submit क्रम all pending
 *   packets)
 * - समयout (this is equivalent to re-issuing a submit or canceling)
 * - cancel (non-pending and pending)
 *
 * >> Data Structures, Packet Ownership, General Overview <<
 *
 * The code below employs two मुख्य data काष्ठाures: The packet queue,
 * containing all packets scheduled क्रम transmission, and the set of pending
 * packets, containing all packets aरुकोing an ACK.
 *
 * Shared ownership of a packet is controlled via reference counting. Inside
 * the transport प्रणाली are a total of five packet owners:
 *
 * - the packet queue,
 * - the pending set,
 * - the transmitter thपढ़ो,
 * - the receiver thपढ़ो (via ACKing), and
 * - the समयout work item.
 *
 * Normal operation is as follows: The initial reference of the packet is
 * obtained by submitting the packet and queuing it. The receiver thपढ़ो takes
 * packets from the queue. By करोing this, it करोes not increment the refcount
 * but takes over the reference (removing it from the queue). If the packet is
 * sequenced (i.e. needs to be ACKed by the client), the transmitter thपढ़ो
 * sets-up the समयout and adds the packet to the pending set beक्रमe starting
 * to transmit it. As the समयout is handled by a reaper task, no additional
 * reference क्रम it is needed. After the transmit is करोne, the reference held
 * by the transmitter thपढ़ो is dropped. If the packet is unsequenced (i.e.
 * करोes not need an ACK), the packet is completed by the transmitter thपढ़ो
 * beक्रमe dropping that reference.
 *
 * On receival of an ACK, the receiver thपढ़ो हटाओs and obtains the
 * reference to the packet from the pending set. The receiver thपढ़ो will then
 * complete the packet and drop its reference.
 *
 * On receival of a NAK, the receiver thपढ़ो re-submits all currently pending
 * packets.
 *
 * Packet समयouts are detected by the समयout reaper. This is a task,
 * scheduled depending on the earliest packet समयout expiration date,
 * checking all currently pending packets अगर their समयout has expired. If the
 * समयout of a packet has expired, it is re-submitted and the number of tries
 * of this packet is incremented. If this number reaches its limit, the packet
 * will be completed with a failure.
 *
 * On transmission failure (such as repeated packet समयouts), the completion
 * callback is immediately run by on thपढ़ो on which the error was detected.
 *
 * To ensure that a packet eventually leaves the प्रणाली it is marked as
 * "locked" directly beक्रमe it is going to be completed or when it is
 * canceled. Marking a packet as "locked" has the effect that passing and
 * creating new references of the packet is disallowed. This means that the
 * packet cannot be added to the queue, the pending set, and the समयout, or
 * be picked up by the transmitter thपढ़ो or receiver thपढ़ो. To हटाओ a
 * packet from the प्रणाली it has to be marked as locked and subsequently all
 * references from the data काष्ठाures (queue, pending) have to be हटाओd.
 * References held by thपढ़ोs will eventually be dropped स्वतःmatically as
 * their execution progresses.
 *
 * Note that the packet completion callback is, in हाल of success and क्रम a
 * sequenced packet, guaranteed to run on the receiver thपढ़ो, thus providing
 * a way to reliably identअगरy responses to the packet. The packet completion
 * callback is only run once and it करोes not indicate that the packet has
 * fully left the प्रणाली (क्रम this, one should rely on the release method,
 * triggered when the reference count of the packet reaches zero). In हाल of
 * re-submission (and with somewhat unlikely timing), it may be possible that
 * the packet is being re-transmitted जबतक the completion callback runs.
 * Completion will occur both on success and पूर्णांकernal error, as well as when
 * the packet is canceled.
 *
 * >> Flags <<
 *
 * Flags are used to indicate the state and progression of a packet. Some flags
 * have stricter guarantees than other:
 *
 * - locked
 *   Indicates अगर the packet is locked. If the packet is locked, passing and/or
 *   creating additional references to the packet is क्रमbidden. The packet thus
 *   may not be queued, dequeued, or हटाओd or added to the pending set. Note
 *   that the packet state flags may still change (e.g. it may be marked as
 *   ACKed, transmitted, ...).
 *
 * - completed
 *   Indicates अगर the packet completion callback has been executed or is about
 *   to be executed. This flag is used to ensure that the packet completion
 *   callback is only run once.
 *
 * - queued
 *   Indicates अगर a packet is present in the submission queue or not. This flag
 *   must only be modअगरied with the queue lock held, and must be coherent to the
 *   presence of the packet in the queue.
 *
 * - pending
 *   Indicates अगर a packet is present in the set of pending packets or not.
 *   This flag must only be modअगरied with the pending lock held, and must be
 *   coherent to the presence of the packet in the pending set.
 *
 * - transmitting
 *   Indicates अगर the packet is currently transmitting. In हाल of
 *   re-transmissions, it is only safe to रुको on the "transmitted" completion
 *   after this flag has been set. The completion will be set both in success
 *   and error हाल.
 *
 * - transmitted
 *   Indicates अगर the packet has been transmitted. This flag is not cleared by
 *   the प्रणाली, thus it indicates the first transmission only.
 *
 * - acked
 *   Indicates अगर the packet has been acknowledged by the client. There are no
 *   other guarantees given. For example, the packet may still be canceled
 *   and/or the completion may be triggered an error even though this bit is
 *   set. Rely on the status provided to the completion callback instead.
 *
 * - canceled
 *   Indicates अगर the packet has been canceled from the outside. There are no
 *   other guarantees given. Specअगरically, the packet may be completed by
 *   another part of the प्रणाली beक्रमe the cancellation attempts to complete it.
 *
 * >> General Notes <<
 *
 * - To aव्योम deadlocks, अगर both queue and pending locks are required, the
 *   pending lock must be acquired beक्रमe the queue lock.
 *
 * - The packet priority must be accessed only जबतक holding the queue lock.
 *
 * - The packet बारtamp must be accessed only जबतक holding the pending
 *   lock.
 */

/*
 * SSH_PTL_MAX_PACKET_TRIES - Maximum transmission attempts क्रम packet.
 *
 * Maximum number of transmission attempts per sequenced packet in हाल of
 * समय-outs. Must be smaller than 16. If the packet बार out after this
 * amount of tries, the packet will be completed with %-ETIMEDOUT as status
 * code.
 */
#घोषणा SSH_PTL_MAX_PACKET_TRIES		3

/*
 * SSH_PTL_TX_TIMEOUT - Packet transmission समयout.
 *
 * Timeout in jअगरfies क्रम packet transmission via the underlying serial
 * device. If transmitting the packet takes दीर्घer than this समयout, the
 * packet will be completed with -ETIMEDOUT. It will not be re-submitted.
 */
#घोषणा SSH_PTL_TX_TIMEOUT			HZ

/*
 * SSH_PTL_PACKET_TIMEOUT - Packet response समयout.
 *
 * Timeout as kसमय_प्रकार delta क्रम ACKs. If we have not received an ACK in this
 * समय-frame after starting transmission, the packet will be re-submitted.
 */
#घोषणा SSH_PTL_PACKET_TIMEOUT			ms_to_kसमय(1000)

/*
 * SSH_PTL_PACKET_TIMEOUT_RESOLUTION - Packet समयout granularity.
 *
 * Time-resolution क्रम समयouts. Should be larger than one jअगरfy to aव्योम
 * direct re-scheduling of reaper work_काष्ठा.
 */
#घोषणा SSH_PTL_PACKET_TIMEOUT_RESOLUTION	ms_to_kसमय(max(2000 / HZ, 50))

/*
 * SSH_PTL_MAX_PENDING - Maximum number of pending packets.
 *
 * Maximum number of sequenced packets concurrently रुकोing क्रम an ACK.
 * Packets marked as blocking will not be transmitted जबतक this limit is
 * reached.
 */
#घोषणा SSH_PTL_MAX_PENDING			1

/*
 * SSH_PTL_RX_BUF_LEN - Evaluation-buffer size in bytes.
 */
#घोषणा SSH_PTL_RX_BUF_LEN			4096

/*
 * SSH_PTL_RX_FIFO_LEN - Fअगरo input-buffer size in bytes.
 */
#घोषणा SSH_PTL_RX_FIFO_LEN			4096

#अगर_घोषित CONFIG_SURFACE_AGGREGATOR_ERROR_INJECTION

/**
 * ssh_ptl_should_drop_ack_packet() - Error injection hook to drop ACK packets.
 *
 * Useful to test detection and handling of स्वतःmated re-transmits by the EC.
 * Specअगरically of packets that the EC considers not-ACKed but the driver
 * alपढ़ोy considers ACKed (due to dropped ACK). In this हाल, the EC
 * re-transmits the packet-to-be-ACKed and the driver should detect it as
 * duplicate/alपढ़ोy handled. Note that the driver should still send an ACK
 * क्रम the re-transmitted packet.
 */
अटल noअंतरभूत bool ssh_ptl_should_drop_ack_packet(व्योम)
अणु
	वापस false;
पूर्ण
ALLOW_ERROR_INJECTION(ssh_ptl_should_drop_ack_packet, TRUE);

/**
 * ssh_ptl_should_drop_nak_packet() - Error injection hook to drop NAK packets.
 *
 * Useful to test/क्रमce स्वतःmated (समयout-based) re-transmit by the EC.
 * Specअगरically, packets that have not reached the driver completely/with valid
 * checksums. Only useful in combination with receival of (injected) bad data.
 */
अटल noअंतरभूत bool ssh_ptl_should_drop_nak_packet(व्योम)
अणु
	वापस false;
पूर्ण
ALLOW_ERROR_INJECTION(ssh_ptl_should_drop_nak_packet, TRUE);

/**
 * ssh_ptl_should_drop_dsq_packet() - Error injection hook to drop sequenced
 * data packet.
 *
 * Useful to test re-transmit समयout of the driver. If the data packet has not
 * been ACKed after a certain समय, the driver should re-transmit the packet up
 * to limited number of बार defined in SSH_PTL_MAX_PACKET_TRIES.
 */
अटल noअंतरभूत bool ssh_ptl_should_drop_dsq_packet(व्योम)
अणु
	वापस false;
पूर्ण
ALLOW_ERROR_INJECTION(ssh_ptl_should_drop_dsq_packet, TRUE);

/**
 * ssh_ptl_should_fail_ग_लिखो() - Error injection hook to make
 * serdev_device_ग_लिखो() fail.
 *
 * Hook to simulate errors in serdev_device_ग_लिखो when transmitting packets.
 */
अटल noअंतरभूत पूर्णांक ssh_ptl_should_fail_ग_लिखो(व्योम)
अणु
	वापस 0;
पूर्ण
ALLOW_ERROR_INJECTION(ssh_ptl_should_fail_ग_लिखो, ERRNO);

/**
 * ssh_ptl_should_corrupt_tx_data() - Error injection hook to simulate invalid
 * data being sent to the EC.
 *
 * Hook to simulate corrupt/invalid data being sent from host (driver) to EC.
 * Causes the packet data to be actively corrupted by overwriting it with
 * pre-defined values, such that it becomes invalid, causing the EC to respond
 * with a NAK packet. Useful to test handling of NAK packets received by the
 * driver.
 */
अटल noअंतरभूत bool ssh_ptl_should_corrupt_tx_data(व्योम)
अणु
	वापस false;
पूर्ण
ALLOW_ERROR_INJECTION(ssh_ptl_should_corrupt_tx_data, TRUE);

/**
 * ssh_ptl_should_corrupt_rx_syn() - Error injection hook to simulate invalid
 * data being sent by the EC.
 *
 * Hook to simulate invalid SYN bytes, i.e. an invalid start of messages and
 * test handling thereof in the driver.
 */
अटल noअंतरभूत bool ssh_ptl_should_corrupt_rx_syn(व्योम)
अणु
	वापस false;
पूर्ण
ALLOW_ERROR_INJECTION(ssh_ptl_should_corrupt_rx_syn, TRUE);

/**
 * ssh_ptl_should_corrupt_rx_data() - Error injection hook to simulate invalid
 * data being sent by the EC.
 *
 * Hook to simulate invalid data/checksum of the message frame and test handling
 * thereof in the driver.
 */
अटल noअंतरभूत bool ssh_ptl_should_corrupt_rx_data(व्योम)
अणु
	वापस false;
पूर्ण
ALLOW_ERROR_INJECTION(ssh_ptl_should_corrupt_rx_data, TRUE);

अटल bool __ssh_ptl_should_drop_ack_packet(काष्ठा ssh_packet *packet)
अणु
	अगर (likely(!ssh_ptl_should_drop_ack_packet()))
		वापस false;

	trace_ssam_ei_tx_drop_ack_packet(packet);
	ptl_info(packet->ptl, "packet error injection: dropping ACK packet %p\n",
		 packet);

	वापस true;
पूर्ण

अटल bool __ssh_ptl_should_drop_nak_packet(काष्ठा ssh_packet *packet)
अणु
	अगर (likely(!ssh_ptl_should_drop_nak_packet()))
		वापस false;

	trace_ssam_ei_tx_drop_nak_packet(packet);
	ptl_info(packet->ptl, "packet error injection: dropping NAK packet %p\n",
		 packet);

	वापस true;
पूर्ण

अटल bool __ssh_ptl_should_drop_dsq_packet(काष्ठा ssh_packet *packet)
अणु
	अगर (likely(!ssh_ptl_should_drop_dsq_packet()))
		वापस false;

	trace_ssam_ei_tx_drop_dsq_packet(packet);
	ptl_info(packet->ptl,
		 "packet error injection: dropping sequenced data packet %p\n",
		 packet);

	वापस true;
पूर्ण

अटल bool ssh_ptl_should_drop_packet(काष्ठा ssh_packet *packet)
अणु
	/* Ignore packets that करोn't carry any data (i.e. flush). */
	अगर (!packet->data.ptr || !packet->data.len)
		वापस false;

	चयन (packet->data.ptr[SSH_MSGOFFSET_FRAME(type)]) अणु
	हाल SSH_FRAME_TYPE_ACK:
		वापस __ssh_ptl_should_drop_ack_packet(packet);

	हाल SSH_FRAME_TYPE_NAK:
		वापस __ssh_ptl_should_drop_nak_packet(packet);

	हाल SSH_FRAME_TYPE_DATA_SEQ:
		वापस __ssh_ptl_should_drop_dsq_packet(packet);

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक ssh_ptl_ग_लिखो_buf(काष्ठा ssh_ptl *ptl, काष्ठा ssh_packet *packet,
			     स्थिर अचिन्हित अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक status;

	status = ssh_ptl_should_fail_ग_लिखो();
	अगर (unlikely(status)) अणु
		trace_ssam_ei_tx_fail_ग_लिखो(packet, status);
		ptl_info(packet->ptl,
			 "packet error injection: simulating transmit error %d, packet %p\n",
			 status, packet);

		वापस status;
	पूर्ण

	वापस serdev_device_ग_लिखो_buf(ptl->serdev, buf, count);
पूर्ण

अटल व्योम ssh_ptl_tx_inject_invalid_data(काष्ठा ssh_packet *packet)
अणु
	/* Ignore packets that करोn't carry any data (i.e. flush). */
	अगर (!packet->data.ptr || !packet->data.len)
		वापस;

	/* Only allow sequenced data packets to be modअगरied. */
	अगर (packet->data.ptr[SSH_MSGOFFSET_FRAME(type)] != SSH_FRAME_TYPE_DATA_SEQ)
		वापस;

	अगर (likely(!ssh_ptl_should_corrupt_tx_data()))
		वापस;

	trace_ssam_ei_tx_corrupt_data(packet);
	ptl_info(packet->ptl,
		 "packet error injection: simulating invalid transmit data on packet %p\n",
		 packet);

	/*
	 * NB: The value 0xb3 has been chosen more or less अक्रमomly so that it
	 * करोesn't have any (major) overlap with the SYN bytes (aa 55) and is
	 * non-trivial (i.e. non-zero, non-0xff).
	 */
	स_रखो(packet->data.ptr, 0xb3, packet->data.len);
पूर्ण

अटल व्योम ssh_ptl_rx_inject_invalid_syn(काष्ठा ssh_ptl *ptl,
					  काष्ठा ssam_span *data)
अणु
	काष्ठा ssam_span frame;

	/* Check अगर there actually is something to corrupt. */
	अगर (!sshp_find_syn(data, &frame))
		वापस;

	अगर (likely(!ssh_ptl_should_corrupt_rx_syn()))
		वापस;

	trace_ssam_ei_rx_corrupt_syn(data->len);

	data->ptr[1] = 0xb3;	/* Set second byte of SYN to "random" value. */
पूर्ण

अटल व्योम ssh_ptl_rx_inject_invalid_data(काष्ठा ssh_ptl *ptl,
					   काष्ठा ssam_span *frame)
अणु
	माप_प्रकार payload_len, message_len;
	काष्ठा ssh_frame *sshf;

	/* Ignore incomplete messages, will get handled once it's complete. */
	अगर (frame->len < SSH_MESSAGE_LENGTH(0))
		वापस;

	/* Ignore incomplete messages, part 2. */
	payload_len = get_unaligned_le16(&frame->ptr[SSH_MSGOFFSET_FRAME(len)]);
	message_len = SSH_MESSAGE_LENGTH(payload_len);
	अगर (frame->len < message_len)
		वापस;

	अगर (likely(!ssh_ptl_should_corrupt_rx_data()))
		वापस;

	sshf = (काष्ठा ssh_frame *)&frame->ptr[SSH_MSGOFFSET_FRAME(type)];
	trace_ssam_ei_rx_corrupt_data(sshf);

	/*
	 * Flip bits in first byte of payload checksum. This is basically
	 * equivalent to a payload/frame data error without us having to worry
	 * about (the, arguably pretty small, probability of) accidental
	 * checksum collisions.
	 */
	frame->ptr[frame->len - 2] = ~frame->ptr[frame->len - 2];
पूर्ण

#अन्यथा /* CONFIG_SURFACE_AGGREGATOR_ERROR_INJECTION */

अटल अंतरभूत bool ssh_ptl_should_drop_packet(काष्ठा ssh_packet *packet)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक ssh_ptl_ग_लिखो_buf(काष्ठा ssh_ptl *ptl,
				    काष्ठा ssh_packet *packet,
				    स्थिर अचिन्हित अक्षर *buf,
				    माप_प्रकार count)
अणु
	वापस serdev_device_ग_लिखो_buf(ptl->serdev, buf, count);
पूर्ण

अटल अंतरभूत व्योम ssh_ptl_tx_inject_invalid_data(काष्ठा ssh_packet *packet)
अणु
पूर्ण

अटल अंतरभूत व्योम ssh_ptl_rx_inject_invalid_syn(काष्ठा ssh_ptl *ptl,
						 काष्ठा ssam_span *data)
अणु
पूर्ण

अटल अंतरभूत व्योम ssh_ptl_rx_inject_invalid_data(काष्ठा ssh_ptl *ptl,
						  काष्ठा ssam_span *frame)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_SURFACE_AGGREGATOR_ERROR_INJECTION */

अटल व्योम __ssh_ptl_packet_release(काष्ठा kref *kref)
अणु
	काष्ठा ssh_packet *p = container_of(kref, काष्ठा ssh_packet, refcnt);

	trace_ssam_packet_release(p);

	ptl_dbg_cond(p->ptl, "ptl: releasing packet %p\n", p);
	p->ops->release(p);
पूर्ण

/**
 * ssh_packet_get() - Increment reference count of packet.
 * @packet: The packet to increment the reference count of.
 *
 * Increments the reference count of the given packet. See ssh_packet_put()
 * क्रम the counter-part of this function.
 *
 * Return: Returns the packet provided as input.
 */
काष्ठा ssh_packet *ssh_packet_get(काष्ठा ssh_packet *packet)
अणु
	अगर (packet)
		kref_get(&packet->refcnt);
	वापस packet;
पूर्ण
EXPORT_SYMBOL_GPL(ssh_packet_get);

/**
 * ssh_packet_put() - Decrement reference count of packet.
 * @packet: The packet to decrement the reference count of.
 *
 * If the reference count reaches zero, the ``release`` callback specअगरied in
 * the packet's &काष्ठा ssh_packet_ops, i.e. ``packet->ops->release``, will be
 * called.
 *
 * See ssh_packet_get() क्रम the counter-part of this function.
 */
व्योम ssh_packet_put(काष्ठा ssh_packet *packet)
अणु
	अगर (packet)
		kref_put(&packet->refcnt, __ssh_ptl_packet_release);
पूर्ण
EXPORT_SYMBOL_GPL(ssh_packet_put);

अटल u8 ssh_packet_get_seq(काष्ठा ssh_packet *packet)
अणु
	वापस packet->data.ptr[SSH_MSGOFFSET_FRAME(seq)];
पूर्ण

/**
 * ssh_packet_init() - Initialize SSH packet.
 * @packet:   The packet to initialize.
 * @type:     Type-flags of the packet.
 * @priority: Priority of the packet. See SSH_PACKET_PRIORITY() क्रम details.
 * @ops:      Packet operations.
 *
 * Initializes the given SSH packet. Sets the transmission buffer poपूर्णांकer to
 * %शून्य and the transmission buffer length to zero. For data-type packets,
 * this buffer has to be set separately via ssh_packet_set_data() beक्रमe
 * submission, and must contain a valid SSH message, i.e. frame with optional
 * payload of any type.
 */
व्योम ssh_packet_init(काष्ठा ssh_packet *packet, अचिन्हित दीर्घ type,
		     u8 priority, स्थिर काष्ठा ssh_packet_ops *ops)
अणु
	kref_init(&packet->refcnt);

	packet->ptl = शून्य;
	INIT_LIST_HEAD(&packet->queue_node);
	INIT_LIST_HEAD(&packet->pending_node);

	packet->state = type & SSH_PACKET_FLAGS_TY_MASK;
	packet->priority = priority;
	packet->बारtamp = KTIME_MAX;

	packet->data.ptr = शून्य;
	packet->data.len = 0;

	packet->ops = ops;
पूर्ण

अटल काष्ठा kmem_cache *ssh_ctrl_packet_cache;

/**
 * ssh_ctrl_packet_cache_init() - Initialize the control packet cache.
 */
पूर्णांक ssh_ctrl_packet_cache_init(व्योम)
अणु
	स्थिर अचिन्हित पूर्णांक size = माप(काष्ठा ssh_packet) + SSH_MSG_LEN_CTRL;
	स्थिर अचिन्हित पूर्णांक align = __alignof__(काष्ठा ssh_packet);
	काष्ठा kmem_cache *cache;

	cache = kmem_cache_create("ssam_ctrl_packet", size, align, 0, शून्य);
	अगर (!cache)
		वापस -ENOMEM;

	ssh_ctrl_packet_cache = cache;
	वापस 0;
पूर्ण

/**
 * ssh_ctrl_packet_cache_destroy() - Deinitialize the control packet cache.
 */
व्योम ssh_ctrl_packet_cache_destroy(व्योम)
अणु
	kmem_cache_destroy(ssh_ctrl_packet_cache);
	ssh_ctrl_packet_cache = शून्य;
पूर्ण

/**
 * ssh_ctrl_packet_alloc() - Allocate packet from control packet cache.
 * @packet: Where the poपूर्णांकer to the newly allocated packet should be stored.
 * @buffer: The buffer corresponding to this packet.
 * @flags:  Flags used क्रम allocation.
 *
 * Allocates a packet and corresponding transport buffer from the control
 * packet cache. Sets the packet's buffer reference to the allocated buffer.
 * The packet must be मुक्तd via ssh_ctrl_packet_मुक्त(), which will also मुक्त
 * the corresponding buffer. The corresponding buffer must not be मुक्तd
 * separately. Intended to be used with %ssh_ptl_ctrl_packet_ops as packet
 * operations.
 *
 * Return: Returns zero on success, %-ENOMEM अगर the allocation failed.
 */
अटल पूर्णांक ssh_ctrl_packet_alloc(काष्ठा ssh_packet **packet,
				 काष्ठा ssam_span *buffer, gfp_t flags)
अणु
	*packet = kmem_cache_alloc(ssh_ctrl_packet_cache, flags);
	अगर (!*packet)
		वापस -ENOMEM;

	buffer->ptr = (u8 *)(*packet + 1);
	buffer->len = SSH_MSG_LEN_CTRL;

	trace_ssam_ctrl_packet_alloc(*packet, buffer->len);
	वापस 0;
पूर्ण

/**
 * ssh_ctrl_packet_मुक्त() - Free packet allocated from control packet cache.
 * @p: The packet to मुक्त.
 */
अटल व्योम ssh_ctrl_packet_मुक्त(काष्ठा ssh_packet *p)
अणु
	trace_ssam_ctrl_packet_मुक्त(p);
	kmem_cache_मुक्त(ssh_ctrl_packet_cache, p);
पूर्ण

अटल स्थिर काष्ठा ssh_packet_ops ssh_ptl_ctrl_packet_ops = अणु
	.complete = शून्य,
	.release = ssh_ctrl_packet_मुक्त,
पूर्ण;

अटल व्योम ssh_ptl_समयout_reaper_mod(काष्ठा ssh_ptl *ptl, kसमय_प्रकार now,
				       kसमय_प्रकार expires)
अणु
	अचिन्हित दीर्घ delta = msecs_to_jअगरfies(kसमय_ms_delta(expires, now));
	kसमय_प्रकार aexp = kसमय_add(expires, SSH_PTL_PACKET_TIMEOUT_RESOLUTION);

	spin_lock(&ptl->rtx_समयout.lock);

	/* Re-adjust / schedule reaper only अगर it is above resolution delta. */
	अगर (kसमय_beक्रमe(aexp, ptl->rtx_समयout.expires)) अणु
		ptl->rtx_समयout.expires = expires;
		mod_delayed_work(प्रणाली_wq, &ptl->rtx_समयout.reaper, delta);
	पूर्ण

	spin_unlock(&ptl->rtx_समयout.lock);
पूर्ण

/* Must be called with queue lock held. */
अटल व्योम ssh_packet_next_try(काष्ठा ssh_packet *p)
अणु
	u8 base = ssh_packet_priority_get_base(p->priority);
	u8 try = ssh_packet_priority_get_try(p->priority);

	lockdep_निश्चित_held(&p->ptl->queue.lock);

	/*
	 * Ensure that we ग_लिखो the priority in one go via WRITE_ONCE() so we
	 * can access it via READ_ONCE() क्रम tracing. Note that other access
	 * is guarded by the queue lock, so no need to use READ_ONCE() there.
	 */
	WRITE_ONCE(p->priority, __SSH_PACKET_PRIORITY(base, try + 1));
पूर्ण

/* Must be called with queue lock held. */
अटल काष्ठा list_head *__ssh_ptl_queue_find_entrypoपूर्णांक(काष्ठा ssh_packet *p)
अणु
	काष्ठा list_head *head;
	काष्ठा ssh_packet *q;

	lockdep_निश्चित_held(&p->ptl->queue.lock);

	/*
	 * We generally assume that there are less control (ACK/NAK) packets
	 * and re-submitted data packets as there are normal data packets (at
	 * least in situations in which many packets are queued; अगर there
	 * aren't many packets queued the decision on how to iterate should be
	 * basically irrelevant; the number of control/data packets is more or
	 * less limited via the maximum number of pending packets). Thus, when
	 * inserting a control or re-submitted data packet, (determined by
	 * their priority), we search from front to back. Normal data packets
	 * are, usually queued directly at the tail of the queue, so क्रम those
	 * search from back to front.
	 */

	अगर (p->priority > SSH_PACKET_PRIORITY(DATA, 0)) अणु
		list_क्रम_each(head, &p->ptl->queue.head) अणु
			q = list_entry(head, काष्ठा ssh_packet, queue_node);

			अगर (q->priority < p->priority)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_prev(head, &p->ptl->queue.head) अणु
			q = list_entry(head, काष्ठा ssh_packet, queue_node);

			अगर (q->priority >= p->priority) अणु
				head = head->next;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस head;
पूर्ण

/* Must be called with queue lock held. */
अटल पूर्णांक __ssh_ptl_queue_push(काष्ठा ssh_packet *packet)
अणु
	काष्ठा ssh_ptl *ptl = packet->ptl;
	काष्ठा list_head *head;

	lockdep_निश्चित_held(&ptl->queue.lock);

	अगर (test_bit(SSH_PTL_SF_SHUTDOWN_BIT, &ptl->state))
		वापस -ESHUTDOWN;

	/* Aव्योम further transitions when canceling/completing. */
	अगर (test_bit(SSH_PACKET_SF_LOCKED_BIT, &packet->state))
		वापस -EINVAL;

	/* If this packet has alपढ़ोy been queued, करो not add it. */
	अगर (test_and_set_bit(SSH_PACKET_SF_QUEUED_BIT, &packet->state))
		वापस -EALREADY;

	head = __ssh_ptl_queue_find_entrypoपूर्णांक(packet);

	list_add_tail(&ssh_packet_get(packet)->queue_node, head);
	वापस 0;
पूर्ण

अटल पूर्णांक ssh_ptl_queue_push(काष्ठा ssh_packet *packet)
अणु
	पूर्णांक status;

	spin_lock(&packet->ptl->queue.lock);
	status = __ssh_ptl_queue_push(packet);
	spin_unlock(&packet->ptl->queue.lock);

	वापस status;
पूर्ण

अटल व्योम ssh_ptl_queue_हटाओ(काष्ठा ssh_packet *packet)
अणु
	काष्ठा ssh_ptl *ptl = packet->ptl;

	spin_lock(&ptl->queue.lock);

	अगर (!test_and_clear_bit(SSH_PACKET_SF_QUEUED_BIT, &packet->state)) अणु
		spin_unlock(&ptl->queue.lock);
		वापस;
	पूर्ण

	list_del(&packet->queue_node);

	spin_unlock(&ptl->queue.lock);
	ssh_packet_put(packet);
पूर्ण

अटल व्योम ssh_ptl_pending_push(काष्ठा ssh_packet *p)
अणु
	काष्ठा ssh_ptl *ptl = p->ptl;
	स्थिर kसमय_प्रकार बारtamp = kसमय_get_coarse_bootसमय();
	स्थिर kसमय_प्रकार समयout = ptl->rtx_समयout.समयout;

	/*
	 * Note: We can get the समय क्रम the बारtamp beक्रमe acquiring the
	 * lock as this is the only place we're setting it and this function
	 * is called only from the transmitter thपढ़ो. Thus it is not possible
	 * to overग_लिखो the बारtamp with an outdated value below.
	 */

	spin_lock(&ptl->pending.lock);

	/* If we are canceling/completing this packet, करो not add it. */
	अगर (test_bit(SSH_PACKET_SF_LOCKED_BIT, &p->state)) अणु
		spin_unlock(&ptl->pending.lock);
		वापस;
	पूर्ण

	/*
	 * On re-submission, the packet has alपढ़ोy been added the pending
	 * set. We still need to update the बारtamp as the packet समयout is
	 * reset क्रम each (re-)submission.
	 */
	p->बारtamp = बारtamp;

	/* In हाल it is alपढ़ोy pending (e.g. re-submission), करो not add it. */
	अगर (!test_and_set_bit(SSH_PACKET_SF_PENDING_BIT, &p->state)) अणु
		atomic_inc(&ptl->pending.count);
		list_add_tail(&ssh_packet_get(p)->pending_node, &ptl->pending.head);
	पूर्ण

	spin_unlock(&ptl->pending.lock);

	/* Arm/update समयout reaper. */
	ssh_ptl_समयout_reaper_mod(ptl, बारtamp, बारtamp + समयout);
पूर्ण

अटल व्योम ssh_ptl_pending_हटाओ(काष्ठा ssh_packet *packet)
अणु
	काष्ठा ssh_ptl *ptl = packet->ptl;

	spin_lock(&ptl->pending.lock);

	अगर (!test_and_clear_bit(SSH_PACKET_SF_PENDING_BIT, &packet->state)) अणु
		spin_unlock(&ptl->pending.lock);
		वापस;
	पूर्ण

	list_del(&packet->pending_node);
	atomic_dec(&ptl->pending.count);

	spin_unlock(&ptl->pending.lock);

	ssh_packet_put(packet);
पूर्ण

/* Warning: Does not check/set "completed" bit. */
अटल व्योम __ssh_ptl_complete(काष्ठा ssh_packet *p, पूर्णांक status)
अणु
	काष्ठा ssh_ptl *ptl = READ_ONCE(p->ptl);

	trace_ssam_packet_complete(p, status);
	ptl_dbg_cond(ptl, "ptl: completing packet %p (status: %d)\n", p, status);

	अगर (p->ops->complete)
		p->ops->complete(p, status);
पूर्ण

अटल व्योम ssh_ptl_हटाओ_and_complete(काष्ठा ssh_packet *p, पूर्णांक status)
अणु
	/*
	 * A call to this function should in general be preceded by
	 * set_bit(SSH_PACKET_SF_LOCKED_BIT, &p->flags) to aव्योम re-adding the
	 * packet to the काष्ठाures it's going to be हटाओd from.
	 *
	 * The set_bit call करोes not need explicit memory barriers as the
	 * implicit barrier of the test_and_set_bit() call below ensure that the
	 * flag is visible beक्रमe we actually attempt to हटाओ the packet.
	 */

	अगर (test_and_set_bit(SSH_PACKET_SF_COMPLETED_BIT, &p->state))
		वापस;

	ssh_ptl_queue_हटाओ(p);
	ssh_ptl_pending_हटाओ(p);

	__ssh_ptl_complete(p, status);
पूर्ण

अटल bool ssh_ptl_tx_can_process(काष्ठा ssh_packet *packet)
अणु
	काष्ठा ssh_ptl *ptl = packet->ptl;

	अगर (test_bit(SSH_PACKET_TY_FLUSH_BIT, &packet->state))
		वापस !atomic_पढ़ो(&ptl->pending.count);

	/* We can always process non-blocking packets. */
	अगर (!test_bit(SSH_PACKET_TY_BLOCKING_BIT, &packet->state))
		वापस true;

	/* If we are alपढ़ोy रुकोing क्रम this packet, send it again. */
	अगर (test_bit(SSH_PACKET_SF_PENDING_BIT, &packet->state))
		वापस true;

	/* Otherwise: Check अगर we have the capacity to send. */
	वापस atomic_पढ़ो(&ptl->pending.count) < SSH_PTL_MAX_PENDING;
पूर्ण

अटल काष्ठा ssh_packet *ssh_ptl_tx_pop(काष्ठा ssh_ptl *ptl)
अणु
	काष्ठा ssh_packet *packet = ERR_PTR(-ENOENT);
	काष्ठा ssh_packet *p, *n;

	spin_lock(&ptl->queue.lock);
	list_क्रम_each_entry_safe(p, n, &ptl->queue.head, queue_node) अणु
		/*
		 * If we are canceling or completing this packet, ignore it.
		 * It's going to be हटाओd from this queue लघुly.
		 */
		अगर (test_bit(SSH_PACKET_SF_LOCKED_BIT, &p->state))
			जारी;

		/*
		 * Packets should be ordered non-blocking/to-be-resent first.
		 * If we cannot process this packet, assume that we can't
		 * process any following packet either and पात.
		 */
		अगर (!ssh_ptl_tx_can_process(p)) अणु
			packet = ERR_PTR(-EBUSY);
			अवरोध;
		पूर्ण

		/*
		 * We are allowed to change the state now. Remove it from the
		 * queue and mark it as being transmitted.
		 */

		list_del(&p->queue_node);

		set_bit(SSH_PACKET_SF_TRANSMITTING_BIT, &p->state);
		/* Ensure that state never माला_लो zero. */
		smp_mb__beक्रमe_atomic();
		clear_bit(SSH_PACKET_SF_QUEUED_BIT, &p->state);

		/*
		 * Update number of tries. This directly influences the
		 * priority in हाल the packet is re-submitted (e.g. via
		 * समयout/NAK). Note that all पढ़ोs and ग_लिखोs to the
		 * priority after the first submission are guarded by the
		 * queue lock.
		 */
		ssh_packet_next_try(p);

		packet = p;
		अवरोध;
	पूर्ण
	spin_unlock(&ptl->queue.lock);

	वापस packet;
पूर्ण

अटल काष्ठा ssh_packet *ssh_ptl_tx_next(काष्ठा ssh_ptl *ptl)
अणु
	काष्ठा ssh_packet *p;

	p = ssh_ptl_tx_pop(ptl);
	अगर (IS_ERR(p))
		वापस p;

	अगर (test_bit(SSH_PACKET_TY_SEQUENCED_BIT, &p->state)) अणु
		ptl_dbg(ptl, "ptl: transmitting sequenced packet %p\n", p);
		ssh_ptl_pending_push(p);
	पूर्ण अन्यथा अणु
		ptl_dbg(ptl, "ptl: transmitting non-sequenced packet %p\n", p);
	पूर्ण

	वापस p;
पूर्ण

अटल व्योम ssh_ptl_tx_compl_success(काष्ठा ssh_packet *packet)
अणु
	काष्ठा ssh_ptl *ptl = packet->ptl;

	ptl_dbg(ptl, "ptl: successfully transmitted packet %p\n", packet);

	/* Transition state to "transmitted". */
	set_bit(SSH_PACKET_SF_TRANSMITTED_BIT, &packet->state);
	/* Ensure that state never माला_लो zero. */
	smp_mb__beक्रमe_atomic();
	clear_bit(SSH_PACKET_SF_TRANSMITTING_BIT, &packet->state);

	/* If the packet is unsequenced, we're करोne: Lock and complete. */
	अगर (!test_bit(SSH_PACKET_TY_SEQUENCED_BIT, &packet->state)) अणु
		set_bit(SSH_PACKET_SF_LOCKED_BIT, &packet->state);
		ssh_ptl_हटाओ_and_complete(packet, 0);
	पूर्ण

	/*
	 * Notअगरy that a packet transmission has finished. In general we're only
	 * रुकोing क्रम one packet (अगर any), so wake_up_all should be fine.
	 */
	wake_up_all(&ptl->tx.packet_wq);
पूर्ण

अटल व्योम ssh_ptl_tx_compl_error(काष्ठा ssh_packet *packet, पूर्णांक status)
अणु
	/* Transmission failure: Lock the packet and try to complete it. */
	set_bit(SSH_PACKET_SF_LOCKED_BIT, &packet->state);
	/* Ensure that state never माला_लो zero. */
	smp_mb__beक्रमe_atomic();
	clear_bit(SSH_PACKET_SF_TRANSMITTING_BIT, &packet->state);

	ptl_err(packet->ptl, "ptl: transmission error: %d\n", status);
	ptl_dbg(packet->ptl, "ptl: failed to transmit packet: %p\n", packet);

	ssh_ptl_हटाओ_and_complete(packet, status);

	/*
	 * Notअगरy that a packet transmission has finished. In general we're only
	 * रुकोing क्रम one packet (अगर any), so wake_up_all should be fine.
	 */
	wake_up_all(&packet->ptl->tx.packet_wq);
पूर्ण

अटल दीर्घ ssh_ptl_tx_रुको_packet(काष्ठा ssh_ptl *ptl)
अणु
	पूर्णांक status;

	status = रुको_क्रम_completion_पूर्णांकerruptible(&ptl->tx.thपढ़ो_cplt_pkt);
	reinit_completion(&ptl->tx.thपढ़ो_cplt_pkt);

	/*
	 * Ensure completion is cleared beक्रमe continuing to aव्योम lost update
	 * problems.
	 */
	smp_mb__after_atomic();

	वापस status;
पूर्ण

अटल दीर्घ ssh_ptl_tx_रुको_transfer(काष्ठा ssh_ptl *ptl, दीर्घ समयout)
अणु
	दीर्घ status;

	status = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ptl->tx.thपढ़ो_cplt_tx,
							   समयout);
	reinit_completion(&ptl->tx.thपढ़ो_cplt_tx);

	/*
	 * Ensure completion is cleared beक्रमe continuing to aव्योम lost update
	 * problems.
	 */
	smp_mb__after_atomic();

	वापस status;
पूर्ण

अटल पूर्णांक ssh_ptl_tx_packet(काष्ठा ssh_ptl *ptl, काष्ठा ssh_packet *packet)
अणु
	दीर्घ समयout = SSH_PTL_TX_TIMEOUT;
	माप_प्रकार offset = 0;

	/* Note: Flush-packets करोn't have any data. */
	अगर (unlikely(!packet->data.ptr))
		वापस 0;

	/* Error injection: drop packet to simulate transmission problem. */
	अगर (ssh_ptl_should_drop_packet(packet))
		वापस 0;

	/* Error injection: simulate invalid packet data. */
	ssh_ptl_tx_inject_invalid_data(packet);

	ptl_dbg(ptl, "tx: sending data (length: %zu)\n", packet->data.len);
	prपूर्णांक_hex_dump_debug("tx: ", DUMP_PREFIX_OFFSET, 16, 1,
			     packet->data.ptr, packet->data.len, false);

	करो अणु
		sमाप_प्रकार status, len;
		u8 *buf;

		buf = packet->data.ptr + offset;
		len = packet->data.len - offset;

		status = ssh_ptl_ग_लिखो_buf(ptl, packet, buf, len);
		अगर (status < 0)
			वापस status;

		अगर (status == len)
			वापस 0;

		offset += status;

		समयout = ssh_ptl_tx_रुको_transfer(ptl, समयout);
		अगर (kthपढ़ो_should_stop() || !atomic_पढ़ो(&ptl->tx.running))
			वापस -ESHUTDOWN;

		अगर (समयout < 0)
			वापस -EINTR;

		अगर (समयout == 0)
			वापस -ETIMEDOUT;
	पूर्ण जबतक (true);
पूर्ण

अटल पूर्णांक ssh_ptl_tx_thपढ़ोfn(व्योम *data)
अणु
	काष्ठा ssh_ptl *ptl = data;

	जबतक (!kthपढ़ो_should_stop() && atomic_पढ़ो(&ptl->tx.running)) अणु
		काष्ठा ssh_packet *packet;
		पूर्णांक status;

		/* Try to get the next packet. */
		packet = ssh_ptl_tx_next(ptl);

		/* If no packet can be processed, we are करोne. */
		अगर (IS_ERR(packet)) अणु
			ssh_ptl_tx_रुको_packet(ptl);
			जारी;
		पूर्ण

		/* Transfer and complete packet. */
		status = ssh_ptl_tx_packet(ptl, packet);
		अगर (status)
			ssh_ptl_tx_compl_error(packet, status);
		अन्यथा
			ssh_ptl_tx_compl_success(packet);

		ssh_packet_put(packet);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ssh_ptl_tx_wakeup_packet() - Wake up packet transmitter thपढ़ो क्रम new
 * packet.
 * @ptl: The packet transport layer.
 *
 * Wakes up the packet transmitter thपढ़ो, notअगरying it that a new packet has
 * arrived and is पढ़ोy क्रम transfer. If the packet transport layer has been
 * shut करोwn, calls to this function will be ignored.
 */
अटल व्योम ssh_ptl_tx_wakeup_packet(काष्ठा ssh_ptl *ptl)
अणु
	अगर (test_bit(SSH_PTL_SF_SHUTDOWN_BIT, &ptl->state))
		वापस;

	complete(&ptl->tx.thपढ़ो_cplt_pkt);
पूर्ण

/**
 * ssh_ptl_tx_start() - Start packet transmitter thपढ़ो.
 * @ptl: The packet transport layer.
 *
 * Return: Returns zero on success, a negative error code on failure.
 */
पूर्णांक ssh_ptl_tx_start(काष्ठा ssh_ptl *ptl)
अणु
	atomic_set_release(&ptl->tx.running, 1);

	ptl->tx.thपढ़ो = kthपढ़ो_run(ssh_ptl_tx_thपढ़ोfn, ptl, "ssam_serial_hub-tx");
	अगर (IS_ERR(ptl->tx.thपढ़ो))
		वापस PTR_ERR(ptl->tx.thपढ़ो);

	वापस 0;
पूर्ण

/**
 * ssh_ptl_tx_stop() - Stop packet transmitter thपढ़ो.
 * @ptl: The packet transport layer.
 *
 * Return: Returns zero on success, a negative error code on failure.
 */
पूर्णांक ssh_ptl_tx_stop(काष्ठा ssh_ptl *ptl)
अणु
	पूर्णांक status = 0;

	अगर (!IS_ERR_OR_शून्य(ptl->tx.thपढ़ो)) अणु
		/* Tell thपढ़ो to stop. */
		atomic_set_release(&ptl->tx.running, 0);

		/*
		 * Wake up thपढ़ो in हाल it is छोड़ोd. Do not use wakeup
		 * helpers as this may be called when the shutकरोwn bit has
		 * alपढ़ोy been set.
		 */
		complete(&ptl->tx.thपढ़ो_cplt_pkt);
		complete(&ptl->tx.thपढ़ो_cplt_tx);

		/* Finally, रुको क्रम thपढ़ो to stop. */
		status = kthपढ़ो_stop(ptl->tx.thपढ़ो);
		ptl->tx.thपढ़ो = शून्य;
	पूर्ण

	वापस status;
पूर्ण

अटल काष्ठा ssh_packet *ssh_ptl_ack_pop(काष्ठा ssh_ptl *ptl, u8 seq_id)
अणु
	काष्ठा ssh_packet *packet = ERR_PTR(-ENOENT);
	काष्ठा ssh_packet *p, *n;

	spin_lock(&ptl->pending.lock);
	list_क्रम_each_entry_safe(p, n, &ptl->pending.head, pending_node) अणु
		/*
		 * We generally expect packets to be in order, so first packet
		 * to be added to pending is first to be sent, is first to be
		 * ACKed.
		 */
		अगर (unlikely(ssh_packet_get_seq(p) != seq_id))
			जारी;

		/*
		 * In हाल we receive an ACK जबतक handling a transmission
		 * error completion. The packet will be हटाओd लघुly.
		 */
		अगर (unlikely(test_bit(SSH_PACKET_SF_LOCKED_BIT, &p->state))) अणु
			packet = ERR_PTR(-EPERM);
			अवरोध;
		पूर्ण

		/*
		 * Mark the packet as ACKed and हटाओ it from pending by
		 * removing its node and decrementing the pending counter.
		 */
		set_bit(SSH_PACKET_SF_ACKED_BIT, &p->state);
		/* Ensure that state never माला_लो zero. */
		smp_mb__beक्रमe_atomic();
		clear_bit(SSH_PACKET_SF_PENDING_BIT, &p->state);

		atomic_dec(&ptl->pending.count);
		list_del(&p->pending_node);
		packet = p;

		अवरोध;
	पूर्ण
	spin_unlock(&ptl->pending.lock);

	वापस packet;
पूर्ण

अटल व्योम ssh_ptl_रुको_until_transmitted(काष्ठा ssh_packet *packet)
अणु
	रुको_event(packet->ptl->tx.packet_wq,
		   test_bit(SSH_PACKET_SF_TRANSMITTED_BIT, &packet->state) ||
		   test_bit(SSH_PACKET_SF_LOCKED_BIT, &packet->state));
पूर्ण

अटल व्योम ssh_ptl_acknowledge(काष्ठा ssh_ptl *ptl, u8 seq)
अणु
	काष्ठा ssh_packet *p;

	p = ssh_ptl_ack_pop(ptl, seq);
	अगर (IS_ERR(p)) अणु
		अगर (PTR_ERR(p) == -ENOENT) अणु
			/*
			 * The packet has not been found in the set of pending
			 * packets.
			 */
			ptl_warn(ptl, "ptl: received ACK for non-pending packet\n");
		पूर्ण अन्यथा अणु
			/*
			 * The packet is pending, but we are not allowed to take
			 * it because it has been locked.
			 */
			WARN_ON(PTR_ERR(p) != -EPERM);
		पूर्ण
		वापस;
	पूर्ण

	ptl_dbg(ptl, "ptl: received ACK for packet %p\n", p);

	/*
	 * It is possible that the packet has been transmitted, but the state
	 * has not been updated from "transmitting" to "transmitted" yet.
	 * In that हाल, we need to रुको क्रम this transition to occur in order
	 * to determine between success or failure.
	 *
	 * On transmission failure, the packet will be locked after this call.
	 * On success, the transmitted bit will be set.
	 */
	ssh_ptl_रुको_until_transmitted(p);

	/*
	 * The packet will alपढ़ोy be locked in हाल of a transmission error or
	 * cancellation. Let the transmitter or cancellation issuer complete the
	 * packet.
	 */
	अगर (unlikely(test_and_set_bit(SSH_PACKET_SF_LOCKED_BIT, &p->state))) अणु
		अगर (unlikely(!test_bit(SSH_PACKET_SF_TRANSMITTED_BIT, &p->state)))
			ptl_err(ptl, "ptl: received ACK before packet had been fully transmitted\n");

		ssh_packet_put(p);
		वापस;
	पूर्ण

	ssh_ptl_हटाओ_and_complete(p, 0);
	ssh_packet_put(p);

	अगर (atomic_पढ़ो(&ptl->pending.count) < SSH_PTL_MAX_PENDING)
		ssh_ptl_tx_wakeup_packet(ptl);
पूर्ण

/**
 * ssh_ptl_submit() - Submit a packet to the transport layer.
 * @ptl: The packet transport layer to submit the packet to.
 * @p:   The packet to submit.
 *
 * Submits a new packet to the transport layer, queuing it to be sent. This
 * function should not be used क्रम re-submission.
 *
 * Return: Returns zero on success, %-EINVAL अगर a packet field is invalid or
 * the packet has been canceled prior to submission, %-EALREADY अगर the packet
 * has alपढ़ोy been submitted, or %-ESHUTDOWN अगर the packet transport layer
 * has been shut करोwn.
 */
पूर्णांक ssh_ptl_submit(काष्ठा ssh_ptl *ptl, काष्ठा ssh_packet *p)
अणु
	काष्ठा ssh_ptl *ptl_old;
	पूर्णांक status;

	trace_ssam_packet_submit(p);

	/* Validate packet fields. */
	अगर (test_bit(SSH_PACKET_TY_FLUSH_BIT, &p->state)) अणु
		अगर (p->data.ptr || test_bit(SSH_PACKET_TY_SEQUENCED_BIT, &p->state))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (!p->data.ptr) अणु
		वापस -EINVAL;
	पूर्ण

	/*
	 * The ptl reference only माला_लो set on or beक्रमe the first submission.
	 * After the first submission, it has to be पढ़ो-only.
	 *
	 * Note that ptl may alपढ़ोy be set from upper-layer request
	 * submission, thus we cannot expect it to be शून्य.
	 */
	ptl_old = READ_ONCE(p->ptl);
	अगर (!ptl_old)
		WRITE_ONCE(p->ptl, ptl);
	अन्यथा अगर (WARN_ON(ptl_old != ptl))
		वापस -EALREADY;	/* Submitted on dअगरferent PTL. */

	status = ssh_ptl_queue_push(p);
	अगर (status)
		वापस status;

	अगर (!test_bit(SSH_PACKET_TY_BLOCKING_BIT, &p->state) ||
	    (atomic_पढ़ो(&ptl->pending.count) < SSH_PTL_MAX_PENDING))
		ssh_ptl_tx_wakeup_packet(ptl);

	वापस 0;
पूर्ण

/*
 * __ssh_ptl_resubmit() - Re-submit a packet to the transport layer.
 * @packet: The packet to re-submit.
 *
 * Re-submits the given packet: Checks अगर it can be re-submitted and queues it
 * अगर it can, resetting the packet बारtamp in the process. Must be called
 * with the pending lock held.
 *
 * Return: Returns %-ECANCELED अगर the packet has exceeded its number of tries,
 * %-EINVAL अगर the packet has been locked, %-EALREADY अगर the packet is alपढ़ोy
 * on the queue, and %-ESHUTDOWN अगर the transmission layer has been shut करोwn.
 */
अटल पूर्णांक __ssh_ptl_resubmit(काष्ठा ssh_packet *packet)
अणु
	पूर्णांक status;
	u8 try;

	lockdep_निश्चित_held(&packet->ptl->pending.lock);

	trace_ssam_packet_resubmit(packet);

	spin_lock(&packet->ptl->queue.lock);

	/* Check अगर the packet is out of tries. */
	try = ssh_packet_priority_get_try(packet->priority);
	अगर (try >= SSH_PTL_MAX_PACKET_TRIES) अणु
		spin_unlock(&packet->ptl->queue.lock);
		वापस -ECANCELED;
	पूर्ण

	status = __ssh_ptl_queue_push(packet);
	अगर (status) अणु
		/*
		 * An error here indicates that the packet has either alपढ़ोy
		 * been queued, been locked, or the transport layer is being
		 * shut करोwn. In all हालs: Ignore the error.
		 */
		spin_unlock(&packet->ptl->queue.lock);
		वापस status;
	पूर्ण

	packet->बारtamp = KTIME_MAX;

	spin_unlock(&packet->ptl->queue.lock);
	वापस 0;
पूर्ण

अटल व्योम ssh_ptl_resubmit_pending(काष्ठा ssh_ptl *ptl)
अणु
	काष्ठा ssh_packet *p;
	bool resub = false;

	/*
	 * Note: We deliberately करो not हटाओ/attempt to cancel and complete
	 * packets that are out of tires in this function. The packet will be
	 * eventually canceled and completed by the समयout. Removing the packet
	 * here could lead to overly eager cancellation अगर the packet has not
	 * been re-transmitted yet but the tries-counter alपढ़ोy updated (i.e
	 * ssh_ptl_tx_next() हटाओd the packet from the queue and updated the
	 * counter, but re-transmission क्रम the last try has not actually
	 * started yet).
	 */

	spin_lock(&ptl->pending.lock);

	/* Re-queue all pending packets. */
	list_क्रम_each_entry(p, &ptl->pending.head, pending_node) अणु
		/*
		 * Re-submission fails अगर the packet is out of tries, has been
		 * locked, is alपढ़ोy queued, or the layer is being shut करोwn.
		 * No need to re-schedule tx-thपढ़ो in those हालs.
		 */
		अगर (!__ssh_ptl_resubmit(p))
			resub = true;
	पूर्ण

	spin_unlock(&ptl->pending.lock);

	अगर (resub)
		ssh_ptl_tx_wakeup_packet(ptl);
पूर्ण

/**
 * ssh_ptl_cancel() - Cancel a packet.
 * @p: The packet to cancel.
 *
 * Cancels a packet. There are no guarantees on when completion and release
 * callbacks will be called. This may occur during execution of this function
 * or may occur at any poपूर्णांक later.
 *
 * Note that it is not guaranteed that the packet will actually be canceled अगर
 * the packet is concurrently completed by another process. The only guarantee
 * of this function is that the packet will be completed (with success,
 * failure, or cancellation) and released from the transport layer in a
 * reasonable समय-frame.
 *
 * May be called beक्रमe the packet has been submitted, in which हाल any later
 * packet submission fails.
 */
व्योम ssh_ptl_cancel(काष्ठा ssh_packet *p)
अणु
	अगर (test_and_set_bit(SSH_PACKET_SF_CANCELED_BIT, &p->state))
		वापस;

	trace_ssam_packet_cancel(p);

	/*
	 * Lock packet and commit with memory barrier. If this packet has
	 * alपढ़ोy been locked, it's going to be हटाओd and completed by
	 * another party, which should have precedence.
	 */
	अगर (test_and_set_bit(SSH_PACKET_SF_LOCKED_BIT, &p->state))
		वापस;

	/*
	 * By marking the packet as locked and employing the implicit memory
	 * barrier of test_and_set_bit, we have guaranteed that, at this poपूर्णांक,
	 * the packet cannot be added to the queue any more.
	 *
	 * In हाल the packet has never been submitted, packet->ptl is शून्य. If
	 * the packet is currently being submitted, packet->ptl may be शून्य or
	 * non-शून्य. Due marking the packet as locked above and committing with
	 * the memory barrier, we have guaranteed that, अगर packet->ptl is शून्य,
	 * the packet will never be added to the queue. If packet->ptl is
	 * non-शून्य, we करोn't have any guarantees.
	 */

	अगर (READ_ONCE(p->ptl)) अणु
		ssh_ptl_हटाओ_and_complete(p, -ECANCELED);

		अगर (atomic_पढ़ो(&p->ptl->pending.count) < SSH_PTL_MAX_PENDING)
			ssh_ptl_tx_wakeup_packet(p->ptl);

	पूर्ण अन्यथा अगर (!test_and_set_bit(SSH_PACKET_SF_COMPLETED_BIT, &p->state)) अणु
		__ssh_ptl_complete(p, -ECANCELED);
	पूर्ण
पूर्ण

/* Must be called with pending lock held */
अटल kसमय_प्रकार ssh_packet_get_expiration(काष्ठा ssh_packet *p, kसमय_प्रकार समयout)
अणु
	lockdep_निश्चित_held(&p->ptl->pending.lock);

	अगर (p->बारtamp != KTIME_MAX)
		वापस kसमय_add(p->बारtamp, समयout);
	अन्यथा
		वापस KTIME_MAX;
पूर्ण

अटल व्योम ssh_ptl_समयout_reap(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ssh_ptl *ptl = to_ssh_ptl(work, rtx_समयout.reaper.work);
	काष्ठा ssh_packet *p, *n;
	LIST_HEAD(claimed);
	kसमय_प्रकार now = kसमय_get_coarse_bootसमय();
	kसमय_प्रकार समयout = ptl->rtx_समयout.समयout;
	kसमय_प्रकार next = KTIME_MAX;
	bool resub = false;
	पूर्णांक status;

	trace_ssam_ptl_समयout_reap(atomic_पढ़ो(&ptl->pending.count));

	/*
	 * Mark reaper as "not pending". This is करोne beक्रमe checking any
	 * packets to aव्योम lost-update type problems.
	 */
	spin_lock(&ptl->rtx_समयout.lock);
	ptl->rtx_समयout.expires = KTIME_MAX;
	spin_unlock(&ptl->rtx_समयout.lock);

	spin_lock(&ptl->pending.lock);

	list_क्रम_each_entry_safe(p, n, &ptl->pending.head, pending_node) अणु
		kसमय_प्रकार expires = ssh_packet_get_expiration(p, समयout);

		/*
		 * Check अगर the समयout hasn't expired yet. Find out next
		 * expiration date to be handled after this run.
		 */
		अगर (kसमय_after(expires, now)) अणु
			next = kसमय_beक्रमe(expires, next) ? expires : next;
			जारी;
		पूर्ण

		trace_ssam_packet_समयout(p);

		status = __ssh_ptl_resubmit(p);

		/*
		 * Re-submission fails अगर the packet is out of tries, has been
		 * locked, is alपढ़ोy queued, or the layer is being shut करोwn.
		 * No need to re-schedule tx-thपढ़ो in those हालs.
		 */
		अगर (!status)
			resub = true;

		/* Go to next packet अगर this packet is not out of tries. */
		अगर (status != -ECANCELED)
			जारी;

		/* No more tries left: Cancel the packet. */

		/*
		 * If someone अन्यथा has locked the packet alपढ़ोy, करोn't use it
		 * and let the other party complete it.
		 */
		अगर (test_and_set_bit(SSH_PACKET_SF_LOCKED_BIT, &p->state))
			जारी;

		/*
		 * We have now marked the packet as locked. Thus it cannot be
		 * added to the pending list again after we've हटाओd it here.
		 * We can thereक्रमe re-use the pending_node of this packet
		 * temporarily.
		 */

		clear_bit(SSH_PACKET_SF_PENDING_BIT, &p->state);

		atomic_dec(&ptl->pending.count);
		list_del(&p->pending_node);

		list_add_tail(&p->pending_node, &claimed);
	पूर्ण

	spin_unlock(&ptl->pending.lock);

	/* Cancel and complete the packet. */
	list_क्रम_each_entry_safe(p, n, &claimed, pending_node) अणु
		अगर (!test_and_set_bit(SSH_PACKET_SF_COMPLETED_BIT, &p->state)) अणु
			ssh_ptl_queue_हटाओ(p);
			__ssh_ptl_complete(p, -ETIMEDOUT);
		पूर्ण

		/*
		 * Drop the reference we've obtained by removing it from
		 * the pending set.
		 */
		list_del(&p->pending_node);
		ssh_packet_put(p);
	पूर्ण

	/* Ensure that reaper करोesn't run again immediately. */
	next = max(next, kसमय_add(now, SSH_PTL_PACKET_TIMEOUT_RESOLUTION));
	अगर (next != KTIME_MAX)
		ssh_ptl_समयout_reaper_mod(ptl, now, next);

	अगर (resub)
		ssh_ptl_tx_wakeup_packet(ptl);
पूर्ण

अटल bool ssh_ptl_rx_retransmit_check(काष्ठा ssh_ptl *ptl, u8 seq)
अणु
	पूर्णांक i;

	/*
	 * Check अगर SEQ has been seen recently (i.e. packet was
	 * re-transmitted and we should ignore it).
	 */
	क्रम (i = 0; i < ARRAY_SIZE(ptl->rx.blocked.seqs); i++) अणु
		अगर (likely(ptl->rx.blocked.seqs[i] != seq))
			जारी;

		ptl_dbg(ptl, "ptl: ignoring repeated data packet\n");
		वापस true;
	पूर्ण

	/* Update list of blocked sequence IDs. */
	ptl->rx.blocked.seqs[ptl->rx.blocked.offset] = seq;
	ptl->rx.blocked.offset = (ptl->rx.blocked.offset + 1)
				  % ARRAY_SIZE(ptl->rx.blocked.seqs);

	वापस false;
पूर्ण

अटल व्योम ssh_ptl_rx_dataframe(काष्ठा ssh_ptl *ptl,
				 स्थिर काष्ठा ssh_frame *frame,
				 स्थिर काष्ठा ssam_span *payload)
अणु
	अगर (ssh_ptl_rx_retransmit_check(ptl, frame->seq))
		वापस;

	ptl->ops.data_received(ptl, payload);
पूर्ण

अटल व्योम ssh_ptl_send_ack(काष्ठा ssh_ptl *ptl, u8 seq)
अणु
	काष्ठा ssh_packet *packet;
	काष्ठा ssam_span buf;
	काष्ठा msgbuf msgb;
	पूर्णांक status;

	status = ssh_ctrl_packet_alloc(&packet, &buf, GFP_KERNEL);
	अगर (status) अणु
		ptl_err(ptl, "ptl: failed to allocate ACK packet\n");
		वापस;
	पूर्ण

	ssh_packet_init(packet, 0, SSH_PACKET_PRIORITY(ACK, 0),
			&ssh_ptl_ctrl_packet_ops);

	msgb_init(&msgb, buf.ptr, buf.len);
	msgb_push_ack(&msgb, seq);
	ssh_packet_set_data(packet, msgb.begin, msgb_bytes_used(&msgb));

	ssh_ptl_submit(ptl, packet);
	ssh_packet_put(packet);
पूर्ण

अटल व्योम ssh_ptl_send_nak(काष्ठा ssh_ptl *ptl)
अणु
	काष्ठा ssh_packet *packet;
	काष्ठा ssam_span buf;
	काष्ठा msgbuf msgb;
	पूर्णांक status;

	status = ssh_ctrl_packet_alloc(&packet, &buf, GFP_KERNEL);
	अगर (status) अणु
		ptl_err(ptl, "ptl: failed to allocate NAK packet\n");
		वापस;
	पूर्ण

	ssh_packet_init(packet, 0, SSH_PACKET_PRIORITY(NAK, 0),
			&ssh_ptl_ctrl_packet_ops);

	msgb_init(&msgb, buf.ptr, buf.len);
	msgb_push_nak(&msgb);
	ssh_packet_set_data(packet, msgb.begin, msgb_bytes_used(&msgb));

	ssh_ptl_submit(ptl, packet);
	ssh_packet_put(packet);
पूर्ण

अटल माप_प्रकार ssh_ptl_rx_eval(काष्ठा ssh_ptl *ptl, काष्ठा ssam_span *source)
अणु
	काष्ठा ssh_frame *frame;
	काष्ठा ssam_span payload;
	काष्ठा ssam_span aligned;
	bool syn_found;
	पूर्णांक status;

	/* Error injection: Modअगरy data to simulate corrupt SYN bytes. */
	ssh_ptl_rx_inject_invalid_syn(ptl, source);

	/* Find SYN. */
	syn_found = sshp_find_syn(source, &aligned);

	अगर (unlikely(aligned.ptr != source->ptr)) अणु
		/*
		 * We expect aligned.ptr == source->ptr. If this is not the
		 * हाल, then aligned.ptr > source->ptr and we've encountered
		 * some unexpected data where we'd expect the start of a new
		 * message (i.e. the SYN sequence).
		 *
		 * This can happen when a CRC check क्रम the previous message
		 * failed and we start actively searching क्रम the next one
		 * (via the call to sshp_find_syn() above), or the first bytes
		 * of a message got dropped or corrupted.
		 *
		 * In any हाल, we issue a warning, send a NAK to the EC to
		 * request re-transmission of any data we haven't acknowledged
		 * yet, and finally, skip everything up to the next SYN
		 * sequence.
		 */

		ptl_warn(ptl, "rx: parser: invalid start of frame, skipping\n");

		/*
		 * Notes:
		 * - This might send multiple NAKs in हाल the communication
		 *   starts with an invalid SYN and is broken करोwn पूर्णांकo multiple
		 *   pieces. This should generally be handled fine, we just
		 *   might receive duplicate data in this हाल, which is
		 *   detected when handling data frames.
		 * - This path will also be executed on invalid CRCs: When an
		 *   invalid CRC is encountered, the code below will skip data
		 *   until directly after the SYN. This causes the search क्रम
		 *   the next SYN, which is generally not placed directly after
		 *   the last one.
		 *
		 *   Open question: Should we send this in हाल of invalid
		 *   payload CRCs अगर the frame-type is non-sequential (current
		 *   implementation) or should we drop that frame without
		 *   telling the EC?
		 */
		ssh_ptl_send_nak(ptl);
	पूर्ण

	अगर (unlikely(!syn_found))
		वापस aligned.ptr - source->ptr;

	/* Error injection: Modअगरy data to simulate corruption. */
	ssh_ptl_rx_inject_invalid_data(ptl, &aligned);

	/* Parse and validate frame. */
	status = sshp_parse_frame(&ptl->serdev->dev, &aligned, &frame, &payload,
				  SSH_PTL_RX_BUF_LEN);
	अगर (status)	/* Invalid frame: skip to next SYN. */
		वापस aligned.ptr - source->ptr + माप(u16);
	अगर (!frame)	/* Not enough data. */
		वापस aligned.ptr - source->ptr;

	trace_ssam_rx_frame_received(frame);

	चयन (frame->type) अणु
	हाल SSH_FRAME_TYPE_ACK:
		ssh_ptl_acknowledge(ptl, frame->seq);
		अवरोध;

	हाल SSH_FRAME_TYPE_NAK:
		ssh_ptl_resubmit_pending(ptl);
		अवरोध;

	हाल SSH_FRAME_TYPE_DATA_SEQ:
		ssh_ptl_send_ack(ptl, frame->seq);
		fallthrough;

	हाल SSH_FRAME_TYPE_DATA_NSQ:
		ssh_ptl_rx_dataframe(ptl, frame, &payload);
		अवरोध;

	शेष:
		ptl_warn(ptl, "ptl: received frame with unknown type %#04x\n",
			 frame->type);
		अवरोध;
	पूर्ण

	वापस aligned.ptr - source->ptr + SSH_MESSAGE_LENGTH(payload.len);
पूर्ण

अटल पूर्णांक ssh_ptl_rx_thपढ़ोfn(व्योम *data)
अणु
	काष्ठा ssh_ptl *ptl = data;

	जबतक (true) अणु
		काष्ठा ssam_span span;
		माप_प्रकार offs = 0;
		माप_प्रकार n;

		रुको_event_पूर्णांकerruptible(ptl->rx.wq,
					 !kfअगरo_is_empty(&ptl->rx.fअगरo) ||
					 kthपढ़ो_should_stop());
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		/* Copy from fअगरo to evaluation buffer. */
		n = sshp_buf_पढ़ो_from_fअगरo(&ptl->rx.buf, &ptl->rx.fअगरo);

		ptl_dbg(ptl, "rx: received data (size: %zu)\n", n);
		prपूर्णांक_hex_dump_debug("rx: ", DUMP_PREFIX_OFFSET, 16, 1,
				     ptl->rx.buf.ptr + ptl->rx.buf.len - n,
				     n, false);

		/* Parse until we need more bytes or buffer is empty. */
		जबतक (offs < ptl->rx.buf.len) अणु
			sshp_buf_span_from(&ptl->rx.buf, offs, &span);
			n = ssh_ptl_rx_eval(ptl, &span);
			अगर (n == 0)
				अवरोध;	/* Need more bytes. */

			offs += n;
		पूर्ण

		/* Throw away the evaluated parts. */
		sshp_buf_drop(&ptl->rx.buf, offs);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ssh_ptl_rx_wakeup(काष्ठा ssh_ptl *ptl)
अणु
	wake_up(&ptl->rx.wq);
पूर्ण

/**
 * ssh_ptl_rx_start() - Start packet transport layer receiver thपढ़ो.
 * @ptl: The packet transport layer.
 *
 * Return: Returns zero on success, a negative error code on failure.
 */
पूर्णांक ssh_ptl_rx_start(काष्ठा ssh_ptl *ptl)
अणु
	अगर (ptl->rx.thपढ़ो)
		वापस 0;

	ptl->rx.thपढ़ो = kthपढ़ो_run(ssh_ptl_rx_thपढ़ोfn, ptl,
				     "ssam_serial_hub-rx");
	अगर (IS_ERR(ptl->rx.thपढ़ो))
		वापस PTR_ERR(ptl->rx.thपढ़ो);

	वापस 0;
पूर्ण

/**
 * ssh_ptl_rx_stop() - Stop packet transport layer receiver thपढ़ो.
 * @ptl: The packet transport layer.
 *
 * Return: Returns zero on success, a negative error code on failure.
 */
पूर्णांक ssh_ptl_rx_stop(काष्ठा ssh_ptl *ptl)
अणु
	पूर्णांक status = 0;

	अगर (ptl->rx.thपढ़ो) अणु
		status = kthपढ़ो_stop(ptl->rx.thपढ़ो);
		ptl->rx.thपढ़ो = शून्य;
	पूर्ण

	वापस status;
पूर्ण

/**
 * ssh_ptl_rx_rcvbuf() - Push data from lower-layer transport to the packet
 * layer.
 * @ptl: The packet transport layer.
 * @buf: Poपूर्णांकer to the data to push to the layer.
 * @n:   Size of the data to push to the layer, in bytes.
 *
 * Pushes data from a lower-layer transport to the receiver fअगरo buffer of the
 * packet layer and notअगरies the receiver thपढ़ो. Calls to this function are
 * ignored once the packet layer has been shut करोwn.
 *
 * Return: Returns the number of bytes transferred (positive or zero) on
 * success. Returns %-ESHUTDOWN अगर the packet layer has been shut करोwn.
 */
पूर्णांक ssh_ptl_rx_rcvbuf(काष्ठा ssh_ptl *ptl, स्थिर u8 *buf, माप_प्रकार n)
अणु
	पूर्णांक used;

	अगर (test_bit(SSH_PTL_SF_SHUTDOWN_BIT, &ptl->state))
		वापस -ESHUTDOWN;

	used = kfअगरo_in(&ptl->rx.fअगरo, buf, n);
	अगर (used)
		ssh_ptl_rx_wakeup(ptl);

	वापस used;
पूर्ण

/**
 * ssh_ptl_shutकरोwn() - Shut करोwn the packet transport layer.
 * @ptl: The packet transport layer.
 *
 * Shuts करोwn the packet transport layer, removing and canceling all queued
 * and pending packets. Packets canceled by this operation will be completed
 * with %-ESHUTDOWN as status. Receiver and transmitter thपढ़ोs will be
 * stopped.
 *
 * As a result of this function, the transport layer will be marked as shut
 * करोwn. Submission of packets after the transport layer has been shut करोwn
 * will fail with %-ESHUTDOWN.
 */
व्योम ssh_ptl_shutकरोwn(काष्ठा ssh_ptl *ptl)
अणु
	LIST_HEAD(complete_q);
	LIST_HEAD(complete_p);
	काष्ठा ssh_packet *p, *n;
	पूर्णांक status;

	/* Ensure that no new packets (including ACK/NAK) can be submitted. */
	set_bit(SSH_PTL_SF_SHUTDOWN_BIT, &ptl->state);
	/*
	 * Ensure that the layer माला_लो marked as shut-करोwn beक्रमe actually
	 * stopping it. In combination with the check in ssh_ptl_queue_push(),
	 * this guarantees that no new packets can be added and all alपढ़ोy
	 * queued packets are properly canceled. In combination with the check
	 * in ssh_ptl_rx_rcvbuf(), this guarantees that received data is
	 * properly cut off.
	 */
	smp_mb__after_atomic();

	status = ssh_ptl_rx_stop(ptl);
	अगर (status)
		ptl_err(ptl, "ptl: failed to stop receiver thread\n");

	status = ssh_ptl_tx_stop(ptl);
	अगर (status)
		ptl_err(ptl, "ptl: failed to stop transmitter thread\n");

	cancel_delayed_work_sync(&ptl->rtx_समयout.reaper);

	/*
	 * At this poपूर्णांक, all thपढ़ोs have been stopped. This means that the
	 * only references to packets from inside the प्रणाली are in the queue
	 * and pending set.
	 *
	 * Note: We still need locks here because someone could still be
	 * canceling packets.
	 *
	 * Note 2: We can re-use queue_node (or pending_node) अगर we mark the
	 * packet as locked an then हटाओ it from the queue (or pending set
	 * respectively). Marking the packet as locked aव्योमs re-queuing
	 * (which should alपढ़ोy be prevented by having stopped the tपढ़ोs...)
	 * and not setting QUEUED_BIT (or PENDING_BIT) prevents removal from a
	 * new list via other thपढ़ोs (e.g. cancellation).
	 *
	 * Note 3: There may be overlap between complete_p and complete_q.
	 * This is handled via test_and_set_bit() on the "completed" flag
	 * (also handles cancellation).
	 */

	/* Mark queued packets as locked and move them to complete_q. */
	spin_lock(&ptl->queue.lock);
	list_क्रम_each_entry_safe(p, n, &ptl->queue.head, queue_node) अणु
		set_bit(SSH_PACKET_SF_LOCKED_BIT, &p->state);
		/* Ensure that state करोes not get zero. */
		smp_mb__beक्रमe_atomic();
		clear_bit(SSH_PACKET_SF_QUEUED_BIT, &p->state);

		list_del(&p->queue_node);
		list_add_tail(&p->queue_node, &complete_q);
	पूर्ण
	spin_unlock(&ptl->queue.lock);

	/* Mark pending packets as locked and move them to complete_p. */
	spin_lock(&ptl->pending.lock);
	list_क्रम_each_entry_safe(p, n, &ptl->pending.head, pending_node) अणु
		set_bit(SSH_PACKET_SF_LOCKED_BIT, &p->state);
		/* Ensure that state करोes not get zero. */
		smp_mb__beक्रमe_atomic();
		clear_bit(SSH_PACKET_SF_PENDING_BIT, &p->state);

		list_del(&p->pending_node);
		list_add_tail(&p->pending_node, &complete_q);
	पूर्ण
	atomic_set(&ptl->pending.count, 0);
	spin_unlock(&ptl->pending.lock);

	/* Complete and drop packets on complete_q. */
	list_क्रम_each_entry(p, &complete_q, queue_node) अणु
		अगर (!test_and_set_bit(SSH_PACKET_SF_COMPLETED_BIT, &p->state))
			__ssh_ptl_complete(p, -ESHUTDOWN);

		ssh_packet_put(p);
	पूर्ण

	/* Complete and drop packets on complete_p. */
	list_क्रम_each_entry(p, &complete_p, pending_node) अणु
		अगर (!test_and_set_bit(SSH_PACKET_SF_COMPLETED_BIT, &p->state))
			__ssh_ptl_complete(p, -ESHUTDOWN);

		ssh_packet_put(p);
	पूर्ण

	/*
	 * At this poपूर्णांक we have guaranteed that the प्रणाली करोesn't reference
	 * any packets any more.
	 */
पूर्ण

/**
 * ssh_ptl_init() - Initialize packet transport layer.
 * @ptl:    The packet transport layer to initialize.
 * @serdev: The underlying serial device, i.e. the lower-level transport.
 * @ops:    Packet layer operations.
 *
 * Initializes the given packet transport layer. Transmitter and receiver
 * thपढ़ोs must be started separately via ssh_ptl_tx_start() and
 * ssh_ptl_rx_start(), after the packet-layer has been initialized and the
 * lower-level transport layer has been set up.
 *
 * Return: Returns zero on success and a nonzero error code on failure.
 */
पूर्णांक ssh_ptl_init(काष्ठा ssh_ptl *ptl, काष्ठा serdev_device *serdev,
		 काष्ठा ssh_ptl_ops *ops)
अणु
	पूर्णांक i, status;

	ptl->serdev = serdev;
	ptl->state = 0;

	spin_lock_init(&ptl->queue.lock);
	INIT_LIST_HEAD(&ptl->queue.head);

	spin_lock_init(&ptl->pending.lock);
	INIT_LIST_HEAD(&ptl->pending.head);
	atomic_set_release(&ptl->pending.count, 0);

	ptl->tx.thपढ़ो = शून्य;
	atomic_set(&ptl->tx.running, 0);
	init_completion(&ptl->tx.thपढ़ो_cplt_pkt);
	init_completion(&ptl->tx.thपढ़ो_cplt_tx);
	init_रुकोqueue_head(&ptl->tx.packet_wq);

	ptl->rx.thपढ़ो = शून्य;
	init_रुकोqueue_head(&ptl->rx.wq);

	spin_lock_init(&ptl->rtx_समयout.lock);
	ptl->rtx_समयout.समयout = SSH_PTL_PACKET_TIMEOUT;
	ptl->rtx_समयout.expires = KTIME_MAX;
	INIT_DELAYED_WORK(&ptl->rtx_समयout.reaper, ssh_ptl_समयout_reap);

	ptl->ops = *ops;

	/* Initialize list of recent/blocked SEQs with invalid sequence IDs. */
	क्रम (i = 0; i < ARRAY_SIZE(ptl->rx.blocked.seqs); i++)
		ptl->rx.blocked.seqs[i] = U16_MAX;
	ptl->rx.blocked.offset = 0;

	status = kfअगरo_alloc(&ptl->rx.fअगरo, SSH_PTL_RX_FIFO_LEN, GFP_KERNEL);
	अगर (status)
		वापस status;

	status = sshp_buf_alloc(&ptl->rx.buf, SSH_PTL_RX_BUF_LEN, GFP_KERNEL);
	अगर (status)
		kfअगरo_मुक्त(&ptl->rx.fअगरo);

	वापस status;
पूर्ण

/**
 * ssh_ptl_destroy() - Deinitialize packet transport layer.
 * @ptl: The packet transport layer to deinitialize.
 *
 * Deinitializes the given packet transport layer and मुक्तs resources
 * associated with it. If receiver and/or transmitter thपढ़ोs have been
 * started, the layer must first be shut करोwn via ssh_ptl_shutकरोwn() beक्रमe
 * this function can be called.
 */
व्योम ssh_ptl_destroy(काष्ठा ssh_ptl *ptl)
अणु
	kfअगरo_मुक्त(&ptl->rx.fअगरo);
	sshp_buf_मुक्त(&ptl->rx.buf);
पूर्ण
