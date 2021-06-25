<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ocfs1_fs_compat.h
 *
 * OCFS1 volume header definitions.  OCFS2 creates valid but unmountable
 * OCFS1 volume headers on the first two sectors of an OCFS2 volume.
 * This allows an OCFS1 volume to see the partition and cleanly fail to
 * mount it.
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित _OCFS1_FS_COMPAT_H
#घोषणा _OCFS1_FS_COMPAT_H

#घोषणा OCFS1_MAX_VOL_SIGNATURE_LEN          128
#घोषणा OCFS1_MAX_MOUNT_POINT_LEN            128
#घोषणा OCFS1_MAX_VOL_ID_LENGTH               16
#घोषणा OCFS1_MAX_VOL_LABEL_LEN               64
#घोषणा OCFS1_MAX_CLUSTER_NAME_LEN            64

#घोषणा OCFS1_MAJOR_VERSION              (2)
#घोषणा OCFS1_MINOR_VERSION              (0)
#घोषणा OCFS1_VOLUME_SIGNATURE		 "OracleCFS"

/*
 * OCFS1 superblock.  Lives at sector 0.
 */
काष्ठा ocfs1_vol_disk_hdr
अणु
/*00*/	__u32 minor_version;
	__u32 major_version;
/*08*/	__u8 signature[OCFS1_MAX_VOL_SIGNATURE_LEN];
/*88*/	__u8 mount_poपूर्णांक[OCFS1_MAX_MOUNT_POINT_LEN];
/*108*/	__u64 serial_num;
/*110*/	__u64 device_size;
	__u64 start_off;
/*120*/	__u64 biपंचांगap_off;
	__u64 publ_off;
/*130*/	__u64 vote_off;
	__u64 root_biपंचांगap_off;
/*140*/	__u64 data_start_off;
	__u64 root_biपंचांगap_size;
/*150*/	__u64 root_off;
	__u64 root_size;
/*160*/	__u64 cluster_size;
	__u64 num_nodes;
/*170*/	__u64 num_clusters;
	__u64 dir_node_size;
/*180*/	__u64 file_node_size;
	__u64 पूर्णांकernal_off;
/*190*/	__u64 node_cfg_off;
	__u64 node_cfg_size;
/*1A0*/	__u64 new_cfg_off;
	__u32 prot_bits;
	__s32 excl_mount;
/*1B0*/
पूर्ण;


काष्ठा ocfs1_disk_lock
अणु
/*00*/	__u32 curr_master;
	__u8 file_lock;
	__u8 compat_pad[3];  /* Not in original definition.  Used to
				make the alपढ़ोy existing alignment
				explicit */
	__u64 last_ग_लिखो_समय;
/*10*/	__u64 last_पढ़ो_समय;
	__u32 ग_लिखोr_node_num;
	__u32 पढ़ोer_node_num;
/*20*/	__u64 oin_node_map;
	__u64 dlock_seq_num;
/*30*/
पूर्ण;

/*
 * OCFS1 volume label.  Lives at sector 1.
 */
काष्ठा ocfs1_vol_label
अणु
/*00*/	काष्ठा ocfs1_disk_lock disk_lock;
/*30*/	__u8 label[OCFS1_MAX_VOL_LABEL_LEN];
/*70*/	__u16 label_len;
/*72*/	__u8 vol_id[OCFS1_MAX_VOL_ID_LENGTH];
/*82*/	__u16 vol_id_len;
/*84*/	__u8 cluster_name[OCFS1_MAX_CLUSTER_NAME_LEN];
/*A4*/	__u16 cluster_name_len;
/*A6*/
पूर्ण;


#पूर्ण_अगर /* _OCFS1_FS_COMPAT_H */

