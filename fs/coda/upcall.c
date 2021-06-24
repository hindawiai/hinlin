<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mostly platक्रमm independent upcall operations to Venus:
 *  -- upcalls
 *  -- upcall routines
 *
 * Linux 2.0 version
 * Copyright (C) 1996 Peter J. Braam <braam@maths.ox.ac.uk>, 
 * Michael Callahan <callahan@maths.ox.ac.uk> 
 * 
 * Reकरोne क्रम Linux 2.1
 * Copyright (C) 1997 Carnegie Mellon University
 *
 * Carnegie Mellon University encourages users of this code to contribute
 * improvements to the Coda project. Contact Peter Braam <coda@cs.cmu.edu>.
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/vfs.h>

#समावेश <linux/coda.h>
#समावेश "coda_psdev.h"
#समावेश "coda_linux.h"
#समावेश "coda_cache.h"

#समावेश "coda_int.h"

अटल पूर्णांक coda_upcall(काष्ठा venus_comm *vc, पूर्णांक inSize, पूर्णांक *outSize,
		       जोड़ inputArgs *buffer);

अटल व्योम *alloc_upcall(पूर्णांक opcode, पूर्णांक size)
अणु
	जोड़ inputArgs *inp;

	inp = kvzalloc(size, GFP_KERNEL);
        अगर (!inp)
		वापस ERR_PTR(-ENOMEM);

        inp->ih.opcode = opcode;
	inp->ih.pid = task_pid_nr_ns(current, &init_pid_ns);
	inp->ih.pgid = task_pgrp_nr_ns(current, &init_pid_ns);
	inp->ih.uid = from_kuid(&init_user_ns, current_fsuid());

	वापस (व्योम*)inp;
पूर्ण

#घोषणा UPARG(op)\
करो अणु\
	inp = (जोड़ inputArgs *)alloc_upcall(op, insize); \
        अगर (IS_ERR(inp)) अणु वापस PTR_ERR(inp); पूर्ण\
        outp = (जोड़ outputArgs *)(inp); \
        outsize = insize; \
पूर्ण जबतक (0)

#घोषणा INSIZE(tag) माप(काष्ठा coda_ ## tag ## _in)
#घोषणा OUTSIZE(tag) माप(काष्ठा coda_ ## tag ## _out)
#घोषणा SIZE(tag)  max_t(अचिन्हित पूर्णांक, INSIZE(tag), OUTSIZE(tag))


/* the upcalls */
पूर्णांक venus_rootfid(काष्ठा super_block *sb, काष्ठा CodaFid *fidp)
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error;

        insize = SIZE(root);
        UPARG(CODA_ROOT);

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);
	अगर (!error)
		*fidp = outp->coda_root.VFid;

	kvमुक्त(inp);
	वापस error;
पूर्ण

पूर्णांक venus_getattr(काष्ठा super_block *sb, काष्ठा CodaFid *fid, 
		     काष्ठा coda_vattr *attr) 
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error;

        insize = SIZE(getattr); 
	UPARG(CODA_GETATTR);
        inp->coda_getattr.VFid = *fid;

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);
	अगर (!error)
		*attr = outp->coda_getattr.attr;

	kvमुक्त(inp);
        वापस error;
पूर्ण

पूर्णांक venus_setattr(काष्ठा super_block *sb, काष्ठा CodaFid *fid, 
		  काष्ठा coda_vattr *vattr)
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error;
	
	insize = SIZE(setattr);
	UPARG(CODA_SETATTR);

        inp->coda_setattr.VFid = *fid;
	inp->coda_setattr.attr = *vattr;

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);

	kvमुक्त(inp);
        वापस error;
पूर्ण

पूर्णांक venus_lookup(काष्ठा super_block *sb, काष्ठा CodaFid *fid, 
		    स्थिर अक्षर *name, पूर्णांक length, पूर्णांक * type, 
		    काष्ठा CodaFid *resfid)
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error;
	पूर्णांक offset;

	offset = INSIZE(lookup);
        insize = max_t(अचिन्हित पूर्णांक, offset + length +1, OUTSIZE(lookup));
	UPARG(CODA_LOOKUP);

        inp->coda_lookup.VFid = *fid;
	inp->coda_lookup.name = offset;
	inp->coda_lookup.flags = CLU_CASE_SENSITIVE;
        /* send Venus a null terminated string */
        स_नकल((अक्षर *)(inp) + offset, name, length);
        *((अक्षर *)inp + offset + length) = '\0';

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);
	अगर (!error) अणु
		*resfid = outp->coda_lookup.VFid;
		*type = outp->coda_lookup.vtype;
	पूर्ण

	kvमुक्त(inp);
	वापस error;
पूर्ण

पूर्णांक venus_बंद(काष्ठा super_block *sb, काष्ठा CodaFid *fid, पूर्णांक flags,
		kuid_t uid)
अणु
	जोड़ inputArgs *inp;
	जोड़ outputArgs *outp;
	पूर्णांक insize, outsize, error;
	
	insize = SIZE(release);
	UPARG(CODA_CLOSE);
	
	inp->ih.uid = from_kuid(&init_user_ns, uid);
        inp->coda_बंद.VFid = *fid;
        inp->coda_बंद.flags = flags;

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);

	kvमुक्त(inp);
        वापस error;
पूर्ण

पूर्णांक venus_खोलो(काष्ठा super_block *sb, काष्ठा CodaFid *fid,
		  पूर्णांक flags, काष्ठा file **fh)
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error;
       
	insize = SIZE(खोलो_by_fd);
	UPARG(CODA_OPEN_BY_FD);

	inp->coda_खोलो_by_fd.VFid = *fid;
	inp->coda_खोलो_by_fd.flags = flags;

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);
	अगर (!error)
		*fh = outp->coda_खोलो_by_fd.fh;

	kvमुक्त(inp);
	वापस error;
पूर्ण	

पूर्णांक venus_सूची_गढ़ो(काष्ठा super_block *sb, काष्ठा CodaFid *dirfid, 
		   स्थिर अक्षर *name, पूर्णांक length, 
		   काष्ठा CodaFid *newfid, काष्ठा coda_vattr *attrs)
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error;
        पूर्णांक offset;

	offset = INSIZE(सूची_गढ़ो);
	insize = max_t(अचिन्हित पूर्णांक, offset + length + 1, OUTSIZE(सूची_गढ़ो));
	UPARG(CODA_MKसूची);

        inp->coda_सूची_गढ़ो.VFid = *dirfid;
        inp->coda_सूची_गढ़ो.attr = *attrs;
	inp->coda_सूची_गढ़ो.name = offset;
        /* Venus must get null terminated string */
        स_नकल((अक्षर *)(inp) + offset, name, length);
        *((अक्षर *)inp + offset + length) = '\0';

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);
	अगर (!error) अणु
		*attrs = outp->coda_सूची_गढ़ो.attr;
		*newfid = outp->coda_सूची_गढ़ो.VFid;
	पूर्ण

	kvमुक्त(inp);
	वापस error;        
पूर्ण


पूर्णांक venus_नाम(काष्ठा super_block *sb, काष्ठा CodaFid *old_fid, 
		 काष्ठा CodaFid *new_fid, माप_प्रकार old_length, 
		 माप_प्रकार new_length, स्थिर अक्षर *old_name, 
		 स्थिर अक्षर *new_name)
अणु
	जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error; 
	पूर्णांक offset, s;
	
	offset = INSIZE(नाम);
	insize = max_t(अचिन्हित पूर्णांक, offset + new_length + old_length + 8,
		     OUTSIZE(नाम)); 
 	UPARG(CODA_RENAME);

        inp->coda_नाम.sourceFid = *old_fid;
        inp->coda_नाम.destFid =  *new_fid;
        inp->coda_नाम.srcname = offset;

        /* Venus must receive an null terminated string */
        s = ( old_length & ~0x3) +4; /* round up to word boundary */
        स_नकल((अक्षर *)(inp) + offset, old_name, old_length);
        *((अक्षर *)inp + offset + old_length) = '\0';

        /* another null terminated string क्रम Venus */
        offset += s;
        inp->coda_नाम.destname = offset;
        s = ( new_length & ~0x3) +4; /* round up to word boundary */
        स_नकल((अक्षर *)(inp) + offset, new_name, new_length);
        *((अक्षर *)inp + offset + new_length) = '\0';

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);

	kvमुक्त(inp);
	वापस error;
पूर्ण

पूर्णांक venus_create(काष्ठा super_block *sb, काष्ठा CodaFid *dirfid, 
		 स्थिर अक्षर *name, पूर्णांक length, पूर्णांक excl, पूर्णांक mode,
		 काष्ठा CodaFid *newfid, काष्ठा coda_vattr *attrs) 
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error;
        पूर्णांक offset;

        offset = INSIZE(create);
	insize = max_t(अचिन्हित पूर्णांक, offset + length + 1, OUTSIZE(create));
	UPARG(CODA_CREATE);

        inp->coda_create.VFid = *dirfid;
        inp->coda_create.attr.va_mode = mode;
	inp->coda_create.excl = excl;
        inp->coda_create.mode = mode;
        inp->coda_create.name = offset;

        /* Venus must get null terminated string */
        स_नकल((अक्षर *)(inp) + offset, name, length);
        *((अक्षर *)inp + offset + length) = '\0';

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);
	अगर (!error) अणु
		*attrs = outp->coda_create.attr;
		*newfid = outp->coda_create.VFid;
	पूर्ण

	kvमुक्त(inp);
	वापस error;        
पूर्ण

पूर्णांक venus_सूची_हटाओ(काष्ठा super_block *sb, काष्ठा CodaFid *dirfid, 
		    स्थिर अक्षर *name, पूर्णांक length)
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error;
        पूर्णांक offset;

        offset = INSIZE(सूची_हटाओ);
	insize = max_t(अचिन्हित पूर्णांक, offset + length + 1, OUTSIZE(सूची_हटाओ));
	UPARG(CODA_RMसूची);

        inp->coda_सूची_हटाओ.VFid = *dirfid;
        inp->coda_सूची_हटाओ.name = offset;
        स_नकल((अक्षर *)(inp) + offset, name, length);
	*((अक्षर *)inp + offset + length) = '\0';

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);

	kvमुक्त(inp);
	वापस error;
पूर्ण

पूर्णांक venus_हटाओ(काष्ठा super_block *sb, काष्ठा CodaFid *dirfid, 
		    स्थिर अक्षर *name, पूर्णांक length)
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक error=0, insize, outsize, offset;

        offset = INSIZE(हटाओ);
	insize = max_t(अचिन्हित पूर्णांक, offset + length + 1, OUTSIZE(हटाओ));
	UPARG(CODA_REMOVE);

        inp->coda_हटाओ.VFid = *dirfid;
        inp->coda_हटाओ.name = offset;
        स_नकल((अक्षर *)(inp) + offset, name, length);
	*((अक्षर *)inp + offset + length) = '\0';

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);

	kvमुक्त(inp);
	वापस error;
पूर्ण

पूर्णांक venus_पढ़ोlink(काष्ठा super_block *sb, काष्ठा CodaFid *fid, 
		      अक्षर *buffer, पूर्णांक *length)
अणु 
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error;
        पूर्णांक retlen;
        अक्षर *result;
        
	insize = max_t(अचिन्हित पूर्णांक,
		     INSIZE(पढ़ोlink), OUTSIZE(पढ़ोlink)+ *length);
	UPARG(CODA_READLINK);

        inp->coda_पढ़ोlink.VFid = *fid;

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);
	अगर (!error) अणु
		retlen = outp->coda_पढ़ोlink.count;
		अगर (retlen >= *length)
			retlen = *length - 1;
		*length = retlen;
		result =  (अक्षर *)outp + (दीर्घ)outp->coda_पढ़ोlink.data;
		स_नकल(buffer, result, retlen);
		*(buffer + retlen) = '\0';
	पूर्ण

	kvमुक्त(inp);
        वापस error;
पूर्ण



पूर्णांक venus_link(काष्ठा super_block *sb, काष्ठा CodaFid *fid, 
		  काष्ठा CodaFid *dirfid, स्थिर अक्षर *name, पूर्णांक len )
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error;
        पूर्णांक offset;

	offset = INSIZE(link);
	insize = max_t(अचिन्हित पूर्णांक, offset  + len + 1, OUTSIZE(link));
        UPARG(CODA_LINK);

        inp->coda_link.sourceFid = *fid;
        inp->coda_link.destFid = *dirfid;
        inp->coda_link.tname = offset;

        /* make sure strings are null terminated */
        स_नकल((अक्षर *)(inp) + offset, name, len);
        *((अक्षर *)inp + offset + len) = '\0';

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);

	kvमुक्त(inp);
        वापस error;
पूर्ण

पूर्णांक venus_symlink(काष्ठा super_block *sb, काष्ठा CodaFid *fid,
		     स्थिर अक्षर *name, पूर्णांक len,
		     स्थिर अक्षर *symname, पूर्णांक symlen)
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error;
        पूर्णांक offset, s;

        offset = INSIZE(symlink);
	insize = max_t(अचिन्हित पूर्णांक, offset + len + symlen + 8, OUTSIZE(symlink));
	UPARG(CODA_SYMLINK);
        
        /*        inp->coda_symlink.attr = *tva; XXXXXX */ 
        inp->coda_symlink.VFid = *fid;

	/* Round up to word boundary and null terminate */
        inp->coda_symlink.srcname = offset;
        s = ( symlen  & ~0x3 ) + 4; 
        स_नकल((अक्षर *)(inp) + offset, symname, symlen);
        *((अक्षर *)inp + offset + symlen) = '\0';
        
	/* Round up to word boundary and null terminate */
        offset += s;
        inp->coda_symlink.tname = offset;
        s = (len & ~0x3) + 4;
        स_नकल((अक्षर *)(inp) + offset, name, len);
        *((अक्षर *)inp + offset + len) = '\0';

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);

	kvमुक्त(inp);
        वापस error;
पूर्ण

पूर्णांक venus_fsync(काष्ठा super_block *sb, काष्ठा CodaFid *fid)
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp; 
	पूर्णांक insize, outsize, error;
	
	insize=SIZE(fsync);
	UPARG(CODA_FSYNC);

	inp->coda_fsync.VFid = *fid;
	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);

	kvमुक्त(inp);
	वापस error;
पूर्ण

पूर्णांक venus_access(काष्ठा super_block *sb, काष्ठा CodaFid *fid, पूर्णांक mask)
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp; 
	पूर्णांक insize, outsize, error;

	insize = SIZE(access);
	UPARG(CODA_ACCESS);

        inp->coda_access.VFid = *fid;
        inp->coda_access.flags = mask;

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);

	kvमुक्त(inp);
	वापस error;
पूर्ण


पूर्णांक venus_pioctl(काष्ठा super_block *sb, काष्ठा CodaFid *fid,
		 अचिन्हित पूर्णांक cmd, काष्ठा PioctlData *data)
अणु
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;  
	पूर्णांक insize, outsize, error;
	पूर्णांक iocsize;

	insize = VC_MAXMSGSIZE;
	UPARG(CODA_IOCTL);

        /* build packet क्रम Venus */
        अगर (data->vi.in_size > VC_MAXDATASIZE) अणु
		error = -EINVAL;
		जाओ निकास;
        पूर्ण

        अगर (data->vi.out_size > VC_MAXDATASIZE) अणु
		error = -EINVAL;
		जाओ निकास;
	पूर्ण

        inp->coda_ioctl.VFid = *fid;
    
        /* the cmd field was mutated by increasing its size field to
         * reflect the path and follow args. We need to subtract that
         * out beक्रमe sending the command to Venus.  */
        inp->coda_ioctl.cmd = (cmd & ~(PIOCPARM_MASK << 16));	
        iocsize = ((cmd >> 16) & PIOCPARM_MASK) - माप(अक्षर *) - माप(पूर्णांक);
        inp->coda_ioctl.cmd |= (iocsize & PIOCPARM_MASK) <<	16;	
    
        /* in->coda_ioctl.rwflag = flag; */
        inp->coda_ioctl.len = data->vi.in_size;
        inp->coda_ioctl.data = (अक्षर *)(INSIZE(ioctl));
     
        /* get the data out of user space */
	अगर (copy_from_user((अक्षर *)inp + (दीर्घ)inp->coda_ioctl.data,
			   data->vi.in, data->vi.in_size)) अणु
		error = -EINVAL;
	        जाओ निकास;
	पूर्ण

	error = coda_upcall(coda_vcp(sb), SIZE(ioctl) + data->vi.in_size,
			    &outsize, inp);

        अगर (error) अणु
		pr_warn("%s: Venus returns: %d for %s\n",
			__func__, error, coda_f2s(fid));
		जाओ निकास; 
	पूर्ण

	अगर (outsize < (दीर्घ)outp->coda_ioctl.data + outp->coda_ioctl.len) अणु
		error = -EINVAL;
		जाओ निकास;
	पूर्ण
        
	/* Copy out the OUT buffer. */
        अगर (outp->coda_ioctl.len > data->vi.out_size) अणु
		error = -EINVAL;
		जाओ निकास;
        पूर्ण

	/* Copy out the OUT buffer. */
	अगर (copy_to_user(data->vi.out,
			 (अक्षर *)outp + (दीर्घ)outp->coda_ioctl.data,
			 outp->coda_ioctl.len)) अणु
		error = -EFAULT;
		जाओ निकास;
	पूर्ण

 निकास:
	kvमुक्त(inp);
	वापस error;
पूर्ण

पूर्णांक venus_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *sfs)
अणु 
        जोड़ inputArgs *inp;
        जोड़ outputArgs *outp;
        पूर्णांक insize, outsize, error;
        
	insize = SIZE(statfs);
	UPARG(CODA_STATFS);

	error = coda_upcall(coda_vcp(dentry->d_sb), insize, &outsize, inp);
	अगर (!error) अणु
		sfs->f_blocks = outp->coda_statfs.stat.f_blocks;
		sfs->f_bमुक्त  = outp->coda_statfs.stat.f_bमुक्त;
		sfs->f_bavail = outp->coda_statfs.stat.f_bavail;
		sfs->f_files  = outp->coda_statfs.stat.f_files;
		sfs->f_fमुक्त  = outp->coda_statfs.stat.f_fमुक्त;
	पूर्ण

	kvमुक्त(inp);
        वापस error;
पूर्ण

पूर्णांक venus_access_पूर्णांकent(काष्ठा super_block *sb, काष्ठा CodaFid *fid,
			bool *access_पूर्णांकent_supported,
			माप_प्रकार count, loff_t ppos, पूर्णांक type)
अणु
	जोड़ inputArgs *inp;
	जोड़ outputArgs *outp;
	पूर्णांक insize, outsize, error;
	bool finalizer =
		type == CODA_ACCESS_TYPE_READ_FINISH ||
		type == CODA_ACCESS_TYPE_WRITE_FINISH;

	अगर (!*access_पूर्णांकent_supported && !finalizer)
		वापस 0;

	insize = SIZE(access_पूर्णांकent);
	UPARG(CODA_ACCESS_INTENT);

	inp->coda_access_पूर्णांकent.VFid = *fid;
	inp->coda_access_पूर्णांकent.count = count;
	inp->coda_access_पूर्णांकent.pos = ppos;
	inp->coda_access_पूर्णांकent.type = type;

	error = coda_upcall(coda_vcp(sb), insize,
			    finalizer ? शून्य : &outsize, inp);

	/*
	 * we have to मुक्त the request buffer क्रम synchronous upcalls
	 * or when asynchronous upcalls fail, but not when asynchronous
	 * upcalls succeed
	 */
	अगर (!finalizer || error)
		kvमुक्त(inp);

	/* Chunked access is not supported or an old Coda client */
	अगर (error == -EOPNOTSUPP) अणु
		*access_पूर्णांकent_supported = false;
		error = 0;
	पूर्ण
	वापस error;
पूर्ण

/*
 * coda_upcall and coda_करोwncall routines.
 */
अटल व्योम coda_block_संकेतs(sigset_t *old)
अणु
	spin_lock_irq(&current->sighand->siglock);
	*old = current->blocked;

	sigfillset(&current->blocked);
	sigdअन्यथाt(&current->blocked, SIGKILL);
	sigdअन्यथाt(&current->blocked, SIGSTOP);
	sigdअन्यथाt(&current->blocked, संक_विघ्न);

	recalc_संक_बाकी();
	spin_unlock_irq(&current->sighand->siglock);
पूर्ण

अटल व्योम coda_unblock_संकेतs(sigset_t *old)
अणु
	spin_lock_irq(&current->sighand->siglock);
	current->blocked = *old;
	recalc_संक_बाकी();
	spin_unlock_irq(&current->sighand->siglock);
पूर्ण

/* Don't allow संकेतs to पूर्णांकerrupt the following upcalls beक्रमe venus
 * has seen them,
 * - CODA_CLOSE or CODA_RELEASE upcall  (to aव्योम reference count problems)
 * - CODA_STORE				(to aव्योम data loss)
 * - CODA_ACCESS_INTENT                 (to aव्योम reference count problems)
 */
#घोषणा CODA_INTERRUPTIBLE(r) (!coda_hard && \
			       (((r)->uc_opcode != CODA_CLOSE && \
				 (r)->uc_opcode != CODA_STORE && \
				 (r)->uc_opcode != CODA_ACCESS_INTENT && \
				 (r)->uc_opcode != CODA_RELEASE) || \
				(r)->uc_flags & CODA_REQ_READ))

अटल अंतरभूत व्योम coda_रुकोक्रम_upcall(काष्ठा venus_comm *vcp,
				       काष्ठा upc_req *req)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	अचिन्हित दीर्घ समयout = jअगरfies + coda_समयout * HZ;
	sigset_t old;
	पूर्णांक blocked;

	coda_block_संकेतs(&old);
	blocked = 1;

	add_रुको_queue(&req->uc_sleep, &रुको);
	क्रम (;;) अणु
		अगर (CODA_INTERRUPTIBLE(req))
			set_current_state(TASK_INTERRUPTIBLE);
		अन्यथा
			set_current_state(TASK_UNINTERRUPTIBLE);

		/* got a reply */
		अगर (req->uc_flags & (CODA_REQ_WRITE | CODA_REQ_ABORT))
			अवरोध;

		अगर (blocked && समय_after(jअगरfies, समयout) &&
		    CODA_INTERRUPTIBLE(req))
		अणु
			coda_unblock_संकेतs(&old);
			blocked = 0;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			list_del(&req->uc_chain);
			अवरोध;
		पूर्ण

		mutex_unlock(&vcp->vc_mutex);
		अगर (blocked)
			schedule_समयout(HZ);
		अन्यथा
			schedule();
		mutex_lock(&vcp->vc_mutex);
	पूर्ण
	अगर (blocked)
		coda_unblock_संकेतs(&old);

	हटाओ_रुको_queue(&req->uc_sleep, &रुको);
	set_current_state(TASK_RUNNING);
पूर्ण


/*
 * coda_upcall will वापस an error in the हाल of
 * failed communication with Venus _or_ will peek at Venus
 * reply and वापस Venus' error.
 *
 * As venus has 2 types of errors, normal errors (positive) and पूर्णांकernal
 * errors (negative), normal errors are negated, जबतक पूर्णांकernal errors
 * are all mapped to -EINTR, जबतक showing a nice warning message. (jh)
 */
अटल पूर्णांक coda_upcall(काष्ठा venus_comm *vcp,
		       पूर्णांक inSize, पूर्णांक *outSize,
		       जोड़ inputArgs *buffer)
अणु
	जोड़ outputArgs *out;
	जोड़ inputArgs *sig_inputArgs;
	काष्ठा upc_req *req = शून्य, *sig_req;
	पूर्णांक error;

	mutex_lock(&vcp->vc_mutex);

	अगर (!vcp->vc_inuse) अणु
		pr_notice("Venus dead, not sending upcall\n");
		error = -ENXIO;
		जाओ निकास;
	पूर्ण

	/* Format the request message. */
	req = kदो_स्मृति(माप(काष्ठा upc_req), GFP_KERNEL);
	अगर (!req) अणु
		error = -ENOMEM;
		जाओ निकास;
	पूर्ण

	buffer->ih.unique = ++vcp->vc_seq;

	req->uc_data = (व्योम *)buffer;
	req->uc_flags = outSize ? 0 : CODA_REQ_ASYNC;
	req->uc_inSize = inSize;
	req->uc_outSize = (outSize && *outSize) ? *outSize : inSize;
	req->uc_opcode = buffer->ih.opcode;
	req->uc_unique = buffer->ih.unique;
	init_रुकोqueue_head(&req->uc_sleep);

	/* Append msg to pending queue and poke Venus. */
	list_add_tail(&req->uc_chain, &vcp->vc_pending);
	wake_up_पूर्णांकerruptible(&vcp->vc_रुकोq);

	अगर (req->uc_flags & CODA_REQ_ASYNC) अणु
		mutex_unlock(&vcp->vc_mutex);
		वापस 0;
	पूर्ण

	/* We can be पूर्णांकerrupted जबतक we रुको क्रम Venus to process
	 * our request.  If the पूर्णांकerrupt occurs beक्रमe Venus has पढ़ो
	 * the request, we dequeue and वापस. If it occurs after the
	 * पढ़ो but beक्रमe the reply, we dequeue, send a संकेत
	 * message, and वापस. If it occurs after the reply we ignore
	 * it. In no हाल करो we want to restart the syscall.  If it
	 * was पूर्णांकerrupted by a venus shutकरोwn (psdev_बंद), वापस
	 * ENODEV.  */

	/* Go to sleep.  Wake up on संकेतs only after the समयout. */
	coda_रुकोक्रम_upcall(vcp, req);

	/* Op went through, पूर्णांकerrupt or not... */
	अगर (req->uc_flags & CODA_REQ_WRITE) अणु
		out = (जोड़ outputArgs *)req->uc_data;
		/* here we map positive Venus errors to kernel errors */
		error = -out->oh.result;
		*outSize = req->uc_outSize;
		जाओ निकास;
	पूर्ण

	error = -EINTR;
	अगर ((req->uc_flags & CODA_REQ_ABORT) || !संकेत_pending(current)) अणु
		pr_warn("Unexpected interruption.\n");
		जाओ निकास;
	पूर्ण

	/* Interrupted beक्रमe venus पढ़ो it. */
	अगर (!(req->uc_flags & CODA_REQ_READ))
		जाओ निकास;

	/* Venus saw the upcall, make sure we can send पूर्णांकerrupt संकेत */
	अगर (!vcp->vc_inuse) अणु
		pr_info("Venus dead, not sending signal.\n");
		जाओ निकास;
	पूर्ण

	error = -ENOMEM;
	sig_req = kदो_स्मृति(माप(काष्ठा upc_req), GFP_KERNEL);
	अगर (!sig_req) जाओ निकास;

	sig_inputArgs = kvzalloc(माप(काष्ठा coda_in_hdr), GFP_KERNEL);
	अगर (!sig_inputArgs) अणु
		kमुक्त(sig_req);
		जाओ निकास;
	पूर्ण

	error = -EINTR;
	sig_inputArgs->ih.opcode = CODA_SIGNAL;
	sig_inputArgs->ih.unique = req->uc_unique;

	sig_req->uc_flags = CODA_REQ_ASYNC;
	sig_req->uc_opcode = sig_inputArgs->ih.opcode;
	sig_req->uc_unique = sig_inputArgs->ih.unique;
	sig_req->uc_data = (व्योम *)sig_inputArgs;
	sig_req->uc_inSize = माप(काष्ठा coda_in_hdr);
	sig_req->uc_outSize = माप(काष्ठा coda_in_hdr);

	/* insert at head of queue! */
	list_add(&(sig_req->uc_chain), &vcp->vc_pending);
	wake_up_पूर्णांकerruptible(&vcp->vc_रुकोq);

निकास:
	kमुक्त(req);
	mutex_unlock(&vcp->vc_mutex);
	वापस error;
पूर्ण

/*  
    The statements below are part of the Coda opportunistic
    programming -- taken from the Mach/BSD kernel code क्रम Coda. 
    You करोn't get correct semantics by stating what needs to be
    करोne without guaranteeing the invariants needed क्रम it to happen.
    When will be have समय to find out what exactly is going on?  (pjb)
*/


/* 
 * There are 7 हालs where cache invalidations occur.  The semantics
 *  of each is listed here:
 *
 * CODA_FLUSH     -- flush all entries from the name cache and the cnode cache.
 * CODA_PURGEUSER -- flush all entries from the name cache क्रम a specअगरic user
 *                  This call is a result of token expiration.
 *
 * The next arise as the result of callbacks on a file or directory.
 * CODA_ZAPखाता   -- flush the cached attributes क्रम a file.

 * CODA_ZAPसूची    -- flush the attributes क्रम the dir and
 *                  क्रमce a new lookup क्रम all the children
                    of this dir.

 *
 * The next is a result of Venus detecting an inconsistent file.
 * CODA_PURGEFID  -- flush the attribute क्रम the file
 *                  purge it and its children from the dcache
 *
 * The last  allows Venus to replace local fids with global ones
 * during reपूर्णांकegration.
 *
 * CODA_REPLACE -- replace one CodaFid with another throughout the name cache */

पूर्णांक coda_करोwncall(काष्ठा venus_comm *vcp, पूर्णांक opcode, जोड़ outputArgs *out,
		  माप_प्रकार nbytes)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा CodaFid *fid = शून्य, *newfid;
	काष्ठा super_block *sb;

	/*
	 * Make sure we have received enough data from the cache
	 * manager to populate the necessary fields in the buffer
	 */
	चयन (opcode) अणु
	हाल CODA_PURGEUSER:
		अगर (nbytes < माप(काष्ठा coda_purgeuser_out))
			वापस -EINVAL;
		अवरोध;

	हाल CODA_ZAPसूची:
		अगर (nbytes < माप(काष्ठा coda_zapdir_out))
			वापस -EINVAL;
		अवरोध;

	हाल CODA_ZAPखाता:
		अगर (nbytes < माप(काष्ठा coda_zapfile_out))
			वापस -EINVAL;
		अवरोध;

	हाल CODA_PURGEFID:
		अगर (nbytes < माप(काष्ठा coda_purgefid_out))
			वापस -EINVAL;
		अवरोध;

	हाल CODA_REPLACE:
		अगर (nbytes < माप(काष्ठा coda_replace_out))
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	/* Handle invalidation requests. */
	mutex_lock(&vcp->vc_mutex);
	sb = vcp->vc_sb;
	अगर (!sb || !sb->s_root)
		जाओ unlock_out;

	चयन (opcode) अणु
	हाल CODA_FLUSH:
		coda_cache_clear_all(sb);
		shrink_dcache_sb(sb);
		अगर (d_really_is_positive(sb->s_root))
			coda_flag_inode(d_inode(sb->s_root), C_FLUSH);
		अवरोध;

	हाल CODA_PURGEUSER:
		coda_cache_clear_all(sb);
		अवरोध;

	हाल CODA_ZAPसूची:
		fid = &out->coda_zapdir.CodaFid;
		अवरोध;

	हाल CODA_ZAPखाता:
		fid = &out->coda_zapfile.CodaFid;
		अवरोध;

	हाल CODA_PURGEFID:
		fid = &out->coda_purgefid.CodaFid;
		अवरोध;

	हाल CODA_REPLACE:
		fid = &out->coda_replace.OldFid;
		अवरोध;
	पूर्ण
	अगर (fid)
		inode = coda_fid_to_inode(fid, sb);

unlock_out:
	mutex_unlock(&vcp->vc_mutex);

	अगर (!inode)
		वापस 0;

	चयन (opcode) अणु
	हाल CODA_ZAPसूची:
		coda_flag_inode_children(inode, C_PURGE);
		coda_flag_inode(inode, C_VATTR);
		अवरोध;

	हाल CODA_ZAPखाता:
		coda_flag_inode(inode, C_VATTR);
		अवरोध;

	हाल CODA_PURGEFID:
		coda_flag_inode_children(inode, C_PURGE);

		/* catch the dentries later अगर some are still busy */
		coda_flag_inode(inode, C_PURGE);
		d_prune_aliases(inode);
		अवरोध;

	हाल CODA_REPLACE:
		newfid = &out->coda_replace.NewFid;
		coda_replace_fid(inode, fid, newfid);
		अवरोध;
	पूर्ण
	iput(inode);
	वापस 0;
पूर्ण
