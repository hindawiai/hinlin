<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  User-space visible declarations क्रम NFS client per-mount
 *  poपूर्णांक statistics
 *
 *  Copyright (C) 2005, 2006 Chuck Lever <cel@netapp.com>
 *
 *  NFS client per-mount statistics provide inक्रमmation about the
 *  health of the NFS client and the health of each NFS mount poपूर्णांक.
 *  Generally these are not क्रम detailed problem diagnosis, but
 *  simply to indicate that there is a problem.
 *
 *  These counters are not meant to be human-पढ़ोable, but are meant
 *  to be पूर्णांकegrated पूर्णांकo प्रणाली monitoring tools such as "sar" and
 *  "iostat".  As such, the counters are sampled by the tools over
 *  समय, and are never zeroed after a file प्रणाली is mounted.
 *  Moving averages can be computed by the tools by taking the
 *  dअगरference between two instantaneous samples  and भागiding that
 *  by the समय between the samples.
 */

#अगर_अघोषित _LINUX_NFS_IOSTAT
#घोषणा _LINUX_NFS_IOSTAT

#घोषणा NFS_IOSTAT_VERS		"1.1"

/*
 * NFS byte counters
 *
 * 1.  SERVER - the number of payload bytes पढ़ो from or written
 *     to the server by the NFS client via an NFS READ or WRITE
 *     request.
 *
 * 2.  NORMAL - the number of bytes पढ़ो or written by applications
 *     via the पढ़ो(2) and ग_लिखो(2) प्रणाली call पूर्णांकerfaces.
 *
 * 3.  सूचीECT - the number of bytes पढ़ो or written from files
 *     खोलोed with the O_सूचीECT flag.
 *
 * These counters give a view of the data throughput पूर्णांकo and out
 * of the NFS client.  Comparing the number of bytes requested by
 * an application with the number of bytes the client requests from
 * the server can provide an indication of client efficiency
 * (per-op, cache hits, etc).
 *
 * These counters can also help अक्षरacterize which access methods
 * are in use.  सूचीECT by itself shows whether there is any O_सूचीECT
 * traffic.  NORMAL + सूचीECT shows how much data is going through
 * the प्रणाली call पूर्णांकerface.  A large amount of SERVER traffic
 * without much NORMAL or सूचीECT traffic shows that applications
 * are using mapped files.
 *
 * NFS page counters
 *
 * These count the number of pages पढ़ो or written via nfs_पढ़ोpage(),
 * nfs_पढ़ोpages(), or their ग_लिखो equivalents.
 *
 * NB: When adding new byte counters, please include the measured
 * units in the name of each byte counter to help users of this
 * पूर्णांकerface determine what exactly is being counted.
 */
क्रमागत nfs_stat_bytecounters अणु
	NFSIOS_NORMALREADBYTES = 0,
	NFSIOS_NORMALWRITTENBYTES,
	NFSIOS_सूचीECTREADBYTES,
	NFSIOS_सूचीECTWRITTENBYTES,
	NFSIOS_SERVERREADBYTES,
	NFSIOS_SERVERWRITTENBYTES,
	NFSIOS_READPAGES,
	NFSIOS_WRITEPAGES,
	__NFSIOS_BYTESMAX,
पूर्ण;

/*
 * NFS event counters
 *
 * These counters provide a low-overhead way of monitoring client
 * activity without enabling NFS trace debugging.  The counters
 * show the rate at which VFS requests are made, and how often the
 * client invalidates its data and attribute caches.  This allows
 * प्रणाली administrators to monitor such things as how बंद-to-खोलो
 * is working, and answer questions such as "why are there so many
 * GETATTR requests on the wire?"
 *
 * They also count anamolous events such as लघु पढ़ोs and ग_लिखोs,
 * silly नामs due to बंद-after-delete, and operations that
 * change the size of a file (such operations can often be the
 * source of data corruption अगर applications aren't using file
 * locking properly).
 */
क्रमागत nfs_stat_eventcounters अणु
	NFSIOS_INODEREVALIDATE = 0,
	NFSIOS_DENTRYREVALIDATE,
	NFSIOS_DATAINVALIDATE,
	NFSIOS_ATTRINVALIDATE,
	NFSIOS_VFSOPEN,
	NFSIOS_VFSLOOKUP,
	NFSIOS_VFSACCESS,
	NFSIOS_VFSUPDATEPAGE,
	NFSIOS_VFSREADPAGE,
	NFSIOS_VFSREADPAGES,
	NFSIOS_VFSWRITEPAGE,
	NFSIOS_VFSWRITEPAGES,
	NFSIOS_VFSGETDENTS,
	NFSIOS_VFSSETATTR,
	NFSIOS_VFSFLUSH,
	NFSIOS_VFSFSYNC,
	NFSIOS_VFSLOCK,
	NFSIOS_VFSRELEASE,
	NFSIOS_CONGESTIONWAIT,
	NFSIOS_SETATTRTRUNC,
	NFSIOS_EXTENDWRITE,
	NFSIOS_SILLYRENAME,
	NFSIOS_SHORTREAD,
	NFSIOS_SHORTWRITE,
	NFSIOS_DELAY,
	NFSIOS_PNFS_READ,
	NFSIOS_PNFS_WRITE,
	__NFSIOS_COUNTSMAX,
पूर्ण;

/*
 * NFS local caching servicing counters
 */
क्रमागत nfs_stat_fscachecounters अणु
	NFSIOS_FSCACHE_PAGES_READ_OK,
	NFSIOS_FSCACHE_PAGES_READ_FAIL,
	NFSIOS_FSCACHE_PAGES_WRITTEN_OK,
	NFSIOS_FSCACHE_PAGES_WRITTEN_FAIL,
	NFSIOS_FSCACHE_PAGES_UNCACHED,
	__NFSIOS_FSCACHEMAX,
पूर्ण;

#पूर्ण_अगर	/* _LINUX_NFS_IOSTAT */
