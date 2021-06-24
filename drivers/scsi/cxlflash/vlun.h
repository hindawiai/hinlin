<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CXL Flash Device Driver
 *
 * Written by: Manoj N. Kumar <manoj@linux.vnet.ibm.com>, IBM Corporation
 *             Matthew R. Ochs <mrochs@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2015 IBM Corporation
 */

#अगर_अघोषित _CXLFLASH_VLUN_H
#घोषणा _CXLFLASH_VLUN_H

/* RHT - Resource Handle Table */
#घोषणा MC_RHT_NMASK      16	/* in bits */
#घोषणा MC_CHUNK_SHIFT    MC_RHT_NMASK	/* shअगरt to go from LBA to chunk# */

#घोषणा HIBIT             (BITS_PER_LONG - 1)

#घोषणा MAX_AUN_CLONE_CNT 0xFF

/*
 * LXT - LBA Translation Table
 *
 * +-------+-------+-------+-------+-------+-------+-------+---+---+
 * | RLBA_BASE                                     |LUN_IDX| P |SEL|
 * +-------+-------+-------+-------+-------+-------+-------+---+---+
 *
 * The LXT Entry contains the physical LBA where the chunk starts (RLBA_BASE).
 * AFU ORes the low order bits from the भव LBA (offset पूर्णांकo the chunk)
 * with RLBA_BASE. The result is the physical LBA to be sent to storage.
 * The LXT Entry also contains an index to a LUN TBL and a biपंचांगask of which
 * outgoing (FC) * ports can be selected. The port select bit-mask is ANDed
 * with a global port select bit-mask मुख्यtained by the driver.
 * In addition, it has permission bits that are ANDed with the
 * RHT permissions to arrive at the final permissions क्रम the chunk.
 *
 * LXT tables are allocated dynamically in groups. This is करोne to aव्योम
 * a दो_स्मृति/मुक्त overhead each समय the LXT has to grow or shrink.
 *
 * Based on the current lxt_cnt (used), it is always possible to know
 * how many are allocated (used+मुक्त). The number of allocated entries is
 * not stored anywhere.
 *
 * The LXT table is re-allocated whenever it needs to cross पूर्णांकo another group.
 */
#घोषणा LXT_GROUP_SIZE          8
#घोषणा LXT_NUM_GROUPS(lxt_cnt) (((lxt_cnt) + 7)/8)	/* alloc'ed groups */
#घोषणा LXT_LUNIDX_SHIFT  8	/* LXT entry, shअगरt क्रम LUN index */
#घोषणा LXT_PERM_SHIFT    4	/* LXT entry, shअगरt क्रम permission bits */

काष्ठा ba_lun_info अणु
	u64 *lun_alloc_map;
	u32 lun_bmap_size;
	u32 total_aus;
	u64 मुक्त_aun_cnt;

	/* indices to be used क्रम elevator lookup of मुक्त map */
	u32 मुक्त_low_idx;
	u32 मुक्त_curr_idx;
	u32 मुक्त_high_idx;

	u8 *aun_clone_map;
पूर्ण;

काष्ठा ba_lun अणु
	u64 lun_id;
	u64 wwpn;
	माप_प्रकार lsize;		/* LUN size in number of LBAs             */
	माप_प्रकार lba_size;	/* LBA size in number of bytes            */
	माप_प्रकार au_size;		/* Allocation Unit size in number of LBAs */
	काष्ठा ba_lun_info *ba_lun_handle;
पूर्ण;

/* Block Allocator */
काष्ठा blka अणु
	काष्ठा ba_lun ba_lun;
	u64 nchunk;		/* number of chunks */
	काष्ठा mutex mutex;
पूर्ण;

#पूर्ण_अगर /* अगरndef _CXLFLASH_SUPERPIPE_H */
