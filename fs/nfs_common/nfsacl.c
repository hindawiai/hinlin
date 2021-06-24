<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fs/nfs_common/nfsacl.c
 *
 *  Copyright (C) 2002-2003 Andreas Gruenbacher <agruen@suse.de>
 */

/*
 * The Solaris nfsacl protocol represents some ACLs slightly dअगरferently
 * than POSIX 1003.1e draft 17 करोes (and we करो):
 *
 *  - Minimal ACLs always have an ACL_MASK entry, so they have
 *    four instead of three entries.
 *  - The ACL_MASK entry in such minimal ACLs always has the same
 *    permissions as the ACL_GROUP_OBJ entry. (In extended ACLs
 *    the ACL_MASK and ACL_GROUP_OBJ entries may dअगरfer.)
 *  - The identअगरier fields of the ACL_USER_OBJ and ACL_GROUP_OBJ
 *    entries contain the identअगरiers of the owner and owning group.
 *    (In POSIX ACLs we always set them to ACL_UNDEFINED_ID).
 *  - ACL entries in the kernel are kept sorted in ascending order
 *    of (e_tag, e_id). Solaris ACLs are unsorted.
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/gfp.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/nfsacl.h>
#समावेश <linux/nfs3.h>
#समावेश <linux/sort.h>

MODULE_LICENSE("GPL");

काष्ठा nfsacl_encode_desc अणु
	काष्ठा xdr_array2_desc desc;
	अचिन्हित पूर्णांक count;
	काष्ठा posix_acl *acl;
	पूर्णांक typeflag;
	kuid_t uid;
	kgid_t gid;
पूर्ण;

काष्ठा nfsacl_simple_acl अणु
	काष्ठा posix_acl acl;
	काष्ठा posix_acl_entry ace[4];
पूर्ण;

अटल पूर्णांक
xdr_nfsace_encode(काष्ठा xdr_array2_desc *desc, व्योम *elem)
अणु
	काष्ठा nfsacl_encode_desc *nfsacl_desc =
		(काष्ठा nfsacl_encode_desc *) desc;
	__be32 *p = elem;

	काष्ठा posix_acl_entry *entry =
		&nfsacl_desc->acl->a_entries[nfsacl_desc->count++];

	*p++ = htonl(entry->e_tag | nfsacl_desc->typeflag);
	चयन(entry->e_tag) अणु
		हाल ACL_USER_OBJ:
			*p++ = htonl(from_kuid(&init_user_ns, nfsacl_desc->uid));
			अवरोध;
		हाल ACL_GROUP_OBJ:
			*p++ = htonl(from_kgid(&init_user_ns, nfsacl_desc->gid));
			अवरोध;
		हाल ACL_USER:
			*p++ = htonl(from_kuid(&init_user_ns, entry->e_uid));
			अवरोध;
		हाल ACL_GROUP:
			*p++ = htonl(from_kgid(&init_user_ns, entry->e_gid));
			अवरोध;
		शेष:  /* Solaris depends on that! */
			*p++ = 0;
			अवरोध;
	पूर्ण
	*p++ = htonl(entry->e_perm & S_IRWXO);
	वापस 0;
पूर्ण

/**
 * nfsacl_encode - Encode an NFSv3 ACL
 *
 * @buf: destination xdr_buf to contain XDR encoded ACL
 * @base: byte offset in xdr_buf where XDR'd ACL begins
 * @inode: inode of file whose ACL this is
 * @acl: posix_acl to encode
 * @encode_entries: whether to encode ACEs as well
 * @typeflag: ACL type: NFS_ACL_DEFAULT or zero
 *
 * Returns size of encoded ACL in bytes or a negative त्रुटि_सं value.
 */
पूर्णांक nfsacl_encode(काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base, काष्ठा inode *inode,
		  काष्ठा posix_acl *acl, पूर्णांक encode_entries, पूर्णांक typeflag)
अणु
	पूर्णांक entries = (acl && acl->a_count) ? max_t(पूर्णांक, acl->a_count, 4) : 0;
	काष्ठा nfsacl_encode_desc nfsacl_desc = अणु
		.desc = अणु
			.elem_size = 12,
			.array_len = encode_entries ? entries : 0,
			.xcode = xdr_nfsace_encode,
		पूर्ण,
		.acl = acl,
		.typeflag = typeflag,
		.uid = inode->i_uid,
		.gid = inode->i_gid,
	पूर्ण;
	काष्ठा nfsacl_simple_acl aclbuf;
	पूर्णांक err;

	अगर (entries > NFS_ACL_MAX_ENTRIES ||
	    xdr_encode_word(buf, base, entries))
		वापस -EINVAL;
	अगर (encode_entries && acl && acl->a_count == 3) अणु
		काष्ठा posix_acl *acl2 = &aclbuf.acl;

		/* Aव्योम the use of posix_acl_alloc().  nfsacl_encode() is
		 * invoked in contexts where a memory allocation failure is
		 * fatal.  Fortunately this fake ACL is small enough to
		 * स्थिरruct on the stack. */
		posix_acl_init(acl2, 4);

		/* Insert entries in canonical order: other orders seem
		 to confuse Solaris VxFS. */
		acl2->a_entries[0] = acl->a_entries[0];  /* ACL_USER_OBJ */
		acl2->a_entries[1] = acl->a_entries[1];  /* ACL_GROUP_OBJ */
		acl2->a_entries[2] = acl->a_entries[1];  /* ACL_MASK */
		acl2->a_entries[2].e_tag = ACL_MASK;
		acl2->a_entries[3] = acl->a_entries[2];  /* ACL_OTHER */
		nfsacl_desc.acl = acl2;
	पूर्ण
	err = xdr_encode_array2(buf, base + 4, &nfsacl_desc.desc);
	अगर (!err)
		err = 8 + nfsacl_desc.desc.elem_size *
			  nfsacl_desc.desc.array_len;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(nfsacl_encode);

/**
 * nfs_stream_encode_acl - Encode an NFSv3 ACL
 *
 * @xdr: an xdr_stream positioned to receive an encoded ACL
 * @inode: inode of file whose ACL this is
 * @acl: posix_acl to encode
 * @encode_entries: whether to encode ACEs as well
 * @typeflag: ACL type: NFS_ACL_DEFAULT or zero
 *
 * Return values:
 *   %false: The ACL could not be encoded
 *   %true: @xdr is advanced to the next available position
 */
bool nfs_stream_encode_acl(काष्ठा xdr_stream *xdr, काष्ठा inode *inode,
			   काष्ठा posix_acl *acl, पूर्णांक encode_entries,
			   पूर्णांक typeflag)
अणु
	स्थिर माप_प्रकार elem_size = XDR_UNIT * 3;
	u32 entries = (acl && acl->a_count) ? max_t(पूर्णांक, acl->a_count, 4) : 0;
	काष्ठा nfsacl_encode_desc nfsacl_desc = अणु
		.desc = अणु
			.elem_size = elem_size,
			.array_len = encode_entries ? entries : 0,
			.xcode = xdr_nfsace_encode,
		पूर्ण,
		.acl = acl,
		.typeflag = typeflag,
		.uid = inode->i_uid,
		.gid = inode->i_gid,
	पूर्ण;
	काष्ठा nfsacl_simple_acl aclbuf;
	अचिन्हित पूर्णांक base;
	पूर्णांक err;

	अगर (entries > NFS_ACL_MAX_ENTRIES)
		वापस false;
	अगर (xdr_stream_encode_u32(xdr, entries) < 0)
		वापस false;

	अगर (encode_entries && acl && acl->a_count == 3) अणु
		काष्ठा posix_acl *acl2 = &aclbuf.acl;

		/* Aव्योम the use of posix_acl_alloc().  nfsacl_encode() is
		 * invoked in contexts where a memory allocation failure is
		 * fatal.  Fortunately this fake ACL is small enough to
		 * स्थिरruct on the stack. */
		posix_acl_init(acl2, 4);

		/* Insert entries in canonical order: other orders seem
		 to confuse Solaris VxFS. */
		acl2->a_entries[0] = acl->a_entries[0];  /* ACL_USER_OBJ */
		acl2->a_entries[1] = acl->a_entries[1];  /* ACL_GROUP_OBJ */
		acl2->a_entries[2] = acl->a_entries[1];  /* ACL_MASK */
		acl2->a_entries[2].e_tag = ACL_MASK;
		acl2->a_entries[3] = acl->a_entries[2];  /* ACL_OTHER */
		nfsacl_desc.acl = acl2;
	पूर्ण

	base = xdr_stream_pos(xdr);
	अगर (!xdr_reserve_space(xdr, XDR_UNIT +
			       elem_size * nfsacl_desc.desc.array_len))
		वापस false;
	err = xdr_encode_array2(xdr->buf, base, &nfsacl_desc.desc);
	अगर (err)
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_stream_encode_acl);


काष्ठा nfsacl_decode_desc अणु
	काष्ठा xdr_array2_desc desc;
	अचिन्हित पूर्णांक count;
	काष्ठा posix_acl *acl;
पूर्ण;

अटल पूर्णांक
xdr_nfsace_decode(काष्ठा xdr_array2_desc *desc, व्योम *elem)
अणु
	काष्ठा nfsacl_decode_desc *nfsacl_desc =
		(काष्ठा nfsacl_decode_desc *) desc;
	__be32 *p = elem;
	काष्ठा posix_acl_entry *entry;
	अचिन्हित पूर्णांक id;

	अगर (!nfsacl_desc->acl) अणु
		अगर (desc->array_len > NFS_ACL_MAX_ENTRIES)
			वापस -EINVAL;
		nfsacl_desc->acl = posix_acl_alloc(desc->array_len, GFP_KERNEL);
		अगर (!nfsacl_desc->acl)
			वापस -ENOMEM;
		nfsacl_desc->count = 0;
	पूर्ण

	entry = &nfsacl_desc->acl->a_entries[nfsacl_desc->count++];
	entry->e_tag = ntohl(*p++) & ~NFS_ACL_DEFAULT;
	id = ntohl(*p++);
	entry->e_perm = ntohl(*p++);

	चयन(entry->e_tag) अणु
		हाल ACL_USER:
			entry->e_uid = make_kuid(&init_user_ns, id);
			अगर (!uid_valid(entry->e_uid))
				वापस -EINVAL;
			अवरोध;
		हाल ACL_GROUP:
			entry->e_gid = make_kgid(&init_user_ns, id);
			अगर (!gid_valid(entry->e_gid))
				वापस -EINVAL;
			अवरोध;
		हाल ACL_USER_OBJ:
		हाल ACL_GROUP_OBJ:
		हाल ACL_OTHER:
			अगर (entry->e_perm & ~S_IRWXO)
				वापस -EINVAL;
			अवरोध;
		हाल ACL_MASK:
			/* Solaris someबार sets additional bits in the mask */
			entry->e_perm &= S_IRWXO;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
cmp_acl_entry(स्थिर व्योम *x, स्थिर व्योम *y)
अणु
	स्थिर काष्ठा posix_acl_entry *a = x, *b = y;

	अगर (a->e_tag != b->e_tag)
		वापस a->e_tag - b->e_tag;
	अन्यथा अगर ((a->e_tag == ACL_USER) && uid_gt(a->e_uid, b->e_uid))
		वापस 1;
	अन्यथा अगर ((a->e_tag == ACL_USER) && uid_lt(a->e_uid, b->e_uid))
		वापस -1;
	अन्यथा अगर ((a->e_tag == ACL_GROUP) && gid_gt(a->e_gid, b->e_gid))
		वापस 1;
	अन्यथा अगर ((a->e_tag == ACL_GROUP) && gid_lt(a->e_gid, b->e_gid))
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * Convert from a Solaris ACL to a POSIX 1003.1e draft 17 ACL.
 */
अटल पूर्णांक
posix_acl_from_nfsacl(काष्ठा posix_acl *acl)
अणु
	काष्ठा posix_acl_entry *pa, *pe,
	       *group_obj = शून्य, *mask = शून्य;

	अगर (!acl)
		वापस 0;

	sort(acl->a_entries, acl->a_count, माप(काष्ठा posix_acl_entry),
	     cmp_acl_entry, शून्य);

	/* Find the ACL_GROUP_OBJ and ACL_MASK entries. */
	FOREACH_ACL_ENTRY(pa, acl, pe) अणु
		चयन(pa->e_tag) अणु
			हाल ACL_USER_OBJ:
				अवरोध;
			हाल ACL_GROUP_OBJ:
				group_obj = pa;
				अवरोध;
			हाल ACL_MASK:
				mask = pa;
				fallthrough;
			हाल ACL_OTHER:
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (acl->a_count == 4 && group_obj && mask &&
	    mask->e_perm == group_obj->e_perm) अणु
		/* हटाओ bogus ACL_MASK entry */
		स_हटाओ(mask, mask+1, (3 - (mask - acl->a_entries)) *
				      माप(काष्ठा posix_acl_entry));
		acl->a_count = 3;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * nfsacl_decode - Decode an NFSv3 ACL
 *
 * @buf: xdr_buf containing XDR'd ACL data to decode
 * @base: byte offset in xdr_buf where XDR'd ACL begins
 * @aclcnt: count of ACEs in decoded posix_acl
 * @pacl: buffer in which to place decoded posix_acl
 *
 * Returns the length of the decoded ACL in bytes, or a negative त्रुटि_सं value.
 */
पूर्णांक nfsacl_decode(काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक *aclcnt,
		  काष्ठा posix_acl **pacl)
अणु
	काष्ठा nfsacl_decode_desc nfsacl_desc = अणु
		.desc = अणु
			.elem_size = 12,
			.xcode = pacl ? xdr_nfsace_decode : शून्य,
		पूर्ण,
	पूर्ण;
	u32 entries;
	पूर्णांक err;

	अगर (xdr_decode_word(buf, base, &entries) ||
	    entries > NFS_ACL_MAX_ENTRIES)
		वापस -EINVAL;
	nfsacl_desc.desc.array_maxlen = entries;
	err = xdr_decode_array2(buf, base + 4, &nfsacl_desc.desc);
	अगर (err)
		वापस err;
	अगर (pacl) अणु
		अगर (entries != nfsacl_desc.desc.array_len ||
		    posix_acl_from_nfsacl(nfsacl_desc.acl) != 0) अणु
			posix_acl_release(nfsacl_desc.acl);
			वापस -EINVAL;
		पूर्ण
		*pacl = nfsacl_desc.acl;
	पूर्ण
	अगर (aclcnt)
		*aclcnt = entries;
	वापस 8 + nfsacl_desc.desc.elem_size *
		   nfsacl_desc.desc.array_len;
पूर्ण
EXPORT_SYMBOL_GPL(nfsacl_decode);

/**
 * nfs_stream_decode_acl - Decode an NFSv3 ACL
 *
 * @xdr: an xdr_stream positioned at an encoded ACL
 * @aclcnt: OUT: count of ACEs in decoded posix_acl
 * @pacl: OUT: a dynamically-allocated buffer containing the decoded posix_acl
 *
 * Return values:
 *   %false: The encoded ACL is not valid
 *   %true: @pacl contains a decoded ACL, and @xdr is advanced
 *
 * On a successful वापस, caller must release *pacl using posix_acl_release().
 */
bool nfs_stream_decode_acl(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक *aclcnt,
			   काष्ठा posix_acl **pacl)
अणु
	स्थिर माप_प्रकार elem_size = XDR_UNIT * 3;
	काष्ठा nfsacl_decode_desc nfsacl_desc = अणु
		.desc = अणु
			.elem_size = elem_size,
			.xcode = pacl ? xdr_nfsace_decode : शून्य,
		पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक base;
	u32 entries;

	अगर (xdr_stream_decode_u32(xdr, &entries) < 0)
		वापस false;
	अगर (entries > NFS_ACL_MAX_ENTRIES)
		वापस false;

	base = xdr_stream_pos(xdr);
	अगर (!xdr_अंतरभूत_decode(xdr, XDR_UNIT + elem_size * entries))
		वापस false;
	nfsacl_desc.desc.array_maxlen = entries;
	अगर (xdr_decode_array2(xdr->buf, base, &nfsacl_desc.desc))
		वापस false;

	अगर (pacl) अणु
		अगर (entries != nfsacl_desc.desc.array_len ||
		    posix_acl_from_nfsacl(nfsacl_desc.acl) != 0) अणु
			posix_acl_release(nfsacl_desc.acl);
			वापस false;
		पूर्ण
		*pacl = nfsacl_desc.acl;
	पूर्ण
	अगर (aclcnt)
		*aclcnt = entries;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_stream_decode_acl);
