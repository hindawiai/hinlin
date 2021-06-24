<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CXL Flash Device Driver
 *
 * Written by: Manoj N. Kumar <manoj@linux.vnet.ibm.com>, IBM Corporation
 *             Matthew R. Ochs <mrochs@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2015 IBM Corporation
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/bitsperदीर्घ.h>

#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>
#समावेश <uapi/scsi/cxlflash_ioctl.h>

#समावेश "sislite.h"
#समावेश "common.h"
#समावेश "vlun.h"
#समावेश "superpipe.h"

/**
 * marshal_virt_to_resize() - translate uभव to resize काष्ठाure
 * @virt:	Source काष्ठाure from which to translate/copy.
 * @resize:	Destination काष्ठाure क्रम the translate/copy.
 */
अटल व्योम marshal_virt_to_resize(काष्ठा dk_cxlflash_uभव *virt,
				   काष्ठा dk_cxlflash_resize *resize)
अणु
	resize->hdr = virt->hdr;
	resize->context_id = virt->context_id;
	resize->rsrc_handle = virt->rsrc_handle;
	resize->req_size = virt->lun_size;
	resize->last_lba = virt->last_lba;
पूर्ण

/**
 * marshal_clone_to_rele() - translate clone to release काष्ठाure
 * @clone:	Source काष्ठाure from which to translate/copy.
 * @release:	Destination काष्ठाure क्रम the translate/copy.
 */
अटल व्योम marshal_clone_to_rele(काष्ठा dk_cxlflash_clone *clone,
				  काष्ठा dk_cxlflash_release *release)
अणु
	release->hdr = clone->hdr;
	release->context_id = clone->context_id_dst;
पूर्ण

/**
 * ba_init() - initializes a block allocator
 * @ba_lun:	Block allocator to initialize.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ba_init(काष्ठा ba_lun *ba_lun)
अणु
	काष्ठा ba_lun_info *bali = शून्य;
	पूर्णांक lun_size_au = 0, i = 0;
	पूर्णांक last_word_underflow = 0;
	u64 *lam;

	pr_debug("%s: Initializing LUN: lun_id=%016llx "
		 "ba_lun->lsize=%lx ba_lun->au_size=%lX\n",
		__func__, ba_lun->lun_id, ba_lun->lsize, ba_lun->au_size);

	/* Calculate bit map size */
	lun_size_au = ba_lun->lsize / ba_lun->au_size;
	अगर (lun_size_au == 0) अणु
		pr_debug("%s: Requested LUN size of 0!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Allocate lun inक्रमmation container */
	bali = kzalloc(माप(काष्ठा ba_lun_info), GFP_KERNEL);
	अगर (unlikely(!bali)) अणु
		pr_err("%s: Failed to allocate lun_info lun_id=%016llx\n",
		       __func__, ba_lun->lun_id);
		वापस -ENOMEM;
	पूर्ण

	bali->total_aus = lun_size_au;
	bali->lun_bmap_size = lun_size_au / BITS_PER_LONG;

	अगर (lun_size_au % BITS_PER_LONG)
		bali->lun_bmap_size++;

	/* Allocate biपंचांगap space */
	bali->lun_alloc_map = kzalloc((bali->lun_bmap_size * माप(u64)),
				      GFP_KERNEL);
	अगर (unlikely(!bali->lun_alloc_map)) अणु
		pr_err("%s: Failed to allocate lun allocation map: "
		       "lun_id=%016llx\n", __func__, ba_lun->lun_id);
		kमुक्त(bali);
		वापस -ENOMEM;
	पूर्ण

	/* Initialize the bit map size and set all bits to '1' */
	bali->मुक्त_aun_cnt = lun_size_au;

	क्रम (i = 0; i < bali->lun_bmap_size; i++)
		bali->lun_alloc_map[i] = 0xFFFFFFFFFFFFFFFFULL;

	/* If the last word not fully utilized, mark extra bits as allocated */
	last_word_underflow = (bali->lun_bmap_size * BITS_PER_LONG);
	last_word_underflow -= bali->मुक्त_aun_cnt;
	अगर (last_word_underflow > 0) अणु
		lam = &bali->lun_alloc_map[bali->lun_bmap_size - 1];
		क्रम (i = (HIBIT - last_word_underflow + 1);
		     i < BITS_PER_LONG;
		     i++)
			clear_bit(i, (uदीर्घ *)lam);
	पूर्ण

	/* Initialize high elevator index, low/curr alपढ़ोy at 0 from kzalloc */
	bali->मुक्त_high_idx = bali->lun_bmap_size;

	/* Allocate clone map */
	bali->aun_clone_map = kzalloc((bali->total_aus * माप(u8)),
				      GFP_KERNEL);
	अगर (unlikely(!bali->aun_clone_map)) अणु
		pr_err("%s: Failed to allocate clone map: lun_id=%016llx\n",
		       __func__, ba_lun->lun_id);
		kमुक्त(bali->lun_alloc_map);
		kमुक्त(bali);
		वापस -ENOMEM;
	पूर्ण

	/* Pass the allocated LUN info as a handle to the user */
	ba_lun->ba_lun_handle = bali;

	pr_debug("%s: Successfully initialized the LUN: "
		 "lun_id=%016llx bitmap size=%x, free_aun_cnt=%llx\n",
		__func__, ba_lun->lun_id, bali->lun_bmap_size,
		bali->मुक्त_aun_cnt);
	वापस 0;
पूर्ण

/**
 * find_मुक्त_range() - locates a मुक्त bit within the block allocator
 * @low:	First word in block allocator to start search.
 * @high:	Last word in block allocator to search.
 * @bali:	LUN inक्रमmation काष्ठाure owning the block allocator to search.
 * @bit_word:	Passes back the word in the block allocator owning the मुक्त bit.
 *
 * Return: The bit position within the passed back word, -1 on failure
 */
अटल पूर्णांक find_मुक्त_range(u32 low,
			   u32 high,
			   काष्ठा ba_lun_info *bali, पूर्णांक *bit_word)
अणु
	पूर्णांक i;
	u64 bit_pos = -1;
	uदीर्घ *lam, num_bits;

	क्रम (i = low; i < high; i++)
		अगर (bali->lun_alloc_map[i] != 0) अणु
			lam = (uदीर्घ *)&bali->lun_alloc_map[i];
			num_bits = (माप(*lam) * BITS_PER_BYTE);
			bit_pos = find_first_bit(lam, num_bits);

			pr_devel("%s: Found free bit %llu in LUN "
				 "map entry %016llx at bitmap index = %d\n",
				 __func__, bit_pos, bali->lun_alloc_map[i], i);

			*bit_word = i;
			bali->मुक्त_aun_cnt--;
			clear_bit(bit_pos, lam);
			अवरोध;
		पूर्ण

	वापस bit_pos;
पूर्ण

/**
 * ba_alloc() - allocates a block from the block allocator
 * @ba_lun:	Block allocator from which to allocate a block.
 *
 * Return: The allocated block, -1 on failure
 */
अटल u64 ba_alloc(काष्ठा ba_lun *ba_lun)
अणु
	u64 bit_pos = -1;
	पूर्णांक bit_word = 0;
	काष्ठा ba_lun_info *bali = शून्य;

	bali = ba_lun->ba_lun_handle;

	pr_debug("%s: Received block allocation request: "
		 "lun_id=%016llx free_aun_cnt=%llx\n",
		 __func__, ba_lun->lun_id, bali->मुक्त_aun_cnt);

	अगर (bali->मुक्त_aun_cnt == 0) अणु
		pr_debug("%s: No space left on LUN: lun_id=%016llx\n",
			 __func__, ba_lun->lun_id);
		वापस -1ULL;
	पूर्ण

	/* Search to find a मुक्त entry, curr->high then low->curr */
	bit_pos = find_मुक्त_range(bali->मुक्त_curr_idx,
				  bali->मुक्त_high_idx, bali, &bit_word);
	अगर (bit_pos == -1) अणु
		bit_pos = find_मुक्त_range(bali->मुक्त_low_idx,
					  bali->मुक्त_curr_idx,
					  bali, &bit_word);
		अगर (bit_pos == -1) अणु
			pr_debug("%s: Could not find an allocation unit on LUN:"
				 " lun_id=%016llx\n", __func__, ba_lun->lun_id);
			वापस -1ULL;
		पूर्ण
	पूर्ण

	/* Update the मुक्त_curr_idx */
	अगर (bit_pos == HIBIT)
		bali->मुक्त_curr_idx = bit_word + 1;
	अन्यथा
		bali->मुक्त_curr_idx = bit_word;

	pr_debug("%s: Allocating AU number=%llx lun_id=%016llx "
		 "free_aun_cnt=%llx\n", __func__,
		 ((bit_word * BITS_PER_LONG) + bit_pos), ba_lun->lun_id,
		 bali->मुक्त_aun_cnt);

	वापस (u64) ((bit_word * BITS_PER_LONG) + bit_pos);
पूर्ण

/**
 * validate_alloc() - validates the specअगरied block has been allocated
 * @bali:		LUN info owning the block allocator.
 * @aun:		Block to validate.
 *
 * Return: 0 on success, -1 on failure
 */
अटल पूर्णांक validate_alloc(काष्ठा ba_lun_info *bali, u64 aun)
अणु
	पूर्णांक idx = 0, bit_pos = 0;

	idx = aun / BITS_PER_LONG;
	bit_pos = aun % BITS_PER_LONG;

	अगर (test_bit(bit_pos, (uदीर्घ *)&bali->lun_alloc_map[idx]))
		वापस -1;

	वापस 0;
पूर्ण

/**
 * ba_मुक्त() - मुक्तs a block from the block allocator
 * @ba_lun:	Block allocator from which to allocate a block.
 * @to_मुक्त:	Block to मुक्त.
 *
 * Return: 0 on success, -1 on failure
 */
अटल पूर्णांक ba_मुक्त(काष्ठा ba_lun *ba_lun, u64 to_मुक्त)
अणु
	पूर्णांक idx = 0, bit_pos = 0;
	काष्ठा ba_lun_info *bali = शून्य;

	bali = ba_lun->ba_lun_handle;

	अगर (validate_alloc(bali, to_मुक्त)) अणु
		pr_debug("%s: AUN %llx is not allocated on lun_id=%016llx\n",
			 __func__, to_मुक्त, ba_lun->lun_id);
		वापस -1;
	पूर्ण

	pr_debug("%s: Received a request to free AU=%llx lun_id=%016llx "
		 "free_aun_cnt=%llx\n", __func__, to_मुक्त, ba_lun->lun_id,
		 bali->मुक्त_aun_cnt);

	अगर (bali->aun_clone_map[to_मुक्त] > 0) अणु
		pr_debug("%s: AUN %llx lun_id=%016llx cloned. Clone count=%x\n",
			 __func__, to_मुक्त, ba_lun->lun_id,
			 bali->aun_clone_map[to_मुक्त]);
		bali->aun_clone_map[to_मुक्त]--;
		वापस 0;
	पूर्ण

	idx = to_मुक्त / BITS_PER_LONG;
	bit_pos = to_मुक्त % BITS_PER_LONG;

	set_bit(bit_pos, (uदीर्घ *)&bali->lun_alloc_map[idx]);
	bali->मुक्त_aun_cnt++;

	अगर (idx < bali->मुक्त_low_idx)
		bali->मुक्त_low_idx = idx;
	अन्यथा अगर (idx > bali->मुक्त_high_idx)
		bali->मुक्त_high_idx = idx;

	pr_debug("%s: Successfully freed AU bit_pos=%x bit map index=%x "
		 "lun_id=%016llx free_aun_cnt=%llx\n", __func__, bit_pos, idx,
		 ba_lun->lun_id, bali->मुक्त_aun_cnt);

	वापस 0;
पूर्ण

/**
 * ba_clone() - Clone a chunk of the block allocation table
 * @ba_lun:	Block allocator from which to allocate a block.
 * @to_clone:	Block to clone.
 *
 * Return: 0 on success, -1 on failure
 */
अटल पूर्णांक ba_clone(काष्ठा ba_lun *ba_lun, u64 to_clone)
अणु
	काष्ठा ba_lun_info *bali = ba_lun->ba_lun_handle;

	अगर (validate_alloc(bali, to_clone)) अणु
		pr_debug("%s: AUN=%llx not allocated on lun_id=%016llx\n",
			 __func__, to_clone, ba_lun->lun_id);
		वापस -1;
	पूर्ण

	pr_debug("%s: Received a request to clone AUN %llx on lun_id=%016llx\n",
		 __func__, to_clone, ba_lun->lun_id);

	अगर (bali->aun_clone_map[to_clone] == MAX_AUN_CLONE_CNT) अणु
		pr_debug("%s: AUN %llx on lun_id=%016llx hit max clones already\n",
			 __func__, to_clone, ba_lun->lun_id);
		वापस -1;
	पूर्ण

	bali->aun_clone_map[to_clone]++;

	वापस 0;
पूर्ण

/**
 * ba_space() - वापसs the amount of मुक्त space left in the block allocator
 * @ba_lun:	Block allocator.
 *
 * Return: Amount of मुक्त space in block allocator
 */
अटल u64 ba_space(काष्ठा ba_lun *ba_lun)
अणु
	काष्ठा ba_lun_info *bali = ba_lun->ba_lun_handle;

	वापस bali->मुक्त_aun_cnt;
पूर्ण

/**
 * cxlflash_ba_terminate() - मुक्तs resources associated with the block allocator
 * @ba_lun:	Block allocator.
 *
 * Safe to call in a partially allocated state.
 */
व्योम cxlflash_ba_terminate(काष्ठा ba_lun *ba_lun)
अणु
	काष्ठा ba_lun_info *bali = ba_lun->ba_lun_handle;

	अगर (bali) अणु
		kमुक्त(bali->aun_clone_map);
		kमुक्त(bali->lun_alloc_map);
		kमुक्त(bali);
		ba_lun->ba_lun_handle = शून्य;
	पूर्ण
पूर्ण

/**
 * init_vlun() - initializes a LUN क्रम भव use
 * @lli:	LUN inक्रमmation काष्ठाure that owns the block allocator.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक init_vlun(काष्ठा llun_info *lli)
अणु
	पूर्णांक rc = 0;
	काष्ठा glun_info *gli = lli->parent;
	काष्ठा blka *blka = &gli->blka;

	स_रखो(blka, 0, माप(*blka));
	mutex_init(&blka->mutex);

	/* LUN IDs are unique per port, save the index instead */
	blka->ba_lun.lun_id = lli->lun_index;
	blka->ba_lun.lsize = gli->max_lba + 1;
	blka->ba_lun.lba_size = gli->blk_len;

	blka->ba_lun.au_size = MC_CHUNK_SIZE;
	blka->nchunk = blka->ba_lun.lsize / MC_CHUNK_SIZE;

	rc = ba_init(&blka->ba_lun);
	अगर (unlikely(rc))
		pr_debug("%s: cannot init block_alloc, rc=%d\n", __func__, rc);

	pr_debug("%s: returning rc=%d lli=%p\n", __func__, rc, lli);
	वापस rc;
पूर्ण

/**
 * ग_लिखो_same16() - sends a SCSI WRITE_SAME16 (0) command to specअगरied LUN
 * @sdev:	SCSI device associated with LUN.
 * @lba:	Logical block address to start ग_लिखो same.
 * @nblks:	Number of logical blocks to ग_लिखो same.
 *
 * The SCSI WRITE_SAME16 can take quite a जबतक to complete. Should an EEH occur
 * जबतक in scsi_execute(), the EEH handler will attempt to recover. As part of
 * the recovery, the handler drains all currently running ioctls, रुकोing until
 * they have completed beक्रमe proceeding with a reset. As this routine is used
 * on the ioctl path, this can create a condition where the EEH handler becomes
 * stuck, infinitely रुकोing क्रम this ioctl thपढ़ो. To aव्योम this behavior,
 * temporarily unmark this thपढ़ो as an ioctl thपढ़ो by releasing the ioctl पढ़ो
 * semaphore. This will allow the EEH handler to proceed with a recovery जबतक
 * this thपढ़ो is still running. Once the scsi_execute() वापसs, reacquire the
 * ioctl पढ़ो semaphore and check the adapter state in हाल it changed जबतक
 * inside of scsi_execute(). The state check will रुको अगर the adapter is still
 * being recovered or वापस a failure अगर the recovery failed. In the event that
 * the adapter reset failed, simply वापस the failure as the ioctl would be
 * unable to जारी.
 *
 * Note that the above माला_दो a requirement on this routine to only be called on
 * an ioctl thपढ़ो.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ग_लिखो_same16(काष्ठा scsi_device *sdev,
			u64 lba,
			u32 nblks)
अणु
	u8 *cmd_buf = शून्य;
	u8 *scsi_cmd = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक result = 0;
	u64 offset = lba;
	पूर्णांक left = nblks;
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	स्थिर u32 s = ilog2(sdev->sector_size) - 9;
	स्थिर u32 to = sdev->request_queue->rq_समयout;
	स्थिर u32 ws_limit = blk_queue_get_max_sectors(sdev->request_queue,
						       REQ_OP_WRITE_SAME) >> s;

	cmd_buf = kzalloc(CMD_बफ_मानE, GFP_KERNEL);
	scsi_cmd = kzalloc(MAX_COMMAND_SIZE, GFP_KERNEL);
	अगर (unlikely(!cmd_buf || !scsi_cmd)) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	जबतक (left > 0) अणु

		scsi_cmd[0] = WRITE_SAME_16;
		scsi_cmd[1] = cfg->ws_unmap ? 0x8 : 0;
		put_unaligned_be64(offset, &scsi_cmd[2]);
		put_unaligned_be32(ws_limit < left ? ws_limit : left,
				   &scsi_cmd[10]);

		/* Drop the ioctl पढ़ो semahpore across lengthy call */
		up_पढ़ो(&cfg->ioctl_rwsem);
		result = scsi_execute(sdev, scsi_cmd, DMA_TO_DEVICE, cmd_buf,
				      CMD_बफ_मानE, शून्य, शून्य, to,
				      CMD_RETRIES, 0, 0, शून्य);
		करोwn_पढ़ो(&cfg->ioctl_rwsem);
		rc = check_state(cfg);
		अगर (rc) अणु
			dev_err(dev, "%s: Failed state result=%08x\n",
				__func__, result);
			rc = -ENODEV;
			जाओ out;
		पूर्ण

		अगर (result) अणु
			dev_err_ratelimited(dev, "%s: command failed for "
					    "offset=%lld result=%08x\n",
					    __func__, offset, result);
			rc = -EIO;
			जाओ out;
		पूर्ण
		left -= ws_limit;
		offset += ws_limit;
	पूर्ण

out:
	kमुक्त(cmd_buf);
	kमुक्त(scsi_cmd);
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * grow_lxt() - expands the translation table associated with the specअगरied RHTE
 * @afu:	AFU associated with the host.
 * @sdev:	SCSI device associated with LUN.
 * @ctxid:	Context ID of context owning the RHTE.
 * @rhndl:	Resource handle associated with the RHTE.
 * @rhte:	Resource handle entry (RHTE).
 * @new_size:	Number of translation entries associated with RHTE.
 *
 * By design, this routine employs a 'best attempt' allocation and will
 * truncate the requested size करोwn अगर there is not sufficient space in
 * the block allocator to satisfy the request but there करोes exist some
 * amount of space. The user is made aware of this by वापसing the size
 * allocated.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक grow_lxt(काष्ठा afu *afu,
		    काष्ठा scsi_device *sdev,
		    ctx_hndl_t ctxid,
		    res_hndl_t rhndl,
		    काष्ठा sisl_rht_entry *rhte,
		    u64 *new_size)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा sisl_lxt_entry *lxt = शून्य, *lxt_old = शून्य;
	काष्ठा llun_info *lli = sdev->hostdata;
	काष्ठा glun_info *gli = lli->parent;
	काष्ठा blka *blka = &gli->blka;
	u32 av_size;
	u32 ngrps, ngrps_old;
	u64 aun;		/* chunk# allocated by block allocator */
	u64 delta = *new_size - rhte->lxt_cnt;
	u64 my_new_size;
	पूर्णांक i, rc = 0;

	/*
	 * Check what is available in the block allocator beक्रमe re-allocating
	 * LXT array. This is करोne up front under the mutex which must not be
	 * released until after allocation is complete.
	 */
	mutex_lock(&blka->mutex);
	av_size = ba_space(&blka->ba_lun);
	अगर (unlikely(av_size <= 0)) अणु
		dev_dbg(dev, "%s: ba_space error av_size=%d\n",
			__func__, av_size);
		mutex_unlock(&blka->mutex);
		rc = -ENOSPC;
		जाओ out;
	पूर्ण

	अगर (av_size < delta)
		delta = av_size;

	lxt_old = rhte->lxt_start;
	ngrps_old = LXT_NUM_GROUPS(rhte->lxt_cnt);
	ngrps = LXT_NUM_GROUPS(rhte->lxt_cnt + delta);

	अगर (ngrps != ngrps_old) अणु
		/* पुनः_स्मृतिate to fit new size */
		lxt = kzalloc((माप(*lxt) * LXT_GROUP_SIZE * ngrps),
			      GFP_KERNEL);
		अगर (unlikely(!lxt)) अणु
			mutex_unlock(&blka->mutex);
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		/* copy over all old entries */
		स_नकल(lxt, lxt_old, (माप(*lxt) * rhte->lxt_cnt));
	पूर्ण अन्यथा
		lxt = lxt_old;

	/* nothing can fail from now on */
	my_new_size = rhte->lxt_cnt + delta;

	/* add new entries to the end */
	क्रम (i = rhte->lxt_cnt; i < my_new_size; i++) अणु
		/*
		 * Due to the earlier check of available space, ba_alloc
		 * cannot fail here. If it did due to पूर्णांकernal error,
		 * leave a rlba_base of -1u which will likely be a
		 * invalid LUN (too large).
		 */
		aun = ba_alloc(&blka->ba_lun);
		अगर ((aun == -1ULL) || (aun >= blka->nchunk))
			dev_dbg(dev, "%s: ba_alloc error allocated chunk=%llu "
				"max=%llu\n", __func__, aun, blka->nchunk - 1);

		/* select both ports, use r/w perms from RHT */
		lxt[i].rlba_base = ((aun << MC_CHUNK_SHIFT) |
				    (lli->lun_index << LXT_LUNIDX_SHIFT) |
				    (RHT_PERM_RW << LXT_PERM_SHIFT |
				     lli->port_sel));
	पूर्ण

	mutex_unlock(&blka->mutex);

	/*
	 * The following sequence is prescribed in the SISlite spec
	 * क्रम syncing up with the AFU when adding LXT entries.
	 */
	dma_wmb(); /* Make LXT updates are visible */

	rhte->lxt_start = lxt;
	dma_wmb(); /* Make RHT entry's LXT table update visible */

	rhte->lxt_cnt = my_new_size;
	dma_wmb(); /* Make RHT entry's LXT table size update visible */

	rc = cxlflash_afu_sync(afu, ctxid, rhndl, AFU_LW_SYNC);
	अगर (unlikely(rc))
		rc = -EAGAIN;

	/* मुक्त old lxt अगर पुनः_स्मृतिated */
	अगर (lxt != lxt_old)
		kमुक्त(lxt_old);
	*new_size = my_new_size;
out:
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * shrink_lxt() - reduces translation table associated with the specअगरied RHTE
 * @afu:	AFU associated with the host.
 * @sdev:	SCSI device associated with LUN.
 * @rhndl:	Resource handle associated with the RHTE.
 * @rhte:	Resource handle entry (RHTE).
 * @ctxi:	Context owning resources.
 * @new_size:	Number of translation entries associated with RHTE.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक shrink_lxt(काष्ठा afu *afu,
		      काष्ठा scsi_device *sdev,
		      res_hndl_t rhndl,
		      काष्ठा sisl_rht_entry *rhte,
		      काष्ठा ctx_info *ctxi,
		      u64 *new_size)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा sisl_lxt_entry *lxt, *lxt_old;
	काष्ठा llun_info *lli = sdev->hostdata;
	काष्ठा glun_info *gli = lli->parent;
	काष्ठा blka *blka = &gli->blka;
	ctx_hndl_t ctxid = DECODE_CTXID(ctxi->ctxid);
	bool needs_ws = ctxi->rht_needs_ws[rhndl];
	bool needs_sync = !ctxi->err_recovery_active;
	u32 ngrps, ngrps_old;
	u64 aun;		/* chunk# allocated by block allocator */
	u64 delta = rhte->lxt_cnt - *new_size;
	u64 my_new_size;
	पूर्णांक i, rc = 0;

	lxt_old = rhte->lxt_start;
	ngrps_old = LXT_NUM_GROUPS(rhte->lxt_cnt);
	ngrps = LXT_NUM_GROUPS(rhte->lxt_cnt - delta);

	अगर (ngrps != ngrps_old) अणु
		/* Reallocate to fit new size unless new size is 0 */
		अगर (ngrps) अणु
			lxt = kzalloc((माप(*lxt) * LXT_GROUP_SIZE * ngrps),
				      GFP_KERNEL);
			अगर (unlikely(!lxt)) अणु
				rc = -ENOMEM;
				जाओ out;
			पूर्ण

			/* Copy over old entries that will reमुख्य */
			स_नकल(lxt, lxt_old,
			       (माप(*lxt) * (rhte->lxt_cnt - delta)));
		पूर्ण अन्यथा
			lxt = शून्य;
	पूर्ण अन्यथा
		lxt = lxt_old;

	/* Nothing can fail from now on */
	my_new_size = rhte->lxt_cnt - delta;

	/*
	 * The following sequence is prescribed in the SISlite spec
	 * क्रम syncing up with the AFU when removing LXT entries.
	 */
	rhte->lxt_cnt = my_new_size;
	dma_wmb(); /* Make RHT entry's LXT table size update visible */

	rhte->lxt_start = lxt;
	dma_wmb(); /* Make RHT entry's LXT table update visible */

	अगर (needs_sync) अणु
		rc = cxlflash_afu_sync(afu, ctxid, rhndl, AFU_HW_SYNC);
		अगर (unlikely(rc))
			rc = -EAGAIN;
	पूर्ण

	अगर (needs_ws) अणु
		/*
		 * Mark the context as unavailable, so that we can release
		 * the mutex safely.
		 */
		ctxi->unavail = true;
		mutex_unlock(&ctxi->mutex);
	पूर्ण

	/* Free LBAs allocated to मुक्तd chunks */
	mutex_lock(&blka->mutex);
	क्रम (i = delta - 1; i >= 0; i--) अणु
		aun = lxt_old[my_new_size + i].rlba_base >> MC_CHUNK_SHIFT;
		अगर (needs_ws)
			ग_लिखो_same16(sdev, aun, MC_CHUNK_SIZE);
		ba_मुक्त(&blka->ba_lun, aun);
	पूर्ण
	mutex_unlock(&blka->mutex);

	अगर (needs_ws) अणु
		/* Make the context visible again */
		mutex_lock(&ctxi->mutex);
		ctxi->unavail = false;
	पूर्ण

	/* Free old lxt अगर पुनः_स्मृतिated */
	अगर (lxt != lxt_old)
		kमुक्त(lxt_old);
	*new_size = my_new_size;
out:
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * _cxlflash_vlun_resize() - changes the size of a भव LUN
 * @sdev:	SCSI device associated with LUN owning भव LUN.
 * @ctxi:	Context owning resources.
 * @resize:	Resize ioctl data काष्ठाure.
 *
 * On successful वापस, the user is inक्रमmed of the new size (in blocks)
 * of the भव LUN in last LBA क्रमmat. When the size of the भव
 * LUN is zero, the last LBA is reflected as -1. See comment in the
 * prologue क्रम _cxlflash_disk_release() regarding AFU syncs and contexts
 * on the error recovery list.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक _cxlflash_vlun_resize(काष्ठा scsi_device *sdev,
			  काष्ठा ctx_info *ctxi,
			  काष्ठा dk_cxlflash_resize *resize)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा llun_info *lli = sdev->hostdata;
	काष्ठा glun_info *gli = lli->parent;
	काष्ठा afu *afu = cfg->afu;
	bool put_ctx = false;

	res_hndl_t rhndl = resize->rsrc_handle;
	u64 new_size;
	u64 nsectors;
	u64 ctxid = DECODE_CTXID(resize->context_id),
	    rctxid = resize->context_id;

	काष्ठा sisl_rht_entry *rhte;

	पूर्णांक rc = 0;

	/*
	 * The requested size (req_size) is always assumed to be in 4k blocks,
	 * so we have to convert it here from 4k to chunk size.
	 */
	nsectors = (resize->req_size * CXLFLASH_BLOCK_SIZE) / gli->blk_len;
	new_size = DIV_ROUND_UP(nsectors, MC_CHUNK_SIZE);

	dev_dbg(dev, "%s: ctxid=%llu rhndl=%llu req_size=%llu new_size=%llu\n",
		__func__, ctxid, resize->rsrc_handle, resize->req_size,
		new_size);

	अगर (unlikely(gli->mode != MODE_VIRTUAL)) अणु
		dev_dbg(dev, "%s: LUN mode does not support resize mode=%d\n",
			__func__, gli->mode);
		rc = -EINVAL;
		जाओ out;

	पूर्ण

	अगर (!ctxi) अणु
		ctxi = get_context(cfg, rctxid, lli, CTX_CTRL_ERR_FALLBACK);
		अगर (unlikely(!ctxi)) अणु
			dev_dbg(dev, "%s: Bad context ctxid=%llu\n",
				__func__, ctxid);
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		put_ctx = true;
	पूर्ण

	rhte = get_rhte(ctxi, rhndl, lli);
	अगर (unlikely(!rhte)) अणु
		dev_dbg(dev, "%s: Bad resource handle rhndl=%u\n",
			__func__, rhndl);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (new_size > rhte->lxt_cnt)
		rc = grow_lxt(afu, sdev, ctxid, rhndl, rhte, &new_size);
	अन्यथा अगर (new_size < rhte->lxt_cnt)
		rc = shrink_lxt(afu, sdev, rhndl, rhte, ctxi, &new_size);
	अन्यथा अणु
		/*
		 * Rare हाल where there is alपढ़ोy sufficient space, just
		 * need to perक्रमm a translation sync with the AFU. This
		 * scenario likely follows a previous sync failure during
		 * a resize operation. Accordingly, perक्रमm the heavyweight
		 * क्रमm of translation sync as it is unknown which type of
		 * resize failed previously.
		 */
		rc = cxlflash_afu_sync(afu, ctxid, rhndl, AFU_HW_SYNC);
		अगर (unlikely(rc)) अणु
			rc = -EAGAIN;
			जाओ out;
		पूर्ण
	पूर्ण

	resize->hdr.वापस_flags = 0;
	resize->last_lba = (new_size * MC_CHUNK_SIZE * gli->blk_len);
	resize->last_lba /= CXLFLASH_BLOCK_SIZE;
	resize->last_lba--;

out:
	अगर (put_ctx)
		put_context(ctxi);
	dev_dbg(dev, "%s: resized to %llu returning rc=%d\n",
		__func__, resize->last_lba, rc);
	वापस rc;
पूर्ण

पूर्णांक cxlflash_vlun_resize(काष्ठा scsi_device *sdev,
			 काष्ठा dk_cxlflash_resize *resize)
अणु
	वापस _cxlflash_vlun_resize(sdev, शून्य, resize);
पूर्ण

/**
 * cxlflash_restore_luntable() - Restore LUN table to prior state
 * @cfg:	Internal काष्ठाure associated with the host.
 */
व्योम cxlflash_restore_luntable(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा llun_info *lli, *temp;
	u32 lind;
	पूर्णांक k;
	काष्ठा device *dev = &cfg->dev->dev;
	__be64 __iomem *fc_port_luns;

	mutex_lock(&global.mutex);

	list_क्रम_each_entry_safe(lli, temp, &cfg->lluns, list) अणु
		अगर (!lli->in_table)
			जारी;

		lind = lli->lun_index;
		dev_dbg(dev, "%s: Virtual LUNs on slot %d:\n", __func__, lind);

		क्रम (k = 0; k < cfg->num_fc_ports; k++)
			अगर (lli->port_sel & (1 << k)) अणु
				fc_port_luns = get_fc_port_luns(cfg, k);
				ग_लिखोq_be(lli->lun_id[k], &fc_port_luns[lind]);
				dev_dbg(dev, "\t%d=%llx\n", k, lli->lun_id[k]);
			पूर्ण
	पूर्ण

	mutex_unlock(&global.mutex);
पूर्ण

/**
 * get_num_ports() - compute number of ports from port selection mask
 * @psm:	Port selection mask.
 *
 * Return: Population count of port selection mask
 */
अटल अंतरभूत u8 get_num_ports(u32 psm)
अणु
	अटल स्थिर u8 bits[16] = अणु 0, 1, 1, 2, 1, 2, 2, 3,
				     1, 2, 2, 3, 2, 3, 3, 4 पूर्ण;

	वापस bits[psm & 0xf];
पूर्ण

/**
 * init_luntable() - ग_लिखो an entry in the LUN table
 * @cfg:	Internal काष्ठाure associated with the host.
 * @lli:	Per adapter LUN inक्रमmation काष्ठाure.
 *
 * On successful वापस, a LUN table entry is created:
 *	- at the top क्रम LUNs visible on multiple ports.
 *	- at the bottom क्रम LUNs visible only on one port.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक init_luntable(काष्ठा cxlflash_cfg *cfg, काष्ठा llun_info *lli)
अणु
	u32 chan;
	u32 lind;
	u32 nports;
	पूर्णांक rc = 0;
	पूर्णांक k;
	काष्ठा device *dev = &cfg->dev->dev;
	__be64 __iomem *fc_port_luns;

	mutex_lock(&global.mutex);

	अगर (lli->in_table)
		जाओ out;

	nports = get_num_ports(lli->port_sel);
	अगर (nports == 0 || nports > cfg->num_fc_ports) अणु
		WARN(1, "Unsupported port configuration nports=%u", nports);
		rc = -EIO;
		जाओ out;
	पूर्ण

	अगर (nports > 1) अणु
		/*
		 * When LUN is visible from multiple ports, we will put
		 * it in the top half of the LUN table.
		 */
		क्रम (k = 0; k < cfg->num_fc_ports; k++) अणु
			अगर (!(lli->port_sel & (1 << k)))
				जारी;

			अगर (cfg->promote_lun_index == cfg->last_lun_index[k]) अणु
				rc = -ENOSPC;
				जाओ out;
			पूर्ण
		पूर्ण

		lind = lli->lun_index = cfg->promote_lun_index;
		dev_dbg(dev, "%s: Virtual LUNs on slot %d:\n", __func__, lind);

		क्रम (k = 0; k < cfg->num_fc_ports; k++) अणु
			अगर (!(lli->port_sel & (1 << k)))
				जारी;

			fc_port_luns = get_fc_port_luns(cfg, k);
			ग_लिखोq_be(lli->lun_id[k], &fc_port_luns[lind]);
			dev_dbg(dev, "\t%d=%llx\n", k, lli->lun_id[k]);
		पूर्ण

		cfg->promote_lun_index++;
	पूर्ण अन्यथा अणु
		/*
		 * When LUN is visible only from one port, we will put
		 * it in the bottom half of the LUN table.
		 */
		chan = PORTMASK2CHAN(lli->port_sel);
		अगर (cfg->promote_lun_index == cfg->last_lun_index[chan]) अणु
			rc = -ENOSPC;
			जाओ out;
		पूर्ण

		lind = lli->lun_index = cfg->last_lun_index[chan];
		fc_port_luns = get_fc_port_luns(cfg, chan);
		ग_लिखोq_be(lli->lun_id[chan], &fc_port_luns[lind]);
		cfg->last_lun_index[chan]--;
		dev_dbg(dev, "%s: Virtual LUNs on slot %d:\n\t%d=%llx\n",
			__func__, lind, chan, lli->lun_id[chan]);
	पूर्ण

	lli->in_table = true;
out:
	mutex_unlock(&global.mutex);
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * cxlflash_disk_भव_खोलो() - खोलो a भव disk of specअगरied size
 * @sdev:	SCSI device associated with LUN owning भव LUN.
 * @arg:	UVirtual ioctl data काष्ठाure.
 *
 * On successful वापस, the user is inक्रमmed of the resource handle
 * to be used to identअगरy the भव LUN and the size (in blocks) of
 * the भव LUN in last LBA क्रमmat. When the size of the भव LUN
 * is zero, the last LBA is reflected as -1.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक cxlflash_disk_भव_खोलो(काष्ठा scsi_device *sdev, व्योम *arg)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा llun_info *lli = sdev->hostdata;
	काष्ठा glun_info *gli = lli->parent;

	काष्ठा dk_cxlflash_uभव *virt = (काष्ठा dk_cxlflash_uभव *)arg;
	काष्ठा dk_cxlflash_resize resize;

	u64 ctxid = DECODE_CTXID(virt->context_id),
	    rctxid = virt->context_id;
	u64 lun_size = virt->lun_size;
	u64 last_lba = 0;
	u64 rsrc_handle = -1;

	पूर्णांक rc = 0;

	काष्ठा ctx_info *ctxi = शून्य;
	काष्ठा sisl_rht_entry *rhte = शून्य;

	dev_dbg(dev, "%s: ctxid=%llu ls=%llu\n", __func__, ctxid, lun_size);

	/* Setup the LUNs block allocator on first call */
	mutex_lock(&gli->mutex);
	अगर (gli->mode == MODE_NONE) अणु
		rc = init_vlun(lli);
		अगर (rc) अणु
			dev_err(dev, "%s: init_vlun failed rc=%d\n",
				__func__, rc);
			rc = -ENOMEM;
			जाओ err0;
		पूर्ण
	पूर्ण

	rc = cxlflash_lun_attach(gli, MODE_VIRTUAL, true);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: Failed attach to LUN (VIRTUAL)\n", __func__);
		जाओ err0;
	पूर्ण
	mutex_unlock(&gli->mutex);

	rc = init_luntable(cfg, lli);
	अगर (rc) अणु
		dev_err(dev, "%s: init_luntable failed rc=%d\n", __func__, rc);
		जाओ err1;
	पूर्ण

	ctxi = get_context(cfg, rctxid, lli, 0);
	अगर (unlikely(!ctxi)) अणु
		dev_err(dev, "%s: Bad context ctxid=%llu\n", __func__, ctxid);
		rc = -EINVAL;
		जाओ err1;
	पूर्ण

	rhte = rhte_checkout(ctxi, lli);
	अगर (unlikely(!rhte)) अणु
		dev_err(dev, "%s: too many opens ctxid=%llu\n",
			__func__, ctxid);
		rc = -EMखाता;	/* too many खोलोs  */
		जाओ err1;
	पूर्ण

	rsrc_handle = (rhte - ctxi->rht_start);

	/* Populate RHT क्रमmat 0 */
	rhte->nmask = MC_RHT_NMASK;
	rhte->fp = SISL_RHT_FP(0U, ctxi->rht_perms);

	/* Resize even अगर requested size is 0 */
	marshal_virt_to_resize(virt, &resize);
	resize.rsrc_handle = rsrc_handle;
	rc = _cxlflash_vlun_resize(sdev, ctxi, &resize);
	अगर (rc) अणु
		dev_err(dev, "%s: resize failed rc=%d\n", __func__, rc);
		जाओ err2;
	पूर्ण
	last_lba = resize.last_lba;

	अगर (virt->hdr.flags & DK_CXLFLASH_UVIRTUAL_NEED_WRITE_SAME)
		ctxi->rht_needs_ws[rsrc_handle] = true;

	virt->hdr.वापस_flags = 0;
	virt->last_lba = last_lba;
	virt->rsrc_handle = rsrc_handle;

	अगर (get_num_ports(lli->port_sel) > 1)
		virt->hdr.वापस_flags |= DK_CXLFLASH_ALL_PORTS_ACTIVE;
out:
	अगर (likely(ctxi))
		put_context(ctxi);
	dev_dbg(dev, "%s: returning handle=%llu rc=%d llba=%llu\n",
		__func__, rsrc_handle, rc, last_lba);
	वापस rc;

err2:
	rhte_checkin(ctxi, rhte);
err1:
	cxlflash_lun_detach(gli);
	जाओ out;
err0:
	/* Special common cleanup prior to successful LUN attach */
	cxlflash_ba_terminate(&gli->blka.ba_lun);
	mutex_unlock(&gli->mutex);
	जाओ out;
पूर्ण

/**
 * clone_lxt() - copies translation tables from source to destination RHTE
 * @afu:	AFU associated with the host.
 * @blka:	Block allocator associated with LUN.
 * @ctxid:	Context ID of context owning the RHTE.
 * @rhndl:	Resource handle associated with the RHTE.
 * @rhte:	Destination resource handle entry (RHTE).
 * @rhte_src:	Source resource handle entry (RHTE).
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक clone_lxt(काष्ठा afu *afu,
		     काष्ठा blka *blka,
		     ctx_hndl_t ctxid,
		     res_hndl_t rhndl,
		     काष्ठा sisl_rht_entry *rhte,
		     काष्ठा sisl_rht_entry *rhte_src)
अणु
	काष्ठा cxlflash_cfg *cfg = afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा sisl_lxt_entry *lxt = शून्य;
	bool locked = false;
	u32 ngrps;
	u64 aun;		/* chunk# allocated by block allocator */
	पूर्णांक j;
	पूर्णांक i = 0;
	पूर्णांक rc = 0;

	ngrps = LXT_NUM_GROUPS(rhte_src->lxt_cnt);

	अगर (ngrps) अणु
		/* allocate new LXTs क्रम clone */
		lxt = kzalloc((माप(*lxt) * LXT_GROUP_SIZE * ngrps),
				GFP_KERNEL);
		अगर (unlikely(!lxt)) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		/* copy over */
		स_नकल(lxt, rhte_src->lxt_start,
		       (माप(*lxt) * rhte_src->lxt_cnt));

		/* clone the LBAs in block allocator via ref_cnt, note that the
		 * block allocator mutex must be held until it is established
		 * that this routine will complete without the need क्रम a
		 * cleanup.
		 */
		mutex_lock(&blka->mutex);
		locked = true;
		क्रम (i = 0; i < rhte_src->lxt_cnt; i++) अणु
			aun = (lxt[i].rlba_base >> MC_CHUNK_SHIFT);
			अगर (ba_clone(&blka->ba_lun, aun) == -1ULL) अणु
				rc = -EIO;
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * The following sequence is prescribed in the SISlite spec
	 * क्रम syncing up with the AFU when adding LXT entries.
	 */
	dma_wmb(); /* Make LXT updates are visible */

	rhte->lxt_start = lxt;
	dma_wmb(); /* Make RHT entry's LXT table update visible */

	rhte->lxt_cnt = rhte_src->lxt_cnt;
	dma_wmb(); /* Make RHT entry's LXT table size update visible */

	rc = cxlflash_afu_sync(afu, ctxid, rhndl, AFU_LW_SYNC);
	अगर (unlikely(rc)) अणु
		rc = -EAGAIN;
		जाओ err2;
	पूर्ण

out:
	अगर (locked)
		mutex_unlock(&blka->mutex);
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
err2:
	/* Reset the RHTE */
	rhte->lxt_cnt = 0;
	dma_wmb();
	rhte->lxt_start = शून्य;
	dma_wmb();
err:
	/* मुक्त the clones alपढ़ोy made */
	क्रम (j = 0; j < i; j++) अणु
		aun = (lxt[j].rlba_base >> MC_CHUNK_SHIFT);
		ba_मुक्त(&blka->ba_lun, aun);
	पूर्ण
	kमुक्त(lxt);
	जाओ out;
पूर्ण

/**
 * cxlflash_disk_clone() - clone a context by making snapshot of another
 * @sdev:	SCSI device associated with LUN owning भव LUN.
 * @clone:	Clone ioctl data काष्ठाure.
 *
 * This routine effectively perक्रमms cxlflash_disk_खोलो operation क्रम each
 * in-use भव resource in the source context. Note that the destination
 * context must be in pristine state and cannot have any resource handles
 * खोलो at the समय of the clone.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक cxlflash_disk_clone(काष्ठा scsi_device *sdev,
			काष्ठा dk_cxlflash_clone *clone)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा llun_info *lli = sdev->hostdata;
	काष्ठा glun_info *gli = lli->parent;
	काष्ठा blka *blka = &gli->blka;
	काष्ठा afu *afu = cfg->afu;
	काष्ठा dk_cxlflash_release release = अणु अणु 0 पूर्ण, 0 पूर्ण;

	काष्ठा ctx_info *ctxi_src = शून्य,
			*ctxi_dst = शून्य;
	काष्ठा lun_access *lun_access_src, *lun_access_dst;
	u32 perms;
	u64 ctxid_src = DECODE_CTXID(clone->context_id_src),
	    ctxid_dst = DECODE_CTXID(clone->context_id_dst),
	    rctxid_src = clone->context_id_src,
	    rctxid_dst = clone->context_id_dst;
	पूर्णांक i, j;
	पूर्णांक rc = 0;
	bool found;
	LIST_HEAD(sidecar);

	dev_dbg(dev, "%s: ctxid_src=%llu ctxid_dst=%llu\n",
		__func__, ctxid_src, ctxid_dst);

	/* Do not clone yourself */
	अगर (unlikely(rctxid_src == rctxid_dst)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (unlikely(gli->mode != MODE_VIRTUAL)) अणु
		rc = -EINVAL;
		dev_dbg(dev, "%s: Only supported on virtual LUNs mode=%u\n",
			__func__, gli->mode);
		जाओ out;
	पूर्ण

	ctxi_src = get_context(cfg, rctxid_src, lli, CTX_CTRL_CLONE);
	ctxi_dst = get_context(cfg, rctxid_dst, lli, 0);
	अगर (unlikely(!ctxi_src || !ctxi_dst)) अणु
		dev_dbg(dev, "%s: Bad context ctxid_src=%llu ctxid_dst=%llu\n",
			__func__, ctxid_src, ctxid_dst);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* Verअगरy there is no खोलो resource handle in the destination context */
	क्रम (i = 0; i < MAX_RHT_PER_CONTEXT; i++)
		अगर (ctxi_dst->rht_start[i].nmask != 0) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

	/* Clone LUN access list */
	list_क्रम_each_entry(lun_access_src, &ctxi_src->luns, list) अणु
		found = false;
		list_क्रम_each_entry(lun_access_dst, &ctxi_dst->luns, list)
			अगर (lun_access_dst->sdev == lun_access_src->sdev) अणु
				found = true;
				अवरोध;
			पूर्ण

		अगर (!found) अणु
			lun_access_dst = kzalloc(माप(*lun_access_dst),
						 GFP_KERNEL);
			अगर (unlikely(!lun_access_dst)) अणु
				dev_err(dev, "%s: lun_access allocation fail\n",
					__func__);
				rc = -ENOMEM;
				जाओ out;
			पूर्ण

			*lun_access_dst = *lun_access_src;
			list_add(&lun_access_dst->list, &sidecar);
		पूर्ण
	पूर्ण

	अगर (unlikely(!ctxi_src->rht_out)) अणु
		dev_dbg(dev, "%s: Nothing to clone\n", __func__);
		जाओ out_success;
	पूर्ण

	/* User specअगरied permission on attach */
	perms = ctxi_dst->rht_perms;

	/*
	 * Copy over checked-out RHT (and their associated LXT) entries by
	 * hand, stopping after we've copied all outstanding entries and
	 * cleaning up अगर the clone fails.
	 *
	 * Note: This loop is equivalent to perक्रमming cxlflash_disk_खोलो and
	 * cxlflash_vlun_resize. As such, LUN accounting needs to be taken पूर्णांकo
	 * account by attaching after each successful RHT entry clone. In the
	 * event that a clone failure is experienced, the LUN detach is handled
	 * via the cleanup perक्रमmed by _cxlflash_disk_release.
	 */
	क्रम (i = 0; i < MAX_RHT_PER_CONTEXT; i++) अणु
		अगर (ctxi_src->rht_out == ctxi_dst->rht_out)
			अवरोध;
		अगर (ctxi_src->rht_start[i].nmask == 0)
			जारी;

		/* Consume a destination RHT entry */
		ctxi_dst->rht_out++;
		ctxi_dst->rht_start[i].nmask = ctxi_src->rht_start[i].nmask;
		ctxi_dst->rht_start[i].fp =
		    SISL_RHT_FP_CLONE(ctxi_src->rht_start[i].fp, perms);
		ctxi_dst->rht_lun[i] = ctxi_src->rht_lun[i];

		rc = clone_lxt(afu, blka, ctxid_dst, i,
			       &ctxi_dst->rht_start[i],
			       &ctxi_src->rht_start[i]);
		अगर (rc) अणु
			marshal_clone_to_rele(clone, &release);
			क्रम (j = 0; j < i; j++) अणु
				release.rsrc_handle = j;
				_cxlflash_disk_release(sdev, ctxi_dst,
						       &release);
			पूर्ण

			/* Put back the one we failed on */
			rhte_checkin(ctxi_dst, &ctxi_dst->rht_start[i]);
			जाओ err;
		पूर्ण

		cxlflash_lun_attach(gli, gli->mode, false);
	पूर्ण

out_success:
	list_splice(&sidecar, &ctxi_dst->luns);

	/* fall through */
out:
	अगर (ctxi_src)
		put_context(ctxi_src);
	अगर (ctxi_dst)
		put_context(ctxi_dst);
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;

err:
	list_क्रम_each_entry_safe(lun_access_src, lun_access_dst, &sidecar, list)
		kमुक्त(lun_access_src);
	जाओ out;
पूर्ण
