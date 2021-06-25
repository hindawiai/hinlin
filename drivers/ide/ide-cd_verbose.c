<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Verbose error logging क्रम ATAPI CD/DVD devices.
 *
 * Copyright (C) 1994-1996  Scott Snyder <snyder@fnald0.fnal.gov>
 * Copyright (C) 1996-1998  Erik Andersen <andersee@debian.org>
 * Copyright (C) 1998-2000  Jens Axboe <axboe@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/ide.h>
#समावेश <scsi/scsi.h>
#समावेश "ide-cd.h"

#अगर_अघोषित CONFIG_BLK_DEV_IDECD_VERBOSE_ERRORS
व्योम ide_cd_log_error(स्थिर अक्षर *name, काष्ठा request *failed_command,
		      काष्ठा request_sense *sense)
अणु
	/* Suppress prपूर्णांकing unit attention and `in progress of becoming पढ़ोy'
	   errors when we're not being verbose. */
	अगर (sense->sense_key == UNIT_ATTENTION ||
	    (sense->sense_key == NOT_READY && (sense->asc == 4 ||
						sense->asc == 0x3a)))
		वापस;

	prपूर्णांकk(KERN_ERR "%s: error code: 0x%02x  sense_key: 0x%02x  "
			"asc: 0x%02x  ascq: 0x%02x\n",
			name, sense->error_code, sense->sense_key,
			sense->asc, sense->ascq);
पूर्ण
#अन्यथा
/* The generic packet command opcodes क्रम CD/DVD Logical Units,
 * From Table 57 of the SFF8090 Ver. 3 (Mt. Fuji) draft standard. */
अटल स्थिर काष्ठा अणु
	अचिन्हित लघु packet_command;
	स्थिर अक्षर * स्थिर text;
पूर्ण packet_command_texts[] = अणु
	अणु GPCMD_TEST_UNIT_READY, "Test Unit Ready" पूर्ण,
	अणु GPCMD_REQUEST_SENSE, "Request Sense" पूर्ण,
	अणु GPCMD_FORMAT_UNIT, "Format Unit" पूर्ण,
	अणु GPCMD_INQUIRY, "Inquiry" पूर्ण,
	अणु GPCMD_START_STOP_UNIT, "Start/Stop Unit" पूर्ण,
	अणु GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL, "Prevent/Allow Medium Removal" पूर्ण,
	अणु GPCMD_READ_FORMAT_CAPACITIES, "Read Format Capacities" पूर्ण,
	अणु GPCMD_READ_CDVD_CAPACITY, "Read Cd/Dvd Capacity" पूर्ण,
	अणु GPCMD_READ_10, "Read 10" पूर्ण,
	अणु GPCMD_WRITE_10, "Write 10" पूर्ण,
	अणु GPCMD_SEEK, "Seek" पूर्ण,
	अणु GPCMD_WRITE_AND_VERIFY_10, "Write and Verify 10" पूर्ण,
	अणु GPCMD_VERIFY_10, "Verify 10" पूर्ण,
	अणु GPCMD_FLUSH_CACHE, "Flush Cache" पूर्ण,
	अणु GPCMD_READ_SUBCHANNEL, "Read Subchannel" पूर्ण,
	अणु GPCMD_READ_TOC_PMA_ATIP, "Read Table of Contents" पूर्ण,
	अणु GPCMD_READ_HEADER, "Read Header" पूर्ण,
	अणु GPCMD_PLAY_AUDIO_10, "Play Audio 10" पूर्ण,
	अणु GPCMD_GET_CONFIGURATION, "Get Configuration" पूर्ण,
	अणु GPCMD_PLAY_AUDIO_MSF, "Play Audio MSF" पूर्ण,
	अणु GPCMD_PLAYAUDIO_TI, "Play Audio TrackIndex" पूर्ण,
	अणु GPCMD_GET_EVENT_STATUS_NOTIFICATION,
		"Get Event Status Notification" पूर्ण,
	अणु GPCMD_PAUSE_RESUME, "Pause/Resume" पूर्ण,
	अणु GPCMD_STOP_PLAY_SCAN, "Stop Play/Scan" पूर्ण,
	अणु GPCMD_READ_DISC_INFO, "Read Disc Info" पूर्ण,
	अणु GPCMD_READ_TRACK_RZONE_INFO, "Read Track Rzone Info" पूर्ण,
	अणु GPCMD_RESERVE_RZONE_TRACK, "Reserve Rzone Track" पूर्ण,
	अणु GPCMD_SEND_OPC, "Send OPC" पूर्ण,
	अणु GPCMD_MODE_SELECT_10, "Mode Select 10" पूर्ण,
	अणु GPCMD_REPAIR_RZONE_TRACK, "Repair Rzone Track" पूर्ण,
	अणु GPCMD_MODE_SENSE_10, "Mode Sense 10" पूर्ण,
	अणु GPCMD_CLOSE_TRACK, "Close Track" पूर्ण,
	अणु GPCMD_BLANK, "Blank" पूर्ण,
	अणु GPCMD_SEND_EVENT, "Send Event" पूर्ण,
	अणु GPCMD_SEND_KEY, "Send Key" पूर्ण,
	अणु GPCMD_REPORT_KEY, "Report Key" पूर्ण,
	अणु GPCMD_LOAD_UNLOAD, "Load/Unload" पूर्ण,
	अणु GPCMD_SET_READ_AHEAD, "Set Read-ahead" पूर्ण,
	अणु GPCMD_READ_12, "Read 12" पूर्ण,
	अणु GPCMD_GET_PERFORMANCE, "Get Performance" पूर्ण,
	अणु GPCMD_SEND_DVD_STRUCTURE, "Send DVD Structure" पूर्ण,
	अणु GPCMD_READ_DVD_STRUCTURE, "Read DVD Structure" पूर्ण,
	अणु GPCMD_SET_STREAMING, "Set Streaming" पूर्ण,
	अणु GPCMD_READ_CD_MSF, "Read CD MSF" पूर्ण,
	अणु GPCMD_SCAN, "Scan" पूर्ण,
	अणु GPCMD_SET_SPEED, "Set Speed" पूर्ण,
	अणु GPCMD_PLAY_CD, "Play CD" पूर्ण,
	अणु GPCMD_MECHANISM_STATUS, "Mechanism Status" पूर्ण,
	अणु GPCMD_READ_CD, "Read CD" पूर्ण,
पूर्ण;

/* From Table 303 of the SFF8090 Ver. 3 (Mt. Fuji) draft standard. */
अटल स्थिर अक्षर * स्थिर sense_key_texts[16] = अणु
	"No sense data",
	"Recovered error",
	"Not ready",
	"Medium error",
	"Hardware error",
	"Illegal request",
	"Unit attention",
	"Data protect",
	"Blank check",
	"(reserved)",
	"(reserved)",
	"Aborted command",
	"(reserved)",
	"(reserved)",
	"Miscompare",
	"(reserved)",
पूर्ण;

/* From Table 304 of the SFF8090 Ver. 3 (Mt. Fuji) draft standard. */
अटल स्थिर काष्ठा अणु
	अचिन्हित दीर्घ asc_ascq;
	स्थिर अक्षर * स्थिर text;
पूर्ण sense_data_texts[] = अणु
	अणु 0x000000, "No additional sense information" पूर्ण,
	अणु 0x000011, "Play operation in progress" पूर्ण,
	अणु 0x000012, "Play operation paused" पूर्ण,
	अणु 0x000013, "Play operation successfully completed" पूर्ण,
	अणु 0x000014, "Play operation stopped due to error" पूर्ण,
	अणु 0x000015, "No current audio status to return" पूर्ण,
	अणु 0x010c0a, "Write error - padding blocks added" पूर्ण,
	अणु 0x011700, "Recovered data with no error correction applied" पूर्ण,
	अणु 0x011701, "Recovered data with retries" पूर्ण,
	अणु 0x011702, "Recovered data with positive head offset" पूर्ण,
	अणु 0x011703, "Recovered data with negative head offset" पूर्ण,
	अणु 0x011704, "Recovered data with retries and/or CIRC applied" पूर्ण,
	अणु 0x011705, "Recovered data using previous sector ID" पूर्ण,
	अणु 0x011800, "Recovered data with error correction applied" पूर्ण,
	अणु 0x011801, "Recovered data with error correction and retries applied"पूर्ण,
	अणु 0x011802, "Recovered data - the data was auto-reallocated" पूर्ण,
	अणु 0x011803, "Recovered data with CIRC" पूर्ण,
	अणु 0x011804, "Recovered data with L-EC" पूर्ण,
	अणु 0x015d00, "Failure prediction threshold exceeded"
		    " - Predicted logical unit failure" पूर्ण,
	अणु 0x015d01, "Failure prediction threshold exceeded"
		    " - Predicted media failure" पूर्ण,
	अणु 0x015dff, "Failure prediction threshold exceeded - False" पूर्ण,
	अणु 0x017301, "Power calibration area almost full" पूर्ण,
	अणु 0x020400, "Logical unit not ready - cause not reportable" पूर्ण,
	/* Following is misspelled in ATAPI 2.6, _and_ in Mt. Fuji */
	अणु 0x020401, "Logical unit not ready"
		    " - in progress [sic] of becoming ready" पूर्ण,
	अणु 0x020402, "Logical unit not ready - initializing command required" पूर्ण,
	अणु 0x020403, "Logical unit not ready - manual intervention required" पूर्ण,
	अणु 0x020404, "Logical unit not ready - format in progress" पूर्ण,
	अणु 0x020407, "Logical unit not ready - operation in progress" पूर्ण,
	अणु 0x020408, "Logical unit not ready - long write in progress" पूर्ण,
	अणु 0x020600, "No reference position found (media may be upside down)" पूर्ण,
	अणु 0x023000, "Incompatible medium installed" पूर्ण,
	अणु 0x023a00, "Medium not present" पूर्ण,
	अणु 0x025300, "Media load or eject failed" पूर्ण,
	अणु 0x025700, "Unable to recover table of contents" पूर्ण,
	अणु 0x030300, "Peripheral device write fault" पूर्ण,
	अणु 0x030301, "No write current" पूर्ण,
	अणु 0x030302, "Excessive write errors" पूर्ण,
	अणु 0x030c00, "Write error" पूर्ण,
	अणु 0x030c01, "Write error - Recovered with auto reallocation" पूर्ण,
	अणु 0x030c02, "Write error - auto reallocation failed" पूर्ण,
	अणु 0x030c03, "Write error - recommend reassignment" पूर्ण,
	अणु 0x030c04, "Compression check miscompare error" पूर्ण,
	अणु 0x030c05, "Data expansion occurred during compress" पूर्ण,
	अणु 0x030c06, "Block not compressible" पूर्ण,
	अणु 0x030c07, "Write error - recovery needed" पूर्ण,
	अणु 0x030c08, "Write error - recovery failed" पूर्ण,
	अणु 0x030c09, "Write error - loss of streaming" पूर्ण,
	अणु 0x031100, "Unrecovered read error" पूर्ण,
	अणु 0x031106, "CIRC unrecovered error" पूर्ण,
	अणु 0x033101, "Format command failed" पूर्ण,
	अणु 0x033200, "No defect spare location available" पूर्ण,
	अणु 0x033201, "Defect list update failure" पूर्ण,
	अणु 0x035100, "Erase failure" पूर्ण,
	अणु 0x037200, "Session fixation error" पूर्ण,
	अणु 0x037201, "Session fixation error writin lead-in" पूर्ण,
	अणु 0x037202, "Session fixation error writin lead-out" पूर्ण,
	अणु 0x037300, "CD control error" पूर्ण,
	अणु 0x037302, "Power calibration area is full" पूर्ण,
	अणु 0x037303, "Power calibration area error" पूर्ण,
	अणु 0x037304, "Program memory area / RMA update failure" पूर्ण,
	अणु 0x037305, "Program memory area / RMA is full" पूर्ण,
	अणु 0x037306, "Program memory area / RMA is (almost) full" पूर्ण,
	अणु 0x040200, "No seek complete" पूर्ण,
	अणु 0x040300, "Write fault" पूर्ण,
	अणु 0x040900, "Track following error" पूर्ण,
	अणु 0x040901, "Tracking servo failure" पूर्ण,
	अणु 0x040902, "Focus servo failure" पूर्ण,
	अणु 0x040903, "Spindle servo failure" पूर्ण,
	अणु 0x041500, "Random positioning error" पूर्ण,
	अणु 0x041501, "Mechanical positioning or changer error" पूर्ण,
	अणु 0x041502, "Positioning error detected by read of medium" पूर्ण,
	अणु 0x043c00, "Mechanical positioning or changer error" पूर्ण,
	अणु 0x044000, "Diagnostic failure on component (ASCQ)" पूर्ण,
	अणु 0x044400, "Internal CD/DVD logical unit failure" पूर्ण,
	अणु 0x04b600, "Media load mechanism failed" पूर्ण,
	अणु 0x051a00, "Parameter list length error" पूर्ण,
	अणु 0x052000, "Invalid command operation code" पूर्ण,
	अणु 0x052100, "Logical block address out of range" पूर्ण,
	अणु 0x052102, "Invalid address for write" पूर्ण,
	अणु 0x052400, "Invalid field in command packet" पूर्ण,
	अणु 0x052600, "Invalid field in parameter list" पूर्ण,
	अणु 0x052601, "Parameter not supported" पूर्ण,
	अणु 0x052602, "Parameter value invalid" पूर्ण,
	अणु 0x052700, "Write protected media" पूर्ण,
	अणु 0x052c00, "Command sequence error" पूर्ण,
	अणु 0x052c03, "Current program area is not empty" पूर्ण,
	अणु 0x052c04, "Current program area is empty" पूर्ण,
	अणु 0x053001, "Cannot read medium - unknown format" पूर्ण,
	अणु 0x053002, "Cannot read medium - incompatible format" पूर्ण,
	अणु 0x053900, "Saving parameters not supported" पूर्ण,
	अणु 0x054e00, "Overlapped commands attempted" पूर्ण,
	अणु 0x055302, "Medium removal prevented" पूर्ण,
	अणु 0x055500, "System resource failure" पूर्ण,
	अणु 0x056300, "End of user area encountered on this track" पूर्ण,
	अणु 0x056400, "Illegal mode for this track or incompatible medium" पूर्ण,
	अणु 0x056f00, "Copy protection key exchange failure"
		    " - Authentication failure" पूर्ण,
	अणु 0x056f01, "Copy protection key exchange failure - Key not present" पूर्ण,
	अणु 0x056f02, "Copy protection key exchange failure"
		     " - Key not established" पूर्ण,
	अणु 0x056f03, "Read of scrambled sector without authentication" पूर्ण,
	अणु 0x056f04, "Media region code is mismatched to logical unit" पूर्ण,
	अणु 0x056f05, "Drive region must be permanent"
		    " / region reset count error" पूर्ण,
	अणु 0x057203, "Session fixation error - incomplete track in session" पूर्ण,
	अणु 0x057204, "Empty or partially written reserved track" पूर्ण,
	अणु 0x057205, "No more RZONE reservations are allowed" पूर्ण,
	अणु 0x05bf00, "Loss of streaming" पूर्ण,
	अणु 0x062800, "Not ready to ready transition, medium may have changed" पूर्ण,
	अणु 0x062900, "Power on, reset or hardware reset occurred" पूर्ण,
	अणु 0x062a00, "Parameters changed" पूर्ण,
	अणु 0x062a01, "Mode parameters changed" पूर्ण,
	अणु 0x062e00, "Insufficient time for operation" पूर्ण,
	अणु 0x063f00, "Logical unit operating conditions have changed" पूर्ण,
	अणु 0x063f01, "Microcode has been changed" पूर्ण,
	अणु 0x065a00, "Operator request or state change input (unspecified)" पूर्ण,
	अणु 0x065a01, "Operator medium removal request" पूर्ण,
	अणु 0x0bb900, "Play operation aborted" पूर्ण,
	/* Here we use 0xff क्रम the key (not a valid key) to signअगरy
	 * that these can have _any_ key value associated with them... */
	अणु 0xff0401, "Logical unit is in process of becoming ready" पूर्ण,
	अणु 0xff0400, "Logical unit not ready, cause not reportable" पूर्ण,
	अणु 0xff0402, "Logical unit not ready, initializing command required" पूर्ण,
	अणु 0xff0403, "Logical unit not ready, manual intervention required" पूर्ण,
	अणु 0xff0500, "Logical unit does not respond to selection" पूर्ण,
	अणु 0xff0800, "Logical unit communication failure" पूर्ण,
	अणु 0xff0802, "Logical unit communication parity error" पूर्ण,
	अणु 0xff0801, "Logical unit communication time-out" पूर्ण,
	अणु 0xff2500, "Logical unit not supported" पूर्ण,
	अणु 0xff4c00, "Logical unit failed self-configuration" पूर्ण,
	अणु 0xff3e00, "Logical unit has not self-configured yet" पूर्ण,
पूर्ण;

व्योम ide_cd_log_error(स्थिर अक्षर *name, काष्ठा request *failed_command,
		      काष्ठा request_sense *sense)
अणु
	पूर्णांक i;
	स्थिर अक्षर *s = "bad sense key!";
	अक्षर buf[80];

	prपूर्णांकk(KERN_ERR "ATAPI device %s:\n", name);
	अगर (sense->error_code == 0x70)
		prपूर्णांकk(KERN_CONT "  Error: ");
	अन्यथा अगर (sense->error_code == 0x71)
		prपूर्णांकk("  Deferred Error: ");
	अन्यथा अगर (sense->error_code == 0x7f)
		prपूर्णांकk(KERN_CONT "  Vendor-specific Error: ");
	अन्यथा
		prपूर्णांकk(KERN_CONT "  Unknown Error Type: ");

	अगर (sense->sense_key < ARRAY_SIZE(sense_key_texts))
		s = sense_key_texts[sense->sense_key];

	prपूर्णांकk(KERN_CONT "%s -- (Sense key=0x%02x)\n", s, sense->sense_key);

	अगर (sense->asc == 0x40) अणु
		प्र_लिखो(buf, "Diagnostic failure on component 0x%02x",
			sense->ascq);
		s = buf;
	पूर्ण अन्यथा अणु
		पूर्णांक lo = 0, mid, hi = ARRAY_SIZE(sense_data_texts);
		अचिन्हित दीर्घ key = (sense->sense_key << 16);

		key |= (sense->asc << 8);
		अगर (!(sense->ascq >= 0x80 && sense->ascq <= 0xdd))
			key |= sense->ascq;
		s = शून्य;

		जबतक (hi > lo) अणु
			mid = (lo + hi) / 2;
			अगर (sense_data_texts[mid].asc_ascq == key ||
			    sense_data_texts[mid].asc_ascq == (0xff0000|key)) अणु
				s = sense_data_texts[mid].text;
				अवरोध;
			पूर्ण अन्यथा अगर (sense_data_texts[mid].asc_ascq > key)
				hi = mid;
			अन्यथा
				lo = mid + 1;
		पूर्ण
	पूर्ण

	अगर (s == शून्य) अणु
		अगर (sense->asc > 0x80)
			s = "(vendor-specific error)";
		अन्यथा
			s = "(reserved error code)";
	पूर्ण

	prपूर्णांकk(KERN_ERR "  %s -- (asc=0x%02x, ascq=0x%02x)\n",
			s, sense->asc, sense->ascq);

	अगर (failed_command != शून्य) अणु
		पूर्णांक lo = 0, mid, hi = ARRAY_SIZE(packet_command_texts);
		s = शून्य;

		जबतक (hi > lo) अणु
			mid = (lo + hi) / 2;
			अगर (packet_command_texts[mid].packet_command ==
			    scsi_req(failed_command)->cmd[0]) अणु
				s = packet_command_texts[mid].text;
				अवरोध;
			पूर्ण
			अगर (packet_command_texts[mid].packet_command >
			    scsi_req(failed_command)->cmd[0])
				hi = mid;
			अन्यथा
				lo = mid + 1;
		पूर्ण

		prपूर्णांकk(KERN_ERR "  The failed \"%s\" packet command "
				"was: \n  \"", s);
		क्रम (i = 0; i < BLK_MAX_CDB; i++)
			prपूर्णांकk(KERN_CONT "%02x ", scsi_req(failed_command)->cmd[i]);
		prपूर्णांकk(KERN_CONT "\"\n");
	पूर्ण

	/* The SKSV bit specअगरies validity of the sense_key_specअगरic
	 * in the next two commands. It is bit 7 of the first byte.
	 * In the हाल of NOT_READY, अगर SKSV is set the drive can
	 * give us nice ETA पढ़ोings.
	 */
	अगर (sense->sense_key == NOT_READY && (sense->sks[0] & 0x80)) अणु
		पूर्णांक progress = (sense->sks[1] << 8 | sense->sks[2]) * 100;

		prपूर्णांकk(KERN_ERR "  Command is %02d%% complete\n",
				progress / 0xffff);
	पूर्ण

	अगर (sense->sense_key == ILLEGAL_REQUEST &&
	    (sense->sks[0] & 0x80) != 0) अणु
		prपूर्णांकk(KERN_ERR "  Error in %s byte %d",
				(sense->sks[0] & 0x40) != 0 ?
				"command packet" : "command data",
				(sense->sks[1] << 8) + sense->sks[2]);

		अगर ((sense->sks[0] & 0x40) != 0)
			prपूर्णांकk(KERN_CONT " bit %d", sense->sks[0] & 0x07);

		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण
पूर्ण
#पूर्ण_अगर
