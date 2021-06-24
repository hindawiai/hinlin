<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Dell Airplane Mode Switch driver
    Copyright (C) 2014-2015  Pali Rohथँr <pali@kernel.org>

*/

#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/input.h>

#समावेश "dell-rbtn.h"

क्रमागत rbtn_type अणु
	RBTN_UNKNOWN,
	RBTN_TOGGLE,
	RBTN_SLIDER,
पूर्ण;

काष्ठा rbtn_data अणु
	क्रमागत rbtn_type type;
	काष्ठा rfसमाप्त *rfसमाप्त;
	काष्ठा input_dev *input_dev;
	bool suspended;
पूर्ण;


/*
 * acpi functions
 */

अटल क्रमागत rbtn_type rbtn_check(काष्ठा acpi_device *device)
अणु
	अचिन्हित दीर्घ दीर्घ output;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(device->handle, "CRBT", शून्य, &output);
	अगर (ACPI_FAILURE(status))
		वापस RBTN_UNKNOWN;

	चयन (output) अणु
	हाल 0:
	हाल 1:
		वापस RBTN_TOGGLE;
	हाल 2:
	हाल 3:
		वापस RBTN_SLIDER;
	शेष:
		वापस RBTN_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक rbtn_get(काष्ठा acpi_device *device)
अणु
	अचिन्हित दीर्घ दीर्घ output;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(device->handle, "GRBT", शून्य, &output);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;

	वापस !output;
पूर्ण

अटल पूर्णांक rbtn_acquire(काष्ठा acpi_device *device, bool enable)
अणु
	काष्ठा acpi_object_list input;
	जोड़ acpi_object param;
	acpi_status status;

	param.type = ACPI_TYPE_INTEGER;
	param.पूर्णांकeger.value = enable;
	input.count = 1;
	input.poपूर्णांकer = &param;

	status = acpi_evaluate_object(device->handle, "ARBT", &input, शून्य);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;

	वापस 0;
पूर्ण


/*
 * rfसमाप्त device
 */

अटल व्योम rbtn_rfसमाप्त_query(काष्ठा rfसमाप्त *rfसमाप्त, व्योम *data)
अणु
	काष्ठा acpi_device *device = data;
	पूर्णांक state;

	state = rbtn_get(device);
	अगर (state < 0)
		वापस;

	rfसमाप्त_set_states(rfसमाप्त, state, state);
पूर्ण

अटल पूर्णांक rbtn_rfसमाप्त_set_block(व्योम *data, bool blocked)
अणु
	/* NOTE: setting soft rfसमाप्त state is not supported */
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops rbtn_ops = अणु
	.query = rbtn_rfसमाप्त_query,
	.set_block = rbtn_rfसमाप्त_set_block,
पूर्ण;

अटल पूर्णांक rbtn_rfसमाप्त_init(काष्ठा acpi_device *device)
अणु
	काष्ठा rbtn_data *rbtn_data = device->driver_data;
	पूर्णांक ret;

	अगर (rbtn_data->rfसमाप्त)
		वापस 0;

	/*
	 * NOTE: rbtn controls all radio devices, not only WLAN
	 *       but rfसमाप्त पूर्णांकerface करोes not support "ANY" type
	 *       so "WLAN" type is used
	 */
	rbtn_data->rfसमाप्त = rfसमाप्त_alloc("dell-rbtn", &device->dev,
					 RFKILL_TYPE_WLAN, &rbtn_ops, device);
	अगर (!rbtn_data->rfसमाप्त)
		वापस -ENOMEM;

	ret = rfसमाप्त_रेजिस्टर(rbtn_data->rfसमाप्त);
	अगर (ret) अणु
		rfसमाप्त_destroy(rbtn_data->rfसमाप्त);
		rbtn_data->rfसमाप्त = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rbtn_rfसमाप्त_निकास(काष्ठा acpi_device *device)
अणु
	काष्ठा rbtn_data *rbtn_data = device->driver_data;

	अगर (!rbtn_data->rfसमाप्त)
		वापस;

	rfसमाप्त_unरेजिस्टर(rbtn_data->rfसमाप्त);
	rfसमाप्त_destroy(rbtn_data->rfसमाप्त);
	rbtn_data->rfसमाप्त = शून्य;
पूर्ण

अटल व्योम rbtn_rfसमाप्त_event(काष्ठा acpi_device *device)
अणु
	काष्ठा rbtn_data *rbtn_data = device->driver_data;

	अगर (rbtn_data->rfसमाप्त)
		rbtn_rfसमाप्त_query(rbtn_data->rfसमाप्त, device);
पूर्ण


/*
 * input device
 */

अटल पूर्णांक rbtn_input_init(काष्ठा rbtn_data *rbtn_data)
अणु
	पूर्णांक ret;

	rbtn_data->input_dev = input_allocate_device();
	अगर (!rbtn_data->input_dev)
		वापस -ENOMEM;

	rbtn_data->input_dev->name = "DELL Wireless hotkeys";
	rbtn_data->input_dev->phys = "dellabce/input0";
	rbtn_data->input_dev->id.bustype = BUS_HOST;
	rbtn_data->input_dev->evbit[0] = BIT(EV_KEY);
	set_bit(KEY_RFKILL, rbtn_data->input_dev->keybit);

	ret = input_रेजिस्टर_device(rbtn_data->input_dev);
	अगर (ret) अणु
		input_मुक्त_device(rbtn_data->input_dev);
		rbtn_data->input_dev = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rbtn_input_निकास(काष्ठा rbtn_data *rbtn_data)
अणु
	input_unरेजिस्टर_device(rbtn_data->input_dev);
	rbtn_data->input_dev = शून्य;
पूर्ण

अटल व्योम rbtn_input_event(काष्ठा rbtn_data *rbtn_data)
अणु
	input_report_key(rbtn_data->input_dev, KEY_RFKILL, 1);
	input_sync(rbtn_data->input_dev);
	input_report_key(rbtn_data->input_dev, KEY_RFKILL, 0);
	input_sync(rbtn_data->input_dev);
पूर्ण


/*
 * acpi driver
 */

अटल पूर्णांक rbtn_add(काष्ठा acpi_device *device);
अटल पूर्णांक rbtn_हटाओ(काष्ठा acpi_device *device);
अटल व्योम rbtn_notअगरy(काष्ठा acpi_device *device, u32 event);

अटल स्थिर काष्ठा acpi_device_id rbtn_ids[] = अणु
	अणु "DELRBTN", 0 पूर्ण,
	अणु "DELLABCE", 0 पूर्ण,

	/*
	 * This driver can also handle the "DELLABC6" device that
	 * appears on the XPS 13 9350, but that device is disabled by
	 * the DSDT unless booted with acpi_osi="!Windows 2012"
	 * acpi_osi="!Windows 2013".
	 *
	 * According to Mario at Dell:
	 *
	 *  DELLABC6 is a custom पूर्णांकerface that was created solely to
	 *  have airplane mode support क्रम Winकरोws 7.  For Winकरोws 10
	 *  the proper पूर्णांकerface is to use that which is handled by
	 *  पूर्णांकel-hid. A OEM airplane mode driver is not used.
	 *
	 *  Since the kernel करोesn't identअगरy as Winकरोws 7 it would be
	 *  incorrect to करो attempt to use that पूर्णांकerface.
	 *
	 * Even अगर we override _OSI and bind to DELLABC6, we end up with
	 * inconsistent behavior in which userspace can get out of sync
	 * with the rfसमाप्त state as it conflicts with events from
	 * पूर्णांकel-hid.
	 *
	 * The upshot is that it is better to just ignore DELLABC6
	 * devices.
	 */

	अणु "", 0 पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम ACPI_SYSTEM_XFACE rbtn_clear_suspended_flag(व्योम *context)
अणु
	काष्ठा rbtn_data *rbtn_data = context;

	rbtn_data->suspended = false;
पूर्ण

अटल पूर्णांक rbtn_suspend(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *device = to_acpi_device(dev);
	काष्ठा rbtn_data *rbtn_data = acpi_driver_data(device);

	rbtn_data->suspended = true;

	वापस 0;
पूर्ण

अटल पूर्णांक rbtn_resume(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *device = to_acpi_device(dev);
	काष्ठा rbtn_data *rbtn_data = acpi_driver_data(device);
	acpi_status status;

	/*
	 * Upon resume, some BIOSes send an ACPI notअगरication thet triggers
	 * an unwanted input event. In order to ignore it, we use a flag
	 * that we set at suspend and clear once we have received the extra
	 * ACPI notअगरication. Since ACPI notअगरications are delivered
	 * asynchronously to drivers, we clear the flag from the workqueue
	 * used to deliver the notअगरications. This should be enough
	 * to have the flag cleared only after we received the extra
	 * notअगरication, अगर any.
	 */
	status = acpi_os_execute(OSL_NOTIFY_HANDLER,
			 rbtn_clear_suspended_flag, rbtn_data);
	अगर (ACPI_FAILURE(status))
		rbtn_clear_suspended_flag(rbtn_data);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(rbtn_pm_ops, rbtn_suspend, rbtn_resume);

अटल काष्ठा acpi_driver rbtn_driver = अणु
	.name = "dell-rbtn",
	.ids = rbtn_ids,
	.drv.pm = &rbtn_pm_ops,
	.ops = अणु
		.add = rbtn_add,
		.हटाओ = rbtn_हटाओ,
		.notअगरy = rbtn_notअगरy,
	पूर्ण,
	.owner = THIS_MODULE,
पूर्ण;


/*
 * notअगरier export functions
 */

अटल bool स्वतः_हटाओ_rfसमाप्त = true;

अटल ATOMIC_NOTIFIER_HEAD(rbtn_chain_head);

अटल पूर्णांक rbtn_inc_count(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा acpi_device *device = to_acpi_device(dev);
	काष्ठा rbtn_data *rbtn_data = device->driver_data;
	पूर्णांक *count = data;

	अगर (rbtn_data->type == RBTN_SLIDER)
		(*count)++;

	वापस 0;
पूर्ण

अटल पूर्णांक rbtn_चयन_dev(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा acpi_device *device = to_acpi_device(dev);
	काष्ठा rbtn_data *rbtn_data = device->driver_data;
	bool enable = data;

	अगर (rbtn_data->type != RBTN_SLIDER)
		वापस 0;

	अगर (enable)
		rbtn_rfसमाप्त_init(device);
	अन्यथा
		rbtn_rfसमाप्त_निकास(device);

	वापस 0;
पूर्ण

पूर्णांक dell_rbtn_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	bool first;
	पूर्णांक count;
	पूर्णांक ret;

	count = 0;
	ret = driver_क्रम_each_device(&rbtn_driver.drv, शून्य, &count,
				     rbtn_inc_count);
	अगर (ret || count == 0)
		वापस -ENODEV;

	first = !rbtn_chain_head.head;

	ret = atomic_notअगरier_chain_रेजिस्टर(&rbtn_chain_head, nb);
	अगर (ret != 0)
		वापस ret;

	अगर (स्वतः_हटाओ_rfसमाप्त && first)
		ret = driver_क्रम_each_device(&rbtn_driver.drv, शून्य,
					     (व्योम *)false, rbtn_चयन_dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dell_rbtn_notअगरier_रेजिस्टर);

पूर्णांक dell_rbtn_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक ret;

	ret = atomic_notअगरier_chain_unरेजिस्टर(&rbtn_chain_head, nb);
	अगर (ret != 0)
		वापस ret;

	अगर (स्वतः_हटाओ_rfसमाप्त && !rbtn_chain_head.head)
		ret = driver_क्रम_each_device(&rbtn_driver.drv, शून्य,
					     (व्योम *)true, rbtn_चयन_dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dell_rbtn_notअगरier_unरेजिस्टर);


/*
 * acpi driver functions
 */

अटल पूर्णांक rbtn_add(काष्ठा acpi_device *device)
अणु
	काष्ठा rbtn_data *rbtn_data;
	क्रमागत rbtn_type type;
	पूर्णांक ret = 0;

	type = rbtn_check(device);
	अगर (type == RBTN_UNKNOWN) अणु
		dev_info(&device->dev, "Unknown device type\n");
		वापस -EINVAL;
	पूर्ण

	ret = rbtn_acquire(device, true);
	अगर (ret < 0) अणु
		dev_err(&device->dev, "Cannot enable device\n");
		वापस ret;
	पूर्ण

	rbtn_data = devm_kzalloc(&device->dev, माप(*rbtn_data), GFP_KERNEL);
	अगर (!rbtn_data)
		वापस -ENOMEM;

	rbtn_data->type = type;
	device->driver_data = rbtn_data;

	चयन (rbtn_data->type) अणु
	हाल RBTN_TOGGLE:
		ret = rbtn_input_init(rbtn_data);
		अवरोध;
	हाल RBTN_SLIDER:
		अगर (स्वतः_हटाओ_rfसमाप्त && rbtn_chain_head.head)
			ret = 0;
		अन्यथा
			ret = rbtn_rfसमाप्त_init(device);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक rbtn_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा rbtn_data *rbtn_data = device->driver_data;

	चयन (rbtn_data->type) अणु
	हाल RBTN_TOGGLE:
		rbtn_input_निकास(rbtn_data);
		अवरोध;
	हाल RBTN_SLIDER:
		rbtn_rfसमाप्त_निकास(device);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rbtn_acquire(device, false);
	device->driver_data = शून्य;

	वापस 0;
पूर्ण

अटल व्योम rbtn_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा rbtn_data *rbtn_data = device->driver_data;

	/*
	 * Some BIOSes send a notअगरication at resume.
	 * Ignore it to prevent unwanted input events.
	 */
	अगर (rbtn_data->suspended) अणु
		dev_dbg(&device->dev, "ACPI notification ignored\n");
		वापस;
	पूर्ण

	अगर (event != 0x80) अणु
		dev_info(&device->dev, "Received unknown event (0x%x)\n",
			 event);
		वापस;
	पूर्ण

	चयन (rbtn_data->type) अणु
	हाल RBTN_TOGGLE:
		rbtn_input_event(rbtn_data);
		अवरोध;
	हाल RBTN_SLIDER:
		rbtn_rfसमाप्त_event(device);
		atomic_notअगरier_call_chain(&rbtn_chain_head, event, device);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण


/*
 * module functions
 */

module_acpi_driver(rbtn_driver);

module_param(स्वतः_हटाओ_rfसमाप्त, bool, 0444);

MODULE_PARM_DESC(स्वतः_हटाओ_rfसमाप्त, "Automatically remove rfkill devices when "
				     "other modules start receiving events "
				     "from this module and re-add them when "
				     "the last module stops receiving events "
				     "(default true)");
MODULE_DEVICE_TABLE(acpi, rbtn_ids);
MODULE_DESCRIPTION("Dell Airplane Mode Switch driver");
MODULE_AUTHOR("Pali Rohथँr <pali@kernel.org>");
MODULE_LICENSE("GPL");
