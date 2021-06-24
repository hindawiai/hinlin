<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "rtsx.h"
#समावेश "sd.h"
#समावेश "ms.h"
#समावेश "spi.h"

व्योम scsi_show_command(काष्ठा rtsx_chip *chip)
अणु
	काष्ठा scsi_cmnd *srb = chip->srb;
	अक्षर *what = शून्य;
	bool unknown_cmd = false;
	पूर्णांक len;

	चयन (srb->cmnd[0]) अणु
	हाल TEST_UNIT_READY:
		what = "TEST_UNIT_READY";
		अवरोध;
	हाल REZERO_UNIT:
		what = "REZERO_UNIT";
		अवरोध;
	हाल REQUEST_SENSE:
		what = "REQUEST_SENSE";
		अवरोध;
	हाल FORMAT_UNIT:
		what = "FORMAT_UNIT";
		अवरोध;
	हाल READ_BLOCK_LIMITS:
		what = "READ_BLOCK_LIMITS";
		अवरोध;
	हाल REASSIGN_BLOCKS:
		what = "REASSIGN_BLOCKS";
		अवरोध;
	हाल READ_6:
		what = "READ_6";
		अवरोध;
	हाल WRITE_6:
		what = "WRITE_6";
		अवरोध;
	हाल SEEK_6:
		what = "SEEK_6";
		अवरोध;
	हाल READ_REVERSE:
		what = "READ_REVERSE";
		अवरोध;
	हाल WRITE_खाताMARKS:
		what = "WRITE_FILEMARKS";
		अवरोध;
	हाल SPACE:
		what = "SPACE";
		अवरोध;
	हाल INQUIRY:
		what = "INQUIRY";
		अवरोध;
	हाल RECOVER_BUFFERED_DATA:
		what = "RECOVER_BUFFERED_DATA";
		अवरोध;
	हाल MODE_SELECT:
		what = "MODE_SELECT";
		अवरोध;
	हाल RESERVE:
		what = "RESERVE";
		अवरोध;
	हाल RELEASE:
		what = "RELEASE";
		अवरोध;
	हाल COPY:
		what = "COPY";
		अवरोध;
	हाल ERASE:
		what = "ERASE";
		अवरोध;
	हाल MODE_SENSE:
		what = "MODE_SENSE";
		अवरोध;
	हाल START_STOP:
		what = "START_STOP";
		अवरोध;
	हाल RECEIVE_DIAGNOSTIC:
		what = "RECEIVE_DIAGNOSTIC";
		अवरोध;
	हाल SEND_DIAGNOSTIC:
		what = "SEND_DIAGNOSTIC";
		अवरोध;
	हाल ALLOW_MEDIUM_REMOVAL:
		what = "ALLOW_MEDIUM_REMOVAL";
		अवरोध;
	हाल SET_WINDOW:
		what = "SET_WINDOW";
		अवरोध;
	हाल READ_CAPACITY:
		what = "READ_CAPACITY";
		अवरोध;
	हाल READ_10:
		what = "READ_10";
		अवरोध;
	हाल WRITE_10:
		what = "WRITE_10";
		अवरोध;
	हाल SEEK_10:
		what = "SEEK_10";
		अवरोध;
	हाल WRITE_VERIFY:
		what = "WRITE_VERIFY";
		अवरोध;
	हाल VERIFY:
		what = "VERIFY";
		अवरोध;
	हाल SEARCH_HIGH:
		what = "SEARCH_HIGH";
		अवरोध;
	हाल SEARCH_EQUAL:
		what = "SEARCH_EQUAL";
		अवरोध;
	हाल SEARCH_LOW:
		what = "SEARCH_LOW";
		अवरोध;
	हाल SET_LIMITS:
		what = "SET_LIMITS";
		अवरोध;
	हाल READ_POSITION:
		what = "READ_POSITION";
		अवरोध;
	हाल SYNCHRONIZE_CACHE:
		what = "SYNCHRONIZE_CACHE";
		अवरोध;
	हाल LOCK_UNLOCK_CACHE:
		what = "LOCK_UNLOCK_CACHE";
		अवरोध;
	हाल READ_DEFECT_DATA:
		what = "READ_DEFECT_DATA";
		अवरोध;
	हाल MEDIUM_SCAN:
		what = "MEDIUM_SCAN";
		अवरोध;
	हाल COMPARE:
		what = "COMPARE";
		अवरोध;
	हाल COPY_VERIFY:
		what = "COPY_VERIFY";
		अवरोध;
	हाल WRITE_BUFFER:
		what = "WRITE_BUFFER";
		अवरोध;
	हाल READ_BUFFER:
		what = "READ_BUFFER";
		अवरोध;
	हाल UPDATE_BLOCK:
		what = "UPDATE_BLOCK";
		अवरोध;
	हाल READ_LONG:
		what = "READ_LONG";
		अवरोध;
	हाल WRITE_LONG:
		what = "WRITE_LONG";
		अवरोध;
	हाल CHANGE_DEFINITION:
		what = "CHANGE_DEFINITION";
		अवरोध;
	हाल WRITE_SAME:
		what = "WRITE_SAME";
		अवरोध;
	हाल GPCMD_READ_SUBCHANNEL:
		what = "READ SUBCHANNEL";
		अवरोध;
	हाल READ_TOC:
		what = "READ_TOC";
		अवरोध;
	हाल GPCMD_READ_HEADER:
		what = "READ HEADER";
		अवरोध;
	हाल GPCMD_PLAY_AUDIO_10:
		what = "PLAY AUDIO (10)";
		अवरोध;
	हाल GPCMD_PLAY_AUDIO_MSF:
		what = "PLAY AUDIO MSF";
		अवरोध;
	हाल GPCMD_GET_EVENT_STATUS_NOTIFICATION:
		what = "GET EVENT/STATUS NOTIFICATION";
		अवरोध;
	हाल GPCMD_PAUSE_RESUME:
		what = "PAUSE/RESUME";
		अवरोध;
	हाल LOG_SELECT:
		what = "LOG_SELECT";
		अवरोध;
	हाल LOG_SENSE:
		what = "LOG_SENSE";
		अवरोध;
	हाल GPCMD_STOP_PLAY_SCAN:
		what = "STOP PLAY/SCAN";
		अवरोध;
	हाल GPCMD_READ_DISC_INFO:
		what = "READ DISC INFORMATION";
		अवरोध;
	हाल GPCMD_READ_TRACK_RZONE_INFO:
		what = "READ TRACK INFORMATION";
		अवरोध;
	हाल GPCMD_RESERVE_RZONE_TRACK:
		what = "RESERVE TRACK";
		अवरोध;
	हाल GPCMD_SEND_OPC:
		what = "SEND OPC";
		अवरोध;
	हाल MODE_SELECT_10:
		what = "MODE_SELECT_10";
		अवरोध;
	हाल GPCMD_REPAIR_RZONE_TRACK:
		what = "REPAIR TRACK";
		अवरोध;
	हाल 0x59:
		what = "READ MASTER CUE";
		अवरोध;
	हाल MODE_SENSE_10:
		what = "MODE_SENSE_10";
		अवरोध;
	हाल GPCMD_CLOSE_TRACK:
		what = "CLOSE TRACK/SESSION";
		अवरोध;
	हाल 0x5C:
		what = "READ BUFFER CAPACITY";
		अवरोध;
	हाल 0x5D:
		what = "SEND CUE SHEET";
		अवरोध;
	हाल GPCMD_BLANK:
		what = "BLANK";
		अवरोध;
	हाल REPORT_LUNS:
		what = "REPORT LUNS";
		अवरोध;
	हाल MOVE_MEDIUM:
		what = "MOVE_MEDIUM or PLAY AUDIO (12)";
		अवरोध;
	हाल READ_12:
		what = "READ_12";
		अवरोध;
	हाल WRITE_12:
		what = "WRITE_12";
		अवरोध;
	हाल WRITE_VERIFY_12:
		what = "WRITE_VERIFY_12";
		अवरोध;
	हाल SEARCH_HIGH_12:
		what = "SEARCH_HIGH_12";
		अवरोध;
	हाल SEARCH_EQUAL_12:
		what = "SEARCH_EQUAL_12";
		अवरोध;
	हाल SEARCH_LOW_12:
		what = "SEARCH_LOW_12";
		अवरोध;
	हाल SEND_VOLUME_TAG:
		what = "SEND_VOLUME_TAG";
		अवरोध;
	हाल READ_ELEMENT_STATUS:
		what = "READ_ELEMENT_STATUS";
		अवरोध;
	हाल GPCMD_READ_CD_MSF:
		what = "READ CD MSF";
		अवरोध;
	हाल GPCMD_SCAN:
		what = "SCAN";
		अवरोध;
	हाल GPCMD_SET_SPEED:
		what = "SET CD SPEED";
		अवरोध;
	हाल GPCMD_MECHANISM_STATUS:
		what = "MECHANISM STATUS";
		अवरोध;
	हाल GPCMD_READ_CD:
		what = "READ CD";
		अवरोध;
	हाल 0xE1:
		what = "WRITE CONTINUE";
		अवरोध;
	हाल WRITE_LONG_2:
		what = "WRITE_LONG_2";
		अवरोध;
	हाल VENDOR_CMND:
		what = "Realtek's vendor command";
		अवरोध;
	शेष:
		what = "(unknown command)";
		unknown_cmd = true;
		अवरोध;
	पूर्ण

	अगर (srb->cmnd[0] != TEST_UNIT_READY)
		dev_dbg(rtsx_dev(chip), "Command %s (%d bytes)\n",
			what, srb->cmd_len);

	अगर (unknown_cmd) अणु
		len = min_t(अचिन्हित लघु, srb->cmd_len, 16);
		dev_dbg(rtsx_dev(chip), "%*ph\n", len, srb->cmnd);
	पूर्ण
पूर्ण

व्योम set_sense_type(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun, पूर्णांक sense_type)
अणु
	चयन (sense_type) अणु
	हाल SENSE_TYPE_MEDIA_CHANGE:
		set_sense_data(chip, lun, CUR_ERR, 0x06, 0, 0x28, 0, 0, 0);
		अवरोध;

	हाल SENSE_TYPE_MEDIA_NOT_PRESENT:
		set_sense_data(chip, lun, CUR_ERR, 0x02, 0, 0x3A, 0, 0, 0);
		अवरोध;

	हाल SENSE_TYPE_MEDIA_LBA_OVER_RANGE:
		set_sense_data(chip, lun, CUR_ERR, 0x05, 0, 0x21, 0, 0, 0);
		अवरोध;

	हाल SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT:
		set_sense_data(chip, lun, CUR_ERR, 0x05, 0, 0x25, 0, 0, 0);
		अवरोध;

	हाल SENSE_TYPE_MEDIA_WRITE_PROTECT:
		set_sense_data(chip, lun, CUR_ERR, 0x07, 0, 0x27, 0, 0, 0);
		अवरोध;

	हाल SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR:
		set_sense_data(chip, lun, CUR_ERR, 0x03, 0, 0x11, 0, 0, 0);
		अवरोध;

	हाल SENSE_TYPE_MEDIA_WRITE_ERR:
		set_sense_data(chip, lun, CUR_ERR, 0x03, 0, 0x0C, 0x02, 0, 0);
		अवरोध;

	हाल SENSE_TYPE_MEDIA_INVALID_CMD_FIELD:
		set_sense_data(chip, lun, CUR_ERR, ILGAL_REQ, 0,
			       ASC_INVLD_CDB, ASCQ_INVLD_CDB, CDB_ILLEGAL, 1);
		अवरोध;

	हाल SENSE_TYPE_FORMAT_IN_PROGRESS:
		set_sense_data(chip, lun, CUR_ERR, 0x02, 0, 0x04, 0x04, 0, 0);
		अवरोध;

	हाल SENSE_TYPE_FORMAT_CMD_FAILED:
		set_sense_data(chip, lun, CUR_ERR, 0x03, 0, 0x31, 0x01, 0, 0);
		अवरोध;

#अगर_घोषित SUPPORT_MAGIC_GATE
	हाल SENSE_TYPE_MG_KEY_FAIL_NOT_ESTAB:
		set_sense_data(chip, lun, CUR_ERR, 0x05, 0, 0x6F, 0x02, 0, 0);
		अवरोध;

	हाल SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN:
		set_sense_data(chip, lun, CUR_ERR, 0x05, 0, 0x6F, 0x00, 0, 0);
		अवरोध;

	हाल SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM:
		set_sense_data(chip, lun, CUR_ERR, 0x02, 0, 0x30, 0x00, 0, 0);
		अवरोध;

	हाल SENSE_TYPE_MG_WRITE_ERR:
		set_sense_data(chip, lun, CUR_ERR, 0x03, 0, 0x0C, 0x00, 0, 0);
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित SUPPORT_SD_LOCK
	हाल SENSE_TYPE_MEDIA_READ_FORBIDDEN:
		set_sense_data(chip, lun, CUR_ERR, 0x07, 0, 0x11, 0x13, 0, 0);
		अवरोध;
#पूर्ण_अगर

	हाल SENSE_TYPE_NO_SENSE:
	शेष:
		set_sense_data(chip, lun, CUR_ERR, 0, 0, 0, 0, 0, 0);
		अवरोध;
	पूर्ण
पूर्ण

व्योम set_sense_data(काष्ठा rtsx_chip *chip, अचिन्हित पूर्णांक lun, u8 err_code,
		    u8 sense_key, u32 info, u8 asc, u8 ascq, u8 sns_key_info0,
		u16 sns_key_info1)
अणु
	काष्ठा sense_data_t *sense = &chip->sense_buffer[lun];

	sense->err_code = err_code;
	sense->sense_key = sense_key;
	sense->info[0] = (u8)(info >> 24);
	sense->info[1] = (u8)(info >> 16);
	sense->info[2] = (u8)(info >> 8);
	sense->info[3] = (u8)info;

	sense->ad_sense_len = माप(काष्ठा sense_data_t) - 8;
	sense->asc = asc;
	sense->ascq = ascq;
	अगर (sns_key_info0 != 0) अणु
		sense->sns_key_info[0] = SKSV | sns_key_info0;
		sense->sns_key_info[1] = (sns_key_info1 & 0xf0) >> 4;
		sense->sns_key_info[2] = sns_key_info1 & 0x0f;
	पूर्ण
पूर्ण

अटल पूर्णांक test_unit_पढ़ोy(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);

	अगर (!check_card_पढ़ोy(chip, lun)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (!(CHK_BIT(chip->lun_mc, lun))) अणु
		SET_BIT(chip->lun_mc, lun);
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		वापस TRANSPORT_FAILED;
	पूर्ण

#अगर_घोषित SUPPORT_SD_LOCK
	अगर (get_lun_card(chip, SCSI_LUN(srb)) == SD_CARD) अणु
		काष्ठा sd_info *sd_card = &chip->sd_card;

		अगर (sd_card->sd_lock_notअगरy) अणु
			sd_card->sd_lock_notअगरy = 0;
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
			वापस TRANSPORT_FAILED;
		पूर्ण अन्यथा अगर (sd_card->sd_lock_status & SD_LOCKED) अणु
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_READ_FORBIDDEN);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस TRANSPORT_GOOD;
पूर्ण

अटल अचिन्हित अक्षर क्रमmatter_inquiry_str[20] = अणु
	'M', 'E', 'M', 'O', 'R', 'Y', 'S', 'T', 'I', 'C', 'K',
#अगर_घोषित SUPPORT_MAGIC_GATE
	'-', 'M', 'G', /* Byte[47:49] */
#अन्यथा
	0x20, 0x20, 0x20,  /* Byte[47:49] */
#पूर्ण_अगर

#अगर_घोषित SUPPORT_MAGIC_GATE
	0x0B,  /* Byte[50]: MG, MS, MSPro, MSXC */
#अन्यथा
	0x09,  /* Byte[50]: MS, MSPro, MSXC */
#पूर्ण_अगर
	0x00,  /* Byte[51]: Category Specअगरic Commands */
	0x00,  /* Byte[52]: Access Control and feature */
	0x20, 0x20, 0x20, /* Byte[53:55] */
पूर्ण;

अटल पूर्णांक inquiry(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	अक्षर *inquiry_शेष = (अक्षर *)"Generic-xD/SD/M.S.      1.00 ";
	अक्षर *inquiry_sdms =    (अक्षर *)"Generic-SD/MemoryStick  1.00 ";
	अक्षर *inquiry_sd =      (अक्षर *)"Generic-SD/MMC          1.00 ";
	अक्षर *inquiry_ms =      (अक्षर *)"Generic-MemoryStick     1.00 ";
	अक्षर *inquiry_string;
	अचिन्हित अक्षर sendbytes;
	अचिन्हित अक्षर *buf;
	u8 card = get_lun_card(chip, lun);
	bool pro_क्रमmatter_flag = false;
	अचिन्हित अक्षर inquiry_buf[] = अणु
		QULIFIRE | DRCT_ACCESS_DEV,
		RMB_DISC | 0x0D,
		0x00,
		0x01,
		0x1f,
		0x02,
		0,
		REL_ADR | WBUS_32 | WBUS_16 | SYNC | LINKED | CMD_QUE | SFT_RE,
	पूर्ण;

	अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN)) अणु
		अगर (chip->lun2card[lun] == SD_CARD)
			inquiry_string = inquiry_sd;
		अन्यथा
			inquiry_string = inquiry_ms;

	पूर्ण अन्यथा अगर (CHECK_LUN_MODE(chip, SD_MS_1LUN)) अणु
		inquiry_string = inquiry_sdms;
	पूर्ण अन्यथा अणु
		inquiry_string = inquiry_शेष;
	पूर्ण

	buf = vदो_स्मृति(scsi_bufflen(srb));
	अगर (!buf)
		वापस TRANSPORT_ERROR;

#अगर_घोषित SUPPORT_MAGIC_GATE
	अगर ((chip->mspro_क्रमmatter_enable) &&
	    (chip->lun2card[lun] & MS_CARD))
#अन्यथा
	अगर (chip->mspro_क्रमmatter_enable)
#पूर्ण_अगर
		अगर (!card || (card == MS_CARD))
			pro_क्रमmatter_flag = true;

	अगर (pro_क्रमmatter_flag) अणु
		अगर (scsi_bufflen(srb) < 56)
			sendbytes = (अचिन्हित अक्षर)(scsi_bufflen(srb));
		अन्यथा
			sendbytes = 56;

	पूर्ण अन्यथा अणु
		अगर (scsi_bufflen(srb) < 36)
			sendbytes = (अचिन्हित अक्षर)(scsi_bufflen(srb));
		अन्यथा
			sendbytes = 36;
	पूर्ण

	अगर (sendbytes > 8) अणु
		स_नकल(buf, inquiry_buf, 8);
		म_नकलन(buf + 8, inquiry_string, sendbytes - 8);
		अगर (pro_क्रमmatter_flag) अणु
			/* Additional Length */
			buf[4] = 0x33;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(buf, inquiry_buf, sendbytes);
	पूर्ण

	अगर (pro_क्रमmatter_flag) अणु
		अगर (sendbytes > 36)
			स_नकल(buf + 36, क्रमmatter_inquiry_str, sendbytes - 36);
	पूर्ण

	scsi_set_resid(srb, 0);

	rtsx_stor_set_xfer_buf(buf, scsi_bufflen(srb), srb);
	vमुक्त(buf);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक start_stop_unit(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);

	scsi_set_resid(srb, scsi_bufflen(srb));

	अगर (srb->cmnd[1] == 1)
		वापस TRANSPORT_GOOD;

	चयन (srb->cmnd[0x4]) अणु
	हाल STOP_MEDIUM:
		/* Media disabled */
		वापस TRANSPORT_GOOD;

	हाल UNLOAD_MEDIUM:
		/* Media shall be unload */
		अगर (check_card_पढ़ोy(chip, lun))
			eject_card(chip, lun);
		वापस TRANSPORT_GOOD;

	हाल MAKE_MEDIUM_READY:
	हाल LOAD_MEDIUM:
		अगर (check_card_पढ़ोy(chip, lun))
			वापस TRANSPORT_GOOD;
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		वापस TRANSPORT_FAILED;

		अवरोध;
	पूर्ण

	वापस TRANSPORT_ERROR;
पूर्ण

अटल पूर्णांक allow_medium_removal(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक prevent;

	prevent = srb->cmnd[4] & 0x1;

	scsi_set_resid(srb, 0);

	अगर (prevent) अणु
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक request_sense(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sense_data_t *sense;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	काष्ठा ms_info *ms_card = &chip->ms_card;
	अचिन्हित अक्षर *पंचांगp, *buf;

	sense = &chip->sense_buffer[lun];

	अगर ((get_lun_card(chip, lun) == MS_CARD) &&
	    ms_card->pro_under_क्रमmatting) अणु
		अगर (ms_card->क्रमmat_status == FORMAT_SUCCESS) अणु
			set_sense_type(chip, lun, SENSE_TYPE_NO_SENSE);
			ms_card->pro_under_क्रमmatting = 0;
			ms_card->progress = 0;
		पूर्ण अन्यथा अगर (ms_card->क्रमmat_status == FORMAT_IN_PROGRESS) अणु
			/* Logical Unit Not Ready Format in Progress */
			set_sense_data(chip, lun, CUR_ERR, 0x02, 0, 0x04, 0x04,
				       0, (u16)(ms_card->progress));
		पूर्ण अन्यथा अणु
			/* Format Command Failed */
			set_sense_type(chip, lun, SENSE_TYPE_FORMAT_CMD_FAILED);
			ms_card->pro_under_क्रमmatting = 0;
			ms_card->progress = 0;
		पूर्ण

		rtsx_set_stat(chip, RTSX_STAT_RUN);
	पूर्ण

	buf = vदो_स्मृति(scsi_bufflen(srb));
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	पंचांगp = (अचिन्हित अक्षर *)sense;
	स_नकल(buf, पंचांगp, scsi_bufflen(srb));

	rtsx_stor_set_xfer_buf(buf, scsi_bufflen(srb), srb);
	vमुक्त(buf);

	scsi_set_resid(srb, 0);
	/* Reset Sense Data */
	set_sense_type(chip, lun, SENSE_TYPE_NO_SENSE);
	वापस TRANSPORT_GOOD;
पूर्ण

अटल व्योम ms_mode_sense(काष्ठा rtsx_chip *chip, u8 cmd,
			  पूर्णांक lun, u8 *buf, पूर्णांक buf_len)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक sys_info_offset;
	पूर्णांक data_size = buf_len;
	bool support_क्रमmat = false;
	पूर्णांक i = 0;

	अगर (cmd == MODE_SENSE) अणु
		sys_info_offset = 8;
		अगर (data_size > 0x68)
			data_size = 0x68;

		buf[i++] = 0x67;  /* Mode Data Length */
	पूर्ण अन्यथा अणु
		sys_info_offset = 12;
		अगर (data_size > 0x6C)
			data_size = 0x6C;

		buf[i++] = 0x00;  /* Mode Data Length (MSB) */
		buf[i++] = 0x6A;  /* Mode Data Length (LSB) */
	पूर्ण

	/* Medium Type Code */
	अगर (check_card_पढ़ोy(chip, lun)) अणु
		अगर (CHK_MSXC(ms_card)) अणु
			support_क्रमmat = true;
			buf[i++] = 0x40;
		पूर्ण अन्यथा अगर (CHK_MSPRO(ms_card)) अणु
			support_क्रमmat = true;
			buf[i++] = 0x20;
		पूर्ण अन्यथा अणु
			buf[i++] = 0x10;
		पूर्ण

		/* WP */
		अगर (check_card_wp(chip, lun))
			buf[i++] = 0x80;
		अन्यथा
			buf[i++] = 0x00;

	पूर्ण अन्यथा अणु
		buf[i++] = 0x00;	/* MediaType */
		buf[i++] = 0x00;	/* WP */
	पूर्ण

	buf[i++] = 0x00;		/* Reserved */

	अगर (cmd == MODE_SENSE_10) अणु
		buf[i++] = 0x00;  /* Reserved */
		buf[i++] = 0x00;  /* Block descriptor length(MSB) */
		buf[i++] = 0x00;  /* Block descriptor length(LSB) */

		/* The Following Data is the content of "Page 0x20" */
		अगर (data_size >= 9)
			buf[i++] = 0x20;		/* Page Code */
		अगर (data_size >= 10)
			buf[i++] = 0x62;		/* Page Length */
		अगर (data_size >= 11)
			buf[i++] = 0x00;		/* No Access Control */
		अगर (data_size >= 12) अणु
			अगर (support_क्रमmat)
				buf[i++] = 0xC0;	/* SF, SGM */
			अन्यथा
				buf[i++] = 0x00;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* The Following Data is the content of "Page 0x20" */
		अगर (data_size >= 5)
			buf[i++] = 0x20;		/* Page Code */
		अगर (data_size >= 6)
			buf[i++] = 0x62;		/* Page Length */
		अगर (data_size >= 7)
			buf[i++] = 0x00;		/* No Access Control */
		अगर (data_size >= 8) अणु
			अगर (support_क्रमmat)
				buf[i++] = 0xC0;	/* SF, SGM */
			अन्यथा
				buf[i++] = 0x00;
		पूर्ण
	पूर्ण

	अगर (data_size > sys_info_offset) अणु
		/* 96 Bytes Attribute Data */
		पूर्णांक len = data_size - sys_info_offset;

		len = (len < 96) ? len : 96;

		स_नकल(buf + sys_info_offset, ms_card->raw_sys_info, len);
	पूर्ण
पूर्ण

अटल पूर्णांक mode_sense(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	अचिन्हित पूर्णांक data_size;
	पूर्णांक status;
	bool pro_क्रमmatter_flag;
	अचिन्हित अक्षर page_code, *buf;
	u8 card = get_lun_card(chip, lun);

#अगर_अघोषित SUPPORT_MAGIC_GATE
	अगर (!check_card_पढ़ोy(chip, lun)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		scsi_set_resid(srb, scsi_bufflen(srb));
		वापस TRANSPORT_FAILED;
	पूर्ण
#पूर्ण_अगर

	pro_क्रमmatter_flag = false;
	data_size = 8;
#अगर_घोषित SUPPORT_MAGIC_GATE
	अगर ((chip->lun2card[lun] & MS_CARD)) अणु
		अगर (!card || (card == MS_CARD)) अणु
			data_size = 108;
			अगर (chip->mspro_क्रमmatter_enable)
				pro_क्रमmatter_flag = true;
		पूर्ण
	पूर्ण
#अन्यथा
	अगर (card == MS_CARD) अणु
		अगर (chip->mspro_क्रमmatter_enable) अणु
			pro_क्रमmatter_flag = true;
			data_size = 108;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	buf = kदो_स्मृति(data_size, GFP_KERNEL);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	page_code = srb->cmnd[2] & 0x3f;

	अगर ((page_code == 0x3F) || (page_code == 0x1C) ||
	    (page_code == 0x00) ||
		(pro_क्रमmatter_flag && (page_code == 0x20))) अणु
		अगर (srb->cmnd[0] == MODE_SENSE) अणु
			अगर ((page_code == 0x3F) || (page_code == 0x20)) अणु
				ms_mode_sense(chip, srb->cmnd[0],
					      lun, buf, data_size);
			पूर्ण अन्यथा अणु
				data_size = 4;
				buf[0] = 0x03;
				buf[1] = 0x00;
				अगर (check_card_wp(chip, lun))
					buf[2] = 0x80;
				अन्यथा
					buf[2] = 0x00;

				buf[3] = 0x00;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((page_code == 0x3F) || (page_code == 0x20)) अणु
				ms_mode_sense(chip, srb->cmnd[0],
					      lun, buf, data_size);
			पूर्ण अन्यथा अणु
				data_size = 8;
				buf[0] = 0x00;
				buf[1] = 0x06;
				buf[2] = 0x00;
				अगर (check_card_wp(chip, lun))
					buf[3] = 0x80;
				अन्यथा
					buf[3] = 0x00;
				buf[4] = 0x00;
				buf[5] = 0x00;
				buf[6] = 0x00;
				buf[7] = 0x00;
			पूर्ण
		पूर्ण
		status = TRANSPORT_GOOD;
	पूर्ण अन्यथा अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		scsi_set_resid(srb, scsi_bufflen(srb));
		status = TRANSPORT_FAILED;
	पूर्ण

	अगर (status == TRANSPORT_GOOD) अणु
		अचिन्हित पूर्णांक len = min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb),
					data_size);
		rtsx_stor_set_xfer_buf(buf, len, srb);
		scsi_set_resid(srb, scsi_bufflen(srb) - len);
	पूर्ण
	kमुक्त(buf);

	वापस status;
पूर्ण

अटल पूर्णांक पढ़ो_ग_लिखो(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
#अगर_घोषित SUPPORT_SD_LOCK
	काष्ठा sd_info *sd_card = &chip->sd_card;
#पूर्ण_अगर
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक retval;
	u32 start_sec;
	u16 sec_cnt;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	अगर (!check_card_पढ़ोy(chip, lun) || (get_card_size(chip, lun) == 0)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (!(CHK_BIT(chip->lun_mc, lun))) अणु
		SET_BIT(chip->lun_mc, lun);
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		वापस TRANSPORT_FAILED;
	पूर्ण

#अगर_घोषित SUPPORT_SD_LOCK
	अगर (sd_card->sd_erase_status) अणु
		/* Accessing to any card is क्रमbidden
		 * until the erase procedure of SD is completed
		 */
		dev_dbg(rtsx_dev(chip), "SD card being erased!\n");
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_READ_FORBIDDEN);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (get_lun_card(chip, lun) == SD_CARD) अणु
		अगर (sd_card->sd_lock_status & SD_LOCKED) अणु
			dev_dbg(rtsx_dev(chip), "SD card locked!\n");
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_READ_FORBIDDEN);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर ((srb->cmnd[0] == READ_10) || (srb->cmnd[0] == WRITE_10)) अणु
		start_sec = ((u32)srb->cmnd[2] << 24) |
			((u32)srb->cmnd[3] << 16) |
			((u32)srb->cmnd[4] << 8) | ((u32)srb->cmnd[5]);
		sec_cnt = ((u16)(srb->cmnd[7]) << 8) | srb->cmnd[8];
	पूर्ण अन्यथा अगर ((srb->cmnd[0] == READ_6) || (srb->cmnd[0] == WRITE_6)) अणु
		start_sec = ((u32)(srb->cmnd[1] & 0x1F) << 16) |
			((u32)srb->cmnd[2] << 8) | ((u32)srb->cmnd[3]);
		sec_cnt = srb->cmnd[4];
		अगर (sec_cnt == 0)
			sec_cnt = 256;
	पूर्ण अन्यथा अगर ((srb->cmnd[0] == VENDOR_CMND) &&
		(srb->cmnd[1] == SCSI_APP_CMD) &&
		((srb->cmnd[2] == PP_READ10) || (srb->cmnd[2] == PP_WRITE10))) अणु
		start_sec = ((u32)srb->cmnd[4] << 24) |
			((u32)srb->cmnd[5] << 16) |
			((u32)srb->cmnd[6] << 8) | ((u32)srb->cmnd[7]);
		sec_cnt = ((u16)(srb->cmnd[9]) << 8) | srb->cmnd[10];
	पूर्ण अन्यथा अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	/* In some test, we will receive a start_sec like 0xFFFFFFFF.
	 * In this situation, start_sec + sec_cnt will overflow, so we
	 * need to judge start_sec at first
	 */
	अगर ((start_sec > get_card_size(chip, lun)) ||
	    ((start_sec + sec_cnt) > get_card_size(chip, lun))) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_LBA_OVER_RANGE);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (sec_cnt == 0) अणु
		scsi_set_resid(srb, 0);
		वापस TRANSPORT_GOOD;
	पूर्ण

	अगर (chip->rw_fail_cnt[lun] == 3) अणु
		dev_dbg(rtsx_dev(chip), "read/write fail three times in succession\n");
		अगर (srb->sc_data_direction == DMA_FROM_DEVICE)
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
		अन्यथा
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_WRITE_ERR);

		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (srb->sc_data_direction == DMA_TO_DEVICE) अणु
		अगर (check_card_wp(chip, lun)) अणु
			dev_dbg(rtsx_dev(chip), "Write protected card!\n");
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_WRITE_PROTECT);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण

	retval = card_rw(srb, chip, start_sec, sec_cnt);
	अगर (retval != STATUS_SUCCESS) अणु
		अगर (chip->need_release & chip->lun2card[lun]) अणु
			chip->rw_fail_cnt[lun] = 0;
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		पूर्ण अन्यथा अणु
			chip->rw_fail_cnt[lun]++;
			अगर (srb->sc_data_direction == DMA_FROM_DEVICE)
				set_sense_type
					(chip, lun,
					 SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			अन्यथा
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
		पूर्ण
		retval = TRANSPORT_FAILED;
		जाओ निकास;
	पूर्ण अन्यथा अणु
		chip->rw_fail_cnt[lun] = 0;
		retval = TRANSPORT_GOOD;
	पूर्ण

	scsi_set_resid(srb, 0);

निकास:
	वापस retval;
पूर्ण

अटल पूर्णांक पढ़ो_क्रमmat_capacity(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	अचिन्हित पूर्णांक buf_len;
	u8 card = get_lun_card(chip, lun);
	u32 card_size;
	पूर्णांक desc_cnt;
	पूर्णांक i = 0;

	अगर (!check_card_पढ़ोy(chip, lun)) अणु
		अगर (!chip->mspro_क्रमmatter_enable) अणु
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण

	buf_len = (scsi_bufflen(srb) > 12) ? 0x14 : 12;

	buf = kदो_स्मृति(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	buf[i++] = 0;
	buf[i++] = 0;
	buf[i++] = 0;

	/* Capacity List Length */
	अगर ((buf_len > 12) && chip->mspro_क्रमmatter_enable &&
	    (chip->lun2card[lun] & MS_CARD) &&
	    (!card || (card == MS_CARD))) अणु
		buf[i++] = 0x10;
		desc_cnt = 2;
	पूर्ण अन्यथा अणु
		buf[i++] = 0x08;
		desc_cnt = 1;
	पूर्ण

	जबतक (desc_cnt) अणु
		अगर (check_card_पढ़ोy(chip, lun)) अणु
			card_size = get_card_size(chip, lun);
			buf[i++] = (अचिन्हित अक्षर)(card_size >> 24);
			buf[i++] = (अचिन्हित अक्षर)(card_size >> 16);
			buf[i++] = (अचिन्हित अक्षर)(card_size >> 8);
			buf[i++] = (अचिन्हित अक्षर)card_size;

			अगर (desc_cnt == 2)
				buf[i++] = 2;
			अन्यथा
				buf[i++] = 0;
		पूर्ण अन्यथा अणु
			buf[i++] = 0xFF;
			buf[i++] = 0xFF;
			buf[i++] = 0xFF;
			buf[i++] = 0xFF;

			अगर (desc_cnt == 2)
				buf[i++] = 3;
			अन्यथा
				buf[i++] = 0;
		पूर्ण

		buf[i++] = 0x00;
		buf[i++] = 0x02;
		buf[i++] = 0x00;

		desc_cnt--;
	पूर्ण

	buf_len = min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), buf_len);
	rtsx_stor_set_xfer_buf(buf, buf_len, srb);
	kमुक्त(buf);

	scsi_set_resid(srb, scsi_bufflen(srb) - buf_len);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक पढ़ो_capacity(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u32 card_size;

	अगर (!check_card_पढ़ोy(chip, lun)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (!(CHK_BIT(chip->lun_mc, lun))) अणु
		SET_BIT(chip->lun_mc, lun);
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		वापस TRANSPORT_FAILED;
	पूर्ण

	buf = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	card_size = get_card_size(chip, lun);
	buf[0] = (अचिन्हित अक्षर)((card_size - 1) >> 24);
	buf[1] = (अचिन्हित अक्षर)((card_size - 1) >> 16);
	buf[2] = (अचिन्हित अक्षर)((card_size - 1) >> 8);
	buf[3] = (अचिन्हित अक्षर)(card_size - 1);

	buf[4] = 0x00;
	buf[5] = 0x00;
	buf[6] = 0x02;
	buf[7] = 0x00;

	rtsx_stor_set_xfer_buf(buf, scsi_bufflen(srb), srb);
	kमुक्त(buf);

	scsi_set_resid(srb, 0);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक पढ़ो_eeprom(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित लघु len, i;
	पूर्णांक retval;
	u8 *buf;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	len = ((u16)srb->cmnd[4] << 8) | srb->cmnd[5];

	buf = vदो_स्मृति(len);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
	अगर (retval != STATUS_SUCCESS) अणु
		vमुक्त(buf);
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
		वापस TRANSPORT_FAILED;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		retval = spi_पढ़ो_eeprom(chip, i, buf + i);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(buf);
			set_sense_type(chip, SCSI_LUN(srb),
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण

	len = (अचिन्हित लघु)min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), len);
	rtsx_stor_set_xfer_buf(buf, len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - len);

	vमुक्त(buf);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ग_लिखो_eeprom(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित लघु len, i;
	पूर्णांक retval;
	u8 *buf;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	len = ((u16)srb->cmnd[4] << 8) | srb->cmnd[5];

	retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, SCSI_LUN(srb), SENSE_TYPE_MEDIA_WRITE_ERR);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (len == 511) अणु
		retval = spi_erase_eeprom_chip(chip);
		अगर (retval != STATUS_SUCCESS) अणु
			set_sense_type(chip, SCSI_LUN(srb),
				       SENSE_TYPE_MEDIA_WRITE_ERR);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण अन्यथा अणु
		len = (अचिन्हित लघु)min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb),
					len);
		buf = vदो_स्मृति(len);
		अगर (!buf)
			वापस TRANSPORT_ERROR;

		rtsx_stor_get_xfer_buf(buf, len, srb);
		scsi_set_resid(srb, scsi_bufflen(srb) - len);

		क्रम (i = 0; i < len; i++) अणु
			retval = spi_ग_लिखो_eeprom(chip, i, buf[i]);
			अगर (retval != STATUS_SUCCESS) अणु
				vमुक्त(buf);
				set_sense_type(chip, SCSI_LUN(srb),
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				वापस TRANSPORT_FAILED;
			पूर्ण
		पूर्ण

		vमुक्त(buf);
	पूर्ण

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक पढ़ो_mem(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित लघु addr, len, i;
	पूर्णांक retval;
	u8 *buf;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	addr = ((u16)srb->cmnd[2] << 8) | srb->cmnd[3];
	len = ((u16)srb->cmnd[4] << 8) | srb->cmnd[5];

	अगर (addr < 0xFC00) अणु
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	buf = vदो_स्मृति(len);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
	अगर (retval != STATUS_SUCCESS) अणु
		vमुक्त(buf);
		set_sense_type(chip, SCSI_LUN(srb), SENSE_TYPE_MEDIA_WRITE_ERR);
		वापस TRANSPORT_FAILED;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		retval = rtsx_पढ़ो_रेजिस्टर(chip, addr + i, buf + i);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(buf);
			set_sense_type(chip, SCSI_LUN(srb),
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण

	len = (अचिन्हित लघु)min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), len);
	rtsx_stor_set_xfer_buf(buf, len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - len);

	vमुक्त(buf);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ग_लिखो_mem(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित लघु addr, len, i;
	पूर्णांक retval;
	u8 *buf;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	addr = ((u16)srb->cmnd[2] << 8) | srb->cmnd[3];
	len = ((u16)srb->cmnd[4] << 8) | srb->cmnd[5];

	अगर (addr < 0xFC00) अणु
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	len = (अचिन्हित लघु)min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), len);
	buf = vदो_स्मृति(len);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	rtsx_stor_get_xfer_buf(buf, len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - len);

	retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
	अगर (retval != STATUS_SUCCESS) अणु
		vमुक्त(buf);
		set_sense_type(chip, SCSI_LUN(srb), SENSE_TYPE_MEDIA_WRITE_ERR);
		वापस TRANSPORT_FAILED;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, addr + i, 0xFF, buf[i]);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(buf);
			set_sense_type(chip, SCSI_LUN(srb),
				       SENSE_TYPE_MEDIA_WRITE_ERR);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण

	vमुक्त(buf);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक get_sd_csd(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);

	अगर (!check_card_पढ़ोy(chip, lun)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (get_lun_card(chip, lun) != SD_CARD) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
		वापस TRANSPORT_FAILED;
	पूर्ण

	scsi_set_resid(srb, 0);
	rtsx_stor_set_xfer_buf(sd_card->raw_csd, scsi_bufflen(srb), srb);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक toggle_gpio_cmd(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	u8 gpio = srb->cmnd[2];

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	अगर (gpio > 3)
		gpio = 1;
	toggle_gpio(chip, gpio);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक पढ़ो_host_reg(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	u8 addr, buf[4];
	u32 val;
	अचिन्हित पूर्णांक len;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	addr = srb->cmnd[4];

	val = rtsx_पढ़ोl(chip, addr);
	dev_dbg(rtsx_dev(chip), "Host register (0x%x): 0x%x\n", addr, val);

	buf[0] = (u8)(val >> 24);
	buf[1] = (u8)(val >> 16);
	buf[2] = (u8)(val >> 8);
	buf[3] = (u8)val;

	len = min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), 4);
	rtsx_stor_set_xfer_buf(buf, len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - len);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ग_लिखो_host_reg(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	u8 addr, buf[4];
	u32 val;
	अचिन्हित पूर्णांक len;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	addr = srb->cmnd[4];

	len = min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), 4);
	rtsx_stor_get_xfer_buf(buf, len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - len);

	val = ((u32)buf[0] << 24) | ((u32)buf[1] << 16) | ((u32)buf[2]
							<< 8) | buf[3];

	rtsx_ग_लिखोl(chip, addr, val);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक set_variable(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);

	अगर (srb->cmnd[3] == 1) अणु
		/* Variable Clock */
		काष्ठा xd_info *xd_card = &chip->xd_card;
		काष्ठा sd_info *sd_card = &chip->sd_card;
		काष्ठा ms_info *ms_card = &chip->ms_card;

		चयन (srb->cmnd[4]) अणु
		हाल XD_CARD:
			xd_card->xd_घड़ी = srb->cmnd[5];
			अवरोध;

		हाल SD_CARD:
			sd_card->sd_घड़ी = srb->cmnd[5];
			अवरोध;

		हाल MS_CARD:
			ms_card->ms_घड़ी = srb->cmnd[5];
			अवरोध;

		शेष:
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण अन्यथा अगर (srb->cmnd[3] == 2) अणु
		अगर (srb->cmnd[4]) अणु
			chip->blink_led = 1;
		पूर्ण अन्यथा अणु
			पूर्णांक retval;

			chip->blink_led = 0;

			rtsx_disable_aspm(chip);

			अगर (chip->ss_en &&
			    (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
				rtsx_निकास_ss(chip);
				रुको_समयout(100);
			पूर्ण
			rtsx_set_stat(chip, RTSX_STAT_RUN);

			retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
			अगर (retval != STATUS_SUCCESS) अणु
				set_sense_type(chip, SCSI_LUN(srb),
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				वापस TRANSPORT_FAILED;
			पूर्ण

			turn_off_led(chip, LED_GPIO);
		पूर्ण
	पूर्ण अन्यथा अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक get_variable(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);

	अगर (srb->cmnd[3] == 1) अणु
		काष्ठा xd_info *xd_card = &chip->xd_card;
		काष्ठा sd_info *sd_card = &chip->sd_card;
		काष्ठा ms_info *ms_card = &chip->ms_card;
		u8 पंचांगp;

		चयन (srb->cmnd[4]) अणु
		हाल XD_CARD:
			पंचांगp = (u8)(xd_card->xd_घड़ी);
			अवरोध;

		हाल SD_CARD:
			पंचांगp = (u8)(sd_card->sd_घड़ी);
			अवरोध;

		हाल MS_CARD:
			पंचांगp = (u8)(ms_card->ms_घड़ी);
			अवरोध;

		शेष:
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			वापस TRANSPORT_FAILED;
		पूर्ण

		rtsx_stor_set_xfer_buf(&पंचांगp, 1, srb);
	पूर्ण अन्यथा अगर (srb->cmnd[3] == 2) अणु
		u8 पंचांगp = chip->blink_led;

		rtsx_stor_set_xfer_buf(&पंचांगp, 1, srb);
	पूर्ण अन्यथा अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक dma_access_ring_buffer(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u16 len;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	len = ((u16)(srb->cmnd[4]) << 8) | srb->cmnd[5];
	len = min_t(u16, len, scsi_bufflen(srb));

	अगर (srb->sc_data_direction == DMA_FROM_DEVICE)
		dev_dbg(rtsx_dev(chip), "Read from device\n");
	अन्यथा
		dev_dbg(rtsx_dev(chip), "Write to device\n");

	retval = rtsx_transfer_data(chip, 0, scsi_sglist(srb), len,
				    scsi_sg_count(srb), srb->sc_data_direction,
				    1000);
	अगर (retval < 0) अणु
		अगर (srb->sc_data_direction == DMA_FROM_DEVICE)
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
		अन्यथा
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_WRITE_ERR);

		वापस TRANSPORT_FAILED;
	पूर्ण
	scsi_set_resid(srb, 0);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक get_dev_status(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा sd_info *sd_card = &chip->sd_card;
	काष्ठा ms_info *ms_card = &chip->ms_card;
	पूर्णांक buf_len;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u8 card = get_lun_card(chip, lun);
	u8 status[32];
#अगर_घोषित SUPPORT_OCP
	u8 oc_now_mask = 0, oc_ever_mask = 0;
#पूर्ण_अगर

	स_रखो(status, 0, 32);

	status[0] = (u8)(chip->product_id);
	status[1] = chip->ic_version;

	अगर (chip->स्वतः_delink_en)
		status[2] = 0x10;
	अन्यथा
		status[2] = 0x00;

	status[3] = 20;
	status[4] = 10;
	status[5] = 05;
	status[6] = 21;

	अगर (chip->card_wp)
		status[7] = 0x20;
	अन्यथा
		status[7] = 0x00;

#अगर_घोषित SUPPORT_OCP
	status[8] = 0;
	अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN) &&
	    (chip->lun2card[lun] == MS_CARD)) अणु
		oc_now_mask = MS_OC_NOW;
		oc_ever_mask = MS_OC_EVER;
	पूर्ण अन्यथा अणु
		oc_now_mask = SD_OC_NOW;
		oc_ever_mask = SD_OC_EVER;
	पूर्ण

	अगर (chip->ocp_stat & oc_now_mask)
		status[8] |= 0x02;

	अगर (chip->ocp_stat & oc_ever_mask)
		status[8] |= 0x01;
#पूर्ण_अगर

	अगर (card == SD_CARD) अणु
		अगर (CHK_SD(sd_card)) अणु
			अगर (CHK_SD_HCXC(sd_card)) अणु
				अगर (sd_card->capacity > 0x4000000)
					status[0x0E] = 0x02;
				अन्यथा
					status[0x0E] = 0x01;
			पूर्ण अन्यथा अणु
				status[0x0E] = 0x00;
			पूर्ण

			अगर (CHK_SD_SDR104(sd_card))
				status[0x0F] = 0x03;
			अन्यथा अगर (CHK_SD_DDR50(sd_card))
				status[0x0F] = 0x04;
			अन्यथा अगर (CHK_SD_SDR50(sd_card))
				status[0x0F] = 0x02;
			अन्यथा अगर (CHK_SD_HS(sd_card))
				status[0x0F] = 0x01;
			अन्यथा
				status[0x0F] = 0x00;
		पूर्ण अन्यथा अणु
			अगर (CHK_MMC_SECTOR_MODE(sd_card))
				status[0x0E] = 0x01;
			अन्यथा
				status[0x0E] = 0x00;

			अगर (CHK_MMC_DDR52(sd_card))
				status[0x0F] = 0x03;
			अन्यथा अगर (CHK_MMC_52M(sd_card))
				status[0x0F] = 0x02;
			अन्यथा अगर (CHK_MMC_26M(sd_card))
				status[0x0F] = 0x01;
			अन्यथा
				status[0x0F] = 0x00;
		पूर्ण
	पूर्ण अन्यथा अगर (card == MS_CARD) अणु
		अगर (CHK_MSPRO(ms_card)) अणु
			अगर (CHK_MSXC(ms_card))
				status[0x0E] = 0x01;
			अन्यथा
				status[0x0E] = 0x00;

			अगर (CHK_HG8BIT(ms_card))
				status[0x0F] = 0x01;
			अन्यथा
				status[0x0F] = 0x00;
		पूर्ण
	पूर्ण

#अगर_घोषित SUPPORT_SD_LOCK
	अगर (card == SD_CARD) अणु
		status[0x17] = 0x80;
		अगर (sd_card->sd_erase_status)
			status[0x17] |= 0x01;
		अगर (sd_card->sd_lock_status & SD_LOCKED) अणु
			status[0x17] |= 0x02;
			status[0x07] |= 0x40;
		पूर्ण
		अगर (sd_card->sd_lock_status & SD_PWD_EXIST)
			status[0x17] |= 0x04;
	पूर्ण अन्यथा अणु
		status[0x17] = 0x00;
	पूर्ण

	dev_dbg(rtsx_dev(chip), "status[0x17] = 0x%x\n", status[0x17]);
#पूर्ण_अगर

	status[0x18] = 0x8A;
	status[0x1A] = 0x28;
#अगर_घोषित SUPPORT_SD_LOCK
	status[0x1F] = 0x01;
#पूर्ण_अगर

	buf_len = min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), माप(status));
	rtsx_stor_set_xfer_buf(status, buf_len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - buf_len);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक set_chip_mode(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक phy_debug_mode;
	पूर्णांक retval;
	u16 reg;

	अगर (!CHECK_PID(chip, 0x5208)) अणु
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	phy_debug_mode = (पूर्णांक)(srb->cmnd[3]);

	अगर (phy_debug_mode) अणु
		chip->phy_debug_mode = 1;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CDRESUMECTL, 0x77, 0);
		अगर (retval != STATUS_SUCCESS)
			वापस TRANSPORT_FAILED;

		rtsx_disable_bus_पूर्णांक(chip);

		retval = rtsx_पढ़ो_phy_रेजिस्टर(chip, 0x1C, &reg);
		अगर (retval != STATUS_SUCCESS)
			वापस TRANSPORT_FAILED;

		reg |= 0x0001;
		retval = rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x1C, reg);
		अगर (retval != STATUS_SUCCESS)
			वापस TRANSPORT_FAILED;
	पूर्ण अन्यथा अणु
		chip->phy_debug_mode = 0;
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, CDRESUMECTL, 0x77, 0x77);
		अगर (retval != STATUS_SUCCESS)
			वापस TRANSPORT_FAILED;

		rtsx_enable_bus_पूर्णांक(chip);

		retval = rtsx_पढ़ो_phy_रेजिस्टर(chip, 0x1C, &reg);
		अगर (retval != STATUS_SUCCESS)
			वापस TRANSPORT_FAILED;

		reg &= 0xFFFE;
		retval = rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x1C, reg);
		अगर (retval != STATUS_SUCCESS)
			वापस TRANSPORT_FAILED;
	पूर्ण

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक rw_mem_cmd_buf(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval =  STATUS_SUCCESS;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u8 cmd_type, mask, value, idx;
	u16 addr;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	चयन (srb->cmnd[3]) अणु
	हाल INIT_BATCHCMD:
		rtsx_init_cmd(chip);
		अवरोध;

	हाल ADD_BATCHCMD:
		cmd_type = srb->cmnd[4];
		अगर (cmd_type > 2) अणु
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			वापस TRANSPORT_FAILED;
		पूर्ण
		addr = (srb->cmnd[5] << 8) | srb->cmnd[6];
		mask = srb->cmnd[7];
		value = srb->cmnd[8];
		rtsx_add_cmd(chip, cmd_type, addr, mask, value);
		अवरोध;

	हाल SEND_BATCHCMD:
		retval = rtsx_send_cmd(chip, 0, 1000);
		अवरोध;

	हाल GET_BATCHRSP:
		idx = srb->cmnd[4];
		value = *(rtsx_get_cmd_data(chip) + idx);
		अगर (scsi_bufflen(srb) < 1) अणु
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			वापस TRANSPORT_FAILED;
		पूर्ण
		rtsx_stor_set_xfer_buf(&value, 1, srb);
		scsi_set_resid(srb, 0);
		अवरोध;

	शेष:
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_WRITE_ERR);
		वापस TRANSPORT_FAILED;
	पूर्ण

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक suit_cmd(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	चयन (srb->cmnd[3]) अणु
	हाल INIT_BATCHCMD:
	हाल ADD_BATCHCMD:
	हाल SEND_BATCHCMD:
	हाल GET_BATCHRSP:
		वापस rw_mem_cmd_buf(srb, chip);
	शेष:
		वापस TRANSPORT_ERROR;
	पूर्ण
पूर्ण

अटल पूर्णांक पढ़ो_phy_रेजिस्टर(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित लघु addr, len, i;
	पूर्णांक retval;
	u8 *buf;
	u16 val;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	addr = ((u16)srb->cmnd[4] << 8) | srb->cmnd[5];
	len = ((u16)srb->cmnd[6] << 8) | srb->cmnd[7];

	अगर (len % 2)
		len -= len % 2;

	अगर (len) अणु
		buf = vदो_स्मृति(len);
		अगर (!buf)
			वापस TRANSPORT_ERROR;

		retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(buf);
			set_sense_type(chip, SCSI_LUN(srb),
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			वापस TRANSPORT_FAILED;
		पूर्ण

		क्रम (i = 0; i < len / 2; i++) अणु
			retval = rtsx_पढ़ो_phy_रेजिस्टर(chip, addr + i, &val);
			अगर (retval != STATUS_SUCCESS) अणु
				vमुक्त(buf);
				set_sense_type
					(chip, SCSI_LUN(srb),
					 SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
				वापस TRANSPORT_FAILED;
			पूर्ण

			buf[2 * i] = (u8)(val >> 8);
			buf[2 * i + 1] = (u8)val;
		पूर्ण

		len = (अचिन्हित लघु)min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb),
					len);
		rtsx_stor_set_xfer_buf(buf, len, srb);
		scsi_set_resid(srb, scsi_bufflen(srb) - len);

		vमुक्त(buf);
	पूर्ण

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ग_लिखो_phy_रेजिस्टर(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित लघु addr, len, i;
	पूर्णांक retval;
	u8 *buf;
	u16 val;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	addr = ((u16)srb->cmnd[4] << 8) | srb->cmnd[5];
	len = ((u16)srb->cmnd[6] << 8) | srb->cmnd[7];

	अगर (len % 2)
		len -= len % 2;

	अगर (len) अणु
		len = (अचिन्हित लघु)min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb),
					len);

		buf = vदो_स्मृति(len);
		अगर (!buf)
			वापस TRANSPORT_ERROR;

		rtsx_stor_get_xfer_buf(buf, len, srb);
		scsi_set_resid(srb, scsi_bufflen(srb) - len);

		retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(buf);
			set_sense_type(chip, SCSI_LUN(srb),
				       SENSE_TYPE_MEDIA_WRITE_ERR);
			वापस TRANSPORT_FAILED;
		पूर्ण

		क्रम (i = 0; i < len / 2; i++) अणु
			val = ((u16)buf[2 * i] << 8) | buf[2 * i + 1];
			retval = rtsx_ग_लिखो_phy_रेजिस्टर(chip, addr + i, val);
			अगर (retval != STATUS_SUCCESS) अणु
				vमुक्त(buf);
				set_sense_type(chip, SCSI_LUN(srb),
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				वापस TRANSPORT_FAILED;
			पूर्ण
		पूर्ण

		vमुक्त(buf);
	पूर्ण

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक erase_eeprom2(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित लघु addr;
	पूर्णांक retval;
	u8 mode;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, SCSI_LUN(srb), SENSE_TYPE_MEDIA_WRITE_ERR);
		वापस TRANSPORT_FAILED;
	पूर्ण

	mode = srb->cmnd[3];
	addr = ((u16)srb->cmnd[4] << 8) | srb->cmnd[5];

	अगर (mode == 0) अणु
		retval = spi_erase_eeprom_chip(chip);
		अगर (retval != STATUS_SUCCESS) अणु
			set_sense_type(chip, SCSI_LUN(srb),
				       SENSE_TYPE_MEDIA_WRITE_ERR);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण अन्यथा अगर (mode == 1) अणु
		retval = spi_erase_eeprom_byte(chip, addr);
		अगर (retval != STATUS_SUCCESS) अणु
			set_sense_type(chip, SCSI_LUN(srb),
				       SENSE_TYPE_MEDIA_WRITE_ERR);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण अन्यथा अणु
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक पढ़ो_eeprom2(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित लघु addr, len, i;
	पूर्णांक retval;
	u8 *buf;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	addr = ((u16)srb->cmnd[4] << 8) | srb->cmnd[5];
	len = ((u16)srb->cmnd[6] << 8) | srb->cmnd[7];

	buf = vदो_स्मृति(len);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
	अगर (retval != STATUS_SUCCESS) अणु
		vमुक्त(buf);
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
		वापस TRANSPORT_FAILED;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		retval = spi_पढ़ो_eeprom(chip, addr + i, buf + i);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(buf);
			set_sense_type(chip, SCSI_LUN(srb),
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण

	len = (अचिन्हित लघु)min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), len);
	rtsx_stor_set_xfer_buf(buf, len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - len);

	vमुक्त(buf);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ग_लिखो_eeprom2(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित लघु addr, len, i;
	पूर्णांक retval;
	u8 *buf;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	addr = ((u16)srb->cmnd[4] << 8) | srb->cmnd[5];
	len = ((u16)srb->cmnd[6] << 8) | srb->cmnd[7];

	len = (अचिन्हित लघु)min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), len);
	buf = vदो_स्मृति(len);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	rtsx_stor_get_xfer_buf(buf, len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - len);

	retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
	अगर (retval != STATUS_SUCCESS) अणु
		vमुक्त(buf);
		set_sense_type(chip, SCSI_LUN(srb), SENSE_TYPE_MEDIA_WRITE_ERR);
		वापस TRANSPORT_FAILED;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		retval = spi_ग_लिखो_eeprom(chip, addr + i, buf[i]);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(buf);
			set_sense_type(chip, SCSI_LUN(srb),
				       SENSE_TYPE_MEDIA_WRITE_ERR);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण

	vमुक्त(buf);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक पढ़ो_efuse(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	u8 addr, len, i;
	u8 *buf;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	addr = srb->cmnd[4];
	len = srb->cmnd[5];

	buf = vदो_स्मृति(len);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
	अगर (retval != STATUS_SUCCESS) अणु
		vमुक्त(buf);
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
		वापस TRANSPORT_FAILED;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		retval = rtsx_पढ़ो_efuse(chip, addr + i, buf + i);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(buf);
			set_sense_type(chip, SCSI_LUN(srb),
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण

	len = (u8)min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), len);
	rtsx_stor_set_xfer_buf(buf, len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - len);

	vमुक्त(buf);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ग_लिखो_efuse(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval, result = TRANSPORT_GOOD;
	u16 val;
	u8 addr, len, i;
	u8 *buf;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	addr = srb->cmnd[4];
	len = srb->cmnd[5];

	len = (u8)min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), len);
	buf = vदो_स्मृति(len);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	rtsx_stor_get_xfer_buf(buf, len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - len);

	retval = rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);
	अगर (retval != STATUS_SUCCESS) अणु
		vमुक्त(buf);
		वापस TRANSPORT_ERROR;
	पूर्ण

	अगर (chip->asic_code) अणु
		retval = rtsx_पढ़ो_phy_रेजिस्टर(chip, 0x08, &val);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(buf);
			वापस TRANSPORT_ERROR;
		पूर्ण

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, PWR_GATE_CTRL,
					     LDO3318_PWR_MASK, LDO_OFF);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(buf);
			वापस TRANSPORT_ERROR;
		पूर्ण

		रुको_समयout(600);

		retval = rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x08,
						 0x4C00 | chip->phy_voltage);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(buf);
			वापस TRANSPORT_ERROR;
		पूर्ण

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, PWR_GATE_CTRL,
					     LDO3318_PWR_MASK, LDO_ON);
		अगर (retval != STATUS_SUCCESS) अणु
			vमुक्त(buf);
			वापस TRANSPORT_ERROR;
		पूर्ण

		रुको_समयout(600);
	पूर्ण

	retval = card_घातer_on(chip, SPI_CARD);
	अगर (retval != STATUS_SUCCESS) अणु
		vमुक्त(buf);
		वापस TRANSPORT_ERROR;
	पूर्ण

	रुको_समयout(50);

	क्रम (i = 0; i < len; i++) अणु
		retval = rtsx_ग_लिखो_efuse(chip, addr + i, buf[i]);
		अगर (retval != STATUS_SUCCESS) अणु
			set_sense_type(chip, SCSI_LUN(srb),
				       SENSE_TYPE_MEDIA_WRITE_ERR);
			result = TRANSPORT_FAILED;
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	vमुक्त(buf);

	retval = card_घातer_off(chip, SPI_CARD);
	अगर (retval != STATUS_SUCCESS)
		वापस TRANSPORT_ERROR;

	अगर (chip->asic_code) अणु
		retval = rtsx_ग_लिखो_रेजिस्टर(chip, PWR_GATE_CTRL,
					     LDO3318_PWR_MASK, LDO_OFF);
		अगर (retval != STATUS_SUCCESS)
			वापस TRANSPORT_ERROR;

		रुको_समयout(600);

		retval = rtsx_ग_लिखो_phy_रेजिस्टर(chip, 0x08, val);
		अगर (retval != STATUS_SUCCESS)
			वापस TRANSPORT_ERROR;

		retval = rtsx_ग_लिखो_रेजिस्टर(chip, PWR_GATE_CTRL,
					     LDO3318_PWR_MASK, LDO_ON);
		अगर (retval != STATUS_SUCCESS)
			वापस TRANSPORT_ERROR;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक पढ़ो_cfg_byte(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	bool func_max;
	u8 func;
	u16 addr, len;
	u8 *buf;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	func = srb->cmnd[3];
	addr = ((u16)(srb->cmnd[4]) << 8) | srb->cmnd[5];
	len = ((u16)(srb->cmnd[6]) << 8) | srb->cmnd[7];

	dev_dbg(rtsx_dev(chip), "%s: func = %d, addr = 0x%x, len = %d\n",
		__func__, func, addr, len);

	अगर (CHK_SDIO_EXIST(chip) && !CHK_SDIO_IGNORED(chip))
		func_max = true;
	अन्यथा
		func_max = false;

	अगर (func > func_max) अणु
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	buf = vदो_स्मृति(len);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	retval = rtsx_पढ़ो_cfg_seq(chip, func, addr, buf, len);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
		vमुक्त(buf);
		वापस TRANSPORT_FAILED;
	पूर्ण

	len = (u16)min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), len);
	rtsx_stor_set_xfer_buf(buf, len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - len);

	vमुक्त(buf);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक ग_लिखो_cfg_byte(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval;
	bool func_max;
	u8 func;
	u16 addr, len;
	u8 *buf;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	func = srb->cmnd[3];
	addr = ((u16)(srb->cmnd[4]) << 8) | srb->cmnd[5];
	len = ((u16)(srb->cmnd[6]) << 8) | srb->cmnd[7];

	dev_dbg(rtsx_dev(chip), "%s: func = %d, addr = 0x%x\n",
		__func__, func, addr);

	अगर (CHK_SDIO_EXIST(chip) && !CHK_SDIO_IGNORED(chip))
		func_max = true;
	अन्यथा
		func_max = false;

	अगर (func > func_max) अणु
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	len = (अचिन्हित लघु)min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), len);
	buf = vदो_स्मृति(len);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	rtsx_stor_get_xfer_buf(buf, len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - len);

	retval = rtsx_ग_लिखो_cfg_seq(chip, func, addr, buf, len);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, SCSI_LUN(srb), SENSE_TYPE_MEDIA_WRITE_ERR);
		vमुक्त(buf);
		वापस TRANSPORT_FAILED;
	पूर्ण

	vमुक्त(buf);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक app_cmd(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक result;

	चयन (srb->cmnd[2]) अणु
	हाल PP_READ10:
	हाल PP_WRITE10:
		result = पढ़ो_ग_लिखो(srb, chip);
		अवरोध;

	हाल READ_HOST_REG:
		result = पढ़ो_host_reg(srb, chip);
		अवरोध;

	हाल WRITE_HOST_REG:
		result = ग_लिखो_host_reg(srb, chip);
		अवरोध;

	हाल GET_VAR:
		result = get_variable(srb, chip);
		अवरोध;

	हाल SET_VAR:
		result = set_variable(srb, chip);
		अवरोध;

	हाल DMA_READ:
	हाल DMA_WRITE:
		result = dma_access_ring_buffer(srb, chip);
		अवरोध;

	हाल READ_PHY:
		result = पढ़ो_phy_रेजिस्टर(srb, chip);
		अवरोध;

	हाल WRITE_PHY:
		result = ग_लिखो_phy_रेजिस्टर(srb, chip);
		अवरोध;

	हाल ERASE_EEPROM2:
		result = erase_eeprom2(srb, chip);
		अवरोध;

	हाल READ_EEPROM2:
		result = पढ़ो_eeprom2(srb, chip);
		अवरोध;

	हाल WRITE_EEPROM2:
		result = ग_लिखो_eeprom2(srb, chip);
		अवरोध;

	हाल READ_EFUSE:
		result = पढ़ो_efuse(srb, chip);
		अवरोध;

	हाल WRITE_EFUSE:
		result = ग_लिखो_efuse(srb, chip);
		अवरोध;

	हाल READ_CFG:
		result = पढ़ो_cfg_byte(srb, chip);
		अवरोध;

	हाल WRITE_CFG:
		result = ग_लिखो_cfg_byte(srb, chip);
		अवरोध;

	हाल SET_CHIP_MODE:
		result = set_chip_mode(srb, chip);
		अवरोध;

	हाल SUIT_CMD:
		result = suit_cmd(srb, chip);
		अवरोध;

	हाल GET_DEV_STATUS:
		result = get_dev_status(srb, chip);
		अवरोध;

	शेष:
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक पढ़ो_status(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	u8 rtsx_status[16];
	पूर्णांक buf_len;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);

	rtsx_status[0] = (u8)(chip->venकरोr_id >> 8);
	rtsx_status[1] = (u8)(chip->venकरोr_id);

	rtsx_status[2] = (u8)(chip->product_id >> 8);
	rtsx_status[3] = (u8)(chip->product_id);

	rtsx_status[4] = (u8)lun;

	अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN)) अणु
		अगर (chip->lun2card[lun] == SD_CARD)
			rtsx_status[5] = 2;
		अन्यथा
			rtsx_status[5] = 3;
	पूर्ण अन्यथा अणु
		अगर (chip->card_exist) अणु
			अगर (chip->card_exist & XD_CARD)
				rtsx_status[5] = 4;
			अन्यथा अगर (chip->card_exist & SD_CARD)
				rtsx_status[5] = 2;
			अन्यथा अगर (chip->card_exist & MS_CARD)
				rtsx_status[5] = 3;
			अन्यथा
				rtsx_status[5] = 7;
		पूर्ण अन्यथा अणु
			rtsx_status[5] = 7;
		पूर्ण
	पूर्ण

	अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN))
		rtsx_status[6] = 2;
	अन्यथा
		rtsx_status[6] = 1;

	rtsx_status[7] = (u8)(chip->product_id);
	rtsx_status[8] = chip->ic_version;

	अगर (check_card_exist(chip, lun))
		rtsx_status[9] = 1;
	अन्यथा
		rtsx_status[9] = 0;

	अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN))
		rtsx_status[10] = 0;
	अन्यथा
		rtsx_status[10] = 1;

	अगर (CHECK_LUN_MODE(chip, SD_MS_2LUN)) अणु
		अगर (chip->lun2card[lun] == SD_CARD)
			rtsx_status[11] = SD_CARD;
		अन्यथा
			rtsx_status[11] = MS_CARD;
	पूर्ण अन्यथा अणु
		rtsx_status[11] = XD_CARD | SD_CARD | MS_CARD;
	पूर्ण

	अगर (check_card_पढ़ोy(chip, lun))
		rtsx_status[12] = 1;
	अन्यथा
		rtsx_status[12] = 0;

	अगर (get_lun_card(chip, lun) == XD_CARD) अणु
		rtsx_status[13] = 0x40;
	पूर्ण अन्यथा अगर (get_lun_card(chip, lun) == SD_CARD) अणु
		काष्ठा sd_info *sd_card = &chip->sd_card;

		rtsx_status[13] = 0x20;
		अगर (CHK_SD(sd_card)) अणु
			अगर (CHK_SD_HCXC(sd_card))
				rtsx_status[13] |= 0x04;
			अगर (CHK_SD_HS(sd_card))
				rtsx_status[13] |= 0x02;
		पूर्ण अन्यथा अणु
			rtsx_status[13] |= 0x08;
			अगर (CHK_MMC_52M(sd_card))
				rtsx_status[13] |= 0x02;
			अगर (CHK_MMC_SECTOR_MODE(sd_card))
				rtsx_status[13] |= 0x04;
		पूर्ण
	पूर्ण अन्यथा अगर (get_lun_card(chip, lun) == MS_CARD) अणु
		काष्ठा ms_info *ms_card = &chip->ms_card;

		अगर (CHK_MSPRO(ms_card)) अणु
			rtsx_status[13] = 0x38;
			अगर (CHK_HG8BIT(ms_card))
				rtsx_status[13] |= 0x04;
#अगर_घोषित SUPPORT_MSXC
			अगर (CHK_MSXC(ms_card))
				rtsx_status[13] |= 0x01;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			rtsx_status[13] = 0x30;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (CHECK_LUN_MODE(chip, DEFAULT_SINGLE)) अणु
#अगर_घोषित SUPPORT_SDIO
			अगर (chip->sd_io && chip->sd_पूर्णांक)
				rtsx_status[13] = 0x60;
			अन्यथा
				rtsx_status[13] = 0x70;
#अन्यथा
			rtsx_status[13] = 0x70;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			अगर (chip->lun2card[lun] == SD_CARD)
				rtsx_status[13] = 0x20;
			अन्यथा
				rtsx_status[13] = 0x30;
		पूर्ण
	पूर्ण

	rtsx_status[14] = 0x78;
	अगर (CHK_SDIO_EXIST(chip) && !CHK_SDIO_IGNORED(chip))
		rtsx_status[15] = 0x83;
	अन्यथा
		rtsx_status[15] = 0x82;

	buf_len = min_t(अचिन्हित पूर्णांक, scsi_bufflen(srb), माप(rtsx_status));
	rtsx_stor_set_xfer_buf(rtsx_status, buf_len, srb);
	scsi_set_resid(srb, scsi_bufflen(srb) - buf_len);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक get_card_bus_width(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u8 card, bus_width;

	अगर (!check_card_पढ़ोy(chip, lun)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	card = get_lun_card(chip, lun);
	अगर ((card == SD_CARD) || (card == MS_CARD)) अणु
		bus_width = chip->card_bus_width[lun];
	पूर्ण अन्यथा अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
		वापस TRANSPORT_FAILED;
	पूर्ण

	scsi_set_resid(srb, 0);
	rtsx_stor_set_xfer_buf(&bus_width, scsi_bufflen(srb), srb);

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक spi_venकरोr_cmd(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक result;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u8 gpio_dir;

	अगर (CHECK_PID(chip, 0x5208) || CHECK_PID(chip, 0x5288)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	rtsx_क्रमce_घातer_on(chip, SSC_PDCTL);

	rtsx_पढ़ो_रेजिस्टर(chip, CARD_GPIO_सूची, &gpio_dir);
	rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO_सूची, 0x07, gpio_dir & 0x06);

	चयन (srb->cmnd[2]) अणु
	हाल SCSI_SPI_GETSTATUS:
		result = spi_get_status(srb, chip);
		अवरोध;

	हाल SCSI_SPI_SETPARAMETER:
		result = spi_set_parameter(srb, chip);
		अवरोध;

	हाल SCSI_SPI_READFALSHID:
		result = spi_पढ़ो_flash_id(srb, chip);
		अवरोध;

	हाल SCSI_SPI_READFLASH:
		result = spi_पढ़ो_flash(srb, chip);
		अवरोध;

	हाल SCSI_SPI_WRITEFLASH:
		result = spi_ग_लिखो_flash(srb, chip);
		अवरोध;

	हाल SCSI_SPI_WRITEFLASHSTATUS:
		result = spi_ग_लिखो_flash_status(srb, chip);
		अवरोध;

	हाल SCSI_SPI_ERASEFLASH:
		result = spi_erase_flash(srb, chip);
		अवरोध;

	शेष:
		rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO_सूची, 0x07, gpio_dir);

		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	rtsx_ग_लिखो_रेजिस्टर(chip, CARD_GPIO_सूची, 0x07, gpio_dir);

	अगर (result != STATUS_SUCCESS)
		वापस TRANSPORT_FAILED;

	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक venकरोr_cmnd(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक result;

	चयन (srb->cmnd[1]) अणु
	हाल READ_STATUS:
		result = पढ़ो_status(srb, chip);
		अवरोध;

	हाल READ_MEM:
		result = पढ़ो_mem(srb, chip);
		अवरोध;

	हाल WRITE_MEM:
		result = ग_लिखो_mem(srb, chip);
		अवरोध;

	हाल READ_EEPROM:
		result = पढ़ो_eeprom(srb, chip);
		अवरोध;

	हाल WRITE_EEPROM:
		result = ग_लिखो_eeprom(srb, chip);
		अवरोध;

	हाल TOGGLE_GPIO:
		result = toggle_gpio_cmd(srb, chip);
		अवरोध;

	हाल GET_SD_CSD:
		result = get_sd_csd(srb, chip);
		अवरोध;

	हाल GET_BUS_WIDTH:
		result = get_card_bus_width(srb, chip);
		अवरोध;

	हाल SCSI_APP_CMD:
		result = app_cmd(srb, chip);
		अवरोध;

	हाल SPI_VENDOR_COMMAND:
		result = spi_venकरोr_cmd(srb, chip);
		अवरोध;

	शेष:
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	वापस result;
पूर्ण

#अगर !defined(LED_AUTO_BLINK) && !defined(REGULAR_BLINK)
व्योम led_shine(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u16 sec_cnt;

	अगर ((srb->cmnd[0] == READ_10) || (srb->cmnd[0] == WRITE_10)) अणु
		sec_cnt = ((u16)(srb->cmnd[7]) << 8) | srb->cmnd[8];
	पूर्ण अन्यथा अगर ((srb->cmnd[0] == READ_6) || (srb->cmnd[0] == WRITE_6)) अणु
		sec_cnt = srb->cmnd[4];
		अगर (sec_cnt == 0)
			sec_cnt = 256;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	अगर (chip->rw_cap[lun] >= GPIO_TOGGLE_THRESHOLD) अणु
		toggle_gpio(chip, LED_GPIO);
		chip->rw_cap[lun] = 0;
	पूर्ण अन्यथा अणु
		chip->rw_cap[lun] += sec_cnt;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ms_क्रमmat_cmnd(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	bool quick_क्रमmat;
	पूर्णांक retval;

	अगर (get_lun_card(chip, lun) != MS_CARD) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर ((srb->cmnd[3] != 0x4D) || (srb->cmnd[4] != 0x47) ||
	    (srb->cmnd[5] != 0x66) || (srb->cmnd[6] != 0x6D) ||
		(srb->cmnd[7] != 0x74)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);

		अगर (!check_card_पढ़ोy(chip, lun) ||
		    (get_card_size(chip, lun) == 0)) अणु
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	अगर (srb->cmnd[8] & 0x01)
		quick_क्रमmat = false;
	अन्यथा
		quick_क्रमmat = true;

	अगर (!(chip->card_पढ़ोy & MS_CARD)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (chip->card_wp & MS_CARD) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_WRITE_PROTECT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (!CHK_MSPRO(ms_card)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	retval = mspro_क्रमmat(srb, chip, MS_SHORT_DATA_LEN, quick_क्रमmat);
	अगर (retval != STATUS_SUCCESS) अणु
		set_sense_type(chip, lun, SENSE_TYPE_FORMAT_CMD_FAILED);
		वापस TRANSPORT_FAILED;
	पूर्ण

	scsi_set_resid(srb, 0);
	वापस TRANSPORT_GOOD;
पूर्ण

#अगर_घोषित SUPPORT_PCGL_1P18
अटल पूर्णांक get_ms_inक्रमmation(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	u8 dev_info_id, data_len;
	u8 *buf;
	अचिन्हित पूर्णांक buf_len;
	पूर्णांक i;

	अगर (!check_card_पढ़ोy(chip, lun)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		वापस TRANSPORT_FAILED;
	पूर्ण
	अगर (get_lun_card(chip, lun) != MS_CARD) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर ((srb->cmnd[2] != 0xB0) || (srb->cmnd[4] != 0x4D) ||
	    (srb->cmnd[5] != 0x53) || (srb->cmnd[6] != 0x49) ||
	    (srb->cmnd[7] != 0x44)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	dev_info_id = srb->cmnd[3];
	अगर ((CHK_MSXC(ms_card) && (dev_info_id == 0x10)) ||
	    (!CHK_MSXC(ms_card) && (dev_info_id == 0x13)) ||
	    !CHK_MSPRO(ms_card)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (dev_info_id == 0x15) अणु
		buf_len = 0x3A;
		data_len = 0x3A;
	पूर्ण अन्यथा अणु
		buf_len = 0x6A;
		data_len = 0x6A;
	पूर्ण

	buf = kदो_स्मृति(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस TRANSPORT_ERROR;

	i = 0;
	/*  GET Memory Stick Media Inक्रमmation Response Header */
	buf[i++] = 0x00;		/* Data length MSB */
	buf[i++] = data_len;		/* Data length LSB */
	/* Device Inक्रमmation Type Code */
	अगर (CHK_MSXC(ms_card))
		buf[i++] = 0x03;
	अन्यथा
		buf[i++] = 0x02;

	/* SGM bit */
	buf[i++] = 0x01;
	/* Reserved */
	buf[i++] = 0x00;
	buf[i++] = 0x00;
	buf[i++] = 0x00;
	/* Number of Device Inक्रमmation */
	buf[i++] = 0x01;

	/*  Device Inक्रमmation Body */

	/* Device Inक्रमmation ID Number */
	buf[i++] = dev_info_id;
	/* Device Inक्रमmation Length */
	अगर (dev_info_id == 0x15)
		data_len = 0x31;
	अन्यथा
		data_len = 0x61;

	buf[i++] = 0x00;		/* Data length MSB */
	buf[i++] = data_len;		/* Data length LSB */
	/* Valid Bit */
	buf[i++] = 0x80;
	अगर ((dev_info_id == 0x10) || (dev_info_id == 0x13)) अणु
		/* System Inक्रमmation */
		स_नकल(buf + i, ms_card->raw_sys_info, 96);
	पूर्ण अन्यथा अणु
		/* Model Name */
		स_नकल(buf + i, ms_card->raw_model_name, 48);
	पूर्ण

	rtsx_stor_set_xfer_buf(buf, buf_len, srb);

	अगर (dev_info_id == 0x15)
		scsi_set_resid(srb, scsi_bufflen(srb) - 0x3C);
	अन्यथा
		scsi_set_resid(srb, scsi_bufflen(srb) - 0x6C);

	kमुक्त(buf);
	वापस STATUS_SUCCESS;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ms_sp_cmnd(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	पूर्णांक retval = TRANSPORT_ERROR;

	अगर (srb->cmnd[2] == MS_FORMAT)
		retval = ms_क्रमmat_cmnd(srb, chip);
#अगर_घोषित SUPPORT_PCGL_1P18
	अन्यथा अगर (srb->cmnd[2] == GET_MS_INFORMATION)
		retval = get_ms_inक्रमmation(srb, chip);
#पूर्ण_अगर

	वापस retval;
पूर्ण

#अगर_घोषित SUPPORT_CPRM
अटल पूर्णांक sd_extension_cmnd(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक result;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	sd_cleanup_work(chip);

	अगर (!check_card_पढ़ोy(chip, lun)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		वापस TRANSPORT_FAILED;
	पूर्ण
	अगर (get_lun_card(chip, lun) != SD_CARD) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	चयन (srb->cmnd[0]) अणु
	हाल SD_PASS_THRU_MODE:
		result = sd_pass_thru_mode(srb, chip);
		अवरोध;

	हाल SD_EXECUTE_NO_DATA:
		result = sd_execute_no_data(srb, chip);
		अवरोध;

	हाल SD_EXECUTE_READ:
		result = sd_execute_पढ़ो_data(srb, chip);
		अवरोध;

	हाल SD_EXECUTE_WRITE:
		result = sd_execute_ग_लिखो_data(srb, chip);
		अवरोध;

	हाल SD_GET_RSP:
		result = sd_get_cmd_rsp(srb, chip);
		अवरोध;

	हाल SD_HW_RST:
		result = sd_hw_rst(srb, chip);
		अवरोध;

	शेष:
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	वापस result;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित SUPPORT_MAGIC_GATE
अटल पूर्णांक mg_report_key(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक retval;
	u8 key_क्रमmat;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	ms_cleanup_work(chip);

	अगर (!check_card_पढ़ोy(chip, lun)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		वापस TRANSPORT_FAILED;
	पूर्ण
	अगर (get_lun_card(chip, lun) != MS_CARD) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (srb->cmnd[7] != KC_MG_R_PRO) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (!CHK_MSPRO(ms_card)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		वापस TRANSPORT_FAILED;
	पूर्ण

	key_क्रमmat = srb->cmnd[10] & 0x3F;
	dev_dbg(rtsx_dev(chip), "key_format = 0x%x\n", key_क्रमmat);

	चयन (key_क्रमmat) अणु
	हाल KF_GET_LOC_EKB:
		अगर ((scsi_bufflen(srb) == 0x41C) &&
		    (srb->cmnd[8] == 0x04) &&
		    (srb->cmnd[9] == 0x1C)) अणु
			retval = mg_get_local_EKB(srb, chip);
			अगर (retval != STATUS_SUCCESS)
				वापस TRANSPORT_FAILED;

		पूर्ण अन्यथा अणु
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			वापस TRANSPORT_FAILED;
		पूर्ण
		अवरोध;

	हाल KF_RSP_CHG:
		अगर ((scsi_bufflen(srb) == 0x24) &&
		    (srb->cmnd[8] == 0x00) &&
		    (srb->cmnd[9] == 0x24)) अणु
			retval = mg_get_rsp_chg(srb, chip);
			अगर (retval != STATUS_SUCCESS)
				वापस TRANSPORT_FAILED;

		पूर्ण अन्यथा अणु
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			वापस TRANSPORT_FAILED;
		पूर्ण
		अवरोध;

	हाल KF_GET_ICV:
		ms_card->mg_entry_num = srb->cmnd[5];
		अगर ((scsi_bufflen(srb) == 0x404) &&
		    (srb->cmnd[8] == 0x04) &&
		    (srb->cmnd[9] == 0x04) &&
		    (srb->cmnd[2] == 0x00) &&
		    (srb->cmnd[3] == 0x00) &&
		    (srb->cmnd[4] == 0x00) &&
		    (srb->cmnd[5] < 32)) अणु
			retval = mg_get_ICV(srb, chip);
			अगर (retval != STATUS_SUCCESS)
				वापस TRANSPORT_FAILED;

		पूर्ण अन्यथा अणु
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			वापस TRANSPORT_FAILED;
		पूर्ण
		अवरोध;

	शेष:
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	scsi_set_resid(srb, 0);
	वापस TRANSPORT_GOOD;
पूर्ण

अटल पूर्णांक mg_send_key(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
	काष्ठा ms_info *ms_card = &chip->ms_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक retval;
	u8 key_क्रमmat;

	rtsx_disable_aspm(chip);

	अगर (chip->ss_en && (rtsx_get_stat(chip) == RTSX_STAT_SS)) अणु
		rtsx_निकास_ss(chip);
		रुको_समयout(100);
	पूर्ण
	rtsx_set_stat(chip, RTSX_STAT_RUN);

	ms_cleanup_work(chip);

	अगर (!check_card_पढ़ोy(chip, lun)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		वापस TRANSPORT_FAILED;
	पूर्ण
	अगर (check_card_wp(chip, lun)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_WRITE_PROTECT);
		वापस TRANSPORT_FAILED;
	पूर्ण
	अगर (get_lun_card(chip, lun) != MS_CARD) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (srb->cmnd[7] != KC_MG_R_PRO) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	अगर (!CHK_MSPRO(ms_card)) अणु
		set_sense_type(chip, lun, SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM);
		वापस TRANSPORT_FAILED;
	पूर्ण

	key_क्रमmat = srb->cmnd[10] & 0x3F;
	dev_dbg(rtsx_dev(chip), "key_format = 0x%x\n", key_क्रमmat);

	चयन (key_क्रमmat) अणु
	हाल KF_SET_LEAF_ID:
		अगर ((scsi_bufflen(srb) == 0x0C) &&
		    (srb->cmnd[8] == 0x00) &&
		    (srb->cmnd[9] == 0x0C)) अणु
			retval = mg_set_leaf_id(srb, chip);
			अगर (retval != STATUS_SUCCESS)
				वापस TRANSPORT_FAILED;

		पूर्ण अन्यथा अणु
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			वापस TRANSPORT_FAILED;
		पूर्ण
		अवरोध;

	हाल KF_CHG_HOST:
		अगर ((scsi_bufflen(srb) == 0x0C) &&
		    (srb->cmnd[8] == 0x00) &&
		    (srb->cmnd[9] == 0x0C)) अणु
			retval = mg_chg(srb, chip);
			अगर (retval != STATUS_SUCCESS)
				वापस TRANSPORT_FAILED;

		पूर्ण अन्यथा अणु
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			वापस TRANSPORT_FAILED;
		पूर्ण
		अवरोध;

	हाल KF_RSP_HOST:
		अगर ((scsi_bufflen(srb) == 0x0C) &&
		    (srb->cmnd[8] == 0x00) &&
		    (srb->cmnd[9] == 0x0C)) अणु
			retval = mg_rsp(srb, chip);
			अगर (retval != STATUS_SUCCESS)
				वापस TRANSPORT_FAILED;

		पूर्ण अन्यथा अणु
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			वापस TRANSPORT_FAILED;
		पूर्ण
		अवरोध;

	हाल KF_SET_ICV:
		ms_card->mg_entry_num = srb->cmnd[5];
		अगर ((scsi_bufflen(srb) == 0x404) &&
		    (srb->cmnd[8] == 0x04) &&
		    (srb->cmnd[9] == 0x04) &&
		    (srb->cmnd[2] == 0x00) &&
		    (srb->cmnd[3] == 0x00) &&
		    (srb->cmnd[4] == 0x00) &&
		    (srb->cmnd[5] < 32)) अणु
			retval = mg_set_ICV(srb, chip);
			अगर (retval != STATUS_SUCCESS)
				वापस TRANSPORT_FAILED;

		पूर्ण अन्यथा अणु
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
			वापस TRANSPORT_FAILED;
		पूर्ण
		अवरोध;

	शेष:
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		वापस TRANSPORT_FAILED;
	पूर्ण

	scsi_set_resid(srb, 0);
	वापस TRANSPORT_GOOD;
पूर्ण
#पूर्ण_अगर

पूर्णांक rtsx_scsi_handler(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip)
अणु
#अगर_घोषित SUPPORT_SD_LOCK
	काष्ठा sd_info *sd_card = &chip->sd_card;
#पूर्ण_अगर
	काष्ठा ms_info *ms_card = &chip->ms_card;
	अचिन्हित पूर्णांक lun = SCSI_LUN(srb);
	पूर्णांक result;

#अगर_घोषित SUPPORT_SD_LOCK
	अगर (sd_card->sd_erase_status) अणु
		/* Block all SCSI command except क्रम
		 * REQUEST_SENSE and rs_ppstatus
		 */
		अगर (!((srb->cmnd[0] == VENDOR_CMND) &&
		      (srb->cmnd[1] == SCSI_APP_CMD) &&
		      (srb->cmnd[2] == GET_DEV_STATUS)) &&
		      (srb->cmnd[0] != REQUEST_SENSE)) अणु
			/* Logical Unit Not Ready Format in Progress */
			set_sense_data(chip, lun, CUR_ERR,
				       0x02, 0, 0x04, 0x04, 0, 0);
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर ((get_lun_card(chip, lun) == MS_CARD) &&
	    (ms_card->क्रमmat_status == FORMAT_IN_PROGRESS)) अणु
		अगर ((srb->cmnd[0] != REQUEST_SENSE) &&
		    (srb->cmnd[0] != INQUIRY)) अणु
			/* Logical Unit Not Ready Format in Progress */
			set_sense_data(chip, lun, CUR_ERR, 0x02, 0, 0x04, 0x04,
				       0, (u16)(ms_card->progress));
			वापस TRANSPORT_FAILED;
		पूर्ण
	पूर्ण

	चयन (srb->cmnd[0]) अणु
	हाल READ_10:
	हाल WRITE_10:
	हाल READ_6:
	हाल WRITE_6:
		result = पढ़ो_ग_लिखो(srb, chip);
#अगर !defined(LED_AUTO_BLINK) && !defined(REGULAR_BLINK)
		led_shine(srb, chip);
#पूर्ण_अगर
		अवरोध;

	हाल TEST_UNIT_READY:
		result = test_unit_पढ़ोy(srb, chip);
		अवरोध;

	हाल INQUIRY:
		result = inquiry(srb, chip);
		अवरोध;

	हाल READ_CAPACITY:
		result = पढ़ो_capacity(srb, chip);
		अवरोध;

	हाल START_STOP:
		result = start_stop_unit(srb, chip);
		अवरोध;

	हाल ALLOW_MEDIUM_REMOVAL:
		result = allow_medium_removal(srb, chip);
		अवरोध;

	हाल REQUEST_SENSE:
		result = request_sense(srb, chip);
		अवरोध;

	हाल MODE_SENSE:
	हाल MODE_SENSE_10:
		result = mode_sense(srb, chip);
		अवरोध;

	हाल 0x23:
		result = पढ़ो_क्रमmat_capacity(srb, chip);
		अवरोध;

	हाल VENDOR_CMND:
		result = venकरोr_cmnd(srb, chip);
		अवरोध;

	हाल MS_SP_CMND:
		result = ms_sp_cmnd(srb, chip);
		अवरोध;

#अगर_घोषित SUPPORT_CPRM
	हाल SD_PASS_THRU_MODE:
	हाल SD_EXECUTE_NO_DATA:
	हाल SD_EXECUTE_READ:
	हाल SD_EXECUTE_WRITE:
	हाल SD_GET_RSP:
	हाल SD_HW_RST:
		result = sd_extension_cmnd(srb, chip);
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित SUPPORT_MAGIC_GATE
	हाल CMD_MSPRO_MG_RKEY:
		result = mg_report_key(srb, chip);
		अवरोध;

	हाल CMD_MSPRO_MG_SKEY:
		result = mg_send_key(srb, chip);
		अवरोध;
#पूर्ण_अगर

	हाल FORMAT_UNIT:
	हाल MODE_SELECT:
	हाल VERIFY:
		result = TRANSPORT_GOOD;
		अवरोध;

	शेष:
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		result = TRANSPORT_FAILED;
	पूर्ण

	वापस result;
पूर्ण
