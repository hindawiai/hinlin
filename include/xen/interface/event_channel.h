<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * event_channel.h
 *
 * Event channels between करोमुख्यs.
 *
 * Copyright (c) 2003-2004, K A Fraser.
 */

#अगर_अघोषित __XEN_PUBLIC_EVENT_CHANNEL_H__
#घोषणा __XEN_PUBLIC_EVENT_CHANNEL_H__

#समावेश <xen/पूर्णांकerface/xen.h>

प्रकार uपूर्णांक32_t evtchn_port_t;
DEFINE_GUEST_HANDLE(evtchn_port_t);

/*
 * EVTCHNOP_alloc_unbound: Allocate a port in करोमुख्य <करोm> and mark as
 * accepting पूर्णांकerकरोमुख्य bindings from करोमुख्य <remote_करोm>. A fresh port
 * is allocated in <करोm> and वापसed as <port>.
 * NOTES:
 *  1. If the caller is unprivileged then <करोm> must be DOMID_SELF.
 *  2. <rकरोm> may be DOMID_SELF, allowing loopback connections.
 */
#घोषणा EVTCHNOP_alloc_unbound	  6
काष्ठा evtchn_alloc_unbound अणु
	/* IN parameters */
	करोmid_t करोm, remote_करोm;
	/* OUT parameters */
	evtchn_port_t port;
पूर्ण;

/*
 * EVTCHNOP_bind_पूर्णांकerकरोमुख्य: Conकाष्ठा an पूर्णांकerकरोमुख्य event channel between
 * the calling करोमुख्य and <remote_करोm>. <remote_करोm,remote_port> must identअगरy
 * a port that is unbound and marked as accepting bindings from the calling
 * करोमुख्य. A fresh port is allocated in the calling करोमुख्य and वापसed as
 * <local_port>.
 * NOTES:
 *  2. <remote_करोm> may be DOMID_SELF, allowing loopback connections.
 */
#घोषणा EVTCHNOP_bind_पूर्णांकerकरोमुख्य 0
काष्ठा evtchn_bind_पूर्णांकerकरोमुख्य अणु
	/* IN parameters. */
	करोmid_t remote_करोm;
	evtchn_port_t remote_port;
	/* OUT parameters. */
	evtchn_port_t local_port;
पूर्ण;

/*
 * EVTCHNOP_bind_virq: Bind a local event channel to VIRQ <irq> on specअगरied
 * vcpu.
 * NOTES:
 *  1. A भव IRQ may be bound to at most one event channel per vcpu.
 *  2. The allocated event channel is bound to the specअगरied vcpu. The binding
 *     may not be changed.
 */
#घोषणा EVTCHNOP_bind_virq	  1
काष्ठा evtchn_bind_virq अणु
	/* IN parameters. */
	uपूर्णांक32_t virq;
	uपूर्णांक32_t vcpu;
	/* OUT parameters. */
	evtchn_port_t port;
पूर्ण;

/*
 * EVTCHNOP_bind_pirq: Bind a local event channel to PIRQ <irq>.
 * NOTES:
 *  1. A physical IRQ may be bound to at most one event channel per करोमुख्य.
 *  2. Only a sufficiently-privileged करोमुख्य may bind to a physical IRQ.
 */
#घोषणा EVTCHNOP_bind_pirq	  2
काष्ठा evtchn_bind_pirq अणु
	/* IN parameters. */
	uपूर्णांक32_t pirq;
#घोषणा BIND_PIRQ__WILL_SHARE 1
	uपूर्णांक32_t flags; /* BIND_PIRQ__* */
	/* OUT parameters. */
	evtchn_port_t port;
पूर्ण;

/*
 * EVTCHNOP_bind_ipi: Bind a local event channel to receive events.
 * NOTES:
 *  1. The allocated event channel is bound to the specअगरied vcpu. The binding
 *     may not be changed.
 */
#घोषणा EVTCHNOP_bind_ipi	  7
काष्ठा evtchn_bind_ipi अणु
	uपूर्णांक32_t vcpu;
	/* OUT parameters. */
	evtchn_port_t port;
पूर्ण;

/*
 * EVTCHNOP_बंद: Close a local event channel <port>. If the channel is
 * पूर्णांकerकरोमुख्य then the remote end is placed in the unbound state
 * (EVTCHNSTAT_unbound), aरुकोing a new connection.
 */
#घोषणा EVTCHNOP_बंद		  3
काष्ठा evtchn_बंद अणु
	/* IN parameters. */
	evtchn_port_t port;
पूर्ण;

/*
 * EVTCHNOP_send: Send an event to the remote end of the channel whose local
 * endpoपूर्णांक is <port>.
 */
#घोषणा EVTCHNOP_send		  4
काष्ठा evtchn_send अणु
	/* IN parameters. */
	evtchn_port_t port;
पूर्ण;

/*
 * EVTCHNOP_status: Get the current status of the communication channel which
 * has an endpoपूर्णांक at <करोm, port>.
 * NOTES:
 *  1. <करोm> may be specअगरied as DOMID_SELF.
 *  2. Only a sufficiently-privileged करोमुख्य may obtain the status of an event
 *     channel क्रम which <करोm> is not DOMID_SELF.
 */
#घोषणा EVTCHNOP_status		  5
काष्ठा evtchn_status अणु
	/* IN parameters */
	करोmid_t  करोm;
	evtchn_port_t port;
	/* OUT parameters */
#घोषणा EVTCHNSTAT_बंदd	0  /* Channel is not in use.		     */
#घोषणा EVTCHNSTAT_unbound	1  /* Channel is रुकोing पूर्णांकerकरोm connection.*/
#घोषणा EVTCHNSTAT_पूर्णांकerकरोमुख्य	2  /* Channel is connected to remote करोमुख्य. */
#घोषणा EVTCHNSTAT_pirq		3  /* Channel is bound to a phys IRQ line.   */
#घोषणा EVTCHNSTAT_virq		4  /* Channel is bound to a भव IRQ line */
#घोषणा EVTCHNSTAT_ipi		5  /* Channel is bound to a भव IPI line */
	uपूर्णांक32_t status;
	uपूर्णांक32_t vcpu;		   /* VCPU to which this channel is bound.   */
	जोड़ अणु
		काष्ठा अणु
			करोmid_t करोm;
		पूर्ण unbound; /* EVTCHNSTAT_unbound */
		काष्ठा अणु
			करोmid_t करोm;
			evtchn_port_t port;
		पूर्ण पूर्णांकerकरोमुख्य; /* EVTCHNSTAT_पूर्णांकerकरोमुख्य */
		uपूर्णांक32_t pirq;	    /* EVTCHNSTAT_pirq	      */
		uपूर्णांक32_t virq;	    /* EVTCHNSTAT_virq	      */
	पूर्ण u;
पूर्ण;

/*
 * EVTCHNOP_bind_vcpu: Specअगरy which vcpu a channel should notअगरy when an
 * event is pending.
 * NOTES:
 *  1. IPI- and VIRQ-bound channels always notअगरy the vcpu that initialised
 *     the binding. This binding cannot be changed.
 *  2. All other channels notअगरy vcpu0 by शेष. This शेष is set when
 *     the channel is allocated (a port that is मुक्तd and subsequently reused
 *     has its binding reset to vcpu0).
 */
#घोषणा EVTCHNOP_bind_vcpu	  8
काष्ठा evtchn_bind_vcpu अणु
	/* IN parameters. */
	evtchn_port_t port;
	uपूर्णांक32_t vcpu;
पूर्ण;

/*
 * EVTCHNOP_unmask: Unmask the specअगरied local event-channel port and deliver
 * a notअगरication to the appropriate VCPU अगर an event is pending.
 */
#घोषणा EVTCHNOP_unmask		  9
काष्ठा evtchn_unmask अणु
	/* IN parameters. */
	evtchn_port_t port;
पूर्ण;

/*
 * EVTCHNOP_reset: Close all event channels associated with specअगरied करोमुख्य.
 * NOTES:
 *  1. <करोm> may be specअगरied as DOMID_SELF.
 *  2. Only a sufficiently-privileged करोमुख्य may specअगरy other than DOMID_SELF.
 */
#घोषणा EVTCHNOP_reset		 10
काष्ठा evtchn_reset अणु
	/* IN parameters. */
	करोmid_t करोm;
पूर्ण;
प्रकार काष्ठा evtchn_reset evtchn_reset_t;

/*
 * EVTCHNOP_init_control: initialize the control block क्रम the FIFO ABI.
 */
#घोषणा EVTCHNOP_init_control    11
काष्ठा evtchn_init_control अणु
	/* IN parameters. */
	uपूर्णांक64_t control_gfn;
	uपूर्णांक32_t offset;
	uपूर्णांक32_t vcpu;
	/* OUT parameters. */
	uपूर्णांक8_t link_bits;
	uपूर्णांक8_t _pad[7];
पूर्ण;

/*
 * EVTCHNOP_expand_array: add an additional page to the event array.
 */
#घोषणा EVTCHNOP_expand_array    12
काष्ठा evtchn_expand_array अणु
	/* IN parameters. */
	uपूर्णांक64_t array_gfn;
पूर्ण;

/*
 * EVTCHNOP_set_priority: set the priority क्रम an event channel.
 */
#घोषणा EVTCHNOP_set_priority    13
काष्ठा evtchn_set_priority अणु
	/* IN parameters. */
	evtchn_port_t port;
	uपूर्णांक32_t priority;
पूर्ण;

काष्ठा evtchn_op अणु
	uपूर्णांक32_t cmd; /* EVTCHNOP_* */
	जोड़ अणु
		काष्ठा evtchn_alloc_unbound    alloc_unbound;
		काष्ठा evtchn_bind_पूर्णांकerकरोमुख्य bind_पूर्णांकerकरोमुख्य;
		काष्ठा evtchn_bind_virq	       bind_virq;
		काष्ठा evtchn_bind_pirq	       bind_pirq;
		काष्ठा evtchn_bind_ipi	       bind_ipi;
		काष्ठा evtchn_बंद	       बंद;
		काष्ठा evtchn_send	       send;
		काष्ठा evtchn_status	       status;
		काष्ठा evtchn_bind_vcpu	       bind_vcpu;
		काष्ठा evtchn_unmask	       unmask;
	पूर्ण u;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(evtchn_op);

/*
 * 2-level ABI
 */

#घोषणा EVTCHN_2L_NR_CHANNELS (माप(xen_uदीर्घ_t) * माप(xen_uदीर्घ_t) * 64)

/*
 * FIFO ABI
 */

/* Events may have priorities from 0 (highest) to 15 (lowest). */
#घोषणा EVTCHN_FIFO_PRIORITY_MAX     0
#घोषणा EVTCHN_FIFO_PRIORITY_DEFAULT 7
#घोषणा EVTCHN_FIFO_PRIORITY_MIN     15

#घोषणा EVTCHN_FIFO_MAX_QUEUES (EVTCHN_FIFO_PRIORITY_MIN + 1)

प्रकार uपूर्णांक32_t event_word_t;

#घोषणा EVTCHN_FIFO_PENDING 31
#घोषणा EVTCHN_FIFO_MASKED  30
#घोषणा EVTCHN_FIFO_LINKED  29
#घोषणा EVTCHN_FIFO_BUSY    28

#घोषणा EVTCHN_FIFO_LINK_BITS 17
#घोषणा EVTCHN_FIFO_LINK_MASK ((1 << EVTCHN_FIFO_LINK_BITS) - 1)

#घोषणा EVTCHN_FIFO_NR_CHANNELS (1 << EVTCHN_FIFO_LINK_BITS)

काष्ठा evtchn_fअगरo_control_block अणु
	uपूर्णांक32_t     पढ़ोy;
	uपूर्णांक32_t     _rsvd;
	event_word_t head[EVTCHN_FIFO_MAX_QUEUES];
पूर्ण;

#पूर्ण_अगर /* __XEN_PUBLIC_EVENT_CHANNEL_H__ */
