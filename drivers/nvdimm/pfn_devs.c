<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2016 Intel Corporation. All rights reserved.
 */
#समावेश <linux/memremap.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/genhd.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश "nd-core.h"
#समावेश "pfn.h"
#समावेश "nd.h"

अटल व्योम nd_pfn_release(काष्ठा device *dev)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	काष्ठा nd_pfn *nd_pfn = to_nd_pfn(dev);

	dev_dbg(dev, "trace\n");
	nd_detach_ndns(&nd_pfn->dev, &nd_pfn->ndns);
	ida_simple_हटाओ(&nd_region->pfn_ida, nd_pfn->id);
	kमुक्त(nd_pfn->uuid);
	kमुक्त(nd_pfn);
पूर्ण

काष्ठा nd_pfn *to_nd_pfn(काष्ठा device *dev)
अणु
	काष्ठा nd_pfn *nd_pfn = container_of(dev, काष्ठा nd_pfn, dev);

	WARN_ON(!is_nd_pfn(dev));
	वापस nd_pfn;
पूर्ण
EXPORT_SYMBOL(to_nd_pfn);

अटल sमाप_प्रकार mode_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_pfn *nd_pfn = to_nd_pfn_safe(dev);

	चयन (nd_pfn->mode) अणु
	हाल PFN_MODE_RAM:
		वापस प्र_लिखो(buf, "ram\n");
	हाल PFN_MODE_PMEM:
		वापस प्र_लिखो(buf, "pmem\n");
	शेष:
		वापस प्र_लिखो(buf, "none\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार mode_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_pfn *nd_pfn = to_nd_pfn_safe(dev);
	sमाप_प्रकार rc = 0;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	अगर (dev->driver)
		rc = -EBUSY;
	अन्यथा अणु
		माप_प्रकार n = len - 1;

		अगर (म_भेदन(buf, "pmem\n", n) == 0
				|| म_भेदन(buf, "pmem", n) == 0) अणु
			nd_pfn->mode = PFN_MODE_PMEM;
		पूर्ण अन्यथा अगर (म_भेदन(buf, "ram\n", n) == 0
				|| म_भेदन(buf, "ram", n) == 0)
			nd_pfn->mode = PFN_MODE_RAM;
		अन्यथा अगर (म_भेदन(buf, "none\n", n) == 0
				|| म_भेदन(buf, "none", n) == 0)
			nd_pfn->mode = PFN_MODE_NONE;
		अन्यथा
			rc = -EINVAL;
	पूर्ण
	dev_dbg(dev, "result: %zd wrote: %s%s", rc, buf,
			buf[len - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस rc ? rc : len;
पूर्ण
अटल DEVICE_ATTR_RW(mode);

अटल sमाप_प्रकार align_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_pfn *nd_pfn = to_nd_pfn_safe(dev);

	वापस प्र_लिखो(buf, "%ld\n", nd_pfn->align);
पूर्ण

अटल अचिन्हित दीर्घ *nd_pfn_supported_alignments(अचिन्हित दीर्घ *alignments)
अणु

	alignments[0] = PAGE_SIZE;

	अगर (has_transparent_hugepage()) अणु
		alignments[1] = HPAGE_PMD_SIZE;
		अगर (IS_ENABLED(CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD))
			alignments[2] = HPAGE_PUD_SIZE;
	पूर्ण

	वापस alignments;
पूर्ण

/*
 * Use pmd mapping अगर supported as शेष alignment
 */
अटल अचिन्हित दीर्घ nd_pfn_शेष_alignment(व्योम)
अणु

	अगर (has_transparent_hugepage())
		वापस HPAGE_PMD_SIZE;
	वापस PAGE_SIZE;
पूर्ण

अटल sमाप_प्रकार align_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_pfn *nd_pfn = to_nd_pfn_safe(dev);
	अचिन्हित दीर्घ aligns[MAX_NVDIMM_ALIGN] = अणु [0] = 0, पूर्ण;
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	rc = nd_size_select_store(dev, buf, &nd_pfn->align,
			nd_pfn_supported_alignments(aligns));
	dev_dbg(dev, "result: %zd wrote: %s%s", rc, buf,
			buf[len - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस rc ? rc : len;
पूर्ण
अटल DEVICE_ATTR_RW(align);

अटल sमाप_प्रकार uuid_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_pfn *nd_pfn = to_nd_pfn_safe(dev);

	अगर (nd_pfn->uuid)
		वापस प्र_लिखो(buf, "%pUb\n", nd_pfn->uuid);
	वापस प्र_लिखो(buf, "\n");
पूर्ण

अटल sमाप_प्रकार uuid_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_pfn *nd_pfn = to_nd_pfn_safe(dev);
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	rc = nd_uuid_store(dev, &nd_pfn->uuid, buf, len);
	dev_dbg(dev, "result: %zd wrote: %s%s", rc, buf,
			buf[len - 1] == '\n' ? "" : "\n");
	nd_device_unlock(dev);

	वापस rc ? rc : len;
पूर्ण
अटल DEVICE_ATTR_RW(uuid);

अटल sमाप_प्रकार namespace_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_pfn *nd_pfn = to_nd_pfn_safe(dev);
	sमाप_प्रकार rc;

	nvdimm_bus_lock(dev);
	rc = प्र_लिखो(buf, "%s\n", nd_pfn->ndns
			? dev_name(&nd_pfn->ndns->dev) : "");
	nvdimm_bus_unlock(dev);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार namespace_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_pfn *nd_pfn = to_nd_pfn_safe(dev);
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	rc = nd_namespace_store(dev, &nd_pfn->ndns, buf, len);
	dev_dbg(dev, "result: %zd wrote: %s%s", rc, buf,
			buf[len - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RW(namespace);

अटल sमाप_प्रकार resource_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_pfn *nd_pfn = to_nd_pfn_safe(dev);
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	अगर (dev->driver) अणु
		काष्ठा nd_pfn_sb *pfn_sb = nd_pfn->pfn_sb;
		u64 offset = __le64_to_cpu(pfn_sb->dataoff);
		काष्ठा nd_namespace_common *ndns = nd_pfn->ndns;
		u32 start_pad = __le32_to_cpu(pfn_sb->start_pad);
		काष्ठा nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);

		rc = प्र_लिखो(buf, "%#llx\n", (अचिन्हित दीर्घ दीर्घ) nsio->res.start
				+ start_pad + offset);
	पूर्ण अन्यथा अणु
		/* no address to convey अगर the pfn instance is disabled */
		rc = -ENXIO;
	पूर्ण
	nd_device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_ADMIN_RO(resource);

अटल sमाप_प्रकार size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_pfn *nd_pfn = to_nd_pfn_safe(dev);
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	अगर (dev->driver) अणु
		काष्ठा nd_pfn_sb *pfn_sb = nd_pfn->pfn_sb;
		u64 offset = __le64_to_cpu(pfn_sb->dataoff);
		काष्ठा nd_namespace_common *ndns = nd_pfn->ndns;
		u32 start_pad = __le32_to_cpu(pfn_sb->start_pad);
		u32 end_trunc = __le32_to_cpu(pfn_sb->end_trunc);
		काष्ठा nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);

		rc = प्र_लिखो(buf, "%llu\n", (अचिन्हित दीर्घ दीर्घ)
				resource_size(&nsio->res) - start_pad
				- end_trunc - offset);
	पूर्ण अन्यथा अणु
		/* no size to convey अगर the pfn instance is disabled */
		rc = -ENXIO;
	पूर्ण
	nd_device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(size);

अटल sमाप_प्रकार supported_alignments_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ aligns[MAX_NVDIMM_ALIGN] = अणु [0] = 0, पूर्ण;

	वापस nd_size_select_show(0,
			nd_pfn_supported_alignments(aligns), buf);
पूर्ण
अटल DEVICE_ATTR_RO(supported_alignments);

अटल काष्ठा attribute *nd_pfn_attributes[] = अणु
	&dev_attr_mode.attr,
	&dev_attr_namespace.attr,
	&dev_attr_uuid.attr,
	&dev_attr_align.attr,
	&dev_attr_resource.attr,
	&dev_attr_size.attr,
	&dev_attr_supported_alignments.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group nd_pfn_attribute_group = अणु
	.attrs = nd_pfn_attributes,
पूर्ण;

स्थिर काष्ठा attribute_group *nd_pfn_attribute_groups[] = अणु
	&nd_pfn_attribute_group,
	&nd_device_attribute_group,
	&nd_numa_attribute_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा device_type nd_pfn_device_type = अणु
	.name = "nd_pfn",
	.release = nd_pfn_release,
	.groups = nd_pfn_attribute_groups,
पूर्ण;

bool is_nd_pfn(काष्ठा device *dev)
अणु
	वापस dev ? dev->type == &nd_pfn_device_type : false;
पूर्ण
EXPORT_SYMBOL(is_nd_pfn);

काष्ठा device *nd_pfn_devinit(काष्ठा nd_pfn *nd_pfn,
		काष्ठा nd_namespace_common *ndns)
अणु
	काष्ठा device *dev;

	अगर (!nd_pfn)
		वापस शून्य;

	nd_pfn->mode = PFN_MODE_NONE;
	nd_pfn->align = nd_pfn_शेष_alignment();
	dev = &nd_pfn->dev;
	device_initialize(&nd_pfn->dev);
	अगर (ndns && !__nd_attach_ndns(&nd_pfn->dev, ndns, &nd_pfn->ndns)) अणु
		dev_dbg(&ndns->dev, "failed, already claimed by %s\n",
				dev_name(ndns->claim));
		put_device(dev);
		वापस शून्य;
	पूर्ण
	वापस dev;
पूर्ण

अटल काष्ठा nd_pfn *nd_pfn_alloc(काष्ठा nd_region *nd_region)
अणु
	काष्ठा nd_pfn *nd_pfn;
	काष्ठा device *dev;

	nd_pfn = kzalloc(माप(*nd_pfn), GFP_KERNEL);
	अगर (!nd_pfn)
		वापस शून्य;

	nd_pfn->id = ida_simple_get(&nd_region->pfn_ida, 0, 0, GFP_KERNEL);
	अगर (nd_pfn->id < 0) अणु
		kमुक्त(nd_pfn);
		वापस शून्य;
	पूर्ण

	dev = &nd_pfn->dev;
	dev_set_name(dev, "pfn%d.%d", nd_region->id, nd_pfn->id);
	dev->type = &nd_pfn_device_type;
	dev->parent = &nd_region->dev;

	वापस nd_pfn;
पूर्ण

काष्ठा device *nd_pfn_create(काष्ठा nd_region *nd_region)
अणु
	काष्ठा nd_pfn *nd_pfn;
	काष्ठा device *dev;

	अगर (!is_memory(&nd_region->dev))
		वापस शून्य;

	nd_pfn = nd_pfn_alloc(nd_region);
	dev = nd_pfn_devinit(nd_pfn, शून्य);

	__nd_device_रेजिस्टर(dev);
	वापस dev;
पूर्ण

/*
 * nd_pfn_clear_memmap_errors() clears any errors in the अस्थिर memmap
 * space associated with the namespace. If the memmap is set to DRAM, then
 * this is a no-op. Since the memmap area is freshly initialized during
 * probe, we have an opportunity to clear any badblocks in this area.
 */
अटल पूर्णांक nd_pfn_clear_memmap_errors(काष्ठा nd_pfn *nd_pfn)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(nd_pfn->dev.parent);
	काष्ठा nd_namespace_common *ndns = nd_pfn->ndns;
	व्योम *zero_page = page_address(ZERO_PAGE(0));
	काष्ठा nd_pfn_sb *pfn_sb = nd_pfn->pfn_sb;
	पूर्णांक num_bad, meta_num, rc, bb_present;
	sector_t first_bad, meta_start;
	काष्ठा nd_namespace_io *nsio;

	अगर (nd_pfn->mode != PFN_MODE_PMEM)
		वापस 0;

	nsio = to_nd_namespace_io(&ndns->dev);
	meta_start = (SZ_4K + माप(*pfn_sb)) >> 9;
	meta_num = (le64_to_cpu(pfn_sb->dataoff) >> 9) - meta_start;

	/*
	 * re-enable the namespace with correct size so that we can access
	 * the device memmap area.
	 */
	devm_namespace_disable(&nd_pfn->dev, ndns);
	rc = devm_namespace_enable(&nd_pfn->dev, ndns, le64_to_cpu(pfn_sb->dataoff));
	अगर (rc)
		वापस rc;

	करो अणु
		अचिन्हित दीर्घ zero_len;
		u64 nsoff;

		bb_present = badblocks_check(&nd_region->bb, meta_start,
				meta_num, &first_bad, &num_bad);
		अगर (bb_present) अणु
			dev_dbg(&nd_pfn->dev, "meta: %x badblocks at %llx\n",
					num_bad, first_bad);
			nsoff = ALIGN_DOWN((nd_region->ndr_start
					+ (first_bad << 9)) - nsio->res.start,
					PAGE_SIZE);
			zero_len = ALIGN(num_bad << 9, PAGE_SIZE);
			जबतक (zero_len) अणु
				अचिन्हित दीर्घ chunk = min(zero_len, PAGE_SIZE);

				rc = nvdimm_ग_लिखो_bytes(ndns, nsoff, zero_page,
							chunk, 0);
				अगर (rc)
					अवरोध;

				zero_len -= chunk;
				nsoff += chunk;
			पूर्ण
			अगर (rc) अणु
				dev_err(&nd_pfn->dev,
					"error clearing %x badblocks at %llx\n",
					num_bad, first_bad);
				वापस rc;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (bb_present);

	वापस 0;
पूर्ण

अटल bool nd_supported_alignment(अचिन्हित दीर्घ align)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ supported[MAX_NVDIMM_ALIGN] = अणु [0] = 0, पूर्ण;

	अगर (align == 0)
		वापस false;

	nd_pfn_supported_alignments(supported);
	क्रम (i = 0; supported[i]; i++)
		अगर (align == supported[i])
			वापस true;
	वापस false;
पूर्ण

/**
 * nd_pfn_validate - पढ़ो and validate info-block
 * @nd_pfn: fsdax namespace runसमय state / properties
 * @sig: 'devdax' or 'fsdax' signature
 *
 * Upon वापस the info-block buffer contents (->pfn_sb) are
 * indeterminate when validation fails, and a coherent info-block
 * otherwise.
 */
पूर्णांक nd_pfn_validate(काष्ठा nd_pfn *nd_pfn, स्थिर अक्षर *sig)
अणु
	u64 checksum, offset;
	काष्ठा resource *res;
	क्रमागत nd_pfn_mode mode;
	काष्ठा nd_namespace_io *nsio;
	अचिन्हित दीर्घ align, start_pad;
	काष्ठा nd_pfn_sb *pfn_sb = nd_pfn->pfn_sb;
	काष्ठा nd_namespace_common *ndns = nd_pfn->ndns;
	स्थिर u8 *parent_uuid = nd_dev_to_uuid(&ndns->dev);

	अगर (!pfn_sb || !ndns)
		वापस -ENODEV;

	अगर (!is_memory(nd_pfn->dev.parent))
		वापस -ENODEV;

	अगर (nvdimm_पढ़ो_bytes(ndns, SZ_4K, pfn_sb, माप(*pfn_sb), 0))
		वापस -ENXIO;

	अगर (स_भेद(pfn_sb->signature, sig, PFN_SIG_LEN) != 0)
		वापस -ENODEV;

	checksum = le64_to_cpu(pfn_sb->checksum);
	pfn_sb->checksum = 0;
	अगर (checksum != nd_sb_checksum((काष्ठा nd_gen_sb *) pfn_sb))
		वापस -ENODEV;
	pfn_sb->checksum = cpu_to_le64(checksum);

	अगर (स_भेद(pfn_sb->parent_uuid, parent_uuid, 16) != 0)
		वापस -ENODEV;

	अगर (__le16_to_cpu(pfn_sb->version_minor) < 1) अणु
		pfn_sb->start_pad = 0;
		pfn_sb->end_trunc = 0;
	पूर्ण

	अगर (__le16_to_cpu(pfn_sb->version_minor) < 2)
		pfn_sb->align = 0;

	अगर (__le16_to_cpu(pfn_sb->version_minor) < 4) अणु
		pfn_sb->page_काष्ठा_size = cpu_to_le16(64);
		pfn_sb->page_size = cpu_to_le32(PAGE_SIZE);
	पूर्ण

	चयन (le32_to_cpu(pfn_sb->mode)) अणु
	हाल PFN_MODE_RAM:
	हाल PFN_MODE_PMEM:
		अवरोध;
	शेष:
		वापस -ENXIO;
	पूर्ण

	align = le32_to_cpu(pfn_sb->align);
	offset = le64_to_cpu(pfn_sb->dataoff);
	start_pad = le32_to_cpu(pfn_sb->start_pad);
	अगर (align == 0)
		align = 1UL << ilog2(offset);
	mode = le32_to_cpu(pfn_sb->mode);

	अगर ((le32_to_cpu(pfn_sb->page_size) > PAGE_SIZE) &&
			(mode == PFN_MODE_PMEM)) अणु
		dev_err(&nd_pfn->dev,
				"init failed, page size mismatch %d\n",
				le32_to_cpu(pfn_sb->page_size));
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((le16_to_cpu(pfn_sb->page_काष्ठा_size) < माप(काष्ठा page)) &&
			(mode == PFN_MODE_PMEM)) अणु
		dev_err(&nd_pfn->dev,
				"init failed, struct page size mismatch %d\n",
				le16_to_cpu(pfn_sb->page_काष्ठा_size));
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * Check whether the we support the alignment. For Dax अगर the
	 * superblock alignment is not matching, we won't initialize
	 * the device.
	 */
	अगर (!nd_supported_alignment(align) &&
			!स_भेद(pfn_sb->signature, DAX_SIG, PFN_SIG_LEN)) अणु
		dev_err(&nd_pfn->dev, "init failed, alignment mismatch: "
				"%ld:%ld\n", nd_pfn->align, align);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!nd_pfn->uuid) अणु
		/*
		 * When probing a namepace via nd_pfn_probe() the uuid
		 * is शून्य (see: nd_pfn_devinit()) we init settings from
		 * pfn_sb
		 */
		nd_pfn->uuid = kmemdup(pfn_sb->uuid, 16, GFP_KERNEL);
		अगर (!nd_pfn->uuid)
			वापस -ENOMEM;
		nd_pfn->align = align;
		nd_pfn->mode = mode;
	पूर्ण अन्यथा अणु
		/*
		 * When probing a pfn / dax instance we validate the
		 * live settings against the pfn_sb
		 */
		अगर (स_भेद(nd_pfn->uuid, pfn_sb->uuid, 16) != 0)
			वापस -ENODEV;

		/*
		 * If the uuid validates, but other settings mismatch
		 * वापस EINVAL because userspace has managed to change
		 * the configuration without specअगरying new
		 * identअगरication.
		 */
		अगर (nd_pfn->align != align || nd_pfn->mode != mode) अणु
			dev_err(&nd_pfn->dev,
					"init failed, settings mismatch\n");
			dev_dbg(&nd_pfn->dev, "align: %lx:%lx mode: %d:%d\n",
					nd_pfn->align, align, nd_pfn->mode,
					mode);
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (align > nvdimm_namespace_capacity(ndns)) अणु
		dev_err(&nd_pfn->dev, "alignment: %lx exceeds capacity %llx\n",
				align, nvdimm_namespace_capacity(ndns));
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * These warnings are verbose because they can only trigger in
	 * the हाल where the physical address alignment of the
	 * namespace has changed since the pfn superblock was
	 * established.
	 */
	nsio = to_nd_namespace_io(&ndns->dev);
	res = &nsio->res;
	अगर (offset >= resource_size(res)) अणु
		dev_err(&nd_pfn->dev, "pfn array size exceeds capacity of %s\n",
				dev_name(&ndns->dev));
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((align && !IS_ALIGNED(res->start + offset + start_pad, align))
			|| !IS_ALIGNED(offset, PAGE_SIZE)) अणु
		dev_err(&nd_pfn->dev,
				"bad offset: %#llx dax disabled align: %#lx\n",
				offset, align);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!IS_ALIGNED(res->start + le32_to_cpu(pfn_sb->start_pad),
				memremap_compat_align())) अणु
		dev_err(&nd_pfn->dev, "resource start misaligned\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!IS_ALIGNED(res->end + 1 - le32_to_cpu(pfn_sb->end_trunc),
				memremap_compat_align())) अणु
		dev_err(&nd_pfn->dev, "resource end misaligned\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nd_pfn_validate);

पूर्णांक nd_pfn_probe(काष्ठा device *dev, काष्ठा nd_namespace_common *ndns)
अणु
	पूर्णांक rc;
	काष्ठा nd_pfn *nd_pfn;
	काष्ठा device *pfn_dev;
	काष्ठा nd_pfn_sb *pfn_sb;
	काष्ठा nd_region *nd_region = to_nd_region(ndns->dev.parent);

	अगर (ndns->क्रमce_raw)
		वापस -ENODEV;

	चयन (ndns->claim_class) अणु
	हाल NVDIMM_CCLASS_NONE:
	हाल NVDIMM_CCLASS_PFN:
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	nvdimm_bus_lock(&ndns->dev);
	nd_pfn = nd_pfn_alloc(nd_region);
	pfn_dev = nd_pfn_devinit(nd_pfn, ndns);
	nvdimm_bus_unlock(&ndns->dev);
	अगर (!pfn_dev)
		वापस -ENOMEM;
	pfn_sb = devm_kदो_स्मृति(dev, माप(*pfn_sb), GFP_KERNEL);
	nd_pfn = to_nd_pfn(pfn_dev);
	nd_pfn->pfn_sb = pfn_sb;
	rc = nd_pfn_validate(nd_pfn, PFN_SIG);
	dev_dbg(dev, "pfn: %s\n", rc == 0 ? dev_name(pfn_dev) : "<none>");
	अगर (rc < 0) अणु
		nd_detach_ndns(pfn_dev, &nd_pfn->ndns);
		put_device(pfn_dev);
	पूर्ण अन्यथा
		__nd_device_रेजिस्टर(pfn_dev);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(nd_pfn_probe);

/*
 * We hotplug memory at sub-section granularity, pad the reserved area
 * from the previous section base to the namespace base address.
 */
अटल अचिन्हित दीर्घ init_alपंचांगap_base(resource_माप_प्रकार base)
अणु
	अचिन्हित दीर्घ base_pfn = PHYS_PFN(base);

	वापस SUBSECTION_ALIGN_DOWN(base_pfn);
पूर्ण

अटल अचिन्हित दीर्घ init_alपंचांगap_reserve(resource_माप_प्रकार base)
अणु
	अचिन्हित दीर्घ reserve = nd_info_block_reserve() >> PAGE_SHIFT;
	अचिन्हित दीर्घ base_pfn = PHYS_PFN(base);

	reserve += base_pfn - SUBSECTION_ALIGN_DOWN(base_pfn);
	वापस reserve;
पूर्ण

अटल पूर्णांक __nvdimm_setup_pfn(काष्ठा nd_pfn *nd_pfn, काष्ठा dev_pagemap *pgmap)
अणु
	काष्ठा range *range = &pgmap->range;
	काष्ठा vmem_alपंचांगap *alपंचांगap = &pgmap->alपंचांगap;
	काष्ठा nd_pfn_sb *pfn_sb = nd_pfn->pfn_sb;
	u64 offset = le64_to_cpu(pfn_sb->dataoff);
	u32 start_pad = __le32_to_cpu(pfn_sb->start_pad);
	u32 end_trunc = __le32_to_cpu(pfn_sb->end_trunc);
	u32 reserve = nd_info_block_reserve();
	काष्ठा nd_namespace_common *ndns = nd_pfn->ndns;
	काष्ठा nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);
	resource_माप_प्रकार base = nsio->res.start + start_pad;
	resource_माप_प्रकार end = nsio->res.end - end_trunc;
	काष्ठा vmem_alपंचांगap __alपंचांगap = अणु
		.base_pfn = init_alपंचांगap_base(base),
		.reserve = init_alपंचांगap_reserve(base),
		.end_pfn = PHYS_PFN(end),
	पूर्ण;

	*range = (काष्ठा range) अणु
		.start = nsio->res.start + start_pad,
		.end = nsio->res.end - end_trunc,
	पूर्ण;
	pgmap->nr_range = 1;
	अगर (nd_pfn->mode == PFN_MODE_RAM) अणु
		अगर (offset < reserve)
			वापस -EINVAL;
		nd_pfn->npfns = le64_to_cpu(pfn_sb->npfns);
	पूर्ण अन्यथा अगर (nd_pfn->mode == PFN_MODE_PMEM) अणु
		nd_pfn->npfns = PHYS_PFN((range_len(range) - offset));
		अगर (le64_to_cpu(nd_pfn->pfn_sb->npfns) > nd_pfn->npfns)
			dev_info(&nd_pfn->dev,
					"number of pfns truncated from %lld to %ld\n",
					le64_to_cpu(nd_pfn->pfn_sb->npfns),
					nd_pfn->npfns);
		स_नकल(alपंचांगap, &__alपंचांगap, माप(*alपंचांगap));
		alपंचांगap->मुक्त = PHYS_PFN(offset - reserve);
		alपंचांगap->alloc = 0;
		pgmap->flags |= PGMAP_ALTMAP_VALID;
	पूर्ण अन्यथा
		वापस -ENXIO;

	वापस 0;
पूर्ण

अटल पूर्णांक nd_pfn_init(काष्ठा nd_pfn *nd_pfn)
अणु
	काष्ठा nd_namespace_common *ndns = nd_pfn->ndns;
	काष्ठा nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);
	resource_माप_प्रकार start, size;
	काष्ठा nd_region *nd_region;
	अचिन्हित दीर्घ npfns, align;
	u32 end_trunc;
	काष्ठा nd_pfn_sb *pfn_sb;
	phys_addr_t offset;
	स्थिर अक्षर *sig;
	u64 checksum;
	पूर्णांक rc;

	pfn_sb = devm_kदो_स्मृति(&nd_pfn->dev, माप(*pfn_sb), GFP_KERNEL);
	अगर (!pfn_sb)
		वापस -ENOMEM;

	nd_pfn->pfn_sb = pfn_sb;
	अगर (is_nd_dax(&nd_pfn->dev))
		sig = DAX_SIG;
	अन्यथा
		sig = PFN_SIG;

	rc = nd_pfn_validate(nd_pfn, sig);
	अगर (rc == 0)
		वापस nd_pfn_clear_memmap_errors(nd_pfn);
	अगर (rc != -ENODEV)
		वापस rc;

	/* no info block, करो init */;
	स_रखो(pfn_sb, 0, माप(*pfn_sb));

	nd_region = to_nd_region(nd_pfn->dev.parent);
	अगर (nd_region->ro) अणु
		dev_info(&nd_pfn->dev,
				"%s is read-only, unable to init metadata\n",
				dev_name(&nd_region->dev));
		वापस -ENXIO;
	पूर्ण

	/*
	 * Note, we use 64 here क्रम the standard size of काष्ठा page,
	 * debugging options may cause it to be larger in which हाल the
	 * implementation will limit the pfns advertised through
	 * ->direct_access() to those that are included in the memmap.
	 */
	start = nsio->res.start;
	size = resource_size(&nsio->res);
	npfns = PHYS_PFN(size - SZ_8K);
	align = max(nd_pfn->align, memremap_compat_align());

	/*
	 * When @start is misaligned fail namespace creation. See
	 * the 'struct nd_pfn_sb' commentary on why ->start_pad is not
	 * an option.
	 */
	अगर (!IS_ALIGNED(start, memremap_compat_align())) अणु
		dev_err(&nd_pfn->dev, "%s: start %pa misaligned to %#lx\n",
				dev_name(&ndns->dev), &start,
				memremap_compat_align());
		वापस -EINVAL;
	पूर्ण
	end_trunc = start + size - ALIGN_DOWN(start + size, align);
	अगर (nd_pfn->mode == PFN_MODE_PMEM) अणु
		/*
		 * The alपंचांगap should be padded out to the block size used
		 * when populating the vmemmap. This *should* be equal to
		 * PMD_SIZE क्रम most architectures.
		 *
		 * Also make sure size of काष्ठा page is less than 64. We
		 * want to make sure we use large enough size here so that
		 * we करोn't have a dynamic reserve space depending on
		 * काष्ठा page size. But we also want to make sure we notice
		 * when we end up adding new elements to काष्ठा page.
		 */
		BUILD_BUG_ON(माप(काष्ठा page) > MAX_STRUCT_PAGE_SIZE);
		offset = ALIGN(start + SZ_8K + MAX_STRUCT_PAGE_SIZE * npfns, align)
			- start;
	पूर्ण अन्यथा अगर (nd_pfn->mode == PFN_MODE_RAM)
		offset = ALIGN(start + SZ_8K, align) - start;
	अन्यथा
		वापस -ENXIO;

	अगर (offset >= size) अणु
		dev_err(&nd_pfn->dev, "%s unable to satisfy requested alignment\n",
				dev_name(&ndns->dev));
		वापस -ENXIO;
	पूर्ण

	npfns = PHYS_PFN(size - offset - end_trunc);
	pfn_sb->mode = cpu_to_le32(nd_pfn->mode);
	pfn_sb->dataoff = cpu_to_le64(offset);
	pfn_sb->npfns = cpu_to_le64(npfns);
	स_नकल(pfn_sb->signature, sig, PFN_SIG_LEN);
	स_नकल(pfn_sb->uuid, nd_pfn->uuid, 16);
	स_नकल(pfn_sb->parent_uuid, nd_dev_to_uuid(&ndns->dev), 16);
	pfn_sb->version_major = cpu_to_le16(1);
	pfn_sb->version_minor = cpu_to_le16(4);
	pfn_sb->end_trunc = cpu_to_le32(end_trunc);
	pfn_sb->align = cpu_to_le32(nd_pfn->align);
	pfn_sb->page_काष्ठा_size = cpu_to_le16(MAX_STRUCT_PAGE_SIZE);
	pfn_sb->page_size = cpu_to_le32(PAGE_SIZE);
	checksum = nd_sb_checksum((काष्ठा nd_gen_sb *) pfn_sb);
	pfn_sb->checksum = cpu_to_le64(checksum);

	rc = nd_pfn_clear_memmap_errors(nd_pfn);
	अगर (rc)
		वापस rc;

	वापस nvdimm_ग_लिखो_bytes(ndns, SZ_4K, pfn_sb, माप(*pfn_sb), 0);
पूर्ण

/*
 * Determine the effective resource range and vmem_alपंचांगap from an nd_pfn
 * instance.
 */
पूर्णांक nvdimm_setup_pfn(काष्ठा nd_pfn *nd_pfn, काष्ठा dev_pagemap *pgmap)
अणु
	पूर्णांक rc;

	अगर (!nd_pfn->uuid || !nd_pfn->ndns)
		वापस -ENODEV;

	rc = nd_pfn_init(nd_pfn);
	अगर (rc)
		वापस rc;

	/* we need a valid pfn_sb beक्रमe we can init a dev_pagemap */
	वापस __nvdimm_setup_pfn(nd_pfn, pgmap);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_setup_pfn);
