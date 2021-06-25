<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Main SSAM/SSH controller काष्ठाure and functionality.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित _SURFACE_AGGREGATOR_CONTROLLER_H
#घोषणा _SURFACE_AGGREGATOR_CONTROLLER_H

#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/serdev.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/srcu.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/surface_aggregator/controller.h>
#समावेश <linux/surface_aggregator/serial_hub.h>

#समावेश "ssh_request_layer.h"


/* -- Safe counters. -------------------------------------------------------- */

/**
 * काष्ठा ssh_seq_counter - Safe counter क्रम SSH sequence IDs.
 * @value: The current counter value.
 */
काष्ठा ssh_seq_counter अणु
	u8 value;
पूर्ण;

/**
 * काष्ठा ssh_rqid_counter - Safe counter क्रम SSH request IDs.
 * @value: The current counter value.
 */
काष्ठा ssh_rqid_counter अणु
	u16 value;
पूर्ण;


/* -- Event/notअगरication प्रणाली. -------------------------------------------- */

/**
 * काष्ठा ssam_nf_head - Notअगरier head क्रम SSAM events.
 * @srcu: The SRCU काष्ठा क्रम synchronization.
 * @head: List-head क्रम notअगरier blocks रेजिस्टरed under this head.
 */
काष्ठा ssam_nf_head अणु
	काष्ठा srcu_काष्ठा srcu;
	काष्ठा list_head head;
पूर्ण;

/**
 * काष्ठा ssam_nf - Notअगरier callback- and activation-registry क्रम SSAM events.
 * @lock:     Lock guarding (de-)registration of notअगरier blocks. Note: This
 *            lock करोes not need to be held क्रम notअगरier calls, only
 *            registration and deregistration.
 * @refcount: The root of the RB-tree used क्रम reference-counting enabled
 *            events/notअगरications.
 * @head:     The list of notअगरier heads क्रम event/notअगरication callbacks.
 */
काष्ठा ssam_nf अणु
	काष्ठा mutex lock;
	काष्ठा rb_root refcount;
	काष्ठा ssam_nf_head head[SSH_NUM_EVENTS];
पूर्ण;


/* -- Event/async request completion प्रणाली. -------------------------------- */

काष्ठा ssam_cplt;

/**
 * काष्ठा ssam_event_item - Struct क्रम event queuing and completion.
 * @node:     The node in the queue.
 * @rqid:     The request ID of the event.
 * @ops:      Instance specअगरic functions.
 * @ops.मुक्त: Callback क्रम मुक्तing this event item.
 * @event:    Actual event data.
 */
काष्ठा ssam_event_item अणु
	काष्ठा list_head node;
	u16 rqid;

	काष्ठा अणु
		व्योम (*मुक्त)(काष्ठा ssam_event_item *event);
	पूर्ण ops;

	काष्ठा ssam_event event;	/* must be last */
पूर्ण;

/**
 * काष्ठा ssam_event_queue - Queue क्रम completing received events.
 * @cplt: Reference to the completion प्रणाली on which this queue is active.
 * @lock: The lock क्रम any operation on the queue.
 * @head: The list-head of the queue.
 * @work: The &काष्ठा work_काष्ठा perक्रमming completion work क्रम this queue.
 */
काष्ठा ssam_event_queue अणु
	काष्ठा ssam_cplt *cplt;

	spinlock_t lock;
	काष्ठा list_head head;
	काष्ठा work_काष्ठा work;
पूर्ण;

/**
 * काष्ठा ssam_event_target - Set of queues क्रम a single SSH target ID.
 * @queue: The array of queues, one queue per event ID.
 */
काष्ठा ssam_event_target अणु
	काष्ठा ssam_event_queue queue[SSH_NUM_EVENTS];
पूर्ण;

/**
 * काष्ठा ssam_cplt - SSAM event/async request completion प्रणाली.
 * @dev:          The device with which this प्रणाली is associated. Only used
 *                क्रम logging.
 * @wq:           The &काष्ठा workqueue_काष्ठा on which all completion work
 *                items are queued.
 * @event:        Event completion management.
 * @event.target: Array of &काष्ठा ssam_event_target, one क्रम each target.
 * @event.notअगर:  Notअगरier callbacks and event activation reference counting.
 */
काष्ठा ssam_cplt अणु
	काष्ठा device *dev;
	काष्ठा workqueue_काष्ठा *wq;

	काष्ठा अणु
		काष्ठा ssam_event_target target[SSH_NUM_TARGETS];
		काष्ठा ssam_nf notअगर;
	पूर्ण event;
पूर्ण;


/* -- Main SSAM device काष्ठाures. ------------------------------------------ */

/**
 * क्रमागत ssam_controller_state - State values क्रम &काष्ठा ssam_controller.
 * @SSAM_CONTROLLER_UNINITIALIZED:
 *	The controller has not been initialized yet or has been deinitialized.
 * @SSAM_CONTROLLER_INITIALIZED:
 *	The controller is initialized, but has not been started yet.
 * @SSAM_CONTROLLER_STARTED:
 *	The controller has been started and is पढ़ोy to use.
 * @SSAM_CONTROLLER_STOPPED:
 *	The controller has been stopped.
 * @SSAM_CONTROLLER_SUSPENDED:
 *	The controller has been suspended.
 */
क्रमागत ssam_controller_state अणु
	SSAM_CONTROLLER_UNINITIALIZED,
	SSAM_CONTROLLER_INITIALIZED,
	SSAM_CONTROLLER_STARTED,
	SSAM_CONTROLLER_STOPPED,
	SSAM_CONTROLLER_SUSPENDED,
पूर्ण;

/**
 * काष्ठा ssam_controller_caps - Controller device capabilities.
 * @ssh_घातer_profile:             SSH घातer profile.
 * @ssh_buffer_size:               SSH driver UART buffer size.
 * @screen_on_sleep_idle_समयout:  SAM UART screen-on sleep idle समयout.
 * @screen_off_sleep_idle_समयout: SAM UART screen-off sleep idle समयout.
 * @d3_बंदs_handle:              SAM बंदs UART handle in D3.
 *
 * Controller and SSH device capabilities found in ACPI.
 */
काष्ठा ssam_controller_caps अणु
	u32 ssh_घातer_profile;
	u32 ssh_buffer_size;
	u32 screen_on_sleep_idle_समयout;
	u32 screen_off_sleep_idle_समयout;
	u32 d3_बंदs_handle:1;
पूर्ण;

/**
 * काष्ठा ssam_controller - SSAM controller device.
 * @kref:  Reference count of the controller.
 * @lock:  Main lock क्रम the controller, used to guard state changes.
 * @state: Controller state.
 * @rtl:   Request transport layer क्रम SSH I/O.
 * @cplt:  Completion प्रणाली क्रम SSH/SSAM events and asynchronous requests.
 * @counter:      Safe SSH message ID counters.
 * @counter.seq:  Sequence ID counter.
 * @counter.rqid: Request ID counter.
 * @irq:          Wakeup IRQ resources.
 * @irq.num:      The wakeup IRQ number.
 * @irq.wakeup_enabled: Whether wakeup by IRQ is enabled during suspend.
 * @caps: The controller device capabilities.
 */
काष्ठा ssam_controller अणु
	काष्ठा kref kref;

	काष्ठा rw_semaphore lock;
	क्रमागत ssam_controller_state state;

	काष्ठा ssh_rtl rtl;
	काष्ठा ssam_cplt cplt;

	काष्ठा अणु
		काष्ठा ssh_seq_counter seq;
		काष्ठा ssh_rqid_counter rqid;
	पूर्ण counter;

	काष्ठा अणु
		पूर्णांक num;
		bool wakeup_enabled;
	पूर्ण irq;

	काष्ठा ssam_controller_caps caps;
पूर्ण;

#घोषणा to_ssam_controller(ptr, member) \
	container_of(ptr, काष्ठा ssam_controller, member)

#घोषणा ssam_dbg(ctrl, fmt, ...)  rtl_dbg(&(ctrl)->rtl, fmt, ##__VA_ARGS__)
#घोषणा ssam_info(ctrl, fmt, ...) rtl_info(&(ctrl)->rtl, fmt, ##__VA_ARGS__)
#घोषणा ssam_warn(ctrl, fmt, ...) rtl_warn(&(ctrl)->rtl, fmt, ##__VA_ARGS__)
#घोषणा ssam_err(ctrl, fmt, ...)  rtl_err(&(ctrl)->rtl, fmt, ##__VA_ARGS__)

/**
 * ssam_controller_receive_buf() - Provide input-data to the controller.
 * @ctrl: The controller.
 * @buf:  The input buffer.
 * @n:    The number of bytes in the input buffer.
 *
 * Provide input data to be evaluated by the controller, which has been
 * received via the lower-level transport.
 *
 * Return: Returns the number of bytes consumed, or, अगर the packet transport
 * layer of the controller has been shut करोwn, %-ESHUTDOWN.
 */
अटल अंतरभूत
पूर्णांक ssam_controller_receive_buf(काष्ठा ssam_controller *ctrl,
				स्थिर अचिन्हित अक्षर *buf, माप_प्रकार n)
अणु
	वापस ssh_ptl_rx_rcvbuf(&ctrl->rtl.ptl, buf, n);
पूर्ण

/**
 * ssam_controller_ग_लिखो_wakeup() - Notअगरy the controller that the underlying
 * device has space available क्रम data to be written.
 * @ctrl: The controller.
 */
अटल अंतरभूत व्योम ssam_controller_ग_लिखो_wakeup(काष्ठा ssam_controller *ctrl)
अणु
	ssh_ptl_tx_wakeup_transfer(&ctrl->rtl.ptl);
पूर्ण

पूर्णांक ssam_controller_init(काष्ठा ssam_controller *ctrl, काष्ठा serdev_device *s);
पूर्णांक ssam_controller_start(काष्ठा ssam_controller *ctrl);
व्योम ssam_controller_shutकरोwn(काष्ठा ssam_controller *ctrl);
व्योम ssam_controller_destroy(काष्ठा ssam_controller *ctrl);

पूर्णांक ssam_notअगरier_disable_रेजिस्टरed(काष्ठा ssam_controller *ctrl);
व्योम ssam_notअगरier_restore_रेजिस्टरed(काष्ठा ssam_controller *ctrl);

पूर्णांक ssam_irq_setup(काष्ठा ssam_controller *ctrl);
व्योम ssam_irq_मुक्त(काष्ठा ssam_controller *ctrl);
पूर्णांक ssam_irq_arm_क्रम_wakeup(काष्ठा ssam_controller *ctrl);
व्योम ssam_irq_disarm_wakeup(काष्ठा ssam_controller *ctrl);

व्योम ssam_controller_lock(काष्ठा ssam_controller *c);
व्योम ssam_controller_unlock(काष्ठा ssam_controller *c);

पूर्णांक ssam_get_firmware_version(काष्ठा ssam_controller *ctrl, u32 *version);
पूर्णांक ssam_ctrl_notअगर_display_off(काष्ठा ssam_controller *ctrl);
पूर्णांक ssam_ctrl_notअगर_display_on(काष्ठा ssam_controller *ctrl);
पूर्णांक ssam_ctrl_notअगर_d0_निकास(काष्ठा ssam_controller *ctrl);
पूर्णांक ssam_ctrl_notअगर_d0_entry(काष्ठा ssam_controller *ctrl);

पूर्णांक ssam_controller_suspend(काष्ठा ssam_controller *ctrl);
पूर्णांक ssam_controller_resume(काष्ठा ssam_controller *ctrl);

पूर्णांक ssam_event_item_cache_init(व्योम);
व्योम ssam_event_item_cache_destroy(व्योम);

#पूर्ण_अगर /* _SURFACE_AGGREGATOR_CONTROLLER_H */
