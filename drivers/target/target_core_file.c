<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_file.c
 *
 * This file contains the Storage Engine <-> खाताIO transport specअगरic functions
 *
 * (c) Copyright 2005-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 ******************************************************************************/

#समावेश <linux/माला.स>
#समावेश <linux/parser.h>
#समावेश <linux/समयr.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/uपन.स>
#समावेश <scsi/scsi_proto.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>

#समावेश "target_core_file.h"

अटल अंतरभूत काष्ठा fd_dev *FD_DEV(काष्ठा se_device *dev)
अणु
	वापस container_of(dev, काष्ठा fd_dev, dev);
पूर्ण

अटल पूर्णांक fd_attach_hba(काष्ठा se_hba *hba, u32 host_id)
अणु
	काष्ठा fd_host *fd_host;

	fd_host = kzalloc(माप(काष्ठा fd_host), GFP_KERNEL);
	अगर (!fd_host) अणु
		pr_err("Unable to allocate memory for struct fd_host\n");
		वापस -ENOMEM;
	पूर्ण

	fd_host->fd_host_id = host_id;

	hba->hba_ptr = fd_host;

	pr_debug("CORE_HBA[%d] - TCM FILEIO HBA Driver %s on Generic"
		" Target Core Stack %s\n", hba->hba_id, FD_VERSION,
		TARGET_CORE_VERSION);
	pr_debug("CORE_HBA[%d] - Attached FILEIO HBA: %u to Generic\n",
		hba->hba_id, fd_host->fd_host_id);

	वापस 0;
पूर्ण

अटल व्योम fd_detach_hba(काष्ठा se_hba *hba)
अणु
	काष्ठा fd_host *fd_host = hba->hba_ptr;

	pr_debug("CORE_HBA[%d] - Detached FILEIO HBA: %u from Generic"
		" Target Core\n", hba->hba_id, fd_host->fd_host_id);

	kमुक्त(fd_host);
	hba->hba_ptr = शून्य;
पूर्ण

अटल काष्ठा se_device *fd_alloc_device(काष्ठा se_hba *hba, स्थिर अक्षर *name)
अणु
	काष्ठा fd_dev *fd_dev;
	काष्ठा fd_host *fd_host = hba->hba_ptr;

	fd_dev = kzalloc(माप(काष्ठा fd_dev), GFP_KERNEL);
	अगर (!fd_dev) अणु
		pr_err("Unable to allocate memory for struct fd_dev\n");
		वापस शून्य;
	पूर्ण

	fd_dev->fd_host = fd_host;

	pr_debug("FILEIO: Allocated fd_dev for %p\n", name);

	वापस &fd_dev->dev;
पूर्ण

अटल पूर्णांक fd_configure_device(काष्ठा se_device *dev)
अणु
	काष्ठा fd_dev *fd_dev = FD_DEV(dev);
	काष्ठा fd_host *fd_host = dev->se_hba->hba_ptr;
	काष्ठा file *file;
	काष्ठा inode *inode = शून्य;
	पूर्णांक flags, ret = -EINVAL;

	अगर (!(fd_dev->fbd_flags & FBDF_HAS_PATH)) अणु
		pr_err("Missing fd_dev_name=\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Use O_DSYNC by शेष instead of O_SYNC to क्रमgo syncing
	 * of pure बारtamp updates.
	 */
	flags = O_RDWR | O_CREAT | O_LARGEखाता | O_DSYNC;

	/*
	 * Optionally allow fd_buffered_io=1 to be enabled क्रम people
	 * who want use the fs buffer cache as an WriteCache mechanism.
	 *
	 * This means that in event of a hard failure, there is a risk
	 * of silent data-loss अगर the SCSI client has *not* perक्रमmed a
	 * क्रमced unit access (FUA) ग_लिखो, or issued SYNCHRONIZE_CACHE
	 * to ग_लिखो-out the entire device cache.
	 */
	अगर (fd_dev->fbd_flags & FDBD_HAS_BUFFERED_IO_WCE) अणु
		pr_debug("FILEIO: Disabling O_DSYNC, using buffered FILEIO\n");
		flags &= ~O_DSYNC;
	पूर्ण

	file = filp_खोलो(fd_dev->fd_dev_name, flags, 0600);
	अगर (IS_ERR(file)) अणु
		pr_err("filp_open(%s) failed\n", fd_dev->fd_dev_name);
		ret = PTR_ERR(file);
		जाओ fail;
	पूर्ण
	fd_dev->fd_file = file;
	/*
	 * If using a block backend with this काष्ठा file, we extract
	 * fd_dev->fd_[block,dev]_size from काष्ठा block_device.
	 *
	 * Otherwise, we use the passed fd_size= from configfs
	 */
	inode = file->f_mapping->host;
	अगर (S_ISBLK(inode->i_mode)) अणु
		काष्ठा request_queue *q = bdev_get_queue(I_BDEV(inode));
		अचिन्हित दीर्घ दीर्घ dev_size;

		fd_dev->fd_block_size = bdev_logical_block_size(I_BDEV(inode));
		/*
		 * Determine the number of bytes from i_size_पढ़ो() minus
		 * one (1) logical sector from underlying काष्ठा block_device
		 */
		dev_size = (i_size_पढ़ो(file->f_mapping->host) -
				       fd_dev->fd_block_size);

		pr_debug("FILEIO: Using size: %llu bytes from struct"
			" block_device blocks: %llu logical_block_size: %d\n",
			dev_size, भाग_u64(dev_size, fd_dev->fd_block_size),
			fd_dev->fd_block_size);

		अगर (target_configure_unmap_from_queue(&dev->dev_attrib, q))
			pr_debug("IFILE: BLOCK Discard support available,"
				 " disabled by default\n");
		/*
		 * Enable ग_लिखो same emulation क्रम IBLOCK and use 0xFFFF as
		 * the smaller WRITE_SAME(10) only has a two-byte block count.
		 */
		dev->dev_attrib.max_ग_लिखो_same_len = 0xFFFF;

		अगर (blk_queue_nonrot(q))
			dev->dev_attrib.is_nonrot = 1;
	पूर्ण अन्यथा अणु
		अगर (!(fd_dev->fbd_flags & FBDF_HAS_SIZE)) अणु
			pr_err("FILEIO: Missing fd_dev_size="
				" parameter, and no backing struct"
				" block_device\n");
			जाओ fail;
		पूर्ण

		fd_dev->fd_block_size = FD_BLOCKSIZE;
		/*
		 * Limit UNMAP emulation to 8k Number of LBAs (NoLB)
		 */
		dev->dev_attrib.max_unmap_lba_count = 0x2000;
		/*
		 * Currently hardcoded to 1 in Linux/SCSI code..
		 */
		dev->dev_attrib.max_unmap_block_desc_count = 1;
		dev->dev_attrib.unmap_granularity = 1;
		dev->dev_attrib.unmap_granularity_alignment = 0;

		/*
		 * Limit WRITE_SAME w/ UNMAP=0 emulation to 8k Number of LBAs (NoLB)
		 * based upon काष्ठा iovec limit क्रम vfs_ग_लिखोv()
		 */
		dev->dev_attrib.max_ग_लिखो_same_len = 0x1000;
	पूर्ण

	dev->dev_attrib.hw_block_size = fd_dev->fd_block_size;
	dev->dev_attrib.max_bytes_per_io = FD_MAX_BYTES;
	dev->dev_attrib.hw_max_sectors = FD_MAX_BYTES / fd_dev->fd_block_size;
	dev->dev_attrib.hw_queue_depth = FD_MAX_DEVICE_QUEUE_DEPTH;

	अगर (fd_dev->fbd_flags & FDBD_HAS_BUFFERED_IO_WCE) अणु
		pr_debug("FILEIO: Forcing setting of emulate_write_cache=1"
			" with FDBD_HAS_BUFFERED_IO_WCE\n");
		dev->dev_attrib.emulate_ग_लिखो_cache = 1;
	पूर्ण

	fd_dev->fd_dev_id = fd_host->fd_host_dev_id_count++;
	fd_dev->fd_queue_depth = dev->queue_depth;

	pr_debug("CORE_FILE[%u] - Added TCM FILEIO Device ID: %u at %s,"
		" %llu total bytes\n", fd_host->fd_host_id, fd_dev->fd_dev_id,
			fd_dev->fd_dev_name, fd_dev->fd_dev_size);

	वापस 0;
fail:
	अगर (fd_dev->fd_file) अणु
		filp_बंद(fd_dev->fd_file, शून्य);
		fd_dev->fd_file = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम fd_dev_call_rcu(काष्ठा rcu_head *p)
अणु
	काष्ठा se_device *dev = container_of(p, काष्ठा se_device, rcu_head);
	काष्ठा fd_dev *fd_dev = FD_DEV(dev);

	kमुक्त(fd_dev);
पूर्ण

अटल व्योम fd_मुक्त_device(काष्ठा se_device *dev)
अणु
	call_rcu(&dev->rcu_head, fd_dev_call_rcu);
पूर्ण

अटल व्योम fd_destroy_device(काष्ठा se_device *dev)
अणु
	काष्ठा fd_dev *fd_dev = FD_DEV(dev);

	अगर (fd_dev->fd_file) अणु
		filp_बंद(fd_dev->fd_file, शून्य);
		fd_dev->fd_file = शून्य;
	पूर्ण
पूर्ण

काष्ठा target_core_file_cmd अणु
	अचिन्हित दीर्घ	len;
	काष्ठा se_cmd	*cmd;
	काष्ठा kiocb	iocb;
	काष्ठा bio_vec	bvecs[];
पूर्ण;

अटल व्योम cmd_rw_aio_complete(काष्ठा kiocb *iocb, दीर्घ ret, दीर्घ ret2)
अणु
	काष्ठा target_core_file_cmd *cmd;

	cmd = container_of(iocb, काष्ठा target_core_file_cmd, iocb);

	अगर (ret != cmd->len)
		target_complete_cmd(cmd->cmd, SAM_STAT_CHECK_CONDITION);
	अन्यथा
		target_complete_cmd(cmd->cmd, SAM_STAT_GOOD);

	kमुक्त(cmd);
पूर्ण

अटल sense_reason_t
fd_execute_rw_aio(काष्ठा se_cmd *cmd, काष्ठा scatterlist *sgl, u32 sgl_nents,
	      क्रमागत dma_data_direction data_direction)
अणु
	पूर्णांक is_ग_लिखो = !(data_direction == DMA_FROM_DEVICE);
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा fd_dev *fd_dev = FD_DEV(dev);
	काष्ठा file *file = fd_dev->fd_file;
	काष्ठा target_core_file_cmd *aio_cmd;
	काष्ठा iov_iter iter;
	काष्ठा scatterlist *sg;
	sमाप_प्रकार len = 0;
	पूर्णांक ret = 0, i;

	aio_cmd = kदो_स्मृति(काष्ठा_size(aio_cmd, bvecs, sgl_nents), GFP_KERNEL);
	अगर (!aio_cmd)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	क्रम_each_sg(sgl, sg, sgl_nents, i) अणु
		aio_cmd->bvecs[i].bv_page = sg_page(sg);
		aio_cmd->bvecs[i].bv_len = sg->length;
		aio_cmd->bvecs[i].bv_offset = sg->offset;

		len += sg->length;
	पूर्ण

	iov_iter_bvec(&iter, is_ग_लिखो, aio_cmd->bvecs, sgl_nents, len);

	aio_cmd->cmd = cmd;
	aio_cmd->len = len;
	aio_cmd->iocb.ki_pos = cmd->t_task_lba * dev->dev_attrib.block_size;
	aio_cmd->iocb.ki_filp = file;
	aio_cmd->iocb.ki_complete = cmd_rw_aio_complete;
	aio_cmd->iocb.ki_flags = IOCB_सूचीECT;

	अगर (is_ग_लिखो && (cmd->se_cmd_flags & SCF_FUA))
		aio_cmd->iocb.ki_flags |= IOCB_DSYNC;

	अगर (is_ग_लिखो)
		ret = call_ग_लिखो_iter(file, &aio_cmd->iocb, &iter);
	अन्यथा
		ret = call_पढ़ो_iter(file, &aio_cmd->iocb, &iter);

	अगर (ret != -EIOCBQUEUED)
		cmd_rw_aio_complete(&aio_cmd->iocb, ret, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक fd_करो_rw(काष्ठा se_cmd *cmd, काष्ठा file *fd,
		    u32 block_size, काष्ठा scatterlist *sgl,
		    u32 sgl_nents, u32 data_length, पूर्णांक is_ग_लिखो)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा iov_iter iter;
	काष्ठा bio_vec *bvec;
	sमाप_प्रकार len = 0;
	loff_t pos = (cmd->t_task_lba * block_size);
	पूर्णांक ret = 0, i;

	bvec = kसुस्मृति(sgl_nents, माप(काष्ठा bio_vec), GFP_KERNEL);
	अगर (!bvec) अणु
		pr_err("Unable to allocate fd_do_readv iov[]\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम_each_sg(sgl, sg, sgl_nents, i) अणु
		bvec[i].bv_page = sg_page(sg);
		bvec[i].bv_len = sg->length;
		bvec[i].bv_offset = sg->offset;

		len += sg->length;
	पूर्ण

	iov_iter_bvec(&iter, READ, bvec, sgl_nents, len);
	अगर (is_ग_लिखो)
		ret = vfs_iter_ग_लिखो(fd, &iter, &pos, 0);
	अन्यथा
		ret = vfs_iter_पढ़ो(fd, &iter, &pos, 0);

	अगर (is_ग_लिखो) अणु
		अगर (ret < 0 || ret != data_length) अणु
			pr_err("%s() write returned %d\n", __func__, ret);
			अगर (ret >= 0)
				ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Return zeros and GOOD status even अगर the READ did not वापस
		 * the expected virt_size क्रम काष्ठा file w/o a backing काष्ठा
		 * block_device.
		 */
		अगर (S_ISBLK(file_inode(fd)->i_mode)) अणु
			अगर (ret < 0 || ret != data_length) अणु
				pr_err("%s() returned %d, expecting %u for "
						"S_ISBLK\n", __func__, ret,
						data_length);
				अगर (ret >= 0)
					ret = -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (ret < 0) अणु
				pr_err("%s() returned %d for non S_ISBLK\n",
						__func__, ret);
			पूर्ण अन्यथा अगर (ret != data_length) अणु
				/*
				 * Short पढ़ो हाल:
				 * Probably some one truncate file under us.
				 * We must explicitly zero sg-pages to prevent
				 * expose uninizialized pages to userspace.
				 */
				अगर (ret < data_length)
					ret += iov_iter_zero(data_length - ret, &iter);
				अन्यथा
					ret = -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण
	kमुक्त(bvec);
	वापस ret;
पूर्ण

अटल sense_reason_t
fd_execute_sync_cache(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा fd_dev *fd_dev = FD_DEV(dev);
	पूर्णांक immed = (cmd->t_task_cdb[1] & 0x2);
	loff_t start, end;
	पूर्णांक ret;

	/*
	 * If the Immediate bit is set, queue up the GOOD response
	 * क्रम this SYNCHRONIZE_CACHE op
	 */
	अगर (immed)
		target_complete_cmd(cmd, SAM_STAT_GOOD);

	/*
	 * Determine अगर we will be flushing the entire device.
	 */
	अगर (cmd->t_task_lba == 0 && cmd->data_length == 0) अणु
		start = 0;
		end = Lदीर्घ_उच्च;
	पूर्ण अन्यथा अणु
		start = cmd->t_task_lba * dev->dev_attrib.block_size;
		अगर (cmd->data_length)
			end = start + cmd->data_length - 1;
		अन्यथा
			end = Lदीर्घ_उच्च;
	पूर्ण

	ret = vfs_fsync_range(fd_dev->fd_file, start, end, 1);
	अगर (ret != 0)
		pr_err("FILEIO: vfs_fsync_range() failed: %d\n", ret);

	अगर (immed)
		वापस 0;

	अगर (ret)
		target_complete_cmd(cmd, SAM_STAT_CHECK_CONDITION);
	अन्यथा
		target_complete_cmd(cmd, SAM_STAT_GOOD);

	वापस 0;
पूर्ण

अटल sense_reason_t
fd_execute_ग_लिखो_same(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *se_dev = cmd->se_dev;
	काष्ठा fd_dev *fd_dev = FD_DEV(se_dev);
	loff_t pos = cmd->t_task_lba * se_dev->dev_attrib.block_size;
	sector_t nolb = sbc_get_ग_लिखो_same_sectors(cmd);
	काष्ठा iov_iter iter;
	काष्ठा bio_vec *bvec;
	अचिन्हित पूर्णांक len = 0, i;
	sमाप_प्रकार ret;

	अगर (!nolb) अणु
		target_complete_cmd(cmd, SAM_STAT_GOOD);
		वापस 0;
	पूर्ण
	अगर (cmd->prot_op) अणु
		pr_err("WRITE_SAME: Protection information with FILEIO"
		       " backends not supported\n");
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण

	अगर (cmd->t_data_nents > 1 ||
	    cmd->t_data_sg[0].length != cmd->se_dev->dev_attrib.block_size) अणु
		pr_err("WRITE_SAME: Illegal SGL t_data_nents: %u length: %u"
			" block_size: %u\n",
			cmd->t_data_nents,
			cmd->t_data_sg[0].length,
			cmd->se_dev->dev_attrib.block_size);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	bvec = kसुस्मृति(nolb, माप(काष्ठा bio_vec), GFP_KERNEL);
	अगर (!bvec)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	क्रम (i = 0; i < nolb; i++) अणु
		bvec[i].bv_page = sg_page(&cmd->t_data_sg[0]);
		bvec[i].bv_len = cmd->t_data_sg[0].length;
		bvec[i].bv_offset = cmd->t_data_sg[0].offset;

		len += se_dev->dev_attrib.block_size;
	पूर्ण

	iov_iter_bvec(&iter, READ, bvec, nolb, len);
	ret = vfs_iter_ग_लिखो(fd_dev->fd_file, &iter, &pos, 0);

	kमुक्त(bvec);
	अगर (ret < 0 || ret != len) अणु
		pr_err("vfs_iter_write() returned %zd for write same\n", ret);
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण

	target_complete_cmd(cmd, SAM_STAT_GOOD);
	वापस 0;
पूर्ण

अटल पूर्णांक
fd_करो_prot_fill(काष्ठा se_device *se_dev, sector_t lba, sector_t nolb,
		व्योम *buf, माप_प्रकार bufsize)
अणु
	काष्ठा fd_dev *fd_dev = FD_DEV(se_dev);
	काष्ठा file *prot_fd = fd_dev->fd_prot_file;
	sector_t prot_length, prot;
	loff_t pos = lba * se_dev->prot_length;

	अगर (!prot_fd) अणु
		pr_err("Unable to locate fd_dev->fd_prot_file\n");
		वापस -ENODEV;
	पूर्ण

	prot_length = nolb * se_dev->prot_length;

	स_रखो(buf, 0xff, bufsize);
	क्रम (prot = 0; prot < prot_length;) अणु
		sector_t len = min_t(sector_t, bufsize, prot_length - prot);
		sमाप_प्रकार ret = kernel_ग_लिखो(prot_fd, buf, len, &pos);

		अगर (ret != len) अणु
			pr_err("vfs_write to prot file failed: %zd\n", ret);
			वापस ret < 0 ? ret : -ENODEV;
		पूर्ण
		prot += ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fd_करो_prot_unmap(काष्ठा se_cmd *cmd, sector_t lba, sector_t nolb)
अणु
	व्योम *buf;
	पूर्णांक rc;

	buf = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!buf) अणु
		pr_err("Unable to allocate FILEIO prot buf\n");
		वापस -ENOMEM;
	पूर्ण

	rc = fd_करो_prot_fill(cmd->se_dev, lba, nolb, buf, PAGE_SIZE);

	मुक्त_page((अचिन्हित दीर्घ)buf);

	वापस rc;
पूर्ण

अटल sense_reason_t
fd_execute_unmap(काष्ठा se_cmd *cmd, sector_t lba, sector_t nolb)
अणु
	काष्ठा file *file = FD_DEV(cmd->se_dev)->fd_file;
	काष्ठा inode *inode = file->f_mapping->host;
	पूर्णांक ret;

	अगर (!nolb) अणु
		वापस 0;
	पूर्ण

	अगर (cmd->se_dev->dev_attrib.pi_prot_type) अणु
		ret = fd_करो_prot_unmap(cmd, lba, nolb);
		अगर (ret)
			वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण

	अगर (S_ISBLK(inode->i_mode)) अणु
		/* The backend is block device, use discard */
		काष्ठा block_device *bdev = I_BDEV(inode);
		काष्ठा se_device *dev = cmd->se_dev;

		ret = blkdev_issue_discard(bdev,
					   target_to_linux_sector(dev, lba),
					   target_to_linux_sector(dev,  nolb),
					   GFP_KERNEL, 0);
		अगर (ret < 0) अणु
			pr_warn("FILEIO: blkdev_issue_discard() failed: %d\n",
				ret);
			वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* The backend is normal file, use fallocate */
		काष्ठा se_device *se_dev = cmd->se_dev;
		loff_t pos = lba * se_dev->dev_attrib.block_size;
		अचिन्हित पूर्णांक len = nolb * se_dev->dev_attrib.block_size;
		पूर्णांक mode = FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE;

		अगर (!file->f_op->fallocate)
			वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

		ret = file->f_op->fallocate(file, mode, pos, len);
		अगर (ret < 0) अणु
			pr_warn("FILEIO: fallocate() failed: %d\n", ret);
			वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल sense_reason_t
fd_execute_rw_buffered(काष्ठा se_cmd *cmd, काष्ठा scatterlist *sgl, u32 sgl_nents,
	      क्रमागत dma_data_direction data_direction)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा fd_dev *fd_dev = FD_DEV(dev);
	काष्ठा file *file = fd_dev->fd_file;
	काष्ठा file *pfile = fd_dev->fd_prot_file;
	sense_reason_t rc;
	पूर्णांक ret = 0;
	/*
	 * Call vectorized fileio functions to map काष्ठा scatterlist
	 * physical memory addresses to काष्ठा iovec भव memory.
	 */
	अगर (data_direction == DMA_FROM_DEVICE) अणु
		अगर (cmd->prot_type && dev->dev_attrib.pi_prot_type) अणु
			ret = fd_करो_rw(cmd, pfile, dev->prot_length,
				       cmd->t_prot_sg, cmd->t_prot_nents,
				       cmd->prot_length, 0);
			अगर (ret < 0)
				वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		पूर्ण

		ret = fd_करो_rw(cmd, file, dev->dev_attrib.block_size,
			       sgl, sgl_nents, cmd->data_length, 0);

		अगर (ret > 0 && cmd->prot_type && dev->dev_attrib.pi_prot_type &&
		    dev->dev_attrib.pi_prot_verअगरy) अणु
			u32 sectors = cmd->data_length >>
					ilog2(dev->dev_attrib.block_size);

			rc = sbc_dअगर_verअगरy(cmd, cmd->t_task_lba, sectors,
					    0, cmd->t_prot_sg, 0);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cmd->prot_type && dev->dev_attrib.pi_prot_type &&
		    dev->dev_attrib.pi_prot_verअगरy) अणु
			u32 sectors = cmd->data_length >>
					ilog2(dev->dev_attrib.block_size);

			rc = sbc_dअगर_verअगरy(cmd, cmd->t_task_lba, sectors,
					    0, cmd->t_prot_sg, 0);
			अगर (rc)
				वापस rc;
		पूर्ण

		ret = fd_करो_rw(cmd, file, dev->dev_attrib.block_size,
			       sgl, sgl_nents, cmd->data_length, 1);
		/*
		 * Perक्रमm implicit vfs_fsync_range() क्रम fd_करो_ग_लिखोv() ops
		 * क्रम SCSI WRITEs with Forced Unit Access (FUA) set.
		 * Allow this to happen independent of WCE=0 setting.
		 */
		अगर (ret > 0 && (cmd->se_cmd_flags & SCF_FUA)) अणु
			loff_t start = cmd->t_task_lba *
				dev->dev_attrib.block_size;
			loff_t end;

			अगर (cmd->data_length)
				end = start + cmd->data_length - 1;
			अन्यथा
				end = Lदीर्घ_उच्च;

			vfs_fsync_range(fd_dev->fd_file, start, end, 1);
		पूर्ण

		अगर (ret > 0 && cmd->prot_type && dev->dev_attrib.pi_prot_type) अणु
			ret = fd_करो_rw(cmd, pfile, dev->prot_length,
				       cmd->t_prot_sg, cmd->t_prot_nents,
				       cmd->prot_length, 1);
			अगर (ret < 0)
				वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		पूर्ण
	पूर्ण

	अगर (ret < 0)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	target_complete_cmd(cmd, SAM_STAT_GOOD);
	वापस 0;
पूर्ण

अटल sense_reason_t
fd_execute_rw(काष्ठा se_cmd *cmd, काष्ठा scatterlist *sgl, u32 sgl_nents,
	      क्रमागत dma_data_direction data_direction)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा fd_dev *fd_dev = FD_DEV(dev);

	/*
	 * We are currently limited by the number of iovecs (2048) per
	 * single vfs_[ग_लिखोv,पढ़ोv] call.
	 */
	अगर (cmd->data_length > FD_MAX_BYTES) अणु
		pr_err("FILEIO: Not able to process I/O of %u bytes due to"
		       "FD_MAX_BYTES: %u iovec count limitation\n",
			cmd->data_length, FD_MAX_BYTES);
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण

	अगर (fd_dev->fbd_flags & FDBD_HAS_ASYNC_IO)
		वापस fd_execute_rw_aio(cmd, sgl, sgl_nents, data_direction);
	वापस fd_execute_rw_buffered(cmd, sgl, sgl_nents, data_direction);
पूर्ण

क्रमागत अणु
	Opt_fd_dev_name, Opt_fd_dev_size, Opt_fd_buffered_io,
	Opt_fd_async_io, Opt_err
पूर्ण;

अटल match_table_t tokens = अणु
	अणुOpt_fd_dev_name, "fd_dev_name=%s"पूर्ण,
	अणुOpt_fd_dev_size, "fd_dev_size=%s"पूर्ण,
	अणुOpt_fd_buffered_io, "fd_buffered_io=%d"पूर्ण,
	अणुOpt_fd_async_io, "fd_async_io=%d"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल sमाप_प्रकार fd_set_configfs_dev_params(काष्ठा se_device *dev,
		स्थिर अक्षर *page, sमाप_प्रकार count)
अणु
	काष्ठा fd_dev *fd_dev = FD_DEV(dev);
	अक्षर *orig, *ptr, *arg_p, *opts;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक ret = 0, arg, token;

	opts = kstrdup(page, GFP_KERNEL);
	अगर (!opts)
		वापस -ENOMEM;

	orig = opts;

	जबतक ((ptr = strsep(&opts, ",\n")) != शून्य) अणु
		अगर (!*ptr)
			जारी;

		token = match_token(ptr, tokens, args);
		चयन (token) अणु
		हाल Opt_fd_dev_name:
			अगर (match_strlcpy(fd_dev->fd_dev_name, &args[0],
				FD_MAX_DEV_NAME) == 0) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			pr_debug("FILEIO: Referencing Path: %s\n",
					fd_dev->fd_dev_name);
			fd_dev->fbd_flags |= FBDF_HAS_PATH;
			अवरोध;
		हाल Opt_fd_dev_size:
			arg_p = match_strdup(&args[0]);
			अगर (!arg_p) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण
			ret = kम_से_अदीर्घl(arg_p, 0, &fd_dev->fd_dev_size);
			kमुक्त(arg_p);
			अगर (ret < 0) अणु
				pr_err("kstrtoull() failed for"
						" fd_dev_size=\n");
				जाओ out;
			पूर्ण
			pr_debug("FILEIO: Referencing Size: %llu"
					" bytes\n", fd_dev->fd_dev_size);
			fd_dev->fbd_flags |= FBDF_HAS_SIZE;
			अवरोध;
		हाल Opt_fd_buffered_io:
			ret = match_पूर्णांक(args, &arg);
			अगर (ret)
				जाओ out;
			अगर (arg != 1) अणु
				pr_err("bogus fd_buffered_io=%d value\n", arg);
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			pr_debug("FILEIO: Using buffered I/O"
				" operations for struct fd_dev\n");

			fd_dev->fbd_flags |= FDBD_HAS_BUFFERED_IO_WCE;
			अवरोध;
		हाल Opt_fd_async_io:
			ret = match_पूर्णांक(args, &arg);
			अगर (ret)
				जाओ out;
			अगर (arg != 1) अणु
				pr_err("bogus fd_async_io=%d value\n", arg);
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			pr_debug("FILEIO: Using async I/O"
				" operations for struct fd_dev\n");

			fd_dev->fbd_flags |= FDBD_HAS_ASYNC_IO;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

out:
	kमुक्त(orig);
	वापस (!ret) ? count : ret;
पूर्ण

अटल sमाप_प्रकार fd_show_configfs_dev_params(काष्ठा se_device *dev, अक्षर *b)
अणु
	काष्ठा fd_dev *fd_dev = FD_DEV(dev);
	sमाप_प्रकार bl = 0;

	bl = प्र_लिखो(b + bl, "TCM FILEIO ID: %u", fd_dev->fd_dev_id);
	bl += प्र_लिखो(b + bl, "        File: %s  Size: %llu  Mode: %s Async: %d\n",
		fd_dev->fd_dev_name, fd_dev->fd_dev_size,
		(fd_dev->fbd_flags & FDBD_HAS_BUFFERED_IO_WCE) ?
		"Buffered-WCE" : "O_DSYNC",
		!!(fd_dev->fbd_flags & FDBD_HAS_ASYNC_IO));
	वापस bl;
पूर्ण

अटल sector_t fd_get_blocks(काष्ठा se_device *dev)
अणु
	काष्ठा fd_dev *fd_dev = FD_DEV(dev);
	काष्ठा file *f = fd_dev->fd_file;
	काष्ठा inode *i = f->f_mapping->host;
	अचिन्हित दीर्घ दीर्घ dev_size;
	/*
	 * When using a file that references an underlying काष्ठा block_device,
	 * ensure dev_size is always based on the current inode size in order
	 * to handle underlying block_device resize operations.
	 */
	अगर (S_ISBLK(i->i_mode))
		dev_size = i_size_पढ़ो(i);
	अन्यथा
		dev_size = fd_dev->fd_dev_size;

	वापस भाग_u64(dev_size - dev->dev_attrib.block_size,
		       dev->dev_attrib.block_size);
पूर्ण

अटल पूर्णांक fd_init_prot(काष्ठा se_device *dev)
अणु
	काष्ठा fd_dev *fd_dev = FD_DEV(dev);
	काष्ठा file *prot_file, *file = fd_dev->fd_file;
	काष्ठा inode *inode;
	पूर्णांक ret, flags = O_RDWR | O_CREAT | O_LARGEखाता | O_DSYNC;
	अक्षर buf[FD_MAX_DEV_PROT_NAME];

	अगर (!file) अणु
		pr_err("Unable to locate fd_dev->fd_file\n");
		वापस -ENODEV;
	पूर्ण

	inode = file->f_mapping->host;
	अगर (S_ISBLK(inode->i_mode)) अणु
		pr_err("FILEIO Protection emulation only supported on"
		       " !S_ISBLK\n");
		वापस -ENOSYS;
	पूर्ण

	अगर (fd_dev->fbd_flags & FDBD_HAS_BUFFERED_IO_WCE)
		flags &= ~O_DSYNC;

	snम_लिखो(buf, FD_MAX_DEV_PROT_NAME, "%s.protection",
		 fd_dev->fd_dev_name);

	prot_file = filp_खोलो(buf, flags, 0600);
	अगर (IS_ERR(prot_file)) अणु
		pr_err("filp_open(%s) failed\n", buf);
		ret = PTR_ERR(prot_file);
		वापस ret;
	पूर्ण
	fd_dev->fd_prot_file = prot_file;

	वापस 0;
पूर्ण

अटल पूर्णांक fd_क्रमmat_prot(काष्ठा se_device *dev)
अणु
	अचिन्हित अक्षर *buf;
	पूर्णांक unit_size = FDBD_FORMAT_UNIT_SIZE * dev->dev_attrib.block_size;
	पूर्णांक ret;

	अगर (!dev->dev_attrib.pi_prot_type) अणु
		pr_err("Unable to format_prot while pi_prot_type == 0\n");
		वापस -ENODEV;
	पूर्ण

	buf = vzalloc(unit_size);
	अगर (!buf) अणु
		pr_err("Unable to allocate FILEIO prot buf\n");
		वापस -ENOMEM;
	पूर्ण

	pr_debug("Using FILEIO prot_length: %llu\n",
		 (अचिन्हित दीर्घ दीर्घ)(dev->transport->get_blocks(dev) + 1) *
					dev->prot_length);

	ret = fd_करो_prot_fill(dev, 0, dev->transport->get_blocks(dev) + 1,
			      buf, unit_size);
	vमुक्त(buf);
	वापस ret;
पूर्ण

अटल व्योम fd_मुक्त_prot(काष्ठा se_device *dev)
अणु
	काष्ठा fd_dev *fd_dev = FD_DEV(dev);

	अगर (!fd_dev->fd_prot_file)
		वापस;

	filp_बंद(fd_dev->fd_prot_file, शून्य);
	fd_dev->fd_prot_file = शून्य;
पूर्ण

अटल काष्ठा sbc_ops fd_sbc_ops = अणु
	.execute_rw		= fd_execute_rw,
	.execute_sync_cache	= fd_execute_sync_cache,
	.execute_ग_लिखो_same	= fd_execute_ग_लिखो_same,
	.execute_unmap		= fd_execute_unmap,
पूर्ण;

अटल sense_reason_t
fd_parse_cdb(काष्ठा se_cmd *cmd)
अणु
	वापस sbc_parse_cdb(cmd, &fd_sbc_ops);
पूर्ण

अटल स्थिर काष्ठा target_backend_ops fileio_ops = अणु
	.name			= "fileio",
	.inquiry_prod		= "FILEIO",
	.inquiry_rev		= FD_VERSION,
	.owner			= THIS_MODULE,
	.attach_hba		= fd_attach_hba,
	.detach_hba		= fd_detach_hba,
	.alloc_device		= fd_alloc_device,
	.configure_device	= fd_configure_device,
	.destroy_device		= fd_destroy_device,
	.मुक्त_device		= fd_मुक्त_device,
	.parse_cdb		= fd_parse_cdb,
	.set_configfs_dev_params = fd_set_configfs_dev_params,
	.show_configfs_dev_params = fd_show_configfs_dev_params,
	.get_device_type	= sbc_get_device_type,
	.get_blocks		= fd_get_blocks,
	.init_prot		= fd_init_prot,
	.क्रमmat_prot		= fd_क्रमmat_prot,
	.मुक्त_prot		= fd_मुक्त_prot,
	.tb_dev_attrib_attrs	= sbc_attrib_attrs,
पूर्ण;

अटल पूर्णांक __init fileio_module_init(व्योम)
अणु
	वापस transport_backend_रेजिस्टर(&fileio_ops);
पूर्ण

अटल व्योम __निकास fileio_module_निकास(व्योम)
अणु
	target_backend_unरेजिस्टर(&fileio_ops);
पूर्ण

MODULE_DESCRIPTION("TCM FILEIO subsystem plugin");
MODULE_AUTHOR("nab@Linux-iSCSI.org");
MODULE_LICENSE("GPL");

module_init(fileio_module_init);
module_निकास(fileio_module_निकास);
