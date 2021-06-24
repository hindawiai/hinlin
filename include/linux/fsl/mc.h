<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Freescale Management Complex (MC) bus खुला पूर्णांकerface
 *
 * Copyright (C) 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2019-2020 NXP
 * Author: German Rivera <German.Rivera@मुक्तscale.com>
 *
 */
#अगर_अघोषित _FSL_MC_H_
#घोषणा _FSL_MC_H_

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <uapi/linux/fsl_mc.h>

#घोषणा FSL_MC_VENDOR_FREESCALE	0x1957

काष्ठा irq_करोमुख्य;
काष्ठा msi_करोमुख्य_info;

काष्ठा fsl_mc_device;
काष्ठा fsl_mc_io;

/**
 * काष्ठा fsl_mc_driver - MC object device driver object
 * @driver: Generic device driver
 * @match_id_table: table of supported device matching Ids
 * @probe: Function called when a device is added
 * @हटाओ: Function called when a device is हटाओd
 * @shutकरोwn: Function called at shutकरोwn समय to quiesce the device
 * @suspend: Function called when a device is stopped
 * @resume: Function called when a device is resumed
 *
 * Generic DPAA device driver object क्रम device drivers that are रेजिस्टरed
 * with a DPRC bus. This काष्ठाure is to be embedded in each device-specअगरic
 * driver काष्ठाure.
 */
काष्ठा fsl_mc_driver अणु
	काष्ठा device_driver driver;
	स्थिर काष्ठा fsl_mc_device_id *match_id_table;
	पूर्णांक (*probe)(काष्ठा fsl_mc_device *dev);
	पूर्णांक (*हटाओ)(काष्ठा fsl_mc_device *dev);
	व्योम (*shutकरोwn)(काष्ठा fsl_mc_device *dev);
	पूर्णांक (*suspend)(काष्ठा fsl_mc_device *dev, pm_message_t state);
	पूर्णांक (*resume)(काष्ठा fsl_mc_device *dev);
पूर्ण;

#घोषणा to_fsl_mc_driver(_drv) \
	container_of(_drv, काष्ठा fsl_mc_driver, driver)

/**
 * क्रमागत fsl_mc_pool_type - Types of allocatable MC bus resources
 *
 * Entries in these क्रमागत are used as indices in the array of resource
 * pools of an fsl_mc_bus object.
 */
क्रमागत fsl_mc_pool_type अणु
	FSL_MC_POOL_DPMCP = 0x0,    /* corresponds to "dpmcp" in the MC */
	FSL_MC_POOL_DPBP,	    /* corresponds to "dpbp" in the MC */
	FSL_MC_POOL_DPCON,	    /* corresponds to "dpcon" in the MC */
	FSL_MC_POOL_IRQ,

	/*
	 * NOTE: New resource pool types must be added beक्रमe this entry
	 */
	FSL_MC_NUM_POOL_TYPES
पूर्ण;

/**
 * काष्ठा fsl_mc_resource - MC generic resource
 * @type: type of resource
 * @id: unique MC resource Id within the resources of the same type
 * @data: poपूर्णांकer to resource-specअगरic data अगर the resource is currently
 * allocated, or शून्य अगर the resource is not currently allocated.
 * @parent_pool: poपूर्णांकer to the parent resource pool from which this
 * resource is allocated from.
 * @node: Node in the मुक्त list of the corresponding resource pool
 *
 * NOTE: This काष्ठाure is to be embedded as a field of specअगरic
 * MC resource काष्ठाures.
 */
काष्ठा fsl_mc_resource अणु
	क्रमागत fsl_mc_pool_type type;
	s32 id;
	व्योम *data;
	काष्ठा fsl_mc_resource_pool *parent_pool;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा fsl_mc_device_irq - MC object device message-based पूर्णांकerrupt
 * @msi_desc: poपूर्णांकer to MSI descriptor allocated by fsl_mc_msi_alloc_descs()
 * @mc_dev: MC object device that owns this पूर्णांकerrupt
 * @dev_irq_index: device-relative IRQ index
 * @resource: MC generic resource associated with the पूर्णांकerrupt
 */
काष्ठा fsl_mc_device_irq अणु
	काष्ठा msi_desc *msi_desc;
	काष्ठा fsl_mc_device *mc_dev;
	u8 dev_irq_index;
	काष्ठा fsl_mc_resource resource;
पूर्ण;

#घोषणा to_fsl_mc_irq(_mc_resource) \
	container_of(_mc_resource, काष्ठा fsl_mc_device_irq, resource)

/* Opened state - Indicates that an object is खोलो by at least one owner */
#घोषणा FSL_MC_OBJ_STATE_OPEN		0x00000001
/* Plugged state - Indicates that the object is plugged */
#घोषणा FSL_MC_OBJ_STATE_PLUGGED	0x00000002

/**
 * Shareability flag - Object flag indicating no memory shareability.
 * the object generates memory accesses that are non coherent with other
 * masters;
 * user is responsible क्रम proper memory handling through IOMMU configuration.
 */
#घोषणा FSL_MC_OBJ_FLAG_NO_MEM_SHAREABILITY	0x0001

/**
 * काष्ठा fsl_mc_obj_desc - Object descriptor
 * @type: Type of object: शून्य terminated string
 * @id: ID of logical object resource
 * @venकरोr: Object venकरोr identअगरier
 * @ver_major: Major version number
 * @ver_minor:  Minor version number
 * @irq_count: Number of पूर्णांकerrupts supported by the object
 * @region_count: Number of mappable regions supported by the object
 * @state: Object state: combination of FSL_MC_OBJ_STATE_ states
 * @label: Object label: शून्य terminated string
 * @flags: Object's flags
 */
काष्ठा fsl_mc_obj_desc अणु
	अक्षर type[16];
	पूर्णांक id;
	u16 venकरोr;
	u16 ver_major;
	u16 ver_minor;
	u8 irq_count;
	u8 region_count;
	u32 state;
	अक्षर label[16];
	u16 flags;
पूर्ण;

/**
 * Bit masks क्रम a MC object device (काष्ठा fsl_mc_device) flags
 */
#घोषणा FSL_MC_IS_DPRC	0x0001

/* Region flags */
/* Indicates that region can be mapped as cacheable */
#घोषणा FSL_MC_REGION_CACHEABLE	0x00000001

/* Indicates that region can be mapped as shareable */
#घोषणा FSL_MC_REGION_SHAREABLE	0x00000002

/**
 * काष्ठा fsl_mc_device - MC object device object
 * @dev: Linux driver model device object
 * @dma_mask: Default DMA mask
 * @flags: MC object device flags
 * @icid: Isolation context ID क्रम the device
 * @mc_handle: MC handle क्रम the corresponding MC object खोलोed
 * @mc_io: Poपूर्णांकer to MC IO object asचिन्हित to this device or
 * शून्य अगर none.
 * @obj_desc: MC description of the DPAA device
 * @regions: poपूर्णांकer to array of MMIO region entries
 * @irqs: poपूर्णांकer to array of poपूर्णांकers to पूर्णांकerrupts allocated to this device
 * @resource: generic resource associated with this MC object device, अगर any.
 * @driver_override: driver name to क्रमce a match
 *
 * Generic device object क्रम MC object devices that are "attached" to a
 * MC bus.
 *
 * NOTES:
 * - For a non-DPRC object its icid is the same as its parent DPRC's icid.
 * - The SMMU notअगरier callback माला_लो invoked after device_add() has been
 *   called क्रम an MC object device, but beक्रमe the device-specअगरic probe
 *   callback माला_लो called.
 * - DP_OBJ_DPRC objects are the only MC objects that have built-in MC
 *   portals. For all other MC objects, their device drivers are responsible क्रम
 *   allocating MC portals क्रम them by calling fsl_mc_portal_allocate().
 * - Some types of MC objects (e.g., DP_OBJ_DPBP, DP_OBJ_DPCON) are
 *   treated as resources that can be allocated/deallocated from the
 *   corresponding resource pool in the object's parent DPRC, using the
 *   fsl_mc_object_allocate()/fsl_mc_object_मुक्त() functions. These MC objects
 *   are known as "allocatable" objects. For them, the corresponding
 *   fsl_mc_device's 'resource' poपूर्णांकs to the associated resource object.
 *   For MC objects that are not allocatable (e.g., DP_OBJ_DPRC, DP_OBJ_DPNI),
 *   'resource' is शून्य.
 */
काष्ठा fsl_mc_device अणु
	काष्ठा device dev;
	u64 dma_mask;
	u16 flags;
	u32 icid;
	u16 mc_handle;
	काष्ठा fsl_mc_io *mc_io;
	काष्ठा fsl_mc_obj_desc obj_desc;
	काष्ठा resource *regions;
	काष्ठा fsl_mc_device_irq **irqs;
	काष्ठा fsl_mc_resource *resource;
	काष्ठा device_link *consumer_link;
	अक्षर   *driver_override;
पूर्ण;

#घोषणा to_fsl_mc_device(_dev) \
	container_of(_dev, काष्ठा fsl_mc_device, dev)

काष्ठा mc_cmd_header अणु
	u8 src_id;
	u8 flags_hw;
	u8 status;
	u8 flags_sw;
	__le16 token;
	__le16 cmd_id;
पूर्ण;

क्रमागत mc_cmd_status अणु
	MC_CMD_STATUS_OK = 0x0, /* Completed successfully */
	MC_CMD_STATUS_READY = 0x1, /* Ready to be processed */
	MC_CMD_STATUS_AUTH_ERR = 0x3, /* Authentication error */
	MC_CMD_STATUS_NO_PRIVILEGE = 0x4, /* No privilege */
	MC_CMD_STATUS_DMA_ERR = 0x5, /* DMA or I/O error */
	MC_CMD_STATUS_CONFIG_ERR = 0x6, /* Configuration error */
	MC_CMD_STATUS_TIMEOUT = 0x7, /* Operation समयd out */
	MC_CMD_STATUS_NO_RESOURCE = 0x8, /* No resources */
	MC_CMD_STATUS_NO_MEMORY = 0x9, /* No memory available */
	MC_CMD_STATUS_BUSY = 0xA, /* Device is busy */
	MC_CMD_STATUS_UNSUPPORTED_OP = 0xB, /* Unsupported operation */
	MC_CMD_STATUS_INVALID_STATE = 0xC /* Invalid state */
पूर्ण;

/*
 * MC command flags
 */

/* High priority flag */
#घोषणा MC_CMD_FLAG_PRI		0x80
/* Command completion flag */
#घोषणा MC_CMD_FLAG_INTR_DIS	0x01

अटल अंतरभूत __le64 mc_encode_cmd_header(u16 cmd_id,
					  u32 cmd_flags,
					  u16 token)
अणु
	__le64 header = 0;
	काष्ठा mc_cmd_header *hdr = (काष्ठा mc_cmd_header *)&header;

	hdr->cmd_id = cpu_to_le16(cmd_id);
	hdr->token  = cpu_to_le16(token);
	hdr->status = MC_CMD_STATUS_READY;
	अगर (cmd_flags & MC_CMD_FLAG_PRI)
		hdr->flags_hw = MC_CMD_FLAG_PRI;
	अगर (cmd_flags & MC_CMD_FLAG_INTR_DIS)
		hdr->flags_sw = MC_CMD_FLAG_INTR_DIS;

	वापस header;
पूर्ण

अटल अंतरभूत u16 mc_cmd_hdr_पढ़ो_token(काष्ठा fsl_mc_command *cmd)
अणु
	काष्ठा mc_cmd_header *hdr = (काष्ठा mc_cmd_header *)&cmd->header;
	u16 token = le16_to_cpu(hdr->token);

	वापस token;
पूर्ण

काष्ठा mc_rsp_create अणु
	__le32 object_id;
पूर्ण;

काष्ठा mc_rsp_api_ver अणु
	__le16 major_ver;
	__le16 minor_ver;
पूर्ण;

अटल अंतरभूत u32 mc_cmd_पढ़ो_object_id(काष्ठा fsl_mc_command *cmd)
अणु
	काष्ठा mc_rsp_create *rsp_params;

	rsp_params = (काष्ठा mc_rsp_create *)cmd->params;
	वापस le32_to_cpu(rsp_params->object_id);
पूर्ण

अटल अंतरभूत व्योम mc_cmd_पढ़ो_api_version(काष्ठा fsl_mc_command *cmd,
					   u16 *major_ver,
					   u16 *minor_ver)
अणु
	काष्ठा mc_rsp_api_ver *rsp_params;

	rsp_params = (काष्ठा mc_rsp_api_ver *)cmd->params;
	*major_ver = le16_to_cpu(rsp_params->major_ver);
	*minor_ver = le16_to_cpu(rsp_params->minor_ver);
पूर्ण

/**
 * Bit masks क्रम a MC I/O object (काष्ठा fsl_mc_io) flags
 */
#घोषणा FSL_MC_IO_ATOMIC_CONTEXT_PORTAL	0x0001

/**
 * काष्ठा fsl_mc_io - MC I/O object to be passed-in to mc_send_command()
 * @dev: device associated with this Mc I/O object
 * @flags: flags क्रम mc_send_command()
 * @portal_size: MC command portal size in bytes
 * @portal_phys_addr: MC command portal physical address
 * @portal_virt_addr: MC command portal भव address
 * @dpmcp_dev: poपूर्णांकer to the DPMCP device associated with the MC portal.
 *
 * Fields are only meaningful अगर the FSL_MC_IO_ATOMIC_CONTEXT_PORTAL flag is not
 * set:
 * @mutex: Mutex to serialize mc_send_command() calls that use the same MC
 * portal, अगर the fsl_mc_io object was created with the
 * FSL_MC_IO_ATOMIC_CONTEXT_PORTAL flag off. mc_send_command() calls क्रम this
 * fsl_mc_io object must be made only from non-atomic context.
 *
 * Fields are only meaningful अगर the FSL_MC_IO_ATOMIC_CONTEXT_PORTAL flag is
 * set:
 * @spinlock: Spinlock to serialize mc_send_command() calls that use the same MC
 * portal, अगर the fsl_mc_io object was created with the
 * FSL_MC_IO_ATOMIC_CONTEXT_PORTAL flag on. mc_send_command() calls क्रम this
 * fsl_mc_io object can be made from atomic or non-atomic context.
 */
काष्ठा fsl_mc_io अणु
	काष्ठा device *dev;
	u16 flags;
	u32 portal_size;
	phys_addr_t portal_phys_addr;
	व्योम __iomem *portal_virt_addr;
	काष्ठा fsl_mc_device *dpmcp_dev;
	जोड़ अणु
		/*
		 * This field is only meaningful अगर the
		 * FSL_MC_IO_ATOMIC_CONTEXT_PORTAL flag is not set
		 */
		काष्ठा mutex mutex; /* serializes mc_send_command() */

		/*
		 * This field is only meaningful अगर the
		 * FSL_MC_IO_ATOMIC_CONTEXT_PORTAL flag is set
		 */
		raw_spinlock_t spinlock; /* serializes mc_send_command() */
	पूर्ण;
पूर्ण;

पूर्णांक mc_send_command(काष्ठा fsl_mc_io *mc_io, काष्ठा fsl_mc_command *cmd);

#अगर_घोषित CONFIG_FSL_MC_BUS
#घोषणा dev_is_fsl_mc(_dev) ((_dev)->bus == &fsl_mc_bus_type)
#अन्यथा
/* If fsl-mc bus is not present device cannot beदीर्घ to fsl-mc bus */
#घोषणा dev_is_fsl_mc(_dev) (0)
#पूर्ण_अगर

/* Macro to check अगर a device is a container device */
#घोषणा fsl_mc_is_cont_dev(_dev) (to_fsl_mc_device(_dev)->flags & \
	FSL_MC_IS_DPRC)

/* Macro to get the container device of a MC device */
#घोषणा fsl_mc_cont_dev(_dev) (fsl_mc_is_cont_dev(_dev) ? \
	(_dev) : (_dev)->parent)

/*
 * module_fsl_mc_driver() - Helper macro क्रम drivers that करोn't करो
 * anything special in module init/निकास.  This eliminates a lot of
 * boilerplate.  Each module may only use this macro once, and
 * calling it replaces module_init() and module_निकास()
 */
#घोषणा module_fsl_mc_driver(__fsl_mc_driver) \
	module_driver(__fsl_mc_driver, fsl_mc_driver_रेजिस्टर, \
		      fsl_mc_driver_unरेजिस्टर)

/*
 * Macro to aव्योम include chaining to get THIS_MODULE
 */
#घोषणा fsl_mc_driver_रेजिस्टर(drv) \
	__fsl_mc_driver_रेजिस्टर(drv, THIS_MODULE)

पूर्णांक __must_check __fsl_mc_driver_रेजिस्टर(काष्ठा fsl_mc_driver *fsl_mc_driver,
					  काष्ठा module *owner);

व्योम fsl_mc_driver_unरेजिस्टर(काष्ठा fsl_mc_driver *driver);

/**
 * काष्ठा fsl_mc_version
 * @major: Major version number: incremented on API compatibility changes
 * @minor: Minor version number: incremented on API additions (that are
 *		backward compatible); reset when major version is incremented
 * @revision: Internal revision number: incremented on implementation changes
 *		and/or bug fixes that have no impact on API
 */
काष्ठा fsl_mc_version अणु
	u32 major;
	u32 minor;
	u32 revision;
पूर्ण;

काष्ठा fsl_mc_version *fsl_mc_get_version(व्योम);

पूर्णांक __must_check fsl_mc_portal_allocate(काष्ठा fsl_mc_device *mc_dev,
					u16 mc_io_flags,
					काष्ठा fsl_mc_io **new_mc_io);

व्योम fsl_mc_portal_मुक्त(काष्ठा fsl_mc_io *mc_io);

पूर्णांक fsl_mc_portal_reset(काष्ठा fsl_mc_io *mc_io);

पूर्णांक __must_check fsl_mc_object_allocate(काष्ठा fsl_mc_device *mc_dev,
					क्रमागत fsl_mc_pool_type pool_type,
					काष्ठा fsl_mc_device **new_mc_adev);

व्योम fsl_mc_object_मुक्त(काष्ठा fsl_mc_device *mc_adev);

काष्ठा irq_करोमुख्य *fsl_mc_msi_create_irq_करोमुख्य(काष्ठा fwnode_handle *fwnode,
						काष्ठा msi_करोमुख्य_info *info,
						काष्ठा irq_करोमुख्य *parent);

पूर्णांक __must_check fsl_mc_allocate_irqs(काष्ठा fsl_mc_device *mc_dev);

व्योम fsl_mc_मुक्त_irqs(काष्ठा fsl_mc_device *mc_dev);

काष्ठा fsl_mc_device *fsl_mc_get_endpoपूर्णांक(काष्ठा fsl_mc_device *mc_dev);

बाह्य काष्ठा bus_type fsl_mc_bus_type;

बाह्य काष्ठा device_type fsl_mc_bus_dprc_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpni_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpio_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpsw_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpbp_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpcon_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpmcp_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpmac_type;
बाह्य काष्ठा device_type fsl_mc_bus_dprtc_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpseci_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpdmux_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpdcei_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpaiop_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpci_type;
बाह्य काष्ठा device_type fsl_mc_bus_dpdmai_type;

अटल अंतरभूत bool is_fsl_mc_bus_dprc(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dprc_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpni(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpni_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpio(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpio_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpsw(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpsw_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpdmux(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpdmux_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpbp(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpbp_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpcon(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpcon_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpmcp(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpmcp_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpmac(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpmac_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dprtc(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dprtc_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpseci(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpseci_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpdcei(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpdcei_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpaiop(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpaiop_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpci(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpci_type;
पूर्ण

अटल अंतरभूत bool is_fsl_mc_bus_dpdmai(स्थिर काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस mc_dev->dev.type == &fsl_mc_bus_dpdmai_type;
पूर्ण

#घोषणा DPRC_RESET_OPTION_NON_RECURSIVE                0x00000001
पूर्णांक dprc_reset_container(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 पूर्णांक child_container_id,
			 u32 options);

पूर्णांक dprc_scan_container(काष्ठा fsl_mc_device *mc_bus_dev,
			bool alloc_पूर्णांकerrupts);

व्योम dprc_हटाओ_devices(काष्ठा fsl_mc_device *mc_bus_dev,
			 काष्ठा fsl_mc_obj_desc *obj_desc_array,
			 पूर्णांक num_child_objects_in_mc);

पूर्णांक dprc_cleanup(काष्ठा fsl_mc_device *mc_dev);

पूर्णांक dprc_setup(काष्ठा fsl_mc_device *mc_dev);

/**
 * Maximum number of total IRQs that can be pre-allocated क्रम an MC bus'
 * IRQ pool
 */
#घोषणा FSL_MC_IRQ_POOL_MAX_TOTAL_IRQS	256

पूर्णांक fsl_mc_populate_irq_pool(काष्ठा fsl_mc_device *mc_bus_dev,
			     अचिन्हित पूर्णांक irq_count);

व्योम fsl_mc_cleanup_irq_pool(काष्ठा fsl_mc_device *mc_bus_dev);

/*
 * Data Path Buffer Pool (DPBP) API
 * Contains initialization APIs and runसमय control APIs क्रम DPBP
 */

पूर्णांक dpbp_खोलो(काष्ठा fsl_mc_io *mc_io,
	      u32 cmd_flags,
	      पूर्णांक dpbp_id,
	      u16 *token);

पूर्णांक dpbp_बंद(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       u16 token);

पूर्णांक dpbp_enable(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token);

पूर्णांक dpbp_disable(काष्ठा fsl_mc_io *mc_io,
		 u32 cmd_flags,
		 u16 token);

पूर्णांक dpbp_reset(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       u16 token);

/**
 * काष्ठा dpbp_attr - Structure representing DPBP attributes
 * @id:		DPBP object ID
 * @bpid:	Hardware buffer pool ID; should be used as an argument in
 *		acquire/release operations on buffers
 */
काष्ठा dpbp_attr अणु
	पूर्णांक id;
	u16 bpid;
पूर्ण;

पूर्णांक dpbp_get_attributes(काष्ठा fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			काष्ठा dpbp_attr *attr);

/* Data Path Concentrator (DPCON) API
 * Contains initialization APIs and runसमय control APIs क्रम DPCON
 */

/**
 * Use it to disable notअगरications; see dpcon_set_notअगरication()
 */
#घोषणा DPCON_INVALID_DPIO_ID		(पूर्णांक)(-1)

पूर्णांक dpcon_खोलो(काष्ठा fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       पूर्णांक dpcon_id,
	       u16 *token);

पूर्णांक dpcon_बंद(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token);

पूर्णांक dpcon_enable(काष्ठा fsl_mc_io *mc_io,
		 u32 cmd_flags,
		 u16 token);

पूर्णांक dpcon_disable(काष्ठा fsl_mc_io *mc_io,
		  u32 cmd_flags,
		  u16 token);

पूर्णांक dpcon_reset(काष्ठा fsl_mc_io *mc_io,
		u32 cmd_flags,
		u16 token);

/**
 * काष्ठा dpcon_attr - Structure representing DPCON attributes
 * @id: DPCON object ID
 * @qbman_ch_id: Channel ID to be used by dequeue operation
 * @num_priorities: Number of priorities क्रम the DPCON channel (1-8)
 */
काष्ठा dpcon_attr अणु
	पूर्णांक id;
	u16 qbman_ch_id;
	u8 num_priorities;
पूर्ण;

पूर्णांक dpcon_get_attributes(काष्ठा fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 काष्ठा dpcon_attr *attr);

/**
 * काष्ठा dpcon_notअगरication_cfg - Structure representing notअगरication params
 * @dpio_id:	DPIO object ID; must be configured with a notअगरication channel;
 *	to disable notअगरications set it to 'DPCON_INVALID_DPIO_ID';
 * @priority:	Priority selection within the DPIO channel; valid values
 *		are 0-7, depending on the number of priorities in that channel
 * @user_ctx:	User context value provided with each CDAN message
 */
काष्ठा dpcon_notअगरication_cfg अणु
	पूर्णांक dpio_id;
	u8 priority;
	u64 user_ctx;
पूर्ण;

पूर्णांक dpcon_set_notअगरication(काष्ठा fsl_mc_io *mc_io,
			   u32 cmd_flags,
			   u16 token,
			   काष्ठा dpcon_notअगरication_cfg *cfg);

#पूर्ण_अगर /* _FSL_MC_H_ */
