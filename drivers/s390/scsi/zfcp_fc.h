<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * zfcp device driver
 *
 * Fibre Channel related definitions and अंतरभूत functions क्रम the zfcp
 * device driver
 *
 * Copyright IBM Corp. 2009, 2017
 */

#अगर_अघोषित ZFCP_FC_H
#घोषणा ZFCP_FC_H

#समावेश <scsi/fc/fc_els.h>
#समावेश <scsi/fc/fc_fcp.h>
#समावेश <scsi/fc/fc_ns.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश "zfcp_fsf.h"

#घोषणा ZFCP_FC_CT_SIZE_PAGE	  (PAGE_SIZE - माप(काष्ठा fc_ct_hdr))
#घोषणा ZFCP_FC_GPN_FT_ENT_PAGE	  (ZFCP_FC_CT_SIZE_PAGE \
					/ माप(काष्ठा fc_gpn_ft_resp))
#घोषणा ZFCP_FC_GPN_FT_NUM_BUFS	  4 /* memory pages */

#घोषणा ZFCP_FC_GPN_FT_MAX_SIZE	  (ZFCP_FC_GPN_FT_NUM_BUFS * PAGE_SIZE \
					- माप(काष्ठा fc_ct_hdr))
#घोषणा ZFCP_FC_GPN_FT_MAX_ENT	  (ZFCP_FC_GPN_FT_NUM_BUFS * \
					(ZFCP_FC_GPN_FT_ENT_PAGE + 1))

#घोषणा ZFCP_FC_CTELS_TMO	(2 * FC_DEF_R_A_TOV / 1000)

/**
 * काष्ठा zfcp_fc_event - FC HBAAPI event क्रम पूर्णांकernal queueing from irq context
 * @code: Event code
 * @data: Event data
 * @list: list_head क्रम zfcp_fc_events list
 */
काष्ठा zfcp_fc_event अणु
	क्रमागत fc_host_event_code code;
	u32 data;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा zfcp_fc_events - Infraकाष्ठाure क्रम posting FC events from irq context
 * @list: List क्रम queueing of events from irq context to workqueue
 * @list_lock: Lock क्रम event list
 * @work: work_काष्ठा क्रम क्रमwarding events in workqueue
*/
काष्ठा zfcp_fc_events अणु
	काष्ठा list_head list;
	spinlock_t list_lock;
	काष्ठा work_काष्ठा work;
पूर्ण;

/**
 * काष्ठा zfcp_fc_gid_pn_req - container क्रम ct header plus gid_pn request
 * @ct_hdr: FC GS common transport header
 * @gid_pn: GID_PN request
 */
काष्ठा zfcp_fc_gid_pn_req अणु
	काष्ठा fc_ct_hdr	ct_hdr;
	काष्ठा fc_ns_gid_pn	gid_pn;
पूर्ण __packed;

/**
 * काष्ठा zfcp_fc_gid_pn_rsp - container क्रम ct header plus gid_pn response
 * @ct_hdr: FC GS common transport header
 * @gid_pn: GID_PN response
 */
काष्ठा zfcp_fc_gid_pn_rsp अणु
	काष्ठा fc_ct_hdr	ct_hdr;
	काष्ठा fc_gid_pn_resp	gid_pn;
पूर्ण __packed;

/**
 * काष्ठा zfcp_fc_gpn_ft - container क्रम ct header plus gpn_ft request
 * @ct_hdr: FC GS common transport header
 * @gpn_ft: GPN_FT request
 */
काष्ठा zfcp_fc_gpn_ft_req अणु
	काष्ठा fc_ct_hdr	ct_hdr;
	काष्ठा fc_ns_gid_ft	gpn_ft;
पूर्ण __packed;

/**
 * काष्ठा zfcp_fc_gspn_req - container क्रम ct header plus GSPN_ID request
 * @ct_hdr: FC GS common transport header
 * @gspn: GSPN_ID request
 */
काष्ठा zfcp_fc_gspn_req अणु
	काष्ठा fc_ct_hdr	ct_hdr;
	काष्ठा fc_gid_pn_resp	gspn;
पूर्ण __packed;

/**
 * काष्ठा zfcp_fc_gspn_rsp - container क्रम ct header plus GSPN_ID response
 * @ct_hdr: FC GS common transport header
 * @gspn: GSPN_ID response
 * @name: The name string of the GSPN_ID response
 */
काष्ठा zfcp_fc_gspn_rsp अणु
	काष्ठा fc_ct_hdr	ct_hdr;
	काष्ठा fc_gspn_resp	gspn;
	अक्षर			name[FC_SYMBOLIC_NAME_SIZE];
पूर्ण __packed;

/**
 * काष्ठा zfcp_fc_rspn_req - container क्रम ct header plus RSPN_ID request
 * @ct_hdr: FC GS common transport header
 * @rspn: RSPN_ID request
 * @name: The name string of the RSPN_ID request
 */
काष्ठा zfcp_fc_rspn_req अणु
	काष्ठा fc_ct_hdr	ct_hdr;
	काष्ठा fc_ns_rspn	rspn;
	अक्षर			name[FC_SYMBOLIC_NAME_SIZE];
पूर्ण __packed;

/**
 * काष्ठा zfcp_fc_req - Container क्रम FC ELS and CT requests sent from zfcp
 * @ct_els: data required क्रम issuing fsf command
 * @sg_req: scatterlist entry क्रम request data, refers to embedded @u submember
 * @sg_rsp: scatterlist entry क्रम response data, refers to embedded @u submember
 * @u: request and response specअगरic data
 * @u.adisc: ADISC specअगरic data
 * @u.adisc.req: ADISC request
 * @u.adisc.rsp: ADISC response
 * @u.gid_pn: GID_PN specअगरic data
 * @u.gid_pn.req: GID_PN request
 * @u.gid_pn.rsp: GID_PN response
 * @u.gpn_ft: GPN_FT specअगरic data
 * @u.gpn_ft.sg_rsp2: GPN_FT response, not embedded here, allocated अन्यथाwhere
 * @u.gpn_ft.req: GPN_FT request
 * @u.gspn: GSPN specअगरic data
 * @u.gspn.req: GSPN request
 * @u.gspn.rsp: GSPN response
 * @u.rspn: RSPN specअगरic data
 * @u.rspn.req: RSPN request
 * @u.rspn.rsp: RSPN response
 */
काष्ठा zfcp_fc_req अणु
	काष्ठा zfcp_fsf_ct_els				ct_els;
	काष्ठा scatterlist				sg_req;
	काष्ठा scatterlist				sg_rsp;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा fc_els_adisc		req;
			काष्ठा fc_els_adisc		rsp;
		पूर्ण adisc;
		काष्ठा अणु
			काष्ठा zfcp_fc_gid_pn_req	req;
			काष्ठा zfcp_fc_gid_pn_rsp	rsp;
		पूर्ण gid_pn;
		काष्ठा अणु
			काष्ठा scatterlist sg_rsp2[ZFCP_FC_GPN_FT_NUM_BUFS - 1];
			काष्ठा zfcp_fc_gpn_ft_req	req;
		पूर्ण gpn_ft;
		काष्ठा अणु
			काष्ठा zfcp_fc_gspn_req		req;
			काष्ठा zfcp_fc_gspn_rsp		rsp;
		पूर्ण gspn;
		काष्ठा अणु
			काष्ठा zfcp_fc_rspn_req		req;
			काष्ठा fc_ct_hdr		rsp;
		पूर्ण rspn;
	पूर्ण u;
पूर्ण;

/**
 * क्रमागत zfcp_fc_wka_status - FC WKA port status in zfcp
 * @ZFCP_FC_WKA_PORT_OFFLINE: Port is बंदd and not in use
 * @ZFCP_FC_WKA_PORT_CLOSING: The FSF "close port" request is pending
 * @ZFCP_FC_WKA_PORT_OPENING: The FSF "open port" request is pending
 * @ZFCP_FC_WKA_PORT_ONLINE: The port is खोलो and the port handle is valid
 */
क्रमागत zfcp_fc_wka_status अणु
	ZFCP_FC_WKA_PORT_OFFLINE,
	ZFCP_FC_WKA_PORT_CLOSING,
	ZFCP_FC_WKA_PORT_OPENING,
	ZFCP_FC_WKA_PORT_ONLINE,
पूर्ण;

/**
 * काष्ठा zfcp_fc_wka_port - representation of well-known-address (WKA) FC port
 * @adapter: Poपूर्णांकer to adapter काष्ठाure this WKA port beदीर्घs to
 * @completion_wq: Wait क्रम completion of खोलो/बंद command
 * @status: Current status of WKA port
 * @refcount: Reference count to keep port खोलो as दीर्घ as it is in use
 * @d_id: FC destination id or well-known-address
 * @handle: FSF handle क्रम the खोलो WKA port
 * @mutex: Mutex used during खोलोing/closing state changes
 * @work: For delaying the closing of the WKA port
 */
काष्ठा zfcp_fc_wka_port अणु
	काष्ठा zfcp_adapter	*adapter;
	रुको_queue_head_t	completion_wq;
	क्रमागत zfcp_fc_wka_status	status;
	atomic_t		refcount;
	u32			d_id;
	u32			handle;
	काष्ठा mutex		mutex;
	काष्ठा delayed_work	work;
पूर्ण;

/**
 * काष्ठा zfcp_fc_wka_ports - Data काष्ठाures क्रम FC generic services
 * @ms: FC Management service
 * @ts: FC समय service
 * @ds: FC directory service
 * @as: FC alias service
 */
काष्ठा zfcp_fc_wka_ports अणु
	काष्ठा zfcp_fc_wka_port ms;
	काष्ठा zfcp_fc_wka_port ts;
	काष्ठा zfcp_fc_wka_port ds;
	काष्ठा zfcp_fc_wka_port as;
पूर्ण;

/**
 * zfcp_fc_scsi_to_fcp - setup FCP command with data from scsi_cmnd
 * @fcp: fcp_cmnd to setup
 * @scsi: scsi_cmnd where to get LUN, task attributes/flags and CDB
 */
अटल अंतरभूत
व्योम zfcp_fc_scsi_to_fcp(काष्ठा fcp_cmnd *fcp, काष्ठा scsi_cmnd *scsi)
अणु
	u32 datalen;

	पूर्णांक_to_scsilun(scsi->device->lun, (काष्ठा scsi_lun *) &fcp->fc_lun);

	fcp->fc_pri_ta = FCP_PTA_SIMPLE;

	अगर (scsi->sc_data_direction == DMA_FROM_DEVICE)
		fcp->fc_flags |= FCP_CFL_RDDATA;
	अगर (scsi->sc_data_direction == DMA_TO_DEVICE)
		fcp->fc_flags |= FCP_CFL_WRDATA;

	स_नकल(fcp->fc_cdb, scsi->cmnd, scsi->cmd_len);

	datalen = scsi_bufflen(scsi);
	fcp->fc_dl = cpu_to_be32(datalen);

	अगर (scsi_get_prot_type(scsi) == SCSI_PROT_DIF_TYPE1) अणु
		datalen += datalen / scsi->device->sector_size * 8;
		fcp->fc_dl = cpu_to_be32(datalen);
	पूर्ण
पूर्ण

/**
 * zfcp_fc_fcp_पंचांग() - Setup FCP command as task management command.
 * @fcp: Poपूर्णांकer to FCP_CMND IU to set up.
 * @dev: Poपूर्णांकer to SCSI_device where to send the task management command.
 * @पंचांग_flags: Task management flags to setup पंचांग command.
 */
अटल अंतरभूत
व्योम zfcp_fc_fcp_पंचांग(काष्ठा fcp_cmnd *fcp, काष्ठा scsi_device *dev, u8 पंचांग_flags)
अणु
	पूर्णांक_to_scsilun(dev->lun, (काष्ठा scsi_lun *) &fcp->fc_lun);
	fcp->fc_पंचांग_flags = पंचांग_flags;
पूर्ण

/**
 * zfcp_fc_evap_fcp_rsp - evaluate FCP RSP IU and update scsi_cmnd accordingly
 * @fcp_rsp: FCP RSP IU to evaluate
 * @scsi: SCSI command where to update status and sense buffer
 */
अटल अंतरभूत
व्योम zfcp_fc_eval_fcp_rsp(काष्ठा fcp_resp_with_ext *fcp_rsp,
			  काष्ठा scsi_cmnd *scsi)
अणु
	काष्ठा fcp_resp_rsp_info *rsp_info;
	अक्षर *sense;
	u32 sense_len, resid;
	u8 rsp_flags;

	scsi->result |= fcp_rsp->resp.fr_status;

	rsp_flags = fcp_rsp->resp.fr_flags;

	अगर (unlikely(rsp_flags & FCP_RSP_LEN_VAL)) अणु
		rsp_info = (काष्ठा fcp_resp_rsp_info *) &fcp_rsp[1];
		अगर (rsp_info->rsp_code == FCP_TMF_CMPL)
			set_host_byte(scsi, DID_OK);
		अन्यथा अणु
			set_host_byte(scsi, DID_ERROR);
			वापस;
		पूर्ण
	पूर्ण

	अगर (unlikely(rsp_flags & FCP_SNS_LEN_VAL)) अणु
		sense = (अक्षर *) &fcp_rsp[1];
		अगर (rsp_flags & FCP_RSP_LEN_VAL)
			sense += be32_to_cpu(fcp_rsp->ext.fr_rsp_len);
		sense_len = min_t(u32, be32_to_cpu(fcp_rsp->ext.fr_sns_len),
				  SCSI_SENSE_BUFFERSIZE);
		स_नकल(scsi->sense_buffer, sense, sense_len);
	पूर्ण

	अगर (unlikely(rsp_flags & FCP_RESID_UNDER)) अणु
		resid = be32_to_cpu(fcp_rsp->ext.fr_resid);
		scsi_set_resid(scsi, resid);
		अगर (scsi_bufflen(scsi) - resid < scsi->underflow &&
		     !(rsp_flags & FCP_SNS_LEN_VAL) &&
		     fcp_rsp->resp.fr_status == SAM_STAT_GOOD)
			set_host_byte(scsi, DID_ERROR);
	पूर्ण अन्यथा अगर (unlikely(rsp_flags & FCP_RESID_OVER)) अणु
		/* FCP_DL was not sufficient क्रम SCSI data length */
		अगर (fcp_rsp->resp.fr_status == SAM_STAT_GOOD)
			set_host_byte(scsi, DID_ERROR);
	पूर्ण
पूर्ण

#पूर्ण_अगर
