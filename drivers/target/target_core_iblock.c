<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_iblock.c
 *
 * This file contains the Storage Engine  <-> Linux BlockIO transport
 * specअगरic functions.
 *
 * (c) Copyright 2003-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 ******************************************************************************/

#समावेश <linux/माला.स>
#समावेश <linux/parser.h>
#समावेश <linux/समयr.h>
#समावेश <linux/fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bपन.स>
#समावेश <linux/genhd.h>
#समावेश <linux/file.h>
#समावेश <linux/module.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>

#समावेश "target_core_iblock.h"

#घोषणा IBLOCK_MAX_BIO_PER_TASK	 32	/* max # of bios to submit at a समय */
#घोषणा IBLOCK_BIO_POOL_SIZE	128

अटल अंतरभूत काष्ठा iblock_dev *IBLOCK_DEV(काष्ठा se_device *dev)
अणु
	वापस container_of(dev, काष्ठा iblock_dev, dev);
पूर्ण


अटल पूर्णांक iblock_attach_hba(काष्ठा se_hba *hba, u32 host_id)
अणु
	pr_debug("CORE_HBA[%d] - TCM iBlock HBA Driver %s on"
		" Generic Target Core Stack %s\n", hba->hba_id,
		IBLOCK_VERSION, TARGET_CORE_VERSION);
	वापस 0;
पूर्ण

अटल व्योम iblock_detach_hba(काष्ठा se_hba *hba)
अणु
पूर्ण

अटल काष्ठा se_device *iblock_alloc_device(काष्ठा se_hba *hba, स्थिर अक्षर *name)
अणु
	काष्ठा iblock_dev *ib_dev = शून्य;

	ib_dev = kzalloc(माप(काष्ठा iblock_dev), GFP_KERNEL);
	अगर (!ib_dev) अणु
		pr_err("Unable to allocate struct iblock_dev\n");
		वापस शून्य;
	पूर्ण

	ib_dev->ibd_plug = kसुस्मृति(nr_cpu_ids, माप(*ib_dev->ibd_plug),
				   GFP_KERNEL);
	अगर (!ib_dev->ibd_plug)
		जाओ मुक्त_dev;

	pr_debug( "IBLOCK: Allocated ib_dev for %s\n", name);

	वापस &ib_dev->dev;

मुक्त_dev:
	kमुक्त(ib_dev);
	वापस शून्य;
पूर्ण

अटल पूर्णांक iblock_configure_device(काष्ठा se_device *dev)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);
	काष्ठा request_queue *q;
	काष्ठा block_device *bd = शून्य;
	काष्ठा blk_पूर्णांकegrity *bi;
	भ_शेषe_t mode;
	अचिन्हित पूर्णांक max_ग_लिखो_zeroes_sectors;
	पूर्णांक ret = -ENOMEM;

	अगर (!(ib_dev->ibd_flags & IBDF_HAS_UDEV_PATH)) अणु
		pr_err("Missing udev_path= parameters for IBLOCK\n");
		वापस -EINVAL;
	पूर्ण

	ret = bioset_init(&ib_dev->ibd_bio_set, IBLOCK_BIO_POOL_SIZE, 0, BIOSET_NEED_BVECS);
	अगर (ret) अणु
		pr_err("IBLOCK: Unable to create bioset\n");
		जाओ out;
	पूर्ण

	pr_debug( "IBLOCK: Claiming struct block_device: %s\n",
			ib_dev->ibd_udev_path);

	mode = FMODE_READ|FMODE_EXCL;
	अगर (!ib_dev->ibd_पढ़ोonly)
		mode |= FMODE_WRITE;
	अन्यथा
		dev->dev_flags |= DF_READ_ONLY;

	bd = blkdev_get_by_path(ib_dev->ibd_udev_path, mode, ib_dev);
	अगर (IS_ERR(bd)) अणु
		ret = PTR_ERR(bd);
		जाओ out_मुक्त_bioset;
	पूर्ण
	ib_dev->ibd_bd = bd;

	q = bdev_get_queue(bd);

	dev->dev_attrib.hw_block_size = bdev_logical_block_size(bd);
	dev->dev_attrib.hw_max_sectors = queue_max_hw_sectors(q);
	dev->dev_attrib.hw_queue_depth = q->nr_requests;

	अगर (target_configure_unmap_from_queue(&dev->dev_attrib, q))
		pr_debug("IBLOCK: BLOCK Discard support available,"
			 " disabled by default\n");

	/*
	 * Enable ग_लिखो same emulation क्रम IBLOCK and use 0xFFFF as
	 * the smaller WRITE_SAME(10) only has a two-byte block count.
	 */
	max_ग_लिखो_zeroes_sectors = bdev_ग_लिखो_zeroes_sectors(bd);
	अगर (max_ग_लिखो_zeroes_sectors)
		dev->dev_attrib.max_ग_लिखो_same_len = max_ग_लिखो_zeroes_sectors;
	अन्यथा
		dev->dev_attrib.max_ग_लिखो_same_len = 0xFFFF;

	अगर (blk_queue_nonrot(q))
		dev->dev_attrib.is_nonrot = 1;

	bi = bdev_get_पूर्णांकegrity(bd);
	अगर (bi) अणु
		काष्ठा bio_set *bs = &ib_dev->ibd_bio_set;

		अगर (!म_भेद(bi->profile->name, "T10-DIF-TYPE3-IP") ||
		    !म_भेद(bi->profile->name, "T10-DIF-TYPE1-IP")) अणु
			pr_err("IBLOCK export of blk_integrity: %s not"
			       " supported\n", bi->profile->name);
			ret = -ENOSYS;
			जाओ out_blkdev_put;
		पूर्ण

		अगर (!म_भेद(bi->profile->name, "T10-DIF-TYPE3-CRC")) अणु
			dev->dev_attrib.pi_prot_type = TARGET_DIF_TYPE3_PROT;
		पूर्ण अन्यथा अगर (!म_भेद(bi->profile->name, "T10-DIF-TYPE1-CRC")) अणु
			dev->dev_attrib.pi_prot_type = TARGET_DIF_TYPE1_PROT;
		पूर्ण

		अगर (dev->dev_attrib.pi_prot_type) अणु
			अगर (bioset_पूर्णांकegrity_create(bs, IBLOCK_BIO_POOL_SIZE) < 0) अणु
				pr_err("Unable to allocate bioset for PI\n");
				ret = -ENOMEM;
				जाओ out_blkdev_put;
			पूर्ण
			pr_debug("IBLOCK setup BIP bs->bio_integrity_pool: %p\n",
				 &bs->bio_पूर्णांकegrity_pool);
		पूर्ण
		dev->dev_attrib.hw_pi_prot_type = dev->dev_attrib.pi_prot_type;
	पूर्ण

	वापस 0;

out_blkdev_put:
	blkdev_put(ib_dev->ibd_bd, FMODE_WRITE|FMODE_READ|FMODE_EXCL);
out_मुक्त_bioset:
	bioset_निकास(&ib_dev->ibd_bio_set);
out:
	वापस ret;
पूर्ण

अटल व्योम iblock_dev_call_rcu(काष्ठा rcu_head *p)
अणु
	काष्ठा se_device *dev = container_of(p, काष्ठा se_device, rcu_head);
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);

	kमुक्त(ib_dev->ibd_plug);
	kमुक्त(ib_dev);
पूर्ण

अटल व्योम iblock_मुक्त_device(काष्ठा se_device *dev)
अणु
	call_rcu(&dev->rcu_head, iblock_dev_call_rcu);
पूर्ण

अटल व्योम iblock_destroy_device(काष्ठा se_device *dev)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);

	अगर (ib_dev->ibd_bd != शून्य)
		blkdev_put(ib_dev->ibd_bd, FMODE_WRITE|FMODE_READ|FMODE_EXCL);
	bioset_निकास(&ib_dev->ibd_bio_set);
पूर्ण

अटल काष्ठा se_dev_plug *iblock_plug_device(काष्ठा se_device *se_dev)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(se_dev);
	काष्ठा iblock_dev_plug *ib_dev_plug;

	/*
	 * Each se_device has a per cpu work this can be run from. We
	 * shouldn't have multiple thपढ़ोs on the same cpu calling this
	 * at the same समय.
	 */
	ib_dev_plug = &ib_dev->ibd_plug[raw_smp_processor_id()];
	अगर (test_and_set_bit(IBD_PLUGF_PLUGGED, &ib_dev_plug->flags))
		वापस शून्य;

	blk_start_plug(&ib_dev_plug->blk_plug);
	वापस &ib_dev_plug->se_plug;
पूर्ण

अटल व्योम iblock_unplug_device(काष्ठा se_dev_plug *se_plug)
अणु
	काष्ठा iblock_dev_plug *ib_dev_plug = container_of(se_plug,
					काष्ठा iblock_dev_plug, se_plug);

	blk_finish_plug(&ib_dev_plug->blk_plug);
	clear_bit(IBD_PLUGF_PLUGGED, &ib_dev_plug->flags);
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ iblock_emulate_पढ़ो_cap_with_block_size(
	काष्ठा se_device *dev,
	काष्ठा block_device *bd,
	काष्ठा request_queue *q)
अणु
	अचिन्हित दीर्घ दीर्घ blocks_दीर्घ = (भाग_u64(i_size_पढ़ो(bd->bd_inode),
					bdev_logical_block_size(bd)) - 1);
	u32 block_size = bdev_logical_block_size(bd);

	अगर (block_size == dev->dev_attrib.block_size)
		वापस blocks_दीर्घ;

	चयन (block_size) अणु
	हाल 4096:
		चयन (dev->dev_attrib.block_size) अणु
		हाल 2048:
			blocks_दीर्घ <<= 1;
			अवरोध;
		हाल 1024:
			blocks_दीर्घ <<= 2;
			अवरोध;
		हाल 512:
			blocks_दीर्घ <<= 3;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 2048:
		चयन (dev->dev_attrib.block_size) अणु
		हाल 4096:
			blocks_दीर्घ >>= 1;
			अवरोध;
		हाल 1024:
			blocks_दीर्घ <<= 1;
			अवरोध;
		हाल 512:
			blocks_दीर्घ <<= 2;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 1024:
		चयन (dev->dev_attrib.block_size) अणु
		हाल 4096:
			blocks_दीर्घ >>= 2;
			अवरोध;
		हाल 2048:
			blocks_दीर्घ >>= 1;
			अवरोध;
		हाल 512:
			blocks_दीर्घ <<= 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 512:
		चयन (dev->dev_attrib.block_size) अणु
		हाल 4096:
			blocks_दीर्घ >>= 3;
			अवरोध;
		हाल 2048:
			blocks_दीर्घ >>= 2;
			अवरोध;
		हाल 1024:
			blocks_दीर्घ >>= 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस blocks_दीर्घ;
पूर्ण

अटल व्योम iblock_complete_cmd(काष्ठा se_cmd *cmd)
अणु
	काष्ठा iblock_req *ibr = cmd->priv;
	u8 status;

	अगर (!refcount_dec_and_test(&ibr->pending))
		वापस;

	अगर (atomic_पढ़ो(&ibr->ib_bio_err_cnt))
		status = SAM_STAT_CHECK_CONDITION;
	अन्यथा
		status = SAM_STAT_GOOD;

	target_complete_cmd(cmd, status);
	kमुक्त(ibr);
पूर्ण

अटल व्योम iblock_bio_करोne(काष्ठा bio *bio)
अणु
	काष्ठा se_cmd *cmd = bio->bi_निजी;
	काष्ठा iblock_req *ibr = cmd->priv;

	अगर (bio->bi_status) अणु
		pr_err("bio error: %p,  err: %d\n", bio, bio->bi_status);
		/*
		 * Bump the ib_bio_err_cnt and release bio.
		 */
		atomic_inc(&ibr->ib_bio_err_cnt);
		smp_mb__after_atomic();
	पूर्ण

	bio_put(bio);

	iblock_complete_cmd(cmd);
पूर्ण

अटल काष्ठा bio *iblock_get_bio(काष्ठा se_cmd *cmd, sector_t lba, u32 sg_num,
				  अचिन्हित पूर्णांक opf)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(cmd->se_dev);
	काष्ठा bio *bio;

	/*
	 * Only allocate as many vector entries as the bio code allows us to,
	 * we'll loop later on until we have handled the whole request.
	 */
	bio = bio_alloc_bioset(GFP_NOIO, bio_max_segs(sg_num),
				&ib_dev->ibd_bio_set);
	अगर (!bio) अणु
		pr_err("Unable to allocate memory for bio\n");
		वापस शून्य;
	पूर्ण

	bio_set_dev(bio, ib_dev->ibd_bd);
	bio->bi_निजी = cmd;
	bio->bi_end_io = &iblock_bio_करोne;
	bio->bi_iter.bi_sector = lba;
	bio->bi_opf = opf;

	वापस bio;
पूर्ण

अटल व्योम iblock_submit_bios(काष्ठा bio_list *list)
अणु
	काष्ठा blk_plug plug;
	काष्ठा bio *bio;
	/*
	 * The block layer handles nested plugs, so just plug/unplug to handle
	 * fabric drivers that didn't support batching and multi bio cmds.
	 */
	blk_start_plug(&plug);
	जबतक ((bio = bio_list_pop(list)))
		submit_bio(bio);
	blk_finish_plug(&plug);
पूर्ण

अटल व्योम iblock_end_io_flush(काष्ठा bio *bio)
अणु
	काष्ठा se_cmd *cmd = bio->bi_निजी;

	अगर (bio->bi_status)
		pr_err("IBLOCK: cache flush failed: %d\n", bio->bi_status);

	अगर (cmd) अणु
		अगर (bio->bi_status)
			target_complete_cmd(cmd, SAM_STAT_CHECK_CONDITION);
		अन्यथा
			target_complete_cmd(cmd, SAM_STAT_GOOD);
	पूर्ण

	bio_put(bio);
पूर्ण

/*
 * Implement SYCHRONIZE CACHE.  Note that we can't handle lba ranges and must
 * always flush the whole cache.
 */
अटल sense_reason_t
iblock_execute_sync_cache(काष्ठा se_cmd *cmd)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(cmd->se_dev);
	पूर्णांक immed = (cmd->t_task_cdb[1] & 0x2);
	काष्ठा bio *bio;

	/*
	 * If the Immediate bit is set, queue up the GOOD response
	 * क्रम this SYNCHRONIZE_CACHE op.
	 */
	अगर (immed)
		target_complete_cmd(cmd, SAM_STAT_GOOD);

	bio = bio_alloc(GFP_KERNEL, 0);
	bio->bi_end_io = iblock_end_io_flush;
	bio_set_dev(bio, ib_dev->ibd_bd);
	bio->bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;
	अगर (!immed)
		bio->bi_निजी = cmd;
	submit_bio(bio);
	वापस 0;
पूर्ण

अटल sense_reason_t
iblock_execute_unmap(काष्ठा se_cmd *cmd, sector_t lba, sector_t nolb)
अणु
	काष्ठा block_device *bdev = IBLOCK_DEV(cmd->se_dev)->ibd_bd;
	काष्ठा se_device *dev = cmd->se_dev;
	पूर्णांक ret;

	ret = blkdev_issue_discard(bdev,
				   target_to_linux_sector(dev, lba),
				   target_to_linux_sector(dev,  nolb),
				   GFP_KERNEL, 0);
	अगर (ret < 0) अणु
		pr_err("blkdev_issue_discard() failed: %d\n", ret);
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण

	वापस 0;
पूर्ण

अटल sense_reason_t
iblock_execute_zero_out(काष्ठा block_device *bdev, काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा scatterlist *sg = &cmd->t_data_sg[0];
	अचिन्हित अक्षर *buf, *not_zero;
	पूर्णांक ret;

	buf = kmap(sg_page(sg)) + sg->offset;
	अगर (!buf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	/*
	 * Fall back to block_execute_ग_लिखो_same() slow-path अगर
	 * incoming WRITE_SAME payload करोes not contain zeros.
	 */
	not_zero = स_प्रथम_inv(buf, 0x00, cmd->data_length);
	kunmap(sg_page(sg));

	अगर (not_zero)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	ret = blkdev_issue_zeroout(bdev,
				target_to_linux_sector(dev, cmd->t_task_lba),
				target_to_linux_sector(dev,
					sbc_get_ग_लिखो_same_sectors(cmd)),
				GFP_KERNEL, BLKDEV_ZERO_NOUNMAP);
	अगर (ret)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	target_complete_cmd(cmd, GOOD);
	वापस 0;
पूर्ण

अटल sense_reason_t
iblock_execute_ग_लिखो_same(काष्ठा se_cmd *cmd)
अणु
	काष्ठा block_device *bdev = IBLOCK_DEV(cmd->se_dev)->ibd_bd;
	काष्ठा iblock_req *ibr;
	काष्ठा scatterlist *sg;
	काष्ठा bio *bio;
	काष्ठा bio_list list;
	काष्ठा se_device *dev = cmd->se_dev;
	sector_t block_lba = target_to_linux_sector(dev, cmd->t_task_lba);
	sector_t sectors = target_to_linux_sector(dev,
					sbc_get_ग_लिखो_same_sectors(cmd));

	अगर (cmd->prot_op) अणु
		pr_err("WRITE_SAME: Protection information with IBLOCK"
		       " backends not supported\n");
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	sg = &cmd->t_data_sg[0];

	अगर (cmd->t_data_nents > 1 ||
	    sg->length != cmd->se_dev->dev_attrib.block_size) अणु
		pr_err("WRITE_SAME: Illegal SGL t_data_nents: %u length: %u"
			" block_size: %u\n", cmd->t_data_nents, sg->length,
			cmd->se_dev->dev_attrib.block_size);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	अगर (bdev_ग_लिखो_zeroes_sectors(bdev)) अणु
		अगर (!iblock_execute_zero_out(bdev, cmd))
			वापस 0;
	पूर्ण

	ibr = kzalloc(माप(काष्ठा iblock_req), GFP_KERNEL);
	अगर (!ibr)
		जाओ fail;
	cmd->priv = ibr;

	bio = iblock_get_bio(cmd, block_lba, 1, REQ_OP_WRITE);
	अगर (!bio)
		जाओ fail_मुक्त_ibr;

	bio_list_init(&list);
	bio_list_add(&list, bio);

	refcount_set(&ibr->pending, 1);

	जबतक (sectors) अणु
		जबतक (bio_add_page(bio, sg_page(sg), sg->length, sg->offset)
				!= sg->length) अणु

			bio = iblock_get_bio(cmd, block_lba, 1, REQ_OP_WRITE);
			अगर (!bio)
				जाओ fail_put_bios;

			refcount_inc(&ibr->pending);
			bio_list_add(&list, bio);
		पूर्ण

		/* Always in 512 byte units क्रम Linux/Block */
		block_lba += sg->length >> SECTOR_SHIFT;
		sectors -= sg->length >> SECTOR_SHIFT;
	पूर्ण

	iblock_submit_bios(&list);
	वापस 0;

fail_put_bios:
	जबतक ((bio = bio_list_pop(&list)))
		bio_put(bio);
fail_मुक्त_ibr:
	kमुक्त(ibr);
fail:
	वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
पूर्ण

क्रमागत अणु
	Opt_udev_path, Opt_पढ़ोonly, Opt_क्रमce, Opt_err
पूर्ण;

अटल match_table_t tokens = अणु
	अणुOpt_udev_path, "udev_path=%s"पूर्ण,
	अणुOpt_पढ़ोonly, "readonly=%d"पूर्ण,
	अणुOpt_क्रमce, "force=%d"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल sमाप_प्रकार iblock_set_configfs_dev_params(काष्ठा se_device *dev,
		स्थिर अक्षर *page, sमाप_प्रकार count)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);
	अक्षर *orig, *ptr, *arg_p, *opts;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक ret = 0, token;
	अचिन्हित दीर्घ पंचांगp_पढ़ोonly;

	opts = kstrdup(page, GFP_KERNEL);
	अगर (!opts)
		वापस -ENOMEM;

	orig = opts;

	जबतक ((ptr = strsep(&opts, ",\n")) != शून्य) अणु
		अगर (!*ptr)
			जारी;

		token = match_token(ptr, tokens, args);
		चयन (token) अणु
		हाल Opt_udev_path:
			अगर (ib_dev->ibd_bd) अणु
				pr_err("Unable to set udev_path= while"
					" ib_dev->ibd_bd exists\n");
				ret = -EEXIST;
				जाओ out;
			पूर्ण
			अगर (match_strlcpy(ib_dev->ibd_udev_path, &args[0],
				SE_UDEV_PATH_LEN) == 0) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			pr_debug("IBLOCK: Referencing UDEV path: %s\n",
					ib_dev->ibd_udev_path);
			ib_dev->ibd_flags |= IBDF_HAS_UDEV_PATH;
			अवरोध;
		हाल Opt_पढ़ोonly:
			arg_p = match_strdup(&args[0]);
			अगर (!arg_p) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण
			ret = kम_से_अदीर्घ(arg_p, 0, &पंचांगp_पढ़ोonly);
			kमुक्त(arg_p);
			अगर (ret < 0) अणु
				pr_err("kstrtoul() failed for"
						" readonly=\n");
				जाओ out;
			पूर्ण
			ib_dev->ibd_पढ़ोonly = पंचांगp_पढ़ोonly;
			pr_debug("IBLOCK: readonly: %d\n", ib_dev->ibd_पढ़ोonly);
			अवरोध;
		हाल Opt_क्रमce:
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

out:
	kमुक्त(orig);
	वापस (!ret) ? count : ret;
पूर्ण

अटल sमाप_प्रकार iblock_show_configfs_dev_params(काष्ठा se_device *dev, अक्षर *b)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);
	काष्ठा block_device *bd = ib_dev->ibd_bd;
	अक्षर buf[BDEVNAME_SIZE];
	sमाप_प्रकार bl = 0;

	अगर (bd)
		bl += प्र_लिखो(b + bl, "iBlock device: %s",
				bdevname(bd, buf));
	अगर (ib_dev->ibd_flags & IBDF_HAS_UDEV_PATH)
		bl += प्र_लिखो(b + bl, "  UDEV PATH: %s",
				ib_dev->ibd_udev_path);
	bl += प्र_लिखो(b + bl, "  readonly: %d\n", ib_dev->ibd_पढ़ोonly);

	bl += प्र_लिखो(b + bl, "        ");
	अगर (bd) अणु
		bl += प्र_लिखो(b + bl, "Major: %d Minor: %d  %s\n",
			MAJOR(bd->bd_dev), MINOR(bd->bd_dev),
			"CLAIMED: IBLOCK");
	पूर्ण अन्यथा अणु
		bl += प्र_लिखो(b + bl, "Major: 0 Minor: 0\n");
	पूर्ण

	वापस bl;
पूर्ण

अटल पूर्णांक
iblock_alloc_bip(काष्ठा se_cmd *cmd, काष्ठा bio *bio,
		 काष्ठा sg_mapping_iter *miter)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा blk_पूर्णांकegrity *bi;
	काष्ठा bio_पूर्णांकegrity_payload *bip;
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);
	पूर्णांक rc;
	माप_प्रकार resid, len;

	bi = bdev_get_पूर्णांकegrity(ib_dev->ibd_bd);
	अगर (!bi) अणु
		pr_err("Unable to locate bio_integrity\n");
		वापस -ENODEV;
	पूर्ण

	bip = bio_पूर्णांकegrity_alloc(bio, GFP_NOIO, bio_max_segs(cmd->t_prot_nents));
	अगर (IS_ERR(bip)) अणु
		pr_err("Unable to allocate bio_integrity_payload\n");
		वापस PTR_ERR(bip);
	पूर्ण

	bip->bip_iter.bi_size = bio_पूर्णांकegrity_bytes(bi, bio_sectors(bio));
	/* भव start sector must be in पूर्णांकegrity पूर्णांकerval units */
	bip_set_seed(bip, bio->bi_iter.bi_sector >>
				  (bi->पूर्णांकerval_exp - SECTOR_SHIFT));

	pr_debug("IBLOCK BIP Size: %u Sector: %llu\n", bip->bip_iter.bi_size,
		 (अचिन्हित दीर्घ दीर्घ)bip->bip_iter.bi_sector);

	resid = bip->bip_iter.bi_size;
	जबतक (resid > 0 && sg_miter_next(miter)) अणु

		len = min_t(माप_प्रकार, miter->length, resid);
		rc = bio_पूर्णांकegrity_add_page(bio, miter->page, len,
					    offset_in_page(miter->addr));
		अगर (rc != len) अणु
			pr_err("bio_integrity_add_page() failed; %d\n", rc);
			sg_miter_stop(miter);
			वापस -ENOMEM;
		पूर्ण

		pr_debug("Added bio integrity page: %p length: %zu offset: %lu\n",
			  miter->page, len, offset_in_page(miter->addr));

		resid -= len;
		अगर (len < miter->length)
			miter->consumed -= miter->length - len;
	पूर्ण
	sg_miter_stop(miter);

	वापस 0;
पूर्ण

अटल sense_reason_t
iblock_execute_rw(काष्ठा se_cmd *cmd, काष्ठा scatterlist *sgl, u32 sgl_nents,
		  क्रमागत dma_data_direction data_direction)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	sector_t block_lba = target_to_linux_sector(dev, cmd->t_task_lba);
	काष्ठा iblock_req *ibr;
	काष्ठा bio *bio;
	काष्ठा bio_list list;
	काष्ठा scatterlist *sg;
	u32 sg_num = sgl_nents;
	अचिन्हित पूर्णांक opf;
	अचिन्हित bio_cnt;
	पूर्णांक i, rc;
	काष्ठा sg_mapping_iter prot_miter;
	अचिन्हित पूर्णांक miter_dir;

	अगर (data_direction == DMA_TO_DEVICE) अणु
		काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);
		काष्ठा request_queue *q = bdev_get_queue(ib_dev->ibd_bd);
		/*
		 * Force ग_लिखोthrough using REQ_FUA अगर a अस्थिर ग_लिखो cache
		 * is not enabled, or अगर initiator set the Force Unit Access bit.
		 */
		opf = REQ_OP_WRITE;
		miter_dir = SG_MITER_TO_SG;
		अगर (test_bit(QUEUE_FLAG_FUA, &q->queue_flags)) अणु
			अगर (cmd->se_cmd_flags & SCF_FUA)
				opf |= REQ_FUA;
			अन्यथा अगर (!test_bit(QUEUE_FLAG_WC, &q->queue_flags))
				opf |= REQ_FUA;
		पूर्ण
	पूर्ण अन्यथा अणु
		opf = REQ_OP_READ;
		miter_dir = SG_MITER_FROM_SG;
	पूर्ण

	ibr = kzalloc(माप(काष्ठा iblock_req), GFP_KERNEL);
	अगर (!ibr)
		जाओ fail;
	cmd->priv = ibr;

	अगर (!sgl_nents) अणु
		refcount_set(&ibr->pending, 1);
		iblock_complete_cmd(cmd);
		वापस 0;
	पूर्ण

	bio = iblock_get_bio(cmd, block_lba, sgl_nents, opf);
	अगर (!bio)
		जाओ fail_मुक्त_ibr;

	bio_list_init(&list);
	bio_list_add(&list, bio);

	refcount_set(&ibr->pending, 2);
	bio_cnt = 1;

	अगर (cmd->prot_type && dev->dev_attrib.pi_prot_type)
		sg_miter_start(&prot_miter, cmd->t_prot_sg, cmd->t_prot_nents,
			       miter_dir);

	क्रम_each_sg(sgl, sg, sgl_nents, i) अणु
		/*
		 * XXX: अगर the length the device accepts is लघुer than the
		 *	length of the S/G list entry this will cause and
		 *	endless loop.  Better hope no driver uses huge pages.
		 */
		जबतक (bio_add_page(bio, sg_page(sg), sg->length, sg->offset)
				!= sg->length) अणु
			अगर (cmd->prot_type && dev->dev_attrib.pi_prot_type) अणु
				rc = iblock_alloc_bip(cmd, bio, &prot_miter);
				अगर (rc)
					जाओ fail_put_bios;
			पूर्ण

			अगर (bio_cnt >= IBLOCK_MAX_BIO_PER_TASK) अणु
				iblock_submit_bios(&list);
				bio_cnt = 0;
			पूर्ण

			bio = iblock_get_bio(cmd, block_lba, sg_num, opf);
			अगर (!bio)
				जाओ fail_put_bios;

			refcount_inc(&ibr->pending);
			bio_list_add(&list, bio);
			bio_cnt++;
		पूर्ण

		/* Always in 512 byte units क्रम Linux/Block */
		block_lba += sg->length >> SECTOR_SHIFT;
		sg_num--;
	पूर्ण

	अगर (cmd->prot_type && dev->dev_attrib.pi_prot_type) अणु
		rc = iblock_alloc_bip(cmd, bio, &prot_miter);
		अगर (rc)
			जाओ fail_put_bios;
	पूर्ण

	iblock_submit_bios(&list);
	iblock_complete_cmd(cmd);
	वापस 0;

fail_put_bios:
	जबतक ((bio = bio_list_pop(&list)))
		bio_put(bio);
fail_मुक्त_ibr:
	kमुक्त(ibr);
fail:
	वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
पूर्ण

अटल sector_t iblock_get_blocks(काष्ठा se_device *dev)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);
	काष्ठा block_device *bd = ib_dev->ibd_bd;
	काष्ठा request_queue *q = bdev_get_queue(bd);

	वापस iblock_emulate_पढ़ो_cap_with_block_size(dev, bd, q);
पूर्ण

अटल sector_t iblock_get_alignment_offset_lbas(काष्ठा se_device *dev)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);
	काष्ठा block_device *bd = ib_dev->ibd_bd;
	पूर्णांक ret;

	ret = bdev_alignment_offset(bd);
	अगर (ret == -1)
		वापस 0;

	/* convert offset-bytes to offset-lbas */
	वापस ret / bdev_logical_block_size(bd);
पूर्ण

अटल अचिन्हित पूर्णांक iblock_get_lbppbe(काष्ठा se_device *dev)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);
	काष्ठा block_device *bd = ib_dev->ibd_bd;
	अचिन्हित पूर्णांक logs_per_phys =
		bdev_physical_block_size(bd) / bdev_logical_block_size(bd);

	वापस ilog2(logs_per_phys);
पूर्ण

अटल अचिन्हित पूर्णांक iblock_get_io_min(काष्ठा se_device *dev)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);
	काष्ठा block_device *bd = ib_dev->ibd_bd;

	वापस bdev_io_min(bd);
पूर्ण

अटल अचिन्हित पूर्णांक iblock_get_io_opt(काष्ठा se_device *dev)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);
	काष्ठा block_device *bd = ib_dev->ibd_bd;

	वापस bdev_io_opt(bd);
पूर्ण

अटल काष्ठा sbc_ops iblock_sbc_ops = अणु
	.execute_rw		= iblock_execute_rw,
	.execute_sync_cache	= iblock_execute_sync_cache,
	.execute_ग_लिखो_same	= iblock_execute_ग_लिखो_same,
	.execute_unmap		= iblock_execute_unmap,
पूर्ण;

अटल sense_reason_t
iblock_parse_cdb(काष्ठा se_cmd *cmd)
अणु
	वापस sbc_parse_cdb(cmd, &iblock_sbc_ops);
पूर्ण

अटल bool iblock_get_ग_लिखो_cache(काष्ठा se_device *dev)
अणु
	काष्ठा iblock_dev *ib_dev = IBLOCK_DEV(dev);
	काष्ठा block_device *bd = ib_dev->ibd_bd;
	काष्ठा request_queue *q = bdev_get_queue(bd);

	वापस test_bit(QUEUE_FLAG_WC, &q->queue_flags);
पूर्ण

अटल स्थिर काष्ठा target_backend_ops iblock_ops = अणु
	.name			= "iblock",
	.inquiry_prod		= "IBLOCK",
	.inquiry_rev		= IBLOCK_VERSION,
	.owner			= THIS_MODULE,
	.attach_hba		= iblock_attach_hba,
	.detach_hba		= iblock_detach_hba,
	.alloc_device		= iblock_alloc_device,
	.configure_device	= iblock_configure_device,
	.destroy_device		= iblock_destroy_device,
	.मुक्त_device		= iblock_मुक्त_device,
	.plug_device		= iblock_plug_device,
	.unplug_device		= iblock_unplug_device,
	.parse_cdb		= iblock_parse_cdb,
	.set_configfs_dev_params = iblock_set_configfs_dev_params,
	.show_configfs_dev_params = iblock_show_configfs_dev_params,
	.get_device_type	= sbc_get_device_type,
	.get_blocks		= iblock_get_blocks,
	.get_alignment_offset_lbas = iblock_get_alignment_offset_lbas,
	.get_lbppbe		= iblock_get_lbppbe,
	.get_io_min		= iblock_get_io_min,
	.get_io_opt		= iblock_get_io_opt,
	.get_ग_लिखो_cache	= iblock_get_ग_लिखो_cache,
	.tb_dev_attrib_attrs	= sbc_attrib_attrs,
पूर्ण;

अटल पूर्णांक __init iblock_module_init(व्योम)
अणु
	वापस transport_backend_रेजिस्टर(&iblock_ops);
पूर्ण

अटल व्योम __निकास iblock_module_निकास(व्योम)
अणु
	target_backend_unरेजिस्टर(&iblock_ops);
पूर्ण

MODULE_DESCRIPTION("TCM IBLOCK subsystem plugin");
MODULE_AUTHOR("nab@Linux-iSCSI.org");
MODULE_LICENSE("GPL");

module_init(iblock_module_init);
module_निकास(iblock_module_निकास);
