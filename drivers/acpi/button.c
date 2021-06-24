<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  button.c - ACPI Button Driver
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) "ACPI: button: " fmt

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <acpi/button.h>

#घोषणा ACPI_BUTTON_CLASS		"button"
#घोषणा ACPI_BUTTON_खाता_STATE		"state"
#घोषणा ACPI_BUTTON_TYPE_UNKNOWN	0x00
#घोषणा ACPI_BUTTON_NOTIFY_STATUS	0x80

#घोषणा ACPI_BUTTON_SUBCLASS_POWER	"power"
#घोषणा ACPI_BUTTON_DEVICE_NAME_POWER	"Power Button"
#घोषणा ACPI_BUTTON_TYPE_POWER		0x01

#घोषणा ACPI_BUTTON_SUBCLASS_SLEEP	"sleep"
#घोषणा ACPI_BUTTON_DEVICE_NAME_SLEEP	"Sleep Button"
#घोषणा ACPI_BUTTON_TYPE_SLEEP		0x03

#घोषणा ACPI_BUTTON_SUBCLASS_LID	"lid"
#घोषणा ACPI_BUTTON_DEVICE_NAME_LID	"Lid Switch"
#घोषणा ACPI_BUTTON_TYPE_LID		0x05

क्रमागत अणु
	ACPI_BUTTON_LID_INIT_IGNORE,
	ACPI_BUTTON_LID_INIT_OPEN,
	ACPI_BUTTON_LID_INIT_METHOD,
	ACPI_BUTTON_LID_INIT_DISABLED,
पूर्ण;

अटल स्थिर अक्षर * स्थिर lid_init_state_str[] = अणु
	[ACPI_BUTTON_LID_INIT_IGNORE]		= "ignore",
	[ACPI_BUTTON_LID_INIT_OPEN]		= "open",
	[ACPI_BUTTON_LID_INIT_METHOD]		= "method",
	[ACPI_BUTTON_LID_INIT_DISABLED]		= "disabled",
पूर्ण;

MODULE_AUTHOR("Paul Diefenbaugh");
MODULE_DESCRIPTION("ACPI Button Driver");
MODULE_LICENSE("GPL");

अटल स्थिर काष्ठा acpi_device_id button_device_ids[] = अणु
	अणुACPI_BUTTON_HID_LID,    0पूर्ण,
	अणुACPI_BUTTON_HID_SLEEP,  0पूर्ण,
	अणुACPI_BUTTON_HID_SLEEPF, 0पूर्ण,
	अणुACPI_BUTTON_HID_POWER,  0पूर्ण,
	अणुACPI_BUTTON_HID_POWERF, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, button_device_ids);

/* Please keep this list sorted alphabetically by venकरोr and model */
अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_lid_quirks[] = अणु
	अणु
		/* GP-electronic T701, _LID method poपूर्णांकs to a भग्नing GPIO */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Insyde"),
			DMI_MATCH(DMI_PRODUCT_NAME, "T701"),
			DMI_MATCH(DMI_BIOS_VERSION, "BYT70A.YNCHENG.WIN.007"),
		पूर्ण,
		.driver_data = (व्योम *)(दीर्घ)ACPI_BUTTON_LID_INIT_DISABLED,
	पूर्ण,
	अणु
		/*
		 * Medion Akoya E2215T, notअगरication of the LID device only
		 * happens on बंद, not on खोलो and _LID always वापसs बंदd.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDION"),
			DMI_MATCH(DMI_PRODUCT_NAME, "E2215T"),
		पूर्ण,
		.driver_data = (व्योम *)(दीर्घ)ACPI_BUTTON_LID_INIT_OPEN,
	पूर्ण,
	अणु
		/*
		 * Medion Akoya E2228T, notअगरication of the LID device only
		 * happens on बंद, not on खोलो and _LID always वापसs बंदd.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEDION"),
			DMI_MATCH(DMI_PRODUCT_NAME, "E2228T"),
		पूर्ण,
		.driver_data = (व्योम *)(दीर्घ)ACPI_BUTTON_LID_INIT_OPEN,
	पूर्ण,
	अणु
		/*
		 * Razer Blade Stealth 13 late 2019, notअगरication of the LID device
		 * only happens on बंद, not on खोलो and _LID always वापसs बंदd.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Razer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Razer Blade Stealth 13 Late 2019"),
		पूर्ण,
		.driver_data = (व्योम *)(दीर्घ)ACPI_BUTTON_LID_INIT_OPEN,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक acpi_button_add(काष्ठा acpi_device *device);
अटल पूर्णांक acpi_button_हटाओ(काष्ठा acpi_device *device);
अटल व्योम acpi_button_notअगरy(काष्ठा acpi_device *device, u32 event);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_button_suspend(काष्ठा device *dev);
अटल पूर्णांक acpi_button_resume(काष्ठा device *dev);
#अन्यथा
#घोषणा acpi_button_suspend शून्य
#घोषणा acpi_button_resume शून्य
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(acpi_button_pm, acpi_button_suspend, acpi_button_resume);

अटल काष्ठा acpi_driver acpi_button_driver = अणु
	.name = "button",
	.class = ACPI_BUTTON_CLASS,
	.ids = button_device_ids,
	.ops = अणु
		.add = acpi_button_add,
		.हटाओ = acpi_button_हटाओ,
		.notअगरy = acpi_button_notअगरy,
	पूर्ण,
	.drv.pm = &acpi_button_pm,
पूर्ण;

काष्ठा acpi_button अणु
	अचिन्हित पूर्णांक type;
	काष्ठा input_dev *input;
	अक्षर phys[32];			/* क्रम input device */
	अचिन्हित दीर्घ pushed;
	पूर्णांक last_state;
	kसमय_प्रकार last_समय;
	bool suspended;
	bool lid_state_initialized;
पूर्ण;

अटल काष्ठा acpi_device *lid_device;
अटल दीर्घ lid_init_state = -1;

अटल अचिन्हित दीर्घ lid_report_पूर्णांकerval __पढ़ो_mostly = 500;
module_param(lid_report_पूर्णांकerval, uदीर्घ, 0644);
MODULE_PARM_DESC(lid_report_पूर्णांकerval, "Interval (ms) between lid key events");

/* FS Interface (/proc) */
अटल काष्ठा proc_dir_entry *acpi_button_dir;
अटल काष्ठा proc_dir_entry *acpi_lid_dir;

अटल पूर्णांक acpi_lid_evaluate_state(काष्ठा acpi_device *device)
अणु
	अचिन्हित दीर्घ दीर्घ lid_state;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(device->handle, "_LID", शून्य, &lid_state);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	वापस lid_state ? 1 : 0;
पूर्ण

अटल पूर्णांक acpi_lid_notअगरy_state(काष्ठा acpi_device *device, पूर्णांक state)
अणु
	काष्ठा acpi_button *button = acpi_driver_data(device);
	kसमय_प्रकार next_report;
	bool करो_update;

	/*
	 * In lid_init_state=ignore mode, अगर user खोलोs/बंदs lid
	 * frequently with "open" missing, and "last_time" is also updated
	 * frequently, "close" cannot be delivered to the userspace.
	 * So "last_time" is only updated after a समयout or an actual
	 * चयन.
	 */
	अगर (lid_init_state != ACPI_BUTTON_LID_INIT_IGNORE ||
	    button->last_state != !!state)
		करो_update = true;
	अन्यथा
		करो_update = false;

	next_report = kसमय_add(button->last_समय,
				ms_to_kसमय(lid_report_पूर्णांकerval));
	अगर (button->last_state == !!state &&
	    kसमय_after(kसमय_get(), next_report)) अणु
		/* Complain the buggy firmware */
		pr_warn_once("The lid device is not compliant to SW_LID.\n");

		/*
		 * Send the unreliable complement चयन event:
		 *
		 * On most platक्रमms, the lid device is reliable. However
		 * there are exceptions:
		 * 1. Platक्रमms वापसing initial lid state as "close" by
		 *    शेष after booting/resuming:
		 *     https://bugzilla.kernel.org/show_bug.cgi?id=89211
		 *     https://bugzilla.kernel.org/show_bug.cgi?id=106151
		 * 2. Platक्रमms never reporting "open" events:
		 *     https://bugzilla.kernel.org/show_bug.cgi?id=106941
		 * On these buggy platक्रमms, the usage model of the ACPI
		 * lid device actually is:
		 * 1. The initial वापसing value of _LID may not be
		 *    reliable.
		 * 2. The खोलो event may not be reliable.
		 * 3. The बंद event is reliable.
		 *
		 * But SW_LID is typed as input चयन event, the input
		 * layer checks अगर the event is redundant. Hence अगर the
		 * state is not चयनed, the userspace cannot see this
		 * platक्रमm triggered reliable event. By inserting a
		 * complement चयन event, it then is guaranteed that the
		 * platक्रमm triggered reliable one can always be seen by
		 * the userspace.
		 */
		अगर (lid_init_state == ACPI_BUTTON_LID_INIT_IGNORE) अणु
			करो_update = true;
			/*
			 * Do generate complement चयन event क्रम "close"
			 * as "close" is reliable and wrong "open" won't
			 * trigger unexpected behaviors.
			 * Do not generate complement चयन event क्रम
			 * "open" as "open" is not reliable and wrong
			 * "close" will trigger unexpected behaviors.
			 */
			अगर (!state) अणु
				input_report_चयन(button->input,
						    SW_LID, state);
				input_sync(button->input);
			पूर्ण
		पूर्ण
	पूर्ण
	/* Send the platक्रमm triggered reliable event */
	अगर (करो_update) अणु
		acpi_handle_debug(device->handle, "ACPI LID %s\n",
				  state ? "open" : "closed");
		input_report_चयन(button->input, SW_LID, !state);
		input_sync(button->input);
		button->last_state = !!state;
		button->last_समय = kसमय_get();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused acpi_button_state_seq_show(काष्ठा seq_file *seq,
						     व्योम *offset)
अणु
	काष्ठा acpi_device *device = seq->निजी;
	पूर्णांक state;

	state = acpi_lid_evaluate_state(device);
	seq_म_लिखो(seq, "state:      %s\n",
		   state < 0 ? "unsupported" : (state ? "open" : "closed"));
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_button_add_fs(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_button *button = acpi_driver_data(device);
	काष्ठा proc_dir_entry *entry = शून्य;
	पूर्णांक ret = 0;

	/* procfs I/F क्रम ACPI lid device only */
	अगर (button->type != ACPI_BUTTON_TYPE_LID)
		वापस 0;

	अगर (acpi_button_dir || acpi_lid_dir) अणु
		pr_info("More than one Lid device found!\n");
		वापस -EEXIST;
	पूर्ण

	/* create /proc/acpi/button */
	acpi_button_dir = proc_सूची_गढ़ो(ACPI_BUTTON_CLASS, acpi_root_dir);
	अगर (!acpi_button_dir)
		वापस -ENODEV;

	/* create /proc/acpi/button/lid */
	acpi_lid_dir = proc_सूची_गढ़ो(ACPI_BUTTON_SUBCLASS_LID, acpi_button_dir);
	अगर (!acpi_lid_dir) अणु
		ret = -ENODEV;
		जाओ हटाओ_button_dir;
	पूर्ण

	/* create /proc/acpi/button/lid/LID/ */
	acpi_device_dir(device) = proc_सूची_गढ़ो(acpi_device_bid(device), acpi_lid_dir);
	अगर (!acpi_device_dir(device)) अणु
		ret = -ENODEV;
		जाओ हटाओ_lid_dir;
	पूर्ण

	/* create /proc/acpi/button/lid/LID/state */
	entry = proc_create_single_data(ACPI_BUTTON_खाता_STATE, S_IRUGO,
			acpi_device_dir(device), acpi_button_state_seq_show,
			device);
	अगर (!entry) अणु
		ret = -ENODEV;
		जाओ हटाओ_dev_dir;
	पूर्ण

करोne:
	वापस ret;

हटाओ_dev_dir:
	हटाओ_proc_entry(acpi_device_bid(device),
			  acpi_lid_dir);
	acpi_device_dir(device) = शून्य;
हटाओ_lid_dir:
	हटाओ_proc_entry(ACPI_BUTTON_SUBCLASS_LID, acpi_button_dir);
	acpi_lid_dir = शून्य;
हटाओ_button_dir:
	हटाओ_proc_entry(ACPI_BUTTON_CLASS, acpi_root_dir);
	acpi_button_dir = शून्य;
	जाओ करोne;
पूर्ण

अटल पूर्णांक acpi_button_हटाओ_fs(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_button *button = acpi_driver_data(device);

	अगर (button->type != ACPI_BUTTON_TYPE_LID)
		वापस 0;

	हटाओ_proc_entry(ACPI_BUTTON_खाता_STATE,
			  acpi_device_dir(device));
	हटाओ_proc_entry(acpi_device_bid(device),
			  acpi_lid_dir);
	acpi_device_dir(device) = शून्य;
	हटाओ_proc_entry(ACPI_BUTTON_SUBCLASS_LID, acpi_button_dir);
	acpi_lid_dir = शून्य;
	हटाओ_proc_entry(ACPI_BUTTON_CLASS, acpi_root_dir);
	acpi_button_dir = शून्य;

	वापस 0;
पूर्ण

/* Driver Interface */
पूर्णांक acpi_lid_खोलो(व्योम)
अणु
	अगर (!lid_device)
		वापस -ENODEV;

	वापस acpi_lid_evaluate_state(lid_device);
पूर्ण
EXPORT_SYMBOL(acpi_lid_खोलो);

अटल पूर्णांक acpi_lid_update_state(काष्ठा acpi_device *device,
				 bool संकेत_wakeup)
अणु
	पूर्णांक state;

	state = acpi_lid_evaluate_state(device);
	अगर (state < 0)
		वापस state;

	अगर (state && संकेत_wakeup)
		acpi_pm_wakeup_event(&device->dev);

	वापस acpi_lid_notअगरy_state(device, state);
पूर्ण

अटल व्योम acpi_lid_initialize_state(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_button *button = acpi_driver_data(device);

	चयन (lid_init_state) अणु
	हाल ACPI_BUTTON_LID_INIT_OPEN:
		(व्योम)acpi_lid_notअगरy_state(device, 1);
		अवरोध;
	हाल ACPI_BUTTON_LID_INIT_METHOD:
		(व्योम)acpi_lid_update_state(device, false);
		अवरोध;
	हाल ACPI_BUTTON_LID_INIT_IGNORE:
	शेष:
		अवरोध;
	पूर्ण

	button->lid_state_initialized = true;
पूर्ण

अटल व्योम acpi_button_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा acpi_button *button = acpi_driver_data(device);
	काष्ठा input_dev *input;

	चयन (event) अणु
	हाल ACPI_FIXED_HARDWARE_EVENT:
		event = ACPI_BUTTON_NOTIFY_STATUS;
		fallthrough;
	हाल ACPI_BUTTON_NOTIFY_STATUS:
		input = button->input;
		अगर (button->type == ACPI_BUTTON_TYPE_LID) अणु
			अगर (button->lid_state_initialized)
				acpi_lid_update_state(device, true);
		पूर्ण अन्यथा अणु
			पूर्णांक keycode;

			acpi_pm_wakeup_event(&device->dev);
			अगर (button->suspended)
				अवरोध;

			keycode = test_bit(KEY_SLEEP, input->keybit) ?
						KEY_SLEEP : KEY_POWER;
			input_report_key(input, keycode, 1);
			input_sync(input);
			input_report_key(input, keycode, 0);
			input_sync(input);

			acpi_bus_generate_netlink_event(
					device->pnp.device_class,
					dev_name(&device->dev),
					event, ++button->pushed);
		पूर्ण
		अवरोध;
	शेष:
		acpi_handle_debug(device->handle, "Unsupported event [0x%x]\n",
				  event);
		अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_button_suspend(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *device = to_acpi_device(dev);
	काष्ठा acpi_button *button = acpi_driver_data(device);

	button->suspended = true;
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_button_resume(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *device = to_acpi_device(dev);
	काष्ठा acpi_button *button = acpi_driver_data(device);

	button->suspended = false;
	अगर (button->type == ACPI_BUTTON_TYPE_LID) अणु
		button->last_state = !!acpi_lid_evaluate_state(device);
		button->last_समय = kसमय_get();
		acpi_lid_initialize_state(device);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक acpi_lid_input_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा acpi_device *device = input_get_drvdata(input);
	काष्ठा acpi_button *button = acpi_driver_data(device);

	button->last_state = !!acpi_lid_evaluate_state(device);
	button->last_समय = kसमय_get();
	acpi_lid_initialize_state(device);

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_button_add(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_button *button;
	काष्ठा input_dev *input;
	स्थिर अक्षर *hid = acpi_device_hid(device);
	अक्षर *name, *class;
	पूर्णांक error;

	अगर (!म_भेद(hid, ACPI_BUTTON_HID_LID) &&
	     lid_init_state == ACPI_BUTTON_LID_INIT_DISABLED)
		वापस -ENODEV;

	button = kzalloc(माप(काष्ठा acpi_button), GFP_KERNEL);
	अगर (!button)
		वापस -ENOMEM;

	device->driver_data = button;

	button->input = input = input_allocate_device();
	अगर (!input) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_button;
	पूर्ण

	name = acpi_device_name(device);
	class = acpi_device_class(device);

	अगर (!म_भेद(hid, ACPI_BUTTON_HID_POWER) ||
	    !म_भेद(hid, ACPI_BUTTON_HID_POWERF)) अणु
		button->type = ACPI_BUTTON_TYPE_POWER;
		म_नकल(name, ACPI_BUTTON_DEVICE_NAME_POWER);
		प्र_लिखो(class, "%s/%s",
			ACPI_BUTTON_CLASS, ACPI_BUTTON_SUBCLASS_POWER);
	पूर्ण अन्यथा अगर (!म_भेद(hid, ACPI_BUTTON_HID_SLEEP) ||
		   !म_भेद(hid, ACPI_BUTTON_HID_SLEEPF)) अणु
		button->type = ACPI_BUTTON_TYPE_SLEEP;
		म_नकल(name, ACPI_BUTTON_DEVICE_NAME_SLEEP);
		प्र_लिखो(class, "%s/%s",
			ACPI_BUTTON_CLASS, ACPI_BUTTON_SUBCLASS_SLEEP);
	पूर्ण अन्यथा अगर (!म_भेद(hid, ACPI_BUTTON_HID_LID)) अणु
		button->type = ACPI_BUTTON_TYPE_LID;
		म_नकल(name, ACPI_BUTTON_DEVICE_NAME_LID);
		प्र_लिखो(class, "%s/%s",
			ACPI_BUTTON_CLASS, ACPI_BUTTON_SUBCLASS_LID);
		input->खोलो = acpi_lid_input_खोलो;
	पूर्ण अन्यथा अणु
		pr_info("Unsupported hid [%s]\n", hid);
		error = -ENODEV;
		जाओ err_मुक्त_input;
	पूर्ण

	error = acpi_button_add_fs(device);
	अगर (error)
		जाओ err_मुक्त_input;

	snम_लिखो(button->phys, माप(button->phys), "%s/button/input0", hid);

	input->name = name;
	input->phys = button->phys;
	input->id.bustype = BUS_HOST;
	input->id.product = button->type;
	input->dev.parent = &device->dev;

	चयन (button->type) अणु
	हाल ACPI_BUTTON_TYPE_POWER:
		input_set_capability(input, EV_KEY, KEY_POWER);
		अवरोध;

	हाल ACPI_BUTTON_TYPE_SLEEP:
		input_set_capability(input, EV_KEY, KEY_SLEEP);
		अवरोध;

	हाल ACPI_BUTTON_TYPE_LID:
		input_set_capability(input, EV_SW, SW_LID);
		अवरोध;
	पूर्ण

	input_set_drvdata(input, device);
	error = input_रेजिस्टर_device(input);
	अगर (error)
		जाओ err_हटाओ_fs;
	अगर (button->type == ACPI_BUTTON_TYPE_LID) अणु
		/*
		 * This assumes there's only one lid device, or अगर there are
		 * more we only care about the last one...
		 */
		lid_device = device;
	पूर्ण

	device_init_wakeup(&device->dev, true);
	pr_info("%s [%s]\n", name, acpi_device_bid(device));
	वापस 0;

 err_हटाओ_fs:
	acpi_button_हटाओ_fs(device);
 err_मुक्त_input:
	input_मुक्त_device(input);
 err_मुक्त_button:
	kमुक्त(button);
	वापस error;
पूर्ण

अटल पूर्णांक acpi_button_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_button *button = acpi_driver_data(device);

	acpi_button_हटाओ_fs(device);
	input_unरेजिस्टर_device(button->input);
	kमुक्त(button);
	वापस 0;
पूर्ण

अटल पूर्णांक param_set_lid_init_state(स्थिर अक्षर *val,
				    स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक i;

	i = sysfs_match_string(lid_init_state_str, val);
	अगर (i < 0)
		वापस i;

	lid_init_state = i;
	pr_info("Initial lid state set to '%s'\n", lid_init_state_str[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक param_get_lid_init_state(अक्षर *buf, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक i, c = 0;

	क्रम (i = 0; i < ARRAY_SIZE(lid_init_state_str); i++)
		अगर (i == lid_init_state)
			c += प्र_लिखो(buf + c, "[%s] ", lid_init_state_str[i]);
		अन्यथा
			c += प्र_लिखो(buf + c, "%s ", lid_init_state_str[i]);

	buf[c - 1] = '\n'; /* Replace the final space with a newline */

	वापस c;
पूर्ण

module_param_call(lid_init_state,
		  param_set_lid_init_state, param_get_lid_init_state,
		  शून्य, 0644);
MODULE_PARM_DESC(lid_init_state, "Behavior for reporting LID initial state");

अटल पूर्णांक acpi_button_रेजिस्टर_driver(काष्ठा acpi_driver *driver)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;

	अगर (lid_init_state == -1) अणु
		dmi_id = dmi_first_match(dmi_lid_quirks);
		अगर (dmi_id)
			lid_init_state = (दीर्घ)dmi_id->driver_data;
		अन्यथा
			lid_init_state = ACPI_BUTTON_LID_INIT_METHOD;
	पूर्ण

	/*
	 * Modules such as nouveau.ko and i915.ko have a link समय dependency
	 * on acpi_lid_खोलो(), and would thereक्रमe not be loadable on ACPI
	 * capable kernels booted in non-ACPI mode अगर the वापस value of
	 * acpi_bus_रेजिस्टर_driver() is वापसed from here with ACPI disabled
	 * when this driver is built as a module.
	 */
	अगर (acpi_disabled)
		वापस 0;

	वापस acpi_bus_रेजिस्टर_driver(driver);
पूर्ण

अटल व्योम acpi_button_unरेजिस्टर_driver(काष्ठा acpi_driver *driver)
अणु
	अगर (!acpi_disabled)
		acpi_bus_unरेजिस्टर_driver(driver);
पूर्ण

module_driver(acpi_button_driver, acpi_button_रेजिस्टर_driver,
	       acpi_button_unरेजिस्टर_driver);
