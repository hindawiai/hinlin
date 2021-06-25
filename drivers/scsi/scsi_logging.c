<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * scsi_logging.c
 *
 * Copyright (C) 2014 SUSE Linux Products GmbH
 * Copyright (C) 2014 Hannes Reinecke <hare@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/atomic.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_dbg.h>

अटल अक्षर *scsi_log_reserve_buffer(माप_प्रकार *len)
अणु
	*len = 128;
	वापस kदो_स्मृति(*len, GFP_ATOMIC);
पूर्ण

अटल व्योम scsi_log_release_buffer(अक्षर *bufptr)
अणु
	kमुक्त(bufptr);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *scmd_name(स्थिर काष्ठा scsi_cmnd *scmd)
अणु
	वापस scmd->request->rq_disk ?
		scmd->request->rq_disk->disk_name : शून्य;
पूर्ण

अटल माप_प्रकार sdev_क्रमmat_header(अक्षर *logbuf, माप_प्रकार logbuf_len,
				 स्थिर अक्षर *name, पूर्णांक tag)
अणु
	माप_प्रकार off = 0;

	अगर (name)
		off += scnम_लिखो(logbuf + off, logbuf_len - off,
				 "[%s] ", name);

	अगर (WARN_ON(off >= logbuf_len))
		वापस off;

	अगर (tag >= 0)
		off += scnम_लिखो(logbuf + off, logbuf_len - off,
				 "tag#%d ", tag);
	वापस off;
पूर्ण

व्योम sdev_prefix_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा scsi_device *sdev,
			स्थिर अक्षर *name, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर *logbuf;
	माप_प्रकार off = 0, logbuf_len;

	अगर (!sdev)
		वापस;

	logbuf = scsi_log_reserve_buffer(&logbuf_len);
	अगर (!logbuf)
		वापस;

	अगर (name)
		off += scnम_लिखो(logbuf + off, logbuf_len - off,
				 "[%s] ", name);
	अगर (!WARN_ON(off >= logbuf_len)) अणु
		बहु_शुरू(args, fmt);
		off += vscnम_लिखो(logbuf + off, logbuf_len - off, fmt, args);
		बहु_पूर्ण(args);
	पूर्ण
	dev_prपूर्णांकk(level, &sdev->sdev_gendev, "%s", logbuf);
	scsi_log_release_buffer(logbuf);
पूर्ण
EXPORT_SYMBOL(sdev_prefix_prपूर्णांकk);

व्योम scmd_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा scsi_cmnd *scmd,
		स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर *logbuf;
	माप_प्रकार off = 0, logbuf_len;

	अगर (!scmd || !scmd->cmnd)
		वापस;

	logbuf = scsi_log_reserve_buffer(&logbuf_len);
	अगर (!logbuf)
		वापस;
	off = sdev_क्रमmat_header(logbuf, logbuf_len, scmd_name(scmd),
				 scmd->request->tag);
	अगर (off < logbuf_len) अणु
		बहु_शुरू(args, fmt);
		off += vscnम_लिखो(logbuf + off, logbuf_len - off, fmt, args);
		बहु_पूर्ण(args);
	पूर्ण
	dev_prपूर्णांकk(level, &scmd->device->sdev_gendev, "%s", logbuf);
	scsi_log_release_buffer(logbuf);
पूर्ण
EXPORT_SYMBOL(scmd_prपूर्णांकk);

अटल माप_प्रकार scsi_क्रमmat_opcode_name(अक्षर *buffer, माप_प्रकार buf_len,
				      स्थिर अचिन्हित अक्षर *cdbp)
अणु
	पूर्णांक sa, cdb0;
	स्थिर अक्षर *cdb_name = शून्य, *sa_name = शून्य;
	माप_प्रकार off;

	cdb0 = cdbp[0];
	अगर (cdb0 == VARIABLE_LENGTH_CMD) अणु
		पूर्णांक len = scsi_varlen_cdb_length(cdbp);

		अगर (len < 10) अणु
			off = scnम_लिखो(buffer, buf_len,
					"short variable length command, len=%d",
					len);
			वापस off;
		पूर्ण
		sa = (cdbp[8] << 8) + cdbp[9];
	पूर्ण अन्यथा
		sa = cdbp[1] & 0x1f;

	अगर (!scsi_opcode_sa_name(cdb0, sa, &cdb_name, &sa_name)) अणु
		अगर (cdb_name)
			off = scnम_लिखो(buffer, buf_len, "%s", cdb_name);
		अन्यथा अणु
			off = scnम_लिखो(buffer, buf_len, "opcode=0x%x", cdb0);
			अगर (WARN_ON(off >= buf_len))
				वापस off;
			अगर (cdb0 >= VENDOR_SPECIFIC_CDB)
				off += scnम_लिखो(buffer + off, buf_len - off,
						 " (vendor)");
			अन्यथा अगर (cdb0 >= 0x60 && cdb0 < 0x7e)
				off += scnम_लिखो(buffer + off, buf_len - off,
						 " (reserved)");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (sa_name)
			off = scnम_लिखो(buffer, buf_len, "%s", sa_name);
		अन्यथा अगर (cdb_name)
			off = scnम_लिखो(buffer, buf_len, "%s, sa=0x%x",
					cdb_name, sa);
		अन्यथा
			off = scnम_लिखो(buffer, buf_len,
					"opcode=0x%x, sa=0x%x", cdb0, sa);
	पूर्ण
	WARN_ON(off >= buf_len);
	वापस off;
पूर्ण

माप_प्रकार __scsi_क्रमmat_command(अक्षर *logbuf, माप_प्रकार logbuf_len,
			     स्थिर अचिन्हित अक्षर *cdb, माप_प्रकार cdb_len)
अणु
	पूर्णांक len, k;
	माप_प्रकार off;

	off = scsi_क्रमmat_opcode_name(logbuf, logbuf_len, cdb);
	अगर (off >= logbuf_len)
		वापस off;
	len = scsi_command_size(cdb);
	अगर (cdb_len < len)
		len = cdb_len;
	/* prपूर्णांक out all bytes in cdb */
	क्रम (k = 0; k < len; ++k) अणु
		अगर (off > logbuf_len - 3)
			अवरोध;
		off += scnम_लिखो(logbuf + off, logbuf_len - off,
				 " %02x", cdb[k]);
	पूर्ण
	वापस off;
पूर्ण
EXPORT_SYMBOL(__scsi_क्रमmat_command);

व्योम scsi_prपूर्णांक_command(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक k;
	अक्षर *logbuf;
	माप_प्रकार off, logbuf_len;

	अगर (!cmd->cmnd)
		वापस;

	logbuf = scsi_log_reserve_buffer(&logbuf_len);
	अगर (!logbuf)
		वापस;

	off = sdev_क्रमmat_header(logbuf, logbuf_len,
				 scmd_name(cmd), cmd->request->tag);
	अगर (off >= logbuf_len)
		जाओ out_prपूर्णांकk;
	off += scnम_लिखो(logbuf + off, logbuf_len - off, "CDB: ");
	अगर (WARN_ON(off >= logbuf_len))
		जाओ out_prपूर्णांकk;

	off += scsi_क्रमmat_opcode_name(logbuf + off, logbuf_len - off,
				       cmd->cmnd);
	अगर (off >= logbuf_len)
		जाओ out_prपूर्णांकk;

	/* prपूर्णांक out all bytes in cdb */
	अगर (cmd->cmd_len > 16) अणु
		/* Prपूर्णांक opcode in one line and use separate lines क्रम CDB */
		off += scnम_लिखो(logbuf + off, logbuf_len - off, "\n");
		dev_prपूर्णांकk(KERN_INFO, &cmd->device->sdev_gendev, "%s", logbuf);
		क्रम (k = 0; k < cmd->cmd_len; k += 16) अणु
			माप_प्रकार linelen = min(cmd->cmd_len - k, 16);

			off = sdev_क्रमmat_header(logbuf, logbuf_len,
						 scmd_name(cmd),
						 cmd->request->tag);
			अगर (!WARN_ON(off > logbuf_len - 58)) अणु
				off += scnम_लिखो(logbuf + off, logbuf_len - off,
						 "CDB[%02x]: ", k);
				hex_dump_to_buffer(&cmd->cmnd[k], linelen,
						   16, 1, logbuf + off,
						   logbuf_len - off, false);
			पूर्ण
			dev_prपूर्णांकk(KERN_INFO, &cmd->device->sdev_gendev, "%s",
				   logbuf);
		पूर्ण
		जाओ out;
	पूर्ण
	अगर (!WARN_ON(off > logbuf_len - 49)) अणु
		off += scnम_लिखो(logbuf + off, logbuf_len - off, " ");
		hex_dump_to_buffer(cmd->cmnd, cmd->cmd_len, 16, 1,
				   logbuf + off, logbuf_len - off,
				   false);
	पूर्ण
out_prपूर्णांकk:
	dev_prपूर्णांकk(KERN_INFO, &cmd->device->sdev_gendev, "%s", logbuf);
out:
	scsi_log_release_buffer(logbuf);
पूर्ण
EXPORT_SYMBOL(scsi_prपूर्णांक_command);

अटल माप_प्रकार
scsi_क्रमmat_extd_sense(अक्षर *buffer, माप_प्रकार buf_len,
		       अचिन्हित अक्षर asc, अचिन्हित अक्षर ascq)
अणु
	माप_प्रकार off = 0;
	स्थिर अक्षर *extd_sense_fmt = शून्य;
	स्थिर अक्षर *extd_sense_str = scsi_extd_sense_क्रमmat(asc, ascq,
							    &extd_sense_fmt);

	अगर (extd_sense_str) अणु
		off = scnम_लिखो(buffer, buf_len, "Add. Sense: %s",
				extd_sense_str);
		अगर (extd_sense_fmt)
			off += scnम_लिखो(buffer + off, buf_len - off,
					 "(%s%x)", extd_sense_fmt, ascq);
	पूर्ण अन्यथा अणु
		अगर (asc >= 0x80)
			off = scnम_लिखो(buffer, buf_len, "<<vendor>>");
		off += scnम_लिखो(buffer + off, buf_len - off,
				 "ASC=0x%x ", asc);
		अगर (ascq >= 0x80)
			off += scnम_लिखो(buffer + off, buf_len - off,
					 "<<vendor>>");
		off += scnम_लिखो(buffer + off, buf_len - off,
				 "ASCQ=0x%x ", ascq);
	पूर्ण
	वापस off;
पूर्ण

अटल माप_प्रकार
scsi_क्रमmat_sense_hdr(अक्षर *buffer, माप_प्रकार buf_len,
		      स्थिर काष्ठा scsi_sense_hdr *sshdr)
अणु
	स्थिर अक्षर *sense_txt;
	माप_प्रकार off;

	off = scnम_लिखो(buffer, buf_len, "Sense Key : ");
	sense_txt = scsi_sense_key_string(sshdr->sense_key);
	अगर (sense_txt)
		off += scnम_लिखो(buffer + off, buf_len - off,
				 "%s ", sense_txt);
	अन्यथा
		off += scnम_लिखो(buffer + off, buf_len - off,
				 "0x%x ", sshdr->sense_key);
	off += scnम_लिखो(buffer + off, buf_len - off,
		scsi_sense_is_deferred(sshdr) ? "[deferred] " : "[current] ");

	अगर (sshdr->response_code >= 0x72)
		off += scnम_लिखो(buffer + off, buf_len - off, "[descriptor] ");
	वापस off;
पूर्ण

अटल व्योम
scsi_log_dump_sense(स्थिर काष्ठा scsi_device *sdev, स्थिर अक्षर *name, पूर्णांक tag,
		    स्थिर अचिन्हित अक्षर *sense_buffer, पूर्णांक sense_len)
अणु
	अक्षर *logbuf;
	माप_प्रकार logbuf_len;
	पूर्णांक i;

	logbuf = scsi_log_reserve_buffer(&logbuf_len);
	अगर (!logbuf)
		वापस;

	क्रम (i = 0; i < sense_len; i += 16) अणु
		पूर्णांक len = min(sense_len - i, 16);
		माप_प्रकार off;

		off = sdev_क्रमmat_header(logbuf, logbuf_len,
					 name, tag);
		hex_dump_to_buffer(&sense_buffer[i], len, 16, 1,
				   logbuf + off, logbuf_len - off,
				   false);
		dev_prपूर्णांकk(KERN_INFO, &sdev->sdev_gendev, "%s", logbuf);
	पूर्ण
	scsi_log_release_buffer(logbuf);
पूर्ण

अटल व्योम
scsi_log_prपूर्णांक_sense_hdr(स्थिर काष्ठा scsi_device *sdev, स्थिर अक्षर *name,
			 पूर्णांक tag, स्थिर काष्ठा scsi_sense_hdr *sshdr)
अणु
	अक्षर *logbuf;
	माप_प्रकार off, logbuf_len;

	logbuf = scsi_log_reserve_buffer(&logbuf_len);
	अगर (!logbuf)
		वापस;
	off = sdev_क्रमmat_header(logbuf, logbuf_len, name, tag);
	off += scsi_क्रमmat_sense_hdr(logbuf + off, logbuf_len - off, sshdr);
	dev_prपूर्णांकk(KERN_INFO, &sdev->sdev_gendev, "%s", logbuf);
	scsi_log_release_buffer(logbuf);

	logbuf = scsi_log_reserve_buffer(&logbuf_len);
	अगर (!logbuf)
		वापस;
	off = sdev_क्रमmat_header(logbuf, logbuf_len, name, tag);
	off += scsi_क्रमmat_extd_sense(logbuf + off, logbuf_len - off,
				      sshdr->asc, sshdr->ascq);
	dev_prपूर्णांकk(KERN_INFO, &sdev->sdev_gendev, "%s", logbuf);
	scsi_log_release_buffer(logbuf);
पूर्ण

अटल व्योम
scsi_log_prपूर्णांक_sense(स्थिर काष्ठा scsi_device *sdev, स्थिर अक्षर *name, पूर्णांक tag,
		     स्थिर अचिन्हित अक्षर *sense_buffer, पूर्णांक sense_len)
अणु
	काष्ठा scsi_sense_hdr sshdr;

	अगर (scsi_normalize_sense(sense_buffer, sense_len, &sshdr))
		scsi_log_prपूर्णांक_sense_hdr(sdev, name, tag, &sshdr);
	अन्यथा
		scsi_log_dump_sense(sdev, name, tag, sense_buffer, sense_len);
पूर्ण

/*
 * Prपूर्णांक normalized SCSI sense header with a prefix.
 */
व्योम
scsi_prपूर्णांक_sense_hdr(स्थिर काष्ठा scsi_device *sdev, स्थिर अक्षर *name,
		     स्थिर काष्ठा scsi_sense_hdr *sshdr)
अणु
	scsi_log_prपूर्णांक_sense_hdr(sdev, name, -1, sshdr);
पूर्ण
EXPORT_SYMBOL(scsi_prपूर्णांक_sense_hdr);

/* Normalize and prपूर्णांक sense buffer with name prefix */
व्योम __scsi_prपूर्णांक_sense(स्थिर काष्ठा scsi_device *sdev, स्थिर अक्षर *name,
			स्थिर अचिन्हित अक्षर *sense_buffer, पूर्णांक sense_len)
अणु
	scsi_log_prपूर्णांक_sense(sdev, name, -1, sense_buffer, sense_len);
पूर्ण
EXPORT_SYMBOL(__scsi_prपूर्णांक_sense);

/* Normalize and prपूर्णांक sense buffer in SCSI command */
व्योम scsi_prपूर्णांक_sense(स्थिर काष्ठा scsi_cmnd *cmd)
अणु
	scsi_log_prपूर्णांक_sense(cmd->device, scmd_name(cmd), cmd->request->tag,
			     cmd->sense_buffer, SCSI_SENSE_BUFFERSIZE);
पूर्ण
EXPORT_SYMBOL(scsi_prपूर्णांक_sense);

व्योम scsi_prपूर्णांक_result(स्थिर काष्ठा scsi_cmnd *cmd, स्थिर अक्षर *msg,
		       पूर्णांक disposition)
अणु
	अक्षर *logbuf;
	माप_प्रकार off, logbuf_len;
	स्थिर अक्षर *mlret_string = scsi_mlवापस_string(disposition);
	स्थिर अक्षर *hb_string = scsi_hostbyte_string(cmd->result);
	स्थिर अक्षर *db_string = scsi_driverbyte_string(cmd->result);
	अचिन्हित दीर्घ cmd_age = (jअगरfies - cmd->jअगरfies_at_alloc) / HZ;

	logbuf = scsi_log_reserve_buffer(&logbuf_len);
	अगर (!logbuf)
		वापस;

	off = sdev_क्रमmat_header(logbuf, logbuf_len,
				 scmd_name(cmd), cmd->request->tag);

	अगर (off >= logbuf_len)
		जाओ out_prपूर्णांकk;

	अगर (msg) अणु
		off += scnम_लिखो(logbuf + off, logbuf_len - off,
				 "%s: ", msg);
		अगर (WARN_ON(off >= logbuf_len))
			जाओ out_prपूर्णांकk;
	पूर्ण
	अगर (mlret_string)
		off += scnम_लिखो(logbuf + off, logbuf_len - off,
				 "%s ", mlret_string);
	अन्यथा
		off += scnम_लिखो(logbuf + off, logbuf_len - off,
				 "UNKNOWN(0x%02x) ", disposition);
	अगर (WARN_ON(off >= logbuf_len))
		जाओ out_prपूर्णांकk;

	off += scnम_लिखो(logbuf + off, logbuf_len - off, "Result: ");
	अगर (WARN_ON(off >= logbuf_len))
		जाओ out_prपूर्णांकk;

	अगर (hb_string)
		off += scnम_लिखो(logbuf + off, logbuf_len - off,
				 "hostbyte=%s ", hb_string);
	अन्यथा
		off += scnम_लिखो(logbuf + off, logbuf_len - off,
				 "hostbyte=0x%02x ", host_byte(cmd->result));
	अगर (WARN_ON(off >= logbuf_len))
		जाओ out_prपूर्णांकk;

	अगर (db_string)
		off += scnम_लिखो(logbuf + off, logbuf_len - off,
				 "driverbyte=%s ", db_string);
	अन्यथा
		off += scnम_लिखो(logbuf + off, logbuf_len - off,
				 "driverbyte=0x%02x ",
				 driver_byte(cmd->result));

	off += scnम_लिखो(logbuf + off, logbuf_len - off,
			 "cmd_age=%lus", cmd_age);

out_prपूर्णांकk:
	dev_prपूर्णांकk(KERN_INFO, &cmd->device->sdev_gendev, "%s", logbuf);
	scsi_log_release_buffer(logbuf);
पूर्ण
EXPORT_SYMBOL(scsi_prपूर्णांक_result);
