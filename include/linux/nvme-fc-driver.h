<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016, Avago Technologies
 */

#अगर_अघोषित _NVME_FC_DRIVER_H
#घोषणा _NVME_FC_DRIVER_H 1

#समावेश <linux/scatterlist.h>


/*
 * **********************  FC-NVME LS API ********************
 *
 *  Data काष्ठाures used by both FC-NVME hosts and FC-NVME
 *  tarमाला_लो to perक्रमm FC-NVME LS requests or transmit
 *  responses.
 *
 * ***********************************************************
 */

/**
 * काष्ठा nvmefc_ls_req - Request काष्ठाure passed from the transport
 *            to the LLDD to perक्रमm a NVME-FC LS request and obtain
 *            a response.
 *            Used by nvme-fc transport (host) to send LS's such as
 *              Create Association, Create Connection and Disconnect
 *              Association.
 *            Used by the nvmet-fc transport (controller) to send
 *              LS's such as Disconnect Association.
 *
 * Values set by the requestor prior to calling the LLDD ls_req entrypoपूर्णांक:
 * @rqstaddr: poपूर्णांकer to request buffer
 * @rqstdma:  PCI DMA address of request buffer
 * @rqstlen:  Length, in bytes, of request buffer
 * @rspaddr:  poपूर्णांकer to response buffer
 * @rspdma:   PCI DMA address of response buffer
 * @rsplen:   Length, in bytes, of response buffer
 * @समयout:  Maximum amount of समय, in seconds, to रुको क्रम the LS response.
 *            If समयout exceeded, LLDD to पात LS exchange and complete
 *            LS request with error status.
 * @निजी:  poपूर्णांकer to memory allocated aदीर्घside the ls request काष्ठाure
 *            that is specअगरically क्रम the LLDD to use जबतक processing the
 *            request. The length of the buffer corresponds to the
 *            lsrqst_priv_sz value specअगरied in the xxx_ढाँचा supplied
 *            by the LLDD.
 * @करोne:     The callback routine the LLDD is to invoke upon completion of
 *            the LS request. req argument is the poपूर्णांकer to the original LS
 *            request काष्ठाure. Status argument must be 0 upon success, a
 *            negative त्रुटि_सं on failure (example: -ENXIO).
 */
काष्ठा nvmefc_ls_req अणु
	व्योम			*rqstaddr;
	dma_addr_t		rqstdma;
	u32			rqstlen;
	व्योम			*rspaddr;
	dma_addr_t		rspdma;
	u32			rsplen;
	u32			समयout;

	व्योम			*निजी;

	व्योम (*करोne)(काष्ठा nvmefc_ls_req *req, पूर्णांक status);

पूर्ण __aligned(माप(u64));	/* alignment क्रम other things alloc'd with */


/**
 * काष्ठा nvmefc_ls_rsp - Structure passed from the transport to the LLDD
 *            to request the transmit the NVME-FC LS response to a
 *            NVME-FC LS request.   The काष्ठाure originates in the LLDD
 *            and is given to the transport via the xxx_rcv_ls_req()
 *            transport routine. As such, the काष्ठाure represents the
 *            FC exchange context क्रम the NVME-FC LS request that was
 *            received and which the response is to be sent क्रम.
 *            Used by the LLDD to pass the nvmet-fc transport (controller)
 *              received LS's such as Create Association, Create Connection
 *              and Disconnect Association.
 *            Used by the LLDD to pass the nvme-fc transport (host)
 *              received LS's such as Disconnect Association or Disconnect
 *              Connection.
 *
 * The काष्ठाure is allocated by the LLDD whenever a LS Request is received
 * from the FC link. The address of the काष्ठाure is passed to the nvmet-fc
 * or nvme-fc layer via the xxx_rcv_ls_req() transport routines.
 *
 * The address of the काष्ठाure is to be passed back to the LLDD
 * when the response is to be transmit. The LLDD will use the address to
 * map back to the LLDD exchange काष्ठाure which मुख्यtains inक्रमmation such
 * the remote N_Port that sent the LS as well as any FC exchange context.
 * Upon completion of the LS response transmit, the LLDD will pass the
 * address of the काष्ठाure back to the transport LS rsp करोne() routine,
 * allowing the transport release dma resources. Upon completion of
 * the करोne() routine, no further access to the काष्ठाure will be made by
 * the transport and the LLDD can de-allocate the काष्ठाure.
 *
 * Field initialization:
 *   At the समय of the xxx_rcv_ls_req() call, there is no content that
 *     is valid in the काष्ठाure.
 *
 *   When the काष्ठाure is used क्रम the LLDD->xmt_ls_rsp() call, the
 *     transport layer will fully set the fields in order to specअगरy the
 *     response payload buffer and its length as well as the करोne routine
 *     to be called upon completion of the transmit.  The transport layer
 *     will also set a निजी poपूर्णांकer क्रम its own use in the करोne routine.
 *
 * Values set by the transport layer prior to calling the LLDD xmt_ls_rsp
 * entrypoपूर्णांक:
 * @rspbuf:   poपूर्णांकer to the LS response buffer
 * @rspdma:   PCI DMA address of the LS response buffer
 * @rsplen:   Length, in bytes, of the LS response buffer
 * @करोne:     The callback routine the LLDD is to invoke upon completion of
 *            transmitting the LS response. req argument is the poपूर्णांकer to
 *            the original ls request.
 * @nvme_fc_निजी:  poपूर्णांकer to an पूर्णांकernal transport-specअगरic काष्ठाure
 *            used as part of the transport करोne() processing. The LLDD is
 *            not to access this poपूर्णांकer.
 */
काष्ठा nvmefc_ls_rsp अणु
	व्योम		*rspbuf;
	dma_addr_t	rspdma;
	u16		rsplen;

	व्योम (*करोne)(काष्ठा nvmefc_ls_rsp *rsp);
	व्योम		*nvme_fc_निजी;	/* LLDD is not to access !! */
पूर्ण;



/*
 * **********************  LLDD FC-NVME Host API ********************
 *
 *  For FC LLDD's that are the NVME Host role.
 *
 * ******************************************************************
 */


/**
 * काष्ठा nvme_fc_port_info - port-specअगरic ids and FC connection-specअगरic
 *                            data element used during NVME Host role
 *                            registrations
 *
 * Static fields describing the port being रेजिस्टरed:
 * @node_name: FC WWNN क्रम the port
 * @port_name: FC WWPN क्रम the port
 * @port_role: What NVME roles are supported (see FC_PORT_ROLE_xxx)
 * @dev_loss_पंचांगo: maximum delay क्रम reconnects to an association on
 *             this device. Used only on a remoteport.
 *
 * Initialization values क्रम dynamic port fields:
 * @port_id:      FC N_Port_ID currently asचिन्हित the port. Upper 8 bits must
 *                be set to 0.
 */
काष्ठा nvme_fc_port_info अणु
	u64			node_name;
	u64			port_name;
	u32			port_role;
	u32			port_id;
	u32			dev_loss_पंचांगo;
पूर्ण;

क्रमागत nvmefc_fcp_datadir अणु
	NVMEFC_FCP_NODATA,	/* payload_length and sg_cnt will be zero */
	NVMEFC_FCP_WRITE,
	NVMEFC_FCP_READ,
पूर्ण;


/**
 * काष्ठा nvmefc_fcp_req - Request काष्ठाure passed from NVME-FC transport
 *                         to LLDD in order to perक्रमm a NVME FCP IO operation.
 *
 * Values set by the NVME-FC layer prior to calling the LLDD fcp_io
 * entrypoपूर्णांक.
 * @cmdaddr:   poपूर्णांकer to the FCP CMD IU buffer
 * @rspaddr:   poपूर्णांकer to the FCP RSP IU buffer
 * @cmddma:    PCI DMA address of the FCP CMD IU buffer
 * @rspdma:    PCI DMA address of the FCP RSP IU buffer
 * @cmdlen:    Length, in bytes, of the FCP CMD IU buffer
 * @rsplen:    Length, in bytes, of the FCP RSP IU buffer
 * @payload_length: Length of DATA_IN or DATA_OUT payload data to transfer
 * @sg_table:  scatter/gather काष्ठाure क्रम payload data
 * @first_sgl: memory क्रम 1st scatter/gather list segment क्रम payload data
 * @sg_cnt:    number of elements in the scatter/gather list
 * @io_dir:    direction of the FCP request (see NVMEFC_FCP_xxx)
 * @sqid:      The nvme SQID the command is being issued on
 * @करोne:      The callback routine the LLDD is to invoke upon completion of
 *             the FCP operation. req argument is the poपूर्णांकer to the original
 *             FCP IO operation.
 * @निजी:   poपूर्णांकer to memory allocated aदीर्घside the FCP operation
 *             request काष्ठाure that is specअगरically क्रम the LLDD to use
 *             जबतक processing the operation. The length of the buffer
 *             corresponds to the fcprqst_priv_sz value specअगरied in the
 *             nvme_fc_port_ढाँचा supplied by the LLDD.
 *
 * Values set by the LLDD indicating completion status of the FCP operation.
 * Must be set prior to calling the करोne() callback.
 * @transferred_length: amount of payload data, in bytes, that were
 *             transferred. Should equal payload_length on success.
 * @rcv_rsplen: length, in bytes, of the FCP RSP IU received.
 * @status:    Completion status of the FCP operation. must be 0 upon success,
 *             negative त्रुटि_सं value upon failure (ex: -EIO). Note: this is
 *             NOT a reflection of the NVME CQE completion status. Only the
 *             status of the FCP operation at the NVME-FC level.
 */
काष्ठा nvmefc_fcp_req अणु
	व्योम			*cmdaddr;
	व्योम			*rspaddr;
	dma_addr_t		cmddma;
	dma_addr_t		rspdma;
	u16			cmdlen;
	u16			rsplen;

	u32			payload_length;
	काष्ठा sg_table		sg_table;
	काष्ठा scatterlist	*first_sgl;
	पूर्णांक			sg_cnt;
	क्रमागत nvmefc_fcp_datadir	io_dir;

	__le16			sqid;

	व्योम (*करोne)(काष्ठा nvmefc_fcp_req *req);

	व्योम			*निजी;

	u32			transferred_length;
	u16			rcv_rsplen;
	u32			status;
पूर्ण __aligned(माप(u64));	/* alignment क्रम other things alloc'd with */


/*
 * Direct copy of fc_port_state क्रमागत. For later merging
 */
क्रमागत nvme_fc_obj_state अणु
	FC_OBJSTATE_UNKNOWN,
	FC_OBJSTATE_NOTPRESENT,
	FC_OBJSTATE_ONLINE,
	FC_OBJSTATE_OFFLINE,		/* User has taken Port Offline */
	FC_OBJSTATE_BLOCKED,
	FC_OBJSTATE_BYPASSED,
	FC_OBJSTATE_DIAGNOSTICS,
	FC_OBJSTATE_LINKDOWN,
	FC_OBJSTATE_ERROR,
	FC_OBJSTATE_LOOPBACK,
	FC_OBJSTATE_DELETED,
पूर्ण;


/**
 * काष्ठा nvme_fc_local_port - काष्ठाure used between NVME-FC transport and
 *                 a LLDD to reference a local NVME host port.
 *                 Allocated/created by the nvme_fc_रेजिस्टर_localport()
 *                 transport पूर्णांकerface.
 *
 * Fields with अटल values क्रम the port. Initialized by the
 * port_info काष्ठा supplied to the registration call.
 * @port_num:  NVME-FC transport host port number
 * @port_role: NVME roles are supported on the port (see FC_PORT_ROLE_xxx)
 * @node_name: FC WWNN क्रम the port
 * @port_name: FC WWPN क्रम the port
 * @निजी:   poपूर्णांकer to memory allocated aदीर्घside the local port
 *             काष्ठाure that is specअगरically क्रम the LLDD to use.
 *             The length of the buffer corresponds to the local_priv_sz
 *             value specअगरied in the nvme_fc_port_ढाँचा supplied by
 *             the LLDD.
 * @dev_loss_पंचांगo: maximum delay क्रम reconnects to an association on
 *             this device. To modअगरy, lldd must call
 *             nvme_fc_set_remoteport_devloss().
 *
 * Fields with dynamic values. Values may change base on link state. LLDD
 * may reference fields directly to change them. Initialized by the
 * port_info काष्ठा supplied to the registration call.
 * @port_id:      FC N_Port_ID currently asचिन्हित the port. Upper 8 bits must
 *                be set to 0.
 * @port_state:   Operational state of the port.
 */
काष्ठा nvme_fc_local_port अणु
	/* अटल/पढ़ो-only fields */
	u32 port_num;
	u32 port_role;
	u64 node_name;
	u64 port_name;

	व्योम *निजी;

	/* dynamic fields */
	u32 port_id;
	क्रमागत nvme_fc_obj_state port_state;
पूर्ण __aligned(माप(u64));	/* alignment क्रम other things alloc'd with */


/**
 * काष्ठा nvme_fc_remote_port - काष्ठाure used between NVME-FC transport and
 *                 a LLDD to reference a remote NVME subप्रणाली port.
 *                 Allocated/created by the nvme_fc_रेजिस्टर_remoteport()
 *                 transport पूर्णांकerface.
 *
 * Fields with अटल values क्रम the port. Initialized by the
 * port_info काष्ठा supplied to the registration call.
 * @port_num:  NVME-FC transport remote subप्रणाली port number
 * @port_role: NVME roles are supported on the port (see FC_PORT_ROLE_xxx)
 * @node_name: FC WWNN क्रम the port
 * @port_name: FC WWPN क्रम the port
 * @localport: poपूर्णांकer to the NVME-FC local host port the subप्रणाली is
 *             connected to.
 * @निजी:   poपूर्णांकer to memory allocated aदीर्घside the remote port
 *             काष्ठाure that is specअगरically क्रम the LLDD to use.
 *             The length of the buffer corresponds to the remote_priv_sz
 *             value specअगरied in the nvme_fc_port_ढाँचा supplied by
 *             the LLDD.
 *
 * Fields with dynamic values. Values may change base on link or login
 * state. LLDD may reference fields directly to change them. Initialized by
 * the port_info काष्ठा supplied to the registration call.
 * @port_id:      FC N_Port_ID currently asचिन्हित the port. Upper 8 bits must
 *                be set to 0.
 * @port_state:   Operational state of the remote port. Valid values are
 *                ONLINE or UNKNOWN.
 */
काष्ठा nvme_fc_remote_port अणु
	/* अटल fields */
	u32 port_num;
	u32 port_role;
	u64 node_name;
	u64 port_name;
	काष्ठा nvme_fc_local_port *localport;
	व्योम *निजी;
	u32 dev_loss_पंचांगo;

	/* dynamic fields */
	u32 port_id;
	क्रमागत nvme_fc_obj_state port_state;
पूर्ण __aligned(माप(u64));	/* alignment क्रम other things alloc'd with */


/**
 * काष्ठा nvme_fc_port_ढाँचा - काष्ठाure containing अटल entrypoपूर्णांकs and
 *                 operational parameters क्रम an LLDD that supports NVME host
 *                 behavior. Passed by reference in port registrations.
 *                 NVME-FC transport remembers ढाँचा reference and may
 *                 access it during runसमय operation.
 *
 * Host/Initiator Transport Entrypoपूर्णांकs/Parameters:
 *
 * @localport_delete:  The LLDD initiates deletion of a localport via
 *       nvme_fc_deरेजिस्टर_localport(). However, the tearकरोwn is
 *       asynchronous. This routine is called upon the completion of the
 *       tearकरोwn to inक्रमm the LLDD that the localport has been deleted.
 *       Entrypoपूर्णांक is Mandatory.
 *
 * @remoteport_delete:  The LLDD initiates deletion of a remoteport via
 *       nvme_fc_deरेजिस्टर_remoteport(). However, the tearकरोwn is
 *       asynchronous. This routine is called upon the completion of the
 *       tearकरोwn to inक्रमm the LLDD that the remoteport has been deleted.
 *       Entrypoपूर्णांक is Mandatory.
 *
 * @create_queue:  Upon creating a host<->controller association, queues are
 *       created such that they can be affinitized to cpus/cores. This
 *       callback पूर्णांकo the LLDD to notअगरy that a controller queue is being
 *       created.  The LLDD may choose to allocate an associated hw queue
 *       or map it onto a shared hw queue. Upon वापस from the call, the
 *       LLDD specअगरies a handle that will be given back to it क्रम any
 *       command that is posted to the controller queue.  The handle can
 *       be used by the LLDD to map quickly to the proper hw queue क्रम
 *       command execution.  The mask of cpu's that will map to this queue
 *       at the block-level is also passed in. The LLDD should use the
 *       queue id and/or cpu masks to ensure proper affinitization of the
 *       controller queue to the hw queue.
 *       Entrypoपूर्णांक is Optional.
 *
 * @delete_queue:  This is the inverse of the crete_queue. During
 *       host<->controller association tearकरोwn, this routine is called
 *       when a controller queue is being terminated. Any association with
 *       a hw queue should be termined. If there is a unique hw queue, the
 *       hw queue should be torn करोwn.
 *       Entrypoपूर्णांक is Optional.
 *
 * @poll_queue:  Called to poll क्रम the completion of an io on a blk queue.
 *       Entrypoपूर्णांक is Optional.
 *
 * @ls_req:  Called to issue a FC-NVME FC-4 LS service request.
 *       The nvme_fc_ls_req काष्ठाure will fully describe the buffers क्रम
 *       the request payload and where to place the response payload. The
 *       LLDD is to allocate an exchange, issue the LS request, obtain the
 *       LS response, and call the "done" routine specअगरied in the request
 *       काष्ठाure (argument to करोne is the ls request काष्ठाure itself).
 *       Entrypoपूर्णांक is Mandatory.
 *
 * @fcp_io:  called to issue a FC-NVME I/O request.  The I/O may be क्रम
 *       an admin queue or an i/o queue.  The nvmefc_fcp_req काष्ठाure will
 *       fully describe the io: the buffer containing the FC-NVME CMD IU
 *       (which contains the SQE), the sg list क्रम the payload अगर applicable,
 *       and the buffer to place the FC-NVME RSP IU पूर्णांकo.  The LLDD will
 *       complete the i/o, indicating the amount of data transferred or
 *       any transport error, and call the "done" routine specअगरied in the
 *       request काष्ठाure (argument to करोne is the fcp request काष्ठाure
 *       itself).
 *       Entrypoपूर्णांक is Mandatory.
 *
 * @ls_पात: called to request the LLDD to पात the indicated ls request.
 *       The call may वापस beक्रमe the पात has completed. After पातing
 *       the request, the LLDD must still call the ls request करोne routine
 *       indicating an FC transport Aborted status.
 *       Entrypoपूर्णांक is Mandatory.
 *
 * @fcp_पात: called to request the LLDD to पात the indicated fcp request.
 *       The call may वापस beक्रमe the पात has completed. After पातing
 *       the request, the LLDD must still call the fcp request करोne routine
 *       indicating an FC transport Aborted status.
 *       Entrypoपूर्णांक is Mandatory.
 *
 * @xmt_ls_rsp:  Called to transmit the response to a FC-NVME FC-4 LS service.
 *       The nvmefc_ls_rsp काष्ठाure is the same LLDD-supplied exchange
 *       काष्ठाure specअगरied in the nvme_fc_rcv_ls_req() call made when
 *       the LS request was received. The काष्ठाure will fully describe
 *       the buffers क्रम the response payload and the dma address of the
 *       payload. The LLDD is to transmit the response (or वापस a
 *       non-zero त्रुटि_सं status), and upon completion of the transmit, call
 *       the "done" routine specअगरied in the nvmefc_ls_rsp काष्ठाure
 *       (argument to करोne is the address of the nvmefc_ls_rsp काष्ठाure
 *       itself). Upon the completion of the करोne routine, the LLDD shall
 *       consider the LS handling complete and the nvmefc_ls_rsp काष्ठाure
 *       may be मुक्तd/released.
 *       Entrypoपूर्णांक is mandatory अगर the LLDD calls the nvme_fc_rcv_ls_req()
 *       entrypoपूर्णांक.
 *
 * @max_hw_queues:  indicates the maximum number of hw queues the LLDD
 *       supports क्रम cpu affinitization.
 *       Value is Mandatory. Must be at least 1.
 *
 * @max_sgl_segments:  indicates the maximum number of sgl segments supported
 *       by the LLDD
 *       Value is Mandatory. Must be at least 1. Recommend at least 256.
 *
 * @max_dअगर_sgl_segments:  indicates the maximum number of sgl segments
 *       supported by the LLDD क्रम DIF operations.
 *       Value is Mandatory. Must be at least 1. Recommend at least 256.
 *
 * @dma_boundary:  indicates the dma address boundary where dma mappings
 *       will be split across.
 *       Value is Mandatory. Typical value is 0xFFFFFFFF to split across
 *       4Gig address boundarys
 *
 * @local_priv_sz: The LLDD sets this field to the amount of additional
 *       memory that it would like fc nvme layer to allocate on the LLDD's
 *       behalf whenever a localport is allocated.  The additional memory
 *       area solely क्रम the of the LLDD and its location is specअगरied by
 *       the localport->निजी poपूर्णांकer.
 *       Value is Mandatory. Allowed to be zero.
 *
 * @remote_priv_sz: The LLDD sets this field to the amount of additional
 *       memory that it would like fc nvme layer to allocate on the LLDD's
 *       behalf whenever a remoteport is allocated.  The additional memory
 *       area solely क्रम the of the LLDD and its location is specअगरied by
 *       the remoteport->निजी poपूर्णांकer.
 *       Value is Mandatory. Allowed to be zero.
 *
 * @lsrqst_priv_sz: The LLDD sets this field to the amount of additional
 *       memory that it would like fc nvme layer to allocate on the LLDD's
 *       behalf whenever a ls request काष्ठाure is allocated. The additional
 *       memory area is solely क्रम use by the LLDD and its location is
 *       specअगरied by the ls_request->निजी poपूर्णांकer.
 *       Value is Mandatory. Allowed to be zero.
 *
 * @fcprqst_priv_sz: The LLDD sets this field to the amount of additional
 *       memory that it would like fc nvme layer to allocate on the LLDD's
 *       behalf whenever a fcp request काष्ठाure is allocated. The additional
 *       memory area solely क्रम the of the LLDD and its location is
 *       specअगरied by the fcp_request->निजी poपूर्णांकer.
 *       Value is Mandatory. Allowed to be zero.
 */
काष्ठा nvme_fc_port_ढाँचा अणु
	/* initiator-based functions */
	व्योम	(*localport_delete)(काष्ठा nvme_fc_local_port *);
	व्योम	(*remoteport_delete)(काष्ठा nvme_fc_remote_port *);
	पूर्णांक	(*create_queue)(काष्ठा nvme_fc_local_port *,
				अचिन्हित पूर्णांक qidx, u16 qsize,
				व्योम **handle);
	व्योम	(*delete_queue)(काष्ठा nvme_fc_local_port *,
				अचिन्हित पूर्णांक qidx, व्योम *handle);
	पूर्णांक	(*ls_req)(काष्ठा nvme_fc_local_port *,
				काष्ठा nvme_fc_remote_port *,
				काष्ठा nvmefc_ls_req *);
	पूर्णांक	(*fcp_io)(काष्ठा nvme_fc_local_port *,
				काष्ठा nvme_fc_remote_port *,
				व्योम *hw_queue_handle,
				काष्ठा nvmefc_fcp_req *);
	व्योम	(*ls_पात)(काष्ठा nvme_fc_local_port *,
				काष्ठा nvme_fc_remote_port *,
				काष्ठा nvmefc_ls_req *);
	व्योम	(*fcp_पात)(काष्ठा nvme_fc_local_port *,
				काष्ठा nvme_fc_remote_port *,
				व्योम *hw_queue_handle,
				काष्ठा nvmefc_fcp_req *);
	पूर्णांक	(*xmt_ls_rsp)(काष्ठा nvme_fc_local_port *localport,
				काष्ठा nvme_fc_remote_port *rport,
				काष्ठा nvmefc_ls_rsp *ls_rsp);

	u32	max_hw_queues;
	u16	max_sgl_segments;
	u16	max_dअगर_sgl_segments;
	u64	dma_boundary;

	/* sizes of additional निजी data क्रम data काष्ठाures */
	u32	local_priv_sz;
	u32	remote_priv_sz;
	u32	lsrqst_priv_sz;
	u32	fcprqst_priv_sz;
पूर्ण;


/*
 * Initiator/Host functions
 */

पूर्णांक nvme_fc_रेजिस्टर_localport(काष्ठा nvme_fc_port_info *pinfo,
			काष्ठा nvme_fc_port_ढाँचा *ढाँचा,
			काष्ठा device *dev,
			काष्ठा nvme_fc_local_port **lport_p);

पूर्णांक nvme_fc_unरेजिस्टर_localport(काष्ठा nvme_fc_local_port *localport);

पूर्णांक nvme_fc_रेजिस्टर_remoteport(काष्ठा nvme_fc_local_port *localport,
			काष्ठा nvme_fc_port_info *pinfo,
			काष्ठा nvme_fc_remote_port **rport_p);

पूर्णांक nvme_fc_unरेजिस्टर_remoteport(काष्ठा nvme_fc_remote_port *remoteport);

व्योम nvme_fc_rescan_remoteport(काष्ठा nvme_fc_remote_port *remoteport);

पूर्णांक nvme_fc_set_remoteport_devloss(काष्ठा nvme_fc_remote_port *remoteport,
			u32 dev_loss_पंचांगo);

/*
 * Routine called to pass a NVME-FC LS request, received by the lldd,
 * to the nvme-fc transport.
 *
 * If the वापस value is zero: the LS was successfully accepted by the
 *   transport.
 * If the वापस value is non-zero: the transport has not accepted the
 *   LS. The lldd should ABTS-LS the LS.
 *
 * Note: अगर the LLDD receives and ABTS क्रम the LS prior to the transport
 * calling the ops->xmt_ls_rsp() routine to transmit a response, the LLDD
 * shall mark the LS as पातed, and when the xmt_ls_rsp() is called: the
 * response shall not be transmit and the काष्ठा nvmefc_ls_rsp() करोne
 * routine shall be called.  The LLDD may transmit the ABTS response as
 * soon as the LS was marked or can delay until the xmt_ls_rsp() call is
 * made.
 * Note: अगर an RCV LS was successfully posted to the transport and the
 * remoteport is then unरेजिस्टरed beक्रमe xmt_ls_rsp() was called क्रम
 * the lsrsp काष्ठाure, the transport will still call xmt_ls_rsp()
 * afterward to cleanup the outstanding lsrsp काष्ठाure. The LLDD should
 * noop the transmission of the rsp and call the lsrsp->करोne() routine
 * to allow the lsrsp काष्ठाure to be released.
 */
पूर्णांक nvme_fc_rcv_ls_req(काष्ठा nvme_fc_remote_port *remoteport,
			काष्ठा nvmefc_ls_rsp *lsrsp,
			व्योम *lsreqbuf, u32 lsreqbuf_len);



/*
 * ***************  LLDD FC-NVME Target/Subप्रणाली API ***************
 *
 *  For FC LLDD's that are the NVME Subप्रणाली role
 *
 * ******************************************************************
 */

/**
 * काष्ठा nvmet_fc_port_info - port-specअगरic ids and FC connection-specअगरic
 *                             data element used during NVME Subप्रणाली role
 *                             registrations
 *
 * Static fields describing the port being रेजिस्टरed:
 * @node_name: FC WWNN क्रम the port
 * @port_name: FC WWPN क्रम the port
 *
 * Initialization values क्रम dynamic port fields:
 * @port_id:      FC N_Port_ID currently asचिन्हित the port. Upper 8 bits must
 *                be set to 0.
 */
काष्ठा nvmet_fc_port_info अणु
	u64			node_name;
	u64			port_name;
	u32			port_id;
पूर्ण;


/* Operations that NVME-FC layer may request the LLDD to perक्रमm क्रम FCP */
क्रमागत अणु
	NVMET_FCOP_READDATA	= 1,	/* xmt data to initiator */
	NVMET_FCOP_WRITEDATA	= 2,	/* xmt data from initiator */
	NVMET_FCOP_READDATA_RSP	= 3,	/* xmt data to initiator and send
					 * rsp as well
					 */
	NVMET_FCOP_RSP		= 4,	/* send rsp frame */
पूर्ण;

/**
 * काष्ठा nvmefc_tgt_fcp_req - Structure used between LLDD and NVMET-FC
 *                            layer to represent the exchange context and
 *                            the specअगरic FC-NVME IU operation(s) to perक्रमm
 *                            क्रम a FC-NVME FCP IO.
 *
 * Structure used between LLDD and nvmet-fc layer to represent the exchange
 * context क्रम a FC-NVME FCP I/O operation (e.g. a nvme sqe, the sqe-related
 * memory transfers, and its assocated cqe transfer).
 *
 * The काष्ठाure is allocated by the LLDD whenever a FCP CMD IU is received
 * from the FC link. The address of the काष्ठाure is passed to the nvmet-fc
 * layer via the nvmet_fc_rcv_fcp_req() call. The address of the काष्ठाure
 * will be passed back to the LLDD क्रम the data operations and transmit of
 * the response. The LLDD is to use the address to map back to the LLDD
 * exchange काष्ठाure which मुख्यtains inक्रमmation such as the targetport
 * the FCP I/O was received on, the remote FC NVME initiator that sent the
 * FCP I/O, and any FC exchange context.  Upon completion of the FCP target
 * operation, the address of the काष्ठाure will be passed back to the FCP
 * op करोne() routine, allowing the nvmet-fc layer to release dma resources.
 * Upon completion of the करोne() routine क्रम either RSP or ABORT ops, no
 * further access will be made by the nvmet-fc layer and the LLDD can
 * de-allocate the काष्ठाure.
 *
 * Field initialization:
 *   At the समय of the nvmet_fc_rcv_fcp_req() call, there is no content that
 *     is valid in the काष्ठाure.
 *
 *   When the काष्ठाure is used क्रम an FCP target operation, the nvmet-fc
 *     layer will fully set the fields in order to specअगरy the scattergather
 *     list, the transfer length, as well as the करोne routine to be called
 *     upon compeletion of the operation.  The nvmet-fc layer will also set a
 *     निजी poपूर्णांकer क्रम its own use in the करोne routine.
 *
 * Values set by the NVMET-FC layer prior to calling the LLDD fcp_op
 * entrypoपूर्णांक.
 * @op:       Indicates the FCP IU operation to perक्रमm (see NVMET_FCOP_xxx)
 * @hwqid:    Specअगरies the hw queue index (0..N-1, where N is the
 *            max_hw_queues value from the LLD's nvmet_fc_target_ढाँचा)
 *            that the operation is to use.
 * @offset:   Indicates the DATA_OUT/DATA_IN payload offset to be tranferred.
 *            Field is only valid on WRITEDATA, READDATA, or READDATA_RSP ops.
 * @समयout:  amount of समय, in seconds, to रुको क्रम a response from the NVME
 *            host. A value of 0 is an infinite रुको.
 *            Valid only क्रम the following ops:
 *              WRITEDATA: caps the रुको क्रम data reception
 *              READDATA_RSP & RSP: caps रुको क्रम FCP_CONF reception (अगर used)
 * @transfer_length: the length, in bytes, of the DATA_OUT or DATA_IN payload
 *            that is to be transferred.
 *            Valid only क्रम the WRITEDATA, READDATA, or READDATA_RSP ops.
 * @ba_rjt:   Contains the BA_RJT payload that is to be transferred.
 *            Valid only क्रम the NVMET_FCOP_BA_RJT op.
 * @sg:       Scatter/gather list क्रम the DATA_OUT/DATA_IN payload data.
 *            Valid only क्रम the WRITEDATA, READDATA, or READDATA_RSP ops.
 * @sg_cnt:   Number of valid entries in the scatter/gather list.
 *            Valid only क्रम the WRITEDATA, READDATA, or READDATA_RSP ops.
 * @rspaddr:  poपूर्णांकer to the FCP RSP IU buffer to be transmit
 *            Used by RSP and READDATA_RSP ops
 * @rspdma:   PCI DMA address of the FCP RSP IU buffer
 *            Used by RSP and READDATA_RSP ops
 * @rsplen:   Length, in bytes, of the FCP RSP IU buffer
 *            Used by RSP and READDATA_RSP ops
 * @करोne:     The callback routine the LLDD is to invoke upon completion of
 *            the operation. req argument is the poपूर्णांकer to the original
 *            FCP subप्रणाली op request.
 * @nvmet_fc_निजी:  poपूर्णांकer to an पूर्णांकernal NVMET-FC layer काष्ठाure used
 *            as part of the NVMET-FC processing. The LLDD is not to
 *            reference this field.
 *
 * Values set by the LLDD indicating completion status of the FCP operation.
 * Must be set prior to calling the करोne() callback.
 * @transferred_length: amount of DATA_OUT payload data received by a
 *            WRITEDATA operation. If not a WRITEDATA operation, value must
 *            be set to 0. Should equal transfer_length on success.
 * @fcp_error: status of the FCP operation. Must be 0 on success; on failure
 *            must be a NVME_SC_FC_xxxx value.
 */
काष्ठा nvmefc_tgt_fcp_req अणु
	u8			op;
	u16			hwqid;
	u32			offset;
	u32			समयout;
	u32			transfer_length;
	काष्ठा fc_ba_rjt	ba_rjt;
	काष्ठा scatterlist	*sg;
	पूर्णांक			sg_cnt;
	व्योम			*rspaddr;
	dma_addr_t		rspdma;
	u16			rsplen;

	व्योम (*करोne)(काष्ठा nvmefc_tgt_fcp_req *);

	व्योम *nvmet_fc_निजी;		/* LLDD is not to access !! */

	u32			transferred_length;
	पूर्णांक			fcp_error;
पूर्ण;


/* Target Features (Bit fields) LLDD supports */
क्रमागत अणु
	NVMET_FCTGTFEAT_READDATA_RSP = (1 << 0),
		/* Bit 0: supports the NVMET_FCPOP_READDATA_RSP op, which
		 * sends (the last) Read Data sequence followed by the RSP
		 * sequence in one LLDD operation. Errors during Data
		 * sequence transmit must not allow RSP sequence to be sent.
		 */
पूर्ण;


/**
 * काष्ठा nvmet_fc_target_port - काष्ठाure used between NVME-FC transport and
 *                 a LLDD to reference a local NVME subप्रणाली port.
 *                 Allocated/created by the nvme_fc_रेजिस्टर_targetport()
 *                 transport पूर्णांकerface.
 *
 * Fields with अटल values क्रम the port. Initialized by the
 * port_info काष्ठा supplied to the registration call.
 * @port_num:  NVME-FC transport subsytem port number
 * @node_name: FC WWNN क्रम the port
 * @port_name: FC WWPN क्रम the port
 * @निजी:   poपूर्णांकer to memory allocated aदीर्घside the local port
 *             काष्ठाure that is specअगरically क्रम the LLDD to use.
 *             The length of the buffer corresponds to the target_priv_sz
 *             value specअगरied in the nvme_fc_target_ढाँचा supplied by
 *             the LLDD.
 *
 * Fields with dynamic values. Values may change base on link state. LLDD
 * may reference fields directly to change them. Initialized by the
 * port_info काष्ठा supplied to the registration call.
 * @port_id:      FC N_Port_ID currently asचिन्हित the port. Upper 8 bits must
 *                be set to 0.
 * @port_state:   Operational state of the port.
 */
काष्ठा nvmet_fc_target_port अणु
	/* अटल/पढ़ो-only fields */
	u32 port_num;
	u64 node_name;
	u64 port_name;

	व्योम *निजी;

	/* dynamic fields */
	u32 port_id;
	क्रमागत nvme_fc_obj_state port_state;
पूर्ण __aligned(माप(u64));	/* alignment क्रम other things alloc'd with */


/**
 * काष्ठा nvmet_fc_target_ढाँचा - काष्ठाure containing अटल entrypoपूर्णांकs
 *                 and operational parameters क्रम an LLDD that supports NVME
 *                 subप्रणाली behavior. Passed by reference in port
 *                 registrations. NVME-FC transport remembers ढाँचा
 *                 reference and may access it during runसमय operation.
 *
 * Subप्रणाली/Target Transport Entrypoपूर्णांकs/Parameters:
 *
 * @targetport_delete:  The LLDD initiates deletion of a targetport via
 *       nvmet_fc_unरेजिस्टर_targetport(). However, the tearकरोwn is
 *       asynchronous. This routine is called upon the completion of the
 *       tearकरोwn to inक्रमm the LLDD that the targetport has been deleted.
 *       Entrypoपूर्णांक is Mandatory.
 *
 * @xmt_ls_rsp:  Called to transmit the response to a FC-NVME FC-4 LS service.
 *       The nvmefc_ls_rsp काष्ठाure is the same LLDD-supplied exchange
 *       काष्ठाure specअगरied in the nvmet_fc_rcv_ls_req() call made when
 *       the LS request was received. The काष्ठाure will fully describe
 *       the buffers क्रम the response payload and the dma address of the
 *       payload. The LLDD is to transmit the response (or वापस a
 *       non-zero त्रुटि_सं status), and upon completion of the transmit, call
 *       the "done" routine specअगरied in the nvmefc_ls_rsp काष्ठाure
 *       (argument to करोne is the address of the nvmefc_ls_rsp काष्ठाure
 *       itself). Upon the completion of the करोne() routine, the LLDD shall
 *       consider the LS handling complete and the nvmefc_ls_rsp काष्ठाure
 *       may be मुक्तd/released.
 *       The transport will always call the xmt_ls_rsp() routine क्रम any
 *       LS received.
 *       Entrypoपूर्णांक is Mandatory.
 *
 * @fcp_op:  Called to perक्रमm a data transfer or transmit a response.
 *       The nvmefc_tgt_fcp_req काष्ठाure is the same LLDD-supplied
 *       exchange काष्ठाure specअगरied in the nvmet_fc_rcv_fcp_req() call
 *       made when the FCP CMD IU was received. The op field in the
 *       काष्ठाure shall indicate the operation क्रम the LLDD to perक्रमm
 *       relative to the io.
 *         NVMET_FCOP_READDATA operation: the LLDD is to send the
 *           payload data (described by sglist) to the host in 1 or
 *           more FC sequences (preferrably 1).  Note: the fc-nvme layer
 *           may call the READDATA operation multiple बार क्रम दीर्घer
 *           payloads.
 *         NVMET_FCOP_WRITEDATA operation: the LLDD is to receive the
 *           payload data (described by sglist) from the host via 1 or
 *           more FC sequences (preferrably 1). The LLDD is to generate
 *           the XFER_RDY IU(s) corresponding to the data being requested.
 *           Note: the FC-NVME layer may call the WRITEDATA operation
 *           multiple बार क्रम दीर्घer payloads.
 *         NVMET_FCOP_READDATA_RSP operation: the LLDD is to send the
 *           payload data (described by sglist) to the host in 1 or
 *           more FC sequences (preferrably 1). If an error occurs during
 *           payload data transmission, the LLDD is to set the
 *           nvmefc_tgt_fcp_req fcp_error and transferred_length field, then
 *           consider the operation complete. On error, the LLDD is to not
 *           transmit the FCP_RSP iu. If all payload data is transferred
 *           successfully, the LLDD is to update the nvmefc_tgt_fcp_req
 *           transferred_length field and may subsequently transmit the
 *           FCP_RSP iu payload (described by rspbuf, rspdma, rsplen).
 *           If FCP_CONF is supported, the LLDD is to aरुको FCP_CONF
 *           reception to confirm the RSP reception by the host. The LLDD
 *           may retramsit the FCP_RSP iu अगर necessary per FC-NVME. Upon
 *           transmission of the FCP_RSP iu अगर FCP_CONF is not supported,
 *           or upon success/failure of FCP_CONF अगर it is supported, the
 *           LLDD is to set the nvmefc_tgt_fcp_req fcp_error field and
 *           consider the operation complete.
 *         NVMET_FCOP_RSP: the LLDD is to transmit the FCP_RSP iu payload
 *           (described by rspbuf, rspdma, rsplen). If FCP_CONF is
 *           supported, the LLDD is to aरुको FCP_CONF reception to confirm
 *           the RSP reception by the host. The LLDD may retramsit the
 *           FCP_RSP iu अगर FCP_CONF is not received per FC-NVME. Upon
 *           transmission of the FCP_RSP iu अगर FCP_CONF is not supported,
 *           or upon success/failure of FCP_CONF अगर it is supported, the
 *           LLDD is to set the nvmefc_tgt_fcp_req fcp_error field and
 *           consider the operation complete.
 *       Upon completing the indicated operation, the LLDD is to set the
 *       status fields क्रम the operation (tranferred_length and fcp_error
 *       status) in the request, then call the "done" routine
 *       indicated in the fcp request. After the operation completes,
 *       regardless of whether the FCP_RSP iu was successfully transmit,
 *       the LLDD-supplied exchange काष्ठाure must reमुख्य valid until the
 *       transport calls the fcp_req_release() callback to वापस ownership
 *       of the exchange काष्ठाure back to the LLDD so that it may be used
 *       क्रम another fcp command.
 *       Note: when calling the करोne routine क्रम READDATA or WRITEDATA
 *       operations, the fc-nvme layer may immediate convert, in the same
 *       thपढ़ो and beक्रमe वापसing to the LLDD, the fcp operation to
 *       the next operation क्रम the fcp io and call the LLDDs fcp_op
 *       call again. If fields in the fcp request are to be accessed post
 *       the करोne call, the LLDD should save their values prior to calling
 *       the करोne routine, and inspect the save values after the करोne
 *       routine.
 *       Returns 0 on success, -<त्रुटि_सं> on failure (Ex: -EIO)
 *       Entrypoपूर्णांक is Mandatory.
 *
 * @fcp_पात:  Called by the transport to पात an active command.
 *       The command may be in-between operations (nothing active in LLDD)
 *       or may have an active WRITEDATA operation pending. The LLDD is to
 *       initiate the ABTS process क्रम the command and वापस from the
 *       callback. The ABTS करोes not need to be complete on the command.
 *       The fcp_पात callback inherently cannot fail. After the
 *       fcp_पात() callback completes, the transport will रुको क्रम any
 *       outstanding operation (अगर there was one) to complete, then will
 *       call the fcp_req_release() callback to वापस the command's
 *       exchange context back to the LLDD.
 *       Entrypoपूर्णांक is Mandatory.
 *
 * @fcp_req_release:  Called by the transport to वापस a nvmefc_tgt_fcp_req
 *       to the LLDD after all operations on the fcp operation are complete.
 *       This may be due to the command completing or upon completion of
 *       पात cleanup.
 *       Entrypoपूर्णांक is Mandatory.
 *
 * @defer_rcv:  Called by the transport to संकेत the LLLD that it has
 *       begun processing of a previously received NVME CMD IU. The LLDD
 *       is now मुक्त to re-use the rcv buffer associated with the
 *       nvmefc_tgt_fcp_req.
 *       Entrypoपूर्णांक is Optional.
 *
 * @discovery_event:  Called by the transport to generate an RSCN
 *       change notअगरications to NVME initiators. The RSCN notअगरications
 *       should cause the initiator to rescan the discovery controller
 *       on the targetport.
 *
 * @ls_req:  Called to issue a FC-NVME FC-4 LS service request.
 *       The nvme_fc_ls_req काष्ठाure will fully describe the buffers क्रम
 *       the request payload and where to place the response payload.
 *       The targetport that is to issue the LS request is identअगरied by
 *       the targetport argument.  The remote port that is to receive the
 *       LS request is identअगरied by the hosthandle argument. The nvmet-fc
 *       transport is only allowed to issue FC-NVME LS's on behalf of an
 *       association that was created prior by a Create Association LS.
 *       The hosthandle will originate from the LLDD in the काष्ठा
 *       nvmefc_ls_rsp काष्ठाure क्रम the Create Association LS that
 *       was delivered to the transport. The transport will save the
 *       hosthandle as an attribute of the association.  If the LLDD
 *       loses connectivity with the remote port, it must call the
 *       nvmet_fc_invalidate_host() routine to हटाओ any references to
 *       the remote port in the transport.
 *       The LLDD is to allocate an exchange, issue the LS request, obtain
 *       the LS response, and call the "done" routine specअगरied in the
 *       request काष्ठाure (argument to करोne is the ls request काष्ठाure
 *       itself).
 *       Entrypoपूर्णांक is Optional - but highly recommended.
 *
 * @ls_पात: called to request the LLDD to पात the indicated ls request.
 *       The call may वापस beक्रमe the पात has completed. After पातing
 *       the request, the LLDD must still call the ls request करोne routine
 *       indicating an FC transport Aborted status.
 *       Entrypoपूर्णांक is Mandatory अगर the ls_req entry poपूर्णांक is specअगरied.
 *
 * @host_release: called to inक्रमm the LLDD that the request to invalidate
 *       the host port indicated by the hosthandle has been fully completed.
 *       No associations exist with the host port and there will be no
 *       further references to hosthandle.
 *       Entrypoपूर्णांक is Mandatory अगर the lldd calls nvmet_fc_invalidate_host().
 *
 * @max_hw_queues:  indicates the maximum number of hw queues the LLDD
 *       supports क्रम cpu affinitization.
 *       Value is Mandatory. Must be at least 1.
 *
 * @max_sgl_segments:  indicates the maximum number of sgl segments supported
 *       by the LLDD
 *       Value is Mandatory. Must be at least 1. Recommend at least 256.
 *
 * @max_dअगर_sgl_segments:  indicates the maximum number of sgl segments
 *       supported by the LLDD क्रम DIF operations.
 *       Value is Mandatory. Must be at least 1. Recommend at least 256.
 *
 * @dma_boundary:  indicates the dma address boundary where dma mappings
 *       will be split across.
 *       Value is Mandatory. Typical value is 0xFFFFFFFF to split across
 *       4Gig address boundarys
 *
 * @target_features: The LLDD sets bits in this field to correspond to
 *       optional features that are supported by the LLDD.
 *       Refer to the NVMET_FCTGTFEAT_xxx values.
 *       Value is Mandatory. Allowed to be zero.
 *
 * @target_priv_sz: The LLDD sets this field to the amount of additional
 *       memory that it would like fc nvme layer to allocate on the LLDD's
 *       behalf whenever a targetport is allocated.  The additional memory
 *       area solely क्रम the of the LLDD and its location is specअगरied by
 *       the targetport->निजी poपूर्णांकer.
 *       Value is Mandatory. Allowed to be zero.
 *
 * @lsrqst_priv_sz: The LLDD sets this field to the amount of additional
 *       memory that it would like nvmet-fc layer to allocate on the LLDD's
 *       behalf whenever a ls request काष्ठाure is allocated. The additional
 *       memory area is solely क्रम use by the LLDD and its location is
 *       specअगरied by the ls_request->निजी poपूर्णांकer.
 *       Value is Mandatory. Allowed to be zero.
 *
 */
काष्ठा nvmet_fc_target_ढाँचा अणु
	व्योम (*targetport_delete)(काष्ठा nvmet_fc_target_port *tgtport);
	पूर्णांक (*xmt_ls_rsp)(काष्ठा nvmet_fc_target_port *tgtport,
				काष्ठा nvmefc_ls_rsp *ls_rsp);
	पूर्णांक (*fcp_op)(काष्ठा nvmet_fc_target_port *tgtport,
				काष्ठा nvmefc_tgt_fcp_req *fcpreq);
	व्योम (*fcp_पात)(काष्ठा nvmet_fc_target_port *tgtport,
				काष्ठा nvmefc_tgt_fcp_req *fcpreq);
	व्योम (*fcp_req_release)(काष्ठा nvmet_fc_target_port *tgtport,
				काष्ठा nvmefc_tgt_fcp_req *fcpreq);
	व्योम (*defer_rcv)(काष्ठा nvmet_fc_target_port *tgtport,
				काष्ठा nvmefc_tgt_fcp_req *fcpreq);
	व्योम (*discovery_event)(काष्ठा nvmet_fc_target_port *tgtport);
	पूर्णांक  (*ls_req)(काष्ठा nvmet_fc_target_port *targetport,
				व्योम *hosthandle, काष्ठा nvmefc_ls_req *lsreq);
	व्योम (*ls_पात)(काष्ठा nvmet_fc_target_port *targetport,
				व्योम *hosthandle, काष्ठा nvmefc_ls_req *lsreq);
	व्योम (*host_release)(व्योम *hosthandle);

	u32	max_hw_queues;
	u16	max_sgl_segments;
	u16	max_dअगर_sgl_segments;
	u64	dma_boundary;

	u32	target_features;

	/* sizes of additional निजी data क्रम data काष्ठाures */
	u32	target_priv_sz;
	u32	lsrqst_priv_sz;
पूर्ण;


पूर्णांक nvmet_fc_रेजिस्टर_targetport(काष्ठा nvmet_fc_port_info *portinfo,
			काष्ठा nvmet_fc_target_ढाँचा *ढाँचा,
			काष्ठा device *dev,
			काष्ठा nvmet_fc_target_port **tgtport_p);

पूर्णांक nvmet_fc_unरेजिस्टर_targetport(काष्ठा nvmet_fc_target_port *tgtport);

/*
 * Routine called to pass a NVME-FC LS request, received by the lldd,
 * to the nvmet-fc transport.
 *
 * If the वापस value is zero: the LS was successfully accepted by the
 *   transport.
 * If the वापस value is non-zero: the transport has not accepted the
 *   LS. The lldd should ABTS-LS the LS.
 *
 * Note: अगर the LLDD receives and ABTS क्रम the LS prior to the transport
 * calling the ops->xmt_ls_rsp() routine to transmit a response, the LLDD
 * shall mark the LS as पातed, and when the xmt_ls_rsp() is called: the
 * response shall not be transmit and the काष्ठा nvmefc_ls_rsp() करोne
 * routine shall be called.  The LLDD may transmit the ABTS response as
 * soon as the LS was marked or can delay until the xmt_ls_rsp() call is
 * made.
 * Note: अगर an RCV LS was successfully posted to the transport and the
 * targetport is then unरेजिस्टरed beक्रमe xmt_ls_rsp() was called क्रम
 * the lsrsp काष्ठाure, the transport will still call xmt_ls_rsp()
 * afterward to cleanup the outstanding lsrsp काष्ठाure. The LLDD should
 * noop the transmission of the rsp and call the lsrsp->करोne() routine
 * to allow the lsrsp काष्ठाure to be released.
 */
पूर्णांक nvmet_fc_rcv_ls_req(काष्ठा nvmet_fc_target_port *tgtport,
			व्योम *hosthandle,
			काष्ठा nvmefc_ls_rsp *rsp,
			व्योम *lsreqbuf, u32 lsreqbuf_len);

/*
 * Routine called by the LLDD whenever it has a logout or loss of
 * connectivity to a NVME-FC host port which there had been active
 * NVMe controllers क्रम.  The host port is indicated by the
 * hosthandle. The hosthandle is given to the nvmet-fc transport
 * when a NVME LS was received, typically to create a new association.
 * The nvmet-fc transport will cache the hostport value with the
 * association क्रम use in LS requests क्रम the association.
 * When the LLDD calls this routine, the nvmet-fc transport will
 * immediately terminate all associations that were created with
 * the hosthandle host port.
 * The LLDD, after calling this routine and having control वापसed,
 * must assume the transport may subsequently utilize hosthandle as
 * part of sending LS's to terminate the association.  The LLDD
 * should reject the LS's अगर they are attempted.
 * Once the last association has terminated क्रम the hosthandle host
 * port, the nvmet-fc transport will call the ops->host_release()
 * callback. As of the callback, the nvmet-fc transport will no
 * दीर्घer reference hosthandle.
 */
व्योम nvmet_fc_invalidate_host(काष्ठा nvmet_fc_target_port *tgtport,
			व्योम *hosthandle);

/*
 * If nvmet_fc_rcv_fcp_req वापसs non-zero, the transport has not accepted
 * the FCP cmd. The lldd should ABTS-LS the cmd.
 */
पूर्णांक nvmet_fc_rcv_fcp_req(काष्ठा nvmet_fc_target_port *tgtport,
			काष्ठा nvmefc_tgt_fcp_req *fcpreq,
			व्योम *cmdiubuf, u32 cmdiubuf_len);

व्योम nvmet_fc_rcv_fcp_पात(काष्ठा nvmet_fc_target_port *tgtport,
			काष्ठा nvmefc_tgt_fcp_req *fcpreq);

#पूर्ण_अगर /* _NVME_FC_DRIVER_H */
