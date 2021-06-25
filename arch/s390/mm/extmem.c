<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author(s)......: Carsten Otte <cotte@de.ibm.com>
 * 		    Rob M van der Heij <rvdheij@nl.ibm.com>
 * 		    Steven Shultz <shultzss@us.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 2002, 2004
 */

#घोषणा KMSG_COMPONENT "extmem"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/memblock.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/ioport.h>
#समावेश <linux/refcount.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/exपंचांगem.h>
#समावेश <यंत्र/cpcmd.h>
#समावेश <यंत्र/setup.h>

#घोषणा DCSS_PURGESEG   0x08
#घोषणा DCSS_LOADSHRX	0x20
#घोषणा DCSS_LOADNSRX	0x24
#घोषणा DCSS_FINDSEGX	0x2c
#घोषणा DCSS_SEGEXTX	0x38
#घोषणा DCSS_FINDSEGA   0x0c

काष्ठा qrange अणु
	अचिन्हित दीर्घ  start; /* last byte type */
	अचिन्हित दीर्घ  end;   /* last byte reserved */
पूर्ण;

काष्ठा qout64 अणु
	अचिन्हित दीर्घ segstart;
	अचिन्हित दीर्घ segend;
	पूर्णांक segcnt;
	पूर्णांक segrcnt;
	काष्ठा qrange range[6];
पूर्ण;

काष्ठा qin64 अणु
	अक्षर qopcode;
	अक्षर rsrv1[3];
	अक्षर qrcode;
	अक्षर rsrv2[3];
	अक्षर qname[8];
	अचिन्हित पूर्णांक qoutptr;
	लघु पूर्णांक qoutlen;
पूर्ण;

काष्ठा dcss_segment अणु
	काष्ठा list_head list;
	अक्षर dcss_name[8];
	अक्षर res_name[16];
	अचिन्हित दीर्घ start_addr;
	अचिन्हित दीर्घ end;
	refcount_t ref_count;
	पूर्णांक करो_nonshared;
	अचिन्हित पूर्णांक vm_segtype;
	काष्ठा qrange range[6];
	पूर्णांक segcnt;
	काष्ठा resource *res;
पूर्ण;

अटल DEFINE_MUTEX(dcss_lock);
अटल LIST_HEAD(dcss_list);
अटल अक्षर *segtype_string[] = अणु "SW", "EW", "SR", "ER", "SN", "EN", "SC",
					"EW/EN-MIXED" पूर्ण;
अटल पूर्णांक loadshr_scode = DCSS_LOADSHRX;
अटल पूर्णांक loadnsr_scode = DCSS_LOADNSRX;
अटल पूर्णांक purgeseg_scode = DCSS_PURGESEG;
अटल पूर्णांक segext_scode = DCSS_SEGEXTX;

/*
 * Create the 8 bytes, ebcdic VM segment name from
 * an ascii name.
 */
अटल व्योम
dcss_mkname(अक्षर *name, अक्षर *dcss_name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (name[i] == '\0')
			अवरोध;
		dcss_name[i] = बड़े(name[i]);
	पूर्ण
	क्रम (; i < 8; i++)
		dcss_name[i] = ' ';
	ASCEBC(dcss_name, 8);
पूर्ण


/*
 * search all segments in dcss_list, and वापस the one
 * namend *name. If not found, वापस शून्य.
 */
अटल काष्ठा dcss_segment *
segment_by_name (अक्षर *name)
अणु
	अक्षर dcss_name[9];
	काष्ठा list_head *l;
	काष्ठा dcss_segment *पंचांगp, *retval = शून्य;

	BUG_ON(!mutex_is_locked(&dcss_lock));
	dcss_mkname (name, dcss_name);
	list_क्रम_each (l, &dcss_list) अणु
		पंचांगp = list_entry (l, काष्ठा dcss_segment, list);
		अगर (स_भेद(पंचांगp->dcss_name, dcss_name, 8) == 0) अणु
			retval = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण


/*
 * Perक्रमm a function on a dcss segment.
 */
अटल अंतरभूत पूर्णांक
dcss_diag(पूर्णांक *func, व्योम *parameter,
           अचिन्हित दीर्घ *ret1, अचिन्हित दीर्घ *ret2)
अणु
	अचिन्हित दीर्घ rx, ry;
	पूर्णांक rc;

	rx = (अचिन्हित दीर्घ) parameter;
	ry = (अचिन्हित दीर्घ) *func;

	diag_stat_inc(DIAG_STAT_X064);
	यंत्र अस्थिर(
		"	diag	%0,%1,0x64\n"
		"	ipm	%2\n"
		"	srl	%2,28\n"
		: "+d" (rx), "+d" (ry), "=d" (rc) : : "cc");
	*ret1 = rx;
	*ret2 = ry;
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक
dcss_diag_translate_rc (पूर्णांक vm_rc) अणु
	अगर (vm_rc == 44)
		वापस -ENOENT;
	वापस -EIO;
पूर्ण


/* करो a diag to get info about a segment.
 * fills start_address, end and vm_segtype fields
 */
अटल पूर्णांक
query_segment_type (काष्ठा dcss_segment *seg)
अणु
	अचिन्हित दीर्घ dummy, vmrc;
	पूर्णांक diag_cc, rc, i;
	काष्ठा qout64 *qout;
	काष्ठा qin64 *qin;

	qin = kदो_स्मृति(माप(*qin), GFP_KERNEL | GFP_DMA);
	qout = kदो_स्मृति(माप(*qout), GFP_KERNEL | GFP_DMA);
	अगर ((qin == शून्य) || (qout == शून्य)) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	/* initialize diag input parameters */
	qin->qopcode = DCSS_FINDSEGA;
	qin->qoutptr = (अचिन्हित दीर्घ) qout;
	qin->qoutlen = माप(काष्ठा qout64);
	स_नकल (qin->qname, seg->dcss_name, 8);

	diag_cc = dcss_diag(&segext_scode, qin, &dummy, &vmrc);

	अगर (diag_cc < 0) अणु
		rc = diag_cc;
		जाओ out_मुक्त;
	पूर्ण
	अगर (diag_cc > 1) अणु
		pr_warn("Querying a DCSS type failed with rc=%ld\n", vmrc);
		rc = dcss_diag_translate_rc (vmrc);
		जाओ out_मुक्त;
	पूर्ण

	अगर (qout->segcnt > 6) अणु
		rc = -EOPNOTSUPP;
		जाओ out_मुक्त;
	पूर्ण

	अगर (qout->segcnt == 1) अणु
		seg->vm_segtype = qout->range[0].start & 0xff;
	पूर्ण अन्यथा अणु
		/* multi-part segment. only one type supported here:
		    - all parts are contiguous
		    - all parts are either EW or EN type
		    - maximum 6 parts allowed */
		अचिन्हित दीर्घ start = qout->segstart >> PAGE_SHIFT;
		क्रम (i=0; i<qout->segcnt; i++) अणु
			अगर (((qout->range[i].start & 0xff) != SEG_TYPE_EW) &&
			    ((qout->range[i].start & 0xff) != SEG_TYPE_EN)) अणु
				rc = -EOPNOTSUPP;
				जाओ out_मुक्त;
			पूर्ण
			अगर (start != qout->range[i].start >> PAGE_SHIFT) अणु
				rc = -EOPNOTSUPP;
				जाओ out_मुक्त;
			पूर्ण
			start = (qout->range[i].end >> PAGE_SHIFT) + 1;
		पूर्ण
		seg->vm_segtype = SEG_TYPE_EWEN;
	पूर्ण

	/* analyze diag output and update seg */
	seg->start_addr = qout->segstart;
	seg->end = qout->segend;

	स_नकल (seg->range, qout->range, 6*माप(काष्ठा qrange));
	seg->segcnt = qout->segcnt;

	rc = 0;

 out_मुक्त:
	kमुक्त(qin);
	kमुक्त(qout);
	वापस rc;
पूर्ण

/*
 * get info about a segment
 * possible वापस values:
 * -ENOSYS  : we are not running on VM
 * -EIO     : could not perक्रमm query diagnose
 * -ENOENT  : no such segment
 * -EOPNOTSUPP: multi-part segment cannot be used with linux
 * -ENOMEM  : out of memory
 * 0 .. 6   : type of segment as defined in include/यंत्र-s390/exपंचांगem.h
 */
पूर्णांक
segment_type (अक्षर* name)
अणु
	पूर्णांक rc;
	काष्ठा dcss_segment seg;

	अगर (!MACHINE_IS_VM)
		वापस -ENOSYS;

	dcss_mkname(name, seg.dcss_name);
	rc = query_segment_type (&seg);
	अगर (rc < 0)
		वापस rc;
	वापस seg.vm_segtype;
पूर्ण

/*
 * check अगर segment collides with other segments that are currently loaded
 * वापसs 1 अगर this is the हाल, 0 अगर no collision was found
 */
अटल पूर्णांक
segment_overlaps_others (काष्ठा dcss_segment *seg)
अणु
	काष्ठा list_head *l;
	काष्ठा dcss_segment *पंचांगp;

	BUG_ON(!mutex_is_locked(&dcss_lock));
	list_क्रम_each(l, &dcss_list) अणु
		पंचांगp = list_entry(l, काष्ठा dcss_segment, list);
		अगर ((पंचांगp->start_addr >> 20) > (seg->end >> 20))
			जारी;
		अगर ((पंचांगp->end >> 20) < (seg->start_addr >> 20))
			जारी;
		अगर (seg == पंचांगp)
			जारी;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * real segment loading function, called from segment_load
 */
अटल पूर्णांक
__segment_load (अक्षर *name, पूर्णांक करो_nonshared, अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ *end)
अणु
	अचिन्हित दीर्घ start_addr, end_addr, dummy;
	काष्ठा dcss_segment *seg;
	पूर्णांक rc, diag_cc;

	start_addr = end_addr = 0;
	seg = kदो_स्मृति(माप(*seg), GFP_KERNEL | GFP_DMA);
	अगर (seg == शून्य) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	dcss_mkname (name, seg->dcss_name);
	rc = query_segment_type (seg);
	अगर (rc < 0)
		जाओ out_मुक्त;

	अगर (segment_overlaps_others(seg)) अणु
		rc = -EBUSY;
		जाओ out_मुक्त;
	पूर्ण

	seg->res = kzalloc(माप(काष्ठा resource), GFP_KERNEL);
	अगर (seg->res == शून्य) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	seg->res->flags = IORESOURCE_BUSY | IORESOURCE_MEM;
	seg->res->start = seg->start_addr;
	seg->res->end = seg->end;
	स_नकल(&seg->res_name, seg->dcss_name, 8);
	EBCASC(seg->res_name, 8);
	seg->res_name[8] = '\0';
	strlcat(seg->res_name, " (DCSS)", माप(seg->res_name));
	seg->res->name = seg->res_name;
	rc = seg->vm_segtype;
	अगर (rc == SEG_TYPE_SC ||
	    ((rc == SEG_TYPE_SR || rc == SEG_TYPE_ER) && !करो_nonshared))
		seg->res->flags |= IORESOURCE_READONLY;

	/* Check क्रम overlapping resources beक्रमe adding the mapping. */
	अगर (request_resource(&iomem_resource, seg->res)) अणु
		rc = -EBUSY;
		जाओ out_मुक्त_resource;
	पूर्ण

	rc = vmem_add_mapping(seg->start_addr, seg->end - seg->start_addr + 1);
	अगर (rc)
		जाओ out_resource;

	अगर (करो_nonshared)
		diag_cc = dcss_diag(&loadnsr_scode, seg->dcss_name,
				&start_addr, &end_addr);
	अन्यथा
		diag_cc = dcss_diag(&loadshr_scode, seg->dcss_name,
				&start_addr, &end_addr);
	अगर (diag_cc < 0) अणु
		dcss_diag(&purgeseg_scode, seg->dcss_name,
				&dummy, &dummy);
		rc = diag_cc;
		जाओ out_mapping;
	पूर्ण
	अगर (diag_cc > 1) अणु
		pr_warn("Loading DCSS %s failed with rc=%ld\n", name, end_addr);
		rc = dcss_diag_translate_rc(end_addr);
		dcss_diag(&purgeseg_scode, seg->dcss_name,
				&dummy, &dummy);
		जाओ out_mapping;
	पूर्ण
	seg->start_addr = start_addr;
	seg->end = end_addr;
	seg->करो_nonshared = करो_nonshared;
	refcount_set(&seg->ref_count, 1);
	list_add(&seg->list, &dcss_list);
	*addr = seg->start_addr;
	*end  = seg->end;
	अगर (करो_nonshared)
		pr_info("DCSS %s of range %px to %px and type %s loaded as "
			"exclusive-writable\n", name, (व्योम*) seg->start_addr,
			(व्योम*) seg->end, segtype_string[seg->vm_segtype]);
	अन्यथा अणु
		pr_info("DCSS %s of range %px to %px and type %s loaded in "
			"shared access mode\n", name, (व्योम*) seg->start_addr,
			(व्योम*) seg->end, segtype_string[seg->vm_segtype]);
	पूर्ण
	जाओ out;
 out_mapping:
	vmem_हटाओ_mapping(seg->start_addr, seg->end - seg->start_addr + 1);
 out_resource:
	release_resource(seg->res);
 out_मुक्त_resource:
	kमुक्त(seg->res);
 out_मुक्त:
	kमुक्त(seg);
 out:
	वापस rc;
पूर्ण

/*
 * this function loads a DCSS segment
 * name         : name of the DCSS
 * करो_nonshared : 0 indicates that the dcss should be shared with other linux images
 *                1 indicates that the dcss should be exclusive क्रम this linux image
 * addr         : will be filled with start address of the segment
 * end          : will be filled with end address of the segment
 * वापस values:
 * -ENOSYS  : we are not running on VM
 * -EIO     : could not perक्रमm query or load diagnose
 * -ENOENT  : no such segment
 * -EOPNOTSUPP: multi-part segment cannot be used with linux
 * -EBUSY   : segment cannot be used (overlaps with dcss or storage)
 * -दुस्फल  : segment cannot be used (exceeds kernel mapping range)
 * -EPERM   : segment is currently loaded with incompatible permissions
 * -ENOMEM  : out of memory
 * 0 .. 6   : type of segment as defined in include/यंत्र-s390/exपंचांगem.h
 */
पूर्णांक
segment_load (अक्षर *name, पूर्णांक करो_nonshared, अचिन्हित दीर्घ *addr,
		अचिन्हित दीर्घ *end)
अणु
	काष्ठा dcss_segment *seg;
	पूर्णांक rc;

	अगर (!MACHINE_IS_VM)
		वापस -ENOSYS;

	mutex_lock(&dcss_lock);
	seg = segment_by_name (name);
	अगर (seg == शून्य)
		rc = __segment_load (name, करो_nonshared, addr, end);
	अन्यथा अणु
		अगर (करो_nonshared == seg->करो_nonshared) अणु
			refcount_inc(&seg->ref_count);
			*addr = seg->start_addr;
			*end  = seg->end;
			rc    = seg->vm_segtype;
		पूर्ण अन्यथा अणु
			*addr = *end = 0;
			rc    = -EPERM;
		पूर्ण
	पूर्ण
	mutex_unlock(&dcss_lock);
	वापस rc;
पूर्ण

/*
 * this function modअगरies the shared state of a DCSS segment. note that
 * name         : name of the DCSS
 * करो_nonshared : 0 indicates that the dcss should be shared with other linux images
 *                1 indicates that the dcss should be exclusive क्रम this linux image
 * वापस values:
 * -EIO     : could not perक्रमm load diagnose (segment gone!)
 * -ENOENT  : no such segment (segment gone!)
 * -EAGAIN  : segment is in use by other exploiters, try later
 * -EINVAL  : no segment with the given name is currently loaded - name invalid
 * -EBUSY   : segment can temporarily not be used (overlaps with dcss)
 * 0	    : operation succeeded
 */
पूर्णांक
segment_modअगरy_shared (अक्षर *name, पूर्णांक करो_nonshared)
अणु
	काष्ठा dcss_segment *seg;
	अचिन्हित दीर्घ start_addr, end_addr, dummy;
	पूर्णांक rc, diag_cc;

	start_addr = end_addr = 0;
	mutex_lock(&dcss_lock);
	seg = segment_by_name (name);
	अगर (seg == शून्य) अणु
		rc = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (करो_nonshared == seg->करो_nonshared) अणु
		pr_info("DCSS %s is already in the requested access "
			"mode\n", name);
		rc = 0;
		जाओ out_unlock;
	पूर्ण
	अगर (refcount_पढ़ो(&seg->ref_count) != 1) अणु
		pr_warn("DCSS %s is in use and cannot be reloaded\n", name);
		rc = -EAGAIN;
		जाओ out_unlock;
	पूर्ण
	release_resource(seg->res);
	अगर (करो_nonshared)
		seg->res->flags &= ~IORESOURCE_READONLY;
	अन्यथा
		अगर (seg->vm_segtype == SEG_TYPE_SR ||
		    seg->vm_segtype == SEG_TYPE_ER)
			seg->res->flags |= IORESOURCE_READONLY;

	अगर (request_resource(&iomem_resource, seg->res)) अणु
		pr_warn("DCSS %s overlaps with used memory resources and cannot be reloaded\n",
			name);
		rc = -EBUSY;
		kमुक्त(seg->res);
		जाओ out_del_mem;
	पूर्ण

	dcss_diag(&purgeseg_scode, seg->dcss_name, &dummy, &dummy);
	अगर (करो_nonshared)
		diag_cc = dcss_diag(&loadnsr_scode, seg->dcss_name,
				&start_addr, &end_addr);
	अन्यथा
		diag_cc = dcss_diag(&loadshr_scode, seg->dcss_name,
				&start_addr, &end_addr);
	अगर (diag_cc < 0) अणु
		rc = diag_cc;
		जाओ out_del_res;
	पूर्ण
	अगर (diag_cc > 1) अणु
		pr_warn("Reloading DCSS %s failed with rc=%ld\n",
			name, end_addr);
		rc = dcss_diag_translate_rc(end_addr);
		जाओ out_del_res;
	पूर्ण
	seg->start_addr = start_addr;
	seg->end = end_addr;
	seg->करो_nonshared = करो_nonshared;
	rc = 0;
	जाओ out_unlock;
 out_del_res:
	release_resource(seg->res);
	kमुक्त(seg->res);
 out_del_mem:
	vmem_हटाओ_mapping(seg->start_addr, seg->end - seg->start_addr + 1);
	list_del(&seg->list);
	dcss_diag(&purgeseg_scode, seg->dcss_name, &dummy, &dummy);
	kमुक्त(seg);
 out_unlock:
	mutex_unlock(&dcss_lock);
	वापस rc;
पूर्ण

/*
 * Decrease the use count of a DCSS segment and हटाओ
 * it from the address space अगर nobody is using it
 * any दीर्घer.
 */
व्योम
segment_unload(अक्षर *name)
अणु
	अचिन्हित दीर्घ dummy;
	काष्ठा dcss_segment *seg;

	अगर (!MACHINE_IS_VM)
		वापस;

	mutex_lock(&dcss_lock);
	seg = segment_by_name (name);
	अगर (seg == शून्य) अणु
		pr_err("Unloading unknown DCSS %s failed\n", name);
		जाओ out_unlock;
	पूर्ण
	अगर (!refcount_dec_and_test(&seg->ref_count))
		जाओ out_unlock;
	release_resource(seg->res);
	kमुक्त(seg->res);
	vmem_हटाओ_mapping(seg->start_addr, seg->end - seg->start_addr + 1);
	list_del(&seg->list);
	dcss_diag(&purgeseg_scode, seg->dcss_name, &dummy, &dummy);
	kमुक्त(seg);
out_unlock:
	mutex_unlock(&dcss_lock);
पूर्ण

/*
 * save segment content permanently
 */
व्योम
segment_save(अक्षर *name)
अणु
	काष्ठा dcss_segment *seg;
	अक्षर cmd1[160];
	अक्षर cmd2[80];
	पूर्णांक i, response;

	अगर (!MACHINE_IS_VM)
		वापस;

	mutex_lock(&dcss_lock);
	seg = segment_by_name (name);

	अगर (seg == शून्य) अणु
		pr_err("Saving unknown DCSS %s failed\n", name);
		जाओ out;
	पूर्ण

	प्र_लिखो(cmd1, "DEFSEG %s", name);
	क्रम (i=0; i<seg->segcnt; i++) अणु
		प्र_लिखो(cmd1+म_माप(cmd1), " %lX-%lX %s",
			seg->range[i].start >> PAGE_SHIFT,
			seg->range[i].end >> PAGE_SHIFT,
			segtype_string[seg->range[i].start & 0xff]);
	पूर्ण
	प्र_लिखो(cmd2, "SAVESEG %s", name);
	response = 0;
	cpcmd(cmd1, शून्य, 0, &response);
	अगर (response) अणु
		pr_err("Saving a DCSS failed with DEFSEG response code "
		       "%i\n", response);
		जाओ out;
	पूर्ण
	cpcmd(cmd2, शून्य, 0, &response);
	अगर (response) अणु
		pr_err("Saving a DCSS failed with SAVESEG response code "
		       "%i\n", response);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&dcss_lock);
पूर्ण

/*
 * prपूर्णांक appropriate error message क्रम segment_load()/segment_type()
 * वापस code
 */
व्योम segment_warning(पूर्णांक rc, अक्षर *seg_name)
अणु
	चयन (rc) अणु
	हाल -ENOENT:
		pr_err("DCSS %s cannot be loaded or queried\n", seg_name);
		अवरोध;
	हाल -ENOSYS:
		pr_err("DCSS %s cannot be loaded or queried without "
		       "z/VM\n", seg_name);
		अवरोध;
	हाल -EIO:
		pr_err("Loading or querying DCSS %s resulted in a "
		       "hardware error\n", seg_name);
		अवरोध;
	हाल -EOPNOTSUPP:
		pr_err("DCSS %s has multiple page ranges and cannot be "
		       "loaded or queried\n", seg_name);
		अवरोध;
	हाल -EBUSY:
		pr_err("%s needs used memory resources and cannot be "
		       "loaded or queried\n", seg_name);
		अवरोध;
	हाल -EPERM:
		pr_err("DCSS %s is already loaded in a different access "
		       "mode\n", seg_name);
		अवरोध;
	हाल -ENOMEM:
		pr_err("There is not enough memory to load or query "
		       "DCSS %s\n", seg_name);
		अवरोध;
	हाल -दुस्फल:
		pr_err("DCSS %s exceeds the kernel mapping range (%lu) "
		       "and cannot be loaded\n", seg_name, VMEM_MAX_PHYS);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

EXPORT_SYMBOL(segment_load);
EXPORT_SYMBOL(segment_unload);
EXPORT_SYMBOL(segment_save);
EXPORT_SYMBOL(segment_type);
EXPORT_SYMBOL(segment_modअगरy_shared);
EXPORT_SYMBOL(segment_warning);
