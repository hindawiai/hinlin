<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic Event Device क्रम ACPI.
 *
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 *
 * Generic Event Device allows platक्रमms to handle पूर्णांकerrupts in ACPI
 * ASL statements. It follows very similar to  _EVT method approach
 * from GPIO events. All पूर्णांकerrupts are listed in _CRS and the handler
 * is written in _EVT method. Here is an example.
 *
 * Device (GED0)
 * अणु
 *
 *     Name (_HID, "ACPI0013")
 *     Name (_UID, 0)
 *     Method (_CRS, 0x0, Serialized)
 *     अणु
 *		Name (RBUF, ResourceTemplate ()
 *		अणु
 *		Interrupt(ResourceConsumer, Edge, ActiveHigh, Shared, , , )
 *		अणु123पूर्ण
 *		पूर्ण
 *     पूर्ण)
 *
 *     Method (_EVT, 1) अणु
 *             अगर (Lequal(123, Arg0))
 *             अणु
 *             पूर्ण
 *     पूर्ण
 * पूर्ण
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>

#घोषणा MODULE_NAME	"acpi-ged"

काष्ठा acpi_ged_device अणु
	काष्ठा device *dev;
	काष्ठा list_head event_list;
पूर्ण;

काष्ठा acpi_ged_event अणु
	काष्ठा list_head node;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक gsi;
	अचिन्हित पूर्णांक irq;
	acpi_handle handle;
पूर्ण;

अटल irqवापस_t acpi_ged_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा acpi_ged_event *event = data;
	acpi_status acpi_ret;

	acpi_ret = acpi_execute_simple_method(event->handle, शून्य, event->gsi);
	अगर (ACPI_FAILURE(acpi_ret))
		dev_err_once(event->dev, "IRQ method execution failed\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल acpi_status acpi_ged_request_पूर्णांकerrupt(काष्ठा acpi_resource *ares,
					      व्योम *context)
अणु
	काष्ठा acpi_ged_event *event;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक gsi;
	अचिन्हित पूर्णांक irqflags = IRQF_ONESHOT;
	काष्ठा acpi_ged_device *geddev = context;
	काष्ठा device *dev = geddev->dev;
	acpi_handle handle = ACPI_HANDLE(dev);
	acpi_handle evt_handle;
	काष्ठा resource r;
	काष्ठा acpi_resource_irq *p = &ares->data.irq;
	काष्ठा acpi_resource_extended_irq *pext = &ares->data.extended_irq;
	अक्षर ev_name[5];
	u8 trigger;

	अगर (ares->type == ACPI_RESOURCE_TYPE_END_TAG)
		वापस AE_OK;

	अगर (!acpi_dev_resource_पूर्णांकerrupt(ares, 0, &r)) अणु
		dev_err(dev, "unable to parse IRQ resource\n");
		वापस AE_ERROR;
	पूर्ण
	अगर (ares->type == ACPI_RESOURCE_TYPE_IRQ) अणु
		gsi = p->पूर्णांकerrupts[0];
		trigger = p->triggering;
	पूर्ण अन्यथा अणु
		gsi = pext->पूर्णांकerrupts[0];
		trigger = pext->triggering;
	पूर्ण

	irq = r.start;

	चयन (gsi) अणु
	हाल 0 ... 255:
		प्र_लिखो(ev_name, "_%c%02X",
			trigger == ACPI_EDGE_SENSITIVE ? 'E' : 'L', gsi);

		अगर (ACPI_SUCCESS(acpi_get_handle(handle, ev_name, &evt_handle)))
			अवरोध;
		fallthrough;
	शेष:
		अगर (ACPI_SUCCESS(acpi_get_handle(handle, "_EVT", &evt_handle)))
			अवरोध;

		dev_err(dev, "cannot locate _EVT method\n");
		वापस AE_ERROR;
	पूर्ण

	event = devm_kzalloc(dev, माप(*event), GFP_KERNEL);
	अगर (!event)
		वापस AE_ERROR;

	event->gsi = gsi;
	event->dev = dev;
	event->irq = irq;
	event->handle = evt_handle;

	अगर (r.flags & IORESOURCE_IRQ_SHAREABLE)
		irqflags |= IRQF_SHARED;

	अगर (request_thपढ़ोed_irq(irq, शून्य, acpi_ged_irq_handler,
				 irqflags, "ACPI:Ged", event)) अणु
		dev_err(dev, "failed to setup event handler for irq %u\n", irq);
		वापस AE_ERROR;
	पूर्ण

	dev_dbg(dev, "GED listening GSI %u @ IRQ %u\n", gsi, irq);
	list_add_tail(&event->node, &geddev->event_list);
	वापस AE_OK;
पूर्ण

अटल पूर्णांक ged_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा acpi_ged_device *geddev;
	acpi_status acpi_ret;

	geddev = devm_kzalloc(&pdev->dev, माप(*geddev), GFP_KERNEL);
	अगर (!geddev)
		वापस -ENOMEM;

	geddev->dev = &pdev->dev;
	INIT_LIST_HEAD(&geddev->event_list);
	acpi_ret = acpi_walk_resources(ACPI_HANDLE(&pdev->dev), "_CRS",
				       acpi_ged_request_पूर्णांकerrupt, geddev);
	अगर (ACPI_FAILURE(acpi_ret)) अणु
		dev_err(&pdev->dev, "unable to parse the _CRS record\n");
		वापस -EINVAL;
	पूर्ण
	platक्रमm_set_drvdata(pdev, geddev);

	वापस 0;
पूर्ण

अटल व्योम ged_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा acpi_ged_device *geddev = platक्रमm_get_drvdata(pdev);
	काष्ठा acpi_ged_event *event, *next;

	list_क्रम_each_entry_safe(event, next, &geddev->event_list, node) अणु
		मुक्त_irq(event->irq, event);
		list_del(&event->node);
		dev_dbg(geddev->dev, "GED releasing GSI %u @ IRQ %u\n",
			 event->gsi, event->irq);
	पूर्ण
पूर्ण

अटल पूर्णांक ged_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	ged_shutकरोwn(pdev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id ged_acpi_ids[] = अणु
	अणु"ACPI0013"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ged_driver = अणु
	.probe = ged_probe,
	.हटाओ = ged_हटाओ,
	.shutकरोwn = ged_shutकरोwn,
	.driver = अणु
		.name = MODULE_NAME,
		.acpi_match_table = ACPI_PTR(ged_acpi_ids),
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(ged_driver);
