<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

/* TODO: Cleanup and लघुen the namespace */

/* Some काष्ठाures are passed directly to/from the firmware and
 * have strict alignment requirements. This is one of them.
 */
काष्ठा पंचांगComResHWDescr अणु
	u8	bLength;
	u8	bDescriptorType;
	u8	bDescriptorSubtype;
	u16	bcdSpecVersion;
	u32	dwClockFrequency;
	u32	dwClockUpdateRes;
	u8	bCapabilities;
	u32	dwDeviceRegistersLocation;
	u32	dwHostMemoryRegion;
	u32	dwHostMemoryRegionSize;
	u32	dwHostHibernatMemRegion;
	u32	dwHostHibernatMemRegionSize;
पूर्ण __attribute__((packed));

/* This is DWORD aligned on winकरोws but I can't find the right
 * gcc syntax to match the binary data from the device.
 * I've manually padded with Reserved[3] bytes to match the hardware,
 * but this could अवरोध अगर GCC decides to pack in a dअगरferent way.
 */
काष्ठा पंचांगComResInterfaceDescr अणु
	u8	bLength;
	u8	bDescriptorType;
	u8	bDescriptorSubtype;
	u8	bFlags;
	u8	bInterfaceType;
	u8	bInterfaceId;
	u8	bBaseInterface;
	u8	bInterruptId;
	u8	bDebugInterruptId;
	u8	BARLocation;
	u8	Reserved[3];
पूर्ण;

काष्ठा पंचांगComResBusDescr अणु
	u64	CommandRing;
	u64	ResponseRing;
	u32	CommandWrite;
	u32	CommandRead;
	u32	ResponseWrite;
	u32	ResponseRead;
पूर्ण;

क्रमागत पंचांगBusType अणु
	NONE		= 0,
	TYPE_BUS_PCI	= 1,
	TYPE_BUS_PCIe	= 2,
	TYPE_BUS_USB	= 3,
	TYPE_BUS_I2C	= 4
पूर्ण;

काष्ठा पंचांगComResBusInfo अणु
	क्रमागत पंचांगBusType Type;
	u16	m_wMaxReqSize;
	u8 __iomem *m_pdwSetRing;
	u32	m_dwSizeSetRing;
	u8 __iomem *m_pdwGetRing;
	u32	m_dwSizeGetRing;
	u32	m_dwSetWritePos;
	u32	m_dwSetReadPos;
	u32	m_dwGetWritePos;
	u32	m_dwGetReadPos;

	/* All access is रक्षित */
	काष्ठा mutex lock;

पूर्ण;

काष्ठा पंचांगComResInfo अणु
	u8	id;
	u8	flags;
	u16	size;
	u32	command;
	u16	controlselector;
	u8	seqno;
पूर्ण __attribute__((packed));

क्रमागत पंचांगComResCmd अणु
	SET_CUR  = 0x01,
	GET_CUR  = 0x81,
	GET_MIN  = 0x82,
	GET_MAX  = 0x83,
	GET_RES  = 0x84,
	GET_LEN  = 0x85,
	GET_INFO = 0x86,
	GET_DEF  = 0x87
पूर्ण;

काष्ठा cmd अणु
	u8 seqno;
	u32 inuse;
	u32 समयout;
	u32 संकेतled;
	काष्ठा mutex lock;
	रुको_queue_head_t रुको;
पूर्ण;

काष्ठा पंचांगDescriptor अणु
	u32	pathid;
	u32	size;
	व्योम	*descriptor;
पूर्ण;

काष्ठा पंचांगComResDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtype;
	u8	unitid;
पूर्ण __attribute__((packed));

काष्ठा पंचांगComResExtDevDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtype;
	u8	unitid;
	u32	devicetype;
	u16	deviceid;
	u32	numgpiopins;
	u8	numgpiogroups;
	u8	controlsize;
पूर्ण __attribute__((packed));

काष्ठा पंचांगComResGPIO अणु
	u32	pin;
	u8	state;
पूर्ण __attribute__((packed));

काष्ठा पंचांगComResPathDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtype;
	u8	pathid;
पूर्ण __attribute__((packed));

/* terminaltype */
क्रमागत पंचांगComResTermType अणु
	ITT_ANTENNA              = 0x0203,
	LINE_CONNECTOR           = 0x0603,
	SPDIF_CONNECTOR          = 0x0605,
	COMPOSITE_CONNECTOR      = 0x0401,
	SVIDEO_CONNECTOR         = 0x0402,
	COMPONENT_CONNECTOR      = 0x0403,
	STANDARD_DMA             = 0xF101
पूर्ण;

काष्ठा पंचांगComResAntTermDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtype;
	u8	terminalid;
	u16	terminaltype;
	u8	assocterminal;
	u8	iterminal;
	u8	controlsize;
पूर्ण __attribute__((packed));

काष्ठा पंचांगComResTunerDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtype;
	u8	unitid;
	u8	sourceid;
	u8	iunit;
	u32	tuningstandards;
	u8	controlsize;
	u32	controls;
पूर्ण __attribute__((packed));

क्रमागत पंचांगBufferFlag अणु
	/* the buffer करोes not contain any valid data */
	TM_BUFFER_FLAG_EMPTY,

	/* the buffer is filled with valid data */
	TM_BUFFER_FLAG_DONE,

	/* the buffer is the dummy buffer - TODO??? */
	TM_BUFFER_FLAG_DUMMY_BUFFER
पूर्ण;

काष्ठा पंचांगBuffer अणु
	u64		*pagetablevirt;
	u64		pagetablephys;
	u16		offset;
	u8		*context;
	u64		बारtamp;
	क्रमागत पंचांगBufferFlag BufferFlag;
	u32		lostbuffers;
	u32		validbuffers;
	u64		*dummypagevirt;
	u64		dummypagephys;
	u64		*addressvirt;
पूर्ण;

काष्ठा पंचांगHWStreamParameters अणु
	u32	bitspersample;
	u32	samplesperline;
	u32	numberoflines;
	u32	pitch;
	u32	linethreshold;
	u64	**pagetablelistvirt;
	u64	*pagetablelistphys;
	u32	numpagetables;
	u32	numpagetableentries;
पूर्ण;

काष्ठा पंचांगStreamParameters अणु
	काष्ठा पंचांगHWStreamParameters	HWStreamParameters;
	u64				qwDummyPageTablePhys;
	u64				*pDummyPageTableVirt;
पूर्ण;

काष्ठा पंचांगComResDMATermDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtyle;
	u8	unitid;
	u16	terminaltype;
	u8	assocterminal;
	u8	sourceid;
	u8	iterminal;
	u32	BARLocation;
	u8	flags;
	u8	पूर्णांकerruptid;
	u8	buffercount;
	u8	metadatasize;
	u8	numक्रमmats;
	u8	controlsize;
पूर्ण __attribute__((packed));

/*
 *
 * Description:
 *  This is the transport stream क्रमmat header.
 *
 * Settings:
 *  bLength                 - The size of this descriptor in bytes.
 *  bDescriptorType         - CS_INTERFACE.
 *  bDescriptorSubtype      - VS_FORMAT_MPEG2TS descriptor subtype.
 *  bFormatIndex            - A non-zero स्थिरant that uniquely identअगरies the
 *                            क्रमmat.
 *  bDataOffset             - Offset to TSP packet within MPEG-2 TS transport
 *                            stride, in bytes.
 *  bPacketLength           - Length of TSP packet, in bytes (typically 188).
 *  bStrideLength           - Length of MPEG-2 TS transport stride.
 *  guidStrideFormat        - A Globally Unique Identअगरier indicating the
 *                            क्रमmat of the stride data (अगर any). Set to zeros
 *                            अगर there is no Stride Data, or अगर the Stride
 *                            Data is to be ignored by the application.
 *
 */
काष्ठा पंचांगComResTSFormatDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtype;
	u8	bFormatIndex;
	u8	bDataOffset;
	u8	bPacketLength;
	u8	bStrideLength;
	u8	guidStrideFormat[16];
पूर्ण __attribute__((packed));

/* Encoder related काष्ठाures */

/* A/V Mux Selector */
काष्ठा पंचांगComResSelDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtype;
	u8	unitid;
	u8	nrinpins;
	u8	sourceid;
पूर्ण __attribute__((packed));

/* A/V Audio processor definitions */
काष्ठा पंचांगComResProcDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtype;
	u8	unitid;
	u8	sourceid;
	u16	wreserved;
	u8	controlsize;
पूर्ण __attribute__((packed));

/* Video bitrate control message */
#घोषणा EU_VIDEO_BIT_RATE_MODE_CONSTANT		(0)
#घोषणा EU_VIDEO_BIT_RATE_MODE_VARIABLE_AVERAGE (1)
#घोषणा EU_VIDEO_BIT_RATE_MODE_VARIABLE_PEAK	(2)
काष्ठा पंचांगComResEncVideoBitRate अणु
	u8	ucVideoBitRateMode;
	u32	dwVideoBitRate;
	u32	dwVideoBitRatePeak;
पूर्ण __attribute__((packed));

/* Video Encoder Aspect Ratio message */
काष्ठा पंचांगComResEncVideoInputAspectRatio अणु
	u8	width;
	u8	height;
पूर्ण __attribute__((packed));

/* Video Encoder GOP IBP message */
/* 1. IPPPPPPPPPPPPPP */
/* 2. IBPBPBPBPBPBPBP */
/* 3. IBBPBBPBBPBBP   */
#घोषणा SAA7164_ENCODER_DEFAULT_GOP_DIST (1)
#घोषणा SAA7164_ENCODER_DEFAULT_GOP_SIZE (15)
काष्ठा पंचांगComResEncVideoGopStructure अणु
	u8	ucGOPSize;	/* GOP Size 12, 15 */
	u8	ucRefFrameDist; /* Reference Frame Distance */
पूर्ण __attribute__((packed));

/* Encoder processor definition */
काष्ठा पंचांगComResEncoderDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtype;
	u8	unitid;
	u8	vsourceid;
	u8	asourceid;
	u8	iunit;
	u32	dwmControlCap;
	u32	dwmProfileCap;
	u32	dwmVidFormatCap;
	u8	bmVidBitrateCap;
	u16	wmVidResolutionsCap;
	u16	wmVidFrmRateCap;
	u32	dwmAudFormatCap;
	u8	bmAudBitrateCap;
पूर्ण __attribute__((packed));

/* Audio processor definition */
काष्ठा पंचांगComResAFeatureDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtype;
	u8	unitid;
	u8	sourceid;
	u8	controlsize;
पूर्ण __attribute__((packed));

/* Audio control messages */
काष्ठा पंचांगComResAudioDefaults अणु
	u8	ucDecoderLevel;
	u8	ucDecoderFM_Level;
	u8	ucMonoLevel;
	u8	ucNICAM_Level;
	u8	ucSAP_Level;
	u8	ucADC_Level;
पूर्ण __attribute__((packed));

/* Audio bitrate control message */
काष्ठा पंचांगComResEncAudioBitRate अणु
	u8	ucAudioBitRateMode;
	u32	dwAudioBitRate;
	u32	dwAudioBitRatePeak;
पूर्ण __attribute__((packed));

/* Tuner / AV Decoder messages */
काष्ठा पंचांगComResTunerStandard अणु
	u8	std;
	u32	country;
पूर्ण __attribute__((packed));

काष्ठा पंचांगComResTunerStandardAuto अणु
	u8	mode;
पूर्ण __attribute__((packed));

/* EEPROM definition क्रम PS stream types */
काष्ठा पंचांगComResPSFormatDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtype;
	u8	bFormatIndex;
	u16	wPacketLength;
	u16	wPackLength;
	u8	bPackDataType;
पूर्ण __attribute__((packed));

/* VBI control काष्ठाure */
काष्ठा पंचांगComResVBIFormatDescrHeader अणु
	u8	len;
	u8	type;
	u8	subtype; /* VS_FORMAT_VBI */
	u8	bFormatIndex;
	u32	VideoStandard; /* See KS_AnalogVideoStandard, NTSC = 1 */
	u8	StartLine; /* NTSC Start = 10 */
	u8	EndLine; /* NTSC = 21 */
	u8	FieldRate; /* 60 क्रम NTSC */
	u8	bNumLines; /* Unused - scheduled क्रम removal */
पूर्ण __attribute__((packed));

काष्ठा पंचांगComResProbeCommit अणु
	u16	bmHपूर्णांक;
	u8	bFormatIndex;
	u8	bFrameIndex;
पूर्ण __attribute__((packed));

काष्ठा पंचांगComResDebugSetLevel अणु
	u32	dwDebugLevel;
पूर्ण __attribute__((packed));

काष्ठा पंचांगComResDebugGetData अणु
	u32	dwResult;
	u8	ucDebugData[256];
पूर्ण __attribute__((packed));

काष्ठा पंचांगFwInfoStruct अणु
	u32	status;
	u32	mode;
	u32	devicespec;
	u32	deviceinst;
	u32	CPULoad;
	u32	Reमुख्यHeap;
	u32	CPUClock;
	u32	RAMSpeed;
पूर्ण __attribute__((packed));
