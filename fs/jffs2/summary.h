<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2004  Ferenc Havasi <havasi@inf.u-szeged.hu>,
 *		     Zoltan Sogor <weth@inf.u-szeged.hu>,
 *		     Patrik Kluba <pajko@halom.u-szeged.hu>,
 *		     University of Szeged, Hungary
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#अगर_अघोषित JFFS2_SUMMARY_H
#घोषणा JFFS2_SUMMARY_H

/* Limit summary size to 64KiB so that we can kदो_स्मृति it. If the summary
   is larger than that, we have to just ditch it and aव्योम using summary
   क्रम the eraseblock in question... and it probably करोesn't hurt us much
   anyway. */
#घोषणा MAX_SUMMARY_SIZE 65536

#समावेश <linux/uपन.स>
#समावेश <linux/jffs2.h>

#घोषणा BLK_STATE_ALLFF		0
#घोषणा BLK_STATE_CLEAN		1
#घोषणा BLK_STATE_PARTसूचीTY	2
#घोषणा BLK_STATE_CLEANMARKER	3
#घोषणा BLK_STATE_ALLसूचीTY	4
#घोषणा BLK_STATE_BADBLOCK	5

#घोषणा JFFS2_SUMMARY_NOSUM_SIZE 0xffffffff
#घोषणा JFFS2_SUMMARY_INODE_SIZE (माप(काष्ठा jffs2_sum_inode_flash))
#घोषणा JFFS2_SUMMARY_सूचीENT_SIZE(x) (माप(काष्ठा jffs2_sum_dirent_flash) + (x))
#घोषणा JFFS2_SUMMARY_XATTR_SIZE (माप(काष्ठा jffs2_sum_xattr_flash))
#घोषणा JFFS2_SUMMARY_XREF_SIZE (माप(काष्ठा jffs2_sum_xref_flash))

/* Summary काष्ठाures used on flash */

काष्ठा jffs2_sum_unknown_flash
अणु
	jपूर्णांक16_t nodetype;	/* node type */
पूर्ण;

काष्ठा jffs2_sum_inode_flash
अणु
	jपूर्णांक16_t nodetype;	/* node type */
	jपूर्णांक32_t inode;		/* inode number */
	jपूर्णांक32_t version;	/* inode version */
	jपूर्णांक32_t offset;	/* offset on jeb */
	jपूर्णांक32_t totlen; 	/* record length */
पूर्ण __attribute__((packed));

काष्ठा jffs2_sum_dirent_flash
अणु
	jपूर्णांक16_t nodetype;	/* == JFFS_NODETYPE_सूचीENT */
	jपूर्णांक32_t totlen;	/* record length */
	jपूर्णांक32_t offset;	/* offset on jeb */
	jपूर्णांक32_t pino;		/* parent inode */
	jपूर्णांक32_t version;	/* dirent version */
	jपूर्णांक32_t ino; 		/* == zero क्रम unlink */
	uपूर्णांक8_t nsize;		/* dirent name size */
	uपूर्णांक8_t type;		/* dirent type */
	uपूर्णांक8_t name[];	/* dirent name */
पूर्ण __attribute__((packed));

काष्ठा jffs2_sum_xattr_flash
अणु
	jपूर्णांक16_t nodetype;	/* == JFFS2_NODETYPE_XATR */
	jपूर्णांक32_t xid;		/* xattr identअगरier */
	jपूर्णांक32_t version;	/* version number */
	jपूर्णांक32_t offset;	/* offset on jeb */
	jपूर्णांक32_t totlen;	/* node length */
पूर्ण __attribute__((packed));

काष्ठा jffs2_sum_xref_flash
अणु
	jपूर्णांक16_t nodetype;	/* == JFFS2_NODETYPE_XREF */
	jपूर्णांक32_t offset;	/* offset on jeb */
पूर्ण __attribute__((packed));

जोड़ jffs2_sum_flash
अणु
	काष्ठा jffs2_sum_unknown_flash u;
	काष्ठा jffs2_sum_inode_flash i;
	काष्ठा jffs2_sum_dirent_flash d;
	काष्ठा jffs2_sum_xattr_flash x;
	काष्ठा jffs2_sum_xref_flash r;
पूर्ण;

/* Summary काष्ठाures used in the memory */

काष्ठा jffs2_sum_unknown_mem
अणु
	जोड़ jffs2_sum_mem *next;
	jपूर्णांक16_t nodetype;	/* node type */
पूर्ण;

काष्ठा jffs2_sum_inode_mem
अणु
	जोड़ jffs2_sum_mem *next;
	jपूर्णांक16_t nodetype;	/* node type */
	jपूर्णांक32_t inode;		/* inode number */
	jपूर्णांक32_t version;	/* inode version */
	jपूर्णांक32_t offset;	/* offset on jeb */
	jपूर्णांक32_t totlen; 	/* record length */
पूर्ण __attribute__((packed));

काष्ठा jffs2_sum_dirent_mem
अणु
	जोड़ jffs2_sum_mem *next;
	jपूर्णांक16_t nodetype;	/* == JFFS_NODETYPE_सूचीENT */
	jपूर्णांक32_t totlen;	/* record length */
	jपूर्णांक32_t offset;	/* ofset on jeb */
	jपूर्णांक32_t pino;		/* parent inode */
	jपूर्णांक32_t version;	/* dirent version */
	jपूर्णांक32_t ino; 		/* == zero क्रम unlink */
	uपूर्णांक8_t nsize;		/* dirent name size */
	uपूर्णांक8_t type;		/* dirent type */
	uपूर्णांक8_t name[];	/* dirent name */
पूर्ण __attribute__((packed));

काष्ठा jffs2_sum_xattr_mem
अणु
	जोड़ jffs2_sum_mem *next;
	jपूर्णांक16_t nodetype;
	jपूर्णांक32_t xid;
	jपूर्णांक32_t version;
	jपूर्णांक32_t offset;
	jपूर्णांक32_t totlen;
पूर्ण __attribute__((packed));

काष्ठा jffs2_sum_xref_mem
अणु
	जोड़ jffs2_sum_mem *next;
	jपूर्णांक16_t nodetype;
	jपूर्णांक32_t offset;
पूर्ण __attribute__((packed));

जोड़ jffs2_sum_mem
अणु
	काष्ठा jffs2_sum_unknown_mem u;
	काष्ठा jffs2_sum_inode_mem i;
	काष्ठा jffs2_sum_dirent_mem d;
	काष्ठा jffs2_sum_xattr_mem x;
	काष्ठा jffs2_sum_xref_mem r;
पूर्ण;

/* Summary related inक्रमmation stored in superblock */

काष्ठा jffs2_summary
अणु
	uपूर्णांक32_t sum_size;      /* collected summary inक्रमmation क्रम nextblock */
	uपूर्णांक32_t sum_num;
	uपूर्णांक32_t sum_padded;
	जोड़ jffs2_sum_mem *sum_list_head;
	जोड़ jffs2_sum_mem *sum_list_tail;

	jपूर्णांक32_t *sum_buf;	/* buffer क्रम writing out summary */
पूर्ण;

/* Summary marker is stored at the end of every sumarized erase block */

काष्ठा jffs2_sum_marker
अणु
	jपूर्णांक32_t offset;	/* offset of the summary node in the jeb */
	jपूर्णांक32_t magic; 	/* == JFFS2_SUM_MAGIC */
पूर्ण;

#घोषणा JFFS2_SUMMARY_FRAME_SIZE (माप(काष्ठा jffs2_raw_summary) + माप(काष्ठा jffs2_sum_marker))

#अगर_घोषित CONFIG_JFFS2_SUMMARY	/* SUMMARY SUPPORT ENABLED */

#घोषणा jffs2_sum_active() (1)
पूर्णांक jffs2_sum_init(काष्ठा jffs2_sb_info *c);
व्योम jffs2_sum_निकास(काष्ठा jffs2_sb_info *c);
व्योम jffs2_sum_disable_collecting(काष्ठा jffs2_summary *s);
पूर्णांक jffs2_sum_is_disabled(काष्ठा jffs2_summary *s);
व्योम jffs2_sum_reset_collected(काष्ठा jffs2_summary *s);
व्योम jffs2_sum_move_collected(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_summary *s);
पूर्णांक jffs2_sum_add_kvec(काष्ठा jffs2_sb_info *c, स्थिर काष्ठा kvec *invecs,
			अचिन्हित दीर्घ count,  uपूर्णांक32_t to);
पूर्णांक jffs2_sum_ग_लिखो_sumnode(काष्ठा jffs2_sb_info *c);
पूर्णांक jffs2_sum_add_padding_mem(काष्ठा jffs2_summary *s, uपूर्णांक32_t size);
पूर्णांक jffs2_sum_add_inode_mem(काष्ठा jffs2_summary *s, काष्ठा jffs2_raw_inode *ri, uपूर्णांक32_t ofs);
पूर्णांक jffs2_sum_add_dirent_mem(काष्ठा jffs2_summary *s, काष्ठा jffs2_raw_dirent *rd, uपूर्णांक32_t ofs);
पूर्णांक jffs2_sum_add_xattr_mem(काष्ठा jffs2_summary *s, काष्ठा jffs2_raw_xattr *rx, uपूर्णांक32_t ofs);
पूर्णांक jffs2_sum_add_xref_mem(काष्ठा jffs2_summary *s, काष्ठा jffs2_raw_xref *rr, uपूर्णांक32_t ofs);
पूर्णांक jffs2_sum_scan_sumnode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb,
			   काष्ठा jffs2_raw_summary *summary, uपूर्णांक32_t sumlen,
			   uपूर्णांक32_t *pseuकरो_अक्रमom);

#अन्यथा				/* SUMMARY DISABLED */

#घोषणा jffs2_sum_active() (0)
#घोषणा jffs2_sum_init(a) (0)
#घोषणा jffs2_sum_निकास(a) करो अणु पूर्ण जबतक (0)
#घोषणा jffs2_sum_disable_collecting(a)
#घोषणा jffs2_sum_is_disabled(a) (0)
#घोषणा jffs2_sum_reset_collected(a) करो अणु पूर्ण जबतक (0)
#घोषणा jffs2_sum_add_kvec(a,b,c,d) (0)
#घोषणा jffs2_sum_move_collected(a,b) करो अणु पूर्ण जबतक (0)
#घोषणा jffs2_sum_ग_लिखो_sumnode(a) (0)
#घोषणा jffs2_sum_add_padding_mem(a,b) करो अणु पूर्ण जबतक (0)
#घोषणा jffs2_sum_add_inode_mem(a,b,c) करो अणु पूर्ण जबतक (0)
#घोषणा jffs2_sum_add_dirent_mem(a,b,c) करो अणु पूर्ण जबतक (0)
#घोषणा jffs2_sum_add_xattr_mem(a,b,c) करो अणु पूर्ण जबतक (0)
#घोषणा jffs2_sum_add_xref_mem(a,b,c) करो अणु पूर्ण जबतक (0)
#घोषणा jffs2_sum_scan_sumnode(a,b,c,d,e) (0)

#पूर्ण_अगर /* CONFIG_JFFS2_SUMMARY */

#पूर्ण_अगर /* JFFS2_SUMMARY_H */
