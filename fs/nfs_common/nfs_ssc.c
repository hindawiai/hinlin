<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Helper क्रम knfsd's SSC to access ops in NFS client modules
 *
 * Author: Dai Ngo <dai.ngo@oracle.com>
 *
 * Copyright (c) 2020, Oracle and/or its affiliates.
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/nfs_ssc.h>
#समावेश "../nfs/nfs4_fs.h"

MODULE_LICENSE("GPL");

काष्ठा nfs_ssc_client_ops_tbl nfs_ssc_client_tbl;
EXPORT_SYMBOL_GPL(nfs_ssc_client_tbl);

#अगर_घोषित CONFIG_NFS_V4_2
/**
 * nfs42_ssc_रेजिस्टर - install the NFS_V4 client ops in the nfs_ssc_client_tbl
 * @ops: NFS_V4 ops to be installed
 *
 * Return values:
 *   None
 */
व्योम nfs42_ssc_रेजिस्टर(स्थिर काष्ठा nfs4_ssc_client_ops *ops)
अणु
	nfs_ssc_client_tbl.ssc_nfs4_ops = ops;
पूर्ण
EXPORT_SYMBOL_GPL(nfs42_ssc_रेजिस्टर);

/**
 * nfs42_ssc_unरेजिस्टर - uninstall the NFS_V4 client ops from
 *				the nfs_ssc_client_tbl
 * @ops: ops to be uninstalled
 *
 * Return values:
 *   None
 */
व्योम nfs42_ssc_unरेजिस्टर(स्थिर काष्ठा nfs4_ssc_client_ops *ops)
अणु
	अगर (nfs_ssc_client_tbl.ssc_nfs4_ops != ops)
		वापस;

	nfs_ssc_client_tbl.ssc_nfs4_ops = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nfs42_ssc_unरेजिस्टर);
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */

#अगर_घोषित CONFIG_NFS_V4_2
/**
 * nfs_ssc_रेजिस्टर - install the NFS_FS client ops in the nfs_ssc_client_tbl
 * @ops: NFS_FS ops to be installed
 *
 * Return values:
 *   None
 */
व्योम nfs_ssc_रेजिस्टर(स्थिर काष्ठा nfs_ssc_client_ops *ops)
अणु
	nfs_ssc_client_tbl.ssc_nfs_ops = ops;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_ssc_रेजिस्टर);

/**
 * nfs_ssc_unरेजिस्टर - uninstall the NFS_FS client ops from
 *				the nfs_ssc_client_tbl
 * @ops: ops to be uninstalled
 *
 * Return values:
 *   None
 */
व्योम nfs_ssc_unरेजिस्टर(स्थिर काष्ठा nfs_ssc_client_ops *ops)
अणु
	अगर (nfs_ssc_client_tbl.ssc_nfs_ops != ops)
		वापस;
	nfs_ssc_client_tbl.ssc_nfs_ops = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_ssc_unरेजिस्टर);

#अन्यथा
व्योम nfs_ssc_रेजिस्टर(स्थिर काष्ठा nfs_ssc_client_ops *ops)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(nfs_ssc_रेजिस्टर);

व्योम nfs_ssc_unरेजिस्टर(स्थिर काष्ठा nfs_ssc_client_ops *ops)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(nfs_ssc_unरेजिस्टर);
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */
