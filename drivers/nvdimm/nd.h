<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#अगर_अघोषित __ND_H__
#घोषणा __ND_H__
#समावेश <linux/libnvdimm.h>
#समावेश <linux/badblocks.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/types.h>
#समावेश <linux/nd.h>
#समावेश "label.h"

क्रमागत अणु
	/*
	 * Limits the maximum number of block apertures a dimm can
	 * support and is an input to the geometry/on-disk-क्रमmat of a
	 * BTT instance
	 */
	ND_MAX_LANES = 256,
	INT_LBASIZE_ALIGNMENT = 64,
	NVDIMM_IO_ATOMIC = 1,
पूर्ण;

काष्ठा nvdimm_drvdata अणु
	काष्ठा device *dev;
	पूर्णांक nslabel_size;
	काष्ठा nd_cmd_get_config_size nsarea;
	व्योम *data;
	पूर्णांक ns_current, ns_next;
	काष्ठा resource dpa;
	काष्ठा kref kref;
पूर्ण;

काष्ठा nd_region_data अणु
	पूर्णांक ns_count;
	पूर्णांक ns_active;
	अचिन्हित पूर्णांक hपूर्णांकs_shअगरt;
	व्योम __iomem *flush_wpq[];
पूर्ण;

अटल अंतरभूत व्योम __iomem *ndrd_get_flush_wpq(काष्ठा nd_region_data *ndrd,
		पूर्णांक dimm, पूर्णांक hपूर्णांक)
अणु
	अचिन्हित पूर्णांक num = 1 << ndrd->hपूर्णांकs_shअगरt;
	अचिन्हित पूर्णांक mask = num - 1;

	वापस ndrd->flush_wpq[dimm * num + (hपूर्णांक & mask)];
पूर्ण

अटल अंतरभूत व्योम ndrd_set_flush_wpq(काष्ठा nd_region_data *ndrd, पूर्णांक dimm,
		पूर्णांक hपूर्णांक, व्योम __iomem *flush)
अणु
	अचिन्हित पूर्णांक num = 1 << ndrd->hपूर्णांकs_shअगरt;
	अचिन्हित पूर्णांक mask = num - 1;

	ndrd->flush_wpq[dimm * num + (hपूर्णांक & mask)] = flush;
पूर्ण

अटल अंतरभूत काष्ठा nd_namespace_index *to_namespace_index(
		काष्ठा nvdimm_drvdata *ndd, पूर्णांक i)
अणु
	अगर (i < 0)
		वापस शून्य;

	वापस ndd->data + माप_namespace_index(ndd) * i;
पूर्ण

अटल अंतरभूत काष्ठा nd_namespace_index *to_current_namespace_index(
		काष्ठा nvdimm_drvdata *ndd)
अणु
	वापस to_namespace_index(ndd, ndd->ns_current);
पूर्ण

अटल अंतरभूत काष्ठा nd_namespace_index *to_next_namespace_index(
		काष्ठा nvdimm_drvdata *ndd)
अणु
	वापस to_namespace_index(ndd, ndd->ns_next);
पूर्ण

अचिन्हित माप_namespace_label(काष्ठा nvdimm_drvdata *ndd);

#घोषणा namespace_label_has(ndd, field) \
	(दुरत्व(काष्ठा nd_namespace_label, field) \
		< माप_namespace_label(ndd))

#घोषणा nd_dbg_dpa(r, d, res, fmt, arg...) \
	dev_dbg((r) ? &(r)->dev : (d)->dev, "%s: %.13s: %#llx @ %#llx " fmt, \
		(r) ? dev_name((d)->dev) : "", res ? res->name : "null", \
		(अचिन्हित दीर्घ दीर्घ) (res ? resource_size(res) : 0), \
		(अचिन्हित दीर्घ दीर्घ) (res ? res->start : 0), ##arg)

#घोषणा क्रम_each_dpa_resource(ndd, res) \
	क्रम (res = (ndd)->dpa.child; res; res = res->sibling)

#घोषणा क्रम_each_dpa_resource_safe(ndd, res, next) \
	क्रम (res = (ndd)->dpa.child, next = res ? res->sibling : शून्य; \
			res; res = next, next = next ? next->sibling : शून्य)

काष्ठा nd_percpu_lane अणु
	पूर्णांक count;
	spinlock_t lock;
पूर्ण;

क्रमागत nd_label_flags अणु
	ND_LABEL_REAP,
पूर्ण;
काष्ठा nd_label_ent अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ flags;
	काष्ठा nd_namespace_label *label;
पूर्ण;

क्रमागत nd_mapping_lock_class अणु
	ND_MAPPING_CLASS0,
	ND_MAPPING_UUID_SCAN,
पूर्ण;

काष्ठा nd_mapping अणु
	काष्ठा nvdimm *nvdimm;
	u64 start;
	u64 size;
	पूर्णांक position;
	काष्ठा list_head labels;
	काष्ठा mutex lock;
	/*
	 * @ndd is क्रम निजी use at region enable / disable समय क्रम
	 * get_ndd() + put_ndd(), all other nd_mapping to ndd
	 * conversions use to_ndd() which respects enabled state of the
	 * nvdimm.
	 */
	काष्ठा nvdimm_drvdata *ndd;
पूर्ण;

काष्ठा nd_region अणु
	काष्ठा device dev;
	काष्ठा ida ns_ida;
	काष्ठा ida btt_ida;
	काष्ठा ida pfn_ida;
	काष्ठा ida dax_ida;
	अचिन्हित दीर्घ flags;
	काष्ठा device *ns_seed;
	काष्ठा device *btt_seed;
	काष्ठा device *pfn_seed;
	काष्ठा device *dax_seed;
	अचिन्हित दीर्घ align;
	u16 ndr_mappings;
	u64 ndr_size;
	u64 ndr_start;
	पूर्णांक id, num_lanes, ro, numa_node, target_node;
	व्योम *provider_data;
	काष्ठा kernfs_node *bb_state;
	काष्ठा badblocks bb;
	काष्ठा nd_पूर्णांकerleave_set *nd_set;
	काष्ठा nd_percpu_lane __percpu *lane;
	पूर्णांक (*flush)(काष्ठा nd_region *nd_region, काष्ठा bio *bio);
	काष्ठा nd_mapping mapping[];
पूर्ण;

काष्ठा nd_blk_region अणु
	पूर्णांक (*enable)(काष्ठा nvdimm_bus *nvdimm_bus, काष्ठा device *dev);
	पूर्णांक (*करो_io)(काष्ठा nd_blk_region *ndbr, resource_माप_प्रकार dpa,
			व्योम *iobuf, u64 len, पूर्णांक rw);
	व्योम *blk_provider_data;
	काष्ठा nd_region nd_region;
पूर्ण;

/*
 * Lookup next in the repeating sequence of 01, 10, and 11.
 */
अटल अंतरभूत अचिन्हित nd_inc_seq(अचिन्हित seq)
अणु
	अटल स्थिर अचिन्हित next[] = अणु 0, 2, 3, 1 पूर्ण;

	वापस next[seq & 3];
पूर्ण

काष्ठा btt;
काष्ठा nd_btt अणु
	काष्ठा device dev;
	काष्ठा nd_namespace_common *ndns;
	काष्ठा btt *btt;
	अचिन्हित दीर्घ lbasize;
	u64 size;
	u8 *uuid;
	पूर्णांक id;
	पूर्णांक initial_offset;
	u16 version_major;
	u16 version_minor;
पूर्ण;

क्रमागत nd_pfn_mode अणु
	PFN_MODE_NONE,
	PFN_MODE_RAM,
	PFN_MODE_PMEM,
पूर्ण;

काष्ठा nd_pfn अणु
	पूर्णांक id;
	u8 *uuid;
	काष्ठा device dev;
	अचिन्हित दीर्घ align;
	अचिन्हित दीर्घ npfns;
	क्रमागत nd_pfn_mode mode;
	काष्ठा nd_pfn_sb *pfn_sb;
	काष्ठा nd_namespace_common *ndns;
पूर्ण;

काष्ठा nd_dax अणु
	काष्ठा nd_pfn nd_pfn;
पूर्ण;

अटल अंतरभूत u32 nd_info_block_reserve(व्योम)
अणु
	वापस ALIGN(SZ_8K, PAGE_SIZE);
पूर्ण

क्रमागत nd_async_mode अणु
	ND_SYNC,
	ND_ASYNC,
पूर्ण;

पूर्णांक nd_पूर्णांकegrity_init(काष्ठा gendisk *disk, अचिन्हित दीर्घ meta_size);
व्योम रुको_nvdimm_bus_probe_idle(काष्ठा device *dev);
व्योम nd_device_रेजिस्टर(काष्ठा device *dev);
व्योम nd_device_unरेजिस्टर(काष्ठा device *dev, क्रमागत nd_async_mode mode);
व्योम nd_device_notअगरy(काष्ठा device *dev, क्रमागत nvdimm_event event);
पूर्णांक nd_uuid_store(काष्ठा device *dev, u8 **uuid_out, स्थिर अक्षर *buf,
		माप_प्रकार len);
sमाप_प्रकार nd_size_select_show(अचिन्हित दीर्घ current_size,
		स्थिर अचिन्हित दीर्घ *supported, अक्षर *buf);
sमाप_प्रकार nd_size_select_store(काष्ठा device *dev, स्थिर अक्षर *buf,
		अचिन्हित दीर्घ *current_size, स्थिर अचिन्हित दीर्घ *supported);
पूर्णांक __init nvdimm_init(व्योम);
पूर्णांक __init nd_region_init(व्योम);
पूर्णांक __init nd_label_init(व्योम);
व्योम nvdimm_निकास(व्योम);
व्योम nd_region_निकास(व्योम);
काष्ठा nvdimm;
बाह्य स्थिर काष्ठा attribute_group nd_device_attribute_group;
बाह्य स्थिर काष्ठा attribute_group nd_numa_attribute_group;
बाह्य स्थिर काष्ठा attribute_group *nvdimm_bus_attribute_groups[];
काष्ठा nvdimm_drvdata *to_ndd(काष्ठा nd_mapping *nd_mapping);
पूर्णांक nvdimm_check_config_data(काष्ठा device *dev);
पूर्णांक nvdimm_init_nsarea(काष्ठा nvdimm_drvdata *ndd);
पूर्णांक nvdimm_init_config_data(काष्ठा nvdimm_drvdata *ndd);
पूर्णांक nvdimm_get_config_data(काष्ठा nvdimm_drvdata *ndd, व्योम *buf,
			   माप_प्रकार offset, माप_प्रकार len);
पूर्णांक nvdimm_set_config_data(काष्ठा nvdimm_drvdata *ndd, माप_प्रकार offset,
		व्योम *buf, माप_प्रकार len);
दीर्घ nvdimm_clear_poison(काष्ठा device *dev, phys_addr_t phys,
		अचिन्हित पूर्णांक len);
व्योम nvdimm_set_labeling(काष्ठा device *dev);
व्योम nvdimm_set_locked(काष्ठा device *dev);
व्योम nvdimm_clear_locked(काष्ठा device *dev);
पूर्णांक nvdimm_security_setup_events(काष्ठा device *dev);
#अगर IS_ENABLED(CONFIG_NVDIMM_KEYS)
पूर्णांक nvdimm_security_unlock(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक nvdimm_security_unlock(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
काष्ठा nd_btt *to_nd_btt(काष्ठा device *dev);

काष्ठा nd_gen_sb अणु
	अक्षर reserved[SZ_4K - 8];
	__le64 checksum;
पूर्ण;

u64 nd_sb_checksum(काष्ठा nd_gen_sb *sb);
#अगर IS_ENABLED(CONFIG_BTT)
पूर्णांक nd_btt_probe(काष्ठा device *dev, काष्ठा nd_namespace_common *ndns);
bool is_nd_btt(काष्ठा device *dev);
काष्ठा device *nd_btt_create(काष्ठा nd_region *nd_region);
#अन्यथा
अटल अंतरभूत पूर्णांक nd_btt_probe(काष्ठा device *dev,
		काष्ठा nd_namespace_common *ndns)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत bool is_nd_btt(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा device *nd_btt_create(काष्ठा nd_region *nd_region)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

काष्ठा nd_pfn *to_nd_pfn(काष्ठा device *dev);
#अगर IS_ENABLED(CONFIG_NVDIMM_PFN)

#घोषणा MAX_NVDIMM_ALIGN	4

पूर्णांक nd_pfn_probe(काष्ठा device *dev, काष्ठा nd_namespace_common *ndns);
bool is_nd_pfn(काष्ठा device *dev);
काष्ठा device *nd_pfn_create(काष्ठा nd_region *nd_region);
काष्ठा device *nd_pfn_devinit(काष्ठा nd_pfn *nd_pfn,
		काष्ठा nd_namespace_common *ndns);
पूर्णांक nd_pfn_validate(काष्ठा nd_pfn *nd_pfn, स्थिर अक्षर *sig);
बाह्य स्थिर काष्ठा attribute_group *nd_pfn_attribute_groups[];
#अन्यथा
अटल अंतरभूत पूर्णांक nd_pfn_probe(काष्ठा device *dev,
		काष्ठा nd_namespace_common *ndns)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत bool is_nd_pfn(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा device *nd_pfn_create(काष्ठा nd_region *nd_region)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक nd_pfn_validate(काष्ठा nd_pfn *nd_pfn, स्थिर अक्षर *sig)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

काष्ठा nd_dax *to_nd_dax(काष्ठा device *dev);
#अगर IS_ENABLED(CONFIG_NVDIMM_DAX)
पूर्णांक nd_dax_probe(काष्ठा device *dev, काष्ठा nd_namespace_common *ndns);
bool is_nd_dax(काष्ठा device *dev);
काष्ठा device *nd_dax_create(काष्ठा nd_region *nd_region);
#अन्यथा
अटल अंतरभूत पूर्णांक nd_dax_probe(काष्ठा device *dev,
		काष्ठा nd_namespace_common *ndns)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत bool is_nd_dax(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा device *nd_dax_create(काष्ठा nd_region *nd_region)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

पूर्णांक nd_region_to_nstype(काष्ठा nd_region *nd_region);
पूर्णांक nd_region_रेजिस्टर_namespaces(काष्ठा nd_region *nd_region, पूर्णांक *err);
u64 nd_region_पूर्णांकerleave_set_cookie(काष्ठा nd_region *nd_region,
		काष्ठा nd_namespace_index *nsindex);
u64 nd_region_पूर्णांकerleave_set_altcookie(काष्ठा nd_region *nd_region);
व्योम nvdimm_bus_lock(काष्ठा device *dev);
व्योम nvdimm_bus_unlock(काष्ठा device *dev);
bool is_nvdimm_bus_locked(काष्ठा device *dev);
व्योम nvdimm_check_and_set_ro(काष्ठा gendisk *disk);
व्योम nvdimm_drvdata_release(काष्ठा kref *kref);
व्योम put_ndd(काष्ठा nvdimm_drvdata *ndd);
पूर्णांक nd_label_reserve_dpa(काष्ठा nvdimm_drvdata *ndd);
व्योम nvdimm_मुक्त_dpa(काष्ठा nvdimm_drvdata *ndd, काष्ठा resource *res);
काष्ठा resource *nvdimm_allocate_dpa(काष्ठा nvdimm_drvdata *ndd,
		काष्ठा nd_label_id *label_id, resource_माप_प्रकार start,
		resource_माप_प्रकार n);
resource_माप_प्रकार nvdimm_namespace_capacity(काष्ठा nd_namespace_common *ndns);
bool nvdimm_namespace_locked(काष्ठा nd_namespace_common *ndns);
काष्ठा nd_namespace_common *nvdimm_namespace_common_probe(काष्ठा device *dev);
पूर्णांक nvdimm_namespace_attach_btt(काष्ठा nd_namespace_common *ndns);
पूर्णांक nvdimm_namespace_detach_btt(काष्ठा nd_btt *nd_btt);
स्थिर अक्षर *nvdimm_namespace_disk_name(काष्ठा nd_namespace_common *ndns,
		अक्षर *name);
अचिन्हित पूर्णांक pmem_sector_size(काष्ठा nd_namespace_common *ndns);
काष्ठा range;
व्योम nvdimm_badblocks_populate(काष्ठा nd_region *nd_region,
		काष्ठा badblocks *bb, स्थिर काष्ठा range *range);
पूर्णांक devm_namespace_enable(काष्ठा device *dev, काष्ठा nd_namespace_common *ndns,
		resource_माप_प्रकार size);
व्योम devm_namespace_disable(काष्ठा device *dev,
		काष्ठा nd_namespace_common *ndns);
#अगर IS_ENABLED(CONFIG_ND_CLAIM)
/* max काष्ठा page size independent of kernel config */
#घोषणा MAX_STRUCT_PAGE_SIZE 64
पूर्णांक nvdimm_setup_pfn(काष्ठा nd_pfn *nd_pfn, काष्ठा dev_pagemap *pgmap);
#अन्यथा
अटल अंतरभूत पूर्णांक nvdimm_setup_pfn(काष्ठा nd_pfn *nd_pfn,
				   काष्ठा dev_pagemap *pgmap)
अणु
	वापस -ENXIO;
पूर्ण
#पूर्ण_अगर
पूर्णांक nd_blk_region_init(काष्ठा nd_region *nd_region);
पूर्णांक nd_region_activate(काष्ठा nd_region *nd_region);
अटल अंतरभूत bool is_bad_pmem(काष्ठा badblocks *bb, sector_t sector,
		अचिन्हित पूर्णांक len)
अणु
	अगर (bb->count) अणु
		sector_t first_bad;
		पूर्णांक num_bad;

		वापस !!badblocks_check(bb, sector, len / 512, &first_bad,
				&num_bad);
	पूर्ण

	वापस false;
पूर्ण
resource_माप_प्रकार nd_namespace_blk_validate(काष्ठा nd_namespace_blk *nsblk);
स्थिर u8 *nd_dev_to_uuid(काष्ठा device *dev);
bool pmem_should_map_pages(काष्ठा device *dev);
#पूर्ण_अगर /* __ND_H__ */
