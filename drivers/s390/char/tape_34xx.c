<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    tape device discipline क्रम 3480/3490 tapes.
 *
 *    Copyright IBM Corp. 2001, 2009
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *		 Tuan Ngo-Anh <ngoanh@de.ibm.com>
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "tape_34xx"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/bपन.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>

#घोषणा TAPE_DBF_AREA	tape_34xx_dbf

#समावेश "tape.h"
#समावेश "tape_std.h"

/*
 * Poपूर्णांकer to debug area.
 */
debug_info_t *TAPE_DBF_AREA = शून्य;
EXPORT_SYMBOL(TAPE_DBF_AREA);

#घोषणा TAPE34XX_FMT_3480	0
#घोषणा TAPE34XX_FMT_3480_2_XF	1
#घोषणा TAPE34XX_FMT_3480_XF	2

काष्ठा tape_34xx_block_id अणु
	अचिन्हित पूर्णांक	wrap		: 1;
	अचिन्हित पूर्णांक	segment		: 7;
	अचिन्हित पूर्णांक	क्रमmat		: 2;
	अचिन्हित पूर्णांक	block		: 22;
पूर्ण;

/*
 * A list of block ID's is used to faster seek blocks.
 */
काष्ठा tape_34xx_sbid अणु
	काष्ठा list_head		list;
	काष्ठा tape_34xx_block_id	bid;
पूर्ण;

अटल व्योम tape_34xx_delete_sbid_from(काष्ठा tape_device *, पूर्णांक);

/*
 * Medium sense क्रम 34xx tapes. There is no 'real' medium sense call.
 * So we just करो a normal sense.
 */
अटल व्योम __tape_34xx_medium_sense(काष्ठा tape_request *request)
अणु
	काष्ठा tape_device *device = request->device;
	अचिन्हित अक्षर *sense;

	अगर (request->rc == 0) अणु
		sense = request->cpdata;

		/*
		 * This isn't quite correct. But since INTERVENTION_REQUIRED
		 * means that the drive is 'neither ready nor on-line' it is
		 * only slightly inaccurate to say there is no tape loaded अगर
		 * the drive isn't online...
		 */
		अगर (sense[0] & SENSE_INTERVENTION_REQUIRED)
			tape_med_state_set(device, MS_UNLOADED);
		अन्यथा
			tape_med_state_set(device, MS_LOADED);

		अगर (sense[1] & SENSE_WRITE_PROTECT)
			device->tape_generic_status |= GMT_WR_PROT(~0);
		अन्यथा
			device->tape_generic_status &= ~GMT_WR_PROT(~0);
	पूर्ण अन्यथा
		DBF_EVENT(4, "tape_34xx: medium sense failed with rc=%d\n",
			request->rc);
	tape_मुक्त_request(request);
पूर्ण

अटल पूर्णांक tape_34xx_medium_sense(काष्ठा tape_device *device)
अणु
	काष्ठा tape_request *request;
	पूर्णांक rc;

	request = tape_alloc_request(1, 32);
	अगर (IS_ERR(request)) अणु
		DBF_EXCEPTION(6, "MSEN fail\n");
		वापस PTR_ERR(request);
	पूर्ण

	request->op = TO_MSEN;
	tape_ccw_end(request->cpaddr, SENSE, 32, request->cpdata);
	rc = tape_करो_io_पूर्णांकerruptible(device, request);
	__tape_34xx_medium_sense(request);
	वापस rc;
पूर्ण

अटल व्योम tape_34xx_medium_sense_async(काष्ठा tape_device *device)
अणु
	काष्ठा tape_request *request;

	request = tape_alloc_request(1, 32);
	अगर (IS_ERR(request)) अणु
		DBF_EXCEPTION(6, "MSEN fail\n");
		वापस;
	पूर्ण

	request->op = TO_MSEN;
	tape_ccw_end(request->cpaddr, SENSE, 32, request->cpdata);
	request->callback = (व्योम *) __tape_34xx_medium_sense;
	request->callback_data = शून्य;
	tape_करो_io_async(device, request);
पूर्ण

काष्ठा tape_34xx_work अणु
	काष्ठा tape_device	*device;
	क्रमागत tape_op		 op;
	काष्ठा work_काष्ठा	 work;
पूर्ण;

/*
 * These functions are currently used only to schedule a medium_sense क्रम
 * later execution. This is because we get an पूर्णांकerrupt whenever a medium
 * is inserted but cannot call tape_करो_io* from an पूर्णांकerrupt context.
 * Maybe that's useful क्रम other actions we want to start from the
 * पूर्णांकerrupt handler.
 * Note: the work handler is called by the प्रणाली work queue. The tape
 * commands started by the handler need to be asynchrounous, otherwise
 * a deadlock can occur e.g. in हाल of a deferred cc=1 (see __tape_करो_irq).
 */
अटल व्योम
tape_34xx_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tape_34xx_work *p =
		container_of(work, काष्ठा tape_34xx_work, work);
	काष्ठा tape_device *device = p->device;

	चयन(p->op) अणु
		हाल TO_MSEN:
			tape_34xx_medium_sense_async(device);
			अवरोध;
		शेष:
			DBF_EVENT(3, "T34XX: internal error: unknown work\n");
	पूर्ण
	tape_put_device(device);
	kमुक्त(p);
पूर्ण

अटल पूर्णांक
tape_34xx_schedule_work(काष्ठा tape_device *device, क्रमागत tape_op op)
अणु
	काष्ठा tape_34xx_work *p;

	अगर ((p = kzalloc(माप(*p), GFP_ATOMIC)) == शून्य)
		वापस -ENOMEM;

	INIT_WORK(&p->work, tape_34xx_work_handler);

	p->device = tape_get_device(device);
	p->op     = op;

	schedule_work(&p->work);
	वापस 0;
पूर्ण

/*
 * Done Handler is called when dev stat = DEVICE-END (successful operation)
 */
अटल अंतरभूत पूर्णांक
tape_34xx_करोne(काष्ठा tape_request *request)
अणु
	DBF_EVENT(6, "%s done\n", tape_op_verbose[request->op]);

	चयन (request->op) अणु
		हाल TO_DSE:
		हाल TO_RUN:
		हाल TO_WRI:
		हाल TO_WTM:
		हाल TO_ASSIGN:
		हाल TO_UNASSIGN:
			tape_34xx_delete_sbid_from(request->device, 0);
			अवरोध;
		शेष:
			;
	पूर्ण
	वापस TAPE_IO_SUCCESS;
पूर्ण

अटल अंतरभूत पूर्णांक
tape_34xx_erp_failed(काष्ठा tape_request *request, पूर्णांक rc)
अणु
	DBF_EVENT(3, "Error recovery failed for %s (RC=%d)\n",
		  tape_op_verbose[request->op], rc);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक
tape_34xx_erp_succeeded(काष्ठा tape_request *request)
अणु
	DBF_EVENT(3, "Error Recovery successful for %s\n",
		  tape_op_verbose[request->op]);
	वापस tape_34xx_करोne(request);
पूर्ण

अटल अंतरभूत पूर्णांक
tape_34xx_erp_retry(काष्ठा tape_request *request)
अणु
	DBF_EVENT(3, "xerp retr %s\n", tape_op_verbose[request->op]);
	वापस TAPE_IO_RETRY;
पूर्ण

/*
 * This function is called, when no request is outstanding and we get an
 * पूर्णांकerrupt
 */
अटल पूर्णांक
tape_34xx_unsolicited_irq(काष्ठा tape_device *device, काष्ठा irb *irb)
अणु
	अगर (irb->scsw.cmd.dstat == 0x85) अणु /* READY */
		/* A medium was inserted in the drive. */
		DBF_EVENT(6, "xuud med\n");
		tape_34xx_delete_sbid_from(device, 0);
		tape_34xx_schedule_work(device, TO_MSEN);
	पूर्ण अन्यथा अणु
		DBF_EVENT(3, "unsol.irq! dev end: %08x\n", device->cdev_id);
		tape_dump_sense_dbf(device, शून्य, irb);
	पूर्ण
	वापस TAPE_IO_SUCCESS;
पूर्ण

/*
 * Read Opposite Error Recovery Function:
 * Used, when Read Forward करोes not work
 */
अटल पूर्णांक
tape_34xx_erp_पढ़ो_opposite(काष्ठा tape_device *device,
			    काष्ठा tape_request *request)
अणु
	अगर (request->op == TO_RFO) अणु
		/*
		 * We did पढ़ो क्रमward, but the data could not be पढ़ो
		 * *correctly*. We transक्रमm the request to a पढ़ो backward
		 * and try again.
		 */
		tape_std_पढ़ो_backward(device, request);
		वापस tape_34xx_erp_retry(request);
	पूर्ण

	/*
	 * We tried to पढ़ो क्रमward and backward, but hat no
	 * success -> failed.
	 */
	वापस tape_34xx_erp_failed(request, -EIO);
पूर्ण

अटल पूर्णांक
tape_34xx_erp_bug(काष्ठा tape_device *device, काष्ठा tape_request *request,
		  काष्ठा irb *irb, पूर्णांक no)
अणु
	अगर (request->op != TO_ASSIGN) अणु
		dev_err(&device->cdev->dev, "An unexpected condition %d "
			"occurred in tape error recovery\n", no);
		tape_dump_sense_dbf(device, request, irb);
	पूर्ण
	वापस tape_34xx_erp_failed(request, -EIO);
पूर्ण

/*
 * Handle data overrun between cu and drive. The channel speed might
 * be too slow.
 */
अटल पूर्णांक
tape_34xx_erp_overrun(काष्ठा tape_device *device, काष्ठा tape_request *request,
		      काष्ठा irb *irb)
अणु
	अगर (irb->ecw[3] == 0x40) अणु
		dev_warn (&device->cdev->dev, "A data overrun occurred between"
			" the control unit and tape unit\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	पूर्ण
	वापस tape_34xx_erp_bug(device, request, irb, -1);
पूर्ण

/*
 * Handle record sequence error.
 */
अटल पूर्णांक
tape_34xx_erp_sequence(काष्ठा tape_device *device,
		       काष्ठा tape_request *request, काष्ठा irb *irb)
अणु
	अगर (irb->ecw[3] == 0x41) अणु
		/*
		 * cu detected incorrect block-id sequence on tape.
		 */
		dev_warn (&device->cdev->dev, "The block ID sequence on the "
			"tape is incorrect\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	पूर्ण
	/*
	 * Record sequence error bit is set, but erpa करोes not
	 * show record sequence error.
	 */
	वापस tape_34xx_erp_bug(device, request, irb, -2);
पूर्ण

/*
 * This function analyses the tape's sense-data in हाल of a unit-check.
 * If possible, it tries to recover from the error. Else the user is
 * inक्रमmed about the problem.
 */
अटल पूर्णांक
tape_34xx_unit_check(काष्ठा tape_device *device, काष्ठा tape_request *request,
		     काष्ठा irb *irb)
अणु
	पूर्णांक inhibit_cu_recovery;
	__u8* sense;

	inhibit_cu_recovery = (*device->modeset_byte & 0x80) ? 1 : 0;
	sense = irb->ecw;

	अगर (
		sense[0] & SENSE_COMMAND_REJECT &&
		sense[1] & SENSE_WRITE_PROTECT
	) अणु
		अगर (
			request->op == TO_DSE ||
			request->op == TO_WRI ||
			request->op == TO_WTM
		) अणु
			/* medium is ग_लिखो रक्षित */
			वापस tape_34xx_erp_failed(request, -EACCES);
		पूर्ण अन्यथा अणु
			वापस tape_34xx_erp_bug(device, request, irb, -3);
		पूर्ण
	पूर्ण

	/*
	 * Special हालs क्रम various tape-states when reaching
	 * end of recorded area
	 *
	 * FIXME: Maybe a special हाल of the special हाल:
	 *        sense[0] == SENSE_EQUIPMENT_CHECK &&
	 *        sense[1] == SENSE_DRIVE_ONLINE    &&
	 *        sense[3] == 0x47 (Volume Fenced)
	 *
	 *        This was caused by जारीd FSF or FSR after an
	 *        'End Of Data'.
	 */
	अगर ((
		sense[0] == SENSE_DATA_CHECK      ||
		sense[0] == SENSE_EQUIPMENT_CHECK ||
		sense[0] == SENSE_EQUIPMENT_CHECK + SENSE_DEFERRED_UNIT_CHECK
	) && (
		sense[1] == SENSE_DRIVE_ONLINE ||
		sense[1] == SENSE_BEGINNING_OF_TAPE + SENSE_WRITE_MODE
	)) अणु
		चयन (request->op) अणु
		/*
		 * sense[0] == SENSE_DATA_CHECK   &&
		 * sense[1] == SENSE_DRIVE_ONLINE
		 * sense[3] == 0x36 (End Of Data)
		 *
		 * Further seeks might वापस a 'Volume Fenced'.
		 */
		हाल TO_FSF:
		हाल TO_FSB:
			/* Trying to seek beyond end of recorded area */
			वापस tape_34xx_erp_failed(request, -ENOSPC);
		हाल TO_BSB:
			वापस tape_34xx_erp_retry(request);

		/*
		 * sense[0] == SENSE_DATA_CHECK   &&
		 * sense[1] == SENSE_DRIVE_ONLINE &&
		 * sense[3] == 0x36 (End Of Data)
		 */
		हाल TO_LBL:
			/* Block could not be located. */
			tape_34xx_delete_sbid_from(device, 0);
			वापस tape_34xx_erp_failed(request, -EIO);

		हाल TO_RFO:
			/* Read beyond end of recorded area -> 0 bytes पढ़ो */
			वापस tape_34xx_erp_failed(request, 0);

		/*
		 * sense[0] == SENSE_EQUIPMENT_CHECK &&
		 * sense[1] == SENSE_DRIVE_ONLINE    &&
		 * sense[3] == 0x38 (Physical End Of Volume)
		 */
		हाल TO_WRI:
			/* Writing at physical end of volume */
			वापस tape_34xx_erp_failed(request, -ENOSPC);
		शेष:
			वापस tape_34xx_erp_failed(request, 0);
		पूर्ण
	पूर्ण

	/* Sensing special bits */
	अगर (sense[0] & SENSE_BUS_OUT_CHECK)
		वापस tape_34xx_erp_retry(request);

	अगर (sense[0] & SENSE_DATA_CHECK) अणु
		/*
		 * hardware failure, damaged tape or improper
		 * operating conditions
		 */
		चयन (sense[3]) अणु
		हाल 0x23:
			/* a पढ़ो data check occurred */
			अगर ((sense[2] & SENSE_TAPE_SYNC_MODE) ||
			    inhibit_cu_recovery)
				// data check is not permanent, may be
				// recovered. We always use async-mode with
				// cu-recovery, so this should *never* happen.
				वापस tape_34xx_erp_bug(device, request,
							 irb, -4);

			/* data check is permanent, CU recovery has failed */
			dev_warn (&device->cdev->dev, "A read error occurred "
				"that cannot be recovered\n");
			वापस tape_34xx_erp_failed(request, -EIO);
		हाल 0x25:
			// a ग_लिखो data check occurred
			अगर ((sense[2] & SENSE_TAPE_SYNC_MODE) ||
			    inhibit_cu_recovery)
				// data check is not permanent, may be
				// recovered. We always use async-mode with
				// cu-recovery, so this should *never* happen.
				वापस tape_34xx_erp_bug(device, request,
							 irb, -5);

			// data check is permanent, cu-recovery has failed
			dev_warn (&device->cdev->dev, "A write error on the "
				"tape cannot be recovered\n");
			वापस tape_34xx_erp_failed(request, -EIO);
		हाल 0x26:
			/* Data Check (पढ़ो opposite) occurred. */
			वापस tape_34xx_erp_पढ़ो_opposite(device, request);
		हाल 0x28:
			/* ID-Mark at tape start couldn't be written */
			dev_warn (&device->cdev->dev, "Writing the ID-mark "
				"failed\n");
			वापस tape_34xx_erp_failed(request, -EIO);
		हाल 0x31:
			/* Tape व्योम. Tried to पढ़ो beyond end of device. */
			dev_warn (&device->cdev->dev, "Reading the tape beyond"
				" the end of the recorded area failed\n");
			वापस tape_34xx_erp_failed(request, -ENOSPC);
		हाल 0x41:
			/* Record sequence error. */
			dev_warn (&device->cdev->dev, "The tape contains an "
				"incorrect block ID sequence\n");
			वापस tape_34xx_erp_failed(request, -EIO);
		शेष:
			/* all data checks क्रम 3480 should result in one of
			 * the above erpa-codes. For 3490, other data-check
			 * conditions करो exist. */
			अगर (device->cdev->id.driver_info == tape_3480)
				वापस tape_34xx_erp_bug(device, request,
							 irb, -6);
		पूर्ण
	पूर्ण

	अगर (sense[0] & SENSE_OVERRUN)
		वापस tape_34xx_erp_overrun(device, request, irb);

	अगर (sense[1] & SENSE_RECORD_SEQUENCE_ERR)
		वापस tape_34xx_erp_sequence(device, request, irb);

	/* Sensing erpa codes */
	चयन (sense[3]) अणु
	हाल 0x00:
		/* Unit check with erpa code 0. Report and ignore. */
		वापस TAPE_IO_SUCCESS;
	हाल 0x21:
		/*
		 * Data streaming not operational. CU will चयन to
		 * पूर्णांकerlock mode. Reissue the command.
		 */
		वापस tape_34xx_erp_retry(request);
	हाल 0x22:
		/*
		 * Path equipment check. Might be drive adapter error, buffer
		 * error on the lower पूर्णांकerface, पूर्णांकernal path not usable,
		 * or error during cartridge load.
		 */
		dev_warn (&device->cdev->dev, "A path equipment check occurred"
			" for the tape device\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x24:
		/*
		 * Load display check. Load display was command was issued,
		 * but the drive is displaying a drive check message. Can
		 * be threated as "device end".
		 */
		वापस tape_34xx_erp_succeeded(request);
	हाल 0x27:
		/*
		 * Command reject. May indicate illegal channel program or
		 * buffer over/underrun. Since all channel programs are
		 * issued by this driver and ought be correct, we assume a
		 * over/underrun situation and retry the channel program.
		 */
		वापस tape_34xx_erp_retry(request);
	हाल 0x29:
		/*
		 * Function incompatible. Either the tape is idrc compressed
		 * but the hardware isn't capable to करो idrc, or a perक्रमm
		 * subप्रणाली func is issued and the CU is not on-line.
		 */
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x2a:
		/*
		 * Unsolicited environmental data. An पूर्णांकernal counter
		 * overflows, we can ignore this and reissue the cmd.
		 */
		वापस tape_34xx_erp_retry(request);
	हाल 0x2b:
		/*
		 * Environmental data present. Indicates either unload
		 * completed ok or पढ़ो buffered log command completed ok.
		 */
		अगर (request->op == TO_RUN) अणु
			/* Rewind unload completed ok. */
			tape_med_state_set(device, MS_UNLOADED);
			वापस tape_34xx_erp_succeeded(request);
		पूर्ण
		/* tape_34xx करोesn't use पढ़ो buffered log commands. */
		वापस tape_34xx_erp_bug(device, request, irb, sense[3]);
	हाल 0x2c:
		/*
		 * Permanent equipment check. CU has tried recovery, but
		 * did not succeed.
		 */
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x2d:
		/* Data security erase failure. */
		अगर (request->op == TO_DSE)
			वापस tape_34xx_erp_failed(request, -EIO);
		/* Data security erase failure, but no such command issued. */
		वापस tape_34xx_erp_bug(device, request, irb, sense[3]);
	हाल 0x2e:
		/*
		 * Not capable. This indicates either that the drive fails
		 * पढ़ोing the क्रमmat id mark or that that क्रमmat specअगरied
		 * is not supported by the drive.
		 */
		dev_warn (&device->cdev->dev, "The tape unit cannot process "
			"the tape format\n");
		वापस tape_34xx_erp_failed(request, -EMEDIUMTYPE);
	हाल 0x30:
		/* The medium is ग_लिखो रक्षित. */
		dev_warn (&device->cdev->dev, "The tape medium is write-"
			"protected\n");
		वापस tape_34xx_erp_failed(request, -EACCES);
	हाल 0x32:
		// Tension loss. We cannot recover this, it's an I/O error.
		dev_warn (&device->cdev->dev, "The tape does not have the "
			"required tape tension\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x33:
		/*
		 * Load Failure. The cartridge was not inserted correctly or
		 * the tape is not thपढ़ोed correctly.
		 */
		dev_warn (&device->cdev->dev, "The tape unit failed to load"
			" the cartridge\n");
		tape_34xx_delete_sbid_from(device, 0);
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x34:
		/*
		 * Unload failure. The drive cannot मुख्यtain tape tension
		 * and control tape movement during an unload operation.
		 */
		dev_warn (&device->cdev->dev, "Automatic unloading of the tape"
			" cartridge failed\n");
		अगर (request->op == TO_RUN)
			वापस tape_34xx_erp_failed(request, -EIO);
		वापस tape_34xx_erp_bug(device, request, irb, sense[3]);
	हाल 0x35:
		/*
		 * Drive equipment check. One of the following:
		 * - cu cannot recover from a drive detected error
		 * - a check code message is shown on drive display
		 * - the cartridge loader करोes not respond correctly
		 * - a failure occurs during an index, load, or unload cycle
		 */
		dev_warn (&device->cdev->dev, "An equipment check has occurred"
			" on the tape unit\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x36:
		अगर (device->cdev->id.driver_info == tape_3490)
			/* End of data. */
			वापस tape_34xx_erp_failed(request, -EIO);
		/* This erpa is reserved क्रम 3480 */
		वापस tape_34xx_erp_bug(device, request, irb, sense[3]);
	हाल 0x37:
		/*
		 * Tape length error. The tape is लघुer than reported in
		 * the beginning-of-tape data.
		 */
		dev_warn (&device->cdev->dev, "The tape information states an"
			" incorrect length\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x38:
		/*
		 * Physical end of tape. A पढ़ो/ग_लिखो operation reached
		 * the physical end of tape.
		 */
		अगर (request->op==TO_WRI ||
		    request->op==TO_DSE ||
		    request->op==TO_WTM)
			वापस tape_34xx_erp_failed(request, -ENOSPC);
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x39:
		/* Backward at Beginning of tape. */
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x3a:
		/* Drive चयनed to not पढ़ोy. */
		dev_warn (&device->cdev->dev, "The tape unit is not ready\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x3b:
		/* Manual शुरुआत or unload. This causes an I/O error. */
		dev_warn (&device->cdev->dev, "The tape medium has been "
			"rewound or unloaded manually\n");
		tape_34xx_delete_sbid_from(device, 0);
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x42:
		/*
		 * Degraded mode. A condition that can cause degraded
		 * perक्रमmance is detected.
		 */
		dev_warn (&device->cdev->dev, "The tape subsystem is running "
			"in degraded mode\n");
		वापस tape_34xx_erp_retry(request);
	हाल 0x43:
		/* Drive not पढ़ोy. */
		tape_34xx_delete_sbid_from(device, 0);
		tape_med_state_set(device, MS_UNLOADED);
		/* Some commands commands are successful even in this हाल */
		अगर (sense[1] & SENSE_DRIVE_ONLINE) अणु
			चयन(request->op) अणु
				हाल TO_ASSIGN:
				हाल TO_UNASSIGN:
				हाल TO_DIS:
				हाल TO_NOP:
					वापस tape_34xx_करोne(request);
					अवरोध;
				शेष:
					अवरोध;
			पूर्ण
		पूर्ण
		वापस tape_34xx_erp_failed(request, -ENOMEDIUM);
	हाल 0x44:
		/* Locate Block unsuccessful. */
		अगर (request->op != TO_BLOCK && request->op != TO_LBL)
			/* No locate block was issued. */
			वापस tape_34xx_erp_bug(device, request,
						 irb, sense[3]);
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x45:
		/* The drive is asचिन्हित to a dअगरferent channel path. */
		dev_warn (&device->cdev->dev, "The tape unit is already "
			"assigned\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x46:
		/*
		 * Drive not on-line. Drive may be चयनed offline,
		 * the घातer supply may be चयनed off or
		 * the drive address may not be set correctly.
		 */
		dev_warn (&device->cdev->dev, "The tape unit is not online\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x47:
		/* Volume fenced. CU reports volume पूर्णांकegrity is lost. */
		dev_warn (&device->cdev->dev, "The control unit has fenced "
			"access to the tape volume\n");
		tape_34xx_delete_sbid_from(device, 0);
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x48:
		/* Log sense data and retry request. */
		वापस tape_34xx_erp_retry(request);
	हाल 0x49:
		/* Bus out check. A parity check error on the bus was found. */
		dev_warn (&device->cdev->dev, "A parity error occurred on the "
			"tape bus\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x4a:
		/* Control unit erp failed. */
		dev_warn (&device->cdev->dev, "I/O error recovery failed on "
			"the tape control unit\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x4b:
		/*
		 * CU and drive incompatible. The drive requests micro-program
		 * patches, which are not available on the CU.
		 */
		dev_warn (&device->cdev->dev, "The tape unit requires a "
			"firmware update\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x4c:
		/*
		 * Recovered Check-One failure. Cu develops a hardware error,
		 * but is able to recover.
		 */
		वापस tape_34xx_erp_retry(request);
	हाल 0x4d:
		अगर (device->cdev->id.driver_info == tape_3490)
			/*
			 * Resetting event received. Since the driver करोes
			 * not support resetting event recovery (which has to
			 * be handled by the I/O Layer), retry our command.
			 */
			वापस tape_34xx_erp_retry(request);
		/* This erpa is reserved क्रम 3480. */
		वापस tape_34xx_erp_bug(device, request, irb, sense[3]);
	हाल 0x4e:
		अगर (device->cdev->id.driver_info == tape_3490) अणु
			/*
			 * Maximum block size exceeded. This indicates, that
			 * the block to be written is larger than allowed क्रम
			 * buffered mode.
			 */
			dev_warn (&device->cdev->dev, "The maximum block size"
				" for buffered mode is exceeded\n");
			वापस tape_34xx_erp_failed(request, -ENOBUFS);
		पूर्ण
		/* This erpa is reserved क्रम 3480. */
		वापस tape_34xx_erp_bug(device, request, irb, sense[3]);
	हाल 0x50:
		/*
		 * Read buffered log (Overflow). CU is running in extended
		 * buffered log mode, and a counter overflows. This should
		 * never happen, since we're never running in extended
		 * buffered log mode.
		 */
		वापस tape_34xx_erp_retry(request);
	हाल 0x51:
		/*
		 * Read buffered log (EOV). खातापूर्ण processing occurs जबतक the
		 * CU is in extended buffered log mode. This should never
		 * happen, since we're never running in extended buffered
		 * log mode.
		 */
		वापस tape_34xx_erp_retry(request);
	हाल 0x52:
		/* End of Volume complete. Rewind unload completed ok. */
		अगर (request->op == TO_RUN) अणु
			tape_med_state_set(device, MS_UNLOADED);
			tape_34xx_delete_sbid_from(device, 0);
			वापस tape_34xx_erp_succeeded(request);
		पूर्ण
		वापस tape_34xx_erp_bug(device, request, irb, sense[3]);
	हाल 0x53:
		/* Global command पूर्णांकercept. */
		वापस tape_34xx_erp_retry(request);
	हाल 0x54:
		/* Channel पूर्णांकerface recovery (temporary). */
		वापस tape_34xx_erp_retry(request);
	हाल 0x55:
		/* Channel पूर्णांकerface recovery (permanent). */
		dev_warn (&device->cdev->dev, "A channel interface error cannot be"
			" recovered\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x56:
		/* Channel protocol error. */
		dev_warn (&device->cdev->dev, "A channel protocol error "
			"occurred\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x57:
		/*
		 * 3480: Attention पूर्णांकercept.
		 * 3490: Global status पूर्णांकercept.
		 */
		वापस tape_34xx_erp_retry(request);
	हाल 0x5a:
		/*
		 * Tape length incompatible. The tape inserted is too दीर्घ,
		 * which could cause damage to the tape or the drive.
		 */
		dev_warn (&device->cdev->dev, "The tape unit does not support "
			"the tape length\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x5b:
		/* Format 3480 XF incompatible */
		अगर (sense[1] & SENSE_BEGINNING_OF_TAPE)
			/* The tape will get overwritten. */
			वापस tape_34xx_erp_retry(request);
		dev_warn (&device->cdev->dev, "The tape unit does not support"
			" format 3480 XF\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x5c:
		/* Format 3480-2 XF incompatible */
		dev_warn (&device->cdev->dev, "The tape unit does not support tape "
			"format 3480-2 XF\n");
		वापस tape_34xx_erp_failed(request, -EIO);
	हाल 0x5d:
		/* Tape length violation. */
		dev_warn (&device->cdev->dev, "The tape unit does not support"
			" the current tape length\n");
		वापस tape_34xx_erp_failed(request, -EMEDIUMTYPE);
	हाल 0x5e:
		/* Compaction algorithm incompatible. */
		dev_warn (&device->cdev->dev, "The tape unit does not support"
			" the compaction algorithm\n");
		वापस tape_34xx_erp_failed(request, -EMEDIUMTYPE);

		/* The following erpas should have been covered earlier. */
	हाल 0x23: /* Read data check. */
	हाल 0x25: /* Write data check. */
	हाल 0x26: /* Data check (पढ़ो opposite). */
	हाल 0x28: /* Write id mark check. */
	हाल 0x31: /* Tape व्योम. */
	हाल 0x40: /* Overrun error. */
	हाल 0x41: /* Record sequence error. */
		/* All other erpas are reserved क्रम future use. */
	शेष:
		वापस tape_34xx_erp_bug(device, request, irb, sense[3]);
	पूर्ण
पूर्ण

/*
 * 3480/3490 पूर्णांकerrupt handler
 */
अटल पूर्णांक
tape_34xx_irq(काष्ठा tape_device *device, काष्ठा tape_request *request,
	      काष्ठा irb *irb)
अणु
	अगर (request == शून्य)
		वापस tape_34xx_unsolicited_irq(device, irb);

	अगर ((irb->scsw.cmd.dstat & DEV_STAT_UNIT_EXCEP) &&
	    (irb->scsw.cmd.dstat & DEV_STAT_DEV_END) &&
	    (request->op == TO_WRI)) अणु
		/* Write at end of volume */
		वापस tape_34xx_erp_failed(request, -ENOSPC);
	पूर्ण

	अगर (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK)
		वापस tape_34xx_unit_check(device, request, irb);

	अगर (irb->scsw.cmd.dstat & DEV_STAT_DEV_END) अणु
		/*
		 * A unit exception occurs on skipping over a tapemark block.
		 */
		अगर (irb->scsw.cmd.dstat & DEV_STAT_UNIT_EXCEP) अणु
			अगर (request->op == TO_BSB || request->op == TO_FSB)
				request->rescnt++;
			अन्यथा
				DBF_EVENT(5, "Unit Exception!\n");
		पूर्ण
		वापस tape_34xx_करोne(request);
	पूर्ण

	DBF_EVENT(6, "xunknownirq\n");
	tape_dump_sense_dbf(device, request, irb);
	वापस TAPE_IO_STOP;
पूर्ण

/*
 * ioctl_overload
 */
अटल पूर्णांक
tape_34xx_ioctl(काष्ठा tape_device *device, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अगर (cmd == TAPE390_DISPLAY) अणु
		काष्ठा display_काष्ठा disp;

		अगर (copy_from_user(&disp, (अक्षर __user *) arg, माप(disp)) != 0)
			वापस -EFAULT;

		वापस tape_std_display(device, &disp);
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम
tape_34xx_append_new_sbid(काष्ठा tape_34xx_block_id bid, काष्ठा list_head *l)
अणु
	काष्ठा tape_34xx_sbid *	new_sbid;

	new_sbid = kदो_स्मृति(माप(*new_sbid), GFP_ATOMIC);
	अगर (!new_sbid)
		वापस;

	new_sbid->bid = bid;
	list_add(&new_sbid->list, l);
पूर्ण

/*
 * Build up the search block ID list. The block ID consists of a logical
 * block number and a hardware specअगरic part. The hardware specअगरic part
 * helps the tape drive to speed up searching क्रम a specअगरic block.
 */
अटल व्योम
tape_34xx_add_sbid(काष्ठा tape_device *device, काष्ठा tape_34xx_block_id bid)
अणु
	काष्ठा list_head *	sbid_list;
	काष्ठा tape_34xx_sbid *	sbid;
	काष्ठा list_head *	l;

	/*
	 * immediately वापस अगर there is no list at all or the block to add
	 * is located in segment 1 of wrap 0 because this position is used
	 * अगर no hardware position data is supplied.
	 */
	sbid_list = (काष्ठा list_head *) device->discdata;
	अगर (!sbid_list || (bid.segment < 2 && bid.wrap == 0))
		वापस;

	/*
	 * Search the position where to insert the new entry. Hardware
	 * acceleration uses only the segment and wrap number. So we
	 * need only one entry क्रम a specअगरic wrap/segment combination.
	 * If there is a block with a lower number but the same hard-
	 * ware position data we just update the block number in the
	 * existing entry.
	 */
	list_क्रम_each(l, sbid_list) अणु
		sbid = list_entry(l, काष्ठा tape_34xx_sbid, list);

		अगर (
			(sbid->bid.segment == bid.segment) &&
			(sbid->bid.wrap    == bid.wrap)
		) अणु
			अगर (bid.block < sbid->bid.block)
				sbid->bid = bid;
			अन्यथा वापस;
			अवरोध;
		पूर्ण

		/* Sort in according to logical block number. */
		अगर (bid.block < sbid->bid.block) अणु
			tape_34xx_append_new_sbid(bid, l->prev);
			अवरोध;
		पूर्ण
	पूर्ण
	/* List empty or new block bigger than last entry. */
	अगर (l == sbid_list)
		tape_34xx_append_new_sbid(bid, l->prev);

	DBF_LH(4, "Current list is:\n");
	list_क्रम_each(l, sbid_list) अणु
		sbid = list_entry(l, काष्ठा tape_34xx_sbid, list);
		DBF_LH(4, "%d:%03d@%05d\n",
			sbid->bid.wrap,
			sbid->bid.segment,
			sbid->bid.block
		);
	पूर्ण
पूर्ण

/*
 * Delete all entries from the search block ID list that beदीर्घ to tape blocks
 * equal or higher than the given number.
 */
अटल व्योम
tape_34xx_delete_sbid_from(काष्ठा tape_device *device, पूर्णांक from)
अणु
	काष्ठा list_head *	sbid_list;
	काष्ठा tape_34xx_sbid *	sbid;
	काष्ठा list_head *	l;
	काष्ठा list_head *	n;

	sbid_list = (काष्ठा list_head *) device->discdata;
	अगर (!sbid_list)
		वापस;

	list_क्रम_each_safe(l, n, sbid_list) अणु
		sbid = list_entry(l, काष्ठा tape_34xx_sbid, list);
		अगर (sbid->bid.block >= from) अणु
			DBF_LH(4, "Delete sbid %d:%03d@%05d\n",
				sbid->bid.wrap,
				sbid->bid.segment,
				sbid->bid.block
			);
			list_del(l);
			kमुक्त(sbid);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Merge hardware position data पूर्णांकo a block id.
 */
अटल व्योम
tape_34xx_merge_sbid(
	काष्ठा tape_device *		device,
	काष्ठा tape_34xx_block_id *	bid
) अणु
	काष्ठा tape_34xx_sbid *	sbid;
	काष्ठा tape_34xx_sbid *	sbid_to_use;
	काष्ठा list_head *	sbid_list;
	काष्ठा list_head *	l;

	sbid_list = (काष्ठा list_head *) device->discdata;
	bid->wrap    = 0;
	bid->segment = 1;

	अगर (!sbid_list || list_empty(sbid_list))
		वापस;

	sbid_to_use = शून्य;
	list_क्रम_each(l, sbid_list) अणु
		sbid = list_entry(l, काष्ठा tape_34xx_sbid, list);

		अगर (sbid->bid.block >= bid->block)
			अवरोध;
		sbid_to_use = sbid;
	पूर्ण
	अगर (sbid_to_use) अणु
		bid->wrap    = sbid_to_use->bid.wrap;
		bid->segment = sbid_to_use->bid.segment;
		DBF_LH(4, "Use %d:%03d@%05d for %05d\n",
			sbid_to_use->bid.wrap,
			sbid_to_use->bid.segment,
			sbid_to_use->bid.block,
			bid->block
		);
	पूर्ण
पूर्ण

अटल पूर्णांक
tape_34xx_setup_device(काष्ठा tape_device * device)
अणु
	पूर्णांक			rc;
	काष्ठा list_head *	discdata;

	DBF_EVENT(6, "34xx device setup\n");
	अगर ((rc = tape_std_assign(device)) == 0) अणु
		अगर ((rc = tape_34xx_medium_sense(device)) != 0) अणु
			DBF_LH(3, "34xx medium sense returned %d\n", rc);
		पूर्ण
	पूर्ण
	discdata = kदो_स्मृति(माप(काष्ठा list_head), GFP_KERNEL);
	अगर (discdata) अणु
			INIT_LIST_HEAD(discdata);
			device->discdata = discdata;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम
tape_34xx_cleanup_device(काष्ठा tape_device *device)
अणु
	tape_std_unassign(device);
	
	अगर (device->discdata) अणु
		tape_34xx_delete_sbid_from(device, 0);
		kमुक्त(device->discdata);
		device->discdata = शून्य;
	पूर्ण
पूर्ण


/*
 * MTTELL: Tell block. Return the number of block relative to current file.
 */
अटल पूर्णांक
tape_34xx_mttell(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा अणु
		काष्ठा tape_34xx_block_id	cbid;
		काष्ठा tape_34xx_block_id	dbid;
	पूर्ण __attribute__ ((packed)) block_id;
	पूर्णांक rc;

	rc = tape_std_पढ़ो_block_id(device, (__u64 *) &block_id);
	अगर (rc)
		वापस rc;

	tape_34xx_add_sbid(device, block_id.cbid);
	वापस block_id.cbid.block;
पूर्ण

/*
 * MTSEEK: seek to the specअगरied block.
 */
अटल पूर्णांक
tape_34xx_mtseek(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;
	काष्ठा tape_34xx_block_id *	bid;

	अगर (mt_count > 0x3fffff) अणु
		DBF_EXCEPTION(6, "xsee parm\n");
		वापस -EINVAL;
	पूर्ण
	request = tape_alloc_request(3, 4);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);

	/* setup ccws */
	request->op = TO_LBL;
	bid         = (काष्ठा tape_34xx_block_id *) request->cpdata;
	bid->क्रमmat = (*device->modeset_byte & 0x08) ?
			TAPE34XX_FMT_3480_XF : TAPE34XX_FMT_3480;
	bid->block  = mt_count;
	tape_34xx_merge_sbid(device, bid);

	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_cc(request->cpaddr + 1, LOCATE, 4, request->cpdata);
	tape_ccw_end(request->cpaddr + 2, NOP, 0, शून्य);

	/* execute it */
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

/*
 * List of 3480/3490 magnetic tape commands.
 */
अटल tape_mtop_fn tape_34xx_mtop[TAPE_NR_MTOPS] = अणु
	[MTRESET]	 = tape_std_mtreset,
	[MTFSF]		 = tape_std_mtfsf,
	[MTBSF]		 = tape_std_mtbsf,
	[MTFSR]		 = tape_std_mtfsr,
	[MTBSR]		 = tape_std_mtbsr,
	[MTWखातापूर्ण]	 = tape_std_mtweof,
	[MTREW]		 = tape_std_mtrew,
	[MTOFFL]	 = tape_std_mtoffl,
	[MTNOP]		 = tape_std_mtnop,
	[MTRETEN]	 = tape_std_mtreten,
	[MTBSFM]	 = tape_std_mtbsfm,
	[MTFSFM]	 = tape_std_mtfsfm,
	[MTEOM]		 = tape_std_mteom,
	[MTERASE]	 = tape_std_mterase,
	[MTRAS1]	 = शून्य,
	[MTRAS2]	 = शून्य,
	[MTRAS3]	 = शून्य,
	[MTSETBLK]	 = tape_std_mtsetblk,
	[MTSETDENSITY]	 = शून्य,
	[MTSEEK]	 = tape_34xx_mtseek,
	[MTTELL]	 = tape_34xx_mttell,
	[MTSETDRVBUFFER] = शून्य,
	[MTFSS]		 = शून्य,
	[MTBSS]		 = शून्य,
	[MTWSM]		 = शून्य,
	[MTLOCK]	 = शून्य,
	[MTUNLOCK]	 = शून्य,
	[MTLOAD]	 = tape_std_mtload,
	[MTUNLOAD]	 = tape_std_mtunload,
	[MTCOMPRESSION]	 = tape_std_mtcompression,
	[MTSETPART]	 = शून्य,
	[MTMKPART]	 = शून्य
पूर्ण;

/*
 * Tape discipline काष्ठाure क्रम 3480 and 3490.
 */
अटल काष्ठा tape_discipline tape_discipline_34xx = अणु
	.owner = THIS_MODULE,
	.setup_device = tape_34xx_setup_device,
	.cleanup_device = tape_34xx_cleanup_device,
	.process_eov = tape_std_process_eov,
	.irq = tape_34xx_irq,
	.पढ़ो_block = tape_std_पढ़ो_block,
	.ग_लिखो_block = tape_std_ग_लिखो_block,
	.ioctl_fn = tape_34xx_ioctl,
	.mtop_array = tape_34xx_mtop
पूर्ण;

अटल काष्ठा ccw_device_id tape_34xx_ids[] = अणु
	अणु CCW_DEVICE_DEVTYPE(0x3480, 0, 0x3480, 0), .driver_info = tape_3480पूर्ण,
	अणु CCW_DEVICE_DEVTYPE(0x3490, 0, 0x3490, 0), .driver_info = tape_3490पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

अटल पूर्णांक
tape_34xx_online(काष्ठा ccw_device *cdev)
अणु
	वापस tape_generic_online(
		dev_get_drvdata(&cdev->dev),
		&tape_discipline_34xx
	);
पूर्ण

अटल काष्ठा ccw_driver tape_34xx_driver = अणु
	.driver = अणु
		.name = "tape_34xx",
		.owner = THIS_MODULE,
	पूर्ण,
	.ids = tape_34xx_ids,
	.probe = tape_generic_probe,
	.हटाओ = tape_generic_हटाओ,
	.set_online = tape_34xx_online,
	.set_offline = tape_generic_offline,
	.पूर्णांक_class = IRQIO_TAP,
पूर्ण;

अटल पूर्णांक
tape_34xx_init (व्योम)
अणु
	पूर्णांक rc;

	TAPE_DBF_AREA = debug_रेजिस्टर ( "tape_34xx", 2, 2, 4*माप(दीर्घ));
	debug_रेजिस्टर_view(TAPE_DBF_AREA, &debug_प्र_लिखो_view);
#अगर_घोषित DBF_LIKE_HELL
	debug_set_level(TAPE_DBF_AREA, 6);
#पूर्ण_अगर

	DBF_EVENT(3, "34xx init\n");
	/* Register driver क्रम 3480/3490 tapes. */
	rc = ccw_driver_रेजिस्टर(&tape_34xx_driver);
	अगर (rc)
		DBF_EVENT(3, "34xx init failed\n");
	अन्यथा
		DBF_EVENT(3, "34xx registered\n");
	वापस rc;
पूर्ण

अटल व्योम
tape_34xx_निकास(व्योम)
अणु
	ccw_driver_unरेजिस्टर(&tape_34xx_driver);

	debug_unरेजिस्टर(TAPE_DBF_AREA);
पूर्ण

MODULE_DEVICE_TABLE(ccw, tape_34xx_ids);
MODULE_AUTHOR("(C) 2001-2002 IBM Deutschland Entwicklung GmbH");
MODULE_DESCRIPTION("Linux on zSeries channel attached 3480 tape device driver");
MODULE_LICENSE("GPL");

module_init(tape_34xx_init);
module_निकास(tape_34xx_निकास);
