<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RDMA Network Block Driver
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */
#अगर_अघोषित RNBD_SRV_DEV_H
#घोषणा RNBD_SRV_DEV_H

#समावेश <linux/fs.h>
#समावेश "rnbd-proto.h"

काष्ठा rnbd_dev अणु
	काष्ठा block_device	*bdev;
	काष्ठा bio_set		*ibd_bio_set;
	भ_शेषe_t			blk_खोलो_flags;
	अक्षर			name[BDEVNAME_SIZE];
पूर्ण;

काष्ठा rnbd_dev_blk_io अणु
	काष्ठा rnbd_dev *dev;
	व्योम		 *priv;
	/* have to be last member क्रम front_pad usage of bioset_init */
	काष्ठा bio	bio;
पूर्ण;

/**
 * rnbd_dev_खोलो() - Open a device
 * @flags:	खोलो flags
 * @bs:		bio_set to use during block io,
 */
काष्ठा rnbd_dev *rnbd_dev_खोलो(स्थिर अक्षर *path, भ_शेषe_t flags,
			       काष्ठा bio_set *bs);

/**
 * rnbd_dev_बंद() - Close a device
 */
व्योम rnbd_dev_बंद(काष्ठा rnbd_dev *dev);

व्योम rnbd_endio(व्योम *priv, पूर्णांक error);

व्योम rnbd_dev_bi_end_io(काष्ठा bio *bio);

काष्ठा bio *rnbd_bio_map_kern(व्योम *data, काष्ठा bio_set *bs,
			      अचिन्हित पूर्णांक len, gfp_t gfp_mask);

अटल अंतरभूत पूर्णांक rnbd_dev_get_max_segs(स्थिर काष्ठा rnbd_dev *dev)
अणु
	वापस queue_max_segments(bdev_get_queue(dev->bdev));
पूर्ण

अटल अंतरभूत पूर्णांक rnbd_dev_get_max_hw_sects(स्थिर काष्ठा rnbd_dev *dev)
अणु
	वापस queue_max_hw_sectors(bdev_get_queue(dev->bdev));
पूर्ण

अटल अंतरभूत पूर्णांक rnbd_dev_get_secure_discard(स्थिर काष्ठा rnbd_dev *dev)
अणु
	वापस blk_queue_secure_erase(bdev_get_queue(dev->bdev));
पूर्ण

अटल अंतरभूत पूर्णांक rnbd_dev_get_max_discard_sects(स्थिर काष्ठा rnbd_dev *dev)
अणु
	अगर (!blk_queue_discard(bdev_get_queue(dev->bdev)))
		वापस 0;

	वापस blk_queue_get_max_sectors(bdev_get_queue(dev->bdev),
					 REQ_OP_DISCARD);
पूर्ण

अटल अंतरभूत पूर्णांक rnbd_dev_get_discard_granularity(स्थिर काष्ठा rnbd_dev *dev)
अणु
	वापस bdev_get_queue(dev->bdev)->limits.discard_granularity;
पूर्ण

अटल अंतरभूत पूर्णांक rnbd_dev_get_discard_alignment(स्थिर काष्ठा rnbd_dev *dev)
अणु
	वापस bdev_get_queue(dev->bdev)->limits.discard_alignment;
पूर्ण

#पूर्ण_अगर /* RNBD_SRV_DEV_H */
