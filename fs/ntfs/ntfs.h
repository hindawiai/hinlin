<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ntfs.h - Defines क्रम NTFS Linux kernel driver.
 *
 * Copyright (c) 2001-2014 Anton Altaparmakov and Tuxera Inc.
 * Copyright (C) 2002 Riअक्षरd Russon
 */

#अगर_अघोषित _LINUX_NTFS_H
#घोषणा _LINUX_NTFS_H

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/compiler.h>
#समावेश <linux/fs.h>
#समावेश <linux/nls.h>
#समावेश <linux/smp.h>
#समावेश <linux/pagemap.h>

#समावेश "types.h"
#समावेश "volume.h"
#समावेश "layout.h"

प्रकार क्रमागत अणु
	NTFS_BLOCK_SIZE		= 512,
	NTFS_BLOCK_SIZE_BITS	= 9,
	NTFS_SB_MAGIC		= 0x5346544e,	/* 'NTFS' */
	NTFS_MAX_NAME_LEN	= 255,
	NTFS_MAX_ATTR_NAME_LEN	= 255,
	NTFS_MAX_CLUSTER_SIZE	= 64 * 1024,	/* 64kiB */
	NTFS_MAX_PAGES_PER_CLUSTER = NTFS_MAX_CLUSTER_SIZE / PAGE_SIZE,
पूर्ण NTFS_CONSTANTS;

/* Global variables. */

/* Slab caches (from super.c). */
बाह्य काष्ठा kmem_cache *ntfs_name_cache;
बाह्य काष्ठा kmem_cache *ntfs_inode_cache;
बाह्य काष्ठा kmem_cache *ntfs_big_inode_cache;
बाह्य काष्ठा kmem_cache *ntfs_attr_ctx_cache;
बाह्य काष्ठा kmem_cache *ntfs_index_ctx_cache;

/* The various operations काष्ठाs defined throughout the driver files. */
बाह्य स्थिर काष्ठा address_space_operations ntfs_normal_aops;
बाह्य स्थिर काष्ठा address_space_operations ntfs_compressed_aops;
बाह्य स्थिर काष्ठा address_space_operations ntfs_mst_aops;

बाह्य स्थिर काष्ठा  file_operations ntfs_file_ops;
बाह्य स्थिर काष्ठा inode_operations ntfs_file_inode_ops;

बाह्य स्थिर काष्ठा  file_operations ntfs_dir_ops;
बाह्य स्थिर काष्ठा inode_operations ntfs_dir_inode_ops;

बाह्य स्थिर काष्ठा  file_operations ntfs_empty_file_ops;
बाह्य स्थिर काष्ठा inode_operations ntfs_empty_inode_ops;

बाह्य स्थिर काष्ठा export_operations ntfs_export_ops;

/**
 * NTFS_SB - वापस the ntfs volume given a vfs super block
 * @sb:		VFS super block
 *
 * NTFS_SB() वापसs the ntfs volume associated with the VFS super block @sb.
 */
अटल अंतरभूत ntfs_volume *NTFS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

/* Declarations of functions and global variables. */

/* From fs/ntfs/compress.c */
बाह्य पूर्णांक ntfs_पढ़ो_compressed_block(काष्ठा page *page);
बाह्य पूर्णांक allocate_compression_buffers(व्योम);
बाह्य व्योम मुक्त_compression_buffers(व्योम);

/* From fs/ntfs/super.c */
#घोषणा शेष_upहाल_len 0x10000
बाह्य काष्ठा mutex ntfs_lock;

प्रकार काष्ठा अणु
	पूर्णांक val;
	अक्षर *str;
पूर्ण option_t;
बाह्य स्थिर option_t on_errors_arr[];

/* From fs/ntfs/mst.c */
बाह्य पूर्णांक post_पढ़ो_mst_fixup(NTFS_RECORD *b, स्थिर u32 size);
बाह्य पूर्णांक pre_ग_लिखो_mst_fixup(NTFS_RECORD *b, स्थिर u32 size);
बाह्य व्योम post_ग_लिखो_mst_fixup(NTFS_RECORD *b);

/* From fs/ntfs/unistr.c */
बाह्य bool ntfs_are_names_equal(स्थिर ntfsअक्षर *s1, माप_प्रकार s1_len,
		स्थिर ntfsअक्षर *s2, माप_प्रकार s2_len,
		स्थिर IGNORE_CASE_BOOL ic,
		स्थिर ntfsअक्षर *upहाल, स्थिर u32 upहाल_size);
बाह्य पूर्णांक ntfs_collate_names(स्थिर ntfsअक्षर *name1, स्थिर u32 name1_len,
		स्थिर ntfsअक्षर *name2, स्थिर u32 name2_len,
		स्थिर पूर्णांक err_val, स्थिर IGNORE_CASE_BOOL ic,
		स्थिर ntfsअक्षर *upहाल, स्थिर u32 upहाल_len);
बाह्य पूर्णांक ntfs_ucsncmp(स्थिर ntfsअक्षर *s1, स्थिर ntfsअक्षर *s2, माप_प्रकार n);
बाह्य पूर्णांक ntfs_ucsnहालcmp(स्थिर ntfsअक्षर *s1, स्थिर ntfsअक्षर *s2, माप_प्रकार n,
		स्थिर ntfsअक्षर *upहाल, स्थिर u32 upहाल_size);
बाह्य व्योम ntfs_upहाल_name(ntfsअक्षर *name, u32 name_len,
		स्थिर ntfsअक्षर *upहाल, स्थिर u32 upहाल_len);
बाह्य व्योम ntfs_file_upहाल_value(खाता_NAME_ATTR *file_name_attr,
		स्थिर ntfsअक्षर *upहाल, स्थिर u32 upहाल_len);
बाह्य पूर्णांक ntfs_file_compare_values(खाता_NAME_ATTR *file_name_attr1,
		खाता_NAME_ATTR *file_name_attr2,
		स्थिर पूर्णांक err_val, स्थिर IGNORE_CASE_BOOL ic,
		स्थिर ntfsअक्षर *upहाल, स्थिर u32 upहाल_len);
बाह्य पूर्णांक ntfs_nlstoucs(स्थिर ntfs_volume *vol, स्थिर अक्षर *ins,
		स्थिर पूर्णांक ins_len, ntfsअक्षर **outs);
बाह्य पूर्णांक ntfs_ucstonls(स्थिर ntfs_volume *vol, स्थिर ntfsअक्षर *ins,
		स्थिर पूर्णांक ins_len, अचिन्हित अक्षर **outs, पूर्णांक outs_len);

/* From fs/ntfs/upहाल.c */
बाह्य ntfsअक्षर *generate_शेष_upहाल(व्योम);

अटल अंतरभूत पूर्णांक ntfs_ffs(पूर्णांक x)
अणु
	पूर्णांक r = 1;

	अगर (!x)
		वापस 0;
	अगर (!(x & 0xffff)) अणु
		x >>= 16;
		r += 16;
	पूर्ण
	अगर (!(x & 0xff)) अणु
		x >>= 8;
		r += 8;
	पूर्ण
	अगर (!(x & 0xf)) अणु
		x >>= 4;
		r += 4;
	पूर्ण
	अगर (!(x & 3)) अणु
		x >>= 2;
		r += 2;
	पूर्ण
	अगर (!(x & 1)) अणु
		x >>= 1;
		r += 1;
	पूर्ण
	वापस r;
पूर्ण

#पूर्ण_अगर /* _LINUX_NTFS_H */
