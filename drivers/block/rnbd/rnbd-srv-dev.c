<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RDMA Network Block Driver
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */
#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME " L" __stringअगरy(__LINE__) ": " fmt

#समावेश "rnbd-srv-dev.h"
#समावेश "rnbd-log.h"

काष्ठा rnbd_dev *rnbd_dev_खोलो(स्थिर अक्षर *path, भ_शेषe_t flags,
			       काष्ठा bio_set *bs)
अणु
	काष्ठा rnbd_dev *dev;
	पूर्णांक ret;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	dev->blk_खोलो_flags = flags;
	dev->bdev = blkdev_get_by_path(path, flags, THIS_MODULE);
	ret = PTR_ERR_OR_ZERO(dev->bdev);
	अगर (ret)
		जाओ err;

	dev->blk_खोलो_flags = flags;
	bdevname(dev->bdev, dev->name);
	dev->ibd_bio_set = bs;

	वापस dev;

err:
	kमुक्त(dev);
	वापस ERR_PTR(ret);
पूर्ण

व्योम rnbd_dev_बंद(काष्ठा rnbd_dev *dev)
अणु
	blkdev_put(dev->bdev, dev->blk_खोलो_flags);
	kमुक्त(dev);
पूर्ण

व्योम rnbd_dev_bi_end_io(काष्ठा bio *bio)
अणु
	काष्ठा rnbd_dev_blk_io *io = bio->bi_निजी;

	rnbd_endio(io->priv, blk_status_to_त्रुटि_सं(bio->bi_status));
	bio_put(bio);
पूर्ण

/**
 *	rnbd_bio_map_kern	-	map kernel address पूर्णांकo bio
 *	@data: poपूर्णांकer to buffer to map
 *	@bs: bio_set to use.
 *	@len: length in bytes
 *	@gfp_mask: allocation flags क्रम bio allocation
 *
 *	Map the kernel address पूर्णांकo a bio suitable क्रम io to a block
 *	device. Returns an error poपूर्णांकer in हाल of error.
 */
काष्ठा bio *rnbd_bio_map_kern(व्योम *data, काष्ठा bio_set *bs,
			      अचिन्हित पूर्णांक len, gfp_t gfp_mask)
अणु
	अचिन्हित दीर्घ kaddr = (अचिन्हित दीर्घ)data;
	अचिन्हित दीर्घ end = (kaddr + len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	अचिन्हित दीर्घ start = kaddr >> PAGE_SHIFT;
	स्थिर पूर्णांक nr_pages = end - start;
	पूर्णांक offset, i;
	काष्ठा bio *bio;

	bio = bio_alloc_bioset(gfp_mask, nr_pages, bs);
	अगर (!bio)
		वापस ERR_PTR(-ENOMEM);

	offset = offset_in_page(kaddr);
	क्रम (i = 0; i < nr_pages; i++) अणु
		अचिन्हित पूर्णांक bytes = PAGE_SIZE - offset;

		अगर (len <= 0)
			अवरोध;

		अगर (bytes > len)
			bytes = len;

		अगर (bio_add_page(bio, virt_to_page(data), bytes,
				    offset) < bytes) अणु
			/* we करोn't support partial mappings */
			bio_put(bio);
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		data += bytes;
		len -= bytes;
		offset = 0;
	पूर्ण

	वापस bio;
पूर्ण
