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

#अगर_अघोषित _CYAPA_H
#घोषणा _CYAPA_H

#समावेश <linux/firmware.h>

/* APA trackpad firmware generation number. */
#घोषणा CYAPA_GEN_UNKNOWN   0x00   /* unknown protocol. */
#घोषणा CYAPA_GEN3   0x03   /* support MT-protocol B with tracking ID. */
#घोषणा CYAPA_GEN5   0x05   /* support TrueTouch GEN5 trackpad device. */
#घोषणा CYAPA_GEN6   0x06   /* support TrueTouch GEN6 trackpad device. */

#घोषणा CYAPA_NAME   "Cypress APA Trackpad (cyapa)"

/*
 * Macros क्रम SMBus communication
 */
#घोषणा SMBUS_READ  0x01
#घोषणा SMBUS_WRITE 0x00
#घोषणा SMBUS_ENCODE_IDX(cmd, idx) ((cmd) | (((idx) & 0x03) << 1))
#घोषणा SMBUS_ENCODE_RW(cmd, rw) ((cmd) | ((rw) & 0x01))
#घोषणा SMBUS_BYTE_BLOCK_CMD_MASK 0x80
#घोषणा SMBUS_GROUP_BLOCK_CMD_MASK 0x40

/* Commands क्रम पढ़ो/ग_लिखो रेजिस्टरs of Cypress trackpad */
#घोषणा CYAPA_CMD_SOFT_RESET       0x00
#घोषणा CYAPA_CMD_POWER_MODE       0x01
#घोषणा CYAPA_CMD_DEV_STATUS       0x02
#घोषणा CYAPA_CMD_GROUP_DATA       0x03
#घोषणा CYAPA_CMD_GROUP_CMD        0x04
#घोषणा CYAPA_CMD_GROUP_QUERY      0x05
#घोषणा CYAPA_CMD_BL_STATUS        0x06
#घोषणा CYAPA_CMD_BL_HEAD          0x07
#घोषणा CYAPA_CMD_BL_CMD           0x08
#घोषणा CYAPA_CMD_BL_DATA          0x09
#घोषणा CYAPA_CMD_BL_ALL           0x0a
#घोषणा CYAPA_CMD_BLK_PRODUCT_ID   0x0b
#घोषणा CYAPA_CMD_BLK_HEAD         0x0c
#घोषणा CYAPA_CMD_MAX_BASELINE     0x0d
#घोषणा CYAPA_CMD_MIN_BASELINE     0x0e

#घोषणा BL_HEAD_OFFSET 0x00
#घोषणा BL_DATA_OFFSET 0x10

#घोषणा BL_STATUS_SIZE  3  /* Length of gen3 bootloader status रेजिस्टरs */
#घोषणा CYAPA_REG_MAP_SIZE  256

/*
 * Gen3 Operational Device Status Register
 *
 * bit 7: Valid पूर्णांकerrupt source
 * bit 6 - 4: Reserved
 * bit 3 - 2: Power status
 * bit 1 - 0: Device status
 */
#घोषणा REG_OP_STATUS     0x00
#घोषणा OP_STATUS_SRC     0x80
#घोषणा OP_STATUS_POWER   0x0c
#घोषणा OP_STATUS_DEV     0x03
#घोषणा OP_STATUS_MASK (OP_STATUS_SRC | OP_STATUS_POWER | OP_STATUS_DEV)

/*
 * Operational Finger Count/Button Flags Register
 *
 * bit 7 - 4: Number of touched finger
 * bit 3: Valid data
 * bit 2: Middle Physical Button
 * bit 1: Right Physical Button
 * bit 0: Left physical Button
 */
#घोषणा REG_OP_DATA1       0x01
#घोषणा OP_DATA_VALID      0x08
#घोषणा OP_DATA_MIDDLE_BTN 0x04
#घोषणा OP_DATA_RIGHT_BTN  0x02
#घोषणा OP_DATA_LEFT_BTN   0x01
#घोषणा OP_DATA_BTN_MASK (OP_DATA_MIDDLE_BTN | OP_DATA_RIGHT_BTN | \
			  OP_DATA_LEFT_BTN)

/*
 * Write-only command file रेजिस्टर used to issue commands and
 * parameters to the bootloader.
 * The शेष value पढ़ो from it is always 0x00.
 */
#घोषणा REG_BL_खाता	0x00
#घोषणा BL_खाता		0x00

/*
 * Bootloader Status Register
 *
 * bit 7: Busy
 * bit 6 - 5: Reserved
 * bit 4: Bootloader running
 * bit 3 - 2: Reserved
 * bit 1: Watchकरोg Reset
 * bit 0: Checksum valid
 */
#घोषणा REG_BL_STATUS        0x01
#घोषणा BL_STATUS_REV_6_5    0x60
#घोषणा BL_STATUS_BUSY       0x80
#घोषणा BL_STATUS_RUNNING    0x10
#घोषणा BL_STATUS_REV_3_2    0x0c
#घोषणा BL_STATUS_WATCHDOG   0x02
#घोषणा BL_STATUS_CSUM_VALID 0x01
#घोषणा BL_STATUS_REV_MASK (BL_STATUS_WATCHDOG | BL_STATUS_REV_3_2 | \
			    BL_STATUS_REV_6_5)

/*
 * Bootloader Error Register
 *
 * bit 7: Invalid
 * bit 6: Invalid security key
 * bit 5: Bootloading
 * bit 4: Command checksum
 * bit 3: Flash protection error
 * bit 2: Flash checksum error
 * bit 1 - 0: Reserved
 */
#घोषणा REG_BL_ERROR         0x02
#घोषणा BL_ERROR_INVALID     0x80
#घोषणा BL_ERROR_INVALID_KEY 0x40
#घोषणा BL_ERROR_BOOTLOADING 0x20
#घोषणा BL_ERROR_CMD_CSUM    0x10
#घोषणा BL_ERROR_FLASH_PROT  0x08
#घोषणा BL_ERROR_FLASH_CSUM  0x04
#घोषणा BL_ERROR_RESERVED    0x03
#घोषणा BL_ERROR_NO_ERR_IDLE    0x00
#घोषणा BL_ERROR_NO_ERR_ACTIVE  (BL_ERROR_BOOTLOADING)

#घोषणा CAPABILITY_BTN_SHIFT            3
#घोषणा CAPABILITY_LEFT_BTN_MASK	(0x01 << 3)
#घोषणा CAPABILITY_RIGHT_BTN_MASK	(0x01 << 4)
#घोषणा CAPABILITY_MIDDLE_BTN_MASK	(0x01 << 5)
#घोषणा CAPABILITY_BTN_MASK  (CAPABILITY_LEFT_BTN_MASK | \
			      CAPABILITY_RIGHT_BTN_MASK | \
			      CAPABILITY_MIDDLE_BTN_MASK)

#घोषणा PWR_MODE_MASK   0xfc
#घोषणा PWR_MODE_FULL_ACTIVE (0x3f << 2)
#घोषणा PWR_MODE_IDLE        (0x03 << 2) /* Default rt suspend scanrate: 30ms */
#घोषणा PWR_MODE_SLEEP       (0x05 << 2) /* Default suspend scanrate: 50ms */
#घोषणा PWR_MODE_BTN_ONLY    (0x01 << 2)
#घोषणा PWR_MODE_OFF         (0x00 << 2)

#घोषणा PWR_STATUS_MASK      0x0c
#घोषणा PWR_STATUS_ACTIVE    (0x03 << 2)
#घोषणा PWR_STATUS_IDLE      (0x02 << 2)
#घोषणा PWR_STATUS_BTN_ONLY  (0x01 << 2)
#घोषणा PWR_STATUS_OFF       (0x00 << 2)

#घोषणा AUTOSUSPEND_DELAY   2000 /* unit : ms */

#घोषणा BTN_ONLY_MODE_NAME   "buttononly"
#घोषणा OFF_MODE_NAME        "off"

/* Common macros क्रम PIP पूर्णांकerface. */
#घोषणा PIP_HID_DESCRIPTOR_ADDR		0x0001
#घोषणा PIP_REPORT_DESCRIPTOR_ADDR	0x0002
#घोषणा PIP_INPUT_REPORT_ADDR		0x0003
#घोषणा PIP_OUTPUT_REPORT_ADDR		0x0004
#घोषणा PIP_CMD_DATA_ADDR		0x0006

#घोषणा PIP_RETRIEVE_DATA_STRUCTURE	0x24
#घोषणा PIP_CMD_CALIBRATE		0x28
#घोषणा PIP_BL_CMD_VERIFY_APP_INTEGRITY	0x31
#घोषणा PIP_BL_CMD_GET_BL_INFO		0x38
#घोषणा PIP_BL_CMD_PROGRAM_VERIFY_ROW	0x39
#घोषणा PIP_BL_CMD_LAUNCH_APP		0x3b
#घोषणा PIP_BL_CMD_INITIATE_BL		0x48
#घोषणा PIP_INVALID_CMD			0xff

#घोषणा PIP_HID_DESCRIPTOR_SIZE		32
#घोषणा PIP_HID_APP_REPORT_ID		0xf7
#घोषणा PIP_HID_BL_REPORT_ID		0xff

#घोषणा PIP_BL_CMD_REPORT_ID		0x40
#घोषणा PIP_BL_RESP_REPORT_ID		0x30
#घोषणा PIP_APP_CMD_REPORT_ID		0x2f
#घोषणा PIP_APP_RESP_REPORT_ID		0x1f

#घोषणा PIP_READ_SYS_INFO_CMD_LENGTH	7
#घोषणा PIP_BL_READ_APP_INFO_CMD_LENGTH	13
#घोषणा PIP_MIN_BL_CMD_LENGTH		13
#घोषणा PIP_MIN_BL_RESP_LENGTH		11
#घोषणा PIP_MIN_APP_CMD_LENGTH		7
#घोषणा PIP_MIN_APP_RESP_LENGTH		5
#घोषणा PIP_UNSUPPORTED_CMD_RESP_LENGTH	6
#घोषणा PIP_READ_SYS_INFO_RESP_LENGTH	71
#घोषणा PIP_BL_APP_INFO_RESP_LENGTH	30
#घोषणा PIP_BL_GET_INFO_RESP_LENGTH	19

#घोषणा PIP_BL_PLATFORM_VER_SHIFT	4
#घोषणा PIP_BL_PLATFORM_VER_MASK	0x0f

#घोषणा PIP_PRODUCT_FAMILY_MASK		0xf000
#घोषणा PIP_PRODUCT_FAMILY_TRACKPAD	0x1000

#घोषणा PIP_DEEP_SLEEP_STATE_ON		0x00
#घोषणा PIP_DEEP_SLEEP_STATE_OFF	0x01
#घोषणा PIP_DEEP_SLEEP_STATE_MASK	0x03
#घोषणा PIP_APP_DEEP_SLEEP_REPORT_ID	0xf0
#घोषणा PIP_DEEP_SLEEP_RESP_LENGTH	5
#घोषणा PIP_DEEP_SLEEP_OPCODE		0x08
#घोषणा PIP_DEEP_SLEEP_OPCODE_MASK	0x0f

#घोषणा PIP_RESP_LENGTH_OFFSET		0
#घोषणा	    PIP_RESP_LENGTH_SIZE	2
#घोषणा PIP_RESP_REPORT_ID_OFFSET	2
#घोषणा PIP_RESP_RSVD_OFFSET		3
#घोषणा     PIP_RESP_RSVD_KEY		0x00
#घोषणा PIP_RESP_BL_SOP_OFFSET		4
#घोषणा     PIP_SOP_KEY			0x01  /* Start of Packet */
#घोषणा     PIP_EOP_KEY			0x17  /* End of Packet */
#घोषणा PIP_RESP_APP_CMD_OFFSET		4
#घोषणा     GET_PIP_CMD_CODE(reg)	((reg) & 0x7f)
#घोषणा PIP_RESP_STATUS_OFFSET		5

#घोषणा VALID_CMD_RESP_HEADER(resp, cmd)				  \
	(((resp)[PIP_RESP_REPORT_ID_OFFSET] == PIP_APP_RESP_REPORT_ID) && \
	((resp)[PIP_RESP_RSVD_OFFSET] == PIP_RESP_RSVD_KEY) &&		  \
	(GET_PIP_CMD_CODE((resp)[PIP_RESP_APP_CMD_OFFSET]) == (cmd)))

#घोषणा PIP_CMD_COMPLETE_SUCCESS(resp_data) \
	((resp_data)[PIP_RESP_STATUS_OFFSET] == 0x00)

/* Variables to record latest gen5 trackpad घातer states. */
#घोषणा UNINIT_SLEEP_TIME	0xffff
#घोषणा UNINIT_PWR_MODE		0xff
#घोषणा PIP_DEV_SET_PWR_STATE(cyapa, s)		((cyapa)->dev_pwr_mode = (s))
#घोषणा PIP_DEV_GET_PWR_STATE(cyapa)		((cyapa)->dev_pwr_mode)
#घोषणा PIP_DEV_SET_SLEEP_TIME(cyapa, t)	((cyapa)->dev_sleep_समय = (t))
#घोषणा PIP_DEV_GET_SLEEP_TIME(cyapa)		((cyapa)->dev_sleep_समय)
#घोषणा PIP_DEV_UNINIT_SLEEP_TIME(cyapa)	\
		(((cyapa)->dev_sleep_समय) == UNINIT_SLEEP_TIME)

/* The touch.id is used as the MT slot id, thus max MT slot is 15 */
#घोषणा CYAPA_MAX_MT_SLOTS  15

काष्ठा cyapa;

प्रकार bool (*cb_sort)(काष्ठा cyapa *, u8 *, पूर्णांक);

क्रमागत cyapa_pm_stage अणु
	CYAPA_PM_DEACTIVE,
	CYAPA_PM_ACTIVE,
	CYAPA_PM_SUSPEND,
	CYAPA_PM_RESUME,
	CYAPA_PM_RUNTIME_SUSPEND,
	CYAPA_PM_RUNTIME_RESUME,
पूर्ण;

काष्ठा cyapa_dev_ops अणु
	पूर्णांक (*check_fw)(काष्ठा cyapa *, स्थिर काष्ठा firmware *);
	पूर्णांक (*bl_enter)(काष्ठा cyapa *);
	पूर्णांक (*bl_activate)(काष्ठा cyapa *);
	पूर्णांक (*bl_initiate)(काष्ठा cyapa *, स्थिर काष्ठा firmware *);
	पूर्णांक (*update_fw)(काष्ठा cyapa *, स्थिर काष्ठा firmware *);
	पूर्णांक (*bl_deactivate)(काष्ठा cyapa *);

	sमाप_प्रकार (*show_baseline)(काष्ठा device *,
			काष्ठा device_attribute *, अक्षर *);
	sमाप_प्रकार (*calibrate_store)(काष्ठा device *,
			काष्ठा device_attribute *, स्थिर अक्षर *, माप_प्रकार);

	पूर्णांक (*initialize)(काष्ठा cyapa *cyapa);

	पूर्णांक (*state_parse)(काष्ठा cyapa *cyapa, u8 *reg_status, पूर्णांक len);
	पूर्णांक (*operational_check)(काष्ठा cyapa *cyapa);

	पूर्णांक (*irq_handler)(काष्ठा cyapa *);
	bool (*irq_cmd_handler)(काष्ठा cyapa *);
	पूर्णांक (*sort_empty_output_data)(काष्ठा cyapa *,
			u8 *, पूर्णांक *, cb_sort);

	पूर्णांक (*set_घातer_mode)(काष्ठा cyapa *, u8, u16, क्रमागत cyapa_pm_stage);

	पूर्णांक (*set_proximity)(काष्ठा cyapa *, bool);
पूर्ण;

काष्ठा cyapa_pip_cmd_states अणु
	काष्ठा mutex cmd_lock;
	काष्ठा completion cmd_पढ़ोy;
	atomic_t cmd_issued;
	u8 in_progress_cmd;
	bool is_irq_mode;

	cb_sort resp_sort_func;
	u8 *resp_data;
	पूर्णांक *resp_len;

	क्रमागत cyapa_pm_stage pm_stage;
	काष्ठा mutex pm_stage_lock;

	u8 irq_cmd_buf[CYAPA_REG_MAP_SIZE];
	u8 empty_buf[CYAPA_REG_MAP_SIZE];
पूर्ण;

जोड़ cyapa_cmd_states अणु
	काष्ठा cyapa_pip_cmd_states pip;
पूर्ण;

क्रमागत cyapa_state अणु
	CYAPA_STATE_NO_DEVICE,
	CYAPA_STATE_BL_BUSY,
	CYAPA_STATE_BL_IDLE,
	CYAPA_STATE_BL_ACTIVE,
	CYAPA_STATE_OP,
	CYAPA_STATE_GEN5_BL,
	CYAPA_STATE_GEN5_APP,
	CYAPA_STATE_GEN6_BL,
	CYAPA_STATE_GEN6_APP,
पूर्ण;

काष्ठा gen6_पूर्णांकerval_setting अणु
	u16 active_पूर्णांकerval;
	u16 lp1_पूर्णांकerval;
	u16 lp2_पूर्णांकerval;
पूर्ण;

/* The मुख्य device काष्ठाure */
काष्ठा cyapa अणु
	क्रमागत cyapa_state state;
	u8 status[BL_STATUS_SIZE];
	bool operational; /* true: पढ़ोy क्रम data reporting; false: not. */

	काष्ठा regulator *vcc;
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	अक्षर phys[32];	/* Device physical location */
	bool irq_wake;  /* Irq wake is enabled */
	bool smbus;

	/* घातer mode settings */
	u8 suspend_घातer_mode;
	u16 suspend_sleep_समय;
	u8 runसमय_suspend_घातer_mode;
	u16 runसमय_suspend_sleep_समय;
	u8 dev_pwr_mode;
	u16 dev_sleep_समय;
	काष्ठा gen6_पूर्णांकerval_setting gen6_पूर्णांकerval_setting;

	/* Read from query data region. */
	अक्षर product_id[16];
	u8 platक्रमm_ver;  /* Platक्रमm version. */
	u8 fw_maj_ver;  /* Firmware major version. */
	u8 fw_min_ver;  /* Firmware minor version. */
	u8 btn_capability;
	u8 gen;
	पूर्णांक max_असल_x;
	पूर्णांक max_असल_y;
	पूर्णांक physical_size_x;
	पूर्णांक physical_size_y;

	/* Used in ttsp and truetouch based trackpad devices. */
	u8 x_origin;  /* X Axis Origin: 0 = left side; 1 = right side. */
	u8 y_origin;  /* Y Axis Origin: 0 = top; 1 = bottom. */
	पूर्णांक electrodes_x;  /* Number of electrodes on the X Axis*/
	पूर्णांक electrodes_y;  /* Number of electrodes on the Y Axis*/
	पूर्णांक electrodes_rx;  /* Number of Rx electrodes */
	पूर्णांक aligned_electrodes_rx;  /* 4 aligned */
	पूर्णांक max_z;

	/*
	 * Used to synchronize the access or update the device state.
	 * And since update firmware and पढ़ो firmware image process will take
	 * quite दीर्घ समय, maybe more than 10 seconds, so use mutex_lock
	 * to sync and रुको other पूर्णांकerface and detecting are करोne or पढ़ोy.
	 */
	काष्ठा mutex state_sync_lock;

	स्थिर काष्ठा cyapa_dev_ops *ops;

	जोड़ cyapa_cmd_states cmd_states;
पूर्ण;


sमाप_प्रकार cyapa_i2c_reg_पढ़ो_block(काष्ठा cyapa *cyapa, u8 reg, माप_प्रकार len,
				 u8 *values);
sमाप_प्रकार cyapa_smbus_पढ़ो_block(काष्ठा cyapa *cyapa, u8 cmd, माप_प्रकार len,
			       u8 *values);

sमाप_प्रकार cyapa_पढ़ो_block(काष्ठा cyapa *cyapa, u8 cmd_idx, u8 *values);

पूर्णांक cyapa_poll_state(काष्ठा cyapa *cyapa, अचिन्हित पूर्णांक समयout);

u8 cyapa_sleep_समय_प्रकारo_pwr_cmd(u16 sleep_समय);
u16 cyapa_pwr_cmd_to_sleep_समय(u8 pwr_mode);

sमाप_प्रकार cyapa_i2c_pip_पढ़ो(काष्ठा cyapa *cyapa, u8 *buf, माप_प्रकार size);
sमाप_प्रकार cyapa_i2c_pip_ग_लिखो(काष्ठा cyapa *cyapa, u8 *buf, माप_प्रकार size);
पूर्णांक cyapa_empty_pip_output_data(काष्ठा cyapa *cyapa,
				u8 *buf, पूर्णांक *len, cb_sort func);
पूर्णांक cyapa_i2c_pip_cmd_irq_sync(काष्ठा cyapa *cyapa,
			       u8 *cmd, पूर्णांक cmd_len,
			       u8 *resp_data, पूर्णांक *resp_len,
			       अचिन्हित दीर्घ समयout,
			       cb_sort func,
			       bool irq_mode);
पूर्णांक cyapa_pip_state_parse(काष्ठा cyapa *cyapa, u8 *reg_data, पूर्णांक len);
bool cyapa_pip_sort_प्रणाली_info_data(काष्ठा cyapa *cyapa, u8 *buf, पूर्णांक len);
bool cyapa_sort_tsg_pip_bl_resp_data(काष्ठा cyapa *cyapa, u8 *data, पूर्णांक len);
पूर्णांक cyapa_pip_deep_sleep(काष्ठा cyapa *cyapa, u8 state);
bool cyapa_sort_tsg_pip_app_resp_data(काष्ठा cyapa *cyapa, u8 *data, पूर्णांक len);
पूर्णांक cyapa_pip_bl_निकास(काष्ठा cyapa *cyapa);
पूर्णांक cyapa_pip_bl_enter(काष्ठा cyapa *cyapa);


bool cyapa_is_pip_bl_mode(काष्ठा cyapa *cyapa);
bool cyapa_is_pip_app_mode(काष्ठा cyapa *cyapa);
पूर्णांक cyapa_pip_cmd_state_initialize(काष्ठा cyapa *cyapa);

पूर्णांक cyapa_pip_resume_scanning(काष्ठा cyapa *cyapa);
पूर्णांक cyapa_pip_suspend_scanning(काष्ठा cyapa *cyapa);

पूर्णांक cyapa_pip_check_fw(काष्ठा cyapa *cyapa, स्थिर काष्ठा firmware *fw);
पूर्णांक cyapa_pip_bl_initiate(काष्ठा cyapa *cyapa, स्थिर काष्ठा firmware *fw);
पूर्णांक cyapa_pip_करो_fw_update(काष्ठा cyapa *cyapa, स्थिर काष्ठा firmware *fw);
पूर्णांक cyapa_pip_bl_activate(काष्ठा cyapa *cyapa);
पूर्णांक cyapa_pip_bl_deactivate(काष्ठा cyapa *cyapa);
sमाप_प्रकार cyapa_pip_करो_calibrate(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count);
पूर्णांक cyapa_pip_set_proximity(काष्ठा cyapa *cyapa, bool enable);

bool cyapa_pip_irq_cmd_handler(काष्ठा cyapa *cyapa);
पूर्णांक cyapa_pip_irq_handler(काष्ठा cyapa *cyapa);


बाह्य u8 pip_पढ़ो_sys_info[];
बाह्य u8 pip_bl_पढ़ो_app_info[];
बाह्य स्थिर अक्षर product_id[];
बाह्य स्थिर काष्ठा cyapa_dev_ops cyapa_gen3_ops;
बाह्य स्थिर काष्ठा cyapa_dev_ops cyapa_gen5_ops;
बाह्य स्थिर काष्ठा cyapa_dev_ops cyapa_gen6_ops;

#पूर्ण_अगर
