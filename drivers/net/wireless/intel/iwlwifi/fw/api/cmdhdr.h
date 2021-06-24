<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_cmdhdr_h__
#घोषणा __iwl_fw_api_cmdhdr_h__

/**
 * DOC: Host command section
 *
 * A host command is a command issued by the upper layer to the fw. There are
 * several versions of fw that have several APIs. The transport layer is
 * completely agnostic to these dअगरferences.
 * The transport करोes provide helper functionality (i.e. SYNC / ASYNC mode),
 */
#घोषणा SEQ_TO_QUEUE(s)	(((s) >> 8) & 0x1f)
#घोषणा QUEUE_TO_SEQ(q)	(((q) & 0x1f) << 8)
#घोषणा SEQ_TO_INDEX(s)	((s) & 0xff)
#घोषणा INDEX_TO_SEQ(i)	((i) & 0xff)
#घोषणा SEQ_RX_FRAME	cpu_to_le16(0x8000)

/*
 * those functions retrieve specअगरic inक्रमmation from
 * the id field in the iwl_host_cmd काष्ठा which contains
 * the command id, the group id and the version of the command
 * and vice versa
*/
अटल अंतरभूत u8 iwl_cmd_opcode(u32 cmdid)
अणु
	वापस cmdid & 0xFF;
पूर्ण

अटल अंतरभूत u8 iwl_cmd_groupid(u32 cmdid)
अणु
	वापस ((cmdid & 0xFF00) >> 8);
पूर्ण

अटल अंतरभूत u8 iwl_cmd_version(u32 cmdid)
अणु
	वापस ((cmdid & 0xFF0000) >> 16);
पूर्ण

अटल अंतरभूत u32 iwl_cmd_id(u8 opcode, u8 groupid, u8 version)
अणु
	वापस opcode + (groupid << 8) + (version << 16);
पूर्ण

/* make u16 wide id out of u8 group and opcode */
#घोषणा WIDE_ID(grp, opcode) (((grp) << 8) | (opcode))
#घोषणा DEF_ID(opcode) ((1 << 8) | (opcode))

/* due to the conversion, this group is special; new groups
 * should be defined in the appropriate fw-api header files
 */
#घोषणा IWL_ALWAYS_LONG_GROUP	1

/**
 * काष्ठा iwl_cmd_header - (लघु) command header क्रमmat
 *
 * This header क्रमmat appears in the beginning of each command sent from the
 * driver, and each response/notअगरication received from uCode.
 */
काष्ठा iwl_cmd_header अणु
	/**
	 * @cmd: Command ID: REPLY_RXON, etc.
	 */
	u8 cmd;
	/**
	 * @group_id: group ID, क्रम commands with groups
	 */
	u8 group_id;
	/**
	 * @sequence:
	 * Sequence number क्रम the command.
	 *
	 * The driver sets up the sequence number to values of its choosing.
	 * uCode करोes not use this value, but passes it back to the driver
	 * when sending the response to each driver-originated command, so
	 * the driver can match the response to the command.  Since the values
	 * करोn't get used by uCode, the driver may set up an arbitrary क्रमmat.
	 *
	 * There is one exception:  uCode sets bit 15 when it originates
	 * the response/notअगरication, i.e. when the response/notअगरication
	 * is not a direct response to a command sent by the driver.  For
	 * example, uCode issues REPLY_RX when it sends a received frame
	 * to the driver; it is not a direct response to any driver command.
	 *
	 * The Linux driver uses the following क्रमmat:
	 *
	 *  0:7		tfd index - position within TX queue
	 *  8:12	TX queue id
	 *  13:14	reserved
	 *  15		unsolicited RX or uCode-originated notअगरication
	 */
	__le16 sequence;
पूर्ण __packed;

/**
 * काष्ठा iwl_cmd_header_wide
 *
 * This header क्रमmat appears in the beginning of each command sent from the
 * driver, and each response/notअगरication received from uCode.
 * this is the wide version that contains more inक्रमmation about the command
 * like length, version and command type
 *
 * @cmd: command ID, like in &काष्ठा iwl_cmd_header
 * @group_id: group ID, like in &काष्ठा iwl_cmd_header
 * @sequence: sequence, like in &काष्ठा iwl_cmd_header
 * @length: length of the command
 * @reserved: reserved
 * @version: command version
 */
काष्ठा iwl_cmd_header_wide अणु
	u8 cmd;
	u8 group_id;
	__le16 sequence;
	__le16 length;
	u8 reserved;
	u8 version;
पूर्ण __packed;

/**
 * काष्ठा iwl_calib_res_notअगर_phy_db - Receive phy db chunk after calibrations
 * @type: type of the result - mostly ignored
 * @length: length of the data
 * @data: data, length in @length
 */
काष्ठा iwl_calib_res_notअगर_phy_db अणु
	__le16 type;
	__le16 length;
	u8 data[];
पूर्ण __packed;

/**
 * काष्ठा iwl_phy_db_cmd - configure operational ucode
 * @type: type of the data
 * @length: length of the data
 * @data: data, length in @length
 */
काष्ठा iwl_phy_db_cmd अणु
	__le16 type;
	__le16 length;
	u8 data[];
पूर्ण __packed;

/**
 * काष्ठा iwl_cmd_response - generic response काष्ठा क्रम most commands
 * @status: status of the command asked, changes क्रम each one
 */
काष्ठा iwl_cmd_response अणु
	__le32 status;
पूर्ण;

#पूर्ण_अगर /* __iwl_fw_api_cmdhdr_h__ */
