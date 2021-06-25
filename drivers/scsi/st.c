<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
   SCSI Tape Driver क्रम Linux version 1.1 and newer. See the accompanying
   file Documentation/scsi/st.rst क्रम more inक्रमmation.

   History:
   Rewritten from Dwayne Forsyth's SCSI tape driver by Kai Makisara.
   Contribution and ideas from several people including (in alphabetical
   order) Klaus Ehrenfried, Eugene Exarevsky, Eric Lee Green, Wolfgang Denk,
   Steve Hirsch, Andreas Koppenh"ofer, Michael Leoकरोlter, Eyal Lebedinsky,
   Michael Schaefer, J"org Weule, and Eric Youngdale.

   Copyright 1992 - 2016 Kai Makisara
   email Kai.Makisara@kolumbus.fi

   Some small क्रमmal changes - aeb, 950809

   Last modअगरied: 18-JAN-1998 Riअक्षरd Gooch <rgooch@atnf.csiro.au> Devfs support
 */

अटल स्थिर अक्षर *verstr = "20160209";

#समावेश <linux/module.h>

#समावेश <linux/compat.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mtपन.स>
#समावेश <linux/cdrom.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/cdev.h>
#समावेश <linux/idr.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_ioctl.h>
#समावेश <scsi/sg.h>


/* The driver prपूर्णांकs some debugging inक्रमmation on the console अगर DEBUG
   is defined and non-zero. */
#घोषणा DEBUG 1
#घोषणा NO_DEBUG 0

#घोषणा ST_DEB_MSG  KERN_NOTICE
#अगर DEBUG
/* The message level क्रम the debug messages is currently set to KERN_NOTICE
   so that people can easily see the messages. Later when the debugging messages
   in the drivers are more widely classअगरied, this may be changed to KERN_DEBUG. */
#घोषणा DEB(a) a
#घोषणा DEBC(a) अगर (debugging) अणु a ; पूर्ण
#अन्यथा
#घोषणा DEB(a)
#घोषणा DEBC(a)
#पूर्ण_अगर

#घोषणा ST_KILOBYTE 1024

#समावेश "st_options.h"
#समावेश "st.h"

अटल पूर्णांक buffer_kbs;
अटल पूर्णांक max_sg_segs;
अटल पूर्णांक try_direct_io = TRY_सूचीECT_IO;
अटल पूर्णांक try_rdio = 1;
अटल पूर्णांक try_wdio = 1;
अटल पूर्णांक debug_flag;

अटल काष्ठा class st_sysfs_class;
अटल स्थिर काष्ठा attribute_group *st_dev_groups[];
अटल स्थिर काष्ठा attribute_group *st_drv_groups[];

MODULE_AUTHOR("Kai Makisara");
MODULE_DESCRIPTION("SCSI tape (st) driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CHARDEV_MAJOR(SCSI_TAPE_MAJOR);
MODULE_ALIAS_SCSI_DEVICE(TYPE_TAPE);

/* Set 'perm' (4th argument) to 0 to disable module_param's definition
 * of sysfs parameters (which module_param करोesn't yet support).
 * Sysfs parameters defined explicitly later.
 */
module_param_named(buffer_kbs, buffer_kbs, पूर्णांक, 0);
MODULE_PARM_DESC(buffer_kbs, "Default driver buffer size for fixed block mode (KB; 32)");
module_param_named(max_sg_segs, max_sg_segs, पूर्णांक, 0);
MODULE_PARM_DESC(max_sg_segs, "Maximum number of scatter/gather segments to use (256)");
module_param_named(try_direct_io, try_direct_io, पूर्णांक, 0);
MODULE_PARM_DESC(try_direct_io, "Try direct I/O between user buffer and tape drive (1)");
module_param_named(debug_flag, debug_flag, पूर्णांक, 0);
MODULE_PARM_DESC(debug_flag, "Enable DEBUG, same as setting debugging=1");


/* Extra parameters क्रम testing */
module_param_named(try_rdio, try_rdio, पूर्णांक, 0);
MODULE_PARM_DESC(try_rdio, "Try direct read i/o when possible");
module_param_named(try_wdio, try_wdio, पूर्णांक, 0);
MODULE_PARM_DESC(try_wdio, "Try direct write i/o when possible");

#अगर_अघोषित MODULE
अटल पूर्णांक ग_लिखो_threshold_kbs;  /* retained क्रम compatibility */
अटल काष्ठा st_dev_parm अणु
	अक्षर *name;
	पूर्णांक *val;
पूर्ण parms[] __initdata = अणु
	अणु
		"buffer_kbs", &buffer_kbs
	पूर्ण,
	अणु       /* Retained क्रम compatibility with 2.4 */
		"write_threshold_kbs", &ग_लिखो_threshold_kbs
	पूर्ण,
	अणु
		"max_sg_segs", शून्य
	पूर्ण,
	अणु
		"try_direct_io", &try_direct_io
	पूर्ण,
	अणु
		"debug_flag", &debug_flag
	पूर्ण
पूर्ण;
#पूर्ण_अगर

/* Restrict the number of modes so that names क्रम all are asचिन्हित */
#अगर ST_NBR_MODES > 16
#त्रुटि "Maximum number of modes is 16"
#पूर्ण_अगर
/* Bit reversed order to get same names क्रम same minors with all
   mode counts */
अटल स्थिर अक्षर *st_क्रमmats[] = अणु
	"",  "r", "k", "s", "l", "t", "o", "u",
	"m", "v", "p", "x", "a", "y", "q", "z"पूर्ण; 

/* The शेष definitions have been moved to st_options.h */

#घोषणा ST_FIXED_BUFFER_SIZE (ST_FIXED_BUFFER_BLOCKS * ST_KILOBYTE)

/* The buffer size should fit पूर्णांकo the 24 bits क्रम length in the
   6-byte SCSI पढ़ो and ग_लिखो commands. */
#अगर ST_FIXED_BUFFER_SIZE >= (2 << 24 - 1)
#त्रुटि "Buffer size should not exceed (2 << 24 - 1) bytes!"
#पूर्ण_अगर

अटल पूर्णांक debugging = DEBUG;

#घोषणा MAX_RETRIES 0
#घोषणा MAX_WRITE_RETRIES 0
#घोषणा MAX_READY_RETRIES 0
#घोषणा NO_TAPE  NOT_READY

#घोषणा ST_TIMEOUT (900 * HZ)
#घोषणा ST_LONG_TIMEOUT (14000 * HZ)

/* Remove mode bits and स्वतः-शुरुआत bit (7) */
#घोषणा TAPE_NR(x) ( ((iminor(x) & ~255) >> (ST_NBR_MODE_BITS + 1)) | \
	(iminor(x) & ((1 << ST_MODE_SHIFT)-1)))
#घोषणा TAPE_MODE(x) ((iminor(x) & ST_MODE_MASK) >> ST_MODE_SHIFT)

/* Conकाष्ठा the minor number from the device (d), mode (m), and non-शुरुआत (n) data */
#घोषणा TAPE_MINOR(d, m, n) (((d & ~(255 >> (ST_NBR_MODE_BITS + 1))) << (ST_NBR_MODE_BITS + 1)) | \
  (d & (255 >> (ST_NBR_MODE_BITS + 1))) | (m << ST_MODE_SHIFT) | ((n != 0) << 7) )

/* Internal ioctl to set both density (uppermost 8 bits) and blocksize (lower
   24 bits) */
#घोषणा SET_DENS_AND_BLK 0x10001

अटल पूर्णांक st_fixed_buffer_size = ST_FIXED_BUFFER_SIZE;
अटल पूर्णांक st_max_sg_segs = ST_MAX_SG;

अटल पूर्णांक modes_defined;

अटल पूर्णांक enlarge_buffer(काष्ठा st_buffer *, पूर्णांक);
अटल व्योम clear_buffer(काष्ठा st_buffer *);
अटल व्योम normalize_buffer(काष्ठा st_buffer *);
अटल पूर्णांक append_to_buffer(स्थिर अक्षर __user *, काष्ठा st_buffer *, पूर्णांक);
अटल पूर्णांक from_buffer(काष्ठा st_buffer *, अक्षर __user *, पूर्णांक);
अटल व्योम move_buffer_data(काष्ठा st_buffer *, पूर्णांक);

अटल पूर्णांक sgl_map_user_pages(काष्ठा st_buffer *, स्थिर अचिन्हित पूर्णांक,
			      अचिन्हित दीर्घ, माप_प्रकार, पूर्णांक);
अटल पूर्णांक sgl_unmap_user_pages(काष्ठा st_buffer *, स्थिर अचिन्हित पूर्णांक, पूर्णांक);

अटल पूर्णांक st_probe(काष्ठा device *);
अटल पूर्णांक st_हटाओ(काष्ठा device *);

अटल काष्ठा scsi_driver st_ढाँचा = अणु
	.gendrv = अणु
		.name		= "st",
		.owner		= THIS_MODULE,
		.probe		= st_probe,
		.हटाओ		= st_हटाओ,
		.groups		= st_drv_groups,
	पूर्ण,
पूर्ण;

अटल पूर्णांक st_compression(काष्ठा scsi_tape *, पूर्णांक);

अटल पूर्णांक find_partition(काष्ठा scsi_tape *);
अटल पूर्णांक चयन_partition(काष्ठा scsi_tape *);

अटल पूर्णांक st_पूर्णांक_ioctl(काष्ठा scsi_tape *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);

अटल व्योम scsi_tape_release(काष्ठा kref *);

#घोषणा to_scsi_tape(obj) container_of(obj, काष्ठा scsi_tape, kref)

अटल DEFINE_MUTEX(st_ref_mutex);
अटल DEFINE_SPINLOCK(st_index_lock);
अटल DEFINE_SPINLOCK(st_use_lock);
अटल DEFINE_IDR(st_index_idr);



#अगर_अघोषित SIGS_FROM_OSST
#घोषणा SIGS_FROM_OSST \
	अणु"OnStream", "SC-", "", "osst"पूर्ण, \
	अणु"OnStream", "DI-", "", "osst"पूर्ण, \
	अणु"OnStream", "DP-", "", "osst"पूर्ण, \
	अणु"OnStream", "USB", "", "osst"पूर्ण, \
	अणु"OnStream", "FW-", "", "osst"पूर्ण
#पूर्ण_अगर

अटल काष्ठा scsi_tape *scsi_tape_get(पूर्णांक dev)
अणु
	काष्ठा scsi_tape *STp = शून्य;

	mutex_lock(&st_ref_mutex);
	spin_lock(&st_index_lock);

	STp = idr_find(&st_index_idr, dev);
	अगर (!STp) जाओ out;

	kref_get(&STp->kref);

	अगर (!STp->device)
		जाओ out_put;

	अगर (scsi_device_get(STp->device))
		जाओ out_put;

	जाओ out;

out_put:
	kref_put(&STp->kref, scsi_tape_release);
	STp = शून्य;
out:
	spin_unlock(&st_index_lock);
	mutex_unlock(&st_ref_mutex);
	वापस STp;
पूर्ण

अटल व्योम scsi_tape_put(काष्ठा scsi_tape *STp)
अणु
	काष्ठा scsi_device *sdev = STp->device;

	mutex_lock(&st_ref_mutex);
	kref_put(&STp->kref, scsi_tape_release);
	scsi_device_put(sdev);
	mutex_unlock(&st_ref_mutex);
पूर्ण

काष्ठा st_reject_data अणु
	अक्षर *venकरोr;
	अक्षर *model;
	अक्षर *rev;
	अक्षर *driver_hपूर्णांक; /* Name of the correct driver, शून्य अगर unknown */
पूर्ण;

अटल काष्ठा st_reject_data reject_list[] = अणु
	/* अणु"XXX", "Yy-", "", शून्यपूर्ण,  example */
	SIGS_FROM_OSST,
	अणुशून्य, पूर्णपूर्ण;

/* If the device signature is on the list of incompatible drives, the
   function वापसs a poपूर्णांकer to the name of the correct driver (अगर known) */
अटल अक्षर * st_incompatible(काष्ठा scsi_device* SDp)
अणु
	काष्ठा st_reject_data *rp;

	क्रम (rp=&(reject_list[0]); rp->venकरोr != शून्य; rp++)
		अगर (!म_भेदन(rp->venकरोr, SDp->venकरोr, म_माप(rp->venकरोr)) &&
		    !म_भेदन(rp->model, SDp->model, म_माप(rp->model)) &&
		    !म_भेदन(rp->rev, SDp->rev, म_माप(rp->rev))) अणु
			अगर (rp->driver_hपूर्णांक)
				वापस rp->driver_hपूर्णांक;
			अन्यथा
				वापस "unknown";
		पूर्ण
	वापस शून्य;
पूर्ण


अटल अंतरभूत अक्षर *tape_name(काष्ठा scsi_tape *tape)
अणु
	वापस tape->disk->disk_name;
पूर्ण

#घोषणा st_prपूर्णांकk(prefix, t, fmt, a...) \
	sdev_prefix_prपूर्णांकk(prefix, (t)->device, tape_name(t), fmt, ##a)
#अगर_घोषित DEBUG
#घोषणा DEBC_prपूर्णांकk(t, fmt, a...) \
	अगर (debugging) अणु st_prपूर्णांकk(ST_DEB_MSG, t, fmt, ##a ); पूर्ण
#अन्यथा
#घोषणा DEBC_prपूर्णांकk(t, fmt, a...)
#पूर्ण_अगर

अटल व्योम st_analyze_sense(काष्ठा st_request *SRpnt, काष्ठा st_cmdstatus *s)
अणु
	स्थिर u8 *ucp;
	स्थिर u8 *sense = SRpnt->sense;

	s->have_sense = scsi_normalize_sense(SRpnt->sense,
				SCSI_SENSE_BUFFERSIZE, &s->sense_hdr);
	s->flags = 0;

	अगर (s->have_sense) अणु
		s->deferred = 0;
		s->reमुख्यder_valid =
			scsi_get_sense_info_fld(sense, SCSI_SENSE_BUFFERSIZE, &s->ureमुख्यder64);
		चयन (sense[0] & 0x7f) अणु
		हाल 0x71:
			s->deferred = 1;
			fallthrough;
		हाल 0x70:
			s->fixed_क्रमmat = 1;
			s->flags = sense[2] & 0xe0;
			अवरोध;
		हाल 0x73:
			s->deferred = 1;
			fallthrough;
		हाल 0x72:
			s->fixed_क्रमmat = 0;
			ucp = scsi_sense_desc_find(sense, SCSI_SENSE_BUFFERSIZE, 4);
			s->flags = ucp ? (ucp[3] & 0xe0) : 0;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण


/* Convert the result to success code */
अटल पूर्णांक st_chk_result(काष्ठा scsi_tape *STp, काष्ठा st_request * SRpnt)
अणु
	पूर्णांक result = SRpnt->result;
	u8 scode;
	DEB(स्थिर अक्षर *stp;)
	अक्षर *name = tape_name(STp);
	काष्ठा st_cmdstatus *cmdstatp;

	अगर (!result)
		वापस 0;

	cmdstatp = &STp->buffer->cmdstat;
	st_analyze_sense(SRpnt, cmdstatp);

	अगर (cmdstatp->have_sense)
		scode = STp->buffer->cmdstat.sense_hdr.sense_key;
	अन्यथा
		scode = 0;

	DEB(
	अगर (debugging) अणु
		st_prपूर्णांकk(ST_DEB_MSG, STp,
			    "Error: %x, cmd: %x %x %x %x %x %x\n", result,
			    SRpnt->cmd[0], SRpnt->cmd[1], SRpnt->cmd[2],
			    SRpnt->cmd[3], SRpnt->cmd[4], SRpnt->cmd[5]);
		अगर (cmdstatp->have_sense)
			__scsi_prपूर्णांक_sense(STp->device, name,
					   SRpnt->sense, SCSI_SENSE_BUFFERSIZE);
	पूर्ण ) /* end DEB */
	अगर (!debugging) अणु /* Abnormal conditions क्रम tape */
		अगर (!cmdstatp->have_sense)
			st_prपूर्णांकk(KERN_WARNING, STp,
			       "Error %x (driver bt 0x%x, host bt 0x%x).\n",
			       result, driver_byte(result), host_byte(result));
		अन्यथा अगर (cmdstatp->have_sense &&
			 scode != NO_SENSE &&
			 scode != RECOVERED_ERROR &&
			 /* scode != UNIT_ATTENTION && */
			 scode != BLANK_CHECK &&
			 scode != VOLUME_OVERFLOW &&
			 SRpnt->cmd[0] != MODE_SENSE &&
			 SRpnt->cmd[0] != TEST_UNIT_READY) अणु

			__scsi_prपूर्णांक_sense(STp->device, name,
					   SRpnt->sense, SCSI_SENSE_BUFFERSIZE);
		पूर्ण
	पूर्ण

	अगर (cmdstatp->fixed_क्रमmat &&
	    STp->cln_mode >= EXTENDED_SENSE_START) अणु  /* Only fixed क्रमmat sense */
		अगर (STp->cln_sense_value)
			STp->cleaning_req |= ((SRpnt->sense[STp->cln_mode] &
					       STp->cln_sense_mask) == STp->cln_sense_value);
		अन्यथा
			STp->cleaning_req |= ((SRpnt->sense[STp->cln_mode] &
					       STp->cln_sense_mask) != 0);
	पूर्ण
	अगर (cmdstatp->have_sense &&
	    cmdstatp->sense_hdr.asc == 0 && cmdstatp->sense_hdr.ascq == 0x17)
		STp->cleaning_req = 1; /* ASC and ASCQ => cleaning requested */

	STp->pos_unknown |= STp->device->was_reset;

	अगर (cmdstatp->have_sense &&
	    scode == RECOVERED_ERROR
#अगर ST_RECOVERED_WRITE_FATAL
	    && SRpnt->cmd[0] != WRITE_6
	    && SRpnt->cmd[0] != WRITE_खाताMARKS
#पूर्ण_अगर
	    ) अणु
		STp->recover_count++;
		STp->recover_reg++;

		DEB(
		अगर (debugging) अणु
			अगर (SRpnt->cmd[0] == READ_6)
				stp = "read";
			अन्यथा अगर (SRpnt->cmd[0] == WRITE_6)
				stp = "write";
			अन्यथा
				stp = "ioctl";
			st_prपूर्णांकk(ST_DEB_MSG, STp,
				  "Recovered %s error (%d).\n",
				  stp, STp->recover_count);
		पूर्ण ) /* end DEB */

		अगर (cmdstatp->flags == 0)
			वापस 0;
	पूर्ण
	वापस (-EIO);
पूर्ण

अटल काष्ठा st_request *st_allocate_request(काष्ठा scsi_tape *stp)
अणु
	काष्ठा st_request *streq;

	streq = kzalloc(माप(*streq), GFP_KERNEL);
	अगर (streq)
		streq->stp = stp;
	अन्यथा अणु
		st_prपूर्णांकk(KERN_ERR, stp,
			  "Can't get SCSI request.\n");
		अगर (संकेत_pending(current))
			stp->buffer->syscall_result = -EINTR;
		अन्यथा
			stp->buffer->syscall_result = -EBUSY;
	पूर्ण

	वापस streq;
पूर्ण

अटल व्योम st_release_request(काष्ठा st_request *streq)
अणु
	kमुक्त(streq);
पूर्ण

अटल व्योम st_करो_stats(काष्ठा scsi_tape *STp, काष्ठा request *req)
अणु
	kसमय_प्रकार now;

	now = kसमय_get();
	अगर (scsi_req(req)->cmd[0] == WRITE_6) अणु
		now = kसमय_sub(now, STp->stats->ग_लिखो_समय);
		atomic64_add(kसमय_प्रकारo_ns(now), &STp->stats->tot_ग_लिखो_समय);
		atomic64_add(kसमय_प्रकारo_ns(now), &STp->stats->tot_io_समय);
		atomic64_inc(&STp->stats->ग_लिखो_cnt);
		अगर (scsi_req(req)->result) अणु
			atomic64_add(atomic_पढ़ो(&STp->stats->last_ग_लिखो_size)
				- STp->buffer->cmdstat.residual,
				&STp->stats->ग_लिखो_byte_cnt);
			अगर (STp->buffer->cmdstat.residual > 0)
				atomic64_inc(&STp->stats->resid_cnt);
		पूर्ण अन्यथा
			atomic64_add(atomic_पढ़ो(&STp->stats->last_ग_लिखो_size),
				&STp->stats->ग_लिखो_byte_cnt);
	पूर्ण अन्यथा अगर (scsi_req(req)->cmd[0] == READ_6) अणु
		now = kसमय_sub(now, STp->stats->पढ़ो_समय);
		atomic64_add(kसमय_प्रकारo_ns(now), &STp->stats->tot_पढ़ो_समय);
		atomic64_add(kसमय_प्रकारo_ns(now), &STp->stats->tot_io_समय);
		atomic64_inc(&STp->stats->पढ़ो_cnt);
		अगर (scsi_req(req)->result) अणु
			atomic64_add(atomic_पढ़ो(&STp->stats->last_पढ़ो_size)
				- STp->buffer->cmdstat.residual,
				&STp->stats->पढ़ो_byte_cnt);
			अगर (STp->buffer->cmdstat.residual > 0)
				atomic64_inc(&STp->stats->resid_cnt);
		पूर्ण अन्यथा
			atomic64_add(atomic_पढ़ो(&STp->stats->last_पढ़ो_size),
				&STp->stats->पढ़ो_byte_cnt);
	पूर्ण अन्यथा अणु
		now = kसमय_sub(now, STp->stats->other_समय);
		atomic64_add(kसमय_प्रकारo_ns(now), &STp->stats->tot_io_समय);
		atomic64_inc(&STp->stats->other_cnt);
	पूर्ण
	atomic64_dec(&STp->stats->in_flight);
पूर्ण

अटल व्योम st_scsi_execute_end(काष्ठा request *req, blk_status_t status)
अणु
	काष्ठा st_request *SRpnt = req->end_io_data;
	काष्ठा scsi_request *rq = scsi_req(req);
	काष्ठा scsi_tape *STp = SRpnt->stp;
	काष्ठा bio *पंचांगp;

	STp->buffer->cmdstat.midlevel_result = SRpnt->result = rq->result;
	STp->buffer->cmdstat.residual = rq->resid_len;

	st_करो_stats(STp, req);

	पंचांगp = SRpnt->bio;
	अगर (rq->sense_len)
		स_नकल(SRpnt->sense, rq->sense, SCSI_SENSE_BUFFERSIZE);
	अगर (SRpnt->रुकोing)
		complete(SRpnt->रुकोing);

	blk_rq_unmap_user(पंचांगp);
	blk_put_request(req);
पूर्ण

अटल पूर्णांक st_scsi_execute(काष्ठा st_request *SRpnt, स्थिर अचिन्हित अक्षर *cmd,
			   पूर्णांक data_direction, व्योम *buffer, अचिन्हित bufflen,
			   पूर्णांक समयout, पूर्णांक retries)
अणु
	काष्ठा request *req;
	काष्ठा scsi_request *rq;
	काष्ठा rq_map_data *mdata = &SRpnt->stp->buffer->map_data;
	पूर्णांक err = 0;
	काष्ठा scsi_tape *STp = SRpnt->stp;

	req = blk_get_request(SRpnt->stp->device->request_queue,
			data_direction == DMA_TO_DEVICE ?
			REQ_OP_SCSI_OUT : REQ_OP_SCSI_IN, 0);
	अगर (IS_ERR(req))
		वापस DRIVER_ERROR << 24;
	rq = scsi_req(req);
	req->rq_flags |= RQF_QUIET;

	mdata->null_mapped = 1;

	अगर (bufflen) अणु
		err = blk_rq_map_user(req->q, req, mdata, शून्य, bufflen,
				      GFP_KERNEL);
		अगर (err) अणु
			blk_put_request(req);
			वापस DRIVER_ERROR << 24;
		पूर्ण
	पूर्ण

	atomic64_inc(&STp->stats->in_flight);
	अगर (cmd[0] == WRITE_6) अणु
		atomic_set(&STp->stats->last_ग_लिखो_size, bufflen);
		STp->stats->ग_लिखो_समय = kसमय_get();
	पूर्ण अन्यथा अगर (cmd[0] == READ_6) अणु
		atomic_set(&STp->stats->last_पढ़ो_size, bufflen);
		STp->stats->पढ़ो_समय = kसमय_get();
	पूर्ण अन्यथा अणु
		STp->stats->other_समय = kसमय_get();
	पूर्ण

	SRpnt->bio = req->bio;
	rq->cmd_len = COMMAND_SIZE(cmd[0]);
	स_रखो(rq->cmd, 0, BLK_MAX_CDB);
	स_नकल(rq->cmd, cmd, rq->cmd_len);
	req->समयout = समयout;
	rq->retries = retries;
	req->end_io_data = SRpnt;

	blk_execute_rq_noरुको(शून्य, req, 1, st_scsi_execute_end);
	वापस 0;
पूर्ण

/* Do the scsi command. Waits until command perक्रमmed अगर करो_रुको is true.
   Otherwise ग_लिखो_behind_check() is used to check that the command
   has finished. */
अटल काष्ठा st_request *
st_करो_scsi(काष्ठा st_request * SRpnt, काष्ठा scsi_tape * STp, अचिन्हित अक्षर *cmd,
	   पूर्णांक bytes, पूर्णांक direction, पूर्णांक समयout, पूर्णांक retries, पूर्णांक करो_रुको)
अणु
	काष्ठा completion *रुकोing;
	काष्ठा rq_map_data *mdata = &STp->buffer->map_data;
	पूर्णांक ret;

	/* अगर async, make sure there's no command outstanding */
	अगर (!करो_रुको && ((STp->buffer)->last_SRpnt)) अणु
		st_prपूर्णांकk(KERN_ERR, STp,
			  "Async command already active.\n");
		अगर (संकेत_pending(current))
			(STp->buffer)->syscall_result = (-EINTR);
		अन्यथा
			(STp->buffer)->syscall_result = (-EBUSY);
		वापस शून्य;
	पूर्ण

	अगर (!SRpnt) अणु
		SRpnt = st_allocate_request(STp);
		अगर (!SRpnt)
			वापस शून्य;
	पूर्ण

	/* If async IO, set last_SRpnt. This ptr tells ग_लिखो_behind_check
	   which IO is outstanding. It's nulled out when the IO completes. */
	अगर (!करो_रुको)
		(STp->buffer)->last_SRpnt = SRpnt;

	रुकोing = &STp->रुको;
	init_completion(रुकोing);
	SRpnt->रुकोing = रुकोing;

	अगर (STp->buffer->करो_dio) अणु
		mdata->page_order = 0;
		mdata->nr_entries = STp->buffer->sg_segs;
		mdata->pages = STp->buffer->mapped_pages;
	पूर्ण अन्यथा अणु
		mdata->page_order = STp->buffer->reserved_page_order;
		mdata->nr_entries =
			DIV_ROUND_UP(bytes, PAGE_SIZE << mdata->page_order);
		mdata->pages = STp->buffer->reserved_pages;
		mdata->offset = 0;
	पूर्ण

	स_नकल(SRpnt->cmd, cmd, माप(SRpnt->cmd));
	STp->buffer->cmdस्थिति.सave_sense = 0;
	STp->buffer->syscall_result = 0;

	ret = st_scsi_execute(SRpnt, cmd, direction, शून्य, bytes, समयout,
			      retries);
	अगर (ret) अणु
		/* could not allocate the buffer or request was too large */
		(STp->buffer)->syscall_result = (-EBUSY);
		(STp->buffer)->last_SRpnt = शून्य;
	पूर्ण अन्यथा अगर (करो_रुको) अणु
		रुको_क्रम_completion(रुकोing);
		SRpnt->रुकोing = शून्य;
		(STp->buffer)->syscall_result = st_chk_result(STp, SRpnt);
	पूर्ण

	वापस SRpnt;
पूर्ण


/* Handle the ग_लिखो-behind checking (रुकोs क्रम completion). Returns -ENOSPC अगर
   ग_लिखो has been correct but EOM early warning reached, -EIO अगर ग_लिखो ended in
   error or zero अगर ग_लिखो successful. Asynchronous ग_लिखोs are used only in
   variable block mode. */
अटल पूर्णांक ग_लिखो_behind_check(काष्ठा scsi_tape * STp)
अणु
	पूर्णांक retval = 0;
	काष्ठा st_buffer *STbuffer;
	काष्ठा st_partstat *STps;
	काष्ठा st_cmdstatus *cmdstatp;
	काष्ठा st_request *SRpnt;

	STbuffer = STp->buffer;
	अगर (!STbuffer->writing)
		वापस 0;

	DEB(
	अगर (STp->ग_लिखो_pending)
		STp->nbr_रुकोs++;
	अन्यथा
		STp->nbr_finished++;
	) /* end DEB */

	रुको_क्रम_completion(&(STp->रुको));
	SRpnt = STbuffer->last_SRpnt;
	STbuffer->last_SRpnt = शून्य;
	SRpnt->रुकोing = शून्य;

	(STp->buffer)->syscall_result = st_chk_result(STp, SRpnt);
	st_release_request(SRpnt);

	STbuffer->buffer_bytes -= STbuffer->writing;
	STps = &(STp->ps[STp->partition]);
	अगर (STps->drv_block >= 0) अणु
		अगर (STp->block_size == 0)
			STps->drv_block++;
		अन्यथा
			STps->drv_block += STbuffer->writing / STp->block_size;
	पूर्ण

	cmdstatp = &STbuffer->cmdstat;
	अगर (STbuffer->syscall_result) अणु
		retval = -EIO;
		अगर (cmdstatp->have_sense && !cmdstatp->deferred &&
		    (cmdstatp->flags & SENSE_EOM) &&
		    (cmdstatp->sense_hdr.sense_key == NO_SENSE ||
		     cmdstatp->sense_hdr.sense_key == RECOVERED_ERROR)) अणु
			/* EOM at ग_लिखो-behind, has all data been written? */
			अगर (!cmdstatp->reमुख्यder_valid ||
			    cmdstatp->ureमुख्यder64 == 0)
				retval = -ENOSPC;
		पूर्ण
		अगर (retval == -EIO)
			STps->drv_block = -1;
	पूर्ण
	STbuffer->writing = 0;

	DEB(अगर (debugging && retval)
		    st_prपूर्णांकk(ST_DEB_MSG, STp,
				"Async write error %x, return value %d.\n",
				STbuffer->cmdstat.midlevel_result, retval);) /* end DEB */

	वापस retval;
पूर्ण


/* Step over खातापूर्ण अगर it has been inadvertently crossed (ioctl not used because
   it messes up the block number). */
अटल पूर्णांक cross_eof(काष्ठा scsi_tape * STp, पूर्णांक क्रमward)
अणु
	काष्ठा st_request *SRpnt;
	अचिन्हित अक्षर cmd[MAX_COMMAND_SIZE];

	cmd[0] = SPACE;
	cmd[1] = 0x01;		/* Space FileMarks */
	अगर (क्रमward) अणु
		cmd[2] = cmd[3] = 0;
		cmd[4] = 1;
	पूर्ण अन्यथा
		cmd[2] = cmd[3] = cmd[4] = 0xff;	/* -1 filemarks */
	cmd[5] = 0;

	DEBC_prपूर्णांकk(STp, "Stepping over filemark %s.\n",
		    क्रमward ? "forward" : "backward");

	SRpnt = st_करो_scsi(शून्य, STp, cmd, 0, DMA_NONE,
			   STp->device->request_queue->rq_समयout,
			   MAX_RETRIES, 1);
	अगर (!SRpnt)
		वापस (STp->buffer)->syscall_result;

	st_release_request(SRpnt);
	SRpnt = शून्य;

	अगर ((STp->buffer)->cmdstat.midlevel_result != 0)
		st_prपूर्णांकk(KERN_ERR, STp,
			  "Stepping over filemark %s failed.\n",
			  क्रमward ? "forward" : "backward");

	वापस (STp->buffer)->syscall_result;
पूर्ण


/* Flush the ग_लिखो buffer (never need to ग_लिखो अगर variable blocksize). */
अटल पूर्णांक st_flush_ग_लिखो_buffer(काष्ठा scsi_tape * STp)
अणु
	पूर्णांक transfer, blks;
	पूर्णांक result;
	अचिन्हित अक्षर cmd[MAX_COMMAND_SIZE];
	काष्ठा st_request *SRpnt;
	काष्ठा st_partstat *STps;

	result = ग_लिखो_behind_check(STp);
	अगर (result)
		वापस result;

	result = 0;
	अगर (STp->dirty == 1) अणु

		transfer = STp->buffer->buffer_bytes;
		DEBC_prपूर्णांकk(STp, "Flushing %d bytes.\n", transfer);

		स_रखो(cmd, 0, MAX_COMMAND_SIZE);
		cmd[0] = WRITE_6;
		cmd[1] = 1;
		blks = transfer / STp->block_size;
		cmd[2] = blks >> 16;
		cmd[3] = blks >> 8;
		cmd[4] = blks;

		SRpnt = st_करो_scsi(शून्य, STp, cmd, transfer, DMA_TO_DEVICE,
				   STp->device->request_queue->rq_समयout,
				   MAX_WRITE_RETRIES, 1);
		अगर (!SRpnt)
			वापस (STp->buffer)->syscall_result;

		STps = &(STp->ps[STp->partition]);
		अगर ((STp->buffer)->syscall_result != 0) अणु
			काष्ठा st_cmdstatus *cmdstatp = &STp->buffer->cmdstat;

			अगर (cmdstatp->have_sense && !cmdstatp->deferred &&
			    (cmdstatp->flags & SENSE_EOM) &&
			    (cmdstatp->sense_hdr.sense_key == NO_SENSE ||
			     cmdstatp->sense_hdr.sense_key == RECOVERED_ERROR) &&
			    (!cmdstatp->reमुख्यder_valid ||
			     cmdstatp->ureमुख्यder64 == 0)) अणु /* All written at EOM early warning */
				STp->dirty = 0;
				(STp->buffer)->buffer_bytes = 0;
				अगर (STps->drv_block >= 0)
					STps->drv_block += blks;
				result = (-ENOSPC);
			पूर्ण अन्यथा अणु
				st_prपूर्णांकk(KERN_ERR, STp, "Error on flush.\n");
				STps->drv_block = (-1);
				result = (-EIO);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (STps->drv_block >= 0)
				STps->drv_block += blks;
			STp->dirty = 0;
			(STp->buffer)->buffer_bytes = 0;
		पूर्ण
		st_release_request(SRpnt);
		SRpnt = शून्य;
	पूर्ण
	वापस result;
पूर्ण


/* Flush the tape buffer. The tape will be positioned correctly unless
   seek_next is true. */
अटल पूर्णांक flush_buffer(काष्ठा scsi_tape *STp, पूर्णांक seek_next)
अणु
	पूर्णांक backspace, result;
	काष्ठा st_partstat *STps;

	/*
	 * If there was a bus reset, block further access
	 * to this device.
	 */
	अगर (STp->pos_unknown)
		वापस (-EIO);

	अगर (STp->पढ़ोy != ST_READY)
		वापस 0;
	STps = &(STp->ps[STp->partition]);
	अगर (STps->rw == ST_WRITING)	/* Writing */
		वापस st_flush_ग_लिखो_buffer(STp);

	अगर (STp->block_size == 0)
		वापस 0;

	backspace = ((STp->buffer)->buffer_bytes +
		     (STp->buffer)->पढ़ो_poपूर्णांकer) / STp->block_size -
	    ((STp->buffer)->पढ़ो_poपूर्णांकer + STp->block_size - 1) /
	    STp->block_size;
	(STp->buffer)->buffer_bytes = 0;
	(STp->buffer)->पढ़ो_poपूर्णांकer = 0;
	result = 0;
	अगर (!seek_next) अणु
		अगर (STps->eof == ST_FM_HIT) अणु
			result = cross_eof(STp, 0);	/* Back over the खातापूर्ण hit */
			अगर (!result)
				STps->eof = ST_NOखातापूर्ण;
			अन्यथा अणु
				अगर (STps->drv_file >= 0)
					STps->drv_file++;
				STps->drv_block = 0;
			पूर्ण
		पूर्ण
		अगर (!result && backspace > 0)
			result = st_पूर्णांक_ioctl(STp, MTBSR, backspace);
	पूर्ण अन्यथा अगर (STps->eof == ST_FM_HIT) अणु
		अगर (STps->drv_file >= 0)
			STps->drv_file++;
		STps->drv_block = 0;
		STps->eof = ST_NOखातापूर्ण;
	पूर्ण
	वापस result;

पूर्ण

/* Set the mode parameters */
अटल पूर्णांक set_mode_densblk(काष्ठा scsi_tape * STp, काष्ठा st_modedef * STm)
अणु
	पूर्णांक set_it = 0;
	अचिन्हित दीर्घ arg;

	अगर (!STp->density_changed &&
	    STm->शेष_density >= 0 &&
	    STm->शेष_density != STp->density) अणु
		arg = STm->शेष_density;
		set_it = 1;
	पूर्ण अन्यथा
		arg = STp->density;
	arg <<= MT_ST_DENSITY_SHIFT;
	अगर (!STp->blksize_changed &&
	    STm->शेष_blksize >= 0 &&
	    STm->शेष_blksize != STp->block_size) अणु
		arg |= STm->शेष_blksize;
		set_it = 1;
	पूर्ण अन्यथा
		arg |= STp->block_size;
	अगर (set_it &&
	    st_पूर्णांक_ioctl(STp, SET_DENS_AND_BLK, arg)) अणु
		st_prपूर्णांकk(KERN_WARNING, STp,
			  "Can't set default block size to %d bytes "
			  "and density %x.\n",
			  STm->शेष_blksize, STm->शेष_density);
		अगर (modes_defined)
			वापस (-EINVAL);
	पूर्ण
	वापस 0;
पूर्ण


/* Lock or unlock the drive करोor. Don't use when st_request allocated. */
अटल पूर्णांक करो_करोor_lock(काष्ठा scsi_tape * STp, पूर्णांक करो_lock)
अणु
	पूर्णांक retval;

	DEBC_prपूर्णांकk(STp, "%socking drive door.\n", करो_lock ? "L" : "Unl");

	retval = scsi_set_medium_removal(STp->device,
			करो_lock ? SCSI_REMOVAL_PREVENT : SCSI_REMOVAL_ALLOW);
	अगर (!retval)
		STp->करोor_locked = करो_lock ? ST_LOCKED_EXPLICIT : ST_UNLOCKED;
	अन्यथा
		STp->करोor_locked = ST_LOCK_FAILS;
	वापस retval;
पूर्ण


/* Set the पूर्णांकernal state after reset */
अटल व्योम reset_state(काष्ठा scsi_tape *STp)
अणु
	पूर्णांक i;
	काष्ठा st_partstat *STps;

	STp->pos_unknown = 0;
	क्रम (i = 0; i < ST_NBR_PARTITIONS; i++) अणु
		STps = &(STp->ps[i]);
		STps->rw = ST_IDLE;
		STps->eof = ST_NOखातापूर्ण;
		STps->at_sm = 0;
		STps->last_block_valid = 0;
		STps->drv_block = -1;
		STps->drv_file = -1;
	पूर्ण
	अगर (STp->can_partitions) अणु
		STp->partition = find_partition(STp);
		अगर (STp->partition < 0)
			STp->partition = 0;
		STp->new_partition = STp->partition;
	पूर्ण
पूर्ण

/* Test अगर the drive is पढ़ोy. Returns either one of the codes below or a negative प्रणाली
   error code. */
#घोषणा CHKRES_READY       0
#घोषणा CHKRES_NEW_SESSION 1
#घोषणा CHKRES_NOT_READY   2
#घोषणा CHKRES_NO_TAPE     3

#घोषणा MAX_ATTENTIONS    10

अटल पूर्णांक test_पढ़ोy(काष्ठा scsi_tape *STp, पूर्णांक करो_रुको)
अणु
	पूर्णांक attentions, रुकोs, max_रुको, scode;
	पूर्णांक retval = CHKRES_READY, new_session = 0;
	अचिन्हित अक्षर cmd[MAX_COMMAND_SIZE];
	काष्ठा st_request *SRpnt = शून्य;
	काष्ठा st_cmdstatus *cmdstatp = &STp->buffer->cmdstat;

	max_रुको = करो_रुको ? ST_BLOCK_SECONDS : 0;

	क्रम (attentions=रुकोs=0; ; ) अणु
		स_रखो((व्योम *) &cmd[0], 0, MAX_COMMAND_SIZE);
		cmd[0] = TEST_UNIT_READY;
		SRpnt = st_करो_scsi(SRpnt, STp, cmd, 0, DMA_NONE,
				   STp->दीर्घ_समयout, MAX_READY_RETRIES, 1);

		अगर (!SRpnt) अणु
			retval = (STp->buffer)->syscall_result;
			अवरोध;
		पूर्ण

		अगर (cmdstatp->have_sense) अणु

			scode = cmdstatp->sense_hdr.sense_key;

			अगर (scode == UNIT_ATTENTION) अणु /* New media? */
				new_session = 1;
				अगर (attentions < MAX_ATTENTIONS) अणु
					attentions++;
					जारी;
				पूर्ण
				अन्यथा अणु
					retval = (-EIO);
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (scode == NOT_READY) अणु
				अगर (रुकोs < max_रुको) अणु
					अगर (msleep_पूर्णांकerruptible(1000)) अणु
						retval = (-EINTR);
						अवरोध;
					पूर्ण
					रुकोs++;
					जारी;
				पूर्ण
				अन्यथा अणु
					अगर ((STp->device)->scsi_level >= SCSI_2 &&
					    cmdstatp->sense_hdr.asc == 0x3a)	/* Check ASC */
						retval = CHKRES_NO_TAPE;
					अन्यथा
						retval = CHKRES_NOT_READY;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		retval = (STp->buffer)->syscall_result;
		अगर (!retval)
			retval = new_session ? CHKRES_NEW_SESSION : CHKRES_READY;
		अवरोध;
	पूर्ण

	अगर (SRpnt != शून्य)
		st_release_request(SRpnt);
	वापस retval;
पूर्ण


/* See अगर the drive is पढ़ोy and gather inक्रमmation about the tape. Return values:
   < 0   negative error code from त्रुटिसं.स
   0     drive पढ़ोy
   1     drive not पढ़ोy (possibly no tape)
*/
अटल पूर्णांक check_tape(काष्ठा scsi_tape *STp, काष्ठा file *filp)
अणु
	पूर्णांक i, retval, new_session = 0, करो_रुको;
	अचिन्हित अक्षर cmd[MAX_COMMAND_SIZE], saved_cleaning;
	अचिन्हित लघु st_flags = filp->f_flags;
	काष्ठा st_request *SRpnt = शून्य;
	काष्ठा st_modedef *STm;
	काष्ठा st_partstat *STps;
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक mode = TAPE_MODE(inode);

	STp->पढ़ोy = ST_READY;

	अगर (mode != STp->current_mode) अणु
		DEBC_prपूर्णांकk(STp, "Mode change from %d to %d.\n",
			    STp->current_mode, mode);
		new_session = 1;
		STp->current_mode = mode;
	पूर्ण
	STm = &(STp->modes[STp->current_mode]);

	saved_cleaning = STp->cleaning_req;
	STp->cleaning_req = 0;

	करो_रुको = ((filp->f_flags & O_NONBLOCK) == 0);
	retval = test_पढ़ोy(STp, करो_रुको);

	अगर (retval < 0)
	    जाओ err_out;

	अगर (retval == CHKRES_NEW_SESSION) अणु
		STp->pos_unknown = 0;
		STp->partition = STp->new_partition = 0;
		अगर (STp->can_partitions)
			STp->nbr_partitions = 1; /* This guess will be updated later
                                                    अगर necessary */
		क्रम (i = 0; i < ST_NBR_PARTITIONS; i++) अणु
			STps = &(STp->ps[i]);
			STps->rw = ST_IDLE;
			STps->eof = ST_NOखातापूर्ण;
			STps->at_sm = 0;
			STps->last_block_valid = 0;
			STps->drv_block = 0;
			STps->drv_file = 0;
		पूर्ण
		new_session = 1;
	पूर्ण
	अन्यथा अणु
		STp->cleaning_req |= saved_cleaning;

		अगर (retval == CHKRES_NOT_READY || retval == CHKRES_NO_TAPE) अणु
			अगर (retval == CHKRES_NO_TAPE)
				STp->पढ़ोy = ST_NO_TAPE;
			अन्यथा
				STp->पढ़ोy = ST_NOT_READY;

			STp->density = 0;	/* Clear the erroneous "residue" */
			STp->ग_लिखो_prot = 0;
			STp->block_size = 0;
			STp->ps[0].drv_file = STp->ps[0].drv_block = (-1);
			STp->partition = STp->new_partition = 0;
			STp->करोor_locked = ST_UNLOCKED;
			वापस CHKRES_NOT_READY;
		पूर्ण
	पूर्ण

	अगर (STp->omit_blklims)
		STp->min_block = STp->max_block = (-1);
	अन्यथा अणु
		स_रखो((व्योम *) &cmd[0], 0, MAX_COMMAND_SIZE);
		cmd[0] = READ_BLOCK_LIMITS;

		SRpnt = st_करो_scsi(SRpnt, STp, cmd, 6, DMA_FROM_DEVICE,
				   STp->device->request_queue->rq_समयout,
				   MAX_READY_RETRIES, 1);
		अगर (!SRpnt) अणु
			retval = (STp->buffer)->syscall_result;
			जाओ err_out;
		पूर्ण

		अगर (!SRpnt->result && !STp->buffer->cmdस्थिति.सave_sense) अणु
			STp->max_block = ((STp->buffer)->b_data[1] << 16) |
			    ((STp->buffer)->b_data[2] << 8) | (STp->buffer)->b_data[3];
			STp->min_block = ((STp->buffer)->b_data[4] << 8) |
			    (STp->buffer)->b_data[5];
			अगर ( DEB( debugging || ) !STp->inited)
				st_prपूर्णांकk(KERN_INFO, STp,
					  "Block limits %d - %d bytes.\n",
					  STp->min_block, STp->max_block);
		पूर्ण अन्यथा अणु
			STp->min_block = STp->max_block = (-1);
			DEBC_prपूर्णांकk(STp, "Can't read block limits.\n");
		पूर्ण
	पूर्ण

	स_रखो((व्योम *) &cmd[0], 0, MAX_COMMAND_SIZE);
	cmd[0] = MODE_SENSE;
	cmd[4] = 12;

	SRpnt = st_करो_scsi(SRpnt, STp, cmd, 12, DMA_FROM_DEVICE,
			   STp->device->request_queue->rq_समयout,
			   MAX_READY_RETRIES, 1);
	अगर (!SRpnt) अणु
		retval = (STp->buffer)->syscall_result;
		जाओ err_out;
	पूर्ण

	अगर ((STp->buffer)->syscall_result != 0) अणु
		DEBC_prपूर्णांकk(STp, "No Mode Sense.\n");
		STp->block_size = ST_DEFAULT_BLOCK;	/* Educated guess (?) */
		(STp->buffer)->syscall_result = 0;	/* Prevent error propagation */
		STp->drv_ग_लिखो_prot = 0;
	पूर्ण अन्यथा अणु
		DEBC_prपूर्णांकk(STp,"Mode sense. Length %d, "
			    "medium %x, WBS %x, BLL %d\n",
			    (STp->buffer)->b_data[0],
			    (STp->buffer)->b_data[1],
			    (STp->buffer)->b_data[2],
			    (STp->buffer)->b_data[3]);

		अगर ((STp->buffer)->b_data[3] >= 8) अणु
			STp->drv_buffer = ((STp->buffer)->b_data[2] >> 4) & 7;
			STp->density = (STp->buffer)->b_data[4];
			STp->block_size = (STp->buffer)->b_data[9] * 65536 +
			    (STp->buffer)->b_data[10] * 256 + (STp->buffer)->b_data[11];
			DEBC_prपूर्णांकk(STp, "Density %x, tape length: %x, "
				    "drv buffer: %d\n",
				    STp->density,
				    (STp->buffer)->b_data[5] * 65536 +
				    (STp->buffer)->b_data[6] * 256 +
				    (STp->buffer)->b_data[7],
				    STp->drv_buffer);
		पूर्ण
		STp->drv_ग_लिखो_prot = ((STp->buffer)->b_data[2] & 0x80) != 0;
		अगर (!STp->drv_buffer && STp->immediate_filemark) अणु
			st_prपूर्णांकk(KERN_WARNING, STp,
				  "non-buffered tape: disabling "
				  "writing immediate filemarks\n");
			STp->immediate_filemark = 0;
		पूर्ण
	पूर्ण
	st_release_request(SRpnt);
	SRpnt = शून्य;
	STp->inited = 1;

	अगर (STp->block_size > 0)
		(STp->buffer)->buffer_blocks =
			(STp->buffer)->buffer_size / STp->block_size;
	अन्यथा
		(STp->buffer)->buffer_blocks = 1;
	(STp->buffer)->buffer_bytes = (STp->buffer)->पढ़ो_poपूर्णांकer = 0;

	DEBC_prपूर्णांकk(STp, "Block size: %d, buffer size: %d (%d blocks).\n",
		    STp->block_size, (STp->buffer)->buffer_size,
		    (STp->buffer)->buffer_blocks);

	अगर (STp->drv_ग_लिखो_prot) अणु
		STp->ग_लिखो_prot = 1;

		DEBC_prपूर्णांकk(STp, "Write protected\n");

		अगर (करो_रुको &&
		    ((st_flags & O_ACCMODE) == O_WRONLY ||
		     (st_flags & O_ACCMODE) == O_RDWR)) अणु
			retval = (-EROFS);
			जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (STp->can_partitions && STp->nbr_partitions < 1) अणु
		/* This code is reached when the device is खोलोed क्रम the first समय
		   after the driver has been initialized with tape in the drive and the
		   partition support has been enabled. */
		DEBC_prपूर्णांकk(STp, "Updating partition number in status.\n");
		अगर ((STp->partition = find_partition(STp)) < 0) अणु
			retval = STp->partition;
			जाओ err_out;
		पूर्ण
		STp->new_partition = STp->partition;
		STp->nbr_partitions = 1; /* This guess will be updated when necessary */
	पूर्ण

	अगर (new_session) अणु	/* Change the drive parameters क्रम the new mode */
		STp->density_changed = STp->blksize_changed = 0;
		STp->compression_changed = 0;
		अगर (!(STm->शेषs_क्रम_ग_लिखोs) &&
		    (retval = set_mode_densblk(STp, STm)) < 0)
		    जाओ err_out;

		अगर (STp->शेष_drvbuffer != 0xff) अणु
			अगर (st_पूर्णांक_ioctl(STp, MTSETDRVBUFFER, STp->शेष_drvbuffer))
				st_prपूर्णांकk(KERN_WARNING, STp,
					  "Can't set default drive "
					  "buffering to %d.\n",
					  STp->शेष_drvbuffer);
		पूर्ण
	पूर्ण

	वापस CHKRES_READY;

 err_out:
	वापस retval;
पूर्ण


/* Open the device. Needs to take the BKL only because of incrementing the SCSI host
   module count. */
अटल पूर्णांक st_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक i, retval = (-EIO);
	पूर्णांक resumed = 0;
	काष्ठा scsi_tape *STp;
	काष्ठा st_partstat *STps;
	पूर्णांक dev = TAPE_NR(inode);

	/*
	 * We really want to करो nonseekable_खोलो(inode, filp); here, but some
	 * versions of tar incorrectly call lseek on tapes and bail out अगर that
	 * fails.  So we disallow pपढ़ो() and pग_लिखो(), but permit lseeks.
	 */
	filp->f_mode &= ~(FMODE_PREAD | FMODE_PWRITE);

	अगर (!(STp = scsi_tape_get(dev))) अणु
		वापस -ENXIO;
	पूर्ण

	filp->निजी_data = STp;

	spin_lock(&st_use_lock);
	अगर (STp->in_use) अणु
		spin_unlock(&st_use_lock);
		DEBC_prपूर्णांकk(STp, "Device already in use.\n");
		scsi_tape_put(STp);
		वापस (-EBUSY);
	पूर्ण

	STp->in_use = 1;
	spin_unlock(&st_use_lock);
	STp->rew_at_बंद = STp->स्वतःrew_dev = (iminor(inode) & 0x80) == 0;

	अगर (scsi_स्वतःpm_get_device(STp->device) < 0) अणु
		retval = -EIO;
		जाओ err_out;
	पूर्ण
	resumed = 1;
	अगर (!scsi_block_when_processing_errors(STp->device)) अणु
		retval = (-ENXIO);
		जाओ err_out;
	पूर्ण

	/* See that we have at least a one page buffer available */
	अगर (!enlarge_buffer(STp->buffer, PAGE_SIZE)) अणु
		st_prपूर्णांकk(KERN_WARNING, STp,
			  "Can't allocate one page tape buffer.\n");
		retval = (-EOVERFLOW);
		जाओ err_out;
	पूर्ण

	(STp->buffer)->cleared = 0;
	(STp->buffer)->writing = 0;
	(STp->buffer)->syscall_result = 0;

	STp->ग_लिखो_prot = ((filp->f_flags & O_ACCMODE) == O_RDONLY);

	STp->dirty = 0;
	क्रम (i = 0; i < ST_NBR_PARTITIONS; i++) अणु
		STps = &(STp->ps[i]);
		STps->rw = ST_IDLE;
	पूर्ण
	STp->try_dio_now = STp->try_dio;
	STp->recover_count = 0;
	DEB( STp->nbr_रुकोs = STp->nbr_finished = 0;
	     STp->nbr_requests = STp->nbr_dio = STp->nbr_pages = 0; )

	retval = check_tape(STp, filp);
	अगर (retval < 0)
		जाओ err_out;
	अगर ((filp->f_flags & O_NONBLOCK) == 0 &&
	    retval != CHKRES_READY) अणु
		अगर (STp->पढ़ोy == NO_TAPE)
			retval = (-ENOMEDIUM);
		अन्यथा
			retval = (-EIO);
		जाओ err_out;
	पूर्ण
	वापस 0;

 err_out:
	normalize_buffer(STp->buffer);
	spin_lock(&st_use_lock);
	STp->in_use = 0;
	spin_unlock(&st_use_lock);
	अगर (resumed)
		scsi_स्वतःpm_put_device(STp->device);
	scsi_tape_put(STp);
	वापस retval;

पूर्ण


/* Flush the tape buffer beक्रमe बंद */
अटल पूर्णांक st_flush(काष्ठा file *filp, fl_owner_t id)
अणु
	पूर्णांक result = 0, result2;
	अचिन्हित अक्षर cmd[MAX_COMMAND_SIZE];
	काष्ठा st_request *SRpnt;
	काष्ठा scsi_tape *STp = filp->निजी_data;
	काष्ठा st_modedef *STm = &(STp->modes[STp->current_mode]);
	काष्ठा st_partstat *STps = &(STp->ps[STp->partition]);

	अगर (file_count(filp) > 1)
		वापस 0;

	अगर (STps->rw == ST_WRITING && !STp->pos_unknown) अणु
		result = st_flush_ग_लिखो_buffer(STp);
		अगर (result != 0 && result != (-ENOSPC))
			जाओ out;
	पूर्ण

	अगर (STp->can_partitions &&
	    (result2 = चयन_partition(STp)) < 0) अणु
		DEBC_prपूर्णांकk(STp, "switch_partition at close failed.\n");
		अगर (result == 0)
			result = result2;
		जाओ out;
	पूर्ण

	DEBC( अगर (STp->nbr_requests)
		st_prपूर्णांकk(KERN_DEBUG, STp,
			  "Number of r/w requests %d, dio used in %d, "
			  "pages %d.\n", STp->nbr_requests, STp->nbr_dio,
			  STp->nbr_pages));

	अगर (STps->rw == ST_WRITING && !STp->pos_unknown) अणु
		काष्ठा st_cmdstatus *cmdstatp = &STp->buffer->cmdstat;

#अगर DEBUG
		DEBC_prपूर्णांकk(STp, "Async write waits %d, finished %d.\n",
			    STp->nbr_रुकोs, STp->nbr_finished);
#पूर्ण_अगर
		स_रखो(cmd, 0, MAX_COMMAND_SIZE);
		cmd[0] = WRITE_खाताMARKS;
		अगर (STp->immediate_filemark)
			cmd[1] = 1;
		cmd[4] = 1 + STp->two_fm;

		SRpnt = st_करो_scsi(शून्य, STp, cmd, 0, DMA_NONE,
				   STp->device->request_queue->rq_समयout,
				   MAX_WRITE_RETRIES, 1);
		अगर (!SRpnt) अणु
			result = (STp->buffer)->syscall_result;
			जाओ out;
		पूर्ण

		अगर (STp->buffer->syscall_result == 0 ||
		    (cmdstatp->have_sense && !cmdstatp->deferred &&
		     (cmdstatp->flags & SENSE_EOM) &&
		     (cmdstatp->sense_hdr.sense_key == NO_SENSE ||
		      cmdstatp->sense_hdr.sense_key == RECOVERED_ERROR) &&
		     (!cmdstatp->reमुख्यder_valid || cmdstatp->ureमुख्यder64 == 0))) अणु
			/* Write successful at EOM */
			st_release_request(SRpnt);
			SRpnt = शून्य;
			अगर (STps->drv_file >= 0)
				STps->drv_file++;
			STps->drv_block = 0;
			अगर (STp->two_fm)
				cross_eof(STp, 0);
			STps->eof = ST_FM;
		पूर्ण
		अन्यथा अणु /* Write error */
			st_release_request(SRpnt);
			SRpnt = शून्य;
			st_prपूर्णांकk(KERN_ERR, STp,
				  "Error on write filemark.\n");
			अगर (result == 0)
				result = (-EIO);
		पूर्ण

		DEBC_prपूर्णांकk(STp, "Buffer flushed, %d EOF(s) written\n", cmd[4]);
	पूर्ण अन्यथा अगर (!STp->rew_at_बंद) अणु
		STps = &(STp->ps[STp->partition]);
		अगर (!STm->sysv || STps->rw != ST_READING) अणु
			अगर (STp->can_bsr)
				result = flush_buffer(STp, 0);
			अन्यथा अगर (STps->eof == ST_FM_HIT) अणु
				result = cross_eof(STp, 0);
				अगर (result) अणु
					अगर (STps->drv_file >= 0)
						STps->drv_file++;
					STps->drv_block = 0;
					STps->eof = ST_FM;
				पूर्ण अन्यथा
					STps->eof = ST_NOखातापूर्ण;
			पूर्ण
		पूर्ण अन्यथा अगर ((STps->eof == ST_NOखातापूर्ण &&
			    !(result = cross_eof(STp, 1))) ||
			   STps->eof == ST_FM_HIT) अणु
			अगर (STps->drv_file >= 0)
				STps->drv_file++;
			STps->drv_block = 0;
			STps->eof = ST_FM;
		पूर्ण
	पूर्ण

      out:
	अगर (STp->rew_at_बंद) अणु
		result2 = st_पूर्णांक_ioctl(STp, MTREW, 1);
		अगर (result == 0)
			result = result2;
	पूर्ण
	वापस result;
पूर्ण


/* Close the device and release it. BKL is not needed: this is the only thपढ़ो
   accessing this tape. */
अटल पूर्णांक st_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा scsi_tape *STp = filp->निजी_data;

	अगर (STp->करोor_locked == ST_LOCKED_AUTO)
		करो_करोor_lock(STp, 0);

	normalize_buffer(STp->buffer);
	spin_lock(&st_use_lock);
	STp->in_use = 0;
	spin_unlock(&st_use_lock);
	scsi_स्वतःpm_put_device(STp->device);
	scsi_tape_put(STp);

	वापस 0;
पूर्ण

/* The checks common to both पढ़ोing and writing */
अटल sमाप_प्रकार rw_checks(काष्ठा scsi_tape *STp, काष्ठा file *filp, माप_प्रकार count)
अणु
	sमाप_प्रकार retval = 0;

	/*
	 * If we are in the middle of error recovery, करोn't let anyone
	 * अन्यथा try and use this device.  Also, अगर error recovery fails, it
	 * may try and take the device offline, in which हाल all further
	 * access to the device is prohibited.
	 */
	अगर (!scsi_block_when_processing_errors(STp->device)) अणु
		retval = (-ENXIO);
		जाओ out;
	पूर्ण

	अगर (STp->पढ़ोy != ST_READY) अणु
		अगर (STp->पढ़ोy == ST_NO_TAPE)
			retval = (-ENOMEDIUM);
		अन्यथा
			retval = (-EIO);
		जाओ out;
	पूर्ण

	अगर (! STp->modes[STp->current_mode].defined) अणु
		retval = (-ENXIO);
		जाओ out;
	पूर्ण


	/*
	 * If there was a bus reset, block further access
	 * to this device.
	 */
	अगर (STp->pos_unknown) अणु
		retval = (-EIO);
		जाओ out;
	पूर्ण

	अगर (count == 0)
		जाओ out;

	DEB(
	अगर (!STp->in_use) अणु
		st_prपूर्णांकk(ST_DEB_MSG, STp,
			  "Incorrect device.\n");
		retval = (-EIO);
		जाओ out;
	पूर्ण ) /* end DEB */

	अगर (STp->can_partitions &&
	    (retval = चयन_partition(STp)) < 0)
		जाओ out;

	अगर (STp->block_size == 0 && STp->max_block > 0 &&
	    (count < STp->min_block || count > STp->max_block)) अणु
		retval = (-EINVAL);
		जाओ out;
	पूर्ण

	अगर (STp->करो_स्वतः_lock && STp->करोor_locked == ST_UNLOCKED &&
	    !करो_करोor_lock(STp, 1))
		STp->करोor_locked = ST_LOCKED_AUTO;

 out:
	वापस retval;
पूर्ण


अटल पूर्णांक setup_buffering(काष्ठा scsi_tape *STp, स्थिर अक्षर __user *buf,
			   माप_प्रकार count, पूर्णांक is_पढ़ो)
अणु
	पूर्णांक i, bufsize, retval = 0;
	काष्ठा st_buffer *STbp = STp->buffer;

	अगर (is_पढ़ो)
		i = STp->try_dio_now && try_rdio;
	अन्यथा
		i = STp->try_dio_now && try_wdio;

	अगर (i && ((अचिन्हित दीर्घ)buf & queue_dma_alignment(
					STp->device->request_queue)) == 0) अणु
		i = sgl_map_user_pages(STbp, STbp->use_sg, (अचिन्हित दीर्घ)buf,
				       count, (is_पढ़ो ? READ : WRITE));
		अगर (i > 0) अणु
			STbp->करो_dio = i;
			STbp->buffer_bytes = 0;   /* can be used as transfer counter */
		पूर्ण
		अन्यथा
			STbp->करो_dio = 0;  /* fall back to buffering with any error */
		STbp->sg_segs = STbp->करो_dio;
		DEB(
		     अगर (STbp->करो_dio) अणु
			STp->nbr_dio++;
			STp->nbr_pages += STbp->करो_dio;
		     पूर्ण
		)
	पूर्ण अन्यथा
		STbp->करो_dio = 0;
	DEB( STp->nbr_requests++; )

	अगर (!STbp->करो_dio) अणु
		अगर (STp->block_size)
			bufsize = STp->block_size > st_fixed_buffer_size ?
				STp->block_size : st_fixed_buffer_size;
		अन्यथा अणु
			bufsize = count;
			/* Make sure that data from previous user is not leaked even अगर
			   HBA करोes not वापस correct residual */
			अगर (is_पढ़ो && STp->sili && !STbp->cleared)
				clear_buffer(STbp);
		पूर्ण

		अगर (bufsize > STbp->buffer_size &&
		    !enlarge_buffer(STbp, bufsize)) अणु
			st_prपूर्णांकk(KERN_WARNING, STp,
				  "Can't allocate %d byte tape buffer.\n",
				  bufsize);
			retval = (-EOVERFLOW);
			जाओ out;
		पूर्ण
		अगर (STp->block_size)
			STbp->buffer_blocks = bufsize / STp->block_size;
	पूर्ण

 out:
	वापस retval;
पूर्ण


/* Can be called more than once after each setup_buffer() */
अटल व्योम release_buffering(काष्ठा scsi_tape *STp, पूर्णांक is_पढ़ो)
अणु
	काष्ठा st_buffer *STbp;

	STbp = STp->buffer;
	अगर (STbp->करो_dio) अणु
		sgl_unmap_user_pages(STbp, STbp->करो_dio, is_पढ़ो);
		STbp->करो_dio = 0;
		STbp->sg_segs = 0;
	पूर्ण
पूर्ण


/* Write command */
अटल sमाप_प्रकार
st_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t * ppos)
अणु
	sमाप_प्रकार total;
	sमाप_प्रकार i, करो_count, blks, transfer;
	sमाप_प्रकार retval;
	पूर्णांक unकरोne, retry_eot = 0, scode;
	पूर्णांक async_ग_लिखो;
	अचिन्हित अक्षर cmd[MAX_COMMAND_SIZE];
	स्थिर अक्षर __user *b_poपूर्णांक;
	काष्ठा st_request *SRpnt = शून्य;
	काष्ठा scsi_tape *STp = filp->निजी_data;
	काष्ठा st_modedef *STm;
	काष्ठा st_partstat *STps;
	काष्ठा st_buffer *STbp;

	अगर (mutex_lock_पूर्णांकerruptible(&STp->lock))
		वापस -ERESTARTSYS;

	retval = rw_checks(STp, filp, count);
	अगर (retval || count == 0)
		जाओ out;

	/* Write must be पूर्णांकegral number of blocks */
	अगर (STp->block_size != 0 && (count % STp->block_size) != 0) अणु
		st_prपूर्णांकk(KERN_WARNING, STp,
			  "Write not multiple of tape block size.\n");
		retval = (-EINVAL);
		जाओ out;
	पूर्ण

	STm = &(STp->modes[STp->current_mode]);
	STps = &(STp->ps[STp->partition]);

	अगर (STp->ग_लिखो_prot) अणु
		retval = (-EACCES);
		जाओ out;
	पूर्ण


	अगर (STps->rw == ST_READING) अणु
		retval = flush_buffer(STp, 0);
		अगर (retval)
			जाओ out;
		STps->rw = ST_WRITING;
	पूर्ण अन्यथा अगर (STps->rw != ST_WRITING &&
		   STps->drv_file == 0 && STps->drv_block == 0) अणु
		अगर ((retval = set_mode_densblk(STp, STm)) < 0)
			जाओ out;
		अगर (STm->शेष_compression != ST_DONT_TOUCH &&
		    !(STp->compression_changed)) अणु
			अगर (st_compression(STp, (STm->शेष_compression == ST_YES))) अणु
				st_prपूर्णांकk(KERN_WARNING, STp,
					  "Can't set default compression.\n");
				अगर (modes_defined) अणु
					retval = (-EINVAL);
					जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	STbp = STp->buffer;
	i = ग_लिखो_behind_check(STp);
	अगर (i) अणु
		अगर (i == -ENOSPC)
			STps->eof = ST_EOM_OK;
		अन्यथा
			STps->eof = ST_EOM_ERROR;
	पूर्ण

	अगर (STps->eof == ST_EOM_OK) अणु
		STps->eof = ST_EOD_1;  /* allow next ग_लिखो */
		retval = (-ENOSPC);
		जाओ out;
	पूर्ण
	अन्यथा अगर (STps->eof == ST_EOM_ERROR) अणु
		retval = (-EIO);
		जाओ out;
	पूर्ण

	/* Check the buffer पढ़ोability in हालs where copy_user might catch
	   the problems after some tape movement. */
	अगर (STp->block_size != 0 &&
	    !STbp->करो_dio &&
	    (copy_from_user(&i, buf, 1) != 0 ||
	     copy_from_user(&i, buf + count - 1, 1) != 0)) अणु
		retval = (-EFAULT);
		जाओ out;
	पूर्ण

	retval = setup_buffering(STp, buf, count, 0);
	अगर (retval)
		जाओ out;

	total = count;

	स_रखो(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = WRITE_6;
	cmd[1] = (STp->block_size != 0);

	STps->rw = ST_WRITING;

	b_poपूर्णांक = buf;
	जबतक (count > 0 && !retry_eot) अणु

		अगर (STbp->करो_dio) अणु
			करो_count = count;
		पूर्ण
		अन्यथा अणु
			अगर (STp->block_size == 0)
				करो_count = count;
			अन्यथा अणु
				करो_count = STbp->buffer_blocks * STp->block_size -
					STbp->buffer_bytes;
				अगर (करो_count > count)
					करो_count = count;
			पूर्ण

			i = append_to_buffer(b_poपूर्णांक, STbp, करो_count);
			अगर (i) अणु
				retval = i;
				जाओ out;
			पूर्ण
		पूर्ण
		count -= करो_count;
		b_poपूर्णांक += करो_count;

		async_ग_लिखो = STp->block_size == 0 && !STbp->करो_dio &&
			STm->करो_async_ग_लिखोs && STps->eof < ST_EOM_OK;

		अगर (STp->block_size != 0 && STm->करो_buffer_ग_लिखोs &&
		    !(STp->try_dio_now && try_wdio) && STps->eof < ST_EOM_OK &&
		    STbp->buffer_bytes < STbp->buffer_size) अणु
			STp->dirty = 1;
			/* Don't ग_लिखो a buffer that is not full enough. */
			अगर (!async_ग_लिखो && count == 0)
				अवरोध;
		पूर्ण

	retry_ग_लिखो:
		अगर (STp->block_size == 0)
			blks = transfer = करो_count;
		अन्यथा अणु
			अगर (!STbp->करो_dio)
				blks = STbp->buffer_bytes;
			अन्यथा
				blks = करो_count;
			blks /= STp->block_size;
			transfer = blks * STp->block_size;
		पूर्ण
		cmd[2] = blks >> 16;
		cmd[3] = blks >> 8;
		cmd[4] = blks;

		SRpnt = st_करो_scsi(SRpnt, STp, cmd, transfer, DMA_TO_DEVICE,
				   STp->device->request_queue->rq_समयout,
				   MAX_WRITE_RETRIES, !async_ग_लिखो);
		अगर (!SRpnt) अणु
			retval = STbp->syscall_result;
			जाओ out;
		पूर्ण
		अगर (async_ग_लिखो && !STbp->syscall_result) अणु
			STbp->writing = transfer;
			STp->dirty = !(STbp->writing ==
				       STbp->buffer_bytes);
			SRpnt = शून्य;  /* Prevent releasing this request! */
			DEB( STp->ग_लिखो_pending = 1; )
			अवरोध;
		पूर्ण

		अगर (STbp->syscall_result != 0) अणु
			काष्ठा st_cmdstatus *cmdstatp = &STp->buffer->cmdstat;

			DEBC_prपूर्णांकk(STp, "Error on write:\n");
			अगर (cmdstatp->have_sense && (cmdstatp->flags & SENSE_EOM)) अणु
				scode = cmdstatp->sense_hdr.sense_key;
				अगर (cmdstatp->reमुख्यder_valid)
					unकरोne = (पूर्णांक)cmdstatp->ureमुख्यder64;
				अन्यथा अगर (STp->block_size == 0 &&
					 scode == VOLUME_OVERFLOW)
					unकरोne = transfer;
				अन्यथा
					unकरोne = 0;
				अगर (STp->block_size != 0)
					unकरोne *= STp->block_size;
				अगर (unकरोne <= करो_count) अणु
					/* Only data from this ग_लिखो is not written */
					count += unकरोne;
					b_poपूर्णांक -= unकरोne;
					करो_count -= unकरोne;
					अगर (STp->block_size)
						blks = (transfer - unकरोne) / STp->block_size;
					STps->eof = ST_EOM_OK;
					/* Continue in fixed block mode अगर all written
					   in this request but still something left to ग_लिखो
					   (retval left to zero)
					*/
					अगर (STp->block_size == 0 ||
					    unकरोne > 0 || count == 0)
						retval = (-ENOSPC); /* EOM within current request */
					DEBC_prपूर्णांकk(STp, "EOM with %d "
						    "bytes unwritten.\n",
						    (पूर्णांक)count);
				पूर्ण अन्यथा अणु
					/* EOT within data buffered earlier (possible only
					   in fixed block mode without direct i/o) */
					अगर (!retry_eot && !cmdstatp->deferred &&
					    (scode == NO_SENSE || scode == RECOVERED_ERROR)) अणु
						move_buffer_data(STp->buffer, transfer - unकरोne);
						retry_eot = 1;
						अगर (STps->drv_block >= 0) अणु
							STps->drv_block += (transfer - unकरोne) /
								STp->block_size;
						पूर्ण
						STps->eof = ST_EOM_OK;
						DEBC_prपूर्णांकk(STp, "Retry "
							    "write of %d "
							    "bytes at EOM.\n",
							    STp->buffer->buffer_bytes);
						जाओ retry_ग_लिखो;
					पूर्ण
					अन्यथा अणु
						/* Either error within data buffered by driver or
						   failed retry */
						count -= करो_count;
						blks = करो_count = 0;
						STps->eof = ST_EOM_ERROR;
						STps->drv_block = (-1); /* Too cautious? */
						retval = (-EIO);	/* EOM क्रम old data */
						DEBC_prपूर्णांकk(STp, "EOM with "
							    "lost data.\n");
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				count += करो_count;
				STps->drv_block = (-1);		/* Too cautious? */
				retval = STbp->syscall_result;
			पूर्ण

		पूर्ण

		अगर (STps->drv_block >= 0) अणु
			अगर (STp->block_size == 0)
				STps->drv_block += (करो_count > 0);
			अन्यथा
				STps->drv_block += blks;
		पूर्ण

		STbp->buffer_bytes = 0;
		STp->dirty = 0;

		अगर (retval || retry_eot) अणु
			अगर (count < total)
				retval = total - count;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (STps->eof == ST_EOD_1)
		STps->eof = ST_EOM_OK;
	अन्यथा अगर (STps->eof != ST_EOM_OK)
		STps->eof = ST_NOखातापूर्ण;
	retval = total - count;

 out:
	अगर (SRpnt != शून्य)
		st_release_request(SRpnt);
	release_buffering(STp, 0);
	mutex_unlock(&STp->lock);

	वापस retval;
पूर्ण

/* Read data from the tape. Returns zero in the normal हाल, one अगर the
   eof status has changed, and the negative error code in हाल of a
   fatal error. Otherwise updates the buffer and the eof state.

   Does release user buffer mapping अगर it is set.
*/
अटल दीर्घ पढ़ो_tape(काष्ठा scsi_tape *STp, दीर्घ count,
		      काष्ठा st_request ** aSRpnt)
अणु
	पूर्णांक transfer, blks, bytes;
	अचिन्हित अक्षर cmd[MAX_COMMAND_SIZE];
	काष्ठा st_request *SRpnt;
	काष्ठा st_modedef *STm;
	काष्ठा st_partstat *STps;
	काष्ठा st_buffer *STbp;
	पूर्णांक retval = 0;

	अगर (count == 0)
		वापस 0;

	STm = &(STp->modes[STp->current_mode]);
	STps = &(STp->ps[STp->partition]);
	अगर (STps->eof == ST_FM_HIT)
		वापस 1;
	STbp = STp->buffer;

	अगर (STp->block_size == 0)
		blks = bytes = count;
	अन्यथा अणु
		अगर (!(STp->try_dio_now && try_rdio) && STm->करो_पढ़ो_ahead) अणु
			blks = (STp->buffer)->buffer_blocks;
			bytes = blks * STp->block_size;
		पूर्ण अन्यथा अणु
			bytes = count;
			अगर (!STbp->करो_dio && bytes > (STp->buffer)->buffer_size)
				bytes = (STp->buffer)->buffer_size;
			blks = bytes / STp->block_size;
			bytes = blks * STp->block_size;
		पूर्ण
	पूर्ण

	स_रखो(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = READ_6;
	cmd[1] = (STp->block_size != 0);
	अगर (!cmd[1] && STp->sili)
		cmd[1] |= 2;
	cmd[2] = blks >> 16;
	cmd[3] = blks >> 8;
	cmd[4] = blks;

	SRpnt = *aSRpnt;
	SRpnt = st_करो_scsi(SRpnt, STp, cmd, bytes, DMA_FROM_DEVICE,
			   STp->device->request_queue->rq_समयout,
			   MAX_RETRIES, 1);
	release_buffering(STp, 1);
	*aSRpnt = SRpnt;
	अगर (!SRpnt)
		वापस STbp->syscall_result;

	STbp->पढ़ो_poपूर्णांकer = 0;
	STps->at_sm = 0;

	/* Something to check */
	अगर (STbp->syscall_result) अणु
		काष्ठा st_cmdstatus *cmdstatp = &STp->buffer->cmdstat;

		retval = 1;
		DEBC_prपूर्णांकk(STp,
			    "Sense: %2x %2x %2x %2x %2x %2x %2x %2x\n",
			    SRpnt->sense[0], SRpnt->sense[1],
			    SRpnt->sense[2], SRpnt->sense[3],
			    SRpnt->sense[4], SRpnt->sense[5],
			    SRpnt->sense[6], SRpnt->sense[7]);
		अगर (cmdstatp->have_sense) अणु

			अगर (cmdstatp->sense_hdr.sense_key == BLANK_CHECK)
				cmdstatp->flags &= 0xcf;	/* No need क्रम EOM in this हाल */

			अगर (cmdstatp->flags != 0) अणु /* खातापूर्ण, EOM, or ILI */
				/* Compute the residual count */
				अगर (cmdstatp->reमुख्यder_valid)
					transfer = (पूर्णांक)cmdstatp->ureमुख्यder64;
				अन्यथा
					transfer = 0;
				अगर (cmdstatp->sense_hdr.sense_key == MEDIUM_ERROR) अणु
					अगर (STp->block_size == 0)
						transfer = bytes;
					/* Some drives set ILI with MEDIUM ERROR */
					cmdstatp->flags &= ~SENSE_ILI;
				पूर्ण

				अगर (cmdstatp->flags & SENSE_ILI) अणु	/* ILI */
					अगर (STp->block_size == 0 &&
					    transfer < 0) अणु
						st_prपूर्णांकk(KERN_NOTICE, STp,
							  "Failed to read %d "
							  "byte block with %d "
							  "byte transfer.\n",
							  bytes - transfer,
							  bytes);
						अगर (STps->drv_block >= 0)
							STps->drv_block += 1;
						STbp->buffer_bytes = 0;
						वापस (-ENOMEM);
					पूर्ण अन्यथा अगर (STp->block_size == 0) अणु
						STbp->buffer_bytes = bytes - transfer;
					पूर्ण अन्यथा अणु
						st_release_request(SRpnt);
						SRpnt = *aSRpnt = शून्य;
						अगर (transfer == blks) अणु	/* We did not get anything, error */
							st_prपूर्णांकk(KERN_NOTICE, STp,
								  "Incorrect "
								  "block size.\n");
							अगर (STps->drv_block >= 0)
								STps->drv_block += blks - transfer + 1;
							st_पूर्णांक_ioctl(STp, MTBSR, 1);
							वापस (-EIO);
						पूर्ण
						/* We have some data, deliver it */
						STbp->buffer_bytes = (blks - transfer) *
						    STp->block_size;
						DEBC_prपूर्णांकk(STp, "ILI but "
							    "enough data "
							    "received %ld "
							    "%d.\n", count,
							    STbp->buffer_bytes);
						अगर (STps->drv_block >= 0)
							STps->drv_block += 1;
						अगर (st_पूर्णांक_ioctl(STp, MTBSR, 1))
							वापस (-EIO);
					पूर्ण
				पूर्ण अन्यथा अगर (cmdstatp->flags & SENSE_FMK) अणु	/* FM overrides EOM */
					अगर (STps->eof != ST_FM_HIT)
						STps->eof = ST_FM_HIT;
					अन्यथा
						STps->eof = ST_EOD_2;
					अगर (STp->block_size == 0)
						STbp->buffer_bytes = 0;
					अन्यथा
						STbp->buffer_bytes =
						    bytes - transfer * STp->block_size;
					DEBC_prपूर्णांकk(STp, "EOF detected (%d "
						    "bytes read).\n",
						    STbp->buffer_bytes);
				पूर्ण अन्यथा अगर (cmdstatp->flags & SENSE_EOM) अणु
					अगर (STps->eof == ST_FM)
						STps->eof = ST_EOD_1;
					अन्यथा
						STps->eof = ST_EOM_OK;
					अगर (STp->block_size == 0)
						STbp->buffer_bytes = bytes - transfer;
					अन्यथा
						STbp->buffer_bytes =
						    bytes - transfer * STp->block_size;

					DEBC_prपूर्णांकk(STp, "EOM detected (%d "
						    "bytes read).\n",
						    STbp->buffer_bytes);
				पूर्ण
			पूर्ण
			/* end of खातापूर्ण, EOM, ILI test */
			अन्यथा अणु	/* nonzero sense key */
				DEBC_prपूर्णांकk(STp, "Tape error while reading.\n");
				STps->drv_block = (-1);
				अगर (STps->eof == ST_FM &&
				    cmdstatp->sense_hdr.sense_key == BLANK_CHECK) अणु
					DEBC_prपूर्णांकk(STp, "Zero returned for "
						    "first BLANK CHECK "
						    "after EOF.\n");
					STps->eof = ST_EOD_2;	/* First BLANK_CHECK after FM */
				पूर्ण अन्यथा	/* Some other extended sense code */
					retval = (-EIO);
			पूर्ण

			अगर (STbp->buffer_bytes < 0)  /* Caused by bogus sense data */
				STbp->buffer_bytes = 0;
		पूर्ण
		/* End of extended sense test */
		अन्यथा अणु		/* Non-extended sense */
			retval = STbp->syscall_result;
		पूर्ण

	पूर्ण
	/* End of error handling */
	अन्यथा अणु			/* Read successful */
		STbp->buffer_bytes = bytes;
		अगर (STp->sili) /* In fixed block mode residual is always zero here */
			STbp->buffer_bytes -= STp->buffer->cmdstat.residual;
	पूर्ण

	अगर (STps->drv_block >= 0) अणु
		अगर (STp->block_size == 0)
			STps->drv_block++;
		अन्यथा
			STps->drv_block += STbp->buffer_bytes / STp->block_size;
	पूर्ण
	वापस retval;
पूर्ण


/* Read command */
अटल sमाप_प्रकार
st_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count, loff_t * ppos)
अणु
	sमाप_प्रकार total;
	sमाप_प्रकार retval = 0;
	sमाप_प्रकार i, transfer;
	पूर्णांक special, करो_dio = 0;
	काष्ठा st_request *SRpnt = शून्य;
	काष्ठा scsi_tape *STp = filp->निजी_data;
	काष्ठा st_modedef *STm;
	काष्ठा st_partstat *STps;
	काष्ठा st_buffer *STbp = STp->buffer;

	अगर (mutex_lock_पूर्णांकerruptible(&STp->lock))
		वापस -ERESTARTSYS;

	retval = rw_checks(STp, filp, count);
	अगर (retval || count == 0)
		जाओ out;

	STm = &(STp->modes[STp->current_mode]);
	अगर (STp->block_size != 0 && (count % STp->block_size) != 0) अणु
		अगर (!STm->करो_पढ़ो_ahead) अणु
			retval = (-EINVAL);	/* Read must be पूर्णांकegral number of blocks */
			जाओ out;
		पूर्ण
		STp->try_dio_now = 0;  /* Direct i/o can't handle split blocks */
	पूर्ण

	STps = &(STp->ps[STp->partition]);
	अगर (STps->rw == ST_WRITING) अणु
		retval = flush_buffer(STp, 0);
		अगर (retval)
			जाओ out;
		STps->rw = ST_READING;
	पूर्ण
	DEB(
	अगर (debugging && STps->eof != ST_NOखातापूर्ण)
		st_prपूर्णांकk(ST_DEB_MSG, STp,
			  "EOF/EOM flag up (%d). Bytes %d\n",
			  STps->eof, STbp->buffer_bytes);
	) /* end DEB */

	retval = setup_buffering(STp, buf, count, 1);
	अगर (retval)
		जाओ out;
	करो_dio = STbp->करो_dio;

	अगर (STbp->buffer_bytes == 0 &&
	    STps->eof >= ST_EOD_1) अणु
		अगर (STps->eof < ST_EOD) अणु
			STps->eof += 1;
			retval = 0;
			जाओ out;
		पूर्ण
		retval = (-EIO);	/* EOM or Blank Check */
		जाओ out;
	पूर्ण

	अगर (करो_dio) अणु
		/* Check the buffer writability beक्रमe any tape movement. Don't alter
		   buffer data. */
		अगर (copy_from_user(&i, buf, 1) != 0 ||
		    copy_to_user(buf, &i, 1) != 0 ||
		    copy_from_user(&i, buf + count - 1, 1) != 0 ||
		    copy_to_user(buf + count - 1, &i, 1) != 0) अणु
			retval = (-EFAULT);
			जाओ out;
		पूर्ण
	पूर्ण

	STps->rw = ST_READING;


	/* Loop until enough data in buffer or a special condition found */
	क्रम (total = 0, special = 0; total < count && !special;) अणु

		/* Get new data अगर the buffer is empty */
		अगर (STbp->buffer_bytes == 0) अणु
			special = पढ़ो_tape(STp, count - total, &SRpnt);
			अगर (special < 0) अणु	/* No need to जारी पढ़ो */
				retval = special;
				जाओ out;
			पूर्ण
		पूर्ण

		/* Move the data from driver buffer to user buffer */
		अगर (STbp->buffer_bytes > 0) अणु
			DEB(
			अगर (debugging && STps->eof != ST_NOखातापूर्ण)
				st_prपूर्णांकk(ST_DEB_MSG, STp,
					  "EOF up (%d). Left %d, needed %d.\n",
					  STps->eof, STbp->buffer_bytes,
					  (पूर्णांक)(count - total));
			) /* end DEB */
			transfer = STbp->buffer_bytes < count - total ?
			    STbp->buffer_bytes : count - total;
			अगर (!करो_dio) अणु
				i = from_buffer(STbp, buf, transfer);
				अगर (i) अणु
					retval = i;
					जाओ out;
				पूर्ण
			पूर्ण
			buf += transfer;
			total += transfer;
		पूर्ण

		अगर (STp->block_size == 0)
			अवरोध;	/* Read only one variable length block */

	पूर्ण			/* क्रम (total = 0, special = 0;
                                   total < count && !special; ) */

	/* Change the eof state अगर no data from tape or buffer */
	अगर (total == 0) अणु
		अगर (STps->eof == ST_FM_HIT) अणु
			STps->eof = ST_FM;
			STps->drv_block = 0;
			अगर (STps->drv_file >= 0)
				STps->drv_file++;
		पूर्ण अन्यथा अगर (STps->eof == ST_EOD_1) अणु
			STps->eof = ST_EOD_2;
			STps->drv_block = 0;
			अगर (STps->drv_file >= 0)
				STps->drv_file++;
		पूर्ण अन्यथा अगर (STps->eof == ST_EOD_2)
			STps->eof = ST_EOD;
	पूर्ण अन्यथा अगर (STps->eof == ST_FM)
		STps->eof = ST_NOखातापूर्ण;
	retval = total;

 out:
	अगर (SRpnt != शून्य) अणु
		st_release_request(SRpnt);
		SRpnt = शून्य;
	पूर्ण
	अगर (करो_dio) अणु
		release_buffering(STp, 1);
		STbp->buffer_bytes = 0;
	पूर्ण
	mutex_unlock(&STp->lock);

	वापस retval;
पूर्ण



DEB(
/* Set the driver options */
अटल व्योम st_log_options(काष्ठा scsi_tape * STp, काष्ठा st_modedef * STm)
अणु
	अगर (debugging) अणु
		st_prपूर्णांकk(KERN_INFO, STp,
			  "Mode %d options: buffer writes: %d, "
			  "async writes: %d, read ahead: %d\n",
			  STp->current_mode, STm->करो_buffer_ग_लिखोs,
			  STm->करो_async_ग_लिखोs, STm->करो_पढ़ो_ahead);
		st_prपूर्णांकk(KERN_INFO, STp,
			  "    can bsr: %d, two FMs: %d, "
			  "fast mteom: %d, auto lock: %d,\n",
			  STp->can_bsr, STp->two_fm, STp->fast_mteom,
			  STp->करो_स्वतः_lock);
		st_prपूर्णांकk(KERN_INFO, STp,
			  "    defs for wr: %d, no block limits: %d, "
			  "partitions: %d, s2 log: %d\n",
			  STm->शेषs_क्रम_ग_लिखोs, STp->omit_blklims,
			  STp->can_partitions, STp->scsi2_logical);
		st_prपूर्णांकk(KERN_INFO, STp,
			  "    sysv: %d nowait: %d sili: %d "
			  "nowait_filemark: %d\n",
			  STm->sysv, STp->immediate, STp->sili,
			  STp->immediate_filemark);
		st_prपूर्णांकk(KERN_INFO, STp, "    debugging: %d\n", debugging);
	पूर्ण
पूर्ण
	)


अटल पूर्णांक st_set_options(काष्ठा scsi_tape *STp, दीर्घ options)
अणु
	पूर्णांक value;
	दीर्घ code;
	काष्ठा st_modedef *STm;
	काष्ठा cdev *cd0, *cd1;
	काष्ठा device *d0, *d1;

	STm = &(STp->modes[STp->current_mode]);
	अगर (!STm->defined) अणु
		cd0 = STm->cdevs[0];
		cd1 = STm->cdevs[1];
		d0  = STm->devs[0];
		d1  = STm->devs[1];
		स_नकल(STm, &(STp->modes[0]), माप(काष्ठा st_modedef));
		STm->cdevs[0] = cd0;
		STm->cdevs[1] = cd1;
		STm->devs[0]  = d0;
		STm->devs[1]  = d1;
		modes_defined = 1;
		DEBC_prपूर्णांकk(STp, "Initialized mode %d definition from mode 0\n",
			    STp->current_mode);
	पूर्ण

	code = options & MT_ST_OPTIONS;
	अगर (code == MT_ST_BOOLEANS) अणु
		STm->करो_buffer_ग_लिखोs = (options & MT_ST_BUFFER_WRITES) != 0;
		STm->करो_async_ग_लिखोs = (options & MT_ST_ASYNC_WRITES) != 0;
		STm->शेषs_क्रम_ग_लिखोs = (options & MT_ST_DEF_WRITES) != 0;
		STm->करो_पढ़ो_ahead = (options & MT_ST_READ_AHEAD) != 0;
		STp->two_fm = (options & MT_ST_TWO_FM) != 0;
		STp->fast_mteom = (options & MT_ST_FAST_MTEOM) != 0;
		STp->करो_स्वतः_lock = (options & MT_ST_AUTO_LOCK) != 0;
		STp->can_bsr = (options & MT_ST_CAN_BSR) != 0;
		STp->omit_blklims = (options & MT_ST_NO_BLKLIMS) != 0;
		अगर ((STp->device)->scsi_level >= SCSI_2)
			STp->can_partitions = (options & MT_ST_CAN_PARTITIONS) != 0;
		STp->scsi2_logical = (options & MT_ST_SCSI2LOGICAL) != 0;
		STp->immediate = (options & MT_ST_NOWAIT) != 0;
		STp->immediate_filemark = (options & MT_ST_NOWAIT_खातापूर्ण) != 0;
		STm->sysv = (options & MT_ST_SYSV) != 0;
		STp->sili = (options & MT_ST_SILI) != 0;
		DEB( debugging = (options & MT_ST_DEBUGGING) != 0;
		     st_log_options(STp, STm); )
	पूर्ण अन्यथा अगर (code == MT_ST_SETBOOLEANS || code == MT_ST_CLEARBOOLEANS) अणु
		value = (code == MT_ST_SETBOOLEANS);
		अगर ((options & MT_ST_BUFFER_WRITES) != 0)
			STm->करो_buffer_ग_लिखोs = value;
		अगर ((options & MT_ST_ASYNC_WRITES) != 0)
			STm->करो_async_ग_लिखोs = value;
		अगर ((options & MT_ST_DEF_WRITES) != 0)
			STm->शेषs_क्रम_ग_लिखोs = value;
		अगर ((options & MT_ST_READ_AHEAD) != 0)
			STm->करो_पढ़ो_ahead = value;
		अगर ((options & MT_ST_TWO_FM) != 0)
			STp->two_fm = value;
		अगर ((options & MT_ST_FAST_MTEOM) != 0)
			STp->fast_mteom = value;
		अगर ((options & MT_ST_AUTO_LOCK) != 0)
			STp->करो_स्वतः_lock = value;
		अगर ((options & MT_ST_CAN_BSR) != 0)
			STp->can_bsr = value;
		अगर ((options & MT_ST_NO_BLKLIMS) != 0)
			STp->omit_blklims = value;
		अगर ((STp->device)->scsi_level >= SCSI_2 &&
		    (options & MT_ST_CAN_PARTITIONS) != 0)
			STp->can_partitions = value;
		अगर ((options & MT_ST_SCSI2LOGICAL) != 0)
			STp->scsi2_logical = value;
		अगर ((options & MT_ST_NOWAIT) != 0)
			STp->immediate = value;
		अगर ((options & MT_ST_NOWAIT_खातापूर्ण) != 0)
			STp->immediate_filemark = value;
		अगर ((options & MT_ST_SYSV) != 0)
			STm->sysv = value;
		अगर ((options & MT_ST_SILI) != 0)
			STp->sili = value;
		DEB(
		अगर ((options & MT_ST_DEBUGGING) != 0)
			debugging = value;
			st_log_options(STp, STm); )
	पूर्ण अन्यथा अगर (code == MT_ST_WRITE_THRESHOLD) अणु
		/* Retained क्रम compatibility */
	पूर्ण अन्यथा अगर (code == MT_ST_DEF_BLKSIZE) अणु
		value = (options & ~MT_ST_OPTIONS);
		अगर (value == ~MT_ST_OPTIONS) अणु
			STm->शेष_blksize = (-1);
			DEBC_prपूर्णांकk(STp, "Default block size disabled.\n");
		पूर्ण अन्यथा अणु
			STm->शेष_blksize = value;
			DEBC_prपूर्णांकk(STp,"Default block size set to "
				    "%d bytes.\n", STm->शेष_blksize);
			अगर (STp->पढ़ोy == ST_READY) अणु
				STp->blksize_changed = 0;
				set_mode_densblk(STp, STm);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (code == MT_ST_TIMEOUTS) अणु
		value = (options & ~MT_ST_OPTIONS);
		अगर ((value & MT_ST_SET_LONG_TIMEOUT) != 0) अणु
			STp->दीर्घ_समयout = (value & ~MT_ST_SET_LONG_TIMEOUT) * HZ;
			DEBC_prपूर्णांकk(STp, "Long timeout set to %d seconds.\n",
				    (value & ~MT_ST_SET_LONG_TIMEOUT));
		पूर्ण अन्यथा अणु
			blk_queue_rq_समयout(STp->device->request_queue,
					     value * HZ);
			DEBC_prपूर्णांकk(STp, "Normal timeout set to %d seconds.\n",
				    value);
		पूर्ण
	पूर्ण अन्यथा अगर (code == MT_ST_SET_CLN) अणु
		value = (options & ~MT_ST_OPTIONS) & 0xff;
		अगर (value != 0 &&
			(value < EXTENDED_SENSE_START ||
				value >= SCSI_SENSE_BUFFERSIZE))
			वापस (-EINVAL);
		STp->cln_mode = value;
		STp->cln_sense_mask = (options >> 8) & 0xff;
		STp->cln_sense_value = (options >> 16) & 0xff;
		st_prपूर्णांकk(KERN_INFO, STp,
			  "Cleaning request mode %d, mask %02x, value %02x\n",
			  value, STp->cln_sense_mask, STp->cln_sense_value);
	पूर्ण अन्यथा अगर (code == MT_ST_DEF_OPTIONS) अणु
		code = (options & ~MT_ST_CLEAR_DEFAULT);
		value = (options & MT_ST_CLEAR_DEFAULT);
		अगर (code == MT_ST_DEF_DENSITY) अणु
			अगर (value == MT_ST_CLEAR_DEFAULT) अणु
				STm->शेष_density = (-1);
				DEBC_prपूर्णांकk(STp,
					    "Density default disabled.\n");
			पूर्ण अन्यथा अणु
				STm->शेष_density = value & 0xff;
				DEBC_prपूर्णांकk(STp, "Density default set to %x\n",
					    STm->शेष_density);
				अगर (STp->पढ़ोy == ST_READY) अणु
					STp->density_changed = 0;
					set_mode_densblk(STp, STm);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (code == MT_ST_DEF_DRVBUFFER) अणु
			अगर (value == MT_ST_CLEAR_DEFAULT) अणु
				STp->शेष_drvbuffer = 0xff;
				DEBC_prपूर्णांकk(STp,
					    "Drive buffer default disabled.\n");
			पूर्ण अन्यथा अणु
				STp->शेष_drvbuffer = value & 7;
				DEBC_prपूर्णांकk(STp,
					    "Drive buffer default set to %x\n",
					    STp->शेष_drvbuffer);
				अगर (STp->पढ़ोy == ST_READY)
					st_पूर्णांक_ioctl(STp, MTSETDRVBUFFER, STp->शेष_drvbuffer);
			पूर्ण
		पूर्ण अन्यथा अगर (code == MT_ST_DEF_COMPRESSION) अणु
			अगर (value == MT_ST_CLEAR_DEFAULT) अणु
				STm->शेष_compression = ST_DONT_TOUCH;
				DEBC_prपूर्णांकk(STp,
					    "Compression default disabled.\n");
			पूर्ण अन्यथा अणु
				अगर ((value & 0xff00) != 0) अणु
					STp->c_algo = (value & 0xff00) >> 8;
					DEBC_prपूर्णांकk(STp, "Compression "
						    "algorithm set to 0x%x.\n",
						    STp->c_algo);
				पूर्ण
				अगर ((value & 0xff) != 0xff) अणु
					STm->शेष_compression = (value & 1 ? ST_YES : ST_NO);
					DEBC_prपूर्णांकk(STp, "Compression default "
						    "set to %x\n",
						    (value & 1));
					अगर (STp->पढ़ोy == ST_READY) अणु
						STp->compression_changed = 0;
						st_compression(STp, (STm->शेष_compression == ST_YES));
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		वापस (-EIO);

	वापस 0;
पूर्ण

#घोषणा MODE_HEADER_LENGTH  4

/* Mode header and page byte offsets */
#घोषणा MH_OFF_DATA_LENGTH     0
#घोषणा MH_OFF_MEDIUM_TYPE     1
#घोषणा MH_OFF_DEV_SPECIFIC    2
#घोषणा MH_OFF_BDESCS_LENGTH   3
#घोषणा MP_OFF_PAGE_NBR        0
#घोषणा MP_OFF_PAGE_LENGTH     1

/* Mode header and page bit masks */
#घोषणा MH_BIT_WP              0x80
#घोषणा MP_MSK_PAGE_NBR        0x3f

/* Don't वापस block descriptors */
#घोषणा MODE_SENSE_OMIT_BDESCS 0x08

#घोषणा MODE_SELECT_PAGE_FORMAT 0x10

/* Read a mode page पूर्णांकo the tape buffer. The block descriptors are included
   अगर incl_block_descs is true. The page control is ored to the page number
   parameter, अगर necessary. */
अटल पूर्णांक पढ़ो_mode_page(काष्ठा scsi_tape *STp, पूर्णांक page, पूर्णांक omit_block_descs)
अणु
	अचिन्हित अक्षर cmd[MAX_COMMAND_SIZE];
	काष्ठा st_request *SRpnt;

	स_रखो(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = MODE_SENSE;
	अगर (omit_block_descs)
		cmd[1] = MODE_SENSE_OMIT_BDESCS;
	cmd[2] = page;
	cmd[4] = 255;

	SRpnt = st_करो_scsi(शून्य, STp, cmd, cmd[4], DMA_FROM_DEVICE,
			   STp->device->request_queue->rq_समयout, 0, 1);
	अगर (SRpnt == शून्य)
		वापस (STp->buffer)->syscall_result;

	st_release_request(SRpnt);

	वापस STp->buffer->syscall_result;
पूर्ण


/* Send the mode page in the tape buffer to the drive. Assumes that the mode data
   in the buffer is correctly क्रमmatted. The दीर्घ समयout is used अगर slow is non-zero. */
अटल पूर्णांक ग_लिखो_mode_page(काष्ठा scsi_tape *STp, पूर्णांक page, पूर्णांक slow)
अणु
	पूर्णांक pgo;
	अचिन्हित अक्षर cmd[MAX_COMMAND_SIZE];
	काष्ठा st_request *SRpnt;
	पूर्णांक समयout;

	स_रखो(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = MODE_SELECT;
	cmd[1] = MODE_SELECT_PAGE_FORMAT;
	pgo = MODE_HEADER_LENGTH + (STp->buffer)->b_data[MH_OFF_BDESCS_LENGTH];
	cmd[4] = pgo + (STp->buffer)->b_data[pgo + MP_OFF_PAGE_LENGTH] + 2;

	/* Clear reserved fields */
	(STp->buffer)->b_data[MH_OFF_DATA_LENGTH] = 0;
	(STp->buffer)->b_data[MH_OFF_MEDIUM_TYPE] = 0;
	(STp->buffer)->b_data[MH_OFF_DEV_SPECIFIC] &= ~MH_BIT_WP;
	(STp->buffer)->b_data[pgo + MP_OFF_PAGE_NBR] &= MP_MSK_PAGE_NBR;

	समयout = slow ?
		STp->दीर्घ_समयout : STp->device->request_queue->rq_समयout;
	SRpnt = st_करो_scsi(शून्य, STp, cmd, cmd[4], DMA_TO_DEVICE,
			   समयout, 0, 1);
	अगर (SRpnt == शून्य)
		वापस (STp->buffer)->syscall_result;

	st_release_request(SRpnt);

	वापस STp->buffer->syscall_result;
पूर्ण


#घोषणा COMPRESSION_PAGE        0x0f
#घोषणा COMPRESSION_PAGE_LENGTH 16

#घोषणा CP_OFF_DCE_DCC          2
#घोषणा CP_OFF_C_ALGO           7

#घोषणा DCE_MASK  0x80
#घोषणा DCC_MASK  0x40
#घोषणा RED_MASK  0x60


/* Control the compression with mode page 15. Algorithm not changed अगर zero.

   The block descriptors are पढ़ो and written because Sony SDT-7000 करोes not
   work without this (suggestion from Michael Schaefer <Michael.Schaefer@dlr.de>).
   Including block descriptors should not cause any harm to other drives. */

अटल पूर्णांक st_compression(काष्ठा scsi_tape * STp, पूर्णांक state)
अणु
	पूर्णांक retval;
	पूर्णांक mpoffs;  /* Offset to mode page start */
	अचिन्हित अक्षर *b_data = (STp->buffer)->b_data;

	अगर (STp->पढ़ोy != ST_READY)
		वापस (-EIO);

	/* Read the current page contents */
	retval = पढ़ो_mode_page(STp, COMPRESSION_PAGE, 0);
	अगर (retval) अणु
		DEBC_prपूर्णांकk(STp, "Compression mode page not supported.\n");
		वापस (-EIO);
	पूर्ण

	mpoffs = MODE_HEADER_LENGTH + b_data[MH_OFF_BDESCS_LENGTH];
	DEBC_prपूर्णांकk(STp, "Compression state is %d.\n",
		    (b_data[mpoffs + CP_OFF_DCE_DCC] & DCE_MASK ? 1 : 0));

	/* Check अगर compression can be changed */
	अगर ((b_data[mpoffs + CP_OFF_DCE_DCC] & DCC_MASK) == 0) अणु
		DEBC_prपूर्णांकk(STp, "Compression not supported.\n");
		वापस (-EIO);
	पूर्ण

	/* Do the change */
	अगर (state) अणु
		b_data[mpoffs + CP_OFF_DCE_DCC] |= DCE_MASK;
		अगर (STp->c_algo != 0)
			b_data[mpoffs + CP_OFF_C_ALGO] = STp->c_algo;
	पूर्ण
	अन्यथा अणु
		b_data[mpoffs + CP_OFF_DCE_DCC] &= ~DCE_MASK;
		अगर (STp->c_algo != 0)
			b_data[mpoffs + CP_OFF_C_ALGO] = 0; /* no compression */
	पूर्ण

	retval = ग_लिखो_mode_page(STp, COMPRESSION_PAGE, 0);
	अगर (retval) अणु
		DEBC_prपूर्णांकk(STp, "Compression change failed.\n");
		वापस (-EIO);
	पूर्ण
	DEBC_prपूर्णांकk(STp, "Compression state changed to %d.\n", state);

	STp->compression_changed = 1;
	वापस 0;
पूर्ण


/* Process the load and unload commands (करोes unload अगर the load code is zero) */
अटल पूर्णांक करो_load_unload(काष्ठा scsi_tape *STp, काष्ठा file *filp, पूर्णांक load_code)
अणु
	पूर्णांक retval = (-EIO), समयout;
	अचिन्हित अक्षर cmd[MAX_COMMAND_SIZE];
	काष्ठा st_partstat *STps;
	काष्ठा st_request *SRpnt;

	अगर (STp->पढ़ोy != ST_READY && !load_code) अणु
		अगर (STp->पढ़ोy == ST_NO_TAPE)
			वापस (-ENOMEDIUM);
		अन्यथा
			वापस (-EIO);
	पूर्ण

	स_रखो(cmd, 0, MAX_COMMAND_SIZE);
	cmd[0] = START_STOP;
	अगर (load_code)
		cmd[4] |= 1;
	/*
	 * If arg >= 1 && arg <= 6 Enhanced load/unload in HP C1553A
	 */
	अगर (load_code >= 1 + MT_ST_HPLOADER_OFFSET
	    && load_code <= 6 + MT_ST_HPLOADER_OFFSET) अणु
		DEBC_prपूर्णांकk(STp, " Enhanced %sload slot %2d.\n",
			    (cmd[4]) ? "" : "un",
			    load_code - MT_ST_HPLOADER_OFFSET);
		cmd[3] = load_code - MT_ST_HPLOADER_OFFSET; /* MediaID field of C1553A */
	पूर्ण
	अगर (STp->immediate) अणु
		cmd[1] = 1;	/* Don't रुको क्रम completion */
		समयout = STp->device->request_queue->rq_समयout;
	पूर्ण
	अन्यथा
		समयout = STp->दीर्घ_समयout;

	DEBC(
		अगर (!load_code)
			st_prपूर्णांकk(ST_DEB_MSG, STp, "Unloading tape.\n");
		अन्यथा
			st_prपूर्णांकk(ST_DEB_MSG, STp, "Loading tape.\n");
		);

	SRpnt = st_करो_scsi(शून्य, STp, cmd, 0, DMA_NONE,
			   समयout, MAX_RETRIES, 1);
	अगर (!SRpnt)
		वापस (STp->buffer)->syscall_result;

	retval = (STp->buffer)->syscall_result;
	st_release_request(SRpnt);

	अगर (!retval) अणु	/* SCSI command successful */

		अगर (!load_code) अणु
			STp->rew_at_बंद = 0;
			STp->पढ़ोy = ST_NO_TAPE;
		पूर्ण
		अन्यथा अणु
			STp->rew_at_बंद = STp->स्वतःrew_dev;
			retval = check_tape(STp, filp);
			अगर (retval > 0)
				retval = 0;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		STps = &(STp->ps[STp->partition]);
		STps->drv_file = STps->drv_block = (-1);
	पूर्ण

	वापस retval;
पूर्ण

#अगर DEBUG
#घोषणा ST_DEB_FORWARD  0
#घोषणा ST_DEB_BACKWARD 1
अटल व्योम deb_space_prपूर्णांक(काष्ठा scsi_tape *STp, पूर्णांक direction, अक्षर *units, अचिन्हित अक्षर *cmd)
अणु
	s32 sc;

	अगर (!debugging)
		वापस;

	sc = sign_extend32(get_unaligned_be24(&cmd[2]), 23);
	अगर (direction)
		sc = -sc;
	st_prपूर्णांकk(ST_DEB_MSG, STp, "Spacing tape %s over %d %s.\n",
		  direction ? "backward" : "forward", sc, units);
पूर्ण
#अन्यथा
#घोषणा ST_DEB_FORWARD  0
#घोषणा ST_DEB_BACKWARD 1
अटल व्योम deb_space_prपूर्णांक(काष्ठा scsi_tape *STp, पूर्णांक direction, अक्षर *units, अचिन्हित अक्षर *cmd) अणुपूर्ण
#पूर्ण_अगर


/* Internal ioctl function */
अटल पूर्णांक st_पूर्णांक_ioctl(काष्ठा scsi_tape *STp, अचिन्हित पूर्णांक cmd_in, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक समयout;
	दीर्घ lपंचांगp;
	पूर्णांक ioctl_result;
	पूर्णांक chg_eof = 1;
	अचिन्हित अक्षर cmd[MAX_COMMAND_SIZE];
	काष्ठा st_request *SRpnt;
	काष्ठा st_partstat *STps;
	पूर्णांक fileno, blkno, at_sm, unकरोne;
	पूर्णांक datalen = 0, direction = DMA_NONE;

	WARN_ON(STp->buffer->करो_dio != 0);
	अगर (STp->पढ़ोy != ST_READY) अणु
		अगर (STp->पढ़ोy == ST_NO_TAPE)
			वापस (-ENOMEDIUM);
		अन्यथा
			वापस (-EIO);
	पूर्ण
	समयout = STp->दीर्घ_समयout;
	STps = &(STp->ps[STp->partition]);
	fileno = STps->drv_file;
	blkno = STps->drv_block;
	at_sm = STps->at_sm;

	स_रखो(cmd, 0, MAX_COMMAND_SIZE);
	चयन (cmd_in) अणु
	हाल MTFSFM:
		chg_eof = 0;	/* Changed from the FSF after this */
		fallthrough;
	हाल MTFSF:
		cmd[0] = SPACE;
		cmd[1] = 0x01;	/* Space FileMarks */
		cmd[2] = (arg >> 16);
		cmd[3] = (arg >> 8);
		cmd[4] = arg;
		deb_space_prपूर्णांक(STp, ST_DEB_FORWARD, "filemarks", cmd);
		अगर (fileno >= 0)
			fileno += arg;
		blkno = 0;
		at_sm &= (arg == 0);
		अवरोध;
	हाल MTBSFM:
		chg_eof = 0;	/* Changed from the FSF after this */
		fallthrough;
	हाल MTBSF:
		cmd[0] = SPACE;
		cmd[1] = 0x01;	/* Space FileMarks */
		lपंचांगp = (-arg);
		cmd[2] = (lपंचांगp >> 16);
		cmd[3] = (lपंचांगp >> 8);
		cmd[4] = lपंचांगp;
		deb_space_prपूर्णांक(STp, ST_DEB_BACKWARD, "filemarks", cmd);
		अगर (fileno >= 0)
			fileno -= arg;
		blkno = (-1);	/* We can't know the block number */
		at_sm &= (arg == 0);
		अवरोध;
	हाल MTFSR:
		cmd[0] = SPACE;
		cmd[1] = 0x00;	/* Space Blocks */
		cmd[2] = (arg >> 16);
		cmd[3] = (arg >> 8);
		cmd[4] = arg;
		deb_space_prपूर्णांक(STp, ST_DEB_FORWARD, "blocks", cmd);
		अगर (blkno >= 0)
			blkno += arg;
		at_sm &= (arg == 0);
		अवरोध;
	हाल MTBSR:
		cmd[0] = SPACE;
		cmd[1] = 0x00;	/* Space Blocks */
		lपंचांगp = (-arg);
		cmd[2] = (lपंचांगp >> 16);
		cmd[3] = (lपंचांगp >> 8);
		cmd[4] = lपंचांगp;
		deb_space_prपूर्णांक(STp, ST_DEB_BACKWARD, "blocks", cmd);
		अगर (blkno >= 0)
			blkno -= arg;
		at_sm &= (arg == 0);
		अवरोध;
	हाल MTFSS:
		cmd[0] = SPACE;
		cmd[1] = 0x04;	/* Space Seपंचांगarks */
		cmd[2] = (arg >> 16);
		cmd[3] = (arg >> 8);
		cmd[4] = arg;
		deb_space_prपूर्णांक(STp, ST_DEB_FORWARD, "setmarks", cmd);
		अगर (arg != 0) अणु
			blkno = fileno = (-1);
			at_sm = 1;
		पूर्ण
		अवरोध;
	हाल MTBSS:
		cmd[0] = SPACE;
		cmd[1] = 0x04;	/* Space Seपंचांगarks */
		lपंचांगp = (-arg);
		cmd[2] = (lपंचांगp >> 16);
		cmd[3] = (lपंचांगp >> 8);
		cmd[4] = lपंचांगp;
		deb_space_prपूर्णांक(STp, ST_DEB_BACKWARD, "setmarks", cmd);
		अगर (arg != 0) अणु
			blkno = fileno = (-1);
			at_sm = 1;
		पूर्ण
		अवरोध;
	हाल MTWखातापूर्ण:
	हाल MTWखातापूर्णI:
	हाल MTWSM:
		अगर (STp->ग_लिखो_prot)
			वापस (-EACCES);
		cmd[0] = WRITE_खाताMARKS;
		अगर (cmd_in == MTWSM)
			cmd[1] = 2;
		अगर (cmd_in == MTWखातापूर्णI ||
		    (cmd_in == MTWखातापूर्ण && STp->immediate_filemark))
			cmd[1] |= 1;
		cmd[2] = (arg >> 16);
		cmd[3] = (arg >> 8);
		cmd[4] = arg;
		समयout = STp->device->request_queue->rq_समयout;
		DEBC(
			अगर (cmd_in != MTWSM)
				st_prपूर्णांकk(ST_DEB_MSG, STp,
					  "Writing %d filemarks.\n",
					  cmd[2] * 65536 +
					  cmd[3] * 256 +
					  cmd[4]);
			अन्यथा
				st_prपूर्णांकk(ST_DEB_MSG, STp,
					  "Writing %d setmarks.\n",
					  cmd[2] * 65536 +
					  cmd[3] * 256 +
					  cmd[4]);
		)
		अगर (fileno >= 0)
			fileno += arg;
		blkno = 0;
		at_sm = (cmd_in == MTWSM);
		अवरोध;
	हाल MTREW:
		cmd[0] = REZERO_UNIT;
		अगर (STp->immediate) अणु
			cmd[1] = 1;	/* Don't रुको क्रम completion */
			समयout = STp->device->request_queue->rq_समयout;
		पूर्ण
		DEBC_prपूर्णांकk(STp, "Rewinding tape.\n");
		fileno = blkno = at_sm = 0;
		अवरोध;
	हाल MTNOP:
		DEBC_prपूर्णांकk(STp, "No op on tape.\n");
		वापस 0;	/* Should करो something ? */
	हाल MTRETEN:
		cmd[0] = START_STOP;
		अगर (STp->immediate) अणु
			cmd[1] = 1;	/* Don't रुको क्रम completion */
			समयout = STp->device->request_queue->rq_समयout;
		पूर्ण
		cmd[4] = 3;
		DEBC_prपूर्णांकk(STp, "Retensioning tape.\n");
		fileno = blkno = at_sm = 0;
		अवरोध;
	हाल MTEOM:
		अगर (!STp->fast_mteom) अणु
			/* space to the end of tape */
			ioctl_result = st_पूर्णांक_ioctl(STp, MTFSF, 0x7fffff);
			fileno = STps->drv_file;
			अगर (STps->eof >= ST_EOD_1)
				वापस 0;
			/* The next lines would hide the number of spaced FileMarks
			   That's why I inserted the previous lines. I had no luck
			   with detecting EOM with FSF, so we go now to EOM.
			   Joerg Weule */
		पूर्ण अन्यथा
			fileno = (-1);
		cmd[0] = SPACE;
		cmd[1] = 3;
		DEBC_prपूर्णांकk(STp, "Spacing to end of recorded medium.\n");
		blkno = -1;
		at_sm = 0;
		अवरोध;
	हाल MTERASE:
		अगर (STp->ग_लिखो_prot)
			वापस (-EACCES);
		cmd[0] = ERASE;
		cmd[1] = (arg ? 1 : 0);	/* Long erase with non-zero argument */
		अगर (STp->immediate) अणु
			cmd[1] |= 2;	/* Don't रुको क्रम completion */
			समयout = STp->device->request_queue->rq_समयout;
		पूर्ण
		अन्यथा
			समयout = STp->दीर्घ_समयout * 8;

		DEBC_prपूर्णांकk(STp, "Erasing tape.\n");
		fileno = blkno = at_sm = 0;
		अवरोध;
	हाल MTSETBLK:		/* Set block length */
	हाल MTSETDENSITY:	/* Set tape density */
	हाल MTSETDRVBUFFER:	/* Set drive buffering */
	हाल SET_DENS_AND_BLK:	/* Set density and block size */
		chg_eof = 0;
		अगर (STp->dirty || (STp->buffer)->buffer_bytes != 0)
			वापस (-EIO);	/* Not allowed अगर data in buffer */
		अगर ((cmd_in == MTSETBLK || cmd_in == SET_DENS_AND_BLK) &&
		    (arg & MT_ST_BLKSIZE_MASK) != 0 &&
		    STp->max_block > 0 &&
		    ((arg & MT_ST_BLKSIZE_MASK) < STp->min_block ||
		     (arg & MT_ST_BLKSIZE_MASK) > STp->max_block)) अणु
			st_prपूर्णांकk(KERN_WARNING, STp, "Illegal block size.\n");
			वापस (-EINVAL);
		पूर्ण
		cmd[0] = MODE_SELECT;
		अगर ((STp->use_pf & USE_PF))
			cmd[1] = MODE_SELECT_PAGE_FORMAT;
		cmd[4] = datalen = 12;
		direction = DMA_TO_DEVICE;

		स_रखो((STp->buffer)->b_data, 0, 12);
		अगर (cmd_in == MTSETDRVBUFFER)
			(STp->buffer)->b_data[2] = (arg & 7) << 4;
		अन्यथा
			(STp->buffer)->b_data[2] =
			    STp->drv_buffer << 4;
		(STp->buffer)->b_data[3] = 8;	/* block descriptor length */
		अगर (cmd_in == MTSETDENSITY) अणु
			(STp->buffer)->b_data[4] = arg;
			STp->density_changed = 1;	/* At least we tried ;-) */
		पूर्ण अन्यथा अगर (cmd_in == SET_DENS_AND_BLK)
			(STp->buffer)->b_data[4] = arg >> 24;
		अन्यथा
			(STp->buffer)->b_data[4] = STp->density;
		अगर (cmd_in == MTSETBLK || cmd_in == SET_DENS_AND_BLK) अणु
			lपंचांगp = arg & MT_ST_BLKSIZE_MASK;
			अगर (cmd_in == MTSETBLK)
				STp->blksize_changed = 1; /* At least we tried ;-) */
		पूर्ण अन्यथा
			lपंचांगp = STp->block_size;
		(STp->buffer)->b_data[9] = (lपंचांगp >> 16);
		(STp->buffer)->b_data[10] = (lपंचांगp >> 8);
		(STp->buffer)->b_data[11] = lपंचांगp;
		समयout = STp->device->request_queue->rq_समयout;
		DEBC(
			अगर (cmd_in == MTSETBLK || cmd_in == SET_DENS_AND_BLK)
				st_prपूर्णांकk(ST_DEB_MSG, STp,
					  "Setting block size to %d bytes.\n",
					  (STp->buffer)->b_data[9] * 65536 +
					  (STp->buffer)->b_data[10] * 256 +
					  (STp->buffer)->b_data[11]);
			अगर (cmd_in == MTSETDENSITY || cmd_in == SET_DENS_AND_BLK)
				st_prपूर्णांकk(ST_DEB_MSG, STp,
					  "Setting density code to %x.\n",
					  (STp->buffer)->b_data[4]);
			अगर (cmd_in == MTSETDRVBUFFER)
				st_prपूर्णांकk(ST_DEB_MSG, STp,
					  "Setting drive buffer code to %d.\n",
					  ((STp->buffer)->b_data[2] >> 4) & 7);
		)
		अवरोध;
	शेष:
		वापस (-ENOSYS);
	पूर्ण

	SRpnt = st_करो_scsi(शून्य, STp, cmd, datalen, direction,
			   समयout, MAX_RETRIES, 1);
	अगर (!SRpnt)
		वापस (STp->buffer)->syscall_result;

	ioctl_result = (STp->buffer)->syscall_result;

	अगर (!ioctl_result) अणु	/* SCSI command successful */
		st_release_request(SRpnt);
		SRpnt = शून्य;
		STps->drv_block = blkno;
		STps->drv_file = fileno;
		STps->at_sm = at_sm;

		अगर (cmd_in == MTBSFM)
			ioctl_result = st_पूर्णांक_ioctl(STp, MTFSF, 1);
		अन्यथा अगर (cmd_in == MTFSFM)
			ioctl_result = st_पूर्णांक_ioctl(STp, MTBSF, 1);

		अगर (cmd_in == MTSETBLK || cmd_in == SET_DENS_AND_BLK) अणु
			STp->block_size = arg & MT_ST_BLKSIZE_MASK;
			अगर (STp->block_size != 0) अणु
				(STp->buffer)->buffer_blocks =
				    (STp->buffer)->buffer_size / STp->block_size;
			पूर्ण
			(STp->buffer)->buffer_bytes = (STp->buffer)->पढ़ो_poपूर्णांकer = 0;
			अगर (cmd_in == SET_DENS_AND_BLK)
				STp->density = arg >> MT_ST_DENSITY_SHIFT;
		पूर्ण अन्यथा अगर (cmd_in == MTSETDRVBUFFER)
			STp->drv_buffer = (arg & 7);
		अन्यथा अगर (cmd_in == MTSETDENSITY)
			STp->density = arg;

		अगर (cmd_in == MTEOM)
			STps->eof = ST_EOD;
		अन्यथा अगर (cmd_in == MTFSF)
			STps->eof = ST_FM;
		अन्यथा अगर (chg_eof)
			STps->eof = ST_NOखातापूर्ण;

		अगर (cmd_in == MTWखातापूर्ण || cmd_in == MTWखातापूर्णI)
			STps->rw = ST_IDLE;  /* prevent स्वतःmatic Wखातापूर्ण at बंद */
	पूर्ण अन्यथा अणु /* SCSI command was not completely successful. Don't वापस
                    from this block without releasing the SCSI command block! */
		काष्ठा st_cmdstatus *cmdstatp = &STp->buffer->cmdstat;

		अगर (cmdstatp->flags & SENSE_EOM) अणु
			अगर (cmd_in != MTBSF && cmd_in != MTBSFM &&
			    cmd_in != MTBSR && cmd_in != MTBSS)
				STps->eof = ST_EOM_OK;
			STps->drv_block = 0;
		पूर्ण

		अगर (cmdstatp->reमुख्यder_valid)
			unकरोne = (पूर्णांक)cmdstatp->ureमुख्यder64;
		अन्यथा
			unकरोne = 0;

		अगर ((cmd_in == MTWखातापूर्ण || cmd_in == MTWखातापूर्णI) &&
		    cmdstatp->have_sense &&
		    (cmdstatp->flags & SENSE_EOM)) अणु
			अगर (cmdstatp->sense_hdr.sense_key == NO_SENSE ||
			    cmdstatp->sense_hdr.sense_key == RECOVERED_ERROR) अणु
				ioctl_result = 0;	/* खातापूर्ण(s) written successfully at EOM */
				STps->eof = ST_NOखातापूर्ण;
			पूर्ण अन्यथा अणु  /* Writing खातापूर्ण(s) failed */
				अगर (fileno >= 0)
					fileno -= unकरोne;
				अगर (unकरोne < arg)
					STps->eof = ST_NOखातापूर्ण;
			पूर्ण
			STps->drv_file = fileno;
		पूर्ण अन्यथा अगर ((cmd_in == MTFSF) || (cmd_in == MTFSFM)) अणु
			अगर (fileno >= 0)
				STps->drv_file = fileno - unकरोne;
			अन्यथा
				STps->drv_file = fileno;
			STps->drv_block = -1;
			STps->eof = ST_NOखातापूर्ण;
		पूर्ण अन्यथा अगर ((cmd_in == MTBSF) || (cmd_in == MTBSFM)) अणु
			अगर (arg > 0 && unकरोne < 0)  /* Some drives get this wrong */
				unकरोne = (-unकरोne);
			अगर (STps->drv_file >= 0)
				STps->drv_file = fileno + unकरोne;
			STps->drv_block = 0;
			STps->eof = ST_NOखातापूर्ण;
		पूर्ण अन्यथा अगर (cmd_in == MTFSR) अणु
			अगर (cmdstatp->flags & SENSE_FMK) अणु	/* Hit filemark */
				अगर (STps->drv_file >= 0)
					STps->drv_file++;
				STps->drv_block = 0;
				STps->eof = ST_FM;
			पूर्ण अन्यथा अणु
				अगर (blkno >= unकरोne)
					STps->drv_block = blkno - unकरोne;
				अन्यथा
					STps->drv_block = (-1);
				STps->eof = ST_NOखातापूर्ण;
			पूर्ण
		पूर्ण अन्यथा अगर (cmd_in == MTBSR) अणु
			अगर (cmdstatp->flags & SENSE_FMK) अणु	/* Hit filemark */
				STps->drv_file--;
				STps->drv_block = (-1);
			पूर्ण अन्यथा अणु
				अगर (arg > 0 && unकरोne < 0)  /* Some drives get this wrong */
					unकरोne = (-unकरोne);
				अगर (STps->drv_block >= 0)
					STps->drv_block = blkno + unकरोne;
			पूर्ण
			STps->eof = ST_NOखातापूर्ण;
		पूर्ण अन्यथा अगर (cmd_in == MTEOM) अणु
			STps->drv_file = (-1);
			STps->drv_block = (-1);
			STps->eof = ST_EOD;
		पूर्ण अन्यथा अगर (cmd_in == MTSETBLK ||
			   cmd_in == MTSETDENSITY ||
			   cmd_in == MTSETDRVBUFFER ||
			   cmd_in == SET_DENS_AND_BLK) अणु
			अगर (cmdstatp->sense_hdr.sense_key == ILLEGAL_REQUEST &&
			    !(STp->use_pf & PF_TESTED)) अणु
				/* Try the other possible state of Page Format अगर not
				   alपढ़ोy tried */
				STp->use_pf = (STp->use_pf ^ USE_PF) | PF_TESTED;
				st_release_request(SRpnt);
				SRpnt = शून्य;
				वापस st_पूर्णांक_ioctl(STp, cmd_in, arg);
			पूर्ण
		पूर्ण अन्यथा अगर (chg_eof)
			STps->eof = ST_NOखातापूर्ण;

		अगर (cmdstatp->sense_hdr.sense_key == BLANK_CHECK)
			STps->eof = ST_EOD;

		st_release_request(SRpnt);
		SRpnt = शून्य;
	पूर्ण

	वापस ioctl_result;
पूर्ण


/* Get the tape position. If bt == 2, arg poपूर्णांकs पूर्णांकo a kernel space mt_loc
   काष्ठाure. */

अटल पूर्णांक get_location(काष्ठा scsi_tape *STp, अचिन्हित पूर्णांक *block, पूर्णांक *partition,
			पूर्णांक logical)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर scmd[MAX_COMMAND_SIZE];
	काष्ठा st_request *SRpnt;

	अगर (STp->पढ़ोy != ST_READY)
		वापस (-EIO);

	स_रखो(scmd, 0, MAX_COMMAND_SIZE);
	अगर ((STp->device)->scsi_level < SCSI_2) अणु
		scmd[0] = QFA_REQUEST_BLOCK;
		scmd[4] = 3;
	पूर्ण अन्यथा अणु
		scmd[0] = READ_POSITION;
		अगर (!logical && !STp->scsi2_logical)
			scmd[1] = 1;
	पूर्ण
	SRpnt = st_करो_scsi(शून्य, STp, scmd, 20, DMA_FROM_DEVICE,
			   STp->device->request_queue->rq_समयout,
			   MAX_READY_RETRIES, 1);
	अगर (!SRpnt)
		वापस (STp->buffer)->syscall_result;

	अगर ((STp->buffer)->syscall_result != 0 ||
	    (STp->device->scsi_level >= SCSI_2 &&
	     ((STp->buffer)->b_data[0] & 4) != 0)) अणु
		*block = *partition = 0;
		DEBC_prपूर्णांकk(STp, " Can't read tape position.\n");
		result = (-EIO);
	पूर्ण अन्यथा अणु
		result = 0;
		अगर ((STp->device)->scsi_level < SCSI_2) अणु
			*block = ((STp->buffer)->b_data[0] << 16)
			    + ((STp->buffer)->b_data[1] << 8)
			    + (STp->buffer)->b_data[2];
			*partition = 0;
		पूर्ण अन्यथा अणु
			*block = ((STp->buffer)->b_data[4] << 24)
			    + ((STp->buffer)->b_data[5] << 16)
			    + ((STp->buffer)->b_data[6] << 8)
			    + (STp->buffer)->b_data[7];
			*partition = (STp->buffer)->b_data[1];
			अगर (((STp->buffer)->b_data[0] & 0x80) &&
			    (STp->buffer)->b_data[1] == 0)	/* BOP of partition 0 */
				STp->ps[0].drv_block = STp->ps[0].drv_file = 0;
		पूर्ण
		DEBC_prपूर्णांकk(STp, "Got tape pos. blk %d part %d.\n",
			    *block, *partition);
	पूर्ण
	st_release_request(SRpnt);
	SRpnt = शून्य;

	वापस result;
पूर्ण


/* Set the tape block and partition. Negative partition means that only the
   block should be set in venकरोr specअगरic way. */
अटल पूर्णांक set_location(काष्ठा scsi_tape *STp, अचिन्हित पूर्णांक block, पूर्णांक partition,
			पूर्णांक logical)
अणु
	काष्ठा st_partstat *STps;
	पूर्णांक result, p;
	अचिन्हित पूर्णांक blk;
	पूर्णांक समयout;
	अचिन्हित अक्षर scmd[MAX_COMMAND_SIZE];
	काष्ठा st_request *SRpnt;

	अगर (STp->पढ़ोy != ST_READY)
		वापस (-EIO);
	समयout = STp->दीर्घ_समयout;
	STps = &(STp->ps[STp->partition]);

	DEBC_prपूर्णांकk(STp, "Setting block to %d and partition to %d.\n",
		    block, partition);
	DEB(अगर (partition < 0)
		वापस (-EIO); )

	/* Update the location at the partition we are leaving */
	अगर ((!STp->can_partitions && partition != 0) ||
	    partition >= ST_NBR_PARTITIONS)
		वापस (-EINVAL);
	अगर (partition != STp->partition) अणु
		अगर (get_location(STp, &blk, &p, 1))
			STps->last_block_valid = 0;
		अन्यथा अणु
			STps->last_block_valid = 1;
			STps->last_block_visited = blk;
			DEBC_prपूर्णांकk(STp, "Visited block %d for "
				    "partition %d saved.\n",
				    blk, STp->partition);
		पूर्ण
	पूर्ण

	स_रखो(scmd, 0, MAX_COMMAND_SIZE);
	अगर ((STp->device)->scsi_level < SCSI_2) अणु
		scmd[0] = QFA_SEEK_BLOCK;
		scmd[2] = (block >> 16);
		scmd[3] = (block >> 8);
		scmd[4] = block;
		scmd[5] = 0;
	पूर्ण अन्यथा अणु
		scmd[0] = SEEK_10;
		scmd[3] = (block >> 24);
		scmd[4] = (block >> 16);
		scmd[5] = (block >> 8);
		scmd[6] = block;
		अगर (!logical && !STp->scsi2_logical)
			scmd[1] = 4;
		अगर (STp->partition != partition) अणु
			scmd[1] |= 2;
			scmd[8] = partition;
			DEBC_prपूर्णांकk(STp, "Trying to change partition "
				    "from %d to %d\n", STp->partition,
				    partition);
		पूर्ण
	पूर्ण
	अगर (STp->immediate) अणु
		scmd[1] |= 1;		/* Don't रुको क्रम completion */
		समयout = STp->device->request_queue->rq_समयout;
	पूर्ण

	SRpnt = st_करो_scsi(शून्य, STp, scmd, 0, DMA_NONE,
			   समयout, MAX_READY_RETRIES, 1);
	अगर (!SRpnt)
		वापस (STp->buffer)->syscall_result;

	STps->drv_block = STps->drv_file = (-1);
	STps->eof = ST_NOखातापूर्ण;
	अगर ((STp->buffer)->syscall_result != 0) अणु
		result = (-EIO);
		अगर (STp->can_partitions &&
		    (STp->device)->scsi_level >= SCSI_2 &&
		    (p = find_partition(STp)) >= 0)
			STp->partition = p;
	पूर्ण अन्यथा अणु
		अगर (STp->can_partitions) अणु
			STp->partition = partition;
			STps = &(STp->ps[partition]);
			अगर (!STps->last_block_valid ||
			    STps->last_block_visited != block) अणु
				STps->at_sm = 0;
				STps->rw = ST_IDLE;
			पूर्ण
		पूर्ण अन्यथा
			STps->at_sm = 0;
		अगर (block == 0)
			STps->drv_block = STps->drv_file = 0;
		result = 0;
	पूर्ण

	st_release_request(SRpnt);
	SRpnt = शून्य;

	वापस result;
पूर्ण


/* Find the current partition number क्रम the drive status. Called from खोलो and
   वापसs either partition number of negative error code. */
अटल पूर्णांक find_partition(काष्ठा scsi_tape *STp)
अणु
	पूर्णांक i, partition;
	अचिन्हित पूर्णांक block;

	अगर ((i = get_location(STp, &block, &partition, 1)) < 0)
		वापस i;
	अगर (partition >= ST_NBR_PARTITIONS)
		वापस (-EIO);
	वापस partition;
पूर्ण


/* Change the partition अगर necessary */
अटल पूर्णांक चयन_partition(काष्ठा scsi_tape *STp)
अणु
	काष्ठा st_partstat *STps;

	अगर (STp->partition == STp->new_partition)
		वापस 0;
	STps = &(STp->ps[STp->new_partition]);
	अगर (!STps->last_block_valid)
		STps->last_block_visited = 0;
	वापस set_location(STp, STps->last_block_visited, STp->new_partition, 1);
पूर्ण

/* Functions क्रम पढ़ोing and writing the medium partition mode page. */

#घोषणा PART_PAGE   0x11
#घोषणा PART_PAGE_FIXED_LENGTH 8

#घोषणा PP_OFF_MAX_ADD_PARTS   2
#घोषणा PP_OFF_NBR_ADD_PARTS   3
#घोषणा PP_OFF_FLAGS           4
#घोषणा PP_OFF_PART_UNITS      6
#घोषणा PP_OFF_RESERVED        7

#घोषणा PP_BIT_IDP             0x20
#घोषणा PP_BIT_FDP             0x80
#घोषणा PP_MSK_PSUM_MB         0x10
#घोषणा PP_MSK_PSUM_UNITS      0x18
#घोषणा PP_MSK_POFM            0x04

/* Get the number of partitions on the tape. As a side effect पढ़ोs the
   mode page पूर्णांकo the tape buffer. */
अटल पूर्णांक nbr_partitions(काष्ठा scsi_tape *STp)
अणु
	पूर्णांक result;

	अगर (STp->पढ़ोy != ST_READY)
		वापस (-EIO);

	result = पढ़ो_mode_page(STp, PART_PAGE, 1);

	अगर (result) अणु
		DEBC_prपूर्णांकk(STp, "Can't read medium partition page.\n");
		result = (-EIO);
	पूर्ण अन्यथा अणु
		result = (STp->buffer)->b_data[MODE_HEADER_LENGTH +
					      PP_OFF_NBR_ADD_PARTS] + 1;
		DEBC_prपूर्णांकk(STp, "Number of partitions %d.\n", result);
	पूर्ण

	वापस result;
पूर्ण


अटल पूर्णांक क्रमmat_medium(काष्ठा scsi_tape *STp, पूर्णांक क्रमmat)
अणु
	पूर्णांक result = 0;
	पूर्णांक समयout = STp->दीर्घ_समयout;
	अचिन्हित अक्षर scmd[MAX_COMMAND_SIZE];
	काष्ठा st_request *SRpnt;

	स_रखो(scmd, 0, MAX_COMMAND_SIZE);
	scmd[0] = FORMAT_UNIT;
	scmd[2] = क्रमmat;
	अगर (STp->immediate) अणु
		scmd[1] |= 1;		/* Don't रुको क्रम completion */
		समयout = STp->device->request_queue->rq_समयout;
	पूर्ण
	DEBC_prपूर्णांकk(STp, "Sending FORMAT MEDIUM\n");
	SRpnt = st_करो_scsi(शून्य, STp, scmd, 0, DMA_NONE,
			   समयout, MAX_RETRIES, 1);
	अगर (!SRpnt)
		result = STp->buffer->syscall_result;
	वापस result;
पूर्ण


/* Partition the tape पूर्णांकo two partitions अगर size > 0 or one partition अगर
   size == 0.

   The block descriptors are पढ़ो and written because Sony SDT-7000 करोes not
   work without this (suggestion from Michael Schaefer <Michael.Schaefer@dlr.de>).

   My HP C1533A drive वापसs only one partition size field. This is used to
   set the size of partition 1. There is no size field क्रम the शेष partition.
   Michael Schaefer's Sony SDT-7000 वापसs two descriptors and the second is
   used to set the size of partition 1 (this is what the SCSI-3 standard specअगरies).
   The following algorithm is used to accommodate both drives: अगर the number of
   partition size fields is greater than the maximum number of additional partitions
   in the mode page, the second field is used. Otherwise the first field is used.

   For Seagate DDS drives the page length must be 8 when no partitions is defined
   and 10 when 1 partition is defined (inक्रमmation from Eric Lee Green). This is
   is acceptable also to some other old drives and enक्रमced अगर the first partition
   size field is used क्रम the first additional partition size.

   For drives that advertize SCSI-3 or newer, use the SSC-3 methods.
 */
अटल पूर्णांक partition_tape(काष्ठा scsi_tape *STp, पूर्णांक size)
अणु
	पूर्णांक result;
	पूर्णांक target_partition;
	bool scsi3 = STp->device->scsi_level >= SCSI_3, needs_क्रमmat = false;
	पूर्णांक pgo, psd_cnt, psकरो;
	पूर्णांक psum = PP_MSK_PSUM_MB, units = 0;
	अचिन्हित अक्षर *bp;

	result = पढ़ो_mode_page(STp, PART_PAGE, 0);
	अगर (result) अणु
		DEBC_prपूर्णांकk(STp, "Can't read partition mode page.\n");
		वापस result;
	पूर्ण
	target_partition = 1;
	अगर (size < 0) अणु
		target_partition = 0;
		size = -size;
	पूर्ण

	/* The mode page is in the buffer. Let's modअगरy it and ग_लिखो it. */
	bp = (STp->buffer)->b_data;
	pgo = MODE_HEADER_LENGTH + bp[MH_OFF_BDESCS_LENGTH];
	DEBC_prपूर्णांकk(STp, "Partition page length is %d bytes.\n",
		    bp[pgo + MP_OFF_PAGE_LENGTH] + 2);

	psd_cnt = (bp[pgo + MP_OFF_PAGE_LENGTH] + 2 - PART_PAGE_FIXED_LENGTH) / 2;

	अगर (scsi3) अणु
		needs_क्रमmat = (bp[pgo + PP_OFF_FLAGS] & PP_MSK_POFM) != 0;
		अगर (needs_क्रमmat && size == 0) अणु
			/* No need to ग_लिखो the mode page when clearing
			 *  partitioning
			 */
			DEBC_prपूर्णांकk(STp, "Formatting tape with one partition.\n");
			result = क्रमmat_medium(STp, 0);
			जाओ out;
		पूर्ण
		अगर (needs_क्रमmat)  /* Leave the old value क्रम HP DATs claiming SCSI_3 */
			psd_cnt = 2;
		अगर ((bp[pgo + PP_OFF_FLAGS] & PP_MSK_PSUM_UNITS) == PP_MSK_PSUM_UNITS) अणु
			/* Use units scaling क्रम large partitions अगर the device
			 * suggests it and no precision lost. Required क्रम IBM
			 * TS1140/50 drives that करोn't support MB units.
			 */
			अगर (size >= 1000 && (size % 1000) == 0) अणु
				size /= 1000;
				psum = PP_MSK_PSUM_UNITS;
				units = 9; /* GB */
			पूर्ण
		पूर्ण
		/* Try it anyway अगर too large to specअगरy in MB */
		अगर (psum == PP_MSK_PSUM_MB && size >= 65534) अणु
			size /= 1000;
			psum = PP_MSK_PSUM_UNITS;
			units = 9;  /* GB */
		पूर्ण
	पूर्ण

	अगर (size >= 65535 ||  /* Does not fit पूर्णांकo two bytes */
	    (target_partition == 0 && psd_cnt < 2)) अणु
		result = -EINVAL;
		जाओ out;
	पूर्ण

	psकरो = pgo + PART_PAGE_FIXED_LENGTH;
	/* The second condition is क्रम HP DDS which use only one partition size
	 * descriptor
	 */
	अगर (target_partition > 0 &&
	    (psd_cnt > bp[pgo + PP_OFF_MAX_ADD_PARTS] ||
	     bp[pgo + PP_OFF_MAX_ADD_PARTS] != 1)) अणु
		bp[psकरो] = bp[psकरो + 1] = 0xff;  /* Rest to partition 0 */
		psकरो += 2;
	पूर्ण
	स_रखो(bp + psकरो, 0, bp[pgo + PP_OFF_NBR_ADD_PARTS] * 2);

	DEBC_prपूर्णांकk(STp, "psd_cnt %d, max.parts %d, nbr_parts %d\n",
		    psd_cnt, bp[pgo + PP_OFF_MAX_ADD_PARTS],
		    bp[pgo + PP_OFF_NBR_ADD_PARTS]);

	अगर (size == 0) अणु
		bp[pgo + PP_OFF_NBR_ADD_PARTS] = 0;
		अगर (psd_cnt <= bp[pgo + PP_OFF_MAX_ADD_PARTS])
		    bp[pgo + MP_OFF_PAGE_LENGTH] = 6;
		DEBC_prपूर्णांकk(STp, "Formatting tape with one partition.\n");
	पूर्ण अन्यथा अणु
		bp[psकरो] = (size >> 8) & 0xff;
		bp[psकरो + 1] = size & 0xff;
		अगर (target_partition == 0)
			bp[psकरो + 2] = bp[psकरो + 3] = 0xff;
		bp[pgo + 3] = 1;
		अगर (bp[pgo + MP_OFF_PAGE_LENGTH] < 8)
		    bp[pgo + MP_OFF_PAGE_LENGTH] = 8;
		DEBC_prपूर्णांकk(STp,
			    "Formatting tape with two partitions (%i = %d MB).\n",
			    target_partition, units > 0 ? size * 1000 : size);
	पूर्ण
	bp[pgo + PP_OFF_PART_UNITS] = 0;
	bp[pgo + PP_OFF_RESERVED] = 0;
	अगर (size != 1 || units != 0) अणु
		bp[pgo + PP_OFF_FLAGS] = PP_BIT_IDP | psum |
			(bp[pgo + PP_OFF_FLAGS] & 0x07);
		bp[pgo + PP_OFF_PART_UNITS] = units;
	पूर्ण अन्यथा
		bp[pgo + PP_OFF_FLAGS] = PP_BIT_FDP |
			(bp[pgo + PP_OFF_FLAGS] & 0x1f);
	bp[pgo + MP_OFF_PAGE_LENGTH] = 6 + psd_cnt * 2;

	result = ग_लिखो_mode_page(STp, PART_PAGE, 1);

	अगर (!result && needs_क्रमmat)
		result = क्रमmat_medium(STp, 1);

	अगर (result) अणु
		st_prपूर्णांकk(KERN_INFO, STp, "Partitioning of tape failed.\n");
		result = (-EIO);
	पूर्ण

out:
	वापस result;
पूर्ण



/* The ioctl command */
अटल दीर्घ st_ioctl_common(काष्ठा file *file, अचिन्हित पूर्णांक cmd_in, व्योम __user *p)
अणु
	पूर्णांक i, cmd_nr, cmd_type, bt;
	पूर्णांक retval = 0;
	अचिन्हित पूर्णांक blk;
	काष्ठा scsi_tape *STp = file->निजी_data;
	काष्ठा st_modedef *STm;
	काष्ठा st_partstat *STps;

	अगर (mutex_lock_पूर्णांकerruptible(&STp->lock))
		वापस -ERESTARTSYS;

	DEB(
	अगर (debugging && !STp->in_use) अणु
		st_prपूर्णांकk(ST_DEB_MSG, STp, "Incorrect device.\n");
		retval = (-EIO);
		जाओ out;
	पूर्ण ) /* end DEB */

	STm = &(STp->modes[STp->current_mode]);
	STps = &(STp->ps[STp->partition]);

	/*
	 * If we are in the middle of error recovery, करोn't let anyone
	 * अन्यथा try and use this device.  Also, अगर error recovery fails, it
	 * may try and take the device offline, in which हाल all further
	 * access to the device is prohibited.
	 */
	retval = scsi_ioctl_block_when_processing_errors(STp->device, cmd_in,
			file->f_flags & O_NDELAY);
	अगर (retval)
		जाओ out;

	cmd_type = _IOC_TYPE(cmd_in);
	cmd_nr = _IOC_NR(cmd_in);

	अगर (cmd_type == _IOC_TYPE(MTIOCTOP) && cmd_nr == _IOC_NR(MTIOCTOP)) अणु
		काष्ठा mtop mtc;

		अगर (_IOC_SIZE(cmd_in) != माप(mtc)) अणु
			retval = (-EINVAL);
			जाओ out;
		पूर्ण

		i = copy_from_user(&mtc, p, माप(काष्ठा mtop));
		अगर (i) अणु
			retval = (-EFAULT);
			जाओ out;
		पूर्ण

		अगर (mtc.mt_op == MTSETDRVBUFFER && !capable(CAP_SYS_ADMIN)) अणु
			st_prपूर्णांकk(KERN_WARNING, STp,
				  "MTSETDRVBUFFER only allowed for root.\n");
			retval = (-EPERM);
			जाओ out;
		पूर्ण
		अगर (!STm->defined &&
		    (mtc.mt_op != MTSETDRVBUFFER &&
		     (mtc.mt_count & MT_ST_OPTIONS) == 0)) अणु
			retval = (-ENXIO);
			जाओ out;
		पूर्ण

		अगर (!STp->pos_unknown) अणु

			अगर (STps->eof == ST_FM_HIT) अणु
				अगर (mtc.mt_op == MTFSF || mtc.mt_op == MTFSFM ||
                                    mtc.mt_op == MTEOM) अणु
					mtc.mt_count -= 1;
					अगर (STps->drv_file >= 0)
						STps->drv_file += 1;
				पूर्ण अन्यथा अगर (mtc.mt_op == MTBSF || mtc.mt_op == MTBSFM) अणु
					mtc.mt_count += 1;
					अगर (STps->drv_file >= 0)
						STps->drv_file += 1;
				पूर्ण
			पूर्ण

			अगर (mtc.mt_op == MTSEEK) अणु
				/* Old position must be restored अगर partition will be
                                   changed */
				i = !STp->can_partitions ||
				    (STp->new_partition != STp->partition);
			पूर्ण अन्यथा अणु
				i = mtc.mt_op == MTREW || mtc.mt_op == MTOFFL ||
				    mtc.mt_op == MTRETEN || mtc.mt_op == MTEOM ||
				    mtc.mt_op == MTLOCK || mtc.mt_op == MTLOAD ||
				    mtc.mt_op == MTFSF || mtc.mt_op == MTFSFM ||
				    mtc.mt_op == MTBSF || mtc.mt_op == MTBSFM ||
				    mtc.mt_op == MTCOMPRESSION;
			पूर्ण
			i = flush_buffer(STp, i);
			अगर (i < 0) अणु
				retval = i;
				जाओ out;
			पूर्ण
			अगर (STps->rw == ST_WRITING &&
			    (mtc.mt_op == MTREW || mtc.mt_op == MTOFFL ||
			     mtc.mt_op == MTSEEK ||
			     mtc.mt_op == MTBSF || mtc.mt_op == MTBSFM)) अणु
				i = st_पूर्णांक_ioctl(STp, MTWखातापूर्ण, 1);
				अगर (i < 0) अणु
					retval = i;
					जाओ out;
				पूर्ण
				अगर (mtc.mt_op == MTBSF || mtc.mt_op == MTBSFM)
					mtc.mt_count++;
				STps->rw = ST_IDLE;
			     पूर्ण

		पूर्ण अन्यथा अणु
			/*
			 * If there was a bus reset, block further access
			 * to this device.  If the user wants to शुरुआत the tape,
			 * then reset the flag and allow access again.
			 */
			अगर (mtc.mt_op != MTREW &&
			    mtc.mt_op != MTOFFL &&
			    mtc.mt_op != MTRETEN &&
			    mtc.mt_op != MTERASE &&
			    mtc.mt_op != MTSEEK &&
			    mtc.mt_op != MTEOM) अणु
				retval = (-EIO);
				जाओ out;
			पूर्ण
			reset_state(STp);
			/* हटाओ this when the midlevel properly clears was_reset */
			STp->device->was_reset = 0;
		पूर्ण

		अगर (mtc.mt_op != MTNOP && mtc.mt_op != MTSETBLK &&
		    mtc.mt_op != MTSETDENSITY && mtc.mt_op != MTWSM &&
		    mtc.mt_op != MTSETDRVBUFFER && mtc.mt_op != MTSETPART)
			STps->rw = ST_IDLE;	/* Prevent स्वतःmatic Wखातापूर्ण and fsf */

		अगर (mtc.mt_op == MTOFFL && STp->करोor_locked != ST_UNLOCKED)
			करो_करोor_lock(STp, 0);	/* Ignore result! */

		अगर (mtc.mt_op == MTSETDRVBUFFER &&
		    (mtc.mt_count & MT_ST_OPTIONS) != 0) अणु
			retval = st_set_options(STp, mtc.mt_count);
			जाओ out;
		पूर्ण

		अगर (mtc.mt_op == MTSETPART) अणु
			अगर (!STp->can_partitions ||
			    mtc.mt_count < 0 || mtc.mt_count >= ST_NBR_PARTITIONS) अणु
				retval = (-EINVAL);
				जाओ out;
			पूर्ण
			अगर (mtc.mt_count >= STp->nbr_partitions &&
			    (STp->nbr_partitions = nbr_partitions(STp)) < 0) अणु
				retval = (-EIO);
				जाओ out;
			पूर्ण
			अगर (mtc.mt_count >= STp->nbr_partitions) अणु
				retval = (-EINVAL);
				जाओ out;
			पूर्ण
			STp->new_partition = mtc.mt_count;
			retval = 0;
			जाओ out;
		पूर्ण

		अगर (mtc.mt_op == MTMKPART) अणु
			अगर (!STp->can_partitions) अणु
				retval = (-EINVAL);
				जाओ out;
			पूर्ण
			i = करो_load_unload(STp, file, 1);
			अगर (i < 0) अणु
				retval = i;
				जाओ out;
			पूर्ण
			i = partition_tape(STp, mtc.mt_count);
			अगर (i < 0) अणु
				retval = i;
				जाओ out;
			पूर्ण
			क्रम (i = 0; i < ST_NBR_PARTITIONS; i++) अणु
				STp->ps[i].rw = ST_IDLE;
				STp->ps[i].at_sm = 0;
				STp->ps[i].last_block_valid = 0;
			पूर्ण
			STp->partition = STp->new_partition = 0;
			STp->nbr_partitions = mtc.mt_count != 0 ? 2 : 1;
			STps->drv_block = STps->drv_file = 0;
			retval = 0;
			जाओ out;
		पूर्ण

		अगर (mtc.mt_op == MTSEEK) अणु
			i = set_location(STp, mtc.mt_count, STp->new_partition, 0);
			अगर (!STp->can_partitions)
				STp->ps[0].rw = ST_IDLE;
			retval = i;
			जाओ out;
		पूर्ण

		अगर (mtc.mt_op == MTUNLOAD || mtc.mt_op == MTOFFL) अणु
			retval = करो_load_unload(STp, file, 0);
			जाओ out;
		पूर्ण

		अगर (mtc.mt_op == MTLOAD) अणु
			retval = करो_load_unload(STp, file, max(1, mtc.mt_count));
			जाओ out;
		पूर्ण

		अगर (mtc.mt_op == MTLOCK || mtc.mt_op == MTUNLOCK) अणु
			retval = करो_करोor_lock(STp, (mtc.mt_op == MTLOCK));
			जाओ out;
		पूर्ण

		अगर (STp->can_partitions && STp->पढ़ोy == ST_READY &&
		    (i = चयन_partition(STp)) < 0) अणु
			retval = i;
			जाओ out;
		पूर्ण

		अगर (mtc.mt_op == MTCOMPRESSION)
			retval = st_compression(STp, (mtc.mt_count & 1));
		अन्यथा
			retval = st_पूर्णांक_ioctl(STp, mtc.mt_op, mtc.mt_count);
		जाओ out;
	पूर्ण
	अगर (!STm->defined) अणु
		retval = (-ENXIO);
		जाओ out;
	पूर्ण

	अगर ((i = flush_buffer(STp, 0)) < 0) अणु
		retval = i;
		जाओ out;
	पूर्ण
	अगर (STp->can_partitions &&
	    (i = चयन_partition(STp)) < 0) अणु
		retval = i;
		जाओ out;
	पूर्ण

	अगर (cmd_type == _IOC_TYPE(MTIOCGET) && cmd_nr == _IOC_NR(MTIOCGET)) अणु
		काष्ठा mtget mt_status;

		अगर (_IOC_SIZE(cmd_in) != माप(काष्ठा mtget)) अणु
			 retval = (-EINVAL);
			 जाओ out;
		पूर्ण

		mt_status.mt_type = STp->tape_type;
		mt_status.mt_dsreg =
		    ((STp->block_size << MT_ST_BLKSIZE_SHIFT) & MT_ST_BLKSIZE_MASK) |
		    ((STp->density << MT_ST_DENSITY_SHIFT) & MT_ST_DENSITY_MASK);
		mt_status.mt_blkno = STps->drv_block;
		mt_status.mt_fileno = STps->drv_file;
		अगर (STp->block_size != 0) अणु
			अगर (STps->rw == ST_WRITING)
				mt_status.mt_blkno +=
				    (STp->buffer)->buffer_bytes / STp->block_size;
			अन्यथा अगर (STps->rw == ST_READING)
				mt_status.mt_blkno -=
                                        ((STp->buffer)->buffer_bytes +
                                         STp->block_size - 1) / STp->block_size;
		पूर्ण

		mt_status.mt_gstat = 0;
		अगर (STp->drv_ग_लिखो_prot)
			mt_status.mt_gstat |= GMT_WR_PROT(0xffffffff);
		अगर (mt_status.mt_blkno == 0) अणु
			अगर (mt_status.mt_fileno == 0)
				mt_status.mt_gstat |= GMT_BOT(0xffffffff);
			अन्यथा
				mt_status.mt_gstat |= GMT_खातापूर्ण(0xffffffff);
		पूर्ण
		mt_status.mt_erreg = (STp->recover_reg << MT_ST_SOFTERR_SHIFT);
		mt_status.mt_resid = STp->partition;
		अगर (STps->eof == ST_EOM_OK || STps->eof == ST_EOM_ERROR)
			mt_status.mt_gstat |= GMT_EOT(0xffffffff);
		अन्यथा अगर (STps->eof >= ST_EOM_OK)
			mt_status.mt_gstat |= GMT_EOD(0xffffffff);
		अगर (STp->density == 1)
			mt_status.mt_gstat |= GMT_D_800(0xffffffff);
		अन्यथा अगर (STp->density == 2)
			mt_status.mt_gstat |= GMT_D_1600(0xffffffff);
		अन्यथा अगर (STp->density == 3)
			mt_status.mt_gstat |= GMT_D_6250(0xffffffff);
		अगर (STp->पढ़ोy == ST_READY)
			mt_status.mt_gstat |= GMT_ONLINE(0xffffffff);
		अगर (STp->पढ़ोy == ST_NO_TAPE)
			mt_status.mt_gstat |= GMT_DR_OPEN(0xffffffff);
		अगर (STps->at_sm)
			mt_status.mt_gstat |= GMT_SM(0xffffffff);
		अगर (STm->करो_async_ग_लिखोs ||
                    (STm->करो_buffer_ग_लिखोs && STp->block_size != 0) ||
		    STp->drv_buffer != 0)
			mt_status.mt_gstat |= GMT_IM_REP_EN(0xffffffff);
		अगर (STp->cleaning_req)
			mt_status.mt_gstat |= GMT_CLN(0xffffffff);

		retval = put_user_mtget(p, &mt_status);
		अगर (retval)
			जाओ out;

		STp->recover_reg = 0;		/* Clear after पढ़ो */
		जाओ out;
	पूर्ण			/* End of MTIOCGET */
	अगर (cmd_type == _IOC_TYPE(MTIOCPOS) && cmd_nr == _IOC_NR(MTIOCPOS)) अणु
		काष्ठा mtpos mt_pos;
		अगर (_IOC_SIZE(cmd_in) != माप(काष्ठा mtpos)) अणु
			 retval = (-EINVAL);
			 जाओ out;
		पूर्ण
		अगर ((i = get_location(STp, &blk, &bt, 0)) < 0) अणु
			retval = i;
			जाओ out;
		पूर्ण
		mt_pos.mt_blkno = blk;
		retval = put_user_mtpos(p, &mt_pos);
		जाओ out;
	पूर्ण
	mutex_unlock(&STp->lock);
	चयन (cmd_in) अणु
		हाल SCSI_IOCTL_STOP_UNIT:
			/* unload */
			retval = scsi_ioctl(STp->device, cmd_in, p);
			अगर (!retval) अणु
				STp->rew_at_बंद = 0;
				STp->पढ़ोy = ST_NO_TAPE;
			पूर्ण
			वापस retval;

		हाल SCSI_IOCTL_GET_IDLUN:
		हाल SCSI_IOCTL_GET_BUS_NUMBER:
			अवरोध;

		शेष:
			अगर ((cmd_in == SG_IO ||
			     cmd_in == SCSI_IOCTL_SEND_COMMAND ||
			     cmd_in == CDROM_SEND_PACKET) &&
			    !capable(CAP_SYS_RAWIO))
				i = -EPERM;
			अन्यथा
				i = scsi_cmd_ioctl(STp->disk->queue, STp->disk,
						   file->f_mode, cmd_in, p);
			अगर (i != -ENOTTY)
				वापस i;
			अवरोध;
	पूर्ण
	वापस -ENOTTY;

 out:
	mutex_unlock(&STp->lock);
	वापस retval;
पूर्ण

अटल दीर्घ st_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd_in, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *p = (व्योम __user *)arg;
	काष्ठा scsi_tape *STp = file->निजी_data;
	पूर्णांक ret;

	ret = st_ioctl_common(file, cmd_in, p);
	अगर (ret != -ENOTTY)
		वापस ret;

	वापस scsi_ioctl(STp->device, cmd_in, p);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ st_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd_in, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *p = compat_ptr(arg);
	काष्ठा scsi_tape *STp = file->निजी_data;
	पूर्णांक ret;

	/* argument conversion is handled using put_user_mtpos/put_user_mtget */
	चयन (cmd_in) अणु
	हाल MTIOCPOS32:
		वापस st_ioctl_common(file, MTIOCPOS, p);
	हाल MTIOCGET32:
		वापस st_ioctl_common(file, MTIOCGET, p);
	पूर्ण

	ret = st_ioctl_common(file, cmd_in, p);
	अगर (ret != -ENOTTY)
		वापस ret;

	वापस scsi_compat_ioctl(STp->device, cmd_in, p);
पूर्ण
#पूर्ण_अगर



/* Try to allocate a new tape buffer. Calling function must not hold
   dev_arr_lock. */
अटल काष्ठा st_buffer *new_tape_buffer(पूर्णांक max_sg)
अणु
	काष्ठा st_buffer *tb;

	tb = kzalloc(माप(काष्ठा st_buffer), GFP_KERNEL);
	अगर (!tb) अणु
		prपूर्णांकk(KERN_NOTICE "st: Can't allocate new tape buffer.\n");
		वापस शून्य;
	पूर्ण
	tb->frp_segs = 0;
	tb->use_sg = max_sg;
	tb->buffer_size = 0;

	tb->reserved_pages = kसुस्मृति(max_sg, माप(काष्ठा page *),
				     GFP_KERNEL);
	अगर (!tb->reserved_pages) अणु
		kमुक्त(tb);
		वापस शून्य;
	पूर्ण

	वापस tb;
पूर्ण


/* Try to allocate enough space in the tape buffer */
#घोषणा ST_MAX_ORDER 6

अटल पूर्णांक enlarge_buffer(काष्ठा st_buffer * STbuffer, पूर्णांक new_size)
अणु
	पूर्णांक segs, max_segs, b_size, order, got;
	gfp_t priority;

	अगर (new_size <= STbuffer->buffer_size)
		वापस 1;

	अगर (STbuffer->buffer_size <= PAGE_SIZE)
		normalize_buffer(STbuffer);  /* Aव्योम extra segment */

	max_segs = STbuffer->use_sg;

	priority = GFP_KERNEL | __GFP_NOWARN;

	अगर (STbuffer->cleared)
		priority |= __GFP_ZERO;

	अगर (STbuffer->frp_segs) अणु
		order = STbuffer->reserved_page_order;
		b_size = PAGE_SIZE << order;
	पूर्ण अन्यथा अणु
		क्रम (b_size = PAGE_SIZE, order = 0;
		     order < ST_MAX_ORDER &&
			     max_segs * (PAGE_SIZE << order) < new_size;
		     order++, b_size *= 2)
			;  /* empty */
		STbuffer->reserved_page_order = order;
	पूर्ण
	अगर (max_segs * (PAGE_SIZE << order) < new_size) अणु
		अगर (order == ST_MAX_ORDER)
			वापस 0;
		normalize_buffer(STbuffer);
		वापस enlarge_buffer(STbuffer, new_size);
	पूर्ण

	क्रम (segs = STbuffer->frp_segs, got = STbuffer->buffer_size;
	     segs < max_segs && got < new_size;) अणु
		काष्ठा page *page;

		page = alloc_pages(priority, order);
		अगर (!page) अणु
			DEB(STbuffer->buffer_size = got);
			normalize_buffer(STbuffer);
			वापस 0;
		पूर्ण

		STbuffer->frp_segs += 1;
		got += b_size;
		STbuffer->buffer_size = got;
		STbuffer->reserved_pages[segs] = page;
		segs++;
	पूर्ण
	STbuffer->b_data = page_address(STbuffer->reserved_pages[0]);

	वापस 1;
पूर्ण


/* Make sure that no data from previous user is in the पूर्णांकernal buffer */
अटल व्योम clear_buffer(काष्ठा st_buffer * st_bp)
अणु
	पूर्णांक i;

	क्रम (i=0; i < st_bp->frp_segs; i++)
		स_रखो(page_address(st_bp->reserved_pages[i]), 0,
		       PAGE_SIZE << st_bp->reserved_page_order);
	st_bp->cleared = 1;
पूर्ण


/* Release the extra buffer */
अटल व्योम normalize_buffer(काष्ठा st_buffer * STbuffer)
अणु
	पूर्णांक i, order = STbuffer->reserved_page_order;

	क्रम (i = 0; i < STbuffer->frp_segs; i++) अणु
		__मुक्त_pages(STbuffer->reserved_pages[i], order);
		STbuffer->buffer_size -= (PAGE_SIZE << order);
	पूर्ण
	STbuffer->frp_segs = 0;
	STbuffer->sg_segs = 0;
	STbuffer->reserved_page_order = 0;
	STbuffer->map_data.offset = 0;
पूर्ण


/* Move data from the user buffer to the tape buffer. Returns zero (success) or
   negative error code. */
अटल पूर्णांक append_to_buffer(स्थिर अक्षर __user *ubp, काष्ठा st_buffer * st_bp, पूर्णांक करो_count)
अणु
	पूर्णांक i, cnt, res, offset;
	पूर्णांक length = PAGE_SIZE << st_bp->reserved_page_order;

	क्रम (i = 0, offset = st_bp->buffer_bytes;
	     i < st_bp->frp_segs && offset >= length; i++)
		offset -= length;
	अगर (i == st_bp->frp_segs) अणु	/* Should never happen */
		prपूर्णांकk(KERN_WARNING "st: append_to_buffer offset overflow.\n");
		वापस (-EIO);
	पूर्ण
	क्रम (; i < st_bp->frp_segs && करो_count > 0; i++) अणु
		काष्ठा page *page = st_bp->reserved_pages[i];
		cnt = length - offset < करो_count ? length - offset : करो_count;
		res = copy_from_user(page_address(page) + offset, ubp, cnt);
		अगर (res)
			वापस (-EFAULT);
		करो_count -= cnt;
		st_bp->buffer_bytes += cnt;
		ubp += cnt;
		offset = 0;
	पूर्ण
	अगर (करो_count) /* Should never happen */
		वापस (-EIO);

	वापस 0;
पूर्ण


/* Move data from the tape buffer to the user buffer. Returns zero (success) or
   negative error code. */
अटल पूर्णांक from_buffer(काष्ठा st_buffer * st_bp, अक्षर __user *ubp, पूर्णांक करो_count)
अणु
	पूर्णांक i, cnt, res, offset;
	पूर्णांक length = PAGE_SIZE << st_bp->reserved_page_order;

	क्रम (i = 0, offset = st_bp->पढ़ो_poपूर्णांकer;
	     i < st_bp->frp_segs && offset >= length; i++)
		offset -= length;
	अगर (i == st_bp->frp_segs) अणु	/* Should never happen */
		prपूर्णांकk(KERN_WARNING "st: from_buffer offset overflow.\n");
		वापस (-EIO);
	पूर्ण
	क्रम (; i < st_bp->frp_segs && करो_count > 0; i++) अणु
		काष्ठा page *page = st_bp->reserved_pages[i];
		cnt = length - offset < करो_count ? length - offset : करो_count;
		res = copy_to_user(ubp, page_address(page) + offset, cnt);
		अगर (res)
			वापस (-EFAULT);
		करो_count -= cnt;
		st_bp->buffer_bytes -= cnt;
		st_bp->पढ़ो_poपूर्णांकer += cnt;
		ubp += cnt;
		offset = 0;
	पूर्ण
	अगर (करो_count) /* Should never happen */
		वापस (-EIO);

	वापस 0;
पूर्ण


/* Move data towards start of buffer */
अटल व्योम move_buffer_data(काष्ठा st_buffer * st_bp, पूर्णांक offset)
अणु
	पूर्णांक src_seg, dst_seg, src_offset = 0, dst_offset;
	पूर्णांक count, total;
	पूर्णांक length = PAGE_SIZE << st_bp->reserved_page_order;

	अगर (offset == 0)
		वापस;

	total=st_bp->buffer_bytes - offset;
	क्रम (src_seg=0; src_seg < st_bp->frp_segs; src_seg++) अणु
		src_offset = offset;
		अगर (src_offset < length)
			अवरोध;
		offset -= length;
	पूर्ण

	st_bp->buffer_bytes = st_bp->पढ़ो_poपूर्णांकer = total;
	क्रम (dst_seg=dst_offset=0; total > 0; ) अणु
		काष्ठा page *dpage = st_bp->reserved_pages[dst_seg];
		काष्ठा page *spage = st_bp->reserved_pages[src_seg];

		count = min(length - dst_offset, length - src_offset);
		स_हटाओ(page_address(dpage) + dst_offset,
			page_address(spage) + src_offset, count);
		src_offset += count;
		अगर (src_offset >= length) अणु
			src_seg++;
			src_offset = 0;
		पूर्ण
		dst_offset += count;
		अगर (dst_offset >= length) अणु
			dst_seg++;
			dst_offset = 0;
		पूर्ण
		total -= count;
	पूर्ण
पूर्ण

/* Validate the options from command line or module parameters */
अटल व्योम validate_options(व्योम)
अणु
	अगर (buffer_kbs > 0)
		st_fixed_buffer_size = buffer_kbs * ST_KILOBYTE;
	अगर (max_sg_segs >= ST_FIRST_SG)
		st_max_sg_segs = max_sg_segs;
पूर्ण

#अगर_अघोषित MODULE
/* Set the boot options. Syntax is defined in Documenation/scsi/st.txt.
 */
अटल पूर्णांक __init st_setup(अक्षर *str)
अणु
	पूर्णांक i, len, पूर्णांकs[5];
	अक्षर *stp;

	stp = get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);

	अगर (पूर्णांकs[0] > 0) अणु
		क्रम (i = 0; i < पूर्णांकs[0] && i < ARRAY_SIZE(parms); i++)
			अगर (parms[i].val)
				*parms[i].val = पूर्णांकs[i + 1];
	पूर्ण अन्यथा अणु
		जबतक (stp != शून्य) अणु
			क्रम (i = 0; i < ARRAY_SIZE(parms); i++) अणु
				len = म_माप(parms[i].name);
				अगर (!म_भेदन(stp, parms[i].name, len) &&
				    (*(stp + len) == ':' || *(stp + len) == '=')) अणु
					अगर (parms[i].val)
						*parms[i].val =
							simple_म_से_अदीर्घ(stp + len + 1, शून्य, 0);
					अन्यथा
						prपूर्णांकk(KERN_WARNING "st: Obsolete parameter %s\n",
						       parms[i].name);
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (i >= ARRAY_SIZE(parms))
				 prपूर्णांकk(KERN_WARNING "st: invalid parameter in '%s'\n",
					stp);
			stp = म_अक्षर(stp, ',');
			अगर (stp)
				stp++;
		पूर्ण
	पूर्ण

	validate_options();

	वापस 1;
पूर्ण

__setup("st=", st_setup);

#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations st_fops =
अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		st_पढ़ो,
	.ग_लिखो =	st_ग_लिखो,
	.unlocked_ioctl = st_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = st_compat_ioctl,
#पूर्ण_अगर
	.खोलो =		st_खोलो,
	.flush =	st_flush,
	.release =	st_release,
	.llseek =	noop_llseek,
पूर्ण;

अटल पूर्णांक create_one_cdev(काष्ठा scsi_tape *tape, पूर्णांक mode, पूर्णांक rew)
अणु
	पूर्णांक i, error;
	dev_t cdev_devno;
	काष्ठा cdev *cdev;
	काष्ठा device *dev;
	काष्ठा st_modedef *STm = &(tape->modes[mode]);
	अक्षर name[10];
	पूर्णांक dev_num = tape->index;

	cdev_devno = MKDEV(SCSI_TAPE_MAJOR, TAPE_MINOR(dev_num, mode, rew));

	cdev = cdev_alloc();
	अगर (!cdev) अणु
		pr_err("st%d: out of memory. Device not attached.\n", dev_num);
		error = -ENOMEM;
		जाओ out;
	पूर्ण
	cdev->owner = THIS_MODULE;
	cdev->ops = &st_fops;
	STm->cdevs[rew] = cdev;

	error = cdev_add(cdev, cdev_devno, 1);
	अगर (error) अणु
		pr_err("st%d: Can't add %s-rewind mode %d\n", dev_num,
		       rew ? "non" : "auto", mode);
		pr_err("st%d: Device not attached.\n", dev_num);
		जाओ out_मुक्त;
	पूर्ण

	i = mode << (4 - ST_NBR_MODE_BITS);
	snम_लिखो(name, 10, "%s%s%s", rew ? "n" : "",
		 tape->disk->disk_name, st_क्रमmats[i]);

	dev = device_create(&st_sysfs_class, &tape->device->sdev_gendev,
			    cdev_devno, &tape->modes[mode], "%s", name);
	अगर (IS_ERR(dev)) अणु
		pr_err("st%d: device_create failed\n", dev_num);
		error = PTR_ERR(dev);
		जाओ out_मुक्त;
	पूर्ण

	STm->devs[rew] = dev;

	वापस 0;
out_मुक्त:
	cdev_del(STm->cdevs[rew]);
out:
	STm->cdevs[rew] = शून्य;
	STm->devs[rew] = शून्य;
	वापस error;
पूर्ण

अटल पूर्णांक create_cdevs(काष्ठा scsi_tape *tape)
अणु
	पूर्णांक mode, error;
	क्रम (mode = 0; mode < ST_NBR_MODES; ++mode) अणु
		error = create_one_cdev(tape, mode, 0);
		अगर (error)
			वापस error;
		error = create_one_cdev(tape, mode, 1);
		अगर (error)
			वापस error;
	पूर्ण

	वापस sysfs_create_link(&tape->device->sdev_gendev.kobj,
				 &tape->modes[0].devs[0]->kobj, "tape");
पूर्ण

अटल व्योम हटाओ_cdevs(काष्ठा scsi_tape *tape)
अणु
	पूर्णांक mode, rew;
	sysfs_हटाओ_link(&tape->device->sdev_gendev.kobj, "tape");
	क्रम (mode = 0; mode < ST_NBR_MODES; mode++) अणु
		काष्ठा st_modedef *STm = &(tape->modes[mode]);
		क्रम (rew = 0; rew < 2; rew++) अणु
			अगर (STm->cdevs[rew])
				cdev_del(STm->cdevs[rew]);
			अगर (STm->devs[rew])
				device_unरेजिस्टर(STm->devs[rew]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक st_probe(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *SDp = to_scsi_device(dev);
	काष्ठा gendisk *disk = शून्य;
	काष्ठा scsi_tape *tpnt = शून्य;
	काष्ठा st_modedef *STm;
	काष्ठा st_partstat *STps;
	काष्ठा st_buffer *buffer;
	पूर्णांक i, error;
	अक्षर *stp;

	अगर (SDp->type != TYPE_TAPE)
		वापस -ENODEV;
	अगर ((stp = st_incompatible(SDp))) अणु
		sdev_prपूर्णांकk(KERN_INFO, SDp,
			    "OnStream tapes are no longer supported;\n");
		sdev_prपूर्णांकk(KERN_INFO, SDp,
			    "please mail to linux-scsi@vger.kernel.org.\n");
		वापस -ENODEV;
	पूर्ण

	scsi_स्वतःpm_get_device(SDp);
	i = queue_max_segments(SDp->request_queue);
	अगर (st_max_sg_segs < i)
		i = st_max_sg_segs;
	buffer = new_tape_buffer(i);
	अगर (buffer == शून्य) अणु
		sdev_prपूर्णांकk(KERN_ERR, SDp,
			    "st: Can't allocate new tape buffer. "
			    "Device not attached.\n");
		जाओ out;
	पूर्ण

	disk = alloc_disk(1);
	अगर (!disk) अणु
		sdev_prपूर्णांकk(KERN_ERR, SDp,
			    "st: out of memory. Device not attached.\n");
		जाओ out_buffer_मुक्त;
	पूर्ण

	tpnt = kzalloc(माप(काष्ठा scsi_tape), GFP_KERNEL);
	अगर (tpnt == शून्य) अणु
		sdev_prपूर्णांकk(KERN_ERR, SDp,
			    "st: Can't allocate device descriptor.\n");
		जाओ out_put_disk;
	पूर्ण
	kref_init(&tpnt->kref);
	tpnt->disk = disk;
	disk->निजी_data = &tpnt->driver;
	/* SCSI tape करोesn't रेजिस्टर this gendisk via add_disk().  Manually
	 * take queue reference that release_disk() expects. */
	अगर (!blk_get_queue(SDp->request_queue))
		जाओ out_put_disk;
	disk->queue = SDp->request_queue;
	tpnt->driver = &st_ढाँचा;

	tpnt->device = SDp;
	अगर (SDp->scsi_level <= 2)
		tpnt->tape_type = MT_ISSCSI1;
	अन्यथा
		tpnt->tape_type = MT_ISSCSI2;

	tpnt->buffer = buffer;
	tpnt->buffer->last_SRpnt = शून्य;

	tpnt->inited = 0;
	tpnt->dirty = 0;
	tpnt->in_use = 0;
	tpnt->drv_buffer = 1;	/* Try buffering अगर no mode sense */
	tpnt->use_pf = (SDp->scsi_level >= SCSI_2);
	tpnt->density = 0;
	tpnt->करो_स्वतः_lock = ST_AUTO_LOCK;
	tpnt->can_bsr = (SDp->scsi_level > 2 ? 1 : ST_IN_खाता_POS); /* BSR mandatory in SCSI3 */
	tpnt->can_partitions = 0;
	tpnt->two_fm = ST_TWO_FM;
	tpnt->fast_mteom = ST_FAST_MTEOM;
	tpnt->scsi2_logical = ST_SCSI2LOGICAL;
	tpnt->sili = ST_SILI;
	tpnt->immediate = ST_NOWAIT;
	tpnt->immediate_filemark = 0;
	tpnt->शेष_drvbuffer = 0xff;		/* No क्रमced buffering */
	tpnt->partition = 0;
	tpnt->new_partition = 0;
	tpnt->nbr_partitions = 0;
	blk_queue_rq_समयout(tpnt->device->request_queue, ST_TIMEOUT);
	tpnt->दीर्घ_समयout = ST_LONG_TIMEOUT;
	tpnt->try_dio = try_direct_io;

	क्रम (i = 0; i < ST_NBR_MODES; i++) अणु
		STm = &(tpnt->modes[i]);
		STm->defined = 0;
		STm->sysv = ST_SYSV;
		STm->शेषs_क्रम_ग_लिखोs = 0;
		STm->करो_async_ग_लिखोs = ST_ASYNC_WRITES;
		STm->करो_buffer_ग_लिखोs = ST_BUFFER_WRITES;
		STm->करो_पढ़ो_ahead = ST_READ_AHEAD;
		STm->शेष_compression = ST_DONT_TOUCH;
		STm->शेष_blksize = (-1);	/* No क्रमced size */
		STm->शेष_density = (-1);	/* No क्रमced density */
		STm->tape = tpnt;
	पूर्ण

	क्रम (i = 0; i < ST_NBR_PARTITIONS; i++) अणु
		STps = &(tpnt->ps[i]);
		STps->rw = ST_IDLE;
		STps->eof = ST_NOखातापूर्ण;
		STps->at_sm = 0;
		STps->last_block_valid = 0;
		STps->drv_block = (-1);
		STps->drv_file = (-1);
	पूर्ण

	tpnt->current_mode = 0;
	tpnt->modes[0].defined = 1;

	tpnt->density_changed = tpnt->compression_changed =
	    tpnt->blksize_changed = 0;
	mutex_init(&tpnt->lock);

	idr_preload(GFP_KERNEL);
	spin_lock(&st_index_lock);
	error = idr_alloc(&st_index_idr, tpnt, 0, ST_MAX_TAPES + 1, GFP_NOWAIT);
	spin_unlock(&st_index_lock);
	idr_preload_end();
	अगर (error < 0) अणु
		pr_warn("st: idr allocation failed: %d\n", error);
		जाओ out_put_queue;
	पूर्ण
	tpnt->index = error;
	प्र_लिखो(disk->disk_name, "st%d", tpnt->index);
	tpnt->stats = kzalloc(माप(काष्ठा scsi_tape_stats), GFP_KERNEL);
	अगर (tpnt->stats == शून्य) अणु
		sdev_prपूर्णांकk(KERN_ERR, SDp,
			    "st: Can't allocate statistics.\n");
		जाओ out_idr_हटाओ;
	पूर्ण

	dev_set_drvdata(dev, tpnt);


	error = create_cdevs(tpnt);
	अगर (error)
		जाओ out_हटाओ_devs;
	scsi_स्वतःpm_put_device(SDp);

	sdev_prपूर्णांकk(KERN_NOTICE, SDp,
		    "Attached scsi tape %s\n", tape_name(tpnt));
	sdev_prपूर्णांकk(KERN_INFO, SDp, "%s: try direct i/o: %s (alignment %d B)\n",
		    tape_name(tpnt), tpnt->try_dio ? "yes" : "no",
		    queue_dma_alignment(SDp->request_queue) + 1);

	वापस 0;

out_हटाओ_devs:
	हटाओ_cdevs(tpnt);
	kमुक्त(tpnt->stats);
out_idr_हटाओ:
	spin_lock(&st_index_lock);
	idr_हटाओ(&st_index_idr, tpnt->index);
	spin_unlock(&st_index_lock);
out_put_queue:
	blk_put_queue(disk->queue);
out_put_disk:
	put_disk(disk);
	kमुक्त(tpnt);
out_buffer_मुक्त:
	kमुक्त(buffer);
out:
	scsi_स्वतःpm_put_device(SDp);
	वापस -ENODEV;
पूर्ण;


अटल पूर्णांक st_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा scsi_tape *tpnt = dev_get_drvdata(dev);
	पूर्णांक index = tpnt->index;

	scsi_स्वतःpm_get_device(to_scsi_device(dev));
	हटाओ_cdevs(tpnt);

	mutex_lock(&st_ref_mutex);
	kref_put(&tpnt->kref, scsi_tape_release);
	mutex_unlock(&st_ref_mutex);
	spin_lock(&st_index_lock);
	idr_हटाओ(&st_index_idr, index);
	spin_unlock(&st_index_lock);
	वापस 0;
पूर्ण

/**
 *      scsi_tape_release - Called to मुक्त the Scsi_Tape काष्ठाure
 *      @kref: poपूर्णांकer to embedded kref
 *
 *      st_ref_mutex must be held entering this routine.  Because it is
 *      called on last put, you should always use the scsi_tape_get()
 *      scsi_tape_put() helpers which manipulate the semaphore directly
 *      and never करो a direct kref_put().
 **/
अटल व्योम scsi_tape_release(काष्ठा kref *kref)
अणु
	काष्ठा scsi_tape *tpnt = to_scsi_tape(kref);
	काष्ठा gendisk *disk = tpnt->disk;

	tpnt->device = शून्य;

	अगर (tpnt->buffer) अणु
		normalize_buffer(tpnt->buffer);
		kमुक्त(tpnt->buffer->reserved_pages);
		kमुक्त(tpnt->buffer);
	पूर्ण

	disk->निजी_data = शून्य;
	put_disk(disk);
	kमुक्त(tpnt->stats);
	kमुक्त(tpnt);
	वापस;
पूर्ण

अटल काष्ठा class st_sysfs_class = अणु
	.name = "scsi_tape",
	.dev_groups = st_dev_groups,
पूर्ण;

अटल पूर्णांक __init init_st(व्योम)
अणु
	पूर्णांक err;

	validate_options();

	prपूर्णांकk(KERN_INFO "st: Version %s, fixed bufsize %d, s/g segs %d\n",
		verstr, st_fixed_buffer_size, st_max_sg_segs);

	debugging = (debug_flag > 0) ? debug_flag : NO_DEBUG;
	अगर (debugging) अणु
		prपूर्णांकk(KERN_INFO "st: Debugging enabled debug_flag = %d\n",
			debugging);
	पूर्ण

	err = class_रेजिस्टर(&st_sysfs_class);
	अगर (err) अणु
		pr_err("Unable register sysfs class for SCSI tapes\n");
		वापस err;
	पूर्ण

	err = रेजिस्टर_chrdev_region(MKDEV(SCSI_TAPE_MAJOR, 0),
				     ST_MAX_TAPE_ENTRIES, "st");
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Unable to get major %d for SCSI tapes\n",
		       SCSI_TAPE_MAJOR);
		जाओ err_class;
	पूर्ण

	err = scsi_रेजिस्टर_driver(&st_ढाँचा.gendrv);
	अगर (err)
		जाओ err_chrdev;

	वापस 0;

err_chrdev:
	unरेजिस्टर_chrdev_region(MKDEV(SCSI_TAPE_MAJOR, 0),
				 ST_MAX_TAPE_ENTRIES);
err_class:
	class_unरेजिस्टर(&st_sysfs_class);
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_st(व्योम)
अणु
	scsi_unरेजिस्टर_driver(&st_ढाँचा.gendrv);
	unरेजिस्टर_chrdev_region(MKDEV(SCSI_TAPE_MAJOR, 0),
				 ST_MAX_TAPE_ENTRIES);
	class_unरेजिस्टर(&st_sysfs_class);
	idr_destroy(&st_index_idr);
	prपूर्णांकk(KERN_INFO "st: Unloaded.\n");
पूर्ण

module_init(init_st);
module_निकास(निकास_st);


/* The sysfs driver पूर्णांकerface. Read-only at the moment */
अटल sमाप_प्रकार try_direct_io_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", try_direct_io);
पूर्ण
अटल DRIVER_ATTR_RO(try_direct_io);

अटल sमाप_प्रकार fixed_buffer_size_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", st_fixed_buffer_size);
पूर्ण
अटल DRIVER_ATTR_RO(fixed_buffer_size);

अटल sमाप_प्रकार max_sg_segs_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", st_max_sg_segs);
पूर्ण
अटल DRIVER_ATTR_RO(max_sg_segs);

अटल sमाप_प्रकार version_show(काष्ठा device_driver *ddd, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "[%s]\n", verstr);
पूर्ण
अटल DRIVER_ATTR_RO(version);

#अगर DEBUG
अटल sमाप_प्रकार debug_flag_store(काष्ठा device_driver *ddp,
	स्थिर अक्षर *buf, माप_प्रकार count)
अणु
/* We only care what the first byte of the data is the rest is unused.
 * अगर it's a '1' we turn on debug and if it's a '0' we disable it. All
 * other values have -EINVAL वापसed अगर they are passed in.
 */
	अगर (count > 0) अणु
		अगर (buf[0] == '0') अणु
			debugging = NO_DEBUG;
			वापस count;
		पूर्ण अन्यथा अगर (buf[0] == '1') अणु
			debugging = 1;
			वापस count;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार debug_flag_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", debugging);
पूर्ण
अटल DRIVER_ATTR_RW(debug_flag);
#पूर्ण_अगर

अटल काष्ठा attribute *st_drv_attrs[] = अणु
	&driver_attr_try_direct_io.attr,
	&driver_attr_fixed_buffer_size.attr,
	&driver_attr_max_sg_segs.attr,
	&driver_attr_version.attr,
#अगर DEBUG
	&driver_attr_debug_flag.attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(st_drv);

/* The sysfs simple class पूर्णांकerface */
अटल sमाप_प्रकार
defined_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);
	sमाप_प्रकार l = 0;

	l = snम_लिखो(buf, PAGE_SIZE, "%d\n", STm->defined);
	वापस l;
पूर्ण
अटल DEVICE_ATTR_RO(defined);

अटल sमाप_प्रकार
शेष_blksize_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);
	sमाप_प्रकार l = 0;

	l = snम_लिखो(buf, PAGE_SIZE, "%d\n", STm->शेष_blksize);
	वापस l;
पूर्ण
अटल DEVICE_ATTR_RO(शेष_blksize);

अटल sमाप_प्रकार
शेष_density_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);
	sमाप_प्रकार l = 0;
	अक्षर *fmt;

	fmt = STm->शेष_density >= 0 ? "0x%02x\n" : "%d\n";
	l = snम_लिखो(buf, PAGE_SIZE, fmt, STm->शेष_density);
	वापस l;
पूर्ण
अटल DEVICE_ATTR_RO(शेष_density);

अटल sमाप_प्रकार
शेष_compression_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);
	sमाप_प्रकार l = 0;

	l = snम_लिखो(buf, PAGE_SIZE, "%d\n", STm->शेष_compression - 1);
	वापस l;
पूर्ण
अटल DEVICE_ATTR_RO(शेष_compression);

अटल sमाप_प्रकार
options_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);
	काष्ठा scsi_tape *STp = STm->tape;
	पूर्णांक options;
	sमाप_प्रकार l = 0;

	options = STm->करो_buffer_ग_लिखोs ? MT_ST_BUFFER_WRITES : 0;
	options |= STm->करो_async_ग_लिखोs ? MT_ST_ASYNC_WRITES : 0;
	options |= STm->करो_पढ़ो_ahead ? MT_ST_READ_AHEAD : 0;
	DEB( options |= debugging ? MT_ST_DEBUGGING : 0 );
	options |= STp->two_fm ? MT_ST_TWO_FM : 0;
	options |= STp->fast_mteom ? MT_ST_FAST_MTEOM : 0;
	options |= STm->शेषs_क्रम_ग_लिखोs ? MT_ST_DEF_WRITES : 0;
	options |= STp->can_bsr ? MT_ST_CAN_BSR : 0;
	options |= STp->omit_blklims ? MT_ST_NO_BLKLIMS : 0;
	options |= STp->can_partitions ? MT_ST_CAN_PARTITIONS : 0;
	options |= STp->scsi2_logical ? MT_ST_SCSI2LOGICAL : 0;
	options |= STm->sysv ? MT_ST_SYSV : 0;
	options |= STp->immediate ? MT_ST_NOWAIT : 0;
	options |= STp->immediate_filemark ? MT_ST_NOWAIT_खातापूर्ण : 0;
	options |= STp->sili ? MT_ST_SILI : 0;

	l = snम_लिखो(buf, PAGE_SIZE, "0x%08x\n", options);
	वापस l;
पूर्ण
अटल DEVICE_ATTR_RO(options);

/* Support क्रम tape stats */

/**
 * पढ़ो_cnt_show - वापस पढ़ो count - count of पढ़ोs made from tape drive
 * @dev: काष्ठा device
 * @attr: attribute काष्ठाure
 * @buf: buffer to वापस क्रमmatted data in
 */
अटल sमाप_प्रकार पढ़ो_cnt_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lld",
		       (दीर्घ दीर्घ)atomic64_पढ़ो(&STm->tape->stats->पढ़ो_cnt));
पूर्ण
अटल DEVICE_ATTR_RO(पढ़ो_cnt);

/**
 * पढ़ो_byte_cnt_show - वापस पढ़ो byte count - tape drives
 * may use blocks less than 512 bytes this gives the raw byte count of
 * of data पढ़ो from the tape drive.
 * @dev: काष्ठा device
 * @attr: attribute काष्ठाure
 * @buf: buffer to वापस क्रमmatted data in
 */
अटल sमाप_प्रकार पढ़ो_byte_cnt_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lld",
		       (दीर्घ दीर्घ)atomic64_पढ़ो(&STm->tape->stats->पढ़ो_byte_cnt));
पूर्ण
अटल DEVICE_ATTR_RO(पढ़ो_byte_cnt);

/**
 * पढ़ो_ns_show - वापस पढ़ो ns - overall समय spent रुकोing on पढ़ोs in ns.
 * @dev: काष्ठा device
 * @attr: attribute काष्ठाure
 * @buf: buffer to वापस क्रमmatted data in
 */
अटल sमाप_प्रकार पढ़ो_ns_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lld",
		       (दीर्घ दीर्घ)atomic64_पढ़ो(&STm->tape->stats->tot_पढ़ो_समय));
पूर्ण
अटल DEVICE_ATTR_RO(पढ़ो_ns);

/**
 * ग_लिखो_cnt_show - ग_लिखो count - number of user calls
 * to ग_लिखो(2) that have written data to tape.
 * @dev: काष्ठा device
 * @attr: attribute काष्ठाure
 * @buf: buffer to वापस क्रमmatted data in
 */
अटल sमाप_प्रकार ग_लिखो_cnt_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lld",
		       (दीर्घ दीर्घ)atomic64_पढ़ो(&STm->tape->stats->ग_लिखो_cnt));
पूर्ण
अटल DEVICE_ATTR_RO(ग_लिखो_cnt);

/**
 * ग_लिखो_byte_cnt_show - ग_लिखो byte count - raw count of
 * bytes written to tape.
 * @dev: काष्ठा device
 * @attr: attribute काष्ठाure
 * @buf: buffer to वापस क्रमmatted data in
 */
अटल sमाप_प्रकार ग_लिखो_byte_cnt_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lld",
		       (दीर्घ दीर्घ)atomic64_पढ़ो(&STm->tape->stats->ग_लिखो_byte_cnt));
पूर्ण
अटल DEVICE_ATTR_RO(ग_लिखो_byte_cnt);

/**
 * ग_लिखो_ns_show - ग_लिखो ns - number of nanoseconds रुकोing on ग_लिखो
 * requests to complete.
 * @dev: काष्ठा device
 * @attr: attribute काष्ठाure
 * @buf: buffer to वापस क्रमmatted data in
 */
अटल sमाप_प्रकार ग_लिखो_ns_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lld",
		       (दीर्घ दीर्घ)atomic64_पढ़ो(&STm->tape->stats->tot_ग_लिखो_समय));
पूर्ण
अटल DEVICE_ATTR_RO(ग_लिखो_ns);

/**
 * in_flight_show - number of I/Os currently in flight -
 * in most हालs this will be either 0 or 1. It may be higher अगर someone
 * has also issued other SCSI commands such as via an ioctl.
 * @dev: काष्ठा device
 * @attr: attribute काष्ठाure
 * @buf: buffer to वापस क्रमmatted data in
 */
अटल sमाप_प्रकार in_flight_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lld",
		       (दीर्घ दीर्घ)atomic64_पढ़ो(&STm->tape->stats->in_flight));
पूर्ण
अटल DEVICE_ATTR_RO(in_flight);

/**
 * io_ns_show - io रुको ns - this is the number of ns spent
 * रुकोing on all I/O to complete. This includes tape movement commands
 * such as शुरुआतing, seeking to end of file or tape, it also includes
 * पढ़ो and ग_लिखो. To determine the समय spent on tape movement
 * subtract the पढ़ो and ग_लिखो ns from this value.
 * @dev: काष्ठा device
 * @attr: attribute काष्ठाure
 * @buf: buffer to वापस क्रमmatted data in
 */
अटल sमाप_प्रकार io_ns_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lld",
		       (दीर्घ दीर्घ)atomic64_पढ़ो(&STm->tape->stats->tot_io_समय));
पूर्ण
अटल DEVICE_ATTR_RO(io_ns);

/**
 * other_cnt_show - other io count - this is the number of
 * I/O requests other than पढ़ो and ग_लिखो requests.
 * Typically these are tape movement requests but will include driver
 * tape movement. This includes only requests issued by the st driver.
 * @dev: काष्ठा device
 * @attr: attribute काष्ठाure
 * @buf: buffer to वापस क्रमmatted data in
 */
अटल sमाप_प्रकार other_cnt_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lld",
		       (दीर्घ दीर्घ)atomic64_पढ़ो(&STm->tape->stats->other_cnt));
पूर्ण
अटल DEVICE_ATTR_RO(other_cnt);

/**
 * resid_cnt_show - A count of the number of बार we get a residual
 * count - this should indicate someone issuing पढ़ोs larger than the
 * block size on tape.
 * @dev: काष्ठा device
 * @attr: attribute काष्ठाure
 * @buf: buffer to वापस क्रमmatted data in
 */
अटल sमाप_प्रकार resid_cnt_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा st_modedef *STm = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lld",
		       (दीर्घ दीर्घ)atomic64_पढ़ो(&STm->tape->stats->resid_cnt));
पूर्ण
अटल DEVICE_ATTR_RO(resid_cnt);

अटल काष्ठा attribute *st_dev_attrs[] = अणु
	&dev_attr_defined.attr,
	&dev_attr_शेष_blksize.attr,
	&dev_attr_शेष_density.attr,
	&dev_attr_शेष_compression.attr,
	&dev_attr_options.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *st_stats_attrs[] = अणु
	&dev_attr_पढ़ो_cnt.attr,
	&dev_attr_पढ़ो_byte_cnt.attr,
	&dev_attr_पढ़ो_ns.attr,
	&dev_attr_ग_लिखो_cnt.attr,
	&dev_attr_ग_लिखो_byte_cnt.attr,
	&dev_attr_ग_लिखो_ns.attr,
	&dev_attr_in_flight.attr,
	&dev_attr_io_ns.attr,
	&dev_attr_other_cnt.attr,
	&dev_attr_resid_cnt.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group stats_group = अणु
	.name = "stats",
	.attrs = st_stats_attrs,
पूर्ण;

अटल काष्ठा attribute_group st_group = अणु
	.attrs = st_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *st_dev_groups[] = अणु
	&st_group,
	&stats_group,
	शून्य,
पूर्ण;

/* The following functions may be useful क्रम a larger audience. */
अटल पूर्णांक sgl_map_user_pages(काष्ठा st_buffer *STbp,
			      स्थिर अचिन्हित पूर्णांक max_pages, अचिन्हित दीर्घ uaddr,
			      माप_प्रकार count, पूर्णांक rw)
अणु
	अचिन्हित दीर्घ end = (uaddr + count + PAGE_SIZE - 1) >> PAGE_SHIFT;
	अचिन्हित दीर्घ start = uaddr >> PAGE_SHIFT;
	स्थिर पूर्णांक nr_pages = end - start;
	पूर्णांक res, i;
	काष्ठा page **pages;
	काष्ठा rq_map_data *mdata = &STbp->map_data;

	/* User attempted Overflow! */
	अगर ((uaddr + count) < uaddr)
		वापस -EINVAL;

	/* Too big */
        अगर (nr_pages > max_pages)
		वापस -ENOMEM;

	/* Hmm? */
	अगर (count == 0)
		वापस 0;

	pages = kदो_स्मृति_array(max_pages, माप(*pages), GFP_KERNEL);
	अगर (pages == शून्य)
		वापस -ENOMEM;

        /* Try to fault in all of the necessary pages */
        /* rw==READ means पढ़ो from drive, ग_लिखो पूर्णांकo memory area */
	res = pin_user_pages_fast(uaddr, nr_pages, rw == READ ? FOLL_WRITE : 0,
				  pages);

	/* Errors and no page mapped should वापस here */
	अगर (res < nr_pages)
		जाओ out_unmap;

        क्रम (i=0; i < nr_pages; i++) अणु
                /* FIXME: flush superflous क्रम rw==READ,
                 * probably wrong function क्रम rw==WRITE
                 */
		flush_dcache_page(pages[i]);
        पूर्ण

	mdata->offset = uaddr & ~PAGE_MASK;
	STbp->mapped_pages = pages;

	वापस nr_pages;
 out_unmap:
	अगर (res > 0) अणु
		unpin_user_pages(pages, res);
		res = 0;
	पूर्ण
	kमुक्त(pages);
	वापस res;
पूर्ण


/* And unmap them... */
अटल पूर्णांक sgl_unmap_user_pages(काष्ठा st_buffer *STbp,
				स्थिर अचिन्हित पूर्णांक nr_pages, पूर्णांक dirtied)
अणु
	/* FIXME: cache flush missing क्रम rw==READ */
	unpin_user_pages_dirty_lock(STbp->mapped_pages, nr_pages, dirtied);

	kमुक्त(STbp->mapped_pages);
	STbp->mapped_pages = शून्य;

	वापस 0;
पूर्ण
