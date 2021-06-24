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
#अगर_अघोषित _VXFS_सूची_H_
#घोषणा _VXFS_सूची_H_

/*
 * Veritas fileप्रणाली driver - directory काष्ठाure.
 *
 * This file contains the definition of the vxfs directory क्रमmat.
 */


/*
 * VxFS directory block header.
 *
 * This entry is the head of every fileप्रणाली block in a directory.
 * It is used क्रम मुक्त space management and additionally includes
 * a hash क्रम speeding up directory search (lookup).
 *
 * The hash may be empty and in fact we करो not use it all in the
 * Linux driver क्रम now.
 */
काष्ठा vxfs_dirblk अणु
	__fs16		d_मुक्त;		/* मुक्त space in dirblock */
	__fs16		d_nhash;	/* no of hash chains */
	__fs16		d_hash[1];	/* hash chain */
पूर्ण;

/*
 * VXFS_NAMELEN is the maximum length of the d_name field
 *	of an VxFS directory entry.
 */
#घोषणा VXFS_NAMELEN	256

/*
 * VxFS directory entry.
 */
काष्ठा vxfs_direct अणु
	__fs32		d_ino;			/* inode number */
	__fs16		d_reclen;		/* record length */
	__fs16		d_namelen;		/* d_name length */
	__fs16		d_hashnext;		/* next hash entry */
	अक्षर		d_name[VXFS_NAMELEN];	/* name */
पूर्ण;

/*
 * VXFS_सूचीPAD defines the directory entry boundaries, is _must_ be
 *	a multiple of four.
 * VXFS_NAMEMIN is the length of a directory entry with a शून्य d_name.
 * VXFS_सूचीROUND is an पूर्णांकernal macros that rounds a length to a value
 *	usable क्रम directory sizes.
 * VXFS_सूचीLEN calculates the directory entry size क्रम an entry with
 *	a d_name with size len.
 */
#घोषणा VXFS_सूचीPAD		4
#घोषणा VXFS_NAMEMIN		दुरत्व(काष्ठा vxfs_direct, d_name)
#घोषणा VXFS_सूचीROUND(len)	((VXFS_सूचीPAD + (len) - 1) & ~(VXFS_सूचीPAD -1))
#घोषणा VXFS_सूचीLEN(len)	(VXFS_सूचीROUND(VXFS_NAMEMIN + (len)))

/*
 * VXFS_सूचीBLKOV is the overhead of a specअगरic dirblock.
 */
#घोषणा VXFS_सूचीBLKOV(sbi, dbp)	\
	((माप(लघु) * fs16_to_cpu(sbi, dbp->d_nhash)) + 4)

#पूर्ण_अगर /* _VXFS_सूची_H_ */
