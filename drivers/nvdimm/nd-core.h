<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#अगर_अघोषित __ND_CORE_H__
#घोषणा __ND_CORE_H__
#समावेश <linux/libnvdimm.h>
#समावेश <linux/device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/mutex.h>
#समावेश <linux/nd.h>
#समावेश "nd.h"

बाह्य काष्ठा list_head nvdimm_bus_list;
बाह्य काष्ठा mutex nvdimm_bus_list_mutex;
बाह्य पूर्णांक nvdimm_major;
बाह्य काष्ठा workqueue_काष्ठा *nvdimm_wq;

काष्ठा nvdimm_bus अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc;
	रुको_queue_head_t रुको;
	काष्ठा list_head list;
	काष्ठा device dev;
	पूर्णांक id, probe_active;
	atomic_t ioctl_active;
	काष्ठा list_head mapping_list;
	काष्ठा mutex reconfig_mutex;
	काष्ठा badrange badrange;
पूर्ण;

काष्ठा nvdimm अणु
	अचिन्हित दीर्घ flags;
	व्योम *provider_data;
	अचिन्हित दीर्घ cmd_mask;
	काष्ठा device dev;
	atomic_t busy;
	पूर्णांक id, num_flush;
	काष्ठा resource *flush_wpq;
	स्थिर अक्षर *dimm_id;
	काष्ठा अणु
		स्थिर काष्ठा nvdimm_security_ops *ops;
		अचिन्हित दीर्घ flags;
		अचिन्हित दीर्घ ext_flags;
		अचिन्हित पूर्णांक overग_लिखो_पंचांगo;
		काष्ठा kernfs_node *overग_लिखो_state;
	पूर्ण sec;
	काष्ठा delayed_work dwork;
	स्थिर काष्ठा nvdimm_fw_ops *fw_ops;
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ nvdimm_security_flags(
		काष्ठा nvdimm *nvdimm, क्रमागत nvdimm_passphrase_type ptype)
अणु
	u64 flags;
	स्थिर u64 state_flags = 1UL << NVDIMM_SECURITY_DISABLED
		| 1UL << NVDIMM_SECURITY_LOCKED
		| 1UL << NVDIMM_SECURITY_UNLOCKED
		| 1UL << NVDIMM_SECURITY_OVERWRITE;

	अगर (!nvdimm->sec.ops)
		वापस 0;

	flags = nvdimm->sec.ops->get_flags(nvdimm, ptype);
	/* disabled, locked, unlocked, and overग_लिखो are mutually exclusive */
	dev_WARN_ONCE(&nvdimm->dev, hweight64(flags & state_flags) > 1,
			"reported invalid security state: %#llx\n",
			(अचिन्हित दीर्घ दीर्घ) flags);
	वापस flags;
पूर्ण
पूर्णांक nvdimm_security_मुक्तze(काष्ठा nvdimm *nvdimm);
#अगर IS_ENABLED(CONFIG_NVDIMM_KEYS)
sमाप_प्रकार nvdimm_security_store(काष्ठा device *dev, स्थिर अक्षर *buf, माप_प्रकार len);
व्योम nvdimm_security_overग_लिखो_query(काष्ठा work_काष्ठा *work);
#अन्यथा
अटल अंतरभूत sमाप_प्रकार nvdimm_security_store(काष्ठा device *dev,
		स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत व्योम nvdimm_security_overग_लिखो_query(काष्ठा work_काष्ठा *work)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * काष्ठा blk_alloc_info - tracking info क्रम BLK dpa scanning
 * @nd_mapping: blk region mapping boundaries
 * @available: decremented in alias_dpa_busy as aliased PMEM is scanned
 * @busy: decremented in blk_dpa_busy to account क्रम ranges alपढ़ोy
 * 	  handled by alias_dpa_busy
 * @res: alias_dpa_busy पूर्णांकerprets this a मुक्त space range that needs to
 * 	 be truncated to the valid BLK allocation starting DPA, blk_dpa_busy
 * 	 treats it as a busy range that needs the aliased PMEM ranges
 * 	 truncated.
 */
काष्ठा blk_alloc_info अणु
	काष्ठा nd_mapping *nd_mapping;
	resource_माप_प्रकार available, busy;
	काष्ठा resource *res;
पूर्ण;

bool is_nvdimm(काष्ठा device *dev);
bool is_nd_pmem(काष्ठा device *dev);
bool is_nd_अस्थिर(काष्ठा device *dev);
bool is_nd_blk(काष्ठा device *dev);
अटल अंतरभूत bool is_nd_region(काष्ठा device *dev)
अणु
	वापस is_nd_pmem(dev) || is_nd_blk(dev) || is_nd_अस्थिर(dev);
पूर्ण
अटल अंतरभूत bool is_memory(काष्ठा device *dev)
अणु
	वापस is_nd_pmem(dev) || is_nd_अस्थिर(dev);
पूर्ण
काष्ठा nvdimm_bus *walk_to_nvdimm_bus(काष्ठा device *nd_dev);
पूर्णांक __init nvdimm_bus_init(व्योम);
व्योम nvdimm_bus_निकास(व्योम);
व्योम nvdimm_devs_निकास(व्योम);
काष्ठा nd_region;
व्योम nd_region_advance_seeds(काष्ठा nd_region *nd_region, काष्ठा device *dev);
व्योम nd_region_create_ns_seed(काष्ठा nd_region *nd_region);
व्योम nd_region_create_btt_seed(काष्ठा nd_region *nd_region);
व्योम nd_region_create_pfn_seed(काष्ठा nd_region *nd_region);
व्योम nd_region_create_dax_seed(काष्ठा nd_region *nd_region);
पूर्णांक nvdimm_bus_create_ndctl(काष्ठा nvdimm_bus *nvdimm_bus);
व्योम nvdimm_bus_destroy_ndctl(काष्ठा nvdimm_bus *nvdimm_bus);
व्योम nd_synchronize(व्योम);
व्योम __nd_device_रेजिस्टर(काष्ठा device *dev);
काष्ठा nd_label_id;
अक्षर *nd_label_gen_id(काष्ठा nd_label_id *label_id, u8 *uuid, u32 flags);
bool nd_is_uuid_unique(काष्ठा device *dev, u8 *uuid);
काष्ठा nd_region;
काष्ठा nvdimm_drvdata;
काष्ठा nd_mapping;
व्योम nd_mapping_मुक्त_labels(काष्ठा nd_mapping *nd_mapping);

पूर्णांक __reserve_मुक्त_pmem(काष्ठा device *dev, व्योम *data);
व्योम release_मुक्त_pmem(काष्ठा nvdimm_bus *nvdimm_bus,
		       काष्ठा nd_mapping *nd_mapping);

resource_माप_प्रकार nd_pmem_max_contiguous_dpa(काष्ठा nd_region *nd_region,
					   काष्ठा nd_mapping *nd_mapping);
resource_माप_प्रकार nd_region_allocatable_dpa(काष्ठा nd_region *nd_region);
resource_माप_प्रकार nd_pmem_available_dpa(काष्ठा nd_region *nd_region,
		काष्ठा nd_mapping *nd_mapping, resource_माप_प्रकार *overlap);
resource_माप_प्रकार nd_blk_available_dpa(काष्ठा nd_region *nd_region);
resource_माप_प्रकार nd_region_available_dpa(काष्ठा nd_region *nd_region);
पूर्णांक nd_region_conflict(काष्ठा nd_region *nd_region, resource_माप_प्रकार start,
		resource_माप_प्रकार size);
resource_माप_प्रकार nvdimm_allocated_dpa(काष्ठा nvdimm_drvdata *ndd,
		काष्ठा nd_label_id *label_id);
पूर्णांक alias_dpa_busy(काष्ठा device *dev, व्योम *data);
काष्ठा resource *nsblk_add_resource(काष्ठा nd_region *nd_region,
		काष्ठा nvdimm_drvdata *ndd, काष्ठा nd_namespace_blk *nsblk,
		resource_माप_प्रकार start);
पूर्णांक nvdimm_num_label_slots(काष्ठा nvdimm_drvdata *ndd);
व्योम get_ndd(काष्ठा nvdimm_drvdata *ndd);
resource_माप_प्रकार __nvdimm_namespace_capacity(काष्ठा nd_namespace_common *ndns);
व्योम nd_detach_ndns(काष्ठा device *dev, काष्ठा nd_namespace_common **_ndns);
व्योम __nd_detach_ndns(काष्ठा device *dev, काष्ठा nd_namespace_common **_ndns);
bool nd_attach_ndns(काष्ठा device *dev, काष्ठा nd_namespace_common *attach,
		काष्ठा nd_namespace_common **_ndns);
bool __nd_attach_ndns(काष्ठा device *dev, काष्ठा nd_namespace_common *attach,
		काष्ठा nd_namespace_common **_ndns);
sमाप_प्रकार nd_namespace_store(काष्ठा device *dev,
		काष्ठा nd_namespace_common **_ndns, स्थिर अक्षर *buf,
		माप_प्रकार len);
काष्ठा nd_pfn *to_nd_pfn_safe(काष्ठा device *dev);
bool is_nvdimm_bus(काष्ठा device *dev);

#अगर IS_ENABLED(CONFIG_ND_CLAIM)
पूर्णांक devm_nsio_enable(काष्ठा device *dev, काष्ठा nd_namespace_io *nsio,
		resource_माप_प्रकार size);
व्योम devm_nsio_disable(काष्ठा device *dev, काष्ठा nd_namespace_io *nsio);
#अन्यथा
अटल अंतरभूत पूर्णांक devm_nsio_enable(काष्ठा device *dev,
		काष्ठा nd_namespace_io *nsio, resource_माप_प्रकार size)
अणु
	वापस -ENXIO;
पूर्ण

अटल अंतरभूत व्योम devm_nsio_disable(काष्ठा device *dev,
		काष्ठा nd_namespace_io *nsio)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROVE_LOCKING
बाह्य काष्ठा class *nd_class;

क्रमागत अणु
	LOCK_BUS,
	LOCK_NDCTL,
	LOCK_REGION,
	LOCK_DIMM = LOCK_REGION,
	LOCK_NAMESPACE,
	LOCK_CLAIM,
पूर्ण;

अटल अंतरभूत व्योम debug_nvdimm_lock(काष्ठा device *dev)
अणु
	अगर (is_nd_region(dev))
		mutex_lock_nested(&dev->lockdep_mutex, LOCK_REGION);
	अन्यथा अगर (is_nvdimm(dev))
		mutex_lock_nested(&dev->lockdep_mutex, LOCK_DIMM);
	अन्यथा अगर (is_nd_btt(dev) || is_nd_pfn(dev) || is_nd_dax(dev))
		mutex_lock_nested(&dev->lockdep_mutex, LOCK_CLAIM);
	अन्यथा अगर (dev->parent && (is_nd_region(dev->parent)))
		mutex_lock_nested(&dev->lockdep_mutex, LOCK_NAMESPACE);
	अन्यथा अगर (is_nvdimm_bus(dev))
		mutex_lock_nested(&dev->lockdep_mutex, LOCK_BUS);
	अन्यथा अगर (dev->class && dev->class == nd_class)
		mutex_lock_nested(&dev->lockdep_mutex, LOCK_NDCTL);
	अन्यथा
		dev_WARN(dev, "unknown lock level\n");
पूर्ण

अटल अंतरभूत व्योम debug_nvdimm_unlock(काष्ठा device *dev)
अणु
	mutex_unlock(&dev->lockdep_mutex);
पूर्ण

अटल अंतरभूत व्योम nd_device_lock(काष्ठा device *dev)
अणु
	device_lock(dev);
	debug_nvdimm_lock(dev);
पूर्ण

अटल अंतरभूत व्योम nd_device_unlock(काष्ठा device *dev)
अणु
	debug_nvdimm_unlock(dev);
	device_unlock(dev);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम nd_device_lock(काष्ठा device *dev)
अणु
	device_lock(dev);
पूर्ण

अटल अंतरभूत व्योम nd_device_unlock(काष्ठा device *dev)
अणु
	device_unlock(dev);
पूर्ण

अटल अंतरभूत व्योम debug_nvdimm_lock(काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_nvdimm_unlock(काष्ठा device *dev)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __ND_CORE_H__ */
