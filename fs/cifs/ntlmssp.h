<शैली गुरु>
/*
 *   fs/cअगरs/ntlmssp.h
 *
 *   Copyright (c) International Business Machines  Corp., 2002,2007
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

#घोषणा NTLMSSP_SIGNATURE "NTLMSSP"
/* Message Types */
#घोषणा NtLmNegotiate     cpu_to_le32(1)
#घोषणा NtLmChallenge     cpu_to_le32(2)
#घोषणा NtLmAuthenticate  cpu_to_le32(3)
#घोषणा UnknownMessage    cpu_to_le32(8)

/* Negotiate Flags */
#घोषणा NTLMSSP_NEGOTIATE_UNICODE         0x01 /* Text strings are unicode */
#घोषणा NTLMSSP_NEGOTIATE_OEM             0x02 /* Text strings are in OEM */
#घोषणा NTLMSSP_REQUEST_TARGET            0x04 /* Srv वापसs its auth realm */
/* define reserved9                       0x08 */
#घोषणा NTLMSSP_NEGOTIATE_SIGN          0x0010 /* Request signing capability */
#घोषणा NTLMSSP_NEGOTIATE_SEAL          0x0020 /* Request confidentiality */
#घोषणा NTLMSSP_NEGOTIATE_DGRAM         0x0040
#घोषणा NTLMSSP_NEGOTIATE_LM_KEY        0x0080 /* Use LM session key */
/* defined reserved 8                   0x0100 */
#घोषणा NTLMSSP_NEGOTIATE_NTLM          0x0200 /* NTLM authentication */
#घोषणा NTLMSSP_NEGOTIATE_NT_ONLY       0x0400 /* Lanman not allowed */
#घोषणा NTLMSSP_ANONYMOUS               0x0800
#घोषणा NTLMSSP_NEGOTIATE_DOMAIN_SUPPLIED 0x1000 /* reserved6 */
#घोषणा NTLMSSP_NEGOTIATE_WORKSTATION_SUPPLIED 0x2000
#घोषणा NTLMSSP_NEGOTIATE_LOCAL_CALL    0x4000 /* client/server same machine */
#घोषणा NTLMSSP_NEGOTIATE_ALWAYS_SIGN   0x8000 /* Sign. All security levels  */
#घोषणा NTLMSSP_TARGET_TYPE_DOMAIN     0x10000
#घोषणा NTLMSSP_TARGET_TYPE_SERVER     0x20000
#घोषणा NTLMSSP_TARGET_TYPE_SHARE      0x40000
#घोषणा NTLMSSP_NEGOTIATE_EXTENDED_SEC 0x80000 /* NB:not related to NTLMv2 pwd*/
/* #घोषणा NTLMSSP_REQUEST_INIT_RESP     0x100000 */
#घोषणा NTLMSSP_NEGOTIATE_IDENTIFY    0x100000
#घोषणा NTLMSSP_REQUEST_ACCEPT_RESP   0x200000 /* reserved5 */
#घोषणा NTLMSSP_REQUEST_NON_NT_KEY    0x400000
#घोषणा NTLMSSP_NEGOTIATE_TARGET_INFO 0x800000
/* #घोषणा reserved4                 0x1000000 */
#घोषणा NTLMSSP_NEGOTIATE_VERSION    0x2000000 /* we करो not set */
/* #घोषणा reserved3                 0x4000000 */
/* #घोषणा reserved2                 0x8000000 */
/* #घोषणा reserved1                0x10000000 */
#घोषणा NTLMSSP_NEGOTIATE_128       0x20000000
#घोषणा NTLMSSP_NEGOTIATE_KEY_XCH   0x40000000
#घोषणा NTLMSSP_NEGOTIATE_56        0x80000000

/* Define AV Pair Field IDs */
क्रमागत av_field_type अणु
	NTLMSSP_AV_EOL = 0,
	NTLMSSP_AV_NB_COMPUTER_NAME,
	NTLMSSP_AV_NB_DOMAIN_NAME,
	NTLMSSP_AV_DNS_COMPUTER_NAME,
	NTLMSSP_AV_DNS_DOMAIN_NAME,
	NTLMSSP_AV_DNS_TREE_NAME,
	NTLMSSP_AV_FLAGS,
	NTLMSSP_AV_TIMESTAMP,
	NTLMSSP_AV_RESTRICTION,
	NTLMSSP_AV_TARGET_NAME,
	NTLMSSP_AV_CHANNEL_BINDINGS
पूर्ण;

/* Although प्रकारs are not commonly used क्रम काष्ठाure definitions */
/* in the Linux kernel, in this particular हाल they are useful      */
/* to more बंदly match the standards करोcument क्रम NTLMSSP from     */
/* OpenGroup and to make the code more बंदly match the standard in */
/* appearance */

प्रकार काष्ठा _SECURITY_BUFFER अणु
	__le16 Length;
	__le16 MaximumLength;
	__le32 BufferOffset;	/* offset to buffer */
पूर्ण __attribute__((packed)) SECURITY_BUFFER;

प्रकार काष्ठा _NEGOTIATE_MESSAGE अणु
	__u8 Signature[माप(NTLMSSP_SIGNATURE)];
	__le32 MessageType;     /* NtLmNegotiate = 1 */
	__le32 NegotiateFlags;
	SECURITY_BUFFER Doमुख्यName;	/* RFC 1001 style and ASCII */
	SECURITY_BUFFER WorkstationName;	/* RFC 1001 and ASCII */
	/* SECURITY_BUFFER क्रम version info not present since we
	   करो not set the version is present flag */
	अक्षर Doमुख्यString[0];
	/* followed by WorkstationString */
पूर्ण __attribute__((packed)) NEGOTIATE_MESSAGE, *PNEGOTIATE_MESSAGE;

प्रकार काष्ठा _CHALLENGE_MESSAGE अणु
	__u8 Signature[माप(NTLMSSP_SIGNATURE)];
	__le32 MessageType;   /* NtLmChallenge = 2 */
	SECURITY_BUFFER TargetName;
	__le32 NegotiateFlags;
	__u8 Challenge[CIFS_CRYPTO_KEY_SIZE];
	__u8 Reserved[8];
	SECURITY_BUFFER TargetInfoArray;
	/* SECURITY_BUFFER क्रम version info not present since we
	   करो not set the version is present flag */
पूर्ण __attribute__((packed)) CHALLENGE_MESSAGE, *PCHALLENGE_MESSAGE;

प्रकार काष्ठा _AUTHENTICATE_MESSAGE अणु
	__u8 Signature[माप(NTLMSSP_SIGNATURE)];
	__le32 MessageType;  /* NtLmsAuthenticate = 3 */
	SECURITY_BUFFER LmChallengeResponse;
	SECURITY_BUFFER NtChallengeResponse;
	SECURITY_BUFFER Doमुख्यName;
	SECURITY_BUFFER UserName;
	SECURITY_BUFFER WorkstationName;
	SECURITY_BUFFER SessionKey;
	__le32 NegotiateFlags;
	/* SECURITY_BUFFER क्रम version info not present since we
	   करो not set the version is present flag */
	अक्षर UserString[0];
पूर्ण __attribute__((packed)) AUTHENTICATE_MESSAGE, *PAUTHENTICATE_MESSAGE;

/*
 * Size of the session key (crypto key encrypted with the password
 */

पूर्णांक decode_ntlmssp_challenge(अक्षर *bcc_ptr, पूर्णांक blob_len, काष्ठा cअगरs_ses *ses);
व्योम build_ntlmssp_negotiate_blob(अचिन्हित अक्षर *pbuffer, काष्ठा cअगरs_ses *ses);
पूर्णांक build_ntlmssp_auth_blob(अचिन्हित अक्षर **pbuffer, u16 *buflen,
			काष्ठा cअगरs_ses *ses,
			स्थिर काष्ठा nls_table *nls_cp);
