<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _AV7110_HW_H_
#घोषणा _AV7110_HW_H_

#समावेश "av7110.h"

/* DEBI transfer mode defs */

#घोषणा DEBINOSWAP 0x000e0000
#घोषणा DEBISWAB   0x001e0000
#घोषणा DEBISWAP   0x002e0000

#घोषणा ARM_WAIT_FREE  (HZ)
#घोषणा ARM_WAIT_SHAKE (HZ/5)
#घोषणा ARM_WAIT_OSD (HZ)


क्रमागत av7110_bootstate
अणु
	BOOTSTATE_BUFFER_EMPTY	= 0,
	BOOTSTATE_BUFFER_FULL	= 1,
	BOOTSTATE_AV7110_BOOT_COMPLETE	= 2
पूर्ण;

क्रमागत av7110_type_rec_play_क्रमmat
अणु	RP_None,
	AudioPES,
	AudioMp2,
	AudioPCM,
	VideoPES,
	AV_PES
पूर्ण;

क्रमागत av7110_osd_palette_type
अणु
	NoPalet =  0,	   /* No palette */
	Pal1Bit =  2,	   /* 2 colors क्रम 1 Bit Palette    */
	Pal2Bit =  4,	   /* 4 colors क्रम 2 bit palette    */
	Pal4Bit =  16,	   /* 16 colors क्रम 4 bit palette   */
	Pal8Bit =  256	   /* 256 colors क्रम 16 bit palette */
पूर्ण;

/* चयन defines */
#घोषणा SB_GPIO 3
#घोषणा SB_OFF	SAA7146_GPIO_OUTLO  /* SlowBlank off (TV-Mode) */
#घोषणा SB_ON	SAA7146_GPIO_INPUT  /* SlowBlank on  (AV-Mode) */
#घोषणा SB_WIDE SAA7146_GPIO_OUTHI  /* SlowBlank 6V  (16/9-Mode) (not implemented) */

#घोषणा FB_GPIO 1
#घोषणा FB_OFF	SAA7146_GPIO_LO     /* FastBlank off (CVBS-Mode) */
#घोषणा FB_ON	SAA7146_GPIO_OUTHI  /* FastBlank on  (RGB-Mode) */
#घोषणा FB_LOOP	SAA7146_GPIO_INPUT  /* FastBlank loop-through (PC graphics ???) */

क्रमागत av7110_video_output_mode
अणु
	NO_OUT	     = 0,		/* disable analog output */
	CVBS_RGB_OUT = 1,
	CVBS_YC_OUT  = 2,
	YC_OUT	     = 3
पूर्ण;

/* firmware पूर्णांकernal msg q status: */
#घोषणा GPMQFull	0x0001		/* Main Message Queue Full */
#घोषणा GPMQOver	0x0002		/* Main Message Queue Overflow */
#घोषणा HPQFull		0x0004		/* High Priority Msg Queue Full */
#घोषणा HPQOver		0x0008
#घोषणा OSDQFull	0x0010		/* OSD Queue Full */
#घोषणा OSDQOver	0x0020
#घोषणा GPMQBusy	0x0040		/* Queue not empty, FW >= 261d */
#घोषणा HPQBusy		0x0080
#घोषणा OSDQBusy	0x0100

/* hw section filter flags */
#घोषणा	SECTION_EIT		0x01
#घोषणा	SECTION_SINGLE		0x00
#घोषणा	SECTION_CYCLE		0x02
#घोषणा	SECTION_CONTINUOS	0x04
#घोषणा	SECTION_MODE		0x06
#घोषणा SECTION_IPMPE		0x0C	/* size up to 4k */
#घोषणा SECTION_HIGH_SPEED	0x1C	/* larger buffer */
#घोषणा DATA_PIPING_FLAG	0x20	/* क्रम Data Piping Filter */

#घोषणा	Pबफ_मानE_NONE 0x0000
#घोषणा	Pबफ_मानE_1P   0x0100
#घोषणा	Pबफ_मानE_2P   0x0200
#घोषणा	Pबफ_मानE_1K   0x0300
#घोषणा	Pबफ_मानE_2K   0x0400
#घोषणा	Pबफ_मानE_4K   0x0500
#घोषणा	Pबफ_मानE_8K   0x0600
#घोषणा Pबफ_मानE_16K  0x0700
#घोषणा Pबफ_मानE_32K  0x0800


/* firmware command codes */
क्रमागत av7110_osd_command अणु
	WCreate,
	WDestroy,
	WMoveD,
	WMoveA,
	WHide,
	WTop,
	DBox,
	DLine,
	DText,
	Set_Font,
	SetColor,
	SetBlend,
	SetWBlend,
	SetCBlend,
	SetNonBlend,
	LoadBmp,
	BlitBmp,
	ReleaseBmp,
	SetWTrans,
	SetWNoTrans,
	Set_Palette
पूर्ण;

क्रमागत av7110_pid_command अणु
	MultiPID,
	VideoPID,
	AudioPID,
	InitFilt,
	FiltError,
	NewVersion,
	CacheError,
	AddPIDFilter,
	DelPIDFilter,
	Scan,
	SetDescr,
	SetIR,
	FlushTSQueue
पूर्ण;

क्रमागत av7110_mpeg_command अणु
	SelAudChannels
पूर्ण;

क्रमागत av7110_audio_command अणु
	AudioDAC,
	CabADAC,
	ON22K,
	OFF22K,
	MainSwitch,
	ADSwitch,
	SendDiSEqC,
	SetRegister,
	SpdअगरSwitch
पूर्ण;

क्रमागत av7110_request_command अणु
	AudioState,
	AudioBuffState,
	VideoState1,
	VideoState2,
	VideoState3,
	CrashCounter,
	ReqVersion,
	ReqVCXO,
	ReqRegister,
	ReqSecFilterError,
	ReqSTC
पूर्ण;

क्रमागत av7110_encoder_command अणु
	SetVidMode,
	SetTestMode,
	LoadVidCode,
	SetMonitorType,
	SetPanScanType,
	SetFreezeMode,
	SetWSSConfig
पूर्ण;

क्रमागत av7110_rec_play_state अणु
	__Record,
	__Stop,
	__Play,
	__Pause,
	__Slow,
	__FF_IP,
	__Scan_I,
	__Continue
पूर्ण;

क्रमागत av7110_fw_cmd_misc अणु
	AV7110_FW_VIDEO_ZOOM = 1,
	AV7110_FW_VIDEO_COMMAND,
	AV7110_FW_AUDIO_COMMAND
पूर्ण;

क्रमागत av7110_command_type अणु
	COMTYPE_NOCOM,
	COMTYPE_PIDFILTER,
	COMTYPE_MPEGDECODER,
	COMTYPE_OSD,
	COMTYPE_BMP,
	COMTYPE_ENCODER,
	COMTYPE_AUDIODAC,
	COMTYPE_REQUEST,
	COMTYPE_SYSTEM,
	COMTYPE_REC_PLAY,
	COMTYPE_COMMON_IF,
	COMTYPE_PID_FILTER,
	COMTYPE_PES,
	COMTYPE_TS,
	COMTYPE_VIDEO,
	COMTYPE_AUDIO,
	COMTYPE_CI_LL,
	COMTYPE_MISC = 0x80
पूर्ण;

#घोषणा VID_NONE_PREF		0x00	/* No aspect ration processing preferred */
#घोषणा VID_PAN_SCAN_PREF	0x01	/* Pan and Scan Display preferred */
#घोषणा VID_VERT_COMP_PREF	0x02	/* Vertical compression display preferred */
#घोषणा VID_VC_AND_PS_PREF	0x03	/* PanScan and vertical Compression अगर allowed */
#घोषणा VID_CENTRE_CUT_PREF	0x05	/* PanScan with zero vector */

/* MPEG video decoder commands */
#घोषणा AV_VIDEO_CMD_STOP	0x000e
#घोषणा AV_VIDEO_CMD_PLAY	0x000d
#घोषणा AV_VIDEO_CMD_FREEZE	0x0102
#घोषणा AV_VIDEO_CMD_FFWD	0x0016
#घोषणा AV_VIDEO_CMD_SLOW	0x0022

/* MPEG audio decoder commands */
#घोषणा AUDIO_CMD_MUTE		0x0001
#घोषणा AUDIO_CMD_UNMUTE	0x0002
#घोषणा AUDIO_CMD_PCM16		0x0010
#घोषणा AUDIO_CMD_STEREO	0x0080
#घोषणा AUDIO_CMD_MONO_L	0x0100
#घोषणा AUDIO_CMD_MONO_R	0x0200
#घोषणा AUDIO_CMD_SYNC_OFF	0x000e
#घोषणा AUDIO_CMD_SYNC_ON	0x000f

/* firmware data पूर्णांकerface codes */
#घोषणा DATA_NONE		 0x00
#घोषणा DATA_FSECTION		 0x01
#घोषणा DATA_IPMPE		 0x02
#घोषणा DATA_MPEG_RECORD	 0x03
#घोषणा DATA_DEBUG_MESSAGE	 0x04
#घोषणा DATA_COMMON_INTERFACE	 0x05
#घोषणा DATA_MPEG_PLAY		 0x06
#घोषणा DATA_BMP_LOAD		 0x07
#घोषणा DATA_IRCOMMAND		 0x08
#घोषणा DATA_PIPING		 0x09
#घोषणा DATA_STREAMING		 0x0a
#घोषणा DATA_CI_GET		 0x0b
#घोषणा DATA_CI_PUT		 0x0c
#घोषणा DATA_MPEG_VIDEO_EVENT	 0x0d

#घोषणा DATA_PES_RECORD		 0x10
#घोषणा DATA_PES_PLAY		 0x11
#घोषणा DATA_TS_RECORD		 0x12
#घोषणा DATA_TS_PLAY		 0x13

/* ancient CI command codes, only two are actually still used
 * by the link level CI firmware */
#घोषणा CI_CMD_ERROR		 0x00
#घोषणा CI_CMD_ACK		 0x01
#घोषणा CI_CMD_SYSTEM_READY	 0x02
#घोषणा CI_CMD_KEYPRESS		 0x03
#घोषणा CI_CMD_ON_TUNED		 0x04
#घोषणा CI_CMD_ON_SWITCH_PROGRAM 0x05
#घोषणा CI_CMD_SECTION_ARRIVED	 0x06
#घोषणा CI_CMD_SECTION_TIMEOUT	 0x07
#घोषणा CI_CMD_TIME		 0x08
#घोषणा CI_CMD_ENTER_MENU	 0x09
#घोषणा CI_CMD_FAST_PSI		 0x0a
#घोषणा CI_CMD_GET_SLOT_INFO	 0x0b

#घोषणा CI_MSG_NONE		 0x00
#घोषणा CI_MSG_CI_INFO		 0x01
#घोषणा CI_MSG_MENU		 0x02
#घोषणा CI_MSG_LIST		 0x03
#घोषणा CI_MSG_TEXT		 0x04
#घोषणा CI_MSG_REQUEST_INPUT	 0x05
#घोषणा CI_MSG_INPUT_COMPLETE	 0x06
#घोषणा CI_MSG_LIST_MORE	 0x07
#घोषणा CI_MSG_MENU_MORE	 0x08
#घोषणा CI_MSG_CLOSE_MMI_IMM	 0x09
#घोषणा CI_MSG_SECTION_REQUEST	 0x0a
#घोषणा CI_MSG_CLOSE_FILTER	 0x0b
#घोषणा CI_PSI_COMPLETE		 0x0c
#घोषणा CI_MODULE_READY		 0x0d
#घोषणा CI_SWITCH_PRG_REPLY	 0x0e
#घोषणा CI_MSG_TEXT_MORE	 0x0f

#घोषणा CI_MSG_CA_PMT		 0xe0
#घोषणा CI_MSG_ERROR		 0xf0


/* base address of the dual ported RAM which serves as communication
 * area between PCI bus and av7110,
 * as seen by the DEBI bus of the saa7146 */
#घोषणा	DPRAM_BASE 0x4000

/* boot protocol area */
#घोषणा AV7110_BOOT_STATE	(DPRAM_BASE + 0x3F8)
#घोषणा AV7110_BOOT_SIZE	(DPRAM_BASE + 0x3FA)
#घोषणा AV7110_BOOT_BASE	(DPRAM_BASE + 0x3FC)
#घोषणा AV7110_BOOT_BLOCK	(DPRAM_BASE + 0x400)
#घोषणा AV7110_BOOT_MAX_SIZE	0xc00

/* firmware command protocol area */
#घोषणा IRQ_STATE	(DPRAM_BASE + 0x0F4)
#घोषणा IRQ_STATE_EXT	(DPRAM_BASE + 0x0F6)
#घोषणा MSGSTATE	(DPRAM_BASE + 0x0F8)
#घोषणा COMMAND		(DPRAM_BASE + 0x0FC)
#घोषणा COM_BUFF	(DPRAM_BASE + 0x100)
#घोषणा COM_BUFF_SIZE	0x20

/* various data buffers */
#घोषणा BUFF1_BASE	(DPRAM_BASE + 0x120)
#घोषणा BUFF1_SIZE	0xE0

#घोषणा DATA_BUFF0_BASE	(DPRAM_BASE + 0x200)
#घोषणा DATA_BUFF0_SIZE	0x0800

#घोषणा DATA_BUFF1_BASE	(DATA_BUFF0_BASE+DATA_BUFF0_SIZE)
#घोषणा DATA_BUFF1_SIZE	0x0800

#घोषणा DATA_BUFF2_BASE	(DATA_BUFF1_BASE+DATA_BUFF1_SIZE)
#घोषणा DATA_BUFF2_SIZE	0x0800

#घोषणा DATA_BUFF3_BASE (DATA_BUFF2_BASE+DATA_BUFF2_SIZE)
#घोषणा DATA_BUFF3_SIZE 0x0400

#घोषणा Reserved	(DPRAM_BASE + 0x1E00)
#घोषणा Reserved_SIZE	0x1C0


/* firmware status area */
#घोषणा STATUS_BASE	(DPRAM_BASE + 0x1FC0)
#घोषणा STATUS_LOOPS	(STATUS_BASE + 0x08)

#घोषणा STATUS_MPEG_WIDTH     (STATUS_BASE + 0x0C)
/* ((aspect_ratio & 0xf) << 12) | (height & 0xfff) */
#घोषणा STATUS_MPEG_HEIGHT_AR (STATUS_BASE + 0x0E)

/* firmware data protocol area */
#घोषणा RX_TYPE		(DPRAM_BASE + 0x1FE8)
#घोषणा RX_LEN		(DPRAM_BASE + 0x1FEA)
#घोषणा TX_TYPE		(DPRAM_BASE + 0x1FEC)
#घोषणा TX_LEN		(DPRAM_BASE + 0x1FEE)

#घोषणा RX_BUFF		(DPRAM_BASE + 0x1FF4)
#घोषणा TX_BUFF		(DPRAM_BASE + 0x1FF6)

#घोषणा HANDSHAKE_REG	(DPRAM_BASE + 0x1FF8)
#घोषणा COM_IF_LOCK	(DPRAM_BASE + 0x1FFA)

#घोषणा IRQ_RX		(DPRAM_BASE + 0x1FFC)
#घोषणा IRQ_TX		(DPRAM_BASE + 0x1FFE)

/* used by boot protocol to load firmware पूर्णांकo av7110 DRAM */
#घोषणा DRAM_START_CODE		0x2e000404
#घोषणा DRAM_MAX_CODE_SIZE	0x00100000

/* saa7146 gpio lines */
#घोषणा RESET_LINE		2
#घोषणा DEBI_DONE_LINE		1
#घोषणा ARM_IRQ_LINE		0



बाह्य पूर्णांक av7110_bootarm(काष्ठा av7110 *av7110);
बाह्य पूर्णांक av7110_firmversion(काष्ठा av7110 *av7110);
#घोषणा FW_CI_LL_SUPPORT(arm_app) ((arm_app) & 0x80000000)
#घोषणा FW_4M_SDRAM(arm_app)      ((arm_app) & 0x40000000)
#घोषणा FW_VERSION(arm_app)	  ((arm_app) & 0x0000FFFF)

बाह्य पूर्णांक av7110_रुको_msgstate(काष्ठा av7110 *av7110, u16 flags);
बाह्य पूर्णांक av7110_fw_cmd(काष्ठा av7110 *av7110, पूर्णांक type, पूर्णांक com, पूर्णांक num, ...);
बाह्य पूर्णांक av7110_fw_request(काष्ठा av7110 *av7110, u16 *request_buf,
			     पूर्णांक request_buf_len, u16 *reply_buf, पूर्णांक reply_buf_len);


/* DEBI (saa7146 data extension bus पूर्णांकerface) access */
बाह्य पूर्णांक av7110_debiग_लिखो(काष्ठा av7110 *av7110, u32 config,
			    पूर्णांक addr, u32 val, अचिन्हित पूर्णांक count);
बाह्य u32 av7110_debiपढ़ो(काष्ठा av7110 *av7110, u32 config,
			   पूर्णांक addr, अचिन्हित पूर्णांक count);


/* DEBI during पूर्णांकerrupt */
/* single word ग_लिखोs */
अटल अंतरभूत व्योम iwdebi(काष्ठा av7110 *av7110, u32 config, पूर्णांक addr, u32 val, अचिन्हित पूर्णांक count)
अणु
	av7110_debiग_लिखो(av7110, config, addr, val, count);
पूर्ण

/* buffer ग_लिखोs */
अटल अंतरभूत व्योम mwdebi(काष्ठा av7110 *av7110, u32 config, पूर्णांक addr,
			  स्थिर u8 *val, पूर्णांक count)
अणु
	स_नकल(av7110->debi_virt, val, count);
	av7110_debiग_लिखो(av7110, config, addr, 0, count);
पूर्ण

अटल अंतरभूत u32 irdebi(काष्ठा av7110 *av7110, u32 config, पूर्णांक addr, u32 val, अचिन्हित पूर्णांक count)
अणु
	u32 res;

	res=av7110_debiपढ़ो(av7110, config, addr, count);
	अगर (count<=4)
		स_नकल(av7110->debi_virt, (अक्षर *) &res, count);
	वापस res;
पूर्ण

/* DEBI outside पूर्णांकerrupts, only क्रम count <= 4! */
अटल अंतरभूत व्योम wdebi(काष्ठा av7110 *av7110, u32 config, पूर्णांक addr, u32 val, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&av7110->debilock, flags);
	av7110_debiग_लिखो(av7110, config, addr, val, count);
	spin_unlock_irqrestore(&av7110->debilock, flags);
पूर्ण

अटल अंतरभूत u32 rdebi(काष्ठा av7110 *av7110, u32 config, पूर्णांक addr, u32 val, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;
	u32 res;

	spin_lock_irqsave(&av7110->debilock, flags);
	res=av7110_debiपढ़ो(av7110, config, addr, count);
	spin_unlock_irqrestore(&av7110->debilock, flags);
	वापस res;
पूर्ण

/* handle mailbox रेजिस्टरs of the dual ported RAM */
अटल अंतरभूत व्योम ARM_ResetMailBox(काष्ठा av7110 *av7110)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&av7110->debilock, flags);
	av7110_debiपढ़ो(av7110, DEBINOSWAP, IRQ_RX, 2);
	av7110_debiग_लिखो(av7110, DEBINOSWAP, IRQ_RX, 0, 2);
	spin_unlock_irqrestore(&av7110->debilock, flags);
पूर्ण

अटल अंतरभूत व्योम ARM_ClearMailBox(काष्ठा av7110 *av7110)
अणु
	iwdebi(av7110, DEBINOSWAP, IRQ_RX, 0, 2);
पूर्ण

अटल अंतरभूत व्योम ARM_ClearIrq(काष्ठा av7110 *av7110)
अणु
	irdebi(av7110, DEBINOSWAP, IRQ_RX, 0, 2);
पूर्ण

/****************************************************************************
 * Firmware commands
 ****************************************************************************/

अटल अंतरभूत पूर्णांक SendDAC(काष्ठा av7110 *av7110, u8 addr, u8 data)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, AudioDAC, 2, addr, data);
पूर्ण

अटल अंतरभूत पूर्णांक av7710_set_video_mode(काष्ठा av7110 *av7110, पूर्णांक mode)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_ENCODER, SetVidMode, 1, mode);
पूर्ण

अटल अंतरभूत पूर्णांक vidcom(काष्ठा av7110 *av7110, u32 com, u32 arg)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_MISC, AV7110_FW_VIDEO_COMMAND, 4,
			     (com>>16), (com&0xffff),
			     (arg>>16), (arg&0xffff));
पूर्ण

अटल अंतरभूत पूर्णांक audcom(काष्ठा av7110 *av7110, u32 com)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_MISC, AV7110_FW_AUDIO_COMMAND, 2,
			     (com>>16), (com&0xffff));
पूर्ण

अटल अंतरभूत पूर्णांक Set22K(काष्ठा av7110 *av7110, पूर्णांक state)
अणु
	वापस av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, (state ? ON22K : OFF22K), 0);
पूर्ण


बाह्य पूर्णांक av7110_diseqc_send(काष्ठा av7110 *av7110, पूर्णांक len, u8 *msg, अचिन्हित दीर्घ burst);


#अगर_घोषित CONFIG_DVB_AV7110_OSD
बाह्य पूर्णांक av7110_osd_cmd(काष्ठा av7110 *av7110, osd_cmd_t *dc);
बाह्य पूर्णांक av7110_osd_capability(काष्ठा av7110 *av7110, osd_cap_t *cap);
#पूर्ण_अगर /* CONFIG_DVB_AV7110_OSD */



#पूर्ण_अगर /* _AV7110_HW_H_ */
