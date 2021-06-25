<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम USB Mass Storage compliant devices
 * Debugging Functions Source Code File
 *
 * Current development and मुख्यtenance by:
 *   (c) 1999-2002 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
 *
 * Developed with the assistance of:
 *   (c) 2002 Alan Stern <stern@rowland.org>
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

#समावेश <linux/device.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/export.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_dbg.h>

#समावेश "usb.h"
#समावेश "debug.h"
#समावेश "scsi.h"


व्योम usb_stor_show_command(स्थिर काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	अक्षर *what = शून्य;

	चयन (srb->cmnd[0]) अणु
	हाल TEST_UNIT_READY: what = "TEST_UNIT_READY"; अवरोध;
	हाल REZERO_UNIT: what = "REZERO_UNIT"; अवरोध;
	हाल REQUEST_SENSE: what = "REQUEST_SENSE"; अवरोध;
	हाल FORMAT_UNIT: what = "FORMAT_UNIT"; अवरोध;
	हाल READ_BLOCK_LIMITS: what = "READ_BLOCK_LIMITS"; अवरोध;
	हाल REASSIGN_BLOCKS: what = "REASSIGN_BLOCKS"; अवरोध;
	हाल READ_6: what = "READ_6"; अवरोध;
	हाल WRITE_6: what = "WRITE_6"; अवरोध;
	हाल SEEK_6: what = "SEEK_6"; अवरोध;
	हाल READ_REVERSE: what = "READ_REVERSE"; अवरोध;
	हाल WRITE_खाताMARKS: what = "WRITE_FILEMARKS"; अवरोध;
	हाल SPACE: what = "SPACE"; अवरोध;
	हाल INQUIRY: what = "INQUIRY"; अवरोध;
	हाल RECOVER_BUFFERED_DATA: what = "RECOVER_BUFFERED_DATA"; अवरोध;
	हाल MODE_SELECT: what = "MODE_SELECT"; अवरोध;
	हाल RESERVE: what = "RESERVE"; अवरोध;
	हाल RELEASE: what = "RELEASE"; अवरोध;
	हाल COPY: what = "COPY"; अवरोध;
	हाल ERASE: what = "ERASE"; अवरोध;
	हाल MODE_SENSE: what = "MODE_SENSE"; अवरोध;
	हाल START_STOP: what = "START_STOP"; अवरोध;
	हाल RECEIVE_DIAGNOSTIC: what = "RECEIVE_DIAGNOSTIC"; अवरोध;
	हाल SEND_DIAGNOSTIC: what = "SEND_DIAGNOSTIC"; अवरोध;
	हाल ALLOW_MEDIUM_REMOVAL: what = "ALLOW_MEDIUM_REMOVAL"; अवरोध;
	हाल SET_WINDOW: what = "SET_WINDOW"; अवरोध;
	हाल READ_CAPACITY: what = "READ_CAPACITY"; अवरोध;
	हाल READ_10: what = "READ_10"; अवरोध;
	हाल WRITE_10: what = "WRITE_10"; अवरोध;
	हाल SEEK_10: what = "SEEK_10"; अवरोध;
	हाल WRITE_VERIFY: what = "WRITE_VERIFY"; अवरोध;
	हाल VERIFY: what = "VERIFY"; अवरोध;
	हाल SEARCH_HIGH: what = "SEARCH_HIGH"; अवरोध;
	हाल SEARCH_EQUAL: what = "SEARCH_EQUAL"; अवरोध;
	हाल SEARCH_LOW: what = "SEARCH_LOW"; अवरोध;
	हाल SET_LIMITS: what = "SET_LIMITS"; अवरोध;
	हाल READ_POSITION: what = "READ_POSITION"; अवरोध;
	हाल SYNCHRONIZE_CACHE: what = "SYNCHRONIZE_CACHE"; अवरोध;
	हाल LOCK_UNLOCK_CACHE: what = "LOCK_UNLOCK_CACHE"; अवरोध;
	हाल READ_DEFECT_DATA: what = "READ_DEFECT_DATA"; अवरोध;
	हाल MEDIUM_SCAN: what = "MEDIUM_SCAN"; अवरोध;
	हाल COMPARE: what = "COMPARE"; अवरोध;
	हाल COPY_VERIFY: what = "COPY_VERIFY"; अवरोध;
	हाल WRITE_BUFFER: what = "WRITE_BUFFER"; अवरोध;
	हाल READ_BUFFER: what = "READ_BUFFER"; अवरोध;
	हाल UPDATE_BLOCK: what = "UPDATE_BLOCK"; अवरोध;
	हाल READ_LONG: what = "READ_LONG"; अवरोध;
	हाल WRITE_LONG: what = "WRITE_LONG"; अवरोध;
	हाल CHANGE_DEFINITION: what = "CHANGE_DEFINITION"; अवरोध;
	हाल WRITE_SAME: what = "WRITE_SAME"; अवरोध;
	हाल GPCMD_READ_SUBCHANNEL: what = "READ SUBCHANNEL"; अवरोध;
	हाल READ_TOC: what = "READ_TOC"; अवरोध;
	हाल GPCMD_READ_HEADER: what = "READ HEADER"; अवरोध;
	हाल GPCMD_PLAY_AUDIO_10: what = "PLAY AUDIO (10)"; अवरोध;
	हाल GPCMD_PLAY_AUDIO_MSF: what = "PLAY AUDIO MSF"; अवरोध;
	हाल GPCMD_GET_EVENT_STATUS_NOTIFICATION:
		what = "GET EVENT/STATUS NOTIFICATION"; अवरोध;
	हाल GPCMD_PAUSE_RESUME: what = "PAUSE/RESUME"; अवरोध;
	हाल LOG_SELECT: what = "LOG_SELECT"; अवरोध;
	हाल LOG_SENSE: what = "LOG_SENSE"; अवरोध;
	हाल GPCMD_STOP_PLAY_SCAN: what = "STOP PLAY/SCAN"; अवरोध;
	हाल GPCMD_READ_DISC_INFO: what = "READ DISC INFORMATION"; अवरोध;
	हाल GPCMD_READ_TRACK_RZONE_INFO:
		what = "READ TRACK INFORMATION"; अवरोध;
	हाल GPCMD_RESERVE_RZONE_TRACK: what = "RESERVE TRACK"; अवरोध;
	हाल GPCMD_SEND_OPC: what = "SEND OPC"; अवरोध;
	हाल MODE_SELECT_10: what = "MODE_SELECT_10"; अवरोध;
	हाल GPCMD_REPAIR_RZONE_TRACK: what = "REPAIR TRACK"; अवरोध;
	हाल 0x59: what = "READ MASTER CUE"; अवरोध;
	हाल MODE_SENSE_10: what = "MODE_SENSE_10"; अवरोध;
	हाल GPCMD_CLOSE_TRACK: what = "CLOSE TRACK/SESSION"; अवरोध;
	हाल 0x5C: what = "READ BUFFER CAPACITY"; अवरोध;
	हाल 0x5D: what = "SEND CUE SHEET"; अवरोध;
	हाल GPCMD_BLANK: what = "BLANK"; अवरोध;
	हाल REPORT_LUNS: what = "REPORT LUNS"; अवरोध;
	हाल MOVE_MEDIUM: what = "MOVE_MEDIUM or PLAY AUDIO (12)"; अवरोध;
	हाल READ_12: what = "READ_12"; अवरोध;
	हाल WRITE_12: what = "WRITE_12"; अवरोध;
	हाल WRITE_VERIFY_12: what = "WRITE_VERIFY_12"; अवरोध;
	हाल SEARCH_HIGH_12: what = "SEARCH_HIGH_12"; अवरोध;
	हाल SEARCH_EQUAL_12: what = "SEARCH_EQUAL_12"; अवरोध;
	हाल SEARCH_LOW_12: what = "SEARCH_LOW_12"; अवरोध;
	हाल SEND_VOLUME_TAG: what = "SEND_VOLUME_TAG"; अवरोध;
	हाल READ_ELEMENT_STATUS: what = "READ_ELEMENT_STATUS"; अवरोध;
	हाल GPCMD_READ_CD_MSF: what = "READ CD MSF"; अवरोध;
	हाल GPCMD_SCAN: what = "SCAN"; अवरोध;
	हाल GPCMD_SET_SPEED: what = "SET CD SPEED"; अवरोध;
	हाल GPCMD_MECHANISM_STATUS: what = "MECHANISM STATUS"; अवरोध;
	हाल GPCMD_READ_CD: what = "READ CD"; अवरोध;
	हाल 0xE1: what = "WRITE CONTINUE"; अवरोध;
	हाल WRITE_LONG_2: what = "WRITE_LONG_2"; अवरोध;
	शेष: what = "(unknown command)"; अवरोध;
	पूर्ण
	usb_stor_dbg(us, "Command %s (%d bytes)\n", what, srb->cmd_len);
	usb_stor_dbg(us, "bytes: %*ph\n", min_t(पूर्णांक, srb->cmd_len, 16),
		     (स्थिर अचिन्हित अक्षर *)srb->cmnd);
पूर्ण

व्योम usb_stor_show_sense(स्थिर काष्ठा us_data *us,
			 अचिन्हित अक्षर key,
			 अचिन्हित अक्षर asc,
			 अचिन्हित अक्षर ascq)
अणु
	स्थिर अक्षर *what, *keystr, *fmt;

	keystr = scsi_sense_key_string(key);
	what = scsi_extd_sense_क्रमmat(asc, ascq, &fmt);

	अगर (keystr == शून्य)
		keystr = "(Unknown Key)";
	अगर (what == शून्य)
		what = "(unknown ASC/ASCQ)";

	अगर (fmt)
		usb_stor_dbg(us, "%s: %s (%s%x)\n", keystr, what, fmt, ascq);
	अन्यथा
		usb_stor_dbg(us, "%s: %s\n", keystr, what);
पूर्ण

व्योम usb_stor_dbg(स्थिर काष्ठा us_data *us, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	dev_vprपूर्णांकk_emit(LOGLEVEL_DEBUG, &us->pusb_dev->dev, fmt, args);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_dbg);
