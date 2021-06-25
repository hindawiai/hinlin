<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/sort.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/nd.h>
#समावेश "nd-core.h"
#समावेश "pmem.h"
#समावेश "pfn.h"
#समावेश "nd.h"

अटल व्योम namespace_io_release(काष्ठा device *dev)
अणु
	काष्ठा nd_namespace_io *nsio = to_nd_namespace_io(dev);

	kमुक्त(nsio);
पूर्ण

अटल व्योम namespace_pmem_release(काष्ठा device *dev)
अणु
	काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);

	अगर (nspm->id >= 0)
		ida_simple_हटाओ(&nd_region->ns_ida, nspm->id);
	kमुक्त(nspm->alt_name);
	kमुक्त(nspm->uuid);
	kमुक्त(nspm);
पूर्ण

अटल व्योम namespace_blk_release(काष्ठा device *dev)
अणु
	काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);

	अगर (nsblk->id >= 0)
		ida_simple_हटाओ(&nd_region->ns_ida, nsblk->id);
	kमुक्त(nsblk->alt_name);
	kमुक्त(nsblk->uuid);
	kमुक्त(nsblk->res);
	kमुक्त(nsblk);
पूर्ण

अटल bool is_namespace_pmem(स्थिर काष्ठा device *dev);
अटल bool is_namespace_blk(स्थिर काष्ठा device *dev);
अटल bool is_namespace_io(स्थिर काष्ठा device *dev);

अटल पूर्णांक is_uuid_busy(काष्ठा device *dev, व्योम *data)
अणु
	u8 *uuid1 = data, *uuid2 = शून्य;

	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		uuid2 = nspm->uuid;
	पूर्ण अन्यथा अगर (is_namespace_blk(dev)) अणु
		काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		uuid2 = nsblk->uuid;
	पूर्ण अन्यथा अगर (is_nd_btt(dev)) अणु
		काष्ठा nd_btt *nd_btt = to_nd_btt(dev);

		uuid2 = nd_btt->uuid;
	पूर्ण अन्यथा अगर (is_nd_pfn(dev)) अणु
		काष्ठा nd_pfn *nd_pfn = to_nd_pfn(dev);

		uuid2 = nd_pfn->uuid;
	पूर्ण

	अगर (uuid2 && स_भेद(uuid1, uuid2, NSLABEL_UUID_LEN) == 0)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक is_namespace_uuid_busy(काष्ठा device *dev, व्योम *data)
अणु
	अगर (is_nd_region(dev))
		वापस device_क्रम_each_child(dev, data, is_uuid_busy);
	वापस 0;
पूर्ण

/**
 * nd_is_uuid_unique - verअगरy that no other namespace has @uuid
 * @dev: any device on a nvdimm_bus
 * @uuid: uuid to check
 */
bool nd_is_uuid_unique(काष्ठा device *dev, u8 *uuid)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	अगर (!nvdimm_bus)
		वापस false;
	WARN_ON_ONCE(!is_nvdimm_bus_locked(&nvdimm_bus->dev));
	अगर (device_क्रम_each_child(&nvdimm_bus->dev, uuid,
				is_namespace_uuid_busy) != 0)
		वापस false;
	वापस true;
पूर्ण

bool pmem_should_map_pages(काष्ठा device *dev)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	काष्ठा nd_namespace_common *ndns = to_ndns(dev);
	काष्ठा nd_namespace_io *nsio;

	अगर (!IS_ENABLED(CONFIG_ZONE_DEVICE))
		वापस false;

	अगर (!test_bit(ND_REGION_PAGEMAP, &nd_region->flags))
		वापस false;

	अगर (is_nd_pfn(dev) || is_nd_btt(dev))
		वापस false;

	अगर (ndns->क्रमce_raw)
		वापस false;

	nsio = to_nd_namespace_io(dev);
	अगर (region_पूर्णांकersects(nsio->res.start, resource_size(&nsio->res),
				IORESOURCE_SYSTEM_RAM,
				IORES_DESC_NONE) == REGION_MIXED)
		वापस false;

	वापस ARCH_MEMREMAP_PMEM == MEMREMAP_WB;
पूर्ण
EXPORT_SYMBOL(pmem_should_map_pages);

अचिन्हित पूर्णांक pmem_sector_size(काष्ठा nd_namespace_common *ndns)
अणु
	अगर (is_namespace_pmem(&ndns->dev)) अणु
		काष्ठा nd_namespace_pmem *nspm;

		nspm = to_nd_namespace_pmem(&ndns->dev);
		अगर (nspm->lbasize == 0 || nspm->lbasize == 512)
			/* शेष */;
		अन्यथा अगर (nspm->lbasize == 4096)
			वापस 4096;
		अन्यथा
			dev_WARN(&ndns->dev, "unsupported sector size: %ld\n",
					nspm->lbasize);
	पूर्ण

	/*
	 * There is no namespace label (is_namespace_io()), or the label
	 * indicates the शेष sector size.
	 */
	वापस 512;
पूर्ण
EXPORT_SYMBOL(pmem_sector_size);

स्थिर अक्षर *nvdimm_namespace_disk_name(काष्ठा nd_namespace_common *ndns,
		अक्षर *name)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(ndns->dev.parent);
	स्थिर अक्षर *suffix = शून्य;

	अगर (ndns->claim && is_nd_btt(ndns->claim))
		suffix = "s";

	अगर (is_namespace_pmem(&ndns->dev) || is_namespace_io(&ndns->dev)) अणु
		पूर्णांक nsidx = 0;

		अगर (is_namespace_pmem(&ndns->dev)) अणु
			काष्ठा nd_namespace_pmem *nspm;

			nspm = to_nd_namespace_pmem(&ndns->dev);
			nsidx = nspm->id;
		पूर्ण

		अगर (nsidx)
			प्र_लिखो(name, "pmem%d.%d%s", nd_region->id, nsidx,
					suffix ? suffix : "");
		अन्यथा
			प्र_लिखो(name, "pmem%d%s", nd_region->id,
					suffix ? suffix : "");
	पूर्ण अन्यथा अगर (is_namespace_blk(&ndns->dev)) अणु
		काष्ठा nd_namespace_blk *nsblk;

		nsblk = to_nd_namespace_blk(&ndns->dev);
		प्र_लिखो(name, "ndblk%d.%d%s", nd_region->id, nsblk->id,
				suffix ? suffix : "");
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण

	वापस name;
पूर्ण
EXPORT_SYMBOL(nvdimm_namespace_disk_name);

स्थिर u8 *nd_dev_to_uuid(काष्ठा device *dev)
अणु
	अटल स्थिर u8 null_uuid[16];

	अगर (!dev)
		वापस null_uuid;

	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		वापस nspm->uuid;
	पूर्ण अन्यथा अगर (is_namespace_blk(dev)) अणु
		काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		वापस nsblk->uuid;
	पूर्ण अन्यथा
		वापस null_uuid;
पूर्ण
EXPORT_SYMBOL(nd_dev_to_uuid);

अटल sमाप_प्रकार nstype_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);

	वापस प्र_लिखो(buf, "%d\n", nd_region_to_nstype(nd_region));
पूर्ण
अटल DEVICE_ATTR_RO(nstype);

अटल sमाप_प्रकार __alt_name_store(काष्ठा device *dev, स्थिर अक्षर *buf,
		स्थिर माप_प्रकार len)
अणु
	अक्षर *input, *pos, *alt_name, **ns_altname;
	sमाप_प्रकार rc;

	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		ns_altname = &nspm->alt_name;
	पूर्ण अन्यथा अगर (is_namespace_blk(dev)) अणु
		काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		ns_altname = &nsblk->alt_name;
	पूर्ण अन्यथा
		वापस -ENXIO;

	अगर (dev->driver || to_ndns(dev)->claim)
		वापस -EBUSY;

	input = kstrndup(buf, len, GFP_KERNEL);
	अगर (!input)
		वापस -ENOMEM;

	pos = strim(input);
	अगर (म_माप(pos) + 1 > NSLABEL_NAME_LEN) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	alt_name = kzalloc(NSLABEL_NAME_LEN, GFP_KERNEL);
	अगर (!alt_name) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	kमुक्त(*ns_altname);
	*ns_altname = alt_name;
	प्र_लिखो(*ns_altname, "%s", pos);
	rc = len;

out:
	kमुक्त(input);
	वापस rc;
पूर्ण

अटल resource_माप_प्रकार nd_namespace_blk_size(काष्ठा nd_namespace_blk *nsblk)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(nsblk->common.dev.parent);
	काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[0];
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	काष्ठा nd_label_id label_id;
	resource_माप_प्रकार size = 0;
	काष्ठा resource *res;

	अगर (!nsblk->uuid)
		वापस 0;
	nd_label_gen_id(&label_id, nsblk->uuid, NSLABEL_FLAG_LOCAL);
	क्रम_each_dpa_resource(ndd, res)
		अगर (म_भेद(res->name, label_id.id) == 0)
			size += resource_size(res);
	वापस size;
पूर्ण

अटल bool __nd_namespace_blk_validate(काष्ठा nd_namespace_blk *nsblk)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(nsblk->common.dev.parent);
	काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[0];
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	काष्ठा nd_label_id label_id;
	काष्ठा resource *res;
	पूर्णांक count, i;

	अगर (!nsblk->uuid || !nsblk->lbasize || !ndd)
		वापस false;

	count = 0;
	nd_label_gen_id(&label_id, nsblk->uuid, NSLABEL_FLAG_LOCAL);
	क्रम_each_dpa_resource(ndd, res) अणु
		अगर (म_भेद(res->name, label_id.id) != 0)
			जारी;
		/*
		 * Resources with unacknowledged adjusपंचांगents indicate a
		 * failure to update labels
		 */
		अगर (res->flags & DPA_RESOURCE_ADJUSTED)
			वापस false;
		count++;
	पूर्ण

	/* These values match after a successful label update */
	अगर (count != nsblk->num_resources)
		वापस false;

	क्रम (i = 0; i < nsblk->num_resources; i++) अणु
		काष्ठा resource *found = शून्य;

		क्रम_each_dpa_resource(ndd, res)
			अगर (res == nsblk->res[i]) अणु
				found = res;
				अवरोध;
			पूर्ण
		/* stale resource */
		अगर (!found)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

resource_माप_प्रकार nd_namespace_blk_validate(काष्ठा nd_namespace_blk *nsblk)
अणु
	resource_माप_प्रकार size;

	nvdimm_bus_lock(&nsblk->common.dev);
	size = __nd_namespace_blk_validate(nsblk);
	nvdimm_bus_unlock(&nsblk->common.dev);

	वापस size;
पूर्ण
EXPORT_SYMBOL(nd_namespace_blk_validate);


अटल पूर्णांक nd_namespace_label_update(काष्ठा nd_region *nd_region,
		काष्ठा device *dev)
अणु
	dev_WARN_ONCE(dev, dev->driver || to_ndns(dev)->claim,
			"namespace must be idle during label update\n");
	अगर (dev->driver || to_ndns(dev)->claim)
		वापस 0;

	/*
	 * Only allow label ग_लिखोs that will result in a valid namespace
	 * or deletion of an existing namespace.
	 */
	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);
		resource_माप_प्रकार size = resource_size(&nspm->nsio.res);

		अगर (size == 0 && nspm->uuid)
			/* delete allocation */;
		अन्यथा अगर (!nspm->uuid)
			वापस 0;

		वापस nd_pmem_namespace_label_update(nd_region, nspm, size);
	पूर्ण अन्यथा अगर (is_namespace_blk(dev)) अणु
		काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);
		resource_माप_प्रकार size = nd_namespace_blk_size(nsblk);

		अगर (size == 0 && nsblk->uuid)
			/* delete allocation */;
		अन्यथा अगर (!nsblk->uuid || !nsblk->lbasize)
			वापस 0;

		वापस nd_blk_namespace_label_update(nd_region, nsblk, size);
	पूर्ण अन्यथा
		वापस -ENXIO;
पूर्ण

अटल sमाप_प्रकार alt_name_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	रुको_nvdimm_bus_probe_idle(dev);
	rc = __alt_name_store(dev, buf, len);
	अगर (rc >= 0)
		rc = nd_namespace_label_update(nd_region, dev);
	dev_dbg(dev, "%s(%zd)\n", rc < 0 ? "fail " : "", rc);
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस rc < 0 ? rc : len;
पूर्ण

अटल sमाप_प्रकार alt_name_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अक्षर *ns_altname;

	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		ns_altname = nspm->alt_name;
	पूर्ण अन्यथा अगर (is_namespace_blk(dev)) अणु
		काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		ns_altname = nsblk->alt_name;
	पूर्ण अन्यथा
		वापस -ENXIO;

	वापस प्र_लिखो(buf, "%s\n", ns_altname ? ns_altname : "");
पूर्ण
अटल DEVICE_ATTR_RW(alt_name);

अटल पूर्णांक scan_मुक्त(काष्ठा nd_region *nd_region,
		काष्ठा nd_mapping *nd_mapping, काष्ठा nd_label_id *label_id,
		resource_माप_प्रकार n)
अणु
	bool is_blk = म_भेदन(label_id->id, "blk", 3) == 0;
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	पूर्णांक rc = 0;

	जबतक (n) अणु
		काष्ठा resource *res, *last;
		resource_माप_प्रकार new_start;

		last = शून्य;
		क्रम_each_dpa_resource(ndd, res)
			अगर (म_भेद(res->name, label_id->id) == 0)
				last = res;
		res = last;
		अगर (!res)
			वापस 0;

		अगर (n >= resource_size(res)) अणु
			n -= resource_size(res);
			nd_dbg_dpa(nd_region, ndd, res, "delete %d\n", rc);
			nvdimm_मुक्त_dpa(ndd, res);
			/* retry with last resource deleted */
			जारी;
		पूर्ण

		/*
		 * Keep BLK allocations relegated to high DPA as much as
		 * possible
		 */
		अगर (is_blk)
			new_start = res->start + n;
		अन्यथा
			new_start = res->start;

		rc = adjust_resource(res, new_start, resource_size(res) - n);
		अगर (rc == 0)
			res->flags |= DPA_RESOURCE_ADJUSTED;
		nd_dbg_dpa(nd_region, ndd, res, "shrink %d\n", rc);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * shrink_dpa_allocation - क्रम each dimm in region मुक्त n bytes क्रम label_id
 * @nd_region: the set of dimms to reclaim @n bytes from
 * @label_id: unique identअगरier क्रम the namespace consuming this dpa range
 * @n: number of bytes per-dimm to release
 *
 * Assumes resources are ordered.  Starting from the end try to
 * adjust_resource() the allocation to @n, but अगर @n is larger than the
 * allocation delete it and find the 'new' last allocation in the label
 * set.
 */
अटल पूर्णांक shrink_dpa_allocation(काष्ठा nd_region *nd_region,
		काष्ठा nd_label_id *label_id, resource_माप_प्रकार n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		पूर्णांक rc;

		rc = scan_मुक्त(nd_region, nd_mapping, label_id, n);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल resource_माप_प्रकार init_dpa_allocation(काष्ठा nd_label_id *label_id,
		काष्ठा nd_region *nd_region, काष्ठा nd_mapping *nd_mapping,
		resource_माप_प्रकार n)
अणु
	bool is_blk = म_भेदन(label_id->id, "blk", 3) == 0;
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	resource_माप_प्रकार first_dpa;
	काष्ठा resource *res;
	पूर्णांक rc = 0;

	/* allocate blk from highest dpa first */
	अगर (is_blk)
		first_dpa = nd_mapping->start + nd_mapping->size - n;
	अन्यथा
		first_dpa = nd_mapping->start;

	/* first resource allocation क्रम this label-id or dimm */
	res = nvdimm_allocate_dpa(ndd, label_id, first_dpa, n);
	अगर (!res)
		rc = -EBUSY;

	nd_dbg_dpa(nd_region, ndd, res, "init %d\n", rc);
	वापस rc ? n : 0;
पूर्ण


/**
 * space_valid() - validate मुक्त dpa space against स्थिरraपूर्णांकs
 * @nd_region: hosting region of the मुक्त space
 * @ndd: dimm device data क्रम debug
 * @label_id: namespace id to allocate space
 * @prev: potential allocation that precedes मुक्त space
 * @next: allocation that follows the given मुक्त space range
 * @exist: first allocation with same id in the mapping
 * @n: range that must satisfied क्रम pmem allocations
 * @valid: मुक्त space range to validate
 *
 * BLK-space is valid as दीर्घ as it करोes not precede a PMEM
 * allocation in a given region. PMEM-space must be contiguous
 * and adjacent to an existing existing allocation (अगर one
 * exists).  If reserving PMEM any space is valid.
 */
अटल व्योम space_valid(काष्ठा nd_region *nd_region, काष्ठा nvdimm_drvdata *ndd,
		काष्ठा nd_label_id *label_id, काष्ठा resource *prev,
		काष्ठा resource *next, काष्ठा resource *exist,
		resource_माप_प्रकार n, काष्ठा resource *valid)
अणु
	bool is_reserve = म_भेद(label_id->id, "pmem-reserve") == 0;
	bool is_pmem = म_भेदन(label_id->id, "pmem", 4) == 0;
	अचिन्हित दीर्घ align;

	align = nd_region->align / nd_region->ndr_mappings;
	valid->start = ALIGN(valid->start, align);
	valid->end = ALIGN_DOWN(valid->end + 1, align) - 1;

	अगर (valid->start >= valid->end)
		जाओ invalid;

	अगर (is_reserve)
		वापस;

	अगर (!is_pmem) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[0];
		काष्ठा nvdimm_bus *nvdimm_bus;
		काष्ठा blk_alloc_info info = अणु
			.nd_mapping = nd_mapping,
			.available = nd_mapping->size,
			.res = valid,
		पूर्ण;

		WARN_ON(!is_nd_blk(&nd_region->dev));
		nvdimm_bus = walk_to_nvdimm_bus(&nd_region->dev);
		device_क्रम_each_child(&nvdimm_bus->dev, &info, alias_dpa_busy);
		वापस;
	पूर्ण

	/* allocation needs to be contiguous, so this is all or nothing */
	अगर (resource_size(valid) < n)
		जाओ invalid;

	/* we've got all the space we need and no existing allocation */
	अगर (!exist)
		वापस;

	/* allocation needs to be contiguous with the existing namespace */
	अगर (valid->start == exist->end + 1
			|| valid->end == exist->start - 1)
		वापस;

 invalid:
	/* truncate @valid size to 0 */
	valid->end = valid->start - 1;
पूर्ण

क्रमागत alloc_loc अणु
	ALLOC_ERR = 0, ALLOC_BEFORE, ALLOC_MID, ALLOC_AFTER,
पूर्ण;

अटल resource_माप_प्रकार scan_allocate(काष्ठा nd_region *nd_region,
		काष्ठा nd_mapping *nd_mapping, काष्ठा nd_label_id *label_id,
		resource_माप_प्रकार n)
अणु
	resource_माप_प्रकार mapping_end = nd_mapping->start + nd_mapping->size - 1;
	bool is_pmem = म_भेदन(label_id->id, "pmem", 4) == 0;
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	काष्ठा resource *res, *exist = शून्य, valid;
	स्थिर resource_माप_प्रकार to_allocate = n;
	पूर्णांक first;

	क्रम_each_dpa_resource(ndd, res)
		अगर (म_भेद(label_id->id, res->name) == 0)
			exist = res;

	valid.start = nd_mapping->start;
	valid.end = mapping_end;
	valid.name = "free space";
 retry:
	first = 0;
	क्रम_each_dpa_resource(ndd, res) अणु
		काष्ठा resource *next = res->sibling, *new_res = शून्य;
		resource_माप_प्रकार allocate, available = 0;
		क्रमागत alloc_loc loc = ALLOC_ERR;
		स्थिर अक्षर *action;
		पूर्णांक rc = 0;

		/* ignore resources outside this nd_mapping */
		अगर (res->start > mapping_end)
			जारी;
		अगर (res->end < nd_mapping->start)
			जारी;

		/* space at the beginning of the mapping */
		अगर (!first++ && res->start > nd_mapping->start) अणु
			valid.start = nd_mapping->start;
			valid.end = res->start - 1;
			space_valid(nd_region, ndd, label_id, शून्य, next, exist,
					to_allocate, &valid);
			available = resource_size(&valid);
			अगर (available)
				loc = ALLOC_BEFORE;
		पूर्ण

		/* space between allocations */
		अगर (!loc && next) अणु
			valid.start = res->start + resource_size(res);
			valid.end = min(mapping_end, next->start - 1);
			space_valid(nd_region, ndd, label_id, res, next, exist,
					to_allocate, &valid);
			available = resource_size(&valid);
			अगर (available)
				loc = ALLOC_MID;
		पूर्ण

		/* space at the end of the mapping */
		अगर (!loc && !next) अणु
			valid.start = res->start + resource_size(res);
			valid.end = mapping_end;
			space_valid(nd_region, ndd, label_id, res, next, exist,
					to_allocate, &valid);
			available = resource_size(&valid);
			अगर (available)
				loc = ALLOC_AFTER;
		पूर्ण

		अगर (!loc || !available)
			जारी;
		allocate = min(available, n);
		चयन (loc) अणु
		हाल ALLOC_BEFORE:
			अगर (म_भेद(res->name, label_id->id) == 0) अणु
				/* adjust current resource up */
				rc = adjust_resource(res, res->start - allocate,
						resource_size(res) + allocate);
				action = "cur grow up";
			पूर्ण अन्यथा
				action = "allocate";
			अवरोध;
		हाल ALLOC_MID:
			अगर (म_भेद(next->name, label_id->id) == 0) अणु
				/* adjust next resource up */
				rc = adjust_resource(next, next->start
						- allocate, resource_size(next)
						+ allocate);
				new_res = next;
				action = "next grow up";
			पूर्ण अन्यथा अगर (म_भेद(res->name, label_id->id) == 0) अणु
				action = "grow down";
			पूर्ण अन्यथा
				action = "allocate";
			अवरोध;
		हाल ALLOC_AFTER:
			अगर (म_भेद(res->name, label_id->id) == 0)
				action = "grow down";
			अन्यथा
				action = "allocate";
			अवरोध;
		शेष:
			वापस n;
		पूर्ण

		अगर (म_भेद(action, "allocate") == 0) अणु
			/* BLK allocate bottom up */
			अगर (!is_pmem)
				valid.start += available - allocate;

			new_res = nvdimm_allocate_dpa(ndd, label_id,
					valid.start, allocate);
			अगर (!new_res)
				rc = -EBUSY;
		पूर्ण अन्यथा अगर (म_भेद(action, "grow down") == 0) अणु
			/* adjust current resource करोwn */
			rc = adjust_resource(res, res->start, resource_size(res)
					+ allocate);
			अगर (rc == 0)
				res->flags |= DPA_RESOURCE_ADJUSTED;
		पूर्ण

		अगर (!new_res)
			new_res = res;

		nd_dbg_dpa(nd_region, ndd, new_res, "%s(%d) %d\n",
				action, loc, rc);

		अगर (rc)
			वापस n;

		n -= allocate;
		अगर (n) अणु
			/*
			 * Retry scan with newly inserted resources.
			 * For example, अगर we did an ALLOC_BEFORE
			 * insertion there may also have been space
			 * available क्रम an ALLOC_AFTER insertion, so we
			 * need to check this same resource again
			 */
			जाओ retry;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण

	/*
	 * If we allocated nothing in the BLK हाल it may be because we are in
	 * an initial "pmem-reserve pass".  Only करो an initial BLK allocation
	 * when none of the DPA space is reserved.
	 */
	अगर ((is_pmem || !ndd->dpa.child) && n == to_allocate)
		वापस init_dpa_allocation(label_id, nd_region, nd_mapping, n);
	वापस n;
पूर्ण

अटल पूर्णांक merge_dpa(काष्ठा nd_region *nd_region,
		काष्ठा nd_mapping *nd_mapping, काष्ठा nd_label_id *label_id)
अणु
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	काष्ठा resource *res;

	अगर (म_भेदन("pmem", label_id->id, 4) == 0)
		वापस 0;
 retry:
	क्रम_each_dpa_resource(ndd, res) अणु
		पूर्णांक rc;
		काष्ठा resource *next = res->sibling;
		resource_माप_प्रकार end = res->start + resource_size(res);

		अगर (!next || म_भेद(res->name, label_id->id) != 0
				|| म_भेद(next->name, label_id->id) != 0
				|| end != next->start)
			जारी;
		end += resource_size(next);
		nvdimm_मुक्त_dpa(ndd, next);
		rc = adjust_resource(res, res->start, end - res->start);
		nd_dbg_dpa(nd_region, ndd, res, "merge %d\n", rc);
		अगर (rc)
			वापस rc;
		res->flags |= DPA_RESOURCE_ADJUSTED;
		जाओ retry;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __reserve_मुक्त_pmem(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा nvdimm *nvdimm = data;
	काष्ठा nd_region *nd_region;
	काष्ठा nd_label_id label_id;
	पूर्णांक i;

	अगर (!is_memory(dev))
		वापस 0;

	nd_region = to_nd_region(dev);
	अगर (nd_region->ndr_mappings == 0)
		वापस 0;

	स_रखो(&label_id, 0, माप(label_id));
	म_जोड़ो(label_id.id, "pmem-reserve");
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		resource_माप_प्रकार n, rem = 0;

		अगर (nd_mapping->nvdimm != nvdimm)
			जारी;

		n = nd_pmem_available_dpa(nd_region, nd_mapping, &rem);
		अगर (n == 0)
			वापस 0;
		rem = scan_allocate(nd_region, nd_mapping, &label_id, n);
		dev_WARN_ONCE(&nd_region->dev, rem,
				"pmem reserve underrun: %#llx of %#llx bytes\n",
				(अचिन्हित दीर्घ दीर्घ) n - rem,
				(अचिन्हित दीर्घ दीर्घ) n);
		वापस rem ? -ENXIO : 0;
	पूर्ण

	वापस 0;
पूर्ण

व्योम release_मुक्त_pmem(काष्ठा nvdimm_bus *nvdimm_bus,
		काष्ठा nd_mapping *nd_mapping)
अणु
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	काष्ठा resource *res, *_res;

	क्रम_each_dpa_resource_safe(ndd, res, _res)
		अगर (म_भेद(res->name, "pmem-reserve") == 0)
			nvdimm_मुक्त_dpa(ndd, res);
पूर्ण

अटल पूर्णांक reserve_मुक्त_pmem(काष्ठा nvdimm_bus *nvdimm_bus,
		काष्ठा nd_mapping *nd_mapping)
अणु
	काष्ठा nvdimm *nvdimm = nd_mapping->nvdimm;
	पूर्णांक rc;

	rc = device_क्रम_each_child(&nvdimm_bus->dev, nvdimm,
			__reserve_मुक्त_pmem);
	अगर (rc)
		release_मुक्त_pmem(nvdimm_bus, nd_mapping);
	वापस rc;
पूर्ण

/**
 * grow_dpa_allocation - क्रम each dimm allocate n bytes क्रम @label_id
 * @nd_region: the set of dimms to allocate @n more bytes from
 * @label_id: unique identअगरier क्रम the namespace consuming this dpa range
 * @n: number of bytes per-dimm to add to the existing allocation
 *
 * Assumes resources are ordered.  For BLK regions, first consume
 * BLK-only available DPA मुक्त space, then consume PMEM-aliased DPA
 * space starting at the highest DPA.  For PMEM regions start
 * allocations from the start of an पूर्णांकerleave set and end at the first
 * BLK allocation or the end of the पूर्णांकerleave set, whichever comes
 * first.
 */
अटल पूर्णांक grow_dpa_allocation(काष्ठा nd_region *nd_region,
		काष्ठा nd_label_id *label_id, resource_माप_प्रकार n)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(&nd_region->dev);
	bool is_pmem = म_भेदन(label_id->id, "pmem", 4) == 0;
	पूर्णांक i;

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		resource_माप_प्रकार rem = n;
		पूर्णांक rc, j;

		/*
		 * In the BLK हाल try once with all unallocated PMEM
		 * reserved, and once without
		 */
		क्रम (j = is_pmem; j < 2; j++) अणु
			bool blk_only = j == 0;

			अगर (blk_only) अणु
				rc = reserve_मुक्त_pmem(nvdimm_bus, nd_mapping);
				अगर (rc)
					वापस rc;
			पूर्ण
			rem = scan_allocate(nd_region, nd_mapping,
					label_id, rem);
			अगर (blk_only)
				release_मुक्त_pmem(nvdimm_bus, nd_mapping);

			/* try again and allow encroachments पूर्णांकo PMEM */
			अगर (rem == 0)
				अवरोध;
		पूर्ण

		dev_WARN_ONCE(&nd_region->dev, rem,
				"allocation underrun: %#llx of %#llx bytes\n",
				(अचिन्हित दीर्घ दीर्घ) n - rem,
				(अचिन्हित दीर्घ दीर्घ) n);
		अगर (rem)
			वापस -ENXIO;

		rc = merge_dpa(nd_region, nd_mapping, label_id);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nd_namespace_pmem_set_resource(काष्ठा nd_region *nd_region,
		काष्ठा nd_namespace_pmem *nspm, resource_माप_प्रकार size)
अणु
	काष्ठा resource *res = &nspm->nsio.res;
	resource_माप_प्रकार offset = 0;

	अगर (size && !nspm->uuid) अणु
		WARN_ON_ONCE(1);
		size = 0;
	पूर्ण

	अगर (size && nspm->uuid) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[0];
		काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
		काष्ठा nd_label_id label_id;
		काष्ठा resource *res;

		अगर (!ndd) अणु
			size = 0;
			जाओ out;
		पूर्ण

		nd_label_gen_id(&label_id, nspm->uuid, 0);

		/* calculate a spa offset from the dpa allocation offset */
		क्रम_each_dpa_resource(ndd, res)
			अगर (म_भेद(res->name, label_id.id) == 0) अणु
				offset = (res->start - nd_mapping->start)
					* nd_region->ndr_mappings;
				जाओ out;
			पूर्ण

		WARN_ON_ONCE(1);
		size = 0;
	पूर्ण

 out:
	res->start = nd_region->ndr_start + offset;
	res->end = res->start + size - 1;
पूर्ण

अटल bool uuid_not_set(स्थिर u8 *uuid, काष्ठा device *dev, स्थिर अक्षर *where)
अणु
	अगर (!uuid) अणु
		dev_dbg(dev, "%s: uuid not set\n", where);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल sमाप_प्रकार __size_store(काष्ठा device *dev, अचिन्हित दीर्घ दीर्घ val)
अणु
	resource_माप_प्रकार allocated = 0, available = 0;
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	काष्ठा nd_namespace_common *ndns = to_ndns(dev);
	काष्ठा nd_mapping *nd_mapping;
	काष्ठा nvdimm_drvdata *ndd;
	काष्ठा nd_label_id label_id;
	u32 flags = 0, reमुख्यder;
	पूर्णांक rc, i, id = -1;
	u8 *uuid = शून्य;

	अगर (dev->driver || ndns->claim)
		वापस -EBUSY;

	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		uuid = nspm->uuid;
		id = nspm->id;
	पूर्ण अन्यथा अगर (is_namespace_blk(dev)) अणु
		काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		uuid = nsblk->uuid;
		flags = NSLABEL_FLAG_LOCAL;
		id = nsblk->id;
	पूर्ण

	/*
	 * We need a uuid क्रम the allocation-label and dimm(s) on which
	 * to store the label.
	 */
	अगर (uuid_not_set(uuid, dev, __func__))
		वापस -ENXIO;
	अगर (nd_region->ndr_mappings == 0) अणु
		dev_dbg(dev, "not associated with dimm(s)\n");
		वापस -ENXIO;
	पूर्ण

	भाग_u64_rem(val, nd_region->align, &reमुख्यder);
	अगर (reमुख्यder) अणु
		dev_dbg(dev, "%llu is not %ldK aligned\n", val,
				nd_region->align / SZ_1K);
		वापस -EINVAL;
	पूर्ण

	nd_label_gen_id(&label_id, uuid, flags);
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		nd_mapping = &nd_region->mapping[i];
		ndd = to_ndd(nd_mapping);

		/*
		 * All dimms in an पूर्णांकerleave set, or the base dimm क्रम a blk
		 * region, need to be enabled क्रम the size to be changed.
		 */
		अगर (!ndd)
			वापस -ENXIO;

		allocated += nvdimm_allocated_dpa(ndd, &label_id);
	पूर्ण
	available = nd_region_allocatable_dpa(nd_region);

	अगर (val > available + allocated)
		वापस -ENOSPC;

	अगर (val == allocated)
		वापस 0;

	val = भाग_u64(val, nd_region->ndr_mappings);
	allocated = भाग_u64(allocated, nd_region->ndr_mappings);
	अगर (val < allocated)
		rc = shrink_dpa_allocation(nd_region, &label_id,
				allocated - val);
	अन्यथा
		rc = grow_dpa_allocation(nd_region, &label_id, val - allocated);

	अगर (rc)
		वापस rc;

	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		nd_namespace_pmem_set_resource(nd_region, nspm,
				val * nd_region->ndr_mappings);
	पूर्ण

	/*
	 * Try to delete the namespace अगर we deleted all of its
	 * allocation, this is not the seed or 0th device क्रम the
	 * region, and it is not actively claimed by a btt, pfn, or dax
	 * instance.
	 */
	अगर (val == 0 && id != 0 && nd_region->ns_seed != dev && !ndns->claim)
		nd_device_unरेजिस्टर(dev, ND_ASYNC);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार size_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	अचिन्हित दीर्घ दीर्घ val;
	u8 **uuid = शून्य;
	पूर्णांक rc;

	rc = kम_से_अदीर्घl(buf, 0, &val);
	अगर (rc)
		वापस rc;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	रुको_nvdimm_bus_probe_idle(dev);
	rc = __size_store(dev, val);
	अगर (rc >= 0)
		rc = nd_namespace_label_update(nd_region, dev);

	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		uuid = &nspm->uuid;
	पूर्ण अन्यथा अगर (is_namespace_blk(dev)) अणु
		काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		uuid = &nsblk->uuid;
	पूर्ण

	अगर (rc == 0 && val == 0 && uuid) अणु
		/* setting size zero == 'delete namespace' */
		kमुक्त(*uuid);
		*uuid = शून्य;
	पूर्ण

	dev_dbg(dev, "%llx %s (%d)\n", val, rc < 0 ? "fail" : "success", rc);

	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस rc < 0 ? rc : len;
पूर्ण

resource_माप_प्रकार __nvdimm_namespace_capacity(काष्ठा nd_namespace_common *ndns)
अणु
	काष्ठा device *dev = &ndns->dev;

	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		वापस resource_size(&nspm->nsio.res);
	पूर्ण अन्यथा अगर (is_namespace_blk(dev)) अणु
		वापस nd_namespace_blk_size(to_nd_namespace_blk(dev));
	पूर्ण अन्यथा अगर (is_namespace_io(dev)) अणु
		काष्ठा nd_namespace_io *nsio = to_nd_namespace_io(dev);

		वापस resource_size(&nsio->res);
	पूर्ण अन्यथा
		WARN_ONCE(1, "unknown namespace type\n");
	वापस 0;
पूर्ण

resource_माप_प्रकार nvdimm_namespace_capacity(काष्ठा nd_namespace_common *ndns)
अणु
	resource_माप_प्रकार size;

	nvdimm_bus_lock(&ndns->dev);
	size = __nvdimm_namespace_capacity(ndns);
	nvdimm_bus_unlock(&ndns->dev);

	वापस size;
पूर्ण
EXPORT_SYMBOL(nvdimm_namespace_capacity);

bool nvdimm_namespace_locked(काष्ठा nd_namespace_common *ndns)
अणु
	पूर्णांक i;
	bool locked = false;
	काष्ठा device *dev = &ndns->dev;
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm *nvdimm = nd_mapping->nvdimm;

		अगर (test_bit(NDD_LOCKED, &nvdimm->flags)) अणु
			dev_dbg(dev, "%s locked\n", nvdimm_name(nvdimm));
			locked = true;
		पूर्ण
	पूर्ण
	वापस locked;
पूर्ण
EXPORT_SYMBOL(nvdimm_namespace_locked);

अटल sमाप_प्रकार size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n", (अचिन्हित दीर्घ दीर्घ)
			nvdimm_namespace_capacity(to_ndns(dev)));
पूर्ण
अटल DEVICE_ATTR(size, 0444, size_show, size_store);

अटल u8 *namespace_to_uuid(काष्ठा device *dev)
अणु
	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		वापस nspm->uuid;
	पूर्ण अन्यथा अगर (is_namespace_blk(dev)) अणु
		काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		वापस nsblk->uuid;
	पूर्ण अन्यथा
		वापस ERR_PTR(-ENXIO);
पूर्ण

अटल sमाप_प्रकार uuid_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u8 *uuid = namespace_to_uuid(dev);

	अगर (IS_ERR(uuid))
		वापस PTR_ERR(uuid);
	अगर (uuid)
		वापस प्र_लिखो(buf, "%pUb\n", uuid);
	वापस प्र_लिखो(buf, "\n");
पूर्ण

/**
 * namespace_update_uuid - check क्रम a unique uuid and whether we're "renaming"
 * @nd_region: parent region so we can updates all dimms in the set
 * @dev: namespace type क्रम generating label_id
 * @new_uuid: incoming uuid
 * @old_uuid: reference to the uuid storage location in the namespace object
 */
अटल पूर्णांक namespace_update_uuid(काष्ठा nd_region *nd_region,
		काष्ठा device *dev, u8 *new_uuid, u8 **old_uuid)
अणु
	u32 flags = is_namespace_blk(dev) ? NSLABEL_FLAG_LOCAL : 0;
	काष्ठा nd_label_id old_label_id;
	काष्ठा nd_label_id new_label_id;
	पूर्णांक i;

	अगर (!nd_is_uuid_unique(dev, new_uuid))
		वापस -EINVAL;

	अगर (*old_uuid == शून्य)
		जाओ out;

	/*
	 * If we've already written a label with this uuid, then it's
	 * too late to नाम because we can't reliably update the uuid
	 * without losing the old namespace.  Userspace must delete this
	 * namespace to abanकरोn the old uuid.
	 */
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];

		/*
		 * This check by itself is sufficient because old_uuid
		 * would be शून्य above अगर this uuid did not exist in the
		 * currently written set.
		 *
		 * FIXME: can we delete uuid with zero dpa allocated?
		 */
		अगर (list_empty(&nd_mapping->labels))
			वापस -EBUSY;
	पूर्ण

	nd_label_gen_id(&old_label_id, *old_uuid, flags);
	nd_label_gen_id(&new_label_id, new_uuid, flags);
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
		काष्ठा nd_label_ent *label_ent;
		काष्ठा resource *res;

		क्रम_each_dpa_resource(ndd, res)
			अगर (म_भेद(res->name, old_label_id.id) == 0)
				प्र_लिखो((व्योम *) res->name, "%s",
						new_label_id.id);

		mutex_lock(&nd_mapping->lock);
		list_क्रम_each_entry(label_ent, &nd_mapping->labels, list) अणु
			काष्ठा nd_namespace_label *nd_label = label_ent->label;
			काष्ठा nd_label_id label_id;

			अगर (!nd_label)
				जारी;
			nd_label_gen_id(&label_id, nd_label->uuid,
					__le32_to_cpu(nd_label->flags));
			अगर (म_भेद(old_label_id.id, label_id.id) == 0)
				set_bit(ND_LABEL_REAP, &label_ent->flags);
		पूर्ण
		mutex_unlock(&nd_mapping->lock);
	पूर्ण
	kमुक्त(*old_uuid);
 out:
	*old_uuid = new_uuid;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार uuid_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	u8 *uuid = शून्य;
	sमाप_प्रकार rc = 0;
	u8 **ns_uuid;

	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		ns_uuid = &nspm->uuid;
	पूर्ण अन्यथा अगर (is_namespace_blk(dev)) अणु
		काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		ns_uuid = &nsblk->uuid;
	पूर्ण अन्यथा
		वापस -ENXIO;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	रुको_nvdimm_bus_probe_idle(dev);
	अगर (to_ndns(dev)->claim)
		rc = -EBUSY;
	अगर (rc >= 0)
		rc = nd_uuid_store(dev, &uuid, buf, len);
	अगर (rc >= 0)
		rc = namespace_update_uuid(nd_region, dev, uuid, ns_uuid);
	अगर (rc >= 0)
		rc = nd_namespace_label_update(nd_region, dev);
	अन्यथा
		kमुक्त(uuid);
	dev_dbg(dev, "result: %zd wrote: %s%s", rc, buf,
			buf[len - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस rc < 0 ? rc : len;
पूर्ण
अटल DEVICE_ATTR_RW(uuid);

अटल sमाप_प्रकार resource_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा resource *res;

	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		res = &nspm->nsio.res;
	पूर्ण अन्यथा अगर (is_namespace_io(dev)) अणु
		काष्ठा nd_namespace_io *nsio = to_nd_namespace_io(dev);

		res = &nsio->res;
	पूर्ण अन्यथा
		वापस -ENXIO;

	/* no address to convey अगर the namespace has no allocation */
	अगर (resource_size(res) == 0)
		वापस -ENXIO;
	वापस प्र_लिखो(buf, "%#llx\n", (अचिन्हित दीर्घ दीर्घ) res->start);
पूर्ण
अटल DEVICE_ATTR_ADMIN_RO(resource);

अटल स्थिर अचिन्हित दीर्घ blk_lbasize_supported[] = अणु 512, 520, 528,
	4096, 4104, 4160, 4224, 0 पूर्ण;

अटल स्थिर अचिन्हित दीर्घ pmem_lbasize_supported[] = अणु 512, 4096, 0 पूर्ण;

अटल sमाप_प्रकार sector_size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अगर (is_namespace_blk(dev)) अणु
		काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		वापस nd_size_select_show(nsblk->lbasize,
				blk_lbasize_supported, buf);
	पूर्ण

	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		वापस nd_size_select_show(nspm->lbasize,
				pmem_lbasize_supported, buf);
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल sमाप_प्रकार sector_size_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	स्थिर अचिन्हित दीर्घ *supported;
	अचिन्हित दीर्घ *lbasize;
	sमाप_प्रकार rc = 0;

	अगर (is_namespace_blk(dev)) अणु
		काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		lbasize = &nsblk->lbasize;
		supported = blk_lbasize_supported;
	पूर्ण अन्यथा अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		lbasize = &nspm->lbasize;
		supported = pmem_lbasize_supported;
	पूर्ण अन्यथा
		वापस -ENXIO;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	अगर (to_ndns(dev)->claim)
		rc = -EBUSY;
	अगर (rc >= 0)
		rc = nd_size_select_store(dev, buf, lbasize, supported);
	अगर (rc >= 0)
		rc = nd_namespace_label_update(nd_region, dev);
	dev_dbg(dev, "result: %zd %s: %s%s", rc, rc < 0 ? "tried" : "wrote",
			buf, buf[len - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस rc ? rc : len;
पूर्ण
अटल DEVICE_ATTR_RW(sector_size);

अटल sमाप_प्रकार dpa_extents_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	काष्ठा nd_label_id label_id;
	पूर्णांक count = 0, i;
	u8 *uuid = शून्य;
	u32 flags = 0;

	nvdimm_bus_lock(dev);
	अगर (is_namespace_pmem(dev)) अणु
		काष्ठा nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		uuid = nspm->uuid;
		flags = 0;
	पूर्ण अन्यथा अगर (is_namespace_blk(dev)) अणु
		काष्ठा nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		uuid = nsblk->uuid;
		flags = NSLABEL_FLAG_LOCAL;
	पूर्ण

	अगर (!uuid)
		जाओ out;

	nd_label_gen_id(&label_id, uuid, flags);
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
		काष्ठा resource *res;

		क्रम_each_dpa_resource(ndd, res)
			अगर (म_भेद(res->name, label_id.id) == 0)
				count++;
	पूर्ण
 out:
	nvdimm_bus_unlock(dev);

	वापस प्र_लिखो(buf, "%d\n", count);
पूर्ण
अटल DEVICE_ATTR_RO(dpa_extents);

अटल पूर्णांक btt_claim_class(काष्ठा device *dev)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	पूर्णांक i, loop_biपंचांगask = 0;

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
		काष्ठा nd_namespace_index *nsindex;

		/*
		 * If any of the DIMMs करो not support labels the only
		 * possible BTT क्रमmat is v1.
		 */
		अगर (!ndd) अणु
			loop_biपंचांगask = 0;
			अवरोध;
		पूर्ण

		nsindex = to_namespace_index(ndd, ndd->ns_current);
		अगर (nsindex == शून्य)
			loop_biपंचांगask |= 1;
		अन्यथा अणु
			/* check whether existing labels are v1.1 or v1.2 */
			अगर (__le16_to_cpu(nsindex->major) == 1
					&& __le16_to_cpu(nsindex->minor) == 1)
				loop_biपंचांगask |= 2;
			अन्यथा
				loop_biपंचांगask |= 4;
		पूर्ण
	पूर्ण
	/*
	 * If nsindex is null loop_biपंचांगask's bit 0 will be set, and अगर an index
	 * block is found, a v1.1 label क्रम any mapping will set bit 1, and a
	 * v1.2 label will set bit 2.
	 *
	 * At the end of the loop, at most one of the three bits must be set.
	 * If multiple bits were set, it means the dअगरferent mappings disagree
	 * about their labels, and this must be cleaned up first.
	 *
	 * If all the label index blocks are found to agree, nsindex of शून्य
	 * implies labels haven't been initialized yet, and when they will,
	 * they will be of the 1.2 क्रमmat, so we can assume BTT2.0
	 *
	 * If 1.1 labels are found, we enक्रमce BTT1.1, and अगर 1.2 labels are
	 * found, we enक्रमce BTT2.0
	 *
	 * If the loop was never entered, शेष to BTT1.1 (legacy namespaces)
	 */
	चयन (loop_biपंचांगask) अणु
	हाल 0:
	हाल 2:
		वापस NVDIMM_CCLASS_BTT;
	हाल 1:
	हाल 4:
		वापस NVDIMM_CCLASS_BTT2;
	शेष:
		वापस -ENXIO;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार holder_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_namespace_common *ndns = to_ndns(dev);
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	rc = प्र_लिखो(buf, "%s\n", ndns->claim ? dev_name(ndns->claim) : "");
	nd_device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(holder);

अटल पूर्णांक __holder_class_store(काष्ठा device *dev, स्थिर अक्षर *buf)
अणु
	काष्ठा nd_namespace_common *ndns = to_ndns(dev);

	अगर (dev->driver || ndns->claim)
		वापस -EBUSY;

	अगर (sysfs_streq(buf, "btt")) अणु
		पूर्णांक rc = btt_claim_class(dev);

		अगर (rc < NVDIMM_CCLASS_NONE)
			वापस rc;
		ndns->claim_class = rc;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "pfn"))
		ndns->claim_class = NVDIMM_CCLASS_PFN;
	अन्यथा अगर (sysfs_streq(buf, "dax"))
		ndns->claim_class = NVDIMM_CCLASS_DAX;
	अन्यथा अगर (sysfs_streq(buf, ""))
		ndns->claim_class = NVDIMM_CCLASS_NONE;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार holder_class_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	पूर्णांक rc;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	रुको_nvdimm_bus_probe_idle(dev);
	rc = __holder_class_store(dev, buf);
	अगर (rc >= 0)
		rc = nd_namespace_label_update(nd_region, dev);
	dev_dbg(dev, "%s(%d)\n", rc < 0 ? "fail " : "", rc);
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस rc < 0 ? rc : len;
पूर्ण

अटल sमाप_प्रकार holder_class_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_namespace_common *ndns = to_ndns(dev);
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	अगर (ndns->claim_class == NVDIMM_CCLASS_NONE)
		rc = प्र_लिखो(buf, "\n");
	अन्यथा अगर ((ndns->claim_class == NVDIMM_CCLASS_BTT) ||
			(ndns->claim_class == NVDIMM_CCLASS_BTT2))
		rc = प्र_लिखो(buf, "btt\n");
	अन्यथा अगर (ndns->claim_class == NVDIMM_CCLASS_PFN)
		rc = प्र_लिखो(buf, "pfn\n");
	अन्यथा अगर (ndns->claim_class == NVDIMM_CCLASS_DAX)
		rc = प्र_लिखो(buf, "dax\n");
	अन्यथा
		rc = प्र_लिखो(buf, "<unknown>\n");
	nd_device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RW(holder_class);

अटल sमाप_प्रकार mode_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_namespace_common *ndns = to_ndns(dev);
	काष्ठा device *claim;
	अक्षर *mode;
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	claim = ndns->claim;
	अगर (claim && is_nd_btt(claim))
		mode = "safe";
	अन्यथा अगर (claim && is_nd_pfn(claim))
		mode = "memory";
	अन्यथा अगर (claim && is_nd_dax(claim))
		mode = "dax";
	अन्यथा अगर (!claim && pmem_should_map_pages(dev))
		mode = "memory";
	अन्यथा
		mode = "raw";
	rc = प्र_लिखो(buf, "%s\n", mode);
	nd_device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(mode);

अटल sमाप_प्रकार क्रमce_raw_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	bool क्रमce_raw;
	पूर्णांक rc = strtobool(buf, &क्रमce_raw);

	अगर (rc)
		वापस rc;

	to_ndns(dev)->क्रमce_raw = क्रमce_raw;
	वापस len;
पूर्ण

अटल sमाप_प्रकार क्रमce_raw_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", to_ndns(dev)->क्रमce_raw);
पूर्ण
अटल DEVICE_ATTR_RW(क्रमce_raw);

अटल काष्ठा attribute *nd_namespace_attributes[] = अणु
	&dev_attr_nstype.attr,
	&dev_attr_size.attr,
	&dev_attr_mode.attr,
	&dev_attr_uuid.attr,
	&dev_attr_holder.attr,
	&dev_attr_resource.attr,
	&dev_attr_alt_name.attr,
	&dev_attr_क्रमce_raw.attr,
	&dev_attr_sector_size.attr,
	&dev_attr_dpa_extents.attr,
	&dev_attr_holder_class.attr,
	शून्य,
पूर्ण;

अटल umode_t namespace_visible(काष्ठा kobject *kobj,
		काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);

	अगर (a == &dev_attr_resource.attr && is_namespace_blk(dev))
		वापस 0;

	अगर (is_namespace_pmem(dev) || is_namespace_blk(dev)) अणु
		अगर (a == &dev_attr_size.attr)
			वापस 0644;

		वापस a->mode;
	पूर्ण

	/* base is_namespace_io() attributes */
	अगर (a == &dev_attr_nstype.attr || a == &dev_attr_size.attr ||
	    a == &dev_attr_holder.attr || a == &dev_attr_holder_class.attr ||
	    a == &dev_attr_क्रमce_raw.attr || a == &dev_attr_mode.attr ||
	    a == &dev_attr_resource.attr)
		वापस a->mode;

	वापस 0;
पूर्ण

अटल काष्ठा attribute_group nd_namespace_attribute_group = अणु
	.attrs = nd_namespace_attributes,
	.is_visible = namespace_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *nd_namespace_attribute_groups[] = अणु
	&nd_device_attribute_group,
	&nd_namespace_attribute_group,
	&nd_numa_attribute_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा device_type namespace_io_device_type = अणु
	.name = "nd_namespace_io",
	.release = namespace_io_release,
	.groups = nd_namespace_attribute_groups,
पूर्ण;

अटल स्थिर काष्ठा device_type namespace_pmem_device_type = अणु
	.name = "nd_namespace_pmem",
	.release = namespace_pmem_release,
	.groups = nd_namespace_attribute_groups,
पूर्ण;

अटल स्थिर काष्ठा device_type namespace_blk_device_type = अणु
	.name = "nd_namespace_blk",
	.release = namespace_blk_release,
	.groups = nd_namespace_attribute_groups,
पूर्ण;

अटल bool is_namespace_pmem(स्थिर काष्ठा device *dev)
अणु
	वापस dev ? dev->type == &namespace_pmem_device_type : false;
पूर्ण

अटल bool is_namespace_blk(स्थिर काष्ठा device *dev)
अणु
	वापस dev ? dev->type == &namespace_blk_device_type : false;
पूर्ण

अटल bool is_namespace_io(स्थिर काष्ठा device *dev)
अणु
	वापस dev ? dev->type == &namespace_io_device_type : false;
पूर्ण

काष्ठा nd_namespace_common *nvdimm_namespace_common_probe(काष्ठा device *dev)
अणु
	काष्ठा nd_btt *nd_btt = is_nd_btt(dev) ? to_nd_btt(dev) : शून्य;
	काष्ठा nd_pfn *nd_pfn = is_nd_pfn(dev) ? to_nd_pfn(dev) : शून्य;
	काष्ठा nd_dax *nd_dax = is_nd_dax(dev) ? to_nd_dax(dev) : शून्य;
	काष्ठा nd_namespace_common *ndns = शून्य;
	resource_माप_प्रकार size;

	अगर (nd_btt || nd_pfn || nd_dax) अणु
		अगर (nd_btt)
			ndns = nd_btt->ndns;
		अन्यथा अगर (nd_pfn)
			ndns = nd_pfn->ndns;
		अन्यथा अगर (nd_dax)
			ndns = nd_dax->nd_pfn.ndns;

		अगर (!ndns)
			वापस ERR_PTR(-ENODEV);

		/*
		 * Flush any in-progess probes / removals in the driver
		 * क्रम the raw personality of this namespace.
		 */
		nd_device_lock(&ndns->dev);
		nd_device_unlock(&ndns->dev);
		अगर (ndns->dev.driver) अणु
			dev_dbg(&ndns->dev, "is active, can't bind %s\n",
					dev_name(dev));
			वापस ERR_PTR(-EBUSY);
		पूर्ण
		अगर (dev_WARN_ONCE(&ndns->dev, ndns->claim != dev,
					"host (%s) vs claim (%s) mismatch\n",
					dev_name(dev),
					dev_name(ndns->claim)))
			वापस ERR_PTR(-ENXIO);
	पूर्ण अन्यथा अणु
		ndns = to_ndns(dev);
		अगर (ndns->claim) अणु
			dev_dbg(dev, "claimed by %s, failing probe\n",
				dev_name(ndns->claim));

			वापस ERR_PTR(-ENXIO);
		पूर्ण
	पूर्ण

	अगर (nvdimm_namespace_locked(ndns))
		वापस ERR_PTR(-EACCES);

	size = nvdimm_namespace_capacity(ndns);
	अगर (size < ND_MIN_NAMESPACE_SIZE) अणु
		dev_dbg(&ndns->dev, "%pa, too small must be at least %#x\n",
				&size, ND_MIN_NAMESPACE_SIZE);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	/*
	 * Note, alignment validation क्रम fsdax and devdax mode
	 * namespaces happens in nd_pfn_validate() where infoblock
	 * padding parameters can be applied.
	 */
	अगर (pmem_should_map_pages(dev)) अणु
		काष्ठा nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);
		काष्ठा resource *res = &nsio->res;

		अगर (!IS_ALIGNED(res->start | (res->end + 1),
					memremap_compat_align())) अणु
			dev_err(&ndns->dev, "%pr misaligned, unable to map\n", res);
			वापस ERR_PTR(-EOPNOTSUPP);
		पूर्ण
	पूर्ण

	अगर (is_namespace_pmem(&ndns->dev)) अणु
		काष्ठा nd_namespace_pmem *nspm;

		nspm = to_nd_namespace_pmem(&ndns->dev);
		अगर (uuid_not_set(nspm->uuid, &ndns->dev, __func__))
			वापस ERR_PTR(-ENODEV);
	पूर्ण अन्यथा अगर (is_namespace_blk(&ndns->dev)) अणु
		काष्ठा nd_namespace_blk *nsblk;

		nsblk = to_nd_namespace_blk(&ndns->dev);
		अगर (uuid_not_set(nsblk->uuid, &ndns->dev, __func__))
			वापस ERR_PTR(-ENODEV);
		अगर (!nsblk->lbasize) अणु
			dev_dbg(&ndns->dev, "sector size not set\n");
			वापस ERR_PTR(-ENODEV);
		पूर्ण
		अगर (!nd_namespace_blk_validate(nsblk))
			वापस ERR_PTR(-ENODEV);
	पूर्ण

	वापस ndns;
पूर्ण
EXPORT_SYMBOL(nvdimm_namespace_common_probe);

पूर्णांक devm_namespace_enable(काष्ठा device *dev, काष्ठा nd_namespace_common *ndns,
		resource_माप_प्रकार size)
अणु
	अगर (is_namespace_blk(&ndns->dev))
		वापस 0;
	वापस devm_nsio_enable(dev, to_nd_namespace_io(&ndns->dev), size);
पूर्ण
EXPORT_SYMBOL_GPL(devm_namespace_enable);

व्योम devm_namespace_disable(काष्ठा device *dev, काष्ठा nd_namespace_common *ndns)
अणु
	अगर (is_namespace_blk(&ndns->dev))
		वापस;
	devm_nsio_disable(dev, to_nd_namespace_io(&ndns->dev));
पूर्ण
EXPORT_SYMBOL_GPL(devm_namespace_disable);

अटल काष्ठा device **create_namespace_io(काष्ठा nd_region *nd_region)
अणु
	काष्ठा nd_namespace_io *nsio;
	काष्ठा device *dev, **devs;
	काष्ठा resource *res;

	nsio = kzalloc(माप(*nsio), GFP_KERNEL);
	अगर (!nsio)
		वापस शून्य;

	devs = kसुस्मृति(2, माप(काष्ठा device *), GFP_KERNEL);
	अगर (!devs) अणु
		kमुक्त(nsio);
		वापस शून्य;
	पूर्ण

	dev = &nsio->common.dev;
	dev->type = &namespace_io_device_type;
	dev->parent = &nd_region->dev;
	res = &nsio->res;
	res->name = dev_name(&nd_region->dev);
	res->flags = IORESOURCE_MEM;
	res->start = nd_region->ndr_start;
	res->end = res->start + nd_region->ndr_size - 1;

	devs[0] = dev;
	वापस devs;
पूर्ण

अटल bool has_uuid_at_pos(काष्ठा nd_region *nd_region, u8 *uuid,
		u64 cookie, u16 pos)
अणु
	काष्ठा nd_namespace_label *found = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nd_पूर्णांकerleave_set *nd_set = nd_region->nd_set;
		काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
		काष्ठा nd_label_ent *label_ent;
		bool found_uuid = false;

		list_क्रम_each_entry(label_ent, &nd_mapping->labels, list) अणु
			काष्ठा nd_namespace_label *nd_label = label_ent->label;
			u16 position, nlabel;
			u64 isetcookie;

			अगर (!nd_label)
				जारी;
			isetcookie = __le64_to_cpu(nd_label->isetcookie);
			position = __le16_to_cpu(nd_label->position);
			nlabel = __le16_to_cpu(nd_label->nlabel);

			अगर (isetcookie != cookie)
				जारी;

			अगर (स_भेद(nd_label->uuid, uuid, NSLABEL_UUID_LEN) != 0)
				जारी;

			अगर (namespace_label_has(ndd, type_guid)
					&& !guid_equal(&nd_set->type_guid,
						&nd_label->type_guid)) अणु
				dev_dbg(ndd->dev, "expect type_guid %pUb got %pUb\n",
						&nd_set->type_guid,
						&nd_label->type_guid);
				जारी;
			पूर्ण

			अगर (found_uuid) अणु
				dev_dbg(ndd->dev, "duplicate entry for uuid\n");
				वापस false;
			पूर्ण
			found_uuid = true;
			अगर (nlabel != nd_region->ndr_mappings)
				जारी;
			अगर (position != pos)
				जारी;
			found = nd_label;
			अवरोध;
		पूर्ण
		अगर (found)
			अवरोध;
	पूर्ण
	वापस found != शून्य;
पूर्ण

अटल पूर्णांक select_pmem_id(काष्ठा nd_region *nd_region, u8 *pmem_id)
अणु
	पूर्णांक i;

	अगर (!pmem_id)
		वापस -ENODEV;

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
		काष्ठा nd_namespace_label *nd_label = शून्य;
		u64 hw_start, hw_end, pmem_start, pmem_end;
		काष्ठा nd_label_ent *label_ent;

		lockdep_निश्चित_held(&nd_mapping->lock);
		list_क्रम_each_entry(label_ent, &nd_mapping->labels, list) अणु
			nd_label = label_ent->label;
			अगर (!nd_label)
				जारी;
			अगर (स_भेद(nd_label->uuid, pmem_id, NSLABEL_UUID_LEN) == 0)
				अवरोध;
			nd_label = शून्य;
		पूर्ण

		अगर (!nd_label) अणु
			WARN_ON(1);
			वापस -EINVAL;
		पूर्ण

		/*
		 * Check that this label is compliant with the dpa
		 * range published in NFIT
		 */
		hw_start = nd_mapping->start;
		hw_end = hw_start + nd_mapping->size;
		pmem_start = __le64_to_cpu(nd_label->dpa);
		pmem_end = pmem_start + __le64_to_cpu(nd_label->rawsize);
		अगर (pmem_start >= hw_start && pmem_start < hw_end
				&& pmem_end <= hw_end && pmem_end > hw_start)
			/* pass */;
		अन्यथा अणु
			dev_dbg(&nd_region->dev, "%s invalid label for %pUb\n",
					dev_name(ndd->dev), nd_label->uuid);
			वापस -EINVAL;
		पूर्ण

		/* move recently validated label to the front of the list */
		list_move(&label_ent->list, &nd_mapping->labels);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * create_namespace_pmem - validate पूर्णांकerleave set labelling, retrieve label0
 * @nd_region: region with mappings to validate
 * @nspm: target namespace to create
 * @nd_label: target pmem namespace label to evaluate
 */
अटल काष्ठा device *create_namespace_pmem(काष्ठा nd_region *nd_region,
		काष्ठा nd_namespace_index *nsindex,
		काष्ठा nd_namespace_label *nd_label)
अणु
	u64 cookie = nd_region_पूर्णांकerleave_set_cookie(nd_region, nsindex);
	u64 altcookie = nd_region_पूर्णांकerleave_set_altcookie(nd_region);
	काष्ठा nd_label_ent *label_ent;
	काष्ठा nd_namespace_pmem *nspm;
	काष्ठा nd_mapping *nd_mapping;
	resource_माप_प्रकार size = 0;
	काष्ठा resource *res;
	काष्ठा device *dev;
	पूर्णांक rc = 0;
	u16 i;

	अगर (cookie == 0) अणु
		dev_dbg(&nd_region->dev, "invalid interleave-set-cookie\n");
		वापस ERR_PTR(-ENXIO);
	पूर्ण

	अगर (__le64_to_cpu(nd_label->isetcookie) != cookie) अणु
		dev_dbg(&nd_region->dev, "invalid cookie in label: %pUb\n",
				nd_label->uuid);
		अगर (__le64_to_cpu(nd_label->isetcookie) != altcookie)
			वापस ERR_PTR(-EAGAIN);

		dev_dbg(&nd_region->dev, "valid altcookie in label: %pUb\n",
				nd_label->uuid);
	पूर्ण

	nspm = kzalloc(माप(*nspm), GFP_KERNEL);
	अगर (!nspm)
		वापस ERR_PTR(-ENOMEM);

	nspm->id = -1;
	dev = &nspm->nsio.common.dev;
	dev->type = &namespace_pmem_device_type;
	dev->parent = &nd_region->dev;
	res = &nspm->nsio.res;
	res->name = dev_name(&nd_region->dev);
	res->flags = IORESOURCE_MEM;

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		अगर (has_uuid_at_pos(nd_region, nd_label->uuid, cookie, i))
			जारी;
		अगर (has_uuid_at_pos(nd_region, nd_label->uuid, altcookie, i))
			जारी;
		अवरोध;
	पूर्ण

	अगर (i < nd_region->ndr_mappings) अणु
		काष्ठा nvdimm *nvdimm = nd_region->mapping[i].nvdimm;

		/*
		 * Give up अगर we करोn't find an instance of a uuid at each
		 * position (from 0 to nd_region->ndr_mappings - 1), or अगर we
		 * find a dimm with two instances of the same uuid.
		 */
		dev_err(&nd_region->dev, "%s missing label for %pUb\n",
				nvdimm_name(nvdimm), nd_label->uuid);
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	/*
	 * Fix up each mapping's 'labels' to have the validated pmem label क्रम
	 * that position at labels[0], and शून्य at labels[1].  In the process,
	 * check that the namespace aligns with पूर्णांकerleave-set.  We know
	 * that it करोes not overlap with any blk namespaces by virtue of
	 * the dimm being enabled (i.e. nd_label_reserve_dpa()
	 * succeeded).
	 */
	rc = select_pmem_id(nd_region, nd_label->uuid);
	अगर (rc)
		जाओ err;

	/* Calculate total size and populate namespace properties from label0 */
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_namespace_label *label0;
		काष्ठा nvdimm_drvdata *ndd;

		nd_mapping = &nd_region->mapping[i];
		label_ent = list_first_entry_or_null(&nd_mapping->labels,
				typeof(*label_ent), list);
		label0 = label_ent ? label_ent->label : शून्य;

		अगर (!label0) अणु
			WARN_ON(1);
			जारी;
		पूर्ण

		size += __le64_to_cpu(label0->rawsize);
		अगर (__le16_to_cpu(label0->position) != 0)
			जारी;
		WARN_ON(nspm->alt_name || nspm->uuid);
		nspm->alt_name = kmemdup((व्योम __क्रमce *) label0->name,
				NSLABEL_NAME_LEN, GFP_KERNEL);
		nspm->uuid = kmemdup((व्योम __क्रमce *) label0->uuid,
				NSLABEL_UUID_LEN, GFP_KERNEL);
		nspm->lbasize = __le64_to_cpu(label0->lbasize);
		ndd = to_ndd(nd_mapping);
		अगर (namespace_label_has(ndd, असलtraction_guid))
			nspm->nsio.common.claim_class
				= to_nvdimm_cclass(&label0->असलtraction_guid);

	पूर्ण

	अगर (!nspm->alt_name || !nspm->uuid) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	nd_namespace_pmem_set_resource(nd_region, nspm, size);

	वापस dev;
 err:
	namespace_pmem_release(dev);
	चयन (rc) अणु
	हाल -EINVAL:
		dev_dbg(&nd_region->dev, "invalid label(s)\n");
		अवरोध;
	हाल -ENODEV:
		dev_dbg(&nd_region->dev, "label not found\n");
		अवरोध;
	शेष:
		dev_dbg(&nd_region->dev, "unexpected err: %d\n", rc);
		अवरोध;
	पूर्ण
	वापस ERR_PTR(rc);
पूर्ण

काष्ठा resource *nsblk_add_resource(काष्ठा nd_region *nd_region,
		काष्ठा nvdimm_drvdata *ndd, काष्ठा nd_namespace_blk *nsblk,
		resource_माप_प्रकार start)
अणु
	काष्ठा nd_label_id label_id;
	काष्ठा resource *res;

	nd_label_gen_id(&label_id, nsblk->uuid, NSLABEL_FLAG_LOCAL);
	res = kपुनः_स्मृति(nsblk->res,
			माप(व्योम *) * (nsblk->num_resources + 1),
			GFP_KERNEL);
	अगर (!res)
		वापस शून्य;
	nsblk->res = (काष्ठा resource **) res;
	क्रम_each_dpa_resource(ndd, res)
		अगर (म_भेद(res->name, label_id.id) == 0
				&& res->start == start) अणु
			nsblk->res[nsblk->num_resources++] = res;
			वापस res;
		पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा device *nd_namespace_blk_create(काष्ठा nd_region *nd_region)
अणु
	काष्ठा nd_namespace_blk *nsblk;
	काष्ठा device *dev;

	अगर (!is_nd_blk(&nd_region->dev))
		वापस शून्य;

	nsblk = kzalloc(माप(*nsblk), GFP_KERNEL);
	अगर (!nsblk)
		वापस शून्य;

	dev = &nsblk->common.dev;
	dev->type = &namespace_blk_device_type;
	nsblk->id = ida_simple_get(&nd_region->ns_ida, 0, 0, GFP_KERNEL);
	अगर (nsblk->id < 0) अणु
		kमुक्त(nsblk);
		वापस शून्य;
	पूर्ण
	dev_set_name(dev, "namespace%d.%d", nd_region->id, nsblk->id);
	dev->parent = &nd_region->dev;

	वापस &nsblk->common.dev;
पूर्ण

अटल काष्ठा device *nd_namespace_pmem_create(काष्ठा nd_region *nd_region)
अणु
	काष्ठा nd_namespace_pmem *nspm;
	काष्ठा resource *res;
	काष्ठा device *dev;

	अगर (!is_memory(&nd_region->dev))
		वापस शून्य;

	nspm = kzalloc(माप(*nspm), GFP_KERNEL);
	अगर (!nspm)
		वापस शून्य;

	dev = &nspm->nsio.common.dev;
	dev->type = &namespace_pmem_device_type;
	dev->parent = &nd_region->dev;
	res = &nspm->nsio.res;
	res->name = dev_name(&nd_region->dev);
	res->flags = IORESOURCE_MEM;

	nspm->id = ida_simple_get(&nd_region->ns_ida, 0, 0, GFP_KERNEL);
	अगर (nspm->id < 0) अणु
		kमुक्त(nspm);
		वापस शून्य;
	पूर्ण
	dev_set_name(dev, "namespace%d.%d", nd_region->id, nspm->id);
	nd_namespace_pmem_set_resource(nd_region, nspm, 0);

	वापस dev;
पूर्ण

व्योम nd_region_create_ns_seed(काष्ठा nd_region *nd_region)
अणु
	WARN_ON(!is_nvdimm_bus_locked(&nd_region->dev));

	अगर (nd_region_to_nstype(nd_region) == ND_DEVICE_NAMESPACE_IO)
		वापस;

	अगर (is_nd_blk(&nd_region->dev))
		nd_region->ns_seed = nd_namespace_blk_create(nd_region);
	अन्यथा
		nd_region->ns_seed = nd_namespace_pmem_create(nd_region);

	/*
	 * Seed creation failures are not fatal, provisioning is simply
	 * disabled until memory becomes available
	 */
	अगर (!nd_region->ns_seed)
		dev_err(&nd_region->dev, "failed to create %s namespace\n",
				is_nd_blk(&nd_region->dev) ? "blk" : "pmem");
	अन्यथा
		nd_device_रेजिस्टर(nd_region->ns_seed);
पूर्ण

व्योम nd_region_create_dax_seed(काष्ठा nd_region *nd_region)
अणु
	WARN_ON(!is_nvdimm_bus_locked(&nd_region->dev));
	nd_region->dax_seed = nd_dax_create(nd_region);
	/*
	 * Seed creation failures are not fatal, provisioning is simply
	 * disabled until memory becomes available
	 */
	अगर (!nd_region->dax_seed)
		dev_err(&nd_region->dev, "failed to create dax namespace\n");
पूर्ण

व्योम nd_region_create_pfn_seed(काष्ठा nd_region *nd_region)
अणु
	WARN_ON(!is_nvdimm_bus_locked(&nd_region->dev));
	nd_region->pfn_seed = nd_pfn_create(nd_region);
	/*
	 * Seed creation failures are not fatal, provisioning is simply
	 * disabled until memory becomes available
	 */
	अगर (!nd_region->pfn_seed)
		dev_err(&nd_region->dev, "failed to create pfn namespace\n");
पूर्ण

व्योम nd_region_create_btt_seed(काष्ठा nd_region *nd_region)
अणु
	WARN_ON(!is_nvdimm_bus_locked(&nd_region->dev));
	nd_region->btt_seed = nd_btt_create(nd_region);
	/*
	 * Seed creation failures are not fatal, provisioning is simply
	 * disabled until memory becomes available
	 */
	अगर (!nd_region->btt_seed)
		dev_err(&nd_region->dev, "failed to create btt namespace\n");
पूर्ण

अटल पूर्णांक add_namespace_resource(काष्ठा nd_region *nd_region,
		काष्ठा nd_namespace_label *nd_label, काष्ठा device **devs,
		पूर्णांक count)
अणु
	काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[0];
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		u8 *uuid = namespace_to_uuid(devs[i]);
		काष्ठा resource *res;

		अगर (IS_ERR_OR_शून्य(uuid)) अणु
			WARN_ON(1);
			जारी;
		पूर्ण

		अगर (स_भेद(uuid, nd_label->uuid, NSLABEL_UUID_LEN) != 0)
			जारी;
		अगर (is_namespace_blk(devs[i])) अणु
			res = nsblk_add_resource(nd_region, ndd,
					to_nd_namespace_blk(devs[i]),
					__le64_to_cpu(nd_label->dpa));
			अगर (!res)
				वापस -ENXIO;
			nd_dbg_dpa(nd_region, ndd, res, "%d assign\n", count);
		पूर्ण अन्यथा अणु
			dev_err(&nd_region->dev,
					"error: conflicting extents for uuid: %pUb\n",
					nd_label->uuid);
			वापस -ENXIO;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल काष्ठा device *create_namespace_blk(काष्ठा nd_region *nd_region,
		काष्ठा nd_namespace_label *nd_label, पूर्णांक count)
अणु

	काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[0];
	काष्ठा nd_पूर्णांकerleave_set *nd_set = nd_region->nd_set;
	काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	काष्ठा nd_namespace_blk *nsblk;
	अक्षर name[NSLABEL_NAME_LEN];
	काष्ठा device *dev = शून्य;
	काष्ठा resource *res;

	अगर (namespace_label_has(ndd, type_guid)) अणु
		अगर (!guid_equal(&nd_set->type_guid, &nd_label->type_guid)) अणु
			dev_dbg(ndd->dev, "expect type_guid %pUb got %pUb\n",
					&nd_set->type_guid,
					&nd_label->type_guid);
			वापस ERR_PTR(-EAGAIN);
		पूर्ण

		अगर (nd_label->isetcookie != __cpu_to_le64(nd_set->cookie2)) अणु
			dev_dbg(ndd->dev, "expect cookie %#llx got %#llx\n",
					nd_set->cookie2,
					__le64_to_cpu(nd_label->isetcookie));
			वापस ERR_PTR(-EAGAIN);
		पूर्ण
	पूर्ण

	nsblk = kzalloc(माप(*nsblk), GFP_KERNEL);
	अगर (!nsblk)
		वापस ERR_PTR(-ENOMEM);
	dev = &nsblk->common.dev;
	dev->type = &namespace_blk_device_type;
	dev->parent = &nd_region->dev;
	nsblk->id = -1;
	nsblk->lbasize = __le64_to_cpu(nd_label->lbasize);
	nsblk->uuid = kmemdup(nd_label->uuid, NSLABEL_UUID_LEN,
			GFP_KERNEL);
	अगर (namespace_label_has(ndd, असलtraction_guid))
		nsblk->common.claim_class
			= to_nvdimm_cclass(&nd_label->असलtraction_guid);
	अगर (!nsblk->uuid)
		जाओ blk_err;
	स_नकल(name, nd_label->name, NSLABEL_NAME_LEN);
	अगर (name[0]) अणु
		nsblk->alt_name = kmemdup(name, NSLABEL_NAME_LEN,
				GFP_KERNEL);
		अगर (!nsblk->alt_name)
			जाओ blk_err;
	पूर्ण
	res = nsblk_add_resource(nd_region, ndd, nsblk,
			__le64_to_cpu(nd_label->dpa));
	अगर (!res)
		जाओ blk_err;
	nd_dbg_dpa(nd_region, ndd, res, "%d: assign\n", count);
	वापस dev;
 blk_err:
	namespace_blk_release(dev);
	वापस ERR_PTR(-ENXIO);
पूर्ण

अटल पूर्णांक cmp_dpa(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा device *dev_a = *(स्थिर काष्ठा device **) a;
	स्थिर काष्ठा device *dev_b = *(स्थिर काष्ठा device **) b;
	काष्ठा nd_namespace_blk *nsblk_a, *nsblk_b;
	काष्ठा nd_namespace_pmem *nspm_a, *nspm_b;

	अगर (is_namespace_io(dev_a))
		वापस 0;

	अगर (is_namespace_blk(dev_a)) अणु
		nsblk_a = to_nd_namespace_blk(dev_a);
		nsblk_b = to_nd_namespace_blk(dev_b);

		वापस स_भेद(&nsblk_a->res[0]->start, &nsblk_b->res[0]->start,
				माप(resource_माप_प्रकार));
	पूर्ण

	nspm_a = to_nd_namespace_pmem(dev_a);
	nspm_b = to_nd_namespace_pmem(dev_b);

	वापस स_भेद(&nspm_a->nsio.res.start, &nspm_b->nsio.res.start,
			माप(resource_माप_प्रकार));
पूर्ण

अटल काष्ठा device **scan_labels(काष्ठा nd_region *nd_region)
अणु
	पूर्णांक i, count = 0;
	काष्ठा device *dev, **devs = शून्य;
	काष्ठा nd_label_ent *label_ent, *e;
	काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[0];
	resource_माप_प्रकार map_end = nd_mapping->start + nd_mapping->size - 1;

	/* "safe" because create_namespace_pmem() might list_move() label_ent */
	list_क्रम_each_entry_safe(label_ent, e, &nd_mapping->labels, list) अणु
		काष्ठा nd_namespace_label *nd_label = label_ent->label;
		काष्ठा device **__devs;
		u32 flags;

		अगर (!nd_label)
			जारी;
		flags = __le32_to_cpu(nd_label->flags);
		अगर (is_nd_blk(&nd_region->dev)
				== !!(flags & NSLABEL_FLAG_LOCAL))
			/* pass, region matches label type */;
		अन्यथा
			जारी;

		/* skip labels that describe extents outside of the region */
		अगर (__le64_to_cpu(nd_label->dpa) < nd_mapping->start ||
		    __le64_to_cpu(nd_label->dpa) > map_end)
				जारी;

		i = add_namespace_resource(nd_region, nd_label, devs, count);
		अगर (i < 0)
			जाओ err;
		अगर (i < count)
			जारी;
		__devs = kसुस्मृति(count + 2, माप(dev), GFP_KERNEL);
		अगर (!__devs)
			जाओ err;
		स_नकल(__devs, devs, माप(dev) * count);
		kमुक्त(devs);
		devs = __devs;

		अगर (is_nd_blk(&nd_region->dev))
			dev = create_namespace_blk(nd_region, nd_label, count);
		अन्यथा अणु
			काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
			काष्ठा nd_namespace_index *nsindex;

			nsindex = to_namespace_index(ndd, ndd->ns_current);
			dev = create_namespace_pmem(nd_region, nsindex, nd_label);
		पूर्ण

		अगर (IS_ERR(dev)) अणु
			चयन (PTR_ERR(dev)) अणु
			हाल -EAGAIN:
				/* skip invalid labels */
				जारी;
			हाल -ENODEV:
				/* fallthrough to seed creation */
				अवरोध;
			शेष:
				जाओ err;
			पूर्ण
		पूर्ण अन्यथा
			devs[count++] = dev;

	पूर्ण

	dev_dbg(&nd_region->dev, "discovered %d %s namespace%s\n",
			count, is_nd_blk(&nd_region->dev)
			? "blk" : "pmem", count == 1 ? "" : "s");

	अगर (count == 0) अणु
		/* Publish a zero-sized namespace क्रम userspace to configure. */
		nd_mapping_मुक्त_labels(nd_mapping);

		devs = kसुस्मृति(2, माप(dev), GFP_KERNEL);
		अगर (!devs)
			जाओ err;
		अगर (is_nd_blk(&nd_region->dev)) अणु
			काष्ठा nd_namespace_blk *nsblk;

			nsblk = kzalloc(माप(*nsblk), GFP_KERNEL);
			अगर (!nsblk)
				जाओ err;
			dev = &nsblk->common.dev;
			dev->type = &namespace_blk_device_type;
		पूर्ण अन्यथा अणु
			काष्ठा nd_namespace_pmem *nspm;

			nspm = kzalloc(माप(*nspm), GFP_KERNEL);
			अगर (!nspm)
				जाओ err;
			dev = &nspm->nsio.common.dev;
			dev->type = &namespace_pmem_device_type;
			nd_namespace_pmem_set_resource(nd_region, nspm, 0);
		पूर्ण
		dev->parent = &nd_region->dev;
		devs[count++] = dev;
	पूर्ण अन्यथा अगर (is_memory(&nd_region->dev)) अणु
		/* clean unselected labels */
		क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
			काष्ठा list_head *l, *e;
			LIST_HEAD(list);
			पूर्णांक j;

			nd_mapping = &nd_region->mapping[i];
			अगर (list_empty(&nd_mapping->labels)) अणु
				WARN_ON(1);
				जारी;
			पूर्ण

			j = count;
			list_क्रम_each_safe(l, e, &nd_mapping->labels) अणु
				अगर (!j--)
					अवरोध;
				list_move_tail(l, &list);
			पूर्ण
			nd_mapping_मुक्त_labels(nd_mapping);
			list_splice_init(&list, &nd_mapping->labels);
		पूर्ण
	पूर्ण

	अगर (count > 1)
		sort(devs, count, माप(काष्ठा device *), cmp_dpa, शून्य);

	वापस devs;

 err:
	अगर (devs) अणु
		क्रम (i = 0; devs[i]; i++)
			अगर (is_nd_blk(&nd_region->dev))
				namespace_blk_release(devs[i]);
			अन्यथा
				namespace_pmem_release(devs[i]);
		kमुक्त(devs);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा device **create_namespaces(काष्ठा nd_region *nd_region)
अणु
	काष्ठा nd_mapping *nd_mapping;
	काष्ठा device **devs;
	पूर्णांक i;

	अगर (nd_region->ndr_mappings == 0)
		वापस शून्य;

	/* lock करोwn all mappings जबतक we scan labels */
	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		nd_mapping = &nd_region->mapping[i];
		mutex_lock_nested(&nd_mapping->lock, i);
	पूर्ण

	devs = scan_labels(nd_region);

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		पूर्णांक reverse = nd_region->ndr_mappings - 1 - i;

		nd_mapping = &nd_region->mapping[reverse];
		mutex_unlock(&nd_mapping->lock);
	पूर्ण

	वापस devs;
पूर्ण

अटल व्योम deactivate_labels(व्योम *region)
अणु
	काष्ठा nd_region *nd_region = region;
	पूर्णांक i;

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm_drvdata *ndd = nd_mapping->ndd;
		काष्ठा nvdimm *nvdimm = nd_mapping->nvdimm;

		mutex_lock(&nd_mapping->lock);
		nd_mapping_मुक्त_labels(nd_mapping);
		mutex_unlock(&nd_mapping->lock);

		put_ndd(ndd);
		nd_mapping->ndd = शून्य;
		अगर (ndd)
			atomic_dec(&nvdimm->busy);
	पूर्ण
पूर्ण

अटल पूर्णांक init_active_labels(काष्ठा nd_region *nd_region)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nd_region->ndr_mappings; i++) अणु
		काष्ठा nd_mapping *nd_mapping = &nd_region->mapping[i];
		काष्ठा nvdimm_drvdata *ndd = to_ndd(nd_mapping);
		काष्ठा nvdimm *nvdimm = nd_mapping->nvdimm;
		काष्ठा nd_label_ent *label_ent;
		पूर्णांक count, j;

		/*
		 * If the dimm is disabled then we may need to prevent
		 * the region from being activated.
		 */
		अगर (!ndd) अणु
			अगर (test_bit(NDD_LOCKED, &nvdimm->flags))
				/* fail, label data may be unपढ़ोable */;
			अन्यथा अगर (test_bit(NDD_LABELING, &nvdimm->flags))
				/* fail, labels needed to disambiguate dpa */;
			अन्यथा
				वापस 0;

			dev_err(&nd_region->dev, "%s: is %s, failing probe\n",
					dev_name(&nd_mapping->nvdimm->dev),
					test_bit(NDD_LOCKED, &nvdimm->flags)
					? "locked" : "disabled");
			वापस -ENXIO;
		पूर्ण
		nd_mapping->ndd = ndd;
		atomic_inc(&nvdimm->busy);
		get_ndd(ndd);

		count = nd_label_active_count(ndd);
		dev_dbg(ndd->dev, "count: %d\n", count);
		अगर (!count)
			जारी;
		क्रम (j = 0; j < count; j++) अणु
			काष्ठा nd_namespace_label *label;

			label_ent = kzalloc(माप(*label_ent), GFP_KERNEL);
			अगर (!label_ent)
				अवरोध;
			label = nd_label_active(ndd, j);
			अगर (test_bit(NDD_NOBLK, &nvdimm->flags)) अणु
				u32 flags = __le32_to_cpu(label->flags);

				flags &= ~NSLABEL_FLAG_LOCAL;
				label->flags = __cpu_to_le32(flags);
			पूर्ण
			label_ent->label = label;

			mutex_lock(&nd_mapping->lock);
			list_add_tail(&label_ent->list, &nd_mapping->labels);
			mutex_unlock(&nd_mapping->lock);
		पूर्ण

		अगर (j < count)
			अवरोध;
	पूर्ण

	अगर (i < nd_region->ndr_mappings) अणु
		deactivate_labels(nd_region);
		वापस -ENOMEM;
	पूर्ण

	वापस devm_add_action_or_reset(&nd_region->dev, deactivate_labels,
			nd_region);
पूर्ण

पूर्णांक nd_region_रेजिस्टर_namespaces(काष्ठा nd_region *nd_region, पूर्णांक *err)
अणु
	काष्ठा device **devs = शून्य;
	पूर्णांक i, rc = 0, type;

	*err = 0;
	nvdimm_bus_lock(&nd_region->dev);
	rc = init_active_labels(nd_region);
	अगर (rc) अणु
		nvdimm_bus_unlock(&nd_region->dev);
		वापस rc;
	पूर्ण

	type = nd_region_to_nstype(nd_region);
	चयन (type) अणु
	हाल ND_DEVICE_NAMESPACE_IO:
		devs = create_namespace_io(nd_region);
		अवरोध;
	हाल ND_DEVICE_NAMESPACE_PMEM:
	हाल ND_DEVICE_NAMESPACE_BLK:
		devs = create_namespaces(nd_region);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	nvdimm_bus_unlock(&nd_region->dev);

	अगर (!devs)
		वापस -ENODEV;

	क्रम (i = 0; devs[i]; i++) अणु
		काष्ठा device *dev = devs[i];
		पूर्णांक id;

		अगर (type == ND_DEVICE_NAMESPACE_BLK) अणु
			काष्ठा nd_namespace_blk *nsblk;

			nsblk = to_nd_namespace_blk(dev);
			id = ida_simple_get(&nd_region->ns_ida, 0, 0,
					GFP_KERNEL);
			nsblk->id = id;
		पूर्ण अन्यथा अगर (type == ND_DEVICE_NAMESPACE_PMEM) अणु
			काष्ठा nd_namespace_pmem *nspm;

			nspm = to_nd_namespace_pmem(dev);
			id = ida_simple_get(&nd_region->ns_ida, 0, 0,
					GFP_KERNEL);
			nspm->id = id;
		पूर्ण अन्यथा
			id = i;

		अगर (id < 0)
			अवरोध;
		dev_set_name(dev, "namespace%d.%d", nd_region->id, id);
		nd_device_रेजिस्टर(dev);
	पूर्ण
	अगर (i)
		nd_region->ns_seed = devs[0];

	अगर (devs[i]) अणु
		पूर्णांक j;

		क्रम (j = i; devs[j]; j++) अणु
			काष्ठा device *dev = devs[j];

			device_initialize(dev);
			put_device(dev);
		पूर्ण
		*err = j - i;
		/*
		 * All of the namespaces we tried to रेजिस्टर failed, so
		 * fail region activation.
		 */
		अगर (*err == 0)
			rc = -ENODEV;
	पूर्ण
	kमुक्त(devs);

	अगर (rc == -ENODEV)
		वापस rc;

	वापस i;
पूर्ण
