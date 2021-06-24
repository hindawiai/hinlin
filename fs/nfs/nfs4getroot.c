<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
* Copyright (C) 2006 Red Hat, Inc. All Rights Reserved.
* Written by David Howells (dhowells@redhat.com)
*/

#समावेश <linux/nfs_fs.h>
#समावेश "nfs4_fs.h"
#समावेश "internal.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_CLIENT

पूर्णांक nfs4_get_rootfh(काष्ठा nfs_server *server, काष्ठा nfs_fh *mntfh, bool auth_probe)
अणु
	काष्ठा nfs_fsinfo fsinfo;
	पूर्णांक ret = -ENOMEM;

	fsinfo.fattr = nfs_alloc_fattr();
	अगर (fsinfo.fattr == शून्य)
		जाओ out;

	/* Start by getting the root filehandle from the server */
	ret = nfs4_proc_get_rootfh(server, mntfh, &fsinfo, auth_probe);
	अगर (ret < 0) अणु
		dprपूर्णांकk("nfs4_get_rootfh: getroot error = %d\n", -ret);
		जाओ out;
	पूर्ण

	अगर (!(fsinfo.fattr->valid & NFS_ATTR_FATTR_TYPE)
			|| !S_ISसूची(fsinfo.fattr->mode)) अणु
		prपूर्णांकk(KERN_ERR "nfs4_get_rootfh:"
		       " getroot encountered non-directory\n");
		ret = -ENOTसूची;
		जाओ out;
	पूर्ण

	स_नकल(&server->fsid, &fsinfo.fattr->fsid, माप(server->fsid));
out:
	nfs_मुक्त_fattr(fsinfo.fattr);
	वापस ret;
पूर्ण
