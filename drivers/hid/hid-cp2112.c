<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * hid-cp2112.c - Silicon Lअसल HID USB to SMBus master bridge
 * Copyright (c) 2013,2014 Uplogix, Inc.
 * David Barksdale <dbarksdale@uplogix.com>
 */

/*
 * The Silicon Lअसल CP2112 chip is a USB HID device which provides an
 * SMBus controller क्रम talking to slave devices and 8 GPIO pins. The
 * host communicates with the CP2112 via raw HID reports.
 *
 * Data Sheet:
 *   https://www.siद_असल.com/Support%20Documents/TechnicalDocs/CP2112.pdf
 * Programming Interface Specअगरication:
 *   https://www.siद_असल.com/करोcuments/खुला/application-notes/an495-cp2112-पूर्णांकerface-specअगरication.pdf
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/hid.h>
#समावेश <linux/hidraw.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/nls.h>
#समावेश <linux/usb/ch9.h>
#समावेश "hid-ids.h"

#घोषणा CP2112_REPORT_MAX_LENGTH		64
#घोषणा CP2112_GPIO_CONFIG_LENGTH		5
#घोषणा CP2112_GPIO_GET_LENGTH			2
#घोषणा CP2112_GPIO_SET_LENGTH			3

क्रमागत अणु
	CP2112_GPIO_CONFIG		= 0x02,
	CP2112_GPIO_GET			= 0x03,
	CP2112_GPIO_SET			= 0x04,
	CP2112_GET_VERSION_INFO		= 0x05,
	CP2112_SMBUS_CONFIG		= 0x06,
	CP2112_DATA_READ_REQUEST	= 0x10,
	CP2112_DATA_WRITE_READ_REQUEST	= 0x11,
	CP2112_DATA_READ_FORCE_SEND	= 0x12,
	CP2112_DATA_READ_RESPONSE	= 0x13,
	CP2112_DATA_WRITE_REQUEST	= 0x14,
	CP2112_TRANSFER_STATUS_REQUEST	= 0x15,
	CP2112_TRANSFER_STATUS_RESPONSE	= 0x16,
	CP2112_CANCEL_TRANSFER		= 0x17,
	CP2112_LOCK_BYTE		= 0x20,
	CP2112_USB_CONFIG		= 0x21,
	CP2112_MANUFACTURER_STRING	= 0x22,
	CP2112_PRODUCT_STRING		= 0x23,
	CP2112_SERIAL_STRING		= 0x24,
पूर्ण;

क्रमागत अणु
	STATUS0_IDLE		= 0x00,
	STATUS0_BUSY		= 0x01,
	STATUS0_COMPLETE	= 0x02,
	STATUS0_ERROR		= 0x03,
पूर्ण;

क्रमागत अणु
	STATUS1_TIMEOUT_NACK		= 0x00,
	STATUS1_TIMEOUT_BUS		= 0x01,
	STATUS1_ARBITRATION_LOST	= 0x02,
	STATUS1_READ_INCOMPLETE		= 0x03,
	STATUS1_WRITE_INCOMPLETE	= 0x04,
	STATUS1_SUCCESS			= 0x05,
पूर्ण;

काष्ठा cp2112_smbus_config_report अणु
	u8 report;		/* CP2112_SMBUS_CONFIG */
	__be32 घड़ी_speed;	/* Hz */
	u8 device_address;	/* Stored in the upper 7 bits */
	u8 स्वतः_send_पढ़ो;	/* 1 = enabled, 0 = disabled */
	__be16 ग_लिखो_समयout;	/* ms, 0 = no समयout */
	__be16 पढ़ो_समयout;	/* ms, 0 = no समयout */
	u8 scl_low_समयout;	/* 1 = enabled, 0 = disabled */
	__be16 retry_समय;	/* # of retries, 0 = no limit */
पूर्ण __packed;

काष्ठा cp2112_usb_config_report अणु
	u8 report;	/* CP2112_USB_CONFIG */
	__le16 vid;	/* Venकरोr ID */
	__le16 pid;	/* Product ID */
	u8 max_घातer;	/* Power requested in 2mA units */
	u8 घातer_mode;	/* 0x00 = bus घातered
			   0x01 = self घातered & regulator off
			   0x02 = self घातered & regulator on */
	u8 release_major;
	u8 release_minor;
	u8 mask;	/* What fields to program */
पूर्ण __packed;

काष्ठा cp2112_पढ़ो_req_report अणु
	u8 report;	/* CP2112_DATA_READ_REQUEST */
	u8 slave_address;
	__be16 length;
पूर्ण __packed;

काष्ठा cp2112_ग_लिखो_पढ़ो_req_report अणु
	u8 report;	/* CP2112_DATA_WRITE_READ_REQUEST */
	u8 slave_address;
	__be16 length;
	u8 target_address_length;
	u8 target_address[16];
पूर्ण __packed;

काष्ठा cp2112_ग_लिखो_req_report अणु
	u8 report;	/* CP2112_DATA_WRITE_REQUEST */
	u8 slave_address;
	u8 length;
	u8 data[61];
पूर्ण __packed;

काष्ठा cp2112_क्रमce_पढ़ो_report अणु
	u8 report;	/* CP2112_DATA_READ_FORCE_SEND */
	__be16 length;
पूर्ण __packed;

काष्ठा cp2112_xfer_status_report अणु
	u8 report;	/* CP2112_TRANSFER_STATUS_RESPONSE */
	u8 status0;	/* STATUS0_* */
	u8 status1;	/* STATUS1_* */
	__be16 retries;
	__be16 length;
पूर्ण __packed;

काष्ठा cp2112_string_report अणु
	u8 dummy;		/* क्रमce .string to be aligned */
	u8 report;		/* CP2112_*_STRING */
	u8 length;		/* length in bytes of everyting after .report */
	u8 type;		/* USB_DT_STRING */
	ब_अक्षर_प्रकार string[30];	/* UTF16_LITTLE_ENDIAN string */
पूर्ण __packed;

/* Number of बार to request transfer status beक्रमe giving up रुकोing क्रम a
   transfer to complete. This may need to be changed अगर SMBUS घड़ी, retries,
   or पढ़ो/ग_लिखो/scl_low समयout settings are changed. */
अटल स्थिर पूर्णांक XFER_STATUS_RETRIES = 10;

/* Time in ms to रुको क्रम a CP2112_DATA_READ_RESPONSE or
   CP2112_TRANSFER_STATUS_RESPONSE. */
अटल स्थिर पूर्णांक RESPONSE_TIMEOUT = 50;

अटल स्थिर काष्ठा hid_device_id cp2112_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CYGNAL, USB_DEVICE_ID_CYGNAL_CP2112) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, cp2112_devices);

काष्ठा cp2112_device अणु
	काष्ठा i2c_adapter adap;
	काष्ठा hid_device *hdev;
	रुको_queue_head_t रुको;
	u8 पढ़ो_data[61];
	u8 पढ़ो_length;
	u8 hwversion;
	पूर्णांक xfer_status;
	atomic_t पढ़ो_avail;
	atomic_t xfer_avail;
	काष्ठा gpio_chip gc;
	काष्ठा irq_chip irq;
	u8 *in_out_buffer;
	काष्ठा mutex lock;

	काष्ठा gpio_desc *desc[8];
	bool gpio_poll;
	काष्ठा delayed_work gpio_poll_worker;
	अचिन्हित दीर्घ irq_mask;
	u8 gpio_prev_state;
पूर्ण;

अटल पूर्णांक gpio_push_pull = 0xFF;
module_param(gpio_push_pull, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(gpio_push_pull, "GPIO push-pull configuration bitmask");

अटल पूर्णांक cp2112_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा cp2112_device *dev = gpiochip_get_data(chip);
	काष्ठा hid_device *hdev = dev->hdev;
	u8 *buf = dev->in_out_buffer;
	पूर्णांक ret;

	mutex_lock(&dev->lock);

	ret = hid_hw_raw_request(hdev, CP2112_GPIO_CONFIG, buf,
				 CP2112_GPIO_CONFIG_LENGTH, HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);
	अगर (ret != CP2112_GPIO_CONFIG_LENGTH) अणु
		hid_err(hdev, "error requesting GPIO config: %d\n", ret);
		अगर (ret >= 0)
			ret = -EIO;
		जाओ निकास;
	पूर्ण

	buf[1] &= ~(1 << offset);
	buf[2] = gpio_push_pull;

	ret = hid_hw_raw_request(hdev, CP2112_GPIO_CONFIG, buf,
				 CP2112_GPIO_CONFIG_LENGTH, HID_FEATURE_REPORT,
				 HID_REQ_SET_REPORT);
	अगर (ret != CP2112_GPIO_CONFIG_LENGTH) अणु
		hid_err(hdev, "error setting GPIO config: %d\n", ret);
		अगर (ret >= 0)
			ret = -EIO;
		जाओ निकास;
	पूर्ण

	ret = 0;

निकास:
	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण

अटल व्योम cp2112_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा cp2112_device *dev = gpiochip_get_data(chip);
	काष्ठा hid_device *hdev = dev->hdev;
	u8 *buf = dev->in_out_buffer;
	पूर्णांक ret;

	mutex_lock(&dev->lock);

	buf[0] = CP2112_GPIO_SET;
	buf[1] = value ? 0xff : 0;
	buf[2] = 1 << offset;

	ret = hid_hw_raw_request(hdev, CP2112_GPIO_SET, buf,
				 CP2112_GPIO_SET_LENGTH, HID_FEATURE_REPORT,
				 HID_REQ_SET_REPORT);
	अगर (ret < 0)
		hid_err(hdev, "error setting GPIO values: %d\n", ret);

	mutex_unlock(&dev->lock);
पूर्ण

अटल पूर्णांक cp2112_gpio_get_all(काष्ठा gpio_chip *chip)
अणु
	काष्ठा cp2112_device *dev = gpiochip_get_data(chip);
	काष्ठा hid_device *hdev = dev->hdev;
	u8 *buf = dev->in_out_buffer;
	पूर्णांक ret;

	mutex_lock(&dev->lock);

	ret = hid_hw_raw_request(hdev, CP2112_GPIO_GET, buf,
				 CP2112_GPIO_GET_LENGTH, HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);
	अगर (ret != CP2112_GPIO_GET_LENGTH) अणु
		hid_err(hdev, "error requesting GPIO values: %d\n", ret);
		ret = ret < 0 ? ret : -EIO;
		जाओ निकास;
	पूर्ण

	ret = buf[1];

निकास:
	mutex_unlock(&dev->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cp2112_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;

	ret = cp2112_gpio_get_all(chip);
	अगर (ret < 0)
		वापस ret;

	वापस (ret >> offset) & 1;
पूर्ण

अटल पूर्णांक cp2112_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा cp2112_device *dev = gpiochip_get_data(chip);
	काष्ठा hid_device *hdev = dev->hdev;
	u8 *buf = dev->in_out_buffer;
	पूर्णांक ret;

	mutex_lock(&dev->lock);

	ret = hid_hw_raw_request(hdev, CP2112_GPIO_CONFIG, buf,
				 CP2112_GPIO_CONFIG_LENGTH, HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);
	अगर (ret != CP2112_GPIO_CONFIG_LENGTH) अणु
		hid_err(hdev, "error requesting GPIO config: %d\n", ret);
		जाओ fail;
	पूर्ण

	buf[1] |= 1 << offset;
	buf[2] = gpio_push_pull;

	ret = hid_hw_raw_request(hdev, CP2112_GPIO_CONFIG, buf,
				 CP2112_GPIO_CONFIG_LENGTH, HID_FEATURE_REPORT,
				 HID_REQ_SET_REPORT);
	अगर (ret < 0) अणु
		hid_err(hdev, "error setting GPIO config: %d\n", ret);
		जाओ fail;
	पूर्ण

	mutex_unlock(&dev->lock);

	/*
	 * Set gpio value when output direction is alपढ़ोy set,
	 * as specअगरied in AN495, Rev. 0.2, cpt. 4.4
	 */
	cp2112_gpio_set(chip, offset, value);

	वापस 0;

fail:
	mutex_unlock(&dev->lock);
	वापस ret < 0 ? ret : -EIO;
पूर्ण

अटल पूर्णांक cp2112_hid_get(काष्ठा hid_device *hdev, अचिन्हित अक्षर report_number,
			  u8 *data, माप_प्रकार count, अचिन्हित अक्षर report_type)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = hid_hw_raw_request(hdev, report_number, buf, count,
				       report_type, HID_REQ_GET_REPORT);
	स_नकल(data, buf, count);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक cp2112_hid_output(काष्ठा hid_device *hdev, u8 *data, माप_प्रकार count,
			     अचिन्हित अक्षर report_type)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kmemdup(data, count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (report_type == HID_OUTPUT_REPORT)
		ret = hid_hw_output_report(hdev, buf, count);
	अन्यथा
		ret = hid_hw_raw_request(hdev, buf[0], buf, count, report_type,
				HID_REQ_SET_REPORT);

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक cp2112_रुको(काष्ठा cp2112_device *dev, atomic_t *avail)
अणु
	पूर्णांक ret = 0;

	/* We have sent either a CP2112_TRANSFER_STATUS_REQUEST or a
	 * CP2112_DATA_READ_FORCE_SEND and we are रुकोing क्रम the response to
	 * come in cp2112_raw_event or समयout. There will only be one of these
	 * in flight at any one समय. The समयout is extremely large and is a
	 * last resort अगर the CP2112 has died. If we करो समयout we करोn't expect
	 * to receive the response which would cause data races, it's not like
	 * we can करो anything about it anyway.
	 */
	ret = रुको_event_पूर्णांकerruptible_समयout(dev->रुको,
		atomic_पढ़ो(avail), msecs_to_jअगरfies(RESPONSE_TIMEOUT));
	अगर (-ERESTARTSYS == ret)
		वापस ret;
	अगर (!ret)
		वापस -ETIMEDOUT;

	atomic_set(avail, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक cp2112_xfer_status(काष्ठा cp2112_device *dev)
अणु
	काष्ठा hid_device *hdev = dev->hdev;
	u8 buf[2];
	पूर्णांक ret;

	buf[0] = CP2112_TRANSFER_STATUS_REQUEST;
	buf[1] = 0x01;
	atomic_set(&dev->xfer_avail, 0);

	ret = cp2112_hid_output(hdev, buf, 2, HID_OUTPUT_REPORT);
	अगर (ret < 0) अणु
		hid_warn(hdev, "Error requesting status: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = cp2112_रुको(dev, &dev->xfer_avail);
	अगर (ret)
		वापस ret;

	वापस dev->xfer_status;
पूर्ण

अटल पूर्णांक cp2112_पढ़ो(काष्ठा cp2112_device *dev, u8 *data, माप_प्रकार size)
अणु
	काष्ठा hid_device *hdev = dev->hdev;
	काष्ठा cp2112_क्रमce_पढ़ो_report report;
	पूर्णांक ret;

	अगर (size > माप(dev->पढ़ो_data))
		size = माप(dev->पढ़ो_data);
	report.report = CP2112_DATA_READ_FORCE_SEND;
	report.length = cpu_to_be16(size);

	atomic_set(&dev->पढ़ो_avail, 0);

	ret = cp2112_hid_output(hdev, &report.report, माप(report),
				HID_OUTPUT_REPORT);
	अगर (ret < 0) अणु
		hid_warn(hdev, "Error requesting data: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = cp2112_रुको(dev, &dev->पढ़ो_avail);
	अगर (ret)
		वापस ret;

	hid_dbg(hdev, "read %d of %zd bytes requested\n",
		dev->पढ़ो_length, size);

	अगर (size > dev->पढ़ो_length)
		size = dev->पढ़ो_length;

	स_नकल(data, dev->पढ़ो_data, size);
	वापस dev->पढ़ो_length;
पूर्ण

अटल पूर्णांक cp2112_पढ़ो_req(व्योम *buf, u8 slave_address, u16 length)
अणु
	काष्ठा cp2112_पढ़ो_req_report *report = buf;

	अगर (length < 1 || length > 512)
		वापस -EINVAL;

	report->report = CP2112_DATA_READ_REQUEST;
	report->slave_address = slave_address << 1;
	report->length = cpu_to_be16(length);
	वापस माप(*report);
पूर्ण

अटल पूर्णांक cp2112_ग_लिखो_पढ़ो_req(व्योम *buf, u8 slave_address, u16 length,
				 u8 command, u8 *data, u8 data_length)
अणु
	काष्ठा cp2112_ग_लिखो_पढ़ो_req_report *report = buf;

	अगर (length < 1 || length > 512
	    || data_length > माप(report->target_address) - 1)
		वापस -EINVAL;

	report->report = CP2112_DATA_WRITE_READ_REQUEST;
	report->slave_address = slave_address << 1;
	report->length = cpu_to_be16(length);
	report->target_address_length = data_length + 1;
	report->target_address[0] = command;
	स_नकल(&report->target_address[1], data, data_length);
	वापस data_length + 6;
पूर्ण

अटल पूर्णांक cp2112_ग_लिखो_req(व्योम *buf, u8 slave_address, u8 command, u8 *data,
			    u8 data_length)
अणु
	काष्ठा cp2112_ग_लिखो_req_report *report = buf;

	अगर (data_length > माप(report->data) - 1)
		वापस -EINVAL;

	report->report = CP2112_DATA_WRITE_REQUEST;
	report->slave_address = slave_address << 1;
	report->length = data_length + 1;
	report->data[0] = command;
	स_नकल(&report->data[1], data, data_length);
	वापस data_length + 4;
पूर्ण

अटल पूर्णांक cp2112_i2c_ग_लिखो_req(व्योम *buf, u8 slave_address, u8 *data,
				u8 data_length)
अणु
	काष्ठा cp2112_ग_लिखो_req_report *report = buf;

	अगर (data_length > माप(report->data))
		वापस -EINVAL;

	report->report = CP2112_DATA_WRITE_REQUEST;
	report->slave_address = slave_address << 1;
	report->length = data_length;
	स_नकल(report->data, data, data_length);
	वापस data_length + 3;
पूर्ण

अटल पूर्णांक cp2112_i2c_ग_लिखो_पढ़ो_req(व्योम *buf, u8 slave_address,
				     u8 *addr, पूर्णांक addr_length,
				     पूर्णांक पढ़ो_length)
अणु
	काष्ठा cp2112_ग_लिखो_पढ़ो_req_report *report = buf;

	अगर (पढ़ो_length < 1 || पढ़ो_length > 512 ||
	    addr_length > माप(report->target_address))
		वापस -EINVAL;

	report->report = CP2112_DATA_WRITE_READ_REQUEST;
	report->slave_address = slave_address << 1;
	report->length = cpu_to_be16(पढ़ो_length);
	report->target_address_length = addr_length;
	स_नकल(report->target_address, addr, addr_length);
	वापस addr_length + 5;
पूर्ण

अटल पूर्णांक cp2112_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			   पूर्णांक num)
अणु
	काष्ठा cp2112_device *dev = (काष्ठा cp2112_device *)adap->algo_data;
	काष्ठा hid_device *hdev = dev->hdev;
	u8 buf[64];
	sमाप_प्रकार count;
	sमाप_प्रकार पढ़ो_length = 0;
	u8 *पढ़ो_buf = शून्य;
	अचिन्हित पूर्णांक retries;
	पूर्णांक ret;

	hid_dbg(hdev, "I2C %d messages\n", num);

	अगर (num == 1) अणु
		अगर (msgs->flags & I2C_M_RD) अणु
			hid_dbg(hdev, "I2C read %#04x len %d\n",
				msgs->addr, msgs->len);
			पढ़ो_length = msgs->len;
			पढ़ो_buf = msgs->buf;
			count = cp2112_पढ़ो_req(buf, msgs->addr, msgs->len);
		पूर्ण अन्यथा अणु
			hid_dbg(hdev, "I2C write %#04x len %d\n",
				msgs->addr, msgs->len);
			count = cp2112_i2c_ग_लिखो_req(buf, msgs->addr,
						     msgs->buf, msgs->len);
		पूर्ण
		अगर (count < 0)
			वापस count;
	पूर्ण अन्यथा अगर (dev->hwversion > 1 &&  /* no repeated start in rev 1 */
		   num == 2 &&
		   msgs[0].addr == msgs[1].addr &&
		   !(msgs[0].flags & I2C_M_RD) && (msgs[1].flags & I2C_M_RD)) अणु
		hid_dbg(hdev, "I2C write-read %#04x wlen %d rlen %d\n",
			msgs[0].addr, msgs[0].len, msgs[1].len);
		पढ़ो_length = msgs[1].len;
		पढ़ो_buf = msgs[1].buf;
		count = cp2112_i2c_ग_लिखो_पढ़ो_req(buf, msgs[0].addr,
				msgs[0].buf, msgs[0].len, msgs[1].len);
		अगर (count < 0)
			वापस count;
	पूर्ण अन्यथा अणु
		hid_err(hdev,
			"Multi-message I2C transactions not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = hid_hw_घातer(hdev, PM_HINT_FULLON);
	अगर (ret < 0) अणु
		hid_err(hdev, "power management error: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = cp2112_hid_output(hdev, buf, count, HID_OUTPUT_REPORT);
	अगर (ret < 0) अणु
		hid_warn(hdev, "Error starting transaction: %d\n", ret);
		जाओ घातer_normal;
	पूर्ण

	क्रम (retries = 0; retries < XFER_STATUS_RETRIES; ++retries) अणु
		ret = cp2112_xfer_status(dev);
		अगर (-EBUSY == ret)
			जारी;
		अगर (ret < 0)
			जाओ घातer_normal;
		अवरोध;
	पूर्ण

	अगर (XFER_STATUS_RETRIES <= retries) अणु
		hid_warn(hdev, "Transfer timed out, cancelling.\n");
		buf[0] = CP2112_CANCEL_TRANSFER;
		buf[1] = 0x01;

		ret = cp2112_hid_output(hdev, buf, 2, HID_OUTPUT_REPORT);
		अगर (ret < 0)
			hid_warn(hdev, "Error cancelling transaction: %d\n",
				 ret);

		ret = -ETIMEDOUT;
		जाओ घातer_normal;
	पूर्ण

	क्रम (count = 0; count < पढ़ो_length;) अणु
		ret = cp2112_पढ़ो(dev, पढ़ो_buf + count, पढ़ो_length - count);
		अगर (ret < 0)
			जाओ घातer_normal;
		अगर (ret == 0) अणु
			hid_err(hdev, "read returned 0\n");
			ret = -EIO;
			जाओ घातer_normal;
		पूर्ण
		count += ret;
		अगर (count > पढ़ो_length) अणु
			/*
			 * The hardware वापसed too much data.
			 * This is mostly harmless because cp2112_पढ़ो()
			 * has a limit check so didn't overrun our
			 * buffer.  Nevertheless, we वापस an error
			 * because something is seriously wrong and
			 * it shouldn't go unnoticed.
			 */
			hid_err(hdev, "long read: %d > %zd\n",
				ret, पढ़ो_length - count + ret);
			ret = -EIO;
			जाओ घातer_normal;
		पूर्ण
	पूर्ण

	/* वापस the number of transferred messages */
	ret = num;

घातer_normal:
	hid_hw_घातer(hdev, PM_HINT_NORMAL);
	hid_dbg(hdev, "I2C transfer finished: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक cp2112_xfer(काष्ठा i2c_adapter *adap, u16 addr,
		       अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो, u8 command,
		       पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	काष्ठा cp2112_device *dev = (काष्ठा cp2112_device *)adap->algo_data;
	काष्ठा hid_device *hdev = dev->hdev;
	u8 buf[64];
	__le16 word;
	sमाप_प्रकार count;
	माप_प्रकार पढ़ो_length = 0;
	अचिन्हित पूर्णांक retries;
	पूर्णांक ret;

	hid_dbg(hdev, "%s addr 0x%x flags 0x%x cmd 0x%x size %d\n",
		पढ़ो_ग_लिखो == I2C_SMBUS_WRITE ? "write" : "read",
		addr, flags, command, size);

	चयन (size) अणु
	हाल I2C_SMBUS_BYTE:
		पढ़ो_length = 1;

		अगर (I2C_SMBUS_READ == पढ़ो_ग_लिखो)
			count = cp2112_पढ़ो_req(buf, addr, पढ़ो_length);
		अन्यथा
			count = cp2112_ग_लिखो_req(buf, addr, command, शून्य,
						 0);
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		पढ़ो_length = 1;

		अगर (I2C_SMBUS_READ == पढ़ो_ग_लिखो)
			count = cp2112_ग_लिखो_पढ़ो_req(buf, addr, पढ़ो_length,
						      command, शून्य, 0);
		अन्यथा
			count = cp2112_ग_लिखो_req(buf, addr, command,
						 &data->byte, 1);
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		पढ़ो_length = 2;
		word = cpu_to_le16(data->word);

		अगर (I2C_SMBUS_READ == पढ़ो_ग_लिखो)
			count = cp2112_ग_लिखो_पढ़ो_req(buf, addr, पढ़ो_length,
						      command, शून्य, 0);
		अन्यथा
			count = cp2112_ग_लिखो_req(buf, addr, command,
						 (u8 *)&word, 2);
		अवरोध;
	हाल I2C_SMBUS_PROC_CALL:
		size = I2C_SMBUS_WORD_DATA;
		पढ़ो_ग_लिखो = I2C_SMBUS_READ;
		पढ़ो_length = 2;
		word = cpu_to_le16(data->word);

		count = cp2112_ग_लिखो_पढ़ो_req(buf, addr, पढ़ो_length, command,
					      (u8 *)&word, 2);
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			पढ़ो_length = data->block[0];
			count = cp2112_ग_लिखो_पढ़ो_req(buf, addr, पढ़ो_length,
						      command, शून्य, 0);
		पूर्ण अन्यथा अणु
			count = cp2112_ग_लिखो_req(buf, addr, command,
						 data->block + 1,
						 data->block[0]);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		अगर (I2C_SMBUS_READ == पढ़ो_ग_लिखो) अणु
			count = cp2112_ग_लिखो_पढ़ो_req(buf, addr,
						      I2C_SMBUS_BLOCK_MAX,
						      command, शून्य, 0);
		पूर्ण अन्यथा अणु
			count = cp2112_ग_लिखो_req(buf, addr, command,
						 data->block,
						 data->block[0] + 1);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		size = I2C_SMBUS_BLOCK_DATA;
		पढ़ो_ग_लिखो = I2C_SMBUS_READ;

		count = cp2112_ग_लिखो_पढ़ो_req(buf, addr, I2C_SMBUS_BLOCK_MAX,
					      command, data->block,
					      data->block[0] + 1);
		अवरोध;
	शेष:
		hid_warn(hdev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (count < 0)
		वापस count;

	ret = hid_hw_घातer(hdev, PM_HINT_FULLON);
	अगर (ret < 0) अणु
		hid_err(hdev, "power management error: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = cp2112_hid_output(hdev, buf, count, HID_OUTPUT_REPORT);
	अगर (ret < 0) अणु
		hid_warn(hdev, "Error starting transaction: %d\n", ret);
		जाओ घातer_normal;
	पूर्ण

	क्रम (retries = 0; retries < XFER_STATUS_RETRIES; ++retries) अणु
		ret = cp2112_xfer_status(dev);
		अगर (-EBUSY == ret)
			जारी;
		अगर (ret < 0)
			जाओ घातer_normal;
		अवरोध;
	पूर्ण

	अगर (XFER_STATUS_RETRIES <= retries) अणु
		hid_warn(hdev, "Transfer timed out, cancelling.\n");
		buf[0] = CP2112_CANCEL_TRANSFER;
		buf[1] = 0x01;

		ret = cp2112_hid_output(hdev, buf, 2, HID_OUTPUT_REPORT);
		अगर (ret < 0)
			hid_warn(hdev, "Error cancelling transaction: %d\n",
				 ret);

		ret = -ETIMEDOUT;
		जाओ घातer_normal;
	पूर्ण

	अगर (I2C_SMBUS_WRITE == पढ़ो_ग_लिखो) अणु
		ret = 0;
		जाओ घातer_normal;
	पूर्ण

	अगर (I2C_SMBUS_BLOCK_DATA == size)
		पढ़ो_length = ret;

	ret = cp2112_पढ़ो(dev, buf, पढ़ो_length);
	अगर (ret < 0)
		जाओ घातer_normal;
	अगर (ret != पढ़ो_length) अणु
		hid_warn(hdev, "short read: %d < %zd\n", ret, पढ़ो_length);
		ret = -EIO;
		जाओ घातer_normal;
	पूर्ण

	चयन (size) अणु
	हाल I2C_SMBUS_BYTE:
	हाल I2C_SMBUS_BYTE_DATA:
		data->byte = buf[0];
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		data->word = le16_to_cpup((__le16 *)buf);
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		स_नकल(data->block + 1, buf, पढ़ो_length);
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		अगर (पढ़ो_length > I2C_SMBUS_BLOCK_MAX) अणु
			ret = -EPROTO;
			जाओ घातer_normal;
		पूर्ण

		स_नकल(data->block, buf, पढ़ो_length);
		अवरोध;
	पूर्ण

	ret = 0;
घातer_normal:
	hid_hw_घातer(hdev, PM_HINT_NORMAL);
	hid_dbg(hdev, "transfer finished: %d\n", ret);
	वापस ret;
पूर्ण

अटल u32 cp2112_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C |
		I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WORD_DATA |
		I2C_FUNC_SMBUS_BLOCK_DATA |
		I2C_FUNC_SMBUS_I2C_BLOCK |
		I2C_FUNC_SMBUS_PROC_CALL |
		I2C_FUNC_SMBUS_BLOCK_PROC_CALL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.master_xfer	= cp2112_i2c_xfer,
	.smbus_xfer	= cp2112_xfer,
	.functionality	= cp2112_functionality,
पूर्ण;

अटल पूर्णांक cp2112_get_usb_config(काष्ठा hid_device *hdev,
				 काष्ठा cp2112_usb_config_report *cfg)
अणु
	पूर्णांक ret;

	ret = cp2112_hid_get(hdev, CP2112_USB_CONFIG, (u8 *)cfg, माप(*cfg),
			     HID_FEATURE_REPORT);
	अगर (ret != माप(*cfg)) अणु
		hid_err(hdev, "error reading usb config: %d\n", ret);
		अगर (ret < 0)
			वापस ret;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cp2112_set_usb_config(काष्ठा hid_device *hdev,
				 काष्ठा cp2112_usb_config_report *cfg)
अणु
	पूर्णांक ret;

	BUG_ON(cfg->report != CP2112_USB_CONFIG);

	ret = cp2112_hid_output(hdev, (u8 *)cfg, माप(*cfg),
				HID_FEATURE_REPORT);
	अगर (ret != माप(*cfg)) अणु
		hid_err(hdev, "error writing usb config: %d\n", ret);
		अगर (ret < 0)
			वापस ret;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम chmod_sysfs_attrs(काष्ठा hid_device *hdev);

#घोषणा CP2112_CONFIG_ATTR(name, store, क्रमmat, ...) \
अटल sमाप_प्रकार name##_store(काष्ठा device *kdev, \
			    काष्ठा device_attribute *attr, स्थिर अक्षर *buf, \
			    माप_प्रकार count) \
अणु \
	काष्ठा hid_device *hdev = to_hid_device(kdev); \
	काष्ठा cp2112_usb_config_report cfg; \
	पूर्णांक ret = cp2112_get_usb_config(hdev, &cfg); \
	अगर (ret) \
		वापस ret; \
	store; \
	ret = cp2112_set_usb_config(hdev, &cfg); \
	अगर (ret) \
		वापस ret; \
	chmod_sysfs_attrs(hdev); \
	वापस count; \
पूर्ण \
अटल sमाप_प्रकार name##_show(काष्ठा device *kdev, \
			   काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	काष्ठा hid_device *hdev = to_hid_device(kdev); \
	काष्ठा cp2112_usb_config_report cfg; \
	पूर्णांक ret = cp2112_get_usb_config(hdev, &cfg); \
	अगर (ret) \
		वापस ret; \
	वापस scnम_लिखो(buf, PAGE_SIZE, क्रमmat, ##__VA_ARGS__); \
पूर्ण \
अटल DEVICE_ATTR_RW(name);

CP2112_CONFIG_ATTR(venकरोr_id, (अणु
	u16 vid;

	अगर (माला_पूछो(buf, "%hi", &vid) != 1)
		वापस -EINVAL;

	cfg.vid = cpu_to_le16(vid);
	cfg.mask = 0x01;
पूर्ण), "0x%04x\n", le16_to_cpu(cfg.vid));

CP2112_CONFIG_ATTR(product_id, (अणु
	u16 pid;

	अगर (माला_पूछो(buf, "%hi", &pid) != 1)
		वापस -EINVAL;

	cfg.pid = cpu_to_le16(pid);
	cfg.mask = 0x02;
पूर्ण), "0x%04x\n", le16_to_cpu(cfg.pid));

CP2112_CONFIG_ATTR(max_घातer, (अणु
	पूर्णांक mA;

	अगर (माला_पूछो(buf, "%i", &mA) != 1)
		वापस -EINVAL;

	cfg.max_घातer = (mA + 1) / 2;
	cfg.mask = 0x04;
पूर्ण), "%u mA\n", cfg.max_घातer * 2);

CP2112_CONFIG_ATTR(घातer_mode, (अणु
	अगर (माला_पूछो(buf, "%hhi", &cfg.घातer_mode) != 1)
		वापस -EINVAL;

	cfg.mask = 0x08;
पूर्ण), "%u\n", cfg.घातer_mode);

CP2112_CONFIG_ATTR(release_version, (अणु
	अगर (माला_पूछो(buf, "%hhi.%hhi", &cfg.release_major, &cfg.release_minor)
	    != 2)
		वापस -EINVAL;

	cfg.mask = 0x10;
पूर्ण), "%u.%u\n", cfg.release_major, cfg.release_minor);

#अघोषित CP2112_CONFIG_ATTR

काष्ठा cp2112_pstring_attribute अणु
	काष्ठा device_attribute attr;
	अचिन्हित अक्षर report;
पूर्ण;

अटल sमाप_प्रकार pstr_store(काष्ठा device *kdev,
			  काष्ठा device_attribute *kattr, स्थिर अक्षर *buf,
			  माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(kdev);
	काष्ठा cp2112_pstring_attribute *attr =
		container_of(kattr, काष्ठा cp2112_pstring_attribute, attr);
	काष्ठा cp2112_string_report report;
	पूर्णांक ret;

	स_रखो(&report, 0, माप(report));

	ret = utf8s_to_utf16s(buf, count, UTF16_LITTLE_ENDIAN,
			      report.string, ARRAY_SIZE(report.string));
	report.report = attr->report;
	report.length = ret * माप(report.string[0]) + 2;
	report.type = USB_DT_STRING;

	ret = cp2112_hid_output(hdev, &report.report, report.length + 1,
				HID_FEATURE_REPORT);
	अगर (ret != report.length + 1) अणु
		hid_err(hdev, "error writing %s string: %d\n", kattr->attr.name,
			ret);
		अगर (ret < 0)
			वापस ret;
		वापस -EIO;
	पूर्ण

	chmod_sysfs_attrs(hdev);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pstr_show(काष्ठा device *kdev,
			 काष्ठा device_attribute *kattr, अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(kdev);
	काष्ठा cp2112_pstring_attribute *attr =
		container_of(kattr, काष्ठा cp2112_pstring_attribute, attr);
	काष्ठा cp2112_string_report report;
	u8 length;
	पूर्णांक ret;

	ret = cp2112_hid_get(hdev, attr->report, &report.report,
			     माप(report) - 1, HID_FEATURE_REPORT);
	अगर (ret < 3) अणु
		hid_err(hdev, "error reading %s string: %d\n", kattr->attr.name,
			ret);
		अगर (ret < 0)
			वापस ret;
		वापस -EIO;
	पूर्ण

	अगर (report.length < 2) अणु
		hid_err(hdev, "invalid %s string length: %d\n",
			kattr->attr.name, report.length);
		वापस -EIO;
	पूर्ण

	length = report.length > ret - 1 ? ret - 1 : report.length;
	length = (length - 2) / माप(report.string[0]);
	ret = utf16s_to_utf8s(report.string, length, UTF16_LITTLE_ENDIAN, buf,
			      PAGE_SIZE - 1);
	buf[ret++] = '\n';
	वापस ret;
पूर्ण

#घोषणा CP2112_PSTR_ATTR(name, _report) \
अटल काष्ठा cp2112_pstring_attribute dev_attr_##name = अणु \
	.attr = __ATTR(name, (S_IWUSR | S_IRUGO), pstr_show, pstr_store), \
	.report = _report, \
पूर्ण;

CP2112_PSTR_ATTR(manufacturer,	CP2112_MANUFACTURER_STRING);
CP2112_PSTR_ATTR(product,	CP2112_PRODUCT_STRING);
CP2112_PSTR_ATTR(serial,	CP2112_SERIAL_STRING);

#अघोषित CP2112_PSTR_ATTR

अटल स्थिर काष्ठा attribute_group cp2112_attr_group = अणु
	.attrs = (काष्ठा attribute *[])अणु
		&dev_attr_venकरोr_id.attr,
		&dev_attr_product_id.attr,
		&dev_attr_max_घातer.attr,
		&dev_attr_घातer_mode.attr,
		&dev_attr_release_version.attr,
		&dev_attr_manufacturer.attr.attr,
		&dev_attr_product.attr.attr,
		&dev_attr_serial.attr.attr,
		शून्य
	पूर्ण
पूर्ण;

/* Chmoding our sysfs attributes is simply a way to expose which fields in the
 * PROM have alपढ़ोy been programmed. We करो not depend on this preventing
 * writing to these attributes since the CP2112 will simply ignore ग_लिखोs to
 * alपढ़ोy-programmed fields. This is why there is no sense in fixing this
 * racy behaviour.
 */
अटल व्योम chmod_sysfs_attrs(काष्ठा hid_device *hdev)
अणु
	काष्ठा attribute **attr;
	u8 buf[2];
	पूर्णांक ret;

	ret = cp2112_hid_get(hdev, CP2112_LOCK_BYTE, buf, माप(buf),
			     HID_FEATURE_REPORT);
	अगर (ret != माप(buf)) अणु
		hid_err(hdev, "error reading lock byte: %d\n", ret);
		वापस;
	पूर्ण

	क्रम (attr = cp2112_attr_group.attrs; *attr; ++attr) अणु
		umode_t mode = (buf[1] & 1) ? S_IWUSR | S_IRUGO : S_IRUGO;
		ret = sysfs_chmod_file(&hdev->dev.kobj, *attr, mode);
		अगर (ret < 0)
			hid_err(hdev, "error chmoding sysfs file %s\n",
				(*attr)->name);
		buf[1] >>= 1;
	पूर्ण
पूर्ण

अटल व्योम cp2112_gpio_irq_ack(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम cp2112_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा cp2112_device *dev = gpiochip_get_data(gc);

	__clear_bit(d->hwirq, &dev->irq_mask);
पूर्ण

अटल व्योम cp2112_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा cp2112_device *dev = gpiochip_get_data(gc);

	__set_bit(d->hwirq, &dev->irq_mask);
पूर्ण

अटल व्योम cp2112_gpio_poll_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cp2112_device *dev = container_of(work, काष्ठा cp2112_device,
						 gpio_poll_worker.work);
	काष्ठा irq_data *d;
	u8 gpio_mask;
	u8 virqs = (u8)dev->irq_mask;
	u32 irq_type;
	पूर्णांक irq, virq, ret;

	ret = cp2112_gpio_get_all(&dev->gc);
	अगर (ret == -ENODEV) /* the hardware has been disconnected */
		वापस;
	अगर (ret < 0)
		जाओ निकास;

	gpio_mask = ret;

	जबतक (virqs) अणु
		virq = ffs(virqs) - 1;
		virqs &= ~BIT(virq);

		अगर (!dev->gc.to_irq)
			अवरोध;

		irq = dev->gc.to_irq(&dev->gc, virq);

		d = irq_get_irq_data(irq);
		अगर (!d)
			जारी;

		irq_type = irqd_get_trigger_type(d);

		अगर (gpio_mask & BIT(virq)) अणु
			/* Level High */

			अगर (irq_type & IRQ_TYPE_LEVEL_HIGH)
				handle_nested_irq(irq);

			अगर ((irq_type & IRQ_TYPE_EDGE_RISING) &&
			    !(dev->gpio_prev_state & BIT(virq)))
				handle_nested_irq(irq);
		पूर्ण अन्यथा अणु
			/* Level Low */

			अगर (irq_type & IRQ_TYPE_LEVEL_LOW)
				handle_nested_irq(irq);

			अगर ((irq_type & IRQ_TYPE_EDGE_FALLING) &&
			    (dev->gpio_prev_state & BIT(virq)))
				handle_nested_irq(irq);
		पूर्ण
	पूर्ण

	dev->gpio_prev_state = gpio_mask;

निकास:
	अगर (dev->gpio_poll)
		schedule_delayed_work(&dev->gpio_poll_worker, 10);
पूर्ण


अटल अचिन्हित पूर्णांक cp2112_gpio_irq_startup(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा cp2112_device *dev = gpiochip_get_data(gc);

	INIT_DELAYED_WORK(&dev->gpio_poll_worker, cp2112_gpio_poll_callback);

	अगर (!dev->gpio_poll) अणु
		dev->gpio_poll = true;
		schedule_delayed_work(&dev->gpio_poll_worker, 0);
	पूर्ण

	cp2112_gpio_irq_unmask(d);
	वापस 0;
पूर्ण

अटल व्योम cp2112_gpio_irq_shutकरोwn(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा cp2112_device *dev = gpiochip_get_data(gc);

	cancel_delayed_work_sync(&dev->gpio_poll_worker);
पूर्ण

अटल पूर्णांक cp2112_gpio_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cp2112_allocate_irq(काष्ठा cp2112_device *dev,
					      पूर्णांक pin)
अणु
	पूर्णांक ret;

	अगर (dev->desc[pin])
		वापस -EINVAL;

	dev->desc[pin] = gpiochip_request_own_desc(&dev->gc, pin,
						   "HID/I2C:Event",
						   GPIO_ACTIVE_HIGH,
						   GPIOD_IN);
	अगर (IS_ERR(dev->desc[pin])) अणु
		dev_err(dev->gc.parent, "Failed to request GPIO\n");
		वापस PTR_ERR(dev->desc[pin]);
	पूर्ण

	ret = cp2112_gpio_direction_input(&dev->gc, pin);
	अगर (ret < 0) अणु
		dev_err(dev->gc.parent, "Failed to set GPIO to input dir\n");
		जाओ err_desc;
	पूर्ण

	ret = gpiochip_lock_as_irq(&dev->gc, pin);
	अगर (ret) अणु
		dev_err(dev->gc.parent, "Failed to lock GPIO as interrupt\n");
		जाओ err_desc;
	पूर्ण

	ret = gpiod_to_irq(dev->desc[pin]);
	अगर (ret < 0) अणु
		dev_err(dev->gc.parent, "Failed to translate GPIO to IRQ\n");
		जाओ err_lock;
	पूर्ण

	वापस ret;

err_lock:
	gpiochip_unlock_as_irq(&dev->gc, pin);
err_desc:
	gpiochip_मुक्त_own_desc(dev->desc[pin]);
	dev->desc[pin] = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक cp2112_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा cp2112_device *dev;
	u8 buf[3];
	काष्ठा cp2112_smbus_config_report config;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक ret;

	dev = devm_kzalloc(&hdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->in_out_buffer = devm_kzalloc(&hdev->dev, CP2112_REPORT_MAX_LENGTH,
					  GFP_KERNEL);
	अगर (!dev->in_out_buffer)
		वापस -ENOMEM;

	mutex_init(&dev->lock);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_खोलो(hdev);
	अगर (ret) अणु
		hid_err(hdev, "hw open failed\n");
		जाओ err_hid_stop;
	पूर्ण

	ret = hid_hw_घातer(hdev, PM_HINT_FULLON);
	अगर (ret < 0) अणु
		hid_err(hdev, "power management error: %d\n", ret);
		जाओ err_hid_बंद;
	पूर्ण

	ret = cp2112_hid_get(hdev, CP2112_GET_VERSION_INFO, buf, माप(buf),
			     HID_FEATURE_REPORT);
	अगर (ret != माप(buf)) अणु
		hid_err(hdev, "error requesting version\n");
		अगर (ret >= 0)
			ret = -EIO;
		जाओ err_घातer_normal;
	पूर्ण

	hid_info(hdev, "Part Number: 0x%02X Device Version: 0x%02X\n",
		 buf[1], buf[2]);

	ret = cp2112_hid_get(hdev, CP2112_SMBUS_CONFIG, (u8 *)&config,
			     माप(config), HID_FEATURE_REPORT);
	अगर (ret != माप(config)) अणु
		hid_err(hdev, "error requesting SMBus config\n");
		अगर (ret >= 0)
			ret = -EIO;
		जाओ err_घातer_normal;
	पूर्ण

	config.retry_समय = cpu_to_be16(1);

	ret = cp2112_hid_output(hdev, (u8 *)&config, माप(config),
				HID_FEATURE_REPORT);
	अगर (ret != माप(config)) अणु
		hid_err(hdev, "error setting SMBus config\n");
		अगर (ret >= 0)
			ret = -EIO;
		जाओ err_घातer_normal;
	पूर्ण

	hid_set_drvdata(hdev, (व्योम *)dev);
	dev->hdev		= hdev;
	dev->adap.owner		= THIS_MODULE;
	dev->adap.class		= I2C_CLASS_HWMON;
	dev->adap.algo		= &smbus_algorithm;
	dev->adap.algo_data	= dev;
	dev->adap.dev.parent	= &hdev->dev;
	snम_लिखो(dev->adap.name, माप(dev->adap.name),
		 "CP2112 SMBus Bridge on hidraw%d",
		 ((काष्ठा hidraw *)hdev->hidraw)->minor);
	dev->hwversion = buf[2];
	init_रुकोqueue_head(&dev->रुको);

	hid_device_io_start(hdev);
	ret = i2c_add_adapter(&dev->adap);
	hid_device_io_stop(hdev);

	अगर (ret) अणु
		hid_err(hdev, "error registering i2c adapter\n");
		जाओ err_घातer_normal;
	पूर्ण

	hid_dbg(hdev, "adapter registered\n");

	dev->gc.label			= "cp2112_gpio";
	dev->gc.direction_input		= cp2112_gpio_direction_input;
	dev->gc.direction_output	= cp2112_gpio_direction_output;
	dev->gc.set			= cp2112_gpio_set;
	dev->gc.get			= cp2112_gpio_get;
	dev->gc.base			= -1;
	dev->gc.ngpio			= 8;
	dev->gc.can_sleep		= 1;
	dev->gc.parent			= &hdev->dev;

	dev->irq.name = "cp2112-gpio";
	dev->irq.irq_startup = cp2112_gpio_irq_startup;
	dev->irq.irq_shutकरोwn = cp2112_gpio_irq_shutकरोwn;
	dev->irq.irq_ack = cp2112_gpio_irq_ack;
	dev->irq.irq_mask = cp2112_gpio_irq_mask;
	dev->irq.irq_unmask = cp2112_gpio_irq_unmask;
	dev->irq.irq_set_type = cp2112_gpio_irq_type;
	dev->irq.flags = IRQCHIP_MASK_ON_SUSPEND;

	girq = &dev->gc.irq;
	girq->chip = &dev->irq;
	/* The event comes from the outside so no parent handler */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_simple_irq;

	ret = gpiochip_add_data(&dev->gc, dev);
	अगर (ret < 0) अणु
		hid_err(hdev, "error registering gpio chip\n");
		जाओ err_मुक्त_i2c;
	पूर्ण

	ret = sysfs_create_group(&hdev->dev.kobj, &cp2112_attr_group);
	अगर (ret < 0) अणु
		hid_err(hdev, "error creating sysfs attrs\n");
		जाओ err_gpiochip_हटाओ;
	पूर्ण

	chmod_sysfs_attrs(hdev);
	hid_hw_घातer(hdev, PM_HINT_NORMAL);

	वापस ret;

err_gpiochip_हटाओ:
	gpiochip_हटाओ(&dev->gc);
err_मुक्त_i2c:
	i2c_del_adapter(&dev->adap);
err_घातer_normal:
	hid_hw_घातer(hdev, PM_HINT_NORMAL);
err_hid_बंद:
	hid_hw_बंद(hdev);
err_hid_stop:
	hid_hw_stop(hdev);
	वापस ret;
पूर्ण

अटल व्योम cp2112_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा cp2112_device *dev = hid_get_drvdata(hdev);
	पूर्णांक i;

	sysfs_हटाओ_group(&hdev->dev.kobj, &cp2112_attr_group);
	i2c_del_adapter(&dev->adap);

	अगर (dev->gpio_poll) अणु
		dev->gpio_poll = false;
		cancel_delayed_work_sync(&dev->gpio_poll_worker);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(dev->desc); i++) अणु
		gpiochip_unlock_as_irq(&dev->gc, i);
		gpiochip_मुक्त_own_desc(dev->desc[i]);
	पूर्ण

	gpiochip_हटाओ(&dev->gc);
	/* i2c_del_adapter has finished removing all i2c devices from our
	 * adapter. Well behaved devices should no दीर्घer call our cp2112_xfer
	 * and should have रुकोed क्रम any pending calls to finish. It has also
	 * रुकोed क्रम device_unरेजिस्टर(&adap->dev) to complete. Thereक्रमe we
	 * can safely मुक्त our काष्ठा cp2112_device.
	 */
	hid_hw_बंद(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल पूर्णांक cp2112_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
			    u8 *data, पूर्णांक size)
अणु
	काष्ठा cp2112_device *dev = hid_get_drvdata(hdev);
	काष्ठा cp2112_xfer_status_report *xfer = (व्योम *)data;

	चयन (data[0]) अणु
	हाल CP2112_TRANSFER_STATUS_RESPONSE:
		hid_dbg(hdev, "xfer status: %02x %02x %04x %04x\n",
			xfer->status0, xfer->status1,
			be16_to_cpu(xfer->retries), be16_to_cpu(xfer->length));

		चयन (xfer->status0) अणु
		हाल STATUS0_IDLE:
			dev->xfer_status = -EAGAIN;
			अवरोध;
		हाल STATUS0_BUSY:
			dev->xfer_status = -EBUSY;
			अवरोध;
		हाल STATUS0_COMPLETE:
			dev->xfer_status = be16_to_cpu(xfer->length);
			अवरोध;
		हाल STATUS0_ERROR:
			चयन (xfer->status1) अणु
			हाल STATUS1_TIMEOUT_NACK:
			हाल STATUS1_TIMEOUT_BUS:
				dev->xfer_status = -ETIMEDOUT;
				अवरोध;
			शेष:
				dev->xfer_status = -EIO;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			dev->xfer_status = -EINVAL;
			अवरोध;
		पूर्ण

		atomic_set(&dev->xfer_avail, 1);
		अवरोध;
	हाल CP2112_DATA_READ_RESPONSE:
		hid_dbg(hdev, "read response: %02x %02x\n", data[1], data[2]);

		dev->पढ़ो_length = data[2];
		अगर (dev->पढ़ो_length > माप(dev->पढ़ो_data))
			dev->पढ़ो_length = माप(dev->पढ़ो_data);

		स_नकल(dev->पढ़ो_data, &data[3], dev->पढ़ो_length);
		atomic_set(&dev->पढ़ो_avail, 1);
		अवरोध;
	शेष:
		hid_err(hdev, "unknown report\n");

		वापस 0;
	पूर्ण

	wake_up_पूर्णांकerruptible(&dev->रुको);
	वापस 1;
पूर्ण

अटल काष्ठा hid_driver cp2112_driver = अणु
	.name		= "cp2112",
	.id_table	= cp2112_devices,
	.probe		= cp2112_probe,
	.हटाओ		= cp2112_हटाओ,
	.raw_event	= cp2112_raw_event,
पूर्ण;

module_hid_driver(cp2112_driver);
MODULE_DESCRIPTION("Silicon Labs HID USB to SMBus master bridge");
MODULE_AUTHOR("David Barksdale <dbarksdale@uplogix.com>");
MODULE_LICENSE("GPL");

