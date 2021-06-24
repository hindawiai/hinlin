<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2008-2009 Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2007-2008 Intel Corporation.  All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#अगर_अघोषित _LIBFCOE_H
#घोषणा _LIBFCOE_H

#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/अक्रमom.h>
#समावेश <scsi/fc/fc_fcoe.h>
#समावेश <scsi/libfc.h>
#समावेश <scsi/fcoe_sysfs.h>

#घोषणा FCOE_MAX_CMD_LEN	16	/* Supported CDB length */

/*
 * Max MTU क्रम FCoE: 14 (FCoE header) + 24 (FC header) + 2112 (max FC payload)
 * + 4 (FC CRC) + 4 (FCoE trailer) =  2158 bytes
 */
#घोषणा FCOE_MTU	2158

/*
 * FIP tunable parameters.
 */
#घोषणा FCOE_CTLR_START_DELAY	2000	/* mS after first adv. to choose FCF */
#घोषणा FCOE_CTLR_SOL_TOV	2000	/* min. solicitation पूर्णांकerval (mS) */
#घोषणा FCOE_CTLR_FCF_LIMIT	20	/* max. number of FCF entries */
#घोषणा FCOE_CTLR_VN2VN_LOGIN_LIMIT 3	/* max. VN2VN rport login retries */

/**
 * क्रमागत fip_state - पूर्णांकernal state of FCoE controller.
 * @FIP_ST_DISABLED: 	controller has been disabled or not yet enabled.
 * @FIP_ST_LINK_WAIT:	the physical link is करोwn or unusable.
 * @FIP_ST_AUTO:	determining whether to use FIP or non-FIP mode.
 * @FIP_ST_NON_FIP:	non-FIP mode selected.
 * @FIP_ST_ENABLED:	FIP mode selected.
 * @FIP_ST_VNMP_START:	VN2VN multipath mode start, रुको
 * @FIP_ST_VNMP_PROBE1:	VN2VN sent first probe, listening
 * @FIP_ST_VNMP_PROBE2:	VN2VN sent second probe, listening
 * @FIP_ST_VNMP_CLAIM:	VN2VN sent claim, रुकोing क्रम responses
 * @FIP_ST_VNMP_UP:	VN2VN multipath mode operation
 */
क्रमागत fip_state अणु
	FIP_ST_DISABLED,
	FIP_ST_LINK_WAIT,
	FIP_ST_AUTO,
	FIP_ST_NON_FIP,
	FIP_ST_ENABLED,
	FIP_ST_VNMP_START,
	FIP_ST_VNMP_PROBE1,
	FIP_ST_VNMP_PROBE2,
	FIP_ST_VNMP_CLAIM,
	FIP_ST_VNMP_UP,
पूर्ण;

/*
 * Modes:
 * The mode is the state that is to be entered after link up.
 * It must not change after fcoe_ctlr_init() sets it.
 */
क्रमागत fip_mode अणु
	FIP_MODE_AUTO,
	FIP_MODE_NON_FIP,
	FIP_MODE_FABRIC,
	FIP_MODE_VN2VN,
पूर्ण;

/**
 * काष्ठा fcoe_ctlr - FCoE Controller and FIP state
 * @state:	   पूर्णांकernal FIP state क्रम network link and FIP or non-FIP mode.
 * @mode:	   LLD-selected mode.
 * @lp:		   &fc_lport: libfc local port.
 * @sel_fcf:	   currently selected FCF, or शून्य.
 * @fcfs:	   list of discovered FCFs.
 * @cdev:          (Optional) poपूर्णांकer to sysfs fcoe_ctlr_device.
 * @fcf_count:	   number of discovered FCF entries.
 * @sol_समय:	   समय when a multicast solicitation was last sent.
 * @sel_समय:	   समय after which to select an FCF.
 * @port_ka_समय:  समय of next port keep-alive.
 * @ctlr_ka_समय:  समय of next controller keep-alive.
 * @समयr:	   समयr काष्ठा used क्रम all delayed events.
 * @समयr_work:	   &work_काष्ठा क्रम करोing keep-alives and resets.
 * @recv_work:	   &work_काष्ठा क्रम receiving FIP frames.
 * @fip_recv_list: list of received FIP frames.
 * @flogi_req:	   clone of FLOGI request sent
 * @rnd_state:	   state क्रम pseuकरो-अक्रमom number generator.
 * @port_id:	   proposed or selected local-port ID.
 * @user_mfs:	   configured maximum FC frame size, including FC header.
 * @flogi_oxid:    exchange ID of most recent fabric login.
 * @flogi_req_send: send of FLOGI requested
 * @flogi_count:   number of FLOGI attempts in AUTO mode.
 * @map_dest:	   use the FC_MAP mode क्रम destination MAC addresses.
 * @fip_resp:	   start FIP VLAN discovery responder
 * @spma:	   supports SPMA server-provided MACs mode
 * @probe_tries:   number of FC_IDs probed
 * @priority:      DCBx FCoE APP priority
 * @dest_addr:	   MAC address of the selected FC क्रमwarder.
 * @ctl_src_addr:  the native MAC address of our local port.
 * @send:	   LLD-supplied function to handle sending FIP Ethernet frames
 * @update_mac:    LLD-supplied function to handle changes to MAC addresses.
 * @get_src_addr:  LLD-supplied function to supply a source MAC address.
 * @ctlr_mutex:	   lock protecting this काष्ठाure.
 * @ctlr_lock:     spinlock covering flogi_req
 *
 * This काष्ठाure is used by all FCoE drivers.  It contains inक्रमmation
 * needed by all FCoE low-level drivers (LLDs) as well as पूर्णांकernal state
 * क्रम FIP, and fields shared with the LLDS.
 */
काष्ठा fcoe_ctlr अणु
	क्रमागत fip_state state;
	क्रमागत fip_mode mode;
	काष्ठा fc_lport *lp;
	काष्ठा fcoe_fcf *sel_fcf;
	काष्ठा list_head fcfs;
	काष्ठा fcoe_ctlr_device *cdev;
	u16 fcf_count;
	अचिन्हित दीर्घ sol_समय;
	अचिन्हित दीर्घ sel_समय;
	अचिन्हित दीर्घ port_ka_समय;
	अचिन्हित दीर्घ ctlr_ka_समय;
	काष्ठा समयr_list समयr;
	काष्ठा work_काष्ठा समयr_work;
	काष्ठा work_काष्ठा recv_work;
	काष्ठा sk_buff_head fip_recv_list;
	काष्ठा sk_buff *flogi_req;

	काष्ठा rnd_state rnd_state;
	u32 port_id;

	u16 user_mfs;
	u16 flogi_oxid;
	u8 flogi_req_send;
	u8 flogi_count;
	bool map_dest;
	bool fip_resp;
	u8 spma;
	u8 probe_tries;
	u8 priority;
	u8 dest_addr[ETH_ALEN];
	u8 ctl_src_addr[ETH_ALEN];

	व्योम (*send)(काष्ठा fcoe_ctlr *, काष्ठा sk_buff *);
	व्योम (*update_mac)(काष्ठा fc_lport *, u8 *addr);
	u8 * (*get_src_addr)(काष्ठा fc_lport *);
	काष्ठा mutex ctlr_mutex;
	spinlock_t ctlr_lock;
पूर्ण;

/**
 * fcoe_ctlr_priv() - Return the निजी data from a fcoe_ctlr
 * @cltr: The fcoe_ctlr whose निजी data will be वापसed
 */
अटल अंतरभूत व्योम *fcoe_ctlr_priv(स्थिर काष्ठा fcoe_ctlr *ctlr)
अणु
	वापस (व्योम *)(ctlr + 1);
पूर्ण

/*
 * This assumes that the fcoe_ctlr (x) is allocated with the fcoe_ctlr_device.
 */
#घोषणा fcoe_ctlr_to_ctlr_dev(x)					\
	(x)->cdev

/**
 * काष्ठा fcoe_fcf - Fibre-Channel Forwarder
 * @list:	 list linkage
 * @event_work:  Work क्रम FC Transport actions queue
 * @event:       The event to be processed
 * @fip:         The controller that the FCF was discovered on
 * @fcf_dev:     The associated fcoe_fcf_device instance
 * @समय:	 प्रणाली समय (jअगरfies) when an advertisement was last received
 * @चयन_name: WWN of चयन from advertisement
 * @fabric_name: WWN of fabric from advertisement
 * @fc_map:	 FC_MAP value from advertisement
 * @fcf_mac:	 Ethernet address of the FCF क्रम FIP traffic
 * @fcoe_mac:	 Ethernet address of the FCF क्रम FCoE traffic
 * @vfid:	 भव fabric ID
 * @pri:	 selection priority, smaller values are better
 * @flogi_sent:	 current FLOGI sent to this FCF
 * @flags:	 flags received from advertisement
 * @fka_period:	 keep-alive period, in jअगरfies
 *
 * A Fibre-Channel Forwarder (FCF) is the entity on the Ethernet that
 * passes FCoE frames on to an FC fabric.  This काष्ठाure represents
 * one FCF from which advertisements have been received.
 *
 * When looking up an FCF, @चयन_name, @fabric_name, @fc_map, @vfid, and
 * @fcf_mac together क्रमm the lookup key.
 */
काष्ठा fcoe_fcf अणु
	काष्ठा list_head list;
	काष्ठा work_काष्ठा event_work;
	काष्ठा fcoe_ctlr *fip;
	काष्ठा fcoe_fcf_device *fcf_dev;
	अचिन्हित दीर्घ समय;

	u64 चयन_name;
	u64 fabric_name;
	u32 fc_map;
	u16 vfid;
	u8 fcf_mac[ETH_ALEN];
	u8 fcoe_mac[ETH_ALEN];

	u8 pri;
	u8 flogi_sent;
	u16 flags;
	u32 fka_period;
	u8 fd_flags:1;
पूर्ण;

#घोषणा fcoe_fcf_to_fcf_dev(x)			\
	((x)->fcf_dev)

/**
 * काष्ठा fcoe_rport - VN2VN remote port
 * @समय:	समय of create or last beacon packet received from node
 * @fcoe_len:	max FCoE frame size, not including VLAN or Ethernet headers
 * @flags:	flags from probe or claim
 * @login_count: number of unsuccessful rport logins to this port
 * @enode_mac:	E_Node control MAC address
 * @vn_mac:	VN_Node asचिन्हित MAC address क्रम data
 */
काष्ठा fcoe_rport अणु
	काष्ठा fc_rport_priv rdata;
	अचिन्हित दीर्घ समय;
	u16 fcoe_len;
	u16 flags;
	u8 login_count;
	u8 enode_mac[ETH_ALEN];
	u8 vn_mac[ETH_ALEN];
पूर्ण;

/* FIP API functions */
व्योम fcoe_ctlr_init(काष्ठा fcoe_ctlr *, क्रमागत fip_mode);
व्योम fcoe_ctlr_destroy(काष्ठा fcoe_ctlr *);
व्योम fcoe_ctlr_link_up(काष्ठा fcoe_ctlr *);
पूर्णांक fcoe_ctlr_link_करोwn(काष्ठा fcoe_ctlr *);
पूर्णांक fcoe_ctlr_els_send(काष्ठा fcoe_ctlr *, काष्ठा fc_lport *, काष्ठा sk_buff *);
व्योम fcoe_ctlr_recv(काष्ठा fcoe_ctlr *, काष्ठा sk_buff *);
पूर्णांक fcoe_ctlr_recv_flogi(काष्ठा fcoe_ctlr *, काष्ठा fc_lport *,
			 काष्ठा fc_frame *);

/* libfcoe funcs */
u64 fcoe_wwn_from_mac(अचिन्हित अक्षर mac[MAX_ADDR_LEN], अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
पूर्णांक fcoe_libfc_config(काष्ठा fc_lport *, काष्ठा fcoe_ctlr *,
		      स्थिर काष्ठा libfc_function_ढाँचा *, पूर्णांक init_fcp);
u32 fcoe_fc_crc(काष्ठा fc_frame *fp);
पूर्णांक fcoe_start_io(काष्ठा sk_buff *skb);
पूर्णांक fcoe_get_wwn(काष्ठा net_device *netdev, u64 *wwn, पूर्णांक type);
व्योम __fcoe_get_lesb(काष्ठा fc_lport *lport, काष्ठा fc_els_lesb *fc_lesb,
		     काष्ठा net_device *netdev);
व्योम fcoe_wwn_to_str(u64 wwn, अक्षर *buf, पूर्णांक len);
पूर्णांक fcoe_validate_vport_create(काष्ठा fc_vport *vport);
पूर्णांक fcoe_link_speed_update(काष्ठा fc_lport *);
व्योम fcoe_get_lesb(काष्ठा fc_lport *, काष्ठा fc_els_lesb *);
व्योम fcoe_ctlr_get_lesb(काष्ठा fcoe_ctlr_device *ctlr_dev);

/**
 * is_fip_mode() - वापसs true अगर FIP mode selected.
 * @fip:	FCoE controller.
 */
अटल अंतरभूत bool is_fip_mode(काष्ठा fcoe_ctlr *fip)
अणु
	वापस fip->state == FIP_ST_ENABLED;
पूर्ण

/* helper क्रम FCoE SW HBA drivers, can include subven and subdev अगर needed. The
 * modpost would use pci_device_id table to स्वतः-generate क्रमmatted module alias
 * पूर्णांकo the corresponding .mod.c file, but there may or may not be a pci device
 * id table क्रम FCoE drivers so we use the following helper क्रम build the fcoe
 * driver module alias.
 */
#घोषणा MODULE_ALIAS_FCOE_PCI(ven, dev) \
	MODULE_ALIAS("fcoe-pci:"	\
		"v" __stringअगरy(ven)	\
		"d" __stringअगरy(dev) "sv*sd*bc*sc*i*")

/* the name of the शेष FCoE transport driver fcoe.ko */
#घोषणा FCOE_TRANSPORT_DEFAULT	"fcoe"

/* काष्ठा fcoe_transport - The FCoE transport पूर्णांकerface
 * @name:	a venकरोr specअगरic name क्रम their FCoE transport driver
 * @attached:	whether this transport is alपढ़ोy attached
 * @list:	list linkage to all attached transports
 * @match:	handler to allow the transport driver to match up a given netdev
 * @alloc:      handler to allocate per-instance FCoE काष्ठाures
 *		(no discovery or login)
 * @create:	handler to sysfs entry of create क्रम FCoE instances
 * @destroy:    handler to delete per-instance FCoE काष्ठाures
 *		(मुक्तs all memory)
 * @enable:	handler to sysfs entry of enable क्रम FCoE instances
 * @disable:	handler to sysfs entry of disable क्रम FCoE instances
 */
काष्ठा fcoe_transport अणु
	अक्षर name[IFNAMSIZ];
	bool attached;
	काष्ठा list_head list;
	bool (*match) (काष्ठा net_device *device);
	पूर्णांक (*alloc) (काष्ठा net_device *device);
	पूर्णांक (*create) (काष्ठा net_device *device, क्रमागत fip_mode fip_mode);
	पूर्णांक (*destroy) (काष्ठा net_device *device);
	पूर्णांक (*enable) (काष्ठा net_device *device);
	पूर्णांक (*disable) (काष्ठा net_device *device);
पूर्ण;

/**
 * काष्ठा fcoe_percpu_s - The context क्रम FCoE receive thपढ़ो(s)
 * @kthपढ़ो:	    The thपढ़ो context (used by bnx2fc)
 * @work:	    The work item (used by fcoe)
 * @fcoe_rx_list:   The queue of pending packets to process
 * @page:	    The memory page क्रम calculating frame trailer CRCs
 * @crc_eof_offset: The offset पूर्णांकo the CRC page poपूर्णांकing to available
 *		    memory क्रम a new trailer
 */
काष्ठा fcoe_percpu_s अणु
	काष्ठा task_काष्ठा *kthपढ़ो;
	काष्ठा work_काष्ठा work;
	काष्ठा sk_buff_head fcoe_rx_list;
	काष्ठा page *crc_eof_page;
	पूर्णांक crc_eof_offset;
पूर्ण;

/**
 * काष्ठा fcoe_port - The FCoE निजी काष्ठाure
 * @priv:		       The associated fcoe पूर्णांकerface. The काष्ठाure is
 *			       defined by the low level driver
 * @lport:		       The associated local port
 * @fcoe_pending_queue:	       The pending Rx queue of skbs
 * @fcoe_pending_queue_active: Indicates अगर the pending queue is active
 * @max_queue_depth:	       Max queue depth of pending queue
 * @min_queue_depth:	       Min queue depth of pending queue
 * @समयr:		       The queue समयr
 * @destroy_work:	       Handle क्रम work context
 *			       (to prevent RTNL deadlocks)
 * @data_srt_addr:	       Source address क्रम data
 *
 * An instance of this काष्ठाure is to be allocated aदीर्घ with the
 * Scsi_Host and libfc fc_lport काष्ठाures.
 */
काष्ठा fcoe_port अणु
	व्योम		      *priv;
	काष्ठा fc_lport	      *lport;
	काष्ठा sk_buff_head   fcoe_pending_queue;
	u8		      fcoe_pending_queue_active;
	u32		      max_queue_depth;
	u32		      min_queue_depth;
	काष्ठा समयr_list     समयr;
	काष्ठा work_काष्ठा    destroy_work;
	u8		      data_src_addr[ETH_ALEN];
	काष्ठा net_device * (*get_netdev)(स्थिर काष्ठा fc_lport *lport);
पूर्ण;

/**
 * fcoe_get_netdev() - Return the net device associated with a local port
 * @lport: The local port to get the net device from
 */
अटल अंतरभूत काष्ठा net_device *fcoe_get_netdev(स्थिर काष्ठा fc_lport *lport)
अणु
	काष्ठा fcoe_port *port = ((काष्ठा fcoe_port *)lport_priv(lport));

	वापस (port->get_netdev) ? port->get_netdev(lport) : शून्य;
पूर्ण

व्योम fcoe_clean_pending_queue(काष्ठा fc_lport *);
व्योम fcoe_check_रुको_queue(काष्ठा fc_lport *lport, काष्ठा sk_buff *skb);
व्योम fcoe_queue_समयr(काष्ठा समयr_list *t);
पूर्णांक fcoe_get_paged_crc_eof(काष्ठा sk_buff *skb, पूर्णांक tlen,
			   काष्ठा fcoe_percpu_s *fps);

/* FCoE Sysfs helpers */
व्योम fcoe_fcf_get_selected(काष्ठा fcoe_fcf_device *);
व्योम fcoe_ctlr_set_fip_mode(काष्ठा fcoe_ctlr_device *);

/**
 * काष्ठा netdev_list
 * A mapping from netdevice to fcoe_transport
 */
काष्ठा fcoe_netdev_mapping अणु
	काष्ठा list_head list;
	काष्ठा net_device *netdev;
	काष्ठा fcoe_transport *ft;
पूर्ण;

/* fcoe transports registration and deregistration */
पूर्णांक fcoe_transport_attach(काष्ठा fcoe_transport *ft);
पूर्णांक fcoe_transport_detach(काष्ठा fcoe_transport *ft);

/* sysfs store handler क्रम ctrl_control पूर्णांकerface */
sमाप_प्रकार fcoe_ctlr_create_store(काष्ठा bus_type *bus,
			       स्थिर अक्षर *buf, माप_प्रकार count);
sमाप_प्रकार fcoe_ctlr_destroy_store(काष्ठा bus_type *bus,
				स्थिर अक्षर *buf, माप_प्रकार count);

#पूर्ण_अगर /* _LIBFCOE_H */


