<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Elantech Touchpad driver (v6)
 *
 * Copyright (C) 2007-2009 Arjan Opmeer <arjan@opmeer.net>
 *
 * Trademarks are the property of their respective owners.
 */

#अगर_अघोषित _ELANTECH_H
#घोषणा _ELANTECH_H

/*
 * Command values क्रम Synaptics style queries
 */
#घोषणा ETP_FW_ID_QUERY			0x00
#घोषणा ETP_FW_VERSION_QUERY		0x01
#घोषणा ETP_CAPABILITIES_QUERY		0x02
#घोषणा ETP_SAMPLE_QUERY		0x03
#घोषणा ETP_RESOLUTION_QUERY		0x04
#घोषणा ETP_ICBODY_QUERY		0x05

/*
 * Command values क्रम रेजिस्टर पढ़ोing or writing
 */
#घोषणा ETP_REGISTER_READ		0x10
#घोषणा ETP_REGISTER_WRITE		0x11
#घोषणा ETP_REGISTER_READWRITE		0x00

/*
 * Hardware version 2 custom PS/2 command value
 */
#घोषणा ETP_PS2_CUSTOM_COMMAND		0xf8

/*
 * Times to retry a ps2_command and millisecond delay between tries
 */
#घोषणा ETP_PS2_COMMAND_TRIES		3
#घोषणा ETP_PS2_COMMAND_DELAY		500

/*
 * Times to try to पढ़ो back a रेजिस्टर and millisecond delay between tries
 */
#घोषणा ETP_READ_BACK_TRIES		5
#घोषणा ETP_READ_BACK_DELAY		2000

/*
 * Register biपंचांगasks क्रम hardware version 1
 */
#घोषणा ETP_R10_ABSOLUTE_MODE		0x04
#घोषणा ETP_R11_4_BYTE_MODE		0x02

/*
 * Capability biपंचांगasks
 */
#घोषणा ETP_CAP_HAS_ROCKER		0x04

/*
 * One hard to find application note states that X axis range is 0 to 576
 * and Y axis range is 0 to 384 क्रम harware version 1.
 * Edge fuzz might be necessary because of bezel around the touchpad
 */
#घोषणा ETP_EDGE_FUZZ_V1		32

#घोषणा ETP_XMIN_V1			(  0 + ETP_EDGE_FUZZ_V1)
#घोषणा ETP_XMAX_V1			(576 - ETP_EDGE_FUZZ_V1)
#घोषणा ETP_YMIN_V1			(  0 + ETP_EDGE_FUZZ_V1)
#घोषणा ETP_YMAX_V1			(384 - ETP_EDGE_FUZZ_V1)

/*
 * The resolution क्रम older v2 hardware द्विगुनd.
 * (newer v2's firmware provides command so we can query)
 */
#घोषणा ETP_XMIN_V2			0
#घोषणा ETP_XMAX_V2			1152
#घोषणा ETP_YMIN_V2			0
#घोषणा ETP_YMAX_V2			768

#घोषणा ETP_PMIN_V2			0
#घोषणा ETP_PMAX_V2			255
#घोषणा ETP_WMIN_V2			0
#घोषणा ETP_WMAX_V2			15

/*
 * v3 hardware has 2 kinds of packet types,
 * v4 hardware has 3.
 */
#घोषणा PACKET_UNKNOWN			0x01
#घोषणा PACKET_DEBOUNCE			0x02
#घोषणा PACKET_V3_HEAD			0x03
#घोषणा PACKET_V3_TAIL			0x04
#घोषणा PACKET_V4_HEAD			0x05
#घोषणा PACKET_V4_MOTION		0x06
#घोषणा PACKET_V4_STATUS		0x07
#घोषणा PACKET_TRACKPOINT		0x08

/*
 * track up to 5 fingers क्रम v4 hardware
 */
#घोषणा ETP_MAX_FINGERS			5

/*
 * weight value क्रम v4 hardware
 */
#घोषणा ETP_WEIGHT_VALUE		5

/*
 * Bus inक्रमmation on 3rd byte of query ETP_RESOLUTION_QUERY(0x04)
 */
#घोषणा ETP_BUS_PS2_ONLY		0
#घोषणा ETP_BUS_SMB_ALERT_ONLY		1
#घोषणा ETP_BUS_SMB_HST_NTFY_ONLY	2
#घोषणा ETP_BUS_PS2_SMB_ALERT		3
#घोषणा ETP_BUS_PS2_SMB_HST_NTFY	4

/*
 * New ICs are either using SMBus Host Notअगरy or just plain PS2.
 *
 * ETP_FW_VERSION_QUERY is:
 * Byte 1:
 *  - bit 0..3: IC BODY
 * Byte 2:
 *  - bit 4: HiddenButton
 *  - bit 5: PS2_SMBUS_NOTIFY
 *  - bit 6: PS2CRCCheck
 */
#घोषणा ETP_NEW_IC_SMBUS_HOST_NOTIFY(fw_version)	\
		((((fw_version) & 0x0f2000) == 0x0f2000) && \
		 ((fw_version) & 0x0000ff) > 0)

/*
 * The base position क्रम one finger, v4 hardware
 */
काष्ठा finger_pos अणु
	अचिन्हित पूर्णांक x;
	अचिन्हित पूर्णांक y;
पूर्ण;

काष्ठा elantech_device_info अणु
	अचिन्हित अक्षर capabilities[3];
	अचिन्हित अक्षर samples[3];
	अचिन्हित अक्षर debug;
	अचिन्हित अक्षर hw_version;
	अचिन्हित अक्षर pattern;
	अचिन्हित पूर्णांक fw_version;
	अचिन्हित पूर्णांक ic_version;
	अचिन्हित पूर्णांक product_id;
	अचिन्हित पूर्णांक x_min;
	अचिन्हित पूर्णांक y_min;
	अचिन्हित पूर्णांक x_max;
	अचिन्हित पूर्णांक y_max;
	अचिन्हित पूर्णांक x_res;
	अचिन्हित पूर्णांक y_res;
	अचिन्हित पूर्णांक x_traces;
	अचिन्हित पूर्णांक y_traces;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक bus;
	bool paritycheck;
	bool jumpy_cursor;
	bool reports_pressure;
	bool crc_enabled;
	bool set_hw_resolution;
	bool has_trackpoपूर्णांक;
	bool has_middle_button;
	पूर्णांक (*send_cmd)(काष्ठा psmouse *psmouse, अचिन्हित अक्षर c,
			अचिन्हित अक्षर *param);
पूर्ण;

काष्ठा elantech_data अणु
	काष्ठा input_dev *tp_dev;	/* Relative device क्रम trackpoपूर्णांक */
	अक्षर tp_phys[32];
	अचिन्हित अक्षर reg_07;
	अचिन्हित अक्षर reg_10;
	अचिन्हित अक्षर reg_11;
	अचिन्हित अक्षर reg_20;
	अचिन्हित अक्षर reg_21;
	अचिन्हित अक्षर reg_22;
	अचिन्हित अक्षर reg_23;
	अचिन्हित अक्षर reg_24;
	अचिन्हित अक्षर reg_25;
	अचिन्हित अक्षर reg_26;
	अचिन्हित पूर्णांक single_finger_reports;
	अचिन्हित पूर्णांक y_max;
	अचिन्हित पूर्णांक width;
	काष्ठा finger_pos mt[ETP_MAX_FINGERS];
	अचिन्हित अक्षर parity[256];
	काष्ठा elantech_device_info info;
	व्योम (*original_set_rate)(काष्ठा psmouse *psmouse, अचिन्हित पूर्णांक rate);
पूर्ण;

पूर्णांक elantech_detect(काष्ठा psmouse *psmouse, bool set_properties);
पूर्णांक elantech_init_ps2(काष्ठा psmouse *psmouse);

#अगर_घोषित CONFIG_MOUSE_PS2_ELANTECH
पूर्णांक elantech_init(काष्ठा psmouse *psmouse);
#अन्यथा
अटल अंतरभूत पूर्णांक elantech_init(काष्ठा psmouse *psmouse)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर /* CONFIG_MOUSE_PS2_ELANTECH */

पूर्णांक elantech_init_smbus(काष्ठा psmouse *psmouse);

#पूर्ण_अगर
