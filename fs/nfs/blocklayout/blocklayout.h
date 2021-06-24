<शैली गुरु>
/*
 *  linux/fs/nfs/blocklayout/blocklayout.h
 *
 *  Module क्रम the NFSv4.1 pNFS block layout driver.
 *
 *  Copyright (c) 2006 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Andy Adamson <andros@citi.umich.edu>
 *  Fred Isaman <iisaman@umich.edu>
 *
 * permission is granted to use, copy, create derivative works and
 * redistribute this software and such derivative works क्रम any purpose,
 * so दीर्घ as the name of the university of michigan is not used in
 * any advertising or खुलाity pertaining to the use or distribution
 * of this software without specअगरic, written prior authorization.  अगर
 * the above copyright notice or any other identअगरication of the
 * university of michigan is included in any copy of any portion of
 * this software, then the disclaimer below must also be included.
 *
 * this software is provided as is, without representation from the
 * university of michigan as to its fitness क्रम any purpose, and without
 * warranty by the university of michigan of any kind, either express
 * or implied, including without limitation the implied warranties of
 * merchantability and fitness क्रम a particular purpose.  the regents
 * of the university of michigan shall not be liable क्रम any damages,
 * including special, indirect, incidental, or consequential damages,
 * with respect to any claim arising out or in connection with the use
 * of the software, even अगर it has been or is hereafter advised of the
 * possibility of such damages.
 */
#अगर_अघोषित FS_NFS_NFS4BLOCKLAYOUT_H
#घोषणा FS_NFS_NFS4BLOCKLAYOUT_H

#समावेश <linux/device-mapper.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>

#समावेश "../nfs4_fs.h"
#समावेश "../pnfs.h"
#समावेश "../netns.h"

#घोषणा PAGE_CACHE_SECTORS (PAGE_SIZE >> SECTOR_SHIFT)
#घोषणा PAGE_CACHE_SECTOR_SHIFT (PAGE_SHIFT - SECTOR_SHIFT)
#घोषणा SECTOR_SIZE (1 << SECTOR_SHIFT)

काष्ठा pnfs_block_dev;

#घोषणा PNFS_BLOCK_MAX_UUIDS	4
#घोषणा PNFS_BLOCK_MAX_DEVICES	64

/*
 * Ranकरोm upper cap क्रम the uuid length to aव्योम unbounded allocation.
 * Not actually limited by the protocol.
 */
#घोषणा PNFS_BLOCK_UUID_LEN	128

काष्ठा pnfs_block_volume अणु
	क्रमागत pnfs_block_volume_type	type;
	जोड़ अणु
		काष्ठा अणु
			पूर्णांक		len;
			पूर्णांक		nr_sigs;
			काष्ठा अणु
				u64		offset;
				u32		sig_len;
				u8		sig[PNFS_BLOCK_UUID_LEN];
			पूर्ण sigs[PNFS_BLOCK_MAX_UUIDS];
		पूर्ण simple;
		काष्ठा अणु
			u64		start;
			u64		len;
			u32		volume;
		पूर्ण slice;
		काष्ठा अणु
			u32		volumes_count;
			u32		volumes[PNFS_BLOCK_MAX_DEVICES];
		पूर्ण concat;
		काष्ठा अणु
			u64		chunk_size;
			u32		volumes_count;
			u32		volumes[PNFS_BLOCK_MAX_DEVICES];
		पूर्ण stripe;
		काष्ठा अणु
			क्रमागत scsi_code_set		code_set;
			क्रमागत scsi_designator_type	designator_type;
			पूर्णांक				designator_len;
			u8				designator[256];
			u64				pr_key;
		पूर्ण scsi;
	पूर्ण;
पूर्ण;

काष्ठा pnfs_block_dev_map अणु
	u64			start;
	u64			len;
	u64			disk_offset;
	काष्ठा block_device		*bdev;
पूर्ण;

काष्ठा pnfs_block_dev अणु
	काष्ठा nfs4_deviceid_node	node;

	u64				start;
	u64				len;

	u32				nr_children;
	काष्ठा pnfs_block_dev		*children;
	u64				chunk_size;

	काष्ठा block_device		*bdev;
	u64				disk_offset;

	u64				pr_key;
	bool				pr_रेजिस्टरed;

	bool (*map)(काष्ठा pnfs_block_dev *dev, u64 offset,
			काष्ठा pnfs_block_dev_map *map);
पूर्ण;

/* sector_t fields are all in 512-byte sectors */
काष्ठा pnfs_block_extent अणु
	जोड़ अणु
		काष्ठा rb_node	be_node;
		काष्ठा list_head be_list;
	पूर्ण;
	काष्ठा nfs4_deviceid_node *be_device;
	sector_t	be_f_offset;	/* the starting offset in the file */
	sector_t	be_length;	/* the size of the extent */
	sector_t	be_v_offset;	/* the starting offset in the volume */
	क्रमागत pnfs_block_extent_state be_state;	/* the state of this extent */
#घोषणा EXTENT_WRITTEN		1
#घोषणा EXTENT_COMMITTING	2
	अचिन्हित पूर्णांक	be_tag;
पूर्ण;

काष्ठा pnfs_block_layout अणु
	काष्ठा pnfs_layout_hdr	bl_layout;
	काष्ठा rb_root		bl_ext_rw;
	काष्ठा rb_root		bl_ext_ro;
	spinlock_t		bl_ext_lock;   /* Protects list manipulation */
	bool			bl_scsi_layout;
	u64			bl_lwb;
पूर्ण;

अटल अंतरभूत काष्ठा pnfs_block_layout *
BLK_LO2EXT(काष्ठा pnfs_layout_hdr *lo)
अणु
	वापस container_of(lo, काष्ठा pnfs_block_layout, bl_layout);
पूर्ण

अटल अंतरभूत काष्ठा pnfs_block_layout *
BLK_LSEG2EXT(काष्ठा pnfs_layout_segment *lseg)
अणु
	वापस BLK_LO2EXT(lseg->pls_layout);
पूर्ण

काष्ठा bl_pipe_msg अणु
	काष्ठा rpc_pipe_msg msg;
	रुको_queue_head_t *bl_wq;
पूर्ण;

काष्ठा bl_msg_hdr अणु
	u8  type;
	u16 totallen; /* length of entire message, including hdr itself */
पूर्ण;

#घोषणा BL_DEVICE_UMOUNT               0x0 /* Umount--delete devices */
#घोषणा BL_DEVICE_MOUNT                0x1 /* Mount--create devices*/
#घोषणा BL_DEVICE_REQUEST_INIT         0x0 /* Start request */
#घोषणा BL_DEVICE_REQUEST_PROC         0x1 /* User level process succeeds */
#घोषणा BL_DEVICE_REQUEST_ERR          0x2 /* User level process fails */

/* dev.c */
काष्ठा nfs4_deviceid_node *bl_alloc_deviceid_node(काष्ठा nfs_server *server,
		काष्ठा pnfs_device *pdev, gfp_t gfp_mask);
व्योम bl_मुक्त_deviceid_node(काष्ठा nfs4_deviceid_node *d);

/* extent_tree.c */
पूर्णांक ext_tree_insert(काष्ठा pnfs_block_layout *bl,
		काष्ठा pnfs_block_extent *new);
पूर्णांक ext_tree_हटाओ(काष्ठा pnfs_block_layout *bl, bool rw, sector_t start,
		sector_t end);
पूर्णांक ext_tree_mark_written(काष्ठा pnfs_block_layout *bl, sector_t start,
		sector_t len, u64 lwb);
bool ext_tree_lookup(काष्ठा pnfs_block_layout *bl, sector_t isect,
		काष्ठा pnfs_block_extent *ret, bool rw);
पूर्णांक ext_tree_prepare_commit(काष्ठा nfs4_layoutcommit_args *arg);
व्योम ext_tree_mark_committed(काष्ठा nfs4_layoutcommit_args *arg, पूर्णांक status);

/* rpc_pipefs.c */
dev_t bl_resolve_deviceid(काष्ठा nfs_server *server,
		काष्ठा pnfs_block_volume *b, gfp_t gfp_mask);
पूर्णांक __init bl_init_pipefs(व्योम);
व्योम bl_cleanup_pipefs(व्योम);

#पूर्ण_अगर /* FS_NFS_NFS4BLOCKLAYOUT_H */
