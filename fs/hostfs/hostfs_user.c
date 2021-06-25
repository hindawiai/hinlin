<शैली गुरु>
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */

#समावेश <मानकपन.स>
#समावेश <मानकघोष.स>
#समावेश <unistd.h>
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/vfs.h>
#समावेश <sys/syscall.h>
#समावेश "hostfs.h"
#समावेश <uसमय.स>

अटल व्योम stat64_to_hostfs(स्थिर काष्ठा stat64 *buf, काष्ठा hostfs_stat *p)
अणु
	p->ino = buf->st_ino;
	p->mode = buf->st_mode;
	p->nlink = buf->st_nlink;
	p->uid = buf->st_uid;
	p->gid = buf->st_gid;
	p->size = buf->st_size;
	p->aसमय.tv_sec = buf->st_aसमय;
	p->aसमय.tv_nsec = 0;
	p->स_समय.tv_sec = buf->st_स_समय;
	p->स_समय.tv_nsec = 0;
	p->mसमय.tv_sec = buf->st_mसमय;
	p->mसमय.tv_nsec = 0;
	p->blksize = buf->st_blksize;
	p->blocks = buf->st_blocks;
	p->maj = os_major(buf->st_rdev);
	p->min = os_minor(buf->st_rdev);
पूर्ण

पूर्णांक stat_file(स्थिर अक्षर *path, काष्ठा hostfs_stat *p, पूर्णांक fd)
अणु
	काष्ठा stat64 buf;

	अगर (fd >= 0) अणु
		अगर (ख_स्थिति64(fd, &buf) < 0)
			वापस -त्रुटि_सं;
	पूर्ण अन्यथा अगर (lstat64(path, &buf) < 0) अणु
		वापस -त्रुटि_सं;
	पूर्ण
	stat64_to_hostfs(&buf, p);
	वापस 0;
पूर्ण

पूर्णांक access_file(अक्षर *path, पूर्णांक r, पूर्णांक w, पूर्णांक x)
अणु
	पूर्णांक mode = 0;

	अगर (r)
		mode = R_OK;
	अगर (w)
		mode |= W_OK;
	अगर (x)
		mode |= X_OK;
	अगर (access(path, mode) != 0)
		वापस -त्रुटि_सं;
	अन्यथा वापस 0;
पूर्ण

पूर्णांक खोलो_file(अक्षर *path, पूर्णांक r, पूर्णांक w, पूर्णांक append)
अणु
	पूर्णांक mode = 0, fd;

	अगर (r && !w)
		mode = O_RDONLY;
	अन्यथा अगर (!r && w)
		mode = O_WRONLY;
	अन्यथा अगर (r && w)
		mode = O_RDWR;
	अन्यथा panic("Impossible mode in open_file");

	अगर (append)
		mode |= O_APPEND;
	fd = खोलो64(path, mode);
	अगर (fd < 0)
		वापस -त्रुटि_सं;
	अन्यथा वापस fd;
पूर्ण

व्योम *खोलो_dir(अक्षर *path, पूर्णांक *err_out)
अणु
	सूची *dir;

	dir = सूची_खोलो(path);
	*err_out = त्रुटि_सं;

	वापस dir;
पूर्ण

व्योम seek_dir(व्योम *stream, अचिन्हित दीर्घ दीर्घ pos)
अणु
	सूची *dir = stream;

	seekdir(dir, pos);
पूर्ण

अक्षर *पढ़ो_dir(व्योम *stream, अचिन्हित दीर्घ दीर्घ *pos_out,
	       अचिन्हित दीर्घ दीर्घ *ino_out, पूर्णांक *len_out,
	       अचिन्हित पूर्णांक *type_out)
अणु
	सूची *dir = stream;
	काष्ठा dirent *ent;

	ent = सूची_पढ़ो(dir);
	अगर (ent == शून्य)
		वापस शून्य;
	*len_out = म_माप(ent->d_name);
	*ino_out = ent->d_ino;
	*type_out = ent->d_type;
	*pos_out = ent->d_off;
	वापस ent->d_name;
पूर्ण

पूर्णांक पढ़ो_file(पूर्णांक fd, अचिन्हित दीर्घ दीर्घ *offset, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक n;

	n = pपढ़ो64(fd, buf, len, *offset);
	अगर (n < 0)
		वापस -त्रुटि_सं;
	*offset += n;
	वापस n;
पूर्ण

पूर्णांक ग_लिखो_file(पूर्णांक fd, अचिन्हित दीर्घ दीर्घ *offset, स्थिर अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक n;

	n = pग_लिखो64(fd, buf, len, *offset);
	अगर (n < 0)
		वापस -त्रुटि_सं;
	*offset += n;
	वापस n;
पूर्ण

पूर्णांक lseek_file(पूर्णांक fd, दीर्घ दीर्घ offset, पूर्णांक whence)
अणु
	पूर्णांक ret;

	ret = lseek64(fd, offset, whence);
	अगर (ret < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक fsync_file(पूर्णांक fd, पूर्णांक datasync)
अणु
	पूर्णांक ret;
	अगर (datasync)
		ret = fdatasync(fd);
	अन्यथा
		ret = fsync(fd);

	अगर (ret < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक replace_file(पूर्णांक oldfd, पूर्णांक fd)
अणु
	वापस dup2(oldfd, fd);
पूर्ण

व्योम बंद_file(व्योम *stream)
अणु
	बंद(*((पूर्णांक *) stream));
पूर्ण

व्योम बंद_dir(व्योम *stream)
अणु
	बंद_सूची(stream);
पूर्ण

पूर्णांक file_create(अक्षर *name, पूर्णांक mode)
अणु
	पूर्णांक fd;

	fd = खोलो64(name, O_CREAT | O_RDWR, mode);
	अगर (fd < 0)
		वापस -त्रुटि_सं;
	वापस fd;
पूर्ण

पूर्णांक set_attr(स्थिर अक्षर *file, काष्ठा hostfs_iattr *attrs, पूर्णांक fd)
अणु
	काष्ठा hostfs_stat st;
	काष्ठा समयval बार[2];
	पूर्णांक err, ma;

	अगर (attrs->ia_valid & HOSTFS_ATTR_MODE) अणु
		अगर (fd >= 0) अणु
			अगर (fchmod(fd, attrs->ia_mode) != 0)
				वापस -त्रुटि_सं;
		पूर्ण अन्यथा अगर (chmod(file, attrs->ia_mode) != 0) अणु
			वापस -त्रुटि_सं;
		पूर्ण
	पूर्ण
	अगर (attrs->ia_valid & HOSTFS_ATTR_UID) अणु
		अगर (fd >= 0) अणु
			अगर (fchown(fd, attrs->ia_uid, -1))
				वापस -त्रुटि_सं;
		पूर्ण अन्यथा अगर (chown(file, attrs->ia_uid, -1)) अणु
			वापस -त्रुटि_सं;
		पूर्ण
	पूर्ण
	अगर (attrs->ia_valid & HOSTFS_ATTR_GID) अणु
		अगर (fd >= 0) अणु
			अगर (fchown(fd, -1, attrs->ia_gid))
				वापस -त्रुटि_सं;
		पूर्ण अन्यथा अगर (chown(file, -1, attrs->ia_gid)) अणु
			वापस -त्रुटि_सं;
		पूर्ण
	पूर्ण
	अगर (attrs->ia_valid & HOSTFS_ATTR_SIZE) अणु
		अगर (fd >= 0) अणु
			अगर (ftruncate(fd, attrs->ia_size))
				वापस -त्रुटि_सं;
		पूर्ण अन्यथा अगर (truncate(file, attrs->ia_size)) अणु
			वापस -त्रुटि_सं;
		पूर्ण
	पूर्ण

	/*
	 * Update accessed and/or modअगरied समय, in two parts: first set
	 * बार according to the changes to perक्रमm, and then call fuबार()
	 * or uबार() to apply them.
	 */
	ma = (HOSTFS_ATTR_ATIME_SET | HOSTFS_ATTR_MTIME_SET);
	अगर (attrs->ia_valid & ma) अणु
		err = stat_file(file, &st, fd);
		अगर (err != 0)
			वापस err;

		बार[0].tv_sec = st.aसमय.tv_sec;
		बार[0].tv_usec = st.aसमय.tv_nsec / 1000;
		बार[1].tv_sec = st.mसमय.tv_sec;
		बार[1].tv_usec = st.mसमय.tv_nsec / 1000;

		अगर (attrs->ia_valid & HOSTFS_ATTR_ATIME_SET) अणु
			बार[0].tv_sec = attrs->ia_aसमय.tv_sec;
			बार[0].tv_usec = attrs->ia_aसमय.tv_nsec / 1000;
		पूर्ण
		अगर (attrs->ia_valid & HOSTFS_ATTR_MTIME_SET) अणु
			बार[1].tv_sec = attrs->ia_mसमय.tv_sec;
			बार[1].tv_usec = attrs->ia_mसमय.tv_nsec / 1000;
		पूर्ण

		अगर (fd >= 0) अणु
			अगर (fuबार(fd, बार) != 0)
				वापस -त्रुटि_सं;
		पूर्ण अन्यथा अगर (uबार(file, बार) != 0) अणु
			वापस -त्रुटि_सं;
		पूर्ण
	पूर्ण

	/* Note: स_समय is not handled */
	अगर (attrs->ia_valid & (HOSTFS_ATTR_ATIME | HOSTFS_ATTR_MTIME)) अणु
		err = stat_file(file, &st, fd);
		attrs->ia_aसमय = st.aसमय;
		attrs->ia_mसमय = st.mसमय;
		अगर (err != 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक make_symlink(स्थिर अक्षर *from, स्थिर अक्षर *to)
अणु
	पूर्णांक err;

	err = symlink(to, from);
	अगर (err)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक unlink_file(स्थिर अक्षर *file)
अणु
	पूर्णांक err;

	err = unlink(file);
	अगर (err)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक करो_सूची_गढ़ो(स्थिर अक्षर *file, पूर्णांक mode)
अणु
	पूर्णांक err;

	err = सूची_गढ़ो(file, mode);
	अगर (err)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक hostfs_करो_सूची_हटाओ(स्थिर अक्षर *file)
अणु
	पूर्णांक err;

	err = सूची_हटाओ(file);
	अगर (err)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक करो_mknod(स्थिर अक्षर *file, पूर्णांक mode, अचिन्हित पूर्णांक major, अचिन्हित पूर्णांक minor)
अणु
	पूर्णांक err;

	err = mknod(file, mode, os_makedev(major, minor));
	अगर (err)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक link_file(स्थिर अक्षर *to, स्थिर अक्षर *from)
अणु
	पूर्णांक err;

	err = link(to, from);
	अगर (err)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक hostfs_करो_पढ़ोlink(अक्षर *file, अक्षर *buf, पूर्णांक size)
अणु
	पूर्णांक n;

	n = पढ़ोlink(file, buf, size);
	अगर (n < 0)
		वापस -त्रुटि_सं;
	अगर (n < size)
		buf[n] = '\0';
	वापस n;
पूर्ण

पूर्णांक नाम_file(अक्षर *from, अक्षर *to)
अणु
	पूर्णांक err;

	err = नाम(from, to);
	अगर (err < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक नाम2_file(अक्षर *from, अक्षर *to, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;

#अगर_अघोषित SYS_नामat2
#  अगरdef __x86_64__
#    define SYS_नामat2 316
#  endअगर
#  अगरdef __i386__
#    define SYS_नामat2 353
#  endअगर
#पूर्ण_अगर

#अगर_घोषित SYS_नामat2
	err = syscall(SYS_नामat2, AT_FDCWD, from, AT_FDCWD, to, flags);
	अगर (err < 0) अणु
		अगर (त्रुटि_सं != ENOSYS)
			वापस -त्रुटि_सं;
		अन्यथा
			वापस -EINVAL;
	पूर्ण
	वापस 0;
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

पूर्णांक करो_statfs(अक्षर *root, दीर्घ *bsize_out, दीर्घ दीर्घ *blocks_out,
	      दीर्घ दीर्घ *bमुक्त_out, दीर्घ दीर्घ *bavail_out,
	      दीर्घ दीर्घ *files_out, दीर्घ दीर्घ *fमुक्त_out,
	      व्योम *fsid_out, पूर्णांक fsid_size, दीर्घ *namelen_out)
अणु
	काष्ठा statfs64 buf;
	पूर्णांक err;

	err = statfs64(root, &buf);
	अगर (err < 0)
		वापस -त्रुटि_सं;

	*bsize_out = buf.f_bsize;
	*blocks_out = buf.f_blocks;
	*bमुक्त_out = buf.f_bमुक्त;
	*bavail_out = buf.f_bavail;
	*files_out = buf.f_files;
	*fमुक्त_out = buf.f_fमुक्त;
	स_नकल(fsid_out, &buf.f_fsid,
	       माप(buf.f_fsid) > fsid_size ? fsid_size :
	       माप(buf.f_fsid));
	*namelen_out = buf.f_namelen;

	वापस 0;
पूर्ण
