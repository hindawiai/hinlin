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
#अगर_अघोषित _VXFS_FSHEAD_H_
#घोषणा _VXFS_FSHEAD_H_

/*
 * Veritas fileप्रणाली driver - fileset header काष्ठाures.
 *
 * This file contains the physical काष्ठाure of the VxFS
 * fileset header.
 */


/*
 * Fileset header 
 */
काष्ठा vxfs_fsh अणु
	__fs32		fsh_version;		/* fileset header version */
	__fs32		fsh_fsindex;		/* fileset index */
	__fs32		fsh_समय;		/* modअगरication समय - sec */
	__fs32		fsh_uसमय;		/* modअगरication समय - usec */
	__fs32		fsh_extop;		/* extop flags */
	__fs32		fsh_ninodes;		/* allocated inodes */
	__fs32		fsh_nau;		/* number of IAUs */
	__fs32		fsh_old_ilesize;	/* old size of ilist */
	__fs32		fsh_dflags;		/* flags */
	__fs32		fsh_quota;		/* quota limit */
	__fs32		fsh_maxinode;		/* maximum inode number */
	__fs32		fsh_iauino;		/* IAU inode */
	__fs32		fsh_ilistino[2];	/* ilist inodes */
	__fs32		fsh_lctino;		/* link count table inode */

	/*
	 * Slightly more fields follow, but they
	 *  a) are not of any पूर्णांकerest क्रम us, and
	 *  b) dअगरfer a lot in dअगरferent vxfs versions/ports
	 */
पूर्ण;

#पूर्ण_अगर /* _VXFS_FSHEAD_H_ */
