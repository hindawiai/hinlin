<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * UFS Transport SGIO v4 BSG Message Support
 *
 * Copyright (C) 2011-2013 Samsung India Software Operations
 * Copyright (C) 2018 Western Digital Corporation
 */
#अगर_अघोषित SCSI_BSG_UFS_H
#घोषणा SCSI_BSG_UFS_H

#समावेश <linux/types.h>
/*
 * This file पूर्णांकended to be included by both kernel and user space
 */

#घोषणा UFS_CDB_SIZE	16
#घोषणा UPIU_TRANSACTION_UIC_CMD 0x1F
/* uic commands are 4DW दीर्घ, per UFSHCI V2.1 paragraph 5.6.1 */
#घोषणा UIC_CMD_SIZE (माप(__u32) * 4)

/**
 * काष्ठा utp_upiu_header - UPIU header काष्ठाure
 * @dword_0: UPIU header DW-0
 * @dword_1: UPIU header DW-1
 * @dword_2: UPIU header DW-2
 */
काष्ठा utp_upiu_header अणु
	__be32 dword_0;
	__be32 dword_1;
	__be32 dword_2;
पूर्ण;

/**
 * काष्ठा utp_upiu_query - upiu request buffer काष्ठाure क्रम
 * query request.
 * @opcode: command to perक्रमm B-0
 * @idn: a value that indicates the particular type of data B-1
 * @index: Index to further identअगरy data B-2
 * @selector: Index to further identअगरy data B-3
 * @reserved_osf: spec reserved field B-4,5
 * @length: number of descriptor bytes to पढ़ो/ग_लिखो B-6,7
 * @value: Attribute value to be written DW-5
 * @reserved: spec reserved DW-6,7
 */
काष्ठा utp_upiu_query अणु
	__u8 opcode;
	__u8 idn;
	__u8 index;
	__u8 selector;
	__be16 reserved_osf;
	__be16 length;
	__be32 value;
	__be32 reserved[2];
पूर्ण;

/**
 * काष्ठा utp_upiu_cmd - Command UPIU काष्ठाure
 * @data_transfer_len: Data Transfer Length DW-3
 * @cdb: Command Descriptor Block CDB DW-4 to DW-7
 */
काष्ठा utp_upiu_cmd अणु
	__be32 exp_data_transfer_len;
	__u8 cdb[UFS_CDB_SIZE];
पूर्ण;

/**
 * काष्ठा utp_upiu_req - general upiu request काष्ठाure
 * @header:UPIU header काष्ठाure DW-0 to DW-2
 * @sc: fields काष्ठाure क्रम scsi command DW-3 to DW-7
 * @qr: fields काष्ठाure क्रम query request DW-3 to DW-7
 * @uc: use utp_upiu_query to host the 4 dwords of uic command
 */
काष्ठा utp_upiu_req अणु
	काष्ठा utp_upiu_header header;
	जोड़ अणु
		काष्ठा utp_upiu_cmd		sc;
		काष्ठा utp_upiu_query		qr;
		काष्ठा utp_upiu_query		uc;
	पूर्ण;
पूर्ण;

/* request (CDB) काष्ठाure of the sg_io_v4 */
काष्ठा ufs_bsg_request अणु
	__u32 msgcode;
	काष्ठा utp_upiu_req upiu_req;
पूर्ण;

/* response (request sense data) काष्ठाure of the sg_io_v4 */
काष्ठा ufs_bsg_reply अणु
	/*
	 * The completion result. Result exists in two क्रमms:
	 * अगर negative, it is an -Exxx प्रणाली त्रुटि_सं value. There will
	 * be no further reply inक्रमmation supplied.
	 * अन्यथा, it's the 4-byte scsi error result, with driver, host,
	 * msg and status fields. The per-msgcode reply काष्ठाure
	 * will contain valid data.
	 */
	__u32 result;

	/* If there was reply_payload, how much was received? */
	__u32 reply_payload_rcv_len;

	काष्ठा utp_upiu_req upiu_rsp;
पूर्ण;
#पूर्ण_अगर /* UFS_BSG_H */
