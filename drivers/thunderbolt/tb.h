<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Thunderbolt driver - bus logic (NHI independent)
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2018, Intel Corporation
 */

#अगर_अघोषित TB_H_
#घोषणा TB_H_

#समावेश <linux/nvmem-provider.h>
#समावेश <linux/pci.h>
#समावेश <linux/thunderbolt.h>
#समावेश <linux/uuid.h>

#समावेश "tb_regs.h"
#समावेश "ctl.h"
#समावेश "dma_port.h"

#घोषणा NVM_MIN_SIZE		SZ_32K
#घोषणा NVM_MAX_SIZE		SZ_512K

/* Intel specअगरic NVM offsets */
#घोषणा NVM_DEVID		0x05
#घोषणा NVM_VERSION		0x08
#घोषणा NVM_FLASH_SIZE		0x45

/**
 * काष्ठा tb_nvm - Structure holding NVM inक्रमmation
 * @dev: Owner of the NVM
 * @major: Major version number of the active NVM portion
 * @minor: Minor version number of the active NVM portion
 * @id: Identअगरier used with both NVM portions
 * @active: Active portion NVMem device
 * @non_active: Non-active portion NVMem device
 * @buf: Buffer where the NVM image is stored beक्रमe it is written to
 *	 the actual NVM flash device
 * @buf_data_size: Number of bytes actually consumed by the new NVM
 *		   image
 * @authenticating: The device is authenticating the new NVM
 * @flushed: The image has been flushed to the storage area
 *
 * The user of this काष्ठाure needs to handle serialization of possible
 * concurrent access.
 */
काष्ठा tb_nvm अणु
	काष्ठा device *dev;
	u8 major;
	u8 minor;
	पूर्णांक id;
	काष्ठा nvmem_device *active;
	काष्ठा nvmem_device *non_active;
	व्योम *buf;
	माप_प्रकार buf_data_size;
	bool authenticating;
	bool flushed;
पूर्ण;

#घोषणा TB_SWITCH_KEY_SIZE		32
#घोषणा TB_SWITCH_MAX_DEPTH		6
#घोषणा USB4_SWITCH_MAX_DEPTH		5

/**
 * क्रमागत tb_चयन_पंचांगu_rate - TMU refresh rate
 * @TB_SWITCH_TMU_RATE_OFF: %0 (Disable Time Sync handshake)
 * @TB_SWITCH_TMU_RATE_HIFI: %16 us समय पूर्णांकerval between successive
 *			     transmission of the Delay Request TSNOS
 *			     (Time Sync Notअगरication Ordered Set) on a Link
 * @TB_SWITCH_TMU_RATE_NORMAL: %1 ms समय पूर्णांकerval between successive
 *			       transmission of the Delay Request TSNOS on
 *			       a Link
 */
क्रमागत tb_चयन_पंचांगu_rate अणु
	TB_SWITCH_TMU_RATE_OFF = 0,
	TB_SWITCH_TMU_RATE_HIFI = 16,
	TB_SWITCH_TMU_RATE_NORMAL = 1000,
पूर्ण;

/**
 * काष्ठा tb_चयन_पंचांगu - Structure holding चयन TMU configuration
 * @cap: Offset to the TMU capability (%0 अगर not found)
 * @has_ucap: Does the चयन support uni-directional mode
 * @rate: TMU refresh rate related to upstream चयन. In हाल of root
 *	  चयन this holds the करोमुख्य rate.
 * @unidirectional: Is the TMU in uni-directional or bi-directional mode
 *		    related to upstream चयन. Don't हाल क्रम root चयन.
 */
काष्ठा tb_चयन_पंचांगu अणु
	पूर्णांक cap;
	bool has_ucap;
	क्रमागत tb_चयन_पंचांगu_rate rate;
	bool unidirectional;
पूर्ण;

/**
 * काष्ठा tb_चयन - a thunderbolt चयन
 * @dev: Device क्रम the चयन
 * @config: Switch configuration
 * @ports: Ports in this चयन
 * @dma_port: If the चयन has port supporting DMA configuration based
 *	      mailbox this will hold the poपूर्णांकer to that (%शून्य
 *	      otherwise). If set it also means the चयन has
 *	      upgradeable NVM.
 * @पंचांगu: The चयन TMU configuration
 * @tb: Poपूर्णांकer to the करोमुख्य the चयन beदीर्घs to
 * @uid: Unique ID of the चयन
 * @uuid: UUID of the चयन (or %शून्य अगर not supported)
 * @venकरोr: Venकरोr ID of the चयन
 * @device: Device ID of the चयन
 * @venकरोr_name: Name of the venकरोr (or %शून्य अगर not known)
 * @device_name: Name of the device (or %शून्य अगर not known)
 * @link_speed: Speed of the link in Gb/s
 * @link_width: Width of the link (1 or 2)
 * @link_usb4: Upstream link is USB4
 * @generation: Switch Thunderbolt generation
 * @cap_plug_events: Offset to the plug events capability (%0 अगर not found)
 * @cap_lc: Offset to the link controller capability (%0 अगर not found)
 * @is_unplugged: The चयन is going away
 * @drom: DROM of the चयन (%शून्य अगर not found)
 * @nvm: Poपूर्णांकer to the NVM अगर the चयन has one (%शून्य otherwise)
 * @no_nvm_upgrade: Prevent NVM upgrade of this चयन
 * @safe_mode: The चयन is in safe-mode
 * @boot: Whether the चयन was alपढ़ोy authorized on boot or not
 * @rpm: The चयन supports runसमय PM
 * @authorized: Whether the चयन is authorized by user or policy
 * @security_level: Switch supported security level
 * @debugfs_dir: Poपूर्णांकer to the debugfs काष्ठाure
 * @key: Contains the key used to challenge the device or %शून्य अगर not
 *	 supported. Size of the key is %TB_SWITCH_KEY_SIZE.
 * @connection_id: Connection ID used with ICM messaging
 * @connection_key: Connection key used with ICM messaging
 * @link: Root चयन link this चयन is connected (ICM only)
 * @depth: Depth in the chain this चयन is connected (ICM only)
 * @rpm_complete: Completion used to रुको क्रम runसमय resume to
 *		  complete (ICM only)
 * @quirks: Quirks used क्रम this Thunderbolt चयन
 *
 * When the चयन is being added or हटाओd to the करोमुख्य (other
 * चयनes) you need to have करोमुख्य lock held.
 *
 * In USB4 terminology this काष्ठाure represents a router.
 */
काष्ठा tb_चयन अणु
	काष्ठा device dev;
	काष्ठा tb_regs_चयन_header config;
	काष्ठा tb_port *ports;
	काष्ठा tb_dma_port *dma_port;
	काष्ठा tb_चयन_पंचांगu पंचांगu;
	काष्ठा tb *tb;
	u64 uid;
	uuid_t *uuid;
	u16 venकरोr;
	u16 device;
	स्थिर अक्षर *venकरोr_name;
	स्थिर अक्षर *device_name;
	अचिन्हित पूर्णांक link_speed;
	अचिन्हित पूर्णांक link_width;
	bool link_usb4;
	अचिन्हित पूर्णांक generation;
	पूर्णांक cap_plug_events;
	पूर्णांक cap_lc;
	bool is_unplugged;
	u8 *drom;
	काष्ठा tb_nvm *nvm;
	bool no_nvm_upgrade;
	bool safe_mode;
	bool boot;
	bool rpm;
	अचिन्हित पूर्णांक authorized;
	क्रमागत tb_security_level security_level;
	काष्ठा dentry *debugfs_dir;
	u8 *key;
	u8 connection_id;
	u8 connection_key;
	u8 link;
	u8 depth;
	काष्ठा completion rpm_complete;
	अचिन्हित दीर्घ quirks;
पूर्ण;

/**
 * काष्ठा tb_port - a thunderbolt port, part of a tb_चयन
 * @config: Cached port configuration पढ़ो from रेजिस्टरs
 * @sw: Switch the port beदीर्घs to
 * @remote: Remote port (%शून्य अगर not connected)
 * @xकरोमुख्य: Remote host (%शून्य अगर not connected)
 * @cap_phy: Offset, zero अगर not found
 * @cap_पंचांगu: Offset of the adapter specअगरic TMU capability (%0 अगर not present)
 * @cap_adap: Offset of the adapter specअगरic capability (%0 अगर not present)
 * @cap_usb4: Offset to the USB4 port capability (%0 अगर not present)
 * @port: Port number on चयन
 * @disabled: Disabled by eeprom or enabled but not implemented
 * @bonded: true अगर the port is bonded (two lanes combined as one)
 * @dual_link_port: If the चयन is connected using two ports, poपूर्णांकs
 *		    to the other port.
 * @link_nr: Is this primary or secondary port on the dual_link.
 * @in_hopids: Currently allocated input HopIDs
 * @out_hopids: Currently allocated output HopIDs
 * @list: Used to link ports to DP resources list
 *
 * In USB4 terminology this काष्ठाure represents an adapter (protocol or
 * lane adapter).
 */
काष्ठा tb_port अणु
	काष्ठा tb_regs_port_header config;
	काष्ठा tb_चयन *sw;
	काष्ठा tb_port *remote;
	काष्ठा tb_xकरोमुख्य *xकरोमुख्य;
	पूर्णांक cap_phy;
	पूर्णांक cap_पंचांगu;
	पूर्णांक cap_adap;
	पूर्णांक cap_usb4;
	u8 port;
	bool disabled;
	bool bonded;
	काष्ठा tb_port *dual_link_port;
	u8 link_nr:1;
	काष्ठा ida in_hopids;
	काष्ठा ida out_hopids;
	काष्ठा list_head list;
पूर्ण;

/**
 * tb_reसमयr: Thunderbolt reसमयr
 * @dev: Device क्रम the reसमयr
 * @tb: Poपूर्णांकer to the करोमुख्य the reसमयr beदीर्घs to
 * @index: Reसमयr index facing the router USB4 port
 * @venकरोr: Venकरोr ID of the reसमयr
 * @device: Device ID of the reसमयr
 * @port: Poपूर्णांकer to the lane 0 adapter
 * @nvm: Poपूर्णांकer to the NVM अगर the reसमयr has one (%शून्य otherwise)
 * @auth_status: Status of last NVM authentication
 */
काष्ठा tb_reसमयr अणु
	काष्ठा device dev;
	काष्ठा tb *tb;
	u8 index;
	u32 venकरोr;
	u32 device;
	काष्ठा tb_port *port;
	काष्ठा tb_nvm *nvm;
	u32 auth_status;
पूर्ण;

/**
 * काष्ठा tb_path_hop - routing inक्रमmation क्रम a tb_path
 * @in_port: Ingress port of a चयन
 * @out_port: Egress port of a चयन where the packet is routed out
 *	      (must be on the same चयन than @in_port)
 * @in_hop_index: HopID where the path configuration entry is placed in
 *		  the path config space of @in_port.
 * @in_counter_index: Used counter index (not used in the driver
 *		      currently, %-1 to disable)
 * @next_hop_index: HopID of the packet when it is routed out from @out_port
 * @initial_credits: Number of initial flow control credits allocated क्रम
 *		     the path
 *
 * Hop configuration is always करोne on the IN port of a चयन.
 * in_port and out_port have to be on the same चयन. Packets arriving on
 * in_port with "hop" = in_hop_index will get routed to through out_port. The
 * next hop to take (on out_port->remote) is determined by
 * next_hop_index. When routing packet to another चयन (out->remote is
 * set) the @next_hop_index must match the @in_hop_index of that next
 * hop to make routing possible.
 *
 * in_counter_index is the index of a counter (in TB_CFG_COUNTERS) on the in
 * port.
 */
काष्ठा tb_path_hop अणु
	काष्ठा tb_port *in_port;
	काष्ठा tb_port *out_port;
	पूर्णांक in_hop_index;
	पूर्णांक in_counter_index;
	पूर्णांक next_hop_index;
	अचिन्हित पूर्णांक initial_credits;
पूर्ण;

/**
 * क्रमागत tb_path_port - path options mask
 * @TB_PATH_NONE: Do not activate on any hop on path
 * @TB_PATH_SOURCE: Activate on the first hop (out of src)
 * @TB_PATH_INTERNAL: Activate on the पूर्णांकermediate hops (not the first/last)
 * @TB_PATH_DESTINATION: Activate on the last hop (पूर्णांकo dst)
 * @TB_PATH_ALL: Activate on all hops on the path
 */
क्रमागत tb_path_port अणु
	TB_PATH_NONE = 0,
	TB_PATH_SOURCE = 1,
	TB_PATH_INTERNAL = 2,
	TB_PATH_DESTINATION = 4,
	TB_PATH_ALL = 7,
पूर्ण;

/**
 * काष्ठा tb_path - a unidirectional path between two ports
 * @tb: Poपूर्णांकer to the करोमुख्य काष्ठाure
 * @name: Name of the path (used क्रम debugging)
 * @nfc_credits: Number of non flow controlled credits allocated क्रम the path
 * @ingress_shared_buffer: Shared buffering used क्रम ingress ports on the path
 * @egress_shared_buffer: Shared buffering used क्रम egress ports on the path
 * @ingress_fc_enable: Flow control क्रम ingress ports on the path
 * @egress_fc_enable: Flow control क्रम egress ports on the path
 * @priority: Priority group अगर the path
 * @weight: Weight of the path inside the priority group
 * @drop_packages: Drop packages from queue tail or head
 * @activated: Is the path active
 * @clear_fc: Clear all flow control from the path config space entries
 *	      when deactivating this path
 * @hops: Path hops
 * @path_length: How many hops the path uses
 *
 * A path consists of a number of hops (see &काष्ठा tb_path_hop). To
 * establish a PCIe tunnel two paths have to be created between the two
 * PCIe ports.
 */
काष्ठा tb_path अणु
	काष्ठा tb *tb;
	स्थिर अक्षर *name;
	पूर्णांक nfc_credits;
	क्रमागत tb_path_port ingress_shared_buffer;
	क्रमागत tb_path_port egress_shared_buffer;
	क्रमागत tb_path_port ingress_fc_enable;
	क्रमागत tb_path_port egress_fc_enable;

	अचिन्हित पूर्णांक priority:3;
	पूर्णांक weight:4;
	bool drop_packages;
	bool activated;
	bool clear_fc;
	काष्ठा tb_path_hop *hops;
	पूर्णांक path_length;
पूर्ण;

/* HopIDs 0-7 are reserved by the Thunderbolt protocol */
#घोषणा TB_PATH_MIN_HOPID	8
/*
 * Support paths from the farthest (depth 6) router to the host and back
 * to the same level (not necessarily to the same router).
 */
#घोषणा TB_PATH_MAX_HOPS	(7 * 2)

/* Possible wake types */
#घोषणा TB_WAKE_ON_CONNECT	BIT(0)
#घोषणा TB_WAKE_ON_DISCONNECT	BIT(1)
#घोषणा TB_WAKE_ON_USB4		BIT(2)
#घोषणा TB_WAKE_ON_USB3		BIT(3)
#घोषणा TB_WAKE_ON_PCIE		BIT(4)

/**
 * काष्ठा tb_cm_ops - Connection manager specअगरic operations vector
 * @driver_पढ़ोy: Called right after control channel is started. Used by
 *		  ICM to send driver पढ़ोy message to the firmware.
 * @start: Starts the करोमुख्य
 * @stop: Stops the करोमुख्य
 * @suspend_noirq: Connection manager specअगरic suspend_noirq
 * @resume_noirq: Connection manager specअगरic resume_noirq
 * @suspend: Connection manager specअगरic suspend
 * @मुक्तze_noirq: Connection manager specअगरic मुक्तze_noirq
 * @thaw_noirq: Connection manager specअगरic thaw_noirq
 * @complete: Connection manager specअगरic complete
 * @runसमय_suspend: Connection manager specअगरic runसमय_suspend
 * @runसमय_resume: Connection manager specअगरic runसमय_resume
 * @runसमय_suspend_चयन: Runसमय suspend a चयन
 * @runसमय_resume_चयन: Runसमय resume a चयन
 * @handle_event: Handle thunderbolt event
 * @get_boot_acl: Get boot ACL list
 * @set_boot_acl: Set boot ACL list
 * @disapprove_चयन: Disapprove चयन (disconnect PCIe tunnel)
 * @approve_चयन: Approve चयन
 * @add_चयन_key: Add key to चयन
 * @challenge_चयन_key: Challenge चयन using key
 * @disconnect_pcie_paths: Disconnects PCIe paths beक्रमe NVM update
 * @approve_xकरोमुख्य_paths: Approve (establish) XDoमुख्य DMA paths
 * @disconnect_xकरोमुख्य_paths: Disconnect XDoमुख्य DMA paths
 * @usb4_चयन_op: Optional proxy क्रम USB4 router operations. If set
 *		    this will be called whenever USB4 router operation is
 *		    perक्रमmed. If this वापसs %-EOPNOTSUPP then the
 *		    native USB4 router operation is called.
 * @usb4_चयन_nvm_authenticate_status: Optional callback that the CM
 *					 implementation can be used to
 *					 वापस status of USB4 NVM_AUTH
 *					 router operation.
 */
काष्ठा tb_cm_ops अणु
	पूर्णांक (*driver_पढ़ोy)(काष्ठा tb *tb);
	पूर्णांक (*start)(काष्ठा tb *tb);
	व्योम (*stop)(काष्ठा tb *tb);
	पूर्णांक (*suspend_noirq)(काष्ठा tb *tb);
	पूर्णांक (*resume_noirq)(काष्ठा tb *tb);
	पूर्णांक (*suspend)(काष्ठा tb *tb);
	पूर्णांक (*मुक्तze_noirq)(काष्ठा tb *tb);
	पूर्णांक (*thaw_noirq)(काष्ठा tb *tb);
	व्योम (*complete)(काष्ठा tb *tb);
	पूर्णांक (*runसमय_suspend)(काष्ठा tb *tb);
	पूर्णांक (*runसमय_resume)(काष्ठा tb *tb);
	पूर्णांक (*runसमय_suspend_चयन)(काष्ठा tb_चयन *sw);
	पूर्णांक (*runसमय_resume_चयन)(काष्ठा tb_चयन *sw);
	व्योम (*handle_event)(काष्ठा tb *tb, क्रमागत tb_cfg_pkg_type,
			     स्थिर व्योम *buf, माप_प्रकार size);
	पूर्णांक (*get_boot_acl)(काष्ठा tb *tb, uuid_t *uuids, माप_प्रकार nuuids);
	पूर्णांक (*set_boot_acl)(काष्ठा tb *tb, स्थिर uuid_t *uuids, माप_प्रकार nuuids);
	पूर्णांक (*disapprove_चयन)(काष्ठा tb *tb, काष्ठा tb_चयन *sw);
	पूर्णांक (*approve_चयन)(काष्ठा tb *tb, काष्ठा tb_चयन *sw);
	पूर्णांक (*add_चयन_key)(काष्ठा tb *tb, काष्ठा tb_चयन *sw);
	पूर्णांक (*challenge_चयन_key)(काष्ठा tb *tb, काष्ठा tb_चयन *sw,
				    स्थिर u8 *challenge, u8 *response);
	पूर्णांक (*disconnect_pcie_paths)(काष्ठा tb *tb);
	पूर्णांक (*approve_xकरोमुख्य_paths)(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
				     पूर्णांक transmit_path, पूर्णांक transmit_ring,
				     पूर्णांक receive_path, पूर्णांक receive_ring);
	पूर्णांक (*disconnect_xकरोमुख्य_paths)(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
					पूर्णांक transmit_path, पूर्णांक transmit_ring,
					पूर्णांक receive_path, पूर्णांक receive_ring);
	पूर्णांक (*usb4_चयन_op)(काष्ठा tb_चयन *sw, u16 opcode, u32 *metadata,
			      u8 *status, स्थिर व्योम *tx_data, माप_प्रकार tx_data_len,
			      व्योम *rx_data, माप_प्रकार rx_data_len);
	पूर्णांक (*usb4_चयन_nvm_authenticate_status)(काष्ठा tb_चयन *sw,
						   u32 *status);
पूर्ण;

अटल अंतरभूत व्योम *tb_priv(काष्ठा tb *tb)
अणु
	वापस (व्योम *)tb->privdata;
पूर्ण

#घोषणा TB_AUTOSUSPEND_DELAY		15000 /* ms */

/* helper functions & macros */

/**
 * tb_upstream_port() - वापस the upstream port of a चयन
 *
 * Every चयन has an upstream port (क्रम the root चयन it is the NHI).
 *
 * During चयन alloc/init tb_upstream_port()->remote may be शून्य, even क्रम
 * non root चयनes (on the NHI port remote is always शून्य).
 *
 * Return: Returns the upstream port of the चयन.
 */
अटल अंतरभूत काष्ठा tb_port *tb_upstream_port(काष्ठा tb_चयन *sw)
अणु
	वापस &sw->ports[sw->config.upstream_port_number];
पूर्ण

/**
 * tb_is_upstream_port() - Is the port upstream facing
 * @port: Port to check
 *
 * Returns true अगर @port is upstream facing port. In हाल of dual link
 * ports both वापस true.
 */
अटल अंतरभूत bool tb_is_upstream_port(स्थिर काष्ठा tb_port *port)
अणु
	स्थिर काष्ठा tb_port *upstream_port = tb_upstream_port(port->sw);
	वापस port == upstream_port || port->dual_link_port == upstream_port;
पूर्ण

अटल अंतरभूत u64 tb_route(स्थिर काष्ठा tb_चयन *sw)
अणु
	वापस ((u64) sw->config.route_hi) << 32 | sw->config.route_lo;
पूर्ण

अटल अंतरभूत काष्ठा tb_port *tb_port_at(u64 route, काष्ठा tb_चयन *sw)
अणु
	u8 port;

	port = route >> (sw->config.depth * 8);
	अगर (WARN_ON(port > sw->config.max_port_number))
		वापस शून्य;
	वापस &sw->ports[port];
पूर्ण

/**
 * tb_port_has_remote() - Does the port have चयन connected करोwnstream
 * @port: Port to check
 *
 * Returns true only when the port is primary port and has remote set.
 */
अटल अंतरभूत bool tb_port_has_remote(स्थिर काष्ठा tb_port *port)
अणु
	अगर (tb_is_upstream_port(port))
		वापस false;
	अगर (!port->remote)
		वापस false;
	अगर (port->dual_link_port && port->link_nr)
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत bool tb_port_is_null(स्थिर काष्ठा tb_port *port)
अणु
	वापस port && port->port && port->config.type == TB_TYPE_PORT;
पूर्ण

अटल अंतरभूत bool tb_port_is_nhi(स्थिर काष्ठा tb_port *port)
अणु
	वापस port && port->config.type == TB_TYPE_NHI;
पूर्ण

अटल अंतरभूत bool tb_port_is_pcie_करोwn(स्थिर काष्ठा tb_port *port)
अणु
	वापस port && port->config.type == TB_TYPE_PCIE_DOWN;
पूर्ण

अटल अंतरभूत bool tb_port_is_pcie_up(स्थिर काष्ठा tb_port *port)
अणु
	वापस port && port->config.type == TB_TYPE_PCIE_UP;
पूर्ण

अटल अंतरभूत bool tb_port_is_dpin(स्थिर काष्ठा tb_port *port)
अणु
	वापस port && port->config.type == TB_TYPE_DP_HDMI_IN;
पूर्ण

अटल अंतरभूत bool tb_port_is_dpout(स्थिर काष्ठा tb_port *port)
अणु
	वापस port && port->config.type == TB_TYPE_DP_HDMI_OUT;
पूर्ण

अटल अंतरभूत bool tb_port_is_usb3_करोwn(स्थिर काष्ठा tb_port *port)
अणु
	वापस port && port->config.type == TB_TYPE_USB3_DOWN;
पूर्ण

अटल अंतरभूत bool tb_port_is_usb3_up(स्थिर काष्ठा tb_port *port)
अणु
	वापस port && port->config.type == TB_TYPE_USB3_UP;
पूर्ण

अटल अंतरभूत पूर्णांक tb_sw_पढ़ो(काष्ठा tb_चयन *sw, व्योम *buffer,
			     क्रमागत tb_cfg_space space, u32 offset, u32 length)
अणु
	अगर (sw->is_unplugged)
		वापस -ENODEV;
	वापस tb_cfg_पढ़ो(sw->tb->ctl,
			   buffer,
			   tb_route(sw),
			   0,
			   space,
			   offset,
			   length);
पूर्ण

अटल अंतरभूत पूर्णांक tb_sw_ग_लिखो(काष्ठा tb_चयन *sw, स्थिर व्योम *buffer,
			      क्रमागत tb_cfg_space space, u32 offset, u32 length)
अणु
	अगर (sw->is_unplugged)
		वापस -ENODEV;
	वापस tb_cfg_ग_लिखो(sw->tb->ctl,
			    buffer,
			    tb_route(sw),
			    0,
			    space,
			    offset,
			    length);
पूर्ण

अटल अंतरभूत पूर्णांक tb_port_पढ़ो(काष्ठा tb_port *port, व्योम *buffer,
			       क्रमागत tb_cfg_space space, u32 offset, u32 length)
अणु
	अगर (port->sw->is_unplugged)
		वापस -ENODEV;
	वापस tb_cfg_पढ़ो(port->sw->tb->ctl,
			   buffer,
			   tb_route(port->sw),
			   port->port,
			   space,
			   offset,
			   length);
पूर्ण

अटल अंतरभूत पूर्णांक tb_port_ग_लिखो(काष्ठा tb_port *port, स्थिर व्योम *buffer,
				क्रमागत tb_cfg_space space, u32 offset, u32 length)
अणु
	अगर (port->sw->is_unplugged)
		वापस -ENODEV;
	वापस tb_cfg_ग_लिखो(port->sw->tb->ctl,
			    buffer,
			    tb_route(port->sw),
			    port->port,
			    space,
			    offset,
			    length);
पूर्ण

#घोषणा tb_err(tb, fmt, arg...) dev_err(&(tb)->nhi->pdev->dev, fmt, ## arg)
#घोषणा tb_WARN(tb, fmt, arg...) dev_WARN(&(tb)->nhi->pdev->dev, fmt, ## arg)
#घोषणा tb_warn(tb, fmt, arg...) dev_warn(&(tb)->nhi->pdev->dev, fmt, ## arg)
#घोषणा tb_info(tb, fmt, arg...) dev_info(&(tb)->nhi->pdev->dev, fmt, ## arg)
#घोषणा tb_dbg(tb, fmt, arg...) dev_dbg(&(tb)->nhi->pdev->dev, fmt, ## arg)

#घोषणा __TB_SW_PRINT(level, sw, fmt, arg...)           \
	करो अणु                                            \
		स्थिर काष्ठा tb_चयन *__sw = (sw);    \
		level(__sw->tb, "%llx: " fmt,           \
		      tb_route(__sw), ## arg);          \
	पूर्ण जबतक (0)
#घोषणा tb_sw_WARN(sw, fmt, arg...) __TB_SW_PRINT(tb_WARN, sw, fmt, ##arg)
#घोषणा tb_sw_warn(sw, fmt, arg...) __TB_SW_PRINT(tb_warn, sw, fmt, ##arg)
#घोषणा tb_sw_info(sw, fmt, arg...) __TB_SW_PRINT(tb_info, sw, fmt, ##arg)
#घोषणा tb_sw_dbg(sw, fmt, arg...) __TB_SW_PRINT(tb_dbg, sw, fmt, ##arg)

#घोषणा __TB_PORT_PRINT(level, _port, fmt, arg...)                      \
	करो अणु                                                            \
		स्थिर काष्ठा tb_port *__port = (_port);                 \
		level(__port->sw->tb, "%llx:%x: " fmt,                  \
		      tb_route(__port->sw), __port->port, ## arg);      \
	पूर्ण जबतक (0)
#घोषणा tb_port_WARN(port, fmt, arg...) \
	__TB_PORT_PRINT(tb_WARN, port, fmt, ##arg)
#घोषणा tb_port_warn(port, fmt, arg...) \
	__TB_PORT_PRINT(tb_warn, port, fmt, ##arg)
#घोषणा tb_port_info(port, fmt, arg...) \
	__TB_PORT_PRINT(tb_info, port, fmt, ##arg)
#घोषणा tb_port_dbg(port, fmt, arg...) \
	__TB_PORT_PRINT(tb_dbg, port, fmt, ##arg)

काष्ठा tb *icm_probe(काष्ठा tb_nhi *nhi);
काष्ठा tb *tb_probe(काष्ठा tb_nhi *nhi);

बाह्य काष्ठा device_type tb_करोमुख्य_type;
बाह्य काष्ठा device_type tb_reसमयr_type;
बाह्य काष्ठा device_type tb_चयन_type;

पूर्णांक tb_करोमुख्य_init(व्योम);
व्योम tb_करोमुख्य_निकास(व्योम);
पूर्णांक tb_xकरोमुख्य_init(व्योम);
व्योम tb_xकरोमुख्य_निकास(व्योम);

काष्ठा tb *tb_करोमुख्य_alloc(काष्ठा tb_nhi *nhi, पूर्णांक समयout_msec, माप_प्रकार privsize);
पूर्णांक tb_करोमुख्य_add(काष्ठा tb *tb);
व्योम tb_करोमुख्य_हटाओ(काष्ठा tb *tb);
पूर्णांक tb_करोमुख्य_suspend_noirq(काष्ठा tb *tb);
पूर्णांक tb_करोमुख्य_resume_noirq(काष्ठा tb *tb);
पूर्णांक tb_करोमुख्य_suspend(काष्ठा tb *tb);
पूर्णांक tb_करोमुख्य_मुक्तze_noirq(काष्ठा tb *tb);
पूर्णांक tb_करोमुख्य_thaw_noirq(काष्ठा tb *tb);
व्योम tb_करोमुख्य_complete(काष्ठा tb *tb);
पूर्णांक tb_करोमुख्य_runसमय_suspend(काष्ठा tb *tb);
पूर्णांक tb_करोमुख्य_runसमय_resume(काष्ठा tb *tb);
पूर्णांक tb_करोमुख्य_disapprove_चयन(काष्ठा tb *tb, काष्ठा tb_चयन *sw);
पूर्णांक tb_करोमुख्य_approve_चयन(काष्ठा tb *tb, काष्ठा tb_चयन *sw);
पूर्णांक tb_करोमुख्य_approve_चयन_key(काष्ठा tb *tb, काष्ठा tb_चयन *sw);
पूर्णांक tb_करोमुख्य_challenge_चयन_key(काष्ठा tb *tb, काष्ठा tb_चयन *sw);
पूर्णांक tb_करोमुख्य_disconnect_pcie_paths(काष्ठा tb *tb);
पूर्णांक tb_करोमुख्य_approve_xकरोमुख्य_paths(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
				    पूर्णांक transmit_path, पूर्णांक transmit_ring,
				    पूर्णांक receive_path, पूर्णांक receive_ring);
पूर्णांक tb_करोमुख्य_disconnect_xकरोमुख्य_paths(काष्ठा tb *tb, काष्ठा tb_xकरोमुख्य *xd,
				       पूर्णांक transmit_path, पूर्णांक transmit_ring,
				       पूर्णांक receive_path, पूर्णांक receive_ring);
पूर्णांक tb_करोमुख्य_disconnect_all_paths(काष्ठा tb *tb);

अटल अंतरभूत काष्ठा tb *tb_करोमुख्य_get(काष्ठा tb *tb)
अणु
	अगर (tb)
		get_device(&tb->dev);
	वापस tb;
पूर्ण

अटल अंतरभूत व्योम tb_करोमुख्य_put(काष्ठा tb *tb)
अणु
	put_device(&tb->dev);
पूर्ण

काष्ठा tb_nvm *tb_nvm_alloc(काष्ठा device *dev);
पूर्णांक tb_nvm_add_active(काष्ठा tb_nvm *nvm, माप_प्रकार size, nvmem_reg_पढ़ो_t reg_पढ़ो);
पूर्णांक tb_nvm_ग_लिखो_buf(काष्ठा tb_nvm *nvm, अचिन्हित पूर्णांक offset, व्योम *val,
		     माप_प्रकार bytes);
पूर्णांक tb_nvm_add_non_active(काष्ठा tb_nvm *nvm, माप_प्रकार size,
			  nvmem_reg_ग_लिखो_t reg_ग_लिखो);
व्योम tb_nvm_मुक्त(काष्ठा tb_nvm *nvm);
व्योम tb_nvm_निकास(व्योम);

काष्ठा tb_चयन *tb_चयन_alloc(काष्ठा tb *tb, काष्ठा device *parent,
				  u64 route);
काष्ठा tb_चयन *tb_चयन_alloc_safe_mode(काष्ठा tb *tb,
			काष्ठा device *parent, u64 route);
पूर्णांक tb_चयन_configure(काष्ठा tb_चयन *sw);
पूर्णांक tb_चयन_add(काष्ठा tb_चयन *sw);
व्योम tb_चयन_हटाओ(काष्ठा tb_चयन *sw);
व्योम tb_चयन_suspend(काष्ठा tb_चयन *sw, bool runसमय);
पूर्णांक tb_चयन_resume(काष्ठा tb_चयन *sw);
पूर्णांक tb_चयन_reset(काष्ठा tb_चयन *sw);
व्योम tb_sw_set_unplugged(काष्ठा tb_चयन *sw);
काष्ठा tb_port *tb_चयन_find_port(काष्ठा tb_चयन *sw,
				    क्रमागत tb_port_type type);
काष्ठा tb_चयन *tb_चयन_find_by_link_depth(काष्ठा tb *tb, u8 link,
					       u8 depth);
काष्ठा tb_चयन *tb_चयन_find_by_uuid(काष्ठा tb *tb, स्थिर uuid_t *uuid);
काष्ठा tb_चयन *tb_चयन_find_by_route(काष्ठा tb *tb, u64 route);

/**
 * tb_चयन_क्रम_each_port() - Iterate over each चयन port
 * @sw: Switch whose ports to iterate
 * @p: Port used as iterator
 *
 * Iterates over each चयन port skipping the control port (port %0).
 */
#घोषणा tb_चयन_क्रम_each_port(sw, p)					\
	क्रम ((p) = &(sw)->ports[1];					\
	     (p) <= &(sw)->ports[(sw)->config.max_port_number]; (p)++)

अटल अंतरभूत काष्ठा tb_चयन *tb_चयन_get(काष्ठा tb_चयन *sw)
अणु
	अगर (sw)
		get_device(&sw->dev);
	वापस sw;
पूर्ण

अटल अंतरभूत व्योम tb_चयन_put(काष्ठा tb_चयन *sw)
अणु
	put_device(&sw->dev);
पूर्ण

अटल अंतरभूत bool tb_is_चयन(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &tb_चयन_type;
पूर्ण

अटल अंतरभूत काष्ठा tb_चयन *tb_to_चयन(काष्ठा device *dev)
अणु
	अगर (tb_is_चयन(dev))
		वापस container_of(dev, काष्ठा tb_चयन, dev);
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा tb_चयन *tb_चयन_parent(काष्ठा tb_चयन *sw)
अणु
	वापस tb_to_चयन(sw->dev.parent);
पूर्ण

अटल अंतरभूत bool tb_चयन_is_light_ridge(स्थिर काष्ठा tb_चयन *sw)
अणु
	वापस sw->config.venकरोr_id == PCI_VENDOR_ID_INTEL &&
	       sw->config.device_id == PCI_DEVICE_ID_INTEL_LIGHT_RIDGE;
पूर्ण

अटल अंतरभूत bool tb_चयन_is_eagle_ridge(स्थिर काष्ठा tb_चयन *sw)
अणु
	वापस sw->config.venकरोr_id == PCI_VENDOR_ID_INTEL &&
	       sw->config.device_id == PCI_DEVICE_ID_INTEL_EAGLE_RIDGE;
पूर्ण

अटल अंतरभूत bool tb_चयन_is_cactus_ridge(स्थिर काष्ठा tb_चयन *sw)
अणु
	अगर (sw->config.venकरोr_id == PCI_VENDOR_ID_INTEL) अणु
		चयन (sw->config.device_id) अणु
		हाल PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_2C:
		हाल PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_4C:
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool tb_चयन_is_falcon_ridge(स्थिर काष्ठा tb_चयन *sw)
अणु
	अगर (sw->config.venकरोr_id == PCI_VENDOR_ID_INTEL) अणु
		चयन (sw->config.device_id) अणु
		हाल PCI_DEVICE_ID_INTEL_FALCON_RIDGE_2C_BRIDGE:
		हाल PCI_DEVICE_ID_INTEL_FALCON_RIDGE_4C_BRIDGE:
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool tb_चयन_is_alpine_ridge(स्थिर काष्ठा tb_चयन *sw)
अणु
	अगर (sw->config.venकरोr_id == PCI_VENDOR_ID_INTEL) अणु
		चयन (sw->config.device_id) अणु
		हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_BRIDGE:
		हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_BRIDGE:
		हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_BRIDGE:
		हाल PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_BRIDGE:
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool tb_चयन_is_titan_ridge(स्थिर काष्ठा tb_चयन *sw)
अणु
	अगर (sw->config.venकरोr_id == PCI_VENDOR_ID_INTEL) अणु
		चयन (sw->config.device_id) अणु
		हाल PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_BRIDGE:
		हाल PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_BRIDGE:
		हाल PCI_DEVICE_ID_INTEL_TITAN_RIDGE_DD_BRIDGE:
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/**
 * tb_चयन_is_usb4() - Is the चयन USB4 compliant
 * @sw: Switch to check
 *
 * Returns true अगर the @sw is USB4 compliant router, false otherwise.
 */
अटल अंतरभूत bool tb_चयन_is_usb4(स्थिर काष्ठा tb_चयन *sw)
अणु
	वापस sw->config.thunderbolt_version == USB4_VERSION_1_0;
पूर्ण

/**
 * tb_चयन_is_icm() - Is the चयन handled by ICM firmware
 * @sw: Switch to check
 *
 * In हाल there is a need to dअगरferentiate whether ICM firmware or SW CM
 * is handling @sw this function can be called. It is valid to call this
 * after tb_चयन_alloc() and tb_चयन_configure() has been called
 * (latter only क्रम SW CM हाल).
 */
अटल अंतरभूत bool tb_चयन_is_icm(स्थिर काष्ठा tb_चयन *sw)
अणु
	वापस !sw->config.enabled;
पूर्ण

पूर्णांक tb_चयन_lane_bonding_enable(काष्ठा tb_चयन *sw);
व्योम tb_चयन_lane_bonding_disable(काष्ठा tb_चयन *sw);
पूर्णांक tb_चयन_configure_link(काष्ठा tb_चयन *sw);
व्योम tb_चयन_unconfigure_link(काष्ठा tb_चयन *sw);

bool tb_चयन_query_dp_resource(काष्ठा tb_चयन *sw, काष्ठा tb_port *in);
पूर्णांक tb_चयन_alloc_dp_resource(काष्ठा tb_चयन *sw, काष्ठा tb_port *in);
व्योम tb_चयन_dealloc_dp_resource(काष्ठा tb_चयन *sw, काष्ठा tb_port *in);

पूर्णांक tb_चयन_पंचांगu_init(काष्ठा tb_चयन *sw);
पूर्णांक tb_चयन_पंचांगu_post_समय(काष्ठा tb_चयन *sw);
पूर्णांक tb_चयन_पंचांगu_disable(काष्ठा tb_चयन *sw);
पूर्णांक tb_चयन_पंचांगu_enable(काष्ठा tb_चयन *sw);

अटल अंतरभूत bool tb_चयन_पंचांगu_is_enabled(स्थिर काष्ठा tb_चयन *sw)
अणु
	वापस sw->पंचांगu.rate == TB_SWITCH_TMU_RATE_HIFI &&
	       !sw->पंचांगu.unidirectional;
पूर्ण

पूर्णांक tb_रुको_क्रम_port(काष्ठा tb_port *port, bool रुको_अगर_unplugged);
पूर्णांक tb_port_add_nfc_credits(काष्ठा tb_port *port, पूर्णांक credits);
पूर्णांक tb_port_clear_counter(काष्ठा tb_port *port, पूर्णांक counter);
पूर्णांक tb_port_unlock(काष्ठा tb_port *port);
पूर्णांक tb_port_enable(काष्ठा tb_port *port);
पूर्णांक tb_port_disable(काष्ठा tb_port *port);
पूर्णांक tb_port_alloc_in_hopid(काष्ठा tb_port *port, पूर्णांक hopid, पूर्णांक max_hopid);
व्योम tb_port_release_in_hopid(काष्ठा tb_port *port, पूर्णांक hopid);
पूर्णांक tb_port_alloc_out_hopid(काष्ठा tb_port *port, पूर्णांक hopid, पूर्णांक max_hopid);
व्योम tb_port_release_out_hopid(काष्ठा tb_port *port, पूर्णांक hopid);
काष्ठा tb_port *tb_next_port_on_path(काष्ठा tb_port *start, काष्ठा tb_port *end,
				     काष्ठा tb_port *prev);

/**
 * tb_क्रम_each_port_on_path() - Iterate over each port on path
 * @src: Source port
 * @dst: Destination port
 * @p: Port used as iterator
 *
 * Walks over each port on path from @src to @dst.
 */
#घोषणा tb_क्रम_each_port_on_path(src, dst, p)				\
	क्रम ((p) = tb_next_port_on_path((src), (dst), शून्य); (p);	\
	     (p) = tb_next_port_on_path((src), (dst), (p)))

पूर्णांक tb_port_get_link_speed(काष्ठा tb_port *port);
पूर्णांक tb_port_get_link_width(काष्ठा tb_port *port);
पूर्णांक tb_port_state(काष्ठा tb_port *port);
पूर्णांक tb_port_lane_bonding_enable(काष्ठा tb_port *port);
व्योम tb_port_lane_bonding_disable(काष्ठा tb_port *port);

पूर्णांक tb_चयन_find_vse_cap(काष्ठा tb_चयन *sw, क्रमागत tb_चयन_vse_cap vsec);
पूर्णांक tb_चयन_find_cap(काष्ठा tb_चयन *sw, क्रमागत tb_चयन_cap cap);
पूर्णांक tb_चयन_next_cap(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक offset);
पूर्णांक tb_port_find_cap(काष्ठा tb_port *port, क्रमागत tb_port_cap cap);
पूर्णांक tb_port_next_cap(काष्ठा tb_port *port, अचिन्हित पूर्णांक offset);
bool tb_port_is_enabled(काष्ठा tb_port *port);

bool tb_usb3_port_is_enabled(काष्ठा tb_port *port);
पूर्णांक tb_usb3_port_enable(काष्ठा tb_port *port, bool enable);

bool tb_pci_port_is_enabled(काष्ठा tb_port *port);
पूर्णांक tb_pci_port_enable(काष्ठा tb_port *port, bool enable);

पूर्णांक tb_dp_port_hpd_is_active(काष्ठा tb_port *port);
पूर्णांक tb_dp_port_hpd_clear(काष्ठा tb_port *port);
पूर्णांक tb_dp_port_set_hops(काष्ठा tb_port *port, अचिन्हित पूर्णांक video,
			अचिन्हित पूर्णांक aux_tx, अचिन्हित पूर्णांक aux_rx);
bool tb_dp_port_is_enabled(काष्ठा tb_port *port);
पूर्णांक tb_dp_port_enable(काष्ठा tb_port *port, bool enable);

काष्ठा tb_path *tb_path_discover(काष्ठा tb_port *src, पूर्णांक src_hopid,
				 काष्ठा tb_port *dst, पूर्णांक dst_hopid,
				 काष्ठा tb_port **last, स्थिर अक्षर *name);
काष्ठा tb_path *tb_path_alloc(काष्ठा tb *tb, काष्ठा tb_port *src, पूर्णांक src_hopid,
			      काष्ठा tb_port *dst, पूर्णांक dst_hopid, पूर्णांक link_nr,
			      स्थिर अक्षर *name);
व्योम tb_path_मुक्त(काष्ठा tb_path *path);
पूर्णांक tb_path_activate(काष्ठा tb_path *path);
व्योम tb_path_deactivate(काष्ठा tb_path *path);
bool tb_path_is_invalid(काष्ठा tb_path *path);
bool tb_path_port_on_path(स्थिर काष्ठा tb_path *path,
			  स्थिर काष्ठा tb_port *port);

पूर्णांक tb_drom_पढ़ो(काष्ठा tb_चयन *sw);
पूर्णांक tb_drom_पढ़ो_uid_only(काष्ठा tb_चयन *sw, u64 *uid);

पूर्णांक tb_lc_पढ़ो_uuid(काष्ठा tb_चयन *sw, u32 *uuid);
पूर्णांक tb_lc_configure_port(काष्ठा tb_port *port);
व्योम tb_lc_unconfigure_port(काष्ठा tb_port *port);
पूर्णांक tb_lc_configure_xकरोमुख्य(काष्ठा tb_port *port);
व्योम tb_lc_unconfigure_xकरोमुख्य(काष्ठा tb_port *port);
पूर्णांक tb_lc_start_lane_initialization(काष्ठा tb_port *port);
पूर्णांक tb_lc_set_wake(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक flags);
पूर्णांक tb_lc_set_sleep(काष्ठा tb_चयन *sw);
bool tb_lc_lane_bonding_possible(काष्ठा tb_चयन *sw);
bool tb_lc_dp_sink_query(काष्ठा tb_चयन *sw, काष्ठा tb_port *in);
पूर्णांक tb_lc_dp_sink_alloc(काष्ठा tb_चयन *sw, काष्ठा tb_port *in);
पूर्णांक tb_lc_dp_sink_dealloc(काष्ठा tb_चयन *sw, काष्ठा tb_port *in);
पूर्णांक tb_lc_क्रमce_घातer(काष्ठा tb_चयन *sw);

अटल अंतरभूत पूर्णांक tb_route_length(u64 route)
अणु
	वापस (fls64(route) + TB_ROUTE_SHIFT - 1) / TB_ROUTE_SHIFT;
पूर्ण

/**
 * tb_करोwnstream_route() - get route to करोwnstream चयन
 *
 * Port must not be the upstream port (otherwise a loop is created).
 *
 * Return: Returns a route to the चयन behind @port.
 */
अटल अंतरभूत u64 tb_करोwnstream_route(काष्ठा tb_port *port)
अणु
	वापस tb_route(port->sw)
	       | ((u64) port->port << (port->sw->config.depth * 8));
पूर्ण

bool tb_is_xकरोमुख्य_enabled(व्योम);
bool tb_xकरोमुख्य_handle_request(काष्ठा tb *tb, क्रमागत tb_cfg_pkg_type type,
			       स्थिर व्योम *buf, माप_प्रकार size);
काष्ठा tb_xकरोमुख्य *tb_xकरोमुख्य_alloc(काष्ठा tb *tb, काष्ठा device *parent,
				    u64 route, स्थिर uuid_t *local_uuid,
				    स्थिर uuid_t *remote_uuid);
व्योम tb_xकरोमुख्य_add(काष्ठा tb_xकरोमुख्य *xd);
व्योम tb_xकरोमुख्य_हटाओ(काष्ठा tb_xकरोमुख्य *xd);
काष्ठा tb_xकरोमुख्य *tb_xकरोमुख्य_find_by_link_depth(काष्ठा tb *tb, u8 link,
						 u8 depth);

पूर्णांक tb_reसमयr_scan(काष्ठा tb_port *port);
व्योम tb_reसमयr_हटाओ_all(काष्ठा tb_port *port);

अटल अंतरभूत bool tb_is_reसमयr(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &tb_reसमयr_type;
पूर्ण

अटल अंतरभूत काष्ठा tb_reसमयr *tb_to_reसमयr(काष्ठा device *dev)
अणु
	अगर (tb_is_reसमयr(dev))
		वापस container_of(dev, काष्ठा tb_reसमयr, dev);
	वापस शून्य;
पूर्ण

पूर्णांक usb4_चयन_setup(काष्ठा tb_चयन *sw);
पूर्णांक usb4_चयन_पढ़ो_uid(काष्ठा tb_चयन *sw, u64 *uid);
पूर्णांक usb4_चयन_drom_पढ़ो(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक address, व्योम *buf,
			  माप_प्रकार size);
bool usb4_चयन_lane_bonding_possible(काष्ठा tb_चयन *sw);
पूर्णांक usb4_चयन_set_wake(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक flags);
पूर्णांक usb4_चयन_set_sleep(काष्ठा tb_चयन *sw);
पूर्णांक usb4_चयन_nvm_sector_size(काष्ठा tb_चयन *sw);
पूर्णांक usb4_चयन_nvm_पढ़ो(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक address, व्योम *buf,
			 माप_प्रकार size);
पूर्णांक usb4_चयन_nvm_ग_लिखो(काष्ठा tb_चयन *sw, अचिन्हित पूर्णांक address,
			  स्थिर व्योम *buf, माप_प्रकार size);
पूर्णांक usb4_चयन_nvm_authenticate(काष्ठा tb_चयन *sw);
पूर्णांक usb4_चयन_nvm_authenticate_status(काष्ठा tb_चयन *sw, u32 *status);
bool usb4_चयन_query_dp_resource(काष्ठा tb_चयन *sw, काष्ठा tb_port *in);
पूर्णांक usb4_चयन_alloc_dp_resource(काष्ठा tb_चयन *sw, काष्ठा tb_port *in);
पूर्णांक usb4_चयन_dealloc_dp_resource(काष्ठा tb_चयन *sw, काष्ठा tb_port *in);
काष्ठा tb_port *usb4_चयन_map_pcie_करोwn(काष्ठा tb_चयन *sw,
					  स्थिर काष्ठा tb_port *port);
काष्ठा tb_port *usb4_चयन_map_usb3_करोwn(काष्ठा tb_चयन *sw,
					  स्थिर काष्ठा tb_port *port);

पूर्णांक usb4_port_unlock(काष्ठा tb_port *port);
पूर्णांक usb4_port_configure(काष्ठा tb_port *port);
व्योम usb4_port_unconfigure(काष्ठा tb_port *port);
पूर्णांक usb4_port_configure_xकरोमुख्य(काष्ठा tb_port *port);
व्योम usb4_port_unconfigure_xकरोमुख्य(काष्ठा tb_port *port);
पूर्णांक usb4_port_क्रमागतerate_reसमयrs(काष्ठा tb_port *port);

पूर्णांक usb4_port_reसमयr_पढ़ो(काष्ठा tb_port *port, u8 index, u8 reg, व्योम *buf,
			   u8 size);
पूर्णांक usb4_port_reसमयr_ग_लिखो(काष्ठा tb_port *port, u8 index, u8 reg,
			    स्थिर व्योम *buf, u8 size);
पूर्णांक usb4_port_reसमयr_is_last(काष्ठा tb_port *port, u8 index);
पूर्णांक usb4_port_reसमयr_nvm_sector_size(काष्ठा tb_port *port, u8 index);
पूर्णांक usb4_port_reसमयr_nvm_ग_लिखो(काष्ठा tb_port *port, u8 index,
				अचिन्हित पूर्णांक address, स्थिर व्योम *buf,
				माप_प्रकार size);
पूर्णांक usb4_port_reसमयr_nvm_authenticate(काष्ठा tb_port *port, u8 index);
पूर्णांक usb4_port_reसमयr_nvm_authenticate_status(काष्ठा tb_port *port, u8 index,
					      u32 *status);
पूर्णांक usb4_port_reसमयr_nvm_पढ़ो(काष्ठा tb_port *port, u8 index,
			       अचिन्हित पूर्णांक address, व्योम *buf, माप_प्रकार size);

पूर्णांक usb4_usb3_port_max_link_rate(काष्ठा tb_port *port);
पूर्णांक usb4_usb3_port_actual_link_rate(काष्ठा tb_port *port);
पूर्णांक usb4_usb3_port_allocated_bandwidth(काष्ठा tb_port *port, पूर्णांक *upstream_bw,
				       पूर्णांक *करोwnstream_bw);
पूर्णांक usb4_usb3_port_allocate_bandwidth(काष्ठा tb_port *port, पूर्णांक *upstream_bw,
				      पूर्णांक *करोwnstream_bw);
पूर्णांक usb4_usb3_port_release_bandwidth(काष्ठा tb_port *port, पूर्णांक *upstream_bw,
				     पूर्णांक *करोwnstream_bw);

/* Keep link controller awake during update */
#घोषणा QUIRK_FORCE_POWER_LINK_CONTROLLER		BIT(0)

व्योम tb_check_quirks(काष्ठा tb_चयन *sw);

#अगर_घोषित CONFIG_ACPI
व्योम tb_acpi_add_links(काष्ठा tb_nhi *nhi);

bool tb_acpi_is_native(व्योम);
bool tb_acpi_may_tunnel_usb3(व्योम);
bool tb_acpi_may_tunnel_dp(व्योम);
bool tb_acpi_may_tunnel_pcie(व्योम);
bool tb_acpi_is_xकरोमुख्य_allowed(व्योम);
#अन्यथा
अटल अंतरभूत व्योम tb_acpi_add_links(काष्ठा tb_nhi *nhi) अणु पूर्ण

अटल अंतरभूत bool tb_acpi_is_native(व्योम) अणु वापस true; पूर्ण
अटल अंतरभूत bool tb_acpi_may_tunnel_usb3(व्योम) अणु वापस true; पूर्ण
अटल अंतरभूत bool tb_acpi_may_tunnel_dp(व्योम) अणु वापस true; पूर्ण
अटल अंतरभूत bool tb_acpi_may_tunnel_pcie(व्योम) अणु वापस true; पूर्ण
अटल अंतरभूत bool tb_acpi_is_xकरोमुख्य_allowed(व्योम) अणु वापस true; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_FS
व्योम tb_debugfs_init(व्योम);
व्योम tb_debugfs_निकास(व्योम);
व्योम tb_चयन_debugfs_init(काष्ठा tb_चयन *sw);
व्योम tb_चयन_debugfs_हटाओ(काष्ठा tb_चयन *sw);
व्योम tb_service_debugfs_init(काष्ठा tb_service *svc);
व्योम tb_service_debugfs_हटाओ(काष्ठा tb_service *svc);
#अन्यथा
अटल अंतरभूत व्योम tb_debugfs_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tb_debugfs_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tb_चयन_debugfs_init(काष्ठा tb_चयन *sw) अणु पूर्ण
अटल अंतरभूत व्योम tb_चयन_debugfs_हटाओ(काष्ठा tb_चयन *sw) अणु पूर्ण
अटल अंतरभूत व्योम tb_service_debugfs_init(काष्ठा tb_service *svc) अणु पूर्ण
अटल अंतरभूत व्योम tb_service_debugfs_हटाओ(काष्ठा tb_service *svc) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB4_KUNIT_TEST
पूर्णांक tb_test_init(व्योम);
व्योम tb_test_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक tb_test_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम tb_test_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
