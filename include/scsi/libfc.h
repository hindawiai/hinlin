<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2007 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#अगर_अघोषित _LIBFC_H_
#घोषणा _LIBFC_H_

#समावेश <linux/समयr.h>
#समावेश <linux/अगर.h>
#समावेश <linux/percpu.h>
#समावेश <linux/refcount.h>

#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_fc.h>
#समावेश <scsi/scsi_bsg_fc.h>

#समावेश <scsi/fc/fc_fcp.h>
#समावेश <scsi/fc/fc_ns.h>
#समावेश <scsi/fc/fc_ms.h>
#समावेश <scsi/fc/fc_els.h>
#समावेश <scsi/fc/fc_gs.h>

#समावेश <scsi/fc_frame.h>

#घोषणा	FC_FC4_PROV_SIZE	(FC_TYPE_FCP + 1)	/* size of tables */

/*
 * libfc error codes
 */
#घोषणा	FC_NO_ERR	0	/* no error */
#घोषणा	FC_EX_TIMEOUT	1	/* Exchange समयout */
#घोषणा	FC_EX_CLOSED	2	/* Exchange बंदd */
#घोषणा FC_EX_ALLOC_ERR	3	/* Exchange allocation failed */
#घोषणा FC_EX_XMIT_ERR	4	/* Exchange transmit failed */
#घोषणा FC_EX_ELS_RJT	5	/* ELS rejected */
#घोषणा FC_EX_INV_LOGIN	6	/* Login not completed */
#घोषणा FC_EX_SEQ_ERR	6	/* Exchange sequence error */

/**
 * क्रमागत fc_lport_state - Local port states
 * @LPORT_ST_DISABLED: Disabled
 * @LPORT_ST_FLOGI:    Fabric login (FLOGI) sent
 * @LPORT_ST_DNS:      Waiting क्रम name server remote port to become पढ़ोy
 * @LPORT_ST_RPN_ID:   Register port name by ID (RPN_ID) sent
 * @LPORT_ST_RFT_ID:   Register Fibre Channel types by ID (RFT_ID) sent
 * @LPORT_ST_RFF_ID:   Register FC-4 Features by ID (RFF_ID) sent
 * @LPORT_ST_FDMI:     Waiting क्रम mgmt server rport to become पढ़ोy
 * @LPORT_ST_RHBA:
 * @LPORT_ST_SCR:      State Change Register (SCR) sent
 * @LPORT_ST_READY:    Ready क्रम use
 * @LPORT_ST_LOGO:     Local port logout (LOGO) sent
 * @LPORT_ST_RESET:    Local port reset
 */
क्रमागत fc_lport_state अणु
	LPORT_ST_DISABLED = 0,
	LPORT_ST_FLOGI,
	LPORT_ST_DNS,
	LPORT_ST_RNN_ID,
	LPORT_ST_RSNN_NN,
	LPORT_ST_RSPN_ID,
	LPORT_ST_RFT_ID,
	LPORT_ST_RFF_ID,
	LPORT_ST_FDMI,
	LPORT_ST_RHBA,
	LPORT_ST_RPA,
	LPORT_ST_DHBA,
	LPORT_ST_DPRT,
	LPORT_ST_SCR,
	LPORT_ST_READY,
	LPORT_ST_LOGO,
	LPORT_ST_RESET
पूर्ण;

क्रमागत fc_disc_event अणु
	DISC_EV_NONE = 0,
	DISC_EV_SUCCESS,
	DISC_EV_FAILED
पूर्ण;

/**
 * क्रमागत fc_rport_state - Remote port states
 * @RPORT_ST_INIT:    Initialized
 * @RPORT_ST_FLOGI:   Waiting क्रम FLOGI completion क्रम poपूर्णांक-to-multipoपूर्णांक
 * @RPORT_ST_PLOGI_WAIT:   Waiting क्रम peer to login क्रम poपूर्णांक-to-multipoपूर्णांक
 * @RPORT_ST_PLOGI:   Waiting क्रम PLOGI completion
 * @RPORT_ST_PRLI:    Waiting क्रम PRLI completion
 * @RPORT_ST_RTV:     Waiting क्रम RTV completion
 * @RPORT_ST_READY:   Ready क्रम use
 * @RPORT_ST_ADISC:   Discover Address sent
 * @RPORT_ST_DELETE:  Remote port being deleted
*/
क्रमागत fc_rport_state अणु
	RPORT_ST_INIT,
	RPORT_ST_FLOGI,
	RPORT_ST_PLOGI_WAIT,
	RPORT_ST_PLOGI,
	RPORT_ST_PRLI,
	RPORT_ST_RTV,
	RPORT_ST_READY,
	RPORT_ST_ADISC,
	RPORT_ST_DELETE,
पूर्ण;

/**
 * काष्ठा fc_disc_port - temporary discovery port to hold rport identअगरiers
 * @lp:         Fibre Channel host port instance
 * @peers:      Node क्रम list management during discovery and RSCN processing
 * @rport_work: Work काष्ठा क्रम starting the rport state machine
 * @port_id:    Port ID of the discovered port
 */
काष्ठा fc_disc_port अणु
	काष्ठा fc_lport    *lp;
	काष्ठा list_head   peers;
	काष्ठा work_काष्ठा rport_work;
	u32		   port_id;
पूर्ण;

/**
 * क्रमागत fc_rport_event - Remote port events
 * @RPORT_EV_NONE:   No event
 * @RPORT_EV_READY:  Remote port is पढ़ोy क्रम use
 * @RPORT_EV_FAILED: State machine failed, remote port is not पढ़ोy
 * @RPORT_EV_STOP:   Remote port has been stopped
 * @RPORT_EV_LOGO:   Remote port logout (LOGO) sent
 */
क्रमागत fc_rport_event अणु
	RPORT_EV_NONE = 0,
	RPORT_EV_READY,
	RPORT_EV_FAILED,
	RPORT_EV_STOP,
	RPORT_EV_LOGO
पूर्ण;

काष्ठा fc_rport_priv;

/**
 * काष्ठा fc_rport_operations - Operations क्रम a remote port
 * @event_callback: Function to be called क्रम remote port events
 */
काष्ठा fc_rport_operations अणु
	व्योम (*event_callback)(काष्ठा fc_lport *, काष्ठा fc_rport_priv *,
			       क्रमागत fc_rport_event);
पूर्ण;

/**
 * काष्ठा fc_rport_libfc_priv - libfc पूर्णांकernal inक्रमmation about a remote port
 * @local_port: The associated local port
 * @rp_state:   Indicates READY क्रम I/O or DELETE when blocked
 * @flags:      REC and RETRY supported flags
 * @e_d_tov:    Error detect समयout value (in msec)
 * @r_a_tov:    Resource allocation समयout value (in msec)
 */
काष्ठा fc_rport_libfc_priv अणु
	काष्ठा fc_lport		   *local_port;
	क्रमागत fc_rport_state	   rp_state;
	u16			   flags;
	#घोषणा FC_RP_FLAGS_REC_SUPPORTED	(1 << 0)
	#घोषणा FC_RP_FLAGS_RETRY		(1 << 1)
	#घोषणा FC_RP_STARTED			(1 << 2)
	#घोषणा FC_RP_FLAGS_CONF_REQ		(1 << 3)
	अचिन्हित पूर्णांक		   e_d_tov;
	अचिन्हित पूर्णांक		   r_a_tov;
पूर्ण;

/**
 * काष्ठा fc_rport_priv - libfc remote port and discovery info
 * @local_port:     The associated local port
 * @rport:          The FC transport remote port
 * @kref:           Reference counter
 * @rp_state:       Enumeration that tracks progress of PLOGI, PRLI,
 *                  and RTV exchanges
 * @ids:            The remote port identअगरiers and roles
 * @flags:          STARTED, REC and RETRY_SUPPORTED flags
 * @max_seq:        Maximum number of concurrent sequences
 * @disc_id:        The discovery identअगरier
 * @maxframe_size:  The maximum frame size
 * @retries:        The retry count क्रम the current state
 * @major_retries:  The retry count क्रम the entire PLOGI/PRLI state machine
 * @e_d_tov:        Error detect समयout value (in msec)
 * @r_a_tov:        Resource allocation समयout value (in msec)
 * @rp_mutex:       The mutex that protects the remote port
 * @retry_work:     Handle क्रम retries
 * @event_callback: Callback when READY, FAILED or LOGO states complete
 * @prli_count:     Count of खोलो PRLI sessions in providers
 * @rcu:	    Structure used क्रम मुक्तing in an RCU-safe manner
 */
काष्ठा fc_rport_priv अणु
	काष्ठा fc_lport		    *local_port;
	काष्ठा fc_rport		    *rport;
	काष्ठा kref		    kref;
	क्रमागत fc_rport_state	    rp_state;
	काष्ठा fc_rport_identअगरiers ids;
	u16			    flags;
	u16			    max_seq;
	u16			    disc_id;
	u16			    maxframe_size;
	अचिन्हित पूर्णांक		    retries;
	अचिन्हित पूर्णांक		    major_retries;
	अचिन्हित पूर्णांक		    e_d_tov;
	अचिन्हित पूर्णांक		    r_a_tov;
	काष्ठा mutex		    rp_mutex;
	काष्ठा delayed_work	    retry_work;
	क्रमागत fc_rport_event	    event;
	काष्ठा fc_rport_operations  *ops;
	काष्ठा list_head	    peers;
	काष्ठा work_काष्ठा	    event_work;
	u32			    supported_classes;
	u16			    prli_count;
	काष्ठा rcu_head		    rcu;
	u16			    sp_features;
	u8			    spp_type;
	व्योम			    (*lld_event_callback)(काष्ठा fc_lport *,
						      काष्ठा fc_rport_priv *,
						      क्रमागत fc_rport_event);
पूर्ण;

/**
 * काष्ठा fc_stats - fc stats काष्ठाure
 * @SecondsSinceLastReset: Seconds since the last reset
 * @TxFrames:              Number of transmitted frames
 * @TxWords:               Number of transmitted words
 * @RxFrames:              Number of received frames
 * @RxWords:               Number of received words
 * @ErrorFrames:           Number of received error frames
 * @DumpedFrames:          Number of dumped frames
 * @FcpPktAllocFails:      Number of fcp packet allocation failures
 * @FcpPktAborts:          Number of fcp packet पातs
 * @FcpFrameAllocFails:    Number of fcp frame allocation failures
 * @LinkFailureCount:      Number of link failures
 * @LossOfSignalCount:     Number क्रम संकेत losses
 * @InvalidTxWordCount:    Number of invalid transmitted words
 * @InvalidCRCCount:       Number of invalid CRCs
 * @InputRequests:         Number of input requests
 * @OutputRequests:        Number of output requests
 * @ControlRequests:       Number of control requests
 * @InputBytes:            Number of received bytes
 * @OutputBytes:           Number of transmitted bytes
 * @VLinkFailureCount:     Number of भव link failures
 * @MissDiscAdvCount:      Number of missing FIP discovery advertisement
 */
काष्ठा fc_stats अणु
	u64		SecondsSinceLastReset;
	u64		TxFrames;
	u64		TxWords;
	u64		RxFrames;
	u64		RxWords;
	u64		ErrorFrames;
	u64		DumpedFrames;
	u64		FcpPktAllocFails;
	u64		FcpPktAborts;
	u64		FcpFrameAllocFails;
	u64		LinkFailureCount;
	u64		LossOfSignalCount;
	u64		InvalidTxWordCount;
	u64		InvalidCRCCount;
	u64		InputRequests;
	u64		OutputRequests;
	u64		ControlRequests;
	u64		InputBytes;
	u64		OutputBytes;
	u64		VLinkFailureCount;
	u64		MissDiscAdvCount;
पूर्ण;

/**
 * काष्ठा fc_seq_els_data - ELS data used क्रम passing ELS specअगरic responses
 * @reason: The reason क्रम rejection
 * @explan: The explanation of the rejection
 *
 * Mainly used by the exchange manager layer.
 */
काष्ठा fc_seq_els_data अणु
	क्रमागत fc_els_rjt_reason reason;
	क्रमागत fc_els_rjt_explan explan;
पूर्ण;

/**
 * काष्ठा fc_fcp_pkt - FCP request काष्ठाure (one क्रम each scsi_cmnd request)
 * @lp:              The associated local port
 * @state:           The state of the I/O
 * @ref_cnt:         Reference count
 * @scsi_pkt_lock:   Lock to protect the SCSI packet (must be taken beक्रमe the
 *                   host_lock अगर both are to be held at the same समय)
 * @cmd:             The SCSI command (set and clear with the host_lock held)
 * @list:            Tracks queued commands (accessed with the host_lock held)
 * @समयr:           The command समयr
 * @पंचांग_करोne:         Completion indicator
 * @रुको_क्रम_comp:   Indicator to रुको क्रम completion of the I/O (in jअगरfies)
 * @data_len:        The length of the data
 * @cdb_cmd:         The CDB command
 * @xfer_len:        The transfer length
 * @xfer_ddp:        Indicates अगर this transfer used DDP (XID of the exchange
 *                   will be set here अगर DDP was setup)
 * @xfer_contig_end: The offset पूर्णांकo the buffer अगर the buffer is contiguous
 *                   (Tx and Rx)
 * @max_payload:     The maximum payload size (in bytes)
 * @io_status:       SCSI result (upper 24 bits)
 * @cdb_status:      CDB status
 * @status_code:     FCP I/O status
 * @scsi_comp_flags: Completion flags (bit 3 Underrun bit 2: overrun)
 * @req_flags:       Request flags (bit 0: पढ़ो bit:1 ग_लिखो)
 * @scsi_resid:      SCSI residule length
 * @rport:           The remote port that the SCSI command is targeted at
 * @seq_ptr:         The sequence that will carry the SCSI command
 * @recov_retry:     Number of recovery retries
 * @recov_seq:       The sequence क्रम REC or SRR
 */
काष्ठा fc_fcp_pkt अणु
	spinlock_t	  scsi_pkt_lock;
	refcount_t	  ref_cnt;

	/* SCSI command and data transfer inक्रमmation */
	u32		  data_len;

	/* SCSI I/O related inक्रमmation */
	काष्ठा scsi_cmnd  *cmd;
	काष्ठा list_head  list;

	/* Housekeeping inक्रमmation */
	काष्ठा fc_lport   *lp;
	u8		  state;

	/* SCSI/FCP वापस status */
	u8		  cdb_status;
	u8		  status_code;
	u8		  scsi_comp_flags;
	u32		  io_status;
	u32		  req_flags;
	u32		  scsi_resid;

	/* Transport related veriables */
	माप_प्रकार		  xfer_len;
	काष्ठा fcp_cmnd   cdb_cmd;
	u32		  xfer_contig_end;
	u16		  max_payload;
	u16		  xfer_ddp;

	/* Associated काष्ठाures */
	काष्ठा fc_rport	  *rport;
	काष्ठा fc_seq	  *seq_ptr;

	/* Timeout/error related inक्रमmation */
	काष्ठा समयr_list समयr;
	पूर्णांक		  रुको_क्रम_comp;
	पूर्णांक		  समयr_delay;
	u32		  recov_retry;
	काष्ठा fc_seq	  *recov_seq;
	काष्ठा completion पंचांग_करोne;
पूर्ण ____cacheline_aligned_in_smp;

/*
 * Structure and function definitions क्रम managing Fibre Channel Exchanges
 * and Sequences
 *
 * fc_exch holds state क्रम one exchange and links to its active sequence.
 *
 * fc_seq holds the state क्रम an inभागidual sequence.
 */

काष्ठा fc_exch_mgr;
काष्ठा fc_exch_mgr_anchor;
बाह्य u16 fc_cpu_mask;	/* cpu mask क्रम possible cpus */

/**
 * काष्ठा fc_seq - FC sequence
 * @id:       The sequence ID
 * @ssb_stat: Status flags क्रम the sequence status block (SSB)
 * @cnt:      Number of frames sent so far
 * @rec_data: FC-4 value क्रम REC
 */
काष्ठा fc_seq अणु
	u8  id;
	u16 ssb_stat;
	u16 cnt;
	u32 rec_data;
पूर्ण;

#घोषणा FC_EX_DONE		(1 << 0) /* ep is completed */
#घोषणा FC_EX_RST_CLEANUP	(1 << 1) /* reset is क्रमcing completion */
#घोषणा FC_EX_QUARANTINE	(1 << 2) /* exch is quarantined */

/**
 * काष्ठा fc_exch - Fibre Channel Exchange
 * @em:           Exchange manager
 * @pool:         Exchange pool
 * @state:        The exchange's state
 * @xid:          The exchange ID
 * @ex_list:      Handle used by the EM to track मुक्त exchanges
 * @ex_lock:      Lock that protects the exchange
 * @ex_refcnt:    Reference count
 * @समयout_work: Handle क्रम समयout handler
 * @lp:           The local port that this exchange is on
 * @oxid:         Originator's exchange ID
 * @rxid:         Responder's exchange ID
 * @oid:          Originator's FCID
 * @sid:          Source FCID
 * @did:          Destination FCID
 * @esb_stat:     ESB exchange status
 * @r_a_tov:      Resouce allocation समय out value (in msecs)
 * @seq_id:       The next sequence ID to use
 * @encaps:       encapsulation inक्रमmation क्रम lower-level driver
 * @f_ctl:        F_CTL flags क्रम the sequence
 * @fh_type:      The frame type
 * @class:        The class of service
 * @seq:          The sequence in use on this exchange
 * @resp_active:  Number of tasks that are concurrently executing @resp().
 * @resp_task:    If @resp_active > 0, either the task executing @resp(), the
 *                task that has been पूर्णांकerrupted to execute the soft-IRQ
 *                executing @resp() or शून्य अगर more than one task is executing
 *                @resp concurrently.
 * @resp_wq:      Waitqueue क्रम the tasks रुकोing on @resp_active.
 * @resp:         Callback क्रम responses on this exchange
 * @deकाष्ठाor:   Called when destroying the exchange
 * @arg:          Passed as a व्योम poपूर्णांकer to the resp() callback
 *
 * Locking notes: The ex_lock protects following items:
 *	state, esb_stat, f_ctl, seq.ssb_stat
 *	seq_id
 *	sequence allocation
 */
काष्ठा fc_exch अणु
	spinlock_t	    ex_lock;
	atomic_t	    ex_refcnt;
	क्रमागत fc_class	    class;
	काष्ठा fc_exch_mgr  *em;
	काष्ठा fc_exch_pool *pool;
	काष्ठा list_head    ex_list;
	काष्ठा fc_lport	    *lp;
	u32		    esb_stat;
	u8		    state;
	u8		    fh_type;
	u8		    seq_id;
	u8		    encaps;
	u16		    xid;
	u16		    oxid;
	u16		    rxid;
	u32		    oid;
	u32		    sid;
	u32		    did;
	u32		    r_a_tov;
	u32		    f_ctl;
	काष्ठा fc_seq       seq;
	पूर्णांक		    resp_active;
	काष्ठा task_काष्ठा  *resp_task;
	रुको_queue_head_t   resp_wq;
	व्योम		    (*resp)(काष्ठा fc_seq *, काष्ठा fc_frame *, व्योम *);
	व्योम		    *arg;
	व्योम		    (*deकाष्ठाor)(काष्ठा fc_seq *, व्योम *);
	काष्ठा delayed_work समयout_work;
पूर्ण ____cacheline_aligned_in_smp;
#घोषणा	fc_seq_exch(sp) container_of(sp, काष्ठा fc_exch, seq)


काष्ठा libfc_function_ढाँचा अणु
	/*
	 * Interface to send a FC frame
	 *
	 * STATUS: REQUIRED
	 */
	पूर्णांक (*frame_send)(काष्ठा fc_lport *, काष्ठा fc_frame *);

	/*
	 * Interface to send ELS/CT frames
	 *
	 * STATUS: OPTIONAL
	 */
	काष्ठा fc_seq *(*elsct_send)(काष्ठा fc_lport *, u32 did,
				     काष्ठा fc_frame *, अचिन्हित पूर्णांक op,
				     व्योम (*resp)(काष्ठा fc_seq *,
					     काष्ठा fc_frame *, व्योम *arg),
				     व्योम *arg, u32 समयr_msec);

	/*
	 * Sets up the DDP context क्रम a given exchange id on the given
	 * scatterlist अगर LLD supports DDP क्रम large receive.
	 *
	 * STATUS: OPTIONAL
	 */
	पूर्णांक (*ddp_setup)(काष्ठा fc_lport *, u16, काष्ठा scatterlist *,
			 अचिन्हित पूर्णांक);
	/*
	 * Completes the DDP transfer and वापसs the length of data DDPed
	 * क्रम the given exchange id.
	 *
	 * STATUS: OPTIONAL
	 */
	पूर्णांक (*ddp_करोne)(काष्ठा fc_lport *, u16);
	/*
	 * Sets up the DDP context क्रम a given exchange id on the given
	 * scatterlist अगर LLD supports DDP क्रम target.
	 *
	 * STATUS: OPTIONAL
	 */
	पूर्णांक (*ddp_target)(काष्ठा fc_lport *, u16, काष्ठा scatterlist *,
			  अचिन्हित पूर्णांक);
	/*
	 * Allow LLD to fill its own Link Error Status Block
	 *
	 * STATUS: OPTIONAL
	 */
	व्योम (*get_lesb)(काष्ठा fc_lport *, काष्ठा fc_els_lesb *lesb);

	/*
	 * Reset an exchange manager, completing all sequences and exchanges.
	 * If s_id is non-zero, reset only exchanges originating from that FID.
	 * If d_id is non-zero, reset only exchanges sending to that FID.
	 *
	 * STATUS: OPTIONAL
	 */
	व्योम (*exch_mgr_reset)(काष्ठा fc_lport *, u32 s_id, u32 d_id);

	/*
	 * Set the local port FC_ID.
	 *
	 * This may be provided by the LLD to allow it to be
	 * notअगरied when the local port is asचिन्हित a FC-ID.
	 *
	 * The frame, अगर non-शून्य, is the incoming frame with the
	 * FLOGI LS_ACC or FLOGI, and may contain the granted MAC
	 * address क्रम the LLD.  The frame poपूर्णांकer may be शून्य अगर
	 * no MAC is associated with this assignment (LOGO or PLOGI).
	 *
	 * If FC_ID is non-zero, r_a_tov and e_d_tov must be valid.
	 *
	 * Note: this is called with the local port mutex held.
	 *
	 * STATUS: OPTIONAL
	 */
	व्योम (*lport_set_port_id)(काष्ठा fc_lport *, u32 port_id,
				  काष्ठा fc_frame *);

	/*
	 * Callback routine after the remote port is logged in
	 *
	 * STATUS: OPTIONAL
	 */
	व्योम (*rport_event_callback)(काष्ठा fc_lport *,
				     काष्ठा fc_rport_priv *,
				     क्रमागत fc_rport_event);

	/*
	 * Send a fcp cmd from fsp pkt.
	 * Called with the SCSI host lock unlocked and irqs disabled.
	 *
	 * The resp handler is called when FCP_RSP received.
	 *
	 * STATUS: OPTIONAL
	 */
	पूर्णांक (*fcp_cmd_send)(काष्ठा fc_lport *, काष्ठा fc_fcp_pkt *,
			    व्योम (*resp)(काष्ठा fc_seq *, काष्ठा fc_frame *,
					 व्योम *));

	/*
	 * Cleanup the FCP layer, used during link करोwn and reset
	 *
	 * STATUS: OPTIONAL
	 */
	व्योम (*fcp_cleanup)(काष्ठा fc_lport *);

	/*
	 * Abort all I/O on a local port
	 *
	 * STATUS: OPTIONAL
	 */
	व्योम (*fcp_पात_io)(काष्ठा fc_lport *);

	/*
	 * Receive a request क्रम the discovery layer.
	 *
	 * STATUS: OPTIONAL
	 */
	व्योम (*disc_recv_req)(काष्ठा fc_lport *, काष्ठा fc_frame *);

	/*
	 * Start discovery क्रम a local port.
	 *
	 * STATUS: OPTIONAL
	 */
	व्योम (*disc_start)(व्योम (*disc_callback)(काष्ठा fc_lport *,
						 क्रमागत fc_disc_event),
			   काष्ठा fc_lport *);

	/*
	 * Stop discovery क्रम a given lport. This will हटाओ
	 * all discovered rports
	 *
	 * STATUS: OPTIONAL
	 */
	व्योम (*disc_stop) (काष्ठा fc_lport *);

	/*
	 * Stop discovery क्रम a given lport. This will block
	 * until all discovered rports are deleted from the
	 * FC transport class
	 *
	 * STATUS: OPTIONAL
	 */
	व्योम (*disc_stop_final) (काष्ठा fc_lport *);
पूर्ण;

/**
 * काष्ठा fc_disc - Discovery context
 * @retry_count:   Number of retries
 * @pending:       1 अगर discovery is pending, 0 अगर not
 * @requested:     1 अगर discovery has been requested, 0 अगर not
 * @seq_count:     Number of sequences used क्रम discovery
 * @buf_len:       Length of the discovery buffer
 * @disc_id:       Discovery ID
 * @rports:        List of discovered remote ports
 * @priv:          Private poपूर्णांकer क्रम use by discovery code
 * @disc_mutex:    Mutex that protects the discovery context
 * @partial_buf:   Partial name buffer (अगर names are वापसed
 *                 in multiple frames)
 * @disc_work:     handle क्रम delayed work context
 * @disc_callback: Callback routine called when discovery completes
 */
काष्ठा fc_disc अणु
	अचिन्हित अक्षर	      retry_count;
	अचिन्हित अक्षर	      pending;
	अचिन्हित अक्षर	      requested;
	अचिन्हित लघु	      seq_count;
	अचिन्हित अक्षर	      buf_len;
	u16		      disc_id;

	काष्ठा list_head      rports;
	व्योम		      *priv;
	काष्ठा mutex	      disc_mutex;
	काष्ठा fc_gpn_ft_resp partial_buf;
	काष्ठा delayed_work   disc_work;

	व्योम (*disc_callback)(काष्ठा fc_lport *,
			      क्रमागत fc_disc_event);
पूर्ण;

/*
 * Local port notअगरier and events.
 */
बाह्य काष्ठा blocking_notअगरier_head fc_lport_notअगरier_head;
क्रमागत fc_lport_event अणु
	FC_LPORT_EV_ADD,
	FC_LPORT_EV_DEL,
पूर्ण;

/**
 * काष्ठा fc_lport - Local port
 * @host:                  The SCSI host associated with a local port
 * @ema_list:              Exchange manager anchor list
 * @dns_rdata:             The directory server remote port
 * @ms_rdata:		   The management server remote port
 * @ptp_rdata:             Poपूर्णांक to poपूर्णांक remote port
 * @scsi_priv:             FCP layer पूर्णांकernal data
 * @disc:                  Discovery context
 * @vports:                Child vports अगर N_Port
 * @vport:                 Parent vport अगर VN_Port
 * @tt:                    Libfc function ढाँचा
 * @link_up:               Link state (1 = link up, 0 = link करोwn)
 * @qfull:                 Queue state (1 queue is full, 0 queue is not full)
 * @state:                 Identअगरies the state
 * @boot_समय:             Timestamp indicating when the local port came online
 * @host_stats:            SCSI host statistics
 * @stats:                 FC local port stats (TODO separate libfc LLD stats)
 * @retry_count:           Number of retries in the current state
 * @port_id:               FC Port ID
 * @wwpn:                  World Wide Port Name
 * @wwnn:                  World Wide Node Name
 * @service_params:        Common service parameters
 * @e_d_tov:               Error detection समयout value
 * @r_a_tov:               Resouce allocation समयout value
 * @rnid_gen:              RNID inक्रमmation
 * @sg_supp:               Indicates अगर scatter gather is supported
 * @seq_offload:           Indicates अगर sequence offload is supported
 * @crc_offload:           Indicates अगर CRC offload is supported
 * @lro_enabled:           Indicates अगर large receive offload is supported
 * @करोes_npiv:             Supports multiple vports
 * @npiv_enabled:          Switch/fabric allows NPIV
 * @mfs:                   The maximum Fibre Channel payload size
 * @max_retry_count:       The maximum retry attempts
 * @max_rport_retry_count: The maximum remote port retry attempts
 * @rport_priv_size:       Size needed by driver after काष्ठा fc_rport_priv
 * @lro_xid:               The maximum XID क्रम LRO
 * @lso_max:               The maximum large offload send size
 * @fcts:                  FC-4 type mask
 * @lp_mutex:              Mutex to protect the local port
 * @list:                  Linkage on list of vport peers
 * @retry_work:            Handle to local port क्रम delayed retry context
 * @prov:		   Poपूर्णांकers available क्रम use by passive FC-4 providers
 * @lport_list:            Linkage on module-wide list of local ports
 */
काष्ठा fc_lport अणु
	/* Associations */
	काष्ठा Scsi_Host	       *host;
	काष्ठा list_head	       ema_list;
	काष्ठा fc_rport_priv	       *dns_rdata;
	काष्ठा fc_rport_priv	       *ms_rdata;
	काष्ठा fc_rport_priv	       *ptp_rdata;
	व्योम			       *scsi_priv;
	काष्ठा fc_disc		       disc;

	/* Virtual port inक्रमmation */
	काष्ठा list_head	       vports;
	काष्ठा fc_vport		       *vport;

	/* Operational Inक्रमmation */
	काष्ठा libfc_function_ढाँचा tt;
	u8			       link_up;
	u8			       qfull;
	u16			       vlan;
	क्रमागत fc_lport_state	       state;
	अचिन्हित दीर्घ		       boot_समय;
	काष्ठा fc_host_statistics      host_stats;
	काष्ठा fc_stats	__percpu       *stats;
	u8			       retry_count;

	/* Fabric inक्रमmation */
	u32			       port_id;
	u64			       wwpn;
	u64			       wwnn;
	अचिन्हित पूर्णांक		       service_params;
	अचिन्हित पूर्णांक		       e_d_tov;
	अचिन्हित पूर्णांक		       r_a_tov;
	काष्ठा fc_els_rnid_gen	       rnid_gen;

	/* Capabilities */
	u32			       sg_supp:1;
	u32			       seq_offload:1;
	u32			       crc_offload:1;
	u32			       lro_enabled:1;
	u32			       करोes_npiv:1;
	u32			       npiv_enabled:1;
	u32			       poपूर्णांक_to_multipoपूर्णांक:1;
	u32			       fdmi_enabled:1;
	u32			       mfs;
	u8			       max_retry_count;
	u8			       max_rport_retry_count;
	u16			       rport_priv_size;
	u16			       link_speed;
	u16			       link_supported_speeds;
	u16			       lro_xid;
	अचिन्हित पूर्णांक		       lso_max;
	काष्ठा fc_ns_fts	       fcts;

	/* Miscellaneous */
	काष्ठा mutex		       lp_mutex;
	काष्ठा list_head	       list;
	काष्ठा delayed_work	       retry_work;
	व्योम			       *prov[FC_FC4_PROV_SIZE];
	काष्ठा list_head	       lport_list;
पूर्ण;

/**
 * काष्ठा fc4_prov - FC-4 provider registration
 * @prli:               Handler क्रम incoming PRLI
 * @prlo:               Handler क्रम session reset
 * @recv:		Handler क्रम incoming request
 * @module:		Poपूर्णांकer to module.  May be शून्य.
 */
काष्ठा fc4_prov अणु
	पूर्णांक (*prli)(काष्ठा fc_rport_priv *, u32 spp_len,
		    स्थिर काष्ठा fc_els_spp *spp_in,
		    काष्ठा fc_els_spp *spp_out);
	व्योम (*prlo)(काष्ठा fc_rport_priv *);
	व्योम (*recv)(काष्ठा fc_lport *, काष्ठा fc_frame *);
	काष्ठा module *module;
पूर्ण;

/*
 * Register FC-4 provider with libfc.
 */
पूर्णांक fc_fc4_रेजिस्टर_provider(क्रमागत fc_fh_type type, काष्ठा fc4_prov *);
व्योम fc_fc4_deरेजिस्टर_provider(क्रमागत fc_fh_type type, काष्ठा fc4_prov *);

/*
 * FC_LPORT HELPER FUNCTIONS
 *****************************/

/**
 * fc_lport_test_पढ़ोy() - Determine अगर a local port is in the READY state
 * @lport: The local port to test
 */
अटल अंतरभूत पूर्णांक fc_lport_test_पढ़ोy(काष्ठा fc_lport *lport)
अणु
	वापस lport->state == LPORT_ST_READY;
पूर्ण

/**
 * fc_set_wwnn() - Set the World Wide Node Name of a local port
 * @lport: The local port whose WWNN is to be set
 * @wwnn:  The new WWNN
 */
अटल अंतरभूत व्योम fc_set_wwnn(काष्ठा fc_lport *lport, u64 wwnn)
अणु
	lport->wwnn = wwnn;
पूर्ण

/**
 * fc_set_wwpn() - Set the World Wide Port Name of a local port
 * @lport: The local port whose WWPN is to be set
 * @wwpn:  The new WWPN
 */
अटल अंतरभूत व्योम fc_set_wwpn(काष्ठा fc_lport *lport, u64 wwpn)
अणु
	lport->wwpn = wwpn;
पूर्ण

/**
 * fc_lport_state_enter() - Change a local port's state
 * @lport: The local port whose state is to change
 * @state: The new state
 */
अटल अंतरभूत व्योम fc_lport_state_enter(काष्ठा fc_lport *lport,
					क्रमागत fc_lport_state state)
अणु
	अगर (state != lport->state)
		lport->retry_count = 0;
	lport->state = state;
पूर्ण

/**
 * fc_lport_init_stats() - Allocate per-CPU statistics क्रम a local port
 * @lport: The local port whose statistics are to be initialized
 */
अटल अंतरभूत पूर्णांक fc_lport_init_stats(काष्ठा fc_lport *lport)
अणु
	lport->stats = alloc_percpu(काष्ठा fc_stats);
	अगर (!lport->stats)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 * fc_lport_मुक्त_stats() - Free memory क्रम a local port's statistics
 * @lport: The local port whose statistics are to be मुक्तd
 */
अटल अंतरभूत व्योम fc_lport_मुक्त_stats(काष्ठा fc_lport *lport)
अणु
	मुक्त_percpu(lport->stats);
पूर्ण

/**
 * lport_priv() - Return the निजी data from a local port
 * @lport: The local port whose निजी data is to be retreived
 */
अटल अंतरभूत व्योम *lport_priv(स्थिर काष्ठा fc_lport *lport)
अणु
	वापस (व्योम *)(lport + 1);
पूर्ण

/**
 * libfc_host_alloc() - Allocate a Scsi_Host with room क्रम a local port and
 *                      LLD निजी data
 * @sht:       The SCSI host ढाँचा
 * @priv_size: Size of निजी data
 *
 * Returns: libfc lport
 */
अटल अंतरभूत काष्ठा fc_lport *
libfc_host_alloc(काष्ठा scsi_host_ढाँचा *sht, पूर्णांक priv_size)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा Scsi_Host *shost;

	shost = scsi_host_alloc(sht, माप(*lport) + priv_size);
	अगर (!shost)
		वापस शून्य;
	lport = shost_priv(shost);
	lport->host = shost;
	INIT_LIST_HEAD(&lport->ema_list);
	INIT_LIST_HEAD(&lport->vports);
	वापस lport;
पूर्ण

/*
 * FC_FCP HELPER FUNCTIONS
 *****************************/
अटल अंतरभूत bool fc_fcp_is_पढ़ो(स्थिर काष्ठा fc_fcp_pkt *fsp)
अणु
	अगर (fsp && fsp->cmd)
		वापस fsp->cmd->sc_data_direction == DMA_FROM_DEVICE;
	वापस false;
पूर्ण

/*
 * LOCAL PORT LAYER
 *****************************/
पूर्णांक fc_lport_init(काष्ठा fc_lport *);
पूर्णांक fc_lport_destroy(काष्ठा fc_lport *);
पूर्णांक fc_fabric_logoff(काष्ठा fc_lport *);
पूर्णांक fc_fabric_login(काष्ठा fc_lport *);
व्योम __fc_linkup(काष्ठा fc_lport *);
व्योम fc_linkup(काष्ठा fc_lport *);
व्योम __fc_linkकरोwn(काष्ठा fc_lport *);
व्योम fc_linkकरोwn(काष्ठा fc_lport *);
व्योम fc_vport_setlink(काष्ठा fc_lport *);
व्योम fc_vports_linkchange(काष्ठा fc_lport *);
पूर्णांक fc_lport_config(काष्ठा fc_lport *);
पूर्णांक fc_lport_reset(काष्ठा fc_lport *);
व्योम fc_lport_recv(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp);
पूर्णांक fc_set_mfs(काष्ठा fc_lport *, u32 mfs);
काष्ठा fc_lport *libfc_vport_create(काष्ठा fc_vport *, पूर्णांक privsize);
काष्ठा fc_lport *fc_vport_id_lookup(काष्ठा fc_lport *, u32 port_id);
पूर्णांक fc_lport_bsg_request(काष्ठा bsg_job *);
व्योम fc_lport_set_local_id(काष्ठा fc_lport *, u32 port_id);
व्योम fc_lport_iterate(व्योम (*func)(काष्ठा fc_lport *, व्योम *), व्योम *);

/*
 * REMOTE PORT LAYER
 *****************************/
व्योम fc_rport_terminate_io(काष्ठा fc_rport *);
काष्ठा fc_rport_priv *fc_rport_lookup(स्थिर काष्ठा fc_lport *lport,
				      u32 port_id);
काष्ठा fc_rport_priv *fc_rport_create(काष्ठा fc_lport *, u32);
व्योम fc_rport_destroy(काष्ठा kref *kref);
पूर्णांक fc_rport_login(काष्ठा fc_rport_priv *rdata);
पूर्णांक fc_rport_logoff(काष्ठा fc_rport_priv *rdata);
व्योम fc_rport_recv_req(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp);
व्योम fc_rport_flush_queue(व्योम);

/*
 * DISCOVERY LAYER
 *****************************/
व्योम fc_disc_init(काष्ठा fc_lport *);
व्योम fc_disc_config(काष्ठा fc_lport *, व्योम *);

अटल अंतरभूत काष्ठा fc_lport *fc_disc_lport(काष्ठा fc_disc *disc)
अणु
	वापस container_of(disc, काष्ठा fc_lport, disc);
पूर्ण

/*
 * FCP LAYER
 *****************************/
पूर्णांक fc_fcp_init(काष्ठा fc_lport *);
व्योम fc_fcp_destroy(काष्ठा fc_lport *);

/*
 * SCSI INTERACTION LAYER
 *****************************/
पूर्णांक fc_queuecommand(काष्ठा Scsi_Host *, काष्ठा scsi_cmnd *);
पूर्णांक fc_eh_पात(काष्ठा scsi_cmnd *);
पूर्णांक fc_eh_device_reset(काष्ठा scsi_cmnd *);
पूर्णांक fc_eh_host_reset(काष्ठा scsi_cmnd *);
पूर्णांक fc_slave_alloc(काष्ठा scsi_device *);

/*
 * ELS/CT पूर्णांकerface
 *****************************/
पूर्णांक fc_elsct_init(काष्ठा fc_lport *);
काष्ठा fc_seq *fc_elsct_send(काष्ठा fc_lport *, u32 did,
				    काष्ठा fc_frame *,
				    अचिन्हित पूर्णांक op,
				    व्योम (*resp)(काष्ठा fc_seq *,
						 काष्ठा fc_frame *,
						 व्योम *arg),
				    व्योम *arg, u32 समयr_msec);
व्योम fc_lport_flogi_resp(काष्ठा fc_seq *, काष्ठा fc_frame *, व्योम *);
व्योम fc_lport_logo_resp(काष्ठा fc_seq *, काष्ठा fc_frame *, व्योम *);
व्योम fc_fill_reply_hdr(काष्ठा fc_frame *, स्थिर काष्ठा fc_frame *,
		       क्रमागत fc_rctl, u32 parm_offset);
व्योम fc_fill_hdr(काष्ठा fc_frame *, स्थिर काष्ठा fc_frame *,
		 क्रमागत fc_rctl, u32 f_ctl, u16 seq_cnt, u32 parm_offset);


/*
 * EXCHANGE MANAGER LAYER
 *****************************/
पूर्णांक fc_exch_init(काष्ठा fc_lport *);
व्योम fc_exch_update_stats(काष्ठा fc_lport *lport);
काष्ठा fc_seq *fc_exch_seq_send(काष्ठा fc_lport *lport,
				काष्ठा fc_frame *fp,
				व्योम (*resp)(काष्ठा fc_seq *,
					     काष्ठा fc_frame *fp,
					     व्योम *arg),
				व्योम (*deकाष्ठाor)(काष्ठा fc_seq *, व्योम *),
				व्योम *arg, u32 समयr_msec);
व्योम fc_seq_els_rsp_send(काष्ठा fc_frame *, क्रमागत fc_els_cmd,
			 काष्ठा fc_seq_els_data *);
काष्ठा fc_seq *fc_seq_start_next(काष्ठा fc_seq *sp);
व्योम fc_seq_set_resp(काष्ठा fc_seq *sp,
		     व्योम (*resp)(काष्ठा fc_seq *, काष्ठा fc_frame *, व्योम *),
		     व्योम *arg);
काष्ठा fc_seq *fc_seq_assign(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp);
व्योम fc_seq_release(काष्ठा fc_seq *sp);
काष्ठा fc_exch_mgr_anchor *fc_exch_mgr_add(काष्ठा fc_lport *,
					   काष्ठा fc_exch_mgr *,
					   bool (*match)(काष्ठा fc_frame *));
व्योम fc_exch_mgr_del(काष्ठा fc_exch_mgr_anchor *);
पूर्णांक fc_exch_mgr_list_clone(काष्ठा fc_lport *src, काष्ठा fc_lport *dst);
काष्ठा fc_exch_mgr *fc_exch_mgr_alloc(काष्ठा fc_lport *, क्रमागत fc_class class,
				      u16 min_xid, u16 max_xid,
				      bool (*match)(काष्ठा fc_frame *));
व्योम fc_exch_mgr_मुक्त(काष्ठा fc_lport *);
व्योम fc_exch_recv(काष्ठा fc_lport *, काष्ठा fc_frame *);
व्योम fc_exch_mgr_reset(काष्ठा fc_lport *, u32 s_id, u32 d_id);
पूर्णांक fc_seq_send(काष्ठा fc_lport *lport, काष्ठा fc_seq *sp, काष्ठा fc_frame *fp);
पूर्णांक fc_seq_exch_पात(स्थिर काष्ठा fc_seq *, अचिन्हित पूर्णांक समयr_msec);
व्योम fc_exch_करोne(काष्ठा fc_seq *sp);

/*
 * Functions क्रम fc_functions_ढाँचा
 */
व्योम fc_get_host_speed(काष्ठा Scsi_Host *);
व्योम fc_get_host_port_state(काष्ठा Scsi_Host *);
व्योम fc_set_rport_loss_पंचांगo(काष्ठा fc_rport *, u32 समयout);
काष्ठा fc_host_statistics *fc_get_host_stats(काष्ठा Scsi_Host *);

#पूर्ण_अगर /* _LIBFC_H_ */
