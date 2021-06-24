<शैली गुरु>
/*
 *   fs/cअगरs/smb2pdu.h
 *
 *   Copyright (c) International Business Machines  Corp., 2009, 2013
 *                 Etersoft, 2012
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *              Pavel Shilovsky (pshilovsky@samba.org) 2012
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

#अगर_अघोषित _SMB2PDU_H
#घोषणा _SMB2PDU_H

#समावेश <net/sock.h>
#समावेश <cअगरsacl.h>

/*
 * Note that, due to trying to use names similar to the protocol specअगरications,
 * there are many mixed हाल field names in the काष्ठाures below.  Although
 * this करोes not match typical Linux kernel style, it is necessary to be
 * able to match against the protocol specfication.
 *
 * SMB2 commands
 * Some commands have minimal (wct=0,bcc=0), or unपूर्णांकeresting, responses
 * (ie no useful data other than the SMB error code itself) and are marked such.
 * Knowing this helps aव्योम response buffer allocations and copy in some हालs.
 */

/* List of commands in host endian */
#घोषणा SMB2_NEGOTIATE_HE	0x0000
#घोषणा SMB2_SESSION_SETUP_HE	0x0001
#घोषणा SMB2_LOGOFF_HE		0x0002 /* trivial request/resp */
#घोषणा SMB2_TREE_CONNECT_HE	0x0003
#घोषणा SMB2_TREE_DISCONNECT_HE	0x0004 /* trivial req/resp */
#घोषणा SMB2_CREATE_HE		0x0005
#घोषणा SMB2_CLOSE_HE		0x0006
#घोषणा SMB2_FLUSH_HE		0x0007 /* trivial resp */
#घोषणा SMB2_READ_HE		0x0008
#घोषणा SMB2_WRITE_HE		0x0009
#घोषणा SMB2_LOCK_HE		0x000A
#घोषणा SMB2_IOCTL_HE		0x000B
#घोषणा SMB2_CANCEL_HE		0x000C
#घोषणा SMB2_ECHO_HE		0x000D
#घोषणा SMB2_QUERY_सूचीECTORY_HE	0x000E
#घोषणा SMB2_CHANGE_NOTIFY_HE	0x000F
#घोषणा SMB2_QUERY_INFO_HE	0x0010
#घोषणा SMB2_SET_INFO_HE	0x0011
#घोषणा SMB2_OPLOCK_BREAK_HE	0x0012

/* The same list in little endian */
#घोषणा SMB2_NEGOTIATE		cpu_to_le16(SMB2_NEGOTIATE_HE)
#घोषणा SMB2_SESSION_SETUP	cpu_to_le16(SMB2_SESSION_SETUP_HE)
#घोषणा SMB2_LOGOFF		cpu_to_le16(SMB2_LOGOFF_HE)
#घोषणा SMB2_TREE_CONNECT	cpu_to_le16(SMB2_TREE_CONNECT_HE)
#घोषणा SMB2_TREE_DISCONNECT	cpu_to_le16(SMB2_TREE_DISCONNECT_HE)
#घोषणा SMB2_CREATE		cpu_to_le16(SMB2_CREATE_HE)
#घोषणा SMB2_CLOSE		cpu_to_le16(SMB2_CLOSE_HE)
#घोषणा SMB2_FLUSH		cpu_to_le16(SMB2_FLUSH_HE)
#घोषणा SMB2_READ		cpu_to_le16(SMB2_READ_HE)
#घोषणा SMB2_WRITE		cpu_to_le16(SMB2_WRITE_HE)
#घोषणा SMB2_LOCK		cpu_to_le16(SMB2_LOCK_HE)
#घोषणा SMB2_IOCTL		cpu_to_le16(SMB2_IOCTL_HE)
#घोषणा SMB2_CANCEL		cpu_to_le16(SMB2_CANCEL_HE)
#घोषणा SMB2_ECHO		cpu_to_le16(SMB2_ECHO_HE)
#घोषणा SMB2_QUERY_सूचीECTORY	cpu_to_le16(SMB2_QUERY_सूचीECTORY_HE)
#घोषणा SMB2_CHANGE_NOTIFY	cpu_to_le16(SMB2_CHANGE_NOTIFY_HE)
#घोषणा SMB2_QUERY_INFO		cpu_to_le16(SMB2_QUERY_INFO_HE)
#घोषणा SMB2_SET_INFO		cpu_to_le16(SMB2_SET_INFO_HE)
#घोषणा SMB2_OPLOCK_BREAK	cpu_to_le16(SMB2_OPLOCK_BREAK_HE)

#घोषणा SMB2_INTERNAL_CMD	cpu_to_le16(0xFFFF)

#घोषणा NUMBER_OF_SMB2_COMMANDS	0x0013

/* 52 transक्रमm hdr + 64 hdr + 88 create rsp */
#घोषणा SMB2_TRANSFORM_HEADER_SIZE 52
#घोषणा MAX_SMB2_HDR_SIZE 204

#घोषणा SMB2_PROTO_NUMBER cpu_to_le32(0x424d53fe)
#घोषणा SMB2_TRANSFORM_PROTO_NUM cpu_to_le32(0x424d53fd)
#घोषणा SMB2_COMPRESSION_TRANSFORM_ID cpu_to_le32(0x424d53fc)

/*
 * SMB2 Header Definition
 *
 * "MBZ" :  Must be Zero
 * "BB"  :  BugBug, Something to check/review/analyze later
 * "PDU" :  "Protocol Data Unit" (ie a network "frame")
 *
 */

#घोषणा SMB2_HEADER_STRUCTURE_SIZE cpu_to_le16(64)

काष्ठा smb2_sync_hdr अणु
	__le32 ProtocolId;	/* 0xFE 'S' 'M' 'B' */
	__le16 StructureSize;	/* 64 */
	__le16 CreditCharge;	/* MBZ */
	__le32 Status;		/* Error from server */
	__le16 Command;
	__le16 CreditRequest;  /* CreditResponse */
	__le32 Flags;
	__le32 NextCommand;
	__le64 MessageId;
	__le32 ProcessId;
	__u32  TreeId;		/* opaque - so करो not make little endian */
	__u64  SessionId;	/* opaque - so करो not make little endian */
	__u8   Signature[16];
पूर्ण __packed;

/* The total header size क्रम SMB2 पढ़ो and ग_लिखो */
#घोषणा SMB2_READWRITE_PDU_HEADER_SIZE (48 + माप(काष्ठा smb2_sync_hdr))

काष्ठा smb2_sync_pdu अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize2; /* size of wct area (varies, request specअगरic) */
पूर्ण __packed;

#घोषणा SMB3_AES_CCM_NONCE 11
#घोषणा SMB3_AES_GCM_NONCE 12

/* Transक्रमm flags (क्रम 3.0 dialect this flag indicates CCM */
#घोषणा TRANSFORM_FLAG_ENCRYPTED	0x0001
काष्ठा smb2_transक्रमm_hdr अणु
	__le32 ProtocolId;	/* 0xFD 'S' 'M' 'B' */
	__u8   Signature[16];
	__u8   Nonce[16];
	__le32 OriginalMessageSize;
	__u16  Reserved1;
	__le16 Flags; /* EncryptionAlgorithm क्रम 3.0, enc enabled क्रम 3.1.1 */
	__u64  SessionId;
पूर्ण __packed;

/* See MS-SMB2 2.2.42 */
काष्ठा smb2_compression_transक्रमm_hdr_unchained अणु
	__le32 ProtocolId;	/* 0xFC 'S' 'M' 'B' */
	__le32 OriginalCompressedSegmentSize;
	__le16 CompressionAlgorithm;
	__le16 Flags;
	__le16 Length; /* अगर chained it is length, अन्यथा offset */
पूर्ण __packed;

/* See MS-SMB2 2.2.42.1 */
#घोषणा SMB2_COMPRESSION_FLAG_NONE	0x0000
#घोषणा SMB2_COMPRESSION_FLAG_CHAINED	0x0001

काष्ठा compression_payload_header अणु
	__le16	CompressionAlgorithm;
	__le16	Flags;
	__le32	Length; /* length of compressed playload including field below अगर present */
	/* __le32 OriginalPayloadSize; */ /* optional, present when LZNT1, LZ77, LZ77+Huffman */
पूर्ण __packed;

/* See MS-SMB2 2.2.42.2 */
काष्ठा smb2_compression_transक्रमm_hdr_chained अणु
	__le32 ProtocolId;	/* 0xFC 'S' 'M' 'B' */
	__le32 OriginalCompressedSegmentSize;
	/* काष्ठा compression_payload_header[] */
पूर्ण __packed;

/* See MS-SMB2 2.2.42.2.2 */
काष्ठा compression_pattern_payload_v1 अणु
	__le16	Pattern;
	__le16	Reserved1;
	__le16	Reserved2;
	__le32	Repetitions;
पूर्ण __packed;

/* See MS-SMB2 2.2.43 */
काष्ठा smb2_rdma_transक्रमm अणु
	__le16 RdmaDescriptorOffset;
	__le16 RdmaDescriptorLength;
	__le32 Channel; /* क्रम values see channel description in smb2 पढ़ो above */
	__le16 Transक्रमmCount;
	__le16 Reserved1;
	__le32 Reserved2;
पूर्ण __packed;

/* Transक्रमmType */
#घोषणा SMB2_RDMA_TRANSFORM_TYPE_ENCRYPTION	0x0001
#घोषणा SMB2_RDMA_TRANSFORM_TYPE_SIGNING	0x0002

काष्ठा smb2_rdma_crypto_transक्रमm अणु
	__le16	Transक्रमmType;
	__le16	SignatureLength;
	__le16	NonceLength;
	__u16	Reserved;
	__u8	Signature[]; /* variable length */
	/* u8 Nonce[] */
	/* followed by padding */
पूर्ण __packed;

/*
 *	SMB2 flag definitions
 */
#घोषणा SMB2_FLAGS_SERVER_TO_REसूची	cpu_to_le32(0x00000001)
#घोषणा SMB2_FLAGS_ASYNC_COMMAND	cpu_to_le32(0x00000002)
#घोषणा SMB2_FLAGS_RELATED_OPERATIONS	cpu_to_le32(0x00000004)
#घोषणा SMB2_FLAGS_SIGNED		cpu_to_le32(0x00000008)
#घोषणा SMB2_FLAGS_PRIORITY_MASK	cpu_to_le32(0x00000070) /* SMB3.1.1 */
#घोषणा SMB2_FLAGS_DFS_OPERATIONS	cpu_to_le32(0x10000000)
#घोषणा SMB2_FLAGS_REPLAY_OPERATION	cpu_to_le32(0x20000000) /* SMB3 & up */

/*
 *	Definitions क्रम SMB2 Protocol Data Units (network frames)
 *
 *  See MS-SMB2.PDF specअगरication क्रम protocol details.
 *  The Naming convention is the lower हाल version of the SMB2
 *  command code name क्रम the काष्ठा. Note that काष्ठाures must be packed.
 *
 */

#घोषणा COMPOUND_FID 0xFFFFFFFFFFFFFFFFULL

#घोषणा SMB2_ERROR_STRUCTURE_SIZE2 cpu_to_le16(9)

काष्ठा smb2_err_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;
	__le16 Reserved; /* MBZ */
	__le32 ByteCount;  /* even अगर zero, at least one byte follows */
	__u8   ErrorData[1];  /* variable length */
पूर्ण __packed;

#घोषणा SYMLINK_ERROR_TAG 0x4c4d5953

काष्ठा smb2_symlink_err_rsp अणु
	__le32 SymLinkLength;
	__le32 SymLinkErrorTag;
	__le32 ReparseTag;
	__le16 ReparseDataLength;
	__le16 UnparsedPathLength;
	__le16 SubstituteNameOffset;
	__le16 SubstituteNameLength;
	__le16 Prपूर्णांकNameOffset;
	__le16 Prपूर्णांकNameLength;
	__le32 Flags;
	__u8  PathBuffer[];
पूर्ण __packed;

/* SMB 3.1.1 and later dialects. See MS-SMB2 section 2.2.2.1 */
काष्ठा smb2_error_context_rsp अणु
	__le32 ErrorDataLength;
	__le32 ErrorId;
	__u8  ErrorContextData; /* ErrorDataLength दीर्घ array */
पूर्ण __packed;

/* ErrorId values */
#घोषणा SMB2_ERROR_ID_DEFAULT		0x00000000
#घोषणा SMB2_ERROR_ID_SHARE_REसूचीECT	cpu_to_le32(0x72645253)	/* "rdRS" */

/* Defines क्रम Type field below (see MS-SMB2 2.2.2.2.2.1) */
#घोषणा MOVE_DST_IPADDR_V4	cpu_to_le32(0x00000001)
#घोषणा MOVE_DST_IPADDR_V6	cpu_to_le32(0x00000002)

काष्ठा move_dst_ipaddr अणु
	__le32 Type;
	__u32  Reserved;
	__u8   address[16]; /* IPv4 followed by 12 bytes rsvd or IPv6 address */
पूर्ण __packed;

काष्ठा share_redirect_error_context_rsp अणु
	__le32 StructureSize;
	__le32 NotअगरicationType;
	__le32 ResourceNameOffset;
	__le32 ResourceNameLength;
	__le16 Flags;
	__le16 TargetType;
	__le32 IPAddrCount;
	काष्ठा move_dst_ipaddr IpAddrMoveList[];
	/* __u8 ResourceName[] */ /* Name of share as counted Unicode string */
पूर्ण __packed;

#घोषणा SMB2_CLIENT_GUID_SIZE 16

काष्ठा smb2_negotiate_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 36 */
	__le16 DialectCount;
	__le16 SecurityMode;
	__le16 Reserved;	/* MBZ */
	__le32 Capabilities;
	__u8   ClientGUID[SMB2_CLIENT_GUID_SIZE];
	/* In SMB3.02 and earlier next three were MBZ le64 ClientStartTime */
	__le32 NegotiateContextOffset; /* SMB3.1.1 only. MBZ earlier */
	__le16 NegotiateContextCount;  /* SMB3.1.1 only. MBZ earlier */
	__le16 Reserved2;
	__le16 Dialects[4]; /* BB expand this अगर स्वतःnegotiate > 4 dialects */
पूर्ण __packed;

/* Dialects */
#घोषणा SMB10_PROT_ID 0x0000 /* local only, not sent on wire w/CIFS negprot */
#घोषणा SMB20_PROT_ID 0x0202
#घोषणा SMB21_PROT_ID 0x0210
#घोषणा SMB30_PROT_ID 0x0300
#घोषणा SMB302_PROT_ID 0x0302
#घोषणा SMB311_PROT_ID 0x0311
#घोषणा BAD_PROT_ID   0xFFFF

/* SecurityMode flags */
#घोषणा	SMB2_NEGOTIATE_SIGNING_ENABLED	0x0001
#घोषणा SMB2_NEGOTIATE_SIGNING_REQUIRED	0x0002
#घोषणा SMB2_SEC_MODE_FLAGS_ALL		0x0003

/* Capabilities flags */
#घोषणा SMB2_GLOBAL_CAP_DFS		0x00000001
#घोषणा SMB2_GLOBAL_CAP_LEASING		0x00000002 /* Resp only New to SMB2.1 */
#घोषणा SMB2_GLOBAL_CAP_LARGE_MTU	0X00000004 /* Resp only New to SMB2.1 */
#घोषणा SMB2_GLOBAL_CAP_MULTI_CHANNEL	0x00000008 /* New to SMB3 */
#घोषणा SMB2_GLOBAL_CAP_PERSISTENT_HANDLES 0x00000010 /* New to SMB3 */
#घोषणा SMB2_GLOBAL_CAP_सूचीECTORY_LEASING  0x00000020 /* New to SMB3 */
#घोषणा SMB2_GLOBAL_CAP_ENCRYPTION	0x00000040 /* New to SMB3 */
/* Internal types */
#घोषणा SMB2_NT_FIND			0x00100000
#घोषणा SMB2_LARGE_खाताS		0x00200000


/* Negotiate Contexts - ContextTypes. See MS-SMB2 section 2.2.3.1 क्रम details */
#घोषणा SMB2_PREAUTH_INTEGRITY_CAPABILITIES	cpu_to_le16(1)
#घोषणा SMB2_ENCRYPTION_CAPABILITIES		cpu_to_le16(2)
#घोषणा SMB2_COMPRESSION_CAPABILITIES		cpu_to_le16(3)
#घोषणा SMB2_NETNAME_NEGOTIATE_CONTEXT_ID	cpu_to_le16(5)
#घोषणा SMB2_TRANSPORT_CAPABILITIES		cpu_to_le16(6)
#घोषणा SMB2_RDMA_TRANSFORM_CAPABILITIES	cpu_to_le16(7)
#घोषणा SMB2_SIGNING_CAPABILITIES		cpu_to_le16(8)
#घोषणा SMB2_POSIX_EXTENSIONS_AVAILABLE		cpu_to_le16(0x100)

काष्ठा smb2_neg_context अणु
	__le16	ContextType;
	__le16	DataLength;
	__le32	Reserved;
	/* Followed by array of data */
पूर्ण __packed;

#घोषणा SMB311_LINUX_CLIENT_SALT_SIZE			32
/* Hash Algorithm Types */
#घोषणा SMB2_PREAUTH_INTEGRITY_SHA512	cpu_to_le16(0x0001)
#घोषणा SMB2_PREAUTH_HASH_SIZE 64

/*
 * SaltLength that the server send can be zero, so the only three required
 * fields (all __le16) end up six bytes total, so the minimum context data len
 * in the response is six bytes which accounts क्रम
 *
 *      HashAlgorithmCount, SaltLength, and 1 HashAlgorithm.
 */
#घोषणा MIN_PREAUTH_CTXT_DATA_LEN 6

काष्ठा smb2_preauth_neg_context अणु
	__le16	ContextType; /* 1 */
	__le16	DataLength;
	__le32	Reserved;
	__le16	HashAlgorithmCount; /* 1 */
	__le16	SaltLength;
	__le16	HashAlgorithms; /* HashAlgorithms[0] since only one defined */
	__u8	Salt[SMB311_LINUX_CLIENT_SALT_SIZE];
पूर्ण __packed;

/* Encryption Algorithms Ciphers */
#घोषणा SMB2_ENCRYPTION_AES128_CCM	cpu_to_le16(0x0001)
#घोषणा SMB2_ENCRYPTION_AES128_GCM	cpu_to_le16(0x0002)
/* we currently करो not request AES256_CCM since presumably GCM faster */
#घोषणा SMB2_ENCRYPTION_AES256_CCM      cpu_to_le16(0x0003)
#घोषणा SMB2_ENCRYPTION_AES256_GCM      cpu_to_le16(0x0004)

/* Min encrypt context data is one cipher so 2 bytes + 2 byte count field */
#घोषणा MIN_ENCRYPT_CTXT_DATA_LEN	4
काष्ठा smb2_encryption_neg_context अणु
	__le16	ContextType; /* 2 */
	__le16	DataLength;
	__le32	Reserved;
	/* CipherCount usally 2, but can be 3 when AES256-GCM enabled */
	__le16	CipherCount; /* AES128-GCM and AES128-CCM by शेष */
	__le16	Ciphers[3];
पूर्ण __packed;

/* See MS-SMB2 2.2.3.1.3 */
#घोषणा SMB3_COMPRESS_NONE	cpu_to_le16(0x0000)
#घोषणा SMB3_COMPRESS_LZNT1	cpu_to_le16(0x0001)
#घोषणा SMB3_COMPRESS_LZ77	cpu_to_le16(0x0002)
#घोषणा SMB3_COMPRESS_LZ77_HUFF	cpu_to_le16(0x0003)
/* Pattern scanning algorithm See MS-SMB2 3.1.4.4.1 */
#घोषणा SMB3_COMPRESS_PATTERN	cpu_to_le16(0x0004) /* Pattern_V1 */

/* Compression Flags */
#घोषणा SMB2_COMPRESSION_CAPABILITIES_FLAG_NONE		cpu_to_le32(0x00000000)
#घोषणा SMB2_COMPRESSION_CAPABILITIES_FLAG_CHAINED	cpu_to_le32(0x00000001)

काष्ठा smb2_compression_capabilities_context अणु
	__le16	ContextType; /* 3 */
	__le16  DataLength;
	__u32	Reserved;
	__le16	CompressionAlgorithmCount;
	__u16	Padding;
	__u32	Flags;
	__le16	CompressionAlgorithms[3];
पूर्ण __packed;

/*
 * For smb2_netname_negotiate_context_id See MS-SMB2 2.2.3.1.4.
 * Its काष्ठा simply contains NetName, an array of Unicode अक्षरacters
 */
काष्ठा smb2_netname_neg_context अणु
	__le16	ContextType; /* 5 */
	__le16	DataLength;
	__le32	Reserved;
	__le16	NetName[]; /* hostname of target converted to UCS-2 */
पूर्ण __packed;

/*
 * For smb2_transport_capabilities context see MS-SMB2 2.2.3.1.5
 * and 2.2.4.1.5
 */

/* Flags */
#घोषणा SMB2_ACCEPT_TRANSFORM_LEVEL_SECURITY	0x00000001

काष्ठा smb2_transport_capabilities_context अणु
	__le16	ContextType; /* 6 */
	__le16  DataLength;
	__u32	Reserved;
	__le32	Flags;
पूर्ण __packed;

/*
 * For rdma transक्रमm capabilities context see MS-SMB2 2.2.3.1.6
 * and 2.2.4.1.6
 */

/* RDMA Transक्रमm IDs */
#घोषणा SMB2_RDMA_TRANSFORM_NONE	0x0000
#घोषणा SMB2_RDMA_TRANSFORM_ENCRYPTION	0x0001
#घोषणा SMB2_RDMA_TRANSFORM_SIGNING	0x0002

काष्ठा smb2_rdma_transक्रमm_capabilities_context अणु
	__le16	ContextType; /* 7 */
	__le16  DataLength;
	__u32	Reserved;
	__le16	Transक्रमmCount;
	__u16	Reserved1;
	__u32	Reserved2;
	__le16	RDMATransक्रमmIds[];
पूर्ण __packed;

/*
 * For signing capabilities context see MS-SMB2 2.2.3.1.7
 * and 2.2.4.1.7
 */

/* Signing algorithms */
#घोषणा SIGNING_ALG_HMAC_SHA256	0
#घोषणा SIGNING_ALG_AES_CMAC	1
#घोषणा SIGNING_ALG_AES_GMAC	2

काष्ठा smb2_signing_capabilities अणु
	__le16	ContextType; /* 8 */
	__le16	DataLength;
	__u32	Reserved;
	__le16	SigningAlgorithmCount;
	__le16	SigningAlgorithms[];
पूर्ण __packed;

#घोषणा POSIX_CTXT_DATA_LEN	16
काष्ठा smb2_posix_neg_context अणु
	__le16	ContextType; /* 0x100 */
	__le16	DataLength;
	__le32	Reserved;
	__u8	Name[16]; /* POSIX ctxt GUID 93AD25509CB411E7B42383DE968BCD7C */
पूर्ण __packed;

काष्ठा smb2_negotiate_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 65 */
	__le16 SecurityMode;
	__le16 DialectRevision;
	__le16 NegotiateContextCount;	/* Prior to SMB3.1.1 was Reserved & MBZ */
	__u8   ServerGUID[16];
	__le32 Capabilities;
	__le32 MaxTransactSize;
	__le32 MaxReadSize;
	__le32 MaxWriteSize;
	__le64 SystemTime;	/* MBZ */
	__le64 ServerStartTime;
	__le16 SecurityBufferOffset;
	__le16 SecurityBufferLength;
	__le32 NegotiateContextOffset;	/* Pre:SMB3.1.1 was reserved/ignored */
	__u8   Buffer[1];	/* variable length GSS security buffer */
पूर्ण __packed;

/* Flags */
#घोषणा SMB2_SESSION_REQ_FLAG_BINDING		0x01
#घोषणा SMB2_SESSION_REQ_FLAG_ENCRYPT_DATA	0x04

काष्ठा smb2_sess_setup_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 25 */
	__u8   Flags;
	__u8   SecurityMode;
	__le32 Capabilities;
	__le32 Channel;
	__le16 SecurityBufferOffset;
	__le16 SecurityBufferLength;
	__u64 PreviousSessionId;
	__u8   Buffer[1];	/* variable length GSS security buffer */
पूर्ण __packed;

/* Currently defined SessionFlags */
#घोषणा SMB2_SESSION_FLAG_IS_GUEST	0x0001
#घोषणा SMB2_SESSION_FLAG_IS_शून्य	0x0002
#घोषणा SMB2_SESSION_FLAG_ENCRYPT_DATA	0x0004
काष्ठा smb2_sess_setup_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 9 */
	__le16 SessionFlags;
	__le16 SecurityBufferOffset;
	__le16 SecurityBufferLength;
	__u8   Buffer[1];	/* variable length GSS security buffer */
पूर्ण __packed;

काष्ठा smb2_logoff_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 4 */
	__le16 Reserved;
पूर्ण __packed;

काष्ठा smb2_logoff_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 4 */
	__le16 Reserved;
पूर्ण __packed;

/* Flags/Reserved क्रम SMB3.1.1 */
#घोषणा SMB2_TREE_CONNECT_FLAG_CLUSTER_RECONNECT cpu_to_le16(0x0001)
#घोषणा SMB2_TREE_CONNECT_FLAG_REसूचीECT_TO_OWNER cpu_to_le16(0x0002)
#घोषणा SMB2_TREE_CONNECT_FLAG_EXTENSION_PRESENT cpu_to_le16(0x0004)

काष्ठा smb2_tree_connect_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 9 */
	__le16 Flags; /* Reserved MBZ क्रम dialects prior to SMB3.1.1 */
	__le16 PathOffset;
	__le16 PathLength;
	__u8   Buffer[1];	/* variable length */
पूर्ण __packed;

/* See MS-SMB2 section 2.2.9.2 */
/* Context Types */
#घोषणा SMB2_RESERVED_TREE_CONNECT_CONTEXT_ID 0x0000
#घोषणा SMB2_REMOTED_IDENTITY_TREE_CONNECT_CONTEXT_ID cpu_to_le16(0x0001)

काष्ठा tree_connect_contexts अणु
	__le16 ContextType;
	__le16 DataLength;
	__le32 Reserved;
	__u8   Data[];
पूर्ण __packed;

/* Remoted identity tree connect context काष्ठाures - see MS-SMB2 2.2.9.2.1 */
काष्ठा smb3_blob_data अणु
	__le16 BlobSize;
	__u8   BlobData[];
पूर्ण __packed;

/* Valid values क्रम Attr */
#घोषणा SE_GROUP_MANDATORY		0x00000001
#घोषणा SE_GROUP_ENABLED_BY_DEFAULT	0x00000002
#घोषणा SE_GROUP_ENABLED		0x00000004
#घोषणा SE_GROUP_OWNER			0x00000008
#घोषणा SE_GROUP_USE_FOR_DENY_ONLY	0x00000010
#घोषणा SE_GROUP_INTEGRITY		0x00000020
#घोषणा SE_GROUP_INTEGRITY_ENABLED	0x00000040
#घोषणा SE_GROUP_RESOURCE		0x20000000
#घोषणा SE_GROUP_LOGON_ID		0xC0000000

/* काष्ठा sid_attr_data is SidData array in BlobData क्रमmat then le32 Attr */

काष्ठा sid_array_data अणु
	__le16 SidAttrCount;
	/* SidAttrList - array of sid_attr_data काष्ठाs */
पूर्ण __packed;

काष्ठा luid_attr_data अणु

पूर्ण __packed;

/*
 * काष्ठा privilege_data is the same as BLOB_DATA - see MS-SMB2 2.2.9.2.1.5
 * but with size of LUID_ATTR_DATA काष्ठा and BlobData set to LUID_ATTR DATA
 */

काष्ठा privilege_array_data अणु
	__le16 PrivilegeCount;
	/* array of privilege_data काष्ठाs */
पूर्ण __packed;

काष्ठा remoted_identity_tcon_context अणु
	__le16 TicketType; /* must be 0x0001 */
	__le16 TicketSize; /* total size of this काष्ठा */
	__le16 User; /* offset to SID_ATTR_DATA काष्ठा with user info */
	__le16 UserName; /* offset to null terminated Unicode username string */
	__le16 Doमुख्य; /* offset to null terminated Unicode करोमुख्य name */
	__le16 Groups; /* offset to SID_ARRAY_DATA काष्ठा with group info */
	__le16 RestrictedGroups; /* similar to above */
	__le16 Privileges; /* offset to PRIVILEGE_ARRAY_DATA काष्ठा */
	__le16 PrimaryGroup; /* offset to SID_ARRAY_DATA काष्ठा */
	__le16 Owner; /* offset to BLOB_DATA काष्ठा */
	__le16 DefaultDacl; /* offset to BLOB_DATA काष्ठा */
	__le16 DeviceGroups; /* offset to SID_ARRAY_DATA काष्ठा */
	__le16 UserClaims; /* offset to BLOB_DATA काष्ठा */
	__le16 DeviceClaims; /* offset to BLOB_DATA काष्ठा */
	__u8   TicketInfo[]; /* variable length buf - remoted identity data */
पूर्ण __packed;

काष्ठा smb2_tree_connect_req_extension अणु
	__le32 TreeConnectContextOffset;
	__le16 TreeConnectContextCount;
	__u8  Reserved[10];
	__u8  PathName[]; /* variable sized array */
	/* followed by array of TreeConnectContexts */
पूर्ण __packed;

काष्ठा smb2_tree_connect_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 16 */
	__u8   ShareType;  /* see below */
	__u8   Reserved;
	__le32 ShareFlags; /* see below */
	__le32 Capabilities; /* see below */
	__le32 MaximalAccess;
पूर्ण __packed;

/* Possible ShareType values */
#घोषणा SMB2_SHARE_TYPE_DISK	0x01
#घोषणा SMB2_SHARE_TYPE_PIPE	0x02
#घोषणा	SMB2_SHARE_TYPE_PRINT	0x03

/*
 * Possible ShareFlags - exactly one and only one of the first 4 caching flags
 * must be set (any of the reमुख्यing, SHI1005, flags may be set inभागidually
 * or in combination.
 */
#घोषणा SMB2_SHAREFLAG_MANUAL_CACHING			0x00000000
#घोषणा SMB2_SHAREFLAG_AUTO_CACHING			0x00000010
#घोषणा SMB2_SHAREFLAG_VDO_CACHING			0x00000020
#घोषणा SMB2_SHAREFLAG_NO_CACHING			0x00000030
#घोषणा SHI1005_FLAGS_DFS				0x00000001
#घोषणा SHI1005_FLAGS_DFS_ROOT				0x00000002
#घोषणा SHI1005_FLAGS_RESTRICT_EXCLUSIVE_OPENS		0x00000100
#घोषणा SHI1005_FLAGS_FORCE_SHARED_DELETE		0x00000200
#घोषणा SHI1005_FLAGS_ALLOW_NAMESPACE_CACHING		0x00000400
#घोषणा SHI1005_FLAGS_ACCESS_BASED_सूचीECTORY_ENUM	0x00000800
#घोषणा SHI1005_FLAGS_FORCE_LEVELII_OPLOCK		0x00001000
#घोषणा SHI1005_FLAGS_ENABLE_HASH_V1			0x00002000
#घोषणा SHI1005_FLAGS_ENABLE_HASH_V2			0x00004000
#घोषणा SHI1005_FLAGS_ENCRYPT_DATA			0x00008000
#घोषणा SMB2_SHAREFLAG_IDENTITY_REMOTING		0x00040000 /* 3.1.1 */
#घोषणा SMB2_SHAREFLAG_COMPRESS_DATA			0x00100000 /* 3.1.1 */
#घोषणा SHI1005_FLAGS_ALL				0x0014FF33

/* Possible share capabilities */
#घोषणा SMB2_SHARE_CAP_DFS	cpu_to_le32(0x00000008) /* all dialects */
#घोषणा SMB2_SHARE_CAP_CONTINUOUS_AVAILABILITY cpu_to_le32(0x00000010) /* 3.0 */
#घोषणा SMB2_SHARE_CAP_SCALEOUT	cpu_to_le32(0x00000020) /* 3.0 */
#घोषणा SMB2_SHARE_CAP_CLUSTER	cpu_to_le32(0x00000040) /* 3.0 */
#घोषणा SMB2_SHARE_CAP_ASYMMETRIC cpu_to_le32(0x00000080) /* 3.02 */
#घोषणा SMB2_SHARE_CAP_REसूचीECT_TO_OWNER cpu_to_le32(0x00000100) /* 3.1.1 */

काष्ठा smb2_tree_disconnect_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 4 */
	__le16 Reserved;
पूर्ण __packed;

काष्ठा smb2_tree_disconnect_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 4 */
	__le16 Reserved;
पूर्ण __packed;

/* File Attrubutes */
#घोषणा खाता_ATTRIBUTE_READONLY			0x00000001
#घोषणा खाता_ATTRIBUTE_HIDDEN			0x00000002
#घोषणा खाता_ATTRIBUTE_SYSTEM			0x00000004
#घोषणा खाता_ATTRIBUTE_सूचीECTORY		0x00000010
#घोषणा खाता_ATTRIBUTE_ARCHIVE			0x00000020
#घोषणा खाता_ATTRIBUTE_NORMAL			0x00000080
#घोषणा खाता_ATTRIBUTE_TEMPORARY		0x00000100
#घोषणा खाता_ATTRIBUTE_SPARSE_खाता		0x00000200
#घोषणा खाता_ATTRIBUTE_REPARSE_POINT		0x00000400
#घोषणा खाता_ATTRIBUTE_COMPRESSED		0x00000800
#घोषणा खाता_ATTRIBUTE_OFFLINE			0x00001000
#घोषणा खाता_ATTRIBUTE_NOT_CONTENT_INDEXED	0x00002000
#घोषणा खाता_ATTRIBUTE_ENCRYPTED		0x00004000
#घोषणा खाता_ATTRIBUTE_INTEGRITY_STREAM		0x00008000
#घोषणा खाता_ATTRIBUTE_NO_SCRUB_DATA		0x00020000

/* Oplock levels */
#घोषणा SMB2_OPLOCK_LEVEL_NONE		0x00
#घोषणा SMB2_OPLOCK_LEVEL_II		0x01
#घोषणा SMB2_OPLOCK_LEVEL_EXCLUSIVE	0x08
#घोषणा SMB2_OPLOCK_LEVEL_BATCH		0x09
#घोषणा SMB2_OPLOCK_LEVEL_LEASE		0xFF
/* Non-spec पूर्णांकernal type */
#घोषणा SMB2_OPLOCK_LEVEL_NOCHANGE	0x99

/* Desired Access Flags */
#घोषणा खाता_READ_DATA_LE		cpu_to_le32(0x00000001)
#घोषणा खाता_WRITE_DATA_LE		cpu_to_le32(0x00000002)
#घोषणा खाता_APPEND_DATA_LE		cpu_to_le32(0x00000004)
#घोषणा खाता_READ_EA_LE			cpu_to_le32(0x00000008)
#घोषणा खाता_WRITE_EA_LE		cpu_to_le32(0x00000010)
#घोषणा खाता_EXECUTE_LE			cpu_to_le32(0x00000020)
#घोषणा खाता_READ_ATTRIBUTES_LE		cpu_to_le32(0x00000080)
#घोषणा खाता_WRITE_ATTRIBUTES_LE	cpu_to_le32(0x00000100)
#घोषणा खाता_DELETE_LE			cpu_to_le32(0x00010000)
#घोषणा खाता_READ_CONTROL_LE		cpu_to_le32(0x00020000)
#घोषणा खाता_WRITE_DAC_LE		cpu_to_le32(0x00040000)
#घोषणा खाता_WRITE_OWNER_LE		cpu_to_le32(0x00080000)
#घोषणा खाता_SYNCHRONIZE_LE		cpu_to_le32(0x00100000)
#घोषणा खाता_ACCESS_SYSTEM_SECURITY_LE	cpu_to_le32(0x01000000)
#घोषणा खाता_MAXIMAL_ACCESS_LE		cpu_to_le32(0x02000000)
#घोषणा खाता_GENERIC_ALL_LE		cpu_to_le32(0x10000000)
#घोषणा खाता_GENERIC_EXECUTE_LE		cpu_to_le32(0x20000000)
#घोषणा खाता_GENERIC_WRITE_LE		cpu_to_le32(0x40000000)
#घोषणा खाता_GENERIC_READ_LE		cpu_to_le32(0x80000000)

/* ShareAccess Flags */
#घोषणा खाता_SHARE_READ_LE		cpu_to_le32(0x00000001)
#घोषणा खाता_SHARE_WRITE_LE		cpu_to_le32(0x00000002)
#घोषणा खाता_SHARE_DELETE_LE		cpu_to_le32(0x00000004)
#घोषणा खाता_SHARE_ALL_LE		cpu_to_le32(0x00000007)

/* CreateDisposition Flags */
#घोषणा खाता_SUPERSEDE_LE		cpu_to_le32(0x00000000)
#घोषणा खाता_OPEN_LE			cpu_to_le32(0x00000001)
#घोषणा खाता_CREATE_LE			cpu_to_le32(0x00000002)
#घोषणा	खाता_OPEN_IF_LE			cpu_to_le32(0x00000003)
#घोषणा खाता_OVERWRITE_LE		cpu_to_le32(0x00000004)
#घोषणा खाता_OVERWRITE_IF_LE		cpu_to_le32(0x00000005)

/* CreateOptions Flags */
#घोषणा खाता_सूचीECTORY_खाता_LE		cpu_to_le32(0x00000001)
/* same as #घोषणा CREATE_NOT_खाता_LE	cpu_to_le32(0x00000001) */
#घोषणा खाता_WRITE_THROUGH_LE		cpu_to_le32(0x00000002)
#घोषणा खाता_SEQUENTIAL_ONLY_LE		cpu_to_le32(0x00000004)
#घोषणा खाता_NO_INTERMEDIATE_BUFFERRING_LE cpu_to_le32(0x00000008)
#घोषणा खाता_SYNCHRONOUS_IO_ALERT_LE	cpu_to_le32(0x00000010)
#घोषणा खाता_SYNCHRONOUS_IO_NON_ALERT_LE	cpu_to_le32(0x00000020)
#घोषणा खाता_NON_सूचीECTORY_खाता_LE	cpu_to_le32(0x00000040)
#घोषणा खाता_COMPLETE_IF_OPLOCKED_LE	cpu_to_le32(0x00000100)
#घोषणा खाता_NO_EA_KNOWLEDGE_LE		cpu_to_le32(0x00000200)
#घोषणा खाता_RANDOM_ACCESS_LE		cpu_to_le32(0x00000800)
#घोषणा खाता_DELETE_ON_CLOSE_LE		cpu_to_le32(0x00001000)
#घोषणा खाता_OPEN_BY_खाता_ID_LE		cpu_to_le32(0x00002000)
#घोषणा खाता_OPEN_FOR_BACKUP_INTENT_LE	cpu_to_le32(0x00004000)
#घोषणा खाता_NO_COMPRESSION_LE		cpu_to_le32(0x00008000)
#घोषणा खाता_RESERVE_OPFILTER_LE	cpu_to_le32(0x00100000)
#घोषणा खाता_OPEN_REPARSE_POINT_LE	cpu_to_le32(0x00200000)
#घोषणा खाता_OPEN_NO_RECALL_LE		cpu_to_le32(0x00400000)
#घोषणा खाता_OPEN_FOR_FREE_SPACE_QUERY_LE cpu_to_le32(0x00800000)

#घोषणा खाता_READ_RIGHTS_LE (खाता_READ_DATA_LE | खाता_READ_EA_LE \
			| खाता_READ_ATTRIBUTES_LE)
#घोषणा खाता_WRITE_RIGHTS_LE (खाता_WRITE_DATA_LE | खाता_APPEND_DATA_LE \
			| खाता_WRITE_EA_LE | खाता_WRITE_ATTRIBUTES_LE)
#घोषणा खाता_EXEC_RIGHTS_LE (खाता_EXECUTE_LE)

/* Impersonation Levels. See MS-WPO section 9.7 and MSDN-IMPERS */
#घोषणा IL_ANONYMOUS		cpu_to_le32(0x00000000)
#घोषणा IL_IDENTIFICATION	cpu_to_le32(0x00000001)
#घोषणा IL_IMPERSONATION	cpu_to_le32(0x00000002)
#घोषणा IL_DELEGATE		cpu_to_le32(0x00000003)

/* Create Context Values */
#घोषणा SMB2_CREATE_EA_BUFFER			"ExtA" /* extended attributes */
#घोषणा SMB2_CREATE_SD_BUFFER			"SecD" /* security descriptor */
#घोषणा SMB2_CREATE_DURABLE_HANDLE_REQUEST	"DHnQ"
#घोषणा SMB2_CREATE_DURABLE_HANDLE_RECONNECT	"DHnC"
#घोषणा SMB2_CREATE_ALLOCATION_SIZE		"AISi"
#घोषणा SMB2_CREATE_QUERY_MAXIMAL_ACCESS_REQUEST "MxAc"
#घोषणा SMB2_CREATE_TIMEWARP_REQUEST		"TWrp"
#घोषणा SMB2_CREATE_QUERY_ON_DISK_ID		"QFid"
#घोषणा SMB2_CREATE_REQUEST_LEASE		"RqLs"
#घोषणा SMB2_CREATE_DURABLE_HANDLE_REQUEST_V2	"DH2Q"
#घोषणा SMB2_CREATE_DURABLE_HANDLE_RECONNECT_V2	"DH2C"
#घोषणा SMB2_CREATE_APP_INSTANCE_ID	0x45BCA66AEFA7F74A9008FA462E144D74
#घोषणा SMB2_CREATE_APP_INSTANCE_VERSION 0xB982D0B73B56074FA07B524A8116A010
#घोषणा SVHDX_OPEN_DEVICE_CONTEX	0x9CCBCF9E04C1E643980E158DA1F6EC83
#घोषणा SMB2_CREATE_TAG_POSIX		0x93AD25509CB411E7B42383DE968BCD7C

/* Flag (SMB3 खोलो response) values */
#घोषणा SMB2_CREATE_FLAG_REPARSEPOINT 0x01

/*
 * Maximum number of iovs we need क्रम an खोलो/create request.
 * [0] : काष्ठा smb2_create_req
 * [1] : path
 * [2] : lease context
 * [3] : durable context
 * [4] : posix context
 * [5] : समय warp context
 * [6] : query id context
 * [7] : compound padding
 */
#घोषणा SMB2_CREATE_IOV_SIZE 8

काष्ठा smb2_create_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 57 */
	__u8   SecurityFlags;
	__u8   RequestedOplockLevel;
	__le32 ImpersonationLevel;
	__le64 SmbCreateFlags;
	__le64 Reserved;
	__le32 DesiredAccess;
	__le32 FileAttributes;
	__le32 ShareAccess;
	__le32 CreateDisposition;
	__le32 CreateOptions;
	__le16 NameOffset;
	__le16 NameLength;
	__le32 CreateContextsOffset;
	__le32 CreateContextsLength;
	__u8   Buffer[];
पूर्ण __packed;

/*
 * Maximum size of a SMB2_CREATE response is 64 (smb2 header) +
 * 88 (fixed part of create response) + 520 (path) + 208 (contexts) +
 * 2 bytes of padding.
 */
#घोषणा MAX_SMB2_CREATE_RESPONSE_SIZE 880

काष्ठा smb2_create_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 89 */
	__u8   OplockLevel;
	__u8   Flag;  /* 0x01 अगर reparse poपूर्णांक */
	__le32 CreateAction;
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le64 AllocationSize;
	__le64 EnकरोfFile;
	__le32 FileAttributes;
	__le32 Reserved2;
	__u64  PersistentFileId; /* opaque endianness */
	__u64  VolatileFileId; /* opaque endianness */
	__le32 CreateContextsOffset;
	__le32 CreateContextsLength;
	__u8   Buffer[1];
पूर्ण __packed;

काष्ठा create_context अणु
	__le32 Next;
	__le16 NameOffset;
	__le16 NameLength;
	__le16 Reserved;
	__le16 DataOffset;
	__le32 DataLength;
	__u8 Buffer[];
पूर्ण __packed;

#घोषणा SMB2_LEASE_READ_CACHING_HE	0x01
#घोषणा SMB2_LEASE_HANDLE_CACHING_HE	0x02
#घोषणा SMB2_LEASE_WRITE_CACHING_HE	0x04

#घोषणा SMB2_LEASE_NONE			cpu_to_le32(0x00)
#घोषणा SMB2_LEASE_READ_CACHING		cpu_to_le32(0x01)
#घोषणा SMB2_LEASE_HANDLE_CACHING	cpu_to_le32(0x02)
#घोषणा SMB2_LEASE_WRITE_CACHING	cpu_to_le32(0x04)

#घोषणा SMB2_LEASE_FLAG_BREAK_IN_PROGRESS cpu_to_le32(0x00000002)
#घोषणा SMB2_LEASE_FLAG_PARENT_LEASE_KEY_SET cpu_to_le32(0x00000004)

#घोषणा SMB2_LEASE_KEY_SIZE 16

काष्ठा lease_context अणु
	u8 LeaseKey[SMB2_LEASE_KEY_SIZE];
	__le32 LeaseState;
	__le32 LeaseFlags;
	__le64 LeaseDuration;
पूर्ण __packed;

काष्ठा lease_context_v2 अणु
	u8 LeaseKey[SMB2_LEASE_KEY_SIZE];
	__le32 LeaseState;
	__le32 LeaseFlags;
	__le64 LeaseDuration;
	__le64 ParentLeaseKeyLow;
	__le64 ParentLeaseKeyHigh;
	__le16 Epoch;
	__le16 Reserved;
पूर्ण __packed;

काष्ठा create_lease अणु
	काष्ठा create_context ccontext;
	__u8   Name[8];
	काष्ठा lease_context lcontext;
पूर्ण __packed;

काष्ठा create_lease_v2 अणु
	काष्ठा create_context ccontext;
	__u8   Name[8];
	काष्ठा lease_context_v2 lcontext;
	__u8   Pad[4];
पूर्ण __packed;

काष्ठा create_durable अणु
	काष्ठा create_context ccontext;
	__u8   Name[8];
	जोड़ अणु
		__u8  Reserved[16];
		काष्ठा अणु
			__u64 PersistentFileId;
			__u64 VolatileFileId;
		पूर्ण Fid;
	पूर्ण Data;
पूर्ण __packed;

काष्ठा create_posix अणु
	काष्ठा create_context ccontext;
	__u8	Name[16];
	__le32  Mode;
	__u32	Reserved;
पूर्ण __packed;

/* See MS-SMB2 2.2.13.2.11 */
/* Flags */
#घोषणा SMB2_DHANDLE_FLAG_PERSISTENT	0x00000002
काष्ठा durable_context_v2 अणु
	__le32 Timeout;
	__le32 Flags;
	__u64 Reserved;
	__u8 CreateGuid[16];
पूर्ण __packed;

काष्ठा create_durable_v2 अणु
	काष्ठा create_context ccontext;
	__u8   Name[8];
	काष्ठा durable_context_v2 dcontext;
पूर्ण __packed;

/* See MS-SMB2 2.2.13.2.12 */
काष्ठा durable_reconnect_context_v2 अणु
	काष्ठा अणु
		__u64 PersistentFileId;
		__u64 VolatileFileId;
	पूर्ण Fid;
	__u8 CreateGuid[16];
	__le32 Flags; /* see above DHANDLE_FLAG_PERSISTENT */
पूर्ण __packed;

/* See MS-SMB2 2.2.14.2.9 */
काष्ठा create_on_disk_id अणु
	काष्ठा create_context ccontext;
	__u8   Name[8];
	__le64 DiskFileId;
	__le64 VolumeId;
	__u32  Reserved[4];
पूर्ण __packed;

/* See MS-SMB2 2.2.14.2.12 */
काष्ठा durable_reconnect_context_v2_rsp अणु
	__le32 Timeout;
	__le32 Flags; /* see above DHANDLE_FLAG_PERSISTENT */
पूर्ण __packed;

काष्ठा create_durable_handle_reconnect_v2 अणु
	काष्ठा create_context ccontext;
	__u8   Name[8];
	काष्ठा durable_reconnect_context_v2 dcontext;
	__u8   Pad[4];
पूर्ण __packed;

/* See MS-SMB2 2.2.13.2.5 */
काष्ठा crt_twarp_ctxt अणु
	काष्ठा create_context ccontext;
	__u8	Name[8];
	__le64	Timestamp;

पूर्ण __packed;

/* See MS-SMB2 2.2.13.2.9 */
काष्ठा crt_query_id_ctxt अणु
	काष्ठा create_context ccontext;
	__u8	Name[8];
पूर्ण __packed;

काष्ठा crt_sd_ctxt अणु
	काष्ठा create_context ccontext;
	__u8	Name[8];
	काष्ठा smb3_sd sd;
पूर्ण __packed;


#घोषणा COPY_CHUNK_RES_KEY_SIZE	24
काष्ठा resume_key_req अणु
	अक्षर ResumeKey[COPY_CHUNK_RES_KEY_SIZE];
	__le32	ContextLength;	/* MBZ */
	अक्षर	Context[];	/* ignored, Winकरोws sets to 4 bytes of zero */
पूर्ण __packed;

/* this goes in the ioctl buffer when करोing a copychunk request */
काष्ठा copychunk_ioctl अणु
	अक्षर SourceKey[COPY_CHUNK_RES_KEY_SIZE];
	__le32 ChunkCount; /* we are only sending 1 */
	__le32 Reserved;
	/* array will only be one chunk दीर्घ क्रम us */
	__le64 SourceOffset;
	__le64 TargetOffset;
	__le32 Length; /* how many bytes to copy */
	__u32 Reserved2;
पूर्ण __packed;

/* this goes in the ioctl buffer when करोing FSCTL_SET_ZERO_DATA */
काष्ठा file_zero_data_inक्रमmation अणु
	__le64	FileOffset;
	__le64	BeyondFinalZero;
पूर्ण __packed;

काष्ठा copychunk_ioctl_rsp अणु
	__le32 ChunksWritten;
	__le32 ChunkBytesWritten;
	__le32 TotalBytesWritten;
पूर्ण __packed;

/* See MS-FSCC 2.3.29 and 2.3.30 */
काष्ठा get_retrieval_poपूर्णांकer_count_req अणु
	__le64 StartingVcn; /* भव cluster number (चिन्हित) */
पूर्ण __packed;

काष्ठा get_retrieval_poपूर्णांकer_count_rsp अणु
	__le32 ExtentCount;
पूर्ण __packed;

/*
 * See MS-FSCC 2.3.33 and 2.3.34
 * request is the same as get_retrieval_poपूर्णांक_count_req काष्ठा above
 */
काष्ठा smb3_extents अणु
	__le64 NextVcn;
	__le64 Lcn; /* logical cluster number */
पूर्ण __packed;

काष्ठा get_retrieval_poपूर्णांकers_refcount_rsp अणु
	__le32 ExtentCount;
	__u32  Reserved;
	__le64 StartingVcn;
	काष्ठा smb3_extents extents[];
पूर्ण __packed;

काष्ठा fsctl_set_पूर्णांकegrity_inक्रमmation_req अणु
	__le16	ChecksumAlgorithm;
	__le16	Reserved;
	__le32	Flags;
पूर्ण __packed;

काष्ठा fsctl_get_पूर्णांकegrity_inक्रमmation_rsp अणु
	__le16	ChecksumAlgorithm;
	__le16	Reserved;
	__le32	Flags;
	__le32	ChecksumChunkSizeInBytes;
	__le32	ClusterSizeInBytes;
पूर्ण __packed;

काष्ठा file_allocated_range_buffer अणु
	__le64	file_offset;
	__le64	length;
पूर्ण __packed;

/* Integrity ChecksumAlgorithm choices क्रम above */
#घोषणा	CHECKSUM_TYPE_NONE	0x0000
#घोषणा	CHECKSUM_TYPE_CRC64	0x0002
#घोषणा CHECKSUM_TYPE_UNCHANGED	0xFFFF	/* set only */

/* Integrity flags क्रम above */
#घोषणा FSCTL_INTEGRITY_FLAG_CHECKSUM_ENFORCEMENT_OFF	0x00000001

/* Reparse काष्ठाures - see MS-FSCC 2.1.2 */

/* काष्ठा fsctl_reparse_info_req is empty, only response काष्ठाs (see below) */

काष्ठा reparse_data_buffer अणु
	__le32	ReparseTag;
	__le16	ReparseDataLength;
	__u16	Reserved;
	__u8	DataBuffer[]; /* Variable Length */
पूर्ण __packed;

काष्ठा reparse_guid_data_buffer अणु
	__le32	ReparseTag;
	__le16	ReparseDataLength;
	__u16	Reserved;
	__u8	ReparseGuid[16];
	__u8	DataBuffer[]; /* Variable Length */
पूर्ण __packed;

काष्ठा reparse_mount_poपूर्णांक_data_buffer अणु
	__le32	ReparseTag;
	__le16	ReparseDataLength;
	__u16	Reserved;
	__le16	SubstituteNameOffset;
	__le16	SubstituteNameLength;
	__le16	Prपूर्णांकNameOffset;
	__le16	Prपूर्णांकNameLength;
	__u8	PathBuffer[]; /* Variable Length */
पूर्ण __packed;

#घोषणा SYMLINK_FLAG_RELATIVE 0x00000001

काष्ठा reparse_symlink_data_buffer अणु
	__le32	ReparseTag;
	__le16	ReparseDataLength;
	__u16	Reserved;
	__le16	SubstituteNameOffset;
	__le16	SubstituteNameLength;
	__le16	Prपूर्णांकNameOffset;
	__le16	Prपूर्णांकNameLength;
	__le32	Flags;
	__u8	PathBuffer[]; /* Variable Length */
पूर्ण __packed;

/* See MS-FSCC 2.1.2.6 and cअगरspdu.h क्रम काष्ठा reparse_posix_data */


/* See MS-DFSC 2.2.2 */
काष्ठा fsctl_get_dfs_referral_req अणु
	__le16 MaxReferralLevel;
	__u8 RequestFileName[];
पूर्ण __packed;

/* DFS response is काष्ठा get_dfs_refer_rsp */

/* See MS-SMB2 2.2.31.3 */
काष्ठा network_resiliency_req अणु
	__le32 Timeout;
	__le32 Reserved;
पूर्ण __packed;
/* There is no buffer क्रम the response ie no काष्ठा network_resiliency_rsp */


काष्ठा validate_negotiate_info_req अणु
	__le32 Capabilities;
	__u8   Guid[SMB2_CLIENT_GUID_SIZE];
	__le16 SecurityMode;
	__le16 DialectCount;
	__le16 Dialects[4]; /* BB expand this अगर स्वतःnegotiate > 4 dialects */
पूर्ण __packed;

काष्ठा validate_negotiate_info_rsp अणु
	__le32 Capabilities;
	__u8   Guid[SMB2_CLIENT_GUID_SIZE];
	__le16 SecurityMode;
	__le16 Dialect; /* Dialect in use क्रम the connection */
पूर्ण __packed;

#घोषणा RSS_CAPABLE	cpu_to_le32(0x00000001)
#घोषणा RDMA_CAPABLE	cpu_to_le32(0x00000002)

#घोषणा INTERNETWORK	cpu_to_le16(0x0002)
#घोषणा INTERNETWORKV6	cpu_to_le16(0x0017)

काष्ठा network_पूर्णांकerface_info_ioctl_rsp अणु
	__le32 Next; /* next पूर्णांकerface. zero अगर this is last one */
	__le32 IfIndex;
	__le32 Capability; /* RSS or RDMA Capable */
	__le32 Reserved;
	__le64 LinkSpeed;
	__le16 Family;
	__u8 Buffer[126];
पूर्ण __packed;

काष्ठा अगरace_info_ipv4 अणु
	__be16 Port;
	__be32 IPv4Address;
	__be64 Reserved;
पूर्ण __packed;

काष्ठा अगरace_info_ipv6 अणु
	__be16 Port;
	__be32 FlowInfo;
	__u8   IPv6Address[16];
	__be32 ScopeId;
पूर्ण __packed;

#घोषणा NO_खाता_ID 0xFFFFFFFFFFFFFFFFULL /* general ioctls to srv not to file */

काष्ठा compress_ioctl अणु
	__le16 CompressionState; /* See cअगरspdu.h क्रम possible flag values */
पूर्ण __packed;

काष्ठा duplicate_extents_to_file अणु
	__u64 PersistentFileHandle; /* source file handle, opaque endianness */
	__u64 VolatileFileHandle;
	__le64 SourceFileOffset;
	__le64 TargetFileOffset;
	__le64 ByteCount;  /* Bytes to be copied */
पूर्ण __packed;

/*
 * Maximum number of iovs we need क्रम an ioctl request.
 * [0] : काष्ठा smb2_ioctl_req
 * [1] : in_data
 */
#घोषणा SMB2_IOCTL_IOV_SIZE 2

काष्ठा smb2_ioctl_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 57 */
	__u16 Reserved;
	__le32 CtlCode;
	__u64  PersistentFileId; /* opaque endianness */
	__u64  VolatileFileId; /* opaque endianness */
	__le32 InputOffset;
	__le32 InputCount;
	__le32 MaxInputResponse;
	__le32 OutputOffset;
	__le32 OutputCount;
	__le32 MaxOutputResponse;
	__le32 Flags;
	__u32  Reserved2;
	__u8   Buffer[];
पूर्ण __packed;

काष्ठा smb2_ioctl_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 57 */
	__u16 Reserved;
	__le32 CtlCode;
	__u64  PersistentFileId; /* opaque endianness */
	__u64  VolatileFileId; /* opaque endianness */
	__le32 InputOffset;
	__le32 InputCount;
	__le32 OutputOffset;
	__le32 OutputCount;
	__le32 Flags;
	__u32  Reserved2;
	/* अक्षर * buffer[] */
पूर्ण __packed;

/* Currently defined values क्रम बंद flags */
#घोषणा SMB2_CLOSE_FLAG_POSTQUERY_ATTRIB	cpu_to_le16(0x0001)
काष्ठा smb2_बंद_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 24 */
	__le16 Flags;
	__le32 Reserved;
	__u64  PersistentFileId; /* opaque endianness */
	__u64  VolatileFileId; /* opaque endianness */
पूर्ण __packed;

/*
 * Maximum size of a SMB2_CLOSE response is 64 (smb2 header) + 60 (data)
 */
#घोषणा MAX_SMB2_CLOSE_RESPONSE_SIZE 124

काष्ठा smb2_बंद_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* 60 */
	__le16 Flags;
	__le32 Reserved;
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le64 AllocationSize;	/* Beginning of खाता_STANDARD_INFO equivalent */
	__le64 EndOfFile;
	__le32 Attributes;
पूर्ण __packed;

काष्ठा smb2_flush_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 24 */
	__le16 Reserved1;
	__le32 Reserved2;
	__u64  PersistentFileId; /* opaque endianness */
	__u64  VolatileFileId; /* opaque endianness */
पूर्ण __packed;

काष्ठा smb2_flush_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;
	__le16 Reserved;
पूर्ण __packed;

/* For पढ़ो request Flags field below, following flag is defined क्रम SMB3.02 */
#घोषणा SMB2_READFLAG_READ_UNBUFFERED	0x01
#घोषणा SMB2_READFLAG_REQUEST_COMPRESSED 0x02 /* See MS-SMB2 2.2.19 */

/* Channel field क्रम पढ़ो and ग_लिखो: exactly one of following flags can be set*/
#घोषणा SMB2_CHANNEL_NONE	cpu_to_le32(0x00000000)
#घोषणा SMB2_CHANNEL_RDMA_V1	cpu_to_le32(0x00000001) /* SMB3 or later */
#घोषणा SMB2_CHANNEL_RDMA_V1_INVALIDATE cpu_to_le32(0x00000002) /* >= SMB3.02 */
#घोषणा SMB2_CHANNEL_RDMA_TRANSFORM cpu_to_le32(0x00000003) /* >= SMB3.02, only used on ग_लिखो */

/* SMB2 पढ़ो request without RFC1001 length at the beginning */
काष्ठा smb2_पढ़ो_plain_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 49 */
	__u8   Padding; /* offset from start of SMB2 header to place पढ़ो */
	__u8   Flags; /* MBZ unless SMB3.02 or later */
	__le32 Length;
	__le64 Offset;
	__u64  PersistentFileId; /* opaque endianness */
	__u64  VolatileFileId; /* opaque endianness */
	__le32 MinimumCount;
	__le32 Channel; /* MBZ except क्रम SMB3 or later */
	__le32 Reमुख्यingBytes;
	__le16 ReadChannelInfoOffset;
	__le16 ReadChannelInfoLength;
	__u8   Buffer[1];
पूर्ण __packed;

/* Read flags */
#घोषणा SMB2_READFLAG_RESPONSE_NONE	0x00000000
#घोषणा SMB2_READFLAG_RESPONSE_RDMA_TRANSFORM	0x00000001

काष्ठा smb2_पढ़ो_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 17 */
	__u8   DataOffset;
	__u8   Reserved;
	__le32 DataLength;
	__le32 DataReमुख्यing;
	__u32  Flags;
	__u8   Buffer[1];
पूर्ण __packed;

/* For ग_लिखो request Flags field below the following flags are defined: */
#घोषणा SMB2_WRITEFLAG_WRITE_THROUGH	0x00000001	/* SMB2.1 or later */
#घोषणा SMB2_WRITEFLAG_WRITE_UNBUFFERED	0x00000002	/* SMB3.02 or later */

काष्ठा smb2_ग_लिखो_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 49 */
	__le16 DataOffset; /* offset from start of SMB2 header to ग_लिखो data */
	__le32 Length;
	__le64 Offset;
	__u64  PersistentFileId; /* opaque endianness */
	__u64  VolatileFileId; /* opaque endianness */
	__le32 Channel; /* MBZ unless SMB3.02 or later */
	__le32 Reमुख्यingBytes;
	__le16 WriteChannelInfoOffset;
	__le16 WriteChannelInfoLength;
	__le32 Flags;
	__u8   Buffer[1];
पूर्ण __packed;

काष्ठा smb2_ग_लिखो_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 17 */
	__u8   DataOffset;
	__u8   Reserved;
	__le32 DataLength;
	__le32 DataReमुख्यing;
	__u32  Reserved2;
	__u8   Buffer[1];
पूर्ण __packed;

/* notअगरy flags */
#घोषणा SMB2_WATCH_TREE			0x0001

/* notअगरy completion filter flags. See MS-FSCC 2.6 and MS-SMB2 2.2.35 */
#घोषणा खाता_NOTIFY_CHANGE_खाता_NAME		0x00000001
#घोषणा खाता_NOTIFY_CHANGE_सूची_NAME		0x00000002
#घोषणा खाता_NOTIFY_CHANGE_ATTRIBUTES		0x00000004
#घोषणा खाता_NOTIFY_CHANGE_SIZE			0x00000008
#घोषणा खाता_NOTIFY_CHANGE_LAST_WRITE		0x00000010
#घोषणा खाता_NOTIFY_CHANGE_LAST_ACCESS		0x00000020
#घोषणा खाता_NOTIFY_CHANGE_CREATION		0x00000040
#घोषणा खाता_NOTIFY_CHANGE_EA			0x00000080
#घोषणा खाता_NOTIFY_CHANGE_SECURITY		0x00000100
#घोषणा खाता_NOTIFY_CHANGE_STREAM_NAME		0x00000200
#घोषणा खाता_NOTIFY_CHANGE_STREAM_SIZE		0x00000400
#घोषणा खाता_NOTIFY_CHANGE_STREAM_WRITE		0x00000800

काष्ठा smb2_change_notअगरy_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16	StructureSize;
	__le16	Flags;
	__le32	OutputBufferLength;
	__u64	PersistentFileId; /* opaque endianness */
	__u64	VolatileFileId; /* opaque endianness */
	__le32	CompletionFilter;
	__u32	Reserved;
पूर्ण __packed;

काष्ठा smb2_change_notअगरy_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16	StructureSize;  /* Must be 9 */
	__le16	OutputBufferOffset;
	__le32	OutputBufferLength;
	__u8	Buffer[1]; /* array of file notअगरy काष्ठाs */
पूर्ण __packed;

#घोषणा SMB2_LOCKFLAG_SHARED_LOCK	0x0001
#घोषणा SMB2_LOCKFLAG_EXCLUSIVE_LOCK	0x0002
#घोषणा SMB2_LOCKFLAG_UNLOCK		0x0004
#घोषणा SMB2_LOCKFLAG_FAIL_IMMEDIATELY	0x0010

काष्ठा smb2_lock_element अणु
	__le64 Offset;
	__le64 Length;
	__le32 Flags;
	__le32 Reserved;
पूर्ण __packed;

काष्ठा smb2_lock_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 48 */
	__le16 LockCount;
	/*
	 * The least signअगरicant four bits are the index, the other 28 bits are
	 * the lock sequence number (0 to 64). See MS-SMB2 2.2.26
	 */
	__le32 LockSequenceNumber;
	__u64  PersistentFileId; /* opaque endianness */
	__u64  VolatileFileId; /* opaque endianness */
	/* Followed by at least one */
	काष्ठा smb2_lock_element locks[1];
पूर्ण __packed;

काष्ठा smb2_lock_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 4 */
	__le16 Reserved;
पूर्ण __packed;

काष्ठा smb2_echo_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 4 */
	__u16  Reserved;
पूर्ण __packed;

काष्ठा smb2_echo_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize;	/* Must be 4 */
	__u16  Reserved;
पूर्ण __packed;

/* search (query_directory) Flags field */
#घोषणा SMB2_RESTART_SCANS		0x01
#घोषणा SMB2_RETURN_SINGLE_ENTRY	0x02
#घोषणा SMB2_INDEX_SPECIFIED		0x04
#घोषणा SMB2_REOPEN			0x10

#घोषणा SMB2_QUERY_सूचीECTORY_IOV_SIZE 2

काष्ठा smb2_query_directory_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 33 */
	__u8   FileInक्रमmationClass;
	__u8   Flags;
	__le32 FileIndex;
	__u64  PersistentFileId; /* opaque endianness */
	__u64  VolatileFileId; /* opaque endianness */
	__le16 FileNameOffset;
	__le16 FileNameLength;
	__le32 OutputBufferLength;
	__u8   Buffer[1];
पूर्ण __packed;

काष्ठा smb2_query_directory_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 9 */
	__le16 OutputBufferOffset;
	__le32 OutputBufferLength;
	__u8   Buffer[1];
पूर्ण __packed;

/* Possible InfoType values */
#घोषणा SMB2_O_INFO_खाता	0x01
#घोषणा SMB2_O_INFO_खाताSYSTEM	0x02
#घोषणा SMB2_O_INFO_SECURITY	0x03
#घोषणा SMB2_O_INFO_QUOTA	0x04

/* Security info type additionalinfo flags. See MS-SMB2 (2.2.37) or MS-DTYP */
#घोषणा OWNER_SECINFO   0x00000001
#घोषणा GROUP_SECINFO   0x00000002
#घोषणा DACL_SECINFO   0x00000004
#घोषणा SACL_SECINFO   0x00000008
#घोषणा LABEL_SECINFO   0x00000010
#घोषणा ATTRIBUTE_SECINFO   0x00000020
#घोषणा SCOPE_SECINFO   0x00000040
#घोषणा BACKUP_SECINFO   0x00010000
#घोषणा UNPROTECTED_SACL_SECINFO   0x10000000
#घोषणा UNPROTECTED_DACL_SECINFO   0x20000000
#घोषणा PROTECTED_SACL_SECINFO   0x40000000
#घोषणा PROTECTED_DACL_SECINFO   0x80000000

/* Flags used क्रम FileFullEAinfo */
#घोषणा SL_RESTART_SCAN		0x00000001
#घोषणा SL_RETURN_SINGLE_ENTRY	0x00000002
#घोषणा SL_INDEX_SPECIFIED	0x00000004

काष्ठा smb2_query_info_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 41 */
	__u8   InfoType;
	__u8   FileInfoClass;
	__le32 OutputBufferLength;
	__le16 InputBufferOffset;
	__u16  Reserved;
	__le32 InputBufferLength;
	__le32 AdditionalInक्रमmation;
	__le32 Flags;
	__u64  PersistentFileId; /* opaque endianness */
	__u64  VolatileFileId; /* opaque endianness */
	__u8   Buffer[1];
पूर्ण __packed;

काष्ठा smb2_query_info_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 9 */
	__le16 OutputBufferOffset;
	__le32 OutputBufferLength;
	__u8   Buffer[1];
पूर्ण __packed;

/*
 * Maximum number of iovs we need क्रम a set-info request.
 * The largest one is नाम/hardlink
 * [0] : काष्ठा smb2_set_info_req + smb2_file_[नाम|link]_info
 * [1] : path
 * [2] : compound padding
 */
#घोषणा SMB2_SET_INFO_IOV_SIZE 3

काष्ठा smb2_set_info_req अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 33 */
	__u8   InfoType;
	__u8   FileInfoClass;
	__le32 BufferLength;
	__le16 BufferOffset;
	__u16  Reserved;
	__le32 AdditionalInक्रमmation;
	__u64  PersistentFileId; /* opaque endianness */
	__u64  VolatileFileId; /* opaque endianness */
	__u8   Buffer[1];
पूर्ण __packed;

काष्ठा smb2_set_info_rsp अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 2 */
पूर्ण __packed;

काष्ठा smb2_oplock_अवरोध अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 24 */
	__u8   OplockLevel;
	__u8   Reserved;
	__le32 Reserved2;
	__u64  PersistentFid;
	__u64  VolatileFid;
पूर्ण __packed;

#घोषणा SMB2_NOTIFY_BREAK_LEASE_FLAG_ACK_REQUIRED cpu_to_le32(0x01)

काष्ठा smb2_lease_अवरोध अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 44 */
	__le16 Epoch;
	__le32 Flags;
	__u8   LeaseKey[16];
	__le32 CurrentLeaseState;
	__le32 NewLeaseState;
	__le32 BreakReason;
	__le32 AccessMaskHपूर्णांक;
	__le32 ShareMaskHपूर्णांक;
पूर्ण __packed;

काष्ठा smb2_lease_ack अणु
	काष्ठा smb2_sync_hdr sync_hdr;
	__le16 StructureSize; /* Must be 36 */
	__le16 Reserved;
	__le32 Flags;
	__u8   LeaseKey[16];
	__le32 LeaseState;
	__le64 LeaseDuration;
पूर्ण __packed;

/*
 *	PDU infolevel काष्ठाure definitions
 *	BB consider moving to a dअगरferent header
 */

/* File System Inक्रमmation Classes */
#घोषणा FS_VOLUME_INFORMATION		1 /* Query */
#घोषणा FS_LABEL_INFORMATION		2 /* Local only */
#घोषणा FS_SIZE_INFORMATION		3 /* Query */
#घोषणा FS_DEVICE_INFORMATION		4 /* Query */
#घोषणा FS_ATTRIBUTE_INFORMATION	5 /* Query */
#घोषणा FS_CONTROL_INFORMATION		6 /* Query, Set */
#घोषणा FS_FULL_SIZE_INFORMATION	7 /* Query */
#घोषणा FS_OBJECT_ID_INFORMATION	8 /* Query, Set */
#घोषणा FS_DRIVER_PATH_INFORMATION	9 /* Local only */
#घोषणा FS_VOLUME_FLAGS_INFORMATION	10 /* Local only */
#घोषणा FS_SECTOR_SIZE_INFORMATION	11 /* SMB3 or later. Query */
#घोषणा FS_POSIX_INFORMATION		100 /* SMB3.1.1 POSIX. Query */

काष्ठा smb2_fs_full_size_info अणु
	__le64 TotalAllocationUnits;
	__le64 CallerAvailableAllocationUnits;
	__le64 ActualAvailableAllocationUnits;
	__le32 SectorsPerAllocationUnit;
	__le32 BytesPerSector;
पूर्ण __packed;

#घोषणा SSINFO_FLAGS_ALIGNED_DEVICE		0x00000001
#घोषणा SSINFO_FLAGS_PARTITION_ALIGNED_ON_DEVICE 0x00000002
#घोषणा SSINFO_FLAGS_NO_SEEK_PENALTY		0x00000004
#घोषणा SSINFO_FLAGS_TRIM_ENABLED		0x00000008

/* sector size info काष्ठा */
काष्ठा smb3_fs_ss_info अणु
	__le32 LogicalBytesPerSector;
	__le32 PhysicalBytesPerSectorForAtomicity;
	__le32 PhysicalBytesPerSectorForPerf;
	__le32 FileSystemEffectivePhysicalBytesPerSectorForAtomicity;
	__le32 Flags;
	__le32 ByteOffsetForSectorAlignment;
	__le32 ByteOffsetForPartitionAlignment;
पूर्ण __packed;

/* volume info काष्ठा - see MS-FSCC 2.5.9 */
#घोषणा MAX_VOL_LABEL_LEN	32
काष्ठा smb3_fs_vol_info अणु
	__le64	VolumeCreationTime;
	__u32	VolumeSerialNumber;
	__le32	VolumeLabelLength; /* includes trailing null */
	__u8	SupportsObjects; /* True अगर eg like NTFS, supports objects */
	__u8	Reserved;
	__u8	VolumeLabel[]; /* variable len */
पूर्ण __packed;

/* partial list of QUERY INFO levels */
#घोषणा खाता_सूचीECTORY_INFORMATION	1
#घोषणा खाता_FULL_सूचीECTORY_INFORMATION 2
#घोषणा खाता_BOTH_सूचीECTORY_INFORMATION 3
#घोषणा खाता_BASIC_INFORMATION		4
#घोषणा खाता_STANDARD_INFORMATION	5
#घोषणा खाता_INTERNAL_INFORMATION	6
#घोषणा खाता_EA_INFORMATION	        7
#घोषणा खाता_ACCESS_INFORMATION		8
#घोषणा खाता_NAME_INFORMATION		9
#घोषणा खाता_RENAME_INFORMATION		10
#घोषणा खाता_LINK_INFORMATION		11
#घोषणा खाता_NAMES_INFORMATION		12
#घोषणा खाता_DISPOSITION_INFORMATION	13
#घोषणा खाता_POSITION_INFORMATION	14
#घोषणा खाता_FULL_EA_INFORMATION	15
#घोषणा खाता_MODE_INFORMATION		16
#घोषणा खाता_ALIGNMENT_INFORMATION	17
#घोषणा खाता_ALL_INFORMATION		18
#घोषणा खाता_ALLOCATION_INFORMATION	19
#घोषणा खाता_END_OF_खाता_INFORMATION	20
#घोषणा खाता_ALTERNATE_NAME_INFORMATION 21
#घोषणा खाता_STREAM_INFORMATION		22
#घोषणा खाता_PIPE_INFORMATION		23
#घोषणा खाता_PIPE_LOCAL_INFORMATION	24
#घोषणा खाता_PIPE_REMOTE_INFORMATION	25
#घोषणा खाता_MAILSLOT_QUERY_INFORMATION 26
#घोषणा खाता_MAILSLOT_SET_INFORMATION	27
#घोषणा खाता_COMPRESSION_INFORMATION	28
#घोषणा खाता_OBJECT_ID_INFORMATION	29
/* Number 30 not defined in करोcuments */
#घोषणा खाता_MOVE_CLUSTER_INFORMATION	31
#घोषणा खाता_QUOTA_INFORMATION		32
#घोषणा खाता_REPARSE_POINT_INFORMATION	33
#घोषणा खाता_NETWORK_OPEN_INFORMATION	34
#घोषणा खाता_ATTRIBUTE_TAG_INFORMATION	35
#घोषणा खाता_TRACKING_INFORMATION	36
#घोषणा खाताID_BOTH_सूचीECTORY_INFORMATION 37
#घोषणा खाताID_FULL_सूचीECTORY_INFORMATION 38
#घोषणा खाता_VALID_DATA_LENGTH_INFORMATION 39
#घोषणा खाता_SHORT_NAME_INFORMATION	40
#घोषणा खाता_SFIO_RESERVE_INFORMATION	44
#घोषणा खाता_SFIO_VOLUME_INFORMATION	45
#घोषणा खाता_HARD_LINK_INFORMATION	46
#घोषणा खाता_NORMALIZED_NAME_INFORMATION 48
#घोषणा खाताID_GLOBAL_TX_सूचीECTORY_INFORMATION 50
#घोषणा खाता_STANDARD_LINK_INFORMATION	54
#घोषणा खाता_ID_INFORMATION		59

काष्ठा smb2_file_पूर्णांकernal_info अणु
	__le64 IndexNumber;
पूर्ण __packed; /* level 6 Query */

काष्ठा smb2_file_नाम_info अणु /* encoding of request क्रम level 10 */
	__u8   ReplaceIfExists; /* 1 = replace existing target with new */
				/* 0 = fail अगर target alपढ़ोy exists */
	__u8   Reserved[7];
	__u64  RootDirectory;  /* MBZ क्रम network operations (why says spec?) */
	__le32 FileNameLength;
	अक्षर   FileName[];     /* New name to be asचिन्हित */
	/* padding - overall काष्ठा size must be >= 24 so filename + pad >= 6 */
पूर्ण __packed; /* level 10 Set */

काष्ठा smb2_file_link_info अणु /* encoding of request क्रम level 11 */
	__u8   ReplaceIfExists; /* 1 = replace existing link with new */
				/* 0 = fail अगर link alपढ़ोy exists */
	__u8   Reserved[7];
	__u64  RootDirectory;  /* MBZ क्रम network operations (why says spec?) */
	__le32 FileNameLength;
	अक्षर   FileName[];     /* Name to be asचिन्हित to new link */
पूर्ण __packed; /* level 11 Set */

काष्ठा smb2_file_full_ea_info अणु /* encoding of response क्रम level 15 */
	__le32 next_entry_offset;
	__u8   flags;
	__u8   ea_name_length;
	__le16 ea_value_length;
	अक्षर   ea_data[]; /* \0 terminated name plus value */
पूर्ण __packed; /* level 15 Set */

/*
 * This level 18, although with काष्ठा with same name is dअगरferent from cअगरs
 * level 0x107. Level 0x107 has an extra u64 between AccessFlags and
 * CurrentByteOffset.
 */
काष्ठा smb2_file_all_info अणु /* data block encoding of response to level 18 */
	__le64 CreationTime;	/* Beginning of खाता_BASIC_INFO equivalent */
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le32 Attributes;
	__u32  Pad1;		/* End of खाता_BASIC_INFO_INFO equivalent */
	__le64 AllocationSize;	/* Beginning of खाता_STANDARD_INFO equivalent */
	__le64 EndOfFile;	/* size ie offset to first मुक्त byte in file */
	__le32 NumberOfLinks;	/* hard links */
	__u8   DeletePending;
	__u8   Directory;
	__u16  Pad2;		/* End of खाता_STANDARD_INFO equivalent */
	__le64 IndexNumber;
	__le32 EASize;
	__le32 AccessFlags;
	__le64 CurrentByteOffset;
	__le32 Mode;
	__le32 AlignmentRequirement;
	__le32 FileNameLength;
	अक्षर   FileName[1];
पूर्ण __packed; /* level 18 Query */

काष्ठा smb2_file_eof_info अणु /* encoding of request क्रम level 10 */
	__le64 EndOfFile; /* new end of file value */
पूर्ण __packed; /* level 20 Set */

काष्ठा smb2_file_reparse_poपूर्णांक_info अणु
	__le64 IndexNumber;
	__le32 Tag;
पूर्ण __packed;

काष्ठा smb2_file_network_खोलो_info अणु
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le64 AllocationSize;
	__le64 EndOfFile;
	__le32 Attributes;
	__le32 Reserved;
पूर्ण __packed; /* level 34 Query also similar वापसed in बंद rsp and खोलो rsp */

/* See MS-FSCC 2.4.43 */
काष्ठा smb2_file_id_inक्रमmation अणु
	__le64	VolumeSerialNumber;
	__u64  PersistentFileId; /* opaque endianness */
	__u64  VolatileFileId; /* opaque endianness */
पूर्ण __packed; /* level 59 */

बाह्य अक्षर smb2_padding[7];

/* equivalent of the contents of SMB3.1.1 POSIX खोलो context response */
काष्ठा create_posix_rsp अणु
	u32 nlink;
	u32 reparse_tag;
	u32 mode;
	काष्ठा cअगरs_sid owner; /* var-sized on the wire */
	काष्ठा cअगरs_sid group; /* var-sized on the wire */
पूर्ण __packed;

/*
 * SMB2-only POSIX info level क्रम query dir
 *
 * See posix_info_sid_size(), posix_info_extra_size() and
 * posix_info_parse() to help with the handling of this काष्ठा.
 */
काष्ठा smb2_posix_info अणु
	__le32 NextEntryOffset;
	__u32 Ignored;
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le64 EndOfFile;
	__le64 AllocationSize;
	__le32 DosAttributes;
	__le64 Inode;
	__le32 DeviceId;
	__le32 Zero;
	/* beginning of POSIX Create Context Response */
	__le32 HardLinks;
	__le32 ReparseTag;
	__le32 Mode;
	/*
	 * var sized owner SID
	 * var sized group SID
	 * le32 filenamelength
	 * u8  filename[]
	 */
पूर्ण __packed;

/* Level 100 query info */
काष्ठा smb311_posix_qinfo अणु
	__le64 CreationTime;
	__le64 LastAccessTime;
	__le64 LastWriteTime;
	__le64 ChangeTime;
	__le64 EndOfFile;
	__le64 AllocationSize;
	__le32 DosAttributes;
	__le64 Inode;
	__le32 DeviceId;
	__le32 Zero;
	/* beginning of POSIX Create Context Response */
	__le32 HardLinks;
	__le32 ReparseTag;
	__le32 Mode;
	u8     Sids[];
	/*
	 * var sized owner SID
	 * var sized group SID
	 * le32 filenamelength
	 * u8  filename[]
	 */
पूर्ण __packed;

/*
 * Parsed version of the above काष्ठा. Allows direct access to the
 * variable length fields
 */
काष्ठा smb2_posix_info_parsed अणु
	स्थिर काष्ठा smb2_posix_info *base;
	माप_प्रकार size;
	काष्ठा cअगरs_sid owner;
	काष्ठा cअगरs_sid group;
	पूर्णांक name_len;
	स्थिर u8 *name;
पूर्ण;

#पूर्ण_अगर				/* _SMB2PDU_H */
