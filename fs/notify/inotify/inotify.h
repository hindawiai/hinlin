<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <linux/inotअगरy.h>
#समावेश <linux/slab.h> /* काष्ठा kmem_cache */

काष्ठा inotअगरy_event_info अणु
	काष्ठा fsnotअगरy_event fse;
	u32 mask;
	पूर्णांक wd;
	u32 sync_cookie;
	पूर्णांक name_len;
	अक्षर name[];
पूर्ण;

काष्ठा inotअगरy_inode_mark अणु
	काष्ठा fsnotअगरy_mark fsn_mark;
	पूर्णांक wd;
पूर्ण;

अटल अंतरभूत काष्ठा inotअगरy_event_info *INOTIFY_E(काष्ठा fsnotअगरy_event *fse)
अणु
	वापस container_of(fse, काष्ठा inotअगरy_event_info, fse);
पूर्ण

बाह्य व्योम inotअगरy_ignored_and_हटाओ_idr(काष्ठा fsnotअगरy_mark *fsn_mark,
					   काष्ठा fsnotअगरy_group *group);
बाह्य पूर्णांक inotअगरy_handle_inode_event(काष्ठा fsnotअगरy_mark *inode_mark,
				      u32 mask, काष्ठा inode *inode,
				      काष्ठा inode *dir,
				      स्थिर काष्ठा qstr *name, u32 cookie);

बाह्य स्थिर काष्ठा fsnotअगरy_ops inotअगरy_fsnotअगरy_ops;
बाह्य काष्ठा kmem_cache *inotअगरy_inode_mark_cachep;

#अगर_घोषित CONFIG_INOTIFY_USER
अटल अंतरभूत व्योम dec_inotअगरy_instances(काष्ठा ucounts *ucounts)
अणु
	dec_ucount(ucounts, UCOUNT_INOTIFY_INSTANCES);
पूर्ण

अटल अंतरभूत काष्ठा ucounts *inc_inotअगरy_watches(काष्ठा ucounts *ucounts)
अणु
	वापस inc_ucount(ucounts->ns, ucounts->uid, UCOUNT_INOTIFY_WATCHES);
पूर्ण

अटल अंतरभूत व्योम dec_inotअगरy_watches(काष्ठा ucounts *ucounts)
अणु
	dec_ucount(ucounts, UCOUNT_INOTIFY_WATCHES);
पूर्ण
#पूर्ण_अगर
