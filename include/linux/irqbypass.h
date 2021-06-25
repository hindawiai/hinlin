<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * IRQ offload/bypass manager
 *
 * Copyright (C) 2015 Red Hat, Inc.
 * Copyright (c) 2015 Linaro Ltd.
 */
#अगर_अघोषित IRQBYPASS_H
#घोषणा IRQBYPASS_H

#समावेश <linux/list.h>

काष्ठा irq_bypass_consumer;

/*
 * Theory of operation
 *
 * The IRQ bypass manager is a simple set of lists and callbacks that allows
 * IRQ producers (ex. physical पूर्णांकerrupt sources) to be matched to IRQ
 * consumers (ex. भवization hardware that allows IRQ bypass or offload)
 * via a shared token (ex. eventfd_ctx).  Producers and consumers रेजिस्टर
 * independently.  When a token match is found, the optional @stop callback
 * will be called क्रम each participant.  The pair will then be connected via
 * the @add_* callbacks, and finally the optional @start callback will allow
 * any final coordination.  When either participant is unरेजिस्टरed, the
 * process is repeated using the @del_* callbacks in place of the @add_*
 * callbacks.  Match tokens must be unique per producer/consumer, 1:N pairings
 * are not supported.
 */

/**
 * काष्ठा irq_bypass_producer - IRQ bypass producer definition
 * @node: IRQ bypass manager निजी list management
 * @token: opaque token to match between producer and consumer (non-शून्य)
 * @irq: Linux IRQ number क्रम the producer device
 * @add_consumer: Connect the IRQ producer to an IRQ consumer (optional)
 * @del_consumer: Disconnect the IRQ producer from an IRQ consumer (optional)
 * @stop: Perक्रमm any quiesce operations necessary prior to add/del (optional)
 * @start: Perक्रमm any startup operations necessary after add/del (optional)
 *
 * The IRQ bypass producer काष्ठाure represents an पूर्णांकerrupt source क्रम
 * participation in possible host bypass, क्रम instance an पूर्णांकerrupt vector
 * क्रम a physical device asचिन्हित to a VM.
 */
काष्ठा irq_bypass_producer अणु
	काष्ठा list_head node;
	व्योम *token;
	पूर्णांक irq;
	पूर्णांक (*add_consumer)(काष्ठा irq_bypass_producer *,
			    काष्ठा irq_bypass_consumer *);
	व्योम (*del_consumer)(काष्ठा irq_bypass_producer *,
			     काष्ठा irq_bypass_consumer *);
	व्योम (*stop)(काष्ठा irq_bypass_producer *);
	व्योम (*start)(काष्ठा irq_bypass_producer *);
पूर्ण;

/**
 * काष्ठा irq_bypass_consumer - IRQ bypass consumer definition
 * @node: IRQ bypass manager निजी list management
 * @token: opaque token to match between producer and consumer (non-शून्य)
 * @add_producer: Connect the IRQ consumer to an IRQ producer
 * @del_producer: Disconnect the IRQ consumer from an IRQ producer
 * @stop: Perक्रमm any quiesce operations necessary prior to add/del (optional)
 * @start: Perक्रमm any startup operations necessary after add/del (optional)
 *
 * The IRQ bypass consumer काष्ठाure represents an पूर्णांकerrupt sink क्रम
 * participation in possible host bypass, क्रम instance a hypervisor may
 * support offloads to allow bypassing the host entirely or offload
 * portions of the पूर्णांकerrupt handling to the VM.
 */
काष्ठा irq_bypass_consumer अणु
	काष्ठा list_head node;
	व्योम *token;
	पूर्णांक (*add_producer)(काष्ठा irq_bypass_consumer *,
			    काष्ठा irq_bypass_producer *);
	व्योम (*del_producer)(काष्ठा irq_bypass_consumer *,
			     काष्ठा irq_bypass_producer *);
	व्योम (*stop)(काष्ठा irq_bypass_consumer *);
	व्योम (*start)(काष्ठा irq_bypass_consumer *);
पूर्ण;

पूर्णांक irq_bypass_रेजिस्टर_producer(काष्ठा irq_bypass_producer *);
व्योम irq_bypass_unरेजिस्टर_producer(काष्ठा irq_bypass_producer *);
पूर्णांक irq_bypass_रेजिस्टर_consumer(काष्ठा irq_bypass_consumer *);
व्योम irq_bypass_unरेजिस्टर_consumer(काष्ठा irq_bypass_consumer *);

#पूर्ण_अगर /* IRQBYPASS_H */
