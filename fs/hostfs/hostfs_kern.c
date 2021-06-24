<शैली गुरु>
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 *
 * Ported the fileप्रणाली routines to 2.5.
 * 2003-02-10 Petr Baudis <pasky@ucw.cz>
 */

#समावेश <linux/fs.h>
#समावेश <linux/magic.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/statfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश "hostfs.h"
#समावेश <init.h>
#समावेश <kern.h>

काष्ठा hostfs_inode_info अणु
	पूर्णांक fd;
	भ_शेषe_t mode;
	काष्ठा inode vfs_inode;
	काष्ठा mutex खोलो_mutex;
पूर्ण;

अटल अंतरभूत काष्ठा hostfs_inode_info *HOSTFS_I(काष्ठा inode *inode)
अणु
	वापस list_entry(inode, काष्ठा hostfs_inode_info, vfs_inode);
पूर्ण

#घोषणा खाता_HOSTFS_I(file) HOSTFS_I(file_inode(file))

अटल काष्ठा kmem_cache *hostfs_inode_cache;

/* Changed in hostfs_args beक्रमe the kernel starts running */
अटल अक्षर *root_ino = "";
अटल पूर्णांक append = 0;

अटल स्थिर काष्ठा inode_operations hostfs_iops;
अटल स्थिर काष्ठा inode_operations hostfs_dir_iops;
अटल स्थिर काष्ठा inode_operations hostfs_link_iops;

#अगर_अघोषित MODULE
अटल पूर्णांक __init hostfs_args(अक्षर *options, पूर्णांक *add)
अणु
	अक्षर *ptr;

	ptr = म_अक्षर(options, ',');
	अगर (ptr != शून्य)
		*ptr++ = '\0';
	अगर (*options != '\0')
		root_ino = options;

	options = ptr;
	जबतक (options) अणु
		ptr = म_अक्षर(options, ',');
		अगर (ptr != शून्य)
			*ptr++ = '\0';
		अगर (*options != '\0') अणु
			अगर (!म_भेद(options, "append"))
				append = 1;
			अन्यथा म_लिखो("hostfs_args - unsupported option - %s\n",
				    options);
		पूर्ण
		options = ptr;
	पूर्ण
	वापस 0;
पूर्ण

__uml_setup("hostfs=", hostfs_args,
"hostfs=<root dir>,<flags>,...\n"
"    This is used to set hostfs parameters.  The root directory argument\n"
"    is used to confine all hostfs mounts to within the specified directory\n"
"    tree on the host.  If this isn't specified, then a user inside UML can\n"
"    mount anything on the host that's accessible to the user that's running\n"
"    it.\n"
"    The only flag currently supported is 'append', which specifies that all\n"
"    files opened by hostfs will be opened in append mode.\n\n"
);
#पूर्ण_अगर

अटल अक्षर *__dentry_name(काष्ठा dentry *dentry, अक्षर *name)
अणु
	अक्षर *p = dentry_path_raw(dentry, name, PATH_MAX);
	अक्षर *root;
	माप_प्रकार len;

	root = dentry->d_sb->s_fs_info;
	len = म_माप(root);
	अगर (IS_ERR(p)) अणु
		__putname(name);
		वापस शून्य;
	पूर्ण

	/*
	 * This function relies on the fact that dentry_path_raw() will place
	 * the path name at the end of the provided buffer.
	 */
	BUG_ON(p + म_माप(p) + 1 != name + PATH_MAX);

	strlcpy(name, root, PATH_MAX);
	अगर (len > p - name) अणु
		__putname(name);
		वापस शून्य;
	पूर्ण

	अगर (p > name + len)
		म_नकल(name + len, p);

	वापस name;
पूर्ण

अटल अक्षर *dentry_name(काष्ठा dentry *dentry)
अणु
	अक्षर *name = __getname();
	अगर (!name)
		वापस शून्य;

	वापस __dentry_name(dentry, name);
पूर्ण

अटल अक्षर *inode_name(काष्ठा inode *ino)
अणु
	काष्ठा dentry *dentry;
	अक्षर *name;

	dentry = d_find_alias(ino);
	अगर (!dentry)
		वापस शून्य;

	name = dentry_name(dentry);

	dput(dentry);

	वापस name;
पूर्ण

अटल अक्षर *follow_link(अक्षर *link)
अणु
	अक्षर *name, *resolved, *end;
	पूर्णांक n;

	name = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (!name) अणु
		n = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	n = hostfs_करो_पढ़ोlink(link, name, PATH_MAX);
	अगर (n < 0)
		जाओ out_मुक्त;
	अन्यथा अगर (n == PATH_MAX) अणु
		n = -E2BIG;
		जाओ out_मुक्त;
	पूर्ण

	अगर (*name == '/')
		वापस name;

	end = म_खोजप(link, '/');
	अगर (end == शून्य)
		वापस name;

	*(end + 1) = '\0';

	resolved = kaप्र_लिखो(GFP_KERNEL, "%s%s", link, name);
	अगर (resolved == शून्य) अणु
		n = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	kमुक्त(name);
	वापस resolved;

 out_मुक्त:
	kमुक्त(name);
	वापस ERR_PTR(n);
पूर्ण

अटल काष्ठा inode *hostfs_iget(काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode = new_inode(sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	वापस inode;
पूर्ण

अटल पूर्णांक hostfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *sf)
अणु
	/*
	 * करो_statfs uses काष्ठा statfs64 पूर्णांकernally, but the linux kernel
	 * काष्ठा statfs still has 32-bit versions क्रम most of these fields,
	 * so we convert them here
	 */
	पूर्णांक err;
	दीर्घ दीर्घ f_blocks;
	दीर्घ दीर्घ f_bमुक्त;
	दीर्घ दीर्घ f_bavail;
	दीर्घ दीर्घ f_files;
	दीर्घ दीर्घ f_fमुक्त;

	err = करो_statfs(dentry->d_sb->s_fs_info,
			&sf->f_bsize, &f_blocks, &f_bमुक्त, &f_bavail, &f_files,
			&f_fमुक्त, &sf->f_fsid, माप(sf->f_fsid),
			&sf->f_namelen);
	अगर (err)
		वापस err;
	sf->f_blocks = f_blocks;
	sf->f_bमुक्त = f_bमुक्त;
	sf->f_bavail = f_bavail;
	sf->f_files = f_files;
	sf->f_fमुक्त = f_fमुक्त;
	sf->f_type = HOSTFS_SUPER_MAGIC;
	वापस 0;
पूर्ण

अटल काष्ठा inode *hostfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा hostfs_inode_info *hi;

	hi = kmem_cache_alloc(hostfs_inode_cache, GFP_KERNEL_ACCOUNT);
	अगर (hi == शून्य)
		वापस शून्य;
	hi->fd = -1;
	hi->mode = 0;
	inode_init_once(&hi->vfs_inode);
	mutex_init(&hi->खोलो_mutex);
	वापस &hi->vfs_inode;
पूर्ण

अटल व्योम hostfs_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	अगर (HOSTFS_I(inode)->fd != -1) अणु
		बंद_file(&HOSTFS_I(inode)->fd);
		HOSTFS_I(inode)->fd = -1;
	पूर्ण
पूर्ण

अटल व्योम hostfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(hostfs_inode_cache, HOSTFS_I(inode));
पूर्ण

अटल पूर्णांक hostfs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	स्थिर अक्षर *root_path = root->d_sb->s_fs_info;
	माप_प्रकार offset = म_माप(root_ino) + 1;

	अगर (म_माप(root_path) > offset)
		seq_show_option(seq, root_path + offset, शून्य);

	अगर (append)
		seq_माला_दो(seq, ",append");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations hostfs_sbops = अणु
	.alloc_inode	= hostfs_alloc_inode,
	.मुक्त_inode	= hostfs_मुक्त_inode,
	.evict_inode	= hostfs_evict_inode,
	.statfs		= hostfs_statfs,
	.show_options	= hostfs_show_options,
पूर्ण;

अटल पूर्णांक hostfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	व्योम *dir;
	अक्षर *name;
	अचिन्हित दीर्घ दीर्घ next, ino;
	पूर्णांक error, len;
	अचिन्हित पूर्णांक type;

	name = dentry_name(file->f_path.dentry);
	अगर (name == शून्य)
		वापस -ENOMEM;
	dir = खोलो_dir(name, &error);
	__putname(name);
	अगर (dir == शून्य)
		वापस -error;
	next = ctx->pos;
	seek_dir(dir, next);
	जबतक ((name = पढ़ो_dir(dir, &next, &ino, &len, &type)) != शून्य) अणु
		अगर (!dir_emit(ctx, name, len, ino, type))
			अवरोध;
		ctx->pos = next;
	पूर्ण
	बंद_dir(dir);
	वापस 0;
पूर्ण

अटल पूर्णांक hostfs_खोलो(काष्ठा inode *ino, काष्ठा file *file)
अणु
	अक्षर *name;
	भ_शेषe_t mode;
	पूर्णांक err;
	पूर्णांक r, w, fd;

	mode = file->f_mode & (FMODE_READ | FMODE_WRITE);
	अगर ((mode & HOSTFS_I(ino)->mode) == mode)
		वापस 0;

	mode |= HOSTFS_I(ino)->mode;

retry:
	r = w = 0;

	अगर (mode & FMODE_READ)
		r = 1;
	अगर (mode & FMODE_WRITE)
		r = w = 1;

	name = dentry_name(file_dentry(file));
	अगर (name == शून्य)
		वापस -ENOMEM;

	fd = खोलो_file(name, r, w, append);
	__putname(name);
	अगर (fd < 0)
		वापस fd;

	mutex_lock(&HOSTFS_I(ino)->खोलो_mutex);
	/* somebody अन्यथा had handled it first? */
	अगर ((mode & HOSTFS_I(ino)->mode) == mode) अणु
		mutex_unlock(&HOSTFS_I(ino)->खोलो_mutex);
		बंद_file(&fd);
		वापस 0;
	पूर्ण
	अगर ((mode | HOSTFS_I(ino)->mode) != mode) अणु
		mode |= HOSTFS_I(ino)->mode;
		mutex_unlock(&HOSTFS_I(ino)->खोलो_mutex);
		बंद_file(&fd);
		जाओ retry;
	पूर्ण
	अगर (HOSTFS_I(ino)->fd == -1) अणु
		HOSTFS_I(ino)->fd = fd;
	पूर्ण अन्यथा अणु
		err = replace_file(fd, HOSTFS_I(ino)->fd);
		बंद_file(&fd);
		अगर (err < 0) अणु
			mutex_unlock(&HOSTFS_I(ino)->खोलो_mutex);
			वापस err;
		पूर्ण
	पूर्ण
	HOSTFS_I(ino)->mode = mode;
	mutex_unlock(&HOSTFS_I(ino)->खोलो_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक hostfs_file_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	filemap_ग_लिखो_and_रुको(inode->i_mapping);

	वापस 0;
पूर्ण

अटल पूर्णांक hostfs_fsync(काष्ठा file *file, loff_t start, loff_t end,
			पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	पूर्णांक ret;

	ret = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (ret)
		वापस ret;

	inode_lock(inode);
	ret = fsync_file(HOSTFS_I(inode)->fd, datasync);
	inode_unlock(inode);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations hostfs_file_fops = अणु
	.llseek		= generic_file_llseek,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.mmap		= generic_file_mmap,
	.खोलो		= hostfs_खोलो,
	.release	= hostfs_file_release,
	.fsync		= hostfs_fsync,
पूर्ण;

अटल स्थिर काष्ठा file_operations hostfs_dir_fops = अणु
	.llseek		= generic_file_llseek,
	.iterate_shared	= hostfs_सूची_पढ़ो,
	.पढ़ो		= generic_पढ़ो_dir,
	.खोलो		= hostfs_खोलो,
	.fsync		= hostfs_fsync,
पूर्ण;

अटल पूर्णांक hostfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा inode *inode = mapping->host;
	अक्षर *buffer;
	loff_t base = page_offset(page);
	पूर्णांक count = PAGE_SIZE;
	पूर्णांक end_index = inode->i_size >> PAGE_SHIFT;
	पूर्णांक err;

	अगर (page->index >= end_index)
		count = inode->i_size & (PAGE_SIZE-1);

	buffer = kmap(page);

	err = ग_लिखो_file(HOSTFS_I(inode)->fd, &base, buffer, count);
	अगर (err != count) अणु
		ClearPageUptodate(page);
		जाओ out;
	पूर्ण

	अगर (base > inode->i_size)
		inode->i_size = base;

	अगर (PageError(page))
		ClearPageError(page);
	err = 0;

 out:
	kunmap(page);

	unlock_page(page);
	वापस err;
पूर्ण

अटल पूर्णांक hostfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	अक्षर *buffer;
	loff_t start = page_offset(page);
	पूर्णांक bytes_पढ़ो, ret = 0;

	buffer = kmap(page);
	bytes_पढ़ो = पढ़ो_file(खाता_HOSTFS_I(file)->fd, &start, buffer,
			PAGE_SIZE);
	अगर (bytes_पढ़ो < 0) अणु
		ClearPageUptodate(page);
		SetPageError(page);
		ret = bytes_पढ़ो;
		जाओ out;
	पूर्ण

	स_रखो(buffer + bytes_पढ़ो, 0, PAGE_SIZE - bytes_पढ़ो);

	ClearPageError(page);
	SetPageUptodate(page);

 out:
	flush_dcache_page(page);
	kunmap(page);
	unlock_page(page);
	वापस ret;
पूर्ण

अटल पूर्णांक hostfs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			      loff_t pos, अचिन्हित len, अचिन्हित flags,
			      काष्ठा page **pagep, व्योम **fsdata)
अणु
	pgoff_t index = pos >> PAGE_SHIFT;

	*pagep = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!*pagep)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक hostfs_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			    loff_t pos, अचिन्हित len, अचिन्हित copied,
			    काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	व्योम *buffer;
	अचिन्हित from = pos & (PAGE_SIZE - 1);
	पूर्णांक err;

	buffer = kmap(page);
	err = ग_लिखो_file(खाता_HOSTFS_I(file)->fd, &pos, buffer + from, copied);
	kunmap(page);

	अगर (!PageUptodate(page) && err == PAGE_SIZE)
		SetPageUptodate(page);

	/*
	 * If err > 0, ग_लिखो_file has added err to pos, so we are comparing
	 * i_size against the last byte written.
	 */
	अगर (err > 0 && (pos > inode->i_size))
		inode->i_size = pos;
	unlock_page(page);
	put_page(page);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा address_space_operations hostfs_aops = अणु
	.ग_लिखोpage 	= hostfs_ग_लिखोpage,
	.पढ़ोpage	= hostfs_पढ़ोpage,
	.set_page_dirty = __set_page_dirty_nobuffers,
	.ग_लिखो_begin	= hostfs_ग_लिखो_begin,
	.ग_लिखो_end	= hostfs_ग_लिखो_end,
पूर्ण;

अटल पूर्णांक पढ़ो_name(काष्ठा inode *ino, अक्षर *name)
अणु
	dev_t rdev;
	काष्ठा hostfs_stat st;
	पूर्णांक err = stat_file(name, &st, -1);
	अगर (err)
		वापस err;

	/* Reencode maj and min with the kernel encoding.*/
	rdev = MKDEV(st.maj, st.min);

	चयन (st.mode & S_IFMT) अणु
	हाल S_IFLNK:
		ino->i_op = &hostfs_link_iops;
		अवरोध;
	हाल S_IFसूची:
		ino->i_op = &hostfs_dir_iops;
		ino->i_fop = &hostfs_dir_fops;
		अवरोध;
	हाल S_IFCHR:
	हाल S_IFBLK:
	हाल S_IFIFO:
	हाल S_IFSOCK:
		init_special_inode(ino, st.mode & S_IFMT, rdev);
		ino->i_op = &hostfs_iops;
		अवरोध;
	हाल S_IFREG:
		ino->i_op = &hostfs_iops;
		ino->i_fop = &hostfs_file_fops;
		ino->i_mapping->a_ops = &hostfs_aops;
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण

	ino->i_ino = st.ino;
	ino->i_mode = st.mode;
	set_nlink(ino, st.nlink);
	i_uid_ग_लिखो(ino, st.uid);
	i_gid_ग_लिखो(ino, st.gid);
	ino->i_aसमय = (काष्ठा बारpec64)अणु st.aसमय.tv_sec, st.aसमय.tv_nsec पूर्ण;
	ino->i_mसमय = (काष्ठा बारpec64)अणु st.mसमय.tv_sec, st.mसमय.tv_nsec पूर्ण;
	ino->i_स_समय = (काष्ठा बारpec64)अणु st.स_समय.tv_sec, st.स_समय.tv_nsec पूर्ण;
	ino->i_size = st.size;
	ino->i_blocks = st.blocks;
	वापस 0;
पूर्ण

अटल पूर्णांक hostfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			 काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा inode *inode;
	अक्षर *name;
	पूर्णांक error, fd;

	inode = hostfs_iget(dir->i_sb);
	अगर (IS_ERR(inode)) अणु
		error = PTR_ERR(inode);
		जाओ out;
	पूर्ण

	error = -ENOMEM;
	name = dentry_name(dentry);
	अगर (name == शून्य)
		जाओ out_put;

	fd = file_create(name, mode & 0777);
	अगर (fd < 0)
		error = fd;
	अन्यथा
		error = पढ़ो_name(inode, name);

	__putname(name);
	अगर (error)
		जाओ out_put;

	HOSTFS_I(inode)->fd = fd;
	HOSTFS_I(inode)->mode = FMODE_READ | FMODE_WRITE;
	d_instantiate(dentry, inode);
	वापस 0;

 out_put:
	iput(inode);
 out:
	वापस error;
पूर्ण

अटल काष्ठा dentry *hostfs_lookup(काष्ठा inode *ino, काष्ठा dentry *dentry,
				    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	अक्षर *name;
	पूर्णांक err;

	inode = hostfs_iget(ino->i_sb);
	अगर (IS_ERR(inode))
		जाओ out;

	err = -ENOMEM;
	name = dentry_name(dentry);
	अगर (name) अणु
		err = पढ़ो_name(inode, name);
		__putname(name);
	पूर्ण
	अगर (err) अणु
		iput(inode);
		inode = (err == -ENOENT) ? शून्य : ERR_PTR(err);
	पूर्ण
 out:
	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल पूर्णांक hostfs_link(काष्ठा dentry *to, काष्ठा inode *ino,
		       काष्ठा dentry *from)
अणु
	अक्षर *from_name, *to_name;
	पूर्णांक err;

	अगर ((from_name = dentry_name(from)) == शून्य)
		वापस -ENOMEM;
	to_name = dentry_name(to);
	अगर (to_name == शून्य) अणु
		__putname(from_name);
		वापस -ENOMEM;
	पूर्ण
	err = link_file(to_name, from_name);
	__putname(from_name);
	__putname(to_name);
	वापस err;
पूर्ण

अटल पूर्णांक hostfs_unlink(काष्ठा inode *ino, काष्ठा dentry *dentry)
अणु
	अक्षर *file;
	पूर्णांक err;

	अगर (append)
		वापस -EPERM;

	अगर ((file = dentry_name(dentry)) == शून्य)
		वापस -ENOMEM;

	err = unlink_file(file);
	__putname(file);
	वापस err;
पूर्ण

अटल पूर्णांक hostfs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *ino,
			  काष्ठा dentry *dentry, स्थिर अक्षर *to)
अणु
	अक्षर *file;
	पूर्णांक err;

	अगर ((file = dentry_name(dentry)) == शून्य)
		वापस -ENOMEM;
	err = make_symlink(file, to);
	__putname(file);
	वापस err;
पूर्ण

अटल पूर्णांक hostfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *ino,
			काष्ठा dentry *dentry, umode_t mode)
अणु
	अक्षर *file;
	पूर्णांक err;

	अगर ((file = dentry_name(dentry)) == शून्य)
		वापस -ENOMEM;
	err = करो_सूची_गढ़ो(file, mode);
	__putname(file);
	वापस err;
पूर्ण

अटल पूर्णांक hostfs_सूची_हटाओ(काष्ठा inode *ino, काष्ठा dentry *dentry)
अणु
	अक्षर *file;
	पूर्णांक err;

	अगर ((file = dentry_name(dentry)) == शून्य)
		वापस -ENOMEM;
	err = hostfs_करो_सूची_हटाओ(file);
	__putname(file);
	वापस err;
पूर्ण

अटल पूर्णांक hostfs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode, dev_t dev)
अणु
	काष्ठा inode *inode;
	अक्षर *name;
	पूर्णांक err;

	inode = hostfs_iget(dir->i_sb);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		जाओ out;
	पूर्ण

	err = -ENOMEM;
	name = dentry_name(dentry);
	अगर (name == शून्य)
		जाओ out_put;

	err = करो_mknod(name, mode, MAJOR(dev), MINOR(dev));
	अगर (err)
		जाओ out_मुक्त;

	err = पढ़ो_name(inode, name);
	__putname(name);
	अगर (err)
		जाओ out_put;

	d_instantiate(dentry, inode);
	वापस 0;

 out_मुक्त:
	__putname(name);
 out_put:
	iput(inode);
 out:
	वापस err;
पूर्ण

अटल पूर्णांक hostfs_नाम2(काष्ठा user_namespace *mnt_userns,
			  काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			  काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			  अचिन्हित पूर्णांक flags)
अणु
	अक्षर *old_name, *new_name;
	पूर्णांक err;

	अगर (flags & ~(RENAME_NOREPLACE | RENAME_EXCHANGE))
		वापस -EINVAL;

	old_name = dentry_name(old_dentry);
	अगर (old_name == शून्य)
		वापस -ENOMEM;
	new_name = dentry_name(new_dentry);
	अगर (new_name == शून्य) अणु
		__putname(old_name);
		वापस -ENOMEM;
	पूर्ण
	अगर (!flags)
		err = नाम_file(old_name, new_name);
	अन्यथा
		err = नाम2_file(old_name, new_name, flags);

	__putname(old_name);
	__putname(new_name);
	वापस err;
पूर्ण

अटल पूर्णांक hostfs_permission(काष्ठा user_namespace *mnt_userns,
			     काष्ठा inode *ino, पूर्णांक desired)
अणु
	अक्षर *name;
	पूर्णांक r = 0, w = 0, x = 0, err;

	अगर (desired & MAY_NOT_BLOCK)
		वापस -ECHILD;

	अगर (desired & MAY_READ) r = 1;
	अगर (desired & MAY_WRITE) w = 1;
	अगर (desired & MAY_EXEC) x = 1;
	name = inode_name(ino);
	अगर (name == शून्य)
		वापस -ENOMEM;

	अगर (S_ISCHR(ino->i_mode) || S_ISBLK(ino->i_mode) ||
	    S_ISFIFO(ino->i_mode) || S_ISSOCK(ino->i_mode))
		err = 0;
	अन्यथा
		err = access_file(name, r, w, x);
	__putname(name);
	अगर (!err)
		err = generic_permission(&init_user_ns, ino, desired);
	वापस err;
पूर्ण

अटल पूर्णांक hostfs_setattr(काष्ठा user_namespace *mnt_userns,
			  काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा hostfs_iattr attrs;
	अक्षर *name;
	पूर्णांक err;

	पूर्णांक fd = HOSTFS_I(inode)->fd;

	err = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (err)
		वापस err;

	अगर (append)
		attr->ia_valid &= ~ATTR_SIZE;

	attrs.ia_valid = 0;
	अगर (attr->ia_valid & ATTR_MODE) अणु
		attrs.ia_valid |= HOSTFS_ATTR_MODE;
		attrs.ia_mode = attr->ia_mode;
	पूर्ण
	अगर (attr->ia_valid & ATTR_UID) अणु
		attrs.ia_valid |= HOSTFS_ATTR_UID;
		attrs.ia_uid = from_kuid(&init_user_ns, attr->ia_uid);
	पूर्ण
	अगर (attr->ia_valid & ATTR_GID) अणु
		attrs.ia_valid |= HOSTFS_ATTR_GID;
		attrs.ia_gid = from_kgid(&init_user_ns, attr->ia_gid);
	पूर्ण
	अगर (attr->ia_valid & ATTR_SIZE) अणु
		attrs.ia_valid |= HOSTFS_ATTR_SIZE;
		attrs.ia_size = attr->ia_size;
	पूर्ण
	अगर (attr->ia_valid & ATTR_ATIME) अणु
		attrs.ia_valid |= HOSTFS_ATTR_ATIME;
		attrs.ia_aसमय = (काष्ठा hostfs_बारpec)
			अणु attr->ia_aसमय.tv_sec, attr->ia_aसमय.tv_nsec पूर्ण;
	पूर्ण
	अगर (attr->ia_valid & ATTR_MTIME) अणु
		attrs.ia_valid |= HOSTFS_ATTR_MTIME;
		attrs.ia_mसमय = (काष्ठा hostfs_बारpec)
			अणु attr->ia_mसमय.tv_sec, attr->ia_mसमय.tv_nsec पूर्ण;
	पूर्ण
	अगर (attr->ia_valid & ATTR_CTIME) अणु
		attrs.ia_valid |= HOSTFS_ATTR_CTIME;
		attrs.ia_स_समय = (काष्ठा hostfs_बारpec)
			अणु attr->ia_स_समय.tv_sec, attr->ia_स_समय.tv_nsec पूर्ण;
	पूर्ण
	अगर (attr->ia_valid & ATTR_ATIME_SET) अणु
		attrs.ia_valid |= HOSTFS_ATTR_ATIME_SET;
	पूर्ण
	अगर (attr->ia_valid & ATTR_MTIME_SET) अणु
		attrs.ia_valid |= HOSTFS_ATTR_MTIME_SET;
	पूर्ण
	name = dentry_name(dentry);
	अगर (name == शून्य)
		वापस -ENOMEM;
	err = set_attr(name, &attrs, fd);
	__putname(name);
	अगर (err)
		वापस err;

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size != i_size_पढ़ो(inode))
		truncate_setsize(inode, attr->ia_size);

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा inode_operations hostfs_iops = अणु
	.permission	= hostfs_permission,
	.setattr	= hostfs_setattr,
पूर्ण;

अटल स्थिर काष्ठा inode_operations hostfs_dir_iops = अणु
	.create		= hostfs_create,
	.lookup		= hostfs_lookup,
	.link		= hostfs_link,
	.unlink		= hostfs_unlink,
	.symlink	= hostfs_symlink,
	.सूची_गढ़ो		= hostfs_सूची_गढ़ो,
	.सूची_हटाओ		= hostfs_सूची_हटाओ,
	.mknod		= hostfs_mknod,
	.नाम		= hostfs_नाम2,
	.permission	= hostfs_permission,
	.setattr	= hostfs_setattr,
पूर्ण;

अटल स्थिर अक्षर *hostfs_get_link(काष्ठा dentry *dentry,
				   काष्ठा inode *inode,
				   काष्ठा delayed_call *करोne)
अणु
	अक्षर *link;
	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);
	link = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (link) अणु
		अक्षर *path = dentry_name(dentry);
		पूर्णांक err = -ENOMEM;
		अगर (path) अणु
			err = hostfs_करो_पढ़ोlink(path, link, PATH_MAX);
			अगर (err == PATH_MAX)
				err = -E2BIG;
			__putname(path);
		पूर्ण
		अगर (err < 0) अणु
			kमुक्त(link);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	set_delayed_call(करोne, kमुक्त_link, link);
	वापस link;
पूर्ण

अटल स्थिर काष्ठा inode_operations hostfs_link_iops = अणु
	.get_link	= hostfs_get_link,
पूर्ण;

अटल पूर्णांक hostfs_fill_sb_common(काष्ठा super_block *sb, व्योम *d, पूर्णांक silent)
अणु
	काष्ठा inode *root_inode;
	अक्षर *host_root_path, *req_root = d;
	पूर्णांक err;

	sb->s_blocksize = 1024;
	sb->s_blocksize_bits = 10;
	sb->s_magic = HOSTFS_SUPER_MAGIC;
	sb->s_op = &hostfs_sbops;
	sb->s_d_op = &simple_dentry_operations;
	sb->s_maxbytes = MAX_LFS_खाताSIZE;

	/* शून्य is prपूर्णांकed as '(null)' by म_लिखो(): aव्योम that. */
	अगर (req_root == शून्य)
		req_root = "";

	err = -ENOMEM;
	sb->s_fs_info = host_root_path =
		kaप्र_लिखो(GFP_KERNEL, "%s/%s", root_ino, req_root);
	अगर (host_root_path == शून्य)
		जाओ out;

	root_inode = new_inode(sb);
	अगर (!root_inode)
		जाओ out;

	err = पढ़ो_name(root_inode, host_root_path);
	अगर (err)
		जाओ out_put;

	अगर (S_ISLNK(root_inode->i_mode)) अणु
		अक्षर *name = follow_link(host_root_path);
		अगर (IS_ERR(name)) अणु
			err = PTR_ERR(name);
			जाओ out_put;
		पूर्ण
		err = पढ़ो_name(root_inode, name);
		kमुक्त(name);
		अगर (err)
			जाओ out_put;
	पूर्ण

	err = -ENOMEM;
	sb->s_root = d_make_root(root_inode);
	अगर (sb->s_root == शून्य)
		जाओ out;

	वापस 0;

out_put:
	iput(root_inode);
out:
	वापस err;
पूर्ण

अटल काष्ठा dentry *hostfs_पढ़ो_sb(काष्ठा file_प्रणाली_type *type,
			  पूर्णांक flags, स्थिर अक्षर *dev_name,
			  व्योम *data)
अणु
	वापस mount_nodev(type, flags, data, hostfs_fill_sb_common);
पूर्ण

अटल व्योम hostfs_समाप्त_sb(काष्ठा super_block *s)
अणु
	समाप्त_anon_super(s);
	kमुक्त(s->s_fs_info);
पूर्ण

अटल काष्ठा file_प्रणाली_type hostfs_type = अणु
	.owner 		= THIS_MODULE,
	.name 		= "hostfs",
	.mount	 	= hostfs_पढ़ो_sb,
	.समाप्त_sb	= hostfs_समाप्त_sb,
	.fs_flags 	= 0,
पूर्ण;
MODULE_ALIAS_FS("hostfs");

अटल पूर्णांक __init init_hostfs(व्योम)
अणु
	hostfs_inode_cache = KMEM_CACHE(hostfs_inode_info, 0);
	अगर (!hostfs_inode_cache)
		वापस -ENOMEM;
	वापस रेजिस्टर_fileप्रणाली(&hostfs_type);
पूर्ण

अटल व्योम __निकास निकास_hostfs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&hostfs_type);
	kmem_cache_destroy(hostfs_inode_cache);
पूर्ण

module_init(init_hostfs)
module_निकास(निकास_hostfs)
MODULE_LICENSE("GPL");
