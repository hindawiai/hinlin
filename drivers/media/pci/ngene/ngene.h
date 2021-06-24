<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ngene.h: nGene PCIe bridge driver
 *
 * Copyright (C) 2005-2007 Micronas
 */

#अगर_अघोषित _NGENE_H_
#घोषणा _NGENE_H_

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <यंत्र/dma.h>
#समावेश <linux/scatterlist.h>

#समावेश <linux/dvb/frontend.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_ca_en50221.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_ringbuffer.h>
#समावेश <media/dvb_net.h>
#समावेश "cxd2099.h"

#घोषणा DEVICE_NAME "ngene"

#घोषणा NGENE_VID       0x18c3
#घोषणा NGENE_PID       0x0720

#अगर_अघोषित VIDEO_CAP_VC1
#घोषणा VIDEO_CAP_AVC   128
#घोषणा VIDEO_CAP_H264  128
#घोषणा VIDEO_CAP_VC1   256
#घोषणा VIDEO_CAP_WMV9  256
#घोषणा VIDEO_CAP_MPEG4 512
#पूर्ण_अगर

#घोषणा DEMOD_TYPE_STV090X	0
#घोषणा DEMOD_TYPE_DRXK		1
#घोषणा DEMOD_TYPE_STV0367	2

#घोषणा DEMOD_TYPE_XO2		32
#घोषणा DEMOD_TYPE_STV0910	(DEMOD_TYPE_XO2 + 0)
#घोषणा DEMOD_TYPE_SONY_CT2	(DEMOD_TYPE_XO2 + 1)
#घोषणा DEMOD_TYPE_SONY_ISDBT	(DEMOD_TYPE_XO2 + 2)
#घोषणा DEMOD_TYPE_SONY_C2T2	(DEMOD_TYPE_XO2 + 3)
#घोषणा DEMOD_TYPE_ST_ATSC	(DEMOD_TYPE_XO2 + 4)
#घोषणा DEMOD_TYPE_SONY_C2T2I	(DEMOD_TYPE_XO2 + 5)

#घोषणा NGENE_XO2_TYPE_NONE	0
#घोषणा NGENE_XO2_TYPE_DUOFLEX	1
#घोषणा NGENE_XO2_TYPE_CI	2

क्रमागत STREAM अणु
	STREAM_VIDEOIN1 = 0,        /* ITU656 or TS Input */
	STREAM_VIDEOIN2,
	STREAM_AUDIOIN1,            /* I2S or SPI Input */
	STREAM_AUDIOIN2,
	STREAM_AUDIOOUT,
	MAX_STREAM
पूर्ण;

क्रमागत SMODE_BITS अणु
	SMODE_AUDIO_SPDIF = 0x20,
	SMODE_AVSYNC = 0x10,
	SMODE_TRANSPORT_STREAM = 0x08,
	SMODE_AUDIO_CAPTURE = 0x04,
	SMODE_VBI_CAPTURE = 0x02,
	SMODE_VIDEO_CAPTURE = 0x01
पूर्ण;

क्रमागत STREAM_FLAG_BITS अणु
	SFLAG_CHROMA_FORMAT_2COMP  = 0x01, /* Chroma Format : 2's complement */
	SFLAG_CHROMA_FORMAT_OFFSET = 0x00, /* Chroma Format : Binary offset */
	SFLAG_ORDER_LUMA_CHROMA    = 0x02, /* Byte order: Y,Cb,Y,Cr */
	SFLAG_ORDER_CHROMA_LUMA    = 0x00, /* Byte order: Cb,Y,Cr,Y */
	SFLAG_COLORBAR             = 0x04, /* Select colorbar */
पूर्ण;

#घोषणा PROGRAM_ROM     0x0000
#घोषणा PROGRAM_SRAM    0x1000
#घोषणा PERIPHERALS0    0x8000
#घोषणा PERIPHERALS1    0x9000
#घोषणा SHARED_BUFFER   0xC000

#घोषणा HOST_TO_NGENE    (SHARED_BUFFER+0x0000)
#घोषणा NGENE_TO_HOST    (SHARED_BUFFER+0x0100)
#घोषणा NGENE_COMMAND    (SHARED_BUFFER+0x0200)
#घोषणा NGENE_COMMAND_HI (SHARED_BUFFER+0x0204)
#घोषणा NGENE_STATUS     (SHARED_BUFFER+0x0208)
#घोषणा NGENE_STATUS_HI  (SHARED_BUFFER+0x020C)
#घोषणा NGENE_EVENT      (SHARED_BUFFER+0x0210)
#घोषणा NGENE_EVENT_HI   (SHARED_BUFFER+0x0214)
#घोषणा VARIABLES        (SHARED_BUFFER+0x0210)

#घोषणा NGENE_INT_COUNTS       (SHARED_BUFFER+0x0260)
#घोषणा NGENE_INT_ENABLE       (SHARED_BUFFER+0x0264)
#घोषणा NGENE_VBI_LINE_COUNT   (SHARED_BUFFER+0x0268)

#घोषणा BUFFER_GP_XMIT  (SHARED_BUFFER+0x0800)
#घोषणा BUFFER_GP_RECV  (SHARED_BUFFER+0x0900)
#घोषणा EEPROM_AREA     (SHARED_BUFFER+0x0A00)

#घोषणा SG_V_IN_1       (SHARED_BUFFER+0x0A80)
#घोषणा SG_VBI_1        (SHARED_BUFFER+0x0B00)
#घोषणा SG_A_IN_1       (SHARED_BUFFER+0x0B80)
#घोषणा SG_V_IN_2       (SHARED_BUFFER+0x0C00)
#घोषणा SG_VBI_2        (SHARED_BUFFER+0x0C80)
#घोषणा SG_A_IN_2       (SHARED_BUFFER+0x0D00)
#घोषणा SG_V_OUT        (SHARED_BUFFER+0x0D80)
#घोषणा SG_A_OUT2       (SHARED_BUFFER+0x0E00)

#घोषणा DATA_A_IN_1     (SHARED_BUFFER+0x0E80)
#घोषणा DATA_A_IN_2     (SHARED_BUFFER+0x0F00)
#घोषणा DATA_A_OUT      (SHARED_BUFFER+0x0F80)
#घोषणा DATA_V_IN_1     (SHARED_BUFFER+0x1000)
#घोषणा DATA_V_IN_2     (SHARED_BUFFER+0x2000)
#घोषणा DATA_V_OUT      (SHARED_BUFFER+0x3000)

#घोषणा DATA_FIFO_AREA  (SHARED_BUFFER+0x1000)

#घोषणा TIMESTAMPS      0xA000
#घोषणा SCRATCHPAD      0xA080
#घोषणा FORCE_INT       0xA088
#घोषणा FORCE_NMI       0xA090
#घोषणा INT_STATUS      0xA0A0

#घोषणा DEV_VER         0x9004

#घोषणा FW_DEBUG_DEFAULT (PROGRAM_SRAM+0x00FF)

काष्ठा SG_ADDR अणु
	u64 start;
	u64 curr;
	u16 curr_ptr;
	u16 elements;
	u32 pad[3];
पूर्ण __attribute__ ((__packed__));

काष्ठा SHARED_MEMORY अणु
	/* C000 */
	u32 HostToNgene[64];

	/* C100 */
	u32 NgeneToHost[64];

	/* C200 */
	u64 NgeneCommand;
	u64 NgeneStatus;
	u64 NgeneEvent;

	/* C210 */
	u8 pad1[0xc260 - 0xc218];

	/* C260 */
	u32 IntCounts;
	u32 IntEnable;

	/* C268 */
	u8 pad2[0xd000 - 0xc268];

पूर्ण __attribute__ ((__packed__));

काष्ठा BUFFER_STREAM_RESULTS अणु
	u32 Clock;           /* Stream समय in 100ns units */
	u16 Reमुख्यingLines;  /* Reमुख्यing lines in this field.
				0 क्रम complete field */
	u8  FieldCount;      /* Video field number */
	u8  Flags;           /* Bit 7 = Done, Bit 6 = seen, Bit 5 = overflow,
				Bit 0 = FieldID */
	u16 BlockCount;      /* Audio block count (unused) */
	u8  Reserved[2];
	u32 DTOUpdate;
पूर्ण __attribute__ ((__packed__));

काष्ठा HW_SCATTER_GATHER_ELEMENT अणु
	u64 Address;
	u32 Length;
	u32 Reserved;
पूर्ण __attribute__ ((__packed__));

काष्ठा BUFFER_HEADER अणु
	u64    Next;
	काष्ठा BUFFER_STREAM_RESULTS SR;

	u32    Number_of_entries_1;
	u32    Reserved5;
	u64    Address_of_first_entry_1;

	u32    Number_of_entries_2;
	u32    Reserved7;
	u64    Address_of_first_entry_2;
पूर्ण __attribute__ ((__packed__));

काष्ठा EVENT_BUFFER अणु
	u32    TimeStamp;
	u8     GPIOStatus;
	u8     UARTStatus;
	u8     RXCharacter;
	u8     EventStatus;
	u32    Reserved[2];
पूर्ण __attribute__ ((__packed__));

/* Firmware commands. */

क्रमागत OPCODES अणु
	CMD_NOP = 0,
	CMD_FWLOAD_PREPARE  = 0x01,
	CMD_FWLOAD_FINISH   = 0x02,
	CMD_I2C_READ        = 0x03,
	CMD_I2C_WRITE       = 0x04,

	CMD_I2C_WRITE_NOSTOP = 0x05,
	CMD_I2C_CONTINUE_WRITE = 0x06,
	CMD_I2C_CONTINUE_WRITE_NOSTOP = 0x07,

	CMD_DEBUG_OUTPUT    = 0x09,

	CMD_CONTROL         = 0x10,
	CMD_CONFIGURE_BUFFER = 0x11,
	CMD_CONFIGURE_FREE_BUFFER = 0x12,

	CMD_SPI_READ        = 0x13,
	CMD_SPI_WRITE       = 0x14,

	CMD_MEM_READ        = 0x20,
	CMD_MEM_WRITE	    = 0x21,
	CMD_SFR_READ	    = 0x22,
	CMD_SFR_WRITE	    = 0x23,
	CMD_IRAM_READ	    = 0x24,
	CMD_IRAM_WRITE	    = 0x25,
	CMD_SET_GPIO_PIN    = 0x26,
	CMD_SET_GPIO_INT    = 0x27,
	CMD_CONFIGURE_UART  = 0x28,
	CMD_WRITE_UART      = 0x29,
	MAX_CMD
पूर्ण;

क्रमागत RESPONSES अणु
	OK = 0,
	ERROR = 1
पूर्ण;

काष्ठा FW_HEADER अणु
	u8 Opcode;
	u8 Length;
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_I2C_WRITE अणु
	काष्ठा FW_HEADER hdr;
	u8 Device;
	u8 Data[250];
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_I2C_CONTINUE_WRITE अणु
	काष्ठा FW_HEADER hdr;
	u8 Data[250];
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_I2C_READ अणु
	काष्ठा FW_HEADER hdr;
	u8 Device;
	u8 Data[252];    /* followed by two bytes of पढ़ो data count */
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_SPI_WRITE अणु
	काष्ठा FW_HEADER hdr;
	u8 ModeSelect;
	u8 Data[250];
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_SPI_READ अणु
	काष्ठा FW_HEADER hdr;
	u8 ModeSelect;
	u8 Data[252];    /* followed by two bytes of पढ़ो data count */
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_FWLOAD_PREPARE अणु
	काष्ठा FW_HEADER hdr;
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_FWLOAD_FINISH अणु
	काष्ठा FW_HEADER hdr;
	u16 Address;     /* address of final block */
	u16 Length;
पूर्ण __attribute__ ((__packed__));

/*
 * Meaning of FW_STREAM_CONTROL::Mode bits:
 *  Bit 7: Loopback PEXin to PEXout using TVOut channel
 *  Bit 6: AVLOOP
 *  Bit 5: Audio select; 0=I2S, 1=SPDIF
 *  Bit 4: AVSYNC
 *  Bit 3: Enable transport stream
 *  Bit 2: Enable audio capture
 *  Bit 1: Enable ITU-Video VBI capture
 *  Bit 0: Enable ITU-Video capture
 *
 * Meaning of FW_STREAM_CONTROL::Control bits (see UVI1_CTL)
 *  Bit 7: continuous capture
 *  Bit 6: capture one field
 *  Bit 5: capture one frame
 *  Bit 4: unused
 *  Bit 3: starting field; 0=odd, 1=even
 *  Bit 2: sample size; 0=8-bit, 1=10-bit
 *  Bit 1: data क्रमmat; 0=UYVY, 1=YUY2
 *  Bit 0: resets buffer poपूर्णांकers
*/

क्रमागत FSC_MODE_BITS अणु
	SMODE_LOOPBACK          = 0x80,
	SMODE_AVLOOP            = 0x40,
	_SMODE_AUDIO_SPDIF      = 0x20,
	_SMODE_AVSYNC           = 0x10,
	_SMODE_TRANSPORT_STREAM = 0x08,
	_SMODE_AUDIO_CAPTURE    = 0x04,
	_SMODE_VBI_CAPTURE      = 0x02,
	_SMODE_VIDEO_CAPTURE    = 0x01
पूर्ण;


/* Meaning of FW_STREAM_CONTROL::Stream bits:
 * Bit 3: Audio sample count:  0 = relative, 1 = असलolute
 * Bit 2: color bar select; 1=color bars, 0=CV3 decoder
 * Bits 1-0: stream select, UVI1, UVI2, TVOUT
 */

काष्ठा FW_STREAM_CONTROL अणु
	काष्ठा FW_HEADER hdr;
	u8     Stream;             /* Stream number (UVI1, UVI2, TVOUT) */
	u8     Control;            /* Value written to UVI1_CTL */
	u8     Mode;               /* Controls घड़ी source */
	u8     SetupDataLen;	   /* Length of setup data, MSB=1 ग_लिखो
				      backwards */
	u16    CaptureBlockCount;  /* Blocks (a 256 Bytes) to capture per buffer
				      क्रम TS and Audio */
	u64    Buffer_Address;	   /* Address of first buffer header */
	u16    BytesPerVideoLine;
	u16    MaxLinesPerField;
	u16    MinLinesPerField;
	u16    Reserved_1;
	u16    BytesPerVBILine;
	u16    MaxVBILinesPerField;
	u16    MinVBILinesPerField;
	u16    SetupDataAddr;      /* ngene relative address of setup data */
	u8     SetupData[32];      /* setup data */
पूर्ण __attribute__((__packed__));

#घोषणा AUDIO_BLOCK_SIZE    256
#घोषणा TS_BLOCK_SIZE       256

काष्ठा FW_MEM_READ अणु
	काष्ठा FW_HEADER hdr;
	u16   address;
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_MEM_WRITE अणु
	काष्ठा FW_HEADER hdr;
	u16   address;
	u8    data;
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_SFR_IRAM_READ अणु
	काष्ठा FW_HEADER hdr;
	u8    address;
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_SFR_IRAM_WRITE अणु
	काष्ठा FW_HEADER hdr;
	u8    address;
	u8    data;
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_SET_GPIO_PIN अणु
	काष्ठा FW_HEADER hdr;
	u8    select;
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_SET_GPIO_INT अणु
	काष्ठा FW_HEADER hdr;
	u8    select;
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_SET_DEBUGMODE अणु
	काष्ठा FW_HEADER hdr;
	u8   debug_flags;
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_CONFIGURE_BUFFERS अणु
	काष्ठा FW_HEADER hdr;
	u8   config;
पूर्ण __attribute__ ((__packed__));

क्रमागत _BUFFER_CONFIGS अणु
	/* 4k UVI1, 4k UVI2, 2k AUD1, 2k AUD2  (standard usage) */
	BUFFER_CONFIG_4422 = 0,
	/* 3k UVI1, 3k UVI2, 3k AUD1, 3k AUD2  (4x TS input usage) */
	BUFFER_CONFIG_3333 = 1,
	/* 8k UVI1, 0k UVI2, 2k AUD1, 2k I2SOut  (HDTV decoder usage) */
	BUFFER_CONFIG_8022 = 2,
	BUFFER_CONFIG_FW17 = 255, /* Use new FW 17 command */
पूर्ण;

काष्ठा FW_CONFIGURE_FREE_BUFFERS अणु
	काष्ठा FW_HEADER hdr;
	u8   UVI1_BufferLength;
	u8   UVI2_BufferLength;
	u8   TVO_BufferLength;
	u8   AUD1_BufferLength;
	u8   AUD2_BufferLength;
	u8   TVA_BufferLength;
पूर्ण __attribute__ ((__packed__));

काष्ठा FW_CONFIGURE_UART अणु
	काष्ठा FW_HEADER hdr;
	u8 UartControl;
पूर्ण __attribute__ ((__packed__));

क्रमागत _UART_CONFIG अणु
	_UART_BAUDRATE_19200 = 0,
	_UART_BAUDRATE_9600  = 1,
	_UART_BAUDRATE_4800  = 2,
	_UART_BAUDRATE_2400  = 3,
	_UART_RX_ENABLE      = 0x40,
	_UART_TX_ENABLE      = 0x80,
पूर्ण;

काष्ठा FW_WRITE_UART अणु
	काष्ठा FW_HEADER hdr;
	u8 Data[252];
पूर्ण __attribute__ ((__packed__));


काष्ठा ngene_command अणु
	u32 in_len;
	u32 out_len;
	जोड़ अणु
		u32                              raw[64];
		u8                               raw8[256];
		काष्ठा FW_HEADER                 hdr;
		काष्ठा FW_I2C_WRITE              I2CWrite;
		काष्ठा FW_I2C_CONTINUE_WRITE     I2CContinueWrite;
		काष्ठा FW_I2C_READ               I2CRead;
		काष्ठा FW_STREAM_CONTROL         StreamControl;
		काष्ठा FW_FWLOAD_PREPARE         FWLoadPrepare;
		काष्ठा FW_FWLOAD_FINISH          FWLoadFinish;
		काष्ठा FW_MEM_READ		 MemoryRead;
		काष्ठा FW_MEM_WRITE		 MemoryWrite;
		काष्ठा FW_SFR_IRAM_READ		 SfrIramRead;
		काष्ठा FW_SFR_IRAM_WRITE         SfrIramWrite;
		काष्ठा FW_SPI_WRITE              SPIWrite;
		काष्ठा FW_SPI_READ               SPIRead;
		काष्ठा FW_SET_GPIO_PIN           SetGpioPin;
		काष्ठा FW_SET_GPIO_INT           SetGpioInt;
		काष्ठा FW_SET_DEBUGMODE          SetDebugMode;
		काष्ठा FW_CONFIGURE_BUFFERS      ConfigureBuffers;
		काष्ठा FW_CONFIGURE_FREE_BUFFERS ConfigureFreeBuffers;
		काष्ठा FW_CONFIGURE_UART         ConfigureUart;
		काष्ठा FW_WRITE_UART             WriteUart;
	पूर्ण cmd;
पूर्ण __attribute__ ((__packed__));

#घोषणा NGENE_INTERFACE_VERSION 0x103
#घोषणा MAX_VIDEO_BUFFER_SIZE   (417792) /* 288*1440 rounded up to next page */
#घोषणा MAX_AUDIO_BUFFER_SIZE     (8192) /* Gives room क्रम about 23msec@48KHz */
#घोषणा MAX_VBI_BUFFER_SIZE      (28672) /* 1144*18 rounded up to next page */
#घोषणा MAX_TS_BUFFER_SIZE       (98304) /* 512*188 rounded up to next page */
#घोषणा MAX_HDTV_BUFFER_SIZE   (2080768) /* 541*1920*2 rounded up to next page
					    Max: (1920x1080i60) */

#घोषणा OVERFLOW_BUFFER_SIZE    (8192)

#घोषणा RING_SIZE_VIDEO     4
#घोषणा RING_SIZE_AUDIO     8
#घोषणा RING_SIZE_TS        8

#घोषणा NUM_SCATTER_GATHER_ENTRIES  8

#घोषणा MAX_DMA_LENGTH (((MAX_VIDEO_BUFFER_SIZE + MAX_VBI_BUFFER_SIZE) * \
			RING_SIZE_VIDEO * 2) + \
			(MAX_AUDIO_BUFFER_SIZE * RING_SIZE_AUDIO * 2) + \
			(MAX_TS_BUFFER_SIZE * RING_SIZE_TS * 4) + \
			(RING_SIZE_VIDEO * PAGE_SIZE * 2) + \
			(RING_SIZE_AUDIO * PAGE_SIZE * 2) + \
			(RING_SIZE_TS    * PAGE_SIZE * 4) + \
			 8 * PAGE_SIZE + OVERFLOW_BUFFER_SIZE + PAGE_SIZE)

#घोषणा EVENT_QUEUE_SIZE    16

/* Gathers the current state of a single channel. */

काष्ठा SBufferHeader अणु
	काष्ठा BUFFER_HEADER   ngeneBuffer; /* Physical descriptor */
	काष्ठा SBufferHeader  *Next;
	व्योम                  *Buffer1;
	काष्ठा HW_SCATTER_GATHER_ELEMENT *scList1;
	व्योम                  *Buffer2;
	काष्ठा HW_SCATTER_GATHER_ELEMENT *scList2;
पूर्ण;

/* Sizeof SBufferHeader aligned to next 64 Bit boundary (hw restriction) */
#घोषणा SIZखातापूर्ण_SBufferHeader ((माप(काष्ठा SBufferHeader) + 63) & ~63)

क्रमागत HWSTATE अणु
	HWSTATE_STOP,
	HWSTATE_STARTUP,
	HWSTATE_RUN,
	HWSTATE_PAUSE,
पूर्ण;

क्रमागत KSSTATE अणु
	KSSTATE_STOP,
	KSSTATE_ACQUIRE,
	KSSTATE_PAUSE,
	KSSTATE_RUN,
पूर्ण;

काष्ठा SRingBufferDescriptor अणु
	काष्ठा SBufferHeader *Head; /* Poपूर्णांकs to first buffer in ring buffer
				       काष्ठाure*/
	u64   PAHead;         /* Physical address of first buffer */
	u32   MemSize;        /* Memory size of allocated ring buffers
				 (needed क्रम मुक्तing) */
	u32   NumBuffers;     /* Number of buffers in the ring */
	u32   Buffer1Length;  /* Allocated length of Buffer 1 */
	u32   Buffer2Length;  /* Allocated length of Buffer 2 */
	व्योम *SCListMem;      /* Memory to hold scatter gather lists क्रम this
				 ring */
	u64   PASCListMem;    /* Physical address  .. */
	u32   SCListMemSize;  /* Size of this memory */
पूर्ण;

क्रमागत STREAMMODEFLAGS अणु
	StreamMode_NONE   = 0, /* Stream not used */
	StreamMode_ANALOG = 1, /* Analog: Stream 0,1 = Video, 2,3 = Audio */
	StreamMode_TSIN   = 2, /* Transport stream input (all) */
	StreamMode_HDTV   = 4, /* HDTV: Maximum 1920x1080p30,1920x1080i60
				  (only stream 0) */
	StreamMode_TSOUT  = 8, /* Transport stream output (only stream 3) */
पूर्ण;


क्रमागत BufferExchangeFlags अणु
	BEF_EVEN_FIELD   = 0x00000001,
	BEF_CONTINUATION = 0x00000002,
	BEF_MORE_DATA    = 0x00000004,
	BEF_OVERFLOW     = 0x00000008,
	DF_SWAP32        = 0x00010000,
पूर्ण;

प्रकार व्योम *(IBufferExchange)(व्योम *, व्योम *, u32, u32, u32);

काष्ठा MICI_STREAMINFO अणु
	IBufferExchange    *pExchange;
	IBufferExchange    *pExchangeVBI;     /* Secondary (VBI, ancillary) */
	u8  Stream;
	u8  Flags;
	u8  Mode;
	u8  Reserved;
	u16 nLinesVideo;
	u16 nBytesPerLineVideo;
	u16 nLinesVBI;
	u16 nBytesPerLineVBI;
	u32 CaptureLength;    /* Used क्रम audio and transport stream */
पूर्ण;

/****************************************************************************/
/* STRUCTS ******************************************************************/
/****************************************************************************/

/* sound hardware definition */
#घोषणा MIXER_ADDR_TVTUNER      0
#घोषणा MIXER_ADDR_LAST         0

काष्ठा ngene_channel;

/*काष्ठा sound chip*/

काष्ठा mychip अणु
	काष्ठा ngene_channel *chan;
	काष्ठा snd_card *card;
	काष्ठा pci_dev *pci;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm *pcm;
	अचिन्हित दीर्घ port;
	पूर्णांक irq;
	spinlock_t mixer_lock;
	spinlock_t lock;
	पूर्णांक mixer_volume[MIXER_ADDR_LAST + 1][2];
	पूर्णांक capture_source[MIXER_ADDR_LAST + 1][2];
पूर्ण;

#अगर_घोषित NGENE_V4L
काष्ठा ngene_overlay अणु
	पूर्णांक                    tvnorm;
	काष्ठा v4l2_rect       w;
	क्रमागत v4l2_field        field;
	काष्ठा v4l2_clip       *clips;
	पूर्णांक                    nclips;
	पूर्णांक                    setup_ok;
पूर्ण;

काष्ठा ngene_tvnorm अणु
	पूर्णांक   v4l2_id;
	अक्षर  *name;
	u16   swidth, sheight; /* scaled standard width, height */
	पूर्णांक   tuner_norm;
	पूर्णांक   soundstd;
पूर्ण;

काष्ठा ngene_vखोलो अणु
	काष्ठा ngene_channel      *ch;
	क्रमागत v4l2_priority         prio;
	पूर्णांक                        width;
	पूर्णांक                        height;
	पूर्णांक                        depth;
	काष्ठा videobuf_queue      vbuf_q;
	काष्ठा videobuf_queue      vbi;
	पूर्णांक                        fourcc;
	पूर्णांक                        picxcount;
	पूर्णांक                        resources;
	क्रमागत v4l2_buf_type         type;
	स्थिर काष्ठा ngene_क्रमmat *fmt;

	स्थिर काष्ठा ngene_क्रमmat *ovfmt;
	काष्ठा ngene_overlay       ov;
पूर्ण;
#पूर्ण_अगर

काष्ठा ngene_channel अणु
	काष्ठा device         device;
	काष्ठा i2c_adapter    i2c_adapter;
	काष्ठा i2c_client    *i2c_client[1];
	पूर्णांक                   i2c_client_fe;

	काष्ठा ngene         *dev;
	पूर्णांक                   number;
	पूर्णांक                   type;
	पूर्णांक                   mode;
	bool                  has_adapter;
	bool                  has_demux;
	पूर्णांक                   demod_type;
	पूर्णांक (*gate_ctrl)(काष्ठा dvb_frontend *, पूर्णांक);

	काष्ठा dvb_frontend  *fe;
	काष्ठा dvb_frontend  *fe2;
	काष्ठा dmxdev         dmxdev;
	काष्ठा dvb_demux      demux;
	काष्ठा dvb_net        dvbnet;
	काष्ठा dmx_frontend   hw_frontend;
	काष्ठा dmx_frontend   mem_frontend;
	पूर्णांक                   users;
	काष्ठा video_device  *v4l_dev;
	काष्ठा dvb_device    *ci_dev;
	काष्ठा tasklet_काष्ठा demux_tasklet;

	काष्ठा SBufferHeader *nextBuffer;
	क्रमागत KSSTATE          State;
	क्रमागत HWSTATE          HWState;
	u8                    Stream;
	u8                    Flags;
	u8                    Mode;
	IBufferExchange      *pBufferExchange;
	IBufferExchange      *pBufferExchange2;

	spinlock_t            state_lock;
	u16                   nLines;
	u16                   nBytesPerLine;
	u16                   nVBILines;
	u16                   nBytesPerVBILine;
	u16                   itumode;
	u32                   Capture1Length;
	u32                   Capture2Length;
	काष्ठा SRingBufferDescriptor RingBuffer;
	काष्ठा SRingBufferDescriptor TSRingBuffer;
	काष्ठा SRingBufferDescriptor TSIdleBuffer;

	u32                   DataFormatFlags;

	पूर्णांक                   AudioDTOUpdated;
	u32                   AudioDTOValue;

	पूर्णांक (*set_tone)(काष्ठा dvb_frontend *, क्रमागत fe_sec_tone_mode);
	u8 lnbh;

	/* stuff from analog driver */

	पूर्णांक minor;
	काष्ठा mychip        *mychip;
	काष्ठा snd_card      *soundcard;
	u8                   *evenbuffer;
	u8                    dma_on;
	पूर्णांक                   soundstreamon;
	पूर्णांक                   audiomute;
	पूर्णांक                   soundbuffisallocated;
	पूर्णांक                   sndbuffflag;
	पूर्णांक                   tun_rdy;
	पूर्णांक                   dec_rdy;
	पूर्णांक                   tun_dec_rdy;
	पूर्णांक                   lastbufferflag;

	काष्ठा ngene_tvnorm  *tvnorms;
	पूर्णांक                   tvnorm_num;
	पूर्णांक                   tvnorm;

#अगर_घोषित NGENE_V4L
	पूर्णांक                   videousers;
	काष्ठा v4l2_prio_state prio;
	काष्ठा ngene_vखोलो    init;
	पूर्णांक                   resources;
	काष्ठा v4l2_framebuffer fbuf;
	काष्ठा ngene_buffer  *screen;     /* overlay             */
	काष्ठा list_head      capture;    /* video capture queue */
	spinlock_t s_lock;
	काष्ठा semaphore reslock;
#पूर्ण_अगर

	पूर्णांक running;

	पूर्णांक tsin_offset;
	u8  tsin_buffer[188];
पूर्ण;


काष्ठा ngene_ci अणु
	काष्ठा device         device;
	काष्ठा i2c_adapter    i2c_adapter;

	काष्ठा ngene         *dev;
	काष्ठा dvb_ca_en50221 *en;
पूर्ण;

काष्ठा ngene;

प्रकार व्योम (rx_cb_t)(काष्ठा ngene *, u32, u8);
प्रकार व्योम (tx_cb_t)(काष्ठा ngene *, u32);

काष्ठा ngene अणु
	पूर्णांक                   nr;
	काष्ठा pci_dev       *pci_dev;
	अचिन्हित अक्षर __iomem *iomem;

	/*काष्ठा i2c_adapter  i2c_adapter;*/

	u32                   device_version;
	u32                   fw_पूर्णांकerface_version;
	u32                   icounts;
	bool                  msi_enabled;
	bool                  cmd_समयout_workaround;

	u8                   *CmdDoneByte;
	पूर्णांक                   BootFirmware;
	व्योम                 *OverflowBuffer;
	dma_addr_t            PAOverflowBuffer;
	व्योम                 *FWInterfaceBuffer;
	dma_addr_t            PAFWInterfaceBuffer;
	u8                   *ngenetohost;
	u8                   *hosttongene;

	काष्ठा EVENT_BUFFER   EventQueue[EVENT_QUEUE_SIZE];
	पूर्णांक                   EventQueueOverflowCount;
	पूर्णांक                   EventQueueOverflowFlag;
	काष्ठा tasklet_काष्ठा event_tasklet;
	काष्ठा EVENT_BUFFER  *EventBuffer;
	पूर्णांक                   EventQueueWriteIndex;
	पूर्णांक                   EventQueueReadIndex;

	रुको_queue_head_t     cmd_wq;
	पूर्णांक                   cmd_करोne;
	काष्ठा mutex          cmd_mutex;
	काष्ठा mutex          stream_mutex;
	काष्ठा semaphore      pll_mutex;
	काष्ठा mutex          i2c_चयन_mutex;
	पूर्णांक                   i2c_current_channel;
	पूर्णांक                   i2c_current_bus;
	spinlock_t            cmd_lock;

	काष्ठा dvb_adapter    adapter[MAX_STREAM];
	काष्ठा dvb_adapter    *first_adapter; /* "one_adapter" modprobe opt */
	काष्ठा ngene_channel  channel[MAX_STREAM];

	काष्ठा ngene_info    *card_info;

	tx_cb_t              *TxEventNotअगरy;
	rx_cb_t              *RxEventNotअगरy;
	पूर्णांक                   tx_busy;
	रुको_queue_head_t     tx_wq;
	रुको_queue_head_t     rx_wq;
#घोषणा UART_RBUF_LEN 4096
	u8                    uart_rbuf[UART_RBUF_LEN];
	पूर्णांक                   uart_rp, uart_wp;

#घोषणा TS_FILLER  0x6f

	u8                   *tsout_buf;
#घोषणा TSOUT_BUF_SIZE (512*188*8)
	काष्ठा dvb_ringbuffer tsout_rbuf;

	u8                   *tsin_buf;
#घोषणा TSIN_BUF_SIZE (512*188*8)
	काष्ठा dvb_ringbuffer tsin_rbuf;

	u8                   *ain_buf;
#घोषणा AIN_BUF_SIZE (128*1024)
	काष्ठा dvb_ringbuffer ain_rbuf;


	u8                   *vin_buf;
#घोषणा VIN_BUF_SIZE (4*1920*1080)
	काष्ठा dvb_ringbuffer vin_rbuf;

	अचिन्हित दीर्घ         exp_val;
	पूर्णांक prev_cmd;

	काष्ठा ngene_ci       ci;
पूर्ण;

काष्ठा ngene_info अणु
	पूर्णांक   type;
#घोषणा NGENE_APP        0
#घोषणा NGENE_TERRATEC   1
#घोषणा NGENE_SIDEWINDER 2
#घोषणा NGENE_RACER      3
#घोषणा NGENE_VIPER      4
#घोषणा NGENE_PYTHON     5
#घोषणा NGENE_VBOX_V1	 6
#घोषणा NGENE_VBOX_V2	 7

	पूर्णांक   fw_version;
	bool  msi_supported;
	अक्षर *name;

	पूर्णांक   io_type[MAX_STREAM];
#घोषणा NGENE_IO_NONE    0
#घोषणा NGENE_IO_TV      1
#घोषणा NGENE_IO_HDTV    2
#घोषणा NGENE_IO_TSIN    4
#घोषणा NGENE_IO_TSOUT   8
#घोषणा NGENE_IO_AIN     16

	व्योम *fe_config[4];
	व्योम *tuner_config[4];

	पूर्णांक (*demod_attach[4])(काष्ठा ngene_channel *);
	पूर्णांक (*tuner_attach[4])(काष्ठा ngene_channel *);

	u8    avf[4];
	u8    msp[4];
	u8    demoda[4];
	u8    lnb[4];
	पूर्णांक   i2c_access;
	u8    ntsc;
	u8    tsf[4];
	u8    i2s[4];

	पूर्णांक (*gate_ctrl)(काष्ठा dvb_frontend *, पूर्णांक);
	पूर्णांक (*चयन_ctrl)(काष्ठा ngene_channel *, पूर्णांक, पूर्णांक);
पूर्ण;

#अगर_घोषित NGENE_V4L
काष्ठा ngene_क्रमmat अणु
	अक्षर *name;
	पूर्णांक   fourcc;          /* video4linux 2      */
	पूर्णांक   btक्रमmat;        /* BT848_COLOR_FMT_*  */
	पूर्णांक   क्रमmat;
	पूर्णांक   btswap;          /* BT848_COLOR_CTL_*  */
	पूर्णांक   depth;           /* bit/pixel          */
	पूर्णांक   flags;
	पूर्णांक   hshअगरt, vshअगरt;  /* क्रम planar modes   */
	पूर्णांक   palette;
पूर्ण;

#घोषणा RESOURCE_OVERLAY       1
#घोषणा RESOURCE_VIDEO         2
#घोषणा RESOURCE_VBI           4

काष्ठा ngene_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा videobuf_buffer     vb;

	/* ngene specअगरic */
	स्थिर काष्ठा ngene_क्रमmat *fmt;
	पूर्णांक                        tvnorm;
	पूर्णांक                        btक्रमmat;
	पूर्णांक                        btswap;
पूर्ण;
#पूर्ण_अगर


/* Provided by ngene-core.c */
पूर्णांक ngene_probe(काष्ठा pci_dev *pci_dev, स्थिर काष्ठा pci_device_id *id);
व्योम ngene_हटाओ(काष्ठा pci_dev *pdev);
व्योम ngene_shutकरोwn(काष्ठा pci_dev *pdev);
पूर्णांक ngene_command(काष्ठा ngene *dev, काष्ठा ngene_command *com);
पूर्णांक ngene_command_gpio_set(काष्ठा ngene *dev, u8 select, u8 level);
व्योम set_transfer(काष्ठा ngene_channel *chan, पूर्णांक state);
व्योम FillTSBuffer(व्योम *Buffer, पूर्णांक Length, u32 Flags);

/* Provided by ngene-cards.c */
पूर्णांक ngene_port_has_cxd2099(काष्ठा i2c_adapter *i2c, u8 *type);

/* Provided by ngene-i2c.c */
पूर्णांक ngene_i2c_init(काष्ठा ngene *dev, पूर्णांक dev_nr);

/* Provided by ngene-dvb.c */
बाह्य काष्ठा dvb_device ngene_dvbdev_ci;
व्योम *tsout_exchange(व्योम *priv, व्योम *buf, u32 len, u32 घड़ी, u32 flags);
व्योम *tsin_exchange(व्योम *priv, व्योम *buf, u32 len, u32 घड़ी, u32 flags);
पूर्णांक ngene_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed);
पूर्णांक ngene_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed);
पूर्णांक my_dvb_dmx_ts_card_init(काष्ठा dvb_demux *dvbdemux, अक्षर *id,
			    पूर्णांक (*start_feed)(काष्ठा dvb_demux_feed *),
			    पूर्णांक (*stop_feed)(काष्ठा dvb_demux_feed *),
			    व्योम *priv);
पूर्णांक my_dvb_dmxdev_ts_card_init(काष्ठा dmxdev *dmxdev,
			       काष्ठा dvb_demux *dvbdemux,
			       काष्ठा dmx_frontend *hw_frontend,
			       काष्ठा dmx_frontend *mem_frontend,
			       काष्ठा dvb_adapter *dvb_adapter);

#पूर्ण_अगर

/*  LocalWords:  Endअगर
 */
