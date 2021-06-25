<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2016 Masaki Ota <masaki.ota@jp.alps.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "hid-ids.h"

/* ALPS Device Product ID */
#घोषणा HID_PRODUCT_ID_T3_BTNLESS	0xD0C0
#घोषणा HID_PRODUCT_ID_COSMO		0x1202
#घोषणा HID_PRODUCT_ID_U1_PTP_1		0x1207
#घोषणा HID_PRODUCT_ID_U1			0x1209
#घोषणा HID_PRODUCT_ID_U1_PTP_2		0x120A
#घोषणा HID_PRODUCT_ID_U1_DUAL		0x120B
#घोषणा HID_PRODUCT_ID_T4_BTNLESS	0x120C

#घोषणा DEV_SINGLEPOINT				0x01
#घोषणा DEV_DUALPOINT				0x02

#घोषणा U1_MOUSE_REPORT_ID			0x01 /* Mouse data ReportID */
#घोषणा U1_ABSOLUTE_REPORT_ID		0x03 /* Absolute data ReportID */
#घोषणा U1_ABSOLUTE_REPORT_ID_SECD  0x02 /* FW-PTP Absolute data ReportID */
#घोषणा U1_FEATURE_REPORT_ID		0x05 /* Feature ReportID */
#घोषणा U1_SP_ABSOLUTE_REPORT_ID	0x06 /* Feature ReportID */

#घोषणा U1_FEATURE_REPORT_LEN		0x08 /* Feature Report Length */
#घोषणा U1_FEATURE_REPORT_LEN_ALL	0x0A
#घोषणा U1_CMD_REGISTER_READ		0xD1
#घोषणा U1_CMD_REGISTER_WRITE		0xD2

#घोषणा	U1_DEVTYPE_SP_SUPPORT		0x10 /* SP Support */
#घोषणा	U1_DISABLE_DEV				0x01
#घोषणा U1_TP_ABS_MODE				0x02
#घोषणा	U1_SP_ABS_MODE				0x80

#घोषणा ADDRESS_U1_DEV_CTRL_1	0x00800040
#घोषणा ADDRESS_U1_DEVICE_TYP	0x00800043
#घोषणा ADDRESS_U1_NUM_SENS_X	0x00800047
#घोषणा ADDRESS_U1_NUM_SENS_Y	0x00800048
#घोषणा ADDRESS_U1_PITCH_SENS_X	0x00800049
#घोषणा ADDRESS_U1_PITCH_SENS_Y	0x0080004A
#घोषणा ADDRESS_U1_RESO_DWN_ABS 0x0080004E
#घोषणा ADDRESS_U1_PAD_BTN		0x00800052
#घोषणा ADDRESS_U1_SP_BTN		0x0080009F

#घोषणा T4_INPUT_REPORT_LEN			माप(काष्ठा t4_input_report)
#घोषणा T4_FEATURE_REPORT_LEN		T4_INPUT_REPORT_LEN
#घोषणा T4_FEATURE_REPORT_ID		7
#घोषणा T4_CMD_REGISTER_READ			0x08
#घोषणा T4_CMD_REGISTER_WRITE			0x07

#घोषणा T4_ADDRESS_BASE				0xC2C0
#घोषणा PRM_SYS_CONFIG_1			(T4_ADDRESS_BASE + 0x0002)
#घोषणा T4_PRM_FEED_CONFIG_1		(T4_ADDRESS_BASE + 0x0004)
#घोषणा T4_PRM_FEED_CONFIG_4		(T4_ADDRESS_BASE + 0x001A)
#घोषणा T4_PRM_ID_CONFIG_3			(T4_ADDRESS_BASE + 0x00B0)


#घोषणा T4_FEEDCFG4_ADVANCED_ABS_ENABLE			0x01
#घोषणा T4_I2C_ABS	0x78

#घोषणा T4_COUNT_PER_ELECTRODE		256
#घोषणा MAX_TOUCHES	5

क्रमागत dev_num अणु
	U1,
	T4,
	UNKNOWN,
पूर्ण;
/**
 * काष्ठा alps_dev
 *
 * @input: poपूर्णांकer to the kernel input device
 * @input2: poपूर्णांकer to the kernel input2 device
 * @hdev: poपूर्णांकer to the काष्ठा hid_device
 *
 * @dev_type: device type
 * @max_fingers: total number of fingers
 * @has_sp: boolean of sp existense
 * @sp_btn_info: button inक्रमmation
 * @x_active_len_mm: active area length of X (mm)
 * @y_active_len_mm: active area length of Y (mm)
 * @x_max: maximum x coordinate value
 * @y_max: maximum y coordinate value
 * @x_min: minimum x coordinate value
 * @y_min: minimum y coordinate value
 * @btn_cnt: number of buttons
 * @sp_btn_cnt: number of stick buttons
 */
काष्ठा alps_dev अणु
	काष्ठा input_dev *input;
	काष्ठा input_dev *input2;
	काष्ठा hid_device *hdev;

	क्रमागत dev_num dev_type;
	u8  max_fingers;
	u8  has_sp;
	u8	sp_btn_info;
	u32	x_active_len_mm;
	u32	y_active_len_mm;
	u32	x_max;
	u32	y_max;
	u32	x_min;
	u32	y_min;
	u32	btn_cnt;
	u32	sp_btn_cnt;
पूर्ण;

काष्ठा t4_contact_data अणु
	u8  palm;
	u8	x_lo;
	u8	x_hi;
	u8	y_lo;
	u8	y_hi;
पूर्ण;

काष्ठा t4_input_report अणु
	u8  reportID;
	u8  numContacts;
	काष्ठा t4_contact_data contact[5];
	u8  button;
	u8  track[5];
	u8  zx[5], zy[5];
	u8  palmTime[5];
	u8  kilroy;
	u16 समयStamp;
पूर्ण;

अटल u16 t4_calc_check_sum(u8 *buffer,
		अचिन्हित दीर्घ offset, अचिन्हित दीर्घ length)
अणु
	u16 sum1 = 0xFF, sum2 = 0xFF;
	अचिन्हित दीर्घ i = 0;

	अगर (offset + length >= 50)
		वापस 0;

	जबतक (length > 0) अणु
		u32 tlen = length > 20 ? 20 : length;

		length -= tlen;

		करो अणु
			sum1 += buffer[offset + i];
			sum2 += sum1;
			i++;
		पूर्ण जबतक (--tlen > 0);

		sum1 = (sum1 & 0xFF) + (sum1 >> 8);
		sum2 = (sum2 & 0xFF) + (sum2 >> 8);
	पूर्ण

	sum1 = (sum1 & 0xFF) + (sum1 >> 8);
	sum2 = (sum2 & 0xFF) + (sum2 >> 8);

	वापस(sum2 << 8 | sum1);
पूर्ण

अटल पूर्णांक t4_पढ़ो_ग_लिखो_रेजिस्टर(काष्ठा hid_device *hdev, u32 address,
	u8 *पढ़ो_val, u8 ग_लिखो_val, bool पढ़ो_flag)
अणु
	पूर्णांक ret;
	u16 check_sum;
	u8 *input;
	u8 *पढ़ोbuf = शून्य;

	input = kzalloc(T4_FEATURE_REPORT_LEN, GFP_KERNEL);
	अगर (!input)
		वापस -ENOMEM;

	input[0] = T4_FEATURE_REPORT_ID;
	अगर (पढ़ो_flag) अणु
		input[1] = T4_CMD_REGISTER_READ;
		input[8] = 0x00;
	पूर्ण अन्यथा अणु
		input[1] = T4_CMD_REGISTER_WRITE;
		input[8] = ग_लिखो_val;
	पूर्ण
	put_unaligned_le32(address, input + 2);
	input[6] = 1;
	input[7] = 0;

	/* Calculate the checksum */
	check_sum = t4_calc_check_sum(input, 1, 8);
	input[9] = (u8)check_sum;
	input[10] = (u8)(check_sum >> 8);
	input[11] = 0;

	ret = hid_hw_raw_request(hdev, T4_FEATURE_REPORT_ID, input,
			T4_FEATURE_REPORT_LEN,
			HID_FEATURE_REPORT, HID_REQ_SET_REPORT);

	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed to read command (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	अगर (पढ़ो_flag) अणु
		पढ़ोbuf = kzalloc(T4_FEATURE_REPORT_LEN, GFP_KERNEL);
		अगर (!पढ़ोbuf) अणु
			ret = -ENOMEM;
			जाओ निकास;
		पूर्ण

		ret = hid_hw_raw_request(hdev, T4_FEATURE_REPORT_ID, पढ़ोbuf,
				T4_FEATURE_REPORT_LEN,
				HID_FEATURE_REPORT, HID_REQ_GET_REPORT);
		अगर (ret < 0) अणु
			dev_err(&hdev->dev, "failed read register (%d)\n", ret);
			जाओ निकास_पढ़ोbuf;
		पूर्ण

		ret = -EINVAL;

		अगर (*(u32 *)&पढ़ोbuf[6] != address) अणु
			dev_err(&hdev->dev, "read register address error (%x,%x)\n",
				*(u32 *)&पढ़ोbuf[6], address);
			जाओ निकास_पढ़ोbuf;
		पूर्ण

		अगर (*(u16 *)&पढ़ोbuf[10] != 1) अणु
			dev_err(&hdev->dev, "read register size error (%x)\n",
				*(u16 *)&पढ़ोbuf[10]);
			जाओ निकास_पढ़ोbuf;
		पूर्ण

		check_sum = t4_calc_check_sum(पढ़ोbuf, 6, 7);
		अगर (*(u16 *)&पढ़ोbuf[13] != check_sum) अणु
			dev_err(&hdev->dev, "read register checksum error (%x,%x)\n",
				*(u16 *)&पढ़ोbuf[13], check_sum);
			जाओ निकास_पढ़ोbuf;
		पूर्ण

		*पढ़ो_val = पढ़ोbuf[12];
	पूर्ण

	ret = 0;

निकास_पढ़ोbuf:
	kमुक्त(पढ़ोbuf);
निकास:
	kमुक्त(input);
	वापस ret;
पूर्ण

अटल पूर्णांक u1_पढ़ो_ग_लिखो_रेजिस्टर(काष्ठा hid_device *hdev, u32 address,
	u8 *पढ़ो_val, u8 ग_लिखो_val, bool पढ़ो_flag)
अणु
	पूर्णांक ret, i;
	u8 check_sum;
	u8 *input;
	u8 *पढ़ोbuf;

	input = kzalloc(U1_FEATURE_REPORT_LEN, GFP_KERNEL);
	अगर (!input)
		वापस -ENOMEM;

	input[0] = U1_FEATURE_REPORT_ID;
	अगर (पढ़ो_flag) अणु
		input[1] = U1_CMD_REGISTER_READ;
		input[6] = 0x00;
	पूर्ण अन्यथा अणु
		input[1] = U1_CMD_REGISTER_WRITE;
		input[6] = ग_लिखो_val;
	पूर्ण

	put_unaligned_le32(address, input + 2);

	/* Calculate the checksum */
	check_sum = U1_FEATURE_REPORT_LEN_ALL;
	क्रम (i = 0; i < U1_FEATURE_REPORT_LEN - 1; i++)
		check_sum += input[i];

	input[7] = check_sum;
	ret = hid_hw_raw_request(hdev, U1_FEATURE_REPORT_ID, input,
			U1_FEATURE_REPORT_LEN,
			HID_FEATURE_REPORT, HID_REQ_SET_REPORT);

	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed to read command (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	अगर (पढ़ो_flag) अणु
		पढ़ोbuf = kzalloc(U1_FEATURE_REPORT_LEN, GFP_KERNEL);
		अगर (!पढ़ोbuf) अणु
			ret = -ENOMEM;
			जाओ निकास;
		पूर्ण

		ret = hid_hw_raw_request(hdev, U1_FEATURE_REPORT_ID, पढ़ोbuf,
				U1_FEATURE_REPORT_LEN,
				HID_FEATURE_REPORT, HID_REQ_GET_REPORT);

		अगर (ret < 0) अणु
			dev_err(&hdev->dev, "failed read register (%d)\n", ret);
			kमुक्त(पढ़ोbuf);
			जाओ निकास;
		पूर्ण

		*पढ़ो_val = पढ़ोbuf[6];

		kमुक्त(पढ़ोbuf);
	पूर्ण

	ret = 0;

निकास:
	kमुक्त(input);
	वापस ret;
पूर्ण

अटल पूर्णांक t4_raw_event(काष्ठा alps_dev *hdata, u8 *data, पूर्णांक size)
अणु
	अचिन्हित पूर्णांक x, y, z;
	पूर्णांक i;
	काष्ठा t4_input_report *p_report = (काष्ठा t4_input_report *)data;

	अगर (!data)
		वापस 0;
	क्रम (i = 0; i < hdata->max_fingers; i++) अणु
		x = p_report->contact[i].x_hi << 8 | p_report->contact[i].x_lo;
		y = p_report->contact[i].y_hi << 8 | p_report->contact[i].y_lo;
		y = hdata->y_max - y + hdata->y_min;
		z = (p_report->contact[i].palm < 0x80 &&
			p_report->contact[i].palm > 0) * 62;
		अगर (x == 0xffff) अणु
			x = 0;
			y = 0;
			z = 0;
		पूर्ण
		input_mt_slot(hdata->input, i);

		input_mt_report_slot_state(hdata->input,
			MT_TOOL_FINGER, z != 0);

		अगर (!z)
			जारी;

		input_report_असल(hdata->input, ABS_MT_POSITION_X, x);
		input_report_असल(hdata->input, ABS_MT_POSITION_Y, y);
		input_report_असल(hdata->input, ABS_MT_PRESSURE, z);
	पूर्ण
	input_mt_sync_frame(hdata->input);

	input_report_key(hdata->input, BTN_LEFT, p_report->button);

	input_sync(hdata->input);
	वापस 1;
पूर्ण

अटल पूर्णांक u1_raw_event(काष्ठा alps_dev *hdata, u8 *data, पूर्णांक size)
अणु
	अचिन्हित पूर्णांक x, y, z;
	पूर्णांक i;
	लघु sp_x, sp_y;

	अगर (!data)
		वापस 0;
	चयन (data[0]) अणु
	हाल U1_MOUSE_REPORT_ID:
		अवरोध;
	हाल U1_FEATURE_REPORT_ID:
		अवरोध;
	हाल U1_ABSOLUTE_REPORT_ID:
	हाल U1_ABSOLUTE_REPORT_ID_SECD:
		क्रम (i = 0; i < hdata->max_fingers; i++) अणु
			u8 *contact = &data[i * 5];

			x = get_unaligned_le16(contact + 3);
			y = get_unaligned_le16(contact + 5);
			z = contact[7] & 0x7F;

			input_mt_slot(hdata->input, i);

			अगर (z != 0) अणु
				input_mt_report_slot_state(hdata->input,
					MT_TOOL_FINGER, 1);
				input_report_असल(hdata->input,
					ABS_MT_POSITION_X, x);
				input_report_असल(hdata->input,
					ABS_MT_POSITION_Y, y);
				input_report_असल(hdata->input,
					ABS_MT_PRESSURE, z);
			पूर्ण अन्यथा अणु
				input_mt_report_slot_inactive(hdata->input);
			पूर्ण
		पूर्ण

		input_mt_sync_frame(hdata->input);

		input_report_key(hdata->input, BTN_LEFT,
			data[1] & 0x1);
		input_report_key(hdata->input, BTN_RIGHT,
			(data[1] & 0x2));
		input_report_key(hdata->input, BTN_MIDDLE,
			(data[1] & 0x4));

		input_sync(hdata->input);

		वापस 1;

	हाल U1_SP_ABSOLUTE_REPORT_ID:
		sp_x = get_unaligned_le16(data+2);
		sp_y = get_unaligned_le16(data+4);

		sp_x = sp_x / 8;
		sp_y = sp_y / 8;

		input_report_rel(hdata->input2, REL_X, sp_x);
		input_report_rel(hdata->input2, REL_Y, sp_y);

		input_report_key(hdata->input2, BTN_LEFT,
			data[1] & 0x1);
		input_report_key(hdata->input2, BTN_RIGHT,
			(data[1] & 0x2));
		input_report_key(hdata->input2, BTN_MIDDLE,
			(data[1] & 0x4));

		input_sync(hdata->input2);

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alps_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	पूर्णांक ret = 0;
	काष्ठा alps_dev *hdata = hid_get_drvdata(hdev);

	चयन (hdev->product) अणु
	हाल HID_PRODUCT_ID_T4_BTNLESS:
		ret = t4_raw_event(hdata, data, size);
		अवरोध;
	शेष:
		ret = u1_raw_event(hdata, data, size);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused alps_post_reset(काष्ठा hid_device *hdev)
अणु
	पूर्णांक ret = -1;
	काष्ठा alps_dev *data = hid_get_drvdata(hdev);

	चयन (data->dev_type) अणु
	हाल T4:
		ret = t4_पढ़ो_ग_लिखो_रेजिस्टर(hdev, T4_PRM_FEED_CONFIG_1,
			शून्य, T4_I2C_ABS, false);
		अगर (ret < 0) अणु
			dev_err(&hdev->dev, "failed T4_PRM_FEED_CONFIG_1 (%d)\n",
				ret);
			जाओ निकास;
		पूर्ण

		ret = t4_पढ़ो_ग_लिखो_रेजिस्टर(hdev, T4_PRM_FEED_CONFIG_4,
			शून्य, T4_FEEDCFG4_ADVANCED_ABS_ENABLE, false);
		अगर (ret < 0) अणु
			dev_err(&hdev->dev, "failed T4_PRM_FEED_CONFIG_4 (%d)\n",
				ret);
			जाओ निकास;
		पूर्ण
		अवरोध;
	हाल U1:
		ret = u1_पढ़ो_ग_लिखो_रेजिस्टर(hdev,
			ADDRESS_U1_DEV_CTRL_1, शून्य,
			U1_TP_ABS_MODE | U1_SP_ABS_MODE, false);
		अगर (ret < 0) अणु
			dev_err(&hdev->dev, "failed to change TP mode (%d)\n",
				ret);
			जाओ निकास;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused alps_post_resume(काष्ठा hid_device *hdev)
अणु
	वापस alps_post_reset(hdev);
पूर्ण

अटल पूर्णांक u1_init(काष्ठा hid_device *hdev, काष्ठा alps_dev *pri_data)
अणु
	पूर्णांक ret;
	u8 पंचांगp, dev_ctrl, sen_line_num_x, sen_line_num_y;
	u8 pitch_x, pitch_y, resolution;

	/* Device initialization */
	ret = u1_पढ़ो_ग_लिखो_रेजिस्टर(hdev, ADDRESS_U1_DEV_CTRL_1,
			&dev_ctrl, 0, true);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed U1_DEV_CTRL_1 (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	dev_ctrl &= ~U1_DISABLE_DEV;
	dev_ctrl |= U1_TP_ABS_MODE;
	ret = u1_पढ़ो_ग_लिखो_रेजिस्टर(hdev, ADDRESS_U1_DEV_CTRL_1,
			शून्य, dev_ctrl, false);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed to change TP mode (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	ret = u1_पढ़ो_ग_लिखो_रेजिस्टर(hdev, ADDRESS_U1_NUM_SENS_X,
			&sen_line_num_x, 0, true);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed U1_NUM_SENS_X (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	ret = u1_पढ़ो_ग_लिखो_रेजिस्टर(hdev, ADDRESS_U1_NUM_SENS_Y,
			&sen_line_num_y, 0, true);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed U1_NUM_SENS_Y (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	ret = u1_पढ़ो_ग_लिखो_रेजिस्टर(hdev, ADDRESS_U1_PITCH_SENS_X,
			&pitch_x, 0, true);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed U1_PITCH_SENS_X (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	ret = u1_पढ़ो_ग_लिखो_रेजिस्टर(hdev, ADDRESS_U1_PITCH_SENS_Y,
			&pitch_y, 0, true);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed U1_PITCH_SENS_Y (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	ret = u1_पढ़ो_ग_लिखो_रेजिस्टर(hdev, ADDRESS_U1_RESO_DWN_ABS,
		&resolution, 0, true);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed U1_RESO_DWN_ABS (%d)\n", ret);
		जाओ निकास;
	पूर्ण
	pri_data->x_active_len_mm =
		(pitch_x * (sen_line_num_x - 1)) / 10;
	pri_data->y_active_len_mm =
		(pitch_y * (sen_line_num_y - 1)) / 10;

	pri_data->x_max =
		(resolution << 2) * (sen_line_num_x - 1);
	pri_data->x_min = 1;
	pri_data->y_max =
		(resolution << 2) * (sen_line_num_y - 1);
	pri_data->y_min = 1;

	ret = u1_पढ़ो_ग_लिखो_रेजिस्टर(hdev, ADDRESS_U1_PAD_BTN,
			&पंचांगp, 0, true);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed U1_PAD_BTN (%d)\n", ret);
		जाओ निकास;
	पूर्ण
	अगर ((पंचांगp & 0x0F) == (पंचांगp & 0xF0) >> 4) अणु
		pri_data->btn_cnt = (पंचांगp & 0x0F);
	पूर्ण अन्यथा अणु
		/* Button pad */
		pri_data->btn_cnt = 1;
	पूर्ण

	pri_data->has_sp = 0;
	/* Check StickPoपूर्णांकer device */
	ret = u1_पढ़ो_ग_लिखो_रेजिस्टर(hdev, ADDRESS_U1_DEVICE_TYP,
			&पंचांगp, 0, true);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed U1_DEVICE_TYP (%d)\n", ret);
		जाओ निकास;
	पूर्ण
	अगर (पंचांगp & U1_DEVTYPE_SP_SUPPORT) अणु
		dev_ctrl |= U1_SP_ABS_MODE;
		ret = u1_पढ़ो_ग_लिखो_रेजिस्टर(hdev, ADDRESS_U1_DEV_CTRL_1,
			शून्य, dev_ctrl, false);
		अगर (ret < 0) अणु
			dev_err(&hdev->dev, "failed SP mode (%d)\n", ret);
			जाओ निकास;
		पूर्ण

		ret = u1_पढ़ो_ग_लिखो_रेजिस्टर(hdev, ADDRESS_U1_SP_BTN,
			&pri_data->sp_btn_info, 0, true);
		अगर (ret < 0) अणु
			dev_err(&hdev->dev, "failed U1_SP_BTN (%d)\n", ret);
			जाओ निकास;
		पूर्ण
		pri_data->has_sp = 1;
	पूर्ण
	pri_data->max_fingers = 5;
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक T4_init(काष्ठा hid_device *hdev, काष्ठा alps_dev *pri_data)
अणु
	पूर्णांक ret;
	u8 पंचांगp, sen_line_num_x, sen_line_num_y;

	ret = t4_पढ़ो_ग_लिखो_रेजिस्टर(hdev, T4_PRM_ID_CONFIG_3, &पंचांगp, 0, true);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed T4_PRM_ID_CONFIG_3 (%d)\n", ret);
		जाओ निकास;
	पूर्ण
	sen_line_num_x = 16 + ((पंचांगp & 0x0F)  | (पंचांगp & 0x08 ? 0xF0 : 0));
	sen_line_num_y = 12 + (((पंचांगp & 0xF0) >> 4)  | (पंचांगp & 0x80 ? 0xF0 : 0));

	pri_data->x_max = sen_line_num_x * T4_COUNT_PER_ELECTRODE;
	pri_data->x_min = T4_COUNT_PER_ELECTRODE;
	pri_data->y_max = sen_line_num_y * T4_COUNT_PER_ELECTRODE;
	pri_data->y_min = T4_COUNT_PER_ELECTRODE;
	pri_data->x_active_len_mm = pri_data->y_active_len_mm = 0;
	pri_data->btn_cnt = 1;

	ret = t4_पढ़ो_ग_लिखो_रेजिस्टर(hdev, PRM_SYS_CONFIG_1, &पंचांगp, 0, true);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed PRM_SYS_CONFIG_1 (%d)\n", ret);
		जाओ निकास;
	पूर्ण
	पंचांगp |= 0x02;
	ret = t4_पढ़ो_ग_लिखो_रेजिस्टर(hdev, PRM_SYS_CONFIG_1, शून्य, पंचांगp, false);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed PRM_SYS_CONFIG_1 (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	ret = t4_पढ़ो_ग_लिखो_रेजिस्टर(hdev, T4_PRM_FEED_CONFIG_1,
					शून्य, T4_I2C_ABS, false);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed T4_PRM_FEED_CONFIG_1 (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	ret = t4_पढ़ो_ग_लिखो_रेजिस्टर(hdev, T4_PRM_FEED_CONFIG_4, शून्य,
				T4_FEEDCFG4_ADVANCED_ABS_ENABLE, false);
	अगर (ret < 0) अणु
		dev_err(&hdev->dev, "failed T4_PRM_FEED_CONFIG_4 (%d)\n", ret);
		जाओ निकास;
	पूर्ण
	pri_data->max_fingers = 5;
	pri_data->has_sp = 0;
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक alps_sp_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);

	वापस hid_hw_खोलो(hid);
पूर्ण

अटल व्योम alps_sp_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);

	hid_hw_बंद(hid);
पूर्ण

अटल पूर्णांक alps_input_configured(काष्ठा hid_device *hdev, काष्ठा hid_input *hi)
अणु
	काष्ठा alps_dev *data = hid_get_drvdata(hdev);
	काष्ठा input_dev *input = hi->input, *input2;
	पूर्णांक ret;
	पूर्णांक res_x, res_y, i;

	data->input = input;

	hid_dbg(hdev, "Opening low level driver\n");
	ret = hid_hw_खोलो(hdev);
	अगर (ret)
		वापस ret;

	/* Allow incoming hid reports */
	hid_device_io_start(hdev);
	चयन (data->dev_type) अणु
	हाल T4:
		ret = T4_init(hdev, data);
		अवरोध;
	हाल U1:
		ret = u1_init(hdev, data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ret)
		जाओ निकास;

	__set_bit(EV_ABS, input->evbit);
	input_set_असल_params(input, ABS_MT_POSITION_X,
						data->x_min, data->x_max, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y,
						data->y_min, data->y_max, 0, 0);

	अगर (data->x_active_len_mm && data->y_active_len_mm) अणु
		res_x = (data->x_max - 1) / data->x_active_len_mm;
		res_y = (data->y_max - 1) / data->y_active_len_mm;

		input_असल_set_res(input, ABS_MT_POSITION_X, res_x);
		input_असल_set_res(input, ABS_MT_POSITION_Y, res_y);
	पूर्ण

	input_set_असल_params(input, ABS_MT_PRESSURE, 0, 64, 0, 0);

	input_mt_init_slots(input, data->max_fingers, INPUT_MT_POINTER);

	__set_bit(EV_KEY, input->evbit);

	अगर (data->btn_cnt == 1)
		__set_bit(INPUT_PROP_BUTTONPAD, input->propbit);

	क्रम (i = 0; i < data->btn_cnt; i++)
		__set_bit(BTN_LEFT + i, input->keybit);

	/* Stick device initialization */
	अगर (data->has_sp) अणु
		input2 = input_allocate_device();
		अगर (!input2) अणु
			ret = -ENOMEM;
			जाओ निकास;
		पूर्ण

		data->input2 = input2;
		input2->phys = input->phys;
		input2->name = "DualPoint Stick";
		input2->id.bustype = BUS_I2C;
		input2->id.venकरोr  = input->id.venकरोr;
		input2->id.product = input->id.product;
		input2->id.version = input->id.version;
		input2->dev.parent = input->dev.parent;

		input_set_drvdata(input2, hdev);
		input2->खोलो = alps_sp_खोलो;
		input2->बंद = alps_sp_बंद;

		__set_bit(EV_KEY, input2->evbit);
		data->sp_btn_cnt = (data->sp_btn_info & 0x0F);
		क्रम (i = 0; i < data->sp_btn_cnt; i++)
			__set_bit(BTN_LEFT + i, input2->keybit);

		__set_bit(EV_REL, input2->evbit);
		__set_bit(REL_X, input2->relbit);
		__set_bit(REL_Y, input2->relbit);
		__set_bit(INPUT_PROP_POINTER, input2->propbit);
		__set_bit(INPUT_PROP_POINTING_STICK, input2->propbit);

		अगर (input_रेजिस्टर_device(data->input2)) अणु
			input_मुक्त_device(input2);
			ret = -ENOENT;
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	hid_device_io_stop(hdev);
	hid_hw_बंद(hdev);
	वापस ret;
पूर्ण

अटल पूर्णांक alps_input_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	वापस -1;
पूर्ण

अटल पूर्णांक alps_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा alps_dev *data = शून्य;
	पूर्णांक ret;
	data = devm_kzalloc(&hdev->dev, माप(काष्ठा alps_dev), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->hdev = hdev;
	hid_set_drvdata(hdev, data);

	hdev->quirks |= HID_QUIRK_NO_INIT_REPORTS;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		वापस ret;
	पूर्ण

	चयन (hdev->product) अणु
	हाल HID_DEVICE_ID_ALPS_T4_BTNLESS:
		data->dev_type = T4;
		अवरोध;
	हाल HID_DEVICE_ID_ALPS_U1_DUAL:
	हाल HID_DEVICE_ID_ALPS_U1:
	हाल HID_DEVICE_ID_ALPS_U1_UNICORN_LEGACY:
		data->dev_type = U1;
		अवरोध;
	शेष:
		data->dev_type = UNKNOWN;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम alps_हटाओ(काष्ठा hid_device *hdev)
अणु
	hid_hw_stop(hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id alps_id[] = अणु
	अणु HID_DEVICE(HID_BUS_ANY, HID_GROUP_ANY,
		USB_VENDOR_ID_ALPS_JP, HID_DEVICE_ID_ALPS_U1_DUAL) पूर्ण,
	अणु HID_DEVICE(HID_BUS_ANY, HID_GROUP_ANY,
		USB_VENDOR_ID_ALPS_JP, HID_DEVICE_ID_ALPS_U1) पूर्ण,
	अणु HID_DEVICE(HID_BUS_ANY, HID_GROUP_ANY,
		USB_VENDOR_ID_ALPS_JP, HID_DEVICE_ID_ALPS_T4_BTNLESS) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, alps_id);

अटल काष्ठा hid_driver alps_driver = अणु
	.name = "hid-alps",
	.id_table		= alps_id,
	.probe			= alps_probe,
	.हटाओ			= alps_हटाओ,
	.raw_event		= alps_raw_event,
	.input_mapping		= alps_input_mapping,
	.input_configured	= alps_input_configured,
#अगर_घोषित CONFIG_PM
	.resume			= alps_post_resume,
	.reset_resume		= alps_post_reset,
#पूर्ण_अगर
पूर्ण;

module_hid_driver(alps_driver);

MODULE_AUTHOR("Masaki Ota <masaki.ota@jp.alps.com>");
MODULE_DESCRIPTION("ALPS HID driver");
MODULE_LICENSE("GPL");
