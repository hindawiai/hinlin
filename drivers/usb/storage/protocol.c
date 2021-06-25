<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम USB Mass Storage compliant devices
 *
 * Current development and मुख्यtenance by:
 *   (c) 1999-2002 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
 *
 * Developed with the assistance of:
 *   (c) 2000 David L. Brown, Jr. (usb-storage@davidb.org)
 *   (c) 2002 Alan Stern (stern@rowland.org)
 *
 * Initial work by:
 *   (c) 1999 Michael Gee (michael@linuxspecअगरic.com)
 *
 * This driver is based on the 'USB Mass Storage Class' करोcument. This
 * describes in detail the protocol used to communicate with such
 * devices.  Clearly, the designers had SCSI and ATAPI commands in
 * mind when they created this करोcument.  The commands are all very
 * similar to commands in the SCSI-II and ATAPI specअगरications.
 *
 * It is important to note that in a number of हालs this class
 * exhibits class-specअगरic exemptions from the USB specअगरication.
 * Notably the usage of NAK, STALL and ACK dअगरfers from the norm, in
 * that they are used to communicate रुको, failed and OK on commands.
 *
 * Also, क्रम certain devices, the पूर्णांकerrupt endpoपूर्णांक is used to convey
 * status of a command.
 */

#समावेश <linux/highस्मृति.स>
#समावेश <linux/export.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश "usb.h"
#समावेश "protocol.h"
#समावेश "debug.h"
#समावेश "scsiglue.h"
#समावेश "transport.h"

/***********************************************************************
 * Protocol routines
 ***********************************************************************/

व्योम usb_stor_pad12_command(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	/*
	 * Pad the SCSI command with zeros out to 12 bytes.  If the
	 * command alपढ़ोy is 12 bytes or दीर्घer, leave it alone.
	 *
	 * NOTE: This only works because a scsi_cmnd काष्ठा field contains
	 * a अचिन्हित अक्षर cmnd[16], so we know we have storage available
	 */
	क्रम (; srb->cmd_len < 12; srb->cmd_len++)
		srb->cmnd[srb->cmd_len] = 0;

	/* send the command to the transport layer */
	usb_stor_invoke_transport(srb, us);
पूर्ण

व्योम usb_stor_ufi_command(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	/*
	 * fix some commands -- this is a क्रमm of mode translation
	 * UFI devices only accept 12 byte दीर्घ commands
	 *
	 * NOTE: This only works because a scsi_cmnd काष्ठा field contains
	 * a अचिन्हित अक्षर cmnd[16], so we know we have storage available
	 */

	/* Pad the ATAPI command with zeros */
	क्रम (; srb->cmd_len < 12; srb->cmd_len++)
		srb->cmnd[srb->cmd_len] = 0;

	/* set command length to 12 bytes (this affects the transport layer) */
	srb->cmd_len = 12;

	/* XXX We should be स्थिरantly re-evaluating the need क्रम these */

	/* determine the correct data length क्रम these commands */
	चयन (srb->cmnd[0]) अणु

		/* क्रम INQUIRY, UFI devices only ever वापस 36 bytes */
	हाल INQUIRY:
		srb->cmnd[4] = 36;
		अवरोध;

		/* again, क्रम MODE_SENSE_10, we get the minimum (8) */
	हाल MODE_SENSE_10:
		srb->cmnd[7] = 0;
		srb->cmnd[8] = 8;
		अवरोध;

		/* क्रम REQUEST_SENSE, UFI devices only ever वापस 18 bytes */
	हाल REQUEST_SENSE:
		srb->cmnd[4] = 18;
		अवरोध;
	पूर्ण /* end चयन on cmnd[0] */

	/* send the command to the transport layer */
	usb_stor_invoke_transport(srb, us);
पूर्ण

व्योम usb_stor_transparent_scsi_command(काष्ठा scsi_cmnd *srb,
				       काष्ठा us_data *us)
अणु
	/* send the command to the transport layer */
	usb_stor_invoke_transport(srb, us);
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_transparent_scsi_command);

/***********************************************************************
 * Scatter-gather transfer buffer access routines
 ***********************************************************************/

/*
 * Copy a buffer of length buflen to/from the srb's transfer buffer.
 * Update the **sgptr and *offset variables so that the next copy will
 * pick up from where this one left off.
 */
अचिन्हित पूर्णांक usb_stor_access_xfer_buf(अचिन्हित अक्षर *buffer,
	अचिन्हित पूर्णांक buflen, काष्ठा scsi_cmnd *srb, काष्ठा scatterlist **sgptr,
	अचिन्हित पूर्णांक *offset, क्रमागत xfer_buf_dir dir)
अणु
	अचिन्हित पूर्णांक cnt = 0;
	काष्ठा scatterlist *sg = *sgptr;
	काष्ठा sg_mapping_iter miter;
	अचिन्हित पूर्णांक nents = scsi_sg_count(srb);

	अगर (sg)
		nents = sg_nents(sg);
	अन्यथा
		sg = scsi_sglist(srb);

	sg_miter_start(&miter, sg, nents, dir == FROM_XFER_BUF ?
		SG_MITER_FROM_SG: SG_MITER_TO_SG);

	अगर (!sg_miter_skip(&miter, *offset))
		वापस cnt;

	जबतक (sg_miter_next(&miter) && cnt < buflen) अणु
		अचिन्हित पूर्णांक len = min_t(अचिन्हित पूर्णांक, miter.length,
				buflen - cnt);

		अगर (dir == FROM_XFER_BUF)
			स_नकल(buffer + cnt, miter.addr, len);
		अन्यथा
			स_नकल(miter.addr, buffer + cnt, len);

		अगर (*offset + len < miter.piter.sg->length) अणु
			*offset += len;
			*sgptr = miter.piter.sg;
		पूर्ण अन्यथा अणु
			*offset = 0;
			*sgptr = sg_next(miter.piter.sg);
		पूर्ण
		cnt += len;
	पूर्ण
	sg_miter_stop(&miter);

	वापस cnt;
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_access_xfer_buf);

/*
 * Store the contents of buffer पूर्णांकo srb's transfer buffer and set the
 * SCSI residue.
 */
व्योम usb_stor_set_xfer_buf(अचिन्हित अक्षर *buffer,
	अचिन्हित पूर्णांक buflen, काष्ठा scsi_cmnd *srb)
अणु
	अचिन्हित पूर्णांक offset = 0;
	काष्ठा scatterlist *sg = शून्य;

	buflen = min(buflen, scsi_bufflen(srb));
	buflen = usb_stor_access_xfer_buf(buffer, buflen, srb, &sg, &offset,
			TO_XFER_BUF);
	अगर (buflen < scsi_bufflen(srb))
		scsi_set_resid(srb, scsi_bufflen(srb) - buflen);
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_set_xfer_buf);
