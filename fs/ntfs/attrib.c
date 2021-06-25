<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**
 * attrib.c - NTFS attribute operations.  Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2012 Anton Altaparmakov and Tuxera Inc.
 * Copyright (c) 2002 Riअक्षरd Russon
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश <linux/ग_लिखोback.h>

#समावेश "attrib.h"
#समावेश "debug.h"
#समावेश "layout.h"
#समावेश "lcnalloc.h"
#समावेश "malloc.h"
#समावेश "mft.h"
#समावेश "ntfs.h"
#समावेश "types.h"

/**
 * ntfs_map_runlist_nolock - map (a part of) a runlist of an ntfs inode
 * @ni:		ntfs inode क्रम which to map (part of) a runlist
 * @vcn:	map runlist part containing this vcn
 * @ctx:	active attribute search context अगर present or शून्य अगर not
 *
 * Map the part of a runlist containing the @vcn of the ntfs inode @ni.
 *
 * If @ctx is specअगरied, it is an active search context of @ni and its base mft
 * record.  This is needed when ntfs_map_runlist_nolock() encounters unmapped
 * runlist fragments and allows their mapping.  If you करो not have the mft
 * record mapped, you can specअगरy @ctx as शून्य and ntfs_map_runlist_nolock()
 * will perक्रमm the necessary mapping and unmapping.
 *
 * Note, ntfs_map_runlist_nolock() saves the state of @ctx on entry and
 * restores it beक्रमe वापसing.  Thus, @ctx will be left poपूर्णांकing to the same
 * attribute on वापस as on entry.  However, the actual poपूर्णांकers in @ctx may
 * poपूर्णांक to dअगरferent memory locations on वापस, so you must remember to reset
 * any cached poपूर्णांकers from the @ctx, i.e. after the call to
 * ntfs_map_runlist_nolock(), you will probably want to करो:
 *	m = ctx->mrec;
 *	a = ctx->attr;
 * Assuming you cache ctx->attr in a variable @a of type ATTR_RECORD * and that
 * you cache ctx->mrec in a variable @m of type MFT_RECORD *.
 *
 * Return 0 on success and -त्रुटि_सं on error.  There is one special error code
 * which is not an error as such.  This is -ENOENT.  It means that @vcn is out
 * of bounds of the runlist.
 *
 * Note the runlist can be शून्य after this function वापसs अगर @vcn is zero and
 * the attribute has zero allocated size, i.e. there simply is no runlist.
 *
 * WARNING: If @ctx is supplied, regardless of whether success or failure is
 *	    वापसed, you need to check IS_ERR(@ctx->mrec) and अगर 'true' the @ctx
 *	    is no दीर्घer valid, i.e. you need to either call
 *	    ntfs_attr_reinit_search_ctx() or ntfs_attr_put_search_ctx() on it.
 *	    In that हाल PTR_ERR(@ctx->mrec) will give you the error code क्रम
 *	    why the mapping of the old inode failed.
 *
 * Locking: - The runlist described by @ni must be locked क्रम writing on entry
 *	      and is locked on वापस.  Note the runlist will be modअगरied.
 *	    - If @ctx is शून्य, the base mft record of @ni must not be mapped on
 *	      entry and it will be left unmapped on वापस.
 *	    - If @ctx is not शून्य, the base mft record must be mapped on entry
 *	      and it will be left mapped on वापस.
 */
पूर्णांक ntfs_map_runlist_nolock(ntfs_inode *ni, VCN vcn, ntfs_attr_search_ctx *ctx)
अणु
	VCN end_vcn;
	अचिन्हित दीर्घ flags;
	ntfs_inode *base_ni;
	MFT_RECORD *m;
	ATTR_RECORD *a;
	runlist_element *rl;
	काष्ठा page *put_this_page = शून्य;
	पूर्णांक err = 0;
	bool ctx_is_temporary, ctx_needs_reset;
	ntfs_attr_search_ctx old_ctx = अणु शून्य, पूर्ण;

	ntfs_debug("Mapping runlist part containing vcn 0x%llx.",
			(अचिन्हित दीर्घ दीर्घ)vcn);
	अगर (!NInoAttr(ni))
		base_ni = ni;
	अन्यथा
		base_ni = ni->ext.base_ntfs_ino;
	अगर (!ctx) अणु
		ctx_is_temporary = ctx_needs_reset = true;
		m = map_mft_record(base_ni);
		अगर (IS_ERR(m))
			वापस PTR_ERR(m);
		ctx = ntfs_attr_get_search_ctx(base_ni, m);
		अगर (unlikely(!ctx)) अणु
			err = -ENOMEM;
			जाओ err_out;
		पूर्ण
	पूर्ण अन्यथा अणु
		VCN allocated_size_vcn;

		BUG_ON(IS_ERR(ctx->mrec));
		a = ctx->attr;
		BUG_ON(!a->non_resident);
		ctx_is_temporary = false;
		end_vcn = sle64_to_cpu(a->data.non_resident.highest_vcn);
		पढ़ो_lock_irqsave(&ni->size_lock, flags);
		allocated_size_vcn = ni->allocated_size >>
				ni->vol->cluster_size_bits;
		पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
		अगर (!a->data.non_resident.lowest_vcn && end_vcn <= 0)
			end_vcn = allocated_size_vcn - 1;
		/*
		 * If we alपढ़ोy have the attribute extent containing @vcn in
		 * @ctx, no need to look it up again.  We slightly cheat in
		 * that अगर vcn exceeds the allocated size, we will refuse to
		 * map the runlist below, so there is definitely no need to get
		 * the right attribute extent.
		 */
		अगर (vcn >= allocated_size_vcn || (a->type == ni->type &&
				a->name_length == ni->name_len &&
				!स_भेद((u8*)a + le16_to_cpu(a->name_offset),
				ni->name, ni->name_len) &&
				sle64_to_cpu(a->data.non_resident.lowest_vcn)
				<= vcn && end_vcn >= vcn))
			ctx_needs_reset = false;
		अन्यथा अणु
			/* Save the old search context. */
			old_ctx = *ctx;
			/*
			 * If the currently mapped (extent) inode is not the
			 * base inode we will unmap it when we reinitialize the
			 * search context which means we need to get a
			 * reference to the page containing the mapped mft
			 * record so we करो not accidentally drop changes to the
			 * mft record when it has not been marked dirty yet.
			 */
			अगर (old_ctx.base_ntfs_ino && old_ctx.ntfs_ino !=
					old_ctx.base_ntfs_ino) अणु
				put_this_page = old_ctx.ntfs_ino->page;
				get_page(put_this_page);
			पूर्ण
			/*
			 * Reinitialize the search context so we can lookup the
			 * needed attribute extent.
			 */
			ntfs_attr_reinit_search_ctx(ctx);
			ctx_needs_reset = true;
		पूर्ण
	पूर्ण
	अगर (ctx_needs_reset) अणु
		err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
				CASE_SENSITIVE, vcn, शून्य, 0, ctx);
		अगर (unlikely(err)) अणु
			अगर (err == -ENOENT)
				err = -EIO;
			जाओ err_out;
		पूर्ण
		BUG_ON(!ctx->attr->non_resident);
	पूर्ण
	a = ctx->attr;
	/*
	 * Only decompress the mapping pairs अगर @vcn is inside it.  Otherwise
	 * we get पूर्णांकo problems when we try to map an out of bounds vcn because
	 * we then try to map the alपढ़ोy mapped runlist fragment and
	 * ntfs_mapping_pairs_decompress() fails.
	 */
	end_vcn = sle64_to_cpu(a->data.non_resident.highest_vcn) + 1;
	अगर (unlikely(vcn && vcn >= end_vcn)) अणु
		err = -ENOENT;
		जाओ err_out;
	पूर्ण
	rl = ntfs_mapping_pairs_decompress(ni->vol, a, ni->runlist.rl);
	अगर (IS_ERR(rl))
		err = PTR_ERR(rl);
	अन्यथा
		ni->runlist.rl = rl;
err_out:
	अगर (ctx_is_temporary) अणु
		अगर (likely(ctx))
			ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(base_ni);
	पूर्ण अन्यथा अगर (ctx_needs_reset) अणु
		/*
		 * If there is no attribute list, restoring the search context
		 * is accomplished simply by copying the saved context back over
		 * the caller supplied context.  If there is an attribute list,
		 * things are more complicated as we need to deal with mapping
		 * of mft records and resulting potential changes in poपूर्णांकers.
		 */
		अगर (NInoAttrList(base_ni)) अणु
			/*
			 * If the currently mapped (extent) inode is not the
			 * one we had beक्रमe, we need to unmap it and map the
			 * old one.
			 */
			अगर (ctx->ntfs_ino != old_ctx.ntfs_ino) अणु
				/*
				 * If the currently mapped inode is not the
				 * base inode, unmap it.
				 */
				अगर (ctx->base_ntfs_ino && ctx->ntfs_ino !=
						ctx->base_ntfs_ino) अणु
					unmap_extent_mft_record(ctx->ntfs_ino);
					ctx->mrec = ctx->base_mrec;
					BUG_ON(!ctx->mrec);
				पूर्ण
				/*
				 * If the old mapped inode is not the base
				 * inode, map it.
				 */
				अगर (old_ctx.base_ntfs_ino &&
						old_ctx.ntfs_ino !=
						old_ctx.base_ntfs_ino) अणु
retry_map:
					ctx->mrec = map_mft_record(
							old_ctx.ntfs_ino);
					/*
					 * Something bad has happened.  If out
					 * of memory retry till it succeeds.
					 * Any other errors are fatal and we
					 * वापस the error code in ctx->mrec.
					 * Let the caller deal with it...  We
					 * just need to fudge things so the
					 * caller can reinit and/or put the
					 * search context safely.
					 */
					अगर (IS_ERR(ctx->mrec)) अणु
						अगर (PTR_ERR(ctx->mrec) ==
								-ENOMEM) अणु
							schedule();
							जाओ retry_map;
						पूर्ण अन्यथा
							old_ctx.ntfs_ino =
								old_ctx.
								base_ntfs_ino;
					पूर्ण
				पूर्ण
			पूर्ण
			/* Update the changed poपूर्णांकers in the saved context. */
			अगर (ctx->mrec != old_ctx.mrec) अणु
				अगर (!IS_ERR(ctx->mrec))
					old_ctx.attr = (ATTR_RECORD*)(
							(u8*)ctx->mrec +
							((u8*)old_ctx.attr -
							(u8*)old_ctx.mrec));
				old_ctx.mrec = ctx->mrec;
			पूर्ण
		पूर्ण
		/* Restore the search context to the saved one. */
		*ctx = old_ctx;
		/*
		 * We drop the reference on the page we took earlier.  In the
		 * हाल that IS_ERR(ctx->mrec) is true this means we might lose
		 * some changes to the mft record that had been made between
		 * the last समय it was marked dirty/written out and now.  This
		 * at this stage is not a problem as the mapping error is fatal
		 * enough that the mft record cannot be written out anyway and
		 * the caller is very likely to shutकरोwn the whole inode
		 * immediately and mark the volume dirty क्रम chkdsk to pick up
		 * the pieces anyway.
		 */
		अगर (put_this_page)
			put_page(put_this_page);
	पूर्ण
	वापस err;
पूर्ण

/**
 * ntfs_map_runlist - map (a part of) a runlist of an ntfs inode
 * @ni:		ntfs inode क्रम which to map (part of) a runlist
 * @vcn:	map runlist part containing this vcn
 *
 * Map the part of a runlist containing the @vcn of the ntfs inode @ni.
 *
 * Return 0 on success and -त्रुटि_सं on error.  There is one special error code
 * which is not an error as such.  This is -ENOENT.  It means that @vcn is out
 * of bounds of the runlist.
 *
 * Locking: - The runlist must be unlocked on entry and is unlocked on वापस.
 *	    - This function takes the runlist lock क्रम writing and may modअगरy
 *	      the runlist.
 */
पूर्णांक ntfs_map_runlist(ntfs_inode *ni, VCN vcn)
अणु
	पूर्णांक err = 0;

	करोwn_ग_लिखो(&ni->runlist.lock);
	/* Make sure someone अन्यथा didn't करो the work जबतक we were sleeping. */
	अगर (likely(ntfs_rl_vcn_to_lcn(ni->runlist.rl, vcn) <=
			LCN_RL_NOT_MAPPED))
		err = ntfs_map_runlist_nolock(ni, vcn, शून्य);
	up_ग_लिखो(&ni->runlist.lock);
	वापस err;
पूर्ण

/**
 * ntfs_attr_vcn_to_lcn_nolock - convert a vcn पूर्णांकo a lcn given an ntfs inode
 * @ni:			ntfs inode of the attribute whose runlist to search
 * @vcn:		vcn to convert
 * @ग_लिखो_locked:	true अगर the runlist is locked क्रम writing
 *
 * Find the भव cluster number @vcn in the runlist of the ntfs attribute
 * described by the ntfs inode @ni and वापस the corresponding logical cluster
 * number (lcn).
 *
 * If the @vcn is not mapped yet, the attempt is made to map the attribute
 * extent containing the @vcn and the vcn to lcn conversion is retried.
 *
 * If @ग_लिखो_locked is true the caller has locked the runlist क्रम writing and
 * अगर false क्रम पढ़ोing.
 *
 * Since lcns must be >= 0, we use negative वापस codes with special meaning:
 *
 * Return code	Meaning / Description
 * ==========================================
 *  LCN_HOLE	Hole / not allocated on disk.
 *  LCN_ENOENT	There is no such vcn in the runlist, i.e. @vcn is out of bounds.
 *  LCN_ENOMEM	Not enough memory to map runlist.
 *  LCN_EIO	Critical error (runlist/file is corrupt, i/o error, etc).
 *
 * Locking: - The runlist must be locked on entry and is left locked on वापस.
 *	    - If @ग_लिखो_locked is 'false', i.e. the runlist is locked क्रम पढ़ोing,
 *	      the lock may be dropped inside the function so you cannot rely on
 *	      the runlist still being the same when this function वापसs.
 */
LCN ntfs_attr_vcn_to_lcn_nolock(ntfs_inode *ni, स्थिर VCN vcn,
		स्थिर bool ग_लिखो_locked)
अणु
	LCN lcn;
	अचिन्हित दीर्घ flags;
	bool is_retry = false;

	BUG_ON(!ni);
	ntfs_debug("Entering for i_ino 0x%lx, vcn 0x%llx, %s_locked.",
			ni->mft_no, (अचिन्हित दीर्घ दीर्घ)vcn,
			ग_लिखो_locked ? "write" : "read");
	BUG_ON(!NInoNonResident(ni));
	BUG_ON(vcn < 0);
	अगर (!ni->runlist.rl) अणु
		पढ़ो_lock_irqsave(&ni->size_lock, flags);
		अगर (!ni->allocated_size) अणु
			पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
			वापस LCN_ENOENT;
		पूर्ण
		पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	पूर्ण
retry_remap:
	/* Convert vcn to lcn.  If that fails map the runlist and retry once. */
	lcn = ntfs_rl_vcn_to_lcn(ni->runlist.rl, vcn);
	अगर (likely(lcn >= LCN_HOLE)) अणु
		ntfs_debug("Done, lcn 0x%llx.", (दीर्घ दीर्घ)lcn);
		वापस lcn;
	पूर्ण
	अगर (lcn != LCN_RL_NOT_MAPPED) अणु
		अगर (lcn != LCN_ENOENT)
			lcn = LCN_EIO;
	पूर्ण अन्यथा अगर (!is_retry) अणु
		पूर्णांक err;

		अगर (!ग_लिखो_locked) अणु
			up_पढ़ो(&ni->runlist.lock);
			करोwn_ग_लिखो(&ni->runlist.lock);
			अगर (unlikely(ntfs_rl_vcn_to_lcn(ni->runlist.rl, vcn) !=
					LCN_RL_NOT_MAPPED)) अणु
				up_ग_लिखो(&ni->runlist.lock);
				करोwn_पढ़ो(&ni->runlist.lock);
				जाओ retry_remap;
			पूर्ण
		पूर्ण
		err = ntfs_map_runlist_nolock(ni, vcn, शून्य);
		अगर (!ग_लिखो_locked) अणु
			up_ग_लिखो(&ni->runlist.lock);
			करोwn_पढ़ो(&ni->runlist.lock);
		पूर्ण
		अगर (likely(!err)) अणु
			is_retry = true;
			जाओ retry_remap;
		पूर्ण
		अगर (err == -ENOENT)
			lcn = LCN_ENOENT;
		अन्यथा अगर (err == -ENOMEM)
			lcn = LCN_ENOMEM;
		अन्यथा
			lcn = LCN_EIO;
	पूर्ण
	अगर (lcn != LCN_ENOENT)
		ntfs_error(ni->vol->sb, "Failed with error code %lli.",
				(दीर्घ दीर्घ)lcn);
	वापस lcn;
पूर्ण

/**
 * ntfs_attr_find_vcn_nolock - find a vcn in the runlist of an ntfs inode
 * @ni:		ntfs inode describing the runlist to search
 * @vcn:	vcn to find
 * @ctx:	active attribute search context अगर present or शून्य अगर not
 *
 * Find the भव cluster number @vcn in the runlist described by the ntfs
 * inode @ni and वापस the address of the runlist element containing the @vcn.
 *
 * If the @vcn is not mapped yet, the attempt is made to map the attribute
 * extent containing the @vcn and the vcn to lcn conversion is retried.
 *
 * If @ctx is specअगरied, it is an active search context of @ni and its base mft
 * record.  This is needed when ntfs_attr_find_vcn_nolock() encounters unmapped
 * runlist fragments and allows their mapping.  If you करो not have the mft
 * record mapped, you can specअगरy @ctx as शून्य and ntfs_attr_find_vcn_nolock()
 * will perक्रमm the necessary mapping and unmapping.
 *
 * Note, ntfs_attr_find_vcn_nolock() saves the state of @ctx on entry and
 * restores it beक्रमe वापसing.  Thus, @ctx will be left poपूर्णांकing to the same
 * attribute on वापस as on entry.  However, the actual poपूर्णांकers in @ctx may
 * poपूर्णांक to dअगरferent memory locations on वापस, so you must remember to reset
 * any cached poपूर्णांकers from the @ctx, i.e. after the call to
 * ntfs_attr_find_vcn_nolock(), you will probably want to करो:
 *	m = ctx->mrec;
 *	a = ctx->attr;
 * Assuming you cache ctx->attr in a variable @a of type ATTR_RECORD * and that
 * you cache ctx->mrec in a variable @m of type MFT_RECORD *.
 * Note you need to distinguish between the lcn of the वापसed runlist element
 * being >= 0 and LCN_HOLE.  In the later हाल you have to वापस zeroes on
 * पढ़ो and allocate clusters on ग_लिखो.
 *
 * Return the runlist element containing the @vcn on success and
 * ERR_PTR(-त्रुटि_सं) on error.  You need to test the वापस value with IS_ERR()
 * to decide अगर the वापस is success or failure and PTR_ERR() to get to the
 * error code अगर IS_ERR() is true.
 *
 * The possible error वापस codes are:
 *	-ENOENT - No such vcn in the runlist, i.e. @vcn is out of bounds.
 *	-ENOMEM - Not enough memory to map runlist.
 *	-EIO	- Critical error (runlist/file is corrupt, i/o error, etc).
 *
 * WARNING: If @ctx is supplied, regardless of whether success or failure is
 *	    वापसed, you need to check IS_ERR(@ctx->mrec) and अगर 'true' the @ctx
 *	    is no दीर्घer valid, i.e. you need to either call
 *	    ntfs_attr_reinit_search_ctx() or ntfs_attr_put_search_ctx() on it.
 *	    In that हाल PTR_ERR(@ctx->mrec) will give you the error code क्रम
 *	    why the mapping of the old inode failed.
 *
 * Locking: - The runlist described by @ni must be locked क्रम writing on entry
 *	      and is locked on वापस.  Note the runlist may be modअगरied when
 *	      needed runlist fragments need to be mapped.
 *	    - If @ctx is शून्य, the base mft record of @ni must not be mapped on
 *	      entry and it will be left unmapped on वापस.
 *	    - If @ctx is not शून्य, the base mft record must be mapped on entry
 *	      and it will be left mapped on वापस.
 */
runlist_element *ntfs_attr_find_vcn_nolock(ntfs_inode *ni, स्थिर VCN vcn,
		ntfs_attr_search_ctx *ctx)
अणु
	अचिन्हित दीर्घ flags;
	runlist_element *rl;
	पूर्णांक err = 0;
	bool is_retry = false;

	BUG_ON(!ni);
	ntfs_debug("Entering for i_ino 0x%lx, vcn 0x%llx, with%s ctx.",
			ni->mft_no, (अचिन्हित दीर्घ दीर्घ)vcn, ctx ? "" : "out");
	BUG_ON(!NInoNonResident(ni));
	BUG_ON(vcn < 0);
	अगर (!ni->runlist.rl) अणु
		पढ़ो_lock_irqsave(&ni->size_lock, flags);
		अगर (!ni->allocated_size) अणु
			पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
			वापस ERR_PTR(-ENOENT);
		पूर्ण
		पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	पूर्ण
retry_remap:
	rl = ni->runlist.rl;
	अगर (likely(rl && vcn >= rl[0].vcn)) अणु
		जबतक (likely(rl->length)) अणु
			अगर (unlikely(vcn < rl[1].vcn)) अणु
				अगर (likely(rl->lcn >= LCN_HOLE)) अणु
					ntfs_debug("Done.");
					वापस rl;
				पूर्ण
				अवरोध;
			पूर्ण
			rl++;
		पूर्ण
		अगर (likely(rl->lcn != LCN_RL_NOT_MAPPED)) अणु
			अगर (likely(rl->lcn == LCN_ENOENT))
				err = -ENOENT;
			अन्यथा
				err = -EIO;
		पूर्ण
	पूर्ण
	अगर (!err && !is_retry) अणु
		/*
		 * If the search context is invalid we cannot map the unmapped
		 * region.
		 */
		अगर (IS_ERR(ctx->mrec))
			err = PTR_ERR(ctx->mrec);
		अन्यथा अणु
			/*
			 * The @vcn is in an unmapped region, map the runlist
			 * and retry.
			 */
			err = ntfs_map_runlist_nolock(ni, vcn, ctx);
			अगर (likely(!err)) अणु
				is_retry = true;
				जाओ retry_remap;
			पूर्ण
		पूर्ण
		अगर (err == -EINVAL)
			err = -EIO;
	पूर्ण अन्यथा अगर (!err)
		err = -EIO;
	अगर (err != -ENOENT)
		ntfs_error(ni->vol->sb, "Failed with error code %i.", err);
	वापस ERR_PTR(err);
पूर्ण

/**
 * ntfs_attr_find - find (next) attribute in mft record
 * @type:	attribute type to find
 * @name:	attribute name to find (optional, i.e. शून्य means करोn't care)
 * @name_len:	attribute name length (only needed अगर @name present)
 * @ic:		IGNORE_CASE or CASE_SENSITIVE (ignored अगर @name not present)
 * @val:	attribute value to find (optional, resident attributes only)
 * @val_len:	attribute value length
 * @ctx:	search context with mft record and attribute to search from
 *
 * You should not need to call this function directly.  Use ntfs_attr_lookup()
 * instead.
 *
 * ntfs_attr_find() takes a search context @ctx as parameter and searches the
 * mft record specअगरied by @ctx->mrec, beginning at @ctx->attr, क्रम an
 * attribute of @type, optionally @name and @val.
 *
 * If the attribute is found, ntfs_attr_find() वापसs 0 and @ctx->attr will
 * poपूर्णांक to the found attribute.
 *
 * If the attribute is not found, ntfs_attr_find() वापसs -ENOENT and
 * @ctx->attr will poपूर्णांक to the attribute beक्रमe which the attribute being
 * searched क्रम would need to be inserted अगर such an action were to be desired.
 *
 * On actual error, ntfs_attr_find() वापसs -EIO.  In this हाल @ctx->attr is
 * undefined and in particular करो not rely on it not changing.
 *
 * If @ctx->is_first is 'true', the search begins with @ctx->attr itself.  If it
 * is 'false', the search begins after @ctx->attr.
 *
 * If @ic is IGNORE_CASE, the @name comparisson is not हाल sensitive and
 * @ctx->ntfs_ino must be set to the ntfs inode to which the mft record
 * @ctx->mrec beदीर्घs.  This is so we can get at the ntfs volume and hence at
 * the upहाल table.  If @ic is CASE_SENSITIVE, the comparison is हाल
 * sensitive.  When @name is present, @name_len is the @name length in Unicode
 * अक्षरacters.
 *
 * If @name is not present (शून्य), we assume that the unnamed attribute is
 * being searched क्रम.
 *
 * Finally, the resident attribute value @val is looked क्रम, अगर present.  If
 * @val is not present (शून्य), @val_len is ignored.
 *
 * ntfs_attr_find() only searches the specअगरied mft record and it ignores the
 * presence of an attribute list attribute (unless it is the one being searched
 * क्रम, obviously).  If you need to take attribute lists पूर्णांकo consideration,
 * use ntfs_attr_lookup() instead (see below).  This also means that you cannot
 * use ntfs_attr_find() to search क्रम extent records of non-resident
 * attributes, as extents with lowest_vcn != 0 are usually described by the
 * attribute list attribute only. - Note that it is possible that the first
 * extent is only in the attribute list जबतक the last extent is in the base
 * mft record, so करो not rely on being able to find the first extent in the
 * base mft record.
 *
 * Warning: Never use @val when looking क्रम attribute types which can be
 *	    non-resident as this most likely will result in a crash!
 */
अटल पूर्णांक ntfs_attr_find(स्थिर ATTR_TYPE type, स्थिर ntfsअक्षर *name,
		स्थिर u32 name_len, स्थिर IGNORE_CASE_BOOL ic,
		स्थिर u8 *val, स्थिर u32 val_len, ntfs_attr_search_ctx *ctx)
अणु
	ATTR_RECORD *a;
	ntfs_volume *vol = ctx->ntfs_ino->vol;
	ntfsअक्षर *upहाल = vol->upहाल;
	u32 upहाल_len = vol->upहाल_len;

	/*
	 * Iterate over attributes in mft record starting at @ctx->attr, or the
	 * attribute following that, अगर @ctx->is_first is 'true'.
	 */
	अगर (ctx->is_first) अणु
		a = ctx->attr;
		ctx->is_first = false;
	पूर्ण अन्यथा
		a = (ATTR_RECORD*)((u8*)ctx->attr +
				le32_to_cpu(ctx->attr->length));
	क्रम (;;	a = (ATTR_RECORD*)((u8*)a + le32_to_cpu(a->length))) अणु
		अगर ((u8*)a < (u8*)ctx->mrec || (u8*)a > (u8*)ctx->mrec +
				le32_to_cpu(ctx->mrec->bytes_allocated))
			अवरोध;
		ctx->attr = a;
		अगर (unlikely(le32_to_cpu(a->type) > le32_to_cpu(type) ||
				a->type == AT_END))
			वापस -ENOENT;
		अगर (unlikely(!a->length))
			अवरोध;
		अगर (a->type != type)
			जारी;
		/*
		 * If @name is present, compare the two names.  If @name is
		 * missing, assume we want an unnamed attribute.
		 */
		अगर (!name) अणु
			/* The search failed अगर the found attribute is named. */
			अगर (a->name_length)
				वापस -ENOENT;
		पूर्ण अन्यथा अगर (!ntfs_are_names_equal(name, name_len,
			    (ntfsअक्षर*)((u8*)a + le16_to_cpu(a->name_offset)),
			    a->name_length, ic, upहाल, upहाल_len)) अणु
			रेजिस्टर पूर्णांक rc;

			rc = ntfs_collate_names(name, name_len,
					(ntfsअक्षर*)((u8*)a +
					le16_to_cpu(a->name_offset)),
					a->name_length, 1, IGNORE_CASE,
					upहाल, upहाल_len);
			/*
			 * If @name collates beक्रमe a->name, there is no
			 * matching attribute.
			 */
			अगर (rc == -1)
				वापस -ENOENT;
			/* If the strings are not equal, जारी search. */
			अगर (rc)
				जारी;
			rc = ntfs_collate_names(name, name_len,
					(ntfsअक्षर*)((u8*)a +
					le16_to_cpu(a->name_offset)),
					a->name_length, 1, CASE_SENSITIVE,
					upहाल, upहाल_len);
			अगर (rc == -1)
				वापस -ENOENT;
			अगर (rc)
				जारी;
		पूर्ण
		/*
		 * The names match or @name not present and attribute is
		 * unnamed.  If no @val specअगरied, we have found the attribute
		 * and are करोne.
		 */
		अगर (!val)
			वापस 0;
		/* @val is present; compare values. */
		अन्यथा अणु
			रेजिस्टर पूर्णांक rc;

			rc = स_भेद(val, (u8*)a + le16_to_cpu(
					a->data.resident.value_offset),
					min_t(u32, val_len, le32_to_cpu(
					a->data.resident.value_length)));
			/*
			 * If @val collates beक्रमe the current attribute's
			 * value, there is no matching attribute.
			 */
			अगर (!rc) अणु
				रेजिस्टर u32 avl;

				avl = le32_to_cpu(
						a->data.resident.value_length);
				अगर (val_len == avl)
					वापस 0;
				अगर (val_len < avl)
					वापस -ENOENT;
			पूर्ण अन्यथा अगर (rc < 0)
				वापस -ENOENT;
		पूर्ण
	पूर्ण
	ntfs_error(vol->sb, "Inode is corrupt.  Run chkdsk.");
	NVolSetErrors(vol);
	वापस -EIO;
पूर्ण

/**
 * load_attribute_list - load an attribute list पूर्णांकo memory
 * @vol:		ntfs volume from which to पढ़ो
 * @runlist:		runlist of the attribute list
 * @al_start:		destination buffer
 * @size:		size of the destination buffer in bytes
 * @initialized_size:	initialized size of the attribute list
 *
 * Walk the runlist @runlist and load all clusters from it copying them पूर्णांकo
 * the linear buffer @al. The maximum number of bytes copied to @al is @size
 * bytes. Note, @size करोes not need to be a multiple of the cluster size. If
 * @initialized_size is less than @size, the region in @al between
 * @initialized_size and @size will be zeroed and not पढ़ो from disk.
 *
 * Return 0 on success or -त्रुटि_सं on error.
 */
पूर्णांक load_attribute_list(ntfs_volume *vol, runlist *runlist, u8 *al_start,
		स्थिर s64 size, स्थिर s64 initialized_size)
अणु
	LCN lcn;
	u8 *al = al_start;
	u8 *al_end = al + initialized_size;
	runlist_element *rl;
	काष्ठा buffer_head *bh;
	काष्ठा super_block *sb;
	अचिन्हित दीर्घ block_size;
	अचिन्हित दीर्घ block, max_block;
	पूर्णांक err = 0;
	अचिन्हित अक्षर block_size_bits;

	ntfs_debug("Entering.");
	अगर (!vol || !runlist || !al || size <= 0 || initialized_size < 0 ||
			initialized_size > size)
		वापस -EINVAL;
	अगर (!initialized_size) अणु
		स_रखो(al, 0, size);
		वापस 0;
	पूर्ण
	sb = vol->sb;
	block_size = sb->s_blocksize;
	block_size_bits = sb->s_blocksize_bits;
	करोwn_पढ़ो(&runlist->lock);
	rl = runlist->rl;
	अगर (!rl) अणु
		ntfs_error(sb, "Cannot read attribute list since runlist is "
				"missing.");
		जाओ err_out;	
	पूर्ण
	/* Read all clusters specअगरied by the runlist one run at a समय. */
	जबतक (rl->length) अणु
		lcn = ntfs_rl_vcn_to_lcn(rl, rl->vcn);
		ntfs_debug("Reading vcn = 0x%llx, lcn = 0x%llx.",
				(अचिन्हित दीर्घ दीर्घ)rl->vcn,
				(अचिन्हित दीर्घ दीर्घ)lcn);
		/* The attribute list cannot be sparse. */
		अगर (lcn < 0) अणु
			ntfs_error(sb, "ntfs_rl_vcn_to_lcn() failed.  Cannot "
					"read attribute list.");
			जाओ err_out;
		पूर्ण
		block = lcn << vol->cluster_size_bits >> block_size_bits;
		/* Read the run from device in chunks of block_size bytes. */
		max_block = block + (rl->length << vol->cluster_size_bits >>
				block_size_bits);
		ntfs_debug("max_block = 0x%lx.", max_block);
		करो अणु
			ntfs_debug("Reading block = 0x%lx.", block);
			bh = sb_bपढ़ो(sb, block);
			अगर (!bh) अणु
				ntfs_error(sb, "sb_bread() failed. Cannot "
						"read attribute list.");
				जाओ err_out;
			पूर्ण
			अगर (al + block_size >= al_end)
				जाओ करो_final;
			स_नकल(al, bh->b_data, block_size);
			brअन्यथा(bh);
			al += block_size;
		पूर्ण जबतक (++block < max_block);
		rl++;
	पूर्ण
	अगर (initialized_size < size) अणु
initialize:
		स_रखो(al_start + initialized_size, 0, size - initialized_size);
	पूर्ण
करोne:
	up_पढ़ो(&runlist->lock);
	वापस err;
करो_final:
	अगर (al < al_end) अणु
		/*
		 * Partial block.
		 *
		 * Note: The attribute list can be smaller than its allocation
		 * by multiple clusters.  This has been encountered by at least
		 * two people running Winकरोws XP, thus we cannot करो any
		 * truncation sanity checking here. (AIA)
		 */
		स_नकल(al, bh->b_data, al_end - al);
		brअन्यथा(bh);
		अगर (initialized_size < size)
			जाओ initialize;
		जाओ करोne;
	पूर्ण
	brअन्यथा(bh);
	/* Real overflow! */
	ntfs_error(sb, "Attribute list buffer overflow. Read attribute list "
			"is truncated.");
err_out:
	err = -EIO;
	जाओ करोne;
पूर्ण

/**
 * ntfs_बाह्यal_attr_find - find an attribute in the attribute list of an inode
 * @type:	attribute type to find
 * @name:	attribute name to find (optional, i.e. शून्य means करोn't care)
 * @name_len:	attribute name length (only needed अगर @name present)
 * @ic:		IGNORE_CASE or CASE_SENSITIVE (ignored अगर @name not present)
 * @lowest_vcn:	lowest vcn to find (optional, non-resident attributes only)
 * @val:	attribute value to find (optional, resident attributes only)
 * @val_len:	attribute value length
 * @ctx:	search context with mft record and attribute to search from
 *
 * You should not need to call this function directly.  Use ntfs_attr_lookup()
 * instead.
 *
 * Find an attribute by searching the attribute list क्रम the corresponding
 * attribute list entry.  Having found the entry, map the mft record अगर the
 * attribute is in a dअगरferent mft record/inode, ntfs_attr_find() the attribute
 * in there and वापस it.
 *
 * On first search @ctx->ntfs_ino must be the base mft record and @ctx must
 * have been obtained from a call to ntfs_attr_get_search_ctx().  On subsequent
 * calls @ctx->ntfs_ino can be any extent inode, too (@ctx->base_ntfs_ino is
 * then the base inode).
 *
 * After finishing with the attribute/mft record you need to call
 * ntfs_attr_put_search_ctx() to cleanup the search context (unmapping any
 * mapped inodes, etc).
 *
 * If the attribute is found, ntfs_बाह्यal_attr_find() वापसs 0 and
 * @ctx->attr will poपूर्णांक to the found attribute.  @ctx->mrec will poपूर्णांक to the
 * mft record in which @ctx->attr is located and @ctx->al_entry will poपूर्णांक to
 * the attribute list entry क्रम the attribute.
 *
 * If the attribute is not found, ntfs_बाह्यal_attr_find() वापसs -ENOENT and
 * @ctx->attr will poपूर्णांक to the attribute in the base mft record beक्रमe which
 * the attribute being searched क्रम would need to be inserted अगर such an action
 * were to be desired.  @ctx->mrec will poपूर्णांक to the mft record in which
 * @ctx->attr is located and @ctx->al_entry will poपूर्णांक to the attribute list
 * entry of the attribute beक्रमe which the attribute being searched क्रम would
 * need to be inserted अगर such an action were to be desired.
 *
 * Thus to insert the not found attribute, one wants to add the attribute to
 * @ctx->mrec (the base mft record) and अगर there is not enough space, the
 * attribute should be placed in a newly allocated extent mft record.  The
 * attribute list entry क्रम the inserted attribute should be inserted in the
 * attribute list attribute at @ctx->al_entry.
 *
 * On actual error, ntfs_बाह्यal_attr_find() वापसs -EIO.  In this हाल
 * @ctx->attr is undefined and in particular करो not rely on it not changing.
 */
अटल पूर्णांक ntfs_बाह्यal_attr_find(स्थिर ATTR_TYPE type,
		स्थिर ntfsअक्षर *name, स्थिर u32 name_len,
		स्थिर IGNORE_CASE_BOOL ic, स्थिर VCN lowest_vcn,
		स्थिर u8 *val, स्थिर u32 val_len, ntfs_attr_search_ctx *ctx)
अणु
	ntfs_inode *base_ni, *ni;
	ntfs_volume *vol;
	ATTR_LIST_ENTRY *al_entry, *next_al_entry;
	u8 *al_start, *al_end;
	ATTR_RECORD *a;
	ntfsअक्षर *al_name;
	u32 al_name_len;
	पूर्णांक err = 0;
	अटल स्थिर अक्षर *es = " Unmount and run chkdsk.";

	ni = ctx->ntfs_ino;
	base_ni = ctx->base_ntfs_ino;
	ntfs_debug("Entering for inode 0x%lx, type 0x%x.", ni->mft_no, type);
	अगर (!base_ni) अणु
		/* First call happens with the base mft record. */
		base_ni = ctx->base_ntfs_ino = ctx->ntfs_ino;
		ctx->base_mrec = ctx->mrec;
	पूर्ण
	अगर (ni == base_ni)
		ctx->base_attr = ctx->attr;
	अगर (type == AT_END)
		जाओ not_found;
	vol = base_ni->vol;
	al_start = base_ni->attr_list;
	al_end = al_start + base_ni->attr_list_size;
	अगर (!ctx->al_entry)
		ctx->al_entry = (ATTR_LIST_ENTRY*)al_start;
	/*
	 * Iterate over entries in attribute list starting at @ctx->al_entry,
	 * or the entry following that, अगर @ctx->is_first is 'true'.
	 */
	अगर (ctx->is_first) अणु
		al_entry = ctx->al_entry;
		ctx->is_first = false;
	पूर्ण अन्यथा
		al_entry = (ATTR_LIST_ENTRY*)((u8*)ctx->al_entry +
				le16_to_cpu(ctx->al_entry->length));
	क्रम (;; al_entry = next_al_entry) अणु
		/* Out of bounds check. */
		अगर ((u8*)al_entry < base_ni->attr_list ||
				(u8*)al_entry > al_end)
			अवरोध;	/* Inode is corrupt. */
		ctx->al_entry = al_entry;
		/* Catch the end of the attribute list. */
		अगर ((u8*)al_entry == al_end)
			जाओ not_found;
		अगर (!al_entry->length)
			अवरोध;
		अगर ((u8*)al_entry + 6 > al_end || (u8*)al_entry +
				le16_to_cpu(al_entry->length) > al_end)
			अवरोध;
		next_al_entry = (ATTR_LIST_ENTRY*)((u8*)al_entry +
				le16_to_cpu(al_entry->length));
		अगर (le32_to_cpu(al_entry->type) > le32_to_cpu(type))
			जाओ not_found;
		अगर (type != al_entry->type)
			जारी;
		/*
		 * If @name is present, compare the two names.  If @name is
		 * missing, assume we want an unnamed attribute.
		 */
		al_name_len = al_entry->name_length;
		al_name = (ntfsअक्षर*)((u8*)al_entry + al_entry->name_offset);
		अगर (!name) अणु
			अगर (al_name_len)
				जाओ not_found;
		पूर्ण अन्यथा अगर (!ntfs_are_names_equal(al_name, al_name_len, name,
				name_len, ic, vol->upहाल, vol->upहाल_len)) अणु
			रेजिस्टर पूर्णांक rc;

			rc = ntfs_collate_names(name, name_len, al_name,
					al_name_len, 1, IGNORE_CASE,
					vol->upहाल, vol->upहाल_len);
			/*
			 * If @name collates beक्रमe al_name, there is no
			 * matching attribute.
			 */
			अगर (rc == -1)
				जाओ not_found;
			/* If the strings are not equal, जारी search. */
			अगर (rc)
				जारी;
			/*
			 * FIXME: Reverse engineering showed 0, IGNORE_CASE but
			 * that is inconsistent with ntfs_attr_find().  The
			 * subsequent rc checks were also dअगरferent.  Perhaps I
			 * made a mistake in one of the two.  Need to recheck
			 * which is correct or at least see what is going on...
			 * (AIA)
			 */
			rc = ntfs_collate_names(name, name_len, al_name,
					al_name_len, 1, CASE_SENSITIVE,
					vol->upहाल, vol->upहाल_len);
			अगर (rc == -1)
				जाओ not_found;
			अगर (rc)
				जारी;
		पूर्ण
		/*
		 * The names match or @name not present and attribute is
		 * unnamed.  Now check @lowest_vcn.  Continue search अगर the
		 * next attribute list entry still fits @lowest_vcn.  Otherwise
		 * we have reached the right one or the search has failed.
		 */
		अगर (lowest_vcn && (u8*)next_al_entry >= al_start	    &&
				(u8*)next_al_entry + 6 < al_end		    &&
				(u8*)next_al_entry + le16_to_cpu(
					next_al_entry->length) <= al_end    &&
				sle64_to_cpu(next_al_entry->lowest_vcn) <=
					lowest_vcn			    &&
				next_al_entry->type == al_entry->type	    &&
				next_al_entry->name_length == al_name_len   &&
				ntfs_are_names_equal((ntfsअक्षर*)((u8*)
					next_al_entry +
					next_al_entry->name_offset),
					next_al_entry->name_length,
					al_name, al_name_len, CASE_SENSITIVE,
					vol->upहाल, vol->upहाल_len))
			जारी;
		अगर (MREF_LE(al_entry->mft_reference) == ni->mft_no) अणु
			अगर (MSEQNO_LE(al_entry->mft_reference) != ni->seq_no) अणु
				ntfs_error(vol->sb, "Found stale mft "
						"reference in attribute list "
						"of base inode 0x%lx.%s",
						base_ni->mft_no, es);
				err = -EIO;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु /* Mft references करो not match. */
			/* If there is a mapped record unmap it first. */
			अगर (ni != base_ni)
				unmap_extent_mft_record(ni);
			/* Do we want the base record back? */
			अगर (MREF_LE(al_entry->mft_reference) ==
					base_ni->mft_no) अणु
				ni = ctx->ntfs_ino = base_ni;
				ctx->mrec = ctx->base_mrec;
			पूर्ण अन्यथा अणु
				/* We want an extent record. */
				ctx->mrec = map_extent_mft_record(base_ni,
						le64_to_cpu(
						al_entry->mft_reference), &ni);
				अगर (IS_ERR(ctx->mrec)) अणु
					ntfs_error(vol->sb, "Failed to map "
							"extent mft record "
							"0x%lx of base inode "
							"0x%lx.%s",
							MREF_LE(al_entry->
							mft_reference),
							base_ni->mft_no, es);
					err = PTR_ERR(ctx->mrec);
					अगर (err == -ENOENT)
						err = -EIO;
					/* Cause @ctx to be sanitized below. */
					ni = शून्य;
					अवरोध;
				पूर्ण
				ctx->ntfs_ino = ni;
			पूर्ण
			ctx->attr = (ATTR_RECORD*)((u8*)ctx->mrec +
					le16_to_cpu(ctx->mrec->attrs_offset));
		पूर्ण
		/*
		 * ctx->vfs_ino, ctx->mrec, and ctx->attr now poपूर्णांक to the
		 * mft record containing the attribute represented by the
		 * current al_entry.
		 */
		/*
		 * We could call पूर्णांकo ntfs_attr_find() to find the right
		 * attribute in this mft record but this would be less
		 * efficient and not quite accurate as ntfs_attr_find() ignores
		 * the attribute instance numbers क्रम example which become
		 * important when one plays with attribute lists.  Also,
		 * because a proper match has been found in the attribute list
		 * entry above, the comparison can now be optimized.  So it is
		 * worth re-implementing a simplअगरied ntfs_attr_find() here.
		 */
		a = ctx->attr;
		/*
		 * Use a manual loop so we can still use अवरोध and जारी
		 * with the same meanings as above.
		 */
करो_next_attr_loop:
		अगर ((u8*)a < (u8*)ctx->mrec || (u8*)a > (u8*)ctx->mrec +
				le32_to_cpu(ctx->mrec->bytes_allocated))
			अवरोध;
		अगर (a->type == AT_END)
			अवरोध;
		अगर (!a->length)
			अवरोध;
		अगर (al_entry->instance != a->instance)
			जाओ करो_next_attr;
		/*
		 * If the type and/or the name are mismatched between the
		 * attribute list entry and the attribute record, there is
		 * corruption so we अवरोध and वापस error EIO.
		 */
		अगर (al_entry->type != a->type)
			अवरोध;
		अगर (!ntfs_are_names_equal((ntfsअक्षर*)((u8*)a +
				le16_to_cpu(a->name_offset)), a->name_length,
				al_name, al_name_len, CASE_SENSITIVE,
				vol->upहाल, vol->upहाल_len))
			अवरोध;
		ctx->attr = a;
		/*
		 * If no @val specअगरied or @val specअगरied and it matches, we
		 * have found it!
		 */
		अगर (!val || (!a->non_resident && le32_to_cpu(
				a->data.resident.value_length) == val_len &&
				!स_भेद((u8*)a +
				le16_to_cpu(a->data.resident.value_offset),
				val, val_len))) अणु
			ntfs_debug("Done, found.");
			वापस 0;
		पूर्ण
करो_next_attr:
		/* Proceed to the next attribute in the current mft record. */
		a = (ATTR_RECORD*)((u8*)a + le32_to_cpu(a->length));
		जाओ करो_next_attr_loop;
	पूर्ण
	अगर (!err) अणु
		ntfs_error(vol->sb, "Base inode 0x%lx contains corrupt "
				"attribute list attribute.%s", base_ni->mft_no,
				es);
		err = -EIO;
	पूर्ण
	अगर (ni != base_ni) अणु
		अगर (ni)
			unmap_extent_mft_record(ni);
		ctx->ntfs_ino = base_ni;
		ctx->mrec = ctx->base_mrec;
		ctx->attr = ctx->base_attr;
	पूर्ण
	अगर (err != -ENOMEM)
		NVolSetErrors(vol);
	वापस err;
not_found:
	/*
	 * If we were looking क्रम AT_END, we reset the search context @ctx and
	 * use ntfs_attr_find() to seek to the end of the base mft record.
	 */
	अगर (type == AT_END) अणु
		ntfs_attr_reinit_search_ctx(ctx);
		वापस ntfs_attr_find(AT_END, name, name_len, ic, val, val_len,
				ctx);
	पूर्ण
	/*
	 * The attribute was not found.  Beक्रमe we वापस, we want to ensure
	 * @ctx->mrec and @ctx->attr indicate the position at which the
	 * attribute should be inserted in the base mft record.  Since we also
	 * want to preserve @ctx->al_entry we cannot reinitialize the search
	 * context using ntfs_attr_reinit_search_ctx() as this would set
	 * @ctx->al_entry to शून्य.  Thus we करो the necessary bits manually (see
	 * ntfs_attr_init_search_ctx() below).  Note, we _only_ preserve
	 * @ctx->al_entry as the reमुख्यing fields (base_*) are identical to
	 * their non base_ counterparts and we cannot set @ctx->base_attr
	 * correctly yet as we करो not know what @ctx->attr will be set to by
	 * the call to ntfs_attr_find() below.
	 */
	अगर (ni != base_ni)
		unmap_extent_mft_record(ni);
	ctx->mrec = ctx->base_mrec;
	ctx->attr = (ATTR_RECORD*)((u8*)ctx->mrec +
			le16_to_cpu(ctx->mrec->attrs_offset));
	ctx->is_first = true;
	ctx->ntfs_ino = base_ni;
	ctx->base_ntfs_ino = शून्य;
	ctx->base_mrec = शून्य;
	ctx->base_attr = शून्य;
	/*
	 * In हाल there are multiple matches in the base mft record, need to
	 * keep क्रमागतerating until we get an attribute not found response (or
	 * another error), otherwise we would keep वापसing the same attribute
	 * over and over again and all programs using us क्रम क्रमागतeration would
	 * lock up in a tight loop.
	 */
	करो अणु
		err = ntfs_attr_find(type, name, name_len, ic, val, val_len,
				ctx);
	पूर्ण जबतक (!err);
	ntfs_debug("Done, not found.");
	वापस err;
पूर्ण

/**
 * ntfs_attr_lookup - find an attribute in an ntfs inode
 * @type:	attribute type to find
 * @name:	attribute name to find (optional, i.e. शून्य means करोn't care)
 * @name_len:	attribute name length (only needed अगर @name present)
 * @ic:		IGNORE_CASE or CASE_SENSITIVE (ignored अगर @name not present)
 * @lowest_vcn:	lowest vcn to find (optional, non-resident attributes only)
 * @val:	attribute value to find (optional, resident attributes only)
 * @val_len:	attribute value length
 * @ctx:	search context with mft record and attribute to search from
 *
 * Find an attribute in an ntfs inode.  On first search @ctx->ntfs_ino must
 * be the base mft record and @ctx must have been obtained from a call to
 * ntfs_attr_get_search_ctx().
 *
 * This function transparently handles attribute lists and @ctx is used to
 * जारी searches where they were left off at.
 *
 * After finishing with the attribute/mft record you need to call
 * ntfs_attr_put_search_ctx() to cleanup the search context (unmapping any
 * mapped inodes, etc).
 *
 * Return 0 अगर the search was successful and -त्रुटि_सं अगर not.
 *
 * When 0, @ctx->attr is the found attribute and it is in mft record
 * @ctx->mrec.  If an attribute list attribute is present, @ctx->al_entry is
 * the attribute list entry of the found attribute.
 *
 * When -ENOENT, @ctx->attr is the attribute which collates just after the
 * attribute being searched क्रम, i.e. अगर one wants to add the attribute to the
 * mft record this is the correct place to insert it पूर्णांकo.  If an attribute
 * list attribute is present, @ctx->al_entry is the attribute list entry which
 * collates just after the attribute list entry of the attribute being searched
 * क्रम, i.e. अगर one wants to add the attribute to the mft record this is the
 * correct place to insert its attribute list entry पूर्णांकo.
 *
 * When -त्रुटि_सं != -ENOENT, an error occurred during the lookup.  @ctx->attr is
 * then undefined and in particular you should not rely on it not changing.
 */
पूर्णांक ntfs_attr_lookup(स्थिर ATTR_TYPE type, स्थिर ntfsअक्षर *name,
		स्थिर u32 name_len, स्थिर IGNORE_CASE_BOOL ic,
		स्थिर VCN lowest_vcn, स्थिर u8 *val, स्थिर u32 val_len,
		ntfs_attr_search_ctx *ctx)
अणु
	ntfs_inode *base_ni;

	ntfs_debug("Entering.");
	BUG_ON(IS_ERR(ctx->mrec));
	अगर (ctx->base_ntfs_ino)
		base_ni = ctx->base_ntfs_ino;
	अन्यथा
		base_ni = ctx->ntfs_ino;
	/* Sanity check, just क्रम debugging really. */
	BUG_ON(!base_ni);
	अगर (!NInoAttrList(base_ni) || type == AT_ATTRIBUTE_LIST)
		वापस ntfs_attr_find(type, name, name_len, ic, val, val_len,
				ctx);
	वापस ntfs_बाह्यal_attr_find(type, name, name_len, ic, lowest_vcn,
			val, val_len, ctx);
पूर्ण

/**
 * ntfs_attr_init_search_ctx - initialize an attribute search context
 * @ctx:	attribute search context to initialize
 * @ni:		ntfs inode with which to initialize the search context
 * @mrec:	mft record with which to initialize the search context
 *
 * Initialize the attribute search context @ctx with @ni and @mrec.
 */
अटल अंतरभूत व्योम ntfs_attr_init_search_ctx(ntfs_attr_search_ctx *ctx,
		ntfs_inode *ni, MFT_RECORD *mrec)
अणु
	*ctx = (ntfs_attr_search_ctx) अणु
		.mrec = mrec,
		/* Sanity checks are perक्रमmed अन्यथाwhere. */
		.attr = (ATTR_RECORD*)((u8*)mrec +
				le16_to_cpu(mrec->attrs_offset)),
		.is_first = true,
		.ntfs_ino = ni,
	पूर्ण;
पूर्ण

/**
 * ntfs_attr_reinit_search_ctx - reinitialize an attribute search context
 * @ctx:	attribute search context to reinitialize
 *
 * Reinitialize the attribute search context @ctx, unmapping an associated
 * extent mft record अगर present, and initialize the search context again.
 *
 * This is used when a search क्रम a new attribute is being started to reset
 * the search context to the beginning.
 */
व्योम ntfs_attr_reinit_search_ctx(ntfs_attr_search_ctx *ctx)
अणु
	अगर (likely(!ctx->base_ntfs_ino)) अणु
		/* No attribute list. */
		ctx->is_first = true;
		/* Sanity checks are perक्रमmed अन्यथाwhere. */
		ctx->attr = (ATTR_RECORD*)((u8*)ctx->mrec +
				le16_to_cpu(ctx->mrec->attrs_offset));
		/*
		 * This needs resetting due to ntfs_बाह्यal_attr_find() which
		 * can leave it set despite having zeroed ctx->base_ntfs_ino.
		 */
		ctx->al_entry = शून्य;
		वापस;
	पूर्ण /* Attribute list. */
	अगर (ctx->ntfs_ino != ctx->base_ntfs_ino)
		unmap_extent_mft_record(ctx->ntfs_ino);
	ntfs_attr_init_search_ctx(ctx, ctx->base_ntfs_ino, ctx->base_mrec);
	वापस;
पूर्ण

/**
 * ntfs_attr_get_search_ctx - allocate/initialize a new attribute search context
 * @ni:		ntfs inode with which to initialize the search context
 * @mrec:	mft record with which to initialize the search context
 *
 * Allocate a new attribute search context, initialize it with @ni and @mrec,
 * and वापस it. Return शून्य अगर allocation failed.
 */
ntfs_attr_search_ctx *ntfs_attr_get_search_ctx(ntfs_inode *ni, MFT_RECORD *mrec)
अणु
	ntfs_attr_search_ctx *ctx;

	ctx = kmem_cache_alloc(ntfs_attr_ctx_cache, GFP_NOFS);
	अगर (ctx)
		ntfs_attr_init_search_ctx(ctx, ni, mrec);
	वापस ctx;
पूर्ण

/**
 * ntfs_attr_put_search_ctx - release an attribute search context
 * @ctx:	attribute search context to मुक्त
 *
 * Release the attribute search context @ctx, unmapping an associated extent
 * mft record अगर present.
 */
व्योम ntfs_attr_put_search_ctx(ntfs_attr_search_ctx *ctx)
अणु
	अगर (ctx->base_ntfs_ino && ctx->ntfs_ino != ctx->base_ntfs_ino)
		unmap_extent_mft_record(ctx->ntfs_ino);
	kmem_cache_मुक्त(ntfs_attr_ctx_cache, ctx);
	वापस;
पूर्ण

#अगर_घोषित NTFS_RW

/**
 * ntfs_attr_find_in_attrdef - find an attribute in the $AttrDef प्रणाली file
 * @vol:	ntfs volume to which the attribute beदीर्घs
 * @type:	attribute type which to find
 *
 * Search क्रम the attribute definition record corresponding to the attribute
 * @type in the $AttrDef प्रणाली file.
 *
 * Return the attribute type definition record अगर found and शून्य अगर not found.
 */
अटल ATTR_DEF *ntfs_attr_find_in_attrdef(स्थिर ntfs_volume *vol,
		स्थिर ATTR_TYPE type)
अणु
	ATTR_DEF *ad;

	BUG_ON(!vol->attrdef);
	BUG_ON(!type);
	क्रम (ad = vol->attrdef; (u8*)ad - (u8*)vol->attrdef <
			vol->attrdef_size && ad->type; ++ad) अणु
		/* We have not found it yet, carry on searching. */
		अगर (likely(le32_to_cpu(ad->type) < le32_to_cpu(type)))
			जारी;
		/* We found the attribute; वापस it. */
		अगर (likely(ad->type == type))
			वापस ad;
		/* We have gone too far alपढ़ोy.  No poपूर्णांक in continuing. */
		अवरोध;
	पूर्ण
	/* Attribute not found. */
	ntfs_debug("Attribute type 0x%x not found in $AttrDef.",
			le32_to_cpu(type));
	वापस शून्य;
पूर्ण

/**
 * ntfs_attr_size_bounds_check - check a size of an attribute type क्रम validity
 * @vol:	ntfs volume to which the attribute beदीर्घs
 * @type:	attribute type which to check
 * @size:	size which to check
 *
 * Check whether the @size in bytes is valid क्रम an attribute of @type on the
 * ntfs volume @vol.  This inक्रमmation is obtained from $AttrDef प्रणाली file.
 *
 * Return 0 अगर valid, -दुस्फल अगर not valid, or -ENOENT अगर the attribute is not
 * listed in $AttrDef.
 */
पूर्णांक ntfs_attr_size_bounds_check(स्थिर ntfs_volume *vol, स्थिर ATTR_TYPE type,
		स्थिर s64 size)
अणु
	ATTR_DEF *ad;

	BUG_ON(size < 0);
	/*
	 * $ATTRIBUTE_LIST has a maximum size of 256kiB, but this is not
	 * listed in $AttrDef.
	 */
	अगर (unlikely(type == AT_ATTRIBUTE_LIST && size > 256 * 1024))
		वापस -दुस्फल;
	/* Get the $AttrDef entry क्रम the attribute @type. */
	ad = ntfs_attr_find_in_attrdef(vol, type);
	अगर (unlikely(!ad))
		वापस -ENOENT;
	/* Do the bounds check. */
	अगर (((sle64_to_cpu(ad->min_size) > 0) &&
			size < sle64_to_cpu(ad->min_size)) ||
			((sle64_to_cpu(ad->max_size) > 0) && size >
			sle64_to_cpu(ad->max_size)))
		वापस -दुस्फल;
	वापस 0;
पूर्ण

/**
 * ntfs_attr_can_be_non_resident - check अगर an attribute can be non-resident
 * @vol:	ntfs volume to which the attribute beदीर्घs
 * @type:	attribute type which to check
 *
 * Check whether the attribute of @type on the ntfs volume @vol is allowed to
 * be non-resident.  This inक्रमmation is obtained from $AttrDef प्रणाली file.
 *
 * Return 0 अगर the attribute is allowed to be non-resident, -EPERM अगर not, and
 * -ENOENT अगर the attribute is not listed in $AttrDef.
 */
पूर्णांक ntfs_attr_can_be_non_resident(स्थिर ntfs_volume *vol, स्थिर ATTR_TYPE type)
अणु
	ATTR_DEF *ad;

	/* Find the attribute definition record in $AttrDef. */
	ad = ntfs_attr_find_in_attrdef(vol, type);
	अगर (unlikely(!ad))
		वापस -ENOENT;
	/* Check the flags and वापस the result. */
	अगर (ad->flags & ATTR_DEF_RESIDENT)
		वापस -EPERM;
	वापस 0;
पूर्ण

/**
 * ntfs_attr_can_be_resident - check अगर an attribute can be resident
 * @vol:	ntfs volume to which the attribute beदीर्घs
 * @type:	attribute type which to check
 *
 * Check whether the attribute of @type on the ntfs volume @vol is allowed to
 * be resident.  This inक्रमmation is derived from our ntfs knowledge and may
 * not be completely accurate, especially when user defined attributes are
 * present.  Basically we allow everything to be resident except क्रम index
 * allocation and $EA attributes.
 *
 * Return 0 अगर the attribute is allowed to be non-resident and -EPERM अगर not.
 *
 * Warning: In the प्रणाली file $MFT the attribute $Biपंचांगap must be non-resident
 *	    otherwise winकरोws will not boot (blue screen of death)!  We cannot
 *	    check क्रम this here as we करो not know which inode's $Biपंचांगap is
 *	    being asked about so the caller needs to special हाल this.
 */
पूर्णांक ntfs_attr_can_be_resident(स्थिर ntfs_volume *vol, स्थिर ATTR_TYPE type)
अणु
	अगर (type == AT_INDEX_ALLOCATION)
		वापस -EPERM;
	वापस 0;
पूर्ण

/**
 * ntfs_attr_record_resize - resize an attribute record
 * @m:		mft record containing attribute record
 * @a:		attribute record to resize
 * @new_size:	new size in bytes to which to resize the attribute record @a
 *
 * Resize the attribute record @a, i.e. the resident part of the attribute, in
 * the mft record @m to @new_size bytes.
 *
 * Return 0 on success and -त्रुटि_सं on error.  The following error codes are
 * defined:
 *	-ENOSPC	- Not enough space in the mft record @m to perक्रमm the resize.
 *
 * Note: On error, no modअगरications have been perक्रमmed whatsoever.
 *
 * Warning: If you make a record smaller without having copied all the data you
 *	    are पूर्णांकerested in the data may be overwritten.
 */
पूर्णांक ntfs_attr_record_resize(MFT_RECORD *m, ATTR_RECORD *a, u32 new_size)
अणु
	ntfs_debug("Entering for new_size %u.", new_size);
	/* Align to 8 bytes अगर it is not alपढ़ोy करोne. */
	अगर (new_size & 7)
		new_size = (new_size + 7) & ~7;
	/* If the actual attribute length has changed, move things around. */
	अगर (new_size != le32_to_cpu(a->length)) अणु
		u32 new_muse = le32_to_cpu(m->bytes_in_use) -
				le32_to_cpu(a->length) + new_size;
		/* Not enough space in this mft record. */
		अगर (new_muse > le32_to_cpu(m->bytes_allocated))
			वापस -ENOSPC;
		/* Move attributes following @a to their new location. */
		स_हटाओ((u8*)a + new_size, (u8*)a + le32_to_cpu(a->length),
				le32_to_cpu(m->bytes_in_use) - ((u8*)a -
				(u8*)m) - le32_to_cpu(a->length));
		/* Adjust @m to reflect the change in used space. */
		m->bytes_in_use = cpu_to_le32(new_muse);
		/* Adjust @a to reflect the new size. */
		अगर (new_size >= दुरत्व(ATTR_REC, length) + माप(a->length))
			a->length = cpu_to_le32(new_size);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ntfs_resident_attr_value_resize - resize the value of a resident attribute
 * @m:		mft record containing attribute record
 * @a:		attribute record whose value to resize
 * @new_size:	new size in bytes to which to resize the attribute value of @a
 *
 * Resize the value of the attribute @a in the mft record @m to @new_size bytes.
 * If the value is made bigger, the newly allocated space is cleared.
 *
 * Return 0 on success and -त्रुटि_सं on error.  The following error codes are
 * defined:
 *	-ENOSPC	- Not enough space in the mft record @m to perक्रमm the resize.
 *
 * Note: On error, no modअगरications have been perक्रमmed whatsoever.
 *
 * Warning: If you make a record smaller without having copied all the data you
 *	    are पूर्णांकerested in the data may be overwritten.
 */
पूर्णांक ntfs_resident_attr_value_resize(MFT_RECORD *m, ATTR_RECORD *a,
		स्थिर u32 new_size)
अणु
	u32 old_size;

	/* Resize the resident part of the attribute record. */
	अगर (ntfs_attr_record_resize(m, a,
			le16_to_cpu(a->data.resident.value_offset) + new_size))
		वापस -ENOSPC;
	/*
	 * The resize succeeded!  If we made the attribute value bigger, clear
	 * the area between the old size and @new_size.
	 */
	old_size = le32_to_cpu(a->data.resident.value_length);
	अगर (new_size > old_size)
		स_रखो((u8*)a + le16_to_cpu(a->data.resident.value_offset) +
				old_size, 0, new_size - old_size);
	/* Finally update the length of the attribute value. */
	a->data.resident.value_length = cpu_to_le32(new_size);
	वापस 0;
पूर्ण

/**
 * ntfs_attr_make_non_resident - convert a resident to a non-resident attribute
 * @ni:		ntfs inode describing the attribute to convert
 * @data_size:	size of the resident data to copy to the non-resident attribute
 *
 * Convert the resident ntfs attribute described by the ntfs inode @ni to a
 * non-resident one.
 *
 * @data_size must be equal to the attribute value size.  This is needed since
 * we need to know the size beक्रमe we can map the mft record and our callers
 * always know it.  The reason we cannot simply पढ़ो the size from the vfs
 * inode i_size is that this is not necessarily uptodate.  This happens when
 * ntfs_attr_make_non_resident() is called in the ->truncate call path(s).
 *
 * Return 0 on success and -त्रुटि_सं on error.  The following error वापस codes
 * are defined:
 *	-EPERM	- The attribute is not allowed to be non-resident.
 *	-ENOMEM	- Not enough memory.
 *	-ENOSPC	- Not enough disk space.
 *	-EINVAL	- Attribute not defined on the volume.
 *	-EIO	- I/o error or other error.
 * Note that -ENOSPC is also वापसed in the हाल that there is not enough
 * space in the mft record to करो the conversion.  This can happen when the mft
 * record is alपढ़ोy very full.  The caller is responsible क्रम trying to make
 * space in the mft record and trying again.  FIXME: Do we need a separate
 * error वापस code क्रम this kind of -ENOSPC or is it always worth trying
 * again in हाल the attribute may then fit in a resident state so no need to
 * make it non-resident at all?  Ho-hum...  (AIA)
 *
 * NOTE to self: No changes in the attribute list are required to move from
 *		 a resident to a non-resident attribute.
 *
 * Locking: - The caller must hold i_mutex on the inode.
 */
पूर्णांक ntfs_attr_make_non_resident(ntfs_inode *ni, स्थिर u32 data_size)
अणु
	s64 new_size;
	काष्ठा inode *vi = VFS_I(ni);
	ntfs_volume *vol = ni->vol;
	ntfs_inode *base_ni;
	MFT_RECORD *m;
	ATTR_RECORD *a;
	ntfs_attr_search_ctx *ctx;
	काष्ठा page *page;
	runlist_element *rl;
	u8 *kaddr;
	अचिन्हित दीर्घ flags;
	पूर्णांक mp_size, mp_ofs, name_ofs, arec_size, err, err2;
	u32 attr_size;
	u8 old_res_attr_flags;

	/* Check that the attribute is allowed to be non-resident. */
	err = ntfs_attr_can_be_non_resident(vol, ni->type);
	अगर (unlikely(err)) अणु
		अगर (err == -EPERM)
			ntfs_debug("Attribute is not allowed to be "
					"non-resident.");
		अन्यथा
			ntfs_debug("Attribute not defined on the NTFS "
					"volume!");
		वापस err;
	पूर्ण
	/*
	 * FIXME: Compressed and encrypted attributes are not supported when
	 * writing and we should never have gotten here क्रम them.
	 */
	BUG_ON(NInoCompressed(ni));
	BUG_ON(NInoEncrypted(ni));
	/*
	 * The size needs to be aligned to a cluster boundary क्रम allocation
	 * purposes.
	 */
	new_size = (data_size + vol->cluster_size - 1) &
			~(vol->cluster_size - 1);
	अगर (new_size > 0) अणु
		/*
		 * Will need the page later and since the page lock nests
		 * outside all ntfs locks, we need to get the page now.
		 */
		page = find_or_create_page(vi->i_mapping, 0,
				mapping_gfp_mask(vi->i_mapping));
		अगर (unlikely(!page))
			वापस -ENOMEM;
		/* Start by allocating clusters to hold the attribute value. */
		rl = ntfs_cluster_alloc(vol, 0, new_size >>
				vol->cluster_size_bits, -1, DATA_ZONE, true);
		अगर (IS_ERR(rl)) अणु
			err = PTR_ERR(rl);
			ntfs_debug("Failed to allocate cluster%s, error code "
					"%i.", (new_size >>
					vol->cluster_size_bits) > 1 ? "s" : "",
					err);
			जाओ page_err_out;
		पूर्ण
	पूर्ण अन्यथा अणु
		rl = शून्य;
		page = शून्य;
	पूर्ण
	/* Determine the size of the mapping pairs array. */
	mp_size = ntfs_get_size_क्रम_mapping_pairs(vol, rl, 0, -1);
	अगर (unlikely(mp_size < 0)) अणु
		err = mp_size;
		ntfs_debug("Failed to get size for mapping pairs array, error "
				"code %i.", err);
		जाओ rl_err_out;
	पूर्ण
	करोwn_ग_लिखो(&ni->runlist.lock);
	अगर (!NInoAttr(ni))
		base_ni = ni;
	अन्यथा
		base_ni = ni->ext.base_ntfs_ino;
	m = map_mft_record(base_ni);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		m = शून्य;
		ctx = शून्य;
		जाओ err_out;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(base_ni, m);
	अगर (unlikely(!ctx)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, ctx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT)
			err = -EIO;
		जाओ err_out;
	पूर्ण
	m = ctx->mrec;
	a = ctx->attr;
	BUG_ON(NInoNonResident(ni));
	BUG_ON(a->non_resident);
	/*
	 * Calculate new offsets क्रम the name and the mapping pairs array.
	 */
	अगर (NInoSparse(ni) || NInoCompressed(ni))
		name_ofs = (दुरत्व(ATTR_REC,
				data.non_resident.compressed_size) +
				माप(a->data.non_resident.compressed_size) +
				7) & ~7;
	अन्यथा
		name_ofs = (दुरत्व(ATTR_REC,
				data.non_resident.compressed_size) + 7) & ~7;
	mp_ofs = (name_ofs + a->name_length * माप(ntfsअक्षर) + 7) & ~7;
	/*
	 * Determine the size of the resident part of the now non-resident
	 * attribute record.
	 */
	arec_size = (mp_ofs + mp_size + 7) & ~7;
	/*
	 * If the page is not uptodate bring it uptodate by copying from the
	 * attribute value.
	 */
	attr_size = le32_to_cpu(a->data.resident.value_length);
	BUG_ON(attr_size != data_size);
	अगर (page && !PageUptodate(page)) अणु
		kaddr = kmap_atomic(page);
		स_नकल(kaddr, (u8*)a +
				le16_to_cpu(a->data.resident.value_offset),
				attr_size);
		स_रखो(kaddr + attr_size, 0, PAGE_SIZE - attr_size);
		kunmap_atomic(kaddr);
		flush_dcache_page(page);
		SetPageUptodate(page);
	पूर्ण
	/* Backup the attribute flag. */
	old_res_attr_flags = a->data.resident.flags;
	/* Resize the resident part of the attribute record. */
	err = ntfs_attr_record_resize(m, a, arec_size);
	अगर (unlikely(err))
		जाओ err_out;
	/*
	 * Convert the resident part of the attribute record to describe a
	 * non-resident attribute.
	 */
	a->non_resident = 1;
	/* Move the attribute name अगर it exists and update the offset. */
	अगर (a->name_length)
		स_हटाओ((u8*)a + name_ofs, (u8*)a + le16_to_cpu(a->name_offset),
				a->name_length * माप(ntfsअक्षर));
	a->name_offset = cpu_to_le16(name_ofs);
	/* Setup the fields specअगरic to non-resident attributes. */
	a->data.non_resident.lowest_vcn = 0;
	a->data.non_resident.highest_vcn = cpu_to_sle64((new_size - 1) >>
			vol->cluster_size_bits);
	a->data.non_resident.mapping_pairs_offset = cpu_to_le16(mp_ofs);
	स_रखो(&a->data.non_resident.reserved, 0,
			माप(a->data.non_resident.reserved));
	a->data.non_resident.allocated_size = cpu_to_sle64(new_size);
	a->data.non_resident.data_size =
			a->data.non_resident.initialized_size =
			cpu_to_sle64(attr_size);
	अगर (NInoSparse(ni) || NInoCompressed(ni)) अणु
		a->data.non_resident.compression_unit = 0;
		अगर (NInoCompressed(ni) || vol->major_ver < 3)
			a->data.non_resident.compression_unit = 4;
		a->data.non_resident.compressed_size =
				a->data.non_resident.allocated_size;
	पूर्ण अन्यथा
		a->data.non_resident.compression_unit = 0;
	/* Generate the mapping pairs array पूर्णांकo the attribute record. */
	err = ntfs_mapping_pairs_build(vol, (u8*)a + mp_ofs,
			arec_size - mp_ofs, rl, 0, -1, शून्य);
	अगर (unlikely(err)) अणु
		ntfs_debug("Failed to build mapping pairs, error code %i.",
				err);
		जाओ unकरो_err_out;
	पूर्ण
	/* Setup the in-memory attribute काष्ठाure to be non-resident. */
	ni->runlist.rl = rl;
	ग_लिखो_lock_irqsave(&ni->size_lock, flags);
	ni->allocated_size = new_size;
	अगर (NInoSparse(ni) || NInoCompressed(ni)) अणु
		ni->itype.compressed.size = ni->allocated_size;
		अगर (a->data.non_resident.compression_unit) अणु
			ni->itype.compressed.block_size = 1U << (a->data.
					non_resident.compression_unit +
					vol->cluster_size_bits);
			ni->itype.compressed.block_size_bits =
					ffs(ni->itype.compressed.block_size) -
					1;
			ni->itype.compressed.block_clusters = 1U <<
					a->data.non_resident.compression_unit;
		पूर्ण अन्यथा अणु
			ni->itype.compressed.block_size = 0;
			ni->itype.compressed.block_size_bits = 0;
			ni->itype.compressed.block_clusters = 0;
		पूर्ण
		vi->i_blocks = ni->itype.compressed.size >> 9;
	पूर्ण अन्यथा
		vi->i_blocks = ni->allocated_size >> 9;
	ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
	/*
	 * This needs to be last since the address space operations ->पढ़ोpage
	 * and ->ग_लिखोpage can run concurrently with us as they are not
	 * serialized on i_mutex.  Note, we are not allowed to fail once we flip
	 * this चयन, which is another reason to करो this last.
	 */
	NInoSetNonResident(ni);
	/* Mark the mft record dirty, so it माला_लो written back. */
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(base_ni);
	up_ग_लिखो(&ni->runlist.lock);
	अगर (page) अणु
		set_page_dirty(page);
		unlock_page(page);
		put_page(page);
	पूर्ण
	ntfs_debug("Done.");
	वापस 0;
unकरो_err_out:
	/* Convert the attribute back पूर्णांकo a resident attribute. */
	a->non_resident = 0;
	/* Move the attribute name अगर it exists and update the offset. */
	name_ofs = (दुरत्व(ATTR_RECORD, data.resident.reserved) +
			माप(a->data.resident.reserved) + 7) & ~7;
	अगर (a->name_length)
		स_हटाओ((u8*)a + name_ofs, (u8*)a + le16_to_cpu(a->name_offset),
				a->name_length * माप(ntfsअक्षर));
	mp_ofs = (name_ofs + a->name_length * माप(ntfsअक्षर) + 7) & ~7;
	a->name_offset = cpu_to_le16(name_ofs);
	arec_size = (mp_ofs + attr_size + 7) & ~7;
	/* Resize the resident part of the attribute record. */
	err2 = ntfs_attr_record_resize(m, a, arec_size);
	अगर (unlikely(err2)) अणु
		/*
		 * This cannot happen (well अगर memory corruption is at work it
		 * could happen in theory), but deal with it as well as we can.
		 * If the old size is too small, truncate the attribute,
		 * otherwise simply give it a larger allocated size.
		 * FIXME: Should check whether chkdsk complains when the
		 * allocated size is much bigger than the resident value size.
		 */
		arec_size = le32_to_cpu(a->length);
		अगर ((mp_ofs + attr_size) > arec_size) अणु
			err2 = attr_size;
			attr_size = arec_size - mp_ofs;
			ntfs_error(vol->sb, "Failed to undo partial resident "
					"to non-resident attribute "
					"conversion.  Truncating inode 0x%lx, "
					"attribute type 0x%x from %i bytes to "
					"%i bytes to maintain metadata "
					"consistency.  THIS MEANS YOU ARE "
					"LOSING %i BYTES DATA FROM THIS %s.",
					vi->i_ino,
					(अचिन्हित)le32_to_cpu(ni->type),
					err2, attr_size, err2 - attr_size,
					((ni->type == AT_DATA) &&
					!ni->name_len) ? "FILE": "ATTRIBUTE");
			ग_लिखो_lock_irqsave(&ni->size_lock, flags);
			ni->initialized_size = attr_size;
			i_size_ग_लिखो(vi, attr_size);
			ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
		पूर्ण
	पूर्ण
	/* Setup the fields specअगरic to resident attributes. */
	a->data.resident.value_length = cpu_to_le32(attr_size);
	a->data.resident.value_offset = cpu_to_le16(mp_ofs);
	a->data.resident.flags = old_res_attr_flags;
	स_रखो(&a->data.resident.reserved, 0,
			माप(a->data.resident.reserved));
	/* Copy the data from the page back to the attribute value. */
	अगर (page) अणु
		kaddr = kmap_atomic(page);
		स_नकल((u8*)a + mp_ofs, kaddr, attr_size);
		kunmap_atomic(kaddr);
	पूर्ण
	/* Setup the allocated size in the ntfs inode in हाल it changed. */
	ग_लिखो_lock_irqsave(&ni->size_lock, flags);
	ni->allocated_size = arec_size - mp_ofs;
	ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
	/* Mark the mft record dirty, so it माला_लो written back. */
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
err_out:
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(base_ni);
	ni->runlist.rl = शून्य;
	up_ग_लिखो(&ni->runlist.lock);
rl_err_out:
	अगर (rl) अणु
		अगर (ntfs_cluster_मुक्त_from_rl(vol, rl) < 0) अणु
			ntfs_error(vol->sb, "Failed to release allocated "
					"cluster(s) in error code path.  Run "
					"chkdsk to recover the lost "
					"cluster(s).");
			NVolSetErrors(vol);
		पूर्ण
		ntfs_मुक्त(rl);
page_err_out:
		unlock_page(page);
		put_page(page);
	पूर्ण
	अगर (err == -EINVAL)
		err = -EIO;
	वापस err;
पूर्ण

/**
 * ntfs_attr_extend_allocation - extend the allocated space of an attribute
 * @ni:			ntfs inode of the attribute whose allocation to extend
 * @new_alloc_size:	new size in bytes to which to extend the allocation to
 * @new_data_size:	new size in bytes to which to extend the data to
 * @data_start:		beginning of region which is required to be non-sparse
 *
 * Extend the allocated space of an attribute described by the ntfs inode @ni
 * to @new_alloc_size bytes.  If @data_start is -1, the whole extension may be
 * implemented as a hole in the file (as दीर्घ as both the volume and the ntfs
 * inode @ni have sparse support enabled).  If @data_start is >= 0, then the
 * region between the old allocated size and @data_start - 1 may be made sparse
 * but the regions between @data_start and @new_alloc_size must be backed by
 * actual clusters.
 *
 * If @new_data_size is -1, it is ignored.  If it is >= 0, then the data size
 * of the attribute is extended to @new_data_size.  Note that the i_size of the
 * vfs inode is not updated.  Only the data size in the base attribute record
 * is updated.  The caller has to update i_size separately अगर this is required.
 * WARNING: It is a BUG() क्रम @new_data_size to be smaller than the old data
 * size as well as क्रम @new_data_size to be greater than @new_alloc_size.
 *
 * For resident attributes this involves resizing the attribute record and अगर
 * necessary moving it and/or other attributes पूर्णांकo extent mft records and/or
 * converting the attribute to a non-resident attribute which in turn involves
 * extending the allocation of a non-resident attribute as described below.
 *
 * For non-resident attributes this involves allocating clusters in the data
 * zone on the volume (except क्रम regions that are being made sparse) and
 * extending the run list to describe the allocated clusters as well as
 * updating the mapping pairs array of the attribute.  This in turn involves
 * resizing the attribute record and अगर necessary moving it and/or other
 * attributes पूर्णांकo extent mft records and/or splitting the attribute record
 * पूर्णांकo multiple extent attribute records.
 *
 * Also, the attribute list attribute is updated अगर present and in some of the
 * above हालs (the ones where extent mft records/attributes come पूर्णांकo play),
 * an attribute list attribute is created अगर not alपढ़ोy present.
 *
 * Return the new allocated size on success and -त्रुटि_सं on error.  In the हाल
 * that an error is encountered but a partial extension at least up to
 * @data_start (अगर present) is possible, the allocation is partially extended
 * and this is वापसed.  This means the caller must check the वापसed size to
 * determine अगर the extension was partial.  If @data_start is -1 then partial
 * allocations are not perक्रमmed.
 *
 * WARNING: Do not call ntfs_attr_extend_allocation() क्रम $MFT/$DATA.
 *
 * Locking: This function takes the runlist lock of @ni क्रम writing as well as
 * locking the mft record of the base ntfs inode.  These locks are मुख्यtained
 * throughout execution of the function.  These locks are required so that the
 * attribute can be resized safely and so that it can क्रम example be converted
 * from resident to non-resident safely.
 *
 * TODO: At present attribute list attribute handling is not implemented.
 *
 * TODO: At present it is not safe to call this function क्रम anything other
 * than the $DATA attribute(s) of an uncompressed and unencrypted file.
 */
s64 ntfs_attr_extend_allocation(ntfs_inode *ni, s64 new_alloc_size,
		स्थिर s64 new_data_size, स्थिर s64 data_start)
अणु
	VCN vcn;
	s64 ll, allocated_size, start = data_start;
	काष्ठा inode *vi = VFS_I(ni);
	ntfs_volume *vol = ni->vol;
	ntfs_inode *base_ni;
	MFT_RECORD *m;
	ATTR_RECORD *a;
	ntfs_attr_search_ctx *ctx;
	runlist_element *rl, *rl2;
	अचिन्हित दीर्घ flags;
	पूर्णांक err, mp_size;
	u32 attr_len = 0; /* Silence stupid gcc warning. */
	bool mp_rebuilt;

#अगर_घोषित DEBUG
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	allocated_size = ni->allocated_size;
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	ntfs_debug("Entering for i_ino 0x%lx, attribute type 0x%x, "
			"old_allocated_size 0x%llx, "
			"new_allocated_size 0x%llx, new_data_size 0x%llx, "
			"data_start 0x%llx.", vi->i_ino,
			(अचिन्हित)le32_to_cpu(ni->type),
			(अचिन्हित दीर्घ दीर्घ)allocated_size,
			(अचिन्हित दीर्घ दीर्घ)new_alloc_size,
			(अचिन्हित दीर्घ दीर्घ)new_data_size,
			(अचिन्हित दीर्घ दीर्घ)start);
#पूर्ण_अगर
retry_extend:
	/*
	 * For non-resident attributes, @start and @new_size need to be aligned
	 * to cluster boundaries क्रम allocation purposes.
	 */
	अगर (NInoNonResident(ni)) अणु
		अगर (start > 0)
			start &= ~(s64)vol->cluster_size_mask;
		new_alloc_size = (new_alloc_size + vol->cluster_size - 1) &
				~(s64)vol->cluster_size_mask;
	पूर्ण
	BUG_ON(new_data_size >= 0 && new_data_size > new_alloc_size);
	/* Check अगर new size is allowed in $AttrDef. */
	err = ntfs_attr_size_bounds_check(vol, ni->type, new_alloc_size);
	अगर (unlikely(err)) अणु
		/* Only emit errors when the ग_लिखो will fail completely. */
		पढ़ो_lock_irqsave(&ni->size_lock, flags);
		allocated_size = ni->allocated_size;
		पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
		अगर (start < 0 || start >= allocated_size) अणु
			अगर (err == -दुस्फल) अणु
				ntfs_error(vol->sb, "Cannot extend allocation "
						"of inode 0x%lx, attribute "
						"type 0x%x, because the new "
						"allocation would exceed the "
						"maximum allowed size for "
						"this attribute type.",
						vi->i_ino, (अचिन्हित)
						le32_to_cpu(ni->type));
			पूर्ण अन्यथा अणु
				ntfs_error(vol->sb, "Cannot extend allocation "
						"of inode 0x%lx, attribute "
						"type 0x%x, because this "
						"attribute type is not "
						"defined on the NTFS volume.  "
						"Possible corruption!  You "
						"should run chkdsk!",
						vi->i_ino, (अचिन्हित)
						le32_to_cpu(ni->type));
			पूर्ण
		पूर्ण
		/* Translate error code to be POSIX conक्रमmant क्रम ग_लिखो(2). */
		अगर (err == -दुस्फल)
			err = -EFBIG;
		अन्यथा
			err = -EIO;
		वापस err;
	पूर्ण
	अगर (!NInoAttr(ni))
		base_ni = ni;
	अन्यथा
		base_ni = ni->ext.base_ntfs_ino;
	/*
	 * We will be modअगरying both the runlist (अगर non-resident) and the mft
	 * record so lock them both करोwn.
	 */
	करोwn_ग_लिखो(&ni->runlist.lock);
	m = map_mft_record(base_ni);
	अगर (IS_ERR(m)) अणु
		err = PTR_ERR(m);
		m = शून्य;
		ctx = शून्य;
		जाओ err_out;
	पूर्ण
	ctx = ntfs_attr_get_search_ctx(base_ni, m);
	अगर (unlikely(!ctx)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	allocated_size = ni->allocated_size;
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	/*
	 * If non-resident, seek to the last extent.  If resident, there is
	 * only one extent, so seek to that.
	 */
	vcn = NInoNonResident(ni) ? allocated_size >> vol->cluster_size_bits :
			0;
	/*
	 * Abort अगर someone did the work whilst we रुकोed क्रम the locks.  If we
	 * just converted the attribute from resident to non-resident it is
	 * likely that exactly this has happened alपढ़ोy.  We cannot quite
	 * पात अगर we need to update the data size.
	 */
	अगर (unlikely(new_alloc_size <= allocated_size)) अणु
		ntfs_debug("Allocated size already exceeds requested size.");
		new_alloc_size = allocated_size;
		अगर (new_data_size < 0)
			जाओ करोne;
		/*
		 * We want the first attribute extent so that we can update the
		 * data size.
		 */
		vcn = 0;
	पूर्ण
	err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
			CASE_SENSITIVE, vcn, शून्य, 0, ctx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT)
			err = -EIO;
		जाओ err_out;
	पूर्ण
	m = ctx->mrec;
	a = ctx->attr;
	/* Use जाओ to reduce indentation. */
	अगर (a->non_resident)
		जाओ करो_non_resident_extend;
	BUG_ON(NInoNonResident(ni));
	/* The total length of the attribute value. */
	attr_len = le32_to_cpu(a->data.resident.value_length);
	/*
	 * Extend the attribute record to be able to store the new attribute
	 * size.  ntfs_attr_record_resize() will not करो anything अगर the size is
	 * not changing.
	 */
	अगर (new_alloc_size < vol->mft_record_size &&
			!ntfs_attr_record_resize(m, a,
			le16_to_cpu(a->data.resident.value_offset) +
			new_alloc_size)) अणु
		/* The resize succeeded! */
		ग_लिखो_lock_irqsave(&ni->size_lock, flags);
		ni->allocated_size = le32_to_cpu(a->length) -
				le16_to_cpu(a->data.resident.value_offset);
		ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
		अगर (new_data_size >= 0) अणु
			BUG_ON(new_data_size < attr_len);
			a->data.resident.value_length =
					cpu_to_le32((u32)new_data_size);
		पूर्ण
		जाओ flush_करोne;
	पूर्ण
	/*
	 * We have to drop all the locks so we can call
	 * ntfs_attr_make_non_resident().  This could be optimised by try-
	 * locking the first page cache page and only अगर that fails dropping
	 * the locks, locking the page, and reकरोing all the locking and
	 * lookups.  While this would be a huge optimisation, it is not worth
	 * it as this is definitely a slow code path.
	 */
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(base_ni);
	up_ग_लिखो(&ni->runlist.lock);
	/*
	 * Not enough space in the mft record, try to make the attribute
	 * non-resident and अगर successful restart the extension process.
	 */
	err = ntfs_attr_make_non_resident(ni, attr_len);
	अगर (likely(!err))
		जाओ retry_extend;
	/*
	 * Could not make non-resident.  If this is due to this not being
	 * permitted क्रम this attribute type or there not being enough space,
	 * try to make other attributes non-resident.  Otherwise fail.
	 */
	अगर (unlikely(err != -EPERM && err != -ENOSPC)) अणु
		/* Only emit errors when the ग_लिखो will fail completely. */
		पढ़ो_lock_irqsave(&ni->size_lock, flags);
		allocated_size = ni->allocated_size;
		पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
		अगर (start < 0 || start >= allocated_size)
			ntfs_error(vol->sb, "Cannot extend allocation of "
					"inode 0x%lx, attribute type 0x%x, "
					"because the conversion from resident "
					"to non-resident attribute failed "
					"with error code %i.", vi->i_ino,
					(अचिन्हित)le32_to_cpu(ni->type), err);
		अगर (err != -ENOMEM)
			err = -EIO;
		जाओ conv_err_out;
	पूर्ण
	/* TODO: Not implemented from here, पात. */
	पढ़ो_lock_irqsave(&ni->size_lock, flags);
	allocated_size = ni->allocated_size;
	पढ़ो_unlock_irqrestore(&ni->size_lock, flags);
	अगर (start < 0 || start >= allocated_size) अणु
		अगर (err == -ENOSPC)
			ntfs_error(vol->sb, "Not enough space in the mft "
					"record/on disk for the non-resident "
					"attribute value.  This case is not "
					"implemented yet.");
		अन्यथा /* अगर (err == -EPERM) */
			ntfs_error(vol->sb, "This attribute type may not be "
					"non-resident.  This case is not "
					"implemented yet.");
	पूर्ण
	err = -EOPNOTSUPP;
	जाओ conv_err_out;
#अगर 0
	// TODO: Attempt to make other attributes non-resident.
	अगर (!err)
		जाओ करो_resident_extend;
	/*
	 * Both the attribute list attribute and the standard inक्रमmation
	 * attribute must reमुख्य in the base inode.  Thus, अगर this is one of
	 * these attributes, we have to try to move other attributes out पूर्णांकo
	 * extent mft records instead.
	 */
	अगर (ni->type == AT_ATTRIBUTE_LIST ||
			ni->type == AT_STANDARD_INFORMATION) अणु
		// TODO: Attempt to move other attributes पूर्णांकo extent mft
		// records.
		err = -EOPNOTSUPP;
		अगर (!err)
			जाओ करो_resident_extend;
		जाओ err_out;
	पूर्ण
	// TODO: Attempt to move this attribute to an extent mft record, but
	// only अगर it is not alपढ़ोy the only attribute in an mft record in
	// which हाल there would be nothing to gain.
	err = -EOPNOTSUPP;
	अगर (!err)
		जाओ करो_resident_extend;
	/* There is nothing we can करो to make enough space. )-: */
	जाओ err_out;
#पूर्ण_अगर
करो_non_resident_extend:
	BUG_ON(!NInoNonResident(ni));
	अगर (new_alloc_size == allocated_size) अणु
		BUG_ON(vcn);
		जाओ alloc_करोne;
	पूर्ण
	/*
	 * If the data starts after the end of the old allocation, this is a
	 * $DATA attribute and sparse attributes are enabled on the volume and
	 * क्रम this inode, then create a sparse region between the old
	 * allocated size and the start of the data.  Otherwise simply proceed
	 * with filling the whole space between the old allocated size and the
	 * new allocated size with clusters.
	 */
	अगर ((start >= 0 && start <= allocated_size) || ni->type != AT_DATA ||
			!NVolSparseEnabled(vol) || NInoSparseDisabled(ni))
		जाओ skip_sparse;
	// TODO: This is not implemented yet.  We just fill in with real
	// clusters क्रम now...
	ntfs_debug("Inserting holes is not-implemented yet.  Falling back to "
			"allocating real clusters instead.");
skip_sparse:
	rl = ni->runlist.rl;
	अगर (likely(rl)) अणु
		/* Seek to the end of the runlist. */
		जबतक (rl->length)
			rl++;
	पूर्ण
	/* If this attribute extent is not mapped, map it now. */
	अगर (unlikely(!rl || rl->lcn == LCN_RL_NOT_MAPPED ||
			(rl->lcn == LCN_ENOENT && rl > ni->runlist.rl &&
			(rl-1)->lcn == LCN_RL_NOT_MAPPED))) अणु
		अगर (!rl && !allocated_size)
			जाओ first_alloc;
		rl = ntfs_mapping_pairs_decompress(vol, a, ni->runlist.rl);
		अगर (IS_ERR(rl)) अणु
			err = PTR_ERR(rl);
			अगर (start < 0 || start >= allocated_size)
				ntfs_error(vol->sb, "Cannot extend allocation "
						"of inode 0x%lx, attribute "
						"type 0x%x, because the "
						"mapping of a runlist "
						"fragment failed with error "
						"code %i.", vi->i_ino,
						(अचिन्हित)le32_to_cpu(ni->type),
						err);
			अगर (err != -ENOMEM)
				err = -EIO;
			जाओ err_out;
		पूर्ण
		ni->runlist.rl = rl;
		/* Seek to the end of the runlist. */
		जबतक (rl->length)
			rl++;
	पूर्ण
	/*
	 * We now know the runlist of the last extent is mapped and @rl is at
	 * the end of the runlist.  We want to begin allocating clusters
	 * starting at the last allocated cluster to reduce fragmentation.  If
	 * there are no valid LCNs in the attribute we let the cluster
	 * allocator choose the starting cluster.
	 */
	/* If the last LCN is a hole or simillar seek back to last real LCN. */
	जबतक (rl->lcn < 0 && rl > ni->runlist.rl)
		rl--;
first_alloc:
	// FIXME: Need to implement partial allocations so at least part of the
	// ग_लिखो can be perक्रमmed when start >= 0.  (Needed क्रम POSIX ग_लिखो(2)
	// conक्रमmance.)
	rl2 = ntfs_cluster_alloc(vol, allocated_size >> vol->cluster_size_bits,
			(new_alloc_size - allocated_size) >>
			vol->cluster_size_bits, (rl && (rl->lcn >= 0)) ?
			rl->lcn + rl->length : -1, DATA_ZONE, true);
	अगर (IS_ERR(rl2)) अणु
		err = PTR_ERR(rl2);
		अगर (start < 0 || start >= allocated_size)
			ntfs_error(vol->sb, "Cannot extend allocation of "
					"inode 0x%lx, attribute type 0x%x, "
					"because the allocation of clusters "
					"failed with error code %i.", vi->i_ino,
					(अचिन्हित)le32_to_cpu(ni->type), err);
		अगर (err != -ENOMEM && err != -ENOSPC)
			err = -EIO;
		जाओ err_out;
	पूर्ण
	rl = ntfs_runlists_merge(ni->runlist.rl, rl2);
	अगर (IS_ERR(rl)) अणु
		err = PTR_ERR(rl);
		अगर (start < 0 || start >= allocated_size)
			ntfs_error(vol->sb, "Cannot extend allocation of "
					"inode 0x%lx, attribute type 0x%x, "
					"because the runlist merge failed "
					"with error code %i.", vi->i_ino,
					(अचिन्हित)le32_to_cpu(ni->type), err);
		अगर (err != -ENOMEM)
			err = -EIO;
		अगर (ntfs_cluster_मुक्त_from_rl(vol, rl2)) अणु
			ntfs_error(vol->sb, "Failed to release allocated "
					"cluster(s) in error code path.  Run "
					"chkdsk to recover the lost "
					"cluster(s).");
			NVolSetErrors(vol);
		पूर्ण
		ntfs_मुक्त(rl2);
		जाओ err_out;
	पूर्ण
	ni->runlist.rl = rl;
	ntfs_debug("Allocated 0x%llx clusters.", (दीर्घ दीर्घ)(new_alloc_size -
			allocated_size) >> vol->cluster_size_bits);
	/* Find the runlist element with which the attribute extent starts. */
	ll = sle64_to_cpu(a->data.non_resident.lowest_vcn);
	rl2 = ntfs_rl_find_vcn_nolock(rl, ll);
	BUG_ON(!rl2);
	BUG_ON(!rl2->length);
	BUG_ON(rl2->lcn < LCN_HOLE);
	mp_rebuilt = false;
	/* Get the size क्रम the new mapping pairs array क्रम this extent. */
	mp_size = ntfs_get_size_क्रम_mapping_pairs(vol, rl2, ll, -1);
	अगर (unlikely(mp_size <= 0)) अणु
		err = mp_size;
		अगर (start < 0 || start >= allocated_size)
			ntfs_error(vol->sb, "Cannot extend allocation of "
					"inode 0x%lx, attribute type 0x%x, "
					"because determining the size for the "
					"mapping pairs failed with error code "
					"%i.", vi->i_ino,
					(अचिन्हित)le32_to_cpu(ni->type), err);
		err = -EIO;
		जाओ unकरो_alloc;
	पूर्ण
	/* Extend the attribute record to fit the bigger mapping pairs array. */
	attr_len = le32_to_cpu(a->length);
	err = ntfs_attr_record_resize(m, a, mp_size +
			le16_to_cpu(a->data.non_resident.mapping_pairs_offset));
	अगर (unlikely(err)) अणु
		BUG_ON(err != -ENOSPC);
		// TODO: Deal with this by moving this extent to a new mft
		// record or by starting a new extent in a new mft record,
		// possibly by extending this extent partially and filling it
		// and creating a new extent क्रम the reमुख्यder, or by making
		// other attributes non-resident and/or by moving other
		// attributes out of this mft record.
		अगर (start < 0 || start >= allocated_size)
			ntfs_error(vol->sb, "Not enough space in the mft "
					"record for the extended attribute "
					"record.  This case is not "
					"implemented yet.");
		err = -EOPNOTSUPP;
		जाओ unकरो_alloc;
	पूर्ण
	mp_rebuilt = true;
	/* Generate the mapping pairs array directly पूर्णांकo the attr record. */
	err = ntfs_mapping_pairs_build(vol, (u8*)a +
			le16_to_cpu(a->data.non_resident.mapping_pairs_offset),
			mp_size, rl2, ll, -1, शून्य);
	अगर (unlikely(err)) अणु
		अगर (start < 0 || start >= allocated_size)
			ntfs_error(vol->sb, "Cannot extend allocation of "
					"inode 0x%lx, attribute type 0x%x, "
					"because building the mapping pairs "
					"failed with error code %i.", vi->i_ino,
					(अचिन्हित)le32_to_cpu(ni->type), err);
		err = -EIO;
		जाओ unकरो_alloc;
	पूर्ण
	/* Update the highest_vcn. */
	a->data.non_resident.highest_vcn = cpu_to_sle64((new_alloc_size >>
			vol->cluster_size_bits) - 1);
	/*
	 * We now have extended the allocated size of the attribute.  Reflect
	 * this in the ntfs_inode काष्ठाure and the attribute record.
	 */
	अगर (a->data.non_resident.lowest_vcn) अणु
		/*
		 * We are not in the first attribute extent, चयन to it, but
		 * first ensure the changes will make it to disk later.
		 */
		flush_dcache_mft_record_page(ctx->ntfs_ino);
		mark_mft_record_dirty(ctx->ntfs_ino);
		ntfs_attr_reinit_search_ctx(ctx);
		err = ntfs_attr_lookup(ni->type, ni->name, ni->name_len,
				CASE_SENSITIVE, 0, शून्य, 0, ctx);
		अगर (unlikely(err))
			जाओ restore_unकरो_alloc;
		/* @m is not used any more so no need to set it. */
		a = ctx->attr;
	पूर्ण
	ग_लिखो_lock_irqsave(&ni->size_lock, flags);
	ni->allocated_size = new_alloc_size;
	a->data.non_resident.allocated_size = cpu_to_sle64(new_alloc_size);
	/*
	 * FIXME: This would fail अगर @ni is a directory, $MFT, or an index,
	 * since those can have sparse/compressed set.  For example can be
	 * set compressed even though it is not compressed itself and in that
	 * हाल the bit means that files are to be created compressed in the
	 * directory...  At present this is ok as this code is only called क्रम
	 * regular files, and only क्रम their $DATA attribute(s).
	 * FIXME: The calculation is wrong अगर we created a hole above.  For now
	 * it करोes not matter as we never create holes.
	 */
	अगर (NInoSparse(ni) || NInoCompressed(ni)) अणु
		ni->itype.compressed.size += new_alloc_size - allocated_size;
		a->data.non_resident.compressed_size =
				cpu_to_sle64(ni->itype.compressed.size);
		vi->i_blocks = ni->itype.compressed.size >> 9;
	पूर्ण अन्यथा
		vi->i_blocks = new_alloc_size >> 9;
	ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
alloc_करोne:
	अगर (new_data_size >= 0) अणु
		BUG_ON(new_data_size <
				sle64_to_cpu(a->data.non_resident.data_size));
		a->data.non_resident.data_size = cpu_to_sle64(new_data_size);
	पूर्ण
flush_करोne:
	/* Ensure the changes make it to disk. */
	flush_dcache_mft_record_page(ctx->ntfs_ino);
	mark_mft_record_dirty(ctx->ntfs_ino);
करोne:
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(base_ni);
	up_ग_लिखो(&ni->runlist.lock);
	ntfs_debug("Done, new_allocated_size 0x%llx.",
			(अचिन्हित दीर्घ दीर्घ)new_alloc_size);
	वापस new_alloc_size;
restore_unकरो_alloc:
	अगर (start < 0 || start >= allocated_size)
		ntfs_error(vol->sb, "Cannot complete extension of allocation "
				"of inode 0x%lx, attribute type 0x%x, because "
				"lookup of first attribute extent failed with "
				"error code %i.", vi->i_ino,
				(अचिन्हित)le32_to_cpu(ni->type), err);
	अगर (err == -ENOENT)
		err = -EIO;
	ntfs_attr_reinit_search_ctx(ctx);
	अगर (ntfs_attr_lookup(ni->type, ni->name, ni->name_len, CASE_SENSITIVE,
			allocated_size >> vol->cluster_size_bits, शून्य, 0,
			ctx)) अणु
		ntfs_error(vol->sb, "Failed to find last attribute extent of "
				"attribute in error code path.  Run chkdsk to "
				"recover.");
		ग_लिखो_lock_irqsave(&ni->size_lock, flags);
		ni->allocated_size = new_alloc_size;
		/*
		 * FIXME: This would fail अगर @ni is a directory...  See above.
		 * FIXME: The calculation is wrong अगर we created a hole above.
		 * For now it करोes not matter as we never create holes.
		 */
		अगर (NInoSparse(ni) || NInoCompressed(ni)) अणु
			ni->itype.compressed.size += new_alloc_size -
					allocated_size;
			vi->i_blocks = ni->itype.compressed.size >> 9;
		पूर्ण अन्यथा
			vi->i_blocks = new_alloc_size >> 9;
		ग_लिखो_unlock_irqrestore(&ni->size_lock, flags);
		ntfs_attr_put_search_ctx(ctx);
		unmap_mft_record(base_ni);
		up_ग_लिखो(&ni->runlist.lock);
		/*
		 * The only thing that is now wrong is the allocated size of the
		 * base attribute extent which chkdsk should be able to fix.
		 */
		NVolSetErrors(vol);
		वापस err;
	पूर्ण
	ctx->attr->data.non_resident.highest_vcn = cpu_to_sle64(
			(allocated_size >> vol->cluster_size_bits) - 1);
unकरो_alloc:
	ll = allocated_size >> vol->cluster_size_bits;
	अगर (ntfs_cluster_मुक्त(ni, ll, -1, ctx) < 0) अणु
		ntfs_error(vol->sb, "Failed to release allocated cluster(s) "
				"in error code path.  Run chkdsk to recover "
				"the lost cluster(s).");
		NVolSetErrors(vol);
	पूर्ण
	m = ctx->mrec;
	a = ctx->attr;
	/*
	 * If the runlist truncation fails and/or the search context is no
	 * दीर्घer valid, we cannot resize the attribute record or build the
	 * mapping pairs array thus we mark the inode bad so that no access to
	 * the मुक्तd clusters can happen.
	 */
	अगर (ntfs_rl_truncate_nolock(vol, &ni->runlist, ll) || IS_ERR(m)) अणु
		ntfs_error(vol->sb, "Failed to %s in error code path.  Run "
				"chkdsk to recover.", IS_ERR(m) ?
				"restore attribute search context" :
				"truncate attribute runlist");
		NVolSetErrors(vol);
	पूर्ण अन्यथा अगर (mp_rebuilt) अणु
		अगर (ntfs_attr_record_resize(m, a, attr_len)) अणु
			ntfs_error(vol->sb, "Failed to restore attribute "
					"record in error code path.  Run "
					"chkdsk to recover.");
			NVolSetErrors(vol);
		पूर्ण अन्यथा /* अगर (success) */ अणु
			अगर (ntfs_mapping_pairs_build(vol, (u8*)a + le16_to_cpu(
					a->data.non_resident.
					mapping_pairs_offset), attr_len -
					le16_to_cpu(a->data.non_resident.
					mapping_pairs_offset), rl2, ll, -1,
					शून्य)) अणु
				ntfs_error(vol->sb, "Failed to restore "
						"mapping pairs array in error "
						"code path.  Run chkdsk to "
						"recover.");
				NVolSetErrors(vol);
			पूर्ण
			flush_dcache_mft_record_page(ctx->ntfs_ino);
			mark_mft_record_dirty(ctx->ntfs_ino);
		पूर्ण
	पूर्ण
err_out:
	अगर (ctx)
		ntfs_attr_put_search_ctx(ctx);
	अगर (m)
		unmap_mft_record(base_ni);
	up_ग_लिखो(&ni->runlist.lock);
conv_err_out:
	ntfs_debug("Failed.  Returning error code %i.", err);
	वापस err;
पूर्ण

/**
 * ntfs_attr_set - fill (a part of) an attribute with a byte
 * @ni:		ntfs inode describing the attribute to fill
 * @ofs:	offset inside the attribute at which to start to fill
 * @cnt:	number of bytes to fill
 * @val:	the अचिन्हित 8-bit value with which to fill the attribute
 *
 * Fill @cnt bytes of the attribute described by the ntfs inode @ni starting at
 * byte offset @ofs inside the attribute with the स्थिरant byte @val.
 *
 * This function is effectively like स_रखो() applied to an ntfs attribute.
 * Note thie function actually only operates on the page cache pages beदीर्घing
 * to the ntfs attribute and it marks them dirty after करोing the स_रखो().
 * Thus it relies on the vm dirty page ग_लिखो code paths to cause the modअगरied
 * pages to be written to the mft record/disk.
 *
 * Return 0 on success and -त्रुटि_सं on error.  An error code of -ESPIPE means
 * that @ofs + @cnt were outside the end of the attribute and no ग_लिखो was
 * perक्रमmed.
 */
पूर्णांक ntfs_attr_set(ntfs_inode *ni, स्थिर s64 ofs, स्थिर s64 cnt, स्थिर u8 val)
अणु
	ntfs_volume *vol = ni->vol;
	काष्ठा address_space *mapping;
	काष्ठा page *page;
	u8 *kaddr;
	pgoff_t idx, end;
	अचिन्हित start_ofs, end_ofs, size;

	ntfs_debug("Entering for ofs 0x%llx, cnt 0x%llx, val 0x%hx.",
			(दीर्घ दीर्घ)ofs, (दीर्घ दीर्घ)cnt, val);
	BUG_ON(ofs < 0);
	BUG_ON(cnt < 0);
	अगर (!cnt)
		जाओ करोne;
	/*
	 * FIXME: Compressed and encrypted attributes are not supported when
	 * writing and we should never have gotten here क्रम them.
	 */
	BUG_ON(NInoCompressed(ni));
	BUG_ON(NInoEncrypted(ni));
	mapping = VFS_I(ni)->i_mapping;
	/* Work out the starting index and page offset. */
	idx = ofs >> PAGE_SHIFT;
	start_ofs = ofs & ~PAGE_MASK;
	/* Work out the ending index and page offset. */
	end = ofs + cnt;
	end_ofs = end & ~PAGE_MASK;
	/* If the end is outside the inode size वापस -ESPIPE. */
	अगर (unlikely(end > i_size_पढ़ो(VFS_I(ni)))) अणु
		ntfs_error(vol->sb, "Request exceeds end of attribute.");
		वापस -ESPIPE;
	पूर्ण
	end >>= PAGE_SHIFT;
	/* If there is a first partial page, need to करो it the slow way. */
	अगर (start_ofs) अणु
		page = पढ़ो_mapping_page(mapping, idx, शून्य);
		अगर (IS_ERR(page)) अणु
			ntfs_error(vol->sb, "Failed to read first partial "
					"page (error, index 0x%lx).", idx);
			वापस PTR_ERR(page);
		पूर्ण
		/*
		 * If the last page is the same as the first page, need to
		 * limit the ग_लिखो to the end offset.
		 */
		size = PAGE_SIZE;
		अगर (idx == end)
			size = end_ofs;
		kaddr = kmap_atomic(page);
		स_रखो(kaddr + start_ofs, val, size - start_ofs);
		flush_dcache_page(page);
		kunmap_atomic(kaddr);
		set_page_dirty(page);
		put_page(page);
		balance_dirty_pages_ratelimited(mapping);
		cond_resched();
		अगर (idx == end)
			जाओ करोne;
		idx++;
	पूर्ण
	/* Do the whole pages the fast way. */
	क्रम (; idx < end; idx++) अणु
		/* Find or create the current page.  (The page is locked.) */
		page = grab_cache_page(mapping, idx);
		अगर (unlikely(!page)) अणु
			ntfs_error(vol->sb, "Insufficient memory to grab "
					"page (index 0x%lx).", idx);
			वापस -ENOMEM;
		पूर्ण
		kaddr = kmap_atomic(page);
		स_रखो(kaddr, val, PAGE_SIZE);
		flush_dcache_page(page);
		kunmap_atomic(kaddr);
		/*
		 * If the page has buffers, mark them uptodate since buffer
		 * state and not page state is definitive in 2.6 kernels.
		 */
		अगर (page_has_buffers(page)) अणु
			काष्ठा buffer_head *bh, *head;

			bh = head = page_buffers(page);
			करो अणु
				set_buffer_uptodate(bh);
			पूर्ण जबतक ((bh = bh->b_this_page) != head);
		पूर्ण
		/* Now that buffers are uptodate, set the page uptodate, too. */
		SetPageUptodate(page);
		/*
		 * Set the page and all its buffers dirty and mark the inode
		 * dirty, too.  The VM will ग_लिखो the page later on.
		 */
		set_page_dirty(page);
		/* Finally unlock and release the page. */
		unlock_page(page);
		put_page(page);
		balance_dirty_pages_ratelimited(mapping);
		cond_resched();
	पूर्ण
	/* If there is a last partial page, need to करो it the slow way. */
	अगर (end_ofs) अणु
		page = पढ़ो_mapping_page(mapping, idx, शून्य);
		अगर (IS_ERR(page)) अणु
			ntfs_error(vol->sb, "Failed to read last partial page "
					"(error, index 0x%lx).", idx);
			वापस PTR_ERR(page);
		पूर्ण
		kaddr = kmap_atomic(page);
		स_रखो(kaddr, val, end_ofs);
		flush_dcache_page(page);
		kunmap_atomic(kaddr);
		set_page_dirty(page);
		put_page(page);
		balance_dirty_pages_ratelimited(mapping);
		cond_resched();
	पूर्ण
करोne:
	ntfs_debug("Done.");
	वापस 0;
पूर्ण

#पूर्ण_अगर /* NTFS_RW */
