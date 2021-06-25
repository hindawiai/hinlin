<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम OLPC XO-1.5 System Control Interrupts (SCI)
 *
 * Copyright (C) 2009-2010 One Laptop per Child
 */

#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/olpc-ec.h>

#समावेश <linux/acpi.h>
#समावेश <यंत्र/olpc.h>

#घोषणा DRV_NAME			"olpc-xo15-sci"
#घोषणा PFX				DRV_NAME ": "
#घोषणा XO15_SCI_CLASS			DRV_NAME
#घोषणा XO15_SCI_DEVICE_NAME		"OLPC XO-1.5 SCI"

अटल अचिन्हित दीर्घ			xo15_sci_gpe;
अटल bool				lid_wake_on_बंद;

/*
 * The normal ACPI LID wakeup behavior is wake-on-खोलो, but not
 * wake-on-बंद. This is implemented as standard by the XO-1.5 DSDT.
 *
 * We provide here a sysfs attribute that will additionally enable
 * wake-on-बंद behavior. This is useful (e.g.) when we opportunistically
 * suspend with the display running; अगर the lid is then बंदd, we want to
 * wake up to turn the display off.
 *
 * This is controlled through a custom method in the XO-1.5 DSDT.
 */
अटल पूर्णांक set_lid_wake_behavior(bool wake_on_बंद)
अणु
	acpi_status status;

	status = acpi_execute_simple_method(शून्य, "\\_SB.PCI0.LID.LIDW", wake_on_बंद);
	अगर (ACPI_FAILURE(status)) अणु
		pr_warn(PFX "failed to set lid behavior\n");
		वापस 1;
	पूर्ण

	lid_wake_on_बंद = wake_on_बंद;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
lid_wake_on_बंद_show(काष्ठा kobject *s, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", lid_wake_on_बंद);
पूर्ण

अटल sमाप_प्रकार lid_wake_on_बंद_store(काष्ठा kobject *s,
				       काष्ठा kobj_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	अचिन्हित पूर्णांक val;

	अगर (माला_पूछो(buf, "%u", &val) != 1)
		वापस -EINVAL;

	set_lid_wake_behavior(!!val);

	वापस n;
पूर्ण

अटल काष्ठा kobj_attribute lid_wake_on_बंद_attr =
	__ATTR(lid_wake_on_बंद, 0644,
	       lid_wake_on_बंद_show,
	       lid_wake_on_बंद_store);

अटल व्योम battery_status_changed(व्योम)
अणु
	काष्ठा घातer_supply *psy = घातer_supply_get_by_name("olpc_battery");

	अगर (psy) अणु
		घातer_supply_changed(psy);
		घातer_supply_put(psy);
	पूर्ण
पूर्ण

अटल व्योम ac_status_changed(व्योम)
अणु
	काष्ठा घातer_supply *psy = घातer_supply_get_by_name("olpc_ac");

	अगर (psy) अणु
		घातer_supply_changed(psy);
		घातer_supply_put(psy);
	पूर्ण
पूर्ण

अटल व्योम process_sci_queue(व्योम)
अणु
	u16 data;
	पूर्णांक r;

	करो अणु
		r = olpc_ec_sci_query(&data);
		अगर (r || !data)
			अवरोध;

		pr_debug(PFX "SCI 0x%x received\n", data);

		चयन (data) अणु
		हाल EC_SCI_SRC_BATERR:
		हाल EC_SCI_SRC_BATSOC:
		हाल EC_SCI_SRC_BATTERY:
		हाल EC_SCI_SRC_BATCRIT:
			battery_status_changed();
			अवरोध;
		हाल EC_SCI_SRC_ACPWR:
			ac_status_changed();
			अवरोध;
		पूर्ण
	पूर्ण जबतक (data);

	अगर (r)
		pr_err(PFX "Failed to clear SCI queue");
पूर्ण

अटल व्योम process_sci_queue_work(काष्ठा work_काष्ठा *work)
अणु
	process_sci_queue();
पूर्ण

अटल DECLARE_WORK(sci_work, process_sci_queue_work);

अटल u32 xo15_sci_gpe_handler(acpi_handle gpe_device, u32 gpe, व्योम *context)
अणु
	schedule_work(&sci_work);
	वापस ACPI_INTERRUPT_HANDLED | ACPI_REENABLE_GPE;
पूर्ण

अटल पूर्णांक xo15_sci_add(काष्ठा acpi_device *device)
अणु
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	acpi_status status;
	पूर्णांक r;

	अगर (!device)
		वापस -EINVAL;

	म_नकल(acpi_device_name(device), XO15_SCI_DEVICE_NAME);
	म_नकल(acpi_device_class(device), XO15_SCI_CLASS);

	/* Get GPE bit assignment (EC events). */
	status = acpi_evaluate_पूर्णांकeger(device->handle, "_GPE", शून्य, &पंचांगp);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;

	xo15_sci_gpe = पंचांगp;
	status = acpi_install_gpe_handler(शून्य, xo15_sci_gpe,
					  ACPI_GPE_EDGE_TRIGGERED,
					  xo15_sci_gpe_handler, device);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	dev_info(&device->dev, "Initialized, GPE = 0x%lx\n", xo15_sci_gpe);

	r = sysfs_create_file(&device->dev.kobj, &lid_wake_on_बंद_attr.attr);
	अगर (r)
		जाओ err_sysfs;

	/* Flush queue, and enable all SCI events */
	process_sci_queue();
	olpc_ec_mask_ग_लिखो(EC_SCI_SRC_ALL);

	acpi_enable_gpe(शून्य, xo15_sci_gpe);

	/* Enable wake-on-EC */
	अगर (device->wakeup.flags.valid)
		device_init_wakeup(&device->dev, true);

	वापस 0;

err_sysfs:
	acpi_हटाओ_gpe_handler(शून्य, xo15_sci_gpe, xo15_sci_gpe_handler);
	cancel_work_sync(&sci_work);
	वापस r;
पूर्ण

अटल पूर्णांक xo15_sci_हटाओ(काष्ठा acpi_device *device)
अणु
	acpi_disable_gpe(शून्य, xo15_sci_gpe);
	acpi_हटाओ_gpe_handler(शून्य, xo15_sci_gpe, xo15_sci_gpe_handler);
	cancel_work_sync(&sci_work);
	sysfs_हटाओ_file(&device->dev.kobj, &lid_wake_on_बंद_attr.attr);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक xo15_sci_resume(काष्ठा device *dev)
अणु
	/* Enable all EC events */
	olpc_ec_mask_ग_लिखो(EC_SCI_SRC_ALL);

	/* Power/battery status might have changed */
	battery_status_changed();
	ac_status_changed();

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(xo15_sci_pm, शून्य, xo15_sci_resume);

अटल स्थिर काष्ठा acpi_device_id xo15_sci_device_ids[] = अणु
	अणु"XO15EC", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_driver xo15_sci_drv = अणु
	.name = DRV_NAME,
	.class = XO15_SCI_CLASS,
	.ids = xo15_sci_device_ids,
	.ops = अणु
		.add = xo15_sci_add,
		.हटाओ = xo15_sci_हटाओ,
	पूर्ण,
	.drv.pm = &xo15_sci_pm,
पूर्ण;

अटल पूर्णांक __init xo15_sci_init(व्योम)
अणु
	वापस acpi_bus_रेजिस्टर_driver(&xo15_sci_drv);
पूर्ण
device_initcall(xo15_sci_init);
