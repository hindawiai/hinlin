<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file implements an irqchip क्रम OPAL events. Whenever there is
 * an पूर्णांकerrupt that is handled by OPAL we get passed a list of events
 * that Linux needs to करो something about. These basically look like
 * पूर्णांकerrupts to Linux so we implement an irqchip to handle them.
 *
 * Copyright Alistair Popple, IBM Corporation 2014.
 */
#समावेश <linux/bitops.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/opal.h>

#समावेश "powernv.h"

/* Maximum number of events supported by OPAL firmware */
#घोषणा MAX_NUM_EVENTS 64

काष्ठा opal_event_irqchip अणु
	काष्ठा irq_chip irqchip;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित दीर्घ mask;
पूर्ण;
अटल काष्ठा opal_event_irqchip opal_event_irqchip;
अटल u64 last_outstanding_events;
अटल पूर्णांक opal_irq_count;
अटल काष्ठा resource *opal_irqs;

व्योम opal_handle_events(व्योम)
अणु
	__be64 events = 0;
	u64 e;

	e = READ_ONCE(last_outstanding_events) & opal_event_irqchip.mask;
again:
	जबतक (e) अणु
		पूर्णांक virq, hwirq;

		hwirq = fls64(e) - 1;
		e &= ~BIT_ULL(hwirq);

		local_irq_disable();
		virq = irq_find_mapping(opal_event_irqchip.करोमुख्य, hwirq);
		अगर (virq) अणु
			irq_enter();
			generic_handle_irq(virq);
			irq_निकास();
		पूर्ण
		local_irq_enable();

		cond_resched();
	पूर्ण
	last_outstanding_events = 0;
	अगर (opal_poll_events(&events) != OPAL_SUCCESS)
		वापस;
	e = be64_to_cpu(events) & opal_event_irqchip.mask;
	अगर (e)
		जाओ again;
पूर्ण

bool opal_have_pending_events(व्योम)
अणु
	अगर (last_outstanding_events & opal_event_irqchip.mask)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम opal_event_mask(काष्ठा irq_data *d)
अणु
	clear_bit(d->hwirq, &opal_event_irqchip.mask);
पूर्ण

अटल व्योम opal_event_unmask(काष्ठा irq_data *d)
अणु
	set_bit(d->hwirq, &opal_event_irqchip.mask);
	अगर (opal_have_pending_events())
		opal_wake_poller();
पूर्ण

अटल पूर्णांक opal_event_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	/*
	 * For now we only support level triggered events. The irq
	 * handler will be called continuously until the event has
	 * been cleared in OPAL.
	 */
	अगर (flow_type != IRQ_TYPE_LEVEL_HIGH)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा opal_event_irqchip opal_event_irqchip = अणु
	.irqchip = अणु
		.name = "OPAL EVT",
		.irq_mask = opal_event_mask,
		.irq_unmask = opal_event_unmask,
		.irq_set_type = opal_event_set_type,
	पूर्ण,
	.mask = 0,
पूर्ण;

अटल पूर्णांक opal_event_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			irq_hw_number_t hwirq)
अणु
	irq_set_chip_data(irq, &opal_event_irqchip);
	irq_set_chip_and_handler(irq, &opal_event_irqchip.irqchip,
				handle_level_irq);

	वापस 0;
पूर्ण

अटल irqवापस_t opal_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	__be64 events;

	opal_handle_पूर्णांकerrupt(virq_to_hw(irq), &events);
	last_outstanding_events = be64_to_cpu(events);
	अगर (opal_have_pending_events())
		opal_wake_poller();

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक opal_event_match(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *node,
			    क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	वापस irq_करोमुख्य_get_of_node(h) == node;
पूर्ण

अटल पूर्णांक opal_event_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *np,
			   स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			   irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_flags)
अणु
	*out_hwirq = पूर्णांकspec[0];
	*out_flags = IRQ_TYPE_LEVEL_HIGH;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops opal_event_करोमुख्य_ops = अणु
	.match	= opal_event_match,
	.map	= opal_event_map,
	.xlate	= opal_event_xlate,
पूर्ण;

व्योम opal_event_shutकरोwn(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	/* First मुक्त पूर्णांकerrupts, which will also mask them */
	क्रम (i = 0; i < opal_irq_count; i++) अणु
		अगर (!opal_irqs || !opal_irqs[i].start)
			जारी;

		अगर (in_पूर्णांकerrupt() || irqs_disabled())
			disable_irq_nosync(opal_irqs[i].start);
		अन्यथा
			मुक्त_irq(opal_irqs[i].start, शून्य);

		opal_irqs[i].start = 0;
	पूर्ण
पूर्ण

पूर्णांक __init opal_event_init(व्योम)
अणु
	काष्ठा device_node *dn, *opal_node;
	bool old_style = false;
	पूर्णांक i, rc = 0;

	opal_node = of_find_node_by_path("/ibm,opal");
	अगर (!opal_node) अणु
		pr_warn("opal: Node not found\n");
		वापस -ENODEV;
	पूर्ण

	/* If dn is शून्य it means the करोमुख्य won't be linked to a DT
	 * node so thereक्रमe irq_of_parse_and_map(...) wont work. But
	 * that shouldn't be problem because if we're running a
	 * version of skiboot that करोesn't have the dn then the
	 * devices won't have the correct properties and will have to
	 * fall back to the legacy method (opal_event_request(...))
	 * anyway. */
	dn = of_find_compatible_node(शून्य, शून्य, "ibm,opal-event");
	opal_event_irqchip.करोमुख्य = irq_करोमुख्य_add_linear(dn, MAX_NUM_EVENTS,
				&opal_event_करोमुख्य_ops, &opal_event_irqchip);
	of_node_put(dn);
	अगर (!opal_event_irqchip.करोमुख्य) अणु
		pr_warn("opal: Unable to create irq domain\n");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Look क्रम new-style (standard) "interrupts" property */
	opal_irq_count = of_irq_count(opal_node);

	/* Absent ? Look क्रम the old one */
	अगर (opal_irq_count < 1) अणु
		/* Get opal-पूर्णांकerrupts property and names अगर present */
		rc = of_property_count_u32_elems(opal_node, "opal-interrupts");
		अगर (rc > 0)
			opal_irq_count = rc;
		old_style = true;
	पूर्ण

	/* No पूर्णांकerrupts ? Bail out */
	अगर (!opal_irq_count)
		जाओ out;

	pr_debug("OPAL: Found %d interrupts reserved for OPAL using %s scheme\n",
		 opal_irq_count, old_style ? "old" : "new");

	/* Allocate an IRQ resources array */
	opal_irqs = kसुस्मृति(opal_irq_count, माप(काष्ठा resource), GFP_KERNEL);
	अगर (WARN_ON(!opal_irqs)) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Build the resources array */
	अगर (old_style) अणु
		/* Old style "opal-interrupts" property */
		क्रम (i = 0; i < opal_irq_count; i++) अणु
			काष्ठा resource *r = &opal_irqs[i];
			स्थिर अक्षर *name = शून्य;
			u32 hw_irq;
			पूर्णांक virq;

			rc = of_property_पढ़ो_u32_index(opal_node, "opal-interrupts",
							i, &hw_irq);
			अगर (WARN_ON(rc < 0)) अणु
				opal_irq_count = i;
				अवरोध;
			पूर्ण
			of_property_पढ़ो_string_index(opal_node, "opal-interrupts-names",
						      i, &name);
			virq = irq_create_mapping(शून्य, hw_irq);
			अगर (!virq) अणु
				pr_warn("Failed to map OPAL irq 0x%x\n", hw_irq);
				जारी;
			पूर्ण
			r->start = r->end = virq;
			r->flags = IORESOURCE_IRQ | IRQ_TYPE_LEVEL_LOW;
			r->name = name;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* new style standard "interrupts" property */
		rc = of_irq_to_resource_table(opal_node, opal_irqs, opal_irq_count);
		अगर (WARN_ON(rc < 0)) अणु
			opal_irq_count = 0;
			kमुक्त(opal_irqs);
			जाओ out;
		पूर्ण
		अगर (WARN_ON(rc < opal_irq_count))
			opal_irq_count = rc;
	पूर्ण

	/* Install पूर्णांकerrupt handlers */
	क्रम (i = 0; i < opal_irq_count; i++) अणु
		काष्ठा resource *r = &opal_irqs[i];
		स्थिर अक्षर *name;

		/* Prefix name */
		अगर (r->name && म_माप(r->name))
			name = kaप्र_लिखो(GFP_KERNEL, "opal-%s", r->name);
		अन्यथा
			name = kaप्र_लिखो(GFP_KERNEL, "opal");

		/* Install पूर्णांकerrupt handler */
		rc = request_irq(r->start, opal_पूर्णांकerrupt, r->flags & IRQD_TRIGGER_MASK,
				 name, शून्य);
		अगर (rc) अणु
			pr_warn("Error %d requesting OPAL irq %d\n", rc, (पूर्णांक)r->start);
			जारी;
		पूर्ण
	पूर्ण
	rc = 0;
 out:
	of_node_put(opal_node);
	वापस rc;
पूर्ण
machine_arch_initcall(घातernv, opal_event_init);

/**
 * opal_event_request(अचिन्हित पूर्णांक opal_event_nr) - Request an event
 * @opal_event_nr: the opal event number to request
 *
 * This routine can be used to find the linux virq number which can
 * then be passed to request_irq to assign a handler क्रम a particular
 * opal event. This should only be used by legacy devices which करोn't
 * have proper device tree bindings. Most devices should use
 * irq_of_parse_and_map() instead.
 */
पूर्णांक opal_event_request(अचिन्हित पूर्णांक opal_event_nr)
अणु
	अगर (WARN_ON_ONCE(!opal_event_irqchip.करोमुख्य))
		वापस 0;

	वापस irq_create_mapping(opal_event_irqchip.करोमुख्य, opal_event_nr);
पूर्ण
EXPORT_SYMBOL(opal_event_request);
