<शैली गुरु>
/*
 * ecma_167.h
 *
 * This file is based on ECMA-167 3rd edition (June 1997)
 * https://www.ecma.ch
 *
 * Copyright (c) 2001-2002  Ben Fennema
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
 * ECMA-167r3 defines and काष्ठाure definitions
 */

#समावेश <linux/types.h>

#अगर_अघोषित _ECMA_167_H
#घोषणा _ECMA_167_H 1

/* Character sets and coding - d-अक्षरacters (ECMA 167r3 1/7.2) */
प्रकार uपूर्णांक8_t		dअक्षरs;

/* Character set specअगरication (ECMA 167r3 1/7.2.1) */
काष्ठा अक्षरspec अणु
	uपूर्णांक8_t		अक्षरSetType;
	uपूर्णांक8_t		अक्षरSetInfo[63];
पूर्ण __packed;

/* Character Set Type (ECMA 167r3 1/7.2.1.1) */
#घोषणा CHARSPEC_TYPE_CS0		0x00	/* (1/7.2.2) */
#घोषणा CHARSPEC_TYPE_CS1		0x01	/* (1/7.2.3) */
#घोषणा CHARSPEC_TYPE_CS2		0x02	/* (1/7.2.4) */
#घोषणा CHARSPEC_TYPE_CS3		0x03	/* (1/7.2.5) */
#घोषणा CHARSPEC_TYPE_CS4		0x04	/* (1/7.2.6) */
#घोषणा CHARSPEC_TYPE_CS5		0x05	/* (1/7.2.7) */
#घोषणा CHARSPEC_TYPE_CS6		0x06	/* (1/7.2.8) */
#घोषणा CHARSPEC_TYPE_CS7		0x07	/* (1/7.2.9) */
#घोषणा CHARSPEC_TYPE_CS8		0x08	/* (1/7.2.10) */

/* Fixed-length अक्षरacter fields - d-string (EMCA 167r3 1/7.2.12) */
प्रकार uपूर्णांक8_t		dstring;

/* Timestamp (ECMA 167r3 1/7.3) */
काष्ठा बारtamp अणु
	__le16		typeAndTimezone;
	__le16		year;
	uपूर्णांक8_t		month;
	uपूर्णांक8_t		day;
	uपूर्णांक8_t		hour;
	uपूर्णांक8_t		minute;
	uपूर्णांक8_t		second;
	uपूर्णांक8_t		centiseconds;
	uपूर्णांक8_t		hundredsOfMicroseconds;
	uपूर्णांक8_t		microseconds;
पूर्ण __packed;

/* Type and Time Zone (ECMA 167r3 1/7.3.1) */
#घोषणा TIMESTAMP_TYPE_MASK		0xF000
#घोषणा TIMESTAMP_TYPE_CUT		0x0000
#घोषणा TIMESTAMP_TYPE_LOCAL		0x1000
#घोषणा TIMESTAMP_TYPE_AGREEMENT	0x2000
#घोषणा TIMESTAMP_TIMEZONE_MASK		0x0FFF

/* Entity identअगरier (ECMA 167r3 1/7.4) */
काष्ठा regid अणु
	uपूर्णांक8_t		flags;
	uपूर्णांक8_t		ident[23];
	uपूर्णांक8_t		identSuffix[8];
पूर्ण __packed;

/* Flags (ECMA 167r3 1/7.4.1) */
#घोषणा ENTITYID_FLAGS_सूचीTY		0x01
#घोषणा ENTITYID_FLAGS_PROTECTED	0x02

/* Volume Structure Descriptor (ECMA 167r3 2/9.1) */
#घोषणा VSD_STD_ID_LEN			5
काष्ठा volStructDesc अणु
	uपूर्णांक8_t		काष्ठाType;
	uपूर्णांक8_t		stdIdent[VSD_STD_ID_LEN];
	uपूर्णांक8_t		काष्ठाVersion;
	uपूर्णांक8_t		काष्ठाData[2041];
पूर्ण __packed;

/* Standard Identअगरier (EMCA 167r2 2/9.1.2) */
#घोषणा VSD_STD_ID_NSR02		"NSR02"	/* (3/9.1) */

/* Standard Identअगरier (ECMA 167r3 2/9.1.2) */
#घोषणा VSD_STD_ID_BEA01		"BEA01"	/* (2/9.2) */
#घोषणा VSD_STD_ID_BOOT2		"BOOT2"	/* (2/9.4) */
#घोषणा VSD_STD_ID_CD001		"CD001"	/* (ECMA-119) */
#घोषणा VSD_STD_ID_CDW02		"CDW02"	/* (ECMA-168) */
#घोषणा VSD_STD_ID_NSR03		"NSR03"	/* (3/9.1) */
#घोषणा VSD_STD_ID_TEA01		"TEA01"	/* (2/9.3) */

/* Beginning Extended Area Descriptor (ECMA 167r3 2/9.2) */
काष्ठा beginningExtendedAreaDesc अणु
	uपूर्णांक8_t		काष्ठाType;
	uपूर्णांक8_t		stdIdent[VSD_STD_ID_LEN];
	uपूर्णांक8_t		काष्ठाVersion;
	uपूर्णांक8_t		काष्ठाData[2041];
पूर्ण __packed;

/* Terminating Extended Area Descriptor (ECMA 167r3 2/9.3) */
काष्ठा terminatingExtendedAreaDesc अणु
	uपूर्णांक8_t		काष्ठाType;
	uपूर्णांक8_t		stdIdent[VSD_STD_ID_LEN];
	uपूर्णांक8_t		काष्ठाVersion;
	uपूर्णांक8_t		काष्ठाData[2041];
पूर्ण __packed;

/* Boot Descriptor (ECMA 167r3 2/9.4) */
काष्ठा bootDesc अणु
	uपूर्णांक8_t			काष्ठाType;
	uपूर्णांक8_t			stdIdent[VSD_STD_ID_LEN];
	uपूर्णांक8_t			काष्ठाVersion;
	uपूर्णांक8_t			reserved1;
	काष्ठा regid		archType;
	काष्ठा regid		bootIdent;
	__le32			bootExtLocation;
	__le32			bootExtLength;
	__le64			loadAddress;
	__le64			startAddress;
	काष्ठा बारtamp	descCreationDateAndTime;
	__le16			flags;
	uपूर्णांक8_t			reserved2[32];
	uपूर्णांक8_t			bootUse[1906];
पूर्ण __packed;

/* Flags (ECMA 167r3 2/9.4.12) */
#घोषणा BOOT_FLAGS_ERASE		0x01

/* Extent Descriptor (ECMA 167r3 3/7.1) */
काष्ठा extent_ad अणु
	__le32		extLength;
	__le32		extLocation;
पूर्ण __packed;

काष्ठा kernel_extent_ad अणु
	uपूर्णांक32_t	extLength;
	uपूर्णांक32_t	extLocation;
पूर्ण;

/* Descriptor Tag (ECMA 167r3 3/7.2) */
काष्ठा tag अणु
	__le16		tagIdent;
	__le16		descVersion;
	uपूर्णांक8_t		tagChecksum;
	uपूर्णांक8_t		reserved;
	__le16		tagSerialNum;
	__le16		descCRC;
	__le16		descCRCLength;
	__le32		tagLocation;
पूर्ण __packed;

/* Tag Identअगरier (ECMA 167r3 3/7.2.1) */
#घोषणा TAG_IDENT_PVD			0x0001
#घोषणा TAG_IDENT_AVDP			0x0002
#घोषणा TAG_IDENT_VDP			0x0003
#घोषणा TAG_IDENT_IUVD			0x0004
#घोषणा TAG_IDENT_PD			0x0005
#घोषणा TAG_IDENT_LVD			0x0006
#घोषणा TAG_IDENT_USD			0x0007
#घोषणा TAG_IDENT_TD			0x0008
#घोषणा TAG_IDENT_LVID			0x0009

/* NSR Descriptor (ECMA 167r3 3/9.1) */
काष्ठा NSRDesc अणु
	uपूर्णांक8_t		काष्ठाType;
	uपूर्णांक8_t		stdIdent[VSD_STD_ID_LEN];
	uपूर्णांक8_t		काष्ठाVersion;
	uपूर्णांक8_t		reserved;
	uपूर्णांक8_t		काष्ठाData[2040];
पूर्ण __packed;

/* Generic Descriptor */
काष्ठा genericDesc अणु
	काष्ठा tag	descTag;
	__le32		volDescSeqNum;
	uपूर्णांक8_t		reserved[492];
पूर्ण __packed;

/* Primary Volume Descriptor (ECMA 167r3 3/10.1) */
काष्ठा primaryVolDesc अणु
	काष्ठा tag		descTag;
	__le32			volDescSeqNum;
	__le32			primaryVolDescNum;
	dstring			volIdent[32];
	__le16			volSeqNum;
	__le16			maxVolSeqNum;
	__le16			पूर्णांकerchangeLvl;
	__le16			maxInterchangeLvl;
	__le32			अक्षरSetList;
	__le32			maxCharSetList;
	dstring			volSetIdent[128];
	काष्ठा अक्षरspec		descCharSet;
	काष्ठा अक्षरspec		explanatoryCharSet;
	काष्ठा extent_ad	volAbstract;
	काष्ठा extent_ad	volCopyright;
	काष्ठा regid		appIdent;
	काष्ठा बारtamp	recordingDateAndTime;
	काष्ठा regid		impIdent;
	uपूर्णांक8_t			impUse[64];
	__le32			predecessorVolDescSeqLocation;
	__le16			flags;
	uपूर्णांक8_t			reserved[22];
पूर्ण __packed;

/* Flags (ECMA 167r3 3/10.1.21) */
#घोषणा PVD_FLAGS_VSID_COMMON		0x0001

/* Anchor Volume Descriptor Poपूर्णांकer (ECMA 167r3 3/10.2) */
काष्ठा anchorVolDescPtr अणु
	काष्ठा tag		descTag;
	काष्ठा extent_ad	मुख्यVolDescSeqExt;
	काष्ठा extent_ad	reserveVolDescSeqExt;
	uपूर्णांक8_t	 		reserved[480];
पूर्ण __packed;

/* Volume Descriptor Poपूर्णांकer (ECMA 167r3 3/10.3) */
काष्ठा volDescPtr अणु
	काष्ठा tag		descTag;
	__le32			volDescSeqNum;
	काष्ठा extent_ad	nextVolDescSeqExt;
	uपूर्णांक8_t			reserved[484];
पूर्ण __packed;

/* Implementation Use Volume Descriptor (ECMA 167r3 3/10.4) */
काष्ठा impUseVolDesc अणु
	काष्ठा tag	descTag;
	__le32		volDescSeqNum;
	काष्ठा regid	impIdent;
	uपूर्णांक8_t		impUse[460];
पूर्ण __packed;

/* Partition Descriptor (ECMA 167r3 3/10.5) */
काष्ठा partitionDesc अणु
	काष्ठा tag descTag;
	__le32 volDescSeqNum;
	__le16 partitionFlags;
	__le16 partitionNumber;
	काष्ठा regid partitionContents;
	uपूर्णांक8_t partitionContentsUse[128];
	__le32 accessType;
	__le32 partitionStartingLocation;
	__le32 partitionLength;
	काष्ठा regid impIdent;
	uपूर्णांक8_t impUse[128];
	uपूर्णांक8_t reserved[156];
पूर्ण __packed;

/* Partition Flags (ECMA 167r3 3/10.5.3) */
#घोषणा PD_PARTITION_FLAGS_ALLOC	0x0001

/* Partition Contents (ECMA 167r2 3/10.5.3) */
#घोषणा PD_PARTITION_CONTENTS_NSR02	"+NSR02"

/* Partition Contents (ECMA 167r3 3/10.5.5) */
#घोषणा PD_PARTITION_CONTENTS_FDC01	"+FDC01"
#घोषणा PD_PARTITION_CONTENTS_CD001	"+CD001"
#घोषणा PD_PARTITION_CONTENTS_CDW02	"+CDW02"
#घोषणा PD_PARTITION_CONTENTS_NSR03	"+NSR03"

/* Access Type (ECMA 167r3 3/10.5.7) */
#घोषणा PD_ACCESS_TYPE_NONE		0x00000000
#घोषणा PD_ACCESS_TYPE_READ_ONLY	0x00000001
#घोषणा PD_ACCESS_TYPE_WRITE_ONCE	0x00000002
#घोषणा PD_ACCESS_TYPE_REWRITABLE	0x00000003
#घोषणा PD_ACCESS_TYPE_OVERWRITABLE	0x00000004

/* Logical Volume Descriptor (ECMA 167r3 3/10.6) */
काष्ठा logicalVolDesc अणु
	काष्ठा tag		descTag;
	__le32			volDescSeqNum;
	काष्ठा अक्षरspec		descCharSet;
	dstring			logicalVolIdent[128];
	__le32			logicalBlockSize;
	काष्ठा regid		करोमुख्यIdent;
	uपूर्णांक8_t			logicalVolContentsUse[16];
	__le32			mapTableLength;
	__le32			numPartitionMaps;
	काष्ठा regid		impIdent;
	uपूर्णांक8_t			impUse[128];
	काष्ठा extent_ad	पूर्णांकegritySeqExt;
	uपूर्णांक8_t			partitionMaps[0];
पूर्ण __packed;

/* Generic Partition Map (ECMA 167r3 3/10.7.1) */
काष्ठा genericPartitionMap अणु
	uपूर्णांक8_t		partitionMapType;
	uपूर्णांक8_t		partitionMapLength;
	uपूर्णांक8_t		partitionMapping[0];
पूर्ण __packed;

/* Partition Map Type (ECMA 167r3 3/10.7.1.1) */
#घोषणा GP_PARTITION_MAP_TYPE_UNDEF	0x00
#घोषणा GP_PARTITION_MAP_TYPE_1		0x01
#घोषणा GP_PARTITION_MAP_TYPE_2		0x02

/* Type 1 Partition Map (ECMA 167r3 3/10.7.2) */
काष्ठा genericPartitionMap1 अणु
	uपूर्णांक8_t		partitionMapType;
	uपूर्णांक8_t		partitionMapLength;
	__le16		volSeqNum;
	__le16		partitionNum;
पूर्ण __packed;

/* Type 2 Partition Map (ECMA 167r3 3/10.7.3) */
काष्ठा genericPartitionMap2 अणु
	uपूर्णांक8_t		partitionMapType;
	uपूर्णांक8_t		partitionMapLength;
	uपूर्णांक8_t		partitionIdent[62];
पूर्ण __packed;

/* Unallocated Space Descriptor (ECMA 167r3 3/10.8) */
काष्ठा unallocSpaceDesc अणु
	काष्ठा tag		descTag;
	__le32			volDescSeqNum;
	__le32			numAllocDescs;
	काष्ठा extent_ad	allocDescs[0];
पूर्ण __packed;

/* Terminating Descriptor (ECMA 167r3 3/10.9) */
काष्ठा terminatingDesc अणु
	काष्ठा tag	descTag;
	uपूर्णांक8_t		reserved[496];
पूर्ण __packed;

/* Logical Volume Integrity Descriptor (ECMA 167r3 3/10.10) */
काष्ठा logicalVolIntegrityDesc अणु
	काष्ठा tag		descTag;
	काष्ठा बारtamp	recordingDateAndTime;
	__le32			पूर्णांकegrityType;
	काष्ठा extent_ad	nextIntegrityExt;
	uपूर्णांक8_t			logicalVolContentsUse[32];
	__le32			numOfPartitions;
	__le32			lengthOfImpUse;
	__le32			मुक्तSpaceTable[0];
	__le32			sizeTable[0];
	uपूर्णांक8_t			impUse[0];
पूर्ण __packed;

/* Integrity Type (ECMA 167r3 3/10.10.3) */
#घोषणा LVID_INTEGRITY_TYPE_OPEN	0x00000000
#घोषणा LVID_INTEGRITY_TYPE_CLOSE	0x00000001

/* Recorded Address (ECMA 167r3 4/7.1) */
काष्ठा lb_addr अणु
	__le32		logicalBlockNum;
	__le16	 	partitionReferenceNum;
पूर्ण __packed;

/* ... and its in-core analog */
काष्ठा kernel_lb_addr अणु
	uपूर्णांक32_t		logicalBlockNum;
	uपूर्णांक16_t	 	partitionReferenceNum;
पूर्ण;

/* Short Allocation Descriptor (ECMA 167r3 4/14.14.1) */
काष्ठा लघु_ad अणु
        __le32		extLength;
        __le32		extPosition;
पूर्ण __packed;

/* Long Allocation Descriptor (ECMA 167r3 4/14.14.2) */
काष्ठा दीर्घ_ad अणु
	__le32		extLength;
	काष्ठा lb_addr	extLocation;
	uपूर्णांक8_t		impUse[6];
पूर्ण __packed;

काष्ठा kernel_दीर्घ_ad अणु
	uपूर्णांक32_t		extLength;
	काष्ठा kernel_lb_addr	extLocation;
	uपूर्णांक8_t			impUse[6];
पूर्ण;

/* Extended Allocation Descriptor (ECMA 167r3 4/14.14.3) */
काष्ठा ext_ad अणु
	__le32		extLength;
	__le32		recordedLength;
	__le32		inक्रमmationLength;
	काष्ठा lb_addr	extLocation;
पूर्ण __packed;

काष्ठा kernel_ext_ad अणु
	uपूर्णांक32_t		extLength;
	uपूर्णांक32_t		recordedLength;
	uपूर्णांक32_t		inक्रमmationLength;
	काष्ठा kernel_lb_addr	extLocation;
पूर्ण;

/* Descriptor Tag (ECMA 167r3 4/7.2 - See 3/7.2) */

/* Tag Identअगरier (ECMA 167r3 4/7.2.1) */
#घोषणा TAG_IDENT_FSD			0x0100
#घोषणा TAG_IDENT_FID			0x0101
#घोषणा TAG_IDENT_AED			0x0102
#घोषणा TAG_IDENT_IE			0x0103
#घोषणा TAG_IDENT_TE			0x0104
#घोषणा TAG_IDENT_FE			0x0105
#घोषणा TAG_IDENT_EAHD			0x0106
#घोषणा TAG_IDENT_USE			0x0107
#घोषणा TAG_IDENT_SBD			0x0108
#घोषणा TAG_IDENT_PIE			0x0109
#घोषणा TAG_IDENT_EFE			0x010A

/* File Set Descriptor (ECMA 167r3 4/14.1) */
काष्ठा fileSetDesc अणु
	काष्ठा tag		descTag;
	काष्ठा बारtamp	recordingDateAndTime;
	__le16			पूर्णांकerchangeLvl;
	__le16			maxInterchangeLvl;
	__le32			अक्षरSetList;
	__le32			maxCharSetList;
	__le32			fileSetNum;
	__le32			fileSetDescNum;
	काष्ठा अक्षरspec		logicalVolIdentCharSet;
	dstring			logicalVolIdent[128];
	काष्ठा अक्षरspec		fileSetCharSet;
	dstring			fileSetIdent[32];
	dstring			copyrightFileIdent[32];
	dstring			असलtractFileIdent[32];
	काष्ठा दीर्घ_ad		rootDirectoryICB;
	काष्ठा regid		करोमुख्यIdent;
	काष्ठा दीर्घ_ad		nextExt;
	काष्ठा दीर्घ_ad		streamDirectoryICB;
	uपूर्णांक8_t			reserved[32];
पूर्ण __packed;

/* Partition Header Descriptor (ECMA 167r3 4/14.3) */
काष्ठा partitionHeaderDesc अणु
	काष्ठा लघु_ad	unallocSpaceTable;
	काष्ठा लघु_ad	unallocSpaceBiपंचांगap;
	काष्ठा लघु_ad	partitionIntegrityTable;
	काष्ठा लघु_ad	मुक्तdSpaceTable;
	काष्ठा लघु_ad	मुक्तdSpaceBiपंचांगap;
	uपूर्णांक8_t		reserved[88];
पूर्ण __packed;

/* File Identअगरier Descriptor (ECMA 167r3 4/14.4) */
काष्ठा fileIdentDesc अणु
	काष्ठा tag	descTag;
	__le16		fileVersionNum;
	uपूर्णांक8_t		fileCharacteristics;
	uपूर्णांक8_t		lengthFileIdent;
	काष्ठा दीर्घ_ad	icb;
	__le16		lengthOfImpUse;
	uपूर्णांक8_t		impUse[0];
	uपूर्णांक8_t		fileIdent[0];
	uपूर्णांक8_t		padding[0];
पूर्ण __packed;

/* File Characteristics (ECMA 167r3 4/14.4.3) */
#घोषणा FID_खाता_CHAR_HIDDEN		0x01
#घोषणा FID_खाता_CHAR_सूचीECTORY		0x02
#घोषणा FID_खाता_CHAR_DELETED		0x04
#घोषणा FID_खाता_CHAR_PARENT		0x08
#घोषणा FID_खाता_CHAR_METADATA		0x10

/* Allocation Ext Descriptor (ECMA 167r3 4/14.5) */
काष्ठा allocExtDesc अणु
	काष्ठा tag	descTag;
	__le32		previousAllocExtLocation;
	__le32		lengthAllocDescs;
पूर्ण __packed;

/* ICB Tag (ECMA 167r3 4/14.6) */
काष्ठा icbtag अणु
	__le32		priorRecordedNumDirectEntries;
	__le16		strategyType;
	__le16		strategyParameter;
	__le16		numEntries;
	uपूर्णांक8_t		reserved;
	uपूर्णांक8_t		fileType;
	काष्ठा lb_addr	parentICBLocation;
	__le16		flags;
पूर्ण __packed;

/* Strategy Type (ECMA 167r3 4/14.6.2) */
#घोषणा ICBTAG_STRATEGY_TYPE_UNDEF	0x0000
#घोषणा ICBTAG_STRATEGY_TYPE_1		0x0001
#घोषणा ICBTAG_STRATEGY_TYPE_2		0x0002
#घोषणा ICBTAG_STRATEGY_TYPE_3		0x0003
#घोषणा ICBTAG_STRATEGY_TYPE_4		0x0004

/* File Type (ECMA 167r3 4/14.6.6) */
#घोषणा ICBTAG_खाता_TYPE_UNDEF		0x00
#घोषणा ICBTAG_खाता_TYPE_USE		0x01
#घोषणा ICBTAG_खाता_TYPE_PIE		0x02
#घोषणा ICBTAG_खाता_TYPE_IE		0x03
#घोषणा ICBTAG_खाता_TYPE_सूचीECTORY	0x04
#घोषणा ICBTAG_खाता_TYPE_REGULAR	0x05
#घोषणा ICBTAG_खाता_TYPE_BLOCK		0x06
#घोषणा ICBTAG_खाता_TYPE_CHAR		0x07
#घोषणा ICBTAG_खाता_TYPE_EA		0x08
#घोषणा ICBTAG_खाता_TYPE_FIFO		0x09
#घोषणा ICBTAG_खाता_TYPE_SOCKET		0x0A
#घोषणा ICBTAG_खाता_TYPE_TE		0x0B
#घोषणा ICBTAG_खाता_TYPE_SYMLINK	0x0C
#घोषणा ICBTAG_खाता_TYPE_STREAMसूची	0x0D

/* Flags (ECMA 167r3 4/14.6.8) */
#घोषणा ICBTAG_FLAG_AD_MASK		0x0007
#घोषणा ICBTAG_FLAG_AD_SHORT		0x0000
#घोषणा ICBTAG_FLAG_AD_LONG		0x0001
#घोषणा ICBTAG_FLAG_AD_EXTENDED		0x0002
#घोषणा ICBTAG_FLAG_AD_IN_ICB		0x0003
#घोषणा ICBTAG_FLAG_SORTED		0x0008
#घोषणा ICBTAG_FLAG_NONRELOCATABLE	0x0010
#घोषणा ICBTAG_FLAG_ARCHIVE		0x0020
#घोषणा ICBTAG_FLAG_SETUID		0x0040
#घोषणा ICBTAG_FLAG_SETGID		0x0080
#घोषणा ICBTAG_FLAG_STICKY		0x0100
#घोषणा ICBTAG_FLAG_CONTIGUOUS		0x0200
#घोषणा ICBTAG_FLAG_SYSTEM		0x0400
#घोषणा ICBTAG_FLAG_TRANSFORMED		0x0800
#घोषणा ICBTAG_FLAG_MULTIVERSIONS	0x1000
#घोषणा ICBTAG_FLAG_STREAM		0x2000

/* Indirect Entry (ECMA 167r3 4/14.7) */
काष्ठा indirectEntry अणु
	काष्ठा tag	descTag;
	काष्ठा icbtag	icbTag;
	काष्ठा दीर्घ_ad	indirectICB;
पूर्ण __packed;

/* Terminal Entry (ECMA 167r3 4/14.8) */
काष्ठा terminalEntry अणु
	काष्ठा tag	descTag;
	काष्ठा icbtag	icbTag;
पूर्ण __packed;

/* File Entry (ECMA 167r3 4/14.9) */
काष्ठा fileEntry अणु
	काष्ठा tag		descTag;
	काष्ठा icbtag		icbTag;
	__le32			uid;
	__le32			gid;
	__le32			permissions;
	__le16			fileLinkCount;
	uपूर्णांक8_t			recordFormat;
	uपूर्णांक8_t			recordDisplayAttr;
	__le32			recordLength;
	__le64			inक्रमmationLength;
	__le64			logicalBlocksRecorded;
	काष्ठा बारtamp	accessTime;
	काष्ठा बारtamp	modअगरicationTime;
	काष्ठा बारtamp	attrTime;
	__le32			checkpoपूर्णांक;
	काष्ठा दीर्घ_ad		extendedAttrICB;
	काष्ठा regid		impIdent;
	__le64			uniqueID;
	__le32			lengthExtendedAttr;
	__le32			lengthAllocDescs;
	uपूर्णांक8_t			extendedAttr[0];
	uपूर्णांक8_t			allocDescs[0];
पूर्ण __packed;

/* Permissions (ECMA 167r3 4/14.9.5) */
#घोषणा FE_PERM_O_EXEC			0x00000001U
#घोषणा FE_PERM_O_WRITE			0x00000002U
#घोषणा FE_PERM_O_READ			0x00000004U
#घोषणा FE_PERM_O_CHATTR		0x00000008U
#घोषणा FE_PERM_O_DELETE		0x00000010U
#घोषणा FE_PERM_G_EXEC			0x00000020U
#घोषणा FE_PERM_G_WRITE			0x00000040U
#घोषणा FE_PERM_G_READ			0x00000080U
#घोषणा FE_PERM_G_CHATTR		0x00000100U
#घोषणा FE_PERM_G_DELETE		0x00000200U
#घोषणा FE_PERM_U_EXEC			0x00000400U
#घोषणा FE_PERM_U_WRITE			0x00000800U
#घोषणा FE_PERM_U_READ			0x00001000U
#घोषणा FE_PERM_U_CHATTR		0x00002000U
#घोषणा FE_PERM_U_DELETE		0x00004000U

/* Record Format (ECMA 167r3 4/14.9.7) */
#घोषणा FE_RECORD_FMT_UNDEF		0x00
#घोषणा FE_RECORD_FMT_FIXED_PAD		0x01
#घोषणा FE_RECORD_FMT_FIXED		0x02
#घोषणा FE_RECORD_FMT_VARIABLE8		0x03
#घोषणा FE_RECORD_FMT_VARIABLE16	0x04
#घोषणा FE_RECORD_FMT_VARIABLE16_MSB	0x05
#घोषणा FE_RECORD_FMT_VARIABLE32	0x06
#घोषणा FE_RECORD_FMT_PRINT		0x07
#घोषणा FE_RECORD_FMT_LF		0x08
#घोषणा FE_RECORD_FMT_CR		0x09
#घोषणा FE_RECORD_FMT_CRLF		0x0A
#घोषणा FE_RECORD_FMT_LFCR		0x0B

/* Record Display Attributes (ECMA 167r3 4/14.9.8) */
#घोषणा FE_RECORD_DISPLAY_ATTR_UNDEF	0x00
#घोषणा FE_RECORD_DISPLAY_ATTR_1	0x01
#घोषणा FE_RECORD_DISPLAY_ATTR_2	0x02
#घोषणा FE_RECORD_DISPLAY_ATTR_3	0x03

/* Extended Attribute Header Descriptor (ECMA 167r3 4/14.10.1) */
काष्ठा extendedAttrHeaderDesc अणु
	काष्ठा tag	descTag;
	__le32		impAttrLocation;
	__le32		appAttrLocation;
पूर्ण __packed;

/* Generic Format (ECMA 167r3 4/14.10.2) */
काष्ठा genericFormat अणु
	__le32		attrType;
	uपूर्णांक8_t		attrSubtype;
	uपूर्णांक8_t		reserved[3];
	__le32		attrLength;
	uपूर्णांक8_t		attrData[0];
पूर्ण __packed;

/* Character Set Inक्रमmation (ECMA 167r3 4/14.10.3) */
काष्ठा अक्षरSetInfo अणु
	__le32		attrType;
	uपूर्णांक8_t		attrSubtype;
	uपूर्णांक8_t		reserved[3];
	__le32		attrLength;
	__le32		escapeSeqLength;
	uपूर्णांक8_t		अक्षरSetType;
	uपूर्णांक8_t		escapeSeq[0];
पूर्ण __packed;

/* Alternate Permissions (ECMA 167r3 4/14.10.4) */
काष्ठा altPerms अणु
	__le32		attrType;
	uपूर्णांक8_t		attrSubtype;
	uपूर्णांक8_t		reserved[3];
	__le32		attrLength;
	__le16		ownerIdent;
	__le16		groupIdent;
	__le16		permission;
पूर्ण __packed;

/* File Times Extended Attribute (ECMA 167r3 4/14.10.5) */
काष्ठा fileTimesExtAttr अणु
	__le32		attrType;
	uपूर्णांक8_t		attrSubtype;
	uपूर्णांक8_t		reserved[3];
	__le32		attrLength;
	__le32		dataLength;
	__le32		fileTimeExistence;
	uपूर्णांक8_t		fileTimes;
पूर्ण __packed;

/* FileTimeExistence (ECMA 167r3 4/14.10.5.6) */
#घोषणा FTE_CREATION			0x00000001
#घोषणा FTE_DELETION			0x00000004
#घोषणा FTE_EFFECTIVE			0x00000008
#घोषणा FTE_BACKUP			0x00000002

/* Inक्रमmation Times Extended Attribute (ECMA 167r3 4/14.10.6) */
काष्ठा infoTimesExtAttr अणु
	__le32		attrType;
	uपूर्णांक8_t		attrSubtype;
	uपूर्णांक8_t		reserved[3];
	__le32		attrLength;
	__le32		dataLength;
	__le32		infoTimeExistence;
	uपूर्णांक8_t		infoTimes[0];
पूर्ण __packed;

/* Device Specअगरication (ECMA 167r3 4/14.10.7) */
काष्ठा deviceSpec अणु
	__le32		attrType;
	uपूर्णांक8_t		attrSubtype;
	uपूर्णांक8_t		reserved[3];
	__le32		attrLength;
	__le32		impUseLength;
	__le32		majorDeviceIdent;
	__le32		minorDeviceIdent;
	uपूर्णांक8_t		impUse[0];
पूर्ण __packed;

/* Implementation Use Extended Attr (ECMA 167r3 4/14.10.8) */
काष्ठा impUseExtAttr अणु
	__le32		attrType;
	uपूर्णांक8_t		attrSubtype;
	uपूर्णांक8_t		reserved[3];
	__le32		attrLength;
	__le32		impUseLength;
	काष्ठा regid	impIdent;
	uपूर्णांक8_t		impUse[0];
पूर्ण __packed;

/* Application Use Extended Attribute (ECMA 167r3 4/14.10.9) */
काष्ठा appUseExtAttr अणु
	__le32		attrType;
	uपूर्णांक8_t		attrSubtype;
	uपूर्णांक8_t		reserved[3];
	__le32		attrLength;
	__le32		appUseLength;
	काष्ठा regid	appIdent;
	uपूर्णांक8_t		appUse[0];
पूर्ण __packed;

#घोषणा EXTATTR_CHAR_SET		1
#घोषणा EXTATTR_ALT_PERMS		3
#घोषणा EXTATTR_खाता_TIMES		5
#घोषणा EXTATTR_INFO_TIMES		6
#घोषणा EXTATTR_DEV_SPEC		12
#घोषणा EXTATTR_IMP_USE			2048
#घोषणा EXTATTR_APP_USE			65536
#घोषणा EXTATTR_SUBTYPE			1

/* Unallocated Space Entry (ECMA 167r3 4/14.11) */
काष्ठा unallocSpaceEntry अणु
	काष्ठा tag	descTag;
	काष्ठा icbtag	icbTag;
	__le32		lengthAllocDescs;
	uपूर्णांक8_t		allocDescs[0];
पूर्ण __packed;

/* Space Biपंचांगap Descriptor (ECMA 167r3 4/14.12) */
काष्ठा spaceBiपंचांगapDesc अणु
	काष्ठा tag	descTag;
	__le32		numOfBits;
	__le32		numOfBytes;
	uपूर्णांक8_t		biपंचांगap[0];
पूर्ण __packed;

/* Partition Integrity Entry (ECMA 167r3 4/14.13) */
काष्ठा partitionIntegrityEntry अणु
	काष्ठा tag		descTag;
	काष्ठा icbtag		icbTag;
	काष्ठा बारtamp	recordingDateAndTime;
	uपूर्णांक8_t			पूर्णांकegrityType;
	uपूर्णांक8_t			reserved[175];
	काष्ठा regid		impIdent;
	uपूर्णांक8_t			impUse[256];
पूर्ण __packed;

/* Short Allocation Descriptor (ECMA 167r3 4/14.14.1) */

/* Extent Length (ECMA 167r3 4/14.14.1.1) */
#घोषणा EXT_LENGTH_MASK			0x3FFFFFFF
#घोषणा EXT_TYPE_MASK			0xC0000000
#घोषणा EXT_RECORDED_ALLOCATED		0x00000000
#घोषणा EXT_NOT_RECORDED_ALLOCATED	0x40000000
#घोषणा EXT_NOT_RECORDED_NOT_ALLOCATED	0x80000000
#घोषणा EXT_NEXT_EXTENT_ALLOCDESCS	0xC0000000

/* Long Allocation Descriptor (ECMA 167r3 4/14.14.2) */

/* Extended Allocation Descriptor (ECMA 167r3 4/14.14.3) */

/* Logical Volume Header Descriptor (ECMA 167r3 4/14.15) */
काष्ठा logicalVolHeaderDesc अणु
	__le64		uniqueID;
	uपूर्णांक8_t		reserved[24];
पूर्ण __packed;

/* Path Component (ECMA 167r3 4/14.16.1) */
काष्ठा pathComponent अणु
	uपूर्णांक8_t		componentType;
	uपूर्णांक8_t		lengthComponentIdent;
	__le16		componentFileVersionNum;
	dअक्षरs		componentIdent[0];
पूर्ण __packed;

/* File Entry (ECMA 167r3 4/14.17) */
काष्ठा extendedFileEntry अणु
	काष्ठा tag		descTag;
	काष्ठा icbtag		icbTag;
	__le32			uid;
	__le32			gid;
	__le32			permissions;
	__le16			fileLinkCount;
	uपूर्णांक8_t			recordFormat;
	uपूर्णांक8_t			recordDisplayAttr;
	__le32			recordLength;
	__le64			inक्रमmationLength;
	__le64			objectSize;
	__le64			logicalBlocksRecorded;
	काष्ठा बारtamp	accessTime;
	काष्ठा बारtamp	modअगरicationTime;
	काष्ठा बारtamp	createTime;
	काष्ठा बारtamp	attrTime;
	__le32			checkpoपूर्णांक;
	__le32			reserved;
	काष्ठा दीर्घ_ad		extendedAttrICB;
	काष्ठा दीर्घ_ad		streamDirectoryICB;
	काष्ठा regid		impIdent;
	__le64			uniqueID;
	__le32			lengthExtendedAttr;
	__le32			lengthAllocDescs;
	uपूर्णांक8_t			extendedAttr[0];
	uपूर्णांक8_t			allocDescs[0];
पूर्ण __packed;

#पूर्ण_अगर /* _ECMA_167_H */
