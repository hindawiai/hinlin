<शैली गुरु>
/* 
   You may distribute this file under either of the two licenses that
   follow at your discretion.
*/

/* BLURB lgpl

                           Coda File System
                              Release 5

          Copyright (c) 1987-1999 Carnegie Mellon University
                  Additional copyrights listed below

This code is distributed "AS IS" without warranty of any kind under
the terms of the GNU Library General Public Licence Version 2, as
shown in the file LICENSE, or under the license shown below. The
technical and financial contributors to Coda are listed in the file
CREDITS.

                        Additional copyrights 
*/

/*

            Coda: an Experimental Distributed File System
                             Release 4.0

          Copyright (c) 1987-1999 Carnegie Mellon University
                         All Rights Reserved

Permission  to  use, copy, modअगरy and distribute this software and its
करोcumentation is hereby granted,  provided  that  both  the  copyright
notice  and  this  permission  notice  appear  in  all  copies  of the
software, derivative works or  modअगरied  versions,  and  any  portions
thereof, and that both notices appear in supporting करोcumentation, and
that credit is given to Carnegie Mellon University  in  all  करोcuments
and खुलाity pertaining to direct or indirect use of this code or its
derivatives.

CODA IS AN EXPERIMENTAL SOFTWARE SYSTEM AND IS  KNOWN  TO  HAVE  BUGS,
SOME  OF  WHICH MAY HAVE SERIOUS CONSEQUENCES.  CARNEGIE MELLON ALLOWS
FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION.   CARNEGIE  MELLON
DISCLAIMS  ANY  LIABILITY  OF  ANY  KIND  FOR  ANY  DAMAGES WHATSOEVER
RESULTING सूचीECTLY OR INसूचीECTLY FROM THE USE OF THIS SOFTWARE  OR  OF
ANY DERIVATIVE WORK.

Carnegie  Mellon  encourages  users  of  this  software  to वापस any
improvements or extensions that  they  make,  and  to  grant  Carnegie
Mellon the rights to redistribute these changes without encumbrance.
*/

/*
 *
 * Based on cfs.h from Mach, but revamped क्रम increased simplicity.
 * Linux modअगरications by 
 * Peter Braam, Aug 1996
 */

#अगर_अघोषित _UAPI_CODA_HEADER_
#घोषणा _UAPI_CODA_HEADER_


/* Catch new _KERNEL defn क्रम NetBSD and DJGPP/__CYGWIN32__ */
#अगर defined(__NetBSD__) || \
  ((defined(DJGPP) || defined(__CYGWIN32__)) && !defined(KERNEL))
#समावेश <sys/types.h>
#पूर्ण_अगर 

#अगर_अघोषित CODA_MAXSYMLINKS
#घोषणा CODA_MAXSYMLINKS 10
#पूर्ण_अगर

#अगर defined(DJGPP) || defined(__CYGWIN32__)
#अगर_घोषित KERNEL
प्रकार अचिन्हित दीर्घ u_दीर्घ;
प्रकार अचिन्हित पूर्णांक u_पूर्णांक;
प्रकार अचिन्हित लघु u_लघु;
प्रकार u_दीर्घ ino_t;
प्रकार u_दीर्घ dev_t;
प्रकार व्योम * caddr_t;
#अगर_घोषित DOS
प्रकार अचिन्हित __पूर्णांक64 u_quad_t;
#अन्यथा 
प्रकार अचिन्हित दीर्घ दीर्घ u_quad_t;
#पूर्ण_अगर

#घोषणा अंतरभूत

#अन्यथा  /* DJGPP but not KERNEL */
#समावेश <sys/समय.स>
प्रकार अचिन्हित दीर्घ दीर्घ u_quad_t;
#पूर्ण_अगर /* !KERNEL */
#पूर्ण_अगर /* !DJGPP */


#अगर defined(__linux__)
#समावेश <linux/समय.स>
#घोषणा cdev_t u_quad_t
#अगर_अघोषित __KERNEL__
#अगर !defined(_UQUAD_T_) && (!defined(__GLIBC__) || __GLIBC__ < 2)
#घोषणा _UQUAD_T_ 1
प्रकार अचिन्हित दीर्घ दीर्घ u_quad_t;
#पूर्ण_अगर
#पूर्ण_अगर /* __KERNEL__ */
#अन्यथा
#घोषणा cdev_t dev_t
#पूर्ण_अगर

#अगर_अघोषित __BIT_TYPES_DEFINED__
#घोषणा __BIT_TYPES_DEFINED__
प्रकार चिन्हित अक्षर	      पूर्णांक8_t;
प्रकार अचिन्हित अक्षर	    u_पूर्णांक8_t;
प्रकार लघु		     पूर्णांक16_t;
प्रकार अचिन्हित लघु	   u_पूर्णांक16_t;
प्रकार पूर्णांक		     पूर्णांक32_t;
प्रकार अचिन्हित पूर्णांक	   u_पूर्णांक32_t;
#पूर्ण_अगर


/*
 * Cfs स्थिरants
 */
#घोषणा CODA_MAXNAMLEN   255
#घोषणा CODA_MAXPATHLEN  1024
#घोषणा CODA_MAXSYMLINK  10

/* these are Coda's version of O_RDONLY etc combinations
 * to deal with VFS खोलो modes
 */
#घोषणा	C_O_READ	0x001
#घोषणा	C_O_WRITE       0x002
#घोषणा C_O_TRUNC       0x010
#घोषणा C_O_EXCL	0x100
#घोषणा C_O_CREAT	0x200

/* these are to find mode bits in Venus */ 
#घोषणा C_M_READ  00400
#घोषणा C_M_WRITE 00200

/* क्रम access Venus will use */
#घोषणा C_A_C_OK    8               /* Test क्रम writing upon create.  */
#घोषणा C_A_R_OK    4               /* Test क्रम पढ़ो permission.  */
#घोषणा C_A_W_OK    2               /* Test क्रम ग_लिखो permission.  */
#घोषणा C_A_X_OK    1               /* Test क्रम execute permission.  */
#घोषणा C_A_F_OK    0               /* Test क्रम existence.  */



#अगर_अघोषित _VENUS_सूचीENT_T_
#घोषणा _VENUS_सूचीENT_T_ 1
काष्ठा venus_dirent अणु
        u_पूर्णांक32_t d_fileno;		/* file number of entry */
        u_पूर्णांक16_t d_reclen;		/* length of this record */
        u_पूर्णांक8_t  d_type;			/* file type, see below */
        u_पूर्णांक8_t  d_namlen;		/* length of string in d_name */
        अक्षर	  d_name[CODA_MAXNAMLEN + 1];/* name must be no दीर्घer than this */
पूर्ण;
#अघोषित सूचीSIZ
#घोषणा सूचीSIZ(dp)      ((माप (काष्ठा venus_dirent) - (CODA_MAXNAMLEN+1)) + \
                         (((dp)->d_namlen+1 + 3) &~ 3))

/*
 * File types
 */
#घोषणा	CDT_UNKNOWN	 0
#घोषणा	CDT_FIFO	 1
#घोषणा	CDT_CHR		 2
#घोषणा	CDT_सूची		 4
#घोषणा	CDT_BLK		 6
#घोषणा	CDT_REG		 8
#घोषणा	CDT_LNK		10
#घोषणा	CDT_SOCK	12
#घोषणा	CDT_WHT		14

/*
 * Convert between stat काष्ठाure types and directory types.
 */
#घोषणा	IFTOCDT(mode)	(((mode) & 0170000) >> 12)
#घोषणा	CDTTOIF(dirtype)	((dirtype) << 12)

#पूर्ण_अगर

#अगर_अघोषित _VUID_T_
#घोषणा _VUID_T_
प्रकार u_पूर्णांक32_t vuid_t;
प्रकार u_पूर्णांक32_t vgid_t;
#पूर्ण_अगर /*_VUID_T_ */

काष्ठा CodaFid अणु
	u_पूर्णांक32_t opaque[4];
पूर्ण;

#घोषणा coda_f2i(fid)\
	(fid ? (fid->opaque[3] ^ (fid->opaque[2]<<10) ^ (fid->opaque[1]<<20) ^ fid->opaque[0]) : 0)

#अगर_अघोषित _VENUS_VATTR_T_
#घोषणा _VENUS_VATTR_T_
/*
 * Vnode types.  VNON means no type.
 */
क्रमागत coda_vtype	अणु C_VNON, C_VREG, C_Vसूची, C_VBLK, C_VCHR, C_VLNK, C_VSOCK, C_VFIFO, C_VBAD पूर्ण;

काष्ठा coda_बारpec अणु
	पूर्णांक64_t		tv_sec;		/* seconds */
	दीर्घ		tv_nsec;	/* nanoseconds */
पूर्ण;

काष्ठा coda_vattr अणु
	दीर्घ     	va_type;	/* vnode type (क्रम create) */
	u_लघु		va_mode;	/* files access mode and type */
	लघु		va_nlink;	/* number of references to file */
	vuid_t		va_uid;		/* owner user id */
	vgid_t		va_gid;		/* owner group id */
	दीर्घ		va_fileid;	/* file id */
	u_quad_t	va_size;	/* file size in bytes */
	दीर्घ		va_blocksize;	/* blocksize preferred क्रम i/o */
	काष्ठा coda_बारpec va_aसमय;	/* समय of last access */
	काष्ठा coda_बारpec va_mसमय;	/* समय of last modअगरication */
	काष्ठा coda_बारpec va_स_समय;	/* समय file changed */
	u_दीर्घ		va_gen;		/* generation number of file */
	u_दीर्घ		va_flags;	/* flags defined क्रम file */
	cdev_t	        va_rdev;	/* device special file represents */
	u_quad_t	va_bytes;	/* bytes of disk space held by file */
	u_quad_t	va_filerev;	/* file modअगरication number */
पूर्ण;

#पूर्ण_अगर 

/* काष्ठाure used by CODA_STATFS क्रम getting cache inक्रमmation from venus */
काष्ठा coda_statfs अणु
    पूर्णांक32_t f_blocks;
    पूर्णांक32_t f_bमुक्त;
    पूर्णांक32_t f_bavail;
    पूर्णांक32_t f_files;
    पूर्णांक32_t f_fमुक्त;
पूर्ण;

/*
 * Kernel <--> Venus communications.
 */

#घोषणा CODA_ROOT	2
#घोषणा CODA_OPEN_BY_FD	3
#घोषणा CODA_OPEN	4
#घोषणा CODA_CLOSE	5
#घोषणा CODA_IOCTL	6
#घोषणा CODA_GETATTR	7
#घोषणा CODA_SETATTR	8
#घोषणा CODA_ACCESS	9
#घोषणा CODA_LOOKUP	10
#घोषणा CODA_CREATE	11
#घोषणा CODA_REMOVE	12
#घोषणा CODA_LINK	13
#घोषणा CODA_RENAME	14
#घोषणा CODA_MKसूची	15
#घोषणा CODA_RMसूची	16
#घोषणा CODA_SYMLINK	18
#घोषणा CODA_READLINK	19
#घोषणा CODA_FSYNC	20
#घोषणा CODA_VGET	22
#घोषणा CODA_SIGNAL	23
#घोषणा CODA_REPLACE	 24 /* DOWNCALL */
#घोषणा CODA_FLUSH       25 /* DOWNCALL */
#घोषणा CODA_PURGEUSER   26 /* DOWNCALL */
#घोषणा CODA_ZAPखाता     27 /* DOWNCALL */
#घोषणा CODA_ZAPसूची      28 /* DOWNCALL */
#घोषणा CODA_PURGEFID    30 /* DOWNCALL */
#घोषणा CODA_OPEN_BY_PATH 31
#घोषणा CODA_RESOLVE     32
#घोषणा CODA_REINTEGRATE 33
#घोषणा CODA_STATFS	 34
#घोषणा CODA_STORE	 35
#घोषणा CODA_RELEASE	 36
#घोषणा CODA_ACCESS_INTENT 37
#घोषणा CODA_NCALLS 38

#घोषणा DOWNCALL(opcode) (opcode >= CODA_REPLACE && opcode <= CODA_PURGEFID)

#घोषणा VC_MAXDATASIZE	    8192
#घोषणा VC_MAXMSGSIZE      माप(जोड़ inputArgs)+माप(जोड़ outputArgs) +\
                            VC_MAXDATASIZE  

#घोषणा CIOC_KERNEL_VERSION _IOWR('c', 10, माप_प्रकार)

//      CODA_KERNEL_VERSION 0 /* करोn't care about kernel version number */
//      CODA_KERNEL_VERSION 1 /* The old venus 4.6 compatible पूर्णांकerface */
//      CODA_KERNEL_VERSION 2 /* venus_lookup माला_लो an extra parameter */
//      CODA_KERNEL_VERSION 3 /* 128-bit file identअगरiers */
//      CODA_KERNEL_VERSION 4 /* 64-bit बारpec */
#घोषणा CODA_KERNEL_VERSION 5 /* access पूर्णांकent support */

/*
 *        Venus <-> Coda  RPC arguments
 */
काष्ठा coda_in_hdr अणु
    u_पूर्णांक32_t opcode;
    u_पूर्णांक32_t unique;	    /* Keep multiple outstanding msgs distinct */
    __kernel_pid_t pid;
    __kernel_pid_t pgid;
    vuid_t uid;
पूर्ण;

/* Really important that opcode and unique are 1st two fields! */
काष्ठा coda_out_hdr अणु
    u_पूर्णांक32_t opcode;
    u_पूर्णांक32_t unique;	
    u_पूर्णांक32_t result;
पूर्ण;

/* coda_root: NO_IN */
काष्ठा coda_root_out अणु
    काष्ठा coda_out_hdr oh;
    काष्ठा CodaFid VFid;
पूर्ण;

काष्ठा coda_root_in अणु
    काष्ठा coda_in_hdr in;
पूर्ण;

/* coda_खोलो: */
काष्ठा coda_खोलो_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    पूर्णांक	flags;
पूर्ण;

काष्ठा coda_खोलो_out अणु
    काष्ठा coda_out_hdr oh;
    cdev_t	dev;
    ino_t	inode;
पूर्ण;


/* coda_store: */
काष्ठा coda_store_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    पूर्णांक	flags;
पूर्ण;

काष्ठा coda_store_out अणु
    काष्ठा coda_out_hdr out;
पूर्ण;

/* coda_release: */
काष्ठा coda_release_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    पूर्णांक	flags;
पूर्ण;

काष्ठा coda_release_out अणु
    काष्ठा coda_out_hdr out;
पूर्ण;

/* coda_बंद: */
काष्ठा coda_बंद_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    पूर्णांक	flags;
पूर्ण;

काष्ठा coda_बंद_out अणु
    काष्ठा coda_out_hdr out;
पूर्ण;

/* coda_ioctl: */
काष्ठा coda_ioctl_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    पूर्णांक	cmd;
    पूर्णांक	len;
    पूर्णांक	rwflag;
    अक्षर *data;			/* Place holder क्रम data. */
पूर्ण;

काष्ठा coda_ioctl_out अणु
    काष्ठा coda_out_hdr oh;
    पूर्णांक	len;
    caddr_t	data;		/* Place holder क्रम data. */
पूर्ण;


/* coda_getattr: */
काष्ठा coda_getattr_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
पूर्ण;

काष्ठा coda_getattr_out अणु
    काष्ठा coda_out_hdr oh;
    काष्ठा coda_vattr attr;
पूर्ण;


/* coda_setattr: NO_OUT */
काष्ठा coda_setattr_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    काष्ठा coda_vattr attr;
पूर्ण;

काष्ठा coda_setattr_out अणु
    काष्ठा coda_out_hdr out;
पूर्ण;

/* coda_access: NO_OUT */
काष्ठा coda_access_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    पूर्णांक	flags;
पूर्ण;

काष्ठा coda_access_out अणु
    काष्ठा coda_out_hdr out;
पूर्ण;


/* lookup flags */
#घोषणा CLU_CASE_SENSITIVE     0x01
#घोषणा CLU_CASE_INSENSITIVE   0x02

/* coda_lookup: */
काष्ठा  coda_lookup_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    पूर्णांक         name;		/* Place holder क्रम data. */
    पूर्णांक         flags;	
पूर्ण;

काष्ठा coda_lookup_out अणु
    काष्ठा coda_out_hdr oh;
    काष्ठा CodaFid VFid;
    पूर्णांक	vtype;
पूर्ण;


/* coda_create: */
काष्ठा coda_create_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    काष्ठा coda_vattr attr;
    पूर्णांक excl;
    पूर्णांक mode;
    पूर्णांक 	name;		/* Place holder क्रम data. */
पूर्ण;

काष्ठा coda_create_out अणु
    काष्ठा coda_out_hdr oh;
    काष्ठा CodaFid VFid;
    काष्ठा coda_vattr attr;
पूर्ण;


/* coda_हटाओ: NO_OUT */
काष्ठा coda_हटाओ_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    पूर्णांक name;		/* Place holder क्रम data. */
पूर्ण;

काष्ठा coda_हटाओ_out अणु
    काष्ठा coda_out_hdr out;
पूर्ण;

/* coda_link: NO_OUT */
काष्ठा coda_link_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid sourceFid;	/* cnode to link *to* */
    काष्ठा CodaFid destFid;	/* Directory in which to place link */
    पूर्णांक tname;		/* Place holder क्रम data. */
पूर्ण;

काष्ठा coda_link_out अणु
    काष्ठा coda_out_hdr out;
पूर्ण;


/* coda_नाम: NO_OUT */
काष्ठा coda_नाम_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid sourceFid;
    पूर्णांक 	srcname;
    काष्ठा CodaFid destFid;
    पूर्णांक 	destname;
पूर्ण;

काष्ठा coda_नाम_out अणु
    काष्ठा coda_out_hdr out;
पूर्ण;

/* coda_सूची_गढ़ो: */
काष्ठा coda_सूची_गढ़ो_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    काष्ठा coda_vattr attr;
    पूर्णांक	   name;		/* Place holder क्रम data. */
पूर्ण;

काष्ठा coda_सूची_गढ़ो_out अणु
    काष्ठा coda_out_hdr oh;
    काष्ठा CodaFid VFid;
    काष्ठा coda_vattr attr;
पूर्ण;


/* coda_सूची_हटाओ: NO_OUT */
काष्ठा coda_सूची_हटाओ_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    पूर्णांक name;		/* Place holder क्रम data. */
पूर्ण;

काष्ठा coda_सूची_हटाओ_out अणु
    काष्ठा coda_out_hdr out;
पूर्ण;

/* coda_symlink: NO_OUT */
काष्ठा coda_symlink_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;	/* Directory to put symlink in */
    पूर्णांक srcname;
    काष्ठा coda_vattr attr;
    पूर्णांक tname;
पूर्ण;

काष्ठा coda_symlink_out अणु
    काष्ठा coda_out_hdr out;
पूर्ण;

/* coda_पढ़ोlink: */
काष्ठा coda_पढ़ोlink_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
पूर्ण;

काष्ठा coda_पढ़ोlink_out अणु
    काष्ठा coda_out_hdr oh;
    पूर्णांक	count;
    caddr_t	data;		/* Place holder क्रम data. */
पूर्ण;


/* coda_fsync: NO_OUT */
काष्ठा coda_fsync_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
पूर्ण;

काष्ठा coda_fsync_out अणु
    काष्ठा coda_out_hdr out;
पूर्ण;

/* coda_vget: */
काष्ठा coda_vget_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
पूर्ण;

काष्ठा coda_vget_out अणु
    काष्ठा coda_out_hdr oh;
    काष्ठा CodaFid VFid;
    पूर्णांक	vtype;
पूर्ण;


/* CODA_SIGNAL is out-of-band, करोesn't need data. */
/* CODA_INVALIDATE is a venus->kernel call */
/* CODA_FLUSH is a venus->kernel call */

/* coda_purgeuser: */
/* CODA_PURGEUSER is a venus->kernel call */
काष्ठा coda_purgeuser_out अणु
    काष्ठा coda_out_hdr oh;
    vuid_t uid;
पूर्ण;

/* coda_zapfile: */
/* CODA_ZAPखाता is a venus->kernel call */
काष्ठा coda_zapfile_out अणु  
    काष्ठा coda_out_hdr oh;
    काष्ठा CodaFid CodaFid;
पूर्ण;

/* coda_zapdir: */
/* CODA_ZAPसूची is a venus->kernel call */	
काष्ठा coda_zapdir_out अणु	  
    काष्ठा coda_out_hdr oh;
    काष्ठा CodaFid CodaFid;
पूर्ण;

/* coda_purgefid: */
/* CODA_PURGEFID is a venus->kernel call */	
काष्ठा coda_purgefid_out अणु 
    काष्ठा coda_out_hdr oh;
    काष्ठा CodaFid CodaFid;
पूर्ण;

/* coda_replace: */
/* CODA_REPLACE is a venus->kernel call */	
काष्ठा coda_replace_out अणु /* coda_replace is a venus->kernel call */
    काष्ठा coda_out_hdr oh;
    काष्ठा CodaFid NewFid;
    काष्ठा CodaFid OldFid;
पूर्ण;

/* coda_खोलो_by_fd: */
काष्ठा coda_खोलो_by_fd_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    पूर्णांक        flags;
पूर्ण;

काष्ठा coda_खोलो_by_fd_out अणु
    काष्ठा coda_out_hdr oh;
    पूर्णांक fd;

#अगर_घोषित __KERNEL__
    काष्ठा file *fh; /* not passed from userspace but used in-kernel only */
#पूर्ण_अगर
पूर्ण;

/* coda_खोलो_by_path: */
काष्ठा coda_खोलो_by_path_in अणु
    काष्ठा coda_in_hdr ih;
    काष्ठा CodaFid VFid;
    पूर्णांक	flags;
पूर्ण;

काष्ठा coda_खोलो_by_path_out अणु
    काष्ठा coda_out_hdr oh;
	पूर्णांक path;
पूर्ण;

/* coda_statfs: NO_IN */
काष्ठा coda_statfs_in अणु
    काष्ठा coda_in_hdr in;
पूर्ण;

काष्ठा coda_statfs_out अणु
    काष्ठा coda_out_hdr oh;
    काष्ठा coda_statfs stat;
पूर्ण;

#घोषणा CODA_ACCESS_TYPE_READ		1
#घोषणा CODA_ACCESS_TYPE_WRITE		2
#घोषणा CODA_ACCESS_TYPE_MMAP		3
#घोषणा CODA_ACCESS_TYPE_READ_FINISH	4
#घोषणा CODA_ACCESS_TYPE_WRITE_FINISH	5

/* coda_access_पूर्णांकent: NO_OUT */
काष्ठा coda_access_पूर्णांकent_in अणु
	काष्ठा coda_in_hdr ih;
	काष्ठा CodaFid VFid;
	पूर्णांक count;
	पूर्णांक pos;
	पूर्णांक type;
पूर्ण;

काष्ठा coda_access_पूर्णांकent_out अणु
	काष्ठा coda_out_hdr out;
पूर्ण;

/* 
 * Occasionally, we करोn't cache the fid वापसed by CODA_LOOKUP. 
 * For instance, अगर the fid is inconsistent. 
 * This हाल is handled by setting the top bit of the type result parameter.
 */
#घोषणा CODA_NOCACHE          0x80000000

जोड़ inputArgs अणु
    काष्ठा coda_in_hdr ih;		/* NB: every काष्ठा below begins with an ih */
    काष्ठा coda_खोलो_in coda_खोलो;
    काष्ठा coda_store_in coda_store;
    काष्ठा coda_release_in coda_release;
    काष्ठा coda_बंद_in coda_बंद;
    काष्ठा coda_ioctl_in coda_ioctl;
    काष्ठा coda_getattr_in coda_getattr;
    काष्ठा coda_setattr_in coda_setattr;
    काष्ठा coda_access_in coda_access;
    काष्ठा coda_lookup_in coda_lookup;
    काष्ठा coda_create_in coda_create;
    काष्ठा coda_हटाओ_in coda_हटाओ;
    काष्ठा coda_link_in coda_link;
    काष्ठा coda_नाम_in coda_नाम;
    काष्ठा coda_सूची_गढ़ो_in coda_सूची_गढ़ो;
    काष्ठा coda_सूची_हटाओ_in coda_सूची_हटाओ;
    काष्ठा coda_symlink_in coda_symlink;
    काष्ठा coda_पढ़ोlink_in coda_पढ़ोlink;
    काष्ठा coda_fsync_in coda_fsync;
    काष्ठा coda_vget_in coda_vget;
    काष्ठा coda_खोलो_by_fd_in coda_खोलो_by_fd;
    काष्ठा coda_खोलो_by_path_in coda_खोलो_by_path;
    काष्ठा coda_statfs_in coda_statfs;
    काष्ठा coda_access_पूर्णांकent_in coda_access_पूर्णांकent;
पूर्ण;

जोड़ outputArgs अणु
    काष्ठा coda_out_hdr oh;		/* NB: every काष्ठा below begins with an oh */
    काष्ठा coda_root_out coda_root;
    काष्ठा coda_खोलो_out coda_खोलो;
    काष्ठा coda_ioctl_out coda_ioctl;
    काष्ठा coda_getattr_out coda_getattr;
    काष्ठा coda_lookup_out coda_lookup;
    काष्ठा coda_create_out coda_create;
    काष्ठा coda_सूची_गढ़ो_out coda_सूची_गढ़ो;
    काष्ठा coda_पढ़ोlink_out coda_पढ़ोlink;
    काष्ठा coda_vget_out coda_vget;
    काष्ठा coda_purgeuser_out coda_purgeuser;
    काष्ठा coda_zapfile_out coda_zapfile;
    काष्ठा coda_zapdir_out coda_zapdir;
    काष्ठा coda_purgefid_out coda_purgefid;
    काष्ठा coda_replace_out coda_replace;
    काष्ठा coda_खोलो_by_fd_out coda_खोलो_by_fd;
    काष्ठा coda_खोलो_by_path_out coda_खोलो_by_path;
    काष्ठा coda_statfs_out coda_statfs;
पूर्ण;    

जोड़ coda_करोwncalls अणु
    /* CODA_INVALIDATE is a venus->kernel call */
    /* CODA_FLUSH is a venus->kernel call */
    काष्ठा coda_purgeuser_out purgeuser;
    काष्ठा coda_zapfile_out zapfile;
    काष्ठा coda_zapdir_out zapdir;
    काष्ठा coda_purgefid_out purgefid;
    काष्ठा coda_replace_out replace;
पूर्ण;


/*
 * Used क्रम identअगरying usage of "Control" and pioctls
 */

#घोषणा PIOCPARM_MASK 0x0000ffff
काष्ठा ViceIoctl अणु
        व्योम __user *in;        /* Data to be transferred in */
        व्योम __user *out;       /* Data to be transferred out */
        u_लघु in_size;        /* Size of input buffer <= 2K */
        u_लघु out_size;       /* Maximum size of output buffer, <= 2K */
पूर्ण;

काष्ठा PioctlData अणु
        स्थिर अक्षर __user *path;
        पूर्णांक follow;
        काष्ठा ViceIoctl vi;
पूर्ण;

#घोषणा CODA_CONTROL		".CONTROL"
#घोषणा CODA_CONTROLLEN		8
#घोषणा CTL_INO			-1

/* Data passed to mount */

#घोषणा CODA_MOUNT_VERSION 1

काष्ठा coda_mount_data अणु
	पूर्णांक		version;
	पूर्णांक		fd;       /* Opened device */
पूर्ण;

#पूर्ण_अगर /* _UAPI_CODA_HEADER_ */
