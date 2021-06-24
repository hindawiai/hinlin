<शैली गुरु>
/*
 *   fs/cअगरs/cअगरspdu.h
 *
 *   Copyright (c) International Business Machines  Corp., 2002,2009
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#अगर_अघोषित _CIFSPDU_H
#घोषणा _CIFSPDU_H

#समावेश <net/sock.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "smbfsctl.h"

#अगर_घोषित CONFIG_CIFS_WEAK_PW_HASH
#घोषणा LANMAN_PROT 0
#घोषणा LANMAN2_PROT 1
#घोषणा CIFS_PROT   2
#अन्यथा
#घोषणा CIFS_PROT   0
#पूर्ण_अगर
#घोषणा POSIX_PROT  (CIFS_PROT+1)
#घोषणा BAD_PROT 0xFFFF

/* SMB command codes:
 * Note some commands have minimal (wct=0,bcc=0), or unपूर्णांकeresting, responses
 * (ie which include no useful data other than the SMB error code itself).
 * This can allow us to aव्योम response buffer allocations and copy in some हालs
 */
#घोषणा SMB_COM_CREATE_सूचीECTORY      0x00 /* trivial response */
#घोषणा SMB_COM_DELETE_सूचीECTORY      0x01 /* trivial response */
#घोषणा SMB_COM_CLOSE                 0x04 /* triv req/rsp, बारtamp ignored */
#घोषणा SMB_COM_FLUSH                 0x05 /* triv req/rsp */
#घोषणा SMB_COM_DELETE                0x06 /* trivial response */
#घोषणा SMB_COM_RENAME                0x07 /* trivial response */
#घोषणा SMB_COM_QUERY_INFORMATION     0x08 /* aka getattr */
#घोषणा SMB_COM_SETATTR               0x09 /* trivial response */
#घोषणा SMB_COM_LOCKING_ANDX          0x24 /* trivial response */
#घोषणा SMB_COM_COPY                  0x29 /* trivial rsp, fail filename ignrd*/
#घोषणा SMB_COM_ECHO                  0x2B /* echo request */
#घोषणा SMB_COM_OPEN_ANDX             0x2D /* Legacy खोलो क्रम old servers */
#घोषणा SMB_COM_READ_ANDX             0x2E
#घोषणा SMB_COM_WRITE_ANDX            0x2F
#घोषणा SMB_COM_TRANSACTION2          0x32
#घोषणा SMB_COM_TRANSACTION2_SECONDARY 0x33
#घोषणा SMB_COM_FIND_CLOSE2           0x34 /* trivial response */
#घोषणा SMB_COM_TREE_DISCONNECT       0x71 /* trivial response */
#घोषणा SMB_COM_NEGOTIATE             0x72
#घोषणा SMB_COM_SESSION_SETUP_ANDX    0x73
#घोषणा SMB_COM_LOGOFF_ANDX           0x74 /* trivial response */
#घोषणा SMB_COM_TREE_CONNECT_ANDX     0x75
#घोषणा SMB_COM_NT_TRANSACT           0xA0
#घोषणा SMB_COM_NT_TRANSACT_SECONDARY 0xA1
#घोषणा SMB_COM_NT_CREATE_ANDX        0xA2
#घोषणा SMB_COM_NT_CANCEL             0xA4 /* no response */
#घोषणा SMB_COM_NT_RENAME             0xA5 /* trivial response */

/* Transact2 subcommand codes */
#घोषणा TRANS2_OPEN                   0x00
#घोषणा TRANS2_FIND_FIRST             0x01
#घोषणा TRANS2_FIND_NEXT              0x02
#घोषणा TRANS2_QUERY_FS_INFORMATION   0x03
#घोषणा TRANS2_SET_FS_INFORMATION     0x04
#घोषणा TRANS2_QUERY_PATH_INFORMATION 0x05
#घोषणा TRANS2_SET_PATH_INFORMATION   0x06
#घोषणा TRANS2_QUERY_खाता_INFORMATION 0x07
#घोषणा TRANS2_SET_खाता_INFORMATION   0x08
#घोषणा TRANS2_GET_DFS_REFERRAL       0x10
#घोषणा TRANS2_REPORT_DFS_INCOSISTENCY 0x11

/* SMB Transact (Named Pipe) subcommand codes */
#घोषणा TRANS_SET_NMPIPE_STATE      0x0001
#घोषणा TRANS_RAW_READ_NMPIPE       0x0011
#घोषणा TRANS_QUERY_NMPIPE_STATE    0x0021
#घोषणा TRANS_QUERY_NMPIPE_INFO     0x0022
#घोषणा TRANS_PEEK_NMPIPE           0x0023
#घोषणा TRANS_TRANSACT_NMPIPE       0x0026
#घोषणा TRANS_RAW_WRITE_NMPIPE      0x0031
#घोषणा TRANS_READ_NMPIPE           0x0036
#घोषणा TRANS_WRITE_NMPIPE          0x0037
#घोषणा TRANS_WAIT_NMPIPE           0x0053
#घोषणा TRANS_CALL_NMPIPE           0x0054

/* NT Transact subcommand codes */
#घोषणा NT_TRANSACT_CREATE            0x01
#घोषणा NT_TRANSACT_IOCTL             0x02
#घोषणा NT_TRANSACT_SET_SECURITY_DESC 0x03
#घोषणा NT_TRANSACT_NOTIFY_CHANGE     0x04
#घोषणा NT_TRANSACT_RENAME            0x05
#घोषणा NT_TRANSACT_QUERY_SECURITY_DESC 0x06
#घोषणा NT_TRANSACT_GET_USER_QUOTA    0x07
#घोषणा NT_TRANSACT_SET_USER_QUOTA    0x08

#घोषणा MAX_CIFS_SMALL_BUFFER_SIZE 448 /* big enough क्रम most */
/* future chained NTCreateXReadX bigger, but क्रम समय being NTCreateX biggest */
/* among the requests (NTCreateX response is bigger with wct of 34) */
#घोषणा MAX_CIFS_HDR_SIZE 0x58 /* 4 len + 32 hdr + (2*24 wct) + 2 bct + 2 pad */
#घोषणा CIFS_SMALL_PATH 120 /* allows क्रम (448-88)/3 */

/* पूर्णांकernal cअगरs vfs काष्ठाures */
/*****************************************************************
 * All स्थिरants go here
 *****************************************************************
 */

/*
 * Starting value क्रम maximum SMB size negotiation
 */
#घोषणा CIFS_MAX_MSGSIZE (4*4096)

/*
 * Size of encrypted user password in bytes
 */
#घोषणा CIFS_ENCPWD_SIZE (16)

/*
 * Size of the crypto key वापसed on the negotiate SMB in bytes
 */
#घोषणा CIFS_CRYPTO_KEY_SIZE (8)

/*
 * Size of the ntlm client response
 */
#घोषणा CIFS_AUTH_RESP_SIZE (24)

/*
 * Size of the session key (crypto key encrypted with the password
 */
#घोषणा CIFS_SESS_KEY_SIZE (16)

/*
 * Size of the smb3 signing key
 */
#घोषणा SMB3_SIGN_KEY_SIZE (16)

/*
 * Size of the smb3 encryption/decryption key storage.
 * This size is big enough to store any cipher key types.
 */
#घोषणा SMB3_ENC_DEC_KEY_SIZE (32)

#घोषणा CIFS_CLIENT_CHALLENGE_SIZE (8)
#घोषणा CIFS_SERVER_CHALLENGE_SIZE (8)
#घोषणा CIFS_HMAC_MD5_HASH_SIZE (16)
#घोषणा CIFS_CPHTXT_SIZE (16)
#घोषणा CIFS_NTHASH_SIZE (16)

/*
 * Maximum user name length
 */
#घोषणा CIFS_UNLEN (20)

/*
 * Flags on SMB खोलो
 */
#घोषणा SMBOPEN_WRITE_THROUGH 0x4000
#घोषणा SMBOPEN_DENY_ALL      0x0010
#घोषणा SMBOPEN_DENY_WRITE    0x0020
#घोषणा SMBOPEN_DENY_READ     0x0030
#घोषणा SMBOPEN_DENY_NONE     0x0040
#घोषणा SMBOPEN_READ          0x0000
#घोषणा SMBOPEN_WRITE         0x0001
#घोषणा SMBOPEN_READWRITE     0x0002
#घोषणा SMBOPEN_EXECUTE       0x0003

#घोषणा SMBOPEN_OCREATE       0x0010
#घोषणा SMBOPEN_OTRUNC        0x0002
#घोषणा SMBOPEN_OAPPEND       0x0001

/*
 * SMB flag definitions
 */
#घोषणा SMBFLG_EXTD_LOCK 0x01	/* server supports lock-पढ़ो ग_लिखो-unlock smb */
#घोषणा SMBFLG_RCV_POSTED 0x02	/* obsolete */
#घोषणा SMBFLG_RSVD 0x04
#घोषणा SMBFLG_CASELESS 0x08	/* all pathnames treated as हालless (off
				implies हाल sensitive file handling request) */
#घोषणा SMBFLG_CANONICAL_PATH_FORMAT 0x10	/* obsolete */
#घोषणा SMBFLG_OLD_OPLOCK 0x20	/* obsolete */
#घोषणा SMBFLG_OLD_OPLOCK_NOTIFY 0x40	/* obsolete */
#घोषणा SMBFLG_RESPONSE 0x80	/* this PDU is a response from server */

/*
 * SMB flag2 definitions
 */
#घोषणा SMBFLG2_KNOWS_LONG_NAMES cpu_to_le16(1)	/* can send दीर्घ (non-8.3)
						   path names in response */
#घोषणा SMBFLG2_KNOWS_EAS cpu_to_le16(2)
#घोषणा SMBFLG2_SECURITY_SIGNATURE cpu_to_le16(4)
#घोषणा SMBFLG2_COMPRESSED (8)
#घोषणा SMBFLG2_SECURITY_SIGNATURE_REQUIRED (0x10)
#घोषणा SMBFLG2_IS_LONG_NAME cpu_to_le16(0x40)
#घोषणा SMBFLG2_REPARSE_PATH (0x400)
#घोषणा SMBFLG2_EXT_SEC cpu_to_le16(0x800)
#घोषणा SMBFLG2_DFS cpu_to_le16(0x1000)
#घोषणा SMBFLG2_PAGING_IO cpu_to_le16(0x2000)
#घोषणा SMBFLG2_ERR_STATUS cpu_to_le16(0x4000)
#घोषणा SMBFLG2_UNICODE cpu_to_le16(0x8000)

/*
 * These are the file access permission bits defined in CIFS क्रम the
 * NTCreateAndX as well as the level 0x107
 * TRANS2_QUERY_PATH_INFORMATION API.  The level 0x107, SMB_QUERY_खाता_ALL_INFO
 * responds with the AccessFlags.
 * The AccessFlags specअगरies the access permissions a caller has to the
 * file and can have any suitable combination of the following values:
 */

#घोषणा खाता_READ_DATA        0x00000001  /* Data can be पढ़ो from the file   */
#घोषणा खाता_WRITE_DATA       0x00000002  /* Data can be written to the file  */
#घोषणा खाता_APPEND_DATA      0x00000004  /* Data can be appended to the file */
#घोषणा खाता_READ_EA          0x00000008  /* Extended attributes associated   */
					  /* with the file can be पढ़ो        */
#घोषणा खाता_WRITE_EA         0x00000010  /* Extended attributes associated   */
					  /* with the file can be written     */
#घोषणा खाता_EXECUTE          0x00000020  /*Data can be पढ़ो पूर्णांकo memory from */
					  /* the file using प्रणाली paging I/O */
#घोषणा खाता_DELETE_CHILD     0x00000040
#घोषणा खाता_READ_ATTRIBUTES  0x00000080  /* Attributes associated with the   */
					  /* file can be पढ़ो                 */
#घोषणा खाता_WRITE_ATTRIBUTES 0x00000100  /* Attributes associated with the   */
					  /* file can be written              */
#घोषणा DELETE                0x00010000  /* The file can be deleted          */
#घोषणा READ_CONTROL          0x00020000  /* The access control list and      */
					  /* ownership associated with the    */
					  /* file can be पढ़ो                 */
#घोषणा WRITE_DAC             0x00040000  /* The access control list and      */
					  /* ownership associated with the    */
					  /* file can be written.             */
#घोषणा WRITE_OWNER           0x00080000  /* Ownership inक्रमmation associated */
					  /* with the file can be written     */
#घोषणा SYNCHRONIZE           0x00100000  /* The file handle can रुकोed on to */
					  /* synchronize with the completion  */
					  /* of an input/output request       */
#घोषणा SYSTEM_SECURITY       0x01000000  /* The प्रणाली access control list   */
					  /* can be पढ़ो and changed          */
#घोषणा GENERIC_ALL           0x10000000
#घोषणा GENERIC_EXECUTE       0x20000000
#घोषणा GENERIC_WRITE         0x40000000
#घोषणा GENERIC_READ          0x80000000
					 /* In summary - Relevant file       */
					 /* access flags from CIFS are       */
					 /* file_पढ़ो_data, file_ग_लिखो_data  */
					 /* file_execute, file_पढ़ो_attributes*/
					 /* ग_लिखो_dac, and delete.           */

#घोषणा खाता_READ_RIGHTS (खाता_READ_DATA | खाता_READ_EA | खाता_READ_ATTRIBUTES)
#घोषणा खाता_WRITE_RIGHTS (खाता_WRITE_DATA | खाता_APPEND_DATA \
				| खाता_WRITE_EA | खाता_WRITE_ATTRIBUTES)
#घोषणा खाता_EXEC_RIGHTS (खाता_EXECUTE)

#घोषणा SET_खाता_READ_RIGHTS (खाता_READ_DATA | खाता_READ_EA | खाता_WRITE_EA \
				| खाता_READ_ATTRIBUTES \
				| खाता_WRITE_ATTRIBUTES \
				| DELETE | READ_CONTROL | WRITE_DAC \
				| WRITE_OWNER | SYNCHRONIZE)
#घोषणा SET_खाता_WRITE_RIGHTS (खाता_WRITE_DATA | खाता_APPEND_DATA \
				| खाता_READ_EA | खाता_WRITE_EA \
				| खाता_READ_ATTRIBUTES \
				| खाता_WRITE_ATTRIBUTES \
				| DELETE | READ_CONTROL | WRITE_DAC \
				| WRITE_OWNER | SYNCHRONIZE)
#घोषणा SET_खाता_EXEC_RIGHTS (खाता_READ_EA | खाता_WRITE_EA | खाता_EXECUTE \
				| खाता_READ_ATTRIBUTES \
				| खाता_WRITE_ATTRIBUTES \
				| DELETE | READ_CONTROL | WRITE_DAC \
				| WRITE_OWNER | SYNCHRONIZE)

#घोषणा SET_MINIMUM_RIGHTS (खाता_READ_EA | खाता_READ_ATTRIBUTES \
				| READ_CONTROL | SYNCHRONIZE)


/*
 * Invalid सूची_पढ़ो handle
 */
#घोषणा CIFS_NO_HANDLE        0xFFFF

#घोषणा NO_CHANGE_64          0xFFFFFFFFFFFFFFFFULL

/* IPC$ in ASCII */
#घोषणा CIFS_IPC_RESOURCE "\x49\x50\x43\x24"

/* IPC$ in Unicode */
#घोषणा CIFS_IPC_UNICODE_RESOURCE "\x00\x49\x00\x50\x00\x43\x00\x24\x00\x00"

/* Unicode Null terminate 2 bytes of 0 */
#घोषणा UNICODE_शून्य "\x00\x00"
#घोषणा ASCII_शून्य 0x00

/*
 * Server type values (वापसed on EnumServer API
 */
#घोषणा CIFS_SV_TYPE_DC     0x00000008
#घोषणा CIFS_SV_TYPE_BACKDC 0x00000010

/*
 * Alias type flags (From EnumAlias API call
 */
#घोषणा CIFS_ALIAS_TYPE_खाता 0x0001
#घोषणा CIFS_SHARE_TYPE_खाता 0x0000

/*
 * File Attribute flags
 */
#घोषणा ATTR_READONLY  0x0001
#घोषणा ATTR_HIDDEN    0x0002
#घोषणा ATTR_SYSTEM    0x0004
#घोषणा ATTR_VOLUME    0x0008
#घोषणा ATTR_सूचीECTORY 0x0010
#घोषणा ATTR_ARCHIVE   0x0020
#घोषणा ATTR_DEVICE    0x0040
#घोषणा ATTR_NORMAL    0x0080
#घोषणा ATTR_TEMPORARY 0x0100
#घोषणा ATTR_SPARSE    0x0200
#घोषणा ATTR_REPARSE   0x0400
#घोषणा ATTR_COMPRESSED 0x0800
#घोषणा ATTR_OFFLINE    0x1000	/* ie file not immediately available -
					on offline storage */
#घोषणा ATTR_NOT_CONTENT_INDEXED 0x2000
#घोषणा ATTR_ENCRYPTED  0x4000
#घोषणा ATTR_POSIX_SEMANTICS 0x01000000
#घोषणा ATTR_BACKUP_SEMANTICS 0x02000000
#घोषणा ATTR_DELETE_ON_CLOSE 0x04000000
#घोषणा ATTR_SEQUENTIAL_SCAN 0x08000000
#घोषणा ATTR_RANDOM_ACCESS   0x10000000
#घोषणा ATTR_NO_BUFFERING    0x20000000
#घोषणा ATTR_WRITE_THROUGH   0x80000000

/* ShareAccess flags */
#घोषणा खाता_NO_SHARE     0x00000000
#घोषणा खाता_SHARE_READ   0x00000001
#घोषणा खाता_SHARE_WRITE  0x00000002
#घोषणा खाता_SHARE_DELETE 0x00000004
#घोषणा खाता_SHARE_ALL    0x00000007

/* CreateDisposition flags, similar to CreateAction as well */
#घोषणा खाता_SUPERSEDE    0x00000000
#घोषणा खाता_OPEN         0x00000001
#घोषणा खाता_CREATE       0x00000002
#घोषणा खाता_OPEN_IF      0x00000003
#घोषणा खाता_OVERWRITE    0x00000004
#घोषणा खाता_OVERWRITE_IF 0x00000005

/* CreateOptions */
#घोषणा CREATE_NOT_खाता		0x00000001	/* अगर set must not be file */
#घोषणा CREATE_WRITE_THROUGH	0x00000002
#घोषणा CREATE_SEQUENTIAL       0x00000004
#घोषणा CREATE_NO_BUFFER        0x00000008      /* should not buffer on srv */
#घोषणा CREATE_SYNC_ALERT       0x00000010	/* MBZ */
#घोषणा CREATE_ASYNC_ALERT      0x00000020	/* MBZ */
#घोषणा CREATE_NOT_सूची		0x00000040    /* अगर set must not be directory */
#घोषणा CREATE_TREE_CONNECTION  0x00000080	/* should be zero */
#घोषणा CREATE_COMPLETE_IF_OPLK 0x00000100	/* should be zero */
#घोषणा CREATE_NO_EA_KNOWLEDGE  0x00000200
#घोषणा CREATE_EIGHT_DOT_THREE  0x00000400	/* करोc says this is obsolete
						 "open for recovery" flag should
						 be zero in any हाल */
#घोषणा CREATE_OPEN_FOR_RECOVERY 0x00000400
#घोषणा CREATE_RANDOM_ACCESS	0x00000800
#घोषणा CREATE_DELETE_ON_CLOSE	0x00001000
#घोषणा CREATE_OPEN_BY_ID       0x00002000
#घोषणा CREATE_OPEN_BACKUP_INTENT 0x00004000
#घोषणा CREATE_NO_COMPRESSION   0x00008000
#घोषणा CREATE_RESERVE_OPFILTER 0x00100000	/* should be zero */
#घोषणा OPEN_REPARSE_POINT	0x00200000
#घोषणा OPEN_NO_RECALL          0x00400000
#घोषणा OPEN_FREE_SPACE_QUERY   0x00800000	/* should be zero */
#घोषणा CREATE_OPTIONS_MASK     0x007FFFFF
#घोषणा CREATE_OPTION_READONLY	0x10000000
#घोषणा CREATE_OPTION_SPECIAL   0x20000000   /* प्रणाली. NB not sent over wire */

/* ImpersonationLevel flags */
#घोषणा SECURITY_ANONYMOUS      0
#घोषणा SECURITY_IDENTIFICATION 1
#घोषणा SECURITY_IMPERSONATION  2
#घोषणा SECURITY_DELEGATION     3

/* SecurityFlags */
#घोषणा SECURITY_CONTEXT_TRACKING 0x01
#घोषणा SECURITY_EFFECTIVE_ONLY   0x02

/*
 * Default PID value, used in all SMBs where the PID is not important
 */
#घोषणा CIFS_DFT_PID  0x1234

/*
 * We use the same routine क्रम Copy and Move SMBs.  This flag is used to
 * distinguish
 */
#घोषणा CIFS_COPY_OP 1
#घोषणा CIFS_RENAME_OP 2

#घोषणा GETU16(var)  (*((__u16 *)var))	/* BB check क्रम endian issues */
#घोषणा GETU32(var)  (*((__u32 *)var))	/* BB check क्रम endian issues */

काष्ठा smb_hdr अणु
	__be32 smb_buf_length;	/* BB length is only two (rarely three) bytes,
		with one or two byte "type" preceding it that will be
		zero - we could mask the type byte off */
	__u8 Protocol[4];
	__u8 Command;
	जोड़ अणु
		काष्ठा अणु
			__u8 ErrorClass;
			__u8 Reserved;
			__le16 Error;
		पूर्ण __attribute__((packed)) DosError;
		__le32 CअगरsError;
	पूर्ण __attribute__((packed)) Status;
	__u8 Flags;
	__le16 Flags2;		/* note: le */
	__le16 PidHigh;
	जोड़ अणु
		काष्ठा अणु
			__le32 SequenceNumber;  /* le */
			__u32 Reserved; /* zero */
		पूर्ण __attribute__((packed)) Sequence;
		__u8 SecuritySignature[8];	/* le */
	पूर्ण __attribute__((packed)) Signature;
	__u8 pad[2];
	__u16 Tid;
	__le16 Pid;
	__u16 Uid;
	__le16 Mid;
	__u8 WordCount;
पूर्ण __attribute__((packed));

/* given a poपूर्णांकer to an smb_hdr, retrieve a व्योम poपूर्णांकer to the ByteCount */
अटल अंतरभूत व्योम *
BCC(काष्ठा smb_hdr *smb)
अणु
	वापस (व्योम *)smb + माप(*smb) + 2 * smb->WordCount;
पूर्ण

/* given a poपूर्णांकer to an smb_hdr retrieve the poपूर्णांकer to the byte area */
#घोषणा pByteArea(smb_var) (BCC(smb_var) + 2)

/* get the unconverted ByteCount क्रम a SMB packet and वापस it */
अटल अंतरभूत __u16
get_bcc(काष्ठा smb_hdr *hdr)
अणु
	__le16 *bc_ptr = (__le16 *)BCC(hdr);

	वापस get_unaligned_le16(bc_ptr);
पूर्ण

/* set the ByteCount क्रम a SMB packet in little-endian */
अटल अंतरभूत व्योम
put_bcc(__u16 count, काष्ठा smb_hdr *hdr)
अणु
	__le16 *bc_ptr = (__le16 *)BCC(hdr);

	put_unaligned_le16(count, bc_ptr);
पूर्ण

/*
 * Computer Name Length (since Netbios name was length 16 with last byte 0x20)
 * No दीर्घer as important, now that TCP names are more commonly used to
 * resolve hosts.
 */
#घोषणा CNLEN 15

/*
 * Share Name Length (SNLEN)
 * Note:  This length was limited by the SMB used to get
 *        the Share info.   NetShareEnum only वापसed 13
 *        अक्षरs, including the null termination.
 * This was हटाओd because it no दीर्घer is limiting.
 */

/*
 * Comment Length
 */
#घोषणा MAXCOMMENTLEN 40

/*
 * The OS/2 maximum path name
 */
#घोषणा MAX_PATHCONF 256

/*
 *  SMB frame definitions  (following must be packed काष्ठाs)
 *  See the SNIA CIFS Specअगरication क्रम details.
 *
 *  The Naming convention is the lower हाल version of the
 *  smb command code name क्रम the काष्ठा and this is प्रकार to the
 *  upperहाल version of the same name with the prefix SMB_ हटाओd
 *  क्रम brevity.  Although प्रकारs are not commonly used क्रम
 *  काष्ठाure definitions in the Linux kernel, their use in the
 *  CIFS standards करोcument, which this code is based on, may
 *  make this one of the हालs where प्रकारs क्रम काष्ठाures make
 *  sense to improve पढ़ोability क्रम पढ़ोers of the standards करोc.
 *  Typedefs can always be हटाओd later अगर they are too distracting
 *  and they are only used क्रम the CIFSs PDUs themselves, not
 *  पूर्णांकernal cअगरs vfs काष्ठाures
 *
 */

प्रकार काष्ठा negotiate_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 0 */
	__le16 ByteCount;
	अचिन्हित अक्षर DialectsArray[1];
पूर्ण __attribute__((packed)) NEGOTIATE_REQ;

/* Dialect index is 13 क्रम LANMAN */

#घोषणा MIN_TZ_ADJ (15 * 60) /* minimum grid क्रम समयzones in seconds */

प्रकार काष्ठा lanman_neg_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 13 */
	__le16 DialectIndex;
	__le16 SecurityMode;
	__le16 MaxBufSize;
	__le16 MaxMpxCount;
	__le16 MaxNumberVcs;
	__le16 RawMode;
	__le32 SessionKey;
	काष्ठा अणु
		__le16 Time;
		__le16 Date;
	पूर्ण __attribute__((packed)) SrvTime;
	__le16 ServerTimeZone;
	__le16 EncryptionKeyLength;
	__le16 Reserved;
	__u16  ByteCount;
	अचिन्हित अक्षर EncryptionKey[1];
पूर्ण __attribute__((packed)) LANMAN_NEG_RSP;

#घोषणा READ_RAW_ENABLE 1
#घोषणा WRITE_RAW_ENABLE 2
#घोषणा RAW_ENABLE (READ_RAW_ENABLE | WRITE_RAW_ENABLE)
#घोषणा SMB1_CLIENT_GUID_SIZE (16)
प्रकार काष्ठा negotiate_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 17 */
	__le16 DialectIndex; /* 0xFFFF = no dialect acceptable */
	__u8 SecurityMode;
	__le16 MaxMpxCount;
	__le16 MaxNumberVcs;
	__le32 MaxBufferSize;
	__le32 MaxRawSize;
	__le32 SessionKey;
	__le32 Capabilities;	/* see below */
	__le32 SystemTimeLow;
	__le32 SystemTimeHigh;
	__le16 ServerTimeZone;
	__u8 EncryptionKeyLength;
	__u16 ByteCount;
	जोड़ अणु
		अचिन्हित अक्षर EncryptionKey[1];	/* cap extended security off */
		/* followed by Doमुख्य name - अगर extended security is off */
		/* followed by 16 bytes of server GUID */
		/* then security blob अगर cap_extended_security negotiated */
		काष्ठा अणु
			अचिन्हित अक्षर GUID[SMB1_CLIENT_GUID_SIZE];
			अचिन्हित अक्षर SecurityBlob[1];
		पूर्ण __attribute__((packed)) extended_response;
	पूर्ण __attribute__((packed)) u;
पूर्ण __attribute__((packed)) NEGOTIATE_RSP;

/* SecurityMode bits */
#घोषणा SECMODE_USER          0x01	/* off indicates share level security */
#घोषणा SECMODE_PW_ENCRYPT    0x02
#घोषणा SECMODE_SIGN_ENABLED  0x04	/* SMB security signatures enabled */
#घोषणा SECMODE_SIGN_REQUIRED 0x08	/* SMB security signatures required */

/* Negotiate response Capabilities */
#घोषणा CAP_RAW_MODE           0x00000001
#घोषणा CAP_MPX_MODE           0x00000002
#घोषणा CAP_UNICODE            0x00000004
#घोषणा CAP_LARGE_खाताS        0x00000008
#घोषणा CAP_NT_SMBS            0x00000010	/* implies CAP_NT_FIND */
#घोषणा CAP_RPC_REMOTE_APIS    0x00000020
#घोषणा CAP_STATUS32           0x00000040
#घोषणा CAP_LEVEL_II_OPLOCKS   0x00000080
#घोषणा CAP_LOCK_AND_READ      0x00000100
#घोषणा CAP_NT_FIND            0x00000200
#घोषणा CAP_DFS                0x00001000
#घोषणा CAP_INFOLEVEL_PASSTHRU 0x00002000
#घोषणा CAP_LARGE_READ_X       0x00004000
#घोषणा CAP_LARGE_WRITE_X      0x00008000
#घोषणा CAP_LWIO               0x00010000 /* support fctl_srv_req_resume_key */
#घोषणा CAP_UNIX               0x00800000
#घोषणा CAP_COMPRESSED_DATA    0x02000000
#घोषणा CAP_DYNAMIC_REAUTH     0x20000000
#घोषणा CAP_PERSISTENT_HANDLES 0x40000000
#घोषणा CAP_EXTENDED_SECURITY  0x80000000

प्रकार जोड़ smb_com_session_setup_andx अणु
	काष्ठा अणु		/* request क्रमmat */
		काष्ठा smb_hdr hdr;	/* wct = 12 */
		__u8 AndXCommand;
		__u8 AndXReserved;
		__le16 AndXOffset;
		__le16 MaxBufferSize;
		__le16 MaxMpxCount;
		__le16 VcNumber;
		__u32 SessionKey;
		__le16 SecurityBlobLength;
		__u32 Reserved;
		__le32 Capabilities;	/* see below */
		__le16 ByteCount;
		अचिन्हित अक्षर SecurityBlob[1];	/* followed by */
		/* STRING NativeOS */
		/* STRING NativeLanMan */
	पूर्ण __attribute__((packed)) req;	/* NTLM request क्रमmat (with
					extended security */

	काष्ठा अणु		/* request क्रमmat */
		काष्ठा smb_hdr hdr;	/* wct = 13 */
		__u8 AndXCommand;
		__u8 AndXReserved;
		__le16 AndXOffset;
		__le16 MaxBufferSize;
		__le16 MaxMpxCount;
		__le16 VcNumber;
		__u32 SessionKey;
		__le16 CaseInsensitivePasswordLength; /* ASCII password len */
		__le16 CaseSensitivePasswordLength; /* Unicode password length*/
		__u32 Reserved;	/* see below */
		__le32 Capabilities;
		__le16 ByteCount;
		अचिन्हित अक्षर CaseInsensitivePassword[1];     /* followed by: */
		/* अचिन्हित अक्षर * CaseSensitivePassword; */
		/* STRING AccountName */
		/* STRING PrimaryDoमुख्य */
		/* STRING NativeOS */
		/* STRING NativeLanMan */
	पूर्ण __attribute__((packed)) req_no_secext; /* NTLM request क्रमmat (without
							extended security */

	काष्ठा अणु		/* शेष (NTLM) response क्रमmat */
		काष्ठा smb_hdr hdr;	/* wct = 4 */
		__u8 AndXCommand;
		__u8 AndXReserved;
		__le16 AndXOffset;
		__le16 Action;	/* see below */
		__le16 SecurityBlobLength;
		__u16 ByteCount;
		अचिन्हित अक्षर SecurityBlob[1];	/* followed by */
/*      अचिन्हित अक्षर  * NativeOS;      */
/*	अचिन्हित अक्षर  * NativeLanMan;  */
/*      अचिन्हित अक्षर  * PrimaryDoमुख्य; */
	पूर्ण __attribute__((packed)) resp;	/* NTLM response
					   (with or without extended sec) */

	काष्ठा अणु		/* request क्रमmat */
		काष्ठा smb_hdr hdr;	/* wct = 10 */
		__u8 AndXCommand;
		__u8 AndXReserved;
		__le16 AndXOffset;
		__le16 MaxBufferSize;
		__le16 MaxMpxCount;
		__le16 VcNumber;
		__u32 SessionKey;
		__le16 PasswordLength;
		__u32 Reserved; /* encrypt key len and offset */
		__le16 ByteCount;
		अचिन्हित अक्षर AccountPassword[1];	/* followed by */
		/* STRING AccountName */
		/* STRING PrimaryDoमुख्य */
		/* STRING NativeOS */
		/* STRING NativeLanMan */
	पूर्ण __attribute__((packed)) old_req; /* pre-NTLM (LANMAN2.1) req क्रमmat */

	काष्ठा अणु		/* शेष (NTLM) response क्रमmat */
		काष्ठा smb_hdr hdr;	/* wct = 3 */
		__u8 AndXCommand;
		__u8 AndXReserved;
		__le16 AndXOffset;
		__le16 Action;	/* see below */
		__u16 ByteCount;
		अचिन्हित अक्षर NativeOS[1];	/* followed by */
/*	अचिन्हित अक्षर * NativeLanMan; */
/*      अचिन्हित अक्षर * PrimaryDoमुख्य; */
	पूर्ण __attribute__((packed)) old_resp; /* pre-NTLM (LANMAN2.1) response */
पूर्ण __attribute__((packed)) SESSION_SETUP_ANDX;

/* क्रमmat of NLTMv2 Response ie "case sensitive password" hash when NTLMv2 */

#घोषणा NTLMSSP_SERVER_TYPE	1
#घोषणा NTLMSSP_DOMAIN_TYPE	2
#घोषणा NTLMSSP_FQ_DOMAIN_TYPE	3
#घोषणा NTLMSSP_DNS_DOMAIN_TYPE	4
#घोषणा NTLMSSP_DNS_PARENT_TYPE	5

काष्ठा ntlmssp2_name अणु
	__le16 type;
	__le16 length;
/*	अक्षर   name[length]; */
पूर्ण __attribute__((packed));

काष्ठा ntlmv2_resp अणु
	जोड़ अणु
	    अक्षर ntlmv2_hash[CIFS_ENCPWD_SIZE];
	    काष्ठा अणु
		__u8 reserved[8];
		__u8 key[CIFS_SERVER_CHALLENGE_SIZE];
	    पूर्ण __attribute__((packed)) challenge;
	पूर्ण __attribute__((packed));
	__le32 blob_signature;
	__u32  reserved;
	__le64  समय;
	__u64  client_chal; /* अक्रमom */
	__u32  reserved2;
	/* array of name entries could follow ending in minimum 4 byte काष्ठा */
पूर्ण __attribute__((packed));


#घोषणा CIFS_NETWORK_OPSYS "CIFS VFS Client for Linux"

/* Capabilities bits (क्रम NTLM SessSetup request) */
#घोषणा CAP_UNICODE            0x00000004
#घोषणा CAP_LARGE_खाताS        0x00000008
#घोषणा CAP_NT_SMBS            0x00000010
#घोषणा CAP_STATUS32           0x00000040
#घोषणा CAP_LEVEL_II_OPLOCKS   0x00000080
#घोषणा CAP_NT_FIND            0x00000200	/* reserved should be zero
				(because NT_SMBs implies the same thing?) */
#घोषणा CAP_BULK_TRANSFER      0x20000000
#घोषणा CAP_EXTENDED_SECURITY  0x80000000

/* Action bits */
#घोषणा GUEST_LOGIN 1

प्रकार काष्ठा smb_com_tconx_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 4 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__le16 Flags;		/* see below */
	__le16 PasswordLength;
	__le16 ByteCount;
	अचिन्हित अक्षर Password[1];	/* followed by */
/* STRING Path    *//* \\server\share name */
	/* STRING Service */
पूर्ण __attribute__((packed)) TCONX_REQ;

प्रकार काष्ठा smb_com_tconx_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 3 , not extended response */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__le16 OptionalSupport;	/* see below */
	__u16 ByteCount;
	अचिन्हित अक्षर Service[1];	/* always ASCII, not Unicode */
	/* STRING NativeFileSystem */
पूर्ण __attribute__((packed)) TCONX_RSP;

प्रकार काष्ठा smb_com_tconx_rsp_ext अणु
	काष्ठा smb_hdr hdr;	/* wct = 7, extended response */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__le16 OptionalSupport;	/* see below */
	__le32 MaximalShareAccessRights;
	__le32 GuestMaximalShareAccessRights;
	__u16 ByteCount;
	अचिन्हित अक्षर Service[1];	/* always ASCII, not Unicode */
	/* STRING NativeFileSystem */
पूर्ण __attribute__((packed)) TCONX_RSP_EXT;


/* tree connect Flags */
#घोषणा DISCONNECT_TID          0x0001
#घोषणा TCON_EXTENDED_SIGNATURES 0x0004
#घोषणा TCON_EXTENDED_SECINFO   0x0008

/* OptionalSupport bits */
#घोषणा SMB_SUPPORT_SEARCH_BITS 0x0001	/* "must have" directory search bits
					 (exclusive searches supported) */
#घोषणा SMB_SHARE_IS_IN_DFS     0x0002
#घोषणा SMB_CSC_MASK               0x000C
/* CSC flags defined as follows */
#घोषणा SMB_CSC_CACHE_MANUAL_REINT 0x0000
#घोषणा SMB_CSC_CACHE_AUTO_REINT   0x0004
#घोषणा SMB_CSC_CACHE_VDO          0x0008
#घोषणा SMB_CSC_NO_CACHING         0x000C
#घोषणा SMB_UNIQUE_खाता_NAME    0x0010
#घोषणा SMB_EXTENDED_SIGNATURES 0x0020

/* services
 *
 * A:       ie disk
 * LPT1:    ie prपूर्णांकer
 * IPC      ie named pipe
 * COMM
 * ?????    ie any type
 *
 */

प्रकार काष्ठा smb_com_echo_req अणु
	काष्ठा	smb_hdr hdr;
	__le16	EchoCount;
	__le16	ByteCount;
	अक्षर	Data[1];
पूर्ण __attribute__((packed)) ECHO_REQ;

प्रकार काष्ठा smb_com_echo_rsp अणु
	काष्ठा	smb_hdr hdr;
	__le16	SequenceNumber;
	__le16	ByteCount;
	अक्षर	Data[1];
पूर्ण __attribute__((packed)) ECHO_RSP;

प्रकार काष्ठा smb_com_logoff_andx_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 2 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__u16 AndXOffset;
	__u16 ByteCount;
पूर्ण __attribute__((packed)) LOGOFF_ANDX_REQ;

प्रकार काष्ठा smb_com_logoff_andx_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 2 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__u16 AndXOffset;
	__u16 ByteCount;
पूर्ण __attribute__((packed)) LOGOFF_ANDX_RSP;

प्रकार जोड़ smb_com_tree_disconnect अणु	/* as an altetnative can use flag on
					tree_connect PDU to effect disconnect */
					/* tdis is probably simplest SMB PDU */
	काष्ठा अणु
		काष्ठा smb_hdr hdr;	/* wct = 0 */
		__u16 ByteCount;	/* bcc = 0 */
	पूर्ण __attribute__((packed)) req;
	काष्ठा अणु
		काष्ठा smb_hdr hdr;	/* wct = 0 */
		__u16 ByteCount;	/* bcc = 0 */
	पूर्ण __attribute__((packed)) resp;
पूर्ण __attribute__((packed)) TREE_DISCONNECT;

प्रकार काष्ठा smb_com_बंद_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 3 */
	__u16 FileID;
	__u32 LastWriteTime;	/* should be zero or -1 */
	__u16 ByteCount;	/* 0 */
पूर्ण __attribute__((packed)) CLOSE_REQ;

प्रकार काष्ठा smb_com_बंद_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 0 */
	__u16 ByteCount;	/* bct = 0 */
पूर्ण __attribute__((packed)) CLOSE_RSP;

प्रकार काष्ठा smb_com_flush_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 1 */
	__u16 FileID;
	__u16 ByteCount;	/* 0 */
पूर्ण __attribute__((packed)) FLUSH_REQ;

प्रकार काष्ठा smb_com_findबंद_req अणु
	काष्ठा smb_hdr hdr; /* wct = 1 */
	__u16 FileID;
	__u16 ByteCount;    /* 0 */
पूर्ण __attribute__((packed)) FINDCLOSE_REQ;

/* OpenFlags */
#घोषणा REQ_MORE_INFO      0x00000001  /* legacy (OPEN_AND_X) only */
#घोषणा REQ_OPLOCK         0x00000002
#घोषणा REQ_BATCHOPLOCK    0x00000004
#घोषणा REQ_OPENसूचीONLY    0x00000008
#घोषणा REQ_EXTENDED_INFO  0x00000010

/* File type */
#घोषणा DISK_TYPE		0x0000
#घोषणा BYTE_PIPE_TYPE		0x0001
#घोषणा MESSAGE_PIPE_TYPE	0x0002
#घोषणा PRINTER_TYPE		0x0003
#घोषणा COMM_DEV_TYPE		0x0004
#घोषणा UNKNOWN_TYPE		0xFFFF

/* Device Type or File Status Flags */
#घोषणा NO_EAS			0x0001
#घोषणा NO_SUBSTREAMS		0x0002
#घोषणा NO_REPARSETAG		0x0004
/* following flags can apply अगर pipe */
#घोषणा ICOUNT_MASK		0x00FF
#घोषणा PIPE_READ_MODE		0x0100
#घोषणा NAMED_PIPE_TYPE		0x0400
#घोषणा PIPE_END_POINT		0x4000
#घोषणा BLOCKING_NAMED_PIPE	0x8000

प्रकार काष्ठा smb_com_खोलो_req अणु	/* also handles create */
	काष्ठा smb_hdr hdr;	/* wct = 24 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__u8 Reserved;		/* Must Be Zero */
	__le16 NameLength;
	__le32 OpenFlags;
	__u32  RootDirectoryFid;
	__le32 DesiredAccess;
	__le64 AllocationSize;
	__le32 FileAttributes;
	__le32 ShareAccess;
	__le32 CreateDisposition;
	__le32 CreateOptions;
	__le32 ImpersonationLevel;
	__u8 SecurityFlags;
	__le16 ByteCount;
	अक्षर fileName[1];
पूर्ण __attribute__((packed)) OPEN_REQ;

/* खोलो response: oplock levels */
#घोषणा OPLOCK_NONE  	 0
#घोषणा OPLOCK_EXCLUSIVE 1
#घोषणा OPLOCK_BATCH	 2
#घोषणा OPLOCK_READ	 3  /* level 2 oplock */

/* खोलो response क्रम CreateAction shअगरted left */
#घोषणा CIFS_CREATE_ACTION 0x20000 /* file created */

प्रकार काष्ठा smb_com_खोलो_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 34 BB */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__u8 OplockLevel;
	__u16 Fid;
	__le32 CreateAction;
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le32 FileAttributes;
	__le64 AllocationSize;
	__le64 EndOfFile;
	__le16 FileType;
	__le16 DeviceState;
	__u8 DirectoryFlag;
	__u16 ByteCount;	/* bct = 0 */
पूर्ण __attribute__((packed)) OPEN_RSP;

प्रकार काष्ठा smb_com_खोलो_rsp_ext अणु
	काष्ठा smb_hdr hdr;     /* wct = 42 but meaningless due to MS bug? */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__u8 OplockLevel;
	__u16 Fid;
	__le32 CreateAction;
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le32 FileAttributes;
	__le64 AllocationSize;
	__le64 EndOfFile;
	__le16 FileType;
	__le16 DeviceState;
	__u8 DirectoryFlag;
	__u8 VolumeGUID[16];
	__u64 FileId; /* note no endian conversion - is opaque UniqueID */
	__le32 MaximalAccessRights;
	__le32 GuestMaximalAccessRights;
	__u16 ByteCount;        /* bct = 0 */
पूर्ण __attribute__((packed)) OPEN_RSP_EXT;


/* क्रमmat of legacy खोलो request */
प्रकार काष्ठा smb_com_खोलोx_req अणु
	काष्ठा smb_hdr	hdr;	/* wct = 15 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__le16 OpenFlags;
	__le16 Mode;
	__le16 Sattr; /* search attributes */
	__le16 FileAttributes;  /* करोs attrs */
	__le32 CreateTime; /* os2 क्रमmat */
	__le16 OpenFunction;
	__le32 EndOfFile;
	__le32 Timeout;
	__le32 Reserved;
	__le16  ByteCount;  /* file name follows */
	अक्षर   fileName[1];
पूर्ण __attribute__((packed)) OPENX_REQ;

प्रकार काष्ठा smb_com_खोलोx_rsp अणु
	काष्ठा smb_hdr	hdr;	/* wct = 15 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__u16  Fid;
	__le16 FileAttributes;
	__le32 LastWriteTime; /* os2 क्रमmat */
	__le32 EndOfFile;
	__le16 Access;
	__le16 FileType;
	__le16 IPCState;
	__le16 Action;
	__u32  FileId;
	__u16  Reserved;
	__u16  ByteCount;
पूर्ण __attribute__((packed)) OPENX_RSP;

/* For encoding of POSIX Open Request - see trans2 function 0x209 data काष्ठा */

/* Legacy ग_लिखो request क्रम older servers */
प्रकार काष्ठा smb_com_ग_लिखोx_req अणु
	काष्ठा smb_hdr hdr;     /* wct = 12 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__u16 Fid;
	__le32 OffsetLow;
	__u32 Reserved; /* Timeout */
	__le16 WriteMode; /* 1 = ग_लिखो through */
	__le16 Reमुख्यing;
	__le16 Reserved2;
	__le16 DataLengthLow;
	__le16 DataOffset;
	__le16 ByteCount;
	__u8 Pad;		/* BB check क्रम whether padded to DWORD
				   boundary and optimum perक्रमmance here */
	अक्षर Data[];
पूर्ण __attribute__((packed)) WRITEX_REQ;

प्रकार काष्ठा smb_com_ग_लिखो_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 14 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__u16 Fid;
	__le32 OffsetLow;
	__u32 Reserved;
	__le16 WriteMode;
	__le16 Reमुख्यing;
	__le16 DataLengthHigh;
	__le16 DataLengthLow;
	__le16 DataOffset;
	__le32 OffsetHigh;
	__le16 ByteCount;
	__u8 Pad;		/* BB check क्रम whether padded to DWORD
				   boundary and optimum perक्रमmance here */
	अक्षर Data[];
पूर्ण __attribute__((packed)) WRITE_REQ;

प्रकार काष्ठा smb_com_ग_लिखो_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 6 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__le16 Count;
	__le16 Reमुख्यing;
	__le16 CountHigh;
	__u16  Reserved;
	__u16 ByteCount;
पूर्ण __attribute__((packed)) WRITE_RSP;

/* legacy पढ़ो request क्रम older servers */
प्रकार काष्ठा smb_com_पढ़ोx_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 10 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__u16 Fid;
	__le32 OffsetLow;
	__le16 MaxCount;
	__le16 MinCount;	/* obsolete */
	__le32 Reserved;
	__le16 Reमुख्यing;
	__le16 ByteCount;
पूर्ण __attribute__((packed)) READX_REQ;

प्रकार काष्ठा smb_com_पढ़ो_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 12 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__u16 Fid;
	__le32 OffsetLow;
	__le16 MaxCount;
	__le16 MinCount;		/* obsolete */
	__le32 MaxCountHigh;
	__le16 Reमुख्यing;
	__le32 OffsetHigh;
	__le16 ByteCount;
पूर्ण __attribute__((packed)) READ_REQ;

प्रकार काष्ठा smb_com_पढ़ो_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 12 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__le16 Reमुख्यing;
	__le16 DataCompactionMode;
	__le16 Reserved;
	__le16 DataLength;
	__le16 DataOffset;
	__le16 DataLengthHigh;
	__u64 Reserved2;
	__u16 ByteCount;
	/* पढ़ो response data immediately follows */
पूर्ण __attribute__((packed)) READ_RSP;

प्रकार काष्ठा locking_andx_range अणु
	__le16 Pid;
	__le16 Pad;
	__le32 OffsetHigh;
	__le32 OffsetLow;
	__le32 LengthHigh;
	__le32 LengthLow;
पूर्ण __attribute__((packed)) LOCKING_ANDX_RANGE;

#घोषणा LOCKING_ANDX_SHARED_LOCK     0x01
#घोषणा LOCKING_ANDX_OPLOCK_RELEASE  0x02
#घोषणा LOCKING_ANDX_CHANGE_LOCKTYPE 0x04
#घोषणा LOCKING_ANDX_CANCEL_LOCK     0x08
#घोषणा LOCKING_ANDX_LARGE_खाताS     0x10	/* always on क्रम us */

प्रकार काष्ठा smb_com_lock_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 8 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__u16 Fid;
	__u8 LockType;
	__u8 OplockLevel;
	__le32 Timeout;
	__le16 NumberOfUnlocks;
	__le16 NumberOfLocks;
	__le16 ByteCount;
	LOCKING_ANDX_RANGE Locks[1];
पूर्ण __attribute__((packed)) LOCK_REQ;

/* lock type */
#घोषणा CIFS_RDLCK	0
#घोषणा CIFS_WRLCK	1
#घोषणा CIFS_UNLCK      2
प्रकार काष्ठा cअगरs_posix_lock अणु
	__le16  lock_type;  /* 0 = Read, 1 = Write, 2 = Unlock */
	__le16  lock_flags; /* 1 = Wait (only valid क्रम setlock) */
	__le32  pid;
	__le64	start;
	__le64	length;
	/* BB what about additional owner info to identअगरy network client */
पूर्ण __attribute__((packed)) CIFS_POSIX_LOCK;

प्रकार काष्ठा smb_com_lock_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 2 */
	__u8 AndXCommand;
	__u8 AndXReserved;
	__le16 AndXOffset;
	__u16 ByteCount;
पूर्ण __attribute__((packed)) LOCK_RSP;

प्रकार काष्ठा smb_com_नाम_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 1 */
	__le16 SearchAttributes;	/* target file attributes */
	__le16 ByteCount;
	__u8 BufferFormat;	/* 4 = ASCII or Unicode */
	अचिन्हित अक्षर OldFileName[1];
	/* followed by __u8 BufferFormat2 */
	/* followed by NewFileName */
पूर्ण __attribute__((packed)) RENAME_REQ;

	/* copy request flags */
#घोषणा COPY_MUST_BE_खाता      0x0001
#घोषणा COPY_MUST_BE_सूची       0x0002
#घोषणा COPY_TARGET_MODE_ASCII 0x0004 /* अगर not set, binary */
#घोषणा COPY_SOURCE_MODE_ASCII 0x0008 /* अगर not set, binary */
#घोषणा COPY_VERIFY_WRITES     0x0010
#घोषणा COPY_TREE              0x0020

प्रकार काष्ठा smb_com_copy_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 3 */
	__u16 Tid2;
	__le16 OpenFunction;
	__le16 Flags;
	__le16 ByteCount;
	__u8 BufferFormat;	/* 4 = ASCII or Unicode */
	अचिन्हित अक्षर OldFileName[1];
	/* followed by __u8 BufferFormat2 */
	/* followed by NewFileName string */
पूर्ण __attribute__((packed)) COPY_REQ;

प्रकार काष्ठा smb_com_copy_rsp अणु
	काष्ठा smb_hdr hdr;     /* wct = 1 */
	__le16 CopyCount;    /* number of files copied */
	__u16 ByteCount;    /* may be zero */
	__u8 BufferFormat;  /* 0x04 - only present अगर errored file follows */
	अचिन्हित अक्षर ErrorFileName[1]; /* only present अगर error in copy */
पूर्ण __attribute__((packed)) COPY_RSP;

#घोषणा CREATE_HARD_LINK		0x103
#घोषणा MOVEखाता_COPY_ALLOWED		0x0002
#घोषणा MOVEखाता_REPLACE_EXISTING	0x0001

प्रकार काष्ठा smb_com_nt_नाम_req अणु	/* A5 - also used क्रम create hardlink */
	काष्ठा smb_hdr hdr;	/* wct = 4 */
	__le16 SearchAttributes;	/* target file attributes */
	__le16 Flags;		/* spec says Inक्रमmation Level */
	__le32 ClusterCount;
	__le16 ByteCount;
	__u8 BufferFormat;	/* 4 = ASCII or Unicode */
	अचिन्हित अक्षर OldFileName[1];
	/* followed by __u8 BufferFormat2 */
	/* followed by NewFileName */
पूर्ण __attribute__((packed)) NT_RENAME_REQ;

प्रकार काष्ठा smb_com_नाम_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 0 */
	__u16 ByteCount;	/* bct = 0 */
पूर्ण __attribute__((packed)) RENAME_RSP;

प्रकार काष्ठा smb_com_delete_file_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 1 */
	__le16 SearchAttributes;
	__le16 ByteCount;
	__u8 BufferFormat;	/* 4 = ASCII */
	अचिन्हित अक्षर fileName[1];
पूर्ण __attribute__((packed)) DELETE_खाता_REQ;

प्रकार काष्ठा smb_com_delete_file_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 0 */
	__u16 ByteCount;	/* bct = 0 */
पूर्ण __attribute__((packed)) DELETE_खाता_RSP;

प्रकार काष्ठा smb_com_delete_directory_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 0 */
	__le16 ByteCount;
	__u8 BufferFormat;	/* 4 = ASCII */
	अचिन्हित अक्षर DirName[1];
पूर्ण __attribute__((packed)) DELETE_सूचीECTORY_REQ;

प्रकार काष्ठा smb_com_delete_directory_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 0 */
	__u16 ByteCount;	/* bct = 0 */
पूर्ण __attribute__((packed)) DELETE_सूचीECTORY_RSP;

प्रकार काष्ठा smb_com_create_directory_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 0 */
	__le16 ByteCount;
	__u8 BufferFormat;	/* 4 = ASCII */
	अचिन्हित अक्षर DirName[1];
पूर्ण __attribute__((packed)) CREATE_सूचीECTORY_REQ;

प्रकार काष्ठा smb_com_create_directory_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 0 */
	__u16 ByteCount;	/* bct = 0 */
पूर्ण __attribute__((packed)) CREATE_सूचीECTORY_RSP;

प्रकार काष्ठा smb_com_query_inक्रमmation_req अणु
	काष्ठा smb_hdr hdr;     /* wct = 0 */
	__le16 ByteCount;	/* 1 + namelen + 1 */
	__u8 BufferFormat;      /* 4 = ASCII */
	अचिन्हित अक्षर FileName[1];
पूर्ण __attribute__((packed)) QUERY_INFORMATION_REQ;

प्रकार काष्ठा smb_com_query_inक्रमmation_rsp अणु
	काष्ठा smb_hdr hdr;     /* wct = 10 */
	__le16 attr;
	__le32  last_ग_लिखो_समय;
	__le32 size;
	__u16  reserved[5];
	__le16 ByteCount;	/* bcc = 0 */
पूर्ण __attribute__((packed)) QUERY_INFORMATION_RSP;

प्रकार काष्ठा smb_com_setattr_req अणु
	काष्ठा smb_hdr hdr; /* wct = 8 */
	__le16 attr;
	__le16 समय_low;
	__le16 समय_high;
	__le16 reserved[5]; /* must be zero */
	__u16  ByteCount;
	__u8   BufferFormat; /* 4 = ASCII */
	अचिन्हित अक्षर fileName[1];
पूर्ण __attribute__((packed)) SETATTR_REQ;

प्रकार काष्ठा smb_com_setattr_rsp अणु
	काष्ठा smb_hdr hdr;     /* wct = 0 */
	__u16 ByteCount;        /* bct = 0 */
पूर्ण __attribute__((packed)) SETATTR_RSP;

/* empty wct response to setattr */

/*******************************************************/
/* NT Transact काष्ठाure definitions follow            */
/* Currently only ioctl, acl (get security descriptor) */
/* and notअगरy are implemented                          */
/*******************************************************/
प्रकार काष्ठा smb_com_ntransact_req अणु
	काष्ठा smb_hdr hdr; /* wct >= 19 */
	__u8 MaxSetupCount;
	__u16 Reserved;
	__le32 TotalParameterCount;
	__le32 TotalDataCount;
	__le32 MaxParameterCount;
	__le32 MaxDataCount;
	__le32 ParameterCount;
	__le32 ParameterOffset;
	__le32 DataCount;
	__le32 DataOffset;
	__u8 SetupCount; /* four setup words follow subcommand */
	/* SNIA spec incorrectly included spurious pad here */
	__le16 SubCommand; /* 2 = IOCTL/FSCTL */
	/* SetupCount words follow then */
	__le16 ByteCount;
	__u8 Pad[3];
	__u8 Parms[];
पूर्ण __attribute__((packed)) NTRANSACT_REQ;

प्रकार काष्ठा smb_com_ntransact_rsp अणु
	काष्ठा smb_hdr hdr;     /* wct = 18 */
	__u8 Reserved[3];
	__le32 TotalParameterCount;
	__le32 TotalDataCount;
	__le32 ParameterCount;
	__le32 ParameterOffset;
	__le32 ParameterDisplacement;
	__le32 DataCount;
	__le32 DataOffset;
	__le32 DataDisplacement;
	__u8 SetupCount;   /* 0 */
	__u16 ByteCount;
	/* __u8 Pad[3]; */
	/* parms and data follow */
पूर्ण __attribute__((packed)) NTRANSACT_RSP;

/* See MS-SMB 2.2.7.2.1.1 */
काष्ठा srv_copychunk अणु
	__le64 SourceOffset;
	__le64 DestinationOffset;
	__le32 CopyLength;
	__u32  Reserved;
पूर्ण __packed;

प्रकार काष्ठा smb_com_transaction_ioctl_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 23 */
	__u8 MaxSetupCount;
	__u16 Reserved;
	__le32 TotalParameterCount;
	__le32 TotalDataCount;
	__le32 MaxParameterCount;
	__le32 MaxDataCount;
	__le32 ParameterCount;
	__le32 ParameterOffset;
	__le32 DataCount;
	__le32 DataOffset;
	__u8 SetupCount; /* four setup words follow subcommand */
	/* SNIA spec incorrectly included spurious pad here */
	__le16 SubCommand; /* 2 = IOCTL/FSCTL */
	__le32 FunctionCode;
	__u16 Fid;
	__u8 IsFsctl;  /* 1 = File System Control 0 = device control (IOCTL) */
	__u8 IsRootFlag; /* 1 = apply command to root of share (must be DFS) */
	__le16 ByteCount;
	__u8 Pad[3];
	__u8 Data[1];
पूर्ण __attribute__((packed)) TRANSACT_IOCTL_REQ;

प्रकार काष्ठा smb_com_transaction_compr_ioctl_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 23 */
	__u8 MaxSetupCount;
	__u16 Reserved;
	__le32 TotalParameterCount;
	__le32 TotalDataCount;
	__le32 MaxParameterCount;
	__le32 MaxDataCount;
	__le32 ParameterCount;
	__le32 ParameterOffset;
	__le32 DataCount;
	__le32 DataOffset;
	__u8 SetupCount; /* four setup words follow subcommand */
	/* SNIA spec incorrectly included spurious pad here */
	__le16 SubCommand; /* 2 = IOCTL/FSCTL */
	__le32 FunctionCode;
	__u16 Fid;
	__u8 IsFsctl;  /* 1 = File System Control 0 = device control (IOCTL) */
	__u8 IsRootFlag; /* 1 = apply command to root of share (must be DFS) */
	__le16 ByteCount;
	__u8 Pad[3];
	__le16 compression_state;  /* See below क्रम valid flags */
पूर्ण __attribute__((packed)) TRANSACT_COMPR_IOCTL_REQ;

/* compression state flags */
#घोषणा COMPRESSION_FORMAT_NONE		0x0000
#घोषणा COMPRESSION_FORMAT_DEFAULT	0x0001
#घोषणा COMPRESSION_FORMAT_LZNT1	0x0002

प्रकार काष्ठा smb_com_transaction_ioctl_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 19 */
	__u8 Reserved[3];
	__le32 TotalParameterCount;
	__le32 TotalDataCount;
	__le32 ParameterCount;
	__le32 ParameterOffset;
	__le32 ParameterDisplacement;
	__le32 DataCount;
	__le32 DataOffset;
	__le32 DataDisplacement;
	__u8 SetupCount;	/* 1 */
	__le16 ReturnedDataLen;
	__u16 ByteCount;
पूर्ण __attribute__((packed)) TRANSACT_IOCTL_RSP;

#घोषणा CIFS_ACL_OWNER 1
#घोषणा CIFS_ACL_GROUP 2
#घोषणा CIFS_ACL_DACL  4
#घोषणा CIFS_ACL_SACL  8

प्रकार काष्ठा smb_com_transaction_qsec_req अणु
	काष्ठा smb_hdr hdr;     /* wct = 19 */
	__u8 MaxSetupCount;
	__u16 Reserved;
	__le32 TotalParameterCount;
	__le32 TotalDataCount;
	__le32 MaxParameterCount;
	__le32 MaxDataCount;
	__le32 ParameterCount;
	__le32 ParameterOffset;
	__le32 DataCount;
	__le32 DataOffset;
	__u8 SetupCount; /* no setup words follow subcommand */
	/* SNIA spec incorrectly included spurious pad here */
	__le16 SubCommand; /* 6 = QUERY_SECURITY_DESC */
	__le16 ByteCount; /* bcc = 3 + 8 */
	__u8 Pad[3];
	__u16 Fid;
	__u16 Reserved2;
	__le32 AclFlags;
पूर्ण __attribute__((packed)) QUERY_SEC_DESC_REQ;


प्रकार काष्ठा smb_com_transaction_ssec_req अणु
	काष्ठा smb_hdr hdr;     /* wct = 19 */
	__u8 MaxSetupCount;
	__u16 Reserved;
	__le32 TotalParameterCount;
	__le32 TotalDataCount;
	__le32 MaxParameterCount;
	__le32 MaxDataCount;
	__le32 ParameterCount;
	__le32 ParameterOffset;
	__le32 DataCount;
	__le32 DataOffset;
	__u8 SetupCount; /* no setup words follow subcommand */
	/* SNIA spec incorrectly included spurious pad here */
	__le16 SubCommand; /* 3 = SET_SECURITY_DESC */
	__le16 ByteCount; /* bcc = 3 + 8 */
	__u8 Pad[3];
	__u16 Fid;
	__u16 Reserved2;
	__le32 AclFlags;
पूर्ण __attribute__((packed)) SET_SEC_DESC_REQ;

प्रकार काष्ठा smb_com_transaction_change_notअगरy_req अणु
	काष्ठा smb_hdr hdr;     /* wct = 23 */
	__u8 MaxSetupCount;
	__u16 Reserved;
	__le32 TotalParameterCount;
	__le32 TotalDataCount;
	__le32 MaxParameterCount;
	__le32 MaxDataCount;
	__le32 ParameterCount;
	__le32 ParameterOffset;
	__le32 DataCount;
	__le32 DataOffset;
	__u8 SetupCount; /* four setup words follow subcommand */
	/* SNIA spec incorrectly included spurious pad here */
	__le16 SubCommand;/* 4 = Change Notअगरy */
	__le32 CompletionFilter;  /* operation to monitor */
	__u16 Fid;
	__u8 WatchTree;  /* 1 = Monitor subdirectories */
	__u8 Reserved2;
	__le16 ByteCount;
/* 	__u8 Pad[3];*/
/*	__u8 Data[1];*/
पूर्ण __attribute__((packed)) TRANSACT_CHANGE_NOTIFY_REQ;

/* BB eventually change to use generic ntransact rsp काष्ठा
      and validation routine */
प्रकार काष्ठा smb_com_transaction_change_notअगरy_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 18 */
	__u8 Reserved[3];
	__le32 TotalParameterCount;
	__le32 TotalDataCount;
	__le32 ParameterCount;
	__le32 ParameterOffset;
	__le32 ParameterDisplacement;
	__le32 DataCount;
	__le32 DataOffset;
	__le32 DataDisplacement;
	__u8 SetupCount;   /* 0 */
	__u16 ByteCount;
	/* __u8 Pad[3]; */
पूर्ण __attribute__((packed)) TRANSACT_CHANGE_NOTIFY_RSP;
/* Completion Filter flags क्रम Notअगरy */
#घोषणा खाता_NOTIFY_CHANGE_खाता_NAME    0x00000001
#घोषणा खाता_NOTIFY_CHANGE_सूची_NAME     0x00000002
#घोषणा खाता_NOTIFY_CHANGE_NAME         0x00000003
#घोषणा खाता_NOTIFY_CHANGE_ATTRIBUTES   0x00000004
#घोषणा खाता_NOTIFY_CHANGE_SIZE         0x00000008
#घोषणा खाता_NOTIFY_CHANGE_LAST_WRITE   0x00000010
#घोषणा खाता_NOTIFY_CHANGE_LAST_ACCESS  0x00000020
#घोषणा खाता_NOTIFY_CHANGE_CREATION     0x00000040
#घोषणा खाता_NOTIFY_CHANGE_EA           0x00000080
#घोषणा खाता_NOTIFY_CHANGE_SECURITY     0x00000100
#घोषणा खाता_NOTIFY_CHANGE_STREAM_NAME  0x00000200
#घोषणा खाता_NOTIFY_CHANGE_STREAM_SIZE  0x00000400
#घोषणा खाता_NOTIFY_CHANGE_STREAM_WRITE 0x00000800

#घोषणा खाता_ACTION_ADDED		0x00000001
#घोषणा खाता_ACTION_REMOVED		0x00000002
#घोषणा खाता_ACTION_MODIFIED		0x00000003
#घोषणा खाता_ACTION_RENAMED_OLD_NAME	0x00000004
#घोषणा खाता_ACTION_RENAMED_NEW_NAME	0x00000005
#घोषणा खाता_ACTION_ADDED_STREAM	0x00000006
#घोषणा खाता_ACTION_REMOVED_STREAM	0x00000007
#घोषणा खाता_ACTION_MODIFIED_STREAM	0x00000008

/* response contains array of the following काष्ठाures */
काष्ठा file_notअगरy_inक्रमmation अणु
	__le32 NextEntryOffset;
	__le32 Action;
	__le32 FileNameLength;
	__u8  FileName[];
पूर्ण __attribute__((packed));

/* For IO_REPARSE_TAG_SYMLINK */
काष्ठा reparse_symlink_data अणु
	__le32	ReparseTag;
	__le16	ReparseDataLength;
	__u16	Reserved;
	__le16	SubstituteNameOffset;
	__le16	SubstituteNameLength;
	__le16	Prपूर्णांकNameOffset;
	__le16	Prपूर्णांकNameLength;
	__le32	Flags;
	अक्षर	PathBuffer[];
पूर्ण __attribute__((packed));

/* Flag above */
#घोषणा SYMLINK_FLAG_RELATIVE 0x00000001

/* For IO_REPARSE_TAG_NFS */
#घोषणा NFS_SPECखाता_LNK	0x00000000014B4E4C
#घोषणा NFS_SPECखाता_CHR	0x0000000000524843
#घोषणा NFS_SPECखाता_BLK	0x00000000004B4C42
#घोषणा NFS_SPECखाता_FIFO	0x000000004F464946
#घोषणा NFS_SPECखाता_SOCK	0x000000004B434F53
काष्ठा reparse_posix_data अणु
	__le32	ReparseTag;
	__le16	ReparseDataLength;
	__u16	Reserved;
	__le64	InodeType; /* LNK, FIFO, CHR etc. */
	अक्षर	PathBuffer[];
पूर्ण __attribute__((packed));

काष्ठा cअगरs_quota_data अणु
	__u32	rsrvd1;  /* 0 */
	__u32	sid_size;
	__u64	rsrvd2;  /* 0 */
	__u64	space_used;
	__u64	soft_limit;
	__u64	hard_limit;
	अक्षर	sid[1];  /* variable size? */
पूर्ण __attribute__((packed));

/* quota sub commands */
#घोषणा QUOTA_LIST_CONTINUE	    0
#घोषणा QUOTA_LIST_START	0x100
#घोषणा QUOTA_FOR_SID		0x101

काष्ठा trans2_req अणु
	/* काष्ठा smb_hdr hdr precedes. Set wct = 14+ */
	__le16 TotalParameterCount;
	__le16 TotalDataCount;
	__le16 MaxParameterCount;
	__le16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Reserved;
	__le16 Flags;
	__le32 Timeout;
	__u16 Reserved2;
	__le16 ParameterCount;
	__le16 ParameterOffset;
	__le16 DataCount;
	__le16 DataOffset;
	__u8 SetupCount;
	__u8 Reserved3;
	__le16 SubCommand; /* 1st setup word - SetupCount words follow */
	__le16 ByteCount;
पूर्ण __attribute__((packed));

काष्ठा smb_t2_req अणु
	काष्ठा smb_hdr hdr;
	काष्ठा trans2_req t2_req;
पूर्ण __attribute__((packed));

काष्ठा trans2_resp अणु
	/* काष्ठा smb_hdr hdr precedes. Note wct = 10 + setup count */
	__le16 TotalParameterCount;
	__le16 TotalDataCount;
	__u16 Reserved;
	__le16 ParameterCount;
	__le16 ParameterOffset;
	__le16 ParameterDisplacement;
	__le16 DataCount;
	__le16 DataOffset;
	__le16 DataDisplacement;
	__u8 SetupCount;
	__u8 Reserved1;
	/* SetupWords[SetupCount];
	__u16 ByteCount;
	__u16 Reserved2;*/
	/* data area follows */
पूर्ण __attribute__((packed));

काष्ठा smb_t2_rsp अणु
	काष्ठा smb_hdr hdr;
	काष्ठा trans2_resp t2_rsp;
पूर्ण __attribute__((packed));

/* PathInfo/FileInfo infolevels */
#घोषणा SMB_INFO_STANDARD                   1
#घोषणा SMB_SET_खाता_EA                     2
#घोषणा SMB_QUERY_खाता_EA_SIZE              2
#घोषणा SMB_INFO_QUERY_EAS_FROM_LIST        3
#घोषणा SMB_INFO_QUERY_ALL_EAS              4
#घोषणा SMB_INFO_IS_NAME_VALID              6
#घोषणा SMB_QUERY_खाता_BASIC_INFO       0x101
#घोषणा SMB_QUERY_खाता_STANDARD_INFO    0x102
#घोषणा SMB_QUERY_खाता_EA_INFO          0x103
#घोषणा SMB_QUERY_खाता_NAME_INFO        0x104
#घोषणा SMB_QUERY_खाता_ALLOCATION_INFO  0x105
#घोषणा SMB_QUERY_खाता_END_OF_खाताINFO  0x106
#घोषणा SMB_QUERY_खाता_ALL_INFO         0x107
#घोषणा SMB_QUERY_ALT_NAME_INFO         0x108
#घोषणा SMB_QUERY_खाता_STREAM_INFO      0x109
#घोषणा SMB_QUERY_खाता_COMPRESSION_INFO 0x10B
#घोषणा SMB_QUERY_खाता_UNIX_BASIC       0x200
#घोषणा SMB_QUERY_खाता_UNIX_LINK        0x201
#घोषणा SMB_QUERY_POSIX_ACL             0x204
#घोषणा SMB_QUERY_XATTR                 0x205  /* e.g. प्रणाली EA name space */
#घोषणा SMB_QUERY_ATTR_FLAGS            0x206  /* append,immutable etc. */
#घोषणा SMB_QUERY_POSIX_PERMISSION      0x207
#घोषणा SMB_QUERY_POSIX_LOCK            0x208
/* #घोषणा SMB_POSIX_OPEN               0x209 */
/* #घोषणा SMB_POSIX_UNLINK             0x20a */
#घोषणा SMB_QUERY_खाता__UNIX_INFO2      0x20b
#घोषणा SMB_QUERY_खाता_INTERNAL_INFO    0x3ee
#घोषणा SMB_QUERY_खाता_ACCESS_INFO      0x3f0
#घोषणा SMB_QUERY_खाता_NAME_INFO2       0x3f1 /* 0x30 bytes */
#घोषणा SMB_QUERY_खाता_POSITION_INFO    0x3f6
#घोषणा SMB_QUERY_खाता_MODE_INFO        0x3f8
#घोषणा SMB_QUERY_खाता_ALGN_INFO        0x3f9


#घोषणा SMB_SET_खाता_BASIC_INFO	        0x101
#घोषणा SMB_SET_खाता_DISPOSITION_INFO   0x102
#घोषणा SMB_SET_खाता_ALLOCATION_INFO    0x103
#घोषणा SMB_SET_खाता_END_OF_खाता_INFO   0x104
#घोषणा SMB_SET_खाता_UNIX_BASIC         0x200
#घोषणा SMB_SET_खाता_UNIX_LINK          0x201
#घोषणा SMB_SET_खाता_UNIX_HLINK         0x203
#घोषणा SMB_SET_POSIX_ACL               0x204
#घोषणा SMB_SET_XATTR                   0x205
#घोषणा SMB_SET_ATTR_FLAGS              0x206  /* append, immutable etc. */
#घोषणा SMB_SET_POSIX_LOCK              0x208
#घोषणा SMB_POSIX_OPEN                  0x209
#घोषणा SMB_POSIX_UNLINK                0x20a
#घोषणा SMB_SET_खाता_UNIX_INFO2         0x20b
#घोषणा SMB_SET_खाता_BASIC_INFO2        0x3ec
#घोषणा SMB_SET_खाता_RENAME_INFORMATION 0x3f2 /* BB check अगर qpathinfo too */
#घोषणा SMB_खाता_ALL_INFO2              0x3fa
#घोषणा SMB_SET_खाता_ALLOCATION_INFO2   0x3fb
#घोषणा SMB_SET_खाता_END_OF_खाता_INFO2  0x3fc
#घोषणा SMB_खाता_MOVE_CLUSTER_INFO      0x407
#घोषणा SMB_खाता_QUOTA_INFO             0x408
#घोषणा SMB_खाता_REPARSEPOINT_INFO      0x409
#घोषणा SMB_खाता_MAXIMUM_INFO           0x40d

/* Find File infolevels */
#घोषणा SMB_FIND_खाता_INFO_STANDARD       0x001
#घोषणा SMB_FIND_खाता_QUERY_EA_SIZE       0x002
#घोषणा SMB_FIND_खाता_QUERY_EAS_FROM_LIST 0x003
#घोषणा SMB_FIND_खाता_सूचीECTORY_INFO      0x101
#घोषणा SMB_FIND_खाता_FULL_सूचीECTORY_INFO 0x102
#घोषणा SMB_FIND_खाता_NAMES_INFO          0x103
#घोषणा SMB_FIND_खाता_BOTH_सूचीECTORY_INFO 0x104
#घोषणा SMB_FIND_खाता_ID_FULL_सूची_INFO    0x105
#घोषणा SMB_FIND_खाता_ID_BOTH_सूची_INFO    0x106
#घोषणा SMB_FIND_खाता_UNIX                0x202
#घोषणा SMB_FIND_खाता_POSIX_INFO          0x064

प्रकार काष्ठा smb_com_transaction2_qpi_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 14+ */
	__le16 TotalParameterCount;
	__le16 TotalDataCount;
	__le16 MaxParameterCount;
	__le16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Reserved;
	__le16 Flags;
	__le32 Timeout;
	__u16 Reserved2;
	__le16 ParameterCount;
	__le16 ParameterOffset;
	__le16 DataCount;
	__le16 DataOffset;
	__u8 SetupCount;
	__u8 Reserved3;
	__le16 SubCommand;	/* one setup word */
	__le16 ByteCount;
	__u8 Pad;
	__le16 Inक्रमmationLevel;
	__u32 Reserved4;
	अक्षर FileName[1];
पूर्ण __attribute__((packed)) TRANSACTION2_QPI_REQ;

प्रकार काष्ठा smb_com_transaction2_qpi_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 10 + SetupCount */
	काष्ठा trans2_resp t2;
	__u16 ByteCount;
	__u16 Reserved2; /* parameter word is present क्रम infolevels > 100 */
पूर्ण __attribute__((packed)) TRANSACTION2_QPI_RSP;

प्रकार काष्ठा smb_com_transaction2_spi_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 15 */
	__le16 TotalParameterCount;
	__le16 TotalDataCount;
	__le16 MaxParameterCount;
	__le16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Reserved;
	__le16 Flags;
	__le32 Timeout;
	__u16 Reserved2;
	__le16 ParameterCount;
	__le16 ParameterOffset;
	__le16 DataCount;
	__le16 DataOffset;
	__u8 SetupCount;
	__u8 Reserved3;
	__le16 SubCommand;	/* one setup word */
	__le16 ByteCount;
	__u8 Pad;
	__u16 Pad1;
	__le16 Inक्रमmationLevel;
	__u32 Reserved4;
	अक्षर FileName[1];
पूर्ण __attribute__((packed)) TRANSACTION2_SPI_REQ;

प्रकार काष्ठा smb_com_transaction2_spi_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 10 + SetupCount */
	काष्ठा trans2_resp t2;
	__u16 ByteCount;
	__u16 Reserved2; /* parameter word is present क्रम infolevels > 100 */
पूर्ण __attribute__((packed)) TRANSACTION2_SPI_RSP;

काष्ठा set_file_नाम अणु
	__le32 overग_लिखो;   /* 1 = overग_लिखो dest */
	__u32 root_fid;   /* zero */
	__le32 target_name_len;
	अक्षर  target_name[];  /* Must be unicode */
पूर्ण __attribute__((packed));

काष्ठा smb_com_transaction2_sfi_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 15 */
	__le16 TotalParameterCount;
	__le16 TotalDataCount;
	__le16 MaxParameterCount;
	__le16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Reserved;
	__le16 Flags;
	__le32 Timeout;
	__u16 Reserved2;
	__le16 ParameterCount;
	__le16 ParameterOffset;
	__le16 DataCount;
	__le16 DataOffset;
	__u8 SetupCount;
	__u8 Reserved3;
	__le16 SubCommand;	/* one setup word */
	__le16 ByteCount;
	__u8 Pad;
	__u16 Pad1;
	__u16 Fid;
	__le16 Inक्रमmationLevel;
	__u16 Reserved4;
पूर्ण __attribute__((packed));

काष्ठा smb_com_transaction2_sfi_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 10 + SetupCount */
	काष्ठा trans2_resp t2;
	__u16 ByteCount;
	__u16 Reserved2;	/* parameter word reserved -
					present क्रम infolevels > 100 */
पूर्ण __attribute__((packed));

काष्ठा smb_t2_qfi_req अणु
	काष्ठा	smb_hdr hdr;
	काष्ठा	trans2_req t2;
	__u8	Pad;
	__u16	Fid;
	__le16	Inक्रमmationLevel;
पूर्ण __attribute__((packed));

काष्ठा smb_t2_qfi_rsp अणु
	काष्ठा smb_hdr hdr;     /* wct = 10 + SetupCount */
	काष्ठा trans2_resp t2;
	__u16 ByteCount;
	__u16 Reserved2;        /* parameter word reserved -
				   present क्रम infolevels > 100 */
पूर्ण __attribute__((packed));

/*
 * Flags on T2 FINDFIRST and FINDNEXT
 */
#घोषणा CIFS_SEARCH_CLOSE_ALWAYS  0x0001
#घोषणा CIFS_SEARCH_CLOSE_AT_END  0x0002
#घोषणा CIFS_SEARCH_RETURN_RESUME 0x0004
#घोषणा CIFS_SEARCH_CONTINUE_FROM_LAST 0x0008
#घोषणा CIFS_SEARCH_BACKUP_SEARCH 0x0010

/*
 * Size of the resume key on FINDFIRST and FINDNEXT calls
 */
#घोषणा CIFS_SMB_RESUME_KEY_SIZE 4

प्रकार काष्ठा smb_com_transaction2_ffirst_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 15 */
	__le16 TotalParameterCount;
	__le16 TotalDataCount;
	__le16 MaxParameterCount;
	__le16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Reserved;
	__le16 Flags;
	__le32 Timeout;
	__u16 Reserved2;
	__le16 ParameterCount;
	__le16 ParameterOffset;
	__le16 DataCount;
	__le16 DataOffset;
	__u8 SetupCount;	/* one */
	__u8 Reserved3;
	__le16 SubCommand;	/* TRANS2_FIND_FIRST */
	__le16 ByteCount;
	__u8 Pad;
	__le16 SearchAttributes;
	__le16 SearchCount;
	__le16 SearchFlags;
	__le16 Inक्रमmationLevel;
	__le32 SearchStorageType;
	अक्षर FileName[1];
पूर्ण __attribute__((packed)) TRANSACTION2_FFIRST_REQ;

प्रकार काष्ठा smb_com_transaction2_ffirst_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 10 */
	काष्ठा trans2_resp t2;
	__u16 ByteCount;
पूर्ण __attribute__((packed)) TRANSACTION2_FFIRST_RSP;

प्रकार काष्ठा smb_com_transaction2_ffirst_rsp_parms अणु
	__u16 SearchHandle;
	__le16 SearchCount;
	__le16 EnकरोfSearch;
	__le16 EAErrorOffset;
	__le16 LastNameOffset;
पूर्ण __attribute__((packed)) T2_FFIRST_RSP_PARMS;

प्रकार काष्ठा smb_com_transaction2_fnext_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 15 */
	__le16 TotalParameterCount;
	__le16 TotalDataCount;
	__le16 MaxParameterCount;
	__le16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Reserved;
	__le16 Flags;
	__le32 Timeout;
	__u16 Reserved2;
	__le16 ParameterCount;
	__le16 ParameterOffset;
	__le16 DataCount;
	__le16 DataOffset;
	__u8 SetupCount;	/* one */
	__u8 Reserved3;
	__le16 SubCommand;	/* TRANS2_FIND_NEXT */
	__le16 ByteCount;
	__u8 Pad;
	__u16 SearchHandle;
	__le16 SearchCount;
	__le16 Inक्रमmationLevel;
	__u32 ResumeKey;
	__le16 SearchFlags;
	अक्षर ResumeFileName[];
पूर्ण __attribute__((packed)) TRANSACTION2_FNEXT_REQ;

प्रकार काष्ठा smb_com_transaction2_fnext_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 10 */
	काष्ठा trans2_resp t2;
	__u16 ByteCount;
पूर्ण __attribute__((packed)) TRANSACTION2_FNEXT_RSP;

प्रकार काष्ठा smb_com_transaction2_fnext_rsp_parms अणु
	__le16 SearchCount;
	__le16 EnकरोfSearch;
	__le16 EAErrorOffset;
	__le16 LastNameOffset;
पूर्ण __attribute__((packed)) T2_FNEXT_RSP_PARMS;

/* QFSInfo Levels */
#घोषणा SMB_INFO_ALLOCATION         1
#घोषणा SMB_INFO_VOLUME             2
#घोषणा SMB_QUERY_FS_VOLUME_INFO    0x102
#घोषणा SMB_QUERY_FS_SIZE_INFO      0x103
#घोषणा SMB_QUERY_FS_DEVICE_INFO    0x104
#घोषणा SMB_QUERY_FS_ATTRIBUTE_INFO 0x105
#घोषणा SMB_QUERY_CIFS_UNIX_INFO    0x200
#घोषणा SMB_QUERY_POSIX_FS_INFO     0x201
#घोषणा SMB_QUERY_POSIX_WHO_AM_I    0x202
#घोषणा SMB_REQUEST_TRANSPORT_ENCRYPTION 0x203
#घोषणा SMB_QUERY_FS_PROXY          0x204 /* WAFS enabled. Returns काष्ठाure
					    खाता_SYSTEM__UNIX_INFO to tell
					    whether new NTIOCTL available
					    (0xACE) क्रम WAN मित्रly SMB
					    operations to be carried */
#घोषणा SMB_QUERY_LABEL_INFO        0x3ea
#घोषणा SMB_QUERY_FS_QUOTA_INFO     0x3ee
#घोषणा SMB_QUERY_FS_FULL_SIZE_INFO 0x3ef
#घोषणा SMB_QUERY_OBJECTID_INFO     0x3f0

प्रकार काष्ठा smb_com_transaction2_qfsi_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 14+ */
	__le16 TotalParameterCount;
	__le16 TotalDataCount;
	__le16 MaxParameterCount;
	__le16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Reserved;
	__le16 Flags;
	__le32 Timeout;
	__u16 Reserved2;
	__le16 ParameterCount;
	__le16 ParameterOffset;
	__le16 DataCount;
	__le16 DataOffset;
	__u8 SetupCount;
	__u8 Reserved3;
	__le16 SubCommand;	/* one setup word */
	__le16 ByteCount;
	__u8 Pad;
	__le16 Inक्रमmationLevel;
पूर्ण __attribute__((packed)) TRANSACTION2_QFSI_REQ;

प्रकार काष्ठा smb_com_transaction_qfsi_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 10 + SetupCount */
	काष्ठा trans2_resp t2;
	__u16 ByteCount;
	__u8 Pad;	/* may be three bytes? *//* followed by data area */
पूर्ण __attribute__((packed)) TRANSACTION2_QFSI_RSP;

प्रकार काष्ठा whoami_rsp_data अणु /* Query level 0x202 */
	__u32 flags; /* 0 = Authenticated user 1 = GUEST */
	__u32 mask; /* which flags bits server understands ie 0x0001 */
	__u64 unix_user_id;
	__u64 unix_user_gid;
	__u32 number_of_supplementary_gids; /* may be zero */
	__u32 number_of_sids; /* may be zero */
	__u32 length_of_sid_array; /* in bytes - may be zero */
	__u32 pad; /* reserved - MBZ */
	/* __u64 gid_array[0]; */  /* may be empty */
	/* __u8 * psid_list */  /* may be empty */
पूर्ण __attribute__((packed)) WHOAMI_RSP_DATA;

/* SETFSInfo Levels */
#घोषणा SMB_SET_CIFS_UNIX_INFO    0x200
/* level 0x203 is defined above in list of QFS info levels */
/* #घोषणा SMB_REQUEST_TRANSPORT_ENCRYPTION 0x203 */

/* Level 0x200 request काष्ठाure follows */
प्रकार काष्ठा smb_com_transaction2_setfsi_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 15 */
	__le16 TotalParameterCount;
	__le16 TotalDataCount;
	__le16 MaxParameterCount;
	__le16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Reserved;
	__le16 Flags;
	__le32 Timeout;
	__u16 Reserved2;
	__le16 ParameterCount;	/* 4 */
	__le16 ParameterOffset;
	__le16 DataCount;	/* 12 */
	__le16 DataOffset;
	__u8 SetupCount;	/* one */
	__u8 Reserved3;
	__le16 SubCommand;	/* TRANS2_SET_FS_INFORMATION */
	__le16 ByteCount;
	__u8 Pad;
	__u16 FileNum;		/* Parameters start. */
	__le16 Inक्रमmationLevel;/* Parameters end. */
	__le16 ClientUnixMajor; /* Data start. */
	__le16 ClientUnixMinor;
	__le64 ClientUnixCap;   /* Data end */
पूर्ण __attribute__((packed)) TRANSACTION2_SETFSI_REQ;

/* level 0x203 request काष्ठाure follows */
प्रकार काष्ठा smb_com_transaction2_setfs_enc_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 15 */
	__le16 TotalParameterCount;
	__le16 TotalDataCount;
	__le16 MaxParameterCount;
	__le16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Reserved;
	__le16 Flags;
	__le32 Timeout;
	__u16 Reserved2;
	__le16 ParameterCount;	/* 4 */
	__le16 ParameterOffset;
	__le16 DataCount;	/* 12 */
	__le16 DataOffset;
	__u8 SetupCount;	/* one */
	__u8 Reserved3;
	__le16 SubCommand;	/* TRANS2_SET_FS_INFORMATION */
	__le16 ByteCount;
	__u8 Pad;
	__u16  Reserved4;	/* Parameters start. */
	__le16 Inक्रमmationLevel;/* Parameters end. */
	/* NTLMSSP Blob, Data start. */
पूर्ण __attribute__((packed)) TRANSACTION2_SETFSI_ENC_REQ;

/* response क्रम setfsinfo levels 0x200 and 0x203 */
प्रकार काष्ठा smb_com_transaction2_setfsi_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 10 */
	काष्ठा trans2_resp t2;
	__u16 ByteCount;
पूर्ण __attribute__((packed)) TRANSACTION2_SETFSI_RSP;

प्रकार काष्ठा smb_com_transaction2_get_dfs_refer_req अणु
	काष्ठा smb_hdr hdr;	/* wct = 15 */
	__le16 TotalParameterCount;
	__le16 TotalDataCount;
	__le16 MaxParameterCount;
	__le16 MaxDataCount;
	__u8 MaxSetupCount;
	__u8 Reserved;
	__le16 Flags;
	__le32 Timeout;
	__u16 Reserved2;
	__le16 ParameterCount;
	__le16 ParameterOffset;
	__le16 DataCount;
	__le16 DataOffset;
	__u8 SetupCount;
	__u8 Reserved3;
	__le16 SubCommand;	/* one setup word */
	__le16 ByteCount;
	__u8 Pad[3];		/* Win2K has sent 0x0F01 (max response length
				   perhaps?) followed by one byte pad - करोesn't
				   seem to matter though */
	__le16 MaxReferralLevel;
	अक्षर RequestFileName[1];
पूर्ण __attribute__((packed)) TRANSACTION2_GET_DFS_REFER_REQ;

#घोषणा DFS_VERSION cpu_to_le16(0x0003)

/* DFS server target type */
#घोषणा DFS_TYPE_LINK 0x0000  /* also क्रम sysvol tarमाला_लो */
#घोषणा DFS_TYPE_ROOT 0x0001

/* Referral Entry Flags */
#घोषणा DFS_NAME_LIST_REF 0x0200 /* set क्रम करोमुख्य or DC referral responses */
#घोषणा DFS_TARGET_SET_BOUNDARY 0x0400 /* only valid with version 4 dfs req */

प्रकार काष्ठा dfs_referral_level_3 अणु /* version 4 is same, + one flag bit */
	__le16 VersionNumber;  /* must be 3 or 4 */
	__le16 Size;
	__le16 ServerType; /* 0x0001 = root tarमाला_लो; 0x0000 = link tarमाला_लो */
	__le16 ReferralEntryFlags;
	__le32 TimeToLive;
	__le16 DfsPathOffset;
	__le16 DfsAlternatePathOffset;
	__le16 NetworkAddressOffset; /* offset of the link target */
	__u8   ServiceSiteGuid[16];  /* MBZ, ignored */
पूर्ण __attribute__((packed)) REFERRAL3;

काष्ठा get_dfs_referral_rsp अणु
	__le16 PathConsumed;
	__le16 NumberOfReferrals;
	__le32 DFSFlags;
	REFERRAL3 referrals[1];	/* array of level 3 dfs_referral काष्ठाures */
	/* followed by the strings poपूर्णांकed to by the referral काष्ठाures */
पूर्ण __packed;

प्रकार काष्ठा smb_com_transaction_get_dfs_refer_rsp अणु
	काष्ठा smb_hdr hdr;	/* wct = 10 */
	काष्ठा trans2_resp t2;
	__u16 ByteCount;
	__u8 Pad;
	काष्ठा get_dfs_referral_rsp dfs_data;
पूर्ण __packed TRANSACTION2_GET_DFS_REFER_RSP;

/* DFS Flags */
#घोषणा DFSREF_REFERRAL_SERVER  0x00000001 /* all tarमाला_लो are DFS roots */
#घोषणा DFSREF_STORAGE_SERVER   0x00000002 /* no further ref requests needed */
#घोषणा DFSREF_TARGET_FAILBACK  0x00000004 /* only क्रम DFS referral version 4 */

/*
 ************************************************************************
 * All काष्ठाs क्रम everything above the SMB PDUs themselves
 * (such as the T2 level specअगरic data) go here
 ************************************************************************
 */

/*
 * Inक्रमmation on a server
 */

काष्ठा serverInfo अणु
	अक्षर name[16];
	अचिन्हित अक्षर versionMajor;
	अचिन्हित अक्षर versionMinor;
	अचिन्हित दीर्घ type;
	अचिन्हित पूर्णांक commentOffset;
पूर्ण __attribute__((packed));

/*
 * The following काष्ठाure is the क्रमmat of the data वापसed on a NetShareEnum
 * with level "90" (x5A)
 */

काष्ठा shareInfo अणु
	अक्षर shareName[13];
	अक्षर pad;
	अचिन्हित लघु type;
	अचिन्हित पूर्णांक commentOffset;
पूर्ण __attribute__((packed));

काष्ठा aliasInfo अणु
	अक्षर aliasName[9];
	अक्षर pad;
	अचिन्हित पूर्णांक commentOffset;
	अचिन्हित अक्षर type[2];
पूर्ण __attribute__((packed));

काष्ठा aliasInfo92 अणु
	पूर्णांक aliasNameOffset;
	पूर्णांक serverNameOffset;
	पूर्णांक shareNameOffset;
पूर्ण __attribute__((packed));

प्रकार काष्ठा अणु
	__le64 TotalAllocationUnits;
	__le64 FreeAllocationUnits;
	__le32 SectorsPerAllocationUnit;
	__le32 BytesPerSector;
पूर्ण __attribute__((packed)) खाता_SYSTEM_INFO;	/* size info, level 0x103 */

प्रकार काष्ठा अणु
	__le32 fsid;
	__le32 SectorsPerAllocationUnit;
	__le32 TotalAllocationUnits;
	__le32 FreeAllocationUnits;
	__le16  BytesPerSector;
पूर्ण __attribute__((packed)) खाता_SYSTEM_ALLOC_INFO;

प्रकार काष्ठा अणु
	__le16 MajorVersionNumber;
	__le16 MinorVersionNumber;
	__le64 Capability;
पूर्ण __attribute__((packed)) खाता_SYSTEM_UNIX_INFO; /* Unix extension level 0x200*/

/* Version numbers क्रम CIFS UNIX major and minor. */
#घोषणा CIFS_UNIX_MAJOR_VERSION 1
#घोषणा CIFS_UNIX_MINOR_VERSION 0

/* Linux/Unix extensions capability flags */
#घोषणा CIFS_UNIX_FCNTL_CAP             0x00000001 /* support क्रम fcntl locks */
#घोषणा CIFS_UNIX_POSIX_ACL_CAP         0x00000002 /* support getfacl/setfacl */
#घोषणा CIFS_UNIX_XATTR_CAP             0x00000004 /* support new namespace   */
#घोषणा CIFS_UNIX_EXTATTR_CAP           0x00000008 /* support chattr/chflag   */
#घोषणा CIFS_UNIX_POSIX_PATHNAMES_CAP   0x00000010 /* Allow POSIX path अक्षरs  */
#घोषणा CIFS_UNIX_POSIX_PATH_OPS_CAP    0x00000020 /* Allow new POSIX path based
						      calls including posix खोलो
						      and posix unlink */
#घोषणा CIFS_UNIX_LARGE_READ_CAP        0x00000040 /* support पढ़ोs >128K (up
						      to 0xFFFF00 */
#घोषणा CIFS_UNIX_LARGE_WRITE_CAP       0x00000080
#घोषणा CIFS_UNIX_TRANSPORT_ENCRYPTION_CAP 0x00000100 /* can करो SPNEGO crypt */
#घोषणा CIFS_UNIX_TRANSPORT_ENCRYPTION_MANDATORY_CAP  0x00000200 /* must करो  */
#घोषणा CIFS_UNIX_PROXY_CAP             0x00000400 /* Proxy cap: 0xACE ioctl and
						      QFS PROXY call */
#अगर_घोषित CONFIG_CIFS_POSIX
/* presumably करोn't need the 0x20 POSIX_PATH_OPS_CAP since we never send
   LockingX instead of posix locking call on unix sess (and we करो not expect
   LockingX to use dअगरferent (ie Winकरोws) semantics than posix locking on
   the same session (अगर WINE needs to करो this later, we can add this cap
   back in later */
/* #घोषणा CIFS_UNIX_CAP_MASK              0x000000fb */
#घोषणा CIFS_UNIX_CAP_MASK              0x000003db
#अन्यथा
#घोषणा CIFS_UNIX_CAP_MASK              0x00000013
#पूर्ण_अगर /* CONFIG_CIFS_POSIX */


#घोषणा CIFS_POSIX_EXTENSIONS           0x00000010 /* support क्रम new QFSInfo */

प्रकार काष्ठा अणु
	/* For undefined recommended transfer size वापस -1 in that field */
	__le32 OptimalTransferSize;  /* bsize on some os, iosize on other os */
	__le32 BlockSize;
    /* The next three fields are in terms of the block size.
	(above). If block size is unknown, 4096 would be a
	reasonable block size क्रम a server to report.
	Note that वापसing the blocks/blocksavail हटाओs need
	to make a second call (to QFSInfo level 0x103 to get this info.
	UserBlockAvail is typically less than or equal to BlocksAvail,
	अगर no distinction is made वापस the same value in each */
	__le64 TotalBlocks;
	__le64 BlocksAvail;       /* bमुक्त */
	__le64 UserBlocksAvail;   /* bavail */
    /* For undefined Node fields or FSID वापस -1 */
	__le64 TotalFileNodes;
	__le64 FreeFileNodes;
	__le64 FileSysIdentअगरier;   /* fsid */
	/* NB Namelen comes from खाता_SYSTEM_ATTRIBUTE_INFO call */
	/* NB flags can come from खाता_SYSTEM_DEVICE_INFO call   */
पूर्ण __attribute__((packed)) खाता_SYSTEM_POSIX_INFO;

/* DeviceType Flags */
#घोषणा खाता_DEVICE_CD_ROM              0x00000002
#घोषणा खाता_DEVICE_CD_ROM_खाता_SYSTEM  0x00000003
#घोषणा खाता_DEVICE_DFS                 0x00000006
#घोषणा खाता_DEVICE_DISK                0x00000007
#घोषणा खाता_DEVICE_DISK_खाता_SYSTEM    0x00000008
#घोषणा खाता_DEVICE_खाता_SYSTEM         0x00000009
#घोषणा खाता_DEVICE_NAMED_PIPE          0x00000011
#घोषणा खाता_DEVICE_NETWORK             0x00000012
#घोषणा खाता_DEVICE_NETWORK_खाता_SYSTEM 0x00000014
#घोषणा खाता_DEVICE_शून्य                0x00000015
#घोषणा खाता_DEVICE_PARALLEL_PORT       0x00000016
#घोषणा खाता_DEVICE_PRINTER             0x00000018
#घोषणा खाता_DEVICE_SERIAL_PORT         0x0000001b
#घोषणा खाता_DEVICE_STREAMS             0x0000001e
#घोषणा खाता_DEVICE_TAPE                0x0000001f
#घोषणा खाता_DEVICE_TAPE_खाता_SYSTEM    0x00000020
#घोषणा खाता_DEVICE_VIRTUAL_DISK        0x00000024
#घोषणा खाता_DEVICE_NETWORK_REसूचीECTOR  0x00000028

/* Device Characteristics */
#घोषणा खाता_REMOVABLE_MEDIA			0x00000001
#घोषणा खाता_READ_ONLY_DEVICE			0x00000002
#घोषणा खाता_FLOPPY_DISKETTE			0x00000004
#घोषणा खाता_WRITE_ONCE_MEDIA			0x00000008
#घोषणा खाता_REMOTE_DEVICE			0x00000010
#घोषणा खाता_DEVICE_IS_MOUNTED			0x00000020
#घोषणा खाता_VIRTUAL_VOLUME			0x00000040
#घोषणा खाता_DEVICE_SECURE_OPEN			0x00000100
#घोषणा खाता_CHARACTERISTIC_TS_DEVICE		0x00001000
#घोषणा खाता_CHARACTERISTIC_WEBDAV_DEVICE	0x00002000
#घोषणा खाता_PORTABLE_DEVICE			0x00004000
#घोषणा खाता_DEVICE_ALLOW_APPCONTAINER_TRAVERSAL 0x00020000

प्रकार काष्ठा अणु
	__le32 DeviceType;
	__le32 DeviceCharacteristics;
पूर्ण __attribute__((packed)) खाता_SYSTEM_DEVICE_INFO; /* device info level 0x104 */

/* minimum includes first three fields, and empty FS Name */
#घोषणा MIN_FS_ATTR_INFO_SIZE 12


/* List of FileSystemAttributes - see 2.5.1 of MS-FSCC */
#घोषणा खाता_SUPPORTS_SPARSE_VDL	0x10000000 /* faster nonsparse extend */
#घोषणा खाता_SUPPORTS_BLOCK_REFCOUNTING	0x08000000 /* allow ioctl dup extents */
#घोषणा खाता_SUPPORT_INTEGRITY_STREAMS	0x04000000
#घोषणा खाता_SUPPORTS_USN_JOURNAL	0x02000000
#घोषणा खाता_SUPPORTS_OPEN_BY_खाता_ID	0x01000000
#घोषणा खाता_SUPPORTS_EXTENDED_ATTRIBUTES 0x00800000
#घोषणा खाता_SUPPORTS_HARD_LINKS	0x00400000
#घोषणा खाता_SUPPORTS_TRANSACTIONS	0x00200000
#घोषणा खाता_SEQUENTIAL_WRITE_ONCE	0x00100000
#घोषणा खाता_READ_ONLY_VOLUME		0x00080000
#घोषणा खाता_NAMED_STREAMS		0x00040000
#घोषणा खाता_SUPPORTS_ENCRYPTION	0x00020000
#घोषणा खाता_SUPPORTS_OBJECT_IDS	0x00010000
#घोषणा खाता_VOLUME_IS_COMPRESSED	0x00008000
#घोषणा खाता_SUPPORTS_REMOTE_STORAGE	0x00000100
#घोषणा खाता_SUPPORTS_REPARSE_POINTS	0x00000080
#घोषणा खाता_SUPPORTS_SPARSE_खाताS	0x00000040
#घोषणा खाता_VOLUME_QUOTAS		0x00000020
#घोषणा खाता_खाता_COMPRESSION		0x00000010
#घोषणा खाता_PERSISTENT_ACLS		0x00000008
#घोषणा खाता_UNICODE_ON_DISK		0x00000004
#घोषणा खाता_CASE_PRESERVED_NAMES	0x00000002
#घोषणा खाता_CASE_SENSITIVE_SEARCH	0x00000001
प्रकार काष्ठा अणु
	__le32 Attributes;
	__le32 MaxPathNameComponentLength;
	__le32 FileSystemNameLen;
	अक्षर FileSystemName[52]; /* करो not have to save this - get subset? */
पूर्ण __attribute__((packed)) खाता_SYSTEM_ATTRIBUTE_INFO;

/******************************************************************************/
/* QueryFileInfo/QueryPathinfo (also क्रम SetPath/SetFile) data buffer क्रमmats */
/******************************************************************************/
प्रकार काष्ठा अणु /* data block encoding of response to level 263 QPathInfo */
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le32 Attributes;
	__u32 Pad1;
	__le64 AllocationSize;
	__le64 EndOfFile;	/* size ie offset to first मुक्त byte in file */
	__le32 NumberOfLinks;	/* hard links */
	__u8 DeletePending;
	__u8 Directory;
	__u16 Pad2;
	__le64 IndexNumber;
	__le32 EASize;
	__le32 AccessFlags;
	__u64 IndexNumber1;
	__le64 CurrentByteOffset;
	__le32 Mode;
	__le32 AlignmentRequirement;
	__le32 FileNameLength;
	अक्षर FileName[1];
पूर्ण __attribute__((packed)) खाता_ALL_INFO;	/* level 0x107 QPathInfo */

प्रकार काष्ठा अणु
	__le64 AllocationSize;
	__le64 EndOfFile;	/* size ie offset to first मुक्त byte in file */
	__le32 NumberOfLinks;	/* hard links */
	__u8 DeletePending;
	__u8 Directory;
	__u16 Pad;
पूर्ण __attribute__((packed)) खाता_STANDARD_INFO;	/* level 0x102 QPathInfo */


/* defines क्रम क्रमागतerating possible values of the Unix type field below */
#घोषणा UNIX_खाता      0
#घोषणा UNIX_सूची       1
#घोषणा UNIX_SYMLINK   2
#घोषणा UNIX_CHARDEV   3
#घोषणा UNIX_BLOCKDEV  4
#घोषणा UNIX_FIFO      5
#घोषणा UNIX_SOCKET    6
प्रकार काष्ठा अणु
	__le64 EndOfFile;
	__le64 NumOfBytes;
	__le64 LastStatusChange; /*SNIA specs DCE समय क्रम the 3 समय fields */
	__le64 LastAccessTime;
	__le64 LastModअगरicationTime;
	__le64 Uid;
	__le64 Gid;
	__le32 Type;
	__le64 DevMajor;
	__le64 DevMinor;
	__le64 UniqueId;
	__le64 Permissions;
	__le64 Nlinks;
पूर्ण __attribute__((packed)) खाता_UNIX_BASIC_INFO;	/* level 0x200 QPathInfo */

प्रकार काष्ठा अणु
	अक्षर LinkDest[1];
पूर्ण __attribute__((packed)) खाता_UNIX_LINK_INFO;	/* level 0x201 QPathInfo */

/* The following three काष्ठाures are needed only क्रम
	setting समय to NT4 and some older servers via
	the primitive DOS समय क्रमmat */
प्रकार काष्ठा अणु
	__u16 Day:5;
	__u16 Month:4;
	__u16 Year:7;
पूर्ण __attribute__((packed)) SMB_DATE;

प्रकार काष्ठा अणु
	__u16 TwoSeconds:5;
	__u16 Minutes:6;
	__u16 Hours:5;
पूर्ण __attribute__((packed)) SMB_TIME;

प्रकार काष्ठा अणु
	__le16 CreationDate; /* SMB Date see above */
	__le16 CreationTime; /* SMB Time */
	__le16 LastAccessDate;
	__le16 LastAccessTime;
	__le16 LastWriteDate;
	__le16 LastWriteTime;
	__le32 DataSize; /* File Size (खातापूर्ण) */
	__le32 AllocationSize;
	__le16 Attributes; /* verअगरy not u32 */
	__le32 EASize;
पूर्ण __attribute__((packed)) खाता_INFO_STANDARD;  /* level 1 SetPath/FileInfo */

प्रकार काष्ठा अणु
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le32 Attributes;
	__u32 Pad;
पूर्ण __attribute__((packed)) खाता_BASIC_INFO;	/* size info, level 0x101 */

काष्ठा file_allocation_info अणु
	__le64 AllocationSize; /* Note old Samba srvr rounds this up too much */
पूर्ण __attribute__((packed));	/* size used on disk, क्रम level 0x103 क्रम set,
				   0x105 क्रम query */

काष्ठा file_end_of_file_info अणु
	__le64 FileSize;		/* offset to end of file */
पूर्ण __attribute__((packed)); /* size info, level 0x104 क्रम set, 0x106 क्रम query */

काष्ठा file_alt_name_info अणु
	__u8   alt_name[1];
पूर्ण __attribute__((packed));      /* level 0x0108 */

काष्ठा file_stream_info अणु
	__le32 number_of_streams;  /* BB check sizes and verअगरy location */
	/* followed by info on streams themselves
		u64 size;
		u64 allocation_size
		stream info */
पूर्ण;      /* level 0x109 */

काष्ठा file_compression_info अणु
	__le64 compressed_size;
	__le16 क्रमmat;
	__u8   unit_shअगरt;
	__u8   ch_shअगरt;
	__u8   cl_shअगरt;
	__u8   pad[3];
पूर्ण __attribute__((packed));      /* level 0x10b */

/* POSIX ACL set/query path info काष्ठाures */
#घोषणा CIFS_ACL_VERSION 1
काष्ठा cअगरs_posix_ace अणु /* access control entry (ACE) */
	__u8  cअगरs_e_tag;
	__u8  cअगरs_e_perm;
	__le64 cअगरs_uid; /* or gid */
पूर्ण __attribute__((packed));

काष्ठा cअगरs_posix_acl अणु /* access conrol list  (ACL) */
	__le16	version;
	__le16	access_entry_count;  /* access ACL - count of entries */
	__le16	शेष_entry_count; /* शेष ACL - count of entries */
	काष्ठा cअगरs_posix_ace ace_array[];
	/* followed by
	काष्ठा cअगरs_posix_ace शेष_ace_arraay[] */
पूर्ण __attribute__((packed));  /* level 0x204 */

/* types of access control entries alपढ़ोy defined in posix_acl.h */
/* #घोषणा CIFS_POSIX_ACL_USER_OBJ	 0x01
#घोषणा CIFS_POSIX_ACL_USER      0x02
#घोषणा CIFS_POSIX_ACL_GROUP_OBJ 0x04
#घोषणा CIFS_POSIX_ACL_GROUP     0x08
#घोषणा CIFS_POSIX_ACL_MASK      0x10
#घोषणा CIFS_POSIX_ACL_OTHER     0x20 */

/* types of perms */
/* #घोषणा CIFS_POSIX_ACL_EXECUTE   0x01
#घोषणा CIFS_POSIX_ACL_WRITE     0x02
#घोषणा CIFS_POSIX_ACL_READ	     0x04 */

/* end of POSIX ACL definitions */

/* POSIX Open Flags */
#घोषणा SMB_O_RDONLY 	 0x1
#घोषणा SMB_O_WRONLY 	0x2
#घोषणा SMB_O_RDWR 	0x4
#घोषणा SMB_O_CREAT 	0x10
#घोषणा SMB_O_EXCL 	0x20
#घोषणा SMB_O_TRUNC 	0x40
#घोषणा SMB_O_APPEND 	0x80
#घोषणा SMB_O_SYNC 	0x100
#घोषणा SMB_O_सूचीECTORY 0x200
#घोषणा SMB_O_NOFOLLOW 	0x400
#घोषणा SMB_O_सूचीECT 	0x800

प्रकार काष्ठा अणु
	__le32 OpenFlags; /* same as NT CreateX */
	__le32 PosixOpenFlags;
	__le64 Permissions;
	__le16 Level; /* reply level requested (see QPathInfo levels) */
पूर्ण __attribute__((packed)) OPEN_PSX_REQ; /* level 0x209 SetPathInfo data */

प्रकार काष्ठा अणु
	__le16 OplockFlags;
	__u16 Fid;
	__le32 CreateAction;
	__le16 ReturnedLevel;
	__le16 Pad;
	/* काष्ठा following varies based on requested level */
पूर्ण __attribute__((packed)) OPEN_PSX_RSP; /* level 0x209 SetPathInfo data */

#घोषणा SMB_POSIX_UNLINK_खाता_TARGET		0
#घोषणा SMB_POSIX_UNLINK_सूचीECTORY_TARGET	1

काष्ठा unlink_psx_rq अणु /* level 0x20a SetPathInfo */
	__le16 type;
पूर्ण __attribute__((packed));

काष्ठा file_पूर्णांकernal_info अणु
	__le64  UniqueId; /* inode number */
पूर्ण __attribute__((packed));      /* level 0x3ee */

काष्ठा file_mode_info अणु
	__le32	Mode;
पूर्ण __attribute__((packed));      /* level 0x3f8 */

काष्ठा file_attrib_tag अणु
	__le32 Attribute;
	__le32 ReparseTag;
पूर्ण __attribute__((packed));      /* level 0x40b */


/********************************************************/
/*  FindFirst/FindNext transact2 data buffer क्रमmats    */
/********************************************************/

प्रकार काष्ठा अणु
	__le32 NextEntryOffset;
	__u32 ResumeKey; /* as with FileIndex - no need to convert */
	खाता_UNIX_BASIC_INFO basic;
	अक्षर FileName[1];
पूर्ण __attribute__((packed)) खाता_UNIX_INFO; /* level 0x202 */

प्रकार काष्ठा अणु
	__le32 NextEntryOffset;
	__u32 FileIndex;
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le64 EndOfFile;
	__le64 AllocationSize;
	__le32 ExtFileAttributes;
	__le32 FileNameLength;
	अक्षर FileName[1];
पूर्ण __attribute__((packed)) खाता_सूचीECTORY_INFO;   /* level 0x101 FF resp data */

प्रकार काष्ठा अणु
	__le32 NextEntryOffset;
	__u32 FileIndex;
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le64 EndOfFile;
	__le64 AllocationSize;
	__le32 ExtFileAttributes;
	__le32 FileNameLength;
	__le32 EaSize; /* length of the xattrs */
	अक्षर FileName[1];
पूर्ण __attribute__((packed)) खाता_FULL_सूचीECTORY_INFO; /* level 0x102 rsp data */

प्रकार काष्ठा अणु
	__le32 NextEntryOffset;
	__u32 FileIndex;
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le64 EndOfFile;
	__le64 AllocationSize;
	__le32 ExtFileAttributes;
	__le32 FileNameLength;
	__le32 EaSize; /* EA size */
	__le32 Reserved;
	__le64 UniqueId; /* inode num - le since Samba माला_दो ino in low 32 bit*/
	अक्षर FileName[1];
पूर्ण __attribute__((packed)) SEARCH_ID_FULL_सूची_INFO; /* level 0x105 FF rsp data */

प्रकार काष्ठा अणु
	__le32 NextEntryOffset;
	__u32 FileIndex;
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le64 EndOfFile;
	__le64 AllocationSize;
	__le32 ExtFileAttributes;
	__le32 FileNameLength;
	__le32 EaSize; /* length of the xattrs */
	__u8   ShortNameLength;
	__u8   Reserved;
	__u8   ShortName[12];
	अक्षर FileName[1];
पूर्ण __attribute__((packed)) खाता_BOTH_सूचीECTORY_INFO; /* level 0x104 FFrsp data */

प्रकार काष्ठा अणु
	__u32  ResumeKey;
	__le16 CreationDate; /* SMB Date */
	__le16 CreationTime; /* SMB Time */
	__le16 LastAccessDate;
	__le16 LastAccessTime;
	__le16 LastWriteDate;
	__le16 LastWriteTime;
	__le32 DataSize; /* File Size (खातापूर्ण) */
	__le32 AllocationSize;
	__le16 Attributes; /* verअगरy not u32 */
	__u8   FileNameLength;
	अक्षर FileName[1];
पूर्ण __attribute__((packed)) FIND_खाता_STANDARD_INFO; /* level 0x1 FF resp data */


काष्ठा win_dev अणु
	अचिन्हित अक्षर type[8]; /* IntxCHR or IntxBLK */
	__le64 major;
	__le64 minor;
पूर्ण __attribute__((packed));

काष्ठा gea अणु
	अचिन्हित अक्षर name_len;
	अक्षर name[1];
पूर्ण __attribute__((packed));

काष्ठा gealist अणु
	अचिन्हित दीर्घ list_len;
	काष्ठा gea list[1];
पूर्ण __attribute__((packed));

काष्ठा fea अणु
	अचिन्हित अक्षर EA_flags;
	__u8 name_len;
	__le16 value_len;
	अक्षर name[1];
	/* optionally followed by value */
पूर्ण __attribute__((packed));
/* flags क्रम _FEA.fEA */
#घोषणा FEA_NEEDEA         0x80	/* need EA bit */

काष्ठा fealist अणु
	__le32 list_len;
	काष्ठा fea list[1];
पूर्ण __attribute__((packed));

/* used to hold an arbitrary blob of data */
काष्ठा data_blob अणु
	__u8 *data;
	माप_प्रकार length;
	व्योम (*मुक्त) (काष्ठा data_blob *data_blob);
पूर्ण __attribute__((packed));


#अगर_घोषित CONFIG_CIFS_POSIX
/*
	For better POSIX semantics from Linux client, (even better
	than the existing CIFS Unix Extensions) we need updated PDUs क्रम:

	1) PosixCreateX - to set and वापस the mode, inode#, device info and
	perhaps add a CreateDevice - to create Pipes and other special .inodes
	Also note POSIX खोलो flags
	2) Close - to वापस the last ग_लिखो समय to करो cache across बंद
		more safely
	3) FindFirst वापस unique inode number - what about resume key, two
	क्रमms लघु (matches सूची_पढ़ो) and full (enough info to cache inodes)
	4) Mkdir - set mode

	And under consideration:
	5) FindClose2 (वापस nanosecond बारtamp ??)
	6) Use nanosecond बारtamps throughout all समय fields अगर
	   corresponding attribute flag is set
	7) sendfile - handle based copy

	what about fixing 64 bit alignment

	There are also various legacy SMB/CIFS requests used as is

	From existing Lanman and NTLM dialects:
	--------------------------------------
	NEGOTIATE
	SESSION_SETUP_ANDX (BB which?)
	TREE_CONNECT_ANDX (BB which wct?)
	TREE_DISCONNECT (BB add volume बारtamp on response)
	LOGOFF_ANDX
	DELETE (note delete खोलो file behavior)
	DELETE_सूचीECTORY
	READ_AND_X
	WRITE_AND_X
	LOCKING_AND_X (note posix lock semantics)
	RENAME (note नाम across dirs and खोलो file नाम posix behaviors)
	NT_RENAME (क्रम hardlinks) Is this good enough क्रम all features?
	FIND_CLOSE2
	TRANSACTION2 (18 हालs)
		SMB_SET_खाता_END_OF_खाता_INFO2 SMB_SET_PATH_END_OF_खाता_INFO2
		(BB verअगरy that never need to set allocation size)
		SMB_SET_खाता_BASIC_INFO2 (setting बार - BB can it be करोne via
			 Unix ext?)

	COPY (note support क्रम copy across directories) - FUTURE, OPTIONAL
	setting/getting OS/2 EAs - FUTURE (BB can this handle
	setting Linux xattrs perfectly)         - OPTIONAL
	dnotअगरy                                 - FUTURE, OPTIONAL
	quota                                   - FUTURE, OPTIONAL

	Note that various requests implemented क्रम NT पूर्णांकerop such as
		NT_TRANSACT (IOCTL) QueryReparseInfo
	are unneeded to servers compliant with the CIFS POSIX extensions

	From CIFS Unix Extensions:
	-------------------------
	T2 SET_PATH_INFO (SMB_SET_खाता_UNIX_LINK) क्रम symlinks
	T2 SET_PATH_INFO (SMB_SET_खाता_BASIC_INFO2)
	T2 QUERY_PATH_INFO (SMB_QUERY_खाता_UNIX_LINK)
	T2 QUERY_PATH_INFO (SMB_QUERY_खाता_UNIX_BASIC)	BB check क्रम missing
							inode fields
				Actually a need QUERY_खाता_UNIX_INFO
				since has inode num
				BB what about a) blksize/blkbits/blocks
							  b) i_version
							  c) i_rdev
							  d) notअगरy mask?
							  e) generation
							  f) size_seqcount
	T2 FIND_FIRST/FIND_NEXT FIND_खाता_UNIX
	TRANS2_GET_DFS_REFERRAL		      - OPTIONAL but recommended
	T2_QFS_INFO QueryDevice/AttributeInfo - OPTIONAL
 */

/* xsymlink is a symlink क्रमmat (used by MacOS) that can be used
   to save symlink info in a regular file when
   mounted to operating प्रणालीs that करो not
   support the cअगरs Unix extensions or EAs (क्रम xattr
   based symlinks).  For such a file to be recognized
   as containing symlink data:

   1) file size must be 1067,
   2) signature must begin file data,
   3) length field must be set to ASCII representation
	of a number which is less than or equal to 1024,
   4) md5 must match that of the path data */

काष्ठा xsymlink अणु
	/* 1067 bytes */
	अक्षर signature[4]; /* XSym */ /* not null terminated */
	अक्षर cr0;         /* \न */
/* ASCII representation of length (4 bytes decimal) terminated by \न not null */
	अक्षर length[4];
	अक्षर cr1;         /* \न */
/* md5 of valid subset of path ie path[0] through path[length-1] */
	__u8 md5[32];
	अक्षर cr2;        /* \न */
/* अगर room left, then end with \न then 0x20s by convention but not required */
	अक्षर path[1024];
पूर्ण __attribute__((packed));

प्रकार काष्ठा file_xattr_info अणु
	/* BB करो we need another field क्रम flags? BB */
	__u32 xattr_name_len;
	__u32 xattr_value_len;
	अक्षर  xattr_name[];
	/* followed by xattr_value[xattr_value_len], no pad */
पूर्ण __attribute__((packed)) खाता_XATTR_INFO; /* extended attribute info
					      level 0x205 */

/* flags क्रम lsattr and chflags commands हटाओd arein uapi/linux/fs.h */

प्रकार काष्ठा file_chattr_info अणु
	__le64	mask; /* list of all possible attribute bits */
	__le64	mode; /* list of actual attribute bits on this inode */
पूर्ण __attribute__((packed)) खाता_CHATTR_INFO;  /* ext attributes
						(chattr, chflags) level 0x206 */
#पूर्ण_अगर 				/* POSIX */
#पूर्ण_अगर				/* _CIFSPDU_H */
