<शैली गुरु>
/*
 * Cypress APA trackpad with I2C पूर्णांकerface
 *
 * Author: Dudley Du <dudl@cypress.com>
 *
 * Copyright (C) 2014-2015 Cypress Semiconductor, Inc.
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
#समावेश <linux/pm_runसमय.स>
#समावेश "cyapa.h"


/* Macro of TSG firmware image */
#घोषणा CYAPA_TSG_FLASH_MAP_BLOCK_SIZE      0x80
#घोषणा CYAPA_TSG_IMG_FW_HDR_SIZE           13
#घोषणा CYAPA_TSG_FW_ROW_SIZE               (CYAPA_TSG_FLASH_MAP_BLOCK_SIZE)
#घोषणा CYAPA_TSG_IMG_START_ROW_NUM         0x002e
#घोषणा CYAPA_TSG_IMG_END_ROW_NUM           0x01fe
#घोषणा CYAPA_TSG_IMG_APP_INTEGRITY_ROW_NUM 0x01ff
#घोषणा CYAPA_TSG_IMG_MAX_RECORDS           (CYAPA_TSG_IMG_END_ROW_NUM - \
				CYAPA_TSG_IMG_START_ROW_NUM + 1 + 1)
#घोषणा CYAPA_TSG_IMG_READ_SIZE             (CYAPA_TSG_FLASH_MAP_BLOCK_SIZE / 2)
#घोषणा CYAPA_TSG_START_OF_APPLICATION      0x1700
#घोषणा CYAPA_TSG_APP_INTEGRITY_SIZE        60
#घोषणा CYAPA_TSG_FLASH_MAP_METADATA_SIZE   60
#घोषणा CYAPA_TSG_BL_KEY_SIZE               8

#घोषणा CYAPA_TSG_MAX_CMD_SIZE              256

/* Macro of PIP पूर्णांकerface */
#घोषणा PIP_BL_INITIATE_RESP_LEN            11
#घोषणा PIP_BL_FAIL_EXIT_RESP_LEN           11
#घोषणा PIP_BL_FAIL_EXIT_STATUS_CODE        0x0c
#घोषणा PIP_BL_VERIFY_INTEGRITY_RESP_LEN    12
#घोषणा PIP_BL_INTEGRITY_CHEKC_PASS         0x00
#घोषणा PIP_BL_BLOCK_WRITE_RESP_LEN         11

#घोषणा PIP_TOUCH_REPORT_ID         0x01
#घोषणा PIP_BTN_REPORT_ID           0x03
#घोषणा PIP_WAKEUP_EVENT_REPORT_ID  0x04
#घोषणा PIP_PUSH_BTN_REPORT_ID      0x06
#घोषणा GEN5_OLD_PUSH_BTN_REPORT_ID 0x05  /* Special क्रम old Gen5 TP. */
#घोषणा PIP_PROXIMITY_REPORT_ID     0x07

#घोषणा PIP_PROXIMITY_REPORT_SIZE	6
#घोषणा PIP_PROXIMITY_DISTANCE_OFFSET	0x05
#घोषणा PIP_PROXIMITY_DISTANCE_MASK	0x01

#घोषणा PIP_TOUCH_REPORT_HEAD_SIZE     7
#घोषणा PIP_TOUCH_REPORT_MAX_SIZE      127
#घोषणा PIP_BTN_REPORT_HEAD_SIZE       6
#घोषणा PIP_BTN_REPORT_MAX_SIZE        14
#घोषणा PIP_WAKEUP_EVENT_SIZE          4

#घोषणा PIP_NUMBER_OF_TOUCH_OFFSET  5
#घोषणा PIP_NUMBER_OF_TOUCH_MASK    0x1f
#घोषणा PIP_BUTTONS_OFFSET          5
#घोषणा PIP_BUTTONS_MASK            0x0f
#घोषणा PIP_GET_EVENT_ID(reg)       (((reg) >> 5) & 0x03)
#घोषणा PIP_GET_TOUCH_ID(reg)       ((reg) & 0x1f)
#घोषणा PIP_TOUCH_TYPE_FINGER	    0x00
#घोषणा PIP_TOUCH_TYPE_PROXIMITY    0x01
#घोषणा PIP_TOUCH_TYPE_HOVER	    0x02
#घोषणा PIP_GET_TOUCH_TYPE(reg)     ((reg) & 0x07)

#घोषणा RECORD_EVENT_NONE        0
#घोषणा RECORD_EVENT_TOUCHDOWN	 1
#घोषणा RECORD_EVENT_DISPLACE    2
#घोषणा RECORD_EVENT_LIFTOFF     3

#घोषणा PIP_SENSING_MODE_MUTUAL_CAP_FINE   0x00
#घोषणा PIP_SENSING_MODE_SELF_CAP          0x02

#घोषणा PIP_SET_PROXIMITY	0x49

/* Macro of Gen5 */
#घोषणा GEN5_BL_MAX_OUTPUT_LENGTH     0x0100
#घोषणा GEN5_APP_MAX_OUTPUT_LENGTH    0x00fe

#घोषणा GEN5_POWER_STATE_ACTIVE              0x01
#घोषणा GEN5_POWER_STATE_LOOK_FOR_TOUCH      0x02
#घोषणा GEN5_POWER_STATE_READY               0x03
#घोषणा GEN5_POWER_STATE_IDLE                0x04
#घोषणा GEN5_POWER_STATE_BTN_ONLY            0x05
#घोषणा GEN5_POWER_STATE_OFF                 0x06

#घोषणा GEN5_POWER_READY_MAX_INTRVL_TIME  50   /* Unit: ms */
#घोषणा GEN5_POWER_IDLE_MAX_INTRVL_TIME   250  /* Unit: ms */

#घोषणा GEN5_CMD_GET_PARAMETER		     0x05
#घोषणा GEN5_CMD_SET_PARAMETER		     0x06
#घोषणा GEN5_PARAMETER_ACT_INTERVL_ID        0x4d
#घोषणा GEN5_PARAMETER_ACT_INTERVL_SIZE      1
#घोषणा GEN5_PARAMETER_ACT_LFT_INTERVL_ID    0x4f
#घोषणा GEN5_PARAMETER_ACT_LFT_INTERVL_SIZE  2
#घोषणा GEN5_PARAMETER_LP_INTRVL_ID          0x4c
#घोषणा GEN5_PARAMETER_LP_INTRVL_SIZE        2

#घोषणा GEN5_PARAMETER_DISABLE_PIP_REPORT    0x08

#घोषणा GEN5_BL_REPORT_DESCRIPTOR_SIZE            0x1d
#घोषणा GEN5_BL_REPORT_DESCRIPTOR_ID              0xfe
#घोषणा GEN5_APP_REPORT_DESCRIPTOR_SIZE           0xee
#घोषणा GEN5_APP_CONTRACT_REPORT_DESCRIPTOR_SIZE  0xfa
#घोषणा GEN5_APP_REPORT_DESCRIPTOR_ID             0xf6

#घोषणा GEN5_RETRIEVE_MUTUAL_PWC_DATA        0x00
#घोषणा GEN5_RETRIEVE_SELF_CAP_PWC_DATA      0x01

#घोषणा GEN5_RETRIEVE_DATA_ELEMENT_SIZE_MASK 0x07

#घोषणा GEN5_CMD_EXECUTE_PANEL_SCAN          0x2a
#घोषणा GEN5_CMD_RETRIEVE_PANEL_SCAN         0x2b
#घोषणा GEN5_PANEL_SCAN_MUTUAL_RAW_DATA      0x00
#घोषणा GEN5_PANEL_SCAN_MUTUAL_BASELINE      0x01
#घोषणा GEN5_PANEL_SCAN_MUTUAL_DIFFCOUNT     0x02
#घोषणा GEN5_PANEL_SCAN_SELF_RAW_DATA        0x03
#घोषणा GEN5_PANEL_SCAN_SELF_BASELINE        0x04
#घोषणा GEN5_PANEL_SCAN_SELF_DIFFCOUNT       0x05

/* The offset only valid क्रम retrieve PWC and panel scan commands */
#घोषणा GEN5_RESP_DATA_STRUCTURE_OFFSET      10
#घोषणा GEN5_PWC_DATA_ELEMENT_SIZE_MASK      0x07


काष्ठा cyapa_pip_touch_record अणु
	/*
	 * Bit 7 - 3: reserved
	 * Bit 2 - 0: touch type;
	 *            0 : standard finger;
	 *            1 : proximity (Start supported in Gen5 TP).
	 *            2 : finger hover (defined, but not used yet.)
	 *            3 - 15 : reserved.
	 */
	u8 touch_type;

	/*
	 * Bit 7: indicates touch lअगरtoff status.
	 *		0 : touch is currently on the panel.
	 *		1 : touch record indicates a lअगरtoff.
	 * Bit 6 - 5: indicates an event associated with this touch instance
	 *		0 : no event
	 *		1 : touchकरोwn
	 *		2 : signअगरicant displacement (> active distance)
	 *		3 : lअगरtoff (record reports last known coordinates)
	 * Bit 4 - 0: An arbitrary ID tag associated with a finger
	 *		to allow tracking a touch as it moves around the panel.
	 */
	u8 touch_tip_event_id;

	/* Bit 7 - 0 of X-axis coordinate of the touch in pixel. */
	u8 x_lo;

	/* Bit 15 - 8 of X-axis coordinate of the touch in pixel. */
	u8 x_hi;

	/* Bit 7 - 0 of Y-axis coordinate of the touch in pixel. */
	u8 y_lo;

	/* Bit 15 - 8 of Y-axis coordinate of the touch in pixel. */
	u8 y_hi;

	/*
	 * The meaning of this value is dअगरferent when touch_type is dअगरferent.
	 * For standard finger type:
	 *	Touch पूर्णांकensity in counts, pressure value.
	 * For proximity type (Start supported in Gen5 TP):
	 *	The distance, in surface units, between the contact and
	 *	the surface.
	 **/
	u8 z;

	/*
	 * The length of the major axis of the ellipse of contact between
	 * the finger and the panel (ABS_MT_TOUCH_MAJOR).
	 */
	u8 major_axis_len;

	/*
	 * The length of the minor axis of the ellipse of contact between
	 * the finger and the panel (ABS_MT_TOUCH_MINOR).
	 */
	u8 minor_axis_len;

	/*
	 * The length of the major axis of the approaching tool.
	 * (ABS_MT_WIDTH_MAJOR)
	 */
	u8 major_tool_len;

	/*
	 * The length of the minor axis of the approaching tool.
	 * (ABS_MT_WIDTH_MINOR)
	 */
	u8 minor_tool_len;

	/*
	 * The angle between the panel vertical axis and
	 * the major axis of the contact ellipse. This value is an 8-bit
	 * चिन्हित पूर्णांकeger. The range is -127 to +127 (corresponding to
	 * -90 degree and +90 degree respectively).
	 * The positive direction is घड़ीwise from the vertical axis.
	 * If the ellipse of contact degenerates पूर्णांकo a circle,
	 * orientation is reported as 0.
	 */
	u8 orientation;
पूर्ण __packed;

काष्ठा cyapa_pip_report_data अणु
	u8 report_head[PIP_TOUCH_REPORT_HEAD_SIZE];
	काष्ठा cyapa_pip_touch_record touch_records[10];
पूर्ण __packed;

काष्ठा cyapa_tsg_bin_image_head अणु
	u8 head_size;  /* Unit: bytes, including itself. */
	u8 ttda_driver_major_version;  /* Reserved as 0. */
	u8 ttda_driver_minor_version;  /* Reserved as 0. */
	u8 fw_major_version;
	u8 fw_minor_version;
	u8 fw_revision_control_number[8];
	u8 silicon_id_hi;
	u8 silicon_id_lo;
	u8 chip_revision;
	u8 family_id;
	u8 bl_ver_maj;
	u8 bl_ver_min;
पूर्ण __packed;

काष्ठा cyapa_tsg_bin_image_data_record अणु
	u8 flash_array_id;
	__be16 row_number;
	/* The number of bytes of flash data contained in this record. */
	__be16 record_len;
	/* The flash program data. */
	u8 record_data[CYAPA_TSG_FW_ROW_SIZE];
पूर्ण __packed;

काष्ठा cyapa_tsg_bin_image अणु
	काष्ठा cyapa_tsg_bin_image_head image_head;
	काष्ठा cyapa_tsg_bin_image_data_record records[];
पूर्ण __packed;

काष्ठा pip_bl_packet_start अणु
	u8 sop;  /* Start of packet, must be 01h */
	u8 cmd_code;
	__le16 data_length;  /* Size of data parameter start from data[0] */
पूर्ण __packed;

काष्ठा pip_bl_packet_end अणु
	__le16 crc;
	u8 eop;  /* End of packet, must be 17h */
पूर्ण __packed;

काष्ठा pip_bl_cmd_head अणु
	__le16 addr;   /* Output report रेजिस्टर address, must be 0004h */
	/* Size of packet not including output report रेजिस्टर address */
	__le16 length;
	u8 report_id;  /* Bootloader output report id, must be 40h */
	u8 rsvd;  /* Reserved, must be 0 */
	काष्ठा pip_bl_packet_start packet_start;
	u8 data[];  /* Command data variable based on commands */
पूर्ण __packed;

/* Initiate bootload command data काष्ठाure. */
काष्ठा pip_bl_initiate_cmd_data अणु
	/* Key must be "A5h 01h 02h 03h FFh FEh FDh 5Ah" */
	u8 key[CYAPA_TSG_BL_KEY_SIZE];
	u8 metadata_raw_parameter[CYAPA_TSG_FLASH_MAP_METADATA_SIZE];
	__le16 metadata_crc;
पूर्ण __packed;

काष्ठा tsg_bl_metadata_row_params अणु
	__le16 size;
	__le16 maximum_size;
	__le32 app_start;
	__le16 app_len;
	__le16 app_crc;
	__le32 app_entry;
	__le32 upgrade_start;
	__le16 upgrade_len;
	__le16 entry_row_crc;
	u8 padding[36];  /* Padding data must be 0 */
	__le16 metadata_crc;  /* CRC starts at offset of 60 */
पूर्ण __packed;

/* Bootload program and verअगरy row command data काष्ठाure */
काष्ठा tsg_bl_flash_row_head अणु
	u8 flash_array_id;
	__le16 flash_row_id;
	u8 flash_data[];
पूर्ण __packed;

काष्ठा pip_app_cmd_head अणु
	__le16 addr;   /* Output report रेजिस्टर address, must be 0004h */
	/* Size of packet not including output report रेजिस्टर address */
	__le16 length;
	u8 report_id;  /* Application output report id, must be 2Fh */
	u8 rsvd;  /* Reserved, must be 0 */
	/*
	 * Bit 7: reserved, must be 0.
	 * Bit 6-0: command code.
	 */
	u8 cmd_code;
	u8 parameter_data[];  /* Parameter data variable based on cmd_code */
पूर्ण __packed;

/* Application get/set parameter command data काष्ठाure */
काष्ठा gen5_app_set_parameter_data अणु
	u8 parameter_id;
	u8 parameter_size;
	__le32 value;
पूर्ण __packed;

काष्ठा gen5_app_get_parameter_data अणु
	u8 parameter_id;
पूर्ण __packed;

काष्ठा gen5_retrieve_panel_scan_data अणु
	__le16 पढ़ो_offset;
	__le16 पढ़ो_elements;
	u8 data_id;
पूर्ण __packed;

u8 pip_पढ़ो_sys_info[] = अणु 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00, 0x02 पूर्ण;
u8 pip_bl_पढ़ो_app_info[] = अणु 0x04, 0x00, 0x0b, 0x00, 0x40, 0x00,
		0x01, 0x3c, 0x00, 0x00, 0xb0, 0x42, 0x17
	पूर्ण;

अटल u8 cyapa_pip_bl_cmd_key[] = अणु 0xa5, 0x01, 0x02, 0x03,
	0xff, 0xfe, 0xfd, 0x5a पूर्ण;

अटल पूर्णांक cyapa_pip_event_process(काष्ठा cyapa *cyapa,
				   काष्ठा cyapa_pip_report_data *report_data);

पूर्णांक cyapa_pip_cmd_state_initialize(काष्ठा cyapa *cyapa)
अणु
	काष्ठा cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;

	init_completion(&pip->cmd_पढ़ोy);
	atomic_set(&pip->cmd_issued, 0);
	mutex_init(&pip->cmd_lock);

	mutex_init(&pip->pm_stage_lock);
	pip->pm_stage = CYAPA_PM_DEACTIVE;

	pip->resp_sort_func = शून्य;
	pip->in_progress_cmd = PIP_INVALID_CMD;
	pip->resp_data = शून्य;
	pip->resp_len = शून्य;

	cyapa->dev_pwr_mode = UNINIT_PWR_MODE;
	cyapa->dev_sleep_समय = UNINIT_SLEEP_TIME;

	वापस 0;
पूर्ण

/* Return negative त्रुटि_सं, or अन्यथा the number of bytes पढ़ो. */
sमाप_प्रकार cyapa_i2c_pip_पढ़ो(काष्ठा cyapa *cyapa, u8 *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;

	अगर (size == 0)
		वापस 0;

	अगर (!buf || size > CYAPA_REG_MAP_SIZE)
		वापस -EINVAL;

	ret = i2c_master_recv(cyapa->client, buf, size);

	अगर (ret != size)
		वापस (ret < 0) ? ret : -EIO;
	वापस size;
पूर्ण

/*
 * Return a negative त्रुटि_सं code अन्यथा zero on success.
 */
sमाप_प्रकार cyapa_i2c_pip_ग_लिखो(काष्ठा cyapa *cyapa, u8 *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;

	अगर (!buf || !size)
		वापस -EINVAL;

	ret = i2c_master_send(cyapa->client, buf, size);

	अगर (ret != size)
		वापस (ret < 0) ? ret : -EIO;

	वापस 0;
पूर्ण

अटल व्योम cyapa_set_pip_pm_state(काष्ठा cyapa *cyapa,
				   क्रमागत cyapa_pm_stage pm_stage)
अणु
	काष्ठा cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;

	mutex_lock(&pip->pm_stage_lock);
	pip->pm_stage = pm_stage;
	mutex_unlock(&pip->pm_stage_lock);
पूर्ण

अटल व्योम cyapa_reset_pip_pm_state(काष्ठा cyapa *cyapa)
अणु
	काष्ठा cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;

	/* Indicates the pip->pm_stage is not valid. */
	mutex_lock(&pip->pm_stage_lock);
	pip->pm_stage = CYAPA_PM_DEACTIVE;
	mutex_unlock(&pip->pm_stage_lock);
पूर्ण

अटल क्रमागत cyapa_pm_stage cyapa_get_pip_pm_state(काष्ठा cyapa *cyapa)
अणु
	काष्ठा cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	क्रमागत cyapa_pm_stage pm_stage;

	mutex_lock(&pip->pm_stage_lock);
	pm_stage = pip->pm_stage;
	mutex_unlock(&pip->pm_stage_lock);

	वापस pm_stage;
पूर्ण

/*
 * This function is aimed to dump all not पढ़ो data in Gen5 trackpad
 * beक्रमe send any command, otherwise, the पूर्णांकerrupt line will be blocked.
 */
पूर्णांक cyapa_empty_pip_output_data(काष्ठा cyapa *cyapa,
		u8 *buf, पूर्णांक *len, cb_sort func)
अणु
	काष्ठा input_dev *input = cyapa->input;
	काष्ठा cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	क्रमागत cyapa_pm_stage pm_stage = cyapa_get_pip_pm_state(cyapa);
	पूर्णांक length;
	पूर्णांक report_count;
	पूर्णांक empty_count;
	पूर्णांक buf_len;
	पूर्णांक error;

	buf_len = 0;
	अगर (len) अणु
		buf_len = (*len < CYAPA_REG_MAP_SIZE) ?
				*len : CYAPA_REG_MAP_SIZE;
		*len = 0;
	पूर्ण

	report_count = 8;  /* max 7 pending data beक्रमe command response data */
	empty_count = 0;
	करो अणु
		/*
		 * Depending on testing in cyapa driver, there are max 5 "02 00"
		 * packets between two valid buffered data report in firmware.
		 * So in order to dump all buffered data out and
		 * make पूर्णांकerrupt line release क्रम reनिश्चित again,
		 * we must set the empty_count check value bigger than 5 to
		 * make it work. Otherwise, in some situation,
		 * the पूर्णांकerrupt line may unable to reactive again,
		 * which will cause trackpad device unable to
		 * report data any more.
		 * क्रम example, it may happen in EFT and ESD testing.
		 */
		अगर (empty_count > 5)
			वापस 0;

		error = cyapa_i2c_pip_पढ़ो(cyapa, pip->empty_buf,
				PIP_RESP_LENGTH_SIZE);
		अगर (error < 0)
			वापस error;

		length = get_unaligned_le16(pip->empty_buf);
		अगर (length == PIP_RESP_LENGTH_SIZE) अणु
			empty_count++;
			जारी;
		पूर्ण अन्यथा अगर (length > CYAPA_REG_MAP_SIZE) अणु
			/* Should not happen */
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (length == 0) अणु
			/* Application or bootloader launch data polled out. */
			length = PIP_RESP_LENGTH_SIZE;
			अगर (buf && buf_len && func &&
				func(cyapa, pip->empty_buf, length)) अणु
				length = min(buf_len, length);
				स_नकल(buf, pip->empty_buf, length);
				*len = length;
				/* Response found, success. */
				वापस 0;
			पूर्ण
			जारी;
		पूर्ण

		error = cyapa_i2c_pip_पढ़ो(cyapa, pip->empty_buf, length);
		अगर (error < 0)
			वापस error;

		report_count--;
		empty_count = 0;
		length = get_unaligned_le16(pip->empty_buf);
		अगर (length <= PIP_RESP_LENGTH_SIZE) अणु
			empty_count++;
		पूर्ण अन्यथा अगर (buf && buf_len && func &&
			func(cyapa, pip->empty_buf, length)) अणु
			length = min(buf_len, length);
			स_नकल(buf, pip->empty_buf, length);
			*len = length;
			/* Response found, success. */
			वापस 0;
		पूर्ण अन्यथा अगर (cyapa->operational &&
			   input && input_device_enabled(input) &&
			   (pm_stage == CYAPA_PM_RUNTIME_RESUME ||
			    pm_stage == CYAPA_PM_RUNTIME_SUSPEND)) अणु
			/* Parse the data and report it अगर it's valid. */
			cyapa_pip_event_process(cyapa,
			       (काष्ठा cyapa_pip_report_data *)pip->empty_buf);
		पूर्ण

		error = -EINVAL;
	पूर्ण जबतक (report_count);

	वापस error;
पूर्ण

अटल पूर्णांक cyapa_करो_i2c_pip_cmd_irq_sync(
		काष्ठा cyapa *cyapa,
		u8 *cmd, माप_प्रकार cmd_len,
		अचिन्हित दीर्घ समयout)
अणु
	काष्ठा cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	पूर्णांक error;

	/* Wait क्रम पूर्णांकerrupt to set पढ़ोy completion */
	init_completion(&pip->cmd_पढ़ोy);

	atomic_inc(&pip->cmd_issued);
	error = cyapa_i2c_pip_ग_लिखो(cyapa, cmd, cmd_len);
	अगर (error) अणु
		atomic_dec(&pip->cmd_issued);
		वापस (error < 0) ? error : -EIO;
	पूर्ण

	/* Wait क्रम पूर्णांकerrupt to indicate command is completed. */
	समयout = रुको_क्रम_completion_समयout(&pip->cmd_पढ़ोy,
				msecs_to_jअगरfies(समयout));
	अगर (समयout == 0) अणु
		atomic_dec(&pip->cmd_issued);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_करो_i2c_pip_cmd_polling(
		काष्ठा cyapa *cyapa,
		u8 *cmd, माप_प्रकार cmd_len,
		u8 *resp_data, पूर्णांक *resp_len,
		अचिन्हित दीर्घ समयout,
		cb_sort func)
अणु
	काष्ठा cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	पूर्णांक tries;
	पूर्णांक length;
	पूर्णांक error;

	atomic_inc(&pip->cmd_issued);
	error = cyapa_i2c_pip_ग_लिखो(cyapa, cmd, cmd_len);
	अगर (error) अणु
		atomic_dec(&pip->cmd_issued);
		वापस error < 0 ? error : -EIO;
	पूर्ण

	length = resp_len ? *resp_len : 0;
	अगर (resp_data && resp_len && length != 0 && func) अणु
		tries = समयout / 5;
		करो अणु
			usleep_range(3000, 5000);
			*resp_len = length;
			error = cyapa_empty_pip_output_data(cyapa,
					resp_data, resp_len, func);
			अगर (error || *resp_len == 0)
				जारी;
			अन्यथा
				अवरोध;
		पूर्ण जबतक (--tries > 0);
		अगर ((error || *resp_len == 0) || tries <= 0)
			error = error ? error : -ETIMEDOUT;
	पूर्ण

	atomic_dec(&pip->cmd_issued);
	वापस error;
पूर्ण

पूर्णांक cyapa_i2c_pip_cmd_irq_sync(
		काष्ठा cyapa *cyapa,
		u8 *cmd, पूर्णांक cmd_len,
		u8 *resp_data, पूर्णांक *resp_len,
		अचिन्हित दीर्घ समयout,
		cb_sort func,
		bool irq_mode)
अणु
	काष्ठा cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	पूर्णांक error;

	अगर (!cmd || !cmd_len)
		वापस -EINVAL;

	/* Commands must be serialized. */
	error = mutex_lock_पूर्णांकerruptible(&pip->cmd_lock);
	अगर (error)
		वापस error;

	pip->resp_sort_func = func;
	pip->resp_data = resp_data;
	pip->resp_len = resp_len;

	अगर (cmd_len >= PIP_MIN_APP_CMD_LENGTH &&
			cmd[4] == PIP_APP_CMD_REPORT_ID) अणु
		/* Application command */
		pip->in_progress_cmd = cmd[6] & 0x7f;
	पूर्ण अन्यथा अगर (cmd_len >= PIP_MIN_BL_CMD_LENGTH &&
			cmd[4] == PIP_BL_CMD_REPORT_ID) अणु
		/* Bootloader command */
		pip->in_progress_cmd = cmd[7];
	पूर्ण

	/* Send command data, रुको and पढ़ो output response data's length. */
	अगर (irq_mode) अणु
		pip->is_irq_mode = true;
		error = cyapa_करो_i2c_pip_cmd_irq_sync(cyapa, cmd, cmd_len,
							समयout);
		अगर (error == -ETIMEDOUT && resp_data &&
				resp_len && *resp_len != 0 && func) अणु
			/*
			 * For some old version, there was no पूर्णांकerrupt क्रम
			 * the command response data, so need to poll here
			 * to try to get the response data.
			 */
			error = cyapa_empty_pip_output_data(cyapa,
					resp_data, resp_len, func);
			अगर (error || *resp_len == 0)
				error = error ? error : -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		pip->is_irq_mode = false;
		error = cyapa_करो_i2c_pip_cmd_polling(cyapa, cmd, cmd_len,
				resp_data, resp_len, समयout, func);
	पूर्ण

	pip->resp_sort_func = शून्य;
	pip->resp_data = शून्य;
	pip->resp_len = शून्य;
	pip->in_progress_cmd = PIP_INVALID_CMD;

	mutex_unlock(&pip->cmd_lock);
	वापस error;
पूर्ण

bool cyapa_sort_tsg_pip_bl_resp_data(काष्ठा cyapa *cyapa,
		u8 *data, पूर्णांक len)
अणु
	अगर (!data || len < PIP_MIN_BL_RESP_LENGTH)
		वापस false;

	/* Bootloader input report id 30h */
	अगर (data[PIP_RESP_REPORT_ID_OFFSET] == PIP_BL_RESP_REPORT_ID &&
			data[PIP_RESP_RSVD_OFFSET] == PIP_RESP_RSVD_KEY &&
			data[PIP_RESP_BL_SOP_OFFSET] == PIP_SOP_KEY)
		वापस true;

	वापस false;
पूर्ण

bool cyapa_sort_tsg_pip_app_resp_data(काष्ठा cyapa *cyapa,
		u8 *data, पूर्णांक len)
अणु
	काष्ठा cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	पूर्णांक resp_len;

	अगर (!data || len < PIP_MIN_APP_RESP_LENGTH)
		वापस false;

	अगर (data[PIP_RESP_REPORT_ID_OFFSET] == PIP_APP_RESP_REPORT_ID &&
			data[PIP_RESP_RSVD_OFFSET] == PIP_RESP_RSVD_KEY) अणु
		resp_len = get_unaligned_le16(&data[PIP_RESP_LENGTH_OFFSET]);
		अगर (GET_PIP_CMD_CODE(data[PIP_RESP_APP_CMD_OFFSET]) == 0x00 &&
			resp_len == PIP_UNSUPPORTED_CMD_RESP_LENGTH &&
			data[5] == pip->in_progress_cmd) अणु
			/* Unsupported command code */
			वापस false;
		पूर्ण अन्यथा अगर (GET_PIP_CMD_CODE(data[PIP_RESP_APP_CMD_OFFSET]) ==
				pip->in_progress_cmd) अणु
			/* Correct command response received */
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool cyapa_sort_pip_application_launch_data(काष्ठा cyapa *cyapa,
		u8 *buf, पूर्णांक len)
अणु
	अगर (buf == शून्य || len < PIP_RESP_LENGTH_SIZE)
		वापस false;

	/*
	 * After reset or घातer on, trackpad device always sets to 0x00 0x00
	 * to indicate a reset or घातer on event.
	 */
	अगर (buf[0] == 0 && buf[1] == 0)
		वापस true;

	वापस false;
पूर्ण

अटल bool cyapa_sort_gen5_hid_descriptor_data(काष्ठा cyapa *cyapa,
		u8 *buf, पूर्णांक len)
अणु
	पूर्णांक resp_len;
	पूर्णांक max_output_len;

	/* Check hid descriptor. */
	अगर (len != PIP_HID_DESCRIPTOR_SIZE)
		वापस false;

	resp_len = get_unaligned_le16(&buf[PIP_RESP_LENGTH_OFFSET]);
	max_output_len = get_unaligned_le16(&buf[16]);
	अगर (resp_len == PIP_HID_DESCRIPTOR_SIZE) अणु
		अगर (buf[PIP_RESP_REPORT_ID_OFFSET] == PIP_HID_BL_REPORT_ID &&
				max_output_len == GEN5_BL_MAX_OUTPUT_LENGTH) अणु
			/* BL mode HID Descriptor */
			वापस true;
		पूर्ण अन्यथा अगर ((buf[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_HID_APP_REPORT_ID) &&
				max_output_len == GEN5_APP_MAX_OUTPUT_LENGTH) अणु
			/* APP mode HID Descriptor */
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool cyapa_sort_pip_deep_sleep_data(काष्ठा cyapa *cyapa,
		u8 *buf, पूर्णांक len)
अणु
	अगर (len == PIP_DEEP_SLEEP_RESP_LENGTH &&
		buf[PIP_RESP_REPORT_ID_OFFSET] ==
			PIP_APP_DEEP_SLEEP_REPORT_ID &&
		(buf[4] & PIP_DEEP_SLEEP_OPCODE_MASK) ==
			PIP_DEEP_SLEEP_OPCODE)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक gen5_idle_state_parse(काष्ठा cyapa *cyapa)
अणु
	u8 resp_data[PIP_HID_DESCRIPTOR_SIZE];
	पूर्णांक max_output_len;
	पूर्णांक length;
	u8 cmd[2];
	पूर्णांक ret;
	पूर्णांक error;

	/*
	 * Dump all buffered data firstly क्रम the situation
	 * when the trackpad is just घातer on the cyapa go here.
	 */
	cyapa_empty_pip_output_data(cyapa, शून्य, शून्य, शून्य);

	स_रखो(resp_data, 0, माप(resp_data));
	ret = cyapa_i2c_pip_पढ़ो(cyapa, resp_data, 3);
	अगर (ret != 3)
		वापस ret < 0 ? ret : -EIO;

	length = get_unaligned_le16(&resp_data[PIP_RESP_LENGTH_OFFSET]);
	अगर (length == PIP_RESP_LENGTH_SIZE) अणु
		/* Normal state of Gen5 with no data to response */
		cyapa->gen = CYAPA_GEN5;

		cyapa_empty_pip_output_data(cyapa, शून्य, शून्य, शून्य);

		/* Read description from trackpad device */
		cmd[0] = 0x01;
		cmd[1] = 0x00;
		length = PIP_HID_DESCRIPTOR_SIZE;
		error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
				cmd, PIP_RESP_LENGTH_SIZE,
				resp_data, &length,
				300,
				cyapa_sort_gen5_hid_descriptor_data,
				false);
		अगर (error)
			वापस error;

		length = get_unaligned_le16(
				&resp_data[PIP_RESP_LENGTH_OFFSET]);
		max_output_len = get_unaligned_le16(&resp_data[16]);
		अगर ((length == PIP_HID_DESCRIPTOR_SIZE ||
				length == PIP_RESP_LENGTH_SIZE) &&
			(resp_data[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_HID_BL_REPORT_ID) &&
			max_output_len == GEN5_BL_MAX_OUTPUT_LENGTH) अणु
			/* BL mode HID Description पढ़ो */
			cyapa->state = CYAPA_STATE_GEN5_BL;
		पूर्ण अन्यथा अगर ((length == PIP_HID_DESCRIPTOR_SIZE ||
				length == PIP_RESP_LENGTH_SIZE) &&
			(resp_data[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_HID_APP_REPORT_ID) &&
			max_output_len == GEN5_APP_MAX_OUTPUT_LENGTH) अणु
			/* APP mode HID Description पढ़ो */
			cyapa->state = CYAPA_STATE_GEN5_APP;
		पूर्ण अन्यथा अणु
			/* Should not happen!!! */
			cyapa->state = CYAPA_STATE_NO_DEVICE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gen5_hid_description_header_parse(काष्ठा cyapa *cyapa, u8 *reg_data)
अणु
	पूर्णांक length;
	u8 resp_data[32];
	पूर्णांक max_output_len;
	पूर्णांक ret;

	/* 0x20 0x00 0xF7 is Gen5 Application HID Description Header;
	 * 0x20 0x00 0xFF is Gen5 Bootloader HID Description Header.
	 *
	 * Must पढ़ो HID Description content through out,
	 * otherwise Gen5 trackpad cannot response next command
	 * or report any touch or button data.
	 */
	ret = cyapa_i2c_pip_पढ़ो(cyapa, resp_data,
			PIP_HID_DESCRIPTOR_SIZE);
	अगर (ret != PIP_HID_DESCRIPTOR_SIZE)
		वापस ret < 0 ? ret : -EIO;
	length = get_unaligned_le16(&resp_data[PIP_RESP_LENGTH_OFFSET]);
	max_output_len = get_unaligned_le16(&resp_data[16]);
	अगर (length == PIP_RESP_LENGTH_SIZE) अणु
		अगर (reg_data[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_HID_BL_REPORT_ID) अणु
			/*
			 * BL mode HID Description has been previously
			 * पढ़ो out.
			 */
			cyapa->gen = CYAPA_GEN5;
			cyapa->state = CYAPA_STATE_GEN5_BL;
		पूर्ण अन्यथा अणु
			/*
			 * APP mode HID Description has been previously
			 * पढ़ो out.
			 */
			cyapa->gen = CYAPA_GEN5;
			cyapa->state = CYAPA_STATE_GEN5_APP;
		पूर्ण
	पूर्ण अन्यथा अगर (length == PIP_HID_DESCRIPTOR_SIZE &&
			resp_data[2] == PIP_HID_BL_REPORT_ID &&
			max_output_len == GEN5_BL_MAX_OUTPUT_LENGTH) अणु
		/* BL mode HID Description पढ़ो. */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_BL;
	पूर्ण अन्यथा अगर (length == PIP_HID_DESCRIPTOR_SIZE &&
			(resp_data[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_HID_APP_REPORT_ID) &&
			max_output_len == GEN5_APP_MAX_OUTPUT_LENGTH) अणु
		/* APP mode HID Description पढ़ो. */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_APP;
	पूर्ण अन्यथा अणु
		/* Should not happen!!! */
		cyapa->state = CYAPA_STATE_NO_DEVICE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gen5_report_data_header_parse(काष्ठा cyapa *cyapa, u8 *reg_data)
अणु
	पूर्णांक length;

	length = get_unaligned_le16(&reg_data[PIP_RESP_LENGTH_OFFSET]);
	चयन (reg_data[PIP_RESP_REPORT_ID_OFFSET]) अणु
	हाल PIP_TOUCH_REPORT_ID:
		अगर (length < PIP_TOUCH_REPORT_HEAD_SIZE ||
			length > PIP_TOUCH_REPORT_MAX_SIZE)
			वापस -EINVAL;
		अवरोध;
	हाल PIP_BTN_REPORT_ID:
	हाल GEN5_OLD_PUSH_BTN_REPORT_ID:
	हाल PIP_PUSH_BTN_REPORT_ID:
		अगर (length < PIP_BTN_REPORT_HEAD_SIZE ||
			length > PIP_BTN_REPORT_MAX_SIZE)
			वापस -EINVAL;
		अवरोध;
	हाल PIP_WAKEUP_EVENT_REPORT_ID:
		अगर (length != PIP_WAKEUP_EVENT_SIZE)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	cyapa->gen = CYAPA_GEN5;
	cyapa->state = CYAPA_STATE_GEN5_APP;
	वापस 0;
पूर्ण

अटल पूर्णांक gen5_cmd_resp_header_parse(काष्ठा cyapa *cyapa, u8 *reg_data)
अणु
	काष्ठा cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	पूर्णांक length;
	पूर्णांक ret;

	/*
	 * Must पढ़ो report data through out,
	 * otherwise Gen5 trackpad cannot response next command
	 * or report any touch or button data.
	 */
	length = get_unaligned_le16(&reg_data[PIP_RESP_LENGTH_OFFSET]);
	ret = cyapa_i2c_pip_पढ़ो(cyapa, pip->empty_buf, length);
	अगर (ret != length)
		वापस ret < 0 ? ret : -EIO;

	अगर (length == PIP_RESP_LENGTH_SIZE) अणु
		/* Previous command has पढ़ो the data through out. */
		अगर (reg_data[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_BL_RESP_REPORT_ID) अणु
			/* Gen5 BL command response data detected */
			cyapa->gen = CYAPA_GEN5;
			cyapa->state = CYAPA_STATE_GEN5_BL;
		पूर्ण अन्यथा अणु
			/* Gen5 APP command response data detected */
			cyapa->gen = CYAPA_GEN5;
			cyapa->state = CYAPA_STATE_GEN5_APP;
		पूर्ण
	पूर्ण अन्यथा अगर ((pip->empty_buf[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_BL_RESP_REPORT_ID) &&
			(pip->empty_buf[PIP_RESP_RSVD_OFFSET] ==
				PIP_RESP_RSVD_KEY) &&
			(pip->empty_buf[PIP_RESP_BL_SOP_OFFSET] ==
				PIP_SOP_KEY) &&
			(pip->empty_buf[length - 1] ==
				PIP_EOP_KEY)) अणु
		/* Gen5 BL command response data detected */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_BL;
	पूर्ण अन्यथा अगर (pip->empty_buf[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_APP_RESP_REPORT_ID &&
			pip->empty_buf[PIP_RESP_RSVD_OFFSET] ==
				PIP_RESP_RSVD_KEY) अणु
		/* Gen5 APP command response data detected */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_APP;
	पूर्ण अन्यथा अणु
		/* Should not happen!!! */
		cyapa->state = CYAPA_STATE_NO_DEVICE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen5_state_parse(काष्ठा cyapa *cyapa, u8 *reg_data, पूर्णांक len)
अणु
	पूर्णांक length;

	अगर (!reg_data || len < 3)
		वापस -EINVAL;

	cyapa->state = CYAPA_STATE_NO_DEVICE;

	/* Parse based on Gen5 अक्षरacteristic रेजिस्टरs and bits */
	length = get_unaligned_le16(&reg_data[PIP_RESP_LENGTH_OFFSET]);
	अगर (length == 0 || length == PIP_RESP_LENGTH_SIZE) अणु
		gen5_idle_state_parse(cyapa);
	पूर्ण अन्यथा अगर (length == PIP_HID_DESCRIPTOR_SIZE &&
			(reg_data[2] == PIP_HID_BL_REPORT_ID ||
				reg_data[2] == PIP_HID_APP_REPORT_ID)) अणु
		gen5_hid_description_header_parse(cyapa, reg_data);
	पूर्ण अन्यथा अगर ((length == GEN5_APP_REPORT_DESCRIPTOR_SIZE ||
			length == GEN5_APP_CONTRACT_REPORT_DESCRIPTOR_SIZE) &&
			reg_data[2] == GEN5_APP_REPORT_DESCRIPTOR_ID) अणु
		/* 0xEE 0x00 0xF6 is Gen5 APP report description header. */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_APP;
	पूर्ण अन्यथा अगर (length == GEN5_BL_REPORT_DESCRIPTOR_SIZE &&
			reg_data[2] == GEN5_BL_REPORT_DESCRIPTOR_ID) अणु
		/* 0x1D 0x00 0xFE is Gen5 BL report descriptor header. */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_BL;
	पूर्ण अन्यथा अगर (reg_data[2] == PIP_TOUCH_REPORT_ID ||
			reg_data[2] == PIP_BTN_REPORT_ID ||
			reg_data[2] == GEN5_OLD_PUSH_BTN_REPORT_ID ||
			reg_data[2] == PIP_PUSH_BTN_REPORT_ID ||
			reg_data[2] == PIP_WAKEUP_EVENT_REPORT_ID) अणु
		gen5_report_data_header_parse(cyapa, reg_data);
	पूर्ण अन्यथा अगर (reg_data[2] == PIP_BL_RESP_REPORT_ID ||
			reg_data[2] == PIP_APP_RESP_REPORT_ID) अणु
		gen5_cmd_resp_header_parse(cyapa, reg_data);
	पूर्ण

	अगर (cyapa->gen == CYAPA_GEN5) अणु
		/*
		 * Must पढ़ो the content (e.g.: report description and so on)
		 * from trackpad device throughout. Otherwise,
		 * Gen5 trackpad cannot response to next command or
		 * report any touch or button data later.
		 */
		cyapa_empty_pip_output_data(cyapa, शून्य, शून्य, शून्य);

		अगर (cyapa->state == CYAPA_STATE_GEN5_APP ||
			cyapa->state == CYAPA_STATE_GEN5_BL)
			वापस 0;
	पूर्ण

	वापस -EAGAIN;
पूर्ण

अटल काष्ठा cyapa_tsg_bin_image_data_record *
cyapa_get_image_record_data_num(स्थिर काष्ठा firmware *fw,
		पूर्णांक *record_num)
अणु
	पूर्णांक head_size;

	head_size = fw->data[0] + 1;
	*record_num = (fw->size - head_size) /
			माप(काष्ठा cyapa_tsg_bin_image_data_record);
	वापस (काष्ठा cyapa_tsg_bin_image_data_record *)&fw->data[head_size];
पूर्ण

पूर्णांक cyapa_pip_bl_initiate(काष्ठा cyapa *cyapa, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा cyapa_tsg_bin_image_data_record *image_records;
	काष्ठा pip_bl_cmd_head *bl_cmd_head;
	काष्ठा pip_bl_packet_start *bl_packet_start;
	काष्ठा pip_bl_initiate_cmd_data *cmd_data;
	काष्ठा pip_bl_packet_end *bl_packet_end;
	u8 cmd[CYAPA_TSG_MAX_CMD_SIZE];
	पूर्णांक cmd_len;
	u16 cmd_data_len;
	u16 cmd_crc = 0;
	u16 meta_data_crc = 0;
	u8 resp_data[11];
	पूर्णांक resp_len;
	पूर्णांक records_num;
	u8 *data;
	पूर्णांक error;

	/* Try to dump all buffered report data beक्रमe any send command. */
	cyapa_empty_pip_output_data(cyapa, शून्य, शून्य, शून्य);

	स_रखो(cmd, 0, CYAPA_TSG_MAX_CMD_SIZE);
	bl_cmd_head = (काष्ठा pip_bl_cmd_head *)cmd;
	cmd_data_len = CYAPA_TSG_BL_KEY_SIZE + CYAPA_TSG_FLASH_MAP_BLOCK_SIZE;
	cmd_len = माप(काष्ठा pip_bl_cmd_head) + cmd_data_len +
		  माप(काष्ठा pip_bl_packet_end);

	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &bl_cmd_head->addr);
	put_unaligned_le16(cmd_len - 2, &bl_cmd_head->length);
	bl_cmd_head->report_id = PIP_BL_CMD_REPORT_ID;

	bl_packet_start = &bl_cmd_head->packet_start;
	bl_packet_start->sop = PIP_SOP_KEY;
	bl_packet_start->cmd_code = PIP_BL_CMD_INITIATE_BL;
	/* 8 key bytes and 128 bytes block size */
	put_unaligned_le16(cmd_data_len, &bl_packet_start->data_length);

	cmd_data = (काष्ठा pip_bl_initiate_cmd_data *)bl_cmd_head->data;
	स_नकल(cmd_data->key, cyapa_pip_bl_cmd_key, CYAPA_TSG_BL_KEY_SIZE);

	image_records = cyapa_get_image_record_data_num(fw, &records_num);

	/* APP_INTEGRITY row is always the last row block */
	data = image_records[records_num - 1].record_data;
	स_नकल(cmd_data->metadata_raw_parameter, data,
		CYAPA_TSG_FLASH_MAP_METADATA_SIZE);

	meta_data_crc = crc_itu_t(0xffff, cmd_data->metadata_raw_parameter,
				CYAPA_TSG_FLASH_MAP_METADATA_SIZE);
	put_unaligned_le16(meta_data_crc, &cmd_data->metadata_crc);

	bl_packet_end = (काष्ठा pip_bl_packet_end *)(bl_cmd_head->data +
				cmd_data_len);
	cmd_crc = crc_itu_t(0xffff, (u8 *)bl_packet_start,
		माप(काष्ठा pip_bl_packet_start) + cmd_data_len);
	put_unaligned_le16(cmd_crc, &bl_packet_end->crc);
	bl_packet_end->eop = PIP_EOP_KEY;

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, cmd_len,
			resp_data, &resp_len, 12000,
			cyapa_sort_tsg_pip_bl_resp_data, true);
	अगर (error || resp_len != PIP_BL_INITIATE_RESP_LEN ||
			resp_data[2] != PIP_BL_RESP_REPORT_ID ||
			!PIP_CMD_COMPLETE_SUCCESS(resp_data))
		वापस error ? error : -EAGAIN;

	वापस 0;
पूर्ण

अटल bool cyapa_sort_pip_bl_निकास_data(काष्ठा cyapa *cyapa, u8 *buf, पूर्णांक len)
अणु
	अगर (buf == शून्य || len < PIP_RESP_LENGTH_SIZE)
		वापस false;

	अगर (buf[0] == 0 && buf[1] == 0)
		वापस true;

	/* Exit bootloader failed क्रम some reason. */
	अगर (len == PIP_BL_FAIL_EXIT_RESP_LEN &&
			buf[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_BL_RESP_REPORT_ID &&
			buf[PIP_RESP_RSVD_OFFSET] == PIP_RESP_RSVD_KEY &&
			buf[PIP_RESP_BL_SOP_OFFSET] == PIP_SOP_KEY &&
			buf[10] == PIP_EOP_KEY)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक cyapa_pip_bl_निकास(काष्ठा cyapa *cyapa)
अणु

	u8 bl_gen5_bl_निकास[] = अणु 0x04, 0x00,
		0x0B, 0x00, 0x40, 0x00, 0x01, 0x3b, 0x00, 0x00,
		0x20, 0xc7, 0x17
	पूर्ण;
	u8 resp_data[11];
	पूर्णांक resp_len;
	पूर्णांक error;

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			bl_gen5_bl_निकास, माप(bl_gen5_bl_निकास),
			resp_data, &resp_len,
			5000, cyapa_sort_pip_bl_निकास_data, false);
	अगर (error)
		वापस error;

	अगर (resp_len == PIP_BL_FAIL_EXIT_RESP_LEN ||
			resp_data[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_BL_RESP_REPORT_ID)
		वापस -EAGAIN;

	अगर (resp_data[0] == 0x00 && resp_data[1] == 0x00)
		वापस 0;

	वापस -ENODEV;
पूर्ण

पूर्णांक cyapa_pip_bl_enter(काष्ठा cyapa *cyapa)
अणु
	u8 cmd[] = अणु 0x04, 0x00, 0x05, 0x00, 0x2F, 0x00, 0x01 पूर्ण;
	u8 resp_data[2];
	पूर्णांक resp_len;
	पूर्णांक error;

	error = cyapa_poll_state(cyapa, 500);
	अगर (error < 0)
		वापस error;

	/* Alपढ़ोy in bootloader mode, Skipping निकास. */
	अगर (cyapa_is_pip_bl_mode(cyapa))
		वापस 0;
	अन्यथा अगर (!cyapa_is_pip_app_mode(cyapa))
		वापस -EINVAL;

	/* Try to dump all buffered report data beक्रमe any send command. */
	cyapa_empty_pip_output_data(cyapa, शून्य, शून्य, शून्य);

	/*
	 * Send bootloader enter command to trackpad device,
	 * after enter bootloader, the response data is two bytes of 0x00 0x00.
	 */
	resp_len = माप(resp_data);
	स_रखो(resp_data, 0, resp_len);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, माप(cmd),
			resp_data, &resp_len,
			5000, cyapa_sort_pip_application_launch_data,
			true);
	अगर (error || resp_data[0] != 0x00 || resp_data[1] != 0x00)
		वापस error < 0 ? error : -EAGAIN;

	cyapa->operational = false;
	अगर (cyapa->gen == CYAPA_GEN5)
		cyapa->state = CYAPA_STATE_GEN5_BL;
	अन्यथा अगर (cyapa->gen == CYAPA_GEN6)
		cyapa->state = CYAPA_STATE_GEN6_BL;
	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_pip_fw_head_check(काष्ठा cyapa *cyapa,
		काष्ठा cyapa_tsg_bin_image_head *image_head)
अणु
	अगर (image_head->head_size != 0x0C && image_head->head_size != 0x12)
		वापस -EINVAL;

	चयन (cyapa->gen) अणु
	हाल CYAPA_GEN6:
		अगर (image_head->family_id != 0x9B ||
		    image_head->silicon_id_hi != 0x0B)
			वापस -EINVAL;
		अवरोध;
	हाल CYAPA_GEN5:
		/* Gen5 without proximity support. */
		अगर (cyapa->platक्रमm_ver < 2) अणु
			अगर (image_head->head_size == 0x0C)
				अवरोध;
			वापस -EINVAL;
		पूर्ण

		अगर (image_head->family_id != 0x91 ||
		    image_head->silicon_id_hi != 0x02)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cyapa_pip_check_fw(काष्ठा cyapa *cyapa, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	काष्ठा cyapa_tsg_bin_image_data_record *image_records;
	स्थिर काष्ठा cyapa_tsg_bin_image_data_record *app_पूर्णांकegrity;
	स्थिर काष्ठा tsg_bl_metadata_row_params *metadata;
	पूर्णांक flash_records_count;
	u32 fw_app_start, fw_upgrade_start;
	u16 fw_app_len, fw_upgrade_len;
	u16 app_crc;
	u16 app_पूर्णांकegrity_crc;
	पूर्णांक i;

	/* Verअगरy the firmware image not miss-used क्रम Gen5 and Gen6. */
	अगर (cyapa_pip_fw_head_check(cyapa,
		(काष्ठा cyapa_tsg_bin_image_head *)fw->data)) अणु
		dev_err(dev, "%s: firmware image not match TP device.\n",
			     __func__);
		वापस -EINVAL;
	पूर्ण

	image_records =
		cyapa_get_image_record_data_num(fw, &flash_records_count);

	/*
	 * APP_INTEGRITY row is always the last row block,
	 * and the row id must be 0x01ff.
	 */
	app_पूर्णांकegrity = &image_records[flash_records_count - 1];

	अगर (app_पूर्णांकegrity->flash_array_id != 0x00 ||
	    get_unaligned_be16(&app_पूर्णांकegrity->row_number) != 0x01ff) अणु
		dev_err(dev, "%s: invalid app_integrity data.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	metadata = (स्थिर व्योम *)app_पूर्णांकegrity->record_data;

	/* Verअगरy app_पूर्णांकegrity crc */
	app_पूर्णांकegrity_crc = crc_itu_t(0xffff, app_पूर्णांकegrity->record_data,
				      CYAPA_TSG_APP_INTEGRITY_SIZE);
	अगर (app_पूर्णांकegrity_crc != get_unaligned_le16(&metadata->metadata_crc)) अणु
		dev_err(dev, "%s: invalid app_integrity crc.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	fw_app_start = get_unaligned_le32(&metadata->app_start);
	fw_app_len = get_unaligned_le16(&metadata->app_len);
	fw_upgrade_start = get_unaligned_le32(&metadata->upgrade_start);
	fw_upgrade_len = get_unaligned_le16(&metadata->upgrade_len);

	अगर (fw_app_start % CYAPA_TSG_FW_ROW_SIZE ||
	    fw_app_len % CYAPA_TSG_FW_ROW_SIZE ||
	    fw_upgrade_start % CYAPA_TSG_FW_ROW_SIZE ||
	    fw_upgrade_len % CYAPA_TSG_FW_ROW_SIZE) अणु
		dev_err(dev, "%s: invalid image alignment.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Verअगरy application image CRC. */
	app_crc = 0xffffU;
	क्रम (i = 0; i < fw_app_len / CYAPA_TSG_FW_ROW_SIZE; i++) अणु
		स्थिर u8 *data = image_records[i].record_data;

		app_crc = crc_itu_t(app_crc, data, CYAPA_TSG_FW_ROW_SIZE);
	पूर्ण

	अगर (app_crc != get_unaligned_le16(&metadata->app_crc)) अणु
		dev_err(dev, "%s: invalid firmware app crc check.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_pip_ग_लिखो_fw_block(काष्ठा cyapa *cyapa,
		काष्ठा cyapa_tsg_bin_image_data_record *flash_record)
अणु
	काष्ठा pip_bl_cmd_head *bl_cmd_head;
	काष्ठा pip_bl_packet_start *bl_packet_start;
	काष्ठा tsg_bl_flash_row_head *flash_row_head;
	काष्ठा pip_bl_packet_end *bl_packet_end;
	u8 cmd[CYAPA_TSG_MAX_CMD_SIZE];
	u16 cmd_len;
	u8 flash_array_id;
	u16 flash_row_id;
	u16 record_len;
	u8 *record_data;
	u16 data_len;
	u16 crc;
	u8 resp_data[11];
	पूर्णांक resp_len;
	पूर्णांक error;

	flash_array_id = flash_record->flash_array_id;
	flash_row_id = get_unaligned_be16(&flash_record->row_number);
	record_len = get_unaligned_be16(&flash_record->record_len);
	record_data = flash_record->record_data;

	स_रखो(cmd, 0, CYAPA_TSG_MAX_CMD_SIZE);
	bl_cmd_head = (काष्ठा pip_bl_cmd_head *)cmd;
	bl_packet_start = &bl_cmd_head->packet_start;
	cmd_len = माप(काष्ठा pip_bl_cmd_head) +
		  माप(काष्ठा tsg_bl_flash_row_head) +
		  CYAPA_TSG_FLASH_MAP_BLOCK_SIZE +
		  माप(काष्ठा pip_bl_packet_end);

	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &bl_cmd_head->addr);
	/* Don't include 2 bytes रेजिस्टर address */
	put_unaligned_le16(cmd_len - 2, &bl_cmd_head->length);
	bl_cmd_head->report_id = PIP_BL_CMD_REPORT_ID;
	bl_packet_start->sop = PIP_SOP_KEY;
	bl_packet_start->cmd_code = PIP_BL_CMD_PROGRAM_VERIFY_ROW;

	/* 1 (Flash Array ID) + 2 (Flash Row ID) + 128 (flash data) */
	data_len = माप(काष्ठा tsg_bl_flash_row_head) + record_len;
	put_unaligned_le16(data_len, &bl_packet_start->data_length);

	flash_row_head = (काष्ठा tsg_bl_flash_row_head *)bl_cmd_head->data;
	flash_row_head->flash_array_id = flash_array_id;
	put_unaligned_le16(flash_row_id, &flash_row_head->flash_row_id);
	स_नकल(flash_row_head->flash_data, record_data, record_len);

	bl_packet_end = (काष्ठा pip_bl_packet_end *)(bl_cmd_head->data +
						      data_len);
	crc = crc_itu_t(0xffff, (u8 *)bl_packet_start,
		माप(काष्ठा pip_bl_packet_start) + data_len);
	put_unaligned_le16(crc, &bl_packet_end->crc);
	bl_packet_end->eop = PIP_EOP_KEY;

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa, cmd, cmd_len,
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_bl_resp_data, true);
	अगर (error || resp_len != PIP_BL_BLOCK_WRITE_RESP_LEN ||
			resp_data[2] != PIP_BL_RESP_REPORT_ID ||
			!PIP_CMD_COMPLETE_SUCCESS(resp_data))
		वापस error < 0 ? error : -EAGAIN;

	वापस 0;
पूर्ण

पूर्णांक cyapa_pip_करो_fw_update(काष्ठा cyapa *cyapa,
		स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	काष्ठा cyapa_tsg_bin_image_data_record *image_records;
	पूर्णांक flash_records_count;
	पूर्णांक i;
	पूर्णांक error;

	cyapa_empty_pip_output_data(cyapa, शून्य, शून्य, शून्य);

	image_records =
		cyapa_get_image_record_data_num(fw, &flash_records_count);

	/*
	 * The last flash row 0x01ff has been written through bl_initiate
	 * command, so DO NOT ग_लिखो flash 0x01ff to trackpad device.
	 */
	क्रम (i = 0; i < (flash_records_count - 1); i++) अणु
		error = cyapa_pip_ग_लिखो_fw_block(cyapa, &image_records[i]);
		अगर (error) अणु
			dev_err(dev, "%s: Gen5 FW update aborted: %d\n",
				__func__, error);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen5_change_घातer_state(काष्ठा cyapa *cyapa, u8 घातer_state)
अणु
	u8 cmd[8] = अणु 0x04, 0x00, 0x06, 0x00, 0x2f, 0x00, 0x08, 0x01 पूर्ण;
	u8 resp_data[6];
	पूर्णांक resp_len;
	पूर्णांक error;

	cmd[7] = घातer_state;
	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa, cmd, माप(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, false);
	अगर (error || !VALID_CMD_RESP_HEADER(resp_data, 0x08) ||
			!PIP_CMD_COMPLETE_SUCCESS(resp_data))
		वापस error < 0 ? error : -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen5_set_पूर्णांकerval_समय(काष्ठा cyapa *cyapa,
		u8 parameter_id, u16 पूर्णांकerval_समय)
अणु
	काष्ठा pip_app_cmd_head *app_cmd_head;
	काष्ठा gen5_app_set_parameter_data *parameter_data;
	u8 cmd[CYAPA_TSG_MAX_CMD_SIZE];
	पूर्णांक cmd_len;
	u8 resp_data[7];
	पूर्णांक resp_len;
	u8 parameter_size;
	पूर्णांक error;

	स_रखो(cmd, 0, CYAPA_TSG_MAX_CMD_SIZE);
	app_cmd_head = (काष्ठा pip_app_cmd_head *)cmd;
	parameter_data = (काष्ठा gen5_app_set_parameter_data *)
			 app_cmd_head->parameter_data;
	cmd_len = माप(काष्ठा pip_app_cmd_head) +
		  माप(काष्ठा gen5_app_set_parameter_data);

	चयन (parameter_id) अणु
	हाल GEN5_PARAMETER_ACT_INTERVL_ID:
		parameter_size = GEN5_PARAMETER_ACT_INTERVL_SIZE;
		अवरोध;
	हाल GEN5_PARAMETER_ACT_LFT_INTERVL_ID:
		parameter_size = GEN5_PARAMETER_ACT_LFT_INTERVL_SIZE;
		अवरोध;
	हाल GEN5_PARAMETER_LP_INTRVL_ID:
		parameter_size = GEN5_PARAMETER_LP_INTRVL_SIZE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &app_cmd_head->addr);
	/*
	 * Don't include unused parameter value bytes and
	 * 2 bytes रेजिस्टर address.
	 */
	put_unaligned_le16(cmd_len - (4 - parameter_size) - 2,
			   &app_cmd_head->length);
	app_cmd_head->report_id = PIP_APP_CMD_REPORT_ID;
	app_cmd_head->cmd_code = GEN5_CMD_SET_PARAMETER;
	parameter_data->parameter_id = parameter_id;
	parameter_data->parameter_size = parameter_size;
	put_unaligned_le32((u32)पूर्णांकerval_समय, &parameter_data->value);
	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa, cmd, cmd_len,
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, false);
	अगर (error || resp_data[5] != parameter_id ||
		resp_data[6] != parameter_size ||
		!VALID_CMD_RESP_HEADER(resp_data, GEN5_CMD_SET_PARAMETER))
		वापस error < 0 ? error : -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen5_get_पूर्णांकerval_समय(काष्ठा cyapa *cyapa,
		u8 parameter_id, u16 *पूर्णांकerval_समय)
अणु
	काष्ठा pip_app_cmd_head *app_cmd_head;
	काष्ठा gen5_app_get_parameter_data *parameter_data;
	u8 cmd[CYAPA_TSG_MAX_CMD_SIZE];
	पूर्णांक cmd_len;
	u8 resp_data[11];
	पूर्णांक resp_len;
	u8 parameter_size;
	u16 mask, i;
	पूर्णांक error;

	स_रखो(cmd, 0, CYAPA_TSG_MAX_CMD_SIZE);
	app_cmd_head = (काष्ठा pip_app_cmd_head *)cmd;
	parameter_data = (काष्ठा gen5_app_get_parameter_data *)
			 app_cmd_head->parameter_data;
	cmd_len = माप(काष्ठा pip_app_cmd_head) +
		  माप(काष्ठा gen5_app_get_parameter_data);

	*पूर्णांकerval_समय = 0;
	चयन (parameter_id) अणु
	हाल GEN5_PARAMETER_ACT_INTERVL_ID:
		parameter_size = GEN5_PARAMETER_ACT_INTERVL_SIZE;
		अवरोध;
	हाल GEN5_PARAMETER_ACT_LFT_INTERVL_ID:
		parameter_size = GEN5_PARAMETER_ACT_LFT_INTERVL_SIZE;
		अवरोध;
	हाल GEN5_PARAMETER_LP_INTRVL_ID:
		parameter_size = GEN5_PARAMETER_LP_INTRVL_SIZE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &app_cmd_head->addr);
	/* Don't include 2 bytes रेजिस्टर address */
	put_unaligned_le16(cmd_len - 2, &app_cmd_head->length);
	app_cmd_head->report_id = PIP_APP_CMD_REPORT_ID;
	app_cmd_head->cmd_code = GEN5_CMD_GET_PARAMETER;
	parameter_data->parameter_id = parameter_id;

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa, cmd, cmd_len,
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, false);
	अगर (error || resp_data[5] != parameter_id || resp_data[6] == 0 ||
		!VALID_CMD_RESP_HEADER(resp_data, GEN5_CMD_GET_PARAMETER))
		वापस error < 0 ? error : -EINVAL;

	mask = 0;
	क्रम (i = 0; i < parameter_size; i++)
		mask |= (0xff << (i * 8));
	*पूर्णांकerval_समय = get_unaligned_le16(&resp_data[7]) & mask;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen5_disable_pip_report(काष्ठा cyapa *cyapa)
अणु
	काष्ठा pip_app_cmd_head *app_cmd_head;
	u8 cmd[10];
	u8 resp_data[7];
	पूर्णांक resp_len;
	पूर्णांक error;

	स_रखो(cmd, 0, माप(cmd));
	app_cmd_head = (काष्ठा pip_app_cmd_head *)cmd;

	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &app_cmd_head->addr);
	put_unaligned_le16(माप(cmd) - 2, &app_cmd_head->length);
	app_cmd_head->report_id = PIP_APP_CMD_REPORT_ID;
	app_cmd_head->cmd_code = GEN5_CMD_SET_PARAMETER;
	app_cmd_head->parameter_data[0] = GEN5_PARAMETER_DISABLE_PIP_REPORT;
	app_cmd_head->parameter_data[1] = 0x01;
	app_cmd_head->parameter_data[2] = 0x01;
	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa, cmd, माप(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, false);
	अगर (error || resp_data[5] != GEN5_PARAMETER_DISABLE_PIP_REPORT ||
		!VALID_CMD_RESP_HEADER(resp_data, GEN5_CMD_SET_PARAMETER) ||
		resp_data[6] != 0x01)
		वापस error < 0 ? error : -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक cyapa_pip_set_proximity(काष्ठा cyapa *cyapa, bool enable)
अणु
	u8 cmd[] = अणु 0x04, 0x00, 0x06, 0x00, 0x2f, 0x00, PIP_SET_PROXIMITY,
		     (u8)!!enable
	पूर्ण;
	u8 resp_data[6];
	पूर्णांक resp_len;
	पूर्णांक error;

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa, cmd, माप(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, false);
	अगर (error || !VALID_CMD_RESP_HEADER(resp_data, PIP_SET_PROXIMITY) ||
			!PIP_CMD_COMPLETE_SUCCESS(resp_data)) अणु
		error = (error == -ETIMEDOUT) ? -EOPNOTSUPP : error;
		वापस error < 0 ? error : -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cyapa_pip_deep_sleep(काष्ठा cyapa *cyapa, u8 state)
अणु
	u8 cmd[] = अणु 0x05, 0x00, 0x00, 0x08पूर्ण;
	u8 resp_data[5];
	पूर्णांक resp_len;
	पूर्णांक error;

	cmd[2] = state & PIP_DEEP_SLEEP_STATE_MASK;
	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa, cmd, माप(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_pip_deep_sleep_data, false);
	अगर (error || ((resp_data[3] & PIP_DEEP_SLEEP_STATE_MASK) != state))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen5_set_घातer_mode(काष्ठा cyapa *cyapa,
		u8 घातer_mode, u16 sleep_समय, क्रमागत cyapa_pm_stage pm_stage)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	u8 घातer_state;
	पूर्णांक error = 0;

	अगर (cyapa->state != CYAPA_STATE_GEN5_APP)
		वापस 0;

	cyapa_set_pip_pm_state(cyapa, pm_stage);

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
		अगर (cyapa_gen5_get_पूर्णांकerval_समय(cyapa,
				GEN5_PARAMETER_LP_INTRVL_ID,
				&cyapa->dev_sleep_समय) != 0)
			PIP_DEV_SET_SLEEP_TIME(cyapa, UNINIT_SLEEP_TIME);

	अगर (PIP_DEV_GET_PWR_STATE(cyapa) == घातer_mode) अणु
		अगर (घातer_mode == PWR_MODE_OFF ||
			घातer_mode == PWR_MODE_FULL_ACTIVE ||
			घातer_mode == PWR_MODE_BTN_ONLY ||
			PIP_DEV_GET_SLEEP_TIME(cyapa) == sleep_समय) अणु
			/* Has in correct घातer mode state, early वापस. */
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (घातer_mode == PWR_MODE_OFF) अणु
		error = cyapa_pip_deep_sleep(cyapa, PIP_DEEP_SLEEP_STATE_OFF);
		अगर (error) अणु
			dev_err(dev, "enter deep sleep fail: %d\n", error);
			जाओ out;
		पूर्ण

		PIP_DEV_SET_PWR_STATE(cyapa, PWR_MODE_OFF);
		जाओ out;
	पूर्ण

	/*
	 * When trackpad in घातer off mode, it cannot change to other घातer
	 * state directly, must be wake up from sleep firstly, then
	 * जारी to करो next घातer sate change.
	 */
	अगर (PIP_DEV_GET_PWR_STATE(cyapa) == PWR_MODE_OFF) अणु
		error = cyapa_pip_deep_sleep(cyapa, PIP_DEEP_SLEEP_STATE_ON);
		अगर (error) अणु
			dev_err(dev, "deep sleep wake fail: %d\n", error);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (घातer_mode == PWR_MODE_FULL_ACTIVE) अणु
		error = cyapa_gen5_change_घातer_state(cyapa,
				GEN5_POWER_STATE_ACTIVE);
		अगर (error) अणु
			dev_err(dev, "change to active fail: %d\n", error);
			जाओ out;
		पूर्ण

		PIP_DEV_SET_PWR_STATE(cyapa, PWR_MODE_FULL_ACTIVE);
	पूर्ण अन्यथा अगर (घातer_mode == PWR_MODE_BTN_ONLY) अणु
		error = cyapa_gen5_change_घातer_state(cyapa,
				GEN5_POWER_STATE_BTN_ONLY);
		अगर (error) अणु
			dev_err(dev, "fail to button only mode: %d\n", error);
			जाओ out;
		पूर्ण

		PIP_DEV_SET_PWR_STATE(cyapa, PWR_MODE_BTN_ONLY);
	पूर्ण अन्यथा अणु
		/*
		 * Continue to change घातer mode even failed to set
		 * पूर्णांकerval समय, it won't affect the घातer mode change.
		 * except the sleep पूर्णांकerval समय is not correct.
		 */
		अगर (PIP_DEV_UNINIT_SLEEP_TIME(cyapa) ||
				sleep_समय != PIP_DEV_GET_SLEEP_TIME(cyapa))
			अगर (cyapa_gen5_set_पूर्णांकerval_समय(cyapa,
					GEN5_PARAMETER_LP_INTRVL_ID,
					sleep_समय) == 0)
				PIP_DEV_SET_SLEEP_TIME(cyapa, sleep_समय);

		अगर (sleep_समय <= GEN5_POWER_READY_MAX_INTRVL_TIME)
			घातer_state = GEN5_POWER_STATE_READY;
		अन्यथा
			घातer_state = GEN5_POWER_STATE_IDLE;
		error = cyapa_gen5_change_घातer_state(cyapa, घातer_state);
		अगर (error) अणु
			dev_err(dev, "set power state to 0x%02x failed: %d\n",
				घातer_state, error);
			जाओ out;
		पूर्ण

		/*
		 * Disable pip report क्रम a little समय, firmware will
		 * re-enable it स्वतःmatically. It's used to fix the issue
		 * that trackpad unable to report संकेत to wake प्रणाली up
		 * in the special situation that प्रणाली is in suspending, and
		 * at the same समय, user touch trackpad to wake प्रणाली up.
		 * This function can aव्योम the data to be buffered when प्रणाली
		 * is suspending which may cause पूर्णांकerrupt line unable to be
		 * निश्चितed again.
		 */
		अगर (pm_stage == CYAPA_PM_SUSPEND)
			cyapa_gen5_disable_pip_report(cyapa);

		PIP_DEV_SET_PWR_STATE(cyapa,
			cyapa_sleep_समय_प्रकारo_pwr_cmd(sleep_समय));
	पूर्ण

out:
	cyapa_reset_pip_pm_state(cyapa);
	वापस error;
पूर्ण

पूर्णांक cyapa_pip_resume_scanning(काष्ठा cyapa *cyapa)
अणु
	u8 cmd[] = अणु 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00, 0x04 पूर्ण;
	u8 resp_data[6];
	पूर्णांक resp_len;
	पूर्णांक error;

	/* Try to dump all buffered data beक्रमe करोing command. */
	cyapa_empty_pip_output_data(cyapa, शून्य, शून्य, शून्य);

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, माप(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, true);
	अगर (error || !VALID_CMD_RESP_HEADER(resp_data, 0x04))
		वापस -EINVAL;

	/* Try to dump all buffered data when resuming scanning. */
	cyapa_empty_pip_output_data(cyapa, शून्य, शून्य, शून्य);

	वापस 0;
पूर्ण

पूर्णांक cyapa_pip_suspend_scanning(काष्ठा cyapa *cyapa)
अणु
	u8 cmd[] = अणु 0x04, 0x00, 0x05, 0x00, 0x2f, 0x00, 0x03 पूर्ण;
	u8 resp_data[6];
	पूर्णांक resp_len;
	पूर्णांक error;

	/* Try to dump all buffered data beक्रमe करोing command. */
	cyapa_empty_pip_output_data(cyapa, शून्य, शून्य, शून्य);

	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, माप(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, true);
	अगर (error || !VALID_CMD_RESP_HEADER(resp_data, 0x03))
		वापस -EINVAL;

	/* Try to dump all buffered data when suspending scanning. */
	cyapa_empty_pip_output_data(cyapa, शून्य, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_pip_calibrate_pwcs(काष्ठा cyapa *cyapa,
		u8 calibrate_sensing_mode_type)
अणु
	काष्ठा pip_app_cmd_head *app_cmd_head;
	u8 cmd[8];
	u8 resp_data[6];
	पूर्णांक resp_len;
	पूर्णांक error;

	/* Try to dump all buffered data beक्रमe करोing command. */
	cyapa_empty_pip_output_data(cyapa, शून्य, शून्य, शून्य);

	स_रखो(cmd, 0, माप(cmd));
	app_cmd_head = (काष्ठा pip_app_cmd_head *)cmd;
	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &app_cmd_head->addr);
	put_unaligned_le16(माप(cmd) - 2, &app_cmd_head->length);
	app_cmd_head->report_id = PIP_APP_CMD_REPORT_ID;
	app_cmd_head->cmd_code = PIP_CMD_CALIBRATE;
	app_cmd_head->parameter_data[0] = calibrate_sensing_mode_type;
	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, माप(cmd),
			resp_data, &resp_len,
			5000, cyapa_sort_tsg_pip_app_resp_data, true);
	अगर (error || !VALID_CMD_RESP_HEADER(resp_data, PIP_CMD_CALIBRATE) ||
			!PIP_CMD_COMPLETE_SUCCESS(resp_data))
		वापस error < 0 ? error : -EAGAIN;

	वापस 0;
पूर्ण

sमाप_प्रकार cyapa_pip_करो_calibrate(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	पूर्णांक error, calibrate_error;

	/* 1. Suspend Scanning*/
	error = cyapa_pip_suspend_scanning(cyapa);
	अगर (error)
		वापस error;

	/* 2. Do mutual capacitance fine calibrate. */
	calibrate_error = cyapa_pip_calibrate_pwcs(cyapa,
				PIP_SENSING_MODE_MUTUAL_CAP_FINE);
	अगर (calibrate_error)
		जाओ resume_scanning;

	/* 3. Do self capacitance calibrate. */
	calibrate_error = cyapa_pip_calibrate_pwcs(cyapa,
				PIP_SENSING_MODE_SELF_CAP);
	अगर (calibrate_error)
		जाओ resume_scanning;

resume_scanning:
	/* 4. Resume Scanning*/
	error = cyapa_pip_resume_scanning(cyapa);
	अगर (error || calibrate_error)
		वापस error ? error : calibrate_error;

	वापस count;
पूर्ण

अटल s32 twos_complement_to_s32(s32 value, पूर्णांक num_bits)
अणु
	अगर (value >> (num_bits - 1))
		value |=  -1 << num_bits;
	वापस value;
पूर्ण

अटल s32 cyapa_parse_काष्ठाure_data(u8 data_क्रमmat, u8 *buf, पूर्णांक buf_len)
अणु
	पूर्णांक data_size;
	bool big_endian;
	bool अचिन्हित_type;
	s32 value;

	data_size = (data_क्रमmat & 0x07);
	big_endian = ((data_क्रमmat & 0x10) == 0x00);
	अचिन्हित_type = ((data_क्रमmat & 0x20) == 0x00);

	अगर (buf_len < data_size)
		वापस 0;

	चयन (data_size) अणु
	हाल 1:
		value  = buf[0];
		अवरोध;
	हाल 2:
		अगर (big_endian)
			value = get_unaligned_be16(buf);
		अन्यथा
			value = get_unaligned_le16(buf);
		अवरोध;
	हाल 4:
		अगर (big_endian)
			value = get_unaligned_be32(buf);
		अन्यथा
			value = get_unaligned_le32(buf);
		अवरोध;
	शेष:
		/* Should not happen, just as शेष हाल here. */
		value = 0;
		अवरोध;
	पूर्ण

	अगर (!अचिन्हित_type)
		value = twos_complement_to_s32(value, data_size * 8);

	वापस value;
पूर्ण

अटल व्योम cyapa_gen5_guess_electrodes(काष्ठा cyapa *cyapa,
		पूर्णांक *electrodes_rx, पूर्णांक *electrodes_tx)
अणु
	अगर (cyapa->electrodes_rx != 0) अणु
		*electrodes_rx = cyapa->electrodes_rx;
		*electrodes_tx = (cyapa->electrodes_x == *electrodes_rx) ?
				cyapa->electrodes_y : cyapa->electrodes_x;
	पूर्ण अन्यथा अणु
		*electrodes_tx = min(cyapa->electrodes_x, cyapa->electrodes_y);
		*electrodes_rx = max(cyapa->electrodes_x, cyapa->electrodes_y);
	पूर्ण
पूर्ण

/*
 * Read all the global mutual or self idac data or mutual or self local PWC
 * data based on the @idac_data_type.
 * If the input value of @data_size is 0, then means पढ़ो global mutual or
 * self idac data. For पढ़ो global mutual idac data, @idac_max, @idac_min and
 * @idac_ave are in order used to वापस the max value of global mutual idac
 * data, the min value of global mutual idac and the average value of the
 * global mutual idac data. For पढ़ो global self idac data, @idac_max is used
 * to वापस the global self cap idac data in Rx direction, @idac_min is used
 * to वापस the global self cap idac data in Tx direction. @idac_ave is not
 * used.
 * If the input value of @data_size is not 0, than means पढ़ो the mutual or
 * self local PWC data. The @idac_max, @idac_min and @idac_ave are used to
 * वापस the max, min and average value of the mutual or self local PWC data.
 * Note, in order to पढ़ो mutual local PWC data, must पढ़ो invoke this function
 * to पढ़ो the mutual global idac data firstly to set the correct Rx number
 * value, otherwise, the पढ़ो mutual idac and PWC data may not correct.
 */
अटल पूर्णांक cyapa_gen5_पढ़ो_idac_data(काष्ठा cyapa *cyapa,
		u8 cmd_code, u8 idac_data_type, पूर्णांक *data_size,
		पूर्णांक *idac_max, पूर्णांक *idac_min, पूर्णांक *idac_ave)
अणु
	काष्ठा pip_app_cmd_head *cmd_head;
	u8 cmd[12];
	u8 resp_data[256];
	पूर्णांक resp_len;
	पूर्णांक पढ़ो_len;
	पूर्णांक value;
	u16 offset;
	पूर्णांक पढ़ो_elements;
	bool पढ़ो_global_idac;
	पूर्णांक sum, count, max_element_cnt;
	पूर्णांक पंचांगp_max, पंचांगp_min, पंचांगp_ave, पंचांगp_sum, पंचांगp_count;
	पूर्णांक electrodes_rx, electrodes_tx;
	पूर्णांक i;
	पूर्णांक error;

	अगर (cmd_code != PIP_RETRIEVE_DATA_STRUCTURE ||
		(idac_data_type != GEN5_RETRIEVE_MUTUAL_PWC_DATA &&
		idac_data_type != GEN5_RETRIEVE_SELF_CAP_PWC_DATA) ||
		!data_size || !idac_max || !idac_min || !idac_ave)
		वापस -EINVAL;

	*idac_max = पूर्णांक_न्यून;
	*idac_min = पूर्णांक_उच्च;
	sum = count = पंचांगp_count = 0;
	electrodes_rx = electrodes_tx = 0;
	अगर (*data_size == 0) अणु
		/*
		 * Read global idac values firstly.
		 * Currently, no idac data exceed 4 bytes.
		 */
		पढ़ो_global_idac = true;
		offset = 0;
		*data_size = 4;
		पंचांगp_max = पूर्णांक_न्यून;
		पंचांगp_min = पूर्णांक_उच्च;
		पंचांगp_ave = पंचांगp_sum = पंचांगp_count = 0;

		अगर (idac_data_type == GEN5_RETRIEVE_MUTUAL_PWC_DATA) अणु
			अगर (cyapa->aligned_electrodes_rx == 0) अणु
				cyapa_gen5_guess_electrodes(cyapa,
					&electrodes_rx, &electrodes_tx);
				cyapa->aligned_electrodes_rx =
					(electrodes_rx + 3) & ~3u;
			पूर्ण
			max_element_cnt =
				(cyapa->aligned_electrodes_rx + 7) & ~7u;
		पूर्ण अन्यथा अणु
			max_element_cnt = 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		पढ़ो_global_idac = false;
		अगर (*data_size > 4)
			*data_size = 4;
		/* Calculate the start offset in bytes of local PWC data. */
		अगर (idac_data_type == GEN5_RETRIEVE_MUTUAL_PWC_DATA) अणु
			offset = cyapa->aligned_electrodes_rx * (*data_size);
			अगर (cyapa->electrodes_rx == cyapa->electrodes_x)
				electrodes_tx = cyapa->electrodes_y;
			अन्यथा
				electrodes_tx = cyapa->electrodes_x;
			max_element_cnt = ((cyapa->aligned_electrodes_rx + 7) &
						~7u) * electrodes_tx;
		पूर्ण अन्यथा अणु
			offset = 2;
			max_element_cnt = cyapa->electrodes_x +
						cyapa->electrodes_y;
			max_element_cnt = (max_element_cnt + 3) & ~3u;
		पूर्ण
	पूर्ण

	स_रखो(cmd, 0, माप(cmd));
	cmd_head = (काष्ठा pip_app_cmd_head *)cmd;
	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &cmd_head->addr);
	put_unaligned_le16(माप(cmd) - 2, &cmd_head->length);
	cmd_head->report_id = PIP_APP_CMD_REPORT_ID;
	cmd_head->cmd_code = cmd_code;
	करो अणु
		पढ़ो_elements = (256 - GEN5_RESP_DATA_STRUCTURE_OFFSET) /
				(*data_size);
		पढ़ो_elements = min(पढ़ो_elements, max_element_cnt - count);
		पढ़ो_len = पढ़ो_elements * (*data_size);

		put_unaligned_le16(offset, &cmd_head->parameter_data[0]);
		put_unaligned_le16(पढ़ो_len, &cmd_head->parameter_data[2]);
		cmd_head->parameter_data[4] = idac_data_type;
		resp_len = GEN5_RESP_DATA_STRUCTURE_OFFSET + पढ़ो_len;
		error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
				cmd, माप(cmd),
				resp_data, &resp_len,
				500, cyapa_sort_tsg_pip_app_resp_data,
				true);
		अगर (error || resp_len < GEN5_RESP_DATA_STRUCTURE_OFFSET ||
				!VALID_CMD_RESP_HEADER(resp_data, cmd_code) ||
				!PIP_CMD_COMPLETE_SUCCESS(resp_data) ||
				resp_data[6] != idac_data_type)
			वापस (error < 0) ? error : -EAGAIN;
		पढ़ो_len = get_unaligned_le16(&resp_data[7]);
		अगर (पढ़ो_len == 0)
			अवरोध;

		*data_size = (resp_data[9] & GEN5_PWC_DATA_ELEMENT_SIZE_MASK);
		अगर (पढ़ो_len < *data_size)
			वापस -EINVAL;

		अगर (पढ़ो_global_idac &&
			idac_data_type == GEN5_RETRIEVE_SELF_CAP_PWC_DATA) अणु
			/* Rx's self global idac data. */
			*idac_max = cyapa_parse_काष्ठाure_data(
				resp_data[9],
				&resp_data[GEN5_RESP_DATA_STRUCTURE_OFFSET],
				*data_size);
			/* Tx's self global idac data. */
			*idac_min = cyapa_parse_काष्ठाure_data(
				resp_data[9],
				&resp_data[GEN5_RESP_DATA_STRUCTURE_OFFSET +
					   *data_size],
				*data_size);
			अवरोध;
		पूर्ण

		/* Read mutual global idac or local mutual/self PWC data. */
		offset += पढ़ो_len;
		क्रम (i = 10; i < (पढ़ो_len + GEN5_RESP_DATA_STRUCTURE_OFFSET);
				i += *data_size) अणु
			value = cyapa_parse_काष्ठाure_data(resp_data[9],
					&resp_data[i], *data_size);
			*idac_min = min(value, *idac_min);
			*idac_max = max(value, *idac_max);

			अगर (idac_data_type == GEN5_RETRIEVE_MUTUAL_PWC_DATA &&
				पंचांगp_count < cyapa->aligned_electrodes_rx &&
				पढ़ो_global_idac) अणु
				/*
				 * The value gap between global and local mutual
				 * idac data must bigger than 50%.
				 * Normally, global value bigger than 50,
				 * local values less than 10.
				 */
				अगर (!पंचांगp_ave || value > पंचांगp_ave / 2) अणु
					पंचांगp_min = min(value, पंचांगp_min);
					पंचांगp_max = max(value, पंचांगp_max);
					पंचांगp_sum += value;
					पंचांगp_count++;

					पंचांगp_ave = पंचांगp_sum / पंचांगp_count;
				पूर्ण
			पूर्ण

			sum += value;
			count++;

			अगर (count >= max_element_cnt)
				जाओ out;
		पूर्ण
	पूर्ण जबतक (true);

out:
	*idac_ave = count ? (sum / count) : 0;

	अगर (पढ़ो_global_idac &&
		idac_data_type == GEN5_RETRIEVE_MUTUAL_PWC_DATA) अणु
		अगर (पंचांगp_count == 0)
			वापस 0;

		अगर (पंचांगp_count == cyapa->aligned_electrodes_rx) अणु
			cyapa->electrodes_rx = cyapa->electrodes_rx ?
				cyapa->electrodes_rx : electrodes_rx;
		पूर्ण अन्यथा अगर (पंचांगp_count == electrodes_rx) अणु
			cyapa->electrodes_rx = cyapa->electrodes_rx ?
				cyapa->electrodes_rx : electrodes_rx;
			cyapa->aligned_electrodes_rx = electrodes_rx;
		पूर्ण अन्यथा अणु
			cyapa->electrodes_rx = cyapa->electrodes_rx ?
				cyapa->electrodes_rx : electrodes_tx;
			cyapa->aligned_electrodes_rx = पंचांगp_count;
		पूर्ण

		*idac_min = पंचांगp_min;
		*idac_max = पंचांगp_max;
		*idac_ave = पंचांगp_ave;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen5_पढ़ो_mutual_idac_data(काष्ठा cyapa *cyapa,
	पूर्णांक *gidac_mutual_max, पूर्णांक *gidac_mutual_min, पूर्णांक *gidac_mutual_ave,
	पूर्णांक *lidac_mutual_max, पूर्णांक *lidac_mutual_min, पूर्णांक *lidac_mutual_ave)
अणु
	पूर्णांक data_size;
	पूर्णांक error;

	*gidac_mutual_max = *gidac_mutual_min = *gidac_mutual_ave = 0;
	*lidac_mutual_max = *lidac_mutual_min = *lidac_mutual_ave = 0;

	data_size = 0;
	error = cyapa_gen5_पढ़ो_idac_data(cyapa,
		PIP_RETRIEVE_DATA_STRUCTURE,
		GEN5_RETRIEVE_MUTUAL_PWC_DATA,
		&data_size,
		gidac_mutual_max, gidac_mutual_min, gidac_mutual_ave);
	अगर (error)
		वापस error;

	error = cyapa_gen5_पढ़ो_idac_data(cyapa,
		PIP_RETRIEVE_DATA_STRUCTURE,
		GEN5_RETRIEVE_MUTUAL_PWC_DATA,
		&data_size,
		lidac_mutual_max, lidac_mutual_min, lidac_mutual_ave);
	वापस error;
पूर्ण

अटल पूर्णांक cyapa_gen5_पढ़ो_self_idac_data(काष्ठा cyapa *cyapa,
		पूर्णांक *gidac_self_rx, पूर्णांक *gidac_self_tx,
		पूर्णांक *lidac_self_max, पूर्णांक *lidac_self_min, पूर्णांक *lidac_self_ave)
अणु
	पूर्णांक data_size;
	पूर्णांक error;

	*gidac_self_rx = *gidac_self_tx = 0;
	*lidac_self_max = *lidac_self_min = *lidac_self_ave = 0;

	data_size = 0;
	error = cyapa_gen5_पढ़ो_idac_data(cyapa,
		PIP_RETRIEVE_DATA_STRUCTURE,
		GEN5_RETRIEVE_SELF_CAP_PWC_DATA,
		&data_size,
		lidac_self_max, lidac_self_min, lidac_self_ave);
	अगर (error)
		वापस error;
	*gidac_self_rx = *lidac_self_max;
	*gidac_self_tx = *lidac_self_min;

	error = cyapa_gen5_पढ़ो_idac_data(cyapa,
		PIP_RETRIEVE_DATA_STRUCTURE,
		GEN5_RETRIEVE_SELF_CAP_PWC_DATA,
		&data_size,
		lidac_self_max, lidac_self_min, lidac_self_ave);
	वापस error;
पूर्ण

अटल sमाप_प्रकार cyapa_gen5_execute_panel_scan(काष्ठा cyapa *cyapa)
अणु
	काष्ठा pip_app_cmd_head *app_cmd_head;
	u8 cmd[7];
	u8 resp_data[6];
	पूर्णांक resp_len;
	पूर्णांक error;

	स_रखो(cmd, 0, माप(cmd));
	app_cmd_head = (काष्ठा pip_app_cmd_head *)cmd;
	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &app_cmd_head->addr);
	put_unaligned_le16(माप(cmd) - 2, &app_cmd_head->length);
	app_cmd_head->report_id = PIP_APP_CMD_REPORT_ID;
	app_cmd_head->cmd_code = GEN5_CMD_EXECUTE_PANEL_SCAN;
	resp_len = माप(resp_data);
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, माप(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, true);
	अगर (error || resp_len != माप(resp_data) ||
			!VALID_CMD_RESP_HEADER(resp_data,
				GEN5_CMD_EXECUTE_PANEL_SCAN) ||
			!PIP_CMD_COMPLETE_SUCCESS(resp_data))
		वापस error ? error : -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen5_पढ़ो_panel_scan_raw_data(काष्ठा cyapa *cyapa,
		u8 cmd_code, u8 raw_data_type, पूर्णांक raw_data_max_num,
		पूर्णांक *raw_data_max, पूर्णांक *raw_data_min, पूर्णांक *raw_data_ave,
		u8 *buffer)
अणु
	काष्ठा pip_app_cmd_head *app_cmd_head;
	काष्ठा gen5_retrieve_panel_scan_data *panel_sacn_data;
	u8 cmd[12];
	u8 resp_data[256];  /* Max bytes can transfer one समय. */
	पूर्णांक resp_len;
	पूर्णांक पढ़ो_elements;
	पूर्णांक पढ़ो_len;
	u16 offset;
	s32 value;
	पूर्णांक sum, count;
	पूर्णांक data_size;
	s32 *पूर्णांकp;
	पूर्णांक i;
	पूर्णांक error;

	अगर (cmd_code != GEN5_CMD_RETRIEVE_PANEL_SCAN ||
		(raw_data_type > GEN5_PANEL_SCAN_SELF_DIFFCOUNT) ||
		!raw_data_max || !raw_data_min || !raw_data_ave)
		वापस -EINVAL;

	पूर्णांकp = (s32 *)buffer;
	*raw_data_max = पूर्णांक_न्यून;
	*raw_data_min = पूर्णांक_उच्च;
	sum = count = 0;
	offset = 0;
	/* Assume max element size is 4 currently. */
	पढ़ो_elements = (256 - GEN5_RESP_DATA_STRUCTURE_OFFSET) / 4;
	पढ़ो_len = पढ़ो_elements * 4;
	app_cmd_head = (काष्ठा pip_app_cmd_head *)cmd;
	put_unaligned_le16(PIP_OUTPUT_REPORT_ADDR, &app_cmd_head->addr);
	put_unaligned_le16(माप(cmd) - 2, &app_cmd_head->length);
	app_cmd_head->report_id = PIP_APP_CMD_REPORT_ID;
	app_cmd_head->cmd_code = cmd_code;
	panel_sacn_data = (काष्ठा gen5_retrieve_panel_scan_data *)
			app_cmd_head->parameter_data;
	करो अणु
		put_unaligned_le16(offset, &panel_sacn_data->पढ़ो_offset);
		put_unaligned_le16(पढ़ो_elements,
			&panel_sacn_data->पढ़ो_elements);
		panel_sacn_data->data_id = raw_data_type;

		resp_len = GEN5_RESP_DATA_STRUCTURE_OFFSET + पढ़ो_len;
		error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, माप(cmd),
			resp_data, &resp_len,
			500, cyapa_sort_tsg_pip_app_resp_data, true);
		अगर (error || resp_len < GEN5_RESP_DATA_STRUCTURE_OFFSET ||
				!VALID_CMD_RESP_HEADER(resp_data, cmd_code) ||
				!PIP_CMD_COMPLETE_SUCCESS(resp_data) ||
				resp_data[6] != raw_data_type)
			वापस error ? error : -EAGAIN;

		पढ़ो_elements = get_unaligned_le16(&resp_data[7]);
		अगर (पढ़ो_elements == 0)
			अवरोध;

		data_size = (resp_data[9] & GEN5_PWC_DATA_ELEMENT_SIZE_MASK);
		offset += पढ़ो_elements;
		अगर (पढ़ो_elements) अणु
			क्रम (i = GEN5_RESP_DATA_STRUCTURE_OFFSET;
			     i < (पढ़ो_elements * data_size +
					GEN5_RESP_DATA_STRUCTURE_OFFSET);
			     i += data_size) अणु
				value = cyapa_parse_काष्ठाure_data(resp_data[9],
						&resp_data[i], data_size);
				*raw_data_min = min(value, *raw_data_min);
				*raw_data_max = max(value, *raw_data_max);

				अगर (पूर्णांकp)
					put_unaligned_le32(value, &पूर्णांकp[count]);

				sum += value;
				count++;

			पूर्ण
		पूर्ण

		अगर (count >= raw_data_max_num)
			अवरोध;

		पढ़ो_elements = (माप(resp_data) -
				GEN5_RESP_DATA_STRUCTURE_OFFSET) / data_size;
		पढ़ो_len = पढ़ो_elements * data_size;
	पूर्ण जबतक (true);

	*raw_data_ave = count ? (sum / count) : 0;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार cyapa_gen5_show_baseline(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cyapa *cyapa = dev_get_drvdata(dev);
	पूर्णांक gidac_mutual_max, gidac_mutual_min, gidac_mutual_ave;
	पूर्णांक lidac_mutual_max, lidac_mutual_min, lidac_mutual_ave;
	पूर्णांक gidac_self_rx, gidac_self_tx;
	पूर्णांक lidac_self_max, lidac_self_min, lidac_self_ave;
	पूर्णांक raw_cap_mutual_max, raw_cap_mutual_min, raw_cap_mutual_ave;
	पूर्णांक raw_cap_self_max, raw_cap_self_min, raw_cap_self_ave;
	पूर्णांक mutual_dअगरfdata_max, mutual_dअगरfdata_min, mutual_dअगरfdata_ave;
	पूर्णांक self_dअगरfdata_max, self_dअगरfdata_min, self_dअगरfdata_ave;
	पूर्णांक mutual_baseline_max, mutual_baseline_min, mutual_baseline_ave;
	पूर्णांक self_baseline_max, self_baseline_min, self_baseline_ave;
	पूर्णांक error, resume_error;
	पूर्णांक size;

	अगर (!cyapa_is_pip_app_mode(cyapa))
		वापस -EBUSY;

	/* 1. Suspend Scanning*/
	error = cyapa_pip_suspend_scanning(cyapa);
	अगर (error)
		वापस error;

	/* 2.  Read global and local mutual IDAC data. */
	gidac_self_rx = gidac_self_tx = 0;
	error = cyapa_gen5_पढ़ो_mutual_idac_data(cyapa,
				&gidac_mutual_max, &gidac_mutual_min,
				&gidac_mutual_ave, &lidac_mutual_max,
				&lidac_mutual_min, &lidac_mutual_ave);
	अगर (error)
		जाओ resume_scanning;

	/* 3.  Read global and local self IDAC data. */
	error = cyapa_gen5_पढ़ो_self_idac_data(cyapa,
				&gidac_self_rx, &gidac_self_tx,
				&lidac_self_max, &lidac_self_min,
				&lidac_self_ave);
	अगर (error)
		जाओ resume_scanning;

	/* 4. Execute panel scan. It must be executed beक्रमe पढ़ो data. */
	error = cyapa_gen5_execute_panel_scan(cyapa);
	अगर (error)
		जाओ resume_scanning;

	/* 5. Retrieve panel scan, mutual cap raw data. */
	error = cyapa_gen5_पढ़ो_panel_scan_raw_data(cyapa,
				GEN5_CMD_RETRIEVE_PANEL_SCAN,
				GEN5_PANEL_SCAN_MUTUAL_RAW_DATA,
				cyapa->electrodes_x * cyapa->electrodes_y,
				&raw_cap_mutual_max, &raw_cap_mutual_min,
				&raw_cap_mutual_ave,
				शून्य);
	अगर (error)
		जाओ resume_scanning;

	/* 6. Retrieve panel scan, self cap raw data. */
	error = cyapa_gen5_पढ़ो_panel_scan_raw_data(cyapa,
				GEN5_CMD_RETRIEVE_PANEL_SCAN,
				GEN5_PANEL_SCAN_SELF_RAW_DATA,
				cyapa->electrodes_x + cyapa->electrodes_y,
				&raw_cap_self_max, &raw_cap_self_min,
				&raw_cap_self_ave,
				शून्य);
	अगर (error)
		जाओ resume_scanning;

	/* 7. Retrieve panel scan, mutual cap dअगरfcount raw data. */
	error = cyapa_gen5_पढ़ो_panel_scan_raw_data(cyapa,
				GEN5_CMD_RETRIEVE_PANEL_SCAN,
				GEN5_PANEL_SCAN_MUTUAL_DIFFCOUNT,
				cyapa->electrodes_x * cyapa->electrodes_y,
				&mutual_dअगरfdata_max, &mutual_dअगरfdata_min,
				&mutual_dअगरfdata_ave,
				शून्य);
	अगर (error)
		जाओ resume_scanning;

	/* 8. Retrieve panel scan, self cap dअगरfcount raw data. */
	error = cyapa_gen5_पढ़ो_panel_scan_raw_data(cyapa,
				GEN5_CMD_RETRIEVE_PANEL_SCAN,
				GEN5_PANEL_SCAN_SELF_DIFFCOUNT,
				cyapa->electrodes_x + cyapa->electrodes_y,
				&self_dअगरfdata_max, &self_dअगरfdata_min,
				&self_dअगरfdata_ave,
				शून्य);
	अगर (error)
		जाओ resume_scanning;

	/* 9. Retrieve panel scan, mutual cap baseline raw data. */
	error = cyapa_gen5_पढ़ो_panel_scan_raw_data(cyapa,
				GEN5_CMD_RETRIEVE_PANEL_SCAN,
				GEN5_PANEL_SCAN_MUTUAL_BASELINE,
				cyapa->electrodes_x * cyapa->electrodes_y,
				&mutual_baseline_max, &mutual_baseline_min,
				&mutual_baseline_ave,
				शून्य);
	अगर (error)
		जाओ resume_scanning;

	/* 10. Retrieve panel scan, self cap baseline raw data. */
	error = cyapa_gen5_पढ़ो_panel_scan_raw_data(cyapa,
				GEN5_CMD_RETRIEVE_PANEL_SCAN,
				GEN5_PANEL_SCAN_SELF_BASELINE,
				cyapa->electrodes_x + cyapa->electrodes_y,
				&self_baseline_max, &self_baseline_min,
				&self_baseline_ave,
				शून्य);
	अगर (error)
		जाओ resume_scanning;

resume_scanning:
	/* 11. Resume Scanning*/
	resume_error = cyapa_pip_resume_scanning(cyapa);
	अगर (resume_error || error)
		वापस resume_error ? resume_error : error;

	/* 12. Output data strings */
	size = scnम_लिखो(buf, PAGE_SIZE, "%d %d %d %d %d %d %d %d %d %d %d ",
		gidac_mutual_min, gidac_mutual_max, gidac_mutual_ave,
		lidac_mutual_min, lidac_mutual_max, lidac_mutual_ave,
		gidac_self_rx, gidac_self_tx,
		lidac_self_min, lidac_self_max, lidac_self_ave);
	size += scnम_लिखो(buf + size, PAGE_SIZE - size,
		"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
		raw_cap_mutual_min, raw_cap_mutual_max, raw_cap_mutual_ave,
		raw_cap_self_min, raw_cap_self_max, raw_cap_self_ave,
		mutual_dअगरfdata_min, mutual_dअगरfdata_max, mutual_dअगरfdata_ave,
		self_dअगरfdata_min, self_dअगरfdata_max, self_dअगरfdata_ave,
		mutual_baseline_min, mutual_baseline_max, mutual_baseline_ave,
		self_baseline_min, self_baseline_max, self_baseline_ave);
	वापस size;
पूर्ण

bool cyapa_pip_sort_प्रणाली_info_data(काष्ठा cyapa *cyapa,
		u8 *buf, पूर्णांक len)
अणु
	/* Check the report id and command code */
	अगर (VALID_CMD_RESP_HEADER(buf, 0x02))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक cyapa_gen5_bl_query_data(काष्ठा cyapa *cyapa)
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

	स_नकल(&cyapa->product_id[0], &resp_data[8], 5);
	cyapa->product_id[5] = '-';
	स_नकल(&cyapa->product_id[6], &resp_data[13], 6);
	cyapa->product_id[12] = '-';
	स_नकल(&cyapa->product_id[13], &resp_data[19], 2);
	cyapa->product_id[15] = '\0';

	cyapa->fw_maj_ver = resp_data[22];
	cyapa->fw_min_ver = resp_data[23];

	cyapa->platक्रमm_ver = (resp_data[26] >> PIP_BL_PLATFORM_VER_SHIFT) &
			      PIP_BL_PLATFORM_VER_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen5_get_query_data(काष्ठा cyapa *cyapa)
अणु
	u8 resp_data[PIP_READ_SYS_INFO_RESP_LENGTH];
	पूर्णांक resp_len;
	u16 product_family;
	पूर्णांक error;

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

	cyapa->platक्रमm_ver = (resp_data[49] >> PIP_BL_PLATFORM_VER_SHIFT) &
			      PIP_BL_PLATFORM_VER_MASK;
	अगर (cyapa->gen == CYAPA_GEN5 && cyapa->platक्रमm_ver < 2) अणु
		/* Gen5 firmware that करोes not support proximity. */
		cyapa->fw_maj_ver = resp_data[15];
		cyapa->fw_min_ver = resp_data[16];
	पूर्ण अन्यथा अणु
		cyapa->fw_maj_ver = resp_data[9];
		cyapa->fw_min_ver = resp_data[10];
	पूर्ण

	cyapa->electrodes_x = resp_data[52];
	cyapa->electrodes_y = resp_data[53];

	cyapa->physical_size_x =  get_unaligned_le16(&resp_data[54]) / 100;
	cyapa->physical_size_y = get_unaligned_le16(&resp_data[56]) / 100;

	cyapa->max_असल_x = get_unaligned_le16(&resp_data[58]);
	cyapa->max_असल_y = get_unaligned_le16(&resp_data[60]);

	cyapa->max_z = get_unaligned_le16(&resp_data[62]);

	cyapa->x_origin = resp_data[64] & 0x01;
	cyapa->y_origin = resp_data[65] & 0x01;

	cyapa->btn_capability = (resp_data[70] << 3) & CAPABILITY_BTN_MASK;

	स_नकल(&cyapa->product_id[0], &resp_data[33], 5);
	cyapa->product_id[5] = '-';
	स_नकल(&cyapa->product_id[6], &resp_data[38], 6);
	cyapa->product_id[12] = '-';
	स_नकल(&cyapa->product_id[13], &resp_data[44], 2);
	cyapa->product_id[15] = '\0';

	अगर (!cyapa->electrodes_x || !cyapa->electrodes_y ||
		!cyapa->physical_size_x || !cyapa->physical_size_y ||
		!cyapa->max_असल_x || !cyapa->max_असल_y || !cyapa->max_z)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cyapa_gen5_करो_operational_check(काष्ठा cyapa *cyapa)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	पूर्णांक error;

	अगर (cyapa->gen != CYAPA_GEN5)
		वापस -ENODEV;

	चयन (cyapa->state) अणु
	हाल CYAPA_STATE_GEN5_BL:
		error = cyapa_pip_bl_निकास(cyapa);
		अगर (error) अणु
			/* Try to update trackpad product inक्रमmation. */
			cyapa_gen5_bl_query_data(cyapa);
			जाओ out;
		पूर्ण

		cyapa->state = CYAPA_STATE_GEN5_APP;
		fallthrough;

	हाल CYAPA_STATE_GEN5_APP:
		/*
		 * If trackpad device in deep sleep mode,
		 * the app command will fail.
		 * So always try to reset trackpad device to full active when
		 * the device state is required.
		 */
		error = cyapa_gen5_set_घातer_mode(cyapa,
				PWR_MODE_FULL_ACTIVE, 0, CYAPA_PM_ACTIVE);
		अगर (error)
			dev_warn(dev, "%s: failed to set power active mode.\n",
				__func__);

		/* By शेष, the trackpad proximity function is enabled. */
		अगर (cyapa->platक्रमm_ver >= 2) अणु
			error = cyapa_pip_set_proximity(cyapa, true);
			अगर (error)
				dev_warn(dev,
					"%s: failed to enable proximity.\n",
					__func__);
		पूर्ण

		/* Get trackpad product inक्रमmation. */
		error = cyapa_gen5_get_query_data(cyapa);
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

/*
 * Return false, करो not जारी process
 * Return true, जारी process.
 */
bool cyapa_pip_irq_cmd_handler(काष्ठा cyapa *cyapa)
अणु
	काष्ठा cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	पूर्णांक length;

	अगर (atomic_पढ़ो(&pip->cmd_issued)) अणु
		/* Polling command response data. */
		अगर (pip->is_irq_mode == false)
			वापस false;

		/*
		 * Read out all none command response data.
		 * these output data may caused by user put finger on
		 * trackpad when host रुकोing the command response.
		 */
		cyapa_i2c_pip_पढ़ो(cyapa, pip->irq_cmd_buf,
			PIP_RESP_LENGTH_SIZE);
		length = get_unaligned_le16(pip->irq_cmd_buf);
		length = (length <= PIP_RESP_LENGTH_SIZE) ?
				PIP_RESP_LENGTH_SIZE : length;
		अगर (length > PIP_RESP_LENGTH_SIZE)
			cyapa_i2c_pip_पढ़ो(cyapa,
				pip->irq_cmd_buf, length);
		अगर (!(pip->resp_sort_func &&
			pip->resp_sort_func(cyapa,
				pip->irq_cmd_buf, length))) अणु
			/*
			 * Cover the Gen5 V1 firmware issue.
			 * The issue is no पूर्णांकerrupt would be निश्चितed from
			 * trackpad device to host क्रम the command response
			 * पढ़ोy event. Because when there was a finger touch
			 * on trackpad device, and the firmware output queue
			 * won't be empty (always with touch report data), so
			 * the पूर्णांकerrupt संकेत won't be निश्चितed again until
			 * the output queue was previous emptied.
			 * This issue would happen in the scenario that
			 * user always has his/her fingers touched on the
			 * trackpad device during प्रणाली booting/rebooting.
			 */
			length = 0;
			अगर (pip->resp_len)
				length = *pip->resp_len;
			cyapa_empty_pip_output_data(cyapa,
					pip->resp_data,
					&length,
					pip->resp_sort_func);
			अगर (pip->resp_len && length != 0) अणु
				*pip->resp_len = length;
				atomic_dec(&pip->cmd_issued);
				complete(&pip->cmd_पढ़ोy);
			पूर्ण
			वापस false;
		पूर्ण

		अगर (pip->resp_data && pip->resp_len) अणु
			*pip->resp_len = (*pip->resp_len < length) ?
				*pip->resp_len : length;
			स_नकल(pip->resp_data, pip->irq_cmd_buf,
				*pip->resp_len);
		पूर्ण
		atomic_dec(&pip->cmd_issued);
		complete(&pip->cmd_पढ़ोy);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम cyapa_pip_report_buttons(काष्ठा cyapa *cyapa,
		स्थिर काष्ठा cyapa_pip_report_data *report_data)
अणु
	काष्ठा input_dev *input = cyapa->input;
	u8 buttons = report_data->report_head[PIP_BUTTONS_OFFSET];

	buttons = (buttons << CAPABILITY_BTN_SHIFT) & CAPABILITY_BTN_MASK;

	अगर (cyapa->btn_capability & CAPABILITY_LEFT_BTN_MASK) अणु
		input_report_key(input, BTN_LEFT,
			!!(buttons & CAPABILITY_LEFT_BTN_MASK));
	पूर्ण
	अगर (cyapa->btn_capability & CAPABILITY_MIDDLE_BTN_MASK) अणु
		input_report_key(input, BTN_MIDDLE,
			!!(buttons & CAPABILITY_MIDDLE_BTN_MASK));
	पूर्ण
	अगर (cyapa->btn_capability & CAPABILITY_RIGHT_BTN_MASK) अणु
		input_report_key(input, BTN_RIGHT,
			!!(buttons & CAPABILITY_RIGHT_BTN_MASK));
	पूर्ण

	input_sync(input);
पूर्ण

अटल व्योम cyapa_pip_report_proximity(काष्ठा cyapa *cyapa,
		स्थिर काष्ठा cyapa_pip_report_data *report_data)
अणु
	काष्ठा input_dev *input = cyapa->input;
	u8 distance = report_data->report_head[PIP_PROXIMITY_DISTANCE_OFFSET] &
			PIP_PROXIMITY_DISTANCE_MASK;

	input_report_असल(input, ABS_DISTANCE, distance);
	input_sync(input);
पूर्ण

अटल व्योम cyapa_pip_report_slot_data(काष्ठा cyapa *cyapa,
		स्थिर काष्ठा cyapa_pip_touch_record *touch)
अणु
	काष्ठा input_dev *input = cyapa->input;
	u8 event_id = PIP_GET_EVENT_ID(touch->touch_tip_event_id);
	पूर्णांक slot = PIP_GET_TOUCH_ID(touch->touch_tip_event_id);
	पूर्णांक x, y;

	अगर (event_id == RECORD_EVENT_LIFTOFF)
		वापस;

	input_mt_slot(input, slot);
	input_mt_report_slot_state(input, MT_TOOL_FINGER, true);
	x = (touch->x_hi << 8) | touch->x_lo;
	अगर (cyapa->x_origin)
		x = cyapa->max_असल_x - x;
	y = (touch->y_hi << 8) | touch->y_lo;
	अगर (cyapa->y_origin)
		y = cyapa->max_असल_y - y;
	input_report_असल(input, ABS_MT_POSITION_X, x);
	input_report_असल(input, ABS_MT_POSITION_Y, y);
	input_report_असल(input, ABS_DISTANCE, 0);
	input_report_असल(input, ABS_MT_PRESSURE,
		touch->z);
	input_report_असल(input, ABS_MT_TOUCH_MAJOR,
		touch->major_axis_len);
	input_report_असल(input, ABS_MT_TOUCH_MINOR,
		touch->minor_axis_len);

	input_report_असल(input, ABS_MT_WIDTH_MAJOR,
		touch->major_tool_len);
	input_report_असल(input, ABS_MT_WIDTH_MINOR,
		touch->minor_tool_len);

	input_report_असल(input, ABS_MT_ORIENTATION,
		touch->orientation);
पूर्ण

अटल व्योम cyapa_pip_report_touches(काष्ठा cyapa *cyapa,
		स्थिर काष्ठा cyapa_pip_report_data *report_data)
अणु
	काष्ठा input_dev *input = cyapa->input;
	अचिन्हित पूर्णांक touch_num;
	पूर्णांक i;

	touch_num = report_data->report_head[PIP_NUMBER_OF_TOUCH_OFFSET] &
			PIP_NUMBER_OF_TOUCH_MASK;

	क्रम (i = 0; i < touch_num; i++)
		cyapa_pip_report_slot_data(cyapa,
			&report_data->touch_records[i]);

	input_mt_sync_frame(input);
	input_sync(input);
पूर्ण

पूर्णांक cyapa_pip_irq_handler(काष्ठा cyapa *cyapa)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	काष्ठा cyapa_pip_report_data report_data;
	अचिन्हित पूर्णांक report_len;
	पूर्णांक ret;

	अगर (!cyapa_is_pip_app_mode(cyapa)) अणु
		dev_err(dev, "invalid device state, gen=%d, state=0x%02x\n",
			cyapa->gen, cyapa->state);
		वापस -EINVAL;
	पूर्ण

	ret = cyapa_i2c_pip_पढ़ो(cyapa, (u8 *)&report_data,
			PIP_RESP_LENGTH_SIZE);
	अगर (ret != PIP_RESP_LENGTH_SIZE) अणु
		dev_err(dev, "failed to read length bytes, (%d)\n", ret);
		वापस -EINVAL;
	पूर्ण

	report_len = get_unaligned_le16(
			&report_data.report_head[PIP_RESP_LENGTH_OFFSET]);
	अगर (report_len < PIP_RESP_LENGTH_SIZE) अणु
		/* Invalid length or पूर्णांकernal reset happened. */
		dev_err(dev, "invalid report_len=%d. bytes: %02x %02x\n",
			report_len, report_data.report_head[0],
			report_data.report_head[1]);
		वापस -EINVAL;
	पूर्ण

	/* Idle, no data क्रम report. */
	अगर (report_len == PIP_RESP_LENGTH_SIZE)
		वापस 0;

	ret = cyapa_i2c_pip_पढ़ो(cyapa, (u8 *)&report_data, report_len);
	अगर (ret != report_len) अणु
		dev_err(dev, "failed to read %d bytes report data, (%d)\n",
			report_len, ret);
		वापस -EINVAL;
	पूर्ण

	वापस cyapa_pip_event_process(cyapa, &report_data);
पूर्ण

अटल पूर्णांक cyapa_pip_event_process(काष्ठा cyapa *cyapa,
				   काष्ठा cyapa_pip_report_data *report_data)
अणु
	काष्ठा device *dev = &cyapa->client->dev;
	अचिन्हित पूर्णांक report_len;
	u8 report_id;

	report_len = get_unaligned_le16(
			&report_data->report_head[PIP_RESP_LENGTH_OFFSET]);
	/* Idle, no data क्रम report. */
	अगर (report_len == PIP_RESP_LENGTH_SIZE)
		वापस 0;

	report_id = report_data->report_head[PIP_RESP_REPORT_ID_OFFSET];
	अगर (report_id == PIP_WAKEUP_EVENT_REPORT_ID &&
			report_len == PIP_WAKEUP_EVENT_SIZE) अणु
		/*
		 * Device wake event from deep sleep mode क्रम touch.
		 * This पूर्णांकerrupt event is used to wake प्रणाली up.
		 *
		 * Note:
		 * It will पूर्णांकroduce about 20~40 ms additional delay
		 * समय in receiving क्रम first valid touch report data.
		 * The समय is used to execute device runसमय resume
		 * process.
		 */
		pm_runसमय_get_sync(dev);
		pm_runसमय_mark_last_busy(dev);
		pm_runसमय_put_sync_स्वतःsuspend(dev);
		वापस 0;
	पूर्ण अन्यथा अगर (report_id != PIP_TOUCH_REPORT_ID &&
			report_id != PIP_BTN_REPORT_ID &&
			report_id != GEN5_OLD_PUSH_BTN_REPORT_ID &&
			report_id != PIP_PUSH_BTN_REPORT_ID &&
			report_id != PIP_PROXIMITY_REPORT_ID) अणु
		/* Running in BL mode or unknown response data पढ़ो. */
		dev_err(dev, "invalid report_id=0x%02x\n", report_id);
		वापस -EINVAL;
	पूर्ण

	अगर (report_id == PIP_TOUCH_REPORT_ID &&
		(report_len < PIP_TOUCH_REPORT_HEAD_SIZE ||
			report_len > PIP_TOUCH_REPORT_MAX_SIZE)) अणु
		/* Invalid report data length क्रम finger packet. */
		dev_err(dev, "invalid touch packet length=%d\n", report_len);
		वापस 0;
	पूर्ण

	अगर ((report_id == PIP_BTN_REPORT_ID ||
			report_id == GEN5_OLD_PUSH_BTN_REPORT_ID ||
			report_id == PIP_PUSH_BTN_REPORT_ID) &&
		(report_len < PIP_BTN_REPORT_HEAD_SIZE ||
			report_len > PIP_BTN_REPORT_MAX_SIZE)) अणु
		/* Invalid report data length of button packet. */
		dev_err(dev, "invalid button packet length=%d\n", report_len);
		वापस 0;
	पूर्ण

	अगर (report_id == PIP_PROXIMITY_REPORT_ID &&
			report_len != PIP_PROXIMITY_REPORT_SIZE) अणु
		/* Invalid report data length of proximity packet. */
		dev_err(dev, "invalid proximity data, length=%d\n", report_len);
		वापस 0;
	पूर्ण

	अगर (report_id == PIP_TOUCH_REPORT_ID)
		cyapa_pip_report_touches(cyapa, report_data);
	अन्यथा अगर (report_id == PIP_PROXIMITY_REPORT_ID)
		cyapa_pip_report_proximity(cyapa, report_data);
	अन्यथा
		cyapa_pip_report_buttons(cyapa, report_data);

	वापस 0;
पूर्ण

पूर्णांक cyapa_pip_bl_activate(काष्ठा cyapa *cyapa) अणु वापस 0; पूर्ण
पूर्णांक cyapa_pip_bl_deactivate(काष्ठा cyapa *cyapa) अणु वापस 0; पूर्ण


स्थिर काष्ठा cyapa_dev_ops cyapa_gen5_ops = अणु
	.check_fw = cyapa_pip_check_fw,
	.bl_enter = cyapa_pip_bl_enter,
	.bl_initiate = cyapa_pip_bl_initiate,
	.update_fw = cyapa_pip_करो_fw_update,
	.bl_activate = cyapa_pip_bl_activate,
	.bl_deactivate = cyapa_pip_bl_deactivate,

	.show_baseline = cyapa_gen5_show_baseline,
	.calibrate_store = cyapa_pip_करो_calibrate,

	.initialize = cyapa_pip_cmd_state_initialize,

	.state_parse = cyapa_gen5_state_parse,
	.operational_check = cyapa_gen5_करो_operational_check,

	.irq_handler = cyapa_pip_irq_handler,
	.irq_cmd_handler = cyapa_pip_irq_cmd_handler,
	.sort_empty_output_data = cyapa_empty_pip_output_data,
	.set_घातer_mode = cyapa_gen5_set_घातer_mode,

	.set_proximity = cyapa_pip_set_proximity,
पूर्ण;
