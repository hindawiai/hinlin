<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ASCII values क्रम a number of symbolic स्थिरants, prपूर्णांकing functions,
 * etc.
 * Additions क्रम SCSI 2 and Linux 2.2.x by D. Gilbert (990422)
 * Additions क्रम SCSI 3+ (SPC-3 T10/1416-D Rev 07 3 May 2002)
 *   by D. Gilbert and aeb (20020609)
 * Updated to SPC-4 T10/1713-D Rev 36g, D. Gilbert 20130701
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_dbg.h>

/* Commands with service actions that change the command name */
#घोषणा THIRD_PARTY_COPY_OUT 0x83
#घोषणा THIRD_PARTY_COPY_IN 0x84

काष्ठा sa_name_list अणु
	पूर्णांक opcode;
	स्थिर काष्ठा value_name_pair *arr;
	पूर्णांक arr_sz;
पूर्ण;

काष्ठा value_name_pair अणु
	पूर्णांक value;
	स्थिर अक्षर * name;
पूर्ण;

अटल स्थिर अक्षर * cdb_byte0_names[] = अणु
/* 00-03 */ "Test Unit Ready", "Rezero Unit/Rewind", शून्य, "Request Sense",
/* 04-07 */ "Format Unit/Medium", "Read Block Limits", शून्य,
	    "Reassign Blocks",
/* 08-0d */ "Read(6)", शून्य, "Write(6)", "Seek(6)", शून्य, शून्य,
/* 0e-12 */ शून्य, "Read Reverse", "Write Filemarks", "Space", "Inquiry",
/* 13-16 */ "Verify(6)", "Recover Buffered Data", "Mode Select(6)",
	    "Reserve(6)",
/* 17-1a */ "Release(6)", "Copy", "Erase", "Mode Sense(6)",
/* 1b-1d */ "Start/Stop Unit", "Receive Diagnostic", "Send Diagnostic",
/* 1e-1f */ "Prevent/Allow Medium Removal", शून्य,
/* 20-22 */  शून्य, शून्य, शून्य,
/* 23-28 */ "Read Format Capacities", "Set Window",
	    "Read Capacity(10)", शून्य, शून्य, "Read(10)",
/* 29-2d */ "Read Generation", "Write(10)", "Seek(10)", "Erase(10)",
            "Read updated block",
/* 2e-31 */ "Write Verify(10)", "Verify(10)", "Search High", "Search Equal",
/* 32-34 */ "Search Low", "Set Limits", "Prefetch/Read Position",
/* 35-37 */ "Synchronize Cache(10)", "Lock/Unlock Cache(10)",
	    "Read Defect Data(10)",
/* 38-3c */ "Medium Scan", "Compare", "Copy Verify", "Write Buffer",
	    "Read Buffer",
/* 3d-3f */ "Update Block", "Read Long(10)",  "Write Long(10)",
/* 40-41 */ "Change Definition", "Write Same(10)",
/* 42-48 */ "Unmap/Read sub-channel", "Read TOC/PMA/ATIP",
	    "Read density support", "Play audio(10)", "Get configuration",
	    "Play audio msf", "Sanitize/Play audio track/index",
/* 49-4f */ "Play track relative(10)", "Get event status notification",
            "Pause/resume", "Log Select", "Log Sense", "Stop play/scan",
            शून्य,
/* 50-55 */ "Xdwrite", "Xpwrite, Read disk info", "Xdread, Read track info",
            "Reserve track", "Send OPC info", "Mode Select(10)",
/* 56-5b */ "Reserve(10)", "Release(10)", "Repair track", "Read master cue",
            "Mode Sense(10)", "Close track/session",
/* 5c-5f */ "Read buffer capacity", "Send cue sheet", "Persistent reserve in",
            "Persistent reserve out",
/* 60-67 */ शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
/* 68-6f */ शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
/* 70-77 */ शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य,
/* 78-7f */ शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, "Extended CDB",
	    "Variable length",
/* 80-84 */ "Xdwrite(16)", "Rebuild(16)", "Regenerate(16)",
	    "Third party copy out", "Third party copy in",
/* 85-89 */ "ATA command pass through(16)", "Access control in",
	    "Access control out", "Read(16)", "Compare and Write",
/* 8a-8f */ "Write(16)", "ORWrite", "Read attributes", "Write attributes",
            "Write and verify(16)", "Verify(16)",
/* 90-94 */ "Pre-fetch(16)", "Synchronize cache(16)",
            "Lock/unlock cache(16)", "Write same(16)", शून्य,
/* 95-99 */ शून्य, शून्य, शून्य, शून्य, शून्य,
/* 9a-9f */ शून्य, शून्य, शून्य, "Service action bidirectional",
	    "Service action in(16)", "Service action out(16)",
/* a0-a5 */ "Report luns", "ATA command pass through(12)/Blank",
            "Security protocol in", "Maintenance in", "Maintenance out",
	    "Move medium/play audio(12)",
/* a6-a9 */ "Exchange medium", "Move medium attached", "Read(12)",
            "Play track relative(12)",
/* aa-ae */ "Write(12)", शून्य, "Erase(12), Get Performance",
            "Read DVD structure", "Write and verify(12)",
/* af-b1 */ "Verify(12)", "Search data high(12)", "Search data equal(12)",
/* b2-b4 */ "Search data low(12)", "Set limits(12)",
            "Read element status attached",
/* b5-b6 */ "Security protocol out", "Send volume tag, set streaming",
/* b7-b9 */ "Read defect data(12)", "Read element status", "Read CD msf",
/* ba-bc */ "Redundancy group (in), Scan",
            "Redundancy group (out), Set cd-rom speed", "Spare (in), Play cd",
/* bd-bf */ "Spare (out), Mechanism status", "Volume set (in), Read cd",
            "Volume set (out), Send DVD structure",
पूर्ण;

अटल स्थिर काष्ठा value_name_pair मुख्यt_in_arr[] = अणु
	अणु0x5, "Report identifying information"पूर्ण,
	अणु0xa, "Report target port groups"पूर्ण,
	अणु0xb, "Report aliases"पूर्ण,
	अणु0xc, "Report supported operation codes"पूर्ण,
	अणु0xd, "Report supported task management functions"पूर्ण,
	अणु0xe, "Report priority"पूर्ण,
	अणु0xf, "Report timestamp"पूर्ण,
	अणु0x10, "Management protocol in"पूर्ण,
पूर्ण;
#घोषणा MAINT_IN_SZ ARRAY_SIZE(मुख्यt_in_arr)

अटल स्थिर काष्ठा value_name_pair मुख्यt_out_arr[] = अणु
	अणु0x6, "Set identifying information"पूर्ण,
	अणु0xa, "Set target port groups"पूर्ण,
	अणु0xb, "Change aliases"पूर्ण,
	अणु0xc, "Remove I_T nexus"पूर्ण,
	अणु0xe, "Set priority"पूर्ण,
	अणु0xf, "Set timestamp"पूर्ण,
	अणु0x10, "Management protocol out"पूर्ण,
पूर्ण;
#घोषणा MAINT_OUT_SZ ARRAY_SIZE(मुख्यt_out_arr)

अटल स्थिर काष्ठा value_name_pair serv_in12_arr[] = अणु
	अणु0x1, "Read media serial number"पूर्ण,
पूर्ण;
#घोषणा SERV_IN12_SZ ARRAY_SIZE(serv_in12_arr)

अटल स्थिर काष्ठा value_name_pair serv_out12_arr[] = अणु
	अणु-1, "dummy entry"पूर्ण,
पूर्ण;
#घोषणा SERV_OUT12_SZ ARRAY_SIZE(serv_out12_arr)

अटल स्थिर काष्ठा value_name_pair serv_bidi_arr[] = अणु
	अणु-1, "dummy entry"पूर्ण,
पूर्ण;
#घोषणा SERV_BIDI_SZ ARRAY_SIZE(serv_bidi_arr)

अटल स्थिर काष्ठा value_name_pair serv_in16_arr[] = अणु
	अणु0x10, "Read capacity(16)"पूर्ण,
	अणु0x11, "Read long(16)"पूर्ण,
	अणु0x12, "Get LBA status"पूर्ण,
	अणु0x13, "Report referrals"पूर्ण,
पूर्ण;
#घोषणा SERV_IN16_SZ ARRAY_SIZE(serv_in16_arr)

अटल स्थिर काष्ठा value_name_pair serv_out16_arr[] = अणु
	अणु0x11, "Write long(16)"पूर्ण,
	अणु0x1f, "Notify data transfer device(16)"पूर्ण,
पूर्ण;
#घोषणा SERV_OUT16_SZ ARRAY_SIZE(serv_out16_arr)

अटल स्थिर काष्ठा value_name_pair pr_in_arr[] = अणु
	अणु0x0, "Persistent reserve in, read keys"पूर्ण,
	अणु0x1, "Persistent reserve in, read reservation"पूर्ण,
	अणु0x2, "Persistent reserve in, report capabilities"पूर्ण,
	अणु0x3, "Persistent reserve in, read full status"पूर्ण,
पूर्ण;
#घोषणा PR_IN_SZ ARRAY_SIZE(pr_in_arr)

अटल स्थिर काष्ठा value_name_pair pr_out_arr[] = अणु
	अणु0x0, "Persistent reserve out, register"पूर्ण,
	अणु0x1, "Persistent reserve out, reserve"पूर्ण,
	अणु0x2, "Persistent reserve out, release"पूर्ण,
	अणु0x3, "Persistent reserve out, clear"पूर्ण,
	अणु0x4, "Persistent reserve out, preempt"पूर्ण,
	अणु0x5, "Persistent reserve out, preempt and abort"पूर्ण,
	अणु0x6, "Persistent reserve out, register and ignore existing key"पूर्ण,
	अणु0x7, "Persistent reserve out, register and move"पूर्ण,
पूर्ण;
#घोषणा PR_OUT_SZ ARRAY_SIZE(pr_out_arr)

/* SPC-4 rev 34 नामd the Extended Copy opcode to Third Party Copy Out.
   LID1 (List Identअगरier length: 1 byte) is the Extended Copy found in SPC-2
   and SPC-3 */
अटल स्थिर काष्ठा value_name_pair tpc_out_arr[] = अणु
	अणु0x0, "Extended copy(LID1)"पूर्ण,
	अणु0x1, "Extended copy(LID4)"पूर्ण,
	अणु0x10, "Populate token"पूर्ण,
	अणु0x11, "Write using token"पूर्ण,
	अणु0x1c, "Copy operation abort"पूर्ण,
पूर्ण;
#घोषणा TPC_OUT_SZ ARRAY_SIZE(tpc_out_arr)

अटल स्थिर काष्ठा value_name_pair tpc_in_arr[] = अणु
	अणु0x0, "Receive copy status(LID1)"पूर्ण,
	अणु0x1, "Receive copy data(LID1)"पूर्ण,
	अणु0x3, "Receive copy operating parameters"पूर्ण,
	अणु0x4, "Receive copy failure details(LID1)"पूर्ण,
	अणु0x5, "Receive copy status(LID4)"पूर्ण,
	अणु0x6, "Receive copy data(LID4)"पूर्ण,
	अणु0x7, "Receive ROD token information"पूर्ण,
	अणु0x8, "Report all ROD tokens"पूर्ण,
पूर्ण;
#घोषणा TPC_IN_SZ ARRAY_SIZE(tpc_in_arr)


अटल स्थिर काष्ठा value_name_pair variable_length_arr[] = अणु
	अणु0x1, "Rebuild(32)"पूर्ण,
	अणु0x2, "Regenerate(32)"पूर्ण,
	अणु0x3, "Xdread(32)"पूर्ण,
	अणु0x4, "Xdwrite(32)"पूर्ण,
	अणु0x5, "Xdwrite extended(32)"पूर्ण,
	अणु0x6, "Xpwrite(32)"पूर्ण,
	अणु0x7, "Xdwriteread(32)"पूर्ण,
	अणु0x8, "Xdwrite extended(64)"पूर्ण,
	अणु0x9, "Read(32)"पूर्ण,
	अणु0xa, "Verify(32)"पूर्ण,
	अणु0xb, "Write(32)"पूर्ण,
	अणु0xc, "Write an verify(32)"पूर्ण,
	अणु0xd, "Write same(32)"पूर्ण,
	अणु0x8801, "Format OSD"पूर्ण,
	अणु0x8802, "Create (osd)"पूर्ण,
	अणु0x8803, "List (osd)"पूर्ण,
	अणु0x8805, "Read (osd)"पूर्ण,
	अणु0x8806, "Write (osd)"पूर्ण,
	अणु0x8807, "Append (osd)"पूर्ण,
	अणु0x8808, "Flush (osd)"पूर्ण,
	अणु0x880a, "Remove (osd)"पूर्ण,
	अणु0x880b, "Create partition (osd)"पूर्ण,
	अणु0x880c, "Remove partition (osd)"पूर्ण,
	अणु0x880e, "Get attributes (osd)"पूर्ण,
	अणु0x880f, "Set attributes (osd)"पूर्ण,
	अणु0x8812, "Create and write (osd)"पूर्ण,
	अणु0x8815, "Create collection (osd)"पूर्ण,
	अणु0x8816, "Remove collection (osd)"पूर्ण,
	अणु0x8817, "List collection (osd)"पूर्ण,
	अणु0x8818, "Set key (osd)"पूर्ण,
	अणु0x8819, "Set master key (osd)"पूर्ण,
	अणु0x881a, "Flush collection (osd)"पूर्ण,
	अणु0x881b, "Flush partition (osd)"पूर्ण,
	अणु0x881c, "Flush OSD"पूर्ण,
	अणु0x8f7e, "Perform SCSI command (osd)"पूर्ण,
	अणु0x8f7f, "Perform task management function (osd)"पूर्ण,
पूर्ण;
#घोषणा VARIABLE_LENGTH_SZ ARRAY_SIZE(variable_length_arr)

अटल काष्ठा sa_name_list sa_names_arr[] = अणु
	अणुVARIABLE_LENGTH_CMD, variable_length_arr, VARIABLE_LENGTH_SZपूर्ण,
	अणुMAINTEन_अंकCE_IN, मुख्यt_in_arr, MAINT_IN_SZपूर्ण,
	अणुMAINTEन_अंकCE_OUT, मुख्यt_out_arr, MAINT_OUT_SZपूर्ण,
	अणुPERSISTENT_RESERVE_IN, pr_in_arr, PR_IN_SZपूर्ण,
	अणुPERSISTENT_RESERVE_OUT, pr_out_arr, PR_OUT_SZपूर्ण,
	अणुSERVICE_ACTION_IN_12, serv_in12_arr, SERV_IN12_SZपूर्ण,
	अणुSERVICE_ACTION_OUT_12, serv_out12_arr, SERV_OUT12_SZपूर्ण,
	अणुSERVICE_ACTION_BIसूचीECTIONAL, serv_bidi_arr, SERV_BIDI_SZपूर्ण,
	अणुSERVICE_ACTION_IN_16, serv_in16_arr, SERV_IN16_SZपूर्ण,
	अणुSERVICE_ACTION_OUT_16, serv_out16_arr, SERV_OUT16_SZपूर्ण,
	अणुTHIRD_PARTY_COPY_IN, tpc_in_arr, TPC_IN_SZपूर्ण,
	अणुTHIRD_PARTY_COPY_OUT, tpc_out_arr, TPC_OUT_SZपूर्ण,
	अणु0, शून्य, 0पूर्ण,
पूर्ण;

bool scsi_opcode_sa_name(पूर्णांक opcode, पूर्णांक service_action,
			 स्थिर अक्षर **cdb_name, स्थिर अक्षर **sa_name)
अणु
	काष्ठा sa_name_list *sa_name_ptr;
	स्थिर काष्ठा value_name_pair *arr = शून्य;
	पूर्णांक arr_sz, k;

	*cdb_name = शून्य;
	अगर (opcode >= VENDOR_SPECIFIC_CDB)
		वापस false;

	अगर (opcode < ARRAY_SIZE(cdb_byte0_names))
		*cdb_name = cdb_byte0_names[opcode];

	क्रम (sa_name_ptr = sa_names_arr; sa_name_ptr->arr; ++sa_name_ptr) अणु
		अगर (sa_name_ptr->opcode == opcode) अणु
			arr = sa_name_ptr->arr;
			arr_sz = sa_name_ptr->arr_sz;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!arr)
		वापस false;

	क्रम (k = 0; k < arr_sz; ++k, ++arr) अणु
		अगर (service_action == arr->value)
			अवरोध;
	पूर्ण
	अगर (k < arr_sz)
		*sa_name = arr->name;

	वापस true;
पूर्ण

काष्ठा error_info अणु
	अचिन्हित लघु code12;	/* 0x0302 looks better than 0x03,0x02 */
	अचिन्हित लघु size;
पूर्ण;

/*
 * There are 700+ entries in this table. To save space, we करोn't store
 * (code, poपूर्णांकer) pairs, which would make माप(काष्ठा
 * error_info)==16 on 64 bits. Rather, the second element just stores
 * the size (including \0) of the corresponding string, and we use the
 * sum of these to get the appropriate offset पूर्णांकo additional_text
 * defined below. This approach saves 12 bytes per entry.
 */
अटल स्थिर काष्ठा error_info additional[] =
अणु
#घोषणा SENSE_CODE(c, s) अणुc, माप(s)पूर्ण,
#समावेश "sense_codes.h"
#अघोषित SENSE_CODE
पूर्ण;

अटल स्थिर अक्षर *additional_text =
#घोषणा SENSE_CODE(c, s) s "\0"
#समावेश "sense_codes.h"
#अघोषित SENSE_CODE
	;

काष्ठा error_info2 अणु
	अचिन्हित अक्षर code1, code2_min, code2_max;
	स्थिर अक्षर * str;
	स्थिर अक्षर * fmt;
पूर्ण;

अटल स्थिर काष्ठा error_info2 additional2[] =
अणु
	अणु0x40, 0x00, 0x7f, "Ram failure", ""पूर्ण,
	अणु0x40, 0x80, 0xff, "Diagnostic failure on component", ""पूर्ण,
	अणु0x41, 0x00, 0xff, "Data path failure", ""पूर्ण,
	अणु0x42, 0x00, 0xff, "Power-on or self-test failure", ""पूर्ण,
	अणु0x4D, 0x00, 0xff, "Tagged overlapped commands", "task tag "पूर्ण,
	अणु0x70, 0x00, 0xff, "Decompression exception", "short algorithm id of "पूर्ण,
	अणु0, 0, 0, शून्य, शून्यपूर्ण
पूर्ण;

/* description of the sense key values */
अटल स्थिर अक्षर * स्थिर snstext[] = अणु
	"No Sense",	    /* 0: There is no sense inक्रमmation */
	"Recovered Error",  /* 1: The last command completed successfully
				  but used error correction */
	"Not Ready",	    /* 2: The addressed target is not पढ़ोy */
	"Medium Error",	    /* 3: Data error detected on the medium */
	"Hardware Error",   /* 4: Controller or device failure */
	"Illegal Request",  /* 5: Error in request */
	"Unit Attention",   /* 6: Removable medium was changed, or
				  the target has been reset, or ... */
	"Data Protect",	    /* 7: Access to the data is blocked */
	"Blank Check",	    /* 8: Reached unexpected written or unwritten
				  region of the medium */
	"Vendor Specific(9)",
	"Copy Aborted",	    /* A: COPY or COMPARE was पातed */
	"Aborted Command",  /* B: The target पातed the command */
	"Equal",	    /* C: A SEARCH DATA command found data equal,
				  reserved in SPC-4 rev 36 */
	"Volume Overflow",  /* D: Medium full with still data to be written */
	"Miscompare",	    /* E: Source data and data on the medium
				  करो not agree */
	"Completed",	    /* F: command completed sense data reported,
				  may occur क्रम successful command */
पूर्ण;

/* Get sense key string or शून्य अगर not available */
स्थिर अक्षर *
scsi_sense_key_string(अचिन्हित अक्षर key)
अणु
	अगर (key < ARRAY_SIZE(snstext))
		वापस snstext[key];
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(scsi_sense_key_string);

/*
 * Get additional sense code string or शून्य अगर not available.
 * This string may contain a "%x" and should be prपूर्णांकed with ascq as arg.
 */
स्थिर अक्षर *
scsi_extd_sense_क्रमmat(अचिन्हित अक्षर asc, अचिन्हित अक्षर ascq, स्थिर अक्षर **fmt)
अणु
	पूर्णांक i;
	अचिन्हित लघु code = ((asc << 8) | ascq);
	अचिन्हित offset = 0;

	*fmt = शून्य;
	क्रम (i = 0; i < ARRAY_SIZE(additional); i++) अणु
		अगर (additional[i].code12 == code)
			वापस additional_text + offset;
		offset += additional[i].size;
	पूर्ण
	क्रम (i = 0; additional2[i].fmt; i++) अणु
		अगर (additional2[i].code1 == asc &&
		    ascq >= additional2[i].code2_min &&
		    ascq <= additional2[i].code2_max) अणु
			*fmt = additional2[i].fmt;
			वापस additional2[i].str;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(scsi_extd_sense_क्रमmat);

अटल स्थिर अक्षर * स्थिर hostbyte_table[]=अणु
"DID_OK", "DID_NO_CONNECT", "DID_BUS_BUSY", "DID_TIME_OUT", "DID_BAD_TARGET",
"DID_ABORT", "DID_PARITY", "DID_ERROR", "DID_RESET", "DID_BAD_INTR",
"DID_PASSTHROUGH", "DID_SOFT_ERROR", "DID_IMM_RETRY", "DID_REQUEUE",
"DID_TRANSPORT_DISRUPTED", "DID_TRANSPORT_FAILFAST", "DID_TARGET_FAILURE",
"DID_NEXUS_FAILURE", "DID_ALLOC_FAILURE", "DID_MEDIUM_ERROR" पूर्ण;

अटल स्थिर अक्षर * स्थिर driverbyte_table[]=अणु
"DRIVER_OK", "DRIVER_BUSY", "DRIVER_SOFT",  "DRIVER_MEDIA", "DRIVER_ERROR",
"DRIVER_INVALID", "DRIVER_TIMEOUT", "DRIVER_HARD", "DRIVER_SENSE"पूर्ण;

स्थिर अक्षर *scsi_hostbyte_string(पूर्णांक result)
अणु
	स्थिर अक्षर *hb_string = शून्य;
	पूर्णांक hb = host_byte(result);

	अगर (hb < ARRAY_SIZE(hostbyte_table))
		hb_string = hostbyte_table[hb];
	वापस hb_string;
पूर्ण
EXPORT_SYMBOL(scsi_hostbyte_string);

स्थिर अक्षर *scsi_driverbyte_string(पूर्णांक result)
अणु
	स्थिर अक्षर *db_string = शून्य;
	पूर्णांक db = driver_byte(result);

	अगर (db < ARRAY_SIZE(driverbyte_table))
		db_string = driverbyte_table[db];
	वापस db_string;
पूर्ण
EXPORT_SYMBOL(scsi_driverbyte_string);

#घोषणा scsi_mlवापस_name(result)	अणु result, #result पूर्ण
अटल स्थिर काष्ठा value_name_pair scsi_mlवापस_arr[] = अणु
	scsi_mlवापस_name(NEEDS_RETRY),
	scsi_mlवापस_name(SUCCESS),
	scsi_mlवापस_name(FAILED),
	scsi_mlवापस_name(QUEUED),
	scsi_mlवापस_name(SOFT_ERROR),
	scsi_mlवापस_name(ADD_TO_MLQUEUE),
	scsi_mlवापस_name(TIMEOUT_ERROR),
	scsi_mlवापस_name(SCSI_RETURN_NOT_HANDLED),
	scsi_mlवापस_name(FAST_IO_FAIL)
पूर्ण;

स्थिर अक्षर *scsi_mlवापस_string(पूर्णांक result)
अणु
	स्थिर काष्ठा value_name_pair *arr = scsi_mlवापस_arr;
	पूर्णांक k;

	क्रम (k = 0; k < ARRAY_SIZE(scsi_mlवापस_arr); ++k, ++arr) अणु
		अगर (result == arr->value)
			वापस arr->name;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(scsi_mlवापस_string);
