<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * NFS protocol definitions
 *
 * This file contains स्थिरants क्रम Version 2 of the protocol.
 */
#अगर_अघोषित _LINUX_NFS2_H
#घोषणा _LINUX_NFS2_H

#घोषणा NFS2_PORT	2049
#घोषणा NFS2_MAXDATA	8192
#घोषणा NFS2_MAXPATHLEN	1024
#घोषणा NFS2_MAXNAMLEN	255
#घोषणा NFS2_MAXGROUPS	16
#घोषणा NFS2_FHSIZE	32
#घोषणा NFS2_COOKIESIZE	4
#घोषणा NFS2_FIFO_DEV	(-1)
#घोषणा NFS2MODE_FMT	0170000
#घोषणा NFS2MODE_सूची	0040000
#घोषणा NFS2MODE_CHR	0020000
#घोषणा NFS2MODE_BLK	0060000
#घोषणा NFS2MODE_REG	0100000
#घोषणा NFS2MODE_LNK	0120000
#घोषणा NFS2MODE_SOCK	0140000
#घोषणा NFS2MODE_FIFO	0010000


/* NFSv2 file types - beware, these are not the same in NFSv3 */
क्रमागत nfs2_ftype अणु
	NF2NON = 0,
	NF2REG = 1,
	NF2सूची = 2,
	NF2BLK = 3,
	NF2CHR = 4,
	NF2LNK = 5,
	NF2SOCK = 6,
	NF2BAD = 7,
	NF2FIFO = 8
पूर्ण;

काष्ठा nfs2_fh अणु
	अक्षर			data[NFS2_FHSIZE];
पूर्ण;

/*
 * Procedure numbers क्रम NFSv2
 */
#घोषणा NFS2_VERSION		2
#घोषणा NFSPROC_शून्य		0
#घोषणा NFSPROC_GETATTR		1
#घोषणा NFSPROC_SETATTR		2
#घोषणा NFSPROC_ROOT		3
#घोषणा NFSPROC_LOOKUP		4
#घोषणा NFSPROC_READLINK	5
#घोषणा NFSPROC_READ		6
#घोषणा NFSPROC_WRITECACHE	7
#घोषणा NFSPROC_WRITE		8
#घोषणा NFSPROC_CREATE		9
#घोषणा NFSPROC_REMOVE		10
#घोषणा NFSPROC_RENAME		11
#घोषणा NFSPROC_LINK		12
#घोषणा NFSPROC_SYMLINK		13
#घोषणा NFSPROC_MKसूची		14
#घोषणा NFSPROC_RMसूची		15
#घोषणा NFSPROC_READसूची		16
#घोषणा NFSPROC_STATFS		17

#पूर्ण_अगर /* _LINUX_NFS2_H */
