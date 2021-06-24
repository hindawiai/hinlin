<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * locks.c
 *
 * Userspace file locking support
 *
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/fcntl.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "dlmglue.h"
#समावेश "file.h"
#समावेश "inode.h"
#समावेश "locks.h"

अटल पूर्णांक ocfs2_करो_flock(काष्ठा file *file, काष्ठा inode *inode,
			  पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	पूर्णांक ret = 0, level = 0, trylock = 0;
	काष्ठा ocfs2_file_निजी *fp = file->निजी_data;
	काष्ठा ocfs2_lock_res *lockres = &fp->fp_flock;

	अगर (fl->fl_type == F_WRLCK)
		level = 1;
	अगर (!IS_SETLKW(cmd))
		trylock = 1;

	mutex_lock(&fp->fp_mutex);

	अगर (lockres->l_flags & OCFS2_LOCK_ATTACHED &&
	    lockres->l_level > LKM_NLMODE) अणु
		पूर्णांक old_level = 0;
		काष्ठा file_lock request;

		अगर (lockres->l_level == LKM_EXMODE)
			old_level = 1;

		अगर (level == old_level)
			जाओ out;

		/*
		 * Converting an existing lock is not guaranteed to be
		 * atomic, so we can get away with simply unlocking
		 * here and allowing the lock code to try at the new
		 * level.
		 */

		locks_init_lock(&request);
		request.fl_type = F_UNLCK;
		request.fl_flags = FL_FLOCK;
		locks_lock_file_रुको(file, &request);

		ocfs2_file_unlock(file);
	पूर्ण

	ret = ocfs2_file_lock(file, level, trylock);
	अगर (ret) अणु
		अगर (ret == -EAGAIN && trylock)
			ret = -EWOULDBLOCK;
		अन्यथा
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = locks_lock_file_रुको(file, fl);
	अगर (ret)
		ocfs2_file_unlock(file);

out:
	mutex_unlock(&fp->fp_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_करो_funlock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_file_निजी *fp = file->निजी_data;

	mutex_lock(&fp->fp_mutex);
	ocfs2_file_unlock(file);
	ret = locks_lock_file_रुको(file, fl);
	mutex_unlock(&fp->fp_mutex);

	वापस ret;
पूर्ण

/*
 * Overall flow of ocfs2_flock() was influenced by gfs2_flock().
 */
पूर्णांक ocfs2_flock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (!(fl->fl_flags & FL_FLOCK))
		वापस -ENOLCK;
	अगर (__mandatory_lock(inode))
		वापस -ENOLCK;

	अगर ((osb->s_mount_opt & OCFS2_MOUNT_LOCALFLOCKS) ||
	    ocfs2_mount_local(osb))
		वापस locks_lock_file_रुको(file, fl);

	अगर (fl->fl_type == F_UNLCK)
		वापस ocfs2_करो_funlock(file, cmd, fl);
	अन्यथा
		वापस ocfs2_करो_flock(file, inode, cmd, fl);
पूर्ण

पूर्णांक ocfs2_lock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (!(fl->fl_flags & FL_POSIX))
		वापस -ENOLCK;
	अगर (__mandatory_lock(inode) && fl->fl_type != F_UNLCK)
		वापस -ENOLCK;

	वापस ocfs2_plock(osb->cconn, OCFS2_I(inode)->ip_blkno, file, cmd, fl);
पूर्ण
