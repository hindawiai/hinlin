<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#अगर_अघोषित __INC_QOS_TYPE_H
#घोषणा __INC_QOS_TYPE_H

#घोषणा BIT0		    0x00000001
#घोषणा BIT1		    0x00000002
#घोषणा BIT2		    0x00000004
#घोषणा BIT3		    0x00000008
#घोषणा BIT4		    0x00000010
#घोषणा BIT5		    0x00000020
#घोषणा BIT6		    0x00000040
#घोषणा BIT7		    0x00000080
#घोषणा BIT8		    0x00000100
#घोषणा BIT9		    0x00000200
#घोषणा BIT10		   0x00000400
#घोषणा BIT11		   0x00000800
#घोषणा BIT12		   0x00001000
#घोषणा BIT13		   0x00002000
#घोषणा BIT14		   0x00004000
#घोषणा BIT15		   0x00008000
#घोषणा BIT16		   0x00010000
#घोषणा BIT17		   0x00020000
#घोषणा BIT18		   0x00040000
#घोषणा BIT19		   0x00080000
#घोषणा BIT20		   0x00100000
#घोषणा BIT21		   0x00200000
#घोषणा BIT22		   0x00400000
#घोषणा BIT23		   0x00800000
#घोषणा BIT24		   0x01000000
#घोषणा BIT25		   0x02000000
#घोषणा BIT26		   0x04000000
#घोषणा BIT27		   0x08000000
#घोषणा BIT28		   0x10000000
#घोषणा BIT29		   0x20000000
#घोषणा BIT30		   0x40000000
#घोषणा BIT31		   0x80000000

जोड़ qos_tsinfo अणु
	u8		अक्षरData[3];
	काष्ठा अणु
		u8		ucTrafficType:1;
		u8		ucTSID:4;
		u8		ucDirection:2;
		u8		ucAccessPolicy:2;
		u8		ucAggregation:1;
		u8		ucPSB:1;
		u8		ucUP:3;
		u8		ucTSInfoAckPolicy:2;
		u8		ucSchedule:1;
		u8		ucReserved:7;
	पूर्ण field;
पूर्ण;

जोड़ tspec_body अणु
	u8		अक्षरData[55];

	काष्ठा अणु
		जोड़ qos_tsinfo TSInfo;
		u16	NominalMSDUsize;
		u16	MaxMSDUsize;
		u32	MinServiceItv;
		u32	MaxServiceItv;
		u32	InactivityItv;
		u32	SuspenItv;
		u32	ServiceStartTime;
		u32	MinDataRate;
		u32	MeanDataRate;
		u32	PeakDataRate;
		u32	MaxBurstSize;
		u32	DelayBound;
		u32	MinPhyRate;
		u16	SurplusBandwidthAllowance;
		u16	MediumTime;
	पूर्ण f;
पूर्ण;

काष्ठा octet_string अणु
	u8 *Octet;
	u16 Length;
पूर्ण;

#घोषणा AC0_BE	0
#घोषणा AC1_BK	1
#घोषणा AC2_VI	2
#घोषणा AC3_VO	3
#घोषणा AC_MAX	4

क्रमागत direction_value अणु
	सूची_UP			= 0,
	सूची_DOWN		= 1,
	सूची_सूचीECT		= 2,
	सूची_BI_सूची		= 3,
पूर्ण;

क्रमागत acm_method अणु
	eAcmWay0_SwAndHw		= 0,
	eAcmWay1_HW			= 1,
	eAcmWay2_SW			= 2,
पूर्ण;


काष्ठा acm अणु
	u64		UsedTime;
	u64		MediumTime;
	u8		HwAcmCtl;
पूर्ण;

जोड़ qos_tclas अणु

	काष्ठा _TYPE_GENERAL अणु
		u8		Priority;
		u8		ClassअगरierType;
		u8		Mask;
	पूर्ण TYPE_GENERAL;

	काष्ठा _TYPE0_ETH अणु
		u8		Priority;
		u8		ClassअगरierType;
		u8		Mask;
		u8		SrcAddr[ETH_ALEN];
		u8		DstAddr[ETH_ALEN];
		u16		Type;
	पूर्ण TYPE0_ETH;

	काष्ठा _TYPE1_IPV4 अणु
		u8		Priority;
		u8		ClassअगरierType;
		u8		Mask;
		u8		Version;
		u8		SrcIP[4];
		u8		DstIP[4];
		u16		SrcPort;
		u16		DstPort;
		u8		DSCP;
		u8		Protocol;
		u8		Reserved;
	पूर्ण TYPE1_IPV4;

	काष्ठा _TYPE1_IPV6 अणु
		u8		Priority;
		u8		ClassअगरierType;
		u8		Mask;
		u8		Version;
		u8		SrcIP[16];
		u8		DstIP[16];
		u16		SrcPort;
		u16		DstPort;
		u8		FlowLabel[3];
	पूर्ण TYPE1_IPV6;

	काष्ठा _TYPE2_8021Q अणु
		u8		Priority;
		u8		ClassअगरierType;
		u8		Mask;
		u16		TagType;
	पूर्ण TYPE2_8021Q;
पूर्ण;

जोड़ aci_aअगरsn अणु
	u8	अक्षरData;

	काष्ठा अणु
		u8	AIFSN:4;
		u8	acm:1;
		u8	ACI:2;
		u8	Reserved:1;
	पूर्ण f;
पूर्ण;

#पूर्ण_अगर
