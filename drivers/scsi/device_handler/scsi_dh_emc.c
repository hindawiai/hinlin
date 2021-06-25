<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Target driver क्रम EMC CLARiiON AX/CX-series hardware.
 * Based on code from Lars Marowsky-Bree <lmb@suse.de>
 * and Ed Goggin <egoggin@emc.com>.
 *
 * Copyright (C) 2006 Red Hat, Inc.  All rights reserved.
 * Copyright (C) 2006 Mike Christie
 */
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_dh.h>
#समावेश <scsi/scsi_device.h>

#घोषणा CLARIION_NAME			"emc"

#घोषणा CLARIION_TRESPASS_PAGE		0x22
#घोषणा CLARIION_BUFFER_SIZE		0xFC
#घोषणा CLARIION_TIMEOUT		(60 * HZ)
#घोषणा CLARIION_RETRIES		3
#घोषणा CLARIION_UNBOUND_LU		-1
#घोषणा CLARIION_SP_A			0
#घोषणा CLARIION_SP_B			1

/* Flags */
#घोषणा CLARIION_SHORT_TRESPASS		1
#घोषणा CLARIION_HONOR_RESERVATIONS	2

/* LUN states */
#घोषणा CLARIION_LUN_UNINITIALIZED	-1
#घोषणा CLARIION_LUN_UNBOUND		0
#घोषणा CLARIION_LUN_BOUND		1
#घोषणा CLARIION_LUN_OWNED		2

अटल अचिन्हित अक्षर दीर्घ_trespass[] = अणु
	0, 0, 0, 0, 0, 0, 0, 0,
	CLARIION_TRESPASS_PAGE,	/* Page code */
	0x09,			/* Page length - 2 */
	0x01,			/* Trespass code */
	0xff, 0xff,		/* Trespass target */
	0, 0, 0, 0, 0, 0	/* Reserved bytes / unknown */
पूर्ण;

अटल अचिन्हित अक्षर लघु_trespass[] = अणु
	0, 0, 0, 0,
	CLARIION_TRESPASS_PAGE,	/* Page code */
	0x02,			/* Page length - 2 */
	0x01,			/* Trespass code */
	0xff,			/* Trespass target */
पूर्ण;

अटल स्थिर अक्षर * lun_state[] =
अणु
    "not bound",
    "bound",
    "owned",
पूर्ण;

काष्ठा clariion_dh_data अणु
	/*
	 * Flags:
	 *  CLARIION_SHORT_TRESPASS
	 * Use लघु trespass command (FC-series) or the दीर्घ version
	 * (शेष क्रम AX/CX CLARiiON arrays).
	 *
	 *  CLARIION_HONOR_RESERVATIONS
	 * Whether or not (शेष) to honor SCSI reservations when
	 * initiating a चयन-over.
	 */
	अचिन्हित flags;
	/*
	 * I/O buffer क्रम both MODE_SELECT and INQUIRY commands.
	 */
	अचिन्हित अक्षर buffer[CLARIION_BUFFER_SIZE];
	/*
	 * LUN state
	 */
	पूर्णांक lun_state;
	/*
	 * SP Port number
	 */
	पूर्णांक port;
	/*
	 * which SP (A=0,B=1,UNBOUND=-1) is the शेष SP क्रम this
	 * path's mapped LUN
	 */
	पूर्णांक शेष_sp;
	/*
	 * which SP (A=0,B=1,UNBOUND=-1) is the active SP क्रम this
	 * path's mapped LUN
	 */
	पूर्णांक current_sp;
पूर्ण;

/*
 * Parse MODE_SELECT cmd reply.
 */
अटल पूर्णांक trespass_endio(काष्ठा scsi_device *sdev,
			  काष्ठा scsi_sense_hdr *sshdr)
अणु
	पूर्णांक err = SCSI_DH_IO;

	sdev_prपूर्णांकk(KERN_ERR, sdev, "%s: Found valid sense data 0x%2x, "
		    "0x%2x, 0x%2x while sending CLARiiON trespass "
		    "command.\n", CLARIION_NAME, sshdr->sense_key,
		    sshdr->asc, sshdr->ascq);

	अगर (sshdr->sense_key == 0x05 && sshdr->asc == 0x04 &&
	    sshdr->ascq == 0x00) अणु
		/*
		 * Array based copy in progress -- करो not send
		 * mode_select or copy will be पातed mid-stream.
		 */
		sdev_prपूर्णांकk(KERN_INFO, sdev, "%s: Array Based Copy in "
			    "progress while sending CLARiiON trespass "
			    "command.\n", CLARIION_NAME);
		err = SCSI_DH_DEV_TEMP_BUSY;
	पूर्ण अन्यथा अगर (sshdr->sense_key == 0x02 && sshdr->asc == 0x04 &&
		   sshdr->ascq == 0x03) अणु
		/*
		 * LUN Not Ready - Manual Intervention Required
		 * indicates in-progress ucode upgrade (NDU).
		 */
		sdev_prपूर्णांकk(KERN_INFO, sdev, "%s: Detected in-progress "
			    "ucode upgrade NDU operation while sending "
			    "CLARiiON trespass command.\n", CLARIION_NAME);
		err = SCSI_DH_DEV_TEMP_BUSY;
	पूर्ण अन्यथा
		err = SCSI_DH_DEV_FAILED;
	वापस err;
पूर्ण

अटल पूर्णांक parse_sp_info_reply(काष्ठा scsi_device *sdev,
			       काष्ठा clariion_dh_data *csdev)
अणु
	पूर्णांक err = SCSI_DH_OK;

	/* check क्रम in-progress ucode upgrade (NDU) */
	अगर (csdev->buffer[48] != 0) अणु
		sdev_prपूर्णांकk(KERN_NOTICE, sdev, "%s: Detected in-progress "
			    "ucode upgrade NDU operation while finding "
			    "current active SP.", CLARIION_NAME);
		err = SCSI_DH_DEV_TEMP_BUSY;
		जाओ out;
	पूर्ण
	अगर (csdev->buffer[4] > 2) अणु
		/* Invalid buffer क्रमmat */
		sdev_prपूर्णांकk(KERN_NOTICE, sdev,
			    "%s: invalid VPD page 0xC0 format\n",
			    CLARIION_NAME);
		err = SCSI_DH_NOSYS;
		जाओ out;
	पूर्ण
	चयन (csdev->buffer[28] & 0x0f) अणु
	हाल 6:
		sdev_prपूर्णांकk(KERN_NOTICE, sdev,
			    "%s: ALUA failover mode detected\n",
			    CLARIION_NAME);
		अवरोध;
	हाल 4:
		/* Linux failover */
		अवरोध;
	शेष:
		sdev_prपूर्णांकk(KERN_WARNING, sdev,
			    "%s: Invalid failover mode %d\n",
			    CLARIION_NAME, csdev->buffer[28] & 0x0f);
		err = SCSI_DH_NOSYS;
		जाओ out;
	पूर्ण

	csdev->शेष_sp = csdev->buffer[5];
	csdev->lun_state = csdev->buffer[4];
	csdev->current_sp = csdev->buffer[8];
	csdev->port = csdev->buffer[7];
	अगर (csdev->lun_state == CLARIION_LUN_OWNED)
		sdev->access_state = SCSI_ACCESS_STATE_OPTIMAL;
	अन्यथा
		sdev->access_state = SCSI_ACCESS_STATE_STANDBY;
	अगर (csdev->शेष_sp == csdev->current_sp)
		sdev->access_state |= SCSI_ACCESS_STATE_PREFERRED;
out:
	वापस err;
पूर्ण

#घोषणा emc_शेष_str "FC (Legacy)"

अटल अक्षर * parse_sp_model(काष्ठा scsi_device *sdev, अचिन्हित अक्षर *buffer)
अणु
	अचिन्हित अक्षर len = buffer[4] + 5;
	अक्षर *sp_model = शून्य;
	अचिन्हित अक्षर sp_len, serial_len;

	अगर (len < 160) अणु
		sdev_prपूर्णांकk(KERN_WARNING, sdev,
			    "%s: Invalid information section length %d\n",
			    CLARIION_NAME, len);
		/* Check क्रम old FC arrays */
		अगर (!म_भेदन(buffer + 8, "DGC", 3)) अणु
			/* Old FC array, not supporting extended inक्रमmation */
			sp_model = emc_शेष_str;
		पूर्ण
		जाओ out;
	पूर्ण

	/*
	 * Parse extended inक्रमmation क्रम SP model number
	 */
	serial_len = buffer[160];
	अगर (serial_len == 0 || serial_len + 161 > len) अणु
		sdev_prपूर्णांकk(KERN_WARNING, sdev,
			    "%s: Invalid array serial number length %d\n",
			    CLARIION_NAME, serial_len);
		जाओ out;
	पूर्ण
	sp_len = buffer[99];
	अगर (sp_len == 0 || serial_len + sp_len + 161 > len) अणु
		sdev_prपूर्णांकk(KERN_WARNING, sdev,
			    "%s: Invalid model number length %d\n",
			    CLARIION_NAME, sp_len);
		जाओ out;
	पूर्ण
	sp_model = &buffer[serial_len + 161];
	/* Strip whitespace at the end */
	जबतक (sp_len > 1 && sp_model[sp_len - 1] == ' ')
		sp_len--;

	sp_model[sp_len] = '\0';

out:
	वापस sp_model;
पूर्ण

अटल पूर्णांक send_trespass_cmd(काष्ठा scsi_device *sdev,
			    काष्ठा clariion_dh_data *csdev)
अणु
	अचिन्हित अक्षर *page22;
	अचिन्हित अक्षर cdb[MAX_COMMAND_SIZE];
	पूर्णांक err, res = SCSI_DH_OK, len;
	काष्ठा scsi_sense_hdr sshdr;
	u64 req_flags = REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT |
		REQ_FAILFAST_DRIVER;

	अगर (csdev->flags & CLARIION_SHORT_TRESPASS) अणु
		page22 = लघु_trespass;
		अगर (!(csdev->flags & CLARIION_HONOR_RESERVATIONS))
			/* Set Honor Reservations bit */
			page22[6] |= 0x80;
		len = माप(लघु_trespass);
		cdb[0] = MODE_SELECT;
		cdb[1] = 0x10;
		cdb[4] = len;
	पूर्ण अन्यथा अणु
		page22 = दीर्घ_trespass;
		अगर (!(csdev->flags & CLARIION_HONOR_RESERVATIONS))
			/* Set Honor Reservations bit */
			page22[10] |= 0x80;
		len = माप(दीर्घ_trespass);
		cdb[0] = MODE_SELECT_10;
		cdb[8] = len;
	पूर्ण
	BUG_ON((len > CLARIION_BUFFER_SIZE));
	स_नकल(csdev->buffer, page22, len);

	err = scsi_execute(sdev, cdb, DMA_TO_DEVICE, csdev->buffer, len, शून्य,
			&sshdr, CLARIION_TIMEOUT * HZ, CLARIION_RETRIES,
			req_flags, 0, शून्य);
	अगर (err) अणु
		अगर (scsi_sense_valid(&sshdr))
			res = trespass_endio(sdev, &sshdr);
		अन्यथा अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "%s: failed to send MODE SELECT: %x\n",
				    CLARIION_NAME, err);
			res = SCSI_DH_IO;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल क्रमागत scsi_disposition clariion_check_sense(काष्ठा scsi_device *sdev,
					काष्ठा scsi_sense_hdr *sense_hdr)
अणु
	चयन (sense_hdr->sense_key) अणु
	हाल NOT_READY:
		अगर (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x03)
			/*
			 * LUN Not Ready - Manual Intervention Required
			 * indicates this is a passive path.
			 *
			 * FIXME: However, अगर this is seen and EVPD C0
			 * indicates that this is due to a NDU in
			 * progress, we should set FAIL_PATH too.
			 * This indicates we might have to करो a SCSI
			 * inquiry in the end_io path. Ugh.
			 *
			 * Can वापस FAILED only when we want the error
			 * recovery process to kick in.
			 */
			वापस SUCCESS;
		अवरोध;
	हाल ILLEGAL_REQUEST:
		अगर (sense_hdr->asc == 0x25 && sense_hdr->ascq == 0x01)
			/*
			 * An array based copy is in progress. Do not
			 * fail the path, करो not bypass to another PG,
			 * करो not retry. Fail the IO immediately.
			 * (Actually this is the same conclusion as in
			 * the शेष handler, but lets make sure.)
			 *
			 * Can वापस FAILED only when we want the error
			 * recovery process to kick in.
			 */
			वापस SUCCESS;
		अवरोध;
	हाल UNIT_ATTENTION:
		अगर (sense_hdr->asc == 0x29 && sense_hdr->ascq == 0x00)
			/*
			 * Unit Attention Code. This is the first IO
			 * to the new path, so just retry.
			 */
			वापस ADD_TO_MLQUEUE;
		अवरोध;
	पूर्ण

	वापस SCSI_RETURN_NOT_HANDLED;
पूर्ण

अटल blk_status_t clariion_prep_fn(काष्ठा scsi_device *sdev,
		काष्ठा request *req)
अणु
	काष्ठा clariion_dh_data *h = sdev->handler_data;

	अगर (h->lun_state != CLARIION_LUN_OWNED) अणु
		req->rq_flags |= RQF_QUIET;
		वापस BLK_STS_IOERR;
	पूर्ण

	वापस BLK_STS_OK;
पूर्ण

अटल पूर्णांक clariion_std_inquiry(काष्ठा scsi_device *sdev,
				काष्ठा clariion_dh_data *csdev)
अणु
	पूर्णांक err = SCSI_DH_OK;
	अक्षर *sp_model;

	sp_model = parse_sp_model(sdev, sdev->inquiry);
	अगर (!sp_model) अणु
		err = SCSI_DH_DEV_UNSUPP;
		जाओ out;
	पूर्ण

	/*
	 * FC Series arrays करो not support दीर्घ trespass
	 */
	अगर (!म_माप(sp_model) || !म_भेदन(sp_model, "FC",2))
		csdev->flags |= CLARIION_SHORT_TRESPASS;

	sdev_prपूर्णांकk(KERN_INFO, sdev,
		    "%s: detected Clariion %s, flags %x\n",
		    CLARIION_NAME, sp_model, csdev->flags);
out:
	वापस err;
पूर्ण

अटल पूर्णांक clariion_send_inquiry(काष्ठा scsi_device *sdev,
				 काष्ठा clariion_dh_data *csdev)
अणु
	पूर्णांक err = SCSI_DH_IO;

	अगर (!scsi_get_vpd_page(sdev, 0xC0, csdev->buffer,
			       CLARIION_BUFFER_SIZE))
		err = parse_sp_info_reply(sdev, csdev);

	वापस err;
पूर्ण

अटल पूर्णांक clariion_activate(काष्ठा scsi_device *sdev,
				activate_complete fn, व्योम *data)
अणु
	काष्ठा clariion_dh_data *csdev = sdev->handler_data;
	पूर्णांक result;

	result = clariion_send_inquiry(sdev, csdev);
	अगर (result != SCSI_DH_OK)
		जाओ करोne;

	अगर (csdev->lun_state == CLARIION_LUN_OWNED)
		जाओ करोne;

	result = send_trespass_cmd(sdev, csdev);
	अगर (result != SCSI_DH_OK)
		जाओ करोne;
	sdev_prपूर्णांकk(KERN_INFO, sdev,"%s: %s trespass command sent\n",
		    CLARIION_NAME,
		    csdev->flags&CLARIION_SHORT_TRESPASS?"short":"long" );

	/* Update status */
	result = clariion_send_inquiry(sdev, csdev);
	अगर (result != SCSI_DH_OK)
		जाओ करोne;

करोne:
	sdev_prपूर्णांकk(KERN_INFO, sdev,
		    "%s: at SP %c Port %d (%s, default SP %c)\n",
		    CLARIION_NAME, csdev->current_sp + 'A',
		    csdev->port, lun_state[csdev->lun_state],
		    csdev->शेष_sp + 'A');

	अगर (fn)
		fn(data, result);
	वापस 0;
पूर्ण
/*
 * params - parameters in the following क्रमmat
 *      "no_of_params\0param1\0param2\0param3\0...\0"
 *      क्रम example, string क्रम 2 parameters with value 10 and 21
 *      is specअगरied as "2\010\021\0".
 */
अटल पूर्णांक clariion_set_params(काष्ठा scsi_device *sdev, स्थिर अक्षर *params)
अणु
	काष्ठा clariion_dh_data *csdev = sdev->handler_data;
	अचिन्हित पूर्णांक hr = 0, st = 0, argc;
	स्थिर अक्षर *p = params;
	पूर्णांक result = SCSI_DH_OK;

	अगर ((माला_पूछो(params, "%u", &argc) != 1) || (argc != 2))
		वापस -EINVAL;

	जबतक (*p++)
		;
	अगर ((माला_पूछो(p, "%u", &st) != 1) || (st > 1))
		वापस -EINVAL;

	जबतक (*p++)
		;
	अगर ((माला_पूछो(p, "%u", &hr) != 1) || (hr > 1))
		वापस -EINVAL;

	अगर (st)
		csdev->flags |= CLARIION_SHORT_TRESPASS;
	अन्यथा
		csdev->flags &= ~CLARIION_SHORT_TRESPASS;

	अगर (hr)
		csdev->flags |= CLARIION_HONOR_RESERVATIONS;
	अन्यथा
		csdev->flags &= ~CLARIION_HONOR_RESERVATIONS;

	/*
	 * If this path is owned, we have to send a trespass command
	 * with the new parameters. If not, simply वापस. Next trespass
	 * command would use the parameters.
	 */
	अगर (csdev->lun_state != CLARIION_LUN_OWNED)
		जाओ करोne;

	csdev->lun_state = CLARIION_LUN_UNINITIALIZED;
	result = send_trespass_cmd(sdev, csdev);
	अगर (result != SCSI_DH_OK)
		जाओ करोne;

	/* Update status */
	result = clariion_send_inquiry(sdev, csdev);

करोne:
	वापस result;
पूर्ण

अटल पूर्णांक clariion_bus_attach(काष्ठा scsi_device *sdev)
अणु
	काष्ठा clariion_dh_data *h;
	पूर्णांक err;

	h = kzalloc(माप(*h) , GFP_KERNEL);
	अगर (!h)
		वापस SCSI_DH_NOMEM;
	h->lun_state = CLARIION_LUN_UNINITIALIZED;
	h->शेष_sp = CLARIION_UNBOUND_LU;
	h->current_sp = CLARIION_UNBOUND_LU;

	err = clariion_std_inquiry(sdev, h);
	अगर (err != SCSI_DH_OK)
		जाओ failed;

	err = clariion_send_inquiry(sdev, h);
	अगर (err != SCSI_DH_OK)
		जाओ failed;

	sdev_prपूर्णांकk(KERN_INFO, sdev,
		    "%s: connected to SP %c Port %d (%s, default SP %c)\n",
		    CLARIION_NAME, h->current_sp + 'A',
		    h->port, lun_state[h->lun_state],
		    h->शेष_sp + 'A');

	sdev->handler_data = h;
	वापस SCSI_DH_OK;

failed:
	kमुक्त(h);
	वापस err;
पूर्ण

अटल व्योम clariion_bus_detach(काष्ठा scsi_device *sdev)
अणु
	kमुक्त(sdev->handler_data);
	sdev->handler_data = शून्य;
पूर्ण

अटल काष्ठा scsi_device_handler clariion_dh = अणु
	.name		= CLARIION_NAME,
	.module		= THIS_MODULE,
	.attach		= clariion_bus_attach,
	.detach		= clariion_bus_detach,
	.check_sense	= clariion_check_sense,
	.activate	= clariion_activate,
	.prep_fn	= clariion_prep_fn,
	.set_params	= clariion_set_params,
पूर्ण;

अटल पूर्णांक __init clariion_init(व्योम)
अणु
	पूर्णांक r;

	r = scsi_रेजिस्टर_device_handler(&clariion_dh);
	अगर (r != 0)
		prपूर्णांकk(KERN_ERR "%s: Failed to register scsi device handler.",
			CLARIION_NAME);
	वापस r;
पूर्ण

अटल व्योम __निकास clariion_निकास(व्योम)
अणु
	scsi_unरेजिस्टर_device_handler(&clariion_dh);
पूर्ण

module_init(clariion_init);
module_निकास(clariion_निकास);

MODULE_DESCRIPTION("EMC CX/AX/FC-family driver");
MODULE_AUTHOR("Mike Christie <michaelc@cs.wisc.edu>, Chandra Seetharaman <sekharan@us.ibm.com>");
MODULE_LICENSE("GPL");
