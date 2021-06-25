<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Oracle Data Analytics Accelerator (DAX)
 *
 * DAX is a coprocessor which resides on the SPARC M7 (DAX1) and M8
 * (DAX2) processor chips, and has direct access to the CPU's L3
 * caches as well as physical memory. It can perक्रमm several
 * operations on data streams with various input and output क्रमmats.
 * The driver provides a transport mechanism only and has limited
 * knowledge of the various opcodes and data क्रमmats. A user space
 * library provides high level services and translates these पूर्णांकo low
 * level commands which are then passed पूर्णांकo the driver and
 * subsequently the hypervisor and the coprocessor.  The library is
 * the recommended way क्रम applications to use the coprocessor, and
 * the driver पूर्णांकerface is not पूर्णांकended क्रम general use.
 *
 * See Documentation/sparc/oradax/oracle-dax.rst क्रम more details.
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/cdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/mdesc.h>
#समावेश <यंत्र/oradax.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Driver for Oracle Data Analytics Accelerator");

#घोषणा	DAX_DBG_FLG_BASIC	0x01
#घोषणा	DAX_DBG_FLG_STAT	0x02
#घोषणा	DAX_DBG_FLG_INFO	0x04
#घोषणा	DAX_DBG_FLG_ALL		0xff

#घोषणा	dax_err(fmt, ...)      pr_err("%s: " fmt "\n", __func__, ##__VA_ARGS__)
#घोषणा	dax_info(fmt, ...)     pr_info("%s: " fmt "\n", __func__, ##__VA_ARGS__)

#घोषणा	dax_dbg(fmt, ...)	करो अणु					\
					अगर (dax_debug & DAX_DBG_FLG_BASIC)\
						dax_info(fmt, ##__VA_ARGS__); \
				पूर्ण जबतक (0)
#घोषणा	dax_stat_dbg(fmt, ...)	करो अणु					\
					अगर (dax_debug & DAX_DBG_FLG_STAT) \
						dax_info(fmt, ##__VA_ARGS__); \
				पूर्ण जबतक (0)
#घोषणा	dax_info_dbg(fmt, ...)	करो अणु \
					अगर (dax_debug & DAX_DBG_FLG_INFO) \
						dax_info(fmt, ##__VA_ARGS__); \
				पूर्ण जबतक (0)

#घोषणा	DAX1_MINOR		1
#घोषणा	DAX1_MAJOR		1
#घोषणा	DAX2_MINOR		0
#घोषणा	DAX2_MAJOR		2

#घोषणा	DAX1_STR    "ORCL,sun4v-dax"
#घोषणा	DAX2_STR    "ORCL,sun4v-dax2"

#घोषणा	DAX_CA_ELEMS		(DAX_MMAP_LEN / माप(काष्ठा dax_cca))

#घोषणा	DAX_CCB_USEC		100
#घोषणा	DAX_CCB_RETRIES		10000

/* stream types */
क्रमागत अणु
	OUT,
	PRI,
	SEC,
	TBL,
	NUM_STREAM_TYPES
पूर्ण;

/* completion status */
#घोषणा	CCA_STAT_NOT_COMPLETED	0
#घोषणा	CCA_STAT_COMPLETED	1
#घोषणा	CCA_STAT_FAILED		2
#घोषणा	CCA_STAT_KILLED		3
#घोषणा	CCA_STAT_NOT_RUN	4
#घोषणा	CCA_STAT_PIPE_OUT	5
#घोषणा	CCA_STAT_PIPE_SRC	6
#घोषणा	CCA_STAT_PIPE_DST	7

/* completion err */
#घोषणा	CCA_ERR_SUCCESS		0x0	/* no error */
#घोषणा	CCA_ERR_OVERFLOW	0x1	/* buffer overflow */
#घोषणा	CCA_ERR_DECODE		0x2	/* CCB decode error */
#घोषणा	CCA_ERR_PAGE_OVERFLOW	0x3	/* page overflow */
#घोषणा	CCA_ERR_KILLED		0x7	/* command was समाप्तed */
#घोषणा	CCA_ERR_TIMEOUT		0x8	/* Timeout */
#घोषणा	CCA_ERR_ADI		0x9	/* ADI error */
#घोषणा	CCA_ERR_DATA_FMT	0xA	/* data क्रमmat error */
#घोषणा	CCA_ERR_OTHER_NO_RETRY	0xE	/* Other error, करो not retry */
#घोषणा	CCA_ERR_OTHER_RETRY	0xF	/* Other error, retry */
#घोषणा	CCA_ERR_PARTIAL_SYMBOL	0x80	/* QP partial symbol warning */

/* CCB address types */
#घोषणा	DAX_ADDR_TYPE_NONE	0
#घोषणा	DAX_ADDR_TYPE_VA_ALT	1	/* secondary context */
#घोषणा	DAX_ADDR_TYPE_RA	2	/* real address */
#घोषणा	DAX_ADDR_TYPE_VA	3	/* भव address */

/* dax_header_t opcode */
#घोषणा	DAX_OP_SYNC_NOP		0x0
#घोषणा	DAX_OP_EXTRACT		0x1
#घोषणा	DAX_OP_SCAN_VALUE	0x2
#घोषणा	DAX_OP_SCAN_RANGE	0x3
#घोषणा	DAX_OP_TRANSLATE	0x4
#घोषणा	DAX_OP_SELECT		0x5
#घोषणा	DAX_OP_INVERT		0x10	/* OR with translate, scan opcodes */

काष्ठा dax_header अणु
	u32 ccb_version:4;	/* 31:28 CCB Version */
				/* 27:24 Sync Flags */
	u32 pipe:1;		/* Pipeline */
	u32 दीर्घccb:1;		/* Longccb. Set क्रम scan with lu2, lu3, lu4. */
	u32 cond:1;		/* Conditional */
	u32 serial:1;		/* Serial */
	u32 opcode:8;		/* 23:16 Opcode */
				/* 15:0 Address Type. */
	u32 reserved:3;		/* 15:13 reserved */
	u32 table_addr_type:2;	/* 12:11 Huffman Table Address Type */
	u32 out_addr_type:3;	/* 10:8 Destination Address Type */
	u32 sec_addr_type:3;	/* 7:5 Secondary Source Address Type */
	u32 pri_addr_type:3;	/* 4:2 Primary Source Address Type */
	u32 cca_addr_type:2;	/* 1:0 Completion Address Type */
पूर्ण;

काष्ठा dax_control अणु
	u32 pri_fmt:4;		/* 31:28 Primary Input Format */
	u32 pri_elem_size:5;	/* 27:23 Primary Input Element Size(less1) */
	u32 pri_offset:3;	/* 22:20 Primary Input Starting Offset */
	u32 sec_encoding:1;	/* 19    Secondary Input Encoding */
				/*	 (must be 0 क्रम Select) */
	u32 sec_offset:3;	/* 18:16 Secondary Input Starting Offset */
	u32 sec_elem_size:2;	/* 15:14 Secondary Input Element Size */
				/*	 (must be 0 क्रम Select) */
	u32 out_fmt:2;		/* 13:12 Output Format */
	u32 out_elem_size:2;	/* 11:10 Output Element Size */
	u32 misc:10;		/* 9:0 Opcode specअगरic info */
पूर्ण;

काष्ठा dax_data_access अणु
	u64 flow_ctrl:2;	/* 63:62 Flow Control Type */
	u64 pipe_target:2;	/* 61:60 Pipeline Target */
	u64 out_buf_size:20;	/* 59:40 Output Buffer Size */
				/*	 (cachelines less 1) */
	u64 unused1:8;		/* 39:32 Reserved, Set to 0 */
	u64 out_alloc:5;	/* 31:27 Output Allocation */
	u64 unused2:1;		/* 26	 Reserved */
	u64 pri_len_fmt:2;	/* 25:24 Input Length Format */
	u64 pri_len:24;		/* 23:0  Input Element/Byte/Bit Count */
				/*	 (less 1) */
पूर्ण;

काष्ठा dax_ccb अणु
	काष्ठा dax_header hdr;	/* CCB Header */
	काष्ठा dax_control ctrl;/* Control Word */
	व्योम *ca;		/* Completion Address */
	व्योम *pri;		/* Primary Input Address */
	काष्ठा dax_data_access dac; /* Data Access Control */
	व्योम *sec;		/* Secondary Input Address */
	u64 dword5;		/* depends on opcode */
	व्योम *out;		/* Output Address */
	व्योम *tbl;		/* Table Address or biपंचांगap */
पूर्ण;

काष्ठा dax_cca अणु
	u8	status;		/* user may mरुको on this address */
	u8	err;		/* user visible error notअगरication */
	u8	rsvd[2];	/* reserved */
	u32	n_reमुख्यing;	/* क्रम QP partial symbol warning */
	u32	output_sz;	/* output in bytes */
	u32	rsvd2;		/* reserved */
	u64	run_cycles;	/* run समय in OCND2 cycles */
	u64	run_stats;	/* nothing reported in version 1.0 */
	u32	n_processed;	/* number input elements */
	u32	rsvd3[5];	/* reserved */
	u64	retval;		/* command वापस value */
	u64	rsvd4[8];	/* reserved */
पूर्ण;

/* per thपढ़ो CCB context */
काष्ठा dax_ctx अणु
	काष्ठा dax_ccb		*ccb_buf;
	u64			ccb_buf_ra;	/* cached RA of ccb_buf  */
	काष्ठा dax_cca		*ca_buf;
	u64			ca_buf_ra;	/* cached RA of ca_buf   */
	काष्ठा page		*pages[DAX_CA_ELEMS][NUM_STREAM_TYPES];
						/* array of locked pages */
	काष्ठा task_काष्ठा	*owner;		/* thपढ़ो that owns ctx  */
	काष्ठा task_काष्ठा	*client;	/* requesting thपढ़ो     */
	जोड़ ccb_result	result;
	u32			ccb_count;
	u32			fail_count;
पूर्ण;

/* driver खुला entry poपूर्णांकs */
अटल पूर्णांक dax_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल sमाप_प्रकार dax_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos);
अटल sमाप_प्रकार dax_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos);
अटल पूर्णांक dax_devmap(काष्ठा file *f, काष्ठा vm_area_काष्ठा *vma);
अटल पूर्णांक dax_बंद(काष्ठा inode *i, काष्ठा file *f);

अटल स्थिर काष्ठा file_operations dax_fops = अणु
	.owner	=	THIS_MODULE,
	.खोलो	=	dax_खोलो,
	.पढ़ो	=	dax_पढ़ो,
	.ग_लिखो	=	dax_ग_लिखो,
	.mmap	=	dax_devmap,
	.release =	dax_बंद,
पूर्ण;

अटल पूर्णांक dax_ccb_exec(काष्ठा dax_ctx *ctx, स्थिर अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos);
अटल पूर्णांक dax_ccb_info(u64 ca, काष्ठा ccb_info_result *info);
अटल पूर्णांक dax_ccb_समाप्त(u64 ca, u16 *समाप्त_res);

अटल काष्ठा cdev c_dev;
अटल काष्ठा class *cl;
अटल dev_t first;

अटल पूर्णांक max_ccb_version;
अटल पूर्णांक dax_debug;
module_param(dax_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(dax_debug, "Debug flags");

अटल पूर्णांक __init dax_attach(व्योम)
अणु
	अचिन्हित दीर्घ dummy, hv_rv, major, minor, minor_requested, max_ccbs;
	काष्ठा mdesc_handle *hp = mdesc_grab();
	अक्षर *prop, *dax_name;
	bool found = false;
	पूर्णांक len, ret = 0;
	u64 pn;

	अगर (hp == शून्य) अणु
		dax_err("Unable to grab mdesc");
		वापस -ENODEV;
	पूर्ण

	mdesc_क्रम_each_node_by_name(hp, pn, "virtual-device") अणु
		prop = (अक्षर *)mdesc_get_property(hp, pn, "name", &len);
		अगर (prop == शून्य)
			जारी;
		अगर (म_भेदन(prop, "dax", म_माप("dax")))
			जारी;
		dax_dbg("Found node 0x%llx = %s", pn, prop);

		prop = (अक्षर *)mdesc_get_property(hp, pn, "compatible", &len);
		अगर (prop == शून्य)
			जारी;
		dax_dbg("Found node 0x%llx = %s", pn, prop);
		found = true;
		अवरोध;
	पूर्ण

	अगर (!found) अणु
		dax_err("No DAX device found");
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	अगर (म_भेदन(prop, DAX2_STR, म_माप(DAX2_STR)) == 0) अणु
		dax_name = DAX_NAME "2";
		major = DAX2_MAJOR;
		minor_requested = DAX2_MINOR;
		max_ccb_version = 1;
		dax_dbg("MD indicates DAX2 coprocessor");
	पूर्ण अन्यथा अगर (म_भेदन(prop, DAX1_STR, म_माप(DAX1_STR)) == 0) अणु
		dax_name = DAX_NAME "1";
		major = DAX1_MAJOR;
		minor_requested = DAX1_MINOR;
		max_ccb_version = 0;
		dax_dbg("MD indicates DAX1 coprocessor");
	पूर्ण अन्यथा अणु
		dax_err("Unknown dax type: %s", prop);
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	minor = minor_requested;
	dax_dbg("Registering DAX HV api with major %ld minor %ld", major,
		minor);
	अगर (sun4v_hvapi_रेजिस्टर(HV_GRP_DAX, major, &minor)) अणु
		dax_err("hvapi_register failed");
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण अन्यथा अणु
		dax_dbg("Max minor supported by HV = %ld (major %ld)", minor,
			major);
		minor = min(minor, minor_requested);
		dax_dbg("registered DAX major %ld minor %ld", major, minor);
	पूर्ण

	/* submit a zero length ccb array to query coprocessor queue size */
	hv_rv = sun4v_ccb_submit(0, 0, HV_CCB_QUERY_CMD, 0, &max_ccbs, &dummy);
	अगर (hv_rv != 0) अणु
		dax_err("get_hwqueue_size failed with status=%ld and max_ccbs=%ld",
			hv_rv, max_ccbs);
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	अगर (max_ccbs != DAX_MAX_CCBS) अणु
		dax_err("HV reports unsupported max_ccbs=%ld", max_ccbs);
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	अगर (alloc_chrdev_region(&first, 0, 1, DAX_NAME) < 0) अणु
		dax_err("alloc_chrdev_region failed");
		ret = -ENXIO;
		जाओ करोne;
	पूर्ण

	cl = class_create(THIS_MODULE, DAX_NAME);
	अगर (IS_ERR(cl)) अणु
		dax_err("class_create failed");
		ret = PTR_ERR(cl);
		जाओ class_error;
	पूर्ण

	अगर (device_create(cl, शून्य, first, शून्य, dax_name) == शून्य) अणु
		dax_err("device_create failed");
		ret = -ENXIO;
		जाओ device_error;
	पूर्ण

	cdev_init(&c_dev, &dax_fops);
	अगर (cdev_add(&c_dev, first, 1) == -1) अणु
		dax_err("cdev_add failed");
		ret = -ENXIO;
		जाओ cdev_error;
	पूर्ण

	pr_info("Attached DAX module\n");
	जाओ करोne;

cdev_error:
	device_destroy(cl, first);
device_error:
	class_destroy(cl);
class_error:
	unरेजिस्टर_chrdev_region(first, 1);
करोne:
	mdesc_release(hp);
	वापस ret;
पूर्ण
module_init(dax_attach);

अटल व्योम __निकास dax_detach(व्योम)
अणु
	pr_info("Cleaning up DAX module\n");
	cdev_del(&c_dev);
	device_destroy(cl, first);
	class_destroy(cl);
	unरेजिस्टर_chrdev_region(first, 1);
पूर्ण
module_निकास(dax_detach);

/* map completion area */
अटल पूर्णांक dax_devmap(काष्ठा file *f, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा dax_ctx *ctx = (काष्ठा dax_ctx *)f->निजी_data;
	माप_प्रकार len = vma->vm_end - vma->vm_start;

	dax_dbg("len=0x%lx, flags=0x%lx", len, vma->vm_flags);

	अगर (ctx->owner != current) अणु
		dax_dbg("devmap called from wrong thread");
		वापस -EINVAL;
	पूर्ण

	अगर (len != DAX_MMAP_LEN) अणु
		dax_dbg("len(%lu) != DAX_MMAP_LEN(%d)", len, DAX_MMAP_LEN);
		वापस -EINVAL;
	पूर्ण

	/* completion area is mapped पढ़ो-only क्रम user */
	अगर (vma->vm_flags & VM_WRITE)
		वापस -EPERM;
	vma->vm_flags &= ~VM_MAYWRITE;

	अगर (remap_pfn_range(vma, vma->vm_start, ctx->ca_buf_ra >> PAGE_SHIFT,
			    len, vma->vm_page_prot))
		वापस -EAGAIN;

	dax_dbg("mmapped completion area at uva 0x%lx", vma->vm_start);
	वापस 0;
पूर्ण

/* Unlock user pages. Called during dequeue or device बंद */
अटल व्योम dax_unlock_pages(काष्ठा dax_ctx *ctx, पूर्णांक ccb_index, पूर्णांक nelem)
अणु
	पूर्णांक i, j;

	क्रम (i = ccb_index; i < ccb_index + nelem; i++) अणु
		क्रम (j = 0; j < NUM_STREAM_TYPES; j++) अणु
			काष्ठा page *p = ctx->pages[i][j];

			अगर (p) अणु
				dax_dbg("freeing page %p", p);
				unpin_user_pages_dirty_lock(&p, 1, j == OUT);
				ctx->pages[i][j] = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dax_lock_page(व्योम *va, काष्ठा page **p)
अणु
	पूर्णांक ret;

	dax_dbg("uva %p", va);

	ret = pin_user_pages_fast((अचिन्हित दीर्घ)va, 1, FOLL_WRITE, p);
	अगर (ret == 1) अणु
		dax_dbg("locked page %p, for VA %p", *p, va);
		वापस 0;
	पूर्ण

	dax_dbg("pin_user_pages failed, va=%p, ret=%d", va, ret);
	वापस -1;
पूर्ण

अटल पूर्णांक dax_lock_pages(काष्ठा dax_ctx *ctx, पूर्णांक idx,
			  पूर्णांक nelem, u64 *err_va)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nelem; i++) अणु
		काष्ठा dax_ccb *ccbp = &ctx->ccb_buf[i];

		/*
		 * For each address in the CCB whose type is भव,
		 * lock the page and change the type to भव alternate
		 * context. On error, वापस the offending address in
		 * err_va.
		 */
		अगर (ccbp->hdr.out_addr_type == DAX_ADDR_TYPE_VA) अणु
			dax_dbg("output");
			अगर (dax_lock_page(ccbp->out,
					  &ctx->pages[i + idx][OUT]) != 0) अणु
				*err_va = (u64)ccbp->out;
				जाओ error;
			पूर्ण
			ccbp->hdr.out_addr_type = DAX_ADDR_TYPE_VA_ALT;
		पूर्ण

		अगर (ccbp->hdr.pri_addr_type == DAX_ADDR_TYPE_VA) अणु
			dax_dbg("input");
			अगर (dax_lock_page(ccbp->pri,
					  &ctx->pages[i + idx][PRI]) != 0) अणु
				*err_va = (u64)ccbp->pri;
				जाओ error;
			पूर्ण
			ccbp->hdr.pri_addr_type = DAX_ADDR_TYPE_VA_ALT;
		पूर्ण

		अगर (ccbp->hdr.sec_addr_type == DAX_ADDR_TYPE_VA) अणु
			dax_dbg("sec input");
			अगर (dax_lock_page(ccbp->sec,
					  &ctx->pages[i + idx][SEC]) != 0) अणु
				*err_va = (u64)ccbp->sec;
				जाओ error;
			पूर्ण
			ccbp->hdr.sec_addr_type = DAX_ADDR_TYPE_VA_ALT;
		पूर्ण

		अगर (ccbp->hdr.table_addr_type == DAX_ADDR_TYPE_VA) अणु
			dax_dbg("tbl");
			अगर (dax_lock_page(ccbp->tbl,
					  &ctx->pages[i + idx][TBL]) != 0) अणु
				*err_va = (u64)ccbp->tbl;
				जाओ error;
			पूर्ण
			ccbp->hdr.table_addr_type = DAX_ADDR_TYPE_VA_ALT;
		पूर्ण

		/* skip over 2nd 64 bytes of दीर्घ CCB */
		अगर (ccbp->hdr.दीर्घccb)
			i++;
	पूर्ण
	वापस DAX_SUBMIT_OK;

error:
	dax_unlock_pages(ctx, idx, nelem);
	वापस DAX_SUBMIT_ERR_NOACCESS;
पूर्ण

अटल व्योम dax_ccb_रुको(काष्ठा dax_ctx *ctx, पूर्णांक idx)
अणु
	पूर्णांक ret, nretries;
	u16 समाप्त_res;

	dax_dbg("idx=%d", idx);

	क्रम (nretries = 0; nretries < DAX_CCB_RETRIES; nretries++) अणु
		अगर (ctx->ca_buf[idx].status == CCA_STAT_NOT_COMPLETED)
			udelay(DAX_CCB_USEC);
		अन्यथा
			वापस;
	पूर्ण
	dax_dbg("ctx (%p): CCB[%d] timed out, wait usec=%d, retries=%d. Killing ccb",
		(व्योम *)ctx, idx, DAX_CCB_USEC, DAX_CCB_RETRIES);

	ret = dax_ccb_समाप्त(ctx->ca_buf_ra + idx * माप(काष्ठा dax_cca),
			   &समाप्त_res);
	dax_dbg("Kill CCB[%d] %s", idx, ret ? "failed" : "succeeded");
पूर्ण

अटल पूर्णांक dax_बंद(काष्ठा inode *ino, काष्ठा file *f)
अणु
	काष्ठा dax_ctx *ctx = (काष्ठा dax_ctx *)f->निजी_data;
	पूर्णांक i;

	f->निजी_data = शून्य;

	क्रम (i = 0; i < DAX_CA_ELEMS; i++) अणु
		अगर (ctx->ca_buf[i].status == CCA_STAT_NOT_COMPLETED) अणु
			dax_dbg("CCB[%d] not completed", i);
			dax_ccb_रुको(ctx, i);
		पूर्ण
		dax_unlock_pages(ctx, i, 1);
	पूर्ण

	kमुक्त(ctx->ccb_buf);
	kमुक्त(ctx->ca_buf);
	dax_stat_dbg("CCBs: %d good, %d bad", ctx->ccb_count, ctx->fail_count);
	kमुक्त(ctx);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dax_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dax_ctx *ctx = f->निजी_data;

	अगर (ctx->client != current)
		वापस -EUSERS;

	ctx->client = शून्य;

	अगर (count != माप(जोड़ ccb_result))
		वापस -EINVAL;
	अगर (copy_to_user(buf, &ctx->result, माप(जोड़ ccb_result)))
		वापस -EFAULT;
	वापस count;
पूर्ण

अटल sमाप_प्रकार dax_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dax_ctx *ctx = f->निजी_data;
	काष्ठा dax_command hdr;
	अचिन्हित दीर्घ ca;
	पूर्णांक i, idx, ret;

	अगर (ctx->client != शून्य)
		वापस -EINVAL;

	अगर (count == 0 || count > DAX_MAX_CCBS * माप(काष्ठा dax_ccb))
		वापस -EINVAL;

	अगर (count % माप(काष्ठा dax_ccb) == 0)
		वापस dax_ccb_exec(ctx, buf, count, ppos); /* CCB EXEC */

	अगर (count != माप(काष्ठा dax_command))
		वापस -EINVAL;

	/* immediate command */
	अगर (ctx->owner != current)
		वापस -EUSERS;

	अगर (copy_from_user(&hdr, buf, माप(hdr)))
		वापस -EFAULT;

	ca = ctx->ca_buf_ra + hdr.ca_offset;

	चयन (hdr.command) अणु
	हाल CCB_KILL:
		अगर (hdr.ca_offset >= DAX_MMAP_LEN) अणु
			dax_dbg("invalid ca_offset (%d) >= ca_buflen (%d)",
				hdr.ca_offset, DAX_MMAP_LEN);
			वापस -EINVAL;
		पूर्ण

		ret = dax_ccb_समाप्त(ca, &ctx->result.समाप्त.action);
		अगर (ret != 0) अणु
			dax_dbg("dax_ccb_kill failed (ret=%d)", ret);
			वापस ret;
		पूर्ण

		dax_info_dbg("killed (ca_offset %d)", hdr.ca_offset);
		idx = hdr.ca_offset / माप(काष्ठा dax_cca);
		ctx->ca_buf[idx].status = CCA_STAT_KILLED;
		ctx->ca_buf[idx].err = CCA_ERR_KILLED;
		ctx->client = current;
		वापस count;

	हाल CCB_INFO:
		अगर (hdr.ca_offset >= DAX_MMAP_LEN) अणु
			dax_dbg("invalid ca_offset (%d) >= ca_buflen (%d)",
				hdr.ca_offset, DAX_MMAP_LEN);
			वापस -EINVAL;
		पूर्ण

		ret = dax_ccb_info(ca, &ctx->result.info);
		अगर (ret != 0) अणु
			dax_dbg("dax_ccb_info failed (ret=%d)", ret);
			वापस ret;
		पूर्ण

		dax_info_dbg("info succeeded on ca_offset %d", hdr.ca_offset);
		ctx->client = current;
		वापस count;

	हाल CCB_DEQUEUE:
		क्रम (i = 0; i < DAX_CA_ELEMS; i++) अणु
			अगर (ctx->ca_buf[i].status !=
			    CCA_STAT_NOT_COMPLETED)
				dax_unlock_pages(ctx, i, 1);
		पूर्ण
		वापस count;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक dax_खोलो(काष्ठा inode *inode, काष्ठा file *f)
अणु
	काष्ठा dax_ctx *ctx = शून्य;
	पूर्णांक i;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (ctx == शून्य)
		जाओ करोne;

	ctx->ccb_buf = kसुस्मृति(DAX_MAX_CCBS, माप(काष्ठा dax_ccb),
			       GFP_KERNEL);
	अगर (ctx->ccb_buf == शून्य)
		जाओ करोne;

	ctx->ccb_buf_ra = virt_to_phys(ctx->ccb_buf);
	dax_dbg("ctx->ccb_buf=0x%p, ccb_buf_ra=0x%llx",
		(व्योम *)ctx->ccb_buf, ctx->ccb_buf_ra);

	/* allocate CCB completion area buffer */
	ctx->ca_buf = kzalloc(DAX_MMAP_LEN, GFP_KERNEL);
	अगर (ctx->ca_buf == शून्य)
		जाओ alloc_error;
	क्रम (i = 0; i < DAX_CA_ELEMS; i++)
		ctx->ca_buf[i].status = CCA_STAT_COMPLETED;

	ctx->ca_buf_ra = virt_to_phys(ctx->ca_buf);
	dax_dbg("ctx=0x%p, ctx->ca_buf=0x%p, ca_buf_ra=0x%llx",
		(व्योम *)ctx, (व्योम *)ctx->ca_buf, ctx->ca_buf_ra);

	ctx->owner = current;
	f->निजी_data = ctx;
	वापस 0;

alloc_error:
	kमुक्त(ctx->ccb_buf);
करोne:
	kमुक्त(ctx);
	वापस -ENOMEM;
पूर्ण

अटल अक्षर *dax_hv_त्रुटि_सं(अचिन्हित दीर्घ hv_ret, पूर्णांक *ret)
अणु
	चयन (hv_ret) अणु
	हाल HV_EBADALIGN:
		*ret = -EFAULT;
		वापस "HV_EBADALIGN";
	हाल HV_ENORADDR:
		*ret = -EFAULT;
		वापस "HV_ENORADDR";
	हाल HV_EINVAL:
		*ret = -EINVAL;
		वापस "HV_EINVAL";
	हाल HV_EWOULDBLOCK:
		*ret = -EAGAIN;
		वापस "HV_EWOULDBLOCK";
	हाल HV_ENOACCESS:
		*ret = -EPERM;
		वापस "HV_ENOACCESS";
	शेष:
		अवरोध;
	पूर्ण

	*ret = -EIO;
	वापस "UNKNOWN";
पूर्ण

अटल पूर्णांक dax_ccb_समाप्त(u64 ca, u16 *समाप्त_res)
अणु
	अचिन्हित दीर्घ hv_ret;
	पूर्णांक count, ret = 0;
	अक्षर *err_str;

	क्रम (count = 0; count < DAX_CCB_RETRIES; count++) अणु
		dax_dbg("attempting kill on ca_ra 0x%llx", ca);
		hv_ret = sun4v_ccb_समाप्त(ca, समाप्त_res);

		अगर (hv_ret == HV_EOK) अणु
			dax_info_dbg("HV_EOK (ca_ra 0x%llx): %d", ca,
				     *समाप्त_res);
		पूर्ण अन्यथा अणु
			err_str = dax_hv_त्रुटि_सं(hv_ret, &ret);
			dax_dbg("%s (ca_ra 0x%llx)", err_str, ca);
		पूर्ण

		अगर (ret != -EAGAIN)
			वापस ret;
		dax_info_dbg("ccb_kill count = %d", count);
		udelay(DAX_CCB_USEC);
	पूर्ण

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक dax_ccb_info(u64 ca, काष्ठा ccb_info_result *info)
अणु
	अचिन्हित दीर्घ hv_ret;
	अक्षर *err_str;
	पूर्णांक ret = 0;

	dax_dbg("attempting info on ca_ra 0x%llx", ca);
	hv_ret = sun4v_ccb_info(ca, info);

	अगर (hv_ret == HV_EOK) अणु
		dax_info_dbg("HV_EOK (ca_ra 0x%llx): %d", ca, info->state);
		अगर (info->state == DAX_CCB_ENQUEUED) अणु
			dax_info_dbg("dax_unit %d, queue_num %d, queue_pos %d",
				     info->inst_num, info->q_num, info->q_pos);
		पूर्ण
	पूर्ण अन्यथा अणु
		err_str = dax_hv_त्रुटि_सं(hv_ret, &ret);
		dax_dbg("%s (ca_ra 0x%llx)", err_str, ca);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dax_prt_ccbs(काष्ठा dax_ccb *ccb, पूर्णांक nelem)
अणु
	पूर्णांक i, j;
	u64 *ccbp;

	dax_dbg("ccb buffer:");
	क्रम (i = 0; i < nelem; i++) अणु
		ccbp = (u64 *)&ccb[i];
		dax_dbg(" %sccb[%d]", ccb[i].hdr.दीर्घccb ? "long " : "",  i);
		क्रम (j = 0; j < 8; j++)
			dax_dbg("\tccb[%d].dwords[%d]=0x%llx",
				i, j, *(ccbp + j));
	पूर्ण
पूर्ण

/*
 * Validates user CCB content.  Also sets completion address and address types
 * क्रम all addresses contained in CCB.
 */
अटल पूर्णांक dax_preprocess_usr_ccbs(काष्ठा dax_ctx *ctx, पूर्णांक idx, पूर्णांक nelem)
अणु
	पूर्णांक i;

	/*
	 * The user is not allowed to specअगरy real address types in
	 * the CCB header.  This must be enक्रमced by the kernel beक्रमe
	 * submitting the CCBs to HV.  The only allowed values क्रम all
	 * address fields are VA or IMM
	 */
	क्रम (i = 0; i < nelem; i++) अणु
		काष्ठा dax_ccb *ccbp = &ctx->ccb_buf[i];
		अचिन्हित दीर्घ ca_offset;

		अगर (ccbp->hdr.ccb_version > max_ccb_version)
			वापस DAX_SUBMIT_ERR_CCB_INVAL;

		चयन (ccbp->hdr.opcode) अणु
		हाल DAX_OP_SYNC_NOP:
		हाल DAX_OP_EXTRACT:
		हाल DAX_OP_SCAN_VALUE:
		हाल DAX_OP_SCAN_RANGE:
		हाल DAX_OP_TRANSLATE:
		हाल DAX_OP_SCAN_VALUE | DAX_OP_INVERT:
		हाल DAX_OP_SCAN_RANGE | DAX_OP_INVERT:
		हाल DAX_OP_TRANSLATE | DAX_OP_INVERT:
		हाल DAX_OP_SELECT:
			अवरोध;
		शेष:
			वापस DAX_SUBMIT_ERR_CCB_INVAL;
		पूर्ण

		अगर (ccbp->hdr.out_addr_type != DAX_ADDR_TYPE_VA &&
		    ccbp->hdr.out_addr_type != DAX_ADDR_TYPE_NONE) अणु
			dax_dbg("invalid out_addr_type in user CCB[%d]", i);
			वापस DAX_SUBMIT_ERR_CCB_INVAL;
		पूर्ण

		अगर (ccbp->hdr.pri_addr_type != DAX_ADDR_TYPE_VA &&
		    ccbp->hdr.pri_addr_type != DAX_ADDR_TYPE_NONE) अणु
			dax_dbg("invalid pri_addr_type in user CCB[%d]", i);
			वापस DAX_SUBMIT_ERR_CCB_INVAL;
		पूर्ण

		अगर (ccbp->hdr.sec_addr_type != DAX_ADDR_TYPE_VA &&
		    ccbp->hdr.sec_addr_type != DAX_ADDR_TYPE_NONE) अणु
			dax_dbg("invalid sec_addr_type in user CCB[%d]", i);
			वापस DAX_SUBMIT_ERR_CCB_INVAL;
		पूर्ण

		अगर (ccbp->hdr.table_addr_type != DAX_ADDR_TYPE_VA &&
		    ccbp->hdr.table_addr_type != DAX_ADDR_TYPE_NONE) अणु
			dax_dbg("invalid table_addr_type in user CCB[%d]", i);
			वापस DAX_SUBMIT_ERR_CCB_INVAL;
		पूर्ण

		/* set completion (real) address and address type */
		ccbp->hdr.cca_addr_type = DAX_ADDR_TYPE_RA;
		ca_offset = (idx + i) * माप(काष्ठा dax_cca);
		ccbp->ca = (व्योम *)ctx->ca_buf_ra + ca_offset;
		स_रखो(&ctx->ca_buf[idx + i], 0, माप(काष्ठा dax_cca));

		dax_dbg("ccb[%d]=%p, ca_offset=0x%lx, compl RA=0x%llx",
			i, ccbp, ca_offset, ctx->ca_buf_ra + ca_offset);

		/* skip over 2nd 64 bytes of दीर्घ CCB */
		अगर (ccbp->hdr.दीर्घccb)
			i++;
	पूर्ण

	वापस DAX_SUBMIT_OK;
पूर्ण

अटल पूर्णांक dax_ccb_exec(काष्ठा dax_ctx *ctx, स्थिर अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ accepted_len, hv_rv;
	पूर्णांक i, idx, nccbs, naccepted;

	ctx->client = current;
	idx = *ppos;
	nccbs = count / माप(काष्ठा dax_ccb);

	अगर (ctx->owner != current) अणु
		dax_dbg("wrong thread");
		ctx->result.exec.status = DAX_SUBMIT_ERR_THR_INIT;
		वापस 0;
	पूर्ण
	dax_dbg("args: ccb_buf_len=%ld, idx=%d", count, idx);

	/* क्रम given index and length, verअगरy ca_buf range exists */
	अगर (idx < 0 || idx > (DAX_CA_ELEMS - nccbs)) अणु
		ctx->result.exec.status = DAX_SUBMIT_ERR_NO_CA_AVAIL;
		वापस 0;
	पूर्ण

	/*
	 * Copy CCBs पूर्णांकo kernel buffer to prevent modअगरication by the
	 * user in between validation and submission.
	 */
	अगर (copy_from_user(ctx->ccb_buf, buf, count)) अणु
		dax_dbg("copyin of user CCB buffer failed");
		ctx->result.exec.status = DAX_SUBMIT_ERR_CCB_ARR_MMU_MISS;
		वापस 0;
	पूर्ण

	/* check to see अगर ca_buf[idx] .. ca_buf[idx + nccbs] are available */
	क्रम (i = idx; i < idx + nccbs; i++) अणु
		अगर (ctx->ca_buf[i].status == CCA_STAT_NOT_COMPLETED) अणु
			dax_dbg("CA range not available, dequeue needed");
			ctx->result.exec.status = DAX_SUBMIT_ERR_NO_CA_AVAIL;
			वापस 0;
		पूर्ण
	पूर्ण
	dax_unlock_pages(ctx, idx, nccbs);

	ctx->result.exec.status = dax_preprocess_usr_ccbs(ctx, idx, nccbs);
	अगर (ctx->result.exec.status != DAX_SUBMIT_OK)
		वापस 0;

	ctx->result.exec.status = dax_lock_pages(ctx, idx, nccbs,
						 &ctx->result.exec.status_data);
	अगर (ctx->result.exec.status != DAX_SUBMIT_OK)
		वापस 0;

	अगर (dax_debug & DAX_DBG_FLG_BASIC)
		dax_prt_ccbs(ctx->ccb_buf, nccbs);

	hv_rv = sun4v_ccb_submit(ctx->ccb_buf_ra, count,
				 HV_CCB_QUERY_CMD | HV_CCB_VA_SECONDARY, 0,
				 &accepted_len, &ctx->result.exec.status_data);

	चयन (hv_rv) अणु
	हाल HV_EOK:
		/*
		 * Hcall succeeded with no errors but the accepted
		 * length may be less than the requested length.  The
		 * only way the driver can resubmit the reमुख्यder is
		 * to रुको क्रम completion of the submitted CCBs since
		 * there is no way to guarantee the ordering semantics
		 * required by the client applications.  Thereक्रमe we
		 * let the user library deal with resubmissions.
		 */
		ctx->result.exec.status = DAX_SUBMIT_OK;
		अवरोध;
	हाल HV_EWOULDBLOCK:
		/*
		 * This is a transient HV API error. The user library
		 * can retry.
		 */
		dax_dbg("hcall returned HV_EWOULDBLOCK");
		ctx->result.exec.status = DAX_SUBMIT_ERR_WOULDBLOCK;
		अवरोध;
	हाल HV_ENOMAP:
		/*
		 * HV was unable to translate a VA. The VA it could
		 * not translate is वापसed in the status_data param.
		 */
		dax_dbg("hcall returned HV_ENOMAP");
		ctx->result.exec.status = DAX_SUBMIT_ERR_NOMAP;
		अवरोध;
	हाल HV_EINVAL:
		/*
		 * This is the result of an invalid user CCB as HV is
		 * validating some of the user CCB fields.  Pass this
		 * error back to the user. There is no supporting info
		 * to isolate the invalid field.
		 */
		dax_dbg("hcall returned HV_EINVAL");
		ctx->result.exec.status = DAX_SUBMIT_ERR_CCB_INVAL;
		अवरोध;
	हाल HV_ENOACCESS:
		/*
		 * HV found a VA that did not have the appropriate
		 * permissions (such as the w bit). The VA in question
		 * is वापसed in status_data param.
		 */
		dax_dbg("hcall returned HV_ENOACCESS");
		ctx->result.exec.status = DAX_SUBMIT_ERR_NOACCESS;
		अवरोध;
	हाल HV_EUNAVAILABLE:
		/*
		 * The requested CCB operation could not be perक्रमmed
		 * at this समय. Return the specअगरic unavailable code
		 * in the status_data field.
		 */
		dax_dbg("hcall returned HV_EUNAVAILABLE");
		ctx->result.exec.status = DAX_SUBMIT_ERR_UNAVAIL;
		अवरोध;
	शेष:
		ctx->result.exec.status = DAX_SUBMIT_ERR_INTERNAL;
		dax_dbg("unknown hcall return value (%ld)", hv_rv);
		अवरोध;
	पूर्ण

	/* unlock pages associated with the unaccepted CCBs */
	naccepted = accepted_len / माप(काष्ठा dax_ccb);
	dax_unlock_pages(ctx, idx + naccepted, nccbs - naccepted);

	/* mark unaccepted CCBs as not completed */
	क्रम (i = idx + naccepted; i < idx + nccbs; i++)
		ctx->ca_buf[i].status = CCA_STAT_COMPLETED;

	ctx->ccb_count += naccepted;
	ctx->fail_count += nccbs - naccepted;

	dax_dbg("hcall rv=%ld, accepted_len=%ld, status_data=0x%llx, ret status=%d",
		hv_rv, accepted_len, ctx->result.exec.status_data,
		ctx->result.exec.status);

	अगर (count == accepted_len)
		ctx->client = शून्य; /* no पढ़ो needed to complete protocol */
	वापस accepted_len;
पूर्ण
