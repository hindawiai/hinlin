<शैली गुरु>
/*
 * osta_udf.h
 *
 * This file is based on OSTA UDF(पंचांग) 2.60 (March 1, 2005)
 * http://www.osta.org
 *
 * Copyright (c) 2001-2004  Ben Fennema
 * Copyright (c) 2017-2019  Pali Rohथँr <pali@kernel.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 * @file
 * OSTA-UDF defines and काष्ठाure definitions
 */

#समावेश "ecma_167.h"

#अगर_अघोषित _OSTA_UDF_H
#घोषणा _OSTA_UDF_H 1

/* OSTA CS0 Charspec (UDF 2.60 2.1.2) */
#घोषणा UDF_CHAR_SET_TYPE		0
#घोषणा UDF_CHAR_SET_INFO		"OSTA Compressed Unicode"

/* Entity Identअगरier (UDF 2.60 2.1.5) */
/* Identअगरiers (UDF 2.60 2.1.5.2) */
/* Implementation Use Extended Attribute (UDF 2.60 3.3.4.5) */
/* Virtual Allocation Table (UDF 1.50 2.2.10) */
/* Logical Volume Extended Inक्रमmation (UDF 1.50 Errata, DCN 5003, 3.3.4.5.1.3) */
/* OS2EA (UDF 1.50 3.3.4.5.3.1) */
/* MacUniqueIDTable (UDF 1.50 3.3.4.5.4.3) */
/* MacResourceFork (UDF 1.50 3.3.4.5.4.4) */
#घोषणा UDF_ID_DEVELOPER		"*Linux UDFFS"
#घोषणा	UDF_ID_COMPLIANT		"*OSTA UDF Compliant"
#घोषणा UDF_ID_LV_INFO			"*UDF LV Info"
#घोषणा UDF_ID_FREE_EA			"*UDF FreeEASpace"
#घोषणा UDF_ID_FREE_APP_EA		"*UDF FreeAppEASpace"
#घोषणा UDF_ID_DVD_CGMS			"*UDF DVD CGMS Info"
#घोषणा UDF_ID_VAT_LVEXTENSION		"*UDF VAT LVExtension"
#घोषणा UDF_ID_OS2_EA			"*UDF OS/2 EA"
#घोषणा UDF_ID_OS2_EA_LENGTH		"*UDF OS/2 EALength"
#घोषणा UDF_ID_MAC_VOLUME		"*UDF Mac VolumeInfo"
#घोषणा UDF_ID_MAC_FINDER		"*UDF Mac FinderInfo"
#घोषणा UDF_ID_MAC_UNIQUE		"*UDF Mac UniqueIDTable"
#घोषणा UDF_ID_MAC_RESOURCE		"*UDF Mac ResourceFork"
#घोषणा UDF_ID_OS400_सूचीINFO		"*UDF OS/400 DirInfo"
#घोषणा UDF_ID_VIRTUAL			"*UDF Virtual Partition"
#घोषणा UDF_ID_SPARABLE			"*UDF Sparable Partition"
#घोषणा UDF_ID_ALLOC			"*UDF Virtual Alloc Tbl"
#घोषणा UDF_ID_SPARING			"*UDF Sparing Table"
#घोषणा UDF_ID_METADATA			"*UDF Metadata Partition"

/* Identअगरier Suffix (UDF 2.60 2.1.5.3) */
#घोषणा DOMAIN_FLAGS_HARD_WRITE_PROTECT	0x01
#घोषणा DOMAIN_FLAGS_SOFT_WRITE_PROTECT	0x02

काष्ठा करोमुख्यIdentSuffix अणु
	__le16		UDFRevision;
	uपूर्णांक8_t		करोमुख्यFlags;
	uपूर्णांक8_t		reserved[5];
पूर्ण __packed;

काष्ठा UDFIdentSuffix अणु
	__le16		UDFRevision;
	uपूर्णांक8_t		OSClass;
	uपूर्णांक8_t		OSIdentअगरier;
	uपूर्णांक8_t		reserved[4];
पूर्ण __packed;

काष्ठा impIdentSuffix अणु
	uपूर्णांक8_t		OSClass;
	uपूर्णांक8_t		OSIdentअगरier;
	uपूर्णांक8_t		impUse[6];
पूर्ण __packed;

काष्ठा appIdentSuffix अणु
	uपूर्णांक8_t		impUse[8];
पूर्ण __packed;

/* Logical Volume Integrity Descriptor (UDF 2.60 2.2.6) */
/* Implementation Use (UDF 2.60 2.2.6.4) */
काष्ठा logicalVolIntegrityDescImpUse अणु
	काष्ठा regid	impIdent;
	__le32		numFiles;
	__le32		numDirs;
	__le16		minUDFReadRev;
	__le16		minUDFWriteRev;
	__le16		maxUDFWriteRev;
	uपूर्णांक8_t		impUse[0];
पूर्ण __packed;

/* Implementation Use Volume Descriptor (UDF 2.60 2.2.7) */
/* Implementation Use (UDF 2.60 2.2.7.2) */
काष्ठा impUseVolDescImpUse अणु
	काष्ठा अक्षरspec	LVICharset;
	dstring		logicalVolIdent[128];
	dstring		LVInfo1[36];
	dstring		LVInfo2[36];
	dstring		LVInfo3[36];
	काष्ठा regid	impIdent;
	uपूर्णांक8_t		impUse[128];
पूर्ण __packed;

काष्ठा udfPartitionMap2 अणु
	uपूर्णांक8_t		partitionMapType;
	uपूर्णांक8_t		partitionMapLength;
	uपूर्णांक8_t		reserved1[2];
	काष्ठा regid	partIdent;
	__le16		volSeqNum;
	__le16		partitionNum;
पूर्ण __packed;

/* Virtual Partition Map (UDF 2.60 2.2.8) */
काष्ठा भवPartitionMap अणु
	uपूर्णांक8_t		partitionMapType;
	uपूर्णांक8_t		partitionMapLength;
	uपूर्णांक8_t		reserved1[2];
	काष्ठा regid	partIdent;
	__le16		volSeqNum;
	__le16		partitionNum;
	uपूर्णांक8_t		reserved2[24];
पूर्ण __packed;

/* Sparable Partition Map (UDF 2.60 2.2.9) */
काष्ठा sparablePartitionMap अणु
	uपूर्णांक8_t partitionMapType;
	uपूर्णांक8_t partitionMapLength;
	uपूर्णांक8_t reserved1[2];
	काष्ठा regid partIdent;
	__le16 volSeqNum;
	__le16 partitionNum;
	__le16 packetLength;
	uपूर्णांक8_t numSparingTables;
	uपूर्णांक8_t reserved2[1];
	__le32 sizeSparingTable;
	__le32 locSparingTable[4];
पूर्ण __packed;

/* Metadata Partition Map (UDF 2.60 2.2.10) */
काष्ठा metadataPartitionMap अणु
	uपूर्णांक8_t		partitionMapType;
	uपूर्णांक8_t		partitionMapLength;
	uपूर्णांक8_t		reserved1[2];
	काष्ठा regid	partIdent;
	__le16		volSeqNum;
	__le16		partitionNum;
	__le32		metadataFileLoc;
	__le32		metadataMirrorFileLoc;
	__le32		metadataBiपंचांगapFileLoc;
	__le32		allocUnitSize;
	__le16		alignUnitSize;
	uपूर्णांक8_t		flags;
	uपूर्णांक8_t		reserved2[5];
पूर्ण __packed;

/* Virtual Allocation Table (UDF 1.5 2.2.10) */
काष्ठा भवAllocationTable15 अणु
	__le32		vatEntry[0];
	काष्ठा regid	vatIdent;
	__le32		previousVATICBLoc;
पूर्ण __packed;

#घोषणा ICBTAG_खाता_TYPE_VAT15		0x00U

/* Virtual Allocation Table (UDF 2.60 2.2.11) */
काष्ठा भवAllocationTable20 अणु
	__le16		lengthHeader;
	__le16		lengthImpUse;
	dstring		logicalVolIdent[128];
	__le32		previousVATICBLoc;
	__le32		numFiles;
	__le32		numDirs;
	__le16		minUDFReadRev;
	__le16		minUDFWriteRev;
	__le16		maxUDFWriteRev;
	__le16		reserved;
	uपूर्णांक8_t		impUse[0];
	__le32		vatEntry[0];
पूर्ण __packed;

#घोषणा ICBTAG_खाता_TYPE_VAT20		0xF8U

/* Sparing Table (UDF 2.60 2.2.12) */
काष्ठा sparingEntry अणु
	__le32		origLocation;
	__le32		mappedLocation;
पूर्ण __packed;

काष्ठा sparingTable अणु
	काष्ठा tag	descTag;
	काष्ठा regid	sparingIdent;
	__le16		पुनः_स्मृतिationTableLen;
	__le16		reserved;
	__le32		sequenceNum;
	काष्ठा sparingEntry
			mapEntry[0];
पूर्ण __packed;

/* Metadata File (and Metadata Mirror File) (UDF 2.60 2.2.13.1) */
#घोषणा ICBTAG_खाता_TYPE_MAIN		0xFA
#घोषणा ICBTAG_खाता_TYPE_MIRROR		0xFB
#घोषणा ICBTAG_खाता_TYPE_BITMAP		0xFC

/* काष्ठा दीर्घ_ad ICB - ADImpUse (UDF 2.60 2.2.4.3) */
काष्ठा allocDescImpUse अणु
	__le16		flags;
	uपूर्णांक8_t		impUse[4];
पूर्ण __packed;

#घोषणा AD_IU_EXT_ERASED		0x0001

/* Real-Time Files (UDF 2.60 6.11) */
#घोषणा ICBTAG_खाता_TYPE_REALTIME	0xF9U

/* Implementation Use Extended Attribute (UDF 2.60 3.3.4.5) */
/* FreeEASpace (UDF 2.60 3.3.4.5.1.1) */
काष्ठा मुक्तEaSpace अणु
	__le16		headerChecksum;
	uपूर्णांक8_t		मुक्तEASpace[0];
पूर्ण __packed;

/* DVD Copyright Management Inक्रमmation (UDF 2.60 3.3.4.5.1.2) */
काष्ठा DVDCopyrightImpUse अणु
	__le16		headerChecksum;
	uपूर्णांक8_t		CGMSInfo;
	uपूर्णांक8_t		dataType;
	uपूर्णांक8_t		protectionSystemInfo[4];
पूर्ण __packed;

/* Logical Volume Extended Inक्रमmation (UDF 1.50 Errata, DCN 5003, 3.3.4.5.1.3) */
काष्ठा LVExtensionEA अणु
	__le16		headerChecksum;
	__le64		verअगरicationID;
	__le32		numFiles;
	__le32		numDirs;
	dstring		logicalVolIdent[128];
पूर्ण __packed;

/* Application Use Extended Attribute (UDF 2.60 3.3.4.6) */
/* FreeAppEASpace (UDF 2.60 3.3.4.6.1) */
काष्ठा मुक्तAppEASpace अणु
	__le16		headerChecksum;
	uपूर्णांक8_t		मुक्तEASpace[0];
पूर्ण __packed;

/* UDF Defined System Stream (UDF 2.60 3.3.7) */
#घोषणा UDF_ID_UNIQUE_ID		"*UDF Unique ID Mapping Data"
#घोषणा UDF_ID_NON_ALLOC		"*UDF Non-Allocatable Space"
#घोषणा UDF_ID_POWER_CAL		"*UDF Power Cal Table"
#घोषणा UDF_ID_BACKUP			"*UDF Backup"

/* UDF Defined Non-System Streams (UDF 2.60 3.3.8) */
#घोषणा UDF_ID_MAC_RESOURCE_FORK_STREAM	"*UDF Macintosh Resource Fork"
/* #घोषणा UDF_ID_OS2_EA		"*UDF OS/2 EA" */
#घोषणा UDF_ID_NT_ACL			"*UDF NT ACL"
#घोषणा UDF_ID_UNIX_ACL			"*UDF UNIX ACL"

/* Operating System Identअगरiers (UDF 2.60 6.3) */
#घोषणा UDF_OS_CLASS_UNDEF		0x00U
#घोषणा UDF_OS_CLASS_DOS		0x01U
#घोषणा UDF_OS_CLASS_OS2		0x02U
#घोषणा UDF_OS_CLASS_MAC		0x03U
#घोषणा UDF_OS_CLASS_UNIX		0x04U
#घोषणा UDF_OS_CLASS_WIN9X		0x05U
#घोषणा UDF_OS_CLASS_WINNT		0x06U
#घोषणा UDF_OS_CLASS_OS400		0x07U
#घोषणा UDF_OS_CLASS_BEOS		0x08U
#घोषणा UDF_OS_CLASS_WINCE		0x09U

#घोषणा UDF_OS_ID_UNDEF			0x00U
#घोषणा UDF_OS_ID_DOS			0x00U
#घोषणा UDF_OS_ID_OS2			0x00U
#घोषणा UDF_OS_ID_MAC			0x00U
#घोषणा UDF_OS_ID_MAX_OSX		0x01U
#घोषणा UDF_OS_ID_UNIX			0x00U
#घोषणा UDF_OS_ID_AIX			0x01U
#घोषणा UDF_OS_ID_SOLARIS		0x02U
#घोषणा UDF_OS_ID_HPUX			0x03U
#घोषणा UDF_OS_ID_IRIX			0x04U
#घोषणा UDF_OS_ID_LINUX			0x05U
#घोषणा UDF_OS_ID_MKLINUX		0x06U
#घोषणा UDF_OS_ID_FREEBSD		0x07U
#घोषणा UDF_OS_ID_NETBSD		0x08U
#घोषणा UDF_OS_ID_WIN9X			0x00U
#घोषणा UDF_OS_ID_WINNT			0x00U
#घोषणा UDF_OS_ID_OS400			0x00U
#घोषणा UDF_OS_ID_BEOS			0x00U
#घोषणा UDF_OS_ID_WINCE			0x00U

#पूर्ण_अगर /* _OSTA_UDF_H */
