<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#अगर_अघोषित __EROFS_FS_ZDATA_H
#घोषणा __EROFS_FS_ZDATA_H

#समावेश "internal.h"
#समावेश "zpvec.h"

#घोषणा Z_EROFS_PCLUSTER_MAX_PAGES	(Z_EROFS_PCLUSTER_MAX_SIZE / PAGE_SIZE)
#घोषणा Z_EROFS_NR_INLINE_PAGEVECS      3

/*
 * Structure fields follow one of the following exclusion rules.
 *
 * I: Modअगरiable by initialization/deकाष्ठाion paths and पढ़ो-only
 *    क्रम everyone अन्यथा;
 *
 * L: Field should be रक्षित by pageset lock;
 *
 * A: Field should be accessed / updated in atomic क्रम parallelized code.
 */
काष्ठा z_erofs_collection अणु
	काष्ठा mutex lock;

	/* I: page offset of start position of decompression */
	अचिन्हित लघु pageofs;

	/* L: maximum relative page index in pagevec[] */
	अचिन्हित लघु nr_pages;

	/* L: total number of pages in pagevec[] */
	अचिन्हित पूर्णांक vcnt;

	जोड़ अणु
		/* L: अंतरभूत a certain number of pagevecs क्रम bootstrap */
		erofs_vtptr_t pagevec[Z_EROFS_NR_INLINE_PAGEVECS];

		/* I: can be used to मुक्त the pcluster by RCU. */
		काष्ठा rcu_head rcu;
	पूर्ण;
पूर्ण;

#घोषणा Z_EROFS_PCLUSTER_FULL_LENGTH    0x00000001
#घोषणा Z_EROFS_PCLUSTER_LENGTH_BIT     1

/*
 * let's leave a type here in हाल of पूर्णांकroducing
 * another tagged poपूर्णांकer later.
 */
प्रकार व्योम *z_erofs_next_pcluster_t;

काष्ठा z_erofs_pcluster अणु
	काष्ठा erofs_workgroup obj;
	काष्ठा z_erofs_collection primary_collection;

	/* A: poपूर्णांक to next chained pcluster or TAILs */
	z_erofs_next_pcluster_t next;

	/* A: lower limit of decompressed length and अगर full length or not */
	अचिन्हित पूर्णांक length;

	/* I: physical cluster size in pages */
	अचिन्हित लघु pclusterpages;

	/* I: compression algorithm क्रमmat */
	अचिन्हित अक्षर algorithmक्रमmat;

	/* A: compressed pages (can be cached or inplaced pages) */
	काष्ठा page *compressed_pages[];
पूर्ण;

#घोषणा z_erofs_primarycollection(pcluster) (&(pcluster)->primary_collection)

/* let's aव्योम the valid 32-bit kernel addresses */

/* the chained workgroup has't submitted io (still खोलो) */
#घोषणा Z_EROFS_PCLUSTER_TAIL           ((व्योम *)0x5F0ECAFE)
/* the chained workgroup has alपढ़ोy submitted io */
#घोषणा Z_EROFS_PCLUSTER_TAIL_CLOSED    ((व्योम *)0x5F0EDEAD)

#घोषणा Z_EROFS_PCLUSTER_NIL            (शून्य)

काष्ठा z_erofs_decompressqueue अणु
	काष्ठा super_block *sb;
	atomic_t pending_bios;
	z_erofs_next_pcluster_t head;

	जोड़ अणु
		रुको_queue_head_t रुको;
		काष्ठा work_काष्ठा work;
	पूर्ण u;
पूर्ण;

#घोषणा MNGD_MAPPING(sbi)	((sbi)->managed_cache->i_mapping)
अटल अंतरभूत bool erofs_page_is_managed(स्थिर काष्ठा erofs_sb_info *sbi,
					 काष्ठा page *page)
अणु
	वापस page->mapping == MNGD_MAPPING(sbi);
पूर्ण

#घोषणा Z_EROFS_ONLINEPAGE_COUNT_BITS   2
#घोषणा Z_EROFS_ONLINEPAGE_COUNT_MASK   ((1 << Z_EROFS_ONLINEPAGE_COUNT_BITS) - 1)
#घोषणा Z_EROFS_ONLINEPAGE_INDEX_SHIFT  (Z_EROFS_ONLINEPAGE_COUNT_BITS)

/*
 * रुकोers (aka. ongoing_packs): # to unlock the page
 * sub-index: 0 - क्रम partial page, >= 1 full page sub-index
 */
प्रकार atomic_t z_erofs_onlinepage_t;

/* type punning */
जोड़ z_erofs_onlinepage_converter अणु
	z_erofs_onlinepage_t *o;
	अचिन्हित दीर्घ *v;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक z_erofs_onlinepage_index(काष्ठा page *page)
अणु
	जोड़ z_erofs_onlinepage_converter u;

	DBG_BUGON(!PagePrivate(page));
	u.v = &page_निजी(page);

	वापस atomic_पढ़ो(u.o) >> Z_EROFS_ONLINEPAGE_INDEX_SHIFT;
पूर्ण

अटल अंतरभूत व्योम z_erofs_onlinepage_init(काष्ठा page *page)
अणु
	जोड़ अणु
		z_erofs_onlinepage_t o;
		अचिन्हित दीर्घ v;
	/* keep from being unlocked in advance */
	पूर्ण u = अणु .o = ATOMIC_INIT(1) पूर्ण;

	set_page_निजी(page, u.v);
	smp_wmb();
	SetPagePrivate(page);
पूर्ण

अटल अंतरभूत व्योम z_erofs_onlinepage_fixup(काष्ठा page *page,
	uपूर्णांकptr_t index, bool करोwn)
अणु
	जोड़ z_erofs_onlinepage_converter u = अणु .v = &page_निजी(page) पूर्ण;
	पूर्णांक orig, orig_index, val;

repeat:
	orig = atomic_पढ़ो(u.o);
	orig_index = orig >> Z_EROFS_ONLINEPAGE_INDEX_SHIFT;
	अगर (orig_index) अणु
		अगर (!index)
			वापस;

		DBG_BUGON(orig_index != index);
	पूर्ण

	val = (index << Z_EROFS_ONLINEPAGE_INDEX_SHIFT) |
		((orig & Z_EROFS_ONLINEPAGE_COUNT_MASK) + (अचिन्हित पूर्णांक)करोwn);
	अगर (atomic_cmpxchg(u.o, orig, val) != orig)
		जाओ repeat;
पूर्ण

अटल अंतरभूत व्योम z_erofs_onlinepage_endio(काष्ठा page *page)
अणु
	जोड़ z_erofs_onlinepage_converter u;
	अचिन्हित पूर्णांक v;

	DBG_BUGON(!PagePrivate(page));
	u.v = &page_निजी(page);

	v = atomic_dec_वापस(u.o);
	अगर (!(v & Z_EROFS_ONLINEPAGE_COUNT_MASK)) अणु
		set_page_निजी(page, 0);
		ClearPagePrivate(page);
		अगर (!PageError(page))
			SetPageUptodate(page);
		unlock_page(page);
	पूर्ण
	erofs_dbg("%s, page %p value %x", __func__, page, atomic_पढ़ो(u.o));
पूर्ण

#घोषणा Z_EROFS_VMAP_ONSTACK_PAGES	\
	min_t(अचिन्हित पूर्णांक, THREAD_SIZE / 8 / माप(काष्ठा page *), 96U)
#घोषणा Z_EROFS_VMAP_GLOBAL_PAGES	2048

#पूर्ण_अगर

