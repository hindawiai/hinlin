<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    standard tape device functions क्रम ibm tapes.
 *
 *  S390 and zSeries version
 *    Copyright IBM Corp. 2001, 2002
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *		 Michael Holzheu <holzheu@de.ibm.com>
 *		 Tuan Ngo-Anh <ngoanh@de.ibm.com>
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>
 *		 Stefan Bader <shbader@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "tape"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/bपन.स>
#समावेश <linux/समयr.h>

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/idals.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/tape390.h>

#घोषणा TAPE_DBF_AREA	tape_core_dbf

#समावेश "tape.h"
#समावेश "tape_std.h"

/*
 * tape_std_assign
 */
अटल व्योम
tape_std_assign_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा tape_request *	request = from_समयr(request, t, समयr);
	काष्ठा tape_device *	device = request->device;
	पूर्णांक rc;

	BUG_ON(!device);

	DBF_EVENT(3, "%08x: Assignment timeout. Device busy.\n",
			device->cdev_id);
	rc = tape_cancel_io(device, request);
	अगर(rc)
		DBF_EVENT(3, "(%08x): Assign timeout: Cancel failed with rc = "
			  "%i\n", device->cdev_id, rc);
पूर्ण

पूर्णांक
tape_std_assign(काष्ठा tape_device *device)
अणु
	पूर्णांक                  rc;
	काष्ठा समयr_list    समयout;
	काष्ठा tape_request *request;

	request = tape_alloc_request(2, 11);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);

	request->op = TO_ASSIGN;
	tape_ccw_cc(request->cpaddr, ASSIGN, 11, request->cpdata);
	tape_ccw_end(request->cpaddr + 1, NOP, 0, शून्य);

	/*
	 * The assign command someबार blocks अगर the device is asचिन्हित
	 * to another host (actually this shouldn't happen but it करोes).
	 * So we set up a समयout क्रम this call.
	 */
	समयr_setup(&request->समयr, tape_std_assign_समयout, 0);
	mod_समयr(&समयout, jअगरfies + 2 * HZ);

	rc = tape_करो_io_पूर्णांकerruptible(device, request);

	del_समयr_sync(&request->समयr);

	अगर (rc != 0) अणु
		DBF_EVENT(3, "%08x: assign failed - device might be busy\n",
			device->cdev_id);
	पूर्ण अन्यथा अणु
		DBF_EVENT(3, "%08x: Tape assigned\n", device->cdev_id);
	पूर्ण
	tape_मुक्त_request(request);
	वापस rc;
पूर्ण

/*
 * tape_std_unassign
 */
पूर्णांक
tape_std_unassign (काष्ठा tape_device *device)
अणु
	पूर्णांक                  rc;
	काष्ठा tape_request *request;

	अगर (device->tape_state == TS_NOT_OPER) अणु
		DBF_EVENT(3, "(%08x): Can't unassign device\n",
			device->cdev_id);
		वापस -EIO;
	पूर्ण

	request = tape_alloc_request(2, 11);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);

	request->op = TO_UNASSIGN;
	tape_ccw_cc(request->cpaddr, UNASSIGN, 11, request->cpdata);
	tape_ccw_end(request->cpaddr + 1, NOP, 0, शून्य);

	अगर ((rc = tape_करो_io(device, request)) != 0) अणु
		DBF_EVENT(3, "%08x: Unassign failed\n", device->cdev_id);
	पूर्ण अन्यथा अणु
		DBF_EVENT(3, "%08x: Tape unassigned\n", device->cdev_id);
	पूर्ण
	tape_मुक्त_request(request);
	वापस rc;
पूर्ण

/*
 * TAPE390_DISPLAY: Show a string on the tape display.
 */
पूर्णांक
tape_std_display(काष्ठा tape_device *device, काष्ठा display_काष्ठा *disp)
अणु
	काष्ठा tape_request *request;
	पूर्णांक rc;

	request = tape_alloc_request(2, 17);
	अगर (IS_ERR(request)) अणु
		DBF_EVENT(3, "TAPE: load display failed\n");
		वापस PTR_ERR(request);
	पूर्ण
	request->op = TO_DIS;

	*(अचिन्हित अक्षर *) request->cpdata = disp->cntrl;
	DBF_EVENT(5, "TAPE: display cntrl=%04x\n", disp->cntrl);
	स_नकल(((अचिन्हित अक्षर *) request->cpdata) + 1, disp->message1, 8);
	स_नकल(((अचिन्हित अक्षर *) request->cpdata) + 9, disp->message2, 8);
	ASCEBC(((अचिन्हित अक्षर*) request->cpdata) + 1, 16);

	tape_ccw_cc(request->cpaddr, LOAD_DISPLAY, 17, request->cpdata);
	tape_ccw_end(request->cpaddr + 1, NOP, 0, शून्य);

	rc = tape_करो_io_पूर्णांकerruptible(device, request);
	tape_मुक्त_request(request);
	वापस rc;
पूर्ण

/*
 * Read block id.
 */
पूर्णांक
tape_std_पढ़ो_block_id(काष्ठा tape_device *device, __u64 *id)
अणु
	काष्ठा tape_request *request;
	पूर्णांक rc;

	request = tape_alloc_request(3, 8);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_RBI;
	/* setup ccws */
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_cc(request->cpaddr + 1, READ_BLOCK_ID, 8, request->cpdata);
	tape_ccw_end(request->cpaddr + 2, NOP, 0, शून्य);
	/* execute it */
	rc = tape_करो_io(device, request);
	अगर (rc == 0)
		/* Get result from पढ़ो buffer. */
		*id = *(__u64 *) request->cpdata;
	tape_मुक्त_request(request);
	वापस rc;
पूर्ण

पूर्णांक
tape_std_terminate_ग_लिखो(काष्ठा tape_device *device)
अणु
	पूर्णांक rc;

	अगर(device->required_tapemarks == 0)
		वापस 0;

	DBF_LH(5, "tape%d: terminate write %dxEOF\n", device->first_minor,
		device->required_tapemarks);

	rc = tape_mtop(device, MTWखातापूर्ण, device->required_tapemarks);
	अगर (rc)
		वापस rc;

	device->required_tapemarks = 0;
	वापस tape_mtop(device, MTBSR, 1);
पूर्ण

/*
 * MTLOAD: Loads the tape.
 * The शेष implementation just रुको until the tape medium state changes
 * to MS_LOADED.
 */
पूर्णांक
tape_std_mtload(काष्ठा tape_device *device, पूर्णांक count)
अणु
	वापस रुको_event_पूर्णांकerruptible(device->state_change_wq,
		(device->medium_state == MS_LOADED));
पूर्ण

/*
 * MTSETBLK: Set block size.
 */
पूर्णांक
tape_std_mtsetblk(काष्ठा tape_device *device, पूर्णांक count)
अणु
	काष्ठा idal_buffer *new;

	DBF_LH(6, "tape_std_mtsetblk(%d)\n", count);
	अगर (count <= 0) अणु
		/*
		 * Just set block_size to 0. tapeअक्षर_पढ़ो/tapeअक्षर_ग_लिखो
		 * will पुनः_स्मृति the idal buffer अगर a bigger one than the
		 * current is needed.
		 */
		device->अक्षर_data.block_size = 0;
		वापस 0;
	पूर्ण
	अगर (device->अक्षर_data.idal_buf != शून्य &&
	    device->अक्षर_data.idal_buf->size == count)
		/* We alपढ़ोy have a idal buffer of that size. */
		वापस 0;

	अगर (count > MAX_BLOCKSIZE) अणु
		DBF_EVENT(3, "Invalid block size (%d > %d) given.\n",
			count, MAX_BLOCKSIZE);
		वापस -EINVAL;
	पूर्ण

	/* Allocate a new idal buffer. */
	new = idal_buffer_alloc(count, 0);
	अगर (IS_ERR(new))
		वापस -ENOMEM;
	अगर (device->अक्षर_data.idal_buf != शून्य)
		idal_buffer_मुक्त(device->अक्षर_data.idal_buf);
	device->अक्षर_data.idal_buf = new;
	device->अक्षर_data.block_size = count;

	DBF_LH(6, "new blocksize is %d\n", device->अक्षर_data.block_size);

	वापस 0;
पूर्ण

/*
 * MTRESET: Set block size to 0.
 */
पूर्णांक
tape_std_mtreset(काष्ठा tape_device *device, पूर्णांक count)
अणु
	DBF_EVENT(6, "TCHAR:devreset:\n");
	device->अक्षर_data.block_size = 0;
	वापस 0;
पूर्ण

/*
 * MTFSF: Forward space over 'count' file marks. The tape is positioned
 * at the EOT (End of Tape) side of the file mark.
 */
पूर्णांक
tape_std_mtfsf(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;
	काष्ठा ccw1 *ccw;

	request = tape_alloc_request(mt_count + 2, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_FSF;
	/* setup ccws */
	ccw = tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1,
			  device->modeset_byte);
	ccw = tape_ccw_repeat(ccw, FORSPACEखाता, mt_count);
	ccw = tape_ccw_end(ccw, NOP, 0, शून्य);

	/* execute it */
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

/*
 * MTFSR: Forward space over 'count' tape blocks (blocksize is set
 * via MTSETBLK.
 */
पूर्णांक
tape_std_mtfsr(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;
	काष्ठा ccw1 *ccw;
	पूर्णांक rc;

	request = tape_alloc_request(mt_count + 2, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_FSB;
	/* setup ccws */
	ccw = tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1,
			  device->modeset_byte);
	ccw = tape_ccw_repeat(ccw, FORSPACEBLOCK, mt_count);
	ccw = tape_ccw_end(ccw, NOP, 0, शून्य);

	/* execute it */
	rc = tape_करो_io(device, request);
	अगर (rc == 0 && request->rescnt > 0) अणु
		DBF_LH(3, "FSR over tapemark\n");
		rc = 1;
	पूर्ण
	tape_मुक्त_request(request);

	वापस rc;
पूर्ण

/*
 * MTBSR: Backward space over 'count' tape blocks.
 * (blocksize is set via MTSETBLK.
 */
पूर्णांक
tape_std_mtbsr(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;
	काष्ठा ccw1 *ccw;
	पूर्णांक rc;

	request = tape_alloc_request(mt_count + 2, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_BSB;
	/* setup ccws */
	ccw = tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1,
			  device->modeset_byte);
	ccw = tape_ccw_repeat(ccw, BACKSPACEBLOCK, mt_count);
	ccw = tape_ccw_end(ccw, NOP, 0, शून्य);

	/* execute it */
	rc = tape_करो_io(device, request);
	अगर (rc == 0 && request->rescnt > 0) अणु
		DBF_LH(3, "BSR over tapemark\n");
		rc = 1;
	पूर्ण
	tape_मुक्त_request(request);

	वापस rc;
पूर्ण

/*
 * MTWखातापूर्ण: Write 'count' file marks at the current position.
 */
पूर्णांक
tape_std_mtweof(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;
	काष्ठा ccw1 *ccw;

	request = tape_alloc_request(mt_count + 2, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_WTM;
	/* setup ccws */
	ccw = tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1,
			  device->modeset_byte);
	ccw = tape_ccw_repeat(ccw, WRITETAPEMARK, mt_count);
	ccw = tape_ccw_end(ccw, NOP, 0, शून्य);

	/* execute it */
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

/*
 * MTBSFM: Backward space over 'count' file marks.
 * The tape is positioned at the BOT (Begin Of Tape) side of the
 * last skipped file mark.
 */
पूर्णांक
tape_std_mtbsfm(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;
	काष्ठा ccw1 *ccw;

	request = tape_alloc_request(mt_count + 2, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_BSF;
	/* setup ccws */
	ccw = tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1,
			  device->modeset_byte);
	ccw = tape_ccw_repeat(ccw, BACKSPACEखाता, mt_count);
	ccw = tape_ccw_end(ccw, NOP, 0, शून्य);

	/* execute it */
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

/*
 * MTBSF: Backward space over 'count' file marks. The tape is positioned at
 * the EOT (End of Tape) side of the last skipped file mark.
 */
पूर्णांक
tape_std_mtbsf(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;
	काष्ठा ccw1 *ccw;
	पूर्णांक rc;

	request = tape_alloc_request(mt_count + 2, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_BSF;
	/* setup ccws */
	ccw = tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1,
			  device->modeset_byte);
	ccw = tape_ccw_repeat(ccw, BACKSPACEखाता, mt_count);
	ccw = tape_ccw_end(ccw, NOP, 0, शून्य);
	/* execute it */
	rc = tape_करो_io_मुक्त(device, request);
	अगर (rc == 0) अणु
		rc = tape_mtop(device, MTFSR, 1);
		अगर (rc > 0)
			rc = 0;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * MTFSFM: Forward space over 'count' file marks.
 * The tape is positioned at the BOT (Begin Of Tape) side
 * of the last skipped file mark.
 */
पूर्णांक
tape_std_mtfsfm(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;
	काष्ठा ccw1 *ccw;
	पूर्णांक rc;

	request = tape_alloc_request(mt_count + 2, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_FSF;
	/* setup ccws */
	ccw = tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1,
			  device->modeset_byte);
	ccw = tape_ccw_repeat(ccw, FORSPACEखाता, mt_count);
	ccw = tape_ccw_end(ccw, NOP, 0, शून्य);
	/* execute it */
	rc = tape_करो_io_मुक्त(device, request);
	अगर (rc == 0) अणु
		rc = tape_mtop(device, MTBSR, 1);
		अगर (rc > 0)
			rc = 0;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * MTREW: Rewind the tape.
 */
पूर्णांक
tape_std_mtrew(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;

	request = tape_alloc_request(3, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_REW;
	/* setup ccws */
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1,
		    device->modeset_byte);
	tape_ccw_cc(request->cpaddr + 1, REWIND, 0, शून्य);
	tape_ccw_end(request->cpaddr + 2, NOP, 0, शून्य);

	/* execute it */
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

/*
 * MTOFFL: Rewind the tape and put the drive off-line.
 * Implement 'rewind unload'
 */
पूर्णांक
tape_std_mtoffl(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;

	request = tape_alloc_request(3, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_RUN;
	/* setup ccws */
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_cc(request->cpaddr + 1, REWIND_UNLOAD, 0, शून्य);
	tape_ccw_end(request->cpaddr + 2, NOP, 0, शून्य);

	/* execute it */
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

/*
 * MTNOP: 'No operation'.
 */
पूर्णांक
tape_std_mtnop(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;

	request = tape_alloc_request(2, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_NOP;
	/* setup ccws */
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_end(request->cpaddr + 1, NOP, 0, शून्य);
	/* execute it */
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

/*
 * MTEOM: positions at the end of the portion of the tape alपढ़ोy used
 * क्रम recordind data. MTEOM positions after the last file mark, पढ़ोy क्रम
 * appending another file.
 */
पूर्णांक
tape_std_mteom(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	पूर्णांक rc;

	/*
	 * Seek from the beginning of tape (शुरुआत).
	 */
	अगर ((rc = tape_mtop(device, MTREW, 1)) < 0)
		वापस rc;

	/*
	 * The logical end of volume is given by two sewuential tapemarks.
	 * Look क्रम this by skipping to the next file (over one tapemark)
	 * and then test क्रम another one (fsr वापसs 1 अगर a tapemark was
	 * encountered).
	 */
	करो अणु
		अगर ((rc = tape_mtop(device, MTFSF, 1)) < 0)
			वापस rc;
		अगर ((rc = tape_mtop(device, MTFSR, 1)) < 0)
			वापस rc;
	पूर्ण जबतक (rc == 0);

	वापस tape_mtop(device, MTBSR, 1);
पूर्ण

/*
 * MTRETEN: Retension the tape, i.e. क्रमward space to end of tape and शुरुआत.
 */
पूर्णांक
tape_std_mtreten(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;

	request = tape_alloc_request(4, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_FSF;
	/* setup ccws */
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_cc(request->cpaddr + 1,FORSPACEखाता, 0, शून्य);
	tape_ccw_cc(request->cpaddr + 2, NOP, 0, शून्य);
	tape_ccw_end(request->cpaddr + 3, CCW_CMD_TIC, 0, request->cpaddr);
	/* execute it, MTRETEN rc माला_लो ignored */
	tape_करो_io_पूर्णांकerruptible(device, request);
	tape_मुक्त_request(request);
	वापस tape_mtop(device, MTREW, 1);
पूर्ण

/*
 * MTERASE: erases the tape.
 */
पूर्णांक
tape_std_mterase(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;

	request = tape_alloc_request(6, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_DSE;
	/* setup ccws */
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_cc(request->cpaddr + 1, REWIND, 0, शून्य);
	tape_ccw_cc(request->cpaddr + 2, ERASE_GAP, 0, शून्य);
	tape_ccw_cc(request->cpaddr + 3, DATA_SEC_ERASE, 0, शून्य);
	tape_ccw_cc(request->cpaddr + 4, REWIND, 0, शून्य);
	tape_ccw_end(request->cpaddr + 5, NOP, 0, शून्य);

	/* execute it */
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

/*
 * MTUNLOAD: Rewind the tape and unload it.
 */
पूर्णांक
tape_std_mtunload(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	वापस tape_mtop(device, MTOFFL, mt_count);
पूर्ण

/*
 * MTCOMPRESSION: used to enable compression.
 * Sets the IDRC on/off.
 */
पूर्णांक
tape_std_mtcompression(काष्ठा tape_device *device, पूर्णांक mt_count)
अणु
	काष्ठा tape_request *request;

	अगर (mt_count < 0 || mt_count > 1) अणु
		DBF_EXCEPTION(6, "xcom parm\n");
		वापस -EINVAL;
	पूर्ण
	request = tape_alloc_request(2, 0);
	अगर (IS_ERR(request))
		वापस PTR_ERR(request);
	request->op = TO_NOP;
	/* setup ccws */
	अगर (mt_count == 0)
		*device->modeset_byte &= ~0x08;
	अन्यथा
		*device->modeset_byte |= 0x08;
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_end(request->cpaddr + 1, NOP, 0, शून्य);
	/* execute it */
	वापस tape_करो_io_मुक्त(device, request);
पूर्ण

/*
 * Read Block
 */
काष्ठा tape_request *
tape_std_पढ़ो_block(काष्ठा tape_device *device, माप_प्रकार count)
अणु
	काष्ठा tape_request *request;

	/*
	 * We have to alloc 4 ccws in order to be able to transक्रमm request
	 * पूर्णांकo a पढ़ो backward request in error हाल.
	 */
	request = tape_alloc_request(4, 0);
	अगर (IS_ERR(request)) अणु
		DBF_EXCEPTION(6, "xrbl fail");
		वापस request;
	पूर्ण
	request->op = TO_RFO;
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_end_idal(request->cpaddr + 1, READ_FORWARD,
			  device->अक्षर_data.idal_buf);
	DBF_EVENT(6, "xrbl ccwg\n");
	वापस request;
पूर्ण

/*
 * Read Block backward transक्रमmation function.
 */
व्योम
tape_std_पढ़ो_backward(काष्ठा tape_device *device, काष्ठा tape_request *request)
अणु
	/*
	 * We have allocated 4 ccws in tape_std_पढ़ो, so we can now
	 * transक्रमm the request to a पढ़ो backward, followed by a
	 * क्रमward space block.
	 */
	request->op = TO_RBA;
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_cc_idal(request->cpaddr + 1, READ_BACKWARD,
			 device->अक्षर_data.idal_buf);
	tape_ccw_cc(request->cpaddr + 2, FORSPACEBLOCK, 0, शून्य);
	tape_ccw_end(request->cpaddr + 3, NOP, 0, शून्य);
	DBF_EVENT(6, "xrop ccwg");पूर्ण

/*
 * Write Block
 */
काष्ठा tape_request *
tape_std_ग_लिखो_block(काष्ठा tape_device *device, माप_प्रकार count)
अणु
	काष्ठा tape_request *request;

	request = tape_alloc_request(2, 0);
	अगर (IS_ERR(request)) अणु
		DBF_EXCEPTION(6, "xwbl fail\n");
		वापस request;
	पूर्ण
	request->op = TO_WRI;
	tape_ccw_cc(request->cpaddr, MODE_SET_DB, 1, device->modeset_byte);
	tape_ccw_end_idal(request->cpaddr + 1, WRITE_CMD,
			  device->अक्षर_data.idal_buf);
	DBF_EVENT(6, "xwbl ccwg\n");
	वापस request;
पूर्ण

/*
 * This routine is called by frontend after an ENOSP on ग_लिखो
 */
व्योम
tape_std_process_eov(काष्ठा tape_device *device)
अणु
	/*
	 * End of volume: We have to backspace the last written record, then
	 * we TRY to ग_लिखो a tapemark and then backspace over the written TM
	 */
	अगर (tape_mtop(device, MTBSR, 1) == 0 &&
	    tape_mtop(device, MTWखातापूर्ण, 1) == 0) अणु
		tape_mtop(device, MTBSR, 1);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(tape_std_assign);
EXPORT_SYMBOL(tape_std_unassign);
EXPORT_SYMBOL(tape_std_display);
EXPORT_SYMBOL(tape_std_पढ़ो_block_id);
EXPORT_SYMBOL(tape_std_mtload);
EXPORT_SYMBOL(tape_std_mtsetblk);
EXPORT_SYMBOL(tape_std_mtreset);
EXPORT_SYMBOL(tape_std_mtfsf);
EXPORT_SYMBOL(tape_std_mtfsr);
EXPORT_SYMBOL(tape_std_mtbsr);
EXPORT_SYMBOL(tape_std_mtweof);
EXPORT_SYMBOL(tape_std_mtbsfm);
EXPORT_SYMBOL(tape_std_mtbsf);
EXPORT_SYMBOL(tape_std_mtfsfm);
EXPORT_SYMBOL(tape_std_mtrew);
EXPORT_SYMBOL(tape_std_mtoffl);
EXPORT_SYMBOL(tape_std_mtnop);
EXPORT_SYMBOL(tape_std_mteom);
EXPORT_SYMBOL(tape_std_mtreten);
EXPORT_SYMBOL(tape_std_mterase);
EXPORT_SYMBOL(tape_std_mtunload);
EXPORT_SYMBOL(tape_std_mtcompression);
EXPORT_SYMBOL(tape_std_पढ़ो_block);
EXPORT_SYMBOL(tape_std_पढ़ो_backward);
EXPORT_SYMBOL(tape_std_ग_लिखो_block);
EXPORT_SYMBOL(tape_std_process_eov);
