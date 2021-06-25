<शैली गुरु>
/*
 *  linux/drivers/block/loop.c
 *
 *  Written by Theoकरोre Ts'o, 3/29/93
 *
 * Copyright 1993 by Theoकरोre Ts'o.  Redistribution of this file is
 * permitted under the GNU General Public License.
 *
 * DES encryption plus some minor changes by Werner Almesberger, 30-MAY-1993
 * more DES encryption plus IDEA encryption by Nicholas J. Leon, June 20, 1996
 *
 * Modularized and updated क्रम 1.1.16 kernel - Mitch Dsouza 28th May 1994
 * Adapted क्रम 1.3.59 kernel - Andries Brouwer, 1 Feb 1996
 *
 * Fixed करो_loop_request() re-entrancy - Vincent.Renardias@waw.com Mar 20, 1997
 *
 * Added devfs support - Riअक्षरd Gooch <rgooch@atnf.csiro.au> 16-Jan-1998
 *
 * Handle sparse backing files correctly - Kenn Humborg, Jun 28, 1998
 *
 * Loadable modules and other fixes by AK, 1998
 *
 * Make real block number available to करोwnstream transfer functions, enables
 * CBC (and relatives) mode encryption requiring unique IVs per data block.
 * Reed H. Petty, rhp@draper.net
 *
 * Maximum number of loop devices now dynamic via max_loop module parameter.
 * Russell Kroll <rkroll@exploits.org> 19990701
 *
 * Maximum number of loop devices when compiled-in now selectable by passing
 * max_loop=<1-255> to the kernel on boot.
 * Erik I. Bolsथच, <eriki@himolde.no>, Oct 31, 1999
 *
 * Completely reग_लिखो request handling to be make_request_fn style and
 * non blocking, pushing work to a helper thपढ़ो. Lots of fixes from
 * Al Viro too.
 * Jens Axboe <axboe@suse.de>, Nov 2000
 *
 * Support up to 256 loop devices
 * Heinz Mauelshagen <mge@sistina.com>, Feb 2002
 *
 * Support क्रम falling back on the ग_लिखो file operation when the address space
 * operations ग_लिखो_begin is not available on the backing fileप्रणाली.
 * Anton Altaparmakov, 16 Feb 2005
 *
 * Still To Fix:
 * - Advisory locking is ignored here.
 * - Should use an own CAP_* category instead of CAP_SYS_ADMIN
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/major.h>
#समावेश <linux/रुको.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/init.h>
#समावेश <linux/swap.h>
#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/suspend.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/completion.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/splice.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/uपन.स>
#समावेश <linux/ioprपन.स>
#समावेश <linux/blk-cgroup.h>

#समावेश "loop.h"

#समावेश <linux/uaccess.h>

अटल DEFINE_IDR(loop_index_idr);
अटल DEFINE_MUTEX(loop_ctl_mutex);

अटल पूर्णांक max_part;
अटल पूर्णांक part_shअगरt;

अटल पूर्णांक transfer_xor(काष्ठा loop_device *lo, पूर्णांक cmd,
			काष्ठा page *raw_page, अचिन्हित raw_off,
			काष्ठा page *loop_page, अचिन्हित loop_off,
			पूर्णांक size, sector_t real_block)
अणु
	अक्षर *raw_buf = kmap_atomic(raw_page) + raw_off;
	अक्षर *loop_buf = kmap_atomic(loop_page) + loop_off;
	अक्षर *in, *out, *key;
	पूर्णांक i, keysize;

	अगर (cmd == READ) अणु
		in = raw_buf;
		out = loop_buf;
	पूर्ण अन्यथा अणु
		in = loop_buf;
		out = raw_buf;
	पूर्ण

	key = lo->lo_encrypt_key;
	keysize = lo->lo_encrypt_key_size;
	क्रम (i = 0; i < size; i++)
		*out++ = *in++ ^ key[(i & 511) % keysize];

	kunmap_atomic(loop_buf);
	kunmap_atomic(raw_buf);
	cond_resched();
	वापस 0;
पूर्ण

अटल पूर्णांक xor_init(काष्ठा loop_device *lo, स्थिर काष्ठा loop_info64 *info)
अणु
	अगर (unlikely(info->lo_encrypt_key_size <= 0))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा loop_func_table none_funcs = अणु
	.number = LO_CRYPT_NONE,
पूर्ण; 

अटल काष्ठा loop_func_table xor_funcs = अणु
	.number = LO_CRYPT_XOR,
	.transfer = transfer_xor,
	.init = xor_init
पूर्ण; 

/* xfer_funcs[0] is special - its release function is never called */
अटल काष्ठा loop_func_table *xfer_funcs[MAX_LO_CRYPT] = अणु
	&none_funcs,
	&xor_funcs
पूर्ण;

अटल loff_t get_size(loff_t offset, loff_t sizelimit, काष्ठा file *file)
अणु
	loff_t loopsize;

	/* Compute loopsize in bytes */
	loopsize = i_size_पढ़ो(file->f_mapping->host);
	अगर (offset > 0)
		loopsize -= offset;
	/* offset is beyond i_size, weird but possible */
	अगर (loopsize < 0)
		वापस 0;

	अगर (sizelimit > 0 && sizelimit < loopsize)
		loopsize = sizelimit;
	/*
	 * Unक्रमtunately, अगर we want to करो I/O on the device,
	 * the number of 512-byte sectors has to fit पूर्णांकo a sector_t.
	 */
	वापस loopsize >> 9;
पूर्ण

अटल loff_t get_loop_size(काष्ठा loop_device *lo, काष्ठा file *file)
अणु
	वापस get_size(lo->lo_offset, lo->lo_sizelimit, file);
पूर्ण

अटल व्योम __loop_update_dio(काष्ठा loop_device *lo, bool dio)
अणु
	काष्ठा file *file = lo->lo_backing_file;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	अचिन्हित लघु sb_bsize = 0;
	अचिन्हित dio_align = 0;
	bool use_dio;

	अगर (inode->i_sb->s_bdev) अणु
		sb_bsize = bdev_logical_block_size(inode->i_sb->s_bdev);
		dio_align = sb_bsize - 1;
	पूर्ण

	/*
	 * We support direct I/O only अगर lo_offset is aligned with the
	 * logical I/O size of backing device, and the logical block
	 * size of loop is bigger than the backing device's and the loop
	 * needn't transक्रमm transfer.
	 *
	 * TODO: the above condition may be loosed in the future, and
	 * direct I/O may be चयनed runसमय at that समय because most
	 * of requests in sane applications should be PAGE_SIZE aligned
	 */
	अगर (dio) अणु
		अगर (queue_logical_block_size(lo->lo_queue) >= sb_bsize &&
				!(lo->lo_offset & dio_align) &&
				mapping->a_ops->direct_IO &&
				!lo->transfer)
			use_dio = true;
		अन्यथा
			use_dio = false;
	पूर्ण अन्यथा अणु
		use_dio = false;
	पूर्ण

	अगर (lo->use_dio == use_dio)
		वापस;

	/* flush dirty pages beक्रमe changing direct IO */
	vfs_fsync(file, 0);

	/*
	 * The flag of LO_FLAGS_सूचीECT_IO is handled similarly with
	 * LO_FLAGS_READ_ONLY, both are set from kernel, and losetup
	 * will get updated by ioctl(LOOP_GET_STATUS)
	 */
	अगर (lo->lo_state == Lo_bound)
		blk_mq_मुक्तze_queue(lo->lo_queue);
	lo->use_dio = use_dio;
	अगर (use_dio) अणु
		blk_queue_flag_clear(QUEUE_FLAG_NOMERGES, lo->lo_queue);
		lo->lo_flags |= LO_FLAGS_सूचीECT_IO;
	पूर्ण अन्यथा अणु
		blk_queue_flag_set(QUEUE_FLAG_NOMERGES, lo->lo_queue);
		lo->lo_flags &= ~LO_FLAGS_सूचीECT_IO;
	पूर्ण
	अगर (lo->lo_state == Lo_bound)
		blk_mq_unमुक्तze_queue(lo->lo_queue);
पूर्ण

/**
 * loop_validate_block_size() - validates the passed in block size
 * @bsize: size to validate
 */
अटल पूर्णांक
loop_validate_block_size(अचिन्हित लघु bsize)
अणु
	अगर (bsize < 512 || bsize > PAGE_SIZE || !is_घातer_of_2(bsize))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * loop_set_size() - sets device size and notअगरies userspace
 * @lo: काष्ठा loop_device to set the size क्रम
 * @size: new size of the loop device
 *
 * Callers must validate that the size passed पूर्णांकo this function fits पूर्णांकo
 * a sector_t, eg using loop_validate_size()
 */
अटल व्योम loop_set_size(काष्ठा loop_device *lo, loff_t size)
अणु
	अगर (!set_capacity_and_notअगरy(lo->lo_disk, size))
		kobject_uevent(&disk_to_dev(lo->lo_disk)->kobj, KOBJ_CHANGE);
पूर्ण

अटल अंतरभूत पूर्णांक
lo_करो_transfer(काष्ठा loop_device *lo, पूर्णांक cmd,
	       काष्ठा page *rpage, अचिन्हित roffs,
	       काष्ठा page *lpage, अचिन्हित loffs,
	       पूर्णांक size, sector_t rblock)
अणु
	पूर्णांक ret;

	ret = lo->transfer(lo, cmd, rpage, roffs, lpage, loffs, size, rblock);
	अगर (likely(!ret))
		वापस 0;

	prपूर्णांकk_ratelimited(KERN_ERR
		"loop: Transfer error at byte offset %llu, length %i.\n",
		(अचिन्हित दीर्घ दीर्घ)rblock << 9, size);
	वापस ret;
पूर्ण

अटल पूर्णांक lo_ग_लिखो_bvec(काष्ठा file *file, काष्ठा bio_vec *bvec, loff_t *ppos)
अणु
	काष्ठा iov_iter i;
	sमाप_प्रकार bw;

	iov_iter_bvec(&i, WRITE, bvec, 1, bvec->bv_len);

	file_start_ग_लिखो(file);
	bw = vfs_iter_ग_लिखो(file, &i, ppos, 0);
	file_end_ग_लिखो(file);

	अगर (likely(bw ==  bvec->bv_len))
		वापस 0;

	prपूर्णांकk_ratelimited(KERN_ERR
		"loop: Write error at byte offset %llu, length %i.\n",
		(अचिन्हित दीर्घ दीर्घ)*ppos, bvec->bv_len);
	अगर (bw >= 0)
		bw = -EIO;
	वापस bw;
पूर्ण

अटल पूर्णांक lo_ग_लिखो_simple(काष्ठा loop_device *lo, काष्ठा request *rq,
		loff_t pos)
अणु
	काष्ठा bio_vec bvec;
	काष्ठा req_iterator iter;
	पूर्णांक ret = 0;

	rq_क्रम_each_segment(bvec, rq, iter) अणु
		ret = lo_ग_लिखो_bvec(lo->lo_backing_file, &bvec, &pos);
		अगर (ret < 0)
			अवरोध;
		cond_resched();
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This is the slow, transक्रमming version that needs to द्विगुन buffer the
 * data as it cannot करो the transक्रमmations in place without having direct
 * access to the destination pages of the backing file.
 */
अटल पूर्णांक lo_ग_लिखो_transfer(काष्ठा loop_device *lo, काष्ठा request *rq,
		loff_t pos)
अणु
	काष्ठा bio_vec bvec, b;
	काष्ठा req_iterator iter;
	काष्ठा page *page;
	पूर्णांक ret = 0;

	page = alloc_page(GFP_NOIO);
	अगर (unlikely(!page))
		वापस -ENOMEM;

	rq_क्रम_each_segment(bvec, rq, iter) अणु
		ret = lo_करो_transfer(lo, WRITE, page, 0, bvec.bv_page,
			bvec.bv_offset, bvec.bv_len, pos >> 9);
		अगर (unlikely(ret))
			अवरोध;

		b.bv_page = page;
		b.bv_offset = 0;
		b.bv_len = bvec.bv_len;
		ret = lo_ग_लिखो_bvec(lo->lo_backing_file, &b, &pos);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	__मुक्त_page(page);
	वापस ret;
पूर्ण

अटल पूर्णांक lo_पढ़ो_simple(काष्ठा loop_device *lo, काष्ठा request *rq,
		loff_t pos)
अणु
	काष्ठा bio_vec bvec;
	काष्ठा req_iterator iter;
	काष्ठा iov_iter i;
	sमाप_प्रकार len;

	rq_क्रम_each_segment(bvec, rq, iter) अणु
		iov_iter_bvec(&i, READ, &bvec, 1, bvec.bv_len);
		len = vfs_iter_पढ़ो(lo->lo_backing_file, &i, &pos, 0);
		अगर (len < 0)
			वापस len;

		flush_dcache_page(bvec.bv_page);

		अगर (len != bvec.bv_len) अणु
			काष्ठा bio *bio;

			__rq_क्रम_each_bio(bio, rq)
				zero_fill_bio(bio);
			अवरोध;
		पूर्ण
		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lo_पढ़ो_transfer(काष्ठा loop_device *lo, काष्ठा request *rq,
		loff_t pos)
अणु
	काष्ठा bio_vec bvec, b;
	काष्ठा req_iterator iter;
	काष्ठा iov_iter i;
	काष्ठा page *page;
	sमाप_प्रकार len;
	पूर्णांक ret = 0;

	page = alloc_page(GFP_NOIO);
	अगर (unlikely(!page))
		वापस -ENOMEM;

	rq_क्रम_each_segment(bvec, rq, iter) अणु
		loff_t offset = pos;

		b.bv_page = page;
		b.bv_offset = 0;
		b.bv_len = bvec.bv_len;

		iov_iter_bvec(&i, READ, &b, 1, b.bv_len);
		len = vfs_iter_पढ़ो(lo->lo_backing_file, &i, &pos, 0);
		अगर (len < 0) अणु
			ret = len;
			जाओ out_मुक्त_page;
		पूर्ण

		ret = lo_करो_transfer(lo, READ, page, 0, bvec.bv_page,
			bvec.bv_offset, len, offset >> 9);
		अगर (ret)
			जाओ out_मुक्त_page;

		flush_dcache_page(bvec.bv_page);

		अगर (len != bvec.bv_len) अणु
			काष्ठा bio *bio;

			__rq_क्रम_each_bio(bio, rq)
				zero_fill_bio(bio);
			अवरोध;
		पूर्ण
	पूर्ण

	ret = 0;
out_मुक्त_page:
	__मुक्त_page(page);
	वापस ret;
पूर्ण

अटल पूर्णांक lo_fallocate(काष्ठा loop_device *lo, काष्ठा request *rq, loff_t pos,
			पूर्णांक mode)
अणु
	/*
	 * We use fallocate to manipulate the space mappings used by the image
	 * a.k.a. discard/zerorange. However we करो not support this अगर
	 * encryption is enabled, because it may give an attacker useful
	 * inक्रमmation.
	 */
	काष्ठा file *file = lo->lo_backing_file;
	काष्ठा request_queue *q = lo->lo_queue;
	पूर्णांक ret;

	mode |= FALLOC_FL_KEEP_SIZE;

	अगर (!blk_queue_discard(q)) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ret = file->f_op->fallocate(file, mode, pos, blk_rq_bytes(rq));
	अगर (unlikely(ret && ret != -EINVAL && ret != -EOPNOTSUPP))
		ret = -EIO;
 out:
	वापस ret;
पूर्ण

अटल पूर्णांक lo_req_flush(काष्ठा loop_device *lo, काष्ठा request *rq)
अणु
	काष्ठा file *file = lo->lo_backing_file;
	पूर्णांक ret = vfs_fsync(file, 0);
	अगर (unlikely(ret && ret != -EINVAL))
		ret = -EIO;

	वापस ret;
पूर्ण

अटल व्योम lo_complete_rq(काष्ठा request *rq)
अणु
	काष्ठा loop_cmd *cmd = blk_mq_rq_to_pdu(rq);
	blk_status_t ret = BLK_STS_OK;

	अगर (!cmd->use_aio || cmd->ret < 0 || cmd->ret == blk_rq_bytes(rq) ||
	    req_op(rq) != REQ_OP_READ) अणु
		अगर (cmd->ret < 0)
			ret = त्रुटि_सं_to_blk_status(cmd->ret);
		जाओ end_io;
	पूर्ण

	/*
	 * Short READ - अगर we got some data, advance our request and
	 * retry it. If we got no data, end the rest with EIO.
	 */
	अगर (cmd->ret) अणु
		blk_update_request(rq, BLK_STS_OK, cmd->ret);
		cmd->ret = 0;
		blk_mq_requeue_request(rq, true);
	पूर्ण अन्यथा अणु
		अगर (cmd->use_aio) अणु
			काष्ठा bio *bio = rq->bio;

			जबतक (bio) अणु
				zero_fill_bio(bio);
				bio = bio->bi_next;
			पूर्ण
		पूर्ण
		ret = BLK_STS_IOERR;
end_io:
		blk_mq_end_request(rq, ret);
	पूर्ण
पूर्ण

अटल व्योम lo_rw_aio_करो_completion(काष्ठा loop_cmd *cmd)
अणु
	काष्ठा request *rq = blk_mq_rq_from_pdu(cmd);

	अगर (!atomic_dec_and_test(&cmd->ref))
		वापस;
	kमुक्त(cmd->bvec);
	cmd->bvec = शून्य;
	अगर (likely(!blk_should_fake_समयout(rq->q)))
		blk_mq_complete_request(rq);
पूर्ण

अटल व्योम lo_rw_aio_complete(काष्ठा kiocb *iocb, दीर्घ ret, दीर्घ ret2)
अणु
	काष्ठा loop_cmd *cmd = container_of(iocb, काष्ठा loop_cmd, iocb);

	अगर (cmd->css)
		css_put(cmd->css);
	cmd->ret = ret;
	lo_rw_aio_करो_completion(cmd);
पूर्ण

अटल पूर्णांक lo_rw_aio(काष्ठा loop_device *lo, काष्ठा loop_cmd *cmd,
		     loff_t pos, bool rw)
अणु
	काष्ठा iov_iter iter;
	काष्ठा req_iterator rq_iter;
	काष्ठा bio_vec *bvec;
	काष्ठा request *rq = blk_mq_rq_from_pdu(cmd);
	काष्ठा bio *bio = rq->bio;
	काष्ठा file *file = lo->lo_backing_file;
	काष्ठा bio_vec पंचांगp;
	अचिन्हित पूर्णांक offset;
	पूर्णांक nr_bvec = 0;
	पूर्णांक ret;

	rq_क्रम_each_bvec(पंचांगp, rq, rq_iter)
		nr_bvec++;

	अगर (rq->bio != rq->biotail) अणु

		bvec = kदो_स्मृति_array(nr_bvec, माप(काष्ठा bio_vec),
				     GFP_NOIO);
		अगर (!bvec)
			वापस -EIO;
		cmd->bvec = bvec;

		/*
		 * The bios of the request may be started from the middle of
		 * the 'bvec' because of bio splitting, so we can't directly
		 * copy bio->bi_iov_vec to new bvec. The rq_क्रम_each_bvec
		 * API will take care of all details क्रम us.
		 */
		rq_क्रम_each_bvec(पंचांगp, rq, rq_iter) अणु
			*bvec = पंचांगp;
			bvec++;
		पूर्ण
		bvec = cmd->bvec;
		offset = 0;
	पूर्ण अन्यथा अणु
		/*
		 * Same here, this bio may be started from the middle of the
		 * 'bvec' because of bio splitting, so offset from the bvec
		 * must be passed to iov iterator
		 */
		offset = bio->bi_iter.bi_bvec_करोne;
		bvec = __bvec_iter_bvec(bio->bi_io_vec, bio->bi_iter);
	पूर्ण
	atomic_set(&cmd->ref, 2);

	iov_iter_bvec(&iter, rw, bvec, nr_bvec, blk_rq_bytes(rq));
	iter.iov_offset = offset;

	cmd->iocb.ki_pos = pos;
	cmd->iocb.ki_filp = file;
	cmd->iocb.ki_complete = lo_rw_aio_complete;
	cmd->iocb.ki_flags = IOCB_सूचीECT;
	cmd->iocb.ki_ioprio = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_NONE, 0);
	अगर (cmd->css)
		kthपढ़ो_associate_blkcg(cmd->css);

	अगर (rw == WRITE)
		ret = call_ग_लिखो_iter(file, &cmd->iocb, &iter);
	अन्यथा
		ret = call_पढ़ो_iter(file, &cmd->iocb, &iter);

	lo_rw_aio_करो_completion(cmd);
	kthपढ़ो_associate_blkcg(शून्य);

	अगर (ret != -EIOCBQUEUED)
		cmd->iocb.ki_complete(&cmd->iocb, ret, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_req_filebacked(काष्ठा loop_device *lo, काष्ठा request *rq)
अणु
	काष्ठा loop_cmd *cmd = blk_mq_rq_to_pdu(rq);
	loff_t pos = ((loff_t) blk_rq_pos(rq) << 9) + lo->lo_offset;

	/*
	 * lo_ग_लिखो_simple and lo_पढ़ो_simple should have been covered
	 * by io submit style function like lo_rw_aio(), one blocker
	 * is that lo_पढ़ो_simple() need to call flush_dcache_page after
	 * the page is written from kernel, and it isn't easy to handle
	 * this in io submit style function which submits all segments
	 * of the req at one समय. And direct पढ़ो IO करोesn't need to
	 * run flush_dcache_page().
	 */
	चयन (req_op(rq)) अणु
	हाल REQ_OP_FLUSH:
		वापस lo_req_flush(lo, rq);
	हाल REQ_OP_WRITE_ZEROES:
		/*
		 * If the caller करोesn't want deallocation, call zeroout to
		 * ग_लिखो zeroes the range.  Otherwise, punch them out.
		 */
		वापस lo_fallocate(lo, rq, pos,
			(rq->cmd_flags & REQ_NOUNMAP) ?
				FALLOC_FL_ZERO_RANGE :
				FALLOC_FL_PUNCH_HOLE);
	हाल REQ_OP_DISCARD:
		वापस lo_fallocate(lo, rq, pos, FALLOC_FL_PUNCH_HOLE);
	हाल REQ_OP_WRITE:
		अगर (lo->transfer)
			वापस lo_ग_लिखो_transfer(lo, rq, pos);
		अन्यथा अगर (cmd->use_aio)
			वापस lo_rw_aio(lo, cmd, pos, WRITE);
		अन्यथा
			वापस lo_ग_लिखो_simple(lo, rq, pos);
	हाल REQ_OP_READ:
		अगर (lo->transfer)
			वापस lo_पढ़ो_transfer(lo, rq, pos);
		अन्यथा अगर (cmd->use_aio)
			वापस lo_rw_aio(lo, cmd, pos, READ);
		अन्यथा
			वापस lo_पढ़ो_simple(lo, rq, pos);
	शेष:
		WARN_ON_ONCE(1);
		वापस -EIO;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम loop_update_dio(काष्ठा loop_device *lo)
अणु
	__loop_update_dio(lo, (lo->lo_backing_file->f_flags & O_सूचीECT) |
				lo->use_dio);
पूर्ण

अटल व्योम loop_reपढ़ो_partitions(काष्ठा loop_device *lo,
				   काष्ठा block_device *bdev)
अणु
	पूर्णांक rc;

	mutex_lock(&bdev->bd_mutex);
	rc = bdev_disk_changed(bdev, false);
	mutex_unlock(&bdev->bd_mutex);
	अगर (rc)
		pr_warn("%s: partition scan of loop%d (%s) failed (rc=%d)\n",
			__func__, lo->lo_number, lo->lo_file_name, rc);
पूर्ण

अटल अंतरभूत पूर्णांक is_loop_device(काष्ठा file *file)
अणु
	काष्ठा inode *i = file->f_mapping->host;

	वापस i && S_ISBLK(i->i_mode) && imajor(i) == LOOP_MAJOR;
पूर्ण

अटल पूर्णांक loop_validate_file(काष्ठा file *file, काष्ठा block_device *bdev)
अणु
	काष्ठा inode	*inode = file->f_mapping->host;
	काष्ठा file	*f = file;

	/* Aव्योम recursion */
	जबतक (is_loop_device(f)) अणु
		काष्ठा loop_device *l;

		अगर (f->f_mapping->host->i_rdev == bdev->bd_dev)
			वापस -EBADF;

		l = I_BDEV(f->f_mapping->host)->bd_disk->निजी_data;
		अगर (l->lo_state != Lo_bound) अणु
			वापस -EINVAL;
		पूर्ण
		f = l->lo_backing_file;
	पूर्ण
	अगर (!S_ISREG(inode->i_mode) && !S_ISBLK(inode->i_mode))
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * loop_change_fd चयनed the backing store of a loopback device to
 * a new file. This is useful क्रम operating प्रणाली installers to मुक्त up
 * the original file and in High Availability environments to चयन to
 * an alternative location क्रम the content in हाल of server meltकरोwn.
 * This can only work अगर the loop device is used पढ़ो-only, and अगर the
 * new backing store is the same size and type as the old backing store.
 */
अटल पूर्णांक loop_change_fd(काष्ठा loop_device *lo, काष्ठा block_device *bdev,
			  अचिन्हित पूर्णांक arg)
अणु
	काष्ठा file	*file = शून्य, *old_file;
	पूर्णांक		error;
	bool		partscan;

	error = mutex_lock_समाप्तable(&lo->lo_mutex);
	अगर (error)
		वापस error;
	error = -ENXIO;
	अगर (lo->lo_state != Lo_bound)
		जाओ out_err;

	/* the loop device has to be पढ़ो-only */
	error = -EINVAL;
	अगर (!(lo->lo_flags & LO_FLAGS_READ_ONLY))
		जाओ out_err;

	error = -EBADF;
	file = fget(arg);
	अगर (!file)
		जाओ out_err;

	error = loop_validate_file(file, bdev);
	अगर (error)
		जाओ out_err;

	old_file = lo->lo_backing_file;

	error = -EINVAL;

	/* size of the new backing store needs to be the same */
	अगर (get_loop_size(lo, file) != get_loop_size(lo, old_file))
		जाओ out_err;

	/* and ... चयन */
	blk_mq_मुक्तze_queue(lo->lo_queue);
	mapping_set_gfp_mask(old_file->f_mapping, lo->old_gfp_mask);
	lo->lo_backing_file = file;
	lo->old_gfp_mask = mapping_gfp_mask(file->f_mapping);
	mapping_set_gfp_mask(file->f_mapping,
			     lo->old_gfp_mask & ~(__GFP_IO|__GFP_FS));
	loop_update_dio(lo);
	blk_mq_unमुक्तze_queue(lo->lo_queue);
	partscan = lo->lo_flags & LO_FLAGS_PARTSCAN;
	mutex_unlock(&lo->lo_mutex);
	/*
	 * We must drop file reference outside of lo_mutex as dropping
	 * the file ref can take bd_mutex which creates circular locking
	 * dependency.
	 */
	fput(old_file);
	अगर (partscan)
		loop_reपढ़ो_partitions(lo, bdev);
	वापस 0;

out_err:
	mutex_unlock(&lo->lo_mutex);
	अगर (file)
		fput(file);
	वापस error;
पूर्ण

/* loop sysfs attributes */

अटल sमाप_प्रकार loop_attr_show(काष्ठा device *dev, अक्षर *page,
			      sमाप_प्रकार (*callback)(काष्ठा loop_device *, अक्षर *))
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	काष्ठा loop_device *lo = disk->निजी_data;

	वापस callback(lo, page);
पूर्ण

#घोषणा LOOP_ATTR_RO(_name)						\
अटल sमाप_प्रकार loop_attr_##_name##_show(काष्ठा loop_device *, अक्षर *);	\
अटल sमाप_प्रकार loop_attr_करो_show_##_name(काष्ठा device *d,		\
				काष्ठा device_attribute *attr, अक्षर *b)	\
अणु									\
	वापस loop_attr_show(d, b, loop_attr_##_name##_show);		\
पूर्ण									\
अटल काष्ठा device_attribute loop_attr_##_name =			\
	__ATTR(_name, 0444, loop_attr_करो_show_##_name, शून्य);

अटल sमाप_प्रकार loop_attr_backing_file_show(काष्ठा loop_device *lo, अक्षर *buf)
अणु
	sमाप_प्रकार ret;
	अक्षर *p = शून्य;

	spin_lock_irq(&lo->lo_lock);
	अगर (lo->lo_backing_file)
		p = file_path(lo->lo_backing_file, buf, PAGE_SIZE - 1);
	spin_unlock_irq(&lo->lo_lock);

	अगर (IS_ERR_OR_शून्य(p))
		ret = PTR_ERR(p);
	अन्यथा अणु
		ret = म_माप(p);
		स_हटाओ(buf, p, ret);
		buf[ret++] = '\n';
		buf[ret] = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार loop_attr_offset_show(काष्ठा loop_device *lo, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n", (अचिन्हित दीर्घ दीर्घ)lo->lo_offset);
पूर्ण

अटल sमाप_प्रकार loop_attr_sizelimit_show(काष्ठा loop_device *lo, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n", (अचिन्हित दीर्घ दीर्घ)lo->lo_sizelimit);
पूर्ण

अटल sमाप_प्रकार loop_attr_स्वतःclear_show(काष्ठा loop_device *lo, अक्षर *buf)
अणु
	पूर्णांक स्वतःclear = (lo->lo_flags & LO_FLAGS_AUTOCLEAR);

	वापस प्र_लिखो(buf, "%s\n", स्वतःclear ? "1" : "0");
पूर्ण

अटल sमाप_प्रकार loop_attr_partscan_show(काष्ठा loop_device *lo, अक्षर *buf)
अणु
	पूर्णांक partscan = (lo->lo_flags & LO_FLAGS_PARTSCAN);

	वापस प्र_लिखो(buf, "%s\n", partscan ? "1" : "0");
पूर्ण

अटल sमाप_प्रकार loop_attr_dio_show(काष्ठा loop_device *lo, अक्षर *buf)
अणु
	पूर्णांक dio = (lo->lo_flags & LO_FLAGS_सूचीECT_IO);

	वापस प्र_लिखो(buf, "%s\n", dio ? "1" : "0");
पूर्ण

LOOP_ATTR_RO(backing_file);
LOOP_ATTR_RO(offset);
LOOP_ATTR_RO(sizelimit);
LOOP_ATTR_RO(स्वतःclear);
LOOP_ATTR_RO(partscan);
LOOP_ATTR_RO(dio);

अटल काष्ठा attribute *loop_attrs[] = अणु
	&loop_attr_backing_file.attr,
	&loop_attr_offset.attr,
	&loop_attr_sizelimit.attr,
	&loop_attr_स्वतःclear.attr,
	&loop_attr_partscan.attr,
	&loop_attr_dio.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group loop_attribute_group = अणु
	.name = "loop",
	.attrs= loop_attrs,
पूर्ण;

अटल व्योम loop_sysfs_init(काष्ठा loop_device *lo)
अणु
	lo->sysfs_inited = !sysfs_create_group(&disk_to_dev(lo->lo_disk)->kobj,
						&loop_attribute_group);
पूर्ण

अटल व्योम loop_sysfs_निकास(काष्ठा loop_device *lo)
अणु
	अगर (lo->sysfs_inited)
		sysfs_हटाओ_group(&disk_to_dev(lo->lo_disk)->kobj,
				   &loop_attribute_group);
पूर्ण

अटल व्योम loop_config_discard(काष्ठा loop_device *lo)
अणु
	काष्ठा file *file = lo->lo_backing_file;
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा request_queue *q = lo->lo_queue;
	u32 granularity, max_discard_sectors;

	/*
	 * If the backing device is a block device, mirror its zeroing
	 * capability. Set the discard sectors to the block device's zeroing
	 * capabilities because loop discards result in blkdev_issue_zeroout(),
	 * not blkdev_issue_discard(). This मुख्यtains consistent behavior with
	 * file-backed loop devices: discarded regions पढ़ो back as zero.
	 */
	अगर (S_ISBLK(inode->i_mode) && !lo->lo_encrypt_key_size) अणु
		काष्ठा request_queue *backingq = bdev_get_queue(I_BDEV(inode));

		max_discard_sectors = backingq->limits.max_ग_लिखो_zeroes_sectors;
		granularity = backingq->limits.discard_granularity ?:
			queue_physical_block_size(backingq);

	/*
	 * We use punch hole to reclaim the मुक्त space used by the
	 * image a.k.a. discard. However we करो not support discard अगर
	 * encryption is enabled, because it may give an attacker
	 * useful inक्रमmation.
	 */
	पूर्ण अन्यथा अगर (!file->f_op->fallocate || lo->lo_encrypt_key_size) अणु
		max_discard_sectors = 0;
		granularity = 0;

	पूर्ण अन्यथा अणु
		max_discard_sectors = अच_पूर्णांक_उच्च >> 9;
		granularity = inode->i_sb->s_blocksize;
	पूर्ण

	अगर (max_discard_sectors) अणु
		q->limits.discard_granularity = granularity;
		blk_queue_max_discard_sectors(q, max_discard_sectors);
		blk_queue_max_ग_लिखो_zeroes_sectors(q, max_discard_sectors);
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, q);
	पूर्ण अन्यथा अणु
		q->limits.discard_granularity = 0;
		blk_queue_max_discard_sectors(q, 0);
		blk_queue_max_ग_लिखो_zeroes_sectors(q, 0);
		blk_queue_flag_clear(QUEUE_FLAG_DISCARD, q);
	पूर्ण
	q->limits.discard_alignment = 0;
पूर्ण

अटल व्योम loop_unprepare_queue(काष्ठा loop_device *lo)
अणु
	kthपढ़ो_flush_worker(&lo->worker);
	kthपढ़ो_stop(lo->worker_task);
पूर्ण

अटल पूर्णांक loop_kthपढ़ो_worker_fn(व्योम *worker_ptr)
अणु
	current->flags |= PF_LOCAL_THROTTLE | PF_MEMALLOC_NOIO;
	वापस kthपढ़ो_worker_fn(worker_ptr);
पूर्ण

अटल पूर्णांक loop_prepare_queue(काष्ठा loop_device *lo)
अणु
	kthपढ़ो_init_worker(&lo->worker);
	lo->worker_task = kthपढ़ो_run(loop_kthपढ़ो_worker_fn,
			&lo->worker, "loop%d", lo->lo_number);
	अगर (IS_ERR(lo->worker_task))
		वापस -ENOMEM;
	set_user_nice(lo->worker_task, MIN_NICE);
	वापस 0;
पूर्ण

अटल व्योम loop_update_rotational(काष्ठा loop_device *lo)
अणु
	काष्ठा file *file = lo->lo_backing_file;
	काष्ठा inode *file_inode = file->f_mapping->host;
	काष्ठा block_device *file_bdev = file_inode->i_sb->s_bdev;
	काष्ठा request_queue *q = lo->lo_queue;
	bool nonrot = true;

	/* not all fileप्रणालीs (e.g. पंचांगpfs) have a sb->s_bdev */
	अगर (file_bdev)
		nonrot = blk_queue_nonrot(bdev_get_queue(file_bdev));

	अगर (nonrot)
		blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
	अन्यथा
		blk_queue_flag_clear(QUEUE_FLAG_NONROT, q);
पूर्ण

अटल पूर्णांक
loop_release_xfer(काष्ठा loop_device *lo)
अणु
	पूर्णांक err = 0;
	काष्ठा loop_func_table *xfer = lo->lo_encryption;

	अगर (xfer) अणु
		अगर (xfer->release)
			err = xfer->release(lo);
		lo->transfer = शून्य;
		lo->lo_encryption = शून्य;
		module_put(xfer->owner);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
loop_init_xfer(काष्ठा loop_device *lo, काष्ठा loop_func_table *xfer,
	       स्थिर काष्ठा loop_info64 *i)
अणु
	पूर्णांक err = 0;

	अगर (xfer) अणु
		काष्ठा module *owner = xfer->owner;

		अगर (!try_module_get(owner))
			वापस -EINVAL;
		अगर (xfer->init)
			err = xfer->init(lo, i);
		अगर (err)
			module_put(owner);
		अन्यथा
			lo->lo_encryption = xfer;
	पूर्ण
	वापस err;
पूर्ण

/**
 * loop_set_status_from_info - configure device from loop_info
 * @lo: काष्ठा loop_device to configure
 * @info: काष्ठा loop_info64 to configure the device with
 *
 * Configures the loop device parameters according to the passed
 * in loop_info64 configuration.
 */
अटल पूर्णांक
loop_set_status_from_info(काष्ठा loop_device *lo,
			  स्थिर काष्ठा loop_info64 *info)
अणु
	पूर्णांक err;
	काष्ठा loop_func_table *xfer;
	kuid_t uid = current_uid();

	अगर ((अचिन्हित पूर्णांक) info->lo_encrypt_key_size > LO_KEY_SIZE)
		वापस -EINVAL;

	err = loop_release_xfer(lo);
	अगर (err)
		वापस err;

	अगर (info->lo_encrypt_type) अणु
		अचिन्हित पूर्णांक type = info->lo_encrypt_type;

		अगर (type >= MAX_LO_CRYPT)
			वापस -EINVAL;
		xfer = xfer_funcs[type];
		अगर (xfer == शून्य)
			वापस -EINVAL;
	पूर्ण अन्यथा
		xfer = शून्य;

	err = loop_init_xfer(lo, xfer, info);
	अगर (err)
		वापस err;

	lo->lo_offset = info->lo_offset;
	lo->lo_sizelimit = info->lo_sizelimit;
	स_नकल(lo->lo_file_name, info->lo_file_name, LO_NAME_SIZE);
	स_नकल(lo->lo_crypt_name, info->lo_crypt_name, LO_NAME_SIZE);
	lo->lo_file_name[LO_NAME_SIZE-1] = 0;
	lo->lo_crypt_name[LO_NAME_SIZE-1] = 0;

	अगर (!xfer)
		xfer = &none_funcs;
	lo->transfer = xfer->transfer;
	lo->ioctl = xfer->ioctl;

	lo->lo_flags = info->lo_flags;

	lo->lo_encrypt_key_size = info->lo_encrypt_key_size;
	lo->lo_init[0] = info->lo_init[0];
	lo->lo_init[1] = info->lo_init[1];
	अगर (info->lo_encrypt_key_size) अणु
		स_नकल(lo->lo_encrypt_key, info->lo_encrypt_key,
		       info->lo_encrypt_key_size);
		lo->lo_key_owner = uid;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक loop_configure(काष्ठा loop_device *lo, भ_शेषe_t mode,
			  काष्ठा block_device *bdev,
			  स्थिर काष्ठा loop_config *config)
अणु
	काष्ठा file	*file;
	काष्ठा inode	*inode;
	काष्ठा address_space *mapping;
	पूर्णांक		error;
	loff_t		size;
	bool		partscan;
	अचिन्हित लघु  bsize;

	/* This is safe, since we have a reference from खोलो(). */
	__module_get(THIS_MODULE);

	error = -EBADF;
	file = fget(config->fd);
	अगर (!file)
		जाओ out;

	/*
	 * If we करोn't hold exclusive handle क्रम the device, upgrade to it
	 * here to aव्योम changing device under exclusive owner.
	 */
	अगर (!(mode & FMODE_EXCL)) अणु
		error = bd_prepare_to_claim(bdev, loop_configure);
		अगर (error)
			जाओ out_putf;
	पूर्ण

	error = mutex_lock_समाप्तable(&lo->lo_mutex);
	अगर (error)
		जाओ out_bdev;

	error = -EBUSY;
	अगर (lo->lo_state != Lo_unbound)
		जाओ out_unlock;

	error = loop_validate_file(file, bdev);
	अगर (error)
		जाओ out_unlock;

	mapping = file->f_mapping;
	inode = mapping->host;

	अगर ((config->info.lo_flags & ~LOOP_CONFIGURE_SETTABLE_FLAGS) != 0) अणु
		error = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (config->block_size) अणु
		error = loop_validate_block_size(config->block_size);
		अगर (error)
			जाओ out_unlock;
	पूर्ण

	error = loop_set_status_from_info(lo, &config->info);
	अगर (error)
		जाओ out_unlock;

	अगर (!(file->f_mode & FMODE_WRITE) || !(mode & FMODE_WRITE) ||
	    !file->f_op->ग_लिखो_iter)
		lo->lo_flags |= LO_FLAGS_READ_ONLY;

	error = loop_prepare_queue(lo);
	अगर (error)
		जाओ out_unlock;

	set_disk_ro(lo->lo_disk, (lo->lo_flags & LO_FLAGS_READ_ONLY) != 0);

	lo->use_dio = lo->lo_flags & LO_FLAGS_सूचीECT_IO;
	lo->lo_device = bdev;
	lo->lo_backing_file = file;
	lo->old_gfp_mask = mapping_gfp_mask(mapping);
	mapping_set_gfp_mask(mapping, lo->old_gfp_mask & ~(__GFP_IO|__GFP_FS));

	अगर (!(lo->lo_flags & LO_FLAGS_READ_ONLY) && file->f_op->fsync)
		blk_queue_ग_लिखो_cache(lo->lo_queue, true, false);

	अगर (config->block_size)
		bsize = config->block_size;
	अन्यथा अगर ((lo->lo_backing_file->f_flags & O_सूचीECT) && inode->i_sb->s_bdev)
		/* In हाल of direct I/O, match underlying block size */
		bsize = bdev_logical_block_size(inode->i_sb->s_bdev);
	अन्यथा
		bsize = 512;

	blk_queue_logical_block_size(lo->lo_queue, bsize);
	blk_queue_physical_block_size(lo->lo_queue, bsize);
	blk_queue_io_min(lo->lo_queue, bsize);

	loop_update_rotational(lo);
	loop_update_dio(lo);
	loop_sysfs_init(lo);

	size = get_loop_size(lo, file);
	loop_set_size(lo, size);

	lo->lo_state = Lo_bound;
	अगर (part_shअगरt)
		lo->lo_flags |= LO_FLAGS_PARTSCAN;
	partscan = lo->lo_flags & LO_FLAGS_PARTSCAN;
	अगर (partscan)
		lo->lo_disk->flags &= ~GENHD_FL_NO_PART_SCAN;

	/* Grab the block_device to prevent its deकाष्ठाion after we
	 * put /dev/loopXX inode. Later in __loop_clr_fd() we bdput(bdev).
	 */
	bdgrab(bdev);
	mutex_unlock(&lo->lo_mutex);
	अगर (partscan)
		loop_reपढ़ो_partitions(lo, bdev);
	अगर (!(mode & FMODE_EXCL))
		bd_पात_claiming(bdev, loop_configure);
	वापस 0;

out_unlock:
	mutex_unlock(&lo->lo_mutex);
out_bdev:
	अगर (!(mode & FMODE_EXCL))
		bd_पात_claiming(bdev, loop_configure);
out_putf:
	fput(file);
out:
	/* This is safe: खोलो() is still holding a reference. */
	module_put(THIS_MODULE);
	वापस error;
पूर्ण

अटल पूर्णांक __loop_clr_fd(काष्ठा loop_device *lo, bool release)
अणु
	काष्ठा file *filp = शून्य;
	gfp_t gfp = lo->old_gfp_mask;
	काष्ठा block_device *bdev = lo->lo_device;
	पूर्णांक err = 0;
	bool partscan = false;
	पूर्णांक lo_number;

	mutex_lock(&lo->lo_mutex);
	अगर (WARN_ON_ONCE(lo->lo_state != Lo_runकरोwn)) अणु
		err = -ENXIO;
		जाओ out_unlock;
	पूर्ण

	filp = lo->lo_backing_file;
	अगर (filp == शून्य) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (test_bit(QUEUE_FLAG_WC, &lo->lo_queue->queue_flags))
		blk_queue_ग_लिखो_cache(lo->lo_queue, false, false);

	/* मुक्तze request queue during the transition */
	blk_mq_मुक्तze_queue(lo->lo_queue);

	spin_lock_irq(&lo->lo_lock);
	lo->lo_backing_file = शून्य;
	spin_unlock_irq(&lo->lo_lock);

	loop_release_xfer(lo);
	lo->transfer = शून्य;
	lo->ioctl = शून्य;
	lo->lo_device = शून्य;
	lo->lo_encryption = शून्य;
	lo->lo_offset = 0;
	lo->lo_sizelimit = 0;
	lo->lo_encrypt_key_size = 0;
	स_रखो(lo->lo_encrypt_key, 0, LO_KEY_SIZE);
	स_रखो(lo->lo_crypt_name, 0, LO_NAME_SIZE);
	स_रखो(lo->lo_file_name, 0, LO_NAME_SIZE);
	blk_queue_logical_block_size(lo->lo_queue, 512);
	blk_queue_physical_block_size(lo->lo_queue, 512);
	blk_queue_io_min(lo->lo_queue, 512);
	अगर (bdev) अणु
		bdput(bdev);
		invalidate_bdev(bdev);
		bdev->bd_inode->i_mapping->wb_err = 0;
	पूर्ण
	set_capacity(lo->lo_disk, 0);
	loop_sysfs_निकास(lo);
	अगर (bdev) अणु
		/* let user-space know about this change */
		kobject_uevent(&disk_to_dev(bdev->bd_disk)->kobj, KOBJ_CHANGE);
	पूर्ण
	mapping_set_gfp_mask(filp->f_mapping, gfp);
	/* This is safe: खोलो() is still holding a reference. */
	module_put(THIS_MODULE);
	blk_mq_unमुक्तze_queue(lo->lo_queue);

	partscan = lo->lo_flags & LO_FLAGS_PARTSCAN && bdev;
	lo_number = lo->lo_number;
	loop_unprepare_queue(lo);
out_unlock:
	mutex_unlock(&lo->lo_mutex);
	अगर (partscan) अणु
		/*
		 * bd_mutex has been held alपढ़ोy in release path, so करोn't
		 * acquire it अगर this function is called in such हाल.
		 *
		 * If the reपढ़ो partition isn't from release path, lo_refcnt
		 * must be at least one and it can only become zero when the
		 * current holder is released.
		 */
		अगर (!release)
			mutex_lock(&bdev->bd_mutex);
		err = bdev_disk_changed(bdev, false);
		अगर (!release)
			mutex_unlock(&bdev->bd_mutex);
		अगर (err)
			pr_warn("%s: partition scan of loop%d failed (rc=%d)\n",
				__func__, lo_number, err);
		/* Device is gone, no poपूर्णांक in वापसing error */
		err = 0;
	पूर्ण

	/*
	 * lo->lo_state is set to Lo_unbound here after above partscan has
	 * finished.
	 *
	 * There cannot be anybody अन्यथा entering __loop_clr_fd() as
	 * lo->lo_backing_file is alपढ़ोy cleared and Lo_runकरोwn state
	 * protects us from all the other places trying to change the 'lo'
	 * device.
	 */
	mutex_lock(&lo->lo_mutex);
	lo->lo_flags = 0;
	अगर (!part_shअगरt)
		lo->lo_disk->flags |= GENHD_FL_NO_PART_SCAN;
	lo->lo_state = Lo_unbound;
	mutex_unlock(&lo->lo_mutex);

	/*
	 * Need not hold lo_mutex to fput backing file. Calling fput holding
	 * lo_mutex triggers a circular lock dependency possibility warning as
	 * fput can take bd_mutex which is usually taken beक्रमe lo_mutex.
	 */
	अगर (filp)
		fput(filp);
	वापस err;
पूर्ण

अटल पूर्णांक loop_clr_fd(काष्ठा loop_device *lo)
अणु
	पूर्णांक err;

	err = mutex_lock_समाप्तable(&lo->lo_mutex);
	अगर (err)
		वापस err;
	अगर (lo->lo_state != Lo_bound) अणु
		mutex_unlock(&lo->lo_mutex);
		वापस -ENXIO;
	पूर्ण
	/*
	 * If we've explicitly asked to tear करोwn the loop device,
	 * and it has an elevated reference count, set it क्रम स्वतः-tearकरोwn when
	 * the last reference goes away. This stops $!~#$@ udev from
	 * preventing tearकरोwn because it decided that it needs to run blkid on
	 * the loopback device whenever they appear. xfstests is notorious क्रम
	 * failing tests because blkid via udev races with a losetup
	 * <dev>/करो something like mkfs/losetup -d <dev> causing the losetup -d
	 * command to fail with EBUSY.
	 */
	अगर (atomic_पढ़ो(&lo->lo_refcnt) > 1) अणु
		lo->lo_flags |= LO_FLAGS_AUTOCLEAR;
		mutex_unlock(&lo->lo_mutex);
		वापस 0;
	पूर्ण
	lo->lo_state = Lo_runकरोwn;
	mutex_unlock(&lo->lo_mutex);

	वापस __loop_clr_fd(lo, false);
पूर्ण

अटल पूर्णांक
loop_set_status(काष्ठा loop_device *lo, स्थिर काष्ठा loop_info64 *info)
अणु
	पूर्णांक err;
	काष्ठा block_device *bdev;
	kuid_t uid = current_uid();
	पूर्णांक prev_lo_flags;
	bool partscan = false;
	bool size_changed = false;

	err = mutex_lock_समाप्तable(&lo->lo_mutex);
	अगर (err)
		वापस err;
	अगर (lo->lo_encrypt_key_size &&
	    !uid_eq(lo->lo_key_owner, uid) &&
	    !capable(CAP_SYS_ADMIN)) अणु
		err = -EPERM;
		जाओ out_unlock;
	पूर्ण
	अगर (lo->lo_state != Lo_bound) अणु
		err = -ENXIO;
		जाओ out_unlock;
	पूर्ण

	अगर (lo->lo_offset != info->lo_offset ||
	    lo->lo_sizelimit != info->lo_sizelimit) अणु
		size_changed = true;
		sync_blockdev(lo->lo_device);
		invalidate_bdev(lo->lo_device);
	पूर्ण

	/* I/O need to be drained during transfer transition */
	blk_mq_मुक्तze_queue(lo->lo_queue);

	अगर (size_changed && lo->lo_device->bd_inode->i_mapping->nrpages) अणु
		/* If any pages were dirtied after invalidate_bdev(), try again */
		err = -EAGAIN;
		pr_warn("%s: loop%d (%s) has still dirty pages (nrpages=%lu)\n",
			__func__, lo->lo_number, lo->lo_file_name,
			lo->lo_device->bd_inode->i_mapping->nrpages);
		जाओ out_unमुक्तze;
	पूर्ण

	prev_lo_flags = lo->lo_flags;

	err = loop_set_status_from_info(lo, info);
	अगर (err)
		जाओ out_unमुक्तze;

	/* Mask out flags that can't be set using LOOP_SET_STATUS. */
	lo->lo_flags &= LOOP_SET_STATUS_SETTABLE_FLAGS;
	/* For those flags, use the previous values instead */
	lo->lo_flags |= prev_lo_flags & ~LOOP_SET_STATUS_SETTABLE_FLAGS;
	/* For flags that can't be cleared, use previous values too */
	lo->lo_flags |= prev_lo_flags & ~LOOP_SET_STATUS_CLEARABLE_FLAGS;

	अगर (size_changed) अणु
		loff_t new_size = get_size(lo->lo_offset, lo->lo_sizelimit,
					   lo->lo_backing_file);
		loop_set_size(lo, new_size);
	पूर्ण

	loop_config_discard(lo);

	/* update dio अगर lo_offset or transfer is changed */
	__loop_update_dio(lo, lo->use_dio);

out_unमुक्तze:
	blk_mq_unमुक्तze_queue(lo->lo_queue);

	अगर (!err && (lo->lo_flags & LO_FLAGS_PARTSCAN) &&
	     !(prev_lo_flags & LO_FLAGS_PARTSCAN)) अणु
		lo->lo_disk->flags &= ~GENHD_FL_NO_PART_SCAN;
		bdev = lo->lo_device;
		partscan = true;
	पूर्ण
out_unlock:
	mutex_unlock(&lo->lo_mutex);
	अगर (partscan)
		loop_reपढ़ो_partitions(lo, bdev);

	वापस err;
पूर्ण

अटल पूर्णांक
loop_get_status(काष्ठा loop_device *lo, काष्ठा loop_info64 *info)
अणु
	काष्ठा path path;
	काष्ठा kstat stat;
	पूर्णांक ret;

	ret = mutex_lock_समाप्तable(&lo->lo_mutex);
	अगर (ret)
		वापस ret;
	अगर (lo->lo_state != Lo_bound) अणु
		mutex_unlock(&lo->lo_mutex);
		वापस -ENXIO;
	पूर्ण

	स_रखो(info, 0, माप(*info));
	info->lo_number = lo->lo_number;
	info->lo_offset = lo->lo_offset;
	info->lo_sizelimit = lo->lo_sizelimit;
	info->lo_flags = lo->lo_flags;
	स_नकल(info->lo_file_name, lo->lo_file_name, LO_NAME_SIZE);
	स_नकल(info->lo_crypt_name, lo->lo_crypt_name, LO_NAME_SIZE);
	info->lo_encrypt_type =
		lo->lo_encryption ? lo->lo_encryption->number : 0;
	अगर (lo->lo_encrypt_key_size && capable(CAP_SYS_ADMIN)) अणु
		info->lo_encrypt_key_size = lo->lo_encrypt_key_size;
		स_नकल(info->lo_encrypt_key, lo->lo_encrypt_key,
		       lo->lo_encrypt_key_size);
	पूर्ण

	/* Drop lo_mutex जबतक we call पूर्णांकo the fileप्रणाली. */
	path = lo->lo_backing_file->f_path;
	path_get(&path);
	mutex_unlock(&lo->lo_mutex);
	ret = vfs_getattr(&path, &stat, STATX_INO, AT_STATX_SYNC_AS_STAT);
	अगर (!ret) अणु
		info->lo_device = huge_encode_dev(stat.dev);
		info->lo_inode = stat.ino;
		info->lo_rdevice = huge_encode_dev(stat.rdev);
	पूर्ण
	path_put(&path);
	वापस ret;
पूर्ण

अटल व्योम
loop_info64_from_old(स्थिर काष्ठा loop_info *info, काष्ठा loop_info64 *info64)
अणु
	स_रखो(info64, 0, माप(*info64));
	info64->lo_number = info->lo_number;
	info64->lo_device = info->lo_device;
	info64->lo_inode = info->lo_inode;
	info64->lo_rdevice = info->lo_rdevice;
	info64->lo_offset = info->lo_offset;
	info64->lo_sizelimit = 0;
	info64->lo_encrypt_type = info->lo_encrypt_type;
	info64->lo_encrypt_key_size = info->lo_encrypt_key_size;
	info64->lo_flags = info->lo_flags;
	info64->lo_init[0] = info->lo_init[0];
	info64->lo_init[1] = info->lo_init[1];
	अगर (info->lo_encrypt_type == LO_CRYPT_CRYPTOAPI)
		स_नकल(info64->lo_crypt_name, info->lo_name, LO_NAME_SIZE);
	अन्यथा
		स_नकल(info64->lo_file_name, info->lo_name, LO_NAME_SIZE);
	स_नकल(info64->lo_encrypt_key, info->lo_encrypt_key, LO_KEY_SIZE);
पूर्ण

अटल पूर्णांक
loop_info64_to_old(स्थिर काष्ठा loop_info64 *info64, काष्ठा loop_info *info)
अणु
	स_रखो(info, 0, माप(*info));
	info->lo_number = info64->lo_number;
	info->lo_device = info64->lo_device;
	info->lo_inode = info64->lo_inode;
	info->lo_rdevice = info64->lo_rdevice;
	info->lo_offset = info64->lo_offset;
	info->lo_encrypt_type = info64->lo_encrypt_type;
	info->lo_encrypt_key_size = info64->lo_encrypt_key_size;
	info->lo_flags = info64->lo_flags;
	info->lo_init[0] = info64->lo_init[0];
	info->lo_init[1] = info64->lo_init[1];
	अगर (info->lo_encrypt_type == LO_CRYPT_CRYPTOAPI)
		स_नकल(info->lo_name, info64->lo_crypt_name, LO_NAME_SIZE);
	अन्यथा
		स_नकल(info->lo_name, info64->lo_file_name, LO_NAME_SIZE);
	स_नकल(info->lo_encrypt_key, info64->lo_encrypt_key, LO_KEY_SIZE);

	/* error in हाल values were truncated */
	अगर (info->lo_device != info64->lo_device ||
	    info->lo_rdevice != info64->lo_rdevice ||
	    info->lo_inode != info64->lo_inode ||
	    info->lo_offset != info64->lo_offset)
		वापस -EOVERFLOW;

	वापस 0;
पूर्ण

अटल पूर्णांक
loop_set_status_old(काष्ठा loop_device *lo, स्थिर काष्ठा loop_info __user *arg)
अणु
	काष्ठा loop_info info;
	काष्ठा loop_info64 info64;

	अगर (copy_from_user(&info, arg, माप (काष्ठा loop_info)))
		वापस -EFAULT;
	loop_info64_from_old(&info, &info64);
	वापस loop_set_status(lo, &info64);
पूर्ण

अटल पूर्णांक
loop_set_status64(काष्ठा loop_device *lo, स्थिर काष्ठा loop_info64 __user *arg)
अणु
	काष्ठा loop_info64 info64;

	अगर (copy_from_user(&info64, arg, माप (काष्ठा loop_info64)))
		वापस -EFAULT;
	वापस loop_set_status(lo, &info64);
पूर्ण

अटल पूर्णांक
loop_get_status_old(काष्ठा loop_device *lo, काष्ठा loop_info __user *arg) अणु
	काष्ठा loop_info info;
	काष्ठा loop_info64 info64;
	पूर्णांक err;

	अगर (!arg)
		वापस -EINVAL;
	err = loop_get_status(lo, &info64);
	अगर (!err)
		err = loop_info64_to_old(&info64, &info);
	अगर (!err && copy_to_user(arg, &info, माप(info)))
		err = -EFAULT;

	वापस err;
पूर्ण

अटल पूर्णांक
loop_get_status64(काष्ठा loop_device *lo, काष्ठा loop_info64 __user *arg) अणु
	काष्ठा loop_info64 info64;
	पूर्णांक err;

	अगर (!arg)
		वापस -EINVAL;
	err = loop_get_status(lo, &info64);
	अगर (!err && copy_to_user(arg, &info64, माप(info64)))
		err = -EFAULT;

	वापस err;
पूर्ण

अटल पूर्णांक loop_set_capacity(काष्ठा loop_device *lo)
अणु
	loff_t size;

	अगर (unlikely(lo->lo_state != Lo_bound))
		वापस -ENXIO;

	size = get_loop_size(lo, lo->lo_backing_file);
	loop_set_size(lo, size);

	वापस 0;
पूर्ण

अटल पूर्णांक loop_set_dio(काष्ठा loop_device *lo, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक error = -ENXIO;
	अगर (lo->lo_state != Lo_bound)
		जाओ out;

	__loop_update_dio(lo, !!arg);
	अगर (lo->use_dio == !!arg)
		वापस 0;
	error = -EINVAL;
 out:
	वापस error;
पूर्ण

अटल पूर्णांक loop_set_block_size(काष्ठा loop_device *lo, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err = 0;

	अगर (lo->lo_state != Lo_bound)
		वापस -ENXIO;

	err = loop_validate_block_size(arg);
	अगर (err)
		वापस err;

	अगर (lo->lo_queue->limits.logical_block_size == arg)
		वापस 0;

	sync_blockdev(lo->lo_device);
	invalidate_bdev(lo->lo_device);

	blk_mq_मुक्तze_queue(lo->lo_queue);

	/* invalidate_bdev should have truncated all the pages */
	अगर (lo->lo_device->bd_inode->i_mapping->nrpages) अणु
		err = -EAGAIN;
		pr_warn("%s: loop%d (%s) has still dirty pages (nrpages=%lu)\n",
			__func__, lo->lo_number, lo->lo_file_name,
			lo->lo_device->bd_inode->i_mapping->nrpages);
		जाओ out_unमुक्तze;
	पूर्ण

	blk_queue_logical_block_size(lo->lo_queue, arg);
	blk_queue_physical_block_size(lo->lo_queue, arg);
	blk_queue_io_min(lo->lo_queue, arg);
	loop_update_dio(lo);
out_unमुक्तze:
	blk_mq_unमुक्तze_queue(lo->lo_queue);

	वापस err;
पूर्ण

अटल पूर्णांक lo_simple_ioctl(काष्ठा loop_device *lo, अचिन्हित पूर्णांक cmd,
			   अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err;

	err = mutex_lock_समाप्तable(&lo->lo_mutex);
	अगर (err)
		वापस err;
	चयन (cmd) अणु
	हाल LOOP_SET_CAPACITY:
		err = loop_set_capacity(lo);
		अवरोध;
	हाल LOOP_SET_सूचीECT_IO:
		err = loop_set_dio(lo, arg);
		अवरोध;
	हाल LOOP_SET_BLOCK_SIZE:
		err = loop_set_block_size(lo, arg);
		अवरोध;
	शेष:
		err = lo->ioctl ? lo->ioctl(lo, cmd, arg) : -EINVAL;
	पूर्ण
	mutex_unlock(&lo->lo_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक lo_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
	अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा loop_device *lo = bdev->bd_disk->निजी_data;
	व्योम __user *argp = (व्योम __user *) arg;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल LOOP_SET_FD: अणु
		/*
		 * Legacy हाल - pass in a zeroed out काष्ठा loop_config with
		 * only the file descriptor set , which corresponds with the
		 * शेष parameters we'd have used otherwise.
		 */
		काष्ठा loop_config config;

		स_रखो(&config, 0, माप(config));
		config.fd = arg;

		वापस loop_configure(lo, mode, bdev, &config);
	पूर्ण
	हाल LOOP_CONFIGURE: अणु
		काष्ठा loop_config config;

		अगर (copy_from_user(&config, argp, माप(config)))
			वापस -EFAULT;

		वापस loop_configure(lo, mode, bdev, &config);
	पूर्ण
	हाल LOOP_CHANGE_FD:
		वापस loop_change_fd(lo, bdev, arg);
	हाल LOOP_CLR_FD:
		वापस loop_clr_fd(lo);
	हाल LOOP_SET_STATUS:
		err = -EPERM;
		अगर ((mode & FMODE_WRITE) || capable(CAP_SYS_ADMIN)) अणु
			err = loop_set_status_old(lo, argp);
		पूर्ण
		अवरोध;
	हाल LOOP_GET_STATUS:
		वापस loop_get_status_old(lo, argp);
	हाल LOOP_SET_STATUS64:
		err = -EPERM;
		अगर ((mode & FMODE_WRITE) || capable(CAP_SYS_ADMIN)) अणु
			err = loop_set_status64(lo, argp);
		पूर्ण
		अवरोध;
	हाल LOOP_GET_STATUS64:
		वापस loop_get_status64(lo, argp);
	हाल LOOP_SET_CAPACITY:
	हाल LOOP_SET_सूचीECT_IO:
	हाल LOOP_SET_BLOCK_SIZE:
		अगर (!(mode & FMODE_WRITE) && !capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		fallthrough;
	शेष:
		err = lo_simple_ioctl(lo, cmd, arg);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_loop_info अणु
	compat_पूर्णांक_t	lo_number;      /* ioctl r/o */
	compat_dev_t	lo_device;      /* ioctl r/o */
	compat_uदीर्घ_t	lo_inode;       /* ioctl r/o */
	compat_dev_t	lo_rdevice;     /* ioctl r/o */
	compat_पूर्णांक_t	lo_offset;
	compat_पूर्णांक_t	lo_encrypt_type;
	compat_पूर्णांक_t	lo_encrypt_key_size;    /* ioctl w/o */
	compat_पूर्णांक_t	lo_flags;       /* ioctl r/o */
	अक्षर		lo_name[LO_NAME_SIZE];
	अचिन्हित अक्षर	lo_encrypt_key[LO_KEY_SIZE]; /* ioctl w/o */
	compat_uदीर्घ_t	lo_init[2];
	अक्षर		reserved[4];
पूर्ण;

/*
 * Transfer 32-bit compatibility काष्ठाure in userspace to 64-bit loop info
 * - noअंतरभूतd to reduce stack space usage in मुख्य part of driver
 */
अटल noअंतरभूत पूर्णांक
loop_info64_from_compat(स्थिर काष्ठा compat_loop_info __user *arg,
			काष्ठा loop_info64 *info64)
अणु
	काष्ठा compat_loop_info info;

	अगर (copy_from_user(&info, arg, माप(info)))
		वापस -EFAULT;

	स_रखो(info64, 0, माप(*info64));
	info64->lo_number = info.lo_number;
	info64->lo_device = info.lo_device;
	info64->lo_inode = info.lo_inode;
	info64->lo_rdevice = info.lo_rdevice;
	info64->lo_offset = info.lo_offset;
	info64->lo_sizelimit = 0;
	info64->lo_encrypt_type = info.lo_encrypt_type;
	info64->lo_encrypt_key_size = info.lo_encrypt_key_size;
	info64->lo_flags = info.lo_flags;
	info64->lo_init[0] = info.lo_init[0];
	info64->lo_init[1] = info.lo_init[1];
	अगर (info.lo_encrypt_type == LO_CRYPT_CRYPTOAPI)
		स_नकल(info64->lo_crypt_name, info.lo_name, LO_NAME_SIZE);
	अन्यथा
		स_नकल(info64->lo_file_name, info.lo_name, LO_NAME_SIZE);
	स_नकल(info64->lo_encrypt_key, info.lo_encrypt_key, LO_KEY_SIZE);
	वापस 0;
पूर्ण

/*
 * Transfer 64-bit loop info to 32-bit compatibility काष्ठाure in userspace
 * - noअंतरभूतd to reduce stack space usage in मुख्य part of driver
 */
अटल noअंतरभूत पूर्णांक
loop_info64_to_compat(स्थिर काष्ठा loop_info64 *info64,
		      काष्ठा compat_loop_info __user *arg)
अणु
	काष्ठा compat_loop_info info;

	स_रखो(&info, 0, माप(info));
	info.lo_number = info64->lo_number;
	info.lo_device = info64->lo_device;
	info.lo_inode = info64->lo_inode;
	info.lo_rdevice = info64->lo_rdevice;
	info.lo_offset = info64->lo_offset;
	info.lo_encrypt_type = info64->lo_encrypt_type;
	info.lo_encrypt_key_size = info64->lo_encrypt_key_size;
	info.lo_flags = info64->lo_flags;
	info.lo_init[0] = info64->lo_init[0];
	info.lo_init[1] = info64->lo_init[1];
	अगर (info.lo_encrypt_type == LO_CRYPT_CRYPTOAPI)
		स_नकल(info.lo_name, info64->lo_crypt_name, LO_NAME_SIZE);
	अन्यथा
		स_नकल(info.lo_name, info64->lo_file_name, LO_NAME_SIZE);
	स_नकल(info.lo_encrypt_key, info64->lo_encrypt_key, LO_KEY_SIZE);

	/* error in हाल values were truncated */
	अगर (info.lo_device != info64->lo_device ||
	    info.lo_rdevice != info64->lo_rdevice ||
	    info.lo_inode != info64->lo_inode ||
	    info.lo_offset != info64->lo_offset ||
	    info.lo_init[0] != info64->lo_init[0] ||
	    info.lo_init[1] != info64->lo_init[1])
		वापस -EOVERFLOW;

	अगर (copy_to_user(arg, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक
loop_set_status_compat(काष्ठा loop_device *lo,
		       स्थिर काष्ठा compat_loop_info __user *arg)
अणु
	काष्ठा loop_info64 info64;
	पूर्णांक ret;

	ret = loop_info64_from_compat(arg, &info64);
	अगर (ret < 0)
		वापस ret;
	वापस loop_set_status(lo, &info64);
पूर्ण

अटल पूर्णांक
loop_get_status_compat(काष्ठा loop_device *lo,
		       काष्ठा compat_loop_info __user *arg)
अणु
	काष्ठा loop_info64 info64;
	पूर्णांक err;

	अगर (!arg)
		वापस -EINVAL;
	err = loop_get_status(lo, &info64);
	अगर (!err)
		err = loop_info64_to_compat(&info64, arg);
	वापस err;
पूर्ण

अटल पूर्णांक lo_compat_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा loop_device *lo = bdev->bd_disk->निजी_data;
	पूर्णांक err;

	चयन(cmd) अणु
	हाल LOOP_SET_STATUS:
		err = loop_set_status_compat(lo,
			     (स्थिर काष्ठा compat_loop_info __user *)arg);
		अवरोध;
	हाल LOOP_GET_STATUS:
		err = loop_get_status_compat(lo,
				     (काष्ठा compat_loop_info __user *)arg);
		अवरोध;
	हाल LOOP_SET_CAPACITY:
	हाल LOOP_CLR_FD:
	हाल LOOP_GET_STATUS64:
	हाल LOOP_SET_STATUS64:
	हाल LOOP_CONFIGURE:
		arg = (अचिन्हित दीर्घ) compat_ptr(arg);
		fallthrough;
	हाल LOOP_SET_FD:
	हाल LOOP_CHANGE_FD:
	हाल LOOP_SET_BLOCK_SIZE:
	हाल LOOP_SET_सूचीECT_IO:
		err = lo_ioctl(bdev, mode, cmd, arg);
		अवरोध;
	शेष:
		err = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक lo_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा loop_device *lo = bdev->bd_disk->निजी_data;
	पूर्णांक err;

	err = mutex_lock_समाप्तable(&lo->lo_mutex);
	अगर (err)
		वापस err;
	अगर (lo->lo_state == Lo_deleting)
		err = -ENXIO;
	अन्यथा
		atomic_inc(&lo->lo_refcnt);
	mutex_unlock(&lo->lo_mutex);
	वापस err;
पूर्ण

अटल व्योम lo_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा loop_device *lo = disk->निजी_data;

	mutex_lock(&lo->lo_mutex);
	अगर (atomic_dec_वापस(&lo->lo_refcnt))
		जाओ out_unlock;

	अगर (lo->lo_flags & LO_FLAGS_AUTOCLEAR) अणु
		अगर (lo->lo_state != Lo_bound)
			जाओ out_unlock;
		lo->lo_state = Lo_runकरोwn;
		mutex_unlock(&lo->lo_mutex);
		/*
		 * In स्वतःclear mode, stop the loop thपढ़ो
		 * and हटाओ configuration after last बंद.
		 */
		__loop_clr_fd(lo, true);
		वापस;
	पूर्ण अन्यथा अगर (lo->lo_state == Lo_bound) अणु
		/*
		 * Otherwise keep thपढ़ो (अगर running) and config,
		 * but flush possible ongoing bios in thपढ़ो.
		 */
		blk_mq_मुक्तze_queue(lo->lo_queue);
		blk_mq_unमुक्तze_queue(lo->lo_queue);
	पूर्ण

out_unlock:
	mutex_unlock(&lo->lo_mutex);
पूर्ण

अटल स्थिर काष्ठा block_device_operations lo_fops = अणु
	.owner =	THIS_MODULE,
	.खोलो =		lo_खोलो,
	.release =	lo_release,
	.ioctl =	lo_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl =	lo_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

/*
 * And now the modules code and kernel पूर्णांकerface.
 */
अटल पूर्णांक max_loop;
module_param(max_loop, पूर्णांक, 0444);
MODULE_PARM_DESC(max_loop, "Maximum number of loop devices");
module_param(max_part, पूर्णांक, 0444);
MODULE_PARM_DESC(max_part, "Maximum number of partitions per loop device");
MODULE_LICENSE("GPL");
MODULE_ALIAS_BLOCKDEV_MAJOR(LOOP_MAJOR);

पूर्णांक loop_रेजिस्टर_transfer(काष्ठा loop_func_table *funcs)
अणु
	अचिन्हित पूर्णांक n = funcs->number;

	अगर (n >= MAX_LO_CRYPT || xfer_funcs[n])
		वापस -EINVAL;
	xfer_funcs[n] = funcs;
	वापस 0;
पूर्ण

अटल पूर्णांक unरेजिस्टर_transfer_cb(पूर्णांक id, व्योम *ptr, व्योम *data)
अणु
	काष्ठा loop_device *lo = ptr;
	काष्ठा loop_func_table *xfer = data;

	mutex_lock(&lo->lo_mutex);
	अगर (lo->lo_encryption == xfer)
		loop_release_xfer(lo);
	mutex_unlock(&lo->lo_mutex);
	वापस 0;
पूर्ण

पूर्णांक loop_unरेजिस्टर_transfer(पूर्णांक number)
अणु
	अचिन्हित पूर्णांक n = number;
	काष्ठा loop_func_table *xfer;

	अगर (n == 0 || n >= MAX_LO_CRYPT || (xfer = xfer_funcs[n]) == शून्य)
		वापस -EINVAL;

	xfer_funcs[n] = शून्य;
	idr_क्रम_each(&loop_index_idr, &unरेजिस्टर_transfer_cb, xfer);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(loop_रेजिस्टर_transfer);
EXPORT_SYMBOL(loop_unरेजिस्टर_transfer);

अटल blk_status_t loop_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
		स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा request *rq = bd->rq;
	काष्ठा loop_cmd *cmd = blk_mq_rq_to_pdu(rq);
	काष्ठा loop_device *lo = rq->q->queuedata;

	blk_mq_start_request(rq);

	अगर (lo->lo_state != Lo_bound)
		वापस BLK_STS_IOERR;

	चयन (req_op(rq)) अणु
	हाल REQ_OP_FLUSH:
	हाल REQ_OP_DISCARD:
	हाल REQ_OP_WRITE_ZEROES:
		cmd->use_aio = false;
		अवरोध;
	शेष:
		cmd->use_aio = lo->use_dio;
		अवरोध;
	पूर्ण

	/* always use the first bio's css */
#अगर_घोषित CONFIG_BLK_CGROUP
	अगर (cmd->use_aio && rq->bio && rq->bio->bi_blkg) अणु
		cmd->css = &bio_blkcg(rq->bio)->css;
		css_get(cmd->css);
	पूर्ण अन्यथा
#पूर्ण_अगर
		cmd->css = शून्य;
	kthपढ़ो_queue_work(&lo->worker, &cmd->work);

	वापस BLK_STS_OK;
पूर्ण

अटल व्योम loop_handle_cmd(काष्ठा loop_cmd *cmd)
अणु
	काष्ठा request *rq = blk_mq_rq_from_pdu(cmd);
	स्थिर bool ग_लिखो = op_is_ग_लिखो(req_op(rq));
	काष्ठा loop_device *lo = rq->q->queuedata;
	पूर्णांक ret = 0;

	अगर (ग_लिखो && (lo->lo_flags & LO_FLAGS_READ_ONLY)) अणु
		ret = -EIO;
		जाओ failed;
	पूर्ण

	ret = करो_req_filebacked(lo, rq);
 failed:
	/* complete non-aio request */
	अगर (!cmd->use_aio || ret) अणु
		अगर (ret == -EOPNOTSUPP)
			cmd->ret = ret;
		अन्यथा
			cmd->ret = ret ? -EIO : 0;
		अगर (likely(!blk_should_fake_समयout(rq->q)))
			blk_mq_complete_request(rq);
	पूर्ण
पूर्ण

अटल व्योम loop_queue_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा loop_cmd *cmd =
		container_of(work, काष्ठा loop_cmd, work);

	loop_handle_cmd(cmd);
पूर्ण

अटल पूर्णांक loop_init_request(काष्ठा blk_mq_tag_set *set, काष्ठा request *rq,
		अचिन्हित पूर्णांक hctx_idx, अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा loop_cmd *cmd = blk_mq_rq_to_pdu(rq);

	kthपढ़ो_init_work(&cmd->work, loop_queue_work);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops loop_mq_ops = अणु
	.queue_rq       = loop_queue_rq,
	.init_request	= loop_init_request,
	.complete	= lo_complete_rq,
पूर्ण;

अटल पूर्णांक loop_add(काष्ठा loop_device **l, पूर्णांक i)
अणु
	काष्ठा loop_device *lo;
	काष्ठा gendisk *disk;
	पूर्णांक err;

	err = -ENOMEM;
	lo = kzalloc(माप(*lo), GFP_KERNEL);
	अगर (!lo)
		जाओ out;

	lo->lo_state = Lo_unbound;

	/* allocate id, अगर @id >= 0, we're requesting that specअगरic id */
	अगर (i >= 0) अणु
		err = idr_alloc(&loop_index_idr, lo, i, i + 1, GFP_KERNEL);
		अगर (err == -ENOSPC)
			err = -EEXIST;
	पूर्ण अन्यथा अणु
		err = idr_alloc(&loop_index_idr, lo, 0, 0, GFP_KERNEL);
	पूर्ण
	अगर (err < 0)
		जाओ out_मुक्त_dev;
	i = err;

	err = -ENOMEM;
	lo->tag_set.ops = &loop_mq_ops;
	lo->tag_set.nr_hw_queues = 1;
	lo->tag_set.queue_depth = 128;
	lo->tag_set.numa_node = NUMA_NO_NODE;
	lo->tag_set.cmd_size = माप(काष्ठा loop_cmd);
	lo->tag_set.flags = BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_STACKING;
	lo->tag_set.driver_data = lo;

	err = blk_mq_alloc_tag_set(&lo->tag_set);
	अगर (err)
		जाओ out_मुक्त_idr;

	lo->lo_queue = blk_mq_init_queue(&lo->tag_set);
	अगर (IS_ERR(lo->lo_queue)) अणु
		err = PTR_ERR(lo->lo_queue);
		जाओ out_cleanup_tags;
	पूर्ण
	lo->lo_queue->queuedata = lo;

	blk_queue_max_hw_sectors(lo->lo_queue, BLK_DEF_MAX_SECTORS);

	/*
	 * By शेष, we करो buffer IO, so it करोesn't make sense to enable
	 * merge because the I/O submitted to backing file is handled page by
	 * page. For directio mode, merge करोes help to dispatch bigger request
	 * to underlayer disk. We will enable merge once directio is enabled.
	 */
	blk_queue_flag_set(QUEUE_FLAG_NOMERGES, lo->lo_queue);

	err = -ENOMEM;
	disk = lo->lo_disk = alloc_disk(1 << part_shअगरt);
	अगर (!disk)
		जाओ out_मुक्त_queue;

	/*
	 * Disable partition scanning by शेष. The in-kernel partition
	 * scanning can be requested inभागidually per-device during its
	 * setup. Userspace can always add and हटाओ partitions from all
	 * devices. The needed partition minors are allocated from the
	 * extended minor space, the मुख्य loop device numbers will जारी
	 * to match the loop minors, regardless of the number of partitions
	 * used.
	 *
	 * If max_part is given, partition scanning is globally enabled क्रम
	 * all loop devices. The minors क्रम the मुख्य loop devices will be
	 * multiples of max_part.
	 *
	 * Note: Global-क्रम-all-devices, set-only-at-init, पढ़ो-only module
	 * parameteters like 'max_loop' and 'max_part' make things needlessly
	 * complicated, are too अटल, inflexible and may surprise
	 * userspace tools. Parameters like this in general should be aव्योमed.
	 */
	अगर (!part_shअगरt)
		disk->flags |= GENHD_FL_NO_PART_SCAN;
	disk->flags |= GENHD_FL_EXT_DEVT;
	atomic_set(&lo->lo_refcnt, 0);
	mutex_init(&lo->lo_mutex);
	lo->lo_number		= i;
	spin_lock_init(&lo->lo_lock);
	disk->major		= LOOP_MAJOR;
	disk->first_minor	= i << part_shअगरt;
	disk->fops		= &lo_fops;
	disk->निजी_data	= lo;
	disk->queue		= lo->lo_queue;
	प्र_लिखो(disk->disk_name, "loop%d", i);
	add_disk(disk);
	*l = lo;
	वापस lo->lo_number;

out_मुक्त_queue:
	blk_cleanup_queue(lo->lo_queue);
out_cleanup_tags:
	blk_mq_मुक्त_tag_set(&lo->tag_set);
out_मुक्त_idr:
	idr_हटाओ(&loop_index_idr, i);
out_मुक्त_dev:
	kमुक्त(lo);
out:
	वापस err;
पूर्ण

अटल व्योम loop_हटाओ(काष्ठा loop_device *lo)
अणु
	del_gendisk(lo->lo_disk);
	blk_cleanup_queue(lo->lo_queue);
	blk_mq_मुक्त_tag_set(&lo->tag_set);
	put_disk(lo->lo_disk);
	mutex_destroy(&lo->lo_mutex);
	kमुक्त(lo);
पूर्ण

अटल पूर्णांक find_मुक्त_cb(पूर्णांक id, व्योम *ptr, व्योम *data)
अणु
	काष्ठा loop_device *lo = ptr;
	काष्ठा loop_device **l = data;

	अगर (lo->lo_state == Lo_unbound) अणु
		*l = lo;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक loop_lookup(काष्ठा loop_device **l, पूर्णांक i)
अणु
	काष्ठा loop_device *lo;
	पूर्णांक ret = -ENODEV;

	अगर (i < 0) अणु
		पूर्णांक err;

		err = idr_क्रम_each(&loop_index_idr, &find_मुक्त_cb, &lo);
		अगर (err == 1) अणु
			*l = lo;
			ret = lo->lo_number;
		पूर्ण
		जाओ out;
	पूर्ण

	/* lookup and वापस a specअगरic i */
	lo = idr_find(&loop_index_idr, i);
	अगर (lo) अणु
		*l = lo;
		ret = lo->lo_number;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम loop_probe(dev_t dev)
अणु
	पूर्णांक idx = MINOR(dev) >> part_shअगरt;
	काष्ठा loop_device *lo;

	अगर (max_loop && idx >= max_loop)
		वापस;

	mutex_lock(&loop_ctl_mutex);
	अगर (loop_lookup(&lo, idx) < 0)
		loop_add(&lo, idx);
	mutex_unlock(&loop_ctl_mutex);
पूर्ण

अटल दीर्घ loop_control_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ parm)
अणु
	काष्ठा loop_device *lo;
	पूर्णांक ret;

	ret = mutex_lock_समाप्तable(&loop_ctl_mutex);
	अगर (ret)
		वापस ret;

	ret = -ENOSYS;
	चयन (cmd) अणु
	हाल LOOP_CTL_ADD:
		ret = loop_lookup(&lo, parm);
		अगर (ret >= 0) अणु
			ret = -EEXIST;
			अवरोध;
		पूर्ण
		ret = loop_add(&lo, parm);
		अवरोध;
	हाल LOOP_CTL_REMOVE:
		ret = loop_lookup(&lo, parm);
		अगर (ret < 0)
			अवरोध;
		ret = mutex_lock_समाप्तable(&lo->lo_mutex);
		अगर (ret)
			अवरोध;
		अगर (lo->lo_state != Lo_unbound) अणु
			ret = -EBUSY;
			mutex_unlock(&lo->lo_mutex);
			अवरोध;
		पूर्ण
		अगर (atomic_पढ़ो(&lo->lo_refcnt) > 0) अणु
			ret = -EBUSY;
			mutex_unlock(&lo->lo_mutex);
			अवरोध;
		पूर्ण
		lo->lo_state = Lo_deleting;
		mutex_unlock(&lo->lo_mutex);
		idr_हटाओ(&loop_index_idr, lo->lo_number);
		loop_हटाओ(lo);
		अवरोध;
	हाल LOOP_CTL_GET_FREE:
		ret = loop_lookup(&lo, -1);
		अगर (ret >= 0)
			अवरोध;
		ret = loop_add(&lo, -1);
	पूर्ण
	mutex_unlock(&loop_ctl_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations loop_ctl_fops = अणु
	.खोलो		= nonseekable_खोलो,
	.unlocked_ioctl	= loop_control_ioctl,
	.compat_ioctl	= loop_control_ioctl,
	.owner		= THIS_MODULE,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice loop_misc = अणु
	.minor		= LOOP_CTRL_MINOR,
	.name		= "loop-control",
	.fops		= &loop_ctl_fops,
पूर्ण;

MODULE_ALIAS_MISCDEV(LOOP_CTRL_MINOR);
MODULE_ALIAS("devname:loop-control");

अटल पूर्णांक __init loop_init(व्योम)
अणु
	पूर्णांक i, nr;
	काष्ठा loop_device *lo;
	पूर्णांक err;

	part_shअगरt = 0;
	अगर (max_part > 0) अणु
		part_shअगरt = fls(max_part);

		/*
		 * Adjust max_part according to part_shअगरt as it is exported
		 * to user space so that user can decide correct minor number
		 * अगर [s]he want to create more devices.
		 *
		 * Note that -1 is required because partition 0 is reserved
		 * क्रम the whole disk.
		 */
		max_part = (1UL << part_shअगरt) - 1;
	पूर्ण

	अगर ((1UL << part_shअगरt) > DISK_MAX_PARTS) अणु
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (max_loop > 1UL << (MINORBITS - part_shअगरt)) अणु
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	/*
	 * If max_loop is specअगरied, create that many devices upfront.
	 * This also becomes a hard limit. If max_loop is not specअगरied,
	 * create CONFIG_BLK_DEV_LOOP_MIN_COUNT loop devices at module
	 * init समय. Loop devices can be requested on-demand with the
	 * /dev/loop-control पूर्णांकerface, or be instantiated by accessing
	 * a 'dead' device node.
	 */
	अगर (max_loop)
		nr = max_loop;
	अन्यथा
		nr = CONFIG_BLK_DEV_LOOP_MIN_COUNT;

	err = misc_रेजिस्टर(&loop_misc);
	अगर (err < 0)
		जाओ err_out;


	अगर (__रेजिस्टर_blkdev(LOOP_MAJOR, "loop", loop_probe)) अणु
		err = -EIO;
		जाओ misc_out;
	पूर्ण

	/* pre-create number of devices given by config or max_loop */
	mutex_lock(&loop_ctl_mutex);
	क्रम (i = 0; i < nr; i++)
		loop_add(&lo, i);
	mutex_unlock(&loop_ctl_mutex);

	prपूर्णांकk(KERN_INFO "loop: module loaded\n");
	वापस 0;

misc_out:
	misc_deरेजिस्टर(&loop_misc);
err_out:
	वापस err;
पूर्ण

अटल पूर्णांक loop_निकास_cb(पूर्णांक id, व्योम *ptr, व्योम *data)
अणु
	काष्ठा loop_device *lo = ptr;

	loop_हटाओ(lo);
	वापस 0;
पूर्ण

अटल व्योम __निकास loop_निकास(व्योम)
अणु
	mutex_lock(&loop_ctl_mutex);

	idr_क्रम_each(&loop_index_idr, &loop_निकास_cb, शून्य);
	idr_destroy(&loop_index_idr);

	unरेजिस्टर_blkdev(LOOP_MAJOR, "loop");

	misc_deरेजिस्टर(&loop_misc);

	mutex_unlock(&loop_ctl_mutex);
पूर्ण

module_init(loop_init);
module_निकास(loop_निकास);

#अगर_अघोषित MODULE
अटल पूर्णांक __init max_loop_setup(अक्षर *str)
अणु
	max_loop = simple_म_से_दीर्घ(str, शून्य, 0);
	वापस 1;
पूर्ण

__setup("max_loop=", max_loop_setup);
#पूर्ण_अगर
