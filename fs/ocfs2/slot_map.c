<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * slot_map.c
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "dlmglue.h"
#समावेश "extent_map.h"
#समावेश "heartbeat.h"
#समावेश "inode.h"
#समावेश "slot_map.h"
#समावेश "super.h"
#समावेश "sysfile.h"
#समावेश "ocfs2_trace.h"

#समावेश "buffer_head_io.h"


काष्ठा ocfs2_slot अणु
	पूर्णांक sl_valid;
	अचिन्हित पूर्णांक sl_node_num;
पूर्ण;

काष्ठा ocfs2_slot_info अणु
	पूर्णांक si_extended;
	पूर्णांक si_slots_per_block;
	काष्ठा inode *si_inode;
	अचिन्हित पूर्णांक si_blocks;
	काष्ठा buffer_head **si_bh;
	अचिन्हित पूर्णांक si_num_slots;
	काष्ठा ocfs2_slot si_slots[];
पूर्ण;


अटल पूर्णांक __ocfs2_node_num_to_slot(काष्ठा ocfs2_slot_info *si,
				    अचिन्हित पूर्णांक node_num);

अटल व्योम ocfs2_invalidate_slot(काष्ठा ocfs2_slot_info *si,
				  पूर्णांक slot_num)
अणु
	BUG_ON((slot_num < 0) || (slot_num >= si->si_num_slots));
	si->si_slots[slot_num].sl_valid = 0;
पूर्ण

अटल व्योम ocfs2_set_slot(काष्ठा ocfs2_slot_info *si,
			   पूर्णांक slot_num, अचिन्हित पूर्णांक node_num)
अणु
	BUG_ON((slot_num < 0) || (slot_num >= si->si_num_slots));

	si->si_slots[slot_num].sl_valid = 1;
	si->si_slots[slot_num].sl_node_num = node_num;
पूर्ण

/* This version is क्रम the extended slot map */
अटल व्योम ocfs2_update_slot_info_extended(काष्ठा ocfs2_slot_info *si)
अणु
	पूर्णांक b, i, slotno;
	काष्ठा ocfs2_slot_map_extended *se;

	slotno = 0;
	क्रम (b = 0; b < si->si_blocks; b++) अणु
		se = (काष्ठा ocfs2_slot_map_extended *)si->si_bh[b]->b_data;
		क्रम (i = 0;
		     (i < si->si_slots_per_block) &&
		     (slotno < si->si_num_slots);
		     i++, slotno++) अणु
			अगर (se->se_slots[i].es_valid)
				ocfs2_set_slot(si, slotno,
					       le32_to_cpu(se->se_slots[i].es_node_num));
			अन्यथा
				ocfs2_invalidate_slot(si, slotno);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Post the slot inक्रमmation on disk पूर्णांकo our slot_info काष्ठा.
 * Must be रक्षित by osb_lock.
 */
अटल व्योम ocfs2_update_slot_info_old(काष्ठा ocfs2_slot_info *si)
अणु
	पूर्णांक i;
	काष्ठा ocfs2_slot_map *sm;

	sm = (काष्ठा ocfs2_slot_map *)si->si_bh[0]->b_data;

	क्रम (i = 0; i < si->si_num_slots; i++) अणु
		अगर (le16_to_cpu(sm->sm_slots[i]) == (u16)OCFS2_INVALID_SLOT)
			ocfs2_invalidate_slot(si, i);
		अन्यथा
			ocfs2_set_slot(si, i, le16_to_cpu(sm->sm_slots[i]));
	पूर्ण
पूर्ण

अटल व्योम ocfs2_update_slot_info(काष्ठा ocfs2_slot_info *si)
अणु
	/*
	 * The slot data will have been refreshed when ocfs2_super_lock
	 * was taken.
	 */
	अगर (si->si_extended)
		ocfs2_update_slot_info_extended(si);
	अन्यथा
		ocfs2_update_slot_info_old(si);
पूर्ण

पूर्णांक ocfs2_refresh_slot_info(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_slot_info *si = osb->slot_info;

	अगर (si == शून्य)
		वापस 0;

	BUG_ON(si->si_blocks == 0);
	BUG_ON(si->si_bh == शून्य);

	trace_ocfs2_refresh_slot_info(si->si_blocks);

	/*
	 * We pass -1 as blocknr because we expect all of si->si_bh to
	 * be !शून्य.  Thus, ocfs2_पढ़ो_blocks() will ignore blocknr.  If
	 * this is not true, the पढ़ो of -1 (UINT64_MAX) will fail.
	 */
	ret = ocfs2_पढ़ो_blocks(INODE_CACHE(si->si_inode), -1, si->si_blocks,
				si->si_bh, OCFS2_BH_IGNORE_CACHE, शून्य);
	अगर (ret == 0) अणु
		spin_lock(&osb->osb_lock);
		ocfs2_update_slot_info(si);
		spin_unlock(&osb->osb_lock);
	पूर्ण

	वापस ret;
पूर्ण

/* post the our slot info stuff पूर्णांकo it's destination bh and ग_लिखो it
 * out. */
अटल व्योम ocfs2_update_disk_slot_extended(काष्ठा ocfs2_slot_info *si,
					    पूर्णांक slot_num,
					    काष्ठा buffer_head **bh)
अणु
	पूर्णांक blkind = slot_num / si->si_slots_per_block;
	पूर्णांक slotno = slot_num % si->si_slots_per_block;
	काष्ठा ocfs2_slot_map_extended *se;

	BUG_ON(blkind >= si->si_blocks);

	se = (काष्ठा ocfs2_slot_map_extended *)si->si_bh[blkind]->b_data;
	se->se_slots[slotno].es_valid = si->si_slots[slot_num].sl_valid;
	अगर (si->si_slots[slot_num].sl_valid)
		se->se_slots[slotno].es_node_num =
			cpu_to_le32(si->si_slots[slot_num].sl_node_num);
	*bh = si->si_bh[blkind];
पूर्ण

अटल व्योम ocfs2_update_disk_slot_old(काष्ठा ocfs2_slot_info *si,
				       पूर्णांक slot_num,
				       काष्ठा buffer_head **bh)
अणु
	पूर्णांक i;
	काष्ठा ocfs2_slot_map *sm;

	sm = (काष्ठा ocfs2_slot_map *)si->si_bh[0]->b_data;
	क्रम (i = 0; i < si->si_num_slots; i++) अणु
		अगर (si->si_slots[i].sl_valid)
			sm->sm_slots[i] =
				cpu_to_le16(si->si_slots[i].sl_node_num);
		अन्यथा
			sm->sm_slots[i] = cpu_to_le16(OCFS2_INVALID_SLOT);
	पूर्ण
	*bh = si->si_bh[0];
पूर्ण

अटल पूर्णांक ocfs2_update_disk_slot(काष्ठा ocfs2_super *osb,
				  काष्ठा ocfs2_slot_info *si,
				  पूर्णांक slot_num)
अणु
	पूर्णांक status;
	काष्ठा buffer_head *bh;

	spin_lock(&osb->osb_lock);
	अगर (si->si_extended)
		ocfs2_update_disk_slot_extended(si, slot_num, &bh);
	अन्यथा
		ocfs2_update_disk_slot_old(si, slot_num, &bh);
	spin_unlock(&osb->osb_lock);

	status = ocfs2_ग_लिखो_block(osb, bh, INODE_CACHE(si->si_inode));
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

/*
 * Calculate how many bytes are needed by the slot map.  Returns
 * an error अगर the slot map file is too small.
 */
अटल पूर्णांक ocfs2_slot_map_physical_size(काष्ठा ocfs2_super *osb,
					काष्ठा inode *inode,
					अचिन्हित दीर्घ दीर्घ *bytes)
अणु
	अचिन्हित दीर्घ दीर्घ bytes_needed;

	अगर (ocfs2_uses_extended_slot_map(osb)) अणु
		bytes_needed = osb->max_slots *
			माप(काष्ठा ocfs2_extended_slot);
	पूर्ण अन्यथा अणु
		bytes_needed = osb->max_slots * माप(__le16);
	पूर्ण
	अगर (bytes_needed > i_size_पढ़ो(inode)) अणु
		mlog(ML_ERROR,
		     "Slot map file is too small!  (size %llu, needed %llu)\n",
		     i_size_पढ़ो(inode), bytes_needed);
		वापस -ENOSPC;
	पूर्ण

	*bytes = bytes_needed;
	वापस 0;
पूर्ण

/* try to find global node in the slot info. Returns -ENOENT
 * अगर nothing is found. */
अटल पूर्णांक __ocfs2_node_num_to_slot(काष्ठा ocfs2_slot_info *si,
				    अचिन्हित पूर्णांक node_num)
अणु
	पूर्णांक i, ret = -ENOENT;

	क्रम(i = 0; i < si->si_num_slots; i++) अणु
		अगर (si->si_slots[i].sl_valid &&
		    (node_num == si->si_slots[i].sl_node_num)) अणु
			ret = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __ocfs2_find_empty_slot(काष्ठा ocfs2_slot_info *si,
				   पूर्णांक preferred)
अणु
	पूर्णांक i, ret = -ENOSPC;

	अगर ((preferred >= 0) && (preferred < si->si_num_slots)) अणु
		अगर (!si->si_slots[preferred].sl_valid ||
		    !si->si_slots[preferred].sl_node_num) अणु
			ret = preferred;
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम(i = 0; i < si->si_num_slots; i++) अणु
		अगर (!si->si_slots[i].sl_valid ||
		    !si->si_slots[i].sl_node_num) अणु
			ret = i;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

पूर्णांक ocfs2_node_num_to_slot(काष्ठा ocfs2_super *osb, अचिन्हित पूर्णांक node_num)
अणु
	पूर्णांक slot;
	काष्ठा ocfs2_slot_info *si = osb->slot_info;

	spin_lock(&osb->osb_lock);
	slot = __ocfs2_node_num_to_slot(si, node_num);
	spin_unlock(&osb->osb_lock);

	वापस slot;
पूर्ण

पूर्णांक ocfs2_slot_to_node_num_locked(काष्ठा ocfs2_super *osb, पूर्णांक slot_num,
				  अचिन्हित पूर्णांक *node_num)
अणु
	काष्ठा ocfs2_slot_info *si = osb->slot_info;

	निश्चित_spin_locked(&osb->osb_lock);

	BUG_ON(slot_num < 0);
	BUG_ON(slot_num >= osb->max_slots);

	अगर (!si->si_slots[slot_num].sl_valid)
		वापस -ENOENT;

	*node_num = si->si_slots[slot_num].sl_node_num;
	वापस 0;
पूर्ण

अटल व्योम __ocfs2_मुक्त_slot_info(काष्ठा ocfs2_slot_info *si)
अणु
	अचिन्हित पूर्णांक i;

	अगर (si == शून्य)
		वापस;

	iput(si->si_inode);
	अगर (si->si_bh) अणु
		क्रम (i = 0; i < si->si_blocks; i++) अणु
			अगर (si->si_bh[i]) अणु
				brअन्यथा(si->si_bh[i]);
				si->si_bh[i] = शून्य;
			पूर्ण
		पूर्ण
		kमुक्त(si->si_bh);
	पूर्ण

	kमुक्त(si);
पूर्ण

पूर्णांक ocfs2_clear_slot(काष्ठा ocfs2_super *osb, पूर्णांक slot_num)
अणु
	काष्ठा ocfs2_slot_info *si = osb->slot_info;

	अगर (si == शून्य)
		वापस 0;

	spin_lock(&osb->osb_lock);
	ocfs2_invalidate_slot(si, slot_num);
	spin_unlock(&osb->osb_lock);

	वापस ocfs2_update_disk_slot(osb, osb->slot_info, slot_num);
पूर्ण

अटल पूर्णांक ocfs2_map_slot_buffers(काष्ठा ocfs2_super *osb,
				  काष्ठा ocfs2_slot_info *si)
अणु
	पूर्णांक status = 0;
	u64 blkno;
	अचिन्हित दीर्घ दीर्घ blocks, bytes = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा buffer_head *bh;

	status = ocfs2_slot_map_physical_size(osb, si->si_inode, &bytes);
	अगर (status)
		जाओ bail;

	blocks = ocfs2_blocks_क्रम_bytes(si->si_inode->i_sb, bytes);
	BUG_ON(blocks > अच_पूर्णांक_उच्च);
	si->si_blocks = blocks;
	अगर (!si->si_blocks)
		जाओ bail;

	अगर (si->si_extended)
		si->si_slots_per_block =
			(osb->sb->s_blocksize /
			 माप(काष्ठा ocfs2_extended_slot));
	अन्यथा
		si->si_slots_per_block = osb->sb->s_blocksize / माप(__le16);

	/* The size checks above should ensure this */
	BUG_ON((osb->max_slots / si->si_slots_per_block) > blocks);

	trace_ocfs2_map_slot_buffers(bytes, si->si_blocks);

	si->si_bh = kसुस्मृति(si->si_blocks, माप(काष्ठा buffer_head *),
			    GFP_KERNEL);
	अगर (!si->si_bh) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	क्रम (i = 0; i < si->si_blocks; i++) अणु
		status = ocfs2_extent_map_get_blocks(si->si_inode, i,
						     &blkno, शून्य, शून्य);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		trace_ocfs2_map_slot_buffers_block((अचिन्हित दीर्घ दीर्घ)blkno, i);

		bh = शून्य;  /* Acquire a fresh bh */
		status = ocfs2_पढ़ो_blocks(INODE_CACHE(si->si_inode), blkno,
					   1, &bh, OCFS2_BH_IGNORE_CACHE, शून्य);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		si->si_bh[i] = bh;
	पूर्ण

bail:
	वापस status;
पूर्ण

पूर्णांक ocfs2_init_slot_info(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status;
	काष्ठा inode *inode = शून्य;
	काष्ठा ocfs2_slot_info *si;

	si = kzalloc(काष्ठा_size(si, si_slots, osb->max_slots), GFP_KERNEL);
	अगर (!si) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	si->si_extended = ocfs2_uses_extended_slot_map(osb);
	si->si_num_slots = osb->max_slots;

	inode = ocfs2_get_प्रणाली_file_inode(osb, SLOT_MAP_SYSTEM_INODE,
					    OCFS2_INVALID_SLOT);
	अगर (!inode) अणु
		status = -EINVAL;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	si->si_inode = inode;
	status = ocfs2_map_slot_buffers(osb, si);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	osb->slot_info = (काष्ठा ocfs2_slot_info *)si;
bail:
	अगर (status < 0)
		__ocfs2_मुक्त_slot_info(si);

	वापस status;
पूर्ण

व्योम ocfs2_मुक्त_slot_info(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_slot_info *si = osb->slot_info;

	osb->slot_info = शून्य;
	__ocfs2_मुक्त_slot_info(si);
पूर्ण

पूर्णांक ocfs2_find_slot(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status;
	पूर्णांक slot;
	काष्ठा ocfs2_slot_info *si;

	si = osb->slot_info;

	spin_lock(&osb->osb_lock);
	ocfs2_update_slot_info(si);

	अगर (ocfs2_mount_local(osb))
		/* use slot 0 directly in local mode */
		slot = 0;
	अन्यथा अणु
		/* search क्रम ourselves first and take the slot अगर it alपढ़ोy
		 * exists. Perhaps we need to mark this in a variable क्रम our
		 * own journal recovery? Possibly not, though we certainly
		 * need to warn to the user */
		slot = __ocfs2_node_num_to_slot(si, osb->node_num);
		अगर (slot < 0) अणु
			/* अगर no slot yet, then just take 1st available
			 * one. */
			slot = __ocfs2_find_empty_slot(si, osb->preferred_slot);
			अगर (slot < 0) अणु
				spin_unlock(&osb->osb_lock);
				mlog(ML_ERROR, "no free slots available!\n");
				status = -EINVAL;
				जाओ bail;
			पूर्ण
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_INFO "ocfs2: Slot %d on device (%s) was "
			       "already allocated to this node!\n",
			       slot, osb->dev_str);
	पूर्ण

	ocfs2_set_slot(si, slot, osb->node_num);
	osb->slot_num = slot;
	spin_unlock(&osb->osb_lock);

	trace_ocfs2_find_slot(osb->slot_num);

	status = ocfs2_update_disk_slot(osb, si, osb->slot_num);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		/*
		 * अगर ग_लिखो block failed, invalidate slot to aव्योम overग_लिखो
		 * slot during dismount in हाल another node rightly has mounted
		 */
		spin_lock(&osb->osb_lock);
		ocfs2_invalidate_slot(si, osb->slot_num);
		osb->slot_num = OCFS2_INVALID_SLOT;
		spin_unlock(&osb->osb_lock);
	पूर्ण

bail:
	वापस status;
पूर्ण

व्योम ocfs2_put_slot(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status, slot_num;
	काष्ठा ocfs2_slot_info *si = osb->slot_info;

	अगर (!si)
		वापस;

	spin_lock(&osb->osb_lock);
	ocfs2_update_slot_info(si);

	slot_num = osb->slot_num;
	ocfs2_invalidate_slot(si, osb->slot_num);
	osb->slot_num = OCFS2_INVALID_SLOT;
	spin_unlock(&osb->osb_lock);

	status = ocfs2_update_disk_slot(osb, si, slot_num);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	ocfs2_मुक्त_slot_info(osb);
पूर्ण
