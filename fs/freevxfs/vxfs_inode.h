<शैली गुरु>
/*
 * Copyright (c) 2000-2001 Christoph Hellwig.
 * Copyright (c) 2016 Krzysztof Blaszkowski
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
#अगर_अघोषित _VXFS_INODE_H_
#घोषणा _VXFS_INODE_H_

/*
 * Veritas fileप्रणाली driver - inode काष्ठाure.
 *
 * This file contains the definition of the disk and core
 * inodes of the Veritas Fileप्रणाली.
 */


#घोषणा VXFS_ISIZE		0x100		/* Inode size */

#घोषणा VXFS_NDADDR		10		/* Number of direct addrs in inode */
#घोषणा VXFS_NIADDR		2		/* Number of indirect addrs in inode */
#घोषणा VXFS_NIMMED		96		/* Size of immediate data in inode */
#घोषणा VXFS_NTYPED		6		/* Num of typed extents */

#घोषणा VXFS_TYPED_OFFSETMASK	(0x00FFFFFFFFFFFFFFULL)
#घोषणा VXFS_TYPED_TYPEMASK	(0xFF00000000000000ULL)
#घोषणा VXFS_TYPED_TYPESHIFT	56

#घोषणा VXFS_TYPED_PER_BLOCK(sbp) \
	((sbp)->s_blocksize / माप(काष्ठा vxfs_typed))

/*
 * Possible extent descriptor types क्रम %VXFS_ORG_TYPED extents.
 */
क्रमागत अणु
	VXFS_TYPED_INसूचीECT		= 1,
	VXFS_TYPED_DATA			= 2,
	VXFS_TYPED_INसूचीECT_DEV4	= 3,
	VXFS_TYPED_DATA_DEV4		= 4,
पूर्ण;

/*
 * Data stored immediately in the inode.
 */
काष्ठा vxfs_immed अणु
	__u8			vi_immed[VXFS_NIMMED];
पूर्ण;

काष्ठा vxfs_ext4 अणु
	__fs32			ve4_spare;		/* ?? */
	__fs32			ve4_indsize;		/* Indirect extent size */
	__fs32			ve4_indir[VXFS_NIADDR];	/* Indirect extents */
	काष्ठा direct अणु					/* Direct extents */
		__fs32		extent;			/* Extent number */
		__fs32		size;			/* Size of extent */
	पूर्ण ve4_direct[VXFS_NDADDR];
पूर्ण;

काष्ठा vxfs_typed अणु
	__fs64		vt_hdr;		/* Header, 0xTTOOOOOOOOOOOOOO; T=type,O=offs */
	__fs32		vt_block;	/* Extent block */
	__fs32		vt_size;	/* Size in blocks */
पूर्ण;

काष्ठा vxfs_typed_dev4 अणु
	__fs64		vd4_hdr;	/* Header, 0xTTOOOOOOOOOOOOOO; T=type,O=offs */
	__fs64		vd4_block;	/* Extent block */
	__fs64		vd4_size;	/* Size in blocks */
	__fs32		vd4_dev;	/* Device ID */
	__u8		__pad1;
पूर्ण;

/*
 * The inode as contained on the physical device.
 */
काष्ठा vxfs_dinode अणु
	__fs32		vdi_mode;
	__fs32		vdi_nlink;	/* Link count */
	__fs32		vdi_uid;	/* UID */
	__fs32		vdi_gid;	/* GID */
	__fs64		vdi_size;	/* Inode size in bytes */
	__fs32		vdi_aसमय;	/* Last समय accessed - sec */
	__fs32		vdi_auसमय;	/* Last समय accessed - usec */
	__fs32		vdi_mसमय;	/* Last modअगरy समय - sec */
	__fs32		vdi_muसमय;	/* Last modअगरy समय - usec */
	__fs32		vdi_स_समय;	/* Create समय - sec */
	__fs32		vdi_cuसमय;	/* Create समय - usec */
	__u8		vdi_aflags;	/* Allocation flags */
	__u8		vdi_orgtype;	/* Organisation type */
	__fs16		vdi_eopflags;
	__fs32		vdi_eopdata;
	जोड़ अणु
		__fs32			rdev;
		__fs32			करोtकरोt;
		काष्ठा अणु
			__u32		reserved;
			__fs32		fixextsize;
		पूर्ण i_regular;
		काष्ठा अणु
			__fs32		matchino;
			__fs32		fsetindex;
		पूर्ण i_vxspec;
		__u64			align;
	पूर्ण vdi_ftarea;
	__fs32		vdi_blocks;	/* How much blocks करोes inode occupy */
	__fs32		vdi_gen;	/* Inode generation */
	__fs64		vdi_version;	/* Version */
	जोड़ अणु
		काष्ठा vxfs_immed	immed;
		काष्ठा vxfs_ext4	ext4;
		काष्ठा vxfs_typed	typed[VXFS_NTYPED];
	पूर्ण vdi_org;
	__fs32		vdi_iattrino;
पूर्ण;

#घोषणा vdi_rdev	vdi_ftarea.rdev
#घोषणा vdi_करोtकरोt	vdi_ftarea.करोtकरोt
#घोषणा vdi_fixextsize	vdi_ftarea.regular.fixextsize
#घोषणा vdi_matchino	vdi_ftarea.vxspec.matchino
#घोषणा vdi_fsetindex	vdi_ftarea.vxspec.fsetindex

#घोषणा vdi_immed	vdi_org.immed
#घोषणा vdi_ext4	vdi_org.ext4
#घोषणा vdi_typed	vdi_org.typed


/*
 * The inode as represented in the मुख्य memory.
 */
काष्ठा vxfs_inode_info अणु
	काष्ठा inode	vfs_inode;

	__u32		vii_mode;
	__u32		vii_nlink;	/* Link count */
	__u32		vii_uid;	/* UID */
	__u32		vii_gid;	/* GID */
	__u64		vii_size;	/* Inode size in bytes */
	__u32		vii_aसमय;	/* Last समय accessed - sec */
	__u32		vii_auसमय;	/* Last समय accessed - usec */
	__u32		vii_mसमय;	/* Last modअगरy समय - sec */
	__u32		vii_muसमय;	/* Last modअगरy समय - usec */
	__u32		vii_स_समय;	/* Create समय - sec */
	__u32		vii_cuसमय;	/* Create समय - usec */
	__u8		vii_orgtype;	/* Organisation type */
	जोड़ अणु
		__u32			rdev;
		__u32			करोtकरोt;
	पूर्ण vii_ftarea;
	__u32		vii_blocks;	/* How much blocks करोes inode occupy */
	__u32		vii_gen;	/* Inode generation */
	जोड़ अणु
		काष्ठा vxfs_immed	immed;
		काष्ठा vxfs_ext4	ext4;
		काष्ठा vxfs_typed	typed[VXFS_NTYPED];
	पूर्ण vii_org;
पूर्ण;

#घोषणा vii_rdev	vii_ftarea.rdev
#घोषणा vii_करोtकरोt	vii_ftarea.करोtकरोt

#घोषणा vii_immed	vii_org.immed
#घोषणा vii_ext4	vii_org.ext4
#घोषणा vii_typed	vii_org.typed

अटल अंतरभूत काष्ठा vxfs_inode_info *VXFS_INO(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा vxfs_inode_info, vfs_inode);
पूर्ण

#पूर्ण_अगर /* _VXFS_INODE_H_ */
