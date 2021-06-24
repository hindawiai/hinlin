<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Basic HP/COMPAQ MSA 1000 support. This is only needed अगर your HW cannot be
 * upgraded.
 *
 * Copyright (C) 2006 Red Hat, Inc.  All rights reserved.
 * Copyright (C) 2006 Mike Christie
 * Copyright (C) 2008 Hannes Reinecke <hare@suse.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_dh.h>

#घोषणा HP_SW_NAME			"hp_sw"

#घोषणा HP_SW_TIMEOUT			(60 * HZ)
#घोषणा HP_SW_RETRIES			3

#घोषणा HP_SW_PATH_UNINITIALIZED	-1
#घोषणा HP_SW_PATH_ACTIVE		0
#घोषणा HP_SW_PATH_PASSIVE		1

काष्ठा hp_sw_dh_data अणु
	पूर्णांक path_state;
	पूर्णांक retries;
	पूर्णांक retry_cnt;
	काष्ठा scsi_device *sdev;
पूर्ण;

अटल पूर्णांक hp_sw_start_stop(काष्ठा hp_sw_dh_data *);

/*
 * tur_करोne - Handle TEST UNIT READY वापस status
 * @sdev: sdev the command has been sent to
 * @errors: blk error code
 *
 * Returns SCSI_DH_DEV_OFFLINED अगर the sdev is on the passive path
 */
अटल पूर्णांक tur_करोne(काष्ठा scsi_device *sdev, काष्ठा hp_sw_dh_data *h,
		    काष्ठा scsi_sense_hdr *sshdr)
अणु
	पूर्णांक ret = SCSI_DH_IO;

	चयन (sshdr->sense_key) अणु
	हाल UNIT_ATTENTION:
		ret = SCSI_DH_IMM_RETRY;
		अवरोध;
	हाल NOT_READY:
		अगर (sshdr->asc == 0x04 && sshdr->ascq == 2) अणु
			/*
			 * LUN not पढ़ोy - Initialization command required
			 *
			 * This is the passive path
			 */
			h->path_state = HP_SW_PATH_PASSIVE;
			ret = SCSI_DH_OK;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		sdev_prपूर्णांकk(KERN_WARNING, sdev,
			   "%s: sending tur failed, sense %x/%x/%x\n",
			   HP_SW_NAME, sshdr->sense_key, sshdr->asc,
			   sshdr->ascq);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * hp_sw_tur - Send TEST UNIT READY
 * @sdev: sdev command should be sent to
 *
 * Use the TEST UNIT READY command to determine
 * the path state.
 */
अटल पूर्णांक hp_sw_tur(काष्ठा scsi_device *sdev, काष्ठा hp_sw_dh_data *h)
अणु
	अचिन्हित अक्षर cmd[6] = अणु TEST_UNIT_READY पूर्ण;
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक ret = SCSI_DH_OK, res;
	u64 req_flags = REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT |
		REQ_FAILFAST_DRIVER;

retry:
	res = scsi_execute(sdev, cmd, DMA_NONE, शून्य, 0, शून्य, &sshdr,
			HP_SW_TIMEOUT, HP_SW_RETRIES, req_flags, 0, शून्य);
	अगर (res) अणु
		अगर (scsi_sense_valid(&sshdr))
			ret = tur_करोne(sdev, h, &sshdr);
		अन्यथा अणु
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "%s: sending tur failed with %x\n",
				    HP_SW_NAME, res);
			ret = SCSI_DH_IO;
		पूर्ण
	पूर्ण अन्यथा अणु
		h->path_state = HP_SW_PATH_ACTIVE;
		ret = SCSI_DH_OK;
	पूर्ण
	अगर (ret == SCSI_DH_IMM_RETRY)
		जाओ retry;

	वापस ret;
पूर्ण

/*
 * hp_sw_start_stop - Send START STOP UNIT command
 * @sdev: sdev command should be sent to
 *
 * Sending START STOP UNIT activates the SP.
 */
अटल पूर्णांक hp_sw_start_stop(काष्ठा hp_sw_dh_data *h)
अणु
	अचिन्हित अक्षर cmd[6] = अणु START_STOP, 0, 0, 0, 1, 0 पूर्ण;
	काष्ठा scsi_sense_hdr sshdr;
	काष्ठा scsi_device *sdev = h->sdev;
	पूर्णांक res, rc = SCSI_DH_OK;
	पूर्णांक retry_cnt = HP_SW_RETRIES;
	u64 req_flags = REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT |
		REQ_FAILFAST_DRIVER;

retry:
	res = scsi_execute(sdev, cmd, DMA_NONE, शून्य, 0, शून्य, &sshdr,
			HP_SW_TIMEOUT, HP_SW_RETRIES, req_flags, 0, शून्य);
	अगर (res) अणु
		अगर (!scsi_sense_valid(&sshdr)) अणु
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "%s: sending start_stop_unit failed, "
				    "no sense available\n", HP_SW_NAME);
			वापस SCSI_DH_IO;
		पूर्ण
		चयन (sshdr.sense_key) अणु
		हाल NOT_READY:
			अगर (sshdr.asc == 0x04 && sshdr.ascq == 3) अणु
				/*
				 * LUN not पढ़ोy - manual पूर्णांकervention required
				 *
				 * Switch-over in progress, retry.
				 */
				अगर (--retry_cnt)
					जाओ retry;
				rc = SCSI_DH_RETRY;
				अवरोध;
			पूर्ण
			fallthrough;
		शेष:
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "%s: sending start_stop_unit failed, "
				    "sense %x/%x/%x\n", HP_SW_NAME,
				    sshdr.sense_key, sshdr.asc, sshdr.ascq);
			rc = SCSI_DH_IO;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल blk_status_t hp_sw_prep_fn(काष्ठा scsi_device *sdev, काष्ठा request *req)
अणु
	काष्ठा hp_sw_dh_data *h = sdev->handler_data;

	अगर (h->path_state != HP_SW_PATH_ACTIVE) अणु
		req->rq_flags |= RQF_QUIET;
		वापस BLK_STS_IOERR;
	पूर्ण

	वापस BLK_STS_OK;
पूर्ण

/*
 * hp_sw_activate - Activate a path
 * @sdev: sdev on the path to be activated
 *
 * The HP Active/Passive firmware is pretty simple;
 * the passive path reports NOT READY with sense codes
 * 0x04/0x02; a START STOP UNIT command will then
 * activate the passive path (and deactivate the
 * previously active one).
 */
अटल पूर्णांक hp_sw_activate(काष्ठा scsi_device *sdev,
				activate_complete fn, व्योम *data)
अणु
	पूर्णांक ret = SCSI_DH_OK;
	काष्ठा hp_sw_dh_data *h = sdev->handler_data;

	ret = hp_sw_tur(sdev, h);

	अगर (ret == SCSI_DH_OK && h->path_state == HP_SW_PATH_PASSIVE)
		ret = hp_sw_start_stop(h);

	अगर (fn)
		fn(data, ret);
	वापस 0;
पूर्ण

अटल पूर्णांक hp_sw_bus_attach(काष्ठा scsi_device *sdev)
अणु
	काष्ठा hp_sw_dh_data *h;
	पूर्णांक ret;

	h = kzalloc(माप(*h), GFP_KERNEL);
	अगर (!h)
		वापस SCSI_DH_NOMEM;
	h->path_state = HP_SW_PATH_UNINITIALIZED;
	h->retries = HP_SW_RETRIES;
	h->sdev = sdev;

	ret = hp_sw_tur(sdev, h);
	अगर (ret != SCSI_DH_OK)
		जाओ failed;
	अगर (h->path_state == HP_SW_PATH_UNINITIALIZED) अणु
		ret = SCSI_DH_NOSYS;
		जाओ failed;
	पूर्ण

	sdev_prपूर्णांकk(KERN_INFO, sdev, "%s: attached to %s path\n",
		    HP_SW_NAME, h->path_state == HP_SW_PATH_ACTIVE?
		    "active":"passive");

	sdev->handler_data = h;
	वापस SCSI_DH_OK;
failed:
	kमुक्त(h);
	वापस ret;
पूर्ण

अटल व्योम hp_sw_bus_detach( काष्ठा scsi_device *sdev )
अणु
	kमुक्त(sdev->handler_data);
	sdev->handler_data = शून्य;
पूर्ण

अटल काष्ठा scsi_device_handler hp_sw_dh = अणु
	.name		= HP_SW_NAME,
	.module		= THIS_MODULE,
	.attach		= hp_sw_bus_attach,
	.detach		= hp_sw_bus_detach,
	.activate	= hp_sw_activate,
	.prep_fn	= hp_sw_prep_fn,
पूर्ण;

अटल पूर्णांक __init hp_sw_init(व्योम)
अणु
	वापस scsi_रेजिस्टर_device_handler(&hp_sw_dh);
पूर्ण

अटल व्योम __निकास hp_sw_निकास(व्योम)
अणु
	scsi_unरेजिस्टर_device_handler(&hp_sw_dh);
पूर्ण

module_init(hp_sw_init);
module_निकास(hp_sw_निकास);

MODULE_DESCRIPTION("HP Active/Passive driver");
MODULE_AUTHOR("Mike Christie <michaelc@cs.wisc.edu");
MODULE_LICENSE("GPL");
