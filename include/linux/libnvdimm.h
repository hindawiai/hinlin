<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * libnvdimm - Non-अस्थिर-memory Devices Subप्रणाली
 *
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#अगर_अघोषित __LIBNVDIMM_H__
#घोषणा __LIBNVDIMM_H__
#समावेश <linux/kernel.h>
#समावेश <linux/sizes.h>
#समावेश <linux/types.h>
#समावेश <linux/uuid.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bपन.स>

काष्ठा badrange_entry अणु
	u64 start;
	u64 length;
	काष्ठा list_head list;
पूर्ण;

काष्ठा badrange अणु
	काष्ठा list_head list;
	spinlock_t lock;
पूर्ण;

क्रमागत अणु
	/* when a dimm supports both PMEM and BLK access a label is required */
	NDD_ALIASING = 0,
	/* unarmed memory devices may not persist ग_लिखोs */
	NDD_UNARMED = 1,
	/* locked memory devices should not be accessed */
	NDD_LOCKED = 2,
	/* memory under security wipes should not be accessed */
	NDD_SECURITY_OVERWRITE = 3,
	/*  tracking whether or not there is a pending device reference */
	NDD_WORK_PENDING = 4,
	/* ignore / filter NSLABEL_FLAG_LOCAL क्रम this DIMM, i.e. no aliasing */
	NDD_NOBLK = 5,
	/* dimm supports namespace labels */
	NDD_LABELING = 6,

	/* need to set a limit somewhere, but yes, this is likely overसमाप्त */
	ND_IOCTL_MAX_BUFLEN = SZ_4M,
	ND_CMD_MAX_ELEM = 5,
	ND_CMD_MAX_ENVELOPE = 256,
	ND_MAX_MAPPINGS = 32,

	/* region flag indicating to direct-map persistent memory by शेष */
	ND_REGION_PAGEMAP = 0,
	/*
	 * Platक्रमm ensures entire CPU store data path is flushed to pmem on
	 * प्रणाली घातer loss.
	 */
	ND_REGION_PERSIST_CACHE = 1,
	/*
	 * Platक्रमm provides mechanisms to स्वतःmatically flush outstanding
	 * ग_लिखो data from memory controler to pmem on प्रणाली घातer loss.
	 * (ADR)
	 */
	ND_REGION_PERSIST_MEMCTRL = 2,

	/* Platक्रमm provides asynchronous flush mechanism */
	ND_REGION_ASYNC = 3,

	/* mark newly adjusted resources as requiring a label update */
	DPA_RESOURCE_ADJUSTED = 1 << 0,
पूर्ण;

काष्ठा nvdimm;
काष्ठा nvdimm_bus_descriptor;
प्रकार पूर्णांक (*ndctl_fn)(काष्ठा nvdimm_bus_descriptor *nd_desc,
		काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक cmd, व्योम *buf,
		अचिन्हित पूर्णांक buf_len, पूर्णांक *cmd_rc);

काष्ठा device_node;
काष्ठा nvdimm_bus_descriptor अणु
	स्थिर काष्ठा attribute_group **attr_groups;
	अचिन्हित दीर्घ cmd_mask;
	अचिन्हित दीर्घ dimm_family_mask;
	अचिन्हित दीर्घ bus_family_mask;
	काष्ठा module *module;
	अक्षर *provider_name;
	काष्ठा device_node *of_node;
	ndctl_fn ndctl;
	पूर्णांक (*flush_probe)(काष्ठा nvdimm_bus_descriptor *nd_desc);
	पूर्णांक (*clear_to_send)(काष्ठा nvdimm_bus_descriptor *nd_desc,
			काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक cmd, व्योम *data);
	स्थिर काष्ठा nvdimm_bus_fw_ops *fw_ops;
पूर्ण;

काष्ठा nd_cmd_desc अणु
	पूर्णांक in_num;
	पूर्णांक out_num;
	u32 in_sizes[ND_CMD_MAX_ELEM];
	पूर्णांक out_sizes[ND_CMD_MAX_ELEM];
पूर्ण;

काष्ठा nd_पूर्णांकerleave_set अणु
	/* v1.1 definition of the पूर्णांकerleave-set-cookie algorithm */
	u64 cookie1;
	/* v1.2 definition of the पूर्णांकerleave-set-cookie algorithm */
	u64 cookie2;
	/* compatibility with initial buggy Linux implementation */
	u64 altcookie;

	guid_t type_guid;
पूर्ण;

काष्ठा nd_mapping_desc अणु
	काष्ठा nvdimm *nvdimm;
	u64 start;
	u64 size;
	पूर्णांक position;
पूर्ण;

काष्ठा nd_region;
काष्ठा nd_region_desc अणु
	काष्ठा resource *res;
	काष्ठा nd_mapping_desc *mapping;
	u16 num_mappings;
	स्थिर काष्ठा attribute_group **attr_groups;
	काष्ठा nd_पूर्णांकerleave_set *nd_set;
	व्योम *provider_data;
	पूर्णांक num_lanes;
	पूर्णांक numa_node;
	पूर्णांक target_node;
	अचिन्हित दीर्घ flags;
	काष्ठा device_node *of_node;
	पूर्णांक (*flush)(काष्ठा nd_region *nd_region, काष्ठा bio *bio);
पूर्ण;

काष्ठा device;
व्योम *devm_nvdimm_memremap(काष्ठा device *dev, resource_माप_प्रकार offset,
		माप_प्रकार size, अचिन्हित दीर्घ flags);
अटल अंतरभूत व्योम __iomem *devm_nvdimm_ioremap(काष्ठा device *dev,
		resource_माप_प्रकार offset, माप_प्रकार size)
अणु
	वापस (व्योम __iomem *) devm_nvdimm_memremap(dev, offset, size, 0);
पूर्ण

काष्ठा nvdimm_bus;
काष्ठा module;
काष्ठा nd_blk_region;
काष्ठा nd_blk_region_desc अणु
	पूर्णांक (*enable)(काष्ठा nvdimm_bus *nvdimm_bus, काष्ठा device *dev);
	पूर्णांक (*करो_io)(काष्ठा nd_blk_region *ndbr, resource_माप_प्रकार dpa,
			व्योम *iobuf, u64 len, पूर्णांक rw);
	काष्ठा nd_region_desc ndr_desc;
पूर्ण;

अटल अंतरभूत काष्ठा nd_blk_region_desc *to_blk_region_desc(
		काष्ठा nd_region_desc *ndr_desc)
अणु
	वापस container_of(ndr_desc, काष्ठा nd_blk_region_desc, ndr_desc);

पूर्ण

/*
 * Note that separate bits क्रम locked + unlocked are defined so that
 * 'flags == 0' corresponds to an error / not-supported state.
 */
क्रमागत nvdimm_security_bits अणु
	NVDIMM_SECURITY_DISABLED,
	NVDIMM_SECURITY_UNLOCKED,
	NVDIMM_SECURITY_LOCKED,
	NVDIMM_SECURITY_FROZEN,
	NVDIMM_SECURITY_OVERWRITE,
पूर्ण;

#घोषणा NVDIMM_PASSPHRASE_LEN		32
#घोषणा NVDIMM_KEY_DESC_LEN		22

काष्ठा nvdimm_key_data अणु
	u8 data[NVDIMM_PASSPHRASE_LEN];
पूर्ण;

क्रमागत nvdimm_passphrase_type अणु
	NVDIMM_USER,
	NVDIMM_MASTER,
पूर्ण;

काष्ठा nvdimm_security_ops अणु
	अचिन्हित दीर्घ (*get_flags)(काष्ठा nvdimm *nvdimm,
			क्रमागत nvdimm_passphrase_type pass_type);
	पूर्णांक (*मुक्तze)(काष्ठा nvdimm *nvdimm);
	पूर्णांक (*change_key)(काष्ठा nvdimm *nvdimm,
			स्थिर काष्ठा nvdimm_key_data *old_data,
			स्थिर काष्ठा nvdimm_key_data *new_data,
			क्रमागत nvdimm_passphrase_type pass_type);
	पूर्णांक (*unlock)(काष्ठा nvdimm *nvdimm,
			स्थिर काष्ठा nvdimm_key_data *key_data);
	पूर्णांक (*disable)(काष्ठा nvdimm *nvdimm,
			स्थिर काष्ठा nvdimm_key_data *key_data);
	पूर्णांक (*erase)(काष्ठा nvdimm *nvdimm,
			स्थिर काष्ठा nvdimm_key_data *key_data,
			क्रमागत nvdimm_passphrase_type pass_type);
	पूर्णांक (*overग_लिखो)(काष्ठा nvdimm *nvdimm,
			स्थिर काष्ठा nvdimm_key_data *key_data);
	पूर्णांक (*query_overग_लिखो)(काष्ठा nvdimm *nvdimm);
पूर्ण;

क्रमागत nvdimm_fwa_state अणु
	NVDIMM_FWA_INVALID,
	NVDIMM_FWA_IDLE,
	NVDIMM_FWA_ARMED,
	NVDIMM_FWA_BUSY,
	NVDIMM_FWA_ARM_OVERFLOW,
पूर्ण;

क्रमागत nvdimm_fwa_trigger अणु
	NVDIMM_FWA_ARM,
	NVDIMM_FWA_DISARM,
पूर्ण;

क्रमागत nvdimm_fwa_capability अणु
	NVDIMM_FWA_CAP_INVALID,
	NVDIMM_FWA_CAP_NONE,
	NVDIMM_FWA_CAP_QUIESCE,
	NVDIMM_FWA_CAP_LIVE,
पूर्ण;

क्रमागत nvdimm_fwa_result अणु
	NVDIMM_FWA_RESULT_INVALID,
	NVDIMM_FWA_RESULT_NONE,
	NVDIMM_FWA_RESULT_SUCCESS,
	NVDIMM_FWA_RESULT_NOTSTAGED,
	NVDIMM_FWA_RESULT_NEEDRESET,
	NVDIMM_FWA_RESULT_FAIL,
पूर्ण;

काष्ठा nvdimm_bus_fw_ops अणु
	क्रमागत nvdimm_fwa_state (*activate_state)
		(काष्ठा nvdimm_bus_descriptor *nd_desc);
	क्रमागत nvdimm_fwa_capability (*capability)
		(काष्ठा nvdimm_bus_descriptor *nd_desc);
	पूर्णांक (*activate)(काष्ठा nvdimm_bus_descriptor *nd_desc);
पूर्ण;

काष्ठा nvdimm_fw_ops अणु
	क्रमागत nvdimm_fwa_state (*activate_state)(काष्ठा nvdimm *nvdimm);
	क्रमागत nvdimm_fwa_result (*activate_result)(काष्ठा nvdimm *nvdimm);
	पूर्णांक (*arm)(काष्ठा nvdimm *nvdimm, क्रमागत nvdimm_fwa_trigger arg);
पूर्ण;

व्योम badrange_init(काष्ठा badrange *badrange);
पूर्णांक badrange_add(काष्ठा badrange *badrange, u64 addr, u64 length);
व्योम badrange_क्रमget(काष्ठा badrange *badrange, phys_addr_t start,
		अचिन्हित पूर्णांक len);
पूर्णांक nvdimm_bus_add_badrange(काष्ठा nvdimm_bus *nvdimm_bus, u64 addr,
		u64 length);
काष्ठा nvdimm_bus *nvdimm_bus_रेजिस्टर(काष्ठा device *parent,
		काष्ठा nvdimm_bus_descriptor *nfit_desc);
व्योम nvdimm_bus_unरेजिस्टर(काष्ठा nvdimm_bus *nvdimm_bus);
काष्ठा nvdimm_bus *to_nvdimm_bus(काष्ठा device *dev);
काष्ठा nvdimm_bus *nvdimm_to_bus(काष्ठा nvdimm *nvdimm);
काष्ठा nvdimm *to_nvdimm(काष्ठा device *dev);
काष्ठा nd_region *to_nd_region(काष्ठा device *dev);
काष्ठा device *nd_region_dev(काष्ठा nd_region *nd_region);
काष्ठा nd_blk_region *to_nd_blk_region(काष्ठा device *dev);
काष्ठा nvdimm_bus_descriptor *to_nd_desc(काष्ठा nvdimm_bus *nvdimm_bus);
काष्ठा device *to_nvdimm_bus_dev(काष्ठा nvdimm_bus *nvdimm_bus);
स्थिर अक्षर *nvdimm_name(काष्ठा nvdimm *nvdimm);
काष्ठा kobject *nvdimm_kobj(काष्ठा nvdimm *nvdimm);
अचिन्हित दीर्घ nvdimm_cmd_mask(काष्ठा nvdimm *nvdimm);
व्योम *nvdimm_provider_data(काष्ठा nvdimm *nvdimm);
काष्ठा nvdimm *__nvdimm_create(काष्ठा nvdimm_bus *nvdimm_bus,
		व्योम *provider_data, स्थिर काष्ठा attribute_group **groups,
		अचिन्हित दीर्घ flags, अचिन्हित दीर्घ cmd_mask, पूर्णांक num_flush,
		काष्ठा resource *flush_wpq, स्थिर अक्षर *dimm_id,
		स्थिर काष्ठा nvdimm_security_ops *sec_ops,
		स्थिर काष्ठा nvdimm_fw_ops *fw_ops);
अटल अंतरभूत काष्ठा nvdimm *nvdimm_create(काष्ठा nvdimm_bus *nvdimm_bus,
		व्योम *provider_data, स्थिर काष्ठा attribute_group **groups,
		अचिन्हित दीर्घ flags, अचिन्हित दीर्घ cmd_mask, पूर्णांक num_flush,
		काष्ठा resource *flush_wpq)
अणु
	वापस __nvdimm_create(nvdimm_bus, provider_data, groups, flags,
			cmd_mask, num_flush, flush_wpq, शून्य, शून्य, शून्य);
पूर्ण

स्थिर काष्ठा nd_cmd_desc *nd_cmd_dimm_desc(पूर्णांक cmd);
स्थिर काष्ठा nd_cmd_desc *nd_cmd_bus_desc(पूर्णांक cmd);
u32 nd_cmd_in_size(काष्ठा nvdimm *nvdimm, पूर्णांक cmd,
		स्थिर काष्ठा nd_cmd_desc *desc, पूर्णांक idx, व्योम *buf);
u32 nd_cmd_out_size(काष्ठा nvdimm *nvdimm, पूर्णांक cmd,
		स्थिर काष्ठा nd_cmd_desc *desc, पूर्णांक idx, स्थिर u32 *in_field,
		स्थिर u32 *out_field, अचिन्हित दीर्घ reमुख्यder);
पूर्णांक nvdimm_bus_check_dimm_count(काष्ठा nvdimm_bus *nvdimm_bus, पूर्णांक dimm_count);
काष्ठा nd_region *nvdimm_pmem_region_create(काष्ठा nvdimm_bus *nvdimm_bus,
		काष्ठा nd_region_desc *ndr_desc);
काष्ठा nd_region *nvdimm_blk_region_create(काष्ठा nvdimm_bus *nvdimm_bus,
		काष्ठा nd_region_desc *ndr_desc);
काष्ठा nd_region *nvdimm_अस्थिर_region_create(काष्ठा nvdimm_bus *nvdimm_bus,
		काष्ठा nd_region_desc *ndr_desc);
व्योम *nd_region_provider_data(काष्ठा nd_region *nd_region);
व्योम *nd_blk_region_provider_data(काष्ठा nd_blk_region *ndbr);
व्योम nd_blk_region_set_provider_data(काष्ठा nd_blk_region *ndbr, व्योम *data);
काष्ठा nvdimm *nd_blk_region_to_dimm(काष्ठा nd_blk_region *ndbr);
अचिन्हित दीर्घ nd_blk_memremap_flags(काष्ठा nd_blk_region *ndbr);
अचिन्हित पूर्णांक nd_region_acquire_lane(काष्ठा nd_region *nd_region);
व्योम nd_region_release_lane(काष्ठा nd_region *nd_region, अचिन्हित पूर्णांक lane);
u64 nd_fletcher64(व्योम *addr, माप_प्रकार len, bool le);
पूर्णांक nvdimm_flush(काष्ठा nd_region *nd_region, काष्ठा bio *bio);
पूर्णांक generic_nvdimm_flush(काष्ठा nd_region *nd_region);
पूर्णांक nvdimm_has_flush(काष्ठा nd_region *nd_region);
पूर्णांक nvdimm_has_cache(काष्ठा nd_region *nd_region);
पूर्णांक nvdimm_in_overग_लिखो(काष्ठा nvdimm *nvdimm);
bool is_nvdimm_sync(काष्ठा nd_region *nd_region);

अटल अंतरभूत पूर्णांक nvdimm_ctl(काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक cmd, व्योम *buf,
		अचिन्हित पूर्णांक buf_len, पूर्णांक *cmd_rc)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = nvdimm_to_bus(nvdimm);
	काष्ठा nvdimm_bus_descriptor *nd_desc = to_nd_desc(nvdimm_bus);

	वापस nd_desc->ndctl(nd_desc, nvdimm, cmd, buf, buf_len, cmd_rc);
पूर्ण

#अगर_घोषित CONFIG_ARCH_HAS_PMEM_API
#घोषणा ARCH_MEMREMAP_PMEM MEMREMAP_WB
व्योम arch_wb_cache_pmem(व्योम *addr, माप_प्रकार size);
व्योम arch_invalidate_pmem(व्योम *addr, माप_प्रकार size);
#अन्यथा
#घोषणा ARCH_MEMREMAP_PMEM MEMREMAP_WT
अटल अंतरभूत व्योम arch_wb_cache_pmem(व्योम *addr, माप_प्रकार size)
अणु
पूर्ण
अटल अंतरभूत व्योम arch_invalidate_pmem(व्योम *addr, माप_प्रकार size)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LIBNVDIMM_H__ */
