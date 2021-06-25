<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * VirtualBox Guest Shared Folders support: Regular file inode and file ops.
 *
 * Copyright (C) 2006-2018 Oracle Corporation
 */

#समावेश <linux/mm.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sizes.h>
#समावेश "vfsmod.h"

काष्ठा vboxsf_handle अणु
	u64 handle;
	u32 root;
	u32 access_flags;
	काष्ठा kref refcount;
	काष्ठा list_head head;
पूर्ण;

अटल पूर्णांक vboxsf_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vboxsf_inode *sf_i = VBOXSF_I(inode);
	काष्ठा shfl_createparms params = अणुपूर्ण;
	काष्ठा vboxsf_handle *sf_handle;
	u32 access_flags = 0;
	पूर्णांक err;

	sf_handle = kदो_स्मृति(माप(*sf_handle), GFP_KERNEL);
	अगर (!sf_handle)
		वापस -ENOMEM;

	/*
	 * We check the value of params.handle afterwards to find out अगर
	 * the call succeeded or failed, as the API करोes not seem to cleanly
	 * distinguish error and inक्रमmational messages.
	 *
	 * Furthermore, we must set params.handle to SHFL_HANDLE_NIL to
	 * make the shared folders host service use our mode parameter.
	 */
	params.handle = SHFL_HANDLE_NIL;
	अगर (file->f_flags & O_CREAT) अणु
		params.create_flags |= SHFL_CF_ACT_CREATE_IF_NEW;
		/*
		 * We ignore O_EXCL, as the Linux kernel seems to call create
		 * beक्रमehand itself, so O_EXCL should always fail.
		 */
		अगर (file->f_flags & O_TRUNC)
			params.create_flags |= SHFL_CF_ACT_OVERWRITE_IF_EXISTS;
		अन्यथा
			params.create_flags |= SHFL_CF_ACT_OPEN_IF_EXISTS;
	पूर्ण अन्यथा अणु
		params.create_flags |= SHFL_CF_ACT_FAIL_IF_NEW;
		अगर (file->f_flags & O_TRUNC)
			params.create_flags |= SHFL_CF_ACT_OVERWRITE_IF_EXISTS;
	पूर्ण

	चयन (file->f_flags & O_ACCMODE) अणु
	हाल O_RDONLY:
		access_flags |= SHFL_CF_ACCESS_READ;
		अवरोध;

	हाल O_WRONLY:
		access_flags |= SHFL_CF_ACCESS_WRITE;
		अवरोध;

	हाल O_RDWR:
		access_flags |= SHFL_CF_ACCESS_READWRITE;
		अवरोध;

	शेष:
		WARN_ON(1);
	पूर्ण

	अगर (file->f_flags & O_APPEND)
		access_flags |= SHFL_CF_ACCESS_APPEND;

	params.create_flags |= access_flags;
	params.info.attr.mode = inode->i_mode;

	err = vboxsf_create_at_dentry(file_dentry(file), &params);
	अगर (err == 0 && params.handle == SHFL_HANDLE_NIL)
		err = (params.result == SHFL_खाता_EXISTS) ? -EEXIST : -ENOENT;
	अगर (err) अणु
		kमुक्त(sf_handle);
		वापस err;
	पूर्ण

	/* the host may have given us dअगरferent attr then requested */
	sf_i->क्रमce_restat = 1;

	/* init our handle काष्ठा and add it to the inode's handles list */
	sf_handle->handle = params.handle;
	sf_handle->root = VBOXSF_SBI(inode->i_sb)->root;
	sf_handle->access_flags = access_flags;
	kref_init(&sf_handle->refcount);

	mutex_lock(&sf_i->handle_list_mutex);
	list_add(&sf_handle->head, &sf_i->handle_list);
	mutex_unlock(&sf_i->handle_list_mutex);

	file->निजी_data = sf_handle;
	वापस 0;
पूर्ण

अटल व्योम vboxsf_handle_release(काष्ठा kref *refcount)
अणु
	काष्ठा vboxsf_handle *sf_handle =
		container_of(refcount, काष्ठा vboxsf_handle, refcount);

	vboxsf_बंद(sf_handle->root, sf_handle->handle);
	kमुक्त(sf_handle);
पूर्ण

अटल पूर्णांक vboxsf_file_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vboxsf_inode *sf_i = VBOXSF_I(inode);
	काष्ठा vboxsf_handle *sf_handle = file->निजी_data;

	/*
	 * When a file is बंदd on our (the guest) side, we want any subsequent
	 * accesses करोne on the host side to see all changes करोne from our side.
	 */
	filemap_ग_लिखो_and_रुको(inode->i_mapping);

	mutex_lock(&sf_i->handle_list_mutex);
	list_del(&sf_handle->head);
	mutex_unlock(&sf_i->handle_list_mutex);

	kref_put(&sf_handle->refcount, vboxsf_handle_release);
	वापस 0;
पूर्ण

/*
 * Write back dirty pages now, because there may not be any suitable
 * खोलो files later
 */
अटल व्योम vboxsf_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	filemap_ग_लिखो_and_रुको(vma->vm_file->f_mapping);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा vboxsf_file_vm_ops = अणु
	.बंद		= vboxsf_vma_बंद,
	.fault		= filemap_fault,
	.map_pages	= filemap_map_pages,
पूर्ण;

अटल पूर्णांक vboxsf_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक err;

	err = generic_file_mmap(file, vma);
	अगर (!err)
		vma->vm_ops = &vboxsf_file_vm_ops;

	वापस err;
पूर्ण

/*
 * Note that since we are accessing files on the host's fileप्रणाली, files
 * may always be changed underneath us by the host!
 *
 * The vboxsf API between the guest and the host करोes not offer any functions
 * to deal with this. There is no inode-generation to check क्रम changes, no
 * events / callback on changes and no way to lock files.
 *
 * To aव्योम वापसing stale data when a file माला_लो *खोलोed* on our (the guest)
 * side, we करो a "stat" on the host side, then compare the mसमय with the
 * last known mसमय and invalidate the page-cache अगर they dअगरfer.
 * This is करोne from vboxsf_inode_revalidate().
 *
 * When पढ़ोs are करोne through the पढ़ो_iter fop, it is possible to करो
 * further cache revalidation then, there are 3 options to deal with this:
 *
 * 1)  Rely solely on the revalidation करोne at खोलो समय
 * 2)  Do another "stat" and compare mसमय again. Unक्रमtunately the vboxsf
 *     host API करोes not allow stat on handles, so we would need to use
 *     file->f_path.dentry and the stat will then fail अगर the file was unlinked
 *     or नामd (and there is no thing like NFS' silly-नाम). So we get:
 * 2a) "stat" and compare mसमय, on stat failure invalidate the cache
 * 2b) "stat" and compare mसमय, on stat failure करो nothing
 * 3)  Simply always call invalidate_inode_pages2_range on the range of the पढ़ो
 *
 * Currently we are keeping things KISS and using option 1. this allows
 * directly using generic_file_पढ़ो_iter without wrapping it.
 *
 * This means that only data written on the host side beक्रमe खोलो() on
 * the guest side is guaranteed to be seen by the guest. If necessary
 * we may provide other पढ़ो-cache strategies in the future and make this
 * configurable through a mount option.
 */
स्थिर काष्ठा file_operations vboxsf_reg_fops = अणु
	.llseek = generic_file_llseek,
	.पढ़ो_iter = generic_file_पढ़ो_iter,
	.ग_लिखो_iter = generic_file_ग_लिखो_iter,
	.mmap = vboxsf_file_mmap,
	.खोलो = vboxsf_file_खोलो,
	.release = vboxsf_file_release,
	.fsync = noop_fsync,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
पूर्ण;

स्थिर काष्ठा inode_operations vboxsf_reg_iops = अणु
	.getattr = vboxsf_getattr,
	.setattr = vboxsf_setattr
पूर्ण;

अटल पूर्णांक vboxsf_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा vboxsf_handle *sf_handle = file->निजी_data;
	loff_t off = page_offset(page);
	u32 nपढ़ो = PAGE_SIZE;
	u8 *buf;
	पूर्णांक err;

	buf = kmap(page);

	err = vboxsf_पढ़ो(sf_handle->root, sf_handle->handle, off, &nपढ़ो, buf);
	अगर (err == 0) अणु
		स_रखो(&buf[nपढ़ो], 0, PAGE_SIZE - nपढ़ो);
		flush_dcache_page(page);
		SetPageUptodate(page);
	पूर्ण अन्यथा अणु
		SetPageError(page);
	पूर्ण

	kunmap(page);
	unlock_page(page);
	वापस err;
पूर्ण

अटल काष्ठा vboxsf_handle *vboxsf_get_ग_लिखो_handle(काष्ठा vboxsf_inode *sf_i)
अणु
	काष्ठा vboxsf_handle *h, *sf_handle = शून्य;

	mutex_lock(&sf_i->handle_list_mutex);
	list_क्रम_each_entry(h, &sf_i->handle_list, head) अणु
		अगर (h->access_flags == SHFL_CF_ACCESS_WRITE ||
		    h->access_flags == SHFL_CF_ACCESS_READWRITE) अणु
			kref_get(&h->refcount);
			sf_handle = h;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&sf_i->handle_list_mutex);

	वापस sf_handle;
पूर्ण

अटल पूर्णांक vboxsf_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा vboxsf_inode *sf_i = VBOXSF_I(inode);
	काष्ठा vboxsf_handle *sf_handle;
	loff_t off = page_offset(page);
	loff_t size = i_size_पढ़ो(inode);
	u32 nग_लिखो = PAGE_SIZE;
	u8 *buf;
	पूर्णांक err;

	अगर (off + PAGE_SIZE > size)
		nग_लिखो = size & ~PAGE_MASK;

	sf_handle = vboxsf_get_ग_लिखो_handle(sf_i);
	अगर (!sf_handle)
		वापस -EBADF;

	buf = kmap(page);
	err = vboxsf_ग_लिखो(sf_handle->root, sf_handle->handle,
			   off, &nग_लिखो, buf);
	kunmap(page);

	kref_put(&sf_handle->refcount, vboxsf_handle_release);

	अगर (err == 0) अणु
		ClearPageError(page);
		/* mसमय changed */
		sf_i->क्रमce_restat = 1;
	पूर्ण अन्यथा अणु
		ClearPageUptodate(page);
	पूर्ण

	unlock_page(page);
	वापस err;
पूर्ण

अटल पूर्णांक vboxsf_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			    loff_t pos, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक copied,
			    काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा vboxsf_handle *sf_handle = file->निजी_data;
	अचिन्हित पूर्णांक from = pos & ~PAGE_MASK;
	u32 nwritten = len;
	u8 *buf;
	पूर्णांक err;

	/* zero the stale part of the page अगर we did a लघु copy */
	अगर (!PageUptodate(page) && copied < len)
		zero_user(page, from + copied, len - copied);

	buf = kmap(page);
	err = vboxsf_ग_लिखो(sf_handle->root, sf_handle->handle,
			   pos, &nwritten, buf + from);
	kunmap(page);

	अगर (err) अणु
		nwritten = 0;
		जाओ out;
	पूर्ण

	/* mसमय changed */
	VBOXSF_I(inode)->क्रमce_restat = 1;

	अगर (!PageUptodate(page) && nwritten == PAGE_SIZE)
		SetPageUptodate(page);

	pos += nwritten;
	अगर (pos > inode->i_size)
		i_size_ग_लिखो(inode, pos);

out:
	unlock_page(page);
	put_page(page);

	वापस nwritten;
पूर्ण

/*
 * Note simple_ग_लिखो_begin करोes not पढ़ो the page from disk on partial ग_लिखोs
 * this is ok since vboxsf_ग_लिखो_end only ग_लिखोs the written parts of the
 * page and it करोes not call SetPageUptodate क्रम partial ग_लिखोs.
 */
स्थिर काष्ठा address_space_operations vboxsf_reg_aops = अणु
	.पढ़ोpage = vboxsf_पढ़ोpage,
	.ग_लिखोpage = vboxsf_ग_लिखोpage,
	.set_page_dirty = __set_page_dirty_nobuffers,
	.ग_लिखो_begin = simple_ग_लिखो_begin,
	.ग_लिखो_end = vboxsf_ग_लिखो_end,
पूर्ण;

अटल स्थिर अक्षर *vboxsf_get_link(काष्ठा dentry *dentry, काष्ठा inode *inode,
				   काष्ठा delayed_call *करोne)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(inode->i_sb);
	काष्ठा shfl_string *path;
	अक्षर *link;
	पूर्णांक err;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	path = vboxsf_path_from_dentry(sbi, dentry);
	अगर (IS_ERR(path))
		वापस ERR_CAST(path);

	link = kzalloc(PATH_MAX, GFP_KERNEL);
	अगर (!link) अणु
		__putname(path);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	err = vboxsf_पढ़ोlink(sbi->root, path, PATH_MAX, link);
	__putname(path);
	अगर (err) अणु
		kमुक्त(link);
		वापस ERR_PTR(err);
	पूर्ण

	set_delayed_call(करोne, kमुक्त_link, link);
	वापस link;
पूर्ण

स्थिर काष्ठा inode_operations vboxsf_lnk_iops = अणु
	.get_link = vboxsf_get_link
पूर्ण;
