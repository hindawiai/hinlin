<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Red Hat, Inc.
 */

#समावेश "fuse_i.h"

#समावेश <linux/uपन.स>
#समावेश <linux/compat.h>
#समावेश <linux/fileattr.h>

/*
 * CUSE servers compiled on 32bit broke on 64bit kernels because the
 * ABI was defined to be 'struct iovec' which is dअगरferent on 32bit
 * and 64bit.  Fortunately we can determine which काष्ठाure the server
 * used from the size of the reply.
 */
अटल पूर्णांक fuse_copy_ioctl_iovec_old(काष्ठा iovec *dst, व्योम *src,
				     माप_प्रकार transferred, अचिन्हित count,
				     bool is_compat)
अणु
#अगर_घोषित CONFIG_COMPAT
	अगर (count * माप(काष्ठा compat_iovec) == transferred) अणु
		काष्ठा compat_iovec *ciov = src;
		अचिन्हित i;

		/*
		 * With this पूर्णांकerface a 32bit server cannot support
		 * non-compat (i.e. ones coming from 64bit apps) ioctl
		 * requests
		 */
		अगर (!is_compat)
			वापस -EINVAL;

		क्रम (i = 0; i < count; i++) अणु
			dst[i].iov_base = compat_ptr(ciov[i].iov_base);
			dst[i].iov_len = ciov[i].iov_len;
		पूर्ण
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	अगर (count * माप(काष्ठा iovec) != transferred)
		वापस -EIO;

	स_नकल(dst, src, transferred);
	वापस 0;
पूर्ण

/* Make sure iov_length() won't overflow */
अटल पूर्णांक fuse_verअगरy_ioctl_iov(काष्ठा fuse_conn *fc, काष्ठा iovec *iov,
				 माप_प्रकार count)
अणु
	माप_प्रकार n;
	u32 max = fc->max_pages << PAGE_SHIFT;

	क्रम (n = 0; n < count; n++, iov++) अणु
		अगर (iov->iov_len > (माप_प्रकार) max)
			वापस -ENOMEM;
		max -= iov->iov_len;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fuse_copy_ioctl_iovec(काष्ठा fuse_conn *fc, काष्ठा iovec *dst,
				 व्योम *src, माप_प्रकार transferred, अचिन्हित count,
				 bool is_compat)
अणु
	अचिन्हित i;
	काष्ठा fuse_ioctl_iovec *fiov = src;

	अगर (fc->minor < 16) अणु
		वापस fuse_copy_ioctl_iovec_old(dst, src, transferred,
						 count, is_compat);
	पूर्ण

	अगर (count * माप(काष्ठा fuse_ioctl_iovec) != transferred)
		वापस -EIO;

	क्रम (i = 0; i < count; i++) अणु
		/* Did the server supply an inappropriate value? */
		अगर (fiov[i].base != (अचिन्हित दीर्घ) fiov[i].base ||
		    fiov[i].len != (अचिन्हित दीर्घ) fiov[i].len)
			वापस -EIO;

		dst[i].iov_base = (व्योम __user *) (अचिन्हित दीर्घ) fiov[i].base;
		dst[i].iov_len = (माप_प्रकार) fiov[i].len;

#अगर_घोषित CONFIG_COMPAT
		अगर (is_compat &&
		    (ptr_to_compat(dst[i].iov_base) != fiov[i].base ||
		     (compat_माप_प्रकार) dst[i].iov_len != fiov[i].len))
			वापस -EIO;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण


/*
 * For ioctls, there is no generic way to determine how much memory
 * needs to be पढ़ो and/or written.  Furthermore, ioctls are allowed
 * to dereference the passed poपूर्णांकer, so the parameter requires deep
 * copying but FUSE has no idea whatsoever about what to copy in or
 * out.
 *
 * This is solved by allowing FUSE server to retry ioctl with
 * necessary in/out iovecs.  Let's assume the ioctl implementation
 * needs to पढ़ो in the following काष्ठाure.
 *
 * काष्ठा a अणु
 *	अक्षर	*buf;
 *	माप_प्रकार	buflen;
 * पूर्ण
 *
 * On the first callout to FUSE server, inarg->in_size and
 * inarg->out_size will be शून्य; then, the server completes the ioctl
 * with FUSE_IOCTL_RETRY set in out->flags, out->in_iovs set to 1 and
 * the actual iov array to
 *
 * अणु अणु .iov_base = inarg.arg,	.iov_len = माप(काष्ठा a) पूर्ण पूर्ण
 *
 * which tells FUSE to copy in the requested area and retry the ioctl.
 * On the second round, the server has access to the काष्ठाure and
 * from that it can tell what to look क्रम next, so on the invocation,
 * it sets FUSE_IOCTL_RETRY, out->in_iovs to 2 and iov array to
 *
 * अणु अणु .iov_base = inarg.arg,	.iov_len = माप(काष्ठा a)	पूर्ण,
 *   अणु .iov_base = a.buf,	.iov_len = a.buflen		पूर्ण पूर्ण
 *
 * FUSE will copy both काष्ठा a and the poपूर्णांकed buffer from the
 * process करोing the ioctl and retry ioctl with both काष्ठा a and the
 * buffer.
 *
 * This समय, FUSE server has everything it needs and completes ioctl
 * without FUSE_IOCTL_RETRY which finishes the ioctl call.
 *
 * Copying data out works the same way.
 *
 * Note that अगर FUSE_IOCTL_UNRESTRICTED is clear, the kernel
 * स्वतःmatically initializes in and out iovs by decoding @cmd with
 * _IOC_* macros and the server is not allowed to request RETRY.  This
 * limits ioctl data transfers to well-क्रमmed ioctls and is the क्रमced
 * behavior क्रम all FUSE servers.
 */
दीर्घ fuse_करो_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
		   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fuse_file *ff = file->निजी_data;
	काष्ठा fuse_mount *fm = ff->fm;
	काष्ठा fuse_ioctl_in inarg = अणु
		.fh = ff->fh,
		.cmd = cmd,
		.arg = arg,
		.flags = flags
	पूर्ण;
	काष्ठा fuse_ioctl_out outarg;
	काष्ठा iovec *iov_page = शून्य;
	काष्ठा iovec *in_iov = शून्य, *out_iov = शून्य;
	अचिन्हित पूर्णांक in_iovs = 0, out_iovs = 0, max_pages;
	माप_प्रकार in_size, out_size, c;
	sमाप_प्रकार transferred;
	पूर्णांक err, i;
	काष्ठा iov_iter ii;
	काष्ठा fuse_args_pages ap = अणुपूर्ण;

#अगर BITS_PER_LONG == 32
	inarg.flags |= FUSE_IOCTL_32BIT;
#अन्यथा
	अगर (flags & FUSE_IOCTL_COMPAT) अणु
		inarg.flags |= FUSE_IOCTL_32BIT;
#अगर_घोषित CONFIG_X86_X32
		अगर (in_x32_syscall())
			inarg.flags |= FUSE_IOCTL_COMPAT_X32;
#पूर्ण_अगर
	पूर्ण
#पूर्ण_अगर

	/* assume all the iovs वापसed by client always fits in a page */
	BUILD_BUG_ON(माप(काष्ठा fuse_ioctl_iovec) * FUSE_IOCTL_MAX_IOV > PAGE_SIZE);

	err = -ENOMEM;
	ap.pages = fuse_pages_alloc(fm->fc->max_pages, GFP_KERNEL, &ap.descs);
	iov_page = (काष्ठा iovec *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!ap.pages || !iov_page)
		जाओ out;

	fuse_page_descs_length_init(ap.descs, 0, fm->fc->max_pages);

	/*
	 * If restricted, initialize IO parameters as encoded in @cmd.
	 * RETRY from server is not allowed.
	 */
	अगर (!(flags & FUSE_IOCTL_UNRESTRICTED)) अणु
		काष्ठा iovec *iov = iov_page;

		iov->iov_base = (व्योम __user *)arg;
		iov->iov_len = _IOC_SIZE(cmd);

		अगर (_IOC_सूची(cmd) & _IOC_WRITE) अणु
			in_iov = iov;
			in_iovs = 1;
		पूर्ण

		अगर (_IOC_सूची(cmd) & _IOC_READ) अणु
			out_iov = iov;
			out_iovs = 1;
		पूर्ण
	पूर्ण

 retry:
	inarg.in_size = in_size = iov_length(in_iov, in_iovs);
	inarg.out_size = out_size = iov_length(out_iov, out_iovs);

	/*
	 * Out data can be used either क्रम actual out data or iovs,
	 * make sure there always is at least one page.
	 */
	out_size = max_t(माप_प्रकार, out_size, PAGE_SIZE);
	max_pages = DIV_ROUND_UP(max(in_size, out_size), PAGE_SIZE);

	/* make sure there are enough buffer pages and init request with them */
	err = -ENOMEM;
	अगर (max_pages > fm->fc->max_pages)
		जाओ out;
	जबतक (ap.num_pages < max_pages) अणु
		ap.pages[ap.num_pages] = alloc_page(GFP_KERNEL | __GFP_HIGHMEM);
		अगर (!ap.pages[ap.num_pages])
			जाओ out;
		ap.num_pages++;
	पूर्ण


	/* okay, let's send it to the client */
	ap.args.opcode = FUSE_IOCTL;
	ap.args.nodeid = ff->nodeid;
	ap.args.in_numargs = 1;
	ap.args.in_args[0].size = माप(inarg);
	ap.args.in_args[0].value = &inarg;
	अगर (in_size) अणु
		ap.args.in_numargs++;
		ap.args.in_args[1].size = in_size;
		ap.args.in_pages = true;

		err = -EFAULT;
		iov_iter_init(&ii, WRITE, in_iov, in_iovs, in_size);
		क्रम (i = 0; iov_iter_count(&ii) && !WARN_ON(i >= ap.num_pages); i++) अणु
			c = copy_page_from_iter(ap.pages[i], 0, PAGE_SIZE, &ii);
			अगर (c != PAGE_SIZE && iov_iter_count(&ii))
				जाओ out;
		पूर्ण
	पूर्ण

	ap.args.out_numargs = 2;
	ap.args.out_args[0].size = माप(outarg);
	ap.args.out_args[0].value = &outarg;
	ap.args.out_args[1].size = out_size;
	ap.args.out_pages = true;
	ap.args.out_argvar = true;

	transferred = fuse_simple_request(fm, &ap.args);
	err = transferred;
	अगर (transferred < 0)
		जाओ out;

	/* did it ask क्रम retry? */
	अगर (outarg.flags & FUSE_IOCTL_RETRY) अणु
		व्योम *vaddr;

		/* no retry अगर in restricted mode */
		err = -EIO;
		अगर (!(flags & FUSE_IOCTL_UNRESTRICTED))
			जाओ out;

		in_iovs = outarg.in_iovs;
		out_iovs = outarg.out_iovs;

		/*
		 * Make sure things are in boundary, separate checks
		 * are to protect against overflow.
		 */
		err = -ENOMEM;
		अगर (in_iovs > FUSE_IOCTL_MAX_IOV ||
		    out_iovs > FUSE_IOCTL_MAX_IOV ||
		    in_iovs + out_iovs > FUSE_IOCTL_MAX_IOV)
			जाओ out;

		vaddr = kmap_atomic(ap.pages[0]);
		err = fuse_copy_ioctl_iovec(fm->fc, iov_page, vaddr,
					    transferred, in_iovs + out_iovs,
					    (flags & FUSE_IOCTL_COMPAT) != 0);
		kunmap_atomic(vaddr);
		अगर (err)
			जाओ out;

		in_iov = iov_page;
		out_iov = in_iov + in_iovs;

		err = fuse_verअगरy_ioctl_iov(fm->fc, in_iov, in_iovs);
		अगर (err)
			जाओ out;

		err = fuse_verअगरy_ioctl_iov(fm->fc, out_iov, out_iovs);
		अगर (err)
			जाओ out;

		जाओ retry;
	पूर्ण

	err = -EIO;
	अगर (transferred > inarg.out_size)
		जाओ out;

	err = -EFAULT;
	iov_iter_init(&ii, READ, out_iov, out_iovs, transferred);
	क्रम (i = 0; iov_iter_count(&ii) && !WARN_ON(i >= ap.num_pages); i++) अणु
		c = copy_page_to_iter(ap.pages[i], 0, PAGE_SIZE, &ii);
		अगर (c != PAGE_SIZE && iov_iter_count(&ii))
			जाओ out;
	पूर्ण
	err = 0;
 out:
	मुक्त_page((अचिन्हित दीर्घ) iov_page);
	जबतक (ap.num_pages)
		__मुक्त_page(ap.pages[--ap.num_pages]);
	kमुक्त(ap.pages);

	वापस err ? err : outarg.result;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_करो_ioctl);

दीर्घ fuse_ioctl_common(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		       अचिन्हित दीर्घ arg, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);

	अगर (!fuse_allow_current_process(fc))
		वापस -EACCES;

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	वापस fuse_करो_ioctl(file, cmd, arg, flags);
पूर्ण

दीर्घ fuse_file_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस fuse_ioctl_common(file, cmd, arg, 0);
पूर्ण

दीर्घ fuse_file_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	वापस fuse_ioctl_common(file, cmd, arg, FUSE_IOCTL_COMPAT);
पूर्ण

अटल पूर्णांक fuse_priv_ioctl(काष्ठा inode *inode, काष्ठा fuse_file *ff,
			   अचिन्हित पूर्णांक cmd, व्योम *ptr, माप_प्रकार size)
अणु
	काष्ठा fuse_mount *fm = ff->fm;
	काष्ठा fuse_ioctl_in inarg;
	काष्ठा fuse_ioctl_out outarg;
	FUSE_ARGS(args);
	पूर्णांक err;

	स_रखो(&inarg, 0, माप(inarg));
	inarg.fh = ff->fh;
	inarg.cmd = cmd;

#अगर BITS_PER_LONG == 32
	inarg.flags |= FUSE_IOCTL_32BIT;
#पूर्ण_अगर
	अगर (S_ISसूची(inode->i_mode))
		inarg.flags |= FUSE_IOCTL_सूची;

	अगर (_IOC_सूची(cmd) & _IOC_READ)
		inarg.out_size = size;
	अगर (_IOC_सूची(cmd) & _IOC_WRITE)
		inarg.in_size = size;

	args.opcode = FUSE_IOCTL;
	args.nodeid = ff->nodeid;
	args.in_numargs = 2;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.in_args[1].size = inarg.in_size;
	args.in_args[1].value = ptr;
	args.out_numargs = 2;
	args.out_args[0].size = माप(outarg);
	args.out_args[0].value = &outarg;
	args.out_args[1].size = inarg.out_size;
	args.out_args[1].value = ptr;

	err = fuse_simple_request(fm, &args);
	अगर (!err && outarg.flags & FUSE_IOCTL_RETRY)
		err = -EIO;

	वापस err;
पूर्ण

अटल काष्ठा fuse_file *fuse_priv_ioctl_prepare(काष्ठा inode *inode)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	bool isdir = S_ISसूची(inode->i_mode);

	अगर (!S_ISREG(inode->i_mode) && !isdir)
		वापस ERR_PTR(-ENOTTY);

	वापस fuse_file_खोलो(fm, get_node_id(inode), O_RDONLY, isdir);
पूर्ण

अटल व्योम fuse_priv_ioctl_cleanup(काष्ठा inode *inode, काष्ठा fuse_file *ff)
अणु
	fuse_file_release(inode, ff, O_RDONLY, शून्य, S_ISसूची(inode->i_mode));
पूर्ण

पूर्णांक fuse_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा fuse_file *ff;
	अचिन्हित पूर्णांक flags;
	काष्ठा fsxattr xfa;
	पूर्णांक err;

	ff = fuse_priv_ioctl_prepare(inode);
	अगर (IS_ERR(ff))
		वापस PTR_ERR(ff);

	अगर (fa->flags_valid) अणु
		err = fuse_priv_ioctl(inode, ff, FS_IOC_GETFLAGS,
				      &flags, माप(flags));
		अगर (err)
			जाओ cleanup;

		fileattr_fill_flags(fa, flags);
	पूर्ण अन्यथा अणु
		err = fuse_priv_ioctl(inode, ff, FS_IOC_FSGETXATTR,
				      &xfa, माप(xfa));
		अगर (err)
			जाओ cleanup;

		fileattr_fill_xflags(fa, xfa.fsx_xflags);
		fa->fsx_extsize = xfa.fsx_extsize;
		fa->fsx_nextents = xfa.fsx_nextents;
		fa->fsx_projid = xfa.fsx_projid;
		fa->fsx_cowextsize = xfa.fsx_cowextsize;
	पूर्ण
cleanup:
	fuse_priv_ioctl_cleanup(inode, ff);

	वापस err;
पूर्ण

पूर्णांक fuse_fileattr_set(काष्ठा user_namespace *mnt_userns,
		      काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा fuse_file *ff;
	अचिन्हित पूर्णांक flags = fa->flags;
	काष्ठा fsxattr xfa;
	पूर्णांक err;

	ff = fuse_priv_ioctl_prepare(inode);
	अगर (IS_ERR(ff))
		वापस PTR_ERR(ff);

	अगर (fa->flags_valid) अणु
		err = fuse_priv_ioctl(inode, ff, FS_IOC_SETFLAGS,
				      &flags, माप(flags));
		अगर (err)
			जाओ cleanup;
	पूर्ण अन्यथा अणु
		स_रखो(&xfa, 0, माप(xfa));
		xfa.fsx_xflags = fa->fsx_xflags;
		xfa.fsx_extsize = fa->fsx_extsize;
		xfa.fsx_nextents = fa->fsx_nextents;
		xfa.fsx_projid = fa->fsx_projid;
		xfa.fsx_cowextsize = fa->fsx_cowextsize;

		err = fuse_priv_ioctl(inode, ff, FS_IOC_FSSETXATTR,
				      &xfa, माप(xfa));
	पूर्ण

cleanup:
	fuse_priv_ioctl_cleanup(inode, ff);

	वापस err;
पूर्ण
