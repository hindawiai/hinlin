<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**
 * dir.c - NTFS kernel directory operations. Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2007 Anton Altaparmakov
 * Copyright (c) 2002 Riअक्षरd Russon
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>

#समावेश "dir.h"
#समावेश "aops.h"
#समावेश "attrib.h"
#समावेश "mft.h"
#समावेश "debug.h"
#समावेश "ntfs.h"

/**
 * The little endian Unicode string $I30 as a global स्थिरant.
 */
ntfsअक्षर I30[5] = अणु cpu_to_le16('$'), cpu_to_le16('I'),
		cpu_to_le16('3'),	cpu_to_le16('0'), 0 पूर्ण;

/**
 * ntfs_lookup_inode_by_name - find an inode in a directory given its name
 * @dir_ni:	ntfs inode of the directory in which to search क्रम the name
 * @uname:	Unicode name क्रम which to search in the directory
 * @uname_len:	length of the name @uname in Unicode अक्षरacters
 * @res:	वापस the found file name अगर necessary (see below)
 *
 * Look क्रम an inode with name @uname in the directory with inode @dir_ni.
 * ntfs_lookup_inode_by_name() walks the contents of the directory looking क्रम
 * the Unicode name. If the name is found in the directory, the corresponding
 * inode number (>= 0) is वापसed as a mft reference in cpu क्रमmat, i.e. it
 * is a 64-bit number containing the sequence number.
 *
 * On error, a negative value is वापसed corresponding to the error code. In
 * particular अगर the inode is not found -ENOENT is वापसed. Note that you
 * can't just check the वापस value क्रम being negative, you have to check the
 * inode number क्रम being negative which you can extract using MREC(वापस
 * value).
 *
 * Note, @uname_len करोes not include the (optional) terminating शून्य अक्षरacter.
 *
 * Note, we look क्रम a हाल sensitive match first but we also look क्रम a हाल
 * insensitive match at the same समय. If we find a हाल insensitive match, we
 * save that क्रम the हाल that we करोn't find an exact match, where we वापस
 * the हाल insensitive match and setup @res (which we allocate!) with the mft
 * reference, the file name type, length and with a copy of the little endian
 * Unicode file name itself. If we match a file name which is in the DOS name
 * space, we only वापस the mft reference and file name type in @res.
 * ntfs_lookup() then uses this to find the दीर्घ file name in the inode itself.
 * This is to aव्योम polluting the dcache with लघु file names. We want them to
 * work but we करोn't care क्रम how quickly one can access them. This also fixes
 * the dcache aliasing issues.
 *
 * Locking:  - Caller must hold i_mutex on the directory.
 *	     - Each page cache page in the index allocation mapping must be
 *	       locked whilst being accessed otherwise we may find a corrupt
 *	       page due to it being under ->ग_लिखोpage at the moment which
 *	       applies the mst protection fixups beक्रमe writing out and then
 *	       हटाओs them again after the ग_लिखो is complete after which it 
 *	       unlocks the page.
 */
MFT_REF ntfs_lookup_inode_by_name(ntfs_inode *dir_ni, स्थिर ntfsअक्षर *uname,
		स्थिर पूर्णांक uname_len, ntfs_name **res)
अणु
	ntfs_volume *vol = dir_ni->vol;
	काष्ठा super_block *sb = vol->sb;
	MFT_RECORD *m;
	INDEX_ROOT *ir;
	INDEX_ENTRY *ie;
	INDEX_ALLOCATION *ia;
	u8 *index_end;
	u64 mref;
	ntfs_attr_search_ctx *ctx;
	पूर्णांक err, rc;
	VCN vcn, old_vcn;
	काष्ठा address_space *ia_mapping;
	काष्ठा page *page;
	u8 *kaddr;
	ntfs_name *name = शून्य;

	BUG_ON(!S_ISसूची(VFS_I(dir_ni)->i_mode));
	BUG_ON(NInoAttr(dir_ni));
	/* Get hold of the mft record क्रम the directory. */
	m = map_mft_record(dir_ni);
	अगर (IS_ERR(m)) अणु
		ntfs_error(sb, "map_mft_record() failed with error code %ld.",
				-PTR_ERR(m));
		वापस ERR_MREF(PTR_ERR(m));
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(dir_ni, m);
	अगर (unlikely(!ctx)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	/* Find the index root attribute in the mft record. */
	err = ntfs_attr_lookup(AT_INDEX_ROOT, I30, 4, CASE_SENSITIVE, 0, शून्य,
			0, ctx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT) अणु
			ntfs_error(sb, "Index root attribute missing in "
					"directory inode 0x%lx.",
					dir_ni->mft_no);
			err = -EIO;
		पूर्ण
		जाओ err_out;
	पूर्ण
	/* Get to the index root value (it's been verअगरied in पढ़ो_inode). */
	ir = (INDEX_ROOT*)((u8*)ctx->attr +
			le16_to_cpu(ctx->attr->data.resident.value_offset));
	index_end = (u8*)&ir->index + le32_to_cpu(ir->index.index_length);
	/* The first index entry. */
	ie = (INDEX_ENTRY*)((u8*)&ir->index +
			le32_to_cpu(ir->index.entries_offset));
	/*
	 * Loop until we exceed valid memory (corruption हाल) or until we
	 * reach the last entry.
	 */
	क्रम (;; ie = (INDEX_ENTRY*)((u8*)ie + le16_to_cpu(ie->length))) अणु
		/* Bounds checks. */
		अगर ((u8*)ie < (u8*)ctx->mrec || (u8*)ie +
				माप(INDEX_ENTRY_HEADER) > index_end ||
				(u8*)ie + le16_to_cpu(ie->key_length) >
				index_end)
			जाओ dir_err_out;
		/*
		 * The last entry cannot contain a name. It can however contain
		 * a poपूर्णांकer to a child node in the B+tree so we just अवरोध out.
		 */
		अगर (ie->flags & INDEX_ENTRY_END)
			अवरोध;
		/*
		 * We perक्रमm a हाल sensitive comparison and अगर that matches
		 * we are करोne and वापस the mft reference of the inode (i.e.
		 * the inode number together with the sequence number क्रम
		 * consistency checking). We convert it to cpu क्रमmat beक्रमe
		 * वापसing.
		 */
		अगर (ntfs_are_names_equal(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length,
				CASE_SENSITIVE, vol->upहाल, vol->upहाल_len)) अणु
found_it:
			/*
			 * We have a perfect match, so we करोn't need to care
			 * about having matched imperfectly beक्रमe, so we can
			 * मुक्त name and set *res to शून्य.
			 * However, अगर the perfect match is a लघु file name,
			 * we need to संकेत this through *res, so that
			 * ntfs_lookup() can fix dcache aliasing issues.
			 * As an optimization we just reuse an existing
			 * allocation of *res.
			 */
			अगर (ie->key.file_name.file_name_type == खाता_NAME_DOS) अणु
				अगर (!name) अणु
					name = kदो_स्मृति(माप(ntfs_name),
							GFP_NOFS);
					अगर (!name) अणु
						err = -ENOMEM;
						जाओ err_out;
					पूर्ण
				पूर्ण
				name->mref = le64_to_cpu(
						ie->data.dir.indexed_file);
				name->type = खाता_NAME_DOS;
				name->len = 0;
				*res = name;
			पूर्ण अन्यथा अणु
				kमुक्त(name);
				*res = शून्य;
			पूर्ण
			mref = le64_to_cpu(ie->data.dir.indexed_file);
			ntfs_attr_put_search_ctx(ctx);
			unmap_mft_record(dir_ni);
			वापस mref;
		पूर्ण
		/*
		 * For a हाल insensitive mount, we also perक्रमm a हाल
		 * insensitive comparison (provided the file name is not in the
		 * POSIX namespace). If the comparison matches, and the name is
		 * in the WIN32 namespace, we cache the filename in *res so
		 * that the caller, ntfs_lookup(), can work on it. If the
		 * comparison matches, and the name is in the DOS namespace, we
		 * only cache the mft reference and the file name type (we set
		 * the name length to zero क्रम simplicity).
		 */
		अगर (!NVolCaseSensitive(vol) &&
				ie->key.file_name.file_name_type &&
				ntfs_are_names_equal(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length,
				IGNORE_CASE, vol->upहाल, vol->upहाल_len)) अणु
			पूर्णांक name_size = माप(ntfs_name);
			u8 type = ie->key.file_name.file_name_type;
			u8 len = ie->key.file_name.file_name_length;

			/* Only one हाल insensitive matching name allowed. */
			अगर (name) अणु
				ntfs_error(sb, "Found already allocated name "
						"in phase 1. Please run chkdsk "
						"and if that doesn't find any "
						"errors please report you saw "
						"this message to "
						"linux-ntfs-dev@lists."
						"sourceforge.net.");
				जाओ dir_err_out;
			पूर्ण

			अगर (type != खाता_NAME_DOS)
				name_size += len * माप(ntfsअक्षर);
			name = kदो_स्मृति(name_size, GFP_NOFS);
			अगर (!name) अणु
				err = -ENOMEM;
				जाओ err_out;
			पूर्ण
			name->mref = le64_to_cpu(ie->data.dir.indexed_file);
			name->type = type;
			अगर (type != खाता_NAME_DOS) अणु
				name->len = len;
				स_नकल(name->name, ie->key.file_name.file_name,
						len * माप(ntfsअक्षर));
			पूर्ण अन्यथा
				name->len = 0;
			*res = name;
		पूर्ण
		/*
		 * Not a perfect match, need to करो full blown collation so we
		 * know which way in the B+tree we have to go.
		 */
		rc = ntfs_collate_names(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length, 1,
				IGNORE_CASE, vol->upहाल, vol->upहाल_len);
		/*
		 * If uname collates beक्रमe the name of the current entry, there
		 * is definitely no such name in this index but we might need to
		 * descend पूर्णांकo the B+tree so we just अवरोध out of the loop.
		 */
		अगर (rc == -1)
			अवरोध;
		/* The names are not equal, जारी the search. */
		अगर (rc)
			जारी;
		/*
		 * Names match with हाल insensitive comparison, now try the
		 * हाल sensitive comparison, which is required क्रम proper
		 * collation.
		 */
		rc = ntfs_collate_names(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length, 1,
				CASE_SENSITIVE, vol->upहाल, vol->upहाल_len);
		अगर (rc == -1)
			अवरोध;
		अगर (rc)
			जारी;
		/*
		 * Perfect match, this will never happen as the
		 * ntfs_are_names_equal() call will have gotten a match but we
		 * still treat it correctly.
		 */
		जाओ found_it;
	पूर्ण
	/*
	 * We have finished with this index without success. Check क्रम the
	 * presence of a child node and अगर not present वापस -ENOENT, unless
	 * we have got a matching name cached in name in which हाल वापस the
	 * mft reference associated with it.
	 */
	अगर (!(ie->flags & INDEX_ENTRY_NODE)) अणु
		अगर (name) अणु
			ntfs_attr_put_search_ctx(ctx);
			unmap_mft_record(dir_ni);
			वापस name->mref;
		पूर्ण
		ntfs_debug("Entry not found.");
		err = -ENOENT;
		जाओ err_out;
	पूर्ण /* Child node present, descend पूर्णांकo it. */
	/* Consistency check: Verअगरy that an index allocation exists. */
	अगर (!NInoIndexAllocPresent(dir_ni)) अणु
		ntfs_error(sb, "No index allocation attribute but index entry "
				"requires one. Directory inode 0x%lx is "
				"corrupt or driver bug.", dir_ni->mft_no);
		जाओ err_out;
	पूर्ण
	/* Get the starting vcn of the index_block holding the child node. */
	vcn = sle64_to_cpup((sle64*)((u8*)ie + le16_to_cpu(ie->length) - 8));
	ia_mapping = VFS_I(dir_ni)->i_mapping;
	/*
	 * We are करोne with the index root and the mft record. Release them,
	 * otherwise we deadlock with ntfs_map_page().
	 */
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(dir_ni);
	m = शून्य;
	ctx = शून्य;
descend_पूर्णांकo_child_node:
	/*
	 * Convert vcn to index पूर्णांकo the index allocation attribute in units
	 * of PAGE_SIZE and map the page cache page, पढ़ोing it from
	 * disk अगर necessary.
	 */
	page = ntfs_map_page(ia_mapping, vcn <<
			dir_ni->itype.index.vcn_size_bits >> PAGE_SHIFT);
	अगर (IS_ERR(page)) अणु
		ntfs_error(sb, "Failed to map directory index page, error %ld.",
				-PTR_ERR(page));
		err = PTR_ERR(page);
		जाओ err_out;
	पूर्ण
	lock_page(page);
	kaddr = (u8*)page_address(page);
fast_descend_पूर्णांकo_child_node:
	/* Get to the index allocation block. */
	ia = (INDEX_ALLOCATION*)(kaddr + ((vcn <<
			dir_ni->itype.index.vcn_size_bits) & ~PAGE_MASK));
	/* Bounds checks. */
	अगर ((u8*)ia < kaddr || (u8*)ia > kaddr + PAGE_SIZE) अणु
		ntfs_error(sb, "Out of bounds check failed. Corrupt directory "
				"inode 0x%lx or driver bug.", dir_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	/* Catch multi sector transfer fixup errors. */
	अगर (unlikely(!ntfs_is_indx_record(ia->magic))) अणु
		ntfs_error(sb, "Directory index record with vcn 0x%llx is "
				"corrupt.  Corrupt inode 0x%lx.  Run chkdsk.",
				(अचिन्हित दीर्घ दीर्घ)vcn, dir_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	अगर (sle64_to_cpu(ia->index_block_vcn) != vcn) अणु
		ntfs_error(sb, "Actual VCN (0x%llx) of index buffer is "
				"different from expected VCN (0x%llx). "
				"Directory inode 0x%lx is corrupt or driver "
				"bug.", (अचिन्हित दीर्घ दीर्घ)
				sle64_to_cpu(ia->index_block_vcn),
				(अचिन्हित दीर्घ दीर्घ)vcn, dir_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	अगर (le32_to_cpu(ia->index.allocated_size) + 0x18 !=
			dir_ni->itype.index.block_size) अणु
		ntfs_error(sb, "Index buffer (VCN 0x%llx) of directory inode "
				"0x%lx has a size (%u) differing from the "
				"directory specified size (%u). Directory "
				"inode is corrupt or driver bug.",
				(अचिन्हित दीर्घ दीर्घ)vcn, dir_ni->mft_no,
				le32_to_cpu(ia->index.allocated_size) + 0x18,
				dir_ni->itype.index.block_size);
		जाओ unm_err_out;
	पूर्ण
	index_end = (u8*)ia + dir_ni->itype.index.block_size;
	अगर (index_end > kaddr + PAGE_SIZE) अणु
		ntfs_error(sb, "Index buffer (VCN 0x%llx) of directory inode "
				"0x%lx crosses page boundary. Impossible! "
				"Cannot access! This is probably a bug in the "
				"driver.", (अचिन्हित दीर्घ दीर्घ)vcn,
				dir_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	index_end = (u8*)&ia->index + le32_to_cpu(ia->index.index_length);
	अगर (index_end > (u8*)ia + dir_ni->itype.index.block_size) अणु
		ntfs_error(sb, "Size of index buffer (VCN 0x%llx) of directory "
				"inode 0x%lx exceeds maximum size.",
				(अचिन्हित दीर्घ दीर्घ)vcn, dir_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	/* The first index entry. */
	ie = (INDEX_ENTRY*)((u8*)&ia->index +
			le32_to_cpu(ia->index.entries_offset));
	/*
	 * Iterate similar to above big loop but applied to index buffer, thus
	 * loop until we exceed valid memory (corruption हाल) or until we
	 * reach the last entry.
	 */
	क्रम (;; ie = (INDEX_ENTRY*)((u8*)ie + le16_to_cpu(ie->length))) अणु
		/* Bounds check. */
		अगर ((u8*)ie < (u8*)ia || (u8*)ie +
				माप(INDEX_ENTRY_HEADER) > index_end ||
				(u8*)ie + le16_to_cpu(ie->key_length) >
				index_end) अणु
			ntfs_error(sb, "Index entry out of bounds in "
					"directory inode 0x%lx.",
					dir_ni->mft_no);
			जाओ unm_err_out;
		पूर्ण
		/*
		 * The last entry cannot contain a name. It can however contain
		 * a poपूर्णांकer to a child node in the B+tree so we just अवरोध out.
		 */
		अगर (ie->flags & INDEX_ENTRY_END)
			अवरोध;
		/*
		 * We perक्रमm a हाल sensitive comparison and अगर that matches
		 * we are करोne and वापस the mft reference of the inode (i.e.
		 * the inode number together with the sequence number क्रम
		 * consistency checking). We convert it to cpu क्रमmat beक्रमe
		 * वापसing.
		 */
		अगर (ntfs_are_names_equal(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length,
				CASE_SENSITIVE, vol->upहाल, vol->upहाल_len)) अणु
found_it2:
			/*
			 * We have a perfect match, so we करोn't need to care
			 * about having matched imperfectly beक्रमe, so we can
			 * मुक्त name and set *res to शून्य.
			 * However, अगर the perfect match is a लघु file name,
			 * we need to संकेत this through *res, so that
			 * ntfs_lookup() can fix dcache aliasing issues.
			 * As an optimization we just reuse an existing
			 * allocation of *res.
			 */
			अगर (ie->key.file_name.file_name_type == खाता_NAME_DOS) अणु
				अगर (!name) अणु
					name = kदो_स्मृति(माप(ntfs_name),
							GFP_NOFS);
					अगर (!name) अणु
						err = -ENOMEM;
						जाओ unm_err_out;
					पूर्ण
				पूर्ण
				name->mref = le64_to_cpu(
						ie->data.dir.indexed_file);
				name->type = खाता_NAME_DOS;
				name->len = 0;
				*res = name;
			पूर्ण अन्यथा अणु
				kमुक्त(name);
				*res = शून्य;
			पूर्ण
			mref = le64_to_cpu(ie->data.dir.indexed_file);
			unlock_page(page);
			ntfs_unmap_page(page);
			वापस mref;
		पूर्ण
		/*
		 * For a हाल insensitive mount, we also perक्रमm a हाल
		 * insensitive comparison (provided the file name is not in the
		 * POSIX namespace). If the comparison matches, and the name is
		 * in the WIN32 namespace, we cache the filename in *res so
		 * that the caller, ntfs_lookup(), can work on it. If the
		 * comparison matches, and the name is in the DOS namespace, we
		 * only cache the mft reference and the file name type (we set
		 * the name length to zero क्रम simplicity).
		 */
		अगर (!NVolCaseSensitive(vol) &&
				ie->key.file_name.file_name_type &&
				ntfs_are_names_equal(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length,
				IGNORE_CASE, vol->upहाल, vol->upहाल_len)) अणु
			पूर्णांक name_size = माप(ntfs_name);
			u8 type = ie->key.file_name.file_name_type;
			u8 len = ie->key.file_name.file_name_length;

			/* Only one हाल insensitive matching name allowed. */
			अगर (name) अणु
				ntfs_error(sb, "Found already allocated name "
						"in phase 2. Please run chkdsk "
						"and if that doesn't find any "
						"errors please report you saw "
						"this message to "
						"linux-ntfs-dev@lists."
						"sourceforge.net.");
				unlock_page(page);
				ntfs_unmap_page(page);
				जाओ dir_err_out;
			पूर्ण

			अगर (type != खाता_NAME_DOS)
				name_size += len * माप(ntfsअक्षर);
			name = kदो_स्मृति(name_size, GFP_NOFS);
			अगर (!name) अणु
				err = -ENOMEM;
				जाओ unm_err_out;
			पूर्ण
			name->mref = le64_to_cpu(ie->data.dir.indexed_file);
			name->type = type;
			अगर (type != खाता_NAME_DOS) अणु
				name->len = len;
				स_नकल(name->name, ie->key.file_name.file_name,
						len * माप(ntfsअक्षर));
			पूर्ण अन्यथा
				name->len = 0;
			*res = name;
		पूर्ण
		/*
		 * Not a perfect match, need to करो full blown collation so we
		 * know which way in the B+tree we have to go.
		 */
		rc = ntfs_collate_names(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length, 1,
				IGNORE_CASE, vol->upहाल, vol->upहाल_len);
		/*
		 * If uname collates beक्रमe the name of the current entry, there
		 * is definitely no such name in this index but we might need to
		 * descend पूर्णांकo the B+tree so we just अवरोध out of the loop.
		 */
		अगर (rc == -1)
			अवरोध;
		/* The names are not equal, जारी the search. */
		अगर (rc)
			जारी;
		/*
		 * Names match with हाल insensitive comparison, now try the
		 * हाल sensitive comparison, which is required क्रम proper
		 * collation.
		 */
		rc = ntfs_collate_names(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length, 1,
				CASE_SENSITIVE, vol->upहाल, vol->upहाल_len);
		अगर (rc == -1)
			अवरोध;
		अगर (rc)
			जारी;
		/*
		 * Perfect match, this will never happen as the
		 * ntfs_are_names_equal() call will have gotten a match but we
		 * still treat it correctly.
		 */
		जाओ found_it2;
	पूर्ण
	/*
	 * We have finished with this index buffer without success. Check क्रम
	 * the presence of a child node.
	 */
	अगर (ie->flags & INDEX_ENTRY_NODE) अणु
		अगर ((ia->index.flags & NODE_MASK) == LEAF_NODE) अणु
			ntfs_error(sb, "Index entry with child node found in "
					"a leaf node in directory inode 0x%lx.",
					dir_ni->mft_no);
			जाओ unm_err_out;
		पूर्ण
		/* Child node present, descend पूर्णांकo it. */
		old_vcn = vcn;
		vcn = sle64_to_cpup((sle64*)((u8*)ie +
				le16_to_cpu(ie->length) - 8));
		अगर (vcn >= 0) अणु
			/* If vcn is in the same page cache page as old_vcn we
			 * recycle the mapped page. */
			अगर (old_vcn << vol->cluster_size_bits >>
					PAGE_SHIFT == vcn <<
					vol->cluster_size_bits >>
					PAGE_SHIFT)
				जाओ fast_descend_पूर्णांकo_child_node;
			unlock_page(page);
			ntfs_unmap_page(page);
			जाओ descend_पूर्णांकo_child_node;
		पूर्ण
		ntfs_error(sb, "Negative child node vcn in directory inode "
				"0x%lx.", dir_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	/*
	 * No child node present, वापस -ENOENT, unless we have got a matching
	 * name cached in name in which हाल वापस the mft reference
	 * associated with it.
	 */
	अगर (name) अणु
		unlock_page(page);
		ntfs_unmap_page(page);
		वापस name->mref;
	पूर्ण
	ntfs_debug("Entry not found.");
	err = -ENOENT;
unm_err_out:
	unlock_page(page);
	ntfs_unmap_page(page);
err_out:
	अगर (!err)
		err = -EIO;
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(dir_ni);
	अगर (name) अणु
		kमुक्त(name);
		*res = शून्य;
	पूर्ण
	वापस ERR_MREF(err);
dir_err_out:
	ntfs_error(sb, "Corrupt directory.  Aborting lookup.");
	जाओ err_out;
पूर्ण

#अगर 0

// TODO: (AIA)
// The algorithm embedded in this code will be required क्रम the समय when we
// want to support adding of entries to directories, where we require correct
// collation of file names in order not to cause corruption of the fileप्रणाली.

/**
 * ntfs_lookup_inode_by_name - find an inode in a directory given its name
 * @dir_ni:	ntfs inode of the directory in which to search क्रम the name
 * @uname:	Unicode name क्रम which to search in the directory
 * @uname_len:	length of the name @uname in Unicode अक्षरacters
 *
 * Look क्रम an inode with name @uname in the directory with inode @dir_ni.
 * ntfs_lookup_inode_by_name() walks the contents of the directory looking क्रम
 * the Unicode name. If the name is found in the directory, the corresponding
 * inode number (>= 0) is वापसed as a mft reference in cpu क्रमmat, i.e. it
 * is a 64-bit number containing the sequence number.
 *
 * On error, a negative value is वापसed corresponding to the error code. In
 * particular अगर the inode is not found -ENOENT is वापसed. Note that you
 * can't just check the वापस value क्रम being negative, you have to check the
 * inode number क्रम being negative which you can extract using MREC(वापस
 * value).
 *
 * Note, @uname_len करोes not include the (optional) terminating शून्य अक्षरacter.
 */
u64 ntfs_lookup_inode_by_name(ntfs_inode *dir_ni, स्थिर ntfsअक्षर *uname,
		स्थिर पूर्णांक uname_len)
अणु
	ntfs_volume *vol = dir_ni->vol;
	काष्ठा super_block *sb = vol->sb;
	MFT_RECORD *m;
	INDEX_ROOT *ir;
	INDEX_ENTRY *ie;
	INDEX_ALLOCATION *ia;
	u8 *index_end;
	u64 mref;
	ntfs_attr_search_ctx *ctx;
	पूर्णांक err, rc;
	IGNORE_CASE_BOOL ic;
	VCN vcn, old_vcn;
	काष्ठा address_space *ia_mapping;
	काष्ठा page *page;
	u8 *kaddr;

	/* Get hold of the mft record क्रम the directory. */
	m = map_mft_record(dir_ni);
	अगर (IS_ERR(m)) अणु
		ntfs_error(sb, "map_mft_record() failed with error code %ld.",
				-PTR_ERR(m));
		वापस ERR_MREF(PTR_ERR(m));
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(dir_ni, m);
	अगर (!ctx) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	/* Find the index root attribute in the mft record. */
	err = ntfs_attr_lookup(AT_INDEX_ROOT, I30, 4, CASE_SENSITIVE, 0, शून्य,
			0, ctx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT) अणु
			ntfs_error(sb, "Index root attribute missing in "
					"directory inode 0x%lx.",
					dir_ni->mft_no);
			err = -EIO;
		पूर्ण
		जाओ err_out;
	पूर्ण
	/* Get to the index root value (it's been verअगरied in पढ़ो_inode). */
	ir = (INDEX_ROOT*)((u8*)ctx->attr +
			le16_to_cpu(ctx->attr->data.resident.value_offset));
	index_end = (u8*)&ir->index + le32_to_cpu(ir->index.index_length);
	/* The first index entry. */
	ie = (INDEX_ENTRY*)((u8*)&ir->index +
			le32_to_cpu(ir->index.entries_offset));
	/*
	 * Loop until we exceed valid memory (corruption हाल) or until we
	 * reach the last entry.
	 */
	क्रम (;; ie = (INDEX_ENTRY*)((u8*)ie + le16_to_cpu(ie->length))) अणु
		/* Bounds checks. */
		अगर ((u8*)ie < (u8*)ctx->mrec || (u8*)ie +
				माप(INDEX_ENTRY_HEADER) > index_end ||
				(u8*)ie + le16_to_cpu(ie->key_length) >
				index_end)
			जाओ dir_err_out;
		/*
		 * The last entry cannot contain a name. It can however contain
		 * a poपूर्णांकer to a child node in the B+tree so we just अवरोध out.
		 */
		अगर (ie->flags & INDEX_ENTRY_END)
			अवरोध;
		/*
		 * If the current entry has a name type of POSIX, the name is
		 * हाल sensitive and not otherwise. This has the effect of us
		 * not being able to access any POSIX file names which collate
		 * after the non-POSIX one when they only dअगरfer in हाल, but
		 * anyone करोing screwy stuff like that deserves to burn in
		 * hell... Doing that kind of stuff on NT4 actually causes
		 * corruption on the partition even when using SP6a and Linux
		 * is not involved at all.
		 */
		ic = ie->key.file_name.file_name_type ? IGNORE_CASE :
				CASE_SENSITIVE;
		/*
		 * If the names match perfectly, we are करोne and वापस the
		 * mft reference of the inode (i.e. the inode number together
		 * with the sequence number क्रम consistency checking. We
		 * convert it to cpu क्रमmat beक्रमe वापसing.
		 */
		अगर (ntfs_are_names_equal(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length, ic,
				vol->upहाल, vol->upहाल_len)) अणु
found_it:
			mref = le64_to_cpu(ie->data.dir.indexed_file);
			ntfs_attr_put_search_ctx(ctx);
			unmap_mft_record(dir_ni);
			वापस mref;
		पूर्ण
		/*
		 * Not a perfect match, need to करो full blown collation so we
		 * know which way in the B+tree we have to go.
		 */
		rc = ntfs_collate_names(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length, 1,
				IGNORE_CASE, vol->upहाल, vol->upहाल_len);
		/*
		 * If uname collates beक्रमe the name of the current entry, there
		 * is definitely no such name in this index but we might need to
		 * descend पूर्णांकo the B+tree so we just अवरोध out of the loop.
		 */
		अगर (rc == -1)
			अवरोध;
		/* The names are not equal, जारी the search. */
		अगर (rc)
			जारी;
		/*
		 * Names match with हाल insensitive comparison, now try the
		 * हाल sensitive comparison, which is required क्रम proper
		 * collation.
		 */
		rc = ntfs_collate_names(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length, 1,
				CASE_SENSITIVE, vol->upहाल, vol->upहाल_len);
		अगर (rc == -1)
			अवरोध;
		अगर (rc)
			जारी;
		/*
		 * Perfect match, this will never happen as the
		 * ntfs_are_names_equal() call will have gotten a match but we
		 * still treat it correctly.
		 */
		जाओ found_it;
	पूर्ण
	/*
	 * We have finished with this index without success. Check क्रम the
	 * presence of a child node.
	 */
	अगर (!(ie->flags & INDEX_ENTRY_NODE)) अणु
		/* No child node, वापस -ENOENT. */
		err = -ENOENT;
		जाओ err_out;
	पूर्ण /* Child node present, descend पूर्णांकo it. */
	/* Consistency check: Verअगरy that an index allocation exists. */
	अगर (!NInoIndexAllocPresent(dir_ni)) अणु
		ntfs_error(sb, "No index allocation attribute but index entry "
				"requires one. Directory inode 0x%lx is "
				"corrupt or driver bug.", dir_ni->mft_no);
		जाओ err_out;
	पूर्ण
	/* Get the starting vcn of the index_block holding the child node. */
	vcn = sle64_to_cpup((u8*)ie + le16_to_cpu(ie->length) - 8);
	ia_mapping = VFS_I(dir_ni)->i_mapping;
	/*
	 * We are करोne with the index root and the mft record. Release them,
	 * otherwise we deadlock with ntfs_map_page().
	 */
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(dir_ni);
	m = शून्य;
	ctx = शून्य;
descend_पूर्णांकo_child_node:
	/*
	 * Convert vcn to index पूर्णांकo the index allocation attribute in units
	 * of PAGE_SIZE and map the page cache page, पढ़ोing it from
	 * disk अगर necessary.
	 */
	page = ntfs_map_page(ia_mapping, vcn <<
			dir_ni->itype.index.vcn_size_bits >> PAGE_SHIFT);
	अगर (IS_ERR(page)) अणु
		ntfs_error(sb, "Failed to map directory index page, error %ld.",
				-PTR_ERR(page));
		err = PTR_ERR(page);
		जाओ err_out;
	पूर्ण
	lock_page(page);
	kaddr = (u8*)page_address(page);
fast_descend_पूर्णांकo_child_node:
	/* Get to the index allocation block. */
	ia = (INDEX_ALLOCATION*)(kaddr + ((vcn <<
			dir_ni->itype.index.vcn_size_bits) & ~PAGE_MASK));
	/* Bounds checks. */
	अगर ((u8*)ia < kaddr || (u8*)ia > kaddr + PAGE_SIZE) अणु
		ntfs_error(sb, "Out of bounds check failed. Corrupt directory "
				"inode 0x%lx or driver bug.", dir_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	/* Catch multi sector transfer fixup errors. */
	अगर (unlikely(!ntfs_is_indx_record(ia->magic))) अणु
		ntfs_error(sb, "Directory index record with vcn 0x%llx is "
				"corrupt.  Corrupt inode 0x%lx.  Run chkdsk.",
				(अचिन्हित दीर्घ दीर्घ)vcn, dir_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	अगर (sle64_to_cpu(ia->index_block_vcn) != vcn) अणु
		ntfs_error(sb, "Actual VCN (0x%llx) of index buffer is "
				"different from expected VCN (0x%llx). "
				"Directory inode 0x%lx is corrupt or driver "
				"bug.", (अचिन्हित दीर्घ दीर्घ)
				sle64_to_cpu(ia->index_block_vcn),
				(अचिन्हित दीर्घ दीर्घ)vcn, dir_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	अगर (le32_to_cpu(ia->index.allocated_size) + 0x18 !=
			dir_ni->itype.index.block_size) अणु
		ntfs_error(sb, "Index buffer (VCN 0x%llx) of directory inode "
				"0x%lx has a size (%u) differing from the "
				"directory specified size (%u). Directory "
				"inode is corrupt or driver bug.",
				(अचिन्हित दीर्घ दीर्घ)vcn, dir_ni->mft_no,
				le32_to_cpu(ia->index.allocated_size) + 0x18,
				dir_ni->itype.index.block_size);
		जाओ unm_err_out;
	पूर्ण
	index_end = (u8*)ia + dir_ni->itype.index.block_size;
	अगर (index_end > kaddr + PAGE_SIZE) अणु
		ntfs_error(sb, "Index buffer (VCN 0x%llx) of directory inode "
				"0x%lx crosses page boundary. Impossible! "
				"Cannot access! This is probably a bug in the "
				"driver.", (अचिन्हित दीर्घ दीर्घ)vcn,
				dir_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	index_end = (u8*)&ia->index + le32_to_cpu(ia->index.index_length);
	अगर (index_end > (u8*)ia + dir_ni->itype.index.block_size) अणु
		ntfs_error(sb, "Size of index buffer (VCN 0x%llx) of directory "
				"inode 0x%lx exceeds maximum size.",
				(अचिन्हित दीर्घ दीर्घ)vcn, dir_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	/* The first index entry. */
	ie = (INDEX_ENTRY*)((u8*)&ia->index +
			le32_to_cpu(ia->index.entries_offset));
	/*
	 * Iterate similar to above big loop but applied to index buffer, thus
	 * loop until we exceed valid memory (corruption हाल) or until we
	 * reach the last entry.
	 */
	क्रम (;; ie = (INDEX_ENTRY*)((u8*)ie + le16_to_cpu(ie->length))) अणु
		/* Bounds check. */
		अगर ((u8*)ie < (u8*)ia || (u8*)ie +
				माप(INDEX_ENTRY_HEADER) > index_end ||
				(u8*)ie + le16_to_cpu(ie->key_length) >
				index_end) अणु
			ntfs_error(sb, "Index entry out of bounds in "
					"directory inode 0x%lx.",
					dir_ni->mft_no);
			जाओ unm_err_out;
		पूर्ण
		/*
		 * The last entry cannot contain a name. It can however contain
		 * a poपूर्णांकer to a child node in the B+tree so we just अवरोध out.
		 */
		अगर (ie->flags & INDEX_ENTRY_END)
			अवरोध;
		/*
		 * If the current entry has a name type of POSIX, the name is
		 * हाल sensitive and not otherwise. This has the effect of us
		 * not being able to access any POSIX file names which collate
		 * after the non-POSIX one when they only dअगरfer in हाल, but
		 * anyone करोing screwy stuff like that deserves to burn in
		 * hell... Doing that kind of stuff on NT4 actually causes
		 * corruption on the partition even when using SP6a and Linux
		 * is not involved at all.
		 */
		ic = ie->key.file_name.file_name_type ? IGNORE_CASE :
				CASE_SENSITIVE;
		/*
		 * If the names match perfectly, we are करोne and वापस the
		 * mft reference of the inode (i.e. the inode number together
		 * with the sequence number क्रम consistency checking. We
		 * convert it to cpu क्रमmat beक्रमe वापसing.
		 */
		अगर (ntfs_are_names_equal(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length, ic,
				vol->upहाल, vol->upहाल_len)) अणु
found_it2:
			mref = le64_to_cpu(ie->data.dir.indexed_file);
			unlock_page(page);
			ntfs_unmap_page(page);
			वापस mref;
		पूर्ण
		/*
		 * Not a perfect match, need to करो full blown collation so we
		 * know which way in the B+tree we have to go.
		 */
		rc = ntfs_collate_names(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length, 1,
				IGNORE_CASE, vol->upहाल, vol->upहाल_len);
		/*
		 * If uname collates beक्रमe the name of the current entry, there
		 * is definitely no such name in this index but we might need to
		 * descend पूर्णांकo the B+tree so we just अवरोध out of the loop.
		 */
		अगर (rc == -1)
			अवरोध;
		/* The names are not equal, जारी the search. */
		अगर (rc)
			जारी;
		/*
		 * Names match with हाल insensitive comparison, now try the
		 * हाल sensitive comparison, which is required क्रम proper
		 * collation.
		 */
		rc = ntfs_collate_names(uname, uname_len,
				(ntfsअक्षर*)&ie->key.file_name.file_name,
				ie->key.file_name.file_name_length, 1,
				CASE_SENSITIVE, vol->upहाल, vol->upहाल_len);
		अगर (rc == -1)
			अवरोध;
		अगर (rc)
			जारी;
		/*
		 * Perfect match, this will never happen as the
		 * ntfs_are_names_equal() call will have gotten a match but we
		 * still treat it correctly.
		 */
		जाओ found_it2;
	पूर्ण
	/*
	 * We have finished with this index buffer without success. Check क्रम
	 * the presence of a child node.
	 */
	अगर (ie->flags & INDEX_ENTRY_NODE) अणु
		अगर ((ia->index.flags & NODE_MASK) == LEAF_NODE) अणु
			ntfs_error(sb, "Index entry with child node found in "
					"a leaf node in directory inode 0x%lx.",
					dir_ni->mft_no);
			जाओ unm_err_out;
		पूर्ण
		/* Child node present, descend पूर्णांकo it. */
		old_vcn = vcn;
		vcn = sle64_to_cpup((u8*)ie + le16_to_cpu(ie->length) - 8);
		अगर (vcn >= 0) अणु
			/* If vcn is in the same page cache page as old_vcn we
			 * recycle the mapped page. */
			अगर (old_vcn << vol->cluster_size_bits >>
					PAGE_SHIFT == vcn <<
					vol->cluster_size_bits >>
					PAGE_SHIFT)
				जाओ fast_descend_पूर्णांकo_child_node;
			unlock_page(page);
			ntfs_unmap_page(page);
			जाओ descend_पूर्णांकo_child_node;
		पूर्ण
		ntfs_error(sb, "Negative child node vcn in directory inode "
				"0x%lx.", dir_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	/* No child node, वापस -ENOENT. */
	ntfs_debug("Entry not found.");
	err = -ENOENT;
unm_err_out:
	unlock_page(page);
	ntfs_unmap_page(page);
err_out:
	अगर (!err)
		err = -EIO;
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(dir_ni);
	वापस ERR_MREF(err);
dir_err_out:
	ntfs_error(sb, "Corrupt directory. Aborting lookup.");
	जाओ err_out;
पूर्ण

#पूर्ण_अगर

/**
 * ntfs_filldir - ntfs specअगरic filldir method
 * @vol:	current ntfs volume
 * @ndir:	ntfs inode of current directory
 * @ia_page:	page in which the index allocation buffer @ie is in resides
 * @ie:		current index entry
 * @name:	buffer to use क्रम the converted name
 * @actor:	what to feed the entries to
 *
 * Convert the Unicode @name to the loaded NLS and pass it to the @filldir
 * callback.
 *
 * If @ia_page is not शून्य it is the locked page containing the index
 * allocation block containing the index entry @ie.
 *
 * Note, we drop (and then reacquire) the page lock on @ia_page across the
 * @filldir() call otherwise we would deadlock with NFSd when it calls ->lookup
 * since ntfs_lookup() will lock the same page.  As an optimization, we करो not
 * retake the lock अगर we are वापसing a non-zero value as ntfs_सूची_पढ़ो()
 * would need to drop the lock immediately anyway.
 */
अटल अंतरभूत पूर्णांक ntfs_filldir(ntfs_volume *vol,
		ntfs_inode *ndir, काष्ठा page *ia_page, INDEX_ENTRY *ie,
		u8 *name, काष्ठा dir_context *actor)
अणु
	अचिन्हित दीर्घ mref;
	पूर्णांक name_len;
	अचिन्हित dt_type;
	खाता_NAME_TYPE_FLAGS name_type;

	name_type = ie->key.file_name.file_name_type;
	अगर (name_type == खाता_NAME_DOS) अणु
		ntfs_debug("Skipping DOS name space entry.");
		वापस 0;
	पूर्ण
	अगर (MREF_LE(ie->data.dir.indexed_file) == खाता_root) अणु
		ntfs_debug("Skipping root directory self reference entry.");
		वापस 0;
	पूर्ण
	अगर (MREF_LE(ie->data.dir.indexed_file) < खाता_first_user &&
			!NVolShowSystemFiles(vol)) अणु
		ntfs_debug("Skipping system file.");
		वापस 0;
	पूर्ण
	name_len = ntfs_ucstonls(vol, (ntfsअक्षर*)&ie->key.file_name.file_name,
			ie->key.file_name.file_name_length, &name,
			NTFS_MAX_NAME_LEN * NLS_MAX_CHARSET_SIZE + 1);
	अगर (name_len <= 0) अणु
		ntfs_warning(vol->sb, "Skipping unrepresentable inode 0x%llx.",
				(दीर्घ दीर्घ)MREF_LE(ie->data.dir.indexed_file));
		वापस 0;
	पूर्ण
	अगर (ie->key.file_name.file_attributes &
			खाता_ATTR_DUP_खाता_NAME_INDEX_PRESENT)
		dt_type = DT_सूची;
	अन्यथा
		dt_type = DT_REG;
	mref = MREF_LE(ie->data.dir.indexed_file);
	/*
	 * Drop the page lock otherwise we deadlock with NFS when it calls
	 * ->lookup since ntfs_lookup() will lock the same page.
	 */
	अगर (ia_page)
		unlock_page(ia_page);
	ntfs_debug("Calling filldir for %s with len %i, fpos 0x%llx, inode "
			"0x%lx, DT_%s.", name, name_len, actor->pos, mref,
			dt_type == DT_सूची ? "DIR" : "REG");
	अगर (!dir_emit(actor, name, name_len, mref, dt_type))
		वापस 1;
	/* Relock the page but not अगर we are पातing ->सूची_पढ़ो. */
	अगर (ia_page)
		lock_page(ia_page);
	वापस 0;
पूर्ण

/*
 * We use the same basic approach as the old NTFS driver, i.e. we parse the
 * index root entries and then the index allocation entries that are marked
 * as in use in the index biपंचांगap.
 *
 * While this will वापस the names in अक्रमom order this करोesn't matter क्रम
 * ->सूची_पढ़ो but OTOH results in a faster ->सूची_पढ़ो.
 *
 * VFS calls ->सूची_पढ़ो without BKL but with i_mutex held. This protects the VFS
 * parts (e.g. ->f_pos and ->i_size, and it also protects against directory
 * modअगरications).
 *
 * Locking:  - Caller must hold i_mutex on the directory.
 *	     - Each page cache page in the index allocation mapping must be
 *	       locked whilst being accessed otherwise we may find a corrupt
 *	       page due to it being under ->ग_लिखोpage at the moment which
 *	       applies the mst protection fixups beक्रमe writing out and then
 *	       हटाओs them again after the ग_लिखो is complete after which it 
 *	       unlocks the page.
 */
अटल पूर्णांक ntfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *actor)
अणु
	s64 ia_pos, ia_start, prev_ia_pos, bmp_pos;
	loff_t i_size;
	काष्ठा inode *bmp_vi, *vdir = file_inode(file);
	काष्ठा super_block *sb = vdir->i_sb;
	ntfs_inode *ndir = NTFS_I(vdir);
	ntfs_volume *vol = NTFS_SB(sb);
	MFT_RECORD *m;
	INDEX_ROOT *ir = शून्य;
	INDEX_ENTRY *ie;
	INDEX_ALLOCATION *ia;
	u8 *name = शून्य;
	पूर्णांक rc, err, ir_pos, cur_bmp_pos;
	काष्ठा address_space *ia_mapping, *bmp_mapping;
	काष्ठा page *bmp_page = शून्य, *ia_page = शून्य;
	u8 *kaddr, *bmp, *index_end;
	ntfs_attr_search_ctx *ctx;

	ntfs_debug("Entering for inode 0x%lx, fpos 0x%llx.",
			vdir->i_ino, actor->pos);
	rc = err = 0;
	/* Are we at end of dir yet? */
	i_size = i_size_पढ़ो(vdir);
	अगर (actor->pos >= i_size + vol->mft_record_size)
		वापस 0;
	/* Emulate . and .. क्रम all directories. */
	अगर (!dir_emit_करोts(file, actor))
		वापस 0;
	m = शून्य;
	ctx = शून्य;
	/*
	 * Allocate a buffer to store the current name being processed
	 * converted to क्रमmat determined by current NLS.
	 */
	name = kदो_स्मृति(NTFS_MAX_NAME_LEN * NLS_MAX_CHARSET_SIZE + 1, GFP_NOFS);
	अगर (unlikely(!name)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	/* Are we jumping straight पूर्णांकo the index allocation attribute? */
	अगर (actor->pos >= vol->mft_record_size)
		जाओ skip_index_root;
	/* Get hold of the mft record क्रम the directory. */
	m = map_mft_record(ndir);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		m = शून्य;
		जाओ err_out;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(ndir, m);
	अगर (unlikely(!ctx)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	/* Get the offset पूर्णांकo the index root attribute. */
	ir_pos = (s64)actor->pos;
	/* Find the index root attribute in the mft record. */
	err = ntfs_attr_lookup(AT_INDEX_ROOT, I30, 4, CASE_SENSITIVE, 0, शून्य,
			0, ctx);
	अगर (unlikely(err)) अणु
		ntfs_error(sb, "Index root attribute missing in directory "
				"inode 0x%lx.", vdir->i_ino);
		जाओ err_out;
	पूर्ण
	/*
	 * Copy the index root attribute value to a buffer so that we can put
	 * the search context and unmap the mft record beक्रमe calling the
	 * filldir() callback.  We need to करो this because of NFSd which calls
	 * ->lookup() from its filldir callback() and this causes NTFS to
	 * deadlock as ntfs_lookup() maps the mft record of the directory and
	 * we have got it mapped here alपढ़ोy.  The only solution is क्रम us to
	 * unmap the mft record here so that a call to ntfs_lookup() is able to
	 * map the mft record without deadlocking.
	 */
	rc = le32_to_cpu(ctx->attr->data.resident.value_length);
	ir = kदो_स्मृति(rc, GFP_NOFS);
	अगर (unlikely(!ir)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	/* Copy the index root value (it has been verअगरied in पढ़ो_inode). */
	स_नकल(ir, (u8*)ctx->attr +
			le16_to_cpu(ctx->attr->data.resident.value_offset), rc);
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(ndir);
	ctx = शून्य;
	m = शून्य;
	index_end = (u8*)&ir->index + le32_to_cpu(ir->index.index_length);
	/* The first index entry. */
	ie = (INDEX_ENTRY*)((u8*)&ir->index +
			le32_to_cpu(ir->index.entries_offset));
	/*
	 * Loop until we exceed valid memory (corruption हाल) or until we
	 * reach the last entry or until filldir tells us it has had enough
	 * or संकेतs an error (both covered by the rc test).
	 */
	क्रम (;; ie = (INDEX_ENTRY*)((u8*)ie + le16_to_cpu(ie->length))) अणु
		ntfs_debug("In index root, offset 0x%zx.", (u8*)ie - (u8*)ir);
		/* Bounds checks. */
		अगर (unlikely((u8*)ie < (u8*)ir || (u8*)ie +
				माप(INDEX_ENTRY_HEADER) > index_end ||
				(u8*)ie + le16_to_cpu(ie->key_length) >
				index_end))
			जाओ err_out;
		/* The last entry cannot contain a name. */
		अगर (ie->flags & INDEX_ENTRY_END)
			अवरोध;
		/* Skip index root entry अगर continuing previous सूची_पढ़ो. */
		अगर (ir_pos > (u8*)ie - (u8*)ir)
			जारी;
		/* Advance the position even अगर going to skip the entry. */
		actor->pos = (u8*)ie - (u8*)ir;
		/* Submit the name to the filldir callback. */
		rc = ntfs_filldir(vol, ndir, शून्य, ie, name, actor);
		अगर (rc) अणु
			kमुक्त(ir);
			जाओ पात;
		पूर्ण
	पूर्ण
	/* We are करोne with the index root and can मुक्त the buffer. */
	kमुक्त(ir);
	ir = शून्य;
	/* If there is no index allocation attribute we are finished. */
	अगर (!NInoIndexAllocPresent(ndir))
		जाओ EOD;
	/* Advance fpos to the beginning of the index allocation. */
	actor->pos = vol->mft_record_size;
skip_index_root:
	kaddr = शून्य;
	prev_ia_pos = -1LL;
	/* Get the offset पूर्णांकo the index allocation attribute. */
	ia_pos = (s64)actor->pos - vol->mft_record_size;
	ia_mapping = vdir->i_mapping;
	ntfs_debug("Inode 0x%lx, getting index bitmap.", vdir->i_ino);
	bmp_vi = ntfs_attr_iget(vdir, AT_BITMAP, I30, 4);
	अगर (IS_ERR(bmp_vi)) अणु
		ntfs_error(sb, "Failed to get bitmap attribute.");
		err = PTR_ERR(bmp_vi);
		जाओ err_out;
	पूर्ण
	bmp_mapping = bmp_vi->i_mapping;
	/* Get the starting biपंचांगap bit position and sanity check it. */
	bmp_pos = ia_pos >> ndir->itype.index.block_size_bits;
	अगर (unlikely(bmp_pos >> 3 >= i_size_पढ़ो(bmp_vi))) अणु
		ntfs_error(sb, "Current index allocation position exceeds "
				"index bitmap size.");
		जाओ iput_err_out;
	पूर्ण
	/* Get the starting bit position in the current biपंचांगap page. */
	cur_bmp_pos = bmp_pos & ((PAGE_SIZE * 8) - 1);
	bmp_pos &= ~(u64)((PAGE_SIZE * 8) - 1);
get_next_bmp_page:
	ntfs_debug("Reading bitmap with page index 0x%llx, bit ofs 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)bmp_pos >> (3 + PAGE_SHIFT),
			(अचिन्हित दीर्घ दीर्घ)bmp_pos &
			(अचिन्हित दीर्घ दीर्घ)((PAGE_SIZE * 8) - 1));
	bmp_page = ntfs_map_page(bmp_mapping,
			bmp_pos >> (3 + PAGE_SHIFT));
	अगर (IS_ERR(bmp_page)) अणु
		ntfs_error(sb, "Reading index bitmap failed.");
		err = PTR_ERR(bmp_page);
		bmp_page = शून्य;
		जाओ iput_err_out;
	पूर्ण
	bmp = (u8*)page_address(bmp_page);
	/* Find next index block in use. */
	जबतक (!(bmp[cur_bmp_pos >> 3] & (1 << (cur_bmp_pos & 7)))) अणु
find_next_index_buffer:
		cur_bmp_pos++;
		/*
		 * If we have reached the end of the biपंचांगap page, get the next
		 * page, and put away the old one.
		 */
		अगर (unlikely((cur_bmp_pos >> 3) >= PAGE_SIZE)) अणु
			ntfs_unmap_page(bmp_page);
			bmp_pos += PAGE_SIZE * 8;
			cur_bmp_pos = 0;
			जाओ get_next_bmp_page;
		पूर्ण
		/* If we have reached the end of the biपंचांगap, we are करोne. */
		अगर (unlikely(((bmp_pos + cur_bmp_pos) >> 3) >= i_size))
			जाओ unm_EOD;
		ia_pos = (bmp_pos + cur_bmp_pos) <<
				ndir->itype.index.block_size_bits;
	पूर्ण
	ntfs_debug("Handling index buffer 0x%llx.",
			(अचिन्हित दीर्घ दीर्घ)bmp_pos + cur_bmp_pos);
	/* If the current index buffer is in the same page we reuse the page. */
	अगर ((prev_ia_pos & (s64)PAGE_MASK) !=
			(ia_pos & (s64)PAGE_MASK)) अणु
		prev_ia_pos = ia_pos;
		अगर (likely(ia_page != शून्य)) अणु
			unlock_page(ia_page);
			ntfs_unmap_page(ia_page);
		पूर्ण
		/*
		 * Map the page cache page containing the current ia_pos,
		 * पढ़ोing it from disk अगर necessary.
		 */
		ia_page = ntfs_map_page(ia_mapping, ia_pos >> PAGE_SHIFT);
		अगर (IS_ERR(ia_page)) अणु
			ntfs_error(sb, "Reading index allocation data failed.");
			err = PTR_ERR(ia_page);
			ia_page = शून्य;
			जाओ err_out;
		पूर्ण
		lock_page(ia_page);
		kaddr = (u8*)page_address(ia_page);
	पूर्ण
	/* Get the current index buffer. */
	ia = (INDEX_ALLOCATION*)(kaddr + (ia_pos & ~PAGE_MASK &
					  ~(s64)(ndir->itype.index.block_size - 1)));
	/* Bounds checks. */
	अगर (unlikely((u8*)ia < kaddr || (u8*)ia > kaddr + PAGE_SIZE)) अणु
		ntfs_error(sb, "Out of bounds check failed. Corrupt directory "
				"inode 0x%lx or driver bug.", vdir->i_ino);
		जाओ err_out;
	पूर्ण
	/* Catch multi sector transfer fixup errors. */
	अगर (unlikely(!ntfs_is_indx_record(ia->magic))) अणु
		ntfs_error(sb, "Directory index record with vcn 0x%llx is "
				"corrupt.  Corrupt inode 0x%lx.  Run chkdsk.",
				(अचिन्हित दीर्घ दीर्घ)ia_pos >>
				ndir->itype.index.vcn_size_bits, vdir->i_ino);
		जाओ err_out;
	पूर्ण
	अगर (unlikely(sle64_to_cpu(ia->index_block_vcn) != (ia_pos &
			~(s64)(ndir->itype.index.block_size - 1)) >>
			ndir->itype.index.vcn_size_bits)) अणु
		ntfs_error(sb, "Actual VCN (0x%llx) of index buffer is "
				"different from expected VCN (0x%llx). "
				"Directory inode 0x%lx is corrupt or driver "
				"bug. ", (अचिन्हित दीर्घ दीर्घ)
				sle64_to_cpu(ia->index_block_vcn),
				(अचिन्हित दीर्घ दीर्घ)ia_pos >>
				ndir->itype.index.vcn_size_bits, vdir->i_ino);
		जाओ err_out;
	पूर्ण
	अगर (unlikely(le32_to_cpu(ia->index.allocated_size) + 0x18 !=
			ndir->itype.index.block_size)) अणु
		ntfs_error(sb, "Index buffer (VCN 0x%llx) of directory inode "
				"0x%lx has a size (%u) differing from the "
				"directory specified size (%u). Directory "
				"inode is corrupt or driver bug.",
				(अचिन्हित दीर्घ दीर्घ)ia_pos >>
				ndir->itype.index.vcn_size_bits, vdir->i_ino,
				le32_to_cpu(ia->index.allocated_size) + 0x18,
				ndir->itype.index.block_size);
		जाओ err_out;
	पूर्ण
	index_end = (u8*)ia + ndir->itype.index.block_size;
	अगर (unlikely(index_end > kaddr + PAGE_SIZE)) अणु
		ntfs_error(sb, "Index buffer (VCN 0x%llx) of directory inode "
				"0x%lx crosses page boundary. Impossible! "
				"Cannot access! This is probably a bug in the "
				"driver.", (अचिन्हित दीर्घ दीर्घ)ia_pos >>
				ndir->itype.index.vcn_size_bits, vdir->i_ino);
		जाओ err_out;
	पूर्ण
	ia_start = ia_pos & ~(s64)(ndir->itype.index.block_size - 1);
	index_end = (u8*)&ia->index + le32_to_cpu(ia->index.index_length);
	अगर (unlikely(index_end > (u8*)ia + ndir->itype.index.block_size)) अणु
		ntfs_error(sb, "Size of index buffer (VCN 0x%llx) of directory "
				"inode 0x%lx exceeds maximum size.",
				(अचिन्हित दीर्घ दीर्घ)ia_pos >>
				ndir->itype.index.vcn_size_bits, vdir->i_ino);
		जाओ err_out;
	पूर्ण
	/* The first index entry in this index buffer. */
	ie = (INDEX_ENTRY*)((u8*)&ia->index +
			le32_to_cpu(ia->index.entries_offset));
	/*
	 * Loop until we exceed valid memory (corruption हाल) or until we
	 * reach the last entry or until filldir tells us it has had enough
	 * or संकेतs an error (both covered by the rc test).
	 */
	क्रम (;; ie = (INDEX_ENTRY*)((u8*)ie + le16_to_cpu(ie->length))) अणु
		ntfs_debug("In index allocation, offset 0x%llx.",
				(अचिन्हित दीर्घ दीर्घ)ia_start +
				(अचिन्हित दीर्घ दीर्घ)((u8*)ie - (u8*)ia));
		/* Bounds checks. */
		अगर (unlikely((u8*)ie < (u8*)ia || (u8*)ie +
				माप(INDEX_ENTRY_HEADER) > index_end ||
				(u8*)ie + le16_to_cpu(ie->key_length) >
				index_end))
			जाओ err_out;
		/* The last entry cannot contain a name. */
		अगर (ie->flags & INDEX_ENTRY_END)
			अवरोध;
		/* Skip index block entry अगर continuing previous सूची_पढ़ो. */
		अगर (ia_pos - ia_start > (u8*)ie - (u8*)ia)
			जारी;
		/* Advance the position even अगर going to skip the entry. */
		actor->pos = (u8*)ie - (u8*)ia +
				(sle64_to_cpu(ia->index_block_vcn) <<
				ndir->itype.index.vcn_size_bits) +
				vol->mft_record_size;
		/*
		 * Submit the name to the @filldir callback.  Note,
		 * ntfs_filldir() drops the lock on @ia_page but it retakes it
		 * beक्रमe वापसing, unless a non-zero value is वापसed in
		 * which हाल the page is left unlocked.
		 */
		rc = ntfs_filldir(vol, ndir, ia_page, ie, name, actor);
		अगर (rc) अणु
			/* @ia_page is alपढ़ोy unlocked in this हाल. */
			ntfs_unmap_page(ia_page);
			ntfs_unmap_page(bmp_page);
			iput(bmp_vi);
			जाओ पात;
		पूर्ण
	पूर्ण
	जाओ find_next_index_buffer;
unm_EOD:
	अगर (ia_page) अणु
		unlock_page(ia_page);
		ntfs_unmap_page(ia_page);
	पूर्ण
	ntfs_unmap_page(bmp_page);
	iput(bmp_vi);
EOD:
	/* We are finished, set fpos to EOD. */
	actor->pos = i_size + vol->mft_record_size;
पात:
	kमुक्त(name);
	वापस 0;
err_out:
	अगर (bmp_page) अणु
		ntfs_unmap_page(bmp_page);
iput_err_out:
		iput(bmp_vi);
	पूर्ण
	अगर (ia_page) अणु
		unlock_page(ia_page);
		ntfs_unmap_page(ia_page);
	पूर्ण
	kमुक्त(ir);
	kमुक्त(name);
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(ndir);
	अगर (!err)
		err = -EIO;
	ntfs_debug("Failed. Returning error code %i.", -err);
	वापस err;
पूर्ण

/**
 * ntfs_dir_खोलो - called when an inode is about to be खोलोed
 * @vi:		inode to be खोलोed
 * @filp:	file काष्ठाure describing the inode
 *
 * Limit directory size to the page cache limit on architectures where अचिन्हित
 * दीर्घ is 32-bits. This is the most we can करो क्रम now without overflowing the
 * page cache page index. Doing it this way means we करोn't run पूर्णांकo problems
 * because of existing too large directories. It would be better to allow the
 * user to पढ़ो the accessible part of the directory but I करोubt very much
 * anyone is going to hit this check on a 32-bit architecture, so there is no
 * poपूर्णांक in adding the extra complनिकासy required to support this.
 *
 * On 64-bit architectures, the check is hopefully optimized away by the
 * compiler.
 */
अटल पूर्णांक ntfs_dir_खोलो(काष्ठा inode *vi, काष्ठा file *filp)
अणु
	अगर (माप(अचिन्हित दीर्घ) < 8) अणु
		अगर (i_size_पढ़ो(vi) > MAX_LFS_खाताSIZE)
			वापस -EFBIG;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित NTFS_RW

/**
 * ntfs_dir_fsync - sync a directory to disk
 * @filp:	directory to be synced
 * @dentry:	dentry describing the directory to sync
 * @datasync:	अगर non-zero only flush user data and not metadata
 *
 * Data पूर्णांकegrity sync of a directory to disk.  Used क्रम fsync, fdatasync, and
 * msync प्रणाली calls.  This function is based on file.c::ntfs_file_fsync().
 *
 * Write the mft record and all associated extent mft records as well as the
 * $INDEX_ALLOCATION and $BITMAP attributes and then sync the block device.
 *
 * If @datasync is true, we करो not रुको on the inode(s) to be written out
 * but we always रुको on the page cache pages to be written out.
 *
 * Note: In the past @filp could be शून्य so we ignore it as we करोn't need it
 * anyway.
 *
 * Locking: Caller must hold i_mutex on the inode.
 *
 * TODO: We should probably also ग_लिखो all attribute/index inodes associated
 * with this inode but since we have no simple way of getting to them we ignore
 * this problem क्रम now.  We करो ग_लिखो the $BITMAP attribute अगर it is present
 * which is the important one क्रम a directory so things are not too bad.
 */
अटल पूर्णांक ntfs_dir_fsync(काष्ठा file *filp, loff_t start, loff_t end,
			  पूर्णांक datasync)
अणु
	काष्ठा inode *bmp_vi, *vi = filp->f_mapping->host;
	पूर्णांक err, ret;
	ntfs_attr na;

	ntfs_debug("Entering for inode 0x%lx.", vi->i_ino);

	err = file_ग_लिखो_and_रुको_range(filp, start, end);
	अगर (err)
		वापस err;
	inode_lock(vi);

	BUG_ON(!S_ISसूची(vi->i_mode));
	/* If the biपंचांगap attribute inode is in memory sync it, too. */
	na.mft_no = vi->i_ino;
	na.type = AT_BITMAP;
	na.name = I30;
	na.name_len = 4;
	bmp_vi = ilookup5(vi->i_sb, vi->i_ino, ntfs_test_inode, &na);
	अगर (bmp_vi) अणु
 		ग_लिखो_inode_now(bmp_vi, !datasync);
		iput(bmp_vi);
	पूर्ण
	ret = __ntfs_ग_लिखो_inode(vi, 1);
	ग_लिखो_inode_now(vi, !datasync);
	err = sync_blockdev(vi->i_sb->s_bdev);
	अगर (unlikely(err && !ret))
		ret = err;
	अगर (likely(!ret))
		ntfs_debug("Done.");
	अन्यथा
		ntfs_warning(vi->i_sb, "Failed to f%ssync inode 0x%lx.  Error "
				"%u.", datasync ? "data" : "", vi->i_ino, -ret);
	inode_unlock(vi);
	वापस ret;
पूर्ण

#पूर्ण_अगर /* NTFS_RW */

स्थिर काष्ठा file_operations ntfs_dir_ops = अणु
	.llseek		= generic_file_llseek,	/* Seek inside directory. */
	.पढ़ो		= generic_पढ़ो_dir,	/* Return -EISसूची. */
	.iterate	= ntfs_सूची_पढ़ो,		/* Read directory contents. */
#अगर_घोषित NTFS_RW
	.fsync		= ntfs_dir_fsync,	/* Sync a directory to disk. */
#पूर्ण_अगर /* NTFS_RW */
	/*.ioctl	= ,*/			/* Perक्रमm function on the
						   mounted fileप्रणाली. */
	.खोलो		= ntfs_dir_खोलो,	/* Open directory. */
पूर्ण;
