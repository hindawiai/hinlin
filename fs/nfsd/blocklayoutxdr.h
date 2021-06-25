<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NFSD_BLOCKLAYOUTXDR_H
#घोषणा _NFSD_BLOCKLAYOUTXDR_H 1

#समावेश <linux/blkdev.h>
#समावेश "xdr4.h"

काष्ठा iomap;
काष्ठा xdr_stream;

काष्ठा pnfs_block_extent अणु
	काष्ठा nfsd4_deviceid		vol_id;
	u64				foff;
	u64				len;
	u64				soff;
	क्रमागत pnfs_block_extent_state	es;
पूर्ण;

काष्ठा pnfs_block_range अणु
	u64				foff;
	u64				len;
पूर्ण;

/*
 * Ranकरोm upper cap क्रम the uuid length to aव्योम unbounded allocation.
 * Not actually limited by the protocol.
 */
#घोषणा PNFS_BLOCK_UUID_LEN	128

काष्ठा pnfs_block_volume अणु
	क्रमागत pnfs_block_volume_type	type;
	जोड़ अणु
		काष्ठा अणु
			u64		offset;
			u32		sig_len;
			u8		sig[PNFS_BLOCK_UUID_LEN];
		पूर्ण simple;
		काष्ठा अणु
			क्रमागत scsi_code_set		code_set;
			क्रमागत scsi_designator_type	designator_type;
			पूर्णांक				designator_len;
			u8				designator[256];
			u64				pr_key;
		पूर्ण scsi;
	पूर्ण;
पूर्ण;

काष्ठा pnfs_block_deviceaddr अणु
	u32				nr_volumes;
	काष्ठा pnfs_block_volume	volumes[];
पूर्ण;

__be32 nfsd4_block_encode_getdeviceinfo(काष्ठा xdr_stream *xdr,
		काष्ठा nfsd4_getdeviceinfo *gdp);
__be32 nfsd4_block_encode_layoutget(काष्ठा xdr_stream *xdr,
		काष्ठा nfsd4_layoutget *lgp);
पूर्णांक nfsd4_block_decode_layoutupdate(__be32 *p, u32 len, काष्ठा iomap **iomapp,
		u32 block_size);
पूर्णांक nfsd4_scsi_decode_layoutupdate(__be32 *p, u32 len, काष्ठा iomap **iomapp,
		u32 block_size);

#पूर्ण_अगर /* _NFSD_BLOCKLAYOUTXDR_H */
