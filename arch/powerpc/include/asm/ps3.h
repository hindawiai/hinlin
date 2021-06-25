<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  PS3 platक्रमm declarations.
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#अगर !defined(_ASM_POWERPC_PS3_H)
#घोषणा _ASM_POWERPC_PS3_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <यंत्र/cell-pmu.h>

जोड़ ps3_firmware_version अणु
	u64 raw;
	काष्ठा अणु
		u16 pad;
		u16 major;
		u16 minor;
		u16 rev;
	पूर्ण;
पूर्ण;

व्योम ps3_get_firmware_version(जोड़ ps3_firmware_version *v);
पूर्णांक ps3_compare_firmware_version(u16 major, u16 minor, u16 rev);

/* 'Other OS' area */

क्रमागत ps3_param_av_multi_out अणु
	PS3_PARAM_AV_MULTI_OUT_NTSC = 0,
	PS3_PARAM_AV_MULTI_OUT_PAL_RGB = 1,
	PS3_PARAM_AV_MULTI_OUT_PAL_YCBCR = 2,
	PS3_PARAM_AV_MULTI_OUT_SECAM = 3,
पूर्ण;

क्रमागत ps3_param_av_multi_out ps3_os_area_get_av_multi_out(व्योम);

बाह्य u64 ps3_os_area_get_rtc_dअगरf(व्योम);
बाह्य व्योम ps3_os_area_set_rtc_dअगरf(u64 rtc_dअगरf);

काष्ठा ps3_os_area_flash_ops अणु
	sमाप_प्रकार (*पढ़ो)(व्योम *buf, माप_प्रकार count, loff_t pos);
	sमाप_प्रकार (*ग_लिखो)(स्थिर व्योम *buf, माप_प्रकार count, loff_t pos);
पूर्ण;

बाह्य व्योम ps3_os_area_flash_रेजिस्टर(स्थिर काष्ठा ps3_os_area_flash_ops *ops);

/* dma routines */

क्रमागत ps3_dma_page_size अणु
	PS3_DMA_4K = 12U,
	PS3_DMA_64K = 16U,
	PS3_DMA_1M = 20U,
	PS3_DMA_16M = 24U,
पूर्ण;

क्रमागत ps3_dma_region_type अणु
	PS3_DMA_OTHER = 0,
	PS3_DMA_INTERNAL = 2,
पूर्ण;

काष्ठा ps3_dma_region_ops;

/**
 * काष्ठा ps3_dma_region - A per device dma state variables काष्ठाure
 * @did: The HV device id.
 * @page_size: The ioc pagesize.
 * @region_type: The HV region type.
 * @bus_addr: The 'translated' bus address of the region.
 * @len: The length in bytes of the region.
 * @offset: The offset from the start of memory of the region.
 * @ioid: The IOID of the device who owns this region
 * @chunk_list: Opaque variable used by the ioc page manager.
 * @region_ops: काष्ठा ps3_dma_region_ops - dma region operations
 */

काष्ठा ps3_dma_region अणु
	काष्ठा ps3_प्रणाली_bus_device *dev;
	/* device variables */
	स्थिर काष्ठा ps3_dma_region_ops *region_ops;
	अचिन्हित अक्षर ioid;
	क्रमागत ps3_dma_page_size page_size;
	क्रमागत ps3_dma_region_type region_type;
	अचिन्हित दीर्घ len;
	अचिन्हित दीर्घ offset;

	/* driver variables  (set by ps3_dma_region_create) */
	अचिन्हित दीर्घ bus_addr;
	काष्ठा अणु
		spinlock_t lock;
		काष्ठा list_head head;
	पूर्ण chunk_list;
पूर्ण;

काष्ठा ps3_dma_region_ops अणु
	पूर्णांक (*create)(काष्ठा ps3_dma_region *);
	पूर्णांक (*मुक्त)(काष्ठा ps3_dma_region *);
	पूर्णांक (*map)(काष्ठा ps3_dma_region *,
		   अचिन्हित दीर्घ virt_addr,
		   अचिन्हित दीर्घ len,
		   dma_addr_t *bus_addr,
		   u64 iopte_pp);
	पूर्णांक (*unmap)(काष्ठा ps3_dma_region *,
		     dma_addr_t bus_addr,
		     अचिन्हित दीर्घ len);
पूर्ण;
/**
 * काष्ठा ps3_dma_region_init - Helper to initialize काष्ठाure variables
 *
 * Helper to properly initialize variables prior to calling
 * ps3_प्रणाली_bus_device_रेजिस्टर.
 */

काष्ठा ps3_प्रणाली_bus_device;

पूर्णांक ps3_dma_region_init(काष्ठा ps3_प्रणाली_bus_device *dev,
	काष्ठा ps3_dma_region *r, क्रमागत ps3_dma_page_size page_size,
	क्रमागत ps3_dma_region_type region_type, व्योम *addr, अचिन्हित दीर्घ len);
पूर्णांक ps3_dma_region_create(काष्ठा ps3_dma_region *r);
पूर्णांक ps3_dma_region_मुक्त(काष्ठा ps3_dma_region *r);
पूर्णांक ps3_dma_map(काष्ठा ps3_dma_region *r, अचिन्हित दीर्घ virt_addr,
	अचिन्हित दीर्घ len, dma_addr_t *bus_addr,
	u64 iopte_pp);
पूर्णांक ps3_dma_unmap(काष्ठा ps3_dma_region *r, dma_addr_t bus_addr,
	अचिन्हित दीर्घ len);

/* mmio routines */

क्रमागत ps3_mmio_page_size अणु
	PS3_MMIO_4K = 12U,
	PS3_MMIO_64K = 16U
पूर्ण;

काष्ठा ps3_mmio_region_ops;
/**
 * काष्ठा ps3_mmio_region - a per device mmio state variables काष्ठाure
 *
 * Current प्रणालीs can be supported with a single region per device.
 */

काष्ठा ps3_mmio_region अणु
	काष्ठा ps3_प्रणाली_bus_device *dev;
	स्थिर काष्ठा ps3_mmio_region_ops *mmio_ops;
	अचिन्हित दीर्घ bus_addr;
	अचिन्हित दीर्घ len;
	क्रमागत ps3_mmio_page_size page_size;
	अचिन्हित दीर्घ lpar_addr;
पूर्ण;

काष्ठा ps3_mmio_region_ops अणु
	पूर्णांक (*create)(काष्ठा ps3_mmio_region *);
	पूर्णांक (*मुक्त)(काष्ठा ps3_mmio_region *);
पूर्ण;
/**
 * काष्ठा ps3_mmio_region_init - Helper to initialize काष्ठाure variables
 *
 * Helper to properly initialize variables prior to calling
 * ps3_प्रणाली_bus_device_रेजिस्टर.
 */

पूर्णांक ps3_mmio_region_init(काष्ठा ps3_प्रणाली_bus_device *dev,
	काष्ठा ps3_mmio_region *r, अचिन्हित दीर्घ bus_addr, अचिन्हित दीर्घ len,
	क्रमागत ps3_mmio_page_size page_size);
पूर्णांक ps3_mmio_region_create(काष्ठा ps3_mmio_region *r);
पूर्णांक ps3_मुक्त_mmio_region(काष्ठा ps3_mmio_region *r);
अचिन्हित दीर्घ ps3_mm_phys_to_lpar(अचिन्हित दीर्घ phys_addr);

/* inrerrupt routines */

क्रमागत ps3_cpu_binding अणु
	PS3_BINDING_CPU_ANY = -1,
	PS3_BINDING_CPU_0 = 0,
	PS3_BINDING_CPU_1 = 1,
पूर्ण;

पूर्णांक ps3_irq_plug_setup(क्रमागत ps3_cpu_binding cpu, अचिन्हित दीर्घ outlet,
	अचिन्हित पूर्णांक *virq);
पूर्णांक ps3_irq_plug_destroy(अचिन्हित पूर्णांक virq);
पूर्णांक ps3_event_receive_port_setup(क्रमागत ps3_cpu_binding cpu, अचिन्हित पूर्णांक *virq);
पूर्णांक ps3_event_receive_port_destroy(अचिन्हित पूर्णांक virq);
पूर्णांक ps3_send_event_locally(अचिन्हित पूर्णांक virq);

पूर्णांक ps3_io_irq_setup(क्रमागत ps3_cpu_binding cpu, अचिन्हित पूर्णांक पूर्णांकerrupt_id,
	अचिन्हित पूर्णांक *virq);
पूर्णांक ps3_io_irq_destroy(अचिन्हित पूर्णांक virq);
पूर्णांक ps3_vuart_irq_setup(क्रमागत ps3_cpu_binding cpu, व्योम* virt_addr_bmp,
	अचिन्हित पूर्णांक *virq);
पूर्णांक ps3_vuart_irq_destroy(अचिन्हित पूर्णांक virq);
पूर्णांक ps3_spe_irq_setup(क्रमागत ps3_cpu_binding cpu, अचिन्हित दीर्घ spe_id,
	अचिन्हित पूर्णांक class, अचिन्हित पूर्णांक *virq);
पूर्णांक ps3_spe_irq_destroy(अचिन्हित पूर्णांक virq);

पूर्णांक ps3_sb_event_receive_port_setup(काष्ठा ps3_प्रणाली_bus_device *dev,
	क्रमागत ps3_cpu_binding cpu, अचिन्हित पूर्णांक *virq);
पूर्णांक ps3_sb_event_receive_port_destroy(काष्ठा ps3_प्रणाली_bus_device *dev,
	अचिन्हित पूर्णांक virq);

/* lv1 result codes */

क्रमागत lv1_result अणु
	LV1_SUCCESS                     = 0,
	/* not used                       -1 */
	LV1_RESOURCE_SHORTAGE           = -2,
	LV1_NO_PRIVILEGE                = -3,
	LV1_DENIED_BY_POLICY            = -4,
	LV1_ACCESS_VIOLATION            = -5,
	LV1_NO_ENTRY                    = -6,
	LV1_DUPLICATE_ENTRY             = -7,
	LV1_TYPE_MISMATCH               = -8,
	LV1_BUSY                        = -9,
	LV1_EMPTY                       = -10,
	LV1_WRONG_STATE                 = -11,
	/* not used                       -12 */
	LV1_NO_MATCH                    = -13,
	LV1_ALREADY_CONNECTED           = -14,
	LV1_UNSUPPORTED_PARAMETER_VALUE = -15,
	LV1_CONDITION_NOT_SATISFIED     = -16,
	LV1_ILLEGAL_PARAMETER_VALUE     = -17,
	LV1_BAD_OPTION                  = -18,
	LV1_IMPLEMENTATION_LIMITATION   = -19,
	LV1_NOT_IMPLEMENTED             = -20,
	LV1_INVALID_CLASS_ID            = -21,
	LV1_CONSTRAINT_NOT_SATISFIED    = -22,
	LV1_ALIGNMENT_ERROR             = -23,
	LV1_HARDWARE_ERROR              = -24,
	LV1_INVALID_DATA_FORMAT         = -25,
	LV1_INVALID_OPERATION           = -26,
	LV1_INTERNAL_ERROR              = -32768,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर* ps3_result(पूर्णांक result)
अणु
#अगर defined(DEBUG) || defined(PS3_VERBOSE_RESULT)
	चयन (result) अणु
	हाल LV1_SUCCESS:
		वापस "LV1_SUCCESS (0)";
	हाल -1:
		वापस "** unknown result ** (-1)";
	हाल LV1_RESOURCE_SHORTAGE:
		वापस "LV1_RESOURCE_SHORTAGE (-2)";
	हाल LV1_NO_PRIVILEGE:
		वापस "LV1_NO_PRIVILEGE (-3)";
	हाल LV1_DENIED_BY_POLICY:
		वापस "LV1_DENIED_BY_POLICY (-4)";
	हाल LV1_ACCESS_VIOLATION:
		वापस "LV1_ACCESS_VIOLATION (-5)";
	हाल LV1_NO_ENTRY:
		वापस "LV1_NO_ENTRY (-6)";
	हाल LV1_DUPLICATE_ENTRY:
		वापस "LV1_DUPLICATE_ENTRY (-7)";
	हाल LV1_TYPE_MISMATCH:
		वापस "LV1_TYPE_MISMATCH (-8)";
	हाल LV1_BUSY:
		वापस "LV1_BUSY (-9)";
	हाल LV1_EMPTY:
		वापस "LV1_EMPTY (-10)";
	हाल LV1_WRONG_STATE:
		वापस "LV1_WRONG_STATE (-11)";
	हाल -12:
		वापस "** unknown result ** (-12)";
	हाल LV1_NO_MATCH:
		वापस "LV1_NO_MATCH (-13)";
	हाल LV1_ALREADY_CONNECTED:
		वापस "LV1_ALREADY_CONNECTED (-14)";
	हाल LV1_UNSUPPORTED_PARAMETER_VALUE:
		वापस "LV1_UNSUPPORTED_PARAMETER_VALUE (-15)";
	हाल LV1_CONDITION_NOT_SATISFIED:
		वापस "LV1_CONDITION_NOT_SATISFIED (-16)";
	हाल LV1_ILLEGAL_PARAMETER_VALUE:
		वापस "LV1_ILLEGAL_PARAMETER_VALUE (-17)";
	हाल LV1_BAD_OPTION:
		वापस "LV1_BAD_OPTION (-18)";
	हाल LV1_IMPLEMENTATION_LIMITATION:
		वापस "LV1_IMPLEMENTATION_LIMITATION (-19)";
	हाल LV1_NOT_IMPLEMENTED:
		वापस "LV1_NOT_IMPLEMENTED (-20)";
	हाल LV1_INVALID_CLASS_ID:
		वापस "LV1_INVALID_CLASS_ID (-21)";
	हाल LV1_CONSTRAINT_NOT_SATISFIED:
		वापस "LV1_CONSTRAINT_NOT_SATISFIED (-22)";
	हाल LV1_ALIGNMENT_ERROR:
		वापस "LV1_ALIGNMENT_ERROR (-23)";
	हाल LV1_HARDWARE_ERROR:
		वापस "LV1_HARDWARE_ERROR (-24)";
	हाल LV1_INVALID_DATA_FORMAT:
		वापस "LV1_INVALID_DATA_FORMAT (-25)";
	हाल LV1_INVALID_OPERATION:
		वापस "LV1_INVALID_OPERATION (-26)";
	हाल LV1_INTERNAL_ERROR:
		वापस "LV1_INTERNAL_ERROR (-32768)";
	शेष:
		BUG();
		वापस "** unknown result **";
	पूर्ण;
#अन्यथा
	वापस "";
#पूर्ण_अगर
पूर्ण

/* प्रणाली bus routines */

क्रमागत ps3_match_id अणु
	PS3_MATCH_ID_EHCI		= 1,
	PS3_MATCH_ID_OHCI		= 2,
	PS3_MATCH_ID_GELIC		= 3,
	PS3_MATCH_ID_AV_SETTINGS	= 4,
	PS3_MATCH_ID_SYSTEM_MANAGER	= 5,
	PS3_MATCH_ID_STOR_DISK		= 6,
	PS3_MATCH_ID_STOR_ROM		= 7,
	PS3_MATCH_ID_STOR_FLASH		= 8,
	PS3_MATCH_ID_SOUND		= 9,
	PS3_MATCH_ID_GPU		= 10,
	PS3_MATCH_ID_LPM		= 11,
पूर्ण;

क्रमागत ps3_match_sub_id अणु
	PS3_MATCH_SUB_ID_GPU_FB		= 1,
	PS3_MATCH_SUB_ID_GPU_RAMDISK	= 2,
पूर्ण;

#घोषणा PS3_MODULE_ALIAS_EHCI		"ps3:1:0"
#घोषणा PS3_MODULE_ALIAS_OHCI		"ps3:2:0"
#घोषणा PS3_MODULE_ALIAS_GELIC		"ps3:3:0"
#घोषणा PS3_MODULE_ALIAS_AV_SETTINGS	"ps3:4:0"
#घोषणा PS3_MODULE_ALIAS_SYSTEM_MANAGER	"ps3:5:0"
#घोषणा PS3_MODULE_ALIAS_STOR_DISK	"ps3:6:0"
#घोषणा PS3_MODULE_ALIAS_STOR_ROM	"ps3:7:0"
#घोषणा PS3_MODULE_ALIAS_STOR_FLASH	"ps3:8:0"
#घोषणा PS3_MODULE_ALIAS_SOUND		"ps3:9:0"
#घोषणा PS3_MODULE_ALIAS_GPU_FB		"ps3:10:1"
#घोषणा PS3_MODULE_ALIAS_GPU_RAMDISK	"ps3:10:2"
#घोषणा PS3_MODULE_ALIAS_LPM		"ps3:11:0"

क्रमागत ps3_प्रणाली_bus_device_type अणु
	PS3_DEVICE_TYPE_IOC0 = 1,
	PS3_DEVICE_TYPE_SB,
	PS3_DEVICE_TYPE_VUART,
	PS3_DEVICE_TYPE_LPM,
पूर्ण;

/**
 * काष्ठा ps3_प्रणाली_bus_device - a device on the प्रणाली bus
 */

काष्ठा ps3_प्रणाली_bus_device अणु
	क्रमागत ps3_match_id match_id;
	क्रमागत ps3_match_sub_id match_sub_id;
	क्रमागत ps3_प्रणाली_bus_device_type dev_type;

	u64 bus_id;                       /* SB */
	u64 dev_id;                       /* SB */
	अचिन्हित पूर्णांक पूर्णांकerrupt_id;        /* SB */
	काष्ठा ps3_dma_region *d_region;  /* SB, IOC0 */
	काष्ठा ps3_mmio_region *m_region; /* SB, IOC0*/
	अचिन्हित पूर्णांक port_number;         /* VUART */
	काष्ठा अणु                          /* LPM */
		u64 node_id;
		u64 pu_id;
		u64 rights;
	पूर्ण lpm;

/*	काष्ठा iommu_table *iommu_table; -- रुकोing क्रम BenH's cleanups */
	काष्ठा device core;
	व्योम *driver_priv; /* निजी driver variables */
पूर्ण;

पूर्णांक ps3_खोलो_hv_device(काष्ठा ps3_प्रणाली_bus_device *dev);
पूर्णांक ps3_बंद_hv_device(काष्ठा ps3_प्रणाली_bus_device *dev);

/**
 * काष्ठा ps3_प्रणाली_bus_driver - a driver क्रम a device on the प्रणाली bus
 */

काष्ठा ps3_प्रणाली_bus_driver अणु
	क्रमागत ps3_match_id match_id;
	क्रमागत ps3_match_sub_id match_sub_id;
	काष्ठा device_driver core;
	पूर्णांक (*probe)(काष्ठा ps3_प्रणाली_bus_device *);
	व्योम (*हटाओ)(काष्ठा ps3_प्रणाली_bus_device *);
	व्योम (*shutकरोwn)(काष्ठा ps3_प्रणाली_bus_device *);
/*	पूर्णांक (*suspend)(काष्ठा ps3_प्रणाली_bus_device *, pm_message_t); */
/*	पूर्णांक (*resume)(काष्ठा ps3_प्रणाली_bus_device *); */
पूर्ण;

पूर्णांक ps3_प्रणाली_bus_device_रेजिस्टर(काष्ठा ps3_प्रणाली_bus_device *dev);
पूर्णांक ps3_प्रणाली_bus_driver_रेजिस्टर(काष्ठा ps3_प्रणाली_bus_driver *drv);
व्योम ps3_प्रणाली_bus_driver_unरेजिस्टर(काष्ठा ps3_प्रणाली_bus_driver *drv);

अटल अंतरभूत काष्ठा ps3_प्रणाली_bus_driver *ps3_drv_to_प्रणाली_bus_drv(
	काष्ठा device_driver *_drv)
अणु
	वापस container_of(_drv, काष्ठा ps3_प्रणाली_bus_driver, core);
पूर्ण
अटल अंतरभूत काष्ठा ps3_प्रणाली_bus_device *ps3_dev_to_प्रणाली_bus_dev(
	काष्ठा device *_dev)
अणु
	वापस container_of(_dev, काष्ठा ps3_प्रणाली_bus_device, core);
पूर्ण
अटल अंतरभूत काष्ठा ps3_प्रणाली_bus_driver *
	ps3_प्रणाली_bus_dev_to_प्रणाली_bus_drv(काष्ठा ps3_प्रणाली_bus_device *_dev)
अणु
	BUG_ON(!_dev);
	BUG_ON(!_dev->core.driver);
	वापस ps3_drv_to_प्रणाली_bus_drv(_dev->core.driver);
पूर्ण

/**
 * ps3_प्रणाली_bus_set_drvdata -
 * @dev: device काष्ठाure
 * @data: Data to set
 */

अटल अंतरभूत व्योम ps3_प्रणाली_bus_set_drvdata(
	काष्ठा ps3_प्रणाली_bus_device *dev, व्योम *data)
अणु
	dev_set_drvdata(&dev->core, data);
पूर्ण
अटल अंतरभूत व्योम *ps3_प्रणाली_bus_get_drvdata(
	काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	वापस dev_get_drvdata(&dev->core);
पूर्ण

/* These two need global scope क्रम get_arch_dma_ops(). */

बाह्य काष्ठा bus_type ps3_प्रणाली_bus_type;

/* प्रणाली manager */

काष्ठा ps3_sys_manager_ops अणु
	काष्ठा ps3_प्रणाली_bus_device *dev;
	व्योम (*घातer_off)(काष्ठा ps3_प्रणाली_bus_device *dev);
	व्योम (*restart)(काष्ठा ps3_प्रणाली_bus_device *dev);
पूर्ण;

व्योम ps3_sys_manager_रेजिस्टर_ops(स्थिर काष्ठा ps3_sys_manager_ops *ops);
व्योम __noवापस ps3_sys_manager_घातer_off(व्योम);
व्योम __noवापस ps3_sys_manager_restart(व्योम);
व्योम __noवापस ps3_sys_manager_halt(व्योम);
पूर्णांक ps3_sys_manager_get_wol(व्योम);
व्योम ps3_sys_manager_set_wol(पूर्णांक state);

काष्ठा ps3_pपुनः_स्मृति अणु
    स्थिर अक्षर *name;
    व्योम *address;
    अचिन्हित दीर्घ size;
    अचिन्हित दीर्घ align;
पूर्ण;

बाह्य काष्ठा ps3_pपुनः_स्मृति ps3fb_videomemory;
बाह्य काष्ठा ps3_pपुनः_स्मृति ps3flash_bounce_buffer;

/* logical perक्रमmance monitor */

/**
 * क्रमागत ps3_lpm_rights - Rigths granted by the प्रणाली policy module.
 *
 * @PS3_LPM_RIGHTS_USE_LPM: The right to use the lpm.
 * @PS3_LPM_RIGHTS_USE_TB: The right to use the पूर्णांकernal trace buffer.
 */

क्रमागत ps3_lpm_rights अणु
	PS3_LPM_RIGHTS_USE_LPM = 0x001,
	PS3_LPM_RIGHTS_USE_TB = 0x100,
पूर्ण;

/**
 * क्रमागत ps3_lpm_tb_type - Type of trace buffer lv1 should use.
 *
 * @PS3_LPM_TB_TYPE_NONE: Do not use a trace buffer.
 * @PS3_LPM_RIGHTS_USE_TB: Use the lv1 पूर्णांकernal trace buffer.  Must have
 *  rights @PS3_LPM_RIGHTS_USE_TB.
 */

क्रमागत ps3_lpm_tb_type अणु
	PS3_LPM_TB_TYPE_NONE = 0,
	PS3_LPM_TB_TYPE_INTERNAL = 1,
पूर्ण;

पूर्णांक ps3_lpm_खोलो(क्रमागत ps3_lpm_tb_type tb_type, व्योम *tb_cache,
	u64 tb_cache_size);
पूर्णांक ps3_lpm_बंद(व्योम);
पूर्णांक ps3_lpm_copy_tb(अचिन्हित दीर्घ offset, व्योम *buf, अचिन्हित दीर्घ count,
	अचिन्हित दीर्घ *bytes_copied);
पूर्णांक ps3_lpm_copy_tb_to_user(अचिन्हित दीर्घ offset, व्योम __user *buf,
	अचिन्हित दीर्घ count, अचिन्हित दीर्घ *bytes_copied);
व्योम ps3_set_bookmark(u64 bookmark);
व्योम ps3_set_pm_bookmark(u64 tag, u64 incident, u64 th_id);
पूर्णांक ps3_set_संकेत(u64 rtas_संकेत_group, u8 संकेत_bit, u16 sub_unit,
	u8 bus_word);

u32 ps3_पढ़ो_phys_ctr(u32 cpu, u32 phys_ctr);
व्योम ps3_ग_लिखो_phys_ctr(u32 cpu, u32 phys_ctr, u32 val);
u32 ps3_पढ़ो_ctr(u32 cpu, u32 ctr);
व्योम ps3_ग_लिखो_ctr(u32 cpu, u32 ctr, u32 val);

u32 ps3_पढ़ो_pm07_control(u32 cpu, u32 ctr);
व्योम ps3_ग_लिखो_pm07_control(u32 cpu, u32 ctr, u32 val);
u32 ps3_पढ़ो_pm(u32 cpu, क्रमागत pm_reg_name reg);
व्योम ps3_ग_लिखो_pm(u32 cpu, क्रमागत pm_reg_name reg, u32 val);

u32 ps3_get_ctr_size(u32 cpu, u32 phys_ctr);
व्योम ps3_set_ctr_size(u32 cpu, u32 phys_ctr, u32 ctr_size);

व्योम ps3_enable_pm(u32 cpu);
व्योम ps3_disable_pm(u32 cpu);
व्योम ps3_enable_pm_पूर्णांकerrupts(u32 cpu, u32 thपढ़ो, u32 mask);
व्योम ps3_disable_pm_पूर्णांकerrupts(u32 cpu);

u32 ps3_get_and_clear_pm_पूर्णांकerrupts(u32 cpu);
व्योम ps3_sync_irq(पूर्णांक node);
u32 ps3_get_hw_thपढ़ो_id(पूर्णांक cpu);
u64 ps3_get_spe_id(व्योम *arg);

व्योम ps3_early_mm_init(व्योम);

#पूर्ण_अगर
