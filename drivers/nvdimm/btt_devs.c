<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#समावेश <linux/blkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/genhd.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश "nd-core.h"
#समावेश "btt.h"
#समावेश "nd.h"

अटल व्योम nd_btt_release(काष्ठा device *dev)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	काष्ठा nd_btt *nd_btt = to_nd_btt(dev);

	dev_dbg(dev, "trace\n");
	nd_detach_ndns(&nd_btt->dev, &nd_btt->ndns);
	ida_simple_हटाओ(&nd_region->btt_ida, nd_btt->id);
	kमुक्त(nd_btt->uuid);
	kमुक्त(nd_btt);
पूर्ण

काष्ठा nd_btt *to_nd_btt(काष्ठा device *dev)
अणु
	काष्ठा nd_btt *nd_btt = container_of(dev, काष्ठा nd_btt, dev);

	WARN_ON(!is_nd_btt(dev));
	वापस nd_btt;
पूर्ण
EXPORT_SYMBOL(to_nd_btt);

अटल स्थिर अचिन्हित दीर्घ btt_lbasize_supported[] = अणु 512, 520, 528,
	4096, 4104, 4160, 4224, 0 पूर्ण;

अटल sमाप_प्रकार sector_size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_btt *nd_btt = to_nd_btt(dev);

	वापस nd_size_select_show(nd_btt->lbasize, btt_lbasize_supported, buf);
पूर्ण

अटल sमाप_प्रकार sector_size_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_btt *nd_btt = to_nd_btt(dev);
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	rc = nd_size_select_store(dev, buf, &nd_btt->lbasize,
			btt_lbasize_supported);
	dev_dbg(dev, "result: %zd wrote: %s%s", rc, buf,
			buf[len - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस rc ? rc : len;
पूर्ण
अटल DEVICE_ATTR_RW(sector_size);

अटल sमाप_प्रकार uuid_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_btt *nd_btt = to_nd_btt(dev);

	अगर (nd_btt->uuid)
		वापस प्र_लिखो(buf, "%pUb\n", nd_btt->uuid);
	वापस प्र_लिखो(buf, "\n");
पूर्ण

अटल sमाप_प्रकार uuid_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_btt *nd_btt = to_nd_btt(dev);
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	rc = nd_uuid_store(dev, &nd_btt->uuid, buf, len);
	dev_dbg(dev, "result: %zd wrote: %s%s", rc, buf,
			buf[len - 1] == '\n' ? "" : "\n");
	nd_device_unlock(dev);

	वापस rc ? rc : len;
पूर्ण
अटल DEVICE_ATTR_RW(uuid);

अटल sमाप_प्रकार namespace_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_btt *nd_btt = to_nd_btt(dev);
	sमाप_प्रकार rc;

	nvdimm_bus_lock(dev);
	rc = प्र_लिखो(buf, "%s\n", nd_btt->ndns
			? dev_name(&nd_btt->ndns->dev) : "");
	nvdimm_bus_unlock(dev);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार namespace_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nd_btt *nd_btt = to_nd_btt(dev);
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	rc = nd_namespace_store(dev, &nd_btt->ndns, buf, len);
	dev_dbg(dev, "result: %zd wrote: %s%s", rc, buf,
			buf[len - 1] == '\n' ? "" : "\n");
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RW(namespace);

अटल sमाप_प्रकार size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nd_btt *nd_btt = to_nd_btt(dev);
	sमाप_प्रकार rc;

	nd_device_lock(dev);
	अगर (dev->driver)
		rc = प्र_लिखो(buf, "%llu\n", nd_btt->size);
	अन्यथा अणु
		/* no size to convey अगर the btt instance is disabled */
		rc = -ENXIO;
	पूर्ण
	nd_device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(size);

अटल sमाप_प्रकार log_zero_flags_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "Y\n");
पूर्ण
अटल DEVICE_ATTR_RO(log_zero_flags);

अटल काष्ठा attribute *nd_btt_attributes[] = अणु
	&dev_attr_sector_size.attr,
	&dev_attr_namespace.attr,
	&dev_attr_uuid.attr,
	&dev_attr_size.attr,
	&dev_attr_log_zero_flags.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group nd_btt_attribute_group = अणु
	.attrs = nd_btt_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *nd_btt_attribute_groups[] = अणु
	&nd_btt_attribute_group,
	&nd_device_attribute_group,
	&nd_numa_attribute_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा device_type nd_btt_device_type = अणु
	.name = "nd_btt",
	.release = nd_btt_release,
	.groups = nd_btt_attribute_groups,
पूर्ण;

bool is_nd_btt(काष्ठा device *dev)
अणु
	वापस dev->type == &nd_btt_device_type;
पूर्ण
EXPORT_SYMBOL(is_nd_btt);

अटल काष्ठा device *__nd_btt_create(काष्ठा nd_region *nd_region,
		अचिन्हित दीर्घ lbasize, u8 *uuid,
		काष्ठा nd_namespace_common *ndns)
अणु
	काष्ठा nd_btt *nd_btt;
	काष्ठा device *dev;

	nd_btt = kzalloc(माप(*nd_btt), GFP_KERNEL);
	अगर (!nd_btt)
		वापस शून्य;

	nd_btt->id = ida_simple_get(&nd_region->btt_ida, 0, 0, GFP_KERNEL);
	अगर (nd_btt->id < 0)
		जाओ out_nd_btt;

	nd_btt->lbasize = lbasize;
	अगर (uuid) अणु
		uuid = kmemdup(uuid, 16, GFP_KERNEL);
		अगर (!uuid)
			जाओ out_put_id;
	पूर्ण
	nd_btt->uuid = uuid;
	dev = &nd_btt->dev;
	dev_set_name(dev, "btt%d.%d", nd_region->id, nd_btt->id);
	dev->parent = &nd_region->dev;
	dev->type = &nd_btt_device_type;
	device_initialize(&nd_btt->dev);
	अगर (ndns && !__nd_attach_ndns(&nd_btt->dev, ndns, &nd_btt->ndns)) अणु
		dev_dbg(&ndns->dev, "failed, already claimed by %s\n",
				dev_name(ndns->claim));
		put_device(dev);
		वापस शून्य;
	पूर्ण
	वापस dev;

out_put_id:
	ida_simple_हटाओ(&nd_region->btt_ida, nd_btt->id);

out_nd_btt:
	kमुक्त(nd_btt);
	वापस शून्य;
पूर्ण

काष्ठा device *nd_btt_create(काष्ठा nd_region *nd_region)
अणु
	काष्ठा device *dev = __nd_btt_create(nd_region, 0, शून्य, शून्य);

	__nd_device_रेजिस्टर(dev);
	वापस dev;
पूर्ण

/**
 * nd_btt_arena_is_valid - check अगर the metadata layout is valid
 * @nd_btt:	device with BTT geometry and backing device info
 * @super:	poपूर्णांकer to the arena's info block being tested
 *
 * Check consistency of the btt info block with itself by validating
 * the checksum, and with the parent namespace by verअगरying the
 * parent_uuid contained in the info block with the one supplied in.
 *
 * Returns:
 * false क्रम an invalid info block, true क्रम a valid one
 */
bool nd_btt_arena_is_valid(काष्ठा nd_btt *nd_btt, काष्ठा btt_sb *super)
अणु
	स्थिर u8 *parent_uuid = nd_dev_to_uuid(&nd_btt->ndns->dev);
	u64 checksum;

	अगर (स_भेद(super->signature, BTT_SIG, BTT_SIG_LEN) != 0)
		वापस false;

	अगर (!guid_is_null((guid_t *)&super->parent_uuid))
		अगर (स_भेद(super->parent_uuid, parent_uuid, 16) != 0)
			वापस false;

	checksum = le64_to_cpu(super->checksum);
	super->checksum = 0;
	अगर (checksum != nd_sb_checksum((काष्ठा nd_gen_sb *) super))
		वापस false;
	super->checksum = cpu_to_le64(checksum);

	/* TODO: figure out action क्रम this */
	अगर ((le32_to_cpu(super->flags) & IB_FLAG_ERROR_MASK) != 0)
		dev_info(&nd_btt->dev, "Found arena with an error flag\n");

	वापस true;
पूर्ण
EXPORT_SYMBOL(nd_btt_arena_is_valid);

पूर्णांक nd_btt_version(काष्ठा nd_btt *nd_btt, काष्ठा nd_namespace_common *ndns,
		काष्ठा btt_sb *btt_sb)
अणु
	अगर (ndns->claim_class == NVDIMM_CCLASS_BTT2) अणु
		/* Probe/setup क्रम BTT v2.0 */
		nd_btt->initial_offset = 0;
		nd_btt->version_major = 2;
		nd_btt->version_minor = 0;
		अगर (nvdimm_पढ़ो_bytes(ndns, 0, btt_sb, माप(*btt_sb), 0))
			वापस -ENXIO;
		अगर (!nd_btt_arena_is_valid(nd_btt, btt_sb))
			वापस -ENODEV;
		अगर ((le16_to_cpu(btt_sb->version_major) != 2) ||
				(le16_to_cpu(btt_sb->version_minor) != 0))
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		/*
		 * Probe/setup क्रम BTT v1.1 (NVDIMM_CCLASS_NONE or
		 * NVDIMM_CCLASS_BTT)
		 */
		nd_btt->initial_offset = SZ_4K;
		nd_btt->version_major = 1;
		nd_btt->version_minor = 1;
		अगर (nvdimm_पढ़ो_bytes(ndns, SZ_4K, btt_sb, माप(*btt_sb), 0))
			वापस -ENXIO;
		अगर (!nd_btt_arena_is_valid(nd_btt, btt_sb))
			वापस -ENODEV;
		अगर ((le16_to_cpu(btt_sb->version_major) != 1) ||
				(le16_to_cpu(btt_sb->version_minor) != 1))
			वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nd_btt_version);

अटल पूर्णांक __nd_btt_probe(काष्ठा nd_btt *nd_btt,
		काष्ठा nd_namespace_common *ndns, काष्ठा btt_sb *btt_sb)
अणु
	पूर्णांक rc;

	अगर (!btt_sb || !ndns || !nd_btt)
		वापस -ENODEV;

	अगर (nvdimm_namespace_capacity(ndns) < SZ_16M)
		वापस -ENXIO;

	rc = nd_btt_version(nd_btt, ndns, btt_sb);
	अगर (rc < 0)
		वापस rc;

	nd_btt->lbasize = le32_to_cpu(btt_sb->बाह्यal_lbasize);
	nd_btt->uuid = kmemdup(btt_sb->uuid, 16, GFP_KERNEL);
	अगर (!nd_btt->uuid)
		वापस -ENOMEM;

	__nd_device_रेजिस्टर(&nd_btt->dev);

	वापस 0;
पूर्ण

पूर्णांक nd_btt_probe(काष्ठा device *dev, काष्ठा nd_namespace_common *ndns)
अणु
	पूर्णांक rc;
	काष्ठा device *btt_dev;
	काष्ठा btt_sb *btt_sb;
	काष्ठा nd_region *nd_region = to_nd_region(ndns->dev.parent);

	अगर (ndns->क्रमce_raw)
		वापस -ENODEV;

	चयन (ndns->claim_class) अणु
	हाल NVDIMM_CCLASS_NONE:
	हाल NVDIMM_CCLASS_BTT:
	हाल NVDIMM_CCLASS_BTT2:
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	nvdimm_bus_lock(&ndns->dev);
	btt_dev = __nd_btt_create(nd_region, 0, शून्य, ndns);
	nvdimm_bus_unlock(&ndns->dev);
	अगर (!btt_dev)
		वापस -ENOMEM;
	btt_sb = devm_kzalloc(dev, माप(*btt_sb), GFP_KERNEL);
	rc = __nd_btt_probe(to_nd_btt(btt_dev), ndns, btt_sb);
	dev_dbg(dev, "btt: %s\n", rc == 0 ? dev_name(btt_dev) : "<none>");
	अगर (rc < 0) अणु
		काष्ठा nd_btt *nd_btt = to_nd_btt(btt_dev);

		nd_detach_ndns(btt_dev, &nd_btt->ndns);
		put_device(btt_dev);
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL(nd_btt_probe);
