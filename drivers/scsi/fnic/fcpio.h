<शैली गुरु>
/*
 * Copyright 2008 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
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
#अगर_अघोषित _FCPIO_H_
#घोषणा _FCPIO_H_

#समावेश <linux/अगर_ether.h>

/*
 * This header file includes all of the data काष्ठाures used क्रम
 * communication by the host driver to the fcp firmware.
 */

/*
 * Exchange and sequence id space allocated to the host driver
 */
#घोषणा FCPIO_HOST_EXCH_RANGE_START         0x1000
#घोषणा FCPIO_HOST_EXCH_RANGE_END           0x1fff
#घोषणा FCPIO_HOST_SEQ_ID_RANGE_START       0x80
#घोषणा FCPIO_HOST_SEQ_ID_RANGE_END         0xff

/*
 * Command entry type
 */
क्रमागत fcpio_type अणु
	/*
	 * Initiator request types
	 */
	FCPIO_ICMND_16 = 0x1,
	FCPIO_ICMND_32,
	FCPIO_ICMND_CMPL,
	FCPIO_ITMF,
	FCPIO_ITMF_CMPL,

	/*
	 * Target request types
	 */
	FCPIO_TCMND_16 = 0x11,
	FCPIO_TCMND_32,
	FCPIO_TDATA,
	FCPIO_TXRDY,
	FCPIO_TRSP,
	FCPIO_TDRSP_CMPL,
	FCPIO_TTMF,
	FCPIO_TTMF_ACK,
	FCPIO_TABORT,
	FCPIO_TABORT_CMPL,

	/*
	 * Misc request types
	 */
	FCPIO_ACK = 0x20,
	FCPIO_RESET,
	FCPIO_RESET_CMPL,
	FCPIO_FLOGI_REG,
	FCPIO_FLOGI_REG_CMPL,
	FCPIO_ECHO,
	FCPIO_ECHO_CMPL,
	FCPIO_LUNMAP_CHNG,
	FCPIO_LUNMAP_REQ,
	FCPIO_LUNMAP_REQ_CMPL,
	FCPIO_FLOGI_FIP_REG,
	FCPIO_FLOGI_FIP_REG_CMPL,
पूर्ण;

/*
 * Header status codes from the firmware
 */
क्रमागत fcpio_status अणु
	FCPIO_SUCCESS = 0,              /* request was successful */

	/*
	 * If a request to the firmware is rejected, the original request
	 * header will be वापसed with the status set to one of the following:
	 */
	FCPIO_INVALID_HEADER,    /* header contains invalid data */
	FCPIO_OUT_OF_RESOURCE,   /* out of resources to complete request */
	FCPIO_INVALID_PARAM,     /* some parameter in request is invalid */
	FCPIO_REQ_NOT_SUPPORTED, /* request type is not supported */
	FCPIO_IO_NOT_FOUND,      /* requested I/O was not found */

	/*
	 * Once a request is processed, the firmware will usually वापस
	 * a cmpl message type.  In हालs where errors occurred,
	 * the header status field would be filled in with one of the following:
	 */
	FCPIO_ABORTED = 0x41,     /* request was पातed */
	FCPIO_TIMEOUT,            /* request was समयd out */
	FCPIO_SGL_INVALID,        /* request was पातed due to sgl error */
	FCPIO_MSS_INVALID,        /* request was पातed due to mss error */
	FCPIO_DATA_CNT_MISMATCH,  /* recv/sent more/less data than exp. */
	FCPIO_FW_ERR,             /* request was terminated due to fw error */
	FCPIO_ITMF_REJECTED,      /* iपंचांगf req was rejected by remote node */
	FCPIO_ITMF_FAILED,        /* iपंचांगf req was failed by remote node */
	FCPIO_ITMF_INCORRECT_LUN, /* iपंचांगf req targeted incorrect LUN */
	FCPIO_CMND_REJECTED,      /* request was invalid and rejected */
	FCPIO_NO_PATH_AVAIL,      /* no paths to the lun was available */
	FCPIO_PATH_FAILED,        /* i/o sent to current path failed */
	FCPIO_LUNMAP_CHNG_PEND,   /* i/o rejected due to lunmap change */
पूर्ण;

/*
 * The header command tag.  All host requests will use the "tag" field
 * to mark commands with a unique tag.  When the firmware responds to
 * a host request, it will copy the tag field पूर्णांकo the response.
 *
 * The only firmware requests that will use the rx_id/ox_id fields instead
 * of the tag field will be the target command and target task management
 * requests.  These two requests करो not have corresponding host requests
 * since they come directly from the FC initiator on the network.
 */
काष्ठा fcpio_tag अणु
	जोड़ अणु
		u32 req_id;
		काष्ठा अणु
			u16 rx_id;
			u16 ox_id;
		पूर्ण ex_id;
	पूर्ण u;
पूर्ण;

अटल अंतरभूत व्योम
fcpio_tag_id_enc(काष्ठा fcpio_tag *tag, u32 id)
अणु
	tag->u.req_id = id;
पूर्ण

अटल अंतरभूत व्योम
fcpio_tag_id_dec(काष्ठा fcpio_tag *tag, u32 *id)
अणु
	*id = tag->u.req_id;
पूर्ण

अटल अंतरभूत व्योम
fcpio_tag_exid_enc(काष्ठा fcpio_tag *tag, u16 ox_id, u16 rx_id)
अणु
	tag->u.ex_id.rx_id = rx_id;
	tag->u.ex_id.ox_id = ox_id;
पूर्ण

अटल अंतरभूत व्योम
fcpio_tag_exid_dec(काष्ठा fcpio_tag *tag, u16 *ox_id, u16 *rx_id)
अणु
	*rx_id = tag->u.ex_id.rx_id;
	*ox_id = tag->u.ex_id.ox_id;
पूर्ण

/*
 * The header क्रम an fcpio request, whether from the firmware or from the
 * host driver
 */
काष्ठा fcpio_header अणु
	u8            type;           /* क्रमागत fcpio_type */
	u8            status;         /* header status entry */
	u16           _resvd;         /* reserved */
	काष्ठा fcpio_tag    tag;      /* header tag */
पूर्ण;

अटल अंतरभूत व्योम
fcpio_header_enc(काष्ठा fcpio_header *hdr,
		 u8 type, u8 status,
		 काष्ठा fcpio_tag tag)
अणु
	hdr->type = type;
	hdr->status = status;
	hdr->_resvd = 0;
	hdr->tag = tag;
पूर्ण

अटल अंतरभूत व्योम
fcpio_header_dec(काष्ठा fcpio_header *hdr,
		 u8 *type, u8 *status,
		 काष्ठा fcpio_tag *tag)
अणु
	*type = hdr->type;
	*status = hdr->status;
	*tag = hdr->tag;
पूर्ण

#घोषणा CDB_16      16
#घोषणा CDB_32      32
#घोषणा LUN_ADDRESS 8

/*
 * fcpio_icmnd_16: host -> firmware request
 *
 * used क्रम sending out an initiator SCSI 16-byte command
 */
काष्ठा fcpio_icmnd_16 अणु
	u32	  lunmap_id;		/* index पूर्णांकo lunmap table */
	u8	  special_req_flags;	/* special exchange request flags */
	u8	  _resvd0[3];	        /* reserved */
	u32	  sgl_cnt;		/* scatter-gather list count */
	u32	  sense_len;		/* sense buffer length */
	u64	  sgl_addr;		/* scatter-gather list addr */
	u64	  sense_addr;		/* sense buffer address */
	u8	  crn;			/* SCSI Command Reference No. */
	u8	  pri_ta;		/* SCSI Priority and Task attribute */
	u8	  _resvd1;		/* reserved: should be 0 */
	u8	  flags;		/* command flags */
	u8	  scsi_cdb[CDB_16];	/* SCSI Cmnd Descriptor Block */
	u32	  data_len;		/* length of data expected */
	u8	  lun[LUN_ADDRESS];	/* FC vNIC only: LUN address */
	u8	  _resvd2;		/* reserved */
	u8	  d_id[3];		/* FC vNIC only: Target D_ID */
	u16	  mss;			/* FC vNIC only: max burst */
	u16	  _resvd3;		/* reserved */
	u32	  r_a_tov;		/* FC vNIC only: Res. Alloc Timeout */
	u32	  e_d_tov;	        /* FC vNIC only: Err Detect Timeout */
पूर्ण;

/*
 * Special request flags
 */
#घोषणा FCPIO_ICMND_SRFLAG_RETRY 0x01   /* Enable Retry handling on exchange */

/*
 * Priority/Task Attribute settings
 */
#घोषणा FCPIO_ICMND_PTA_SIMPLE      0   /* simple task attribute */
#घोषणा FCPIO_ICMND_PTA_HEADQ       1   /* head of queue task attribute */
#घोषणा FCPIO_ICMND_PTA_ORDERED     2   /* ordered task attribute */
#घोषणा FCPIO_ICMND_PTA_ACA         4   /* स्वतः contingent allegiance */
#घोषणा FCPIO_ICMND_PRI_SHIFT       3   /* priority field starts in bit 3 */

/*
 * Command flags
 */
#घोषणा FCPIO_ICMND_RDDATA      0x02    /* पढ़ो data */
#घोषणा FCPIO_ICMND_WRDATA      0x01    /* ग_लिखो data */

/*
 * fcpio_icmnd_32: host -> firmware request
 *
 * used क्रम sending out an initiator SCSI 32-byte command
 */
काष्ठा fcpio_icmnd_32 अणु
	u32   lunmap_id;              /* index पूर्णांकo lunmap table */
	u8    special_req_flags;      /* special exchange request flags */
	u8    _resvd0[3];             /* reserved */
	u32   sgl_cnt;                /* scatter-gather list count */
	u32   sense_len;              /* sense buffer length */
	u64   sgl_addr;               /* scatter-gather list addr */
	u64   sense_addr;             /* sense buffer address */
	u8    crn;                    /* SCSI Command Reference No. */
	u8    pri_ta;                 /* SCSI Priority and Task attribute */
	u8    _resvd1;                /* reserved: should be 0 */
	u8    flags;                  /* command flags */
	u8    scsi_cdb[CDB_32];       /* SCSI Cmnd Descriptor Block */
	u32   data_len;               /* length of data expected */
	u8    lun[LUN_ADDRESS];       /* FC vNIC only: LUN address */
	u8    _resvd2;                /* reserved */
	u8    d_id[3];		      /* FC vNIC only: Target D_ID */
	u16   mss;                    /* FC vNIC only: max burst */
	u16   _resvd3;                /* reserved */
	u32   r_a_tov;                /* FC vNIC only: Res. Alloc Timeout */
	u32   e_d_tov;                /* FC vNIC only: Error Detect Timeout */
पूर्ण;

/*
 * fcpio_iपंचांगf: host -> firmware request
 *
 * used क्रम requesting the firmware to पात a request and/or send out
 * a task management function
 *
 * The t_tag field is only needed when the request type is ABT_TASK.
 */
काष्ठा fcpio_iपंचांगf अणु
	u32   lunmap_id;              /* index पूर्णांकo lunmap table */
	u32   पंचांग_req;                 /* SCSI Task Management request */
	u32   t_tag;                  /* header tag of fcpio to be पातed */
	u32   _resvd;                 /* _reserved */
	u8    lun[LUN_ADDRESS];       /* FC vNIC only: LUN address */
	u8    _resvd1;                /* reserved */
	u8    d_id[3];		      /* FC vNIC only: Target D_ID */
	u32   r_a_tov;                /* FC vNIC only: R_A_TOV in msec */
	u32   e_d_tov;                /* FC vNIC only: E_D_TOV in msec */
पूर्ण;

/*
 * Task Management request
 */
क्रमागत fcpio_iपंचांगf_पंचांग_req_type अणु
	FCPIO_ITMF_ABT_TASK_TERM = 0x01,    /* पात task and terminate */
	FCPIO_ITMF_ABT_TASK,                /* पात task and issue abts */
	FCPIO_ITMF_ABT_TASK_SET,            /* पात task set */
	FCPIO_ITMF_CLR_TASK_SET,            /* clear task set */
	FCPIO_ITMF_LUN_RESET,               /* logical unit reset task mgmt */
	FCPIO_ITMF_CLR_ACA,                 /* Clear ACA condition */
पूर्ण;

/*
 * fcpio_tdata: host -> firmware request
 *
 * used क्रम requesting the firmware to send out a पढ़ो data transfer क्रम a
 * target command
 */
काष्ठा fcpio_tdata अणु
	u16   rx_id;                  /* FC rx_id of target command */
	u16   flags;                  /* command flags */
	u32   rel_offset;             /* data sequence relative offset */
	u32   sgl_cnt;                /* scatter-gather list count */
	u32   data_len;               /* length of data expected to send */
	u64   sgl_addr;               /* scatter-gather list address */
पूर्ण;

/*
 * Command flags
 */
#घोषणा FCPIO_TDATA_SCSI_RSP    0x01    /* send a scsi resp. after last frame */

/*
 * fcpio_txrdy: host -> firmware request
 *
 * used क्रम requesting the firmware to send out a ग_लिखो data transfer क्रम a
 * target command
 */
काष्ठा fcpio_txrdy अणु
	u16   rx_id;                  /* FC rx_id of target command */
	u16   _resvd0;                /* reserved */
	u32   rel_offset;             /* data sequence relative offset */
	u32   sgl_cnt;                /* scatter-gather list count */
	u32   data_len;               /* length of data expected to send */
	u64   sgl_addr;               /* scatter-gather list address */
पूर्ण;

/*
 * fcpio_trsp: host -> firmware request
 *
 * used क्रम requesting the firmware to send out a response क्रम a target
 * command
 */
काष्ठा fcpio_trsp अणु
	u16   rx_id;                  /* FC rx_id of target command */
	u16   _resvd0;                /* reserved */
	u32   sense_len;              /* sense data buffer length */
	u64   sense_addr;             /* sense data buffer address */
	u16   _resvd1;                /* reserved */
	u8    flags;                  /* response request flags */
	u8    scsi_status;            /* SCSI status */
	u32   residual;               /* SCSI data residual value of I/O */
पूर्ण;

/*
 * resposnse request flags
 */
#घोषणा FCPIO_TRSP_RESID_UNDER  0x08   /* residual is valid and is underflow */
#घोषणा FCPIO_TRSP_RESID_OVER   0x04   /* residual is valid and is overflow */

/*
 * fcpio_tपंचांगf_ack: host -> firmware response
 *
 * used by the host to indicate to the firmware it has received and processed
 * the target पंचांगf request
 */
काष्ठा fcpio_tपंचांगf_ack अणु
	u16   rx_id;                  /* FC rx_id of target command */
	u16   _resvd0;                /* reserved */
	u32   पंचांगf_status;             /* SCSI task management status */
पूर्ण;

/*
 * fcpio_tपात: host -> firmware request
 *
 * used by the host to request the firmware to पात a target request that was
 * received by the firmware
 */
काष्ठा fcpio_tपात अणु
	u16   rx_id;                  /* rx_id of the target request */
पूर्ण;

/*
 * fcpio_reset: host -> firmware request
 *
 * used by the host to संकेत a reset of the driver to the firmware
 * and to request firmware to clean up all outstanding I/O
 */
काष्ठा fcpio_reset अणु
	u32   _resvd;
पूर्ण;

क्रमागत fcpio_flogi_reg_क्रमmat_type अणु
	FCPIO_FLOGI_REG_DEF_DEST = 0,    /* Use the oui | s_id mac क्रमmat */
	FCPIO_FLOGI_REG_GW_DEST,         /* Use the fixed gateway mac */
पूर्ण;

/*
 * fcpio_flogi_reg: host -> firmware request
 *
 * fc vnic only
 * used by the host to notअगरy the firmware of the lअगर's s_id
 * and destination mac address क्रमmat
 */
काष्ठा fcpio_flogi_reg अणु
	u8 क्रमmat;
	u8 s_id[3];			/* FC vNIC only: Source S_ID */
	u8 gateway_mac[ETH_ALEN];	/* Destination gateway mac */
	u16 _resvd;
	u32 r_a_tov;			/* R_A_TOV in msec */
	u32 e_d_tov;			/* E_D_TOV in msec */
पूर्ण;

/*
 * fcpio_echo: host -> firmware request
 *
 * sends a heartbeat echo request to the firmware
 */
काष्ठा fcpio_echo अणु
	u32 _resvd;
पूर्ण;

/*
 * fcpio_lunmap_req: host -> firmware request
 *
 * scsi vnic only
 * sends a request to retrieve the lunmap table क्रम scsi vnics
 */
काष्ठा fcpio_lunmap_req अणु
	u64 addr;                     /* address of the buffer */
	u32 len;                      /* len of the buffer */
पूर्ण;

/*
 * fcpio_flogi_fip_reg: host -> firmware request
 *
 * fc vnic only
 * used by the host to notअगरy the firmware of the lअगर's s_id
 * and destination mac address क्रमmat
 */
काष्ठा fcpio_flogi_fip_reg अणु
	u8    _resvd0;
	u8     s_id[3];               /* FC vNIC only: Source S_ID */
	u8     fcf_mac[ETH_ALEN];     /* FCF Target destination mac */
	u16   _resvd1;
	u32   r_a_tov;                /* R_A_TOV in msec */
	u32   e_d_tov;                /* E_D_TOV in msec */
	u8    ha_mac[ETH_ALEN];       /* Host adapter source mac */
	u16   _resvd2;
पूर्ण;

/*
 * Basic काष्ठाure क्रम all fcpio काष्ठाures that are sent from the host to the
 * firmware.  They are 128 bytes per काष्ठाure.
 */
#घोषणा FCPIO_HOST_REQ_LEN      128     /* expected length of host requests */

काष्ठा fcpio_host_req अणु
	काष्ठा fcpio_header hdr;

	जोड़ अणु
		/*
		 * Defines space needed क्रम request
		 */
		u8 buf[FCPIO_HOST_REQ_LEN - माप(काष्ठा fcpio_header)];

		/*
		 * Initiator host requests
		 */
		काष्ठा fcpio_icmnd_16               icmnd_16;
		काष्ठा fcpio_icmnd_32               icmnd_32;
		काष्ठा fcpio_iपंचांगf                   iपंचांगf;

		/*
		 * Target host requests
		 */
		काष्ठा fcpio_tdata                  tdata;
		काष्ठा fcpio_txrdy                  txrdy;
		काष्ठा fcpio_trsp                   trsp;
		काष्ठा fcpio_tपंचांगf_ack               tपंचांगf_ack;
		काष्ठा fcpio_tपात                 tपात;

		/*
		 * Misc requests
		 */
		काष्ठा fcpio_reset                  reset;
		काष्ठा fcpio_flogi_reg              flogi_reg;
		काष्ठा fcpio_echo                   echo;
		काष्ठा fcpio_lunmap_req             lunmap_req;
		काष्ठा fcpio_flogi_fip_reg          flogi_fip_reg;
	पूर्ण u;
पूर्ण;

/*
 * fcpio_icmnd_cmpl: firmware -> host response
 *
 * used क्रम sending the host a response to an initiator command
 */
काष्ठा fcpio_icmnd_cmpl अणु
	u8    _resvd0[6];             /* reserved */
	u8    flags;                  /* response flags */
	u8    scsi_status;            /* SCSI status */
	u32   residual;               /* SCSI data residual length */
	u32   sense_len;              /* SCSI sense length */
पूर्ण;

/*
 * response flags
 */
#घोषणा FCPIO_ICMND_CMPL_RESID_UNDER    0x08    /* resid under and valid */
#घोषणा FCPIO_ICMND_CMPL_RESID_OVER     0x04    /* resid over and valid */

/*
 * fcpio_iपंचांगf_cmpl: firmware -> host response
 *
 * used क्रम sending the host a response क्रम a iपंचांगf request
 */
काष्ठा fcpio_iपंचांगf_cmpl अणु
	u32    _resvd;                /* reserved */
पूर्ण;

/*
 * fcpio_tcmnd_16: firmware -> host request
 *
 * used by the firmware to notअगरy the host of an incoming target SCSI 16-Byte
 * request
 */
काष्ठा fcpio_tcmnd_16 अणु
	u8    lun[LUN_ADDRESS];       /* FC vNIC only: LUN address */
	u8    crn;                    /* SCSI Command Reference No. */
	u8    pri_ta;                 /* SCSI Priority and Task attribute */
	u8    _resvd2;                /* reserved: should be 0 */
	u8    flags;                  /* command flags */
	u8    scsi_cdb[CDB_16];       /* SCSI Cmnd Descriptor Block */
	u32   data_len;               /* length of data expected */
	u8    _resvd1;                /* reserved */
	u8    s_id[3];		      /* FC vNIC only: Source S_ID */
पूर्ण;

/*
 * Priority/Task Attribute settings
 */
#घोषणा FCPIO_TCMND_PTA_SIMPLE      0   /* simple task attribute */
#घोषणा FCPIO_TCMND_PTA_HEADQ       1   /* head of queue task attribute */
#घोषणा FCPIO_TCMND_PTA_ORDERED     2   /* ordered task attribute */
#घोषणा FCPIO_TCMND_PTA_ACA         4   /* स्वतः contingent allegiance */
#घोषणा FCPIO_TCMND_PRI_SHIFT       3   /* priority field starts in bit 3 */

/*
 * Command flags
 */
#घोषणा FCPIO_TCMND_RDDATA      0x02    /* पढ़ो data */
#घोषणा FCPIO_TCMND_WRDATA      0x01    /* ग_लिखो data */

/*
 * fcpio_tcmnd_32: firmware -> host request
 *
 * used by the firmware to notअगरy the host of an incoming target SCSI 32-Byte
 * request
 */
काष्ठा fcpio_tcmnd_32 अणु
	u8    lun[LUN_ADDRESS];       /* FC vNIC only: LUN address */
	u8    crn;                    /* SCSI Command Reference No. */
	u8    pri_ta;                 /* SCSI Priority and Task attribute */
	u8    _resvd2;                /* reserved: should be 0 */
	u8    flags;                  /* command flags */
	u8    scsi_cdb[CDB_32];       /* SCSI Cmnd Descriptor Block */
	u32   data_len;               /* length of data expected */
	u8    _resvd0;                /* reserved */
	u8    s_id[3];		      /* FC vNIC only: Source S_ID */
पूर्ण;

/*
 * fcpio_tdrsp_cmpl: firmware -> host response
 *
 * used by the firmware to notअगरy the host of a response to a host target
 * command
 */
काष्ठा fcpio_tdrsp_cmpl अणु
	u16   rx_id;                  /* rx_id of the target request */
	u16   _resvd0;                /* reserved */
पूर्ण;

/*
 * fcpio_tपंचांगf: firmware -> host request
 *
 * used by the firmware to notअगरy the host of an incoming task management
 * function request
 */
काष्ठा fcpio_tपंचांगf अणु
	u8    _resvd0;                /* reserved */
	u8    s_id[3];		      /* FC vNIC only: Source S_ID */
	u8    lun[LUN_ADDRESS];       /* FC vNIC only: LUN address */
	u8    crn;                    /* SCSI Command Reference No. */
	u8    _resvd2[3];             /* reserved */
	u32   पंचांगf_type;               /* task management request type */
पूर्ण;

/*
 * Task Management request
 */
#घोषणा FCPIO_TTMF_CLR_ACA      0x40    /* Clear ACA condition */
#घोषणा FCPIO_TTMF_LUN_RESET    0x10    /* logical unit reset task mgmt */
#घोषणा FCPIO_TTMF_CLR_TASK_SET 0x04    /* clear task set */
#घोषणा FCPIO_TTMF_ABT_TASK_SET 0x02    /* पात task set */
#घोषणा FCPIO_TTMF_ABT_TASK     0x01    /* पात task */

/*
 * fcpio_tपात_cmpl: firmware -> host response
 *
 * used by the firmware to respond to a host's tपात request
 */
काष्ठा fcpio_tपात_cmpl अणु
	u16   rx_id;                  /* rx_id of the target request */
	u16   _resvd0;                /* reserved */
पूर्ण;

/*
 * fcpio_ack: firmware -> host response
 *
 * used by firmware to notअगरy the host of the last work request received
 */
काष्ठा fcpio_ack अणु
	u16  request_out;             /* last host entry received */
	u16  _resvd;
पूर्ण;

/*
 * fcpio_reset_cmpl: firmware -> host response
 *
 * use by firmware to respond to the host's reset request
 */
काष्ठा fcpio_reset_cmpl अणु
	u16   vnic_id;
पूर्ण;

/*
 * fcpio_flogi_reg_cmpl: firmware -> host response
 *
 * fc vnic only
 * response to the fcpio_flogi_reg request
 */
काष्ठा fcpio_flogi_reg_cmpl अणु
	u32 _resvd;
पूर्ण;

/*
 * fcpio_echo_cmpl: firmware -> host response
 *
 * response to the fcpio_echo request
 */
काष्ठा fcpio_echo_cmpl अणु
	u32 _resvd;
पूर्ण;

/*
 * fcpio_lunmap_chng: firmware -> host notअगरication
 *
 * scsi vnic only
 * notअगरies the host that the lunmap tables have changed
 */
काष्ठा fcpio_lunmap_chng अणु
	u32 _resvd;
पूर्ण;

/*
 * fcpio_lunmap_req_cmpl: firmware -> host response
 *
 * scsi vnic only
 * response क्रम lunmap table request from the host
 */
काष्ठा fcpio_lunmap_req_cmpl अणु
	u32 _resvd;
पूर्ण;

/*
 * Basic काष्ठाure क्रम all fcpio काष्ठाures that are sent from the firmware to
 * the host.  They are 64 bytes per काष्ठाure.
 */
#घोषणा FCPIO_FW_REQ_LEN        64      /* expected length of fw requests */
काष्ठा fcpio_fw_req अणु
	काष्ठा fcpio_header hdr;

	जोड़ अणु
		/*
		 * Defines space needed क्रम request
		 */
		u8 buf[FCPIO_FW_REQ_LEN - माप(काष्ठा fcpio_header)];

		/*
		 * Initiator firmware responses
		 */
		काष्ठा fcpio_icmnd_cmpl         icmnd_cmpl;
		काष्ठा fcpio_iपंचांगf_cmpl          iपंचांगf_cmpl;

		/*
		 * Target firmware new requests
		 */
		काष्ठा fcpio_tcmnd_16           tcmnd_16;
		काष्ठा fcpio_tcmnd_32           tcmnd_32;

		/*
		 * Target firmware responses
		 */
		काष्ठा fcpio_tdrsp_cmpl         tdrsp_cmpl;
		काष्ठा fcpio_tपंचांगf               tपंचांगf;
		काष्ठा fcpio_tपात_cmpl        tपात_cmpl;

		/*
		 * Firmware response to work received
		 */
		काष्ठा fcpio_ack                ack;

		/*
		 * Misc requests
		 */
		काष्ठा fcpio_reset_cmpl         reset_cmpl;
		काष्ठा fcpio_flogi_reg_cmpl     flogi_reg_cmpl;
		काष्ठा fcpio_echo_cmpl          echo_cmpl;
		काष्ठा fcpio_lunmap_chng        lunmap_chng;
		काष्ठा fcpio_lunmap_req_cmpl    lunmap_req_cmpl;
	पूर्ण u;
पूर्ण;

/*
 * Access routines to encode and decode the color bit, which is the most
 * signअगरicant bit of the MSB of the काष्ठाure
 */
अटल अंतरभूत व्योम fcpio_color_enc(काष्ठा fcpio_fw_req *fw_req, u8 color)
अणु
	u8 *c = ((u8 *) fw_req) + माप(काष्ठा fcpio_fw_req) - 1;

	अगर (color)
		*c |= 0x80;
	अन्यथा
		*c &= ~0x80;
पूर्ण

अटल अंतरभूत व्योम fcpio_color_dec(काष्ठा fcpio_fw_req *fw_req, u8 *color)
अणु
	u8 *c = ((u8 *) fw_req) + माप(काष्ठा fcpio_fw_req) - 1;

	*color = *c >> 7;

	/*
	 * Make sure color bit is पढ़ो from desc *beक्रमe* other fields
	 * are पढ़ो from desc.  Hardware guarantees color bit is last
	 * bit (byte) written.  Adding the rmb() prevents the compiler
	 * and/or CPU from reordering the पढ़ोs which would potentially
	 * result in पढ़ोing stale values.
	 */

	rmb();

पूर्ण

/*
 * Lunmap table entry क्रम scsi vnics
 */
#घोषणा FCPIO_LUNMAP_TABLE_SIZE     256
#घोषणा FCPIO_FLAGS_LUNMAP_VALID    0x80
#घोषणा FCPIO_FLAGS_BOOT            0x01
काष्ठा fcpio_lunmap_entry अणु
	u8    bus;
	u8    target;
	u8    lun;
	u8    path_cnt;
	u16   flags;
	u16   update_cnt;
पूर्ण;

काष्ठा fcpio_lunmap_tbl अणु
	u32                   update_cnt;
	काष्ठा fcpio_lunmap_entry   lunmaps[FCPIO_LUNMAP_TABLE_SIZE];
पूर्ण;

#पूर्ण_अगर /* _FCPIO_H_ */
