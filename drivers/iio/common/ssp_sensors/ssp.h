<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (C) 2014, Samsung Electronics Co. Ltd. All Rights Reserved.
 */

#अगर_अघोषित __SSP_SENSORHUB_H__
#घोषणा __SSP_SENSORHUB_H__

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iio/common/ssp_sensors.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/spi/spi.h>

#घोषणा SSP_DEVICE_ID		0x55

#अगर_घोषित SSP_DBG
#घोषणा ssp_dbg(क्रमmat, ...) pr_info("[SSP] "क्रमmat, ##__VA_ARGS__)
#अन्यथा
#घोषणा ssp_dbg(क्रमmat, ...)
#पूर्ण_अगर

#घोषणा SSP_SW_RESET_TIME		3000
/* Sensor polling in ms */
#घोषणा SSP_DEFAULT_POLLING_DELAY	200
#घोषणा SSP_DEFAULT_RETRIES		3
#घोषणा SSP_DATA_PACKET_SIZE		960
#घोषणा SSP_HEADER_BUFFER_SIZE		4

क्रमागत अणु
	SSP_KERNEL_BINARY = 0,
	SSP_KERNEL_CRASHED_BINARY,
पूर्ण;

क्रमागत अणु
	SSP_INITIALIZATION_STATE = 0,
	SSP_NO_SENSOR_STATE,
	SSP_ADD_SENSOR_STATE,
	SSP_RUNNING_SENSOR_STATE,
पूर्ण;

/* Firmware करोwnload STATE */
क्रमागत अणु
	SSP_FW_DL_STATE_FAIL = -1,
	SSP_FW_DL_STATE_NONE = 0,
	SSP_FW_DL_STATE_NEED_TO_SCHEDULE,
	SSP_FW_DL_STATE_SCHEDULED,
	SSP_FW_DL_STATE_DOWNLOADING,
	SSP_FW_DL_STATE_SYNC,
	SSP_FW_DL_STATE_DONE,
पूर्ण;

#घोषणा SSP_INVALID_REVISION			99999
#घोषणा SSP_INVALID_REVISION2			0xffffff

/* AP -> SSP Inकाष्ठाion */
#घोषणा SSP_MSG2SSP_INST_BYPASS_SENSOR_ADD	0xa1
#घोषणा SSP_MSG2SSP_INST_BYPASS_SENSOR_RM	0xa2
#घोषणा SSP_MSG2SSP_INST_REMOVE_ALL		0xa3
#घोषणा SSP_MSG2SSP_INST_CHANGE_DELAY		0xa4
#घोषणा SSP_MSG2SSP_INST_LIBRARY_ADD		0xb1
#घोषणा SSP_MSG2SSP_INST_LIBRARY_REMOVE		0xb2
#घोषणा SSP_MSG2SSP_INST_LIB_NOTI		0xb4
#घोषणा SSP_MSG2SSP_INST_LIB_DATA		0xc1

#घोषणा SSP_MSG2SSP_AP_MCU_SET_GYRO_CAL		0xcd
#घोषणा SSP_MSG2SSP_AP_MCU_SET_ACCEL_CAL	0xce
#घोषणा SSP_MSG2SSP_AP_STATUS_SHUTDOWN		0xd0
#घोषणा SSP_MSG2SSP_AP_STATUS_WAKEUP		0xd1
#घोषणा SSP_MSG2SSP_AP_STATUS_SLEEP		0xd2
#घोषणा SSP_MSG2SSP_AP_STATUS_RESUME		0xd3
#घोषणा SSP_MSG2SSP_AP_STATUS_SUSPEND		0xd4
#घोषणा SSP_MSG2SSP_AP_STATUS_RESET		0xd5
#घोषणा SSP_MSG2SSP_AP_STATUS_POW_CONNECTED	0xd6
#घोषणा SSP_MSG2SSP_AP_STATUS_POW_DISCONNECTED	0xd7
#घोषणा SSP_MSG2SSP_AP_TEMPHUMIDITY_CAL_DONE	0xda
#घोषणा SSP_MSG2SSP_AP_MCU_SET_DUMPMODE		0xdb
#घोषणा SSP_MSG2SSP_AP_MCU_DUMP_CHECK		0xdc
#घोषणा SSP_MSG2SSP_AP_MCU_BATCH_FLUSH		0xdd
#घोषणा SSP_MSG2SSP_AP_MCU_BATCH_COUNT		0xdf

#घोषणा SSP_MSG2SSP_AP_WHOAMI				0x0f
#घोषणा SSP_MSG2SSP_AP_FIRMWARE_REV			0xf0
#घोषणा SSP_MSG2SSP_AP_SENSOR_FORMATION			0xf1
#घोषणा SSP_MSG2SSP_AP_SENSOR_PROXTHRESHOLD		0xf2
#घोषणा SSP_MSG2SSP_AP_SENSOR_BARCODE_EMUL		0xf3
#घोषणा SSP_MSG2SSP_AP_SENSOR_SCANNING			0xf4
#घोषणा SSP_MSG2SSP_AP_SET_MAGNETIC_HWOFFSET		0xf5
#घोषणा SSP_MSG2SSP_AP_GET_MAGNETIC_HWOFFSET		0xf6
#घोषणा SSP_MSG2SSP_AP_SENSOR_GESTURE_CURRENT		0xf7
#घोषणा SSP_MSG2SSP_AP_GET_THERM			0xf8
#घोषणा SSP_MSG2SSP_AP_GET_BIG_DATA			0xf9
#घोषणा SSP_MSG2SSP_AP_SET_BIG_DATA			0xfa
#घोषणा SSP_MSG2SSP_AP_START_BIG_DATA			0xfb
#घोषणा SSP_MSG2SSP_AP_SET_MAGNETIC_STATIC_MATRIX	0xfd
#घोषणा SSP_MSG2SSP_AP_SENSOR_TILT			0xea
#घोषणा SSP_MSG2SSP_AP_MCU_SET_TIME			0xfe
#घोषणा SSP_MSG2SSP_AP_MCU_GET_TIME			0xff

#घोषणा SSP_MSG2SSP_AP_FUSEROM				0x01

/* voice data */
#घोषणा SSP_TYPE_WAKE_UP_VOICE_SERVICE			0x01
#घोषणा SSP_TYPE_WAKE_UP_VOICE_SOUND_SOURCE_AM		0x01
#घोषणा SSP_TYPE_WAKE_UP_VOICE_SOUND_SOURCE_GRAMMER	0x02

/* Factory Test */
#घोषणा SSP_ACCELEROMETER_FACTORY			0x80
#घोषणा SSP_GYROSCOPE_FACTORY				0x81
#घोषणा SSP_GEOMAGNETIC_FACTORY				0x82
#घोषणा SSP_PRESSURE_FACTORY				0x85
#घोषणा SSP_GESTURE_FACTORY				0x86
#घोषणा SSP_TEMPHUMIDITY_CRC_FACTORY			0x88
#घोषणा SSP_GYROSCOPE_TEMP_FACTORY			0x8a
#घोषणा SSP_GYROSCOPE_DPS_FACTORY			0x8b
#घोषणा SSP_MCU_FACTORY					0x8c
#घोषणा SSP_MCU_SLEEP_FACTORY				0x8d

/* SSP -> AP ACK about ग_लिखो CMD */
#घोषणा SSP_MSG_ACK		0x80	/* ACK from SSP to AP */
#घोषणा SSP_MSG_NAK		0x70	/* NAK from SSP to AP */

काष्ठा ssp_sensorhub_info अणु
	अक्षर *fw_name;
	अक्षर *fw_crashed_name;
	अचिन्हित पूर्णांक fw_rev;
	स्थिर u8 * स्थिर mag_table;
	स्थिर अचिन्हित पूर्णांक mag_length;
पूर्ण;

/* ssp_msg options bit */
#घोषणा SSP_RW		0
#घोषणा SSP_INDEX	3

#घोषणा SSP_AP2HUB_READ		0
#घोषणा SSP_AP2HUB_WRITE	1
#घोषणा SSP_HUB2AP_WRITE	2
#घोषणा SSP_AP2HUB_READY	3
#घोषणा SSP_AP2HUB_RETURN	4

/**
 * काष्ठा ssp_data - ssp platक्रमmdata काष्ठाure
 * @spi:		spi device
 * @sensorhub_info:	info about sensorhub board specअगरic features
 * @wdt_समयr:		watchकरोg समयr
 * @work_wdt:		watchकरोg work
 * @work_firmware:	firmware upgrade work queue
 * @work_refresh:	refresh work queue क्रम reset request from MCU
 * @shut_करोwn:		shut करोwn flag
 * @mcu_dump_mode:	mcu dump mode क्रम debug
 * @समय_syncing:	समय syncing indication flag
 * @बारtamp:		previous समय in ns calculated क्रम समय syncing
 * @check_status:	status table क्रम each sensor
 * @com_fail_cnt:	communication fail count
 * @reset_cnt:		reset count
 * @समयout_cnt:	समयout count
 * @available_sensors:	available sensors seen by sensorhub (bit array)
 * @cur_firm_rev:	cached current firmware revision
 * @last_resume_state:	last AP resume/suspend state used to handle the PM
 *                      state of ssp
 * @last_ap_state:	(obsolete) sleep notअगरication क्रम MCU
 * @sensor_enable:	sensor enable mask
 * @delay_buf:		data acquisition पूर्णांकervals table
 * @batch_latency_buf:	yet unknown but existing in communication protocol
 * @batch_opt_buf:	yet unknown but existing in communication protocol
 * @accel_position:	yet unknown but existing in communication protocol
 * @mag_position:	yet unknown but existing in communication protocol
 * @fw_dl_state:	firmware करोwnload state
 * @comm_lock:		lock protecting the handshake
 * @pending_lock:	lock protecting pending list and completion
 * @mcu_reset_gpiod:	mcu reset line
 * @ap_mcu_gpiod:	ap to mcu gpio line
 * @mcu_ap_gpiod:	mcu to ap gpio line
 * @pending_list:	pending list क्रम messages queued to be sent/पढ़ो
 * @sensor_devs:	रेजिस्टरed IIO devices table
 * @enable_refcount:	enable reference count क्रम wdt (watchकरोg समयr)
 * @header_buffer:	cache aligned buffer क्रम packet header
 */
काष्ठा ssp_data अणु
	काष्ठा spi_device *spi;
	स्थिर काष्ठा ssp_sensorhub_info *sensorhub_info;
	काष्ठा समयr_list wdt_समयr;
	काष्ठा work_काष्ठा work_wdt;
	काष्ठा delayed_work work_refresh;

	bool shut_करोwn;
	bool mcu_dump_mode;
	bool समय_syncing;
	पूर्णांक64_t बारtamp;

	पूर्णांक check_status[SSP_SENSOR_MAX];

	अचिन्हित पूर्णांक com_fail_cnt;
	अचिन्हित पूर्णांक reset_cnt;
	अचिन्हित पूर्णांक समयout_cnt;

	अचिन्हित पूर्णांक available_sensors;
	अचिन्हित पूर्णांक cur_firm_rev;

	अक्षर last_resume_state;
	अक्षर last_ap_state;

	अचिन्हित पूर्णांक sensor_enable;
	u32 delay_buf[SSP_SENSOR_MAX];
	s32 batch_latency_buf[SSP_SENSOR_MAX];
	s8 batch_opt_buf[SSP_SENSOR_MAX];

	पूर्णांक accel_position;
	पूर्णांक mag_position;
	पूर्णांक fw_dl_state;

	काष्ठा mutex comm_lock;
	काष्ठा mutex pending_lock;

	काष्ठा gpio_desc *mcu_reset_gpiod;
	काष्ठा gpio_desc *ap_mcu_gpiod;
	काष्ठा gpio_desc *mcu_ap_gpiod;

	काष्ठा list_head pending_list;

	काष्ठा iio_dev *sensor_devs[SSP_SENSOR_MAX];
	atomic_t enable_refcount;

	__le16 header_buffer[SSP_HEADER_BUFFER_SIZE / माप(__le16)]
		____cacheline_aligned;
पूर्ण;

व्योम ssp_clean_pending_list(काष्ठा ssp_data *data);

पूर्णांक ssp_command(काष्ठा ssp_data *data, अक्षर command, पूर्णांक arg);

पूर्णांक ssp_send_inकाष्ठाion(काष्ठा ssp_data *data, u8 inst, u8 sensor_type,
			 u8 *send_buf, u8 length);

पूर्णांक ssp_irq_msg(काष्ठा ssp_data *data);

पूर्णांक ssp_get_chipid(काष्ठा ssp_data *data);

पूर्णांक ssp_set_magnetic_matrix(काष्ठा ssp_data *data);

अचिन्हित पूर्णांक ssp_get_sensor_scanning_info(काष्ठा ssp_data *data);

अचिन्हित पूर्णांक ssp_get_firmware_rev(काष्ठा ssp_data *data);

पूर्णांक ssp_queue_ssp_refresh_task(काष्ठा ssp_data *data, अचिन्हित पूर्णांक delay);

#पूर्ण_अगर /* __SSP_SENSORHUB_H__ */
