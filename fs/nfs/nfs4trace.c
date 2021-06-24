<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013 Trond Myklebust <Trond.Myklebust@netapp.com>
 */
#समावेश <linux/nfs_fs.h>
#समावेश "nfs4_fs.h"
#समावेश "internal.h"
#समावेश "nfs4session.h"
#समावेश "callback.h"
#समावेश "pnfs.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "nfs4trace.h"

#अगर_घोषित CONFIG_NFS_V4_1
EXPORT_TRACEPOINT_SYMBOL_GPL(nfs4_pnfs_पढ़ो);
EXPORT_TRACEPOINT_SYMBOL_GPL(nfs4_pnfs_ग_लिखो);
EXPORT_TRACEPOINT_SYMBOL_GPL(nfs4_pnfs_commit_ds);

EXPORT_TRACEPOINT_SYMBOL_GPL(pnfs_mds_fallback_pg_init_पढ़ो);
EXPORT_TRACEPOINT_SYMBOL_GPL(pnfs_mds_fallback_pg_init_ग_लिखो);
EXPORT_TRACEPOINT_SYMBOL_GPL(pnfs_mds_fallback_pg_get_mirror_count);
EXPORT_TRACEPOINT_SYMBOL_GPL(pnfs_mds_fallback_पढ़ो_करोne);
EXPORT_TRACEPOINT_SYMBOL_GPL(pnfs_mds_fallback_ग_लिखो_करोne);
EXPORT_TRACEPOINT_SYMBOL_GPL(pnfs_mds_fallback_पढ़ो_pagelist);
EXPORT_TRACEPOINT_SYMBOL_GPL(pnfs_mds_fallback_ग_लिखो_pagelist);

EXPORT_TRACEPOINT_SYMBOL_GPL(ff_layout_पढ़ो_error);
EXPORT_TRACEPOINT_SYMBOL_GPL(ff_layout_ग_लिखो_error);
EXPORT_TRACEPOINT_SYMBOL_GPL(ff_layout_commit_error);
#पूर्ण_अगर
