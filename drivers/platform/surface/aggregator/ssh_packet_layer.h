<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * SSH packet transport layer.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित _SURFACE_AGGREGATOR_SSH_PACKET_LAYER_H
#घोषणा _SURFACE_AGGREGATOR_SSH_PACKET_LAYER_H

#समावेश <linux/atomic.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/serdev.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/surface_aggregator/serial_hub.h>
#समावेश "ssh_parser.h"

/**
 * क्रमागत ssh_ptl_state_flags - State-flags क्रम &काष्ठा ssh_ptl.
 *
 * @SSH_PTL_SF_SHUTDOWN_BIT:
 *	Indicates that the packet transport layer has been shut करोwn or is
 *	being shut करोwn and should not accept any new packets/data.
 */
क्रमागत ssh_ptl_state_flags अणु
	SSH_PTL_SF_SHUTDOWN_BIT,
पूर्ण;

/**
 * काष्ठा ssh_ptl_ops - Callback operations क्रम packet transport layer.
 * @data_received: Function called when a data-packet has been received. Both,
 *                 the packet layer on which the packet has been received and
 *                 the packet's payload data are provided to this function.
 */
काष्ठा ssh_ptl_ops अणु
	व्योम (*data_received)(काष्ठा ssh_ptl *p, स्थिर काष्ठा ssam_span *data);
पूर्ण;

/**
 * काष्ठा ssh_ptl - SSH packet transport layer.
 * @serdev:        Serial device providing the underlying data transport.
 * @state:         State(-flags) of the transport layer.
 * @queue:         Packet submission queue.
 * @queue.lock:    Lock क्रम modअगरying the packet submission queue.
 * @queue.head:    List-head of the packet submission queue.
 * @pending:       Set/list of pending packets.
 * @pending.lock:  Lock क्रम modअगरying the pending set.
 * @pending.head:  List-head of the pending set/list.
 * @pending.count: Number of currently pending packets.
 * @tx:            Transmitter subप्रणाली.
 * @tx.running:    Flag indicating (desired) transmitter thपढ़ो state.
 * @tx.thपढ़ो:     Transmitter thपढ़ो.
 * @tx.thपढ़ो_cplt_tx:  Completion क्रम transmitter thपढ़ो रुकोing on transfer.
 * @tx.thपढ़ो_cplt_pkt: Completion क्रम transmitter thपढ़ो रुकोing on packets.
 * @tx.packet_wq:  Waitqueue-head क्रम packet transmit completion.
 * @rx:            Receiver subप्रणाली.
 * @rx.thपढ़ो:     Receiver thपढ़ो.
 * @rx.wq:         Waitqueue-head क्रम receiver thपढ़ो.
 * @rx.fअगरo:       Buffer क्रम receiving data/pushing data to receiver thपढ़ो.
 * @rx.buf:        Buffer क्रम evaluating data on receiver thपढ़ो.
 * @rx.blocked:    List of recent/blocked sequence IDs to detect retransmission.
 * @rx.blocked.seqs:   Array of blocked sequence IDs.
 * @rx.blocked.offset: Offset indicating where a new ID should be inserted.
 * @rtx_समयout:   Retransmission समयout subप्रणाली.
 * @rtx_समयout.lock:    Lock क्रम modअगरying the retransmission समयout reaper.
 * @rtx_समयout.समयout: Timeout पूर्णांकerval क्रम retransmission.
 * @rtx_समयout.expires: Time specअगरying when the reaper work is next scheduled.
 * @rtx_समयout.reaper:  Work perक्रमming समयout checks and subsequent actions.
 * @ops:           Packet layer operations.
 */
काष्ठा ssh_ptl अणु
	काष्ठा serdev_device *serdev;
	अचिन्हित दीर्घ state;

	काष्ठा अणु
		spinlock_t lock;
		काष्ठा list_head head;
	पूर्ण queue;

	काष्ठा अणु
		spinlock_t lock;
		काष्ठा list_head head;
		atomic_t count;
	पूर्ण pending;

	काष्ठा अणु
		atomic_t running;
		काष्ठा task_काष्ठा *thपढ़ो;
		काष्ठा completion thपढ़ो_cplt_tx;
		काष्ठा completion thपढ़ो_cplt_pkt;
		काष्ठा रुको_queue_head packet_wq;
	पूर्ण tx;

	काष्ठा अणु
		काष्ठा task_काष्ठा *thपढ़ो;
		काष्ठा रुको_queue_head wq;
		काष्ठा kfअगरo fअगरo;
		काष्ठा sshp_buf buf;

		काष्ठा अणु
			u16 seqs[8];
			u16 offset;
		पूर्ण blocked;
	पूर्ण rx;

	काष्ठा अणु
		spinlock_t lock;
		kसमय_प्रकार समयout;
		kसमय_प्रकार expires;
		काष्ठा delayed_work reaper;
	पूर्ण rtx_समयout;

	काष्ठा ssh_ptl_ops ops;
पूर्ण;

#घोषणा __ssam_prcond(func, p, fmt, ...)		\
	करो अणु						\
		typeof(p) __p = (p);			\
							\
		अगर (__p)				\
			func(__p, fmt, ##__VA_ARGS__);	\
	पूर्ण जबतक (0)

#घोषणा ptl_dbg(p, fmt, ...)  dev_dbg(&(p)->serdev->dev, fmt, ##__VA_ARGS__)
#घोषणा ptl_info(p, fmt, ...) dev_info(&(p)->serdev->dev, fmt, ##__VA_ARGS__)
#घोषणा ptl_warn(p, fmt, ...) dev_warn(&(p)->serdev->dev, fmt, ##__VA_ARGS__)
#घोषणा ptl_err(p, fmt, ...)  dev_err(&(p)->serdev->dev, fmt, ##__VA_ARGS__)
#घोषणा ptl_dbg_cond(p, fmt, ...) __ssam_prcond(ptl_dbg, p, fmt, ##__VA_ARGS__)

#घोषणा to_ssh_ptl(ptr, member) \
	container_of(ptr, काष्ठा ssh_ptl, member)

पूर्णांक ssh_ptl_init(काष्ठा ssh_ptl *ptl, काष्ठा serdev_device *serdev,
		 काष्ठा ssh_ptl_ops *ops);

व्योम ssh_ptl_destroy(काष्ठा ssh_ptl *ptl);

/**
 * ssh_ptl_get_device() - Get device associated with packet transport layer.
 * @ptl: The packet transport layer.
 *
 * Return: Returns the device on which the given packet transport layer builds
 * upon.
 */
अटल अंतरभूत काष्ठा device *ssh_ptl_get_device(काष्ठा ssh_ptl *ptl)
अणु
	वापस ptl->serdev ? &ptl->serdev->dev : शून्य;
पूर्ण

पूर्णांक ssh_ptl_tx_start(काष्ठा ssh_ptl *ptl);
पूर्णांक ssh_ptl_tx_stop(काष्ठा ssh_ptl *ptl);
पूर्णांक ssh_ptl_rx_start(काष्ठा ssh_ptl *ptl);
पूर्णांक ssh_ptl_rx_stop(काष्ठा ssh_ptl *ptl);
व्योम ssh_ptl_shutकरोwn(काष्ठा ssh_ptl *ptl);

पूर्णांक ssh_ptl_submit(काष्ठा ssh_ptl *ptl, काष्ठा ssh_packet *p);
व्योम ssh_ptl_cancel(काष्ठा ssh_packet *p);

पूर्णांक ssh_ptl_rx_rcvbuf(काष्ठा ssh_ptl *ptl, स्थिर u8 *buf, माप_प्रकार n);

/**
 * ssh_ptl_tx_wakeup_transfer() - Wake up packet transmitter thपढ़ो क्रम
 * transfer.
 * @ptl: The packet transport layer.
 *
 * Wakes up the packet transmitter thपढ़ो, notअगरying it that the underlying
 * transport has more space क्रम data to be transmitted. If the packet
 * transport layer has been shut करोwn, calls to this function will be ignored.
 */
अटल अंतरभूत व्योम ssh_ptl_tx_wakeup_transfer(काष्ठा ssh_ptl *ptl)
अणु
	अगर (test_bit(SSH_PTL_SF_SHUTDOWN_BIT, &ptl->state))
		वापस;

	complete(&ptl->tx.thपढ़ो_cplt_tx);
पूर्ण

व्योम ssh_packet_init(काष्ठा ssh_packet *packet, अचिन्हित दीर्घ type,
		     u8 priority, स्थिर काष्ठा ssh_packet_ops *ops);

पूर्णांक ssh_ctrl_packet_cache_init(व्योम);
व्योम ssh_ctrl_packet_cache_destroy(व्योम);

#पूर्ण_अगर /* _SURFACE_AGGREGATOR_SSH_PACKET_LAYER_H */
