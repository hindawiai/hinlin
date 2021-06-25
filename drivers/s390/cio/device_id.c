<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  CCW device SENSE ID I/O handling.
 *
 *    Copyright IBM Corp. 2002, 2009
 *    Author(s): Cornelia Huck <cornelia.huck@de.ibm.com>
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>
 *		 Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/diag.h>

#समावेश "cio.h"
#समावेश "cio_debug.h"
#समावेश "device.h"
#समावेश "io_sch.h"

#घोषणा SENSE_ID_RETRIES	256
#घोषणा SENSE_ID_TIMEOUT	(10 * HZ)
#घोषणा SENSE_ID_MIN_LEN	4
#घोषणा SENSE_ID_BASIC_LEN	7

/**
 * diag210_to_senseid - convert diag 0x210 data to sense id inक्रमmation
 * @senseid: sense id
 * @diag: diag 0x210 data
 *
 * Return 0 on success, non-zero otherwise.
 */
अटल पूर्णांक diag210_to_senseid(काष्ठा senseid *senseid, काष्ठा diag210 *diag)
अणु
	अटल काष्ठा अणु
		पूर्णांक class, type, cu_type;
	पूर्ण vm_devices[] = अणु
		अणु 0x08, 0x01, 0x3480 पूर्ण,
		अणु 0x08, 0x02, 0x3430 पूर्ण,
		अणु 0x08, 0x10, 0x3420 पूर्ण,
		अणु 0x08, 0x42, 0x3424 पूर्ण,
		अणु 0x08, 0x44, 0x9348 पूर्ण,
		अणु 0x08, 0x81, 0x3490 पूर्ण,
		अणु 0x08, 0x82, 0x3422 पूर्ण,
		अणु 0x10, 0x41, 0x1403 पूर्ण,
		अणु 0x10, 0x42, 0x3211 पूर्ण,
		अणु 0x10, 0x43, 0x3203 पूर्ण,
		अणु 0x10, 0x45, 0x3800 पूर्ण,
		अणु 0x10, 0x47, 0x3262 पूर्ण,
		अणु 0x10, 0x48, 0x3820 पूर्ण,
		अणु 0x10, 0x49, 0x3800 पूर्ण,
		अणु 0x10, 0x4a, 0x4245 पूर्ण,
		अणु 0x10, 0x4b, 0x4248 पूर्ण,
		अणु 0x10, 0x4d, 0x3800 पूर्ण,
		अणु 0x10, 0x4e, 0x3820 पूर्ण,
		अणु 0x10, 0x4f, 0x3820 पूर्ण,
		अणु 0x10, 0x82, 0x2540 पूर्ण,
		अणु 0x10, 0x84, 0x3525 पूर्ण,
		अणु 0x20, 0x81, 0x2501 पूर्ण,
		अणु 0x20, 0x82, 0x2540 पूर्ण,
		अणु 0x20, 0x84, 0x3505 पूर्ण,
		अणु 0x40, 0x01, 0x3278 पूर्ण,
		अणु 0x40, 0x04, 0x3277 पूर्ण,
		अणु 0x40, 0x80, 0x2250 पूर्ण,
		अणु 0x40, 0xc0, 0x5080 पूर्ण,
		अणु 0x80, 0x00, 0x3215 पूर्ण,
	पूर्ण;
	पूर्णांक i;

	/* Special हाल क्रम osa devices. */
	अगर (diag->vrdcvcla == 0x02 && diag->vrdcvtyp == 0x20) अणु
		senseid->cu_type = 0x3088;
		senseid->cu_model = 0x60;
		senseid->reserved = 0xff;
		वापस 0;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(vm_devices); i++) अणु
		अगर (diag->vrdcvcla == vm_devices[i].class &&
		    diag->vrdcvtyp == vm_devices[i].type) अणु
			senseid->cu_type = vm_devices[i].cu_type;
			senseid->reserved = 0xff;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

/**
 * diag_get_dev_info - retrieve device inक्रमmation via diag 0x210
 * @cdev: ccw device
 *
 * Returns zero on success, non-zero otherwise.
 */
अटल पूर्णांक diag210_get_dev_info(काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccw_dev_id *dev_id = &cdev->निजी->dev_id;
	काष्ठा senseid *senseid = &cdev->निजी->dma_area->senseid;
	काष्ठा diag210 diag_data;
	पूर्णांक rc;

	अगर (dev_id->ssid != 0)
		वापस -ENODEV;
	स_रखो(&diag_data, 0, माप(diag_data));
	diag_data.vrdcdvno	= dev_id->devno;
	diag_data.vrdclen	= माप(diag_data);
	rc = diag210(&diag_data);
	CIO_TRACE_EVENT(4, "diag210");
	CIO_HEX_EVENT(4, &rc, माप(rc));
	CIO_HEX_EVENT(4, &diag_data, माप(diag_data));
	अगर (rc != 0 && rc != 2)
		जाओ err_failed;
	अगर (diag210_to_senseid(senseid, &diag_data))
		जाओ err_unknown;
	वापस 0;

err_unknown:
	CIO_MSG_EVENT(0, "snsid: device 0.%x.%04x: unknown diag210 data\n",
		      dev_id->ssid, dev_id->devno);
	वापस -ENODEV;
err_failed:
	CIO_MSG_EVENT(0, "snsid: device 0.%x.%04x: diag210 failed (rc=%d)\n",
		      dev_id->ssid, dev_id->devno, rc);
	वापस -ENODEV;
पूर्ण

/*
 * Initialize SENSE ID data.
 */
अटल व्योम snsid_init(काष्ठा ccw_device *cdev)
अणु
	cdev->निजी->flags.esid = 0;

	स_रखो(&cdev->निजी->dma_area->senseid, 0,
	       माप(cdev->निजी->dma_area->senseid));
	cdev->निजी->dma_area->senseid.cu_type = 0xffff;
पूर्ण

/*
 * Check क्रम complete SENSE ID data.
 */
अटल पूर्णांक snsid_check(काष्ठा ccw_device *cdev, व्योम *data)
अणु
	काष्ठा cmd_scsw *scsw = &cdev->निजी->dma_area->irb.scsw.cmd;
	पूर्णांक len = माप(काष्ठा senseid) - scsw->count;

	/* Check क्रम incomplete SENSE ID data. */
	अगर (len < SENSE_ID_MIN_LEN)
		जाओ out_restart;
	अगर (cdev->निजी->dma_area->senseid.cu_type == 0xffff)
		जाओ out_restart;
	/* Check क्रम incompatible SENSE ID data. */
	अगर (cdev->निजी->dma_area->senseid.reserved != 0xff)
		वापस -EOPNOTSUPP;
	/* Check क्रम extended-identअगरication inक्रमmation. */
	अगर (len > SENSE_ID_BASIC_LEN)
		cdev->निजी->flags.esid = 1;
	वापस 0;

out_restart:
	snsid_init(cdev);
	वापस -EAGAIN;
पूर्ण

/*
 * Process SENSE ID request result.
 */
अटल व्योम snsid_callback(काष्ठा ccw_device *cdev, व्योम *data, पूर्णांक rc)
अणु
	काष्ठा ccw_dev_id *id = &cdev->निजी->dev_id;
	काष्ठा senseid *senseid = &cdev->निजी->dma_area->senseid;
	पूर्णांक vm = 0;

	अगर (rc && MACHINE_IS_VM) अणु
		/* Try diag 0x210 fallback on z/VM. */
		snsid_init(cdev);
		अगर (diag210_get_dev_info(cdev) == 0) अणु
			rc = 0;
			vm = 1;
		पूर्ण
	पूर्ण
	CIO_MSG_EVENT(2, "snsid: device 0.%x.%04x: rc=%d %04x/%02x "
		      "%04x/%02x%s\n", id->ssid, id->devno, rc,
		      senseid->cu_type, senseid->cu_model, senseid->dev_type,
		      senseid->dev_model, vm ? " (diag210)" : "");
	ccw_device_sense_id_करोne(cdev, rc);
पूर्ण

/**
 * ccw_device_sense_id_start - perक्रमm SENSE ID
 * @cdev: ccw device
 *
 * Execute a SENSE ID channel program on @cdev to update its sense id
 * inक्रमmation. When finished, call ccw_device_sense_id_करोne with a
 * वापस code specअगरying the result.
 */
व्योम ccw_device_sense_id_start(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा ccw_request *req = &cdev->निजी->req;
	काष्ठा ccw1 *cp = cdev->निजी->dma_area->iccws;

	CIO_TRACE_EVENT(4, "snsid");
	CIO_HEX_EVENT(4, &cdev->निजी->dev_id, माप(cdev->निजी->dev_id));
	/* Data setup. */
	snsid_init(cdev);
	/* Channel program setup. */
	cp->cmd_code	= CCW_CMD_SENSE_ID;
	cp->cda		= (u32) (addr_t) &cdev->निजी->dma_area->senseid;
	cp->count	= माप(काष्ठा senseid);
	cp->flags	= CCW_FLAG_SLI;
	/* Request setup. */
	स_रखो(req, 0, माप(*req));
	req->cp		= cp;
	req->समयout	= SENSE_ID_TIMEOUT;
	req->maxretries	= SENSE_ID_RETRIES;
	req->lpm	= sch->schib.pmcw.pam & sch->opm;
	req->check	= snsid_check;
	req->callback	= snsid_callback;
	ccw_request_start(cdev);
पूर्ण
