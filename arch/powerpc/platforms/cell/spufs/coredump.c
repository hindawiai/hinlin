<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SPU core dump code
 *
 * (C) Copyright 2006 IBM Corp.
 *
 * Author: Dwayne Grant McConnell <decimal@us.ibm.com>
 */

#समावेश <linux/elf.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/fs.h>
#समावेश <linux/gfp.h>
#समावेश <linux/list.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/coredump.h>
#समावेश <linux/binfmts.h>

#समावेश <linux/uaccess.h>

#समावेश "spufs.h"

अटल पूर्णांक spufs_ctx_note_size(काष्ठा spu_context *ctx, पूर्णांक dfd)
अणु
	पूर्णांक i, sz, total = 0;
	अक्षर *name;
	अक्षर fullname[80];

	क्रम (i = 0; spufs_coredump_पढ़ो[i].name != शून्य; i++) अणु
		name = spufs_coredump_पढ़ो[i].name;
		sz = spufs_coredump_पढ़ो[i].size;

		प्र_लिखो(fullname, "SPU/%d/%s", dfd, name);

		total += माप(काष्ठा elf_note);
		total += roundup(म_माप(fullname) + 1, 4);
		total += roundup(sz, 4);
	पूर्ण

	वापस total;
पूर्ण

अटल पूर्णांक match_context(स्थिर व्योम *v, काष्ठा file *file, अचिन्हित fd)
अणु
	काष्ठा spu_context *ctx;
	अगर (file->f_op != &spufs_context_fops)
		वापस 0;
	ctx = SPUFS_I(file_inode(file))->i_ctx;
	अगर (ctx->flags & SPU_CREATE_NOSCHED)
		वापस 0;
	वापस fd + 1;
पूर्ण

/*
 * The additional architecture-specअगरic notes क्रम Cell are various
 * context files in the spu context.
 *
 * This function iterates over all खोलो file descriptors and sees
 * अगर they are a directory in spufs.  In that हाल we use spufs
 * पूर्णांकernal functionality to dump them without needing to actually
 * खोलो the files.
 */
/*
 * descriptor table is not shared, so files can't change or go away.
 */
अटल काष्ठा spu_context *coredump_next_context(पूर्णांक *fd)
अणु
	काष्ठा spu_context *ctx;
	काष्ठा file *file;
	पूर्णांक n = iterate_fd(current->files, *fd, match_context, शून्य);
	अगर (!n)
		वापस शून्य;
	*fd = n - 1;

	rcu_पढ़ो_lock();
	file = lookup_fd_rcu(*fd);
	ctx = SPUFS_I(file_inode(file))->i_ctx;
	get_spu_context(ctx);
	rcu_पढ़ो_unlock();

	वापस ctx;
पूर्ण

पूर्णांक spufs_coredump_extra_notes_size(व्योम)
अणु
	काष्ठा spu_context *ctx;
	पूर्णांक size = 0, rc, fd;

	fd = 0;
	जबतक ((ctx = coredump_next_context(&fd)) != शून्य) अणु
		rc = spu_acquire_saved(ctx);
		अगर (rc) अणु
			put_spu_context(ctx);
			अवरोध;
		पूर्ण

		rc = spufs_ctx_note_size(ctx, fd);
		spu_release_saved(ctx);
		अगर (rc < 0) अणु
			put_spu_context(ctx);
			अवरोध;
		पूर्ण

		size += rc;

		/* start searching the next fd next समय */
		fd++;
		put_spu_context(ctx);
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक spufs_arch_ग_लिखो_note(काष्ठा spu_context *ctx, पूर्णांक i,
				  काष्ठा coredump_params *cprm, पूर्णांक dfd)
अणु
	माप_प्रकार sz = spufs_coredump_पढ़ो[i].size;
	अक्षर fullname[80];
	काष्ठा elf_note en;
	पूर्णांक ret;

	प्र_लिखो(fullname, "SPU/%d/%s", dfd, spufs_coredump_पढ़ो[i].name);
	en.n_namesz = म_माप(fullname) + 1;
	en.n_descsz = sz;
	en.n_type = NT_SPU;

	अगर (!dump_emit(cprm, &en, माप(en)))
		वापस -EIO;
	अगर (!dump_emit(cprm, fullname, en.n_namesz))
		वापस -EIO;
	अगर (!dump_align(cprm, 4))
		वापस -EIO;

	अगर (spufs_coredump_पढ़ो[i].dump) अणु
		ret = spufs_coredump_पढ़ो[i].dump(ctx, cprm);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		अक्षर buf[32];

		ret = snम_लिखो(buf, माप(buf), "0x%.16llx",
			       spufs_coredump_पढ़ो[i].get(ctx));
		अगर (ret >= माप(buf))
			वापस माप(buf);

		/* count trailing the शून्य: */
		अगर (!dump_emit(cprm, buf, ret + 1))
			वापस -EIO;
	पूर्ण

	dump_skip_to(cprm, roundup(cprm->pos - ret + sz, 4));
	वापस 0;
पूर्ण

पूर्णांक spufs_coredump_extra_notes_ग_लिखो(काष्ठा coredump_params *cprm)
अणु
	काष्ठा spu_context *ctx;
	पूर्णांक fd, j, rc;

	fd = 0;
	जबतक ((ctx = coredump_next_context(&fd)) != शून्य) अणु
		rc = spu_acquire_saved(ctx);
		अगर (rc)
			वापस rc;

		क्रम (j = 0; spufs_coredump_पढ़ो[j].name != शून्य; j++) अणु
			rc = spufs_arch_ग_लिखो_note(ctx, j, cprm, fd);
			अगर (rc) अणु
				spu_release_saved(ctx);
				वापस rc;
			पूर्ण
		पूर्ण

		spu_release_saved(ctx);

		/* start searching the next fd next समय */
		fd++;
	पूर्ण

	वापस 0;
पूर्ण
