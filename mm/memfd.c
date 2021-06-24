<शैली गुरु>
/*
 * memfd_create प्रणाली call and file sealing support
 *
 * Code was originally included in shmem.c, and broken out to facilitate
 * use by hugetlbfs as well as पंचांगpfs.
 *
 * This file is released under the GPL.
 */

#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/file.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/khugepaged.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/memfd.h>
#समावेश <uapi/linux/memfd.h>

/*
 * We need a tag: a new tag would expand every xa_node by 8 bytes,
 * so reuse a tag which we firmly believe is never set or cleared on पंचांगpfs
 * or hugetlbfs because they are memory only fileप्रणालीs.
 */
#घोषणा MEMFD_TAG_PINNED        PAGECACHE_TAG_TOWRITE
#घोषणा LAST_SCAN               4       /* about 150ms max */

अटल व्योम memfd_tag_pins(काष्ठा xa_state *xas)
अणु
	काष्ठा page *page;
	अचिन्हित पूर्णांक tagged = 0;

	lru_add_drain();

	xas_lock_irq(xas);
	xas_क्रम_each(xas, page, अच_दीर्घ_उच्च) अणु
		अगर (xa_is_value(page))
			जारी;
		page = find_subpage(page, xas->xa_index);
		अगर (page_count(page) - page_mapcount(page) > 1)
			xas_set_mark(xas, MEMFD_TAG_PINNED);

		अगर (++tagged % XA_CHECK_SCHED)
			जारी;

		xas_छोड़ो(xas);
		xas_unlock_irq(xas);
		cond_resched();
		xas_lock_irq(xas);
	पूर्ण
	xas_unlock_irq(xas);
पूर्ण

/*
 * Setting SEAL_WRITE requires us to verअगरy there's no pending ग_लिखोr. However,
 * via get_user_pages(), drivers might have some pending I/O without any active
 * user-space mappings (eg., direct-IO, AIO). Thereक्रमe, we look at all pages
 * and see whether it has an elevated ref-count. If so, we tag them and रुको क्रम
 * them to be dropped.
 * The caller must guarantee that no new user will acquire writable references
 * to those pages to aव्योम races.
 */
अटल पूर्णांक memfd_रुको_क्रम_pins(काष्ठा address_space *mapping)
अणु
	XA_STATE(xas, &mapping->i_pages, 0);
	काष्ठा page *page;
	पूर्णांक error, scan;

	memfd_tag_pins(&xas);

	error = 0;
	क्रम (scan = 0; scan <= LAST_SCAN; scan++) अणु
		अचिन्हित पूर्णांक tagged = 0;

		अगर (!xas_marked(&xas, MEMFD_TAG_PINNED))
			अवरोध;

		अगर (!scan)
			lru_add_drain_all();
		अन्यथा अगर (schedule_समयout_समाप्तable((HZ << scan) / 200))
			scan = LAST_SCAN;

		xas_set(&xas, 0);
		xas_lock_irq(&xas);
		xas_क्रम_each_marked(&xas, page, अच_दीर्घ_उच्च, MEMFD_TAG_PINNED) अणु
			bool clear = true;
			अगर (xa_is_value(page))
				जारी;
			page = find_subpage(page, xas.xa_index);
			अगर (page_count(page) - page_mapcount(page) != 1) अणु
				/*
				 * On the last scan, we clean up all those tags
				 * we inserted; but make a note that we still
				 * found pages pinned.
				 */
				अगर (scan == LAST_SCAN)
					error = -EBUSY;
				अन्यथा
					clear = false;
			पूर्ण
			अगर (clear)
				xas_clear_mark(&xas, MEMFD_TAG_PINNED);
			अगर (++tagged % XA_CHECK_SCHED)
				जारी;

			xas_छोड़ो(&xas);
			xas_unlock_irq(&xas);
			cond_resched();
			xas_lock_irq(&xas);
		पूर्ण
		xas_unlock_irq(&xas);
	पूर्ण

	वापस error;
पूर्ण

अटल अचिन्हित पूर्णांक *memfd_file_seals_ptr(काष्ठा file *file)
अणु
	अगर (shmem_file(file))
		वापस &SHMEM_I(file_inode(file))->seals;

#अगर_घोषित CONFIG_HUGETLBFS
	अगर (is_file_hugepages(file))
		वापस &HUGETLBFS_I(file_inode(file))->seals;
#पूर्ण_अगर

	वापस शून्य;
पूर्ण

#घोषणा F_ALL_SEALS (F_SEAL_SEAL | \
		     F_SEAL_SHRINK | \
		     F_SEAL_GROW | \
		     F_SEAL_WRITE | \
		     F_SEAL_FUTURE_WRITE)

अटल पूर्णांक memfd_add_seals(काष्ठा file *file, अचिन्हित पूर्णांक seals)
अणु
	काष्ठा inode *inode = file_inode(file);
	अचिन्हित पूर्णांक *file_seals;
	पूर्णांक error;

	/*
	 * SEALING
	 * Sealing allows multiple parties to share a पंचांगpfs or hugetlbfs file
	 * but restrict access to a specअगरic subset of file operations. Seals
	 * can only be added, but never हटाओd. This way, mutually untrusted
	 * parties can share common memory regions with a well-defined policy.
	 * A malicious peer can thus never perक्रमm unwanted operations on a
	 * shared object.
	 *
	 * Seals are only supported on special पंचांगpfs or hugetlbfs files and
	 * always affect the whole underlying inode. Once a seal is set, it
	 * may prevent some kinds of access to the file. Currently, the
	 * following seals are defined:
	 *   SEAL_SEAL: Prevent further seals from being set on this file
	 *   SEAL_SHRINK: Prevent the file from shrinking
	 *   SEAL_GROW: Prevent the file from growing
	 *   SEAL_WRITE: Prevent ग_लिखो access to the file
	 *
	 * As we करोn't require any trust relationship between two parties, we
	 * must prevent seals from being हटाओd. Thereक्रमe, sealing a file
	 * only adds a given set of seals to the file, it never touches
	 * existing seals. Furthermore, the "setting seals"-operation can be
	 * sealed itself, which basically prevents any further seal from being
	 * added.
	 *
	 * Semantics of sealing are only defined on अस्थिर files. Only
	 * anonymous पंचांगpfs and hugetlbfs files support sealing. More
	 * importantly, seals are never written to disk. Thereक्रमe, there's
	 * no plan to support it on other file types.
	 */

	अगर (!(file->f_mode & FMODE_WRITE))
		वापस -EPERM;
	अगर (seals & ~(अचिन्हित पूर्णांक)F_ALL_SEALS)
		वापस -EINVAL;

	inode_lock(inode);

	file_seals = memfd_file_seals_ptr(file);
	अगर (!file_seals) अणु
		error = -EINVAL;
		जाओ unlock;
	पूर्ण

	अगर (*file_seals & F_SEAL_SEAL) अणु
		error = -EPERM;
		जाओ unlock;
	पूर्ण

	अगर ((seals & F_SEAL_WRITE) && !(*file_seals & F_SEAL_WRITE)) अणु
		error = mapping_deny_writable(file->f_mapping);
		अगर (error)
			जाओ unlock;

		error = memfd_रुको_क्रम_pins(file->f_mapping);
		अगर (error) अणु
			mapping_allow_writable(file->f_mapping);
			जाओ unlock;
		पूर्ण
	पूर्ण

	*file_seals |= seals;
	error = 0;

unlock:
	inode_unlock(inode);
	वापस error;
पूर्ण

अटल पूर्णांक memfd_get_seals(काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक *seals = memfd_file_seals_ptr(file);

	वापस seals ? *seals : -EINVAL;
पूर्ण

दीर्घ memfd_fcntl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ error;

	चयन (cmd) अणु
	हाल F_ADD_SEALS:
		/* disallow upper 32bit */
		अगर (arg > अच_पूर्णांक_उच्च)
			वापस -EINVAL;

		error = memfd_add_seals(file, arg);
		अवरोध;
	हाल F_GET_SEALS:
		error = memfd_get_seals(file);
		अवरोध;
	शेष:
		error = -EINVAL;
		अवरोध;
	पूर्ण

	वापस error;
पूर्ण

#घोषणा MFD_NAME_PREFIX "memfd:"
#घोषणा MFD_NAME_PREFIX_LEN (माप(MFD_NAME_PREFIX) - 1)
#घोषणा MFD_NAME_MAX_LEN (NAME_MAX - MFD_NAME_PREFIX_LEN)

#घोषणा MFD_ALL_FLAGS (MFD_CLOEXEC | MFD_ALLOW_SEALING | MFD_HUGETLB)

SYSCALL_DEFINE2(memfd_create,
		स्थिर अक्षर __user *, uname,
		अचिन्हित पूर्णांक, flags)
अणु
	अचिन्हित पूर्णांक *file_seals;
	काष्ठा file *file;
	पूर्णांक fd, error;
	अक्षर *name;
	दीर्घ len;

	अगर (!(flags & MFD_HUGETLB)) अणु
		अगर (flags & ~(अचिन्हित पूर्णांक)MFD_ALL_FLAGS)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Allow huge page size encoding in flags. */
		अगर (flags & ~(अचिन्हित पूर्णांक)(MFD_ALL_FLAGS |
				(MFD_HUGE_MASK << MFD_HUGE_SHIFT)))
			वापस -EINVAL;
	पूर्ण

	/* length includes terminating zero */
	len = strnlen_user(uname, MFD_NAME_MAX_LEN + 1);
	अगर (len <= 0)
		वापस -EFAULT;
	अगर (len > MFD_NAME_MAX_LEN + 1)
		वापस -EINVAL;

	name = kदो_स्मृति(len + MFD_NAME_PREFIX_LEN, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;

	म_नकल(name, MFD_NAME_PREFIX);
	अगर (copy_from_user(&name[MFD_NAME_PREFIX_LEN], uname, len)) अणु
		error = -EFAULT;
		जाओ err_name;
	पूर्ण

	/* terminating-zero may have changed after strnlen_user() वापसed */
	अगर (name[len + MFD_NAME_PREFIX_LEN - 1]) अणु
		error = -EFAULT;
		जाओ err_name;
	पूर्ण

	fd = get_unused_fd_flags((flags & MFD_CLOEXEC) ? O_CLOEXEC : 0);
	अगर (fd < 0) अणु
		error = fd;
		जाओ err_name;
	पूर्ण

	अगर (flags & MFD_HUGETLB) अणु
		काष्ठा user_काष्ठा *user = शून्य;

		file = hugetlb_file_setup(name, 0, VM_NORESERVE, &user,
					HUGETLB_ANONHUGE_INODE,
					(flags >> MFD_HUGE_SHIFT) &
					MFD_HUGE_MASK);
	पूर्ण अन्यथा
		file = shmem_file_setup(name, 0, VM_NORESERVE);
	अगर (IS_ERR(file)) अणु
		error = PTR_ERR(file);
		जाओ err_fd;
	पूर्ण
	file->f_mode |= FMODE_LSEEK | FMODE_PREAD | FMODE_PWRITE;
	file->f_flags |= O_LARGEखाता;

	अगर (flags & MFD_ALLOW_SEALING) अणु
		file_seals = memfd_file_seals_ptr(file);
		*file_seals &= ~F_SEAL_SEAL;
	पूर्ण

	fd_install(fd, file);
	kमुक्त(name);
	वापस fd;

err_fd:
	put_unused_fd(fd);
err_name:
	kमुक्त(name);
	वापस error;
पूर्ण
