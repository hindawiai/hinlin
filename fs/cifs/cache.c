<शैली गुरु>
/*
 *   fs/cअगरs/cache.c - CIFS fileप्रणाली cache index काष्ठाure definitions
 *
 *   Copyright (c) 2010 Novell, Inc.
 *   Authors(s): Suresh Jayaraman (sjayaraman@suse.de>
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
#समावेश "fscache.h"
#समावेश "cifs_debug.h"

/*
 * CIFS fileप्रणाली definition क्रम FS-Cache
 */
काष्ठा fscache_netfs cअगरs_fscache_netfs = अणु
	.name = "cifs",
	.version = 0,
पूर्ण;

/*
 * Register CIFS क्रम caching with FS-Cache
 */
पूर्णांक cअगरs_fscache_रेजिस्टर(व्योम)
अणु
	वापस fscache_रेजिस्टर_netfs(&cअगरs_fscache_netfs);
पूर्ण

/*
 * Unरेजिस्टर CIFS क्रम caching
 */
व्योम cअगरs_fscache_unरेजिस्टर(व्योम)
अणु
	fscache_unरेजिस्टर_netfs(&cअगरs_fscache_netfs);
पूर्ण

/*
 * Server object क्रम FS-Cache
 */
स्थिर काष्ठा fscache_cookie_def cअगरs_fscache_server_index_def = अणु
	.name = "CIFS.server",
	.type = FSCACHE_COOKIE_TYPE_INDEX,
पूर्ण;

अटल क्रमागत
fscache_checkaux cअगरs_fscache_super_check_aux(व्योम *cookie_netfs_data,
					      स्थिर व्योम *data,
					      uपूर्णांक16_t datalen,
					      loff_t object_size)
अणु
	काष्ठा cअगरs_fscache_super_auxdata auxdata;
	स्थिर काष्ठा cअगरs_tcon *tcon = cookie_netfs_data;

	अगर (datalen != माप(auxdata))
		वापस FSCACHE_CHECKAUX_OBSOLETE;

	स_रखो(&auxdata, 0, माप(auxdata));
	auxdata.resource_id = tcon->resource_id;
	auxdata.vol_create_समय = tcon->vol_create_समय;
	auxdata.vol_serial_number = tcon->vol_serial_number;

	अगर (स_भेद(data, &auxdata, datalen) != 0)
		वापस FSCACHE_CHECKAUX_OBSOLETE;

	वापस FSCACHE_CHECKAUX_OKAY;
पूर्ण

/*
 * Superblock object क्रम FS-Cache
 */
स्थिर काष्ठा fscache_cookie_def cअगरs_fscache_super_index_def = अणु
	.name = "CIFS.super",
	.type = FSCACHE_COOKIE_TYPE_INDEX,
	.check_aux = cअगरs_fscache_super_check_aux,
पूर्ण;

अटल क्रमागत
fscache_checkaux cअगरs_fscache_inode_check_aux(व्योम *cookie_netfs_data,
					      स्थिर व्योम *data,
					      uपूर्णांक16_t datalen,
					      loff_t object_size)
अणु
	काष्ठा cअगरs_fscache_inode_auxdata auxdata;
	काष्ठा cअगरsInodeInfo *cअगरsi = cookie_netfs_data;

	अगर (datalen != माप(auxdata))
		वापस FSCACHE_CHECKAUX_OBSOLETE;

	स_रखो(&auxdata, 0, माप(auxdata));
	auxdata.eof = cअगरsi->server_eof;
	auxdata.last_ग_लिखो_समय_sec = cअगरsi->vfs_inode.i_mसमय.tv_sec;
	auxdata.last_change_समय_sec = cअगरsi->vfs_inode.i_स_समय.tv_sec;
	auxdata.last_ग_लिखो_समय_nsec = cअगरsi->vfs_inode.i_mसमय.tv_nsec;
	auxdata.last_change_समय_nsec = cअगरsi->vfs_inode.i_स_समय.tv_nsec;

	अगर (स_भेद(data, &auxdata, datalen) != 0)
		वापस FSCACHE_CHECKAUX_OBSOLETE;

	वापस FSCACHE_CHECKAUX_OKAY;
पूर्ण

स्थिर काष्ठा fscache_cookie_def cअगरs_fscache_inode_object_def = अणु
	.name		= "CIFS.uniqueid",
	.type		= FSCACHE_COOKIE_TYPE_DATAखाता,
	.check_aux	= cअगरs_fscache_inode_check_aux,
पूर्ण;
