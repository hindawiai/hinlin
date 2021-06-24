<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright(c) 2016 Intel Corporation.
 */

#अगर_अघोषित DEF_RDMAVT_INCMR_H
#घोषणा DEF_RDMAVT_INCMR_H

/*
 * For Memory Regions. This stuff should probably be moved पूर्णांकo rdmavt/mr.h once
 * drivers no दीर्घer need access to the MR directly.
 */
#समावेश <linux/percpu-refcount.h>

/*
 * A segment is a linear region of low physical memory.
 * Used by the verbs layer.
 */
काष्ठा rvt_seg अणु
	व्योम *vaddr;
	माप_प्रकार length;
पूर्ण;

/* The number of rvt_segs that fit in a page. */
#घोषणा RVT_SEGSZ     (PAGE_SIZE / माप(काष्ठा rvt_seg))

काष्ठा rvt_segarray अणु
	काष्ठा rvt_seg segs[RVT_SEGSZ];
पूर्ण;

काष्ठा rvt_mregion अणु
	काष्ठा ib_pd *pd;       /* shares refcnt of ibmr.pd */
	u64 user_base;          /* User's address क्रम this region */
	u64 iova;               /* IB start address of this region */
	माप_प्रकार length;
	u32 lkey;
	u32 offset;             /* offset (bytes) to start of region */
	पूर्णांक access_flags;
	u32 max_segs;           /* number of rvt_segs in all the arrays */
	u32 mapsz;              /* size of the map array */
	atomic_t lkey_invalid;	/* true अगर current lkey is invalid */
	u8  page_shअगरt;         /* 0 - non unक्रमm/non घातerof2 sizes */
	u8  lkey_published;     /* in global table */
	काष्ठा percpu_ref refcount;
	काष्ठा completion comp; /* complete when refcount goes to zero */
	काष्ठा rvt_segarray *map[];    /* the segments */
पूर्ण;

#घोषणा RVT_MAX_LKEY_TABLE_BITS 23

काष्ठा rvt_lkey_table अणु
	/* पढ़ो mostly fields */
	u32 max;                /* size of the table */
	u32 shअगरt;              /* lkey/rkey shअगरt */
	काष्ठा rvt_mregion __rcu **table;
	/* ग_लिखोable fields */
	/* protect changes in this काष्ठा */
	spinlock_t lock ____cacheline_aligned_in_smp;
	u32 next;               /* next unused index (speeds search) */
	u32 gen;                /* generation count */
पूर्ण;

/*
 * These keep track of the copy progress within a memory region.
 * Used by the verbs layer.
 */
काष्ठा rvt_sge अणु
	काष्ठा rvt_mregion *mr;
	व्योम *vaddr;            /* kernel भव address of segment */
	u32 sge_length;         /* length of the SGE */
	u32 length;             /* reमुख्यing length of the segment */
	u16 m;                  /* current index: mr->map[m] */
	u16 n;                  /* current index: mr->map[m]->segs[n] */
पूर्ण;

काष्ठा rvt_sge_state अणु
	काष्ठा rvt_sge *sg_list;      /* next SGE to be used अगर any */
	काष्ठा rvt_sge sge;   /* progress state क्रम the current SGE */
	u32 total_len;
	u8 num_sge;
पूर्ण;

अटल अंतरभूत व्योम rvt_put_mr(काष्ठा rvt_mregion *mr)
अणु
	percpu_ref_put(&mr->refcount);
पूर्ण

अटल अंतरभूत व्योम rvt_get_mr(काष्ठा rvt_mregion *mr)
अणु
	percpu_ref_get(&mr->refcount);
पूर्ण

अटल अंतरभूत व्योम rvt_put_ss(काष्ठा rvt_sge_state *ss)
अणु
	जबतक (ss->num_sge) अणु
		rvt_put_mr(ss->sge.mr);
		अगर (--ss->num_sge)
			ss->sge = *ss->sg_list++;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 rvt_get_sge_length(काष्ठा rvt_sge *sge, u32 length)
अणु
	u32 len = sge->length;

	अगर (len > length)
		len = length;
	अगर (len > sge->sge_length)
		len = sge->sge_length;

	वापस len;
पूर्ण

अटल अंतरभूत व्योम rvt_update_sge(काष्ठा rvt_sge_state *ss, u32 length,
				  bool release)
अणु
	काष्ठा rvt_sge *sge = &ss->sge;

	sge->vaddr += length;
	sge->length -= length;
	sge->sge_length -= length;
	अगर (sge->sge_length == 0) अणु
		अगर (release)
			rvt_put_mr(sge->mr);
		अगर (--ss->num_sge)
			*sge = *ss->sg_list++;
	पूर्ण अन्यथा अगर (sge->length == 0 && sge->mr->lkey) अणु
		अगर (++sge->n >= RVT_SEGSZ) अणु
			अगर (++sge->m >= sge->mr->mapsz)
				वापस;
			sge->n = 0;
		पूर्ण
		sge->vaddr = sge->mr->map[sge->m]->segs[sge->n].vaddr;
		sge->length = sge->mr->map[sge->m]->segs[sge->n].length;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rvt_skip_sge(काष्ठा rvt_sge_state *ss, u32 length,
				bool release)
अणु
	काष्ठा rvt_sge *sge = &ss->sge;

	जबतक (length) अणु
		u32 len = rvt_get_sge_length(sge, length);

		WARN_ON_ONCE(len == 0);
		rvt_update_sge(ss, len, release);
		length -= len;
	पूर्ण
पूर्ण

bool rvt_ss_has_lkey(काष्ठा rvt_sge_state *ss, u32 lkey);
bool rvt_mr_has_lkey(काष्ठा rvt_mregion *mr, u32 lkey);

#पूर्ण_अगर          /* DEF_RDMAVT_INCMRH */
