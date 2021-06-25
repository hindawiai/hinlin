<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/******************************************************************************
 *  speedtch.c  -  Alcatel SpeedTouch USB xDSL modem driver
 *
 *  Copyright (C) 2001, Alcatel
 *  Copyright (C) 2003, Duncan Sands
 *  Copyright (C) 2004, David Woodhouse
 *
 *  Based on "modem_run.c", copyright (C) 2001, Benoit Papillault
 ******************************************************************************/

#समावेश <यंत्र/page.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/workqueue.h>

#समावेश "usbatm.h"

#घोषणा DRIVER_AUTHOR	"Johan Verrept, Duncan Sands <duncan.sands@free.fr>"
#घोषणा DRIVER_DESC	"Alcatel SpeedTouch USB driver"

अटल स्थिर अक्षर speedtch_driver_name[] = "speedtch";

#घोषणा CTRL_TIMEOUT 2000	/* milliseconds */
#घोषणा DATA_TIMEOUT 2000	/* milliseconds */

#घोषणा OFFSET_7	0		/* size 1 */
#घोषणा OFFSET_b	1		/* size 8 */
#घोषणा OFFSET_d	9		/* size 4 */
#घोषणा OFFSET_e	13		/* size 1 */
#घोषणा OFFSET_f	14		/* size 1 */

#घोषणा SIZE_7		1
#घोषणा SIZE_b		8
#घोषणा SIZE_d		4
#घोषणा SIZE_e		1
#घोषणा SIZE_f		1

#घोषणा MIN_POLL_DELAY		5000	/* milliseconds */
#घोषणा MAX_POLL_DELAY		60000	/* milliseconds */

#घोषणा RESUBMIT_DELAY		1000	/* milliseconds */

#घोषणा DEFAULT_BULK_ALTSETTING	1
#घोषणा DEFAULT_ISOC_ALTSETTING	3
#घोषणा DEFAULT_DL_512_FIRST	0
#घोषणा DEFAULT_ENABLE_ISOC	0
#घोषणा DEFAULT_SW_BUFFERING	0

अटल अचिन्हित पूर्णांक altsetting = 0; /* zero means: use the शेष */
अटल bool dl_512_first = DEFAULT_DL_512_FIRST;
अटल bool enable_isoc = DEFAULT_ENABLE_ISOC;
अटल bool sw_buffering = DEFAULT_SW_BUFFERING;

#घोषणा DEFAULT_B_MAX_DSL	8128
#घोषणा DEFAULT_MODEM_MODE	11
#घोषणा MODEM_OPTION_LENGTH	16
अटल स्थिर अचिन्हित अक्षर DEFAULT_MODEM_OPTION[MODEM_OPTION_LENGTH] = अणु
	0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

अटल अचिन्हित पूर्णांक BMaxDSL = DEFAULT_B_MAX_DSL;
अटल अचिन्हित अक्षर ModemMode = DEFAULT_MODEM_MODE;
अटल अचिन्हित अक्षर ModemOption[MODEM_OPTION_LENGTH];
अटल अचिन्हित पूर्णांक num_ModemOption;

module_param(altsetting, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(altsetting,
		"Alternative setting for data interface (bulk_default: "
		__MODULE_STRING(DEFAULT_BULK_ALTSETTING) "; isoc_default: "
		__MODULE_STRING(DEFAULT_ISOC_ALTSETTING) ")");

module_param(dl_512_first, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dl_512_first,
		 "Read 512 bytes before sending firmware (default: "
		 __MODULE_STRING(DEFAULT_DL_512_FIRST) ")");

module_param(enable_isoc, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(enable_isoc,
		"Use isochronous transfers if available (default: "
		__MODULE_STRING(DEFAULT_ENABLE_ISOC) ")");

module_param(sw_buffering, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(sw_buffering,
		 "Enable software buffering (default: "
		 __MODULE_STRING(DEFAULT_SW_BUFFERING) ")");

module_param(BMaxDSL, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(BMaxDSL,
		"default: " __MODULE_STRING(DEFAULT_B_MAX_DSL));

module_param(ModemMode, byte, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ModemMode,
		"default: " __MODULE_STRING(DEFAULT_MODEM_MODE));

module_param_array(ModemOption, byte, &num_ModemOption, S_IRUGO);
MODULE_PARM_DESC(ModemOption, "default: 0x10,0x00,0x00,0x00,0x20");

#घोषणा INTERFACE_DATA		1
#घोषणा ENDPOINT_INT		0x81
#घोषणा ENDPOINT_BULK_DATA	0x07
#घोषणा ENDPOINT_ISOC_DATA	0x07
#घोषणा ENDPOINT_FIRMWARE	0x05

काष्ठा speedtch_params अणु
	अचिन्हित पूर्णांक altsetting;
	अचिन्हित पूर्णांक BMaxDSL;
	अचिन्हित अक्षर ModemMode;
	अचिन्हित अक्षर ModemOption[MODEM_OPTION_LENGTH];
पूर्ण;

काष्ठा speedtch_instance_data अणु
	काष्ठा usbaपंचांग_data *usbaपंचांग;

	काष्ठा speedtch_params params; /* set in probe, स्थिरant afterwards */

	काष्ठा समयr_list status_check_समयr;
	काष्ठा work_काष्ठा status_check_work;

	अचिन्हित अक्षर last_status;

	पूर्णांक poll_delay; /* milliseconds */

	काष्ठा समयr_list resubmit_समयr;
	काष्ठा urb *पूर्णांक_urb;
	अचिन्हित अक्षर पूर्णांक_data[16];

	अचिन्हित अक्षर scratch_buffer[16];
पूर्ण;

/***************
**  firmware  **
***************/

अटल व्योम speedtch_set_swbuff(काष्ठा speedtch_instance_data *instance, पूर्णांक state)
अणु
	काष्ठा usbaपंचांग_data *usbaपंचांग = instance->usbaपंचांग;
	काष्ठा usb_device *usb_dev = usbaपंचांग->usb_dev;
	पूर्णांक ret;

	ret = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			      0x32, 0x40, state ? 0x01 : 0x00, 0x00, शून्य, 0, CTRL_TIMEOUT);
	अगर (ret < 0)
		usb_warn(usbaपंचांग,
			 "%sabling SW buffering: usb_control_msg returned %d\n",
			 state ? "En" : "Dis", ret);
	अन्यथा
		usb_dbg(usbaपंचांग, "speedtch_set_swbuff: %sbled SW buffering\n", state ? "En" : "Dis");
पूर्ण

अटल व्योम speedtch_test_sequence(काष्ठा speedtch_instance_data *instance)
अणु
	काष्ठा usbaपंचांग_data *usbaपंचांग = instance->usbaपंचांग;
	काष्ठा usb_device *usb_dev = usbaपंचांग->usb_dev;
	अचिन्हित अक्षर *buf = instance->scratch_buffer;
	पूर्णांक ret;

	/* URB 147 */
	buf[0] = 0x1c;
	buf[1] = 0x50;
	ret = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			      0x01, 0x40, 0x0b, 0x00, buf, 2, CTRL_TIMEOUT);
	अगर (ret < 0)
		usb_warn(usbaपंचांग, "%s failed on URB147: %d\n", __func__, ret);

	/* URB 148 */
	buf[0] = 0x32;
	buf[1] = 0x00;
	ret = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			      0x01, 0x40, 0x02, 0x00, buf, 2, CTRL_TIMEOUT);
	अगर (ret < 0)
		usb_warn(usbaपंचांग, "%s failed on URB148: %d\n", __func__, ret);

	/* URB 149 */
	buf[0] = 0x01;
	buf[1] = 0x00;
	buf[2] = 0x01;
	ret = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			      0x01, 0x40, 0x03, 0x00, buf, 3, CTRL_TIMEOUT);
	अगर (ret < 0)
		usb_warn(usbaपंचांग, "%s failed on URB149: %d\n", __func__, ret);

	/* URB 150 */
	buf[0] = 0x01;
	buf[1] = 0x00;
	buf[2] = 0x01;
	ret = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			      0x01, 0x40, 0x04, 0x00, buf, 3, CTRL_TIMEOUT);
	अगर (ret < 0)
		usb_warn(usbaपंचांग, "%s failed on URB150: %d\n", __func__, ret);

	/* Extra initialisation in recent drivers - gives higher speeds */

	/* URBext1 */
	buf[0] = instance->params.ModemMode;
	ret = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			      0x01, 0x40, 0x11, 0x00, buf, 1, CTRL_TIMEOUT);
	अगर (ret < 0)
		usb_warn(usbaपंचांग, "%s failed on URBext1: %d\n", __func__, ret);

	/* URBext2 */
	/* This seems to be the one which actually triggers the higher sync
	   rate -- it करोes require the new firmware too, although it works OK
	   with older firmware */
	ret = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			      0x01, 0x40, 0x14, 0x00,
			      instance->params.ModemOption,
			      MODEM_OPTION_LENGTH, CTRL_TIMEOUT);
	अगर (ret < 0)
		usb_warn(usbaपंचांग, "%s failed on URBext2: %d\n", __func__, ret);

	/* URBext3 */
	buf[0] = instance->params.BMaxDSL & 0xff;
	buf[1] = instance->params.BMaxDSL >> 8;
	ret = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			      0x01, 0x40, 0x12, 0x00, buf, 2, CTRL_TIMEOUT);
	अगर (ret < 0)
		usb_warn(usbaपंचांग, "%s failed on URBext3: %d\n", __func__, ret);
पूर्ण

अटल पूर्णांक speedtch_upload_firmware(काष्ठा speedtch_instance_data *instance,
				     स्थिर काष्ठा firmware *fw1,
				     स्थिर काष्ठा firmware *fw2)
अणु
	अचिन्हित अक्षर *buffer;
	काष्ठा usbaपंचांग_data *usbaपंचांग = instance->usbaपंचांग;
	काष्ठा usb_device *usb_dev = usbaपंचांग->usb_dev;
	पूर्णांक actual_length;
	पूर्णांक ret = 0;
	पूर्णांक offset;

	usb_dbg(usbaपंचांग, "%s entered\n", __func__);

	buffer = (अचिन्हित अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!buffer) अणु
		ret = -ENOMEM;
		usb_dbg(usbaपंचांग, "%s: no memory for buffer!\n", __func__);
		जाओ out;
	पूर्ण

	अगर (!usb_अगरnum_to_अगर(usb_dev, 2)) अणु
		ret = -ENODEV;
		usb_dbg(usbaपंचांग, "%s: interface not found!\n", __func__);
		जाओ out_मुक्त;
	पूर्ण

	/* URB 7 */
	अगर (dl_512_first) अणु	/* some modems need a पढ़ो beक्रमe writing the firmware */
		ret = usb_bulk_msg(usb_dev, usb_rcvbulkpipe(usb_dev, ENDPOINT_FIRMWARE),
				   buffer, 0x200, &actual_length, 2000);

		अगर (ret < 0 && ret != -ETIMEDOUT)
			usb_warn(usbaपंचांग, "%s: read BLOCK0 from modem failed (%d)!\n", __func__, ret);
		अन्यथा
			usb_dbg(usbaपंचांग, "%s: BLOCK0 downloaded (%d bytes)\n", __func__, ret);
	पूर्ण

	/* URB 8 : both leds are अटल green */
	क्रम (offset = 0; offset < fw1->size; offset += PAGE_SIZE) अणु
		पूर्णांक thislen = min_t(पूर्णांक, PAGE_SIZE, fw1->size - offset);
		स_नकल(buffer, fw1->data + offset, thislen);

		ret = usb_bulk_msg(usb_dev, usb_sndbulkpipe(usb_dev, ENDPOINT_FIRMWARE),
				   buffer, thislen, &actual_length, DATA_TIMEOUT);

		अगर (ret < 0) अणु
			usb_err(usbaपंचांग, "%s: write BLOCK1 to modem failed (%d)!\n", __func__, ret);
			जाओ out_मुक्त;
		पूर्ण
		usb_dbg(usbaपंचांग, "%s: BLOCK1 uploaded (%zu bytes)\n", __func__, fw1->size);
	पूर्ण

	/* USB led blinking green, ADSL led off */

	/* URB 11 */
	ret = usb_bulk_msg(usb_dev, usb_rcvbulkpipe(usb_dev, ENDPOINT_FIRMWARE),
			   buffer, 0x200, &actual_length, DATA_TIMEOUT);

	अगर (ret < 0) अणु
		usb_err(usbaपंचांग, "%s: read BLOCK2 from modem failed (%d)!\n", __func__, ret);
		जाओ out_मुक्त;
	पूर्ण
	usb_dbg(usbaपंचांग, "%s: BLOCK2 downloaded (%d bytes)\n", __func__, actual_length);

	/* URBs 12 to 139 - USB led blinking green, ADSL led off */
	क्रम (offset = 0; offset < fw2->size; offset += PAGE_SIZE) अणु
		पूर्णांक thislen = min_t(पूर्णांक, PAGE_SIZE, fw2->size - offset);
		स_नकल(buffer, fw2->data + offset, thislen);

		ret = usb_bulk_msg(usb_dev, usb_sndbulkpipe(usb_dev, ENDPOINT_FIRMWARE),
				   buffer, thislen, &actual_length, DATA_TIMEOUT);

		अगर (ret < 0) अणु
			usb_err(usbaपंचांग, "%s: write BLOCK3 to modem failed (%d)!\n", __func__, ret);
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण
	usb_dbg(usbaपंचांग, "%s: BLOCK3 uploaded (%zu bytes)\n", __func__, fw2->size);

	/* USB led अटल green, ADSL led अटल red */

	/* URB 142 */
	ret = usb_bulk_msg(usb_dev, usb_rcvbulkpipe(usb_dev, ENDPOINT_FIRMWARE),
			   buffer, 0x200, &actual_length, DATA_TIMEOUT);

	अगर (ret < 0) अणु
		usb_err(usbaपंचांग, "%s: read BLOCK4 from modem failed (%d)!\n", __func__, ret);
		जाओ out_मुक्त;
	पूर्ण

	/* success */
	usb_dbg(usbaपंचांग, "%s: BLOCK4 downloaded (%d bytes)\n", __func__, actual_length);

	/* Delay to allow firmware to start up. We can करो this here
	   because we're in our own kernel thपढ़ो anyway. */
	msleep_पूर्णांकerruptible(1000);

	अगर ((ret = usb_set_पूर्णांकerface(usb_dev, INTERFACE_DATA, instance->params.altsetting)) < 0) अणु
		usb_err(usbaपंचांग, "%s: setting interface to %d failed (%d)!\n", __func__, instance->params.altsetting, ret);
		जाओ out_मुक्त;
	पूर्ण

	/* Enable software buffering, अगर requested */
	अगर (sw_buffering)
		speedtch_set_swbuff(instance, 1);

	/* Magic spell; करोn't ask us what this करोes */
	speedtch_test_sequence(instance);

	ret = 0;

out_मुक्त:
	मुक्त_page((अचिन्हित दीर्घ)buffer);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक speedtch_find_firmware(काष्ठा usbaपंचांग_data *usbaपंचांग, काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				  पूर्णांक phase, स्थिर काष्ठा firmware **fw_p)
अणु
	काष्ठा device *dev = &पूर्णांकf->dev;
	स्थिर u16 bcdDevice = le16_to_cpu(पूर्णांकerface_to_usbdev(पूर्णांकf)->descriptor.bcdDevice);
	स्थिर u8 major_revision = bcdDevice >> 8;
	स्थिर u8 minor_revision = bcdDevice & 0xff;
	अक्षर buf[24];

	प्र_लिखो(buf, "speedtch-%d.bin.%x.%02x", phase, major_revision, minor_revision);
	usb_dbg(usbaपंचांग, "%s: looking for %s\n", __func__, buf);

	अगर (request_firmware(fw_p, buf, dev)) अणु
		प्र_लिखो(buf, "speedtch-%d.bin.%x", phase, major_revision);
		usb_dbg(usbaपंचांग, "%s: looking for %s\n", __func__, buf);

		अगर (request_firmware(fw_p, buf, dev)) अणु
			प्र_लिखो(buf, "speedtch-%d.bin", phase);
			usb_dbg(usbaपंचांग, "%s: looking for %s\n", __func__, buf);

			अगर (request_firmware(fw_p, buf, dev)) अणु
				usb_err(usbaपंचांग, "%s: no stage %d firmware found!\n", __func__, phase);
				वापस -ENOENT;
			पूर्ण
		पूर्ण
	पूर्ण

	usb_info(usbaपंचांग, "found stage %d firmware %s\n", phase, buf);

	वापस 0;
पूर्ण

अटल पूर्णांक speedtch_heavy_init(काष्ठा usbaपंचांग_data *usbaपंचांग, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	स्थिर काष्ठा firmware *fw1, *fw2;
	काष्ठा speedtch_instance_data *instance = usbaपंचांग->driver_data;
	पूर्णांक ret;

	अगर ((ret = speedtch_find_firmware(usbaपंचांग, पूर्णांकf, 1, &fw1)) < 0)
		वापस ret;

	अगर ((ret = speedtch_find_firmware(usbaपंचांग, पूर्णांकf, 2, &fw2)) < 0) अणु
		release_firmware(fw1);
		वापस ret;
	पूर्ण

	अगर ((ret = speedtch_upload_firmware(instance, fw1, fw2)) < 0)
		usb_err(usbaपंचांग, "%s: firmware upload failed (%d)!\n", __func__, ret);

	release_firmware(fw2);
	release_firmware(fw1);

	वापस ret;
पूर्ण


/**********
**  ATM  **
**********/

अटल पूर्णांक speedtch_पढ़ो_status(काष्ठा speedtch_instance_data *instance)
अणु
	काष्ठा usbaपंचांग_data *usbaपंचांग = instance->usbaपंचांग;
	काष्ठा usb_device *usb_dev = usbaपंचांग->usb_dev;
	अचिन्हित अक्षर *buf = instance->scratch_buffer;
	पूर्णांक ret;

	स_रखो(buf, 0, 16);

	ret = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			      0x12, 0xc0, 0x07, 0x00, buf + OFFSET_7, SIZE_7,
			      CTRL_TIMEOUT);
	अगर (ret < 0) अणु
		aपंचांग_dbg(usbaपंचांग, "%s: MSG 7 failed\n", __func__);
		वापस ret;
	पूर्ण

	ret = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			      0x12, 0xc0, 0x0b, 0x00, buf + OFFSET_b, SIZE_b,
			      CTRL_TIMEOUT);
	अगर (ret < 0) अणु
		aपंचांग_dbg(usbaपंचांग, "%s: MSG B failed\n", __func__);
		वापस ret;
	पूर्ण

	ret = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			      0x12, 0xc0, 0x0d, 0x00, buf + OFFSET_d, SIZE_d,
			      CTRL_TIMEOUT);
	अगर (ret < 0) अणु
		aपंचांग_dbg(usbaपंचांग, "%s: MSG D failed\n", __func__);
		वापस ret;
	पूर्ण

	ret = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			      0x01, 0xc0, 0x0e, 0x00, buf + OFFSET_e, SIZE_e,
			      CTRL_TIMEOUT);
	अगर (ret < 0) अणु
		aपंचांग_dbg(usbaपंचांग, "%s: MSG E failed\n", __func__);
		वापस ret;
	पूर्ण

	ret = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			      0x01, 0xc0, 0x0f, 0x00, buf + OFFSET_f, SIZE_f,
			      CTRL_TIMEOUT);
	अगर (ret < 0) अणु
		aपंचांग_dbg(usbaपंचांग, "%s: MSG F failed\n", __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक speedtch_start_synchro(काष्ठा speedtch_instance_data *instance)
अणु
	काष्ठा usbaपंचांग_data *usbaपंचांग = instance->usbaपंचांग;
	काष्ठा usb_device *usb_dev = usbaपंचांग->usb_dev;
	अचिन्हित अक्षर *buf = instance->scratch_buffer;
	पूर्णांक ret;

	aपंचांग_dbg(usbaपंचांग, "%s entered\n", __func__);

	स_रखो(buf, 0, 2);

	ret = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			      0x12, 0xc0, 0x04, 0x00,
			      buf, 2, CTRL_TIMEOUT);

	अगर (ret < 0)
		aपंचांग_warn(usbaपंचांग, "failed to start ADSL synchronisation: %d\n", ret);
	अन्यथा
		aपंचांग_dbg(usbaपंचांग, "%s: modem prodded. %d bytes returned: %02x %02x\n",
			__func__, ret, buf[0], buf[1]);

	वापस ret;
पूर्ण

अटल व्योम speedtch_check_status(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा speedtch_instance_data *instance =
		container_of(work, काष्ठा speedtch_instance_data,
			     status_check_work);
	काष्ठा usbaपंचांग_data *usbaपंचांग = instance->usbaपंचांग;
	काष्ठा aपंचांग_dev *aपंचांग_dev = usbaपंचांग->aपंचांग_dev;
	अचिन्हित अक्षर *buf = instance->scratch_buffer;
	पूर्णांक करोwn_speed, up_speed, ret;
	अचिन्हित अक्षर status;

#अगर_घोषित VERBOSE_DEBUG
	aपंचांग_dbg(usbaपंचांग, "%s entered\n", __func__);
#पूर्ण_अगर

	ret = speedtch_पढ़ो_status(instance);
	अगर (ret < 0) अणु
		aपंचांग_warn(usbaपंचांग, "error %d fetching device status\n", ret);
		instance->poll_delay = min(2 * instance->poll_delay, MAX_POLL_DELAY);
		वापस;
	पूर्ण

	instance->poll_delay = max(instance->poll_delay / 2, MIN_POLL_DELAY);

	status = buf[OFFSET_7];

	अगर ((status != instance->last_status) || !status) अणु
		aपंचांग_dbg(usbaपंचांग, "%s: line state 0x%02x\n", __func__, status);

		चयन (status) अणु
		हाल 0:
			aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_LOST);
			अगर (instance->last_status)
				aपंचांग_info(usbaपंचांग, "ADSL line is down\n");
			/* It may never resync again unless we ask it to... */
			ret = speedtch_start_synchro(instance);
			अवरोध;

		हाल 0x08:
			aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_UNKNOWN);
			aपंचांग_info(usbaपंचांग, "ADSL line is blocked?\n");
			अवरोध;

		हाल 0x10:
			aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_LOST);
			aपंचांग_info(usbaपंचांग, "ADSL line is synchronising\n");
			अवरोध;

		हाल 0x20:
			करोwn_speed = buf[OFFSET_b] | (buf[OFFSET_b + 1] << 8)
				| (buf[OFFSET_b + 2] << 16) | (buf[OFFSET_b + 3] << 24);
			up_speed = buf[OFFSET_b + 4] | (buf[OFFSET_b + 5] << 8)
				| (buf[OFFSET_b + 6] << 16) | (buf[OFFSET_b + 7] << 24);

			अगर (!(करोwn_speed & 0x0000ffff) && !(up_speed & 0x0000ffff)) अणु
				करोwn_speed >>= 16;
				up_speed >>= 16;
			पूर्ण

			aपंचांग_dev->link_rate = करोwn_speed * 1000 / 424;
			aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_FOUND);

			aपंचांग_info(usbaपंचांग,
				 "ADSL line is up (%d kb/s down | %d kb/s up)\n",
				 करोwn_speed, up_speed);
			अवरोध;

		शेष:
			aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_UNKNOWN);
			aपंचांग_info(usbaपंचांग, "unknown line state %02x\n", status);
			अवरोध;
		पूर्ण

		instance->last_status = status;
	पूर्ण
पूर्ण

अटल व्योम speedtch_status_poll(काष्ठा समयr_list *t)
अणु
	काष्ठा speedtch_instance_data *instance = from_समयr(instance, t,
						             status_check_समयr);

	schedule_work(&instance->status_check_work);

	/* The following check is racy, but the race is harmless */
	अगर (instance->poll_delay < MAX_POLL_DELAY)
		mod_समयr(&instance->status_check_समयr, jअगरfies + msecs_to_jअगरfies(instance->poll_delay));
	अन्यथा
		aपंचांग_warn(instance->usbaपंचांग, "Too many failures - disabling line status polling\n");
पूर्ण

अटल व्योम speedtch_resubmit_पूर्णांक(काष्ठा समयr_list *t)
अणु
	काष्ठा speedtch_instance_data *instance = from_समयr(instance, t,
							     resubmit_समयr);
	काष्ठा urb *पूर्णांक_urb = instance->पूर्णांक_urb;
	पूर्णांक ret;

	aपंचांग_dbg(instance->usbaपंचांग, "%s entered\n", __func__);

	अगर (पूर्णांक_urb) अणु
		ret = usb_submit_urb(पूर्णांक_urb, GFP_ATOMIC);
		अगर (!ret)
			schedule_work(&instance->status_check_work);
		अन्यथा अणु
			aपंचांग_dbg(instance->usbaपंचांग, "%s: usb_submit_urb failed with result %d\n", __func__, ret);
			mod_समयr(&instance->resubmit_समयr, jअगरfies + msecs_to_jअगरfies(RESUBMIT_DELAY));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम speedtch_handle_पूर्णांक(काष्ठा urb *पूर्णांक_urb)
अणु
	काष्ठा speedtch_instance_data *instance = पूर्णांक_urb->context;
	काष्ठा usbaपंचांग_data *usbaपंचांग = instance->usbaपंचांग;
	अचिन्हित पूर्णांक count = पूर्णांक_urb->actual_length;
	पूर्णांक status = पूर्णांक_urb->status;
	पूर्णांक ret;

	/* The magic पूर्णांकerrupt क्रम "up state" */
	अटल स्थिर अचिन्हित अक्षर up_पूर्णांक[6]   = अणु 0xa1, 0x00, 0x01, 0x00, 0x00, 0x00 पूर्ण;
	/* The magic पूर्णांकerrupt क्रम "down state" */
	अटल स्थिर अचिन्हित अक्षर करोwn_पूर्णांक[6] = अणु 0xa1, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;

	aपंचांग_dbg(usbaपंचांग, "%s entered\n", __func__);

	अगर (status < 0) अणु
		aपंचांग_dbg(usbaपंचांग, "%s: nonzero urb status %d!\n", __func__, status);
		जाओ fail;
	पूर्ण

	अगर ((count == 6) && !स_भेद(up_पूर्णांक, instance->पूर्णांक_data, 6)) अणु
		del_समयr(&instance->status_check_समयr);
		aपंचांग_info(usbaपंचांग, "DSL line goes up\n");
	पूर्ण अन्यथा अगर ((count == 6) && !स_भेद(करोwn_पूर्णांक, instance->पूर्णांक_data, 6)) अणु
		aपंचांग_info(usbaपंचांग, "DSL line goes down\n");
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		aपंचांग_dbg(usbaपंचांग, "%s: unknown interrupt packet of length %d:", __func__, count);
		क्रम (i = 0; i < count; i++)
			prपूर्णांकk(" %02x", instance->पूर्णांक_data[i]);
		prपूर्णांकk("\n");
		जाओ fail;
	पूर्ण

	पूर्णांक_urb = instance->पूर्णांक_urb;
	अगर (पूर्णांक_urb) अणु
		ret = usb_submit_urb(पूर्णांक_urb, GFP_ATOMIC);
		schedule_work(&instance->status_check_work);
		अगर (ret < 0) अणु
			aपंचांग_dbg(usbaपंचांग, "%s: usb_submit_urb failed with result %d\n", __func__, ret);
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस;

fail:
	पूर्णांक_urb = instance->पूर्णांक_urb;
	अगर (पूर्णांक_urb)
		mod_समयr(&instance->resubmit_समयr, jअगरfies + msecs_to_jअगरfies(RESUBMIT_DELAY));
पूर्ण

अटल पूर्णांक speedtch_aपंचांग_start(काष्ठा usbaपंचांग_data *usbaपंचांग, काष्ठा aपंचांग_dev *aपंचांग_dev)
अणु
	काष्ठा usb_device *usb_dev = usbaपंचांग->usb_dev;
	काष्ठा speedtch_instance_data *instance = usbaपंचांग->driver_data;
	पूर्णांक i, ret;
	अचिन्हित अक्षर mac_str[13];

	aपंचांग_dbg(usbaपंचांग, "%s entered\n", __func__);

	/* Set MAC address, it is stored in the serial number */
	स_रखो(aपंचांग_dev->esi, 0, माप(aपंचांग_dev->esi));
	अगर (usb_string(usb_dev, usb_dev->descriptor.iSerialNumber, mac_str, माप(mac_str)) == 12) अणु
		क्रम (i = 0; i < 6; i++)
			aपंचांग_dev->esi[i] = (hex_to_bin(mac_str[i * 2]) << 4) +
				hex_to_bin(mac_str[i * 2 + 1]);
	पूर्ण

	/* Start modem synchronisation */
	ret = speedtch_start_synchro(instance);

	/* Set up पूर्णांकerrupt endpoपूर्णांक */
	अगर (instance->पूर्णांक_urb) अणु
		ret = usb_submit_urb(instance->पूर्णांक_urb, GFP_KERNEL);
		अगर (ret < 0) अणु
			/* Doesn't matter; we'll poll anyway */
			aपंचांग_dbg(usbaपंचांग, "%s: submission of interrupt URB failed (%d)!\n", __func__, ret);
			usb_मुक्त_urb(instance->पूर्णांक_urb);
			instance->पूर्णांक_urb = शून्य;
		पूर्ण
	पूर्ण

	/* Start status polling */
	mod_समयr(&instance->status_check_समयr, jअगरfies + msecs_to_jअगरfies(1000));

	वापस 0;
पूर्ण

अटल व्योम speedtch_aपंचांग_stop(काष्ठा usbaपंचांग_data *usbaपंचांग, काष्ठा aपंचांग_dev *aपंचांग_dev)
अणु
	काष्ठा speedtch_instance_data *instance = usbaपंचांग->driver_data;
	काष्ठा urb *पूर्णांक_urb = instance->पूर्णांक_urb;

	aपंचांग_dbg(usbaपंचांग, "%s entered\n", __func__);

	del_समयr_sync(&instance->status_check_समयr);

	/*
	 * Since resubmit_समयr and पूर्णांक_urb can schedule themselves and
	 * each other, shutting them करोwn correctly takes some care
	 */
	instance->पूर्णांक_urb = शून्य; /* संकेत shutकरोwn */
	mb();
	usb_समाप्त_urb(पूर्णांक_urb);
	del_समयr_sync(&instance->resubmit_समयr);
	/*
	 * At this poपूर्णांक, speedtch_handle_पूर्णांक and speedtch_resubmit_पूर्णांक
	 * can run or be running, but instance->पूर्णांक_urb == शून्य means that
	 * they will not reschedule
	 */
	usb_समाप्त_urb(पूर्णांक_urb);
	del_समयr_sync(&instance->resubmit_समयr);
	usb_मुक्त_urb(पूर्णांक_urb);

	flush_work(&instance->status_check_work);
पूर्ण

अटल पूर्णांक speedtch_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक speedtch_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
पूर्ण


/**********
**  USB  **
**********/

अटल स्थिर काष्ठा usb_device_id speedtch_usb_ids[] = अणु
	अणुUSB_DEVICE(0x06b9, 0x4061)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, speedtch_usb_ids);

अटल पूर्णांक speedtch_usb_probe(काष्ठा usb_पूर्णांकerface *, स्थिर काष्ठा usb_device_id *);

अटल काष्ठा usb_driver speedtch_usb_driver = अणु
	.name		= speedtch_driver_name,
	.probe		= speedtch_usb_probe,
	.disconnect	= usbaपंचांग_usb_disconnect,
	.pre_reset	= speedtch_pre_reset,
	.post_reset	= speedtch_post_reset,
	.id_table	= speedtch_usb_ids
पूर्ण;

अटल व्योम speedtch_release_पूर्णांकerfaces(काष्ठा usb_device *usb_dev,
					पूर्णांक num_पूर्णांकerfaces)
अणु
	काष्ठा usb_पूर्णांकerface *cur_पूर्णांकf;
	पूर्णांक i;

	क्रम (i = 0; i < num_पूर्णांकerfaces; i++) अणु
		cur_पूर्णांकf = usb_अगरnum_to_अगर(usb_dev, i);
		अगर (cur_पूर्णांकf) अणु
			usb_set_पूर्णांकfdata(cur_पूर्णांकf, शून्य);
			usb_driver_release_पूर्णांकerface(&speedtch_usb_driver, cur_पूर्णांकf);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक speedtch_bind(काष्ठा usbaपंचांग_data *usbaपंचांग,
			 काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_पूर्णांकerface *cur_पूर्णांकf, *data_पूर्णांकf;
	काष्ठा speedtch_instance_data *instance;
	पूर्णांक अगरnum = पूर्णांकf->altsetting->desc.bInterfaceNumber;
	पूर्णांक num_पूर्णांकerfaces = usb_dev->actconfig->desc.bNumInterfaces;
	पूर्णांक i, ret;
	पूर्णांक use_isoc;

	usb_dbg(usbaपंचांग, "%s entered\n", __func__);

	/* sanity checks */

	अगर (usb_dev->descriptor.bDeviceClass != USB_CLASS_VENDOR_SPEC) अणु
		usb_err(usbaपंचांग, "%s: wrong device class %d\n", __func__, usb_dev->descriptor.bDeviceClass);
		वापस -ENODEV;
	पूर्ण

	data_पूर्णांकf = usb_अगरnum_to_अगर(usb_dev, INTERFACE_DATA);
	अगर (!data_पूर्णांकf) अणु
		usb_err(usbaपंचांग, "%s: data interface not found!\n", __func__);
		वापस -ENODEV;
	पूर्ण

	/* claim all पूर्णांकerfaces */

	क्रम (i = 0; i < num_पूर्णांकerfaces; i++) अणु
		cur_पूर्णांकf = usb_अगरnum_to_अगर(usb_dev, i);

		अगर ((i != अगरnum) && cur_पूर्णांकf) अणु
			ret = usb_driver_claim_पूर्णांकerface(&speedtch_usb_driver, cur_पूर्णांकf, usbaपंचांग);

			अगर (ret < 0) अणु
				usb_err(usbaपंचांग, "%s: failed to claim interface %2d (%d)!\n", __func__, i, ret);
				speedtch_release_पूर्णांकerfaces(usb_dev, i);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	instance = kzalloc(माप(*instance), GFP_KERNEL);

	अगर (!instance) अणु
		ret = -ENOMEM;
		जाओ fail_release;
	पूर्ण

	instance->usbaपंचांग = usbaपंचांग;

	/* module parameters may change at any moment, so take a snapshot */
	instance->params.altsetting = altsetting;
	instance->params.BMaxDSL = BMaxDSL;
	instance->params.ModemMode = ModemMode;
	स_नकल(instance->params.ModemOption, DEFAULT_MODEM_OPTION, MODEM_OPTION_LENGTH);
	स_नकल(instance->params.ModemOption, ModemOption, num_ModemOption);
	use_isoc = enable_isoc;

	अगर (instance->params.altsetting)
		अगर ((ret = usb_set_पूर्णांकerface(usb_dev, INTERFACE_DATA, instance->params.altsetting)) < 0) अणु
			usb_err(usbaपंचांग, "%s: setting interface to %2d failed (%d)!\n", __func__, instance->params.altsetting, ret);
			instance->params.altsetting = 0; /* fall back to शेष */
		पूर्ण

	अगर (!instance->params.altsetting && use_isoc)
		अगर ((ret = usb_set_पूर्णांकerface(usb_dev, INTERFACE_DATA, DEFAULT_ISOC_ALTSETTING)) < 0) अणु
			usb_dbg(usbaपंचांग, "%s: setting interface to %2d failed (%d)!\n", __func__, DEFAULT_ISOC_ALTSETTING, ret);
			use_isoc = 0; /* fall back to bulk */
		पूर्ण

	अगर (use_isoc) अणु
		स्थिर काष्ठा usb_host_पूर्णांकerface *desc = data_पूर्णांकf->cur_altsetting;
		स्थिर __u8 target_address = USB_सूची_IN | usbaपंचांग->driver->isoc_in;

		use_isoc = 0; /* fall back to bulk अगर endpoपूर्णांक not found */

		क्रम (i = 0; i < desc->desc.bNumEndpoपूर्णांकs; i++) अणु
			स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक_desc = &desc->endpoपूर्णांक[i].desc;

			अगर ((endpoपूर्णांक_desc->bEndpoपूर्णांकAddress == target_address)) अणु
				use_isoc =
					usb_endpoपूर्णांक_xfer_isoc(endpoपूर्णांक_desc);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!use_isoc)
			usb_info(usbaपंचांग, "isochronous transfer not supported - using bulk\n");
	पूर्ण

	अगर (!use_isoc && !instance->params.altsetting)
		अगर ((ret = usb_set_पूर्णांकerface(usb_dev, INTERFACE_DATA, DEFAULT_BULK_ALTSETTING)) < 0) अणु
			usb_err(usbaपंचांग, "%s: setting interface to %2d failed (%d)!\n", __func__, DEFAULT_BULK_ALTSETTING, ret);
			जाओ fail_मुक्त;
		पूर्ण

	अगर (!instance->params.altsetting)
		instance->params.altsetting = use_isoc ? DEFAULT_ISOC_ALTSETTING : DEFAULT_BULK_ALTSETTING;

	usbaपंचांग->flags |= (use_isoc ? UDSL_USE_ISOC : 0);

	INIT_WORK(&instance->status_check_work, speedtch_check_status);
	समयr_setup(&instance->status_check_समयr, speedtch_status_poll, 0);
	instance->last_status = 0xff;
	instance->poll_delay = MIN_POLL_DELAY;

	समयr_setup(&instance->resubmit_समयr, speedtch_resubmit_पूर्णांक, 0);

	instance->पूर्णांक_urb = usb_alloc_urb(0, GFP_KERNEL);

	अगर (instance->पूर्णांक_urb)
		usb_fill_पूर्णांक_urb(instance->पूर्णांक_urb, usb_dev,
				 usb_rcvपूर्णांकpipe(usb_dev, ENDPOINT_INT),
				 instance->पूर्णांक_data, माप(instance->पूर्णांक_data),
				 speedtch_handle_पूर्णांक, instance, 16);
	अन्यथा
		usb_dbg(usbaपंचांग, "%s: no memory for interrupt urb!\n", __func__);

	/* check whether the modem alपढ़ोy seems to be alive */
	ret = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			      0x12, 0xc0, 0x07, 0x00,
			      instance->scratch_buffer + OFFSET_7, SIZE_7, 500);

	usbaपंचांग->flags |= (ret == SIZE_7 ? UDSL_SKIP_HEAVY_INIT : 0);

	usb_dbg(usbaपंचांग, "%s: firmware %s loaded\n", __func__, usbaपंचांग->flags & UDSL_SKIP_HEAVY_INIT ? "already" : "not");

	अगर (!(usbaपंचांग->flags & UDSL_SKIP_HEAVY_INIT))
		अगर ((ret = usb_reset_device(usb_dev)) < 0) अणु
			usb_err(usbaपंचांग, "%s: device reset failed (%d)!\n", __func__, ret);
			जाओ fail_मुक्त;
		पूर्ण

        usbaपंचांग->driver_data = instance;

	वापस 0;

fail_मुक्त:
	usb_मुक्त_urb(instance->पूर्णांक_urb);
	kमुक्त(instance);
fail_release:
	speedtch_release_पूर्णांकerfaces(usb_dev, num_पूर्णांकerfaces);
	वापस ret;
पूर्ण

अटल व्योम speedtch_unbind(काष्ठा usbaपंचांग_data *usbaपंचांग, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा speedtch_instance_data *instance = usbaपंचांग->driver_data;

	usb_dbg(usbaपंचांग, "%s entered\n", __func__);

	speedtch_release_पूर्णांकerfaces(usb_dev, usb_dev->actconfig->desc.bNumInterfaces);
	usb_मुक्त_urb(instance->पूर्णांक_urb);
	kमुक्त(instance);
पूर्ण


/***********
**  init  **
***********/

अटल काष्ठा usbaपंचांग_driver speedtch_usbaपंचांग_driver = अणु
	.driver_name	= speedtch_driver_name,
	.bind		= speedtch_bind,
	.heavy_init	= speedtch_heavy_init,
	.unbind		= speedtch_unbind,
	.aपंचांग_start	= speedtch_aपंचांग_start,
	.aपंचांग_stop	= speedtch_aपंचांग_stop,
	.bulk_in	= ENDPOINT_BULK_DATA,
	.bulk_out	= ENDPOINT_BULK_DATA,
	.isoc_in	= ENDPOINT_ISOC_DATA
पूर्ण;

अटल पूर्णांक speedtch_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	वापस usbaपंचांग_usb_probe(पूर्णांकf, id, &speedtch_usbaपंचांग_driver);
पूर्ण

module_usb_driver(speedtch_usb_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
