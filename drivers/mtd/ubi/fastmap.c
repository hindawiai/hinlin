<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012 Linutronix GmbH
 * Copyright (c) 2014 sigma star gmbh
 * Author: Riअक्षरd Weinberger <riअक्षरd@nod.at>
 */

#समावेश <linux/crc32.h>
#समावेश <linux/biपंचांगap.h>
#समावेश "ubi.h"

/**
 * init_seen - allocate memory क्रम used क्रम debugging.
 * @ubi: UBI device description object
 */
अटल अंतरभूत अचिन्हित दीर्घ *init_seen(काष्ठा ubi_device *ubi)
अणु
	अचिन्हित दीर्घ *ret;

	अगर (!ubi_dbg_chk_fasपंचांगap(ubi))
		वापस शून्य;

	ret = kसुस्मृति(BITS_TO_LONGS(ubi->peb_count), माप(अचिन्हित दीर्घ),
		      GFP_KERNEL);
	अगर (!ret)
		वापस ERR_PTR(-ENOMEM);

	वापस ret;
पूर्ण

/**
 * मुक्त_seen - मुक्त the seen logic पूर्णांकeger array.
 * @seen: पूर्णांकeger array of @ubi->peb_count size
 */
अटल अंतरभूत व्योम मुक्त_seen(अचिन्हित दीर्घ *seen)
अणु
	kमुक्त(seen);
पूर्ण

/**
 * set_seen - mark a PEB as seen.
 * @ubi: UBI device description object
 * @pnum: The PEB to be makred as seen
 * @seen: पूर्णांकeger array of @ubi->peb_count size
 */
अटल अंतरभूत व्योम set_seen(काष्ठा ubi_device *ubi, पूर्णांक pnum, अचिन्हित दीर्घ *seen)
अणु
	अगर (!ubi_dbg_chk_fasपंचांगap(ubi) || !seen)
		वापस;

	set_bit(pnum, seen);
पूर्ण

/**
 * self_check_seen - check whether all PEB have been seen by fasपंचांगap.
 * @ubi: UBI device description object
 * @seen: पूर्णांकeger array of @ubi->peb_count size
 */
अटल पूर्णांक self_check_seen(काष्ठा ubi_device *ubi, अचिन्हित दीर्घ *seen)
अणु
	पूर्णांक pnum, ret = 0;

	अगर (!ubi_dbg_chk_fasपंचांगap(ubi) || !seen)
		वापस 0;

	क्रम (pnum = 0; pnum < ubi->peb_count; pnum++) अणु
		अगर (!test_bit(pnum, seen) && ubi->lookuptbl[pnum]) अणु
			ubi_err(ubi, "self-check failed for PEB %d, fastmap didn't see it", pnum);
			ret = -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ubi_calc_fm_size - calculates the fasपंचांगap size in bytes क्रम an UBI device.
 * @ubi: UBI device description object
 */
माप_प्रकार ubi_calc_fm_size(काष्ठा ubi_device *ubi)
अणु
	माप_प्रकार size;

	size = माप(काष्ठा ubi_fm_sb) +
		माप(काष्ठा ubi_fm_hdr) +
		माप(काष्ठा ubi_fm_scan_pool) +
		माप(काष्ठा ubi_fm_scan_pool) +
		(ubi->peb_count * माप(काष्ठा ubi_fm_ec)) +
		(माप(काष्ठा ubi_fm_eba) +
		(ubi->peb_count * माप(__be32))) +
		माप(काष्ठा ubi_fm_volhdr) * UBI_MAX_VOLUMES;
	वापस roundup(size, ubi->leb_size);
पूर्ण


/**
 * new_fm_vhdr - allocate a new volume header क्रम fasपंचांगap usage.
 * @ubi: UBI device description object
 * @vol_id: the VID of the new header
 *
 * Returns a new काष्ठा ubi_vid_hdr on success.
 * शून्य indicates out of memory.
 */
अटल काष्ठा ubi_vid_io_buf *new_fm_vbuf(काष्ठा ubi_device *ubi, पूर्णांक vol_id)
अणु
	काष्ठा ubi_vid_io_buf *new;
	काष्ठा ubi_vid_hdr *vh;

	new = ubi_alloc_vid_buf(ubi, GFP_KERNEL);
	अगर (!new)
		जाओ out;

	vh = ubi_get_vid_hdr(new);
	vh->vol_type = UBI_VID_DYNAMIC;
	vh->vol_id = cpu_to_be32(vol_id);

	/* UBI implementations without fasपंचांगap support have to delete the
	 * fasपंचांगap.
	 */
	vh->compat = UBI_COMPAT_DELETE;

out:
	वापस new;
पूर्ण

/**
 * add_aeb - create and add a attach erase block to a given list.
 * @ai: UBI attach info object
 * @list: the target list
 * @pnum: PEB number of the new attach erase block
 * @ec: erease counter of the new LEB
 * @scrub: scrub this PEB after attaching
 *
 * Returns 0 on success, < 0 indicates an पूर्णांकernal error.
 */
अटल पूर्णांक add_aeb(काष्ठा ubi_attach_info *ai, काष्ठा list_head *list,
		   पूर्णांक pnum, पूर्णांक ec, पूर्णांक scrub)
अणु
	काष्ठा ubi_ainf_peb *aeb;

	aeb = ubi_alloc_aeb(ai, pnum, ec);
	अगर (!aeb)
		वापस -ENOMEM;

	aeb->lnum = -1;
	aeb->scrub = scrub;
	aeb->copy_flag = aeb->sqnum = 0;

	ai->ec_sum += aeb->ec;
	ai->ec_count++;

	अगर (ai->max_ec < aeb->ec)
		ai->max_ec = aeb->ec;

	अगर (ai->min_ec > aeb->ec)
		ai->min_ec = aeb->ec;

	list_add_tail(&aeb->u.list, list);

	वापस 0;
पूर्ण

/**
 * add_vol - create and add a new volume to ubi_attach_info.
 * @ai: ubi_attach_info object
 * @vol_id: VID of the new volume
 * @used_ebs: number of used EBS
 * @data_pad: data padding value of the new volume
 * @vol_type: volume type
 * @last_eb_bytes: number of bytes in the last LEB
 *
 * Returns the new काष्ठा ubi_ainf_volume on success.
 * शून्य indicates an error.
 */
अटल काष्ठा ubi_ainf_volume *add_vol(काष्ठा ubi_attach_info *ai, पूर्णांक vol_id,
				       पूर्णांक used_ebs, पूर्णांक data_pad, u8 vol_type,
				       पूर्णांक last_eb_bytes)
अणु
	काष्ठा ubi_ainf_volume *av;

	av = ubi_add_av(ai, vol_id);
	अगर (IS_ERR(av))
		वापस av;

	av->data_pad = data_pad;
	av->last_data_size = last_eb_bytes;
	av->compat = 0;
	av->vol_type = vol_type;
	अगर (av->vol_type == UBI_STATIC_VOLUME)
		av->used_ebs = used_ebs;

	dbg_bld("found volume (ID %i)", vol_id);
	वापस av;
पूर्ण

/**
 * assign_aeb_to_av - assigns a SEB to a given ainf_volume and हटाओs it
 * from it's original list.
 * @ai: ubi_attach_info object
 * @aeb: the to be asचिन्हित SEB
 * @av: target scan volume
 */
अटल व्योम assign_aeb_to_av(काष्ठा ubi_attach_info *ai,
			     काष्ठा ubi_ainf_peb *aeb,
			     काष्ठा ubi_ainf_volume *av)
अणु
	काष्ठा ubi_ainf_peb *पंचांगp_aeb;
	काष्ठा rb_node **p = &av->root.rb_node, *parent = शून्य;

	जबतक (*p) अणु
		parent = *p;

		पंचांगp_aeb = rb_entry(parent, काष्ठा ubi_ainf_peb, u.rb);
		अगर (aeb->lnum != पंचांगp_aeb->lnum) अणु
			अगर (aeb->lnum < पंचांगp_aeb->lnum)
				p = &(*p)->rb_left;
			अन्यथा
				p = &(*p)->rb_right;

			जारी;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	list_del(&aeb->u.list);
	av->leb_count++;

	rb_link_node(&aeb->u.rb, parent, p);
	rb_insert_color(&aeb->u.rb, &av->root);
पूर्ण

/**
 * update_vol - inserts or updates a LEB which was found a pool.
 * @ubi: the UBI device object
 * @ai: attach info object
 * @av: the volume this LEB beदीर्घs to
 * @new_vh: the volume header derived from new_aeb
 * @new_aeb: the AEB to be examined
 *
 * Returns 0 on success, < 0 indicates an पूर्णांकernal error.
 */
अटल पूर्णांक update_vol(काष्ठा ubi_device *ubi, काष्ठा ubi_attach_info *ai,
		      काष्ठा ubi_ainf_volume *av, काष्ठा ubi_vid_hdr *new_vh,
		      काष्ठा ubi_ainf_peb *new_aeb)
अणु
	काष्ठा rb_node **p = &av->root.rb_node, *parent = शून्य;
	काष्ठा ubi_ainf_peb *aeb, *victim;
	पूर्णांक cmp_res;

	जबतक (*p) अणु
		parent = *p;
		aeb = rb_entry(parent, काष्ठा ubi_ainf_peb, u.rb);

		अगर (be32_to_cpu(new_vh->lnum) != aeb->lnum) अणु
			अगर (be32_to_cpu(new_vh->lnum) < aeb->lnum)
				p = &(*p)->rb_left;
			अन्यथा
				p = &(*p)->rb_right;

			जारी;
		पूर्ण

		/* This हाल can happen अगर the fasपंचांगap माला_लो written
		 * because of a volume change (creation, deletion, ..).
		 * Then a PEB can be within the persistent EBA and the pool.
		 */
		अगर (aeb->pnum == new_aeb->pnum) अणु
			ubi_निश्चित(aeb->lnum == new_aeb->lnum);
			ubi_मुक्त_aeb(ai, new_aeb);

			वापस 0;
		पूर्ण

		cmp_res = ubi_compare_lebs(ubi, aeb, new_aeb->pnum, new_vh);
		अगर (cmp_res < 0)
			वापस cmp_res;

		/* new_aeb is newer */
		अगर (cmp_res & 1) अणु
			victim = ubi_alloc_aeb(ai, aeb->pnum, aeb->ec);
			अगर (!victim)
				वापस -ENOMEM;

			list_add_tail(&victim->u.list, &ai->erase);

			अगर (av->highest_lnum == be32_to_cpu(new_vh->lnum))
				av->last_data_size =
					be32_to_cpu(new_vh->data_size);

			dbg_bld("vol %i: AEB %i's PEB %i is the newer",
				av->vol_id, aeb->lnum, new_aeb->pnum);

			aeb->ec = new_aeb->ec;
			aeb->pnum = new_aeb->pnum;
			aeb->copy_flag = new_vh->copy_flag;
			aeb->scrub = new_aeb->scrub;
			aeb->sqnum = new_aeb->sqnum;
			ubi_मुक्त_aeb(ai, new_aeb);

		/* new_aeb is older */
		पूर्ण अन्यथा अणु
			dbg_bld("vol %i: AEB %i's PEB %i is old, dropping it",
				av->vol_id, aeb->lnum, new_aeb->pnum);
			list_add_tail(&new_aeb->u.list, &ai->erase);
		पूर्ण

		वापस 0;
	पूर्ण
	/* This LEB is new, let's add it to the volume */

	अगर (av->highest_lnum <= be32_to_cpu(new_vh->lnum)) अणु
		av->highest_lnum = be32_to_cpu(new_vh->lnum);
		av->last_data_size = be32_to_cpu(new_vh->data_size);
	पूर्ण

	अगर (av->vol_type == UBI_STATIC_VOLUME)
		av->used_ebs = be32_to_cpu(new_vh->used_ebs);

	av->leb_count++;

	rb_link_node(&new_aeb->u.rb, parent, p);
	rb_insert_color(&new_aeb->u.rb, &av->root);

	वापस 0;
पूर्ण

/**
 * process_pool_aeb - we found a non-empty PEB in a pool.
 * @ubi: UBI device object
 * @ai: attach info object
 * @new_vh: the volume header derived from new_aeb
 * @new_aeb: the AEB to be examined
 *
 * Returns 0 on success, < 0 indicates an पूर्णांकernal error.
 */
अटल पूर्णांक process_pool_aeb(काष्ठा ubi_device *ubi, काष्ठा ubi_attach_info *ai,
			    काष्ठा ubi_vid_hdr *new_vh,
			    काष्ठा ubi_ainf_peb *new_aeb)
अणु
	पूर्णांक vol_id = be32_to_cpu(new_vh->vol_id);
	काष्ठा ubi_ainf_volume *av;

	अगर (vol_id == UBI_FM_SB_VOLUME_ID || vol_id == UBI_FM_DATA_VOLUME_ID) अणु
		ubi_मुक्त_aeb(ai, new_aeb);

		वापस 0;
	पूर्ण

	/* Find the volume this SEB beदीर्घs to */
	av = ubi_find_av(ai, vol_id);
	अगर (!av) अणु
		ubi_err(ubi, "orphaned volume in fastmap pool!");
		ubi_मुक्त_aeb(ai, new_aeb);
		वापस UBI_BAD_FASTMAP;
	पूर्ण

	ubi_निश्चित(vol_id == av->vol_id);

	वापस update_vol(ubi, ai, av, new_vh, new_aeb);
पूर्ण

/**
 * unmap_peb - unmap a PEB.
 * If fasपंचांगap detects a मुक्त PEB in the pool it has to check whether
 * this PEB has been unmapped after writing the fasपंचांगap.
 *
 * @ai: UBI attach info object
 * @pnum: The PEB to be unmapped
 */
अटल व्योम unmap_peb(काष्ठा ubi_attach_info *ai, पूर्णांक pnum)
अणु
	काष्ठा ubi_ainf_volume *av;
	काष्ठा rb_node *node, *node2;
	काष्ठा ubi_ainf_peb *aeb;

	ubi_rb_क्रम_each_entry(node, av, &ai->volumes, rb) अणु
		ubi_rb_क्रम_each_entry(node2, aeb, &av->root, u.rb) अणु
			अगर (aeb->pnum == pnum) अणु
				rb_erase(&aeb->u.rb, &av->root);
				av->leb_count--;
				ubi_मुक्त_aeb(ai, aeb);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * scan_pool - scans a pool क्रम changed (no दीर्घer empty PEBs).
 * @ubi: UBI device object
 * @ai: attach info object
 * @pebs: an array of all PEB numbers in the to be scanned pool
 * @pool_size: size of the pool (number of entries in @pebs)
 * @max_sqnum: poपूर्णांकer to the maximal sequence number
 * @मुक्त: list of PEBs which are most likely मुक्त (and go पूर्णांकo @ai->मुक्त)
 *
 * Returns 0 on success, अगर the pool is unusable UBI_BAD_FASTMAP is वापसed.
 * < 0 indicates an पूर्णांकernal error.
 */
अटल पूर्णांक scan_pool(काष्ठा ubi_device *ubi, काष्ठा ubi_attach_info *ai,
		     __be32 *pebs, पूर्णांक pool_size, अचिन्हित दीर्घ दीर्घ *max_sqnum,
		     काष्ठा list_head *मुक्त)
अणु
	काष्ठा ubi_vid_io_buf *vb;
	काष्ठा ubi_vid_hdr *vh;
	काष्ठा ubi_ec_hdr *ech;
	काष्ठा ubi_ainf_peb *new_aeb;
	पूर्णांक i, pnum, err, ret = 0;

	ech = kzalloc(ubi->ec_hdr_alsize, GFP_KERNEL);
	अगर (!ech)
		वापस -ENOMEM;

	vb = ubi_alloc_vid_buf(ubi, GFP_KERNEL);
	अगर (!vb) अणु
		kमुक्त(ech);
		वापस -ENOMEM;
	पूर्ण

	vh = ubi_get_vid_hdr(vb);

	dbg_bld("scanning fastmap pool: size = %i", pool_size);

	/*
	 * Now scan all PEBs in the pool to find changes which have been made
	 * after the creation of the fasपंचांगap
	 */
	क्रम (i = 0; i < pool_size; i++) अणु
		पूर्णांक scrub = 0;
		पूर्णांक image_seq;

		pnum = be32_to_cpu(pebs[i]);

		अगर (ubi_io_is_bad(ubi, pnum)) अणु
			ubi_err(ubi, "bad PEB in fastmap pool!");
			ret = UBI_BAD_FASTMAP;
			जाओ out;
		पूर्ण

		err = ubi_io_पढ़ो_ec_hdr(ubi, pnum, ech, 0);
		अगर (err && err != UBI_IO_BITFLIPS) अणु
			ubi_err(ubi, "unable to read EC header! PEB:%i err:%i",
				pnum, err);
			ret = err > 0 ? UBI_BAD_FASTMAP : err;
			जाओ out;
		पूर्ण अन्यथा अगर (err == UBI_IO_BITFLIPS)
			scrub = 1;

		/*
		 * Older UBI implementations have image_seq set to zero, so
		 * we shouldn't fail अगर image_seq == 0.
		 */
		image_seq = be32_to_cpu(ech->image_seq);

		अगर (image_seq && (image_seq != ubi->image_seq)) अणु
			ubi_err(ubi, "bad image seq: 0x%x, expected: 0x%x",
				be32_to_cpu(ech->image_seq), ubi->image_seq);
			ret = UBI_BAD_FASTMAP;
			जाओ out;
		पूर्ण

		err = ubi_io_पढ़ो_vid_hdr(ubi, pnum, vb, 0);
		अगर (err == UBI_IO_FF || err == UBI_IO_FF_BITFLIPS) अणु
			अचिन्हित दीर्घ दीर्घ ec = be64_to_cpu(ech->ec);
			unmap_peb(ai, pnum);
			dbg_bld("Adding PEB to free: %i", pnum);

			अगर (err == UBI_IO_FF_BITFLIPS)
				scrub = 1;

			add_aeb(ai, मुक्त, pnum, ec, scrub);
			जारी;
		पूर्ण अन्यथा अगर (err == 0 || err == UBI_IO_BITFLIPS) अणु
			dbg_bld("Found non empty PEB:%i in pool", pnum);

			अगर (err == UBI_IO_BITFLIPS)
				scrub = 1;

			new_aeb = ubi_alloc_aeb(ai, pnum, be64_to_cpu(ech->ec));
			अगर (!new_aeb) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			new_aeb->lnum = be32_to_cpu(vh->lnum);
			new_aeb->sqnum = be64_to_cpu(vh->sqnum);
			new_aeb->copy_flag = vh->copy_flag;
			new_aeb->scrub = scrub;

			अगर (*max_sqnum < new_aeb->sqnum)
				*max_sqnum = new_aeb->sqnum;

			err = process_pool_aeb(ubi, ai, vh, new_aeb);
			अगर (err) अणु
				ret = err > 0 ? UBI_BAD_FASTMAP : err;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* We are paranoid and fall back to scanning mode */
			ubi_err(ubi, "fastmap pool PEBs contains damaged PEBs!");
			ret = err > 0 ? UBI_BAD_FASTMAP : err;
			जाओ out;
		पूर्ण

	पूर्ण

out:
	ubi_मुक्त_vid_buf(vb);
	kमुक्त(ech);
	वापस ret;
पूर्ण

/**
 * count_fasपंचांगap_pebs - Counts the PEBs found by fasपंचांगap.
 * @ai: The UBI attach info object
 */
अटल पूर्णांक count_fasपंचांगap_pebs(काष्ठा ubi_attach_info *ai)
अणु
	काष्ठा ubi_ainf_peb *aeb;
	काष्ठा ubi_ainf_volume *av;
	काष्ठा rb_node *rb1, *rb2;
	पूर्णांक n = 0;

	list_क्रम_each_entry(aeb, &ai->erase, u.list)
		n++;

	list_क्रम_each_entry(aeb, &ai->मुक्त, u.list)
		n++;

	ubi_rb_क्रम_each_entry(rb1, av, &ai->volumes, rb)
		ubi_rb_क्रम_each_entry(rb2, aeb, &av->root, u.rb)
			n++;

	वापस n;
पूर्ण

/**
 * ubi_attach_fasपंचांगap - creates ubi_attach_info from a fasपंचांगap.
 * @ubi: UBI device object
 * @ai: UBI attach info object
 * @fm: the fasपंचांगap to be attached
 *
 * Returns 0 on success, UBI_BAD_FASTMAP अगर the found fasपंचांगap was unusable.
 * < 0 indicates an पूर्णांकernal error.
 */
अटल पूर्णांक ubi_attach_fasपंचांगap(काष्ठा ubi_device *ubi,
			      काष्ठा ubi_attach_info *ai,
			      काष्ठा ubi_fasपंचांगap_layout *fm)
अणु
	काष्ठा list_head used, मुक्त;
	काष्ठा ubi_ainf_volume *av;
	काष्ठा ubi_ainf_peb *aeb, *पंचांगp_aeb, *_पंचांगp_aeb;
	काष्ठा ubi_fm_sb *fmsb;
	काष्ठा ubi_fm_hdr *fmhdr;
	काष्ठा ubi_fm_scan_pool *fmpl, *fmpl_wl;
	काष्ठा ubi_fm_ec *fmec;
	काष्ठा ubi_fm_volhdr *fmvhdr;
	काष्ठा ubi_fm_eba *fm_eba;
	पूर्णांक ret, i, j, pool_size, wl_pool_size;
	माप_प्रकार fm_pos = 0, fm_size = ubi->fm_size;
	अचिन्हित दीर्घ दीर्घ max_sqnum = 0;
	व्योम *fm_raw = ubi->fm_buf;

	INIT_LIST_HEAD(&used);
	INIT_LIST_HEAD(&मुक्त);
	ai->min_ec = UBI_MAX_ERASECOUNTER;

	fmsb = (काष्ठा ubi_fm_sb *)(fm_raw);
	ai->max_sqnum = fmsb->sqnum;
	fm_pos += माप(काष्ठा ubi_fm_sb);
	अगर (fm_pos >= fm_size)
		जाओ fail_bad;

	fmhdr = (काष्ठा ubi_fm_hdr *)(fm_raw + fm_pos);
	fm_pos += माप(*fmhdr);
	अगर (fm_pos >= fm_size)
		जाओ fail_bad;

	अगर (be32_to_cpu(fmhdr->magic) != UBI_FM_HDR_MAGIC) अणु
		ubi_err(ubi, "bad fastmap header magic: 0x%x, expected: 0x%x",
			be32_to_cpu(fmhdr->magic), UBI_FM_HDR_MAGIC);
		जाओ fail_bad;
	पूर्ण

	fmpl = (काष्ठा ubi_fm_scan_pool *)(fm_raw + fm_pos);
	fm_pos += माप(*fmpl);
	अगर (fm_pos >= fm_size)
		जाओ fail_bad;
	अगर (be32_to_cpu(fmpl->magic) != UBI_FM_POOL_MAGIC) अणु
		ubi_err(ubi, "bad fastmap pool magic: 0x%x, expected: 0x%x",
			be32_to_cpu(fmpl->magic), UBI_FM_POOL_MAGIC);
		जाओ fail_bad;
	पूर्ण

	fmpl_wl = (काष्ठा ubi_fm_scan_pool *)(fm_raw + fm_pos);
	fm_pos += माप(*fmpl_wl);
	अगर (fm_pos >= fm_size)
		जाओ fail_bad;
	अगर (be32_to_cpu(fmpl_wl->magic) != UBI_FM_POOL_MAGIC) अणु
		ubi_err(ubi, "bad fastmap WL pool magic: 0x%x, expected: 0x%x",
			be32_to_cpu(fmpl_wl->magic), UBI_FM_POOL_MAGIC);
		जाओ fail_bad;
	पूर्ण

	pool_size = be16_to_cpu(fmpl->size);
	wl_pool_size = be16_to_cpu(fmpl_wl->size);
	fm->max_pool_size = be16_to_cpu(fmpl->max_size);
	fm->max_wl_pool_size = be16_to_cpu(fmpl_wl->max_size);

	अगर (pool_size > UBI_FM_MAX_POOL_SIZE || pool_size < 0) अणु
		ubi_err(ubi, "bad pool size: %i", pool_size);
		जाओ fail_bad;
	पूर्ण

	अगर (wl_pool_size > UBI_FM_MAX_POOL_SIZE || wl_pool_size < 0) अणु
		ubi_err(ubi, "bad WL pool size: %i", wl_pool_size);
		जाओ fail_bad;
	पूर्ण


	अगर (fm->max_pool_size > UBI_FM_MAX_POOL_SIZE ||
	    fm->max_pool_size < 0) अणु
		ubi_err(ubi, "bad maximal pool size: %i", fm->max_pool_size);
		जाओ fail_bad;
	पूर्ण

	अगर (fm->max_wl_pool_size > UBI_FM_MAX_POOL_SIZE ||
	    fm->max_wl_pool_size < 0) अणु
		ubi_err(ubi, "bad maximal WL pool size: %i",
			fm->max_wl_pool_size);
		जाओ fail_bad;
	पूर्ण

	/* पढ़ो EC values from मुक्त list */
	क्रम (i = 0; i < be32_to_cpu(fmhdr->मुक्त_peb_count); i++) अणु
		fmec = (काष्ठा ubi_fm_ec *)(fm_raw + fm_pos);
		fm_pos += माप(*fmec);
		अगर (fm_pos >= fm_size)
			जाओ fail_bad;

		add_aeb(ai, &ai->मुक्त, be32_to_cpu(fmec->pnum),
			be32_to_cpu(fmec->ec), 0);
	पूर्ण

	/* पढ़ो EC values from used list */
	क्रम (i = 0; i < be32_to_cpu(fmhdr->used_peb_count); i++) अणु
		fmec = (काष्ठा ubi_fm_ec *)(fm_raw + fm_pos);
		fm_pos += माप(*fmec);
		अगर (fm_pos >= fm_size)
			जाओ fail_bad;

		add_aeb(ai, &used, be32_to_cpu(fmec->pnum),
			be32_to_cpu(fmec->ec), 0);
	पूर्ण

	/* पढ़ो EC values from scrub list */
	क्रम (i = 0; i < be32_to_cpu(fmhdr->scrub_peb_count); i++) अणु
		fmec = (काष्ठा ubi_fm_ec *)(fm_raw + fm_pos);
		fm_pos += माप(*fmec);
		अगर (fm_pos >= fm_size)
			जाओ fail_bad;

		add_aeb(ai, &used, be32_to_cpu(fmec->pnum),
			be32_to_cpu(fmec->ec), 1);
	पूर्ण

	/* पढ़ो EC values from erase list */
	क्रम (i = 0; i < be32_to_cpu(fmhdr->erase_peb_count); i++) अणु
		fmec = (काष्ठा ubi_fm_ec *)(fm_raw + fm_pos);
		fm_pos += माप(*fmec);
		अगर (fm_pos >= fm_size)
			जाओ fail_bad;

		add_aeb(ai, &ai->erase, be32_to_cpu(fmec->pnum),
			be32_to_cpu(fmec->ec), 1);
	पूर्ण

	ai->mean_ec = भाग_u64(ai->ec_sum, ai->ec_count);
	ai->bad_peb_count = be32_to_cpu(fmhdr->bad_peb_count);

	/* Iterate over all volumes and पढ़ो their EBA table */
	क्रम (i = 0; i < be32_to_cpu(fmhdr->vol_count); i++) अणु
		fmvhdr = (काष्ठा ubi_fm_volhdr *)(fm_raw + fm_pos);
		fm_pos += माप(*fmvhdr);
		अगर (fm_pos >= fm_size)
			जाओ fail_bad;

		अगर (be32_to_cpu(fmvhdr->magic) != UBI_FM_VHDR_MAGIC) अणु
			ubi_err(ubi, "bad fastmap vol header magic: 0x%x, expected: 0x%x",
				be32_to_cpu(fmvhdr->magic), UBI_FM_VHDR_MAGIC);
			जाओ fail_bad;
		पूर्ण

		av = add_vol(ai, be32_to_cpu(fmvhdr->vol_id),
			     be32_to_cpu(fmvhdr->used_ebs),
			     be32_to_cpu(fmvhdr->data_pad),
			     fmvhdr->vol_type,
			     be32_to_cpu(fmvhdr->last_eb_bytes));

		अगर (IS_ERR(av)) अणु
			अगर (PTR_ERR(av) == -EEXIST)
				ubi_err(ubi, "volume (ID %i) already exists",
					fmvhdr->vol_id);

			जाओ fail_bad;
		पूर्ण

		ai->vols_found++;
		अगर (ai->highest_vol_id < be32_to_cpu(fmvhdr->vol_id))
			ai->highest_vol_id = be32_to_cpu(fmvhdr->vol_id);

		fm_eba = (काष्ठा ubi_fm_eba *)(fm_raw + fm_pos);
		fm_pos += माप(*fm_eba);
		fm_pos += (माप(__be32) * be32_to_cpu(fm_eba->reserved_pebs));
		अगर (fm_pos >= fm_size)
			जाओ fail_bad;

		अगर (be32_to_cpu(fm_eba->magic) != UBI_FM_EBA_MAGIC) अणु
			ubi_err(ubi, "bad fastmap EBA header magic: 0x%x, expected: 0x%x",
				be32_to_cpu(fm_eba->magic), UBI_FM_EBA_MAGIC);
			जाओ fail_bad;
		पूर्ण

		क्रम (j = 0; j < be32_to_cpu(fm_eba->reserved_pebs); j++) अणु
			पूर्णांक pnum = be32_to_cpu(fm_eba->pnum[j]);

			अगर (pnum < 0)
				जारी;

			aeb = शून्य;
			list_क्रम_each_entry(पंचांगp_aeb, &used, u.list) अणु
				अगर (पंचांगp_aeb->pnum == pnum) अणु
					aeb = पंचांगp_aeb;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (!aeb) अणु
				ubi_err(ubi, "PEB %i is in EBA but not in used list", pnum);
				जाओ fail_bad;
			पूर्ण

			aeb->lnum = j;

			अगर (av->highest_lnum <= aeb->lnum)
				av->highest_lnum = aeb->lnum;

			assign_aeb_to_av(ai, aeb, av);

			dbg_bld("inserting PEB:%i (LEB %i) to vol %i",
				aeb->pnum, aeb->lnum, av->vol_id);
		पूर्ण
	पूर्ण

	ret = scan_pool(ubi, ai, fmpl->pebs, pool_size, &max_sqnum, &मुक्त);
	अगर (ret)
		जाओ fail;

	ret = scan_pool(ubi, ai, fmpl_wl->pebs, wl_pool_size, &max_sqnum, &मुक्त);
	अगर (ret)
		जाओ fail;

	अगर (max_sqnum > ai->max_sqnum)
		ai->max_sqnum = max_sqnum;

	list_क्रम_each_entry_safe(पंचांगp_aeb, _पंचांगp_aeb, &मुक्त, u.list)
		list_move_tail(&पंचांगp_aeb->u.list, &ai->मुक्त);

	list_क्रम_each_entry_safe(पंचांगp_aeb, _पंचांगp_aeb, &used, u.list)
		list_move_tail(&पंचांगp_aeb->u.list, &ai->erase);

	ubi_निश्चित(list_empty(&मुक्त));

	/*
	 * If fasपंचांगap is leaking PEBs (must not happen), उठाओ a
	 * fat warning and fall back to scanning mode.
	 * We करो this here because in ubi_wl_init() it's too late
	 * and we cannot fall back to scanning.
	 */
	अगर (WARN_ON(count_fasपंचांगap_pebs(ai) != ubi->peb_count -
		    ai->bad_peb_count - fm->used_blocks))
		जाओ fail_bad;

	वापस 0;

fail_bad:
	ret = UBI_BAD_FASTMAP;
fail:
	list_क्रम_each_entry_safe(पंचांगp_aeb, _पंचांगp_aeb, &used, u.list) अणु
		list_del(&पंचांगp_aeb->u.list);
		ubi_मुक्त_aeb(ai, पंचांगp_aeb);
	पूर्ण
	list_क्रम_each_entry_safe(पंचांगp_aeb, _पंचांगp_aeb, &मुक्त, u.list) अणु
		list_del(&पंचांगp_aeb->u.list);
		ubi_मुक्त_aeb(ai, पंचांगp_aeb);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * find_fm_anchor - find the most recent Fasपंचांगap superblock (anchor)
 * @ai: UBI attach info to be filled
 */
अटल पूर्णांक find_fm_anchor(काष्ठा ubi_attach_info *ai)
अणु
	पूर्णांक ret = -1;
	काष्ठा ubi_ainf_peb *aeb;
	अचिन्हित दीर्घ दीर्घ max_sqnum = 0;

	list_क्रम_each_entry(aeb, &ai->fasपंचांगap, u.list) अणु
		अगर (aeb->vol_id == UBI_FM_SB_VOLUME_ID && aeb->sqnum > max_sqnum) अणु
			max_sqnum = aeb->sqnum;
			ret = aeb->pnum;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा ubi_ainf_peb *clone_aeb(काष्ठा ubi_attach_info *ai,
				      काष्ठा ubi_ainf_peb *old)
अणु
	काष्ठा ubi_ainf_peb *new;

	new = ubi_alloc_aeb(ai, old->pnum, old->ec);
	अगर (!new)
		वापस शून्य;

	new->vol_id = old->vol_id;
	new->sqnum = old->sqnum;
	new->lnum = old->lnum;
	new->scrub = old->scrub;
	new->copy_flag = old->copy_flag;

	वापस new;
पूर्ण

/**
 * ubi_scan_fasपंचांगap - scan the fasपंचांगap.
 * @ubi: UBI device object
 * @ai: UBI attach info to be filled
 * @scan_ai: UBI attach info from the first 64 PEBs,
 *           used to find the most recent Fasपंचांगap data काष्ठाure
 *
 * Returns 0 on success, UBI_NO_FASTMAP अगर no fasपंचांगap was found,
 * UBI_BAD_FASTMAP अगर one was found but is not usable.
 * < 0 indicates an पूर्णांकernal error.
 */
पूर्णांक ubi_scan_fasपंचांगap(काष्ठा ubi_device *ubi, काष्ठा ubi_attach_info *ai,
		     काष्ठा ubi_attach_info *scan_ai)
अणु
	काष्ठा ubi_fm_sb *fmsb, *fmsb2;
	काष्ठा ubi_vid_io_buf *vb;
	काष्ठा ubi_vid_hdr *vh;
	काष्ठा ubi_ec_hdr *ech;
	काष्ठा ubi_fasपंचांगap_layout *fm;
	काष्ठा ubi_ainf_peb *aeb;
	पूर्णांक i, used_blocks, pnum, fm_anchor, ret = 0;
	माप_प्रकार fm_size;
	__be32 crc, पंचांगp_crc;
	अचिन्हित दीर्घ दीर्घ sqnum = 0;

	fm_anchor = find_fm_anchor(scan_ai);
	अगर (fm_anchor < 0)
		वापस UBI_NO_FASTMAP;

	/* Copy all (possible) fasपंचांगap blocks पूर्णांकo our new attach काष्ठाure. */
	list_क्रम_each_entry(aeb, &scan_ai->fasपंचांगap, u.list) अणु
		काष्ठा ubi_ainf_peb *new;

		new = clone_aeb(ai, aeb);
		अगर (!new)
			वापस -ENOMEM;

		list_add(&new->u.list, &ai->fasपंचांगap);
	पूर्ण

	करोwn_ग_लिखो(&ubi->fm_protect);
	स_रखो(ubi->fm_buf, 0, ubi->fm_size);

	fmsb = kदो_स्मृति(माप(*fmsb), GFP_KERNEL);
	अगर (!fmsb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	fm = kzalloc(माप(*fm), GFP_KERNEL);
	अगर (!fm) अणु
		ret = -ENOMEM;
		kमुक्त(fmsb);
		जाओ out;
	पूर्ण

	ret = ubi_io_पढ़ो_data(ubi, fmsb, fm_anchor, 0, माप(*fmsb));
	अगर (ret && ret != UBI_IO_BITFLIPS)
		जाओ मुक्त_fm_sb;
	अन्यथा अगर (ret == UBI_IO_BITFLIPS)
		fm->to_be_tortured[0] = 1;

	अगर (be32_to_cpu(fmsb->magic) != UBI_FM_SB_MAGIC) अणु
		ubi_err(ubi, "bad super block magic: 0x%x, expected: 0x%x",
			be32_to_cpu(fmsb->magic), UBI_FM_SB_MAGIC);
		ret = UBI_BAD_FASTMAP;
		जाओ मुक्त_fm_sb;
	पूर्ण

	अगर (fmsb->version != UBI_FM_FMT_VERSION) अणु
		ubi_err(ubi, "bad fastmap version: %i, expected: %i",
			fmsb->version, UBI_FM_FMT_VERSION);
		ret = UBI_BAD_FASTMAP;
		जाओ मुक्त_fm_sb;
	पूर्ण

	used_blocks = be32_to_cpu(fmsb->used_blocks);
	अगर (used_blocks > UBI_FM_MAX_BLOCKS || used_blocks < 1) अणु
		ubi_err(ubi, "number of fastmap blocks is invalid: %i",
			used_blocks);
		ret = UBI_BAD_FASTMAP;
		जाओ मुक्त_fm_sb;
	पूर्ण

	fm_size = ubi->leb_size * used_blocks;
	अगर (fm_size != ubi->fm_size) अणु
		ubi_err(ubi, "bad fastmap size: %zi, expected: %zi",
			fm_size, ubi->fm_size);
		ret = UBI_BAD_FASTMAP;
		जाओ मुक्त_fm_sb;
	पूर्ण

	ech = kzalloc(ubi->ec_hdr_alsize, GFP_KERNEL);
	अगर (!ech) अणु
		ret = -ENOMEM;
		जाओ मुक्त_fm_sb;
	पूर्ण

	vb = ubi_alloc_vid_buf(ubi, GFP_KERNEL);
	अगर (!vb) अणु
		ret = -ENOMEM;
		जाओ मुक्त_hdr;
	पूर्ण

	vh = ubi_get_vid_hdr(vb);

	क्रम (i = 0; i < used_blocks; i++) अणु
		पूर्णांक image_seq;

		pnum = be32_to_cpu(fmsb->block_loc[i]);

		अगर (ubi_io_is_bad(ubi, pnum)) अणु
			ret = UBI_BAD_FASTMAP;
			जाओ मुक्त_hdr;
		पूर्ण

		अगर (i == 0 && pnum != fm_anchor) अणु
			ubi_err(ubi, "Fastmap anchor PEB mismatch: PEB: %i vs. %i",
				pnum, fm_anchor);
			ret = UBI_BAD_FASTMAP;
			जाओ मुक्त_hdr;
		पूर्ण

		ret = ubi_io_पढ़ो_ec_hdr(ubi, pnum, ech, 0);
		अगर (ret && ret != UBI_IO_BITFLIPS) अणु
			ubi_err(ubi, "unable to read fastmap block# %i EC (PEB: %i)",
				i, pnum);
			अगर (ret > 0)
				ret = UBI_BAD_FASTMAP;
			जाओ मुक्त_hdr;
		पूर्ण अन्यथा अगर (ret == UBI_IO_BITFLIPS)
			fm->to_be_tortured[i] = 1;

		image_seq = be32_to_cpu(ech->image_seq);
		अगर (!ubi->image_seq)
			ubi->image_seq = image_seq;

		/*
		 * Older UBI implementations have image_seq set to zero, so
		 * we shouldn't fail अगर image_seq == 0.
		 */
		अगर (image_seq && (image_seq != ubi->image_seq)) अणु
			ubi_err(ubi, "wrong image seq:%d instead of %d",
				be32_to_cpu(ech->image_seq), ubi->image_seq);
			ret = UBI_BAD_FASTMAP;
			जाओ मुक्त_hdr;
		पूर्ण

		ret = ubi_io_पढ़ो_vid_hdr(ubi, pnum, vb, 0);
		अगर (ret && ret != UBI_IO_BITFLIPS) अणु
			ubi_err(ubi, "unable to read fastmap block# %i (PEB: %i)",
				i, pnum);
			जाओ मुक्त_hdr;
		पूर्ण

		अगर (i == 0) अणु
			अगर (be32_to_cpu(vh->vol_id) != UBI_FM_SB_VOLUME_ID) अणु
				ubi_err(ubi, "bad fastmap anchor vol_id: 0x%x, expected: 0x%x",
					be32_to_cpu(vh->vol_id),
					UBI_FM_SB_VOLUME_ID);
				ret = UBI_BAD_FASTMAP;
				जाओ मुक्त_hdr;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (be32_to_cpu(vh->vol_id) != UBI_FM_DATA_VOLUME_ID) अणु
				ubi_err(ubi, "bad fastmap data vol_id: 0x%x, expected: 0x%x",
					be32_to_cpu(vh->vol_id),
					UBI_FM_DATA_VOLUME_ID);
				ret = UBI_BAD_FASTMAP;
				जाओ मुक्त_hdr;
			पूर्ण
		पूर्ण

		अगर (sqnum < be64_to_cpu(vh->sqnum))
			sqnum = be64_to_cpu(vh->sqnum);

		ret = ubi_io_पढ़ो_data(ubi, ubi->fm_buf + (ubi->leb_size * i),
				       pnum, 0, ubi->leb_size);
		अगर (ret && ret != UBI_IO_BITFLIPS) अणु
			ubi_err(ubi, "unable to read fastmap block# %i (PEB: %i, "
				"err: %i)", i, pnum, ret);
			जाओ मुक्त_hdr;
		पूर्ण
	पूर्ण

	kमुक्त(fmsb);
	fmsb = शून्य;

	fmsb2 = (काष्ठा ubi_fm_sb *)(ubi->fm_buf);
	पंचांगp_crc = be32_to_cpu(fmsb2->data_crc);
	fmsb2->data_crc = 0;
	crc = crc32(UBI_CRC32_INIT, ubi->fm_buf, fm_size);
	अगर (crc != पंचांगp_crc) अणु
		ubi_err(ubi, "fastmap data CRC is invalid");
		ubi_err(ubi, "CRC should be: 0x%x, calc: 0x%x",
			पंचांगp_crc, crc);
		ret = UBI_BAD_FASTMAP;
		जाओ मुक्त_hdr;
	पूर्ण

	fmsb2->sqnum = sqnum;

	fm->used_blocks = used_blocks;

	ret = ubi_attach_fasपंचांगap(ubi, ai, fm);
	अगर (ret) अणु
		अगर (ret > 0)
			ret = UBI_BAD_FASTMAP;
		जाओ मुक्त_hdr;
	पूर्ण

	क्रम (i = 0; i < used_blocks; i++) अणु
		काष्ठा ubi_wl_entry *e;

		e = kmem_cache_alloc(ubi_wl_entry_slab, GFP_KERNEL);
		अगर (!e) अणु
			जबतक (i--)
				kmem_cache_मुक्त(ubi_wl_entry_slab, fm->e[i]);

			ret = -ENOMEM;
			जाओ मुक्त_hdr;
		पूर्ण

		e->pnum = be32_to_cpu(fmsb2->block_loc[i]);
		e->ec = be32_to_cpu(fmsb2->block_ec[i]);
		fm->e[i] = e;
	पूर्ण

	ubi->fm = fm;
	ubi->fm_pool.max_size = ubi->fm->max_pool_size;
	ubi->fm_wl_pool.max_size = ubi->fm->max_wl_pool_size;
	ubi_msg(ubi, "attached by fastmap");
	ubi_msg(ubi, "fastmap pool size: %d", ubi->fm_pool.max_size);
	ubi_msg(ubi, "fastmap WL pool size: %d",
		ubi->fm_wl_pool.max_size);
	ubi->fm_disabled = 0;
	ubi->fast_attach = 1;

	ubi_मुक्त_vid_buf(vb);
	kमुक्त(ech);
out:
	up_ग_लिखो(&ubi->fm_protect);
	अगर (ret == UBI_BAD_FASTMAP)
		ubi_err(ubi, "Attach by fastmap failed, doing a full scan!");
	वापस ret;

मुक्त_hdr:
	ubi_मुक्त_vid_buf(vb);
	kमुक्त(ech);
मुक्त_fm_sb:
	kमुक्त(fmsb);
	kमुक्त(fm);
	जाओ out;
पूर्ण

पूर्णांक ubi_fasपंचांगap_init_checkmap(काष्ठा ubi_volume *vol, पूर्णांक leb_count)
अणु
	काष्ठा ubi_device *ubi = vol->ubi;

	अगर (!ubi->fast_attach)
		वापस 0;

	vol->checkmap = kसुस्मृति(BITS_TO_LONGS(leb_count), माप(अचिन्हित दीर्घ),
				GFP_KERNEL);
	अगर (!vol->checkmap)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम ubi_fasपंचांगap_destroy_checkmap(काष्ठा ubi_volume *vol)
अणु
	kमुक्त(vol->checkmap);
पूर्ण

/**
 * ubi_ग_लिखो_fasपंचांगap - ग_लिखोs a fasपंचांगap.
 * @ubi: UBI device object
 * @new_fm: the to be written fasपंचांगap
 *
 * Returns 0 on success, < 0 indicates an पूर्णांकernal error.
 */
अटल पूर्णांक ubi_ग_लिखो_fasपंचांगap(काष्ठा ubi_device *ubi,
			     काष्ठा ubi_fasपंचांगap_layout *new_fm)
अणु
	माप_प्रकार fm_pos = 0;
	व्योम *fm_raw;
	काष्ठा ubi_fm_sb *fmsb;
	काष्ठा ubi_fm_hdr *fmh;
	काष्ठा ubi_fm_scan_pool *fmpl, *fmpl_wl;
	काष्ठा ubi_fm_ec *fec;
	काष्ठा ubi_fm_volhdr *fvh;
	काष्ठा ubi_fm_eba *feba;
	काष्ठा ubi_wl_entry *wl_e;
	काष्ठा ubi_volume *vol;
	काष्ठा ubi_vid_io_buf *avbuf, *dvbuf;
	काष्ठा ubi_vid_hdr *avhdr, *dvhdr;
	काष्ठा ubi_work *ubi_wrk;
	काष्ठा rb_node *पंचांगp_rb;
	पूर्णांक ret, i, j, मुक्त_peb_count, used_peb_count, vol_count;
	पूर्णांक scrub_peb_count, erase_peb_count;
	अचिन्हित दीर्घ *seen_pebs;

	fm_raw = ubi->fm_buf;
	स_रखो(ubi->fm_buf, 0, ubi->fm_size);

	avbuf = new_fm_vbuf(ubi, UBI_FM_SB_VOLUME_ID);
	अगर (!avbuf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	dvbuf = new_fm_vbuf(ubi, UBI_FM_DATA_VOLUME_ID);
	अगर (!dvbuf) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_avbuf;
	पूर्ण

	avhdr = ubi_get_vid_hdr(avbuf);
	dvhdr = ubi_get_vid_hdr(dvbuf);

	seen_pebs = init_seen(ubi);
	अगर (IS_ERR(seen_pebs)) अणु
		ret = PTR_ERR(seen_pebs);
		जाओ out_मुक्त_dvbuf;
	पूर्ण

	spin_lock(&ubi->volumes_lock);
	spin_lock(&ubi->wl_lock);

	fmsb = (काष्ठा ubi_fm_sb *)fm_raw;
	fm_pos += माप(*fmsb);
	ubi_निश्चित(fm_pos <= ubi->fm_size);

	fmh = (काष्ठा ubi_fm_hdr *)(fm_raw + fm_pos);
	fm_pos += माप(*fmh);
	ubi_निश्चित(fm_pos <= ubi->fm_size);

	fmsb->magic = cpu_to_be32(UBI_FM_SB_MAGIC);
	fmsb->version = UBI_FM_FMT_VERSION;
	fmsb->used_blocks = cpu_to_be32(new_fm->used_blocks);
	/* the max sqnum will be filled in जबतक *पढ़ोing* the fasपंचांगap */
	fmsb->sqnum = 0;

	fmh->magic = cpu_to_be32(UBI_FM_HDR_MAGIC);
	मुक्त_peb_count = 0;
	used_peb_count = 0;
	scrub_peb_count = 0;
	erase_peb_count = 0;
	vol_count = 0;

	fmpl = (काष्ठा ubi_fm_scan_pool *)(fm_raw + fm_pos);
	fm_pos += माप(*fmpl);
	fmpl->magic = cpu_to_be32(UBI_FM_POOL_MAGIC);
	fmpl->size = cpu_to_be16(ubi->fm_pool.size);
	fmpl->max_size = cpu_to_be16(ubi->fm_pool.max_size);

	क्रम (i = 0; i < ubi->fm_pool.size; i++) अणु
		fmpl->pebs[i] = cpu_to_be32(ubi->fm_pool.pebs[i]);
		set_seen(ubi, ubi->fm_pool.pebs[i], seen_pebs);
	पूर्ण

	fmpl_wl = (काष्ठा ubi_fm_scan_pool *)(fm_raw + fm_pos);
	fm_pos += माप(*fmpl_wl);
	fmpl_wl->magic = cpu_to_be32(UBI_FM_POOL_MAGIC);
	fmpl_wl->size = cpu_to_be16(ubi->fm_wl_pool.size);
	fmpl_wl->max_size = cpu_to_be16(ubi->fm_wl_pool.max_size);

	क्रम (i = 0; i < ubi->fm_wl_pool.size; i++) अणु
		fmpl_wl->pebs[i] = cpu_to_be32(ubi->fm_wl_pool.pebs[i]);
		set_seen(ubi, ubi->fm_wl_pool.pebs[i], seen_pebs);
	पूर्ण

	ubi_क्रम_each_मुक्त_peb(ubi, wl_e, पंचांगp_rb) अणु
		fec = (काष्ठा ubi_fm_ec *)(fm_raw + fm_pos);

		fec->pnum = cpu_to_be32(wl_e->pnum);
		set_seen(ubi, wl_e->pnum, seen_pebs);
		fec->ec = cpu_to_be32(wl_e->ec);

		मुक्त_peb_count++;
		fm_pos += माप(*fec);
		ubi_निश्चित(fm_pos <= ubi->fm_size);
	पूर्ण
	अगर (ubi->fm_next_anchor) अणु
		fec = (काष्ठा ubi_fm_ec *)(fm_raw + fm_pos);

		fec->pnum = cpu_to_be32(ubi->fm_next_anchor->pnum);
		set_seen(ubi, ubi->fm_next_anchor->pnum, seen_pebs);
		fec->ec = cpu_to_be32(ubi->fm_next_anchor->ec);

		मुक्त_peb_count++;
		fm_pos += माप(*fec);
		ubi_निश्चित(fm_pos <= ubi->fm_size);
	पूर्ण
	fmh->मुक्त_peb_count = cpu_to_be32(मुक्त_peb_count);

	ubi_क्रम_each_used_peb(ubi, wl_e, पंचांगp_rb) अणु
		fec = (काष्ठा ubi_fm_ec *)(fm_raw + fm_pos);

		fec->pnum = cpu_to_be32(wl_e->pnum);
		set_seen(ubi, wl_e->pnum, seen_pebs);
		fec->ec = cpu_to_be32(wl_e->ec);

		used_peb_count++;
		fm_pos += माप(*fec);
		ubi_निश्चित(fm_pos <= ubi->fm_size);
	पूर्ण

	ubi_क्रम_each_रक्षित_peb(ubi, i, wl_e) अणु
		fec = (काष्ठा ubi_fm_ec *)(fm_raw + fm_pos);

		fec->pnum = cpu_to_be32(wl_e->pnum);
		set_seen(ubi, wl_e->pnum, seen_pebs);
		fec->ec = cpu_to_be32(wl_e->ec);

		used_peb_count++;
		fm_pos += माप(*fec);
		ubi_निश्चित(fm_pos <= ubi->fm_size);
	पूर्ण
	fmh->used_peb_count = cpu_to_be32(used_peb_count);

	ubi_क्रम_each_scrub_peb(ubi, wl_e, पंचांगp_rb) अणु
		fec = (काष्ठा ubi_fm_ec *)(fm_raw + fm_pos);

		fec->pnum = cpu_to_be32(wl_e->pnum);
		set_seen(ubi, wl_e->pnum, seen_pebs);
		fec->ec = cpu_to_be32(wl_e->ec);

		scrub_peb_count++;
		fm_pos += माप(*fec);
		ubi_निश्चित(fm_pos <= ubi->fm_size);
	पूर्ण
	fmh->scrub_peb_count = cpu_to_be32(scrub_peb_count);


	list_क्रम_each_entry(ubi_wrk, &ubi->works, list) अणु
		अगर (ubi_is_erase_work(ubi_wrk)) अणु
			wl_e = ubi_wrk->e;
			ubi_निश्चित(wl_e);

			fec = (काष्ठा ubi_fm_ec *)(fm_raw + fm_pos);

			fec->pnum = cpu_to_be32(wl_e->pnum);
			set_seen(ubi, wl_e->pnum, seen_pebs);
			fec->ec = cpu_to_be32(wl_e->ec);

			erase_peb_count++;
			fm_pos += माप(*fec);
			ubi_निश्चित(fm_pos <= ubi->fm_size);
		पूर्ण
	पूर्ण
	fmh->erase_peb_count = cpu_to_be32(erase_peb_count);

	क्रम (i = 0; i < UBI_MAX_VOLUMES + UBI_INT_VOL_COUNT; i++) अणु
		vol = ubi->volumes[i];

		अगर (!vol)
			जारी;

		vol_count++;

		fvh = (काष्ठा ubi_fm_volhdr *)(fm_raw + fm_pos);
		fm_pos += माप(*fvh);
		ubi_निश्चित(fm_pos <= ubi->fm_size);

		fvh->magic = cpu_to_be32(UBI_FM_VHDR_MAGIC);
		fvh->vol_id = cpu_to_be32(vol->vol_id);
		fvh->vol_type = vol->vol_type;
		fvh->used_ebs = cpu_to_be32(vol->used_ebs);
		fvh->data_pad = cpu_to_be32(vol->data_pad);
		fvh->last_eb_bytes = cpu_to_be32(vol->last_eb_bytes);

		ubi_निश्चित(vol->vol_type == UBI_DYNAMIC_VOLUME ||
			vol->vol_type == UBI_STATIC_VOLUME);

		feba = (काष्ठा ubi_fm_eba *)(fm_raw + fm_pos);
		fm_pos += माप(*feba) + (माप(__be32) * vol->reserved_pebs);
		ubi_निश्चित(fm_pos <= ubi->fm_size);

		क्रम (j = 0; j < vol->reserved_pebs; j++) अणु
			काष्ठा ubi_eba_leb_desc ldesc;

			ubi_eba_get_ldesc(vol, j, &ldesc);
			feba->pnum[j] = cpu_to_be32(ldesc.pnum);
		पूर्ण

		feba->reserved_pebs = cpu_to_be32(j);
		feba->magic = cpu_to_be32(UBI_FM_EBA_MAGIC);
	पूर्ण
	fmh->vol_count = cpu_to_be32(vol_count);
	fmh->bad_peb_count = cpu_to_be32(ubi->bad_peb_count);

	avhdr->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
	avhdr->lnum = 0;

	spin_unlock(&ubi->wl_lock);
	spin_unlock(&ubi->volumes_lock);

	dbg_bld("writing fastmap SB to PEB %i", new_fm->e[0]->pnum);
	ret = ubi_io_ग_लिखो_vid_hdr(ubi, new_fm->e[0]->pnum, avbuf);
	अगर (ret) अणु
		ubi_err(ubi, "unable to write vid_hdr to fastmap SB!");
		जाओ out_मुक्त_seen;
	पूर्ण

	क्रम (i = 0; i < new_fm->used_blocks; i++) अणु
		fmsb->block_loc[i] = cpu_to_be32(new_fm->e[i]->pnum);
		set_seen(ubi, new_fm->e[i]->pnum, seen_pebs);
		fmsb->block_ec[i] = cpu_to_be32(new_fm->e[i]->ec);
	पूर्ण

	fmsb->data_crc = 0;
	fmsb->data_crc = cpu_to_be32(crc32(UBI_CRC32_INIT, fm_raw,
					   ubi->fm_size));

	क्रम (i = 1; i < new_fm->used_blocks; i++) अणु
		dvhdr->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
		dvhdr->lnum = cpu_to_be32(i);
		dbg_bld("writing fastmap data to PEB %i sqnum %llu",
			new_fm->e[i]->pnum, be64_to_cpu(dvhdr->sqnum));
		ret = ubi_io_ग_लिखो_vid_hdr(ubi, new_fm->e[i]->pnum, dvbuf);
		अगर (ret) अणु
			ubi_err(ubi, "unable to write vid_hdr to PEB %i!",
				new_fm->e[i]->pnum);
			जाओ out_मुक्त_seen;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < new_fm->used_blocks; i++) अणु
		ret = ubi_io_ग_लिखो_data(ubi, fm_raw + (i * ubi->leb_size),
					new_fm->e[i]->pnum, 0, ubi->leb_size);
		अगर (ret) अणु
			ubi_err(ubi, "unable to write fastmap to PEB %i!",
				new_fm->e[i]->pnum);
			जाओ out_मुक्त_seen;
		पूर्ण
	पूर्ण

	ubi_निश्चित(new_fm);
	ubi->fm = new_fm;

	ret = self_check_seen(ubi, seen_pebs);
	dbg_bld("fastmap written!");

out_मुक्त_seen:
	मुक्त_seen(seen_pebs);
out_मुक्त_dvbuf:
	ubi_मुक्त_vid_buf(dvbuf);
out_मुक्त_avbuf:
	ubi_मुक्त_vid_buf(avbuf);

out:
	वापस ret;
पूर्ण

/**
 * erase_block - Manually erase a PEB.
 * @ubi: UBI device object
 * @pnum: PEB to be erased
 *
 * Returns the new EC value on success, < 0 indicates an पूर्णांकernal error.
 */
अटल पूर्णांक erase_block(काष्ठा ubi_device *ubi, पूर्णांक pnum)
अणु
	पूर्णांक ret;
	काष्ठा ubi_ec_hdr *ec_hdr;
	दीर्घ दीर्घ ec;

	ec_hdr = kzalloc(ubi->ec_hdr_alsize, GFP_KERNEL);
	अगर (!ec_hdr)
		वापस -ENOMEM;

	ret = ubi_io_पढ़ो_ec_hdr(ubi, pnum, ec_hdr, 0);
	अगर (ret < 0)
		जाओ out;
	अन्यथा अगर (ret && ret != UBI_IO_BITFLIPS) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = ubi_io_sync_erase(ubi, pnum, 0);
	अगर (ret < 0)
		जाओ out;

	ec = be64_to_cpu(ec_hdr->ec);
	ec += ret;
	अगर (ec > UBI_MAX_ERASECOUNTER) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ec_hdr->ec = cpu_to_be64(ec);
	ret = ubi_io_ग_लिखो_ec_hdr(ubi, pnum, ec_hdr);
	अगर (ret < 0)
		जाओ out;

	ret = ec;
out:
	kमुक्त(ec_hdr);
	वापस ret;
पूर्ण

/**
 * invalidate_fasपंचांगap - destroys a fasपंचांगap.
 * @ubi: UBI device object
 *
 * This function ensures that upon next UBI attach a full scan
 * is issued. We need this अगर UBI is about to ग_लिखो a new fasपंचांगap
 * but is unable to करो so. In this हाल we have two options:
 * a) Make sure that the current fasपंचांगap will not be usued upon
 * attach समय and contine or b) fall back to RO mode to have the
 * current fasपंचांगap in a valid state.
 * Returns 0 on success, < 0 indicates an पूर्णांकernal error.
 */
अटल पूर्णांक invalidate_fasपंचांगap(काष्ठा ubi_device *ubi)
अणु
	पूर्णांक ret;
	काष्ठा ubi_fasपंचांगap_layout *fm;
	काष्ठा ubi_wl_entry *e;
	काष्ठा ubi_vid_io_buf *vb = शून्य;
	काष्ठा ubi_vid_hdr *vh;

	अगर (!ubi->fm)
		वापस 0;

	ubi->fm = शून्य;

	ret = -ENOMEM;
	fm = kzalloc(माप(*fm), GFP_KERNEL);
	अगर (!fm)
		जाओ out;

	vb = new_fm_vbuf(ubi, UBI_FM_SB_VOLUME_ID);
	अगर (!vb)
		जाओ out_मुक्त_fm;

	vh = ubi_get_vid_hdr(vb);

	ret = -ENOSPC;
	e = ubi_wl_get_fm_peb(ubi, 1);
	अगर (!e)
		जाओ out_मुक्त_fm;

	/*
	 * Create fake fasपंचांगap such that UBI will fall back
	 * to scanning mode.
	 */
	vh->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
	ret = ubi_io_ग_लिखो_vid_hdr(ubi, e->pnum, vb);
	अगर (ret < 0) अणु
		ubi_wl_put_fm_peb(ubi, e, 0, 0);
		जाओ out_मुक्त_fm;
	पूर्ण

	fm->used_blocks = 1;
	fm->e[0] = e;

	ubi->fm = fm;

out:
	ubi_मुक्त_vid_buf(vb);
	वापस ret;

out_मुक्त_fm:
	kमुक्त(fm);
	जाओ out;
पूर्ण

/**
 * वापस_fm_pebs - वापसs all PEBs used by a fasपंचांगap back to the
 * WL sub-प्रणाली.
 * @ubi: UBI device object
 * @fm: fasपंचांगap layout object
 */
अटल व्योम वापस_fm_pebs(काष्ठा ubi_device *ubi,
			   काष्ठा ubi_fasपंचांगap_layout *fm)
अणु
	पूर्णांक i;

	अगर (!fm)
		वापस;

	क्रम (i = 0; i < fm->used_blocks; i++) अणु
		अगर (fm->e[i]) अणु
			ubi_wl_put_fm_peb(ubi, fm->e[i], i,
					  fm->to_be_tortured[i]);
			fm->e[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ubi_update_fasपंचांगap - will be called by UBI अगर a volume changes or
 * a fasपंचांगap pool becomes full.
 * @ubi: UBI device object
 *
 * Returns 0 on success, < 0 indicates an पूर्णांकernal error.
 */
पूर्णांक ubi_update_fasपंचांगap(काष्ठा ubi_device *ubi)
अणु
	पूर्णांक ret, i, j;
	काष्ठा ubi_fasपंचांगap_layout *new_fm, *old_fm;
	काष्ठा ubi_wl_entry *पंचांगp_e;

	करोwn_ग_लिखो(&ubi->fm_protect);
	करोwn_ग_लिखो(&ubi->work_sem);
	करोwn_ग_लिखो(&ubi->fm_eba_sem);

	ubi_refill_pools(ubi);

	अगर (ubi->ro_mode || ubi->fm_disabled) अणु
		up_ग_लिखो(&ubi->fm_eba_sem);
		up_ग_लिखो(&ubi->work_sem);
		up_ग_लिखो(&ubi->fm_protect);
		वापस 0;
	पूर्ण

	new_fm = kzalloc(माप(*new_fm), GFP_KERNEL);
	अगर (!new_fm) अणु
		up_ग_लिखो(&ubi->fm_eba_sem);
		up_ग_लिखो(&ubi->work_sem);
		up_ग_लिखो(&ubi->fm_protect);
		वापस -ENOMEM;
	पूर्ण

	new_fm->used_blocks = ubi->fm_size / ubi->leb_size;
	old_fm = ubi->fm;
	ubi->fm = शून्य;

	अगर (new_fm->used_blocks > UBI_FM_MAX_BLOCKS) अणु
		ubi_err(ubi, "fastmap too large");
		ret = -ENOSPC;
		जाओ err;
	पूर्ण

	क्रम (i = 1; i < new_fm->used_blocks; i++) अणु
		spin_lock(&ubi->wl_lock);
		पंचांगp_e = ubi_wl_get_fm_peb(ubi, 0);
		spin_unlock(&ubi->wl_lock);

		अगर (!पंचांगp_e) अणु
			अगर (old_fm && old_fm->e[i]) अणु
				ret = erase_block(ubi, old_fm->e[i]->pnum);
				अगर (ret < 0) अणु
					ubi_err(ubi, "could not erase old fastmap PEB");

					क्रम (j = 1; j < i; j++) अणु
						ubi_wl_put_fm_peb(ubi, new_fm->e[j],
								  j, 0);
						new_fm->e[j] = शून्य;
					पूर्ण
					जाओ err;
				पूर्ण
				new_fm->e[i] = old_fm->e[i];
				old_fm->e[i] = शून्य;
			पूर्ण अन्यथा अणु
				ubi_err(ubi, "could not get any free erase block");

				क्रम (j = 1; j < i; j++) अणु
					ubi_wl_put_fm_peb(ubi, new_fm->e[j], j, 0);
					new_fm->e[j] = शून्य;
				पूर्ण

				ret = -ENOSPC;
				जाओ err;
			पूर्ण
		पूर्ण अन्यथा अणु
			new_fm->e[i] = पंचांगp_e;

			अगर (old_fm && old_fm->e[i]) अणु
				ubi_wl_put_fm_peb(ubi, old_fm->e[i], i,
						  old_fm->to_be_tortured[i]);
				old_fm->e[i] = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Old fasपंचांगap is larger than the new one */
	अगर (old_fm && new_fm->used_blocks < old_fm->used_blocks) अणु
		क्रम (i = new_fm->used_blocks; i < old_fm->used_blocks; i++) अणु
			ubi_wl_put_fm_peb(ubi, old_fm->e[i], i,
					  old_fm->to_be_tortured[i]);
			old_fm->e[i] = शून्य;
		पूर्ण
	पूर्ण

	spin_lock(&ubi->wl_lock);
	पंचांगp_e = ubi->fm_anchor;
	ubi->fm_anchor = शून्य;
	spin_unlock(&ubi->wl_lock);

	अगर (old_fm) अणु
		/* no fresh anchor PEB was found, reuse the old one */
		अगर (!पंचांगp_e) अणु
			ret = erase_block(ubi, old_fm->e[0]->pnum);
			अगर (ret < 0) अणु
				ubi_err(ubi, "could not erase old anchor PEB");

				क्रम (i = 1; i < new_fm->used_blocks; i++) अणु
					ubi_wl_put_fm_peb(ubi, new_fm->e[i],
							  i, 0);
					new_fm->e[i] = शून्य;
				पूर्ण
				जाओ err;
			पूर्ण
			new_fm->e[0] = old_fm->e[0];
			new_fm->e[0]->ec = ret;
			old_fm->e[0] = शून्य;
		पूर्ण अन्यथा अणु
			/* we've got a new anchor PEB, वापस the old one */
			ubi_wl_put_fm_peb(ubi, old_fm->e[0], 0,
					  old_fm->to_be_tortured[0]);
			new_fm->e[0] = पंचांगp_e;
			old_fm->e[0] = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!पंचांगp_e) अणु
			ubi_err(ubi, "could not find any anchor PEB");

			क्रम (i = 1; i < new_fm->used_blocks; i++) अणु
				ubi_wl_put_fm_peb(ubi, new_fm->e[i], i, 0);
				new_fm->e[i] = शून्य;
			पूर्ण

			ret = -ENOSPC;
			जाओ err;
		पूर्ण
		new_fm->e[0] = पंचांगp_e;
	पूर्ण

	ret = ubi_ग_लिखो_fasपंचांगap(ubi, new_fm);

	अगर (ret)
		जाओ err;

out_unlock:
	up_ग_लिखो(&ubi->fm_eba_sem);
	up_ग_लिखो(&ubi->work_sem);
	up_ग_लिखो(&ubi->fm_protect);
	kमुक्त(old_fm);

	ubi_ensure_anchor_pebs(ubi);

	वापस ret;

err:
	ubi_warn(ubi, "Unable to write new fastmap, err=%i", ret);

	ret = invalidate_fasपंचांगap(ubi);
	अगर (ret < 0) अणु
		ubi_err(ubi, "Unable to invalidate current fastmap!");
		ubi_ro_mode(ubi);
	पूर्ण अन्यथा अणु
		वापस_fm_pebs(ubi, old_fm);
		वापस_fm_pebs(ubi, new_fm);
		ret = 0;
	पूर्ण

	kमुक्त(new_fm);
	जाओ out_unlock;
पूर्ण
