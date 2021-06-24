<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>
#समावेश <linux/inotअगरy.h>
#समावेश <linux/fanotअगरy.h>
#समावेश <linux/kernel.h>
#समावेश <linux/namei.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/exportfs.h>

#समावेश "inotify/inotify.h"
#समावेश "fdinfo.h"
#समावेश "fsnotify.h"

#अगर defined(CONFIG_PROC_FS)

#अगर defined(CONFIG_INOTIFY_USER) || defined(CONFIG_FANOTIFY)

अटल व्योम show_fdinfo(काष्ठा seq_file *m, काष्ठा file *f,
			व्योम (*show)(काष्ठा seq_file *m,
				     काष्ठा fsnotअगरy_mark *mark))
अणु
	काष्ठा fsnotअगरy_group *group = f->निजी_data;
	काष्ठा fsnotअगरy_mark *mark;

	mutex_lock(&group->mark_mutex);
	list_क्रम_each_entry(mark, &group->marks_list, g_list) अणु
		show(m, mark);
		अगर (seq_has_overflowed(m))
			अवरोध;
	पूर्ण
	mutex_unlock(&group->mark_mutex);
पूर्ण

#अगर defined(CONFIG_EXPORTFS)
अटल व्योम show_mark_fhandle(काष्ठा seq_file *m, काष्ठा inode *inode)
अणु
	काष्ठा अणु
		काष्ठा file_handle handle;
		u8 pad[MAX_HANDLE_SZ];
	पूर्ण f;
	पूर्णांक size, ret, i;

	f.handle.handle_bytes = माप(f.pad);
	size = f.handle.handle_bytes >> 2;

	ret = exportfs_encode_inode_fh(inode, (काष्ठा fid *)f.handle.f_handle, &size, शून्य);
	अगर ((ret == खाताID_INVALID) || (ret < 0)) अणु
		WARN_ONCE(1, "Can't encode file handler for inotify: %d\n", ret);
		वापस;
	पूर्ण

	f.handle.handle_type = ret;
	f.handle.handle_bytes = size * माप(u32);

	seq_म_लिखो(m, "fhandle-bytes:%x fhandle-type:%x f_handle:",
		   f.handle.handle_bytes, f.handle.handle_type);

	क्रम (i = 0; i < f.handle.handle_bytes; i++)
		seq_म_लिखो(m, "%02x", (पूर्णांक)f.handle.f_handle[i]);
पूर्ण
#अन्यथा
अटल व्योम show_mark_fhandle(काष्ठा seq_file *m, काष्ठा inode *inode)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_INOTIFY_USER

अटल व्योम inotअगरy_fdinfo(काष्ठा seq_file *m, काष्ठा fsnotअगरy_mark *mark)
अणु
	काष्ठा inotअगरy_inode_mark *inode_mark;
	काष्ठा inode *inode;

	अगर (mark->connector->type != FSNOTIFY_OBJ_TYPE_INODE)
		वापस;

	inode_mark = container_of(mark, काष्ठा inotअगरy_inode_mark, fsn_mark);
	inode = igrab(fsnotअगरy_conn_inode(mark->connector));
	अगर (inode) अणु
		/*
		 * IN_ALL_EVENTS represents all of the mask bits
		 * that we expose to userspace.  There is at
		 * least one bit (FS_EVENT_ON_CHILD) which is
		 * used only पूर्णांकernally to the kernel.
		 */
		u32 mask = mark->mask & IN_ALL_EVENTS;
		seq_म_लिखो(m, "inotify wd:%x ino:%lx sdev:%x mask:%x ignored_mask:%x ",
			   inode_mark->wd, inode->i_ino, inode->i_sb->s_dev,
			   mask, mark->ignored_mask);
		show_mark_fhandle(m, inode);
		seq_अ_दो(m, '\n');
		iput(inode);
	पूर्ण
पूर्ण

व्योम inotअगरy_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *f)
अणु
	show_fdinfo(m, f, inotअगरy_fdinfo);
पूर्ण

#पूर्ण_अगर /* CONFIG_INOTIFY_USER */

#अगर_घोषित CONFIG_FANOTIFY

अटल व्योम fanotअगरy_fdinfo(काष्ठा seq_file *m, काष्ठा fsnotअगरy_mark *mark)
अणु
	अचिन्हित पूर्णांक mflags = 0;
	काष्ठा inode *inode;

	अगर (mark->flags & FSNOTIFY_MARK_FLAG_IGNORED_SURV_MODIFY)
		mflags |= FAN_MARK_IGNORED_SURV_MODIFY;

	अगर (mark->connector->type == FSNOTIFY_OBJ_TYPE_INODE) अणु
		inode = igrab(fsnotअगरy_conn_inode(mark->connector));
		अगर (!inode)
			वापस;
		seq_म_लिखो(m, "fanotify ino:%lx sdev:%x mflags:%x mask:%x ignored_mask:%x ",
			   inode->i_ino, inode->i_sb->s_dev,
			   mflags, mark->mask, mark->ignored_mask);
		show_mark_fhandle(m, inode);
		seq_अ_दो(m, '\n');
		iput(inode);
	पूर्ण अन्यथा अगर (mark->connector->type == FSNOTIFY_OBJ_TYPE_VFSMOUNT) अणु
		काष्ठा mount *mnt = fsnotअगरy_conn_mount(mark->connector);

		seq_म_लिखो(m, "fanotify mnt_id:%x mflags:%x mask:%x ignored_mask:%x\n",
			   mnt->mnt_id, mflags, mark->mask, mark->ignored_mask);
	पूर्ण अन्यथा अगर (mark->connector->type == FSNOTIFY_OBJ_TYPE_SB) अणु
		काष्ठा super_block *sb = fsnotअगरy_conn_sb(mark->connector);

		seq_म_लिखो(m, "fanotify sdev:%x mflags:%x mask:%x ignored_mask:%x\n",
			   sb->s_dev, mflags, mark->mask, mark->ignored_mask);
	पूर्ण
पूर्ण

व्योम fanotअगरy_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *f)
अणु
	काष्ठा fsnotअगरy_group *group = f->निजी_data;

	seq_म_लिखो(m, "fanotify flags:%x event-flags:%x\n",
		   group->fanotअगरy_data.flags & FANOTIFY_INIT_FLAGS,
		   group->fanotअगरy_data.f_flags);

	show_fdinfo(m, f, fanotअगरy_fdinfo);
पूर्ण

#पूर्ण_अगर /* CONFIG_FANOTIFY */

#पूर्ण_अगर /* CONFIG_INOTIFY_USER || CONFIG_FANOTIFY */

#पूर्ण_अगर /* CONFIG_PROC_FS */
