<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/input/tablet/wacom_sys.c
 *
 *  USB Wacom tablet support - प्रणाली specअगरic code
 */

/*
 */

#समावेश "wacom_wac.h"
#समावेश "wacom.h"
#समावेश <linux/input/mt.h>

#घोषणा WAC_MSG_RETRIES		5
#घोषणा WAC_CMD_RETRIES		10

#घोषणा DEV_ATTR_RW_PERM (S_IRUGO | S_IWUSR | S_IWGRP)
#घोषणा DEV_ATTR_WO_PERM (S_IWUSR | S_IWGRP)
#घोषणा DEV_ATTR_RO_PERM (S_IRUSR | S_IRGRP)

अटल पूर्णांक wacom_get_report(काष्ठा hid_device *hdev, u8 type, u8 *buf,
			    माप_प्रकार size, अचिन्हित पूर्णांक retries)
अणु
	पूर्णांक retval;

	करो अणु
		retval = hid_hw_raw_request(hdev, buf[0], buf, size, type,
				HID_REQ_GET_REPORT);
	पूर्ण जबतक ((retval == -ETIMEDOUT || retval == -EAGAIN) && --retries);

	अगर (retval < 0)
		hid_err(hdev, "wacom_get_report: ran out of retries "
			"(last error = %d)\n", retval);

	वापस retval;
पूर्ण

अटल पूर्णांक wacom_set_report(काष्ठा hid_device *hdev, u8 type, u8 *buf,
			    माप_प्रकार size, अचिन्हित पूर्णांक retries)
अणु
	पूर्णांक retval;

	करो अणु
		retval = hid_hw_raw_request(hdev, buf[0], buf, size, type,
				HID_REQ_SET_REPORT);
	पूर्ण जबतक ((retval == -ETIMEDOUT || retval == -EAGAIN) && --retries);

	अगर (retval < 0)
		hid_err(hdev, "wacom_set_report: ran out of retries "
			"(last error = %d)\n", retval);

	वापस retval;
पूर्ण

अटल व्योम wacom_wac_queue_insert(काष्ठा hid_device *hdev,
				   काष्ठा kfअगरo_rec_ptr_2 *fअगरo,
				   u8 *raw_data, पूर्णांक size)
अणु
	bool warned = false;

	जबतक (kfअगरo_avail(fअगरo) < size) अणु
		अगर (!warned)
			hid_warn(hdev, "%s: kfifo has filled, starting to drop events\n", __func__);
		warned = true;

		kfअगरo_skip(fअगरo);
	पूर्ण

	kfअगरo_in(fअगरo, raw_data, size);
पूर्ण

अटल व्योम wacom_wac_queue_flush(काष्ठा hid_device *hdev,
				  काष्ठा kfअगरo_rec_ptr_2 *fअगरo)
अणु
	जबतक (!kfअगरo_is_empty(fअगरo)) अणु
		u8 buf[WACOM_PKGLEN_MAX];
		पूर्णांक size;
		पूर्णांक err;

		size = kfअगरo_out(fअगरo, buf, माप(buf));
		err = hid_report_raw_event(hdev, HID_INPUT_REPORT, buf, size, false);
		अगर (err) अणु
			hid_warn(hdev, "%s: unable to flush event due to error %d\n",
				 __func__, err);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक wacom_wac_pen_serial_enक्रमce(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *raw_data, पूर्णांक report_size)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom_wac->features;
	bool flush = false;
	bool insert = false;
	पूर्णांक i, j;

	अगर (wacom_wac->serial[0] || !(features->quirks & WACOM_QUIRK_TOOLSERIAL))
		वापस 0;

	/* Queue events which have invalid tool type or serial number */
	क्रम (i = 0; i < report->maxfield; i++) अणु
		क्रम (j = 0; j < report->field[i]->maxusage; j++) अणु
			काष्ठा hid_field *field = report->field[i];
			काष्ठा hid_usage *usage = &field->usage[j];
			अचिन्हित पूर्णांक equivalent_usage = wacom_equivalent_usage(usage->hid);
			अचिन्हित पूर्णांक offset;
			अचिन्हित पूर्णांक size;
			अचिन्हित पूर्णांक value;

			अगर (equivalent_usage != HID_DG_INRANGE &&
			    equivalent_usage != HID_DG_TOOLSERIALNUMBER &&
			    equivalent_usage != WACOM_HID_WD_SERIALHI &&
			    equivalent_usage != WACOM_HID_WD_TOOLTYPE)
				जारी;

			offset = field->report_offset;
			size = field->report_size;
			value = hid_field_extract(hdev, raw_data+1, offset + j * size, size);

			/* If we go out of range, we need to flush the queue ASAP */
			अगर (equivalent_usage == HID_DG_INRANGE)
				value = !value;

			अगर (value) अणु
				flush = true;
				चयन (equivalent_usage) अणु
				हाल HID_DG_TOOLSERIALNUMBER:
					wacom_wac->serial[0] = value;
					अवरोध;

				हाल WACOM_HID_WD_SERIALHI:
					wacom_wac->serial[0] |= ((__u64)value) << 32;
					अवरोध;

				हाल WACOM_HID_WD_TOOLTYPE:
					wacom_wac->id[0] = value;
					अवरोध;
				पूर्ण
			पूर्ण
			अन्यथा अणु
				insert = true;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (flush)
		wacom_wac_queue_flush(hdev, wacom_wac->pen_fअगरo);
	अन्यथा अगर (insert)
		wacom_wac_queue_insert(hdev, wacom_wac->pen_fअगरo,
				       raw_data, report_size);

	वापस insert && !flush;
पूर्ण

अटल पूर्णांक wacom_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *raw_data, पूर्णांक size)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);

	अगर (size > WACOM_PKGLEN_MAX)
		वापस 1;

	अगर (wacom_wac_pen_serial_enक्रमce(hdev, report, raw_data, size))
		वापस -1;

	स_नकल(wacom->wacom_wac.data, raw_data, size);

	wacom_wac_irq(&wacom->wacom_wac, size);

	वापस 0;
पूर्ण

अटल पूर्णांक wacom_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा wacom *wacom = input_get_drvdata(dev);

	वापस hid_hw_खोलो(wacom->hdev);
पूर्ण

अटल व्योम wacom_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा wacom *wacom = input_get_drvdata(dev);

	/*
	 * wacom->hdev should never be null, but surprisingly, I had the हाल
	 * once जबतक unplugging the Wacom Wireless Receiver.
	 */
	अगर (wacom->hdev)
		hid_hw_बंद(wacom->hdev);
पूर्ण

/*
 * Calculate the resolution of the X or Y axis using hidinput_calc_असल_res.
 */
अटल पूर्णांक wacom_calc_hid_res(पूर्णांक logical_extents, पूर्णांक physical_extents,
			       अचिन्हित unit, पूर्णांक exponent)
अणु
	काष्ठा hid_field field = अणु
		.logical_maximum = logical_extents,
		.physical_maximum = physical_extents,
		.unit = unit,
		.unit_exponent = exponent,
	पूर्ण;

	वापस hidinput_calc_असल_res(&field, ABS_X);
पूर्ण

अटल व्योम wacom_hid_usage_quirk(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_features *features = &wacom->wacom_wac.features;
	अचिन्हित पूर्णांक equivalent_usage = wacom_equivalent_usage(usage->hid);

	/*
	 * The Dell Canvas 27 needs to be चयनed to its venकरोr-defined
	 * report to provide the best resolution.
	 */
	अगर (hdev->venकरोr == USB_VENDOR_ID_WACOM &&
	    hdev->product == 0x4200 &&
	    field->application == HID_UP_MSVENDOR) अणु
		wacom->wacom_wac.mode_report = field->report->id;
		wacom->wacom_wac.mode_value = 2;
	पूर्ण

	/*
	 * ISDv4 devices which predate HID's aकरोption of the
	 * HID_DG_BARELSWITCH2 usage use 0x000D0000 in its
	 * position instead. We can accurately detect अगर a
	 * usage with that value should be HID_DG_BARRELSWITCH2
	 * based on the surrounding usages, which have reमुख्यed
	 * स्थिरant across generations.
	 */
	अगर (features->type == HID_GENERIC &&
	    usage->hid == 0x000D0000 &&
	    field->application == HID_DG_PEN &&
	    field->physical == HID_DG_STYLUS) अणु
		पूर्णांक i = usage->usage_index;

		अगर (i-4 >= 0 && i+1 < field->maxusage &&
		    field->usage[i-4].hid == HID_DG_TIPSWITCH &&
		    field->usage[i-3].hid == HID_DG_BARRELSWITCH &&
		    field->usage[i-2].hid == HID_DG_ERASER &&
		    field->usage[i-1].hid == HID_DG_INVERT &&
		    field->usage[i+1].hid == HID_DG_INRANGE) अणु
			usage->hid = HID_DG_BARRELSWITCH2;
		पूर्ण
	पूर्ण

	/*
	 * Wacom's AES devices use dअगरferent venकरोr-defined usages to
	 * report serial number inक्रमmation compared to their bअक्रमed
	 * hardware. The usages are also someबार ill-defined and करो
	 * not have the correct logical min/max values set. Lets patch
	 * the descriptor to use the bअक्रमed usage convention and fix
	 * the errors.
	 */
	अगर (usage->hid == WACOM_HID_WT_SERIALNUMBER &&
	    field->report_size == 16 &&
	    field->index + 2 < field->report->maxfield) अणु
		काष्ठा hid_field *a = field->report->field[field->index + 1];
		काष्ठा hid_field *b = field->report->field[field->index + 2];

		अगर (a->maxusage > 0 &&
		    a->usage[0].hid == HID_DG_TOOLSERIALNUMBER &&
		    a->report_size == 32 &&
		    b->maxusage > 0 &&
		    b->usage[0].hid == 0xFF000000 &&
		    b->report_size == 8) अणु
			features->quirks |= WACOM_QUIRK_AESPEN;
			usage->hid = WACOM_HID_WD_TOOLTYPE;
			field->logical_minimum = S16_MIN;
			field->logical_maximum = S16_MAX;
			a->logical_minimum = S32_MIN;
			a->logical_maximum = S32_MAX;
			b->usage[0].hid = WACOM_HID_WD_SERIALHI;
			b->logical_minimum = 0;
			b->logical_maximum = U8_MAX;
		पूर्ण
	पूर्ण

	/* 2nd-generation Intuos Pro Large has incorrect Y maximum */
	अगर (hdev->venकरोr == USB_VENDOR_ID_WACOM &&
	    hdev->product == 0x0358 &&
	    WACOM_PEN_FIELD(field) &&
	    equivalent_usage == HID_GD_Y) अणु
		field->logical_maximum = 43200;
	पूर्ण
पूर्ण

अटल व्योम wacom_feature_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_features *features = &wacom->wacom_wac.features;
	काष्ठा hid_data *hid_data = &wacom->wacom_wac.hid_data;
	अचिन्हित पूर्णांक equivalent_usage = wacom_equivalent_usage(usage->hid);
	u8 *data;
	पूर्णांक ret;
	u32 n;

	wacom_hid_usage_quirk(hdev, field, usage);

	चयन (equivalent_usage) अणु
	हाल WACOM_HID_WD_TOUCH_RING_SETTING:
		wacom->generic_has_leds = true;
		अवरोध;
	हाल HID_DG_CONTACTMAX:
		/* leave touch_max as is अगर predefined */
		अगर (!features->touch_max) अणु
			/* पढ़ो manually */
			n = hid_report_len(field->report);
			data = hid_alloc_report_buf(field->report, GFP_KERNEL);
			अगर (!data)
				अवरोध;
			data[0] = field->report->id;
			ret = wacom_get_report(hdev, HID_FEATURE_REPORT,
					       data, n, WAC_CMD_RETRIES);
			अगर (ret == n && features->type == HID_GENERIC) अणु
				ret = hid_report_raw_event(hdev,
					HID_FEATURE_REPORT, data, n, 0);
			पूर्ण अन्यथा अगर (ret == 2 && features->type != HID_GENERIC) अणु
				features->touch_max = data[1];
			पूर्ण अन्यथा अणु
				features->touch_max = 16;
				hid_warn(hdev, "wacom_feature_mapping: "
					 "could not get HID_DG_CONTACTMAX, "
					 "defaulting to %d\n",
					  features->touch_max);
			पूर्ण
			kमुक्त(data);
		पूर्ण
		अवरोध;
	हाल HID_DG_INPUTMODE:
		/* Ignore अगर value index is out of bounds. */
		अगर (usage->usage_index >= field->report_count) अणु
			dev_err(&hdev->dev, "HID_DG_INPUTMODE out of range\n");
			अवरोध;
		पूर्ण

		hid_data->inpuपंचांगode = field->report->id;
		hid_data->inpuपंचांगode_index = usage->usage_index;
		अवरोध;

	हाल HID_UP_DIGITIZER:
		अगर (field->report->id == 0x0B &&
		    (field->application == WACOM_HID_G9_PEN ||
		     field->application == WACOM_HID_G11_PEN)) अणु
			wacom->wacom_wac.mode_report = field->report->id;
			wacom->wacom_wac.mode_value = 0;
		पूर्ण
		अवरोध;

	हाल WACOM_HID_WD_DATAMODE:
		wacom->wacom_wac.mode_report = field->report->id;
		wacom->wacom_wac.mode_value = 2;
		अवरोध;

	हाल WACOM_HID_UP_G9:
	हाल WACOM_HID_UP_G11:
		अगर (field->report->id == 0x03 &&
		    (field->application == WACOM_HID_G9_TOUCHSCREEN ||
		     field->application == WACOM_HID_G11_TOUCHSCREEN)) अणु
			wacom->wacom_wac.mode_report = field->report->id;
			wacom->wacom_wac.mode_value = 0;
		पूर्ण
		अवरोध;
	हाल WACOM_HID_WD_OFFSETLEFT:
	हाल WACOM_HID_WD_OFFSETTOP:
	हाल WACOM_HID_WD_OFFSETRIGHT:
	हाल WACOM_HID_WD_OFFSETBOTTOM:
		/* पढ़ो manually */
		n = hid_report_len(field->report);
		data = hid_alloc_report_buf(field->report, GFP_KERNEL);
		अगर (!data)
			अवरोध;
		data[0] = field->report->id;
		ret = wacom_get_report(hdev, HID_FEATURE_REPORT,
					data, n, WAC_CMD_RETRIES);
		अगर (ret == n) अणु
			ret = hid_report_raw_event(hdev, HID_FEATURE_REPORT,
						   data, n, 0);
		पूर्ण अन्यथा अणु
			hid_warn(hdev, "%s: could not retrieve sensor offsets\n",
				 __func__);
		पूर्ण
		kमुक्त(data);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Interface Descriptor of wacom devices can be incomplete and
 * inconsistent so wacom_features table is used to store stylus
 * device's packet lengths, various maximum values, and tablet
 * resolution based on product ID's.
 *
 * For devices that contain 2 पूर्णांकerfaces, wacom_features table is
 * inaccurate क्रम the touch पूर्णांकerface.  Since the Interface Descriptor
 * क्रम touch पूर्णांकerfaces has pretty complete data, this function exists
 * to query tablet क्रम this missing inक्रमmation instead of hard coding in
 * an additional table.
 *
 * A typical Interface Descriptor क्रम a stylus will contain a
 * boot mouse application collection that is not of पूर्णांकerest and this
 * function will ignore it.
 *
 * It also contains a digitizer application collection that also is not
 * of पूर्णांकerest since any inक्रमmation it contains would be duplicate
 * of what is in wacom_features. Usually it defines a report of an array
 * of bytes that could be used as max length of the stylus packet वापसed.
 * If it happens to define a Digitizer-Stylus Physical Collection then
 * the X and Y logical values contain valid data but it is ignored.
 *
 * A typical Interface Descriptor क्रम a touch पूर्णांकerface will contain a
 * Digitizer-Finger Physical Collection which will define both logical
 * X/Y maximum as well as the physical size of tablet. Since touch
 * पूर्णांकerfaces haven't supported pressure or distance, this is enough
 * inक्रमmation to override invalid values in the wacom_features table.
 *
 * Intuos5 touch पूर्णांकerface and 3rd gen Bamboo Touch करो not contain useful
 * data. We deal with them after वापसing from this function.
 */
अटल व्योम wacom_usage_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_features *features = &wacom->wacom_wac.features;
	bool finger = WACOM_FINGER_FIELD(field);
	bool pen = WACOM_PEN_FIELD(field);
	अचिन्हित equivalent_usage = wacom_equivalent_usage(usage->hid);

	/*
	* Requiring Stylus Usage will ignore boot mouse
	* X/Y values and some हालs of invalid Digitizer X/Y
	* values commonly reported.
	*/
	अगर (pen)
		features->device_type |= WACOM_DEVICETYPE_PEN;
	अन्यथा अगर (finger)
		features->device_type |= WACOM_DEVICETYPE_TOUCH;
	अन्यथा
		वापस;

	wacom_hid_usage_quirk(hdev, field, usage);

	चयन (equivalent_usage) अणु
	हाल HID_GD_X:
		features->x_max = field->logical_maximum;
		अगर (finger) अणु
			features->x_phy = field->physical_maximum;
			अगर ((features->type != BAMBOO_PT) &&
			    (features->type != BAMBOO_TOUCH)) अणु
				features->unit = field->unit;
				features->unitExpo = field->unit_exponent;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HID_GD_Y:
		features->y_max = field->logical_maximum;
		अगर (finger) अणु
			features->y_phy = field->physical_maximum;
			अगर ((features->type != BAMBOO_PT) &&
			    (features->type != BAMBOO_TOUCH)) अणु
				features->unit = field->unit;
				features->unitExpo = field->unit_exponent;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HID_DG_TIPPRESSURE:
		अगर (pen)
			features->pressure_max = field->logical_maximum;
		अवरोध;
	पूर्ण

	अगर (features->type == HID_GENERIC)
		wacom_wac_usage_mapping(hdev, field, usage);
पूर्ण

अटल व्योम wacom_post_parse_hid(काष्ठा hid_device *hdev,
				 काष्ठा wacom_features *features)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;

	अगर (features->type == HID_GENERIC) अणु
		/* Any last-minute generic device setup */
		अगर (wacom_wac->has_mode_change) अणु
			अगर (wacom_wac->is_direct_mode)
				features->device_type |= WACOM_DEVICETYPE_सूचीECT;
			अन्यथा
				features->device_type &= ~WACOM_DEVICETYPE_सूचीECT;
		पूर्ण

		अगर (features->touch_max > 1) अणु
			अगर (features->device_type & WACOM_DEVICETYPE_सूचीECT)
				input_mt_init_slots(wacom_wac->touch_input,
						    wacom_wac->features.touch_max,
						    INPUT_MT_सूचीECT);
			अन्यथा
				input_mt_init_slots(wacom_wac->touch_input,
						    wacom_wac->features.touch_max,
						    INPUT_MT_POINTER);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम wacom_parse_hid(काष्ठा hid_device *hdev,
			   काष्ठा wacom_features *features)
अणु
	काष्ठा hid_report_क्रमागत *rep_क्रमागत;
	काष्ठा hid_report *hreport;
	पूर्णांक i, j;

	/* check features first */
	rep_क्रमागत = &hdev->report_क्रमागत[HID_FEATURE_REPORT];
	list_क्रम_each_entry(hreport, &rep_क्रमागत->report_list, list) अणु
		क्रम (i = 0; i < hreport->maxfield; i++) अणु
			/* Ignore अगर report count is out of bounds. */
			अगर (hreport->field[i]->report_count < 1)
				जारी;

			क्रम (j = 0; j < hreport->field[i]->maxusage; j++) अणु
				wacom_feature_mapping(hdev, hreport->field[i],
						hreport->field[i]->usage + j);
			पूर्ण
		पूर्ण
	पूर्ण

	/* now check the input usages */
	rep_क्रमागत = &hdev->report_क्रमागत[HID_INPUT_REPORT];
	list_क्रम_each_entry(hreport, &rep_क्रमागत->report_list, list) अणु

		अगर (!hreport->maxfield)
			जारी;

		क्रम (i = 0; i < hreport->maxfield; i++)
			क्रम (j = 0; j < hreport->field[i]->maxusage; j++)
				wacom_usage_mapping(hdev, hreport->field[i],
						hreport->field[i]->usage + j);
	पूर्ण

	wacom_post_parse_hid(hdev, features);
पूर्ण

अटल पूर्णांक wacom_hid_set_device_mode(काष्ठा hid_device *hdev)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा hid_data *hid_data = &wacom->wacom_wac.hid_data;
	काष्ठा hid_report *r;
	काष्ठा hid_report_क्रमागत *re;

	अगर (hid_data->inpuपंचांगode < 0)
		वापस 0;

	re = &(hdev->report_क्रमागत[HID_FEATURE_REPORT]);
	r = re->report_id_hash[hid_data->inpuपंचांगode];
	अगर (r) अणु
		r->field[0]->value[hid_data->inpuपंचांगode_index] = 2;
		hid_hw_request(hdev, r, HID_REQ_SET_REPORT);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wacom_set_device_mode(काष्ठा hid_device *hdev,
				 काष्ठा wacom_wac *wacom_wac)
अणु
	u8 *rep_data;
	काष्ठा hid_report *r;
	काष्ठा hid_report_क्रमागत *re;
	u32 length;
	पूर्णांक error = -ENOMEM, limit = 0;

	अगर (wacom_wac->mode_report < 0)
		वापस 0;

	re = &(hdev->report_क्रमागत[HID_FEATURE_REPORT]);
	r = re->report_id_hash[wacom_wac->mode_report];
	अगर (!r)
		वापस -EINVAL;

	rep_data = hid_alloc_report_buf(r, GFP_KERNEL);
	अगर (!rep_data)
		वापस -ENOMEM;

	length = hid_report_len(r);

	करो अणु
		rep_data[0] = wacom_wac->mode_report;
		rep_data[1] = wacom_wac->mode_value;

		error = wacom_set_report(hdev, HID_FEATURE_REPORT, rep_data,
					 length, 1);
		अगर (error >= 0)
			error = wacom_get_report(hdev, HID_FEATURE_REPORT,
			                         rep_data, length, 1);
	पूर्ण जबतक (error >= 0 &&
		 rep_data[1] != wacom_wac->mode_report &&
		 limit++ < WAC_MSG_RETRIES);

	kमुक्त(rep_data);

	वापस error < 0 ? error : 0;
पूर्ण

अटल पूर्णांक wacom_bt_query_tablet_data(काष्ठा hid_device *hdev, u8 speed,
		काष्ठा wacom_features *features)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	पूर्णांक ret;
	u8 rep_data[2];

	चयन (features->type) अणु
	हाल GRAPHIRE_BT:
		rep_data[0] = 0x03;
		rep_data[1] = 0x00;
		ret = wacom_set_report(hdev, HID_FEATURE_REPORT, rep_data, 2,
					3);

		अगर (ret >= 0) अणु
			rep_data[0] = speed == 0 ? 0x05 : 0x06;
			rep_data[1] = 0x00;

			ret = wacom_set_report(hdev, HID_FEATURE_REPORT,
						rep_data, 2, 3);

			अगर (ret >= 0) अणु
				wacom->wacom_wac.bt_high_speed = speed;
				वापस 0;
			पूर्ण
		पूर्ण

		/*
		 * Note that अगर the raw queries fail, it's not a hard failure
		 * and it is safe to जारी
		 */
		hid_warn(hdev, "failed to poke device, command %d, err %d\n",
			 rep_data[0], ret);
		अवरोध;
	हाल INTUOS4WL:
		अगर (speed == 1)
			wacom->wacom_wac.bt_features &= ~0x20;
		अन्यथा
			wacom->wacom_wac.bt_features |= 0x20;

		rep_data[0] = 0x03;
		rep_data[1] = wacom->wacom_wac.bt_features;

		ret = wacom_set_report(hdev, HID_FEATURE_REPORT, rep_data, 2,
					1);
		अगर (ret >= 0)
			wacom->wacom_wac.bt_high_speed = speed;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Switch the tablet पूर्णांकo its most-capable mode. Wacom tablets are
 * typically configured to घातer-up in a mode which sends mouse-like
 * reports to the OS. To get असलolute position, pressure data, etc.
 * from the tablet, it is necessary to चयन the tablet out of this
 * mode and पूर्णांकo one which sends the full range of tablet data.
 */
अटल पूर्णांक _wacom_query_tablet_data(काष्ठा wacom *wacom)
अणु
	काष्ठा hid_device *hdev = wacom->hdev;
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom_wac->features;

	अगर (hdev->bus == BUS_BLUETOOTH)
		वापस wacom_bt_query_tablet_data(hdev, 1, features);

	अगर (features->type != HID_GENERIC) अणु
		अगर (features->device_type & WACOM_DEVICETYPE_TOUCH) अणु
			अगर (features->type > TABLETPC) अणु
				/* MT Tablet PC touch */
				wacom_wac->mode_report = 3;
				wacom_wac->mode_value = 4;
			पूर्ण अन्यथा अगर (features->type == WACOM_24HDT) अणु
				wacom_wac->mode_report = 18;
				wacom_wac->mode_value = 2;
			पूर्ण अन्यथा अगर (features->type == WACOM_27QHDT) अणु
				wacom_wac->mode_report = 131;
				wacom_wac->mode_value = 2;
			पूर्ण अन्यथा अगर (features->type == BAMBOO_PAD) अणु
				wacom_wac->mode_report = 2;
				wacom_wac->mode_value = 2;
			पूर्ण
		पूर्ण अन्यथा अगर (features->device_type & WACOM_DEVICETYPE_PEN) अणु
			अगर (features->type <= BAMBOO_PT) अणु
				wacom_wac->mode_report = 2;
				wacom_wac->mode_value = 2;
			पूर्ण
		पूर्ण
	पूर्ण

	wacom_set_device_mode(hdev, wacom_wac);

	अगर (features->type == HID_GENERIC)
		वापस wacom_hid_set_device_mode(hdev);

	वापस 0;
पूर्ण

अटल व्योम wacom_retrieve_hid_descriptor(काष्ठा hid_device *hdev,
					 काष्ठा wacom_features *features)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = wacom->पूर्णांकf;

	/* शेष features */
	features->x_fuzz = 4;
	features->y_fuzz = 4;
	features->pressure_fuzz = 0;
	features->distance_fuzz = 1;
	features->tilt_fuzz = 1;

	/*
	 * The wireless device HID is basic and layout conflicts with
	 * other tablets (monitor and touch पूर्णांकerface can look like pen).
	 * Skip the query क्रम this type and modअगरy शेषs based on
	 * पूर्णांकerface number.
	 */
	अगर (features->type == WIRELESS) अणु
		अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber == 0)
			features->device_type = WACOM_DEVICETYPE_WL_MONITOR;
		अन्यथा
			features->device_type = WACOM_DEVICETYPE_NONE;
		वापस;
	पूर्ण

	wacom_parse_hid(hdev, features);
पूर्ण

काष्ठा wacom_hdev_data अणु
	काष्ठा list_head list;
	काष्ठा kref kref;
	काष्ठा hid_device *dev;
	काष्ठा wacom_shared shared;
पूर्ण;

अटल LIST_HEAD(wacom_udev_list);
अटल DEFINE_MUTEX(wacom_udev_list_lock);

अटल bool wacom_are_sibling(काष्ठा hid_device *hdev,
		काष्ठा hid_device *sibling)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_features *features = &wacom->wacom_wac.features;
	काष्ठा wacom *sibling_wacom = hid_get_drvdata(sibling);
	काष्ठा wacom_features *sibling_features = &sibling_wacom->wacom_wac.features;
	__u32 oVid = features->oVid ? features->oVid : hdev->venकरोr;
	__u32 oPid = features->oPid ? features->oPid : hdev->product;

	/* The defined oVid/oPid must match that of the sibling */
	अगर (features->oVid != HID_ANY_ID && sibling->venकरोr != oVid)
		वापस false;
	अगर (features->oPid != HID_ANY_ID && sibling->product != oPid)
		वापस false;

	/*
	 * Devices with the same VID/PID must share the same physical
	 * device path, जबतक those with dअगरferent VID/PID must share
	 * the same physical parent device path.
	 */
	अगर (hdev->venकरोr == sibling->venकरोr && hdev->product == sibling->product) अणु
		अगर (!hid_compare_device_paths(hdev, sibling, '/'))
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (!hid_compare_device_paths(hdev, sibling, '.'))
			वापस false;
	पूर्ण

	/* Skip the reमुख्यing heuristics unless you are a HID_GENERIC device */
	अगर (features->type != HID_GENERIC)
		वापस true;

	/*
	 * Direct-input devices may not be siblings of indirect-input
	 * devices.
	 */
	अगर ((features->device_type & WACOM_DEVICETYPE_सूचीECT) &&
	    !(sibling_features->device_type & WACOM_DEVICETYPE_सूचीECT))
		वापस false;

	/*
	 * Indirect-input devices may not be siblings of direct-input
	 * devices.
	 */
	अगर (!(features->device_type & WACOM_DEVICETYPE_सूचीECT) &&
	    (sibling_features->device_type & WACOM_DEVICETYPE_सूचीECT))
		वापस false;

	/* Pen devices may only be siblings of touch devices */
	अगर ((features->device_type & WACOM_DEVICETYPE_PEN) &&
	    !(sibling_features->device_type & WACOM_DEVICETYPE_TOUCH))
		वापस false;

	/* Touch devices may only be siblings of pen devices */
	अगर ((features->device_type & WACOM_DEVICETYPE_TOUCH) &&
	    !(sibling_features->device_type & WACOM_DEVICETYPE_PEN))
		वापस false;

	/*
	 * No reason could be found क्रम these two devices to NOT be
	 * siblings, so there's a good chance they ARE siblings
	 */
	वापस true;
पूर्ण

अटल काष्ठा wacom_hdev_data *wacom_get_hdev_data(काष्ठा hid_device *hdev)
अणु
	काष्ठा wacom_hdev_data *data;

	/* Try to find an alपढ़ोy-probed पूर्णांकerface from the same device */
	list_क्रम_each_entry(data, &wacom_udev_list, list) अणु
		अगर (hid_compare_device_paths(hdev, data->dev, '/')) अणु
			kref_get(&data->kref);
			वापस data;
		पूर्ण
	पूर्ण

	/* Fallback to finding devices that appear to be "siblings" */
	list_क्रम_each_entry(data, &wacom_udev_list, list) अणु
		अगर (wacom_are_sibling(hdev, data->dev)) अणु
			kref_get(&data->kref);
			वापस data;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम wacom_release_shared_data(काष्ठा kref *kref)
अणु
	काष्ठा wacom_hdev_data *data =
		container_of(kref, काष्ठा wacom_hdev_data, kref);

	mutex_lock(&wacom_udev_list_lock);
	list_del(&data->list);
	mutex_unlock(&wacom_udev_list_lock);

	kमुक्त(data);
पूर्ण

अटल व्योम wacom_हटाओ_shared_data(व्योम *res)
अणु
	काष्ठा wacom *wacom = res;
	काष्ठा wacom_hdev_data *data;
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;

	अगर (wacom_wac->shared) अणु
		data = container_of(wacom_wac->shared, काष्ठा wacom_hdev_data,
				    shared);

		अगर (wacom_wac->shared->touch == wacom->hdev)
			wacom_wac->shared->touch = शून्य;
		अन्यथा अगर (wacom_wac->shared->pen == wacom->hdev)
			wacom_wac->shared->pen = शून्य;

		kref_put(&data->kref, wacom_release_shared_data);
		wacom_wac->shared = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक wacom_add_shared_data(काष्ठा hid_device *hdev)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_hdev_data *data;
	पूर्णांक retval = 0;

	mutex_lock(&wacom_udev_list_lock);

	data = wacom_get_hdev_data(hdev);
	अगर (!data) अणु
		data = kzalloc(माप(काष्ठा wacom_hdev_data), GFP_KERNEL);
		अगर (!data) अणु
			retval = -ENOMEM;
			जाओ out;
		पूर्ण

		kref_init(&data->kref);
		data->dev = hdev;
		list_add_tail(&data->list, &wacom_udev_list);
	पूर्ण

	wacom_wac->shared = &data->shared;

	retval = devm_add_action(&hdev->dev, wacom_हटाओ_shared_data, wacom);
	अगर (retval) अणु
		mutex_unlock(&wacom_udev_list_lock);
		wacom_हटाओ_shared_data(wacom);
		वापस retval;
	पूर्ण

	अगर (wacom_wac->features.device_type & WACOM_DEVICETYPE_TOUCH)
		wacom_wac->shared->touch = hdev;
	अन्यथा अगर (wacom_wac->features.device_type & WACOM_DEVICETYPE_PEN)
		wacom_wac->shared->pen = hdev;

out:
	mutex_unlock(&wacom_udev_list_lock);
	वापस retval;
पूर्ण

अटल पूर्णांक wacom_led_control(काष्ठा wacom *wacom)
अणु
	अचिन्हित अक्षर *buf;
	पूर्णांक retval;
	अचिन्हित अक्षर report_id = WAC_CMD_LED_CONTROL;
	पूर्णांक buf_size = 9;

	अगर (!wacom->led.groups)
		वापस -ENOTSUPP;

	अगर (wacom->wacom_wac.features.type == REMOTE)
		वापस -ENOTSUPP;

	अगर (wacom->wacom_wac.pid) अणु /* wireless connected */
		report_id = WAC_CMD_WL_LED_CONTROL;
		buf_size = 13;
	पूर्ण
	अन्यथा अगर (wacom->wacom_wac.features.type == INTUOSP2_BT) अणु
		report_id = WAC_CMD_WL_INTUOSP2;
		buf_size = 51;
	पूर्ण
	buf = kzalloc(buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (wacom->wacom_wac.features.type == HID_GENERIC) अणु
		buf[0] = WAC_CMD_LED_CONTROL_GENERIC;
		buf[1] = wacom->led.llv;
		buf[2] = wacom->led.groups[0].select & 0x03;

	पूर्ण अन्यथा अगर ((wacom->wacom_wac.features.type >= INTUOS5S &&
	    wacom->wacom_wac.features.type <= INTUOSPL)) अणु
		/*
		 * Touch Ring and crop mark LED luminance may take on
		 * one of four values:
		 *    0 = Low; 1 = Medium; 2 = High; 3 = Off
		 */
		पूर्णांक ring_led = wacom->led.groups[0].select & 0x03;
		पूर्णांक ring_lum = (((wacom->led.llv & 0x60) >> 5) - 1) & 0x03;
		पूर्णांक crop_lum = 0;
		अचिन्हित अक्षर led_bits = (crop_lum << 4) | (ring_lum << 2) | (ring_led);

		buf[0] = report_id;
		अगर (wacom->wacom_wac.pid) अणु
			wacom_get_report(wacom->hdev, HID_FEATURE_REPORT,
					 buf, buf_size, WAC_CMD_RETRIES);
			buf[0] = report_id;
			buf[4] = led_bits;
		पूर्ण अन्यथा
			buf[1] = led_bits;
	पूर्ण
	अन्यथा अगर (wacom->wacom_wac.features.type == INTUOSP2_BT) अणु
		buf[0] = report_id;
		buf[4] = 100; // Power Connection LED (ORANGE)
		buf[5] = 100; // BT Connection LED (BLUE)
		buf[6] = 100; // Paper Mode (RED?)
		buf[7] = 100; // Paper Mode (GREEN?)
		buf[8] = 100; // Paper Mode (BLUE?)
		buf[9] = wacom->led.llv;
		buf[10] = wacom->led.groups[0].select & 0x03;
	पूर्ण
	अन्यथा अणु
		पूर्णांक led = wacom->led.groups[0].select | 0x4;

		अगर (wacom->wacom_wac.features.type == WACOM_21UX2 ||
		    wacom->wacom_wac.features.type == WACOM_24HD)
			led |= (wacom->led.groups[1].select << 4) | 0x40;

		buf[0] = report_id;
		buf[1] = led;
		buf[2] = wacom->led.llv;
		buf[3] = wacom->led.hlv;
		buf[4] = wacom->led.img_lum;
	पूर्ण

	retval = wacom_set_report(wacom->hdev, HID_FEATURE_REPORT, buf, buf_size,
				  WAC_CMD_RETRIES);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल पूर्णांक wacom_led_putimage(काष्ठा wacom *wacom, पूर्णांक button_id, u8 xfer_id,
		स्थिर अचिन्हित len, स्थिर व्योम *img)
अणु
	अचिन्हित अक्षर *buf;
	पूर्णांक i, retval;
	स्थिर अचिन्हित chunk_len = len / 4; /* 4 chunks are needed to be sent */

	buf = kzalloc(chunk_len + 3 , GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* Send 'start' command */
	buf[0] = WAC_CMD_ICON_START;
	buf[1] = 1;
	retval = wacom_set_report(wacom->hdev, HID_FEATURE_REPORT, buf, 2,
				  WAC_CMD_RETRIES);
	अगर (retval < 0)
		जाओ out;

	buf[0] = xfer_id;
	buf[1] = button_id & 0x07;
	क्रम (i = 0; i < 4; i++) अणु
		buf[2] = i;
		स_नकल(buf + 3, img + i * chunk_len, chunk_len);

		retval = wacom_set_report(wacom->hdev, HID_FEATURE_REPORT,
					  buf, chunk_len + 3, WAC_CMD_RETRIES);
		अगर (retval < 0)
			अवरोध;
	पूर्ण

	/* Send 'stop' */
	buf[0] = WAC_CMD_ICON_START;
	buf[1] = 0;
	wacom_set_report(wacom->hdev, HID_FEATURE_REPORT, buf, 2,
			 WAC_CMD_RETRIES);

out:
	kमुक्त(buf);
	वापस retval;
पूर्ण

अटल sमाप_प्रकार wacom_led_select_store(काष्ठा device *dev, पूर्णांक set_id,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	अचिन्हित पूर्णांक id;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &id);
	अगर (err)
		वापस err;

	mutex_lock(&wacom->lock);

	wacom->led.groups[set_id].select = id & 0x3;
	err = wacom_led_control(wacom);

	mutex_unlock(&wacom->lock);

	वापस err < 0 ? err : count;
पूर्ण

#घोषणा DEVICE_LED_SELECT_ATTR(SET_ID)					\
अटल sमाप_प्रकार wacom_led##SET_ID##_select_store(काष्ठा device *dev,	\
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)	\
अणु									\
	वापस wacom_led_select_store(dev, SET_ID, buf, count);		\
पूर्ण									\
अटल sमाप_प्रकार wacom_led##SET_ID##_select_show(काष्ठा device *dev,	\
	काष्ठा device_attribute *attr, अक्षर *buf)			\
अणु									\
	काष्ठा hid_device *hdev = to_hid_device(dev);\
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);			\
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",			\
			 wacom->led.groups[SET_ID].select);		\
पूर्ण									\
अटल DEVICE_ATTR(status_led##SET_ID##_select, DEV_ATTR_RW_PERM,	\
		    wacom_led##SET_ID##_select_show,			\
		    wacom_led##SET_ID##_select_store)

DEVICE_LED_SELECT_ATTR(0);
DEVICE_LED_SELECT_ATTR(1);

अटल sमाप_प्रकार wacom_luminance_store(काष्ठा wacom *wacom, u8 *dest,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	mutex_lock(&wacom->lock);

	*dest = value & 0x7f;
	err = wacom_led_control(wacom);

	mutex_unlock(&wacom->lock);

	वापस err < 0 ? err : count;
पूर्ण

#घोषणा DEVICE_LUMIन_अंकCE_ATTR(name, field)				\
अटल sमाप_प्रकार wacom_##name##_luminance_store(काष्ठा device *dev,	\
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)	\
अणु									\
	काष्ठा hid_device *hdev = to_hid_device(dev);\
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);			\
									\
	वापस wacom_luminance_store(wacom, &wacom->led.field,		\
				     buf, count);			\
पूर्ण									\
अटल sमाप_प्रकार wacom_##name##_luminance_show(काष्ठा device *dev,	\
	काष्ठा device_attribute *attr, अक्षर *buf)			\
अणु									\
	काष्ठा wacom *wacom = dev_get_drvdata(dev);			\
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", wacom->led.field);	\
पूर्ण									\
अटल DEVICE_ATTR(name##_luminance, DEV_ATTR_RW_PERM,			\
		   wacom_##name##_luminance_show,			\
		   wacom_##name##_luminance_store)

DEVICE_LUMIन_अंकCE_ATTR(status0, llv);
DEVICE_LUMIन_अंकCE_ATTR(status1, hlv);
DEVICE_LUMIन_अंकCE_ATTR(buttons, img_lum);

अटल sमाप_प्रकार wacom_button_image_store(काष्ठा device *dev, पूर्णांक button_id,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	पूर्णांक err;
	अचिन्हित len;
	u8 xfer_id;

	अगर (hdev->bus == BUS_BLUETOOTH) अणु
		len = 256;
		xfer_id = WAC_CMD_ICON_BT_XFER;
	पूर्ण अन्यथा अणु
		len = 1024;
		xfer_id = WAC_CMD_ICON_XFER;
	पूर्ण

	अगर (count != len)
		वापस -EINVAL;

	mutex_lock(&wacom->lock);

	err = wacom_led_putimage(wacom, button_id, xfer_id, len, buf);

	mutex_unlock(&wacom->lock);

	वापस err < 0 ? err : count;
पूर्ण

#घोषणा DEVICE_BTNIMG_ATTR(BUTTON_ID)					\
अटल sमाप_प्रकार wacom_btnimg##BUTTON_ID##_store(काष्ठा device *dev,	\
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)	\
अणु									\
	वापस wacom_button_image_store(dev, BUTTON_ID, buf, count);	\
पूर्ण									\
अटल DEVICE_ATTR(button##BUTTON_ID##_rawimg, DEV_ATTR_WO_PERM,	\
		   शून्य, wacom_btnimg##BUTTON_ID##_store)

DEVICE_BTNIMG_ATTR(0);
DEVICE_BTNIMG_ATTR(1);
DEVICE_BTNIMG_ATTR(2);
DEVICE_BTNIMG_ATTR(3);
DEVICE_BTNIMG_ATTR(4);
DEVICE_BTNIMG_ATTR(5);
DEVICE_BTNIMG_ATTR(6);
DEVICE_BTNIMG_ATTR(7);

अटल काष्ठा attribute *cपूर्णांकiq_led_attrs[] = अणु
	&dev_attr_status_led0_select.attr,
	&dev_attr_status_led1_select.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cपूर्णांकiq_led_attr_group = अणु
	.name = "wacom_led",
	.attrs = cपूर्णांकiq_led_attrs,
पूर्ण;

अटल काष्ठा attribute *पूर्णांकuos4_led_attrs[] = अणु
	&dev_attr_status0_luminance.attr,
	&dev_attr_status1_luminance.attr,
	&dev_attr_status_led0_select.attr,
	&dev_attr_buttons_luminance.attr,
	&dev_attr_button0_rawimg.attr,
	&dev_attr_button1_rawimg.attr,
	&dev_attr_button2_rawimg.attr,
	&dev_attr_button3_rawimg.attr,
	&dev_attr_button4_rawimg.attr,
	&dev_attr_button5_rawimg.attr,
	&dev_attr_button6_rawimg.attr,
	&dev_attr_button7_rawimg.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group पूर्णांकuos4_led_attr_group = अणु
	.name = "wacom_led",
	.attrs = पूर्णांकuos4_led_attrs,
पूर्ण;

अटल काष्ठा attribute *पूर्णांकuos5_led_attrs[] = अणु
	&dev_attr_status0_luminance.attr,
	&dev_attr_status_led0_select.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group पूर्णांकuos5_led_attr_group = अणु
	.name = "wacom_led",
	.attrs = पूर्णांकuos5_led_attrs,
पूर्ण;

अटल काष्ठा attribute *generic_led_attrs[] = अणु
	&dev_attr_status0_luminance.attr,
	&dev_attr_status_led0_select.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group generic_led_attr_group = अणु
	.name = "wacom_led",
	.attrs = generic_led_attrs,
पूर्ण;

काष्ठा wacom_sysfs_group_devres अणु
	स्थिर काष्ठा attribute_group *group;
	काष्ठा kobject *root;
पूर्ण;

अटल व्योम wacom_devm_sysfs_group_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा wacom_sysfs_group_devres *devres = res;
	काष्ठा kobject *kobj = devres->root;

	dev_dbg(dev, "%s: dropping reference to %s\n",
		__func__, devres->group->name);
	sysfs_हटाओ_group(kobj, devres->group);
पूर्ण

अटल पूर्णांक __wacom_devm_sysfs_create_group(काष्ठा wacom *wacom,
					   काष्ठा kobject *root,
					   स्थिर काष्ठा attribute_group *group)
अणु
	काष्ठा wacom_sysfs_group_devres *devres;
	पूर्णांक error;

	devres = devres_alloc(wacom_devm_sysfs_group_release,
			      माप(काष्ठा wacom_sysfs_group_devres),
			      GFP_KERNEL);
	अगर (!devres)
		वापस -ENOMEM;

	devres->group = group;
	devres->root = root;

	error = sysfs_create_group(devres->root, group);
	अगर (error) अणु
		devres_मुक्त(devres);
		वापस error;
	पूर्ण

	devres_add(&wacom->hdev->dev, devres);

	वापस 0;
पूर्ण

अटल पूर्णांक wacom_devm_sysfs_create_group(काष्ठा wacom *wacom,
					 स्थिर काष्ठा attribute_group *group)
अणु
	वापस __wacom_devm_sysfs_create_group(wacom, &wacom->hdev->dev.kobj,
					       group);
पूर्ण

अटल व्योम wacom_devm_kfअगरo_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा kfअगरo_rec_ptr_2 *devres = res;

	kfअगरo_मुक्त(devres);
पूर्ण

अटल पूर्णांक wacom_devm_kfअगरo_alloc(काष्ठा wacom *wacom)
अणु
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा kfअगरo_rec_ptr_2 *pen_fअगरo;
	पूर्णांक error;

	pen_fअगरo = devres_alloc(wacom_devm_kfअगरo_release,
			      माप(काष्ठा kfअगरo_rec_ptr_2),
			      GFP_KERNEL);

	अगर (!pen_fअगरo)
		वापस -ENOMEM;

	error = kfअगरo_alloc(pen_fअगरo, WACOM_PKGLEN_MAX, GFP_KERNEL);
	अगर (error) अणु
		devres_मुक्त(pen_fअगरo);
		वापस error;
	पूर्ण

	devres_add(&wacom->hdev->dev, pen_fअगरo);
	wacom_wac->pen_fअगरo = pen_fअगरo;

	वापस 0;
पूर्ण

क्रमागत led_brightness wacom_leds_brightness_get(काष्ठा wacom_led *led)
अणु
	काष्ठा wacom *wacom = led->wacom;

	अगर (wacom->led.max_hlv)
		वापस led->hlv * LED_FULL / wacom->led.max_hlv;

	अगर (wacom->led.max_llv)
		वापस led->llv * LED_FULL / wacom->led.max_llv;

	/* device करोesn't support brightness tuning */
	वापस LED_FULL;
पूर्ण

अटल क्रमागत led_brightness __wacom_led_brightness_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा wacom_led *led = container_of(cdev, काष्ठा wacom_led, cdev);
	काष्ठा wacom *wacom = led->wacom;

	अगर (wacom->led.groups[led->group].select != led->id)
		वापस LED_OFF;

	वापस wacom_leds_brightness_get(led);
पूर्ण

अटल पूर्णांक wacom_led_brightness_set(काष्ठा led_classdev *cdev,
				    क्रमागत led_brightness brightness)
अणु
	काष्ठा wacom_led *led = container_of(cdev, काष्ठा wacom_led, cdev);
	काष्ठा wacom *wacom = led->wacom;
	पूर्णांक error;

	mutex_lock(&wacom->lock);

	अगर (!wacom->led.groups || (brightness == LED_OFF &&
	    wacom->led.groups[led->group].select != led->id)) अणु
		error = 0;
		जाओ out;
	पूर्ण

	led->llv = wacom->led.llv = wacom->led.max_llv * brightness / LED_FULL;
	led->hlv = wacom->led.hlv = wacom->led.max_hlv * brightness / LED_FULL;

	wacom->led.groups[led->group].select = led->id;

	error = wacom_led_control(wacom);

out:
	mutex_unlock(&wacom->lock);

	वापस error;
पूर्ण

अटल व्योम wacom_led_पढ़ोonly_brightness_set(काष्ठा led_classdev *cdev,
					       क्रमागत led_brightness brightness)
अणु
पूर्ण

अटल पूर्णांक wacom_led_रेजिस्टर_one(काष्ठा device *dev, काष्ठा wacom *wacom,
				  काष्ठा wacom_led *led, अचिन्हित पूर्णांक group,
				  अचिन्हित पूर्णांक id, bool पढ़ो_only)
अणु
	पूर्णांक error;
	अक्षर *name;

	name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
			      "%s::wacom-%d.%d",
			      dev_name(dev),
			      group,
			      id);
	अगर (!name)
		वापस -ENOMEM;

	अगर (!पढ़ो_only) अणु
		led->trigger.name = name;
		error = devm_led_trigger_रेजिस्टर(dev, &led->trigger);
		अगर (error) अणु
			hid_err(wacom->hdev,
				"failed to register LED trigger %s: %d\n",
				led->cdev.name, error);
			वापस error;
		पूर्ण
	पूर्ण

	led->group = group;
	led->id = id;
	led->wacom = wacom;
	led->llv = wacom->led.llv;
	led->hlv = wacom->led.hlv;
	led->cdev.name = name;
	led->cdev.max_brightness = LED_FULL;
	led->cdev.flags = LED_HW_PLUGGABLE;
	led->cdev.brightness_get = __wacom_led_brightness_get;
	अगर (!पढ़ो_only) अणु
		led->cdev.brightness_set_blocking = wacom_led_brightness_set;
		led->cdev.शेष_trigger = led->cdev.name;
	पूर्ण अन्यथा अणु
		led->cdev.brightness_set = wacom_led_पढ़ोonly_brightness_set;
	पूर्ण

	error = devm_led_classdev_रेजिस्टर(dev, &led->cdev);
	अगर (error) अणु
		hid_err(wacom->hdev,
			"failed to register LED %s: %d\n",
			led->cdev.name, error);
		led->cdev.name = शून्य;
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wacom_led_groups_release_one(व्योम *data)
अणु
	काष्ठा wacom_group_leds *group = data;

	devres_release_group(group->dev, group);
पूर्ण

अटल पूर्णांक wacom_led_groups_alloc_and_रेजिस्टर_one(काष्ठा device *dev,
						   काष्ठा wacom *wacom,
						   पूर्णांक group_id, पूर्णांक count,
						   bool पढ़ो_only)
अणु
	काष्ठा wacom_led *leds;
	पूर्णांक i, error;

	अगर (group_id >= wacom->led.count || count <= 0)
		वापस -EINVAL;

	अगर (!devres_खोलो_group(dev, &wacom->led.groups[group_id], GFP_KERNEL))
		वापस -ENOMEM;

	leds = devm_kसुस्मृति(dev, count, माप(काष्ठा wacom_led), GFP_KERNEL);
	अगर (!leds) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	wacom->led.groups[group_id].leds = leds;
	wacom->led.groups[group_id].count = count;

	क्रम (i = 0; i < count; i++) अणु
		error = wacom_led_रेजिस्टर_one(dev, wacom, &leds[i],
					       group_id, i, पढ़ो_only);
		अगर (error)
			जाओ err;
	पूर्ण

	wacom->led.groups[group_id].dev = dev;

	devres_बंद_group(dev, &wacom->led.groups[group_id]);

	/*
	 * There is a bug (?) in devm_led_classdev_रेजिस्टर() in which its
	 * increments the refcount of the parent. If the parent is an input
	 * device, that means the ref count never reaches 0 when
	 * devm_input_device_release() माला_लो called.
	 * This means that the LEDs are still there after disconnect.
	 * Manually क्रमce the release of the group so that the leds are released
	 * once we are करोne using them.
	 */
	error = devm_add_action_or_reset(&wacom->hdev->dev,
					 wacom_led_groups_release_one,
					 &wacom->led.groups[group_id]);
	अगर (error)
		वापस error;

	वापस 0;

err:
	devres_release_group(dev, &wacom->led.groups[group_id]);
	वापस error;
पूर्ण

काष्ठा wacom_led *wacom_led_find(काष्ठा wacom *wacom, अचिन्हित पूर्णांक group_id,
				 अचिन्हित पूर्णांक id)
अणु
	काष्ठा wacom_group_leds *group;

	अगर (group_id >= wacom->led.count)
		वापस शून्य;

	group = &wacom->led.groups[group_id];

	अगर (!group->leds)
		वापस शून्य;

	id %= group->count;

	वापस &group->leds[id];
पूर्ण

/*
 * wacom_led_next: gives the next available led with a wacom trigger.
 *
 * वापसs the next available काष्ठा wacom_led which has its शेष trigger
 * or the current one अगर none is available.
 */
काष्ठा wacom_led *wacom_led_next(काष्ठा wacom *wacom, काष्ठा wacom_led *cur)
अणु
	काष्ठा wacom_led *next_led;
	पूर्णांक group, next;

	अगर (!wacom || !cur)
		वापस शून्य;

	group = cur->group;
	next = cur->id;

	करो अणु
		next_led = wacom_led_find(wacom, group, ++next);
		अगर (!next_led || next_led == cur)
			वापस next_led;
	पूर्ण जबतक (next_led->cdev.trigger != &next_led->trigger);

	वापस next_led;
पूर्ण

अटल व्योम wacom_led_groups_release(व्योम *data)
अणु
	काष्ठा wacom *wacom = data;

	wacom->led.groups = शून्य;
	wacom->led.count = 0;
पूर्ण

अटल पूर्णांक wacom_led_groups_allocate(काष्ठा wacom *wacom, पूर्णांक count)
अणु
	काष्ठा device *dev = &wacom->hdev->dev;
	काष्ठा wacom_group_leds *groups;
	पूर्णांक error;

	groups = devm_kसुस्मृति(dev, count, माप(काष्ठा wacom_group_leds),
			      GFP_KERNEL);
	अगर (!groups)
		वापस -ENOMEM;

	error = devm_add_action_or_reset(dev, wacom_led_groups_release, wacom);
	अगर (error)
		वापस error;

	wacom->led.groups = groups;
	wacom->led.count = count;

	वापस 0;
पूर्ण

अटल पूर्णांक wacom_leds_alloc_and_रेजिस्टर(काष्ठा wacom *wacom, पूर्णांक group_count,
					 पूर्णांक led_per_group, bool पढ़ो_only)
अणु
	काष्ठा device *dev;
	पूर्णांक i, error;

	अगर (!wacom->wacom_wac.pad_input)
		वापस -EINVAL;

	dev = &wacom->wacom_wac.pad_input->dev;

	error = wacom_led_groups_allocate(wacom, group_count);
	अगर (error)
		वापस error;

	क्रम (i = 0; i < group_count; i++) अणु
		error = wacom_led_groups_alloc_and_रेजिस्टर_one(dev, wacom, i,
								led_per_group,
								पढ़ो_only);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wacom_initialize_leds(काष्ठा wacom *wacom)
अणु
	पूर्णांक error;

	अगर (!(wacom->wacom_wac.features.device_type & WACOM_DEVICETYPE_PAD))
		वापस 0;

	/* Initialize शेष values */
	चयन (wacom->wacom_wac.features.type) अणु
	हाल HID_GENERIC:
		अगर (!wacom->generic_has_leds)
			वापस 0;
		wacom->led.llv = 100;
		wacom->led.max_llv = 100;

		error = wacom_leds_alloc_and_रेजिस्टर(wacom, 1, 4, false);
		अगर (error) अणु
			hid_err(wacom->hdev,
				"cannot create leds err: %d\n", error);
			वापस error;
		पूर्ण

		error = wacom_devm_sysfs_create_group(wacom,
						      &generic_led_attr_group);
		अवरोध;

	हाल INTUOS4S:
	हाल INTUOS4:
	हाल INTUOS4WL:
	हाल INTUOS4L:
		wacom->led.llv = 10;
		wacom->led.hlv = 20;
		wacom->led.max_llv = 127;
		wacom->led.max_hlv = 127;
		wacom->led.img_lum = 10;

		error = wacom_leds_alloc_and_रेजिस्टर(wacom, 1, 4, false);
		अगर (error) अणु
			hid_err(wacom->hdev,
				"cannot create leds err: %d\n", error);
			वापस error;
		पूर्ण

		error = wacom_devm_sysfs_create_group(wacom,
						      &पूर्णांकuos4_led_attr_group);
		अवरोध;

	हाल WACOM_24HD:
	हाल WACOM_21UX2:
		wacom->led.llv = 0;
		wacom->led.hlv = 0;
		wacom->led.img_lum = 0;

		error = wacom_leds_alloc_and_रेजिस्टर(wacom, 2, 4, false);
		अगर (error) अणु
			hid_err(wacom->hdev,
				"cannot create leds err: %d\n", error);
			वापस error;
		पूर्ण

		error = wacom_devm_sysfs_create_group(wacom,
						      &cपूर्णांकiq_led_attr_group);
		अवरोध;

	हाल INTUOS5S:
	हाल INTUOS5:
	हाल INTUOS5L:
	हाल INTUOSPS:
	हाल INTUOSPM:
	हाल INTUOSPL:
		wacom->led.llv = 32;
		wacom->led.max_llv = 96;

		error = wacom_leds_alloc_and_रेजिस्टर(wacom, 1, 4, false);
		अगर (error) अणु
			hid_err(wacom->hdev,
				"cannot create leds err: %d\n", error);
			वापस error;
		पूर्ण

		error = wacom_devm_sysfs_create_group(wacom,
						      &पूर्णांकuos5_led_attr_group);
		अवरोध;

	हाल INTUOSP2_BT:
		wacom->led.llv = 50;
		wacom->led.max_llv = 100;
		error = wacom_leds_alloc_and_रेजिस्टर(wacom, 1, 4, false);
		अगर (error) अणु
			hid_err(wacom->hdev,
				"cannot create leds err: %d\n", error);
			वापस error;
		पूर्ण
		वापस 0;

	हाल REMOTE:
		wacom->led.llv = 255;
		wacom->led.max_llv = 255;
		error = wacom_led_groups_allocate(wacom, 5);
		अगर (error) अणु
			hid_err(wacom->hdev,
				"cannot create leds err: %d\n", error);
			वापस error;
		पूर्ण
		वापस 0;

	शेष:
		वापस 0;
	पूर्ण

	अगर (error) अणु
		hid_err(wacom->hdev,
			"cannot create sysfs group err: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wacom_init_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wacom *wacom = container_of(work, काष्ठा wacom, init_work.work);

	_wacom_query_tablet_data(wacom);
	wacom_led_control(wacom);
पूर्ण

अटल व्योम wacom_query_tablet_data(काष्ठा wacom *wacom)
अणु
	schedule_delayed_work(&wacom->init_work, msecs_to_jअगरfies(1000));
पूर्ण

अटल क्रमागत घातer_supply_property wacom_battery_props[] = अणु
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_SCOPE,
	POWER_SUPPLY_PROP_CAPACITY
पूर्ण;

अटल पूर्णांक wacom_battery_get_property(काष्ठा घातer_supply *psy,
				      क्रमागत घातer_supply_property psp,
				      जोड़ घातer_supply_propval *val)
अणु
	काष्ठा wacom_battery *battery = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;

	चयन (psp) अणु
		हाल POWER_SUPPLY_PROP_MODEL_NAME:
			val->strval = battery->wacom->wacom_wac.name;
			अवरोध;
		हाल POWER_SUPPLY_PROP_PRESENT:
			val->पूर्णांकval = battery->bat_connected;
			अवरोध;
		हाल POWER_SUPPLY_PROP_SCOPE:
			val->पूर्णांकval = POWER_SUPPLY_SCOPE_DEVICE;
			अवरोध;
		हाल POWER_SUPPLY_PROP_CAPACITY:
			val->पूर्णांकval = battery->battery_capacity;
			अवरोध;
		हाल POWER_SUPPLY_PROP_STATUS:
			अगर (battery->bat_status != WACOM_POWER_SUPPLY_STATUS_AUTO)
				val->पूर्णांकval = battery->bat_status;
			अन्यथा अगर (battery->bat_अक्षरging)
				val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
			अन्यथा अगर (battery->battery_capacity == 100 &&
				    battery->ps_connected)
				val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
			अन्यथा अगर (battery->ps_connected)
				val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
			अन्यथा
				val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __wacom_initialize_battery(काष्ठा wacom *wacom,
				      काष्ठा wacom_battery *battery)
अणु
	अटल atomic_t battery_no = ATOMIC_INIT(0);
	काष्ठा device *dev = &wacom->hdev->dev;
	काष्ठा घातer_supply_config psy_cfg = अणु .drv_data = battery, पूर्ण;
	काष्ठा घातer_supply *ps_bat;
	काष्ठा घातer_supply_desc *bat_desc = &battery->bat_desc;
	अचिन्हित दीर्घ n;
	पूर्णांक error;

	अगर (!devres_खोलो_group(dev, bat_desc, GFP_KERNEL))
		वापस -ENOMEM;

	battery->wacom = wacom;

	n = atomic_inc_वापस(&battery_no) - 1;

	bat_desc->properties = wacom_battery_props;
	bat_desc->num_properties = ARRAY_SIZE(wacom_battery_props);
	bat_desc->get_property = wacom_battery_get_property;
	प्र_लिखो(battery->bat_name, "wacom_battery_%ld", n);
	bat_desc->name = battery->bat_name;
	bat_desc->type = POWER_SUPPLY_TYPE_USB;
	bat_desc->use_क्रम_apm = 0;

	ps_bat = devm_घातer_supply_रेजिस्टर(dev, bat_desc, &psy_cfg);
	अगर (IS_ERR(ps_bat)) अणु
		error = PTR_ERR(ps_bat);
		जाओ err;
	पूर्ण

	घातer_supply_घातers(ps_bat, &wacom->hdev->dev);

	battery->battery = ps_bat;

	devres_बंद_group(dev, bat_desc);
	वापस 0;

err:
	devres_release_group(dev, bat_desc);
	वापस error;
पूर्ण

अटल पूर्णांक wacom_initialize_battery(काष्ठा wacom *wacom)
अणु
	अगर (wacom->wacom_wac.features.quirks & WACOM_QUIRK_BATTERY)
		वापस __wacom_initialize_battery(wacom, &wacom->battery);

	वापस 0;
पूर्ण

अटल व्योम wacom_destroy_battery(काष्ठा wacom *wacom)
अणु
	अगर (wacom->battery.battery) अणु
		devres_release_group(&wacom->hdev->dev,
				     &wacom->battery.bat_desc);
		wacom->battery.battery = शून्य;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार wacom_show_speed(काष्ठा device *dev,
				काष्ठा device_attribute
				*attr, अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);

	वापस sysfs_emit(buf, "%i\n", wacom->wacom_wac.bt_high_speed);
पूर्ण

अटल sमाप_प्रकार wacom_store_speed(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	u8 new_speed;

	अगर (kstrtou8(buf, 0, &new_speed))
		वापस -EINVAL;

	अगर (new_speed != 0 && new_speed != 1)
		वापस -EINVAL;

	wacom_bt_query_tablet_data(hdev, new_speed, &wacom->wacom_wac.features);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(speed, DEV_ATTR_RW_PERM,
		wacom_show_speed, wacom_store_speed);


अटल sमाप_प्रकार wacom_show_remote_mode(काष्ठा kobject *kobj,
				      काष्ठा kobj_attribute *kattr,
				      अक्षर *buf, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj->parent);
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	u8 mode;

	mode = wacom->led.groups[index].select;
	वापस प्र_लिखो(buf, "%d\n", mode < 3 ? mode : -1);
पूर्ण

#घोषणा DEVICE_EKR_ATTR_GROUP(SET_ID)					\
अटल sमाप_प्रकार wacom_show_remote##SET_ID##_mode(काष्ठा kobject *kobj,	\
			       काष्ठा kobj_attribute *kattr, अक्षर *buf)	\
अणु									\
	वापस wacom_show_remote_mode(kobj, kattr, buf, SET_ID);	\
पूर्ण									\
अटल काष्ठा kobj_attribute remote##SET_ID##_mode_attr = अणु		\
	.attr = अणु.name = "remote_mode",					\
		.mode = DEV_ATTR_RO_PERMपूर्ण,				\
	.show = wacom_show_remote##SET_ID##_mode,			\
पूर्ण;									\
अटल काष्ठा attribute *remote##SET_ID##_serial_attrs[] = अणु		\
	&remote##SET_ID##_mode_attr.attr,				\
	शून्य								\
पूर्ण;									\
अटल स्थिर काष्ठा attribute_group remote##SET_ID##_serial_group = अणु	\
	.name = शून्य,							\
	.attrs = remote##SET_ID##_serial_attrs,				\
पूर्ण

DEVICE_EKR_ATTR_GROUP(0);
DEVICE_EKR_ATTR_GROUP(1);
DEVICE_EKR_ATTR_GROUP(2);
DEVICE_EKR_ATTR_GROUP(3);
DEVICE_EKR_ATTR_GROUP(4);

अटल पूर्णांक wacom_remote_create_attr_group(काष्ठा wacom *wacom, __u32 serial,
					  पूर्णांक index)
अणु
	पूर्णांक error = 0;
	काष्ठा wacom_remote *remote = wacom->remote;

	remote->remotes[index].group.name = devm_kaप्र_लिखो(&wacom->hdev->dev,
							  GFP_KERNEL,
							  "%d", serial);
	अगर (!remote->remotes[index].group.name)
		वापस -ENOMEM;

	error = __wacom_devm_sysfs_create_group(wacom, remote->remote_dir,
						&remote->remotes[index].group);
	अगर (error) अणु
		remote->remotes[index].group.name = शून्य;
		hid_err(wacom->hdev,
			"cannot create sysfs group err: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wacom_cmd_unpair_remote(काष्ठा wacom *wacom, अचिन्हित अक्षर selector)
अणु
	स्थिर माप_प्रकार buf_size = 2;
	अचिन्हित अक्षर *buf;
	पूर्णांक retval;

	buf = kzalloc(buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = WAC_CMD_DELETE_PAIRING;
	buf[1] = selector;

	retval = wacom_set_report(wacom->hdev, HID_OUTPUT_REPORT, buf,
				  buf_size, WAC_CMD_RETRIES);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार wacom_store_unpair_remote(काष्ठा kobject *kobj,
					 काष्ठा kobj_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित अक्षर selector = 0;
	काष्ठा device *dev = kobj_to_dev(kobj->parent);
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	पूर्णांक err;

	अगर (!म_भेदन(buf, "*\n", 2)) अणु
		selector = WAC_CMD_UNPAIR_ALL;
	पूर्ण अन्यथा अणु
		hid_info(wacom->hdev, "remote: unrecognized unpair code: %s\n",
			 buf);
		वापस -1;
	पूर्ण

	mutex_lock(&wacom->lock);

	err = wacom_cmd_unpair_remote(wacom, selector);
	mutex_unlock(&wacom->lock);

	वापस err < 0 ? err : count;
पूर्ण

अटल काष्ठा kobj_attribute unpair_remote_attr = अणु
	.attr = अणु.name = "unpair_remote", .mode = 0200पूर्ण,
	.store = wacom_store_unpair_remote,
पूर्ण;

अटल स्थिर काष्ठा attribute *remote_unpair_attrs[] = अणु
	&unpair_remote_attr.attr,
	शून्य
पूर्ण;

अटल व्योम wacom_remotes_destroy(व्योम *data)
अणु
	काष्ठा wacom *wacom = data;
	काष्ठा wacom_remote *remote = wacom->remote;

	अगर (!remote)
		वापस;

	kobject_put(remote->remote_dir);
	kfअगरo_मुक्त(&remote->remote_fअगरo);
	wacom->remote = शून्य;
पूर्ण

अटल पूर्णांक wacom_initialize_remotes(काष्ठा wacom *wacom)
अणु
	पूर्णांक error = 0;
	काष्ठा wacom_remote *remote;
	पूर्णांक i;

	अगर (wacom->wacom_wac.features.type != REMOTE)
		वापस 0;

	remote = devm_kzalloc(&wacom->hdev->dev, माप(*wacom->remote),
			      GFP_KERNEL);
	अगर (!remote)
		वापस -ENOMEM;

	wacom->remote = remote;

	spin_lock_init(&remote->remote_lock);

	error = kfअगरo_alloc(&remote->remote_fअगरo,
			5 * माप(काष्ठा wacom_remote_data),
			GFP_KERNEL);
	अगर (error) अणु
		hid_err(wacom->hdev, "failed allocating remote_fifo\n");
		वापस -ENOMEM;
	पूर्ण

	remote->remotes[0].group = remote0_serial_group;
	remote->remotes[1].group = remote1_serial_group;
	remote->remotes[2].group = remote2_serial_group;
	remote->remotes[3].group = remote3_serial_group;
	remote->remotes[4].group = remote4_serial_group;

	remote->remote_dir = kobject_create_and_add("wacom_remote",
						    &wacom->hdev->dev.kobj);
	अगर (!remote->remote_dir)
		वापस -ENOMEM;

	error = sysfs_create_files(remote->remote_dir, remote_unpair_attrs);

	अगर (error) अणु
		hid_err(wacom->hdev,
			"cannot create sysfs group err: %d\n", error);
		वापस error;
	पूर्ण

	क्रम (i = 0; i < WACOM_MAX_REMOTES; i++) अणु
		wacom->led.groups[i].select = WACOM_STATUS_UNKNOWN;
		remote->remotes[i].serial = 0;
	पूर्ण

	error = devm_add_action_or_reset(&wacom->hdev->dev,
					 wacom_remotes_destroy, wacom);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल काष्ठा input_dev *wacom_allocate_input(काष्ठा wacom *wacom)
अणु
	काष्ठा input_dev *input_dev;
	काष्ठा hid_device *hdev = wacom->hdev;
	काष्ठा wacom_wac *wacom_wac = &(wacom->wacom_wac);

	input_dev = devm_input_allocate_device(&hdev->dev);
	अगर (!input_dev)
		वापस शून्य;

	input_dev->name = wacom_wac->features.name;
	input_dev->phys = hdev->phys;
	input_dev->dev.parent = &hdev->dev;
	input_dev->खोलो = wacom_खोलो;
	input_dev->बंद = wacom_बंद;
	input_dev->uniq = hdev->uniq;
	input_dev->id.bustype = hdev->bus;
	input_dev->id.venकरोr  = hdev->venकरोr;
	input_dev->id.product = wacom_wac->pid ? wacom_wac->pid : hdev->product;
	input_dev->id.version = hdev->version;
	input_set_drvdata(input_dev, wacom);

	वापस input_dev;
पूर्ण

अटल पूर्णांक wacom_allocate_inमाला_दो(काष्ठा wacom *wacom)
अणु
	काष्ठा wacom_wac *wacom_wac = &(wacom->wacom_wac);

	wacom_wac->pen_input = wacom_allocate_input(wacom);
	wacom_wac->touch_input = wacom_allocate_input(wacom);
	wacom_wac->pad_input = wacom_allocate_input(wacom);
	अगर (!wacom_wac->pen_input ||
	    !wacom_wac->touch_input ||
	    !wacom_wac->pad_input)
		वापस -ENOMEM;

	wacom_wac->pen_input->name = wacom_wac->pen_name;
	wacom_wac->touch_input->name = wacom_wac->touch_name;
	wacom_wac->pad_input->name = wacom_wac->pad_name;

	वापस 0;
पूर्ण

अटल पूर्णांक wacom_रेजिस्टर_inमाला_दो(काष्ठा wacom *wacom)
अणु
	काष्ठा input_dev *pen_input_dev, *touch_input_dev, *pad_input_dev;
	काष्ठा wacom_wac *wacom_wac = &(wacom->wacom_wac);
	पूर्णांक error = 0;

	pen_input_dev = wacom_wac->pen_input;
	touch_input_dev = wacom_wac->touch_input;
	pad_input_dev = wacom_wac->pad_input;

	अगर (!pen_input_dev || !touch_input_dev || !pad_input_dev)
		वापस -EINVAL;

	error = wacom_setup_pen_input_capabilities(pen_input_dev, wacom_wac);
	अगर (error) अणु
		/* no pen in use on this पूर्णांकerface */
		input_मुक्त_device(pen_input_dev);
		wacom_wac->pen_input = शून्य;
		pen_input_dev = शून्य;
	पूर्ण अन्यथा अणु
		error = input_रेजिस्टर_device(pen_input_dev);
		अगर (error)
			जाओ fail;
	पूर्ण

	error = wacom_setup_touch_input_capabilities(touch_input_dev, wacom_wac);
	अगर (error) अणु
		/* no touch in use on this पूर्णांकerface */
		input_मुक्त_device(touch_input_dev);
		wacom_wac->touch_input = शून्य;
		touch_input_dev = शून्य;
	पूर्ण अन्यथा अणु
		error = input_रेजिस्टर_device(touch_input_dev);
		अगर (error)
			जाओ fail;
	पूर्ण

	error = wacom_setup_pad_input_capabilities(pad_input_dev, wacom_wac);
	अगर (error) अणु
		/* no pad in use on this पूर्णांकerface */
		input_मुक्त_device(pad_input_dev);
		wacom_wac->pad_input = शून्य;
		pad_input_dev = शून्य;
	पूर्ण अन्यथा अणु
		error = input_रेजिस्टर_device(pad_input_dev);
		अगर (error)
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	wacom_wac->pad_input = शून्य;
	wacom_wac->touch_input = शून्य;
	wacom_wac->pen_input = शून्य;
	वापस error;
पूर्ण

/*
 * Not all devices report physical dimensions from HID.
 * Compute the शेष from hardcoded logical dimension
 * and resolution beक्रमe driver overग_लिखोs them.
 */
अटल व्योम wacom_set_शेष_phy(काष्ठा wacom_features *features)
अणु
	अगर (features->x_resolution) अणु
		features->x_phy = (features->x_max * 100) /
					features->x_resolution;
		features->y_phy = (features->y_max * 100) /
					features->y_resolution;
	पूर्ण
पूर्ण

अटल व्योम wacom_calculate_res(काष्ठा wacom_features *features)
अणु
	/* set unit to "100th of a mm" क्रम devices not reported by HID */
	अगर (!features->unit) अणु
		features->unit = 0x11;
		features->unitExpo = -3;
	पूर्ण

	features->x_resolution = wacom_calc_hid_res(features->x_max,
						    features->x_phy,
						    features->unit,
						    features->unitExpo);
	features->y_resolution = wacom_calc_hid_res(features->y_max,
						    features->y_phy,
						    features->unit,
						    features->unitExpo);
पूर्ण

व्योम wacom_battery_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wacom *wacom = container_of(work, काष्ठा wacom, battery_work);

	अगर ((wacom->wacom_wac.features.quirks & WACOM_QUIRK_BATTERY) &&
	     !wacom->battery.battery) अणु
		wacom_initialize_battery(wacom);
	पूर्ण
	अन्यथा अगर (!(wacom->wacom_wac.features.quirks & WACOM_QUIRK_BATTERY) &&
		 wacom->battery.battery) अणु
		wacom_destroy_battery(wacom);
	पूर्ण
पूर्ण

अटल माप_प्रकार wacom_compute_pktlen(काष्ठा hid_device *hdev)
अणु
	काष्ठा hid_report_क्रमागत *report_क्रमागत;
	काष्ठा hid_report *report;
	माप_प्रकार size = 0;

	report_क्रमागत = hdev->report_क्रमागत + HID_INPUT_REPORT;

	list_क्रम_each_entry(report, &report_क्रमागत->report_list, list) अणु
		माप_प्रकार report_size = hid_report_len(report);
		अगर (report_size > size)
			size = report_size;
	पूर्ण

	वापस size;
पूर्ण

अटल व्योम wacom_update_name(काष्ठा wacom *wacom, स्थिर अक्षर *suffix)
अणु
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom_wac->features;
	अक्षर name[WACOM_NAME_MAX - 20]; /* Leave some room क्रम suffixes */

	/* Generic devices name unspecअगरied */
	अगर ((features->type == HID_GENERIC) && !म_भेद("Wacom HID", features->name)) अणु
		अक्षर *product_name = wacom->hdev->name;

		अगर (hid_is_using_ll_driver(wacom->hdev, &usb_hid_driver)) अणु
			काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(wacom->hdev->dev.parent);
			काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
			product_name = dev->product;
		पूर्ण

		अगर (wacom->hdev->bus == BUS_I2C) अणु
			snम_लिखो(name, माप(name), "%s %X",
				 features->name, wacom->hdev->product);
		पूर्ण अन्यथा अगर (म_माला(product_name, "Wacom") ||
			   म_माला(product_name, "wacom") ||
			   म_माला(product_name, "WACOM")) अणु
			strlcpy(name, product_name, माप(name));
		पूर्ण अन्यथा अणु
			snम_लिखो(name, माप(name), "Wacom %s", product_name);
		पूर्ण

		/* strip out excess whitespaces */
		जबतक (1) अणु
			अक्षर *gap = म_माला(name, "  ");
			अगर (gap == शून्य)
				अवरोध;
			/* shअगरt everything including the terminator */
			स_हटाओ(gap, gap+1, म_माप(gap));
		पूर्ण

		/* get rid of trailing whitespace */
		अगर (name[म_माप(name)-1] == ' ')
			name[म_माप(name)-1] = '\0';
	पूर्ण अन्यथा अणु
		strlcpy(name, features->name, माप(name));
	पूर्ण

	snम_लिखो(wacom_wac->name, माप(wacom_wac->name), "%s%s",
		 name, suffix);

	/* Append the device type to the name */
	snम_लिखो(wacom_wac->pen_name, माप(wacom_wac->pen_name),
		"%s%s Pen", name, suffix);
	snम_लिखो(wacom_wac->touch_name, माप(wacom_wac->touch_name),
		"%s%s Finger", name, suffix);
	snम_लिखो(wacom_wac->pad_name, माप(wacom_wac->pad_name),
		"%s%s Pad", name, suffix);
पूर्ण

अटल व्योम wacom_release_resources(काष्ठा wacom *wacom)
अणु
	काष्ठा hid_device *hdev = wacom->hdev;

	अगर (!wacom->resources)
		वापस;

	devres_release_group(&hdev->dev, wacom);

	wacom->resources = false;

	wacom->wacom_wac.pen_input = शून्य;
	wacom->wacom_wac.touch_input = शून्य;
	wacom->wacom_wac.pad_input = शून्य;
पूर्ण

अटल व्योम wacom_set_shared_values(काष्ठा wacom_wac *wacom_wac)
अणु
	अगर (wacom_wac->features.device_type & WACOM_DEVICETYPE_TOUCH) अणु
		wacom_wac->shared->type = wacom_wac->features.type;
		wacom_wac->shared->touch_input = wacom_wac->touch_input;
	पूर्ण

	अगर (wacom_wac->has_mute_touch_चयन) अणु
		wacom_wac->shared->has_mute_touch_चयन = true;
		wacom_wac->shared->is_touch_on = true;
	पूर्ण

	अगर (wacom_wac->shared->has_mute_touch_चयन &&
	    wacom_wac->shared->touch_input) अणु
		set_bit(EV_SW, wacom_wac->shared->touch_input->evbit);
		input_set_capability(wacom_wac->shared->touch_input, EV_SW,
				     SW_MUTE_DEVICE);
	पूर्ण
पूर्ण

अटल पूर्णांक wacom_parse_and_रेजिस्टर(काष्ठा wacom *wacom, bool wireless)
अणु
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom_wac->features;
	काष्ठा hid_device *hdev = wacom->hdev;
	पूर्णांक error;
	अचिन्हित पूर्णांक connect_mask = HID_CONNECT_HIDRAW;

	features->pktlen = wacom_compute_pktlen(hdev);
	अगर (features->pktlen > WACOM_PKGLEN_MAX)
		वापस -EINVAL;

	अगर (!devres_खोलो_group(&hdev->dev, wacom, GFP_KERNEL))
		वापस -ENOMEM;

	wacom->resources = true;

	error = wacom_allocate_inमाला_दो(wacom);
	अगर (error)
		जाओ fail;

	/*
	 * Bamboo Pad has a generic hid handling क्रम the Pen, and we चयन it
	 * पूर्णांकo debug mode क्रम the touch part.
	 * We ignore the other पूर्णांकerfaces.
	 */
	अगर (features->type == BAMBOO_PAD) अणु
		अगर (features->pktlen == WACOM_PKGLEN_PENABLED) अणु
			features->type = HID_GENERIC;
		पूर्ण अन्यथा अगर ((features->pktlen != WACOM_PKGLEN_BPAD_TOUCH) &&
			   (features->pktlen != WACOM_PKGLEN_BPAD_TOUCH_USB)) अणु
			error = -ENODEV;
			जाओ fail;
		पूर्ण
	पूर्ण

	/* set the शेष size in हाल we करो not get them from hid */
	wacom_set_शेष_phy(features);

	/* Retrieve the physical and logical size क्रम touch devices */
	wacom_retrieve_hid_descriptor(hdev, features);
	wacom_setup_device_quirks(wacom);

	अगर (features->device_type == WACOM_DEVICETYPE_NONE &&
	    features->type != WIRELESS) अणु
		error = features->type == HID_GENERIC ? -ENODEV : 0;

		dev_warn(&hdev->dev, "Unknown device_type for '%s'. %s.",
			 hdev->name,
			 error ? "Ignoring" : "Assuming pen");

		अगर (error)
			जाओ fail;

		features->device_type |= WACOM_DEVICETYPE_PEN;
	पूर्ण

	wacom_calculate_res(features);

	wacom_update_name(wacom, wireless ? " (WL)" : "");

	/* pen only Bamboo neither support touch nor pad */
	अगर ((features->type == BAMBOO_PEN) &&
	    ((features->device_type & WACOM_DEVICETYPE_TOUCH) ||
	    (features->device_type & WACOM_DEVICETYPE_PAD))) अणु
		error = -ENODEV;
		जाओ fail;
	पूर्ण

	error = wacom_add_shared_data(hdev);
	अगर (error)
		जाओ fail;

	अगर (!(features->device_type & WACOM_DEVICETYPE_WL_MONITOR) &&
	     (features->quirks & WACOM_QUIRK_BATTERY)) अणु
		error = wacom_initialize_battery(wacom);
		अगर (error)
			जाओ fail;
	पूर्ण

	error = wacom_रेजिस्टर_inमाला_दो(wacom);
	अगर (error)
		जाओ fail;

	अगर (wacom->wacom_wac.features.device_type & WACOM_DEVICETYPE_PAD) अणु
		error = wacom_initialize_leds(wacom);
		अगर (error)
			जाओ fail;

		error = wacom_initialize_remotes(wacom);
		अगर (error)
			जाओ fail;
	पूर्ण

	अगर (features->type == HID_GENERIC)
		connect_mask |= HID_CONNECT_DRIVER;

	/* Regular HID work starts now */
	error = hid_hw_start(hdev, connect_mask);
	अगर (error) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ fail;
	पूर्ण

	अगर (!wireless) अणु
		/* Note that अगर query fails it is not a hard failure */
		wacom_query_tablet_data(wacom);
	पूर्ण

	/* touch only Bamboo करोesn't support pen */
	अगर ((features->type == BAMBOO_TOUCH) &&
	    (features->device_type & WACOM_DEVICETYPE_PEN)) अणु
		cancel_delayed_work_sync(&wacom->init_work);
		_wacom_query_tablet_data(wacom);
		error = -ENODEV;
		जाओ fail_quirks;
	पूर्ण

	अगर (features->device_type & WACOM_DEVICETYPE_WL_MONITOR)
		error = hid_hw_खोलो(hdev);

	wacom_set_shared_values(wacom_wac);
	devres_बंद_group(&hdev->dev, wacom);

	वापस 0;

fail_quirks:
	hid_hw_stop(hdev);
fail:
	wacom_release_resources(wacom);
	वापस error;
पूर्ण

अटल व्योम wacom_wireless_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wacom *wacom = container_of(work, काष्ठा wacom, wireless_work);
	काष्ठा usb_device *usbdev = wacom->usbdev;
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा hid_device *hdev1, *hdev2;
	काष्ठा wacom *wacom1, *wacom2;
	काष्ठा wacom_wac *wacom_wac1, *wacom_wac2;
	पूर्णांक error;

	/*
	 * Regardless अगर this is a disconnect or a new tablet,
	 * हटाओ any existing input and battery devices.
	 */

	wacom_destroy_battery(wacom);

	/* Stylus पूर्णांकerface */
	hdev1 = usb_get_पूर्णांकfdata(usbdev->config->पूर्णांकerface[1]);
	wacom1 = hid_get_drvdata(hdev1);
	wacom_wac1 = &(wacom1->wacom_wac);
	wacom_release_resources(wacom1);

	/* Touch पूर्णांकerface */
	hdev2 = usb_get_पूर्णांकfdata(usbdev->config->पूर्णांकerface[2]);
	wacom2 = hid_get_drvdata(hdev2);
	wacom_wac2 = &(wacom2->wacom_wac);
	wacom_release_resources(wacom2);

	अगर (wacom_wac->pid == 0) अणु
		hid_info(wacom->hdev, "wireless tablet disconnected\n");
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा hid_device_id *id = wacom_ids;

		hid_info(wacom->hdev, "wireless tablet connected with PID %x\n",
			 wacom_wac->pid);

		जबतक (id->bus) अणु
			अगर (id->venकरोr == USB_VENDOR_ID_WACOM &&
			    id->product == wacom_wac->pid)
				अवरोध;
			id++;
		पूर्ण

		अगर (!id->bus) अणु
			hid_info(wacom->hdev, "ignoring unknown PID.\n");
			वापस;
		पूर्ण

		/* Stylus पूर्णांकerface */
		wacom_wac1->features =
			*((काष्ठा wacom_features *)id->driver_data);

		wacom_wac1->pid = wacom_wac->pid;
		hid_hw_stop(hdev1);
		error = wacom_parse_and_रेजिस्टर(wacom1, true);
		अगर (error)
			जाओ fail;

		/* Touch पूर्णांकerface */
		अगर (wacom_wac1->features.touch_max ||
		    (wacom_wac1->features.type >= INTUOSHT &&
		    wacom_wac1->features.type <= BAMBOO_PT)) अणु
			wacom_wac2->features =
				*((काष्ठा wacom_features *)id->driver_data);
			wacom_wac2->pid = wacom_wac->pid;
			hid_hw_stop(hdev2);
			error = wacom_parse_and_रेजिस्टर(wacom2, true);
			अगर (error)
				जाओ fail;
		पूर्ण

		strlcpy(wacom_wac->name, wacom_wac1->name,
			माप(wacom_wac->name));
		error = wacom_initialize_battery(wacom);
		अगर (error)
			जाओ fail;
	पूर्ण

	वापस;

fail:
	wacom_release_resources(wacom1);
	wacom_release_resources(wacom2);
	वापस;
पूर्ण

अटल व्योम wacom_remote_destroy_one(काष्ठा wacom *wacom, अचिन्हित पूर्णांक index)
अणु
	काष्ठा wacom_remote *remote = wacom->remote;
	u32 serial = remote->remotes[index].serial;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < WACOM_MAX_REMOTES; i++) अणु
		अगर (remote->remotes[i].serial == serial) अणु

			spin_lock_irqsave(&remote->remote_lock, flags);
			remote->remotes[i].रेजिस्टरed = false;
			spin_unlock_irqrestore(&remote->remote_lock, flags);

			अगर (remote->remotes[i].battery.battery)
				devres_release_group(&wacom->hdev->dev,
						     &remote->remotes[i].battery.bat_desc);

			अगर (remote->remotes[i].group.name)
				devres_release_group(&wacom->hdev->dev,
						     &remote->remotes[i]);

			remote->remotes[i].serial = 0;
			remote->remotes[i].group.name = शून्य;
			remote->remotes[i].battery.battery = शून्य;
			wacom->led.groups[i].select = WACOM_STATUS_UNKNOWN;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक wacom_remote_create_one(काष्ठा wacom *wacom, u32 serial,
				   अचिन्हित पूर्णांक index)
अणु
	काष्ठा wacom_remote *remote = wacom->remote;
	काष्ठा device *dev = &wacom->hdev->dev;
	पूर्णांक error, k;

	/* A remote can pair more than once with an EKR,
	 * check to make sure this serial isn't alपढ़ोy paired.
	 */
	क्रम (k = 0; k < WACOM_MAX_REMOTES; k++) अणु
		अगर (remote->remotes[k].serial == serial)
			अवरोध;
	पूर्ण

	अगर (k < WACOM_MAX_REMOTES) अणु
		remote->remotes[index].serial = serial;
		वापस 0;
	पूर्ण

	अगर (!devres_खोलो_group(dev, &remote->remotes[index], GFP_KERNEL))
		वापस -ENOMEM;

	error = wacom_remote_create_attr_group(wacom, serial, index);
	अगर (error)
		जाओ fail;

	remote->remotes[index].input = wacom_allocate_input(wacom);
	अगर (!remote->remotes[index].input) अणु
		error = -ENOMEM;
		जाओ fail;
	पूर्ण
	remote->remotes[index].input->uniq = remote->remotes[index].group.name;
	remote->remotes[index].input->name = wacom->wacom_wac.pad_name;

	अगर (!remote->remotes[index].input->name) अणु
		error = -EINVAL;
		जाओ fail;
	पूर्ण

	error = wacom_setup_pad_input_capabilities(remote->remotes[index].input,
						   &wacom->wacom_wac);
	अगर (error)
		जाओ fail;

	remote->remotes[index].serial = serial;

	error = input_रेजिस्टर_device(remote->remotes[index].input);
	अगर (error)
		जाओ fail;

	error = wacom_led_groups_alloc_and_रेजिस्टर_one(
					&remote->remotes[index].input->dev,
					wacom, index, 3, true);
	अगर (error)
		जाओ fail;

	remote->remotes[index].रेजिस्टरed = true;

	devres_बंद_group(dev, &remote->remotes[index]);
	वापस 0;

fail:
	devres_release_group(dev, &remote->remotes[index]);
	remote->remotes[index].serial = 0;
	वापस error;
पूर्ण

अटल पूर्णांक wacom_remote_attach_battery(काष्ठा wacom *wacom, पूर्णांक index)
अणु
	काष्ठा wacom_remote *remote = wacom->remote;
	पूर्णांक error;

	अगर (!remote->remotes[index].रेजिस्टरed)
		वापस 0;

	अगर (remote->remotes[index].battery.battery)
		वापस 0;

	अगर (wacom->led.groups[index].select == WACOM_STATUS_UNKNOWN)
		वापस 0;

	error = __wacom_initialize_battery(wacom,
					&wacom->remote->remotes[index].battery);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल व्योम wacom_remote_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wacom *wacom = container_of(work, काष्ठा wacom, remote_work);
	काष्ठा wacom_remote *remote = wacom->remote;
	काष्ठा wacom_remote_data data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक count;
	u32 serial;
	पूर्णांक i;

	spin_lock_irqsave(&remote->remote_lock, flags);

	count = kfअगरo_out(&remote->remote_fअगरo, &data, माप(data));

	अगर (count != माप(data)) अणु
		hid_err(wacom->hdev,
			"workitem triggered without status available\n");
		spin_unlock_irqrestore(&remote->remote_lock, flags);
		वापस;
	पूर्ण

	अगर (!kfअगरo_is_empty(&remote->remote_fअगरo))
		wacom_schedule_work(&wacom->wacom_wac, WACOM_WORKER_REMOTE);

	spin_unlock_irqrestore(&remote->remote_lock, flags);

	क्रम (i = 0; i < WACOM_MAX_REMOTES; i++) अणु
		serial = data.remote[i].serial;
		अगर (data.remote[i].connected) अणु

			अगर (remote->remotes[i].serial == serial) अणु
				wacom_remote_attach_battery(wacom, i);
				जारी;
			पूर्ण

			अगर (remote->remotes[i].serial)
				wacom_remote_destroy_one(wacom, i);

			wacom_remote_create_one(wacom, serial, i);

		पूर्ण अन्यथा अगर (remote->remotes[i].serial) अणु
			wacom_remote_destroy_one(wacom, i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम wacom_mode_change_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wacom *wacom = container_of(work, काष्ठा wacom, mode_change_work);
	काष्ठा wacom_shared *shared = wacom->wacom_wac.shared;
	काष्ठा wacom *wacom1 = शून्य;
	काष्ठा wacom *wacom2 = शून्य;
	bool is_direct = wacom->wacom_wac.is_direct_mode;
	पूर्णांक error = 0;

	अगर (shared->pen) अणु
		wacom1 = hid_get_drvdata(shared->pen);
		wacom_release_resources(wacom1);
		hid_hw_stop(wacom1->hdev);
		wacom1->wacom_wac.has_mode_change = true;
		wacom1->wacom_wac.is_direct_mode = is_direct;
	पूर्ण

	अगर (shared->touch) अणु
		wacom2 = hid_get_drvdata(shared->touch);
		wacom_release_resources(wacom2);
		hid_hw_stop(wacom2->hdev);
		wacom2->wacom_wac.has_mode_change = true;
		wacom2->wacom_wac.is_direct_mode = is_direct;
	पूर्ण

	अगर (wacom1) अणु
		error = wacom_parse_and_रेजिस्टर(wacom1, false);
		अगर (error)
			वापस;
	पूर्ण

	अगर (wacom2) अणु
		error = wacom_parse_and_रेजिस्टर(wacom2, false);
		अगर (error)
			वापस;
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक wacom_probe(काष्ठा hid_device *hdev,
		स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा wacom *wacom;
	काष्ठा wacom_wac *wacom_wac;
	काष्ठा wacom_features *features;
	पूर्णांक error;

	अगर (!id->driver_data)
		वापस -EINVAL;

	hdev->quirks |= HID_QUIRK_NO_INIT_REPORTS;

	/* hid-core sets this quirk क्रम the boot पूर्णांकerface */
	hdev->quirks &= ~HID_QUIRK_NOGET;

	wacom = devm_kzalloc(&hdev->dev, माप(काष्ठा wacom), GFP_KERNEL);
	अगर (!wacom)
		वापस -ENOMEM;

	hid_set_drvdata(hdev, wacom);
	wacom->hdev = hdev;

	wacom_wac = &wacom->wacom_wac;
	wacom_wac->features = *((काष्ठा wacom_features *)id->driver_data);
	features = &wacom_wac->features;

	अगर (features->check_क्रम_hid_type && features->hid_type != hdev->type)
		वापस -ENODEV;

	error = wacom_devm_kfअगरo_alloc(wacom);
	अगर (error)
		वापस error;

	wacom_wac->hid_data.inpuपंचांगode = -1;
	wacom_wac->mode_report = -1;

	wacom->usbdev = dev;
	wacom->पूर्णांकf = पूर्णांकf;
	mutex_init(&wacom->lock);
	INIT_DELAYED_WORK(&wacom->init_work, wacom_init_work);
	INIT_WORK(&wacom->wireless_work, wacom_wireless_work);
	INIT_WORK(&wacom->battery_work, wacom_battery_work);
	INIT_WORK(&wacom->remote_work, wacom_remote_work);
	INIT_WORK(&wacom->mode_change_work, wacom_mode_change_work);

	/* ask क्रम the report descriptor to be loaded by HID */
	error = hid_parse(hdev);
	अगर (error) अणु
		hid_err(hdev, "parse failed\n");
		वापस error;
	पूर्ण

	error = wacom_parse_and_रेजिस्टर(wacom, false);
	अगर (error)
		वापस error;

	अगर (hdev->bus == BUS_BLUETOOTH) अणु
		error = device_create_file(&hdev->dev, &dev_attr_speed);
		अगर (error)
			hid_warn(hdev,
				 "can't create sysfs speed attribute err: %d\n",
				 error);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wacom_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);
	काष्ठा wacom_wac *wacom_wac = &wacom->wacom_wac;
	काष्ठा wacom_features *features = &wacom_wac->features;

	अगर (features->device_type & WACOM_DEVICETYPE_WL_MONITOR)
		hid_hw_बंद(hdev);

	hid_hw_stop(hdev);

	cancel_delayed_work_sync(&wacom->init_work);
	cancel_work_sync(&wacom->wireless_work);
	cancel_work_sync(&wacom->battery_work);
	cancel_work_sync(&wacom->remote_work);
	cancel_work_sync(&wacom->mode_change_work);
	अगर (hdev->bus == BUS_BLUETOOTH)
		device_हटाओ_file(&hdev->dev, &dev_attr_speed);

	/* make sure we करोn't trigger the LEDs */
	wacom_led_groups_release(wacom);

	अगर (wacom->wacom_wac.features.type != REMOTE)
		wacom_release_resources(wacom);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wacom_resume(काष्ठा hid_device *hdev)
अणु
	काष्ठा wacom *wacom = hid_get_drvdata(hdev);

	mutex_lock(&wacom->lock);

	/* चयन to wacom mode first */
	_wacom_query_tablet_data(wacom);
	wacom_led_control(wacom);

	mutex_unlock(&wacom->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक wacom_reset_resume(काष्ठा hid_device *hdev)
अणु
	वापस wacom_resume(hdev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा hid_driver wacom_driver = अणु
	.name =		"wacom",
	.id_table =	wacom_ids,
	.probe =	wacom_probe,
	.हटाओ =	wacom_हटाओ,
	.report =	wacom_wac_report,
#अगर_घोषित CONFIG_PM
	.resume =	wacom_resume,
	.reset_resume =	wacom_reset_resume,
#पूर्ण_अगर
	.raw_event =	wacom_raw_event,
पूर्ण;
module_hid_driver(wacom_driver);

MODULE_VERSION(DRIVER_VERSION);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
