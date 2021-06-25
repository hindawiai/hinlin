<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPIBSG_H
#घोषणा _UAPIBSG_H

#समावेश <linux/types.h>

#घोषणा BSG_PROTOCOL_SCSI		0

#घोषणा BSG_SUB_PROTOCOL_SCSI_CMD	0
#घोषणा BSG_SUB_PROTOCOL_SCSI_TMF	1
#घोषणा BSG_SUB_PROTOCOL_SCSI_TRANSPORT	2

/*
 * For flag स्थिरants below:
 * sg.h sg_io_hdr also has bits defined क्रम it's flags member. These
 * two flag values (0x10 and 0x20) have the same meaning in sg.h . For
 * bsg the BSG_FLAG_Q_AT_HEAD flag is ignored since it is the deafult.
 */
#घोषणा BSG_FLAG_Q_AT_TAIL 0x10 /* शेष is Q_AT_HEAD */
#घोषणा BSG_FLAG_Q_AT_HEAD 0x20

काष्ठा sg_io_v4 अणु
	__s32 guard;		/* [i] 'Q' to dअगरferentiate from v3 */
	__u32 protocol;		/* [i] 0 -> SCSI , .... */
	__u32 subprotocol;	/* [i] 0 -> SCSI command, 1 -> SCSI task
				   management function, .... */

	__u32 request_len;	/* [i] in bytes */
	__u64 request;		/* [i], [*i] अणुSCSI: cdbपूर्ण */
	__u64 request_tag;	/* [i] अणुSCSI: task tag (only अगर flagged)पूर्ण */
	__u32 request_attr;	/* [i] अणुSCSI: task attributeपूर्ण */
	__u32 request_priority;	/* [i] अणुSCSI: task priorityपूर्ण */
	__u32 request_extra;	/* [i] अणुspare, क्रम paddingपूर्ण */
	__u32 max_response_len;	/* [i] in bytes */
	__u64 response;		/* [i], [*o] अणुSCSI: (स्वतः)sense dataपूर्ण */

        /* "dout_": data out (to device); "din_": data in (from device) */
	__u32 करोut_iovec_count;	/* [i] 0 -> "flat" करोut transfer अन्यथा
				   करोut_xfer poपूर्णांकs to array of iovec */
	__u32 करोut_xfer_len;	/* [i] bytes to be transferred to device */
	__u32 din_iovec_count;	/* [i] 0 -> "flat" din transfer */
	__u32 din_xfer_len;	/* [i] bytes to be transferred from device */
	__u64 करोut_xferp;	/* [i], [*i] */
	__u64 din_xferp;	/* [i], [*o] */

	__u32 समयout;		/* [i] units: millisecond */
	__u32 flags;		/* [i] bit mask */
	__u64 usr_ptr;		/* [i->o] unused पूर्णांकernally */
	__u32 spare_in;		/* [i] */

	__u32 driver_status;	/* [o] 0 -> ok */
	__u32 transport_status;	/* [o] 0 -> ok */
	__u32 device_status;	/* [o] अणुSCSI: command completion statusपूर्ण */
	__u32 retry_delay;	/* [o] अणुSCSI: status auxiliary inक्रमmationपूर्ण */
	__u32 info;		/* [o] additional inक्रमmation */
	__u32 duration;		/* [o] समय to complete, in milliseconds */
	__u32 response_len;	/* [o] bytes of response actually written */
	__s32 din_resid;	/* [o] din_xfer_len - actual_din_xfer_len */
	__s32 करोut_resid;	/* [o] करोut_xfer_len - actual_करोut_xfer_len */
	__u64 generated_tag;	/* [o] अणुSCSI: transport generated task tagपूर्ण */
	__u32 spare_out;	/* [o] */

	__u32 padding;
पूर्ण;


#पूर्ण_अगर /* _UAPIBSG_H */
