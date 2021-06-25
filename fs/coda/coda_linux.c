<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Inode operations क्रम Coda fileप्रणाली
 * Original version: (C) 1996 P. Braam and M. Callahan
 * Rewritten क्रम Linux 2.1. (C) 1997 Carnegie Mellon University
 * 
 * Carnegie Mellon encourages users to contribute improvements to
 * the Coda project. Contact Peter Braam (coda@cs.cmu.edu).
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/माला.स>

#समावेश <linux/coda.h>
#समावेश "coda_psdev.h"
#समावेश "coda_linux.h"

/* initialize the debugging variables */
पूर्णांक coda_fake_statfs;

/* prपूर्णांक a fid */
अक्षर * coda_f2s(काष्ठा CodaFid *f)
अणु
	अटल अक्षर s[60];

 	प्र_लिखो(s, "(%08x.%08x.%08x.%08x)", f->opaque[0], f->opaque[1], f->opaque[2], f->opaque[3]);

	वापस s;
पूर्ण

/* recognize special .CONTROL name */
पूर्णांक coda_iscontrol(स्थिर अक्षर *name, माप_प्रकार length)
अणु
	वापस ((CODA_CONTROLLEN == length) && 
                (म_भेदन(name, CODA_CONTROL, CODA_CONTROLLEN) == 0));
पूर्ण

अचिन्हित लघु coda_flags_to_cflags(अचिन्हित लघु flags)
अणु
	अचिन्हित लघु coda_flags = 0;
	
	अगर ((flags & O_ACCMODE) == O_RDONLY)
		coda_flags |= C_O_READ;

	अगर ((flags & O_ACCMODE) == O_RDWR)
		coda_flags |= C_O_READ | C_O_WRITE;

	अगर ((flags & O_ACCMODE) == O_WRONLY)
		coda_flags |= C_O_WRITE;

	अगर (flags & O_TRUNC)
		coda_flags |= C_O_TRUNC;

	अगर (flags & O_CREAT)
		coda_flags |= C_O_CREAT;

	अगर (flags & O_EXCL)
		coda_flags |= C_O_EXCL;

	वापस coda_flags;
पूर्ण

अटल काष्ठा बारpec64 coda_to_बारpec64(काष्ठा coda_बारpec ts)
अणु
	काष्ठा बारpec64 ts64 = अणु
		.tv_sec = ts.tv_sec,
		.tv_nsec = ts.tv_nsec,
	पूर्ण;

	वापस ts64;
पूर्ण

अटल काष्ठा coda_बारpec बारpec64_to_coda(काष्ठा बारpec64 ts64)
अणु
	काष्ठा coda_बारpec ts = अणु
		.tv_sec = ts64.tv_sec,
		.tv_nsec = ts64.tv_nsec,
	पूर्ण;

	वापस ts;
पूर्ण

/* utility functions below */
व्योम coda_vattr_to_iattr(काष्ठा inode *inode, काष्ठा coda_vattr *attr)
अणु
        पूर्णांक inode_type;
        /* inode's i_flags, i_ino are set by iget 
           XXX: is this all we need ??
           */
        चयन (attr->va_type) अणु
        हाल C_VNON:
                inode_type  = 0;
                अवरोध;
        हाल C_VREG:
                inode_type = S_IFREG;
                अवरोध;
        हाल C_Vसूची:
                inode_type = S_IFसूची;
                अवरोध;
        हाल C_VLNK:
                inode_type = S_IFLNK;
                अवरोध;
        शेष:
                inode_type = 0;
        पूर्ण
	inode->i_mode |= inode_type;

	अगर (attr->va_mode != (u_लघु) -1)
	        inode->i_mode = attr->va_mode | inode_type;
        अगर (attr->va_uid != -1) 
	        inode->i_uid = make_kuid(&init_user_ns, (uid_t) attr->va_uid);
        अगर (attr->va_gid != -1)
	        inode->i_gid = make_kgid(&init_user_ns, (gid_t) attr->va_gid);
	अगर (attr->va_nlink != -1)
		set_nlink(inode, attr->va_nlink);
	अगर (attr->va_size != -1)
	        inode->i_size = attr->va_size;
	अगर (attr->va_size != -1)
		inode->i_blocks = (attr->va_size + 511) >> 9;
	अगर (attr->va_aसमय.tv_sec != -1) 
		inode->i_aसमय = coda_to_बारpec64(attr->va_aसमय);
	अगर (attr->va_mसमय.tv_sec != -1)
		inode->i_mसमय = coda_to_बारpec64(attr->va_mसमय);
        अगर (attr->va_स_समय.tv_sec != -1)
		inode->i_स_समय = coda_to_बारpec64(attr->va_स_समय);
पूर्ण


/* 
 * BSD sets attributes that need not be modअगरied to -1. 
 * Linux uses the valid field to indicate what should be
 * looked at.  The BSD type field needs to be deduced from linux 
 * mode.
 * So we have to करो some translations here.
 */

व्योम coda_iattr_to_vattr(काष्ठा iattr *iattr, काष्ठा coda_vattr *vattr)
अणु
        अचिन्हित पूर्णांक valid;

        /* clean out */        
	vattr->va_mode = -1;
        vattr->va_uid = (vuid_t) -1; 
        vattr->va_gid = (vgid_t) -1;
        vattr->va_size = (off_t) -1;
	vattr->va_aसमय.tv_sec = (पूर्णांक64_t) -1;
	vattr->va_aसमय.tv_nsec = (दीर्घ) -1;
	vattr->va_mसमय.tv_sec = (पूर्णांक64_t) -1;
	vattr->va_mसमय.tv_nsec = (दीर्घ) -1;
	vattr->va_स_समय.tv_sec = (पूर्णांक64_t) -1;
	vattr->va_स_समय.tv_nsec = (दीर्घ) -1;
        vattr->va_type = C_VNON;
	vattr->va_fileid = -1;
	vattr->va_gen = -1;
	vattr->va_bytes = -1;
	vattr->va_nlink = -1;
	vattr->va_blocksize = -1;
	vattr->va_rdev = -1;
        vattr->va_flags = 0;

        /* determine the type */
#अगर 0
        mode = iattr->ia_mode;
                अगर ( S_ISसूची(mode) ) अणु
                vattr->va_type = C_Vसूची; 
        पूर्ण अन्यथा अगर ( S_ISREG(mode) ) अणु
                vattr->va_type = C_VREG;
        पूर्ण अन्यथा अगर ( S_ISLNK(mode) ) अणु
                vattr->va_type = C_VLNK;
        पूर्ण अन्यथा अणु
                /* करोn't करो others */
                vattr->va_type = C_VNON;
        पूर्ण
#पूर्ण_अगर 

        /* set those vattrs that need change */
        valid = iattr->ia_valid;
        अगर ( valid & ATTR_MODE ) अणु
                vattr->va_mode = iattr->ia_mode;
	पूर्ण
        अगर ( valid & ATTR_UID ) अणु
                vattr->va_uid = (vuid_t) from_kuid(&init_user_ns, iattr->ia_uid);
	पूर्ण
        अगर ( valid & ATTR_GID ) अणु
                vattr->va_gid = (vgid_t) from_kgid(&init_user_ns, iattr->ia_gid);
	पूर्ण
        अगर ( valid & ATTR_SIZE ) अणु
                vattr->va_size = iattr->ia_size;
	पूर्ण
        अगर ( valid & ATTR_ATIME ) अणु
		vattr->va_aसमय = बारpec64_to_coda(iattr->ia_aसमय);
	पूर्ण
        अगर ( valid & ATTR_MTIME ) अणु
		vattr->va_mसमय = बारpec64_to_coda(iattr->ia_mसमय);
	पूर्ण
        अगर ( valid & ATTR_CTIME ) अणु
		vattr->va_स_समय = बारpec64_to_coda(iattr->ia_स_समय);
	पूर्ण
पूर्ण

