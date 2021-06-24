<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   fs/cअगरs/neपंचांगisc.c
 *
 *   Copyright (c) International Business Machines  Corp., 2002,2008
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 *   Error mapping routines from Samba libsmb/errormap.c
 *   Copyright (C) Andrew Tridgell 2001
 */

#समावेश <linux/net.h>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/fs.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/inet.h>
#समावेश "cifsfs.h"
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "smberr.h"
#समावेश "cifs_debug.h"
#समावेश "nterr.h"

काष्ठा smb_to_posix_error अणु
	__u16 smb_err;
	पूर्णांक posix_code;
पूर्ण;

अटल स्थिर काष्ठा smb_to_posix_error mapping_table_ERRDOS[] = अणु
	अणुERRbadfunc, -EINVALपूर्ण,
	अणुERRbadfile, -ENOENTपूर्ण,
	अणुERRbadpath, -ENOTसूचीपूर्ण,
	अणुERRnofids, -EMखातापूर्ण,
	अणुERRnoaccess, -EACCESपूर्ण,
	अणुERRbadfid, -EBADFपूर्ण,
	अणुERRbadmcb, -EIOपूर्ण,
	अणुERRnomem, -EREMOTEIOपूर्ण,
	अणुERRbadmem, -EFAULTपूर्ण,
	अणुERRbadenv, -EFAULTपूर्ण,
	अणुERRbadक्रमmat, -EINVALपूर्ण,
	अणुERRbadaccess, -EACCESपूर्ण,
	अणुERRbaddata, -EIOपूर्ण,
	अणुERRbaddrive, -ENXIOपूर्ण,
	अणुERRremcd, -EACCESपूर्ण,
	अणुERRdअगरfdevice, -EXDEVपूर्ण,
	अणुERRnofiles, -ENOENTपूर्ण,
	अणुERRग_लिखोprot, -EROFSपूर्ण,
	अणुERRbadshare, -EBUSYपूर्ण,
	अणुERRlock, -EACCESपूर्ण,
	अणुERRunsup, -EINVALपूर्ण,
	अणुERRnosuchshare, -ENXIOपूर्ण,
	अणुERRfilexists, -EEXISTपूर्ण,
	अणुERRinvparm, -EINVALपूर्ण,
	अणुERRdiskfull, -ENOSPCपूर्ण,
	अणुERRinvname, -ENOENTपूर्ण,
	अणुERRinvlevel, -EOPNOTSUPPपूर्ण,
	अणुERRdirnotempty, -ENOTEMPTYपूर्ण,
	अणुERRnotlocked, -ENOLCKपूर्ण,
	अणुERRcancelviolation, -ENOLCKपूर्ण,
	अणुERRalपढ़ोyexists, -EEXISTपूर्ण,
	अणुERRmoredata, -EOVERFLOWपूर्ण,
	अणुERReasnotsupported, -EOPNOTSUPPपूर्ण,
	अणुErrQuota, -EDQUOTपूर्ण,
	अणुErrNotALink, -ENOLINKपूर्ण,
	अणुERRnetlogonNotStarted, -ENOPROTOOPTपूर्ण,
	अणुERRsymlink, -EOPNOTSUPPपूर्ण,
	अणुErrTooManyLinks, -EMLINKपूर्ण,
	अणु0, 0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा smb_to_posix_error mapping_table_ERRSRV[] = अणु
	अणुERRerror, -EIOपूर्ण,
	अणुERRbadpw, -EACCESपूर्ण,  /* was EPERM */
	अणुERRbadtype, -EREMOTEपूर्ण,
	अणुERRaccess, -EACCESपूर्ण,
	अणुERRinvtid, -ENXIOपूर्ण,
	अणुERRinvnetname, -ENXIOपूर्ण,
	अणुERRinvdevice, -ENXIOपूर्ण,
	अणुERRqfull, -ENOSPCपूर्ण,
	अणुERRqtoobig, -ENOSPCपूर्ण,
	अणुERRqeof, -EIOपूर्ण,
	अणुERRinvpfid, -EBADFपूर्ण,
	अणुERRsmbcmd, -EBADRQCपूर्ण,
	अणुERRsrverror, -EIOपूर्ण,
	अणुERRbadBID, -EIOपूर्ण,
	अणुERRfilespecs, -EINVALपूर्ण,
	अणुERRbadLink, -EIOपूर्ण,
	अणुERRbadpermits, -EINVALपूर्ण,
	अणुERRbadPID, -ESRCHपूर्ण,
	अणुERRsetattrmode, -EINVALपूर्ण,
	अणुERRछोड़ोd, -EHOSTDOWNपूर्ण,
	अणुERRmsgoff, -EHOSTDOWNपूर्ण,
	अणुERRnoroom, -ENOSPCपूर्ण,
	अणुERRrmuns, -EUSERSपूर्ण,
	अणुERRसमयout, -ETIMEपूर्ण,
	अणुERRnoresource, -EREMOTEIOपूर्ण,
	अणुERRtoomanyuids, -EUSERSपूर्ण,
	अणुERRbaduid, -EACCESपूर्ण,
	अणुERRusempx, -EIOपूर्ण,
	अणुERRusestd, -EIOपूर्ण,
	अणुERR_NOTIFY_ENUM_सूची, -ENOBUFSपूर्ण,
	अणुERRnoSuchUser, -EACCESपूर्ण,
/*	अणुERRaccountexpired, -EACCESपूर्ण,
	अणुERRbadclient, -EACCESपूर्ण,
	अणुERRbadLogonTime, -EACCESपूर्ण,
	अणुERRpasswordExpired, -EACCESपूर्ण,*/
	अणुERRaccountexpired, -EKEYEXPIREDपूर्ण,
	अणुERRbadclient, -EACCESपूर्ण,
	अणुERRbadLogonTime, -EACCESपूर्ण,
	अणुERRpasswordExpired, -EKEYEXPIREDपूर्ण,

	अणुERRnosupport, -EINVALपूर्ण,
	अणु0, 0पूर्ण
पूर्ण;

/*
 * Convert a string containing text IPv4 or IPv6 address to binary क्रमm.
 *
 * Returns 0 on failure.
 */
अटल पूर्णांक
cअगरs_inet_pton(स्थिर पूर्णांक address_family, स्थिर अक्षर *cp, पूर्णांक len, व्योम *dst)
अणु
	पूर्णांक ret = 0;

	/* calculate length by finding first slash or शून्य */
	अगर (address_family == AF_INET)
		ret = in4_pton(cp, len, dst, '\\', शून्य);
	अन्यथा अगर (address_family == AF_INET6)
		ret = in6_pton(cp, len, dst , '\\', शून्य);

	cअगरs_dbg(NOISY, "address conversion returned %d for %*.*s\n",
		 ret, len, len, cp);
	अगर (ret > 0)
		ret = 1;
	वापस ret;
पूर्ण

/*
 * Try to convert a string to an IPv4 address and then attempt to convert
 * it to an IPv6 address अगर that fails. Set the family field अगर either
 * succeeds. If it's an IPv6 address and it has a '%' sign in it, try to
 * treat the part following it as a numeric sin6_scope_id.
 *
 * Returns 0 on failure.
 */
पूर्णांक
cअगरs_convert_address(काष्ठा sockaddr *dst, स्थिर अक्षर *src, पूर्णांक len)
अणु
	पूर्णांक rc, alen, slen;
	स्थिर अक्षर *pct;
	अक्षर scope_id[13];
	काष्ठा sockaddr_in *s4 = (काष्ठा sockaddr_in *) dst;
	काष्ठा sockaddr_in6 *s6 = (काष्ठा sockaddr_in6 *) dst;

	/* IPv4 address */
	अगर (cअगरs_inet_pton(AF_INET, src, len, &s4->sin_addr.s_addr)) अणु
		s4->sin_family = AF_INET;
		वापस 1;
	पूर्ण

	/* attempt to exclude the scope ID from the address part */
	pct = स_प्रथम(src, '%', len);
	alen = pct ? pct - src : len;

	rc = cअगरs_inet_pton(AF_INET6, src, alen, &s6->sin6_addr.s6_addr);
	अगर (!rc)
		वापस rc;

	s6->sin6_family = AF_INET6;
	अगर (pct) अणु
		/* grab the scope ID */
		slen = len - (alen + 1);
		अगर (slen <= 0 || slen > 12)
			वापस 0;
		स_नकल(scope_id, pct + 1, slen);
		scope_id[slen] = '\0';

		rc = kstrtouपूर्णांक(scope_id, 0, &s6->sin6_scope_id);
		rc = (rc == 0) ? 1 : 0;
	पूर्ण

	वापस rc;
पूर्ण

व्योम
cअगरs_set_port(काष्ठा sockaddr *addr, स्थिर अचिन्हित लघु पूर्णांक port)
अणु
	चयन (addr->sa_family) अणु
	हाल AF_INET:
		((काष्ठा sockaddr_in *)addr)->sin_port = htons(port);
		अवरोध;
	हाल AF_INET6:
		((काष्ठा sockaddr_in6 *)addr)->sin6_port = htons(port);
		अवरोध;
	पूर्ण
पूर्ण

/*****************************************************************************
convert a NT status code to a करोs class/code
 *****************************************************************************/
/* NT status -> करोs error map */
अटल स्थिर काष्ठा अणु
	__u8 करोs_class;
	__u16 करोs_code;
	__u32 ntstatus;
पूर्ण ntstatus_to_करोs_map[] = अणु
	अणु
	ERRDOS, ERRgeneral, NT_STATUS_UNSUCCESSFULपूर्ण, अणु
	ERRDOS, ERRbadfunc, NT_STATUS_NOT_IMPLEMENTEDपूर्ण, अणु
	ERRDOS, ERRinvlevel, NT_STATUS_INVALID_INFO_CLASSपूर्ण, अणु
	ERRDOS, 24, NT_STATUS_INFO_LENGTH_MISMATCHपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ACCESS_VIOLATIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_IN_PAGE_ERRORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PAGEखाता_QUOTAपूर्ण, अणु
	ERRDOS, ERRbadfid, NT_STATUS_INVALID_HANDLEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BAD_INITIAL_STACKपूर्ण, अणु
	ERRDOS, 193, NT_STATUS_BAD_INITIAL_PCपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_CIDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_TIMER_NOT_CANCELEDपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETERपूर्ण, अणु
	ERRDOS, ERRbadfile, NT_STATUS_NO_SUCH_DEVICEपूर्ण, अणु
	ERRDOS, ERRbadfile, NT_STATUS_NO_SUCH_खातापूर्ण, अणु
	ERRDOS, ERRbadfunc, NT_STATUS_INVALID_DEVICE_REQUESTपूर्ण, अणु
	ERRDOS, 38, NT_STATUS_END_OF_खातापूर्ण, अणु
	ERRDOS, 34, NT_STATUS_WRONG_VOLUMEपूर्ण, अणु
	ERRDOS, 21, NT_STATUS_NO_MEDIA_IN_DEVICEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNRECOGNIZED_MEDIAपूर्ण, अणु
	ERRDOS, 27, NT_STATUS_NONEXISTENT_SECTORपूर्ण,
/*	अणु This NT error code was 'sqashed'
	 from NT_STATUS_MORE_PROCESSING_REQUIRED to NT_STATUS_OK
	 during the session setup पूर्ण */
	अणु
	ERRDOS, ERRnomem, NT_STATUS_NO_MEMORYपूर्ण, अणु
	ERRDOS, 487, NT_STATUS_CONFLICTING_ADDRESSESपूर्ण, अणु
	ERRDOS, 487, NT_STATUS_NOT_MAPPED_VIEWपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_UNABLE_TO_FREE_VMपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_UNABLE_TO_DELETE_SECTIONपूर्ण, अणु
	ERRDOS, 2142, NT_STATUS_INVALID_SYSTEM_SERVICEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ILLEGAL_INSTRUCTIONपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_INVALID_LOCK_SEQUENCEपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_INVALID_VIEW_SIZEपूर्ण, अणु
	ERRDOS, 193, NT_STATUS_INVALID_खाता_FOR_SECTIONपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_ALREADY_COMMITTEDपूर्ण,
/*	अणु This NT error code was 'sqashed'
	 from NT_STATUS_ACCESS_DENIED to NT_STATUS_TRUSTED_RELATIONSHIP_FAILURE
	 during the session setup पूर्ण   */
	अणु
	ERRDOS, ERRnoaccess, NT_STATUS_ACCESS_DENIEDपूर्ण, अणु
	ERRDOS, 111, NT_STATUS_BUFFER_TOO_SMALLपूर्ण, अणु
	ERRDOS, ERRbadfid, NT_STATUS_OBJECT_TYPE_MISMATCHपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NONCONTINUABLE_EXCEPTIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_DISPOSITIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNWINDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BAD_STACKपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_UNWIND_TARGETपूर्ण, अणु
	ERRDOS, 158, NT_STATUS_NOT_LOCKEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PARITY_ERRORपूर्ण, अणु
	ERRDOS, 487, NT_STATUS_UNABLE_TO_DECOMMIT_VMपूर्ण, अणु
	ERRDOS, 487, NT_STATUS_NOT_COMMITTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_PORT_ATTRIBUTESपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PORT_MESSAGE_TOO_LONGपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_MIXपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_QUOTA_LOWERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DISK_CORRUPT_ERRORपूर्ण, अणु
	 /* mapping changed since shell करोes lookup on * expects FileNotFound */
	ERRDOS, ERRbadfile, NT_STATUS_OBJECT_NAME_INVALIDपूर्ण, अणु
	ERRDOS, ERRbadfile, NT_STATUS_OBJECT_NAME_NOT_FOUNDपूर्ण, अणु
	ERRDOS, ERRalपढ़ोyexists, NT_STATUS_OBJECT_NAME_COLLISIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_HANDLE_NOT_WAITABLEपूर्ण, अणु
	ERRDOS, ERRbadfid, NT_STATUS_PORT_DISCONNECTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DEVICE_ALREADY_ATTACHEDपूर्ण, अणु
	ERRDOS, 161, NT_STATUS_OBJECT_PATH_INVALIDपूर्ण, अणु
	ERRDOS, ERRbadpath, NT_STATUS_OBJECT_PATH_NOT_FOUNDपूर्ण, अणु
	ERRDOS, 161, NT_STATUS_OBJECT_PATH_SYNTAX_BADपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DATA_OVERRUNपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DATA_LATE_ERRORपूर्ण, अणु
	ERRDOS, 23, NT_STATUS_DATA_ERRORपूर्ण, अणु
	ERRDOS, 23, NT_STATUS_CRC_ERRORपूर्ण, अणु
	ERRDOS, ERRnomem, NT_STATUS_SECTION_TOO_BIGपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_PORT_CONNECTION_REFUSEDपूर्ण, अणु
	ERRDOS, ERRbadfid, NT_STATUS_INVALID_PORT_HANDLEपूर्ण, अणु
	ERRDOS, ERRbadshare, NT_STATUS_SHARING_VIOLATIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_QUOTA_EXCEEDEDपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PAGE_PROTECTIONपूर्ण, अणु
	ERRDOS, 288, NT_STATUS_MUTANT_NOT_OWNEDपूर्ण, अणु
	ERRDOS, 298, NT_STATUS_SEMAPHORE_LIMIT_EXCEEDEDपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_PORT_ALREADY_SETपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_SECTION_NOT_IMAGEपूर्ण, अणु
	ERRDOS, 156, NT_STATUS_SUSPEND_COUNT_EXCEEDEDपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_THREAD_IS_TERMINATINGपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_BAD_WORKING_SET_LIMITपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INCOMPATIBLE_खाता_MAPपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_SECTION_PROTECTIONपूर्ण, अणु
	ERRDOS, ERReasnotsupported, NT_STATUS_EAS_NOT_SUPPORTEDपूर्ण, अणु
	ERRDOS, 255, NT_STATUS_EA_TOO_LARGEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NONEXISTENT_EA_ENTRYपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_EAS_ON_खातापूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_EA_CORRUPT_ERRORपूर्ण, अणु
	ERRDOS, ERRlock, NT_STATUS_खाता_LOCK_CONFLICTपूर्ण, अणु
	ERRDOS, ERRlock, NT_STATUS_LOCK_NOT_GRANTEDपूर्ण, अणु
	ERRDOS, ERRbadfile, NT_STATUS_DELETE_PENDINGपूर्ण, अणु
	ERRDOS, ERRunsup, NT_STATUS_CTL_खाता_NOT_SUPPORTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNKNOWN_REVISIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_REVISION_MISMATCHपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_OWNERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_PRIMARY_GROUPपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_IMPERSONATION_TOKENपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CANT_DISABLE_MANDATORYपूर्ण, अणु
	ERRDOS, 2215, NT_STATUS_NO_LOGON_SERVERSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_SUCH_LOGON_SESSIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_SUCH_PRIVILEGEपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_PRIVILEGE_NOT_HELDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_ACCOUNT_NAMEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_USER_EXISTSपूर्ण,
/*	अणु This NT error code was 'sqashed'
	 from NT_STATUS_NO_SUCH_USER to NT_STATUS_LOGON_FAILURE
	 during the session setup पूर्ण */
	अणु
	ERRDOS, ERRnoaccess, NT_STATUS_NO_SUCH_USERपूर्ण, अणु /* could map to 2238 */
	ERRHRD, ERRgeneral, NT_STATUS_GROUP_EXISTSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_SUCH_GROUPपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_MEMBER_IN_GROUPपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_MEMBER_NOT_IN_GROUPपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LAST_ADMINपूर्ण,
/*	अणु This NT error code was 'sqashed'
	 from NT_STATUS_WRONG_PASSWORD to NT_STATUS_LOGON_FAILURE
	 during the session setup पूर्ण */
	अणु
	ERRSRV, ERRbadpw, NT_STATUS_WRONG_PASSWORDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ILL_FORMED_PASSWORDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PASSWORD_RESTRICTIONपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_LOGON_FAILUREपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ACCOUNT_RESTRICTIONपूर्ण, अणु
	ERRSRV, ERRbadLogonTime, NT_STATUS_INVALID_LOGON_HOURSपूर्ण, अणु
	ERRSRV, ERRbadclient, NT_STATUS_INVALID_WORKSTATIONपूर्ण, अणु
	ERRSRV, ERRpasswordExpired, NT_STATUS_PASSWORD_EXPIREDपूर्ण, अणु
	ERRSRV, ERRaccountexpired, NT_STATUS_ACCOUNT_DISABLEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NONE_MAPPEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_TOO_MANY_LUIDS_REQUESTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LUIDS_EXHAUSTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_SUB_AUTHORITYपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_ACLपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_SIDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_SECURITY_DESCRपूर्ण, अणु
	ERRDOS, 127, NT_STATUS_PROCEDURE_NOT_FOUNDपूर्ण, अणु
	ERRDOS, 193, NT_STATUS_INVALID_IMAGE_FORMATपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_TOKENपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BAD_INHERITANCE_ACLपूर्ण, अणु
	ERRDOS, 158, NT_STATUS_RANGE_NOT_LOCKEDपूर्ण, अणु
	ERRDOS, 112, NT_STATUS_DISK_FULLपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_SERVER_DISABLEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_SERVER_NOT_DISABLEDपूर्ण, अणु
	ERRDOS, 68, NT_STATUS_TOO_MANY_GUIDS_REQUESTEDपूर्ण, अणु
	ERRDOS, 259, NT_STATUS_GUIDS_EXHAUSTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_ID_AUTHORITYपूर्ण, अणु
	ERRDOS, 259, NT_STATUS_AGENTS_EXHAUSTEDपूर्ण, अणु
	ERRDOS, 154, NT_STATUS_INVALID_VOLUME_LABELपूर्ण, अणु
	ERRDOS, 14, NT_STATUS_SECTION_NOT_EXTENDEDपूर्ण, अणु
	ERRDOS, 487, NT_STATUS_NOT_MAPPED_DATAपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_RESOURCE_DATA_NOT_FOUNDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_RESOURCE_TYPE_NOT_FOUNDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_RESOURCE_NAME_NOT_FOUNDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ARRAY_BOUNDS_EXCEEDEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FLOAT_DENORMAL_OPERANDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FLOAT_DIVIDE_BY_ZEROपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FLOAT_INEXACT_RESULTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FLOAT_INVALID_OPERATIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FLOAT_OVERFLOWपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FLOAT_STACK_CHECKपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FLOAT_UNDERFLOWपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INTEGER_DIVIDE_BY_ZEROपूर्ण, अणु
	ERRDOS, 534, NT_STATUS_INTEGER_OVERFLOWपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PRIVILEGED_INSTRUCTIONपूर्ण, अणु
	ERRDOS, ERRnomem, NT_STATUS_TOO_MANY_PAGING_खाताSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_खाता_INVALIDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ALLOTTED_SPACE_EXCEEDEDपूर्ण,
/*	अणु This NT error code was 'sqashed'
	 from NT_STATUS_INSUFFICIENT_RESOURCES to
	 NT_STATUS_INSUFF_SERVER_RESOURCES during the session setup पूर्ण */
	अणु
	ERRDOS, ERRnoresource, NT_STATUS_INSUFFICIENT_RESOURCESपूर्ण, अणु
	ERRDOS, ERRbadpath, NT_STATUS_DFS_EXIT_PATH_FOUNDपूर्ण, अणु
	ERRDOS, 23, NT_STATUS_DEVICE_DATA_ERRORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DEVICE_NOT_CONNECTEDपूर्ण, अणु
	ERRDOS, 21, NT_STATUS_DEVICE_POWER_FAILUREपूर्ण, अणु
	ERRDOS, 487, NT_STATUS_FREE_VM_NOT_AT_BASEपूर्ण, अणु
	ERRDOS, 487, NT_STATUS_MEMORY_NOT_ALLOCATEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_WORKING_SET_QUOTAपूर्ण, अणु
	ERRDOS, 19, NT_STATUS_MEDIA_WRITE_PROTECTEDपूर्ण, अणु
	ERRDOS, 21, NT_STATUS_DEVICE_NOT_READYपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_GROUP_ATTRIBUTESपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BAD_IMPERSONATION_LEVELपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CANT_OPEN_ANONYMOUSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BAD_VALIDATION_CLASSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BAD_TOKEN_TYPEपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_BAD_MASTER_BOOT_RECORDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INSTRUCTION_MISALIGNMENTपूर्ण, अणु
	ERRDOS, ERRpipebusy, NT_STATUS_INSTANCE_NOT_AVAILABLEपूर्ण, अणु
	ERRDOS, ERRpipebusy, NT_STATUS_PIPE_NOT_AVAILABLEपूर्ण, अणु
	ERRDOS, ERRbadpipe, NT_STATUS_INVALID_PIPE_STATEपूर्ण, अणु
	ERRDOS, ERRpipebusy, NT_STATUS_PIPE_BUSYपूर्ण, अणु
	ERRDOS, ERRbadfunc, NT_STATUS_ILLEGAL_FUNCTIONपूर्ण, अणु
	ERRDOS, ERRnotconnected, NT_STATUS_PIPE_DISCONNECTEDपूर्ण, अणु
	ERRDOS, ERRpipeclosing, NT_STATUS_PIPE_CLOSINGपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PIPE_CONNECTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PIPE_LISTENINGपूर्ण, अणु
	ERRDOS, ERRbadpipe, NT_STATUS_INVALID_READ_MODEपूर्ण, अणु
	ERRDOS, 121, NT_STATUS_IO_TIMEOUTपूर्ण, अणु
	ERRDOS, 38, NT_STATUS_खाता_FORCED_CLOSEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PROFILING_NOT_STARTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PROFILING_NOT_STOPPEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_COULD_NOT_INTERPRETपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_खाता_IS_A_सूचीECTORYपूर्ण, अणु
	ERRDOS, ERRunsup, NT_STATUS_NOT_SUPPORTEDपूर्ण, अणु
	ERRDOS, 51, NT_STATUS_REMOTE_NOT_LISTENINGपूर्ण, अणु
	ERRDOS, 52, NT_STATUS_DUPLICATE_NAMEपूर्ण, अणु
	ERRDOS, 53, NT_STATUS_BAD_NETWORK_PATHपूर्ण, अणु
	ERRDOS, 54, NT_STATUS_NETWORK_BUSYपूर्ण, अणु
	ERRDOS, 55, NT_STATUS_DEVICE_DOES_NOT_EXISTपूर्ण, अणु
	ERRDOS, 56, NT_STATUS_TOO_MANY_COMMANDSपूर्ण, अणु
	ERRDOS, 57, NT_STATUS_ADAPTER_HARDWARE_ERRORपूर्ण, अणु
	ERRDOS, 58, NT_STATUS_INVALID_NETWORK_RESPONSEपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_UNEXPECTED_NETWORK_ERRORपूर्ण, अणु
	ERRDOS, 60, NT_STATUS_BAD_REMOTE_ADAPTERपूर्ण, अणु
	ERRDOS, 61, NT_STATUS_PRINT_QUEUE_FULLपूर्ण, अणु
	ERRDOS, 62, NT_STATUS_NO_SPOOL_SPACEपूर्ण, अणु
	ERRDOS, 63, NT_STATUS_PRINT_CANCELLEDपूर्ण, अणु
	ERRDOS, 64, NT_STATUS_NETWORK_NAME_DELETEDपूर्ण, अणु
	ERRDOS, 65, NT_STATUS_NETWORK_ACCESS_DENIEDपूर्ण, अणु
	ERRDOS, 66, NT_STATUS_BAD_DEVICE_TYPEपूर्ण, अणु
	ERRDOS, ERRnosuchshare, NT_STATUS_BAD_NETWORK_NAMEपूर्ण, अणु
	ERRDOS, 68, NT_STATUS_TOO_MANY_NAMESपूर्ण, अणु
	ERRDOS, 69, NT_STATUS_TOO_MANY_SESSIONSपूर्ण, अणु
	ERRDOS, 70, NT_STATUS_SHARING_PAUSEDपूर्ण, अणु
	ERRDOS, 71, NT_STATUS_REQUEST_NOT_ACCEPTEDपूर्ण, अणु
	ERRDOS, 72, NT_STATUS_REसूचीECTOR_PAUSEDपूर्ण, अणु
	ERRDOS, 88, NT_STATUS_NET_WRITE_FAULTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PROFILING_AT_LIMITपूर्ण, अणु
	ERRDOS, ERRdअगरfdevice, NT_STATUS_NOT_SAME_DEVICEपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_खाता_RENAMEDपूर्ण, अणु
	ERRDOS, 240, NT_STATUS_VIRTUAL_CIRCUIT_CLOSEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_SECURITY_ON_OBJECTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CANT_WAITपूर्ण, अणु
	ERRDOS, ERRpipeclosing, NT_STATUS_PIPE_EMPTYपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CANT_ACCESS_DOMAIN_INFOपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CANT_TERMINATE_SELFपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_SERVER_STATEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_DOMAIN_STATEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_DOMAIN_ROLEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_SUCH_DOMAINपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DOMAIN_EXISTSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DOMAIN_LIMIT_EXCEEDEDपूर्ण, अणु
	ERRDOS, 300, NT_STATUS_OPLOCK_NOT_GRANTEDपूर्ण, अणु
	ERRDOS, 301, NT_STATUS_INVALID_OPLOCK_PROTOCOLपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INTERNAL_DB_CORRUPTIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INTERNAL_ERRORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_GENERIC_NOT_MAPPEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BAD_DESCRIPTOR_FORMATपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_USER_BUFFERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNEXPECTED_IO_ERRORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNEXPECTED_MM_CREATE_ERRपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNEXPECTED_MM_MAP_ERRORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNEXPECTED_MM_EXTEND_ERRपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NOT_LOGON_PROCESSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LOGON_SESSION_EXISTSपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_1पूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_2पूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_3पूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_4पूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_5पूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_6पूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_7पूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_8पूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_9पूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_10पूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_11पूर्ण, अणु
	ERRDOS, 87, NT_STATUS_INVALID_PARAMETER_12पूर्ण, अणु
	ERRDOS, ERRbadpath, NT_STATUS_REसूचीECTOR_NOT_STARTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_REसूचीECTOR_STARTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_STACK_OVERFLOWपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_SUCH_PACKAGEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BAD_FUNCTION_TABLEपूर्ण, अणु
	ERRDOS, 203, 0xc0000100पूर्ण, अणु
	ERRDOS, 145, NT_STATUS_सूचीECTORY_NOT_EMPTYपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_खाता_CORRUPT_ERRORपूर्ण, अणु
	ERRDOS, 267, NT_STATUS_NOT_A_सूचीECTORYपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BAD_LOGON_SESSION_STATEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LOGON_SESSION_COLLISIONपूर्ण, अणु
	ERRDOS, 206, NT_STATUS_NAME_TOO_LONGपूर्ण, अणु
	ERRDOS, 2401, NT_STATUS_खाताS_OPENपूर्ण, अणु
	ERRDOS, 2404, NT_STATUS_CONNECTION_IN_USEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_MESSAGE_NOT_FOUNDपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_PROCESS_IS_TERMINATINGपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_LOGON_TYPEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_GUID_TRANSLATIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CANNOT_IMPERSONATEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_IMAGE_ALREADY_LOADEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ABIOS_NOT_PRESENTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ABIOS_LID_NOT_EXISTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ABIOS_LID_ALREADY_OWNEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ABIOS_NOT_LID_OWNERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ABIOS_INVALID_COMMANDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ABIOS_INVALID_LIDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ABIOS_SELECTOR_NOT_AVAILABLEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ABIOS_INVALID_SELECTORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_LDTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_LDT_SIZEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_LDT_OFFSETपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_LDT_DESCRIPTORपूर्ण, अणु
	ERRDOS, 193, NT_STATUS_INVALID_IMAGE_NE_FORMATपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_RXACT_INVALID_STATEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_RXACT_COMMIT_FAILUREपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_MAPPED_खाता_SIZE_ZEROपूर्ण, अणु
	ERRDOS, ERRnofids, NT_STATUS_TOO_MANY_OPENED_खाताSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CANCELLEDपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_CANNOT_DELETEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_COMPUTER_NAMEपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_खाता_DELETEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_SPECIAL_ACCOUNTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_SPECIAL_GROUPपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_SPECIAL_USERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_MEMBERS_PRIMARY_GROUPपूर्ण, अणु
	ERRDOS, ERRbadfid, NT_STATUS_खाता_CLOSEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_TOO_MANY_THREADSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_THREAD_NOT_IN_PROCESSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_TOKEN_ALREADY_IN_USEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PAGEखाता_QUOTA_EXCEEDEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_COMMITMENT_LIMITपूर्ण, अणु
	ERRDOS, 193, NT_STATUS_INVALID_IMAGE_LE_FORMATपूर्ण, अणु
	ERRDOS, 193, NT_STATUS_INVALID_IMAGE_NOT_MZपूर्ण, अणु
	ERRDOS, 193, NT_STATUS_INVALID_IMAGE_PROTECTपूर्ण, अणु
	ERRDOS, 193, NT_STATUS_INVALID_IMAGE_WIN_16पूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LOGON_SERVER_CONFLICTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_TIME_DIFFERENCE_AT_DCपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_SYNCHRONIZATION_REQUIREDपूर्ण, अणु
	ERRDOS, 126, NT_STATUS_DLL_NOT_FOUNDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_OPEN_FAILEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_IO_PRIVILEGE_FAILEDपूर्ण, अणु
	ERRDOS, 182, NT_STATUS_ORDINAL_NOT_FOUNDपूर्ण, अणु
	ERRDOS, 127, NT_STATUS_ENTRYPOINT_NOT_FOUNDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CONTROL_C_EXITपूर्ण, अणु
	ERRDOS, 64, NT_STATUS_LOCAL_DISCONNECTपूर्ण, अणु
	ERRDOS, 64, NT_STATUS_REMOTE_DISCONNECTपूर्ण, अणु
	ERRDOS, 51, NT_STATUS_REMOTE_RESOURCESपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_LINK_FAILEDपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_LINK_TIMEOUTपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_INVALID_CONNECTIONपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_INVALID_ADDRESSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DLL_INIT_FAILEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_MISSING_SYSTEMखातापूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNHANDLED_EXCEPTIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_APP_INIT_FAILUREपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PAGEखाता_CREATE_FAILEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_PAGEखातापूर्ण, अणु
	ERRDOS, 124, NT_STATUS_INVALID_LEVELपूर्ण, अणु
	ERRDOS, 86, NT_STATUS_WRONG_PASSWORD_COREपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ILLEGAL_FLOAT_CONTEXTपूर्ण, अणु
	ERRDOS, 109, NT_STATUS_PIPE_BROKENपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_REGISTRY_CORRUPTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_REGISTRY_IO_FAILEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_EVENT_PAIRपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNRECOGNIZED_VOLUMEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_SERIAL_NO_DEVICE_INITEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_SUCH_ALIASपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_MEMBER_NOT_IN_ALIASपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_MEMBER_IN_ALIASपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ALIAS_EXISTSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LOGON_NOT_GRANTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_TOO_MANY_SECRETSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_SECRET_TOO_LONGपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INTERNAL_DB_ERRORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FULLSCREEN_MODEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_TOO_MANY_CONTEXT_IDSपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_LOGON_TYPE_NOT_GRANTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NOT_REGISTRY_खातापूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NT_CROSS_ENCRYPTION_REQUIREDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DOMAIN_CTRLR_CONFIG_ERRORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FT_MISSING_MEMBERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ILL_FORMED_SERVICE_ENTRYपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ILLEGAL_CHARACTERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNMAPPABLE_CHARACTERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNDEFINED_CHARACTERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FLOPPY_VOLUMEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FLOPPY_ID_MARK_NOT_FOUNDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FLOPPY_WRONG_CYLINDERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FLOPPY_UNKNOWN_ERRORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FLOPPY_BAD_REGISTERSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DISK_RECALIBRATE_FAILEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DISK_OPERATION_FAILEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DISK_RESET_FAILEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_SHARED_IRQ_BUSYपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FT_ORPHANINGपूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc000016eपूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc000016fपूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc0000170पूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc0000171पूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PARTITION_FAILUREपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_BLOCK_LENGTHपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DEVICE_NOT_PARTITIONEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNABLE_TO_LOCK_MEDIAपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNABLE_TO_UNLOAD_MEDIAपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_EOM_OVERFLOWपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_MEDIAपूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc0000179पूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_SUCH_MEMBERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_MEMBERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_KEY_DELETEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_LOG_SPACEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_TOO_MANY_SIDSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LM_CROSS_ENCRYPTION_REQUIREDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_KEY_HAS_CHILDRENपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CHILD_MUST_BE_VOLATILEपूर्ण, अणु
	ERRDOS, 87, NT_STATUS_DEVICE_CONFIGURATION_ERRORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DRIVER_INTERNAL_ERRORपूर्ण, अणु
	ERRDOS, 22, NT_STATUS_INVALID_DEVICE_STATEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_IO_DEVICE_ERRORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DEVICE_PROTOCOL_ERRORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BACKUP_CONTROLLERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LOG_खाता_FULLपूर्ण, अणु
	ERRDOS, 19, NT_STATUS_TOO_LATEपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_NO_TRUST_LSA_SECRETपूर्ण,
/*	अणु This NT error code was 'sqashed'
	 from NT_STATUS_NO_TRUST_SAM_ACCOUNT to
	 NT_STATUS_TRUSTED_RELATIONSHIP_FAILURE during the session setup पूर्ण */
	अणु
	ERRDOS, ERRnoaccess, NT_STATUS_NO_TRUST_SAM_ACCOUNTपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_TRUSTED_DOMAIN_FAILUREपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_TRUSTED_RELATIONSHIP_FAILUREपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_EVENTLOG_खाता_CORRUPTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_EVENTLOG_CANT_STARTपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_TRUST_FAILUREपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_MUTANT_LIMIT_EXCEEDEDपूर्ण, अणु
	ERRDOS, ERRnetlogonNotStarted, NT_STATUS_NETLOGON_NOT_STARTEDपूर्ण, अणु
	ERRSRV, ERRaccountexpired, NT_STATUS_ACCOUNT_EXPIREDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_POSSIBLE_DEADLOCKपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NETWORK_CREDENTIAL_CONFLICTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_REMOTE_SESSION_LIMITपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_EVENTLOG_खाता_CHANGEDपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_NOLOGON_INTERDOMAIN_TRUST_ACCOUNTपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_NOLOGON_WORKSTATION_TRUST_ACCOUNTपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_NOLOGON_SERVER_TRUST_ACCOUNTपूर्ण,
/*	अणु This NT error code was 'sqashed'
	 from NT_STATUS_DOMAIN_TRUST_INCONSISTENT to NT_STATUS_LOGON_FAILURE
	 during the session setup पूर्ण  */
	अणु
	ERRDOS, ERRnoaccess, NT_STATUS_DOMAIN_TRUST_INCONSISTENTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FS_DRIVER_REQUIREDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_USER_SESSION_KEYपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_USER_SESSION_DELETEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_RESOURCE_LANG_NOT_FOUNDपूर्ण, अणु
	ERRDOS, ERRnoresource, NT_STATUS_INSUFF_SERVER_RESOURCESपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_BUFFER_SIZEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_ADDRESS_COMPONENTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_ADDRESS_WILDCARDपूर्ण, अणु
	ERRDOS, 68, NT_STATUS_TOO_MANY_ADDRESSESपूर्ण, अणु
	ERRDOS, 52, NT_STATUS_ADDRESS_ALREADY_EXISTSपूर्ण, अणु
	ERRDOS, 64, NT_STATUS_ADDRESS_CLOSEDपूर्ण, अणु
	ERRDOS, 64, NT_STATUS_CONNECTION_DISCONNECTEDपूर्ण, अणु
	ERRDOS, 64, NT_STATUS_CONNECTION_RESETपूर्ण, अणु
	ERRDOS, 68, NT_STATUS_TOO_MANY_NODESपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_TRANSACTION_ABORTEDपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_TRANSACTION_TIMED_OUTपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_TRANSACTION_NO_RELEASEपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_TRANSACTION_NO_MATCHपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_TRANSACTION_RESPONDEDपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_TRANSACTION_INVALID_IDपूर्ण, अणु
	ERRDOS, 59, NT_STATUS_TRANSACTION_INVALID_TYPEपूर्ण, अणु
	ERRDOS, ERRunsup, NT_STATUS_NOT_SERVER_SESSIONपूर्ण, अणु
	ERRDOS, ERRunsup, NT_STATUS_NOT_CLIENT_SESSIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CANNOT_LOAD_REGISTRY_खातापूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DEBUG_ATTACH_FAILEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_SYSTEM_PROCESS_TERMINATEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DATA_NOT_ACCEPTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_BROWSER_SERVERS_FOUNDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_VDM_HARD_ERRORपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DRIVER_CANCEL_TIMEOUTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_REPLY_MESSAGE_MISMATCHपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_MAPPED_ALIGNMENTपूर्ण, अणु
	ERRDOS, 193, NT_STATUS_IMAGE_CHECKSUM_MISMATCHपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LOST_WRITEBEHIND_DATAपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CLIENT_SERVER_PARAMETERS_INVALIDपूर्ण, अणु
	ERRSRV, ERRpasswordExpired, NT_STATUS_PASSWORD_MUST_CHANGEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NOT_FOUNDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NOT_TINY_STREAMपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_RECOVERY_FAILUREपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_STACK_OVERFLOW_READपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FAIL_CHECKपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DUPLICATE_OBJECTIDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_OBJECTID_EXISTSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CONVERT_TO_LARGEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_RETRYपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_FOUND_OUT_OF_SCOPEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ALLOCATE_BUCKETपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PROPSET_NOT_FOUNDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_MARSHALL_OVERFLOWपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_VARIANTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_DOMAIN_CONTROLLER_NOT_FOUNDपूर्ण, अणु
	ERRDOS, ERRnoaccess, NT_STATUS_ACCOUNT_LOCKED_OUTपूर्ण, अणु
	ERRDOS, ERRbadfid, NT_STATUS_HANDLE_NOT_CLOSABLEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CONNECTION_REFUSEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_GRACEFUL_DISCONNECTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ADDRESS_ALREADY_ASSOCIATEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_ADDRESS_NOT_ASSOCIATEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CONNECTION_INVALIDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CONNECTION_ACTIVEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NETWORK_UNREACHABLEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_HOST_UNREACHABLEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PROTOCOL_UNREACHABLEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PORT_UNREACHABLEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_REQUEST_ABORTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CONNECTION_ABORTEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BAD_COMPRESSION_BUFFERपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_USER_MAPPED_खातापूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_AUDIT_FAILEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_TIMER_RESOLUTION_NOT_SETपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_CONNECTION_COUNT_LIMITपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LOGIN_TIME_RESTRICTIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LOGIN_WKSTA_RESTRICTIONपूर्ण, अणु
	ERRDOS, 193, NT_STATUS_IMAGE_MP_UP_MISMATCHपूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc000024aपूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc000024bपूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc000024cपूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc000024dपूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc000024eपूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc000024fपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INSUFFICIENT_LOGON_INFOपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BAD_DLL_ENTRYPOINTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_BAD_SERVICE_ENTRYPOINTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LPC_REPLY_LOSTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_IP_ADDRESS_CONFLICT1पूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_IP_ADDRESS_CONFLICT2पूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_REGISTRY_QUOTA_LIMITपूर्ण, अणु
	ERRSRV, 3, NT_STATUS_PATH_NOT_COVEREDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_NO_CALLBACK_ACTIVEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_LICENSE_QUOTA_EXCEEDEDपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PWD_TOO_SHORTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PWD_TOO_RECENTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PWD_HISTORY_CONFLICTपूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc000025dपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_PLUGPLAY_NO_DEVICEपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_UNSUPPORTED_COMPRESSIONपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_HW_PROखातापूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_INVALID_PLUGPLAY_DEVICE_PATHपूर्ण, अणु
	ERRDOS, 182, NT_STATUS_DRIVER_ORDINAL_NOT_FOUNDपूर्ण, अणु
	ERRDOS, 127, NT_STATUS_DRIVER_ENTRYPOINT_NOT_FOUNDपूर्ण, अणु
	ERRDOS, 288, NT_STATUS_RESOURCE_NOT_OWNEDपूर्ण, अणु
	ERRDOS, ErrTooManyLinks, NT_STATUS_TOO_MANY_LINKSपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_QUOTA_LIST_INCONSISTENTपूर्ण, अणु
	ERRHRD, ERRgeneral, NT_STATUS_खाता_IS_OFFLINEपूर्ण, अणु
	ERRDOS, 21, 0xc000026eपूर्ण, अणु
	ERRDOS, 161, 0xc0000281पूर्ण, अणु
	ERRDOS, ERRnoaccess, 0xc000028aपूर्ण, अणु
	ERRDOS, ERRnoaccess, 0xc000028bपूर्ण, अणु
	ERRHRD, ERRgeneral, 0xc000028cपूर्ण, अणु
	ERRDOS, ERRnoaccess, 0xc000028dपूर्ण, अणु
	ERRDOS, ERRnoaccess, 0xc000028eपूर्ण, अणु
	ERRDOS, ERRnoaccess, 0xc000028fपूर्ण, अणु
	ERRDOS, ERRnoaccess, 0xc0000290पूर्ण, अणु
	ERRDOS, ERRbadfunc, 0xc000029cपूर्ण, अणु
	ERRDOS, ERRsymlink, NT_STATUS_STOPPED_ON_SYMLINKपूर्ण, अणु
	ERRDOS, ERRinvlevel, 0x007c0001पूर्ण, अणु
	0, 0, 0 पूर्ण
पूर्ण;

/*****************************************************************************
 Prपूर्णांक an error message from the status code
 *****************************************************************************/
अटल व्योम
cअगरs_prपूर्णांक_status(__u32 status_code)
अणु
	पूर्णांक idx = 0;

	जबतक (nt_errs[idx].nt_errstr != शून्य) अणु
		अगर (((nt_errs[idx].nt_errcode) & 0xFFFFFF) ==
		    (status_code & 0xFFFFFF)) अणु
			pr_notice("Status code returned 0x%08x %s\n",
				  status_code, nt_errs[idx].nt_errstr);
		पूर्ण
		idx++;
	पूर्ण
	वापस;
पूर्ण


अटल व्योम
ntstatus_to_करोs(__u32 ntstatus, __u8 *eclass, __u16 *ecode)
अणु
	पूर्णांक i;
	अगर (ntstatus == 0) अणु
		*eclass = 0;
		*ecode = 0;
		वापस;
	पूर्ण
	क्रम (i = 0; ntstatus_to_करोs_map[i].ntstatus; i++) अणु
		अगर (ntstatus == ntstatus_to_करोs_map[i].ntstatus) अणु
			*eclass = ntstatus_to_करोs_map[i].करोs_class;
			*ecode = ntstatus_to_करोs_map[i].करोs_code;
			वापस;
		पूर्ण
	पूर्ण
	*eclass = ERRHRD;
	*ecode = ERRgeneral;
पूर्ण

पूर्णांक
map_smb_to_linux_error(अक्षर *buf, bool logErr)
अणु
	काष्ठा smb_hdr *smb = (काष्ठा smb_hdr *)buf;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = -EIO;	/* अगर transport error smb error may not be set */
	__u8 smberrclass;
	__u16 smberrcode;

	/* BB अगर NT Status codes - map NT BB */

	/* old style smb error codes */
	अगर (smb->Status.CअगरsError == 0)
		वापस 0;

	अगर (smb->Flags2 & SMBFLG2_ERR_STATUS) अणु
		/* translate the newer STATUS codes to old style SMB errors
		 * and then to POSIX errors */
		__u32 err = le32_to_cpu(smb->Status.CअगरsError);
		अगर (logErr && (err != (NT_STATUS_MORE_PROCESSING_REQUIRED)))
			cअगरs_prपूर्णांक_status(err);
		अन्यथा अगर (cअगरsFYI & CIFS_RC)
			cअगरs_prपूर्णांक_status(err);
		ntstatus_to_करोs(err, &smberrclass, &smberrcode);
	पूर्ण अन्यथा अणु
		smberrclass = smb->Status.DosError.ErrorClass;
		smberrcode = le16_to_cpu(smb->Status.DosError.Error);
	पूर्ण

	/* old style errors */

	/* DOS class smb error codes - map DOS */
	अगर (smberrclass == ERRDOS) अणु
		/* 1 byte field no need to byte reverse */
		क्रम (i = 0;
		     i <
		     माप(mapping_table_ERRDOS) /
		     माप(काष्ठा smb_to_posix_error); i++) अणु
			अगर (mapping_table_ERRDOS[i].smb_err == 0)
				अवरोध;
			अन्यथा अगर (mapping_table_ERRDOS[i].smb_err ==
								smberrcode) अणु
				rc = mapping_table_ERRDOS[i].posix_code;
				अवरोध;
			पूर्ण
			/* अन्यथा try next error mapping one to see अगर match */
		पूर्ण
	पूर्ण अन्यथा अगर (smberrclass == ERRSRV) अणु
		/* server class of error codes */
		क्रम (i = 0;
		     i <
		     माप(mapping_table_ERRSRV) /
		     माप(काष्ठा smb_to_posix_error); i++) अणु
			अगर (mapping_table_ERRSRV[i].smb_err == 0)
				अवरोध;
			अन्यथा अगर (mapping_table_ERRSRV[i].smb_err ==
								smberrcode) अणु
				rc = mapping_table_ERRSRV[i].posix_code;
				अवरोध;
			पूर्ण
			/* अन्यथा try next error mapping to see अगर match */
		पूर्ण
	पूर्ण
	/* अन्यथा ERRHRD class errors or junk  - वापस EIO */

	cअगरs_dbg(FYI, "Mapping smb error code 0x%x to POSIX err %d\n",
		 le32_to_cpu(smb->Status.CअगरsError), rc);

	/* generic corrective action e.g. reconnect SMB session on
	 * ERRbaduid could be added */

	वापस rc;
पूर्ण

पूर्णांक
map_and_check_smb_error(काष्ठा mid_q_entry *mid, bool logErr)
अणु
	पूर्णांक rc;
	काष्ठा smb_hdr *smb = (काष्ठा smb_hdr *)mid->resp_buf;

	rc = map_smb_to_linux_error((अक्षर *)smb, logErr);
	अगर (rc == -EACCES && !(smb->Flags2 & SMBFLG2_ERR_STATUS)) अणु
		/* possible ERRBaduid */
		__u8 class = smb->Status.DosError.ErrorClass;
		__u16 code = le16_to_cpu(smb->Status.DosError.Error);

		/* चयन can be used to handle dअगरferent errors */
		अगर (class == ERRSRV && code == ERRbaduid) अणु
			cअगरs_dbg(FYI, "Server returned 0x%x, reconnecting session...\n",
				code);
			spin_lock(&GlobalMid_Lock);
			अगर (mid->server->tcpStatus != CअगरsExiting)
				mid->server->tcpStatus = CअगरsNeedReconnect;
			spin_unlock(&GlobalMid_Lock);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण


/*
 * calculate the size of the SMB message based on the fixed header
 * portion, the number of word parameters and the data portion of the message
 */
अचिन्हित पूर्णांक
smbCalcSize(व्योम *buf, काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा smb_hdr *ptr = (काष्ठा smb_hdr *)buf;
	वापस (माप(काष्ठा smb_hdr) + (2 * ptr->WordCount) +
		2 /* size of the bcc field */ + get_bcc(ptr));
पूर्ण

/* The following are taken from fs/ntfs/util.c */

#घोषणा NTFS_TIME_OFFSET ((u64)(369*365 + 89) * 24 * 3600 * 10000000)

/*
 * Convert the NT UTC (based 1601-01-01, in hundred nanosecond units)
 * पूर्णांकo Unix UTC (based 1970-01-01, in seconds).
 */
काष्ठा बारpec64
cअगरs_NTसमयToUnix(__le64 ntutc)
अणु
	काष्ठा बारpec64 ts;
	/* BB what about the समयzone? BB */

	/* Subtract the NTFS समय offset, then convert to 1s पूर्णांकervals. */
	s64 t = le64_to_cpu(ntutc) - NTFS_TIME_OFFSET;
	u64 असल_t;

	/*
	 * Unक्रमtunately can not use normal 64 bit भागision on 32 bit arch, but
	 * the alternative, करो_भाग, करोes not work with negative numbers so have
	 * to special हाल them
	 */
	अगर (t < 0) अणु
		असल_t = -t;
		ts.tv_nsec = (समय64_t)(करो_भाग(असल_t, 10000000) * 100);
		ts.tv_nsec = -ts.tv_nsec;
		ts.tv_sec = -असल_t;
	पूर्ण अन्यथा अणु
		असल_t = t;
		ts.tv_nsec = (समय64_t)करो_भाग(असल_t, 10000000) * 100;
		ts.tv_sec = असल_t;
	पूर्ण

	वापस ts;
पूर्ण

/* Convert the Unix UTC पूर्णांकo NT UTC. */
u64
cअगरs_UnixTimeToNT(काष्ठा बारpec64 t)
अणु
	/* Convert to 100ns पूर्णांकervals and then add the NTFS समय offset. */
	वापस (u64) t.tv_sec * 10000000 + t.tv_nsec/100 + NTFS_TIME_OFFSET;
पूर्ण

अटल स्थिर पूर्णांक total_days_of_prev_months[] = अणु
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
पूर्ण;

काष्ठा बारpec64 cnvrtDosUnixTm(__le16 le_date, __le16 le_समय, पूर्णांक offset)
अणु
	काष्ठा बारpec64 ts;
	समय64_t sec, days;
	पूर्णांक min, day, month, year;
	u16 date = le16_to_cpu(le_date);
	u16 समय = le16_to_cpu(le_समय);
	SMB_TIME *st = (SMB_TIME *)&समय;
	SMB_DATE *sd = (SMB_DATE *)&date;

	cअगरs_dbg(FYI, "date %d time %d\n", date, समय);

	sec = 2 * st->TwoSeconds;
	min = st->Minutes;
	अगर ((sec > 59) || (min > 59))
		cअगरs_dbg(VFS, "Invalid time min %d sec %lld\n", min, sec);
	sec += (min * 60);
	sec += 60 * 60 * st->Hours;
	अगर (st->Hours > 24)
		cअगरs_dbg(VFS, "Invalid hours %d\n", st->Hours);
	day = sd->Day;
	month = sd->Month;
	अगर (day < 1 || day > 31 || month < 1 || month > 12) अणु
		cअगरs_dbg(VFS, "Invalid date, month %d day: %d\n", month, day);
		day = clamp(day, 1, 31);
		month = clamp(month, 1, 12);
	पूर्ण
	month -= 1;
	days = day + total_days_of_prev_months[month];
	days += 3652; /* account क्रम dअगरference in days between 1980 and 1970 */
	year = sd->Year;
	days += year * 365;
	days += (year/4); /* leap year */
	/* generalized leap year calculation is more complex, ie no leap year
	क्रम years/100 except क्रम years/400, but since the maximum number क्रम DOS
	 year is 2**7, the last year is 1980+127, which means we need only
	 consider 2 special हाल years, ie the years 2000 and 2100, and only
	 adjust क्रम the lack of leap year क्रम the year 2100, as 2000 was a
	 leap year (भागisable by 400) */
	अगर (year >= 120)  /* the year 2100 */
		days = days - 1;  /* करो not count leap year क्रम the year 2100 */

	/* adjust क्रम leap year where we are still beक्रमe leap day */
	अगर (year != 120)
		days -= ((year & 0x03) == 0) && (month < 2 ? 1 : 0);
	sec += 24 * 60 * 60 * days;

	ts.tv_sec = sec + offset;

	/* cअगरs_dbg(FYI, "sec after cnvrt dos to unix time %d\n",sec); */

	ts.tv_nsec = 0;
	वापस ts;
पूर्ण
