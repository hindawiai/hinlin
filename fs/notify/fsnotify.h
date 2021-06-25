<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __FS_NOTIFY_FSNOTIFY_H_
#घोषणा __FS_NOTIFY_FSNOTIFY_H_

#समावेश <linux/list.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/srcu.h>
#समावेश <linux/types.h>

#समावेश "../mount.h"

अटल अंतरभूत काष्ठा inode *fsnotअगरy_conn_inode(
				काष्ठा fsnotअगरy_mark_connector *conn)
अणु
	वापस container_of(conn->obj, काष्ठा inode, i_fsnotअगरy_marks);
पूर्ण

अटल अंतरभूत काष्ठा mount *fsnotअगरy_conn_mount(
				काष्ठा fsnotअगरy_mark_connector *conn)
अणु
	वापस container_of(conn->obj, काष्ठा mount, mnt_fsnotअगरy_marks);
पूर्ण

अटल अंतरभूत काष्ठा super_block *fsnotअगरy_conn_sb(
				काष्ठा fsnotअगरy_mark_connector *conn)
अणु
	वापस container_of(conn->obj, काष्ठा super_block, s_fsnotअगरy_marks);
पूर्ण

/* destroy all events sitting in this groups notअगरication queue */
बाह्य व्योम fsnotअगरy_flush_notअगरy(काष्ठा fsnotअगरy_group *group);

/* protects पढ़ोs of inode and vfsmount marks list */
बाह्य काष्ठा srcu_काष्ठा fsnotअगरy_mark_srcu;

/* compare two groups क्रम sorting of marks lists */
बाह्य पूर्णांक fsnotअगरy_compare_groups(काष्ठा fsnotअगरy_group *a,
				   काष्ठा fsnotअगरy_group *b);

/* Destroy all marks attached to an object via connector */
बाह्य व्योम fsnotअगरy_destroy_marks(fsnotअगरy_connp_t *connp);
/* run the list of all marks associated with inode and destroy them */
अटल अंतरभूत व्योम fsnotअगरy_clear_marks_by_inode(काष्ठा inode *inode)
अणु
	fsnotअगरy_destroy_marks(&inode->i_fsnotअगरy_marks);
पूर्ण
/* run the list of all marks associated with vfsmount and destroy them */
अटल अंतरभूत व्योम fsnotअगरy_clear_marks_by_mount(काष्ठा vfsmount *mnt)
अणु
	fsnotअगरy_destroy_marks(&real_mount(mnt)->mnt_fsnotअगरy_marks);
पूर्ण
/* run the list of all marks associated with sb and destroy them */
अटल अंतरभूत व्योम fsnotअगरy_clear_marks_by_sb(काष्ठा super_block *sb)
अणु
	fsnotअगरy_destroy_marks(&sb->s_fsnotअगरy_marks);
पूर्ण

/*
 * update the dentry->d_flags of all of inode's children to indicate अगर inode cares
 * about events that happen to its children.
 */
बाह्य व्योम __fsnotअगरy_update_child_dentry_flags(काष्ठा inode *inode);

/* allocate and destroy and event holder to attach events to notअगरication/access queues */
बाह्य काष्ठा fsnotअगरy_event_holder *fsnotअगरy_alloc_event_holder(व्योम);
बाह्य व्योम fsnotअगरy_destroy_event_holder(काष्ठा fsnotअगरy_event_holder *holder);

बाह्य काष्ठा kmem_cache *fsnotअगरy_mark_connector_cachep;

#पूर्ण_अगर	/* __FS_NOTIFY_FSNOTIFY_H_ */
