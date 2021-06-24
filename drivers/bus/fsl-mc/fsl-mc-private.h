<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Freescale Management Complex (MC) bus निजी declarations
 *
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 *
 */
#अगर_अघोषित _FSL_MC_PRIVATE_H_
#घोषणा _FSL_MC_PRIVATE_H_

#समावेश <linux/fsl/mc.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/miscdevice.h>

/*
 * Data Path Management Complex (DPMNG) General API
 */

/* DPMNG command versioning */
#घोषणा DPMNG_CMD_BASE_VERSION		1
#घोषणा DPMNG_CMD_ID_OFFSET		4

#घोषणा DPMNG_CMD(id)	(((id) << DPMNG_CMD_ID_OFFSET) | DPMNG_CMD_BASE_VERSION)

/* DPMNG command IDs */
#घोषणा DPMNG_CMDID_GET_VERSION		DPMNG_CMD(0x831)

काष्ठा dpmng_rsp_get_version अणु
	__le32 revision;
	__le32 version_major;
	__le32 version_minor;
पूर्ण;

/*
 * Data Path Management Command Portal (DPMCP) API
 */

/* Minimal supported DPMCP Version */
#घोषणा DPMCP_MIN_VER_MAJOR		3
#घोषणा DPMCP_MIN_VER_MINOR		0

/* DPMCP command versioning */
#घोषणा DPMCP_CMD_BASE_VERSION		1
#घोषणा DPMCP_CMD_ID_OFFSET		4

#घोषणा DPMCP_CMD(id)	(((id) << DPMCP_CMD_ID_OFFSET) | DPMCP_CMD_BASE_VERSION)

/* DPMCP command IDs */
#घोषणा DPMCP_CMDID_CLOSE		DPMCP_CMD(0x800)
#घोषणा DPMCP_CMDID_OPEN		DPMCP_CMD(0x80b)
#घोषणा DPMCP_CMDID_RESET		DPMCP_CMD(0x005)

काष्ठा dpmcp_cmd_खोलो अणु
	__le32 dpmcp_id;
पूर्ण;

/*
 * Initialization and runसमय control APIs क्रम DPMCP
 */
पूर्णांक dpmcp_खोलो(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       पूर्णांक dpmcp_id,
	       u16 *token);

पूर्णांक dpmcp_बंद(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token);

पूर्णांक dpmcp_reset(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token);

/*
 * Data Path Resource Container (DPRC) API
 */

/* Minimal supported DPRC Version */
#घोषणा DPRC_MIN_VER_MAJOR			6
#घोषणा DPRC_MIN_VER_MINOR			0

/* DPRC command versioning */
#घोषणा DPRC_CMD_BASE_VERSION			1
#घोषणा DPRC_CMD_2ND_VERSION			2
#घोषणा DPRC_CMD_3RD_VERSION			3
#घोषणा DPRC_CMD_ID_OFFSET			4

#घोषणा DPRC_CMD(id)	(((id) << DPRC_CMD_ID_OFFSET) | DPRC_CMD_BASE_VERSION)
#घोषणा DPRC_CMD_V2(id)	(((id) << DPRC_CMD_ID_OFFSET) | DPRC_CMD_2ND_VERSION)
#घोषणा DPRC_CMD_V3(id)	(((id) << DPRC_CMD_ID_OFFSET) | DPRC_CMD_3RD_VERSION)

/* DPRC command IDs */
#घोषणा DPRC_CMDID_CLOSE                        DPRC_CMD(0x800)
#घोषणा DPRC_CMDID_OPEN                         DPRC_CMD(0x805)
#घोषणा DPRC_CMDID_GET_API_VERSION              DPRC_CMD(0xa05)

#घोषणा DPRC_CMDID_GET_ATTR                     DPRC_CMD(0x004)
#घोषणा DPRC_CMDID_RESET_CONT                   DPRC_CMD(0x005)
#घोषणा DPRC_CMDID_RESET_CONT_V2                DPRC_CMD_V2(0x005)

#घोषणा DPRC_CMDID_SET_IRQ                      DPRC_CMD(0x010)
#घोषणा DPRC_CMDID_SET_IRQ_ENABLE               DPRC_CMD(0x012)
#घोषणा DPRC_CMDID_SET_IRQ_MASK                 DPRC_CMD(0x014)
#घोषणा DPRC_CMDID_GET_IRQ_STATUS               DPRC_CMD(0x016)
#घोषणा DPRC_CMDID_CLEAR_IRQ_STATUS             DPRC_CMD(0x017)

#घोषणा DPRC_CMDID_GET_CONT_ID                  DPRC_CMD(0x830)
#घोषणा DPRC_CMDID_GET_OBJ_COUNT                DPRC_CMD(0x159)
#घोषणा DPRC_CMDID_GET_OBJ                      DPRC_CMD(0x15A)
#घोषणा DPRC_CMDID_GET_OBJ_REG                  DPRC_CMD(0x15E)
#घोषणा DPRC_CMDID_GET_OBJ_REG_V2               DPRC_CMD_V2(0x15E)
#घोषणा DPRC_CMDID_GET_OBJ_REG_V3               DPRC_CMD_V3(0x15E)
#घोषणा DPRC_CMDID_SET_OBJ_IRQ                  DPRC_CMD(0x15F)

#घोषणा DPRC_CMDID_GET_CONNECTION               DPRC_CMD(0x16C)

काष्ठा dprc_cmd_खोलो अणु
	__le32 container_id;
पूर्ण;

काष्ठा dprc_cmd_reset_container अणु
	__le32 child_container_id;
	__le32 options;
पूर्ण;

काष्ठा dprc_cmd_set_irq अणु
	/* cmd word 0 */
	__le32 irq_val;
	u8 irq_index;
	u8 pad[3];
	/* cmd word 1 */
	__le64 irq_addr;
	/* cmd word 2 */
	__le32 irq_num;
पूर्ण;

#घोषणा DPRC_ENABLE		0x1

काष्ठा dprc_cmd_set_irq_enable अणु
	u8 enable;
	u8 pad[3];
	u8 irq_index;
पूर्ण;

काष्ठा dprc_cmd_set_irq_mask अणु
	__le32 mask;
	u8 irq_index;
पूर्ण;

काष्ठा dprc_cmd_get_irq_status अणु
	__le32 status;
	u8 irq_index;
पूर्ण;

काष्ठा dprc_rsp_get_irq_status अणु
	__le32 status;
पूर्ण;

काष्ठा dprc_cmd_clear_irq_status अणु
	__le32 status;
	u8 irq_index;
पूर्ण;

काष्ठा dprc_rsp_get_attributes अणु
	/* response word 0 */
	__le32 container_id;
	__le32 icid;
	/* response word 1 */
	__le32 options;
	__le32 portal_id;
पूर्ण;

काष्ठा dprc_rsp_get_obj_count अणु
	__le32 pad;
	__le32 obj_count;
पूर्ण;

काष्ठा dprc_cmd_get_obj अणु
	__le32 obj_index;
पूर्ण;

काष्ठा dprc_rsp_get_obj अणु
	/* response word 0 */
	__le32 pad0;
	__le32 id;
	/* response word 1 */
	__le16 venकरोr;
	u8 irq_count;
	u8 region_count;
	__le32 state;
	/* response word 2 */
	__le16 version_major;
	__le16 version_minor;
	__le16 flags;
	__le16 pad1;
	/* response word 3-4 */
	u8 type[16];
	/* response word 5-6 */
	u8 label[16];
पूर्ण;

काष्ठा dprc_cmd_get_obj_region अणु
	/* cmd word 0 */
	__le32 obj_id;
	__le16 pad0;
	u8 region_index;
	u8 pad1;
	/* cmd word 1-2 */
	__le64 pad2[2];
	/* cmd word 3-4 */
	u8 obj_type[16];
पूर्ण;

काष्ठा dprc_rsp_get_obj_region अणु
	/* response word 0 */
	__le64 pad0;
	/* response word 1 */
	__le64 base_offset;
	/* response word 2 */
	__le32 size;
	u8 type;
	u8 pad2[3];
	/* response word 3 */
	__le32 flags;
	__le32 pad3;
	/* response word 4 */
	/* base_addr may be zero अगर older MC firmware is used */
	__le64 base_addr;
पूर्ण;

काष्ठा dprc_cmd_set_obj_irq अणु
	/* cmd word 0 */
	__le32 irq_val;
	u8 irq_index;
	u8 pad[3];
	/* cmd word 1 */
	__le64 irq_addr;
	/* cmd word 2 */
	__le32 irq_num;
	__le32 obj_id;
	/* cmd word 3-4 */
	u8 obj_type[16];
पूर्ण;

काष्ठा dprc_cmd_get_connection अणु
	__le32 ep1_id;
	__le16 ep1_पूर्णांकerface_id;
	u8 pad[2];
	u8 ep1_type[16];
पूर्ण;

काष्ठा dprc_rsp_get_connection अणु
	__le64 pad[3];
	__le32 ep2_id;
	__le16 ep2_पूर्णांकerface_id;
	__le16 pad1;
	u8 ep2_type[16];
	__le32 state;
पूर्ण;

/*
 * DPRC API क्रम managing and querying DPAA resources
 */
पूर्णांक dprc_खोलो(काष्ठा fsl_mc_io *mc_io,
	      u32 cmd_flags,
	      पूर्णांक container_id,
	      u16 *token);

पूर्णांक dprc_बंद(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       u16 token);

/* DPRC IRQ events */

/* IRQ event - Indicates that a new object added to the container */
#घोषणा DPRC_IRQ_EVENT_OBJ_ADDED		0x00000001
/* IRQ event - Indicates that an object was हटाओd from the container */
#घोषणा DPRC_IRQ_EVENT_OBJ_REMOVED		0x00000002
/*
 * IRQ event - Indicates that one of the descendant containers that खोलोed by
 * this container is destroyed
 */
#घोषणा DPRC_IRQ_EVENT_CONTAINER_DESTROYED	0x00000010

/*
 * IRQ event - Indicates that on one of the container's खोलोed object is
 * destroyed
 */
#घोषणा DPRC_IRQ_EVENT_OBJ_DESTROYED		0x00000020

/* Irq event - Indicates that object is created at the container */
#घोषणा DPRC_IRQ_EVENT_OBJ_CREATED		0x00000040

/**
 * काष्ठा dprc_irq_cfg - IRQ configuration
 * @paddr:	Address that must be written to संकेत a message-based पूर्णांकerrupt
 * @val:	Value to ग_लिखो पूर्णांकo irq_addr address
 * @irq_num:	A user defined number associated with this IRQ
 */
काष्ठा dprc_irq_cfg अणु
	     phys_addr_t paddr;
	     u32 val;
	     पूर्णांक irq_num;
पूर्ण;

पूर्णांक dprc_set_irq(काष्ठा fsl_mc_io *mc_io,
		 u32 cmd_flags,
		 u16 token,
		 u8 irq_index,
		 काष्ठा dprc_irq_cfg *irq_cfg);

पूर्णांक dprc_set_irq_enable(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			u8 irq_index,
			u8 en);

पूर्णांक dprc_set_irq_mask(काष्ठा fsl_mc_io *mc_io,
		      u32 cmd_flags,
		      u16 token,
		      u8 irq_index,
		      u32 mask);

पूर्णांक dprc_get_irq_status(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			u8 irq_index,
			u32 *status);

पूर्णांक dprc_clear_irq_status(काष्ठा fsl_mc_io *mc_io,
			  u32 cmd_flags,
			  u16 token,
			  u8 irq_index,
			  u32 status);

/**
 * काष्ठा dprc_attributes - Container attributes
 * @container_id: Container's ID
 * @icid: Container's ICID
 * @portal_id: Container's portal ID
 * @options: Container's options as set at container's creation
 */
काष्ठा dprc_attributes अणु
	पूर्णांक container_id;
	u32 icid;
	पूर्णांक portal_id;
	u64 options;
पूर्ण;

पूर्णांक dprc_get_attributes(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			काष्ठा dprc_attributes *attributes);

पूर्णांक dprc_get_obj_count(काष्ठा fsl_mc_io *mc_io,
		       u32 cmd_flags,
		       u16 token,
		       पूर्णांक *obj_count);

पूर्णांक dprc_get_obj(काष्ठा fsl_mc_io *mc_io,
		 u32 cmd_flags,
		 u16 token,
		 पूर्णांक obj_index,
		 काष्ठा fsl_mc_obj_desc *obj_desc);

पूर्णांक dprc_set_obj_irq(काष्ठा fsl_mc_io *mc_io,
		     u32 cmd_flags,
		     u16 token,
		     अक्षर *obj_type,
		     पूर्णांक obj_id,
		     u8 irq_index,
		     काष्ठा dprc_irq_cfg *irq_cfg);
/**
 * क्रमागत dprc_region_type - Region type
 * @DPRC_REGION_TYPE_MC_PORTAL: MC portal region
 * @DPRC_REGION_TYPE_QBMAN_PORTAL: Qbman portal region
 */
क्रमागत dprc_region_type अणु
	DPRC_REGION_TYPE_MC_PORTAL,
	DPRC_REGION_TYPE_QBMAN_PORTAL,
	DPRC_REGION_TYPE_QBMAN_MEM_BACKED_PORTAL
पूर्ण;

/**
 * काष्ठा dprc_region_desc - Mappable region descriptor
 * @base_offset: Region offset from region's base address.
 *	For DPMCP and DPRC objects, region base is offset from SoC MC portals
 *	base address; For DPIO, region base is offset from SoC QMan portals
 *	base address
 * @size: Region size (in bytes)
 * @flags: Region attributes
 * @type: Portal region type
 */
काष्ठा dprc_region_desc अणु
	u32 base_offset;
	u32 size;
	u32 flags;
	क्रमागत dprc_region_type type;
	u64 base_address;
पूर्ण;

पूर्णांक dprc_get_obj_region(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			अक्षर *obj_type,
			पूर्णांक obj_id,
			u8 region_index,
			काष्ठा dprc_region_desc *region_desc);

पूर्णांक dprc_get_api_version(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 *major_ver,
			 u16 *minor_ver);

पूर्णांक dprc_get_container_id(काष्ठा fsl_mc_io *mc_io,
			  u32 cmd_flags,
			  पूर्णांक *container_id);

/**
 * काष्ठा dprc_endpoपूर्णांक - Endpoपूर्णांक description क्रम link connect/disconnect
 *			operations
 * @type:	Endpoपूर्णांक object type: शून्य terminated string
 * @id:		Endpoपूर्णांक object ID
 * @अगर_id:	Interface ID; should be set क्रम endpoपूर्णांकs with multiple
 *		पूर्णांकerfaces ("dpsw", "dpdmux"); क्रम others, always set to 0
 */
काष्ठा dprc_endpoपूर्णांक अणु
	अक्षर type[16];
	पूर्णांक id;
	u16 अगर_id;
पूर्ण;

पूर्णांक dprc_get_connection(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			स्थिर काष्ठा dprc_endpoपूर्णांक *endpoपूर्णांक1,
			काष्ठा dprc_endpoपूर्णांक *endpoपूर्णांक2,
			पूर्णांक *state);

/*
 * Data Path Buffer Pool (DPBP) API
 */

/* DPBP Version */
#घोषणा DPBP_VER_MAJOR				3
#घोषणा DPBP_VER_MINOR				2

/* Command versioning */
#घोषणा DPBP_CMD_BASE_VERSION			1
#घोषणा DPBP_CMD_ID_OFFSET			4

#घोषणा DPBP_CMD(id)	(((id) << DPBP_CMD_ID_OFFSET) | DPBP_CMD_BASE_VERSION)

/* Command IDs */
#घोषणा DPBP_CMDID_CLOSE		DPBP_CMD(0x800)
#घोषणा DPBP_CMDID_OPEN			DPBP_CMD(0x804)

#घोषणा DPBP_CMDID_ENABLE		DPBP_CMD(0x002)
#घोषणा DPBP_CMDID_DISABLE		DPBP_CMD(0x003)
#घोषणा DPBP_CMDID_GET_ATTR		DPBP_CMD(0x004)
#घोषणा DPBP_CMDID_RESET		DPBP_CMD(0x005)

काष्ठा dpbp_cmd_खोलो अणु
	__le32 dpbp_id;
पूर्ण;

#घोषणा DPBP_ENABLE			0x1

काष्ठा dpbp_rsp_get_attributes अणु
	/* response word 0 */
	__le16 pad;
	__le16 bpid;
	__le32 id;
	/* response word 1 */
	__le16 version_major;
	__le16 version_minor;
पूर्ण;

/*
 * Data Path Concentrator (DPCON) API
 */

/* DPCON Version */
#घोषणा DPCON_VER_MAJOR				3
#घोषणा DPCON_VER_MINOR				2

/* Command versioning */
#घोषणा DPCON_CMD_BASE_VERSION			1
#घोषणा DPCON_CMD_ID_OFFSET			4

#घोषणा DPCON_CMD(id)	(((id) << DPCON_CMD_ID_OFFSET) | DPCON_CMD_BASE_VERSION)

/* Command IDs */
#घोषणा DPCON_CMDID_CLOSE			DPCON_CMD(0x800)
#घोषणा DPCON_CMDID_OPEN			DPCON_CMD(0x808)

#घोषणा DPCON_CMDID_ENABLE			DPCON_CMD(0x002)
#घोषणा DPCON_CMDID_DISABLE			DPCON_CMD(0x003)
#घोषणा DPCON_CMDID_GET_ATTR			DPCON_CMD(0x004)
#घोषणा DPCON_CMDID_RESET			DPCON_CMD(0x005)

#घोषणा DPCON_CMDID_SET_NOTIFICATION		DPCON_CMD(0x100)

काष्ठा dpcon_cmd_खोलो अणु
	__le32 dpcon_id;
पूर्ण;

#घोषणा DPCON_ENABLE			1

काष्ठा dpcon_rsp_get_attr अणु
	/* response word 0 */
	__le32 id;
	__le16 qbman_ch_id;
	u8 num_priorities;
	u8 pad;
पूर्ण;

काष्ठा dpcon_cmd_set_notअगरication अणु
	/* cmd word 0 */
	__le32 dpio_id;
	u8 priority;
	u8 pad[3];
	/* cmd word 1 */
	__le64 user_ctx;
पूर्ण;


/**
 * काष्ठा fsl_mc_resource_pool - Pool of MC resources of a given
 * type
 * @type: type of resources in the pool
 * @max_count: maximum number of resources in the pool
 * @मुक्त_count: number of मुक्त resources in the pool
 * @mutex: mutex to serialize access to the pool's मुक्त list
 * @मुक्त_list: anchor node of list of मुक्त resources in the pool
 * @mc_bus: poपूर्णांकer to the MC bus that owns this resource pool
 */
काष्ठा fsl_mc_resource_pool अणु
	क्रमागत fsl_mc_pool_type type;
	पूर्णांक max_count;
	पूर्णांक मुक्त_count;
	काष्ठा mutex mutex;	/* serializes access to मुक्त_list */
	काष्ठा list_head मुक्त_list;
	काष्ठा fsl_mc_bus *mc_bus;
पूर्ण;

/**
 * काष्ठा fsl_mc_uapi - inक्रमmation associated with a device file
 * @misc: काष्ठा miscdevice linked to the root dprc
 * @device: newly created device in /dev
 * @mutex: mutex lock to serialize the खोलो/release operations
 * @local_instance_in_use: local MC I/O instance in use or not
 * @अटल_mc_io: poपूर्णांकer to the अटल MC I/O object
 */
काष्ठा fsl_mc_uapi अणु
	काष्ठा miscdevice misc;
	काष्ठा device *device;
	काष्ठा mutex mutex; /* serialize खोलो/release operations */
	u32 local_instance_in_use;
	काष्ठा fsl_mc_io *अटल_mc_io;
पूर्ण;

/**
 * काष्ठा fsl_mc_bus - logical bus that corresponds to a physical DPRC
 * @mc_dev: fsl-mc device क्रम the bus device itself.
 * @resource_pools: array of resource pools (one pool per resource type)
 * क्रम this MC bus. These resources represent allocatable entities
 * from the physical DPRC.
 * @irq_resources: Poपूर्णांकer to array of IRQ objects क्रम the IRQ pool
 * @scan_mutex: Serializes bus scanning
 * @dprc_attr: DPRC attributes
 * @uapi_misc: काष्ठा that असलtracts the पूर्णांकeraction with userspace
 */
काष्ठा fsl_mc_bus अणु
	काष्ठा fsl_mc_device mc_dev;
	काष्ठा fsl_mc_resource_pool resource_pools[FSL_MC_NUM_POOL_TYPES];
	काष्ठा fsl_mc_device_irq *irq_resources;
	काष्ठा mutex scan_mutex;    /* serializes bus scanning */
	काष्ठा dprc_attributes dprc_attr;
	काष्ठा fsl_mc_uapi uapi_misc;
	पूर्णांक irq_enabled;
पूर्ण;

#घोषणा to_fsl_mc_bus(_mc_dev) \
	container_of(_mc_dev, काष्ठा fsl_mc_bus, mc_dev)

पूर्णांक __must_check fsl_mc_device_add(काष्ठा fsl_mc_obj_desc *obj_desc,
				   काष्ठा fsl_mc_io *mc_io,
				   काष्ठा device *parent_dev,
				   काष्ठा fsl_mc_device **new_mc_dev);

व्योम fsl_mc_device_हटाओ(काष्ठा fsl_mc_device *mc_dev);

पूर्णांक __init dprc_driver_init(व्योम);

व्योम dprc_driver_निकास(व्योम);

पूर्णांक dprc_scan_objects(काष्ठा fsl_mc_device *mc_bus_dev,
		      bool alloc_पूर्णांकerrupts);

पूर्णांक __init fsl_mc_allocator_driver_init(व्योम);

व्योम fsl_mc_allocator_driver_निकास(व्योम);

व्योम fsl_mc_init_all_resource_pools(काष्ठा fsl_mc_device *mc_bus_dev);

व्योम fsl_mc_cleanup_all_resource_pools(काष्ठा fsl_mc_device *mc_bus_dev);

पूर्णांक __must_check fsl_mc_resource_allocate(काष्ठा fsl_mc_bus *mc_bus,
					  क्रमागत fsl_mc_pool_type pool_type,
					  काष्ठा fsl_mc_resource
							  **new_resource);

व्योम fsl_mc_resource_मुक्त(काष्ठा fsl_mc_resource *resource);

पूर्णांक fsl_mc_msi_करोमुख्य_alloc_irqs(काष्ठा device *dev,
				 अचिन्हित पूर्णांक irq_count);

व्योम fsl_mc_msi_करोमुख्य_मुक्त_irqs(काष्ठा device *dev);

काष्ठा irq_करोमुख्य *fsl_mc_find_msi_करोमुख्य(काष्ठा device *dev);

पूर्णांक __must_check fsl_create_mc_io(काष्ठा device *dev,
				  phys_addr_t mc_portal_phys_addr,
				  u32 mc_portal_size,
				  काष्ठा fsl_mc_device *dpmcp_dev,
				  u32 flags, काष्ठा fsl_mc_io **new_mc_io);

व्योम fsl_destroy_mc_io(काष्ठा fsl_mc_io *mc_io);

bool fsl_mc_is_root_dprc(काष्ठा device *dev);

व्योम fsl_mc_get_root_dprc(काष्ठा device *dev,
			 काष्ठा device **root_dprc_dev);

काष्ठा fsl_mc_device *fsl_mc_device_lookup(काष्ठा fsl_mc_obj_desc *obj_desc,
					   काष्ठा fsl_mc_device *mc_bus_dev);

u16 mc_cmd_hdr_पढ़ो_cmdid(काष्ठा fsl_mc_command *cmd);

#अगर_घोषित CONFIG_FSL_MC_UAPI_SUPPORT

पूर्णांक fsl_mc_uapi_create_device_file(काष्ठा fsl_mc_bus *mc_bus);

व्योम fsl_mc_uapi_हटाओ_device_file(काष्ठा fsl_mc_bus *mc_bus);

#अन्यथा

अटल अंतरभूत पूर्णांक fsl_mc_uapi_create_device_file(काष्ठा fsl_mc_bus *mc_bus)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम fsl_mc_uapi_हटाओ_device_file(काष्ठा fsl_mc_bus *mc_bus)
अणु
पूर्ण

#पूर्ण_अगर

पूर्णांक disable_dprc_irq(काष्ठा fsl_mc_device *mc_dev);
पूर्णांक enable_dprc_irq(काष्ठा fsl_mc_device *mc_dev);
पूर्णांक get_dprc_irq_state(काष्ठा fsl_mc_device *mc_dev);

#पूर्ण_अगर /* _FSL_MC_PRIVATE_H_ */
