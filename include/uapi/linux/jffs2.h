<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in the
 * jffs2 directory.
 */

#अगर_अघोषित __LINUX_JFFS2_H__
#घोषणा __LINUX_JFFS2_H__

#समावेश <linux/types.h>
#समावेश <linux/magic.h>

/* You must include something which defines the C99 uपूर्णांकXX_t types. 
   We करोn't करो it from here because this file is used in too many
   dअगरferent environments. */

/* Values we may expect to find in the 'magic' field */
#घोषणा JFFS2_OLD_MAGIC_BITMASK 0x1984
#घोषणा JFFS2_MAGIC_BITMASK 0x1985
#घोषणा KSAMTIB_CIGAM_2SFFJ 0x8519 /* For detecting wrong-endian fs */
#घोषणा JFFS2_EMPTY_BITMASK 0xffff
#घोषणा JFFS2_सूचीTY_BITMASK 0x0000

/* Summary node MAGIC marker */
#घोषणा JFFS2_SUM_MAGIC	0x02851885

/* We only allow a single अक्षर क्रम length, and 0xFF is empty flash so
   we करोn't want it confused with a real length. Hence max 254.
*/
#घोषणा JFFS2_MAX_NAME_LEN 254

/* How small can we sensibly ग_लिखो nodes? */
#घोषणा JFFS2_MIN_DATA_LEN 128

#घोषणा JFFS2_COMPR_NONE	0x00
#घोषणा JFFS2_COMPR_ZERO	0x01
#घोषणा JFFS2_COMPR_RTIME	0x02
#घोषणा JFFS2_COMPR_RUBINMIPS	0x03
#घोषणा JFFS2_COMPR_COPY	0x04
#घोषणा JFFS2_COMPR_DYNRUBIN	0x05
#घोषणा JFFS2_COMPR_ZLIB	0x06
#घोषणा JFFS2_COMPR_LZO		0x07
/* Compatibility flags. */
#घोषणा JFFS2_COMPAT_MASK 0xc000      /* What करो to अगर an unknown nodetype is found */
#घोषणा JFFS2_NODE_ACCURATE 0x2000
/* INCOMPAT: Fail to mount the fileप्रणाली */
#घोषणा JFFS2_FEATURE_INCOMPAT 0xc000
/* ROCOMPAT: Mount पढ़ो-only */
#घोषणा JFFS2_FEATURE_ROCOMPAT 0x8000
/* RWCOMPAT_COPY: Mount पढ़ो/ग_लिखो, and copy the node when it's GC'd */
#घोषणा JFFS2_FEATURE_RWCOMPAT_COPY 0x4000
/* RWCOMPAT_DELETE: Mount पढ़ो/ग_लिखो, and delete the node when it's GC'd */
#घोषणा JFFS2_FEATURE_RWCOMPAT_DELETE 0x0000

#घोषणा JFFS2_NODETYPE_सूचीENT (JFFS2_FEATURE_INCOMPAT | JFFS2_NODE_ACCURATE | 1)
#घोषणा JFFS2_NODETYPE_INODE (JFFS2_FEATURE_INCOMPAT | JFFS2_NODE_ACCURATE | 2)
#घोषणा JFFS2_NODETYPE_CLEANMARKER (JFFS2_FEATURE_RWCOMPAT_DELETE | JFFS2_NODE_ACCURATE | 3)
#घोषणा JFFS2_NODETYPE_PADDING (JFFS2_FEATURE_RWCOMPAT_DELETE | JFFS2_NODE_ACCURATE | 4)

#घोषणा JFFS2_NODETYPE_SUMMARY (JFFS2_FEATURE_RWCOMPAT_DELETE | JFFS2_NODE_ACCURATE | 6)

#घोषणा JFFS2_NODETYPE_XATTR (JFFS2_FEATURE_INCOMPAT | JFFS2_NODE_ACCURATE | 8)
#घोषणा JFFS2_NODETYPE_XREF (JFFS2_FEATURE_INCOMPAT | JFFS2_NODE_ACCURATE | 9)

/* XATTR Related */
#घोषणा JFFS2_XPREFIX_USER		1	/* क्रम "user." */
#घोषणा JFFS2_XPREFIX_SECURITY		2	/* क्रम "security." */
#घोषणा JFFS2_XPREFIX_ACL_ACCESS	3	/* क्रम "system.posix_acl_access" */
#घोषणा JFFS2_XPREFIX_ACL_DEFAULT	4	/* क्रम "system.posix_acl_default" */
#घोषणा JFFS2_XPREFIX_TRUSTED		5	/* क्रम "trusted.*" */

#घोषणा JFFS2_ACL_VERSION		0x0001

#घोषणा JFFS2_INO_FLAG_PREREAD	  1	/* Do पढ़ो_inode() क्रम this one at
					   mount समय, करोn't रुको क्रम it to
					   happen later */
#घोषणा JFFS2_INO_FLAG_USERCOMPR  2	/* User has requested a specअगरic
					   compression type */


/* These can go once we've made sure we've caught all uses without
   byteswapping */

प्रकार काष्ठा अणु
	__u32 v32;
पूर्ण __attribute__((packed)) jपूर्णांक32_t;

प्रकार काष्ठा अणु
	__u32 m;
पूर्ण __attribute__((packed)) jmode_t;

प्रकार काष्ठा अणु
	__u16 v16;
पूर्ण __attribute__((packed)) jपूर्णांक16_t;

काष्ठा jffs2_unknown_node
अणु
	/* All start like this */
	jपूर्णांक16_t magic;
	jपूर्णांक16_t nodetype;
	jपूर्णांक32_t totlen; /* So we can skip over nodes we करोn't grok */
	jपूर्णांक32_t hdr_crc;
पूर्ण;

काष्ठा jffs2_raw_dirent
अणु
	jपूर्णांक16_t magic;
	jपूर्णांक16_t nodetype;	/* == JFFS2_NODETYPE_सूचीENT */
	jपूर्णांक32_t totlen;
	jपूर्णांक32_t hdr_crc;
	jपूर्णांक32_t pino;
	jपूर्णांक32_t version;
	jपूर्णांक32_t ino; /* == zero क्रम unlink */
	jपूर्णांक32_t mस_समय;
	__u8 nsize;
	__u8 type;
	__u8 unused[2];
	jपूर्णांक32_t node_crc;
	jपूर्णांक32_t name_crc;
	__u8 name[0];
पूर्ण;

/* The JFFS2 raw inode काष्ठाure: Used क्रम storage on physical media.  */
/* The uid, gid, aसमय, mसमय and स_समय members could be दीर्घer, but
   are left like this क्रम space efficiency. If and when people decide
   they really need them extended, it's simple enough to add support क्रम
   a new type of raw node.
*/
काष्ठा jffs2_raw_inode
अणु
	jपूर्णांक16_t magic;      /* A स्थिरant magic number.  */
	jपूर्णांक16_t nodetype;   /* == JFFS2_NODETYPE_INODE */
	jपूर्णांक32_t totlen;     /* Total length of this node (inc data, etc.) */
	jपूर्णांक32_t hdr_crc;
	jपूर्णांक32_t ino;        /* Inode number.  */
	jपूर्णांक32_t version;    /* Version number.  */
	jmode_t mode;       /* The file's type or mode.  */
	jपूर्णांक16_t uid;        /* The file's owner.  */
	jपूर्णांक16_t gid;        /* The file's group.  */
	jपूर्णांक32_t isize;      /* Total resultant size of this inode (used क्रम truncations)  */
	jपूर्णांक32_t aसमय;      /* Last access समय.  */
	jपूर्णांक32_t mसमय;      /* Last modअगरication समय.  */
	jपूर्णांक32_t स_समय;      /* Change समय.  */
	jपूर्णांक32_t offset;     /* Where to begin to ग_लिखो.  */
	jपूर्णांक32_t csize;      /* (Compressed) data size */
	jपूर्णांक32_t dsize;	     /* Size of the node's data. (after decompression) */
	__u8 compr;       /* Compression algorithm used */
	__u8 usercompr;   /* Compression algorithm requested by the user */
	jपूर्णांक16_t flags;	     /* See JFFS2_INO_FLAG_* */
	jपूर्णांक32_t data_crc;   /* CRC क्रम the (compressed) data.  */
	jपूर्णांक32_t node_crc;   /* CRC क्रम the raw inode (excluding data)  */
	__u8 data[0];
पूर्ण;

काष्ठा jffs2_raw_xattr अणु
	jपूर्णांक16_t magic;
	jपूर्णांक16_t nodetype;	/* = JFFS2_NODETYPE_XATTR */
	jपूर्णांक32_t totlen;
	jपूर्णांक32_t hdr_crc;
	jपूर्णांक32_t xid;		/* XATTR identअगरier number */
	jपूर्णांक32_t version;
	__u8 xprefix;
	__u8 name_len;
	jपूर्णांक16_t value_len;
	jपूर्णांक32_t data_crc;
	jपूर्णांक32_t node_crc;
	__u8 data[0];
पूर्ण __attribute__((packed));

काष्ठा jffs2_raw_xref
अणु
	jपूर्णांक16_t magic;
	jपूर्णांक16_t nodetype;	/* = JFFS2_NODETYPE_XREF */
	jपूर्णांक32_t totlen;
	jपूर्णांक32_t hdr_crc;
	jपूर्णांक32_t ino;		/* inode number */
	jपूर्णांक32_t xid;		/* XATTR identअगरier number */
	jपूर्णांक32_t xseqno;	/* xref sequential number */
	jपूर्णांक32_t node_crc;
पूर्ण __attribute__((packed));

काष्ठा jffs2_raw_summary
अणु
	jपूर्णांक16_t magic;
	jपूर्णांक16_t nodetype; 	/* = JFFS2_NODETYPE_SUMMARY */
	jपूर्णांक32_t totlen;
	jपूर्णांक32_t hdr_crc;
	jपूर्णांक32_t sum_num;	/* number of sum entries*/
	jपूर्णांक32_t cln_mkr;	/* clean marker size, 0 = no cleanmarker */
	jपूर्णांक32_t padded;	/* sum of the size of padding nodes */
	jपूर्णांक32_t sum_crc;	/* summary inक्रमmation crc */
	jपूर्णांक32_t node_crc; 	/* node crc */
	jपूर्णांक32_t sum[0]; 	/* inode summary info */
पूर्ण;

जोड़ jffs2_node_जोड़
अणु
	काष्ठा jffs2_raw_inode i;
	काष्ठा jffs2_raw_dirent d;
	काष्ठा jffs2_raw_xattr x;
	काष्ठा jffs2_raw_xref r;
	काष्ठा jffs2_raw_summary s;
	काष्ठा jffs2_unknown_node u;
पूर्ण;

/* Data payload क्रम device nodes. */
जोड़ jffs2_device_node अणु
	jपूर्णांक16_t old_id;
	jपूर्णांक32_t new_id;
पूर्ण;

#पूर्ण_अगर /* __LINUX_JFFS2_H__ */
