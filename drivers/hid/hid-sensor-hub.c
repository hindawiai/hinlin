<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID Sensors Driver
 * Copyright (c) 2012, Intel Corporation.
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/list.h>
#समावेश <linux/hid-sensor-ids.h>
#समावेश <linux/hid-sensor-hub.h>
#समावेश "hid-ids.h"

#घोषणा HID_SENSOR_HUB_ENUM_QUIRK	0x01

/**
 * काष्ठा sensor_hub_data - Hold a instance data क्रम a HID hub device
 * @mutex:		Mutex to serialize synchronous request.
 * @lock:		Spin lock to protect pending request काष्ठाure.
 * @dyn_callback_list:	Holds callback function
 * @dyn_callback_lock:	spin lock to protect callback list
 * @hid_sensor_hub_client_devs:	Stores all MFD cells क्रम a hub instance.
 * @hid_sensor_client_cnt: Number of MFD cells, (no of sensors attached).
 * @ref_cnt:		Number of MFD clients have खोलोed this device
 */
काष्ठा sensor_hub_data अणु
	काष्ठा mutex mutex;
	spinlock_t lock;
	काष्ठा list_head dyn_callback_list;
	spinlock_t dyn_callback_lock;
	काष्ठा mfd_cell *hid_sensor_hub_client_devs;
	पूर्णांक hid_sensor_client_cnt;
	पूर्णांक ref_cnt;
पूर्ण;

/**
 * काष्ठा hid_sensor_hub_callbacks_list - Stores callback list
 * @list:		list head.
 * @usage_id:		usage id क्रम a physical device.
 * @hsdev:		Stored hid instance क्रम current hub device.
 * @usage_callback:	Stores रेजिस्टरed callback functions.
 * @priv:		Private data क्रम a physical device.
 */
काष्ठा hid_sensor_hub_callbacks_list अणु
	काष्ठा list_head list;
	u32 usage_id;
	काष्ठा hid_sensor_hub_device *hsdev;
	काष्ठा hid_sensor_hub_callbacks *usage_callback;
	व्योम *priv;
पूर्ण;

अटल काष्ठा hid_report *sensor_hub_report(पूर्णांक id, काष्ठा hid_device *hdev,
						पूर्णांक dir)
अणु
	काष्ठा hid_report *report;

	list_क्रम_each_entry(report, &hdev->report_क्रमागत[dir].report_list, list) अणु
		अगर (report->id == id)
			वापस report;
	पूर्ण
	hid_warn(hdev, "No report with id 0x%x found\n", id);

	वापस शून्य;
पूर्ण

अटल पूर्णांक sensor_hub_get_physical_device_count(काष्ठा hid_device *hdev)
अणु
	पूर्णांक i;
	पूर्णांक count = 0;

	क्रम (i = 0; i < hdev->maxcollection; ++i) अणु
		काष्ठा hid_collection *collection = &hdev->collection[i];
		अगर (collection->type == HID_COLLECTION_PHYSICAL ||
		    collection->type == HID_COLLECTION_APPLICATION)
			++count;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम sensor_hub_fill_attr_info(
		काष्ठा hid_sensor_hub_attribute_info *info,
		s32 index, s32 report_id, काष्ठा hid_field *field)
अणु
	info->index = index;
	info->report_id = report_id;
	info->units = field->unit;
	info->unit_expo = field->unit_exponent;
	info->size = (field->report_size * field->report_count)/8;
	info->logical_minimum = field->logical_minimum;
	info->logical_maximum = field->logical_maximum;
पूर्ण

अटल काष्ठा hid_sensor_hub_callbacks *sensor_hub_get_callback(
					काष्ठा hid_device *hdev,
					u32 usage_id,
					पूर्णांक collection_index,
					काष्ठा hid_sensor_hub_device **hsdev,
					व्योम **priv)
अणु
	काष्ठा hid_sensor_hub_callbacks_list *callback;
	काष्ठा sensor_hub_data *pdata = hid_get_drvdata(hdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->dyn_callback_lock, flags);
	list_क्रम_each_entry(callback, &pdata->dyn_callback_list, list)
		अगर ((callback->usage_id == usage_id ||
		     callback->usage_id == HID_USAGE_SENSOR_COLLECTION) &&
			(collection_index >=
				callback->hsdev->start_collection_index) &&
			(collection_index <
				callback->hsdev->end_collection_index)) अणु
			*priv = callback->priv;
			*hsdev = callback->hsdev;
			spin_unlock_irqrestore(&pdata->dyn_callback_lock,
					       flags);
			वापस callback->usage_callback;
		पूर्ण
	spin_unlock_irqrestore(&pdata->dyn_callback_lock, flags);

	वापस शून्य;
पूर्ण

पूर्णांक sensor_hub_रेजिस्टर_callback(काष्ठा hid_sensor_hub_device *hsdev,
			u32 usage_id,
			काष्ठा hid_sensor_hub_callbacks *usage_callback)
अणु
	काष्ठा hid_sensor_hub_callbacks_list *callback;
	काष्ठा sensor_hub_data *pdata = hid_get_drvdata(hsdev->hdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->dyn_callback_lock, flags);
	list_क्रम_each_entry(callback, &pdata->dyn_callback_list, list)
		अगर (callback->usage_id == usage_id &&
						callback->hsdev == hsdev) अणु
			spin_unlock_irqrestore(&pdata->dyn_callback_lock, flags);
			वापस -EINVAL;
		पूर्ण
	callback = kzalloc(माप(*callback), GFP_ATOMIC);
	अगर (!callback) अणु
		spin_unlock_irqrestore(&pdata->dyn_callback_lock, flags);
		वापस -ENOMEM;
	पूर्ण
	callback->hsdev = hsdev;
	callback->usage_callback = usage_callback;
	callback->usage_id = usage_id;
	callback->priv = शून्य;
	/*
	 * If there is a handler रेजिस्टरed क्रम the collection type, then
	 * it will handle all reports क्रम sensors in this collection. If
	 * there is also an inभागidual sensor handler registration, then
	 * we want to make sure that the reports are directed to collection
	 * handler, as this may be a fusion sensor. So add collection handlers
	 * to the beginning of the list, so that they are matched first.
	 */
	अगर (usage_id == HID_USAGE_SENSOR_COLLECTION)
		list_add(&callback->list, &pdata->dyn_callback_list);
	अन्यथा
		list_add_tail(&callback->list, &pdata->dyn_callback_list);
	spin_unlock_irqrestore(&pdata->dyn_callback_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sensor_hub_रेजिस्टर_callback);

पूर्णांक sensor_hub_हटाओ_callback(काष्ठा hid_sensor_hub_device *hsdev,
				u32 usage_id)
अणु
	काष्ठा hid_sensor_hub_callbacks_list *callback;
	काष्ठा sensor_hub_data *pdata = hid_get_drvdata(hsdev->hdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->dyn_callback_lock, flags);
	list_क्रम_each_entry(callback, &pdata->dyn_callback_list, list)
		अगर (callback->usage_id == usage_id &&
						callback->hsdev == hsdev) अणु
			list_del(&callback->list);
			kमुक्त(callback);
			अवरोध;
		पूर्ण
	spin_unlock_irqrestore(&pdata->dyn_callback_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sensor_hub_हटाओ_callback);

पूर्णांक sensor_hub_set_feature(काष्ठा hid_sensor_hub_device *hsdev, u32 report_id,
			   u32 field_index, पूर्णांक buffer_size, व्योम *buffer)
अणु
	काष्ठा hid_report *report;
	काष्ठा sensor_hub_data *data = hid_get_drvdata(hsdev->hdev);
	__s32 *buf32 = buffer;
	पूर्णांक i = 0;
	पूर्णांक reमुख्यing_bytes;
	__s32 value;
	पूर्णांक ret = 0;

	mutex_lock(&data->mutex);
	report = sensor_hub_report(report_id, hsdev->hdev, HID_FEATURE_REPORT);
	अगर (!report || (field_index >= report->maxfield)) अणु
		ret = -EINVAL;
		जाओ करोne_proc;
	पूर्ण

	reमुख्यing_bytes = buffer_size % माप(__s32);
	buffer_size = buffer_size / माप(__s32);
	अगर (buffer_size) अणु
		क्रम (i = 0; i < buffer_size; ++i) अणु
			ret = hid_set_field(report->field[field_index], i,
					    (__क्रमce __s32)cpu_to_le32(*buf32));
			अगर (ret)
				जाओ करोne_proc;

			++buf32;
		पूर्ण
	पूर्ण
	अगर (reमुख्यing_bytes) अणु
		value = 0;
		स_नकल(&value, (u8 *)buf32, reमुख्यing_bytes);
		ret = hid_set_field(report->field[field_index], i,
				    (__क्रमce __s32)cpu_to_le32(value));
		अगर (ret)
			जाओ करोne_proc;
	पूर्ण
	hid_hw_request(hsdev->hdev, report, HID_REQ_SET_REPORT);
	hid_hw_रुको(hsdev->hdev);

करोne_proc:
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sensor_hub_set_feature);

पूर्णांक sensor_hub_get_feature(काष्ठा hid_sensor_hub_device *hsdev, u32 report_id,
			   u32 field_index, पूर्णांक buffer_size, व्योम *buffer)
अणु
	काष्ठा hid_report *report;
	काष्ठा sensor_hub_data *data = hid_get_drvdata(hsdev->hdev);
	पूर्णांक report_size;
	पूर्णांक ret = 0;
	u8 *val_ptr;
	पूर्णांक buffer_index = 0;
	पूर्णांक i;

	स_रखो(buffer, 0, buffer_size);

	mutex_lock(&data->mutex);
	report = sensor_hub_report(report_id, hsdev->hdev, HID_FEATURE_REPORT);
	अगर (!report || (field_index >= report->maxfield) ||
	    report->field[field_index]->report_count < 1) अणु
		ret = -EINVAL;
		जाओ करोne_proc;
	पूर्ण
	hid_hw_request(hsdev->hdev, report, HID_REQ_GET_REPORT);
	hid_hw_रुको(hsdev->hdev);

	/* calculate number of bytes required to पढ़ो this field */
	report_size = DIV_ROUND_UP(report->field[field_index]->report_size,
				   8) *
				   report->field[field_index]->report_count;
	अगर (!report_size) अणु
		ret = -EINVAL;
		जाओ करोne_proc;
	पूर्ण
	ret = min(report_size, buffer_size);

	val_ptr = (u8 *)report->field[field_index]->value;
	क्रम (i = 0; i < report->field[field_index]->report_count; ++i) अणु
		अगर (buffer_index >= ret)
			अवरोध;

		स_नकल(&((u8 *)buffer)[buffer_index], val_ptr,
		       report->field[field_index]->report_size / 8);
		val_ptr += माप(__s32);
		buffer_index += (report->field[field_index]->report_size / 8);
	पूर्ण

करोne_proc:
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sensor_hub_get_feature);


पूर्णांक sensor_hub_input_attr_get_raw_value(काष्ठा hid_sensor_hub_device *hsdev,
					u32 usage_id,
					u32 attr_usage_id, u32 report_id,
					क्रमागत sensor_hub_पढ़ो_flags flag,
					bool is_चिन्हित)
अणु
	काष्ठा sensor_hub_data *data = hid_get_drvdata(hsdev->hdev);
	अचिन्हित दीर्घ flags;
	काष्ठा hid_report *report;
	पूर्णांक ret_val = 0;

	report = sensor_hub_report(report_id, hsdev->hdev,
				   HID_INPUT_REPORT);
	अगर (!report)
		वापस -EINVAL;

	mutex_lock(hsdev->mutex_ptr);
	अगर (flag == SENSOR_HUB_SYNC) अणु
		स_रखो(&hsdev->pending, 0, माप(hsdev->pending));
		init_completion(&hsdev->pending.पढ़ोy);
		hsdev->pending.usage_id = usage_id;
		hsdev->pending.attr_usage_id = attr_usage_id;
		hsdev->pending.raw_size = 0;

		spin_lock_irqsave(&data->lock, flags);
		hsdev->pending.status = true;
		spin_unlock_irqrestore(&data->lock, flags);
	पूर्ण
	mutex_lock(&data->mutex);
	hid_hw_request(hsdev->hdev, report, HID_REQ_GET_REPORT);
	mutex_unlock(&data->mutex);
	अगर (flag == SENSOR_HUB_SYNC) अणु
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(
						&hsdev->pending.पढ़ोy, HZ*5);
		चयन (hsdev->pending.raw_size) अणु
		हाल 1:
			अगर (is_चिन्हित)
				ret_val = *(s8 *)hsdev->pending.raw_data;
			अन्यथा
				ret_val = *(u8 *)hsdev->pending.raw_data;
			अवरोध;
		हाल 2:
			अगर (is_चिन्हित)
				ret_val = *(s16 *)hsdev->pending.raw_data;
			अन्यथा
				ret_val = *(u16 *)hsdev->pending.raw_data;
			अवरोध;
		हाल 4:
			ret_val = *(u32 *)hsdev->pending.raw_data;
			अवरोध;
		शेष:
			ret_val = 0;
		पूर्ण
		kमुक्त(hsdev->pending.raw_data);
		hsdev->pending.status = false;
	पूर्ण
	mutex_unlock(hsdev->mutex_ptr);

	वापस ret_val;
पूर्ण
EXPORT_SYMBOL_GPL(sensor_hub_input_attr_get_raw_value);

पूर्णांक hid_sensor_get_usage_index(काष्ठा hid_sensor_hub_device *hsdev,
				u32 report_id, पूर्णांक field_index, u32 usage_id)
अणु
	काष्ठा hid_report *report;
	काष्ठा hid_field *field;
	पूर्णांक i;

	report = sensor_hub_report(report_id, hsdev->hdev, HID_FEATURE_REPORT);
	अगर (!report || (field_index >= report->maxfield))
		जाओ करोne_proc;

	field = report->field[field_index];
	क्रम (i = 0; i < field->maxusage; ++i) अणु
		अगर (field->usage[i].hid == usage_id)
			वापस field->usage[i].usage_index;
	पूर्ण

करोne_proc:
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(hid_sensor_get_usage_index);

पूर्णांक sensor_hub_input_get_attribute_info(काष्ठा hid_sensor_hub_device *hsdev,
				u8 type,
				u32 usage_id,
				u32 attr_usage_id,
				काष्ठा hid_sensor_hub_attribute_info *info)
अणु
	पूर्णांक ret = -1;
	पूर्णांक i;
	काष्ठा hid_report *report;
	काष्ठा hid_field *field;
	काष्ठा hid_report_क्रमागत *report_क्रमागत;
	काष्ठा hid_device *hdev = hsdev->hdev;

	/* Initialize with शेषs */
	info->usage_id = usage_id;
	info->attrib_id = attr_usage_id;
	info->report_id = -1;
	info->index = -1;
	info->units = -1;
	info->unit_expo = -1;

	report_क्रमागत = &hdev->report_क्रमागत[type];
	list_क्रम_each_entry(report, &report_क्रमागत->report_list, list) अणु
		क्रम (i = 0; i < report->maxfield; ++i) अणु
			field = report->field[i];
			अगर (field->maxusage) अणु
				अगर (field->physical == usage_id &&
					(field->logical == attr_usage_id ||
					field->usage[0].hid ==
							attr_usage_id) &&
					(field->usage[0].collection_index >=
					hsdev->start_collection_index) &&
					(field->usage[0].collection_index <
					hsdev->end_collection_index)) अणु

					sensor_hub_fill_attr_info(info, i,
								report->id,
								field);
					ret = 0;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sensor_hub_input_get_attribute_info);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sensor_hub_suspend(काष्ठा hid_device *hdev, pm_message_t message)
अणु
	काष्ठा sensor_hub_data *pdata = hid_get_drvdata(hdev);
	काष्ठा hid_sensor_hub_callbacks_list *callback;
	अचिन्हित दीर्घ flags;

	hid_dbg(hdev, " sensor_hub_suspend\n");
	spin_lock_irqsave(&pdata->dyn_callback_lock, flags);
	list_क्रम_each_entry(callback, &pdata->dyn_callback_list, list) अणु
		अगर (callback->usage_callback->suspend)
			callback->usage_callback->suspend(
					callback->hsdev, callback->priv);
	पूर्ण
	spin_unlock_irqrestore(&pdata->dyn_callback_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sensor_hub_resume(काष्ठा hid_device *hdev)
अणु
	काष्ठा sensor_hub_data *pdata = hid_get_drvdata(hdev);
	काष्ठा hid_sensor_hub_callbacks_list *callback;
	अचिन्हित दीर्घ flags;

	hid_dbg(hdev, " sensor_hub_resume\n");
	spin_lock_irqsave(&pdata->dyn_callback_lock, flags);
	list_क्रम_each_entry(callback, &pdata->dyn_callback_list, list) अणु
		अगर (callback->usage_callback->resume)
			callback->usage_callback->resume(
					callback->hsdev, callback->priv);
	पूर्ण
	spin_unlock_irqrestore(&pdata->dyn_callback_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sensor_hub_reset_resume(काष्ठा hid_device *hdev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Handle raw report as sent by device
 */
अटल पूर्णांक sensor_hub_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *raw_data, पूर्णांक size)
अणु
	पूर्णांक i;
	u8 *ptr;
	पूर्णांक sz;
	काष्ठा sensor_hub_data *pdata = hid_get_drvdata(hdev);
	अचिन्हित दीर्घ flags;
	काष्ठा hid_sensor_hub_callbacks *callback = शून्य;
	काष्ठा hid_collection *collection = शून्य;
	व्योम *priv = शून्य;
	काष्ठा hid_sensor_hub_device *hsdev = शून्य;

	hid_dbg(hdev, "sensor_hub_raw_event report id:0x%x size:%d type:%d\n",
			 report->id, size, report->type);
	hid_dbg(hdev, "maxfield:%d\n", report->maxfield);
	अगर (report->type != HID_INPUT_REPORT)
		वापस 1;

	ptr = raw_data;
	अगर (report->id)
		ptr++; /* Skip report id */

	spin_lock_irqsave(&pdata->lock, flags);

	क्रम (i = 0; i < report->maxfield; ++i) अणु
		hid_dbg(hdev, "%d collection_index:%x hid:%x sz:%x\n",
				i, report->field[i]->usage->collection_index,
				report->field[i]->usage->hid,
				(report->field[i]->report_size *
					report->field[i]->report_count)/8);
		sz = (report->field[i]->report_size *
					report->field[i]->report_count)/8;
		collection = &hdev->collection[
				report->field[i]->usage->collection_index];
		hid_dbg(hdev, "collection->usage %x\n",
					collection->usage);

		callback = sensor_hub_get_callback(hdev,
				report->field[i]->physical,
				report->field[i]->usage[0].collection_index,
				&hsdev, &priv);
		अगर (!callback) अणु
			ptr += sz;
			जारी;
		पूर्ण
		अगर (hsdev->pending.status && (hsdev->pending.attr_usage_id ==
					      report->field[i]->usage->hid ||
					      hsdev->pending.attr_usage_id ==
					      report->field[i]->logical)) अणु
			hid_dbg(hdev, "data was pending ...\n");
			hsdev->pending.raw_data = kmemdup(ptr, sz, GFP_ATOMIC);
			अगर (hsdev->pending.raw_data)
				hsdev->pending.raw_size = sz;
			अन्यथा
				hsdev->pending.raw_size = 0;
			complete(&hsdev->pending.पढ़ोy);
		पूर्ण
		अगर (callback->capture_sample) अणु
			अगर (report->field[i]->logical)
				callback->capture_sample(hsdev,
					report->field[i]->logical, sz, ptr,
					callback->pdev);
			अन्यथा
				callback->capture_sample(hsdev,
					report->field[i]->usage->hid, sz, ptr,
					callback->pdev);
		पूर्ण
		ptr += sz;
	पूर्ण
	अगर (callback && collection && callback->send_event)
		callback->send_event(hsdev, collection->usage,
				callback->pdev);
	spin_unlock_irqrestore(&pdata->lock, flags);

	वापस 1;
पूर्ण

पूर्णांक sensor_hub_device_खोलो(काष्ठा hid_sensor_hub_device *hsdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा sensor_hub_data *data =  hid_get_drvdata(hsdev->hdev);

	mutex_lock(&data->mutex);
	अगर (!data->ref_cnt) अणु
		ret = hid_hw_खोलो(hsdev->hdev);
		अगर (ret) अणु
			hid_err(hsdev->hdev, "failed to open hid device\n");
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण
	पूर्ण
	data->ref_cnt++;
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sensor_hub_device_खोलो);

व्योम sensor_hub_device_बंद(काष्ठा hid_sensor_hub_device *hsdev)
अणु
	काष्ठा sensor_hub_data *data =  hid_get_drvdata(hsdev->hdev);

	mutex_lock(&data->mutex);
	data->ref_cnt--;
	अगर (!data->ref_cnt)
		hid_hw_बंद(hsdev->hdev);
	mutex_unlock(&data->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(sensor_hub_device_बंद);

अटल __u8 *sensor_hub_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	/*
	 * Checks अगर the report descriptor of Thinkpad Helix 2 has a logical
	 * minimum क्रम magnetic flux axis greater than the maximum.
	 */
	अगर (hdev->product == USB_DEVICE_ID_TEXAS_INSTRUMENTS_LENOVO_YOGA &&
		*rsize == 2558 && rdesc[913] == 0x17 && rdesc[914] == 0x40 &&
		rdesc[915] == 0x81 && rdesc[916] == 0x08 &&
		rdesc[917] == 0x00 && rdesc[918] == 0x27 &&
		rdesc[921] == 0x07 && rdesc[922] == 0x00) अणु
		/* Sets negative logical minimum क्रम mag x, y and z */
		rdesc[914] = rdesc[935] = rdesc[956] = 0xc0;
		rdesc[915] = rdesc[936] = rdesc[957] = 0x7e;
		rdesc[916] = rdesc[937] = rdesc[958] = 0xf7;
		rdesc[917] = rdesc[938] = rdesc[959] = 0xff;
	पूर्ण

	वापस rdesc;
पूर्ण

अटल पूर्णांक sensor_hub_probe(काष्ठा hid_device *hdev,
				स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा sensor_hub_data *sd;
	पूर्णांक i;
	अक्षर *name;
	पूर्णांक dev_cnt;
	काष्ठा hid_sensor_hub_device *hsdev;
	काष्ठा hid_sensor_hub_device *last_hsdev = शून्य;
	काष्ठा hid_sensor_hub_device *collection_hsdev = शून्य;

	sd = devm_kzalloc(&hdev->dev, माप(*sd), GFP_KERNEL);
	अगर (!sd) अणु
		hid_err(hdev, "cannot allocate Sensor data\n");
		वापस -ENOMEM;
	पूर्ण

	hid_set_drvdata(hdev, sd);

	spin_lock_init(&sd->lock);
	spin_lock_init(&sd->dyn_callback_lock);
	mutex_init(&sd->mutex);
	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		वापस ret;
	पूर्ण
	INIT_LIST_HEAD(&hdev->inमाला_दो);

	ret = hid_hw_start(hdev, 0);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		वापस ret;
	पूर्ण
	INIT_LIST_HEAD(&sd->dyn_callback_list);
	sd->hid_sensor_client_cnt = 0;

	dev_cnt = sensor_hub_get_physical_device_count(hdev);
	अगर (dev_cnt > HID_MAX_PHY_DEVICES) अणु
		hid_err(hdev, "Invalid Physical device count\n");
		ret = -EINVAL;
		जाओ err_stop_hw;
	पूर्ण
	sd->hid_sensor_hub_client_devs = devm_kसुस्मृति(&hdev->dev,
						      dev_cnt,
						      माप(काष्ठा mfd_cell),
						      GFP_KERNEL);
	अगर (sd->hid_sensor_hub_client_devs == शून्य) अणु
		hid_err(hdev, "Failed to allocate memory for mfd cells\n");
		ret = -ENOMEM;
		जाओ err_stop_hw;
	पूर्ण

	क्रम (i = 0; i < hdev->maxcollection; ++i) अणु
		काष्ठा hid_collection *collection = &hdev->collection[i];

		अगर (collection->type == HID_COLLECTION_PHYSICAL ||
		    collection->type == HID_COLLECTION_APPLICATION) अणु

			hsdev = devm_kzalloc(&hdev->dev, माप(*hsdev),
					     GFP_KERNEL);
			अगर (!hsdev) अणु
				hid_err(hdev, "cannot allocate hid_sensor_hub_device\n");
				ret = -ENOMEM;
				जाओ err_stop_hw;
			पूर्ण
			hsdev->hdev = hdev;
			hsdev->venकरोr_id = hdev->venकरोr;
			hsdev->product_id = hdev->product;
			hsdev->usage = collection->usage;
			hsdev->mutex_ptr = devm_kzalloc(&hdev->dev,
							माप(काष्ठा mutex),
							GFP_KERNEL);
			अगर (!hsdev->mutex_ptr) अणु
				ret = -ENOMEM;
				जाओ err_stop_hw;
			पूर्ण
			mutex_init(hsdev->mutex_ptr);
			hsdev->start_collection_index = i;
			अगर (last_hsdev)
				last_hsdev->end_collection_index = i;
			last_hsdev = hsdev;
			name = devm_kaप्र_लिखो(&hdev->dev, GFP_KERNEL,
					      "HID-SENSOR-%x",
					      collection->usage);
			अगर (name == शून्य) अणु
				hid_err(hdev, "Failed MFD device name\n");
				ret = -ENOMEM;
				जाओ err_stop_hw;
			पूर्ण
			sd->hid_sensor_hub_client_devs[
				sd->hid_sensor_client_cnt].name = name;
			sd->hid_sensor_hub_client_devs[
				sd->hid_sensor_client_cnt].platक्रमm_data =
							hsdev;
			sd->hid_sensor_hub_client_devs[
				sd->hid_sensor_client_cnt].pdata_size =
							माप(*hsdev);
			hid_dbg(hdev, "Adding %s:%d\n", name,
					hsdev->start_collection_index);
			sd->hid_sensor_client_cnt++;
			अगर (collection_hsdev)
				collection_hsdev->end_collection_index = i;
			अगर (collection->type == HID_COLLECTION_APPLICATION &&
			    collection->usage == HID_USAGE_SENSOR_COLLECTION)
				collection_hsdev = hsdev;
		पूर्ण
	पूर्ण
	अगर (last_hsdev)
		last_hsdev->end_collection_index = i;
	अगर (collection_hsdev)
		collection_hsdev->end_collection_index = i;

	ret = mfd_add_hotplug_devices(&hdev->dev,
			sd->hid_sensor_hub_client_devs,
			sd->hid_sensor_client_cnt);
	अगर (ret < 0)
		जाओ err_stop_hw;

	वापस ret;

err_stop_hw:
	hid_hw_stop(hdev);

	वापस ret;
पूर्ण

अटल व्योम sensor_hub_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा sensor_hub_data *data = hid_get_drvdata(hdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	hid_dbg(hdev, " hardware removed\n");
	hid_hw_बंद(hdev);
	hid_hw_stop(hdev);
	spin_lock_irqsave(&data->lock, flags);
	क्रम (i = 0; i < data->hid_sensor_client_cnt; ++i) अणु
		काष्ठा hid_sensor_hub_device *hsdev =
			data->hid_sensor_hub_client_devs[i].platक्रमm_data;
		अगर (hsdev->pending.status)
			complete(&hsdev->pending.पढ़ोy);
	पूर्ण
	spin_unlock_irqrestore(&data->lock, flags);
	mfd_हटाओ_devices(&hdev->dev);
	mutex_destroy(&data->mutex);
पूर्ण

अटल स्थिर काष्ठा hid_device_id sensor_hub_devices[] = अणु
	अणु HID_DEVICE(HID_BUS_ANY, HID_GROUP_SENSOR_HUB, HID_ANY_ID,
		     HID_ANY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, sensor_hub_devices);

अटल काष्ठा hid_driver sensor_hub_driver = अणु
	.name = "hid-sensor-hub",
	.id_table = sensor_hub_devices,
	.probe = sensor_hub_probe,
	.हटाओ = sensor_hub_हटाओ,
	.raw_event = sensor_hub_raw_event,
	.report_fixup = sensor_hub_report_fixup,
#अगर_घोषित CONFIG_PM
	.suspend = sensor_hub_suspend,
	.resume = sensor_hub_resume,
	.reset_resume = sensor_hub_reset_resume,
#पूर्ण_अगर
पूर्ण;
module_hid_driver(sensor_hub_driver);

MODULE_DESCRIPTION("HID Sensor Hub driver");
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@intel.com>");
MODULE_LICENSE("GPL");
