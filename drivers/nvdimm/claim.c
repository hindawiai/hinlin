<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#समावेश <linux/device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/badblocks.h>
#समावेश "nd-core.h"
#समावेश "pmem.h"
#समावेश "pfn.h"
#समावेश "btt.h"
#समावेश "nd.h"

व्योम __nd_detach_ndns(काष्ठा device *dev, काष्ठा nd_namespace_common **_ndns)
अणु
	काष्ठा nd_namespace_common *ndns = *_ndns;
	काष्ठा nvdimm_bus *nvdimm_bus;

	अगर (!ndns)
		वापस;

	nvdimm_bus = walk_to_nvdimm_bus(&ndns->dev);
	lockdep_निश्चित_held(&nvdimm_bus->reconfig_mutex);
	dev_WARN_ONCE(dev, ndns->claim != dev, "%s: invalid claim\n", __func__);
	ndns->claim = शून्य;
	*_ndns = शून्य;
	put_device(&ndns->dev);
पूर्ण

व्योम nd_detach_ndns(काष्ठा device *dev,
		काष्ठा nd_namespace_common **_ndns)
अणु
	काष्ठा nd_namespace_common *ndns = *_ndns;

	अगर (!ndns)
		वापस;
	get_device(&ndns->dev);
	nvdimm_bus_lock(&ndns->dev);
	__nd_detach_ndns(dev, _ndns);
	nvdimm_bus_unlock(&ndns->dev);
	put_device(&ndns->dev);
पूर्ण

bool __nd_attach_ndns(काष्ठा device *dev, काष्ठा nd_namespace_common *attach,
		काष्ठा nd_namespace_common **_ndns)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(&attach->dev);

	अगर (attach->claim)
		वापस false;
	lockdep_निश्चित_held(&nvdimm_bus->reconfig_mutex);
	dev_WARN_ONCE(dev, *_ndns, "%s: invalid claim\n", __func__);
	attach->claim = dev;
	*_ndns = attach;
	get_device(&attach->dev);
	वापस true;
पूर्ण

bool nd_attach_ndns(काष्ठा device *dev, काष्ठा nd_namespace_common *attach,
		काष्ठा nd_namespace_common **_ndns)
अणु
	bool claimed;

	nvdimm_bus_lock(&attach->dev);
	claimed = __nd_attach_ndns(dev, attach, _ndns);
	nvdimm_bus_unlock(&attach->dev);
	वापस claimed;
पूर्ण

अटल पूर्णांक namespace_match(काष्ठा device *dev, व्योम *data)
अणु
	अक्षर *name = data;

	वापस म_भेद(name, dev_name(dev)) == 0;
पूर्ण

अटल bool is_idle(काष्ठा device *dev, काष्ठा nd_namespace_common *ndns)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	काष्ठा device *seed = शून्य;

	अगर (is_nd_btt(dev))
		seed = nd_region->btt_seed;
	अन्यथा अगर (is_nd_pfn(dev))
		seed = nd_region->pfn_seed;
	अन्यथा अगर (is_nd_dax(dev))
		seed = nd_region->dax_seed;

	अगर (seed == dev || ndns || dev->driver)
		वापस false;
	वापस true;
पूर्ण

काष्ठा nd_pfn *to_nd_pfn_safe(काष्ठा device *dev)
अणु
	/*
	 * pfn device attributes are re-used by dax device instances, so we
	 * need to be careful to correct device-to-nd_pfn conversion.
	 */
	अगर (is_nd_pfn(dev))
		वापस to_nd_pfn(dev);

	अगर (is_nd_dax(dev)) अणु
		काष्ठा nd_dax *nd_dax = to_nd_dax(dev);

		वापस &nd_dax->nd_pfn;
	पूर्ण

	WARN_ON(1);
	वापस शून्य;
पूर्ण

अटल व्योम nd_detach_and_reset(काष्ठा device *dev,
		काष्ठा nd_namespace_common **_ndns)
अणु
	/* detach the namespace and destroy / reset the device */
	__nd_detach_ndns(dev, _ndns);
	अगर (is_idle(dev, *_ndns)) अणु
		nd_device_unरेजिस्टर(dev, ND_ASYNC);
	पूर्ण अन्यथा अगर (is_nd_btt(dev)) अणु
		काष्ठा nd_btt *nd_btt = to_nd_btt(dev);

		nd_btt->lbasize = 0;
		kमुक्त(nd_btt->uuid);
		nd_btt->uuid = शून्य;
	पूर्ण अन्यथा अगर (is_nd_pfn(dev) || is_nd_dax(dev)) अणु
		काष्ठा nd_pfn *nd_pfn = to_nd_pfn_safe(dev);

		kमुक्त(nd_pfn->uuid);
		nd_pfn->uuid = शून्य;
		nd_pfn->mode = PFN_MODE_NONE;
	पूर्ण
पूर्ण

sमाप_प्रकार nd_namespace_store(काष्ठा device *dev,
		काष्ठा nd_namespace_common **_ndns, स्थिर अक्षर *buf,
		माप_प्रकार len)
अणु
	काष्ठा nd_namespace_common *ndns;
	काष्ठा device *found;
	अक्षर *name;

	अगर (dev->driver) अणु
		dev_dbg(dev, "namespace already active\n");
		वापस -EBUSY;
	पूर्ण

	name = kstrndup(buf, len, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;
	strim(name);

	अगर (म_भेदन(name, "namespace", 9) == 0 || म_भेद(name, "") == 0)
		/* pass */;
	अन्यथा अणु
		len = -EINVAL;
		जाओ out;
	पूर्ण

	ndns = *_ndns;
	अगर (म_भेद(name, "") == 0) अणु
		nd_detach_and_reset(dev, _ndns);
		जाओ out;
	पूर्ण अन्यथा अगर (ndns) अणु
		dev_dbg(dev, "namespace already set to: %s\n",
				dev_name(&ndns->dev));
		len = -EBUSY;
		जाओ out;
	पूर्ण

	found = device_find_child(dev->parent, name, namespace_match);
	अगर (!found) अणु
		dev_dbg(dev, "'%s' not found under %s\n", name,
				dev_name(dev->parent));
		len = -ENODEV;
		जाओ out;
	पूर्ण

	ndns = to_ndns(found);

	चयन (ndns->claim_class) अणु
	हाल NVDIMM_CCLASS_NONE:
		अवरोध;
	हाल NVDIMM_CCLASS_BTT:
	हाल NVDIMM_CCLASS_BTT2:
		अगर (!is_nd_btt(dev)) अणु
			len = -EBUSY;
			जाओ out_attach;
		पूर्ण
		अवरोध;
	हाल NVDIMM_CCLASS_PFN:
		अगर (!is_nd_pfn(dev)) अणु
			len = -EBUSY;
			जाओ out_attach;
		पूर्ण
		अवरोध;
	हाल NVDIMM_CCLASS_DAX:
		अगर (!is_nd_dax(dev)) अणु
			len = -EBUSY;
			जाओ out_attach;
		पूर्ण
		अवरोध;
	शेष:
		len = -EBUSY;
		जाओ out_attach;
		अवरोध;
	पूर्ण

	अगर (__nvdimm_namespace_capacity(ndns) < SZ_16M) अणु
		dev_dbg(dev, "%s too small to host\n", name);
		len = -ENXIO;
		जाओ out_attach;
	पूर्ण

	WARN_ON_ONCE(!is_nvdimm_bus_locked(dev));
	अगर (!__nd_attach_ndns(dev, ndns, _ndns)) अणु
		dev_dbg(dev, "%s already claimed\n",
				dev_name(&ndns->dev));
		len = -EBUSY;
	पूर्ण

 out_attach:
	put_device(&ndns->dev); /* from device_find_child */
 out:
	kमुक्त(name);
	वापस len;
पूर्ण

/*
 * nd_sb_checksum: compute checksum क्रम a generic info block
 *
 * Returns a fletcher64 checksum of everything in the given info block
 * except the last field (since that's where the checksum lives).
 */
u64 nd_sb_checksum(काष्ठा nd_gen_sb *nd_gen_sb)
अणु
	u64 sum;
	__le64 sum_save;

	BUILD_BUG_ON(माप(काष्ठा btt_sb) != SZ_4K);
	BUILD_BUG_ON(माप(काष्ठा nd_pfn_sb) != SZ_4K);
	BUILD_BUG_ON(माप(काष्ठा nd_gen_sb) != SZ_4K);

	sum_save = nd_gen_sb->checksum;
	nd_gen_sb->checksum = 0;
	sum = nd_fletcher64(nd_gen_sb, माप(*nd_gen_sb), 1);
	nd_gen_sb->checksum = sum_save;
	वापस sum;
पूर्ण
EXPORT_SYMBOL(nd_sb_checksum);

अटल पूर्णांक nsio_rw_bytes(काष्ठा nd_namespace_common *ndns,
		resource_माप_प्रकार offset, व्योम *buf, माप_प्रकार size, पूर्णांक rw,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);
	अचिन्हित पूर्णांक sz_align = ALIGN(size + (offset & (512 - 1)), 512);
	sector_t sector = offset >> 9;
	पूर्णांक rc = 0, ret = 0;

	अगर (unlikely(!size))
		वापस 0;

	अगर (unlikely(offset + size > nsio->size)) अणु
		dev_WARN_ONCE(&ndns->dev, 1, "request out of range\n");
		वापस -EFAULT;
	पूर्ण

	अगर (rw == READ) अणु
		अगर (unlikely(is_bad_pmem(&nsio->bb, sector, sz_align)))
			वापस -EIO;
		अगर (copy_mc_to_kernel(buf, nsio->addr + offset, size) != 0)
			वापस -EIO;
		वापस 0;
	पूर्ण

	अगर (unlikely(is_bad_pmem(&nsio->bb, sector, sz_align))) अणु
		अगर (IS_ALIGNED(offset, 512) && IS_ALIGNED(size, 512)
				&& !(flags & NVDIMM_IO_ATOMIC)) अणु
			दीर्घ cleared;

			might_sleep();
			cleared = nvdimm_clear_poison(&ndns->dev,
					nsio->res.start + offset, size);
			अगर (cleared < size)
				rc = -EIO;
			अगर (cleared > 0 && cleared / 512) अणु
				cleared /= 512;
				badblocks_clear(&nsio->bb, sector, cleared);
			पूर्ण
			arch_invalidate_pmem(nsio->addr + offset, size);
		पूर्ण अन्यथा
			rc = -EIO;
	पूर्ण

	स_नकल_flushcache(nsio->addr + offset, buf, size);
	ret = nvdimm_flush(to_nd_region(ndns->dev.parent), शून्य);
	अगर (ret)
		rc = ret;

	वापस rc;
पूर्ण

पूर्णांक devm_nsio_enable(काष्ठा device *dev, काष्ठा nd_namespace_io *nsio,
		resource_माप_प्रकार size)
अणु
	काष्ठा nd_namespace_common *ndns = &nsio->common;
	काष्ठा range range = अणु
		.start = nsio->res.start,
		.end = nsio->res.end,
	पूर्ण;

	nsio->size = size;
	अगर (!devm_request_mem_region(dev, range.start, size,
				dev_name(&ndns->dev))) अणु
		dev_warn(dev, "could not reserve region %pR\n", &nsio->res);
		वापस -EBUSY;
	पूर्ण

	ndns->rw_bytes = nsio_rw_bytes;
	अगर (devm_init_badblocks(dev, &nsio->bb))
		वापस -ENOMEM;
	nvdimm_badblocks_populate(to_nd_region(ndns->dev.parent), &nsio->bb,
			&range);

	nsio->addr = devm_memremap(dev, range.start, size, ARCH_MEMREMAP_PMEM);

	वापस PTR_ERR_OR_ZERO(nsio->addr);
पूर्ण

व्योम devm_nsio_disable(काष्ठा device *dev, काष्ठा nd_namespace_io *nsio)
अणु
	काष्ठा resource *res = &nsio->res;

	devm_memunmap(dev, nsio->addr);
	devm_निकास_badblocks(dev, &nsio->bb);
	devm_release_mem_region(dev, res->start, nsio->size);
पूर्ण
