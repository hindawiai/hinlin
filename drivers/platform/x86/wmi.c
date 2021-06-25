<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ACPI-WMI mapping driver
 *
 *  Copyright (C) 2007-2008 Carlos Corbacho <carlos@strangeworlds.co.uk>
 *
 *  GUID parsing code from ldm.c is:
 *   Copyright (C) 2001,2002 Riअक्षरd Russon <ldm@flatcap.org>
 *   Copyright (c) 2001-2007 Anton Altaparmakov
 *   Copyright (C) 2001,2002 Jakob Kemi <jakob.kemi@telia.com>
 *
 *  WMI bus infraकाष्ठाure by Andrew Lutomirski and Darren Hart:
 *    Copyright (C) 2015 Andrew Lutomirski
 *    Copyright (C) 2017 VMware, Inc. All Rights Reserved.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/uuid.h>
#समावेश <linux/wmi.h>
#समावेश <linux/fs.h>
#समावेश <uapi/linux/wmi.h>

MODULE_AUTHOR("Carlos Corbacho");
MODULE_DESCRIPTION("ACPI-WMI Mapping Driver");
MODULE_LICENSE("GPL");

अटल LIST_HEAD(wmi_block_list);

काष्ठा guid_block अणु
	अक्षर guid[16];
	जोड़ अणु
		अक्षर object_id[2];
		काष्ठा अणु
			अचिन्हित अक्षर notअगरy_id;
			अचिन्हित अक्षर reserved;
		पूर्ण;
	पूर्ण;
	u8 instance_count;
	u8 flags;
पूर्ण;

काष्ठा wmi_block अणु
	काष्ठा wmi_device dev;
	काष्ठा list_head list;
	काष्ठा guid_block gblock;
	काष्ठा miscdevice अक्षर_dev;
	काष्ठा mutex अक्षर_mutex;
	काष्ठा acpi_device *acpi_device;
	wmi_notअगरy_handler handler;
	व्योम *handler_data;
	u64 req_buf_size;

	bool पढ़ो_takes_no_args;
पूर्ण;


/*
 * If the GUID data block is marked as expensive, we must enable and
 * explicitily disable data collection.
 */
#घोषणा ACPI_WMI_EXPENSIVE   0x1
#घोषणा ACPI_WMI_METHOD      0x2	/* GUID is a method */
#घोषणा ACPI_WMI_STRING      0x4	/* GUID takes & वापसs a string */
#घोषणा ACPI_WMI_EVENT       0x8	/* GUID is an event */

अटल bool debug_event;
module_param(debug_event, bool, 0444);
MODULE_PARM_DESC(debug_event,
		 "Log WMI Events [0/1]");

अटल bool debug_dump_wdg;
module_param(debug_dump_wdg, bool, 0444);
MODULE_PARM_DESC(debug_dump_wdg,
		 "Dump available WMI interfaces [0/1]");

अटल पूर्णांक acpi_wmi_हटाओ(काष्ठा platक्रमm_device *device);
अटल पूर्णांक acpi_wmi_probe(काष्ठा platक्रमm_device *device);

अटल स्थिर काष्ठा acpi_device_id wmi_device_ids[] = अणु
	अणु"PNP0C14", 0पूर्ण,
	अणु"pnp0c14", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, wmi_device_ids);

अटल काष्ठा platक्रमm_driver acpi_wmi_driver = अणु
	.driver = अणु
		.name = "acpi-wmi",
		.acpi_match_table = wmi_device_ids,
	पूर्ण,
	.probe = acpi_wmi_probe,
	.हटाओ = acpi_wmi_हटाओ,
पूर्ण;

/*
 * GUID parsing functions
 */

अटल bool find_guid(स्थिर अक्षर *guid_string, काष्ठा wmi_block **out)
अणु
	guid_t guid_input;
	काष्ठा wmi_block *wblock;
	काष्ठा guid_block *block;

	अगर (guid_parse(guid_string, &guid_input))
		वापस false;

	list_क्रम_each_entry(wblock, &wmi_block_list, list) अणु
		block = &wblock->gblock;

		अगर (स_भेद(block->guid, &guid_input, 16) == 0) अणु
			अगर (out)
				*out = wblock;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर व्योम *find_guid_context(काष्ठा wmi_block *wblock,
				      काष्ठा wmi_driver *wdriver)
अणु
	स्थिर काष्ठा wmi_device_id *id;
	guid_t guid_input;

	अगर (wblock == शून्य || wdriver == शून्य)
		वापस शून्य;
	अगर (wdriver->id_table == शून्य)
		वापस शून्य;

	id = wdriver->id_table;
	जबतक (*id->guid_string) अणु
		अगर (guid_parse(id->guid_string, &guid_input))
			जारी;
		अगर (!स_भेद(wblock->gblock.guid, &guid_input, 16))
			वापस id->context;
		id++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक get_subobj_info(acpi_handle handle, स्थिर अक्षर *pathname,
			   काष्ठा acpi_device_info **info)
अणु
	काष्ठा acpi_device_info *dummy_info, **info_ptr;
	acpi_handle subobj_handle;
	acpi_status status;

	status = acpi_get_handle(handle, (अक्षर *)pathname, &subobj_handle);
	अगर (status == AE_NOT_FOUND)
		वापस -ENOENT;
	अन्यथा अगर (ACPI_FAILURE(status))
		वापस -EIO;

	info_ptr = info ? info : &dummy_info;
	status = acpi_get_object_info(subobj_handle, info_ptr);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	अगर (!info)
		kमुक्त(dummy_info);

	वापस 0;
पूर्ण

अटल acpi_status wmi_method_enable(काष्ठा wmi_block *wblock, पूर्णांक enable)
अणु
	काष्ठा guid_block *block = शून्य;
	अक्षर method[5];
	acpi_status status;
	acpi_handle handle;

	block = &wblock->gblock;
	handle = wblock->acpi_device->handle;

	snम_लिखो(method, 5, "WE%02X", block->notअगरy_id);
	status = acpi_execute_simple_method(handle, method, enable);

	अगर (status != AE_OK && status != AE_NOT_FOUND)
		वापस status;
	अन्यथा
		वापस AE_OK;
पूर्ण

/*
 * Exported WMI functions
 */

/**
 * set_required_buffer_size - Sets the buffer size needed क्रम perक्रमming IOCTL
 * @wdev: A wmi bus device from a driver
 * @length: Required buffer size
 *
 * Allocates memory needed क्रम buffer, stores the buffer size in that memory
 */
पूर्णांक set_required_buffer_size(काष्ठा wmi_device *wdev, u64 length)
अणु
	काष्ठा wmi_block *wblock;

	wblock = container_of(wdev, काष्ठा wmi_block, dev);
	wblock->req_buf_size = length;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(set_required_buffer_size);

/**
 * wmi_evaluate_method - Evaluate a WMI method
 * @guid_string: 36 अक्षर string of the क्रमm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 * @instance: Instance index
 * @method_id: Method ID to call
 * @in: Buffer containing input क्रम the method call
 * @out: Empty buffer to वापस the method results
 *
 * Call an ACPI-WMI method
 */
acpi_status wmi_evaluate_method(स्थिर अक्षर *guid_string, u8 instance,
u32 method_id, स्थिर काष्ठा acpi_buffer *in, काष्ठा acpi_buffer *out)
अणु
	काष्ठा wmi_block *wblock = शून्य;

	अगर (!find_guid(guid_string, &wblock))
		वापस AE_ERROR;
	वापस wmidev_evaluate_method(&wblock->dev, instance, method_id,
				      in, out);
पूर्ण
EXPORT_SYMBOL_GPL(wmi_evaluate_method);

/**
 * wmidev_evaluate_method - Evaluate a WMI method
 * @wdev: A wmi bus device from a driver
 * @instance: Instance index
 * @method_id: Method ID to call
 * @in: Buffer containing input क्रम the method call
 * @out: Empty buffer to वापस the method results
 *
 * Call an ACPI-WMI method
 */
acpi_status wmidev_evaluate_method(काष्ठा wmi_device *wdev, u8 instance,
	u32 method_id, स्थिर काष्ठा acpi_buffer *in, काष्ठा acpi_buffer *out)
अणु
	काष्ठा guid_block *block = शून्य;
	काष्ठा wmi_block *wblock = शून्य;
	acpi_handle handle;
	acpi_status status;
	काष्ठा acpi_object_list input;
	जोड़ acpi_object params[3];
	अक्षर method[5] = "WM";

	wblock = container_of(wdev, काष्ठा wmi_block, dev);
	block = &wblock->gblock;
	handle = wblock->acpi_device->handle;

	अगर (!(block->flags & ACPI_WMI_METHOD))
		वापस AE_BAD_DATA;

	अगर (block->instance_count <= instance)
		वापस AE_BAD_PARAMETER;

	input.count = 2;
	input.poपूर्णांकer = params;
	params[0].type = ACPI_TYPE_INTEGER;
	params[0].पूर्णांकeger.value = instance;
	params[1].type = ACPI_TYPE_INTEGER;
	params[1].पूर्णांकeger.value = method_id;

	अगर (in) अणु
		input.count = 3;

		अगर (block->flags & ACPI_WMI_STRING) अणु
			params[2].type = ACPI_TYPE_STRING;
		पूर्ण अन्यथा अणु
			params[2].type = ACPI_TYPE_BUFFER;
		पूर्ण
		params[2].buffer.length = in->length;
		params[2].buffer.poपूर्णांकer = in->poपूर्णांकer;
	पूर्ण

	म_जोड़न(method, block->object_id, 2);

	status = acpi_evaluate_object(handle, method, &input, out);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(wmidev_evaluate_method);

अटल acpi_status __query_block(काष्ठा wmi_block *wblock, u8 instance,
				 काष्ठा acpi_buffer *out)
अणु
	काष्ठा guid_block *block = शून्य;
	acpi_handle handle;
	acpi_status status, wc_status = AE_ERROR;
	काष्ठा acpi_object_list input;
	जोड़ acpi_object wq_params[1];
	अक्षर method[5];
	अक्षर wc_method[5] = "WC";

	अगर (!out)
		वापस AE_BAD_PARAMETER;

	block = &wblock->gblock;
	handle = wblock->acpi_device->handle;

	अगर (block->instance_count <= instance)
		वापस AE_BAD_PARAMETER;

	/* Check GUID is a data block */
	अगर (block->flags & (ACPI_WMI_EVENT | ACPI_WMI_METHOD))
		वापस AE_ERROR;

	input.count = 1;
	input.poपूर्णांकer = wq_params;
	wq_params[0].type = ACPI_TYPE_INTEGER;
	wq_params[0].पूर्णांकeger.value = instance;

	अगर (instance == 0 && wblock->पढ़ो_takes_no_args)
		input.count = 0;

	/*
	 * If ACPI_WMI_EXPENSIVE, call the relevant WCxx method first to
	 * enable collection.
	 */
	अगर (block->flags & ACPI_WMI_EXPENSIVE) अणु
		म_जोड़न(wc_method, block->object_id, 2);

		/*
		 * Some GUIDs अवरोध the specअगरication by declaring themselves
		 * expensive, but have no corresponding WCxx method. So we
		 * should not fail अगर this happens.
		 */
		wc_status = acpi_execute_simple_method(handle, wc_method, 1);
	पूर्ण

	म_नकल(method, "WQ");
	म_जोड़न(method, block->object_id, 2);

	status = acpi_evaluate_object(handle, method, &input, out);

	/*
	 * If ACPI_WMI_EXPENSIVE, call the relevant WCxx method, even अगर
	 * the WQxx method failed - we should disable collection anyway.
	 */
	अगर ((block->flags & ACPI_WMI_EXPENSIVE) && ACPI_SUCCESS(wc_status)) अणु
		status = acpi_execute_simple_method(handle, wc_method, 0);
	पूर्ण

	वापस status;
पूर्ण

/**
 * wmi_query_block - Return contents of a WMI block (deprecated)
 * @guid_string: 36 अक्षर string of the क्रमm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 * @instance: Instance index
 * @out: Empty buffer to वापस the contents of the data block to
 *
 * Return the contents of an ACPI-WMI data block to a buffer
 */
acpi_status wmi_query_block(स्थिर अक्षर *guid_string, u8 instance,
			    काष्ठा acpi_buffer *out)
अणु
	काष्ठा wmi_block *wblock;

	अगर (!guid_string)
		वापस AE_BAD_PARAMETER;

	अगर (!find_guid(guid_string, &wblock))
		वापस AE_ERROR;

	वापस __query_block(wblock, instance, out);
पूर्ण
EXPORT_SYMBOL_GPL(wmi_query_block);

जोड़ acpi_object *wmidev_block_query(काष्ठा wmi_device *wdev, u8 instance)
अणु
	काष्ठा acpi_buffer out = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा wmi_block *wblock = container_of(wdev, काष्ठा wmi_block, dev);

	अगर (ACPI_FAILURE(__query_block(wblock, instance, &out)))
		वापस शून्य;

	वापस (जोड़ acpi_object *)out.poपूर्णांकer;
पूर्ण
EXPORT_SYMBOL_GPL(wmidev_block_query);

/**
 * wmi_set_block - Write to a WMI block
 * @guid_string: 36 अक्षर string of the क्रमm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 * @instance: Instance index
 * @in: Buffer containing new values क्रम the data block
 *
 * Write the contents of the input buffer to an ACPI-WMI data block
 */
acpi_status wmi_set_block(स्थिर अक्षर *guid_string, u8 instance,
			  स्थिर काष्ठा acpi_buffer *in)
अणु
	काष्ठा guid_block *block = शून्य;
	काष्ठा wmi_block *wblock = शून्य;
	acpi_handle handle;
	काष्ठा acpi_object_list input;
	जोड़ acpi_object params[2];
	अक्षर method[5] = "WS";

	अगर (!guid_string || !in)
		वापस AE_BAD_DATA;

	अगर (!find_guid(guid_string, &wblock))
		वापस AE_ERROR;

	block = &wblock->gblock;
	handle = wblock->acpi_device->handle;

	अगर (block->instance_count <= instance)
		वापस AE_BAD_PARAMETER;

	/* Check GUID is a data block */
	अगर (block->flags & (ACPI_WMI_EVENT | ACPI_WMI_METHOD))
		वापस AE_ERROR;

	input.count = 2;
	input.poपूर्णांकer = params;
	params[0].type = ACPI_TYPE_INTEGER;
	params[0].पूर्णांकeger.value = instance;

	अगर (block->flags & ACPI_WMI_STRING) अणु
		params[1].type = ACPI_TYPE_STRING;
	पूर्ण अन्यथा अणु
		params[1].type = ACPI_TYPE_BUFFER;
	पूर्ण
	params[1].buffer.length = in->length;
	params[1].buffer.poपूर्णांकer = in->poपूर्णांकer;

	म_जोड़न(method, block->object_id, 2);

	वापस acpi_evaluate_object(handle, method, &input, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(wmi_set_block);

अटल व्योम wmi_dump_wdg(स्थिर काष्ठा guid_block *g)
अणु
	pr_info("%pUL:\n", g->guid);
	अगर (g->flags & ACPI_WMI_EVENT)
		pr_info("\tnotify_id: 0x%02X\n", g->notअगरy_id);
	अन्यथा
		pr_info("\tobject_id: %2pE\n", g->object_id);
	pr_info("\tinstance_count: %d\n", g->instance_count);
	pr_info("\tflags: %#x", g->flags);
	अगर (g->flags) अणु
		अगर (g->flags & ACPI_WMI_EXPENSIVE)
			pr_cont(" ACPI_WMI_EXPENSIVE");
		अगर (g->flags & ACPI_WMI_METHOD)
			pr_cont(" ACPI_WMI_METHOD");
		अगर (g->flags & ACPI_WMI_STRING)
			pr_cont(" ACPI_WMI_STRING");
		अगर (g->flags & ACPI_WMI_EVENT)
			pr_cont(" ACPI_WMI_EVENT");
	पूर्ण
	pr_cont("\n");

पूर्ण

अटल व्योम wmi_notअगरy_debug(u32 value, व्योम *context)
अणु
	काष्ठा acpi_buffer response = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;

	status = wmi_get_event_data(value, &response);
	अगर (status != AE_OK) अणु
		pr_info("bad event status 0x%x\n", status);
		वापस;
	पूर्ण

	obj = (जोड़ acpi_object *)response.poपूर्णांकer;

	अगर (!obj)
		वापस;

	pr_info("DEBUG Event ");
	चयन(obj->type) अणु
	हाल ACPI_TYPE_BUFFER:
		pr_cont("BUFFER_TYPE - length %d\n", obj->buffer.length);
		अवरोध;
	हाल ACPI_TYPE_STRING:
		pr_cont("STRING_TYPE - %s\n", obj->string.poपूर्णांकer);
		अवरोध;
	हाल ACPI_TYPE_INTEGER:
		pr_cont("INTEGER_TYPE - %llu\n", obj->पूर्णांकeger.value);
		अवरोध;
	हाल ACPI_TYPE_PACKAGE:
		pr_cont("PACKAGE_TYPE - %d elements\n", obj->package.count);
		अवरोध;
	शेष:
		pr_cont("object type 0x%X\n", obj->type);
	पूर्ण
	kमुक्त(obj);
पूर्ण

/**
 * wmi_install_notअगरy_handler - Register handler क्रम WMI events
 * @guid: 36 अक्षर string of the क्रमm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 * @handler: Function to handle notअगरications
 * @data: Data to be वापसed to handler when event is fired
 *
 * Register a handler क्रम events sent to the ACPI-WMI mapper device.
 */
acpi_status wmi_install_notअगरy_handler(स्थिर अक्षर *guid,
wmi_notअगरy_handler handler, व्योम *data)
अणु
	काष्ठा wmi_block *block;
	acpi_status status = AE_NOT_EXIST;
	guid_t guid_input;

	अगर (!guid || !handler)
		वापस AE_BAD_PARAMETER;

	अगर (guid_parse(guid, &guid_input))
		वापस AE_BAD_PARAMETER;

	list_क्रम_each_entry(block, &wmi_block_list, list) अणु
		acpi_status wmi_status;

		अगर (स_भेद(block->gblock.guid, &guid_input, 16) == 0) अणु
			अगर (block->handler &&
			    block->handler != wmi_notअगरy_debug)
				वापस AE_ALREADY_ACQUIRED;

			block->handler = handler;
			block->handler_data = data;

			wmi_status = wmi_method_enable(block, 1);
			अगर ((wmi_status != AE_OK) ||
			    ((wmi_status == AE_OK) && (status == AE_NOT_EXIST)))
				status = wmi_status;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(wmi_install_notअगरy_handler);

/**
 * wmi_uninstall_notअगरy_handler - Unरेजिस्टर handler क्रम WMI events
 * @guid: 36 अक्षर string of the क्रमm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 *
 * Unरेजिस्टर handler क्रम events sent to the ACPI-WMI mapper device.
 */
acpi_status wmi_हटाओ_notअगरy_handler(स्थिर अक्षर *guid)
अणु
	काष्ठा wmi_block *block;
	acpi_status status = AE_NOT_EXIST;
	guid_t guid_input;

	अगर (!guid)
		वापस AE_BAD_PARAMETER;

	अगर (guid_parse(guid, &guid_input))
		वापस AE_BAD_PARAMETER;

	list_क्रम_each_entry(block, &wmi_block_list, list) अणु
		acpi_status wmi_status;

		अगर (स_भेद(block->gblock.guid, &guid_input, 16) == 0) अणु
			अगर (!block->handler ||
			    block->handler == wmi_notअगरy_debug)
				वापस AE_शून्य_ENTRY;

			अगर (debug_event) अणु
				block->handler = wmi_notअगरy_debug;
				status = AE_OK;
			पूर्ण अन्यथा अणु
				wmi_status = wmi_method_enable(block, 0);
				block->handler = शून्य;
				block->handler_data = शून्य;
				अगर ((wmi_status != AE_OK) ||
				    ((wmi_status == AE_OK) &&
				     (status == AE_NOT_EXIST)))
					status = wmi_status;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(wmi_हटाओ_notअगरy_handler);

/**
 * wmi_get_event_data - Get WMI data associated with an event
 *
 * @event: Event to find
 * @out: Buffer to hold event data. out->poपूर्णांकer should be मुक्तd with kमुक्त()
 *
 * Returns extra data associated with an event in WMI.
 */
acpi_status wmi_get_event_data(u32 event, काष्ठा acpi_buffer *out)
अणु
	काष्ठा acpi_object_list input;
	जोड़ acpi_object params[1];
	काष्ठा guid_block *gblock;
	काष्ठा wmi_block *wblock;

	input.count = 1;
	input.poपूर्णांकer = params;
	params[0].type = ACPI_TYPE_INTEGER;
	params[0].पूर्णांकeger.value = event;

	list_क्रम_each_entry(wblock, &wmi_block_list, list) अणु
		gblock = &wblock->gblock;

		अगर ((gblock->flags & ACPI_WMI_EVENT) &&
			(gblock->notअगरy_id == event))
			वापस acpi_evaluate_object(wblock->acpi_device->handle,
				"_WED", &input, out);
	पूर्ण

	वापस AE_NOT_FOUND;
पूर्ण
EXPORT_SYMBOL_GPL(wmi_get_event_data);

/**
 * wmi_has_guid - Check अगर a GUID is available
 * @guid_string: 36 अक्षर string of the क्रमm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 *
 * Check अगर a given GUID is defined by _WDG
 */
bool wmi_has_guid(स्थिर अक्षर *guid_string)
अणु
	वापस find_guid(guid_string, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(wmi_has_guid);

/**
 * wmi_get_acpi_device_uid() - Get _UID name of ACPI device that defines GUID
 * @guid_string: 36 अक्षर string of the क्रमm fa50ff2b-f2e8-45de-83fa-65417f2f49ba
 *
 * Find the _UID of ACPI device associated with this WMI GUID.
 *
 * Return: The ACPI _UID field value or शून्य अगर the WMI GUID was not found
 */
अक्षर *wmi_get_acpi_device_uid(स्थिर अक्षर *guid_string)
अणु
	काष्ठा wmi_block *wblock = शून्य;

	अगर (!find_guid(guid_string, &wblock))
		वापस शून्य;

	वापस acpi_device_uid(wblock->acpi_device);
पूर्ण
EXPORT_SYMBOL_GPL(wmi_get_acpi_device_uid);

अटल काष्ठा wmi_block *dev_to_wblock(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा wmi_block, dev.dev);
पूर्ण

अटल काष्ठा wmi_device *dev_to_wdev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा wmi_device, dev);
पूर्ण

/*
 * sysfs पूर्णांकerface
 */
अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा wmi_block *wblock = dev_to_wblock(dev);

	वापस प्र_लिखो(buf, "wmi:%pUL\n", wblock->gblock.guid);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार guid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा wmi_block *wblock = dev_to_wblock(dev);

	वापस प्र_लिखो(buf, "%pUL\n", wblock->gblock.guid);
पूर्ण
अटल DEVICE_ATTR_RO(guid);

अटल sमाप_प्रकार instance_count_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wmi_block *wblock = dev_to_wblock(dev);

	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)wblock->gblock.instance_count);
पूर्ण
अटल DEVICE_ATTR_RO(instance_count);

अटल sमाप_प्रकार expensive_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wmi_block *wblock = dev_to_wblock(dev);

	वापस प्र_लिखो(buf, "%d\n",
		       (wblock->gblock.flags & ACPI_WMI_EXPENSIVE) != 0);
पूर्ण
अटल DEVICE_ATTR_RO(expensive);

अटल काष्ठा attribute *wmi_attrs[] = अणु
	&dev_attr_modalias.attr,
	&dev_attr_guid.attr,
	&dev_attr_instance_count.attr,
	&dev_attr_expensive.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(wmi);

अटल sमाप_प्रकार notअगरy_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा wmi_block *wblock = dev_to_wblock(dev);

	वापस प्र_लिखो(buf, "%02X\n", (अचिन्हित पूर्णांक)wblock->gblock.notअगरy_id);
पूर्ण
अटल DEVICE_ATTR_RO(notअगरy_id);

अटल काष्ठा attribute *wmi_event_attrs[] = अणु
	&dev_attr_notअगरy_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(wmi_event);

अटल sमाप_प्रकार object_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा wmi_block *wblock = dev_to_wblock(dev);

	वापस प्र_लिखो(buf, "%c%c\n", wblock->gblock.object_id[0],
		       wblock->gblock.object_id[1]);
पूर्ण
अटल DEVICE_ATTR_RO(object_id);

अटल sमाप_प्रकार setable_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा wmi_device *wdev = dev_to_wdev(dev);

	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)wdev->setable);
पूर्ण
अटल DEVICE_ATTR_RO(setable);

अटल काष्ठा attribute *wmi_data_attrs[] = अणु
	&dev_attr_object_id.attr,
	&dev_attr_setable.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(wmi_data);

अटल काष्ठा attribute *wmi_method_attrs[] = अणु
	&dev_attr_object_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(wmi_method);

अटल पूर्णांक wmi_dev_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा wmi_block *wblock = dev_to_wblock(dev);

	अगर (add_uevent_var(env, "MODALIAS=wmi:%pUL", wblock->gblock.guid))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "WMI_GUID=%pUL", wblock->gblock.guid))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम wmi_dev_release(काष्ठा device *dev)
अणु
	काष्ठा wmi_block *wblock = dev_to_wblock(dev);

	kमुक्त(wblock);
पूर्ण

अटल पूर्णांक wmi_dev_match(काष्ठा device *dev, काष्ठा device_driver *driver)
अणु
	काष्ठा wmi_driver *wmi_driver =
		container_of(driver, काष्ठा wmi_driver, driver);
	काष्ठा wmi_block *wblock = dev_to_wblock(dev);
	स्थिर काष्ठा wmi_device_id *id = wmi_driver->id_table;

	अगर (id == शून्य)
		वापस 0;

	जबतक (*id->guid_string) अणु
		guid_t driver_guid;

		अगर (WARN_ON(guid_parse(id->guid_string, &driver_guid)))
			जारी;
		अगर (!स_भेद(&driver_guid, wblock->gblock.guid, 16))
			वापस 1;

		id++;
	पूर्ण

	वापस 0;
पूर्ण
अटल पूर्णांक wmi_अक्षर_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	स्थिर अक्षर *driver_name = filp->f_path.dentry->d_iname;
	काष्ठा wmi_block *wblock = शून्य;
	काष्ठा wmi_block *next = शून्य;

	list_क्रम_each_entry_safe(wblock, next, &wmi_block_list, list) अणु
		अगर (!wblock->dev.dev.driver)
			जारी;
		अगर (म_भेद(driver_name, wblock->dev.dev.driver->name) == 0) अणु
			filp->निजी_data = wblock;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!filp->निजी_data)
		वापस -ENODEV;

	वापस nonseekable_खोलो(inode, filp);
पूर्ण

अटल sमाप_प्रकार wmi_अक्षर_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
	माप_प्रकार length, loff_t *offset)
अणु
	काष्ठा wmi_block *wblock = filp->निजी_data;

	वापस simple_पढ़ो_from_buffer(buffer, length, offset,
				       &wblock->req_buf_size,
				       माप(wblock->req_buf_size));
पूर्ण

अटल दीर्घ wmi_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा wmi_ioctl_buffer __user *input =
		(काष्ठा wmi_ioctl_buffer __user *) arg;
	काष्ठा wmi_block *wblock = filp->निजी_data;
	काष्ठा wmi_ioctl_buffer *buf = शून्य;
	काष्ठा wmi_driver *wdriver = शून्य;
	पूर्णांक ret;

	अगर (_IOC_TYPE(cmd) != WMI_IOC)
		वापस -ENOTTY;

	/* make sure we're not calling a higher instance than exists*/
	अगर (_IOC_NR(cmd) >= wblock->gblock.instance_count)
		वापस -EINVAL;

	mutex_lock(&wblock->अक्षर_mutex);
	buf = wblock->handler_data;
	अगर (get_user(buf->length, &input->length)) अणु
		dev_dbg(&wblock->dev.dev, "Read length from user failed\n");
		ret = -EFAULT;
		जाओ out_ioctl;
	पूर्ण
	/* अगर it's too small, पात */
	अगर (buf->length < wblock->req_buf_size) अणु
		dev_err(&wblock->dev.dev,
			"Buffer %lld too small, need at least %lld\n",
			buf->length, wblock->req_buf_size);
		ret = -EINVAL;
		जाओ out_ioctl;
	पूर्ण
	/* अगर it's too big, warn, driver will only use what is needed */
	अगर (buf->length > wblock->req_buf_size)
		dev_warn(&wblock->dev.dev,
			"Buffer %lld is bigger than required %lld\n",
			buf->length, wblock->req_buf_size);

	/* copy the काष्ठाure from userspace */
	अगर (copy_from_user(buf, input, wblock->req_buf_size)) अणु
		dev_dbg(&wblock->dev.dev, "Copy %llu from user failed\n",
			wblock->req_buf_size);
		ret = -EFAULT;
		जाओ out_ioctl;
	पूर्ण

	/* let the driver करो any filtering and करो the call */
	wdriver = container_of(wblock->dev.dev.driver,
			       काष्ठा wmi_driver, driver);
	अगर (!try_module_get(wdriver->driver.owner)) अणु
		ret = -EBUSY;
		जाओ out_ioctl;
	पूर्ण
	ret = wdriver->filter_callback(&wblock->dev, cmd, buf);
	module_put(wdriver->driver.owner);
	अगर (ret)
		जाओ out_ioctl;

	/* वापस the result (only up to our पूर्णांकernal buffer size) */
	अगर (copy_to_user(input, buf, wblock->req_buf_size)) अणु
		dev_dbg(&wblock->dev.dev, "Copy %llu to user failed\n",
			wblock->req_buf_size);
		ret = -EFAULT;
	पूर्ण

out_ioctl:
	mutex_unlock(&wblock->अक्षर_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations wmi_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= wmi_अक्षर_पढ़ो,
	.खोलो		= wmi_अक्षर_खोलो,
	.unlocked_ioctl	= wmi_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;

अटल पूर्णांक wmi_dev_probe(काष्ठा device *dev)
अणु
	काष्ठा wmi_block *wblock = dev_to_wblock(dev);
	काष्ठा wmi_driver *wdriver =
		container_of(dev->driver, काष्ठा wmi_driver, driver);
	पूर्णांक ret = 0;
	अक्षर *buf;

	अगर (ACPI_FAILURE(wmi_method_enable(wblock, 1)))
		dev_warn(dev, "failed to enable device -- probing anyway\n");

	अगर (wdriver->probe) अणु
		ret = wdriver->probe(dev_to_wdev(dev),
				find_guid_context(wblock, wdriver));
		अगर (ret != 0)
			जाओ probe_failure;
	पूर्ण

	/* driver wants a अक्षरacter device made */
	अगर (wdriver->filter_callback) अणु
		/* check that required buffer size declared by driver or MOF */
		अगर (!wblock->req_buf_size) अणु
			dev_err(&wblock->dev.dev,
				"Required buffer size not set\n");
			ret = -EINVAL;
			जाओ probe_failure;
		पूर्ण

		wblock->handler_data = kदो_स्मृति(wblock->req_buf_size,
					       GFP_KERNEL);
		अगर (!wblock->handler_data) अणु
			ret = -ENOMEM;
			जाओ probe_failure;
		पूर्ण

		buf = kaप्र_लिखो(GFP_KERNEL, "wmi/%s", wdriver->driver.name);
		अगर (!buf) अणु
			ret = -ENOMEM;
			जाओ probe_string_failure;
		पूर्ण
		wblock->अक्षर_dev.minor = MISC_DYNAMIC_MINOR;
		wblock->अक्षर_dev.name = buf;
		wblock->अक्षर_dev.fops = &wmi_fops;
		wblock->अक्षर_dev.mode = 0444;
		ret = misc_रेजिस्टर(&wblock->अक्षर_dev);
		अगर (ret) अणु
			dev_warn(dev, "failed to register char dev: %d\n", ret);
			ret = -ENOMEM;
			जाओ probe_misc_failure;
		पूर्ण
	पूर्ण

	वापस 0;

probe_misc_failure:
	kमुक्त(buf);
probe_string_failure:
	kमुक्त(wblock->handler_data);
probe_failure:
	अगर (ACPI_FAILURE(wmi_method_enable(wblock, 0)))
		dev_warn(dev, "failed to disable device\n");
	वापस ret;
पूर्ण

अटल पूर्णांक wmi_dev_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा wmi_block *wblock = dev_to_wblock(dev);
	काष्ठा wmi_driver *wdriver =
		container_of(dev->driver, काष्ठा wmi_driver, driver);

	अगर (wdriver->filter_callback) अणु
		misc_deरेजिस्टर(&wblock->अक्षर_dev);
		kमुक्त(wblock->अक्षर_dev.name);
		kमुक्त(wblock->handler_data);
	पूर्ण

	अगर (wdriver->हटाओ)
		wdriver->हटाओ(dev_to_wdev(dev));

	अगर (ACPI_FAILURE(wmi_method_enable(wblock, 0)))
		dev_warn(dev, "failed to disable device\n");

	वापस 0;
पूर्ण

अटल काष्ठा class wmi_bus_class = अणु
	.name = "wmi_bus",
पूर्ण;

अटल काष्ठा bus_type wmi_bus_type = अणु
	.name = "wmi",
	.dev_groups = wmi_groups,
	.match = wmi_dev_match,
	.uevent = wmi_dev_uevent,
	.probe = wmi_dev_probe,
	.हटाओ = wmi_dev_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा device_type wmi_type_event = अणु
	.name = "event",
	.groups = wmi_event_groups,
	.release = wmi_dev_release,
पूर्ण;

अटल स्थिर काष्ठा device_type wmi_type_method = अणु
	.name = "method",
	.groups = wmi_method_groups,
	.release = wmi_dev_release,
पूर्ण;

अटल स्थिर काष्ठा device_type wmi_type_data = अणु
	.name = "data",
	.groups = wmi_data_groups,
	.release = wmi_dev_release,
पूर्ण;

अटल पूर्णांक wmi_create_device(काष्ठा device *wmi_bus_dev,
			     स्थिर काष्ठा guid_block *gblock,
			     काष्ठा wmi_block *wblock,
			     काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_device_info *info;
	अक्षर method[5];
	पूर्णांक result;

	अगर (gblock->flags & ACPI_WMI_EVENT) अणु
		wblock->dev.dev.type = &wmi_type_event;
		जाओ out_init;
	पूर्ण

	अगर (gblock->flags & ACPI_WMI_METHOD) अणु
		wblock->dev.dev.type = &wmi_type_method;
		mutex_init(&wblock->अक्षर_mutex);
		जाओ out_init;
	पूर्ण

	/*
	 * Data Block Query Control Method (WQxx by convention) is
	 * required per the WMI करोcumentation. If it is not present,
	 * we ignore this data block.
	 */
	म_नकल(method, "WQ");
	म_जोड़न(method, wblock->gblock.object_id, 2);
	result = get_subobj_info(device->handle, method, &info);

	अगर (result) अणु
		dev_warn(wmi_bus_dev,
			 "%s data block query control method not found\n",
			 method);
		वापस result;
	पूर्ण

	wblock->dev.dev.type = &wmi_type_data;

	/*
	 * The Microsoft करोcumentation specअगरically states:
	 *
	 *   Data blocks रेजिस्टरed with only a single instance
	 *   can ignore the parameter.
	 *
	 * ACPICA will get mad at us अगर we call the method with the wrong number
	 * of arguments, so check what our method expects.  (On some Dell
	 * laptops, WQxx may not be a method at all.)
	 */
	अगर (info->type != ACPI_TYPE_METHOD || info->param_count == 0)
		wblock->पढ़ो_takes_no_args = true;

	kमुक्त(info);

	म_नकल(method, "WS");
	म_जोड़न(method, wblock->gblock.object_id, 2);
	result = get_subobj_info(device->handle, method, शून्य);

	अगर (result == 0)
		wblock->dev.setable = true;

 out_init:
	wblock->dev.dev.bus = &wmi_bus_type;
	wblock->dev.dev.parent = wmi_bus_dev;

	dev_set_name(&wblock->dev.dev, "%pUL", gblock->guid);

	device_initialize(&wblock->dev.dev);

	वापस 0;
पूर्ण

अटल व्योम wmi_मुक्त_devices(काष्ठा acpi_device *device)
अणु
	काष्ठा wmi_block *wblock, *next;

	/* Delete devices क्रम all the GUIDs */
	list_क्रम_each_entry_safe(wblock, next, &wmi_block_list, list) अणु
		अगर (wblock->acpi_device == device) अणु
			list_del(&wblock->list);
			device_unरेजिस्टर(&wblock->dev.dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool guid_alपढ़ोy_parsed(काष्ठा acpi_device *device, स्थिर u8 *guid)
अणु
	काष्ठा wmi_block *wblock;

	list_क्रम_each_entry(wblock, &wmi_block_list, list) अणु
		अगर (स_भेद(wblock->gblock.guid, guid, 16) == 0) अणु
			/*
			 * Because we historically didn't track the relationship
			 * between GUIDs and ACPI nodes, we करोn't know whether
			 * we need to suppress GUIDs that are unique on a
			 * given node but duplicated across nodes.
			 */
			dev_warn(&device->dev, "duplicate WMI GUID %pUL (first instance was on %s)\n",
				 guid, dev_name(&wblock->acpi_device->dev));
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/*
 * Parse the _WDG method क्रम the GUID data blocks
 */
अटल पूर्णांक parse_wdg(काष्ठा device *wmi_bus_dev, काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_buffer out = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	स्थिर काष्ठा guid_block *gblock;
	काष्ठा wmi_block *wblock, *next;
	जोड़ acpi_object *obj;
	acpi_status status;
	पूर्णांक retval = 0;
	u32 i, total;

	status = acpi_evaluate_object(device->handle, "_WDG", शून्य, &out);
	अगर (ACPI_FAILURE(status))
		वापस -ENXIO;

	obj = (जोड़ acpi_object *) out.poपूर्णांकer;
	अगर (!obj)
		वापस -ENXIO;

	अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		retval = -ENXIO;
		जाओ out_मुक्त_poपूर्णांकer;
	पूर्ण

	gblock = (स्थिर काष्ठा guid_block *)obj->buffer.poपूर्णांकer;
	total = obj->buffer.length / माप(काष्ठा guid_block);

	क्रम (i = 0; i < total; i++) अणु
		अगर (debug_dump_wdg)
			wmi_dump_wdg(&gblock[i]);

		/*
		 * Some WMI devices, like those क्रम nVidia hooks, have a
		 * duplicate GUID. It's not clear what we should करो in this
		 * हाल yet, so क्रम now, we'll just ignore the duplicate
		 * क्रम device creation.
		 */
		अगर (guid_alपढ़ोy_parsed(device, gblock[i].guid))
			जारी;

		wblock = kzalloc(माप(काष्ठा wmi_block), GFP_KERNEL);
		अगर (!wblock) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण

		wblock->acpi_device = device;
		wblock->gblock = gblock[i];

		retval = wmi_create_device(wmi_bus_dev, &gblock[i], wblock, device);
		अगर (retval) अणु
			kमुक्त(wblock);
			जारी;
		पूर्ण

		list_add_tail(&wblock->list, &wmi_block_list);

		अगर (debug_event) अणु
			wblock->handler = wmi_notअगरy_debug;
			wmi_method_enable(wblock, 1);
		पूर्ण
	पूर्ण

	/*
	 * Now that all of the devices are created, add them to the
	 * device tree and probe subdrivers.
	 */
	list_क्रम_each_entry_safe(wblock, next, &wmi_block_list, list) अणु
		अगर (wblock->acpi_device != device)
			जारी;

		retval = device_add(&wblock->dev.dev);
		अगर (retval) अणु
			dev_err(wmi_bus_dev, "failed to register %pUL\n",
				wblock->gblock.guid);
			अगर (debug_event)
				wmi_method_enable(wblock, 0);
			list_del(&wblock->list);
			put_device(&wblock->dev.dev);
		पूर्ण
	पूर्ण

out_मुक्त_poपूर्णांकer:
	kमुक्त(out.poपूर्णांकer);
	वापस retval;
पूर्ण

/*
 * WMI can have EmbeddedControl access regions. In which हाल, we just want to
 * hand these off to the EC driver.
 */
अटल acpi_status
acpi_wmi_ec_space_handler(u32 function, acpi_physical_address address,
		      u32 bits, u64 *value,
		      व्योम *handler_context, व्योम *region_context)
अणु
	पूर्णांक result = 0, i = 0;
	u8 temp = 0;

	अगर ((address > 0xFF) || !value)
		वापस AE_BAD_PARAMETER;

	अगर (function != ACPI_READ && function != ACPI_WRITE)
		वापस AE_BAD_PARAMETER;

	अगर (bits != 8)
		वापस AE_BAD_PARAMETER;

	अगर (function == ACPI_READ) अणु
		result = ec_पढ़ो(address, &temp);
		(*value) |= ((u64)temp) << i;
	पूर्ण अन्यथा अणु
		temp = 0xff & ((*value) >> i);
		result = ec_ग_लिखो(address, temp);
	पूर्ण

	चयन (result) अणु
	हाल -EINVAL:
		वापस AE_BAD_PARAMETER;
	हाल -ENODEV:
		वापस AE_NOT_FOUND;
	हाल -ETIME:
		वापस AE_TIME;
	शेष:
		वापस AE_OK;
	पूर्ण
पूर्ण

अटल व्योम acpi_wmi_notअगरy_handler(acpi_handle handle, u32 event,
				    व्योम *context)
अणु
	काष्ठा guid_block *block;
	काष्ठा wmi_block *wblock;
	bool found_it = false;

	list_क्रम_each_entry(wblock, &wmi_block_list, list) अणु
		block = &wblock->gblock;

		अगर (wblock->acpi_device->handle == handle &&
		    (block->flags & ACPI_WMI_EVENT) &&
		    (block->notअगरy_id == event))
		अणु
			found_it = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found_it)
		वापस;

	/* If a driver is bound, then notअगरy the driver. */
	अगर (wblock->dev.dev.driver) अणु
		काष्ठा wmi_driver *driver;
		काष्ठा acpi_object_list input;
		जोड़ acpi_object params[1];
		काष्ठा acpi_buffer evdata = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
		acpi_status status;

		driver = container_of(wblock->dev.dev.driver,
				      काष्ठा wmi_driver, driver);

		input.count = 1;
		input.poपूर्णांकer = params;
		params[0].type = ACPI_TYPE_INTEGER;
		params[0].पूर्णांकeger.value = event;

		status = acpi_evaluate_object(wblock->acpi_device->handle,
					      "_WED", &input, &evdata);
		अगर (ACPI_FAILURE(status)) अणु
			dev_warn(&wblock->dev.dev,
				 "failed to get event data\n");
			वापस;
		पूर्ण

		अगर (driver->notअगरy)
			driver->notअगरy(&wblock->dev,
				       (जोड़ acpi_object *)evdata.poपूर्णांकer);

		kमुक्त(evdata.poपूर्णांकer);
	पूर्ण अन्यथा अगर (wblock->handler) अणु
		/* Legacy handler */
		wblock->handler(event, wblock->handler_data);
	पूर्ण

	अगर (debug_event)
		pr_info("DEBUG Event GUID: %pUL\n", wblock->gblock.guid);

	acpi_bus_generate_netlink_event(
		wblock->acpi_device->pnp.device_class,
		dev_name(&wblock->dev.dev),
		event, 0);

पूर्ण

अटल पूर्णांक acpi_wmi_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा acpi_device *acpi_device = ACPI_COMPANION(&device->dev);

	acpi_हटाओ_notअगरy_handler(acpi_device->handle, ACPI_DEVICE_NOTIFY,
				   acpi_wmi_notअगरy_handler);
	acpi_हटाओ_address_space_handler(acpi_device->handle,
				ACPI_ADR_SPACE_EC, &acpi_wmi_ec_space_handler);
	wmi_मुक्त_devices(acpi_device);
	device_unरेजिस्टर((काष्ठा device *)dev_get_drvdata(&device->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_wmi_probe(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा acpi_device *acpi_device;
	काष्ठा device *wmi_bus_dev;
	acpi_status status;
	पूर्णांक error;

	acpi_device = ACPI_COMPANION(&device->dev);
	अगर (!acpi_device) अणु
		dev_err(&device->dev, "ACPI companion is missing\n");
		वापस -ENODEV;
	पूर्ण

	status = acpi_install_address_space_handler(acpi_device->handle,
						    ACPI_ADR_SPACE_EC,
						    &acpi_wmi_ec_space_handler,
						    शून्य, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&device->dev, "Error installing EC region handler\n");
		वापस -ENODEV;
	पूर्ण

	status = acpi_install_notअगरy_handler(acpi_device->handle,
					     ACPI_DEVICE_NOTIFY,
					     acpi_wmi_notअगरy_handler,
					     शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&device->dev, "Error installing notify handler\n");
		error = -ENODEV;
		जाओ err_हटाओ_ec_handler;
	पूर्ण

	wmi_bus_dev = device_create(&wmi_bus_class, &device->dev, MKDEV(0, 0),
				    शून्य, "wmi_bus-%s", dev_name(&device->dev));
	अगर (IS_ERR(wmi_bus_dev)) अणु
		error = PTR_ERR(wmi_bus_dev);
		जाओ err_हटाओ_notअगरy_handler;
	पूर्ण
	dev_set_drvdata(&device->dev, wmi_bus_dev);

	error = parse_wdg(wmi_bus_dev, acpi_device);
	अगर (error) अणु
		pr_err("Failed to parse WDG method\n");
		जाओ err_हटाओ_busdev;
	पूर्ण

	वापस 0;

err_हटाओ_busdev:
	device_unरेजिस्टर(wmi_bus_dev);

err_हटाओ_notअगरy_handler:
	acpi_हटाओ_notअगरy_handler(acpi_device->handle, ACPI_DEVICE_NOTIFY,
				   acpi_wmi_notअगरy_handler);

err_हटाओ_ec_handler:
	acpi_हटाओ_address_space_handler(acpi_device->handle,
					  ACPI_ADR_SPACE_EC,
					  &acpi_wmi_ec_space_handler);

	वापस error;
पूर्ण

पूर्णांक __must_check __wmi_driver_रेजिस्टर(काष्ठा wmi_driver *driver,
				       काष्ठा module *owner)
अणु
	driver->driver.owner = owner;
	driver->driver.bus = &wmi_bus_type;

	वापस driver_रेजिस्टर(&driver->driver);
पूर्ण
EXPORT_SYMBOL(__wmi_driver_रेजिस्टर);

व्योम wmi_driver_unरेजिस्टर(काष्ठा wmi_driver *driver)
अणु
	driver_unरेजिस्टर(&driver->driver);
पूर्ण
EXPORT_SYMBOL(wmi_driver_unरेजिस्टर);

अटल पूर्णांक __init acpi_wmi_init(व्योम)
अणु
	पूर्णांक error;

	अगर (acpi_disabled)
		वापस -ENODEV;

	error = class_रेजिस्टर(&wmi_bus_class);
	अगर (error)
		वापस error;

	error = bus_रेजिस्टर(&wmi_bus_type);
	अगर (error)
		जाओ err_unreg_class;

	error = platक्रमm_driver_रेजिस्टर(&acpi_wmi_driver);
	अगर (error) अणु
		pr_err("Error loading mapper\n");
		जाओ err_unreg_bus;
	पूर्ण

	वापस 0;

err_unreg_bus:
	bus_unरेजिस्टर(&wmi_bus_type);

err_unreg_class:
	class_unरेजिस्टर(&wmi_bus_class);

	वापस error;
पूर्ण

अटल व्योम __निकास acpi_wmi_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&acpi_wmi_driver);
	bus_unरेजिस्टर(&wmi_bus_type);
	class_unरेजिस्टर(&wmi_bus_class);
पूर्ण

subsys_initcall_sync(acpi_wmi_init);
module_निकास(acpi_wmi_निकास);
