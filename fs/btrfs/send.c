<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012 Alexander Block.  All rights reserved.
 */

#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/sort.h>
#समावेश <linux/mount.h>
#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/माला.स>
#समावेश <linux/compat.h>
#समावेश <linux/crc32c.h>

#समावेश "send.h"
#समावेश "backref.h"
#समावेश "locking.h"
#समावेश "disk-io.h"
#समावेश "btrfs_inode.h"
#समावेश "transaction.h"
#समावेश "compression.h"
#समावेश "xattr.h"

/*
 * Maximum number of references an extent can have in order क्रम us to attempt to
 * issue clone operations instead of ग_लिखो operations. This currently exists to
 * aव्योम hitting limitations of the backreference walking code (taking a lot of
 * समय and using too much memory क्रम extents with large number of references).
 */
#घोषणा SEND_MAX_EXTENT_REFS	64

/*
 * A fs_path is a helper to dynamically build path names with unknown size.
 * It पुनः_स्मृतिates the पूर्णांकernal buffer on demand.
 * It allows fast adding of path elements on the right side (normal path) and
 * fast adding to the left side (reversed path). A reversed path can also be
 * unreversed अगर needed.
 */
काष्ठा fs_path अणु
	जोड़ अणु
		काष्ठा अणु
			अक्षर *start;
			अक्षर *end;

			अक्षर *buf;
			अचिन्हित लघु buf_len:15;
			अचिन्हित लघु reversed:1;
			अक्षर अंतरभूत_buf[];
		पूर्ण;
		/*
		 * Average path length करोes not exceed 200 bytes, we'll have
		 * better packing in the slab and higher chance to satisfy
		 * a allocation later during send.
		 */
		अक्षर pad[256];
	पूर्ण;
पूर्ण;
#घोषणा FS_PATH_INLINE_SIZE \
	(माप(काष्ठा fs_path) - दुरत्व(काष्ठा fs_path, अंतरभूत_buf))


/* reused क्रम each extent */
काष्ठा clone_root अणु
	काष्ठा btrfs_root *root;
	u64 ino;
	u64 offset;

	u64 found_refs;
पूर्ण;

#घोषणा SEND_CTX_MAX_NAME_CACHE_SIZE 128
#घोषणा SEND_CTX_NAME_CACHE_CLEAN_SIZE (SEND_CTX_MAX_NAME_CACHE_SIZE * 2)

काष्ठा send_ctx अणु
	काष्ठा file *send_filp;
	loff_t send_off;
	अक्षर *send_buf;
	u32 send_size;
	u32 send_max_size;
	u64 total_send_size;
	u64 cmd_send_size[BTRFS_SEND_C_MAX + 1];
	u64 flags;	/* 'flags' member of btrfs_ioctl_send_args is u64 */

	काष्ठा btrfs_root *send_root;
	काष्ठा btrfs_root *parent_root;
	काष्ठा clone_root *clone_roots;
	पूर्णांक clone_roots_cnt;

	/* current state of the compare_tree call */
	काष्ठा btrfs_path *left_path;
	काष्ठा btrfs_path *right_path;
	काष्ठा btrfs_key *cmp_key;

	/*
	 * infos of the currently processed inode. In हाल of deleted inodes,
	 * these are the values from the deleted inode.
	 */
	u64 cur_ino;
	u64 cur_inode_gen;
	पूर्णांक cur_inode_new;
	पूर्णांक cur_inode_new_gen;
	पूर्णांक cur_inode_deleted;
	u64 cur_inode_size;
	u64 cur_inode_mode;
	u64 cur_inode_rdev;
	u64 cur_inode_last_extent;
	u64 cur_inode_next_ग_लिखो_offset;
	bool ignore_cur_inode;

	u64 send_progress;

	काष्ठा list_head new_refs;
	काष्ठा list_head deleted_refs;

	काष्ठा radix_tree_root name_cache;
	काष्ठा list_head name_cache_list;
	पूर्णांक name_cache_size;

	काष्ठा file_ra_state ra;

	/*
	 * We process inodes by their increasing order, so अगर beक्रमe an
	 * incremental send we reverse the parent/child relationship of
	 * directories such that a directory with a lower inode number was
	 * the parent of a directory with a higher inode number, and the one
	 * becoming the new parent got नामd too, we can't नाम/move the
	 * directory with lower inode number when we finish processing it - we
	 * must process the directory with higher inode number first, then
	 * नाम/move it and then नाम/move the directory with lower inode
	 * number. Example follows.
	 *
	 * Tree state when the first send was perक्रमmed:
	 *
	 * .
	 * |-- a                   (ino 257)
	 *     |-- b               (ino 258)
	 *         |
	 *         |
	 *         |-- c           (ino 259)
	 *         |   |-- d       (ino 260)
	 *         |
	 *         |-- c2          (ino 261)
	 *
	 * Tree state when the second (incremental) send is perक्रमmed:
	 *
	 * .
	 * |-- a                   (ino 257)
	 *     |-- b               (ino 258)
	 *         |-- c2          (ino 261)
	 *             |-- d2      (ino 260)
	 *                 |-- cc  (ino 259)
	 *
	 * The sequence of steps that lead to the second state was:
	 *
	 * mv /a/b/c/d /a/b/c2/d2
	 * mv /a/b/c /a/b/c2/d2/cc
	 *
	 * "c" has lower inode number, but we can't move it (2nd mv operation)
	 * beक्रमe we move "d", which has higher inode number.
	 *
	 * So we just memorize which move/नाम operations must be perक्रमmed
	 * later when their respective parent is processed and moved/नामd.
	 */

	/* Indexed by parent directory inode number. */
	काष्ठा rb_root pending_dir_moves;

	/*
	 * Reverse index, indexed by the inode number of a directory that
	 * is रुकोing क्रम the move/नाम of its immediate parent beक्रमe its
	 * own move/नाम can be perक्रमmed.
	 */
	काष्ठा rb_root रुकोing_dir_moves;

	/*
	 * A directory that is going to be rm'ed might have a child directory
	 * which is in the pending directory moves index above. In this हाल,
	 * the directory can only be हटाओd after the move/नाम of its child
	 * is perक्रमmed. Example:
	 *
	 * Parent snapshot:
	 *
	 * .                        (ino 256)
	 * |-- a/                   (ino 257)
	 *     |-- b/               (ino 258)
	 *         |-- c/           (ino 259)
	 *         |   |-- x/       (ino 260)
	 *         |
	 *         |-- y/           (ino 261)
	 *
	 * Send snapshot:
	 *
	 * .                        (ino 256)
	 * |-- a/                   (ino 257)
	 *     |-- b/               (ino 258)
	 *         |-- YY/          (ino 261)
	 *              |-- x/      (ino 260)
	 *
	 * Sequence of steps that lead to the send snapshot:
	 * rm -f /a/b/c/foo.txt
	 * mv /a/b/y /a/b/YY
	 * mv /a/b/c/x /a/b/YY
	 * सूची_हटाओ /a/b/c
	 *
	 * When the child is processed, its move/नाम is delayed until its
	 * parent is processed (as explained above), but all other operations
	 * like update uबार, chown, chgrp, etc, are perक्रमmed and the paths
	 * that it uses क्रम those operations must use the orphanized name of
	 * its parent (the directory we're going to rm later), so we need to
	 * memorize that name.
	 *
	 * Indexed by the inode number of the directory to be deleted.
	 */
	काष्ठा rb_root orphan_dirs;
पूर्ण;

काष्ठा pending_dir_move अणु
	काष्ठा rb_node node;
	काष्ठा list_head list;
	u64 parent_ino;
	u64 ino;
	u64 gen;
	काष्ठा list_head update_refs;
पूर्ण;

काष्ठा रुकोing_dir_move अणु
	काष्ठा rb_node node;
	u64 ino;
	/*
	 * There might be some directory that could not be हटाओd because it
	 * was रुकोing क्रम this directory inode to be moved first. Thereक्रमe
	 * after this directory is moved, we can try to सूची_हटाओ the ino सूची_हटाओ_ino.
	 */
	u64 सूची_हटाओ_ino;
	u64 सूची_हटाओ_gen;
	bool orphanized;
पूर्ण;

काष्ठा orphan_dir_info अणु
	काष्ठा rb_node node;
	u64 ino;
	u64 gen;
	u64 last_dir_index_offset;
पूर्ण;

काष्ठा name_cache_entry अणु
	काष्ठा list_head list;
	/*
	 * radix_tree has only 32bit entries but we need to handle 64bit inums.
	 * We use the lower 32bit of the 64bit inum to store it in the tree. If
	 * more then one inum would fall पूर्णांकo the same entry, we use radix_list
	 * to store the additional entries. radix_list is also used to store
	 * entries where two entries have the same inum but dअगरferent
	 * generations.
	 */
	काष्ठा list_head radix_list;
	u64 ino;
	u64 gen;
	u64 parent_ino;
	u64 parent_gen;
	पूर्णांक ret;
	पूर्णांक need_later_update;
	पूर्णांक name_len;
	अक्षर name[];
पूर्ण;

#घोषणा ADVANCE							1
#घोषणा ADVANCE_ONLY_NEXT					-1

क्रमागत btrfs_compare_tree_result अणु
	BTRFS_COMPARE_TREE_NEW,
	BTRFS_COMPARE_TREE_DELETED,
	BTRFS_COMPARE_TREE_CHANGED,
	BTRFS_COMPARE_TREE_SAME,
पूर्ण;

__cold
अटल व्योम inconsistent_snapshot_error(काष्ठा send_ctx *sctx,
					क्रमागत btrfs_compare_tree_result result,
					स्थिर अक्षर *what)
अणु
	स्थिर अक्षर *result_string;

	चयन (result) अणु
	हाल BTRFS_COMPARE_TREE_NEW:
		result_string = "new";
		अवरोध;
	हाल BTRFS_COMPARE_TREE_DELETED:
		result_string = "deleted";
		अवरोध;
	हाल BTRFS_COMPARE_TREE_CHANGED:
		result_string = "updated";
		अवरोध;
	हाल BTRFS_COMPARE_TREE_SAME:
		ASSERT(0);
		result_string = "unchanged";
		अवरोध;
	शेष:
		ASSERT(0);
		result_string = "unexpected";
	पूर्ण

	btrfs_err(sctx->send_root->fs_info,
		  "Send: inconsistent snapshot, found %s %s for inode %llu without updated inode item, send root is %llu, parent root is %llu",
		  result_string, what, sctx->cmp_key->objectid,
		  sctx->send_root->root_key.objectid,
		  (sctx->parent_root ?
		   sctx->parent_root->root_key.objectid : 0));
पूर्ण

अटल पूर्णांक is_रुकोing_क्रम_move(काष्ठा send_ctx *sctx, u64 ino);

अटल काष्ठा रुकोing_dir_move *
get_रुकोing_dir_move(काष्ठा send_ctx *sctx, u64 ino);

अटल पूर्णांक is_रुकोing_क्रम_rm(काष्ठा send_ctx *sctx, u64 dir_ino, u64 gen);

अटल पूर्णांक need_send_hole(काष्ठा send_ctx *sctx)
अणु
	वापस (sctx->parent_root && !sctx->cur_inode_new &&
		!sctx->cur_inode_new_gen && !sctx->cur_inode_deleted &&
		S_ISREG(sctx->cur_inode_mode));
पूर्ण

अटल व्योम fs_path_reset(काष्ठा fs_path *p)
अणु
	अगर (p->reversed) अणु
		p->start = p->buf + p->buf_len - 1;
		p->end = p->start;
		*p->start = 0;
	पूर्ण अन्यथा अणु
		p->start = p->buf;
		p->end = p->start;
		*p->start = 0;
	पूर्ण
पूर्ण

अटल काष्ठा fs_path *fs_path_alloc(व्योम)
अणु
	काष्ठा fs_path *p;

	p = kदो_स्मृति(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस शून्य;
	p->reversed = 0;
	p->buf = p->अंतरभूत_buf;
	p->buf_len = FS_PATH_INLINE_SIZE;
	fs_path_reset(p);
	वापस p;
पूर्ण

अटल काष्ठा fs_path *fs_path_alloc_reversed(व्योम)
अणु
	काष्ठा fs_path *p;

	p = fs_path_alloc();
	अगर (!p)
		वापस शून्य;
	p->reversed = 1;
	fs_path_reset(p);
	वापस p;
पूर्ण

अटल व्योम fs_path_मुक्त(काष्ठा fs_path *p)
अणु
	अगर (!p)
		वापस;
	अगर (p->buf != p->अंतरभूत_buf)
		kमुक्त(p->buf);
	kमुक्त(p);
पूर्ण

अटल पूर्णांक fs_path_len(काष्ठा fs_path *p)
अणु
	वापस p->end - p->start;
पूर्ण

अटल पूर्णांक fs_path_ensure_buf(काष्ठा fs_path *p, पूर्णांक len)
अणु
	अक्षर *पंचांगp_buf;
	पूर्णांक path_len;
	पूर्णांक old_buf_len;

	len++;

	अगर (p->buf_len >= len)
		वापस 0;

	अगर (len > PATH_MAX) अणु
		WARN_ON(1);
		वापस -ENOMEM;
	पूर्ण

	path_len = p->end - p->start;
	old_buf_len = p->buf_len;

	/*
	 * First समय the अंतरभूत_buf करोes not suffice
	 */
	अगर (p->buf == p->अंतरभूत_buf) अणु
		पंचांगp_buf = kदो_स्मृति(len, GFP_KERNEL);
		अगर (पंचांगp_buf)
			स_नकल(पंचांगp_buf, p->buf, old_buf_len);
	पूर्ण अन्यथा अणु
		पंचांगp_buf = kपुनः_स्मृति(p->buf, len, GFP_KERNEL);
	पूर्ण
	अगर (!पंचांगp_buf)
		वापस -ENOMEM;
	p->buf = पंचांगp_buf;
	/*
	 * The real size of the buffer is bigger, this will let the fast path
	 * happen most of the समय
	 */
	p->buf_len = ksize(p->buf);

	अगर (p->reversed) अणु
		पंचांगp_buf = p->buf + old_buf_len - path_len - 1;
		p->end = p->buf + p->buf_len - 1;
		p->start = p->end - path_len;
		स_हटाओ(p->start, पंचांगp_buf, path_len + 1);
	पूर्ण अन्यथा अणु
		p->start = p->buf;
		p->end = p->start + path_len;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fs_path_prepare_क्रम_add(काष्ठा fs_path *p, पूर्णांक name_len,
				   अक्षर **prepared)
अणु
	पूर्णांक ret;
	पूर्णांक new_len;

	new_len = p->end - p->start + name_len;
	अगर (p->start != p->end)
		new_len++;
	ret = fs_path_ensure_buf(p, new_len);
	अगर (ret < 0)
		जाओ out;

	अगर (p->reversed) अणु
		अगर (p->start != p->end)
			*--p->start = '/';
		p->start -= name_len;
		*prepared = p->start;
	पूर्ण अन्यथा अणु
		अगर (p->start != p->end)
			*p->end++ = '/';
		*prepared = p->end;
		p->end += name_len;
		*p->end = 0;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक fs_path_add(काष्ठा fs_path *p, स्थिर अक्षर *name, पूर्णांक name_len)
अणु
	पूर्णांक ret;
	अक्षर *prepared;

	ret = fs_path_prepare_क्रम_add(p, name_len, &prepared);
	अगर (ret < 0)
		जाओ out;
	स_नकल(prepared, name, name_len);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक fs_path_add_path(काष्ठा fs_path *p, काष्ठा fs_path *p2)
अणु
	पूर्णांक ret;
	अक्षर *prepared;

	ret = fs_path_prepare_क्रम_add(p, p2->end - p2->start, &prepared);
	अगर (ret < 0)
		जाओ out;
	स_नकल(prepared, p2->start, p2->end - p2->start);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक fs_path_add_from_extent_buffer(काष्ठा fs_path *p,
					  काष्ठा extent_buffer *eb,
					  अचिन्हित दीर्घ off, पूर्णांक len)
अणु
	पूर्णांक ret;
	अक्षर *prepared;

	ret = fs_path_prepare_क्रम_add(p, len, &prepared);
	अगर (ret < 0)
		जाओ out;

	पढ़ो_extent_buffer(eb, prepared, off, len);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक fs_path_copy(काष्ठा fs_path *p, काष्ठा fs_path *from)
अणु
	पूर्णांक ret;

	p->reversed = from->reversed;
	fs_path_reset(p);

	ret = fs_path_add_path(p, from);

	वापस ret;
पूर्ण


अटल व्योम fs_path_unreverse(काष्ठा fs_path *p)
अणु
	अक्षर *पंचांगp;
	पूर्णांक len;

	अगर (!p->reversed)
		वापस;

	पंचांगp = p->start;
	len = p->end - p->start;
	p->start = p->buf;
	p->end = p->start + len;
	स_हटाओ(p->start, पंचांगp, len + 1);
	p->reversed = 0;
पूर्ण

अटल काष्ठा btrfs_path *alloc_path_क्रम_send(व्योम)
अणु
	काष्ठा btrfs_path *path;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस शून्य;
	path->search_commit_root = 1;
	path->skip_locking = 1;
	path->need_commit_sem = 1;
	वापस path;
पूर्ण

अटल पूर्णांक ग_लिखो_buf(काष्ठा file *filp, स्थिर व्योम *buf, u32 len, loff_t *off)
अणु
	पूर्णांक ret;
	u32 pos = 0;

	जबतक (pos < len) अणु
		ret = kernel_ग_लिखो(filp, buf + pos, len - pos, off);
		/* TODO handle that correctly */
		/*अगर (ret == -ERESTARTSYS) अणु
			जारी;
		पूर्ण*/
		अगर (ret < 0)
			वापस ret;
		अगर (ret == 0) अणु
			वापस -EIO;
		पूर्ण
		pos += ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tlv_put(काष्ठा send_ctx *sctx, u16 attr, स्थिर व्योम *data, पूर्णांक len)
अणु
	काष्ठा btrfs_tlv_header *hdr;
	पूर्णांक total_len = माप(*hdr) + len;
	पूर्णांक left = sctx->send_max_size - sctx->send_size;

	अगर (unlikely(left < total_len))
		वापस -EOVERFLOW;

	hdr = (काष्ठा btrfs_tlv_header *) (sctx->send_buf + sctx->send_size);
	put_unaligned_le16(attr, &hdr->tlv_type);
	put_unaligned_le16(len, &hdr->tlv_len);
	स_नकल(hdr + 1, data, len);
	sctx->send_size += total_len;

	वापस 0;
पूर्ण

#घोषणा TLV_PUT_DEFINE_INT(bits) \
	अटल पूर्णांक tlv_put_u##bits(काष्ठा send_ctx *sctx,	 	\
			u##bits attr, u##bits value)			\
	अणु								\
		__le##bits __पंचांगp = cpu_to_le##bits(value);		\
		वापस tlv_put(sctx, attr, &__पंचांगp, माप(__पंचांगp));	\
	पूर्ण

TLV_PUT_DEFINE_INT(64)

अटल पूर्णांक tlv_put_string(काष्ठा send_ctx *sctx, u16 attr,
			  स्थिर अक्षर *str, पूर्णांक len)
अणु
	अगर (len == -1)
		len = म_माप(str);
	वापस tlv_put(sctx, attr, str, len);
पूर्ण

अटल पूर्णांक tlv_put_uuid(काष्ठा send_ctx *sctx, u16 attr,
			स्थिर u8 *uuid)
अणु
	वापस tlv_put(sctx, attr, uuid, BTRFS_UUID_SIZE);
पूर्ण

अटल पूर्णांक tlv_put_btrfs_बारpec(काष्ठा send_ctx *sctx, u16 attr,
				  काष्ठा extent_buffer *eb,
				  काष्ठा btrfs_बारpec *ts)
अणु
	काष्ठा btrfs_बारpec bts;
	पढ़ो_extent_buffer(eb, &bts, (अचिन्हित दीर्घ)ts, माप(bts));
	वापस tlv_put(sctx, attr, &bts, माप(bts));
पूर्ण


#घोषणा TLV_PUT(sctx, attrtype, data, attrlen) \
	करो अणु \
		ret = tlv_put(sctx, attrtype, data, attrlen); \
		अगर (ret < 0) \
			जाओ tlv_put_failure; \
	पूर्ण जबतक (0)

#घोषणा TLV_PUT_INT(sctx, attrtype, bits, value) \
	करो अणु \
		ret = tlv_put_u##bits(sctx, attrtype, value); \
		अगर (ret < 0) \
			जाओ tlv_put_failure; \
	पूर्ण जबतक (0)

#घोषणा TLV_PUT_U8(sctx, attrtype, data) TLV_PUT_INT(sctx, attrtype, 8, data)
#घोषणा TLV_PUT_U16(sctx, attrtype, data) TLV_PUT_INT(sctx, attrtype, 16, data)
#घोषणा TLV_PUT_U32(sctx, attrtype, data) TLV_PUT_INT(sctx, attrtype, 32, data)
#घोषणा TLV_PUT_U64(sctx, attrtype, data) TLV_PUT_INT(sctx, attrtype, 64, data)
#घोषणा TLV_PUT_STRING(sctx, attrtype, str, len) \
	करो अणु \
		ret = tlv_put_string(sctx, attrtype, str, len); \
		अगर (ret < 0) \
			जाओ tlv_put_failure; \
	पूर्ण जबतक (0)
#घोषणा TLV_PUT_PATH(sctx, attrtype, p) \
	करो अणु \
		ret = tlv_put_string(sctx, attrtype, p->start, \
			p->end - p->start); \
		अगर (ret < 0) \
			जाओ tlv_put_failure; \
	पूर्ण जबतक(0)
#घोषणा TLV_PUT_UUID(sctx, attrtype, uuid) \
	करो अणु \
		ret = tlv_put_uuid(sctx, attrtype, uuid); \
		अगर (ret < 0) \
			जाओ tlv_put_failure; \
	पूर्ण जबतक (0)
#घोषणा TLV_PUT_BTRFS_TIMESPEC(sctx, attrtype, eb, ts) \
	करो अणु \
		ret = tlv_put_btrfs_बारpec(sctx, attrtype, eb, ts); \
		अगर (ret < 0) \
			जाओ tlv_put_failure; \
	पूर्ण जबतक (0)

अटल पूर्णांक send_header(काष्ठा send_ctx *sctx)
अणु
	काष्ठा btrfs_stream_header hdr;

	म_नकल(hdr.magic, BTRFS_SEND_STREAM_MAGIC);
	hdr.version = cpu_to_le32(BTRFS_SEND_STREAM_VERSION);

	वापस ग_लिखो_buf(sctx->send_filp, &hdr, माप(hdr),
					&sctx->send_off);
पूर्ण

/*
 * For each command/item we want to send to userspace, we call this function.
 */
अटल पूर्णांक begin_cmd(काष्ठा send_ctx *sctx, पूर्णांक cmd)
अणु
	काष्ठा btrfs_cmd_header *hdr;

	अगर (WARN_ON(!sctx->send_buf))
		वापस -EINVAL;

	BUG_ON(sctx->send_size);

	sctx->send_size += माप(*hdr);
	hdr = (काष्ठा btrfs_cmd_header *)sctx->send_buf;
	put_unaligned_le16(cmd, &hdr->cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक send_cmd(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_cmd_header *hdr;
	u32 crc;

	hdr = (काष्ठा btrfs_cmd_header *)sctx->send_buf;
	put_unaligned_le32(sctx->send_size - माप(*hdr), &hdr->len);
	put_unaligned_le32(0, &hdr->crc);

	crc = btrfs_crc32c(0, (अचिन्हित अक्षर *)sctx->send_buf, sctx->send_size);
	put_unaligned_le32(crc, &hdr->crc);

	ret = ग_लिखो_buf(sctx->send_filp, sctx->send_buf, sctx->send_size,
					&sctx->send_off);

	sctx->total_send_size += sctx->send_size;
	sctx->cmd_send_size[get_unaligned_le16(&hdr->cmd)] += sctx->send_size;
	sctx->send_size = 0;

	वापस ret;
पूर्ण

/*
 * Sends a move inकाष्ठाion to user space
 */
अटल पूर्णांक send_नाम(काष्ठा send_ctx *sctx,
		     काष्ठा fs_path *from, काष्ठा fs_path *to)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	पूर्णांक ret;

	btrfs_debug(fs_info, "send_rename %s -> %s", from->start, to->start);

	ret = begin_cmd(sctx, BTRFS_SEND_C_RENAME);
	अगर (ret < 0)
		जाओ out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, from);
	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH_TO, to);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	वापस ret;
पूर्ण

/*
 * Sends a link inकाष्ठाion to user space
 */
अटल पूर्णांक send_link(काष्ठा send_ctx *sctx,
		     काष्ठा fs_path *path, काष्ठा fs_path *lnk)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	पूर्णांक ret;

	btrfs_debug(fs_info, "send_link %s -> %s", path->start, lnk->start);

	ret = begin_cmd(sctx, BTRFS_SEND_C_LINK);
	अगर (ret < 0)
		जाओ out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, path);
	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH_LINK, lnk);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	वापस ret;
पूर्ण

/*
 * Sends an unlink inकाष्ठाion to user space
 */
अटल पूर्णांक send_unlink(काष्ठा send_ctx *sctx, काष्ठा fs_path *path)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	पूर्णांक ret;

	btrfs_debug(fs_info, "send_unlink %s", path->start);

	ret = begin_cmd(sctx, BTRFS_SEND_C_UNLINK);
	अगर (ret < 0)
		जाओ out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, path);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	वापस ret;
पूर्ण

/*
 * Sends a सूची_हटाओ inकाष्ठाion to user space
 */
अटल पूर्णांक send_सूची_हटाओ(काष्ठा send_ctx *sctx, काष्ठा fs_path *path)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	पूर्णांक ret;

	btrfs_debug(fs_info, "send_rmdir %s", path->start);

	ret = begin_cmd(sctx, BTRFS_SEND_C_RMसूची);
	अगर (ret < 0)
		जाओ out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, path);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	वापस ret;
पूर्ण

/*
 * Helper function to retrieve some fields from an inode item.
 */
अटल पूर्णांक __get_inode_info(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
			  u64 ino, u64 *size, u64 *gen, u64 *mode, u64 *uid,
			  u64 *gid, u64 *rdev)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_inode_item *ii;
	काष्ठा btrfs_key key;

	key.objectid = ino;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret) अणु
		अगर (ret > 0)
			ret = -ENOENT;
		वापस ret;
	पूर्ण

	ii = btrfs_item_ptr(path->nodes[0], path->slots[0],
			काष्ठा btrfs_inode_item);
	अगर (size)
		*size = btrfs_inode_size(path->nodes[0], ii);
	अगर (gen)
		*gen = btrfs_inode_generation(path->nodes[0], ii);
	अगर (mode)
		*mode = btrfs_inode_mode(path->nodes[0], ii);
	अगर (uid)
		*uid = btrfs_inode_uid(path->nodes[0], ii);
	अगर (gid)
		*gid = btrfs_inode_gid(path->nodes[0], ii);
	अगर (rdev)
		*rdev = btrfs_inode_rdev(path->nodes[0], ii);

	वापस ret;
पूर्ण

अटल पूर्णांक get_inode_info(काष्ठा btrfs_root *root,
			  u64 ino, u64 *size, u64 *gen,
			  u64 *mode, u64 *uid, u64 *gid,
			  u64 *rdev)
अणु
	काष्ठा btrfs_path *path;
	पूर्णांक ret;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;
	ret = __get_inode_info(root, path, ino, size, gen, mode, uid, gid,
			       rdev);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

प्रकार पूर्णांक (*iterate_inode_ref_t)(पूर्णांक num, u64 dir, पूर्णांक index,
				   काष्ठा fs_path *p,
				   व्योम *ctx);

/*
 * Helper function to iterate the entries in ONE btrfs_inode_ref or
 * btrfs_inode_extref.
 * The iterate callback may वापस a non zero value to stop iteration. This can
 * be a negative value क्रम error codes or 1 to simply stop it.
 *
 * path must poपूर्णांक to the INODE_REF or INODE_EXTREF when called.
 */
अटल पूर्णांक iterate_inode_ref(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
			     काष्ठा btrfs_key *found_key, पूर्णांक resolve,
			     iterate_inode_ref_t iterate, व्योम *ctx)
अणु
	काष्ठा extent_buffer *eb = path->nodes[0];
	काष्ठा btrfs_item *item;
	काष्ठा btrfs_inode_ref *iref;
	काष्ठा btrfs_inode_extref *extref;
	काष्ठा btrfs_path *पंचांगp_path;
	काष्ठा fs_path *p;
	u32 cur = 0;
	u32 total;
	पूर्णांक slot = path->slots[0];
	u32 name_len;
	अक्षर *start;
	पूर्णांक ret = 0;
	पूर्णांक num = 0;
	पूर्णांक index;
	u64 dir;
	अचिन्हित दीर्घ name_off;
	अचिन्हित दीर्घ elem_size;
	अचिन्हित दीर्घ ptr;

	p = fs_path_alloc_reversed();
	अगर (!p)
		वापस -ENOMEM;

	पंचांगp_path = alloc_path_क्रम_send();
	अगर (!पंचांगp_path) अणु
		fs_path_मुक्त(p);
		वापस -ENOMEM;
	पूर्ण


	अगर (found_key->type == BTRFS_INODE_REF_KEY) अणु
		ptr = (अचिन्हित दीर्घ)btrfs_item_ptr(eb, slot,
						    काष्ठा btrfs_inode_ref);
		item = btrfs_item_nr(slot);
		total = btrfs_item_size(eb, item);
		elem_size = माप(*iref);
	पूर्ण अन्यथा अणु
		ptr = btrfs_item_ptr_offset(eb, slot);
		total = btrfs_item_size_nr(eb, slot);
		elem_size = माप(*extref);
	पूर्ण

	जबतक (cur < total) अणु
		fs_path_reset(p);

		अगर (found_key->type == BTRFS_INODE_REF_KEY) अणु
			iref = (काष्ठा btrfs_inode_ref *)(ptr + cur);
			name_len = btrfs_inode_ref_name_len(eb, iref);
			name_off = (अचिन्हित दीर्घ)(iref + 1);
			index = btrfs_inode_ref_index(eb, iref);
			dir = found_key->offset;
		पूर्ण अन्यथा अणु
			extref = (काष्ठा btrfs_inode_extref *)(ptr + cur);
			name_len = btrfs_inode_extref_name_len(eb, extref);
			name_off = (अचिन्हित दीर्घ)&extref->name;
			index = btrfs_inode_extref_index(eb, extref);
			dir = btrfs_inode_extref_parent(eb, extref);
		पूर्ण

		अगर (resolve) अणु
			start = btrfs_ref_to_path(root, पंचांगp_path, name_len,
						  name_off, eb, dir,
						  p->buf, p->buf_len);
			अगर (IS_ERR(start)) अणु
				ret = PTR_ERR(start);
				जाओ out;
			पूर्ण
			अगर (start < p->buf) अणु
				/* overflow , try again with larger buffer */
				ret = fs_path_ensure_buf(p,
						p->buf_len + p->buf - start);
				अगर (ret < 0)
					जाओ out;
				start = btrfs_ref_to_path(root, पंचांगp_path,
							  name_len, name_off,
							  eb, dir,
							  p->buf, p->buf_len);
				अगर (IS_ERR(start)) अणु
					ret = PTR_ERR(start);
					जाओ out;
				पूर्ण
				BUG_ON(start < p->buf);
			पूर्ण
			p->start = start;
		पूर्ण अन्यथा अणु
			ret = fs_path_add_from_extent_buffer(p, eb, name_off,
							     name_len);
			अगर (ret < 0)
				जाओ out;
		पूर्ण

		cur += elem_size + name_len;
		ret = iterate(num, dir, index, p, ctx);
		अगर (ret)
			जाओ out;
		num++;
	पूर्ण

out:
	btrfs_मुक्त_path(पंचांगp_path);
	fs_path_मुक्त(p);
	वापस ret;
पूर्ण

प्रकार पूर्णांक (*iterate_dir_item_t)(पूर्णांक num, काष्ठा btrfs_key *di_key,
				  स्थिर अक्षर *name, पूर्णांक name_len,
				  स्थिर अक्षर *data, पूर्णांक data_len,
				  u8 type, व्योम *ctx);

/*
 * Helper function to iterate the entries in ONE btrfs_dir_item.
 * The iterate callback may वापस a non zero value to stop iteration. This can
 * be a negative value क्रम error codes or 1 to simply stop it.
 *
 * path must poपूर्णांक to the dir item when called.
 */
अटल पूर्णांक iterate_dir_item(काष्ठा btrfs_root *root, काष्ठा btrfs_path *path,
			    iterate_dir_item_t iterate, व्योम *ctx)
अणु
	पूर्णांक ret = 0;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_item *item;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_key di_key;
	अक्षर *buf = शून्य;
	पूर्णांक buf_len;
	u32 name_len;
	u32 data_len;
	u32 cur;
	u32 len;
	u32 total;
	पूर्णांक slot;
	पूर्णांक num;
	u8 type;

	/*
	 * Start with a small buffer (1 page). If later we end up needing more
	 * space, which can happen क्रम xattrs on a fs with a leaf size greater
	 * then the page size, attempt to increase the buffer. Typically xattr
	 * values are small.
	 */
	buf_len = PATH_MAX;
	buf = kदो_स्मृति(buf_len, GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	eb = path->nodes[0];
	slot = path->slots[0];
	item = btrfs_item_nr(slot);
	di = btrfs_item_ptr(eb, slot, काष्ठा btrfs_dir_item);
	cur = 0;
	len = 0;
	total = btrfs_item_size(eb, item);

	num = 0;
	जबतक (cur < total) अणु
		name_len = btrfs_dir_name_len(eb, di);
		data_len = btrfs_dir_data_len(eb, di);
		type = btrfs_dir_type(eb, di);
		btrfs_dir_item_key_to_cpu(eb, di, &di_key);

		अगर (type == BTRFS_FT_XATTR) अणु
			अगर (name_len > XATTR_NAME_MAX) अणु
				ret = -ENAMETOOLONG;
				जाओ out;
			पूर्ण
			अगर (name_len + data_len >
					BTRFS_MAX_XATTR_SIZE(root->fs_info)) अणु
				ret = -E2BIG;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Path too दीर्घ
			 */
			अगर (name_len + data_len > PATH_MAX) अणु
				ret = -ENAMETOOLONG;
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (name_len + data_len > buf_len) अणु
			buf_len = name_len + data_len;
			अगर (is_vदो_स्मृति_addr(buf)) अणु
				vमुक्त(buf);
				buf = शून्य;
			पूर्ण अन्यथा अणु
				अक्षर *पंचांगp = kपुनः_स्मृति(buf, buf_len,
						GFP_KERNEL | __GFP_NOWARN);

				अगर (!पंचांगp)
					kमुक्त(buf);
				buf = पंचांगp;
			पूर्ण
			अगर (!buf) अणु
				buf = kvदो_स्मृति(buf_len, GFP_KERNEL);
				अगर (!buf) अणु
					ret = -ENOMEM;
					जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण

		पढ़ो_extent_buffer(eb, buf, (अचिन्हित दीर्घ)(di + 1),
				name_len + data_len);

		len = माप(*di) + name_len + data_len;
		di = (काष्ठा btrfs_dir_item *)((अक्षर *)di + len);
		cur += len;

		ret = iterate(num, &di_key, buf, name_len, buf + name_len,
				data_len, type, ctx);
		अगर (ret < 0)
			जाओ out;
		अगर (ret) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		num++;
	पूर्ण

out:
	kvमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक __copy_first_ref(पूर्णांक num, u64 dir, पूर्णांक index,
			    काष्ठा fs_path *p, व्योम *ctx)
अणु
	पूर्णांक ret;
	काष्ठा fs_path *pt = ctx;

	ret = fs_path_copy(pt, p);
	अगर (ret < 0)
		वापस ret;

	/* we want the first only */
	वापस 1;
पूर्ण

/*
 * Retrieve the first path of an inode. If an inode has more then one
 * ref/hardlink, this is ignored.
 */
अटल पूर्णांक get_inode_path(काष्ठा btrfs_root *root,
			  u64 ino, काष्ठा fs_path *path)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key, found_key;
	काष्ठा btrfs_path *p;

	p = alloc_path_क्रम_send();
	अगर (!p)
		वापस -ENOMEM;

	fs_path_reset(path);

	key.objectid = ino;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = 0;

	ret = btrfs_search_slot_क्रम_पढ़ो(root, &key, p, 1, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret) अणु
		ret = 1;
		जाओ out;
	पूर्ण
	btrfs_item_key_to_cpu(p->nodes[0], &found_key, p->slots[0]);
	अगर (found_key.objectid != ino ||
	    (found_key.type != BTRFS_INODE_REF_KEY &&
	     found_key.type != BTRFS_INODE_EXTREF_KEY)) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	ret = iterate_inode_ref(root, p, &found_key, 1,
				__copy_first_ref, path);
	अगर (ret < 0)
		जाओ out;
	ret = 0;

out:
	btrfs_मुक्त_path(p);
	वापस ret;
पूर्ण

काष्ठा backref_ctx अणु
	काष्ठा send_ctx *sctx;

	/* number of total found references */
	u64 found;

	/*
	 * used क्रम clones found in send_root. clones found behind cur_objectid
	 * and cur_offset are not considered as allowed clones.
	 */
	u64 cur_objectid;
	u64 cur_offset;

	/* may be truncated in हाल it's the last extent in a file */
	u64 extent_len;

	/* Just to check क्रम bugs in backref resolving */
	पूर्णांक found_itself;
पूर्ण;

अटल पूर्णांक __clone_root_cmp_द्वा_खोज(स्थिर व्योम *key, स्थिर व्योम *elt)
अणु
	u64 root = (u64)(uपूर्णांकptr_t)key;
	काष्ठा clone_root *cr = (काष्ठा clone_root *)elt;

	अगर (root < cr->root->root_key.objectid)
		वापस -1;
	अगर (root > cr->root->root_key.objectid)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __clone_root_cmp_sort(स्थिर व्योम *e1, स्थिर व्योम *e2)
अणु
	काष्ठा clone_root *cr1 = (काष्ठा clone_root *)e1;
	काष्ठा clone_root *cr2 = (काष्ठा clone_root *)e2;

	अगर (cr1->root->root_key.objectid < cr2->root->root_key.objectid)
		वापस -1;
	अगर (cr1->root->root_key.objectid > cr2->root->root_key.objectid)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * Called क्रम every backref that is found क्रम the current extent.
 * Results are collected in sctx->clone_roots->ino/offset/found_refs
 */
अटल पूर्णांक __iterate_backrefs(u64 ino, u64 offset, u64 root, व्योम *ctx_)
अणु
	काष्ठा backref_ctx *bctx = ctx_;
	काष्ठा clone_root *found;

	/* First check अगर the root is in the list of accepted clone sources */
	found = द्वा_खोज((व्योम *)(uपूर्णांकptr_t)root, bctx->sctx->clone_roots,
			bctx->sctx->clone_roots_cnt,
			माप(काष्ठा clone_root),
			__clone_root_cmp_द्वा_खोज);
	अगर (!found)
		वापस 0;

	अगर (found->root == bctx->sctx->send_root &&
	    ino == bctx->cur_objectid &&
	    offset == bctx->cur_offset) अणु
		bctx->found_itself = 1;
	पूर्ण

	/*
	 * Make sure we करोn't consider clones from send_root that are
	 * behind the current inode/offset.
	 */
	अगर (found->root == bctx->sctx->send_root) अणु
		/*
		 * If the source inode was not yet processed we can't issue a
		 * clone operation, as the source extent करोes not exist yet at
		 * the destination of the stream.
		 */
		अगर (ino > bctx->cur_objectid)
			वापस 0;
		/*
		 * We clone from the inode currently being sent as दीर्घ as the
		 * source extent is alपढ़ोy processed, otherwise we could try
		 * to clone from an extent that करोes not exist yet at the
		 * destination of the stream.
		 */
		अगर (ino == bctx->cur_objectid &&
		    offset + bctx->extent_len >
		    bctx->sctx->cur_inode_next_ग_लिखो_offset)
			वापस 0;
	पूर्ण

	bctx->found++;
	found->found_refs++;
	अगर (ino < found->ino) अणु
		found->ino = ino;
		found->offset = offset;
	पूर्ण अन्यथा अगर (found->ino == ino) अणु
		/*
		 * same extent found more then once in the same file.
		 */
		अगर (found->offset > offset + bctx->extent_len)
			found->offset = offset;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Given an inode, offset and extent item, it finds a good clone क्रम a clone
 * inकाष्ठाion. Returns -ENOENT when none could be found. The function makes
 * sure that the वापसed clone is usable at the poपूर्णांक where sending is at the
 * moment. This means, that no clones are accepted which lie behind the current
 * inode+offset.
 *
 * path must poपूर्णांक to the extent item when called.
 */
अटल पूर्णांक find_extent_clone(काष्ठा send_ctx *sctx,
			     काष्ठा btrfs_path *path,
			     u64 ino, u64 data_offset,
			     u64 ino_size,
			     काष्ठा clone_root **found)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	पूर्णांक ret;
	पूर्णांक extent_type;
	u64 logical;
	u64 disk_byte;
	u64 num_bytes;
	u64 extent_item_pos;
	u64 flags = 0;
	काष्ठा btrfs_file_extent_item *fi;
	काष्ठा extent_buffer *eb = path->nodes[0];
	काष्ठा backref_ctx *backref_ctx = शून्य;
	काष्ठा clone_root *cur_clone_root;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_path *पंचांगp_path;
	काष्ठा btrfs_extent_item *ei;
	पूर्णांक compressed;
	u32 i;

	पंचांगp_path = alloc_path_क्रम_send();
	अगर (!पंचांगp_path)
		वापस -ENOMEM;

	/* We only use this path under the commit sem */
	पंचांगp_path->need_commit_sem = 0;

	backref_ctx = kदो_स्मृति(माप(*backref_ctx), GFP_KERNEL);
	अगर (!backref_ctx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (data_offset >= ino_size) अणु
		/*
		 * There may be extents that lie behind the file's size.
		 * I at least had this in combination with snapshotting जबतक
		 * writing large files.
		 */
		ret = 0;
		जाओ out;
	पूर्ण

	fi = btrfs_item_ptr(eb, path->slots[0],
			काष्ठा btrfs_file_extent_item);
	extent_type = btrfs_file_extent_type(eb, fi);
	अगर (extent_type == BTRFS_खाता_EXTENT_INLINE) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	compressed = btrfs_file_extent_compression(eb, fi);

	num_bytes = btrfs_file_extent_num_bytes(eb, fi);
	disk_byte = btrfs_file_extent_disk_bytenr(eb, fi);
	अगर (disk_byte == 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	logical = disk_byte + btrfs_file_extent_offset(eb, fi);

	करोwn_पढ़ो(&fs_info->commit_root_sem);
	ret = extent_from_logical(fs_info, disk_byte, पंचांगp_path,
				  &found_key, &flags);
	up_पढ़ो(&fs_info->commit_root_sem);

	अगर (ret < 0)
		जाओ out;
	अगर (flags & BTRFS_EXTENT_FLAG_TREE_BLOCK) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	ei = btrfs_item_ptr(पंचांगp_path->nodes[0], पंचांगp_path->slots[0],
			    काष्ठा btrfs_extent_item);
	/*
	 * Backreference walking (iterate_extent_inodes() below) is currently
	 * too expensive when an extent has a large number of references, both
	 * in समय spent and used memory. So क्रम now just fallback to ग_लिखो
	 * operations instead of clone operations when an extent has more than
	 * a certain amount of references.
	 */
	अगर (btrfs_extent_refs(पंचांगp_path->nodes[0], ei) > SEND_MAX_EXTENT_REFS) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	btrfs_release_path(पंचांगp_path);

	/*
	 * Setup the clone roots.
	 */
	क्रम (i = 0; i < sctx->clone_roots_cnt; i++) अणु
		cur_clone_root = sctx->clone_roots + i;
		cur_clone_root->ino = (u64)-1;
		cur_clone_root->offset = 0;
		cur_clone_root->found_refs = 0;
	पूर्ण

	backref_ctx->sctx = sctx;
	backref_ctx->found = 0;
	backref_ctx->cur_objectid = ino;
	backref_ctx->cur_offset = data_offset;
	backref_ctx->found_itself = 0;
	backref_ctx->extent_len = num_bytes;

	/*
	 * The last extent of a file may be too large due to page alignment.
	 * We need to adjust extent_len in this हाल so that the checks in
	 * __iterate_backrefs work.
	 */
	अगर (data_offset + num_bytes >= ino_size)
		backref_ctx->extent_len = ino_size - data_offset;

	/*
	 * Now collect all backrefs.
	 */
	अगर (compressed == BTRFS_COMPRESS_NONE)
		extent_item_pos = logical - found_key.objectid;
	अन्यथा
		extent_item_pos = 0;
	ret = iterate_extent_inodes(fs_info, found_key.objectid,
				    extent_item_pos, 1, __iterate_backrefs,
				    backref_ctx, false);

	अगर (ret < 0)
		जाओ out;

	अगर (!backref_ctx->found_itself) अणु
		/* found a bug in backref code? */
		ret = -EIO;
		btrfs_err(fs_info,
			  "did not find backref in send_root. inode=%llu, offset=%llu, disk_byte=%llu found extent=%llu",
			  ino, data_offset, disk_byte, found_key.objectid);
		जाओ out;
	पूर्ण

	btrfs_debug(fs_info,
		    "find_extent_clone: data_offset=%llu, ino=%llu, num_bytes=%llu, logical=%llu",
		    data_offset, ino, num_bytes, logical);

	अगर (!backref_ctx->found)
		btrfs_debug(fs_info, "no clones found");

	cur_clone_root = शून्य;
	क्रम (i = 0; i < sctx->clone_roots_cnt; i++) अणु
		अगर (sctx->clone_roots[i].found_refs) अणु
			अगर (!cur_clone_root)
				cur_clone_root = sctx->clone_roots + i;
			अन्यथा अगर (sctx->clone_roots[i].root == sctx->send_root)
				/* prefer clones from send_root over others */
				cur_clone_root = sctx->clone_roots + i;
		पूर्ण

	पूर्ण

	अगर (cur_clone_root) अणु
		*found = cur_clone_root;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -ENOENT;
	पूर्ण

out:
	btrfs_मुक्त_path(पंचांगp_path);
	kमुक्त(backref_ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_symlink(काष्ठा btrfs_root *root,
			u64 ino,
			काष्ठा fs_path *dest)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_file_extent_item *ei;
	u8 type;
	u8 compression;
	अचिन्हित दीर्घ off;
	पूर्णांक len;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = ino;
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret) अणु
		/*
		 * An empty symlink inode. Can happen in rare error paths when
		 * creating a symlink (transaction committed beक्रमe the inode
		 * eviction handler हटाओd the symlink inode items and a crash
		 * happened in between or the subvol was snapshoted in between).
		 * Prपूर्णांक an inक्रमmative message to dmesg/syslog so that the user
		 * can delete the symlink.
		 */
		btrfs_err(root->fs_info,
			  "Found empty symlink inode %llu at root %llu",
			  ino, root->root_key.objectid);
		ret = -EIO;
		जाओ out;
	पूर्ण

	ei = btrfs_item_ptr(path->nodes[0], path->slots[0],
			काष्ठा btrfs_file_extent_item);
	type = btrfs_file_extent_type(path->nodes[0], ei);
	compression = btrfs_file_extent_compression(path->nodes[0], ei);
	BUG_ON(type != BTRFS_खाता_EXTENT_INLINE);
	BUG_ON(compression);

	off = btrfs_file_extent_अंतरभूत_start(ei);
	len = btrfs_file_extent_ram_bytes(path->nodes[0], ei);

	ret = fs_path_add_from_extent_buffer(dest, path->nodes[0], off, len);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * Helper function to generate a file name that is unique in the root of
 * send_root and parent_root. This is used to generate names क्रम orphan inodes.
 */
अटल पूर्णांक gen_unique_name(काष्ठा send_ctx *sctx,
			   u64 ino, u64 gen,
			   काष्ठा fs_path *dest)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_dir_item *di;
	अक्षर पंचांगp[64];
	पूर्णांक len;
	u64 idx = 0;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	जबतक (1) अणु
		len = snम_लिखो(पंचांगp, माप(पंचांगp), "o%llu-%llu-%llu",
				ino, gen, idx);
		ASSERT(len < माप(पंचांगp));

		di = btrfs_lookup_dir_item(शून्य, sctx->send_root,
				path, BTRFS_FIRST_FREE_OBJECTID,
				पंचांगp, म_माप(पंचांगp), 0);
		btrfs_release_path(path);
		अगर (IS_ERR(di)) अणु
			ret = PTR_ERR(di);
			जाओ out;
		पूर्ण
		अगर (di) अणु
			/* not unique, try again */
			idx++;
			जारी;
		पूर्ण

		अगर (!sctx->parent_root) अणु
			/* unique */
			ret = 0;
			अवरोध;
		पूर्ण

		di = btrfs_lookup_dir_item(शून्य, sctx->parent_root,
				path, BTRFS_FIRST_FREE_OBJECTID,
				पंचांगp, म_माप(पंचांगp), 0);
		btrfs_release_path(path);
		अगर (IS_ERR(di)) अणु
			ret = PTR_ERR(di);
			जाओ out;
		पूर्ण
		अगर (di) अणु
			/* not unique, try again */
			idx++;
			जारी;
		पूर्ण
		/* unique */
		अवरोध;
	पूर्ण

	ret = fs_path_add(dest, पंचांगp, म_माप(पंचांगp));

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

क्रमागत inode_state अणु
	inode_state_no_change,
	inode_state_will_create,
	inode_state_did_create,
	inode_state_will_delete,
	inode_state_did_delete,
पूर्ण;

अटल पूर्णांक get_cur_inode_state(काष्ठा send_ctx *sctx, u64 ino, u64 gen)
अणु
	पूर्णांक ret;
	पूर्णांक left_ret;
	पूर्णांक right_ret;
	u64 left_gen;
	u64 right_gen;

	ret = get_inode_info(sctx->send_root, ino, शून्य, &left_gen, शून्य, शून्य,
			शून्य, शून्य);
	अगर (ret < 0 && ret != -ENOENT)
		जाओ out;
	left_ret = ret;

	अगर (!sctx->parent_root) अणु
		right_ret = -ENOENT;
	पूर्ण अन्यथा अणु
		ret = get_inode_info(sctx->parent_root, ino, शून्य, &right_gen,
				शून्य, शून्य, शून्य, शून्य);
		अगर (ret < 0 && ret != -ENOENT)
			जाओ out;
		right_ret = ret;
	पूर्ण

	अगर (!left_ret && !right_ret) अणु
		अगर (left_gen == gen && right_gen == gen) अणु
			ret = inode_state_no_change;
		पूर्ण अन्यथा अगर (left_gen == gen) अणु
			अगर (ino < sctx->send_progress)
				ret = inode_state_did_create;
			अन्यथा
				ret = inode_state_will_create;
		पूर्ण अन्यथा अगर (right_gen == gen) अणु
			अगर (ino < sctx->send_progress)
				ret = inode_state_did_delete;
			अन्यथा
				ret = inode_state_will_delete;
		पूर्ण अन्यथा  अणु
			ret = -ENOENT;
		पूर्ण
	पूर्ण अन्यथा अगर (!left_ret) अणु
		अगर (left_gen == gen) अणु
			अगर (ino < sctx->send_progress)
				ret = inode_state_did_create;
			अन्यथा
				ret = inode_state_will_create;
		पूर्ण अन्यथा अणु
			ret = -ENOENT;
		पूर्ण
	पूर्ण अन्यथा अगर (!right_ret) अणु
		अगर (right_gen == gen) अणु
			अगर (ino < sctx->send_progress)
				ret = inode_state_did_delete;
			अन्यथा
				ret = inode_state_will_delete;
		पूर्ण अन्यथा अणु
			ret = -ENOENT;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -ENOENT;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक is_inode_existent(काष्ठा send_ctx *sctx, u64 ino, u64 gen)
अणु
	पूर्णांक ret;

	अगर (ino == BTRFS_FIRST_FREE_OBJECTID)
		वापस 1;

	ret = get_cur_inode_state(sctx, ino, gen);
	अगर (ret < 0)
		जाओ out;

	अगर (ret == inode_state_no_change ||
	    ret == inode_state_did_create ||
	    ret == inode_state_will_delete)
		ret = 1;
	अन्यथा
		ret = 0;

out:
	वापस ret;
पूर्ण

/*
 * Helper function to lookup a dir item in a dir.
 */
अटल पूर्णांक lookup_dir_item_inode(काष्ठा btrfs_root *root,
				 u64 dir, स्थिर अक्षर *name, पूर्णांक name_len,
				 u64 *found_inode,
				 u8 *found_type)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_dir_item *di;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	di = btrfs_lookup_dir_item(शून्य, root, path,
			dir, name, name_len, 0);
	अगर (IS_ERR_OR_शून्य(di)) अणु
		ret = di ? PTR_ERR(di) : -ENOENT;
		जाओ out;
	पूर्ण
	btrfs_dir_item_key_to_cpu(path->nodes[0], di, &key);
	अगर (key.type == BTRFS_ROOT_ITEM_KEY) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	*found_inode = key.objectid;
	*found_type = btrfs_dir_type(path->nodes[0], di);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * Looks up the first btrfs_inode_ref of a given ino. It वापसs the parent dir,
 * generation of the parent dir and the name of the dir entry.
 */
अटल पूर्णांक get_first_ref(काष्ठा btrfs_root *root, u64 ino,
			 u64 *dir, u64 *dir_gen, काष्ठा fs_path *name)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_path *path;
	पूर्णांक len;
	u64 parent_dir;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = ino;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = 0;

	ret = btrfs_search_slot_क्रम_पढ़ो(root, &key, path, 1, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (!ret)
		btrfs_item_key_to_cpu(path->nodes[0], &found_key,
				path->slots[0]);
	अगर (ret || found_key.objectid != ino ||
	    (found_key.type != BTRFS_INODE_REF_KEY &&
	     found_key.type != BTRFS_INODE_EXTREF_KEY)) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (found_key.type == BTRFS_INODE_REF_KEY) अणु
		काष्ठा btrfs_inode_ref *iref;
		iref = btrfs_item_ptr(path->nodes[0], path->slots[0],
				      काष्ठा btrfs_inode_ref);
		len = btrfs_inode_ref_name_len(path->nodes[0], iref);
		ret = fs_path_add_from_extent_buffer(name, path->nodes[0],
						     (अचिन्हित दीर्घ)(iref + 1),
						     len);
		parent_dir = found_key.offset;
	पूर्ण अन्यथा अणु
		काष्ठा btrfs_inode_extref *extref;
		extref = btrfs_item_ptr(path->nodes[0], path->slots[0],
					काष्ठा btrfs_inode_extref);
		len = btrfs_inode_extref_name_len(path->nodes[0], extref);
		ret = fs_path_add_from_extent_buffer(name, path->nodes[0],
					(अचिन्हित दीर्घ)&extref->name, len);
		parent_dir = btrfs_inode_extref_parent(path->nodes[0], extref);
	पूर्ण
	अगर (ret < 0)
		जाओ out;
	btrfs_release_path(path);

	अगर (dir_gen) अणु
		ret = get_inode_info(root, parent_dir, शून्य, dir_gen, शून्य,
				     शून्य, शून्य, शून्य);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	*dir = parent_dir;

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक is_first_ref(काष्ठा btrfs_root *root,
			u64 ino, u64 dir,
			स्थिर अक्षर *name, पूर्णांक name_len)
अणु
	पूर्णांक ret;
	काष्ठा fs_path *पंचांगp_name;
	u64 पंचांगp_dir;

	पंचांगp_name = fs_path_alloc();
	अगर (!पंचांगp_name)
		वापस -ENOMEM;

	ret = get_first_ref(root, ino, &पंचांगp_dir, शून्य, पंचांगp_name);
	अगर (ret < 0)
		जाओ out;

	अगर (dir != पंचांगp_dir || name_len != fs_path_len(पंचांगp_name)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	ret = !स_भेद(पंचांगp_name->start, name, name_len);

out:
	fs_path_मुक्त(पंचांगp_name);
	वापस ret;
पूर्ण

/*
 * Used by process_recorded_refs to determine अगर a new ref would overग_लिखो an
 * alपढ़ोy existing ref. In हाल it detects an overग_लिखो, it वापसs the
 * inode/gen in who_ino/who_gen.
 * When an overग_लिखो is detected, process_recorded_refs करोes proper orphanizing
 * to make sure later references to the overwritten inode are possible.
 * Orphanizing is however only required क्रम the first ref of an inode.
 * process_recorded_refs करोes an additional is_first_ref check to see अगर
 * orphanizing is really required.
 */
अटल पूर्णांक will_overग_लिखो_ref(काष्ठा send_ctx *sctx, u64 dir, u64 dir_gen,
			      स्थिर अक्षर *name, पूर्णांक name_len,
			      u64 *who_ino, u64 *who_gen, u64 *who_mode)
अणु
	पूर्णांक ret = 0;
	u64 gen;
	u64 other_inode = 0;
	u8 other_type = 0;

	अगर (!sctx->parent_root)
		जाओ out;

	ret = is_inode_existent(sctx, dir, dir_gen);
	अगर (ret <= 0)
		जाओ out;

	/*
	 * If we have a parent root we need to verअगरy that the parent dir was
	 * not deleted and then re-created, अगर it was then we have no overग_लिखो
	 * and we can just unlink this entry.
	 */
	अगर (sctx->parent_root && dir != BTRFS_FIRST_FREE_OBJECTID) अणु
		ret = get_inode_info(sctx->parent_root, dir, शून्य, &gen, शून्य,
				     शून्य, शून्य, शून्य);
		अगर (ret < 0 && ret != -ENOENT)
			जाओ out;
		अगर (ret) अणु
			ret = 0;
			जाओ out;
		पूर्ण
		अगर (gen != dir_gen)
			जाओ out;
	पूर्ण

	ret = lookup_dir_item_inode(sctx->parent_root, dir, name, name_len,
			&other_inode, &other_type);
	अगर (ret < 0 && ret != -ENOENT)
		जाओ out;
	अगर (ret) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/*
	 * Check अगर the overwritten ref was alपढ़ोy processed. If yes, the ref
	 * was alपढ़ोy unlinked/moved, so we can safely assume that we will not
	 * overग_लिखो anything at this poपूर्णांक in समय.
	 */
	अगर (other_inode > sctx->send_progress ||
	    is_रुकोing_क्रम_move(sctx, other_inode)) अणु
		ret = get_inode_info(sctx->parent_root, other_inode, शून्य,
				who_gen, who_mode, शून्य, शून्य, शून्य);
		अगर (ret < 0)
			जाओ out;

		ret = 1;
		*who_ino = other_inode;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * Checks अगर the ref was overwritten by an alपढ़ोy processed inode. This is
 * used by __get_cur_name_and_parent to find out अगर the ref was orphanized and
 * thus the orphan name needs be used.
 * process_recorded_refs also uses it to aव्योम unlinking of refs that were
 * overwritten.
 */
अटल पूर्णांक did_overग_लिखो_ref(काष्ठा send_ctx *sctx,
			    u64 dir, u64 dir_gen,
			    u64 ino, u64 ino_gen,
			    स्थिर अक्षर *name, पूर्णांक name_len)
अणु
	पूर्णांक ret = 0;
	u64 gen;
	u64 ow_inode;
	u8 other_type;

	अगर (!sctx->parent_root)
		जाओ out;

	ret = is_inode_existent(sctx, dir, dir_gen);
	अगर (ret <= 0)
		जाओ out;

	अगर (dir != BTRFS_FIRST_FREE_OBJECTID) अणु
		ret = get_inode_info(sctx->send_root, dir, शून्य, &gen, शून्य,
				     शून्य, शून्य, शून्य);
		अगर (ret < 0 && ret != -ENOENT)
			जाओ out;
		अगर (ret) अणु
			ret = 0;
			जाओ out;
		पूर्ण
		अगर (gen != dir_gen)
			जाओ out;
	पूर्ण

	/* check अगर the ref was overwritten by another ref */
	ret = lookup_dir_item_inode(sctx->send_root, dir, name, name_len,
			&ow_inode, &other_type);
	अगर (ret < 0 && ret != -ENOENT)
		जाओ out;
	अगर (ret) अणु
		/* was never and will never be overwritten */
		ret = 0;
		जाओ out;
	पूर्ण

	ret = get_inode_info(sctx->send_root, ow_inode, शून्य, &gen, शून्य, शून्य,
			शून्य, शून्य);
	अगर (ret < 0)
		जाओ out;

	अगर (ow_inode == ino && gen == ino_gen) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/*
	 * We know that it is or will be overwritten. Check this now.
	 * The current inode being processed might have been the one that caused
	 * inode 'ino' to be orphanized, thereक्रमe check अगर ow_inode matches
	 * the current inode being processed.
	 */
	अगर ((ow_inode < sctx->send_progress) ||
	    (ino != sctx->cur_ino && ow_inode == sctx->cur_ino &&
	     gen == sctx->cur_inode_gen))
		ret = 1;
	अन्यथा
		ret = 0;

out:
	वापस ret;
पूर्ण

/*
 * Same as did_overग_लिखो_ref, but also checks अगर it is the first ref of an inode
 * that got overwritten. This is used by process_recorded_refs to determine
 * अगर it has to use the path as वापसed by get_cur_path or the orphan name.
 */
अटल पूर्णांक did_overग_लिखो_first_ref(काष्ठा send_ctx *sctx, u64 ino, u64 gen)
अणु
	पूर्णांक ret = 0;
	काष्ठा fs_path *name = शून्य;
	u64 dir;
	u64 dir_gen;

	अगर (!sctx->parent_root)
		जाओ out;

	name = fs_path_alloc();
	अगर (!name)
		वापस -ENOMEM;

	ret = get_first_ref(sctx->parent_root, ino, &dir, &dir_gen, name);
	अगर (ret < 0)
		जाओ out;

	ret = did_overग_लिखो_ref(sctx, dir, dir_gen, ino, gen,
			name->start, fs_path_len(name));

out:
	fs_path_मुक्त(name);
	वापस ret;
पूर्ण

/*
 * Insert a name cache entry. On 32bit kernels the radix tree index is 32bit,
 * so we need to करो some special handling in हाल we have clashes. This function
 * takes care of this with the help of name_cache_entry::radix_list.
 * In हाल of error, nce is kमुक्तd.
 */
अटल पूर्णांक name_cache_insert(काष्ठा send_ctx *sctx,
			     काष्ठा name_cache_entry *nce)
अणु
	पूर्णांक ret = 0;
	काष्ठा list_head *nce_head;

	nce_head = radix_tree_lookup(&sctx->name_cache,
			(अचिन्हित दीर्घ)nce->ino);
	अगर (!nce_head) अणु
		nce_head = kदो_स्मृति(माप(*nce_head), GFP_KERNEL);
		अगर (!nce_head) अणु
			kमुक्त(nce);
			वापस -ENOMEM;
		पूर्ण
		INIT_LIST_HEAD(nce_head);

		ret = radix_tree_insert(&sctx->name_cache, nce->ino, nce_head);
		अगर (ret < 0) अणु
			kमुक्त(nce_head);
			kमुक्त(nce);
			वापस ret;
		पूर्ण
	पूर्ण
	list_add_tail(&nce->radix_list, nce_head);
	list_add_tail(&nce->list, &sctx->name_cache_list);
	sctx->name_cache_size++;

	वापस ret;
पूर्ण

अटल व्योम name_cache_delete(काष्ठा send_ctx *sctx,
			      काष्ठा name_cache_entry *nce)
अणु
	काष्ठा list_head *nce_head;

	nce_head = radix_tree_lookup(&sctx->name_cache,
			(अचिन्हित दीर्घ)nce->ino);
	अगर (!nce_head) अणु
		btrfs_err(sctx->send_root->fs_info,
	      "name_cache_delete lookup failed ino %llu cache size %d, leaking memory",
			nce->ino, sctx->name_cache_size);
	पूर्ण

	list_del(&nce->radix_list);
	list_del(&nce->list);
	sctx->name_cache_size--;

	/*
	 * We may not get to the final release of nce_head अगर the lookup fails
	 */
	अगर (nce_head && list_empty(nce_head)) अणु
		radix_tree_delete(&sctx->name_cache, (अचिन्हित दीर्घ)nce->ino);
		kमुक्त(nce_head);
	पूर्ण
पूर्ण

अटल काष्ठा name_cache_entry *name_cache_search(काष्ठा send_ctx *sctx,
						    u64 ino, u64 gen)
अणु
	काष्ठा list_head *nce_head;
	काष्ठा name_cache_entry *cur;

	nce_head = radix_tree_lookup(&sctx->name_cache, (अचिन्हित दीर्घ)ino);
	अगर (!nce_head)
		वापस शून्य;

	list_क्रम_each_entry(cur, nce_head, radix_list) अणु
		अगर (cur->ino == ino && cur->gen == gen)
			वापस cur;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Removes the entry from the list and adds it back to the end. This marks the
 * entry as recently used so that name_cache_clean_unused करोes not हटाओ it.
 */
अटल व्योम name_cache_used(काष्ठा send_ctx *sctx, काष्ठा name_cache_entry *nce)
अणु
	list_del(&nce->list);
	list_add_tail(&nce->list, &sctx->name_cache_list);
पूर्ण

/*
 * Remove some entries from the beginning of name_cache_list.
 */
अटल व्योम name_cache_clean_unused(काष्ठा send_ctx *sctx)
अणु
	काष्ठा name_cache_entry *nce;

	अगर (sctx->name_cache_size < SEND_CTX_NAME_CACHE_CLEAN_SIZE)
		वापस;

	जबतक (sctx->name_cache_size > SEND_CTX_MAX_NAME_CACHE_SIZE) अणु
		nce = list_entry(sctx->name_cache_list.next,
				काष्ठा name_cache_entry, list);
		name_cache_delete(sctx, nce);
		kमुक्त(nce);
	पूर्ण
पूर्ण

अटल व्योम name_cache_मुक्त(काष्ठा send_ctx *sctx)
अणु
	काष्ठा name_cache_entry *nce;

	जबतक (!list_empty(&sctx->name_cache_list)) अणु
		nce = list_entry(sctx->name_cache_list.next,
				काष्ठा name_cache_entry, list);
		name_cache_delete(sctx, nce);
		kमुक्त(nce);
	पूर्ण
पूर्ण

/*
 * Used by get_cur_path क्रम each ref up to the root.
 * Returns 0 अगर it succeeded.
 * Returns 1 अगर the inode is not existent or got overwritten. In that हाल, the
 * name is an orphan name. This inकाष्ठाs get_cur_path to stop iterating. If 1
 * is वापसed, parent_ino/parent_gen are not guaranteed to be valid.
 * Returns <0 in हाल of error.
 */
अटल पूर्णांक __get_cur_name_and_parent(काष्ठा send_ctx *sctx,
				     u64 ino, u64 gen,
				     u64 *parent_ino,
				     u64 *parent_gen,
				     काष्ठा fs_path *dest)
अणु
	पूर्णांक ret;
	पूर्णांक nce_ret;
	काष्ठा name_cache_entry *nce = शून्य;

	/*
	 * First check अगर we alपढ़ोy did a call to this function with the same
	 * ino/gen. If yes, check अगर the cache entry is still up-to-date. If yes
	 * वापस the cached result.
	 */
	nce = name_cache_search(sctx, ino, gen);
	अगर (nce) अणु
		अगर (ino < sctx->send_progress && nce->need_later_update) अणु
			name_cache_delete(sctx, nce);
			kमुक्त(nce);
			nce = शून्य;
		पूर्ण अन्यथा अणु
			name_cache_used(sctx, nce);
			*parent_ino = nce->parent_ino;
			*parent_gen = nce->parent_gen;
			ret = fs_path_add(dest, nce->name, nce->name_len);
			अगर (ret < 0)
				जाओ out;
			ret = nce->ret;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * If the inode is not existent yet, add the orphan name and वापस 1.
	 * This should only happen क्रम the parent dir that we determine in
	 * __record_new_ref
	 */
	ret = is_inode_existent(sctx, ino, gen);
	अगर (ret < 0)
		जाओ out;

	अगर (!ret) अणु
		ret = gen_unique_name(sctx, ino, gen, dest);
		अगर (ret < 0)
			जाओ out;
		ret = 1;
		जाओ out_cache;
	पूर्ण

	/*
	 * Depending on whether the inode was alपढ़ोy processed or not, use
	 * send_root or parent_root क्रम ref lookup.
	 */
	अगर (ino < sctx->send_progress)
		ret = get_first_ref(sctx->send_root, ino,
				    parent_ino, parent_gen, dest);
	अन्यथा
		ret = get_first_ref(sctx->parent_root, ino,
				    parent_ino, parent_gen, dest);
	अगर (ret < 0)
		जाओ out;

	/*
	 * Check अगर the ref was overwritten by an inode's ref that was processed
	 * earlier. If yes, treat as orphan and वापस 1.
	 */
	ret = did_overग_लिखो_ref(sctx, *parent_ino, *parent_gen, ino, gen,
			dest->start, dest->end - dest->start);
	अगर (ret < 0)
		जाओ out;
	अगर (ret) अणु
		fs_path_reset(dest);
		ret = gen_unique_name(sctx, ino, gen, dest);
		अगर (ret < 0)
			जाओ out;
		ret = 1;
	पूर्ण

out_cache:
	/*
	 * Store the result of the lookup in the name cache.
	 */
	nce = kदो_स्मृति(माप(*nce) + fs_path_len(dest) + 1, GFP_KERNEL);
	अगर (!nce) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	nce->ino = ino;
	nce->gen = gen;
	nce->parent_ino = *parent_ino;
	nce->parent_gen = *parent_gen;
	nce->name_len = fs_path_len(dest);
	nce->ret = ret;
	म_नकल(nce->name, dest->start);

	अगर (ino < sctx->send_progress)
		nce->need_later_update = 0;
	अन्यथा
		nce->need_later_update = 1;

	nce_ret = name_cache_insert(sctx, nce);
	अगर (nce_ret < 0)
		ret = nce_ret;
	name_cache_clean_unused(sctx);

out:
	वापस ret;
पूर्ण

/*
 * Magic happens here. This function वापसs the first ref to an inode as it
 * would look like जबतक receiving the stream at this poपूर्णांक in समय.
 * We walk the path up to the root. For every inode in between, we check अगर it
 * was alपढ़ोy processed/sent. If yes, we जारी with the parent as found
 * in send_root. If not, we जारी with the parent as found in parent_root.
 * If we encounter an inode that was deleted at this poपूर्णांक in समय, we use the
 * inodes "orphan" name instead of the real name and stop. Same with new inodes
 * that were not created yet and overwritten inodes/refs.
 *
 * When करो we have orphan inodes:
 * 1. When an inode is freshly created and thus no valid refs are available yet
 * 2. When a directory lost all it's refs (deleted) but still has dir items
 *    inside which were not processed yet (pending क्रम move/delete). If anyone
 *    tried to get the path to the dir items, it would get a path inside that
 *    orphan directory.
 * 3. When an inode is moved around or माला_लो new links, it may overग_लिखो the ref
 *    of an unprocessed inode. If in that हाल the first ref would be
 *    overwritten, the overwritten inode माला_लो "orphanized". Later when we
 *    process this overwritten inode, it is restored at a new place by moving
 *    the orphan inode.
 *
 * sctx->send_progress tells this function at which poपूर्णांक in समय receiving
 * would be.
 */
अटल पूर्णांक get_cur_path(काष्ठा send_ctx *sctx, u64 ino, u64 gen,
			काष्ठा fs_path *dest)
अणु
	पूर्णांक ret = 0;
	काष्ठा fs_path *name = शून्य;
	u64 parent_inode = 0;
	u64 parent_gen = 0;
	पूर्णांक stop = 0;

	name = fs_path_alloc();
	अगर (!name) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	dest->reversed = 1;
	fs_path_reset(dest);

	जबतक (!stop && ino != BTRFS_FIRST_FREE_OBJECTID) अणु
		काष्ठा रुकोing_dir_move *wdm;

		fs_path_reset(name);

		अगर (is_रुकोing_क्रम_rm(sctx, ino, gen)) अणु
			ret = gen_unique_name(sctx, ino, gen, name);
			अगर (ret < 0)
				जाओ out;
			ret = fs_path_add_path(dest, name);
			अवरोध;
		पूर्ण

		wdm = get_रुकोing_dir_move(sctx, ino);
		अगर (wdm && wdm->orphanized) अणु
			ret = gen_unique_name(sctx, ino, gen, name);
			stop = 1;
		पूर्ण अन्यथा अगर (wdm) अणु
			ret = get_first_ref(sctx->parent_root, ino,
					    &parent_inode, &parent_gen, name);
		पूर्ण अन्यथा अणु
			ret = __get_cur_name_and_parent(sctx, ino, gen,
							&parent_inode,
							&parent_gen, name);
			अगर (ret)
				stop = 1;
		पूर्ण

		अगर (ret < 0)
			जाओ out;

		ret = fs_path_add_path(dest, name);
		अगर (ret < 0)
			जाओ out;

		ino = parent_inode;
		gen = parent_gen;
	पूर्ण

out:
	fs_path_मुक्त(name);
	अगर (!ret)
		fs_path_unreverse(dest);
	वापस ret;
पूर्ण

/*
 * Sends a BTRFS_SEND_C_SUBVOL command/item to userspace
 */
अटल पूर्णांक send_subvol_begin(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_root *send_root = sctx->send_root;
	काष्ठा btrfs_root *parent_root = sctx->parent_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_root_ref *ref;
	काष्ठा extent_buffer *leaf;
	अक्षर *name = शून्य;
	पूर्णांक namelen;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	name = kदो_स्मृति(BTRFS_PATH_NAME_MAX, GFP_KERNEL);
	अगर (!name) अणु
		btrfs_मुक्त_path(path);
		वापस -ENOMEM;
	पूर्ण

	key.objectid = send_root->root_key.objectid;
	key.type = BTRFS_ROOT_BACKREF_KEY;
	key.offset = 0;

	ret = btrfs_search_slot_क्रम_पढ़ो(send_root->fs_info->tree_root,
				&key, path, 1, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
	अगर (key.type != BTRFS_ROOT_BACKREF_KEY ||
	    key.objectid != send_root->root_key.objectid) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	ref = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_root_ref);
	namelen = btrfs_root_ref_name_len(leaf, ref);
	पढ़ो_extent_buffer(leaf, name, (अचिन्हित दीर्घ)(ref + 1), namelen);
	btrfs_release_path(path);

	अगर (parent_root) अणु
		ret = begin_cmd(sctx, BTRFS_SEND_C_SNAPSHOT);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		ret = begin_cmd(sctx, BTRFS_SEND_C_SUBVOL);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	TLV_PUT_STRING(sctx, BTRFS_SEND_A_PATH, name, namelen);

	अगर (!btrfs_is_empty_uuid(sctx->send_root->root_item.received_uuid))
		TLV_PUT_UUID(sctx, BTRFS_SEND_A_UUID,
			    sctx->send_root->root_item.received_uuid);
	अन्यथा
		TLV_PUT_UUID(sctx, BTRFS_SEND_A_UUID,
			    sctx->send_root->root_item.uuid);

	TLV_PUT_U64(sctx, BTRFS_SEND_A_CTRANSID,
		    btrfs_root_ctransid(&sctx->send_root->root_item));
	अगर (parent_root) अणु
		अगर (!btrfs_is_empty_uuid(parent_root->root_item.received_uuid))
			TLV_PUT_UUID(sctx, BTRFS_SEND_A_CLONE_UUID,
				     parent_root->root_item.received_uuid);
		अन्यथा
			TLV_PUT_UUID(sctx, BTRFS_SEND_A_CLONE_UUID,
				     parent_root->root_item.uuid);
		TLV_PUT_U64(sctx, BTRFS_SEND_A_CLONE_CTRANSID,
			    btrfs_root_ctransid(&sctx->parent_root->root_item));
	पूर्ण

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	btrfs_मुक्त_path(path);
	kमुक्त(name);
	वापस ret;
पूर्ण

अटल पूर्णांक send_truncate(काष्ठा send_ctx *sctx, u64 ino, u64 gen, u64 size)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	पूर्णांक ret = 0;
	काष्ठा fs_path *p;

	btrfs_debug(fs_info, "send_truncate %llu size=%llu", ino, size);

	p = fs_path_alloc();
	अगर (!p)
		वापस -ENOMEM;

	ret = begin_cmd(sctx, BTRFS_SEND_C_TRUNCATE);
	अगर (ret < 0)
		जाओ out;

	ret = get_cur_path(sctx, ino, gen, p);
	अगर (ret < 0)
		जाओ out;
	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_SIZE, size);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	fs_path_मुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक send_chmod(काष्ठा send_ctx *sctx, u64 ino, u64 gen, u64 mode)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	पूर्णांक ret = 0;
	काष्ठा fs_path *p;

	btrfs_debug(fs_info, "send_chmod %llu mode=%llu", ino, mode);

	p = fs_path_alloc();
	अगर (!p)
		वापस -ENOMEM;

	ret = begin_cmd(sctx, BTRFS_SEND_C_CHMOD);
	अगर (ret < 0)
		जाओ out;

	ret = get_cur_path(sctx, ino, gen, p);
	अगर (ret < 0)
		जाओ out;
	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_MODE, mode & 07777);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	fs_path_मुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक send_chown(काष्ठा send_ctx *sctx, u64 ino, u64 gen, u64 uid, u64 gid)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	पूर्णांक ret = 0;
	काष्ठा fs_path *p;

	btrfs_debug(fs_info, "send_chown %llu uid=%llu, gid=%llu",
		    ino, uid, gid);

	p = fs_path_alloc();
	अगर (!p)
		वापस -ENOMEM;

	ret = begin_cmd(sctx, BTRFS_SEND_C_CHOWN);
	अगर (ret < 0)
		जाओ out;

	ret = get_cur_path(sctx, ino, gen, p);
	अगर (ret < 0)
		जाओ out;
	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_UID, uid);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_GID, gid);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	fs_path_मुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक send_uबार(काष्ठा send_ctx *sctx, u64 ino, u64 gen)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	पूर्णांक ret = 0;
	काष्ठा fs_path *p = शून्य;
	काष्ठा btrfs_inode_item *ii;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_key key;
	पूर्णांक slot;

	btrfs_debug(fs_info, "send_utimes %llu", ino);

	p = fs_path_alloc();
	अगर (!p)
		वापस -ENOMEM;

	path = alloc_path_क्रम_send();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	key.objectid = ino;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(शून्य, sctx->send_root, &key, path, 0, 0);
	अगर (ret > 0)
		ret = -ENOENT;
	अगर (ret < 0)
		जाओ out;

	eb = path->nodes[0];
	slot = path->slots[0];
	ii = btrfs_item_ptr(eb, slot, काष्ठा btrfs_inode_item);

	ret = begin_cmd(sctx, BTRFS_SEND_C_UTIMES);
	अगर (ret < 0)
		जाओ out;

	ret = get_cur_path(sctx, ino, gen, p);
	अगर (ret < 0)
		जाओ out;
	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
	TLV_PUT_BTRFS_TIMESPEC(sctx, BTRFS_SEND_A_ATIME, eb, &ii->aसमय);
	TLV_PUT_BTRFS_TIMESPEC(sctx, BTRFS_SEND_A_MTIME, eb, &ii->mसमय);
	TLV_PUT_BTRFS_TIMESPEC(sctx, BTRFS_SEND_A_CTIME, eb, &ii->स_समय);
	/* TODO Add oसमय support when the oसमय patches get पूर्णांकo upstream */

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	fs_path_मुक्त(p);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * Sends a BTRFS_SEND_C_MKXXX or SYMLINK command to user space. We करोn't have
 * a valid path yet because we did not process the refs yet. So, the inode
 * is created as orphan.
 */
अटल पूर्णांक send_create_inode(काष्ठा send_ctx *sctx, u64 ino)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	पूर्णांक ret = 0;
	काष्ठा fs_path *p;
	पूर्णांक cmd;
	u64 gen;
	u64 mode;
	u64 rdev;

	btrfs_debug(fs_info, "send_create_inode %llu", ino);

	p = fs_path_alloc();
	अगर (!p)
		वापस -ENOMEM;

	अगर (ino != sctx->cur_ino) अणु
		ret = get_inode_info(sctx->send_root, ino, शून्य, &gen, &mode,
				     शून्य, शून्य, &rdev);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		gen = sctx->cur_inode_gen;
		mode = sctx->cur_inode_mode;
		rdev = sctx->cur_inode_rdev;
	पूर्ण

	अगर (S_ISREG(mode)) अणु
		cmd = BTRFS_SEND_C_MKखाता;
	पूर्ण अन्यथा अगर (S_ISसूची(mode)) अणु
		cmd = BTRFS_SEND_C_MKसूची;
	पूर्ण अन्यथा अगर (S_ISLNK(mode)) अणु
		cmd = BTRFS_SEND_C_SYMLINK;
	पूर्ण अन्यथा अगर (S_ISCHR(mode) || S_ISBLK(mode)) अणु
		cmd = BTRFS_SEND_C_MKNOD;
	पूर्ण अन्यथा अगर (S_ISFIFO(mode)) अणु
		cmd = BTRFS_SEND_C_MKFIFO;
	पूर्ण अन्यथा अगर (S_ISSOCK(mode)) अणु
		cmd = BTRFS_SEND_C_MKSOCK;
	पूर्ण अन्यथा अणु
		btrfs_warn(sctx->send_root->fs_info, "unexpected inode type %o",
				(पूर्णांक)(mode & S_IFMT));
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ret = begin_cmd(sctx, cmd);
	अगर (ret < 0)
		जाओ out;

	ret = gen_unique_name(sctx, ino, gen, p);
	अगर (ret < 0)
		जाओ out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_INO, ino);

	अगर (S_ISLNK(mode)) अणु
		fs_path_reset(p);
		ret = पढ़ो_symlink(sctx->send_root, ino, p);
		अगर (ret < 0)
			जाओ out;
		TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH_LINK, p);
	पूर्ण अन्यथा अगर (S_ISCHR(mode) || S_ISBLK(mode) ||
		   S_ISFIFO(mode) || S_ISSOCK(mode)) अणु
		TLV_PUT_U64(sctx, BTRFS_SEND_A_RDEV, new_encode_dev(rdev));
		TLV_PUT_U64(sctx, BTRFS_SEND_A_MODE, mode);
	पूर्ण

	ret = send_cmd(sctx);
	अगर (ret < 0)
		जाओ out;


tlv_put_failure:
out:
	fs_path_मुक्त(p);
	वापस ret;
पूर्ण

/*
 * We need some special handling क्रम inodes that get processed beक्रमe the parent
 * directory got created. See process_recorded_refs क्रम details.
 * This function करोes the check अगर we alपढ़ोy created the dir out of order.
 */
अटल पूर्णांक did_create_dir(काष्ठा send_ctx *sctx, u64 dir)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_key di_key;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_dir_item *di;
	पूर्णांक slot;

	path = alloc_path_क्रम_send();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	key.objectid = dir;
	key.type = BTRFS_सूची_INDEX_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(शून्य, sctx->send_root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;

	जबतक (1) अणु
		eb = path->nodes[0];
		slot = path->slots[0];
		अगर (slot >= btrfs_header_nritems(eb)) अणु
			ret = btrfs_next_leaf(sctx->send_root, path);
			अगर (ret < 0) अणु
				जाओ out;
			पूर्ण अन्यथा अगर (ret > 0) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(eb, &found_key, slot);
		अगर (found_key.objectid != key.objectid ||
		    found_key.type != key.type) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		di = btrfs_item_ptr(eb, slot, काष्ठा btrfs_dir_item);
		btrfs_dir_item_key_to_cpu(eb, di, &di_key);

		अगर (di_key.type != BTRFS_ROOT_ITEM_KEY &&
		    di_key.objectid < sctx->send_progress) अणु
			ret = 1;
			जाओ out;
		पूर्ण

		path->slots[0]++;
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * Only creates the inode अगर it is:
 * 1. Not a directory
 * 2. Or a directory which was not created alपढ़ोy due to out of order
 *    directories. See did_create_dir and process_recorded_refs क्रम details.
 */
अटल पूर्णांक send_create_inode_अगर_needed(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret;

	अगर (S_ISसूची(sctx->cur_inode_mode)) अणु
		ret = did_create_dir(sctx, sctx->cur_ino);
		अगर (ret < 0)
			जाओ out;
		अगर (ret) अणु
			ret = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = send_create_inode(sctx, sctx->cur_ino);
	अगर (ret < 0)
		जाओ out;

out:
	वापस ret;
पूर्ण

काष्ठा recorded_ref अणु
	काष्ठा list_head list;
	अक्षर *name;
	काष्ठा fs_path *full_path;
	u64 dir;
	u64 dir_gen;
	पूर्णांक name_len;
पूर्ण;

अटल व्योम set_ref_path(काष्ठा recorded_ref *ref, काष्ठा fs_path *path)
अणु
	ref->full_path = path;
	ref->name = (अक्षर *)kbasename(ref->full_path->start);
	ref->name_len = ref->full_path->end - ref->name;
पूर्ण

/*
 * We need to process new refs beक्रमe deleted refs, but compare_tree gives us
 * everything mixed. So we first record all refs and later process them.
 * This function is a helper to record one ref.
 */
अटल पूर्णांक __record_ref(काष्ठा list_head *head, u64 dir,
		      u64 dir_gen, काष्ठा fs_path *path)
अणु
	काष्ठा recorded_ref *ref;

	ref = kदो_स्मृति(माप(*ref), GFP_KERNEL);
	अगर (!ref)
		वापस -ENOMEM;

	ref->dir = dir;
	ref->dir_gen = dir_gen;
	set_ref_path(ref, path);
	list_add_tail(&ref->list, head);
	वापस 0;
पूर्ण

अटल पूर्णांक dup_ref(काष्ठा recorded_ref *ref, काष्ठा list_head *list)
अणु
	काष्ठा recorded_ref *new;

	new = kदो_स्मृति(माप(*ref), GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;

	new->dir = ref->dir;
	new->dir_gen = ref->dir_gen;
	new->full_path = शून्य;
	INIT_LIST_HEAD(&new->list);
	list_add_tail(&new->list, list);
	वापस 0;
पूर्ण

अटल व्योम __मुक्त_recorded_refs(काष्ठा list_head *head)
अणु
	काष्ठा recorded_ref *cur;

	जबतक (!list_empty(head)) अणु
		cur = list_entry(head->next, काष्ठा recorded_ref, list);
		fs_path_मुक्त(cur->full_path);
		list_del(&cur->list);
		kमुक्त(cur);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_recorded_refs(काष्ठा send_ctx *sctx)
अणु
	__मुक्त_recorded_refs(&sctx->new_refs);
	__मुक्त_recorded_refs(&sctx->deleted_refs);
पूर्ण

/*
 * Renames/moves a file/dir to its orphan name. Used when the first
 * ref of an unprocessed inode माला_लो overwritten and क्रम all non empty
 * directories.
 */
अटल पूर्णांक orphanize_inode(काष्ठा send_ctx *sctx, u64 ino, u64 gen,
			  काष्ठा fs_path *path)
अणु
	पूर्णांक ret;
	काष्ठा fs_path *orphan;

	orphan = fs_path_alloc();
	अगर (!orphan)
		वापस -ENOMEM;

	ret = gen_unique_name(sctx, ino, gen, orphan);
	अगर (ret < 0)
		जाओ out;

	ret = send_नाम(sctx, path, orphan);

out:
	fs_path_मुक्त(orphan);
	वापस ret;
पूर्ण

अटल काष्ठा orphan_dir_info *add_orphan_dir_info(काष्ठा send_ctx *sctx,
						   u64 dir_ino, u64 dir_gen)
अणु
	काष्ठा rb_node **p = &sctx->orphan_dirs.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा orphan_dir_info *entry, *odi;

	जबतक (*p) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा orphan_dir_info, node);
		अगर (dir_ino < entry->ino)
			p = &(*p)->rb_left;
		अन्यथा अगर (dir_ino > entry->ino)
			p = &(*p)->rb_right;
		अन्यथा अगर (dir_gen < entry->gen)
			p = &(*p)->rb_left;
		अन्यथा अगर (dir_gen > entry->gen)
			p = &(*p)->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण

	odi = kदो_स्मृति(माप(*odi), GFP_KERNEL);
	अगर (!odi)
		वापस ERR_PTR(-ENOMEM);
	odi->ino = dir_ino;
	odi->gen = dir_gen;
	odi->last_dir_index_offset = 0;

	rb_link_node(&odi->node, parent, p);
	rb_insert_color(&odi->node, &sctx->orphan_dirs);
	वापस odi;
पूर्ण

अटल काष्ठा orphan_dir_info *get_orphan_dir_info(काष्ठा send_ctx *sctx,
						   u64 dir_ino, u64 gen)
अणु
	काष्ठा rb_node *n = sctx->orphan_dirs.rb_node;
	काष्ठा orphan_dir_info *entry;

	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा orphan_dir_info, node);
		अगर (dir_ino < entry->ino)
			n = n->rb_left;
		अन्यथा अगर (dir_ino > entry->ino)
			n = n->rb_right;
		अन्यथा अगर (gen < entry->gen)
			n = n->rb_left;
		अन्यथा अगर (gen > entry->gen)
			n = n->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक is_रुकोing_क्रम_rm(काष्ठा send_ctx *sctx, u64 dir_ino, u64 gen)
अणु
	काष्ठा orphan_dir_info *odi = get_orphan_dir_info(sctx, dir_ino, gen);

	वापस odi != शून्य;
पूर्ण

अटल व्योम मुक्त_orphan_dir_info(काष्ठा send_ctx *sctx,
				 काष्ठा orphan_dir_info *odi)
अणु
	अगर (!odi)
		वापस;
	rb_erase(&odi->node, &sctx->orphan_dirs);
	kमुक्त(odi);
पूर्ण

/*
 * Returns 1 अगर a directory can be हटाओd at this poपूर्णांक in समय.
 * We check this by iterating all dir items and checking अगर the inode behind
 * the dir item was alपढ़ोy processed.
 */
अटल पूर्णांक can_सूची_हटाओ(काष्ठा send_ctx *sctx, u64 dir, u64 dir_gen,
		     u64 send_progress)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_root *root = sctx->parent_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_key loc;
	काष्ठा btrfs_dir_item *di;
	काष्ठा orphan_dir_info *odi = शून्य;

	/*
	 * Don't try to सूची_हटाओ the top/root subvolume dir.
	 */
	अगर (dir == BTRFS_FIRST_FREE_OBJECTID)
		वापस 0;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = dir;
	key.type = BTRFS_सूची_INDEX_KEY;
	key.offset = 0;

	odi = get_orphan_dir_info(sctx, dir, dir_gen);
	अगर (odi)
		key.offset = odi->last_dir_index_offset;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;

	जबतक (1) अणु
		काष्ठा रुकोing_dir_move *dm;

		अगर (path->slots[0] >= btrfs_header_nritems(path->nodes[0])) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ out;
			अन्यथा अगर (ret > 0)
				अवरोध;
			जारी;
		पूर्ण
		btrfs_item_key_to_cpu(path->nodes[0], &found_key,
				      path->slots[0]);
		अगर (found_key.objectid != key.objectid ||
		    found_key.type != key.type)
			अवरोध;

		di = btrfs_item_ptr(path->nodes[0], path->slots[0],
				काष्ठा btrfs_dir_item);
		btrfs_dir_item_key_to_cpu(path->nodes[0], di, &loc);

		dm = get_रुकोing_dir_move(sctx, loc.objectid);
		अगर (dm) अणु
			odi = add_orphan_dir_info(sctx, dir, dir_gen);
			अगर (IS_ERR(odi)) अणु
				ret = PTR_ERR(odi);
				जाओ out;
			पूर्ण
			odi->gen = dir_gen;
			odi->last_dir_index_offset = found_key.offset;
			dm->सूची_हटाओ_ino = dir;
			dm->सूची_हटाओ_gen = dir_gen;
			ret = 0;
			जाओ out;
		पूर्ण

		अगर (loc.objectid > send_progress) अणु
			odi = add_orphan_dir_info(sctx, dir, dir_gen);
			अगर (IS_ERR(odi)) अणु
				ret = PTR_ERR(odi);
				जाओ out;
			पूर्ण
			odi->gen = dir_gen;
			odi->last_dir_index_offset = found_key.offset;
			ret = 0;
			जाओ out;
		पूर्ण

		path->slots[0]++;
	पूर्ण
	मुक्त_orphan_dir_info(sctx, odi);

	ret = 1;

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक is_रुकोing_क्रम_move(काष्ठा send_ctx *sctx, u64 ino)
अणु
	काष्ठा रुकोing_dir_move *entry = get_रुकोing_dir_move(sctx, ino);

	वापस entry != शून्य;
पूर्ण

अटल पूर्णांक add_रुकोing_dir_move(काष्ठा send_ctx *sctx, u64 ino, bool orphanized)
अणु
	काष्ठा rb_node **p = &sctx->रुकोing_dir_moves.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा रुकोing_dir_move *entry, *dm;

	dm = kदो_स्मृति(माप(*dm), GFP_KERNEL);
	अगर (!dm)
		वापस -ENOMEM;
	dm->ino = ino;
	dm->सूची_हटाओ_ino = 0;
	dm->सूची_हटाओ_gen = 0;
	dm->orphanized = orphanized;

	जबतक (*p) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा रुकोing_dir_move, node);
		अगर (ino < entry->ino) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (ino > entry->ino) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			kमुक्त(dm);
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	rb_link_node(&dm->node, parent, p);
	rb_insert_color(&dm->node, &sctx->रुकोing_dir_moves);
	वापस 0;
पूर्ण

अटल काष्ठा रुकोing_dir_move *
get_रुकोing_dir_move(काष्ठा send_ctx *sctx, u64 ino)
अणु
	काष्ठा rb_node *n = sctx->रुकोing_dir_moves.rb_node;
	काष्ठा रुकोing_dir_move *entry;

	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा रुकोing_dir_move, node);
		अगर (ino < entry->ino)
			n = n->rb_left;
		अन्यथा अगर (ino > entry->ino)
			n = n->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_रुकोing_dir_move(काष्ठा send_ctx *sctx,
				  काष्ठा रुकोing_dir_move *dm)
अणु
	अगर (!dm)
		वापस;
	rb_erase(&dm->node, &sctx->रुकोing_dir_moves);
	kमुक्त(dm);
पूर्ण

अटल पूर्णांक add_pending_dir_move(काष्ठा send_ctx *sctx,
				u64 ino,
				u64 ino_gen,
				u64 parent_ino,
				काष्ठा list_head *new_refs,
				काष्ठा list_head *deleted_refs,
				स्थिर bool is_orphan)
अणु
	काष्ठा rb_node **p = &sctx->pending_dir_moves.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा pending_dir_move *entry = शून्य, *pm;
	काष्ठा recorded_ref *cur;
	पूर्णांक exists = 0;
	पूर्णांक ret;

	pm = kदो_स्मृति(माप(*pm), GFP_KERNEL);
	अगर (!pm)
		वापस -ENOMEM;
	pm->parent_ino = parent_ino;
	pm->ino = ino;
	pm->gen = ino_gen;
	INIT_LIST_HEAD(&pm->list);
	INIT_LIST_HEAD(&pm->update_refs);
	RB_CLEAR_NODE(&pm->node);

	जबतक (*p) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा pending_dir_move, node);
		अगर (parent_ino < entry->parent_ino) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (parent_ino > entry->parent_ino) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			exists = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(cur, deleted_refs, list) अणु
		ret = dup_ref(cur, &pm->update_refs);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
	list_क्रम_each_entry(cur, new_refs, list) अणु
		ret = dup_ref(cur, &pm->update_refs);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = add_रुकोing_dir_move(sctx, pm->ino, is_orphan);
	अगर (ret)
		जाओ out;

	अगर (exists) अणु
		list_add_tail(&pm->list, &entry->list);
	पूर्ण अन्यथा अणु
		rb_link_node(&pm->node, parent, p);
		rb_insert_color(&pm->node, &sctx->pending_dir_moves);
	पूर्ण
	ret = 0;
out:
	अगर (ret) अणु
		__मुक्त_recorded_refs(&pm->update_refs);
		kमुक्त(pm);
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा pending_dir_move *get_pending_dir_moves(काष्ठा send_ctx *sctx,
						      u64 parent_ino)
अणु
	काष्ठा rb_node *n = sctx->pending_dir_moves.rb_node;
	काष्ठा pending_dir_move *entry;

	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा pending_dir_move, node);
		अगर (parent_ino < entry->parent_ino)
			n = n->rb_left;
		अन्यथा अगर (parent_ino > entry->parent_ino)
			n = n->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक path_loop(काष्ठा send_ctx *sctx, काष्ठा fs_path *name,
		     u64 ino, u64 gen, u64 *ancestor_ino)
अणु
	पूर्णांक ret = 0;
	u64 parent_inode = 0;
	u64 parent_gen = 0;
	u64 start_ino = ino;

	*ancestor_ino = 0;
	जबतक (ino != BTRFS_FIRST_FREE_OBJECTID) अणु
		fs_path_reset(name);

		अगर (is_रुकोing_क्रम_rm(sctx, ino, gen))
			अवरोध;
		अगर (is_रुकोing_क्रम_move(sctx, ino)) अणु
			अगर (*ancestor_ino == 0)
				*ancestor_ino = ino;
			ret = get_first_ref(sctx->parent_root, ino,
					    &parent_inode, &parent_gen, name);
		पूर्ण अन्यथा अणु
			ret = __get_cur_name_and_parent(sctx, ino, gen,
							&parent_inode,
							&parent_gen, name);
			अगर (ret > 0) अणु
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (ret < 0)
			अवरोध;
		अगर (parent_inode == start_ino) अणु
			ret = 1;
			अगर (*ancestor_ino == 0)
				*ancestor_ino = ino;
			अवरोध;
		पूर्ण
		ino = parent_inode;
		gen = parent_gen;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक apply_dir_move(काष्ठा send_ctx *sctx, काष्ठा pending_dir_move *pm)
अणु
	काष्ठा fs_path *from_path = शून्य;
	काष्ठा fs_path *to_path = शून्य;
	काष्ठा fs_path *name = शून्य;
	u64 orig_progress = sctx->send_progress;
	काष्ठा recorded_ref *cur;
	u64 parent_ino, parent_gen;
	काष्ठा रुकोing_dir_move *dm = शून्य;
	u64 सूची_हटाओ_ino = 0;
	u64 सूची_हटाओ_gen;
	u64 ancestor;
	bool is_orphan;
	पूर्णांक ret;

	name = fs_path_alloc();
	from_path = fs_path_alloc();
	अगर (!name || !from_path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	dm = get_रुकोing_dir_move(sctx, pm->ino);
	ASSERT(dm);
	सूची_हटाओ_ino = dm->सूची_हटाओ_ino;
	सूची_हटाओ_gen = dm->सूची_हटाओ_gen;
	is_orphan = dm->orphanized;
	मुक्त_रुकोing_dir_move(sctx, dm);

	अगर (is_orphan) अणु
		ret = gen_unique_name(sctx, pm->ino,
				      pm->gen, from_path);
	पूर्ण अन्यथा अणु
		ret = get_first_ref(sctx->parent_root, pm->ino,
				    &parent_ino, &parent_gen, name);
		अगर (ret < 0)
			जाओ out;
		ret = get_cur_path(sctx, parent_ino, parent_gen,
				   from_path);
		अगर (ret < 0)
			जाओ out;
		ret = fs_path_add_path(from_path, name);
	पूर्ण
	अगर (ret < 0)
		जाओ out;

	sctx->send_progress = sctx->cur_ino + 1;
	ret = path_loop(sctx, name, pm->ino, pm->gen, &ancestor);
	अगर (ret < 0)
		जाओ out;
	अगर (ret) अणु
		LIST_HEAD(deleted_refs);
		ASSERT(ancestor > BTRFS_FIRST_FREE_OBJECTID);
		ret = add_pending_dir_move(sctx, pm->ino, pm->gen, ancestor,
					   &pm->update_refs, &deleted_refs,
					   is_orphan);
		अगर (ret < 0)
			जाओ out;
		अगर (सूची_हटाओ_ino) अणु
			dm = get_रुकोing_dir_move(sctx, pm->ino);
			ASSERT(dm);
			dm->सूची_हटाओ_ino = सूची_हटाओ_ino;
			dm->सूची_हटाओ_gen = सूची_हटाओ_gen;
		पूर्ण
		जाओ out;
	पूर्ण
	fs_path_reset(name);
	to_path = name;
	name = शून्य;
	ret = get_cur_path(sctx, pm->ino, pm->gen, to_path);
	अगर (ret < 0)
		जाओ out;

	ret = send_नाम(sctx, from_path, to_path);
	अगर (ret < 0)
		जाओ out;

	अगर (सूची_हटाओ_ino) अणु
		काष्ठा orphan_dir_info *odi;
		u64 gen;

		odi = get_orphan_dir_info(sctx, सूची_हटाओ_ino, सूची_हटाओ_gen);
		अगर (!odi) अणु
			/* alपढ़ोy deleted */
			जाओ finish;
		पूर्ण
		gen = odi->gen;

		ret = can_सूची_हटाओ(sctx, सूची_हटाओ_ino, gen, sctx->cur_ino);
		अगर (ret < 0)
			जाओ out;
		अगर (!ret)
			जाओ finish;

		name = fs_path_alloc();
		अगर (!name) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		ret = get_cur_path(sctx, सूची_हटाओ_ino, gen, name);
		अगर (ret < 0)
			जाओ out;
		ret = send_सूची_हटाओ(sctx, name);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

finish:
	ret = send_uबार(sctx, pm->ino, pm->gen);
	अगर (ret < 0)
		जाओ out;

	/*
	 * After नाम/move, need to update the uबार of both new parent(s)
	 * and old parent(s).
	 */
	list_क्रम_each_entry(cur, &pm->update_refs, list) अणु
		/*
		 * The parent inode might have been deleted in the send snapshot
		 */
		ret = get_inode_info(sctx->send_root, cur->dir, शून्य,
				     शून्य, शून्य, शून्य, शून्य, शून्य);
		अगर (ret == -ENOENT) अणु
			ret = 0;
			जारी;
		पूर्ण
		अगर (ret < 0)
			जाओ out;

		ret = send_uबार(sctx, cur->dir, cur->dir_gen);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	fs_path_मुक्त(name);
	fs_path_मुक्त(from_path);
	fs_path_मुक्त(to_path);
	sctx->send_progress = orig_progress;

	वापस ret;
पूर्ण

अटल व्योम मुक्त_pending_move(काष्ठा send_ctx *sctx, काष्ठा pending_dir_move *m)
अणु
	अगर (!list_empty(&m->list))
		list_del(&m->list);
	अगर (!RB_EMPTY_NODE(&m->node))
		rb_erase(&m->node, &sctx->pending_dir_moves);
	__मुक्त_recorded_refs(&m->update_refs);
	kमुक्त(m);
पूर्ण

अटल व्योम tail_append_pending_moves(काष्ठा send_ctx *sctx,
				      काष्ठा pending_dir_move *moves,
				      काष्ठा list_head *stack)
अणु
	अगर (list_empty(&moves->list)) अणु
		list_add_tail(&moves->list, stack);
	पूर्ण अन्यथा अणु
		LIST_HEAD(list);
		list_splice_init(&moves->list, &list);
		list_add_tail(&moves->list, stack);
		list_splice_tail(&list, stack);
	पूर्ण
	अगर (!RB_EMPTY_NODE(&moves->node)) अणु
		rb_erase(&moves->node, &sctx->pending_dir_moves);
		RB_CLEAR_NODE(&moves->node);
	पूर्ण
पूर्ण

अटल पूर्णांक apply_children_dir_moves(काष्ठा send_ctx *sctx)
अणु
	काष्ठा pending_dir_move *pm;
	काष्ठा list_head stack;
	u64 parent_ino = sctx->cur_ino;
	पूर्णांक ret = 0;

	pm = get_pending_dir_moves(sctx, parent_ino);
	अगर (!pm)
		वापस 0;

	INIT_LIST_HEAD(&stack);
	tail_append_pending_moves(sctx, pm, &stack);

	जबतक (!list_empty(&stack)) अणु
		pm = list_first_entry(&stack, काष्ठा pending_dir_move, list);
		parent_ino = pm->ino;
		ret = apply_dir_move(sctx, pm);
		मुक्त_pending_move(sctx, pm);
		अगर (ret)
			जाओ out;
		pm = get_pending_dir_moves(sctx, parent_ino);
		अगर (pm)
			tail_append_pending_moves(sctx, pm, &stack);
	पूर्ण
	वापस 0;

out:
	जबतक (!list_empty(&stack)) अणु
		pm = list_first_entry(&stack, काष्ठा pending_dir_move, list);
		मुक्त_pending_move(sctx, pm);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * We might need to delay a directory नाम even when no ancestor directory
 * (in the send root) with a higher inode number than ours (sctx->cur_ino) was
 * नामd. This happens when we नाम a directory to the old name (the name
 * in the parent root) of some other unrelated directory that got its नाम
 * delayed due to some ancestor with higher number that got नामd.
 *
 * Example:
 *
 * Parent snapshot:
 * .                                       (ino 256)
 * |---- a/                                (ino 257)
 * |     |---- file                        (ino 260)
 * |
 * |---- b/                                (ino 258)
 * |---- c/                                (ino 259)
 *
 * Send snapshot:
 * .                                       (ino 256)
 * |---- a/                                (ino 258)
 * |---- x/                                (ino 259)
 *       |---- y/                          (ino 257)
 *             |----- file                 (ino 260)
 *
 * Here we can not नाम 258 from 'b' to 'a' without the नाम of inode 257
 * from 'a' to 'x/y' happening first, which in turn depends on the नाम of
 * inode 259 from 'c' to 'x'. So the order of नाम commands the send stream
 * must issue is:
 *
 * 1 - नाम 259 from 'c' to 'x'
 * 2 - नाम 257 from 'a' to 'x/y'
 * 3 - नाम 258 from 'b' to 'a'
 *
 * Returns 1 अगर the नाम of sctx->cur_ino needs to be delayed, 0 अगर it can
 * be करोne right away and < 0 on error.
 */
अटल पूर्णांक रुको_क्रम_dest_dir_move(काष्ठा send_ctx *sctx,
				  काष्ठा recorded_ref *parent_ref,
				  स्थिर bool is_orphan)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->parent_root->fs_info;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key di_key;
	काष्ठा btrfs_dir_item *di;
	u64 left_gen;
	u64 right_gen;
	पूर्णांक ret = 0;
	काष्ठा रुकोing_dir_move *wdm;

	अगर (RB_EMPTY_ROOT(&sctx->रुकोing_dir_moves))
		वापस 0;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = parent_ref->dir;
	key.type = BTRFS_सूची_ITEM_KEY;
	key.offset = btrfs_name_hash(parent_ref->name, parent_ref->name_len);

	ret = btrfs_search_slot(शून्य, sctx->parent_root, &key, path, 0, 0);
	अगर (ret < 0) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	di = btrfs_match_dir_item_name(fs_info, path, parent_ref->name,
				       parent_ref->name_len);
	अगर (!di) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	/*
	 * di_key.objectid has the number of the inode that has a dentry in the
	 * parent directory with the same name that sctx->cur_ino is being
	 * नामd to. We need to check अगर that inode is in the send root as
	 * well and अगर it is currently marked as an inode with a pending नाम,
	 * अगर it is, we need to delay the नाम of sctx->cur_ino as well, so
	 * that it happens after that other inode is नामd.
	 */
	btrfs_dir_item_key_to_cpu(path->nodes[0], di, &di_key);
	अगर (di_key.type != BTRFS_INODE_ITEM_KEY) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	ret = get_inode_info(sctx->parent_root, di_key.objectid, शून्य,
			     &left_gen, शून्य, शून्य, शून्य, शून्य);
	अगर (ret < 0)
		जाओ out;
	ret = get_inode_info(sctx->send_root, di_key.objectid, शून्य,
			     &right_gen, शून्य, शून्य, शून्य, शून्य);
	अगर (ret < 0) अणु
		अगर (ret == -ENOENT)
			ret = 0;
		जाओ out;
	पूर्ण

	/* Dअगरferent inode, no need to delay the नाम of sctx->cur_ino */
	अगर (right_gen != left_gen) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	wdm = get_रुकोing_dir_move(sctx, di_key.objectid);
	अगर (wdm && !wdm->orphanized) अणु
		ret = add_pending_dir_move(sctx,
					   sctx->cur_ino,
					   sctx->cur_inode_gen,
					   di_key.objectid,
					   &sctx->new_refs,
					   &sctx->deleted_refs,
					   is_orphan);
		अगर (!ret)
			ret = 1;
	पूर्ण
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * Check अगर inode ino2, or any of its ancestors, is inode ino1.
 * Return 1 अगर true, 0 अगर false and < 0 on error.
 */
अटल पूर्णांक check_ino_in_path(काष्ठा btrfs_root *root,
			     स्थिर u64 ino1,
			     स्थिर u64 ino1_gen,
			     स्थिर u64 ino2,
			     स्थिर u64 ino2_gen,
			     काष्ठा fs_path *fs_path)
अणु
	u64 ino = ino2;

	अगर (ino1 == ino2)
		वापस ino1_gen == ino2_gen;

	जबतक (ino > BTRFS_FIRST_FREE_OBJECTID) अणु
		u64 parent;
		u64 parent_gen;
		पूर्णांक ret;

		fs_path_reset(fs_path);
		ret = get_first_ref(root, ino, &parent, &parent_gen, fs_path);
		अगर (ret < 0)
			वापस ret;
		अगर (parent == ino1)
			वापस parent_gen == ino1_gen;
		ino = parent;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Check अगर ino ino1 is an ancestor of inode ino2 in the given root क्रम any
 * possible path (in हाल ino2 is not a directory and has multiple hard links).
 * Return 1 अगर true, 0 अगर false and < 0 on error.
 */
अटल पूर्णांक is_ancestor(काष्ठा btrfs_root *root,
		       स्थिर u64 ino1,
		       स्थिर u64 ino1_gen,
		       स्थिर u64 ino2,
		       काष्ठा fs_path *fs_path)
अणु
	bool मुक्त_fs_path = false;
	पूर्णांक ret = 0;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा btrfs_key key;

	अगर (!fs_path) अणु
		fs_path = fs_path_alloc();
		अगर (!fs_path)
			वापस -ENOMEM;
		मुक्त_fs_path = true;
	पूर्ण

	path = alloc_path_क्रम_send();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	key.objectid = ino2;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = 0;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;

	जबतक (true) अणु
		काष्ठा extent_buffer *leaf = path->nodes[0];
		पूर्णांक slot = path->slots[0];
		u32 cur_offset = 0;
		u32 item_size;

		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ out;
			अगर (ret > 0)
				अवरोध;
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, slot);
		अगर (key.objectid != ino2)
			अवरोध;
		अगर (key.type != BTRFS_INODE_REF_KEY &&
		    key.type != BTRFS_INODE_EXTREF_KEY)
			अवरोध;

		item_size = btrfs_item_size_nr(leaf, slot);
		जबतक (cur_offset < item_size) अणु
			u64 parent;
			u64 parent_gen;

			अगर (key.type == BTRFS_INODE_EXTREF_KEY) अणु
				अचिन्हित दीर्घ ptr;
				काष्ठा btrfs_inode_extref *extref;

				ptr = btrfs_item_ptr_offset(leaf, slot);
				extref = (काष्ठा btrfs_inode_extref *)
					(ptr + cur_offset);
				parent = btrfs_inode_extref_parent(leaf,
								   extref);
				cur_offset += माप(*extref);
				cur_offset += btrfs_inode_extref_name_len(leaf,
								  extref);
			पूर्ण अन्यथा अणु
				parent = key.offset;
				cur_offset = item_size;
			पूर्ण

			ret = get_inode_info(root, parent, शून्य, &parent_gen,
					     शून्य, शून्य, शून्य, शून्य);
			अगर (ret < 0)
				जाओ out;
			ret = check_ino_in_path(root, ino1, ino1_gen,
						parent, parent_gen, fs_path);
			अगर (ret)
				जाओ out;
		पूर्ण
		path->slots[0]++;
	पूर्ण
	ret = 0;
 out:
	btrfs_मुक्त_path(path);
	अगर (मुक्त_fs_path)
		fs_path_मुक्त(fs_path);
	वापस ret;
पूर्ण

अटल पूर्णांक रुको_क्रम_parent_move(काष्ठा send_ctx *sctx,
				काष्ठा recorded_ref *parent_ref,
				स्थिर bool is_orphan)
अणु
	पूर्णांक ret = 0;
	u64 ino = parent_ref->dir;
	u64 ino_gen = parent_ref->dir_gen;
	u64 parent_ino_beक्रमe, parent_ino_after;
	काष्ठा fs_path *path_beक्रमe = शून्य;
	काष्ठा fs_path *path_after = शून्य;
	पूर्णांक len1, len2;

	path_after = fs_path_alloc();
	path_beक्रमe = fs_path_alloc();
	अगर (!path_after || !path_beक्रमe) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Our current directory inode may not yet be नामd/moved because some
	 * ancestor (immediate or not) has to be नामd/moved first. So find अगर
	 * such ancestor exists and make sure our own नाम/move happens after
	 * that ancestor is processed to aव्योम path build infinite loops (करोne
	 * at get_cur_path()).
	 */
	जबतक (ino > BTRFS_FIRST_FREE_OBJECTID) अणु
		u64 parent_ino_after_gen;

		अगर (is_रुकोing_क्रम_move(sctx, ino)) अणु
			/*
			 * If the current inode is an ancestor of ino in the
			 * parent root, we need to delay the नाम of the
			 * current inode, otherwise करोn't delayed the नाम
			 * because we can end up with a circular dependency
			 * of नामs, resulting in some directories never
			 * getting the respective नाम operations issued in
			 * the send stream or getting पूर्णांकo infinite path build
			 * loops.
			 */
			ret = is_ancestor(sctx->parent_root,
					  sctx->cur_ino, sctx->cur_inode_gen,
					  ino, path_beक्रमe);
			अगर (ret)
				अवरोध;
		पूर्ण

		fs_path_reset(path_beक्रमe);
		fs_path_reset(path_after);

		ret = get_first_ref(sctx->send_root, ino, &parent_ino_after,
				    &parent_ino_after_gen, path_after);
		अगर (ret < 0)
			जाओ out;
		ret = get_first_ref(sctx->parent_root, ino, &parent_ino_beक्रमe,
				    शून्य, path_beक्रमe);
		अगर (ret < 0 && ret != -ENOENT) अणु
			जाओ out;
		पूर्ण अन्यथा अगर (ret == -ENOENT) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		len1 = fs_path_len(path_beक्रमe);
		len2 = fs_path_len(path_after);
		अगर (ino > sctx->cur_ino &&
		    (parent_ino_beक्रमe != parent_ino_after || len1 != len2 ||
		     स_भेद(path_beक्रमe->start, path_after->start, len1))) अणु
			u64 parent_ino_gen;

			ret = get_inode_info(sctx->parent_root, ino, शून्य,
					     &parent_ino_gen, शून्य, शून्य, शून्य,
					     शून्य);
			अगर (ret < 0)
				जाओ out;
			अगर (ino_gen == parent_ino_gen) अणु
				ret = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		ino = parent_ino_after;
		ino_gen = parent_ino_after_gen;
	पूर्ण

out:
	fs_path_मुक्त(path_beक्रमe);
	fs_path_मुक्त(path_after);

	अगर (ret == 1) अणु
		ret = add_pending_dir_move(sctx,
					   sctx->cur_ino,
					   sctx->cur_inode_gen,
					   ino,
					   &sctx->new_refs,
					   &sctx->deleted_refs,
					   is_orphan);
		अगर (!ret)
			ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक update_ref_path(काष्ठा send_ctx *sctx, काष्ठा recorded_ref *ref)
अणु
	पूर्णांक ret;
	काष्ठा fs_path *new_path;

	/*
	 * Our reference's name member poपूर्णांकs to its full_path member string, so
	 * we use here a new path.
	 */
	new_path = fs_path_alloc();
	अगर (!new_path)
		वापस -ENOMEM;

	ret = get_cur_path(sctx, ref->dir, ref->dir_gen, new_path);
	अगर (ret < 0) अणु
		fs_path_मुक्त(new_path);
		वापस ret;
	पूर्ण
	ret = fs_path_add(new_path, ref->name, ref->name_len);
	अगर (ret < 0) अणु
		fs_path_मुक्त(new_path);
		वापस ret;
	पूर्ण

	fs_path_मुक्त(ref->full_path);
	set_ref_path(ref, new_path);

	वापस 0;
पूर्ण

/*
 * When processing the new references क्रम an inode we may orphanize an existing
 * directory inode because its old name conflicts with one of the new references
 * of the current inode. Later, when processing another new reference of our
 * inode, we might need to orphanize another inode, but the path we have in the
 * reference reflects the pre-orphanization name of the directory we previously
 * orphanized. For example:
 *
 * parent snapshot looks like:
 *
 * .                                     (ino 256)
 * |----- f1                             (ino 257)
 * |----- f2                             (ino 258)
 * |----- d1/                            (ino 259)
 *        |----- d2/                     (ino 260)
 *
 * send snapshot looks like:
 *
 * .                                     (ino 256)
 * |----- d1                             (ino 258)
 * |----- f2/                            (ino 259)
 *        |----- f2_link/                (ino 260)
 *        |       |----- f1              (ino 257)
 *        |
 *        |----- d2                      (ino 258)
 *
 * When processing inode 257 we compute the name क्रम inode 259 as "d1", and we
 * cache it in the name cache. Later when we start processing inode 258, when
 * collecting all its new references we set a full path of "d1/d2" क्रम its new
 * reference with name "d2". When we start processing the new references we
 * start by processing the new reference with name "d1", and this results in
 * orphanizing inode 259, since its old reference causes a conflict. Then we
 * move on the next new reference, with name "d2", and we find out we must
 * orphanize inode 260, as its old reference conflicts with ours - but क्रम the
 * orphanization we use a source path corresponding to the path we stored in the
 * new reference, which is "d1/d2" and not "o259-6-0/d2" - this makes the
 * receiver fail since the path component "d1/" no दीर्घer exists, it was नामd
 * to "o259-6-0/" when processing the previous new reference. So in this हाल we
 * must recompute the path in the new reference and use it क्रम the new
 * orphanization operation.
 */
अटल पूर्णांक refresh_ref_path(काष्ठा send_ctx *sctx, काष्ठा recorded_ref *ref)
अणु
	अक्षर *name;
	पूर्णांक ret;

	name = kmemdup(ref->name, ref->name_len, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;

	fs_path_reset(ref->full_path);
	ret = get_cur_path(sctx, ref->dir, ref->dir_gen, ref->full_path);
	अगर (ret < 0)
		जाओ out;

	ret = fs_path_add(ref->full_path, name, ref->name_len);
	अगर (ret < 0)
		जाओ out;

	/* Update the reference's base name poपूर्णांकer. */
	set_ref_path(ref, ref->full_path);
out:
	kमुक्त(name);
	वापस ret;
पूर्ण

/*
 * This करोes all the move/link/unlink/सूची_हटाओ magic.
 */
अटल पूर्णांक process_recorded_refs(काष्ठा send_ctx *sctx, पूर्णांक *pending_move)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	पूर्णांक ret = 0;
	काष्ठा recorded_ref *cur;
	काष्ठा recorded_ref *cur2;
	काष्ठा list_head check_dirs;
	काष्ठा fs_path *valid_path = शून्य;
	u64 ow_inode = 0;
	u64 ow_gen;
	u64 ow_mode;
	पूर्णांक did_overग_लिखो = 0;
	पूर्णांक is_orphan = 0;
	u64 last_dir_ino_rm = 0;
	bool can_नाम = true;
	bool orphanized_dir = false;
	bool orphanized_ancestor = false;

	btrfs_debug(fs_info, "process_recorded_refs %llu", sctx->cur_ino);

	/*
	 * This should never happen as the root dir always has the same ref
	 * which is always '..'
	 */
	BUG_ON(sctx->cur_ino <= BTRFS_FIRST_FREE_OBJECTID);
	INIT_LIST_HEAD(&check_dirs);

	valid_path = fs_path_alloc();
	अगर (!valid_path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * First, check अगर the first ref of the current inode was overwritten
	 * beक्रमe. If yes, we know that the current inode was alपढ़ोy orphanized
	 * and thus use the orphan name. If not, we can use get_cur_path to
	 * get the path of the first ref as it would like जबतक receiving at
	 * this poपूर्णांक in समय.
	 * New inodes are always orphan at the beginning, so क्रमce to use the
	 * orphan name in this हाल.
	 * The first ref is stored in valid_path and will be updated अगर it
	 * माला_लो moved around.
	 */
	अगर (!sctx->cur_inode_new) अणु
		ret = did_overग_लिखो_first_ref(sctx, sctx->cur_ino,
				sctx->cur_inode_gen);
		अगर (ret < 0)
			जाओ out;
		अगर (ret)
			did_overग_लिखो = 1;
	पूर्ण
	अगर (sctx->cur_inode_new || did_overग_लिखो) अणु
		ret = gen_unique_name(sctx, sctx->cur_ino,
				sctx->cur_inode_gen, valid_path);
		अगर (ret < 0)
			जाओ out;
		is_orphan = 1;
	पूर्ण अन्यथा अणु
		ret = get_cur_path(sctx, sctx->cur_ino, sctx->cur_inode_gen,
				valid_path);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	/*
	 * Beक्रमe करोing any नाम and link operations, करो a first pass on the
	 * new references to orphanize any unprocessed inodes that may have a
	 * reference that conflicts with one of the new references of the current
	 * inode. This needs to happen first because a new reference may conflict
	 * with the old reference of a parent directory, so we must make sure
	 * that the path used क्रम link and नाम commands करोn't use an
	 * orphanized name when an ancestor was not yet orphanized.
	 *
	 * Example:
	 *
	 * Parent snapshot:
	 *
	 * .                                                      (ino 256)
	 * |----- testdir/                                        (ino 259)
	 * |          |----- a                                    (ino 257)
	 * |
	 * |----- b                                               (ino 258)
	 *
	 * Send snapshot:
	 *
	 * .                                                      (ino 256)
	 * |----- testdir_2/                                      (ino 259)
	 * |          |----- a                                    (ino 260)
	 * |
	 * |----- testdir                                         (ino 257)
	 * |----- b                                               (ino 257)
	 * |----- b2                                              (ino 258)
	 *
	 * Processing the new reference क्रम inode 257 with name "b" may happen
	 * beक्रमe processing the new reference with name "testdir". If so, we
	 * must make sure that by the समय we send a link command to create the
	 * hard link "b", inode 259 was alपढ़ोy orphanized, since the generated
	 * path in "valid_path" alपढ़ोy contains the orphanized name क्रम 259.
	 * We are processing inode 257, so only later when processing 259 we करो
	 * the नाम operation to change its temporary (orphanized) name to
	 * "testdir_2".
	 */
	list_क्रम_each_entry(cur, &sctx->new_refs, list) अणु
		ret = get_cur_inode_state(sctx, cur->dir, cur->dir_gen);
		अगर (ret < 0)
			जाओ out;
		अगर (ret == inode_state_will_create)
			जारी;

		/*
		 * Check अगर this new ref would overग_लिखो the first ref of another
		 * unprocessed inode. If yes, orphanize the overwritten inode.
		 * If we find an overwritten ref that is not the first ref,
		 * simply unlink it.
		 */
		ret = will_overग_लिखो_ref(sctx, cur->dir, cur->dir_gen,
				cur->name, cur->name_len,
				&ow_inode, &ow_gen, &ow_mode);
		अगर (ret < 0)
			जाओ out;
		अगर (ret) अणु
			ret = is_first_ref(sctx->parent_root,
					   ow_inode, cur->dir, cur->name,
					   cur->name_len);
			अगर (ret < 0)
				जाओ out;
			अगर (ret) अणु
				काष्ठा name_cache_entry *nce;
				काष्ठा रुकोing_dir_move *wdm;

				अगर (orphanized_dir) अणु
					ret = refresh_ref_path(sctx, cur);
					अगर (ret < 0)
						जाओ out;
				पूर्ण

				ret = orphanize_inode(sctx, ow_inode, ow_gen,
						cur->full_path);
				अगर (ret < 0)
					जाओ out;
				अगर (S_ISसूची(ow_mode))
					orphanized_dir = true;

				/*
				 * If ow_inode has its नाम operation delayed
				 * make sure that its orphanized name is used in
				 * the source path when perक्रमming its नाम
				 * operation.
				 */
				अगर (is_रुकोing_क्रम_move(sctx, ow_inode)) अणु
					wdm = get_रुकोing_dir_move(sctx,
								   ow_inode);
					ASSERT(wdm);
					wdm->orphanized = true;
				पूर्ण

				/*
				 * Make sure we clear our orphanized inode's
				 * name from the name cache. This is because the
				 * inode ow_inode might be an ancestor of some
				 * other inode that will be orphanized as well
				 * later and has an inode number greater than
				 * sctx->send_progress. We need to prevent
				 * future name lookups from using the old name
				 * and get instead the orphan name.
				 */
				nce = name_cache_search(sctx, ow_inode, ow_gen);
				अगर (nce) अणु
					name_cache_delete(sctx, nce);
					kमुक्त(nce);
				पूर्ण

				/*
				 * ow_inode might currently be an ancestor of
				 * cur_ino, thereक्रमe compute valid_path (the
				 * current path of cur_ino) again because it
				 * might contain the pre-orphanization name of
				 * ow_inode, which is no दीर्घer valid.
				 */
				ret = is_ancestor(sctx->parent_root,
						  ow_inode, ow_gen,
						  sctx->cur_ino, शून्य);
				अगर (ret > 0) अणु
					orphanized_ancestor = true;
					fs_path_reset(valid_path);
					ret = get_cur_path(sctx, sctx->cur_ino,
							   sctx->cur_inode_gen,
							   valid_path);
				पूर्ण
				अगर (ret < 0)
					जाओ out;
			पूर्ण अन्यथा अणु
				ret = send_unlink(sctx, cur->full_path);
				अगर (ret < 0)
					जाओ out;
			पूर्ण
		पूर्ण

	पूर्ण

	list_क्रम_each_entry(cur, &sctx->new_refs, list) अणु
		/*
		 * We may have refs where the parent directory करोes not exist
		 * yet. This happens अगर the parent directories inum is higher
		 * than the current inum. To handle this हाल, we create the
		 * parent directory out of order. But we need to check अगर this
		 * did alपढ़ोy happen beक्रमe due to other refs in the same dir.
		 */
		ret = get_cur_inode_state(sctx, cur->dir, cur->dir_gen);
		अगर (ret < 0)
			जाओ out;
		अगर (ret == inode_state_will_create) अणु
			ret = 0;
			/*
			 * First check अगर any of the current inodes refs did
			 * alपढ़ोy create the dir.
			 */
			list_क्रम_each_entry(cur2, &sctx->new_refs, list) अणु
				अगर (cur == cur2)
					अवरोध;
				अगर (cur2->dir == cur->dir) अणु
					ret = 1;
					अवरोध;
				पूर्ण
			पूर्ण

			/*
			 * If that did not happen, check अगर a previous inode
			 * did alपढ़ोy create the dir.
			 */
			अगर (!ret)
				ret = did_create_dir(sctx, cur->dir);
			अगर (ret < 0)
				जाओ out;
			अगर (!ret) अणु
				ret = send_create_inode(sctx, cur->dir);
				अगर (ret < 0)
					जाओ out;
			पूर्ण
		पूर्ण

		अगर (S_ISसूची(sctx->cur_inode_mode) && sctx->parent_root) अणु
			ret = रुको_क्रम_dest_dir_move(sctx, cur, is_orphan);
			अगर (ret < 0)
				जाओ out;
			अगर (ret == 1) अणु
				can_नाम = false;
				*pending_move = 1;
			पूर्ण
		पूर्ण

		अगर (S_ISसूची(sctx->cur_inode_mode) && sctx->parent_root &&
		    can_नाम) अणु
			ret = रुको_क्रम_parent_move(sctx, cur, is_orphan);
			अगर (ret < 0)
				जाओ out;
			अगर (ret == 1) अणु
				can_नाम = false;
				*pending_move = 1;
			पूर्ण
		पूर्ण

		/*
		 * link/move the ref to the new place. If we have an orphan
		 * inode, move it and update valid_path. If not, link or move
		 * it depending on the inode mode.
		 */
		अगर (is_orphan && can_नाम) अणु
			ret = send_नाम(sctx, valid_path, cur->full_path);
			अगर (ret < 0)
				जाओ out;
			is_orphan = 0;
			ret = fs_path_copy(valid_path, cur->full_path);
			अगर (ret < 0)
				जाओ out;
		पूर्ण अन्यथा अगर (can_नाम) अणु
			अगर (S_ISसूची(sctx->cur_inode_mode)) अणु
				/*
				 * Dirs can't be linked, so move it. For moved
				 * dirs, we always have one new and one deleted
				 * ref. The deleted ref is ignored later.
				 */
				ret = send_नाम(sctx, valid_path,
						  cur->full_path);
				अगर (!ret)
					ret = fs_path_copy(valid_path,
							   cur->full_path);
				अगर (ret < 0)
					जाओ out;
			पूर्ण अन्यथा अणु
				/*
				 * We might have previously orphanized an inode
				 * which is an ancestor of our current inode,
				 * so our reference's full path, which was
				 * computed beक्रमe any such orphanizations, must
				 * be updated.
				 */
				अगर (orphanized_dir) अणु
					ret = update_ref_path(sctx, cur);
					अगर (ret < 0)
						जाओ out;
				पूर्ण
				ret = send_link(sctx, cur->full_path,
						valid_path);
				अगर (ret < 0)
					जाओ out;
			पूर्ण
		पूर्ण
		ret = dup_ref(cur, &check_dirs);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (S_ISसूची(sctx->cur_inode_mode) && sctx->cur_inode_deleted) अणु
		/*
		 * Check अगर we can alपढ़ोy सूची_हटाओ the directory. If not,
		 * orphanize it. For every dir item inside that माला_लो deleted
		 * later, we करो this check again and सूची_हटाओ it then अगर possible.
		 * See the use of check_dirs क्रम more details.
		 */
		ret = can_सूची_हटाओ(sctx, sctx->cur_ino, sctx->cur_inode_gen,
				sctx->cur_ino);
		अगर (ret < 0)
			जाओ out;
		अगर (ret) अणु
			ret = send_सूची_हटाओ(sctx, valid_path);
			अगर (ret < 0)
				जाओ out;
		पूर्ण अन्यथा अगर (!is_orphan) अणु
			ret = orphanize_inode(sctx, sctx->cur_ino,
					sctx->cur_inode_gen, valid_path);
			अगर (ret < 0)
				जाओ out;
			is_orphan = 1;
		पूर्ण

		list_क्रम_each_entry(cur, &sctx->deleted_refs, list) अणु
			ret = dup_ref(cur, &check_dirs);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (S_ISसूची(sctx->cur_inode_mode) &&
		   !list_empty(&sctx->deleted_refs)) अणु
		/*
		 * We have a moved dir. Add the old parent to check_dirs
		 */
		cur = list_entry(sctx->deleted_refs.next, काष्ठा recorded_ref,
				list);
		ret = dup_ref(cur, &check_dirs);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अगर (!S_ISसूची(sctx->cur_inode_mode)) अणु
		/*
		 * We have a non dir inode. Go through all deleted refs and
		 * unlink them अगर they were not alपढ़ोy overwritten by other
		 * inodes.
		 */
		list_क्रम_each_entry(cur, &sctx->deleted_refs, list) अणु
			ret = did_overग_लिखो_ref(sctx, cur->dir, cur->dir_gen,
					sctx->cur_ino, sctx->cur_inode_gen,
					cur->name, cur->name_len);
			अगर (ret < 0)
				जाओ out;
			अगर (!ret) अणु
				/*
				 * If we orphanized any ancestor beक्रमe, we need
				 * to recompute the full path क्रम deleted names,
				 * since any such path was computed beक्रमe we
				 * processed any references and orphanized any
				 * ancestor inode.
				 */
				अगर (orphanized_ancestor) अणु
					ret = update_ref_path(sctx, cur);
					अगर (ret < 0)
						जाओ out;
				पूर्ण
				ret = send_unlink(sctx, cur->full_path);
				अगर (ret < 0)
					जाओ out;
			पूर्ण
			ret = dup_ref(cur, &check_dirs);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
		/*
		 * If the inode is still orphan, unlink the orphan. This may
		 * happen when a previous inode did overग_लिखो the first ref
		 * of this inode and no new refs were added क्रम the current
		 * inode. Unlinking करोes not mean that the inode is deleted in
		 * all हालs. There may still be links to this inode in other
		 * places.
		 */
		अगर (is_orphan) अणु
			ret = send_unlink(sctx, valid_path);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * We did collect all parent dirs where cur_inode was once located. We
	 * now go through all these dirs and check अगर they are pending क्रम
	 * deletion and अगर it's finally possible to perक्रमm the सूची_हटाओ now.
	 * We also update the inode stats of the parent dirs here.
	 */
	list_क्रम_each_entry(cur, &check_dirs, list) अणु
		/*
		 * In हाल we had refs पूर्णांकo dirs that were not processed yet,
		 * we करोn't need to करो the uसमय and सूची_हटाओ logic क्रम these dirs.
		 * The dir will be processed later.
		 */
		अगर (cur->dir > sctx->cur_ino)
			जारी;

		ret = get_cur_inode_state(sctx, cur->dir, cur->dir_gen);
		अगर (ret < 0)
			जाओ out;

		अगर (ret == inode_state_did_create ||
		    ret == inode_state_no_change) अणु
			/* TODO delayed uबार */
			ret = send_uबार(sctx, cur->dir, cur->dir_gen);
			अगर (ret < 0)
				जाओ out;
		पूर्ण अन्यथा अगर (ret == inode_state_did_delete &&
			   cur->dir != last_dir_ino_rm) अणु
			ret = can_सूची_हटाओ(sctx, cur->dir, cur->dir_gen,
					sctx->cur_ino);
			अगर (ret < 0)
				जाओ out;
			अगर (ret) अणु
				ret = get_cur_path(sctx, cur->dir,
						   cur->dir_gen, valid_path);
				अगर (ret < 0)
					जाओ out;
				ret = send_सूची_हटाओ(sctx, valid_path);
				अगर (ret < 0)
					जाओ out;
				last_dir_ino_rm = cur->dir;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = 0;

out:
	__मुक्त_recorded_refs(&check_dirs);
	मुक्त_recorded_refs(sctx);
	fs_path_मुक्त(valid_path);
	वापस ret;
पूर्ण

अटल पूर्णांक record_ref(काष्ठा btrfs_root *root, u64 dir, काष्ठा fs_path *name,
		      व्योम *ctx, काष्ठा list_head *refs)
अणु
	पूर्णांक ret = 0;
	काष्ठा send_ctx *sctx = ctx;
	काष्ठा fs_path *p;
	u64 gen;

	p = fs_path_alloc();
	अगर (!p)
		वापस -ENOMEM;

	ret = get_inode_info(root, dir, शून्य, &gen, शून्य, शून्य,
			शून्य, शून्य);
	अगर (ret < 0)
		जाओ out;

	ret = get_cur_path(sctx, dir, gen, p);
	अगर (ret < 0)
		जाओ out;
	ret = fs_path_add_path(p, name);
	अगर (ret < 0)
		जाओ out;

	ret = __record_ref(refs, dir, gen, p);

out:
	अगर (ret)
		fs_path_मुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक __record_new_ref(पूर्णांक num, u64 dir, पूर्णांक index,
			    काष्ठा fs_path *name,
			    व्योम *ctx)
अणु
	काष्ठा send_ctx *sctx = ctx;
	वापस record_ref(sctx->send_root, dir, name, ctx, &sctx->new_refs);
पूर्ण


अटल पूर्णांक __record_deleted_ref(पूर्णांक num, u64 dir, पूर्णांक index,
				काष्ठा fs_path *name,
				व्योम *ctx)
अणु
	काष्ठा send_ctx *sctx = ctx;
	वापस record_ref(sctx->parent_root, dir, name, ctx,
			  &sctx->deleted_refs);
पूर्ण

अटल पूर्णांक record_new_ref(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret;

	ret = iterate_inode_ref(sctx->send_root, sctx->left_path,
				sctx->cmp_key, 0, __record_new_ref, sctx);
	अगर (ret < 0)
		जाओ out;
	ret = 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक record_deleted_ref(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret;

	ret = iterate_inode_ref(sctx->parent_root, sctx->right_path,
				sctx->cmp_key, 0, __record_deleted_ref, sctx);
	अगर (ret < 0)
		जाओ out;
	ret = 0;

out:
	वापस ret;
पूर्ण

काष्ठा find_ref_ctx अणु
	u64 dir;
	u64 dir_gen;
	काष्ठा btrfs_root *root;
	काष्ठा fs_path *name;
	पूर्णांक found_idx;
पूर्ण;

अटल पूर्णांक __find_iref(पूर्णांक num, u64 dir, पूर्णांक index,
		       काष्ठा fs_path *name,
		       व्योम *ctx_)
अणु
	काष्ठा find_ref_ctx *ctx = ctx_;
	u64 dir_gen;
	पूर्णांक ret;

	अगर (dir == ctx->dir && fs_path_len(name) == fs_path_len(ctx->name) &&
	    म_भेदन(name->start, ctx->name->start, fs_path_len(name)) == 0) अणु
		/*
		 * To aव्योम करोing extra lookups we'll only करो this अगर everything
		 * अन्यथा matches.
		 */
		ret = get_inode_info(ctx->root, dir, शून्य, &dir_gen, शून्य,
				     शून्य, शून्य, शून्य);
		अगर (ret)
			वापस ret;
		अगर (dir_gen != ctx->dir_gen)
			वापस 0;
		ctx->found_idx = num;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक find_iref(काष्ठा btrfs_root *root,
		     काष्ठा btrfs_path *path,
		     काष्ठा btrfs_key *key,
		     u64 dir, u64 dir_gen, काष्ठा fs_path *name)
अणु
	पूर्णांक ret;
	काष्ठा find_ref_ctx ctx;

	ctx.dir = dir;
	ctx.name = name;
	ctx.dir_gen = dir_gen;
	ctx.found_idx = -1;
	ctx.root = root;

	ret = iterate_inode_ref(root, path, key, 0, __find_iref, &ctx);
	अगर (ret < 0)
		वापस ret;

	अगर (ctx.found_idx == -1)
		वापस -ENOENT;

	वापस ctx.found_idx;
पूर्ण

अटल पूर्णांक __record_changed_new_ref(पूर्णांक num, u64 dir, पूर्णांक index,
				    काष्ठा fs_path *name,
				    व्योम *ctx)
अणु
	u64 dir_gen;
	पूर्णांक ret;
	काष्ठा send_ctx *sctx = ctx;

	ret = get_inode_info(sctx->send_root, dir, शून्य, &dir_gen, शून्य,
			     शून्य, शून्य, शून्य);
	अगर (ret)
		वापस ret;

	ret = find_iref(sctx->parent_root, sctx->right_path,
			sctx->cmp_key, dir, dir_gen, name);
	अगर (ret == -ENOENT)
		ret = __record_new_ref(num, dir, index, name, sctx);
	अन्यथा अगर (ret > 0)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक __record_changed_deleted_ref(पूर्णांक num, u64 dir, पूर्णांक index,
					काष्ठा fs_path *name,
					व्योम *ctx)
अणु
	u64 dir_gen;
	पूर्णांक ret;
	काष्ठा send_ctx *sctx = ctx;

	ret = get_inode_info(sctx->parent_root, dir, शून्य, &dir_gen, शून्य,
			     शून्य, शून्य, शून्य);
	अगर (ret)
		वापस ret;

	ret = find_iref(sctx->send_root, sctx->left_path, sctx->cmp_key,
			dir, dir_gen, name);
	अगर (ret == -ENOENT)
		ret = __record_deleted_ref(num, dir, index, name, sctx);
	अन्यथा अगर (ret > 0)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक record_changed_ref(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret = 0;

	ret = iterate_inode_ref(sctx->send_root, sctx->left_path,
			sctx->cmp_key, 0, __record_changed_new_ref, sctx);
	अगर (ret < 0)
		जाओ out;
	ret = iterate_inode_ref(sctx->parent_root, sctx->right_path,
			sctx->cmp_key, 0, __record_changed_deleted_ref, sctx);
	अगर (ret < 0)
		जाओ out;
	ret = 0;

out:
	वापस ret;
पूर्ण

/*
 * Record and process all refs at once. Needed when an inode changes the
 * generation number, which means that it was deleted and recreated.
 */
अटल पूर्णांक process_all_refs(काष्ठा send_ctx *sctx,
			    क्रमागत btrfs_compare_tree_result cmd)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा extent_buffer *eb;
	पूर्णांक slot;
	iterate_inode_ref_t cb;
	पूर्णांक pending_move = 0;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	अगर (cmd == BTRFS_COMPARE_TREE_NEW) अणु
		root = sctx->send_root;
		cb = __record_new_ref;
	पूर्ण अन्यथा अगर (cmd == BTRFS_COMPARE_TREE_DELETED) अणु
		root = sctx->parent_root;
		cb = __record_deleted_ref;
	पूर्ण अन्यथा अणु
		btrfs_err(sctx->send_root->fs_info,
				"Wrong command %d in process_all_refs", cmd);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	key.objectid = sctx->cmp_key->objectid;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;

	जबतक (1) अणु
		eb = path->nodes[0];
		slot = path->slots[0];
		अगर (slot >= btrfs_header_nritems(eb)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ out;
			अन्यथा अगर (ret > 0)
				अवरोध;
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(eb, &found_key, slot);

		अगर (found_key.objectid != key.objectid ||
		    (found_key.type != BTRFS_INODE_REF_KEY &&
		     found_key.type != BTRFS_INODE_EXTREF_KEY))
			अवरोध;

		ret = iterate_inode_ref(root, path, &found_key, 0, cb, sctx);
		अगर (ret < 0)
			जाओ out;

		path->slots[0]++;
	पूर्ण
	btrfs_release_path(path);

	/*
	 * We करोn't actually care about pending_move as we are simply
	 * re-creating this inode and will be नाम'ing it पूर्णांकo place once we
	 * नाम the parent directory.
	 */
	ret = process_recorded_refs(sctx, &pending_move);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक send_set_xattr(काष्ठा send_ctx *sctx,
			  काष्ठा fs_path *path,
			  स्थिर अक्षर *name, पूर्णांक name_len,
			  स्थिर अक्षर *data, पूर्णांक data_len)
अणु
	पूर्णांक ret = 0;

	ret = begin_cmd(sctx, BTRFS_SEND_C_SET_XATTR);
	अगर (ret < 0)
		जाओ out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, path);
	TLV_PUT_STRING(sctx, BTRFS_SEND_A_XATTR_NAME, name, name_len);
	TLV_PUT(sctx, BTRFS_SEND_A_XATTR_DATA, data, data_len);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	वापस ret;
पूर्ण

अटल पूर्णांक send_हटाओ_xattr(काष्ठा send_ctx *sctx,
			  काष्ठा fs_path *path,
			  स्थिर अक्षर *name, पूर्णांक name_len)
अणु
	पूर्णांक ret = 0;

	ret = begin_cmd(sctx, BTRFS_SEND_C_REMOVE_XATTR);
	अगर (ret < 0)
		जाओ out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, path);
	TLV_PUT_STRING(sctx, BTRFS_SEND_A_XATTR_NAME, name, name_len);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	वापस ret;
पूर्ण

अटल पूर्णांक __process_new_xattr(पूर्णांक num, काष्ठा btrfs_key *di_key,
			       स्थिर अक्षर *name, पूर्णांक name_len,
			       स्थिर अक्षर *data, पूर्णांक data_len,
			       u8 type, व्योम *ctx)
अणु
	पूर्णांक ret;
	काष्ठा send_ctx *sctx = ctx;
	काष्ठा fs_path *p;
	काष्ठा posix_acl_xattr_header dummy_acl;

	/* Capabilities are emitted by finish_inode_अगर_needed */
	अगर (!म_भेदन(name, XATTR_NAME_CAPS, name_len))
		वापस 0;

	p = fs_path_alloc();
	अगर (!p)
		वापस -ENOMEM;

	/*
	 * This hack is needed because empty acls are stored as zero byte
	 * data in xattrs. Problem with that is, that receiving these zero byte
	 * acls will fail later. To fix this, we send a dummy acl list that
	 * only contains the version number and no entries.
	 */
	अगर (!म_भेदन(name, XATTR_NAME_POSIX_ACL_ACCESS, name_len) ||
	    !म_भेदन(name, XATTR_NAME_POSIX_ACL_DEFAULT, name_len)) अणु
		अगर (data_len == 0) अणु
			dummy_acl.a_version =
					cpu_to_le32(POSIX_ACL_XATTR_VERSION);
			data = (अक्षर *)&dummy_acl;
			data_len = माप(dummy_acl);
		पूर्ण
	पूर्ण

	ret = get_cur_path(sctx, sctx->cur_ino, sctx->cur_inode_gen, p);
	अगर (ret < 0)
		जाओ out;

	ret = send_set_xattr(sctx, p, name, name_len, data, data_len);

out:
	fs_path_मुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक __process_deleted_xattr(पूर्णांक num, काष्ठा btrfs_key *di_key,
				   स्थिर अक्षर *name, पूर्णांक name_len,
				   स्थिर अक्षर *data, पूर्णांक data_len,
				   u8 type, व्योम *ctx)
अणु
	पूर्णांक ret;
	काष्ठा send_ctx *sctx = ctx;
	काष्ठा fs_path *p;

	p = fs_path_alloc();
	अगर (!p)
		वापस -ENOMEM;

	ret = get_cur_path(sctx, sctx->cur_ino, sctx->cur_inode_gen, p);
	अगर (ret < 0)
		जाओ out;

	ret = send_हटाओ_xattr(sctx, p, name, name_len);

out:
	fs_path_मुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक process_new_xattr(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret = 0;

	ret = iterate_dir_item(sctx->send_root, sctx->left_path,
			       __process_new_xattr, sctx);

	वापस ret;
पूर्ण

अटल पूर्णांक process_deleted_xattr(काष्ठा send_ctx *sctx)
अणु
	वापस iterate_dir_item(sctx->parent_root, sctx->right_path,
				__process_deleted_xattr, sctx);
पूर्ण

काष्ठा find_xattr_ctx अणु
	स्थिर अक्षर *name;
	पूर्णांक name_len;
	पूर्णांक found_idx;
	अक्षर *found_data;
	पूर्णांक found_data_len;
पूर्ण;

अटल पूर्णांक __find_xattr(पूर्णांक num, काष्ठा btrfs_key *di_key,
			स्थिर अक्षर *name, पूर्णांक name_len,
			स्थिर अक्षर *data, पूर्णांक data_len,
			u8 type, व्योम *vctx)
अणु
	काष्ठा find_xattr_ctx *ctx = vctx;

	अगर (name_len == ctx->name_len &&
	    म_भेदन(name, ctx->name, name_len) == 0) अणु
		ctx->found_idx = num;
		ctx->found_data_len = data_len;
		ctx->found_data = kmemdup(data, data_len, GFP_KERNEL);
		अगर (!ctx->found_data)
			वापस -ENOMEM;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक find_xattr(काष्ठा btrfs_root *root,
		      काष्ठा btrfs_path *path,
		      काष्ठा btrfs_key *key,
		      स्थिर अक्षर *name, पूर्णांक name_len,
		      अक्षर **data, पूर्णांक *data_len)
अणु
	पूर्णांक ret;
	काष्ठा find_xattr_ctx ctx;

	ctx.name = name;
	ctx.name_len = name_len;
	ctx.found_idx = -1;
	ctx.found_data = शून्य;
	ctx.found_data_len = 0;

	ret = iterate_dir_item(root, path, __find_xattr, &ctx);
	अगर (ret < 0)
		वापस ret;

	अगर (ctx.found_idx == -1)
		वापस -ENOENT;
	अगर (data) अणु
		*data = ctx.found_data;
		*data_len = ctx.found_data_len;
	पूर्ण अन्यथा अणु
		kमुक्त(ctx.found_data);
	पूर्ण
	वापस ctx.found_idx;
पूर्ण


अटल पूर्णांक __process_changed_new_xattr(पूर्णांक num, काष्ठा btrfs_key *di_key,
				       स्थिर अक्षर *name, पूर्णांक name_len,
				       स्थिर अक्षर *data, पूर्णांक data_len,
				       u8 type, व्योम *ctx)
अणु
	पूर्णांक ret;
	काष्ठा send_ctx *sctx = ctx;
	अक्षर *found_data = शून्य;
	पूर्णांक found_data_len  = 0;

	ret = find_xattr(sctx->parent_root, sctx->right_path,
			 sctx->cmp_key, name, name_len, &found_data,
			 &found_data_len);
	अगर (ret == -ENOENT) अणु
		ret = __process_new_xattr(num, di_key, name, name_len, data,
				data_len, type, ctx);
	पूर्ण अन्यथा अगर (ret >= 0) अणु
		अगर (data_len != found_data_len ||
		    स_भेद(data, found_data, data_len)) अणु
			ret = __process_new_xattr(num, di_key, name, name_len,
					data, data_len, type, ctx);
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण
	पूर्ण

	kमुक्त(found_data);
	वापस ret;
पूर्ण

अटल पूर्णांक __process_changed_deleted_xattr(पूर्णांक num, काष्ठा btrfs_key *di_key,
					   स्थिर अक्षर *name, पूर्णांक name_len,
					   स्थिर अक्षर *data, पूर्णांक data_len,
					   u8 type, व्योम *ctx)
अणु
	पूर्णांक ret;
	काष्ठा send_ctx *sctx = ctx;

	ret = find_xattr(sctx->send_root, sctx->left_path, sctx->cmp_key,
			 name, name_len, शून्य, शून्य);
	अगर (ret == -ENOENT)
		ret = __process_deleted_xattr(num, di_key, name, name_len, data,
				data_len, type, ctx);
	अन्यथा अगर (ret >= 0)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक process_changed_xattr(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret = 0;

	ret = iterate_dir_item(sctx->send_root, sctx->left_path,
			__process_changed_new_xattr, sctx);
	अगर (ret < 0)
		जाओ out;
	ret = iterate_dir_item(sctx->parent_root, sctx->right_path,
			__process_changed_deleted_xattr, sctx);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक process_all_new_xattrs(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा extent_buffer *eb;
	पूर्णांक slot;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	root = sctx->send_root;

	key.objectid = sctx->cmp_key->objectid;
	key.type = BTRFS_XATTR_ITEM_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;

	जबतक (1) अणु
		eb = path->nodes[0];
		slot = path->slots[0];
		अगर (slot >= btrfs_header_nritems(eb)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0) अणु
				जाओ out;
			पूर्ण अन्यथा अगर (ret > 0) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(eb, &found_key, slot);
		अगर (found_key.objectid != key.objectid ||
		    found_key.type != key.type) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		ret = iterate_dir_item(root, path, __process_new_xattr, sctx);
		अगर (ret < 0)
			जाओ out;

		path->slots[0]++;
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल अंतरभूत u64 max_send_पढ़ो_size(स्थिर काष्ठा send_ctx *sctx)
अणु
	वापस sctx->send_max_size - SZ_16K;
पूर्ण

अटल पूर्णांक put_data_header(काष्ठा send_ctx *sctx, u32 len)
अणु
	काष्ठा btrfs_tlv_header *hdr;

	अगर (sctx->send_max_size - sctx->send_size < माप(*hdr) + len)
		वापस -EOVERFLOW;
	hdr = (काष्ठा btrfs_tlv_header *)(sctx->send_buf + sctx->send_size);
	put_unaligned_le16(BTRFS_SEND_A_DATA, &hdr->tlv_type);
	put_unaligned_le16(len, &hdr->tlv_len);
	sctx->send_size += माप(*hdr);
	वापस 0;
पूर्ण

अटल पूर्णांक put_file_data(काष्ठा send_ctx *sctx, u64 offset, u32 len)
अणु
	काष्ठा btrfs_root *root = sctx->send_root;
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा inode *inode;
	काष्ठा page *page;
	pgoff_t index = offset >> PAGE_SHIFT;
	pgoff_t last_index;
	अचिन्हित pg_offset = offset_in_page(offset);
	पूर्णांक ret;

	ret = put_data_header(sctx, len);
	अगर (ret)
		वापस ret;

	inode = btrfs_iget(fs_info->sb, sctx->cur_ino, root);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	last_index = (offset + len - 1) >> PAGE_SHIFT;

	/* initial पढ़ोahead */
	स_रखो(&sctx->ra, 0, माप(काष्ठा file_ra_state));
	file_ra_state_init(&sctx->ra, inode->i_mapping);

	जबतक (index <= last_index) अणु
		अचिन्हित cur_len = min_t(अचिन्हित, len,
					 PAGE_SIZE - pg_offset);

		page = find_lock_page(inode->i_mapping, index);
		अगर (!page) अणु
			page_cache_sync_पढ़ोahead(inode->i_mapping, &sctx->ra,
				शून्य, index, last_index + 1 - index);

			page = find_or_create_page(inode->i_mapping, index,
					GFP_KERNEL);
			अगर (!page) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (PageReadahead(page)) अणु
			page_cache_async_पढ़ोahead(inode->i_mapping, &sctx->ra,
				शून्य, page, index, last_index + 1 - index);
		पूर्ण

		अगर (!PageUptodate(page)) अणु
			btrfs_पढ़ोpage(शून्य, page);
			lock_page(page);
			अगर (!PageUptodate(page)) अणु
				unlock_page(page);
				put_page(page);
				ret = -EIO;
				अवरोध;
			पूर्ण
		पूर्ण

		स_नकल_from_page(sctx->send_buf + sctx->send_size, page,
				 pg_offset, cur_len);
		unlock_page(page);
		put_page(page);
		index++;
		pg_offset = 0;
		len -= cur_len;
		sctx->send_size += cur_len;
	पूर्ण
	iput(inode);
	वापस ret;
पूर्ण

/*
 * Read some bytes from the current inode/file and send a ग_लिखो command to
 * user space.
 */
अटल पूर्णांक send_ग_लिखो(काष्ठा send_ctx *sctx, u64 offset, u32 len)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	पूर्णांक ret = 0;
	काष्ठा fs_path *p;

	p = fs_path_alloc();
	अगर (!p)
		वापस -ENOMEM;

	btrfs_debug(fs_info, "send_write offset=%llu, len=%d", offset, len);

	ret = begin_cmd(sctx, BTRFS_SEND_C_WRITE);
	अगर (ret < 0)
		जाओ out;

	ret = get_cur_path(sctx, sctx->cur_ino, sctx->cur_inode_gen, p);
	अगर (ret < 0)
		जाओ out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_खाता_OFFSET, offset);
	ret = put_file_data(sctx, offset, len);
	अगर (ret < 0)
		जाओ out;

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	fs_path_मुक्त(p);
	वापस ret;
पूर्ण

/*
 * Send a clone command to user space.
 */
अटल पूर्णांक send_clone(काष्ठा send_ctx *sctx,
		      u64 offset, u32 len,
		      काष्ठा clone_root *clone_root)
अणु
	पूर्णांक ret = 0;
	काष्ठा fs_path *p;
	u64 gen;

	btrfs_debug(sctx->send_root->fs_info,
		    "send_clone offset=%llu, len=%d, clone_root=%llu, clone_inode=%llu, clone_offset=%llu",
		    offset, len, clone_root->root->root_key.objectid,
		    clone_root->ino, clone_root->offset);

	p = fs_path_alloc();
	अगर (!p)
		वापस -ENOMEM;

	ret = begin_cmd(sctx, BTRFS_SEND_C_CLONE);
	अगर (ret < 0)
		जाओ out;

	ret = get_cur_path(sctx, sctx->cur_ino, sctx->cur_inode_gen, p);
	अगर (ret < 0)
		जाओ out;

	TLV_PUT_U64(sctx, BTRFS_SEND_A_खाता_OFFSET, offset);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_CLONE_LEN, len);
	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);

	अगर (clone_root->root == sctx->send_root) अणु
		ret = get_inode_info(sctx->send_root, clone_root->ino, शून्य,
				&gen, शून्य, शून्य, शून्य, शून्य);
		अगर (ret < 0)
			जाओ out;
		ret = get_cur_path(sctx, clone_root->ino, gen, p);
	पूर्ण अन्यथा अणु
		ret = get_inode_path(clone_root->root, clone_root->ino, p);
	पूर्ण
	अगर (ret < 0)
		जाओ out;

	/*
	 * If the parent we're using has a received_uuid set then use that as
	 * our clone source as that is what we will look क्रम when करोing a
	 * receive.
	 *
	 * This covers the हाल that we create a snapshot off of a received
	 * subvolume and then use that as the parent and try to receive on a
	 * dअगरferent host.
	 */
	अगर (!btrfs_is_empty_uuid(clone_root->root->root_item.received_uuid))
		TLV_PUT_UUID(sctx, BTRFS_SEND_A_CLONE_UUID,
			     clone_root->root->root_item.received_uuid);
	अन्यथा
		TLV_PUT_UUID(sctx, BTRFS_SEND_A_CLONE_UUID,
			     clone_root->root->root_item.uuid);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_CLONE_CTRANSID,
		    btrfs_root_ctransid(&clone_root->root->root_item));
	TLV_PUT_PATH(sctx, BTRFS_SEND_A_CLONE_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_CLONE_OFFSET,
			clone_root->offset);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	fs_path_मुक्त(p);
	वापस ret;
पूर्ण

/*
 * Send an update extent command to user space.
 */
अटल पूर्णांक send_update_extent(काष्ठा send_ctx *sctx,
			      u64 offset, u32 len)
अणु
	पूर्णांक ret = 0;
	काष्ठा fs_path *p;

	p = fs_path_alloc();
	अगर (!p)
		वापस -ENOMEM;

	ret = begin_cmd(sctx, BTRFS_SEND_C_UPDATE_EXTENT);
	अगर (ret < 0)
		जाओ out;

	ret = get_cur_path(sctx, sctx->cur_ino, sctx->cur_inode_gen, p);
	अगर (ret < 0)
		जाओ out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_खाता_OFFSET, offset);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_SIZE, len);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	fs_path_मुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक send_hole(काष्ठा send_ctx *sctx, u64 end)
अणु
	काष्ठा fs_path *p = शून्य;
	u64 पढ़ो_size = max_send_पढ़ो_size(sctx);
	u64 offset = sctx->cur_inode_last_extent;
	पूर्णांक ret = 0;

	/*
	 * A hole that starts at खातापूर्ण or beyond it. Since we करो not yet support
	 * fallocate (क्रम extent pपुनः_स्मृतिation and hole punching), sending a
	 * ग_लिखो of zeroes starting at खातापूर्ण or beyond would later require issuing
	 * a truncate operation which would unकरो the ग_लिखो and achieve nothing.
	 */
	अगर (offset >= sctx->cur_inode_size)
		वापस 0;

	/*
	 * Don't go beyond the inode's i_size due to pपुनः_स्मृति extents that start
	 * after the i_size.
	 */
	end = min_t(u64, end, sctx->cur_inode_size);

	अगर (sctx->flags & BTRFS_SEND_FLAG_NO_खाता_DATA)
		वापस send_update_extent(sctx, offset, end - offset);

	p = fs_path_alloc();
	अगर (!p)
		वापस -ENOMEM;
	ret = get_cur_path(sctx, sctx->cur_ino, sctx->cur_inode_gen, p);
	अगर (ret < 0)
		जाओ tlv_put_failure;
	जबतक (offset < end) अणु
		u64 len = min(end - offset, पढ़ो_size);

		ret = begin_cmd(sctx, BTRFS_SEND_C_WRITE);
		अगर (ret < 0)
			अवरोध;
		TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
		TLV_PUT_U64(sctx, BTRFS_SEND_A_खाता_OFFSET, offset);
		ret = put_data_header(sctx, len);
		अगर (ret < 0)
			अवरोध;
		स_रखो(sctx->send_buf + sctx->send_size, 0, len);
		sctx->send_size += len;
		ret = send_cmd(sctx);
		अगर (ret < 0)
			अवरोध;
		offset += len;
	पूर्ण
	sctx->cur_inode_next_ग_लिखो_offset = offset;
tlv_put_failure:
	fs_path_मुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक send_extent_data(काष्ठा send_ctx *sctx,
			    स्थिर u64 offset,
			    स्थिर u64 len)
अणु
	u64 पढ़ो_size = max_send_पढ़ो_size(sctx);
	u64 sent = 0;

	अगर (sctx->flags & BTRFS_SEND_FLAG_NO_खाता_DATA)
		वापस send_update_extent(sctx, offset, len);

	जबतक (sent < len) अणु
		u64 size = min(len - sent, पढ़ो_size);
		पूर्णांक ret;

		ret = send_ग_लिखो(sctx, offset + sent, size);
		अगर (ret < 0)
			वापस ret;
		sent += size;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Search क्रम a capability xattr related to sctx->cur_ino. If the capability is
 * found, call send_set_xattr function to emit it.
 *
 * Return 0 अगर there isn't a capability, or when the capability was emitted
 * successfully, or < 0 अगर an error occurred.
 */
अटल पूर्णांक send_capabilities(काष्ठा send_ctx *sctx)
अणु
	काष्ठा fs_path *fspath = शून्य;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_dir_item *di;
	काष्ठा extent_buffer *leaf;
	अचिन्हित दीर्घ data_ptr;
	अक्षर *buf = शून्य;
	पूर्णांक buf_len;
	पूर्णांक ret = 0;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	di = btrfs_lookup_xattr(शून्य, sctx->send_root, path, sctx->cur_ino,
				XATTR_NAME_CAPS, म_माप(XATTR_NAME_CAPS), 0);
	अगर (!di) अणु
		/* There is no xattr क्रम this inode */
		जाओ out;
	पूर्ण अन्यथा अगर (IS_ERR(di)) अणु
		ret = PTR_ERR(di);
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	buf_len = btrfs_dir_data_len(leaf, di);

	fspath = fs_path_alloc();
	buf = kदो_स्मृति(buf_len, GFP_KERNEL);
	अगर (!fspath || !buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = get_cur_path(sctx, sctx->cur_ino, sctx->cur_inode_gen, fspath);
	अगर (ret < 0)
		जाओ out;

	data_ptr = (अचिन्हित दीर्घ)(di + 1) + btrfs_dir_name_len(leaf, di);
	पढ़ो_extent_buffer(leaf, buf, data_ptr, buf_len);

	ret = send_set_xattr(sctx, fspath, XATTR_NAME_CAPS,
			म_माप(XATTR_NAME_CAPS), buf, buf_len);
out:
	kमुक्त(buf);
	fs_path_मुक्त(fspath);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक clone_range(काष्ठा send_ctx *sctx,
		       काष्ठा clone_root *clone_root,
		       स्थिर u64 disk_byte,
		       u64 data_offset,
		       u64 offset,
		       u64 len)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	पूर्णांक ret;
	u64 clone_src_i_size = 0;

	/*
	 * Prevent cloning from a zero offset with a length matching the sector
	 * size because in some scenarios this will make the receiver fail.
	 *
	 * For example, अगर in the source fileप्रणाली the extent at offset 0
	 * has a length of sectorsize and it was written using direct IO, then
	 * it can never be an अंतरभूत extent (even अगर compression is enabled).
	 * Then this extent can be cloned in the original fileप्रणाली to a non
	 * zero file offset, but it may not be possible to clone in the
	 * destination fileप्रणाली because it can be अंतरभूतd due to compression
	 * on the destination fileप्रणाली (as the receiver's ग_लिखो operations are
	 * always करोne using buffered IO). The same happens when the original
	 * fileप्रणाली करोes not have compression enabled but the destination
	 * fileप्रणाली has.
	 */
	अगर (clone_root->offset == 0 &&
	    len == sctx->send_root->fs_info->sectorsize)
		वापस send_extent_data(sctx, offset, len);

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	/*
	 * There are inodes that have extents that lie behind its i_size. Don't
	 * accept clones from these extents.
	 */
	ret = __get_inode_info(clone_root->root, path, clone_root->ino,
			       &clone_src_i_size, शून्य, शून्य, शून्य, शून्य, शून्य);
	btrfs_release_path(path);
	अगर (ret < 0)
		जाओ out;

	/*
	 * We can't send a clone operation क्रम the entire range अगर we find
	 * extent items in the respective range in the source file that
	 * refer to dअगरferent extents or अगर we find holes.
	 * So check क्रम that and करो a mix of clone and regular ग_लिखो/copy
	 * operations अगर needed.
	 *
	 * Example:
	 *
	 * mkfs.btrfs -f /dev/sda
	 * mount /dev/sda /mnt
	 * xfs_io -f -c "pwrite -S 0xaa 0K 100K" /mnt/foo
	 * cp --reflink=always /mnt/foo /mnt/bar
	 * xfs_io -c "pwrite -S 0xbb 50K 50K" /mnt/foo
	 * btrfs subvolume snapshot -r /mnt /mnt/snap
	 *
	 * If when we send the snapshot and we are processing file bar (which
	 * has a higher inode number than foo) we blindly send a clone operation
	 * क्रम the [0, 100K[ range from foo to bar, the receiver ends up getting
	 * a file bar that matches the content of file foo - iow, करोesn't match
	 * the content from bar in the original fileप्रणाली.
	 */
	key.objectid = clone_root->ino;
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = clone_root->offset;
	ret = btrfs_search_slot(शून्य, clone_root->root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret > 0 && path->slots[0] > 0) अणु
		btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0] - 1);
		अगर (key.objectid == clone_root->ino &&
		    key.type == BTRFS_EXTENT_DATA_KEY)
			path->slots[0]--;
	पूर्ण

	जबतक (true) अणु
		काष्ठा extent_buffer *leaf = path->nodes[0];
		पूर्णांक slot = path->slots[0];
		काष्ठा btrfs_file_extent_item *ei;
		u8 type;
		u64 ext_len;
		u64 clone_len;
		u64 clone_data_offset;

		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(clone_root->root, path);
			अगर (ret < 0)
				जाओ out;
			अन्यथा अगर (ret > 0)
				अवरोध;
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, slot);

		/*
		 * We might have an implicit trailing hole (NO_HOLES feature
		 * enabled). We deal with it after leaving this loop.
		 */
		अगर (key.objectid != clone_root->ino ||
		    key.type != BTRFS_EXTENT_DATA_KEY)
			अवरोध;

		ei = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_file_extent_item);
		type = btrfs_file_extent_type(leaf, ei);
		अगर (type == BTRFS_खाता_EXTENT_INLINE) अणु
			ext_len = btrfs_file_extent_ram_bytes(leaf, ei);
			ext_len = PAGE_ALIGN(ext_len);
		पूर्ण अन्यथा अणु
			ext_len = btrfs_file_extent_num_bytes(leaf, ei);
		पूर्ण

		अगर (key.offset + ext_len <= clone_root->offset)
			जाओ next;

		अगर (key.offset > clone_root->offset) अणु
			/* Implicit hole, NO_HOLES feature enabled. */
			u64 hole_len = key.offset - clone_root->offset;

			अगर (hole_len > len)
				hole_len = len;
			ret = send_extent_data(sctx, offset, hole_len);
			अगर (ret < 0)
				जाओ out;

			len -= hole_len;
			अगर (len == 0)
				अवरोध;
			offset += hole_len;
			clone_root->offset += hole_len;
			data_offset += hole_len;
		पूर्ण

		अगर (key.offset >= clone_root->offset + len)
			अवरोध;

		अगर (key.offset >= clone_src_i_size)
			अवरोध;

		अगर (key.offset + ext_len > clone_src_i_size)
			ext_len = clone_src_i_size - key.offset;

		clone_data_offset = btrfs_file_extent_offset(leaf, ei);
		अगर (btrfs_file_extent_disk_bytenr(leaf, ei) == disk_byte) अणु
			clone_root->offset = key.offset;
			अगर (clone_data_offset < data_offset &&
				clone_data_offset + ext_len > data_offset) अणु
				u64 extent_offset;

				extent_offset = data_offset - clone_data_offset;
				ext_len -= extent_offset;
				clone_data_offset += extent_offset;
				clone_root->offset += extent_offset;
			पूर्ण
		पूर्ण

		clone_len = min_t(u64, ext_len, len);

		अगर (btrfs_file_extent_disk_bytenr(leaf, ei) == disk_byte &&
		    clone_data_offset == data_offset) अणु
			स्थिर u64 src_end = clone_root->offset + clone_len;
			स्थिर u64 sectorsize = SZ_64K;

			/*
			 * We can't clone the last block, when its size is not
			 * sector size aligned, पूर्णांकo the middle of a file. If we
			 * करो so, the receiver will get a failure (-EINVAL) when
			 * trying to clone or will silently corrupt the data in
			 * the destination file अगर it's on a kernel without the
			 * fix पूर्णांकroduced by commit ac765f83f1397646
			 * ("Btrfs: fix data corruption due to cloning of eof
			 * block).
			 *
			 * So issue a clone of the aligned करोwn range plus a
			 * regular ग_लिखो क्रम the eof block, अगर we hit that हाल.
			 *
			 * Also, we use the maximum possible sector size, 64K,
			 * because we करोn't know what's the sector size of the
			 * fileप्रणाली that receives the stream, so we have to
			 * assume the largest possible sector size.
			 */
			अगर (src_end == clone_src_i_size &&
			    !IS_ALIGNED(src_end, sectorsize) &&
			    offset + clone_len < sctx->cur_inode_size) अणु
				u64 slen;

				slen = ALIGN_DOWN(src_end - clone_root->offset,
						  sectorsize);
				अगर (slen > 0) अणु
					ret = send_clone(sctx, offset, slen,
							 clone_root);
					अगर (ret < 0)
						जाओ out;
				पूर्ण
				ret = send_extent_data(sctx, offset + slen,
						       clone_len - slen);
			पूर्ण अन्यथा अणु
				ret = send_clone(sctx, offset, clone_len,
						 clone_root);
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = send_extent_data(sctx, offset, clone_len);
		पूर्ण

		अगर (ret < 0)
			जाओ out;

		len -= clone_len;
		अगर (len == 0)
			अवरोध;
		offset += clone_len;
		clone_root->offset += clone_len;

		/*
		 * If we are cloning from the file we are currently processing,
		 * and using the send root as the clone root, we must stop once
		 * the current clone offset reaches the current eof of the file
		 * at the receiver, otherwise we would issue an invalid clone
		 * operation (source range going beyond eof) and cause the
		 * receiver to fail. So अगर we reach the current eof, bail out
		 * and fallback to a regular ग_लिखो.
		 */
		अगर (clone_root->root == sctx->send_root &&
		    clone_root->ino == sctx->cur_ino &&
		    clone_root->offset >= sctx->cur_inode_next_ग_लिखो_offset)
			अवरोध;

		data_offset += clone_len;
next:
		path->slots[0]++;
	पूर्ण

	अगर (len > 0)
		ret = send_extent_data(sctx, offset, len);
	अन्यथा
		ret = 0;
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक send_ग_लिखो_or_clone(काष्ठा send_ctx *sctx,
			       काष्ठा btrfs_path *path,
			       काष्ठा btrfs_key *key,
			       काष्ठा clone_root *clone_root)
अणु
	पूर्णांक ret = 0;
	u64 offset = key->offset;
	u64 end;
	u64 bs = sctx->send_root->fs_info->sb->s_blocksize;

	end = min_t(u64, btrfs_file_extent_end(path), sctx->cur_inode_size);
	अगर (offset >= end)
		वापस 0;

	अगर (clone_root && IS_ALIGNED(end, bs)) अणु
		काष्ठा btrfs_file_extent_item *ei;
		u64 disk_byte;
		u64 data_offset;

		ei = btrfs_item_ptr(path->nodes[0], path->slots[0],
				    काष्ठा btrfs_file_extent_item);
		disk_byte = btrfs_file_extent_disk_bytenr(path->nodes[0], ei);
		data_offset = btrfs_file_extent_offset(path->nodes[0], ei);
		ret = clone_range(sctx, clone_root, disk_byte, data_offset,
				  offset, end - offset);
	पूर्ण अन्यथा अणु
		ret = send_extent_data(sctx, offset, end - offset);
	पूर्ण
	sctx->cur_inode_next_ग_लिखो_offset = end;
	वापस ret;
पूर्ण

अटल पूर्णांक is_extent_unchanged(काष्ठा send_ctx *sctx,
			       काष्ठा btrfs_path *left_path,
			       काष्ठा btrfs_key *ekey)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा extent_buffer *eb;
	पूर्णांक slot;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_file_extent_item *ei;
	u64 left_disknr;
	u64 right_disknr;
	u64 left_offset;
	u64 right_offset;
	u64 left_offset_fixed;
	u64 left_len;
	u64 right_len;
	u64 left_gen;
	u64 right_gen;
	u8 left_type;
	u8 right_type;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	eb = left_path->nodes[0];
	slot = left_path->slots[0];
	ei = btrfs_item_ptr(eb, slot, काष्ठा btrfs_file_extent_item);
	left_type = btrfs_file_extent_type(eb, ei);

	अगर (left_type != BTRFS_खाता_EXTENT_REG) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	left_disknr = btrfs_file_extent_disk_bytenr(eb, ei);
	left_len = btrfs_file_extent_num_bytes(eb, ei);
	left_offset = btrfs_file_extent_offset(eb, ei);
	left_gen = btrfs_file_extent_generation(eb, ei);

	/*
	 * Following comments will refer to these graphics. L is the left
	 * extents which we are checking at the moment. 1-8 are the right
	 * extents that we iterate.
	 *
	 *       |-----L-----|
	 * |-1-|-2a-|-3-|-4-|-5-|-6-|
	 *
	 *       |-----L-----|
	 * |--1--|-2b-|...(same as above)
	 *
	 * Alternative situation. Happens on files where extents got split.
	 *       |-----L-----|
	 * |-----------7-----------|-6-|
	 *
	 * Alternative situation. Happens on files which got larger.
	 *       |-----L-----|
	 * |-8-|
	 * Nothing follows after 8.
	 */

	key.objectid = ekey->objectid;
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = ekey->offset;
	ret = btrfs_search_slot_क्रम_पढ़ो(sctx->parent_root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/*
	 * Handle special हाल where the right side has no extents at all.
	 */
	eb = path->nodes[0];
	slot = path->slots[0];
	btrfs_item_key_to_cpu(eb, &found_key, slot);
	अगर (found_key.objectid != key.objectid ||
	    found_key.type != key.type) अणु
		/* If we're a hole then just pretend nothing changed */
		ret = (left_disknr) ? 0 : 1;
		जाओ out;
	पूर्ण

	/*
	 * We're now on 2a, 2b or 7.
	 */
	key = found_key;
	जबतक (key.offset < ekey->offset + left_len) अणु
		ei = btrfs_item_ptr(eb, slot, काष्ठा btrfs_file_extent_item);
		right_type = btrfs_file_extent_type(eb, ei);
		अगर (right_type != BTRFS_खाता_EXTENT_REG &&
		    right_type != BTRFS_खाता_EXTENT_INLINE) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		अगर (right_type == BTRFS_खाता_EXTENT_INLINE) अणु
			right_len = btrfs_file_extent_ram_bytes(eb, ei);
			right_len = PAGE_ALIGN(right_len);
		पूर्ण अन्यथा अणु
			right_len = btrfs_file_extent_num_bytes(eb, ei);
		पूर्ण

		/*
		 * Are we at extent 8? If yes, we know the extent is changed.
		 * This may only happen on the first iteration.
		 */
		अगर (found_key.offset + right_len <= ekey->offset) अणु
			/* If we're a hole just pretend nothing changed */
			ret = (left_disknr) ? 0 : 1;
			जाओ out;
		पूर्ण

		/*
		 * We just wanted to see अगर when we have an अंतरभूत extent, what
		 * follows it is a regular extent (wanted to check the above
		 * condition क्रम अंतरभूत extents too). This should normally not
		 * happen but it's possible क्रम example when we have an अंतरभूत
		 * compressed extent representing data with a size matching
		 * the page size (currently the same as sector size).
		 */
		अगर (right_type == BTRFS_खाता_EXTENT_INLINE) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		right_disknr = btrfs_file_extent_disk_bytenr(eb, ei);
		right_offset = btrfs_file_extent_offset(eb, ei);
		right_gen = btrfs_file_extent_generation(eb, ei);

		left_offset_fixed = left_offset;
		अगर (key.offset < ekey->offset) अणु
			/* Fix the right offset क्रम 2a and 7. */
			right_offset += ekey->offset - key.offset;
		पूर्ण अन्यथा अणु
			/* Fix the left offset क्रम all behind 2a and 2b */
			left_offset_fixed += key.offset - ekey->offset;
		पूर्ण

		/*
		 * Check अगर we have the same extent.
		 */
		अगर (left_disknr != right_disknr ||
		    left_offset_fixed != right_offset ||
		    left_gen != right_gen) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		/*
		 * Go to the next extent.
		 */
		ret = btrfs_next_item(sctx->parent_root, path);
		अगर (ret < 0)
			जाओ out;
		अगर (!ret) अणु
			eb = path->nodes[0];
			slot = path->slots[0];
			btrfs_item_key_to_cpu(eb, &found_key, slot);
		पूर्ण
		अगर (ret || found_key.objectid != key.objectid ||
		    found_key.type != key.type) अणु
			key.offset += right_len;
			अवरोध;
		पूर्ण
		अगर (found_key.offset != key.offset + right_len) अणु
			ret = 0;
			जाओ out;
		पूर्ण
		key = found_key;
	पूर्ण

	/*
	 * We're now behind the left extent (treat as unchanged) or at the end
	 * of the right side (treat as changed).
	 */
	अगर (key.offset >= ekey->offset + left_len)
		ret = 1;
	अन्यथा
		ret = 0;


out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक get_last_extent(काष्ठा send_ctx *sctx, u64 offset)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_root *root = sctx->send_root;
	काष्ठा btrfs_key key;
	पूर्णांक ret;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	sctx->cur_inode_last_extent = 0;

	key.objectid = sctx->cur_ino;
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = offset;
	ret = btrfs_search_slot_क्रम_पढ़ो(root, &key, path, 0, 1);
	अगर (ret < 0)
		जाओ out;
	ret = 0;
	btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
	अगर (key.objectid != sctx->cur_ino || key.type != BTRFS_EXTENT_DATA_KEY)
		जाओ out;

	sctx->cur_inode_last_extent = btrfs_file_extent_end(path);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक range_is_hole_in_parent(काष्ठा send_ctx *sctx,
				   स्थिर u64 start,
				   स्थिर u64 end)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_root *root = sctx->parent_root;
	u64 search_start = start;
	पूर्णांक ret;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = sctx->cur_ino;
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = search_start;
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret > 0 && path->slots[0] > 0)
		path->slots[0]--;

	जबतक (search_start < end) अणु
		काष्ठा extent_buffer *leaf = path->nodes[0];
		पूर्णांक slot = path->slots[0];
		काष्ठा btrfs_file_extent_item *fi;
		u64 extent_end;

		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ out;
			अन्यथा अगर (ret > 0)
				अवरोध;
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, slot);
		अगर (key.objectid < sctx->cur_ino ||
		    key.type < BTRFS_EXTENT_DATA_KEY)
			जाओ next;
		अगर (key.objectid > sctx->cur_ino ||
		    key.type > BTRFS_EXTENT_DATA_KEY ||
		    key.offset >= end)
			अवरोध;

		fi = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_file_extent_item);
		extent_end = btrfs_file_extent_end(path);
		अगर (extent_end <= start)
			जाओ next;
		अगर (btrfs_file_extent_disk_bytenr(leaf, fi) == 0) अणु
			search_start = extent_end;
			जाओ next;
		पूर्ण
		ret = 0;
		जाओ out;
next:
		path->slots[0]++;
	पूर्ण
	ret = 1;
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक maybe_send_hole(काष्ठा send_ctx *sctx, काष्ठा btrfs_path *path,
			   काष्ठा btrfs_key *key)
अणु
	पूर्णांक ret = 0;

	अगर (sctx->cur_ino != key->objectid || !need_send_hole(sctx))
		वापस 0;

	अगर (sctx->cur_inode_last_extent == (u64)-1) अणु
		ret = get_last_extent(sctx, key->offset - 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (path->slots[0] == 0 &&
	    sctx->cur_inode_last_extent < key->offset) अणु
		/*
		 * We might have skipped entire leafs that contained only
		 * file extent items क्रम our current inode. These leafs have
		 * a generation number smaller (older) than the one in the
		 * current leaf and the leaf our last extent came from, and
		 * are located between these 2 leafs.
		 */
		ret = get_last_extent(sctx, key->offset - 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (sctx->cur_inode_last_extent < key->offset) अणु
		ret = range_is_hole_in_parent(sctx,
					      sctx->cur_inode_last_extent,
					      key->offset);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret == 0)
			ret = send_hole(sctx, key->offset);
		अन्यथा
			ret = 0;
	पूर्ण
	sctx->cur_inode_last_extent = btrfs_file_extent_end(path);
	वापस ret;
पूर्ण

अटल पूर्णांक process_extent(काष्ठा send_ctx *sctx,
			  काष्ठा btrfs_path *path,
			  काष्ठा btrfs_key *key)
अणु
	काष्ठा clone_root *found_clone = शून्य;
	पूर्णांक ret = 0;

	अगर (S_ISLNK(sctx->cur_inode_mode))
		वापस 0;

	अगर (sctx->parent_root && !sctx->cur_inode_new) अणु
		ret = is_extent_unchanged(sctx, path, key);
		अगर (ret < 0)
			जाओ out;
		अगर (ret) अणु
			ret = 0;
			जाओ out_hole;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा btrfs_file_extent_item *ei;
		u8 type;

		ei = btrfs_item_ptr(path->nodes[0], path->slots[0],
				    काष्ठा btrfs_file_extent_item);
		type = btrfs_file_extent_type(path->nodes[0], ei);
		अगर (type == BTRFS_खाता_EXTENT_PREALLOC ||
		    type == BTRFS_खाता_EXTENT_REG) अणु
			/*
			 * The send spec करोes not have a pपुनः_स्मृति command yet,
			 * so just leave a hole क्रम pपुनः_स्मृति'ed extents until
			 * we have enough commands queued up to justअगरy rev'ing
			 * the send spec.
			 */
			अगर (type == BTRFS_खाता_EXTENT_PREALLOC) अणु
				ret = 0;
				जाओ out;
			पूर्ण

			/* Have a hole, just skip it. */
			अगर (btrfs_file_extent_disk_bytenr(path->nodes[0], ei) == 0) अणु
				ret = 0;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = find_extent_clone(sctx, path, key->objectid, key->offset,
			sctx->cur_inode_size, &found_clone);
	अगर (ret != -ENOENT && ret < 0)
		जाओ out;

	ret = send_ग_लिखो_or_clone(sctx, path, key, found_clone);
	अगर (ret)
		जाओ out;
out_hole:
	ret = maybe_send_hole(sctx, path, key);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक process_all_extents(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा extent_buffer *eb;
	पूर्णांक slot;

	root = sctx->send_root;
	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = sctx->cmp_key->objectid;
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;

	जबतक (1) अणु
		eb = path->nodes[0];
		slot = path->slots[0];

		अगर (slot >= btrfs_header_nritems(eb)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0) अणु
				जाओ out;
			पूर्ण अन्यथा अगर (ret > 0) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(eb, &found_key, slot);

		अगर (found_key.objectid != key.objectid ||
		    found_key.type != key.type) अणु
			ret = 0;
			जाओ out;
		पूर्ण

		ret = process_extent(sctx, path, &found_key);
		अगर (ret < 0)
			जाओ out;

		path->slots[0]++;
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक process_recorded_refs_अगर_needed(काष्ठा send_ctx *sctx, पूर्णांक at_end,
					   पूर्णांक *pending_move,
					   पूर्णांक *refs_processed)
अणु
	पूर्णांक ret = 0;

	अगर (sctx->cur_ino == 0)
		जाओ out;
	अगर (!at_end && sctx->cur_ino == sctx->cmp_key->objectid &&
	    sctx->cmp_key->type <= BTRFS_INODE_EXTREF_KEY)
		जाओ out;
	अगर (list_empty(&sctx->new_refs) && list_empty(&sctx->deleted_refs))
		जाओ out;

	ret = process_recorded_refs(sctx, pending_move);
	अगर (ret < 0)
		जाओ out;

	*refs_processed = 1;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक finish_inode_अगर_needed(काष्ठा send_ctx *sctx, पूर्णांक at_end)
अणु
	पूर्णांक ret = 0;
	u64 left_mode;
	u64 left_uid;
	u64 left_gid;
	u64 right_mode;
	u64 right_uid;
	u64 right_gid;
	पूर्णांक need_chmod = 0;
	पूर्णांक need_chown = 0;
	पूर्णांक need_truncate = 1;
	पूर्णांक pending_move = 0;
	पूर्णांक refs_processed = 0;

	अगर (sctx->ignore_cur_inode)
		वापस 0;

	ret = process_recorded_refs_अगर_needed(sctx, at_end, &pending_move,
					      &refs_processed);
	अगर (ret < 0)
		जाओ out;

	/*
	 * We have processed the refs and thus need to advance send_progress.
	 * Now, calls to get_cur_xxx will take the updated refs of the current
	 * inode पूर्णांकo account.
	 *
	 * On the other hand, अगर our current inode is a directory and couldn't
	 * be moved/नामd because its parent was नामd/moved too and it has
	 * a higher inode number, we can only move/नाम our current inode
	 * after we moved/नामd its parent. Thereक्रमe in this हाल operate on
	 * the old path (pre move/नाम) of our current inode, and the
	 * move/नाम will be perक्रमmed later.
	 */
	अगर (refs_processed && !pending_move)
		sctx->send_progress = sctx->cur_ino + 1;

	अगर (sctx->cur_ino == 0 || sctx->cur_inode_deleted)
		जाओ out;
	अगर (!at_end && sctx->cmp_key->objectid == sctx->cur_ino)
		जाओ out;

	ret = get_inode_info(sctx->send_root, sctx->cur_ino, शून्य, शून्य,
			&left_mode, &left_uid, &left_gid, शून्य);
	अगर (ret < 0)
		जाओ out;

	अगर (!sctx->parent_root || sctx->cur_inode_new) अणु
		need_chown = 1;
		अगर (!S_ISLNK(sctx->cur_inode_mode))
			need_chmod = 1;
		अगर (sctx->cur_inode_next_ग_लिखो_offset == sctx->cur_inode_size)
			need_truncate = 0;
	पूर्ण अन्यथा अणु
		u64 old_size;

		ret = get_inode_info(sctx->parent_root, sctx->cur_ino,
				&old_size, शून्य, &right_mode, &right_uid,
				&right_gid, शून्य);
		अगर (ret < 0)
			जाओ out;

		अगर (left_uid != right_uid || left_gid != right_gid)
			need_chown = 1;
		अगर (!S_ISLNK(sctx->cur_inode_mode) && left_mode != right_mode)
			need_chmod = 1;
		अगर ((old_size == sctx->cur_inode_size) ||
		    (sctx->cur_inode_size > old_size &&
		     sctx->cur_inode_next_ग_लिखो_offset == sctx->cur_inode_size))
			need_truncate = 0;
	पूर्ण

	अगर (S_ISREG(sctx->cur_inode_mode)) अणु
		अगर (need_send_hole(sctx)) अणु
			अगर (sctx->cur_inode_last_extent == (u64)-1 ||
			    sctx->cur_inode_last_extent <
			    sctx->cur_inode_size) अणु
				ret = get_last_extent(sctx, (u64)-1);
				अगर (ret)
					जाओ out;
			पूर्ण
			अगर (sctx->cur_inode_last_extent <
			    sctx->cur_inode_size) अणु
				ret = send_hole(sctx, sctx->cur_inode_size);
				अगर (ret)
					जाओ out;
			पूर्ण
		पूर्ण
		अगर (need_truncate) अणु
			ret = send_truncate(sctx, sctx->cur_ino,
					    sctx->cur_inode_gen,
					    sctx->cur_inode_size);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण

	अगर (need_chown) अणु
		ret = send_chown(sctx, sctx->cur_ino, sctx->cur_inode_gen,
				left_uid, left_gid);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
	अगर (need_chmod) अणु
		ret = send_chmod(sctx, sctx->cur_ino, sctx->cur_inode_gen,
				left_mode);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = send_capabilities(sctx);
	अगर (ret < 0)
		जाओ out;

	/*
	 * If other directory inodes depended on our current directory
	 * inode's move/नाम, now करो their move/नाम operations.
	 */
	अगर (!is_रुकोing_क्रम_move(sctx, sctx->cur_ino)) अणु
		ret = apply_children_dir_moves(sctx);
		अगर (ret)
			जाओ out;
		/*
		 * Need to send that every समय, no matter अगर it actually
		 * changed between the two trees as we have करोne changes to
		 * the inode beक्रमe. If our inode is a directory and it's
		 * रुकोing to be moved/नामd, we will send its uबार when
		 * it's moved/renamed, therefore we don't need to करो it here.
		 */
		sctx->send_progress = sctx->cur_ino + 1;
		ret = send_uबार(sctx, sctx->cur_ino, sctx->cur_inode_gen);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

काष्ठा parent_paths_ctx अणु
	काष्ठा list_head *refs;
	काष्ठा send_ctx *sctx;
पूर्ण;

अटल पूर्णांक record_parent_ref(पूर्णांक num, u64 dir, पूर्णांक index, काष्ठा fs_path *name,
			     व्योम *ctx)
अणु
	काष्ठा parent_paths_ctx *ppctx = ctx;

	वापस record_ref(ppctx->sctx->parent_root, dir, name, ppctx->sctx,
			  ppctx->refs);
पूर्ण

/*
 * Issue unlink operations क्रम all paths of the current inode found in the
 * parent snapshot.
 */
अटल पूर्णांक btrfs_unlink_all_paths(काष्ठा send_ctx *sctx)
अणु
	LIST_HEAD(deleted_refs);
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा parent_paths_ctx ctx;
	पूर्णांक ret;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = sctx->cur_ino;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(शून्य, sctx->parent_root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;

	ctx.refs = &deleted_refs;
	ctx.sctx = sctx;

	जबतक (true) अणु
		काष्ठा extent_buffer *eb = path->nodes[0];
		पूर्णांक slot = path->slots[0];

		अगर (slot >= btrfs_header_nritems(eb)) अणु
			ret = btrfs_next_leaf(sctx->parent_root, path);
			अगर (ret < 0)
				जाओ out;
			अन्यथा अगर (ret > 0)
				अवरोध;
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(eb, &key, slot);
		अगर (key.objectid != sctx->cur_ino)
			अवरोध;
		अगर (key.type != BTRFS_INODE_REF_KEY &&
		    key.type != BTRFS_INODE_EXTREF_KEY)
			अवरोध;

		ret = iterate_inode_ref(sctx->parent_root, path, &key, 1,
					record_parent_ref, &ctx);
		अगर (ret < 0)
			जाओ out;

		path->slots[0]++;
	पूर्ण

	जबतक (!list_empty(&deleted_refs)) अणु
		काष्ठा recorded_ref *ref;

		ref = list_first_entry(&deleted_refs, काष्ठा recorded_ref, list);
		ret = send_unlink(sctx, ref->full_path);
		अगर (ret < 0)
			जाओ out;
		fs_path_मुक्त(ref->full_path);
		list_del(&ref->list);
		kमुक्त(ref);
	पूर्ण
	ret = 0;
out:
	btrfs_मुक्त_path(path);
	अगर (ret)
		__मुक्त_recorded_refs(&deleted_refs);
	वापस ret;
पूर्ण

अटल पूर्णांक changed_inode(काष्ठा send_ctx *sctx,
			 क्रमागत btrfs_compare_tree_result result)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_key *key = sctx->cmp_key;
	काष्ठा btrfs_inode_item *left_ii = शून्य;
	काष्ठा btrfs_inode_item *right_ii = शून्य;
	u64 left_gen = 0;
	u64 right_gen = 0;

	sctx->cur_ino = key->objectid;
	sctx->cur_inode_new_gen = 0;
	sctx->cur_inode_last_extent = (u64)-1;
	sctx->cur_inode_next_ग_लिखो_offset = 0;
	sctx->ignore_cur_inode = false;

	/*
	 * Set send_progress to current inode. This will tell all get_cur_xxx
	 * functions that the current inode's refs are not updated yet. Later,
	 * when process_recorded_refs is finished, it is set to cur_ino + 1.
	 */
	sctx->send_progress = sctx->cur_ino;

	अगर (result == BTRFS_COMPARE_TREE_NEW ||
	    result == BTRFS_COMPARE_TREE_CHANGED) अणु
		left_ii = btrfs_item_ptr(sctx->left_path->nodes[0],
				sctx->left_path->slots[0],
				काष्ठा btrfs_inode_item);
		left_gen = btrfs_inode_generation(sctx->left_path->nodes[0],
				left_ii);
	पूर्ण अन्यथा अणु
		right_ii = btrfs_item_ptr(sctx->right_path->nodes[0],
				sctx->right_path->slots[0],
				काष्ठा btrfs_inode_item);
		right_gen = btrfs_inode_generation(sctx->right_path->nodes[0],
				right_ii);
	पूर्ण
	अगर (result == BTRFS_COMPARE_TREE_CHANGED) अणु
		right_ii = btrfs_item_ptr(sctx->right_path->nodes[0],
				sctx->right_path->slots[0],
				काष्ठा btrfs_inode_item);

		right_gen = btrfs_inode_generation(sctx->right_path->nodes[0],
				right_ii);

		/*
		 * The cur_ino = root dir हाल is special here. We can't treat
		 * the inode as deleted+reused because it would generate a
		 * stream that tries to delete/सूची_गढ़ो the root dir.
		 */
		अगर (left_gen != right_gen &&
		    sctx->cur_ino != BTRFS_FIRST_FREE_OBJECTID)
			sctx->cur_inode_new_gen = 1;
	पूर्ण

	/*
	 * Normally we करो not find inodes with a link count of zero (orphans)
	 * because the most common हाल is to create a snapshot and use it
	 * क्रम a send operation. However other less common use हालs involve
	 * using a subvolume and send it after turning it to RO mode just
	 * after deleting all hard links of a file जबतक holding an खोलो
	 * file descriptor against it or turning a RO snapshot पूर्णांकo RW mode,
	 * keep an खोलो file descriptor against a file, delete it and then
	 * turn the snapshot back to RO mode beक्रमe using it क्रम a send
	 * operation. So अगर we find such हालs, ignore the inode and all its
	 * items completely अगर it's a new inode, or if it's a changed inode
	 * make sure all its previous paths (from the parent snapshot) are all
	 * unlinked and all other the inode items are ignored.
	 */
	अगर (result == BTRFS_COMPARE_TREE_NEW ||
	    result == BTRFS_COMPARE_TREE_CHANGED) अणु
		u32 nlinks;

		nlinks = btrfs_inode_nlink(sctx->left_path->nodes[0], left_ii);
		अगर (nlinks == 0) अणु
			sctx->ignore_cur_inode = true;
			अगर (result == BTRFS_COMPARE_TREE_CHANGED)
				ret = btrfs_unlink_all_paths(sctx);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (result == BTRFS_COMPARE_TREE_NEW) अणु
		sctx->cur_inode_gen = left_gen;
		sctx->cur_inode_new = 1;
		sctx->cur_inode_deleted = 0;
		sctx->cur_inode_size = btrfs_inode_size(
				sctx->left_path->nodes[0], left_ii);
		sctx->cur_inode_mode = btrfs_inode_mode(
				sctx->left_path->nodes[0], left_ii);
		sctx->cur_inode_rdev = btrfs_inode_rdev(
				sctx->left_path->nodes[0], left_ii);
		अगर (sctx->cur_ino != BTRFS_FIRST_FREE_OBJECTID)
			ret = send_create_inode_अगर_needed(sctx);
	पूर्ण अन्यथा अगर (result == BTRFS_COMPARE_TREE_DELETED) अणु
		sctx->cur_inode_gen = right_gen;
		sctx->cur_inode_new = 0;
		sctx->cur_inode_deleted = 1;
		sctx->cur_inode_size = btrfs_inode_size(
				sctx->right_path->nodes[0], right_ii);
		sctx->cur_inode_mode = btrfs_inode_mode(
				sctx->right_path->nodes[0], right_ii);
	पूर्ण अन्यथा अगर (result == BTRFS_COMPARE_TREE_CHANGED) अणु
		/*
		 * We need to करो some special handling in हाल the inode was
		 * reported as changed with a changed generation number. This
		 * means that the original inode was deleted and new inode
		 * reused the same inum. So we have to treat the old inode as
		 * deleted and the new one as new.
		 */
		अगर (sctx->cur_inode_new_gen) अणु
			/*
			 * First, process the inode as अगर it was deleted.
			 */
			sctx->cur_inode_gen = right_gen;
			sctx->cur_inode_new = 0;
			sctx->cur_inode_deleted = 1;
			sctx->cur_inode_size = btrfs_inode_size(
					sctx->right_path->nodes[0], right_ii);
			sctx->cur_inode_mode = btrfs_inode_mode(
					sctx->right_path->nodes[0], right_ii);
			ret = process_all_refs(sctx,
					BTRFS_COMPARE_TREE_DELETED);
			अगर (ret < 0)
				जाओ out;

			/*
			 * Now process the inode as अगर it was new.
			 */
			sctx->cur_inode_gen = left_gen;
			sctx->cur_inode_new = 1;
			sctx->cur_inode_deleted = 0;
			sctx->cur_inode_size = btrfs_inode_size(
					sctx->left_path->nodes[0], left_ii);
			sctx->cur_inode_mode = btrfs_inode_mode(
					sctx->left_path->nodes[0], left_ii);
			sctx->cur_inode_rdev = btrfs_inode_rdev(
					sctx->left_path->nodes[0], left_ii);
			ret = send_create_inode_अगर_needed(sctx);
			अगर (ret < 0)
				जाओ out;

			ret = process_all_refs(sctx, BTRFS_COMPARE_TREE_NEW);
			अगर (ret < 0)
				जाओ out;
			/*
			 * Advance send_progress now as we did not get पूर्णांकo
			 * process_recorded_refs_अगर_needed in the new_gen हाल.
			 */
			sctx->send_progress = sctx->cur_ino + 1;

			/*
			 * Now process all extents and xattrs of the inode as अगर
			 * they were all new.
			 */
			ret = process_all_extents(sctx);
			अगर (ret < 0)
				जाओ out;
			ret = process_all_new_xattrs(sctx);
			अगर (ret < 0)
				जाओ out;
		पूर्ण अन्यथा अणु
			sctx->cur_inode_gen = left_gen;
			sctx->cur_inode_new = 0;
			sctx->cur_inode_new_gen = 0;
			sctx->cur_inode_deleted = 0;
			sctx->cur_inode_size = btrfs_inode_size(
					sctx->left_path->nodes[0], left_ii);
			sctx->cur_inode_mode = btrfs_inode_mode(
					sctx->left_path->nodes[0], left_ii);
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * We have to process new refs beक्रमe deleted refs, but compare_trees gives us
 * the new and deleted refs mixed. To fix this, we record the new/deleted refs
 * first and later process them in process_recorded_refs.
 * For the cur_inode_new_gen हाल, we skip recording completely because
 * changed_inode did alपढ़ोy initiate processing of refs. The reason क्रम this is
 * that in this हाल, compare_tree actually compares the refs of 2 dअगरferent
 * inodes. To fix this, process_all_refs is used in changed_inode to handle all
 * refs of the right tree as deleted and all refs of the left tree as new.
 */
अटल पूर्णांक changed_ref(काष्ठा send_ctx *sctx,
		       क्रमागत btrfs_compare_tree_result result)
अणु
	पूर्णांक ret = 0;

	अगर (sctx->cur_ino != sctx->cmp_key->objectid) अणु
		inconsistent_snapshot_error(sctx, result, "reference");
		वापस -EIO;
	पूर्ण

	अगर (!sctx->cur_inode_new_gen &&
	    sctx->cur_ino != BTRFS_FIRST_FREE_OBJECTID) अणु
		अगर (result == BTRFS_COMPARE_TREE_NEW)
			ret = record_new_ref(sctx);
		अन्यथा अगर (result == BTRFS_COMPARE_TREE_DELETED)
			ret = record_deleted_ref(sctx);
		अन्यथा अगर (result == BTRFS_COMPARE_TREE_CHANGED)
			ret = record_changed_ref(sctx);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Process new/deleted/changed xattrs. We skip processing in the
 * cur_inode_new_gen हाल because changed_inode did alपढ़ोy initiate processing
 * of xattrs. The reason is the same as in changed_ref
 */
अटल पूर्णांक changed_xattr(काष्ठा send_ctx *sctx,
			 क्रमागत btrfs_compare_tree_result result)
अणु
	पूर्णांक ret = 0;

	अगर (sctx->cur_ino != sctx->cmp_key->objectid) अणु
		inconsistent_snapshot_error(sctx, result, "xattr");
		वापस -EIO;
	पूर्ण

	अगर (!sctx->cur_inode_new_gen && !sctx->cur_inode_deleted) अणु
		अगर (result == BTRFS_COMPARE_TREE_NEW)
			ret = process_new_xattr(sctx);
		अन्यथा अगर (result == BTRFS_COMPARE_TREE_DELETED)
			ret = process_deleted_xattr(sctx);
		अन्यथा अगर (result == BTRFS_COMPARE_TREE_CHANGED)
			ret = process_changed_xattr(sctx);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Process new/deleted/changed extents. We skip processing in the
 * cur_inode_new_gen हाल because changed_inode did alपढ़ोy initiate processing
 * of extents. The reason is the same as in changed_ref
 */
अटल पूर्णांक changed_extent(काष्ठा send_ctx *sctx,
			  क्रमागत btrfs_compare_tree_result result)
अणु
	पूर्णांक ret = 0;

	/*
	 * We have found an extent item that changed without the inode item
	 * having changed. This can happen either after relocation (where the
	 * disk_bytenr of an extent item is replaced at
	 * relocation.c:replace_file_extents()) or after deduplication पूर्णांकo a
	 * file in both the parent and send snapshots (where an extent item can
	 * get modअगरied or replaced with a new one). Note that deduplication
	 * updates the inode item, but it only changes the iversion (sequence
	 * field in the inode item) of the inode, so अगर a file is deduplicated
	 * the same amount of बार in both the parent and send snapshots, its
	 * iversion becames the same in both snapshots, whence the inode item is
	 * the same on both snapshots.
	 */
	अगर (sctx->cur_ino != sctx->cmp_key->objectid)
		वापस 0;

	अगर (!sctx->cur_inode_new_gen && !sctx->cur_inode_deleted) अणु
		अगर (result != BTRFS_COMPARE_TREE_DELETED)
			ret = process_extent(sctx, sctx->left_path,
					sctx->cmp_key);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dir_changed(काष्ठा send_ctx *sctx, u64 dir)
अणु
	u64 orig_gen, new_gen;
	पूर्णांक ret;

	ret = get_inode_info(sctx->send_root, dir, शून्य, &new_gen, शून्य, शून्य,
			     शून्य, शून्य);
	अगर (ret)
		वापस ret;

	ret = get_inode_info(sctx->parent_root, dir, शून्य, &orig_gen, शून्य,
			     शून्य, शून्य, शून्य);
	अगर (ret)
		वापस ret;

	वापस (orig_gen != new_gen) ? 1 : 0;
पूर्ण

अटल पूर्णांक compare_refs(काष्ठा send_ctx *sctx, काष्ठा btrfs_path *path,
			काष्ठा btrfs_key *key)
अणु
	काष्ठा btrfs_inode_extref *extref;
	काष्ठा extent_buffer *leaf;
	u64 dirid = 0, last_dirid = 0;
	अचिन्हित दीर्घ ptr;
	u32 item_size;
	u32 cur_offset = 0;
	पूर्णांक ref_name_len;
	पूर्णांक ret = 0;

	/* Easy हाल, just check this one dirid */
	अगर (key->type == BTRFS_INODE_REF_KEY) अणु
		dirid = key->offset;

		ret = dir_changed(sctx, dirid);
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	item_size = btrfs_item_size_nr(leaf, path->slots[0]);
	ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
	जबतक (cur_offset < item_size) अणु
		extref = (काष्ठा btrfs_inode_extref *)(ptr +
						       cur_offset);
		dirid = btrfs_inode_extref_parent(leaf, extref);
		ref_name_len = btrfs_inode_extref_name_len(leaf, extref);
		cur_offset += ref_name_len + माप(*extref);
		अगर (dirid == last_dirid)
			जारी;
		ret = dir_changed(sctx, dirid);
		अगर (ret)
			अवरोध;
		last_dirid = dirid;
	पूर्ण
out:
	वापस ret;
पूर्ण

/*
 * Updates compare related fields in sctx and simply क्रमwards to the actual
 * changed_xxx functions.
 */
अटल पूर्णांक changed_cb(काष्ठा btrfs_path *left_path,
		      काष्ठा btrfs_path *right_path,
		      काष्ठा btrfs_key *key,
		      क्रमागत btrfs_compare_tree_result result,
		      काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret = 0;

	अगर (result == BTRFS_COMPARE_TREE_SAME) अणु
		अगर (key->type == BTRFS_INODE_REF_KEY ||
		    key->type == BTRFS_INODE_EXTREF_KEY) अणु
			ret = compare_refs(sctx, left_path, key);
			अगर (!ret)
				वापस 0;
			अगर (ret < 0)
				वापस ret;
		पूर्ण अन्यथा अगर (key->type == BTRFS_EXTENT_DATA_KEY) अणु
			वापस maybe_send_hole(sctx, left_path, key);
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
		result = BTRFS_COMPARE_TREE_CHANGED;
		ret = 0;
	पूर्ण

	sctx->left_path = left_path;
	sctx->right_path = right_path;
	sctx->cmp_key = key;

	ret = finish_inode_अगर_needed(sctx, 0);
	अगर (ret < 0)
		जाओ out;

	/* Ignore non-FS objects */
	अगर (key->objectid == BTRFS_FREE_INO_OBJECTID ||
	    key->objectid == BTRFS_FREE_SPACE_OBJECTID)
		जाओ out;

	अगर (key->type == BTRFS_INODE_ITEM_KEY) अणु
		ret = changed_inode(sctx, result);
	पूर्ण अन्यथा अगर (!sctx->ignore_cur_inode) अणु
		अगर (key->type == BTRFS_INODE_REF_KEY ||
		    key->type == BTRFS_INODE_EXTREF_KEY)
			ret = changed_ref(sctx, result);
		अन्यथा अगर (key->type == BTRFS_XATTR_ITEM_KEY)
			ret = changed_xattr(sctx, result);
		अन्यथा अगर (key->type == BTRFS_EXTENT_DATA_KEY)
			ret = changed_extent(sctx, result);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक full_send_tree(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_root *send_root = sctx->send_root;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *eb;
	पूर्णांक slot;

	path = alloc_path_क्रम_send();
	अगर (!path)
		वापस -ENOMEM;
	path->पढ़ोa = READA_FORWARD_ALWAYS;

	key.objectid = BTRFS_FIRST_FREE_OBJECTID;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;

	ret = btrfs_search_slot_क्रम_पढ़ो(send_root, &key, path, 1, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret)
		जाओ out_finish;

	जबतक (1) अणु
		eb = path->nodes[0];
		slot = path->slots[0];
		btrfs_item_key_to_cpu(eb, &key, slot);

		ret = changed_cb(path, शून्य, &key,
				 BTRFS_COMPARE_TREE_NEW, sctx);
		अगर (ret < 0)
			जाओ out;

		ret = btrfs_next_item(send_root, path);
		अगर (ret < 0)
			जाओ out;
		अगर (ret) अणु
			ret  = 0;
			अवरोध;
		पूर्ण
	पूर्ण

out_finish:
	ret = finish_inode_अगर_needed(sctx, 1);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक tree_move_करोwn(काष्ठा btrfs_path *path, पूर्णांक *level, u64 पढ़ोa_min_gen)
अणु
	काष्ठा extent_buffer *eb;
	काष्ठा extent_buffer *parent = path->nodes[*level];
	पूर्णांक slot = path->slots[*level];
	स्थिर पूर्णांक nritems = btrfs_header_nritems(parent);
	u64 पढ़ोa_max;
	u64 पढ़ोa_करोne = 0;

	BUG_ON(*level == 0);
	eb = btrfs_पढ़ो_node_slot(parent, slot);
	अगर (IS_ERR(eb))
		वापस PTR_ERR(eb);

	/*
	 * Trigger पढ़ोahead क्रम the next leaves we will process, so that it is
	 * very likely that when we need them they are alपढ़ोy in memory and we
	 * will not block on disk IO. For nodes we only करो पढ़ोahead क्रम one,
	 * since the समय winकरोw between processing nodes is typically larger.
	 */
	पढ़ोa_max = (*level == 1 ? SZ_128K : eb->fs_info->nodesize);

	क्रम (slot++; slot < nritems && पढ़ोa_करोne < पढ़ोa_max; slot++) अणु
		अगर (btrfs_node_ptr_generation(parent, slot) > पढ़ोa_min_gen) अणु
			btrfs_पढ़ोahead_node_child(parent, slot);
			पढ़ोa_करोne += eb->fs_info->nodesize;
		पूर्ण
	पूर्ण

	path->nodes[*level - 1] = eb;
	path->slots[*level - 1] = 0;
	(*level)--;
	वापस 0;
पूर्ण

अटल पूर्णांक tree_move_next_or_upnext(काष्ठा btrfs_path *path,
				    पूर्णांक *level, पूर्णांक root_level)
अणु
	पूर्णांक ret = 0;
	पूर्णांक nritems;
	nritems = btrfs_header_nritems(path->nodes[*level]);

	path->slots[*level]++;

	जबतक (path->slots[*level] >= nritems) अणु
		अगर (*level == root_level)
			वापस -1;

		/* move upnext */
		path->slots[*level] = 0;
		मुक्त_extent_buffer(path->nodes[*level]);
		path->nodes[*level] = शून्य;
		(*level)++;
		path->slots[*level]++;

		nritems = btrfs_header_nritems(path->nodes[*level]);
		ret = 1;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Returns 1 अगर it had to move up and next. 0 is वापसed अगर it moved only next
 * or करोwn.
 */
अटल पूर्णांक tree_advance(काष्ठा btrfs_path *path,
			पूर्णांक *level, पूर्णांक root_level,
			पूर्णांक allow_करोwn,
			काष्ठा btrfs_key *key,
			u64 पढ़ोa_min_gen)
अणु
	पूर्णांक ret;

	अगर (*level == 0 || !allow_करोwn) अणु
		ret = tree_move_next_or_upnext(path, level, root_level);
	पूर्ण अन्यथा अणु
		ret = tree_move_करोwn(path, level, पढ़ोa_min_gen);
	पूर्ण
	अगर (ret >= 0) अणु
		अगर (*level == 0)
			btrfs_item_key_to_cpu(path->nodes[*level], key,
					path->slots[*level]);
		अन्यथा
			btrfs_node_key_to_cpu(path->nodes[*level], key,
					path->slots[*level]);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक tree_compare_item(काष्ठा btrfs_path *left_path,
			     काष्ठा btrfs_path *right_path,
			     अक्षर *पंचांगp_buf)
अणु
	पूर्णांक cmp;
	पूर्णांक len1, len2;
	अचिन्हित दीर्घ off1, off2;

	len1 = btrfs_item_size_nr(left_path->nodes[0], left_path->slots[0]);
	len2 = btrfs_item_size_nr(right_path->nodes[0], right_path->slots[0]);
	अगर (len1 != len2)
		वापस 1;

	off1 = btrfs_item_ptr_offset(left_path->nodes[0], left_path->slots[0]);
	off2 = btrfs_item_ptr_offset(right_path->nodes[0],
				right_path->slots[0]);

	पढ़ो_extent_buffer(left_path->nodes[0], पंचांगp_buf, off1, len1);

	cmp = स_भेद_extent_buffer(right_path->nodes[0], पंचांगp_buf, off2, len1);
	अगर (cmp)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * This function compares two trees and calls the provided callback क्रम
 * every changed/new/deleted item it finds.
 * If shared tree blocks are encountered, whole subtrees are skipped, making
 * the compare pretty fast on snapshotted subvolumes.
 *
 * This currently works on commit roots only. As commit roots are पढ़ो only,
 * we करोn't करो any locking. The commit roots are रक्षित with transactions.
 * Transactions are ended and rejoined when a commit is tried in between.
 *
 * This function checks क्रम modअगरications करोne to the trees जबतक comparing.
 * If it detects a change, it पातs immediately.
 */
अटल पूर्णांक btrfs_compare_trees(काष्ठा btrfs_root *left_root,
			काष्ठा btrfs_root *right_root, काष्ठा send_ctx *sctx)
अणु
	काष्ठा btrfs_fs_info *fs_info = left_root->fs_info;
	पूर्णांक ret;
	पूर्णांक cmp;
	काष्ठा btrfs_path *left_path = शून्य;
	काष्ठा btrfs_path *right_path = शून्य;
	काष्ठा btrfs_key left_key;
	काष्ठा btrfs_key right_key;
	अक्षर *पंचांगp_buf = शून्य;
	पूर्णांक left_root_level;
	पूर्णांक right_root_level;
	पूर्णांक left_level;
	पूर्णांक right_level;
	पूर्णांक left_end_reached;
	पूर्णांक right_end_reached;
	पूर्णांक advance_left;
	पूर्णांक advance_right;
	u64 left_blockptr;
	u64 right_blockptr;
	u64 left_gen;
	u64 right_gen;
	u64 पढ़ोa_min_gen;

	left_path = btrfs_alloc_path();
	अगर (!left_path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	right_path = btrfs_alloc_path();
	अगर (!right_path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	पंचांगp_buf = kvदो_स्मृति(fs_info->nodesize, GFP_KERNEL);
	अगर (!पंचांगp_buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	left_path->search_commit_root = 1;
	left_path->skip_locking = 1;
	right_path->search_commit_root = 1;
	right_path->skip_locking = 1;

	/*
	 * Strategy: Go to the first items of both trees. Then करो
	 *
	 * If both trees are at level 0
	 *   Compare keys of current items
	 *     If left < right treat left item as new, advance left tree
	 *       and repeat
	 *     If left > right treat right item as deleted, advance right tree
	 *       and repeat
	 *     If left == right करो deep compare of items, treat as changed अगर
	 *       needed, advance both trees and repeat
	 * If both trees are at the same level but not at level 0
	 *   Compare keys of current nodes/leafs
	 *     If left < right advance left tree and repeat
	 *     If left > right advance right tree and repeat
	 *     If left == right compare blockptrs of the next nodes/leafs
	 *       If they match advance both trees but stay at the same level
	 *         and repeat
	 *       If they करोn't match advance both trees जबतक allowing to go
	 *         deeper and repeat
	 * If tree levels are dअगरferent
	 *   Advance the tree that needs it and repeat
	 *
	 * Advancing a tree means:
	 *   If we are at level 0, try to go to the next slot. If that's not
	 *   possible, go one level up and repeat. Stop when we found a level
	 *   where we could go to the next slot. We may at this poपूर्णांक be on a
	 *   node or a leaf.
	 *
	 *   If we are not at level 0 and not on shared tree blocks, go one
	 *   level deeper.
	 *
	 *   If we are not at level 0 and on shared tree blocks, go one slot to
	 *   the right अगर possible or go up and right.
	 */

	करोwn_पढ़ो(&fs_info->commit_root_sem);
	left_level = btrfs_header_level(left_root->commit_root);
	left_root_level = left_level;
	left_path->nodes[left_level] =
			btrfs_clone_extent_buffer(left_root->commit_root);
	अगर (!left_path->nodes[left_level]) अणु
		up_पढ़ो(&fs_info->commit_root_sem);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	right_level = btrfs_header_level(right_root->commit_root);
	right_root_level = right_level;
	right_path->nodes[right_level] =
			btrfs_clone_extent_buffer(right_root->commit_root);
	अगर (!right_path->nodes[right_level]) अणु
		up_पढ़ो(&fs_info->commit_root_sem);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	/*
	 * Our right root is the parent root, जबतक the left root is the "send"
	 * root. We know that all new nodes/leaves in the left root must have
	 * a generation greater than the right root's generation, so we trigger
	 * पढ़ोahead क्रम those nodes and leaves of the left root, as we know we
	 * will need to पढ़ो them at some poपूर्णांक.
	 */
	पढ़ोa_min_gen = btrfs_header_generation(right_root->commit_root);
	up_पढ़ो(&fs_info->commit_root_sem);

	अगर (left_level == 0)
		btrfs_item_key_to_cpu(left_path->nodes[left_level],
				&left_key, left_path->slots[left_level]);
	अन्यथा
		btrfs_node_key_to_cpu(left_path->nodes[left_level],
				&left_key, left_path->slots[left_level]);
	अगर (right_level == 0)
		btrfs_item_key_to_cpu(right_path->nodes[right_level],
				&right_key, right_path->slots[right_level]);
	अन्यथा
		btrfs_node_key_to_cpu(right_path->nodes[right_level],
				&right_key, right_path->slots[right_level]);

	left_end_reached = right_end_reached = 0;
	advance_left = advance_right = 0;

	जबतक (1) अणु
		cond_resched();
		अगर (advance_left && !left_end_reached) अणु
			ret = tree_advance(left_path, &left_level,
					left_root_level,
					advance_left != ADVANCE_ONLY_NEXT,
					&left_key, पढ़ोa_min_gen);
			अगर (ret == -1)
				left_end_reached = ADVANCE;
			अन्यथा अगर (ret < 0)
				जाओ out;
			advance_left = 0;
		पूर्ण
		अगर (advance_right && !right_end_reached) अणु
			ret = tree_advance(right_path, &right_level,
					right_root_level,
					advance_right != ADVANCE_ONLY_NEXT,
					&right_key, पढ़ोa_min_gen);
			अगर (ret == -1)
				right_end_reached = ADVANCE;
			अन्यथा अगर (ret < 0)
				जाओ out;
			advance_right = 0;
		पूर्ण

		अगर (left_end_reached && right_end_reached) अणु
			ret = 0;
			जाओ out;
		पूर्ण अन्यथा अगर (left_end_reached) अणु
			अगर (right_level == 0) अणु
				ret = changed_cb(left_path, right_path,
						&right_key,
						BTRFS_COMPARE_TREE_DELETED,
						sctx);
				अगर (ret < 0)
					जाओ out;
			पूर्ण
			advance_right = ADVANCE;
			जारी;
		पूर्ण अन्यथा अगर (right_end_reached) अणु
			अगर (left_level == 0) अणु
				ret = changed_cb(left_path, right_path,
						&left_key,
						BTRFS_COMPARE_TREE_NEW,
						sctx);
				अगर (ret < 0)
					जाओ out;
			पूर्ण
			advance_left = ADVANCE;
			जारी;
		पूर्ण

		अगर (left_level == 0 && right_level == 0) अणु
			cmp = btrfs_comp_cpu_keys(&left_key, &right_key);
			अगर (cmp < 0) अणु
				ret = changed_cb(left_path, right_path,
						&left_key,
						BTRFS_COMPARE_TREE_NEW,
						sctx);
				अगर (ret < 0)
					जाओ out;
				advance_left = ADVANCE;
			पूर्ण अन्यथा अगर (cmp > 0) अणु
				ret = changed_cb(left_path, right_path,
						&right_key,
						BTRFS_COMPARE_TREE_DELETED,
						sctx);
				अगर (ret < 0)
					जाओ out;
				advance_right = ADVANCE;
			पूर्ण अन्यथा अणु
				क्रमागत btrfs_compare_tree_result result;

				WARN_ON(!extent_buffer_uptodate(left_path->nodes[0]));
				ret = tree_compare_item(left_path, right_path,
							पंचांगp_buf);
				अगर (ret)
					result = BTRFS_COMPARE_TREE_CHANGED;
				अन्यथा
					result = BTRFS_COMPARE_TREE_SAME;
				ret = changed_cb(left_path, right_path,
						 &left_key, result, sctx);
				अगर (ret < 0)
					जाओ out;
				advance_left = ADVANCE;
				advance_right = ADVANCE;
			पूर्ण
		पूर्ण अन्यथा अगर (left_level == right_level) अणु
			cmp = btrfs_comp_cpu_keys(&left_key, &right_key);
			अगर (cmp < 0) अणु
				advance_left = ADVANCE;
			पूर्ण अन्यथा अगर (cmp > 0) अणु
				advance_right = ADVANCE;
			पूर्ण अन्यथा अणु
				left_blockptr = btrfs_node_blockptr(
						left_path->nodes[left_level],
						left_path->slots[left_level]);
				right_blockptr = btrfs_node_blockptr(
						right_path->nodes[right_level],
						right_path->slots[right_level]);
				left_gen = btrfs_node_ptr_generation(
						left_path->nodes[left_level],
						left_path->slots[left_level]);
				right_gen = btrfs_node_ptr_generation(
						right_path->nodes[right_level],
						right_path->slots[right_level]);
				अगर (left_blockptr == right_blockptr &&
				    left_gen == right_gen) अणु
					/*
					 * As we're on a shared block, don't
					 * allow to go deeper.
					 */
					advance_left = ADVANCE_ONLY_NEXT;
					advance_right = ADVANCE_ONLY_NEXT;
				पूर्ण अन्यथा अणु
					advance_left = ADVANCE;
					advance_right = ADVANCE;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (left_level < right_level) अणु
			advance_right = ADVANCE;
		पूर्ण अन्यथा अणु
			advance_left = ADVANCE;
		पूर्ण
	पूर्ण

out:
	btrfs_मुक्त_path(left_path);
	btrfs_मुक्त_path(right_path);
	kvमुक्त(पंचांगp_buf);
	वापस ret;
पूर्ण

अटल पूर्णांक send_subvol(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक ret;

	अगर (!(sctx->flags & BTRFS_SEND_FLAG_OMIT_STREAM_HEADER)) अणु
		ret = send_header(sctx);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = send_subvol_begin(sctx);
	अगर (ret < 0)
		जाओ out;

	अगर (sctx->parent_root) अणु
		ret = btrfs_compare_trees(sctx->send_root, sctx->parent_root, sctx);
		अगर (ret < 0)
			जाओ out;
		ret = finish_inode_अगर_needed(sctx, 1);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		ret = full_send_tree(sctx);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	मुक्त_recorded_refs(sctx);
	वापस ret;
पूर्ण

/*
 * If orphan cleanup did हटाओ any orphans from a root, it means the tree
 * was modअगरied and thereक्रमe the commit root is not the same as the current
 * root anymore. This is a problem, because send uses the commit root and
 * thereक्रमe can see inode items that करोn't exist in the current root anymore,
 * and क्रम example make calls to btrfs_iget, which will करो tree lookups based
 * on the current root and not on the commit root. Those lookups will fail,
 * वापसing a -ESTALE error, and making send fail with that error. So make
 * sure a send करोes not see any orphans we have just हटाओd, and that it will
 * see the same inodes regardless of whether a transaction commit happened
 * beक्रमe it started (meaning that the commit root will be the same as the
 * current root) or not.
 */
अटल पूर्णांक ensure_commit_roots_uptodate(काष्ठा send_ctx *sctx)
अणु
	पूर्णांक i;
	काष्ठा btrfs_trans_handle *trans = शून्य;

again:
	अगर (sctx->parent_root &&
	    sctx->parent_root->node != sctx->parent_root->commit_root)
		जाओ commit_trans;

	क्रम (i = 0; i < sctx->clone_roots_cnt; i++)
		अगर (sctx->clone_roots[i].root->node !=
		    sctx->clone_roots[i].root->commit_root)
			जाओ commit_trans;

	अगर (trans)
		वापस btrfs_end_transaction(trans);

	वापस 0;

commit_trans:
	/* Use any root, all fs roots will get their commit roots updated. */
	अगर (!trans) अणु
		trans = btrfs_join_transaction(sctx->send_root);
		अगर (IS_ERR(trans))
			वापस PTR_ERR(trans);
		जाओ again;
	पूर्ण

	वापस btrfs_commit_transaction(trans);
पूर्ण

/*
 * Make sure any existing dellaloc is flushed क्रम any root used by a send
 * operation so that we करो not miss any data and we करो not race with ग_लिखोback
 * finishing and changing a tree जबतक send is using the tree. This could
 * happen अगर a subvolume is in RW mode, has delalloc, is turned to RO mode and
 * a send operation then uses the subvolume.
 * After flushing delalloc ensure_commit_roots_uptodate() must be called.
 */
अटल पूर्णांक flush_delalloc_roots(काष्ठा send_ctx *sctx)
अणु
	काष्ठा btrfs_root *root = sctx->parent_root;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (root) अणु
		ret = btrfs_start_delalloc_snapshot(root, false);
		अगर (ret)
			वापस ret;
		btrfs_रुको_ordered_extents(root, U64_MAX, 0, U64_MAX);
	पूर्ण

	क्रम (i = 0; i < sctx->clone_roots_cnt; i++) अणु
		root = sctx->clone_roots[i].root;
		ret = btrfs_start_delalloc_snapshot(root, false);
		अगर (ret)
			वापस ret;
		btrfs_रुको_ordered_extents(root, U64_MAX, 0, U64_MAX);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम btrfs_root_dec_send_in_progress(काष्ठा btrfs_root* root)
अणु
	spin_lock(&root->root_item_lock);
	root->send_in_progress--;
	/*
	 * Not much left to करो, we करोn't know why it's unbalanced and
	 * can't blindly reset it to 0.
	 */
	अगर (root->send_in_progress < 0)
		btrfs_err(root->fs_info,
			  "send_in_progress unbalanced %d root %llu",
			  root->send_in_progress, root->root_key.objectid);
	spin_unlock(&root->root_item_lock);
पूर्ण

अटल व्योम dedupe_in_progress_warn(स्थिर काष्ठा btrfs_root *root)
अणु
	btrfs_warn_rl(root->fs_info,
"cannot use root %llu for send while deduplications on it are in progress (%d in progress)",
		      root->root_key.objectid, root->dedupe_in_progress);
पूर्ण

दीर्घ btrfs_ioctl_send(काष्ठा file *mnt_file, काष्ठा btrfs_ioctl_send_args *arg)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_root *send_root = BTRFS_I(file_inode(mnt_file))->root;
	काष्ठा btrfs_fs_info *fs_info = send_root->fs_info;
	काष्ठा btrfs_root *clone_root;
	काष्ठा send_ctx *sctx = शून्य;
	u32 i;
	u64 *clone_sources_पंचांगp = शून्य;
	पूर्णांक clone_sources_to_rollback = 0;
	माप_प्रकार alloc_size;
	पूर्णांक sort_clone_roots = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	/*
	 * The subvolume must reमुख्य पढ़ो-only during send, protect against
	 * making it RW. This also protects against deletion.
	 */
	spin_lock(&send_root->root_item_lock);
	अगर (btrfs_root_पढ़ोonly(send_root) && send_root->dedupe_in_progress) अणु
		dedupe_in_progress_warn(send_root);
		spin_unlock(&send_root->root_item_lock);
		वापस -EAGAIN;
	पूर्ण
	send_root->send_in_progress++;
	spin_unlock(&send_root->root_item_lock);

	/*
	 * Userspace tools करो the checks and warn the user अगर it's
	 * not RO.
	 */
	अगर (!btrfs_root_पढ़ोonly(send_root)) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	/*
	 * Check that we करोn't overflow at later allocations, we request
	 * clone_sources_count + 1 items, and compare to अचिन्हित दीर्घ inside
	 * access_ok.
	 */
	अगर (arg->clone_sources_count >
	    अच_दीर्घ_उच्च / माप(काष्ठा clone_root) - 1) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (arg->flags & ~BTRFS_SEND_FLAG_MASK) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	sctx = kzalloc(माप(काष्ठा send_ctx), GFP_KERNEL);
	अगर (!sctx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&sctx->new_refs);
	INIT_LIST_HEAD(&sctx->deleted_refs);
	INIT_RADIX_TREE(&sctx->name_cache, GFP_KERNEL);
	INIT_LIST_HEAD(&sctx->name_cache_list);

	sctx->flags = arg->flags;

	sctx->send_filp = fget(arg->send_fd);
	अगर (!sctx->send_filp) अणु
		ret = -EBADF;
		जाओ out;
	पूर्ण

	sctx->send_root = send_root;
	/*
	 * Unlikely but possible, अगर the subvolume is marked क्रम deletion but
	 * is slow to हटाओ the directory entry, send can still be started
	 */
	अगर (btrfs_root_dead(sctx->send_root)) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	sctx->clone_roots_cnt = arg->clone_sources_count;

	sctx->send_max_size = BTRFS_SEND_BUF_SIZE;
	sctx->send_buf = kvदो_स्मृति(sctx->send_max_size, GFP_KERNEL);
	अगर (!sctx->send_buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	sctx->pending_dir_moves = RB_ROOT;
	sctx->रुकोing_dir_moves = RB_ROOT;
	sctx->orphan_dirs = RB_ROOT;

	sctx->clone_roots = kvसुस्मृति(माप(*sctx->clone_roots),
				     arg->clone_sources_count + 1,
				     GFP_KERNEL);
	अगर (!sctx->clone_roots) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	alloc_size = array_size(माप(*arg->clone_sources),
				arg->clone_sources_count);

	अगर (arg->clone_sources_count) अणु
		clone_sources_पंचांगp = kvदो_स्मृति(alloc_size, GFP_KERNEL);
		अगर (!clone_sources_पंचांगp) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		ret = copy_from_user(clone_sources_पंचांगp, arg->clone_sources,
				alloc_size);
		अगर (ret) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < arg->clone_sources_count; i++) अणु
			clone_root = btrfs_get_fs_root(fs_info,
						clone_sources_पंचांगp[i], true);
			अगर (IS_ERR(clone_root)) अणु
				ret = PTR_ERR(clone_root);
				जाओ out;
			पूर्ण
			spin_lock(&clone_root->root_item_lock);
			अगर (!btrfs_root_पढ़ोonly(clone_root) ||
			    btrfs_root_dead(clone_root)) अणु
				spin_unlock(&clone_root->root_item_lock);
				btrfs_put_root(clone_root);
				ret = -EPERM;
				जाओ out;
			पूर्ण
			अगर (clone_root->dedupe_in_progress) अणु
				dedupe_in_progress_warn(clone_root);
				spin_unlock(&clone_root->root_item_lock);
				btrfs_put_root(clone_root);
				ret = -EAGAIN;
				जाओ out;
			पूर्ण
			clone_root->send_in_progress++;
			spin_unlock(&clone_root->root_item_lock);

			sctx->clone_roots[i].root = clone_root;
			clone_sources_to_rollback = i + 1;
		पूर्ण
		kvमुक्त(clone_sources_पंचांगp);
		clone_sources_पंचांगp = शून्य;
	पूर्ण

	अगर (arg->parent_root) अणु
		sctx->parent_root = btrfs_get_fs_root(fs_info, arg->parent_root,
						      true);
		अगर (IS_ERR(sctx->parent_root)) अणु
			ret = PTR_ERR(sctx->parent_root);
			जाओ out;
		पूर्ण

		spin_lock(&sctx->parent_root->root_item_lock);
		sctx->parent_root->send_in_progress++;
		अगर (!btrfs_root_पढ़ोonly(sctx->parent_root) ||
				btrfs_root_dead(sctx->parent_root)) अणु
			spin_unlock(&sctx->parent_root->root_item_lock);
			ret = -EPERM;
			जाओ out;
		पूर्ण
		अगर (sctx->parent_root->dedupe_in_progress) अणु
			dedupe_in_progress_warn(sctx->parent_root);
			spin_unlock(&sctx->parent_root->root_item_lock);
			ret = -EAGAIN;
			जाओ out;
		पूर्ण
		spin_unlock(&sctx->parent_root->root_item_lock);
	पूर्ण

	/*
	 * Clones from send_root are allowed, but only अगर the clone source
	 * is behind the current send position. This is checked जबतक searching
	 * क्रम possible clone sources.
	 */
	sctx->clone_roots[sctx->clone_roots_cnt++].root =
		btrfs_grab_root(sctx->send_root);

	/* We करो a द्वा_खोज later */
	sort(sctx->clone_roots, sctx->clone_roots_cnt,
			माप(*sctx->clone_roots), __clone_root_cmp_sort,
			शून्य);
	sort_clone_roots = 1;

	ret = flush_delalloc_roots(sctx);
	अगर (ret)
		जाओ out;

	ret = ensure_commit_roots_uptodate(sctx);
	अगर (ret)
		जाओ out;

	mutex_lock(&fs_info->balance_mutex);
	अगर (test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags)) अणु
		mutex_unlock(&fs_info->balance_mutex);
		btrfs_warn_rl(fs_info,
		"cannot run send because a balance operation is in progress");
		ret = -EAGAIN;
		जाओ out;
	पूर्ण
	fs_info->send_in_progress++;
	mutex_unlock(&fs_info->balance_mutex);

	current->journal_info = BTRFS_SEND_TRANS_STUB;
	ret = send_subvol(sctx);
	current->journal_info = शून्य;
	mutex_lock(&fs_info->balance_mutex);
	fs_info->send_in_progress--;
	mutex_unlock(&fs_info->balance_mutex);
	अगर (ret < 0)
		जाओ out;

	अगर (!(sctx->flags & BTRFS_SEND_FLAG_OMIT_END_CMD)) अणु
		ret = begin_cmd(sctx, BTRFS_SEND_C_END);
		अगर (ret < 0)
			जाओ out;
		ret = send_cmd(sctx);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

out:
	WARN_ON(sctx && !ret && !RB_EMPTY_ROOT(&sctx->pending_dir_moves));
	जबतक (sctx && !RB_EMPTY_ROOT(&sctx->pending_dir_moves)) अणु
		काष्ठा rb_node *n;
		काष्ठा pending_dir_move *pm;

		n = rb_first(&sctx->pending_dir_moves);
		pm = rb_entry(n, काष्ठा pending_dir_move, node);
		जबतक (!list_empty(&pm->list)) अणु
			काष्ठा pending_dir_move *pm2;

			pm2 = list_first_entry(&pm->list,
					       काष्ठा pending_dir_move, list);
			मुक्त_pending_move(sctx, pm2);
		पूर्ण
		मुक्त_pending_move(sctx, pm);
	पूर्ण

	WARN_ON(sctx && !ret && !RB_EMPTY_ROOT(&sctx->रुकोing_dir_moves));
	जबतक (sctx && !RB_EMPTY_ROOT(&sctx->रुकोing_dir_moves)) अणु
		काष्ठा rb_node *n;
		काष्ठा रुकोing_dir_move *dm;

		n = rb_first(&sctx->रुकोing_dir_moves);
		dm = rb_entry(n, काष्ठा रुकोing_dir_move, node);
		rb_erase(&dm->node, &sctx->रुकोing_dir_moves);
		kमुक्त(dm);
	पूर्ण

	WARN_ON(sctx && !ret && !RB_EMPTY_ROOT(&sctx->orphan_dirs));
	जबतक (sctx && !RB_EMPTY_ROOT(&sctx->orphan_dirs)) अणु
		काष्ठा rb_node *n;
		काष्ठा orphan_dir_info *odi;

		n = rb_first(&sctx->orphan_dirs);
		odi = rb_entry(n, काष्ठा orphan_dir_info, node);
		मुक्त_orphan_dir_info(sctx, odi);
	पूर्ण

	अगर (sort_clone_roots) अणु
		क्रम (i = 0; i < sctx->clone_roots_cnt; i++) अणु
			btrfs_root_dec_send_in_progress(
					sctx->clone_roots[i].root);
			btrfs_put_root(sctx->clone_roots[i].root);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; sctx && i < clone_sources_to_rollback; i++) अणु
			btrfs_root_dec_send_in_progress(
					sctx->clone_roots[i].root);
			btrfs_put_root(sctx->clone_roots[i].root);
		पूर्ण

		btrfs_root_dec_send_in_progress(send_root);
	पूर्ण
	अगर (sctx && !IS_ERR_OR_शून्य(sctx->parent_root)) अणु
		btrfs_root_dec_send_in_progress(sctx->parent_root);
		btrfs_put_root(sctx->parent_root);
	पूर्ण

	kvमुक्त(clone_sources_पंचांगp);

	अगर (sctx) अणु
		अगर (sctx->send_filp)
			fput(sctx->send_filp);

		kvमुक्त(sctx->clone_roots);
		kvमुक्त(sctx->send_buf);

		name_cache_मुक्त(sctx);

		kमुक्त(sctx);
	पूर्ण

	वापस ret;
पूर्ण
