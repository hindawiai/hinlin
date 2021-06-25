<शैली गुरु>
/*
 * Copyright (c) 2000-2001 Christoph Hellwig.
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
#अगर_अघोषित _VXFS_OLT_H_
#घोषणा _VXFS_OLT_H_

/*
 * Veritas fileप्रणाली driver - Object Location Table data काष्ठाures.
 *
 * This file contains definitions क्रम the Object Location Table used
 * by the Veritas Fileप्रणाली version 2 and newer.
 */


/*
 * OLT magic number (vxfs_olt->olt_magic).
 */
#घोषणा VXFS_OLT_MAGIC		0xa504FCF5

/*
 * VxFS OLT entry types.
 */
क्रमागत अणु
	VXFS_OLT_FREE	= 1,
	VXFS_OLT_FSHEAD	= 2,
	VXFS_OLT_CUT	= 3,
	VXFS_OLT_ILIST	= 4,
	VXFS_OLT_DEV	= 5,
	VXFS_OLT_SB	= 6
पूर्ण;

/*
 * VxFS OLT header.
 *
 * The Object Location Table header is placed at the beginning of each
 * OLT extent.  It is used to fing certain fileप्रणाली-wide metadata, e.g.
 * the initial inode list, the fileset header or the device configuration.
 */
काष्ठा vxfs_olt अणु
	__fs32		olt_magic;	/* magic number			*/
	__fs32		olt_size;	/* size of this entry		*/
	__fs32		olt_checksum;	/* checksum of extent		*/
	__u32		__unused1;	/* ???				*/
	__fs32		olt_mसमय;	/* समय of last mod. (sec)	*/
	__fs32		olt_muसमय;	/* समय of last mod. (usec)	*/
	__fs32		olt_totमुक्त;	/* मुक्त space in OLT extent	*/
	__fs32		olt_extents[2];	/* addr of this extent, replica	*/
	__fs32		olt_esize;	/* size of this extent		*/
	__fs32		olt_next[2];    /* addr of next extent, replica	*/
	__fs32		olt_nsize;	/* size of next extent		*/
	__u32		__unused2;	/* align to 8 byte boundary	*/
पूर्ण;

/*
 * VxFS common OLT entry (on disk).
 */
काष्ठा vxfs_oltcommon अणु
	__fs32		olt_type;	/* type of this record		*/
	__fs32		olt_size;	/* size of this record		*/
पूर्ण;

/*
 * VxFS मुक्त OLT entry (on disk).
 */
काष्ठा vxfs_oltमुक्त अणु
	__fs32		olt_type;	/* type of this record		*/
	__fs32		olt_fsize;	/* size of this मुक्त record	*/
पूर्ण;

/*
 * VxFS initial-inode list (on disk).
 */
काष्ठा vxfs_oltilist अणु
	__fs32	olt_type;	/* type of this record		*/
	__fs32	olt_size;	/* size of this record		*/
	__fs32		olt_iext[2];	/* initial inode list, replica	*/
पूर्ण;

/*
 * Current Usage Table 
 */
काष्ठा vxfs_oltcut अणु
	__fs32		olt_type;	/* type of this record		*/
	__fs32		olt_size;	/* size of this record		*/
	__fs32		olt_cutino;	/* inode of current usage table	*/
	__u8		__pad;		/* unused, 8 byte align		*/
पूर्ण;

/*
 * Inodes containing Superblock, Intent log and OLTs 
 */
काष्ठा vxfs_oltsb अणु
	__fs32		olt_type;	/* type of this record		*/
	__fs32		olt_size;	/* size of this record		*/
	__fs32		olt_sbino;	/* inode of superblock file	*/
	__u32		__unused1;	/* ???				*/
	__fs32		olt_logino[2];	/* inode of log file,replica	*/
	__fs32		olt_oltino[2];	/* inode of OLT, replica	*/
पूर्ण;

/*
 * Inode containing device configuration + it's replica 
 */
काष्ठा vxfs_oltdev अणु
	__fs32		olt_type;	/* type of this record		*/
	__fs32		olt_size;	/* size of this record		*/
	__fs32		olt_devino[2];	/* inode of device config files	*/
पूर्ण;

/*
 * Fileset header 
 */
काष्ठा vxfs_oltfshead अणु
	__fs32		olt_type;	/* type number			*/
	__fs32		olt_size;	/* size of this record		*/
	__fs32		olt_fsino[2];   /* inodes of fileset header	*/
पूर्ण;

#पूर्ण_अगर /* _VXFS_OLT_H_ */
