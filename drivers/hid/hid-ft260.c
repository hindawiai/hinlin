<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * hid-ft260.c - FTDI FT260 USB HID to I2C host bridge
 *
 * Copyright (c) 2021, Michael Zaidman <michaelz@xsightद_असल.com>
 *
 * Data Sheet:
 *   https://www.ftdichip.com/Support/Documents/DataSheets/ICs/DS_FT260.pdf
 */

#समावेश "hid-ids.h"
#समावेश <linux/hidraw.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#अगर_घोषित DEBUG
अटल पूर्णांक ft260_debug = 1;
#अन्यथा
अटल पूर्णांक ft260_debug;
#पूर्ण_अगर
module_param_named(debug, ft260_debug, पूर्णांक, 0600);
MODULE_PARM_DESC(debug, "Toggle FT260 debugging messages");

#घोषणा ft260_dbg(क्रमmat, arg...)					  \
	करो अणु								  \
		अगर (ft260_debug)					  \
			pr_info("%s: " क्रमmat, __func__, ##arg);	  \
	पूर्ण जबतक (0)

#घोषणा FT260_REPORT_MAX_LENGTH (64)
#घोषणा FT260_I2C_DATA_REPORT_ID(len) (FT260_I2C_REPORT_MIN + (len - 1) / 4)
/*
 * The input report क्रमmat assigns 62 bytes क्रम the data payload, but ft260
 * वापसs 60 and 2 in two separate transactions. To minimize transfer समय
 * in पढ़ोing chunks mode, set the maximum पढ़ो payload length to 60 bytes.
 */
#घोषणा FT260_RD_DATA_MAX (60)
#घोषणा FT260_WR_DATA_MAX (60)

/*
 * Device पूर्णांकerface configuration.
 * The FT260 has 2 पूर्णांकerfaces that are controlled by DCNF0 and DCNF1 pins.
 * First implementes USB HID to I2C bridge function and
 * second - USB HID to UART bridge function.
 */
क्रमागत अणु
	FT260_MODE_ALL			= 0x00,
	FT260_MODE_I2C			= 0x01,
	FT260_MODE_UART			= 0x02,
	FT260_MODE_BOTH			= 0x03,
पूर्ण;

/* Control pipe */
क्रमागत अणु
	FT260_GET_RQST_TYPE		= 0xA1,
	FT260_GET_REPORT		= 0x01,
	FT260_SET_RQST_TYPE		= 0x21,
	FT260_SET_REPORT		= 0x09,
	FT260_FEATURE			= 0x03,
पूर्ण;

/* Report IDs / Feature In */
क्रमागत अणु
	FT260_CHIP_VERSION		= 0xA0,
	FT260_SYSTEM_SETTINGS		= 0xA1,
	FT260_I2C_STATUS		= 0xC0,
	FT260_I2C_READ_REQ		= 0xC2,
	FT260_I2C_REPORT_MIN		= 0xD0,
	FT260_I2C_REPORT_MAX		= 0xDE,
	FT260_GPIO			= 0xB0,
	FT260_UART_INTERRUPT_STATUS	= 0xB1,
	FT260_UART_STATUS		= 0xE0,
	FT260_UART_RI_DCD_STATUS	= 0xE1,
	FT260_UART_REPORT		= 0xF0,
पूर्ण;

/* Feature Out */
क्रमागत अणु
	FT260_SET_CLOCK			= 0x01,
	FT260_SET_I2C_MODE		= 0x02,
	FT260_SET_UART_MODE		= 0x03,
	FT260_ENABLE_INTERRUPT		= 0x05,
	FT260_SELECT_GPIO2_FUNC		= 0x06,
	FT260_ENABLE_UART_DCD_RI	= 0x07,
	FT260_SELECT_GPIOA_FUNC		= 0x08,
	FT260_SELECT_GPIOG_FUNC		= 0x09,
	FT260_SET_INTERRUPT_TRIGGER	= 0x0A,
	FT260_SET_SUSPEND_OUT_POLAR	= 0x0B,
	FT260_ENABLE_UART_RI_WAKEUP	= 0x0C,
	FT260_SET_UART_RI_WAKEUP_CFG	= 0x0D,
	FT260_SET_I2C_RESET		= 0x20,
	FT260_SET_I2C_CLOCK_SPEED	= 0x22,
	FT260_SET_UART_RESET		= 0x40,
	FT260_SET_UART_CONFIG		= 0x41,
	FT260_SET_UART_BAUD_RATE	= 0x42,
	FT260_SET_UART_DATA_BIT		= 0x43,
	FT260_SET_UART_PARITY		= 0x44,
	FT260_SET_UART_STOP_BIT		= 0x45,
	FT260_SET_UART_BREAKING		= 0x46,
	FT260_SET_UART_XON_XOFF		= 0x49,
पूर्ण;

/* Response codes in I2C status report */
क्रमागत अणु
	FT260_I2C_STATUS_SUCCESS	= 0x00,
	FT260_I2C_STATUS_CTRL_BUSY	= 0x01,
	FT260_I2C_STATUS_ERROR		= 0x02,
	FT260_I2C_STATUS_ADDR_NO_ACK	= 0x04,
	FT260_I2C_STATUS_DATA_NO_ACK	= 0x08,
	FT260_I2C_STATUS_ARBITR_LOST	= 0x10,
	FT260_I2C_STATUS_CTRL_IDLE	= 0x20,
	FT260_I2C_STATUS_BUS_BUSY	= 0x40,
पूर्ण;

/* I2C Conditions flags */
क्रमागत अणु
	FT260_FLAG_NONE			= 0x00,
	FT260_FLAG_START		= 0x02,
	FT260_FLAG_START_REPEATED	= 0x03,
	FT260_FLAG_STOP			= 0x04,
	FT260_FLAG_START_STOP		= 0x06,
	FT260_FLAG_START_STOP_REPEATED	= 0x07,
पूर्ण;

#घोषणा FT260_SET_REQUEST_VALUE(report_id) ((FT260_FEATURE << 8) | report_id)

/* Feature In reports */

काष्ठा ft260_get_chip_version_report अणु
	u8 report;		/* FT260_CHIP_VERSION */
	u8 chip_code[4];	/* FTDI chip identअगरication code */
	u8 reserved[8];
पूर्ण __packed;

काष्ठा ft260_get_प्रणाली_status_report अणु
	u8 report;		/* FT260_SYSTEM_SETTINGS */
	u8 chip_mode;		/* DCNF0 and DCNF1 status, bits 0-1 */
	u8 घड़ी_ctl;		/* 0 - 12MHz, 1 - 24MHz, 2 - 48MHz */
	u8 suspend_status;	/* 0 - not suspended, 1 - suspended */
	u8 pwren_status;	/* 0 - FT260 is not पढ़ोy, 1 - पढ़ोy */
	u8 i2c_enable;		/* 0 - disabled, 1 - enabled */
	u8 uart_mode;		/* 0 - OFF; 1 - RTS_CTS, 2 - DTR_DSR, */
				/* 3 - XON_XOFF, 4 - No flow control */
	u8 hid_over_i2c_en;	/* 0 - disabled, 1 - enabled */
	u8 gpio2_function;	/* 0 - GPIO,  1 - SUSPOUT, */
				/* 2 - PWREN, 4 - TX_LED */
	u8 gpioA_function;	/* 0 - GPIO, 3 - TX_ACTIVE, 4 - TX_LED */
	u8 gpioG_function;	/* 0 - GPIO, 2 - PWREN, */
				/* 5 - RX_LED, 6 - BCD_DET */
	u8 suspend_out_pol;	/* 0 - active-high, 1 - active-low */
	u8 enable_wakeup_पूर्णांक;	/* 0 - disabled, 1 - enabled */
	u8 पूर्णांकr_cond;		/* Interrupt trigger conditions */
	u8 घातer_saving_en;	/* 0 - disabled, 1 - enabled */
	u8 reserved[10];
पूर्ण __packed;

काष्ठा ft260_get_i2c_status_report अणु
	u8 report;		/* FT260_I2C_STATUS */
	u8 bus_status;		/* I2C bus status */
	__le16 घड़ी;		/* I2C bus घड़ी in range 60-3400 KHz */
	u8 reserved;
पूर्ण __packed;

/* Feature Out reports */

काष्ठा ft260_set_प्रणाली_घड़ी_report अणु
	u8 report;		/* FT260_SYSTEM_SETTINGS */
	u8 request;		/* FT260_SET_CLOCK */
	u8 घड़ी_ctl;		/* 0 - 12MHz, 1 - 24MHz, 2 - 48MHz */
पूर्ण __packed;

काष्ठा ft260_set_i2c_mode_report अणु
	u8 report;		/* FT260_SYSTEM_SETTINGS */
	u8 request;		/* FT260_SET_I2C_MODE */
	u8 i2c_enable;		/* 0 - disabled, 1 - enabled */
पूर्ण __packed;

काष्ठा ft260_set_uart_mode_report अणु
	u8 report;		/* FT260_SYSTEM_SETTINGS */
	u8 request;		/* FT260_SET_UART_MODE */
	u8 uart_mode;		/* 0 - OFF; 1 - RTS_CTS, 2 - DTR_DSR, */
				/* 3 - XON_XOFF, 4 - No flow control */
पूर्ण __packed;

काष्ठा ft260_set_i2c_reset_report अणु
	u8 report;		/* FT260_SYSTEM_SETTINGS */
	u8 request;		/* FT260_SET_I2C_RESET */
पूर्ण __packed;

काष्ठा ft260_set_i2c_speed_report अणु
	u8 report;		/* FT260_SYSTEM_SETTINGS */
	u8 request;		/* FT260_SET_I2C_CLOCK_SPEED */
	__le16 घड़ी;		/* I2C bus घड़ी in range 60-3400 KHz */
पूर्ण __packed;

/* Data transfer reports */

काष्ठा ft260_i2c_ग_लिखो_request_report अणु
	u8 report;		/* FT260_I2C_REPORT */
	u8 address;		/* 7-bit I2C address */
	u8 flag;		/* I2C transaction condition */
	u8 length;		/* data payload length */
	u8 data[FT260_WR_DATA_MAX]; /* data payload */
पूर्ण __packed;

काष्ठा ft260_i2c_पढ़ो_request_report अणु
	u8 report;		/* FT260_I2C_READ_REQ */
	u8 address;		/* 7-bit I2C address */
	u8 flag;		/* I2C transaction condition */
	__le16 length;		/* data payload length */
पूर्ण __packed;

काष्ठा ft260_i2c_input_report अणु
	u8 report;		/* FT260_I2C_REPORT */
	u8 length;		/* data payload length */
	u8 data[2];		/* data payload */
पूर्ण __packed;

अटल स्थिर काष्ठा hid_device_id ft260_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_FUTURE_TECHNOLOGY,
			 USB_DEVICE_ID_FT260) पूर्ण,
	अणु /* END OF LIST */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ft260_devices);

काष्ठा ft260_device अणु
	काष्ठा i2c_adapter adap;
	काष्ठा hid_device *hdev;
	काष्ठा completion रुको;
	काष्ठा mutex lock;
	u8 ग_लिखो_buf[FT260_REPORT_MAX_LENGTH];
	u8 *पढ़ो_buf;
	u16 पढ़ो_idx;
	u16 पढ़ो_len;
	u16 घड़ी;
पूर्ण;

अटल पूर्णांक ft260_hid_feature_report_get(काष्ठा hid_device *hdev,
					अचिन्हित अक्षर report_id, u8 *data,
					माप_प्रकार len)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = hid_hw_raw_request(hdev, report_id, buf, len, HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);
	अगर (likely(ret == len))
		स_नकल(data, buf, len);
	अन्यथा अगर (ret >= 0)
		ret = -EIO;
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक ft260_hid_feature_report_set(काष्ठा hid_device *hdev, u8 *data,
					माप_प्रकार len)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kmemdup(data, len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = FT260_SYSTEM_SETTINGS;

	ret = hid_hw_raw_request(hdev, buf[0], buf, len, HID_FEATURE_REPORT,
				 HID_REQ_SET_REPORT);

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक ft260_i2c_reset(काष्ठा hid_device *hdev)
अणु
	काष्ठा ft260_set_i2c_reset_report report;
	पूर्णांक ret;

	report.request = FT260_SET_I2C_RESET;

	ret = ft260_hid_feature_report_set(hdev, (u8 *)&report, माप(report));
	अगर (ret < 0) अणु
		hid_err(hdev, "failed to reset I2C controller: %d\n", ret);
		वापस ret;
	पूर्ण

	ft260_dbg("done\n");
	वापस ret;
पूर्ण

अटल पूर्णांक ft260_xfer_status(काष्ठा ft260_device *dev)
अणु
	काष्ठा hid_device *hdev = dev->hdev;
	काष्ठा ft260_get_i2c_status_report report;
	पूर्णांक ret;

	ret = ft260_hid_feature_report_get(hdev, FT260_I2C_STATUS,
					   (u8 *)&report, माप(report));
	अगर (unlikely(ret < 0)) अणु
		hid_err(hdev, "failed to retrieve status: %d\n", ret);
		वापस ret;
	पूर्ण

	dev->घड़ी = le16_to_cpu(report.घड़ी);
	ft260_dbg("bus_status %#02x, clock %u\n", report.bus_status,
		  dev->घड़ी);

	अगर (report.bus_status & FT260_I2C_STATUS_CTRL_BUSY)
		वापस -EAGAIN;

	अगर (report.bus_status & FT260_I2C_STATUS_BUS_BUSY)
		वापस -EBUSY;

	अगर (report.bus_status & FT260_I2C_STATUS_ERROR)
		वापस -EIO;

	ret = -EIO;

	अगर (report.bus_status & FT260_I2C_STATUS_ADDR_NO_ACK)
		ft260_dbg("unacknowledged address\n");

	अगर (report.bus_status & FT260_I2C_STATUS_DATA_NO_ACK)
		ft260_dbg("unacknowledged data\n");

	अगर (report.bus_status & FT260_I2C_STATUS_ARBITR_LOST)
		ft260_dbg("arbitration loss\n");

	अगर (report.bus_status & FT260_I2C_STATUS_CTRL_IDLE)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक ft260_hid_output_report(काष्ठा hid_device *hdev, u8 *data,
				   माप_प्रकार len)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kmemdup(data, len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = hid_hw_output_report(hdev, buf, len);

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक ft260_hid_output_report_check_status(काष्ठा ft260_device *dev,
						u8 *data, पूर्णांक len)
अणु
	पूर्णांक ret, usec, try = 3;
	काष्ठा hid_device *hdev = dev->hdev;

	ret = ft260_hid_output_report(hdev, data, len);
	अगर (ret < 0) अणु
		hid_err(hdev, "%s: failed to start transfer, ret %d\n",
			__func__, ret);
		ft260_i2c_reset(hdev);
		वापस ret;
	पूर्ण

	/* transfer समय = 1 / घड़ी(KHz) * 10 bits * bytes */
	usec = 10000 / dev->घड़ी * len;
	usleep_range(usec, usec + 100);
	ft260_dbg("wait %d usec, len %d\n", usec, len);
	करो अणु
		ret = ft260_xfer_status(dev);
		अगर (ret != -EAGAIN)
			अवरोध;
	पूर्ण जबतक (--try);

	अगर (ret == 0 || ret == -EBUSY)
		वापस 0;

	ft260_i2c_reset(hdev);
	वापस -EIO;
पूर्ण

अटल पूर्णांक ft260_i2c_ग_लिखो(काष्ठा ft260_device *dev, u8 addr, u8 *data,
			   पूर्णांक data_len, u8 flag)
अणु
	पूर्णांक len, ret, idx = 0;
	काष्ठा hid_device *hdev = dev->hdev;
	काष्ठा ft260_i2c_ग_लिखो_request_report *rep =
		(काष्ठा ft260_i2c_ग_लिखो_request_report *)dev->ग_लिखो_buf;

	करो अणु
		अगर (data_len <= FT260_WR_DATA_MAX)
			len = data_len;
		अन्यथा
			len = FT260_WR_DATA_MAX;

		rep->report = FT260_I2C_DATA_REPORT_ID(len);
		rep->address = addr;
		rep->length = len;
		rep->flag = flag;

		स_नकल(rep->data, &data[idx], len);

		ft260_dbg("rep %#02x addr %#02x off %d len %d d[0] %#02x\n",
			  rep->report, addr, idx, len, data[0]);

		ret = ft260_hid_output_report_check_status(dev, (u8 *)rep,
							   len + 4);
		अगर (ret < 0) अणु
			hid_err(hdev, "%s: failed to start transfer, ret %d\n",
				__func__, ret);
			वापस ret;
		पूर्ण

		data_len -= len;
		idx += len;

	पूर्ण जबतक (data_len > 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ft260_smbus_ग_लिखो(काष्ठा ft260_device *dev, u8 addr, u8 cmd,
			     u8 *data, u8 data_len, u8 flag)
अणु
	पूर्णांक ret = 0;
	पूर्णांक len = 4;

	काष्ठा ft260_i2c_ग_लिखो_request_report *rep =
		(काष्ठा ft260_i2c_ग_लिखो_request_report *)dev->ग_लिखो_buf;

	अगर (data_len >= माप(rep->data))
		वापस -EINVAL;

	rep->address = addr;
	rep->data[0] = cmd;
	rep->length = data_len + 1;
	rep->flag = flag;
	len += rep->length;

	rep->report = FT260_I2C_DATA_REPORT_ID(len);

	अगर (data_len > 0)
		स_नकल(&rep->data[1], data, data_len);

	ft260_dbg("rep %#02x addr %#02x cmd %#02x datlen %d replen %d\n",
		  rep->report, addr, cmd, rep->length, len);

	ret = ft260_hid_output_report_check_status(dev, (u8 *)rep, len);

	वापस ret;
पूर्ण

अटल पूर्णांक ft260_i2c_पढ़ो(काष्ठा ft260_device *dev, u8 addr, u8 *data,
			  u16 len, u8 flag)
अणु
	काष्ठा ft260_i2c_पढ़ो_request_report rep;
	काष्ठा hid_device *hdev = dev->hdev;
	पूर्णांक समयout;
	पूर्णांक ret;

	अगर (len > FT260_RD_DATA_MAX) अणु
		hid_err(hdev, "%s: unsupported rd len: %d\n", __func__, len);
		वापस -EINVAL;
	पूर्ण

	dev->पढ़ो_idx = 0;
	dev->पढ़ो_buf = data;
	dev->पढ़ो_len = len;

	rep.report = FT260_I2C_READ_REQ;
	rep.length = cpu_to_le16(len);
	rep.address = addr;
	rep.flag = flag;

	ft260_dbg("rep %#02x addr %#02x len %d\n", rep.report, rep.address,
		  rep.length);

	reinit_completion(&dev->रुको);

	ret = ft260_hid_output_report(hdev, (u8 *)&rep, माप(rep));
	अगर (ret < 0) अणु
		hid_err(hdev, "%s: failed to start transaction, ret %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	समयout = msecs_to_jअगरfies(5000);
	अगर (!रुको_क्रम_completion_समयout(&dev->रुको, समयout)) अणु
		ft260_i2c_reset(hdev);
		वापस -ETIMEDOUT;
	पूर्ण

	ret = ft260_xfer_status(dev);
	अगर (ret == 0)
		वापस 0;

	ft260_i2c_reset(hdev);
	वापस -EIO;
पूर्ण

/*
 * A अक्रमom पढ़ो operation is implemented as a dummy ग_लिखो operation, followed
 * by a current address पढ़ो operation. The dummy ग_लिखो operation is used to
 * load the target byte address पूर्णांकo the current byte address counter, from
 * which the subsequent current address पढ़ो operation then पढ़ोs.
 */
अटल पूर्णांक ft260_i2c_ग_लिखो_पढ़ो(काष्ठा ft260_device *dev, काष्ठा i2c_msg *msgs)
अणु
	पूर्णांक len, ret;
	u16 left_len = msgs[1].len;
	u8 *पढ़ो_buf = msgs[1].buf;
	u8 addr = msgs[0].addr;
	u16 पढ़ो_off = 0;
	काष्ठा hid_device *hdev = dev->hdev;

	अगर (msgs[0].len > 2) अणु
		hid_err(hdev, "%s: unsupported wr len: %d\n", __func__,
			msgs[0].len);
		वापस -EOPNOTSUPP;
	पूर्ण

	स_नकल(&पढ़ो_off, msgs[0].buf, msgs[0].len);

	करो अणु
		अगर (left_len <= FT260_RD_DATA_MAX)
			len = left_len;
		अन्यथा
			len = FT260_RD_DATA_MAX;

		ft260_dbg("read_off %#x left_len %d len %d\n", पढ़ो_off,
			  left_len, len);

		ret = ft260_i2c_ग_लिखो(dev, addr, (u8 *)&पढ़ो_off, msgs[0].len,
				      FT260_FLAG_START);
		अगर (ret < 0)
			वापस ret;

		ret = ft260_i2c_पढ़ो(dev, addr, पढ़ो_buf, len,
				     FT260_FLAG_START_STOP);
		अगर (ret < 0)
			वापस ret;

		left_len -= len;
		पढ़ो_buf += len;
		पढ़ो_off += len;

	पूर्ण जबतक (left_len > 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ft260_i2c_xfer(काष्ठा i2c_adapter *adapter, काष्ठा i2c_msg *msgs,
			  पूर्णांक num)
अणु
	पूर्णांक ret;
	काष्ठा ft260_device *dev = i2c_get_adapdata(adapter);
	काष्ठा hid_device *hdev = dev->hdev;

	mutex_lock(&dev->lock);

	ret = hid_hw_घातer(hdev, PM_HINT_FULLON);
	अगर (ret < 0) अणु
		hid_err(hdev, "failed to enter FULLON power mode: %d\n", ret);
		mutex_unlock(&dev->lock);
		वापस ret;
	पूर्ण

	अगर (num == 1) अणु
		अगर (msgs->flags & I2C_M_RD)
			ret = ft260_i2c_पढ़ो(dev, msgs->addr, msgs->buf,
					     msgs->len, FT260_FLAG_START_STOP);
		अन्यथा
			ret = ft260_i2c_ग_लिखो(dev, msgs->addr, msgs->buf,
					      msgs->len, FT260_FLAG_START_STOP);
		अगर (ret < 0)
			जाओ i2c_निकास;

	पूर्ण अन्यथा अणु
		/* Combined ग_लिखो then पढ़ो message */
		ret = ft260_i2c_ग_लिखो_पढ़ो(dev, msgs);
		अगर (ret < 0)
			जाओ i2c_निकास;
	पूर्ण

	ret = num;
i2c_निकास:
	hid_hw_घातer(hdev, PM_HINT_NORMAL);
	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ft260_smbus_xfer(काष्ठा i2c_adapter *adapter, u16 addr, u16 flags,
			    अक्षर पढ़ो_ग_लिखो, u8 cmd, पूर्णांक size,
			    जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक ret;
	काष्ठा ft260_device *dev = i2c_get_adapdata(adapter);
	काष्ठा hid_device *hdev = dev->hdev;

	ft260_dbg("smbus size %d\n", size);

	mutex_lock(&dev->lock);

	ret = hid_hw_घातer(hdev, PM_HINT_FULLON);
	अगर (ret < 0) अणु
		hid_err(hdev, "power management error: %d\n", ret);
		mutex_unlock(&dev->lock);
		वापस ret;
	पूर्ण

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
			ret = ft260_i2c_पढ़ो(dev, addr, &data->byte, 0,
					     FT260_FLAG_START_STOP);
		अन्यथा
			ret = ft260_smbus_ग_लिखो(dev, addr, cmd, शून्य, 0,
						FT260_FLAG_START_STOP);
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
			ret = ft260_i2c_पढ़ो(dev, addr, &data->byte, 1,
					     FT260_FLAG_START_STOP);
		अन्यथा
			ret = ft260_smbus_ग_लिखो(dev, addr, cmd, शून्य, 0,
						FT260_FLAG_START_STOP);
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = ft260_smbus_ग_लिखो(dev, addr, cmd, शून्य, 0,
						FT260_FLAG_START);
			अगर (ret)
				जाओ smbus_निकास;

			ret = ft260_i2c_पढ़ो(dev, addr, &data->byte, 1,
					     FT260_FLAG_START_STOP_REPEATED);
		पूर्ण अन्यथा अणु
			ret = ft260_smbus_ग_लिखो(dev, addr, cmd, &data->byte, 1,
						FT260_FLAG_START_STOP);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = ft260_smbus_ग_लिखो(dev, addr, cmd, शून्य, 0,
						FT260_FLAG_START);
			अगर (ret)
				जाओ smbus_निकास;

			ret = ft260_i2c_पढ़ो(dev, addr, (u8 *)&data->word, 2,
					     FT260_FLAG_START_STOP_REPEATED);
		पूर्ण अन्यथा अणु
			ret = ft260_smbus_ग_लिखो(dev, addr, cmd,
						(u8 *)&data->word, 2,
						FT260_FLAG_START_STOP);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = ft260_smbus_ग_लिखो(dev, addr, cmd, शून्य, 0,
						FT260_FLAG_START);
			अगर (ret)
				जाओ smbus_निकास;

			ret = ft260_i2c_पढ़ो(dev, addr, data->block,
					     data->block[0] + 1,
					     FT260_FLAG_START_STOP_REPEATED);
		पूर्ण अन्यथा अणु
			ret = ft260_smbus_ग_लिखो(dev, addr, cmd, data->block,
						data->block[0] + 1,
						FT260_FLAG_START_STOP);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			ret = ft260_smbus_ग_लिखो(dev, addr, cmd, शून्य, 0,
						FT260_FLAG_START);
			अगर (ret)
				जाओ smbus_निकास;

			ret = ft260_i2c_पढ़ो(dev, addr, data->block + 1,
					     data->block[0],
					     FT260_FLAG_START_STOP_REPEATED);
		पूर्ण अन्यथा अणु
			ret = ft260_smbus_ग_लिखो(dev, addr, cmd, data->block + 1,
						data->block[0],
						FT260_FLAG_START_STOP);
		पूर्ण
		अवरोध;
	शेष:
		hid_err(hdev, "unsupported smbus transaction size %d\n", size);
		ret = -EOPNOTSUPP;
	पूर्ण

smbus_निकास:
	hid_hw_घातer(hdev, PM_HINT_NORMAL);
	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण

अटल u32 ft260_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_QUICK |
	       I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	       I2C_FUNC_SMBUS_BLOCK_DATA | I2C_FUNC_SMBUS_I2C_BLOCK;
पूर्ण

अटल स्थिर काष्ठा i2c_adapter_quirks ft260_i2c_quirks = अणु
	.flags = I2C_AQ_COMB_WRITE_THEN_READ,
	.max_comb_1st_msg_len = 2,
पूर्ण;

अटल स्थिर काष्ठा i2c_algorithm ft260_i2c_algo = अणु
	.master_xfer = ft260_i2c_xfer,
	.smbus_xfer = ft260_smbus_xfer,
	.functionality = ft260_functionality,
पूर्ण;

अटल पूर्णांक ft260_get_प्रणाली_config(काष्ठा hid_device *hdev,
				   काष्ठा ft260_get_प्रणाली_status_report *cfg)
अणु
	पूर्णांक ret;
	पूर्णांक len = माप(काष्ठा ft260_get_प्रणाली_status_report);

	ret = ft260_hid_feature_report_get(hdev, FT260_SYSTEM_SETTINGS,
					   (u8 *)cfg, len);
	अगर (ret < 0) अणु
		hid_err(hdev, "failed to retrieve system status\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ft260_is_पूर्णांकerface_enabled(काष्ठा hid_device *hdev)
अणु
	काष्ठा ft260_get_प्रणाली_status_report cfg;
	काष्ठा usb_पूर्णांकerface *usbअगर = to_usb_पूर्णांकerface(hdev->dev.parent);
	पूर्णांक पूर्णांकerface = usbअगर->cur_altsetting->desc.bInterfaceNumber;
	पूर्णांक ret;

	ret = ft260_get_प्रणाली_config(hdev, &cfg);
	अगर (ret)
		वापस ret;

	ft260_dbg("interface:  0x%02x\n", पूर्णांकerface);
	ft260_dbg("chip mode:  0x%02x\n", cfg.chip_mode);
	ft260_dbg("clock_ctl:  0x%02x\n", cfg.घड़ी_ctl);
	ft260_dbg("i2c_enable: 0x%02x\n", cfg.i2c_enable);
	ft260_dbg("uart_mode:  0x%02x\n", cfg.uart_mode);

	चयन (cfg.chip_mode) अणु
	हाल FT260_MODE_ALL:
	हाल FT260_MODE_BOTH:
		अगर (पूर्णांकerface == 1) अणु
			hid_info(hdev, "uart interface is not supported\n");
			वापस 0;
		पूर्ण
		ret = 1;
		अवरोध;
	हाल FT260_MODE_UART:
		अगर (पूर्णांकerface == 0) अणु
			hid_info(hdev, "uart is unsupported on interface 0\n");
			ret = 0;
		पूर्ण
		अवरोध;
	हाल FT260_MODE_I2C:
		अगर (पूर्णांकerface == 1) अणु
			hid_info(hdev, "i2c is unsupported on interface 1\n");
			ret = 0;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ft260_byte_show(काष्ठा hid_device *hdev, पूर्णांक id, u8 *cfg, पूर्णांक len,
			   u8 *field, u8 *buf)
अणु
	पूर्णांक ret;

	ret = ft260_hid_feature_report_get(hdev, id, cfg, len);
	अगर (ret < 0)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%hi\n", *field);
पूर्ण

अटल पूर्णांक ft260_word_show(काष्ठा hid_device *hdev, पूर्णांक id, u8 *cfg, पूर्णांक len,
			   u16 *field, u8 *buf)
अणु
	पूर्णांक ret;

	ret = ft260_hid_feature_report_get(hdev, id, cfg, len);
	अगर (ret < 0)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%hi\n", le16_to_cpu(*field));
पूर्ण

#घोषणा FT260_ATTR_SHOW(name, reptype, id, type, func)			       \
	अटल sमाप_प्रकार name##_show(काष्ठा device *kdev,			       \
				   काष्ठा device_attribute *attr, अक्षर *buf)   \
	अणु								       \
		काष्ठा reptype rep;					       \
		काष्ठा hid_device *hdev = to_hid_device(kdev);		       \
		type *field = &rep.name;				       \
		पूर्णांक len = माप(rep);					       \
									       \
		वापस func(hdev, id, (u8 *)&rep, len, field, buf);	       \
	पूर्ण

#घोषणा FT260_SSTAT_ATTR_SHOW(name)					       \
		FT260_ATTR_SHOW(name, ft260_get_प्रणाली_status_report,	       \
				FT260_SYSTEM_SETTINGS, u8, ft260_byte_show)

#घोषणा FT260_I2CST_ATTR_SHOW(name)					       \
		FT260_ATTR_SHOW(name, ft260_get_i2c_status_report,	       \
				FT260_I2C_STATUS, u16, ft260_word_show)

#घोषणा FT260_ATTR_STORE(name, reptype, id, req, type, func)		       \
	अटल sमाप_प्रकार name##_store(काष्ठा device *kdev,		       \
				    काष्ठा device_attribute *attr,	       \
				    स्थिर अक्षर *buf, माप_प्रकार count)	       \
	अणु								       \
		काष्ठा reptype rep;					       \
		काष्ठा hid_device *hdev = to_hid_device(kdev);		       \
		type name;						       \
		पूर्णांक ret;						       \
									       \
		अगर (!func(buf, 10, &name)) अणु				       \
			rep.name = name;				       \
			rep.report = id;				       \
			rep.request = req;				       \
			ret = ft260_hid_feature_report_set(hdev, (u8 *)&rep,   \
							   माप(rep));       \
			अगर (!ret)					       \
				ret = count;				       \
		पूर्ण अन्यथा अणु						       \
			ret = -EINVAL;					       \
		पूर्ण							       \
		वापस ret;						       \
	पूर्ण

#घोषणा FT260_BYTE_ATTR_STORE(name, reptype, req)			       \
		FT260_ATTR_STORE(name, reptype, FT260_SYSTEM_SETTINGS, req,    \
				 u8, kstrtou8)

#घोषणा FT260_WORD_ATTR_STORE(name, reptype, req)			       \
		FT260_ATTR_STORE(name, reptype, FT260_SYSTEM_SETTINGS, req,    \
				 u16, kstrtou16)

FT260_SSTAT_ATTR_SHOW(chip_mode);
अटल DEVICE_ATTR_RO(chip_mode);

FT260_SSTAT_ATTR_SHOW(pwren_status);
अटल DEVICE_ATTR_RO(pwren_status);

FT260_SSTAT_ATTR_SHOW(suspend_status);
अटल DEVICE_ATTR_RO(suspend_status);

FT260_SSTAT_ATTR_SHOW(hid_over_i2c_en);
अटल DEVICE_ATTR_RO(hid_over_i2c_en);

FT260_SSTAT_ATTR_SHOW(घातer_saving_en);
अटल DEVICE_ATTR_RO(घातer_saving_en);

FT260_SSTAT_ATTR_SHOW(i2c_enable);
FT260_BYTE_ATTR_STORE(i2c_enable, ft260_set_i2c_mode_report,
		      FT260_SET_I2C_MODE);
अटल DEVICE_ATTR_RW(i2c_enable);

FT260_SSTAT_ATTR_SHOW(uart_mode);
FT260_BYTE_ATTR_STORE(uart_mode, ft260_set_uart_mode_report,
		      FT260_SET_UART_MODE);
अटल DEVICE_ATTR_RW(uart_mode);

FT260_SSTAT_ATTR_SHOW(घड़ी_ctl);
FT260_BYTE_ATTR_STORE(घड़ी_ctl, ft260_set_प्रणाली_घड़ी_report,
		      FT260_SET_CLOCK);
अटल DEVICE_ATTR_RW(घड़ी_ctl);

FT260_I2CST_ATTR_SHOW(घड़ी);
FT260_WORD_ATTR_STORE(घड़ी, ft260_set_i2c_speed_report,
		      FT260_SET_I2C_CLOCK_SPEED);
अटल DEVICE_ATTR_RW(घड़ी);

अटल sमाप_प्रकार i2c_reset_store(काष्ठा device *kdev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा hid_device *hdev = to_hid_device(kdev);
	पूर्णांक ret = ft260_i2c_reset(hdev);

	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(i2c_reset);

अटल स्थिर काष्ठा attribute_group ft260_attr_group = अणु
	.attrs = (काष्ठा attribute *[]) अणु
		  &dev_attr_chip_mode.attr,
		  &dev_attr_pwren_status.attr,
		  &dev_attr_suspend_status.attr,
		  &dev_attr_hid_over_i2c_en.attr,
		  &dev_attr_घातer_saving_en.attr,
		  &dev_attr_i2c_enable.attr,
		  &dev_attr_uart_mode.attr,
		  &dev_attr_घड़ी_ctl.attr,
		  &dev_attr_i2c_reset.attr,
		  &dev_attr_घड़ी.attr,
		  शून्य
	पूर्ण
पूर्ण;

अटल पूर्णांक ft260_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा ft260_device *dev;
	काष्ठा ft260_get_chip_version_report version;
	पूर्णांक ret;

	dev = devm_kzalloc(&hdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "failed to parse HID\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	अगर (ret) अणु
		hid_err(hdev, "failed to start HID HW\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_खोलो(hdev);
	अगर (ret) अणु
		hid_err(hdev, "failed to open HID HW\n");
		जाओ err_hid_stop;
	पूर्ण

	ret = ft260_hid_feature_report_get(hdev, FT260_CHIP_VERSION,
					   (u8 *)&version, माप(version));
	अगर (ret < 0) अणु
		hid_err(hdev, "failed to retrieve chip version\n");
		जाओ err_hid_बंद;
	पूर्ण

	hid_info(hdev, "chip code: %02x%02x %02x%02x\n",
		 version.chip_code[0], version.chip_code[1],
		 version.chip_code[2], version.chip_code[3]);

	ret = ft260_is_पूर्णांकerface_enabled(hdev);
	अगर (ret <= 0)
		जाओ err_hid_बंद;

	hid_set_drvdata(hdev, dev);
	dev->hdev = hdev;
	dev->adap.owner = THIS_MODULE;
	dev->adap.class = I2C_CLASS_HWMON;
	dev->adap.algo = &ft260_i2c_algo;
	dev->adap.quirks = &ft260_i2c_quirks;
	dev->adap.dev.parent = &hdev->dev;
	snम_लिखो(dev->adap.name, माप(dev->adap.name),
		 "FT260 usb-i2c bridge on hidraw%d",
		 ((काष्ठा hidraw *)hdev->hidraw)->minor);

	mutex_init(&dev->lock);
	init_completion(&dev->रुको);

	ret = i2c_add_adapter(&dev->adap);
	अगर (ret) अणु
		hid_err(hdev, "failed to add i2c adapter\n");
		जाओ err_hid_बंद;
	पूर्ण

	i2c_set_adapdata(&dev->adap, dev);

	ret = sysfs_create_group(&hdev->dev.kobj, &ft260_attr_group);
	अगर (ret < 0) अणु
		hid_err(hdev, "failed to create sysfs attrs\n");
		जाओ err_i2c_मुक्त;
	पूर्ण

	ret = ft260_xfer_status(dev);
	अगर (ret)
		ft260_i2c_reset(hdev);

	वापस 0;

err_i2c_मुक्त:
	i2c_del_adapter(&dev->adap);
err_hid_बंद:
	hid_hw_बंद(hdev);
err_hid_stop:
	hid_hw_stop(hdev);
	वापस ret;
पूर्ण

अटल व्योम ft260_हटाओ(काष्ठा hid_device *hdev)
अणु
	पूर्णांक ret;
	काष्ठा ft260_device *dev = hid_get_drvdata(hdev);

	ret = ft260_is_पूर्णांकerface_enabled(hdev);
	अगर (ret <= 0)
		वापस;

	sysfs_हटाओ_group(&hdev->dev.kobj, &ft260_attr_group);
	i2c_del_adapter(&dev->adap);

	hid_hw_बंद(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल पूर्णांक ft260_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
			   u8 *data, पूर्णांक size)
अणु
	काष्ठा ft260_device *dev = hid_get_drvdata(hdev);
	काष्ठा ft260_i2c_input_report *xfer = (व्योम *)data;

	अगर (xfer->report >= FT260_I2C_REPORT_MIN &&
	    xfer->report <= FT260_I2C_REPORT_MAX) अणु
		ft260_dbg("i2c resp: rep %#02x len %d\n", xfer->report,
			  xfer->length);

		स_नकल(&dev->पढ़ो_buf[dev->पढ़ो_idx], &xfer->data,
		       xfer->length);
		dev->पढ़ो_idx += xfer->length;

		अगर (dev->पढ़ो_idx == dev->पढ़ो_len)
			complete(&dev->रुको);

	पूर्ण अन्यथा अणु
		hid_err(hdev, "unknown report: %#02x\n", xfer->report);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल काष्ठा hid_driver ft260_driver = अणु
	.name		= "ft260",
	.id_table	= ft260_devices,
	.probe		= ft260_probe,
	.हटाओ		= ft260_हटाओ,
	.raw_event	= ft260_raw_event,
पूर्ण;

module_hid_driver(ft260_driver);
MODULE_DESCRIPTION("FTDI FT260 USB HID to I2C host bridge");
MODULE_AUTHOR("Michael Zaidman <michael.zaidman@gmail.com>");
MODULE_LICENSE("GPL v2");
