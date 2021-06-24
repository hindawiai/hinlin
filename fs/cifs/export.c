<शैली गुरु>
/*
 *   fs/cअगरs/export.c
 *
 *   Copyright (C) International Business Machines  Corp., 2007
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 *   Common Internet FileSystem (CIFS) client
 *
 *   Operations related to support क्रम exporting files via NFSD
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

 /*
  * See Documentation/fileप्रणालीs/nfs/exporting.rst
  * and examples in fs/exportfs
  *
  * Since cअगरs is a network file प्रणाली, an "fsid" must be included क्रम
  * any nfs exports file entries which refer to cअगरs paths.  In addition
  * the cअगरs mount must be mounted with the "serverino" option (ie use stable
  * server inode numbers instead of locally generated temporary ones).
  * Although cअगरs inodes करो not use generation numbers (have generation number
  * of zero) - the inode number alone should be good enough क्रम simple हालs
  * in which users want to export cअगरs shares with NFS. The decode and encode
  * could be improved by using a new routine which expects 64 bit inode numbers
  * instead of the शेष 32 bit routines in fs/exportfs
  *
  */

#समावेश <linux/fs.h>
#समावेश <linux/exportfs.h>
#समावेश "cifsglob.h"
#समावेश "cifs_debug.h"
#समावेश "cifsfs.h"

#अगर_घोषित CONFIG_CIFS_NFSD_EXPORT
अटल काष्ठा dentry *cअगरs_get_parent(काष्ठा dentry *dentry)
अणु
	/* BB need to add code here eventually to enable export via NFSD */
	cअगरs_dbg(FYI, "get parent for %p\n", dentry);
	वापस ERR_PTR(-EACCES);
पूर्ण

स्थिर काष्ठा export_operations cअगरs_export_ops = अणु
	.get_parent = cअगरs_get_parent,
/*	Following five export operations are unneeded so far and can शेष:
	.get_dentry =
	.get_name =
	.find_exported_dentry =
	.decode_fh =
	.encode_fs =  */
पूर्ण;

#पूर्ण_अगर /* CONFIG_CIFS_NFSD_EXPORT */

