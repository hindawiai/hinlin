<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * squashfs.h
 */

#घोषणा TRACE(s, args...)	pr_debug("SQUASHFS: "s, ## args)

#घोषणा ERROR(s, args...)	pr_err("SQUASHFS error: "s, ## args)

#घोषणा WARNING(s, args...)	pr_warn("SQUASHFS: "s, ## args)

/* block.c */
बाह्य पूर्णांक squashfs_पढ़ो_data(काष्ठा super_block *, u64, पूर्णांक, u64 *,
				काष्ठा squashfs_page_actor *);

/* cache.c */
बाह्य काष्ठा squashfs_cache *squashfs_cache_init(अक्षर *, पूर्णांक, पूर्णांक);
बाह्य व्योम squashfs_cache_delete(काष्ठा squashfs_cache *);
बाह्य काष्ठा squashfs_cache_entry *squashfs_cache_get(काष्ठा super_block *,
				काष्ठा squashfs_cache *, u64, पूर्णांक);
बाह्य व्योम squashfs_cache_put(काष्ठा squashfs_cache_entry *);
बाह्य पूर्णांक squashfs_copy_data(व्योम *, काष्ठा squashfs_cache_entry *, पूर्णांक, पूर्णांक);
बाह्य पूर्णांक squashfs_पढ़ो_metadata(काष्ठा super_block *, व्योम *, u64 *,
				पूर्णांक *, पूर्णांक);
बाह्य काष्ठा squashfs_cache_entry *squashfs_get_fragment(काष्ठा super_block *,
				u64, पूर्णांक);
बाह्य काष्ठा squashfs_cache_entry *squashfs_get_datablock(काष्ठा super_block *,
				u64, पूर्णांक);
बाह्य व्योम *squashfs_पढ़ो_table(काष्ठा super_block *, u64, पूर्णांक);

/* decompressor.c */
बाह्य स्थिर काष्ठा squashfs_decompressor *squashfs_lookup_decompressor(पूर्णांक);
बाह्य व्योम *squashfs_decompressor_setup(काष्ठा super_block *, अचिन्हित लघु);

/* decompressor_xxx.c */
बाह्य व्योम *squashfs_decompressor_create(काष्ठा squashfs_sb_info *, व्योम *);
बाह्य व्योम squashfs_decompressor_destroy(काष्ठा squashfs_sb_info *);
बाह्य पूर्णांक squashfs_decompress(काष्ठा squashfs_sb_info *, काष्ठा bio *,
				पूर्णांक, पूर्णांक, काष्ठा squashfs_page_actor *);
बाह्य पूर्णांक squashfs_max_decompressors(व्योम);

/* export.c */
बाह्य __le64 *squashfs_पढ़ो_inode_lookup_table(काष्ठा super_block *, u64, u64,
				अचिन्हित पूर्णांक);

/* fragment.c */
बाह्य पूर्णांक squashfs_frag_lookup(काष्ठा super_block *, अचिन्हित पूर्णांक, u64 *);
बाह्य __le64 *squashfs_पढ़ो_fragment_index_table(काष्ठा super_block *,
				u64, u64, अचिन्हित पूर्णांक);

/* file.c */
व्योम squashfs_fill_page(काष्ठा page *, काष्ठा squashfs_cache_entry *, पूर्णांक, पूर्णांक);
व्योम squashfs_copy_cache(काष्ठा page *, काष्ठा squashfs_cache_entry *, पूर्णांक,
				पूर्णांक);

/* file_xxx.c */
बाह्य पूर्णांक squashfs_पढ़ोpage_block(काष्ठा page *, u64, पूर्णांक, पूर्णांक);

/* id.c */
बाह्य पूर्णांक squashfs_get_id(काष्ठा super_block *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक *);
बाह्य __le64 *squashfs_पढ़ो_id_index_table(काष्ठा super_block *, u64, u64,
				अचिन्हित लघु);

/* inode.c */
बाह्य काष्ठा inode *squashfs_iget(काष्ठा super_block *, दीर्घ दीर्घ,
				अचिन्हित पूर्णांक);
बाह्य पूर्णांक squashfs_पढ़ो_inode(काष्ठा inode *, दीर्घ दीर्घ);

/* xattr.c */
बाह्य sमाप_प्रकार squashfs_listxattr(काष्ठा dentry *, अक्षर *, माप_प्रकार);

/*
 * Inodes, files,  decompressor and xattr operations
 */

/* dir.c */
बाह्य स्थिर काष्ठा file_operations squashfs_dir_ops;

/* export.c */
बाह्य स्थिर काष्ठा export_operations squashfs_export_ops;

/* file.c */
बाह्य स्थिर काष्ठा address_space_operations squashfs_aops;

/* inode.c */
बाह्य स्थिर काष्ठा inode_operations squashfs_inode_ops;

/* namei.c */
बाह्य स्थिर काष्ठा inode_operations squashfs_dir_inode_ops;

/* symlink.c */
बाह्य स्थिर काष्ठा address_space_operations squashfs_symlink_aops;
बाह्य स्थिर काष्ठा inode_operations squashfs_symlink_inode_ops;

/* xattr.c */
बाह्य स्थिर काष्ठा xattr_handler *squashfs_xattr_handlers[];
