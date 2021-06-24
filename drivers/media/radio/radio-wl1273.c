<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Texas Instruments WL1273 FM radio.
 *
 * Copyright (C) 2011 Nokia Corporation
 * Author: Matti J. Aaltonen <matti.j.aaltonen@nokia.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/wl1273-core.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>

#घोषणा DRIVER_DESC "Wl1273 FM Radio"

#घोषणा WL1273_POWER_SET_OFF		0
#घोषणा WL1273_POWER_SET_FM		BIT(0)
#घोषणा WL1273_POWER_SET_RDS		BIT(1)
#घोषणा WL1273_POWER_SET_RETENTION	BIT(4)

#घोषणा WL1273_PUPD_SET_OFF		0x00
#घोषणा WL1273_PUPD_SET_ON		0x01
#घोषणा WL1273_PUPD_SET_RETENTION	0x10

#घोषणा WL1273_FREQ(x)		(x * 10000 / 625)
#घोषणा WL1273_INV_FREQ(x)	(x * 625 / 10000)

/*
 * अटल पूर्णांक radio_nr - The number of the radio device
 *
 * The शेष is 0.
 */
अटल पूर्णांक radio_nr;
module_param(radio_nr, पूर्णांक, 0);
MODULE_PARM_DESC(radio_nr, "The number of the radio device. Default = 0");

काष्ठा wl1273_device अणु
	अक्षर *bus_type;

	u8 क्रमbidden;
	अचिन्हित पूर्णांक preemphasis;
	अचिन्हित पूर्णांक spacing;
	अचिन्हित पूर्णांक tx_घातer;
	अचिन्हित पूर्णांक rx_frequency;
	अचिन्हित पूर्णांक tx_frequency;
	अचिन्हित पूर्णांक rangelow;
	अचिन्हित पूर्णांक rangehigh;
	अचिन्हित पूर्णांक band;
	bool stereo;

	/* RDS */
	अचिन्हित पूर्णांक rds_on;

	रुको_queue_head_t पढ़ो_queue;
	काष्ठा mutex lock; /* क्रम serializing fm radio operations */
	काष्ठा completion busy;

	अचिन्हित अक्षर *buffer;
	अचिन्हित पूर्णांक buf_size;
	अचिन्हित पूर्णांक rd_index;
	अचिन्हित पूर्णांक wr_index;

	/* Selected पूर्णांकerrupts */
	u16 irq_flags;
	u16 irq_received;

	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_device v4l2dev;
	काष्ठा video_device videodev;
	काष्ठा device *dev;
	काष्ठा wl1273_core *core;
	काष्ठा file *owner;
	अक्षर *ग_लिखो_buf;
	अचिन्हित पूर्णांक rds_users;
पूर्ण;

#घोषणा WL1273_IRQ_MASK	 (WL1273_FR_EVENT		|	\
			  WL1273_POW_ENB_EVENT)

/*
 * अटल अचिन्हित पूर्णांक rds_buf - the number of RDS buffer blocks used.
 *
 * The शेष number is 100.
 */
अटल अचिन्हित पूर्णांक rds_buf = 100;
module_param(rds_buf, uपूर्णांक, 0);
MODULE_PARM_DESC(rds_buf, "Number of RDS buffer entries. Default = 100");

अटल पूर्णांक wl1273_fm_ग_लिखो_fw(काष्ठा wl1273_core *core,
			      __u8 *fw, पूर्णांक len)
अणु
	काष्ठा i2c_client *client = core->client;
	काष्ठा i2c_msg msg;
	पूर्णांक i, r = 0;

	msg.addr = client->addr;
	msg.flags = 0;

	क्रम (i = 0; i <= len; i++) अणु
		msg.len = fw[0];
		msg.buf = fw + 1;

		fw += msg.len + 1;
		dev_dbg(&client->dev, "%s:len[%d]: %d\n", __func__, i, msg.len);

		r = i2c_transfer(client->adapter, &msg, 1);
		अगर (r < 0 && i < len + 1)
			अवरोध;
	पूर्ण

	dev_dbg(&client->dev, "%s: i: %d\n", __func__, i);
	dev_dbg(&client->dev, "%s: len + 1: %d\n", __func__, len + 1);

	/* Last transfer always fails. */
	अगर (i == len || r == 1)
		r = 0;

	वापस r;
पूर्ण

#घोषणा WL1273_FIFO_HAS_DATA(status)	(1 << 5 & status)
#घोषणा WL1273_RDS_CORRECTABLE_ERROR	(1 << 3)
#घोषणा WL1273_RDS_UNCORRECTABLE_ERROR	(1 << 4)

अटल पूर्णांक wl1273_fm_rds(काष्ठा wl1273_device *radio)
अणु
	काष्ठा wl1273_core *core = radio->core;
	काष्ठा i2c_client *client = core->client;
	u16 val;
	u8 b0 = WL1273_RDS_DATA_GET, status;
	काष्ठा v4l2_rds_data rds = अणु 0, 0, 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.buf = &b0,
			.len = 1,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.buf = (u8 *) &rds,
			.len = माप(rds),
		पूर्ण
	पूर्ण;
	पूर्णांक r;

	अगर (core->mode != WL1273_MODE_RX)
		वापस 0;

	r = core->पढ़ो(core, WL1273_RDS_SYNC_GET, &val);
	अगर (r)
		वापस r;

	अगर ((val & 0x01) == 0) अणु
		/* RDS decoder not synchronized */
		वापस -EAGAIN;
	पूर्ण

	/* copy all four RDS blocks to पूर्णांकernal buffer */
	करो अणु
		r = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
		अगर (r != ARRAY_SIZE(msg)) अणु
			dev_err(radio->dev, WL1273_FM_DRIVER_NAME
				": %s: read_rds error r == %i)\n",
				__func__, r);
		पूर्ण

		status = rds.block;

		अगर (!WL1273_FIFO_HAS_DATA(status))
			अवरोध;

		/* copy bits 0-2 (the block ID) to bits 3-5 */
		rds.block = V4L2_RDS_BLOCK_MSK & status;
		rds.block |= rds.block << 3;

		/* copy the error bits to standard positions */
		अगर (WL1273_RDS_UNCORRECTABLE_ERROR & status) अणु
			rds.block |= V4L2_RDS_BLOCK_ERROR;
			rds.block &= ~V4L2_RDS_BLOCK_CORRECTED;
		पूर्ण अन्यथा अगर  (WL1273_RDS_CORRECTABLE_ERROR & status) अणु
			rds.block &= ~V4L2_RDS_BLOCK_ERROR;
			rds.block |= V4L2_RDS_BLOCK_CORRECTED;
		पूर्ण

		/* copy RDS block to पूर्णांकernal buffer */
		स_नकल(&radio->buffer[radio->wr_index], &rds, RDS_BLOCK_SIZE);
		radio->wr_index += 3;

		/* wrap ग_लिखो poपूर्णांकer */
		अगर (radio->wr_index >= radio->buf_size)
			radio->wr_index = 0;

		/* check क्रम overflow & start over */
		अगर (radio->wr_index == radio->rd_index) अणु
			dev_dbg(radio->dev, "RDS OVERFLOW");

			radio->rd_index = 0;
			radio->wr_index = 0;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (WL1273_FIFO_HAS_DATA(status));

	/* wake up पढ़ो queue */
	अगर (radio->wr_index != radio->rd_index)
		wake_up_पूर्णांकerruptible(&radio->पढ़ो_queue);

	वापस 0;
पूर्ण

अटल irqवापस_t wl1273_fm_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा wl1273_device *radio = dev_id;
	काष्ठा wl1273_core *core = radio->core;
	u16 flags;
	पूर्णांक r;

	r = core->पढ़ो(core, WL1273_FLAG_GET, &flags);
	अगर (r)
		जाओ out;

	अगर (flags & WL1273_BL_EVENT) अणु
		radio->irq_received = flags;
		dev_dbg(radio->dev, "IRQ: BL\n");
	पूर्ण

	अगर (flags & WL1273_RDS_EVENT) अणु
		msleep(200);

		wl1273_fm_rds(radio);
	पूर्ण

	अगर (flags & WL1273_BBLK_EVENT)
		dev_dbg(radio->dev, "IRQ: BBLK\n");

	अगर (flags & WL1273_LSYNC_EVENT)
		dev_dbg(radio->dev, "IRQ: LSYNC\n");

	अगर (flags & WL1273_LEV_EVENT) अणु
		u16 level;

		r = core->पढ़ो(core, WL1273_RSSI_LVL_GET, &level);
		अगर (r)
			जाओ out;

		अगर (level > 14)
			dev_dbg(radio->dev, "IRQ: LEV: 0x%x04\n", level);
	पूर्ण

	अगर (flags & WL1273_IFFR_EVENT)
		dev_dbg(radio->dev, "IRQ: IFFR\n");

	अगर (flags & WL1273_PI_EVENT)
		dev_dbg(radio->dev, "IRQ: PI\n");

	अगर (flags & WL1273_PD_EVENT)
		dev_dbg(radio->dev, "IRQ: PD\n");

	अगर (flags & WL1273_STIC_EVENT)
		dev_dbg(radio->dev, "IRQ: STIC\n");

	अगर (flags & WL1273_MAL_EVENT)
		dev_dbg(radio->dev, "IRQ: MAL\n");

	अगर (flags & WL1273_POW_ENB_EVENT) अणु
		complete(&radio->busy);
		dev_dbg(radio->dev, "NOT BUSY\n");
		dev_dbg(radio->dev, "IRQ: POW_ENB\n");
	पूर्ण

	अगर (flags & WL1273_SCAN_OVER_EVENT)
		dev_dbg(radio->dev, "IRQ: SCAN_OVER\n");

	अगर (flags & WL1273_ERROR_EVENT)
		dev_dbg(radio->dev, "IRQ: ERROR\n");

	अगर (flags & WL1273_FR_EVENT) अणु
		u16 freq;

		dev_dbg(radio->dev, "IRQ: FR:\n");

		अगर (core->mode == WL1273_MODE_RX) अणु
			r = core->ग_लिखो(core, WL1273_TUNER_MODE_SET,
					TUNER_MODE_STOP_SEARCH);
			अगर (r) अणु
				dev_err(radio->dev,
					"%s: TUNER_MODE_SET fails: %d\n",
					__func__, r);
				जाओ out;
			पूर्ण

			r = core->पढ़ो(core, WL1273_FREQ_SET, &freq);
			अगर (r)
				जाओ out;

			अगर (radio->band == WL1273_BAND_JAPAN)
				radio->rx_frequency = WL1273_BAND_JAPAN_LOW +
					freq * 50;
			अन्यथा
				radio->rx_frequency = WL1273_BAND_OTHER_LOW +
					freq * 50;
			/*
			 *  The driver works better with this msleep,
			 *  the करोcumentation करोesn't mention it.
			 */
			usleep_range(10000, 15000);

			dev_dbg(radio->dev, "%dkHz\n", radio->rx_frequency);

		पूर्ण अन्यथा अणु
			r = core->पढ़ो(core, WL1273_CHANL_SET, &freq);
			अगर (r)
				जाओ out;

			dev_dbg(radio->dev, "%dkHz\n", freq);
		पूर्ण
		dev_dbg(radio->dev, "%s: NOT BUSY\n", __func__);
	पूर्ण

out:
	core->ग_लिखो(core, WL1273_INT_MASK_SET, radio->irq_flags);
	complete(&radio->busy);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wl1273_fm_set_tx_freq(काष्ठा wl1273_device *radio, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r = 0;
	अचिन्हित दीर्घ t;

	अगर (freq < WL1273_BAND_TX_LOW) अणु
		dev_err(radio->dev,
			"Frequency out of range: %d < %d\n", freq,
			WL1273_BAND_TX_LOW);
		वापस -दुस्फल;
	पूर्ण

	अगर (freq > WL1273_BAND_TX_HIGH) अणु
		dev_err(radio->dev,
			"Frequency out of range: %d > %d\n", freq,
			WL1273_BAND_TX_HIGH);
		वापस -दुस्फल;
	पूर्ण

	/*
	 *  The driver works better with this sleep,
	 *  the करोcumentation करोesn't mention it.
	 */
	usleep_range(5000, 10000);

	dev_dbg(radio->dev, "%s: freq: %d kHz\n", __func__, freq);

	/* Set the current tx channel */
	r = core->ग_लिखो(core, WL1273_CHANL_SET, freq / 10);
	अगर (r)
		वापस r;

	reinit_completion(&radio->busy);

	/* रुको क्रम the FR IRQ */
	t = रुको_क्रम_completion_समयout(&radio->busy, msecs_to_jअगरfies(2000));
	अगर (!t)
		वापस -ETIMEDOUT;

	dev_dbg(radio->dev, "WL1273_CHANL_SET: %lu\n", t);

	/* Enable the output घातer */
	r = core->ग_लिखो(core, WL1273_POWER_ENB_SET, 1);
	अगर (r)
		वापस r;

	reinit_completion(&radio->busy);

	/* रुको क्रम the POWER_ENB IRQ */
	t = रुको_क्रम_completion_समयout(&radio->busy, msecs_to_jअगरfies(1000));
	अगर (!t)
		वापस -ETIMEDOUT;

	radio->tx_frequency = freq;
	dev_dbg(radio->dev, "WL1273_POWER_ENB_SET: %lu\n", t);

	वापस	0;
पूर्ण

अटल पूर्णांक wl1273_fm_set_rx_freq(काष्ठा wl1273_device *radio, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r, f;
	अचिन्हित दीर्घ t;

	अगर (freq < radio->rangelow) अणु
		dev_err(radio->dev,
			"Frequency out of range: %d < %d\n", freq,
			radio->rangelow);
		r = -दुस्फल;
		जाओ err;
	पूर्ण

	अगर (freq > radio->rangehigh) अणु
		dev_err(radio->dev,
			"Frequency out of range: %d > %d\n", freq,
			radio->rangehigh);
		r = -दुस्फल;
		जाओ err;
	पूर्ण

	dev_dbg(radio->dev, "%s: %dkHz\n", __func__, freq);

	core->ग_लिखो(core, WL1273_INT_MASK_SET, radio->irq_flags);

	अगर (radio->band == WL1273_BAND_JAPAN)
		f = (freq - WL1273_BAND_JAPAN_LOW) / 50;
	अन्यथा
		f = (freq - WL1273_BAND_OTHER_LOW) / 50;

	r = core->ग_लिखो(core, WL1273_FREQ_SET, f);
	अगर (r) अणु
		dev_err(radio->dev, "FREQ_SET fails\n");
		जाओ err;
	पूर्ण

	r = core->ग_लिखो(core, WL1273_TUNER_MODE_SET, TUNER_MODE_PRESET);
	अगर (r) अणु
		dev_err(radio->dev, "TUNER_MODE_SET fails\n");
		जाओ err;
	पूर्ण

	reinit_completion(&radio->busy);

	t = रुको_क्रम_completion_समयout(&radio->busy, msecs_to_jअगरfies(2000));
	अगर (!t) अणु
		dev_err(radio->dev, "%s: TIMEOUT\n", __func__);
		वापस -ETIMEDOUT;
	पूर्ण

	radio->rd_index = 0;
	radio->wr_index = 0;
	radio->rx_frequency = freq;
	वापस 0;
err:
	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_get_freq(काष्ठा wl1273_device *radio)
अणु
	काष्ठा wl1273_core *core = radio->core;
	अचिन्हित पूर्णांक freq;
	u16 f;
	पूर्णांक r;

	अगर (core->mode == WL1273_MODE_RX) अणु
		r = core->पढ़ो(core, WL1273_FREQ_SET, &f);
		अगर (r)
			वापस r;

		dev_dbg(radio->dev, "Freq get: 0x%04x\n", f);
		अगर (radio->band == WL1273_BAND_JAPAN)
			freq = WL1273_BAND_JAPAN_LOW + 50 * f;
		अन्यथा
			freq = WL1273_BAND_OTHER_LOW + 50 * f;
	पूर्ण अन्यथा अणु
		r = core->पढ़ो(core, WL1273_CHANL_SET, &f);
		अगर (r)
			वापस r;

		freq = f * 10;
	पूर्ण

	वापस freq;
पूर्ण

/**
 * wl1273_fm_upload_firmware_patch() -	Upload the firmware.
 * @radio:				A poपूर्णांकer to the device काष्ठा.
 *
 * The firmware file consists of arrays of bytes where the first byte
 * gives the array length. The first byte in the file gives the
 * number of these arrays.
 */
अटल पूर्णांक wl1273_fm_upload_firmware_patch(काष्ठा wl1273_device *radio)
अणु
	काष्ठा wl1273_core *core = radio->core;
	अचिन्हित पूर्णांक packet_num;
	स्थिर काष्ठा firmware *fw_p;
	स्थिर अक्षर *fw_name = "radio-wl1273-fw.bin";
	काष्ठा device *dev = radio->dev;
	__u8 *ptr;
	पूर्णांक r;

	dev_dbg(dev, "%s:\n", __func__);

	/*
	 * Uploading the firmware patch is not always necessary,
	 * so we only prपूर्णांक an info message.
	 */
	अगर (request_firmware(&fw_p, fw_name, dev)) अणु
		dev_info(dev, "%s - %s not found\n", __func__, fw_name);

		वापस 0;
	पूर्ण

	ptr = (__u8 *) fw_p->data;
	packet_num = ptr[0];
	dev_dbg(dev, "%s: packets: %d\n", __func__, packet_num);

	r = wl1273_fm_ग_लिखो_fw(core, ptr + 1, packet_num);
	अगर (r) अणु
		dev_err(dev, "FW upload error: %d\n", r);
		जाओ out;
	पूर्ण

	/* ignore possible error here */
	core->ग_लिखो(core, WL1273_RESET, 0);

	dev_dbg(dev, "%s - download OK, r: %d\n", __func__, r);
out:
	release_firmware(fw_p);
	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_stop(काष्ठा wl1273_device *radio)
अणु
	काष्ठा wl1273_core *core = radio->core;

	अगर (core->mode == WL1273_MODE_RX) अणु
		पूर्णांक r = core->ग_लिखो(core, WL1273_POWER_SET,
				    WL1273_POWER_SET_OFF);
		अगर (r)
			dev_err(radio->dev, "%s: POWER_SET fails: %d\n",
				__func__, r);
	पूर्ण अन्यथा अगर (core->mode == WL1273_MODE_TX) अणु
		पूर्णांक r = core->ग_लिखो(core, WL1273_PUPD_SET,
				    WL1273_PUPD_SET_OFF);
		अगर (r)
			dev_err(radio->dev,
				"%s: PUPD_SET fails: %d\n", __func__, r);
	पूर्ण

	अगर (core->pdata->disable) अणु
		core->pdata->disable();
		dev_dbg(radio->dev, "Back to reset\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl1273_fm_start(काष्ठा wl1273_device *radio, पूर्णांक new_mode)
अणु
	काष्ठा wl1273_core *core = radio->core;
	काष्ठा wl1273_fm_platक्रमm_data *pdata = core->pdata;
	काष्ठा device *dev = radio->dev;
	पूर्णांक r = -EINVAL;

	अगर (pdata->enable && core->mode == WL1273_MODE_OFF) अणु
		dev_dbg(radio->dev, "Out of reset\n");

		pdata->enable();
		msleep(250);
	पूर्ण

	अगर (new_mode == WL1273_MODE_RX) अणु
		u16 val = WL1273_POWER_SET_FM;

		अगर (radio->rds_on)
			val |= WL1273_POWER_SET_RDS;

		/* If this fails try again */
		r = core->ग_लिखो(core, WL1273_POWER_SET, val);
		अगर (r) अणु
			msleep(100);

			r = core->ग_लिखो(core, WL1273_POWER_SET, val);
			अगर (r) अणु
				dev_err(dev, "%s: POWER_SET fails\n", __func__);
				जाओ fail;
			पूर्ण
		पूर्ण

		/* rds buffer configuration */
		radio->wr_index = 0;
		radio->rd_index = 0;

	पूर्ण अन्यथा अगर (new_mode == WL1273_MODE_TX) अणु
		/* If this fails try again once */
		r = core->ग_लिखो(core, WL1273_PUPD_SET, WL1273_PUPD_SET_ON);
		अगर (r) अणु
			msleep(100);
			r = core->ग_लिखो(core, WL1273_PUPD_SET,
					WL1273_PUPD_SET_ON);
			अगर (r) अणु
				dev_err(dev, "%s: PUPD_SET fails\n", __func__);
				जाओ fail;
			पूर्ण
		पूर्ण

		अगर (radio->rds_on) अणु
			r = core->ग_लिखो(core, WL1273_RDS_DATA_ENB, 1);
			अगर (r) अणु
				dev_err(dev, "%s: RDS_DATA_ENB ON fails\n",
					__func__);
				जाओ fail;
			पूर्ण
		पूर्ण अन्यथा अणु
			r = core->ग_लिखो(core, WL1273_RDS_DATA_ENB, 0);
			अगर (r) अणु
				dev_err(dev, "%s: RDS_DATA_ENB OFF fails\n",
					__func__);
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(dev, "%s: Illegal mode.\n", __func__);
	पूर्ण

	अगर (core->mode == WL1273_MODE_OFF) अणु
		r = wl1273_fm_upload_firmware_patch(radio);
		अगर (r)
			dev_warn(dev, "Firmware upload failed.\n");

		/*
		 * Someबार the chip is in a wrong घातer state at this poपूर्णांक.
		 * So we set the घातer once again.
		 */
		अगर (new_mode == WL1273_MODE_RX) अणु
			u16 val = WL1273_POWER_SET_FM;

			अगर (radio->rds_on)
				val |= WL1273_POWER_SET_RDS;

			r = core->ग_लिखो(core, WL1273_POWER_SET, val);
			अगर (r) अणु
				dev_err(dev, "%s: POWER_SET fails\n", __func__);
				जाओ fail;
			पूर्ण
		पूर्ण अन्यथा अगर (new_mode == WL1273_MODE_TX) अणु
			r = core->ग_लिखो(core, WL1273_PUPD_SET,
					WL1273_PUPD_SET_ON);
			अगर (r) अणु
				dev_err(dev, "%s: PUPD_SET fails\n", __func__);
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
fail:
	अगर (pdata->disable)
		pdata->disable();

	dev_dbg(dev, "%s: return: %d\n", __func__, r);
	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_suspend(काष्ठा wl1273_device *radio)
अणु
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r;

	/* Cannot go from OFF to SUSPENDED */
	अगर (core->mode == WL1273_MODE_RX)
		r = core->ग_लिखो(core, WL1273_POWER_SET,
				WL1273_POWER_SET_RETENTION);
	अन्यथा अगर (core->mode == WL1273_MODE_TX)
		r = core->ग_लिखो(core, WL1273_PUPD_SET,
				WL1273_PUPD_SET_RETENTION);
	अन्यथा
		r = -EINVAL;

	अगर (r) अणु
		dev_err(radio->dev, "%s: POWER_SET fails: %d\n", __func__, r);
		जाओ out;
	पूर्ण

out:
	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_set_mode(काष्ठा wl1273_device *radio, पूर्णांक mode)
अणु
	काष्ठा wl1273_core *core = radio->core;
	काष्ठा device *dev = radio->dev;
	पूर्णांक old_mode;
	पूर्णांक r;

	dev_dbg(dev, "%s\n", __func__);
	dev_dbg(dev, "Forbidden modes: 0x%02x\n", radio->क्रमbidden);

	old_mode = core->mode;
	अगर (mode & radio->क्रमbidden) अणु
		r = -EPERM;
		जाओ out;
	पूर्ण

	चयन (mode) अणु
	हाल WL1273_MODE_RX:
	हाल WL1273_MODE_TX:
		r = wl1273_fm_start(radio, mode);
		अगर (r) अणु
			dev_err(dev, "%s: Cannot start.\n", __func__);
			wl1273_fm_stop(radio);
			जाओ out;
		पूर्ण

		core->mode = mode;
		r = core->ग_लिखो(core, WL1273_INT_MASK_SET, radio->irq_flags);
		अगर (r) अणु
			dev_err(dev, "INT_MASK_SET fails.\n");
			जाओ out;
		पूर्ण

		/* remember previous settings */
		अगर (mode == WL1273_MODE_RX) अणु
			r = wl1273_fm_set_rx_freq(radio, radio->rx_frequency);
			अगर (r) अणु
				dev_err(dev, "set freq fails: %d.\n", r);
				जाओ out;
			पूर्ण

			r = core->set_volume(core, core->volume);
			अगर (r) अणु
				dev_err(dev, "set volume fails: %d.\n", r);
				जाओ out;
			पूर्ण

			dev_dbg(dev, "%s: Set vol: %d.\n", __func__,
				core->volume);
		पूर्ण अन्यथा अणु
			r = wl1273_fm_set_tx_freq(radio, radio->tx_frequency);
			अगर (r) अणु
				dev_err(dev, "set freq fails: %d.\n", r);
				जाओ out;
			पूर्ण
		पूर्ण

		dev_dbg(radio->dev, "%s: Set audio mode.\n", __func__);

		r = core->set_audio(core, core->audio_mode);
		अगर (r)
			dev_err(dev, "Cannot set audio mode.\n");
		अवरोध;

	हाल WL1273_MODE_OFF:
		r = wl1273_fm_stop(radio);
		अगर (r)
			dev_err(dev, "%s: Off fails: %d\n", __func__, r);
		अन्यथा
			core->mode = WL1273_MODE_OFF;

		अवरोध;

	हाल WL1273_MODE_SUSPENDED:
		r = wl1273_fm_suspend(radio);
		अगर (r)
			dev_err(dev, "%s: Suspend fails: %d\n", __func__, r);
		अन्यथा
			core->mode = WL1273_MODE_SUSPENDED;

		अवरोध;

	शेष:
		dev_err(dev, "%s: Unknown mode: %d\n", __func__, mode);
		r = -EINVAL;
		अवरोध;
	पूर्ण
out:
	अगर (r)
		core->mode = old_mode;

	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_set_seek(काष्ठा wl1273_device *radio,
			      अचिन्हित पूर्णांक wrap_around,
			      अचिन्हित पूर्णांक seek_upward,
			      पूर्णांक level)
अणु
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r = 0;
	अचिन्हित पूर्णांक dir = (seek_upward == 0) ? 0 : 1;
	अचिन्हित पूर्णांक f;

	f = radio->rx_frequency;
	dev_dbg(radio->dev, "rx_frequency: %d\n", f);

	अगर (dir && f + radio->spacing <= radio->rangehigh)
		r = wl1273_fm_set_rx_freq(radio, f + radio->spacing);
	अन्यथा अगर (dir && wrap_around)
		r = wl1273_fm_set_rx_freq(radio, radio->rangelow);
	अन्यथा अगर (f - radio->spacing >= radio->rangelow)
		r = wl1273_fm_set_rx_freq(radio, f - radio->spacing);
	अन्यथा अगर (wrap_around)
		r = wl1273_fm_set_rx_freq(radio, radio->rangehigh);

	अगर (r)
		जाओ out;

	अगर (level < च_अक्षर_न्यून || level > च_अक्षर_उच्च)
		वापस -EINVAL;

	reinit_completion(&radio->busy);
	dev_dbg(radio->dev, "%s: BUSY\n", __func__);

	r = core->ग_लिखो(core, WL1273_INT_MASK_SET, radio->irq_flags);
	अगर (r)
		जाओ out;

	dev_dbg(radio->dev, "%s\n", __func__);

	r = core->ग_लिखो(core, WL1273_SEARCH_LVL_SET, level);
	अगर (r)
		जाओ out;

	r = core->ग_लिखो(core, WL1273_SEARCH_सूची_SET, dir);
	अगर (r)
		जाओ out;

	r = core->ग_लिखो(core, WL1273_TUNER_MODE_SET, TUNER_MODE_AUTO_SEEK);
	अगर (r)
		जाओ out;

	/* रुको क्रम the FR IRQ */
	रुको_क्रम_completion_समयout(&radio->busy, msecs_to_jअगरfies(1000));
	अगर (!(radio->irq_received & WL1273_BL_EVENT)) अणु
		r = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	radio->irq_received &= ~WL1273_BL_EVENT;

	अगर (!wrap_around)
		जाओ out;

	/* Wrap around */
	dev_dbg(radio->dev, "Wrap around in HW seek.\n");

	अगर (seek_upward)
		f = radio->rangelow;
	अन्यथा
		f = radio->rangehigh;

	r = wl1273_fm_set_rx_freq(radio, f);
	अगर (r)
		जाओ out;

	reinit_completion(&radio->busy);
	dev_dbg(radio->dev, "%s: BUSY\n", __func__);

	r = core->ग_लिखो(core, WL1273_TUNER_MODE_SET, TUNER_MODE_AUTO_SEEK);
	अगर (r)
		जाओ out;

	/* रुको क्रम the FR IRQ */
	अगर (!रुको_क्रम_completion_समयout(&radio->busy, msecs_to_jअगरfies(1000)))
		r = -ETIMEDOUT;
out:
	dev_dbg(radio->dev, "%s: Err: %d\n", __func__, r);
	वापस r;
पूर्ण

/**
 * wl1273_fm_get_tx_ctune() -	Get the TX tuning capacitor value.
 * @radio:			A poपूर्णांकer to the device काष्ठा.
 */
अटल अचिन्हित पूर्णांक wl1273_fm_get_tx_ctune(काष्ठा wl1273_device *radio)
अणु
	काष्ठा wl1273_core *core = radio->core;
	काष्ठा device *dev = radio->dev;
	u16 val;
	पूर्णांक r;

	अगर (core->mode == WL1273_MODE_OFF ||
	    core->mode == WL1273_MODE_SUSPENDED)
		वापस -EPERM;

	r = core->पढ़ो(core, WL1273_READ_FMANT_TUNE_VALUE, &val);
	अगर (r) अणु
		dev_err(dev, "%s: read error: %d\n", __func__, r);
		जाओ out;
	पूर्ण

out:
	वापस val;
पूर्ण

/**
 * wl1273_fm_set_preemphasis() - Set the TX pre-emphasis value.
 * @radio:			 A poपूर्णांकer to the device काष्ठा.
 * @preemphasis:		 The new pre-amphasis value.
 *
 * Possible pre-emphasis values are: V4L2_PREEMPHASIS_DISABLED,
 * V4L2_PREEMPHASIS_50_uS and V4L2_PREEMPHASIS_75_uS.
 */
अटल पूर्णांक wl1273_fm_set_preemphasis(काष्ठा wl1273_device *radio,
				     अचिन्हित पूर्णांक preemphasis)
अणु
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r;
	u16 em;

	अगर (core->mode == WL1273_MODE_OFF ||
	    core->mode == WL1273_MODE_SUSPENDED)
		वापस -EPERM;

	mutex_lock(&core->lock);

	चयन (preemphasis) अणु
	हाल V4L2_PREEMPHASIS_DISABLED:
		em = 1;
		अवरोध;
	हाल V4L2_PREEMPHASIS_50_uS:
		em = 0;
		अवरोध;
	हाल V4L2_PREEMPHASIS_75_uS:
		em = 2;
		अवरोध;
	शेष:
		r = -EINVAL;
		जाओ out;
	पूर्ण

	r = core->ग_लिखो(core, WL1273_PREMPH_SET, em);
	अगर (r)
		जाओ out;

	radio->preemphasis = preemphasis;

out:
	mutex_unlock(&core->lock);
	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_rds_on(काष्ठा wl1273_device *radio)
अणु
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r;

	dev_dbg(radio->dev, "%s\n", __func__);
	अगर (radio->rds_on)
		वापस 0;

	r = core->ग_लिखो(core, WL1273_POWER_SET,
			WL1273_POWER_SET_FM | WL1273_POWER_SET_RDS);
	अगर (r)
		जाओ out;

	r = wl1273_fm_set_rx_freq(radio, radio->rx_frequency);
	अगर (r)
		dev_err(radio->dev, "set freq fails: %d.\n", r);
out:
	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_rds_off(काष्ठा wl1273_device *radio)
अणु
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r;

	अगर (!radio->rds_on)
		वापस 0;

	radio->irq_flags &= ~WL1273_RDS_EVENT;

	r = core->ग_लिखो(core, WL1273_INT_MASK_SET, radio->irq_flags);
	अगर (r)
		जाओ out;

	/* Service pending पढ़ो */
	wake_up_पूर्णांकerruptible(&radio->पढ़ो_queue);

	dev_dbg(radio->dev, "%s\n", __func__);

	r = core->ग_लिखो(core, WL1273_POWER_SET, WL1273_POWER_SET_FM);
	अगर (r)
		जाओ out;

	r = wl1273_fm_set_rx_freq(radio, radio->rx_frequency);
	अगर (r)
		dev_err(radio->dev, "set freq fails: %d.\n", r);
out:
	dev_dbg(radio->dev, "%s: exiting...\n", __func__);

	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_set_rds(काष्ठा wl1273_device *radio, अचिन्हित पूर्णांक new_mode)
अणु
	पूर्णांक r = 0;
	काष्ठा wl1273_core *core = radio->core;

	अगर (core->mode == WL1273_MODE_OFF ||
	    core->mode == WL1273_MODE_SUSPENDED)
		वापस -EPERM;

	अगर (new_mode == WL1273_RDS_RESET) अणु
		r = core->ग_लिखो(core, WL1273_RDS_CNTRL_SET, 1);
		वापस r;
	पूर्ण

	अगर (core->mode == WL1273_MODE_TX && new_mode == WL1273_RDS_OFF) अणु
		r = core->ग_लिखो(core, WL1273_RDS_DATA_ENB, 0);
	पूर्ण अन्यथा अगर (core->mode == WL1273_MODE_TX && new_mode == WL1273_RDS_ON) अणु
		r = core->ग_लिखो(core, WL1273_RDS_DATA_ENB, 1);
	पूर्ण अन्यथा अगर (core->mode == WL1273_MODE_RX && new_mode == WL1273_RDS_OFF) अणु
		r = wl1273_fm_rds_off(radio);
	पूर्ण अन्यथा अगर (core->mode == WL1273_MODE_RX && new_mode == WL1273_RDS_ON) अणु
		r = wl1273_fm_rds_on(radio);
	पूर्ण अन्यथा अणु
		dev_err(radio->dev, "%s: Unknown mode: %d\n",
			__func__, new_mode);
		r = -EINVAL;
	पूर्ण

	अगर (!r)
		radio->rds_on = (new_mode == WL1273_RDS_ON) ? true : false;

	वापस r;
पूर्ण

अटल sमाप_प्रकार wl1273_fm_fops_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;
	u16 val;
	पूर्णांक r;

	dev_dbg(radio->dev, "%s\n", __func__);

	अगर (core->mode != WL1273_MODE_TX)
		वापस count;

	अगर (radio->rds_users == 0) अणु
		dev_warn(radio->dev, "%s: RDS not on.\n", __func__);
		वापस 0;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&core->lock))
		वापस -EINTR;
	/*
	 * Multiple processes can खोलो the device, but only
	 * one माला_लो to ग_लिखो to it.
	 */
	अगर (radio->owner && radio->owner != file) अणु
		r = -EBUSY;
		जाओ out;
	पूर्ण
	radio->owner = file;

	/* Manual Mode */
	अगर (count > 255)
		val = 255;
	अन्यथा
		val = count;

	core->ग_लिखो(core, WL1273_RDS_CONFIG_DATA_SET, val);

	अगर (copy_from_user(radio->ग_लिखो_buf + 1, buf, val)) अणु
		r = -EFAULT;
		जाओ out;
	पूर्ण

	dev_dbg(radio->dev, "Count: %d\n", val);
	dev_dbg(radio->dev, "From user: \"%s\"\n", radio->ग_लिखो_buf);

	radio->ग_लिखो_buf[0] = WL1273_RDS_DATA_SET;
	core->ग_लिखो_data(core, radio->ग_लिखो_buf, val + 1);

	r = val;
out:
	mutex_unlock(&core->lock);

	वापस r;
पूर्ण

अटल __poll_t wl1273_fm_fops_poll(काष्ठा file *file,
					काष्ठा poll_table_काष्ठा *pts)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;

	अगर (radio->owner && radio->owner != file)
		वापस EPOLLERR;

	radio->owner = file;

	अगर (core->mode == WL1273_MODE_RX) अणु
		poll_रुको(file, &radio->पढ़ो_queue, pts);

		अगर (radio->rd_index != radio->wr_index)
			वापस EPOLLIN | EPOLLRDNORM;

	पूर्ण अन्यथा अगर (core->mode == WL1273_MODE_TX) अणु
		वापस EPOLLOUT | EPOLLWRNORM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl1273_fm_fops_खोलो(काष्ठा file *file)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r = 0;

	dev_dbg(radio->dev, "%s\n", __func__);

	अगर (core->mode == WL1273_MODE_RX && radio->rds_on &&
	    !radio->rds_users) अणु
		dev_dbg(radio->dev, "%s: Mode: %d\n", __func__, core->mode);

		अगर (mutex_lock_पूर्णांकerruptible(&core->lock))
			वापस -EINTR;

		radio->irq_flags |= WL1273_RDS_EVENT;

		r = core->ग_लिखो(core, WL1273_INT_MASK_SET,
				radio->irq_flags);
		अगर (r) अणु
			mutex_unlock(&core->lock);
			जाओ out;
		पूर्ण

		radio->rds_users++;

		mutex_unlock(&core->lock);
	पूर्ण
out:
	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_fops_release(काष्ठा file *file)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r = 0;

	dev_dbg(radio->dev, "%s\n", __func__);

	अगर (radio->rds_users > 0) अणु
		radio->rds_users--;
		अगर (radio->rds_users == 0) अणु
			mutex_lock(&core->lock);

			radio->irq_flags &= ~WL1273_RDS_EVENT;

			अगर (core->mode == WL1273_MODE_RX) अणु
				r = core->ग_लिखो(core,
						WL1273_INT_MASK_SET,
						radio->irq_flags);
				अगर (r) अणु
					mutex_unlock(&core->lock);
					जाओ out;
				पूर्ण
			पूर्ण
			mutex_unlock(&core->lock);
		पूर्ण
	पूर्ण

	अगर (file == radio->owner)
		radio->owner = शून्य;
out:
	वापस r;
पूर्ण

अटल sमाप_प्रकार wl1273_fm_fops_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक r = 0;
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;
	अचिन्हित पूर्णांक block_count = 0;
	u16 val;

	dev_dbg(radio->dev, "%s\n", __func__);

	अगर (core->mode != WL1273_MODE_RX)
		वापस 0;

	अगर (radio->rds_users == 0) अणु
		dev_warn(radio->dev, "%s: RDS not on.\n", __func__);
		वापस 0;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&core->lock))
		वापस -EINTR;

	/*
	 * Multiple processes can खोलो the device, but only
	 * one at a समय माला_लो पढ़ो access.
	 */
	अगर (radio->owner && radio->owner != file) अणु
		r = -EBUSY;
		जाओ out;
	पूर्ण
	radio->owner = file;

	r = core->पढ़ो(core, WL1273_RDS_SYNC_GET, &val);
	अगर (r) अणु
		dev_err(radio->dev, "%s: Get RDS_SYNC fails.\n", __func__);
		जाओ out;
	पूर्ण अन्यथा अगर (val == 0) अणु
		dev_info(radio->dev, "RDS_SYNC: Not synchronized\n");
		r = -ENODATA;
		जाओ out;
	पूर्ण

	/* block अगर no new data available */
	जबतक (radio->wr_index == radio->rd_index) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			r = -EWOULDBLOCK;
			जाओ out;
		पूर्ण

		dev_dbg(radio->dev, "%s: Wait for RDS data.\n", __func__);
		अगर (रुको_event_पूर्णांकerruptible(radio->पढ़ो_queue,
					     radio->wr_index !=
					     radio->rd_index) < 0) अणु
			r = -EINTR;
			जाओ out;
		पूर्ण
	पूर्ण

	/* calculate block count from byte count */
	count /= RDS_BLOCK_SIZE;

	/* copy RDS blocks from the पूर्णांकernal buffer and to user buffer */
	जबतक (block_count < count) अणु
		अगर (radio->rd_index == radio->wr_index)
			अवरोध;

		/* always transfer complete RDS blocks */
		अगर (copy_to_user(buf, &radio->buffer[radio->rd_index],
				 RDS_BLOCK_SIZE))
			अवरोध;

		/* increment and wrap the पढ़ो poपूर्णांकer */
		radio->rd_index += RDS_BLOCK_SIZE;
		अगर (radio->rd_index >= radio->buf_size)
			radio->rd_index = 0;

		/* increment counters */
		block_count++;
		buf += RDS_BLOCK_SIZE;
		r += RDS_BLOCK_SIZE;
	पूर्ण

out:
	dev_dbg(radio->dev, "%s: exit\n", __func__);
	mutex_unlock(&core->lock);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations wl1273_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= wl1273_fm_fops_पढ़ो,
	.ग_लिखो		= wl1273_fm_fops_ग_लिखो,
	.poll		= wl1273_fm_fops_poll,
	.unlocked_ioctl	= video_ioctl2,
	.खोलो		= wl1273_fm_fops_खोलो,
	.release	= wl1273_fm_fops_release,
पूर्ण;

अटल पूर्णांक wl1273_fm_vidioc_querycap(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_capability *capability)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));

	dev_dbg(radio->dev, "%s\n", __func__);

	strscpy(capability->driver, WL1273_FM_DRIVER_NAME,
		माप(capability->driver));
	strscpy(capability->card, "Texas Instruments Wl1273 FM Radio",
		माप(capability->card));
	strscpy(capability->bus_info, radio->bus_type,
		माप(capability->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक wl1273_fm_vidioc_g_input(काष्ठा file *file, व्योम *priv,
				    अचिन्हित पूर्णांक *i)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));

	dev_dbg(radio->dev, "%s\n", __func__);

	*i = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक wl1273_fm_vidioc_s_input(काष्ठा file *file, व्योम *priv,
				    अचिन्हित पूर्णांक i)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));

	dev_dbg(radio->dev, "%s\n", __func__);

	अगर (i != 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * wl1273_fm_set_tx_घातer() -	Set the transmission घातer value.
 * @radio:			A poपूर्णांकer to the device काष्ठा.
 * @घातer:			The new घातer value.
 */
अटल पूर्णांक wl1273_fm_set_tx_घातer(काष्ठा wl1273_device *radio, u16 घातer)
अणु
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r;

	अगर (core->mode == WL1273_MODE_OFF ||
	    core->mode == WL1273_MODE_SUSPENDED)
		वापस -EPERM;

	mutex_lock(&core->lock);

	/* Convert the dBuV value to chip presentation */
	r = core->ग_लिखो(core, WL1273_POWER_LEV_SET, 122 - घातer);
	अगर (r)
		जाओ out;

	radio->tx_घातer = घातer;

out:
	mutex_unlock(&core->lock);
	वापस r;
पूर्ण

#घोषणा WL1273_SPACING_50kHz	1
#घोषणा WL1273_SPACING_100kHz	2
#घोषणा WL1273_SPACING_200kHz	4

अटल पूर्णांक wl1273_fm_tx_set_spacing(काष्ठा wl1273_device *radio,
				    अचिन्हित पूर्णांक spacing)
अणु
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r;

	अगर (spacing == 0) अणु
		r = core->ग_लिखो(core, WL1273_SCAN_SPACING_SET,
				WL1273_SPACING_100kHz);
		radio->spacing = 100;
	पूर्ण अन्यथा अगर (spacing - 50000 < 25000) अणु
		r = core->ग_लिखो(core, WL1273_SCAN_SPACING_SET,
				WL1273_SPACING_50kHz);
		radio->spacing = 50;
	पूर्ण अन्यथा अगर (spacing - 100000 < 50000) अणु
		r = core->ग_लिखो(core, WL1273_SCAN_SPACING_SET,
				WL1273_SPACING_100kHz);
		radio->spacing = 100;
	पूर्ण अन्यथा अणु
		r = core->ग_लिखो(core, WL1273_SCAN_SPACING_SET,
				WL1273_SPACING_200kHz);
		radio->spacing = 200;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा wl1273_device *radio = ctrl->priv;
	काष्ठा wl1273_core *core = radio->core;

	dev_dbg(radio->dev, "%s\n", __func__);

	अगर (mutex_lock_पूर्णांकerruptible(&core->lock))
		वापस -EINTR;

	चयन (ctrl->id) अणु
	हाल  V4L2_CID_TUNE_ANTENNA_CAPACITOR:
		ctrl->val = wl1273_fm_get_tx_ctune(radio);
		अवरोध;

	शेष:
		dev_warn(radio->dev, "%s: Unknown IOCTL: %d\n",
			 __func__, ctrl->id);
		अवरोध;
	पूर्ण

	mutex_unlock(&core->lock);

	वापस 0;
पूर्ण

#घोषणा WL1273_MUTE_SOFT_ENABLE    (1 << 0)
#घोषणा WL1273_MUTE_AC             (1 << 1)
#घोषणा WL1273_MUTE_HARD_LEFT      (1 << 2)
#घोषणा WL1273_MUTE_HARD_RIGHT     (1 << 3)
#घोषणा WL1273_MUTE_SOFT_FORCE     (1 << 4)

अटल अंतरभूत काष्ठा wl1273_device *to_radio(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस container_of(ctrl->handler, काष्ठा wl1273_device, ctrl_handler);
पूर्ण

अटल पूर्णांक wl1273_fm_vidioc_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा wl1273_device *radio = to_radio(ctrl);
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r = 0;

	dev_dbg(radio->dev, "%s\n", __func__);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		अगर (mutex_lock_पूर्णांकerruptible(&core->lock))
			वापस -EINTR;

		अगर (core->mode == WL1273_MODE_RX && ctrl->val)
			r = core->ग_लिखो(core,
					WL1273_MUTE_STATUS_SET,
					WL1273_MUTE_HARD_LEFT |
					WL1273_MUTE_HARD_RIGHT);
		अन्यथा अगर (core->mode == WL1273_MODE_RX)
			r = core->ग_लिखो(core,
					WL1273_MUTE_STATUS_SET, 0x0);
		अन्यथा अगर (core->mode == WL1273_MODE_TX && ctrl->val)
			r = core->ग_लिखो(core, WL1273_MUTE, 1);
		अन्यथा अगर (core->mode == WL1273_MODE_TX)
			r = core->ग_लिखो(core, WL1273_MUTE, 0);

		mutex_unlock(&core->lock);
		अवरोध;

	हाल V4L2_CID_AUDIO_VOLUME:
		अगर (ctrl->val == 0)
			r = wl1273_fm_set_mode(radio, WL1273_MODE_OFF);
		अन्यथा
			r =  core->set_volume(core, core->volume);
		अवरोध;

	हाल V4L2_CID_TUNE_PREEMPHASIS:
		r = wl1273_fm_set_preemphasis(radio, ctrl->val);
		अवरोध;

	हाल V4L2_CID_TUNE_POWER_LEVEL:
		r = wl1273_fm_set_tx_घातer(radio, ctrl->val);
		अवरोध;

	शेष:
		dev_warn(radio->dev, "%s: Unknown IOCTL: %d\n",
			 __func__, ctrl->id);
		अवरोध;
	पूर्ण

	dev_dbg(radio->dev, "%s\n", __func__);
	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_vidioc_g_audio(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_audio *audio)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));

	dev_dbg(radio->dev, "%s\n", __func__);

	अगर (audio->index > 1)
		वापस -EINVAL;

	strscpy(audio->name, "Radio", माप(audio->name));
	audio->capability = V4L2_AUDCAP_STEREO;

	वापस 0;
पूर्ण

अटल पूर्णांक wl1273_fm_vidioc_s_audio(काष्ठा file *file, व्योम *priv,
				    स्थिर काष्ठा v4l2_audio *audio)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));

	dev_dbg(radio->dev, "%s\n", __func__);

	अगर (audio->index != 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

#घोषणा WL1273_RDS_NOT_SYNCHRONIZED 0
#घोषणा WL1273_RDS_SYNCHRONIZED 1

अटल पूर्णांक wl1273_fm_vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_tuner *tuner)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;
	u16 val;
	पूर्णांक r;

	dev_dbg(radio->dev, "%s\n", __func__);

	अगर (tuner->index > 0)
		वापस -EINVAL;

	strscpy(tuner->name, WL1273_FM_DRIVER_NAME, माप(tuner->name));
	tuner->type = V4L2_TUNER_RADIO;

	tuner->rangelow	= WL1273_FREQ(WL1273_BAND_JAPAN_LOW);
	tuner->rangehigh = WL1273_FREQ(WL1273_BAND_OTHER_HIGH);

	tuner->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_RDS |
		V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_RDS_BLOCK_IO |
		V4L2_TUNER_CAP_HWSEEK_BOUNDED | V4L2_TUNER_CAP_HWSEEK_WRAP;

	अगर (radio->stereo)
		tuner->audmode = V4L2_TUNER_MODE_STEREO;
	अन्यथा
		tuner->audmode = V4L2_TUNER_MODE_MONO;

	अगर (core->mode != WL1273_MODE_RX)
		वापस 0;

	अगर (mutex_lock_पूर्णांकerruptible(&core->lock))
		वापस -EINTR;

	r = core->पढ़ो(core, WL1273_STEREO_GET, &val);
	अगर (r)
		जाओ out;

	अगर (val == 1)
		tuner->rxsubchans = V4L2_TUNER_SUB_STEREO;
	अन्यथा
		tuner->rxsubchans = V4L2_TUNER_SUB_MONO;

	r = core->पढ़ो(core, WL1273_RSSI_LVL_GET, &val);
	अगर (r)
		जाओ out;

	tuner->संकेत = (s16) val;
	dev_dbg(radio->dev, "Signal: %d\n", tuner->संकेत);

	tuner->afc = 0;

	r = core->पढ़ो(core, WL1273_RDS_SYNC_GET, &val);
	अगर (r)
		जाओ out;

	अगर (val == WL1273_RDS_SYNCHRONIZED)
		tuner->rxsubchans |= V4L2_TUNER_SUB_RDS;
out:
	mutex_unlock(&core->lock);

	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
				    स्थिर काष्ठा v4l2_tuner *tuner)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r = 0;

	dev_dbg(radio->dev, "%s\n", __func__);
	dev_dbg(radio->dev, "tuner->index: %d\n", tuner->index);
	dev_dbg(radio->dev, "tuner->name: %s\n", tuner->name);
	dev_dbg(radio->dev, "tuner->capability: 0x%04x\n", tuner->capability);
	dev_dbg(radio->dev, "tuner->rxsubchans: 0x%04x\n", tuner->rxsubchans);
	dev_dbg(radio->dev, "tuner->rangelow: %d\n", tuner->rangelow);
	dev_dbg(radio->dev, "tuner->rangehigh: %d\n", tuner->rangehigh);

	अगर (tuner->index > 0)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&core->lock))
		वापस -EINTR;

	r = wl1273_fm_set_mode(radio, WL1273_MODE_RX);
	अगर (r)
		जाओ out;

	अगर (tuner->rxsubchans & V4L2_TUNER_SUB_RDS)
		r = wl1273_fm_set_rds(radio, WL1273_RDS_ON);
	अन्यथा
		r = wl1273_fm_set_rds(radio, WL1273_RDS_OFF);

	अगर (r)
		dev_warn(radio->dev, "%s: RDS fails: %d\n", __func__, r);

	अगर (tuner->audmode == V4L2_TUNER_MODE_MONO) अणु
		r = core->ग_लिखो(core, WL1273_MOST_MODE_SET, WL1273_RX_MONO);
		अगर (r < 0) अणु
			dev_warn(radio->dev, "%s: MOST_MODE fails: %d\n",
				 __func__, r);
			जाओ out;
		पूर्ण
		radio->stereo = false;
	पूर्ण अन्यथा अगर (tuner->audmode == V4L2_TUNER_MODE_STEREO) अणु
		r = core->ग_लिखो(core, WL1273_MOST_MODE_SET, WL1273_RX_STEREO);
		अगर (r < 0) अणु
			dev_warn(radio->dev, "%s: MOST_MODE fails: %d\n",
				 __func__, r);
			जाओ out;
		पूर्ण
		radio->stereo = true;
	पूर्ण अन्यथा अणु
		dev_err(radio->dev, "%s: tuner->audmode: %d\n",
			 __func__, tuner->audmode);
		r = -EINVAL;
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&core->lock);

	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;

	dev_dbg(radio->dev, "%s\n", __func__);

	अगर (mutex_lock_पूर्णांकerruptible(&core->lock))
		वापस -EINTR;

	freq->type = V4L2_TUNER_RADIO;
	freq->frequency = WL1273_FREQ(wl1273_fm_get_freq(radio));

	mutex_unlock(&core->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक wl1273_fm_vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r;

	dev_dbg(radio->dev, "%s: %d\n", __func__, freq->frequency);

	अगर (freq->type != V4L2_TUNER_RADIO) अणु
		dev_dbg(radio->dev,
			"freq->type != V4L2_TUNER_RADIO: %d\n", freq->type);
		वापस -EINVAL;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&core->lock))
		वापस -EINTR;

	अगर (core->mode == WL1273_MODE_RX) अणु
		dev_dbg(radio->dev, "freq: %d\n", freq->frequency);

		r = wl1273_fm_set_rx_freq(radio,
					  WL1273_INV_FREQ(freq->frequency));
		अगर (r)
			dev_warn(radio->dev, WL1273_FM_DRIVER_NAME
				 ": set frequency failed with %d\n", r);
	पूर्ण अन्यथा अणु
		r = wl1273_fm_set_tx_freq(radio,
					  WL1273_INV_FREQ(freq->frequency));
		अगर (r)
			dev_warn(radio->dev, WL1273_FM_DRIVER_NAME
				 ": set frequency failed with %d\n", r);
	पूर्ण

	mutex_unlock(&core->lock);

	dev_dbg(radio->dev, "wl1273_vidioc_s_frequency: DONE\n");
	वापस r;
पूर्ण

#घोषणा WL1273_DEFAULT_SEEK_LEVEL	7

अटल पूर्णांक wl1273_fm_vidioc_s_hw_freq_seek(काष्ठा file *file, व्योम *priv,
					   स्थिर काष्ठा v4l2_hw_freq_seek *seek)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r;

	dev_dbg(radio->dev, "%s\n", __func__);

	अगर (seek->tuner != 0 || seek->type != V4L2_TUNER_RADIO)
		वापस -EINVAL;

	अगर (file->f_flags & O_NONBLOCK)
		वापस -EWOULDBLOCK;

	अगर (mutex_lock_पूर्णांकerruptible(&core->lock))
		वापस -EINTR;

	r = wl1273_fm_set_mode(radio, WL1273_MODE_RX);
	अगर (r)
		जाओ out;

	r = wl1273_fm_tx_set_spacing(radio, seek->spacing);
	अगर (r)
		dev_warn(radio->dev, "HW seek failed: %d\n", r);

	r = wl1273_fm_set_seek(radio, seek->wrap_around, seek->seek_upward,
			       WL1273_DEFAULT_SEEK_LEVEL);
	अगर (r)
		dev_warn(radio->dev, "HW seek failed: %d\n", r);

out:
	mutex_unlock(&core->lock);
	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_vidioc_s_modulator(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_modulator *modulator)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;
	पूर्णांक r = 0;

	dev_dbg(radio->dev, "%s\n", __func__);

	अगर (modulator->index > 0)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&core->lock))
		वापस -EINTR;

	r = wl1273_fm_set_mode(radio, WL1273_MODE_TX);
	अगर (r)
		जाओ out;

	अगर (modulator->txsubchans & V4L2_TUNER_SUB_RDS)
		r = wl1273_fm_set_rds(radio, WL1273_RDS_ON);
	अन्यथा
		r = wl1273_fm_set_rds(radio, WL1273_RDS_OFF);

	अगर (modulator->txsubchans & V4L2_TUNER_SUB_MONO)
		r = core->ग_लिखो(core, WL1273_MONO_SET, WL1273_TX_MONO);
	अन्यथा
		r = core->ग_लिखो(core, WL1273_MONO_SET,
				WL1273_RX_STEREO);
	अगर (r < 0)
		dev_warn(radio->dev, WL1273_FM_DRIVER_NAME
			 "MONO_SET fails: %d\n", r);
out:
	mutex_unlock(&core->lock);

	वापस r;
पूर्ण

अटल पूर्णांक wl1273_fm_vidioc_g_modulator(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_modulator *modulator)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;
	u16 val;
	पूर्णांक r;

	dev_dbg(radio->dev, "%s\n", __func__);

	strscpy(modulator->name, WL1273_FM_DRIVER_NAME,
		माप(modulator->name));

	modulator->rangelow = WL1273_FREQ(WL1273_BAND_JAPAN_LOW);
	modulator->rangehigh = WL1273_FREQ(WL1273_BAND_OTHER_HIGH);

	modulator->capability =  V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_RDS |
		V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_RDS_BLOCK_IO;

	अगर (core->mode != WL1273_MODE_TX)
		वापस 0;

	अगर (mutex_lock_पूर्णांकerruptible(&core->lock))
		वापस -EINTR;

	r = core->पढ़ो(core, WL1273_MONO_SET, &val);
	अगर (r)
		जाओ out;

	अगर (val == WL1273_TX_STEREO)
		modulator->txsubchans = V4L2_TUNER_SUB_STEREO;
	अन्यथा
		modulator->txsubchans = V4L2_TUNER_SUB_MONO;

	अगर (radio->rds_on)
		modulator->txsubchans |= V4L2_TUNER_SUB_RDS;
out:
	mutex_unlock(&core->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक wl1273_fm_vidioc_log_status(काष्ठा file *file, व्योम *priv)
अणु
	काष्ठा wl1273_device *radio = video_get_drvdata(video_devdata(file));
	काष्ठा wl1273_core *core = radio->core;
	काष्ठा device *dev = radio->dev;
	u16 val;
	पूर्णांक r;

	dev_info(dev, DRIVER_DESC);

	अगर (core->mode == WL1273_MODE_OFF) अणु
		dev_info(dev, "Mode: Off\n");
		वापस 0;
	पूर्ण

	अगर (core->mode == WL1273_MODE_SUSPENDED) अणु
		dev_info(dev, "Mode: Suspended\n");
		वापस 0;
	पूर्ण

	r = core->पढ़ो(core, WL1273_ASIC_ID_GET, &val);
	अगर (r)
		dev_err(dev, "%s: Get ASIC_ID fails.\n", __func__);
	अन्यथा
		dev_info(dev, "ASIC_ID: 0x%04x\n", val);

	r = core->पढ़ो(core, WL1273_ASIC_VER_GET, &val);
	अगर (r)
		dev_err(dev, "%s: Get ASIC_VER fails.\n", __func__);
	अन्यथा
		dev_info(dev, "ASIC Version: 0x%04x\n", val);

	r = core->पढ़ो(core, WL1273_FIRM_VER_GET, &val);
	अगर (r)
		dev_err(dev, "%s: Get FIRM_VER fails.\n", __func__);
	अन्यथा
		dev_info(dev, "FW version: %d(0x%04x)\n", val, val);

	r = core->पढ़ो(core, WL1273_BAND_SET, &val);
	अगर (r)
		dev_err(dev, "%s: Get BAND fails.\n", __func__);
	अन्यथा
		dev_info(dev, "BAND: %d\n", val);

	अगर (core->mode == WL1273_MODE_TX) अणु
		r = core->पढ़ो(core, WL1273_PUPD_SET, &val);
		अगर (r)
			dev_err(dev, "%s: Get PUPD fails.\n", __func__);
		अन्यथा
			dev_info(dev, "PUPD: 0x%04x\n", val);

		r = core->पढ़ो(core, WL1273_CHANL_SET, &val);
		अगर (r)
			dev_err(dev, "%s: Get CHANL fails.\n", __func__);
		अन्यथा
			dev_info(dev, "Tx frequency: %dkHz\n", val*10);
	पूर्ण अन्यथा अगर (core->mode == WL1273_MODE_RX) अणु
		पूर्णांक bf = radio->rangelow;

		r = core->पढ़ो(core, WL1273_FREQ_SET, &val);
		अगर (r)
			dev_err(dev, "%s: Get FREQ fails.\n", __func__);
		अन्यथा
			dev_info(dev, "RX Frequency: %dkHz\n", bf + val*50);

		r = core->पढ़ो(core, WL1273_MOST_MODE_SET, &val);
		अगर (r)
			dev_err(dev, "%s: Get MOST_MODE fails.\n",
				__func__);
		अन्यथा अगर (val == 0)
			dev_info(dev, "MOST_MODE: Stereo according to blend\n");
		अन्यथा अगर (val == 1)
			dev_info(dev, "MOST_MODE: Force mono output\n");
		अन्यथा
			dev_info(dev, "MOST_MODE: Unexpected value: %d\n", val);

		r = core->पढ़ो(core, WL1273_MOST_BLEND_SET, &val);
		अगर (r)
			dev_err(dev, "%s: Get MOST_BLEND fails.\n", __func__);
		अन्यथा अगर (val == 0)
			dev_info(dev,
				 "MOST_BLEND: Switched blend & hysteresis.\n");
		अन्यथा अगर (val == 1)
			dev_info(dev, "MOST_BLEND: Soft blend.\n");
		अन्यथा
			dev_info(dev, "MOST_BLEND: Unexpected val: %d\n", val);

		r = core->पढ़ो(core, WL1273_STEREO_GET, &val);
		अगर (r)
			dev_err(dev, "%s: Get STEREO fails.\n", __func__);
		अन्यथा अगर (val == 0)
			dev_info(dev, "STEREO: Not detected\n");
		अन्यथा अगर (val == 1)
			dev_info(dev, "STEREO: Detected\n");
		अन्यथा
			dev_info(dev, "STEREO: Unexpected value: %d\n", val);

		r = core->पढ़ो(core, WL1273_RSSI_LVL_GET, &val);
		अगर (r)
			dev_err(dev, "%s: Get RSSI_LVL fails.\n", __func__);
		अन्यथा
			dev_info(dev, "RX signal strength: %d\n", (s16) val);

		r = core->पढ़ो(core, WL1273_POWER_SET, &val);
		अगर (r)
			dev_err(dev, "%s: Get POWER fails.\n", __func__);
		अन्यथा
			dev_info(dev, "POWER: 0x%04x\n", val);

		r = core->पढ़ो(core, WL1273_INT_MASK_SET, &val);
		अगर (r)
			dev_err(dev, "%s: Get INT_MASK fails.\n", __func__);
		अन्यथा
			dev_info(dev, "INT_MASK: 0x%04x\n", val);

		r = core->पढ़ो(core, WL1273_RDS_SYNC_GET, &val);
		अगर (r)
			dev_err(dev, "%s: Get RDS_SYNC fails.\n",
				__func__);
		अन्यथा अगर (val == 0)
			dev_info(dev, "RDS_SYNC: Not synchronized\n");

		अन्यथा अगर (val == 1)
			dev_info(dev, "RDS_SYNC: Synchronized\n");
		अन्यथा
			dev_info(dev, "RDS_SYNC: Unexpected value: %d\n", val);

		r = core->पढ़ो(core, WL1273_I2S_MODE_CONFIG_SET, &val);
		अगर (r)
			dev_err(dev, "%s: Get I2S_MODE_CONFIG fails.\n",
				__func__);
		अन्यथा
			dev_info(dev, "I2S_MODE_CONFIG: 0x%04x\n", val);

		r = core->पढ़ो(core, WL1273_VOLUME_SET, &val);
		अगर (r)
			dev_err(dev, "%s: Get VOLUME fails.\n", __func__);
		अन्यथा
			dev_info(dev, "VOLUME: 0x%04x\n", val);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wl1273_vdev_release(काष्ठा video_device *dev)
अणु
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops wl1273_ctrl_ops = अणु
	.s_ctrl = wl1273_fm_vidioc_s_ctrl,
	.g_अस्थिर_ctrl = wl1273_fm_g_अस्थिर_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops wl1273_ioctl_ops = अणु
	.vidioc_querycap	= wl1273_fm_vidioc_querycap,
	.vidioc_g_input		= wl1273_fm_vidioc_g_input,
	.vidioc_s_input		= wl1273_fm_vidioc_s_input,
	.vidioc_g_audio		= wl1273_fm_vidioc_g_audio,
	.vidioc_s_audio		= wl1273_fm_vidioc_s_audio,
	.vidioc_g_tuner		= wl1273_fm_vidioc_g_tuner,
	.vidioc_s_tuner		= wl1273_fm_vidioc_s_tuner,
	.vidioc_g_frequency	= wl1273_fm_vidioc_g_frequency,
	.vidioc_s_frequency	= wl1273_fm_vidioc_s_frequency,
	.vidioc_s_hw_freq_seek	= wl1273_fm_vidioc_s_hw_freq_seek,
	.vidioc_g_modulator	= wl1273_fm_vidioc_g_modulator,
	.vidioc_s_modulator	= wl1273_fm_vidioc_s_modulator,
	.vidioc_log_status      = wl1273_fm_vidioc_log_status,
पूर्ण;

अटल स्थिर काष्ठा video_device wl1273_viddev_ढाँचा = अणु
	.fops			= &wl1273_fops,
	.ioctl_ops		= &wl1273_ioctl_ops,
	.name			= WL1273_FM_DRIVER_NAME,
	.release		= wl1273_vdev_release,
	.vfl_dir		= VFL_सूची_TX,
	.device_caps		= V4L2_CAP_HW_FREQ_SEEK | V4L2_CAP_TUNER |
				  V4L2_CAP_RADIO | V4L2_CAP_AUDIO |
				  V4L2_CAP_RDS_CAPTURE | V4L2_CAP_MODULATOR |
				  V4L2_CAP_RDS_OUTPUT,
पूर्ण;

अटल पूर्णांक wl1273_fm_radio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wl1273_device *radio = platक्रमm_get_drvdata(pdev);
	काष्ठा wl1273_core *core = radio->core;

	dev_info(&pdev->dev, "%s.\n", __func__);

	मुक्त_irq(core->client->irq, radio);
	core->pdata->मुक्त_resources();

	v4l2_ctrl_handler_मुक्त(&radio->ctrl_handler);
	video_unरेजिस्टर_device(&radio->videodev);
	v4l2_device_unरेजिस्टर(&radio->v4l2dev);

	वापस 0;
पूर्ण

अटल पूर्णांक wl1273_fm_radio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wl1273_core **core = pdev->dev.platक्रमm_data;
	काष्ठा wl1273_device *radio;
	काष्ठा v4l2_ctrl *ctrl;
	पूर्णांक r = 0;

	pr_debug("%s\n", __func__);

	अगर (!core) अणु
		dev_err(&pdev->dev, "No platform data.\n");
		r = -EINVAL;
		जाओ pdata_err;
	पूर्ण

	radio = devm_kzalloc(&pdev->dev, माप(*radio), GFP_KERNEL);
	अगर (!radio) अणु
		r = -ENOMEM;
		जाओ pdata_err;
	पूर्ण

	/* RDS buffer allocation */
	radio->buf_size = rds_buf * RDS_BLOCK_SIZE;
	radio->buffer = devm_kzalloc(&pdev->dev, radio->buf_size, GFP_KERNEL);
	अगर (!radio->buffer) अणु
		pr_err("Cannot allocate memory for RDS buffer.\n");
		r = -ENOMEM;
		जाओ pdata_err;
	पूर्ण

	radio->core = *core;
	radio->irq_flags = WL1273_IRQ_MASK;
	radio->dev = &radio->core->client->dev;
	radio->rds_on = false;
	radio->core->mode = WL1273_MODE_OFF;
	radio->tx_घातer = 118;
	radio->core->audio_mode = WL1273_AUDIO_ANALOG;
	radio->band = WL1273_BAND_OTHER;
	radio->core->i2s_mode = WL1273_I2S_DEF_MODE;
	radio->core->channel_number = 2;
	radio->core->volume = WL1273_DEFAULT_VOLUME;
	radio->rx_frequency = WL1273_BAND_OTHER_LOW;
	radio->tx_frequency = WL1273_BAND_OTHER_HIGH;
	radio->rangelow = WL1273_BAND_OTHER_LOW;
	radio->rangehigh = WL1273_BAND_OTHER_HIGH;
	radio->stereo = true;
	radio->bus_type = "I2C";

	अगर (radio->core->pdata->request_resources) अणु
		r = radio->core->pdata->request_resources(radio->core->client);
		अगर (r) अणु
			dev_err(radio->dev, WL1273_FM_DRIVER_NAME
				": Cannot get platform data\n");
			जाओ pdata_err;
		पूर्ण

		dev_dbg(radio->dev, "irq: %d\n", radio->core->client->irq);

		r = request_thपढ़ोed_irq(radio->core->client->irq, शून्य,
					 wl1273_fm_irq_thपढ़ो_handler,
					 IRQF_ONESHOT | IRQF_TRIGGER_FALLING,
					 "wl1273-fm", radio);
		अगर (r < 0) अणु
			dev_err(radio->dev, WL1273_FM_DRIVER_NAME
				": Unable to register IRQ handler: %d\n", r);
			जाओ err_request_irq;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(radio->dev, WL1273_FM_DRIVER_NAME ": Core WL1273 IRQ not configured");
		r = -EINVAL;
		जाओ pdata_err;
	पूर्ण

	init_completion(&radio->busy);
	init_रुकोqueue_head(&radio->पढ़ो_queue);

	radio->ग_लिखो_buf = devm_kzalloc(&pdev->dev, 256, GFP_KERNEL);
	अगर (!radio->ग_लिखो_buf) अणु
		r = -ENOMEM;
		जाओ ग_लिखो_buf_err;
	पूर्ण

	radio->dev = &pdev->dev;
	radio->v4l2dev.ctrl_handler = &radio->ctrl_handler;
	radio->rds_users = 0;

	r = v4l2_device_रेजिस्टर(&pdev->dev, &radio->v4l2dev);
	अगर (r) अणु
		dev_err(&pdev->dev, "Cannot register v4l2_device.\n");
		जाओ ग_लिखो_buf_err;
	पूर्ण

	/* V4L2 configuration */
	radio->videodev = wl1273_viddev_ढाँचा;

	radio->videodev.v4l2_dev = &radio->v4l2dev;

	v4l2_ctrl_handler_init(&radio->ctrl_handler, 6);

	/* add in ascending ID order */
	v4l2_ctrl_new_std(&radio->ctrl_handler, &wl1273_ctrl_ops,
			  V4L2_CID_AUDIO_VOLUME, 0, WL1273_MAX_VOLUME, 1,
			  WL1273_DEFAULT_VOLUME);

	v4l2_ctrl_new_std(&radio->ctrl_handler, &wl1273_ctrl_ops,
			  V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);

	v4l2_ctrl_new_std_menu(&radio->ctrl_handler, &wl1273_ctrl_ops,
			       V4L2_CID_TUNE_PREEMPHASIS,
			       V4L2_PREEMPHASIS_75_uS, 0x03,
			       V4L2_PREEMPHASIS_50_uS);

	v4l2_ctrl_new_std(&radio->ctrl_handler, &wl1273_ctrl_ops,
			  V4L2_CID_TUNE_POWER_LEVEL, 91, 122, 1, 118);

	ctrl = v4l2_ctrl_new_std(&radio->ctrl_handler, &wl1273_ctrl_ops,
				 V4L2_CID_TUNE_ANTENNA_CAPACITOR,
				 0, 255, 1, 255);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	अगर (radio->ctrl_handler.error) अणु
		r = radio->ctrl_handler.error;
		dev_err(&pdev->dev, "Ctrl handler error: %d\n", r);
		जाओ handler_init_err;
	पूर्ण

	video_set_drvdata(&radio->videodev, radio);
	platक्रमm_set_drvdata(pdev, radio);

	/* रेजिस्टर video device */
	r = video_रेजिस्टर_device(&radio->videodev, VFL_TYPE_RADIO, radio_nr);
	अगर (r) अणु
		dev_err(&pdev->dev, WL1273_FM_DRIVER_NAME
			": Could not register video device\n");
		जाओ handler_init_err;
	पूर्ण

	वापस 0;

handler_init_err:
	v4l2_ctrl_handler_मुक्त(&radio->ctrl_handler);
	v4l2_device_unरेजिस्टर(&radio->v4l2dev);
ग_लिखो_buf_err:
	मुक्त_irq(radio->core->client->irq, radio);
err_request_irq:
	radio->core->pdata->मुक्त_resources();
pdata_err:
	वापस r;
पूर्ण

अटल काष्ठा platक्रमm_driver wl1273_fm_radio_driver = अणु
	.probe		= wl1273_fm_radio_probe,
	.हटाओ		= wl1273_fm_radio_हटाओ,
	.driver		= अणु
		.name	= "wl1273_fm_radio",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wl1273_fm_radio_driver);

MODULE_AUTHOR("Matti Aaltonen <matti.j.aaltonen@nokia.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wl1273_fm_radio");
