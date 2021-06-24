<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 * Based on.......: linux/drivers/s390/block/mdisk.c
 * ...............: by Harपंचांगunt Penner <hpenner@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2000
 *
 */

#घोषणा KMSG_COMPONENT "dasd"

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/bपन.स>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>

#समावेश <यंत्र/dasd.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/vtoc.h>

#समावेश "dasd_int.h"
#समावेश "dasd_diag.h"

#घोषणा PRINTK_HEADER "dasd(diag):"

MODULE_LICENSE("GPL");

/* The maximum number of blocks per request (max_blocks) is dependent on the
 * amount of storage that is available in the अटल I/O buffer क्रम each
 * device. Currently each device माला_लो 2 pages. We want to fit two requests
 * पूर्णांकo the available memory so that we can immediately start the next अगर one
 * finishes. */
#घोषणा DIAG_MAX_BLOCKS	(((2 * PAGE_SIZE - माप(काष्ठा dasd_ccw_req) - \
			   माप(काष्ठा dasd_diag_req)) / \
		           माप(काष्ठा dasd_diag_bio)) / 2)
#घोषणा DIAG_MAX_RETRIES	32
#घोषणा DIAG_TIMEOUT		50

अटल काष्ठा dasd_discipline dasd_diag_discipline;

काष्ठा dasd_diag_निजी अणु
	काष्ठा dasd_diag_अक्षरacteristics rdc_data;
	काष्ठा dasd_diag_rw_io iob;
	काष्ठा dasd_diag_init_io iib;
	blocknum_t pt_block;
	काष्ठा ccw_dev_id dev_id;
पूर्ण;

काष्ठा dasd_diag_req अणु
	अचिन्हित पूर्णांक block_count;
	काष्ठा dasd_diag_bio bio[];
पूर्ण;

अटल स्थिर u8 DASD_DIAG_CMS1[] = अणु 0xc3, 0xd4, 0xe2, 0xf1 पूर्ण;/* EBCDIC CMS1 */

/* Perक्रमm DIAG250 call with block I/O parameter list iob (input and output)
 * and function code cmd.
 * In हाल of an exception वापस 3. Otherwise वापस result of bitwise OR of
 * resulting condition code and DIAG वापस code. */
अटल अंतरभूत पूर्णांक __dia250(व्योम *iob, पूर्णांक cmd)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg2 यंत्र ("2") = (अचिन्हित दीर्घ) iob;
	प्रकार जोड़ अणु
		काष्ठा dasd_diag_init_io init_io;
		काष्ठा dasd_diag_rw_io rw_io;
	पूर्ण addr_type;
	पूर्णांक rc;

	rc = 3;
	यंत्र अस्थिर(
		"	diag	2,%2,0x250\n"
		"0:	ipm	%0\n"
		"	srl	%0,28\n"
		"	or	%0,3\n"
		"1:\n"
		EX_TABLE(0b,1b)
		: "+d" (rc), "=m" (*(addr_type *) iob)
		: "d" (cmd), "d" (reg2), "m" (*(addr_type *) iob)
		: "3", "cc");
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक dia250(व्योम *iob, पूर्णांक cmd)
अणु
	diag_stat_inc(DIAG_STAT_X250);
	वापस __dia250(iob, cmd);
पूर्ण

/* Initialize block I/O to DIAG device using the specअगरied blocksize and
 * block offset. On success, वापस zero and set end_block to contain the
 * number of blocks on the device minus the specअगरied offset. Return non-zero
 * otherwise. */
अटल अंतरभूत पूर्णांक
mdsk_init_io(काष्ठा dasd_device *device, अचिन्हित पूर्णांक blocksize,
	     blocknum_t offset, blocknum_t *end_block)
अणु
	काष्ठा dasd_diag_निजी *निजी = device->निजी;
	काष्ठा dasd_diag_init_io *iib = &निजी->iib;
	पूर्णांक rc;

	स_रखो(iib, 0, माप (काष्ठा dasd_diag_init_io));

	iib->dev_nr = निजी->dev_id.devno;
	iib->block_size = blocksize;
	iib->offset = offset;
	iib->flaga = DASD_DIAG_FLAGA_DEFAULT;

	rc = dia250(iib, INIT_BIO);

	अगर ((rc & 3) == 0 && end_block)
		*end_block = iib->end_block;

	वापस rc;
पूर्ण

/* Remove block I/O environment क्रम device. Return zero on success, non-zero
 * otherwise. */
अटल अंतरभूत पूर्णांक
mdsk_term_io(काष्ठा dasd_device * device)
अणु
	काष्ठा dasd_diag_निजी *निजी = device->निजी;
	काष्ठा dasd_diag_init_io *iib = &निजी->iib;
	पूर्णांक rc;

	स_रखो(iib, 0, माप (काष्ठा dasd_diag_init_io));
	iib->dev_nr = निजी->dev_id.devno;
	rc = dia250(iib, TERM_BIO);
	वापस rc;
पूर्ण

/* Error recovery क्रम failed DIAG requests - try to reestablish the DIAG
 * environment. */
अटल व्योम
dasd_diag_erp(काष्ठा dasd_device *device)
अणु
	पूर्णांक rc;

	mdsk_term_io(device);
	rc = mdsk_init_io(device, device->block->bp_block, 0, शून्य);
	अगर (rc == 4) अणु
		अगर (!(test_and_set_bit(DASD_FLAG_DEVICE_RO, &device->flags)))
			pr_warn("%s: The access mode of a DIAG device changed to read-only\n",
				dev_name(&device->cdev->dev));
		rc = 0;
	पूर्ण
	अगर (rc)
		pr_warn("%s: DIAG ERP failed with rc=%d\n",
			dev_name(&device->cdev->dev), rc);
पूर्ण

/* Start a given request at the device. Return zero on success, non-zero
 * otherwise. */
अटल पूर्णांक
dasd_start_diag(काष्ठा dasd_ccw_req * cqr)
अणु
	काष्ठा dasd_device *device;
	काष्ठा dasd_diag_निजी *निजी;
	काष्ठा dasd_diag_req *dreq;
	पूर्णांक rc;

	device = cqr->startdev;
	अगर (cqr->retries < 0) अणु
		DBF_DEV_EVENT(DBF_ERR, device, "DIAG start_IO: request %p "
			    "- no retry left)", cqr);
		cqr->status = DASD_CQR_ERROR;
		वापस -EIO;
	पूर्ण
	निजी = device->निजी;
	dreq = cqr->data;

	निजी->iob.dev_nr = निजी->dev_id.devno;
	निजी->iob.key = 0;
	निजी->iob.flags = DASD_DIAG_RWFLAG_ASYNC;
	निजी->iob.block_count = dreq->block_count;
	निजी->iob.पूर्णांकerrupt_params = (addr_t) cqr;
	निजी->iob.bio_list = dreq->bio;
	निजी->iob.flaga = DASD_DIAG_FLAGA_DEFAULT;

	cqr->startclk = get_tod_घड़ी();
	cqr->startसमय = jअगरfies;
	cqr->retries--;

	rc = dia250(&निजी->iob, RW_BIO);
	चयन (rc) अणु
	हाल 0: /* Synchronous I/O finished successfully */
		cqr->stopclk = get_tod_घड़ी();
		cqr->status = DASD_CQR_SUCCESS;
		/* Indicate to calling function that only a dasd_schedule_bh()
		   and no समयr is needed */
                rc = -EACCES;
		अवरोध;
	हाल 8: /* Asynchronous I/O was started */
		cqr->status = DASD_CQR_IN_IO;
		rc = 0;
		अवरोध;
	शेष: /* Error condition */
		cqr->status = DASD_CQR_QUEUED;
		DBF_DEV_EVENT(DBF_WARNING, device, "dia250 returned rc=%d", rc);
		dasd_diag_erp(device);
		rc = -EIO;
		अवरोध;
	पूर्ण
	cqr->पूर्णांकrc = rc;
	वापस rc;
पूर्ण

/* Terminate given request at the device. */
अटल पूर्णांक
dasd_diag_term_IO(काष्ठा dasd_ccw_req * cqr)
अणु
	काष्ठा dasd_device *device;

	device = cqr->startdev;
	mdsk_term_io(device);
	mdsk_init_io(device, device->block->bp_block, 0, शून्य);
	cqr->status = DASD_CQR_CLEAR_PENDING;
	cqr->stopclk = get_tod_घड़ी();
	dasd_schedule_device_bh(device);
	वापस 0;
पूर्ण

/* Handle बाह्यal पूर्णांकerruption. */
अटल व्योम dasd_ext_handler(काष्ठा ext_code ext_code,
			     अचिन्हित पूर्णांक param32, अचिन्हित दीर्घ param64)
अणु
	काष्ठा dasd_ccw_req *cqr, *next;
	काष्ठा dasd_device *device;
	अचिन्हित दीर्घ expires;
	अचिन्हित दीर्घ flags;
	addr_t ip;
	पूर्णांक rc;

	चयन (ext_code.subcode >> 8) अणु
	हाल DASD_DIAG_CODE_31BIT:
		ip = (addr_t) param32;
		अवरोध;
	हाल DASD_DIAG_CODE_64BIT:
		ip = (addr_t) param64;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	inc_irq_stat(IRQEXT_DSD);
	अगर (!ip) अणु		/* no पूर्णांकparm: unsolicited पूर्णांकerrupt */
		DBF_EVENT(DBF_NOTICE, "%s", "caught unsolicited "
			      "interrupt");
		वापस;
	पूर्ण
	cqr = (काष्ठा dasd_ccw_req *) ip;
	device = (काष्ठा dasd_device *) cqr->startdev;
	अगर (म_भेदन(device->discipline->ebcname, (अक्षर *) &cqr->magic, 4)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device,
			    " magic number of dasd_ccw_req 0x%08X doesn't"
			    " match discipline 0x%08X",
			    cqr->magic, *(पूर्णांक *) (&device->discipline->name));
		वापस;
	पूर्ण

	/* get irq lock to modअगरy request queue */
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);

	/* Check क्रम a pending clear operation */
	अगर (cqr->status == DASD_CQR_CLEAR_PENDING) अणु
		cqr->status = DASD_CQR_CLEARED;
		dasd_device_clear_समयr(device);
		dasd_schedule_device_bh(device);
		spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
		वापस;
	पूर्ण

	cqr->stopclk = get_tod_घड़ी();

	expires = 0;
	अगर ((ext_code.subcode & 0xff) == 0) अणु
		cqr->status = DASD_CQR_SUCCESS;
		/* Start first request on queue अगर possible -> fast_io. */
		अगर (!list_empty(&device->ccw_queue)) अणु
			next = list_entry(device->ccw_queue.next,
					  काष्ठा dasd_ccw_req, devlist);
			अगर (next->status == DASD_CQR_QUEUED) अणु
				rc = dasd_start_diag(next);
				अगर (rc == 0)
					expires = next->expires;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		cqr->status = DASD_CQR_QUEUED;
		DBF_DEV_EVENT(DBF_DEBUG, device, "interrupt status for "
			      "request %p was %d (%d retries left)", cqr,
			      ext_code.subcode & 0xff, cqr->retries);
		dasd_diag_erp(device);
	पूर्ण

	अगर (expires != 0)
		dasd_device_set_समयr(device, expires);
	अन्यथा
		dasd_device_clear_समयr(device);
	dasd_schedule_device_bh(device);

	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
पूर्ण

/* Check whether device can be controlled by DIAG discipline. Return zero on
 * success, non-zero otherwise. */
अटल पूर्णांक
dasd_diag_check_device(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_diag_निजी *निजी = device->निजी;
	काष्ठा dasd_diag_अक्षरacteristics *rdc_data;
	काष्ठा vtoc_cms_label *label;
	काष्ठा dasd_block *block;
	काष्ठा dasd_diag_bio *bio;
	अचिन्हित पूर्णांक sb, bsize;
	blocknum_t end_block;
	पूर्णांक rc;

	अगर (निजी == शून्य) अणु
		निजी = kzalloc(माप(*निजी), GFP_KERNEL);
		अगर (निजी == शून्य) अणु
			DBF_DEV_EVENT(DBF_WARNING, device, "%s",
				"Allocating memory for private DASD data "
				      "failed\n");
			वापस -ENOMEM;
		पूर्ण
		ccw_device_get_id(device->cdev, &निजी->dev_id);
		device->निजी = निजी;
	पूर्ण
	block = dasd_alloc_block();
	अगर (IS_ERR(block)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "could not allocate dasd block structure");
		device->निजी = शून्य;
		kमुक्त(निजी);
		वापस PTR_ERR(block);
	पूर्ण
	device->block = block;
	block->base = device;

	/* Read Device Characteristics */
	rdc_data = &निजी->rdc_data;
	rdc_data->dev_nr = निजी->dev_id.devno;
	rdc_data->rdc_len = माप (काष्ठा dasd_diag_अक्षरacteristics);

	rc = diag210((काष्ठा diag210 *) rdc_data);
	अगर (rc) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "failed to retrieve device "
			    "information (rc=%d)", rc);
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	device->शेष_expires = DIAG_TIMEOUT;
	device->शेष_retries = DIAG_MAX_RETRIES;

	/* Figure out position of label block */
	चयन (निजी->rdc_data.vdev_class) अणु
	हाल DEV_CLASS_FBA:
		निजी->pt_block = 1;
		अवरोध;
	हाल DEV_CLASS_ECKD:
		निजी->pt_block = 2;
		अवरोध;
	शेष:
		pr_warn("%s: Device type %d is not supported in DIAG mode\n",
			dev_name(&device->cdev->dev),
			निजी->rdc_data.vdev_class);
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	DBF_DEV_EVENT(DBF_INFO, device,
		      "%04X: %04X on real %04X/%02X",
		      rdc_data->dev_nr,
		      rdc_data->vdev_type,
		      rdc_data->rdev_type, rdc_data->rdev_model);

	/* terminate all outstanding operations */
	mdsk_term_io(device);

	/* figure out blocksize of device */
	label = (काष्ठा vtoc_cms_label *) get_zeroed_page(GFP_KERNEL);
	अगर (label == शून्य)  अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "No memory to allocate initialization request");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	bio = kzalloc(माप(*bio), GFP_KERNEL);
	अगर (bio == शून्य)  अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "No memory to allocate initialization bio");
		rc = -ENOMEM;
		जाओ out_label;
	पूर्ण
	rc = 0;
	end_block = 0;
	/* try all sizes - needed क्रम ECKD devices */
	क्रम (bsize = 512; bsize <= PAGE_SIZE; bsize <<= 1) अणु
		mdsk_init_io(device, bsize, 0, &end_block);
		स_रखो(bio, 0, माप(*bio));
		bio->type = MDSK_READ_REQ;
		bio->block_number = निजी->pt_block + 1;
		bio->buffer = label;
		स_रखो(&निजी->iob, 0, माप (काष्ठा dasd_diag_rw_io));
		निजी->iob.dev_nr = rdc_data->dev_nr;
		निजी->iob.key = 0;
		निजी->iob.flags = 0;	/* करो synchronous io */
		निजी->iob.block_count = 1;
		निजी->iob.पूर्णांकerrupt_params = 0;
		निजी->iob.bio_list = bio;
		निजी->iob.flaga = DASD_DIAG_FLAGA_DEFAULT;
		rc = dia250(&निजी->iob, RW_BIO);
		अगर (rc == 3) अणु
			pr_warn("%s: A 64-bit DIAG call failed\n",
				dev_name(&device->cdev->dev));
			rc = -EOPNOTSUPP;
			जाओ out_bio;
		पूर्ण
		mdsk_term_io(device);
		अगर (rc == 0)
			अवरोध;
	पूर्ण
	अगर (bsize > PAGE_SIZE) अणु
		pr_warn("%s: Accessing the DASD failed because of an incorrect format (rc=%d)\n",
			dev_name(&device->cdev->dev), rc);
		rc = -EIO;
		जाओ out_bio;
	पूर्ण
	/* check क्रम label block */
	अगर (स_भेद(label->label_id, DASD_DIAG_CMS1,
		  माप(DASD_DIAG_CMS1)) == 0) अणु
		/* get क्रमmatted blocksize from label block */
		bsize = (अचिन्हित पूर्णांक) label->block_size;
		block->blocks = (अचिन्हित दीर्घ) label->block_count;
	पूर्ण अन्यथा
		block->blocks = end_block;
	block->bp_block = bsize;
	block->s2b_shअगरt = 0;	/* bits to shअगरt 512 to get a block */
	क्रम (sb = 512; sb < bsize; sb = sb << 1)
		block->s2b_shअगरt++;
	rc = mdsk_init_io(device, block->bp_block, 0, शून्य);
	अगर (rc && (rc != 4)) अणु
		pr_warn("%s: DIAG initialization failed with rc=%d\n",
			dev_name(&device->cdev->dev), rc);
		rc = -EIO;
	पूर्ण अन्यथा अणु
		अगर (rc == 4)
			set_bit(DASD_FLAG_DEVICE_RO, &device->flags);
		pr_info("%s: New DASD with %ld byte/block, total size %ld "
			"KB%s\n", dev_name(&device->cdev->dev),
			(अचिन्हित दीर्घ) block->bp_block,
			(अचिन्हित दीर्घ) (block->blocks <<
					 block->s2b_shअगरt) >> 1,
			(rc == 4) ? ", read-only device" : "");
		rc = 0;
	पूर्ण
out_bio:
	kमुक्त(bio);
out_label:
	मुक्त_page((दीर्घ) label);
out:
	अगर (rc) अणु
		device->block = शून्य;
		dasd_मुक्त_block(block);
		device->निजी = शून्य;
		kमुक्त(निजी);
	पूर्ण
	वापस rc;
पूर्ण

/* Fill in भव disk geometry क्रम device. Return zero on success, non-zero
 * otherwise. */
अटल पूर्णांक
dasd_diag_fill_geometry(काष्ठा dasd_block *block, काष्ठा hd_geometry *geo)
अणु
	अगर (dasd_check_blocksize(block->bp_block) != 0)
		वापस -EINVAL;
	geo->cylinders = (block->blocks << block->s2b_shअगरt) >> 10;
	geo->heads = 16;
	geo->sectors = 128 >> block->s2b_shअगरt;
	वापस 0;
पूर्ण

अटल dasd_erp_fn_t
dasd_diag_erp_action(काष्ठा dasd_ccw_req * cqr)
अणु
	वापस dasd_शेष_erp_action;
पूर्ण

अटल dasd_erp_fn_t
dasd_diag_erp_postaction(काष्ठा dasd_ccw_req * cqr)
अणु
	वापस dasd_शेष_erp_postaction;
पूर्ण

/* Create DASD request from block device request. Return poपूर्णांकer to new
 * request on success, ERR_PTR otherwise. */
अटल काष्ठा dasd_ccw_req *dasd_diag_build_cp(काष्ठा dasd_device *memdev,
					       काष्ठा dasd_block *block,
					       काष्ठा request *req)
अणु
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा dasd_diag_req *dreq;
	काष्ठा dasd_diag_bio *dbio;
	काष्ठा req_iterator iter;
	काष्ठा bio_vec bv;
	अक्षर *dst;
	अचिन्हित पूर्णांक count;
	sector_t recid, first_rec, last_rec;
	अचिन्हित पूर्णांक blksize, off;
	अचिन्हित अक्षर rw_cmd;

	अगर (rq_data_dir(req) == READ)
		rw_cmd = MDSK_READ_REQ;
	अन्यथा अगर (rq_data_dir(req) == WRITE)
		rw_cmd = MDSK_WRITE_REQ;
	अन्यथा
		वापस ERR_PTR(-EINVAL);
	blksize = block->bp_block;
	/* Calculate record id of first and last block. */
	first_rec = blk_rq_pos(req) >> block->s2b_shअगरt;
	last_rec =
		(blk_rq_pos(req) + blk_rq_sectors(req) - 1) >> block->s2b_shअगरt;
	/* Check काष्ठा bio and count the number of blocks क्रम the request. */
	count = 0;
	rq_क्रम_each_segment(bv, req, iter) अणु
		अगर (bv.bv_len & (blksize - 1))
			/* Fba can only करो full blocks. */
			वापस ERR_PTR(-EINVAL);
		count += bv.bv_len >> (block->s2b_shअगरt + 9);
	पूर्ण
	/* Paranoia. */
	अगर (count != last_rec - first_rec + 1)
		वापस ERR_PTR(-EINVAL);
	/* Build the request */
	cqr = dasd_sदो_स्मृति_request(DASD_DIAG_MAGIC, 0, काष्ठा_size(dreq, bio, count),
				   memdev, blk_mq_rq_to_pdu(req));
	अगर (IS_ERR(cqr))
		वापस cqr;

	dreq = (काष्ठा dasd_diag_req *) cqr->data;
	dreq->block_count = count;
	dbio = dreq->bio;
	recid = first_rec;
	rq_क्रम_each_segment(bv, req, iter) अणु
		dst = page_address(bv.bv_page) + bv.bv_offset;
		क्रम (off = 0; off < bv.bv_len; off += blksize) अणु
			स_रखो(dbio, 0, माप (काष्ठा dasd_diag_bio));
			dbio->type = rw_cmd;
			dbio->block_number = recid + 1;
			dbio->buffer = dst;
			dbio++;
			dst += blksize;
			recid++;
		पूर्ण
	पूर्ण
	cqr->retries = memdev->शेष_retries;
	cqr->buildclk = get_tod_घड़ी();
	अगर (blk_noretry_request(req) ||
	    block->base->features & DASD_FEATURE_FAILFAST)
		set_bit(DASD_CQR_FLAGS_FAILFAST, &cqr->flags);
	cqr->startdev = memdev;
	cqr->memdev = memdev;
	cqr->block = block;
	cqr->expires = memdev->शेष_expires * HZ;
	cqr->status = DASD_CQR_FILLED;
	वापस cqr;
पूर्ण

/* Release DASD request. Return non-zero अगर request was successful, zero
 * otherwise. */
अटल पूर्णांक
dasd_diag_मुक्त_cp(काष्ठा dasd_ccw_req *cqr, काष्ठा request *req)
अणु
	पूर्णांक status;

	status = cqr->status == DASD_CQR_DONE;
	dasd_sमुक्त_request(cqr, cqr->memdev);
	वापस status;
पूर्ण

अटल व्योम dasd_diag_handle_terminated_request(काष्ठा dasd_ccw_req *cqr)
अणु
	अगर (cqr->retries < 0)
		cqr->status = DASD_CQR_FAILED;
	अन्यथा
		cqr->status = DASD_CQR_FILLED;
पूर्ण;

/* Fill in IOCTL data क्रम device. */
अटल पूर्णांक
dasd_diag_fill_info(काष्ठा dasd_device * device,
		    काष्ठा dasd_inक्रमmation2_t * info)
अणु
	काष्ठा dasd_diag_निजी *निजी = device->निजी;

	info->label_block = (अचिन्हित पूर्णांक) निजी->pt_block;
	info->FBA_layout = 1;
	info->क्रमmat = DASD_FORMAT_LDL;
	info->अक्षरacteristics_size = माप(निजी->rdc_data);
	स_नकल(info->अक्षरacteristics, &निजी->rdc_data,
	       माप(निजी->rdc_data));
	info->confdata_size = 0;
	वापस 0;
पूर्ण

अटल व्योम
dasd_diag_dump_sense(काष्ठा dasd_device *device, काष्ठा dasd_ccw_req * req,
		     काष्ठा irb *stat)
अणु
	DBF_DEV_EVENT(DBF_WARNING, device, "%s",
		    "dump sense not available for DIAG data");
पूर्ण

/*
 * Initialize block layer request queue.
 */
अटल व्योम dasd_diag_setup_blk_queue(काष्ठा dasd_block *block)
अणु
	अचिन्हित पूर्णांक logical_block_size = block->bp_block;
	काष्ठा request_queue *q = block->request_queue;
	पूर्णांक max;

	max = DIAG_MAX_BLOCKS << block->s2b_shअगरt;
	blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
	q->limits.max_dev_sectors = max;
	blk_queue_logical_block_size(q, logical_block_size);
	blk_queue_max_hw_sectors(q, max);
	blk_queue_max_segments(q, अच_लघु_उच्च);
	/* With page sized segments each segment can be translated पूर्णांकo one idaw/tidaw */
	blk_queue_max_segment_size(q, PAGE_SIZE);
	blk_queue_segment_boundary(q, PAGE_SIZE - 1);
पूर्ण

अटल पूर्णांक dasd_diag_pe_handler(काष्ठा dasd_device *device,
				__u8 tbvpm, __u8 fcsecpm)
अणु
	वापस dasd_generic_verअगरy_path(device, tbvpm);
पूर्ण

अटल काष्ठा dasd_discipline dasd_diag_discipline = अणु
	.owner = THIS_MODULE,
	.name = "DIAG",
	.ebcname = "DIAG",
	.check_device = dasd_diag_check_device,
	.pe_handler = dasd_diag_pe_handler,
	.fill_geometry = dasd_diag_fill_geometry,
	.setup_blk_queue = dasd_diag_setup_blk_queue,
	.start_IO = dasd_start_diag,
	.term_IO = dasd_diag_term_IO,
	.handle_terminated_request = dasd_diag_handle_terminated_request,
	.erp_action = dasd_diag_erp_action,
	.erp_postaction = dasd_diag_erp_postaction,
	.build_cp = dasd_diag_build_cp,
	.मुक्त_cp = dasd_diag_मुक्त_cp,
	.dump_sense = dasd_diag_dump_sense,
	.fill_info = dasd_diag_fill_info,
पूर्ण;

अटल पूर्णांक __init
dasd_diag_init(व्योम)
अणु
	अगर (!MACHINE_IS_VM) अणु
		pr_info("Discipline %s cannot be used without z/VM\n",
			dasd_diag_discipline.name);
		वापस -ENODEV;
	पूर्ण
	ASCEBC(dasd_diag_discipline.ebcname, 4);

	irq_subclass_रेजिस्टर(IRQ_SUBCLASS_SERVICE_SIGNAL);
	रेजिस्टर_बाह्यal_irq(EXT_IRQ_CP_SERVICE, dasd_ext_handler);
	dasd_diag_discipline_poपूर्णांकer = &dasd_diag_discipline;
	वापस 0;
पूर्ण

अटल व्योम __निकास
dasd_diag_cleanup(व्योम)
अणु
	unरेजिस्टर_बाह्यal_irq(EXT_IRQ_CP_SERVICE, dasd_ext_handler);
	irq_subclass_unरेजिस्टर(IRQ_SUBCLASS_SERVICE_SIGNAL);
	dasd_diag_discipline_poपूर्णांकer = शून्य;
पूर्ण

module_init(dasd_diag_init);
module_निकास(dasd_diag_cleanup);
