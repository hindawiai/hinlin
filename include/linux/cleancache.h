<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CLEANCACHE_H
#घोषणा _LINUX_CLEANCACHE_H

#समावेश <linux/fs.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/mm.h>

#घोषणा CLEANCACHE_NO_POOL		-1
#घोषणा CLEANCACHE_NO_BACKEND		-2
#घोषणा CLEANCACHE_NO_BACKEND_SHARED	-3

#घोषणा CLEANCACHE_KEY_MAX 6

/*
 * cleancache requires every file with a page in cleancache to have a
 * unique key unless/until the file is हटाओd/truncated.  For some
 * fileप्रणालीs, the inode number is unique, but क्रम "modern" fileप्रणालीs
 * an exportable filehandle is required (see exportfs.h)
 */
काष्ठा cleancache_filekey अणु
	जोड़ अणु
		ino_t ino;
		__u32 fh[CLEANCACHE_KEY_MAX];
		u32 key[CLEANCACHE_KEY_MAX];
	पूर्ण u;
पूर्ण;

काष्ठा cleancache_ops अणु
	पूर्णांक (*init_fs)(माप_प्रकार);
	पूर्णांक (*init_shared_fs)(uuid_t *uuid, माप_प्रकार);
	पूर्णांक (*get_page)(पूर्णांक, काष्ठा cleancache_filekey,
			pgoff_t, काष्ठा page *);
	व्योम (*put_page)(पूर्णांक, काष्ठा cleancache_filekey,
			pgoff_t, काष्ठा page *);
	व्योम (*invalidate_page)(पूर्णांक, काष्ठा cleancache_filekey, pgoff_t);
	व्योम (*invalidate_inode)(पूर्णांक, काष्ठा cleancache_filekey);
	व्योम (*invalidate_fs)(पूर्णांक);
पूर्ण;

बाह्य पूर्णांक cleancache_रेजिस्टर_ops(स्थिर काष्ठा cleancache_ops *ops);
बाह्य व्योम __cleancache_init_fs(काष्ठा super_block *);
बाह्य व्योम __cleancache_init_shared_fs(काष्ठा super_block *);
बाह्य पूर्णांक  __cleancache_get_page(काष्ठा page *);
बाह्य व्योम __cleancache_put_page(काष्ठा page *);
बाह्य व्योम __cleancache_invalidate_page(काष्ठा address_space *, काष्ठा page *);
बाह्य व्योम __cleancache_invalidate_inode(काष्ठा address_space *);
बाह्य व्योम __cleancache_invalidate_fs(काष्ठा super_block *);

#अगर_घोषित CONFIG_CLEANCACHE
#घोषणा cleancache_enabled (1)
अटल अंतरभूत bool cleancache_fs_enabled_mapping(काष्ठा address_space *mapping)
अणु
	वापस mapping->host->i_sb->cleancache_poolid >= 0;
पूर्ण
अटल अंतरभूत bool cleancache_fs_enabled(काष्ठा page *page)
अणु
	वापस cleancache_fs_enabled_mapping(page->mapping);
पूर्ण
#अन्यथा
#घोषणा cleancache_enabled (0)
#घोषणा cleancache_fs_enabled(_page) (0)
#घोषणा cleancache_fs_enabled_mapping(_page) (0)
#पूर्ण_अगर

/*
 * The shim layer provided by these अंतरभूत functions allows the compiler
 * to reduce all cleancache hooks to nothingness अगर CONFIG_CLEANCACHE
 * is disabled, to a single global variable check अगर CONFIG_CLEANCACHE
 * is enabled but no cleancache "backend" has dynamically enabled it,
 * and, क्रम the most frequent cleancache ops, to a single global variable
 * check plus a superblock element comparison अगर CONFIG_CLEANCACHE is enabled
 * and a cleancache backend has dynamically enabled cleancache, but the
 * fileप्रणाली referenced by that cleancache op has not enabled cleancache.
 * As a result, CONFIG_CLEANCACHE can be enabled by शेष with essentially
 * no measurable perक्रमmance impact.
 */

अटल अंतरभूत व्योम cleancache_init_fs(काष्ठा super_block *sb)
अणु
	अगर (cleancache_enabled)
		__cleancache_init_fs(sb);
पूर्ण

अटल अंतरभूत व्योम cleancache_init_shared_fs(काष्ठा super_block *sb)
अणु
	अगर (cleancache_enabled)
		__cleancache_init_shared_fs(sb);
पूर्ण

अटल अंतरभूत पूर्णांक cleancache_get_page(काष्ठा page *page)
अणु
	अगर (cleancache_enabled && cleancache_fs_enabled(page))
		वापस __cleancache_get_page(page);
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम cleancache_put_page(काष्ठा page *page)
अणु
	अगर (cleancache_enabled && cleancache_fs_enabled(page))
		__cleancache_put_page(page);
पूर्ण

अटल अंतरभूत व्योम cleancache_invalidate_page(काष्ठा address_space *mapping,
					काष्ठा page *page)
अणु
	/* careful... page->mapping is शून्य someबार when this is called */
	अगर (cleancache_enabled && cleancache_fs_enabled_mapping(mapping))
		__cleancache_invalidate_page(mapping, page);
पूर्ण

अटल अंतरभूत व्योम cleancache_invalidate_inode(काष्ठा address_space *mapping)
अणु
	अगर (cleancache_enabled && cleancache_fs_enabled_mapping(mapping))
		__cleancache_invalidate_inode(mapping);
पूर्ण

अटल अंतरभूत व्योम cleancache_invalidate_fs(काष्ठा super_block *sb)
अणु
	अगर (cleancache_enabled)
		__cleancache_invalidate_fs(sb);
पूर्ण

#पूर्ण_अगर /* _LINUX_CLEANCACHE_H */
