<शैली गुरु>
/* bnx2x_sp.h: Qlogic Everest network driver.
 *
 * Copyright 2011-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * Unless you and Qlogic execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2, available
 * at http://www.gnu.org/licenses/gpl-2.0.hपंचांगl (the "GPL").
 *
 * Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Qlogic software provided under a
 * license other than the GPL, without Qlogic's express prior written
 * consent.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Vladislav Zolotarov
 *
 */
#अगर_अघोषित BNX2X_SP_VERBS
#घोषणा BNX2X_SP_VERBS

काष्ठा bnx2x;
काष्ठा eth_context;

/* Bits representing general command's configuration */
क्रमागत अणु
	RAMROD_TX,
	RAMROD_RX,
	/* Wait until all pending commands complete */
	RAMROD_COMP_WAIT,
	/* Don't send a ramrod, only update a registry */
	RAMROD_DRV_CLR_ONLY,
	/* Configure HW according to the current object state */
	RAMROD_RESTORE,
	 /* Execute the next command now */
	RAMROD_EXEC,
	/* Don't add a new command and जारी execution of postponed
	 * commands. If not set a new command will be added to the
	 * pending commands list.
	 */
	RAMROD_CONT,
	/* If there is another pending ramrod, रुको until it finishes and
	 * re-try to submit this one. This flag can be set only in sleepable
	 * context, and should not be set from the context that completes the
	 * ramrods as deadlock will occur.
	 */
	RAMROD_RETRY,
पूर्ण;

प्रकार क्रमागत अणु
	BNX2X_OBJ_TYPE_RX,
	BNX2X_OBJ_TYPE_TX,
	BNX2X_OBJ_TYPE_RX_TX,
पूर्ण bnx2x_obj_type;

/* Public slow path states */
क्रमागत अणु
	BNX2X_FILTER_MAC_PENDING,
	BNX2X_FILTER_VLAN_PENDING,
	BNX2X_FILTER_VLAN_MAC_PENDING,
	BNX2X_FILTER_RX_MODE_PENDING,
	BNX2X_FILTER_RX_MODE_SCHED,
	BNX2X_FILTER_ISCSI_ETH_START_SCHED,
	BNX2X_FILTER_ISCSI_ETH_STOP_SCHED,
	BNX2X_FILTER_FCOE_ETH_START_SCHED,
	BNX2X_FILTER_FCOE_ETH_STOP_SCHED,
	BNX2X_FILTER_MCAST_PENDING,
	BNX2X_FILTER_MCAST_SCHED,
	BNX2X_FILTER_RSS_CONF_PENDING,
	BNX2X_AFEX_FCOE_Q_UPDATE_PENDING,
	BNX2X_AFEX_PENDING_VIFSET_MCP_ACK
पूर्ण;

काष्ठा bnx2x_raw_obj अणु
	u8		func_id;

	/* Queue params */
	u8		cl_id;
	u32		cid;

	/* Ramrod data buffer params */
	व्योम		*rdata;
	dma_addr_t	rdata_mapping;

	/* Ramrod state params */
	पूर्णांक		state;   /* "ramrod is pending" state bit */
	अचिन्हित दीर्घ	*pstate; /* poपूर्णांकer to state buffer */

	bnx2x_obj_type	obj_type;

	पूर्णांक (*रुको_comp)(काष्ठा bnx2x *bp,
			 काष्ठा bnx2x_raw_obj *o);

	bool (*check_pending)(काष्ठा bnx2x_raw_obj *o);
	व्योम (*clear_pending)(काष्ठा bnx2x_raw_obj *o);
	व्योम (*set_pending)(काष्ठा bnx2x_raw_obj *o);
पूर्ण;

/************************* VLAN-MAC commands related parameters ***************/
काष्ठा bnx2x_mac_ramrod_data अणु
	u8 mac[ETH_ALEN];
	u8 is_inner_mac;
पूर्ण;

काष्ठा bnx2x_vlan_ramrod_data अणु
	u16 vlan;
पूर्ण;

काष्ठा bnx2x_vlan_mac_ramrod_data अणु
	u8 mac[ETH_ALEN];
	u8 is_inner_mac;
	u16 vlan;
पूर्ण;

जोड़ bnx2x_classअगरication_ramrod_data अणु
	काष्ठा bnx2x_mac_ramrod_data mac;
	काष्ठा bnx2x_vlan_ramrod_data vlan;
	काष्ठा bnx2x_vlan_mac_ramrod_data vlan_mac;
पूर्ण;

/* VLAN_MAC commands */
क्रमागत bnx2x_vlan_mac_cmd अणु
	BNX2X_VLAN_MAC_ADD,
	BNX2X_VLAN_MAC_DEL,
	BNX2X_VLAN_MAC_MOVE,
पूर्ण;

काष्ठा bnx2x_vlan_mac_data अणु
	/* Requested command: BNX2X_VLAN_MAC_XX */
	क्रमागत bnx2x_vlan_mac_cmd cmd;
	/* used to contain the data related vlan_mac_flags bits from
	 * ramrod parameters.
	 */
	अचिन्हित दीर्घ vlan_mac_flags;

	/* Needed क्रम MOVE command */
	काष्ठा bnx2x_vlan_mac_obj *target_obj;

	जोड़ bnx2x_classअगरication_ramrod_data u;
पूर्ण;

/*************************** Exe Queue obj ************************************/
जोड़ bnx2x_exe_queue_cmd_data अणु
	काष्ठा bnx2x_vlan_mac_data vlan_mac;

	काष्ठा अणु
		/* TODO */
	पूर्ण mcast;
पूर्ण;

काष्ठा bnx2x_exeq_elem अणु
	काष्ठा list_head		link;

	/* Length of this element in the exe_chunk. */
	पूर्णांक				cmd_len;

	जोड़ bnx2x_exe_queue_cmd_data	cmd_data;
पूर्ण;

जोड़ bnx2x_qable_obj;

जोड़ bnx2x_exeq_comp_elem अणु
	जोड़ event_ring_elem *elem;
पूर्ण;

काष्ठा bnx2x_exe_queue_obj;

प्रकार पूर्णांक (*exe_q_validate)(काष्ठा bnx2x *bp,
			      जोड़ bnx2x_qable_obj *o,
			      काष्ठा bnx2x_exeq_elem *elem);

प्रकार पूर्णांक (*exe_q_हटाओ)(काष्ठा bnx2x *bp,
			    जोड़ bnx2x_qable_obj *o,
			    काष्ठा bnx2x_exeq_elem *elem);

/* Return positive अगर entry was optimized, 0 - अगर not, negative
 * in हाल of an error.
 */
प्रकार पूर्णांक (*exe_q_optimize)(काष्ठा bnx2x *bp,
			      जोड़ bnx2x_qable_obj *o,
			      काष्ठा bnx2x_exeq_elem *elem);
प्रकार पूर्णांक (*exe_q_execute)(काष्ठा bnx2x *bp,
			     जोड़ bnx2x_qable_obj *o,
			     काष्ठा list_head *exe_chunk,
			     अचिन्हित दीर्घ *ramrod_flags);
प्रकार काष्ठा bnx2x_exeq_elem *
			(*exe_q_get)(काष्ठा bnx2x_exe_queue_obj *o,
				     काष्ठा bnx2x_exeq_elem *elem);

काष्ठा bnx2x_exe_queue_obj अणु
	/* Commands pending क्रम an execution. */
	काष्ठा list_head	exe_queue;

	/* Commands pending क्रम an completion. */
	काष्ठा list_head	pending_comp;

	spinlock_t		lock;

	/* Maximum length of commands' list क्रम one execution */
	पूर्णांक			exe_chunk_len;

	जोड़ bnx2x_qable_obj	*owner;

	/****** Virtual functions ******/
	/**
	 * Called beक्रमe commands execution क्रम commands that are really
	 * going to be executed (after 'optimize').
	 *
	 * Must run under exe_queue->lock
	 */
	exe_q_validate		validate;

	/**
	 * Called beक्रमe removing pending commands, cleaning allocated
	 * resources (e.g., credits from validate)
	 */
	 exe_q_हटाओ		हटाओ;

	/**
	 * This will try to cancel the current pending commands list
	 * considering the new command.
	 *
	 * Returns the number of optimized commands or a negative error code
	 *
	 * Must run under exe_queue->lock
	 */
	exe_q_optimize		optimize;

	/**
	 * Run the next commands chunk (owner specअगरic).
	 */
	exe_q_execute		execute;

	/**
	 * Return the exe_queue element containing the specअगरic command
	 * अगर any. Otherwise वापस शून्य.
	 */
	exe_q_get		get;
पूर्ण;
/***************** Classअगरication verbs: Set/Del MAC/VLAN/VLAN-MAC ************/
/*
 * Element in the VLAN_MAC registry list having all currently configured
 * rules.
 */
काष्ठा bnx2x_vlan_mac_registry_elem अणु
	काष्ठा list_head	link;

	/* Used to store the cam offset used क्रम the mac/vlan/vlan-mac.
	 * Relevant क्रम 57710 and 57711 only. VLANs and MACs share the
	 * same CAM क्रम these chips.
	 */
	पूर्णांक			cam_offset;

	/* Needed क्रम DEL and RESTORE flows */
	अचिन्हित दीर्घ		vlan_mac_flags;

	जोड़ bnx2x_classअगरication_ramrod_data u;
पूर्ण;

/* Bits representing VLAN_MAC commands specअगरic flags */
क्रमागत अणु
	BNX2X_UC_LIST_MAC,
	BNX2X_ETH_MAC,
	BNX2X_ISCSI_ETH_MAC,
	BNX2X_NETQ_ETH_MAC,
	BNX2X_VLAN,
	BNX2X_DONT_CONSUME_CAM_CREDIT,
	BNX2X_DONT_CONSUME_CAM_CREDIT_DEST,
पूर्ण;
/* When looking क्रम matching filters, some flags are not पूर्णांकeresting */
#घोषणा BNX2X_VLAN_MAC_CMP_MASK	(1 << BNX2X_UC_LIST_MAC | \
				 1 << BNX2X_ETH_MAC | \
				 1 << BNX2X_ISCSI_ETH_MAC | \
				 1 << BNX2X_NETQ_ETH_MAC | \
				 1 << BNX2X_VLAN)
#घोषणा BNX2X_VLAN_MAC_CMP_FLAGS(flags) \
	((flags) & BNX2X_VLAN_MAC_CMP_MASK)

काष्ठा bnx2x_vlan_mac_ramrod_params अणु
	/* Object to run the command from */
	काष्ठा bnx2x_vlan_mac_obj *vlan_mac_obj;

	/* General command flags: COMP_WAIT, etc. */
	अचिन्हित दीर्घ ramrod_flags;

	/* Command specअगरic configuration request */
	काष्ठा bnx2x_vlan_mac_data user_req;
पूर्ण;

काष्ठा bnx2x_vlan_mac_obj अणु
	काष्ठा bnx2x_raw_obj raw;

	/* Bookkeeping list: will prevent the addition of alपढ़ोy existing
	 * entries.
	 */
	काष्ठा list_head		head;
	/* Implement a simple पढ़ोer/ग_लिखोr lock on the head list.
	 * all these fields should only be accessed under the exe_queue lock
	 */
	u8		head_पढ़ोer; /* Num. of पढ़ोers accessing head list */
	bool		head_exe_request; /* Pending execution request. */
	अचिन्हित दीर्घ	saved_ramrod_flags; /* Ramrods of pending execution */

	/* TODO: Add it's initialization in the init functions */
	काष्ठा bnx2x_exe_queue_obj	exe_queue;

	/* MACs credit pool */
	काष्ठा bnx2x_credit_pool_obj	*macs_pool;

	/* VLANs credit pool */
	काष्ठा bnx2x_credit_pool_obj	*vlans_pool;

	/* RAMROD command to be used */
	पूर्णांक				ramrod_cmd;

	/* copy first n elements onto pपुनः_स्मृतिated buffer
	 *
	 * @param n number of elements to get
	 * @param buf buffer pपुनः_स्मृतिated by caller पूर्णांकo which elements
	 *            will be copied. Note elements are 4-byte aligned
	 *            so buffer size must be able to accommodate the
	 *            aligned elements.
	 *
	 * @वापस number of copied bytes
	 */
	पूर्णांक (*get_n_elements)(काष्ठा bnx2x *bp,
			      काष्ठा bnx2x_vlan_mac_obj *o, पूर्णांक n, u8 *base,
			      u8 stride, u8 size);

	/**
	 * Checks अगर ADD-ramrod with the given params may be perक्रमmed.
	 *
	 * @वापस zero अगर the element may be added
	 */

	पूर्णांक (*check_add)(काष्ठा bnx2x *bp,
			 काष्ठा bnx2x_vlan_mac_obj *o,
			 जोड़ bnx2x_classअगरication_ramrod_data *data);

	/**
	 * Checks अगर DEL-ramrod with the given params may be perक्रमmed.
	 *
	 * @वापस true अगर the element may be deleted
	 */
	काष्ठा bnx2x_vlan_mac_registry_elem *
		(*check_del)(काष्ठा bnx2x *bp,
			     काष्ठा bnx2x_vlan_mac_obj *o,
			     जोड़ bnx2x_classअगरication_ramrod_data *data);

	/**
	 * Checks अगर DEL-ramrod with the given params may be perक्रमmed.
	 *
	 * @वापस true अगर the element may be deleted
	 */
	bool (*check_move)(काष्ठा bnx2x *bp,
			   काष्ठा bnx2x_vlan_mac_obj *src_o,
			   काष्ठा bnx2x_vlan_mac_obj *dst_o,
			   जोड़ bnx2x_classअगरication_ramrod_data *data);

	/**
	 *  Update the relevant credit object(s) (consume/वापस
	 *  correspondingly).
	 */
	bool (*get_credit)(काष्ठा bnx2x_vlan_mac_obj *o);
	bool (*put_credit)(काष्ठा bnx2x_vlan_mac_obj *o);
	bool (*get_cam_offset)(काष्ठा bnx2x_vlan_mac_obj *o, पूर्णांक *offset);
	bool (*put_cam_offset)(काष्ठा bnx2x_vlan_mac_obj *o, पूर्णांक offset);

	/**
	 * Configures one rule in the ramrod data buffer.
	 */
	व्योम (*set_one_rule)(काष्ठा bnx2x *bp,
			     काष्ठा bnx2x_vlan_mac_obj *o,
			     काष्ठा bnx2x_exeq_elem *elem, पूर्णांक rule_idx,
			     पूर्णांक cam_offset);

	/**
	*  Delete all configured elements having the given
	*  vlan_mac_flags specअगरication. Assumes no pending क्रम
	*  execution commands. Will schedule all all currently
	*  configured MACs/VLANs/VLAN-MACs matching the vlan_mac_flags
	*  specअगरication क्रम deletion and will use the given
	*  ramrod_flags क्रम the last DEL operation.
	 *
	 * @param bp
	 * @param o
	 * @param ramrod_flags RAMROD_XX flags
	 *
	 * @वापस 0 अगर the last operation has completed successfully
	 *         and there are no more elements left, positive value
	 *         अगर there are pending क्रम completion commands,
	 *         negative value in हाल of failure.
	 */
	पूर्णांक (*delete_all)(काष्ठा bnx2x *bp,
			  काष्ठा bnx2x_vlan_mac_obj *o,
			  अचिन्हित दीर्घ *vlan_mac_flags,
			  अचिन्हित दीर्घ *ramrod_flags);

	/**
	 * Reconfigures the next MAC/VLAN/VLAN-MAC element from the previously
	 * configured elements list.
	 *
	 * @param bp
	 * @param p Command parameters (RAMROD_COMP_WAIT bit in
	 *          ramrod_flags is only taken पूर्णांकo an account)
	 * @param ppos a poपूर्णांकer to the cookie that should be given back in the
	 *        next call to make function handle the next element. If
	 *        *ppos is set to शून्य it will restart the iterator.
	 *        If वापसed *ppos == शून्य this means that the last
	 *        element has been handled.
	 *
	 * @वापस पूर्णांक
	 */
	पूर्णांक (*restore)(काष्ठा bnx2x *bp,
		       काष्ठा bnx2x_vlan_mac_ramrod_params *p,
		       काष्ठा bnx2x_vlan_mac_registry_elem **ppos);

	/**
	 * Should be called on a completion arrival.
	 *
	 * @param bp
	 * @param o
	 * @param cqe Completion element we are handling
	 * @param ramrod_flags अगर RAMROD_CONT is set the next bulk of
	 *		       pending commands will be executed.
	 *		       RAMROD_DRV_CLR_ONLY and RAMROD_RESTORE
	 *		       may also be set अगर needed.
	 *
	 * @वापस 0 अगर there are neither pending nor रुकोing क्रम
	 *         completion commands. Positive value अगर there are
	 *         pending क्रम execution or क्रम completion commands.
	 *         Negative value in हाल of an error (including an
	 *         error in the cqe).
	 */
	पूर्णांक (*complete)(काष्ठा bnx2x *bp, काष्ठा bnx2x_vlan_mac_obj *o,
			जोड़ event_ring_elem *cqe,
			अचिन्हित दीर्घ *ramrod_flags);

	/**
	 * Wait क्रम completion of all commands. Don't schedule new ones,
	 * just रुको. It assumes that the completion code will schedule
	 * क्रम new commands.
	 */
	पूर्णांक (*रुको)(काष्ठा bnx2x *bp, काष्ठा bnx2x_vlan_mac_obj *o);
पूर्ण;

क्रमागत अणु
	BNX2X_LLH_CAM_ISCSI_ETH_LINE = 0,
	BNX2X_LLH_CAM_ETH_LINE,
	BNX2X_LLH_CAM_MAX_PF_LINE = NIG_REG_LLH1_FUNC_MEM_SIZE / 2
पूर्ण;

/** RX_MODE verbs:DROP_ALL/ACCEPT_ALL/ACCEPT_ALL_MULTI/ACCEPT_ALL_VLAN/NORMAL */

/* RX_MODE ramrod special flags: set in rx_mode_flags field in
 * a bnx2x_rx_mode_ramrod_params.
 */
क्रमागत अणु
	BNX2X_RX_MODE_FCOE_ETH,
	BNX2X_RX_MODE_ISCSI_ETH,
पूर्ण;

क्रमागत अणु
	BNX2X_ACCEPT_UNICAST,
	BNX2X_ACCEPT_MULTICAST,
	BNX2X_ACCEPT_ALL_UNICAST,
	BNX2X_ACCEPT_ALL_MULTICAST,
	BNX2X_ACCEPT_BROADCAST,
	BNX2X_ACCEPT_UNMATCHED,
	BNX2X_ACCEPT_ANY_VLAN
पूर्ण;

काष्ठा bnx2x_rx_mode_ramrod_params अणु
	काष्ठा bnx2x_rx_mode_obj *rx_mode_obj;
	अचिन्हित दीर्घ *pstate;
	पूर्णांक state;
	u8 cl_id;
	u32 cid;
	u8 func_id;
	अचिन्हित दीर्घ ramrod_flags;
	अचिन्हित दीर्घ rx_mode_flags;

	/* rdata is either a poपूर्णांकer to eth_filter_rules_ramrod_data(e2) or to
	 * a tstorm_eth_mac_filter_config (e1x).
	 */
	व्योम *rdata;
	dma_addr_t rdata_mapping;

	/* Rx mode settings */
	अचिन्हित दीर्घ rx_accept_flags;

	/* पूर्णांकernal चयनing settings */
	अचिन्हित दीर्घ tx_accept_flags;
पूर्ण;

काष्ठा bnx2x_rx_mode_obj अणु
	पूर्णांक (*config_rx_mode)(काष्ठा bnx2x *bp,
			      काष्ठा bnx2x_rx_mode_ramrod_params *p);

	पूर्णांक (*रुको_comp)(काष्ठा bnx2x *bp,
			 काष्ठा bnx2x_rx_mode_ramrod_params *p);
पूर्ण;

/********************** Set multicast group ***********************************/

काष्ठा bnx2x_mcast_list_elem अणु
	काष्ठा list_head link;
	u8 *mac;
पूर्ण;

जोड़ bnx2x_mcast_config_data अणु
	u8 *mac;
	u8 bin; /* used in a RESTORE flow */
पूर्ण;

काष्ठा bnx2x_mcast_ramrod_params अणु
	काष्ठा bnx2x_mcast_obj *mcast_obj;

	/* Relevant options are RAMROD_COMP_WAIT and RAMROD_DRV_CLR_ONLY */
	अचिन्हित दीर्घ ramrod_flags;

	काष्ठा list_head mcast_list; /* list of काष्ठा bnx2x_mcast_list_elem */
	/** TODO:
	 *      - नाम it to macs_num.
	 *      - Add a new command type क्रम handling pending commands
	 *        (हटाओ "zero semantics").
	 *
	 *  Length of mcast_list. If zero and ADD_CONT command - post
	 *  pending commands.
	 */
	पूर्णांक mcast_list_len;
पूर्ण;

क्रमागत bnx2x_mcast_cmd अणु
	BNX2X_MCAST_CMD_ADD,
	BNX2X_MCAST_CMD_CONT,
	BNX2X_MCAST_CMD_DEL,
	BNX2X_MCAST_CMD_RESTORE,

	/* Following this, multicast configuration should equal to approx
	 * the set of MACs provided [i.e., हटाओ all अन्यथा].
	 * The two sub-commands are used पूर्णांकernally to decide whether a given
	 * bin is to be added or हटाओd
	 */
	BNX2X_MCAST_CMD_SET,
	BNX2X_MCAST_CMD_SET_ADD,
	BNX2X_MCAST_CMD_SET_DEL,
पूर्ण;

काष्ठा bnx2x_mcast_obj अणु
	काष्ठा bnx2x_raw_obj raw;

	जोड़ अणु
		काष्ठा अणु
		#घोषणा BNX2X_MCAST_BINS_NUM	256
		#घोषणा BNX2X_MCAST_VEC_SZ	(BNX2X_MCAST_BINS_NUM / 64)
			u64 vec[BNX2X_MCAST_VEC_SZ];

			/** Number of BINs to clear. Should be updated
			 *  immediately when a command arrives in order to
			 *  properly create DEL commands.
			 */
			पूर्णांक num_bins_set;
		पूर्ण aprox_match;

		काष्ठा अणु
			काष्ठा list_head macs;
			पूर्णांक num_macs_set;
		पूर्ण exact_match;
	पूर्ण registry;

	/* Pending commands */
	काष्ठा list_head pending_cmds_head;

	/* A state that is set in raw.pstate, when there are pending commands */
	पूर्णांक sched_state;

	/* Maximal number of mcast MACs configured in one command */
	पूर्णांक max_cmd_len;

	/* Total number of currently pending MACs to configure: both
	 * in the pending commands list and in the current command.
	 */
	पूर्णांक total_pending_num;

	u8 engine_id;

	/**
	 * @param cmd command to execute (BNX2X_MCAST_CMD_X, see above)
	 */
	पूर्णांक (*config_mcast)(काष्ठा bnx2x *bp,
			    काष्ठा bnx2x_mcast_ramrod_params *p,
			    क्रमागत bnx2x_mcast_cmd cmd);

	/**
	 * Fills the ramrod data during the RESTORE flow.
	 *
	 * @param bp
	 * @param o
	 * @param start_idx Registry index to start from
	 * @param rdata_idx Index in the ramrod data to start from
	 *
	 * @वापस -1 अगर we handled the whole registry or index of the last
	 *         handled registry element.
	 */
	पूर्णांक (*hdl_restore)(काष्ठा bnx2x *bp, काष्ठा bnx2x_mcast_obj *o,
			   पूर्णांक start_bin, पूर्णांक *rdata_idx);

	पूर्णांक (*enqueue_cmd)(काष्ठा bnx2x *bp, काष्ठा bnx2x_mcast_obj *o,
			   काष्ठा bnx2x_mcast_ramrod_params *p,
			   क्रमागत bnx2x_mcast_cmd cmd);

	व्योम (*set_one_rule)(काष्ठा bnx2x *bp,
			     काष्ठा bnx2x_mcast_obj *o, पूर्णांक idx,
			     जोड़ bnx2x_mcast_config_data *cfg_data,
			     क्रमागत bnx2x_mcast_cmd cmd);

	/** Checks अगर there are more mcast MACs to be set or a previous
	 *  command is still pending.
	 */
	bool (*check_pending)(काष्ठा bnx2x_mcast_obj *o);

	/**
	 * Set/Clear/Check SCHEDULED state of the object
	 */
	व्योम (*set_sched)(काष्ठा bnx2x_mcast_obj *o);
	व्योम (*clear_sched)(काष्ठा bnx2x_mcast_obj *o);
	bool (*check_sched)(काष्ठा bnx2x_mcast_obj *o);

	/* Wait until all pending commands complete */
	पूर्णांक (*रुको_comp)(काष्ठा bnx2x *bp, काष्ठा bnx2x_mcast_obj *o);

	/**
	 * Handle the पूर्णांकernal object counters needed क्रम proper
	 * commands handling. Checks that the provided parameters are
	 * feasible.
	 */
	पूर्णांक (*validate)(काष्ठा bnx2x *bp,
			काष्ठा bnx2x_mcast_ramrod_params *p,
			क्रमागत bnx2x_mcast_cmd cmd);

	/**
	 * Restore the values of पूर्णांकernal counters in हाल of a failure.
	 */
	व्योम (*revert)(काष्ठा bnx2x *bp,
		       काष्ठा bnx2x_mcast_ramrod_params *p,
		       पूर्णांक old_num_bins,
		       क्रमागत bnx2x_mcast_cmd cmd);

	पूर्णांक (*get_registry_size)(काष्ठा bnx2x_mcast_obj *o);
	व्योम (*set_registry_size)(काष्ठा bnx2x_mcast_obj *o, पूर्णांक n);
पूर्ण;

/*************************** Credit handling **********************************/
काष्ठा bnx2x_credit_pool_obj अणु

	/* Current amount of credit in the pool */
	atomic_t	credit;

	/* Maximum allowed credit. put() will check against it. */
	पूर्णांक		pool_sz;

	/* Allocate a pool table अटलally.
	 *
	 * Currently the maximum allowed size is MAX_MAC_CREDIT_E2(272)
	 *
	 * The set bit in the table will mean that the entry is available.
	 */
#घोषणा BNX2X_POOL_VEC_SIZE	(MAX_MAC_CREDIT_E2 / 64)
	u64		pool_mirror[BNX2X_POOL_VEC_SIZE];

	/* Base pool offset (initialized dअगरferently */
	पूर्णांक		base_pool_offset;

	/**
	 * Get the next मुक्त pool entry.
	 *
	 * @वापस true अगर there was a मुक्त entry in the pool
	 */
	bool (*get_entry)(काष्ठा bnx2x_credit_pool_obj *o, पूर्णांक *entry);

	/**
	 * Return the entry back to the pool.
	 *
	 * @वापस true अगर entry is legal and has been successfully
	 *         वापसed to the pool.
	 */
	bool (*put_entry)(काष्ठा bnx2x_credit_pool_obj *o, पूर्णांक entry);

	/**
	 * Get the requested amount of credit from the pool.
	 *
	 * @param cnt Amount of requested credit
	 * @वापस true अगर the operation is successful
	 */
	bool (*get)(काष्ठा bnx2x_credit_pool_obj *o, पूर्णांक cnt);

	/**
	 * Returns the credit to the pool.
	 *
	 * @param cnt Amount of credit to वापस
	 * @वापस true अगर the operation is successful
	 */
	bool (*put)(काष्ठा bnx2x_credit_pool_obj *o, पूर्णांक cnt);

	/**
	 * Reads the current amount of credit.
	 */
	पूर्णांक (*check)(काष्ठा bnx2x_credit_pool_obj *o);
पूर्ण;

/*************************** RSS configuration ********************************/
क्रमागत अणु
	/* RSS_MODE bits are mutually exclusive */
	BNX2X_RSS_MODE_DISABLED,
	BNX2X_RSS_MODE_REGULAR,

	BNX2X_RSS_SET_SRCH, /* Setup searcher, E1x specअगरic flag */

	BNX2X_RSS_IPV4,
	BNX2X_RSS_IPV4_TCP,
	BNX2X_RSS_IPV4_UDP,
	BNX2X_RSS_IPV6,
	BNX2X_RSS_IPV6_TCP,
	BNX2X_RSS_IPV6_UDP,

	BNX2X_RSS_IPV4_VXLAN,
	BNX2X_RSS_IPV6_VXLAN,
	BNX2X_RSS_TUNN_INNER_HDRS,
पूर्ण;

काष्ठा bnx2x_config_rss_params अणु
	काष्ठा bnx2x_rss_config_obj *rss_obj;

	/* may have RAMROD_COMP_WAIT set only */
	अचिन्हित दीर्घ	ramrod_flags;

	/* BNX2X_RSS_X bits */
	अचिन्हित दीर्घ	rss_flags;

	/* Number hash bits to take पूर्णांकo an account */
	u8		rss_result_mask;

	/* Indirection table */
	u8		ind_table[T_ETH_INसूचीECTION_TABLE_SIZE];

	/* RSS hash values */
	u32		rss_key[10];

	/* valid only अगरf BNX2X_RSS_UPDATE_TOE is set */
	u16		toe_rss_biपंचांगap;
पूर्ण;

काष्ठा bnx2x_rss_config_obj अणु
	काष्ठा bnx2x_raw_obj	raw;

	/* RSS engine to use */
	u8			engine_id;

	/* Last configured indirection table */
	u8			ind_table[T_ETH_INसूचीECTION_TABLE_SIZE];

	/* flags क्रम enabling 4-tupple hash on UDP */
	u8			udp_rss_v4;
	u8			udp_rss_v6;

	पूर्णांक (*config_rss)(काष्ठा bnx2x *bp,
			  काष्ठा bnx2x_config_rss_params *p);
पूर्ण;

/*********************** Queue state update ***********************************/

/* UPDATE command options */
क्रमागत अणु
	BNX2X_Q_UPDATE_IN_VLAN_REM,
	BNX2X_Q_UPDATE_IN_VLAN_REM_CHNG,
	BNX2X_Q_UPDATE_OUT_VLAN_REM,
	BNX2X_Q_UPDATE_OUT_VLAN_REM_CHNG,
	BNX2X_Q_UPDATE_ANTI_SPOOF,
	BNX2X_Q_UPDATE_ANTI_SPOOF_CHNG,
	BNX2X_Q_UPDATE_ACTIVATE,
	BNX2X_Q_UPDATE_ACTIVATE_CHNG,
	BNX2X_Q_UPDATE_DEF_VLAN_EN,
	BNX2X_Q_UPDATE_DEF_VLAN_EN_CHNG,
	BNX2X_Q_UPDATE_SILENT_VLAN_REM_CHNG,
	BNX2X_Q_UPDATE_SILENT_VLAN_REM,
	BNX2X_Q_UPDATE_TX_SWITCHING_CHNG,
	BNX2X_Q_UPDATE_TX_SWITCHING,
	BNX2X_Q_UPDATE_PTP_PKTS_CHNG,
	BNX2X_Q_UPDATE_PTP_PKTS,
पूर्ण;

/* Allowed Queue states */
क्रमागत bnx2x_q_state अणु
	BNX2X_Q_STATE_RESET,
	BNX2X_Q_STATE_INITIALIZED,
	BNX2X_Q_STATE_ACTIVE,
	BNX2X_Q_STATE_MULTI_COS,
	BNX2X_Q_STATE_MCOS_TERMINATED,
	BNX2X_Q_STATE_INACTIVE,
	BNX2X_Q_STATE_STOPPED,
	BNX2X_Q_STATE_TERMINATED,
	BNX2X_Q_STATE_FLRED,
	BNX2X_Q_STATE_MAX,
पूर्ण;

/* Allowed Queue states */
क्रमागत bnx2x_q_logical_state अणु
	BNX2X_Q_LOGICAL_STATE_ACTIVE,
	BNX2X_Q_LOGICAL_STATE_STOPPED,
पूर्ण;

/* Allowed commands */
क्रमागत bnx2x_queue_cmd अणु
	BNX2X_Q_CMD_INIT,
	BNX2X_Q_CMD_SETUP,
	BNX2X_Q_CMD_SETUP_TX_ONLY,
	BNX2X_Q_CMD_DEACTIVATE,
	BNX2X_Q_CMD_ACTIVATE,
	BNX2X_Q_CMD_UPDATE,
	BNX2X_Q_CMD_UPDATE_TPA,
	BNX2X_Q_CMD_HALT,
	BNX2X_Q_CMD_CFC_DEL,
	BNX2X_Q_CMD_TERMINATE,
	BNX2X_Q_CMD_EMPTY,
	BNX2X_Q_CMD_MAX,
पूर्ण;

/* queue SETUP + INIT flags */
क्रमागत अणु
	BNX2X_Q_FLG_TPA,
	BNX2X_Q_FLG_TPA_IPV6,
	BNX2X_Q_FLG_TPA_GRO,
	BNX2X_Q_FLG_STATS,
	BNX2X_Q_FLG_ZERO_STATS,
	BNX2X_Q_FLG_ACTIVE,
	BNX2X_Q_FLG_OV,
	BNX2X_Q_FLG_VLAN,
	BNX2X_Q_FLG_COS,
	BNX2X_Q_FLG_HC,
	BNX2X_Q_FLG_HC_EN,
	BNX2X_Q_FLG_DHC,
	BNX2X_Q_FLG_FCOE,
	BNX2X_Q_FLG_LEADING_RSS,
	BNX2X_Q_FLG_MCAST,
	BNX2X_Q_FLG_DEF_VLAN,
	BNX2X_Q_FLG_TX_SWITCH,
	BNX2X_Q_FLG_TX_SEC,
	BNX2X_Q_FLG_ANTI_SPOOF,
	BNX2X_Q_FLG_SILENT_VLAN_REM,
	BNX2X_Q_FLG_FORCE_DEFAULT_PRI,
	BNX2X_Q_FLG_REFUSE_OUTBAND_VLAN,
	BNX2X_Q_FLG_PCSUM_ON_PKT,
	BNX2X_Q_FLG_TUN_INC_INNER_IP_ID
पूर्ण;

/* Queue type options: queue type may be a combination of below. */
क्रमागत bnx2x_q_type अणु
	/** TODO: Consider moving both these flags पूर्णांकo the init()
	 *        ramrod params.
	 */
	BNX2X_Q_TYPE_HAS_RX,
	BNX2X_Q_TYPE_HAS_TX,
पूर्ण;

#घोषणा BNX2X_PRIMARY_CID_INDEX			0
#घोषणा BNX2X_MULTI_TX_COS_E1X			3 /* QM only */
#घोषणा BNX2X_MULTI_TX_COS_E2_E3A0		2
#घोषणा BNX2X_MULTI_TX_COS_E3B0			3
#घोषणा BNX2X_MULTI_TX_COS			3 /* Maximum possible */

#घोषणा MAC_PAD (ALIGN(ETH_ALEN, माप(u32)) - ETH_ALEN)
/* DMAE channel to be used by FW क्रम बारync workaroun. A driver that sends
 * बारync-related ramrods must not use this DMAE command ID.
 */
#घोषणा FW_DMAE_CMD_ID 6

काष्ठा bnx2x_queue_init_params अणु
	काष्ठा अणु
		अचिन्हित दीर्घ	flags;
		u16		hc_rate;
		u8		fw_sb_id;
		u8		sb_cq_index;
	पूर्ण tx;

	काष्ठा अणु
		अचिन्हित दीर्घ	flags;
		u16		hc_rate;
		u8		fw_sb_id;
		u8		sb_cq_index;
	पूर्ण rx;

	/* CID context in the host memory */
	काष्ठा eth_context *cxts[BNX2X_MULTI_TX_COS];

	/* maximum number of cos supported by hardware */
	u8 max_cos;
पूर्ण;

काष्ठा bnx2x_queue_terminate_params अणु
	/* index within the tx_only cids of this queue object */
	u8 cid_index;
पूर्ण;

काष्ठा bnx2x_queue_cfc_del_params अणु
	/* index within the tx_only cids of this queue object */
	u8 cid_index;
पूर्ण;

काष्ठा bnx2x_queue_update_params अणु
	अचिन्हित दीर्घ	update_flags; /* BNX2X_Q_UPDATE_XX bits */
	u16		def_vlan;
	u16		silent_removal_value;
	u16		silent_removal_mask;
/* index within the tx_only cids of this queue object */
	u8		cid_index;
पूर्ण;

काष्ठा bnx2x_queue_update_tpa_params अणु
	dma_addr_t sge_map;
	u8 update_ipv4;
	u8 update_ipv6;
	u8 max_tpa_queues;
	u8 max_sges_pkt;
	u8 complete_on_both_clients;
	u8 करोnt_verअगरy_thr;
	u8 tpa_mode;
	u8 _pad;

	u16 sge_buff_sz;
	u16 max_agg_sz;

	u16 sge_छोड़ो_thr_low;
	u16 sge_छोड़ो_thr_high;
पूर्ण;

काष्ठा rxq_छोड़ो_params अणु
	u16		bd_th_lo;
	u16		bd_th_hi;
	u16		rcq_th_lo;
	u16		rcq_th_hi;
	u16		sge_th_lo; /* valid अगरf BNX2X_Q_FLG_TPA */
	u16		sge_th_hi; /* valid अगरf BNX2X_Q_FLG_TPA */
	u16		pri_map;
पूर्ण;

/* general */
काष्ठा bnx2x_general_setup_params अणु
	/* valid अगरf BNX2X_Q_FLG_STATS */
	u8		stat_id;

	u8		spcl_id;
	u16		mtu;
	u8		cos;

	u8		fp_hsi;
पूर्ण;

काष्ठा bnx2x_rxq_setup_params अणु
	/* dma */
	dma_addr_t	dscr_map;
	dma_addr_t	sge_map;
	dma_addr_t	rcq_map;
	dma_addr_t	rcq_np_map;

	u16		drop_flags;
	u16		buf_sz;
	u8		fw_sb_id;
	u8		cl_qzone_id;

	/* valid अगरf BNX2X_Q_FLG_TPA */
	u16		tpa_agg_sz;
	u16		sge_buf_sz;
	u8		max_sges_pkt;
	u8		max_tpa_queues;
	u8		rss_engine_id;

	/* valid अगरf BNX2X_Q_FLG_MCAST */
	u8		mcast_engine_id;

	u8		cache_line_log;

	u8		sb_cq_index;

	/* valid अगरf BXN2X_Q_FLG_SILENT_VLAN_REM */
	u16 silent_removal_value;
	u16 silent_removal_mask;
पूर्ण;

काष्ठा bnx2x_txq_setup_params अणु
	/* dma */
	dma_addr_t	dscr_map;

	u8		fw_sb_id;
	u8		sb_cq_index;
	u8		cos;		/* valid अगरf BNX2X_Q_FLG_COS */
	u16		traffic_type;
	/* equals to the leading rss client id, used क्रम TX classअगरication*/
	u8		tss_leading_cl_id;

	/* valid अगरf BNX2X_Q_FLG_DEF_VLAN */
	u16		शेष_vlan;
पूर्ण;

काष्ठा bnx2x_queue_setup_params अणु
	काष्ठा bnx2x_general_setup_params gen_params;
	काष्ठा bnx2x_txq_setup_params txq_params;
	काष्ठा bnx2x_rxq_setup_params rxq_params;
	काष्ठा rxq_छोड़ो_params छोड़ो_params;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा bnx2x_queue_setup_tx_only_params अणु
	काष्ठा bnx2x_general_setup_params	gen_params;
	काष्ठा bnx2x_txq_setup_params		txq_params;
	अचिन्हित दीर्घ				flags;
	/* index within the tx_only cids of this queue object */
	u8					cid_index;
पूर्ण;

काष्ठा bnx2x_queue_state_params अणु
	काष्ठा bnx2x_queue_sp_obj *q_obj;

	/* Current command */
	क्रमागत bnx2x_queue_cmd cmd;

	/* may have RAMROD_COMP_WAIT set only */
	अचिन्हित दीर्घ ramrod_flags;

	/* Params according to the current command */
	जोड़ अणु
		काष्ठा bnx2x_queue_update_params	update;
		काष्ठा bnx2x_queue_update_tpa_params    update_tpa;
		काष्ठा bnx2x_queue_setup_params		setup;
		काष्ठा bnx2x_queue_init_params		init;
		काष्ठा bnx2x_queue_setup_tx_only_params	tx_only;
		काष्ठा bnx2x_queue_terminate_params	terminate;
		काष्ठा bnx2x_queue_cfc_del_params	cfc_del;
	पूर्ण params;
पूर्ण;

काष्ठा bnx2x_vअगरlist_params अणु
	u8 echo_res;
	u8 func_bit_map_res;
पूर्ण;

काष्ठा bnx2x_queue_sp_obj अणु
	u32		cids[BNX2X_MULTI_TX_COS];
	u8		cl_id;
	u8		func_id;

	/* number of traffic classes supported by queue.
	 * The primary connection of the queue supports the first traffic
	 * class. Any further traffic class is supported by a tx-only
	 * connection.
	 *
	 * Thereक्रमe max_cos is also a number of valid entries in the cids
	 * array.
	 */
	u8 max_cos;
	u8 num_tx_only, next_tx_only;

	क्रमागत bnx2x_q_state state, next_state;

	/* bits from क्रमागत bnx2x_q_type */
	अचिन्हित दीर्घ	type;

	/* BNX2X_Q_CMD_XX bits. This object implements "one
	 * pending" paradigm but क्रम debug and tracing purposes it's
	 * more convenient to have dअगरferent bits क्रम dअगरferent
	 * commands.
	 */
	अचिन्हित दीर्घ	pending;

	/* Buffer to use as a ramrod data and its mapping */
	व्योम		*rdata;
	dma_addr_t	rdata_mapping;

	/**
	 * Perक्रमms one state change according to the given parameters.
	 *
	 * @वापस 0 in हाल of success and negative value otherwise.
	 */
	पूर्णांक (*send_cmd)(काष्ठा bnx2x *bp,
			काष्ठा bnx2x_queue_state_params *params);

	/**
	 * Sets the pending bit according to the requested transition.
	 */
	पूर्णांक (*set_pending)(काष्ठा bnx2x_queue_sp_obj *o,
			   काष्ठा bnx2x_queue_state_params *params);

	/**
	 * Checks that the requested state transition is legal.
	 */
	पूर्णांक (*check_transition)(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_queue_sp_obj *o,
				काष्ठा bnx2x_queue_state_params *params);

	/**
	 * Completes the pending command.
	 */
	पूर्णांक (*complete_cmd)(काष्ठा bnx2x *bp,
			    काष्ठा bnx2x_queue_sp_obj *o,
			    क्रमागत bnx2x_queue_cmd);

	पूर्णांक (*रुको_comp)(काष्ठा bnx2x *bp,
			 काष्ठा bnx2x_queue_sp_obj *o,
			 क्रमागत bnx2x_queue_cmd cmd);
पूर्ण;

/********************** Function state update *********************************/

/* UPDATE command options */
क्रमागत अणु
	BNX2X_F_UPDATE_TX_SWITCH_SUSPEND_CHNG,
	BNX2X_F_UPDATE_TX_SWITCH_SUSPEND,
	BNX2X_F_UPDATE_SD_VLAN_TAG_CHNG,
	BNX2X_F_UPDATE_SD_VLAN_ETH_TYPE_CHNG,
	BNX2X_F_UPDATE_VLAN_FORCE_PRIO_CHNG,
	BNX2X_F_UPDATE_VLAN_FORCE_PRIO_FLAG,
	BNX2X_F_UPDATE_TUNNEL_CFG_CHNG,
	BNX2X_F_UPDATE_TUNNEL_INNER_CLSS_L2GRE,
	BNX2X_F_UPDATE_TUNNEL_INNER_CLSS_VXLAN,
	BNX2X_F_UPDATE_TUNNEL_INNER_CLSS_L2GENEVE,
	BNX2X_F_UPDATE_TUNNEL_INNER_RSS,
पूर्ण;

/* Allowed Function states */
क्रमागत bnx2x_func_state अणु
	BNX2X_F_STATE_RESET,
	BNX2X_F_STATE_INITIALIZED,
	BNX2X_F_STATE_STARTED,
	BNX2X_F_STATE_TX_STOPPED,
	BNX2X_F_STATE_MAX,
पूर्ण;

/* Allowed Function commands */
क्रमागत bnx2x_func_cmd अणु
	BNX2X_F_CMD_HW_INIT,
	BNX2X_F_CMD_START,
	BNX2X_F_CMD_STOP,
	BNX2X_F_CMD_HW_RESET,
	BNX2X_F_CMD_AFEX_UPDATE,
	BNX2X_F_CMD_AFEX_VIFLISTS,
	BNX2X_F_CMD_TX_STOP,
	BNX2X_F_CMD_TX_START,
	BNX2X_F_CMD_SWITCH_UPDATE,
	BNX2X_F_CMD_SET_TIMESYNC,
	BNX2X_F_CMD_MAX,
पूर्ण;

काष्ठा bnx2x_func_hw_init_params अणु
	/* A load phase वापसed by MCP.
	 *
	 * May be:
	 *		FW_MSG_CODE_DRV_LOAD_COMMON_CHIP
	 *		FW_MSG_CODE_DRV_LOAD_COMMON
	 *		FW_MSG_CODE_DRV_LOAD_PORT
	 *		FW_MSG_CODE_DRV_LOAD_FUNCTION
	 */
	u32 load_phase;
पूर्ण;

काष्ठा bnx2x_func_hw_reset_params अणु
	/* A load phase वापसed by MCP.
	 *
	 * May be:
	 *		FW_MSG_CODE_DRV_LOAD_COMMON_CHIP
	 *		FW_MSG_CODE_DRV_LOAD_COMMON
	 *		FW_MSG_CODE_DRV_LOAD_PORT
	 *		FW_MSG_CODE_DRV_LOAD_FUNCTION
	 */
	u32 reset_phase;
पूर्ण;

काष्ठा bnx2x_func_start_params अणु
	/* Multi Function mode:
	 *	- Single Function
	 *	- Switch Dependent
	 *	- Switch Independent
	 */
	u16 mf_mode;

	/* Switch Dependent mode outer VLAN tag */
	u16 sd_vlan_tag;

	/* Function cos mode */
	u8 network_cos_mode;

	/* UDP dest port क्रम VXLAN */
	u16 vxlan_dst_port;

	/* UDP dest port क्रम Geneve */
	u16 geneve_dst_port;

	/* Enable inner Rx classअगरications क्रम L2GRE packets */
	u8 inner_clss_l2gre;

	/* Enable inner Rx classअगरications क्रम L2-Geneve packets */
	u8 inner_clss_l2geneve;

	/* Enable inner Rx classअगरication क्रम vxlan packets */
	u8 inner_clss_vxlan;

	/* Enable RSS according to inner header */
	u8 inner_rss;

	/* Allows accepting of packets failing MF classअगरication, possibly
	 * only matching a given ethertype
	 */
	u8 class_fail;
	u16 class_fail_ethtype;

	/* Override priority of output packets */
	u8 sd_vlan_क्रमce_pri;
	u8 sd_vlan_क्रमce_pri_val;

	/* Replace vlan's ethertype */
	u16 sd_vlan_eth_type;

	/* Prevent inner vlans from being added by FW */
	u8 no_added_tags;

	/* Inner-to-Outer vlan priority mapping */
	u8 c2s_pri[MAX_VLAN_PRIORITIES];
	u8 c2s_pri_शेष;
	u8 c2s_pri_valid;
पूर्ण;

काष्ठा bnx2x_func_चयन_update_params अणु
	अचिन्हित दीर्घ changes; /* BNX2X_F_UPDATE_XX bits */
	u16 vlan;
	u16 vlan_eth_type;
	u8 vlan_क्रमce_prio;
	u16 vxlan_dst_port;
	u16 geneve_dst_port;
पूर्ण;

काष्ठा bnx2x_func_afex_update_params अणु
	u16 vअगर_id;
	u16 afex_शेष_vlan;
	u8 allowed_priorities;
पूर्ण;

काष्ठा bnx2x_func_afex_vअगरlists_params अणु
	u16 vअगर_list_index;
	u8 func_bit_map;
	u8 afex_vअगर_list_command;
	u8 func_to_clear;
पूर्ण;

काष्ठा bnx2x_func_tx_start_params अणु
	काष्ठा priority_cos traffic_type_to_priority_cos[MAX_TRAFFIC_TYPES];
	u8 dcb_enabled;
	u8 dcb_version;
	u8 करोnt_add_pri_0_en;
	u8 dcb_outer_pri[MAX_TRAFFIC_TYPES];
पूर्ण;

काष्ठा bnx2x_func_set_बारync_params अणु
	/* Reset, set or keep the current drअगरt value */
	u8 drअगरt_adjust_cmd;

	/* Dec, inc or keep the current offset */
	u8 offset_cmd;

	/* Drअगरt value direction */
	u8 add_sub_drअगरt_adjust_value;

	/* Drअगरt, period and offset values to be used according to the commands
	 * above.
	 */
	u8 drअगरt_adjust_value;
	u32 drअगरt_adjust_period;
	u64 offset_delta;
पूर्ण;

काष्ठा bnx2x_func_state_params अणु
	काष्ठा bnx2x_func_sp_obj *f_obj;

	/* Current command */
	क्रमागत bnx2x_func_cmd cmd;

	/* may have RAMROD_COMP_WAIT set only */
	अचिन्हित दीर्घ	ramrod_flags;

	/* Params according to the current command */
	जोड़ अणु
		काष्ठा bnx2x_func_hw_init_params hw_init;
		काष्ठा bnx2x_func_hw_reset_params hw_reset;
		काष्ठा bnx2x_func_start_params start;
		काष्ठा bnx2x_func_चयन_update_params चयन_update;
		काष्ठा bnx2x_func_afex_update_params afex_update;
		काष्ठा bnx2x_func_afex_vअगरlists_params afex_vअगरlists;
		काष्ठा bnx2x_func_tx_start_params tx_start;
		काष्ठा bnx2x_func_set_बारync_params set_बारync;
	पूर्ण params;
पूर्ण;

काष्ठा bnx2x_func_sp_drv_ops अणु
	/* Init tool + runसमय initialization:
	 *      - Common Chip
	 *      - Common (per Path)
	 *      - Port
	 *      - Function phases
	 */
	पूर्णांक (*init_hw_cmn_chip)(काष्ठा bnx2x *bp);
	पूर्णांक (*init_hw_cmn)(काष्ठा bnx2x *bp);
	पूर्णांक (*init_hw_port)(काष्ठा bnx2x *bp);
	पूर्णांक (*init_hw_func)(काष्ठा bnx2x *bp);

	/* Reset Function HW: Common, Port, Function phases. */
	व्योम (*reset_hw_cmn)(काष्ठा bnx2x *bp);
	व्योम (*reset_hw_port)(काष्ठा bnx2x *bp);
	व्योम (*reset_hw_func)(काष्ठा bnx2x *bp);

	/* Init/Free GUNZIP resources */
	पूर्णांक (*gunzip_init)(काष्ठा bnx2x *bp);
	व्योम (*gunzip_end)(काष्ठा bnx2x *bp);

	/* Prepare/Release FW resources */
	पूर्णांक (*init_fw)(काष्ठा bnx2x *bp);
	व्योम (*release_fw)(काष्ठा bnx2x *bp);
पूर्ण;

काष्ठा bnx2x_func_sp_obj अणु
	क्रमागत bnx2x_func_state	state, next_state;

	/* BNX2X_FUNC_CMD_XX bits. This object implements "one
	 * pending" paradigm but क्रम debug and tracing purposes it's
	 * more convenient to have dअगरferent bits क्रम dअगरferent
	 * commands.
	 */
	अचिन्हित दीर्घ		pending;

	/* Buffer to use as a ramrod data and its mapping */
	व्योम			*rdata;
	dma_addr_t		rdata_mapping;

	/* Buffer to use as a afex ramrod data and its mapping.
	 * This can't be same rdata as above because afex ramrod requests
	 * can arrive to the object in parallel to other ramrod requests.
	 */
	व्योम			*afex_rdata;
	dma_addr_t		afex_rdata_mapping;

	/* this mutex validates that when pending flag is taken, the next
	 * ramrod to be sent will be the one set the pending bit
	 */
	काष्ठा mutex		one_pending_mutex;

	/* Driver पूर्णांकerface */
	काष्ठा bnx2x_func_sp_drv_ops	*drv;

	/**
	 * Perक्रमms one state change according to the given parameters.
	 *
	 * @वापस 0 in हाल of success and negative value otherwise.
	 */
	पूर्णांक (*send_cmd)(काष्ठा bnx2x *bp,
			काष्ठा bnx2x_func_state_params *params);

	/**
	 * Checks that the requested state transition is legal.
	 */
	पूर्णांक (*check_transition)(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_func_sp_obj *o,
				काष्ठा bnx2x_func_state_params *params);

	/**
	 * Completes the pending command.
	 */
	पूर्णांक (*complete_cmd)(काष्ठा bnx2x *bp,
			    काष्ठा bnx2x_func_sp_obj *o,
			    क्रमागत bnx2x_func_cmd cmd);

	पूर्णांक (*रुको_comp)(काष्ठा bnx2x *bp, काष्ठा bnx2x_func_sp_obj *o,
			 क्रमागत bnx2x_func_cmd cmd);
पूर्ण;

/********************** Interfaces ********************************************/
/* Queueable objects set */
जोड़ bnx2x_qable_obj अणु
	काष्ठा bnx2x_vlan_mac_obj vlan_mac;
पूर्ण;
/************** Function state update *********/
व्योम bnx2x_init_func_obj(काष्ठा bnx2x *bp,
			 काष्ठा bnx2x_func_sp_obj *obj,
			 व्योम *rdata, dma_addr_t rdata_mapping,
			 व्योम *afex_rdata, dma_addr_t afex_rdata_mapping,
			 काष्ठा bnx2x_func_sp_drv_ops *drv_अगरace);

पूर्णांक bnx2x_func_state_change(काष्ठा bnx2x *bp,
			    काष्ठा bnx2x_func_state_params *params);

क्रमागत bnx2x_func_state bnx2x_func_get_state(काष्ठा bnx2x *bp,
					   काष्ठा bnx2x_func_sp_obj *o);
/******************* Queue State **************/
व्योम bnx2x_init_queue_obj(काष्ठा bnx2x *bp,
			  काष्ठा bnx2x_queue_sp_obj *obj, u8 cl_id, u32 *cids,
			  u8 cid_cnt, u8 func_id, व्योम *rdata,
			  dma_addr_t rdata_mapping, अचिन्हित दीर्घ type);

पूर्णांक bnx2x_queue_state_change(काष्ठा bnx2x *bp,
			     काष्ठा bnx2x_queue_state_params *params);

पूर्णांक bnx2x_get_q_logical_state(काष्ठा bnx2x *bp,
			       काष्ठा bnx2x_queue_sp_obj *obj);

/********************* VLAN-MAC ****************/
व्योम bnx2x_init_mac_obj(काष्ठा bnx2x *bp,
			काष्ठा bnx2x_vlan_mac_obj *mac_obj,
			u8 cl_id, u32 cid, u8 func_id, व्योम *rdata,
			dma_addr_t rdata_mapping, पूर्णांक state,
			अचिन्हित दीर्घ *pstate, bnx2x_obj_type type,
			काष्ठा bnx2x_credit_pool_obj *macs_pool);

व्योम bnx2x_init_vlan_obj(काष्ठा bnx2x *bp,
			 काष्ठा bnx2x_vlan_mac_obj *vlan_obj,
			 u8 cl_id, u32 cid, u8 func_id, व्योम *rdata,
			 dma_addr_t rdata_mapping, पूर्णांक state,
			 अचिन्हित दीर्घ *pstate, bnx2x_obj_type type,
			 काष्ठा bnx2x_credit_pool_obj *vlans_pool);

व्योम bnx2x_init_vlan_mac_obj(काष्ठा bnx2x *bp,
			     काष्ठा bnx2x_vlan_mac_obj *vlan_mac_obj,
			     u8 cl_id, u32 cid, u8 func_id, व्योम *rdata,
			     dma_addr_t rdata_mapping, पूर्णांक state,
			     अचिन्हित दीर्घ *pstate, bnx2x_obj_type type,
			     काष्ठा bnx2x_credit_pool_obj *macs_pool,
			     काष्ठा bnx2x_credit_pool_obj *vlans_pool);

पूर्णांक bnx2x_vlan_mac_h_पढ़ो_lock(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_vlan_mac_obj *o);
व्योम bnx2x_vlan_mac_h_पढ़ो_unlock(काष्ठा bnx2x *bp,
				  काष्ठा bnx2x_vlan_mac_obj *o);
पूर्णांक bnx2x_vlan_mac_h_ग_लिखो_lock(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_vlan_mac_obj *o);
पूर्णांक bnx2x_config_vlan_mac(काष्ठा bnx2x *bp,
			   काष्ठा bnx2x_vlan_mac_ramrod_params *p);

पूर्णांक bnx2x_vlan_mac_move(काष्ठा bnx2x *bp,
			काष्ठा bnx2x_vlan_mac_ramrod_params *p,
			काष्ठा bnx2x_vlan_mac_obj *dest_o);

/********************* RX MODE ****************/

व्योम bnx2x_init_rx_mode_obj(काष्ठा bnx2x *bp,
			    काष्ठा bnx2x_rx_mode_obj *o);

/**
 * bnx2x_config_rx_mode - Send and RX_MODE ramrod according to the provided parameters.
 *
 * @p: Command parameters
 *
 * Return: 0 - अगर operation was successful and there is no pending completions,
 *         positive number - अगर there are pending completions,
 *         negative - अगर there were errors
 */
पूर्णांक bnx2x_config_rx_mode(काष्ठा bnx2x *bp,
			 काष्ठा bnx2x_rx_mode_ramrod_params *p);

/****************** MULTICASTS ****************/

व्योम bnx2x_init_mcast_obj(काष्ठा bnx2x *bp,
			  काष्ठा bnx2x_mcast_obj *mcast_obj,
			  u8 mcast_cl_id, u32 mcast_cid, u8 func_id,
			  u8 engine_id, व्योम *rdata, dma_addr_t rdata_mapping,
			  पूर्णांक state, अचिन्हित दीर्घ *pstate,
			  bnx2x_obj_type type);

/**
 * bnx2x_config_mcast - Configure multicast MACs list.
 *
 * @cmd: command to execute: BNX2X_MCAST_CMD_X
 *
 * May configure a new list
 * provided in p->mcast_list (BNX2X_MCAST_CMD_ADD), clean up
 * (BNX2X_MCAST_CMD_DEL) or restore (BNX2X_MCAST_CMD_RESTORE) a current
 * configuration, जारी to execute the pending commands
 * (BNX2X_MCAST_CMD_CONT).
 *
 * If previous command is still pending or अगर number of MACs to
 * configure is more that maximum number of MACs in one command,
 * the current command will be enqueued to the tail of the
 * pending commands list.
 *
 * Return: 0 is operation was successful and there are no pending completions,
 *         negative अगर there were errors, positive अगर there are pending
 *         completions.
 */
पूर्णांक bnx2x_config_mcast(काष्ठा bnx2x *bp,
		       काष्ठा bnx2x_mcast_ramrod_params *p,
		       क्रमागत bnx2x_mcast_cmd cmd);

/****************** CREDIT POOL ****************/
व्योम bnx2x_init_mac_credit_pool(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_credit_pool_obj *p, u8 func_id,
				u8 func_num);
व्योम bnx2x_init_vlan_credit_pool(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_credit_pool_obj *p, u8 func_id,
				 u8 func_num);
व्योम bnx2x_init_credit_pool(काष्ठा bnx2x_credit_pool_obj *p,
			    पूर्णांक base, पूर्णांक credit);

/****************** RSS CONFIGURATION ****************/
व्योम bnx2x_init_rss_config_obj(काष्ठा bnx2x *bp,
			       काष्ठा bnx2x_rss_config_obj *rss_obj,
			       u8 cl_id, u32 cid, u8 func_id, u8 engine_id,
			       व्योम *rdata, dma_addr_t rdata_mapping,
			       पूर्णांक state, अचिन्हित दीर्घ *pstate,
			       bnx2x_obj_type type);

/**
 * bnx2x_config_rss - Updates RSS configuration according to provided parameters
 *
 * Return: 0 in हाल of success
 */
पूर्णांक bnx2x_config_rss(काष्ठा bnx2x *bp,
		     काष्ठा bnx2x_config_rss_params *p);

/**
 * bnx2x_get_rss_ind_table - Return the current ind_table configuration.
 *
 * @ind_table: buffer to fill with the current indirection
 *                  table content. Should be at least
 *                  T_ETH_INसूचीECTION_TABLE_SIZE bytes दीर्घ.
 */
व्योम bnx2x_get_rss_ind_table(काष्ठा bnx2x_rss_config_obj *rss_obj,
			     u8 *ind_table);

#घोषणा PF_MAC_CREDIT_E2(bp, func_num)					\
	((MAX_MAC_CREDIT_E2 - GET_NUM_VFS_PER_PATH(bp) * VF_MAC_CREDIT_CNT) / \
	 func_num + GET_NUM_VFS_PER_PF(bp) * VF_MAC_CREDIT_CNT)

#घोषणा BNX2X_VFS_VLAN_CREDIT(bp)	\
	(GET_NUM_VFS_PER_PATH(bp) * VF_VLAN_CREDIT_CNT)

#घोषणा PF_VLAN_CREDIT_E2(bp, func_num)					 \
	((MAX_VLAN_CREDIT_E2 - 1 - BNX2X_VFS_VLAN_CREDIT(bp)) /	\
	 func_num + GET_NUM_VFS_PER_PF(bp) * VF_VLAN_CREDIT_CNT)

#पूर्ण_अगर /* BNX2X_SP_VERBS */
