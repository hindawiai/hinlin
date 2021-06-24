<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2013 Andrew Duggan <aduggan@synaptics.com>
 *  Copyright (c) 2013 Synaptics Incorporated
 *  Copyright (c) 2014 Benjamin Tissoires <benjamin.tissoires@gmail.com>
 *  Copyright (c) 2014 Red Hat, Inc
 */

#समावेश <linux/kernel.h>
#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/rmi.h>
#समावेश "hid-ids.h"

#घोषणा RMI_MOUSE_REPORT_ID		0x01 /* Mouse emulation Report */
#घोषणा RMI_WRITE_REPORT_ID		0x09 /* Output Report */
#घोषणा RMI_READ_ADDR_REPORT_ID		0x0a /* Output Report */
#घोषणा RMI_READ_DATA_REPORT_ID		0x0b /* Input Report */
#घोषणा RMI_ATTN_REPORT_ID		0x0c /* Input Report */
#घोषणा RMI_SET_RMI_MODE_REPORT_ID	0x0f /* Feature Report */

/* flags */
#घोषणा RMI_READ_REQUEST_PENDING	0
#घोषणा RMI_READ_DATA_PENDING		1
#घोषणा RMI_STARTED			2

/* device flags */
#घोषणा RMI_DEVICE			BIT(0)
#घोषणा RMI_DEVICE_HAS_PHYS_BUTTONS	BIT(1)
#घोषणा RMI_DEVICE_OUTPUT_SET_REPORT	BIT(2)

/*
 * retrieve the ctrl रेजिस्टरs
 * the ctrl रेजिस्टर has a size of 20 but a fw bug split it पूर्णांकo 16 + 4,
 * and there is no way to know अगर the first 20 bytes are here or not.
 * We use only the first 12 bytes, so get only them.
 */
#घोषणा RMI_F11_CTRL_REG_COUNT		12

क्रमागत rmi_mode_type अणु
	RMI_MODE_OFF			= 0,
	RMI_MODE_ATTN_REPORTS		= 1,
	RMI_MODE_NO_PACKED_ATTN_REPORTS	= 2,
पूर्ण;

/**
 * काष्ठा rmi_data - stores inक्रमmation क्रम hid communication
 *
 * @page_mutex: Locks current page to aव्योम changing pages in unexpected ways.
 * @page: Keeps track of the current भव page
 * @xport: transport device to be रेजिस्टरed with the RMI4 core.
 *
 * @रुको: Used क्रम रुकोing क्रम पढ़ो data
 *
 * @ग_लिखोReport: output buffer when writing RMI रेजिस्टरs
 * @पढ़ोReport: input buffer when पढ़ोing RMI रेजिस्टरs
 *
 * @input_report_size: size of an input report (advertised by HID)
 * @output_report_size: size of an output report (advertised by HID)
 *
 * @flags: flags क्रम the current device (started, पढ़ोing, etc...)
 *
 * @reset_work: worker which will be called in हाल of a mouse report
 * @hdev: poपूर्णांकer to the काष्ठा hid_device
 *
 * @device_flags: flags which describe the device
 *
 * @करोमुख्य: the IRQ करोमुख्य allocated क्रम this RMI4 device
 * @rmi_irq: the irq that will be used to generate events to rmi-core
 */
काष्ठा rmi_data अणु
	काष्ठा mutex page_mutex;
	पूर्णांक page;
	काष्ठा rmi_transport_dev xport;

	रुको_queue_head_t रुको;

	u8 *ग_लिखोReport;
	u8 *पढ़ोReport;

	u32 input_report_size;
	u32 output_report_size;

	अचिन्हित दीर्घ flags;

	काष्ठा work_काष्ठा reset_work;
	काष्ठा hid_device *hdev;

	अचिन्हित दीर्घ device_flags;

	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक rmi_irq;
पूर्ण;

#घोषणा RMI_PAGE(addr) (((addr) >> 8) & 0xff)

अटल पूर्णांक rmi_ग_लिखो_report(काष्ठा hid_device *hdev, u8 *report, पूर्णांक len);

/**
 * rmi_set_page - Set RMI page
 * @hdev: The poपूर्णांकer to the hid_device काष्ठा
 * @page: The new page address.
 *
 * RMI devices have 16-bit addressing, but some of the physical
 * implementations (like SMBus) only have 8-bit addressing. So RMI implements
 * a page address at 0xff of every page so we can reliable page addresses
 * every 256 रेजिस्टरs.
 *
 * The page_mutex lock must be held when this function is entered.
 *
 * Returns zero on success, non-zero on failure.
 */
अटल पूर्णांक rmi_set_page(काष्ठा hid_device *hdev, u8 page)
अणु
	काष्ठा rmi_data *data = hid_get_drvdata(hdev);
	पूर्णांक retval;

	data->ग_लिखोReport[0] = RMI_WRITE_REPORT_ID;
	data->ग_लिखोReport[1] = 1;
	data->ग_लिखोReport[2] = 0xFF;
	data->ग_लिखोReport[4] = page;

	retval = rmi_ग_लिखो_report(hdev, data->ग_लिखोReport,
			data->output_report_size);
	अगर (retval != data->output_report_size) अणु
		dev_err(&hdev->dev,
			"%s: set page failed: %d.", __func__, retval);
		वापस retval;
	पूर्ण

	data->page = page;
	वापस 0;
पूर्ण

अटल पूर्णांक rmi_set_mode(काष्ठा hid_device *hdev, u8 mode)
अणु
	पूर्णांक ret;
	स्थिर u8 txbuf[2] = अणुRMI_SET_RMI_MODE_REPORT_ID, modeपूर्ण;
	u8 *buf;

	buf = kmemdup(txbuf, माप(txbuf), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = hid_hw_raw_request(hdev, RMI_SET_RMI_MODE_REPORT_ID, buf,
			माप(txbuf), HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
	kमुक्त(buf);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "unable to set rmi mode to %d (%d)\n", mode,
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_ग_लिखो_report(काष्ठा hid_device *hdev, u8 *report, पूर्णांक len)
अणु
	काष्ठा rmi_data *data = hid_get_drvdata(hdev);
	पूर्णांक ret;

	अगर (data->device_flags & RMI_DEVICE_OUTPUT_SET_REPORT) अणु
		/*
		 * Talk to device by using SET_REPORT requests instead.
		 */
		ret = hid_hw_raw_request(hdev, report[0], report,
				len, HID_OUTPUT_REPORT, HID_REQ_SET_REPORT);
	पूर्ण अन्यथा अणु
		ret = hid_hw_output_report(hdev, (व्योम *)report, len);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed to write hid report (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rmi_hid_पढ़ो_block(काष्ठा rmi_transport_dev *xport, u16 addr,
		व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा rmi_data *data = container_of(xport, काष्ठा rmi_data, xport);
	काष्ठा hid_device *hdev = data->hdev;
	पूर्णांक ret;
	पूर्णांक bytes_पढ़ो;
	पूर्णांक bytes_needed;
	पूर्णांक retries;
	पूर्णांक पढ़ो_input_count;

	mutex_lock(&data->page_mutex);

	अगर (RMI_PAGE(addr) != data->page) अणु
		ret = rmi_set_page(hdev, RMI_PAGE(addr));
		अगर (ret < 0)
			जाओ निकास;
	पूर्ण

	क्रम (retries = 5; retries > 0; retries--) अणु
		data->ग_लिखोReport[0] = RMI_READ_ADDR_REPORT_ID;
		data->ग_लिखोReport[1] = 0; /* old 1 byte पढ़ो count */
		data->ग_लिखोReport[2] = addr & 0xFF;
		data->ग_लिखोReport[3] = (addr >> 8) & 0xFF;
		data->ग_लिखोReport[4] = len  & 0xFF;
		data->ग_लिखोReport[5] = (len >> 8) & 0xFF;

		set_bit(RMI_READ_REQUEST_PENDING, &data->flags);

		ret = rmi_ग_लिखो_report(hdev, data->ग_लिखोReport,
						data->output_report_size);
		अगर (ret != data->output_report_size) अणु
			dev_err(&hdev->dev,
				"failed to write request output report (%d)\n",
				ret);
			जाओ निकास;
		पूर्ण

		bytes_पढ़ो = 0;
		bytes_needed = len;
		जबतक (bytes_पढ़ो < len) अणु
			अगर (!रुको_event_समयout(data->रुको,
				test_bit(RMI_READ_DATA_PENDING, &data->flags),
					msecs_to_jअगरfies(1000))) अणु
				hid_warn(hdev, "%s: timeout elapsed\n",
					 __func__);
				ret = -EAGAIN;
				अवरोध;
			पूर्ण

			पढ़ो_input_count = data->पढ़ोReport[1];
			स_नकल(buf + bytes_पढ़ो, &data->पढ़ोReport[2],
				पढ़ो_input_count < bytes_needed ?
					पढ़ो_input_count : bytes_needed);

			bytes_पढ़ो += पढ़ो_input_count;
			bytes_needed -= पढ़ो_input_count;
			clear_bit(RMI_READ_DATA_PENDING, &data->flags);
		पूर्ण

		अगर (ret >= 0) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

निकास:
	clear_bit(RMI_READ_REQUEST_PENDING, &data->flags);
	mutex_unlock(&data->page_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक rmi_hid_ग_लिखो_block(काष्ठा rmi_transport_dev *xport, u16 addr,
		स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा rmi_data *data = container_of(xport, काष्ठा rmi_data, xport);
	काष्ठा hid_device *hdev = data->hdev;
	पूर्णांक ret;

	mutex_lock(&data->page_mutex);

	अगर (RMI_PAGE(addr) != data->page) अणु
		ret = rmi_set_page(hdev, RMI_PAGE(addr));
		अगर (ret < 0)
			जाओ निकास;
	पूर्ण

	data->ग_लिखोReport[0] = RMI_WRITE_REPORT_ID;
	data->ग_लिखोReport[1] = len;
	data->ग_लिखोReport[2] = addr & 0xFF;
	data->ग_लिखोReport[3] = (addr >> 8) & 0xFF;
	स_नकल(&data->ग_लिखोReport[4], buf, len);

	ret = rmi_ग_लिखो_report(hdev, data->ग_लिखोReport,
					data->output_report_size);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev,
			"failed to write request output report (%d)\n",
			ret);
		जाओ निकास;
	पूर्ण
	ret = 0;

निकास:
	mutex_unlock(&data->page_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक rmi_reset_attn_mode(काष्ठा hid_device *hdev)
अणु
	काष्ठा rmi_data *data = hid_get_drvdata(hdev);
	काष्ठा rmi_device *rmi_dev = data->xport.rmi_dev;
	पूर्णांक ret;

	ret = rmi_set_mode(hdev, RMI_MODE_ATTN_REPORTS);
	अगर (ret)
		वापस ret;

	अगर (test_bit(RMI_STARTED, &data->flags))
		ret = rmi_dev->driver->reset_handler(rmi_dev);

	वापस ret;
पूर्ण

अटल व्योम rmi_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rmi_data *hdata = container_of(work, काष्ठा rmi_data,
						reset_work);

	/* चयन the device to RMI अगर we receive a generic mouse report */
	rmi_reset_attn_mode(hdata->hdev);
पूर्ण

अटल पूर्णांक rmi_input_event(काष्ठा hid_device *hdev, u8 *data, पूर्णांक size)
अणु
	काष्ठा rmi_data *hdata = hid_get_drvdata(hdev);
	काष्ठा rmi_device *rmi_dev = hdata->xport.rmi_dev;
	अचिन्हित दीर्घ flags;

	अगर (!(test_bit(RMI_STARTED, &hdata->flags)))
		वापस 0;

	local_irq_save(flags);

	rmi_set_attn_data(rmi_dev, data[1], &data[2], size - 2);

	generic_handle_irq(hdata->rmi_irq);

	local_irq_restore(flags);

	वापस 1;
पूर्ण

अटल पूर्णांक rmi_पढ़ो_data_event(काष्ठा hid_device *hdev, u8 *data, पूर्णांक size)
अणु
	काष्ठा rmi_data *hdata = hid_get_drvdata(hdev);

	अगर (!test_bit(RMI_READ_REQUEST_PENDING, &hdata->flags)) अणु
		hid_dbg(hdev, "no read request pending\n");
		वापस 0;
	पूर्ण

	स_नकल(hdata->पढ़ोReport, data, size < hdata->input_report_size ?
			size : hdata->input_report_size);
	set_bit(RMI_READ_DATA_PENDING, &hdata->flags);
	wake_up(&hdata->रुको);

	वापस 1;
पूर्ण

अटल पूर्णांक rmi_check_sanity(काष्ठा hid_device *hdev, u8 *data, पूर्णांक size)
अणु
	पूर्णांक valid_size = size;
	/*
	 * On the Dell XPS 13 9333, the bus someबार get confused and fills
	 * the report with a sentinel value "ff". Synaptics told us that such
	 * behavior करोes not comes from the touchpad itself, so we filter out
	 * such reports here.
	 */

	जबतक ((data[valid_size - 1] == 0xff) && valid_size > 0)
		valid_size--;

	वापस valid_size;
पूर्ण

अटल पूर्णांक rmi_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा rmi_data *hdata = hid_get_drvdata(hdev);

	अगर (!(hdata->device_flags & RMI_DEVICE))
		वापस 0;

	size = rmi_check_sanity(hdev, data, size);
	अगर (size < 2)
		वापस 0;

	चयन (data[0]) अणु
	हाल RMI_READ_DATA_REPORT_ID:
		वापस rmi_पढ़ो_data_event(hdev, data, size);
	हाल RMI_ATTN_REPORT_ID:
		वापस rmi_input_event(hdev, data, size);
	शेष:
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
			काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा rmi_data *data = hid_get_drvdata(hdev);

	अगर ((data->device_flags & RMI_DEVICE) &&
	    (field->application == HID_GD_POINTER ||
	    field->application == HID_GD_MOUSE)) अणु
		अगर (data->device_flags & RMI_DEVICE_HAS_PHYS_BUTTONS) अणु
			अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON)
				वापस 0;

			अगर ((usage->hid == HID_GD_X || usage->hid == HID_GD_Y)
			    && !value)
				वापस 1;
		पूर्ण

		schedule_work(&data->reset_work);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rmi_report(काष्ठा hid_device *hid, काष्ठा hid_report *report)
अणु
	काष्ठा hid_field *field = report->field[0];

	अगर (!(hid->claimed & HID_CLAIMED_INPUT))
		वापस;

	चयन (report->id) अणु
	हाल RMI_READ_DATA_REPORT_ID:
	हाल RMI_ATTN_REPORT_ID:
		वापस;
	पूर्ण

	अगर (field && field->hidinput && field->hidinput->input)
		input_sync(field->hidinput->input);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rmi_suspend(काष्ठा hid_device *hdev, pm_message_t message)
अणु
	काष्ठा rmi_data *data = hid_get_drvdata(hdev);
	काष्ठा rmi_device *rmi_dev = data->xport.rmi_dev;
	पूर्णांक ret;

	अगर (!(data->device_flags & RMI_DEVICE))
		वापस 0;

	ret = rmi_driver_suspend(rmi_dev, false);
	अगर (ret) अणु
		hid_warn(hdev, "Failed to suspend device: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_post_resume(काष्ठा hid_device *hdev)
अणु
	काष्ठा rmi_data *data = hid_get_drvdata(hdev);
	काष्ठा rmi_device *rmi_dev = data->xport.rmi_dev;
	पूर्णांक ret;

	अगर (!(data->device_flags & RMI_DEVICE))
		वापस 0;

	/* Make sure the HID device is पढ़ोy to receive events */
	ret = hid_hw_खोलो(hdev);
	अगर (ret)
		वापस ret;

	ret = rmi_reset_attn_mode(hdev);
	अगर (ret)
		जाओ out;

	ret = rmi_driver_resume(rmi_dev, false);
	अगर (ret) अणु
		hid_warn(hdev, "Failed to resume device: %d\n", ret);
		जाओ out;
	पूर्ण

out:
	hid_hw_बंद(hdev);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक rmi_hid_reset(काष्ठा rmi_transport_dev *xport, u16 reset_addr)
अणु
	काष्ठा rmi_data *data = container_of(xport, काष्ठा rmi_data, xport);
	काष्ठा hid_device *hdev = data->hdev;

	वापस rmi_reset_attn_mode(hdev);
पूर्ण

अटल पूर्णांक rmi_input_configured(काष्ठा hid_device *hdev, काष्ठा hid_input *hi)
अणु
	काष्ठा rmi_data *data = hid_get_drvdata(hdev);
	काष्ठा input_dev *input = hi->input;
	पूर्णांक ret = 0;

	अगर (!(data->device_flags & RMI_DEVICE))
		वापस 0;

	data->xport.input = input;

	hid_dbg(hdev, "Opening low level driver\n");
	ret = hid_hw_खोलो(hdev);
	अगर (ret)
		वापस ret;

	/* Allow incoming hid reports */
	hid_device_io_start(hdev);

	ret = rmi_set_mode(hdev, RMI_MODE_ATTN_REPORTS);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed to set rmi mode\n");
		जाओ निकास;
	पूर्ण

	ret = rmi_set_page(hdev, 0);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed to set page select to 0.\n");
		जाओ निकास;
	पूर्ण

	ret = rmi_रेजिस्टर_transport_device(&data->xport);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed to register transport driver\n");
		जाओ निकास;
	पूर्ण

	set_bit(RMI_STARTED, &data->flags);

निकास:
	hid_device_io_stop(hdev);
	hid_hw_बंद(hdev);
	वापस ret;
पूर्ण

अटल पूर्णांक rmi_input_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा rmi_data *data = hid_get_drvdata(hdev);

	/*
	 * we want to make HID ignore the advertised HID collection
	 * क्रम RMI deivces
	 */
	अगर (data->device_flags & RMI_DEVICE) अणु
		अगर ((data->device_flags & RMI_DEVICE_HAS_PHYS_BUTTONS) &&
		    ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON))
			वापस 0;

		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_check_valid_report_id(काष्ठा hid_device *hdev, अचिन्हित type,
		अचिन्हित id, काष्ठा hid_report **report)
अणु
	पूर्णांक i;

	*report = hdev->report_क्रमागत[type].report_id_hash[id];
	अगर (*report) अणु
		क्रम (i = 0; i < (*report)->maxfield; i++) अणु
			अचिन्हित app = (*report)->field[i]->application;
			अगर ((app & HID_USAGE_PAGE) >= HID_UP_MSVENDOR)
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा rmi_device_platक्रमm_data rmi_hid_pdata = अणु
	.sensor_pdata = अणु
		.sensor_type = rmi_sensor_touchpad,
		.axis_align.flip_y = true,
		.dribble = RMI_REG_STATE_ON,
		.palm_detect = RMI_REG_STATE_OFF,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rmi_transport_ops hid_rmi_ops = अणु
	.ग_लिखो_block	= rmi_hid_ग_लिखो_block,
	.पढ़ो_block	= rmi_hid_पढ़ो_block,
	.reset		= rmi_hid_reset,
पूर्ण;

अटल व्योम rmi_irq_tearकरोwn(व्योम *data)
अणु
	काष्ठा rmi_data *hdata = data;
	काष्ठा irq_करोमुख्य *करोमुख्य = hdata->करोमुख्य;

	अगर (!करोमुख्य)
		वापस;

	irq_dispose_mapping(irq_find_mapping(करोमुख्य, 0));

	irq_करोमुख्य_हटाओ(करोमुख्य);
	hdata->करोमुख्य = शून्य;
	hdata->rmi_irq = 0;
पूर्ण

अटल पूर्णांक rmi_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
		       irq_hw_number_t hw_irq_num)
अणु
	irq_set_chip_and_handler(virq, &dummy_irq_chip, handle_simple_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops rmi_irq_ops = अणु
	.map = rmi_irq_map,
पूर्ण;

अटल पूर्णांक rmi_setup_irq_करोमुख्य(काष्ठा hid_device *hdev)
अणु
	काष्ठा rmi_data *hdata = hid_get_drvdata(hdev);
	पूर्णांक ret;

	hdata->करोमुख्य = irq_करोमुख्य_create_linear(hdev->dev.fwnode, 1,
						 &rmi_irq_ops, hdata);
	अगर (!hdata->करोमुख्य)
		वापस -ENOMEM;

	ret = devm_add_action_or_reset(&hdev->dev, &rmi_irq_tearकरोwn, hdata);
	अगर (ret)
		वापस ret;

	hdata->rmi_irq = irq_create_mapping(hdata->करोमुख्य, 0);
	अगर (hdata->rmi_irq <= 0) अणु
		hid_err(hdev, "Can't allocate an IRQ\n");
		वापस hdata->rmi_irq < 0 ? hdata->rmi_irq : -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा rmi_data *data = शून्य;
	पूर्णांक ret;
	माप_प्रकार alloc_size;
	काष्ठा hid_report *input_report;
	काष्ठा hid_report *output_report;
	काष्ठा hid_report *feature_report;

	data = devm_kzalloc(&hdev->dev, माप(काष्ठा rmi_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	INIT_WORK(&data->reset_work, rmi_reset_work);
	data->hdev = hdev;

	hid_set_drvdata(hdev, data);

	hdev->quirks |= HID_QUIRK_NO_INIT_REPORTS;
	hdev->quirks |= HID_QUIRK_NO_INPUT_SYNC;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		वापस ret;
	पूर्ण

	अगर (id->driver_data)
		data->device_flags = id->driver_data;

	/*
	 * Check क्रम the RMI specअगरic report ids. If they are misisng
	 * simply वापस and let the events be processed by hid-input
	 */
	अगर (!rmi_check_valid_report_id(hdev, HID_FEATURE_REPORT,
	    RMI_SET_RMI_MODE_REPORT_ID, &feature_report)) अणु
		hid_dbg(hdev, "device does not have set mode feature report\n");
		जाओ start;
	पूर्ण

	अगर (!rmi_check_valid_report_id(hdev, HID_INPUT_REPORT,
	    RMI_ATTN_REPORT_ID, &input_report)) अणु
		hid_dbg(hdev, "device does not have attention input report\n");
		जाओ start;
	पूर्ण

	data->input_report_size = hid_report_len(input_report);

	अगर (!rmi_check_valid_report_id(hdev, HID_OUTPUT_REPORT,
	    RMI_WRITE_REPORT_ID, &output_report)) अणु
		hid_dbg(hdev,
			"device does not have rmi write output report\n");
		जाओ start;
	पूर्ण

	data->output_report_size = hid_report_len(output_report);

	data->device_flags |= RMI_DEVICE;
	alloc_size = data->output_report_size + data->input_report_size;

	data->ग_लिखोReport = devm_kzalloc(&hdev->dev, alloc_size, GFP_KERNEL);
	अगर (!data->ग_लिखोReport) अणु
		hid_err(hdev, "failed to allocate buffer for HID reports\n");
		वापस -ENOMEM;
	पूर्ण

	data->पढ़ोReport = data->ग_लिखोReport + data->output_report_size;

	init_रुकोqueue_head(&data->रुको);

	mutex_init(&data->page_mutex);

	ret = rmi_setup_irq_करोमुख्य(hdev);
	अगर (ret) अणु
		hid_err(hdev, "failed to allocate IRQ domain\n");
		वापस ret;
	पूर्ण

	अगर (data->device_flags & RMI_DEVICE_HAS_PHYS_BUTTONS)
		rmi_hid_pdata.gpio_data.disable = true;

	data->xport.dev = hdev->dev.parent;
	data->xport.pdata = rmi_hid_pdata;
	data->xport.pdata.irq = data->rmi_irq;
	data->xport.proto_name = "hid";
	data->xport.ops = &hid_rmi_ops;

start:
	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rmi_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा rmi_data *hdata = hid_get_drvdata(hdev);

	अगर ((hdata->device_flags & RMI_DEVICE)
	    && test_bit(RMI_STARTED, &hdata->flags)) अणु
		clear_bit(RMI_STARTED, &hdata->flags);
		cancel_work_sync(&hdata->reset_work);
		rmi_unरेजिस्टर_transport_device(&hdata->xport);
	पूर्ण

	hid_hw_stop(hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id rmi_id[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_RAZER, USB_DEVICE_ID_RAZER_BLADE_14),
		.driver_data = RMI_DEVICE_HAS_PHYS_BUTTONS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LENOVO, USB_DEVICE_ID_LENOVO_X1_COVER) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_PRIMAX, USB_DEVICE_ID_PRIMAX_REZEL) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SYNAPTICS, USB_DEVICE_ID_SYNAPTICS_ACER_SWITCH5),
		.driver_data = RMI_DEVICE_OUTPUT_SET_REPORT पूर्ण,
	अणु HID_DEVICE(HID_BUS_ANY, HID_GROUP_RMI, HID_ANY_ID, HID_ANY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, rmi_id);

अटल काष्ठा hid_driver rmi_driver = अणु
	.name = "hid-rmi",
	.id_table		= rmi_id,
	.probe			= rmi_probe,
	.हटाओ			= rmi_हटाओ,
	.event			= rmi_event,
	.raw_event		= rmi_raw_event,
	.report			= rmi_report,
	.input_mapping		= rmi_input_mapping,
	.input_configured	= rmi_input_configured,
#अगर_घोषित CONFIG_PM
	.suspend		= rmi_suspend,
	.resume			= rmi_post_resume,
	.reset_resume		= rmi_post_resume,
#पूर्ण_अगर
पूर्ण;

module_hid_driver(rmi_driver);

MODULE_AUTHOR("Andrew Duggan <aduggan@synaptics.com>");
MODULE_DESCRIPTION("RMI HID driver");
MODULE_LICENSE("GPL");
