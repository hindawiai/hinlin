<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014-2016 Christoph Hellwig.
 */
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/nfs4.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_xdr.h>
#समावेश <linux/pr.h>

#समावेश "blocklayout.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PNFS_LD

अटल व्योम
bl_मुक्त_device(काष्ठा pnfs_block_dev *dev)
अणु
	अगर (dev->nr_children) अणु
		पूर्णांक i;

		क्रम (i = 0; i < dev->nr_children; i++)
			bl_मुक्त_device(&dev->children[i]);
		kमुक्त(dev->children);
	पूर्ण अन्यथा अणु
		अगर (dev->pr_रेजिस्टरed) अणु
			स्थिर काष्ठा pr_ops *ops =
				dev->bdev->bd_disk->fops->pr_ops;
			पूर्णांक error;

			error = ops->pr_रेजिस्टर(dev->bdev, dev->pr_key, 0,
				false);
			अगर (error)
				pr_err("failed to unregister PR key.\n");
		पूर्ण

		अगर (dev->bdev)
			blkdev_put(dev->bdev, FMODE_READ | FMODE_WRITE);
	पूर्ण
पूर्ण

व्योम
bl_मुक्त_deviceid_node(काष्ठा nfs4_deviceid_node *d)
अणु
	काष्ठा pnfs_block_dev *dev =
		container_of(d, काष्ठा pnfs_block_dev, node);

	bl_मुक्त_device(dev);
	kमुक्त_rcu(dev, node.rcu);
पूर्ण

अटल पूर्णांक
nfs4_block_decode_volume(काष्ठा xdr_stream *xdr, काष्ठा pnfs_block_volume *b)
अणु
	__be32 *p;
	पूर्णांक i;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (!p)
		वापस -EIO;
	b->type = be32_to_cpup(p++);

	चयन (b->type) अणु
	हाल PNFS_BLOCK_VOLUME_SIMPLE:
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (!p)
			वापस -EIO;
		b->simple.nr_sigs = be32_to_cpup(p++);
		अगर (!b->simple.nr_sigs || b->simple.nr_sigs > PNFS_BLOCK_MAX_UUIDS) अणु
			dprपूर्णांकk("Bad signature count: %d\n", b->simple.nr_sigs);
			वापस -EIO;
		पूर्ण

		b->simple.len = 4 + 4;
		क्रम (i = 0; i < b->simple.nr_sigs; i++) अणु
			p = xdr_अंतरभूत_decode(xdr, 8 + 4);
			अगर (!p)
				वापस -EIO;
			p = xdr_decode_hyper(p, &b->simple.sigs[i].offset);
			b->simple.sigs[i].sig_len = be32_to_cpup(p++);
			अगर (b->simple.sigs[i].sig_len > PNFS_BLOCK_UUID_LEN) अणु
				pr_info("signature too long: %d\n",
					b->simple.sigs[i].sig_len);
				वापस -EIO;
			पूर्ण

			p = xdr_अंतरभूत_decode(xdr, b->simple.sigs[i].sig_len);
			अगर (!p)
				वापस -EIO;
			स_नकल(&b->simple.sigs[i].sig, p,
				b->simple.sigs[i].sig_len);

			b->simple.len += 8 + 4 + \
				(XDR_QUADLEN(b->simple.sigs[i].sig_len) << 2);
		पूर्ण
		अवरोध;
	हाल PNFS_BLOCK_VOLUME_SLICE:
		p = xdr_अंतरभूत_decode(xdr, 8 + 8 + 4);
		अगर (!p)
			वापस -EIO;
		p = xdr_decode_hyper(p, &b->slice.start);
		p = xdr_decode_hyper(p, &b->slice.len);
		b->slice.volume = be32_to_cpup(p++);
		अवरोध;
	हाल PNFS_BLOCK_VOLUME_CONCAT:
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (!p)
			वापस -EIO;

		b->concat.volumes_count = be32_to_cpup(p++);
		अगर (b->concat.volumes_count > PNFS_BLOCK_MAX_DEVICES) अणु
			dprपूर्णांकk("Too many volumes: %d\n", b->concat.volumes_count);
			वापस -EIO;
		पूर्ण

		p = xdr_अंतरभूत_decode(xdr, b->concat.volumes_count * 4);
		अगर (!p)
			वापस -EIO;
		क्रम (i = 0; i < b->concat.volumes_count; i++)
			b->concat.volumes[i] = be32_to_cpup(p++);
		अवरोध;
	हाल PNFS_BLOCK_VOLUME_STRIPE:
		p = xdr_अंतरभूत_decode(xdr, 8 + 4);
		अगर (!p)
			वापस -EIO;

		p = xdr_decode_hyper(p, &b->stripe.chunk_size);
		b->stripe.volumes_count = be32_to_cpup(p++);
		अगर (b->stripe.volumes_count > PNFS_BLOCK_MAX_DEVICES) अणु
			dprपूर्णांकk("Too many volumes: %d\n", b->stripe.volumes_count);
			वापस -EIO;
		पूर्ण

		p = xdr_अंतरभूत_decode(xdr, b->stripe.volumes_count * 4);
		अगर (!p)
			वापस -EIO;
		क्रम (i = 0; i < b->stripe.volumes_count; i++)
			b->stripe.volumes[i] = be32_to_cpup(p++);
		अवरोध;
	हाल PNFS_BLOCK_VOLUME_SCSI:
		p = xdr_अंतरभूत_decode(xdr, 4 + 4 + 4);
		अगर (!p)
			वापस -EIO;
		b->scsi.code_set = be32_to_cpup(p++);
		b->scsi.designator_type = be32_to_cpup(p++);
		b->scsi.designator_len = be32_to_cpup(p++);
		p = xdr_अंतरभूत_decode(xdr, b->scsi.designator_len);
		अगर (!p)
			वापस -EIO;
		अगर (b->scsi.designator_len > 256)
			वापस -EIO;
		स_नकल(&b->scsi.designator, p, b->scsi.designator_len);
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (!p)
			वापस -EIO;
		p = xdr_decode_hyper(p, &b->scsi.pr_key);
		अवरोध;
	शेष:
		dprपूर्णांकk("unknown volume type!\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool bl_map_simple(काष्ठा pnfs_block_dev *dev, u64 offset,
		काष्ठा pnfs_block_dev_map *map)
अणु
	map->start = dev->start;
	map->len = dev->len;
	map->disk_offset = dev->disk_offset;
	map->bdev = dev->bdev;
	वापस true;
पूर्ण

अटल bool bl_map_concat(काष्ठा pnfs_block_dev *dev, u64 offset,
		काष्ठा pnfs_block_dev_map *map)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev->nr_children; i++) अणु
		काष्ठा pnfs_block_dev *child = &dev->children[i];

		अगर (child->start > offset ||
		    child->start + child->len <= offset)
			जारी;

		child->map(child, offset - child->start, map);
		वापस true;
	पूर्ण

	dprपूर्णांकk("%s: ran off loop!\n", __func__);
	वापस false;
पूर्ण

अटल bool bl_map_stripe(काष्ठा pnfs_block_dev *dev, u64 offset,
		काष्ठा pnfs_block_dev_map *map)
अणु
	काष्ठा pnfs_block_dev *child;
	u64 chunk;
	u32 chunk_idx;
	u64 disk_offset;

	chunk = भाग_u64(offset, dev->chunk_size);
	भाग_u64_rem(chunk, dev->nr_children, &chunk_idx);

	अगर (chunk_idx >= dev->nr_children) अणु
		dprपूर्णांकk("%s: invalid chunk idx %d (%lld/%lld)\n",
			__func__, chunk_idx, offset, dev->chunk_size);
		/* error, should not happen */
		वापस false;
	पूर्ण

	/* truncate offset to the beginning of the stripe */
	offset = chunk * dev->chunk_size;

	/* disk offset of the stripe */
	disk_offset = भाग_u64(offset, dev->nr_children);

	child = &dev->children[chunk_idx];
	child->map(child, disk_offset, map);

	map->start += offset;
	map->disk_offset += disk_offset;
	map->len = dev->chunk_size;
	वापस true;
पूर्ण

अटल पूर्णांक
bl_parse_deviceid(काष्ठा nfs_server *server, काष्ठा pnfs_block_dev *d,
		काष्ठा pnfs_block_volume *volumes, पूर्णांक idx, gfp_t gfp_mask);


अटल पूर्णांक
bl_parse_simple(काष्ठा nfs_server *server, काष्ठा pnfs_block_dev *d,
		काष्ठा pnfs_block_volume *volumes, पूर्णांक idx, gfp_t gfp_mask)
अणु
	काष्ठा pnfs_block_volume *v = &volumes[idx];
	काष्ठा block_device *bdev;
	dev_t dev;

	dev = bl_resolve_deviceid(server, v, gfp_mask);
	अगर (!dev)
		वापस -EIO;

	bdev = blkdev_get_by_dev(dev, FMODE_READ | FMODE_WRITE, शून्य);
	अगर (IS_ERR(bdev)) अणु
		prपूर्णांकk(KERN_WARNING "pNFS: failed to open device %d:%d (%ld)\n",
			MAJOR(dev), MINOR(dev), PTR_ERR(bdev));
		वापस PTR_ERR(bdev);
	पूर्ण
	d->bdev = bdev;


	d->len = i_size_पढ़ो(d->bdev->bd_inode);
	d->map = bl_map_simple;

	prपूर्णांकk(KERN_INFO "pNFS: using block device %s\n",
		d->bdev->bd_disk->disk_name);
	वापस 0;
पूर्ण

अटल bool
bl_validate_designator(काष्ठा pnfs_block_volume *v)
अणु
	चयन (v->scsi.designator_type) अणु
	हाल PS_DESIGNATOR_EUI64:
		अगर (v->scsi.code_set != PS_CODE_SET_BINARY)
			वापस false;

		अगर (v->scsi.designator_len != 8 &&
		    v->scsi.designator_len != 10 &&
		    v->scsi.designator_len != 16)
			वापस false;

		वापस true;
	हाल PS_DESIGNATOR_NAA:
		अगर (v->scsi.code_set != PS_CODE_SET_BINARY)
			वापस false;

		अगर (v->scsi.designator_len != 8 &&
		    v->scsi.designator_len != 16)
			वापस false;

		वापस true;
	हाल PS_DESIGNATOR_T10:
	हाल PS_DESIGNATOR_NAME:
		pr_err("pNFS: unsupported designator "
			"(code set %d, type %d, len %d.\n",
			v->scsi.code_set,
			v->scsi.designator_type,
			v->scsi.designator_len);
		वापस false;
	शेष:
		pr_err("pNFS: invalid designator "
			"(code set %d, type %d, len %d.\n",
			v->scsi.code_set,
			v->scsi.designator_type,
			v->scsi.designator_len);
		वापस false;
	पूर्ण
पूर्ण

/*
 * Try to खोलो the udev path क्रम the WWN.  At least on Debian the udev
 * by-id path will always poपूर्णांक to the dm-multipath device अगर one exists.
 */
अटल काष्ठा block_device *
bl_खोलो_udev_path(काष्ठा pnfs_block_volume *v)
अणु
	काष्ठा block_device *bdev;
	स्थिर अक्षर *devname;

	devname = kaप्र_लिखो(GFP_KERNEL, "/dev/disk/by-id/wwn-0x%*phN",
				v->scsi.designator_len, v->scsi.designator);
	अगर (!devname)
		वापस ERR_PTR(-ENOMEM);

	bdev = blkdev_get_by_path(devname, FMODE_READ | FMODE_WRITE, शून्य);
	अगर (IS_ERR(bdev)) अणु
		pr_warn("pNFS: failed to open device %s (%ld)\n",
			devname, PTR_ERR(bdev));
	पूर्ण

	kमुक्त(devname);
	वापस bdev;
पूर्ण

/*
 * Try to खोलो the RH/Feकरोra specअगरic dm-mpath udev path क्रम this WWN, as the
 * wwn- links will only poपूर्णांक to the first discovered SCSI device there.
 */
अटल काष्ठा block_device *
bl_खोलो_dm_mpath_udev_path(काष्ठा pnfs_block_volume *v)
अणु
	काष्ठा block_device *bdev;
	स्थिर अक्षर *devname;

	devname = kaप्र_लिखो(GFP_KERNEL,
			"/dev/disk/by-id/dm-uuid-mpath-%d%*phN",
			v->scsi.designator_type,
			v->scsi.designator_len, v->scsi.designator);
	अगर (!devname)
		वापस ERR_PTR(-ENOMEM);

	bdev = blkdev_get_by_path(devname, FMODE_READ | FMODE_WRITE, शून्य);
	kमुक्त(devname);
	वापस bdev;
पूर्ण

अटल पूर्णांक
bl_parse_scsi(काष्ठा nfs_server *server, काष्ठा pnfs_block_dev *d,
		काष्ठा pnfs_block_volume *volumes, पूर्णांक idx, gfp_t gfp_mask)
अणु
	काष्ठा pnfs_block_volume *v = &volumes[idx];
	काष्ठा block_device *bdev;
	स्थिर काष्ठा pr_ops *ops;
	पूर्णांक error;

	अगर (!bl_validate_designator(v))
		वापस -EINVAL;

	bdev = bl_खोलो_dm_mpath_udev_path(v);
	अगर (IS_ERR(bdev))
		bdev = bl_खोलो_udev_path(v);
	अगर (IS_ERR(bdev))
		वापस PTR_ERR(bdev);
	d->bdev = bdev;

	d->len = i_size_पढ़ो(d->bdev->bd_inode);
	d->map = bl_map_simple;
	d->pr_key = v->scsi.pr_key;

	pr_info("pNFS: using block device %s (reservation key 0x%llx)\n",
		d->bdev->bd_disk->disk_name, d->pr_key);

	ops = d->bdev->bd_disk->fops->pr_ops;
	अगर (!ops) अणु
		pr_err("pNFS: block device %s does not support reservations.",
				d->bdev->bd_disk->disk_name);
		error = -EINVAL;
		जाओ out_blkdev_put;
	पूर्ण

	error = ops->pr_रेजिस्टर(d->bdev, 0, d->pr_key, true);
	अगर (error) अणु
		pr_err("pNFS: failed to register key for block device %s.",
				d->bdev->bd_disk->disk_name);
		जाओ out_blkdev_put;
	पूर्ण

	d->pr_रेजिस्टरed = true;
	वापस 0;

out_blkdev_put:
	blkdev_put(d->bdev, FMODE_READ | FMODE_WRITE);
	वापस error;
पूर्ण

अटल पूर्णांक
bl_parse_slice(काष्ठा nfs_server *server, काष्ठा pnfs_block_dev *d,
		काष्ठा pnfs_block_volume *volumes, पूर्णांक idx, gfp_t gfp_mask)
अणु
	काष्ठा pnfs_block_volume *v = &volumes[idx];
	पूर्णांक ret;

	ret = bl_parse_deviceid(server, d, volumes, v->slice.volume, gfp_mask);
	अगर (ret)
		वापस ret;

	d->disk_offset = v->slice.start;
	d->len = v->slice.len;
	वापस 0;
पूर्ण

अटल पूर्णांक
bl_parse_concat(काष्ठा nfs_server *server, काष्ठा pnfs_block_dev *d,
		काष्ठा pnfs_block_volume *volumes, पूर्णांक idx, gfp_t gfp_mask)
अणु
	काष्ठा pnfs_block_volume *v = &volumes[idx];
	u64 len = 0;
	पूर्णांक ret, i;

	d->children = kसुस्मृति(v->concat.volumes_count,
			माप(काष्ठा pnfs_block_dev), GFP_KERNEL);
	अगर (!d->children)
		वापस -ENOMEM;

	क्रम (i = 0; i < v->concat.volumes_count; i++) अणु
		ret = bl_parse_deviceid(server, &d->children[i],
				volumes, v->concat.volumes[i], gfp_mask);
		अगर (ret)
			वापस ret;

		d->nr_children++;
		d->children[i].start += len;
		len += d->children[i].len;
	पूर्ण

	d->len = len;
	d->map = bl_map_concat;
	वापस 0;
पूर्ण

अटल पूर्णांक
bl_parse_stripe(काष्ठा nfs_server *server, काष्ठा pnfs_block_dev *d,
		काष्ठा pnfs_block_volume *volumes, पूर्णांक idx, gfp_t gfp_mask)
अणु
	काष्ठा pnfs_block_volume *v = &volumes[idx];
	u64 len = 0;
	पूर्णांक ret, i;

	d->children = kसुस्मृति(v->stripe.volumes_count,
			माप(काष्ठा pnfs_block_dev), GFP_KERNEL);
	अगर (!d->children)
		वापस -ENOMEM;

	क्रम (i = 0; i < v->stripe.volumes_count; i++) अणु
		ret = bl_parse_deviceid(server, &d->children[i],
				volumes, v->stripe.volumes[i], gfp_mask);
		अगर (ret)
			वापस ret;

		d->nr_children++;
		len += d->children[i].len;
	पूर्ण

	d->len = len;
	d->chunk_size = v->stripe.chunk_size;
	d->map = bl_map_stripe;
	वापस 0;
पूर्ण

अटल पूर्णांक
bl_parse_deviceid(काष्ठा nfs_server *server, काष्ठा pnfs_block_dev *d,
		काष्ठा pnfs_block_volume *volumes, पूर्णांक idx, gfp_t gfp_mask)
अणु
	चयन (volumes[idx].type) अणु
	हाल PNFS_BLOCK_VOLUME_SIMPLE:
		वापस bl_parse_simple(server, d, volumes, idx, gfp_mask);
	हाल PNFS_BLOCK_VOLUME_SLICE:
		वापस bl_parse_slice(server, d, volumes, idx, gfp_mask);
	हाल PNFS_BLOCK_VOLUME_CONCAT:
		वापस bl_parse_concat(server, d, volumes, idx, gfp_mask);
	हाल PNFS_BLOCK_VOLUME_STRIPE:
		वापस bl_parse_stripe(server, d, volumes, idx, gfp_mask);
	हाल PNFS_BLOCK_VOLUME_SCSI:
		वापस bl_parse_scsi(server, d, volumes, idx, gfp_mask);
	शेष:
		dprपूर्णांकk("unsupported volume type: %d\n", volumes[idx].type);
		वापस -EIO;
	पूर्ण
पूर्ण

काष्ठा nfs4_deviceid_node *
bl_alloc_deviceid_node(काष्ठा nfs_server *server, काष्ठा pnfs_device *pdev,
		gfp_t gfp_mask)
अणु
	काष्ठा nfs4_deviceid_node *node = शून्य;
	काष्ठा pnfs_block_volume *volumes;
	काष्ठा pnfs_block_dev *top;
	काष्ठा xdr_stream xdr;
	काष्ठा xdr_buf buf;
	काष्ठा page *scratch;
	पूर्णांक nr_volumes, ret, i;
	__be32 *p;

	scratch = alloc_page(gfp_mask);
	अगर (!scratch)
		जाओ out;

	xdr_init_decode_pages(&xdr, &buf, pdev->pages, pdev->pglen);
	xdr_set_scratch_page(&xdr, scratch);

	p = xdr_अंतरभूत_decode(&xdr, माप(__be32));
	अगर (!p)
		जाओ out_मुक्त_scratch;
	nr_volumes = be32_to_cpup(p++);

	volumes = kसुस्मृति(nr_volumes, माप(काष्ठा pnfs_block_volume),
			  gfp_mask);
	अगर (!volumes)
		जाओ out_मुक्त_scratch;

	क्रम (i = 0; i < nr_volumes; i++) अणु
		ret = nfs4_block_decode_volume(&xdr, &volumes[i]);
		अगर (ret < 0)
			जाओ out_मुक्त_volumes;
	पूर्ण

	top = kzalloc(माप(*top), gfp_mask);
	अगर (!top)
		जाओ out_मुक्त_volumes;

	ret = bl_parse_deviceid(server, top, volumes, nr_volumes - 1, gfp_mask);

	node = &top->node;
	nfs4_init_deviceid_node(node, server, &pdev->dev_id);
	अगर (ret)
		nfs4_mark_deviceid_unavailable(node);

out_मुक्त_volumes:
	kमुक्त(volumes);
out_मुक्त_scratch:
	__मुक्त_page(scratch);
out:
	वापस node;
पूर्ण
