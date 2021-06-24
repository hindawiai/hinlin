<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RapidIO पूर्णांकerconnect services
 * (RapidIO Interconnect Specअगरication, http://www.rapidio.org)
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#अगर_अघोषित LINUX_RIO_H
#घोषणा LINUX_RIO_H

#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/rio_regs.h>
#समावेश <linux/mod_devicetable.h>
#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
#समावेश <linux/dmaengine.h>
#पूर्ण_अगर

#घोषणा RIO_NO_HOPCOUNT		-1
#घोषणा RIO_INVALID_DESTID	0xffff

#घोषणा RIO_MAX_MPORTS		8
#घोषणा RIO_MAX_MPORT_RESOURCES	16
#घोषणा RIO_MAX_DEV_RESOURCES	16
#घोषणा RIO_MAX_MPORT_NAME	40

#घोषणा RIO_GLOBAL_TABLE	0xff	/* Indicates access of a चयन's
					   global routing table अगर it
					   has multiple (or per port)
					   tables */

#घोषणा RIO_INVALID_ROUTE	0xff	/* Indicates that a route table
					   entry is invalid (no route
					   exists क्रम the device ID) */

#घोषणा RIO_MAX_ROUTE_ENTRIES(size)	(size ? (1 << 16) : (1 << 8))
#घोषणा RIO_ANY_DESTID(size)		(size ? 0xffff : 0xff)

#घोषणा RIO_MAX_MBOX		4
#घोषणा RIO_MAX_MSG_SIZE	0x1000

/*
 * Error values that may be वापसed by RIO functions.
 */
#घोषणा RIO_SUCCESSFUL			0x00
#घोषणा RIO_BAD_SIZE			0x81

/*
 * For RIO devices, the region numbers are asचिन्हित this way:
 *
 *	0	RapidIO outbound करोorbells
 *      1-15	RapidIO memory regions
 *
 * For RIO master ports, the region number are asचिन्हित this way:
 *
 *	0	RapidIO inbound करोorbells
 *	1	RapidIO inbound mailboxes
 *	2	RapidIO outbound mailboxes
 */
#घोषणा RIO_DOORBELL_RESOURCE	0
#घोषणा RIO_INB_MBOX_RESOURCE	1
#घोषणा RIO_OUTB_MBOX_RESOURCE	2

#घोषणा RIO_PW_MSG_SIZE		64

/*
 * A component tag value (stored in the component tag CSR) is used as device's
 * unique identअगरier asचिन्हित during क्रमागतeration. Besides being used क्रम
 * identअगरying चयनes (which करो not have device ID रेजिस्टर), it also is used
 * by error management notअगरication and thereक्रमe has to be asचिन्हित
 * to endpoपूर्णांकs as well.
 */
#घोषणा RIO_CTAG_RESRVD	0xfffe0000 /* Reserved */
#घोषणा RIO_CTAG_UDEVID	0x0001ffff /* Unique device identअगरier */

बाह्य काष्ठा bus_type rio_bus_type;
बाह्य काष्ठा class rio_mport_class;

काष्ठा rio_mport;
काष्ठा rio_dev;
जोड़ rio_pw_msg;

/**
 * काष्ठा rio_चयन - RIO चयन info
 * @node: Node in global list of चयनes
 * @route_table: Copy of चयन routing table
 * @port_ok: Status of each port (one bit per port) - OK=1 or UNINIT=0
 * @ops: poपूर्णांकer to चयन-specअगरic operations
 * @lock: lock to serialize operations updates
 * @nextdev: Array of per-port poपूर्णांकers to the next attached device
 */
काष्ठा rio_चयन अणु
	काष्ठा list_head node;
	u8 *route_table;
	u32 port_ok;
	काष्ठा rio_चयन_ops *ops;
	spinlock_t lock;
	काष्ठा rio_dev *nextdev[];
पूर्ण;

/**
 * काष्ठा rio_चयन_ops - Per-चयन operations
 * @owner: The module owner of this काष्ठाure
 * @add_entry: Callback क्रम चयन-specअगरic route add function
 * @get_entry: Callback क्रम चयन-specअगरic route get function
 * @clr_table: Callback क्रम चयन-specअगरic clear route table function
 * @set_करोमुख्य: Callback क्रम चयन-specअगरic करोमुख्य setting function
 * @get_करोमुख्य: Callback क्रम चयन-specअगरic करोमुख्य get function
 * @em_init: Callback क्रम चयन-specअगरic error management init function
 * @em_handle: Callback क्रम चयन-specअगरic error management handler function
 *
 * Defines the operations that are necessary to initialize/control
 * a particular RIO चयन device.
 */
काष्ठा rio_चयन_ops अणु
	काष्ठा module *owner;
	पूर्णांक (*add_entry) (काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
			  u16 table, u16 route_destid, u8 route_port);
	पूर्णांक (*get_entry) (काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
			  u16 table, u16 route_destid, u8 *route_port);
	पूर्णांक (*clr_table) (काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
			  u16 table);
	पूर्णांक (*set_करोमुख्य) (काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
			   u8 sw_करोमुख्य);
	पूर्णांक (*get_करोमुख्य) (काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
			   u8 *sw_करोमुख्य);
	पूर्णांक (*em_init) (काष्ठा rio_dev *dev);
	पूर्णांक (*em_handle) (काष्ठा rio_dev *dev, u8 swport);
पूर्ण;

क्रमागत rio_device_state अणु
	RIO_DEVICE_INITIALIZING,
	RIO_DEVICE_RUNNING,
	RIO_DEVICE_GONE,
	RIO_DEVICE_SHUTDOWN,
पूर्ण;

/**
 * काष्ठा rio_dev - RIO device info
 * @global_list: Node in list of all RIO devices
 * @net_list: Node in list of RIO devices in a network
 * @net: Network this device is a part of
 * @करो_क्रमागत: Enumeration flag
 * @did: Device ID
 * @vid: Venकरोr ID
 * @device_rev: Device revision
 * @यंत्र_did: Assembly device ID
 * @यंत्र_vid: Assembly venकरोr ID
 * @यंत्र_rev: Assembly revision
 * @efptr: Extended feature poपूर्णांकer
 * @pef: Processing element features
 * @swpinfo: Switch port info
 * @src_ops: Source operation capabilities
 * @dst_ops: Destination operation capabilities
 * @comp_tag: RIO component tag
 * @phys_efptr: RIO device extended features poपूर्णांकer
 * @phys_rmap: LP-Serial Register Map Type (1 or 2)
 * @em_efptr: RIO Error Management features poपूर्णांकer
 * @dma_mask: Mask of bits of RIO address this device implements
 * @driver: Driver claiming this device
 * @dev: Device model device
 * @riores: RIO resources this device owns
 * @pwcback: port-ग_लिखो callback function क्रम this device
 * @destid: Network destination ID (or associated destid क्रम चयन)
 * @hopcount: Hopcount to this device
 * @prev: Previous RIO device connected to the current one
 * @state: device state
 * @rचयन: काष्ठा rio_चयन (अगर valid क्रम this device)
 */
काष्ठा rio_dev अणु
	काष्ठा list_head global_list;	/* node in list of all RIO devices */
	काष्ठा list_head net_list;	/* node in per net list */
	काष्ठा rio_net *net;	/* RIO net this device resides in */
	bool करो_क्रमागत;
	u16 did;
	u16 vid;
	u32 device_rev;
	u16 यंत्र_did;
	u16 यंत्र_vid;
	u16 यंत्र_rev;
	u16 efptr;
	u32 pef;
	u32 swpinfo;
	u32 src_ops;
	u32 dst_ops;
	u32 comp_tag;
	u32 phys_efptr;
	u32 phys_rmap;
	u32 em_efptr;
	u64 dma_mask;
	काष्ठा rio_driver *driver;	/* RIO driver claiming this device */
	काष्ठा device dev;	/* LDM device काष्ठाure */
	काष्ठा resource riores[RIO_MAX_DEV_RESOURCES];
	पूर्णांक (*pwcback) (काष्ठा rio_dev *rdev, जोड़ rio_pw_msg *msg, पूर्णांक step);
	u16 destid;
	u8 hopcount;
	काष्ठा rio_dev *prev;
	atomic_t state;
	काष्ठा rio_चयन rचयन[];	/* RIO चयन info */
पूर्ण;

#घोषणा rio_dev_g(n) list_entry(n, काष्ठा rio_dev, global_list)
#घोषणा rio_dev_f(n) list_entry(n, काष्ठा rio_dev, net_list)
#घोषणा	to_rio_dev(n) container_of(n, काष्ठा rio_dev, dev)
#घोषणा sw_to_rio_dev(n) container_of(n, काष्ठा rio_dev, rचयन[0])
#घोषणा	to_rio_mport(n) container_of(n, काष्ठा rio_mport, dev)
#घोषणा	to_rio_net(n) container_of(n, काष्ठा rio_net, dev)

/**
 * काष्ठा rio_msg - RIO message event
 * @res: Mailbox resource
 * @mcback: Message event callback
 */
काष्ठा rio_msg अणु
	काष्ठा resource *res;
	व्योम (*mcback) (काष्ठा rio_mport * mport, व्योम *dev_id, पूर्णांक mbox, पूर्णांक slot);
पूर्ण;

/**
 * काष्ठा rio_dbell - RIO करोorbell event
 * @node: Node in list of करोorbell events
 * @res: Doorbell resource
 * @dinb: Doorbell event callback
 * @dev_id: Device specअगरic poपूर्णांकer to pass on event
 */
काष्ठा rio_dbell अणु
	काष्ठा list_head node;
	काष्ठा resource *res;
	व्योम (*dinb) (काष्ठा rio_mport *mport, व्योम *dev_id, u16 src, u16 dst, u16 info);
	व्योम *dev_id;
पूर्ण;

/**
 * काष्ठा rio_mport - RIO master port info
 * @dbells: List of करोorbell events
 * @pग_लिखोs: List of portग_लिखो events
 * @node: Node in global list of master ports
 * @nnode: Node in network list of master ports
 * @net: RIO net this mport is attached to
 * @lock: lock to synchronize lists manipulations
 * @iores: I/O mem resource that this master port पूर्णांकerface owns
 * @riores: RIO resources that this master port पूर्णांकerfaces owns
 * @inb_msg: RIO inbound message event descriptors
 * @outb_msg: RIO outbound message event descriptors
 * @host_deviceid: Host device ID associated with this master port
 * @ops: configuration space functions
 * @id: Port ID, unique among all ports
 * @index: Port index, unique among all port पूर्णांकerfaces of the same type
 * @sys_size: RapidIO common transport प्रणाली size
 * @phys_efptr: RIO port extended features poपूर्णांकer
 * @phys_rmap: LP-Serial EFB Register Mapping type (1 or 2).
 * @name: Port name string
 * @dev: device काष्ठाure associated with an mport
 * @priv: Master port निजी data
 * @dma: DMA device associated with mport
 * @nscan: RapidIO network क्रमागतeration/discovery operations
 * @state: mport device state
 * @pwe_refcnt: port-ग_लिखो enable ref counter to track enable/disable requests
 */
काष्ठा rio_mport अणु
	काष्ठा list_head dbells;	/* list of करोorbell events */
	काष्ठा list_head pग_लिखोs;	/* list of portग_लिखो events */
	काष्ठा list_head node;	/* node in global list of ports */
	काष्ठा list_head nnode;	/* node in net list of ports */
	काष्ठा rio_net *net;	/* RIO net this mport is attached to */
	काष्ठा mutex lock;
	काष्ठा resource iores;
	काष्ठा resource riores[RIO_MAX_MPORT_RESOURCES];
	काष्ठा rio_msg inb_msg[RIO_MAX_MBOX];
	काष्ठा rio_msg outb_msg[RIO_MAX_MBOX];
	पूर्णांक host_deviceid;	/* Host device ID */
	काष्ठा rio_ops *ops;	/* low-level architecture-dependent routines */
	अचिन्हित अक्षर id;	/* port ID, unique among all ports */
	अचिन्हित अक्षर index;	/* port index, unique among all port
				   पूर्णांकerfaces of the same type */
	अचिन्हित पूर्णांक sys_size;	/* RapidIO common transport प्रणाली size.
				 * 0 - Small size. 256 devices.
				 * 1 - Large size, 65536 devices.
				 */
	u32 phys_efptr;
	u32 phys_rmap;
	अचिन्हित अक्षर name[RIO_MAX_MPORT_NAME];
	काष्ठा device dev;
	व्योम *priv;		/* Master port निजी data */
#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
	काष्ठा dma_device	dma;
#पूर्ण_अगर
	काष्ठा rio_scan *nscan;
	atomic_t state;
	अचिन्हित पूर्णांक pwe_refcnt;
पूर्ण;

अटल अंतरभूत पूर्णांक rio_mport_is_running(काष्ठा rio_mport *mport)
अणु
	वापस atomic_पढ़ो(&mport->state) == RIO_DEVICE_RUNNING;
पूर्ण

/*
 * Enumeration/discovery control flags
 */
#घोषणा RIO_SCAN_ENUM_NO_WAIT	0x00000001 /* Do not रुको क्रम क्रमागत completed */

/**
 * काष्ठा rio_net - RIO network info
 * @node: Node in global list of RIO networks
 * @devices: List of devices in this network
 * @चयनes: List of चयनes in this network
 * @mports: List of master ports accessing this network
 * @hport: Default port क्रम accessing this network
 * @id: RIO network ID
 * @dev: Device object
 * @क्रमागत_data: निजी data specअगरic to a network क्रमागतerator
 * @release: क्रमागतerator-specअगरic release callback
 */
काष्ठा rio_net अणु
	काष्ठा list_head node;	/* node in list of networks */
	काष्ठा list_head devices;	/* list of devices in this net */
	काष्ठा list_head चयनes;	/* list of चयनes in this net */
	काष्ठा list_head mports;	/* list of ports accessing net */
	काष्ठा rio_mport *hport;	/* primary port क्रम accessing net */
	अचिन्हित अक्षर id;	/* RIO network ID */
	काष्ठा device dev;
	व्योम *क्रमागत_data;	/* निजी data क्रम क्रमागतerator of the network */
	व्योम (*release)(काष्ठा rio_net *net);
पूर्ण;

क्रमागत rio_link_speed अणु
	RIO_LINK_DOWN = 0, /* SRIO Link not initialized */
	RIO_LINK_125 = 1, /* 1.25 GBaud  */
	RIO_LINK_250 = 2, /* 2.5 GBaud   */
	RIO_LINK_312 = 3, /* 3.125 GBaud */
	RIO_LINK_500 = 4, /* 5.0 GBaud   */
	RIO_LINK_625 = 5  /* 6.25 GBaud  */
पूर्ण;

क्रमागत rio_link_width अणु
	RIO_LINK_1X  = 0,
	RIO_LINK_1XR = 1,
	RIO_LINK_2X  = 3,
	RIO_LINK_4X  = 2,
	RIO_LINK_8X  = 4,
	RIO_LINK_16X = 5
पूर्ण;

क्रमागत rio_mport_flags अणु
	RIO_MPORT_DMA	 = (1 << 0), /* supports DMA data transfers */
	RIO_MPORT_DMA_SG = (1 << 1), /* DMA supports HW SG mode */
	RIO_MPORT_IBSG	 = (1 << 2), /* inbound mapping supports SG */
पूर्ण;

/**
 * काष्ठा rio_mport_attr - RIO mport device attributes
 * @flags: mport device capability flags
 * @link_speed: SRIO link speed value (as defined by RapidIO specअगरication)
 * @link_width:	SRIO link width value (as defined by RapidIO specअगरication)
 * @dma_max_sge: number of SG list entries that can be handled by DMA channel(s)
 * @dma_max_size: max number of bytes in single DMA transfer (SG entry)
 * @dma_align: alignment shअगरt क्रम DMA operations (as क्रम other DMA operations)
 */
काष्ठा rio_mport_attr अणु
	पूर्णांक flags;
	पूर्णांक link_speed;
	पूर्णांक link_width;

	/* DMA capability info: valid only अगर RIO_MPORT_DMA flag is set */
	पूर्णांक dma_max_sge;
	पूर्णांक dma_max_size;
	पूर्णांक dma_align;
पूर्ण;

/* Low-level architecture-dependent routines */

/**
 * काष्ठा rio_ops - Low-level RIO configuration space operations
 * @lcपढ़ो: Callback to perक्रमm local (master port) पढ़ो of config space.
 * @lcग_लिखो: Callback to perक्रमm local (master port) ग_लिखो of config space.
 * @cपढ़ो: Callback to perक्रमm network पढ़ो of config space.
 * @cग_लिखो: Callback to perक्रमm network ग_लिखो of config space.
 * @dsend: Callback to send a करोorbell message.
 * @pwenable: Callback to enable/disable port-ग_लिखो message handling.
 * @खोलो_outb_mbox: Callback to initialize outbound mailbox.
 * @बंद_outb_mbox: Callback to shut करोwn outbound mailbox.
 * @खोलो_inb_mbox: Callback to initialize inbound mailbox.
 * @बंद_inb_mbox: Callback to	shut करोwn inbound mailbox.
 * @add_outb_message: Callback to add a message to an outbound mailbox queue.
 * @add_inb_buffer: Callback to	add a buffer to an inbound mailbox queue.
 * @get_inb_message: Callback to get a message from an inbound mailbox queue.
 * @map_inb: Callback to map RapidIO address region पूर्णांकo local memory space.
 * @unmap_inb: Callback to unmap RapidIO address region mapped with map_inb().
 * @query_mport: Callback to query mport device attributes.
 * @map_outb: Callback to map outbound address region पूर्णांकo local memory space.
 * @unmap_outb: Callback to unmap outbound RapidIO address region.
 */
काष्ठा rio_ops अणु
	पूर्णांक (*lcपढ़ो) (काष्ठा rio_mport *mport, पूर्णांक index, u32 offset, पूर्णांक len,
			u32 *data);
	पूर्णांक (*lcग_लिखो) (काष्ठा rio_mport *mport, पूर्णांक index, u32 offset, पूर्णांक len,
			u32 data);
	पूर्णांक (*cपढ़ो) (काष्ठा rio_mport *mport, पूर्णांक index, u16 destid,
			u8 hopcount, u32 offset, पूर्णांक len, u32 *data);
	पूर्णांक (*cग_लिखो) (काष्ठा rio_mport *mport, पूर्णांक index, u16 destid,
			u8 hopcount, u32 offset, पूर्णांक len, u32 data);
	पूर्णांक (*dsend) (काष्ठा rio_mport *mport, पूर्णांक index, u16 destid, u16 data);
	पूर्णांक (*pwenable) (काष्ठा rio_mport *mport, पूर्णांक enable);
	पूर्णांक (*खोलो_outb_mbox)(काष्ठा rio_mport *mport, व्योम *dev_id,
			      पूर्णांक mbox, पूर्णांक entries);
	व्योम (*बंद_outb_mbox)(काष्ठा rio_mport *mport, पूर्णांक mbox);
	पूर्णांक  (*खोलो_inb_mbox)(काष्ठा rio_mport *mport, व्योम *dev_id,
			     पूर्णांक mbox, पूर्णांक entries);
	व्योम (*बंद_inb_mbox)(काष्ठा rio_mport *mport, पूर्णांक mbox);
	पूर्णांक  (*add_outb_message)(काष्ठा rio_mport *mport, काष्ठा rio_dev *rdev,
				 पूर्णांक mbox, व्योम *buffer, माप_प्रकार len);
	पूर्णांक (*add_inb_buffer)(काष्ठा rio_mport *mport, पूर्णांक mbox, व्योम *buf);
	व्योम *(*get_inb_message)(काष्ठा rio_mport *mport, पूर्णांक mbox);
	पूर्णांक (*map_inb)(काष्ठा rio_mport *mport, dma_addr_t lstart,
			u64 rstart, u64 size, u32 flags);
	व्योम (*unmap_inb)(काष्ठा rio_mport *mport, dma_addr_t lstart);
	पूर्णांक (*query_mport)(काष्ठा rio_mport *mport,
			   काष्ठा rio_mport_attr *attr);
	पूर्णांक (*map_outb)(काष्ठा rio_mport *mport, u16 destid, u64 rstart,
			u32 size, u32 flags, dma_addr_t *laddr);
	व्योम (*unmap_outb)(काष्ठा rio_mport *mport, u16 destid, u64 rstart);
पूर्ण;

#घोषणा RIO_RESOURCE_MEM	0x00000100
#घोषणा RIO_RESOURCE_DOORBELL	0x00000200
#घोषणा RIO_RESOURCE_MAILBOX	0x00000400

#घोषणा RIO_RESOURCE_CACHEABLE	0x00010000
#घोषणा RIO_RESOURCE_PCI	0x00020000

#घोषणा RIO_RESOURCE_BUSY	0x80000000

/**
 * काष्ठा rio_driver - RIO driver info
 * @node: Node in list of drivers
 * @name: RIO driver name
 * @id_table: RIO device ids to be associated with this driver
 * @probe: RIO device inserted
 * @हटाओ: RIO device हटाओd
 * @shutकरोwn: shutकरोwn notअगरication callback
 * @suspend: RIO device suspended
 * @resume: RIO device awakened
 * @enable_wake: RIO device enable wake event
 * @driver: LDM driver काष्ठा
 *
 * Provides info on a RIO device driver क्रम insertion/removal and
 * घातer management purposes.
 */
काष्ठा rio_driver अणु
	काष्ठा list_head node;
	अक्षर *name;
	स्थिर काष्ठा rio_device_id *id_table;
	पूर्णांक (*probe) (काष्ठा rio_dev * dev, स्थिर काष्ठा rio_device_id * id);
	व्योम (*हटाओ) (काष्ठा rio_dev * dev);
	व्योम (*shutकरोwn)(काष्ठा rio_dev *dev);
	पूर्णांक (*suspend) (काष्ठा rio_dev * dev, u32 state);
	पूर्णांक (*resume) (काष्ठा rio_dev * dev);
	पूर्णांक (*enable_wake) (काष्ठा rio_dev * dev, u32 state, पूर्णांक enable);
	काष्ठा device_driver driver;
पूर्ण;

#घोषणा	to_rio_driver(drv) container_of(drv,काष्ठा rio_driver, driver)

जोड़ rio_pw_msg अणु
	काष्ठा अणु
		u32 comptag;	/* Component Tag CSR */
		u32 errdetect;	/* Port N Error Detect CSR */
		u32 is_port;	/* Implementation specअगरic + PortID */
		u32 ltlerrdet;	/* LTL Error Detect CSR */
		u32 padding[12];
	पूर्ण em;
	u32 raw[RIO_PW_MSG_SIZE/माप(u32)];
पूर्ण;

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE

/*
 * क्रमागत rio_ग_लिखो_type - RIO ग_लिखो transaction types used in DMA transfers
 *
 * Note: RapidIO specअगरication defines ग_लिखो (NWRITE) and
 * ग_लिखो-with-response (NWRITE_R) data transfer operations.
 * Existing DMA controllers that service RapidIO may use one of these operations
 * क्रम entire data transfer or their combination with only the last data packet
 * requires response.
 */
क्रमागत rio_ग_लिखो_type अणु
	RDW_DEFAULT,		/* शेष method used by DMA driver */
	RDW_ALL_NWRITE,		/* all packets use NWRITE */
	RDW_ALL_NWRITE_R,	/* all packets use NWRITE_R */
	RDW_LAST_NWRITE_R,	/* last packet uses NWRITE_R, others - NWRITE */
पूर्ण;

काष्ठा rio_dma_ext अणु
	u16 destid;
	u64 rio_addr;	/* low 64-bits of 66-bit RapidIO address */
	u8  rio_addr_u;  /* upper 2-bits of 66-bit RapidIO address */
	क्रमागत rio_ग_लिखो_type wr_type; /* preferred RIO ग_लिखो operation type */
पूर्ण;

काष्ठा rio_dma_data अणु
	/* Local data (as scatterlist) */
	काष्ठा scatterlist	*sg;	/* I/O scatter list */
	अचिन्हित पूर्णांक		sg_len;	/* size of scatter list */
	/* Remote device address (flat buffer) */
	u64 rio_addr;	/* low 64-bits of 66-bit RapidIO address */
	u8  rio_addr_u;  /* upper 2-bits of 66-bit RapidIO address */
	क्रमागत rio_ग_लिखो_type wr_type; /* preferred RIO ग_लिखो operation type */
पूर्ण;

अटल अंतरभूत काष्ठा rio_mport *dma_to_mport(काष्ठा dma_device *ddev)
अणु
	वापस container_of(ddev, काष्ठा rio_mport, dma);
पूर्ण
#पूर्ण_अगर /* CONFIG_RAPIDIO_DMA_ENGINE */

/**
 * काष्ठा rio_scan - RIO क्रमागतeration and discovery operations
 * @owner: The module owner of this काष्ठाure
 * @क्रमागतerate: Callback to perक्रमm RapidIO fabric क्रमागतeration.
 * @discover: Callback to perक्रमm RapidIO fabric discovery.
 */
काष्ठा rio_scan अणु
	काष्ठा module *owner;
	पूर्णांक (*क्रमागतerate)(काष्ठा rio_mport *mport, u32 flags);
	पूर्णांक (*discover)(काष्ठा rio_mport *mport, u32 flags);
पूर्ण;

/**
 * काष्ठा rio_scan_node - list node to रेजिस्टर RapidIO क्रमागतeration and
 * discovery methods with RapidIO core.
 * @mport_id: ID of an mport (net) serviced by this क्रमागतerator
 * @node: node in global list of रेजिस्टरed क्रमागतerators
 * @ops: RIO क्रमागतeration and discovery operations
 */
काष्ठा rio_scan_node अणु
	पूर्णांक mport_id;
	काष्ठा list_head node;
	काष्ठा rio_scan *ops;
पूर्ण;

/* Architecture and hardware-specअगरic functions */
बाह्य पूर्णांक rio_mport_initialize(काष्ठा rio_mport *);
बाह्य पूर्णांक rio_रेजिस्टर_mport(काष्ठा rio_mport *);
बाह्य पूर्णांक rio_unरेजिस्टर_mport(काष्ठा rio_mport *);
बाह्य पूर्णांक rio_खोलो_inb_mbox(काष्ठा rio_mport *, व्योम *, पूर्णांक, पूर्णांक);
बाह्य व्योम rio_बंद_inb_mbox(काष्ठा rio_mport *, पूर्णांक);
बाह्य पूर्णांक rio_खोलो_outb_mbox(काष्ठा rio_mport *, व्योम *, पूर्णांक, पूर्णांक);
बाह्य व्योम rio_बंद_outb_mbox(काष्ठा rio_mport *, पूर्णांक);
बाह्य पूर्णांक rio_query_mport(काष्ठा rio_mport *port,
			   काष्ठा rio_mport_attr *mport_attr);

#पूर्ण_अगर				/* LINUX_RIO_H */
