<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ALPS touchpad PS/2 mouse driver
 *
 * Copyright (c) 2003 Peter Osterlund <petero2@telia.com>
 * Copyright (c) 2005 Vojtech Pavlik <vojtech@suse.cz>
 */

#अगर_अघोषित _ALPS_H
#घोषणा _ALPS_H

#समावेश <linux/input/mt.h>

#घोषणा ALPS_PROTO_V1		0x100
#घोषणा ALPS_PROTO_V2		0x200
#घोषणा ALPS_PROTO_V3		0x300
#घोषणा ALPS_PROTO_V3_RUSHMORE	0x310
#घोषणा ALPS_PROTO_V4		0x400
#घोषणा ALPS_PROTO_V5		0x500
#घोषणा ALPS_PROTO_V6		0x600
#घोषणा ALPS_PROTO_V7		0x700	/* t3btl t4s */
#घोषणा ALPS_PROTO_V8		0x800	/* SS4btl SS4s */
#घोषणा ALPS_PROTO_V9		0x900	/* ss3btl */

#घोषणा MAX_TOUCHES	4

#घोषणा DOLPHIN_COUNT_PER_ELECTRODE	64
#घोषणा DOLPHIN_PROखाता_XOFFSET		8	/* x-electrode offset */
#घोषणा DOLPHIN_PROखाता_YOFFSET		1	/* y-electrode offset */

/*
 * क्रमागत SS4_PACKET_ID - defines the packet type क्रम V8
 * SS4_PACKET_ID_IDLE: There's no finger and no button activity.
 * SS4_PACKET_ID_ONE: There's one finger on touchpad
 *  or there's button activities.
 * SS4_PACKET_ID_TWO: There's two or more fingers on touchpad
 * SS4_PACKET_ID_MULTI: There's three or more fingers on touchpad
 * SS4_PACKET_ID_STICK: A stick poपूर्णांकer packet
*/
क्रमागत SS4_PACKET_ID अणु
	SS4_PACKET_ID_IDLE = 0,
	SS4_PACKET_ID_ONE,
	SS4_PACKET_ID_TWO,
	SS4_PACKET_ID_MULTI,
	SS4_PACKET_ID_STICK,
पूर्ण;

#घोषणा SS4_COUNT_PER_ELECTRODE		256
#घोषणा SS4_NUMSENSOR_XOFFSET		7
#घोषणा SS4_NUMSENSOR_YOFFSET		7
#घोषणा SS4_MIN_PITCH_MM		50

#घोषणा SS4_MASK_NORMAL_BUTTONS		0x07

#घोषणा SS4PLUS_COUNT_PER_ELECTRODE	128
#घोषणा SS4PLUS_NUMSENSOR_XOFFSET	16
#घोषणा SS4PLUS_NUMSENSOR_YOFFSET	5
#घोषणा SS4PLUS_MIN_PITCH_MM		37

#घोषणा IS_SS4PLUS_DEV(_b)	(((_b[0]) == 0x73) &&	\
				 ((_b[1]) == 0x03) &&	\
				 ((_b[2]) == 0x28)		\
				)

#घोषणा SS4_IS_IDLE_V2(_b)	(((_b[0]) == 0x18) &&		\
				 ((_b[1]) == 0x10) &&		\
				 ((_b[2]) == 0x00) &&		\
				 ((_b[3] & 0x88) == 0x08) &&	\
				 ((_b[4]) == 0x10) &&		\
				 ((_b[5]) == 0x00)		\
				)

#घोषणा SS4_1F_X_V2(_b)		(((_b[0]) & 0x0007) |		\
				 ((_b[1] << 3) & 0x0078) |	\
				 ((_b[1] << 2) & 0x0380) |	\
				 ((_b[2] << 5) & 0x1C00)	\
				)

#घोषणा SS4_1F_Y_V2(_b)		(((_b[2]) & 0x000F) |		\
				 ((_b[3] >> 2) & 0x0030) |	\
				 ((_b[4] << 6) & 0x03C0) |	\
				 ((_b[4] << 5) & 0x0C00)	\
				)

#घोषणा SS4_1F_Z_V2(_b)		(((_b[5]) & 0x0F) |		\
				 ((_b[5] >> 1) & 0x70) |	\
				 ((_b[4]) & 0x80)		\
				)

#घोषणा SS4_1F_LFB_V2(_b)	(((_b[2] >> 4) & 0x01) == 0x01)

#घोषणा SS4_MF_LF_V2(_b, _i)	((_b[1 + (_i) * 3] & 0x0004) == 0x0004)

#घोषणा SS4_BTN_V2(_b)		((_b[0] >> 5) & SS4_MASK_NORMAL_BUTTONS)

#घोषणा SS4_STD_MF_X_V2(_b, _i)	(((_b[0 + (_i) * 3] << 5) & 0x00E0) |	\
				 ((_b[1 + _i * 3]  << 5) & 0x1F00)	\
				)

#घोषणा SS4_PLUS_STD_MF_X_V2(_b, _i) (((_b[0 + (_i) * 3] << 4) & 0x0070) | \
				 ((_b[1 + (_i) * 3]  << 4) & 0x0F80)	\
				)

#घोषणा SS4_STD_MF_Y_V2(_b, _i)	(((_b[1 + (_i) * 3] << 3) & 0x0010) |	\
				 ((_b[2 + (_i) * 3] << 5) & 0x01E0) |	\
				 ((_b[2 + (_i) * 3] << 4) & 0x0E00)	\
				)

#घोषणा SS4_BTL_MF_X_V2(_b, _i)	(SS4_STD_MF_X_V2(_b, _i) |		\
				 ((_b[0 + (_i) * 3] >> 3) & 0x0010)	\
				)

#घोषणा SS4_PLUS_BTL_MF_X_V2(_b, _i) (SS4_PLUS_STD_MF_X_V2(_b, _i) |	\
				 ((_b[0 + (_i) * 3] >> 4) & 0x0008)	\
				)

#घोषणा SS4_BTL_MF_Y_V2(_b, _i)	(SS4_STD_MF_Y_V2(_b, _i) | \
				 ((_b[0 + (_i) * 3] >> 3) & 0x0008)	\
				)

#घोषणा SS4_MF_Z_V2(_b, _i)	(((_b[1 + (_i) * 3]) & 0x0001) |	\
				 ((_b[1 + (_i) * 3] >> 1) & 0x0002)	\
				)

#घोषणा SS4_IS_MF_CONTINUE(_b)	((_b[2] & 0x10) == 0x10)
#घोषणा SS4_IS_5F_DETECTED(_b)	((_b[2] & 0x10) == 0x10)

#घोषणा SS4_TS_X_V2(_b)		(s8)(				\
				 ((_b[0] & 0x01) << 7) |	\
				 (_b[1] & 0x7F)		\
				)

#घोषणा SS4_TS_Y_V2(_b)		-(s8)(				\
				 ((_b[3] & 0x01) << 7) |	\
				 (_b[2] & 0x7F)		\
				)

#घोषणा SS4_TS_Z_V2(_b)		(s8)(_b[4] & 0x7F)


#घोषणा SS4_MFPACKET_NO_AX		8160	/* X-Coordinate value */
#घोषणा SS4_MFPACKET_NO_AY		4080	/* Y-Coordinate value */
#घोषणा SS4_MFPACKET_NO_AX_BL		8176	/* Buttonless X-Coord value */
#घोषणा SS4_MFPACKET_NO_AY_BL		4088	/* Buttonless Y-Coord value */
#घोषणा SS4_PLUS_MFPACKET_NO_AX		4080	/* SS4 PLUS, X */
#घोषणा SS4_PLUS_MFPACKET_NO_AX_BL	4088	/* Buttonless SS4 PLUS, X */

/*
 * क्रमागत V7_PACKET_ID - defines the packet type क्रम V7
 * V7_PACKET_ID_IDLE: There's no finger and no button activity.
 * V7_PACKET_ID_TWO: There's one or two non-resting fingers on touchpad
 *  or there's button activities.
 * V7_PACKET_ID_MULTI: There are at least three non-resting fingers.
 * V7_PACKET_ID_NEW: The finger position in slot is not जारीs from
 *  previous packet.
*/
क्रमागत V7_PACKET_ID अणु
	 V7_PACKET_ID_IDLE,
	 V7_PACKET_ID_TWO,
	 V7_PACKET_ID_MULTI,
	 V7_PACKET_ID_NEW,
	 V7_PACKET_ID_UNKNOWN,
पूर्ण;

/**
 * काष्ठा alps_protocol_info - inक्रमmation about protocol used by a device
 * @version: Indicates V1/V2/V3/...
 * @byte0: Helps figure out whether a position report packet matches the
 *   known क्रमmat क्रम this model.  The first byte of the report, ANDed with
 *   mask0, should match byte0.
 * @mask0: The mask used to check the first byte of the report.
 * @flags: Additional device capabilities (passthrough port, trackstick, etc.).
 */
काष्ठा alps_protocol_info अणु
	u16 version;
	u8 byte0, mask0;
	अचिन्हित पूर्णांक flags;
पूर्ण;

/**
 * काष्ठा alps_model_info - touchpad ID table
 * @signature: E7 response string to match.
 * @protocol_info: inक्रमmation about protocol used by the device.
 *
 * Many (but not all) ALPS touchpads can be identअगरied by looking at the
 * values वापसed in the "E7 report" and/or the "EC report."  This table
 * lists a number of such touchpads.
 */
काष्ठा alps_model_info अणु
	u8 signature[3];
	काष्ठा alps_protocol_info protocol_info;
पूर्ण;

/**
 * काष्ठा alps_nibble_commands - encodings क्रम रेजिस्टर accesses
 * @command: PS/2 command used क्रम the nibble
 * @data: Data supplied as an argument to the PS/2 command, अगर applicable
 *
 * The ALPS protocol uses magic sequences to transmit binary data to the
 * touchpad, as it is generally not OK to send arbitrary bytes out the
 * PS/2 port.  Each of the sequences in this table sends one nibble of the
 * रेजिस्टर address or (ग_लिखो) data.  Dअगरferent versions of the ALPS protocol
 * use slightly dअगरferent encodings.
 */
काष्ठा alps_nibble_commands अणु
	पूर्णांक command;
	अचिन्हित अक्षर data;
पूर्ण;

काष्ठा alps_biपंचांगap_poपूर्णांक अणु
	पूर्णांक start_bit;
	पूर्णांक num_bits;
पूर्ण;

/**
 * काष्ठा alps_fields - decoded version of the report packet
 * @x_map: Biपंचांगap of active X positions क्रम MT.
 * @y_map: Biपंचांगap of active Y positions क्रम MT.
 * @fingers: Number of fingers क्रम MT.
 * @pressure: Pressure.
 * @st: position क्रम ST.
 * @mt: position क्रम MT.
 * @first_mp: Packet is the first of a multi-packet report.
 * @is_mp: Packet is part of a multi-packet report.
 * @left: Left touchpad button is active.
 * @right: Right touchpad button is active.
 * @middle: Middle touchpad button is active.
 * @ts_left: Left trackstick button is active.
 * @ts_right: Right trackstick button is active.
 * @ts_middle: Middle trackstick button is active.
 */
काष्ठा alps_fields अणु
	अचिन्हित पूर्णांक x_map;
	अचिन्हित पूर्णांक y_map;
	अचिन्हित पूर्णांक fingers;

	पूर्णांक pressure;
	काष्ठा input_mt_pos st;
	काष्ठा input_mt_pos mt[MAX_TOUCHES];

	अचिन्हित पूर्णांक first_mp:1;
	अचिन्हित पूर्णांक is_mp:1;

	अचिन्हित पूर्णांक left:1;
	अचिन्हित पूर्णांक right:1;
	अचिन्हित पूर्णांक middle:1;

	अचिन्हित पूर्णांक ts_left:1;
	अचिन्हित पूर्णांक ts_right:1;
	अचिन्हित पूर्णांक ts_middle:1;
पूर्ण;

/**
 * काष्ठा alps_data - निजी data काष्ठाure क्रम the ALPS driver
 * @psmouse: Poपूर्णांकer to parent psmouse device
 * @dev2: Trackstick device (can be शून्य).
 * @dev3: Generic PS/2 mouse (can be शून्य, delayed रेजिस्टरing).
 * @phys2: Physical path क्रम the trackstick device.
 * @phys3: Physical path क्रम the generic PS/2 mouse.
 * @dev3_रेजिस्टर_work: Delayed work क्रम रेजिस्टरing PS/2 mouse.
 * @nibble_commands: Command mapping used क्रम touchpad रेजिस्टर accesses.
 * @addr_command: Command used to tell the touchpad that a रेजिस्टर address
 *   follows.
 * @proto_version: Indicates V1/V2/V3/...
 * @byte0: Helps figure out whether a position report packet matches the
 *   known क्रमmat क्रम this model.  The first byte of the report, ANDed with
 *   mask0, should match byte0.
 * @mask0: The mask used to check the first byte of the report.
 * @fw_ver: cached copy of firmware version (EC report)
 * @flags: Additional device capabilities (passthrough port, trackstick, etc.).
 * @x_max: Largest possible X position value.
 * @y_max: Largest possible Y position value.
 * @x_bits: Number of X bits in the MT biपंचांगap.
 * @y_bits: Number of Y bits in the MT biपंचांगap.
 * @hw_init: Protocol-specअगरic hardware init function.
 * @process_packet: Protocol-specअगरic function to process a report packet.
 * @decode_fields: Protocol-specअगरic function to पढ़ो packet bitfields.
 * @set_असल_params: Protocol-specअगरic function to configure the input_dev.
 * @prev_fin: Finger bit from previous packet.
 * @multi_packet: Multi-packet data in progress.
 * @multi_data: Saved multi-packet data.
 * @f: Decoded packet data fields.
 * @quirks: Biपंचांगap of ALPS_QUIRK_*.
 * @समयr: Timer क्रम flushing out the final report packet in the stream.
 */
काष्ठा alps_data अणु
	काष्ठा psmouse *psmouse;
	काष्ठा input_dev *dev2;
	काष्ठा input_dev *dev3;
	अक्षर phys2[32];
	अक्षर phys3[32];
	काष्ठा delayed_work dev3_रेजिस्टर_work;

	/* these are स्वतःdetected when the device is identअगरied */
	स्थिर काष्ठा alps_nibble_commands *nibble_commands;
	पूर्णांक addr_command;
	u16 proto_version;
	u8 byte0, mask0;
	u8 dev_id[3];
	u8 fw_ver[3];
	पूर्णांक flags;
	पूर्णांक x_max;
	पूर्णांक y_max;
	पूर्णांक x_bits;
	पूर्णांक y_bits;
	अचिन्हित पूर्णांक x_res;
	अचिन्हित पूर्णांक y_res;

	पूर्णांक (*hw_init)(काष्ठा psmouse *psmouse);
	व्योम (*process_packet)(काष्ठा psmouse *psmouse);
	पूर्णांक (*decode_fields)(काष्ठा alps_fields *f, अचिन्हित अक्षर *p,
			      काष्ठा psmouse *psmouse);
	व्योम (*set_असल_params)(काष्ठा alps_data *priv, काष्ठा input_dev *dev1);

	पूर्णांक prev_fin;
	पूर्णांक multi_packet;
	पूर्णांक second_touch;
	अचिन्हित अक्षर multi_data[6];
	काष्ठा alps_fields f;
	u8 quirks;
	काष्ठा समयr_list समयr;
पूर्ण;

#घोषणा ALPS_QUIRK_TRACKSTICK_BUTTONS	1 /* trakcstick buttons in trackstick packet */

पूर्णांक alps_detect(काष्ठा psmouse *psmouse, bool set_properties);
पूर्णांक alps_init(काष्ठा psmouse *psmouse);

#पूर्ण_अगर
