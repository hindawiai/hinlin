<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2014,2016 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */
#अगर_अघोषित __WIL_FW_H__
#घोषणा __WIL_FW_H__

#घोषणा WIL_FW_SIGNATURE (0x36323130) /* '0126' */
#घोषणा WIL_FW_FMT_VERSION (1) /* क्रमmat version driver supports */

क्रमागत wil_fw_record_type अणु
	wil_fw_type_comment = 1,
	wil_fw_type_data = 2,
	wil_fw_type_fill = 3,
	wil_fw_type_action = 4,
	wil_fw_type_verअगरy = 5,
	wil_fw_type_file_header = 6,
	wil_fw_type_direct_ग_लिखो = 7,
	wil_fw_type_gateway_data = 8,
	wil_fw_type_gateway_data4 = 9,
पूर्ण;

काष्ठा wil_fw_record_head अणु
	__le16 type; /* क्रमागत wil_fw_record_type */
	__le16 flags; /* to be defined */
	__le32 size; /* whole record, bytes after head */
पूर्ण __packed;

/* data block. ग_लिखो starting from @addr
 * data_size inferred from the @head.size. For this हाल,
 * data_size = @head.size - दुरत्व(काष्ठा wil_fw_record_data, data)
 */
काष्ठा wil_fw_record_data अणु /* type == wil_fw_type_data */
	__le32 addr;
	__le32 data[]; /* [data_size], see above */
पूर्ण __packed;

/* fill with स्थिरant @value, @size bytes starting from @addr */
काष्ठा wil_fw_record_fill अणु /* type == wil_fw_type_fill */
	__le32 addr;
	__le32 value;
	__le32 size;
पूर्ण __packed;

/* मुक्त-क्रमm comment
 * क्रम inक्रमmational purpose, data_size is @head.size from record header
 */
काष्ठा wil_fw_record_comment अणु /* type == wil_fw_type_comment */
	u8 data[0]; /* मुक्त-क्रमm data [data_size], see above */
पूर्ण __packed;

/* Comment header - common क्रम all comment record types */
काष्ठा wil_fw_record_comment_hdr अणु
	__le32 magic;
पूर्ण;

/* FW capabilities encoded inside a comment record */
#घोषणा WIL_FW_CAPABILITIES_MAGIC (0xabcddcba)
काष्ठा wil_fw_record_capabilities अणु /* type == wil_fw_type_comment */
	/* identअगरies capabilities record */
	काष्ठा wil_fw_record_comment_hdr hdr;
	/* capabilities (variable size), see क्रमागत wmi_fw_capability */
	u8 capabilities[];
पूर्ण __packed;

/* FW VIF concurrency encoded inside a comment record
 * Format is similar to wiphy->अगरace_combinations
 */
#घोषणा WIL_FW_CONCURRENCY_MAGIC (0xfedccdef)
#घोषणा WIL_FW_CONCURRENCY_REC_VER	1
काष्ठा wil_fw_concurrency_limit अणु
	__le16 max; /* maximum number of पूर्णांकerfaces of these types */
	__le16 types; /* पूर्णांकerface types (bit mask of क्रमागत nl80211_अगरtype) */
पूर्ण __packed;

काष्ठा wil_fw_concurrency_combo अणु
	u8 n_limits; /* number of wil_fw_concurrency_limit entries */
	u8 max_पूर्णांकerfaces; /* max number of concurrent पूर्णांकerfaces allowed */
	u8 n_dअगरf_channels; /* total number of dअगरferent channels allowed */
	u8 same_bi; /* क्रम APs, 1 अगर all APs must have same BI */
	/* keep last - concurrency limits, variable size by n_limits */
	काष्ठा wil_fw_concurrency_limit limits[];
पूर्ण __packed;

काष्ठा wil_fw_record_concurrency अणु /* type == wil_fw_type_comment */
	/* identअगरies concurrency record */
	__le32 magic;
	/* काष्ठाure version, currently always 1 */
	u8 version;
	/* maximum number of supported MIDs _in addition_ to MID 0 */
	u8 n_mids;
	/* number of concurrency combinations that follow */
	__le16 n_combos;
	/* keep last - combinations, variable size by n_combos */
	काष्ठा wil_fw_concurrency_combo combos[];
पूर्ण __packed;

/* brd file info encoded inside a comment record */
#घोषणा WIL_BRD_खाता_MAGIC (0xabcddcbb)

काष्ठा brd_info अणु
	__le32 base_addr;
	__le32 max_size_bytes;
पूर्ण __packed;

काष्ठा wil_fw_record_brd_file अणु /* type == wil_fw_type_comment */
	/* identअगरies brd file record */
	काष्ठा wil_fw_record_comment_hdr hdr;
	__le32 version;
	काष्ठा brd_info brd_info[];
पूर्ण __packed;

/* perक्रमm action
 * data_size = @head.size - दुरत्व(काष्ठा wil_fw_record_action, data)
 */
काष्ठा wil_fw_record_action अणु /* type == wil_fw_type_action */
	__le32 action; /* action to perक्रमm: reset, रुको क्रम fw पढ़ोy etc. */
	__le32 data[]; /* action specअगरic, [data_size], see above */
पूर्ण __packed;

/* data block क्रम काष्ठा wil_fw_record_direct_ग_लिखो */
काष्ठा wil_fw_data_dग_लिखो अणु
	__le32 addr;
	__le32 value;
	__le32 mask;
पूर्ण __packed;

/* ग_लिखो @value to the @addr,
 * preserve original bits accordingly to the @mask
 * data_size is @head.size where @head is record header
 */
काष्ठा wil_fw_record_direct_ग_लिखो अणु /* type == wil_fw_type_direct_ग_लिखो */
	काष्ठा wil_fw_data_dग_लिखो data[0];
पूर्ण __packed;

/* verअगरy condition: [@addr] & @mask == @value
 * अगर condition not met, firmware करोwnload fails
 */
काष्ठा wil_fw_record_verअगरy अणु /* type == wil_fw_verअगरy */
	__le32 addr; /* पढ़ो from this address */
	__le32 value; /* reference value */
	__le32 mask; /* mask क्रम verअगरication */
पूर्ण __packed;

/* file header
 * First record of every file
 */
/* the FW version prefix in the comment */
#घोषणा WIL_FW_VERSION_PREFIX "FW version: "
#घोषणा WIL_FW_VERSION_PREFIX_LEN (माप(WIL_FW_VERSION_PREFIX) - 1)
काष्ठा wil_fw_record_file_header अणु
	__le32 signature ; /* Wilocity signature */
	__le32 reserved;
	__le32 crc; /* crc32 of the following data  */
	__le32 version; /* क्रमmat version */
	__le32 data_len; /* total data in file, including this record */
	u8 comment[32]; /* लघु description */
पूर्ण __packed;

/* 1-dword gateway */
/* data block क्रम the काष्ठा wil_fw_record_gateway_data */
काष्ठा wil_fw_data_gw अणु
	__le32 addr;
	__le32 value;
पूर्ण __packed;

/* gateway ग_लिखो block.
 * ग_लिखो starting address and values from the data buffer
 * through the gateway
 * data_size inferred from the @head.size. For this हाल,
 * data_size = @head.size - दुरत्व(काष्ठा wil_fw_record_gateway_data, data)
 */
काष्ठा wil_fw_record_gateway_data अणु /* type == wil_fw_type_gateway_data */
	__le32 gateway_addr_addr;
	__le32 gateway_value_addr;
	__le32 gateway_cmd_addr;
	__le32 gateway_ctrl_address;
#घोषणा WIL_FW_GW_CTL_BUSY	BIT(29) /* gateway busy perक्रमming operation */
#घोषणा WIL_FW_GW_CTL_RUN	BIT(30) /* start gateway operation */
	__le32 command;
	काष्ठा wil_fw_data_gw data[]; /* total size [data_size], see above */
पूर्ण __packed;

/* 4-dword gateway */
/* data block क्रम the काष्ठा wil_fw_record_gateway_data4 */
काष्ठा wil_fw_data_gw4 अणु
	__le32 addr;
	__le32 value[4];
पूर्ण __packed;

/* gateway ग_लिखो block.
 * ग_लिखो starting address and values from the data buffer
 * through the gateway
 * data_size inferred from the @head.size. For this हाल,
 * data_size = @head.size - दुरत्व(काष्ठा wil_fw_record_gateway_data4, data)
 */
काष्ठा wil_fw_record_gateway_data4 अणु /* type == wil_fw_type_gateway_data4 */
	__le32 gateway_addr_addr;
	__le32 gateway_value_addr[4];
	__le32 gateway_cmd_addr;
	__le32 gateway_ctrl_address; /* same logic as क्रम 1-dword gw */
	__le32 command;
	काष्ठा wil_fw_data_gw4 data[]; /* total size [data_size], see above */
पूर्ण __packed;

#पूर्ण_अगर /* __WIL_FW_H__ */
