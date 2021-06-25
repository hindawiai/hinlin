<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * NVDIMM Firmware Interface Table - NFIT
 *
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#अगर_अघोषित __NFIT_H__
#घोषणा __NFIT_H__
#समावेश <linux/workqueue.h>
#समावेश <linux/libnvdimm.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/types.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/acuuid.h>

/* ACPI 6.1 */
#घोषणा UUID_NFIT_BUS "2f10e7a4-9e91-11e4-89d3-123b93f75cba"

/* https://pmem.io/करोcuments/NVDIMM_DSM_Interface-V1.6.pdf */
#घोषणा UUID_NFIT_DIMM "4309ac30-0d11-11e4-9191-0800200c9a66"
#घोषणा UUID_INTEL_BUS "c7d8acd4-2df8-4b82-9f65-a325335af149"

/* https://github.com/HewlettPackard/hpe-nvm/blob/master/Documentation/ */
#घोषणा UUID_NFIT_DIMM_N_HPE1 "9002c334-acf3-4c0e-9642-a235f0d53bc6"
#घोषणा UUID_NFIT_DIMM_N_HPE2 "5008664b-b758-41a0-a03c-27c2f2d04f7e"

/* https://msdn.microsoft.com/library/winकरोws/hardware/mt604741 */
#घोषणा UUID_NFIT_DIMM_N_MSFT "1ee68b36-d4bd-4a1a-9a16-4f8e53d46e05"

/* http://www.uefi.org/RFIC_LIST (see "Virtual NVDIMM 0x1901") */
#घोषणा UUID_NFIT_DIMM_N_HYPERV "5746c5f2-a9a2-4264-ad0e-e4ddc9e09e80"

#घोषणा ACPI_NFIT_MEM_FAILED_MASK (ACPI_NFIT_MEM_SAVE_FAILED \
		| ACPI_NFIT_MEM_RESTORE_FAILED | ACPI_NFIT_MEM_FLUSH_FAILED \
		| ACPI_NFIT_MEM_NOT_ARMED | ACPI_NFIT_MEM_MAP_FAILED)

#घोषणा NVDIMM_CMD_MAX 31

#घोषणा NVDIMM_STANDARD_CMDMASK \
(1 << ND_CMD_SMART | 1 << ND_CMD_SMART_THRESHOLD | 1 << ND_CMD_DIMM_FLAGS \
 | 1 << ND_CMD_GET_CONFIG_SIZE | 1 << ND_CMD_GET_CONFIG_DATA \
 | 1 << ND_CMD_SET_CONFIG_DATA | 1 << ND_CMD_VENDOR_EFFECT_LOG_SIZE \
 | 1 << ND_CMD_VENDOR_EFFECT_LOG | 1 << ND_CMD_VENDOR)

/*
 * Command numbers that the kernel needs to know about to handle
 * non-शेष DSM revision ids
 */
क्रमागत nvdimm_family_cmds अणु
	NVDIMM_INTEL_LATCH_SHUTDOWN = 10,
	NVDIMM_INTEL_GET_MODES = 11,
	NVDIMM_INTEL_GET_FWINFO = 12,
	NVDIMM_INTEL_START_FWUPDATE = 13,
	NVDIMM_INTEL_SEND_FWUPDATE = 14,
	NVDIMM_INTEL_FINISH_FWUPDATE = 15,
	NVDIMM_INTEL_QUERY_FWUPDATE = 16,
	NVDIMM_INTEL_SET_THRESHOLD = 17,
	NVDIMM_INTEL_INJECT_ERROR = 18,
	NVDIMM_INTEL_GET_SECURITY_STATE = 19,
	NVDIMM_INTEL_SET_PASSPHRASE = 20,
	NVDIMM_INTEL_DISABLE_PASSPHRASE = 21,
	NVDIMM_INTEL_UNLOCK_UNIT = 22,
	NVDIMM_INTEL_FREEZE_LOCK = 23,
	NVDIMM_INTEL_SECURE_ERASE = 24,
	NVDIMM_INTEL_OVERWRITE = 25,
	NVDIMM_INTEL_QUERY_OVERWRITE = 26,
	NVDIMM_INTEL_SET_MASTER_PASSPHRASE = 27,
	NVDIMM_INTEL_MASTER_SECURE_ERASE = 28,
	NVDIMM_INTEL_FW_ACTIVATE_DIMMINFO = 29,
	NVDIMM_INTEL_FW_ACTIVATE_ARM = 30,
पूर्ण;

क्रमागत nvdimm_bus_family_cmds अणु
	NVDIMM_BUS_INTEL_FW_ACTIVATE_BUSINFO = 1,
	NVDIMM_BUS_INTEL_FW_ACTIVATE = 2,
पूर्ण;

#घोषणा NVDIMM_INTEL_SECURITY_CMDMASK \
(1 << NVDIMM_INTEL_GET_SECURITY_STATE | 1 << NVDIMM_INTEL_SET_PASSPHRASE \
| 1 << NVDIMM_INTEL_DISABLE_PASSPHRASE | 1 << NVDIMM_INTEL_UNLOCK_UNIT \
| 1 << NVDIMM_INTEL_FREEZE_LOCK | 1 << NVDIMM_INTEL_SECURE_ERASE \
| 1 << NVDIMM_INTEL_OVERWRITE | 1 << NVDIMM_INTEL_QUERY_OVERWRITE \
| 1 << NVDIMM_INTEL_SET_MASTER_PASSPHRASE \
| 1 << NVDIMM_INTEL_MASTER_SECURE_ERASE)

#घोषणा NVDIMM_INTEL_FW_ACTIVATE_CMDMASK \
(1 << NVDIMM_INTEL_FW_ACTIVATE_DIMMINFO | 1 << NVDIMM_INTEL_FW_ACTIVATE_ARM)

#घोषणा NVDIMM_BUS_INTEL_FW_ACTIVATE_CMDMASK \
(1 << NVDIMM_BUS_INTEL_FW_ACTIVATE_BUSINFO | 1 << NVDIMM_BUS_INTEL_FW_ACTIVATE)

#घोषणा NVDIMM_INTEL_CMDMASK \
(NVDIMM_STANDARD_CMDMASK | 1 << NVDIMM_INTEL_GET_MODES \
 | 1 << NVDIMM_INTEL_GET_FWINFO | 1 << NVDIMM_INTEL_START_FWUPDATE \
 | 1 << NVDIMM_INTEL_SEND_FWUPDATE | 1 << NVDIMM_INTEL_FINISH_FWUPDATE \
 | 1 << NVDIMM_INTEL_QUERY_FWUPDATE | 1 << NVDIMM_INTEL_SET_THRESHOLD \
 | 1 << NVDIMM_INTEL_INJECT_ERROR | 1 << NVDIMM_INTEL_LATCH_SHUTDOWN \
 | NVDIMM_INTEL_SECURITY_CMDMASK | NVDIMM_INTEL_FW_ACTIVATE_CMDMASK)

#घोषणा NVDIMM_INTEL_DENY_CMDMASK \
(NVDIMM_INTEL_SECURITY_CMDMASK | NVDIMM_INTEL_FW_ACTIVATE_CMDMASK)

क्रमागत nfit_uuids अणु
	/* क्रम simplicity alias the uuid index with the family id */
	NFIT_DEV_DIMM = NVDIMM_FAMILY_INTEL,
	NFIT_DEV_DIMM_N_HPE1 = NVDIMM_FAMILY_HPE1,
	NFIT_DEV_DIMM_N_HPE2 = NVDIMM_FAMILY_HPE2,
	NFIT_DEV_DIMM_N_MSFT = NVDIMM_FAMILY_MSFT,
	NFIT_DEV_DIMM_N_HYPERV = NVDIMM_FAMILY_HYPERV,
	/*
	 * to_nfit_bus_uuid() expects to translate bus uuid family ids
	 * to a UUID index using NVDIMM_FAMILY_MAX as an offset
	 */
	NFIT_BUS_INTEL = NVDIMM_FAMILY_MAX + NVDIMM_BUS_FAMILY_INTEL,
	NFIT_SPA_VOLATILE,
	NFIT_SPA_PM,
	NFIT_SPA_DCR,
	NFIT_SPA_BDW,
	NFIT_SPA_VDISK,
	NFIT_SPA_VCD,
	NFIT_SPA_PDISK,
	NFIT_SPA_PCD,
	NFIT_DEV_BUS,
	NFIT_UUID_MAX,
पूर्ण;

/*
 * Region क्रमmat पूर्णांकerface codes are stored with the पूर्णांकerface as the
 * LSB and the function as the MSB.
 */
#घोषणा NFIT_FIC_BYTE cpu_to_le16(0x101) /* byte-addressable energy backed */
#घोषणा NFIT_FIC_BLK cpu_to_le16(0x201) /* block-addressable non-energy backed */
#घोषणा NFIT_FIC_BYTEN cpu_to_le16(0x301) /* byte-addressable non-energy backed */

क्रमागत अणु
	NFIT_BLK_READ_FLUSH = 1,
	NFIT_BLK_DCR_LATCH = 2,
	NFIT_ARS_STATUS_DONE = 0,
	NFIT_ARS_STATUS_BUSY = 1 << 16,
	NFIT_ARS_STATUS_NONE = 2 << 16,
	NFIT_ARS_STATUS_INTR = 3 << 16,
	NFIT_ARS_START_BUSY = 6,
	NFIT_ARS_CAP_NONE = 1,
	NFIT_ARS_F_OVERFLOW = 1,
	NFIT_ARS_TIMEOUT = 90,
पूर्ण;

क्रमागत nfit_root_notअगरiers अणु
	NFIT_NOTIFY_UPDATE = 0x80,
	NFIT_NOTIFY_UC_MEMORY_ERROR = 0x81,
पूर्ण;

क्रमागत nfit_dimm_notअगरiers अणु
	NFIT_NOTIFY_DIMM_HEALTH = 0x81,
पूर्ण;

क्रमागत nfit_ars_state अणु
	ARS_REQ_SHORT,
	ARS_REQ_LONG,
	ARS_FAILED,
पूर्ण;

काष्ठा nfit_spa अणु
	काष्ठा list_head list;
	काष्ठा nd_region *nd_region;
	अचिन्हित दीर्घ ars_state;
	u32 clear_err_unit;
	u32 max_ars;
	काष्ठा acpi_nfit_प्रणाली_address spa[];
पूर्ण;

काष्ठा nfit_dcr अणु
	काष्ठा list_head list;
	काष्ठा acpi_nfit_control_region dcr[];
पूर्ण;

काष्ठा nfit_bdw अणु
	काष्ठा list_head list;
	काष्ठा acpi_nfit_data_region bdw[];
पूर्ण;

काष्ठा nfit_idt अणु
	काष्ठा list_head list;
	काष्ठा acpi_nfit_पूर्णांकerleave idt[];
पूर्ण;

काष्ठा nfit_flush अणु
	काष्ठा list_head list;
	काष्ठा acpi_nfit_flush_address flush[];
पूर्ण;

काष्ठा nfit_memdev अणु
	काष्ठा list_head list;
	काष्ठा acpi_nfit_memory_map memdev[];
पूर्ण;

क्रमागत nfit_mem_flags अणु
	NFIT_MEM_LSR,
	NFIT_MEM_LSW,
	NFIT_MEM_सूचीTY,
	NFIT_MEM_सूचीTY_COUNT,
पूर्ण;

#घोषणा NFIT_DIMM_ID_LEN	22

/* assembled tables क्रम a given dimm/memory-device */
काष्ठा nfit_mem अणु
	काष्ठा nvdimm *nvdimm;
	काष्ठा acpi_nfit_memory_map *memdev_dcr;
	काष्ठा acpi_nfit_memory_map *memdev_pmem;
	काष्ठा acpi_nfit_memory_map *memdev_bdw;
	काष्ठा acpi_nfit_control_region *dcr;
	काष्ठा acpi_nfit_data_region *bdw;
	काष्ठा acpi_nfit_प्रणाली_address *spa_dcr;
	काष्ठा acpi_nfit_प्रणाली_address *spa_bdw;
	काष्ठा acpi_nfit_पूर्णांकerleave *idt_dcr;
	काष्ठा acpi_nfit_पूर्णांकerleave *idt_bdw;
	काष्ठा kernfs_node *flags_attr;
	काष्ठा nfit_flush *nfit_flush;
	काष्ठा list_head list;
	काष्ठा acpi_device *adev;
	काष्ठा acpi_nfit_desc *acpi_desc;
	क्रमागत nvdimm_fwa_state fwa_state;
	क्रमागत nvdimm_fwa_result fwa_result;
	पूर्णांक fwa_count;
	अक्षर id[NFIT_DIMM_ID_LEN+1];
	काष्ठा resource *flush_wpq;
	अचिन्हित दीर्घ dsm_mask;
	अचिन्हित दीर्घ flags;
	u32 dirty_shutकरोwn;
	पूर्णांक family;
पूर्ण;

क्रमागत scrub_flags अणु
	ARS_BUSY,
	ARS_CANCEL,
	ARS_VALID,
	ARS_POLL,
पूर्ण;

काष्ठा acpi_nfit_desc अणु
	काष्ठा nvdimm_bus_descriptor nd_desc;
	काष्ठा acpi_table_header acpi_header;
	काष्ठा mutex init_mutex;
	काष्ठा list_head memdevs;
	काष्ठा list_head flushes;
	काष्ठा list_head dimms;
	काष्ठा list_head spas;
	काष्ठा list_head dcrs;
	काष्ठा list_head bdws;
	काष्ठा list_head idts;
	काष्ठा nvdimm_bus *nvdimm_bus;
	काष्ठा device *dev;
	काष्ठा nd_cmd_ars_status *ars_status;
	काष्ठा nfit_spa *scrub_spa;
	काष्ठा delayed_work dwork;
	काष्ठा list_head list;
	काष्ठा kernfs_node *scrub_count_state;
	अचिन्हित पूर्णांक max_ars;
	अचिन्हित पूर्णांक scrub_count;
	अचिन्हित पूर्णांक scrub_mode;
	अचिन्हित दीर्घ scrub_flags;
	अचिन्हित दीर्घ dimm_cmd_क्रमce_en;
	अचिन्हित दीर्घ bus_cmd_क्रमce_en;
	अचिन्हित दीर्घ bus_dsm_mask;
	अचिन्हित दीर्घ family_dsm_mask[NVDIMM_BUS_FAMILY_MAX + 1];
	अचिन्हित पूर्णांक platक्रमm_cap;
	अचिन्हित पूर्णांक scrub_पंचांगo;
	पूर्णांक (*blk_करो_io)(काष्ठा nd_blk_region *ndbr, resource_माप_प्रकार dpa,
			व्योम *iobuf, u64 len, पूर्णांक rw);
	क्रमागत nvdimm_fwa_state fwa_state;
	क्रमागत nvdimm_fwa_capability fwa_cap;
	पूर्णांक fwa_count;
	bool fwa_noidle;
	bool fwa_nosuspend;
पूर्ण;

क्रमागत scrub_mode अणु
	HW_ERROR_SCRUB_OFF,
	HW_ERROR_SCRUB_ON,
पूर्ण;

क्रमागत nd_blk_mmio_selector अणु
	BDW,
	DCR,
पूर्ण;

काष्ठा nd_blk_addr अणु
	जोड़ अणु
		व्योम __iomem *base;
		व्योम *aperture;
	पूर्ण;
पूर्ण;

काष्ठा nfit_blk अणु
	काष्ठा nfit_blk_mmio अणु
		काष्ठा nd_blk_addr addr;
		u64 size;
		u64 base_offset;
		u32 line_size;
		u32 num_lines;
		u32 table_size;
		काष्ठा acpi_nfit_पूर्णांकerleave *idt;
		काष्ठा acpi_nfit_प्रणाली_address *spa;
	पूर्ण mmio[2];
	काष्ठा nd_region *nd_region;
	u64 bdw_offset; /* post पूर्णांकerleave offset */
	u64 stat_offset;
	u64 cmd_offset;
	u32 dimm_flags;
पूर्ण;

बाह्य काष्ठा list_head acpi_descs;
बाह्य काष्ठा mutex acpi_desc_lock;
पूर्णांक acpi_nfit_ars_rescan(काष्ठा acpi_nfit_desc *acpi_desc,
		क्रमागत nfit_ars_state req_type);

#अगर_घोषित CONFIG_X86_MCE
व्योम nfit_mce_रेजिस्टर(व्योम);
व्योम nfit_mce_unरेजिस्टर(व्योम);
#अन्यथा
अटल अंतरभूत व्योम nfit_mce_रेजिस्टर(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम nfit_mce_unरेजिस्टर(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक nfit_spa_type(काष्ठा acpi_nfit_प्रणाली_address *spa);

अटल अंतरभूत काष्ठा acpi_nfit_memory_map *__to_nfit_memdev(
		काष्ठा nfit_mem *nfit_mem)
अणु
	अगर (nfit_mem->memdev_dcr)
		वापस nfit_mem->memdev_dcr;
	वापस nfit_mem->memdev_pmem;
पूर्ण

अटल अंतरभूत काष्ठा acpi_nfit_desc *to_acpi_desc(
		काष्ठा nvdimm_bus_descriptor *nd_desc)
अणु
	वापस container_of(nd_desc, काष्ठा acpi_nfit_desc, nd_desc);
पूर्ण

#अगर_घोषित CONFIG_PROVE_LOCKING
अटल अंतरभूत व्योम nfit_device_lock(काष्ठा device *dev)
अणु
	device_lock(dev);
	mutex_lock(&dev->lockdep_mutex);
पूर्ण

अटल अंतरभूत व्योम nfit_device_unlock(काष्ठा device *dev)
अणु
	mutex_unlock(&dev->lockdep_mutex);
	device_unlock(dev);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम nfit_device_lock(काष्ठा device *dev)
अणु
	device_lock(dev);
पूर्ण

अटल अंतरभूत व्योम nfit_device_unlock(काष्ठा device *dev)
अणु
	device_unlock(dev);
पूर्ण
#पूर्ण_अगर

स्थिर guid_t *to_nfit_uuid(क्रमागत nfit_uuids id);
पूर्णांक acpi_nfit_init(काष्ठा acpi_nfit_desc *acpi_desc, व्योम *nfit, acpi_size sz);
व्योम acpi_nfit_shutकरोwn(व्योम *data);
व्योम __acpi_nfit_notअगरy(काष्ठा device *dev, acpi_handle handle, u32 event);
व्योम __acpi_nvdimm_notअगरy(काष्ठा device *dev, u32 event);
पूर्णांक acpi_nfit_ctl(काष्ठा nvdimm_bus_descriptor *nd_desc, काष्ठा nvdimm *nvdimm,
		अचिन्हित पूर्णांक cmd, व्योम *buf, अचिन्हित पूर्णांक buf_len, पूर्णांक *cmd_rc);
व्योम acpi_nfit_desc_init(काष्ठा acpi_nfit_desc *acpi_desc, काष्ठा device *dev);
bool पूर्णांकel_fwa_supported(काष्ठा nvdimm_bus *nvdimm_bus);
बाह्य काष्ठा device_attribute dev_attr_firmware_activate_noidle;
#पूर्ण_अगर /* __NFIT_H__ */
