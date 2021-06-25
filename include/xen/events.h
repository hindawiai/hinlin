<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _XEN_EVENTS_H
#घोषणा _XEN_EVENTS_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#अगर_घोषित CONFIG_PCI_MSI
#समावेश <linux/msi.h>
#पूर्ण_अगर

#समावेश <xen/पूर्णांकerface/event_channel.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/events.h>

काष्ठा xenbus_device;

अचिन्हित xen_evtchn_nr_channels(व्योम);

पूर्णांक bind_evtchn_to_irq(evtchn_port_t evtchn);
पूर्णांक bind_evtchn_to_irqhandler(evtchn_port_t evtchn,
			      irq_handler_t handler,
			      अचिन्हित दीर्घ irqflags, स्थिर अक्षर *devname,
			      व्योम *dev_id);
पूर्णांक bind_evtchn_to_irqhandler_lateeoi(evtchn_port_t evtchn,
			      irq_handler_t handler,
			      अचिन्हित दीर्घ irqflags, स्थिर अक्षर *devname,
			      व्योम *dev_id);
पूर्णांक bind_virq_to_irq(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक cpu, bool percpu);
पूर्णांक bind_virq_to_irqhandler(अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक cpu,
			    irq_handler_t handler,
			    अचिन्हित दीर्घ irqflags, स्थिर अक्षर *devname,
			    व्योम *dev_id);
पूर्णांक bind_ipi_to_irqhandler(क्रमागत ipi_vector ipi,
			   अचिन्हित पूर्णांक cpu,
			   irq_handler_t handler,
			   अचिन्हित दीर्घ irqflags,
			   स्थिर अक्षर *devname,
			   व्योम *dev_id);
पूर्णांक bind_पूर्णांकerकरोमुख्य_evtchn_to_irq_lateeoi(काष्ठा xenbus_device *dev,
					   evtchn_port_t remote_port);
पूर्णांक bind_पूर्णांकerकरोमुख्य_evtchn_to_irqhandler_lateeoi(काष्ठा xenbus_device *dev,
						  evtchn_port_t remote_port,
						  irq_handler_t handler,
						  अचिन्हित दीर्घ irqflags,
						  स्थिर अक्षर *devname,
						  व्योम *dev_id);

/*
 * Common unbind function क्रम all event sources. Takes IRQ to unbind from.
 * Automatically बंदs the underlying event channel (even क्रम bindings
 * made with bind_evtchn_to_irqhandler()).
 */
व्योम unbind_from_irqhandler(अचिन्हित पूर्णांक irq, व्योम *dev_id);

/*
 * Send late EOI क्रम an IRQ bound to an event channel via one of the *_lateeoi
 * functions above.
 */
व्योम xen_irq_lateeoi(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक eoi_flags);
/* Signal an event was spurious, i.e. there was no action resulting from it. */
#घोषणा XEN_EOI_FLAG_SPURIOUS	0x00000001

#घोषणा XEN_IRQ_PRIORITY_MAX     EVTCHN_FIFO_PRIORITY_MAX
#घोषणा XEN_IRQ_PRIORITY_DEFAULT EVTCHN_FIFO_PRIORITY_DEFAULT
#घोषणा XEN_IRQ_PRIORITY_MIN     EVTCHN_FIFO_PRIORITY_MIN
पूर्णांक xen_set_irq_priority(अचिन्हित irq, अचिन्हित priority);

/*
 * Allow extra references to event channels exposed to userspace by evtchn
 */
पूर्णांक evtchn_make_refcounted(evtchn_port_t evtchn);
पूर्णांक evtchn_get(evtchn_port_t evtchn);
व्योम evtchn_put(evtchn_port_t evtchn);

व्योम xen_send_IPI_one(अचिन्हित पूर्णांक cpu, क्रमागत ipi_vector vector);
व्योम rebind_evtchn_irq(evtchn_port_t evtchn, पूर्णांक irq);
पूर्णांक xen_set_affinity_evtchn(काष्ठा irq_desc *desc, अचिन्हित पूर्णांक tcpu);

अटल अंतरभूत व्योम notअगरy_remote_via_evtchn(evtchn_port_t port)
अणु
	काष्ठा evtchn_send send = अणु .port = port पूर्ण;
	(व्योम)HYPERVISOR_event_channel_op(EVTCHNOP_send, &send);
पूर्ण

व्योम notअगरy_remote_via_irq(पूर्णांक irq);

व्योम xen_irq_resume(व्योम);

/* Clear an irq's pending state, in preparation क्रम polling on it */
व्योम xen_clear_irq_pending(पूर्णांक irq);
व्योम xen_set_irq_pending(पूर्णांक irq);
bool xen_test_irq_pending(पूर्णांक irq);

/* Poll रुकोing क्रम an irq to become pending.  In the usual हाल, the
   irq will be disabled so it won't deliver an पूर्णांकerrupt. */
व्योम xen_poll_irq(पूर्णांक irq);

/* Poll रुकोing क्रम an irq to become pending with a समयout.  In the usual हाल,
 * the irq will be disabled so it won't deliver an पूर्णांकerrupt. */
व्योम xen_poll_irq_समयout(पूर्णांक irq, u64 समयout);

/* Determine the IRQ which is bound to an event channel */
अचिन्हित पूर्णांक irq_from_evtchn(evtchn_port_t evtchn);
पूर्णांक irq_from_virq(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक virq);
evtchn_port_t evtchn_from_irq(अचिन्हित irq);

पूर्णांक xen_set_callback_via(uपूर्णांक64_t via);
व्योम xen_evtchn_करो_upcall(काष्ठा pt_regs *regs);
व्योम xen_hvm_evtchn_करो_upcall(व्योम);

/* Bind a pirq क्रम a physical पूर्णांकerrupt to an irq. */
पूर्णांक xen_bind_pirq_gsi_to_irq(अचिन्हित gsi,
			     अचिन्हित pirq, पूर्णांक shareable, अक्षर *name);

#अगर_घोषित CONFIG_PCI_MSI
/* Allocate a pirq क्रम a MSI style physical पूर्णांकerrupt. */
पूर्णांक xen_allocate_pirq_msi(काष्ठा pci_dev *dev, काष्ठा msi_desc *msidesc);
/* Bind an PSI pirq to an irq. */
पूर्णांक xen_bind_pirq_msi_to_irq(काष्ठा pci_dev *dev, काष्ठा msi_desc *msidesc,
			     पूर्णांक pirq, पूर्णांक nvec, स्थिर अक्षर *name, करोmid_t करोmid);
#पूर्ण_अगर

/* De-allocates the above mentioned physical पूर्णांकerrupt. */
पूर्णांक xen_destroy_irq(पूर्णांक irq);

/* Return irq from pirq */
पूर्णांक xen_irq_from_pirq(अचिन्हित pirq);

/* Return the pirq allocated to the irq. */
पूर्णांक xen_pirq_from_irq(अचिन्हित irq);

/* Return the irq allocated to the gsi */
पूर्णांक xen_irq_from_gsi(अचिन्हित gsi);

/* Determine whether to ignore this IRQ अगर it is passed to a guest. */
पूर्णांक xen_test_irq_shared(पूर्णांक irq);

/* initialize Xen IRQ subप्रणाली */
व्योम xen_init_IRQ(व्योम);
#पूर्ण_अगर	/* _XEN_EVENTS_H */
