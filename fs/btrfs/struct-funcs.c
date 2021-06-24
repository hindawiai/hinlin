<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <यंत्र/unaligned.h>

#समावेश "ctree.h"

अटल bool check_setget_bounds(स्थिर काष्ठा extent_buffer *eb,
				स्थिर व्योम *ptr, अचिन्हित off, पूर्णांक size)
अणु
	स्थिर अचिन्हित दीर्घ member_offset = (अचिन्हित दीर्घ)ptr + off;

	अगर (member_offset > eb->len) अणु
		btrfs_warn(eb->fs_info,
	"bad eb member start: ptr 0x%lx start %llu member offset %lu size %d",
			(अचिन्हित दीर्घ)ptr, eb->start, member_offset, size);
		वापस false;
	पूर्ण
	अगर (member_offset + size > eb->len) अणु
		btrfs_warn(eb->fs_info,
	"bad eb member end: ptr 0x%lx start %llu member offset %lu size %d",
			(अचिन्हित दीर्घ)ptr, eb->start, member_offset, size);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Macro ढाँचाs that define helpers to पढ़ो/ग_लिखो extent buffer data of a
 * given size, that are also used via ctree.h क्रम access to item members by
 * specialized helpers.
 *
 * Generic helpers:
 * - btrfs_set_8 (क्रम 8/16/32/64)
 * - btrfs_get_8 (क्रम 8/16/32/64)
 *
 * Generic helpers with a token (cached address of the most recently accessed
 * page):
 * - btrfs_set_token_8 (क्रम 8/16/32/64)
 * - btrfs_get_token_8 (क्रम 8/16/32/64)
 *
 * The set/get functions handle data spanning two pages transparently, in हाल
 * metadata block size is larger than page.  Every poपूर्णांकer to metadata items is
 * an offset पूर्णांकo the extent buffer page array, cast to a specअगरic type.  This
 * gives us all the type checking.
 *
 * The extent buffer pages stored in the array pages करो not क्रमm a contiguous
 * phyusical range, but the API functions assume the linear offset to the range
 * from 0 to metadata node size.
 */

#घोषणा DEFINE_BTRFS_SETGET_BITS(bits)					\
u##bits btrfs_get_token_##bits(काष्ठा btrfs_map_token *token,		\
			       स्थिर व्योम *ptr, अचिन्हित दीर्घ off)	\
अणु									\
	स्थिर अचिन्हित दीर्घ member_offset = (अचिन्हित दीर्घ)ptr + off;	\
	स्थिर अचिन्हित दीर्घ idx = get_eb_page_index(member_offset);	\
	स्थिर अचिन्हित दीर्घ oip = get_eb_offset_in_page(token->eb,	\
							member_offset);	\
	स्थिर पूर्णांक size = माप(u##bits);				\
	u8 lebytes[माप(u##bits)];					\
	स्थिर पूर्णांक part = PAGE_SIZE - oip;				\
									\
	ASSERT(token);							\
	ASSERT(token->kaddr);						\
	ASSERT(check_setget_bounds(token->eb, ptr, off, size));		\
	अगर (token->offset <= member_offset &&				\
	    member_offset + size <= token->offset + PAGE_SIZE) अणु	\
		वापस get_unaligned_le##bits(token->kaddr + oip);	\
	पूर्ण								\
	token->kaddr = page_address(token->eb->pages[idx]);		\
	token->offset = idx << PAGE_SHIFT;				\
	अगर (oip + size <= PAGE_SIZE)					\
		वापस get_unaligned_le##bits(token->kaddr + oip);	\
									\
	स_नकल(lebytes, token->kaddr + oip, part);			\
	token->kaddr = page_address(token->eb->pages[idx + 1]);		\
	token->offset = (idx + 1) << PAGE_SHIFT;			\
	स_नकल(lebytes + part, token->kaddr, size - part);		\
	वापस get_unaligned_le##bits(lebytes);				\
पूर्ण									\
u##bits btrfs_get_##bits(स्थिर काष्ठा extent_buffer *eb,		\
			 स्थिर व्योम *ptr, अचिन्हित दीर्घ off)		\
अणु									\
	स्थिर अचिन्हित दीर्घ member_offset = (अचिन्हित दीर्घ)ptr + off;	\
	स्थिर अचिन्हित दीर्घ oip = get_eb_offset_in_page(eb, member_offset); \
	स्थिर अचिन्हित दीर्घ idx = get_eb_page_index(member_offset);	\
	अक्षर *kaddr = page_address(eb->pages[idx]);			\
	स्थिर पूर्णांक size = माप(u##bits);				\
	स्थिर पूर्णांक part = PAGE_SIZE - oip;				\
	u8 lebytes[माप(u##bits)];					\
									\
	ASSERT(check_setget_bounds(eb, ptr, off, size));		\
	अगर (oip + size <= PAGE_SIZE)					\
		वापस get_unaligned_le##bits(kaddr + oip);		\
									\
	स_नकल(lebytes, kaddr + oip, part);				\
	kaddr = page_address(eb->pages[idx + 1]);			\
	स_नकल(lebytes + part, kaddr, size - part);			\
	वापस get_unaligned_le##bits(lebytes);				\
पूर्ण									\
व्योम btrfs_set_token_##bits(काष्ठा btrfs_map_token *token,		\
			    स्थिर व्योम *ptr, अचिन्हित दीर्घ off,		\
			    u##bits val)				\
अणु									\
	स्थिर अचिन्हित दीर्घ member_offset = (अचिन्हित दीर्घ)ptr + off;	\
	स्थिर अचिन्हित दीर्घ idx = get_eb_page_index(member_offset);	\
	स्थिर अचिन्हित दीर्घ oip = get_eb_offset_in_page(token->eb,	\
							member_offset);	\
	स्थिर पूर्णांक size = माप(u##bits);				\
	u8 lebytes[माप(u##bits)];					\
	स्थिर पूर्णांक part = PAGE_SIZE - oip;				\
									\
	ASSERT(token);							\
	ASSERT(token->kaddr);						\
	ASSERT(check_setget_bounds(token->eb, ptr, off, size));		\
	अगर (token->offset <= member_offset &&				\
	    member_offset + size <= token->offset + PAGE_SIZE) अणु	\
		put_unaligned_le##bits(val, token->kaddr + oip);	\
		वापस;							\
	पूर्ण								\
	token->kaddr = page_address(token->eb->pages[idx]);		\
	token->offset = idx << PAGE_SHIFT;				\
	अगर (oip + size <= PAGE_SIZE) अणु					\
		put_unaligned_le##bits(val, token->kaddr + oip);	\
		वापस;							\
	पूर्ण								\
	put_unaligned_le##bits(val, lebytes);				\
	स_नकल(token->kaddr + oip, lebytes, part);			\
	token->kaddr = page_address(token->eb->pages[idx + 1]);		\
	token->offset = (idx + 1) << PAGE_SHIFT;			\
	स_नकल(token->kaddr, lebytes + part, size - part);		\
पूर्ण									\
व्योम btrfs_set_##bits(स्थिर काष्ठा extent_buffer *eb, व्योम *ptr,	\
		      अचिन्हित दीर्घ off, u##bits val)			\
अणु									\
	स्थिर अचिन्हित दीर्घ member_offset = (अचिन्हित दीर्घ)ptr + off;	\
	स्थिर अचिन्हित दीर्घ oip = get_eb_offset_in_page(eb, member_offset); \
	स्थिर अचिन्हित दीर्घ idx = get_eb_page_index(member_offset);	\
	अक्षर *kaddr = page_address(eb->pages[idx]);			\
	स्थिर पूर्णांक size = माप(u##bits);				\
	स्थिर पूर्णांक part = PAGE_SIZE - oip;				\
	u8 lebytes[माप(u##bits)];					\
									\
	ASSERT(check_setget_bounds(eb, ptr, off, size));		\
	अगर (oip + size <= PAGE_SIZE) अणु					\
		put_unaligned_le##bits(val, kaddr + oip);		\
		वापस;							\
	पूर्ण								\
									\
	put_unaligned_le##bits(val, lebytes);				\
	स_नकल(kaddr + oip, lebytes, part);				\
	kaddr = page_address(eb->pages[idx + 1]);			\
	स_नकल(kaddr, lebytes + part, size - part);			\
पूर्ण

DEFINE_BTRFS_SETGET_BITS(8)
DEFINE_BTRFS_SETGET_BITS(16)
DEFINE_BTRFS_SETGET_BITS(32)
DEFINE_BTRFS_SETGET_BITS(64)

व्योम btrfs_node_key(स्थिर काष्ठा extent_buffer *eb,
		    काष्ठा btrfs_disk_key *disk_key, पूर्णांक nr)
अणु
	अचिन्हित दीर्घ ptr = btrfs_node_key_ptr_offset(nr);
	पढ़ो_eb_member(eb, (काष्ठा btrfs_key_ptr *)ptr,
		       काष्ठा btrfs_key_ptr, key, disk_key);
पूर्ण
