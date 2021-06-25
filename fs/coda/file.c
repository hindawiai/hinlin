<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * File operations क्रम Coda.
 * Original version: (C) 1996 Peter Braam 
 * Rewritten क्रम Linux 2.1: (C) 1997 Carnegie Mellon University
 *
 * Carnegie Mellon encourages users of this code to contribute improvements
 * to the Coda project. Contact Peter Braam <coda@cs.cmu.edu>.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/cred.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/uपन.स>

#समावेश <linux/coda.h>
#समावेश "coda_psdev.h"
#समावेश "coda_linux.h"
#समावेश "coda_int.h"

काष्ठा coda_vm_ops अणु
	atomic_t refcnt;
	काष्ठा file *coda_file;
	स्थिर काष्ठा vm_operations_काष्ठा *host_vm_ops;
	काष्ठा vm_operations_काष्ठा vm_ops;
पूर्ण;

अटल sमाप_प्रकार
coda_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *coda_file = iocb->ki_filp;
	काष्ठा inode *coda_inode = file_inode(coda_file);
	काष्ठा coda_file_info *cfi = coda_ftoc(coda_file);
	loff_t ki_pos = iocb->ki_pos;
	माप_प्रकार count = iov_iter_count(to);
	sमाप_प्रकार ret;

	ret = venus_access_पूर्णांकent(coda_inode->i_sb, coda_i2f(coda_inode),
				  &cfi->cfi_access_पूर्णांकent,
				  count, ki_pos, CODA_ACCESS_TYPE_READ);
	अगर (ret)
		जाओ finish_पढ़ो;

	ret = vfs_iter_पढ़ो(cfi->cfi_container, to, &iocb->ki_pos, 0);

finish_पढ़ो:
	venus_access_पूर्णांकent(coda_inode->i_sb, coda_i2f(coda_inode),
			    &cfi->cfi_access_पूर्णांकent,
			    count, ki_pos, CODA_ACCESS_TYPE_READ_FINISH);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
coda_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *coda_file = iocb->ki_filp;
	काष्ठा inode *coda_inode = file_inode(coda_file);
	काष्ठा coda_file_info *cfi = coda_ftoc(coda_file);
	काष्ठा file *host_file = cfi->cfi_container;
	loff_t ki_pos = iocb->ki_pos;
	माप_प्रकार count = iov_iter_count(to);
	sमाप_प्रकार ret;

	ret = venus_access_पूर्णांकent(coda_inode->i_sb, coda_i2f(coda_inode),
				  &cfi->cfi_access_पूर्णांकent,
				  count, ki_pos, CODA_ACCESS_TYPE_WRITE);
	अगर (ret)
		जाओ finish_ग_लिखो;

	file_start_ग_लिखो(host_file);
	inode_lock(coda_inode);
	ret = vfs_iter_ग_लिखो(cfi->cfi_container, to, &iocb->ki_pos, 0);
	coda_inode->i_size = file_inode(host_file)->i_size;
	coda_inode->i_blocks = (coda_inode->i_size + 511) >> 9;
	coda_inode->i_mसमय = coda_inode->i_स_समय = current_समय(coda_inode);
	inode_unlock(coda_inode);
	file_end_ग_लिखो(host_file);

finish_ग_लिखो:
	venus_access_पूर्णांकent(coda_inode->i_sb, coda_i2f(coda_inode),
			    &cfi->cfi_access_पूर्णांकent,
			    count, ki_pos, CODA_ACCESS_TYPE_WRITE_FINISH);
	वापस ret;
पूर्ण

अटल व्योम
coda_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा coda_vm_ops *cvm_ops =
		container_of(vma->vm_ops, काष्ठा coda_vm_ops, vm_ops);

	atomic_inc(&cvm_ops->refcnt);

	अगर (cvm_ops->host_vm_ops && cvm_ops->host_vm_ops->खोलो)
		cvm_ops->host_vm_ops->खोलो(vma);
पूर्ण

अटल व्योम
coda_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा coda_vm_ops *cvm_ops =
		container_of(vma->vm_ops, काष्ठा coda_vm_ops, vm_ops);

	अगर (cvm_ops->host_vm_ops && cvm_ops->host_vm_ops->बंद)
		cvm_ops->host_vm_ops->बंद(vma);

	अगर (atomic_dec_and_test(&cvm_ops->refcnt)) अणु
		vma->vm_ops = cvm_ops->host_vm_ops;
		fput(cvm_ops->coda_file);
		kमुक्त(cvm_ops);
	पूर्ण
पूर्ण

अटल पूर्णांक
coda_file_mmap(काष्ठा file *coda_file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा inode *coda_inode = file_inode(coda_file);
	काष्ठा coda_file_info *cfi = coda_ftoc(coda_file);
	काष्ठा file *host_file = cfi->cfi_container;
	काष्ठा inode *host_inode = file_inode(host_file);
	काष्ठा coda_inode_info *cii;
	काष्ठा coda_vm_ops *cvm_ops;
	loff_t ppos;
	माप_प्रकार count;
	पूर्णांक ret;

	अगर (!host_file->f_op->mmap)
		वापस -ENODEV;

	अगर (WARN_ON(coda_file != vma->vm_file))
		वापस -EIO;

	count = vma->vm_end - vma->vm_start;
	ppos = vma->vm_pgoff * PAGE_SIZE;

	ret = venus_access_पूर्णांकent(coda_inode->i_sb, coda_i2f(coda_inode),
				  &cfi->cfi_access_पूर्णांकent,
				  count, ppos, CODA_ACCESS_TYPE_MMAP);
	अगर (ret)
		वापस ret;

	cvm_ops = kदो_स्मृति(माप(काष्ठा coda_vm_ops), GFP_KERNEL);
	अगर (!cvm_ops)
		वापस -ENOMEM;

	cii = ITOC(coda_inode);
	spin_lock(&cii->c_lock);
	coda_file->f_mapping = host_file->f_mapping;
	अगर (coda_inode->i_mapping == &coda_inode->i_data)
		coda_inode->i_mapping = host_inode->i_mapping;

	/* only allow additional mmaps as दीर्घ as userspace isn't changing
	 * the container file on us! */
	अन्यथा अगर (coda_inode->i_mapping != host_inode->i_mapping) अणु
		spin_unlock(&cii->c_lock);
		kमुक्त(cvm_ops);
		वापस -EBUSY;
	पूर्ण

	/* keep track of how often the coda_inode/host_file has been mmapped */
	cii->c_mapcount++;
	cfi->cfi_mapcount++;
	spin_unlock(&cii->c_lock);

	vma->vm_file = get_file(host_file);
	ret = call_mmap(vma->vm_file, vma);

	अगर (ret) अणु
		/* अगर call_mmap fails, our caller will put host_file so we
		 * should drop the reference to the coda_file that we got.
		 */
		fput(coda_file);
		kमुक्त(cvm_ops);
	पूर्ण अन्यथा अणु
		/* here we add redirects क्रम the खोलो/बंद vm_operations */
		cvm_ops->host_vm_ops = vma->vm_ops;
		अगर (vma->vm_ops)
			cvm_ops->vm_ops = *vma->vm_ops;

		cvm_ops->vm_ops.खोलो = coda_vm_खोलो;
		cvm_ops->vm_ops.बंद = coda_vm_बंद;
		cvm_ops->coda_file = coda_file;
		atomic_set(&cvm_ops->refcnt, 1);

		vma->vm_ops = &cvm_ops->vm_ops;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक coda_खोलो(काष्ठा inode *coda_inode, काष्ठा file *coda_file)
अणु
	काष्ठा file *host_file = शून्य;
	पूर्णांक error;
	अचिन्हित लघु flags = coda_file->f_flags & (~O_EXCL);
	अचिन्हित लघु coda_flags = coda_flags_to_cflags(flags);
	काष्ठा coda_file_info *cfi;

	cfi = kदो_स्मृति(माप(काष्ठा coda_file_info), GFP_KERNEL);
	अगर (!cfi)
		वापस -ENOMEM;

	error = venus_खोलो(coda_inode->i_sb, coda_i2f(coda_inode), coda_flags,
			   &host_file);
	अगर (!host_file)
		error = -EIO;

	अगर (error) अणु
		kमुक्त(cfi);
		वापस error;
	पूर्ण

	host_file->f_flags |= coda_file->f_flags & (O_APPEND | O_SYNC);

	cfi->cfi_magic = CODA_MAGIC;
	cfi->cfi_mapcount = 0;
	cfi->cfi_container = host_file;
	/* assume access पूर्णांकents are supported unless we hear otherwise */
	cfi->cfi_access_पूर्णांकent = true;

	BUG_ON(coda_file->निजी_data != शून्य);
	coda_file->निजी_data = cfi;
	वापस 0;
पूर्ण

पूर्णांक coda_release(काष्ठा inode *coda_inode, काष्ठा file *coda_file)
अणु
	अचिन्हित लघु flags = (coda_file->f_flags) & (~O_EXCL);
	अचिन्हित लघु coda_flags = coda_flags_to_cflags(flags);
	काष्ठा coda_file_info *cfi;
	काष्ठा coda_inode_info *cii;
	काष्ठा inode *host_inode;
	पूर्णांक err;

	cfi = coda_ftoc(coda_file);

	err = venus_बंद(coda_inode->i_sb, coda_i2f(coda_inode),
			  coda_flags, coda_file->f_cred->fsuid);

	host_inode = file_inode(cfi->cfi_container);
	cii = ITOC(coda_inode);

	/* did we mmap this file? */
	spin_lock(&cii->c_lock);
	अगर (coda_inode->i_mapping == &host_inode->i_data) अणु
		cii->c_mapcount -= cfi->cfi_mapcount;
		अगर (!cii->c_mapcount)
			coda_inode->i_mapping = &coda_inode->i_data;
	पूर्ण
	spin_unlock(&cii->c_lock);

	fput(cfi->cfi_container);
	kमुक्त(coda_file->निजी_data);
	coda_file->निजी_data = शून्य;

	/* VFS fput ignores the वापस value from file_operations->release, so
	 * there is no use वापसing an error here */
	वापस 0;
पूर्ण

पूर्णांक coda_fsync(काष्ठा file *coda_file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा file *host_file;
	काष्ठा inode *coda_inode = file_inode(coda_file);
	काष्ठा coda_file_info *cfi;
	पूर्णांक err;

	अगर (!(S_ISREG(coda_inode->i_mode) || S_ISसूची(coda_inode->i_mode) ||
	      S_ISLNK(coda_inode->i_mode)))
		वापस -EINVAL;

	err = filemap_ग_लिखो_and_रुको_range(coda_inode->i_mapping, start, end);
	अगर (err)
		वापस err;
	inode_lock(coda_inode);

	cfi = coda_ftoc(coda_file);
	host_file = cfi->cfi_container;

	err = vfs_fsync(host_file, datasync);
	अगर (!err && !datasync)
		err = venus_fsync(coda_inode->i_sb, coda_i2f(coda_inode));
	inode_unlock(coda_inode);

	वापस err;
पूर्ण

स्थिर काष्ठा file_operations coda_file_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= coda_file_पढ़ो_iter,
	.ग_लिखो_iter	= coda_file_ग_लिखो_iter,
	.mmap		= coda_file_mmap,
	.खोलो		= coda_खोलो,
	.release	= coda_release,
	.fsync		= coda_fsync,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
पूर्ण;
