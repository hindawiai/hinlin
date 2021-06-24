<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
   drbd_req.h

   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2006-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 2006-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.
   Copyright (C) 2006-2008, Philipp Reisner <philipp.reisner@linbit.com>.

 */

#अगर_अघोषित _DRBD_REQ_H
#घोषणा _DRBD_REQ_H

#समावेश <linux/module.h>

#समावेश <linux/slab.h>
#समावेश <linux/drbd.h>
#समावेश "drbd_int.h"

/* The request callbacks will be called in irq context by the IDE drivers,
   and in Softirqs/Tasklets/BH context by the SCSI drivers,
   and by the receiver and worker in kernel-thपढ़ो context.
   Try to get the locking right :) */

/*
 * Objects of type काष्ठा drbd_request करो only exist on a R_PRIMARY node, and are
 * associated with IO requests originating from the block layer above us.
 *
 * There are quite a few things that may happen to a drbd request
 * during its lअगरeसमय.
 *
 *  It will be created.
 *  It will be marked with the पूर्णांकention to be
 *    submitted to local disk and/or
 *    send via the network.
 *
 *  It has to be placed on the transfer log and other housekeeping lists,
 *  In हाल we have a network connection.
 *
 *  It may be identअगरied as a concurrent (ग_लिखो) request
 *    and be handled accordingly.
 *
 *  It may me handed over to the local disk subप्रणाली.
 *  It may be completed by the local disk subप्रणाली,
 *    either successfully or with io-error.
 *  In हाल it is a READ request, and it failed locally,
 *    it may be retried remotely.
 *
 *  It may be queued क्रम sending.
 *  It may be handed over to the network stack,
 *    which may fail.
 *  It may be acknowledged by the "peer" according to the wire_protocol in use.
 *    this may be a negative ack.
 *  It may receive a faked ack when the network connection is lost and the
 *  transfer log is cleaned up.
 *  Sending may be canceled due to network connection loss.
 *  When it finally has outlived its समय,
 *    corresponding dirty bits in the resync-biपंचांगap may be cleared or set,
 *    it will be destroyed,
 *    and completion will be संकेतled to the originator,
 *      with or without "success".
 */

क्रमागत drbd_req_event अणु
	CREATED,
	TO_BE_SENT,
	TO_BE_SUBMITTED,

	/* XXX yes, now I am inconsistent...
	 * these are not "events" but "actions"
	 * oh, well... */
	QUEUE_FOR_NET_WRITE,
	QUEUE_FOR_NET_READ,
	QUEUE_FOR_SEND_OOS,

	/* An empty flush is queued as P_BARRIER,
	 * which will cause it to complete "successfully",
	 * even अगर the local disk flush failed.
	 *
	 * Just like "real" requests, empty flushes (blkdev_issue_flush()) will
	 * only see an error अगर neither local nor remote data is reachable. */
	QUEUE_AS_DRBD_BARRIER,

	SEND_CANCELED,
	SEND_FAILED,
	HANDED_OVER_TO_NETWORK,
	OOS_HANDED_TO_NETWORK,
	CONNECTION_LOST_WHILE_PENDING,
	READ_RETRY_REMOTE_CANCELED,
	RECV_ACKED_BY_PEER,
	WRITE_ACKED_BY_PEER,
	WRITE_ACKED_BY_PEER_AND_SIS, /* and set_in_sync */
	CONFLICT_RESOLVED,
	POSTPONE_WRITE,
	NEG_ACKED,
	BARRIER_ACKED, /* in protocol A and B */
	DATA_RECEIVED, /* (remote पढ़ो) */

	COMPLETED_OK,
	READ_COMPLETED_WITH_ERROR,
	READ_AHEAD_COMPLETED_WITH_ERROR,
	WRITE_COMPLETED_WITH_ERROR,
	DISCARD_COMPLETED_NOTSUPP,
	DISCARD_COMPLETED_WITH_ERROR,

	ABORT_DISK_IO,
	RESEND,
	FAIL_FROZEN_DISK_IO,
	RESTART_FROZEN_DISK_IO,
	NOTHING,
पूर्ण;

/* encoding of request states क्रम now.  we करोn't actually need that many bits.
 * we करोn't need to करो atomic bit operations either, since most of the समय we
 * need to look at the connection state and/or manipulate some lists at the
 * same समय, so we should hold the request lock anyways.
 */
क्रमागत drbd_req_state_bits अणु
	/* 3210
	 * 0000: no local possible
	 * 0001: to be submitted
	 *    UNUSED, we could map: 011: submitted, completion still pending
	 * 0110: completed ok
	 * 0010: completed with error
	 * 1001: Aborted (beक्रमe completion)
	 * 1x10: Aborted and completed -> मुक्त
	 */
	__RQ_LOCAL_PENDING,
	__RQ_LOCAL_COMPLETED,
	__RQ_LOCAL_OK,
	__RQ_LOCAL_ABORTED,

	/* 87654
	 * 00000: no network possible
	 * 00001: to be send
	 * 00011: to be send, on worker queue
	 * 00101: sent, expecting recv_ack (B) or ग_लिखो_ack (C)
	 * 11101: sent,
	 *        recv_ack (B) or implicit "ack" (A),
	 *        still रुकोing क्रम the barrier ack.
	 *        master_bio may alपढ़ोy be completed and invalidated.
	 * 11100: ग_लिखो acked (C),
	 *        data received (क्रम remote पढ़ो, any protocol)
	 *        or finally the barrier ack has arrived (B,A)...
	 *        request can be मुक्तd
	 * 01100: neg-acked (ग_लिखो, protocol C)
	 *        or neg-d-acked (पढ़ो, any protocol)
	 *        or समाप्तed from the transfer log
	 *        during cleanup after connection loss
	 *        request can be मुक्तd
	 * 01000: canceled or send failed...
	 *        request can be मुक्तd
	 */

	/* अगर "SENT" is not set, yet, this can still fail or be canceled.
	 * अगर "SENT" is set alपढ़ोy, we still रुको क्रम an Ack packet.
	 * when cleared, the master_bio may be completed.
	 * in (B,A) the request object may still linger on the transaction log
	 * until the corresponding barrier ack comes in */
	__RQ_NET_PENDING,

	/* If it is QUEUED, and it is a WRITE, it is also रेजिस्टरed in the
	 * transfer log. Currently we need this flag to aव्योम conflicts between
	 * worker canceling the request and tl_clear_barrier समाप्तing it from
	 * transfer log.  We should reकाष्ठाure the code so this conflict करोes
	 * no दीर्घer occur. */
	__RQ_NET_QUEUED,

	/* well, actually only "handed over to the network stack".
	 *
	 * TODO can potentially be dropped because of the similar meaning
	 * of RQ_NET_SENT and ~RQ_NET_QUEUED.
	 * however it is not exactly the same. beक्रमe we drop it
	 * we must ensure that we can tell a request with network part
	 * from a request without, regardless of what happens to it. */
	__RQ_NET_SENT,

	/* when set, the request may be मुक्तd (अगर RQ_NET_QUEUED is clear).
	 * basically this means the corresponding P_BARRIER_ACK was received */
	__RQ_NET_DONE,

	/* whether or not we know (C) or pretend (B,A) that the ग_लिखो
	 * was successfully written on the peer.
	 */
	__RQ_NET_OK,

	/* peer called drbd_set_in_sync() क्रम this ग_लिखो */
	__RQ_NET_SIS,

	/* keep this last, its क्रम the RQ_NET_MASK */
	__RQ_NET_MAX,

	/* Set when this is a ग_लिखो, clear क्रम a पढ़ो */
	__RQ_WRITE,
	__RQ_WSAME,
	__RQ_UNMAP,
	__RQ_ZEROES,

	/* Should call drbd_al_complete_io() क्रम this request... */
	__RQ_IN_ACT_LOG,

	/* This was the most recent request during some blk_finish_plug()
	 * or its implicit from-schedule equivalent.
	 * We may use it as hपूर्णांक to send a P_UNPLUG_REMOTE */
	__RQ_UNPLUG,

	/* The peer has sent a retry ACK */
	__RQ_POSTPONED,

	/* would have been completed,
	 * but was not, because of drbd_suspended() */
	__RQ_COMPLETION_SUSP,

	/* We expect a receive ACK (wire proto B) */
	__RQ_EXP_RECEIVE_ACK,

	/* We expect a ग_लिखो ACK (wite proto C) */
	__RQ_EXP_WRITE_ACK,

	/* रुकोing क्रम a barrier ack, did an extra kref_get */
	__RQ_EXP_BARR_ACK,
पूर्ण;

#घोषणा RQ_LOCAL_PENDING   (1UL << __RQ_LOCAL_PENDING)
#घोषणा RQ_LOCAL_COMPLETED (1UL << __RQ_LOCAL_COMPLETED)
#घोषणा RQ_LOCAL_OK        (1UL << __RQ_LOCAL_OK)
#घोषणा RQ_LOCAL_ABORTED   (1UL << __RQ_LOCAL_ABORTED)

#घोषणा RQ_LOCAL_MASK      ((RQ_LOCAL_ABORTED << 1)-1)

#घोषणा RQ_NET_PENDING     (1UL << __RQ_NET_PENDING)
#घोषणा RQ_NET_QUEUED      (1UL << __RQ_NET_QUEUED)
#घोषणा RQ_NET_SENT        (1UL << __RQ_NET_SENT)
#घोषणा RQ_NET_DONE        (1UL << __RQ_NET_DONE)
#घोषणा RQ_NET_OK          (1UL << __RQ_NET_OK)
#घोषणा RQ_NET_SIS         (1UL << __RQ_NET_SIS)

#घोषणा RQ_NET_MASK        (((1UL << __RQ_NET_MAX)-1) & ~RQ_LOCAL_MASK)

#घोषणा RQ_WRITE           (1UL << __RQ_WRITE)
#घोषणा RQ_WSAME           (1UL << __RQ_WSAME)
#घोषणा RQ_UNMAP           (1UL << __RQ_UNMAP)
#घोषणा RQ_ZEROES          (1UL << __RQ_ZEROES)
#घोषणा RQ_IN_ACT_LOG      (1UL << __RQ_IN_ACT_LOG)
#घोषणा RQ_UNPLUG          (1UL << __RQ_UNPLUG)
#घोषणा RQ_POSTPONED	   (1UL << __RQ_POSTPONED)
#घोषणा RQ_COMPLETION_SUSP (1UL << __RQ_COMPLETION_SUSP)
#घोषणा RQ_EXP_RECEIVE_ACK (1UL << __RQ_EXP_RECEIVE_ACK)
#घोषणा RQ_EXP_WRITE_ACK   (1UL << __RQ_EXP_WRITE_ACK)
#घोषणा RQ_EXP_BARR_ACK    (1UL << __RQ_EXP_BARR_ACK)

/* For waking up the frozen transfer log mod_req() has to वापस अगर the request
   should be counted in the epoch object*/
#घोषणा MR_WRITE       1
#घोषणा MR_READ        2

/* Short lived temporary काष्ठा on the stack.
 * We could squirrel the error to be वापसed पूर्णांकo
 * bio->bi_iter.bi_size, or similar. But that would be too ugly. */
काष्ठा bio_and_error अणु
	काष्ठा bio *bio;
	पूर्णांक error;
पूर्ण;

बाह्य व्योम start_new_tl_epoch(काष्ठा drbd_connection *connection);
बाह्य व्योम drbd_req_destroy(काष्ठा kref *kref);
बाह्य व्योम _req_may_be_करोne(काष्ठा drbd_request *req,
		काष्ठा bio_and_error *m);
बाह्य पूर्णांक __req_mod(काष्ठा drbd_request *req, क्रमागत drbd_req_event what,
		काष्ठा bio_and_error *m);
बाह्य व्योम complete_master_bio(काष्ठा drbd_device *device,
		काष्ठा bio_and_error *m);
बाह्य व्योम request_समयr_fn(काष्ठा समयr_list *t);
बाह्य व्योम tl_restart(काष्ठा drbd_connection *connection, क्रमागत drbd_req_event what);
बाह्य व्योम _tl_restart(काष्ठा drbd_connection *connection, क्रमागत drbd_req_event what);
बाह्य व्योम tl_पात_disk_io(काष्ठा drbd_device *device);

/* this is in drbd_मुख्य.c */
बाह्य व्योम drbd_restart_request(काष्ठा drbd_request *req);

/* use this अगर you करोn't want to deal with calling complete_master_bio()
 * outside the spinlock, e.g. when walking some list on cleanup. */
अटल अंतरभूत पूर्णांक _req_mod(काष्ठा drbd_request *req, क्रमागत drbd_req_event what)
अणु
	काष्ठा drbd_device *device = req->device;
	काष्ठा bio_and_error m;
	पूर्णांक rv;

	/* __req_mod possibly मुक्तs req, करो not touch req after that! */
	rv = __req_mod(req, what, &m);
	अगर (m.bio)
		complete_master_bio(device, &m);

	वापस rv;
पूर्ण

/* completion of master bio is outside of our spinlock.
 * We still may or may not be inside some irqs disabled section
 * of the lower level driver completion callback, so we need to
 * spin_lock_irqsave here. */
अटल अंतरभूत पूर्णांक req_mod(काष्ठा drbd_request *req,
		क्रमागत drbd_req_event what)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा drbd_device *device = req->device;
	काष्ठा bio_and_error m;
	पूर्णांक rv;

	spin_lock_irqsave(&device->resource->req_lock, flags);
	rv = __req_mod(req, what, &m);
	spin_unlock_irqrestore(&device->resource->req_lock, flags);

	अगर (m.bio)
		complete_master_bio(device, &m);

	वापस rv;
पूर्ण

बाह्य bool drbd_should_करो_remote(जोड़ drbd_dev_state);

#पूर्ण_अगर
