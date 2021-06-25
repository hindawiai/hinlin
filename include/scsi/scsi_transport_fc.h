<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  FiberChannel transport specअगरic attributes exported to sysfs.
 *
 *  Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.
 *  Copyright (C) 2004-2007   James Smart, Emulex Corporation
 *    Reग_लिखो क्रम host, target, device, and remote port attributes,
 *    statistics, and service functions...
 */
#अगर_अघोषित SCSI_TRANSPORT_FC_H
#घोषणा SCSI_TRANSPORT_FC_H

#समावेश <linux/sched.h>
#समावेश <linux/bsg-lib.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_netlink.h>
#समावेश <scsi/scsi_host.h>

काष्ठा scsi_transport_ढाँचा;

/*
 * FC Port definitions - Following FC HBAAPI guidelines
 *
 * Note: Not all binary values क्रम the dअगरferent fields match HBAAPI.
 *  Instead, we use densely packed ordinal values or क्रमागतs.
 *  We get away with this as we never present the actual binary values
 *  बाह्यally. For sysfs, we always present the string that describes
 *  the value. Thus, an admin करोesn't need a magic HBAAPI decoder ring
 *  to understand the values. The HBAAPI user-space library is मुक्त to
 *  convert the strings पूर्णांकo the HBAAPI-specअगरied binary values.
 *
 * Note: Not all HBAAPI-defined values are contained in the definitions
 *  below. Those not appropriate to an fc_host (e.g. FCP initiator) have
 *  been हटाओd.
 */

/*
 * fc_port_type: If you alter this, you also need to alter scsi_transport_fc.c
 * (क्रम the ascii descriptions).
 */
क्रमागत fc_port_type अणु
	FC_PORTTYPE_UNKNOWN,
	FC_PORTTYPE_OTHER,
	FC_PORTTYPE_NOTPRESENT,
	FC_PORTTYPE_NPORT,		/* Attached to FPort */
	FC_PORTTYPE_NLPORT,		/* (Public) Loop w/ FLPort */
	FC_PORTTYPE_LPORT,		/* (Private) Loop w/o FLPort */
	FC_PORTTYPE_PTP,		/* Poपूर्णांक to Poपूर्णांक w/ another NPort */
	FC_PORTTYPE_NPIV,		/* VPORT based on NPIV */
पूर्ण;


/*
 * fc_port_state: If you alter this, you also need to alter scsi_transport_fc.c
 * (क्रम the ascii descriptions).
 */
क्रमागत fc_port_state अणु
	FC_PORTSTATE_UNKNOWN,
	FC_PORTSTATE_NOTPRESENT,
	FC_PORTSTATE_ONLINE,
	FC_PORTSTATE_OFFLINE,		/* User has taken Port Offline */
	FC_PORTSTATE_BLOCKED,
	FC_PORTSTATE_BYPASSED,
	FC_PORTSTATE_DIAGNOSTICS,
	FC_PORTSTATE_LINKDOWN,
	FC_PORTSTATE_ERROR,
	FC_PORTSTATE_LOOPBACK,
	FC_PORTSTATE_DELETED,
	FC_PORTSTATE_MARGINAL,
पूर्ण;


/*
 * fc_vport_state: If you alter this, you also need to alter
 * scsi_transport_fc.c (क्रम the ascii descriptions).
 */
क्रमागत fc_vport_state अणु
	FC_VPORT_UNKNOWN,
	FC_VPORT_ACTIVE,
	FC_VPORT_DISABLED,
	FC_VPORT_LINKDOWN,
	FC_VPORT_INITIALIZING,
	FC_VPORT_NO_FABRIC_SUPP,
	FC_VPORT_NO_FABRIC_RSCS,
	FC_VPORT_FABRIC_LOGOUT,
	FC_VPORT_FABRIC_REJ_WWN,
	FC_VPORT_FAILED,
पूर्ण;



/*
 * FC Classes of Service
 * Note: values are not क्रमागतerated, as they can be "or'd" together
 * क्रम reporting (e.g. report supported_classes). If you alter this list,
 * you also need to alter scsi_transport_fc.c (क्रम the ascii descriptions).
 */
#घोषणा FC_COS_UNSPECIFIED		0
#घोषणा FC_COS_CLASS1			2
#घोषणा FC_COS_CLASS2			4
#घोषणा FC_COS_CLASS3			8
#घोषणा FC_COS_CLASS4			0x10
#घोषणा FC_COS_CLASS6			0x40

/*
 * FC Port Speeds
 * Note: values are not क्रमागतerated, as they can be "or'd" together
 * क्रम reporting (e.g. report supported_speeds). If you alter this list,
 * you also need to alter scsi_transport_fc.c (क्रम the ascii descriptions).
 */
#घोषणा FC_PORTSPEED_UNKNOWN		0 /* Unknown - transceiver
					     incapable of reporting */
#घोषणा FC_PORTSPEED_1GBIT		1
#घोषणा FC_PORTSPEED_2GBIT		2
#घोषणा FC_PORTSPEED_10GBIT		4
#घोषणा FC_PORTSPEED_4GBIT		8
#घोषणा FC_PORTSPEED_8GBIT		0x10
#घोषणा FC_PORTSPEED_16GBIT		0x20
#घोषणा FC_PORTSPEED_32GBIT		0x40
#घोषणा FC_PORTSPEED_20GBIT		0x80
#घोषणा FC_PORTSPEED_40GBIT		0x100
#घोषणा FC_PORTSPEED_50GBIT		0x200
#घोषणा FC_PORTSPEED_100GBIT		0x400
#घोषणा FC_PORTSPEED_25GBIT		0x800
#घोषणा FC_PORTSPEED_64GBIT		0x1000
#घोषणा FC_PORTSPEED_128GBIT		0x2000
#घोषणा FC_PORTSPEED_256GBIT		0x4000
#घोषणा FC_PORTSPEED_NOT_NEGOTIATED	(1 << 15) /* Speed not established */

/*
 * fc_tgtid_binding_type: If you alter this, you also need to alter
 * scsi_transport_fc.c (क्रम the ascii descriptions).
 */
क्रमागत fc_tgtid_binding_type  अणु
	FC_TGTID_BIND_NONE,
	FC_TGTID_BIND_BY_WWPN,
	FC_TGTID_BIND_BY_WWNN,
	FC_TGTID_BIND_BY_ID,
पूर्ण;

/*
 * FC Port Roles
 * Note: values are not क्रमागतerated, as they can be "or'd" together
 * क्रम reporting (e.g. report roles). If you alter this list,
 * you also need to alter scsi_transport_fc.c (क्रम the ascii descriptions).
 */
#घोषणा FC_PORT_ROLE_UNKNOWN			0x00
#घोषणा FC_PORT_ROLE_FCP_TARGET			0x01
#घोषणा FC_PORT_ROLE_FCP_INITIATOR		0x02
#घोषणा FC_PORT_ROLE_IP_PORT			0x04
#घोषणा FC_PORT_ROLE_FCP_DUMMY_INITIATOR	0x08
#घोषणा FC_PORT_ROLE_NVME_INITIATOR		0x10
#घोषणा FC_PORT_ROLE_NVME_TARGET		0x20
#घोषणा FC_PORT_ROLE_NVME_DISCOVERY		0x40

/* The following are क्रम compatibility */
#घोषणा FC_RPORT_ROLE_UNKNOWN			FC_PORT_ROLE_UNKNOWN
#घोषणा FC_RPORT_ROLE_FCP_TARGET		FC_PORT_ROLE_FCP_TARGET
#घोषणा FC_RPORT_ROLE_FCP_INITIATOR		FC_PORT_ROLE_FCP_INITIATOR
#घोषणा FC_RPORT_ROLE_IP_PORT			FC_PORT_ROLE_IP_PORT


/* Macro क्रम use in defining Virtual Port attributes */
#घोषणा FC_VPORT_ATTR(_name,_mode,_show,_store)		\
काष्ठा device_attribute dev_attr_vport_##_name = 	\
	__ATTR(_name,_mode,_show,_store)

/*
 * fc_vport_identअगरiers: This set of data contains all elements
 * to uniquely identअगरy and instantiate a FC भव port.
 *
 * Notes:
 *   symbolic_name: The driver is to append the symbolic_name string data
 *      to the symbolic_node_name data that it generates by शेष.
 *      the resulting combination should then be रेजिस्टरed with the चयन.
 *      It is expected that things like Xen may stuff a VM title पूर्णांकo
 *      this field.
 */
#घोषणा FC_VPORT_SYMBOLIC_NAMELEN		64
काष्ठा fc_vport_identअगरiers अणु
	u64 node_name;
	u64 port_name;
	u32 roles;
	bool disable;
	क्रमागत fc_port_type vport_type;	/* only FC_PORTTYPE_NPIV allowed */
	अक्षर symbolic_name[FC_VPORT_SYMBOLIC_NAMELEN];
पूर्ण;

/*
 * FC Virtual Port Attributes
 *
 * This काष्ठाure exists क्रम each FC port is a भव FC port. Virtual
 * ports share the physical link with the Physical port. Each भव
 * ports has a unique presence on the SAN, and may be instantiated via
 * NPIV, Virtual Fabrics, or via additional ALPAs. As the vport is a
 * unique presence, each vport has it's own view of the fabric,
 * authentication privilege, and priorities.
 *
 * A भव port may support 1 or more FC4 roles. Typically it is a
 * FCP Initiator. It could be a FCP Target, or exist sole क्रम an IP over FC
 * roles. FC port attributes क्रम the vport will be reported on any
 * fc_host class object allocated क्रम an FCP Initiator.
 *
 * --
 *
 * Fixed attributes are not expected to change. The driver is
 * expected to set these values after receiving the fc_vport काष्ठाure
 * via the vport_create() call from the transport.
 * The transport fully manages all get functions w/o driver पूर्णांकeraction.
 *
 * Dynamic attributes are expected to change. The driver participates
 * in all get/set operations via functions provided by the driver.
 *
 * Private attributes are transport-managed values. They are fully
 * managed by the transport w/o driver पूर्णांकeraction.
 */

काष्ठा fc_vport अणु
	/* Fixed Attributes */

	/* Dynamic Attributes */

	/* Private (Transport-managed) Attributes */
	क्रमागत fc_vport_state vport_state;
	क्रमागत fc_vport_state vport_last_state;
	u64 node_name;
	u64 port_name;
	u32 roles;
	u32 vport_id;		/* Admin Identअगरier क्रम the vport */
	क्रमागत fc_port_type vport_type;
	अक्षर symbolic_name[FC_VPORT_SYMBOLIC_NAMELEN];

	/* exported data */
	व्योम *dd_data;			/* Used क्रम driver-specअगरic storage */

	/* पूर्णांकernal data */
	काष्ठा Scsi_Host *shost;	/* Physical Port Parent */
	अचिन्हित पूर्णांक channel;
	u32 number;
	u8 flags;
	काष्ठा list_head peers;
	काष्ठा device dev;
	काष्ठा work_काष्ठा vport_delete_work;
पूर्ण __attribute__((aligned(माप(अचिन्हित दीर्घ))));

/* bit field values क्रम काष्ठा fc_vport "flags" field: */
#घोषणा FC_VPORT_CREATING		0x01
#घोषणा FC_VPORT_DELETING		0x02
#घोषणा FC_VPORT_DELETED		0x04
#घोषणा FC_VPORT_DEL			0x06	/* Any DELETE state */

#घोषणा	dev_to_vport(d)				\
	container_of(d, काष्ठा fc_vport, dev)
#घोषणा transport_class_to_vport(dev)		\
	dev_to_vport(dev->parent)
#घोषणा vport_to_shost(v)			\
	(v->shost)
#घोषणा vport_to_shost_channel(v)		\
	(v->channel)
#घोषणा vport_to_parent(v)			\
	(v->dev.parent)


/* Error वापस codes क्रम vport_create() callback */
#घोषणा VPCERR_UNSUPPORTED		-ENOSYS		/* no driver/adapter
							   support */
#घोषणा VPCERR_BAD_WWN			-ENOTUNIQ	/* driver validation
							   of WWNs failed */
#घोषणा VPCERR_NO_FABRIC_SUPP		-EOPNOTSUPP	/* Fabric connection
							   is loop or the
							   Fabric Port करोes
							   not support NPIV */

/*
 * fc_rport_identअगरiers: This set of data contains all elements
 * to uniquely identअगरy a remote FC port. The driver uses this data
 * to report the existence of a remote FC port in the topology. Internally,
 * the transport uses this data क्रम attributes and to manage consistent
 * target id bindings.
 */
काष्ठा fc_rport_identअगरiers अणु
	u64 node_name;
	u64 port_name;
	u32 port_id;
	u32 roles;
पूर्ण;

/*
 * Fabric Perक्रमmance Impact Notअगरication Statistics
 */
काष्ठा fc_fpin_stats अणु
	/* Delivery */
	u64 dn;
	u64 dn_unknown;
	u64 dn_समयout;
	u64 dn_unable_to_route;
	u64 dn_device_specअगरic;

	/* Link Integrity */
	u64 li;
	u64 li_failure_unknown;
	u64 li_link_failure_count;
	u64 li_loss_of_sync_count;
	u64 li_loss_of_संकेतs_count;
	u64 li_prim_seq_err_count;
	u64 li_invalid_tx_word_count;
	u64 li_invalid_crc_count;
	u64 li_device_specअगरic;

	/* Congestion/Peer Congestion */
	u64 cn;
	u64 cn_clear;
	u64 cn_lost_credit;
	u64 cn_credit_stall;
	u64 cn_oversubscription;
	u64 cn_device_specअगरic;
पूर्ण;

/* Macro क्रम use in defining Remote Port attributes */
#घोषणा FC_RPORT_ATTR(_name,_mode,_show,_store)				\
काष्ठा device_attribute dev_attr_rport_##_name = 	\
	__ATTR(_name,_mode,_show,_store)


/*
 * FC Remote Port Attributes
 *
 * This काष्ठाure exists क्रम each remote FC port that a LLDD notअगरies
 * the subप्रणाली of.  A remote FC port may or may not be a SCSI Target,
 * also be a SCSI initiator, IP endpoपूर्णांक, etc. As such, the remote
 * port is considered a separate entity, independent of "role" (such
 * as scsi target).
 *
 * --
 *
 * Attributes are based on HBAAPI V2.0 definitions. Only those
 * attributes that are determinable by the local port (aka Host)
 * are contained.
 *
 * Fixed attributes are not expected to change. The driver is
 * expected to set these values after successfully calling
 * fc_remote_port_add(). The transport fully manages all get functions
 * w/o driver पूर्णांकeraction.
 *
 * Dynamic attributes are expected to change. The driver participates
 * in all get/set operations via functions provided by the driver.
 *
 * Private attributes are transport-managed values. They are fully
 * managed by the transport w/o driver पूर्णांकeraction.
 */

काष्ठा fc_rport अणु	/* aka fc_starget_attrs */
	/* Fixed Attributes */
	u32 maxframe_size;
	u32 supported_classes;

	/* Dynamic Attributes */
	u32 dev_loss_पंचांगo;	/* Remote Port loss समयout in seconds. */
	काष्ठा fc_fpin_stats fpin_stats;

	/* Private (Transport-managed) Attributes */
	u64 node_name;
	u64 port_name;
	u32 port_id;
	u32 roles;
	क्रमागत fc_port_state port_state;	/* Will only be ONLINE or UNKNOWN */
	u32 scsi_target_id;
	u32 fast_io_fail_पंचांगo;

	/* exported data */
	व्योम *dd_data;			/* Used क्रम driver-specअगरic storage */

	/* पूर्णांकernal data */
	अचिन्हित पूर्णांक channel;
	u32 number;
	u8 flags;
	काष्ठा list_head peers;
	काष्ठा device dev;
 	काष्ठा delayed_work dev_loss_work;
 	काष्ठा work_काष्ठा scan_work;
 	काष्ठा delayed_work fail_io_work;
 	काष्ठा work_काष्ठा stgt_delete_work;
	काष्ठा work_काष्ठा rport_delete_work;
	काष्ठा request_queue *rqst_q;	/* bsg support */
पूर्ण __attribute__((aligned(माप(अचिन्हित दीर्घ))));

/* bit field values क्रम काष्ठा fc_rport "flags" field: */
#घोषणा FC_RPORT_DEVLOSS_PENDING	0x01
#घोषणा FC_RPORT_SCAN_PENDING		0x02
#घोषणा FC_RPORT_FAST_FAIL_TIMEDOUT	0x04
#घोषणा FC_RPORT_DEVLOSS_CALLBK_DONE	0x08

#घोषणा	dev_to_rport(d)				\
	container_of(d, काष्ठा fc_rport, dev)
#घोषणा transport_class_to_rport(dev)	\
	dev_to_rport(dev->parent)
#घोषणा rport_to_shost(r)			\
	dev_to_shost(r->dev.parent)

/*
 * FC SCSI Target Attributes
 *
 * The SCSI Target is considered an extension of a remote port (as
 * a remote port can be more than a SCSI Target). Within the scsi
 * subप्रणाली, we leave the Target as a separate entity. Doing so
 * provides backward compatibility with prior FC transport api's,
 * and lets remote ports be handled entirely within the FC transport
 * and independently from the scsi subप्रणाली. The drawback is that
 * some data will be duplicated.
 */

काष्ठा fc_starget_attrs अणु	/* aka fc_target_attrs */
	/* Dynamic Attributes */
	u64 node_name;
	u64 port_name;
	u32 port_id;
पूर्ण;

#घोषणा fc_starget_node_name(x) \
	(((काष्ठा fc_starget_attrs *)&(x)->starget_data)->node_name)
#घोषणा fc_starget_port_name(x)	\
	(((काष्ठा fc_starget_attrs *)&(x)->starget_data)->port_name)
#घोषणा fc_starget_port_id(x) \
	(((काष्ठा fc_starget_attrs *)&(x)->starget_data)->port_id)

#घोषणा starget_to_rport(s)			\
	scsi_is_fc_rport(s->dev.parent) ? dev_to_rport(s->dev.parent) : शून्य


/*
 * FC Local Port (Host) Statistics
 */

/* FC Statistics - Following FC HBAAPI v2.0 guidelines */
काष्ठा fc_host_statistics अणु
	/* port statistics */
	u64 seconds_since_last_reset;
	u64 tx_frames;
	u64 tx_words;
	u64 rx_frames;
	u64 rx_words;
	u64 lip_count;
	u64 nos_count;
	u64 error_frames;
	u64 dumped_frames;
	u64 link_failure_count;
	u64 loss_of_sync_count;
	u64 loss_of_संकेत_count;
	u64 prim_seq_protocol_err_count;
	u64 invalid_tx_word_count;
	u64 invalid_crc_count;

	/* fc4 statistics  (only FCP supported currently) */
	u64 fcp_input_requests;
	u64 fcp_output_requests;
	u64 fcp_control_requests;
	u64 fcp_input_megabytes;
	u64 fcp_output_megabytes;
	u64 fcp_packet_alloc_failures;	/* fcp packet allocation failures */
	u64 fcp_packet_पातs;		/* fcp packet पातed */
	u64 fcp_frame_alloc_failures;	/* fcp frame allocation failures */

	/* fc exches statistics */
	u64 fc_no_मुक्त_exch;		/* no मुक्त exch memory */
	u64 fc_no_मुक्त_exch_xid;	/* no मुक्त exch id */
	u64 fc_xid_not_found;		/* exch not found क्रम a response */
	u64 fc_xid_busy;		/* exch exist क्रम new a request */
	u64 fc_seq_not_found;		/* seq is not found क्रम exchange */
	u64 fc_non_bls_resp;		/* a non BLS response frame with
					   a sequence responder in new exch */
	/* Host Congestion Signals */
	u64 cn_sig_warn;
	u64 cn_sig_alarm;
पूर्ण;


/*
 * FC Event Codes - Polled and Async, following FC HBAAPI v2.0 guidelines
 */

/*
 * fc_host_event_code: If you alter this, you also need to alter
 * scsi_transport_fc.c (क्रम the ascii descriptions).
 */
क्रमागत fc_host_event_code  अणु
	FCH_EVT_LIP			= 0x1,
	FCH_EVT_LINKUP			= 0x2,
	FCH_EVT_LINKDOWN		= 0x3,
	FCH_EVT_LIPRESET		= 0x4,
	FCH_EVT_RSCN			= 0x5,
	FCH_EVT_ADAPTER_CHANGE		= 0x103,
	FCH_EVT_PORT_UNKNOWN		= 0x200,
	FCH_EVT_PORT_OFFLINE		= 0x201,
	FCH_EVT_PORT_ONLINE		= 0x202,
	FCH_EVT_PORT_FABRIC		= 0x204,
	FCH_EVT_LINK_UNKNOWN		= 0x500,
	FCH_EVT_LINK_FPIN		= 0x501,
	FCH_EVT_VENDOR_UNIQUE		= 0xffff,
पूर्ण;


/*
 * FC Local Port (Host) Attributes
 *
 * Attributes are based on HBAAPI V2.0 definitions.
 * Note: OSDeviceName is determined by user-space library
 *
 * Fixed attributes are not expected to change. The driver is
 * expected to set these values after successfully calling scsi_add_host().
 * The transport fully manages all get functions w/o driver पूर्णांकeraction.
 *
 * Dynamic attributes are expected to change. The driver participates
 * in all get/set operations via functions provided by the driver.
 *
 * Private attributes are transport-managed values. They are fully
 * managed by the transport w/o driver पूर्णांकeraction.
 */

#घोषणा FC_FC4_LIST_SIZE		32
#घोषणा FC_SYMBOLIC_NAME_SIZE		256
#घोषणा FC_VERSION_STRING_SIZE		64
#घोषणा FC_SERIAL_NUMBER_SIZE		80

काष्ठा fc_host_attrs अणु
	/* Fixed Attributes */
	u64 node_name;
	u64 port_name;
	u64 permanent_port_name;
	u32 supported_classes;
	u8  supported_fc4s[FC_FC4_LIST_SIZE];
	u32 supported_speeds;
	u32 maxframe_size;
	u16 max_npiv_vports;
	अक्षर serial_number[FC_SERIAL_NUMBER_SIZE];
	अक्षर manufacturer[FC_SERIAL_NUMBER_SIZE];
	अक्षर model[FC_SYMBOLIC_NAME_SIZE];
	अक्षर model_description[FC_SYMBOLIC_NAME_SIZE];
	अक्षर hardware_version[FC_VERSION_STRING_SIZE];
	अक्षर driver_version[FC_VERSION_STRING_SIZE];
	अक्षर firmware_version[FC_VERSION_STRING_SIZE];
	अक्षर optionrom_version[FC_VERSION_STRING_SIZE];

	/* Dynamic Attributes */
	u32 port_id;
	क्रमागत fc_port_type port_type;
	क्रमागत fc_port_state port_state;
	u8  active_fc4s[FC_FC4_LIST_SIZE];
	u32 speed;
	u64 fabric_name;
	अक्षर symbolic_name[FC_SYMBOLIC_NAME_SIZE];
	अक्षर प्रणाली_hostname[FC_SYMBOLIC_NAME_SIZE];
	u32 dev_loss_पंचांगo;
	काष्ठा fc_fpin_stats fpin_stats;

	/* Private (Transport-managed) Attributes */
	क्रमागत fc_tgtid_binding_type  tgtid_bind_type;

	/* पूर्णांकernal data */
	काष्ठा list_head rports;
	काष्ठा list_head rport_bindings;
	काष्ठा list_head vports;
	u32 next_rport_number;
	u32 next_target_id;
	u32 next_vport_number;
	u16 npiv_vports_inuse;

	/* work queues क्रम rport state manipulation */
	अक्षर work_q_name[20];
	काष्ठा workqueue_काष्ठा *work_q;
	अक्षर devloss_work_q_name[20];
	काष्ठा workqueue_काष्ठा *devloss_work_q;

	/* bsg support */
	काष्ठा request_queue *rqst_q;
पूर्ण;

#घोषणा shost_to_fc_host(x) \
	((काष्ठा fc_host_attrs *)(x)->shost_data)

#घोषणा fc_host_node_name(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->node_name)
#घोषणा fc_host_port_name(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->port_name)
#घोषणा fc_host_permanent_port_name(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->permanent_port_name)
#घोषणा fc_host_supported_classes(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->supported_classes)
#घोषणा fc_host_supported_fc4s(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->supported_fc4s)
#घोषणा fc_host_supported_speeds(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->supported_speeds)
#घोषणा fc_host_maxframe_size(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->maxframe_size)
#घोषणा fc_host_max_npiv_vports(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->max_npiv_vports)
#घोषणा fc_host_serial_number(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->serial_number)
#घोषणा fc_host_manufacturer(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->manufacturer)
#घोषणा fc_host_model(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->model)
#घोषणा fc_host_model_description(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->model_description)
#घोषणा fc_host_hardware_version(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->hardware_version)
#घोषणा fc_host_driver_version(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->driver_version)
#घोषणा fc_host_firmware_version(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->firmware_version)
#घोषणा fc_host_optionrom_version(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->optionrom_version)
#घोषणा fc_host_port_id(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->port_id)
#घोषणा fc_host_port_type(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->port_type)
#घोषणा fc_host_port_state(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->port_state)
#घोषणा fc_host_active_fc4s(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->active_fc4s)
#घोषणा fc_host_speed(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->speed)
#घोषणा fc_host_fabric_name(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->fabric_name)
#घोषणा fc_host_symbolic_name(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->symbolic_name)
#घोषणा fc_host_प्रणाली_hostname(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->प्रणाली_hostname)
#घोषणा fc_host_tgtid_bind_type(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->tgtid_bind_type)
#घोषणा fc_host_rports(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->rports)
#घोषणा fc_host_rport_bindings(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->rport_bindings)
#घोषणा fc_host_vports(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->vports)
#घोषणा fc_host_next_rport_number(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->next_rport_number)
#घोषणा fc_host_next_target_id(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->next_target_id)
#घोषणा fc_host_next_vport_number(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->next_vport_number)
#घोषणा fc_host_npiv_vports_inuse(x)	\
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->npiv_vports_inuse)
#घोषणा fc_host_work_q_name(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->work_q_name)
#घोषणा fc_host_work_q(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->work_q)
#घोषणा fc_host_devloss_work_q_name(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->devloss_work_q_name)
#घोषणा fc_host_devloss_work_q(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->devloss_work_q)
#घोषणा fc_host_dev_loss_पंचांगo(x) \
	(((काष्ठा fc_host_attrs *)(x)->shost_data)->dev_loss_पंचांगo)

/* The functions by which the transport class and the driver communicate */
काष्ठा fc_function_ढाँचा अणु
	व्योम    (*get_rport_dev_loss_पंचांगo)(काष्ठा fc_rport *);
	व्योम	(*set_rport_dev_loss_पंचांगo)(काष्ठा fc_rport *, u32);

	व्योम	(*get_starget_node_name)(काष्ठा scsi_target *);
	व्योम	(*get_starget_port_name)(काष्ठा scsi_target *);
	व्योम 	(*get_starget_port_id)(काष्ठा scsi_target *);

	व्योम 	(*get_host_port_id)(काष्ठा Scsi_Host *);
	व्योम	(*get_host_port_type)(काष्ठा Scsi_Host *);
	व्योम	(*get_host_port_state)(काष्ठा Scsi_Host *);
	व्योम	(*get_host_active_fc4s)(काष्ठा Scsi_Host *);
	व्योम	(*get_host_speed)(काष्ठा Scsi_Host *);
	व्योम	(*get_host_fabric_name)(काष्ठा Scsi_Host *);
	व्योम	(*get_host_symbolic_name)(काष्ठा Scsi_Host *);
	व्योम	(*set_host_प्रणाली_hostname)(काष्ठा Scsi_Host *);

	काष्ठा fc_host_statistics * (*get_fc_host_stats)(काष्ठा Scsi_Host *);
	व्योम	(*reset_fc_host_stats)(काष्ठा Scsi_Host *);

	पूर्णांक	(*issue_fc_host_lip)(काष्ठा Scsi_Host *);

	व्योम    (*dev_loss_पंचांगo_callbk)(काष्ठा fc_rport *);
	व्योम	(*terminate_rport_io)(काष्ठा fc_rport *);

	व्योम	(*set_vport_symbolic_name)(काष्ठा fc_vport *);
	पूर्णांक  	(*vport_create)(काष्ठा fc_vport *, bool);
	पूर्णांक	(*vport_disable)(काष्ठा fc_vport *, bool);
	पूर्णांक  	(*vport_delete)(काष्ठा fc_vport *);

	/* bsg support */
	पूर्णांक	(*bsg_request)(काष्ठा bsg_job *);
	पूर्णांक	(*bsg_समयout)(काष्ठा bsg_job *);

	/* allocation lengths क्रम host-specअगरic data */
	u32	 			dd_fcrport_size;
	u32	 			dd_fcvport_size;
	u32				dd_bsg_size;

	/*
	 * The driver sets these to tell the transport class it
	 * wants the attributes displayed in sysfs.  If the show_ flag
	 * is not set, the attribute will be निजी to the transport
	 * class
	 */

	/* remote port fixed attributes */
	अचिन्हित दीर्घ	show_rport_maxframe_size:1;
	अचिन्हित दीर्घ	show_rport_supported_classes:1;
	अचिन्हित दीर्घ   show_rport_dev_loss_पंचांगo:1;

	/*
	 * target dynamic attributes
	 * These should all be "1" अगर the driver uses the remote port
	 * add/delete functions (so attributes reflect rport values).
	 */
	अचिन्हित दीर्घ	show_starget_node_name:1;
	अचिन्हित दीर्घ	show_starget_port_name:1;
	अचिन्हित दीर्घ	show_starget_port_id:1;

	/* host fixed attributes */
	अचिन्हित दीर्घ	show_host_node_name:1;
	अचिन्हित दीर्घ	show_host_port_name:1;
	अचिन्हित दीर्घ	show_host_permanent_port_name:1;
	अचिन्हित दीर्घ	show_host_supported_classes:1;
	अचिन्हित दीर्घ	show_host_supported_fc4s:1;
	अचिन्हित दीर्घ	show_host_supported_speeds:1;
	अचिन्हित दीर्घ	show_host_maxframe_size:1;
	अचिन्हित दीर्घ	show_host_serial_number:1;
	अचिन्हित दीर्घ	show_host_manufacturer:1;
	अचिन्हित दीर्घ	show_host_model:1;
	अचिन्हित दीर्घ	show_host_model_description:1;
	अचिन्हित दीर्घ	show_host_hardware_version:1;
	अचिन्हित दीर्घ	show_host_driver_version:1;
	अचिन्हित दीर्घ	show_host_firmware_version:1;
	अचिन्हित दीर्घ	show_host_optionrom_version:1;
	/* host dynamic attributes */
	अचिन्हित दीर्घ	show_host_port_id:1;
	अचिन्हित दीर्घ	show_host_port_type:1;
	अचिन्हित दीर्घ	show_host_port_state:1;
	अचिन्हित दीर्घ	show_host_active_fc4s:1;
	अचिन्हित दीर्घ	show_host_speed:1;
	अचिन्हित दीर्घ	show_host_fabric_name:1;
	अचिन्हित दीर्घ	show_host_symbolic_name:1;
	अचिन्हित दीर्घ	show_host_प्रणाली_hostname:1;

	अचिन्हित दीर्घ	disable_target_scan:1;
पूर्ण;

/**
 * fc_remote_port_chkपढ़ोy - called to validate the remote port state
 *   prior to initiating io to the port.
 *
 * Returns a scsi result code that can be वापसed by the LLDD.
 *
 * @rport:	remote port to be checked
 **/
अटल अंतरभूत पूर्णांक
fc_remote_port_chkपढ़ोy(काष्ठा fc_rport *rport)
अणु
	पूर्णांक result;

	चयन (rport->port_state) अणु
	हाल FC_PORTSTATE_ONLINE:
	हाल FC_PORTSTATE_MARGINAL:
		अगर (rport->roles & FC_PORT_ROLE_FCP_TARGET)
			result = 0;
		अन्यथा अगर (rport->flags & FC_RPORT_DEVLOSS_PENDING)
			result = DID_IMM_RETRY << 16;
		अन्यथा
			result = DID_NO_CONNECT << 16;
		अवरोध;
	हाल FC_PORTSTATE_BLOCKED:
		अगर (rport->flags & FC_RPORT_FAST_FAIL_TIMEDOUT)
			result = DID_TRANSPORT_FAILFAST << 16;
		अन्यथा
			result = DID_IMM_RETRY << 16;
		अवरोध;
	शेष:
		result = DID_NO_CONNECT << 16;
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

अटल अंतरभूत u64 wwn_to_u64(स्थिर u8 *wwn)
अणु
	वापस get_unaligned_be64(wwn);
पूर्ण

अटल अंतरभूत व्योम u64_to_wwn(u64 inm, u8 *wwn)
अणु
	put_unaligned_be64(inm, wwn);
पूर्ण

/**
 * fc_vport_set_state() - called to set a vport's state. Saves the old state,
 *   excepting the transitory states of initializing and sending the ELS
 *   traffic to instantiate the vport on the link.
 *
 * Assumes the driver has surrounded this with the proper locking to ensure
 * a coherent state change.
 *
 * @vport:	भव port whose state is changing
 * @new_state:  new state
 **/
अटल अंतरभूत व्योम
fc_vport_set_state(काष्ठा fc_vport *vport, क्रमागत fc_vport_state new_state)
अणु
	अगर ((new_state != FC_VPORT_UNKNOWN) &&
	    (new_state != FC_VPORT_INITIALIZING))
		vport->vport_last_state = vport->vport_state;
	vport->vport_state = new_state;
पूर्ण

काष्ठा scsi_transport_ढाँचा *fc_attach_transport(
			काष्ठा fc_function_ढाँचा *);
व्योम fc_release_transport(काष्ठा scsi_transport_ढाँचा *);
व्योम fc_हटाओ_host(काष्ठा Scsi_Host *);
काष्ठा fc_rport *fc_remote_port_add(काष्ठा Scsi_Host *shost,
			पूर्णांक channel, काष्ठा fc_rport_identअगरiers  *ids);
व्योम fc_remote_port_delete(काष्ठा fc_rport  *rport);
व्योम fc_remote_port_rolechg(काष्ठा fc_rport  *rport, u32 roles);
पूर्णांक scsi_is_fc_rport(स्थिर काष्ठा device *);
u32 fc_get_event_number(व्योम);
व्योम fc_host_post_event(काष्ठा Scsi_Host *shost, u32 event_number,
		क्रमागत fc_host_event_code event_code, u32 event_data);
व्योम fc_host_post_venकरोr_event(काष्ठा Scsi_Host *shost, u32 event_number,
		u32 data_len, अक्षर *data_buf, u64 venकरोr_id);
काष्ठा fc_rport *fc_find_rport_by_wwpn(काष्ठा Scsi_Host *shost, u64 wwpn);
व्योम fc_host_post_fc_event(काष्ठा Scsi_Host *shost, u32 event_number,
		क्रमागत fc_host_event_code event_code,
		u32 data_len, अक्षर *data_buf, u64 venकरोr_id);
	/* Note: when specअगरying venकरोr_id to fc_host_post_venकरोr_event()
	 *   or fc_host_post_fc_event(), be sure to पढ़ो the Venकरोr Type
	 *   and ID क्रमmatting requirements specअगरied in scsi_netlink.h
	 * Note: when calling fc_host_post_fc_event(), venकरोr_id may be
	 *   specअगरied as 0.
	 */
व्योम fc_host_fpin_rcv(काष्ठा Scsi_Host *shost, u32 fpin_len, अक्षर *fpin_buf);
काष्ठा fc_vport *fc_vport_create(काष्ठा Scsi_Host *shost, पूर्णांक channel,
		काष्ठा fc_vport_identअगरiers *);
पूर्णांक fc_vport_terminate(काष्ठा fc_vport *vport);
पूर्णांक fc_block_rport(काष्ठा fc_rport *rport);
पूर्णांक fc_block_scsi_eh(काष्ठा scsi_cmnd *cmnd);
क्रमागत blk_eh_समयr_वापस fc_eh_समयd_out(काष्ठा scsi_cmnd *scmd);
bool fc_eh_should_retry_cmd(काष्ठा scsi_cmnd *scmd);

अटल अंतरभूत काष्ठा Scsi_Host *fc_bsg_to_shost(काष्ठा bsg_job *job)
अणु
	अगर (scsi_is_host_device(job->dev))
		वापस dev_to_shost(job->dev);
	वापस rport_to_shost(dev_to_rport(job->dev));
पूर्ण

अटल अंतरभूत काष्ठा fc_rport *fc_bsg_to_rport(काष्ठा bsg_job *job)
अणु
	अगर (scsi_is_fc_rport(job->dev))
		वापस dev_to_rport(job->dev);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* SCSI_TRANSPORT_FC_H */
