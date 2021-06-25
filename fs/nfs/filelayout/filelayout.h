<शैली गुरु>
/*
 *  NFSv4 file layout driver data काष्ठाures.
 *
 *  Copyright (c) 2002
 *  The Regents of the University of Michigan
 *  All Rights Reserved
 *
 *  Dean Hildebअक्रम <dhildebz@umich.edu>
 *
 *  Permission is granted to use, copy, create derivative works, and
 *  redistribute this software and such derivative works क्रम any purpose,
 *  so दीर्घ as the name of the University of Michigan is not used in
 *  any advertising or खुलाity pertaining to the use or distribution
 *  of this software without specअगरic, written prior authorization. If
 *  the above copyright notice or any other identअगरication of the
 *  University of Michigan is included in any copy of any portion of
 *  this software, then the disclaimer below must also be included.
 *
 *  This software is provided as is, without representation or warranty
 *  of any kind either express or implied, including without limitation
 *  the implied warranties of merchantability, fitness क्रम a particular
 *  purpose, or noninfringement.  The Regents of the University of
 *  Michigan shall not be liable क्रम any damages, including special,
 *  indirect, incidental, or consequential damages, with respect to any
 *  claim arising out of or in connection with the use of the software,
 *  even अगर it has been or is hereafter advised of the possibility of
 *  such damages.
 */

#अगर_अघोषित FS_NFS_NFS4खाताLAYOUT_H
#घोषणा FS_NFS_NFS4खाताLAYOUT_H

#समावेश "../pnfs.h"

/*
 * Field testing shows we need to support up to 4096 stripe indices.
 * We store each index as a u8 (u32 on the wire) to keep the memory footprपूर्णांक
 * reasonable. This in turn means we support a maximum of 256
 * RFC 5661 multipath_list4 काष्ठाures.
 */
#घोषणा NFS4_PNFS_MAX_STRIPE_CNT 4096
#घोषणा NFS4_PNFS_MAX_MULTI_CNT  256 /* 256 fit पूर्णांकo a u8 stripe_index */

क्रमागत stripetype4 अणु
	STRIPE_SPARSE = 1,
	STRIPE_DENSE = 2
पूर्ण;

काष्ठा nfs4_file_layout_dsaddr अणु
	काष्ठा nfs4_deviceid_node	id_node;
	u32				stripe_count;
	u8				*stripe_indices;
	u32				ds_num;
	काष्ठा nfs4_pnfs_ds		*ds_list[1];
पूर्ण;

काष्ठा nfs4_filelayout_segment अणु
	काष्ठा pnfs_layout_segment	generic_hdr;
	u32				stripe_type;
	u32				commit_through_mds;
	u32				stripe_unit;
	u32				first_stripe_index;
	u64				pattern_offset;
	काष्ठा nfs4_deviceid		deviceid;
	काष्ठा nfs4_file_layout_dsaddr	*dsaddr; /* Poपूर्णांक to GETDEVINFO data */
	अचिन्हित पूर्णांक			num_fh;
	काष्ठा nfs_fh			**fh_array;
पूर्ण;

काष्ठा nfs4_filelayout अणु
	काष्ठा pnfs_layout_hdr generic_hdr;
	काष्ठा pnfs_ds_commit_info commit_info;
पूर्ण;

अटल अंतरभूत काष्ठा nfs4_filelayout *
खाताLAYOUT_FROM_HDR(काष्ठा pnfs_layout_hdr *lo)
अणु
	वापस container_of(lo, काष्ठा nfs4_filelayout, generic_hdr);
पूर्ण

अटल अंतरभूत काष्ठा nfs4_filelayout_segment *
खाताLAYOUT_LSEG(काष्ठा pnfs_layout_segment *lseg)
अणु
	वापस container_of(lseg,
			    काष्ठा nfs4_filelayout_segment,
			    generic_hdr);
पूर्ण

अटल अंतरभूत काष्ठा nfs4_deviceid_node *
खाताLAYOUT_DEVID_NODE(काष्ठा pnfs_layout_segment *lseg)
अणु
	वापस &खाताLAYOUT_LSEG(lseg)->dsaddr->id_node;
पूर्ण

अटल अंतरभूत bool
filelayout_test_devid_invalid(काष्ठा nfs4_deviceid_node *node)
अणु
	वापस test_bit(NFS_DEVICEID_INVALID, &node->flags);
पूर्ण

बाह्य bool
filelayout_test_devid_unavailable(काष्ठा nfs4_deviceid_node *node);

बाह्य काष्ठा nfs_fh *
nfs4_fl_select_ds_fh(काष्ठा pnfs_layout_segment *lseg, u32 j);

u32 nfs4_fl_calc_j_index(काष्ठा pnfs_layout_segment *lseg, loff_t offset);
u32 nfs4_fl_calc_ds_index(काष्ठा pnfs_layout_segment *lseg, u32 j);
काष्ठा nfs4_pnfs_ds *nfs4_fl_prepare_ds(काष्ठा pnfs_layout_segment *lseg,
					u32 ds_idx);

बाह्य काष्ठा nfs4_file_layout_dsaddr *
nfs4_fl_alloc_deviceid_node(काष्ठा nfs_server *server,
	काष्ठा pnfs_device *pdev, gfp_t gfp_flags);
बाह्य व्योम nfs4_fl_put_deviceid(काष्ठा nfs4_file_layout_dsaddr *dsaddr);
बाह्य व्योम nfs4_fl_मुक्त_deviceid(काष्ठा nfs4_file_layout_dsaddr *dsaddr);

#पूर्ण_अगर /* FS_NFS_NFS4खाताLAYOUT_H */
