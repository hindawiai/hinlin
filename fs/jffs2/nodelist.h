<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#अगर_अघोषित __JFFS2_NODELIST_H__
#घोषणा __JFFS2_NODELIST_H__

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/jffs2.h>
#समावेश "jffs2_fs_sb.h"
#समावेश "jffs2_fs_i.h"
#समावेश "xattr.h"
#समावेश "acl.h"
#समावेश "summary.h"

#अगर_घोषित __ECOS
#समावेश "os-ecos.h"
#अन्यथा
#समावेश "os-linux.h"
#पूर्ण_अगर

#घोषणा JFFS2_NATIVE_ENDIAN

/* Note we handle mode bits conversion from JFFS2 (i.e. Linux) to/from
   whatever OS we're actually running on here too. */

#अगर defined(JFFS2_NATIVE_ENDIAN)
#घोषणा cpu_to_je16(x) ((jपूर्णांक16_t)अणुxपूर्ण)
#घोषणा cpu_to_je32(x) ((jपूर्णांक32_t)अणुxपूर्ण)
#घोषणा cpu_to_jemode(x) ((jmode_t)अणुos_to_jffs2_mode(x)पूर्ण)

#घोषणा स्थिरant_cpu_to_je16(x) ((jपूर्णांक16_t)अणुxपूर्ण)
#घोषणा स्थिरant_cpu_to_je32(x) ((jपूर्णांक32_t)अणुxपूर्ण)

#घोषणा je16_to_cpu(x) ((x).v16)
#घोषणा je32_to_cpu(x) ((x).v32)
#घोषणा jemode_to_cpu(x) (jffs2_to_os_mode((x).m))
#या_अगर defined(JFFS2_BIG_ENDIAN)
#घोषणा cpu_to_je16(x) ((jपूर्णांक16_t)अणुcpu_to_be16(x)पूर्ण)
#घोषणा cpu_to_je32(x) ((jपूर्णांक32_t)अणुcpu_to_be32(x)पूर्ण)
#घोषणा cpu_to_jemode(x) ((jmode_t)अणुcpu_to_be32(os_to_jffs2_mode(x))पूर्ण)

#घोषणा स्थिरant_cpu_to_je16(x) ((jपूर्णांक16_t)अणु__स्थिरant_cpu_to_be16(x)पूर्ण)
#घोषणा स्थिरant_cpu_to_je32(x) ((jपूर्णांक32_t)अणु__स्थिरant_cpu_to_be32(x)पूर्ण)

#घोषणा je16_to_cpu(x) (be16_to_cpu(x.v16))
#घोषणा je32_to_cpu(x) (be32_to_cpu(x.v32))
#घोषणा jemode_to_cpu(x) (be32_to_cpu(jffs2_to_os_mode((x).m)))
#या_अगर defined(JFFS2_LITTLE_ENDIAN)
#घोषणा cpu_to_je16(x) ((jपूर्णांक16_t)अणुcpu_to_le16(x)पूर्ण)
#घोषणा cpu_to_je32(x) ((jपूर्णांक32_t)अणुcpu_to_le32(x)पूर्ण)
#घोषणा cpu_to_jemode(x) ((jmode_t)अणुcpu_to_le32(os_to_jffs2_mode(x))पूर्ण)

#घोषणा स्थिरant_cpu_to_je16(x) ((jपूर्णांक16_t)अणु__स्थिरant_cpu_to_le16(x)पूर्ण)
#घोषणा स्थिरant_cpu_to_je32(x) ((jपूर्णांक32_t)अणु__स्थिरant_cpu_to_le32(x)पूर्ण)

#घोषणा je16_to_cpu(x) (le16_to_cpu(x.v16))
#घोषणा je32_to_cpu(x) (le32_to_cpu(x.v32))
#घोषणा jemode_to_cpu(x) (le32_to_cpu(jffs2_to_os_mode((x).m)))
#अन्यथा
#त्रुटि wibble
#पूर्ण_अगर

/* The minimal node header size */
#घोषणा JFFS2_MIN_NODE_HEADER माप(काष्ठा jffs2_raw_dirent)

/*
  This is all we need to keep in-core क्रम each raw node during normal
  operation. As and when we करो पढ़ो_inode on a particular inode, we can
  scan the nodes which are listed क्रम it and build up a proper map of
  which nodes are currently valid. JFFSv1 always used to keep that whole
  map in core क्रम each inode.
*/
काष्ठा jffs2_raw_node_ref
अणु
	काष्ठा jffs2_raw_node_ref *next_in_ino; /* Poपूर्णांकs to the next raw_node_ref
		क्रम this object. If this _is_ the last, it poपूर्णांकs to the inode_cache,
		xattr_ref or xattr_datum instead. The common part of those काष्ठाures
		has शून्य in the first word. See jffs2_raw_ref_to_ic() below */
	uपूर्णांक32_t flash_offset;
#अघोषित TEST_TOTLEN
#अगर_घोषित TEST_TOTLEN
	uपूर्णांक32_t __totlen; /* This may die; use ref_totlen(c, jeb, ) below */
#पूर्ण_अगर
पूर्ण;

#घोषणा REF_LINK_NODE ((पूर्णांक32_t)-1)
#घोषणा REF_EMPTY_NODE ((पूर्णांक32_t)-2)

/* Use blocks of about 256 bytes */
#घोषणा REFS_PER_BLOCK ((255/माप(काष्ठा jffs2_raw_node_ref))-1)

अटल अंतरभूत काष्ठा jffs2_raw_node_ref *ref_next(काष्ठा jffs2_raw_node_ref *ref)
अणु
	ref++;

	/* Link to another block of refs */
	अगर (ref->flash_offset == REF_LINK_NODE) अणु
		ref = ref->next_in_ino;
		अगर (!ref)
			वापस ref;
	पूर्ण

	/* End of chain */
	अगर (ref->flash_offset == REF_EMPTY_NODE)
		वापस शून्य;

	वापस ref;
पूर्ण

अटल अंतरभूत काष्ठा jffs2_inode_cache *jffs2_raw_ref_to_ic(काष्ठा jffs2_raw_node_ref *raw)
अणु
	जबतक(raw->next_in_ino)
		raw = raw->next_in_ino;

	/* NB. This can be a jffs2_xattr_datum or jffs2_xattr_ref and
	   not actually a jffs2_inode_cache. Check ->class */
	वापस ((काष्ठा jffs2_inode_cache *)raw);
पूर्ण

	/* flash_offset & 3 always has to be zero, because nodes are
	   always aligned at 4 bytes. So we have a couple of extra bits
	   to play with, which indicate the node's status; see below: */
#घोषणा REF_UNCHECKED	0	/* We haven't yet checked the CRC or built its inode */
#घोषणा REF_OBSOLETE	1	/* Obsolete, can be completely ignored */
#घोषणा REF_PRISTINE	2	/* Completely clean. GC without looking */
#घोषणा REF_NORMAL	3	/* Possibly overlapped. Read the page and ग_लिखो again on GC */
#घोषणा ref_flags(ref)		((ref)->flash_offset & 3)
#घोषणा ref_offset(ref)		((ref)->flash_offset & ~3)
#घोषणा ref_obsolete(ref)	(((ref)->flash_offset & 3) == REF_OBSOLETE)
#घोषणा mark_ref_normal(ref)    करो अणु (ref)->flash_offset = ref_offset(ref) | REF_NORMAL; पूर्ण जबतक(0)

/* Dirent nodes should be REF_PRISTINE only अगर they are not a deletion
   dirent. Deletion dirents should be REF_NORMAL so that GC माला_लो to
   throw them away when appropriate */
#घोषणा dirent_node_state(rd)	( (je32_to_cpu((rd)->ino)?REF_PRISTINE:REF_NORMAL) )

/* NB: REF_PRISTINE क्रम an inode-less node (ref->next_in_ino == शून्य) indicates
   it is an unknown node of type JFFS2_NODETYPE_RWCOMPAT_COPY, so it'll get
   copied. If you need to करो anything dअगरferent to GC inode-less nodes, then
   you need to modअगरy gc.c accordingly. */

/* For each inode in the fileप्रणाली, we need to keep a record of
   nlink, because it would be a PITA to scan the whole directory tree
   at पढ़ो_inode() समय to calculate it, and to keep sufficient inक्रमmation
   in the raw_node_ref (basically both parent and child inode number क्रम
   dirent nodes) would take more space than this करोes. We also keep
   a poपूर्णांकer to the first physical node which is part of this inode, too.
*/
काष्ठा jffs2_inode_cache अणु
	/* First part of काष्ठाure is shared with other objects which
	   can terminate the raw node refs' next_in_ino list -- which
	   currently काष्ठा jffs2_xattr_datum and काष्ठा jffs2_xattr_ref. */

	काष्ठा jffs2_full_dirent *scan_dents; /* Used during scan to hold
		temporary lists of dirents, and later must be set to
		शून्य to mark the end of the raw_node_ref->next_in_ino
		chain. */
	काष्ठा jffs2_raw_node_ref *nodes;
	uपूर्णांक8_t class;	/* It's used क्रम identअगरication */

	/* end of shared काष्ठाure */

	uपूर्णांक8_t flags;
	uपूर्णांक16_t state;
	uपूर्णांक32_t ino;
	काष्ठा jffs2_inode_cache *next;
#अगर_घोषित CONFIG_JFFS2_FS_XATTR
	काष्ठा jffs2_xattr_ref *xref;
#पूर्ण_अगर
	uपूर्णांक32_t pino_nlink;	/* Directories store parent inode
				   here; other inodes store nlink.
				   Zero always means that it's
				   completely unlinked. */
पूर्ण;

/* Inode states क्रम 'state' above. We need the 'GC' state to prevent
   someone from करोing a पढ़ो_inode() जबतक we're moving a 'REF_PRISTINE'
   node without going through all the iget() nonsense */
#घोषणा INO_STATE_UNCHECKED	0	/* CRC checks not yet करोne */
#घोषणा INO_STATE_CHECKING	1	/* CRC checks in progress */
#घोषणा INO_STATE_PRESENT	2	/* In core */
#घोषणा INO_STATE_CHECKEDABSENT	3	/* Checked, cleared again */
#घोषणा INO_STATE_GC		4	/* GCing a 'pristine' node */
#घोषणा INO_STATE_READING	5	/* In पढ़ो_inode() */
#घोषणा INO_STATE_CLEARING	6	/* In clear_inode() */

#घोषणा INO_FLAGS_XATTR_CHECKED	0x01	/* has no duplicate xattr_ref */
#घोषणा INO_FLAGS_IS_सूची	0x02	/* is a directory */

#घोषणा RAWNODE_CLASS_INODE_CACHE	0
#घोषणा RAWNODE_CLASS_XATTR_DATUM	1
#घोषणा RAWNODE_CLASS_XATTR_REF		2

#घोषणा INOCACHE_HASHSIZE_MIN 128
#घोषणा INOCACHE_HASHSIZE_MAX 1024

#घोषणा ग_लिखो_ofs(c) ((c)->nextblock->offset + (c)->sector_size - (c)->nextblock->मुक्त_size)

/*
  Larger representation of a raw node, kept in-core only when the
  काष्ठा inode क्रम this particular ino is instantiated.
*/

काष्ठा jffs2_full_dnode
अणु
	काष्ठा jffs2_raw_node_ref *raw;
	uपूर्णांक32_t ofs; /* The offset to which the data of this node beदीर्घs */
	uपूर्णांक32_t size;
	uपूर्णांक32_t frags; /* Number of fragments which currently refer
			to this node. When this reaches zero,
			the node is obsolete.  */
पूर्ण;

/*
   Even larger representation of a raw node, kept in-core only जबतक
   we're actually building up the original map of which nodes go where,
   in पढ़ो_inode()
*/
काष्ठा jffs2_पंचांगp_dnode_info
अणु
	काष्ठा rb_node rb;
	काष्ठा jffs2_full_dnode *fn;
	uपूर्णांक32_t version;
	uपूर्णांक32_t data_crc;
	uपूर्णांक32_t partial_crc;
	uपूर्णांक32_t csize;
	uपूर्णांक16_t overlapped;
पूर्ण;

/* Temporary data काष्ठाure used during पढ़ोinode. */
काष्ठा jffs2_पढ़ोinode_info
अणु
	काष्ठा rb_root tn_root;
	काष्ठा jffs2_पंचांगp_dnode_info *mdata_tn;
	uपूर्णांक32_t highest_version;
	uपूर्णांक32_t latest_mस_समय;
	uपूर्णांक32_t mस_समय_ver;
	काष्ठा jffs2_full_dirent *fds;
	काष्ठा jffs2_raw_node_ref *latest_ref;
पूर्ण;

काष्ठा jffs2_full_dirent
अणु
	जोड़ अणु
		काष्ठा jffs2_raw_node_ref *raw;
		काष्ठा jffs2_inode_cache *ic; /* Just during part of build */
	पूर्ण;
	काष्ठा jffs2_full_dirent *next;
	uपूर्णांक32_t version;
	uपूर्णांक32_t ino; /* == zero क्रम unlink */
	अचिन्हित पूर्णांक nhash;
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर name[];
पूर्ण;

/*
  Fragments - used to build a map of which raw node to obtain
  data from क्रम each part of the ino
*/
काष्ठा jffs2_node_frag
अणु
	काष्ठा rb_node rb;
	काष्ठा jffs2_full_dnode *node; /* शून्य क्रम holes */
	uपूर्णांक32_t size;
	uपूर्णांक32_t ofs; /* The offset to which this fragment beदीर्घs */
पूर्ण;

काष्ठा jffs2_eraseblock
अणु
	काष्ठा list_head list;
	पूर्णांक bad_count;
	uपूर्णांक32_t offset;		/* of this block in the MTD */

	uपूर्णांक32_t unchecked_size;
	uपूर्णांक32_t used_size;
	uपूर्णांक32_t dirty_size;
	uपूर्णांक32_t wasted_size;
	uपूर्णांक32_t मुक्त_size;	/* Note that sector_size - मुक्त_size
				   is the address of the first मुक्त space */
	uपूर्णांक32_t allocated_refs;
	काष्ठा jffs2_raw_node_ref *first_node;
	काष्ठा jffs2_raw_node_ref *last_node;

	काष्ठा jffs2_raw_node_ref *gc_node;	/* Next node to be garbage collected */
पूर्ण;

अटल अंतरभूत पूर्णांक jffs2_blocks_use_vदो_स्मृति(काष्ठा jffs2_sb_info *c)
अणु
	वापस ((c->flash_size / c->sector_size) * माप (काष्ठा jffs2_eraseblock)) > (128 * 1024);
पूर्ण

#घोषणा ref_totlen(a, b, c) __jffs2_ref_totlen((a), (b), (c))

#घोषणा ALLOC_NORMAL	0	/* Normal allocation */
#घोषणा ALLOC_DELETION	1	/* Deletion node. Best to allow it */
#घोषणा ALLOC_GC	2	/* Space requested क्रम GC. Give it or die */
#घोषणा ALLOC_NORETRY	3	/* For jffs2_ग_लिखो_dnode: On failure, वापस -EAGAIN instead of retrying */

/* How much dirty space beक्रमe it goes on the very_dirty_list */
#घोषणा VERYसूचीTY(c, size) ((size) >= ((c)->sector_size / 2))

/* check अगर dirty space is more than 255 Byte */
#घोषणा ISसूचीTY(size) ((size) >  माप (काष्ठा jffs2_raw_inode) + JFFS2_MIN_DATA_LEN)

#घोषणा PAD(x) (((x)+3)&~3)

अटल अंतरभूत पूर्णांक jffs2_encode_dev(जोड़ jffs2_device_node *jdev, dev_t rdev)
अणु
	अगर (old_valid_dev(rdev)) अणु
		jdev->old_id = cpu_to_je16(old_encode_dev(rdev));
		वापस माप(jdev->old_id);
	पूर्ण अन्यथा अणु
		jdev->new_id = cpu_to_je32(new_encode_dev(rdev));
		वापस माप(jdev->new_id);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा jffs2_node_frag *frag_first(काष्ठा rb_root *root)
अणु
	काष्ठा rb_node *node = rb_first(root);

	अगर (!node)
		वापस शून्य;

	वापस rb_entry(node, काष्ठा jffs2_node_frag, rb);
पूर्ण

अटल अंतरभूत काष्ठा jffs2_node_frag *frag_last(काष्ठा rb_root *root)
अणु
	काष्ठा rb_node *node = rb_last(root);

	अगर (!node)
		वापस शून्य;

	वापस rb_entry(node, काष्ठा jffs2_node_frag, rb);
पूर्ण

#घोषणा frag_next(frag) rb_entry(rb_next(&(frag)->rb), काष्ठा jffs2_node_frag, rb)
#घोषणा frag_prev(frag) rb_entry(rb_prev(&(frag)->rb), काष्ठा jffs2_node_frag, rb)
#घोषणा frag_parent(frag) rb_entry(rb_parent(&(frag)->rb), काष्ठा jffs2_node_frag, rb)
#घोषणा frag_left(frag) rb_entry((frag)->rb.rb_left, काष्ठा jffs2_node_frag, rb)
#घोषणा frag_right(frag) rb_entry((frag)->rb.rb_right, काष्ठा jffs2_node_frag, rb)
#घोषणा frag_erase(frag, list) rb_erase(&frag->rb, list)

#घोषणा tn_next(tn) rb_entry(rb_next(&(tn)->rb), काष्ठा jffs2_पंचांगp_dnode_info, rb)
#घोषणा tn_prev(tn) rb_entry(rb_prev(&(tn)->rb), काष्ठा jffs2_पंचांगp_dnode_info, rb)
#घोषणा tn_parent(tn) rb_entry(rb_parent(&(tn)->rb), काष्ठा jffs2_पंचांगp_dnode_info, rb)
#घोषणा tn_left(tn) rb_entry((tn)->rb.rb_left, काष्ठा jffs2_पंचांगp_dnode_info, rb)
#घोषणा tn_right(tn) rb_entry((tn)->rb.rb_right, काष्ठा jffs2_पंचांगp_dnode_info, rb)
#घोषणा tn_erase(tn, list) rb_erase(&tn->rb, list)
#घोषणा tn_last(list) rb_entry(rb_last(list), काष्ठा jffs2_पंचांगp_dnode_info, rb)
#घोषणा tn_first(list) rb_entry(rb_first(list), काष्ठा jffs2_पंचांगp_dnode_info, rb)

/* nodelist.c */
व्योम jffs2_add_fd_to_list(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_full_dirent *new, काष्ठा jffs2_full_dirent **list);
व्योम jffs2_set_inocache_state(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *ic, पूर्णांक state);
काष्ठा jffs2_inode_cache *jffs2_get_ino_cache(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t ino);
व्योम jffs2_add_ino_cache (काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *new);
व्योम jffs2_del_ino_cache(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *old);
व्योम jffs2_मुक्त_ino_caches(काष्ठा jffs2_sb_info *c);
व्योम jffs2_मुक्त_raw_node_refs(काष्ठा jffs2_sb_info *c);
काष्ठा jffs2_node_frag *jffs2_lookup_node_frag(काष्ठा rb_root *fragtree, uपूर्णांक32_t offset);
व्योम jffs2_समाप्त_fragtree(काष्ठा rb_root *root, काष्ठा jffs2_sb_info *c_delete);
पूर्णांक jffs2_add_full_dnode_to_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f, काष्ठा jffs2_full_dnode *fn);
uपूर्णांक32_t jffs2_truncate_fragtree (काष्ठा jffs2_sb_info *c, काष्ठा rb_root *list, uपूर्णांक32_t size);
काष्ठा jffs2_raw_node_ref *jffs2_link_node_ref(काष्ठा jffs2_sb_info *c,
					       काष्ठा jffs2_eraseblock *jeb,
					       uपूर्णांक32_t ofs, uपूर्णांक32_t len,
					       काष्ठा jffs2_inode_cache *ic);
बाह्य uपूर्णांक32_t __jffs2_ref_totlen(काष्ठा jffs2_sb_info *c,
				   काष्ठा jffs2_eraseblock *jeb,
				   काष्ठा jffs2_raw_node_ref *ref);

/* nodemgmt.c */
पूर्णांक jffs2_thपढ़ो_should_wake(काष्ठा jffs2_sb_info *c);
पूर्णांक jffs2_reserve_space(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t minsize,
			uपूर्णांक32_t *len, पूर्णांक prio, uपूर्णांक32_t sumsize);
पूर्णांक jffs2_reserve_space_gc(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t minsize,
			uपूर्णांक32_t *len, uपूर्णांक32_t sumsize);
काष्ठा jffs2_raw_node_ref *jffs2_add_physical_node_ref(काष्ठा jffs2_sb_info *c, 
						       uपूर्णांक32_t ofs, uपूर्णांक32_t len,
						       काष्ठा jffs2_inode_cache *ic);
व्योम jffs2_complete_reservation(काष्ठा jffs2_sb_info *c);
व्योम jffs2_mark_node_obsolete(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_raw_node_ref *raw);

/* ग_लिखो.c */
पूर्णांक jffs2_करो_new_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f, uपूर्णांक32_t mode, काष्ठा jffs2_raw_inode *ri);

काष्ठा jffs2_full_dnode *jffs2_ग_लिखो_dnode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
					   काष्ठा jffs2_raw_inode *ri, स्थिर अचिन्हित अक्षर *data,
					   uपूर्णांक32_t datalen, पूर्णांक alloc_mode);
काष्ठा jffs2_full_dirent *jffs2_ग_लिखो_dirent(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
					     काष्ठा jffs2_raw_dirent *rd, स्थिर अचिन्हित अक्षर *name,
					     uपूर्णांक32_t namelen, पूर्णांक alloc_mode);
पूर्णांक jffs2_ग_लिखो_inode_range(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
			    काष्ठा jffs2_raw_inode *ri, अचिन्हित अक्षर *buf,
			    uपूर्णांक32_t offset, uपूर्णांक32_t ग_लिखोlen, uपूर्णांक32_t *retlen);
पूर्णांक jffs2_करो_create(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *dir_f, काष्ठा jffs2_inode_info *f,
		    काष्ठा jffs2_raw_inode *ri, स्थिर काष्ठा qstr *qstr);
पूर्णांक jffs2_करो_unlink(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *dir_f, स्थिर अक्षर *name,
		    पूर्णांक namelen, काष्ठा jffs2_inode_info *dead_f, uपूर्णांक32_t समय);
पूर्णांक jffs2_करो_link(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *dir_f, uपूर्णांक32_t ino,
		   uपूर्णांक8_t type, स्थिर अक्षर *name, पूर्णांक namelen, uपूर्णांक32_t समय);


/* पढ़ोinode.c */
पूर्णांक jffs2_करो_पढ़ो_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
			uपूर्णांक32_t ino, काष्ठा jffs2_raw_inode *latest_node);
पूर्णांक jffs2_करो_crccheck_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_cache *ic);
व्योम jffs2_करो_clear_inode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f);

/* दो_स्मृति.c */
पूर्णांक jffs2_create_slab_caches(व्योम);
व्योम jffs2_destroy_slab_caches(व्योम);

काष्ठा jffs2_full_dirent *jffs2_alloc_full_dirent(पूर्णांक namesize);
व्योम jffs2_मुक्त_full_dirent(काष्ठा jffs2_full_dirent *);
काष्ठा jffs2_full_dnode *jffs2_alloc_full_dnode(व्योम);
व्योम jffs2_मुक्त_full_dnode(काष्ठा jffs2_full_dnode *);
काष्ठा jffs2_raw_dirent *jffs2_alloc_raw_dirent(व्योम);
व्योम jffs2_मुक्त_raw_dirent(काष्ठा jffs2_raw_dirent *);
काष्ठा jffs2_raw_inode *jffs2_alloc_raw_inode(व्योम);
व्योम jffs2_मुक्त_raw_inode(काष्ठा jffs2_raw_inode *);
काष्ठा jffs2_पंचांगp_dnode_info *jffs2_alloc_पंचांगp_dnode_info(व्योम);
व्योम jffs2_मुक्त_पंचांगp_dnode_info(काष्ठा jffs2_पंचांगp_dnode_info *);
पूर्णांक jffs2_pपुनः_स्मृति_raw_node_refs(काष्ठा jffs2_sb_info *c,
				 काष्ठा jffs2_eraseblock *jeb, पूर्णांक nr);
व्योम jffs2_मुक्त_refblock(काष्ठा jffs2_raw_node_ref *);
काष्ठा jffs2_node_frag *jffs2_alloc_node_frag(व्योम);
व्योम jffs2_मुक्त_node_frag(काष्ठा jffs2_node_frag *);
काष्ठा jffs2_inode_cache *jffs2_alloc_inode_cache(व्योम);
व्योम jffs2_मुक्त_inode_cache(काष्ठा jffs2_inode_cache *);
#अगर_घोषित CONFIG_JFFS2_FS_XATTR
काष्ठा jffs2_xattr_datum *jffs2_alloc_xattr_datum(व्योम);
व्योम jffs2_मुक्त_xattr_datum(काष्ठा jffs2_xattr_datum *);
काष्ठा jffs2_xattr_ref *jffs2_alloc_xattr_ref(व्योम);
व्योम jffs2_मुक्त_xattr_ref(काष्ठा jffs2_xattr_ref *);
#पूर्ण_अगर

/* gc.c */
पूर्णांक jffs2_garbage_collect_pass(काष्ठा jffs2_sb_info *c);

/* पढ़ो.c */
पूर्णांक jffs2_पढ़ो_dnode(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
		     काष्ठा jffs2_full_dnode *fd, अचिन्हित अक्षर *buf,
		     पूर्णांक ofs, पूर्णांक len);
पूर्णांक jffs2_पढ़ो_inode_range(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f,
			   अचिन्हित अक्षर *buf, uपूर्णांक32_t offset, uपूर्णांक32_t len);
अक्षर *jffs2_getlink(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_inode_info *f);

/* scan.c */
पूर्णांक jffs2_scan_medium(काष्ठा jffs2_sb_info *c);
व्योम jffs2_rotate_lists(काष्ठा jffs2_sb_info *c);
काष्ठा jffs2_inode_cache *jffs2_scan_make_ino_cache(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t ino);
पूर्णांक jffs2_scan_classअगरy_jeb(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb);
पूर्णांक jffs2_scan_dirty_space(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb, uपूर्णांक32_t size);

/* build.c */
पूर्णांक jffs2_करो_mount_fs(काष्ठा jffs2_sb_info *c);

/* erase.c */
पूर्णांक jffs2_erase_pending_blocks(काष्ठा jffs2_sb_info *c, पूर्णांक count);
व्योम jffs2_मुक्त_jeb_node_refs(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb);

#अगर_घोषित CONFIG_JFFS2_FS_WRITEBUFFER
/* wbuf.c */
पूर्णांक jffs2_flush_wbuf_gc(काष्ठा jffs2_sb_info *c, uपूर्णांक32_t ino);
पूर्णांक jffs2_flush_wbuf_pad(काष्ठा jffs2_sb_info *c);
पूर्णांक jffs2_check_nand_cleanmarker(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb);
पूर्णांक jffs2_ग_लिखो_nand_cleanmarker(काष्ठा jffs2_sb_info *c, काष्ठा jffs2_eraseblock *jeb);
#पूर्ण_अगर

#समावेश "debug.h"

#पूर्ण_अगर /* __JFFS2_NODELIST_H__ */
