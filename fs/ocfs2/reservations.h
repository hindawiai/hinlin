<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * reservations.h
 *
 * Allocation reservations function prototypes and काष्ठाures.
 *
 * Copyright (C) 2010 Novell.  All rights reserved.
 */

#अगर_अघोषित	OCFS2_RESERVATIONS_H
#घोषणा	OCFS2_RESERVATIONS_H

#समावेश <linux/rbtree.h>

#घोषणा OCFS2_DEFAULT_RESV_LEVEL	2
#घोषणा OCFS2_MAX_RESV_LEVEL	9
#घोषणा OCFS2_MIN_RESV_LEVEL	0

काष्ठा ocfs2_alloc_reservation अणु
	काष्ठा rb_node	r_node;

	अचिन्हित पूर्णांक	r_start;	/* Beginning of current winकरोw */
	अचिन्हित पूर्णांक	r_len;		/* Length of the winकरोw */

	अचिन्हित पूर्णांक	r_last_len;	/* Length of most recent alloc */
	अचिन्हित पूर्णांक	r_last_start;	/* Start of most recent alloc */
	काष्ठा list_head	r_lru;	/* LRU list head */

	अचिन्हित पूर्णांक	r_flags;
पूर्ण;

#घोषणा	OCFS2_RESV_FLAG_INUSE	0x01	/* Set when r_node is part of a btree */
#घोषणा	OCFS2_RESV_FLAG_TMP	0x02	/* Temporary reservation, will be
					 * destroyed immedately after use */
#घोषणा	OCFS2_RESV_FLAG_सूची	0x04	/* Reservation is क्रम an unindexed
					 * directory btree */

काष्ठा ocfs2_reservation_map अणु
	काष्ठा rb_root		m_reservations;
	अक्षर			*m_disk_biपंचांगap;

	काष्ठा ocfs2_super	*m_osb;

	/* The following are not initialized to meaningful values until a disk
	 * biपंचांगap is provided. */
	u32			m_biपंचांगap_len;	/* Number of valid
						 * bits available */

	काष्ठा list_head	m_lru;		/* LRU of reservations
						 * काष्ठाures. */

पूर्ण;

व्योम ocfs2_resv_init_once(काष्ठा ocfs2_alloc_reservation *resv);

#घोषणा OCFS2_RESV_TYPES	(OCFS2_RESV_FLAG_TMP|OCFS2_RESV_FLAG_सूची)
व्योम ocfs2_resv_set_type(काष्ठा ocfs2_alloc_reservation *resv,
			 अचिन्हित पूर्णांक flags);

पूर्णांक ocfs2_dir_resv_allowed(काष्ठा ocfs2_super *osb);

/**
 * ocfs2_resv_discard() - truncate a reservation
 * @resmap:
 * @resv: the reservation to truncate.
 *
 * After this function is called, the reservation will be empty, and
 * unlinked from the rbtree.
 */
व्योम ocfs2_resv_discard(काष्ठा ocfs2_reservation_map *resmap,
			काष्ठा ocfs2_alloc_reservation *resv);


/**
 * ocfs2_resmap_init() - Initialize fields of a reservations biपंचांगap
 * @resmap: काष्ठा ocfs2_reservation_map to initialize
 * @obj: unused क्रम now
 * @ops: unused क्रम now
 * @max_biपंचांगap_bytes: Maximum size of the biपंचांगap (typically blocksize)
 *
 * Only possible वापस value other than '0' is -ENOMEM क्रम failure to
 * allocation mirror biपंचांगap.
 */
पूर्णांक ocfs2_resmap_init(काष्ठा ocfs2_super *osb,
		      काष्ठा ocfs2_reservation_map *resmap);

/**
 * ocfs2_resmap_restart() - "restart" a reservation biपंचांगap
 * @resmap: reservations biपंचांगap
 * @clen: Number of valid bits in the biपंचांगap
 * @disk_biपंचांगap: the disk biपंचांगap this resmap should refer to.
 *
 * Re-initialize the parameters of a reservation biपंचांगap. This is
 * useful क्रम local alloc winकरोw slides.
 *
 * This function will call ocfs2_trunc_resv against all existing
 * reservations. A future version will recalculate existing
 * reservations based on the new biपंचांगap.
 */
व्योम ocfs2_resmap_restart(काष्ठा ocfs2_reservation_map *resmap,
			  अचिन्हित पूर्णांक clen, अक्षर *disk_biपंचांगap);

/**
 * ocfs2_resmap_uninit() - uninitialize a reservation biपंचांगap काष्ठाure
 * @resmap: the काष्ठा ocfs2_reservation_map to uninitialize
 */
व्योम ocfs2_resmap_uninit(काष्ठा ocfs2_reservation_map *resmap);

/**
 * ocfs2_resmap_resv_bits() - Return still-valid reservation bits
 * @resmap: reservations biपंचांगap
 * @resv: reservation to base search from
 * @cstart: start of proposed allocation
 * @clen: length (in clusters) of proposed allocation
 *
 * Using the reservation data from resv, this function will compare
 * resmap and resmap->m_disk_biपंचांगap to determine what part (अगर any) of
 * the reservation winकरोw is still clear to use. If resv is empty,
 * this function will try to allocate a winकरोw क्रम it.
 *
 * On success, zero is वापसed and the valid allocation area is set in cstart
 * and clen.
 *
 * Returns -ENOSPC अगर reservations are disabled.
 */
पूर्णांक ocfs2_resmap_resv_bits(काष्ठा ocfs2_reservation_map *resmap,
			   काष्ठा ocfs2_alloc_reservation *resv,
			   पूर्णांक *cstart, पूर्णांक *clen);

/**
 * ocfs2_resmap_claimed_bits() - Tell the reservation code that bits were used.
 * @resmap: reservations biपंचांगap
 * @resv: optional reservation to recalulate based on new biपंचांगap
 * @cstart: start of allocation in clusters
 * @clen: end of allocation in clusters.
 *
 * Tell the reservation code that bits were used to fulfill allocation in
 * resmap. The bits करोn't have to have been part of any existing
 * reservation. But we must always call this function when bits are claimed.
 * Internally, the reservations code will use this inक्रमmation to mark the
 * reservations biपंचांगap. If resv is passed, it's next allocation winकरोw will be
 * calculated. It also expects that 'cstart' is the same as we passed back
 * from ocfs2_resmap_resv_bits().
 */
व्योम ocfs2_resmap_claimed_bits(काष्ठा ocfs2_reservation_map *resmap,
			       काष्ठा ocfs2_alloc_reservation *resv,
			       u32 cstart, u32 clen);

#पूर्ण_अगर	/* OCFS2_RESERVATIONS_H */
