<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/input/tablet/wacom_wac.h
 */
#अगर_अघोषित WACOM_WAC_H
#घोषणा WACOM_WAC_H

#समावेश <linux/types.h>
#समावेश <linux/hid.h>
#समावेश <linux/kfअगरo.h>

/* maximum packet length क्रम USB/BT devices */
#घोषणा WACOM_PKGLEN_MAX	361

#घोषणा WACOM_NAME_MAX		64
#घोषणा WACOM_MAX_REMOTES	5
#घोषणा WACOM_STATUS_UNKNOWN	255

/* packet length क्रम inभागidual models */
#घोषणा WACOM_PKGLEN_BBFUN	 9
#घोषणा WACOM_PKGLEN_TPC1FG	 5
#घोषणा WACOM_PKGLEN_TPC1FG_B	10
#घोषणा WACOM_PKGLEN_TPC2FG	14
#घोषणा WACOM_PKGLEN_BBTOUCH	20
#घोषणा WACOM_PKGLEN_BBTOUCH3	64
#घोषणा WACOM_PKGLEN_BBPEN	10
#घोषणा WACOM_PKGLEN_WIRELESS	32
#घोषणा WACOM_PKGLEN_PENABLED	 8
#घोषणा WACOM_PKGLEN_BPAD_TOUCH	32
#घोषणा WACOM_PKGLEN_BPAD_TOUCH_USB	64

/* wacom data size per MT contact */
#घोषणा WACOM_BYTES_PER_MT_PACKET	11
#घोषणा WACOM_BYTES_PER_24HDT_PACKET	14
#घोषणा WACOM_BYTES_PER_QHDTHID_PACKET	 6

/* device IDs */
#घोषणा STYLUS_DEVICE_ID	0x02
#घोषणा TOUCH_DEVICE_ID		0x03
#घोषणा CURSOR_DEVICE_ID	0x06
#घोषणा ERASER_DEVICE_ID	0x0A
#घोषणा PAD_DEVICE_ID		0x0F

/* wacom data packet report IDs */
#घोषणा WACOM_REPORT_PENABLED		2
#घोषणा WACOM_REPORT_PENABLED_BT	3
#घोषणा WACOM_REPORT_INTUOS_ID1		5
#घोषणा WACOM_REPORT_INTUOS_ID2		6
#घोषणा WACOM_REPORT_INTUOSPAD		12
#घोषणा WACOM_REPORT_INTUOS5PAD		3
#घोषणा WACOM_REPORT_DTUSPAD		21
#घोषणा WACOM_REPORT_TPC1FG		6
#घोषणा WACOM_REPORT_TPC2FG		13
#घोषणा WACOM_REPORT_TPCMT		13
#घोषणा WACOM_REPORT_TPCMT2		3
#घोषणा WACOM_REPORT_TPCHID		15
#घोषणा WACOM_REPORT_CINTIQ		16
#घोषणा WACOM_REPORT_CINTIQPAD		17
#घोषणा WACOM_REPORT_TPCST		16
#घोषणा WACOM_REPORT_DTUS		17
#घोषणा WACOM_REPORT_TPC1FGE		18
#घोषणा WACOM_REPORT_24HDT		1
#घोषणा WACOM_REPORT_WL			128
#घोषणा WACOM_REPORT_USB		192
#घोषणा WACOM_REPORT_BPAD_PEN		3
#घोषणा WACOM_REPORT_BPAD_TOUCH		16
#घोषणा WACOM_REPORT_DEVICE_LIST	16
#घोषणा WACOM_REPORT_INTUOS_PEN		16
#घोषणा WACOM_REPORT_REMOTE		17
#घोषणा WACOM_REPORT_INTUOSHT2_ID	8

/* wacom command report ids */
#घोषणा WAC_CMD_WL_LED_CONTROL          0x03
#घोषणा WAC_CMD_LED_CONTROL             0x20
#घोषणा WAC_CMD_ICON_START              0x21
#घोषणा WAC_CMD_ICON_XFER               0x23
#घोषणा WAC_CMD_ICON_BT_XFER            0x26
#घोषणा WAC_CMD_DELETE_PAIRING          0x20
#घोषणा WAC_CMD_LED_CONTROL_GENERIC     0x32
#घोषणा WAC_CMD_UNPAIR_ALL              0xFF
#घोषणा WAC_CMD_WL_INTUOSP2             0x82

/* device quirks */
#घोषणा WACOM_QUIRK_BBTOUCH_LOWRES	0x0001
#घोषणा WACOM_QUIRK_SENSE		0x0002
#घोषणा WACOM_QUIRK_AESPEN		0x0004
#घोषणा WACOM_QUIRK_BATTERY		0x0008
#घोषणा WACOM_QUIRK_TOOLSERIAL		0x0010

/* device types */
#घोषणा WACOM_DEVICETYPE_NONE           0x0000
#घोषणा WACOM_DEVICETYPE_PEN            0x0001
#घोषणा WACOM_DEVICETYPE_TOUCH          0x0002
#घोषणा WACOM_DEVICETYPE_PAD            0x0004
#घोषणा WACOM_DEVICETYPE_WL_MONITOR     0x0008
#घोषणा WACOM_DEVICETYPE_सूचीECT         0x0010

#घोषणा WACOM_POWER_SUPPLY_STATUS_AUTO  -1

#घोषणा WACOM_HID_UP_WACOMDIGITIZER     0xff0d0000
#घोषणा WACOM_HID_SP_PAD                0x00040000
#घोषणा WACOM_HID_SP_BUTTON             0x00090000
#घोषणा WACOM_HID_SP_DIGITIZER          0x000d0000
#घोषणा WACOM_HID_SP_DIGITIZERINFO      0x00100000
#घोषणा WACOM_HID_WD_DIGITIZER          (WACOM_HID_UP_WACOMDIGITIZER | 0x01)
#घोषणा WACOM_HID_WD_PEN                (WACOM_HID_UP_WACOMDIGITIZER | 0x02)
#घोषणा WACOM_HID_WD_SENSE              (WACOM_HID_UP_WACOMDIGITIZER | 0x36)
#घोषणा WACOM_HID_WD_DIGITIZERFNKEYS    (WACOM_HID_UP_WACOMDIGITIZER | 0x39)
#घोषणा WACOM_HID_WD_SERIALNUMBER       (WACOM_HID_UP_WACOMDIGITIZER | 0x5b)
#घोषणा WACOM_HID_WD_SERIALHI           (WACOM_HID_UP_WACOMDIGITIZER | 0x5c)
#घोषणा WACOM_HID_WD_TOOLTYPE           (WACOM_HID_UP_WACOMDIGITIZER | 0x77)
#घोषणा WACOM_HID_WD_DISTANCE           (WACOM_HID_UP_WACOMDIGITIZER | 0x0132)
#घोषणा WACOM_HID_WD_TOUCHSTRIP         (WACOM_HID_UP_WACOMDIGITIZER | 0x0136)
#घोषणा WACOM_HID_WD_TOUCHSTRIP2        (WACOM_HID_UP_WACOMDIGITIZER | 0x0137)
#घोषणा WACOM_HID_WD_TOUCHRING          (WACOM_HID_UP_WACOMDIGITIZER | 0x0138)
#घोषणा WACOM_HID_WD_TOUCHRINGSTATUS    (WACOM_HID_UP_WACOMDIGITIZER | 0x0139)
#घोषणा WACOM_HID_WD_REPORT_VALID       (WACOM_HID_UP_WACOMDIGITIZER | 0x01d0)
#घोषणा WACOM_HID_WD_ACCELEROMETER_X    (WACOM_HID_UP_WACOMDIGITIZER | 0x0401)
#घोषणा WACOM_HID_WD_ACCELEROMETER_Y    (WACOM_HID_UP_WACOMDIGITIZER | 0x0402)
#घोषणा WACOM_HID_WD_ACCELEROMETER_Z    (WACOM_HID_UP_WACOMDIGITIZER | 0x0403)
#घोषणा WACOM_HID_WD_BATTERY_CHARGING   (WACOM_HID_UP_WACOMDIGITIZER | 0x0404)
#घोषणा WACOM_HID_WD_TOUCHONOFF         (WACOM_HID_UP_WACOMDIGITIZER | 0x0454)
#घोषणा WACOM_HID_WD_BATTERY_LEVEL      (WACOM_HID_UP_WACOMDIGITIZER | 0x043b)
#घोषणा WACOM_HID_WD_EXPRESSKEY00       (WACOM_HID_UP_WACOMDIGITIZER | 0x0910)
#घोषणा WACOM_HID_WD_EXPRESSKEYCAP00    (WACOM_HID_UP_WACOMDIGITIZER | 0x0950)
#घोषणा WACOM_HID_WD_MODE_CHANGE        (WACOM_HID_UP_WACOMDIGITIZER | 0x0980)
#घोषणा WACOM_HID_WD_MUTE_DEVICE        (WACOM_HID_UP_WACOMDIGITIZER | 0x0981)
#घोषणा WACOM_HID_WD_CONTROLPANEL       (WACOM_HID_UP_WACOMDIGITIZER | 0x0982)
#घोषणा WACOM_HID_WD_ONSCREEN_KEYBOARD  (WACOM_HID_UP_WACOMDIGITIZER | 0x0983)
#घोषणा WACOM_HID_WD_BUTTONCONFIG       (WACOM_HID_UP_WACOMDIGITIZER | 0x0986)
#घोषणा WACOM_HID_WD_BUTTONHOME         (WACOM_HID_UP_WACOMDIGITIZER | 0x0990)
#घोषणा WACOM_HID_WD_BUTTONUP           (WACOM_HID_UP_WACOMDIGITIZER | 0x0991)
#घोषणा WACOM_HID_WD_BUTTONDOWN         (WACOM_HID_UP_WACOMDIGITIZER | 0x0992)
#घोषणा WACOM_HID_WD_BUTTONLEFT         (WACOM_HID_UP_WACOMDIGITIZER | 0x0993)
#घोषणा WACOM_HID_WD_BUTTONRIGHT        (WACOM_HID_UP_WACOMDIGITIZER | 0x0994)
#घोषणा WACOM_HID_WD_BUTTONCENTER       (WACOM_HID_UP_WACOMDIGITIZER | 0x0995)
#घोषणा WACOM_HID_WD_FINGERWHEEL        (WACOM_HID_UP_WACOMDIGITIZER | 0x0d03)
#घोषणा WACOM_HID_WD_OFFSETLEFT         (WACOM_HID_UP_WACOMDIGITIZER | 0x0d30)
#घोषणा WACOM_HID_WD_OFFSETTOP          (WACOM_HID_UP_WACOMDIGITIZER | 0x0d31)
#घोषणा WACOM_HID_WD_OFFSETRIGHT        (WACOM_HID_UP_WACOMDIGITIZER | 0x0d32)
#घोषणा WACOM_HID_WD_OFFSETBOTTOM       (WACOM_HID_UP_WACOMDIGITIZER | 0x0d33)
#घोषणा WACOM_HID_WD_DATAMODE           (WACOM_HID_UP_WACOMDIGITIZER | 0x1002)
#घोषणा WACOM_HID_WD_DIGITIZERINFO      (WACOM_HID_UP_WACOMDIGITIZER | 0x1013)
#घोषणा WACOM_HID_WD_TOUCH_RING_SETTING (WACOM_HID_UP_WACOMDIGITIZER | 0x1032)
#घोषणा WACOM_HID_UP_G9                 0xff090000
#घोषणा WACOM_HID_G9_PEN                (WACOM_HID_UP_G9 | 0x02)
#घोषणा WACOM_HID_G9_TOUCHSCREEN        (WACOM_HID_UP_G9 | 0x11)
#घोषणा WACOM_HID_UP_G11                0xff110000
#घोषणा WACOM_HID_G11_PEN               (WACOM_HID_UP_G11 | 0x02)
#घोषणा WACOM_HID_G11_TOUCHSCREEN       (WACOM_HID_UP_G11 | 0x11)
#घोषणा WACOM_HID_UP_WACOMTOUCH         0xff000000
#घोषणा WACOM_HID_WT_TOUCHSCREEN        (WACOM_HID_UP_WACOMTOUCH | 0x04)
#घोषणा WACOM_HID_WT_TOUCHPAD           (WACOM_HID_UP_WACOMTOUCH | 0x05)
#घोषणा WACOM_HID_WT_CONTACTMAX         (WACOM_HID_UP_WACOMTOUCH | 0x55)
#घोषणा WACOM_HID_WT_SERIALNUMBER       (WACOM_HID_UP_WACOMTOUCH | 0x5b)
#घोषणा WACOM_HID_WT_X                  (WACOM_HID_UP_WACOMTOUCH | 0x130)
#घोषणा WACOM_HID_WT_Y                  (WACOM_HID_UP_WACOMTOUCH | 0x131)
#घोषणा WACOM_HID_WT_REPORT_VALID       (WACOM_HID_UP_WACOMTOUCH | 0x1d0)

#घोषणा WACOM_BATTERY_USAGE(f)	(((f)->hid == HID_DG_BATTERYSTRENGTH) || \
				 ((f)->hid == WACOM_HID_WD_BATTERY_CHARGING) || \
				 ((f)->hid == WACOM_HID_WD_BATTERY_LEVEL))

#घोषणा WACOM_PAD_FIELD(f)	(((f)->physical == HID_DG_TABLETFUNCTIONKEY) || \
				 ((f)->physical == WACOM_HID_WD_DIGITIZERFNKEYS) || \
				 ((f)->physical == WACOM_HID_WD_DIGITIZERINFO))

#घोषणा WACOM_PEN_FIELD(f)	(((f)->logical == HID_DG_STYLUS) || \
				 ((f)->physical == HID_DG_STYLUS) || \
				 ((f)->physical == HID_DG_PEN) || \
				 ((f)->application == HID_DG_PEN) || \
				 ((f)->application == HID_DG_DIGITIZER) || \
				 ((f)->application == WACOM_HID_WD_PEN) || \
				 ((f)->application == WACOM_HID_WD_DIGITIZER) || \
				 ((f)->application == WACOM_HID_G9_PEN) || \
				 ((f)->application == WACOM_HID_G11_PEN))
#घोषणा WACOM_FINGER_FIELD(f)	(((f)->logical == HID_DG_FINGER) || \
				 ((f)->physical == HID_DG_FINGER) || \
				 ((f)->application == HID_DG_TOUCHSCREEN) || \
				 ((f)->application == WACOM_HID_G9_TOUCHSCREEN) || \
				 ((f)->application == WACOM_HID_G11_TOUCHSCREEN) || \
				 ((f)->application == WACOM_HID_WT_TOUCHPAD) || \
				 ((f)->application == HID_DG_TOUCHPAD))

#घोषणा WACOM_सूचीECT_DEVICE(f)	(((f)->application == HID_DG_TOUCHSCREEN) || \
				 ((f)->application == WACOM_HID_WT_TOUCHSCREEN) || \
				 ((f)->application == HID_DG_PEN) || \
				 ((f)->application == WACOM_HID_WD_PEN))

क्रमागत अणु
	PENPARTNER = 0,
	GRAPHIRE,
	GRAPHIRE_BT,
	WACOM_G4,
	PTU,
	PL,
	DTU,
	DTUS,
	DTUSX,
	INTUOS,
	INTUOS3S,
	INTUOS3,
	INTUOS3L,
	INTUOS4S,
	INTUOS4,
	INTUOS4WL,
	INTUOS4L,
	INTUOS5S,
	INTUOS5,
	INTUOS5L,
	INTUOSPS,
	INTUOSPM,
	INTUOSPL,
	INTUOSP2_BT,
	INTUOSP2S_BT,
	INTUOSHT3_BT,
	WACOM_21UX2,
	WACOM_22HD,
	DTK,
	WACOM_24HD,
	WACOM_27QHD,
	CINTIQ_HYBRID,
	CINTIQ_COMPANION_2,
	CINTIQ,
	WACOM_BEE,
	WACOM_13HD,
	WACOM_MO,
	BAMBOO_PEN,
	INTUOSHT,
	INTUOSHT2,
	BAMBOO_TOUCH,
	BAMBOO_PT,
	WACOM_24HDT,
	WACOM_27QHDT,
	BAMBOO_PAD,
	WIRELESS,
	REMOTE,
	TABLETPC,   /* add new TPC below */
	TABLETPCE,
	TABLETPC2FG,
	MTSCREEN,
	MTTPC,
	MTTPC_B,
	HID_GENERIC,
	MAX_TYPE
पूर्ण;

काष्ठा wacom_features अणु
	स्थिर अक्षर *name;
	पूर्णांक x_max;
	पूर्णांक y_max;
	पूर्णांक pressure_max;
	पूर्णांक distance_max;
	पूर्णांक type;
	पूर्णांक x_resolution;
	पूर्णांक y_resolution;
	पूर्णांक numbered_buttons;
	पूर्णांक offset_left;
	पूर्णांक offset_right;
	पूर्णांक offset_top;
	पूर्णांक offset_bottom;
	पूर्णांक device_type;
	पूर्णांक x_phy;
	पूर्णांक y_phy;
	अचिन्हित unit;
	पूर्णांक unitExpo;
	पूर्णांक x_fuzz;
	पूर्णांक y_fuzz;
	पूर्णांक pressure_fuzz;
	पूर्णांक distance_fuzz;
	पूर्णांक tilt_fuzz;
	अचिन्हित quirks;
	अचिन्हित touch_max;
	पूर्णांक oVid;
	पूर्णांक oPid;
	पूर्णांक pktlen;
	bool check_क्रम_hid_type;
	पूर्णांक hid_type;
पूर्ण;

काष्ठा wacom_shared अणु
	bool stylus_in_proximity;
	bool touch_करोwn;
	/* क्रम wireless device to access USB पूर्णांकerfaces */
	अचिन्हित touch_max;
	पूर्णांक type;
	काष्ठा input_dev *touch_input;
	काष्ठा hid_device *pen;
	काष्ठा hid_device *touch;
	bool has_mute_touch_चयन;
	bool is_touch_on;
पूर्ण;

काष्ठा hid_data अणु
	__s16 inpuपंचांगode;	/* InputMode HID feature, -1 अगर non-existent */
	__s16 inpuपंचांगode_index;	/* InputMode HID feature index in the report */
	bool sense_state;
	bool inrange_state;
	bool invert_state;
	bool tipचयन;
	bool barrelचयन;
	bool barrelचयन2;
	bool serialhi;
	पूर्णांक x;
	पूर्णांक y;
	पूर्णांक pressure;
	पूर्णांक width;
	पूर्णांक height;
	पूर्णांक id;
	पूर्णांक cc_report;
	पूर्णांक cc_index;
	पूर्णांक cc_value_index;
	पूर्णांक last_slot_field;
	पूर्णांक num_expected;
	पूर्णांक num_received;
	पूर्णांक bat_status;
	पूर्णांक battery_capacity;
	पूर्णांक bat_अक्षरging;
	पूर्णांक bat_connected;
	पूर्णांक ps_connected;
	bool pad_input_event_flag;
पूर्ण;

काष्ठा wacom_remote_data अणु
	काष्ठा अणु
		u32 serial;
		bool connected;
	पूर्ण remote[WACOM_MAX_REMOTES];
पूर्ण;

काष्ठा wacom_wac अणु
	अक्षर name[WACOM_NAME_MAX];
	अक्षर pen_name[WACOM_NAME_MAX];
	अक्षर touch_name[WACOM_NAME_MAX];
	अक्षर pad_name[WACOM_NAME_MAX];
	अचिन्हित अक्षर data[WACOM_PKGLEN_MAX];
	पूर्णांक tool[2];
	पूर्णांक id[2];
	__u64 serial[2];
	bool reporting_data;
	काष्ठा wacom_features features;
	काष्ठा wacom_shared *shared;
	काष्ठा input_dev *pen_input;
	काष्ठा input_dev *touch_input;
	काष्ठा input_dev *pad_input;
	काष्ठा kfअगरo_rec_ptr_2 *pen_fअगरo;
	पूर्णांक pid;
	पूर्णांक num_contacts_left;
	u8 bt_features;
	u8 bt_high_speed;
	पूर्णांक mode_report;
	पूर्णांक mode_value;
	काष्ठा hid_data hid_data;
	bool has_mute_touch_चयन;
	bool has_mode_change;
	bool is_direct_mode;
	bool is_invalid_bt_frame;
पूर्ण;

#पूर्ण_अगर
