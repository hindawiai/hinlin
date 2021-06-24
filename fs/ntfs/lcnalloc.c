<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lcnalloc.c - Cluster (de)allocation code.  Part of the Linux-NTFS project.
 *
 * Copyright (c) 2004-2005 Anton Altaparmakov
 */

#अगर_घोषित NTFS_RW

#समावेश <linux/pagemap.h>

#समावेश "lcnalloc.h"
#समावेश "debug.h"
#समावेश "bitmap.h"
#समावेश "inode.h"
#समावेश "volume.h"
#समावेश "attrib.h"
#समावेश "malloc.h"
#समावेश "aops.h"
#समावेश "ntfs.h"

/**
 * ntfs_cluster_मुक्त_from_rl_nolock - मुक्त clusters from runlist
 * @vol:	mounted ntfs volume on which to मुक्त the clusters
 * @rl:		runlist describing the clusters to मुक्त
 *
 * Free all the clusters described by the runlist @rl on the volume @vol.  In
 * the हाल of an error being वापसed, at least some of the clusters were not
 * मुक्तd.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 *
 * Locking: - The volume lcn biपंचांगap must be locked क्रम writing on entry and is
 *	      left locked on वापस.
 */
पूर्णांक ntfs_cluster_मुक्त_from_rl_nolock(ntfs_volume *vol,
		स्थिर runlist_element *rl)
अणु
	काष्ठा inode *lcnbmp_vi = vol->lcnbmp_ino;
	पूर्णांक ret = 0;

	ntfs_debug("Entering.");
	अगर (!rl)
		वापस 0;
	क्रम (; rl->length; rl++) अणु
		पूर्णांक err;

		अगर (rl->lcn < 0)
			जारी;
		err = ntfs_biपंचांगap_clear_run(lcnbmp_vi, rl->lcn, rl->length);
		अगर (unlikely(err && (!ret || ret == -ENOMEM) && ret != err))
			ret = err;
	पूर्ण
	ntfs_debug("Done.");
	वापस ret;
पूर्ण

/**
 * ntfs_cluster_alloc - allocate clusters on an ntfs volume
 * @vol:	mounted ntfs volume on which to allocate the clusters
 * @start_vcn:	vcn to use क्रम the first allocated cluster
 * @count:	number of clusters to allocate
 * @start_lcn:	starting lcn at which to allocate the clusters (or -1 अगर none)
 * @zone:	zone from which to allocate the clusters
 * @is_extension:	अगर 'true', this is an attribute extension
 *
 * Allocate @count clusters preferably starting at cluster @start_lcn or at the
 * current allocator position अगर @start_lcn is -1, on the mounted ntfs volume
 * @vol. @zone is either DATA_ZONE क्रम allocation of normal clusters or
 * MFT_ZONE क्रम allocation of clusters क्रम the master file table, i.e. the
 * $MFT/$DATA attribute.
 *
 * @start_vcn specअगरies the vcn of the first allocated cluster.  This makes
 * merging the resulting runlist with the old runlist easier.
 *
 * If @is_extension is 'true', the caller is allocating clusters to extend an
 * attribute and अगर it is 'false', the caller is allocating clusters to fill a
 * hole in an attribute.  Practically the dअगरference is that अगर @is_extension
 * is 'true' the वापसed runlist will be terminated with LCN_ENOENT and अगर
 * @is_extension is 'false' the runlist will be terminated with
 * LCN_RL_NOT_MAPPED.
 *
 * You need to check the वापस value with IS_ERR().  If this is false, the
 * function was successful and the वापस value is a runlist describing the
 * allocated cluster(s).  If IS_ERR() is true, the function failed and
 * PTR_ERR() gives you the error code.
 *
 * Notes on the allocation algorithm
 * =================================
 *
 * There are two data zones.  First is the area between the end of the mft zone
 * and the end of the volume, and second is the area between the start of the
 * volume and the start of the mft zone.  On unmodअगरied/standard NTFS 1.x
 * volumes, the second data zone करोes not exist due to the mft zone being
 * expanded to cover the start of the volume in order to reserve space क्रम the
 * mft biपंचांगap attribute.
 *
 * This is not the prettiest function but the complनिकासy stems from the need of
 * implementing the mft vs data zoned approach and from the fact that we have
 * access to the lcn biपंचांगap in portions of up to 8192 bytes at a समय, so we
 * need to cope with crossing over boundaries of two buffers.  Further, the
 * fact that the allocator allows क्रम caller supplied hपूर्णांकs as to the location
 * of where allocation should begin and the fact that the allocator keeps track
 * of where in the data zones the next natural allocation should occur,
 * contribute to the complनिकासy of the function.  But it should all be
 * worthजबतक, because this allocator should: 1) be a full implementation of
 * the MFT zone approach used by Winकरोws NT, 2) cause reduction in
 * fragmentation, and 3) be speedy in allocations (the code is not optimized
 * क्रम speed, but the algorithm is, so further speed improvements are probably
 * possible).
 *
 * FIXME: We should be monitoring cluster allocation and increment the MFT zone
 * size dynamically but this is something क्रम the future.  We will just cause
 * heavier fragmentation by not करोing it and I am not even sure Winकरोws would
 * grow the MFT zone dynamically, so it might even be correct not to करो this.
 * The overhead in करोing dynamic MFT zone expansion would be very large and
 * unlikely worth the efक्रमt. (AIA)
 *
 * TODO: I have added in द्विगुन the required zone position poपूर्णांकer wrap around
 * logic which can be optimized to having only one of the two logic sets.
 * However, having the द्विगुन logic will work fine, but अगर we have only one of
 * the sets and we get it wrong somewhere, then we get पूर्णांकo trouble, so
 * removing the duplicate logic requires _very_ careful consideration of _all_
 * possible code paths.  So at least क्रम now, I am leaving the द्विगुन logic -
 * better safe than sorry... (AIA)
 *
 * Locking: - The volume lcn biपंचांगap must be unlocked on entry and is unlocked
 *	      on वापस.
 *	    - This function takes the volume lcn biपंचांगap lock क्रम writing and
 *	      modअगरies the biपंचांगap contents.
 */
runlist_element *ntfs_cluster_alloc(ntfs_volume *vol, स्थिर VCN start_vcn,
		स्थिर s64 count, स्थिर LCN start_lcn,
		स्थिर NTFS_CLUSTER_ALLOCATION_ZONES zone,
		स्थिर bool is_extension)
अणु
	LCN zone_start, zone_end, bmp_pos, bmp_initial_pos, last_पढ़ो_pos, lcn;
	LCN prev_lcn = 0, prev_run_len = 0, mft_zone_size;
	s64 clusters;
	loff_t i_size;
	काष्ठा inode *lcnbmp_vi;
	runlist_element *rl = शून्य;
	काष्ठा address_space *mapping;
	काष्ठा page *page = शून्य;
	u8 *buf, *byte;
	पूर्णांक err = 0, rlpos, rlsize, buf_size;
	u8 pass, करोne_zones, search_zone, need_ग_लिखोback = 0, bit;

	ntfs_debug("Entering for start_vcn 0x%llx, count 0x%llx, start_lcn "
			"0x%llx, zone %s_ZONE.", (अचिन्हित दीर्घ दीर्घ)start_vcn,
			(अचिन्हित दीर्घ दीर्घ)count,
			(अचिन्हित दीर्घ दीर्घ)start_lcn,
			zone == MFT_ZONE ? "MFT" : "DATA");
	BUG_ON(!vol);
	lcnbmp_vi = vol->lcnbmp_ino;
	BUG_ON(!lcnbmp_vi);
	BUG_ON(start_vcn < 0);
	BUG_ON(count < 0);
	BUG_ON(start_lcn < -1);
	BUG_ON(zone < FIRST_ZONE);
	BUG_ON(zone > LAST_ZONE);

	/* Return शून्य अगर @count is zero. */
	अगर (!count)
		वापस शून्य;
	/* Take the lcnbmp lock क्रम writing. */
	करोwn_ग_लिखो(&vol->lcnbmp_lock);
	/*
	 * If no specअगरic @start_lcn was requested, use the current data zone
	 * position, otherwise use the requested @start_lcn but make sure it
	 * lies outside the mft zone.  Also set करोne_zones to 0 (no zones करोne)
	 * and pass depending on whether we are starting inside a zone (1) or
	 * at the beginning of a zone (2).  If requesting from the MFT_ZONE,
	 * we either start at the current position within the mft zone or at
	 * the specअगरied position.  If the latter is out of bounds then we start
	 * at the beginning of the MFT_ZONE.
	 */
	करोne_zones = 0;
	pass = 1;
	/*
	 * zone_start and zone_end are the current search range.  search_zone
	 * is 1 क्रम mft zone, 2 क्रम data zone 1 (end of mft zone till end of
	 * volume) and 4 क्रम data zone 2 (start of volume till start of mft
	 * zone).
	 */
	zone_start = start_lcn;
	अगर (zone_start < 0) अणु
		अगर (zone == DATA_ZONE)
			zone_start = vol->data1_zone_pos;
		अन्यथा
			zone_start = vol->mft_zone_pos;
		अगर (!zone_start) अणु
			/*
			 * Zone starts at beginning of volume which means a
			 * single pass is sufficient.
			 */
			pass = 2;
		पूर्ण
	पूर्ण अन्यथा अगर (zone == DATA_ZONE && zone_start >= vol->mft_zone_start &&
			zone_start < vol->mft_zone_end) अणु
		zone_start = vol->mft_zone_end;
		/*
		 * Starting at beginning of data1_zone which means a single
		 * pass in this zone is sufficient.
		 */
		pass = 2;
	पूर्ण अन्यथा अगर (zone == MFT_ZONE && (zone_start < vol->mft_zone_start ||
			zone_start >= vol->mft_zone_end)) अणु
		zone_start = vol->mft_lcn;
		अगर (!vol->mft_zone_end)
			zone_start = 0;
		/*
		 * Starting at beginning of volume which means a single pass
		 * is sufficient.
		 */
		pass = 2;
	पूर्ण
	अगर (zone == MFT_ZONE) अणु
		zone_end = vol->mft_zone_end;
		search_zone = 1;
	पूर्ण अन्यथा /* अगर (zone == DATA_ZONE) */ अणु
		/* Skip searching the mft zone. */
		करोne_zones |= 1;
		अगर (zone_start >= vol->mft_zone_end) अणु
			zone_end = vol->nr_clusters;
			search_zone = 2;
		पूर्ण अन्यथा अणु
			zone_end = vol->mft_zone_start;
			search_zone = 4;
		पूर्ण
	पूर्ण
	/*
	 * bmp_pos is the current bit position inside the biपंचांगap.  We use
	 * bmp_initial_pos to determine whether or not to करो a zone चयन.
	 */
	bmp_pos = bmp_initial_pos = zone_start;

	/* Loop until all clusters are allocated, i.e. clusters == 0. */
	clusters = count;
	rlpos = rlsize = 0;
	mapping = lcnbmp_vi->i_mapping;
	i_size = i_size_पढ़ो(lcnbmp_vi);
	जबतक (1) अणु
		ntfs_debug("Start of outer while loop: done_zones 0x%x, "
				"search_zone %i, pass %i, zone_start 0x%llx, "
				"zone_end 0x%llx, bmp_initial_pos 0x%llx, "
				"bmp_pos 0x%llx, rlpos %i, rlsize %i.",
				करोne_zones, search_zone, pass,
				(अचिन्हित दीर्घ दीर्घ)zone_start,
				(अचिन्हित दीर्घ दीर्घ)zone_end,
				(अचिन्हित दीर्घ दीर्घ)bmp_initial_pos,
				(अचिन्हित दीर्घ दीर्घ)bmp_pos, rlpos, rlsize);
		/* Loop until we run out of मुक्त clusters. */
		last_पढ़ो_pos = bmp_pos >> 3;
		ntfs_debug("last_read_pos 0x%llx.",
				(अचिन्हित दीर्घ दीर्घ)last_पढ़ो_pos);
		अगर (last_पढ़ो_pos > i_size) अणु
			ntfs_debug("End of attribute reached.  "
					"Skipping to zone_pass_done.");
			जाओ zone_pass_करोne;
		पूर्ण
		अगर (likely(page)) अणु
			अगर (need_ग_लिखोback) अणु
				ntfs_debug("Marking page dirty.");
				flush_dcache_page(page);
				set_page_dirty(page);
				need_ग_लिखोback = 0;
			पूर्ण
			ntfs_unmap_page(page);
		पूर्ण
		page = ntfs_map_page(mapping, last_पढ़ो_pos >>
				PAGE_SHIFT);
		अगर (IS_ERR(page)) अणु
			err = PTR_ERR(page);
			ntfs_error(vol->sb, "Failed to map page.");
			जाओ out;
		पूर्ण
		buf_size = last_पढ़ो_pos & ~PAGE_MASK;
		buf = page_address(page) + buf_size;
		buf_size = PAGE_SIZE - buf_size;
		अगर (unlikely(last_पढ़ो_pos + buf_size > i_size))
			buf_size = i_size - last_पढ़ो_pos;
		buf_size <<= 3;
		lcn = bmp_pos & 7;
		bmp_pos &= ~(LCN)7;
		ntfs_debug("Before inner while loop: buf_size %i, lcn 0x%llx, "
				"bmp_pos 0x%llx, need_writeback %i.", buf_size,
				(अचिन्हित दीर्घ दीर्घ)lcn,
				(अचिन्हित दीर्घ दीर्घ)bmp_pos, need_ग_लिखोback);
		जबतक (lcn < buf_size && lcn + bmp_pos < zone_end) अणु
			byte = buf + (lcn >> 3);
			ntfs_debug("In inner while loop: buf_size %i, "
					"lcn 0x%llx, bmp_pos 0x%llx, "
					"need_writeback %i, byte ofs 0x%x, "
					"*byte 0x%x.", buf_size,
					(अचिन्हित दीर्घ दीर्घ)lcn,
					(अचिन्हित दीर्घ दीर्घ)bmp_pos,
					need_ग_लिखोback,
					(अचिन्हित पूर्णांक)(lcn >> 3),
					(अचिन्हित पूर्णांक)*byte);
			/* Skip full bytes. */
			अगर (*byte == 0xff) अणु
				lcn = (lcn + 8) & ~(LCN)7;
				ntfs_debug("Continuing while loop 1.");
				जारी;
			पूर्ण
			bit = 1 << (lcn & 7);
			ntfs_debug("bit 0x%x.", bit);
			/* If the bit is alपढ़ोy set, go onto the next one. */
			अगर (*byte & bit) अणु
				lcn++;
				ntfs_debug("Continuing while loop 2.");
				जारी;
			पूर्ण
			/*
			 * Allocate more memory अगर needed, including space क्रम
			 * the terminator element.
			 * ntfs_दो_स्मृति_nofs() operates on whole pages only.
			 */
			अगर ((rlpos + 2) * माप(*rl) > rlsize) अणु
				runlist_element *rl2;

				ntfs_debug("Reallocating memory.");
				अगर (!rl)
					ntfs_debug("First free bit is at LCN "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							(lcn + bmp_pos));
				rl2 = ntfs_दो_स्मृति_nofs(rlsize + (पूर्णांक)PAGE_SIZE);
				अगर (unlikely(!rl2)) अणु
					err = -ENOMEM;
					ntfs_error(vol->sb, "Failed to "
							"allocate memory.");
					जाओ out;
				पूर्ण
				स_नकल(rl2, rl, rlsize);
				ntfs_मुक्त(rl);
				rl = rl2;
				rlsize += PAGE_SIZE;
				ntfs_debug("Reallocated memory, rlsize 0x%x.",
						rlsize);
			पूर्ण
			/* Allocate the biपंचांगap bit. */
			*byte |= bit;
			/* We need to ग_लिखो this biपंचांगap page to disk. */
			need_ग_लिखोback = 1;
			ntfs_debug("*byte 0x%x, need_writeback is set.",
					(अचिन्हित पूर्णांक)*byte);
			/*
			 * Coalesce with previous run अगर adjacent LCNs.
			 * Otherwise, append a new run.
			 */
			ntfs_debug("Adding run (lcn 0x%llx, len 0x%llx), "
					"prev_lcn 0x%llx, lcn 0x%llx, "
					"bmp_pos 0x%llx, prev_run_len 0x%llx, "
					"rlpos %i.",
					(अचिन्हित दीर्घ दीर्घ)(lcn + bmp_pos),
					1ULL, (अचिन्हित दीर्घ दीर्घ)prev_lcn,
					(अचिन्हित दीर्घ दीर्घ)lcn,
					(अचिन्हित दीर्घ दीर्घ)bmp_pos,
					(अचिन्हित दीर्घ दीर्घ)prev_run_len,
					rlpos);
			अगर (prev_lcn == lcn + bmp_pos - prev_run_len && rlpos) अणु
				ntfs_debug("Coalescing to run (lcn 0x%llx, "
						"len 0x%llx).",
						(अचिन्हित दीर्घ दीर्घ)
						rl[rlpos - 1].lcn,
						(अचिन्हित दीर्घ दीर्घ)
						rl[rlpos - 1].length);
				rl[rlpos - 1].length = ++prev_run_len;
				ntfs_debug("Run now (lcn 0x%llx, len 0x%llx), "
						"prev_run_len 0x%llx.",
						(अचिन्हित दीर्घ दीर्घ)
						rl[rlpos - 1].lcn,
						(अचिन्हित दीर्घ दीर्घ)
						rl[rlpos - 1].length,
						(अचिन्हित दीर्घ दीर्घ)
						prev_run_len);
			पूर्ण अन्यथा अणु
				अगर (likely(rlpos)) अणु
					ntfs_debug("Adding new run, (previous "
							"run lcn 0x%llx, "
							"len 0x%llx).",
							(अचिन्हित दीर्घ दीर्घ)
							rl[rlpos - 1].lcn,
							(अचिन्हित दीर्घ दीर्घ)
							rl[rlpos - 1].length);
					rl[rlpos].vcn = rl[rlpos - 1].vcn +
							prev_run_len;
				पूर्ण अन्यथा अणु
					ntfs_debug("Adding new run, is first "
							"run.");
					rl[rlpos].vcn = start_vcn;
				पूर्ण
				rl[rlpos].lcn = prev_lcn = lcn + bmp_pos;
				rl[rlpos].length = prev_run_len = 1;
				rlpos++;
			पूर्ण
			/* Done? */
			अगर (!--clusters) अणु
				LCN tc;
				/*
				 * Update the current zone position.  Positions
				 * of alपढ़ोy scanned zones have been updated
				 * during the respective zone चयनes.
				 */
				tc = lcn + bmp_pos + 1;
				ntfs_debug("Done. Updating current zone "
						"position, tc 0x%llx, "
						"search_zone %i.",
						(अचिन्हित दीर्घ दीर्घ)tc,
						search_zone);
				चयन (search_zone) अणु
				हाल 1:
					ntfs_debug("Before checks, "
							"vol->mft_zone_pos "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							vol->mft_zone_pos);
					अगर (tc >= vol->mft_zone_end) अणु
						vol->mft_zone_pos =
								vol->mft_lcn;
						अगर (!vol->mft_zone_end)
							vol->mft_zone_pos = 0;
					पूर्ण अन्यथा अगर ((bmp_initial_pos >=
							vol->mft_zone_pos ||
							tc > vol->mft_zone_pos)
							&& tc >= vol->mft_lcn)
						vol->mft_zone_pos = tc;
					ntfs_debug("After checks, "
							"vol->mft_zone_pos "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							vol->mft_zone_pos);
					अवरोध;
				हाल 2:
					ntfs_debug("Before checks, "
							"vol->data1_zone_pos "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							vol->data1_zone_pos);
					अगर (tc >= vol->nr_clusters)
						vol->data1_zone_pos =
							     vol->mft_zone_end;
					अन्यथा अगर ((bmp_initial_pos >=
						    vol->data1_zone_pos ||
						    tc > vol->data1_zone_pos)
						    && tc >= vol->mft_zone_end)
						vol->data1_zone_pos = tc;
					ntfs_debug("After checks, "
							"vol->data1_zone_pos "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							vol->data1_zone_pos);
					अवरोध;
				हाल 4:
					ntfs_debug("Before checks, "
							"vol->data2_zone_pos "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							vol->data2_zone_pos);
					अगर (tc >= vol->mft_zone_start)
						vol->data2_zone_pos = 0;
					अन्यथा अगर (bmp_initial_pos >=
						      vol->data2_zone_pos ||
						      tc > vol->data2_zone_pos)
						vol->data2_zone_pos = tc;
					ntfs_debug("After checks, "
							"vol->data2_zone_pos "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							vol->data2_zone_pos);
					अवरोध;
				शेष:
					BUG();
				पूर्ण
				ntfs_debug("Finished.  Going to out.");
				जाओ out;
			पूर्ण
			lcn++;
		पूर्ण
		bmp_pos += buf_size;
		ntfs_debug("After inner while loop: buf_size 0x%x, lcn "
				"0x%llx, bmp_pos 0x%llx, need_writeback %i.",
				buf_size, (अचिन्हित दीर्घ दीर्घ)lcn,
				(अचिन्हित दीर्घ दीर्घ)bmp_pos, need_ग_लिखोback);
		अगर (bmp_pos < zone_end) अणु
			ntfs_debug("Continuing outer while loop, "
					"bmp_pos 0x%llx, zone_end 0x%llx.",
					(अचिन्हित दीर्घ दीर्घ)bmp_pos,
					(अचिन्हित दीर्घ दीर्घ)zone_end);
			जारी;
		पूर्ण
zone_pass_करोne:	/* Finished with the current zone pass. */
		ntfs_debug("At zone_pass_done, pass %i.", pass);
		अगर (pass == 1) अणु
			/*
			 * Now करो pass 2, scanning the first part of the zone
			 * we omitted in pass 1.
			 */
			pass = 2;
			zone_end = zone_start;
			चयन (search_zone) अणु
			हाल 1: /* mft_zone */
				zone_start = vol->mft_zone_start;
				अवरोध;
			हाल 2: /* data1_zone */
				zone_start = vol->mft_zone_end;
				अवरोध;
			हाल 4: /* data2_zone */
				zone_start = 0;
				अवरोध;
			शेष:
				BUG();
			पूर्ण
			/* Sanity check. */
			अगर (zone_end < zone_start)
				zone_end = zone_start;
			bmp_pos = zone_start;
			ntfs_debug("Continuing outer while loop, pass 2, "
					"zone_start 0x%llx, zone_end 0x%llx, "
					"bmp_pos 0x%llx.",
					(अचिन्हित दीर्घ दीर्घ)zone_start,
					(अचिन्हित दीर्घ दीर्घ)zone_end,
					(अचिन्हित दीर्घ दीर्घ)bmp_pos);
			जारी;
		पूर्ण /* pass == 2 */
करोne_zones_check:
		ntfs_debug("At done_zones_check, search_zone %i, done_zones "
				"before 0x%x, done_zones after 0x%x.",
				search_zone, करोne_zones,
				करोne_zones | search_zone);
		करोne_zones |= search_zone;
		अगर (करोne_zones < 7) अणु
			ntfs_debug("Switching zone.");
			/* Now चयन to the next zone we haven't करोne yet. */
			pass = 1;
			चयन (search_zone) अणु
			हाल 1:
				ntfs_debug("Switching from mft zone to data1 "
						"zone.");
				/* Update mft zone position. */
				अगर (rlpos) अणु
					LCN tc;

					ntfs_debug("Before checks, "
							"vol->mft_zone_pos "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							vol->mft_zone_pos);
					tc = rl[rlpos - 1].lcn +
							rl[rlpos - 1].length;
					अगर (tc >= vol->mft_zone_end) अणु
						vol->mft_zone_pos =
								vol->mft_lcn;
						अगर (!vol->mft_zone_end)
							vol->mft_zone_pos = 0;
					पूर्ण अन्यथा अगर ((bmp_initial_pos >=
							vol->mft_zone_pos ||
							tc > vol->mft_zone_pos)
							&& tc >= vol->mft_lcn)
						vol->mft_zone_pos = tc;
					ntfs_debug("After checks, "
							"vol->mft_zone_pos "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							vol->mft_zone_pos);
				पूर्ण
				/* Switch from mft zone to data1 zone. */
चयन_to_data1_zone:		search_zone = 2;
				zone_start = bmp_initial_pos =
						vol->data1_zone_pos;
				zone_end = vol->nr_clusters;
				अगर (zone_start == vol->mft_zone_end)
					pass = 2;
				अगर (zone_start >= zone_end) अणु
					vol->data1_zone_pos = zone_start =
							vol->mft_zone_end;
					pass = 2;
				पूर्ण
				अवरोध;
			हाल 2:
				ntfs_debug("Switching from data1 zone to "
						"data2 zone.");
				/* Update data1 zone position. */
				अगर (rlpos) अणु
					LCN tc;

					ntfs_debug("Before checks, "
							"vol->data1_zone_pos "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							vol->data1_zone_pos);
					tc = rl[rlpos - 1].lcn +
							rl[rlpos - 1].length;
					अगर (tc >= vol->nr_clusters)
						vol->data1_zone_pos =
							     vol->mft_zone_end;
					अन्यथा अगर ((bmp_initial_pos >=
						    vol->data1_zone_pos ||
						    tc > vol->data1_zone_pos)
						    && tc >= vol->mft_zone_end)
						vol->data1_zone_pos = tc;
					ntfs_debug("After checks, "
							"vol->data1_zone_pos "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							vol->data1_zone_pos);
				पूर्ण
				/* Switch from data1 zone to data2 zone. */
				search_zone = 4;
				zone_start = bmp_initial_pos =
						vol->data2_zone_pos;
				zone_end = vol->mft_zone_start;
				अगर (!zone_start)
					pass = 2;
				अगर (zone_start >= zone_end) अणु
					vol->data2_zone_pos = zone_start =
							bmp_initial_pos = 0;
					pass = 2;
				पूर्ण
				अवरोध;
			हाल 4:
				ntfs_debug("Switching from data2 zone to "
						"data1 zone.");
				/* Update data2 zone position. */
				अगर (rlpos) अणु
					LCN tc;

					ntfs_debug("Before checks, "
							"vol->data2_zone_pos "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							vol->data2_zone_pos);
					tc = rl[rlpos - 1].lcn +
							rl[rlpos - 1].length;
					अगर (tc >= vol->mft_zone_start)
						vol->data2_zone_pos = 0;
					अन्यथा अगर (bmp_initial_pos >=
						      vol->data2_zone_pos ||
						      tc > vol->data2_zone_pos)
						vol->data2_zone_pos = tc;
					ntfs_debug("After checks, "
							"vol->data2_zone_pos "
							"0x%llx.",
							(अचिन्हित दीर्घ दीर्घ)
							vol->data2_zone_pos);
				पूर्ण
				/* Switch from data2 zone to data1 zone. */
				जाओ चयन_to_data1_zone;
			शेष:
				BUG();
			पूर्ण
			ntfs_debug("After zone switch, search_zone %i, "
					"pass %i, bmp_initial_pos 0x%llx, "
					"zone_start 0x%llx, zone_end 0x%llx.",
					search_zone, pass,
					(अचिन्हित दीर्घ दीर्घ)bmp_initial_pos,
					(अचिन्हित दीर्घ दीर्घ)zone_start,
					(अचिन्हित दीर्घ दीर्घ)zone_end);
			bmp_pos = zone_start;
			अगर (zone_start == zone_end) अणु
				ntfs_debug("Empty zone, going to "
						"done_zones_check.");
				/* Empty zone. Don't bother searching it. */
				जाओ करोne_zones_check;
			पूर्ण
			ntfs_debug("Continuing outer while loop.");
			जारी;
		पूर्ण /* करोne_zones == 7 */
		ntfs_debug("All zones are finished.");
		/*
		 * All zones are finished!  If DATA_ZONE, shrink mft zone.  If
		 * MFT_ZONE, we have really run out of space.
		 */
		mft_zone_size = vol->mft_zone_end - vol->mft_zone_start;
		ntfs_debug("vol->mft_zone_start 0x%llx, vol->mft_zone_end "
				"0x%llx, mft_zone_size 0x%llx.",
				(अचिन्हित दीर्घ दीर्घ)vol->mft_zone_start,
				(अचिन्हित दीर्घ दीर्घ)vol->mft_zone_end,
				(अचिन्हित दीर्घ दीर्घ)mft_zone_size);
		अगर (zone == MFT_ZONE || mft_zone_size <= 0) अणु
			ntfs_debug("No free clusters left, going to out.");
			/* Really no more space left on device. */
			err = -ENOSPC;
			जाओ out;
		पूर्ण /* zone == DATA_ZONE && mft_zone_size > 0 */
		ntfs_debug("Shrinking mft zone.");
		zone_end = vol->mft_zone_end;
		mft_zone_size >>= 1;
		अगर (mft_zone_size > 0)
			vol->mft_zone_end = vol->mft_zone_start + mft_zone_size;
		अन्यथा /* mft zone and data2 zone no दीर्घer exist. */
			vol->data2_zone_pos = vol->mft_zone_start =
					vol->mft_zone_end = 0;
		अगर (vol->mft_zone_pos >= vol->mft_zone_end) अणु
			vol->mft_zone_pos = vol->mft_lcn;
			अगर (!vol->mft_zone_end)
				vol->mft_zone_pos = 0;
		पूर्ण
		bmp_pos = zone_start = bmp_initial_pos =
				vol->data1_zone_pos = vol->mft_zone_end;
		search_zone = 2;
		pass = 2;
		करोne_zones &= ~2;
		ntfs_debug("After shrinking mft zone, mft_zone_size 0x%llx, "
				"vol->mft_zone_start 0x%llx, "
				"vol->mft_zone_end 0x%llx, "
				"vol->mft_zone_pos 0x%llx, search_zone 2, "
				"pass 2, dones_zones 0x%x, zone_start 0x%llx, "
				"zone_end 0x%llx, vol->data1_zone_pos 0x%llx, "
				"continuing outer while loop.",
				(अचिन्हित दीर्घ दीर्घ)mft_zone_size,
				(अचिन्हित दीर्घ दीर्घ)vol->mft_zone_start,
				(अचिन्हित दीर्घ दीर्घ)vol->mft_zone_end,
				(अचिन्हित दीर्घ दीर्घ)vol->mft_zone_pos,
				करोne_zones, (अचिन्हित दीर्घ दीर्घ)zone_start,
				(अचिन्हित दीर्घ दीर्घ)zone_end,
				(अचिन्हित दीर्घ दीर्घ)vol->data1_zone_pos);
	पूर्ण
	ntfs_debug("After outer while loop.");
out:
	ntfs_debug("At out.");
	/* Add runlist terminator element. */
	अगर (likely(rl)) अणु
		rl[rlpos].vcn = rl[rlpos - 1].vcn + rl[rlpos - 1].length;
		rl[rlpos].lcn = is_extension ? LCN_ENOENT : LCN_RL_NOT_MAPPED;
		rl[rlpos].length = 0;
	पूर्ण
	अगर (likely(page && !IS_ERR(page))) अणु
		अगर (need_ग_लिखोback) अणु
			ntfs_debug("Marking page dirty.");
			flush_dcache_page(page);
			set_page_dirty(page);
			need_ग_लिखोback = 0;
		पूर्ण
		ntfs_unmap_page(page);
	पूर्ण
	अगर (likely(!err)) अणु
		up_ग_लिखो(&vol->lcnbmp_lock);
		ntfs_debug("Done.");
		वापस rl;
	पूर्ण
	ntfs_error(vol->sb, "Failed to allocate clusters, aborting "
			"(error %i).", err);
	अगर (rl) अणु
		पूर्णांक err2;

		अगर (err == -ENOSPC)
			ntfs_debug("Not enough space to complete allocation, "
					"err -ENOSPC, first free lcn 0x%llx, "
					"could allocate up to 0x%llx "
					"clusters.",
					(अचिन्हित दीर्घ दीर्घ)rl[0].lcn,
					(अचिन्हित दीर्घ दीर्घ)(count - clusters));
		/* Deallocate all allocated clusters. */
		ntfs_debug("Attempting rollback...");
		err2 = ntfs_cluster_मुक्त_from_rl_nolock(vol, rl);
		अगर (err2) अणु
			ntfs_error(vol->sb, "Failed to rollback (error %i).  "
					"Leaving inconsistent metadata!  "
					"Unmount and run chkdsk.", err2);
			NVolSetErrors(vol);
		पूर्ण
		/* Free the runlist. */
		ntfs_मुक्त(rl);
	पूर्ण अन्यथा अगर (err == -ENOSPC)
		ntfs_debug("No space left at all, err = -ENOSPC, first free "
				"lcn = 0x%llx.",
				(दीर्घ दीर्घ)vol->data1_zone_pos);
	up_ग_लिखो(&vol->lcnbmp_lock);
	वापस ERR_PTR(err);
पूर्ण

/**
 * __ntfs_cluster_मुक्त - मुक्त clusters on an ntfs volume
 * @ni:		ntfs inode whose runlist describes the clusters to मुक्त
 * @start_vcn:	vcn in the runlist of @ni at which to start मुक्तing clusters
 * @count:	number of clusters to मुक्त or -1 क्रम all clusters
 * @ctx:	active attribute search context अगर present or शून्य अगर not
 * @is_rollback:	true अगर this is a rollback operation
 *
 * Free @count clusters starting at the cluster @start_vcn in the runlist
 * described by the vfs inode @ni.
 *
 * If @count is -1, all clusters from @start_vcn to the end of the runlist are
 * deallocated.  Thus, to completely मुक्त all clusters in a runlist, use
 * @start_vcn = 0 and @count = -1.
 *
 * If @ctx is specअगरied, it is an active search context of @ni and its base mft
 * record.  This is needed when __ntfs_cluster_मुक्त() encounters unmapped
 * runlist fragments and allows their mapping.  If you करो not have the mft
 * record mapped, you can specअगरy @ctx as शून्य and __ntfs_cluster_मुक्त() will
 * perक्रमm the necessary mapping and unmapping.
 *
 * Note, __ntfs_cluster_मुक्त() saves the state of @ctx on entry and restores it
 * beक्रमe वापसing.  Thus, @ctx will be left poपूर्णांकing to the same attribute on
 * वापस as on entry.  However, the actual poपूर्णांकers in @ctx may poपूर्णांक to
 * dअगरferent memory locations on वापस, so you must remember to reset any
 * cached poपूर्णांकers from the @ctx, i.e. after the call to __ntfs_cluster_मुक्त(),
 * you will probably want to करो:
 *	m = ctx->mrec;
 *	a = ctx->attr;
 * Assuming you cache ctx->attr in a variable @a of type ATTR_RECORD * and that
 * you cache ctx->mrec in a variable @m of type MFT_RECORD *.
 *
 * @is_rollback should always be 'false', it is क्रम पूर्णांकernal use to rollback
 * errors.  You probably want to use ntfs_cluster_मुक्त() instead.
 *
 * Note, __ntfs_cluster_मुक्त() करोes not modअगरy the runlist, so you have to
 * हटाओ from the runlist or mark sparse the मुक्तd runs later.
 *
 * Return the number of deallocated clusters (not counting sparse ones) on
 * success and -त्रुटि_सं on error.
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
 *	    - The volume lcn biपंचांगap must be unlocked on entry and is unlocked
 *	      on वापस.
 *	    - This function takes the volume lcn biपंचांगap lock क्रम writing and
 *	      modअगरies the biपंचांगap contents.
 *	    - If @ctx is शून्य, the base mft record of @ni must not be mapped on
 *	      entry and it will be left unmapped on वापस.
 *	    - If @ctx is not शून्य, the base mft record must be mapped on entry
 *	      and it will be left mapped on वापस.
 */
s64 __ntfs_cluster_मुक्त(ntfs_inode *ni, स्थिर VCN start_vcn, s64 count,
		ntfs_attr_search_ctx *ctx, स्थिर bool is_rollback)
अणु
	s64 delta, to_मुक्त, total_मुक्तd, real_मुक्तd;
	ntfs_volume *vol;
	काष्ठा inode *lcnbmp_vi;
	runlist_element *rl;
	पूर्णांक err;

	BUG_ON(!ni);
	ntfs_debug("Entering for i_ino 0x%lx, start_vcn 0x%llx, count "
			"0x%llx.%s", ni->mft_no, (अचिन्हित दीर्घ दीर्घ)start_vcn,
			(अचिन्हित दीर्घ दीर्घ)count,
			is_rollback ? " (rollback)" : "");
	vol = ni->vol;
	lcnbmp_vi = vol->lcnbmp_ino;
	BUG_ON(!lcnbmp_vi);
	BUG_ON(start_vcn < 0);
	BUG_ON(count < -1);
	/*
	 * Lock the lcn biपंचांगap क्रम writing but only अगर not rolling back.  We
	 * must hold the lock all the way including through rollback otherwise
	 * rollback is not possible because once we have cleared a bit and
	 * dropped the lock, anyone could have set the bit again, thus
	 * allocating the cluster क्रम another use.
	 */
	अगर (likely(!is_rollback))
		करोwn_ग_लिखो(&vol->lcnbmp_lock);

	total_मुक्तd = real_मुक्तd = 0;

	rl = ntfs_attr_find_vcn_nolock(ni, start_vcn, ctx);
	अगर (IS_ERR(rl)) अणु
		अगर (!is_rollback)
			ntfs_error(vol->sb, "Failed to find first runlist "
					"element (error %li), aborting.",
					PTR_ERR(rl));
		err = PTR_ERR(rl);
		जाओ err_out;
	पूर्ण
	अगर (unlikely(rl->lcn < LCN_HOLE)) अणु
		अगर (!is_rollback)
			ntfs_error(vol->sb, "First runlist element has "
					"invalid lcn, aborting.");
		err = -EIO;
		जाओ err_out;
	पूर्ण
	/* Find the starting cluster inside the run that needs मुक्तing. */
	delta = start_vcn - rl->vcn;

	/* The number of clusters in this run that need मुक्तing. */
	to_मुक्त = rl->length - delta;
	अगर (count >= 0 && to_मुक्त > count)
		to_मुक्त = count;

	अगर (likely(rl->lcn >= 0)) अणु
		/* Do the actual मुक्तing of the clusters in this run. */
		err = ntfs_biपंचांगap_set_bits_in_run(lcnbmp_vi, rl->lcn + delta,
				to_मुक्त, likely(!is_rollback) ? 0 : 1);
		अगर (unlikely(err)) अणु
			अगर (!is_rollback)
				ntfs_error(vol->sb, "Failed to clear first run "
						"(error %i), aborting.", err);
			जाओ err_out;
		पूर्ण
		/* We have मुक्तd @to_मुक्त real clusters. */
		real_मुक्तd = to_मुक्त;
	पूर्ण;
	/* Go to the next run and adjust the number of clusters left to मुक्त. */
	++rl;
	अगर (count >= 0)
		count -= to_मुक्त;

	/* Keep track of the total "freed" clusters, including sparse ones. */
	total_मुक्तd = to_मुक्त;
	/*
	 * Loop over the reमुख्यing runs, using @count as a capping value, and
	 * मुक्त them.
	 */
	क्रम (; rl->length && count != 0; ++rl) अणु
		अगर (unlikely(rl->lcn < LCN_HOLE)) अणु
			VCN vcn;

			/* Attempt to map runlist. */
			vcn = rl->vcn;
			rl = ntfs_attr_find_vcn_nolock(ni, vcn, ctx);
			अगर (IS_ERR(rl)) अणु
				err = PTR_ERR(rl);
				अगर (!is_rollback)
					ntfs_error(vol->sb, "Failed to map "
							"runlist fragment or "
							"failed to find "
							"subsequent runlist "
							"element.");
				जाओ err_out;
			पूर्ण
			अगर (unlikely(rl->lcn < LCN_HOLE)) अणु
				अगर (!is_rollback)
					ntfs_error(vol->sb, "Runlist element "
							"has invalid lcn "
							"(0x%llx).",
							(अचिन्हित दीर्घ दीर्घ)
							rl->lcn);
				err = -EIO;
				जाओ err_out;
			पूर्ण
		पूर्ण
		/* The number of clusters in this run that need मुक्तing. */
		to_मुक्त = rl->length;
		अगर (count >= 0 && to_मुक्त > count)
			to_मुक्त = count;

		अगर (likely(rl->lcn >= 0)) अणु
			/* Do the actual मुक्तing of the clusters in the run. */
			err = ntfs_biपंचांगap_set_bits_in_run(lcnbmp_vi, rl->lcn,
					to_मुक्त, likely(!is_rollback) ? 0 : 1);
			अगर (unlikely(err)) अणु
				अगर (!is_rollback)
					ntfs_error(vol->sb, "Failed to clear "
							"subsequent run.");
				जाओ err_out;
			पूर्ण
			/* We have मुक्तd @to_मुक्त real clusters. */
			real_मुक्तd += to_मुक्त;
		पूर्ण
		/* Adjust the number of clusters left to मुक्त. */
		अगर (count >= 0)
			count -= to_मुक्त;
	
		/* Update the total करोne clusters. */
		total_मुक्तd += to_मुक्त;
	पूर्ण
	अगर (likely(!is_rollback))
		up_ग_लिखो(&vol->lcnbmp_lock);

	BUG_ON(count > 0);

	/* We are करोne.  Return the number of actually मुक्तd clusters. */
	ntfs_debug("Done.");
	वापस real_मुक्तd;
err_out:
	अगर (is_rollback)
		वापस err;
	/* If no real clusters were मुक्तd, no need to rollback. */
	अगर (!real_मुक्तd) अणु
		up_ग_लिखो(&vol->lcnbmp_lock);
		वापस err;
	पूर्ण
	/*
	 * Attempt to rollback and अगर that succeeds just वापस the error code.
	 * If rollback fails, set the volume errors flag, emit an error
	 * message, and वापस the error code.
	 */
	delta = __ntfs_cluster_मुक्त(ni, start_vcn, total_मुक्तd, ctx, true);
	अगर (delta < 0) अणु
		ntfs_error(vol->sb, "Failed to rollback (error %i).  Leaving "
				"inconsistent metadata!  Unmount and run "
				"chkdsk.", (पूर्णांक)delta);
		NVolSetErrors(vol);
	पूर्ण
	up_ग_लिखो(&vol->lcnbmp_lock);
	ntfs_error(vol->sb, "Aborting (error %i).", err);
	वापस err;
पूर्ण

#पूर्ण_अगर /* NTFS_RW */
