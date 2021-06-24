<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#अगर_अघोषित _JFFS2_DEBUG_H_
#घोषणा _JFFS2_DEBUG_H_

#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/sched.h>

#अगर_अघोषित CONFIG_JFFS2_FS_DEBUG
#घोषणा CONFIG_JFFS2_FS_DEBUG 0
#पूर्ण_अगर

#अगर CONFIG_JFFS2_FS_DEBUG > 0
/* Enable "paranoia" checks and dumps */
#घोषणा JFFS2_DBG_PARANOIA_CHECKS
#घोषणा JFFS2_DBG_DUMPS

/*
 * By defining/undefining the below macros one may select debugging messages
 * fro specअगरic JFFS2 subप्रणालीs.
 */
#घोषणा JFFS2_DBG_READINODE_MESSAGES
#घोषणा JFFS2_DBG_FRAGTREE_MESSAGES
#घोषणा JFFS2_DBG_DENTLIST_MESSAGES
#घोषणा JFFS2_DBG_NODEREF_MESSAGES
#घोषणा JFFS2_DBG_INOCACHE_MESSAGES
#घोषणा JFFS2_DBG_SUMMARY_MESSAGES
#घोषणा JFFS2_DBG_FSBUILD_MESSAGES
#पूर्ण_अगर

#अगर CONFIG_JFFS2_FS_DEBUG > 1
#घोषणा JFFS2_DBG_FRAGTREE2_MESSAGES
#घोषणा JFFS2_DBG_READINODE2_MESSAGES
#घोषणा JFFS2_DBG_MEMALLOC_MESSAGES
#पूर्ण_अगर

/* Sanity checks are supposed to be light-weight and enabled by शेष */
#घोषणा JFFS2_DBG_SANITY_CHECKS

/*
 * Dx() are मुख्यly used क्रम debugging messages, they must go away and be
 * superseded by nicer dbg_xxx() macros...
 */
#अगर CONFIG_JFFS2_FS_DEBUG > 0
#घोषणा DEBUG
#घोषणा D1(x) x
#अन्यथा
#घोषणा D1(x)
#पूर्ण_अगर

#अगर CONFIG_JFFS2_FS_DEBUG > 1
#घोषणा D2(x) x
#अन्यथा
#घोषणा D2(x)
#पूर्ण_अगर

#घोषणा jffs2_dbg(level, fmt, ...)		\
करो अणु						\
	अगर (CONFIG_JFFS2_FS_DEBUG >= level)	\
		pr_debug(fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

/* The prefixes of JFFS2 messages */
#घोषणा JFFS2_DBG		KERN_DEBUG
#घोषणा JFFS2_DBG_PREFIX	"[JFFS2 DBG]"
#घोषणा JFFS2_DBG_MSG_PREFIX	JFFS2_DBG JFFS2_DBG_PREFIX

/* JFFS2 message macros */
#घोषणा JFFS2_ERROR(fmt, ...)					\
	pr_err("error: (%d) %s: " fmt,				\
	       task_pid_nr(current), __func__, ##__VA_ARGS__)

#घोषणा JFFS2_WARNING(fmt, ...)						\
	pr_warn("warning: (%d) %s: " fmt,				\
		task_pid_nr(current), __func__, ##__VA_ARGS__)

#घोषणा JFFS2_NOTICE(fmt, ...)						\
	pr_notice("notice: (%d) %s: " fmt,				\
		  task_pid_nr(current), __func__, ##__VA_ARGS__)

#घोषणा JFFS2_DEBUG(fmt, ...)						\
	prपूर्णांकk(KERN_DEBUG "[JFFS2 DBG] (%d) %s: " fmt,			\
	       task_pid_nr(current), __func__, ##__VA_ARGS__)

/*
 * We split our debugging messages on several parts, depending on the JFFS2
 * subप्रणाली the message beदीर्घs to.
 */
/* Read inode debugging messages */
#अगर_घोषित JFFS2_DBG_READINODE_MESSAGES
#घोषणा dbg_पढ़ोinode(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा dbg_पढ़ोinode(fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर
#अगर_घोषित JFFS2_DBG_READINODE2_MESSAGES
#घोषणा dbg_पढ़ोinode2(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा dbg_पढ़ोinode2(fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

/* Fragtree build debugging messages */
#अगर_घोषित JFFS2_DBG_FRAGTREE_MESSAGES
#घोषणा dbg_fragtree(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा dbg_fragtree(fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर
#अगर_घोषित JFFS2_DBG_FRAGTREE2_MESSAGES
#घोषणा dbg_fragtree2(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा dbg_fragtree2(fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

/* Directory entry list manilulation debugging messages */
#अगर_घोषित JFFS2_DBG_DENTLIST_MESSAGES
#घोषणा dbg_dentlist(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा dbg_dentlist(fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

/* Prपूर्णांक the messages about manipulating node_refs */
#अगर_घोषित JFFS2_DBG_NODEREF_MESSAGES
#घोषणा dbg_noderef(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा dbg_noderef(fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

/* Manipulations with the list of inodes (JFFS2 inocache) */
#अगर_घोषित JFFS2_DBG_INOCACHE_MESSAGES
#घोषणा dbg_inocache(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा dbg_inocache(fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

/* Summary debugging messages */
#अगर_घोषित JFFS2_DBG_SUMMARY_MESSAGES
#घोषणा dbg_summary(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा dbg_summary(fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

/* File प्रणाली build messages */
#अगर_घोषित JFFS2_DBG_FSBUILD_MESSAGES
#घोषणा dbg_fsbuild(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा dbg_fsbuild(fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

/* Watch the object allocations */
#अगर_घोषित JFFS2_DBG_MEMALLOC_MESSAGES
#घोषणा dbg_meदो_स्मृति(fmt, ...)	JFFS2_DEBUG(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा dbg_meदो_स्मृति(fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

/* Watch the XATTR subप्रणाली */
#अगर_घोषित JFFS2_DBG_XATTR_MESSAGES
#घोषणा dbg_xattr(fmt, ...)  JFFS2_DEBUG(fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा dbg_xattr(fmt, ...)  no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर 

/* "Sanity" checks */
व्योम
__jffs2_dbg_acct_sanity_check_nolock(काष्ठा jffs2_sb_info *c,
				     काष्ठा jffs2_eraseblock *jeb);
व्योम
__jffs2_dbg_acct_sanity_check(काष्ठा jffs2_sb_info *c,
			      काष्ठा jffs2_eraseblock *jeb);

/* "Paranoia" checks */
व्योम
__jffs2_dbg_fragtree_paranoia_check(काष्ठा jffs2_inode_info *f);
व्योम
__jffs2_dbg_fragtree_paranoia_check_nolock(काष्ठा jffs2_inode_info *f);
व्योम
__jffs2_dbg_acct_paranoia_check(काष्ठा jffs2_sb_info *c,
			   	काष्ठा jffs2_eraseblock *jeb);
व्योम
__jffs2_dbg_acct_paranoia_check_nolock(काष्ठा jffs2_sb_info *c,
				       काष्ठा jffs2_eraseblock *jeb);
व्योम
__jffs2_dbg_preग_लिखो_paranoia_check(काष्ठा jffs2_sb_info *c,
				    uपूर्णांक32_t ofs, पूर्णांक len);

/* "Dump" functions */
व्योम
__jffs2_dbg_dump_jeb(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb);
व्योम
__jffs2_dbg_dump_jeb_nolock(काष्ठा jffs2_eraseblock *jeb);
व्योम
__jffs2_dbg_dump_block_lists(काष्ठा jffs2_sb_info *c);
व्योम
__jffs2_dbg_dump_block_lists_nolock(काष्ठा jffs2_sb_info *c);
व्योम
__jffs2_dbg_dump_node_refs(काष्ठा jffs2_sb_info *c,
		 	   काष्ठा jffs2_eraseblock *jeb);
व्योम
__jffs2_dbg_dump_node_refs_nolock(काष्ठा jffs2_sb_info *c,
				  काष्ठा jffs2_eraseblock *jeb);
व्योम
__jffs2_dbg_dump_fragtree(काष्ठा jffs2_inode_info *f);
व्योम
__jffs2_dbg_dump_fragtree_nolock(काष्ठा jffs2_inode_info *f);
व्योम
__jffs2_dbg_dump_buffer(अचिन्हित अक्षर *buf, पूर्णांक len, uपूर्णांक32_t offs);
व्योम
__jffs2_dbg_dump_node(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t ofs);

#अगर_घोषित JFFS2_DBG_PARANOIA_CHECKS
#घोषणा jffs2_dbg_fragtree_paranoia_check(f)			\
	__jffs2_dbg_fragtree_paranoia_check(f)
#घोषणा jffs2_dbg_fragtree_paranoia_check_nolock(f)		\
	__jffs2_dbg_fragtree_paranoia_check_nolock(f)
#घोषणा jffs2_dbg_acct_paranoia_check(c, jeb)			\
	__jffs2_dbg_acct_paranoia_check(c,jeb)
#घोषणा jffs2_dbg_acct_paranoia_check_nolock(c, jeb)		\
	__jffs2_dbg_acct_paranoia_check_nolock(c,jeb)
#घोषणा jffs2_dbg_preग_लिखो_paranoia_check(c, ofs, len)		\
	__jffs2_dbg_preग_लिखो_paranoia_check(c, ofs, len)
#अन्यथा
#घोषणा jffs2_dbg_fragtree_paranoia_check(f)
#घोषणा jffs2_dbg_fragtree_paranoia_check_nolock(f)
#घोषणा jffs2_dbg_acct_paranoia_check(c, jeb)
#घोषणा jffs2_dbg_acct_paranoia_check_nolock(c, jeb)
#घोषणा jffs2_dbg_preग_लिखो_paranoia_check(c, ofs, len)
#पूर्ण_अगर /* !JFFS2_PARANOIA_CHECKS */

#अगर_घोषित JFFS2_DBG_DUMPS
#घोषणा jffs2_dbg_dump_jeb(c, jeb)				\
	__jffs2_dbg_dump_jeb(c, jeb);
#घोषणा jffs2_dbg_dump_jeb_nolock(jeb)				\
	__jffs2_dbg_dump_jeb_nolock(jeb);
#घोषणा jffs2_dbg_dump_block_lists(c)				\
	__jffs2_dbg_dump_block_lists(c)
#घोषणा jffs2_dbg_dump_block_lists_nolock(c)			\
	__jffs2_dbg_dump_block_lists_nolock(c)
#घोषणा jffs2_dbg_dump_fragtree(f)				\
	__jffs2_dbg_dump_fragtree(f);
#घोषणा jffs2_dbg_dump_fragtree_nolock(f)			\
	__jffs2_dbg_dump_fragtree_nolock(f);
#घोषणा jffs2_dbg_dump_buffer(buf, len, offs)			\
	__jffs2_dbg_dump_buffer(*buf, len, offs);
#घोषणा jffs2_dbg_dump_node(c, ofs)				\
	__jffs2_dbg_dump_node(c, ofs);
#अन्यथा
#घोषणा jffs2_dbg_dump_jeb(c, jeb)
#घोषणा jffs2_dbg_dump_jeb_nolock(jeb)
#घोषणा jffs2_dbg_dump_block_lists(c)
#घोषणा jffs2_dbg_dump_block_lists_nolock(c)
#घोषणा jffs2_dbg_dump_fragtree(f)
#घोषणा jffs2_dbg_dump_fragtree_nolock(f)
#घोषणा jffs2_dbg_dump_buffer(buf, len, offs)
#घोषणा jffs2_dbg_dump_node(c, ofs)
#पूर्ण_अगर /* !JFFS2_DBG_DUMPS */

#अगर_घोषित JFFS2_DBG_SANITY_CHECKS
#घोषणा jffs2_dbg_acct_sanity_check(c, jeb)			\
	__jffs2_dbg_acct_sanity_check(c, jeb)
#घोषणा jffs2_dbg_acct_sanity_check_nolock(c, jeb)		\
	__jffs2_dbg_acct_sanity_check_nolock(c, jeb)
#अन्यथा
#घोषणा jffs2_dbg_acct_sanity_check(c, jeb)
#घोषणा jffs2_dbg_acct_sanity_check_nolock(c, jeb)
#पूर्ण_अगर /* !JFFS2_DBG_SANITY_CHECKS */

#पूर्ण_अगर /* _JFFS2_DEBUG_H_ */
