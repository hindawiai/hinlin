<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * SSH request transport layer.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित _SURFACE_AGGREGATOR_SSH_REQUEST_LAYER_H
#घोषणा _SURFACE_AGGREGATOR_SSH_REQUEST_LAYER_H

#समावेश <linux/atomic.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/surface_aggregator/serial_hub.h>
#समावेश <linux/surface_aggregator/controller.h>

#समावेश "ssh_packet_layer.h"

/**
 * क्रमागत ssh_rtl_state_flags - State-flags क्रम &काष्ठा ssh_rtl.
 *
 * @SSH_RTL_SF_SHUTDOWN_BIT:
 *	Indicates that the request transport layer has been shut करोwn or is
 *	being shut करोwn and should not accept any new requests.
 */
क्रमागत ssh_rtl_state_flags अणु
	SSH_RTL_SF_SHUTDOWN_BIT,
पूर्ण;

/**
 * काष्ठा ssh_rtl_ops - Callback operations क्रम request transport layer.
 * @handle_event: Function called when a SSH event has been received. The
 *                specअगरied function takes the request layer, received command
 *                काष्ठा, and corresponding payload as arguments. If the event
 *                has no payload, the payload span is empty (not %शून्य).
 */
काष्ठा ssh_rtl_ops अणु
	व्योम (*handle_event)(काष्ठा ssh_rtl *rtl, स्थिर काष्ठा ssh_command *cmd,
			     स्थिर काष्ठा ssam_span *data);
पूर्ण;

/**
 * काष्ठा ssh_rtl - SSH request transport layer.
 * @ptl:           Underlying packet transport layer.
 * @state:         State(-flags) of the transport layer.
 * @queue:         Request submission queue.
 * @queue.lock:    Lock क्रम modअगरying the request submission queue.
 * @queue.head:    List-head of the request submission queue.
 * @pending:       Set/list of pending requests.
 * @pending.lock:  Lock क्रम modअगरying the request set.
 * @pending.head:  List-head of the pending set/list.
 * @pending.count: Number of currently pending requests.
 * @tx:            Transmitter subप्रणाली.
 * @tx.work:       Transmitter work item.
 * @rtx_समयout:   Retransmission समयout subप्रणाली.
 * @rtx_समयout.lock:    Lock क्रम modअगरying the retransmission समयout reaper.
 * @rtx_समयout.समयout: Timeout पूर्णांकerval क्रम retransmission.
 * @rtx_समयout.expires: Time specअगरying when the reaper work is next scheduled.
 * @rtx_समयout.reaper:  Work perक्रमming समयout checks and subsequent actions.
 * @ops:           Request layer operations.
 */
काष्ठा ssh_rtl अणु
	काष्ठा ssh_ptl ptl;
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
		काष्ठा work_काष्ठा work;
	पूर्ण tx;

	काष्ठा अणु
		spinlock_t lock;
		kसमय_प्रकार समयout;
		kसमय_प्रकार expires;
		काष्ठा delayed_work reaper;
	पूर्ण rtx_समयout;

	काष्ठा ssh_rtl_ops ops;
पूर्ण;

#घोषणा rtl_dbg(r, fmt, ...)  ptl_dbg(&(r)->ptl, fmt, ##__VA_ARGS__)
#घोषणा rtl_info(p, fmt, ...) ptl_info(&(p)->ptl, fmt, ##__VA_ARGS__)
#घोषणा rtl_warn(r, fmt, ...) ptl_warn(&(r)->ptl, fmt, ##__VA_ARGS__)
#घोषणा rtl_err(r, fmt, ...)  ptl_err(&(r)->ptl, fmt, ##__VA_ARGS__)
#घोषणा rtl_dbg_cond(r, fmt, ...) __ssam_prcond(rtl_dbg, r, fmt, ##__VA_ARGS__)

#घोषणा to_ssh_rtl(ptr, member) \
	container_of(ptr, काष्ठा ssh_rtl, member)

/**
 * ssh_rtl_get_device() - Get device associated with request transport layer.
 * @rtl: The request transport layer.
 *
 * Return: Returns the device on which the given request transport layer
 * builds upon.
 */
अटल अंतरभूत काष्ठा device *ssh_rtl_get_device(काष्ठा ssh_rtl *rtl)
अणु
	वापस ssh_ptl_get_device(&rtl->ptl);
पूर्ण

/**
 * ssh_request_rtl() - Get request transport layer associated with request.
 * @rqst: The request to get the request transport layer reference क्रम.
 *
 * Return: Returns the &काष्ठा ssh_rtl associated with the given SSH request.
 */
अटल अंतरभूत काष्ठा ssh_rtl *ssh_request_rtl(काष्ठा ssh_request *rqst)
अणु
	काष्ठा ssh_ptl *ptl;

	ptl = READ_ONCE(rqst->packet.ptl);
	वापस likely(ptl) ? to_ssh_rtl(ptl, ptl) : शून्य;
पूर्ण

पूर्णांक ssh_rtl_submit(काष्ठा ssh_rtl *rtl, काष्ठा ssh_request *rqst);
bool ssh_rtl_cancel(काष्ठा ssh_request *rqst, bool pending);

पूर्णांक ssh_rtl_init(काष्ठा ssh_rtl *rtl, काष्ठा serdev_device *serdev,
		 स्थिर काष्ठा ssh_rtl_ops *ops);

पूर्णांक ssh_rtl_start(काष्ठा ssh_rtl *rtl);
पूर्णांक ssh_rtl_flush(काष्ठा ssh_rtl *rtl, अचिन्हित दीर्घ समयout);
व्योम ssh_rtl_shutकरोwn(काष्ठा ssh_rtl *rtl);
व्योम ssh_rtl_destroy(काष्ठा ssh_rtl *rtl);

पूर्णांक ssh_request_init(काष्ठा ssh_request *rqst, क्रमागत ssam_request_flags flags,
		     स्थिर काष्ठा ssh_request_ops *ops);

#पूर्ण_अगर /* _SURFACE_AGGREGATOR_SSH_REQUEST_LAYER_H */
