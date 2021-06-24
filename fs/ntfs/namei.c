<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * namei.c - NTFS kernel directory inode operations. Part of the Linux-NTFS
 *	     project.
 *
 * Copyright (c) 2001-2006 Anton Altaparmakov
 */

#समावेश <linux/dcache.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/security.h>
#समावेश <linux/slab.h>

#समावेश "attrib.h"
#समावेश "debug.h"
#समावेश "dir.h"
#समावेश "mft.h"
#समावेश "ntfs.h"

/**
 * ntfs_lookup - find the inode represented by a dentry in a directory inode
 * @dir_ino:	directory inode in which to look क्रम the inode
 * @dent:	dentry representing the inode to look क्रम
 * @flags:	lookup flags
 *
 * In लघु, ntfs_lookup() looks क्रम the inode represented by the dentry @dent
 * in the directory inode @dir_ino and अगर found attaches the inode to the
 * dentry @dent.
 *
 * In more detail, the dentry @dent specअगरies which inode to look क्रम by
 * supplying the name of the inode in @dent->d_name.name. ntfs_lookup()
 * converts the name to Unicode and walks the contents of the directory inode
 * @dir_ino looking क्रम the converted Unicode name. If the name is found in the
 * directory, the corresponding inode is loaded by calling ntfs_iget() on its
 * inode number and the inode is associated with the dentry @dent via a call to
 * d_splice_alias().
 *
 * If the name is not found in the directory, a शून्य inode is inserted पूर्णांकo the
 * dentry @dent via a call to d_add(). The dentry is then termed a negative
 * dentry.
 *
 * Only अगर an actual error occurs, करो we वापस an error via ERR_PTR().
 *
 * In order to handle the हाल insensitivity issues of NTFS with regards to the
 * dcache and the dcache requiring only one dentry per directory, we deal with
 * dentry aliases that only dअगरfer in हाल in ->ntfs_lookup() जबतक मुख्यtaining
 * a हाल sensitive dcache. This means that we get the full benefit of dcache
 * speed when the file/directory is looked up with the same हाल as वापसed by
 * ->ntfs_सूची_पढ़ो() but that a lookup क्रम any other हाल (or क्रम the लघु file
 * name) will not find anything in dcache and will enter ->ntfs_lookup()
 * instead, where we search the directory क्रम a fully matching file name
 * (including हाल) and अगर that is not found, we search क्रम a file name that
 * matches with dअगरferent हाल and अगर that has non-POSIX semantics we वापस
 * that. We actually करो only one search (हाल sensitive) and keep tअसल on
 * whether we have found a हाल insensitive match in the process.
 *
 * To simplअगरy matters क्रम us, we करो not treat the लघु vs दीर्घ filenames as
 * two hard links but instead अगर the lookup matches a लघु filename, we
 * वापस the dentry क्रम the corresponding दीर्घ filename instead.
 *
 * There are three हालs we need to distinguish here:
 *
 * 1) @dent perfectly matches (i.e. including हाल) a directory entry with a
 *    file name in the WIN32 or POSIX namespaces. In this हाल
 *    ntfs_lookup_inode_by_name() will वापस with name set to शून्य and we
 *    just d_splice_alias() @dent.
 * 2) @dent matches (not including हाल) a directory entry with a file name in
 *    the WIN32 namespace. In this हाल ntfs_lookup_inode_by_name() will वापस
 *    with name set to poपूर्णांक to a kदो_स्मृति()ed ntfs_name काष्ठाure containing
 *    the properly हालd little endian Unicode name. We convert the name to the
 *    current NLS code page, search अगर a dentry with this name alपढ़ोy exists
 *    and अगर so वापस that instead of @dent.  At this poपूर्णांक things are
 *    complicated by the possibility of 'disconnected' dentries due to NFS
 *    which we deal with appropriately (see the code comments).  The VFS will
 *    then destroy the old @dent and use the one we वापसed.  If a dentry is
 *    not found, we allocate a new one, d_splice_alias() it, and वापस it as
 *    above.
 * 3) @dent matches either perfectly or not (i.e. we करोn't care about हाल) a
 *    directory entry with a file name in the DOS namespace. In this हाल
 *    ntfs_lookup_inode_by_name() will वापस with name set to poपूर्णांक to a
 *    kदो_स्मृति()ed ntfs_name काष्ठाure containing the mft reference (cpu endian)
 *    of the inode. We use the mft reference to पढ़ो the inode and to find the
 *    file name in the WIN32 namespace corresponding to the matched लघु file
 *    name. We then convert the name to the current NLS code page, and proceed
 *    searching क्रम a dentry with this name, etc, as in हाल 2), above.
 *
 * Locking: Caller must hold i_mutex on the directory.
 */
अटल काष्ठा dentry *ntfs_lookup(काष्ठा inode *dir_ino, काष्ठा dentry *dent,
		अचिन्हित पूर्णांक flags)
अणु
	ntfs_volume *vol = NTFS_SB(dir_ino->i_sb);
	काष्ठा inode *dent_inode;
	ntfsअक्षर *uname;
	ntfs_name *name = शून्य;
	MFT_REF mref;
	अचिन्हित दीर्घ dent_ino;
	पूर्णांक uname_len;

	ntfs_debug("Looking up %pd in directory inode 0x%lx.",
			dent, dir_ino->i_ino);
	/* Convert the name of the dentry to Unicode. */
	uname_len = ntfs_nlstoucs(vol, dent->d_name.name, dent->d_name.len,
			&uname);
	अगर (uname_len < 0) अणु
		अगर (uname_len != -ENAMETOOLONG)
			ntfs_error(vol->sb, "Failed to convert name to "
					"Unicode.");
		वापस ERR_PTR(uname_len);
	पूर्ण
	mref = ntfs_lookup_inode_by_name(NTFS_I(dir_ino), uname, uname_len,
			&name);
	kmem_cache_मुक्त(ntfs_name_cache, uname);
	अगर (!IS_ERR_MREF(mref)) अणु
		dent_ino = MREF(mref);
		ntfs_debug("Found inode 0x%lx. Calling ntfs_iget.", dent_ino);
		dent_inode = ntfs_iget(vol->sb, dent_ino);
		अगर (!IS_ERR(dent_inode)) अणु
			/* Consistency check. */
			अगर (is_bad_inode(dent_inode) || MSEQNO(mref) ==
					NTFS_I(dent_inode)->seq_no ||
					dent_ino == खाता_MFT) अणु
				/* Perfect WIN32/POSIX match. -- Case 1. */
				अगर (!name) अणु
					ntfs_debug("Done.  (Case 1.)");
					वापस d_splice_alias(dent_inode, dent);
				पूर्ण
				/*
				 * We are too indented.  Handle imperfect
				 * matches and लघु file names further below.
				 */
				जाओ handle_name;
			पूर्ण
			ntfs_error(vol->sb, "Found stale reference to inode "
					"0x%lx (reference sequence number = "
					"0x%x, inode sequence number = 0x%x), "
					"returning -EIO. Run chkdsk.",
					dent_ino, MSEQNO(mref),
					NTFS_I(dent_inode)->seq_no);
			iput(dent_inode);
			dent_inode = ERR_PTR(-EIO);
		पूर्ण अन्यथा
			ntfs_error(vol->sb, "ntfs_iget(0x%lx) failed with "
					"error code %li.", dent_ino,
					PTR_ERR(dent_inode));
		kमुक्त(name);
		/* Return the error code. */
		वापस ERR_CAST(dent_inode);
	पूर्ण
	/* It is guaranteed that @name is no दीर्घer allocated at this poपूर्णांक. */
	अगर (MREF_ERR(mref) == -ENOENT) अणु
		ntfs_debug("Entry was not found, adding negative dentry.");
		/* The dcache will handle negative entries. */
		d_add(dent, शून्य);
		ntfs_debug("Done.");
		वापस शून्य;
	पूर्ण
	ntfs_error(vol->sb, "ntfs_lookup_ino_by_name() failed with error "
			"code %i.", -MREF_ERR(mref));
	वापस ERR_PTR(MREF_ERR(mref));
	// TODO: Consider moving this lot to a separate function! (AIA)
handle_name:
   अणु
	MFT_RECORD *m;
	ntfs_attr_search_ctx *ctx;
	ntfs_inode *ni = NTFS_I(dent_inode);
	पूर्णांक err;
	काष्ठा qstr nls_name;

	nls_name.name = शून्य;
	अगर (name->type != खाता_NAME_DOS) अणु			/* Case 2. */
		ntfs_debug("Case 2.");
		nls_name.len = (अचिन्हित)ntfs_ucstonls(vol,
				(ntfsअक्षर*)&name->name, name->len,
				(अचिन्हित अक्षर**)&nls_name.name, 0);
		kमुक्त(name);
	पूर्ण अन्यथा /* अगर (name->type == खाता_NAME_DOS) */ अणु		/* Case 3. */
		खाता_NAME_ATTR *fn;

		ntfs_debug("Case 3.");
		kमुक्त(name);

		/* Find the WIN32 name corresponding to the matched DOS name. */
		ni = NTFS_I(dent_inode);
		m = map_mft_record(ni);
		अगर (IS_ERR(m)) अणु
			err = PTR_ERR(m);
			m = शून्य;
			ctx = शून्य;
			जाओ err_out;
		पूर्ण
		ctx = ntfs_attr_get_search_ctx(ni, m);
		अगर (unlikely(!ctx)) अणु
			err = -ENOMEM;
			जाओ err_out;
		पूर्ण
		करो अणु
			ATTR_RECORD *a;
			u32 val_len;

			err = ntfs_attr_lookup(AT_खाता_NAME, शून्य, 0, 0, 0,
					शून्य, 0, ctx);
			अगर (unlikely(err)) अणु
				ntfs_error(vol->sb, "Inode corrupt: No WIN32 "
						"namespace counterpart to DOS "
						"file name. Run chkdsk.");
				अगर (err == -ENOENT)
					err = -EIO;
				जाओ err_out;
			पूर्ण
			/* Consistency checks. */
			a = ctx->attr;
			अगर (a->non_resident || a->flags)
				जाओ eio_err_out;
			val_len = le32_to_cpu(a->data.resident.value_length);
			अगर (le16_to_cpu(a->data.resident.value_offset) +
					val_len > le32_to_cpu(a->length))
				जाओ eio_err_out;
			fn = (खाता_NAME_ATTR*)((u8*)ctx->attr + le16_to_cpu(
					ctx->attr->data.resident.value_offset));
			अगर ((u32)(fn->file_name_length * माप(ntfsअक्षर) +
					माप(खाता_NAME_ATTR)) > val_len)
				जाओ eio_err_out;
		पूर्ण जबतक (fn->file_name_type != खाता_NAME_WIN32);

		/* Convert the found WIN32 name to current NLS code page. */
		nls_name.len = (अचिन्हित)ntfs_ucstonls(vol,
				(ntfsअक्षर*)&fn->file_name, fn->file_name_length,
				(अचिन्हित अक्षर**)&nls_name.name, 0);

		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(ni);
	पूर्ण
	m = शून्य;
	ctx = शून्य;

	/* Check अगर a conversion error occurred. */
	अगर ((चिन्हित)nls_name.len < 0) अणु
		err = (चिन्हित)nls_name.len;
		जाओ err_out;
	पूर्ण
	nls_name.hash = full_name_hash(dent, nls_name.name, nls_name.len);

	dent = d_add_ci(dent, dent_inode, &nls_name);
	kमुक्त(nls_name.name);
	वापस dent;

eio_err_out:
	ntfs_error(vol->sb, "Illegal file name attribute. Run chkdsk.");
	err = -EIO;
err_out:
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(ni);
	iput(dent_inode);
	ntfs_error(vol->sb, "Failed, returning error code %i.", err);
	वापस ERR_PTR(err);
   पूर्ण
पूर्ण

/**
 * Inode operations क्रम directories.
 */
स्थिर काष्ठा inode_operations ntfs_dir_inode_ops = अणु
	.lookup	= ntfs_lookup,	/* VFS: Lookup directory. */
पूर्ण;

/**
 * ntfs_get_parent - find the dentry of the parent of a given directory dentry
 * @child_dent:		dentry of the directory whose parent directory to find
 *
 * Find the dentry क्रम the parent directory of the directory specअगरied by the
 * dentry @child_dent.  This function is called from
 * fs/exportfs/expfs.c::find_exported_dentry() which in turn is called from the
 * शेष ->decode_fh() which is export_decode_fh() in the same file.
 *
 * The code is based on the ext3 ->get_parent() implementation found in
 * fs/ext3/namei.c::ext3_get_parent().
 *
 * Note: ntfs_get_parent() is called with @d_inode(child_dent)->i_mutex करोwn.
 *
 * Return the dentry of the parent directory on success or the error code on
 * error (IS_ERR() is true).
 */
अटल काष्ठा dentry *ntfs_get_parent(काष्ठा dentry *child_dent)
अणु
	काष्ठा inode *vi = d_inode(child_dent);
	ntfs_inode *ni = NTFS_I(vi);
	MFT_RECORD *mrec;
	ntfs_attr_search_ctx *ctx;
	ATTR_RECORD *attr;
	खाता_NAME_ATTR *fn;
	अचिन्हित दीर्घ parent_ino;
	पूर्णांक err;

	ntfs_debug("Entering for inode 0x%lx.", vi->i_ino);
	/* Get the mft record of the inode beदीर्घing to the child dentry. */
	mrec = map_mft_record(ni);
	अगर (IS_ERR(mrec))
		वापस ERR_CAST(mrec);
	/* Find the first file name attribute in the mft record. */
	ctx = ntfs_attr_get_search_ctx(ni, mrec);
	अगर (unlikely(!ctx)) अणु
		unmap_mft_record(ni);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
try_next:
	err = ntfs_attr_lookup(AT_खाता_NAME, शून्य, 0, CASE_SENSITIVE, 0, शून्य,
			0, ctx);
	अगर (unlikely(err)) अणु
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(ni);
		अगर (err == -ENOENT)
			ntfs_error(vi->i_sb, "Inode 0x%lx does not have a "
					"file name attribute.  Run chkdsk.",
					vi->i_ino);
		वापस ERR_PTR(err);
	पूर्ण
	attr = ctx->attr;
	अगर (unlikely(attr->non_resident))
		जाओ try_next;
	fn = (खाता_NAME_ATTR *)((u8 *)attr +
			le16_to_cpu(attr->data.resident.value_offset));
	अगर (unlikely((u8 *)fn + le32_to_cpu(attr->data.resident.value_length) >
			(u8*)attr + le32_to_cpu(attr->length)))
		जाओ try_next;
	/* Get the inode number of the parent directory. */
	parent_ino = MREF_LE(fn->parent_directory);
	/* Release the search context and the mft record of the child. */
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(ni);

	वापस d_obtain_alias(ntfs_iget(vi->i_sb, parent_ino));
पूर्ण

अटल काष्ठा inode *ntfs_nfs_get_inode(काष्ठा super_block *sb,
		u64 ino, u32 generation)
अणु
	काष्ठा inode *inode;

	inode = ntfs_iget(sb, ino);
	अगर (!IS_ERR(inode)) अणु
		अगर (is_bad_inode(inode) || inode->i_generation != generation) अणु
			iput(inode);
			inode = ERR_PTR(-ESTALE);
		पूर्ण
	पूर्ण

	वापस inode;
पूर्ण

अटल काष्ठा dentry *ntfs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_dentry(sb, fid, fh_len, fh_type,
				    ntfs_nfs_get_inode);
पूर्ण

अटल काष्ठा dentry *ntfs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_parent(sb, fid, fh_len, fh_type,
				    ntfs_nfs_get_inode);
पूर्ण

/**
 * Export operations allowing NFS exporting of mounted NTFS partitions.
 *
 * We use the शेष ->encode_fh() क्रम now.  Note that they
 * use 32 bits to store the inode number which is an अचिन्हित दीर्घ so on 64-bit
 * architectures is usually 64 bits so it would all fail horribly on huge
 * volumes.  I guess we need to define our own encode and decode fh functions
 * that store 64-bit inode numbers at some poपूर्णांक but क्रम now we will ignore the
 * problem...
 *
 * We also use the शेष ->get_name() helper (used by ->decode_fh() via
 * fs/exportfs/expfs.c::find_exported_dentry()) as that is completely fs
 * independent.
 *
 * The शेष ->get_parent() just वापसs -EACCES so we have to provide our
 * own and the शेष ->get_dentry() is incompatible with NTFS due to not
 * allowing the inode number 0 which is used in NTFS क्रम the प्रणाली file $MFT
 * and due to using iget() whereas NTFS needs ntfs_iget().
 */
स्थिर काष्ठा export_operations ntfs_export_ops = अणु
	.get_parent	= ntfs_get_parent,	/* Find the parent of a given
						   directory. */
	.fh_to_dentry	= ntfs_fh_to_dentry,
	.fh_to_parent	= ntfs_fh_to_parent,
पूर्ण;
