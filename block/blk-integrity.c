<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * blk-पूर्णांकegrity.c - Block layer data पूर्णांकegrity extensions
 *
 * Copyright (C) 2007, 2008 Oracle Corporation
 * Written by: Martin K. Petersen <martin.petersen@oracle.com>
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/mempool.h>
#समावेश <linux/bपन.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>

#समावेश "blk.h"

/**
 * blk_rq_count_पूर्णांकegrity_sg - Count number of पूर्णांकegrity scatterlist elements
 * @q:		request queue
 * @bio:	bio with पूर्णांकegrity metadata attached
 *
 * Description: Returns the number of elements required in a
 * scatterlist corresponding to the पूर्णांकegrity metadata in a bio.
 */
पूर्णांक blk_rq_count_पूर्णांकegrity_sg(काष्ठा request_queue *q, काष्ठा bio *bio)
अणु
	काष्ठा bio_vec iv, ivprv = अणु शून्य पूर्ण;
	अचिन्हित पूर्णांक segments = 0;
	अचिन्हित पूर्णांक seg_size = 0;
	काष्ठा bvec_iter iter;
	पूर्णांक prev = 0;

	bio_क्रम_each_पूर्णांकegrity_vec(iv, bio, iter) अणु

		अगर (prev) अणु
			अगर (!biovec_phys_mergeable(q, &ivprv, &iv))
				जाओ new_segment;
			अगर (seg_size + iv.bv_len > queue_max_segment_size(q))
				जाओ new_segment;

			seg_size += iv.bv_len;
		पूर्ण अन्यथा अणु
new_segment:
			segments++;
			seg_size = iv.bv_len;
		पूर्ण

		prev = 1;
		ivprv = iv;
	पूर्ण

	वापस segments;
पूर्ण
EXPORT_SYMBOL(blk_rq_count_पूर्णांकegrity_sg);

/**
 * blk_rq_map_पूर्णांकegrity_sg - Map पूर्णांकegrity metadata पूर्णांकo a scatterlist
 * @q:		request queue
 * @bio:	bio with पूर्णांकegrity metadata attached
 * @sglist:	target scatterlist
 *
 * Description: Map the पूर्णांकegrity vectors in request पूर्णांकo a
 * scatterlist.  The scatterlist must be big enough to hold all
 * elements.  I.e. sized using blk_rq_count_पूर्णांकegrity_sg().
 */
पूर्णांक blk_rq_map_पूर्णांकegrity_sg(काष्ठा request_queue *q, काष्ठा bio *bio,
			    काष्ठा scatterlist *sglist)
अणु
	काष्ठा bio_vec iv, ivprv = अणु शून्य पूर्ण;
	काष्ठा scatterlist *sg = शून्य;
	अचिन्हित पूर्णांक segments = 0;
	काष्ठा bvec_iter iter;
	पूर्णांक prev = 0;

	bio_क्रम_each_पूर्णांकegrity_vec(iv, bio, iter) अणु

		अगर (prev) अणु
			अगर (!biovec_phys_mergeable(q, &ivprv, &iv))
				जाओ new_segment;
			अगर (sg->length + iv.bv_len > queue_max_segment_size(q))
				जाओ new_segment;

			sg->length += iv.bv_len;
		पूर्ण अन्यथा अणु
new_segment:
			अगर (!sg)
				sg = sglist;
			अन्यथा अणु
				sg_unmark_end(sg);
				sg = sg_next(sg);
			पूर्ण

			sg_set_page(sg, iv.bv_page, iv.bv_len, iv.bv_offset);
			segments++;
		पूर्ण

		prev = 1;
		ivprv = iv;
	पूर्ण

	अगर (sg)
		sg_mark_end(sg);

	वापस segments;
पूर्ण
EXPORT_SYMBOL(blk_rq_map_पूर्णांकegrity_sg);

/**
 * blk_पूर्णांकegrity_compare - Compare पूर्णांकegrity profile of two disks
 * @gd1:	Disk to compare
 * @gd2:	Disk to compare
 *
 * Description: Meta-devices like DM and MD need to verअगरy that all
 * sub-devices use the same पूर्णांकegrity क्रमmat beक्रमe advertising to
 * upper layers that they can send/receive पूर्णांकegrity metadata.  This
 * function can be used to check whether two gendisk devices have
 * compatible पूर्णांकegrity क्रमmats.
 */
पूर्णांक blk_पूर्णांकegrity_compare(काष्ठा gendisk *gd1, काष्ठा gendisk *gd2)
अणु
	काष्ठा blk_पूर्णांकegrity *b1 = &gd1->queue->पूर्णांकegrity;
	काष्ठा blk_पूर्णांकegrity *b2 = &gd2->queue->पूर्णांकegrity;

	अगर (!b1->profile && !b2->profile)
		वापस 0;

	अगर (!b1->profile || !b2->profile)
		वापस -1;

	अगर (b1->पूर्णांकerval_exp != b2->पूर्णांकerval_exp) अणु
		pr_err("%s: %s/%s protection interval %u != %u\n",
		       __func__, gd1->disk_name, gd2->disk_name,
		       1 << b1->पूर्णांकerval_exp, 1 << b2->पूर्णांकerval_exp);
		वापस -1;
	पूर्ण

	अगर (b1->tuple_size != b2->tuple_size) अणु
		pr_err("%s: %s/%s tuple sz %u != %u\n", __func__,
		       gd1->disk_name, gd2->disk_name,
		       b1->tuple_size, b2->tuple_size);
		वापस -1;
	पूर्ण

	अगर (b1->tag_size && b2->tag_size && (b1->tag_size != b2->tag_size)) अणु
		pr_err("%s: %s/%s tag sz %u != %u\n", __func__,
		       gd1->disk_name, gd2->disk_name,
		       b1->tag_size, b2->tag_size);
		वापस -1;
	पूर्ण

	अगर (b1->profile != b2->profile) अणु
		pr_err("%s: %s/%s type %s != %s\n", __func__,
		       gd1->disk_name, gd2->disk_name,
		       b1->profile->name, b2->profile->name);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(blk_पूर्णांकegrity_compare);

bool blk_पूर्णांकegrity_merge_rq(काष्ठा request_queue *q, काष्ठा request *req,
			    काष्ठा request *next)
अणु
	अगर (blk_पूर्णांकegrity_rq(req) == 0 && blk_पूर्णांकegrity_rq(next) == 0)
		वापस true;

	अगर (blk_पूर्णांकegrity_rq(req) == 0 || blk_पूर्णांकegrity_rq(next) == 0)
		वापस false;

	अगर (bio_पूर्णांकegrity(req->bio)->bip_flags !=
	    bio_पूर्णांकegrity(next->bio)->bip_flags)
		वापस false;

	अगर (req->nr_पूर्णांकegrity_segments + next->nr_पूर्णांकegrity_segments >
	    q->limits.max_पूर्णांकegrity_segments)
		वापस false;

	अगर (पूर्णांकegrity_req_gap_back_merge(req, next->bio))
		वापस false;

	वापस true;
पूर्ण

bool blk_पूर्णांकegrity_merge_bio(काष्ठा request_queue *q, काष्ठा request *req,
			     काष्ठा bio *bio)
अणु
	पूर्णांक nr_पूर्णांकegrity_segs;
	काष्ठा bio *next = bio->bi_next;

	अगर (blk_पूर्णांकegrity_rq(req) == 0 && bio_पूर्णांकegrity(bio) == शून्य)
		वापस true;

	अगर (blk_पूर्णांकegrity_rq(req) == 0 || bio_पूर्णांकegrity(bio) == शून्य)
		वापस false;

	अगर (bio_पूर्णांकegrity(req->bio)->bip_flags != bio_पूर्णांकegrity(bio)->bip_flags)
		वापस false;

	bio->bi_next = शून्य;
	nr_पूर्णांकegrity_segs = blk_rq_count_पूर्णांकegrity_sg(q, bio);
	bio->bi_next = next;

	अगर (req->nr_पूर्णांकegrity_segments + nr_पूर्णांकegrity_segs >
	    q->limits.max_पूर्णांकegrity_segments)
		वापस false;

	req->nr_पूर्णांकegrity_segments += nr_पूर्णांकegrity_segs;

	वापस true;
पूर्ण

काष्ठा पूर्णांकegrity_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा blk_पूर्णांकegrity *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा blk_पूर्णांकegrity *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

अटल sमाप_प्रकार पूर्णांकegrity_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				   अक्षर *page)
अणु
	काष्ठा gendisk *disk = container_of(kobj, काष्ठा gendisk, पूर्णांकegrity_kobj);
	काष्ठा blk_पूर्णांकegrity *bi = &disk->queue->पूर्णांकegrity;
	काष्ठा पूर्णांकegrity_sysfs_entry *entry =
		container_of(attr, काष्ठा पूर्णांकegrity_sysfs_entry, attr);

	वापस entry->show(bi, page);
पूर्ण

अटल sमाप_प्रकार पूर्णांकegrity_attr_store(काष्ठा kobject *kobj,
				    काष्ठा attribute *attr, स्थिर अक्षर *page,
				    माप_प्रकार count)
अणु
	काष्ठा gendisk *disk = container_of(kobj, काष्ठा gendisk, पूर्णांकegrity_kobj);
	काष्ठा blk_पूर्णांकegrity *bi = &disk->queue->पूर्णांकegrity;
	काष्ठा पूर्णांकegrity_sysfs_entry *entry =
		container_of(attr, काष्ठा पूर्णांकegrity_sysfs_entry, attr);
	sमाप_प्रकार ret = 0;

	अगर (entry->store)
		ret = entry->store(bi, page, count);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार पूर्णांकegrity_क्रमmat_show(काष्ठा blk_पूर्णांकegrity *bi, अक्षर *page)
अणु
	अगर (bi->profile && bi->profile->name)
		वापस प्र_लिखो(page, "%s\n", bi->profile->name);
	अन्यथा
		वापस प्र_लिखो(page, "none\n");
पूर्ण

अटल sमाप_प्रकार पूर्णांकegrity_tag_size_show(काष्ठा blk_पूर्णांकegrity *bi, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", bi->tag_size);
पूर्ण

अटल sमाप_प्रकार पूर्णांकegrity_पूर्णांकerval_show(काष्ठा blk_पूर्णांकegrity *bi, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n",
		       bi->पूर्णांकerval_exp ? 1 << bi->पूर्णांकerval_exp : 0);
पूर्ण

अटल sमाप_प्रकार पूर्णांकegrity_verअगरy_store(काष्ठा blk_पूर्णांकegrity *bi,
				      स्थिर अक्षर *page, माप_प्रकार count)
अणु
	अक्षर *p = (अक्षर *) page;
	अचिन्हित दीर्घ val = simple_म_से_अदीर्घ(p, &p, 10);

	अगर (val)
		bi->flags |= BLK_INTEGRITY_VERIFY;
	अन्यथा
		bi->flags &= ~BLK_INTEGRITY_VERIFY;

	वापस count;
पूर्ण

अटल sमाप_प्रकार पूर्णांकegrity_verअगरy_show(काष्ठा blk_पूर्णांकegrity *bi, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", (bi->flags & BLK_INTEGRITY_VERIFY) != 0);
पूर्ण

अटल sमाप_प्रकार पूर्णांकegrity_generate_store(काष्ठा blk_पूर्णांकegrity *bi,
					स्थिर अक्षर *page, माप_प्रकार count)
अणु
	अक्षर *p = (अक्षर *) page;
	अचिन्हित दीर्घ val = simple_म_से_अदीर्घ(p, &p, 10);

	अगर (val)
		bi->flags |= BLK_INTEGRITY_GENERATE;
	अन्यथा
		bi->flags &= ~BLK_INTEGRITY_GENERATE;

	वापस count;
पूर्ण

अटल sमाप_प्रकार पूर्णांकegrity_generate_show(काष्ठा blk_पूर्णांकegrity *bi, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", (bi->flags & BLK_INTEGRITY_GENERATE) != 0);
पूर्ण

अटल sमाप_प्रकार पूर्णांकegrity_device_show(काष्ठा blk_पूर्णांकegrity *bi, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n",
		       (bi->flags & BLK_INTEGRITY_DEVICE_CAPABLE) != 0);
पूर्ण

अटल काष्ठा पूर्णांकegrity_sysfs_entry पूर्णांकegrity_क्रमmat_entry = अणु
	.attr = अणु .name = "format", .mode = 0444 पूर्ण,
	.show = पूर्णांकegrity_क्रमmat_show,
पूर्ण;

अटल काष्ठा पूर्णांकegrity_sysfs_entry पूर्णांकegrity_tag_size_entry = अणु
	.attr = अणु .name = "tag_size", .mode = 0444 पूर्ण,
	.show = पूर्णांकegrity_tag_size_show,
पूर्ण;

अटल काष्ठा पूर्णांकegrity_sysfs_entry पूर्णांकegrity_पूर्णांकerval_entry = अणु
	.attr = अणु .name = "protection_interval_bytes", .mode = 0444 पूर्ण,
	.show = पूर्णांकegrity_पूर्णांकerval_show,
पूर्ण;

अटल काष्ठा पूर्णांकegrity_sysfs_entry पूर्णांकegrity_verअगरy_entry = अणु
	.attr = अणु .name = "read_verify", .mode = 0644 पूर्ण,
	.show = पूर्णांकegrity_verअगरy_show,
	.store = पूर्णांकegrity_verअगरy_store,
पूर्ण;

अटल काष्ठा पूर्णांकegrity_sysfs_entry पूर्णांकegrity_generate_entry = अणु
	.attr = अणु .name = "write_generate", .mode = 0644 पूर्ण,
	.show = पूर्णांकegrity_generate_show,
	.store = पूर्णांकegrity_generate_store,
पूर्ण;

अटल काष्ठा पूर्णांकegrity_sysfs_entry पूर्णांकegrity_device_entry = अणु
	.attr = अणु .name = "device_is_integrity_capable", .mode = 0444 पूर्ण,
	.show = पूर्णांकegrity_device_show,
पूर्ण;

अटल काष्ठा attribute *पूर्णांकegrity_attrs[] = अणु
	&पूर्णांकegrity_क्रमmat_entry.attr,
	&पूर्णांकegrity_tag_size_entry.attr,
	&पूर्णांकegrity_पूर्णांकerval_entry.attr,
	&पूर्णांकegrity_verअगरy_entry.attr,
	&पूर्णांकegrity_generate_entry.attr,
	&पूर्णांकegrity_device_entry.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(पूर्णांकegrity);

अटल स्थिर काष्ठा sysfs_ops पूर्णांकegrity_ops = अणु
	.show	= &पूर्णांकegrity_attr_show,
	.store	= &पूर्णांकegrity_attr_store,
पूर्ण;

अटल काष्ठा kobj_type पूर्णांकegrity_ktype = अणु
	.शेष_groups = पूर्णांकegrity_groups,
	.sysfs_ops	= &पूर्णांकegrity_ops,
पूर्ण;

अटल blk_status_t blk_पूर्णांकegrity_nop_fn(काष्ठा blk_पूर्णांकegrity_iter *iter)
अणु
	वापस BLK_STS_OK;
पूर्ण

अटल व्योम blk_पूर्णांकegrity_nop_prepare(काष्ठा request *rq)
अणु
पूर्ण

अटल व्योम blk_पूर्णांकegrity_nop_complete(काष्ठा request *rq,
		अचिन्हित पूर्णांक nr_bytes)
अणु
पूर्ण

अटल स्थिर काष्ठा blk_पूर्णांकegrity_profile nop_profile = अणु
	.name = "nop",
	.generate_fn = blk_पूर्णांकegrity_nop_fn,
	.verअगरy_fn = blk_पूर्णांकegrity_nop_fn,
	.prepare_fn = blk_पूर्णांकegrity_nop_prepare,
	.complete_fn = blk_पूर्णांकegrity_nop_complete,
पूर्ण;

/**
 * blk_पूर्णांकegrity_रेजिस्टर - Register a gendisk as being पूर्णांकegrity-capable
 * @disk:	काष्ठा gendisk poपूर्णांकer to make पूर्णांकegrity-aware
 * @ढाँचा:	block पूर्णांकegrity profile to रेजिस्टर
 *
 * Description: When a device needs to advertise itself as being able to
 * send/receive पूर्णांकegrity metadata it must use this function to रेजिस्टर
 * the capability with the block layer. The ढाँचा is a blk_पूर्णांकegrity
 * काष्ठा with values appropriate क्रम the underlying hardware. See
 * Documentation/block/data-पूर्णांकegrity.rst.
 */
व्योम blk_पूर्णांकegrity_रेजिस्टर(काष्ठा gendisk *disk, काष्ठा blk_पूर्णांकegrity *ढाँचा)
अणु
	काष्ठा blk_पूर्णांकegrity *bi = &disk->queue->पूर्णांकegrity;

	bi->flags = BLK_INTEGRITY_VERIFY | BLK_INTEGRITY_GENERATE |
		ढाँचा->flags;
	bi->पूर्णांकerval_exp = ढाँचा->पूर्णांकerval_exp ? :
		ilog2(queue_logical_block_size(disk->queue));
	bi->profile = ढाँचा->profile ? ढाँचा->profile : &nop_profile;
	bi->tuple_size = ढाँचा->tuple_size;
	bi->tag_size = ढाँचा->tag_size;

	blk_queue_flag_set(QUEUE_FLAG_STABLE_WRITES, disk->queue);

#अगर_घोषित CONFIG_BLK_INLINE_ENCRYPTION
	अगर (disk->queue->ksm) अणु
		pr_warn("blk-integrity: Integrity and hardware inline encryption are not supported together. Disabling hardware inline encryption.\n");
		blk_ksm_unरेजिस्टर(disk->queue);
	पूर्ण
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(blk_पूर्णांकegrity_रेजिस्टर);

/**
 * blk_पूर्णांकegrity_unरेजिस्टर - Unरेजिस्टर block पूर्णांकegrity profile
 * @disk:	disk whose पूर्णांकegrity profile to unरेजिस्टर
 *
 * Description: This function unरेजिस्टरs the पूर्णांकegrity capability from
 * a block device.
 */
व्योम blk_पूर्णांकegrity_unरेजिस्टर(काष्ठा gendisk *disk)
अणु
	blk_queue_flag_clear(QUEUE_FLAG_STABLE_WRITES, disk->queue);
	स_रखो(&disk->queue->पूर्णांकegrity, 0, माप(काष्ठा blk_पूर्णांकegrity));
पूर्ण
EXPORT_SYMBOL(blk_पूर्णांकegrity_unरेजिस्टर);

व्योम blk_पूर्णांकegrity_add(काष्ठा gendisk *disk)
अणु
	अगर (kobject_init_and_add(&disk->पूर्णांकegrity_kobj, &पूर्णांकegrity_ktype,
				 &disk_to_dev(disk)->kobj, "%s", "integrity"))
		वापस;

	kobject_uevent(&disk->पूर्णांकegrity_kobj, KOBJ_ADD);
पूर्ण

व्योम blk_पूर्णांकegrity_del(काष्ठा gendisk *disk)
अणु
	kobject_uevent(&disk->पूर्णांकegrity_kobj, KOBJ_REMOVE);
	kobject_del(&disk->पूर्णांकegrity_kobj);
	kobject_put(&disk->पूर्णांकegrity_kobj);
पूर्ण
