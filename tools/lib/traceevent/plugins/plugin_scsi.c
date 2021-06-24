<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>
#समावेश "event-parse.h"
#समावेश "trace-seq.h"

प्रकार अचिन्हित दीर्घ sector_t;
प्रकार uपूर्णांक64_t u64;
प्रकार अचिन्हित पूर्णांक u32;

/*
 *      SCSI opcodes
 */
#घोषणा TEST_UNIT_READY			0x00
#घोषणा REZERO_UNIT			0x01
#घोषणा REQUEST_SENSE			0x03
#घोषणा FORMAT_UNIT			0x04
#घोषणा READ_BLOCK_LIMITS		0x05
#घोषणा REASSIGN_BLOCKS			0x07
#घोषणा INITIALIZE_ELEMENT_STATUS	0x07
#घोषणा READ_6				0x08
#घोषणा WRITE_6				0x0a
#घोषणा SEEK_6				0x0b
#घोषणा READ_REVERSE			0x0f
#घोषणा WRITE_खाताMARKS			0x10
#घोषणा SPACE				0x11
#घोषणा INQUIRY				0x12
#घोषणा RECOVER_BUFFERED_DATA		0x14
#घोषणा MODE_SELECT			0x15
#घोषणा RESERVE				0x16
#घोषणा RELEASE				0x17
#घोषणा COPY				0x18
#घोषणा ERASE				0x19
#घोषणा MODE_SENSE			0x1a
#घोषणा START_STOP			0x1b
#घोषणा RECEIVE_DIAGNOSTIC		0x1c
#घोषणा SEND_DIAGNOSTIC			0x1d
#घोषणा ALLOW_MEDIUM_REMOVAL		0x1e

#घोषणा READ_FORMAT_CAPACITIES		0x23
#घोषणा SET_WINDOW			0x24
#घोषणा READ_CAPACITY			0x25
#घोषणा READ_10				0x28
#घोषणा WRITE_10			0x2a
#घोषणा SEEK_10				0x2b
#घोषणा POSITION_TO_ELEMENT		0x2b
#घोषणा WRITE_VERIFY			0x2e
#घोषणा VERIFY				0x2f
#घोषणा SEARCH_HIGH			0x30
#घोषणा SEARCH_EQUAL			0x31
#घोषणा SEARCH_LOW			0x32
#घोषणा SET_LIMITS			0x33
#घोषणा PRE_FETCH			0x34
#घोषणा READ_POSITION			0x34
#घोषणा SYNCHRONIZE_CACHE		0x35
#घोषणा LOCK_UNLOCK_CACHE		0x36
#घोषणा READ_DEFECT_DATA		0x37
#घोषणा MEDIUM_SCAN			0x38
#घोषणा COMPARE				0x39
#घोषणा COPY_VERIFY			0x3a
#घोषणा WRITE_BUFFER			0x3b
#घोषणा READ_BUFFER			0x3c
#घोषणा UPDATE_BLOCK			0x3d
#घोषणा READ_LONG			0x3e
#घोषणा WRITE_LONG			0x3f
#घोषणा CHANGE_DEFINITION		0x40
#घोषणा WRITE_SAME			0x41
#घोषणा UNMAP				0x42
#घोषणा READ_TOC			0x43
#घोषणा READ_HEADER			0x44
#घोषणा GET_EVENT_STATUS_NOTIFICATION	0x4a
#घोषणा LOG_SELECT			0x4c
#घोषणा LOG_SENSE			0x4d
#घोषणा XDWRITEREAD_10			0x53
#घोषणा MODE_SELECT_10			0x55
#घोषणा RESERVE_10			0x56
#घोषणा RELEASE_10			0x57
#घोषणा MODE_SENSE_10			0x5a
#घोषणा PERSISTENT_RESERVE_IN		0x5e
#घोषणा PERSISTENT_RESERVE_OUT		0x5f
#घोषणा VARIABLE_LENGTH_CMD		0x7f
#घोषणा REPORT_LUNS			0xa0
#घोषणा SECURITY_PROTOCOL_IN		0xa2
#घोषणा MAINTEन_अंकCE_IN			0xa3
#घोषणा MAINTEन_अंकCE_OUT			0xa4
#घोषणा MOVE_MEDIUM			0xa5
#घोषणा EXCHANGE_MEDIUM			0xa6
#घोषणा READ_12				0xa8
#घोषणा SERVICE_ACTION_OUT_12		0xa9
#घोषणा WRITE_12			0xaa
#घोषणा SERVICE_ACTION_IN_12		0xab
#घोषणा WRITE_VERIFY_12			0xae
#घोषणा VERIFY_12			0xaf
#घोषणा SEARCH_HIGH_12			0xb0
#घोषणा SEARCH_EQUAL_12			0xb1
#घोषणा SEARCH_LOW_12			0xb2
#घोषणा SECURITY_PROTOCOL_OUT		0xb5
#घोषणा READ_ELEMENT_STATUS		0xb8
#घोषणा SEND_VOLUME_TAG			0xb6
#घोषणा WRITE_LONG_2			0xea
#घोषणा EXTENDED_COPY			0x83
#घोषणा RECEIVE_COPY_RESULTS		0x84
#घोषणा ACCESS_CONTROL_IN		0x86
#घोषणा ACCESS_CONTROL_OUT		0x87
#घोषणा READ_16				0x88
#घोषणा WRITE_16			0x8a
#घोषणा READ_ATTRIBUTE			0x8c
#घोषणा WRITE_ATTRIBUTE			0x8d
#घोषणा VERIFY_16			0x8f
#घोषणा SYNCHRONIZE_CACHE_16		0x91
#घोषणा WRITE_SAME_16			0x93
#घोषणा SERVICE_ACTION_BIसूचीECTIONAL	0x9d
#घोषणा SERVICE_ACTION_IN_16		0x9e
#घोषणा SERVICE_ACTION_OUT_16		0x9f
/* values क्रम service action in */
#घोषणा	SAI_READ_CAPACITY_16		0x10
#घोषणा SAI_GET_LBA_STATUS		0x12
/* values क्रम VARIABLE_LENGTH_CMD service action codes
 * see spc4r17 Section D.3.5, table D.7 and D.8 */
#घोषणा VLC_SA_RECEIVE_CREDENTIAL	0x1800
/* values क्रम मुख्यtenance in */
#घोषणा MI_REPORT_IDENTIFYING_INFORMATION		0x05
#घोषणा MI_REPORT_TARGET_PGS				0x0a
#घोषणा MI_REPORT_ALIASES				0x0b
#घोषणा MI_REPORT_SUPPORTED_OPERATION_CODES		0x0c
#घोषणा MI_REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS	0x0d
#घोषणा MI_REPORT_PRIORITY				0x0e
#घोषणा MI_REPORT_TIMESTAMP				0x0f
#घोषणा MI_MANAGEMENT_PROTOCOL_IN			0x10
/* value क्रम MI_REPORT_TARGET_PGS ext header */
#घोषणा MI_EXT_HDR_PARAM_FMT		0x20
/* values क्रम मुख्यtenance out */
#घोषणा MO_SET_IDENTIFYING_INFORMATION	0x06
#घोषणा MO_SET_TARGET_PGS		0x0a
#घोषणा MO_CHANGE_ALIASES		0x0b
#घोषणा MO_SET_PRIORITY			0x0e
#घोषणा MO_SET_TIMESTAMP		0x0f
#घोषणा MO_MANAGEMENT_PROTOCOL_OUT	0x10
/* values क्रम variable length command */
#घोषणा XDREAD_32			0x03
#घोषणा XDWRITE_32			0x04
#घोषणा XPWRITE_32			0x06
#घोषणा XDWRITEREAD_32			0x07
#घोषणा READ_32				0x09
#घोषणा VERIFY_32			0x0a
#घोषणा WRITE_32			0x0b
#घोषणा WRITE_SAME_32			0x0d

#घोषणा SERVICE_ACTION16(cdb) (cdb[1] & 0x1f)
#घोषणा SERVICE_ACTION32(cdb) ((cdb[8] << 8) | cdb[9])

अटल स्थिर अक्षर *
scsi_trace_misc(काष्ठा trace_seq *, अचिन्हित अक्षर *, पूर्णांक);

अटल स्थिर अक्षर *
scsi_trace_rw6(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = p->buffer + p->len;
	sector_t lba = 0, txlen = 0;

	lba |= ((cdb[1] & 0x1F) << 16);
	lba |=  (cdb[2] << 8);
	lba |=   cdb[3];
	txlen = cdb[4];

	trace_seq_म_लिखो(p, "lba=%llu txlen=%llu",
			 (अचिन्हित दीर्घ दीर्घ)lba, (अचिन्हित दीर्घ दीर्घ)txlen);
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_rw10(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = p->buffer + p->len;
	sector_t lba = 0, txlen = 0;

	lba |= (cdb[2] << 24);
	lba |= (cdb[3] << 16);
	lba |= (cdb[4] << 8);
	lba |=  cdb[5];
	txlen |= (cdb[7] << 8);
	txlen |=  cdb[8];

	trace_seq_म_लिखो(p, "lba=%llu txlen=%llu protect=%u",
			 (अचिन्हित दीर्घ दीर्घ)lba, (अचिन्हित दीर्घ दीर्घ)txlen,
			 cdb[1] >> 5);

	अगर (cdb[0] == WRITE_SAME)
		trace_seq_म_लिखो(p, " unmap=%u", cdb[1] >> 3 & 1);

	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_rw12(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = p->buffer + p->len;
	sector_t lba = 0, txlen = 0;

	lba |= (cdb[2] << 24);
	lba |= (cdb[3] << 16);
	lba |= (cdb[4] << 8);
	lba |=  cdb[5];
	txlen |= (cdb[6] << 24);
	txlen |= (cdb[7] << 16);
	txlen |= (cdb[8] << 8);
	txlen |=  cdb[9];

	trace_seq_म_लिखो(p, "lba=%llu txlen=%llu protect=%u",
			 (अचिन्हित दीर्घ दीर्घ)lba, (अचिन्हित दीर्घ दीर्घ)txlen,
			 cdb[1] >> 5);
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_rw16(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = p->buffer + p->len;
	sector_t lba = 0, txlen = 0;

	lba |= ((u64)cdb[2] << 56);
	lba |= ((u64)cdb[3] << 48);
	lba |= ((u64)cdb[4] << 40);
	lba |= ((u64)cdb[5] << 32);
	lba |= (cdb[6] << 24);
	lba |= (cdb[7] << 16);
	lba |= (cdb[8] << 8);
	lba |=  cdb[9];
	txlen |= (cdb[10] << 24);
	txlen |= (cdb[11] << 16);
	txlen |= (cdb[12] << 8);
	txlen |=  cdb[13];

	trace_seq_म_लिखो(p, "lba=%llu txlen=%llu protect=%u",
			 (अचिन्हित दीर्घ दीर्घ)lba, (अचिन्हित दीर्घ दीर्घ)txlen,
			 cdb[1] >> 5);

	अगर (cdb[0] == WRITE_SAME_16)
		trace_seq_म_लिखो(p, " unmap=%u", cdb[1] >> 3 & 1);

	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_rw32(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = p->buffer + p->len, *cmd;
	sector_t lba = 0, txlen = 0;
	u32 ei_lbrt = 0;

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
		trace_seq_म_लिखो(p, "UNKNOWN");
		जाओ out;
	पूर्ण

	lba |= ((u64)cdb[12] << 56);
	lba |= ((u64)cdb[13] << 48);
	lba |= ((u64)cdb[14] << 40);
	lba |= ((u64)cdb[15] << 32);
	lba |= (cdb[16] << 24);
	lba |= (cdb[17] << 16);
	lba |= (cdb[18] << 8);
	lba |=  cdb[19];
	ei_lbrt |= (cdb[20] << 24);
	ei_lbrt |= (cdb[21] << 16);
	ei_lbrt |= (cdb[22] << 8);
	ei_lbrt |=  cdb[23];
	txlen |= (cdb[28] << 24);
	txlen |= (cdb[29] << 16);
	txlen |= (cdb[30] << 8);
	txlen |=  cdb[31];

	trace_seq_म_लिखो(p, "%s_32 lba=%llu txlen=%llu protect=%u ei_lbrt=%u",
			 cmd, (अचिन्हित दीर्घ दीर्घ)lba,
			 (अचिन्हित दीर्घ दीर्घ)txlen, cdb[10] >> 5, ei_lbrt);

	अगर (SERVICE_ACTION32(cdb) == WRITE_SAME_32)
		trace_seq_म_लिखो(p, " unmap=%u", cdb[10] >> 3 & 1);

out:
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_unmap(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = p->buffer + p->len;
	अचिन्हित पूर्णांक regions = cdb[7] << 8 | cdb[8];

	trace_seq_म_लिखो(p, "regions=%u", (regions - 8) / 16);
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *
scsi_trace_service_action_in(काष्ठा trace_seq *p, अचिन्हित अक्षर *cdb, पूर्णांक len)
अणु
	स्थिर अक्षर *ret = p->buffer + p->len, *cmd;
	sector_t lba = 0;
	u32 alloc_len = 0;

	चयन (SERVICE_ACTION16(cdb)) अणु
	हाल SAI_READ_CAPACITY_16:
		cmd = "READ_CAPACITY_16";
		अवरोध;
	हाल SAI_GET_LBA_STATUS:
		cmd = "GET_LBA_STATUS";
		अवरोध;
	शेष:
		trace_seq_म_लिखो(p, "UNKNOWN");
		जाओ out;
	पूर्ण

	lba |= ((u64)cdb[2] << 56);
	lba |= ((u64)cdb[3] << 48);
	lba |= ((u64)cdb[4] << 40);
	lba |= ((u64)cdb[5] << 32);
	lba |= (cdb[6] << 24);
	lba |= (cdb[7] << 16);
	lba |= (cdb[8] << 8);
	lba |=  cdb[9];
	alloc_len |= (cdb[10] << 24);
	alloc_len |= (cdb[11] << 16);
	alloc_len |= (cdb[12] << 8);
	alloc_len |=  cdb[13];

	trace_seq_म_लिखो(p, "%s lba=%llu alloc_len=%u", cmd,
			 (अचिन्हित दीर्घ दीर्घ)lba, alloc_len);

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
	स्थिर अक्षर *ret = p->buffer + p->len;

	trace_seq_म_लिखो(p, "-");
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
	शेष:
		वापस scsi_trace_misc(p, cdb, len);
	पूर्ण
पूर्ण

अचिन्हित दीर्घ दीर्घ process_scsi_trace_parse_cdb(काष्ठा trace_seq *s,
						अचिन्हित दीर्घ दीर्घ *args)
अणु
	scsi_trace_parse_cdb(s, (अचिन्हित अक्षर *) (अचिन्हित दीर्घ) args[1], args[2]);
	वापस 0;
पूर्ण

पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
अणु
	tep_रेजिस्टर_prपूर्णांक_function(tep,
				    process_scsi_trace_parse_cdb,
				    TEP_FUNC_ARG_STRING,
				    "scsi_trace_parse_cdb",
				    TEP_FUNC_ARG_PTR,
				    TEP_FUNC_ARG_PTR,
				    TEP_FUNC_ARG_INT,
				    TEP_FUNC_ARG_VOID);
	वापस 0;
पूर्ण

व्योम TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
अणु
	tep_unरेजिस्टर_prपूर्णांक_function(tep, process_scsi_trace_parse_cdb,
				      "scsi_trace_parse_cdb");
पूर्ण
