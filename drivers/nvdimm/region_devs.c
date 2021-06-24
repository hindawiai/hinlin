<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#समावेश <linux/scatterlist.h>
#समावेश <linux/memregion.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/hash.h>
#समावेश <linux/sort.h>
#समावेश <linux/पन.स>
#समावेश <linux/nd.h>
#समावेश "nd-core.h"
#समावेश "nd.h"

/*
 * For पढ़ोq() and ग_लिखोq() on 32-bit builds, the hi-lo, lo-hi order is
 * irrelevant.
 */
#समावेश <linux/io-64-nonatomic-hi-lo.h>

अटल DEFINE_PER_CPU(पूर्णांक, flush_idx);

अटल पूर्णांक nvdimm_map_flush(काष्ठा device *dev, काष्ठा nvdimm *nvdimm, पूर्णांक dimm,
		काष्ठा nd_region_data *ndrd)
अणु
	पूर्णांक i, j;

	dev_dbg(dev, "%s: map %d flush address%s\n", nvdimm_name(nvdimm),
			nvdimm->num_flush, nvdimm->num_flush == 1 ? "" : "es");
	क्रम (i = 0; i < (1 << ndrd->hपूर्णांकs_shअगरt); i++) अणु
		काष्ठा resource *res = &nvdimm->flush_wpq[i];
		अचिन्हित दीर्घ pfn = PHYS_PFN(res->start);
		व्योम __iomem *flush_page;

		/* check अगर flush hपूर्णांकs share a page */
		क्रम (j = 0; j < i; j++) अणु
			काष्ठा resource *res_j = &nvdimm->flush_wpq[j];
			अचिन्हित दीर्घ pfn_j = PHYS_PFN(res_j->start);

			अगर (pfn == pfn_j)
				अवरोध;
		पूर्ण

		अगर (j < i)
			flush_page = (व्योम __iomem *) ((अचिन्हित दीर्घ)
					ndrd_get_flush_wpq(ndrd, dimm, j)
					& PAGE_MASK);
		अन्यथा
			flush_page = devm_nvdimm_ioremap(dev,
					PFN_PHYS(pfn), PAGE_SIZE);
		अगर (!flush_page)
			वापस -ENXIO;
		ndrd_set_flush_wpq(ndrd, dimm, i, flush_page
				+ (res->start & ~PAGE_MASK));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक nd_region_activate(काष्ठा nd_region *nd_region)
अणु
	पूर्णांक i, j, num_flush = 0;
	काष्ठा nd_region_data *ndrd;
	काष्ठा device *dev = &nd_region->dev;
	माप_प्रकार flush_data_size = माप(व्योम *);

	nvdimm_bus_lock(&nd_region->dev);
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm *nvdimm = nd_mapping->nvdimm;

		अगर (test_bit(NDD_SECURITY_OVERWRITE, &nvdimm->flags)) अणु
			nvdimm_bus_unlock(&nd_region->dev);
			वापस -EBUSY;
		पूर्ण

		/* at least one null hपूर्णांक slot per-dimm क्रम the "no-hint" हाल */
		flush_data_size += माप(व्योम *);
		num_flush = min_not_zero(num_flush, nvdimm->num_flush);
		अगर (!nvdimm->num_flush)
			जारी;
		flush_data_size += nvdimm->num_flush * माप(व्योम *);
	पूर्ण
	nvdimm_bus_unlock(&nd_region->dev);

	ndrd = devm_kzalloc(dev, माप(*ndrd) + flush_data_size, GFP_KERNEL);
	अगर (!ndrd)
		वापस -ENOMEM;
	dev_set_drvdata(dev, ndrd);

	अगर (!num_flush)
		वापस 0;

	ndrd->hपूर्णांकs_shअगरt = ilog2(num_flush);
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm *nvdimm = nd_mapping->nvdimm;
		पूर्णांक rc = nvdimm_map_flush(&nd_region->dev, nvdimm, i, ndrd);

		अगर (rc)
			वापस rc;
	पूर्ण

	/*
	 * Clear out entries that are duplicates. This should prevent the
	 * extra flushings.
	 */
	क्रम (i = 0; i < nd_region->ndr_mappings - 1; i++) अणु
		/* ignore अगर शून्य alपढ़ोy */
		अगर (!ndrd_get_flush_wpq(ndrd, i, 0))
			जारी;

		क्रम (j = i + 1; j < nd_region->ndr_mappings; j++)
			अगर (ndrd_get_flush_wpq(ndrd, i, 0) ==
			    ndrd_get_flush_wpq(ndrd, j, 0))
				ndrd_set_flush_wpq(ndrd, j, 0, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nd_region_release(काष्ठा device *dev)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	u16 i;

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm *nvdimm = nd_mapping->nvdimm;

		put_device(&nvdimm->dev);
	पूर्ण
	मुक्त_percpu(nd_region->lane);
	memregion_मुक्त(nd_region->id);
	अगर (is_nd_blk(dev))
		kमुक्त(to_nd_blk_region(dev));
	अन्यथा
		kमुक्त(nd_region);
पूर्ण

काष्ठा nd_region *to_nd_region(काष्ठा device *dev)
अणु
	काष्ठा nd_region *nd_region = container_of(dev, काष्ठा nd_region, dev);

	WARN_ON(dev->type->release != nd_region_release);
	वापस nd_region;
पूर्ण
EXPORT_SYMBOL_GPL(to_nd_region);

काष्ठा device *nd_region_dev(काष्ठा nd_region *nd_region)
अणु
	अगर (!nd_region)
		वापस शून्य;
	वापस &nd_region->dev;
पूर्ण
EXPORT_SYMBOL_GPL(nd_region_dev);

काष्ठा nd_blk_region *to_nd_blk_region(काष्ठा device *dev)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	WARN_ON(!is_nd_blk(dev));
	वापस container_of(nd_region, काष्ठा nd_blk_region, nd_region);
पूर्ण
EXPORT_SYMBOL_GPL(to_nd_blk_region);

व्योम *nd_region_provider_data(काष्ठा nd_region *nd_region)
अणु
	वापस nd_region->provider_data;
पूर्ण
EXPORT_SYMBOL_GPL(nd_region_provider_data);

व्योम *nd_blk_region_provider_data(काष्ठा nd_blk_region *ndbr)
अणु
	वापस ndbr->blk_provider_data;
पूर्ण
EXPORT_SYMBOL_GPL(nd_blk_region_provider_data);

व्योम nd_blk_region_set_provider_data(काष्ठा nd_blk_region *ndbr, व्योम *data)
अणु
	ndbr->blk_provider_data = data;
पूर्ण
EXPORT_SYMBOL_GPL(nd_blk_region_set_provider_data);

/**
 * nd_region_to_nstype() - region to an पूर्णांकeger namespace type
 * @nd_region: region-device to पूर्णांकerrogate
 *
 * This is the 'nstype' attribute of a region as well, an input to the
 * MODALIAS क्रम namespace devices, and bit number क्रम a nvdimm_bus to match
 * namespace devices with namespace drivers.
 */
पूर्णांक nd_region_to_nstype(काष्ठा nd_region *nd_region)
अणु
	अगर (is_memory(&nd_region->dev)) अणु
		u16 i, label;

		क्रम (i = 0, label = 0; i < nd_region->ndr_mappings; i++) अणु
			काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
			काष्ठा nvdimm *nvdimm = nd_mapping->nvdimm;

			अगर (test_bit(NDD_LABELING, &nvdimm->flags))
				label++;
		पूर्ण
		अगर (label)
			वापस ND_DEVICE_NAMESPACE_PMEM;
		अन्यथा
			वापस ND_DEVICE_NAMESPACE_IO;
	पूर्ण अन्यथा अगर (is_nd_blk(&nd_region->dev)) अणु
		वापस ND_DEVICE_NAMESPACE_BLK;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nd_region_to_nstype);

अटल अचिन्हित दीर्घ दीर्घ region_size(काष्ठा nd_region *nd_region)
अणु
	अगर (is_memory(&nd_region->dev)) अणु
		वापस nd_region->ndr_size;
	पूर्ण अन्यथा अगर (nd_region->ndr_mappings == 1) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[0];

		वापस nd_mapping->size;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	वापस प्र_लिखो(buf, "%llu\n", region_size(nd_region));
पूर्ण
अटल DEVICE_ATTR_RO(size);

अटल sमाप_प्रकार deep_flush_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	/*
	 * NOTE: in the nvdimm_has_flush() error हाल this attribute is
	 * not visible.
	 */
	वापस प्र_लिखो(buf, "%d\n", nvdimm_has_flush(nd_region));
पूर्ण

अटल sमाप_प्रकार deep_flush_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	bool flush;
	पूर्णांक rc = strtobool(buf, &flush);
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	अगर (rc)
		वापस rc;
	अगर (!flush)
		वापस -EINVAL;
	rc = nvdimm_flush(nd_region, शून्य);
	अगर (rc)
		वापस rc;

	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(deep_flush);

अटल sमाप_प्रकार mappings_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	वापस प्र_लिखो(buf, "%d\n", nd_region->ndr_mappings);
पूर्ण
अटल DEVICE_ATTR_RO(mappings);

अटल sमाप_प्रकार nstype_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	वापस प्र_लिखो(buf, "%d\n", nd_region_to_nstype(nd_region));
पूर्ण
अटल DEVICE_ATTR_RO(nstype);

अटल sमाप_प्रकार set_cookie_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	काष्ठा nd_पूर्णांकerleave_set *nd_set = nd_region->nd_set;
	sमाप_प्रकार rc = 0;

	अगर (is_memory(dev) && nd_set)
		/* pass, should be precluded by region_visible */;
	अन्यथा
		वापस -ENXIO;

	/*
	 * The cookie to show depends on which specअगरication of the
	 * labels we are using. If there are not labels then शेष to
	 * the v1.1 namespace label cookie definition. To पढ़ो all this
	 * data we need to रुको क्रम probing to settle.
	 */
	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	रुको_nvdimm_bus_probe_idle(dev);
	अगर (nd_region->ndr_mappings) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[0];
		काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);

		अगर (ndd) अणु
			काष्ठा nd_namespace_index *nsindex;

			nsindex = to_namespace_index(ndd, ndd->ns_current);
			rc = प्र_लिखो(buf, "%#llx\n",
					nd_region_पूर्णांकerleave_set_cookie(nd_region,
						nsindex));
		पूर्ण
	पूर्ण
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	अगर (rc)
		वापस rc;
	वापस प्र_लिखो(buf, "%#llx\n", nd_set->cookie1);
पूर्ण
अटल DEVICE_ATTR_RO(set_cookie);

resource_माप_प्रकार nd_region_available_dpa(काष्ठा nd_region *nd_region)
अणु
	resource_माप_प्रकार blk_max_overlap = 0, available, overlap;
	पूर्णांक i;

	WARN_ON(!is_nvdimm_bus_locked(&nd_region->dev));

 retry:
	available = 0;
	overlap = blk_max_overlap;
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);

		/* अगर a dimm is disabled the available capacity is zero */
		अगर (!ndd)
			वापस 0;

		अगर (is_memory(&nd_region->dev)) अणु
			available += nd_pmem_available_dpa(nd_region,
					nd_mapping, &overlap);
			अगर (overlap > blk_max_overlap) अणु
				blk_max_overlap = overlap;
				जाओ retry;
			पूर्ण
		पूर्ण अन्यथा अगर (is_nd_blk(&nd_region->dev))
			available += nd_blk_available_dpa(nd_region);
	पूर्ण

	वापस available;
पूर्ण

resource_माप_प्रकार nd_region_allocatable_dpa(काष्ठा nd_region *nd_region)
अणु
	resource_माप_प्रकार available = 0;
	पूर्णांक i;

	अगर (is_memory(&nd_region->dev))
		available = PHYS_ADDR_MAX;

	WARN_ON(!is_nvdimm_bus_locked(&nd_region->dev));
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];

		अगर (is_memory(&nd_region->dev))
			available = min(available,
					nd_pmem_max_contiguous_dpa(nd_region,
								   nd_mapping));
		अन्यथा अगर (is_nd_blk(&nd_region->dev))
			available += nd_blk_available_dpa(nd_region);
	पूर्ण
	अगर (is_memory(&nd_region->dev))
		वापस available * nd_region->ndr_mappings;
	वापस available;
पूर्ण

अटल sमाप_प्रकार available_size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	अचिन्हित दीर्घ दीर्घ available = 0;

	/*
	 * Flush in-flight updates and grab a snapshot of the available
	 * size.  Of course, this value is potentially invalidated the
	 * memory nvdimm_bus_lock() is dropped, but that's userspace's
	 * problem to not race itself.
	 */
	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	रुको_nvdimm_bus_probe_idle(dev);
	available = nd_region_available_dpa(nd_region);
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस प्र_लिखो(buf, "%llu\n", available);
पूर्ण
अटल DEVICE_ATTR_RO(available_size);

अटल sमाप_प्रकार max_available_extent_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	अचिन्हित दीर्घ दीर्घ available = 0;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	रुको_nvdimm_bus_probe_idle(dev);
	available = nd_region_allocatable_dpa(nd_region);
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस प्र_लिखो(buf, "%llu\n", available);
पूर्ण
अटल DEVICE_ATTR_RO(max_available_extent);

अटल sमाप_प्रकार init_namespaces_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region_data *ndrd = dev_get_drvdata(dev);
	sमाप_प्रकार rc;

	nvdimm_bus_lock(dev);
	अगर (ndrd)
		rc = प्र_लिखो(buf, "%d/%d\n", ndrd->ns_active, ndrd->ns_count);
	अन्यथा
		rc = -ENXIO;
	nvdimm_bus_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(init_namespaces);

अटल sमाप_प्रकार namespace_seed_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	sमाप_प्रकार rc;

	nvdimm_bus_lock(dev);
	अगर (nd_region->ns_seed)
		rc = प्र_लिखो(buf, "%s\n", dev_name(nd_region->ns_seed));
	अन्यथा
		rc = प्र_लिखो(buf, "\n");
	nvdimm_bus_unlock(dev);
	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(namespace_seed);

अटल sमाप_प्रकार btt_seed_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	sमाप_प्रकार rc;

	nvdimm_bus_lock(dev);
	अगर (nd_region->btt_seed)
		rc = प्र_लिखो(buf, "%s\n", dev_name(nd_region->btt_seed));
	अन्यथा
		rc = प्र_लिखो(buf, "\n");
	nvdimm_bus_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(btt_seed);

अटल sमाप_प्रकार pfn_seed_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	sमाप_प्रकार rc;

	nvdimm_bus_lock(dev);
	अगर (nd_region->pfn_seed)
		rc = प्र_लिखो(buf, "%s\n", dev_name(nd_region->pfn_seed));
	अन्यथा
		rc = प्र_लिखो(buf, "\n");
	nvdimm_bus_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(pfn_seed);

अटल sमाप_प्रकार dax_seed_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	sमाप_प्रकार rc;

	nvdimm_bus_lock(dev);
	अगर (nd_region->dax_seed)
		rc = प्र_लिखो(buf, "%s\n", dev_name(nd_region->dax_seed));
	अन्यथा
		rc = प्र_लिखो(buf, "\n");
	nvdimm_bus_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(dax_seed);

अटल sमाप_प्रकार पढ़ो_only_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	वापस प्र_लिखो(buf, "%d\n", nd_region->ro);
पूर्ण

अटल पूर्णांक revalidate_पढ़ो_only(काष्ठा device *dev, व्योम *data)
अणु
	nd_device_notअगरy(dev, NVDIMM_REVALIDATE_REGION);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार पढ़ो_only_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	bool ro;
	पूर्णांक rc = strtobool(buf, &ro);
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	अगर (rc)
		वापस rc;

	nd_region->ro = ro;
	device_क्रम_each_child(dev, शून्य, revalidate_पढ़ो_only);
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(पढ़ो_only);

अटल sमाप_प्रकार align_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	वापस प्र_लिखो(buf, "%#lx\n", nd_region->align);
पूर्ण

अटल sमाप_प्रकार align_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	अचिन्हित दीर्घ val, dpa;
	u32 reमुख्यder;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ(buf, 0, &val);
	अगर (rc)
		वापस rc;

	अगर (!nd_region->ndr_mappings)
		वापस -ENXIO;

	/*
	 * Ensure space-align is evenly भागisible by the region
	 * पूर्णांकerleave-width because the kernel typically has no facility
	 * to determine which DIMM(s), dimm-physical-addresses, would
	 * contribute to the tail capacity in प्रणाली-physical-address
	 * space क्रम the namespace.
	 */
	dpa = भाग_u64_rem(val, nd_region->ndr_mappings, &reमुख्यder);
	अगर (!is_घातer_of_2(dpa) || dpa < PAGE_SIZE
			|| val > region_size(nd_region) || reमुख्यder)
		वापस -EINVAL;

	/*
	 * Given that space allocation consults this value multiple
	 * बार ensure it करोes not change क्रम the duration of the
	 * allocation.
	 */
	nvdimm_bus_lock(dev);
	nd_region->align = val;
	nvdimm_bus_unlock(dev);

	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(align);

अटल sमाप_प्रकार region_badblocks_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	अगर (dev->driver)
		rc = badblocks_show(&nd_region->bb, buf, 0);
	अन्यथा
		rc = -ENXIO;
	nd_device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR(badblocks, 0444, region_badblocks_show, शून्य);

अटल sमाप_प्रकार resource_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	वापस प्र_लिखो(buf, "%#llx\n", nd_region->ndr_start);
पूर्ण
अटल DEVICE_ATTR_ADMIN_RO(resource);

अटल sमाप_प्रकार persistence_करोमुख्य_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	अगर (test_bit(ND_REGION_PERSIST_CACHE, &nd_region->flags))
		वापस प्र_लिखो(buf, "cpu_cache\n");
	अन्यथा अगर (test_bit(ND_REGION_PERSIST_MEMCTRL, &nd_region->flags))
		वापस प्र_लिखो(buf, "memory_controller\n");
	अन्यथा
		वापस प्र_लिखो(buf, "\n");
पूर्ण
अटल DEVICE_ATTR_RO(persistence_करोमुख्य);

अटल काष्ठा attribute *nd_region_attributes[] = अणु
	&dev_attr_size.attr,
	&dev_attr_align.attr,
	&dev_attr_nstype.attr,
	&dev_attr_mappings.attr,
	&dev_attr_btt_seed.attr,
	&dev_attr_pfn_seed.attr,
	&dev_attr_dax_seed.attr,
	&dev_attr_deep_flush.attr,
	&dev_attr_पढ़ो_only.attr,
	&dev_attr_set_cookie.attr,
	&dev_attr_available_size.attr,
	&dev_attr_max_available_extent.attr,
	&dev_attr_namespace_seed.attr,
	&dev_attr_init_namespaces.attr,
	&dev_attr_badblocks.attr,
	&dev_attr_resource.attr,
	&dev_attr_persistence_करोमुख्य.attr,
	शून्य,
पूर्ण;

अटल umode_t region_visible(काष्ठा kobject *kobj, काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, typeof(*dev), kobj);
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	काष्ठा nd_पूर्णांकerleave_set *nd_set = nd_region->nd_set;
	पूर्णांक type = nd_region_to_nstype(nd_region);

	अगर (!is_memory(dev) && a == &dev_attr_pfn_seed.attr)
		वापस 0;

	अगर (!is_memory(dev) && a == &dev_attr_dax_seed.attr)
		वापस 0;

	अगर (!is_memory(dev) && a == &dev_attr_badblocks.attr)
		वापस 0;

	अगर (a == &dev_attr_resource.attr && !is_memory(dev))
		वापस 0;

	अगर (a == &dev_attr_deep_flush.attr) अणु
		पूर्णांक has_flush = nvdimm_has_flush(nd_region);

		अगर (has_flush == 1)
			वापस a->mode;
		अन्यथा अगर (has_flush == 0)
			वापस 0444;
		अन्यथा
			वापस 0;
	पूर्ण

	अगर (a == &dev_attr_persistence_करोमुख्य.attr) अणु
		अगर ((nd_region->flags & (BIT(ND_REGION_PERSIST_CACHE)
					| BIT(ND_REGION_PERSIST_MEMCTRL))) == 0)
			वापस 0;
		वापस a->mode;
	पूर्ण

	अगर (a == &dev_attr_align.attr)
		वापस a->mode;

	अगर (a != &dev_attr_set_cookie.attr
			&& a != &dev_attr_available_size.attr)
		वापस a->mode;

	अगर ((type == ND_DEVICE_NAMESPACE_PMEM
				|| type == ND_DEVICE_NAMESPACE_BLK)
			&& a == &dev_attr_available_size.attr)
		वापस a->mode;
	अन्यथा अगर (is_memory(dev) && nd_set)
		वापस a->mode;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mappingN(काष्ठा device *dev, अक्षर *buf, पूर्णांक n)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);
	काष्ठा nd_mapping *nd_mapping;
	काष्ठा nvdimm *nvdimm;

	अगर (n >= nd_region->ndr_mappings)
		वापस -ENXIO;
	nd_mapping = &nd_region->mapping[n];
	nvdimm = nd_mapping->nvdimm;

	वापस प्र_लिखो(buf, "%s,%llu,%llu,%d\n", dev_name(&nvdimm->dev),
			nd_mapping->start, nd_mapping->size,
			nd_mapping->position);
पूर्ण

#घोषणा REGION_MAPPING(idx) \
अटल sमाप_प्रकार mapping##idx##_show(काष्ठा device *dev,		\
		काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु								\
	वापस mappingN(dev, buf, idx);				\
पूर्ण								\
अटल DEVICE_ATTR_RO(mapping##idx)

/*
 * 32 should be enough क्रम a जबतक, even in the presence of socket
 * पूर्णांकerleave a 32-way पूर्णांकerleave set is a degenerate हाल.
 */
REGION_MAPPING(0);
REGION_MAPPING(1);
REGION_MAPPING(2);
REGION_MAPPING(3);
REGION_MAPPING(4);
REGION_MAPPING(5);
REGION_MAPPING(6);
REGION_MAPPING(7);
REGION_MAPPING(8);
REGION_MAPPING(9);
REGION_MAPPING(10);
REGION_MAPPING(11);
REGION_MAPPING(12);
REGION_MAPPING(13);
REGION_MAPPING(14);
REGION_MAPPING(15);
REGION_MAPPING(16);
REGION_MAPPING(17);
REGION_MAPPING(18);
REGION_MAPPING(19);
REGION_MAPPING(20);
REGION_MAPPING(21);
REGION_MAPPING(22);
REGION_MAPPING(23);
REGION_MAPPING(24);
REGION_MAPPING(25);
REGION_MAPPING(26);
REGION_MAPPING(27);
REGION_MAPPING(28);
REGION_MAPPING(29);
REGION_MAPPING(30);
REGION_MAPPING(31);

अटल umode_t mapping_visible(काष्ठा kobject *kobj, काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	अगर (n < nd_region->ndr_mappings)
		वापस a->mode;
	वापस 0;
पूर्ण

अटल काष्ठा attribute *mapping_attributes[] = अणु
	&dev_attr_mapping0.attr,
	&dev_attr_mapping1.attr,
	&dev_attr_mapping2.attr,
	&dev_attr_mapping3.attr,
	&dev_attr_mapping4.attr,
	&dev_attr_mapping5.attr,
	&dev_attr_mapping6.attr,
	&dev_attr_mapping7.attr,
	&dev_attr_mapping8.attr,
	&dev_attr_mapping9.attr,
	&dev_attr_mapping10.attr,
	&dev_attr_mapping11.attr,
	&dev_attr_mapping12.attr,
	&dev_attr_mapping13.attr,
	&dev_attr_mapping14.attr,
	&dev_attr_mapping15.attr,
	&dev_attr_mapping16.attr,
	&dev_attr_mapping17.attr,
	&dev_attr_mapping18.attr,
	&dev_attr_mapping19.attr,
	&dev_attr_mapping20.attr,
	&dev_attr_mapping21.attr,
	&dev_attr_mapping22.attr,
	&dev_attr_mapping23.attr,
	&dev_attr_mapping24.attr,
	&dev_attr_mapping25.attr,
	&dev_attr_mapping26.attr,
	&dev_attr_mapping27.attr,
	&dev_attr_mapping28.attr,
	&dev_attr_mapping29.attr,
	&dev_attr_mapping30.attr,
	&dev_attr_mapping31.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nd_mapping_attribute_group = अणु
	.is_visible = mapping_visible,
	.attrs = mapping_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nd_region_attribute_group = अणु
	.attrs = nd_region_attributes,
	.is_visible = region_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *nd_region_attribute_groups[] = अणु
	&nd_device_attribute_group,
	&nd_region_attribute_group,
	&nd_numa_attribute_group,
	&nd_mapping_attribute_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा device_type nd_blk_device_type = अणु
	.name = "nd_blk",
	.release = nd_region_release,
	.groups = nd_region_attribute_groups,
पूर्ण;

अटल स्थिर काष्ठा device_type nd_pmem_device_type = अणु
	.name = "nd_pmem",
	.release = nd_region_release,
	.groups = nd_region_attribute_groups,
पूर्ण;

अटल स्थिर काष्ठा device_type nd_अस्थिर_device_type = अणु
	.name = "nd_volatile",
	.release = nd_region_release,
	.groups = nd_region_attribute_groups,
पूर्ण;

bool is_nd_pmem(काष्ठा device *dev)
अणु
	वापस dev ? dev->type == &nd_pmem_device_type : false;
पूर्ण

bool is_nd_blk(काष्ठा device *dev)
अणु
	वापस dev ? dev->type == &nd_blk_device_type : false;
पूर्ण

bool is_nd_अस्थिर(काष्ठा device *dev)
अणु
	वापस dev ? dev->type == &nd_अस्थिर_device_type : false;
पूर्ण

u64 nd_region_पूर्णांकerleave_set_cookie(काष्ठा nd_region *nd_region,
		काष्ठा nd_namespace_index *nsindex)
अणु
	काष्ठा nd_पूर्णांकerleave_set *nd_set = nd_region->nd_set;

	अगर (!nd_set)
		वापस 0;

	अगर (nsindex && __le16_to_cpu(nsindex->major) == 1
			&& __le16_to_cpu(nsindex->minor) == 1)
		वापस nd_set->cookie1;
	वापस nd_set->cookie2;
पूर्ण

u64 nd_region_पूर्णांकerleave_set_altcookie(काष्ठा nd_region *nd_region)
अणु
	काष्ठा nd_पूर्णांकerleave_set *nd_set = nd_region->nd_set;

	अगर (nd_set)
		वापस nd_set->altcookie;
	वापस 0;
पूर्ण

व्योम nd_mapping_मुक्त_labels(काष्ठा nd_mapping *nd_mapping)
अणु
	काष्ठा nd_label_ent *label_ent, *e;

	lockdep_निश्चित_held(&nd_mapping->lock);
	list_क्रम_each_entry_safe(label_ent, e, &nd_mapping->labels, list) अणु
		list_del(&label_ent->list);
		kमुक्त(label_ent);
	पूर्ण
पूर्ण

/*
 * When a namespace is activated create new seeds क्रम the next
 * namespace, or namespace-personality to be configured.
 */
व्योम nd_region_advance_seeds(काष्ठा nd_region *nd_region, काष्ठा device *dev)
अणु
	nvdimm_bus_lock(dev);
	अगर (nd_region->ns_seed == dev) अणु
		nd_region_create_ns_seed(nd_region);
	पूर्ण अन्यथा अगर (is_nd_btt(dev)) अणु
		काष्ठा nd_btt *nd_btt = to_nd_btt(dev);

		अगर (nd_region->btt_seed == dev)
			nd_region_create_btt_seed(nd_region);
		अगर (nd_region->ns_seed == &nd_btt->ndns->dev)
			nd_region_create_ns_seed(nd_region);
	पूर्ण अन्यथा अगर (is_nd_pfn(dev)) अणु
		काष्ठा nd_pfn *nd_pfn = to_nd_pfn(dev);

		अगर (nd_region->pfn_seed == dev)
			nd_region_create_pfn_seed(nd_region);
		अगर (nd_region->ns_seed == &nd_pfn->ndns->dev)
			nd_region_create_ns_seed(nd_region);
	पूर्ण अन्यथा अगर (is_nd_dax(dev)) अणु
		काष्ठा nd_dax *nd_dax = to_nd_dax(dev);

		अगर (nd_region->dax_seed == dev)
			nd_region_create_dax_seed(nd_region);
		अगर (nd_region->ns_seed == &nd_dax->nd_pfn.ndns->dev)
			nd_region_create_ns_seed(nd_region);
	पूर्ण
	nvdimm_bus_unlock(dev);
पूर्ण

पूर्णांक nd_blk_region_init(काष्ठा nd_region *nd_region)
अणु
	काष्ठा device *dev = &nd_region->dev;
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	अगर (!is_nd_blk(dev))
		वापस 0;

	अगर (nd_region->ndr_mappings < 1) अणु
		dev_dbg(dev, "invalid BLK region\n");
		वापस -ENXIO;
	पूर्ण

	वापस to_nd_blk_region(dev)->enable(nvdimm_bus, dev);
पूर्ण

/**
 * nd_region_acquire_lane - allocate and lock a lane
 * @nd_region: region id and number of lanes possible
 *
 * A lane correlates to a BLK-data-winकरोw and/or a log slot in the BTT.
 * We optimize क्रम the common हाल where there are 256 lanes, one
 * per-cpu.  For larger प्रणालीs we need to lock to share lanes.  For now
 * this implementation assumes the cost of मुख्यtaining an allocator क्रम
 * मुक्त lanes is on the order of the lock hold समय, so it implements a
 * अटल lane = cpu % num_lanes mapping.
 *
 * In the हाल of a BTT instance on top of a BLK namespace a lane may be
 * acquired recursively.  We lock on the first instance.
 *
 * In the हाल of a BTT instance on top of PMEM, we only acquire a lane
 * क्रम the BTT metadata updates.
 */
अचिन्हित पूर्णांक nd_region_acquire_lane(काष्ठा nd_region *nd_region)
अणु
	अचिन्हित पूर्णांक cpu, lane;

	cpu = get_cpu();
	अगर (nd_region->num_lanes < nr_cpu_ids) अणु
		काष्ठा nd_percpu_lane *ndl_lock, *ndl_count;

		lane = cpu % nd_region->num_lanes;
		ndl_count = per_cpu_ptr(nd_region->lane, cpu);
		ndl_lock = per_cpu_ptr(nd_region->lane, lane);
		अगर (ndl_count->count++ == 0)
			spin_lock(&ndl_lock->lock);
	पूर्ण अन्यथा
		lane = cpu;

	वापस lane;
पूर्ण
EXPORT_SYMBOL(nd_region_acquire_lane);

व्योम nd_region_release_lane(काष्ठा nd_region *nd_region, अचिन्हित पूर्णांक lane)
अणु
	अगर (nd_region->num_lanes < nr_cpu_ids) अणु
		अचिन्हित पूर्णांक cpu = get_cpu();
		काष्ठा nd_percpu_lane *ndl_lock, *ndl_count;

		ndl_count = per_cpu_ptr(nd_region->lane, cpu);
		ndl_lock = per_cpu_ptr(nd_region->lane, lane);
		अगर (--ndl_count->count == 0)
			spin_unlock(&ndl_lock->lock);
		put_cpu();
	पूर्ण
	put_cpu();
पूर्ण
EXPORT_SYMBOL(nd_region_release_lane);

/*
 * PowerPC requires this alignment क्रम memremap_pages(). All other archs
 * should be ok with SUBSECTION_SIZE (see memremap_compat_align()).
 */
#घोषणा MEMREMAP_COMPAT_ALIGN_MAX SZ_16M

अटल अचिन्हित दीर्घ शेष_align(काष्ठा nd_region *nd_region)
अणु
	अचिन्हित दीर्घ align;
	पूर्णांक i, mappings;
	u32 reमुख्यder;

	अगर (is_nd_blk(&nd_region->dev))
		align = PAGE_SIZE;
	अन्यथा
		align = MEMREMAP_COMPAT_ALIGN_MAX;

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm *nvdimm = nd_mapping->nvdimm;

		अगर (test_bit(NDD_ALIASING, &nvdimm->flags)) अणु
			align = MEMREMAP_COMPAT_ALIGN_MAX;
			अवरोध;
		पूर्ण
	पूर्ण

	mappings = max_t(u16, 1, nd_region->ndr_mappings);
	भाग_u64_rem(align, mappings, &reमुख्यder);
	अगर (reमुख्यder)
		align *= mappings;

	वापस align;
पूर्ण

अटल काष्ठा nd_region *nd_region_create(काष्ठा nvdimm_bus *nvdimm_bus,
		काष्ठा nd_region_desc *ndr_desc,
		स्थिर काष्ठा device_type *dev_type, स्थिर अक्षर *caller)
अणु
	काष्ठा nd_region *nd_region;
	काष्ठा device *dev;
	व्योम *region_buf;
	अचिन्हित पूर्णांक i;
	पूर्णांक ro = 0;

	क्रम (i = 0; i < ndr_desc->num_mappings; i++) अणु
		काष्ठा nd_mapping_desc *mapping = &ndr_desc->mapping[i];
		काष्ठा nvdimm *nvdimm = mapping->nvdimm;

		अगर ((mapping->start | mapping->size) % PAGE_SIZE) अणु
			dev_err(&nvdimm_bus->dev,
				"%s: %s mapping%d is not %ld aligned\n",
				caller, dev_name(&nvdimm->dev), i, PAGE_SIZE);
			वापस शून्य;
		पूर्ण

		अगर (test_bit(NDD_UNARMED, &nvdimm->flags))
			ro = 1;

		अगर (test_bit(NDD_NOBLK, &nvdimm->flags)
				&& dev_type == &nd_blk_device_type) अणु
			dev_err(&nvdimm_bus->dev, "%s: %s mapping%d is not BLK capable\n",
					caller, dev_name(&nvdimm->dev), i);
			वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (dev_type == &nd_blk_device_type) अणु
		काष्ठा nd_blk_region_desc *ndbr_desc;
		काष्ठा nd_blk_region *ndbr;

		ndbr_desc = to_blk_region_desc(ndr_desc);
		ndbr = kzalloc(माप(*ndbr) + माप(काष्ठा nd_mapping)
				* ndr_desc->num_mappings,
				GFP_KERNEL);
		अगर (ndbr) अणु
			nd_region = &ndbr->nd_region;
			ndbr->enable = ndbr_desc->enable;
			ndbr->करो_io = ndbr_desc->करो_io;
		पूर्ण
		region_buf = ndbr;
	पूर्ण अन्यथा अणु
		nd_region = kzalloc(काष्ठा_size(nd_region, mapping,
						ndr_desc->num_mappings),
				    GFP_KERNEL);
		region_buf = nd_region;
	पूर्ण

	अगर (!region_buf)
		वापस शून्य;
	nd_region->id = memregion_alloc(GFP_KERNEL);
	अगर (nd_region->id < 0)
		जाओ err_id;

	nd_region->lane = alloc_percpu(काष्ठा nd_percpu_lane);
	अगर (!nd_region->lane)
		जाओ err_percpu;

        क्रम (i = 0; i < nr_cpu_ids; i++) अणु
		काष्ठा nd_percpu_lane *ndl;

		ndl = per_cpu_ptr(nd_region->lane, i);
		spin_lock_init(&ndl->lock);
		ndl->count = 0;
	पूर्ण

	क्रम (i = 0; i < ndr_desc->num_mappings; i++) अणु
		काष्ठा nd_mapping_desc *mapping = &ndr_desc->mapping[i];
		काष्ठा nvdimm *nvdimm = mapping->nvdimm;

		nd_region->mapping[i].nvdimm = nvdimm;
		nd_region->mapping[i].start = mapping->start;
		nd_region->mapping[i].size = mapping->size;
		nd_region->mapping[i].position = mapping->position;
		INIT_LIST_HEAD(&nd_region->mapping[i].labels);
		mutex_init(&nd_region->mapping[i].lock);

		get_device(&nvdimm->dev);
	पूर्ण
	nd_region->ndr_mappings = ndr_desc->num_mappings;
	nd_region->provider_data = ndr_desc->provider_data;
	nd_region->nd_set = ndr_desc->nd_set;
	nd_region->num_lanes = ndr_desc->num_lanes;
	nd_region->flags = ndr_desc->flags;
	nd_region->ro = ro;
	nd_region->numa_node = ndr_desc->numa_node;
	nd_region->target_node = ndr_desc->target_node;
	ida_init(&nd_region->ns_ida);
	ida_init(&nd_region->btt_ida);
	ida_init(&nd_region->pfn_ida);
	ida_init(&nd_region->dax_ida);
	dev = &nd_region->dev;
	dev_set_name(dev, "region%d", nd_region->id);
	dev->parent = &nvdimm_bus->dev;
	dev->type = dev_type;
	dev->groups = ndr_desc->attr_groups;
	dev->of_node = ndr_desc->of_node;
	nd_region->ndr_size = resource_size(ndr_desc->res);
	nd_region->ndr_start = ndr_desc->res->start;
	nd_region->align = शेष_align(nd_region);
	अगर (ndr_desc->flush)
		nd_region->flush = ndr_desc->flush;
	अन्यथा
		nd_region->flush = शून्य;

	nd_device_रेजिस्टर(dev);

	वापस nd_region;

 err_percpu:
	memregion_मुक्त(nd_region->id);
 err_id:
	kमुक्त(region_buf);
	वापस शून्य;
पूर्ण

काष्ठा nd_region *nvdimm_pmem_region_create(काष्ठा nvdimm_bus *nvdimm_bus,
		काष्ठा nd_region_desc *ndr_desc)
अणु
	ndr_desc->num_lanes = ND_MAX_LANES;
	वापस nd_region_create(nvdimm_bus, ndr_desc, &nd_pmem_device_type,
			__func__);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_pmem_region_create);

काष्ठा nd_region *nvdimm_blk_region_create(काष्ठा nvdimm_bus *nvdimm_bus,
		काष्ठा nd_region_desc *ndr_desc)
अणु
	अगर (ndr_desc->num_mappings > 1)
		वापस शून्य;
	ndr_desc->num_lanes = min(ndr_desc->num_lanes, ND_MAX_LANES);
	वापस nd_region_create(nvdimm_bus, ndr_desc, &nd_blk_device_type,
			__func__);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_blk_region_create);

काष्ठा nd_region *nvdimm_अस्थिर_region_create(काष्ठा nvdimm_bus *nvdimm_bus,
		काष्ठा nd_region_desc *ndr_desc)
अणु
	ndr_desc->num_lanes = ND_MAX_LANES;
	वापस nd_region_create(nvdimm_bus, ndr_desc, &nd_अस्थिर_device_type,
			__func__);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_अस्थिर_region_create);

पूर्णांक nvdimm_flush(काष्ठा nd_region *nd_region, काष्ठा bio *bio)
अणु
	पूर्णांक rc = 0;

	अगर (!nd_region->flush)
		rc = generic_nvdimm_flush(nd_region);
	अन्यथा अणु
		अगर (nd_region->flush(nd_region, bio))
			rc = -EIO;
	पूर्ण

	वापस rc;
पूर्ण
/**
 * nvdimm_flush - flush any posted ग_लिखो queues between the cpu and pmem media
 * @nd_region: blk or पूर्णांकerleaved pmem region
 */
पूर्णांक generic_nvdimm_flush(काष्ठा nd_region *nd_region)
अणु
	काष्ठा nd_region_data *ndrd = dev_get_drvdata(&nd_region->dev);
	पूर्णांक i, idx;

	/*
	 * Try to encourage some भागersity in flush hपूर्णांक addresses
	 * across cpus assuming a limited number of flush hपूर्णांकs.
	 */
	idx = this_cpu_पढ़ो(flush_idx);
	idx = this_cpu_add_वापस(flush_idx, hash_32(current->pid + idx, 8));

	/*
	 * The pmem_wmb() is needed to 'sfence' all
	 * previous ग_लिखोs such that they are architecturally visible क्रम
	 * the platक्रमm buffer flush. Note that we've alपढ़ोy arranged क्रम pmem
	 * ग_लिखोs to aव्योम the cache via स_नकल_flushcache().  The final
	 * wmb() ensures ordering क्रम the NVDIMM flush ग_लिखो.
	 */
	pmem_wmb();
	क्रम (i = 0; i < nd_region->ndr_mappings; i++)
		अगर (ndrd_get_flush_wpq(ndrd, i, 0))
			ग_लिखोq(1, ndrd_get_flush_wpq(ndrd, i, idx));
	wmb();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_flush);

/**
 * nvdimm_has_flush - determine ग_लिखो flushing requirements
 * @nd_region: blk or पूर्णांकerleaved pmem region
 *
 * Returns 1 अगर ग_लिखोs require flushing
 * Returns 0 अगर ग_लिखोs करो not require flushing
 * Returns -ENXIO अगर flushing capability can not be determined
 */
पूर्णांक nvdimm_has_flush(काष्ठा nd_region *nd_region)
अणु
	पूर्णांक i;

	/* no nvdimm or pmem api == flushing capability unknown */
	अगर (nd_region->ndr_mappings == 0
			|| !IS_ENABLED(CONFIG_ARCH_HAS_PMEM_API))
		वापस -ENXIO;

	/* Test अगर an explicit flush function is defined */
	अगर (test_bit(ND_REGION_ASYNC, &nd_region->flags) && nd_region->flush)
		वापस 1;

	/* Test अगर any flush hपूर्णांकs क्रम the region are available */
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm *nvdimm = nd_mapping->nvdimm;

		/* flush hपूर्णांकs present / available */
		अगर (nvdimm->num_flush)
			वापस 1;
	पूर्ण

	/*
	 * The platक्रमm defines dimm devices without hपूर्णांकs nor explicit flush,
	 * assume platक्रमm persistence mechanism like ADR
	 */
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_has_flush);

पूर्णांक nvdimm_has_cache(काष्ठा nd_region *nd_region)
अणु
	वापस is_nd_pmem(&nd_region->dev) &&
		!test_bit(ND_REGION_PERSIST_CACHE, &nd_region->flags);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_has_cache);

bool is_nvdimm_sync(काष्ठा nd_region *nd_region)
अणु
	अगर (is_nd_अस्थिर(&nd_region->dev))
		वापस true;

	वापस is_nd_pmem(&nd_region->dev) &&
		!test_bit(ND_REGION_ASYNC, &nd_region->flags);
पूर्ण
EXPORT_SYMBOL_GPL(is_nvdimm_sync);

काष्ठा conflict_context अणु
	काष्ठा nd_region *nd_region;
	resource_माप_प्रकार start, size;
पूर्ण;

अटल पूर्णांक region_conflict(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा nd_region *nd_region;
	काष्ठा conflict_context *ctx = data;
	resource_माप_प्रकार res_end, region_end, region_start;

	अगर (!is_memory(dev))
		वापस 0;

	nd_region = to_nd_region(dev);
	अगर (nd_region == ctx->nd_region)
		वापस 0;

	res_end = ctx->start + ctx->size;
	region_start = nd_region->ndr_start;
	region_end = region_start + nd_region->ndr_size;
	अगर (ctx->start >= region_start && ctx->start < region_end)
		वापस -EBUSY;
	अगर (res_end > region_start && res_end <= region_end)
		वापस -EBUSY;
	वापस 0;
पूर्ण

पूर्णांक nd_region_conflict(काष्ठा nd_region *nd_region, resource_माप_प्रकार start,
		resource_माप_प्रकार size)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(&nd_region->dev);
	काष्ठा conflict_context ctx = अणु
		.nd_region = nd_region,
		.start = start,
		.size = size,
	पूर्ण;

	वापस device_क्रम_each_child(&nvdimm_bus->dev, &ctx, region_conflict);
पूर्ण
