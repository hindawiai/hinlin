<शैली गुरु>
/*
 * Cypress APA trackpad with I2C पूर्णांकerface
 *
 * Author: Dudley Du <dudl@cypress.com>
 *
 * Copyright (C) 2015 Cypress Semiconductor, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/crc-itu-t.h>
#समावेश "cyapa.h"


#घोषणा GEN6_ENABLE_CMD_IRQ	0x41
#घोषणा GEN6_DISABLE_CMD_IRQ	0x42
#घोषणा GEN6_ENABLE_DEV_IRQ	0x43
#घोषणा GEN6_DISABLE_DEV_IRQ	0x44

#घोषणा GEN6_POWER_MODE_ACTIVE		0x01
#घोषणा GEN6_POWER_MODE_LP_MODE1	0x02
#घोषणा GEN6_POWER_MODE_LP_MODE2	0x03
#घोषणा GEN6_POWER_MODE_BTN_ONLY	0x04

#घोषणा GEN6_SET_POWER_MODE_INTERVAL	0x47
#घोषणा GEN6_GET_POWER_MODE_INTERVAL	0x48

#घोषणा GEN6_MAX_RX_NUM 14
#घोषणा GEN6_RETRIEVE_DATA_ID_RX_ATTENURATOR_IDAC	0x00
#घोषणा GEN6_RETRIEVE_DATA_ID_ATTENURATOR_TRIM		0x12


काष्ठा pip_app_cmd_head अणु
	__le16 addr;
	__le16 length;
	u8 report_id;
	u8 resv;  /* Reserved, must be 0 */
	u8 cmd_code;  /* bit7: resv, set to 0; bit6~0: command code.*/
पूर्ण __packed;

काष्ठा pip_app_resp_head अणु
	__le16 length;
	u8 report_id;
	u8 resv;  /* Reserved, must be 0 */
	u8 cmd_code;  /* bit7: TGL; bit6~0: command code.*/
	/*
	 * The value of data_status can be the first byte of data or
	 * the command status or the unsupported command code depending on the
	 * requested command code.
	*/
	u8 data_status;
पूर्ण __packed;

काष्ठा pip_fixed_info अणु
	u8 silicon_id_high;
	u8 silicon_id_low;
	u8 family_id;
पूर्ण;

अटल u8 pip_get_bl_info[] = अणु
	0x04, 0x00, 0x0B, 0x00, 0x40, 0x00, 0x01, 0x38,
	0x00, 0x00, 0x70, 0x9E, 0x17
पूर्ण;

अटल bool cyapa_sort_pip_hid_descriptor_data(काष्ठा cyapa *cyapa,
		u8 *buf, पूर्णांक len)
अणु
	अगर (len != PIP_HID_DESCRIPTOR_SIZE)
		वापस false;

	अगर (buf[PIP_RESP_REPORT_ID_OFFSET] == PIP_HID_APP_REPORT_ID ||
		buf[PIP_RESP_REPORT_ID_OFFSET] == PIP_HID_BL_REPORT_ID)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक cyapa_get_pip_fixed_info(काष्ठा cyapa *cyapa,
		काष्ठा pip_fixed_info *pip_info, bool is_bootloader)
अणु
	u8 resp_data[PIP_READ_SYS_INFO_RESP_LENGTH];
	पूर्णांक resp_len;
	u16 product_family;
	पूर्णांक error;

	अगर (is_bootloader) अणु
		/* Read Bootloader Inक्रमmation to determine Gen5 or Gen6. */
		resp_len = माप(resp_data);
		error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
				pip_get_bl_info, माप(pip_get_bl_info),
				resp_data, &resp_len,
				2000, cyapa_sort_tsg_pip_bl_resp_data,
				false);
		अगर (error || resp_len < PIP_BL_GET_INFO_RESP_LENGTH)
			वापस error ? error : -EIO;

		pip_info->family_id = resp_data[8];
		pip_info->silicon_id_low = resp_data[10];
		pip_info->silicon_id_high = resp_data[11];

		वापस 0;
	पूर्ण

	/* Get App System Inक्रमmation to determine Gen5 or Gen6. */
	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			pip_पढ़ो_sys_info, PIP_READ_SYS_INFO_CMD_LENGTH,
			resp_data, &resp_len,
			2000, cyapa_pip_sort_प्रणाली_info_data, false);
	अगर (error || resp_len < PIP_READ_SYS_INFO_RESP_LENGTH)
		वापस error ? error : -EIO;

	product_family = get_unaligned_le16(&resp_data[7]);
	अगर ((product_family & PIP_PRODUCT_FAMILY_MASK) !=
		PIP_PRODUCT_FAMILY_TRACKPAD)
		वापस -EINVAL;

	pip_info->family_id = resp_data[19];
	pip_info->silicon_id_low = resp_data[21];
	pip_info->silicon_id_high = resp_data[22];

	वापस 0;

पूर्ण

पूर्णांक cyapa_pip_state_parse(काष्ठा cyapa *cyapa, u8 *reg_data, पूर्णांक len)
अणु
	u8 cmd[] = अणु 0x01, 0x00पूर्ण;
	काष्ठा pip_fixed_info pip_info;
	u8 resp_data[PIP_HID_DESCRIPTOR_SIZE];
	पूर्णांक resp_len;
	bool is_bootloader;
	पूर्णांक error;

	cyapa->state = CYAPA_STATE_NO_DEVICE;

	/* Try to wake from it deep sleep state अगर it is. */
	cyapa_pip_deep_sleep(cyapa, PIP_DEEP_SLEEP_STATE_ON);

	/* Empty the buffer queue to get fresh data with later commands. */
	cyapa_empty_pip_output_data(cyapa, शून्य, शून्य, शून्य);

	/*
	 * Read description info from trackpad device to determine running in
	 * APP mode or Bootloader mode.
	 */
	resp_len = PIP_HID_DESCRIPTOR_SIZE;
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, माप(cmd),
			resp_data, &resp_len,
			300,
			cyapa_sort_pip_hid_descriptor_data,
			false);
	अगर (error)
		वापस error;

	अगर (resp_data[PIP_RESP_REPORT_ID_OFFSET] == PIP_HID_BL_REPORT_ID)
		is_bootloader = true;
	अन्यथा अगर (resp_data[PIP_RESP_REPORT_ID_OFFSET] == PIP_HID_APP_REPORT_ID)
		is_bootloader = false;
	अन्यथा
		वापस -EAGAIN;

	/* Get PIP fixed inक्रमmation to determine Gen5 or Gen6. */
	स_रखो(&pip_info, 0, माप(काष्ठा pip_fixed_info));
	error = cyapa_get_pip_fixed_info(cyapa, &pip_info, is_bootloader);
	अगर (error)
		वापस error;

	अगर (pip_info.family_id == 0x9B && pip_info.silicon_id_high == 0x0B) अणु
		cyapa->gen = CYAPA_GEN6;
		cyapa->state = is_bootloader ? CYAPA_STATE_GEN6_BL
					     : CYAPA_STATE_GEN6_APP;
	पूर्ण अन्यथा अगर (pip_info.family_id == 0x91 &&
		   pip_info.silicon_id_high == 0x02) अणु
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = is_bootloader ? CYAPA_STATE_GEN5_BL
					     : CYAPA_STATE_GEN5_APP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen6_पढ़ो_sys_info(काष्ठा cyapa *cyapa)
अणु
	u8 resp_data[PIP_READ_SYS_INFO_RESP_LENGTH];
	पूर्णांक resp_len;
	u16 product_family;
	u8 rotat_align;
	पूर्णांक error;

	/* Get App System Inक्रमmation to determine Gen5 or Gen6. */
	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			pip_पढ़ो_sys_info, PIP_READ_SYS_INFO_CMD_LENGTH,
			resp_data, &resp_len,
			2000, cyapa_pip_sort_प्रणाली_info_data, false);
	अगर (error || resp_len < माप(resp_data))
		वापस error ? error : -EIO;

	product_family = get_unaligned_le16(&resp_data[7]);
	अगर ((product_family & PIP_PRODUCT_FAMILY_MASK) !=
		PIP_PRODUCT_FAMILY_TRACKPAD)
		वापस -EINVAL;

	cyapa->platक्रमm_ver = (resp_data[67] >> PIP_BL_PLATFORM_VER_SHIFT) &
			      PIP_BL_PLATFORM_VER_MASK;
	cyapa->fw_maj_ver = resp_data[9];
	cyapa->fw_min_ver = resp_data[10];

	cyapa->electrodes_x = resp_data[33];
	cyapa->electrodes_y = resp_data[34];

	cyapa->physical_size_x =  get_unaligned_le16(&resp_data[35]) / 100;
	cyapa->physical_size_y = get_unaligned_le16(&resp_data[37]) / 100;

	cyapa->max_असल_x = get_unaligned_le16(&resp_data[39]);
	cyapa->max_असल_y = get_unaligned_le16(&resp_data[41]);

	cyapa->max_z = get_unaligned_le16(&resp_data[43]);

	cyapa->x_origin = resp_data[45] & 0x01;
	cyapa->y_origin = resp_data[46] & 0x01;

	cyapa->btn_capability = (resp_data[70] << 3) & CAPABILITY_BTN_MASK;

	स_नकल(&cyapa->product_id[0], &resp_data[51], 5);
	cyapa->product_id[5] = '-';
	स_नकल(&cyapa->product_id[6], &resp_data[56], 6);
	cyapa->product_id[12] = '-';
	स_नकल(&cyapa->product_id[13], &resp_data[62], 2);
	cyapa->product_id[15] = '\0';

	/* Get the number of Rx electrodes. */
	rotat_align = resp_data[68];
	cyapa->electrodes_rx =
		rotat_align ? cyapa->electrodes_y : cyapa->electrodes_x;
	cyapa->aligned_electrodes_rx = (cyapa->electrodes_rx + 3) & ~3u;

	अगर (!cyapa->electrodes_x || !cyapa->electrodes_y ||
		!cyapa->physical_size_x || !cyapa->physical_size_y ||
		!cyapa->max_असल_x || !cyapa->max_असल_y || !cyapa->max_z)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen6_bl_पढ़ो_app_info(काष्ठा cyapa *cyapa)
अणु
	u8 resp_data[PIP_BL_APP_INFO_RESP_LENGTH];
	पूर्णांक resp_len;
	पूर्णांक error;

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			pip_bl_पढ़ो_app_info, PIP_BL_READ_APP_INFO_CMD_LENGTH,
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_bl_resp_data, false);
	अगर (error || resp_len < PIP_BL_APP_INFO_RESP_LENGTH ||
		!PIP_CMD_COMPLETE_SUCCESS(resp_data))
		वापस error ? error : -EIO;

	cyapa->fw_maj_ver = resp_data[8];
	cyapa->fw_min_ver = resp_data[9];

	cyapa->platक्रमm_ver = (resp_data[12] >> PIP_BL_PLATFORM_VER_SHIFT) &
			      PIP_BL_PLATFORM_VER_MASK;

	स_नकल(&cyapa->product_id[0], &resp_data[13], 5);
	cyapa->product_id[5] = '-';
	स_नकल(&cyapa->product_id[6], &resp_data[18], 6);
	cyapa->product_id[12] = '-';
	स_नकल(&cyapa->product_id[13], &resp_data[24], 2);
	cyapa->product_id[15] = '\0';

	वापस 0;

पूर्ण

अटल पूर्णांक cyapa_gen6_config_dev_irq(काष्ठा cyapa *cyapa, u8 cmd_code)
अणु
	u8 cmd[] = अणु 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00, cmd_code पूर्ण;
	u8 resp_data[6];
	पूर्णांक resp_len;
	पूर्णांक error;

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa, cmd, माप(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, false);
	अगर (error || !VALID_CMD_RESP_HEADER(resp_data, cmd_code) ||
			!PIP_CMD_COMPLETE_SUCCESS(resp_data)
			)
		वापस error < 0 ? error : -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen6_set_proximity(काष्ठा cyapa *cyapa, bool enable)
अणु
	पूर्णांक error;

	cyapa_gen6_config_dev_irq(cyapa, GEN6_DISABLE_CMD_IRQ);
	error = cyapa_pip_set_proximity(cyapa, enable);
	cyapa_gen6_config_dev_irq(cyapa, GEN6_ENABLE_CMD_IRQ);

	वापस error;
पूर्ण

अटल पूर्णांक cyapa_gen6_change_घातer_state(काष्ठा cyapa *cyapa, u8 घातer_mode)
अणु
	u8 cmd[] = अणु 0x04, 0x00, 0x06, 0x00, 0x2f, 0x00, 0x46, घातer_mode पूर्ण;
	u8 resp_data[6];
	पूर्णांक resp_len;
	पूर्णांक error;

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa, cmd, माप(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, false);
	अगर (error || !VALID_CMD_RESP_HEADER(resp_data, 0x46))
		वापस error < 0 ? error : -EINVAL;

	/* New घातer state applied in device not match the set घातer state. */
	अगर (resp_data[5] != घातer_mode)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen6_set_पूर्णांकerval_setting(काष्ठा cyapa *cyapa,
		काष्ठा gen6_पूर्णांकerval_setting *पूर्णांकerval_setting)
अणु
	काष्ठा gen6_set_पूर्णांकerval_cmd अणु
		__le16 addr;
		__le16 length;
		u8 report_id;
		u8 rsvd;  /* Reserved, must be 0 */
		u8 cmd_code;
		__le16 active_पूर्णांकerval;
		__le16 lp1_पूर्णांकerval;
		__le16 lp2_पूर्णांकerval;
	पूर्ण __packed set_पूर्णांकerval_cmd;
	u8 resp_data[11];
	पूर्णांक resp_len;
	पूर्णांक error;

	स_रखो(&set_पूर्णांकerval_cmd, 0, माप(set_पूर्णांकerval_cmd));
	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &set_पूर्णांकerval_cmd.addr);
	put_unaligned_le16(माप(set_पूर्णांकerval_cmd) - 2,
			   &set_पूर्णांकerval_cmd.length);
	set_पूर्णांकerval_cmd.report_id = PIP_APP_CMD_REPORT_ID;
	set_पूर्णांकerval_cmd.cmd_code = GEN6_SET_POWER_MODE_INTERVAL;
	put_unaligned_le16(पूर्णांकerval_setting->active_पूर्णांकerval,
			   &set_पूर्णांकerval_cmd.active_पूर्णांकerval);
	put_unaligned_le16(पूर्णांकerval_setting->lp1_पूर्णांकerval,
			   &set_पूर्णांकerval_cmd.lp1_पूर्णांकerval);
	put_unaligned_le16(पूर्णांकerval_setting->lp2_पूर्णांकerval,
			   &set_पूर्णांकerval_cmd.lp2_पूर्णांकerval);

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			(u8 *)&set_पूर्णांकerval_cmd, माप(set_पूर्णांकerval_cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, false);
	अगर (error ||
		!VALID_CMD_RESP_HEADER(resp_data, GEN6_SET_POWER_MODE_INTERVAL))
		वापस error < 0 ? error : -EINVAL;

	/* Get the real set पूर्णांकervals from response. */
	पूर्णांकerval_setting->active_पूर्णांकerval = get_unaligned_le16(&resp_data[5]);
	पूर्णांकerval_setting->lp1_पूर्णांकerval = get_unaligned_le16(&resp_data[7]);
	पूर्णांकerval_setting->lp2_पूर्णांकerval = get_unaligned_le16(&resp_data[9]);

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen6_get_पूर्णांकerval_setting(काष्ठा cyapa *cyapa,
		काष्ठा gen6_पूर्णांकerval_setting *पूर्णांकerval_setting)
अणु
	u8 cmd[] = अणु 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00,
		     GEN6_GET_POWER_MODE_INTERVAL पूर्ण;
	u8 resp_data[11];
	पूर्णांक resp_len;
	पूर्णांक error;

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa, cmd, माप(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, false);
	अगर (error ||
		!VALID_CMD_RESP_HEADER(resp_data, GEN6_GET_POWER_MODE_INTERVAL))
		वापस error < 0 ? error : -EINVAL;

	पूर्णांकerval_setting->active_पूर्णांकerval = get_unaligned_le16(&resp_data[5]);
	पूर्णांकerval_setting->lp1_पूर्णांकerval = get_unaligned_le16(&resp_data[7]);
	पूर्णांकerval_setting->lp2_पूर्णांकerval = get_unaligned_le16(&resp_data[9]);

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen6_deep_sleep(काष्ठा cyapa *cyapa, u8 state)
अणु
	u8 ping[] = अणु 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00, 0x00 पूर्ण;

	अगर (state == PIP_DEEP_SLEEP_STATE_ON)
		/*
		 * Send ping command to notअगरy device prepare क्रम wake up
		 * when it's in deep sleep mode. At this समय, device will
		 * response nothing except an I2C NAK.
		 */
		cyapa_i2c_pip_ग_लिखो(cyapa, ping, माप(ping));

	वापस cyapa_pip_deep_sleep(cyapa, state);
पूर्ण

अटल पूर्णांक cyapa_gen6_set_घातer_mode(काष्ठा cyapa *cyapa,
		u8 घातer_mode, u16 sleep_समय, क्रमागत cyapa_pm_stage pm_stage)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	काष्ठा gen6_पूर्णांकerval_setting *पूर्णांकerval_setting =
			&cyapa->gen6_पूर्णांकerval_setting;
	u8 lp_mode;
	पूर्णांक error;

	अगर (cyapa->state != CYAPA_STATE_GEN6_APP)
		वापस 0;

	अगर (PIP_DEV_GET_PWR_STATE(cyapa) == UNINIT_PWR_MODE) अणु
		/*
		 * Assume TP in deep sleep mode when driver is loaded,
		 * aव्योम driver unload and reload command IO issue caused by TP
		 * has been set पूर्णांकo deep sleep mode when unloading.
		 */
		PIP_DEV_SET_PWR_STATE(cyapa, PWR_MODE_OFF);
	पूर्ण

	अगर (PIP_DEV_UNINIT_SLEEP_TIME(cyapa) &&
		PIP_DEV_GET_PWR_STATE(cyapa) != PWR_MODE_OFF)
		PIP_DEV_SET_SLEEP_TIME(cyapa, UNINIT_SLEEP_TIME);

	अगर (PIP_DEV_GET_PWR_STATE(cyapa) == घातer_mode) अणु
		अगर (घातer_mode == PWR_MODE_OFF ||
			घातer_mode == PWR_MODE_FULL_ACTIVE ||
			घातer_mode == PWR_MODE_BTN_ONLY ||
			PIP_DEV_GET_SLEEP_TIME(cyapa) == sleep_समय) अणु
			/* Has in correct घातer mode state, early वापस. */
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (घातer_mode == PWR_MODE_OFF) अणु
		cyapa_gen6_config_dev_irq(cyapa, GEN6_DISABLE_CMD_IRQ);

		error = cyapa_gen6_deep_sleep(cyapa, PIP_DEEP_SLEEP_STATE_OFF);
		अगर (error) अणु
			dev_err(dev, "enter deep sleep fail: %d\n", error);
			वापस error;
		पूर्ण

		PIP_DEV_SET_PWR_STATE(cyapa, PWR_MODE_OFF);
		वापस 0;
	पूर्ण

	/*
	 * When trackpad in घातer off mode, it cannot change to other घातer
	 * state directly, must be wake up from sleep firstly, then
	 * जारी to करो next घातer sate change.
	 */
	अगर (PIP_DEV_GET_PWR_STATE(cyapa) == PWR_MODE_OFF) अणु
		error = cyapa_gen6_deep_sleep(cyapa, PIP_DEEP_SLEEP_STATE_ON);
		अगर (error) अणु
			dev_err(dev, "deep sleep wake fail: %d\n", error);
			वापस error;
		पूर्ण
	पूर्ण

	/*
	 * Disable device निश्चित पूर्णांकerrupts क्रम command response to aव्योम
	 * disturbing प्रणाली suspending or hibernating process.
	 */
	cyapa_gen6_config_dev_irq(cyapa, GEN6_DISABLE_CMD_IRQ);

	अगर (घातer_mode == PWR_MODE_FULL_ACTIVE) अणु
		error = cyapa_gen6_change_घातer_state(cyapa,
				GEN6_POWER_MODE_ACTIVE);
		अगर (error) अणु
			dev_err(dev, "change to active fail: %d\n", error);
			जाओ out;
		पूर्ण

		PIP_DEV_SET_PWR_STATE(cyapa, PWR_MODE_FULL_ACTIVE);

		/* Sync the पूर्णांकerval setting from device. */
		cyapa_gen6_get_पूर्णांकerval_setting(cyapa, पूर्णांकerval_setting);

	पूर्ण अन्यथा अगर (घातer_mode == PWR_MODE_BTN_ONLY) अणु
		error = cyapa_gen6_change_घातer_state(cyapa,
				GEN6_POWER_MODE_BTN_ONLY);
		अगर (error) अणु
			dev_err(dev, "fail to button only mode: %d\n", error);
			जाओ out;
		पूर्ण

		PIP_DEV_SET_PWR_STATE(cyapa, PWR_MODE_BTN_ONLY);
	पूर्ण अन्यथा अणु
		/*
		 * Gen6 पूर्णांकernally supports to 2 low घातer scan पूर्णांकerval समय,
		 * so can help to चयन घातer mode quickly.
		 * such as runसमय suspend and प्रणाली suspend.
		 */
		अगर (पूर्णांकerval_setting->lp1_पूर्णांकerval == sleep_समय) अणु
			lp_mode = GEN6_POWER_MODE_LP_MODE1;
		पूर्ण अन्यथा अगर (पूर्णांकerval_setting->lp2_पूर्णांकerval == sleep_समय) अणु
			lp_mode = GEN6_POWER_MODE_LP_MODE2;
		पूर्ण अन्यथा अणु
			अगर (पूर्णांकerval_setting->lp1_पूर्णांकerval == 0) अणु
				पूर्णांकerval_setting->lp1_पूर्णांकerval = sleep_समय;
				lp_mode = GEN6_POWER_MODE_LP_MODE1;
			पूर्ण अन्यथा अणु
				पूर्णांकerval_setting->lp2_पूर्णांकerval = sleep_समय;
				lp_mode = GEN6_POWER_MODE_LP_MODE2;
			पूर्ण
			cyapa_gen6_set_पूर्णांकerval_setting(cyapa,
							पूर्णांकerval_setting);
		पूर्ण

		error = cyapa_gen6_change_घातer_state(cyapa, lp_mode);
		अगर (error) अणु
			dev_err(dev, "set power state to 0x%02x failed: %d\n",
				lp_mode, error);
			जाओ out;
		पूर्ण

		PIP_DEV_SET_SLEEP_TIME(cyapa, sleep_समय);
		PIP_DEV_SET_PWR_STATE(cyapa,
			cyapa_sleep_समय_प्रकारo_pwr_cmd(sleep_समय));
	पूर्ण

out:
	cyapa_gen6_config_dev_irq(cyapa, GEN6_ENABLE_CMD_IRQ);
	वापस error;
पूर्ण

अटल पूर्णांक cyapa_gen6_initialize(काष्ठा cyapa *cyapa)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_pip_retrieve_data_काष्ठाure(काष्ठा cyapa *cyapa,
		u16 पढ़ो_offset, u16 पढ़ो_len, u8 data_id,
		u8 *data, पूर्णांक *data_buf_lens)
अणु
	काष्ठा retrieve_data_काष्ठा_cmd अणु
		काष्ठा pip_app_cmd_head head;
		__le16 पढ़ो_offset;
		__le16 पढ़ो_length;
		u8 data_id;
	पूर्ण __packed cmd;
	u8 resp_data[GEN6_MAX_RX_NUM + 10];
	पूर्णांक resp_len;
	पूर्णांक error;

	स_रखो(&cmd, 0, माप(cmd));
	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &cmd.head.addr);
	put_unaligned_le16(माप(cmd) - 2, &cmd.head.length);
	cmd.head.report_id = PIP_APP_CMD_REPORT_ID;
	cmd.head.cmd_code = PIP_RETRIEVE_DATA_STRUCTURE;
	put_unaligned_le16(पढ़ो_offset, &cmd.पढ़ो_offset);
	put_unaligned_le16(पढ़ो_len, &cmd.पढ़ो_length);
	cmd.data_id = data_id;

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
				(u8 *)&cmd, माप(cmd),
				resp_data, &resp_len,
				500, cyapa_sort_tsg_pip_app_resp_data,
				true);
	अगर (error || !PIP_CMD_COMPLETE_SUCCESS(resp_data) ||
		resp_data[6] != data_id ||
		!VALID_CMD_RESP_HEADER(resp_data, PIP_RETRIEVE_DATA_STRUCTURE))
		वापस (error < 0) ? error : -EAGAIN;

	पढ़ो_len = get_unaligned_le16(&resp_data[7]);
	अगर (*data_buf_lens < पढ़ो_len) अणु
		*data_buf_lens = पढ़ो_len;
		वापस -ENOBUFS;
	पूर्ण

	स_नकल(data, &resp_data[10], पढ़ो_len);
	*data_buf_lens = पढ़ो_len;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार cyapa_gen6_show_baseline(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	u8 data[GEN6_MAX_RX_NUM];
	पूर्णांक data_len;
	पूर्णांक size = 0;
	पूर्णांक i;
	पूर्णांक error;
	पूर्णांक resume_error;

	अगर (!cyapa_is_pip_app_mode(cyapa))
		वापस -EBUSY;

	/* 1. Suspend Scanning*/
	error = cyapa_pip_suspend_scanning(cyapa);
	अगर (error)
		वापस error;

	/* 2. IDAC and RX Attenuator Calibration Data (Center Frequency). */
	data_len = माप(data);
	error = cyapa_pip_retrieve_data_काष्ठाure(cyapa, 0, data_len,
			GEN6_RETRIEVE_DATA_ID_RX_ATTENURATOR_IDAC,
			data, &data_len);
	अगर (error)
		जाओ resume_scanning;

	size = scnम_लिखो(buf, PAGE_SIZE, "%d %d %d %d %d %d ",
			data[0],  /* RX Attenuator Mutual */
			data[1],  /* IDAC Mutual */
			data[2],  /* RX Attenuator Self RX */
			data[3],  /* IDAC Self RX */
			data[4],  /* RX Attenuator Self TX */
			data[5]	  /* IDAC Self TX */
			);

	/* 3. Read Attenuator Trim. */
	data_len = माप(data);
	error = cyapa_pip_retrieve_data_काष्ठाure(cyapa, 0, data_len,
			GEN6_RETRIEVE_DATA_ID_ATTENURATOR_TRIM,
			data, &data_len);
	अगर (error)
		जाओ resume_scanning;

	/* set attenuator trim values. */
	क्रम (i = 0; i < data_len; i++)
		size += scnम_लिखो(buf + size, PAGE_SIZE - size,	"%d ", data[i]);
	size += scnम_लिखो(buf + size, PAGE_SIZE - size, "\n");

resume_scanning:
	/* 4. Resume Scanning*/
	resume_error = cyapa_pip_resume_scanning(cyapa);
	अगर (resume_error || error) अणु
		स_रखो(buf, 0, PAGE_SIZE);
		वापस resume_error ? resume_error : error;
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक cyapa_gen6_operational_check(काष्ठा cyapa *cyapa)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	पूर्णांक error;

	अगर (cyapa->gen != CYAPA_GEN6)
		वापस -ENODEV;

	चयन (cyapa->state) अणु
	हाल CYAPA_STATE_GEN6_BL:
		error = cyapa_pip_bl_निकास(cyapa);
		अगर (error) अणु
			/* Try to update trackpad product inक्रमmation. */
			cyapa_gen6_bl_पढ़ो_app_info(cyapa);
			जाओ out;
		पूर्ण

		cyapa->state = CYAPA_STATE_GEN6_APP;
		fallthrough;

	हाल CYAPA_STATE_GEN6_APP:
		/*
		 * If trackpad device in deep sleep mode,
		 * the app command will fail.
		 * So always try to reset trackpad device to full active when
		 * the device state is required.
		 */
		error = cyapa_gen6_set_घातer_mode(cyapa,
				PWR_MODE_FULL_ACTIVE, 0, CYAPA_PM_ACTIVE);
		अगर (error)
			dev_warn(dev, "%s: failed to set power active mode.\n",
				__func__);

		/* By शेष, the trackpad proximity function is enabled. */
		error = cyapa_pip_set_proximity(cyapa, true);
		अगर (error)
			dev_warn(dev, "%s: failed to enable proximity.\n",
				__func__);

		/* Get trackpad product inक्रमmation. */
		error = cyapa_gen6_पढ़ो_sys_info(cyapa);
		अगर (error)
			जाओ out;
		/* Only support product ID starting with CYTRA */
		अगर (स_भेद(cyapa->product_id, product_id,
				म_माप(product_id)) != 0) अणु
			dev_err(dev, "%s: unknown product ID (%s)\n",
				__func__, cyapa->product_id);
			error = -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		error = -EINVAL;
	पूर्ण

out:
	वापस error;
पूर्ण

स्थिर काष्ठा cyapa_dev_ops cyapa_gen6_ops = अणु
	.check_fw = cyapa_pip_check_fw,
	.bl_enter = cyapa_pip_bl_enter,
	.bl_initiate = cyapa_pip_bl_initiate,
	.update_fw = cyapa_pip_करो_fw_update,
	.bl_activate = cyapa_pip_bl_activate,
	.bl_deactivate = cyapa_pip_bl_deactivate,

	.show_baseline = cyapa_gen6_show_baseline,
	.calibrate_store = cyapa_pip_करो_calibrate,

	.initialize = cyapa_gen6_initialize,

	.state_parse = cyapa_pip_state_parse,
	.operational_check = cyapa_gen6_operational_check,

	.irq_handler = cyapa_pip_irq_handler,
	.irq_cmd_handler = cyapa_pip_irq_cmd_handler,
	.sort_empty_output_data = cyapa_empty_pip_output_data,
	.set_घातer_mode = cyapa_gen6_set_घातer_mode,

	.set_proximity = cyapa_gen6_set_proximity,
पूर्ण;
