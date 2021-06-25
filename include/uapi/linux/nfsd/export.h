<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/linux/nfsd/export.h
 * 
 * Public declarations क्रम NFS exports. The definitions क्रम the
 * syscall पूर्णांकerface are in nfsctl.h
 *
 * Copyright (C) 1995-1997 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित _UAPINFSD_EXPORT_H
#घोषणा _UAPINFSD_EXPORT_H

# include <linux/types.h>

/*
 * Important limits क्रम the exports stuff.
 */
#घोषणा NFSCLNT_IDMAX		1024
#घोषणा NFSCLNT_ADDRMAX		16
#घोषणा NFSCLNT_KEYMAX		32

/*
 * Export flags.
 *
 * Please update the expflags[] array in fs/nfsd/export.c when adding
 * a new flag.
 */
#घोषणा NFSEXP_READONLY		0x0001
#घोषणा NFSEXP_INSECURE_PORT	0x0002
#घोषणा NFSEXP_ROOTSQUASH	0x0004
#घोषणा NFSEXP_ALLSQUASH	0x0008
#घोषणा NFSEXP_ASYNC		0x0010
#घोषणा NFSEXP_GATHERED_WRITES	0x0020
#घोषणा NFSEXP_NOREADसूचीPLUS    0x0040
#घोषणा NFSEXP_SECURITY_LABEL	0x0080
/* 0x100 currently unused */
#घोषणा NFSEXP_NOHIDE		0x0200
#घोषणा NFSEXP_NOSUBTREECHECK	0x0400
#घोषणा	NFSEXP_NOAUTHNLM	0x0800		/* Don't authenticate NLM requests - just trust */
#घोषणा NFSEXP_MSNFS		0x1000	/* करो silly things that MS clients expect; no दीर्घer supported */
#घोषणा NFSEXP_FSID		0x2000
#घोषणा	NFSEXP_CROSSMOUNT	0x4000
#घोषणा	NFSEXP_NOACL		0x8000	/* reserved क्रम possible ACL related use */
/*
 * The NFSEXP_V4ROOT flag causes the kernel to give access only to NFSv4
 * clients, and only to the single directory that is the root of the
 * export; further lookup and सूची_पढ़ो operations are treated as अगर every
 * subdirectory was a mountpoपूर्णांक, and ignored अगर they are not themselves
 * exported.  This is used by nfsd and mountd to स्थिरruct the NFSv4
 * pseuकरोfileप्रणाली, which provides access only to paths leading to each
 * exported fileप्रणाली.
 */
#घोषणा	NFSEXP_V4ROOT		0x10000
#घोषणा NFSEXP_PNFS		0x20000

/* All flags that we claim to support.  (Note we करोn't support NOACL.) */
#घोषणा NFSEXP_ALLFLAGS		0x3FEFF

/* The flags that may vary depending on security flavor: */
#घोषणा NFSEXP_SECINFO_FLAGS	(NFSEXP_READONLY | NFSEXP_ROOTSQUASH \
					| NFSEXP_ALLSQUASH \
					| NFSEXP_INSECURE_PORT)


#पूर्ण_अगर /* _UAPINFSD_EXPORT_H */
