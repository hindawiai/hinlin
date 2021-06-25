<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * xen-acpi-pad.c - Xen pad पूर्णांकerface
 *
 * Copyright (c) 2012, Intel Corporation.
 *    Author: Liu, Jinsong <jinsong.liu@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/acpi.h>
#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/version.h>
#समावेश <xen/xen-ops.h>
#समावेश <यंत्र/xen/hypercall.h>

#घोषणा ACPI_PROCESSOR_AGGREGATOR_CLASS	"acpi_pad"
#घोषणा ACPI_PROCESSOR_AGGREGATOR_DEVICE_NAME "Processor Aggregator"
#घोषणा ACPI_PROCESSOR_AGGREGATOR_NOTIFY 0x80
अटल DEFINE_MUTEX(xen_cpu_lock);

अटल पूर्णांक xen_acpi_pad_idle_cpus(अचिन्हित पूर्णांक idle_nums)
अणु
	काष्ठा xen_platक्रमm_op op;

	op.cmd = XENPF_core_parking;
	op.u.core_parking.type = XEN_CORE_PARKING_SET;
	op.u.core_parking.idle_nums = idle_nums;

	वापस HYPERVISOR_platक्रमm_op(&op);
पूर्ण

अटल पूर्णांक xen_acpi_pad_idle_cpus_num(व्योम)
अणु
	काष्ठा xen_platक्रमm_op op;

	op.cmd = XENPF_core_parking;
	op.u.core_parking.type = XEN_CORE_PARKING_GET;

	वापस HYPERVISOR_platक्रमm_op(&op)
	       ?: op.u.core_parking.idle_nums;
पूर्ण

/*
 * Query firmware how many CPUs should be idle
 * वापस -1 on failure
 */
अटल पूर्णांक acpi_pad_pur(acpi_handle handle)
अणु
	काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object *package;
	पूर्णांक num = -1;

	अगर (ACPI_FAILURE(acpi_evaluate_object(handle, "_PUR", शून्य, &buffer)))
		वापस num;

	अगर (!buffer.length || !buffer.poपूर्णांकer)
		वापस num;

	package = buffer.poपूर्णांकer;

	अगर (package->type == ACPI_TYPE_PACKAGE &&
		package->package.count == 2 &&
		package->package.elements[0].पूर्णांकeger.value == 1) /* rev 1 */
		num = package->package.elements[1].पूर्णांकeger.value;

	kमुक्त(buffer.poपूर्णांकer);
	वापस num;
पूर्ण

अटल व्योम acpi_pad_handle_notअगरy(acpi_handle handle)
अणु
	पूर्णांक idle_nums;
	काष्ठा acpi_buffer param = अणु
		.length = 4,
		.poपूर्णांकer = (व्योम *)&idle_nums,
	पूर्ण;


	mutex_lock(&xen_cpu_lock);
	idle_nums = acpi_pad_pur(handle);
	अगर (idle_nums < 0) अणु
		mutex_unlock(&xen_cpu_lock);
		वापस;
	पूर्ण

	idle_nums = xen_acpi_pad_idle_cpus(idle_nums)
		    ?: xen_acpi_pad_idle_cpus_num();
	अगर (idle_nums >= 0)
		acpi_evaluate_ost(handle, ACPI_PROCESSOR_AGGREGATOR_NOTIFY,
				  0, &param);
	mutex_unlock(&xen_cpu_lock);
पूर्ण

अटल व्योम acpi_pad_notअगरy(acpi_handle handle, u32 event,
	व्योम *data)
अणु
	चयन (event) अणु
	हाल ACPI_PROCESSOR_AGGREGATOR_NOTIFY:
		acpi_pad_handle_notअगरy(handle);
		अवरोध;
	शेष:
		pr_warn("Unsupported event [0x%x]\n", event);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_pad_add(काष्ठा acpi_device *device)
अणु
	acpi_status status;

	म_नकल(acpi_device_name(device), ACPI_PROCESSOR_AGGREGATOR_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_PROCESSOR_AGGREGATOR_CLASS);

	status = acpi_install_notअगरy_handler(device->handle,
		ACPI_DEVICE_NOTIFY, acpi_pad_notअगरy, device);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_pad_हटाओ(काष्ठा acpi_device *device)
अणु
	mutex_lock(&xen_cpu_lock);
	xen_acpi_pad_idle_cpus(0);
	mutex_unlock(&xen_cpu_lock);

	acpi_हटाओ_notअगरy_handler(device->handle,
		ACPI_DEVICE_NOTIFY, acpi_pad_notअगरy);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id pad_device_ids[] = अणु
	अणु"ACPI000C", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_driver acpi_pad_driver = अणु
	.name = "processor_aggregator",
	.class = ACPI_PROCESSOR_AGGREGATOR_CLASS,
	.ids = pad_device_ids,
	.ops = अणु
		.add = acpi_pad_add,
		.हटाओ = acpi_pad_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init xen_acpi_pad_init(व्योम)
अणु
	/* Only DOM0 is responsible क्रम Xen acpi pad */
	अगर (!xen_initial_करोमुख्य())
		वापस -ENODEV;

	/* Only Xen4.2 or later support Xen acpi pad */
	अगर (!xen_running_on_version_or_later(4, 2))
		वापस -ENODEV;

	वापस acpi_bus_रेजिस्टर_driver(&acpi_pad_driver);
पूर्ण
subsys_initcall(xen_acpi_pad_init);
