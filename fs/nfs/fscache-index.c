<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* NFS FS-Cache index काष्ठाure definition
 *
 * Copyright (C) 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_fs_sb.h>
#समावेश <linux/in6.h>
#समावेश <linux/iversion.h>

#समावेश "internal.h"
#समावेश "fscache.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_FSCACHE

/*
 * Define the NFS fileप्रणाली क्रम FS-Cache.  Upon registration FS-Cache sticks
 * the cookie क्रम the top-level index object क्रम NFS पूर्णांकo here.  The top-level
 * index can than have other cache objects inserted पूर्णांकo it.
 */
काष्ठा fscache_netfs nfs_fscache_netfs = अणु
	.name		= "nfs",
	.version	= 0,
पूर्ण;

/*
 * Register NFS क्रम caching
 */
पूर्णांक nfs_fscache_रेजिस्टर(व्योम)
अणु
	वापस fscache_रेजिस्टर_netfs(&nfs_fscache_netfs);
पूर्ण

/*
 * Unरेजिस्टर NFS क्रम caching
 */
व्योम nfs_fscache_unरेजिस्टर(व्योम)
अणु
	fscache_unरेजिस्टर_netfs(&nfs_fscache_netfs);
पूर्ण

/*
 * Define the server object क्रम FS-Cache.  This is used to describe a server
 * object to fscache_acquire_cookie().  It is keyed by the NFS protocol and
 * server address parameters.
 */
स्थिर काष्ठा fscache_cookie_def nfs_fscache_server_index_def = अणु
	.name		= "NFS.server",
	.type 		= FSCACHE_COOKIE_TYPE_INDEX,
पूर्ण;

/*
 * Define the superblock object क्रम FS-Cache.  This is used to describe a
 * superblock object to fscache_acquire_cookie().  It is keyed by all the NFS
 * parameters that might cause a separate superblock.
 */
स्थिर काष्ठा fscache_cookie_def nfs_fscache_super_index_def = अणु
	.name		= "NFS.super",
	.type 		= FSCACHE_COOKIE_TYPE_INDEX,
पूर्ण;

/*
 * Consult the netfs about the state of an object
 * - This function can be असलent अगर the index carries no state data
 * - The netfs data from the cookie being used as the target is
 *   presented, as is the auxiliary data
 */
अटल
क्रमागत fscache_checkaux nfs_fscache_inode_check_aux(व्योम *cookie_netfs_data,
						  स्थिर व्योम *data,
						  uपूर्णांक16_t datalen,
						  loff_t object_size)
अणु
	काष्ठा nfs_fscache_inode_auxdata auxdata;
	काष्ठा nfs_inode *nfsi = cookie_netfs_data;

	अगर (datalen != माप(auxdata))
		वापस FSCACHE_CHECKAUX_OBSOLETE;

	स_रखो(&auxdata, 0, माप(auxdata));
	auxdata.mसमय_sec  = nfsi->vfs_inode.i_mसमय.tv_sec;
	auxdata.mसमय_nsec = nfsi->vfs_inode.i_mसमय.tv_nsec;
	auxdata.स_समय_sec  = nfsi->vfs_inode.i_स_समय.tv_sec;
	auxdata.स_समय_nsec = nfsi->vfs_inode.i_स_समय.tv_nsec;

	अगर (NFS_SERVER(&nfsi->vfs_inode)->nfs_client->rpc_ops->version == 4)
		auxdata.change_attr = inode_peek_iversion_raw(&nfsi->vfs_inode);

	अगर (स_भेद(data, &auxdata, datalen) != 0)
		वापस FSCACHE_CHECKAUX_OBSOLETE;

	वापस FSCACHE_CHECKAUX_OKAY;
पूर्ण

/*
 * Get an extra reference on a पढ़ो context.
 * - This function can be असलent अगर the completion function करोesn't require a
 *   context.
 * - The पढ़ो context is passed back to NFS in the event that a data पढ़ो on the
 *   cache fails with EIO - in which हाल the server must be contacted to
 *   retrieve the data, which requires the पढ़ो context क्रम security.
 */
अटल व्योम nfs_fh_get_context(व्योम *cookie_netfs_data, व्योम *context)
अणु
	get_nfs_खोलो_context(context);
पूर्ण

/*
 * Release an extra reference on a पढ़ो context.
 * - This function can be असलent अगर the completion function करोesn't require a
 *   context.
 */
अटल व्योम nfs_fh_put_context(व्योम *cookie_netfs_data, व्योम *context)
अणु
	अगर (context)
		put_nfs_खोलो_context(context);
पूर्ण

/*
 * Define the inode object क्रम FS-Cache.  This is used to describe an inode
 * object to fscache_acquire_cookie().  It is keyed by the NFS file handle क्रम
 * an inode.
 *
 * Coherency is managed by comparing the copies of i_size, i_mसमय and i_स_समय
 * held in the cache auxiliary data क्रम the data storage object with those in
 * the inode काष्ठा in memory.
 */
स्थिर काष्ठा fscache_cookie_def nfs_fscache_inode_object_def = अणु
	.name		= "NFS.fh",
	.type		= FSCACHE_COOKIE_TYPE_DATAखाता,
	.check_aux	= nfs_fscache_inode_check_aux,
	.get_context	= nfs_fh_get_context,
	.put_context	= nfs_fh_put_context,
पूर्ण;
