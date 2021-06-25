<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  WMI hotkeys support क्रम Dell All-In-One series
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/acpi.h>
#समावेश <linux/माला.स>

MODULE_DESCRIPTION("WMI hotkeys driver for Dell All-In-One series");
MODULE_LICENSE("GPL");

#घोषणा EVENT_GUID1 "284A0E6B-380E-472A-921F-E52786257FB4"
#घोषणा EVENT_GUID2 "02314822-307C-4F66-BF0E-48AEAEB26CC8"

काष्ठा dell_wmi_event अणु
	u16	length;
	/* 0x000: A hot key pressed or an event occurred
	 * 0x00F: A sequence of hot keys are pressed */
	u16	type;
	u16	event[];
पूर्ण;

अटल स्थिर अक्षर *dell_wmi_aio_guids[] = अणु
	EVENT_GUID1,
	EVENT_GUID2,
	शून्य
पूर्ण;

MODULE_ALIAS("wmi:"EVENT_GUID1);
MODULE_ALIAS("wmi:"EVENT_GUID2);

अटल स्थिर काष्ठा key_entry dell_wmi_aio_keymap[] = अणु
	अणु KE_KEY, 0xc0, अणु KEY_VOLUMEUP पूर्ण पूर्ण,
	अणु KE_KEY, 0xc1, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 0xe030, अणु KEY_VOLUMEUP पूर्ण पूर्ण,
	अणु KE_KEY, 0xe02e, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 0xe020, अणु KEY_MUTE पूर्ण पूर्ण,
	अणु KE_KEY, 0xe027, अणु KEY_DISPLAYTOGGLE पूर्ण पूर्ण,
	अणु KE_KEY, 0xe006, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	अणु KE_KEY, 0xe005, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 0xe00b, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण,
	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल काष्ठा input_dev *dell_wmi_aio_input_dev;

/*
 * The new WMI event data क्रमmat will follow the dell_wmi_event काष्ठाure
 * So, we will check अगर the buffer matches the क्रमmat
 */
अटल bool dell_wmi_aio_event_check(u8 *buffer, पूर्णांक length)
अणु
	काष्ठा dell_wmi_event *event = (काष्ठा dell_wmi_event *)buffer;

	अगर (event == शून्य || length < 6)
		वापस false;

	अगर ((event->type == 0 || event->type == 0xf) &&
			event->length >= 2)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम dell_wmi_aio_notअगरy(u32 value, व्योम *context)
अणु
	काष्ठा acpi_buffer response = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	काष्ठा dell_wmi_event *event;
	acpi_status status;

	status = wmi_get_event_data(value, &response);
	अगर (status != AE_OK) अणु
		pr_info("bad event status 0x%x\n", status);
		वापस;
	पूर्ण

	obj = (जोड़ acpi_object *)response.poपूर्णांकer;
	अगर (obj) अणु
		अचिन्हित पूर्णांक scancode = 0;

		चयन (obj->type) अणु
		हाल ACPI_TYPE_INTEGER:
			/* Most All-In-One correctly वापस पूर्णांकeger scancode */
			scancode = obj->पूर्णांकeger.value;
			sparse_keymap_report_event(dell_wmi_aio_input_dev,
				scancode, 1, true);
			अवरोध;
		हाल ACPI_TYPE_BUFFER:
			अगर (dell_wmi_aio_event_check(obj->buffer.poपूर्णांकer,
						obj->buffer.length)) अणु
				event = (काष्ठा dell_wmi_event *)
					obj->buffer.poपूर्णांकer;
				scancode = event->event[0];
			पूर्ण अन्यथा अणु
				/* Broken machines वापस the scancode in a
				   buffer */
				अगर (obj->buffer.poपूर्णांकer &&
						obj->buffer.length > 0)
					scancode = obj->buffer.poपूर्णांकer[0];
			पूर्ण
			अगर (scancode)
				sparse_keymap_report_event(
					dell_wmi_aio_input_dev,
					scancode, 1, true);
			अवरोध;
		पूर्ण
	पूर्ण
	kमुक्त(obj);
पूर्ण

अटल पूर्णांक __init dell_wmi_aio_input_setup(व्योम)
अणु
	पूर्णांक err;

	dell_wmi_aio_input_dev = input_allocate_device();

	अगर (!dell_wmi_aio_input_dev)
		वापस -ENOMEM;

	dell_wmi_aio_input_dev->name = "Dell AIO WMI hotkeys";
	dell_wmi_aio_input_dev->phys = "wmi/input0";
	dell_wmi_aio_input_dev->id.bustype = BUS_HOST;

	err = sparse_keymap_setup(dell_wmi_aio_input_dev,
			dell_wmi_aio_keymap, शून्य);
	अगर (err) अणु
		pr_err("Unable to setup input device keymap\n");
		जाओ err_मुक्त_dev;
	पूर्ण
	err = input_रेजिस्टर_device(dell_wmi_aio_input_dev);
	अगर (err) अणु
		pr_info("Unable to register input device\n");
		जाओ err_मुक्त_dev;
	पूर्ण
	वापस 0;

err_मुक्त_dev:
	input_मुक्त_device(dell_wmi_aio_input_dev);
	वापस err;
पूर्ण

अटल स्थिर अक्षर *dell_wmi_aio_find(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; dell_wmi_aio_guids[i] != शून्य; i++)
		अगर (wmi_has_guid(dell_wmi_aio_guids[i]))
			वापस dell_wmi_aio_guids[i];

	वापस शून्य;
पूर्ण

अटल पूर्णांक __init dell_wmi_aio_init(व्योम)
अणु
	पूर्णांक err;
	स्थिर अक्षर *guid;

	guid = dell_wmi_aio_find();
	अगर (!guid) अणु
		pr_warn("No known WMI GUID found\n");
		वापस -ENXIO;
	पूर्ण

	err = dell_wmi_aio_input_setup();
	अगर (err)
		वापस err;

	err = wmi_install_notअगरy_handler(guid, dell_wmi_aio_notअगरy, शून्य);
	अगर (err) अणु
		pr_err("Unable to register notify handler - %d\n", err);
		input_unरेजिस्टर_device(dell_wmi_aio_input_dev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास dell_wmi_aio_निकास(व्योम)
अणु
	स्थिर अक्षर *guid;

	guid = dell_wmi_aio_find();
	wmi_हटाओ_notअगरy_handler(guid);
	input_unरेजिस्टर_device(dell_wmi_aio_input_dev);
पूर्ण

module_init(dell_wmi_aio_init);
module_निकास(dell_wmi_aio_निकास);
