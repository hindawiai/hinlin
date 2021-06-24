<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * attrib.h - Defines क्रम attribute handling in NTFS Linux kernel driver.
 *	      Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2005 Anton Altaparmakov
 * Copyright (c) 2002 Riअक्षरd Russon
 */

#अगर_अघोषित _LINUX_NTFS_ATTRIB_H
#घोषणा _LINUX_NTFS_ATTRIB_H

#समावेश "endian.h"
#समावेश "types.h"
#समावेश "layout.h"
#समावेश "inode.h"
#समावेश "runlist.h"
#समावेश "volume.h"

/**
 * ntfs_attr_search_ctx - used in attribute search functions
 * @mrec:	buffer containing mft record to search
 * @attr:	attribute record in @mrec where to begin/जारी search
 * @is_first:	अगर true ntfs_attr_lookup() begins search with @attr, अन्यथा after
 *
 * Structure must be initialized to zero beक्रमe the first call to one of the
 * attribute search functions. Initialize @mrec to poपूर्णांक to the mft record to
 * search, and @attr to poपूर्णांक to the first attribute within @mrec (not necessary
 * अगर calling the _first() functions), and set @is_first to 'true' (not necessary
 * अगर calling the _first() functions).
 *
 * If @is_first is 'true', the search begins with @attr. If @is_first is 'false',
 * the search begins after @attr. This is so that, after the first call to one
 * of the search attribute functions, we can call the function again, without
 * any modअगरication of the search context, to स्वतःmagically get the next
 * matching attribute.
 */
प्रकार काष्ठा अणु
	MFT_RECORD *mrec;
	ATTR_RECORD *attr;
	bool is_first;
	ntfs_inode *ntfs_ino;
	ATTR_LIST_ENTRY *al_entry;
	ntfs_inode *base_ntfs_ino;
	MFT_RECORD *base_mrec;
	ATTR_RECORD *base_attr;
पूर्ण ntfs_attr_search_ctx;

बाह्य पूर्णांक ntfs_map_runlist_nolock(ntfs_inode *ni, VCN vcn,
		ntfs_attr_search_ctx *ctx);
बाह्य पूर्णांक ntfs_map_runlist(ntfs_inode *ni, VCN vcn);

बाह्य LCN ntfs_attr_vcn_to_lcn_nolock(ntfs_inode *ni, स्थिर VCN vcn,
		स्थिर bool ग_लिखो_locked);

बाह्य runlist_element *ntfs_attr_find_vcn_nolock(ntfs_inode *ni,
		स्थिर VCN vcn, ntfs_attr_search_ctx *ctx);

पूर्णांक ntfs_attr_lookup(स्थिर ATTR_TYPE type, स्थिर ntfsअक्षर *name,
		स्थिर u32 name_len, स्थिर IGNORE_CASE_BOOL ic,
		स्थिर VCN lowest_vcn, स्थिर u8 *val, स्थिर u32 val_len,
		ntfs_attr_search_ctx *ctx);

बाह्य पूर्णांक load_attribute_list(ntfs_volume *vol, runlist *rl, u8 *al_start,
		स्थिर s64 size, स्थिर s64 initialized_size);

अटल अंतरभूत s64 ntfs_attr_size(स्थिर ATTR_RECORD *a)
अणु
	अगर (!a->non_resident)
		वापस (s64)le32_to_cpu(a->data.resident.value_length);
	वापस sle64_to_cpu(a->data.non_resident.data_size);
पूर्ण

बाह्य व्योम ntfs_attr_reinit_search_ctx(ntfs_attr_search_ctx *ctx);
बाह्य ntfs_attr_search_ctx *ntfs_attr_get_search_ctx(ntfs_inode *ni,
		MFT_RECORD *mrec);
बाह्य व्योम ntfs_attr_put_search_ctx(ntfs_attr_search_ctx *ctx);

#अगर_घोषित NTFS_RW

बाह्य पूर्णांक ntfs_attr_size_bounds_check(स्थिर ntfs_volume *vol,
		स्थिर ATTR_TYPE type, स्थिर s64 size);
बाह्य पूर्णांक ntfs_attr_can_be_non_resident(स्थिर ntfs_volume *vol,
		स्थिर ATTR_TYPE type);
बाह्य पूर्णांक ntfs_attr_can_be_resident(स्थिर ntfs_volume *vol,
		स्थिर ATTR_TYPE type);

बाह्य पूर्णांक ntfs_attr_record_resize(MFT_RECORD *m, ATTR_RECORD *a, u32 new_size);
बाह्य पूर्णांक ntfs_resident_attr_value_resize(MFT_RECORD *m, ATTR_RECORD *a,
		स्थिर u32 new_size);

बाह्य पूर्णांक ntfs_attr_make_non_resident(ntfs_inode *ni, स्थिर u32 data_size);

बाह्य s64 ntfs_attr_extend_allocation(ntfs_inode *ni, s64 new_alloc_size,
		स्थिर s64 new_data_size, स्थिर s64 data_start);

बाह्य पूर्णांक ntfs_attr_set(ntfs_inode *ni, स्थिर s64 ofs, स्थिर s64 cnt,
		स्थिर u8 val);

#पूर्ण_अगर /* NTFS_RW */

#पूर्ण_अगर /* _LINUX_NTFS_ATTRIB_H */
