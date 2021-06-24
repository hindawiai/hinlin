<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008 Oracle.  All rights reserved.
 */

#अगर_अघोषित BTRFS_COMPRESSION_H
#घोषणा BTRFS_COMPRESSION_H

#समावेश <linux/sizes.h>

काष्ठा btrfs_inode;

/*
 * We want to make sure that amount of RAM required to uncompress an extent is
 * reasonable, so we limit the total size in ram of a compressed extent to
 * 128k.  This is a crucial number because it also controls how easily we can
 * spपढ़ो पढ़ोs across cpus क्रम decompression.
 *
 * We also want to make sure the amount of IO required to करो a अक्रमom पढ़ो is
 * reasonably small, so we limit the size of a compressed extent to 128k.
 */

/* Maximum length of compressed data stored on disk */
#घोषणा BTRFS_MAX_COMPRESSED		(SZ_128K)
/* Maximum size of data beक्रमe compression */
#घोषणा BTRFS_MAX_UNCOMPRESSED		(SZ_128K)

#घोषणा	BTRFS_ZLIB_DEFAULT_LEVEL		3

काष्ठा compressed_bio अणु
	/* number of bios pending क्रम this compressed extent */
	refcount_t pending_bios;

	/* the pages with the compressed data on them */
	काष्ठा page **compressed_pages;

	/* inode that owns this data */
	काष्ठा inode *inode;

	/* starting offset in the inode क्रम our pages */
	u64 start;

	/* number of bytes in the inode we're working on */
	अचिन्हित दीर्घ len;

	/* number of bytes on disk */
	अचिन्हित दीर्घ compressed_len;

	/* the compression algorithm क्रम this bio */
	पूर्णांक compress_type;

	/* number of compressed pages in the array */
	अचिन्हित दीर्घ nr_pages;

	/* IO errors */
	पूर्णांक errors;
	पूर्णांक mirror_num;

	/* क्रम पढ़ोs, this is the bio we are copying the data पूर्णांकo */
	काष्ठा bio *orig_bio;

	/*
	 * the start of a variable length array of checksums only
	 * used by पढ़ोs
	 */
	u8 sums[];
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक btrfs_compress_type(अचिन्हित पूर्णांक type_level)
अणु
	वापस (type_level & 0xF);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक btrfs_compress_level(अचिन्हित पूर्णांक type_level)
अणु
	वापस ((type_level & 0xF0) >> 4);
पूर्ण

व्योम __init btrfs_init_compress(व्योम);
व्योम __cold btrfs_निकास_compress(व्योम);

पूर्णांक btrfs_compress_pages(अचिन्हित पूर्णांक type_level, काष्ठा address_space *mapping,
			 u64 start, काष्ठा page **pages,
			 अचिन्हित दीर्घ *out_pages,
			 अचिन्हित दीर्घ *total_in,
			 अचिन्हित दीर्घ *total_out);
पूर्णांक btrfs_decompress(पूर्णांक type, अचिन्हित अक्षर *data_in, काष्ठा page *dest_page,
		     अचिन्हित दीर्घ start_byte, माप_प्रकार srclen, माप_प्रकार destlen);
पूर्णांक btrfs_decompress_buf2page(स्थिर अक्षर *buf, अचिन्हित दीर्घ buf_start,
			      अचिन्हित दीर्घ total_out, u64 disk_start,
			      काष्ठा bio *bio);

blk_status_t btrfs_submit_compressed_ग_लिखो(काष्ठा btrfs_inode *inode, u64 start,
				  अचिन्हित दीर्घ len, u64 disk_start,
				  अचिन्हित दीर्घ compressed_len,
				  काष्ठा page **compressed_pages,
				  अचिन्हित दीर्घ nr_pages,
				  अचिन्हित पूर्णांक ग_लिखो_flags,
				  काष्ठा cgroup_subsys_state *blkcg_css);
blk_status_t btrfs_submit_compressed_पढ़ो(काष्ठा inode *inode, काष्ठा bio *bio,
				 पूर्णांक mirror_num, अचिन्हित दीर्घ bio_flags);

अचिन्हित पूर्णांक btrfs_compress_str2level(अचिन्हित पूर्णांक type, स्थिर अक्षर *str);

क्रमागत btrfs_compression_type अणु
	BTRFS_COMPRESS_NONE  = 0,
	BTRFS_COMPRESS_ZLIB  = 1,
	BTRFS_COMPRESS_LZO   = 2,
	BTRFS_COMPRESS_ZSTD  = 3,
	BTRFS_NR_COMPRESS_TYPES = 4,
पूर्ण;

काष्ठा workspace_manager अणु
	काष्ठा list_head idle_ws;
	spinlock_t ws_lock;
	/* Number of मुक्त workspaces */
	पूर्णांक मुक्त_ws;
	/* Total number of allocated workspaces */
	atomic_t total_ws;
	/* Waiters क्रम a मुक्त workspace */
	रुको_queue_head_t ws_रुको;
पूर्ण;

काष्ठा list_head *btrfs_get_workspace(पूर्णांक type, अचिन्हित पूर्णांक level);
व्योम btrfs_put_workspace(पूर्णांक type, काष्ठा list_head *ws);

काष्ठा btrfs_compress_op अणु
	काष्ठा workspace_manager *workspace_manager;
	/* Maximum level supported by the compression algorithm */
	अचिन्हित पूर्णांक max_level;
	अचिन्हित पूर्णांक शेष_level;
पूर्ण;

/* The heuristic workspaces are managed via the 0th workspace manager */
#घोषणा BTRFS_NR_WORKSPACE_MANAGERS	BTRFS_NR_COMPRESS_TYPES

बाह्य स्थिर काष्ठा btrfs_compress_op btrfs_heuristic_compress;
बाह्य स्थिर काष्ठा btrfs_compress_op btrfs_zlib_compress;
बाह्य स्थिर काष्ठा btrfs_compress_op btrfs_lzo_compress;
बाह्य स्थिर काष्ठा btrfs_compress_op btrfs_zstd_compress;

स्थिर अक्षर* btrfs_compress_type2str(क्रमागत btrfs_compression_type type);
bool btrfs_compress_is_valid_type(स्थिर अक्षर *str, माप_प्रकार len);

पूर्णांक btrfs_compress_heuristic(काष्ठा inode *inode, u64 start, u64 end);

पूर्णांक zlib_compress_pages(काष्ठा list_head *ws, काष्ठा address_space *mapping,
		u64 start, काष्ठा page **pages, अचिन्हित दीर्घ *out_pages,
		अचिन्हित दीर्घ *total_in, अचिन्हित दीर्घ *total_out);
पूर्णांक zlib_decompress_bio(काष्ठा list_head *ws, काष्ठा compressed_bio *cb);
पूर्णांक zlib_decompress(काष्ठा list_head *ws, अचिन्हित अक्षर *data_in,
		काष्ठा page *dest_page, अचिन्हित दीर्घ start_byte, माप_प्रकार srclen,
		माप_प्रकार destlen);
काष्ठा list_head *zlib_alloc_workspace(अचिन्हित पूर्णांक level);
व्योम zlib_मुक्त_workspace(काष्ठा list_head *ws);
काष्ठा list_head *zlib_get_workspace(अचिन्हित पूर्णांक level);

पूर्णांक lzo_compress_pages(काष्ठा list_head *ws, काष्ठा address_space *mapping,
		u64 start, काष्ठा page **pages, अचिन्हित दीर्घ *out_pages,
		अचिन्हित दीर्घ *total_in, अचिन्हित दीर्घ *total_out);
पूर्णांक lzo_decompress_bio(काष्ठा list_head *ws, काष्ठा compressed_bio *cb);
पूर्णांक lzo_decompress(काष्ठा list_head *ws, अचिन्हित अक्षर *data_in,
		काष्ठा page *dest_page, अचिन्हित दीर्घ start_byte, माप_प्रकार srclen,
		माप_प्रकार destlen);
काष्ठा list_head *lzo_alloc_workspace(अचिन्हित पूर्णांक level);
व्योम lzo_मुक्त_workspace(काष्ठा list_head *ws);

पूर्णांक zstd_compress_pages(काष्ठा list_head *ws, काष्ठा address_space *mapping,
		u64 start, काष्ठा page **pages, अचिन्हित दीर्घ *out_pages,
		अचिन्हित दीर्घ *total_in, अचिन्हित दीर्घ *total_out);
पूर्णांक zstd_decompress_bio(काष्ठा list_head *ws, काष्ठा compressed_bio *cb);
पूर्णांक zstd_decompress(काष्ठा list_head *ws, अचिन्हित अक्षर *data_in,
		काष्ठा page *dest_page, अचिन्हित दीर्घ start_byte, माप_प्रकार srclen,
		माप_प्रकार destlen);
व्योम zstd_init_workspace_manager(व्योम);
व्योम zstd_cleanup_workspace_manager(व्योम);
काष्ठा list_head *zstd_alloc_workspace(अचिन्हित पूर्णांक level);
व्योम zstd_मुक्त_workspace(काष्ठा list_head *ws);
काष्ठा list_head *zstd_get_workspace(अचिन्हित पूर्णांक level);
व्योम zstd_put_workspace(काष्ठा list_head *ws);

#पूर्ण_अगर
