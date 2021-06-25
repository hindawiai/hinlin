<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/fs/pnode.h
 *
 * (C) Copyright IBM Corporation 2005.
 */
#अगर_अघोषित _LINUX_PNODE_H
#घोषणा _LINUX_PNODE_H

#समावेश <linux/list.h>
#समावेश "mount.h"

#घोषणा IS_MNT_SHARED(m) ((m)->mnt.mnt_flags & MNT_SHARED)
#घोषणा IS_MNT_SLAVE(m) ((m)->mnt_master)
#घोषणा IS_MNT_NEW(m)  (!(m)->mnt_ns || is_anon_ns((m)->mnt_ns))
#घोषणा CLEAR_MNT_SHARED(m) ((m)->mnt.mnt_flags &= ~MNT_SHARED)
#घोषणा IS_MNT_UNBINDABLE(m) ((m)->mnt.mnt_flags & MNT_UNBINDABLE)
#घोषणा IS_MNT_MARKED(m) ((m)->mnt.mnt_flags & MNT_MARKED)
#घोषणा SET_MNT_MARK(m) ((m)->mnt.mnt_flags |= MNT_MARKED)
#घोषणा CLEAR_MNT_MARK(m) ((m)->mnt.mnt_flags &= ~MNT_MARKED)
#घोषणा IS_MNT_LOCKED(m) ((m)->mnt.mnt_flags & MNT_LOCKED)

#घोषणा CL_EXPIRE    		0x01
#घोषणा CL_SLAVE     		0x02
#घोषणा CL_COPY_UNBINDABLE	0x04
#घोषणा CL_MAKE_SHARED 		0x08
#घोषणा CL_PRIVATE 		0x10
#घोषणा CL_SHARED_TO_SLAVE	0x20
#घोषणा CL_COPY_MNT_NS_खाता	0x40

#घोषणा CL_COPY_ALL		(CL_COPY_UNBINDABLE | CL_COPY_MNT_NS_खाता)

अटल अंतरभूत व्योम set_mnt_shared(काष्ठा mount *mnt)
अणु
	mnt->mnt.mnt_flags &= ~MNT_SHARED_MASK;
	mnt->mnt.mnt_flags |= MNT_SHARED;
पूर्ण

व्योम change_mnt_propagation(काष्ठा mount *, पूर्णांक);
पूर्णांक propagate_mnt(काष्ठा mount *, काष्ठा mountpoपूर्णांक *, काष्ठा mount *,
		काष्ठा hlist_head *);
पूर्णांक propagate_umount(काष्ठा list_head *);
पूर्णांक propagate_mount_busy(काष्ठा mount *, पूर्णांक);
व्योम propagate_mount_unlock(काष्ठा mount *);
व्योम mnt_release_group_id(काष्ठा mount *);
पूर्णांक get_करोminating_id(काष्ठा mount *mnt, स्थिर काष्ठा path *root);
पूर्णांक mnt_get_count(काष्ठा mount *mnt);
व्योम mnt_set_mountpoपूर्णांक(काष्ठा mount *, काष्ठा mountpoपूर्णांक *,
			काष्ठा mount *);
व्योम mnt_change_mountpoपूर्णांक(काष्ठा mount *parent, काष्ठा mountpoपूर्णांक *mp,
			   काष्ठा mount *mnt);
काष्ठा mount *copy_tree(काष्ठा mount *, काष्ठा dentry *, पूर्णांक);
bool is_path_reachable(काष्ठा mount *, काष्ठा dentry *,
			 स्थिर काष्ठा path *root);
पूर्णांक count_mounts(काष्ठा mnt_namespace *ns, काष्ठा mount *mnt);
#पूर्ण_अगर /* _LINUX_PNODE_H */
