<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/fs/nfs/ioस्थिति.स
 *
 *  Declarations क्रम NFS client per-mount statistics
 *
 *  Copyright (C) 2005, 2006 Chuck Lever <cel@netapp.com>
 *
 */

#अगर_अघोषित _NFS_IOSTAT
#घोषणा _NFS_IOSTAT

#समावेश <linux/percpu.h>
#समावेश <linux/cache.h>
#समावेश <linux/nfs_ioस्थिति.स>

काष्ठा nfs_iostats अणु
	अचिन्हित दीर्घ दीर्घ	bytes[__NFSIOS_BYTESMAX];
#अगर_घोषित CONFIG_NFS_FSCACHE
	अचिन्हित दीर्घ दीर्घ	fscache[__NFSIOS_FSCACHEMAX];
#पूर्ण_अगर
	अचिन्हित दीर्घ		events[__NFSIOS_COUNTSMAX];
पूर्ण ____cacheline_aligned;

अटल अंतरभूत व्योम nfs_inc_server_stats(स्थिर काष्ठा nfs_server *server,
					क्रमागत nfs_stat_eventcounters stat)
अणु
	this_cpu_inc(server->io_stats->events[stat]);
पूर्ण

अटल अंतरभूत व्योम nfs_inc_stats(स्थिर काष्ठा inode *inode,
				 क्रमागत nfs_stat_eventcounters stat)
अणु
	nfs_inc_server_stats(NFS_SERVER(inode), stat);
पूर्ण

अटल अंतरभूत व्योम nfs_add_server_stats(स्थिर काष्ठा nfs_server *server,
					क्रमागत nfs_stat_bytecounters stat,
					दीर्घ addend)
अणु
	this_cpu_add(server->io_stats->bytes[stat], addend);
पूर्ण

अटल अंतरभूत व्योम nfs_add_stats(स्थिर काष्ठा inode *inode,
				 क्रमागत nfs_stat_bytecounters stat,
				 दीर्घ addend)
अणु
	nfs_add_server_stats(NFS_SERVER(inode), stat, addend);
पूर्ण

#अगर_घोषित CONFIG_NFS_FSCACHE
अटल अंतरभूत व्योम nfs_add_fscache_stats(काष्ठा inode *inode,
					 क्रमागत nfs_stat_fscachecounters stat,
					 दीर्घ addend)
अणु
	this_cpu_add(NFS_SERVER(inode)->io_stats->fscache[stat], addend);
पूर्ण
अटल अंतरभूत व्योम nfs_inc_fscache_stats(काष्ठा inode *inode,
					 क्रमागत nfs_stat_fscachecounters stat)
अणु
	this_cpu_inc(NFS_SERVER(inode)->io_stats->fscache[stat]);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा nfs_iostats __percpu *nfs_alloc_iostats(व्योम)
अणु
	वापस alloc_percpu(काष्ठा nfs_iostats);
पूर्ण

अटल अंतरभूत व्योम nfs_मुक्त_iostats(काष्ठा nfs_iostats __percpu *stats)
अणु
	अगर (stats != शून्य)
		मुक्त_percpu(stats);
पूर्ण

#पूर्ण_अगर /* _NFS_IOSTAT */
