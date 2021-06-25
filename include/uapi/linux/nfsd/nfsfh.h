<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file describes the layout of the file handles as passed
 * over the wire.
 *
 * Copyright (C) 1995, 1996, 1997 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित _UAPI_LINUX_NFSD_FH_H
#घोषणा _UAPI_LINUX_NFSD_FH_H

#समावेश <linux/types.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs2.h>
#समावेश <linux/nfs3.h>
#समावेश <linux/nfs4.h>

/*
 * This is the old "dentry style" Linux NFSv2 file handle.
 *
 * The xino and xdev fields are currently used to transport the
 * ino/dev of the exported inode.
 */
काष्ठा nfs_fhbase_old अणु
	__u32		fb_dcookie;	/* dentry cookie - always 0xfeebbaca */
	__u32		fb_ino;		/* our inode number */
	__u32		fb_dirino;	/* dir inode number, 0 क्रम directories */
	__u32		fb_dev;		/* our device */
	__u32		fb_xdev;
	__u32		fb_xino;
	__u32		fb_generation;
पूर्ण;

/*
 * This is the new flexible, extensible style NFSv2/v3/v4 file handle.
 * by Neil Brown <neilb@cse.unsw.edu.au> - March 2000
 *
 * The file handle starts with a sequence of four-byte words.
 * The first word contains a version number (1) and three descriptor bytes
 * that tell how the reमुख्यing 3 variable length fields should be handled.
 * These three bytes are auth_type, fsid_type and fileid_type.
 *
 * All four-byte values are in host-byte-order.
 *
 * The auth_type field is deprecated and must be set to 0.
 *
 * The fsid_type identअगरies how the fileप्रणाली (or export poपूर्णांक) is
 *    encoded.
 *  Current values:
 *     0  - 4 byte device id (ms-2-bytes major, ls-2-bytes minor), 4byte inode number
 *        NOTE: we cannot use the kdev_t device id value, because kdev_t.h
 *              says we mustn't.  We must अवरोध it up and reassemble.
 *     1  - 4 byte user specअगरied identअगरier
 *     2  - 4 byte major, 4 byte minor, 4 byte inode number - DEPRECATED
 *     3  - 4 byte device id, encoded क्रम user-space, 4 byte inode number
 *     4  - 4 byte inode number and 4 byte uuid
 *     5  - 8 byte uuid
 *     6  - 16 byte uuid
 *     7  - 8 byte inode number and 16 byte uuid
 *
 * The fileid_type identअगरied how the file within the fileप्रणाली is encoded.
 *   The values क्रम this field are fileप्रणाली specअगरic, exccept that
 *   fileप्रणालीs must not use the values '0' or '0xff'. 'See enum fid_type'
 *   in include/linux/exportfs.h क्रम currently रेजिस्टरed values.
 */
काष्ठा nfs_fhbase_new अणु
	जोड़ अणु
		काष्ठा अणु
			__u8		fb_version_aux;	/* == 1, even => nfs_fhbase_old */
			__u8		fb_auth_type_aux;
			__u8		fb_fsid_type_aux;
			__u8		fb_fileid_type_aux;
			__u32		fb_auth[1];
			/*	__u32		fb_fsid[0]; भग्नing */
			/*	__u32		fb_fileid[0]; भग्नing */
		पूर्ण;
		काष्ठा अणु
			__u8		fb_version;	/* == 1, even => nfs_fhbase_old */
			__u8		fb_auth_type;
			__u8		fb_fsid_type;
			__u8		fb_fileid_type;
			__u32		fb_auth_flex[]; /* flexible-array member */
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा knfsd_fh अणु
	अचिन्हित पूर्णांक	fh_size;	/* signअगरicant क्रम NFSv3.
					 * Poपूर्णांकs to the current size जबतक building
					 * a new file handle
					 */
	जोड़ अणु
		काष्ठा nfs_fhbase_old	fh_old;
		__u32			fh_pad[NFS4_FHSIZE/4];
		काष्ठा nfs_fhbase_new	fh_new;
	पूर्ण fh_base;
पूर्ण;

#घोषणा ofh_dcookie		fh_base.fh_old.fb_dcookie
#घोषणा ofh_ino			fh_base.fh_old.fb_ino
#घोषणा ofh_dirino		fh_base.fh_old.fb_dirino
#घोषणा ofh_dev			fh_base.fh_old.fb_dev
#घोषणा ofh_xdev		fh_base.fh_old.fb_xdev
#घोषणा ofh_xino		fh_base.fh_old.fb_xino
#घोषणा ofh_generation		fh_base.fh_old.fb_generation

#घोषणा	fh_version		fh_base.fh_new.fb_version
#घोषणा	fh_fsid_type		fh_base.fh_new.fb_fsid_type
#घोषणा	fh_auth_type		fh_base.fh_new.fb_auth_type
#घोषणा	fh_fileid_type		fh_base.fh_new.fb_fileid_type
#घोषणा	fh_fsid			fh_base.fh_new.fb_auth_flex

/* Do not use, provided क्रम userspace compatiblity. */
#घोषणा	fh_auth			fh_base.fh_new.fb_auth

#पूर्ण_अगर /* _UAPI_LINUX_NFSD_FH_H */
