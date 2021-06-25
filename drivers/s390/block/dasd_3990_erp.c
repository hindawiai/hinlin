<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author(s)......: Horst  Hummel    <Horst.Hummel@de.ibm.com>
 *		    Holger Smolinski <Holger.Smolinski@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 2000, 2001
 *
 */

#घोषणा KMSG_COMPONENT "dasd-eckd"

#समावेश <linux/समयr.h>
#समावेश <यंत्र/idals.h>

#घोषणा PRINTK_HEADER "dasd_erp(3990): "

#समावेश "dasd_int.h"
#समावेश "dasd_eckd.h"


काष्ठा DCTL_data अणु
	अचिन्हित अक्षर subcommand;  /* e.g Inhibit Write, Enable Write,... */
	अचिन्हित अक्षर modअगरier;	   /* Subcommand modअगरier */
	अचिन्हित लघु res;	   /* reserved */
पूर्ण __attribute__ ((packed));

/*
 *****************************************************************************
 * SECTION ERP HANDLING
 *****************************************************************************
 */
/*
 *****************************************************************************
 * 24 and 32 byte sense ERP functions
 *****************************************************************************
 */

/*
 * DASD_3990_ERP_CLEANUP
 *
 * DESCRIPTION
 *   Removes the alपढ़ोy build but not necessary ERP request and sets
 *   the status of the original cqr / erp to the given (final) status
 *
 *  PARAMETER
 *   erp		request to be blocked
 *   final_status	either DASD_CQR_DONE or DASD_CQR_FAILED
 *
 * RETURN VALUES
 *   cqr		original cqr
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_cleanup(काष्ठा dasd_ccw_req * erp, अक्षर final_status)
अणु
	काष्ठा dasd_ccw_req *cqr = erp->refers;

	dasd_मुक्त_erp_request(erp, erp->memdev);
	cqr->status = final_status;
	वापस cqr;

पूर्ण				/* end dasd_3990_erp_cleanup */

/*
 * DASD_3990_ERP_BLOCK_QUEUE
 *
 * DESCRIPTION
 *   Block the given device request queue to prevent from further
 *   processing until the started समयr has expired or an related
 *   पूर्णांकerrupt was received.
 */
अटल व्योम dasd_3990_erp_block_queue(काष्ठा dasd_ccw_req *erp, पूर्णांक expires)
अणु

	काष्ठा dasd_device *device = erp->startdev;
	अचिन्हित दीर्घ flags;

	DBF_DEV_EVENT(DBF_INFO, device,
		    "blocking request queue for %is", expires/HZ);

	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	dasd_device_set_stop_bits(device, DASD_STOPPED_PENDING);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	erp->status = DASD_CQR_FILLED;
	अगर (erp->block)
		dasd_block_set_समयr(erp->block, expires);
	अन्यथा
		dasd_device_set_समयr(device, expires);
पूर्ण

/*
 * DASD_3990_ERP_INT_REQ
 *
 * DESCRIPTION
 *   Handles 'Intervention Required' error.
 *   This means either device offline or not installed.
 *
 * PARAMETER
 *   erp		current erp
 * RETURN VALUES
 *   erp		modअगरied erp
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_पूर्णांक_req(काष्ठा dasd_ccw_req * erp)
अणु

	काष्ठा dasd_device *device = erp->startdev;

	/* first समय set initial retry counter and erp_function */
	/* and retry once without blocking queue		 */
	/* (this enables easier enqueing of the cqr)		 */
	अगर (erp->function != dasd_3990_erp_पूर्णांक_req) अणु

		erp->retries = 256;
		erp->function = dasd_3990_erp_पूर्णांक_req;

	पूर्ण अन्यथा अणु

		/* issue a message and रुको क्रम 'device ready' पूर्णांकerrupt */
		dev_err(&device->cdev->dev,
			    "is offline or not installed - "
			    "INTERVENTION REQUIRED!!\n");

		dasd_3990_erp_block_queue(erp, 60*HZ);
	पूर्ण

	वापस erp;

पूर्ण				/* end dasd_3990_erp_पूर्णांक_req */

/*
 * DASD_3990_ERP_ALTERNATE_PATH
 *
 * DESCRIPTION
 *   Repeat the operation on a dअगरferent channel path.
 *   If all alternate paths have been tried, the request is posted with a
 *   permanent error.
 *
 *  PARAMETER
 *   erp		poपूर्णांकer to the current ERP
 *
 * RETURN VALUES
 *   erp		modअगरied poपूर्णांकer to the ERP
 */
अटल व्योम
dasd_3990_erp_alternate_path(काष्ठा dasd_ccw_req * erp)
अणु
	काष्ठा dasd_device *device = erp->startdev;
	__u8 opm;
	अचिन्हित दीर्घ flags;

	/* try alternate valid path */
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	opm = ccw_device_get_path_mask(device->cdev);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	अगर (erp->lpm == 0)
		erp->lpm = dasd_path_get_opm(device) &
			~(erp->irb.esw.esw0.sublog.lpum);
	अन्यथा
		erp->lpm &= ~(erp->irb.esw.esw0.sublog.lpum);

	अगर ((erp->lpm & opm) != 0x00) अणु

		DBF_DEV_EVENT(DBF_WARNING, device,
			    "try alternate lpm=%x (lpum=%x / opm=%x)",
			    erp->lpm, erp->irb.esw.esw0.sublog.lpum, opm);

		/* reset status to submit the request again... */
		erp->status = DASD_CQR_FILLED;
		erp->retries = 10;
	पूर्ण अन्यथा अणु
		dev_err(&device->cdev->dev,
			"The DASD cannot be reached on any path (lpum=%x"
			"/opm=%x)\n", erp->irb.esw.esw0.sublog.lpum, opm);

		/* post request with permanent error */
		erp->status = DASD_CQR_FAILED;
	पूर्ण
पूर्ण				/* end dasd_3990_erp_alternate_path */

/*
 * DASD_3990_ERP_DCTL
 *
 * DESCRIPTION
 *   Setup cqr to करो the Diagnostic Control (DCTL) command with an
 *   Inhibit Write subcommand (0x20) and the given modअगरier.
 *
 *  PARAMETER
 *   erp		poपूर्णांकer to the current (failed) ERP
 *   modअगरier		subcommand modअगरier
 *
 * RETURN VALUES
 *   dctl_cqr		poपूर्णांकer to NEW dctl_cqr
 *
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_DCTL(काष्ठा dasd_ccw_req * erp, अक्षर modअगरier)
अणु

	काष्ठा dasd_device *device = erp->startdev;
	काष्ठा DCTL_data *DCTL_data;
	काष्ठा ccw1 *ccw;
	काष्ठा dasd_ccw_req *dctl_cqr;

	dctl_cqr = dasd_alloc_erp_request((अक्षर *) &erp->magic, 1,
					  माप(काष्ठा DCTL_data),
					  device);
	अगर (IS_ERR(dctl_cqr)) अणु
		dev_err(&device->cdev->dev,
			    "Unable to allocate DCTL-CQR\n");
		erp->status = DASD_CQR_FAILED;
		वापस erp;
	पूर्ण

	DCTL_data = dctl_cqr->data;

	DCTL_data->subcommand = 0x02;	/* Inhibit Write */
	DCTL_data->modअगरier = modअगरier;

	ccw = dctl_cqr->cpaddr;
	स_रखो(ccw, 0, माप(काष्ठा ccw1));
	ccw->cmd_code = CCW_CMD_DCTL;
	ccw->count = 4;
	ccw->cda = (__u32)(addr_t) DCTL_data;
	dctl_cqr->flags = erp->flags;
	dctl_cqr->function = dasd_3990_erp_DCTL;
	dctl_cqr->refers = erp;
	dctl_cqr->startdev = device;
	dctl_cqr->memdev = device;
	dctl_cqr->magic = erp->magic;
	dctl_cqr->expires = 5 * 60 * HZ;
	dctl_cqr->retries = 2;

	dctl_cqr->buildclk = get_tod_घड़ी();

	dctl_cqr->status = DASD_CQR_FILLED;

	वापस dctl_cqr;

पूर्ण				/* end dasd_3990_erp_DCTL */

/*
 * DASD_3990_ERP_ACTION_1
 *
 * DESCRIPTION
 *   Setup ERP to करो the ERP action 1 (see Reference manual).
 *   Repeat the operation on a dअगरferent channel path.
 *   As deviation from the recommended recovery action, we reset the path mask
 *   after we have tried each path and go through all paths a second समय.
 *   This will cover situations where only one path at a समय is actually करोwn,
 *   but all paths fail and recover just with the same sequence and timing as
 *   we try to use them (flapping links).
 *   If all alternate paths have been tried twice, the request is posted with
 *   a permanent error.
 *
 *  PARAMETER
 *   erp		poपूर्णांकer to the current ERP
 *
 * RETURN VALUES
 *   erp		poपूर्णांकer to the ERP
 *
 */
अटल काष्ठा dasd_ccw_req *dasd_3990_erp_action_1_sec(काष्ठा dasd_ccw_req *erp)
अणु
	erp->function = dasd_3990_erp_action_1_sec;
	dasd_3990_erp_alternate_path(erp);
	वापस erp;
पूर्ण

अटल काष्ठा dasd_ccw_req *dasd_3990_erp_action_1(काष्ठा dasd_ccw_req *erp)
अणु
	erp->function = dasd_3990_erp_action_1;
	dasd_3990_erp_alternate_path(erp);
	अगर (erp->status == DASD_CQR_FAILED &&
	    !test_bit(DASD_CQR_VERIFY_PATH, &erp->flags)) अणु
		erp->status = DASD_CQR_FILLED;
		erp->retries = 10;
		erp->lpm = dasd_path_get_opm(erp->startdev);
		erp->function = dasd_3990_erp_action_1_sec;
	पूर्ण
	वापस erp;
पूर्ण				/* end dasd_3990_erp_action_1(b) */

/*
 * DASD_3990_ERP_ACTION_4
 *
 * DESCRIPTION
 *   Setup ERP to करो the ERP action 4 (see Reference manual).
 *   Set the current request to PENDING to block the CQR queue क्रम that device
 *   until the state change पूर्णांकerrupt appears.
 *   Use a समयr (20 seconds) to retry the cqr अगर the पूर्णांकerrupt is still
 *   missing.
 *
 *  PARAMETER
 *   sense		sense data of the actual error
 *   erp		poपूर्णांकer to the current ERP
 *
 * RETURN VALUES
 *   erp		poपूर्णांकer to the ERP
 *
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_action_4(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = erp->startdev;

	/* first समय set initial retry counter and erp_function    */
	/* and retry once without रुकोing क्रम state change pending  */
	/* पूर्णांकerrupt (this enables easier enqueing of the cqr)	    */
	अगर (erp->function != dasd_3990_erp_action_4) अणु

		DBF_DEV_EVENT(DBF_INFO, device, "%s",
			    "dasd_3990_erp_action_4: first time retry");

		erp->retries = 256;
		erp->function = dasd_3990_erp_action_4;

	पूर्ण अन्यथा अणु
		अगर (sense && (sense[25] == 0x1D)) अणु /* state change pending */

			DBF_DEV_EVENT(DBF_INFO, device,
				    "waiting for state change pending "
				    "interrupt, %d retries left",
				    erp->retries);

			dasd_3990_erp_block_queue(erp, 30*HZ);

		पूर्ण अन्यथा अगर (sense && (sense[25] == 0x1E)) अणु	/* busy */
			DBF_DEV_EVENT(DBF_INFO, device,
				    "busy - redriving request later, "
				    "%d retries left",
				    erp->retries);
                        dasd_3990_erp_block_queue(erp, HZ);
		पूर्ण अन्यथा अणु
			/* no state change pending - retry */
			DBF_DEV_EVENT(DBF_INFO, device,
				     "redriving request immediately, "
				     "%d retries left",
				     erp->retries);
			erp->status = DASD_CQR_FILLED;
		पूर्ण
	पूर्ण

	वापस erp;

पूर्ण				/* end dasd_3990_erp_action_4 */

/*
 *****************************************************************************
 * 24 byte sense ERP functions (only)
 *****************************************************************************
 */

/*
 * DASD_3990_ERP_ACTION_5
 *
 * DESCRIPTION
 *   Setup ERP to करो the ERP action 5 (see Reference manual).
 *   NOTE: Further handling is करोne in xxx_further_erp after the retries.
 *
 *  PARAMETER
 *   erp		poपूर्णांकer to the current ERP
 *
 * RETURN VALUES
 *   erp		poपूर्णांकer to the ERP
 *
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_action_5(काष्ठा dasd_ccw_req * erp)
अणु

	/* first of all retry */
	erp->retries = 10;
	erp->function = dasd_3990_erp_action_5;

	वापस erp;

पूर्ण				/* end dasd_3990_erp_action_5 */

/*
 * DASD_3990_HANDLE_ENV_DATA
 *
 * DESCRIPTION
 *   Handles 24 byte 'Environmental data present'.
 *   Does a analysis of the sense data (message Format)
 *   and prपूर्णांकs the error messages.
 *
 * PARAMETER
 *   sense		current sense data
 *
 * RETURN VALUES
 *   व्योम
 */
अटल व्योम
dasd_3990_handle_env_data(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = erp->startdev;
	अक्षर msg_क्रमmat = (sense[7] & 0xF0);
	अक्षर msg_no = (sense[7] & 0x0F);
	अक्षर errorstring[ERRORLENGTH];

	चयन (msg_क्रमmat) अणु
	हाल 0x00:		/* Format 0 - Program or System Checks */

		अगर (sense[1] & 0x10) अणु	/* check message to चालक bit */

			चयन (msg_no) अणु
			हाल 0x00:	/* No Message */
				अवरोध;
			हाल 0x01:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Invalid Command\n");
				अवरोध;
			हाल 0x02:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Invalid Command "
					    "Sequence\n");
				अवरोध;
			हाल 0x03:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - CCW Count less than "
					    "required\n");
				अवरोध;
			हाल 0x04:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Invalid Parameter\n");
				अवरोध;
			हाल 0x05:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Diagnostic of Special"
					    " Command Violates File Mask\n");
				अवरोध;
			हाल 0x07:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Channel Returned with "
					    "Incorrect retry CCW\n");
				अवरोध;
			हाल 0x08:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Reset Notification\n");
				अवरोध;
			हाल 0x09:
				dev_warn(&device->cdev->dev,
					 "FORMAT 0 - Storage Path Restart\n");
				अवरोध;
			हाल 0x0A:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Channel requested "
					    "... %02x\n", sense[8]);
				अवरोध;
			हाल 0x0B:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Invalid Defective/"
					    "Alternate Track Pointer\n");
				अवरोध;
			हाल 0x0C:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - DPS Installation "
					    "Check\n");
				अवरोध;
			हाल 0x0E:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Command Invalid on "
					    "Secondary Address\n");
				अवरोध;
			हाल 0x0F:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Status Not As "
					    "Required: reason %02x\n",
					 sense[8]);
				अवरोध;
			शेष:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Reserved\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (msg_no) अणु
			हाल 0x00:	/* No Message */
				अवरोध;
			हाल 0x01:
				dev_warn(&device->cdev->dev,
					 "FORMAT 0 - Device Error "
					 "Source\n");
				अवरोध;
			हाल 0x02:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Reserved\n");
				अवरोध;
			हाल 0x03:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Device Fenced - "
					    "device = %02x\n", sense[4]);
				अवरोध;
			हाल 0x04:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Data Pinned for "
					    "Device\n");
				अवरोध;
			शेष:
				dev_warn(&device->cdev->dev,
					    "FORMAT 0 - Reserved\n");
			पूर्ण
		पूर्ण
		अवरोध;

	हाल 0x10:		/* Format 1 - Device Equipment Checks */
		चयन (msg_no) अणु
		हाल 0x00:	/* No Message */
			अवरोध;
		हाल 0x01:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Device Status 1 not as "
				    "expected\n");
			अवरोध;
		हाल 0x03:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Index missing\n");
			अवरोध;
		हाल 0x04:
			dev_warn(&device->cdev->dev,
				 "FORMAT 1 - Interruption cannot be "
				 "reset\n");
			अवरोध;
		हाल 0x05:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Device did not respond to "
				    "selection\n");
			अवरोध;
		हाल 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Device check-2 error or Set "
				    "Sector is not complete\n");
			अवरोध;
		हाल 0x07:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Head address does not "
				    "compare\n");
			अवरोध;
		हाल 0x08:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Device status 1 not valid\n");
			अवरोध;
		हाल 0x09:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Device not ready\n");
			अवरोध;
		हाल 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Track physical address did "
				    "not compare\n");
			अवरोध;
		हाल 0x0B:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Missing device address bit\n");
			अवरोध;
		हाल 0x0C:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Drive motor switch is off\n");
			अवरोध;
		हाल 0x0D:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Seek incomplete\n");
			अवरोध;
		हाल 0x0E:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Cylinder address did not "
				    "compare\n");
			अवरोध;
		हाल 0x0F:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Offset active cannot be "
				    "reset\n");
			अवरोध;
		शेष:
			dev_warn(&device->cdev->dev,
				    "FORMAT 1 - Reserved\n");
		पूर्ण
		अवरोध;

	हाल 0x20:		/* Format 2 - 3990 Equipment Checks */
		चयन (msg_no) अणु
		हाल 0x08:
			dev_warn(&device->cdev->dev,
				    "FORMAT 2 - 3990 check-2 error\n");
			अवरोध;
		हाल 0x0E:
			dev_warn(&device->cdev->dev,
				    "FORMAT 2 - Support facility errors\n");
			अवरोध;
		हाल 0x0F:
			dev_warn(&device->cdev->dev,
				 "FORMAT 2 - Microcode detected error "
				 "%02x\n",
				 sense[8]);
			अवरोध;
		शेष:
			dev_warn(&device->cdev->dev,
				    "FORMAT 2 - Reserved\n");
		पूर्ण
		अवरोध;

	हाल 0x30:		/* Format 3 - 3990 Control Checks */
		चयन (msg_no) अणु
		हाल 0x0F:
			dev_warn(&device->cdev->dev,
				    "FORMAT 3 - Allegiance terminated\n");
			अवरोध;
		शेष:
			dev_warn(&device->cdev->dev,
				    "FORMAT 3 - Reserved\n");
		पूर्ण
		अवरोध;

	हाल 0x40:		/* Format 4 - Data Checks */
		चयन (msg_no) अणु
		हाल 0x00:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Home address area error\n");
			अवरोध;
		हाल 0x01:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Count area error\n");
			अवरोध;
		हाल 0x02:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Key area error\n");
			अवरोध;
		हाल 0x03:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Data area error\n");
			अवरोध;
		हाल 0x04:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in home address "
				    "area\n");
			अवरोध;
		हाल 0x05:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in count address "
				    "area\n");
			अवरोध;
		हाल 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in key area\n");
			अवरोध;
		हाल 0x07:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in data area\n");
			अवरोध;
		हाल 0x08:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Home address area error; "
				    "offset active\n");
			अवरोध;
		हाल 0x09:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Count area error; offset "
				    "active\n");
			अवरोध;
		हाल 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Key area error; offset "
				    "active\n");
			अवरोध;
		हाल 0x0B:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Data area error; "
				    "offset active\n");
			अवरोध;
		हाल 0x0C:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in home "
				    "address area; offset active\n");
			अवरोध;
		हाल 0x0D:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in count "
				    "address area; offset active\n");
			अवरोध;
		हाल 0x0E:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in key area; "
				    "offset active\n");
			अवरोध;
		हाल 0x0F:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - No sync byte in data area; "
				    "offset active\n");
			अवरोध;
		शेष:
			dev_warn(&device->cdev->dev,
				    "FORMAT 4 - Reserved\n");
		पूर्ण
		अवरोध;

	हाल 0x50:  /* Format 5 - Data Check with displacement inक्रमmation */
		चयन (msg_no) अणु
		हाल 0x00:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Data Check in the "
				    "home address area\n");
			अवरोध;
		हाल 0x01:
			dev_warn(&device->cdev->dev,
				 "FORMAT 5 - Data Check in the count "
				 "area\n");
			अवरोध;
		हाल 0x02:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Data Check in the key area\n");
			अवरोध;
		हाल 0x03:
			dev_warn(&device->cdev->dev,
				 "FORMAT 5 - Data Check in the data "
				 "area\n");
			अवरोध;
		हाल 0x08:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Data Check in the "
				    "home address area; offset active\n");
			अवरोध;
		हाल 0x09:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Data Check in the count area; "
				    "offset active\n");
			अवरोध;
		हाल 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Data Check in the key area; "
				    "offset active\n");
			अवरोध;
		हाल 0x0B:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Data Check in the data area; "
				    "offset active\n");
			अवरोध;
		शेष:
			dev_warn(&device->cdev->dev,
				    "FORMAT 5 - Reserved\n");
		पूर्ण
		अवरोध;

	हाल 0x60:  /* Format 6 - Usage Statistics/Overrun Errors */
		चयन (msg_no) अणु
		हाल 0x00:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel A\n");
			अवरोध;
		हाल 0x01:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel B\n");
			अवरोध;
		हाल 0x02:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel C\n");
			अवरोध;
		हाल 0x03:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel D\n");
			अवरोध;
		हाल 0x04:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel E\n");
			अवरोध;
		हाल 0x05:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel F\n");
			अवरोध;
		हाल 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel G\n");
			अवरोध;
		हाल 0x07:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Overrun on channel H\n");
			अवरोध;
		शेष:
			dev_warn(&device->cdev->dev,
				    "FORMAT 6 - Reserved\n");
		पूर्ण
		अवरोध;

	हाल 0x70:  /* Format 7 - Device Connection Control Checks */
		चयन (msg_no) अणु
		हाल 0x00:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - RCC initiated by a connection "
				    "check alert\n");
			अवरोध;
		हाल 0x01:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - RCC 1 sequence not "
				    "successful\n");
			अवरोध;
		हाल 0x02:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - RCC 1 and RCC 2 sequences not "
				    "successful\n");
			अवरोध;
		हाल 0x03:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Invalid tag-in during "
				    "selection sequence\n");
			अवरोध;
		हाल 0x04:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - extra RCC required\n");
			अवरोध;
		हाल 0x05:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Invalid DCC selection "
				    "response or timeout\n");
			अवरोध;
		हाल 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Missing end operation; device "
				    "transfer complete\n");
			अवरोध;
		हाल 0x07:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Missing end operation; device "
				    "transfer incomplete\n");
			अवरोध;
		हाल 0x08:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Invalid tag-in for an "
				    "immediate command sequence\n");
			अवरोध;
		हाल 0x09:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Invalid tag-in for an "
				    "extended command sequence\n");
			अवरोध;
		हाल 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - 3990 microcode time out when "
				    "stopping selection\n");
			अवरोध;
		हाल 0x0B:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - No response to selection "
				    "after a poll interruption\n");
			अवरोध;
		हाल 0x0C:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Permanent path error (DASD "
				    "controller not available)\n");
			अवरोध;
		हाल 0x0D:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - DASD controller not available"
				    " on disconnected command chain\n");
			अवरोध;
		शेष:
			dev_warn(&device->cdev->dev,
				    "FORMAT 7 - Reserved\n");
		पूर्ण
		अवरोध;

	हाल 0x80:  /* Format 8 - Additional Device Equipment Checks */
		चयन (msg_no) अणु
		हाल 0x00:	/* No Message */
		हाल 0x01:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - Error correction code "
				    "hardware fault\n");
			अवरोध;
		हाल 0x03:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - Unexpected end operation "
				    "response code\n");
			अवरोध;
		हाल 0x04:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - End operation with transfer "
				    "count not zero\n");
			अवरोध;
		हाल 0x05:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - End operation with transfer "
				    "count zero\n");
			अवरोध;
		हाल 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - DPS checks after a system "
				    "reset or selective reset\n");
			अवरोध;
		हाल 0x07:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - DPS cannot be filled\n");
			अवरोध;
		हाल 0x08:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - Short busy time-out during "
				    "device selection\n");
			अवरोध;
		हाल 0x09:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - DASD controller failed to "
				    "set or reset the long busy latch\n");
			अवरोध;
		हाल 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - No interruption from device "
				    "during a command chain\n");
			अवरोध;
		शेष:
			dev_warn(&device->cdev->dev,
				    "FORMAT 8 - Reserved\n");
		पूर्ण
		अवरोध;

	हाल 0x90:  /* Format 9 - Device Read, Write, and Seek Checks */
		चयन (msg_no) अणु
		हाल 0x00:
			अवरोध;	/* No Message */
		हाल 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT 9 - Device check-2 error\n");
			अवरोध;
		हाल 0x07:
			dev_warn(&device->cdev->dev,
				 "FORMAT 9 - Head address did not "
				 "compare\n");
			अवरोध;
		हाल 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT 9 - Track physical address did "
				    "not compare while oriented\n");
			अवरोध;
		हाल 0x0E:
			dev_warn(&device->cdev->dev,
				    "FORMAT 9 - Cylinder address did not "
				    "compare\n");
			अवरोध;
		शेष:
			dev_warn(&device->cdev->dev,
				    "FORMAT 9 - Reserved\n");
		पूर्ण
		अवरोध;

	हाल 0xF0:		/* Format F - Cache Storage Checks */
		चयन (msg_no) अणु
		हाल 0x00:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Operation Terminated\n");
			अवरोध;
		हाल 0x01:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Subsystem Processing Error\n");
			अवरोध;
		हाल 0x02:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Cache or nonvolatile storage "
				    "equipment failure\n");
			अवरोध;
		हाल 0x04:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Caching terminated\n");
			अवरोध;
		हाल 0x06:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Cache fast write access not "
				    "authorized\n");
			अवरोध;
		हाल 0x07:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Track format incorrect\n");
			अवरोध;
		हाल 0x09:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Caching reinitiated\n");
			अवरोध;
		हाल 0x0A:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Nonvolatile storage "
				    "terminated\n");
			अवरोध;
		हाल 0x0B:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Volume is suspended duplex\n");
			/* call extended error reporting (EER) */
			dasd_eer_ग_लिखो(device, erp->refers,
				       DASD_EER_PPRCSUSPEND);
			अवरोध;
		हाल 0x0C:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Subsystem status cannot be "
				    "determined\n");
			अवरोध;
		हाल 0x0D:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Caching status reset to "
				    "default\n");
			अवरोध;
		हाल 0x0E:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - DASD Fast Write inhibited\n");
			अवरोध;
		शेष:
			dev_warn(&device->cdev->dev,
				    "FORMAT F - Reserved\n");
		पूर्ण
		अवरोध;

	शेष:	/* unknown message क्रमmat - should not happen
			   पूर्णांकernal error 03 - unknown message क्रमmat */
		snम_लिखो(errorstring, ERRORLENGTH, "03 %x02", msg_क्रमmat);
		dev_err(&device->cdev->dev,
			 "An error occurred in the DASD device driver, "
			 "reason=%s\n", errorstring);
		अवरोध;
	पूर्ण			/* end चयन message क्रमmat */

पूर्ण				/* end dasd_3990_handle_env_data */

/*
 * DASD_3990_ERP_COM_REJ
 *
 * DESCRIPTION
 *   Handles 24 byte 'Command Reject' error.
 *
 * PARAMETER
 *   erp		current erp_head
 *   sense		current sense data
 *
 * RETURN VALUES
 *   erp		'new' erp_head - poपूर्णांकer to new ERP
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_com_rej(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = erp->startdev;

	erp->function = dasd_3990_erp_com_rej;

	/* env data present (ACTION 10 - retry should work) */
	अगर (sense[2] & SNS2_ENV_DATA_PRESENT) अणु

		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Command Reject - environmental data present");

		dasd_3990_handle_env_data(erp, sense);

		erp->retries = 5;

	पूर्ण अन्यथा अगर (sense[1] & SNS1_WRITE_INHIBITED) अणु
		dev_err(&device->cdev->dev, "An I/O request was rejected"
			" because writing is inhibited\n");
		erp = dasd_3990_erp_cleanup(erp, DASD_CQR_FAILED);
	पूर्ण अन्यथा अणु
		/* fatal error -  set status to FAILED
		   पूर्णांकernal error 09 - Command Reject */
		अगर (!test_bit(DASD_CQR_SUPPRESS_CR, &erp->flags))
			dev_err(&device->cdev->dev,
				"An error occurred in the DASD device driver, reason=09\n");

		erp = dasd_3990_erp_cleanup(erp, DASD_CQR_FAILED);
	पूर्ण

	वापस erp;

पूर्ण				/* end dasd_3990_erp_com_rej */

/*
 * DASD_3990_ERP_BUS_OUT
 *
 * DESCRIPTION
 *   Handles 24 byte 'Bus Out Parity Check' error.
 *
 * PARAMETER
 *   erp		current erp_head
 * RETURN VALUES
 *   erp		new erp_head - poपूर्णांकer to new ERP
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_bus_out(काष्ठा dasd_ccw_req * erp)
अणु

	काष्ठा dasd_device *device = erp->startdev;

	/* first समय set initial retry counter and erp_function */
	/* and retry once without blocking queue		 */
	/* (this enables easier enqueing of the cqr)		 */
	अगर (erp->function != dasd_3990_erp_bus_out) अणु
		erp->retries = 256;
		erp->function = dasd_3990_erp_bus_out;

	पूर्ण अन्यथा अणु

		/* issue a message and रुको क्रम 'device ready' पूर्णांकerrupt */
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "bus out parity error or BOPC requested by "
			    "channel");

		dasd_3990_erp_block_queue(erp, 60*HZ);

	पूर्ण

	वापस erp;

पूर्ण				/* end dasd_3990_erp_bus_out */

/*
 * DASD_3990_ERP_EQUIP_CHECK
 *
 * DESCRIPTION
 *   Handles 24 byte 'Equipment Check' error.
 *
 * PARAMETER
 *   erp		current erp_head
 * RETURN VALUES
 *   erp		new erp_head - poपूर्णांकer to new ERP
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_equip_check(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = erp->startdev;

	erp->function = dasd_3990_erp_equip_check;

	अगर (sense[1] & SNS1_WRITE_INHIBITED) अणु
		dev_info(&device->cdev->dev,
			    "Write inhibited path encountered\n");

		/* vary path offline
		   पूर्णांकernal error 04 - Path should be varied off-line.*/
		dev_err(&device->cdev->dev, "An error occurred in the DASD "
			"device driver, reason=%s\n", "04");

		erp = dasd_3990_erp_action_1(erp);

	पूर्ण अन्यथा अगर (sense[2] & SNS2_ENV_DATA_PRESENT) अणु

		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Equipment Check - " "environmental data present");

		dasd_3990_handle_env_data(erp, sense);

		erp = dasd_3990_erp_action_4(erp, sense);

	पूर्ण अन्यथा अगर (sense[1] & SNS1_PERM_ERR) अणु

		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Equipment Check - retry exhausted or "
			    "undesirable");

		erp = dasd_3990_erp_action_1(erp);

	पूर्ण अन्यथा अणु
		/* all other equipment checks - Action 5 */
		/* rest is करोne when retries == 0 */
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Equipment check or processing error");

		erp = dasd_3990_erp_action_5(erp);
	पूर्ण
	वापस erp;

पूर्ण				/* end dasd_3990_erp_equip_check */

/*
 * DASD_3990_ERP_DATA_CHECK
 *
 * DESCRIPTION
 *   Handles 24 byte 'Data Check' error.
 *
 * PARAMETER
 *   erp		current erp_head
 * RETURN VALUES
 *   erp		new erp_head - poपूर्णांकer to new ERP
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_data_check(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = erp->startdev;

	erp->function = dasd_3990_erp_data_check;

	अगर (sense[2] & SNS2_CORRECTABLE) अणु	/* correctable data check */

		/* issue message that the data has been corrected */
		dev_emerg(&device->cdev->dev,
			    "Data recovered during retry with PCI "
			    "fetch mode active\n");

		/* not possible to handle this situation in Linux */
		panic("No way to inform application about the possibly "
		      "incorrect data");

	पूर्ण अन्यथा अगर (sense[2] & SNS2_ENV_DATA_PRESENT) अणु

		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Uncorrectable data check recovered secondary "
			    "addr of duplex pair");

		erp = dasd_3990_erp_action_4(erp, sense);

	पूर्ण अन्यथा अगर (sense[1] & SNS1_PERM_ERR) अणु

		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Uncorrectable data check with internal "
			    "retry exhausted");

		erp = dasd_3990_erp_action_1(erp);

	पूर्ण अन्यथा अणु
		/* all other data checks */
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Uncorrectable data check with retry count "
			    "exhausted...");

		erp = dasd_3990_erp_action_5(erp);
	पूर्ण

	वापस erp;

पूर्ण				/* end dasd_3990_erp_data_check */

/*
 * DASD_3990_ERP_OVERRUN
 *
 * DESCRIPTION
 *   Handles 24 byte 'Overrun' error.
 *
 * PARAMETER
 *   erp		current erp_head
 * RETURN VALUES
 *   erp		new erp_head - poपूर्णांकer to new ERP
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_overrun(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = erp->startdev;

	erp->function = dasd_3990_erp_overrun;

	DBF_DEV_EVENT(DBF_WARNING, device, "%s",
		    "Overrun - service overrun or overrun"
		    " error requested by channel");

	erp = dasd_3990_erp_action_5(erp);

	वापस erp;

पूर्ण				/* end dasd_3990_erp_overrun */

/*
 * DASD_3990_ERP_INV_FORMAT
 *
 * DESCRIPTION
 *   Handles 24 byte 'Invalid Track Format' error.
 *
 * PARAMETER
 *   erp		current erp_head
 * RETURN VALUES
 *   erp		new erp_head - poपूर्णांकer to new ERP
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_inv_क्रमmat(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = erp->startdev;

	erp->function = dasd_3990_erp_inv_क्रमmat;

	अगर (sense[2] & SNS2_ENV_DATA_PRESENT) अणु

		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Track format error when destaging or "
			    "staging data");

		dasd_3990_handle_env_data(erp, sense);

		erp = dasd_3990_erp_action_4(erp, sense);

	पूर्ण अन्यथा अणु
		/* पूर्णांकernal error 06 - The track क्रमmat is not valid*/
		dev_err(&device->cdev->dev,
			"An error occurred in the DASD device driver, "
			"reason=%s\n", "06");

		erp = dasd_3990_erp_cleanup(erp, DASD_CQR_FAILED);
	पूर्ण

	वापस erp;

पूर्ण				/* end dasd_3990_erp_inv_क्रमmat */

/*
 * DASD_3990_ERP_EOC
 *
 * DESCRIPTION
 *   Handles 24 byte 'End-of-Cylinder' error.
 *
 * PARAMETER
 *   erp		alपढ़ोy added शेष erp
 * RETURN VALUES
 *   erp		poपूर्णांकer to original (failed) cqr.
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_EOC(काष्ठा dasd_ccw_req * शेष_erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = शेष_erp->startdev;

	dev_err(&device->cdev->dev,
		"The cylinder data for accessing the DASD is inconsistent\n");

	/* implement action 7 - BUG */
	वापस dasd_3990_erp_cleanup(शेष_erp, DASD_CQR_FAILED);

पूर्ण				/* end dasd_3990_erp_EOC */

/*
 * DASD_3990_ERP_ENV_DATA
 *
 * DESCRIPTION
 *   Handles 24 byte 'Environmental-Data Present' error.
 *
 * PARAMETER
 *   erp		current erp_head
 * RETURN VALUES
 *   erp		new erp_head - poपूर्णांकer to new ERP
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_env_data(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = erp->startdev;

	erp->function = dasd_3990_erp_env_data;

	DBF_DEV_EVENT(DBF_WARNING, device, "%s", "Environmental data present");

	dasd_3990_handle_env_data(erp, sense);

	/* करोn't retry on disabled पूर्णांकerface */
	अगर (sense[7] != 0x0F) अणु
		erp = dasd_3990_erp_action_4(erp, sense);
	पूर्ण अन्यथा अणु
		erp->status = DASD_CQR_FILLED;
	पूर्ण

	वापस erp;

पूर्ण				/* end dasd_3990_erp_env_data */

/*
 * DASD_3990_ERP_NO_REC
 *
 * DESCRIPTION
 *   Handles 24 byte 'No Record Found' error.
 *
 * PARAMETER
 *   erp		alपढ़ोy added शेष ERP
 *
 * RETURN VALUES
 *   erp		new erp_head - poपूर्णांकer to new ERP
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_no_rec(काष्ठा dasd_ccw_req * शेष_erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = शेष_erp->startdev;

	/*
	 * In some हालs the 'No Record Found' error might be expected and
	 * log messages shouldn't be written then.
	 * Check अगर the according suppress bit is set.
	 */
	अगर (!test_bit(DASD_CQR_SUPPRESS_NRF, &शेष_erp->flags))
		dev_err(&device->cdev->dev,
			"The specified record was not found\n");

	वापस dasd_3990_erp_cleanup(शेष_erp, DASD_CQR_FAILED);

पूर्ण				/* end dasd_3990_erp_no_rec */

/*
 * DASD_3990_ERP_खाता_PROT
 *
 * DESCRIPTION
 *   Handles 24 byte 'File Protected' error.
 *   Note: Seek related recovery is not implemented because
 *	   wee करोn't use the seek command yet.
 *
 * PARAMETER
 *   erp		current erp_head
 * RETURN VALUES
 *   erp		new erp_head - poपूर्णांकer to new ERP
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_file_prot(काष्ठा dasd_ccw_req * erp)
अणु

	काष्ठा dasd_device *device = erp->startdev;

	/*
	 * In some हालs the 'File Protected' error might be expected and
	 * log messages shouldn't be written then.
	 * Check अगर the according suppress bit is set.
	 */
	अगर (!test_bit(DASD_CQR_SUPPRESS_FP, &erp->flags))
		dev_err(&device->cdev->dev,
			"Accessing the DASD failed because of a hardware error\n");

	वापस dasd_3990_erp_cleanup(erp, DASD_CQR_FAILED);

पूर्ण				/* end dasd_3990_erp_file_prot */

/*
 * DASD_3990_ERP_INSPECT_ALIAS
 *
 * DESCRIPTION
 *   Checks अगर the original request was started on an alias device.
 *   If yes, it modअगरies the original and the erp request so that
 *   the erp request can be started on a base device.
 *
 * PARAMETER
 *   erp		poपूर्णांकer to the currently created शेष ERP
 *
 * RETURN VALUES
 *   erp		poपूर्णांकer to the modअगरied ERP, or शून्य
 */

अटल काष्ठा dasd_ccw_req *dasd_3990_erp_inspect_alias(
						काष्ठा dasd_ccw_req *erp)
अणु
	काष्ठा dasd_ccw_req *cqr = erp->refers;
	अक्षर *sense;

	अगर (cqr->block &&
	    (cqr->block->base != cqr->startdev)) अणु

		sense = dasd_get_sense(&erp->refers->irb);
		/*
		 * dynamic pav may have changed base alias mapping
		 */
		अगर (!test_bit(DASD_FLAG_OFFLINE, &cqr->startdev->flags) && sense
		    && (sense[0] == 0x10) && (sense[7] == 0x0F)
		    && (sense[8] == 0x67)) अणु
			/*
			 * हटाओ device from alias handling to prevent new
			 * requests from being scheduled on the
			 * wrong alias device
			 */
			dasd_alias_हटाओ_device(cqr->startdev);

			/* schedule worker to reload device */
			dasd_reload_device(cqr->startdev);
		पूर्ण

		अगर (cqr->startdev->features & DASD_FEATURE_ERPLOG) अणु
			DBF_DEV_EVENT(DBF_ERR, cqr->startdev,
				    "ERP on alias device for request %p,"
				    " recover on base device %s", cqr,
				    dev_name(&cqr->block->base->cdev->dev));
		पूर्ण
		dasd_eckd_reset_ccw_to_base_io(cqr);
		erp->startdev = cqr->block->base;
		erp->function = dasd_3990_erp_inspect_alias;
		वापस erp;
	पूर्ण अन्यथा
		वापस शून्य;
पूर्ण


/*
 * DASD_3990_ERP_INSPECT_24
 *
 * DESCRIPTION
 *   Does a detailed inspection of the 24 byte sense data
 *   and sets up a related error recovery action.
 *
 * PARAMETER
 *   sense		sense data of the actual error
 *   erp		poपूर्णांकer to the currently created शेष ERP
 *
 * RETURN VALUES
 *   erp		poपूर्णांकer to the (addtitional) ERP
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_inspect_24(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	काष्ठा dasd_ccw_req *erp_filled = शून्य;

	/* Check sense क्रम ....	   */
	/* 'Command Reject'	   */
	अगर ((erp_filled == शून्य) && (sense[0] & SNS0_CMD_REJECT)) अणु
		erp_filled = dasd_3990_erp_com_rej(erp, sense);
	पूर्ण
	/* 'Intervention Required' */
	अगर ((erp_filled == शून्य) && (sense[0] & SNS0_INTERVENTION_REQ)) अणु
		erp_filled = dasd_3990_erp_पूर्णांक_req(erp);
	पूर्ण
	/* 'Bus Out Parity Check'  */
	अगर ((erp_filled == शून्य) && (sense[0] & SNS0_BUS_OUT_CHECK)) अणु
		erp_filled = dasd_3990_erp_bus_out(erp);
	पूर्ण
	/* 'Equipment Check'	   */
	अगर ((erp_filled == शून्य) && (sense[0] & SNS0_EQUIPMENT_CHECK)) अणु
		erp_filled = dasd_3990_erp_equip_check(erp, sense);
	पूर्ण
	/* 'Data Check'		   */
	अगर ((erp_filled == शून्य) && (sense[0] & SNS0_DATA_CHECK)) अणु
		erp_filled = dasd_3990_erp_data_check(erp, sense);
	पूर्ण
	/* 'Overrun'		   */
	अगर ((erp_filled == शून्य) && (sense[0] & SNS0_OVERRUN)) अणु
		erp_filled = dasd_3990_erp_overrun(erp, sense);
	पूर्ण
	/* 'Invalid Track Format'  */
	अगर ((erp_filled == शून्य) && (sense[1] & SNS1_INV_TRACK_FORMAT)) अणु
		erp_filled = dasd_3990_erp_inv_क्रमmat(erp, sense);
	पूर्ण
	/* 'End-of-Cylinder'	   */
	अगर ((erp_filled == शून्य) && (sense[1] & SNS1_EOC)) अणु
		erp_filled = dasd_3990_erp_EOC(erp, sense);
	पूर्ण
	/* 'Environmental Data'	   */
	अगर ((erp_filled == शून्य) && (sense[2] & SNS2_ENV_DATA_PRESENT)) अणु
		erp_filled = dasd_3990_erp_env_data(erp, sense);
	पूर्ण
	/* 'No Record Found'	   */
	अगर ((erp_filled == शून्य) && (sense[1] & SNS1_NO_REC_FOUND)) अणु
		erp_filled = dasd_3990_erp_no_rec(erp, sense);
	पूर्ण
	/* 'File Protected'	   */
	अगर ((erp_filled == शून्य) && (sense[1] & SNS1_खाता_PROTECTED)) अणु
		erp_filled = dasd_3990_erp_file_prot(erp);
	पूर्ण
	/* other (unknown) error - करो शेष ERP */
	अगर (erp_filled == शून्य) अणु

		erp_filled = erp;
	पूर्ण

	वापस erp_filled;

पूर्ण				/* END dasd_3990_erp_inspect_24 */

/*
 *****************************************************************************
 * 32 byte sense ERP functions (only)
 *****************************************************************************
 */

/*
 * DASD_3990_ERPACTION_10_32
 *
 * DESCRIPTION
 *   Handles 32 byte 'Action 10' of Single Program Action Codes.
 *   Just retry and अगर retry करोesn't work, वापस with error.
 *
 * PARAMETER
 *   erp		current erp_head
 *   sense		current sense data
 * RETURN VALUES
 *   erp		modअगरied erp_head
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_action_10_32(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = erp->startdev;

	erp->retries = 256;
	erp->function = dasd_3990_erp_action_10_32;

	DBF_DEV_EVENT(DBF_WARNING, device, "%s", "Perform logging requested");

	वापस erp;

पूर्ण				/* end dasd_3990_erp_action_10_32 */

/*
 * DASD_3990_ERP_ACTION_1B_32
 *
 * DESCRIPTION
 *   Handles 32 byte 'Action 1B' of Single Program Action Codes.
 *   A ग_लिखो operation could not be finished because of an unexpected
 *   condition.
 *   The alपढ़ोy created 'default erp' is used to get the link to
 *   the erp chain, but it can not be used क्रम this recovery
 *   action because it contains no DE/LO data space.
 *
 * PARAMETER
 *   शेष_erp	alपढ़ोy added शेष erp.
 *   sense		current sense data
 *
 * RETURN VALUES
 *   erp		new erp or
 *			शेष_erp in हाल of imprecise ending or error
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_action_1B_32(काष्ठा dasd_ccw_req * शेष_erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = शेष_erp->startdev;
	__u32 cpa = 0;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा dasd_ccw_req *erp;
	काष्ठा DE_eckd_data *DE_data;
	काष्ठा PFX_eckd_data *PFX_data;
	अक्षर *LO_data;		/* LO_eckd_data_t */
	काष्ठा ccw1 *ccw, *oldccw;

	DBF_DEV_EVENT(DBF_WARNING, device, "%s",
		    "Write not finished because of unexpected condition");

	शेष_erp->function = dasd_3990_erp_action_1B_32;

	/* determine the original cqr */
	cqr = शेष_erp;

	जबतक (cqr->refers != शून्य) अणु
		cqr = cqr->refers;
	पूर्ण

	अगर (scsw_is_पंचांग(&cqr->irb.scsw)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "32 bit sense, action 1B is not defined"
			      " in transport mode - just retry");
		वापस शेष_erp;
	पूर्ण

	/* क्रम imprecise ending just करो शेष erp */
	अगर (sense[1] & 0x01) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Imprecise ending is set - just retry");

		वापस शेष_erp;
	पूर्ण

	/* determine the address of the CCW to be restarted */
	/* Imprecise ending is not set -> addr from IRB-SCSW */
	cpa = शेष_erp->refers->irb.scsw.cmd.cpa;

	अगर (cpa == 0) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Unable to determine address of the CCW "
			    "to be restarted");

		वापस dasd_3990_erp_cleanup(शेष_erp, DASD_CQR_FAILED);
	पूर्ण

	/* Build new ERP request including DE/LO */
	erp = dasd_alloc_erp_request((अक्षर *) &cqr->magic,
				     2 + 1,/* DE/LO + TIC */
				     माप(काष्ठा DE_eckd_data) +
				     माप(काष्ठा LO_eckd_data), device);

	अगर (IS_ERR(erp)) अणु
		/* पूर्णांकernal error 01 - Unable to allocate ERP */
		dev_err(&device->cdev->dev, "An error occurred in the DASD "
			"device driver, reason=%s\n", "01");
		वापस dasd_3990_erp_cleanup(शेष_erp, DASD_CQR_FAILED);
	पूर्ण

	/* use original DE */
	DE_data = erp->data;
	oldccw = cqr->cpaddr;
	अगर (oldccw->cmd_code == DASD_ECKD_CCW_PFX) अणु
		PFX_data = cqr->data;
		स_नकल(DE_data, &PFX_data->define_extent,
		       माप(काष्ठा DE_eckd_data));
	पूर्ण अन्यथा
		स_नकल(DE_data, cqr->data, माप(काष्ठा DE_eckd_data));

	/* create LO */
	LO_data = erp->data + माप(काष्ठा DE_eckd_data);

	अगर ((sense[3] == 0x01) && (LO_data[1] & 0x01)) अणु
		/* should not */
		वापस dasd_3990_erp_cleanup(शेष_erp, DASD_CQR_FAILED);
	पूर्ण

	अगर ((sense[7] & 0x3F) == 0x01) अणु
		/* operation code is WRITE DATA -> data area orientation */
		LO_data[0] = 0x81;

	पूर्ण अन्यथा अगर ((sense[7] & 0x3F) == 0x03) अणु
		/* operation code is FORMAT WRITE -> index orientation */
		LO_data[0] = 0xC3;

	पूर्ण अन्यथा अणु
		LO_data[0] = sense[7];	/* operation */
	पूर्ण

	LO_data[1] = sense[8];	/* auxiliary */
	LO_data[2] = sense[9];
	LO_data[3] = sense[3];	/* count */
	LO_data[4] = sense[29];	/* seek_addr.cyl */
	LO_data[5] = sense[30];	/* seek_addr.cyl 2nd byte */
	LO_data[7] = sense[31];	/* seek_addr.head 2nd byte */

	स_नकल(&(LO_data[8]), &(sense[11]), 8);

	/* create DE ccw */
	ccw = erp->cpaddr;
	स_रखो(ccw, 0, माप(काष्ठा ccw1));
	ccw->cmd_code = DASD_ECKD_CCW_DEFINE_EXTENT;
	ccw->flags = CCW_FLAG_CC;
	ccw->count = 16;
	ccw->cda = (__u32)(addr_t) DE_data;

	/* create LO ccw */
	ccw++;
	स_रखो(ccw, 0, माप(काष्ठा ccw1));
	ccw->cmd_code = DASD_ECKD_CCW_LOCATE_RECORD;
	ccw->flags = CCW_FLAG_CC;
	ccw->count = 16;
	ccw->cda = (__u32)(addr_t) LO_data;

	/* TIC to the failed ccw */
	ccw++;
	ccw->cmd_code = CCW_CMD_TIC;
	ccw->cda = cpa;

	/* fill erp related fields */
	erp->flags = शेष_erp->flags;
	erp->function = dasd_3990_erp_action_1B_32;
	erp->refers = शेष_erp->refers;
	erp->startdev = device;
	erp->memdev = device;
	erp->magic = शेष_erp->magic;
	erp->expires = शेष_erp->expires;
	erp->retries = 256;
	erp->buildclk = get_tod_घड़ी();
	erp->status = DASD_CQR_FILLED;

	/* हटाओ the शेष erp */
	dasd_मुक्त_erp_request(शेष_erp, device);

	वापस erp;

पूर्ण				/* end dasd_3990_erp_action_1B_32 */

/*
 * DASD_3990_UPDATE_1B
 *
 * DESCRIPTION
 *   Handles the update to the 32 byte 'Action 1B' of Single Program
 *   Action Codes in हाल the first action was not successful.
 *   The alपढ़ोy created 'previous_erp' is the currently not successful
 *   ERP.
 *
 * PARAMETER
 *   previous_erp	alपढ़ोy created previous erp.
 *   sense		current sense data
 * RETURN VALUES
 *   erp		modअगरied erp
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_update_1B(काष्ठा dasd_ccw_req * previous_erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = previous_erp->startdev;
	__u32 cpa = 0;
	काष्ठा dasd_ccw_req *cqr;
	काष्ठा dasd_ccw_req *erp;
	अक्षर *LO_data;		/* काष्ठा LO_eckd_data */
	काष्ठा ccw1 *ccw;

	DBF_DEV_EVENT(DBF_WARNING, device, "%s",
		    "Write not finished because of unexpected condition"
		    " - follow on");

	/* determine the original cqr */
	cqr = previous_erp;

	जबतक (cqr->refers != शून्य) अणु
		cqr = cqr->refers;
	पूर्ण

	अगर (scsw_is_पंचांग(&cqr->irb.scsw)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "32 bit sense, action 1B, update,"
			      " in transport mode - just retry");
		वापस previous_erp;
	पूर्ण

	/* क्रम imprecise ending just करो शेष erp */
	अगर (sense[1] & 0x01) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Imprecise ending is set - just retry");

		previous_erp->status = DASD_CQR_FILLED;

		वापस previous_erp;
	पूर्ण

	/* determine the address of the CCW to be restarted */
	/* Imprecise ending is not set -> addr from IRB-SCSW */
	cpa = previous_erp->irb.scsw.cmd.cpa;

	अगर (cpa == 0) अणु
		/* पूर्णांकernal error 02 -
		   Unable to determine address of the CCW to be restarted */
		dev_err(&device->cdev->dev, "An error occurred in the DASD "
			"device driver, reason=%s\n", "02");

		previous_erp->status = DASD_CQR_FAILED;

		वापस previous_erp;
	पूर्ण

	erp = previous_erp;

	/* update the LO with the new वापसed sense data  */
	LO_data = erp->data + माप(काष्ठा DE_eckd_data);

	अगर ((sense[3] == 0x01) && (LO_data[1] & 0x01)) अणु
		/* should not happen */
		previous_erp->status = DASD_CQR_FAILED;

		वापस previous_erp;
	पूर्ण

	अगर ((sense[7] & 0x3F) == 0x01) अणु
		/* operation code is WRITE DATA -> data area orientation */
		LO_data[0] = 0x81;

	पूर्ण अन्यथा अगर ((sense[7] & 0x3F) == 0x03) अणु
		/* operation code is FORMAT WRITE -> index orientation */
		LO_data[0] = 0xC3;

	पूर्ण अन्यथा अणु
		LO_data[0] = sense[7];	/* operation */
	पूर्ण

	LO_data[1] = sense[8];	/* auxiliary */
	LO_data[2] = sense[9];
	LO_data[3] = sense[3];	/* count */
	LO_data[4] = sense[29];	/* seek_addr.cyl */
	LO_data[5] = sense[30];	/* seek_addr.cyl 2nd byte */
	LO_data[7] = sense[31];	/* seek_addr.head 2nd byte */

	स_नकल(&(LO_data[8]), &(sense[11]), 8);

	/* TIC to the failed ccw */
	ccw = erp->cpaddr;	/* addr of DE ccw */
	ccw++;			/* addr of LE ccw */
	ccw++;			/* addr of TIC ccw */
	ccw->cda = cpa;

	erp->status = DASD_CQR_FILLED;

	वापस erp;

पूर्ण				/* end dasd_3990_update_1B */

/*
 * DASD_3990_ERP_COMPOUND_RETRY
 *
 * DESCRIPTION
 *   Handles the compound ERP action retry code.
 *   NOTE: At least one retry is करोne even अगर zero is specअगरied
 *	   by the sense data. This makes enqueueing of the request
 *	   easier.
 *
 * PARAMETER
 *   sense		sense data of the actual error
 *   erp		poपूर्णांकer to the currently created ERP
 *
 * RETURN VALUES
 *   erp		modअगरied ERP poपूर्णांकer
 *
 */
अटल व्योम
dasd_3990_erp_compound_retry(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	चयन (sense[25] & 0x03) अणु
	हाल 0x00:		/* no not retry */
		erp->retries = 1;
		अवरोध;

	हाल 0x01:		/* retry 2 बार */
		erp->retries = 2;
		अवरोध;

	हाल 0x02:		/* retry 10 बार */
		erp->retries = 10;
		अवरोध;

	हाल 0x03:		/* retry 256 बार */
		erp->retries = 256;
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	erp->function = dasd_3990_erp_compound_retry;

पूर्ण				/* end dasd_3990_erp_compound_retry */

/*
 * DASD_3990_ERP_COMPOUND_PATH
 *
 * DESCRIPTION
 *   Handles the compound ERP action क्रम retry on alternate
 *   channel path.
 *
 * PARAMETER
 *   sense		sense data of the actual error
 *   erp		poपूर्णांकer to the currently created ERP
 *
 * RETURN VALUES
 *   erp		modअगरied ERP poपूर्णांकer
 *
 */
अटल व्योम
dasd_3990_erp_compound_path(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु
	अगर (sense[25] & DASD_SENSE_BIT_3) अणु
		dasd_3990_erp_alternate_path(erp);

		अगर (erp->status == DASD_CQR_FAILED &&
		    !test_bit(DASD_CQR_VERIFY_PATH, &erp->flags)) अणु
			/* reset the lpm and the status to be able to
			 * try further actions. */
			erp->lpm = dasd_path_get_opm(erp->startdev);
			erp->status = DASD_CQR_NEED_ERP;
		पूर्ण
	पूर्ण

	erp->function = dasd_3990_erp_compound_path;

पूर्ण				/* end dasd_3990_erp_compound_path */

/*
 * DASD_3990_ERP_COMPOUND_CODE
 *
 * DESCRIPTION
 *   Handles the compound ERP action क्रम retry code.
 *
 * PARAMETER
 *   sense		sense data of the actual error
 *   erp		poपूर्णांकer to the currently created ERP
 *
 * RETURN VALUES
 *   erp		NEW ERP poपूर्णांकer
 *
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_compound_code(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	अगर (sense[25] & DASD_SENSE_BIT_2) अणु

		चयन (sense[28]) अणु
		हाल 0x17:
			/* issue a Diagnostic Control command with an
			 * Inhibit Write subcommand and controller modअगरier */
			erp = dasd_3990_erp_DCTL(erp, 0x20);
			अवरोध;

		हाल 0x25:
			/* रुको क्रम 5 seconds and retry again */
			erp->retries = 1;

			dasd_3990_erp_block_queue (erp, 5*HZ);
			अवरोध;

		शेष:
			/* should not happen - जारी */
			अवरोध;
		पूर्ण
	पूर्ण

	erp->function = dasd_3990_erp_compound_code;

	वापस erp;

पूर्ण				/* end dasd_3990_erp_compound_code */

/*
 * DASD_3990_ERP_COMPOUND_CONFIG
 *
 * DESCRIPTION
 *   Handles the compound ERP action क्रम configuration
 *   dependent error.
 *   Note: duplex handling is not implemented (yet).
 *
 * PARAMETER
 *   sense		sense data of the actual error
 *   erp		poपूर्णांकer to the currently created ERP
 *
 * RETURN VALUES
 *   erp		modअगरied ERP poपूर्णांकer
 *
 */
अटल व्योम
dasd_3990_erp_compound_config(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	अगर ((sense[25] & DASD_SENSE_BIT_1) && (sense[26] & DASD_SENSE_BIT_2)) अणु

		/* set to suspended duplex state then restart
		   पूर्णांकernal error 05 - Set device to suspended duplex state
		   should be करोne */
		काष्ठा dasd_device *device = erp->startdev;
		dev_err(&device->cdev->dev,
			"An error occurred in the DASD device driver, "
			"reason=%s\n", "05");

	पूर्ण

	erp->function = dasd_3990_erp_compound_config;

पूर्ण				/* end dasd_3990_erp_compound_config */

/*
 * DASD_3990_ERP_COMPOUND
 *
 * DESCRIPTION
 *   Does the further compound program action अगर
 *   compound retry was not successful.
 *
 * PARAMETER
 *   sense		sense data of the actual error
 *   erp		poपूर्णांकer to the current (failed) ERP
 *
 * RETURN VALUES
 *   erp		(additional) ERP poपूर्णांकer
 *
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_compound(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	अगर ((erp->function == dasd_3990_erp_compound_retry) &&
	    (erp->status == DASD_CQR_NEED_ERP)) अणु

		dasd_3990_erp_compound_path(erp, sense);
	पूर्ण

	अगर ((erp->function == dasd_3990_erp_compound_path) &&
	    (erp->status == DASD_CQR_NEED_ERP)) अणु

		erp = dasd_3990_erp_compound_code(erp, sense);
	पूर्ण

	अगर ((erp->function == dasd_3990_erp_compound_code) &&
	    (erp->status == DASD_CQR_NEED_ERP)) अणु

		dasd_3990_erp_compound_config(erp, sense);
	पूर्ण

	/* अगर no compound action ERP specअगरied, the request failed */
	अगर (erp->status == DASD_CQR_NEED_ERP)
		erp->status = DASD_CQR_FAILED;

	वापस erp;

पूर्ण				/* end dasd_3990_erp_compound */

/*
 *DASD_3990_ERP_HANDLE_SIM
 *
 *DESCRIPTION
 *  inspects the SIM SENSE data and starts an appropriate action
 *
 * PARAMETER
 *   sense	   sense data of the actual error
 *
 * RETURN VALUES
 *   none
 */
व्योम
dasd_3990_erp_handle_sim(काष्ठा dasd_device *device, अक्षर *sense)
अणु
	/* prपूर्णांक message according to log or message to चालक mode */
	अगर ((sense[24] & DASD_SIM_MSG_TO_OP) || (sense[1] & 0x10)) अणु
		/* prपूर्णांक SIM SRC from RefCode */
		dev_err(&device->cdev->dev, "SIM - SRC: "
			    "%02x%02x%02x%02x\n", sense[22],
			    sense[23], sense[11], sense[12]);
	पूर्ण अन्यथा अगर (sense[24] & DASD_SIM_LOG) अणु
		/* prपूर्णांक SIM SRC Refcode */
		dev_warn(&device->cdev->dev, "log SIM - SRC: "
			    "%02x%02x%02x%02x\n", sense[22],
			    sense[23], sense[11], sense[12]);
	पूर्ण
पूर्ण

/*
 * DASD_3990_ERP_INSPECT_32
 *
 * DESCRIPTION
 *   Does a detailed inspection of the 32 byte sense data
 *   and sets up a related error recovery action.
 *
 * PARAMETER
 *   sense		sense data of the actual error
 *   erp		poपूर्णांकer to the currently created शेष ERP
 *
 * RETURN VALUES
 *   erp_filled		poपूर्णांकer to the ERP
 *
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_inspect_32(काष्ठा dasd_ccw_req * erp, अक्षर *sense)
अणु

	काष्ठा dasd_device *device = erp->startdev;

	erp->function = dasd_3990_erp_inspect_32;

	/* check क्रम SIM sense data */
	अगर ((sense[6] & DASD_SIM_SENSE) == DASD_SIM_SENSE)
		dasd_3990_erp_handle_sim(device, sense);

	अगर (sense[25] & DASD_SENSE_BIT_0) अणु

		/* compound program action codes (byte25 bit 0 == '1') */
		dasd_3990_erp_compound_retry(erp, sense);

	पूर्ण अन्यथा अणु

		/* single program action codes (byte25 bit 0 == '0') */
		चयन (sense[25]) अणु

		हाल 0x00:	/* success - use शेष ERP क्रम retries */
			DBF_DEV_EVENT(DBF_DEBUG, device, "%s",
				    "ERP called for successful request"
				    " - just retry");
			अवरोध;

		हाल 0x01:	/* fatal error */
			dev_err(&device->cdev->dev,
				    "ERP failed for the DASD\n");

			erp = dasd_3990_erp_cleanup(erp, DASD_CQR_FAILED);
			अवरोध;

		हाल 0x02:	/* पूर्णांकervention required */
		हाल 0x03:	/* पूर्णांकervention required during dual copy */
			erp = dasd_3990_erp_पूर्णांक_req(erp);
			अवरोध;

		हाल 0x0F:  /* length mismatch during update ग_लिखो command
			       पूर्णांकernal error 08 - update ग_लिखो command error*/
			dev_err(&device->cdev->dev, "An error occurred in the "
				"DASD device driver, reason=%s\n", "08");

			erp = dasd_3990_erp_cleanup(erp, DASD_CQR_FAILED);
			अवरोध;

		हाल 0x10:  /* logging required क्रम other channel program */
			erp = dasd_3990_erp_action_10_32(erp, sense);
			अवरोध;

		हाल 0x15:	/* next track outside defined extend
				   पूर्णांकernal error 07 - The next track is not
				   within the defined storage extent */
			dev_err(&device->cdev->dev,
				"An error occurred in the DASD device driver, "
				"reason=%s\n", "07");

			erp = dasd_3990_erp_cleanup(erp, DASD_CQR_FAILED);
			अवरोध;

		हाल 0x1B:	/* unexpected condition during ग_लिखो */

			erp = dasd_3990_erp_action_1B_32(erp, sense);
			अवरोध;

		हाल 0x1C:	/* invalid data */
			dev_emerg(&device->cdev->dev,
				    "Data recovered during retry with PCI "
				    "fetch mode active\n");

			/* not possible to handle this situation in Linux */
			panic
			    ("Invalid data - No way to inform application "
			     "about the possibly incorrect data");
			अवरोध;

		हाल 0x1D:	/* state-change pending */
			DBF_DEV_EVENT(DBF_WARNING, device, "%s",
				    "A State change pending condition exists "
				    "for the subsystem or device");

			erp = dasd_3990_erp_action_4(erp, sense);
			अवरोध;

		हाल 0x1E:	/* busy */
			DBF_DEV_EVENT(DBF_WARNING, device, "%s",
				    "Busy condition exists "
				    "for the subsystem or device");
                        erp = dasd_3990_erp_action_4(erp, sense);
			अवरोध;

		शेष:	/* all others errors - शेष erp  */
			अवरोध;
		पूर्ण
	पूर्ण

	वापस erp;

पूर्ण				/* end dasd_3990_erp_inspect_32 */

अटल व्योम dasd_3990_erp_disable_path(काष्ठा dasd_device *device, __u8 lpum)
अणु
	पूर्णांक pos = pathmask_to_pos(lpum);

	अगर (!(device->features & DASD_FEATURE_PATH_AUTODISABLE)) अणु
		dev_err(&device->cdev->dev,
			"Path %x.%02x (pathmask %02x) is operational despite excessive IFCCs\n",
			device->path[pos].cssid, device->path[pos].chpid, lpum);
		जाओ out;
	पूर्ण

	/* no reमुख्यing path, cannot disable */
	अगर (!(dasd_path_get_opm(device) & ~lpum)) अणु
		dev_err(&device->cdev->dev,
			"Last path %x.%02x (pathmask %02x) is operational despite excessive IFCCs\n",
			device->path[pos].cssid, device->path[pos].chpid, lpum);
		जाओ out;
	पूर्ण

	dev_err(&device->cdev->dev,
		"Path %x.%02x (pathmask %02x) is disabled - IFCC threshold exceeded\n",
		device->path[pos].cssid, device->path[pos].chpid, lpum);
	dasd_path_हटाओ_opm(device, lpum);
	dasd_path_add_अगरccpm(device, lpum);

out:
	device->path[pos].errorclk = 0;
	atomic_set(&device->path[pos].error_count, 0);
पूर्ण

अटल व्योम dasd_3990_erp_account_error(काष्ठा dasd_ccw_req *erp)
अणु
	काष्ठा dasd_device *device = erp->startdev;
	__u8 lpum = erp->refers->irb.esw.esw1.lpum;
	पूर्णांक pos = pathmask_to_pos(lpum);
	अचिन्हित दीर्घ clk;

	अगर (!device->path_thrhld)
		वापस;

	clk = get_tod_घड़ी();
	/*
	 * check अगर the last error is दीर्घer ago than the समयout,
	 * अगर so reset error state
	 */
	अगर ((tod_to_ns(clk - device->path[pos].errorclk) / NSEC_PER_SEC)
	    >= device->path_पूर्णांकerval) अणु
		atomic_set(&device->path[pos].error_count, 0);
		device->path[pos].errorclk = 0;
	पूर्ण
	atomic_inc(&device->path[pos].error_count);
	device->path[pos].errorclk = clk;
	/* threshold exceeded disable path अगर possible */
	अगर (atomic_पढ़ो(&device->path[pos].error_count) >=
	    device->path_thrhld)
		dasd_3990_erp_disable_path(device, lpum);
पूर्ण

/*
 *****************************************************************************
 * मुख्य ERP control functions (24 and 32 byte sense)
 *****************************************************************************
 */

/*
 * DASD_3990_ERP_CONTROL_CHECK
 *
 * DESCRIPTION
 *   Does a generic inspection अगर a control check occurred and sets up
 *   the related error recovery procedure
 *
 * PARAMETER
 *   erp		poपूर्णांकer to the currently created शेष ERP
 *
 * RETURN VALUES
 *   erp_filled		poपूर्णांकer to the erp
 */

अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_control_check(काष्ठा dasd_ccw_req *erp)
अणु
	काष्ठा dasd_device *device = erp->startdev;

	अगर (scsw_cstat(&erp->refers->irb.scsw) & (SCHN_STAT_INTF_CTRL_CHK
					   | SCHN_STAT_CHN_CTRL_CHK)) अणु
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "channel or interface control check");
		dasd_3990_erp_account_error(erp);
		erp = dasd_3990_erp_action_4(erp, शून्य);
	पूर्ण
	वापस erp;
पूर्ण

/*
 * DASD_3990_ERP_INSPECT
 *
 * DESCRIPTION
 *   Does a detailed inspection क्रम sense data by calling either
 *   the 24-byte or the 32-byte inspection routine.
 *
 * PARAMETER
 *   erp		poपूर्णांकer to the currently created शेष ERP
 * RETURN VALUES
 *   erp_new		contens was possibly modअगरied
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_inspect(काष्ठा dasd_ccw_req *erp)
अणु

	काष्ठा dasd_ccw_req *erp_new = शून्य;
	अक्षर *sense;

	/* अगर this problem occurred on an alias retry on base */
	erp_new = dasd_3990_erp_inspect_alias(erp);
	अगर (erp_new)
		वापस erp_new;

	/* sense data are located in the refers record of the
	 * alपढ़ोy set up new ERP !
	 * check अगर concurrent sens is available
	 */
	sense = dasd_get_sense(&erp->refers->irb);
	अगर (!sense)
		erp_new = dasd_3990_erp_control_check(erp);
	/* distinguish between 24 and 32 byte sense data */
	अन्यथा अगर (sense[27] & DASD_SENSE_BIT_0) अणु

		/* inspect the 24 byte sense data */
		erp_new = dasd_3990_erp_inspect_24(erp, sense);

	पूर्ण अन्यथा अणु

		/* inspect the 32 byte sense data */
		erp_new = dasd_3990_erp_inspect_32(erp, sense);

	पूर्ण	/* end distinguish between 24 and 32 byte sense data */

	वापस erp_new;
पूर्ण

/*
 * DASD_3990_ERP_ADD_ERP
 *
 * DESCRIPTION
 *   This function adds an additional request block (ERP) to the head of
 *   the given cqr (or erp).
 *   For a command mode cqr the erp is initialized as an शेष erp
 *   (retry TIC).
 *   For transport mode we make a copy of the original TCW (poपूर्णांकs to
 *   the original TCCB, TIDALs, etc.) but give it a fresh
 *   TSB so the original sense data will not be changed.
 *
 * PARAMETER
 *   cqr		head of the current ERP-chain (or single cqr अगर
 *			first error)
 * RETURN VALUES
 *   erp		poपूर्णांकer to new ERP-chain head
 */
अटल काष्ठा dasd_ccw_req *dasd_3990_erp_add_erp(काष्ठा dasd_ccw_req *cqr)
अणु

	काष्ठा dasd_device *device = cqr->startdev;
	काष्ठा ccw1 *ccw;
	काष्ठा dasd_ccw_req *erp;
	पूर्णांक cplength, datasize;
	काष्ठा tcw *tcw;
	काष्ठा tsb *tsb;

	अगर (cqr->cpmode == 1) अणु
		cplength = 0;
		/* TCW needs to be 64 byte aligned, so leave enough room */
		datasize = 64 + माप(काष्ठा tcw) + माप(काष्ठा tsb);
	पूर्ण अन्यथा अणु
		cplength = 2;
		datasize = 0;
	पूर्ण

	/* allocate additional request block */
	erp = dasd_alloc_erp_request((अक्षर *) &cqr->magic,
				     cplength, datasize, device);
	अगर (IS_ERR(erp)) अणु
                अगर (cqr->retries <= 0) अणु
			DBF_DEV_EVENT(DBF_ERR, device, "%s",
				    "Unable to allocate ERP request");
			cqr->status = DASD_CQR_FAILED;
			cqr->stopclk = get_tod_घड़ी();
		पूर्ण अन्यथा अणु
			DBF_DEV_EVENT(DBF_ERR, device,
                                     "Unable to allocate ERP request "
				     "(%i retries left)",
                                     cqr->retries);
			dasd_block_set_समयr(device->block, (HZ << 3));
                पूर्ण
		वापस erp;
	पूर्ण

	ccw = cqr->cpaddr;
	अगर (cqr->cpmode == 1) अणु
		/* make a shallow copy of the original tcw but set new tsb */
		erp->cpmode = 1;
		erp->cpaddr = PTR_ALIGN(erp->data, 64);
		tcw = erp->cpaddr;
		tsb = (काष्ठा tsb *) &tcw[1];
		*tcw = *((काष्ठा tcw *)cqr->cpaddr);
		tcw->tsb = (दीर्घ)tsb;
	पूर्ण अन्यथा अगर (ccw->cmd_code == DASD_ECKD_CCW_PSF) अणु
		/* PSF cannot be chained from NOOP/TIC */
		erp->cpaddr = cqr->cpaddr;
	पूर्ण अन्यथा अणु
		/* initialize request with शेष TIC to current ERP/CQR */
		ccw = erp->cpaddr;
		ccw->cmd_code = CCW_CMD_NOOP;
		ccw->flags = CCW_FLAG_CC;
		ccw++;
		ccw->cmd_code = CCW_CMD_TIC;
		ccw->cda      = (दीर्घ)(cqr->cpaddr);
	पूर्ण

	erp->flags = cqr->flags;
	erp->function = dasd_3990_erp_add_erp;
	erp->refers   = cqr;
	erp->startdev = device;
	erp->memdev   = device;
	erp->block    = cqr->block;
	erp->magic    = cqr->magic;
	erp->expires  = cqr->expires;
	erp->retries  = 256;
	erp->buildclk = get_tod_घड़ी();
	erp->status = DASD_CQR_FILLED;

	वापस erp;
पूर्ण

/*
 * DASD_3990_ERP_ADDITIONAL_ERP
 *
 * DESCRIPTION
 *   An additional ERP is needed to handle the current error.
 *   Add ERP to the head of the ERP-chain containing the ERP processing
 *   determined based on the sense data.
 *
 * PARAMETER
 *   cqr		head of the current ERP-chain (or single cqr अगर
 *			first error)
 *
 * RETURN VALUES
 *   erp		poपूर्णांकer to new ERP-chain head
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_additional_erp(काष्ठा dasd_ccw_req * cqr)
अणु

	काष्ठा dasd_ccw_req *erp = शून्य;

	/* add erp and initialize with शेष TIC */
	erp = dasd_3990_erp_add_erp(cqr);

	अगर (IS_ERR(erp))
		वापस erp;

	/* inspect sense, determine specअगरic ERP अगर possible */
	अगर (erp != cqr) अणु

		erp = dasd_3990_erp_inspect(erp);
	पूर्ण

	वापस erp;

पूर्ण				/* end dasd_3990_erp_additional_erp */

/*
 * DASD_3990_ERP_ERROR_MATCH
 *
 * DESCRIPTION
 *   Check अगर the device status of the given cqr is the same.
 *   This means that the failed CCW and the relevant sense data
 *   must match.
 *   I करोn't distinguish between 24 and 32 byte sense because in हाल of
 *   24 byte sense byte 25 and 27 is set as well.
 *
 * PARAMETER
 *   cqr1		first cqr, which will be compared with the
 *   cqr2		second cqr.
 *
 * RETURN VALUES
 *   match		'boolean' क्रम match found
 *			वापसs 1 अगर match found, otherwise 0.
 */
अटल पूर्णांक dasd_3990_erp_error_match(काष्ठा dasd_ccw_req *cqr1,
				     काष्ठा dasd_ccw_req *cqr2)
अणु
	अक्षर *sense1, *sense2;

	अगर (cqr1->startdev != cqr2->startdev)
		वापस 0;

	sense1 = dasd_get_sense(&cqr1->irb);
	sense2 = dasd_get_sense(&cqr2->irb);

	/* one request has sense data, the other not -> no match, वापस 0 */
	अगर (!sense1 != !sense2)
		वापस 0;
	/* no sense data in both हालs -> check cstat क्रम IFCC */
	अगर (!sense1 && !sense2)	अणु
		अगर ((scsw_cstat(&cqr1->irb.scsw) & (SCHN_STAT_INTF_CTRL_CHK |
						    SCHN_STAT_CHN_CTRL_CHK)) ==
		    (scsw_cstat(&cqr2->irb.scsw) & (SCHN_STAT_INTF_CTRL_CHK |
						    SCHN_STAT_CHN_CTRL_CHK)))
			वापस 1; /* match with अगरcc*/
	पूर्ण
	/* check sense data; byte 0-2,25,27 */
	अगर (!(sense1 && sense2 &&
	      (स_भेद(sense1, sense2, 3) == 0) &&
	      (sense1[27] == sense2[27]) &&
	      (sense1[25] == sense2[25]))) अणु

		वापस 0;	/* sense करोesn't match */
	पूर्ण

	वापस 1;		/* match */

पूर्ण				/* end dasd_3990_erp_error_match */

/*
 * DASD_3990_ERP_IN_ERP
 *
 * DESCRIPTION
 *   check अगर the current error alपढ़ोy happened beक्रमe.
 *   quick निकास अगर current cqr is not an ERP (cqr->refers=शून्य)
 *
 * PARAMETER
 *   cqr		failed cqr (either original cqr or alपढ़ोy an erp)
 *
 * RETURN VALUES
 *   erp		erp-poपूर्णांकer to the alपढ़ोy defined error
 *			recovery procedure OR
 *			शून्य अगर a 'new' error occurred.
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_in_erp(काष्ठा dasd_ccw_req *cqr)
अणु

	काष्ठा dasd_ccw_req *erp_head = cqr,	/* save erp chain head */
	*erp_match = शून्य;	/* save erp chain head */
	पूर्णांक match = 0;		/* 'boolean' क्रम matching error found */

	अगर (cqr->refers == शून्य) अणु	/* वापस अगर not in erp */
		वापस शून्य;
	पूर्ण

	/* check the erp/cqr chain क्रम current error */
	करो अणु
		match = dasd_3990_erp_error_match(erp_head, cqr->refers);
		erp_match = cqr;	/* save possible matching erp  */
		cqr = cqr->refers;	/* check next erp/cqr in queue */

	पूर्ण जबतक ((cqr->refers != शून्य) && (!match));

	अगर (!match) अणु
		वापस शून्य;	/* no match was found */
	पूर्ण

	वापस erp_match;	/* वापस address of matching erp */

पूर्ण				/* END dasd_3990_erp_in_erp */

/*
 * DASD_3990_ERP_FURTHER_ERP (24 & 32 byte sense)
 *
 * DESCRIPTION
 *   No retry is left क्रम the current ERP. Check what has to be करोne
 *   with the ERP.
 *     - करो further defined ERP action or
 *     - रुको क्रम पूर्णांकerrupt or
 *     - निकास with permanent error
 *
 * PARAMETER
 *   erp		ERP which is in progress with no retry left
 *
 * RETURN VALUES
 *   erp		modअगरied/additional ERP
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_further_erp(काष्ठा dasd_ccw_req *erp)
अणु

	काष्ठा dasd_device *device = erp->startdev;
	अक्षर *sense = dasd_get_sense(&erp->irb);

	/* check क्रम 24 byte sense ERP */
	अगर ((erp->function == dasd_3990_erp_bus_out) ||
	    (erp->function == dasd_3990_erp_action_1) ||
	    (erp->function == dasd_3990_erp_action_4)) अणु

		erp = dasd_3990_erp_action_1(erp);

	पूर्ण अन्यथा अगर (erp->function == dasd_3990_erp_action_1_sec) अणु
		erp = dasd_3990_erp_action_1_sec(erp);
	पूर्ण अन्यथा अगर (erp->function == dasd_3990_erp_action_5) अणु

		/* retries have not been successful */
		/* prepare erp क्रम retry on dअगरferent channel path */
		erp = dasd_3990_erp_action_1(erp);

		अगर (sense && !(sense[2] & DASD_SENSE_BIT_0)) अणु

			/* issue a Diagnostic Control command with an
			 * Inhibit Write subcommand */

			चयन (sense[25]) अणु
			हाल 0x17:
			हाल 0x57:अणु	/* controller */
					erp = dasd_3990_erp_DCTL(erp, 0x20);
					अवरोध;
				पूर्ण
			हाल 0x18:
			हाल 0x58:अणु	/* channel path */
					erp = dasd_3990_erp_DCTL(erp, 0x40);
					अवरोध;
				पूर्ण
			हाल 0x19:
			हाल 0x59:अणु	/* storage director */
					erp = dasd_3990_erp_DCTL(erp, 0x80);
					अवरोध;
				पूर्ण
			शेष:
				DBF_DEV_EVENT(DBF_WARNING, device,
					    "invalid subcommand modifier 0x%x "
					    "for Diagnostic Control Command",
					    sense[25]);
			पूर्ण
		पूर्ण

		/* check क्रम 32 byte sense ERP */
	पूर्ण अन्यथा अगर (sense &&
		   ((erp->function == dasd_3990_erp_compound_retry) ||
		    (erp->function == dasd_3990_erp_compound_path) ||
		    (erp->function == dasd_3990_erp_compound_code) ||
		    (erp->function == dasd_3990_erp_compound_config))) अणु

		erp = dasd_3990_erp_compound(erp, sense);

	पूर्ण अन्यथा अणु
		/*
		 * No retry left and no additional special handling
		 * necessary
		 */
		dev_err(&device->cdev->dev,
			"ERP %p has run out of retries and failed\n", erp);

		erp->status = DASD_CQR_FAILED;
	पूर्ण

	वापस erp;

पूर्ण				/* end dasd_3990_erp_further_erp */

/*
 * DASD_3990_ERP_HANDLE_MATCH_ERP
 *
 * DESCRIPTION
 *   An error occurred again and an ERP has been detected which is alपढ़ोy
 *   used to handle this error (e.g. retries).
 *   All prior ERP's are asumed to be successful and thereक्रमe हटाओd
 *   from queue.
 *   If retry counter of matching erp is alपढ़ोy 0, it is checked अगर further
 *   action is needed (besides retry) or अगर the ERP has failed.
 *
 * PARAMETER
 *   erp_head		first ERP in ERP-chain
 *   erp		ERP that handles the actual error.
 *			(matching erp)
 *
 * RETURN VALUES
 *   erp		modअगरied/additional ERP
 */
अटल काष्ठा dasd_ccw_req *
dasd_3990_erp_handle_match_erp(काष्ठा dasd_ccw_req *erp_head,
			       काष्ठा dasd_ccw_req *erp)
अणु

	काष्ठा dasd_device *device = erp_head->startdev;
	काष्ठा dasd_ccw_req *erp_करोne = erp_head;	/* finished req */
	काष्ठा dasd_ccw_req *erp_मुक्त = शून्य;	/* req to be मुक्तd */

	/* loop over successful ERPs and हटाओ them from chanq */
	जबतक (erp_करोne != erp) अणु

		अगर (erp_करोne == शून्य)	/* end of chain reached */
			panic(PRINTK_HEADER "Programming error in ERP! The "
			      "original request was lost\n");

		/* हटाओ the request from the device queue */
		list_del(&erp_करोne->blocklist);

		erp_मुक्त = erp_करोne;
		erp_करोne = erp_करोne->refers;

		/* मुक्त the finished erp request */
		dasd_मुक्त_erp_request(erp_मुक्त, erp_मुक्त->memdev);

	पूर्ण			/* end जबतक */

	अगर (erp->retries > 0) अणु

		अक्षर *sense = dasd_get_sense(&erp->refers->irb);

		/* check क्रम special retries */
		अगर (sense && erp->function == dasd_3990_erp_action_4) अणु

			erp = dasd_3990_erp_action_4(erp, sense);

		पूर्ण अन्यथा अगर (sense &&
			   erp->function == dasd_3990_erp_action_1B_32) अणु

			erp = dasd_3990_update_1B(erp, sense);

		पूर्ण अन्यथा अगर (sense && erp->function == dasd_3990_erp_पूर्णांक_req) अणु

			erp = dasd_3990_erp_पूर्णांक_req(erp);

		पूर्ण अन्यथा अणु
			/* simple retry	  */
			DBF_DEV_EVENT(DBF_DEBUG, device,
				    "%i retries left for erp %p",
				    erp->retries, erp);

			/* handle the request again... */
			erp->status = DASD_CQR_FILLED;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* no retry left - check क्रम further necessary action	 */
		/* अगर no further actions, handle rest as permanent error */
		erp = dasd_3990_erp_further_erp(erp);
	पूर्ण

	वापस erp;

पूर्ण				/* end dasd_3990_erp_handle_match_erp */

/*
 * DASD_3990_ERP_ACTION
 *
 * DESCRIPTION
 *   control routine क्रम 3990 erp actions.
 *   Has to be called with the queue lock (namely the s390_irq_lock) acquired.
 *
 * PARAMETER
 *   cqr		failed cqr (either original cqr or alपढ़ोy an erp)
 *
 * RETURN VALUES
 *   erp		erp-poपूर्णांकer to the head of the ERP action chain.
 *			This means:
 *			 - either a ptr to an additional ERP cqr or
 *			 - the original given cqr (which's status might
 *			   be modअगरied)
 */
काष्ठा dasd_ccw_req *
dasd_3990_erp_action(काष्ठा dasd_ccw_req * cqr)
अणु
	काष्ठा dasd_ccw_req *erp = शून्य;
	काष्ठा dasd_device *device = cqr->startdev;
	काष्ठा dasd_ccw_req *temp_erp = शून्य;

	अगर (device->features & DASD_FEATURE_ERPLOG) अणु
		/* prपूर्णांक current erp_chain */
		dev_err(&device->cdev->dev,
			    "ERP chain at BEGINNING of ERP-ACTION\n");
		क्रम (temp_erp = cqr;
		     temp_erp != शून्य; temp_erp = temp_erp->refers) अणु

			dev_err(&device->cdev->dev,
				    "ERP %p (%02x) refers to %p\n",
				    temp_erp, temp_erp->status,
				    temp_erp->refers);
		पूर्ण
	पूर्ण

	/* द्विगुन-check अगर current erp/cqr was successful */
	अगर ((scsw_cstat(&cqr->irb.scsw) == 0x00) &&
	    (scsw_dstat(&cqr->irb.scsw) ==
	     (DEV_STAT_CHN_END | DEV_STAT_DEV_END))) अणु

		DBF_DEV_EVENT(DBF_DEBUG, device,
			    "ERP called for successful request %p"
			    " - NO ERP necessary", cqr);

		cqr->status = DASD_CQR_DONE;

		वापस cqr;
	पूर्ण

	/* check अगर error happened beक्रमe */
	erp = dasd_3990_erp_in_erp(cqr);

	अगर (erp == शून्य) अणु
		/* no matching erp found - set up erp */
		erp = dasd_3990_erp_additional_erp(cqr);
		अगर (IS_ERR(erp))
			वापस erp;
	पूर्ण अन्यथा अणु
		/* matching erp found - set all leading erp's to DONE */
		erp = dasd_3990_erp_handle_match_erp(cqr, erp);
	पूर्ण


	/*
	 * For path verअगरication work we need to stick with the path that was
	 * originally chosen so that the per path configuration data is
	 * asचिन्हित correctly.
	 */
	अगर (test_bit(DASD_CQR_VERIFY_PATH, &erp->flags) && cqr->lpm) अणु
		erp->lpm = cqr->lpm;
	पूर्ण

	अगर (device->features & DASD_FEATURE_ERPLOG) अणु
		/* prपूर्णांक current erp_chain */
		dev_err(&device->cdev->dev,
			    "ERP chain at END of ERP-ACTION\n");
		क्रम (temp_erp = erp;
		     temp_erp != शून्य; temp_erp = temp_erp->refers) अणु

			dev_err(&device->cdev->dev,
				    "ERP %p (%02x) refers to %p\n",
				    temp_erp, temp_erp->status,
				    temp_erp->refers);
		पूर्ण
	पूर्ण

	/* enqueue ERP request अगर it's a new one */
	अगर (list_empty(&erp->blocklist)) अणु
		cqr->status = DASD_CQR_IN_ERP;
		/* add erp request beक्रमe the cqr */
		list_add_tail(&erp->blocklist, &cqr->blocklist);
	पूर्ण



	वापस erp;

पूर्ण				/* end dasd_3990_erp_action */
