<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  History:
 *  Started: Aug 9 by Lawrence Foard (entropy@world.std.com),
 *           to allow user process control of SCSI devices.
 *  Development Sponsored by Killy Corp. NY NY
 *
 * Original driver (sg.c):
 *        Copyright (C) 1992 Lawrence Foard
 * Version 2 and 3 extensions to driver:
 *        Copyright (C) 1998 - 2014 Douglas Gilbert
 */

अटल पूर्णांक sg_version_num = 30536;	/* 2 digits क्रम each component */
#घोषणा SG_VERSION_STR "3.5.36"

/*
 *  D. P. Gilbert (dgilbert@पूर्णांकerlog.com), notes:
 *      - scsi logging is available via SCSI_LOG_TIMEOUT macros. First
 *        the kernel/module needs to be built with CONFIG_SCSI_LOGGING
 *        (otherwise the macros compile to empty statements).
 *
 */
#समावेश <linux/module.h>

#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mtपन.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/cdev.h>
#समावेश <linux/idr.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/blktrace_api.h>
#समावेश <linux/mutex.h>
#समावेश <linux/atomic.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/uपन.स>
#समावेश <linux/cred.h> /* क्रम sg_check_file_access() */

#समावेश "scsi.h"
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_ioctl.h>
#समावेश <scsi/sg.h>

#समावेश "scsi_logging.h"

#अगर_घोषित CONFIG_SCSI_PROC_FS
#समावेश <linux/proc_fs.h>
अटल अक्षर *sg_version_date = "20140603";

अटल पूर्णांक sg_proc_init(व्योम);
#पूर्ण_अगर

#घोषणा SG_ALLOW_DIO_DEF 0

#घोषणा SG_MAX_DEVS 32768

/* SG_MAX_CDB_SIZE should be 260 (spc4r37 section 3.1.30) however the type
 * of sg_io_hdr::cmd_len can only represent 255. All SCSI commands greater
 * than 16 bytes are "variable length" whose length is a multiple of 4
 */
#घोषणा SG_MAX_CDB_SIZE 252

#घोषणा SG_DEFAULT_TIMEOUT mult_frac(SG_DEFAULT_TIMEOUT_USER, HZ, USER_HZ)

पूर्णांक sg_big_buff = SG_DEF_RESERVED_SIZE;
/* N.B. This variable is पढ़ोable and ग_लिखोable via
   /proc/scsi/sg/def_reserved_size . Each समय sg_खोलो() is called a buffer
   of this size (or less अगर there is not enough memory) will be reserved
   क्रम use by this file descriptor. [Deprecated usage: this variable is also
   पढ़ोable via /proc/sys/kernel/sg-big-buff अगर the sg driver is built पूर्णांकo
   the kernel (i.e. it is not a module).] */
अटल पूर्णांक def_reserved_size = -1;	/* picks up init parameter */
अटल पूर्णांक sg_allow_dio = SG_ALLOW_DIO_DEF;

अटल पूर्णांक scatter_elem_sz = SG_SCATTER_SZ;
अटल पूर्णांक scatter_elem_sz_prev = SG_SCATTER_SZ;

#घोषणा SG_SECTOR_SZ 512

अटल पूर्णांक sg_add_device(काष्ठा device *, काष्ठा class_पूर्णांकerface *);
अटल व्योम sg_हटाओ_device(काष्ठा device *, काष्ठा class_पूर्णांकerface *);

अटल DEFINE_IDR(sg_index_idr);
अटल DEFINE_RWLOCK(sg_index_lock);	/* Also used to lock
							   file descriptor list क्रम device */

अटल काष्ठा class_पूर्णांकerface sg_पूर्णांकerface = अणु
	.add_dev        = sg_add_device,
	.हटाओ_dev     = sg_हटाओ_device,
पूर्ण;

प्रकार काष्ठा sg_scatter_hold अणु /* holding area क्रम scsi scatter gather info */
	अचिन्हित लघु k_use_sg; /* Count of kernel scatter-gather pieces */
	अचिन्हित sglist_len; /* size of दो_स्मृति'd scatter-gather list ++ */
	अचिन्हित bufflen;	/* Size of (aggregate) data buffer */
	काष्ठा page **pages;
	पूर्णांक page_order;
	अक्षर dio_in_use;	/* 0->indirect IO (or mmap), 1->dio */
	अचिन्हित अक्षर cmd_opcode; /* first byte of command */
पूर्ण Sg_scatter_hold;

काष्ठा sg_device;		/* क्रमward declarations */
काष्ठा sg_fd;

प्रकार काष्ठा sg_request अणु	/* SG_MAX_QUEUE requests outstanding per file */
	काष्ठा list_head entry;	/* list entry */
	काष्ठा sg_fd *parentfp;	/* शून्य -> not in use */
	Sg_scatter_hold data;	/* hold buffer, perhaps scatter list */
	sg_io_hdr_t header;	/* scsi command+info, see <scsi/sg.h> */
	अचिन्हित अक्षर sense_b[SCSI_SENSE_BUFFERSIZE];
	अक्षर res_used;		/* 1 -> using reserve buffer, 0 -> not ... */
	अक्षर orphan;		/* 1 -> drop on sight, 0 -> normal */
	अक्षर sg_io_owned;	/* 1 -> packet beदीर्घs to SG_IO */
	/* करोne रक्षित by rq_list_lock */
	अक्षर करोne;		/* 0->beक्रमe bh, 1->beक्रमe पढ़ो, 2->पढ़ो */
	काष्ठा request *rq;
	काष्ठा bio *bio;
	काष्ठा execute_work ew;
पूर्ण Sg_request;

प्रकार काष्ठा sg_fd अणु		/* holds the state of a file descriptor */
	काष्ठा list_head sfd_siblings;  /* रक्षित by device's sfd_lock */
	काष्ठा sg_device *parentdp;	/* owning device */
	रुको_queue_head_t पढ़ो_रुको;	/* queue पढ़ो until command करोne */
	rwlock_t rq_list_lock;	/* protect access to list in req_arr */
	काष्ठा mutex f_mutex;	/* protect against changes in this fd */
	पूर्णांक समयout;		/* शेषs to SG_DEFAULT_TIMEOUT      */
	पूर्णांक समयout_user;	/* शेषs to SG_DEFAULT_TIMEOUT_USER */
	Sg_scatter_hold reserve;	/* buffer held क्रम this file descriptor */
	काष्ठा list_head rq_list; /* head of request list */
	काष्ठा fasync_काष्ठा *async_qp;	/* used by asynchronous notअगरication */
	Sg_request req_arr[SG_MAX_QUEUE];	/* used as singly-linked list */
	अक्षर क्रमce_packid;	/* 1 -> pack_id input to पढ़ो(), 0 -> ignored */
	अक्षर cmd_q;		/* 1 -> allow command queuing, 0 -> करोn't */
	अचिन्हित अक्षर next_cmd_len; /* 0: स्वतःmatic, >0: use on next ग_लिखो() */
	अक्षर keep_orphan;	/* 0 -> drop orphan (def), 1 -> keep क्रम पढ़ो() */
	अक्षर mmap_called;	/* 0 -> mmap() never called on this fd */
	अक्षर res_in_use;	/* 1 -> 'reserve' array in use */
	काष्ठा kref f_ref;
	काष्ठा execute_work ew;
पूर्ण Sg_fd;

प्रकार काष्ठा sg_device अणु /* holds the state of each scsi generic device */
	काष्ठा scsi_device *device;
	रुको_queue_head_t खोलो_रुको;    /* queue खोलो() when O_EXCL present */
	काष्ठा mutex खोलो_rel_lock;     /* held when in खोलो() or release() */
	पूर्णांक sg_tablesize;	/* adapter's max scatter-gather table size */
	u32 index;		/* device index number */
	काष्ठा list_head sfds;
	rwlock_t sfd_lock;      /* protect access to sfd list */
	atomic_t detaching;     /* 0->device usable, 1->device detaching */
	bool exclude;		/* 1->खोलो(O_EXCL) succeeded and is active */
	पूर्णांक खोलो_cnt;		/* count of खोलोs (perhaps < num(sfds) ) */
	अक्षर sgdebug;		/* 0->off, 1->sense, 9->dump dev, 10-> all devs */
	काष्ठा gendisk *disk;
	काष्ठा cdev * cdev;	/* अक्षर_dev [sysfs: /sys/cdev/major/sg<n>] */
	काष्ठा kref d_ref;
पूर्ण Sg_device;

/* tasklet or soft irq callback */
अटल व्योम sg_rq_end_io(काष्ठा request *rq, blk_status_t status);
अटल पूर्णांक sg_start_req(Sg_request *srp, अचिन्हित अक्षर *cmd);
अटल पूर्णांक sg_finish_rem_req(Sg_request * srp);
अटल पूर्णांक sg_build_indirect(Sg_scatter_hold * schp, Sg_fd * sfp, पूर्णांक buff_size);
अटल sमाप_प्रकार sg_new_पढ़ो(Sg_fd * sfp, अक्षर __user *buf, माप_प्रकार count,
			   Sg_request * srp);
अटल sमाप_प्रकार sg_new_ग_लिखो(Sg_fd *sfp, काष्ठा file *file,
			स्थिर अक्षर __user *buf, माप_प्रकार count, पूर्णांक blocking,
			पूर्णांक पढ़ो_only, पूर्णांक sg_io_owned, Sg_request **o_srp);
अटल पूर्णांक sg_common_ग_लिखो(Sg_fd * sfp, Sg_request * srp,
			   अचिन्हित अक्षर *cmnd, पूर्णांक समयout, पूर्णांक blocking);
अटल पूर्णांक sg_पढ़ो_oxfer(Sg_request * srp, अक्षर __user *outp, पूर्णांक num_पढ़ो_xfer);
अटल व्योम sg_हटाओ_scat(Sg_fd * sfp, Sg_scatter_hold * schp);
अटल व्योम sg_build_reserve(Sg_fd * sfp, पूर्णांक req_size);
अटल व्योम sg_link_reserve(Sg_fd * sfp, Sg_request * srp, पूर्णांक size);
अटल व्योम sg_unlink_reserve(Sg_fd * sfp, Sg_request * srp);
अटल Sg_fd *sg_add_sfp(Sg_device * sdp);
अटल व्योम sg_हटाओ_sfp(काष्ठा kref *);
अटल Sg_request *sg_get_rq_mark(Sg_fd * sfp, पूर्णांक pack_id);
अटल Sg_request *sg_add_request(Sg_fd * sfp);
अटल पूर्णांक sg_हटाओ_request(Sg_fd * sfp, Sg_request * srp);
अटल Sg_device *sg_get_dev(पूर्णांक dev);
अटल व्योम sg_device_destroy(काष्ठा kref *kref);

#घोषणा SZ_SG_HEADER माप(काष्ठा sg_header)
#घोषणा SZ_SG_IO_HDR माप(sg_io_hdr_t)
#घोषणा SZ_SG_IOVEC माप(sg_iovec_t)
#घोषणा SZ_SG_REQ_INFO माप(sg_req_info_t)

#घोषणा sg_prपूर्णांकk(prefix, sdp, fmt, a...) \
	sdev_prefix_prपूर्णांकk(prefix, (sdp)->device,		\
			   (sdp)->disk->disk_name, fmt, ##a)

/*
 * The SCSI पूर्णांकerfaces that use पढ़ो() and ग_लिखो() as an asynchronous variant of
 * ioctl(..., SG_IO, ...) are fundamentally unsafe, since there are lots of ways
 * to trigger पढ़ो() and ग_लिखो() calls from various contexts with elevated
 * privileges. This can lead to kernel memory corruption (e.g. अगर these
 * पूर्णांकerfaces are called through splice()) and privilege escalation inside
 * userspace (e.g. अगर a process with access to such a device passes a file
 * descriptor to a SUID binary as मानक_निवेश/मानक_निकास/मानक_त्रुटि).
 *
 * This function provides protection क्रम the legacy API by restricting the
 * calling context.
 */
अटल पूर्णांक sg_check_file_access(काष्ठा file *filp, स्थिर अक्षर *caller)
अणु
	अगर (filp->f_cred != current_real_cred()) अणु
		pr_err_once("%s: process %d (%s) changed security contexts after opening file descriptor, this is not allowed.\n",
			caller, task_tgid_vnr(current), current->comm);
		वापस -EPERM;
	पूर्ण
	अगर (uaccess_kernel()) अणु
		pr_err_once("%s: process %d (%s) called from kernel context, this is not allowed.\n",
			caller, task_tgid_vnr(current), current->comm);
		वापस -EACCES;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sg_allow_access(काष्ठा file *filp, अचिन्हित अक्षर *cmd)
अणु
	काष्ठा sg_fd *sfp = filp->निजी_data;

	अगर (sfp->parentdp->device->type == TYPE_SCANNER)
		वापस 0;

	वापस blk_verअगरy_command(cmd, filp->f_mode);
पूर्ण

अटल पूर्णांक
खोलो_रुको(Sg_device *sdp, पूर्णांक flags)
अणु
	पूर्णांक retval = 0;

	अगर (flags & O_EXCL) अणु
		जबतक (sdp->खोलो_cnt > 0) अणु
			mutex_unlock(&sdp->खोलो_rel_lock);
			retval = रुको_event_पूर्णांकerruptible(sdp->खोलो_रुको,
					(atomic_पढ़ो(&sdp->detaching) ||
					 !sdp->खोलो_cnt));
			mutex_lock(&sdp->खोलो_rel_lock);

			अगर (retval) /* -ERESTARTSYS */
				वापस retval;
			अगर (atomic_पढ़ो(&sdp->detaching))
				वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (sdp->exclude) अणु
			mutex_unlock(&sdp->खोलो_rel_lock);
			retval = रुको_event_पूर्णांकerruptible(sdp->खोलो_रुको,
					(atomic_पढ़ो(&sdp->detaching) ||
					 !sdp->exclude));
			mutex_lock(&sdp->खोलो_rel_lock);

			अगर (retval) /* -ERESTARTSYS */
				वापस retval;
			अगर (atomic_पढ़ो(&sdp->detaching))
				वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

/* Returns 0 on success, अन्यथा a negated त्रुटि_सं value */
अटल पूर्णांक
sg_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक dev = iminor(inode);
	पूर्णांक flags = filp->f_flags;
	काष्ठा request_queue *q;
	Sg_device *sdp;
	Sg_fd *sfp;
	पूर्णांक retval;

	nonseekable_खोलो(inode, filp);
	अगर ((flags & O_EXCL) && (O_RDONLY == (flags & O_ACCMODE)))
		वापस -EPERM; /* Can't lock it with पढ़ो only access */
	sdp = sg_get_dev(dev);
	अगर (IS_ERR(sdp))
		वापस PTR_ERR(sdp);

	SCSI_LOG_TIMEOUT(3, sg_prपूर्णांकk(KERN_INFO, sdp,
				      "sg_open: flags=0x%x\n", flags));

	/* This driver's module count bumped by fops_get in <linux/fs.h> */
	/* Prevent the device driver from vanishing जबतक we sleep */
	retval = scsi_device_get(sdp->device);
	अगर (retval)
		जाओ sg_put;

	retval = scsi_स्वतःpm_get_device(sdp->device);
	अगर (retval)
		जाओ sdp_put;

	/* scsi_block_when_processing_errors() may block so bypass
	 * check अगर O_NONBLOCK. Permits SCSI commands to be issued
	 * during error recovery. Tपढ़ो carefully. */
	अगर (!((flags & O_NONBLOCK) ||
	      scsi_block_when_processing_errors(sdp->device))) अणु
		retval = -ENXIO;
		/* we are in error recovery क्रम this device */
		जाओ error_out;
	पूर्ण

	mutex_lock(&sdp->खोलो_rel_lock);
	अगर (flags & O_NONBLOCK) अणु
		अगर (flags & O_EXCL) अणु
			अगर (sdp->खोलो_cnt > 0) अणु
				retval = -EBUSY;
				जाओ error_mutex_locked;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (sdp->exclude) अणु
				retval = -EBUSY;
				जाओ error_mutex_locked;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		retval = खोलो_रुको(sdp, flags);
		अगर (retval) /* -ERESTARTSYS or -ENODEV */
			जाओ error_mutex_locked;
	पूर्ण

	/* N.B. at this poपूर्णांक we are holding the खोलो_rel_lock */
	अगर (flags & O_EXCL)
		sdp->exclude = true;

	अगर (sdp->खोलो_cnt < 1) अणु  /* no existing खोलोs */
		sdp->sgdebug = 0;
		q = sdp->device->request_queue;
		sdp->sg_tablesize = queue_max_segments(q);
	पूर्ण
	sfp = sg_add_sfp(sdp);
	अगर (IS_ERR(sfp)) अणु
		retval = PTR_ERR(sfp);
		जाओ out_unकरो;
	पूर्ण

	filp->निजी_data = sfp;
	sdp->खोलो_cnt++;
	mutex_unlock(&sdp->खोलो_rel_lock);

	retval = 0;
sg_put:
	kref_put(&sdp->d_ref, sg_device_destroy);
	वापस retval;

out_unकरो:
	अगर (flags & O_EXCL) अणु
		sdp->exclude = false;   /* unकरो अगर error */
		wake_up_पूर्णांकerruptible(&sdp->खोलो_रुको);
	पूर्ण
error_mutex_locked:
	mutex_unlock(&sdp->खोलो_rel_lock);
error_out:
	scsi_स्वतःpm_put_device(sdp->device);
sdp_put:
	scsi_device_put(sdp->device);
	जाओ sg_put;
पूर्ण

/* Release resources associated with a successful sg_खोलो()
 * Returns 0 on success, अन्यथा a negated त्रुटि_सं value */
अटल पूर्णांक
sg_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	Sg_device *sdp;
	Sg_fd *sfp;

	अगर ((!(sfp = (Sg_fd *) filp->निजी_data)) || (!(sdp = sfp->parentdp)))
		वापस -ENXIO;
	SCSI_LOG_TIMEOUT(3, sg_prपूर्णांकk(KERN_INFO, sdp, "sg_release\n"));

	mutex_lock(&sdp->खोलो_rel_lock);
	scsi_स्वतःpm_put_device(sdp->device);
	kref_put(&sfp->f_ref, sg_हटाओ_sfp);
	sdp->खोलो_cnt--;

	/* possibly many खोलो()s रुकोing on exlude clearing, start many;
	 * only खोलो(O_EXCL)s रुको on 0==खोलो_cnt so only start one */
	अगर (sdp->exclude) अणु
		sdp->exclude = false;
		wake_up_पूर्णांकerruptible_all(&sdp->खोलो_रुको);
	पूर्ण अन्यथा अगर (0 == sdp->खोलो_cnt) अणु
		wake_up_पूर्णांकerruptible(&sdp->खोलो_रुको);
	पूर्ण
	mutex_unlock(&sdp->खोलो_rel_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक get_sg_io_pack_id(पूर्णांक *pack_id, व्योम __user *buf, माप_प्रकार count)
अणु
	काष्ठा sg_header __user *old_hdr = buf;
	पूर्णांक reply_len;

	अगर (count >= SZ_SG_HEADER) अणु
		/* negative reply_len means v3 क्रमmat, otherwise v1/v2 */
		अगर (get_user(reply_len, &old_hdr->reply_len))
			वापस -EFAULT;

		अगर (reply_len >= 0)
			वापस get_user(*pack_id, &old_hdr->pack_id);

		अगर (in_compat_syscall() &&
		    count >= माप(काष्ठा compat_sg_io_hdr)) अणु
			काष्ठा compat_sg_io_hdr __user *hp = buf;

			वापस get_user(*pack_id, &hp->pack_id);
		पूर्ण

		अगर (count >= माप(काष्ठा sg_io_hdr)) अणु
			काष्ठा sg_io_hdr __user *hp = buf;

			वापस get_user(*pack_id, &hp->pack_id);
		पूर्ण
	पूर्ण

	/* no valid header was passed, so ignore the pack_id */
	*pack_id = -1;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
sg_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count, loff_t * ppos)
अणु
	Sg_device *sdp;
	Sg_fd *sfp;
	Sg_request *srp;
	पूर्णांक req_pack_id = -1;
	sg_io_hdr_t *hp;
	काष्ठा sg_header *old_hdr;
	पूर्णांक retval;

	/*
	 * This could cause a response to be stअक्रमed. Close the associated
	 * file descriptor to मुक्त up any resources being held.
	 */
	retval = sg_check_file_access(filp, __func__);
	अगर (retval)
		वापस retval;

	अगर ((!(sfp = (Sg_fd *) filp->निजी_data)) || (!(sdp = sfp->parentdp)))
		वापस -ENXIO;
	SCSI_LOG_TIMEOUT(3, sg_prपूर्णांकk(KERN_INFO, sdp,
				      "sg_read: count=%d\n", (पूर्णांक) count));

	अगर (sfp->क्रमce_packid)
		retval = get_sg_io_pack_id(&req_pack_id, buf, count);
	अगर (retval)
		वापस retval;

	srp = sg_get_rq_mark(sfp, req_pack_id);
	अगर (!srp) अणु		/* now रुको on packet to arrive */
		अगर (atomic_पढ़ो(&sdp->detaching))
			वापस -ENODEV;
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		retval = रुको_event_पूर्णांकerruptible(sfp->पढ़ो_रुको,
			(atomic_पढ़ो(&sdp->detaching) ||
			(srp = sg_get_rq_mark(sfp, req_pack_id))));
		अगर (atomic_पढ़ो(&sdp->detaching))
			वापस -ENODEV;
		अगर (retval)
			/* -ERESTARTSYS as संकेत hit process */
			वापस retval;
	पूर्ण
	अगर (srp->header.पूर्णांकerface_id != '\0')
		वापस sg_new_पढ़ो(sfp, buf, count, srp);

	hp = &srp->header;
	old_hdr = kzalloc(SZ_SG_HEADER, GFP_KERNEL);
	अगर (!old_hdr)
		वापस -ENOMEM;

	old_hdr->reply_len = (पूर्णांक) hp->समयout;
	old_hdr->pack_len = old_hdr->reply_len; /* old, strange behaviour */
	old_hdr->pack_id = hp->pack_id;
	old_hdr->twelve_byte =
	    ((srp->data.cmd_opcode >= 0xc0) && (12 == hp->cmd_len)) ? 1 : 0;
	old_hdr->target_status = hp->masked_status;
	old_hdr->host_status = hp->host_status;
	old_hdr->driver_status = hp->driver_status;
	अगर ((CHECK_CONDITION & hp->masked_status) ||
	    (DRIVER_SENSE & hp->driver_status))
		स_नकल(old_hdr->sense_buffer, srp->sense_b,
		       माप (old_hdr->sense_buffer));
	चयन (hp->host_status) अणु
	/* This setup of 'result' is क्रम backward compatibility and is best
	   ignored by the user who should use target, host + driver status */
	हाल DID_OK:
	हाल DID_PASSTHROUGH:
	हाल DID_SOFT_ERROR:
		old_hdr->result = 0;
		अवरोध;
	हाल DID_NO_CONNECT:
	हाल DID_BUS_BUSY:
	हाल DID_TIME_OUT:
		old_hdr->result = EBUSY;
		अवरोध;
	हाल DID_BAD_TARGET:
	हाल DID_ABORT:
	हाल DID_PARITY:
	हाल DID_RESET:
	हाल DID_BAD_INTR:
		old_hdr->result = EIO;
		अवरोध;
	हाल DID_ERROR:
		old_hdr->result = (srp->sense_b[0] == 0 && 
				  hp->masked_status == GOOD) ? 0 : EIO;
		अवरोध;
	शेष:
		old_hdr->result = EIO;
		अवरोध;
	पूर्ण

	/* Now copy the result back to the user buffer.  */
	अगर (count >= SZ_SG_HEADER) अणु
		अगर (copy_to_user(buf, old_hdr, SZ_SG_HEADER)) अणु
			retval = -EFAULT;
			जाओ मुक्त_old_hdr;
		पूर्ण
		buf += SZ_SG_HEADER;
		अगर (count > old_hdr->reply_len)
			count = old_hdr->reply_len;
		अगर (count > SZ_SG_HEADER) अणु
			अगर (sg_पढ़ो_oxfer(srp, buf, count - SZ_SG_HEADER)) अणु
				retval = -EFAULT;
				जाओ मुक्त_old_hdr;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		count = (old_hdr->result == 0) ? 0 : -EIO;
	sg_finish_rem_req(srp);
	sg_हटाओ_request(sfp, srp);
	retval = count;
मुक्त_old_hdr:
	kमुक्त(old_hdr);
	वापस retval;
पूर्ण

अटल sमाप_प्रकार
sg_new_पढ़ो(Sg_fd * sfp, अक्षर __user *buf, माप_प्रकार count, Sg_request * srp)
अणु
	sg_io_hdr_t *hp = &srp->header;
	पूर्णांक err = 0, err2;
	पूर्णांक len;

	अगर (in_compat_syscall()) अणु
		अगर (count < माप(काष्ठा compat_sg_io_hdr)) अणु
			err = -EINVAL;
			जाओ err_out;
		पूर्ण
	पूर्ण अन्यथा अगर (count < SZ_SG_IO_HDR) अणु
		err = -EINVAL;
		जाओ err_out;
	पूर्ण
	hp->sb_len_wr = 0;
	अगर ((hp->mx_sb_len > 0) && hp->sbp) अणु
		अगर ((CHECK_CONDITION & hp->masked_status) ||
		    (DRIVER_SENSE & hp->driver_status)) अणु
			पूर्णांक sb_len = SCSI_SENSE_BUFFERSIZE;
			sb_len = (hp->mx_sb_len > sb_len) ? sb_len : hp->mx_sb_len;
			len = 8 + (पूर्णांक) srp->sense_b[7];	/* Additional sense length field */
			len = (len > sb_len) ? sb_len : len;
			अगर (copy_to_user(hp->sbp, srp->sense_b, len)) अणु
				err = -EFAULT;
				जाओ err_out;
			पूर्ण
			hp->sb_len_wr = len;
		पूर्ण
	पूर्ण
	अगर (hp->masked_status || hp->host_status || hp->driver_status)
		hp->info |= SG_INFO_CHECK;
	err = put_sg_io_hdr(hp, buf);
err_out:
	err2 = sg_finish_rem_req(srp);
	sg_हटाओ_request(sfp, srp);
	वापस err ? : err2 ? : count;
पूर्ण

अटल sमाप_प्रकार
sg_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t * ppos)
अणु
	पूर्णांक mxsize, cmd_size, k;
	पूर्णांक input_size, blocking;
	अचिन्हित अक्षर opcode;
	Sg_device *sdp;
	Sg_fd *sfp;
	Sg_request *srp;
	काष्ठा sg_header old_hdr;
	sg_io_hdr_t *hp;
	अचिन्हित अक्षर cmnd[SG_MAX_CDB_SIZE];
	पूर्णांक retval;

	retval = sg_check_file_access(filp, __func__);
	अगर (retval)
		वापस retval;

	अगर ((!(sfp = (Sg_fd *) filp->निजी_data)) || (!(sdp = sfp->parentdp)))
		वापस -ENXIO;
	SCSI_LOG_TIMEOUT(3, sg_prपूर्णांकk(KERN_INFO, sdp,
				      "sg_write: count=%d\n", (पूर्णांक) count));
	अगर (atomic_पढ़ो(&sdp->detaching))
		वापस -ENODEV;
	अगर (!((filp->f_flags & O_NONBLOCK) ||
	      scsi_block_when_processing_errors(sdp->device)))
		वापस -ENXIO;

	अगर (count < SZ_SG_HEADER)
		वापस -EIO;
	अगर (copy_from_user(&old_hdr, buf, SZ_SG_HEADER))
		वापस -EFAULT;
	blocking = !(filp->f_flags & O_NONBLOCK);
	अगर (old_hdr.reply_len < 0)
		वापस sg_new_ग_लिखो(sfp, filp, buf, count,
				    blocking, 0, 0, शून्य);
	अगर (count < (SZ_SG_HEADER + 6))
		वापस -EIO;	/* The minimum scsi command length is 6 bytes. */

	buf += SZ_SG_HEADER;
	अगर (get_user(opcode, buf))
		वापस -EFAULT;

	अगर (!(srp = sg_add_request(sfp))) अणु
		SCSI_LOG_TIMEOUT(1, sg_prपूर्णांकk(KERN_INFO, sdp,
					      "sg_write: queue full\n"));
		वापस -गलत_तर्क;
	पूर्ण
	mutex_lock(&sfp->f_mutex);
	अगर (sfp->next_cmd_len > 0) अणु
		cmd_size = sfp->next_cmd_len;
		sfp->next_cmd_len = 0;	/* reset so only this ग_लिखो() effected */
	पूर्ण अन्यथा अणु
		cmd_size = COMMAND_SIZE(opcode);	/* based on SCSI command group */
		अगर ((opcode >= 0xc0) && old_hdr.twelve_byte)
			cmd_size = 12;
	पूर्ण
	mutex_unlock(&sfp->f_mutex);
	SCSI_LOG_TIMEOUT(4, sg_prपूर्णांकk(KERN_INFO, sdp,
		"sg_write:   scsi opcode=0x%02x, cmd_size=%d\n", (पूर्णांक) opcode, cmd_size));
/* Determine buffer size.  */
	input_size = count - cmd_size;
	mxsize = (input_size > old_hdr.reply_len) ? input_size : old_hdr.reply_len;
	mxsize -= SZ_SG_HEADER;
	input_size -= SZ_SG_HEADER;
	अगर (input_size < 0) अणु
		sg_हटाओ_request(sfp, srp);
		वापस -EIO;	/* User did not pass enough bytes क्रम this command. */
	पूर्ण
	hp = &srp->header;
	hp->पूर्णांकerface_id = '\0';	/* indicator of old पूर्णांकerface tunnelled */
	hp->cmd_len = (अचिन्हित अक्षर) cmd_size;
	hp->iovec_count = 0;
	hp->mx_sb_len = 0;
	अगर (input_size > 0)
		hp->dxfer_direction = (old_hdr.reply_len > SZ_SG_HEADER) ?
		    SG_DXFER_TO_FROM_DEV : SG_DXFER_TO_DEV;
	अन्यथा
		hp->dxfer_direction = (mxsize > 0) ? SG_DXFER_FROM_DEV : SG_DXFER_NONE;
	hp->dxfer_len = mxsize;
	अगर ((hp->dxfer_direction == SG_DXFER_TO_DEV) ||
	    (hp->dxfer_direction == SG_DXFER_TO_FROM_DEV))
		hp->dxferp = (अक्षर __user *)buf + cmd_size;
	अन्यथा
		hp->dxferp = शून्य;
	hp->sbp = शून्य;
	hp->समयout = old_hdr.reply_len;	/* काष्ठाure abuse ... */
	hp->flags = input_size;	/* काष्ठाure abuse ... */
	hp->pack_id = old_hdr.pack_id;
	hp->usr_ptr = शून्य;
	अगर (copy_from_user(cmnd, buf, cmd_size)) अणु
		sg_हटाओ_request(sfp, srp);
		वापस -EFAULT;
	पूर्ण
	/*
	 * SG_DXFER_TO_FROM_DEV is functionally equivalent to SG_DXFER_FROM_DEV,
	 * but is is possible that the app पूर्णांकended SG_DXFER_TO_DEV, because there
	 * is a non-zero input_size, so emit a warning.
	 */
	अगर (hp->dxfer_direction == SG_DXFER_TO_FROM_DEV) अणु
		prपूर्णांकk_ratelimited(KERN_WARNING
				   "sg_write: data in/out %d/%d bytes "
				   "for SCSI command 0x%x-- guessing "
				   "data in;\n   program %s not setting "
				   "count and/or reply_len properly\n",
				   old_hdr.reply_len - (पूर्णांक)SZ_SG_HEADER,
				   input_size, (अचिन्हित पूर्णांक) cmnd[0],
				   current->comm);
	पूर्ण
	k = sg_common_ग_लिखो(sfp, srp, cmnd, sfp->समयout, blocking);
	वापस (k < 0) ? k : count;
पूर्ण

अटल sमाप_प्रकार
sg_new_ग_लिखो(Sg_fd *sfp, काष्ठा file *file, स्थिर अक्षर __user *buf,
		 माप_प्रकार count, पूर्णांक blocking, पूर्णांक पढ़ो_only, पूर्णांक sg_io_owned,
		 Sg_request **o_srp)
अणु
	पूर्णांक k;
	Sg_request *srp;
	sg_io_hdr_t *hp;
	अचिन्हित अक्षर cmnd[SG_MAX_CDB_SIZE];
	पूर्णांक समयout;
	अचिन्हित दीर्घ ul_समयout;

	अगर (count < SZ_SG_IO_HDR)
		वापस -EINVAL;

	sfp->cmd_q = 1;	/* when sg_io_hdr seen, set command queuing on */
	अगर (!(srp = sg_add_request(sfp))) अणु
		SCSI_LOG_TIMEOUT(1, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
					      "sg_new_write: queue full\n"));
		वापस -गलत_तर्क;
	पूर्ण
	srp->sg_io_owned = sg_io_owned;
	hp = &srp->header;
	अगर (get_sg_io_hdr(hp, buf)) अणु
		sg_हटाओ_request(sfp, srp);
		वापस -EFAULT;
	पूर्ण
	अगर (hp->पूर्णांकerface_id != 'S') अणु
		sg_हटाओ_request(sfp, srp);
		वापस -ENOSYS;
	पूर्ण
	अगर (hp->flags & SG_FLAG_MMAP_IO) अणु
		अगर (hp->dxfer_len > sfp->reserve.bufflen) अणु
			sg_हटाओ_request(sfp, srp);
			वापस -ENOMEM;	/* MMAP_IO size must fit in reserve buffer */
		पूर्ण
		अगर (hp->flags & SG_FLAG_सूचीECT_IO) अणु
			sg_हटाओ_request(sfp, srp);
			वापस -EINVAL;	/* either MMAP_IO or सूचीECT_IO (not both) */
		पूर्ण
		अगर (sfp->res_in_use) अणु
			sg_हटाओ_request(sfp, srp);
			वापस -EBUSY;	/* reserve buffer alपढ़ोy being used */
		पूर्ण
	पूर्ण
	ul_समयout = msecs_to_jअगरfies(srp->header.समयout);
	समयout = (ul_समयout < पूर्णांक_उच्च) ? ul_समयout : पूर्णांक_उच्च;
	अगर ((!hp->cmdp) || (hp->cmd_len < 6) || (hp->cmd_len > माप (cmnd))) अणु
		sg_हटाओ_request(sfp, srp);
		वापस -EMSGSIZE;
	पूर्ण
	अगर (copy_from_user(cmnd, hp->cmdp, hp->cmd_len)) अणु
		sg_हटाओ_request(sfp, srp);
		वापस -EFAULT;
	पूर्ण
	अगर (पढ़ो_only && sg_allow_access(file, cmnd)) अणु
		sg_हटाओ_request(sfp, srp);
		वापस -EPERM;
	पूर्ण
	k = sg_common_ग_लिखो(sfp, srp, cmnd, समयout, blocking);
	अगर (k < 0)
		वापस k;
	अगर (o_srp)
		*o_srp = srp;
	वापस count;
पूर्ण

अटल पूर्णांक
sg_common_ग_लिखो(Sg_fd * sfp, Sg_request * srp,
		अचिन्हित अक्षर *cmnd, पूर्णांक समयout, पूर्णांक blocking)
अणु
	पूर्णांक k, at_head;
	Sg_device *sdp = sfp->parentdp;
	sg_io_hdr_t *hp = &srp->header;

	srp->data.cmd_opcode = cmnd[0];	/* hold opcode of command */
	hp->status = 0;
	hp->masked_status = 0;
	hp->msg_status = 0;
	hp->info = 0;
	hp->host_status = 0;
	hp->driver_status = 0;
	hp->resid = 0;
	SCSI_LOG_TIMEOUT(4, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
			"sg_common_write:  scsi opcode=0x%02x, cmd_size=%d\n",
			(पूर्णांक) cmnd[0], (पूर्णांक) hp->cmd_len));

	अगर (hp->dxfer_len >= SZ_256M) अणु
		sg_हटाओ_request(sfp, srp);
		वापस -EINVAL;
	पूर्ण

	k = sg_start_req(srp, cmnd);
	अगर (k) अणु
		SCSI_LOG_TIMEOUT(1, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
			"sg_common_write: start_req err=%d\n", k));
		sg_finish_rem_req(srp);
		sg_हटाओ_request(sfp, srp);
		वापस k;	/* probably out of space --> ENOMEM */
	पूर्ण
	अगर (atomic_पढ़ो(&sdp->detaching)) अणु
		अगर (srp->bio) अणु
			scsi_req_मुक्त_cmd(scsi_req(srp->rq));
			blk_put_request(srp->rq);
			srp->rq = शून्य;
		पूर्ण

		sg_finish_rem_req(srp);
		sg_हटाओ_request(sfp, srp);
		वापस -ENODEV;
	पूर्ण

	hp->duration = jअगरfies_to_msecs(jअगरfies);
	अगर (hp->पूर्णांकerface_id != '\0' &&	/* v3 (or later) पूर्णांकerface */
	    (SG_FLAG_Q_AT_TAIL & hp->flags))
		at_head = 0;
	अन्यथा
		at_head = 1;

	srp->rq->समयout = समयout;
	kref_get(&sfp->f_ref); /* sg_rq_end_io() करोes kref_put(). */
	blk_execute_rq_noरुको(sdp->disk, srp->rq, at_head, sg_rq_end_io);
	वापस 0;
पूर्ण

अटल पूर्णांक srp_करोne(Sg_fd *sfp, Sg_request *srp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	पढ़ो_lock_irqsave(&sfp->rq_list_lock, flags);
	ret = srp->करोne;
	पढ़ो_unlock_irqrestore(&sfp->rq_list_lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक max_sectors_bytes(काष्ठा request_queue *q)
अणु
	अचिन्हित पूर्णांक max_sectors = queue_max_sectors(q);

	max_sectors = min_t(अचिन्हित पूर्णांक, max_sectors, पूर्णांक_उच्च >> 9);

	वापस max_sectors << 9;
पूर्ण

अटल व्योम
sg_fill_request_table(Sg_fd *sfp, sg_req_info_t *rinfo)
अणु
	Sg_request *srp;
	पूर्णांक val;
	अचिन्हित पूर्णांक ms;

	val = 0;
	list_क्रम_each_entry(srp, &sfp->rq_list, entry) अणु
		अगर (val >= SG_MAX_QUEUE)
			अवरोध;
		rinfo[val].req_state = srp->करोne + 1;
		rinfo[val].problem =
			srp->header.masked_status &
			srp->header.host_status &
			srp->header.driver_status;
		अगर (srp->करोne)
			rinfo[val].duration =
				srp->header.duration;
		अन्यथा अणु
			ms = jअगरfies_to_msecs(jअगरfies);
			rinfo[val].duration =
				(ms > srp->header.duration) ?
				(ms - srp->header.duration) : 0;
		पूर्ण
		rinfo[val].orphan = srp->orphan;
		rinfo[val].sg_io_owned = srp->sg_io_owned;
		rinfo[val].pack_id = srp->header.pack_id;
		rinfo[val].usr_ptr = srp->header.usr_ptr;
		val++;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_sg_req_info अणु /* used by SG_GET_REQUEST_TABLE ioctl() */
	अक्षर req_state;
	अक्षर orphan;
	अक्षर sg_io_owned;
	अक्षर problem;
	पूर्णांक pack_id;
	compat_uptr_t usr_ptr;
	अचिन्हित पूर्णांक duration;
	पूर्णांक unused;
पूर्ण;

अटल पूर्णांक put_compat_request_table(काष्ठा compat_sg_req_info __user *o,
				    काष्ठा sg_req_info *rinfo)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < SG_MAX_QUEUE; i++) अणु
		अगर (copy_to_user(o + i, rinfo + i, दुरत्व(sg_req_info_t, usr_ptr)) ||
		    put_user((uपूर्णांकptr_t)rinfo[i].usr_ptr, &o[i].usr_ptr) ||
		    put_user(rinfo[i].duration, &o[i].duration) ||
		    put_user(rinfo[i].unused, &o[i].unused))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल दीर्घ
sg_ioctl_common(काष्ठा file *filp, Sg_device *sdp, Sg_fd *sfp,
		अचिन्हित पूर्णांक cmd_in, व्योम __user *p)
अणु
	पूर्णांक __user *ip = p;
	पूर्णांक result, val, पढ़ो_only;
	Sg_request *srp;
	अचिन्हित दीर्घ अगरlags;

	SCSI_LOG_TIMEOUT(3, sg_prपूर्णांकk(KERN_INFO, sdp,
				   "sg_ioctl: cmd=0x%x\n", (पूर्णांक) cmd_in));
	पढ़ो_only = (O_RDWR != (filp->f_flags & O_ACCMODE));

	चयन (cmd_in) अणु
	हाल SG_IO:
		अगर (atomic_पढ़ो(&sdp->detaching))
			वापस -ENODEV;
		अगर (!scsi_block_when_processing_errors(sdp->device))
			वापस -ENXIO;
		result = sg_new_ग_लिखो(sfp, filp, p, SZ_SG_IO_HDR,
				 1, पढ़ो_only, 1, &srp);
		अगर (result < 0)
			वापस result;
		result = रुको_event_पूर्णांकerruptible(sfp->पढ़ो_रुको,
			(srp_करोne(sfp, srp) || atomic_पढ़ो(&sdp->detaching)));
		अगर (atomic_पढ़ो(&sdp->detaching))
			वापस -ENODEV;
		ग_लिखो_lock_irq(&sfp->rq_list_lock);
		अगर (srp->करोne) अणु
			srp->करोne = 2;
			ग_लिखो_unlock_irq(&sfp->rq_list_lock);
			result = sg_new_पढ़ो(sfp, p, SZ_SG_IO_HDR, srp);
			वापस (result < 0) ? result : 0;
		पूर्ण
		srp->orphan = 1;
		ग_लिखो_unlock_irq(&sfp->rq_list_lock);
		वापस result;	/* -ERESTARTSYS because संकेत hit process */
	हाल SG_SET_TIMEOUT:
		result = get_user(val, ip);
		अगर (result)
			वापस result;
		अगर (val < 0)
			वापस -EIO;
		अगर (val >= mult_frac((s64)पूर्णांक_उच्च, USER_HZ, HZ))
			val = min_t(s64, mult_frac((s64)पूर्णांक_उच्च, USER_HZ, HZ),
				    पूर्णांक_उच्च);
		sfp->समयout_user = val;
		sfp->समयout = mult_frac(val, HZ, USER_HZ);

		वापस 0;
	हाल SG_GET_TIMEOUT:	/* N.B. User receives समयout as वापस value */
				/* strange ..., क्रम backward compatibility */
		वापस sfp->समयout_user;
	हाल SG_SET_FORCE_LOW_DMA:
		/*
		 * N.B. This ioctl never worked properly, but failed to
		 * वापस an error value. So वापसing '0' to keep compability
		 * with legacy applications.
		 */
		वापस 0;
	हाल SG_GET_LOW_DMA:
		वापस put_user(0, ip);
	हाल SG_GET_SCSI_ID:
		अणु
			sg_scsi_id_t v;

			अगर (atomic_पढ़ो(&sdp->detaching))
				वापस -ENODEV;
			स_रखो(&v, 0, माप(v));
			v.host_no = sdp->device->host->host_no;
			v.channel = sdp->device->channel;
			v.scsi_id = sdp->device->id;
			v.lun = sdp->device->lun;
			v.scsi_type = sdp->device->type;
			v.h_cmd_per_lun = sdp->device->host->cmd_per_lun;
			v.d_queue_depth = sdp->device->queue_depth;
			अगर (copy_to_user(p, &v, माप(sg_scsi_id_t)))
				वापस -EFAULT;
			वापस 0;
		पूर्ण
	हाल SG_SET_FORCE_PACK_ID:
		result = get_user(val, ip);
		अगर (result)
			वापस result;
		sfp->क्रमce_packid = val ? 1 : 0;
		वापस 0;
	हाल SG_GET_PACK_ID:
		पढ़ो_lock_irqsave(&sfp->rq_list_lock, अगरlags);
		list_क्रम_each_entry(srp, &sfp->rq_list, entry) अणु
			अगर ((1 == srp->करोne) && (!srp->sg_io_owned)) अणु
				पढ़ो_unlock_irqrestore(&sfp->rq_list_lock,
						       अगरlags);
				वापस put_user(srp->header.pack_id, ip);
			पूर्ण
		पूर्ण
		पढ़ो_unlock_irqrestore(&sfp->rq_list_lock, अगरlags);
		वापस put_user(-1, ip);
	हाल SG_GET_NUM_WAITING:
		पढ़ो_lock_irqsave(&sfp->rq_list_lock, अगरlags);
		val = 0;
		list_क्रम_each_entry(srp, &sfp->rq_list, entry) अणु
			अगर ((1 == srp->करोne) && (!srp->sg_io_owned))
				++val;
		पूर्ण
		पढ़ो_unlock_irqrestore(&sfp->rq_list_lock, अगरlags);
		वापस put_user(val, ip);
	हाल SG_GET_SG_TABLESIZE:
		वापस put_user(sdp->sg_tablesize, ip);
	हाल SG_SET_RESERVED_SIZE:
		result = get_user(val, ip);
		अगर (result)
			वापस result;
                अगर (val < 0)
                        वापस -EINVAL;
		val = min_t(पूर्णांक, val,
			    max_sectors_bytes(sdp->device->request_queue));
		mutex_lock(&sfp->f_mutex);
		अगर (val != sfp->reserve.bufflen) अणु
			अगर (sfp->mmap_called ||
			    sfp->res_in_use) अणु
				mutex_unlock(&sfp->f_mutex);
				वापस -EBUSY;
			पूर्ण

			sg_हटाओ_scat(sfp, &sfp->reserve);
			sg_build_reserve(sfp, val);
		पूर्ण
		mutex_unlock(&sfp->f_mutex);
		वापस 0;
	हाल SG_GET_RESERVED_SIZE:
		val = min_t(पूर्णांक, sfp->reserve.bufflen,
			    max_sectors_bytes(sdp->device->request_queue));
		वापस put_user(val, ip);
	हाल SG_SET_COMMAND_Q:
		result = get_user(val, ip);
		अगर (result)
			वापस result;
		sfp->cmd_q = val ? 1 : 0;
		वापस 0;
	हाल SG_GET_COMMAND_Q:
		वापस put_user((पूर्णांक) sfp->cmd_q, ip);
	हाल SG_SET_KEEP_ORPHAN:
		result = get_user(val, ip);
		अगर (result)
			वापस result;
		sfp->keep_orphan = val;
		वापस 0;
	हाल SG_GET_KEEP_ORPHAN:
		वापस put_user((पूर्णांक) sfp->keep_orphan, ip);
	हाल SG_NEXT_CMD_LEN:
		result = get_user(val, ip);
		अगर (result)
			वापस result;
		अगर (val > SG_MAX_CDB_SIZE)
			वापस -ENOMEM;
		sfp->next_cmd_len = (val > 0) ? val : 0;
		वापस 0;
	हाल SG_GET_VERSION_NUM:
		वापस put_user(sg_version_num, ip);
	हाल SG_GET_ACCESS_COUNT:
		/* faked - we करोn't have a real access count anymore */
		val = (sdp->device ? 1 : 0);
		वापस put_user(val, ip);
	हाल SG_GET_REQUEST_TABLE:
		अणु
			sg_req_info_t *rinfo;

			rinfo = kसुस्मृति(SG_MAX_QUEUE, SZ_SG_REQ_INFO,
					GFP_KERNEL);
			अगर (!rinfo)
				वापस -ENOMEM;
			पढ़ो_lock_irqsave(&sfp->rq_list_lock, अगरlags);
			sg_fill_request_table(sfp, rinfo);
			पढ़ो_unlock_irqrestore(&sfp->rq_list_lock, अगरlags);
	#अगर_घोषित CONFIG_COMPAT
			अगर (in_compat_syscall())
				result = put_compat_request_table(p, rinfo);
			अन्यथा
	#पूर्ण_अगर
				result = copy_to_user(p, rinfo,
						      SZ_SG_REQ_INFO * SG_MAX_QUEUE);
			result = result ? -EFAULT : 0;
			kमुक्त(rinfo);
			वापस result;
		पूर्ण
	हाल SG_EMULATED_HOST:
		अगर (atomic_पढ़ो(&sdp->detaching))
			वापस -ENODEV;
		वापस put_user(sdp->device->host->hostt->emulated, ip);
	हाल SCSI_IOCTL_SEND_COMMAND:
		अगर (atomic_पढ़ो(&sdp->detaching))
			वापस -ENODEV;
		वापस sg_scsi_ioctl(sdp->device->request_queue, शून्य, filp->f_mode, p);
	हाल SG_SET_DEBUG:
		result = get_user(val, ip);
		अगर (result)
			वापस result;
		sdp->sgdebug = (अक्षर) val;
		वापस 0;
	हाल BLKSECTGET:
		वापस put_user(max_sectors_bytes(sdp->device->request_queue),
				ip);
	हाल BLKTRACESETUP:
		वापस blk_trace_setup(sdp->device->request_queue,
				       sdp->disk->disk_name,
				       MKDEV(SCSI_GENERIC_MAJOR, sdp->index),
				       शून्य, p);
	हाल BLKTRACESTART:
		वापस blk_trace_startstop(sdp->device->request_queue, 1);
	हाल BLKTRACESTOP:
		वापस blk_trace_startstop(sdp->device->request_queue, 0);
	हाल BLKTRACETEARDOWN:
		वापस blk_trace_हटाओ(sdp->device->request_queue);
	हाल SCSI_IOCTL_GET_IDLUN:
	हाल SCSI_IOCTL_GET_BUS_NUMBER:
	हाल SCSI_IOCTL_PROBE_HOST:
	हाल SG_GET_TRANSFORM:
	हाल SG_SCSI_RESET:
		अगर (atomic_पढ़ो(&sdp->detaching))
			वापस -ENODEV;
		अवरोध;
	शेष:
		अगर (पढ़ो_only)
			वापस -EPERM;	/* करोn't know so take safe approach */
		अवरोध;
	पूर्ण

	result = scsi_ioctl_block_when_processing_errors(sdp->device,
			cmd_in, filp->f_flags & O_NDELAY);
	अगर (result)
		वापस result;

	वापस -ENOIOCTLCMD;
पूर्ण

अटल दीर्घ
sg_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd_in, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *p = (व्योम __user *)arg;
	Sg_device *sdp;
	Sg_fd *sfp;
	पूर्णांक ret;

	अगर ((!(sfp = (Sg_fd *) filp->निजी_data)) || (!(sdp = sfp->parentdp)))
		वापस -ENXIO;

	ret = sg_ioctl_common(filp, sdp, sfp, cmd_in, p);
	अगर (ret != -ENOIOCTLCMD)
		वापस ret;

	वापस scsi_ioctl(sdp->device, cmd_in, p);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ sg_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd_in, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *p = compat_ptr(arg);
	Sg_device *sdp;
	Sg_fd *sfp;
	पूर्णांक ret;

	अगर ((!(sfp = (Sg_fd *) filp->निजी_data)) || (!(sdp = sfp->parentdp)))
		वापस -ENXIO;

	ret = sg_ioctl_common(filp, sdp, sfp, cmd_in, p);
	अगर (ret != -ENOIOCTLCMD)
		वापस ret;

	वापस scsi_compat_ioctl(sdp->device, cmd_in, p);
पूर्ण
#पूर्ण_अगर

अटल __poll_t
sg_poll(काष्ठा file *filp, poll_table * रुको)
अणु
	__poll_t res = 0;
	Sg_device *sdp;
	Sg_fd *sfp;
	Sg_request *srp;
	पूर्णांक count = 0;
	अचिन्हित दीर्घ अगरlags;

	sfp = filp->निजी_data;
	अगर (!sfp)
		वापस EPOLLERR;
	sdp = sfp->parentdp;
	अगर (!sdp)
		वापस EPOLLERR;
	poll_रुको(filp, &sfp->पढ़ो_रुको, रुको);
	पढ़ो_lock_irqsave(&sfp->rq_list_lock, अगरlags);
	list_क्रम_each_entry(srp, &sfp->rq_list, entry) अणु
		/* अगर any पढ़ो रुकोing, flag it */
		अगर ((0 == res) && (1 == srp->करोne) && (!srp->sg_io_owned))
			res = EPOLLIN | EPOLLRDNORM;
		++count;
	पूर्ण
	पढ़ो_unlock_irqrestore(&sfp->rq_list_lock, अगरlags);

	अगर (atomic_पढ़ो(&sdp->detaching))
		res |= EPOLLHUP;
	अन्यथा अगर (!sfp->cmd_q) अणु
		अगर (0 == count)
			res |= EPOLLOUT | EPOLLWRNORM;
	पूर्ण अन्यथा अगर (count < SG_MAX_QUEUE)
		res |= EPOLLOUT | EPOLLWRNORM;
	SCSI_LOG_TIMEOUT(3, sg_prपूर्णांकk(KERN_INFO, sdp,
				      "sg_poll: res=0x%x\n", (__क्रमce u32) res));
	वापस res;
पूर्ण

अटल पूर्णांक
sg_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक mode)
अणु
	Sg_device *sdp;
	Sg_fd *sfp;

	अगर ((!(sfp = (Sg_fd *) filp->निजी_data)) || (!(sdp = sfp->parentdp)))
		वापस -ENXIO;
	SCSI_LOG_TIMEOUT(3, sg_prपूर्णांकk(KERN_INFO, sdp,
				      "sg_fasync: mode=%d\n", mode));

	वापस fasync_helper(fd, filp, mode, &sfp->async_qp);
पूर्ण

अटल vm_fault_t
sg_vma_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	Sg_fd *sfp;
	अचिन्हित दीर्घ offset, len, sa;
	Sg_scatter_hold *rsv_schp;
	पूर्णांक k, length;

	अगर ((शून्य == vma) || (!(sfp = (Sg_fd *) vma->vm_निजी_data)))
		वापस VM_FAULT_SIGBUS;
	rsv_schp = &sfp->reserve;
	offset = vmf->pgoff << PAGE_SHIFT;
	अगर (offset >= rsv_schp->bufflen)
		वापस VM_FAULT_SIGBUS;
	SCSI_LOG_TIMEOUT(3, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
				      "sg_vma_fault: offset=%lu, scatg=%d\n",
				      offset, rsv_schp->k_use_sg));
	sa = vma->vm_start;
	length = 1 << (PAGE_SHIFT + rsv_schp->page_order);
	क्रम (k = 0; k < rsv_schp->k_use_sg && sa < vma->vm_end; k++) अणु
		len = vma->vm_end - sa;
		len = (len < length) ? len : length;
		अगर (offset < len) अणु
			काष्ठा page *page = nth_page(rsv_schp->pages[k],
						     offset >> PAGE_SHIFT);
			get_page(page);	/* increment page count */
			vmf->page = page;
			वापस 0; /* success */
		पूर्ण
		sa += len;
		offset -= len;
	पूर्ण

	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा sg_mmap_vm_ops = अणु
	.fault = sg_vma_fault,
पूर्ण;

अटल पूर्णांक
sg_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	Sg_fd *sfp;
	अचिन्हित दीर्घ req_sz, len, sa;
	Sg_scatter_hold *rsv_schp;
	पूर्णांक k, length;
	पूर्णांक ret = 0;

	अगर ((!filp) || (!vma) || (!(sfp = (Sg_fd *) filp->निजी_data)))
		वापस -ENXIO;
	req_sz = vma->vm_end - vma->vm_start;
	SCSI_LOG_TIMEOUT(3, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
				      "sg_mmap starting, vm_start=%p, len=%d\n",
				      (व्योम *) vma->vm_start, (पूर्णांक) req_sz));
	अगर (vma->vm_pgoff)
		वापस -EINVAL;	/* want no offset */
	rsv_schp = &sfp->reserve;
	mutex_lock(&sfp->f_mutex);
	अगर (req_sz > rsv_schp->bufflen) अणु
		ret = -ENOMEM;	/* cannot map more than reserved buffer */
		जाओ out;
	पूर्ण

	sa = vma->vm_start;
	length = 1 << (PAGE_SHIFT + rsv_schp->page_order);
	क्रम (k = 0; k < rsv_schp->k_use_sg && sa < vma->vm_end; k++) अणु
		len = vma->vm_end - sa;
		len = (len < length) ? len : length;
		sa += len;
	पूर्ण

	sfp->mmap_called = 1;
	vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_निजी_data = sfp;
	vma->vm_ops = &sg_mmap_vm_ops;
out:
	mutex_unlock(&sfp->f_mutex);
	वापस ret;
पूर्ण

अटल व्योम
sg_rq_end_io_usercontext(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sg_request *srp = container_of(work, काष्ठा sg_request, ew.work);
	काष्ठा sg_fd *sfp = srp->parentfp;

	sg_finish_rem_req(srp);
	sg_हटाओ_request(sfp, srp);
	kref_put(&sfp->f_ref, sg_हटाओ_sfp);
पूर्ण

/*
 * This function is a "bottom half" handler that is called by the mid
 * level when a command is completed (or has failed).
 */
अटल व्योम
sg_rq_end_io(काष्ठा request *rq, blk_status_t status)
अणु
	काष्ठा sg_request *srp = rq->end_io_data;
	काष्ठा scsi_request *req = scsi_req(rq);
	Sg_device *sdp;
	Sg_fd *sfp;
	अचिन्हित दीर्घ अगरlags;
	अचिन्हित पूर्णांक ms;
	अक्षर *sense;
	पूर्णांक result, resid, करोne = 1;

	अगर (WARN_ON(srp->करोne != 0))
		वापस;

	sfp = srp->parentfp;
	अगर (WARN_ON(sfp == शून्य))
		वापस;

	sdp = sfp->parentdp;
	अगर (unlikely(atomic_पढ़ो(&sdp->detaching)))
		pr_info("%s: device detaching\n", __func__);

	sense = req->sense;
	result = req->result;
	resid = req->resid_len;

	SCSI_LOG_TIMEOUT(4, sg_prपूर्णांकk(KERN_INFO, sdp,
				      "sg_cmd_done: pack_id=%d, res=0x%x\n",
				      srp->header.pack_id, result));
	srp->header.resid = resid;
	ms = jअगरfies_to_msecs(jअगरfies);
	srp->header.duration = (ms > srp->header.duration) ?
				(ms - srp->header.duration) : 0;
	अगर (0 != result) अणु
		काष्ठा scsi_sense_hdr sshdr;

		srp->header.status = 0xff & result;
		srp->header.masked_status = status_byte(result);
		srp->header.msg_status = msg_byte(result);
		srp->header.host_status = host_byte(result);
		srp->header.driver_status = driver_byte(result);
		अगर ((sdp->sgdebug > 0) &&
		    ((CHECK_CONDITION == srp->header.masked_status) ||
		     (COMMAND_TERMINATED == srp->header.masked_status)))
			__scsi_prपूर्णांक_sense(sdp->device, __func__, sense,
					   SCSI_SENSE_BUFFERSIZE);

		/* Following अगर statement is a patch supplied by Eric Youngdale */
		अगर (driver_byte(result) != 0
		    && scsi_normalize_sense(sense, SCSI_SENSE_BUFFERSIZE, &sshdr)
		    && !scsi_sense_is_deferred(&sshdr)
		    && sshdr.sense_key == UNIT_ATTENTION
		    && sdp->device->removable) अणु
			/* Detected possible disc change. Set the bit - this */
			/* may be used अगर there are fileप्रणालीs using this device */
			sdp->device->changed = 1;
		पूर्ण
	पूर्ण

	अगर (req->sense_len)
		स_नकल(srp->sense_b, req->sense, SCSI_SENSE_BUFFERSIZE);

	/* Rely on ग_लिखो phase to clean out srp status values, so no "else" */

	/*
	 * Free the request as soon as it is complete so that its resources
	 * can be reused without रुकोing क्रम userspace to पढ़ो() the
	 * result.  But keep the associated bio (अगर any) around until
	 * blk_rq_unmap_user() can be called from user context.
	 */
	srp->rq = शून्य;
	scsi_req_मुक्त_cmd(scsi_req(rq));
	blk_put_request(rq);

	ग_लिखो_lock_irqsave(&sfp->rq_list_lock, अगरlags);
	अगर (unlikely(srp->orphan)) अणु
		अगर (sfp->keep_orphan)
			srp->sg_io_owned = 0;
		अन्यथा
			करोne = 0;
	पूर्ण
	srp->करोne = करोne;
	ग_लिखो_unlock_irqrestore(&sfp->rq_list_lock, अगरlags);

	अगर (likely(करोne)) अणु
		/* Now wake up any sg_पढ़ो() that is रुकोing क्रम this
		 * packet.
		 */
		wake_up_पूर्णांकerruptible(&sfp->पढ़ो_रुको);
		समाप्त_fasync(&sfp->async_qp, SIGPOLL, POLL_IN);
		kref_put(&sfp->f_ref, sg_हटाओ_sfp);
	पूर्ण अन्यथा अणु
		INIT_WORK(&srp->ew.work, sg_rq_end_io_usercontext);
		schedule_work(&srp->ew.work);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations sg_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = sg_पढ़ो,
	.ग_लिखो = sg_ग_लिखो,
	.poll = sg_poll,
	.unlocked_ioctl = sg_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = sg_compat_ioctl,
#पूर्ण_अगर
	.खोलो = sg_खोलो,
	.mmap = sg_mmap,
	.release = sg_release,
	.fasync = sg_fasync,
	.llseek = no_llseek,
पूर्ण;

अटल काष्ठा class *sg_sysfs_class;

अटल पूर्णांक sg_sysfs_valid = 0;

अटल Sg_device *
sg_alloc(काष्ठा gendisk *disk, काष्ठा scsi_device *scsidp)
अणु
	काष्ठा request_queue *q = scsidp->request_queue;
	Sg_device *sdp;
	अचिन्हित दीर्घ अगरlags;
	पूर्णांक error;
	u32 k;

	sdp = kzalloc(माप(Sg_device), GFP_KERNEL);
	अगर (!sdp) अणु
		sdev_prपूर्णांकk(KERN_WARNING, scsidp, "%s: kmalloc Sg_device "
			    "failure\n", __func__);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	idr_preload(GFP_KERNEL);
	ग_लिखो_lock_irqsave(&sg_index_lock, अगरlags);

	error = idr_alloc(&sg_index_idr, sdp, 0, SG_MAX_DEVS, GFP_NOWAIT);
	अगर (error < 0) अणु
		अगर (error == -ENOSPC) अणु
			sdev_prपूर्णांकk(KERN_WARNING, scsidp,
				    "Unable to attach sg device type=%d, minor number exceeds %d\n",
				    scsidp->type, SG_MAX_DEVS - 1);
			error = -ENODEV;
		पूर्ण अन्यथा अणु
			sdev_prपूर्णांकk(KERN_WARNING, scsidp, "%s: idr "
				    "allocation Sg_device failure: %d\n",
				    __func__, error);
		पूर्ण
		जाओ out_unlock;
	पूर्ण
	k = error;

	SCSI_LOG_TIMEOUT(3, sdev_prपूर्णांकk(KERN_INFO, scsidp,
					"sg_alloc: dev=%d \n", k));
	प्र_लिखो(disk->disk_name, "sg%d", k);
	disk->first_minor = k;
	sdp->disk = disk;
	sdp->device = scsidp;
	mutex_init(&sdp->खोलो_rel_lock);
	INIT_LIST_HEAD(&sdp->sfds);
	init_रुकोqueue_head(&sdp->खोलो_रुको);
	atomic_set(&sdp->detaching, 0);
	rwlock_init(&sdp->sfd_lock);
	sdp->sg_tablesize = queue_max_segments(q);
	sdp->index = k;
	kref_init(&sdp->d_ref);
	error = 0;

out_unlock:
	ग_लिखो_unlock_irqrestore(&sg_index_lock, अगरlags);
	idr_preload_end();

	अगर (error) अणु
		kमुक्त(sdp);
		वापस ERR_PTR(error);
	पूर्ण
	वापस sdp;
पूर्ण

अटल पूर्णांक
sg_add_device(काष्ठा device *cl_dev, काष्ठा class_पूर्णांकerface *cl_पूर्णांकf)
अणु
	काष्ठा scsi_device *scsidp = to_scsi_device(cl_dev->parent);
	काष्ठा gendisk *disk;
	Sg_device *sdp = शून्य;
	काष्ठा cdev * cdev = शून्य;
	पूर्णांक error;
	अचिन्हित दीर्घ अगरlags;

	disk = alloc_disk(1);
	अगर (!disk) अणु
		pr_warn("%s: alloc_disk failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	disk->major = SCSI_GENERIC_MAJOR;

	error = -ENOMEM;
	cdev = cdev_alloc();
	अगर (!cdev) अणु
		pr_warn("%s: cdev_alloc failed\n", __func__);
		जाओ out;
	पूर्ण
	cdev->owner = THIS_MODULE;
	cdev->ops = &sg_fops;

	sdp = sg_alloc(disk, scsidp);
	अगर (IS_ERR(sdp)) अणु
		pr_warn("%s: sg_alloc failed\n", __func__);
		error = PTR_ERR(sdp);
		जाओ out;
	पूर्ण

	error = cdev_add(cdev, MKDEV(SCSI_GENERIC_MAJOR, sdp->index), 1);
	अगर (error)
		जाओ cdev_add_err;

	sdp->cdev = cdev;
	अगर (sg_sysfs_valid) अणु
		काष्ठा device *sg_class_member;

		sg_class_member = device_create(sg_sysfs_class, cl_dev->parent,
						MKDEV(SCSI_GENERIC_MAJOR,
						      sdp->index),
						sdp, "%s", disk->disk_name);
		अगर (IS_ERR(sg_class_member)) अणु
			pr_err("%s: device_create failed\n", __func__);
			error = PTR_ERR(sg_class_member);
			जाओ cdev_add_err;
		पूर्ण
		error = sysfs_create_link(&scsidp->sdev_gendev.kobj,
					  &sg_class_member->kobj, "generic");
		अगर (error)
			pr_err("%s: unable to make symlink 'generic' back "
			       "to sg%d\n", __func__, sdp->index);
	पूर्ण अन्यथा
		pr_warn("%s: sg_sys Invalid\n", __func__);

	sdev_prपूर्णांकk(KERN_NOTICE, scsidp, "Attached scsi generic sg%d "
		    "type %d\n", sdp->index, scsidp->type);

	dev_set_drvdata(cl_dev, sdp);

	वापस 0;

cdev_add_err:
	ग_लिखो_lock_irqsave(&sg_index_lock, अगरlags);
	idr_हटाओ(&sg_index_idr, sdp->index);
	ग_लिखो_unlock_irqrestore(&sg_index_lock, अगरlags);
	kमुक्त(sdp);

out:
	put_disk(disk);
	अगर (cdev)
		cdev_del(cdev);
	वापस error;
पूर्ण

अटल व्योम
sg_device_destroy(काष्ठा kref *kref)
अणु
	काष्ठा sg_device *sdp = container_of(kref, काष्ठा sg_device, d_ref);
	अचिन्हित दीर्घ flags;

	/* CAUTION!  Note that the device can still be found via idr_find()
	 * even though the refcount is 0.  Thereक्रमe, करो idr_हटाओ() BEFORE
	 * any other cleanup.
	 */

	ग_लिखो_lock_irqsave(&sg_index_lock, flags);
	idr_हटाओ(&sg_index_idr, sdp->index);
	ग_लिखो_unlock_irqrestore(&sg_index_lock, flags);

	SCSI_LOG_TIMEOUT(3,
		sg_prपूर्णांकk(KERN_INFO, sdp, "sg_device_destroy\n"));

	put_disk(sdp->disk);
	kमुक्त(sdp);
पूर्ण

अटल व्योम
sg_हटाओ_device(काष्ठा device *cl_dev, काष्ठा class_पूर्णांकerface *cl_पूर्णांकf)
अणु
	काष्ठा scsi_device *scsidp = to_scsi_device(cl_dev->parent);
	Sg_device *sdp = dev_get_drvdata(cl_dev);
	अचिन्हित दीर्घ अगरlags;
	Sg_fd *sfp;
	पूर्णांक val;

	अगर (!sdp)
		वापस;
	/* want sdp->detaching non-zero as soon as possible */
	val = atomic_inc_वापस(&sdp->detaching);
	अगर (val > 1)
		वापस; /* only want to करो following once per device */

	SCSI_LOG_TIMEOUT(3, sg_prपूर्णांकk(KERN_INFO, sdp,
				      "%s\n", __func__));

	पढ़ो_lock_irqsave(&sdp->sfd_lock, अगरlags);
	list_क्रम_each_entry(sfp, &sdp->sfds, sfd_siblings) अणु
		wake_up_पूर्णांकerruptible_all(&sfp->पढ़ो_रुको);
		समाप्त_fasync(&sfp->async_qp, SIGPOLL, POLL_HUP);
	पूर्ण
	wake_up_पूर्णांकerruptible_all(&sdp->खोलो_रुको);
	पढ़ो_unlock_irqrestore(&sdp->sfd_lock, अगरlags);

	sysfs_हटाओ_link(&scsidp->sdev_gendev.kobj, "generic");
	device_destroy(sg_sysfs_class, MKDEV(SCSI_GENERIC_MAJOR, sdp->index));
	cdev_del(sdp->cdev);
	sdp->cdev = शून्य;

	kref_put(&sdp->d_ref, sg_device_destroy);
पूर्ण

module_param_named(scatter_elem_sz, scatter_elem_sz, पूर्णांक, S_IRUGO | S_IWUSR);
module_param_named(def_reserved_size, def_reserved_size, पूर्णांक,
		   S_IRUGO | S_IWUSR);
module_param_named(allow_dio, sg_allow_dio, पूर्णांक, S_IRUGO | S_IWUSR);

MODULE_AUTHOR("Douglas Gilbert");
MODULE_DESCRIPTION("SCSI generic (sg) driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(SG_VERSION_STR);
MODULE_ALIAS_CHARDEV_MAJOR(SCSI_GENERIC_MAJOR);

MODULE_PARM_DESC(scatter_elem_sz, "scatter gather element "
                "size (default: max(SG_SCATTER_SZ, PAGE_SIZE))");
MODULE_PARM_DESC(def_reserved_size, "size of buffer reserved for each fd");
MODULE_PARM_DESC(allow_dio, "allow direct I/O (default: 0 (disallow))");

अटल पूर्णांक __init
init_sg(व्योम)
अणु
	पूर्णांक rc;

	अगर (scatter_elem_sz < PAGE_SIZE) अणु
		scatter_elem_sz = PAGE_SIZE;
		scatter_elem_sz_prev = scatter_elem_sz;
	पूर्ण
	अगर (def_reserved_size >= 0)
		sg_big_buff = def_reserved_size;
	अन्यथा
		def_reserved_size = sg_big_buff;

	rc = रेजिस्टर_chrdev_region(MKDEV(SCSI_GENERIC_MAJOR, 0), 
				    SG_MAX_DEVS, "sg");
	अगर (rc)
		वापस rc;
        sg_sysfs_class = class_create(THIS_MODULE, "scsi_generic");
        अगर ( IS_ERR(sg_sysfs_class) ) अणु
		rc = PTR_ERR(sg_sysfs_class);
		जाओ err_out;
        पूर्ण
	sg_sysfs_valid = 1;
	rc = scsi_रेजिस्टर_पूर्णांकerface(&sg_पूर्णांकerface);
	अगर (0 == rc) अणु
#अगर_घोषित CONFIG_SCSI_PROC_FS
		sg_proc_init();
#पूर्ण_अगर				/* CONFIG_SCSI_PROC_FS */
		वापस 0;
	पूर्ण
	class_destroy(sg_sysfs_class);
err_out:
	unरेजिस्टर_chrdev_region(MKDEV(SCSI_GENERIC_MAJOR, 0), SG_MAX_DEVS);
	वापस rc;
पूर्ण

अटल व्योम __निकास
निकास_sg(व्योम)
अणु
#अगर_घोषित CONFIG_SCSI_PROC_FS
	हटाओ_proc_subtree("scsi/sg", शून्य);
#पूर्ण_अगर				/* CONFIG_SCSI_PROC_FS */
	scsi_unरेजिस्टर_पूर्णांकerface(&sg_पूर्णांकerface);
	class_destroy(sg_sysfs_class);
	sg_sysfs_valid = 0;
	unरेजिस्टर_chrdev_region(MKDEV(SCSI_GENERIC_MAJOR, 0),
				 SG_MAX_DEVS);
	idr_destroy(&sg_index_idr);
पूर्ण

अटल पूर्णांक
sg_start_req(Sg_request *srp, अचिन्हित अक्षर *cmd)
अणु
	पूर्णांक res;
	काष्ठा request *rq;
	काष्ठा scsi_request *req;
	Sg_fd *sfp = srp->parentfp;
	sg_io_hdr_t *hp = &srp->header;
	पूर्णांक dxfer_len = (पूर्णांक) hp->dxfer_len;
	पूर्णांक dxfer_dir = hp->dxfer_direction;
	अचिन्हित पूर्णांक iov_count = hp->iovec_count;
	Sg_scatter_hold *req_schp = &srp->data;
	Sg_scatter_hold *rsv_schp = &sfp->reserve;
	काष्ठा request_queue *q = sfp->parentdp->device->request_queue;
	काष्ठा rq_map_data *md, map_data;
	पूर्णांक rw = hp->dxfer_direction == SG_DXFER_TO_DEV ? WRITE : READ;
	अचिन्हित अक्षर *दीर्घ_cmdp = शून्य;

	SCSI_LOG_TIMEOUT(4, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
				      "sg_start_req: dxfer_len=%d\n",
				      dxfer_len));

	अगर (hp->cmd_len > BLK_MAX_CDB) अणु
		दीर्घ_cmdp = kzalloc(hp->cmd_len, GFP_KERNEL);
		अगर (!दीर्घ_cmdp)
			वापस -ENOMEM;
	पूर्ण

	/*
	 * NOTE
	 *
	 * With scsi-mq enabled, there are a fixed number of pपुनः_स्मृतिated
	 * requests equal in number to shost->can_queue.  If all of the
	 * pपुनः_स्मृतिated requests are alपढ़ोy in use, then blk_get_request()
	 * will sleep until an active command completes, मुक्तing up a request.
	 * Although रुकोing in an asynchronous पूर्णांकerface is less than ideal, we
	 * करो not want to use BLK_MQ_REQ_NOWAIT here because userspace might
	 * not expect an EWOULDBLOCK from this condition.
	 */
	rq = blk_get_request(q, hp->dxfer_direction == SG_DXFER_TO_DEV ?
			REQ_OP_SCSI_OUT : REQ_OP_SCSI_IN, 0);
	अगर (IS_ERR(rq)) अणु
		kमुक्त(दीर्घ_cmdp);
		वापस PTR_ERR(rq);
	पूर्ण
	req = scsi_req(rq);

	अगर (hp->cmd_len > BLK_MAX_CDB)
		req->cmd = दीर्घ_cmdp;
	स_नकल(req->cmd, cmd, hp->cmd_len);
	req->cmd_len = hp->cmd_len;

	srp->rq = rq;
	rq->end_io_data = srp;
	req->retries = SG_DEFAULT_RETRIES;

	अगर ((dxfer_len <= 0) || (dxfer_dir == SG_DXFER_NONE))
		वापस 0;

	अगर (sg_allow_dio && hp->flags & SG_FLAG_सूचीECT_IO &&
	    dxfer_dir != SG_DXFER_UNKNOWN && !iov_count &&
	    blk_rq_aligned(q, (अचिन्हित दीर्घ)hp->dxferp, dxfer_len))
		md = शून्य;
	अन्यथा
		md = &map_data;

	अगर (md) अणु
		mutex_lock(&sfp->f_mutex);
		अगर (dxfer_len <= rsv_schp->bufflen &&
		    !sfp->res_in_use) अणु
			sfp->res_in_use = 1;
			sg_link_reserve(sfp, srp, dxfer_len);
		पूर्ण अन्यथा अगर (hp->flags & SG_FLAG_MMAP_IO) अणु
			res = -EBUSY; /* sfp->res_in_use == 1 */
			अगर (dxfer_len > rsv_schp->bufflen)
				res = -ENOMEM;
			mutex_unlock(&sfp->f_mutex);
			वापस res;
		पूर्ण अन्यथा अणु
			res = sg_build_indirect(req_schp, sfp, dxfer_len);
			अगर (res) अणु
				mutex_unlock(&sfp->f_mutex);
				वापस res;
			पूर्ण
		पूर्ण
		mutex_unlock(&sfp->f_mutex);

		md->pages = req_schp->pages;
		md->page_order = req_schp->page_order;
		md->nr_entries = req_schp->k_use_sg;
		md->offset = 0;
		md->null_mapped = hp->dxferp ? 0 : 1;
		अगर (dxfer_dir == SG_DXFER_TO_FROM_DEV)
			md->from_user = 1;
		अन्यथा
			md->from_user = 0;
	पूर्ण

	अगर (iov_count) अणु
		काष्ठा iovec *iov = शून्य;
		काष्ठा iov_iter i;

		res = import_iovec(rw, hp->dxferp, iov_count, 0, &iov, &i);
		अगर (res < 0)
			वापस res;

		iov_iter_truncate(&i, hp->dxfer_len);
		अगर (!iov_iter_count(&i)) अणु
			kमुक्त(iov);
			वापस -EINVAL;
		पूर्ण

		res = blk_rq_map_user_iov(q, rq, md, &i, GFP_ATOMIC);
		kमुक्त(iov);
	पूर्ण अन्यथा
		res = blk_rq_map_user(q, rq, md, hp->dxferp,
				      hp->dxfer_len, GFP_ATOMIC);

	अगर (!res) अणु
		srp->bio = rq->bio;

		अगर (!md) अणु
			req_schp->dio_in_use = 1;
			hp->info |= SG_INFO_सूचीECT_IO;
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक
sg_finish_rem_req(Sg_request *srp)
अणु
	पूर्णांक ret = 0;

	Sg_fd *sfp = srp->parentfp;
	Sg_scatter_hold *req_schp = &srp->data;

	SCSI_LOG_TIMEOUT(4, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
				      "sg_finish_rem_req: res_used=%d\n",
				      (पूर्णांक) srp->res_used));
	अगर (srp->bio)
		ret = blk_rq_unmap_user(srp->bio);

	अगर (srp->rq) अणु
		scsi_req_मुक्त_cmd(scsi_req(srp->rq));
		blk_put_request(srp->rq);
	पूर्ण

	अगर (srp->res_used)
		sg_unlink_reserve(sfp, srp);
	अन्यथा
		sg_हटाओ_scat(sfp, req_schp);

	वापस ret;
पूर्ण

अटल पूर्णांक
sg_build_sgat(Sg_scatter_hold * schp, स्थिर Sg_fd * sfp, पूर्णांक tablesize)
अणु
	पूर्णांक sg_bufflen = tablesize * माप(काष्ठा page *);
	gfp_t gfp_flags = GFP_ATOMIC | __GFP_NOWARN;

	schp->pages = kzalloc(sg_bufflen, gfp_flags);
	अगर (!schp->pages)
		वापस -ENOMEM;
	schp->sglist_len = sg_bufflen;
	वापस tablesize;	/* number of scat_gath elements allocated */
पूर्ण

अटल पूर्णांक
sg_build_indirect(Sg_scatter_hold * schp, Sg_fd * sfp, पूर्णांक buff_size)
अणु
	पूर्णांक ret_sz = 0, i, k, rem_sz, num, mx_sc_elems;
	पूर्णांक sg_tablesize = sfp->parentdp->sg_tablesize;
	पूर्णांक blk_size = buff_size, order;
	gfp_t gfp_mask = GFP_ATOMIC | __GFP_COMP | __GFP_NOWARN | __GFP_ZERO;

	अगर (blk_size < 0)
		वापस -EFAULT;
	अगर (0 == blk_size)
		++blk_size;	/* करोn't know why */
	/* round request up to next highest SG_SECTOR_SZ byte boundary */
	blk_size = ALIGN(blk_size, SG_SECTOR_SZ);
	SCSI_LOG_TIMEOUT(4, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
		"sg_build_indirect: buff_size=%d, blk_size=%d\n",
		buff_size, blk_size));

	/* N.B. ret_sz carried पूर्णांकo this block ... */
	mx_sc_elems = sg_build_sgat(schp, sfp, sg_tablesize);
	अगर (mx_sc_elems < 0)
		वापस mx_sc_elems;	/* most likely -ENOMEM */

	num = scatter_elem_sz;
	अगर (unlikely(num != scatter_elem_sz_prev)) अणु
		अगर (num < PAGE_SIZE) अणु
			scatter_elem_sz = PAGE_SIZE;
			scatter_elem_sz_prev = PAGE_SIZE;
		पूर्ण अन्यथा
			scatter_elem_sz_prev = num;
	पूर्ण

	order = get_order(num);
retry:
	ret_sz = 1 << (PAGE_SHIFT + order);

	क्रम (k = 0, rem_sz = blk_size; rem_sz > 0 && k < mx_sc_elems;
	     k++, rem_sz -= ret_sz) अणु

		num = (rem_sz > scatter_elem_sz_prev) ?
			scatter_elem_sz_prev : rem_sz;

		schp->pages[k] = alloc_pages(gfp_mask, order);
		अगर (!schp->pages[k])
			जाओ out;

		अगर (num == scatter_elem_sz_prev) अणु
			अगर (unlikely(ret_sz > scatter_elem_sz_prev)) अणु
				scatter_elem_sz = ret_sz;
				scatter_elem_sz_prev = ret_sz;
			पूर्ण
		पूर्ण

		SCSI_LOG_TIMEOUT(5, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
				 "sg_build_indirect: k=%d, num=%d, ret_sz=%d\n",
				 k, num, ret_sz));
	पूर्ण		/* end of क्रम loop */

	schp->page_order = order;
	schp->k_use_sg = k;
	SCSI_LOG_TIMEOUT(5, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
			 "sg_build_indirect: k_use_sg=%d, rem_sz=%d\n",
			 k, rem_sz));

	schp->bufflen = blk_size;
	अगर (rem_sz > 0)	/* must have failed */
		वापस -ENOMEM;
	वापस 0;
out:
	क्रम (i = 0; i < k; i++)
		__मुक्त_pages(schp->pages[i], order);

	अगर (--order >= 0)
		जाओ retry;

	वापस -ENOMEM;
पूर्ण

अटल व्योम
sg_हटाओ_scat(Sg_fd * sfp, Sg_scatter_hold * schp)
अणु
	SCSI_LOG_TIMEOUT(4, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
			 "sg_remove_scat: k_use_sg=%d\n", schp->k_use_sg));
	अगर (schp->pages && schp->sglist_len > 0) अणु
		अगर (!schp->dio_in_use) अणु
			पूर्णांक k;

			क्रम (k = 0; k < schp->k_use_sg && schp->pages[k]; k++) अणु
				SCSI_LOG_TIMEOUT(5,
					sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
					"sg_remove_scat: k=%d, pg=0x%p\n",
					k, schp->pages[k]));
				__मुक्त_pages(schp->pages[k], schp->page_order);
			पूर्ण

			kमुक्त(schp->pages);
		पूर्ण
	पूर्ण
	स_रखो(schp, 0, माप (*schp));
पूर्ण

अटल पूर्णांक
sg_पढ़ो_oxfer(Sg_request * srp, अक्षर __user *outp, पूर्णांक num_पढ़ो_xfer)
अणु
	Sg_scatter_hold *schp = &srp->data;
	पूर्णांक k, num;

	SCSI_LOG_TIMEOUT(4, sg_prपूर्णांकk(KERN_INFO, srp->parentfp->parentdp,
			 "sg_read_oxfer: num_read_xfer=%d\n",
			 num_पढ़ो_xfer));
	अगर ((!outp) || (num_पढ़ो_xfer <= 0))
		वापस 0;

	num = 1 << (PAGE_SHIFT + schp->page_order);
	क्रम (k = 0; k < schp->k_use_sg && schp->pages[k]; k++) अणु
		अगर (num > num_पढ़ो_xfer) अणु
			अगर (copy_to_user(outp, page_address(schp->pages[k]),
					   num_पढ़ो_xfer))
				वापस -EFAULT;
			अवरोध;
		पूर्ण अन्यथा अणु
			अगर (copy_to_user(outp, page_address(schp->pages[k]),
					   num))
				वापस -EFAULT;
			num_पढ़ो_xfer -= num;
			अगर (num_पढ़ो_xfer <= 0)
				अवरोध;
			outp += num;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
sg_build_reserve(Sg_fd * sfp, पूर्णांक req_size)
अणु
	Sg_scatter_hold *schp = &sfp->reserve;

	SCSI_LOG_TIMEOUT(4, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
			 "sg_build_reserve: req_size=%d\n", req_size));
	करो अणु
		अगर (req_size < PAGE_SIZE)
			req_size = PAGE_SIZE;
		अगर (0 == sg_build_indirect(schp, sfp, req_size))
			वापस;
		अन्यथा
			sg_हटाओ_scat(sfp, schp);
		req_size >>= 1;	/* भागide by 2 */
	पूर्ण जबतक (req_size > (PAGE_SIZE / 2));
पूर्ण

अटल व्योम
sg_link_reserve(Sg_fd * sfp, Sg_request * srp, पूर्णांक size)
अणु
	Sg_scatter_hold *req_schp = &srp->data;
	Sg_scatter_hold *rsv_schp = &sfp->reserve;
	पूर्णांक k, num, rem;

	srp->res_used = 1;
	SCSI_LOG_TIMEOUT(4, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
			 "sg_link_reserve: size=%d\n", size));
	rem = size;

	num = 1 << (PAGE_SHIFT + rsv_schp->page_order);
	क्रम (k = 0; k < rsv_schp->k_use_sg; k++) अणु
		अगर (rem <= num) अणु
			req_schp->k_use_sg = k + 1;
			req_schp->sglist_len = rsv_schp->sglist_len;
			req_schp->pages = rsv_schp->pages;

			req_schp->bufflen = size;
			req_schp->page_order = rsv_schp->page_order;
			अवरोध;
		पूर्ण अन्यथा
			rem -= num;
	पूर्ण

	अगर (k >= rsv_schp->k_use_sg)
		SCSI_LOG_TIMEOUT(1, sg_prपूर्णांकk(KERN_INFO, sfp->parentdp,
				 "sg_link_reserve: BAD size\n"));
पूर्ण

अटल व्योम
sg_unlink_reserve(Sg_fd * sfp, Sg_request * srp)
अणु
	Sg_scatter_hold *req_schp = &srp->data;

	SCSI_LOG_TIMEOUT(4, sg_prपूर्णांकk(KERN_INFO, srp->parentfp->parentdp,
				      "sg_unlink_reserve: req->k_use_sg=%d\n",
				      (पूर्णांक) req_schp->k_use_sg));
	req_schp->k_use_sg = 0;
	req_schp->bufflen = 0;
	req_schp->pages = शून्य;
	req_schp->page_order = 0;
	req_schp->sglist_len = 0;
	srp->res_used = 0;
	/* Called without mutex lock to aव्योम deadlock */
	sfp->res_in_use = 0;
पूर्ण

अटल Sg_request *
sg_get_rq_mark(Sg_fd * sfp, पूर्णांक pack_id)
अणु
	Sg_request *resp;
	अचिन्हित दीर्घ अगरlags;

	ग_लिखो_lock_irqsave(&sfp->rq_list_lock, अगरlags);
	list_क्रम_each_entry(resp, &sfp->rq_list, entry) अणु
		/* look क्रम requests that are पढ़ोy + not SG_IO owned */
		अगर ((1 == resp->करोne) && (!resp->sg_io_owned) &&
		    ((-1 == pack_id) || (resp->header.pack_id == pack_id))) अणु
			resp->करोne = 2;	/* guard against other पढ़ोers */
			ग_लिखो_unlock_irqrestore(&sfp->rq_list_lock, अगरlags);
			वापस resp;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_irqrestore(&sfp->rq_list_lock, अगरlags);
	वापस शून्य;
पूर्ण

/* always adds to end of list */
अटल Sg_request *
sg_add_request(Sg_fd * sfp)
अणु
	पूर्णांक k;
	अचिन्हित दीर्घ अगरlags;
	Sg_request *rp = sfp->req_arr;

	ग_लिखो_lock_irqsave(&sfp->rq_list_lock, अगरlags);
	अगर (!list_empty(&sfp->rq_list)) अणु
		अगर (!sfp->cmd_q)
			जाओ out_unlock;

		क्रम (k = 0; k < SG_MAX_QUEUE; ++k, ++rp) अणु
			अगर (!rp->parentfp)
				अवरोध;
		पूर्ण
		अगर (k >= SG_MAX_QUEUE)
			जाओ out_unlock;
	पूर्ण
	स_रखो(rp, 0, माप (Sg_request));
	rp->parentfp = sfp;
	rp->header.duration = jअगरfies_to_msecs(jअगरfies);
	list_add_tail(&rp->entry, &sfp->rq_list);
	ग_लिखो_unlock_irqrestore(&sfp->rq_list_lock, अगरlags);
	वापस rp;
out_unlock:
	ग_लिखो_unlock_irqrestore(&sfp->rq_list_lock, अगरlags);
	वापस शून्य;
पूर्ण

/* Return of 1 क्रम found; 0 क्रम not found */
अटल पूर्णांक
sg_हटाओ_request(Sg_fd * sfp, Sg_request * srp)
अणु
	अचिन्हित दीर्घ अगरlags;
	पूर्णांक res = 0;

	अगर (!sfp || !srp || list_empty(&sfp->rq_list))
		वापस res;
	ग_लिखो_lock_irqsave(&sfp->rq_list_lock, अगरlags);
	अगर (!list_empty(&srp->entry)) अणु
		list_del(&srp->entry);
		srp->parentfp = शून्य;
		res = 1;
	पूर्ण
	ग_लिखो_unlock_irqrestore(&sfp->rq_list_lock, अगरlags);
	वापस res;
पूर्ण

अटल Sg_fd *
sg_add_sfp(Sg_device * sdp)
अणु
	Sg_fd *sfp;
	अचिन्हित दीर्घ अगरlags;
	पूर्णांक bufflen;

	sfp = kzalloc(माप(*sfp), GFP_ATOMIC | __GFP_NOWARN);
	अगर (!sfp)
		वापस ERR_PTR(-ENOMEM);

	init_रुकोqueue_head(&sfp->पढ़ो_रुको);
	rwlock_init(&sfp->rq_list_lock);
	INIT_LIST_HEAD(&sfp->rq_list);
	kref_init(&sfp->f_ref);
	mutex_init(&sfp->f_mutex);
	sfp->समयout = SG_DEFAULT_TIMEOUT;
	sfp->समयout_user = SG_DEFAULT_TIMEOUT_USER;
	sfp->क्रमce_packid = SG_DEF_FORCE_PACK_ID;
	sfp->cmd_q = SG_DEF_COMMAND_Q;
	sfp->keep_orphan = SG_DEF_KEEP_ORPHAN;
	sfp->parentdp = sdp;
	ग_लिखो_lock_irqsave(&sdp->sfd_lock, अगरlags);
	अगर (atomic_पढ़ो(&sdp->detaching)) अणु
		ग_लिखो_unlock_irqrestore(&sdp->sfd_lock, अगरlags);
		kमुक्त(sfp);
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	list_add_tail(&sfp->sfd_siblings, &sdp->sfds);
	ग_लिखो_unlock_irqrestore(&sdp->sfd_lock, अगरlags);
	SCSI_LOG_TIMEOUT(3, sg_prपूर्णांकk(KERN_INFO, sdp,
				      "sg_add_sfp: sfp=0x%p\n", sfp));
	अगर (unlikely(sg_big_buff != def_reserved_size))
		sg_big_buff = def_reserved_size;

	bufflen = min_t(पूर्णांक, sg_big_buff,
			max_sectors_bytes(sdp->device->request_queue));
	sg_build_reserve(sfp, bufflen);
	SCSI_LOG_TIMEOUT(3, sg_prपूर्णांकk(KERN_INFO, sdp,
				      "sg_add_sfp: bufflen=%d, k_use_sg=%d\n",
				      sfp->reserve.bufflen,
				      sfp->reserve.k_use_sg));

	kref_get(&sdp->d_ref);
	__module_get(THIS_MODULE);
	वापस sfp;
पूर्ण

अटल व्योम
sg_हटाओ_sfp_usercontext(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sg_fd *sfp = container_of(work, काष्ठा sg_fd, ew.work);
	काष्ठा sg_device *sdp = sfp->parentdp;
	Sg_request *srp;
	अचिन्हित दीर्घ अगरlags;

	/* Cleanup any responses which were never पढ़ो(). */
	ग_लिखो_lock_irqsave(&sfp->rq_list_lock, अगरlags);
	जबतक (!list_empty(&sfp->rq_list)) अणु
		srp = list_first_entry(&sfp->rq_list, Sg_request, entry);
		sg_finish_rem_req(srp);
		list_del(&srp->entry);
		srp->parentfp = शून्य;
	पूर्ण
	ग_लिखो_unlock_irqrestore(&sfp->rq_list_lock, अगरlags);

	अगर (sfp->reserve.bufflen > 0) अणु
		SCSI_LOG_TIMEOUT(6, sg_prपूर्णांकk(KERN_INFO, sdp,
				"sg_remove_sfp:    bufflen=%d, k_use_sg=%d\n",
				(पूर्णांक) sfp->reserve.bufflen,
				(पूर्णांक) sfp->reserve.k_use_sg));
		sg_हटाओ_scat(sfp, &sfp->reserve);
	पूर्ण

	SCSI_LOG_TIMEOUT(6, sg_prपूर्णांकk(KERN_INFO, sdp,
			"sg_remove_sfp: sfp=0x%p\n", sfp));
	kमुक्त(sfp);

	scsi_device_put(sdp->device);
	kref_put(&sdp->d_ref, sg_device_destroy);
	module_put(THIS_MODULE);
पूर्ण

अटल व्योम
sg_हटाओ_sfp(काष्ठा kref *kref)
अणु
	काष्ठा sg_fd *sfp = container_of(kref, काष्ठा sg_fd, f_ref);
	काष्ठा sg_device *sdp = sfp->parentdp;
	अचिन्हित दीर्घ अगरlags;

	ग_लिखो_lock_irqsave(&sdp->sfd_lock, अगरlags);
	list_del(&sfp->sfd_siblings);
	ग_लिखो_unlock_irqrestore(&sdp->sfd_lock, अगरlags);

	INIT_WORK(&sfp->ew.work, sg_हटाओ_sfp_usercontext);
	schedule_work(&sfp->ew.work);
पूर्ण

#अगर_घोषित CONFIG_SCSI_PROC_FS
अटल पूर्णांक
sg_idr_max_id(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	पूर्णांक *k = data;

	अगर (*k < id)
		*k = id;

	वापस 0;
पूर्ण

अटल पूर्णांक
sg_last_dev(व्योम)
अणु
	पूर्णांक k = -1;
	अचिन्हित दीर्घ अगरlags;

	पढ़ो_lock_irqsave(&sg_index_lock, अगरlags);
	idr_क्रम_each(&sg_index_idr, sg_idr_max_id, &k);
	पढ़ो_unlock_irqrestore(&sg_index_lock, अगरlags);
	वापस k + 1;		/* origin 1 */
पूर्ण
#पूर्ण_अगर

/* must be called with sg_index_lock held */
अटल Sg_device *sg_lookup_dev(पूर्णांक dev)
अणु
	वापस idr_find(&sg_index_idr, dev);
पूर्ण

अटल Sg_device *
sg_get_dev(पूर्णांक dev)
अणु
	काष्ठा sg_device *sdp;
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&sg_index_lock, flags);
	sdp = sg_lookup_dev(dev);
	अगर (!sdp)
		sdp = ERR_PTR(-ENXIO);
	अन्यथा अगर (atomic_पढ़ो(&sdp->detaching)) अणु
		/* If sdp->detaching, then the refcount may alपढ़ोy be 0, in
		 * which हाल it would be a bug to करो kref_get().
		 */
		sdp = ERR_PTR(-ENODEV);
	पूर्ण अन्यथा
		kref_get(&sdp->d_ref);
	पढ़ो_unlock_irqrestore(&sg_index_lock, flags);

	वापस sdp;
पूर्ण

#अगर_घोषित CONFIG_SCSI_PROC_FS
अटल पूर्णांक sg_proc_seq_show_पूर्णांक(काष्ठा seq_file *s, व्योम *v);

अटल पूर्णांक sg_proc_single_खोलो_adio(काष्ठा inode *inode, काष्ठा file *file);
अटल sमाप_प्रकार sg_proc_ग_लिखो_adio(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
			          माप_प्रकार count, loff_t *off);
अटल स्थिर काष्ठा proc_ops adio_proc_ops = अणु
	.proc_खोलो	= sg_proc_single_खोलो_adio,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= sg_proc_ग_लिखो_adio,
	.proc_release	= single_release,
पूर्ण;

अटल पूर्णांक sg_proc_single_खोलो_dressz(काष्ठा inode *inode, काष्ठा file *file);
अटल sमाप_प्रकार sg_proc_ग_लिखो_dressz(काष्ठा file *filp, 
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *off);
अटल स्थिर काष्ठा proc_ops dressz_proc_ops = अणु
	.proc_खोलो	= sg_proc_single_खोलो_dressz,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_ग_लिखो	= sg_proc_ग_लिखो_dressz,
	.proc_release	= single_release,
पूर्ण;

अटल पूर्णांक sg_proc_seq_show_version(काष्ठा seq_file *s, व्योम *v);
अटल पूर्णांक sg_proc_seq_show_devhdr(काष्ठा seq_file *s, व्योम *v);
अटल पूर्णांक sg_proc_seq_show_dev(काष्ठा seq_file *s, व्योम *v);
अटल व्योम * dev_seq_start(काष्ठा seq_file *s, loff_t *pos);
अटल व्योम * dev_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos);
अटल व्योम dev_seq_stop(काष्ठा seq_file *s, व्योम *v);
अटल स्थिर काष्ठा seq_operations dev_seq_ops = अणु
	.start = dev_seq_start,
	.next  = dev_seq_next,
	.stop  = dev_seq_stop,
	.show  = sg_proc_seq_show_dev,
पूर्ण;

अटल पूर्णांक sg_proc_seq_show_devstrs(काष्ठा seq_file *s, व्योम *v);
अटल स्थिर काष्ठा seq_operations devstrs_seq_ops = अणु
	.start = dev_seq_start,
	.next  = dev_seq_next,
	.stop  = dev_seq_stop,
	.show  = sg_proc_seq_show_devstrs,
पूर्ण;

अटल पूर्णांक sg_proc_seq_show_debug(काष्ठा seq_file *s, व्योम *v);
अटल स्थिर काष्ठा seq_operations debug_seq_ops = अणु
	.start = dev_seq_start,
	.next  = dev_seq_next,
	.stop  = dev_seq_stop,
	.show  = sg_proc_seq_show_debug,
पूर्ण;

अटल पूर्णांक
sg_proc_init(व्योम)
अणु
	काष्ठा proc_dir_entry *p;

	p = proc_सूची_गढ़ो("scsi/sg", शून्य);
	अगर (!p)
		वापस 1;

	proc_create("allow_dio", S_IRUGO | S_IWUSR, p, &adio_proc_ops);
	proc_create_seq("debug", S_IRUGO, p, &debug_seq_ops);
	proc_create("def_reserved_size", S_IRUGO | S_IWUSR, p, &dressz_proc_ops);
	proc_create_single("device_hdr", S_IRUGO, p, sg_proc_seq_show_devhdr);
	proc_create_seq("devices", S_IRUGO, p, &dev_seq_ops);
	proc_create_seq("device_strs", S_IRUGO, p, &devstrs_seq_ops);
	proc_create_single("version", S_IRUGO, p, sg_proc_seq_show_version);
	वापस 0;
पूर्ण


अटल पूर्णांक sg_proc_seq_show_पूर्णांक(काष्ठा seq_file *s, व्योम *v)
अणु
	seq_म_लिखो(s, "%d\n", *((पूर्णांक *)s->निजी));
	वापस 0;
पूर्ण

अटल पूर्णांक sg_proc_single_खोलो_adio(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, sg_proc_seq_show_पूर्णांक, &sg_allow_dio);
पूर्ण

अटल sमाप_प्रकार 
sg_proc_ग_लिखो_adio(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
		   माप_प्रकार count, loff_t *off)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ num;

	अगर (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
		वापस -EACCES;
	err = kम_से_अदीर्घ_from_user(buffer, count, 0, &num);
	अगर (err)
		वापस err;
	sg_allow_dio = num ? 1 : 0;
	वापस count;
पूर्ण

अटल पूर्णांक sg_proc_single_खोलो_dressz(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, sg_proc_seq_show_पूर्णांक, &sg_big_buff);
पूर्ण

अटल sमाप_प्रकार 
sg_proc_ग_लिखो_dressz(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
		     माप_प्रकार count, loff_t *off)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ k = अच_दीर्घ_उच्च;

	अगर (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
		वापस -EACCES;

	err = kम_से_अदीर्घ_from_user(buffer, count, 0, &k);
	अगर (err)
		वापस err;
	अगर (k <= 1048576) अणु	/* limit "big buff" to 1 MB */
		sg_big_buff = k;
		वापस count;
	पूर्ण
	वापस -दुस्फल;
पूर्ण

अटल पूर्णांक sg_proc_seq_show_version(काष्ठा seq_file *s, व्योम *v)
अणु
	seq_म_लिखो(s, "%d\t%s [%s]\n", sg_version_num, SG_VERSION_STR,
		   sg_version_date);
	वापस 0;
पूर्ण

अटल पूर्णांक sg_proc_seq_show_devhdr(काष्ठा seq_file *s, व्योम *v)
अणु
	seq_माला_दो(s, "host\tchan\tid\tlun\ttype\topens\tqdepth\tbusy\tonline\n");
	वापस 0;
पूर्ण

काष्ठा sg_proc_deviter अणु
	loff_t	index;
	माप_प्रकार	max;
पूर्ण;

अटल व्योम * dev_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा sg_proc_deviter * it = kदो_स्मृति(माप(*it), GFP_KERNEL);

	s->निजी = it;
	अगर (! it)
		वापस शून्य;

	it->index = *pos;
	it->max = sg_last_dev();
	अगर (it->index >= it->max)
		वापस शून्य;
	वापस it;
पूर्ण

अटल व्योम * dev_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा sg_proc_deviter * it = s->निजी;

	*pos = ++it->index;
	वापस (it->index < it->max) ? it : शून्य;
पूर्ण

अटल व्योम dev_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
	kमुक्त(s->निजी);
पूर्ण

अटल पूर्णांक sg_proc_seq_show_dev(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा sg_proc_deviter * it = (काष्ठा sg_proc_deviter *) v;
	Sg_device *sdp;
	काष्ठा scsi_device *scsidp;
	अचिन्हित दीर्घ अगरlags;

	पढ़ो_lock_irqsave(&sg_index_lock, अगरlags);
	sdp = it ? sg_lookup_dev(it->index) : शून्य;
	अगर ((शून्य == sdp) || (शून्य == sdp->device) ||
	    (atomic_पढ़ो(&sdp->detaching)))
		seq_माला_दो(s, "-1\t-1\t-1\t-1\t-1\t-1\t-1\t-1\t-1\n");
	अन्यथा अणु
		scsidp = sdp->device;
		seq_म_लिखो(s, "%d\t%d\t%d\t%llu\t%d\t%d\t%d\t%d\t%d\n",
			      scsidp->host->host_no, scsidp->channel,
			      scsidp->id, scsidp->lun, (पूर्णांक) scsidp->type,
			      1,
			      (पूर्णांक) scsidp->queue_depth,
			      (पूर्णांक) scsi_device_busy(scsidp),
			      (पूर्णांक) scsi_device_online(scsidp));
	पूर्ण
	पढ़ो_unlock_irqrestore(&sg_index_lock, अगरlags);
	वापस 0;
पूर्ण

अटल पूर्णांक sg_proc_seq_show_devstrs(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा sg_proc_deviter * it = (काष्ठा sg_proc_deviter *) v;
	Sg_device *sdp;
	काष्ठा scsi_device *scsidp;
	अचिन्हित दीर्घ अगरlags;

	पढ़ो_lock_irqsave(&sg_index_lock, अगरlags);
	sdp = it ? sg_lookup_dev(it->index) : शून्य;
	scsidp = sdp ? sdp->device : शून्य;
	अगर (sdp && scsidp && (!atomic_पढ़ो(&sdp->detaching)))
		seq_म_लिखो(s, "%8.8s\t%16.16s\t%4.4s\n",
			   scsidp->venकरोr, scsidp->model, scsidp->rev);
	अन्यथा
		seq_माला_दो(s, "<no active device>\n");
	पढ़ो_unlock_irqrestore(&sg_index_lock, अगरlags);
	वापस 0;
पूर्ण

/* must be called जबतक holding sg_index_lock */
अटल व्योम sg_proc_debug_helper(काष्ठा seq_file *s, Sg_device * sdp)
अणु
	पूर्णांक k, new_पूर्णांकerface, blen, usg;
	Sg_request *srp;
	Sg_fd *fp;
	स्थिर sg_io_hdr_t *hp;
	स्थिर अक्षर * cp;
	अचिन्हित पूर्णांक ms;

	k = 0;
	list_क्रम_each_entry(fp, &sdp->sfds, sfd_siblings) अणु
		k++;
		पढ़ो_lock(&fp->rq_list_lock); /* irqs alपढ़ोy disabled */
		seq_म_लिखो(s, "   FD(%d): timeout=%dms bufflen=%d "
			   "(res)sgat=%d low_dma=%d\n", k,
			   jअगरfies_to_msecs(fp->समयout),
			   fp->reserve.bufflen,
			   (पूर्णांक) fp->reserve.k_use_sg, 0);
		seq_म_लिखो(s, "   cmd_q=%d f_packid=%d k_orphan=%d closed=0\n",
			   (पूर्णांक) fp->cmd_q, (पूर्णांक) fp->क्रमce_packid,
			   (पूर्णांक) fp->keep_orphan);
		list_क्रम_each_entry(srp, &fp->rq_list, entry) अणु
			hp = &srp->header;
			new_पूर्णांकerface = (hp->पूर्णांकerface_id == '\0') ? 0 : 1;
			अगर (srp->res_used) अणु
				अगर (new_पूर्णांकerface &&
				    (SG_FLAG_MMAP_IO & hp->flags))
					cp = "     mmap>> ";
				अन्यथा
					cp = "     rb>> ";
			पूर्ण अन्यथा अणु
				अगर (SG_INFO_सूचीECT_IO_MASK & hp->info)
					cp = "     dio>> ";
				अन्यथा
					cp = "     ";
			पूर्ण
			seq_माला_दो(s, cp);
			blen = srp->data.bufflen;
			usg = srp->data.k_use_sg;
			seq_माला_दो(s, srp->करोne ?
				 ((1 == srp->करोne) ?  "rcv:" : "fin:")
				  : "act:");
			seq_म_लिखो(s, " id=%d blen=%d",
				   srp->header.pack_id, blen);
			अगर (srp->करोne)
				seq_म_लिखो(s, " dur=%d", hp->duration);
			अन्यथा अणु
				ms = jअगरfies_to_msecs(jअगरfies);
				seq_म_लिखो(s, " t_o/elap=%d/%d",
					(new_पूर्णांकerface ? hp->समयout :
						  jअगरfies_to_msecs(fp->समयout)),
					(ms > hp->duration ? ms - hp->duration : 0));
			पूर्ण
			seq_म_लिखो(s, "ms sgat=%d op=0x%02x\n", usg,
				   (पूर्णांक) srp->data.cmd_opcode);
		पूर्ण
		अगर (list_empty(&fp->rq_list))
			seq_माला_दो(s, "     No requests active\n");
		पढ़ो_unlock(&fp->rq_list_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक sg_proc_seq_show_debug(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा sg_proc_deviter * it = (काष्ठा sg_proc_deviter *) v;
	Sg_device *sdp;
	अचिन्हित दीर्घ अगरlags;

	अगर (it && (0 == it->index))
		seq_म_लिखो(s, "max_active_device=%d  def_reserved_size=%d\n",
			   (पूर्णांक)it->max, sg_big_buff);

	पढ़ो_lock_irqsave(&sg_index_lock, अगरlags);
	sdp = it ? sg_lookup_dev(it->index) : शून्य;
	अगर (शून्य == sdp)
		जाओ skip;
	पढ़ो_lock(&sdp->sfd_lock);
	अगर (!list_empty(&sdp->sfds)) अणु
		seq_म_लिखो(s, " >>> device=%s ", sdp->disk->disk_name);
		अगर (atomic_पढ़ो(&sdp->detaching))
			seq_माला_दो(s, "detaching pending close ");
		अन्यथा अगर (sdp->device) अणु
			काष्ठा scsi_device *scsidp = sdp->device;

			seq_म_लिखो(s, "%d:%d:%d:%llu   em=%d",
				   scsidp->host->host_no,
				   scsidp->channel, scsidp->id,
				   scsidp->lun,
				   scsidp->host->hostt->emulated);
		पूर्ण
		seq_म_लिखो(s, " sg_tablesize=%d excl=%d open_cnt=%d\n",
			   sdp->sg_tablesize, sdp->exclude, sdp->खोलो_cnt);
		sg_proc_debug_helper(s, sdp);
	पूर्ण
	पढ़ो_unlock(&sdp->sfd_lock);
skip:
	पढ़ो_unlock_irqrestore(&sg_index_lock, अगरlags);
	वापस 0;
पूर्ण

#पूर्ण_अगर				/* CONFIG_SCSI_PROC_FS */

module_init(init_sg);
module_निकास(निकास_sg);
