<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * NFSv3 protocol definitions
 */
#अगर_अघोषित _UAPI_LINUX_NFS3_H
#घोषणा _UAPI_LINUX_NFS3_H

#घोषणा NFS3_PORT		2049
#घोषणा NFS3_MAXDATA		32768
#घोषणा NFS3_MAXPATHLEN		PATH_MAX
#घोषणा NFS3_MAXNAMLEN		NAME_MAX
#घोषणा NFS3_MAXGROUPS		16
#घोषणा NFS3_FHSIZE		64
#घोषणा NFS3_COOKIESIZE		4
#घोषणा NFS3_CREATEVERFSIZE	8
#घोषणा NFS3_COOKIEVERFSIZE	8
#घोषणा NFS3_WRITEVERFSIZE	8
#घोषणा NFS3_FIFO_DEV		(-1)
#घोषणा NFS3MODE_FMT		0170000
#घोषणा NFS3MODE_सूची		0040000
#घोषणा NFS3MODE_CHR		0020000
#घोषणा NFS3MODE_BLK		0060000
#घोषणा NFS3MODE_REG		0100000
#घोषणा NFS3MODE_LNK		0120000
#घोषणा NFS3MODE_SOCK		0140000
#घोषणा NFS3MODE_FIFO		0010000

/* Flags क्रम access() call */
#घोषणा NFS3_ACCESS_READ	0x0001
#घोषणा NFS3_ACCESS_LOOKUP	0x0002
#घोषणा NFS3_ACCESS_MODIFY	0x0004
#घोषणा NFS3_ACCESS_EXTEND	0x0008
#घोषणा NFS3_ACCESS_DELETE	0x0010
#घोषणा NFS3_ACCESS_EXECUTE	0x0020
#घोषणा NFS3_ACCESS_FULL	0x003f

/* Flags क्रम create mode */
क्रमागत nfs3_createmode अणु
	NFS3_CREATE_UNCHECKED = 0,
	NFS3_CREATE_GUARDED = 1,
	NFS3_CREATE_EXCLUSIVE = 2
पूर्ण;

/* NFSv3 file प्रणाली properties */
#घोषणा NFS3_FSF_LINK		0x0001
#घोषणा NFS3_FSF_SYMLINK	0x0002
#घोषणा NFS3_FSF_HOMOGENEOUS	0x0008
#घोषणा NFS3_FSF_CANSETTIME	0x0010
/* Some लघुhands. See fs/nfsd/nfs3proc.c */
#घोषणा NFS3_FSF_DEFAULT	0x001B
#घोषणा NFS3_FSF_BILLYBOY	0x0018
#घोषणा NFS3_FSF_READONLY	0x0008

क्रमागत nfs3_ftype अणु
	NF3NON  = 0,
	NF3REG  = 1,
	NF3सूची  = 2,
	NF3BLK  = 3,
	NF3CHR  = 4,
	NF3LNK  = 5,
	NF3SOCK = 6,
	NF3FIFO = 7,	/* changed from NFSv2 (was 8) */
	NF3BAD  = 8
पूर्ण;

क्रमागत nfs3_समय_how अणु
	DONT_CHANGE		= 0,
	SET_TO_SERVER_TIME	= 1,
	SET_TO_CLIENT_TIME	= 2,
पूर्ण;

काष्ठा nfs3_fh अणु
	अचिन्हित लघु size;
	अचिन्हित अक्षर  data[NFS3_FHSIZE];
पूर्ण;

#घोषणा NFS3_VERSION		3
#घोषणा NFS3PROC_शून्य		0
#घोषणा NFS3PROC_GETATTR	1
#घोषणा NFS3PROC_SETATTR	2
#घोषणा NFS3PROC_LOOKUP		3
#घोषणा NFS3PROC_ACCESS		4
#घोषणा NFS3PROC_READLINK	5
#घोषणा NFS3PROC_READ		6
#घोषणा NFS3PROC_WRITE		7
#घोषणा NFS3PROC_CREATE		8
#घोषणा NFS3PROC_MKसूची		9
#घोषणा NFS3PROC_SYMLINK	10
#घोषणा NFS3PROC_MKNOD		11
#घोषणा NFS3PROC_REMOVE		12
#घोषणा NFS3PROC_RMसूची		13
#घोषणा NFS3PROC_RENAME		14
#घोषणा NFS3PROC_LINK		15
#घोषणा NFS3PROC_READसूची	16
#घोषणा NFS3PROC_READसूचीPLUS	17
#घोषणा NFS3PROC_FSSTAT		18
#घोषणा NFS3PROC_FSINFO		19
#घोषणा NFS3PROC_PATHCONF	20
#घोषणा NFS3PROC_COMMIT		21

#घोषणा NFS_MNT3_VERSION	3
 

#पूर्ण_अगर /* _UAPI_LINUX_NFS3_H */
