<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * runlist.h - Defines क्रम runlist handling in NTFS Linux kernel driver.
 *	       Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2005 Anton Altaparmakov
 * Copyright (c) 2002 Riअक्षरd Russon
 */

#अगर_अघोषित _LINUX_NTFS_RUNLIST_H
#घोषणा _LINUX_NTFS_RUNLIST_H

#समावेश "types.h"
#समावेश "layout.h"
#समावेश "volume.h"

/**
 * runlist_element - in memory vcn to lcn mapping array element
 * @vcn:	starting vcn of the current array element
 * @lcn:	starting lcn of the current array element
 * @length:	length in clusters of the current array element
 *
 * The last vcn (in fact the last vcn + 1) is reached when length == 0.
 *
 * When lcn == -1 this means that the count vcns starting at vcn are not
 * physically allocated (i.e. this is a hole / data is sparse).
 */
प्रकार काष्ठा अणु	/* In memory vcn to lcn mapping काष्ठाure element. */
	VCN vcn;	/* vcn = Starting भव cluster number. */
	LCN lcn;	/* lcn = Starting logical cluster number. */
	s64 length;	/* Run length in clusters. */
पूर्ण runlist_element;

/**
 * runlist - in memory vcn to lcn mapping array including a पढ़ो/ग_लिखो lock
 * @rl:		poपूर्णांकer to an array of runlist elements
 * @lock:	पढ़ो/ग_लिखो spinlock क्रम serializing access to @rl
 *
 */
प्रकार काष्ठा अणु
	runlist_element *rl;
	काष्ठा rw_semaphore lock;
पूर्ण runlist;

अटल अंतरभूत व्योम ntfs_init_runlist(runlist *rl)
अणु
	rl->rl = शून्य;
	init_rwsem(&rl->lock);
पूर्ण

प्रकार क्रमागत अणु
	LCN_HOLE		= -1,	/* Keep this as highest value or die! */
	LCN_RL_NOT_MAPPED	= -2,
	LCN_ENOENT		= -3,
	LCN_ENOMEM		= -4,
	LCN_EIO			= -5,
पूर्ण LCN_SPECIAL_VALUES;

बाह्य runlist_element *ntfs_runlists_merge(runlist_element *drl,
		runlist_element *srl);

बाह्य runlist_element *ntfs_mapping_pairs_decompress(स्थिर ntfs_volume *vol,
		स्थिर ATTR_RECORD *attr, runlist_element *old_rl);

बाह्य LCN ntfs_rl_vcn_to_lcn(स्थिर runlist_element *rl, स्थिर VCN vcn);

#अगर_घोषित NTFS_RW

बाह्य runlist_element *ntfs_rl_find_vcn_nolock(runlist_element *rl,
		स्थिर VCN vcn);

बाह्य पूर्णांक ntfs_get_size_क्रम_mapping_pairs(स्थिर ntfs_volume *vol,
		स्थिर runlist_element *rl, स्थिर VCN first_vcn,
		स्थिर VCN last_vcn);

बाह्य पूर्णांक ntfs_mapping_pairs_build(स्थिर ntfs_volume *vol, s8 *dst,
		स्थिर पूर्णांक dst_len, स्थिर runlist_element *rl,
		स्थिर VCN first_vcn, स्थिर VCN last_vcn, VCN *स्थिर stop_vcn);

बाह्य पूर्णांक ntfs_rl_truncate_nolock(स्थिर ntfs_volume *vol,
		runlist *स्थिर runlist, स्थिर s64 new_length);

पूर्णांक ntfs_rl_punch_nolock(स्थिर ntfs_volume *vol, runlist *स्थिर runlist,
		स्थिर VCN start, स्थिर s64 length);

#पूर्ण_अगर /* NTFS_RW */

#पूर्ण_अगर /* _LINUX_NTFS_RUNLIST_H */
