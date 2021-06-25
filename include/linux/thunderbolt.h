<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Thunderbolt service API
 *
 * Copyright (C) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2017, Intel Corporation
 * Authors: Michael Jamet <michael.jamet@पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#अगर_अघोषित THUNDERBOLT_H_
#घोषणा THUNDERBOLT_H_

#समावेश <linux/device.h>
#समावेश <linux/idr.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pci.h>
#समावेश <linux/uuid.h>
#समावेश <linux/workqueue.h>

क्रमागत tb_cfg_pkg_type अणु
	TB_CFG_PKG_READ = 1,
	TB_CFG_PKG_WRITE = 2,
	TB_CFG_PKG_ERROR = 3,
	TB_CFG_PKG_NOTIFY_ACK = 4,
	TB_CFG_PKG_EVENT = 5,
	TB_CFG_PKG_XDOMAIN_REQ = 6,
	TB_CFG_PKG_XDOMAIN_RESP = 7,
	TB_CFG_PKG_OVERRIDE = 8,
	TB_CFG_PKG_RESET = 9,
	TB_CFG_PKG_ICM_EVENT = 10,
	TB_CFG_PKG_ICM_CMD = 11,
	TB_CFG_PKG_ICM_RESP = 12,
	TB_CFG_PKG_PREPARE_TO_SLEEP = 13,
पूर्ण;

/**
 * क्रमागत tb_security_level - Thunderbolt security level
 * @TB_SECURITY_NONE: No security, legacy mode
 * @TB_SECURITY_USER: User approval required at minimum
 * @TB_SECURITY_SECURE: One समय saved key required at minimum
 * @TB_SECURITY_DPONLY: Only tunnel Display port (and USB)
 * @TB_SECURITY_USBONLY: Only tunnel USB controller of the connected
 *			 Thunderbolt करोck (and Display Port). All PCIe
 *			 links करोwnstream of the करोck are हटाओd.
 * @TB_SECURITY_NOPCIE: For USB4 प्रणालीs this level is used when the
 *			PCIe tunneling is disabled from the BIOS.
 */
क्रमागत tb_security_level अणु
	TB_SECURITY_NONE,
	TB_SECURITY_USER,
	TB_SECURITY_SECURE,
	TB_SECURITY_DPONLY,
	TB_SECURITY_USBONLY,
	TB_SECURITY_NOPCIE,
पूर्ण;

/**
 * काष्ठा tb - मुख्य thunderbolt bus काष्ठाure
 * @dev: Doमुख्य device
 * @lock: Big lock. Must be held when accessing any काष्ठा
 *	  tb_चयन / काष्ठा tb_port.
 * @nhi: Poपूर्णांकer to the NHI काष्ठाure
 * @ctl: Control channel क्रम this करोमुख्य
 * @wq: Ordered workqueue क्रम all करोमुख्य specअगरic work
 * @root_चयन: Root चयन of this करोमुख्य
 * @cm_ops: Connection manager specअगरic operations vector
 * @index: Linux asचिन्हित करोमुख्य number
 * @security_level: Current security level
 * @nboot_acl: Number of boot ACLs the करोमुख्य supports
 * @privdata: Private connection manager specअगरic data
 */
काष्ठा tb अणु
	काष्ठा device dev;
	काष्ठा mutex lock;
	काष्ठा tb_nhi *nhi;
	काष्ठा tb_ctl *ctl;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा tb_चयन *root_चयन;
	स्थिर काष्ठा tb_cm_ops *cm_ops;
	पूर्णांक index;
	क्रमागत tb_security_level security_level;
	माप_प्रकार nboot_acl;
	अचिन्हित दीर्घ privdata[];
पूर्ण;

बाह्य काष्ठा bus_type tb_bus_type;
बाह्य काष्ठा device_type tb_service_type;
बाह्य काष्ठा device_type tb_xकरोमुख्य_type;

#घोषणा TB_LINKS_PER_PHY_PORT	2

अटल अंतरभूत अचिन्हित पूर्णांक tb_phy_port_from_link(अचिन्हित पूर्णांक link)
अणु
	वापस (link - 1) / TB_LINKS_PER_PHY_PORT;
पूर्ण

/**
 * काष्ठा tb_property_dir - XDoमुख्य property directory
 * @uuid: Directory UUID or %शून्य अगर root directory
 * @properties: List of properties in this directory
 *
 * User needs to provide serialization अगर needed.
 */
काष्ठा tb_property_dir अणु
	स्थिर uuid_t *uuid;
	काष्ठा list_head properties;
पूर्ण;

क्रमागत tb_property_type अणु
	TB_PROPERTY_TYPE_UNKNOWN = 0x00,
	TB_PROPERTY_TYPE_सूचीECTORY = 0x44,
	TB_PROPERTY_TYPE_DATA = 0x64,
	TB_PROPERTY_TYPE_TEXT = 0x74,
	TB_PROPERTY_TYPE_VALUE = 0x76,
पूर्ण;

#घोषणा TB_PROPERTY_KEY_SIZE	8

/**
 * काष्ठा tb_property - XDoमुख्य property
 * @list: Used to link properties together in a directory
 * @key: Key क्रम the property (always terminated).
 * @type: Type of the property
 * @length: Length of the property data in dwords
 * @value: Property value
 *
 * Users use @type to determine which field in @value is filled.
 */
काष्ठा tb_property अणु
	काष्ठा list_head list;
	अक्षर key[TB_PROPERTY_KEY_SIZE + 1];
	क्रमागत tb_property_type type;
	माप_प्रकार length;
	जोड़ अणु
		काष्ठा tb_property_dir *dir;
		u8 *data;
		अक्षर *text;
		u32 immediate;
	पूर्ण value;
पूर्ण;

काष्ठा tb_property_dir *tb_property_parse_dir(स्थिर u32 *block,
					      माप_प्रकार block_len);
sमाप_प्रकार tb_property_क्रमmat_dir(स्थिर काष्ठा tb_property_dir *dir, u32 *block,
			       माप_प्रकार block_len);
काष्ठा tb_property_dir *tb_property_copy_dir(स्थिर काष्ठा tb_property_dir *dir);
काष्ठा tb_property_dir *tb_property_create_dir(स्थिर uuid_t *uuid);
व्योम tb_property_मुक्त_dir(काष्ठा tb_property_dir *dir);
पूर्णांक tb_property_add_immediate(काष्ठा tb_property_dir *parent, स्थिर अक्षर *key,
			      u32 value);
पूर्णांक tb_property_add_data(काष्ठा tb_property_dir *parent, स्थिर अक्षर *key,
			 स्थिर व्योम *buf, माप_प्रकार buflen);
पूर्णांक tb_property_add_text(काष्ठा tb_property_dir *parent, स्थिर अक्षर *key,
			 स्थिर अक्षर *text);
पूर्णांक tb_property_add_dir(काष्ठा tb_property_dir *parent, स्थिर अक्षर *key,
			काष्ठा tb_property_dir *dir);
व्योम tb_property_हटाओ(काष्ठा tb_property *tb_property);
काष्ठा tb_property *tb_property_find(काष्ठा tb_property_dir *dir,
			स्थिर अक्षर *key, क्रमागत tb_property_type type);
काष्ठा tb_property *tb_property_get_next(काष्ठा tb_property_dir *dir,
					 काष्ठा tb_property *prev);

#घोषणा tb_property_क्रम_each(dir, property)			\
	क्रम (property = tb_property_get_next(dir, शून्य);	\
	     property;						\
	     property = tb_property_get_next(dir, property))

पूर्णांक tb_रेजिस्टर_property_dir(स्थिर अक्षर *key, काष्ठा tb_property_dir *dir);
व्योम tb_unरेजिस्टर_property_dir(स्थिर अक्षर *key, काष्ठा tb_property_dir *dir);

/**
 * काष्ठा tb_xकरोमुख्य - Cross-करोमुख्य (XDoमुख्य) connection
 * @dev: XDoमुख्य device
 * @tb: Poपूर्णांकer to the करोमुख्य
 * @remote_uuid: UUID of the remote करोमुख्य (host)
 * @local_uuid: Cached local UUID
 * @route: Route string the other करोमुख्य can be reached
 * @venकरोr: Venकरोr ID of the remote करोमुख्य
 * @device: Device ID of the demote करोमुख्य
 * @local_max_hopid: Maximum input HopID of this host
 * @remote_max_hopid: Maximum input HopID of the remote host
 * @lock: Lock to serialize access to the following fields of this काष्ठाure
 * @venकरोr_name: Name of the venकरोr (or %शून्य अगर not known)
 * @device_name: Name of the device (or %शून्य अगर not known)
 * @link_speed: Speed of the link in Gb/s
 * @link_width: Width of the link (1 or 2)
 * @is_unplugged: The XDoमुख्य is unplugged
 * @needs_uuid: If the XDoमुख्य करोes not have @remote_uuid it will be
 *		queried first
 * @service_ids: Used to generate IDs क्रम the services
 * @in_hopids: Input HopIDs क्रम DMA tunneling
 * @out_hopids; Output HopIDs क्रम DMA tunneling
 * @local_property_block: Local block of properties
 * @local_property_block_gen: Generation of @local_property_block
 * @local_property_block_len: Length of the @local_property_block in dwords
 * @remote_properties: Properties exported by the remote करोमुख्य
 * @remote_property_block_gen: Generation of @remote_properties
 * @get_uuid_work: Work used to retrieve @remote_uuid
 * @uuid_retries: Number of बार left @remote_uuid is requested beक्रमe
 *		  giving up
 * @get_properties_work: Work used to get remote करोमुख्य properties
 * @properties_retries: Number of बार left to पढ़ो properties
 * @properties_changed_work: Work used to notअगरy the remote करोमुख्य that
 *			     our properties have changed
 * @properties_changed_retries: Number of बार left to send properties
 *				changed notअगरication
 * @link: Root चयन link the remote करोमुख्य is connected (ICM only)
 * @depth: Depth in the chain the remote करोमुख्य is connected (ICM only)
 *
 * This काष्ठाure represents connection across two करोमुख्यs (hosts).
 * Each XDoमुख्य contains zero or more services which are exposed as
 * &काष्ठा tb_service objects.
 *
 * Service drivers may access this काष्ठाure अगर they need to क्रमागतerate
 * non-standard properties but they need hold @lock when करोing so
 * because properties can be changed asynchronously in response to
 * changes in the remote करोमुख्य.
 */
काष्ठा tb_xकरोमुख्य अणु
	काष्ठा device dev;
	काष्ठा tb *tb;
	uuid_t *remote_uuid;
	स्थिर uuid_t *local_uuid;
	u64 route;
	u16 venकरोr;
	u16 device;
	अचिन्हित पूर्णांक local_max_hopid;
	अचिन्हित पूर्णांक remote_max_hopid;
	काष्ठा mutex lock;
	स्थिर अक्षर *venकरोr_name;
	स्थिर अक्षर *device_name;
	अचिन्हित पूर्णांक link_speed;
	अचिन्हित पूर्णांक link_width;
	bool is_unplugged;
	bool needs_uuid;
	काष्ठा ida service_ids;
	काष्ठा ida in_hopids;
	काष्ठा ida out_hopids;
	u32 *local_property_block;
	u32 local_property_block_gen;
	u32 local_property_block_len;
	काष्ठा tb_property_dir *remote_properties;
	u32 remote_property_block_gen;
	काष्ठा delayed_work get_uuid_work;
	पूर्णांक uuid_retries;
	काष्ठा delayed_work get_properties_work;
	पूर्णांक properties_retries;
	काष्ठा delayed_work properties_changed_work;
	पूर्णांक properties_changed_retries;
	u8 link;
	u8 depth;
पूर्ण;

पूर्णांक tb_xकरोमुख्य_lane_bonding_enable(काष्ठा tb_xकरोमुख्य *xd);
व्योम tb_xकरोमुख्य_lane_bonding_disable(काष्ठा tb_xकरोमुख्य *xd);
पूर्णांक tb_xकरोमुख्य_alloc_in_hopid(काष्ठा tb_xकरोमुख्य *xd, पूर्णांक hopid);
व्योम tb_xकरोमुख्य_release_in_hopid(काष्ठा tb_xकरोमुख्य *xd, पूर्णांक hopid);
पूर्णांक tb_xकरोमुख्य_alloc_out_hopid(काष्ठा tb_xकरोमुख्य *xd, पूर्णांक hopid);
व्योम tb_xकरोमुख्य_release_out_hopid(काष्ठा tb_xकरोमुख्य *xd, पूर्णांक hopid);
पूर्णांक tb_xकरोमुख्य_enable_paths(काष्ठा tb_xकरोमुख्य *xd, पूर्णांक transmit_path,
			    पूर्णांक transmit_ring, पूर्णांक receive_path,
			    पूर्णांक receive_ring);
पूर्णांक tb_xकरोमुख्य_disable_paths(काष्ठा tb_xकरोमुख्य *xd, पूर्णांक transmit_path,
			     पूर्णांक transmit_ring, पूर्णांक receive_path,
			     पूर्णांक receive_ring);

अटल अंतरभूत पूर्णांक tb_xकरोमुख्य_disable_all_paths(काष्ठा tb_xकरोमुख्य *xd)
अणु
	वापस tb_xकरोमुख्य_disable_paths(xd, -1, -1, -1, -1);
पूर्ण

काष्ठा tb_xकरोमुख्य *tb_xकरोमुख्य_find_by_uuid(काष्ठा tb *tb, स्थिर uuid_t *uuid);
काष्ठा tb_xकरोमुख्य *tb_xकरोमुख्य_find_by_route(काष्ठा tb *tb, u64 route);

अटल अंतरभूत काष्ठा tb_xकरोमुख्य *
tb_xकरोमुख्य_find_by_uuid_locked(काष्ठा tb *tb, स्थिर uuid_t *uuid)
अणु
	काष्ठा tb_xकरोमुख्य *xd;

	mutex_lock(&tb->lock);
	xd = tb_xकरोमुख्य_find_by_uuid(tb, uuid);
	mutex_unlock(&tb->lock);

	वापस xd;
पूर्ण

अटल अंतरभूत काष्ठा tb_xकरोमुख्य *
tb_xकरोमुख्य_find_by_route_locked(काष्ठा tb *tb, u64 route)
अणु
	काष्ठा tb_xकरोमुख्य *xd;

	mutex_lock(&tb->lock);
	xd = tb_xकरोमुख्य_find_by_route(tb, route);
	mutex_unlock(&tb->lock);

	वापस xd;
पूर्ण

अटल अंतरभूत काष्ठा tb_xकरोमुख्य *tb_xकरोमुख्य_get(काष्ठा tb_xकरोमुख्य *xd)
अणु
	अगर (xd)
		get_device(&xd->dev);
	वापस xd;
पूर्ण

अटल अंतरभूत व्योम tb_xकरोमुख्य_put(काष्ठा tb_xकरोमुख्य *xd)
अणु
	अगर (xd)
		put_device(&xd->dev);
पूर्ण

अटल अंतरभूत bool tb_is_xकरोमुख्य(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &tb_xकरोमुख्य_type;
पूर्ण

अटल अंतरभूत काष्ठा tb_xकरोमुख्य *tb_to_xकरोमुख्य(काष्ठा device *dev)
अणु
	अगर (tb_is_xकरोमुख्य(dev))
		वापस container_of(dev, काष्ठा tb_xकरोमुख्य, dev);
	वापस शून्य;
पूर्ण

पूर्णांक tb_xकरोमुख्य_response(काष्ठा tb_xकरोमुख्य *xd, स्थिर व्योम *response,
			माप_प्रकार size, क्रमागत tb_cfg_pkg_type type);
पूर्णांक tb_xकरोमुख्य_request(काष्ठा tb_xकरोमुख्य *xd, स्थिर व्योम *request,
		       माप_प्रकार request_size, क्रमागत tb_cfg_pkg_type request_type,
		       व्योम *response, माप_प्रकार response_size,
		       क्रमागत tb_cfg_pkg_type response_type,
		       अचिन्हित पूर्णांक समयout_msec);

/**
 * tb_protocol_handler - Protocol specअगरic handler
 * @uuid: XDoमुख्य messages with this UUID are dispatched to this handler
 * @callback: Callback called with the XDoमुख्य message. Returning %1
 *	      here tells the XDoमुख्य core that the message was handled
 *	      by this handler and should not be क्रमwared to other
 *	      handlers.
 * @data: Data passed with the callback
 * @list: Handlers are linked using this
 *
 * Thunderbolt services can hook पूर्णांकo incoming XDoमुख्य requests by
 * रेजिस्टरing protocol handler. Only limitation is that the XDoमुख्य
 * discovery protocol UUID cannot be रेजिस्टरed since it is handled by
 * the core XDoमुख्य code.
 *
 * The @callback must check that the message is really directed to the
 * service the driver implements.
 */
काष्ठा tb_protocol_handler अणु
	स्थिर uuid_t *uuid;
	पूर्णांक (*callback)(स्थिर व्योम *buf, माप_प्रकार size, व्योम *data);
	व्योम *data;
	काष्ठा list_head list;
पूर्ण;

पूर्णांक tb_रेजिस्टर_protocol_handler(काष्ठा tb_protocol_handler *handler);
व्योम tb_unरेजिस्टर_protocol_handler(काष्ठा tb_protocol_handler *handler);

/**
 * काष्ठा tb_service - Thunderbolt service
 * @dev: XDoमुख्य device
 * @id: ID of the service (shown in sysfs)
 * @key: Protocol key from the properties directory
 * @prtcid: Protocol ID from the properties directory
 * @prtcvers: Protocol version from the properties directory
 * @prtcrevs: Protocol software revision from the properties directory
 * @prtcstns: Protocol settings mask from the properties directory
 * @debugfs_dir: Poपूर्णांकer to the service debugfs directory. Always created
 *		 when debugfs is enabled. Can be used by service drivers to
 *		 add their own entries under the service.
 *
 * Each करोमुख्य exposes set of services it supports as collection of
 * properties. For each service there will be one corresponding
 * &काष्ठा tb_service. Service drivers are bound to these.
 */
काष्ठा tb_service अणु
	काष्ठा device dev;
	पूर्णांक id;
	स्थिर अक्षर *key;
	u32 prtcid;
	u32 prtcvers;
	u32 prtcrevs;
	u32 prtcstns;
	काष्ठा dentry *debugfs_dir;
पूर्ण;

अटल अंतरभूत काष्ठा tb_service *tb_service_get(काष्ठा tb_service *svc)
अणु
	अगर (svc)
		get_device(&svc->dev);
	वापस svc;
पूर्ण

अटल अंतरभूत व्योम tb_service_put(काष्ठा tb_service *svc)
अणु
	अगर (svc)
		put_device(&svc->dev);
पूर्ण

अटल अंतरभूत bool tb_is_service(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &tb_service_type;
पूर्ण

अटल अंतरभूत काष्ठा tb_service *tb_to_service(काष्ठा device *dev)
अणु
	अगर (tb_is_service(dev))
		वापस container_of(dev, काष्ठा tb_service, dev);
	वापस शून्य;
पूर्ण

/**
 * tb_service_driver - Thunderbolt service driver
 * @driver: Driver काष्ठाure
 * @probe: Called when the driver is probed
 * @हटाओ: Called when the driver is हटाओd (optional)
 * @shutकरोwn: Called at shutकरोwn समय to stop the service (optional)
 * @id_table: Table of service identअगरiers the driver supports
 */
काष्ठा tb_service_driver अणु
	काष्ठा device_driver driver;
	पूर्णांक (*probe)(काष्ठा tb_service *svc, स्थिर काष्ठा tb_service_id *id);
	व्योम (*हटाओ)(काष्ठा tb_service *svc);
	व्योम (*shutकरोwn)(काष्ठा tb_service *svc);
	स्थिर काष्ठा tb_service_id *id_table;
पूर्ण;

#घोषणा TB_SERVICE(key, id)				\
	.match_flags = TBSVC_MATCH_PROTOCOL_KEY |	\
		       TBSVC_MATCH_PROTOCOL_ID,		\
	.protocol_key = (key),				\
	.protocol_id = (id)

पूर्णांक tb_रेजिस्टर_service_driver(काष्ठा tb_service_driver *drv);
व्योम tb_unरेजिस्टर_service_driver(काष्ठा tb_service_driver *drv);

अटल अंतरभूत व्योम *tb_service_get_drvdata(स्थिर काष्ठा tb_service *svc)
अणु
	वापस dev_get_drvdata(&svc->dev);
पूर्ण

अटल अंतरभूत व्योम tb_service_set_drvdata(काष्ठा tb_service *svc, व्योम *data)
अणु
	dev_set_drvdata(&svc->dev, data);
पूर्ण

अटल अंतरभूत काष्ठा tb_xकरोमुख्य *tb_service_parent(काष्ठा tb_service *svc)
अणु
	वापस tb_to_xकरोमुख्य(svc->dev.parent);
पूर्ण

/**
 * काष्ठा tb_nhi - thunderbolt native host पूर्णांकerface
 * @lock: Must be held during ring creation/deकाष्ठाion. Is acquired by
 *	  पूर्णांकerrupt_work when dispatching पूर्णांकerrupts to inभागidual rings.
 * @pdev: Poपूर्णांकer to the PCI device
 * @ops: NHI specअगरic optional ops
 * @iobase: MMIO space of the NHI
 * @tx_rings: All Tx rings available on this host controller
 * @rx_rings: All Rx rings available on this host controller
 * @msix_ida: Used to allocate MSI-X vectors क्रम rings
 * @going_away: The host controller device is about to disappear so when
 *		this flag is set, aव्योम touching the hardware anymore.
 * @पूर्णांकerrupt_work: Work scheduled to handle ring पूर्णांकerrupt when no
 *		    MSI-X is used.
 * @hop_count: Number of rings (end poपूर्णांक hops) supported by NHI.
 */
काष्ठा tb_nhi अणु
	spinlock_t lock;
	काष्ठा pci_dev *pdev;
	स्थिर काष्ठा tb_nhi_ops *ops;
	व्योम __iomem *iobase;
	काष्ठा tb_ring **tx_rings;
	काष्ठा tb_ring **rx_rings;
	काष्ठा ida msix_ida;
	bool going_away;
	काष्ठा work_काष्ठा पूर्णांकerrupt_work;
	u32 hop_count;
पूर्ण;

/**
 * काष्ठा tb_ring - thunderbolt TX or RX ring associated with a NHI
 * @lock: Lock serializing actions to this ring. Must be acquired after
 *	  nhi->lock.
 * @nhi: Poपूर्णांकer to the native host controller पूर्णांकerface
 * @size: Size of the ring
 * @hop: Hop (DMA channel) associated with this ring
 * @head: Head of the ring (ग_लिखो next descriptor here)
 * @tail: Tail of the ring (complete next descriptor here)
 * @descriptors: Allocated descriptors क्रम this ring
 * @queue: Queue holding frames to be transferred over this ring
 * @in_flight: Queue holding frames that are currently in flight
 * @work: Interrupt work काष्ठाure
 * @is_tx: Is the ring Tx or Rx
 * @running: Is the ring running
 * @irq: MSI-X irq number अगर the ring uses MSI-X. %0 otherwise.
 * @vector: MSI-X vector number the ring uses (only set अगर @irq is > 0)
 * @flags: Ring specअगरic flags
 * @e2e_tx_hop: Transmit HopID when E2E is enabled. Only applicable to
 *		RX ring. For TX ring this should be set to %0.
 * @sof_mask: Bit mask used to detect start of frame PDF
 * @eof_mask: Bit mask used to detect end of frame PDF
 * @start_poll: Called when ring पूर्णांकerrupt is triggered to start
 *		polling. Passing %शून्य keeps the ring in पूर्णांकerrupt mode.
 * @poll_data: Data passed to @start_poll
 */
काष्ठा tb_ring अणु
	spinlock_t lock;
	काष्ठा tb_nhi *nhi;
	पूर्णांक size;
	पूर्णांक hop;
	पूर्णांक head;
	पूर्णांक tail;
	काष्ठा ring_desc *descriptors;
	dma_addr_t descriptors_dma;
	काष्ठा list_head queue;
	काष्ठा list_head in_flight;
	काष्ठा work_काष्ठा work;
	bool is_tx:1;
	bool running:1;
	पूर्णांक irq;
	u8 vector;
	अचिन्हित पूर्णांक flags;
	पूर्णांक e2e_tx_hop;
	u16 sof_mask;
	u16 eof_mask;
	व्योम (*start_poll)(व्योम *data);
	व्योम *poll_data;
पूर्ण;

/* Leave ring पूर्णांकerrupt enabled on suspend */
#घोषणा RING_FLAG_NO_SUSPEND	BIT(0)
/* Configure the ring to be in frame mode */
#घोषणा RING_FLAG_FRAME		BIT(1)
/* Enable end-to-end flow control */
#घोषणा RING_FLAG_E2E		BIT(2)

काष्ठा ring_frame;
प्रकार व्योम (*ring_cb)(काष्ठा tb_ring *, काष्ठा ring_frame *, bool canceled);

/**
 * क्रमागत ring_desc_flags - Flags क्रम DMA ring descriptor
 * %RING_DESC_ISOCH: Enable isonchronous DMA (Tx only)
 * %RING_DESC_CRC_ERROR: In frame mode CRC check failed क्रम the frame (Rx only)
 * %RING_DESC_COMPLETED: Descriptor completed (set by NHI)
 * %RING_DESC_POSTED: Always set this
 * %RING_DESC_BUFFER_OVERRUN: RX buffer overrun
 * %RING_DESC_INTERRUPT: Request an पूर्णांकerrupt on completion
 */
क्रमागत ring_desc_flags अणु
	RING_DESC_ISOCH = 0x1,
	RING_DESC_CRC_ERROR = 0x1,
	RING_DESC_COMPLETED = 0x2,
	RING_DESC_POSTED = 0x4,
	RING_DESC_BUFFER_OVERRUN = 0x04,
	RING_DESC_INTERRUPT = 0x8,
पूर्ण;

/**
 * काष्ठा ring_frame - For use with ring_rx/ring_tx
 * @buffer_phy: DMA mapped address of the frame
 * @callback: Callback called when the frame is finished (optional)
 * @list: Frame is linked to a queue using this
 * @size: Size of the frame in bytes (%0 means %4096)
 * @flags: Flags क्रम the frame (see &क्रमागत ring_desc_flags)
 * @eof: End of frame protocol defined field
 * @sof: Start of frame protocol defined field
 */
काष्ठा ring_frame अणु
	dma_addr_t buffer_phy;
	ring_cb callback;
	काष्ठा list_head list;
	u32 size:12;
	u32 flags:12;
	u32 eof:4;
	u32 sof:4;
पूर्ण;

/* Minimum size क्रम ring_rx */
#घोषणा TB_FRAME_SIZE		0x100

काष्ठा tb_ring *tb_ring_alloc_tx(काष्ठा tb_nhi *nhi, पूर्णांक hop, पूर्णांक size,
				 अचिन्हित पूर्णांक flags);
काष्ठा tb_ring *tb_ring_alloc_rx(काष्ठा tb_nhi *nhi, पूर्णांक hop, पूर्णांक size,
				 अचिन्हित पूर्णांक flags, पूर्णांक e2e_tx_hop,
				 u16 sof_mask, u16 eof_mask,
				 व्योम (*start_poll)(व्योम *), व्योम *poll_data);
व्योम tb_ring_start(काष्ठा tb_ring *ring);
व्योम tb_ring_stop(काष्ठा tb_ring *ring);
व्योम tb_ring_मुक्त(काष्ठा tb_ring *ring);

पूर्णांक __tb_ring_enqueue(काष्ठा tb_ring *ring, काष्ठा ring_frame *frame);

/**
 * tb_ring_rx() - enqueue a frame on an RX ring
 * @ring: Ring to enqueue the frame
 * @frame: Frame to enqueue
 *
 * @frame->buffer, @frame->buffer_phy have to be set. The buffer must
 * contain at least %TB_FRAME_SIZE bytes.
 *
 * @frame->callback will be invoked with @frame->size, @frame->flags,
 * @frame->eof, @frame->sof set once the frame has been received.
 *
 * If ring_stop() is called after the packet has been enqueued
 * @frame->callback will be called with canceled set to true.
 *
 * Return: Returns %-ESHUTDOWN अगर ring_stop has been called. Zero otherwise.
 */
अटल अंतरभूत पूर्णांक tb_ring_rx(काष्ठा tb_ring *ring, काष्ठा ring_frame *frame)
अणु
	WARN_ON(ring->is_tx);
	वापस __tb_ring_enqueue(ring, frame);
पूर्ण

/**
 * tb_ring_tx() - enqueue a frame on an TX ring
 * @ring: Ring the enqueue the frame
 * @frame: Frame to enqueue
 *
 * @frame->buffer, @frame->buffer_phy, @frame->size, @frame->eof and
 * @frame->sof have to be set.
 *
 * @frame->callback will be invoked with once the frame has been transmitted.
 *
 * If ring_stop() is called after the packet has been enqueued @frame->callback
 * will be called with canceled set to true.
 *
 * Return: Returns %-ESHUTDOWN अगर ring_stop has been called. Zero otherwise.
 */
अटल अंतरभूत पूर्णांक tb_ring_tx(काष्ठा tb_ring *ring, काष्ठा ring_frame *frame)
अणु
	WARN_ON(!ring->is_tx);
	वापस __tb_ring_enqueue(ring, frame);
पूर्ण

/* Used only when the ring is in polling mode */
काष्ठा ring_frame *tb_ring_poll(काष्ठा tb_ring *ring);
व्योम tb_ring_poll_complete(काष्ठा tb_ring *ring);

/**
 * tb_ring_dma_device() - Return device used क्रम DMA mapping
 * @ring: Ring whose DMA device is retrieved
 *
 * Use this function when you are mapping DMA क्रम buffers that are
 * passed to the ring क्रम sending/receiving.
 */
अटल अंतरभूत काष्ठा device *tb_ring_dma_device(काष्ठा tb_ring *ring)
अणु
	वापस &ring->nhi->pdev->dev;
पूर्ण

#पूर्ण_अगर /* THUNDERBOLT_H_ */
