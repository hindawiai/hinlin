<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_SUBPAGE_H
#घोषणा BTRFS_SUBPAGE_H

#समावेश <linux/spinlock.h>

/*
 * Maximum page size we support is 64K, minimum sector size is 4K, u16 biपंचांगap
 * is sufficient. Regular biपंचांगap_* is not used due to size reasons.
 */
#घोषणा BTRFS_SUBPAGE_BITMAP_SIZE	16

/*
 * Structure to trace status of each sector inside a page, attached to
 * page::निजी क्रम both data and metadata inodes.
 */
काष्ठा btrfs_subpage अणु
	/* Common members क्रम both data and metadata pages */
	spinlock_t lock;
	u16 uptodate_biपंचांगap;
	u16 error_biपंचांगap;
	u16 dirty_biपंचांगap;
	u16 ग_लिखोback_biपंचांगap;
	जोड़ अणु
		/*
		 * Structures only used by metadata
		 *
		 * @eb_refs should only be operated under निजी_lock, as it
		 * manages whether the subpage can be detached.
		 */
		atomic_t eb_refs;
		/* Structures only used by data */
		काष्ठा अणु
			atomic_t पढ़ोers;
		पूर्ण;
	पूर्ण;
पूर्ण;

क्रमागत btrfs_subpage_type अणु
	BTRFS_SUBPAGE_METADATA,
	BTRFS_SUBPAGE_DATA,
पूर्ण;

पूर्णांक btrfs_attach_subpage(स्थिर काष्ठा btrfs_fs_info *fs_info,
			 काष्ठा page *page, क्रमागत btrfs_subpage_type type);
व्योम btrfs_detach_subpage(स्थिर काष्ठा btrfs_fs_info *fs_info,
			  काष्ठा page *page);

/* Allocate additional data where page represents more than one sector */
पूर्णांक btrfs_alloc_subpage(स्थिर काष्ठा btrfs_fs_info *fs_info,
			काष्ठा btrfs_subpage **ret,
			क्रमागत btrfs_subpage_type type);
व्योम btrfs_मुक्त_subpage(काष्ठा btrfs_subpage *subpage);

व्योम btrfs_page_inc_eb_refs(स्थिर काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा page *page);
व्योम btrfs_page_dec_eb_refs(स्थिर काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा page *page);

व्योम btrfs_subpage_start_पढ़ोer(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len);
व्योम btrfs_subpage_end_पढ़ोer(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len);

/*
 * Template क्रम subpage related operations.
 *
 * btrfs_subpage_*() are क्रम call sites where the page has subpage attached and
 * the range is ensured to be inside the page.
 *
 * btrfs_page_*() are क्रम call sites where the page can either be subpage
 * specअगरic or regular page. The function will handle both हालs.
 * But the range still needs to be inside the page.
 */
#घोषणा DECLARE_BTRFS_SUBPAGE_OPS(name)					\
व्योम btrfs_subpage_set_##name(स्थिर काष्ठा btrfs_fs_info *fs_info,	\
		काष्ठा page *page, u64 start, u32 len);			\
व्योम btrfs_subpage_clear_##name(स्थिर काष्ठा btrfs_fs_info *fs_info,	\
		काष्ठा page *page, u64 start, u32 len);			\
bool btrfs_subpage_test_##name(स्थिर काष्ठा btrfs_fs_info *fs_info,	\
		काष्ठा page *page, u64 start, u32 len);			\
व्योम btrfs_page_set_##name(स्थिर काष्ठा btrfs_fs_info *fs_info,		\
		काष्ठा page *page, u64 start, u32 len);			\
व्योम btrfs_page_clear_##name(स्थिर काष्ठा btrfs_fs_info *fs_info,	\
		काष्ठा page *page, u64 start, u32 len);			\
bool btrfs_page_test_##name(स्थिर काष्ठा btrfs_fs_info *fs_info,	\
		काष्ठा page *page, u64 start, u32 len);

DECLARE_BTRFS_SUBPAGE_OPS(uptodate);
DECLARE_BTRFS_SUBPAGE_OPS(error);
DECLARE_BTRFS_SUBPAGE_OPS(dirty);
DECLARE_BTRFS_SUBPAGE_OPS(ग_लिखोback);

bool btrfs_subpage_clear_and_test_dirty(स्थिर काष्ठा btrfs_fs_info *fs_info,
		काष्ठा page *page, u64 start, u32 len);

#पूर्ण_अगर
