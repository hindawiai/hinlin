<शैली गुरु>
/*
 * Copyright (C) 2004-2005 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_BIO_RECORD_H
#घोषणा DM_BIO_RECORD_H

#समावेश <linux/bपन.स>

/*
 * There are lots of mutable fields in the bio काष्ठा that get
 * changed by the lower levels of the block layer.  Some tarमाला_लो,
 * such as multipath, may wish to resubmit a bio on error.  The
 * functions in this file help the target record and restore the
 * original bio state.
 */

काष्ठा dm_bio_details अणु
	काष्ठा block_device *bi_bdev;
	पूर्णांक __bi_reमुख्यing;
	अचिन्हित दीर्घ bi_flags;
	काष्ठा bvec_iter bi_iter;
	bio_end_io_t *bi_end_io;
#अगर defined(CONFIG_BLK_DEV_INTEGRITY)
	काष्ठा bio_पूर्णांकegrity_payload *bi_पूर्णांकegrity;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत व्योम dm_bio_record(काष्ठा dm_bio_details *bd, काष्ठा bio *bio)
अणु
	bd->bi_bdev = bio->bi_bdev;
	bd->bi_flags = bio->bi_flags;
	bd->bi_iter = bio->bi_iter;
	bd->__bi_reमुख्यing = atomic_पढ़ो(&bio->__bi_reमुख्यing);
	bd->bi_end_io = bio->bi_end_io;
#अगर defined(CONFIG_BLK_DEV_INTEGRITY)
	bd->bi_पूर्णांकegrity = bio_पूर्णांकegrity(bio);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम dm_bio_restore(काष्ठा dm_bio_details *bd, काष्ठा bio *bio)
अणु
	bio->bi_bdev = bd->bi_bdev;
	bio->bi_flags = bd->bi_flags;
	bio->bi_iter = bd->bi_iter;
	atomic_set(&bio->__bi_reमुख्यing, bd->__bi_reमुख्यing);
	bio->bi_end_io = bd->bi_end_io;
#अगर defined(CONFIG_BLK_DEV_INTEGRITY)
	bio->bi_पूर्णांकegrity = bd->bi_पूर्णांकegrity;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर
