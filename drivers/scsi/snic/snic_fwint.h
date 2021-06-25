<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __SNIC_FWINT_H
#घोषणा __SNIC_FWINT_H

#घोषणा SNIC_CDB_LEN	32	/* SCSI CDB size 32, can be used क्रम 16 bytes */
#घोषणा LUN_ADDR_LEN	8

/*
 * Command entry type
 */
क्रमागत snic_io_type अणु
	/*
	 * Initiator request types
	 */
	SNIC_REQ_REPORT_TGTS = 0x2,	/* Report Tarमाला_लो */
	SNIC_REQ_ICMND,			/* Initiator command क्रम SCSI IO */
	SNIC_REQ_ITMF,			/* Initiator command क्रम Task Mgmt */
	SNIC_REQ_HBA_RESET,		/* SNIC Reset */
	SNIC_REQ_EXCH_VER,		/* Exchange Version Inक्रमmation */
	SNIC_REQ_TGT_INFO,		/* Backend/Target Inक्रमmation */
	SNIC_REQ_BOOT_LUNS,

	/*
	 * Response type
	 */
	SNIC_RSP_REPORT_TGTS_CMPL = 0x12,/* Report Tarमाला_लो Completion */
	SNIC_RSP_ICMND_CMPL,		/* SCSI IO Completion */
	SNIC_RSP_ITMF_CMPL,		/* Task Management Completion */
	SNIC_RSP_HBA_RESET_CMPL,	/* SNIC Reset Completion */
	SNIC_RSP_EXCH_VER_CMPL,		/* Exchange Version Completion*/
	SNIC_RSP_BOOT_LUNS_CMPL,

	/*
	 * Misc Request types
	 */
	SNIC_MSG_ACK = 0x80,		/* Ack: snic_notअगरy_msg */
	SNIC_MSG_ASYNC_EVNOTIFY,	/* Asynchronous Event Notअगरication */
पूर्ण; /* end of क्रमागत snic_io_type */


/*
 * Header status codes from firmware
 */
क्रमागत snic_io_status अणु
	SNIC_STAT_IO_SUCCESS = 0,	/* request was successful */

	/*
	 * If a request to the fw is rejected, the original request header
	 * will be वापसed with the status set to one of the following:
	 */
	SNIC_STAT_INVALID_HDR,	/* header contains invalid data */
	SNIC_STAT_OUT_OF_RES,	/* out of resources to complete request */
	SNIC_STAT_INVALID_PARM,	/* some parameter in request is not valid */
	SNIC_STAT_REQ_NOT_SUP,	/* req type is not supported */
	SNIC_STAT_IO_NOT_FOUND,	/* requested IO was not found */

	/*
	 * Once a request is processed, the fw will usually वापस
	 * a cmpl message type. In हालs where errors occurred,
	 * the header status would be filled in with one of the following:
	 */
	SNIC_STAT_ABORTED,		/* req was पातed */
	SNIC_STAT_TIMEOUT,		/* req was समयd out */
	SNIC_STAT_SGL_INVALID,		/* req was पातed due to sgl error */
	SNIC_STAT_DATA_CNT_MISMATCH,	/*recv/sent more/less data than expec */
	SNIC_STAT_FW_ERR,		/* req was terminated due to fw error */
	SNIC_STAT_ITMF_REJECT,		/* iपंचांगf req was rejected by target */
	SNIC_STAT_ITMF_FAIL,		/* iपंचांगf req was failed */
	SNIC_STAT_ITMF_INCORRECT_LUN,	/* iपंचांगf req has incorrect LUN id*/
	SNIC_STAT_CMND_REJECT,		/* req was invalid and rejected */
	SNIC_STAT_DEV_OFFLINE,		/* req sent to offline device */
	SNIC_STAT_NO_BOOTLUN,
	SNIC_STAT_SCSI_ERR,		/* SCSI error वापसed by Target. */
	SNIC_STAT_NOT_READY,		/* sNIC Subप्रणाली is not पढ़ोy */
	SNIC_STAT_FATAL_ERROR,		/* sNIC is in unrecoverable state */
पूर्ण; /* end of क्रमागत snic_io_status */

/*
 * snic_io_hdr : host <--> firmware
 *
 * क्रम any other message that will be queued to firmware should
 *  have the following request header
 */
काष्ठा snic_io_hdr अणु
	__le32	hid;
	__le32	cmnd_id;	/* tag here */
	uदीर्घ	init_ctx;	/* initiator context */
	u8	type;		/* request/response type */
	u8	status;		/* header status entry */
	u8	protocol;	/* Protocol specअगरic, may needed क्रम RoCE*/
	u8	flags;
	__le16	sg_cnt;
	u16	resvd;
पूर्ण;

/* auxillary funciton क्रम encoding the snic_io_hdr */
अटल अंतरभूत व्योम
snic_io_hdr_enc(काष्ठा snic_io_hdr *hdr, u8 typ, u8 status, u32 id, u32 hid,
		u16 sg_cnt, uदीर्घ ctx)
अणु
	hdr->type = typ;
	hdr->status = status;
	hdr->protocol = 0;
	hdr->hid = cpu_to_le32(hid);
	hdr->cmnd_id = cpu_to_le32(id);
	hdr->sg_cnt = cpu_to_le16(sg_cnt);
	hdr->init_ctx = ctx;
	hdr->flags = 0;
पूर्ण

/* auxillary funciton क्रम decoding the snic_io_hdr */
अटल अंतरभूत व्योम
snic_io_hdr_dec(काष्ठा snic_io_hdr *hdr, u8 *typ, u8 *stat, u32 *cmnd_id,
		u32 *hid, uदीर्घ *ctx)
अणु
	*typ = hdr->type;
	*stat = hdr->status;
	*hid = le32_to_cpu(hdr->hid);
	*cmnd_id = le32_to_cpu(hdr->cmnd_id);
	*ctx = hdr->init_ctx;
पूर्ण

/*
 * snic_host_info: host -> firmware
 *
 * Used क्रम sending host inक्रमmation to firmware, and request fw version
 */
काष्ठा snic_exch_ver_req अणु
	__le32	drvr_ver;	/* क्रम debugging, when fw dump captured */
	__le32	os_type;	/* क्रम OS specअगरic features */
पूर्ण;

/*
 * os_type flags
 * Bit 0-7 : OS inक्रमmation
 * Bit 8-31: Feature/Capability Inक्रमmation
 */
#घोषणा SNIC_OS_LINUX	0x1
#घोषणा SNIC_OS_WIN	0x2
#घोषणा SNIC_OS_ESX	0x3

/*
 * HBA Capabilities
 * Bit 1: Reserved.
 * Bit 2: Dynamic Discovery of LUNs.
 * Bit 3: Async event notअगरications on on tgt online/offline events.
 * Bit 4: IO समयout support in FW.
 * Bit 5-31: Reserved.
 */
#घोषणा SNIC_HBA_CAP_DDL	0x02	/* Supports Dynamic Discovery of LUNs */
#घोषणा SNIC_HBA_CAP_AEN	0x04	/* Supports Async Event Noitअगरcation */
#घोषणा SNIC_HBA_CAP_TMO	0x08	/* Supports IO समयout in FW */

/*
 * snic_exch_ver_rsp : firmware -> host
 *
 * Used by firmware to send response to version request
 */
काष्ठा snic_exch_ver_rsp अणु
	__le32	version;
	__le32	hid;
	__le32	max_concur_ios;		/* max concurrent ios */
	__le32	max_sgs_per_cmd;	/* max sgls per IO */
	__le32	max_io_sz;		/* max io size supported */
	__le32	hba_cap;		/* hba capabilities */
	__le32	max_tgts;		/* max tgts supported */
	__le16	io_समयout;		/* FW extended समयout */
	u16	rsvd;
पूर्ण;


/*
 * snic_report_tgts : host -> firmware request
 *
 * Used by the host to request list of tarमाला_लो
 */
काष्ठा snic_report_tgts अणु
	__le16	sg_cnt;
	__le16	flags;		/* specअगरic flags from fw */
	u8	_resvd[4];
	__le64	sg_addr;	/* Poपूर्णांकs to SGL */
	__le64	sense_addr;
पूर्ण;

क्रमागत snic_type अणु
	SNIC_NONE = 0x0,
	SNIC_DAS,
	SNIC_SAN,
पूर्ण;


/* Report Target Response */
क्रमागत snic_tgt_type अणु
	SNIC_TGT_NONE = 0x0,
	SNIC_TGT_DAS,	/* DAS Target */
	SNIC_TGT_SAN,	/* SAN Target */
पूर्ण;

/* target id क्रमmat */
काष्ठा snic_tgt_id अणु
	__le32	tgt_id;		/* target id */
	__le16	tgt_type;	/* tgt type */
	__le16	vnic_id;	/* corresponding vnic id */
पूर्ण;

/*
 * snic_report_tgts_cmpl : firmware -> host response
 *
 * Used by firmware to send response to Report Tarमाला_लो request
 */
काष्ठा snic_report_tgts_cmpl अणु
	__le32	tgt_cnt;	/* Number of Tarमाला_लो accessible */
	u32	_resvd;
पूर्ण;

/*
 * Command flags
 *
 * Bit 0: Read flags
 * Bit 1: Write flag
 * Bit 2: ESGL - sg/esg array contains extended sg
 *	  ESGE - is a host buffer contains sg elements
 * Bit 3-4: Task Attributes
 *		00b - simple
 *		01b - head of queue
 *		10b - ordered
 * Bit 5-7: Priority - future use
 * Bit 8-15: Reserved
 */

#घोषणा SNIC_ICMND_WR		0x01	/* ग_लिखो command */
#घोषणा SNIC_ICMND_RD		0x02	/* पढ़ो command */
#घोषणा SNIC_ICMND_ESGL		0x04	/* SGE/ESGE array contains valid data*/

/*
 * Priority/Task Attribute settings
 */
#घोषणा SNIC_ICMND_TSK_SHIFT		2	/* task attr starts at bit 2 */
#घोषणा SNIC_ICMND_TSK_MASK(x)		((x>>SNIC_ICMND_TSK_SHIFT) & ~(0xffff))
#घोषणा SNIC_ICMND_TSK_SIMPLE		0	/* simple task attr */
#घोषणा SNIC_ICMND_TSK_HEAD_OF_QUEUE	1	/* head of qeuue task attr */
#घोषणा SNIC_ICMND_TSK_ORDERED		2	/* ordered task attr */

#घोषणा SNIC_ICMND_PRI_SHIFT		5	/* prio val starts at bit 5 */

/*
 * snic_icmnd : host-> firmware request
 *
 * used क्रम sending out an initiator SCSI 16/32-byte command
 */
काष्ठा snic_icmnd अणु
	__le16	sg_cnt;		/* Number of SG Elements */
	__le16	flags;		/* flags */
	__le32	sense_len;	/* Sense buffer length */
	__le64	tgt_id;		/* Destination Target ID */
	__le64	lun_id;		/* Destination LUN ID */
	u8	cdb_len;
	u8	_resvd;
	__le16	समय_out;	/* ms समय क्रम Res allocations fw to handle io*/
	__le32	data_len;	/* Total number of bytes to be transferred */
	u8	cdb[SNIC_CDB_LEN];
	__le64	sg_addr;	/* Poपूर्णांकs to SG List */
	__le64	sense_addr;	/* Sense buffer address */
पूर्ण;


/* Response flags */
/* Bit 0: Under run
 * Bit 1: Over Run
 * Bit 2-7: Reserved
 */
#घोषणा SNIC_ICMND_CMPL_UNDR_RUN	0x01	/* resid under and valid */
#घोषणा SNIC_ICMND_CMPL_OVER_RUN	0x02	/* resid over and valid */

/*
 * snic_icmnd_cmpl: firmware -> host response
 *
 * Used क्रम sending the host a response to an icmnd (initiator command)
 */
काष्ठा snic_icmnd_cmpl अणु
	u8	scsi_status;	/* value as per SAM */
	u8	flags;
	__le16	sense_len;	/* Sense Length */
	__le32	resid;		/* Residue : # bytes under or over run */
पूर्ण;

/*
 * snic_iपंचांगf: host->firmware request
 *
 * used क्रम requesting the firmware to पात a request and/or send out
 * a task management function
 *
 * the req_id field is valid in हाल of पात task and clear task
 */
काष्ठा snic_iपंचांगf अणु
	u8	पंचांग_type;	/* SCSI Task Management request */
	u8	resvd;
	__le16	flags;		/* flags */
	__le32	req_id;		/* Command id of snic req to be पातed */
	__le64	tgt_id;		/* Target ID */
	__le64	lun_id;		/* Destination LUN ID */
	__le16	समयout;	/* in sec */
पूर्ण;

/*
 * Task Management Request
 */
क्रमागत snic_iपंचांगf_पंचांग_type अणु
	SNIC_ITMF_ABTS_TASK = 0x01,	/* Abort Task */
	SNIC_ITMF_ABTS_TASK_SET,	/* Abort Task Set */
	SNIC_ITMF_CLR_TASK,		/* Clear Task */
	SNIC_ITMF_CLR_TASKSET,		/* Clear Task Set */
	SNIC_ITMF_LUN_RESET,		/* Lun Reset */
	SNIC_ITMF_ABTS_TASK_TERM,	/* Supported क्रम SAN Tarमाला_लो */
पूर्ण;

/*
 * snic_iपंचांगf_cmpl: firmware -> host resposne
 *
 * used क्रम sending the host a response क्रम a iपंचांगf request
 */
काष्ठा snic_iपंचांगf_cmpl अणु
	__le32	nterminated;	/* # IOs terminated as a result of पंचांगf */
	u8	flags;		/* flags */
	u8	_resvd[3];
पूर्ण;

/*
 * iपंचांगfl_cmpl flags
 * Bit 0 : 1 - Num terminated field valid
 * Bit 1 - 7 : Reserved
 */
#घोषणा SNIC_NUM_TERM_VALID	0x01	/* Number of IOs terminated */

/*
 * snic_hba_reset: host -> firmware request
 *
 * used क्रम requesting firmware to reset snic
 */
काष्ठा snic_hba_reset अणु
	__le16	flags;		/* flags */
	u8	_resvd[6];
पूर्ण;

/*
 * snic_hba_reset_cmpl: firmware -> host response
 *
 * Used by firmware to respond to the host's hba reset request
 */
काष्ठा snic_hba_reset_cmpl अणु
	u8	flags;		/* flags : more info needs to be added*/
	u8	_resvd[7];
पूर्ण;

/*
 * snic_notअगरy_msg: firmware -> host response
 *
 * Used by firmware to notअगरy host of the last work queue entry received
 */
काष्ठा snic_notअगरy_msg अणु
	__le32	wqe_num;	/* wq entry number */
	u8	flags;		/* flags, macros */
	u8	_resvd[4];
पूर्ण;


#घोषणा SNIC_EVDATA_LEN		24	/* in bytes */
/* snic_async_evnotअगरy: firmware -> host notअगरication
 *
 * Used by firmware to notअगरy the host about configuration/state changes
 */
काष्ठा snic_async_evnotअगरy अणु
	u8	FLS_EVENT_DESC;
	u8	vnic;			/* vnic id */
	u8	_resvd[2];
	__le32	ev_id;			/* Event ID */
	u8	ev_data[SNIC_EVDATA_LEN]; /* Event Data */
	u8	_resvd2[4];
पूर्ण;

/* async event flags */
क्रमागत snic_ev_type अणु
	SNIC_EV_TGT_OFFLINE = 0x01, /* Target Offline, PL contains TGT ID */
	SNIC_EV_TGT_ONLINE,	/* Target Online, PL contains TGT ID */
	SNIC_EV_LUN_OFFLINE,	/* LUN Offline, PL contains LUN ID */
	SNIC_EV_LUN_ONLINE,	/* LUN Online, PL contains LUN ID */
	SNIC_EV_CONF_CHG,	/* Dev Config/Attr Change Event */
	SNIC_EV_TGT_ADDED,	/* Target Added */
	SNIC_EV_TGT_DELTD,	/* Target Del'd, PL contains TGT ID */
	SNIC_EV_LUN_ADDED,	/* LUN Added */
	SNIC_EV_LUN_DELTD,	/* LUN Del'd, PL cont. TGT & LUN ID */

	SNIC_EV_DISC_CMPL = 0x10, /* Discovery Completed Event */
पूर्ण;


#घोषणा SNIC_HOST_REQ_LEN	128	/*Exp length of host req, wq desc sz*/
/* Payload 88 bytes = 128 - 24 - 16 */
#घोषणा SNIC_HOST_REQ_PAYLOAD	((पूर्णांक)(SNIC_HOST_REQ_LEN -		\
					माप(काष्ठा snic_io_hdr) -	\
					(2 * माप(u64)) - माप(uदीर्घ)))

/*
 * snic_host_req: host -> firmware request
 *
 * Basic काष्ठाure क्रम all snic requests that are sent from the host to
 * firmware. They are 128 bytes in size.
 */
काष्ठा snic_host_req अणु
	u64	ctrl_data[2];	/*16 bytes - Control Data */
	काष्ठा snic_io_hdr hdr;
	जोड़ अणु
		/*
		 * Entry specअगरic space, last byte contains color
		 */
		u8	buf[SNIC_HOST_REQ_PAYLOAD];

		/*
		 * Exchange firmware version
		 */
		काष्ठा snic_exch_ver_req	exch_ver;

		/* report tarमाला_लो */
		काष्ठा snic_report_tgts		rpt_tgts;

		/* io request */
		काष्ठा snic_icmnd		icmnd;

		/* task management request */
		काष्ठा snic_iपंचांगf		iपंचांगf;

		/* hba reset */
		काष्ठा snic_hba_reset		reset;
	पूर्ण u;

	uदीर्घ req_pa;
पूर्ण; /* end of snic_host_req काष्ठाure */


#घोषणा SNIC_FW_REQ_LEN		64 /* Expected length of fw req */
काष्ठा snic_fw_req अणु
	काष्ठा snic_io_hdr hdr;
	जोड़ अणु
		/*
		 * Entry specअगरic space, last byte contains color
		 */
		u8	buf[SNIC_FW_REQ_LEN - माप(काष्ठा snic_io_hdr)];

		/* Exchange Version Response */
		काष्ठा snic_exch_ver_rsp	exch_ver_cmpl;

		/* Report Tarमाला_लो Response */
		काष्ठा snic_report_tgts_cmpl	rpt_tgts_cmpl;

		/* scsi response */
		काष्ठा snic_icmnd_cmpl		icmnd_cmpl;

		/* task management response */
		काष्ठा snic_iपंचांगf_cmpl		iपंचांगf_cmpl;

		/* hba reset response */
		काष्ठा snic_hba_reset_cmpl	reset_cmpl;

		/* notअगरy message */
		काष्ठा snic_notअगरy_msg		ack;

		/* async notअगरication event */
		काष्ठा snic_async_evnotअगरy	async_ev;

	पूर्ण u;
पूर्ण; /* end of snic_fw_req काष्ठाure */

/*
 * Auxillary macro to verअगरy specअगरic snic req/cmpl काष्ठाures
 * to ensure that it will be aligned to 64 bit, and not using
 * color bit field
 */
#घोषणा VERIFY_REQ_SZ(x)
#घोषणा VERIFY_CMPL_SZ(x)

/*
 * Access routines to encode and decode the color bit, which is the most
 * signअगरicant bit of the काष्ठाure.
 */
अटल अंतरभूत व्योम
snic_color_enc(काष्ठा snic_fw_req *req, u8 color)
अणु
	u8 *c = ((u8 *) req) + माप(काष्ठा snic_fw_req) - 1;

	अगर (color)
		*c |= 0x80;
	अन्यथा
		*c &= ~0x80;
पूर्ण

अटल अंतरभूत व्योम
snic_color_dec(काष्ठा snic_fw_req *req, u8 *color)
अणु
	u8 *c = ((u8 *) req) + माप(काष्ठा snic_fw_req) - 1;

	*color = *c >> 7;

	/* Make sure color bit is पढ़ो from desc *beक्रमe* other fields
	 * are पढ़ो from desc. Hardware guarantees color bit is last
	 * bit (byte) written. Adding the rmb() prevents the compiler
	 * and/or CPU from reordering the पढ़ोs which would potentially
	 * result in पढ़ोing stale values.
	 */
	rmb();
पूर्ण
#पूर्ण_अगर /* end of __SNIC_FWINT_H */
