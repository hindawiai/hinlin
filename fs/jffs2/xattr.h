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

#अगर_अघोषित _JFFS2_FS_XATTR_H_
#घोषणा _JFFS2_FS_XATTR_H_

#समावेश <linux/xattr.h>
#समावेश <linux/list.h>

#घोषणा JFFS2_XFLAGS_HOT	(0x01)	/* This datum is HOT */
#घोषणा JFFS2_XFLAGS_BIND	(0x02)	/* This datum is not reclaimed */
#घोषणा JFFS2_XFLAGS_DEAD	(0x40)	/* This datum is alपढ़ोy dead */
#घोषणा JFFS2_XFLAGS_INVALID	(0x80)	/* This datum contains crc error */

काष्ठा jffs2_xattr_datum
अणु
	व्योम *always_null;
	काष्ठा jffs2_raw_node_ref *node;
	uपूर्णांक8_t class;
	uपूर्णांक8_t flags;
	uपूर्णांक16_t xprefix;		/* see JFFS2_XATTR_PREFIX_* */

	काष्ठा list_head xindex;	/* chained from c->xattrindex[n] */
	atomic_t refcnt;		/* # of xattr_ref refers this */
	uपूर्णांक32_t xid;
	uपूर्णांक32_t version;

	uपूर्णांक32_t data_crc;
	uपूर्णांक32_t hashkey;
	अक्षर *xname;		/* XATTR name without prefix */
	uपूर्णांक32_t name_len;	/* length of xname */
	अक्षर *xvalue;		/* XATTR value */
	uपूर्णांक32_t value_len;	/* length of xvalue */
पूर्ण;

काष्ठा jffs2_inode_cache;
काष्ठा jffs2_xattr_ref
अणु
	व्योम *always_null;
	काष्ठा jffs2_raw_node_ref *node;
	uपूर्णांक8_t class;
	uपूर्णांक8_t flags;		/* Currently unused */
	u16 unused;

	uपूर्णांक32_t xseqno;
	जोड़ अणु
		काष्ठा jffs2_inode_cache *ic;	/* reference to jffs2_inode_cache */
		uपूर्णांक32_t ino;			/* only used in scanning/building  */
	पूर्ण;
	जोड़ अणु
		काष्ठा jffs2_xattr_datum *xd;	/* reference to jffs2_xattr_datum */
		uपूर्णांक32_t xid;			/* only used in sccanning/building */
	पूर्ण;
	काष्ठा jffs2_xattr_ref *next;		/* chained from ic->xref_list */
पूर्ण;

#घोषणा XREF_DELETE_MARKER	(0x00000001)
अटल अंतरभूत पूर्णांक is_xattr_ref_dead(काष्ठा jffs2_xattr_ref *ref)
अणु
	वापस ((ref->xseqno & XREF_DELETE_MARKER) != 0);
पूर्ण

#अगर_घोषित CONFIG_JFFS2_FS_XATTR

बाह्य व्योम jffs2_init_xattr_subप्रणाली(काष्ठा jffs2_sb_info *c);
बाह्य व्योम jffs2_build_xattr_subप्रणाली(काष्ठा jffs2_sb_info *c);
बाह्य व्योम jffs2_clear_xattr_subप्रणाली(काष्ठा jffs2_sb_info *c);

बाह्य काष्ठा jffs2_xattr_datum *jffs2_setup_xattr_datum(काष्ठा jffs2_sb_info *c,
							 uपूर्णांक32_t xid, uपूर्णांक32_t version);

बाह्य व्योम jffs2_xattr_करो_crccheck_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *ic);
बाह्य व्योम jffs2_xattr_delete_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *ic);
बाह्य व्योम jffs2_xattr_मुक्त_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *ic);

बाह्य पूर्णांक jffs2_garbage_collect_xattr_datum(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_datum *xd,
					     काष्ठा jffs2_raw_node_ref *raw);
बाह्य पूर्णांक jffs2_garbage_collect_xattr_ref(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_ref *ref,
					   काष्ठा jffs2_raw_node_ref *raw);
बाह्य पूर्णांक jffs2_verअगरy_xattr(काष्ठा jffs2_sb_info *c);
बाह्य व्योम jffs2_release_xattr_datum(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_datum *xd);
बाह्य व्योम jffs2_release_xattr_ref(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_xattr_ref *ref);

बाह्य पूर्णांक करो_jffs2_getxattr(काष्ठा inode *inode, पूर्णांक xprefix, स्थिर अक्षर *xname,
			     अक्षर *buffer, माप_प्रकार size);
बाह्य पूर्णांक करो_jffs2_setxattr(काष्ठा inode *inode, पूर्णांक xprefix, स्थिर अक्षर *xname,
			     स्थिर अक्षर *buffer, माप_प्रकार size, पूर्णांक flags);

बाह्य स्थिर काष्ठा xattr_handler *jffs2_xattr_handlers[];
बाह्य स्थिर काष्ठा xattr_handler jffs2_user_xattr_handler;
बाह्य स्थिर काष्ठा xattr_handler jffs2_trusted_xattr_handler;

बाह्य sमाप_प्रकार jffs2_listxattr(काष्ठा dentry *, अक्षर *, माप_प्रकार);

#अन्यथा

#घोषणा jffs2_init_xattr_subप्रणाली(c)
#घोषणा jffs2_build_xattr_subप्रणाली(c)
#घोषणा jffs2_clear_xattr_subप्रणाली(c)

#घोषणा jffs2_xattr_करो_crccheck_inode(c, ic)
#घोषणा jffs2_xattr_delete_inode(c, ic)
#घोषणा jffs2_xattr_मुक्त_inode(c, ic)
#घोषणा jffs2_verअगरy_xattr(c)			(1)

#घोषणा jffs2_xattr_handlers	शून्य
#घोषणा jffs2_listxattr		शून्य

#पूर्ण_अगर /* CONFIG_JFFS2_FS_XATTR */

#अगर_घोषित CONFIG_JFFS2_FS_SECURITY
बाह्य पूर्णांक jffs2_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
			       स्थिर काष्ठा qstr *qstr);
बाह्य स्थिर काष्ठा xattr_handler jffs2_security_xattr_handler;
#अन्यथा
#घोषणा jffs2_init_security(inode,dir,qstr)	(0)
#पूर्ण_अगर /* CONFIG_JFFS2_FS_SECURITY */

#पूर्ण_अगर /* _JFFS2_FS_XATTR_H_ */
