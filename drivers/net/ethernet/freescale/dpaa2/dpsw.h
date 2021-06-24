<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2021 NXP
 *
 */

#अगर_अघोषित __FSL_DPSW_H
#घोषणा __FSL_DPSW_H

/* Data Path L2-Switch API
 * Contains API क्रम handling DPSW topology and functionality
 */

काष्ठा fsl_mc_io;

/* DPSW general definitions */

#घोषणा DPSW_MAX_PRIORITIES	8

#घोषणा DPSW_MAX_IF		64

पूर्णांक dpsw_खोलो(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, पूर्णांक dpsw_id, u16 *token);

पूर्णांक dpsw_बंद(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token);

/* DPSW options */

/**
 * DPSW_OPT_FLOODING_DIS - Flooding was disabled at device create
 */
#घोषणा DPSW_OPT_FLOODING_DIS		0x0000000000000001ULL
/**
 * DPSW_OPT_MULTICAST_DIS - Multicast was disabled at device create
 */
#घोषणा DPSW_OPT_MULTICAST_DIS		0x0000000000000004ULL
/**
 * DPSW_OPT_CTRL_IF_DIS - Control पूर्णांकerface support is disabled
 */
#घोषणा DPSW_OPT_CTRL_IF_DIS		0x0000000000000010ULL

/**
 * क्रमागत dpsw_component_type - component type of a bridge
 * @DPSW_COMPONENT_TYPE_C_VLAN: A C-VLAN component of an
 *   enterprise VLAN bridge or of a Provider Bridge used
 *   to process C-tagged frames
 * @DPSW_COMPONENT_TYPE_S_VLAN: An S-VLAN component of a
 *   Provider Bridge
 *
 */
क्रमागत dpsw_component_type अणु
	DPSW_COMPONENT_TYPE_C_VLAN = 0,
	DPSW_COMPONENT_TYPE_S_VLAN
पूर्ण;

/**
 *  क्रमागत dpsw_flooding_cfg - flooding configuration requested
 * @DPSW_FLOODING_PER_VLAN: Flooding replicators are allocated per VLAN and
 * पूर्णांकerfaces present in each of them can be configured using
 * dpsw_vlan_add_अगर_flooding()/dpsw_vlan_हटाओ_अगर_flooding().
 * This is the शेष configuration.
 *
 * @DPSW_FLOODING_PER_FDB: Flooding replicators are allocated per FDB and
 * पूर्णांकerfaces present in each of them can be configured using
 * dpsw_set_egress_flood().
 */
क्रमागत dpsw_flooding_cfg अणु
	DPSW_FLOODING_PER_VLAN = 0,
	DPSW_FLOODING_PER_FDB,
पूर्ण;

/**
 * क्रमागत dpsw_broadcast_cfg - broadcast configuration requested
 * @DPSW_BROADCAST_PER_OBJECT: There is only one broadcast replicator per DPSW
 * object. This is the शेष configuration.
 * @DPSW_BROADCAST_PER_FDB: Broadcast replicators are allocated per FDB and
 * पूर्णांकerfaces present in each of them can be configured using
 * dpsw_set_egress_flood().
 */
क्रमागत dpsw_broadcast_cfg अणु
	DPSW_BROADCAST_PER_OBJECT = 0,
	DPSW_BROADCAST_PER_FDB,
पूर्ण;

पूर्णांक dpsw_enable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token);

पूर्णांक dpsw_disable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token);

पूर्णांक dpsw_reset(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token);

/* DPSW IRQ Index and Events */

#घोषणा DPSW_IRQ_INDEX_IF		0x0000
#घोषणा DPSW_IRQ_INDEX_L2SW		0x0001

/**
 * DPSW_IRQ_EVENT_LINK_CHANGED - Indicates that the link state changed
 */
#घोषणा DPSW_IRQ_EVENT_LINK_CHANGED	0x0001

/**
 * काष्ठा dpsw_irq_cfg - IRQ configuration
 * @addr:	Address that must be written to संकेत a message-based पूर्णांकerrupt
 * @val:	Value to ग_लिखो पूर्णांकo irq_addr address
 * @irq_num: A user defined number associated with this IRQ
 */
काष्ठा dpsw_irq_cfg अणु
	u64 addr;
	u32 val;
	पूर्णांक irq_num;
पूर्ण;

पूर्णांक dpsw_set_irq_enable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 irq_index, u8 en);

पूर्णांक dpsw_set_irq_mask(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		      u8 irq_index, u32 mask);

पूर्णांक dpsw_get_irq_status(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 irq_index, u32 *status);

पूर्णांक dpsw_clear_irq_status(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			  u8 irq_index, u32 status);

/**
 * काष्ठा dpsw_attr - Structure representing DPSW attributes
 * @id: DPSW object ID
 * @options: Enable/Disable DPSW features
 * @max_vlans: Maximum Number of VLANs
 * @max_meters_per_अगर:  Number of meters per पूर्णांकerface
 * @max_fdbs: Maximum Number of FDBs
 * @max_fdb_entries: Number of FDB entries क्रम शेष FDB table;
 *			0 - indicates शेष 1024 entries.
 * @fdb_aging_समय: Default FDB aging समय क्रम शेष FDB table;
 *			0 - indicates शेष 300 seconds
 * @max_fdb_mc_groups: Number of multicast groups in each FDB table;
 *			0 - indicates शेष 32
 * @mem_size: DPSW frame storage memory size
 * @num_अगरs: Number of पूर्णांकerfaces
 * @num_vlans: Current number of VLANs
 * @num_fdbs: Current number of FDBs
 * @component_type: Component type of this bridge
 * @flooding_cfg: Flooding configuration (PER_VLAN - शेष, PER_FDB)
 * @broadcast_cfg: Broadcast configuration (PER_OBJECT - शेष, PER_FDB)
 */
काष्ठा dpsw_attr अणु
	पूर्णांक id;
	u64 options;
	u16 max_vlans;
	u8 max_meters_per_अगर;
	u8 max_fdbs;
	u16 max_fdb_entries;
	u16 fdb_aging_समय;
	u16 max_fdb_mc_groups;
	u16 num_अगरs;
	u16 mem_size;
	u16 num_vlans;
	u8 num_fdbs;
	क्रमागत dpsw_component_type component_type;
	क्रमागत dpsw_flooding_cfg flooding_cfg;
	क्रमागत dpsw_broadcast_cfg broadcast_cfg;
पूर्ण;

पूर्णांक dpsw_get_attributes(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			काष्ठा dpsw_attr *attr);

/**
 * काष्ठा dpsw_ctrl_अगर_attr - Control पूर्णांकerface attributes
 * @rx_fqid:		Receive FQID
 * @rx_err_fqid:	Receive error FQID
 * @tx_err_conf_fqid:	Transmit error and confirmation FQID
 */
काष्ठा dpsw_ctrl_अगर_attr अणु
	u32 rx_fqid;
	u32 rx_err_fqid;
	u32 tx_err_conf_fqid;
पूर्ण;

पूर्णांक dpsw_ctrl_अगर_get_attributes(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
				u16 token, काष्ठा dpsw_ctrl_अगर_attr *attr);

क्रमागत dpsw_queue_type अणु
	DPSW_QUEUE_RX,
	DPSW_QUEUE_TX_ERR_CONF,
	DPSW_QUEUE_RX_ERR,
पूर्ण;

#घोषणा DPSW_MAX_DPBP     8

/**
 * काष्ठा dpsw_ctrl_अगर_pools_cfg - Control पूर्णांकerface buffer pools configuration
 * @num_dpbp: Number of DPBPs
 * @pools: Array of buffer pools parameters; The number of valid entries
 *	must match 'num_dpbp' value
 * @pools.dpbp_id: DPBP object ID
 * @pools.buffer_size: Buffer size
 * @pools.backup_pool: Backup pool
 */
काष्ठा dpsw_ctrl_अगर_pools_cfg अणु
	u8 num_dpbp;
	काष्ठा अणु
		पूर्णांक dpbp_id;
		u16 buffer_size;
		पूर्णांक backup_pool;
	पूर्ण pools[DPSW_MAX_DPBP];
पूर्ण;

पूर्णांक dpsw_ctrl_अगर_set_pools(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			   स्थिर काष्ठा dpsw_ctrl_अगर_pools_cfg *cfg);

#घोषणा DPSW_CTRL_IF_QUEUE_OPT_USER_CTX		0x00000001
#घोषणा DPSW_CTRL_IF_QUEUE_OPT_DEST		0x00000002

क्रमागत dpsw_ctrl_अगर_dest अणु
	DPSW_CTRL_IF_DEST_NONE = 0,
	DPSW_CTRL_IF_DEST_DPIO = 1,
पूर्ण;

काष्ठा dpsw_ctrl_अगर_dest_cfg अणु
	क्रमागत dpsw_ctrl_अगर_dest dest_type;
	पूर्णांक dest_id;
	u8 priority;
पूर्ण;

काष्ठा dpsw_ctrl_अगर_queue_cfg अणु
	u32 options;
	u64 user_ctx;
	काष्ठा dpsw_ctrl_अगर_dest_cfg dest_cfg;
पूर्ण;

पूर्णांक dpsw_ctrl_अगर_set_queue(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			   क्रमागत dpsw_queue_type qtype,
			   स्थिर काष्ठा dpsw_ctrl_अगर_queue_cfg *cfg);

पूर्णांक dpsw_ctrl_अगर_enable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token);

पूर्णांक dpsw_ctrl_अगर_disable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token);

/**
 * क्रमागत dpsw_action - Action selection क्रम special/control frames
 * @DPSW_ACTION_DROP: Drop frame
 * @DPSW_ACTION_REसूचीECT: Redirect frame to control port
 */
क्रमागत dpsw_action अणु
	DPSW_ACTION_DROP = 0,
	DPSW_ACTION_REसूचीECT = 1
पूर्ण;

#घोषणा DPSW_LINK_OPT_AUTONEG		0x0000000000000001ULL
#घोषणा DPSW_LINK_OPT_HALF_DUPLEX	0x0000000000000002ULL
#घोषणा DPSW_LINK_OPT_PAUSE		0x0000000000000004ULL
#घोषणा DPSW_LINK_OPT_ASYM_PAUSE	0x0000000000000008ULL

/**
 * काष्ठा dpsw_link_cfg - Structure representing DPSW link configuration
 * @rate: Rate
 * @options: Mask of available options; use 'DPSW_LINK_OPT_<X>' values
 */
काष्ठा dpsw_link_cfg अणु
	u32 rate;
	u64 options;
पूर्ण;

पूर्णांक dpsw_अगर_set_link_cfg(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 अगर_id,
			 काष्ठा dpsw_link_cfg *cfg);

/**
 * काष्ठा dpsw_link_state - Structure representing DPSW link state
 * @rate: Rate
 * @options: Mask of available options; use 'DPSW_LINK_OPT_<X>' values
 * @up: 0 - covers two हालs: करोwn and disconnected, 1 - up
 */
काष्ठा dpsw_link_state अणु
	u32 rate;
	u64 options;
	u8 up;
पूर्ण;

पूर्णांक dpsw_अगर_get_link_state(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			   u16 अगर_id, काष्ठा dpsw_link_state *state);

/**
 * काष्ठा dpsw_tci_cfg - Tag Control Inक्रमmation (TCI) configuration
 * @pcp: Priority Code Poपूर्णांक (PCP): a 3-bit field which refers
 *		 to the IEEE 802.1p priority
 * @dei: Drop Eligible Indicator (DEI): a 1-bit field. May be used
 *		 separately or in conjunction with PCP to indicate frames
 *		 eligible to be dropped in the presence of congestion
 * @vlan_id: VLAN Identअगरier (VID): a 12-bit field specअगरying the VLAN
 *			to which the frame beदीर्घs. The hexadecimal values
 *			of 0x000 and 0xFFF are reserved;
 *			all other values may be used as VLAN identअगरiers,
 *			allowing up to 4,094 VLANs
 */
काष्ठा dpsw_tci_cfg अणु
	u8 pcp;
	u8 dei;
	u16 vlan_id;
पूर्ण;

पूर्णांक dpsw_अगर_set_tci(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 अगर_id,
		    स्थिर काष्ठा dpsw_tci_cfg *cfg);

पूर्णांक dpsw_अगर_get_tci(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 अगर_id,
		    काष्ठा dpsw_tci_cfg *cfg);

/**
 * क्रमागत dpsw_stp_state - Spanning Tree Protocol (STP) states
 * @DPSW_STP_STATE_DISABLED: Disabled state
 * @DPSW_STP_STATE_LISTENING: Listening state
 * @DPSW_STP_STATE_LEARNING: Learning state
 * @DPSW_STP_STATE_FORWARDING: Forwarding state
 * @DPSW_STP_STATE_BLOCKING: Blocking state
 *
 */
क्रमागत dpsw_stp_state अणु
	DPSW_STP_STATE_DISABLED = 0,
	DPSW_STP_STATE_LISTENING = 1,
	DPSW_STP_STATE_LEARNING = 2,
	DPSW_STP_STATE_FORWARDING = 3,
	DPSW_STP_STATE_BLOCKING = 0
पूर्ण;

/**
 * काष्ठा dpsw_stp_cfg - Spanning Tree Protocol (STP) Configuration
 * @vlan_id: VLAN ID STP state
 * @state: STP state
 */
काष्ठा dpsw_stp_cfg अणु
	u16 vlan_id;
	क्रमागत dpsw_stp_state state;
पूर्ण;

पूर्णांक dpsw_अगर_set_stp(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 अगर_id,
		    स्थिर काष्ठा dpsw_stp_cfg *cfg);

/**
 * क्रमागत dpsw_accepted_frames - Types of frames to accept
 * @DPSW_ADMIT_ALL: The device accepts VLAN tagged, untagged and
 *			priority tagged frames
 * @DPSW_ADMIT_ONLY_VLAN_TAGGED: The device discards untagged frames or
 *			Priority-Tagged frames received on this पूर्णांकerface.
 *
 */
क्रमागत dpsw_accepted_frames अणु
	DPSW_ADMIT_ALL = 1,
	DPSW_ADMIT_ONLY_VLAN_TAGGED = 3
पूर्ण;

/**
 * क्रमागत dpsw_counter  - Counters types
 * @DPSW_CNT_ING_FRAME: Counts ingress frames
 * @DPSW_CNT_ING_BYTE: Counts ingress bytes
 * @DPSW_CNT_ING_FLTR_FRAME: Counts filtered ingress frames
 * @DPSW_CNT_ING_FRAME_DISCARD: Counts discarded ingress frame
 * @DPSW_CNT_ING_MCAST_FRAME: Counts ingress multicast frames
 * @DPSW_CNT_ING_MCAST_BYTE: Counts ingress multicast bytes
 * @DPSW_CNT_ING_BCAST_FRAME: Counts ingress broadcast frames
 * @DPSW_CNT_ING_BCAST_BYTES: Counts ingress broadcast bytes
 * @DPSW_CNT_EGR_FRAME: Counts egress frames
 * @DPSW_CNT_EGR_BYTE: Counts egress bytes
 * @DPSW_CNT_EGR_FRAME_DISCARD: Counts discarded egress frames
 * @DPSW_CNT_EGR_STP_FRAME_DISCARD: Counts egress STP discarded frames
 * @DPSW_CNT_ING_NO_BUFF_DISCARD: Counts ingress no buffer discarded frames
 */
क्रमागत dpsw_counter अणु
	DPSW_CNT_ING_FRAME = 0x0,
	DPSW_CNT_ING_BYTE = 0x1,
	DPSW_CNT_ING_FLTR_FRAME = 0x2,
	DPSW_CNT_ING_FRAME_DISCARD = 0x3,
	DPSW_CNT_ING_MCAST_FRAME = 0x4,
	DPSW_CNT_ING_MCAST_BYTE = 0x5,
	DPSW_CNT_ING_BCAST_FRAME = 0x6,
	DPSW_CNT_ING_BCAST_BYTES = 0x7,
	DPSW_CNT_EGR_FRAME = 0x8,
	DPSW_CNT_EGR_BYTE = 0x9,
	DPSW_CNT_EGR_FRAME_DISCARD = 0xa,
	DPSW_CNT_EGR_STP_FRAME_DISCARD = 0xb,
	DPSW_CNT_ING_NO_BUFF_DISCARD = 0xc,
पूर्ण;

पूर्णांक dpsw_अगर_get_counter(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u16 अगर_id, क्रमागत dpsw_counter type, u64 *counter);

पूर्णांक dpsw_अगर_enable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 अगर_id);

पूर्णांक dpsw_अगर_disable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 अगर_id);

/**
 * काष्ठा dpsw_अगर_attr - Structure representing DPSW पूर्णांकerface attributes
 * @num_tcs: Number of traffic classes
 * @rate: Transmit rate in bits per second
 * @options: Interface configuration options (biपंचांगap)
 * @enabled: Indicates अगर पूर्णांकerface is enabled
 * @accept_all_vlan: The device discards/accepts incoming frames
 *		क्रम VLANs that करो not include this पूर्णांकerface
 * @admit_untagged: When set to 'DPSW_ADMIT_ONLY_VLAN_TAGGED', the device
 *		discards untagged frames or priority-tagged frames received on
 *		this पूर्णांकerface;
 *		When set to 'DPSW_ADMIT_ALL', untagged frames or priority-
 *		tagged frames received on this पूर्णांकerface are accepted
 * @qdid: control frames transmit qdid
 */
काष्ठा dpsw_अगर_attr अणु
	u8 num_tcs;
	u32 rate;
	u32 options;
	पूर्णांक enabled;
	पूर्णांक accept_all_vlan;
	क्रमागत dpsw_accepted_frames admit_untagged;
	u16 qdid;
पूर्ण;

पूर्णांक dpsw_अगर_get_attributes(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			   u16 अगर_id, काष्ठा dpsw_अगर_attr *attr);

पूर्णांक dpsw_अगर_set_max_frame_length(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
				 u16 अगर_id, u16 frame_length);

/**
 * काष्ठा dpsw_vlan_cfg - VLAN Configuration
 * @fdb_id: Forwarding Data Base
 */
काष्ठा dpsw_vlan_cfg अणु
	u16 fdb_id;
पूर्ण;

पूर्णांक dpsw_vlan_add(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		  u16 vlan_id, स्थिर काष्ठा dpsw_vlan_cfg *cfg);

#घोषणा DPSW_VLAN_ADD_IF_OPT_FDB_ID            0x0001

/**
 * काष्ठा dpsw_vlan_अगर_cfg - Set of VLAN Interfaces
 * @num_अगरs: The number of पूर्णांकerfaces that are asचिन्हित to the egress
 *		list क्रम this VLAN
 * @अगर_id: The set of पूर्णांकerfaces that are
 *		asचिन्हित to the egress list क्रम this VLAN
 * @options: Options map क्रम this command (DPSW_VLAN_ADD_IF_OPT_FDB_ID)
 * @fdb_id: FDB id to be used by this VLAN on these specअगरic पूर्णांकerfaces
 *		(taken पूर्णांकo account only अगर the DPSW_VLAN_ADD_IF_OPT_FDB_ID is
 *		specअगरied in the options field)
 */
काष्ठा dpsw_vlan_अगर_cfg अणु
	u16 num_अगरs;
	u16 options;
	u16 अगर_id[DPSW_MAX_IF];
	u16 fdb_id;
पूर्ण;

पूर्णांक dpsw_vlan_add_अगर(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		     u16 vlan_id, स्थिर काष्ठा dpsw_vlan_अगर_cfg *cfg);

पूर्णांक dpsw_vlan_add_अगर_untagged(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			      u16 vlan_id, स्थिर काष्ठा dpsw_vlan_अगर_cfg *cfg);

पूर्णांक dpsw_vlan_हटाओ_अगर(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u16 vlan_id, स्थिर काष्ठा dpsw_vlan_अगर_cfg *cfg);

पूर्णांक dpsw_vlan_हटाओ_अगर_untagged(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
				 u16 vlan_id, स्थिर काष्ठा dpsw_vlan_अगर_cfg *cfg);

पूर्णांक dpsw_vlan_हटाओ(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		     u16 vlan_id);

/**
 * क्रमागत dpsw_fdb_entry_type - FDB Entry type - Static/Dynamic
 * @DPSW_FDB_ENTRY_STATIC: Static entry
 * @DPSW_FDB_ENTRY_DINAMIC: Dynamic entry
 */
क्रमागत dpsw_fdb_entry_type अणु
	DPSW_FDB_ENTRY_STATIC = 0,
	DPSW_FDB_ENTRY_DINAMIC = 1
पूर्ण;

/**
 * काष्ठा dpsw_fdb_unicast_cfg - Unicast entry configuration
 * @type: Select अटल or dynamic entry
 * @mac_addr: MAC address
 * @अगर_egress: Egress पूर्णांकerface ID
 */
काष्ठा dpsw_fdb_unicast_cfg अणु
	क्रमागत dpsw_fdb_entry_type type;
	u8 mac_addr[6];
	u16 अगर_egress;
पूर्ण;

पूर्णांक dpsw_fdb_add_unicast(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			 u16 fdb_id, स्थिर काष्ठा dpsw_fdb_unicast_cfg *cfg);

पूर्णांक dpsw_fdb_हटाओ_unicast(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			    u16 fdb_id, स्थिर काष्ठा dpsw_fdb_unicast_cfg *cfg);

#घोषणा DPSW_FDB_ENTRY_TYPE_DYNAMIC  BIT(0)
#घोषणा DPSW_FDB_ENTRY_TYPE_UNICAST  BIT(1)

/**
 * काष्ठा fdb_dump_entry - fdb snapshot entry
 * @mac_addr: MAC address
 * @type: bit0 - DINAMIC(1)/STATIC(0), bit1 - UNICAST(1)/MULTICAST(0)
 * @अगर_info: unicast - egress पूर्णांकerface, multicast - number of egress पूर्णांकerfaces
 * @अगर_mask: multicast - egress पूर्णांकerface mask
 */
काष्ठा fdb_dump_entry अणु
	u8 mac_addr[6];
	u8 type;
	u8 अगर_info;
	u8 अगर_mask[8];
पूर्ण;

पूर्णांक dpsw_fdb_dump(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 fdb_id,
		  u64 iova_addr, u32 iova_size, u16 *num_entries);

/**
 * काष्ठा dpsw_fdb_multicast_cfg - Multi-cast entry configuration
 * @type: Select अटल or dynamic entry
 * @mac_addr: MAC address
 * @num_अगरs: Number of बाह्यal and पूर्णांकernal पूर्णांकerfaces
 * @अगर_id: Egress पूर्णांकerface IDs
 */
काष्ठा dpsw_fdb_multicast_cfg अणु
	क्रमागत dpsw_fdb_entry_type type;
	u8 mac_addr[6];
	u16 num_अगरs;
	u16 अगर_id[DPSW_MAX_IF];
पूर्ण;

पूर्णांक dpsw_fdb_add_multicast(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			   u16 fdb_id, स्थिर काष्ठा dpsw_fdb_multicast_cfg *cfg);

पूर्णांक dpsw_fdb_हटाओ_multicast(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			      u16 fdb_id, स्थिर काष्ठा dpsw_fdb_multicast_cfg *cfg);

/**
 * क्रमागत dpsw_learning_mode - Auto-learning modes
 * @DPSW_LEARNING_MODE_DIS: Disable Auto-learning
 * @DPSW_LEARNING_MODE_HW: Enable HW स्वतः-Learning
 * @DPSW_LEARNING_MODE_NON_SECURE: Enable None secure learning by CPU
 * @DPSW_LEARNING_MODE_SECURE: Enable secure learning by CPU
 *
 *	NONE - SECURE LEARNING
 *	SMAC found	DMAC found	CTLU Action
 *	v		v	Forward frame to
 *						1.  DMAC destination
 *	-		v	Forward frame to
 *						1.  DMAC destination
 *						2.  Control पूर्णांकerface
 *	v		-	Forward frame to
 *						1.  Flooding list of पूर्णांकerfaces
 *	-		-	Forward frame to
 *						1.  Flooding list of पूर्णांकerfaces
 *						2.  Control पूर्णांकerface
 *	SECURE LEARING
 *	SMAC found	DMAC found	CTLU Action
 *	v		v		Forward frame to
 *						1.  DMAC destination
 *	-		v		Forward frame to
 *						1.  Control पूर्णांकerface
 *	v		-		Forward frame to
 *						1.  Flooding list of पूर्णांकerfaces
 *	-		-		Forward frame to
 *						1.  Control पूर्णांकerface
 */
क्रमागत dpsw_learning_mode अणु
	DPSW_LEARNING_MODE_DIS = 0,
	DPSW_LEARNING_MODE_HW = 1,
	DPSW_LEARNING_MODE_NON_SECURE = 2,
	DPSW_LEARNING_MODE_SECURE = 3
पूर्ण;

/**
 * काष्ठा dpsw_fdb_attr - FDB Attributes
 * @max_fdb_entries: Number of FDB entries
 * @fdb_ageing_समय: Ageing समय in seconds
 * @learning_mode: Learning mode
 * @num_fdb_mc_groups: Current number of multicast groups
 * @max_fdb_mc_groups: Maximum number of multicast groups
 */
काष्ठा dpsw_fdb_attr अणु
	u16 max_fdb_entries;
	u16 fdb_ageing_समय;
	क्रमागत dpsw_learning_mode learning_mode;
	u16 num_fdb_mc_groups;
	u16 max_fdb_mc_groups;
पूर्ण;

पूर्णांक dpsw_get_api_version(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
			 u16 *major_ver, u16 *minor_ver);

पूर्णांक dpsw_अगर_get_port_mac_addr(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			      u16 अगर_id, u8 mac_addr[6]);

/**
 * काष्ठा dpsw_fdb_cfg  - FDB Configuration
 * @num_fdb_entries: Number of FDB entries
 * @fdb_ageing_समय: Ageing समय in seconds
 */
काष्ठा dpsw_fdb_cfg अणु
	u16 num_fdb_entries;
	u16 fdb_ageing_समय;
पूर्ण;

पूर्णांक dpsw_fdb_add(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 *fdb_id,
		 स्थिर काष्ठा dpsw_fdb_cfg *cfg);

पूर्णांक dpsw_fdb_हटाओ(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 fdb_id);

/**
 * क्रमागत dpsw_flood_type - Define the flood type of a DPSW object
 * @DPSW_BROADCAST: Broadcast flooding
 * @DPSW_FLOODING: Unknown flooding
 */
क्रमागत dpsw_flood_type अणु
	DPSW_BROADCAST = 0,
	DPSW_FLOODING,
पूर्ण;

काष्ठा dpsw_egress_flood_cfg अणु
	u16 fdb_id;
	क्रमागत dpsw_flood_type flood_type;
	u16 num_अगरs;
	u16 अगर_id[DPSW_MAX_IF];
पूर्ण;

पूर्णांक dpsw_set_egress_flood(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			  स्थिर काष्ठा dpsw_egress_flood_cfg *cfg);

पूर्णांक dpsw_अगर_set_learning_mode(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			      u16 अगर_id, क्रमागत dpsw_learning_mode mode);

/**
 * काष्ठा dpsw_acl_cfg - ACL Configuration
 * @max_entries: Number of ACL rules
 */
काष्ठा dpsw_acl_cfg अणु
	u16 max_entries;
पूर्ण;

पूर्णांक dpsw_acl_add(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token, u16 *acl_id,
		 स्थिर काष्ठा dpsw_acl_cfg *cfg);

पूर्णांक dpsw_acl_हटाओ(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		    u16 acl_id);

/**
 * काष्ठा dpsw_acl_अगर_cfg - List of पूर्णांकerfaces to associate with an ACL table
 * @num_अगरs: Number of पूर्णांकerfaces
 * @अगर_id: List of पूर्णांकerfaces
 */
काष्ठा dpsw_acl_अगर_cfg अणु
	u16 num_अगरs;
	u16 अगर_id[DPSW_MAX_IF];
पूर्ण;

पूर्णांक dpsw_acl_add_अगर(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		    u16 acl_id, स्थिर काष्ठा dpsw_acl_अगर_cfg *cfg);

पूर्णांक dpsw_acl_हटाओ_अगर(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		       u16 acl_id, स्थिर काष्ठा dpsw_acl_अगर_cfg *cfg);

/**
 * काष्ठा dpsw_acl_fields - ACL fields.
 * @l2_dest_mac: Destination MAC address: BPDU, Multicast, Broadcast, Unicast,
 *			slow protocols, MVRP, STP
 * @l2_source_mac: Source MAC address
 * @l2_tpid: Layer 2 (Ethernet) protocol type, used to identअगरy the following
 *		protocols: MPLS, PTP, PFC, ARP, Jumbo frames, LLDP, IEEE802.1ae,
 *		Q-in-Q, IPv4, IPv6, PPPoE
 * @l2_pcp_dei: indicate which protocol is encapsulated in the payload
 * @l2_vlan_id: layer 2 VLAN ID
 * @l2_ether_type: layer 2 Ethernet type
 * @l3_dscp: Layer 3 dअगरferentiated services code poपूर्णांक
 * @l3_protocol: Tells the Network layer at the destination host, to which
 *		Protocol this packet beदीर्घs to. The following protocol are
 *		supported: ICMP, IGMP, IPv4 (encapsulation), TCP, IPv6
 *		(encapsulation), GRE, PTP
 * @l3_source_ip: Source IPv4 IP
 * @l3_dest_ip: Destination IPv4 IP
 * @l4_source_port: Source TCP/UDP Port
 * @l4_dest_port: Destination TCP/UDP Port
 */
काष्ठा dpsw_acl_fields अणु
	u8 l2_dest_mac[6];
	u8 l2_source_mac[6];
	u16 l2_tpid;
	u8 l2_pcp_dei;
	u16 l2_vlan_id;
	u16 l2_ether_type;
	u8 l3_dscp;
	u8 l3_protocol;
	u32 l3_source_ip;
	u32 l3_dest_ip;
	u16 l4_source_port;
	u16 l4_dest_port;
पूर्ण;

/**
 * काष्ठा dpsw_acl_key - ACL key
 * @match: Match fields
 * @mask: Mask: b'1 - valid, b'0 don't care
 */
काष्ठा dpsw_acl_key अणु
	काष्ठा dpsw_acl_fields match;
	काष्ठा dpsw_acl_fields mask;
पूर्ण;

/**
 * क्रमागत dpsw_acl_action - action to be run on the ACL rule match
 * @DPSW_ACL_ACTION_DROP: Drop frame
 * @DPSW_ACL_ACTION_REसूचीECT: Redirect to certain port
 * @DPSW_ACL_ACTION_ACCEPT: Accept frame
 * @DPSW_ACL_ACTION_REसूचीECT_TO_CTRL_IF: Redirect to control पूर्णांकerface
 */
क्रमागत dpsw_acl_action अणु
	DPSW_ACL_ACTION_DROP,
	DPSW_ACL_ACTION_REसूचीECT,
	DPSW_ACL_ACTION_ACCEPT,
	DPSW_ACL_ACTION_REसूचीECT_TO_CTRL_IF
पूर्ण;

/**
 * काष्ठा dpsw_acl_result - ACL action
 * @action: Action should be taken when	ACL entry hit
 * @अगर_id:  Interface IDs to redirect frame. Valid only अगर redirect selected क्रम
 *		 action
 */
काष्ठा dpsw_acl_result अणु
	क्रमागत dpsw_acl_action action;
	u16 अगर_id;
पूर्ण;

/**
 * काष्ठा dpsw_acl_entry_cfg - ACL entry
 * @key_iova: I/O भव address of DMA-able memory filled with key after call
 *				to dpsw_acl_prepare_entry_cfg()
 * @result: Required action when entry hit occurs
 * @precedence: Precedence inside ACL 0 is lowest; This priority can not change
 *		during the lअगरeसमय of a Policy. It is user responsibility to
 *		space the priorities according to consequent rule additions.
 */
काष्ठा dpsw_acl_entry_cfg अणु
	u64 key_iova;
	काष्ठा dpsw_acl_result result;
	पूर्णांक precedence;
पूर्ण;

व्योम dpsw_acl_prepare_entry_cfg(स्थिर काष्ठा dpsw_acl_key *key,
				u8 *entry_cfg_buf);

पूर्णांक dpsw_acl_add_entry(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
		       u16 acl_id, स्थिर काष्ठा dpsw_acl_entry_cfg *cfg);

पूर्णांक dpsw_acl_हटाओ_entry(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			  u16 acl_id, स्थिर काष्ठा dpsw_acl_entry_cfg *cfg);
#पूर्ण_अगर /* __FSL_DPSW_H */
