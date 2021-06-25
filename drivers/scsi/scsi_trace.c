<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 FUJITSU LIMITED
 * Copyright (C) 2010 Tomohiro Kusumi <kusumi.tomohiro@jp.fujitsu.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/trace_seq.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <trace/events/scsi.h>

#घोषणा SERVICE_ACTION16(cdb) (cdb[1] & 0x1f)
#घोषणा SERVICE_ACTION32(cdb) (get_unaligned_be16(&cdb[8]))

अटल स्थिर अक्षर *
scsi_trace_misc(काष्ठा trace_seq *, अचिन्हित अक्षर *, पूर्णांक);

अटल स्थिर अक्षर *
scsi_trace_rw6(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u32 lba, txlen;

	lba = get_unaligned_be24(&cdb[1]) & 0x1fffff;
	/*
	 * From SBC-2: a TRANSFER LENGTH field set to zero specअगरies that 256
	 * logical blocks shall be पढ़ो (READ(6)) or written (WRITE(6)).
	 */
	txlen = cdb[4] ? cdb[4] : 256;

	trace_seq_म_लिखो(p, "lba=%u txlen=%u", lba, txlen);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_rw10(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u32 lba, txlen;

	lba = get_unaligned_be32(&cdb[2]);
	txlen = get_unaligned_be16(&cdb[7]);

	trace_seq_म_लिखो(p, "lba=%u txlen=%u protect=%u", lba, txlen,
			 cdb[1] >> 5);

	अगर (cdb[0] == WRITE_SAME)
		trace_seq_म_लिखो(p, " unmap=%u", cdb[1] >> 3 & 1);

	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_rw12(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u32 lba, txlen;

	lba = get_unaligned_be32(&cdb[2]);
	txlen = get_unaligned_be32(&cdb[6]);

	trace_seq_म_लिखो(p, "lba=%u txlen=%u protect=%u", lba, txlen,
			 cdb[1] >> 5);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_rw16(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	u64 lba;
	u32 txlen;

	lba = get_unaligned_be64(&cdb[2]);
	txlen = get_unaligned_be32(&cdb[10]);

	trace_seq_म_लिखो(p, "lba=%llu txlen=%u protect=%u", lba, txlen,
			 cdb[1] >> 5);

	अगर (cdb[0] == WRITE_SAME_16)
		trace_seq_म_लिखो(p, " unmap=%u", cdb[1] >> 3 & 1);

	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_rw32(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p), *cmd;
	u64 lba;
	u32 ei_lbrt, txlen;

	चयन (SERVICE_ACTION32(cdb)) अणु
	हाल READ_32:
		cmd = "READ";
		अवरोध;
	हाल VERIFY_32:
		cmd = "VERIFY";
		अवरोध;
	हाल WRITE_32:
		cmd = "WRITE";
		अवरोध;
	हाल WRITE_SAME_32:
		cmd = "WRITE_SAME";
		अवरोध;
	शेष:
		trace_seq_माला_दो(p, "UNKNOWN");
		जाओ out;
	पूर्ण

	lba = get_unaligned_be64(&cdb[12]);
	ei_lbrt = get_unaligned_be32(&cdb[20]);
	txlen = get_unaligned_be32(&cdb[28]);

	trace_seq_म_लिखो(p, "%s_32 lba=%llu txlen=%u protect=%u ei_lbrt=%u",
			 cmd, lba, txlen, cdb[10] >> 5, ei_lbrt);

	अगर (SERVICE_ACTION32(cdb) == WRITE_SAME_32)
		trace_seq_म_लिखो(p, " unmap=%u", cdb[10] >> 3 & 1);

out:
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_unmap(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	अचिन्हित पूर्णांक regions = get_unaligned_be16(&cdb[7]);

	trace_seq_म_लिखो(p, "regions=%u", (regions - 8) / 16);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_service_action_in(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p), *cmd;
	u64 lba;
	u32 alloc_len;

	चयन (SERVICE_ACTION16(cdb)) अणु
	हाल SAI_READ_CAPACITY_16:
		cmd = "READ_CAPACITY_16";
		अवरोध;
	हाल SAI_GET_LBA_STATUS:
		cmd = "GET_LBA_STATUS";
		अवरोध;
	शेष:
		trace_seq_माला_दो(p, "UNKNOWN");
		जाओ out;
	पूर्ण

	lba = get_unaligned_be64(&cdb[2]);
	alloc_len = get_unaligned_be32(&cdb[10]);

	trace_seq_म_लिखो(p, "%s lba=%llu alloc_len=%u", cmd, lba, alloc_len);

out:
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_मुख्यtenance_in(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p), *cmd;
	u32 alloc_len;

	चयन (SERVICE_ACTION16(cdb)) अणु
	हाल MI_REPORT_IDENTIFYING_INFORMATION:
		cmd = "REPORT_IDENTIFYING_INFORMATION";
		अवरोध;
	हाल MI_REPORT_TARGET_PGS:
		cmd = "REPORT_TARGET_PORT_GROUPS";
		अवरोध;
	हाल MI_REPORT_ALIASES:
		cmd = "REPORT_ALIASES";
		अवरोध;
	हाल MI_REPORT_SUPPORTED_OPERATION_CODES:
		cmd = "REPORT_SUPPORTED_OPERATION_CODES";
		अवरोध;
	हाल MI_REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS:
		cmd = "REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS";
		अवरोध;
	हाल MI_REPORT_PRIORITY:
		cmd = "REPORT_PRIORITY";
		अवरोध;
	हाल MI_REPORT_TIMESTAMP:
		cmd = "REPORT_TIMESTAMP";
		अवरोध;
	हाल MI_MANAGEMENT_PROTOCOL_IN:
		cmd = "MANAGEMENT_PROTOCOL_IN";
		अवरोध;
	शेष:
		trace_seq_माला_दो(p, "UNKNOWN");
		जाओ out;
	पूर्ण

	alloc_len = get_unaligned_be32(&cdb[6]);

	trace_seq_म_लिखो(p, "%s alloc_len=%u", cmd, alloc_len);

out:
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_मुख्यtenance_out(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p), *cmd;
	u32 alloc_len;

	चयन (SERVICE_ACTION16(cdb)) अणु
	हाल MO_SET_IDENTIFYING_INFORMATION:
		cmd = "SET_IDENTIFYING_INFORMATION";
		अवरोध;
	हाल MO_SET_TARGET_PGS:
		cmd = "SET_TARGET_PORT_GROUPS";
		अवरोध;
	हाल MO_CHANGE_ALIASES:
		cmd = "CHANGE_ALIASES";
		अवरोध;
	हाल MO_SET_PRIORITY:
		cmd = "SET_PRIORITY";
		अवरोध;
	हाल MO_SET_TIMESTAMP:
		cmd = "SET_TIMESTAMP";
		अवरोध;
	हाल MO_MANAGEMENT_PROTOCOL_OUT:
		cmd = "MANAGEMENT_PROTOCOL_OUT";
		अवरोध;
	शेष:
		trace_seq_माला_दो(p, "UNKNOWN");
		जाओ out;
	पूर्ण

	alloc_len = get_unaligned_be32(&cdb[6]);

	trace_seq_म_लिखो(p, "%s alloc_len=%u", cmd, alloc_len);

out:
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_zbc_in(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p), *cmd;
	u64 zone_id;
	u32 alloc_len;
	u8 options;

	चयन (SERVICE_ACTION16(cdb)) अणु
	हाल ZI_REPORT_ZONES:
		cmd = "REPORT_ZONES";
		अवरोध;
	शेष:
		trace_seq_माला_दो(p, "UNKNOWN");
		जाओ out;
	पूर्ण

	zone_id = get_unaligned_be64(&cdb[2]);
	alloc_len = get_unaligned_be32(&cdb[10]);
	options = cdb[14] & 0x3f;

	trace_seq_म_लिखो(p, "%s zone=%llu alloc_len=%u options=%u partial=%u",
			 cmd, (अचिन्हित दीर्घ दीर्घ)zone_id, alloc_len,
			 options, (cdb[14] >> 7) & 1);

out:
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_zbc_out(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p), *cmd;
	u64 zone_id;

	चयन (SERVICE_ACTION16(cdb)) अणु
	हाल ZO_CLOSE_ZONE:
		cmd = "CLOSE_ZONE";
		अवरोध;
	हाल ZO_FINISH_ZONE:
		cmd = "FINISH_ZONE";
		अवरोध;
	हाल ZO_OPEN_ZONE:
		cmd = "OPEN_ZONE";
		अवरोध;
	हाल ZO_RESET_WRITE_POINTER:
		cmd = "RESET_WRITE_POINTER";
		अवरोध;
	शेष:
		trace_seq_माला_दो(p, "UNKNOWN");
		जाओ out;
	पूर्ण

	zone_id = get_unaligned_be64(&cdb[2]);

	trace_seq_म_लिखो(p, "%s zone=%llu all=%u", cmd,
			 (अचिन्हित दीर्घ दीर्घ)zone_id, cdb[14] & 1);

out:
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_varlen(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	चयन (SERVICE_ACTION32(cdb)) अणु
	हाल READ_32:
	हाल VERIFY_32:
	हाल WRITE_32:
	हाल WRITE_SAME_32:
		वापस scsi_trace_rw32(p, cdb, len);
	शेष:
		वापस scsi_trace_misc(p, cdb, len);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_misc(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_अ_दो(p, '-');
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण

स्थिर अक्षर *
scsi_trace_parse_cdb(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	चयन (cdb[0]) अणु
	हाल READ_6:
	हाल WRITE_6:
		वापस scsi_trace_rw6(p, cdb, len);
	हाल READ_10:
	हाल VERIFY:
	हाल WRITE_10:
	हाल WRITE_SAME:
		वापस scsi_trace_rw10(p, cdb, len);
	हाल READ_12:
	हाल VERIFY_12:
	हाल WRITE_12:
		वापस scsi_trace_rw12(p, cdb, len);
	हाल READ_16:
	हाल VERIFY_16:
	हाल WRITE_16:
	हाल WRITE_SAME_16:
		वापस scsi_trace_rw16(p, cdb, len);
	हाल UNMAP:
		वापस scsi_trace_unmap(p, cdb, len);
	हाल SERVICE_ACTION_IN_16:
		वापस scsi_trace_service_action_in(p, cdb, len);
	हाल VARIABLE_LENGTH_CMD:
		वापस scsi_trace_varlen(p, cdb, len);
	हाल MAINTEन_अंकCE_IN:
		वापस scsi_trace_मुख्यtenance_in(p, cdb, len);
	हाल MAINTEन_अंकCE_OUT:
		वापस scsi_trace_मुख्यtenance_out(p, cdb, len);
	हाल ZBC_IN:
		वापस scsi_trace_zbc_in(p, cdb, len);
	हाल ZBC_OUT:
		वापस scsi_trace_zbc_out(p, cdb, len);
	शेष:
		वापस scsi_trace_misc(p, cdb, len);
	पूर्ण
पूर्ण
