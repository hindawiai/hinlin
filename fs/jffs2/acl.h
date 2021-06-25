<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2006  NEC Corporation
 *
 * Created by KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

काष्ठा jffs2_acl_entry अणु
	jपूर्णांक16_t	e_tag;
	jपूर्णांक16_t	e_perm;
	jपूर्णांक32_t	e_id;
पूर्ण;

काष्ठा jffs2_acl_entry_लघु अणु
	jपूर्णांक16_t	e_tag;
	jपूर्णांक16_t	e_perm;
पूर्ण;

काष्ठा jffs2_acl_header अणु
	jपूर्णांक32_t	a_version;
	काष्ठा jffs2_acl_entry	a_entries[];
पूर्ण;

#अगर_घोषित CONFIG_JFFS2_FS_POSIX_ACL

काष्ठा posix_acl *jffs2_get_acl(काष्ठा inode *inode, पूर्णांक type);
पूर्णांक jffs2_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		  काष्ठा posix_acl *acl, पूर्णांक type);
बाह्य पूर्णांक jffs2_init_acl_pre(काष्ठा inode *, काष्ठा inode *, umode_t *);
बाह्य पूर्णांक jffs2_init_acl_post(काष्ठा inode *);

#अन्यथा

#घोषणा jffs2_get_acl				(शून्य)
#घोषणा jffs2_set_acl				(शून्य)
#घोषणा jffs2_init_acl_pre(dir_i,inode,mode)	(0)
#घोषणा jffs2_init_acl_post(inode)		(0)

#पूर्ण_अगर	/* CONFIG_JFFS2_FS_POSIX_ACL */
