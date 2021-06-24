<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2010 2011 Mark Nelson and Tseng-Hui (Frank) Lin, IBM Corporation
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/io_event_irq.h>

#समावेश "pseries.h"

/*
 * IO event पूर्णांकerrupt is a mechanism provided by RTAS to वापस
 * inक्रमmation about hardware error and non-error events. Device
 * drivers can रेजिस्टर their event handlers to receive events.
 * Device drivers are expected to use atomic_notअगरier_chain_रेजिस्टर()
 * and atomic_notअगरier_chain_unरेजिस्टर() to रेजिस्टर and unरेजिस्टर
 * their event handlers. Since multiple IO event types and scopes
 * share an IO event पूर्णांकerrupt, the event handlers are called one
 * by one until the IO event is claimed by one of the handlers.
 * The event handlers are expected to वापस NOTIFY_OK अगर the
 * event is handled by the event handler or NOTIFY_DONE अगर the
 * event करोes not beदीर्घ to the handler.
 *
 * Usage:
 *
 * Notअगरier function:
 * #समावेश <यंत्र/io_event_irq.h>
 * पूर्णांक event_handler(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val, व्योम *data) अणु
 * 	p = (काष्ठा pseries_io_event_sect_data *) data;
 * 	अगर (! is_my_event(p->scope, p->event_type)) वापस NOTIFY_DONE;
 * 		:
 * 		:
 * 	वापस NOTIFY_OK;
 * पूर्ण
 * काष्ठा notअगरier_block event_nb = अणु
 * 	.notअगरier_call = event_handler,
 * पूर्ण
 *
 * Registration:
 * atomic_notअगरier_chain_रेजिस्टर(&pseries_ioei_notअगरier_list, &event_nb);
 *
 * Unregistration:
 * atomic_notअगरier_chain_unरेजिस्टर(&pseries_ioei_notअगरier_list, &event_nb);
 */

ATOMIC_NOTIFIER_HEAD(pseries_ioei_notअगरier_list);
EXPORT_SYMBOL_GPL(pseries_ioei_notअगरier_list);

अटल पूर्णांक ioei_check_exception_token;

अटल अक्षर ioei_rtas_buf[RTAS_DATA_BUF_SIZE] __cacheline_aligned;

/**
 * Find the data portion of an IO Event section from event log.
 * @elog: RTAS error/event log.
 *
 * Return:
 * 	poपूर्णांकer to a valid IO event section data. शून्य अगर not found.
 */
अटल काष्ठा pseries_io_event * ioei_find_event(काष्ठा rtas_error_log *elog)
अणु
	काष्ठा pseries_errorlog *sect;

	/* We should only ever get called क्रम io-event पूर्णांकerrupts, but अगर
	 * we करो get called क्रम another type then something went wrong so
	 * make some noise about it.
	 * RTAS_TYPE_IO only exists in extended event log version 6 or later.
	 * No need to check event log version.
	 */
	अगर (unlikely(rtas_error_type(elog) != RTAS_TYPE_IO)) अणु
		prपूर्णांकk_once(KERN_WARNING"io_event_irq: Unexpected event type %d",
			    rtas_error_type(elog));
		वापस शून्य;
	पूर्ण

	sect = get_pseries_errorlog(elog, PSERIES_ELOG_SECT_ID_IO_EVENT);
	अगर (unlikely(!sect)) अणु
		prपूर्णांकk_once(KERN_WARNING "io_event_irq: RTAS extended event "
			    "log does not contain an IO Event section. "
			    "Could be a bug in system firmware!\n");
		वापस शून्य;
	पूर्ण
	वापस (काष्ठा pseries_io_event *) &sect->data;
पूर्ण

/*
 * PAPR:
 * - check-exception वापसs the first found error or event and clear that
 *   error or event so it is reported once.
 * - Each पूर्णांकerrupt वापसs one event. If a plateक्रमm chooses to report
 *   multiple events through a single पूर्णांकerrupt, it must ensure that the
 *   पूर्णांकerrupt reमुख्यs निश्चितed until check-exception has been used to
 *   process all out-standing events क्रम that पूर्णांकerrupt.
 *
 * Implementation notes:
 * - Events must be processed in the order they are वापसed. Hence,
 *   sequential in nature.
 * - The owner of an event is determined by combinations of scope,
 *   event type, and sub-type. There is no easy way to pre-sort clients
 *   by scope or event type alone. For example, Torrent ISR route change
 *   event is reported with scope 0x00 (Not Applicable) rather than
 *   0x3B (Torrent-hub). It is better to let the clients to identअगरy
 *   who owns the event.
 */

अटल irqवापस_t ioei_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pseries_io_event *event;
	पूर्णांक rtas_rc;

	क्रम (;;) अणु
		rtas_rc = rtas_call(ioei_check_exception_token, 6, 1, शून्य,
				    RTAS_VECTOR_EXTERNAL_INTERRUPT,
				    virq_to_hw(irq),
				    RTAS_IO_EVENTS, 1 /* Time Critical */,
				    __pa(ioei_rtas_buf),
				    RTAS_DATA_BUF_SIZE);
		अगर (rtas_rc != 0)
			अवरोध;

		event = ioei_find_event((काष्ठा rtas_error_log *)ioei_rtas_buf);
		अगर (!event)
			जारी;

		atomic_notअगरier_call_chain(&pseries_ioei_notअगरier_list,
					   0, event);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init ioei_init(व्योम)
अणु
	काष्ठा device_node *np;

	ioei_check_exception_token = rtas_token("check-exception");
	अगर (ioei_check_exception_token == RTAS_UNKNOWN_SERVICE)
		वापस -ENODEV;

	np = of_find_node_by_path("/event-sources/ibm,io-events");
	अगर (np) अणु
		request_event_sources_irqs(np, ioei_पूर्णांकerrupt, "IO_EVENT");
		pr_info("IBM I/O event interrupts enabled\n");
		of_node_put(np);
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण
machine_subsys_initcall(pseries, ioei_init);

