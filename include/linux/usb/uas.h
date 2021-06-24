<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __USB_UAS_H__
#घोषणा __USB_UAS_H__

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>

/* Common header क्रम all IUs */
काष्ठा iu अणु
	__u8 iu_id;
	__u8 rsvd1;
	__be16 tag;
पूर्ण __attribute__((__packed__));

क्रमागत अणु
	IU_ID_COMMAND		= 0x01,
	IU_ID_STATUS		= 0x03,
	IU_ID_RESPONSE		= 0x04,
	IU_ID_TASK_MGMT		= 0x05,
	IU_ID_READ_READY	= 0x06,
	IU_ID_WRITE_READY	= 0x07,
पूर्ण;

क्रमागत अणु
	TMF_ABORT_TASK          = 0x01,
	TMF_ABORT_TASK_SET      = 0x02,
	TMF_CLEAR_TASK_SET      = 0x04,
	TMF_LOGICAL_UNIT_RESET  = 0x08,
	TMF_I_T_NEXUS_RESET     = 0x10,
	TMF_CLEAR_ACA           = 0x40,
	TMF_QUERY_TASK          = 0x80,
	TMF_QUERY_TASK_SET      = 0x81,
	TMF_QUERY_ASYNC_EVENT   = 0x82,
पूर्ण;

क्रमागत अणु
	RC_TMF_COMPLETE         = 0x00,
	RC_INVALID_INFO_UNIT    = 0x02,
	RC_TMF_NOT_SUPPORTED    = 0x04,
	RC_TMF_FAILED           = 0x05,
	RC_TMF_SUCCEEDED        = 0x08,
	RC_INCORRECT_LUN        = 0x09,
	RC_OVERLAPPED_TAG       = 0x0a,
पूर्ण;

काष्ठा command_iu अणु
	__u8 iu_id;
	__u8 rsvd1;
	__be16 tag;
	__u8 prio_attr;
	__u8 rsvd5;
	__u8 len;
	__u8 rsvd7;
	काष्ठा scsi_lun lun;
	__u8 cdb[16];	/* XXX: Overflow-checking tools may misunderstand */
पूर्ण __attribute__((__packed__));

काष्ठा task_mgmt_iu अणु
	__u8 iu_id;
	__u8 rsvd1;
	__be16 tag;
	__u8 function;
	__u8 rsvd2;
	__be16 task_tag;
	काष्ठा scsi_lun lun;
पूर्ण __attribute__((__packed__));

/*
 * Also used क्रम the Read Ready and Write Ready IUs since they have the
 * same first four bytes
 */
काष्ठा sense_iu अणु
	__u8 iu_id;
	__u8 rsvd1;
	__be16 tag;
	__be16 status_qual;
	__u8 status;
	__u8 rsvd7[7];
	__be16 len;
	__u8 sense[SCSI_SENSE_BUFFERSIZE];
पूर्ण __attribute__((__packed__));

काष्ठा response_iu अणु
	__u8 iu_id;
	__u8 rsvd1;
	__be16 tag;
	__u8 add_response_info[3];
	__u8 response_code;
पूर्ण __attribute__((__packed__));

काष्ठा usb_pipe_usage_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;

	__u8  bPipeID;
	__u8  Reserved;
पूर्ण __attribute__((__packed__));

क्रमागत अणु
	CMD_PIPE_ID		= 1,
	STATUS_PIPE_ID		= 2,
	DATA_IN_PIPE_ID		= 3,
	DATA_OUT_PIPE_ID	= 4,

	UAS_SIMPLE_TAG		= 0,
	UAS_HEAD_TAG		= 1,
	UAS_ORDERED_TAG		= 2,
	UAS_ACA			= 4,
पूर्ण;
#पूर्ण_अगर
