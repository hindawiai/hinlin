<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Driver क्रम the Korg 1212 IO PCI card
 *
 *	Copyright (c) 2001 Harolकरो Gamal <gamal@alternex.com.br>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>

// ----------------------------------------------------------------------------
// Debug Stuff
// ----------------------------------------------------------------------------
#घोषणा K1212_DEBUG_LEVEL		0
#अगर K1212_DEBUG_LEVEL > 0
#घोषणा K1212_DEBUG_PRINTK(fmt,args...)	prपूर्णांकk(KERN_DEBUG fmt,##args)
#अन्यथा
#घोषणा K1212_DEBUG_PRINTK(fmt,...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर
#अगर K1212_DEBUG_LEVEL > 1
#घोषणा K1212_DEBUG_PRINTK_VERBOSE(fmt,args...)	prपूर्णांकk(KERN_DEBUG fmt,##args)
#अन्यथा
#घोषणा K1212_DEBUG_PRINTK_VERBOSE(fmt,...)
#पूर्ण_अगर

// ----------------------------------------------------------------------------
// Record/Play Buffer Allocation Method. If K1212_LARGEALLOC is defined all 
// buffers are alocated as a large piece inside KorgSharedBuffer.
// ----------------------------------------------------------------------------
//#घोषणा K1212_LARGEALLOC		1

// ----------------------------------------------------------------------------
// Valid states of the Korg 1212 I/O card.
// ----------------------------------------------------------------------------
क्रमागत CardState अणु
   K1212_STATE_NONEXISTENT,		// there is no card here
   K1212_STATE_UNINITIALIZED,		// the card is aरुकोing DSP करोwnload
   K1212_STATE_DSP_IN_PROCESS,		// the card is currently करोwnloading its DSP code
   K1212_STATE_DSP_COMPLETE,		// the card has finished the DSP करोwnload
   K1212_STATE_READY,			// the card can be खोलोed by an application.  Any application
					//    requests prior to this state should fail.  Only an खोलो
					//    request can be made at this state.
   K1212_STATE_OPEN,			// an application has खोलोed the card
   K1212_STATE_SETUP,			// the card has been setup क्रम play
   K1212_STATE_PLAYING,			// the card is playing
   K1212_STATE_MONITOR,			// the card is in the monitor mode
   K1212_STATE_CALIBRATING,		// the card is currently calibrating
   K1212_STATE_ERRORSTOP,		// the card has stopped itself because of an error and we
					//    are in the process of cleaning things up.
   K1212_STATE_MAX_STATE		// state values of this and beyond are invalid
पूर्ण;

// ----------------------------------------------------------------------------
// The following क्रमागतeration defines the स्थिरants written to the card's
// host-to-card करोorbell to initiate a command.
// ----------------------------------------------------------------------------
क्रमागत korg1212_dbcnst अणु
   K1212_DB_RequestForData        = 0,    // sent by the card to request a buffer fill.
   K1212_DB_TriggerPlay           = 1,    // starts playback/record on the card.
   K1212_DB_SelectPlayMode        = 2,    // select monitor, playback setup, or stop.
   K1212_DB_ConfigureBufferMemory = 3,    // tells card where the host audio buffers are.
   K1212_DB_RequestAdatTimecode   = 4,    // asks the card क्रम the latest ADAT समयcode value.
   K1212_DB_SetClockSourceRate    = 5,    // sets the घड़ी source and rate क्रम the card.
   K1212_DB_ConfigureMiscMemory   = 6,    // tells card where other buffers are.
   K1212_DB_TriggerFromAdat       = 7,    // tells card to trigger from Adat at a specअगरic
                                          //    समयcode value.
   K1212_DB_DMAERROR              = 0x80, // DMA Error - the PCI bus is congestioned.
   K1212_DB_CARDSTOPPED           = 0x81, // Card has stopped by user request.
   K1212_DB_RebootCard            = 0xA0, // inकाष्ठाs the card to reboot.
   K1212_DB_BootFromDSPPage4      = 0xA4, // inकाष्ठाs the card to boot from the DSP microcode
                                          //    on page 4 (local page to card).
   K1212_DB_DSPDownloadDone       = 0xAE, // sent by the card to indicate the करोwnload has
                                          //    completed.
   K1212_DB_StartDSPDownload      = 0xAF  // tells the card to करोwnload its DSP firmware.
पूर्ण;


// ----------------------------------------------------------------------------
// The following क्रमागतeration defines वापस codes 
// to the Korg 1212 I/O driver.
// ----------------------------------------------------------------------------
क्रमागत snd_korg1212rc अणु
   K1212_CMDRET_Success         = 0,   // command was successfully placed
   K1212_CMDRET_DIOCFailure,           // the DeviceIoControl call failed
   K1212_CMDRET_PMFailure,             // the रक्षित mode call failed
   K1212_CMDRET_FailUnspecअगरied,       // unspecअगरied failure
   K1212_CMDRET_FailBadState,          // the specअगरied command can not be given in
                                       //    the card's current state. (or the wave device's
                                       //    state)
   K1212_CMDRET_CardUninitialized,     // the card is uninitialized and cannot be used
   K1212_CMDRET_BadIndex,              // an out of range card index was specअगरied
   K1212_CMDRET_BadHandle,             // an invalid card handle was specअगरied
   K1212_CMDRET_NoFillRoutine,         // a play request has been made beक्रमe a fill routine set
   K1212_CMDRET_FillRoutineInUse,      // can't set a new fill routine जबतक one is in use
   K1212_CMDRET_NoAckFromCard,         // the card never acknowledged a command
   K1212_CMDRET_BadParams,             // bad parameters were provided by the caller

   K1212_CMDRET_BadDevice,             // the specअगरied wave device was out of range
   K1212_CMDRET_BadFormat              // the specअगरied wave क्रमmat is unsupported
पूर्ण;

// ----------------------------------------------------------------------------
// The following क्रमागतeration defines the स्थिरants used to select the play
// mode क्रम the card in the SelectPlayMode command.
// ----------------------------------------------------------------------------
क्रमागत PlayModeSelector अणु
   K1212_MODE_SetupPlay  = 0x00000001,     // provides card with pre-play inक्रमmation
   K1212_MODE_MonitorOn  = 0x00000002,     // tells card to turn on monitor mode
   K1212_MODE_MonitorOff = 0x00000004,     // tells card to turn off monitor mode
   K1212_MODE_StopPlay   = 0x00000008      // stops playback on the card
पूर्ण;

// ----------------------------------------------------------------------------
// The following क्रमागतeration defines the स्थिरants used to select the monitor
// mode क्रम the card in the SetMonitorMode command.
// ----------------------------------------------------------------------------
क्रमागत MonitorModeSelector अणु
   K1212_MONMODE_Off  = 0,     // tells card to turn off monitor mode
   K1212_MONMODE_On            // tells card to turn on monitor mode
पूर्ण;

#घोषणा MAILBOX0_OFFSET      0x40	// location of mailbox 0 relative to base address
#घोषणा MAILBOX1_OFFSET      0x44	// location of mailbox 1 relative to base address
#घोषणा MAILBOX2_OFFSET      0x48	// location of mailbox 2 relative to base address
#घोषणा MAILBOX3_OFFSET      0x4c	// location of mailbox 3 relative to base address
#घोषणा OUT_DOORBELL_OFFSET  0x60	// location of PCI to local करोorbell
#घोषणा IN_DOORBELL_OFFSET   0x64	// location of local to PCI करोorbell
#घोषणा STATUS_REG_OFFSET    0x68	// location of पूर्णांकerrupt control/status रेजिस्टर
#घोषणा PCI_CONTROL_OFFSET   0x6c	// location of the EEPROM, PCI, User I/O, init control
					//    रेजिस्टर
#घोषणा SENS_CONTROL_OFFSET  0x6e	// location of the input sensitivity setting रेजिस्टर.
					//    this is the upper word of the PCI control reg.
#घोषणा DEV_VEND_ID_OFFSET   0x70	// location of the device and venकरोr ID रेजिस्टर

#घोषणा MAX_COMMAND_RETRIES  5         // maximum number of बार the driver will attempt
                                       //    to send a command beक्रमe giving up.
#घोषणा COMMAND_ACK_MASK     0x8000    // the MSB is set in the command acknowledgment from
                                        //    the card.
#घोषणा DOORBELL_VAL_MASK    0x00FF    // the करोorbell value is one byte

#घोषणा CARD_BOOT_DELAY_IN_MS  10
#घोषणा CARD_BOOT_TIMEOUT      10
#घोषणा DSP_BOOT_DELAY_IN_MS   200

#घोषणा kNumBuffers		8
#घोषणा k1212MaxCards		4
#घोषणा k1212NumWaveDevices	6
#घोषणा k16BitChannels		10
#घोषणा k32BitChannels		2
#घोषणा kAudioChannels		(k16BitChannels + k32BitChannels)
#घोषणा kPlayBufferFrames	1024

#घोषणा K1212_ANALOG_CHANNELS	2
#घोषणा K1212_SPDIF_CHANNELS	2
#घोषणा K1212_ADAT_CHANNELS	8
#घोषणा K1212_CHANNELS		(K1212_ADAT_CHANNELS + K1212_ANALOG_CHANNELS)
#घोषणा K1212_MIN_CHANNELS	1
#घोषणा K1212_MAX_CHANNELS	K1212_CHANNELS
#घोषणा K1212_FRAME_SIZE        (माप(काष्ठा KorgAudioFrame))
#घोषणा K1212_MAX_SAMPLES	(kPlayBufferFrames*kNumBuffers)
#घोषणा K1212_PERIODS		(kNumBuffers)
#घोषणा K1212_PERIOD_BYTES	(K1212_FRAME_SIZE*kPlayBufferFrames)
#घोषणा K1212_BUF_SIZE          (K1212_PERIOD_BYTES*kNumBuffers)
#घोषणा K1212_ANALOG_BUF_SIZE	(K1212_ANALOG_CHANNELS * 2 * kPlayBufferFrames * kNumBuffers)
#घोषणा K1212_SPDIF_BUF_SIZE	(K1212_SPDIF_CHANNELS * 3 * kPlayBufferFrames * kNumBuffers)
#घोषणा K1212_ADAT_BUF_SIZE	(K1212_ADAT_CHANNELS * 2 * kPlayBufferFrames * kNumBuffers)
#घोषणा K1212_MAX_BUF_SIZE	(K1212_ANALOG_BUF_SIZE + K1212_ADAT_BUF_SIZE)

#घोषणा k1212MinADCSens     0x00
#घोषणा k1212MaxADCSens     0x7f
#घोषणा k1212MaxVolume      0x7fff
#घोषणा k1212MaxWaveVolume  0xffff
#घोषणा k1212MinVolume      0x0000
#घोषणा k1212MaxVolInverted 0x8000

// -----------------------------------------------------------------
// the following bits are used क्रम controlling पूर्णांकerrupts in the
// पूर्णांकerrupt control/status reg
// -----------------------------------------------------------------
#घोषणा  PCI_INT_ENABLE_BIT               0x00000100
#घोषणा  PCI_DOORBELL_INT_ENABLE_BIT      0x00000200
#घोषणा  LOCAL_INT_ENABLE_BIT             0x00010000
#घोषणा  LOCAL_DOORBELL_INT_ENABLE_BIT    0x00020000
#घोषणा  LOCAL_DMA1_INT_ENABLE_BIT        0x00080000

// -----------------------------------------------------------------
// the following bits are defined क्रम the PCI command रेजिस्टर
// -----------------------------------------------------------------
#घोषणा  PCI_CMD_MEM_SPACE_ENABLE_BIT     0x0002
#घोषणा  PCI_CMD_IO_SPACE_ENABLE_BIT      0x0001
#घोषणा  PCI_CMD_BUS_MASTER_ENABLE_BIT    0x0004

// -----------------------------------------------------------------
// the following bits are defined क्रम the PCI status रेजिस्टर
// -----------------------------------------------------------------
#घोषणा  PCI_STAT_PARITY_ERROR_BIT        0x8000
#घोषणा  PCI_STAT_SYSTEM_ERROR_BIT        0x4000
#घोषणा  PCI_STAT_MASTER_ABORT_RCVD_BIT   0x2000
#घोषणा  PCI_STAT_TARGET_ABORT_RCVD_BIT   0x1000
#घोषणा  PCI_STAT_TARGET_ABORT_SENT_BIT   0x0800

// ------------------------------------------------------------------------
// the following स्थिरants are used in setting the 1212 I/O card's input
// sensitivity.
// ------------------------------------------------------------------------
#घोषणा  SET_SENS_LOCALINIT_BITPOS        15
#घोषणा  SET_SENS_DATA_BITPOS             10
#घोषणा  SET_SENS_CLOCK_BITPOS            8
#घोषणा  SET_SENS_LOADSHIFT_BITPOS        0

#घोषणा  SET_SENS_LEFTCHANID              0x00
#घोषणा  SET_SENS_RIGHTCHANID             0x01

#घोषणा  K1212SENSUPDATE_DELAY_IN_MS      50

// --------------------------------------------------------------------------
// WaitRTCTicks
//
//    This function रुकोs the specअगरied number of real समय घड़ी ticks.
//    According to the DDK, each tick is ~0.8 microseconds.
//    The defines following the function declaration can be used क्रम the
//    numTicksToWait parameter.
// --------------------------------------------------------------------------
#घोषणा ONE_RTC_TICK         1
#घोषणा SENSCLKPULSE_WIDTH   4
#घोषणा LOADSHIFT_DELAY      4
#घोषणा INTERCOMMAND_DELAY  40
#घोषणा STOPCARD_DELAY      300        // max # RTC ticks क्रम the card to stop once we ग_लिखो
                                       //    the command रेजिस्टर.  (could be up to 180 us)
#घोषणा COMMAND_ACK_DELAY   13         // number of RTC ticks to रुको क्रम an acknowledgement
                                       //    from the card after sending a command.

क्रमागत ClockSourceIndex अणु
   K1212_CLKIDX_AdatAt44_1K = 0,    // selects source as ADAT at 44.1 kHz
   K1212_CLKIDX_AdatAt48K,          // selects source as ADAT at 48 kHz
   K1212_CLKIDX_WordAt44_1K,        // selects source as S/PDIF at 44.1 kHz
   K1212_CLKIDX_WordAt48K,          // selects source as S/PDIF at 48 kHz
   K1212_CLKIDX_LocalAt44_1K,       // selects source as local घड़ी at 44.1 kHz
   K1212_CLKIDX_LocalAt48K,         // selects source as local घड़ी at 48 kHz
   K1212_CLKIDX_Invalid             // used to check validity of the index
पूर्ण;

क्रमागत ClockSourceType अणु
   K1212_CLKIDX_Adat = 0,    // selects source as ADAT
   K1212_CLKIDX_Word,        // selects source as S/PDIF
   K1212_CLKIDX_Local        // selects source as local घड़ी
पूर्ण;

काष्ठा KorgAudioFrame अणु
	u16 frameData16[k16BitChannels]; /* channels 0-9 use 16 bit samples */
	u32 frameData32[k32BitChannels]; /* channels 10-11 use 32 bits - only 20 are sent across S/PDIF */
	u32 समयCodeVal; /* holds the ADAT समयcode value */
पूर्ण;

काष्ठा KorgAudioBuffer अणु
	काष्ठा KorgAudioFrame  bufferData[kPlayBufferFrames];     /* buffer definition */
पूर्ण;

काष्ठा KorgSharedBuffer अणु
#अगर_घोषित K1212_LARGEALLOC
   काष्ठा KorgAudioBuffer   playDataBufs[kNumBuffers];
   काष्ठा KorgAudioBuffer   recordDataBufs[kNumBuffers];
#पूर्ण_अगर
   लघु             volumeData[kAudioChannels];
   u32               cardCommand;
   u16               routeData [kAudioChannels];
   u32               AdatTimeCode;                 // ADAT समयcode value
पूर्ण;

काष्ठा SensBits अणु
   जोड़ अणु
      काष्ठा अणु
         अचिन्हित पूर्णांक leftChanVal:8;
         अचिन्हित पूर्णांक leftChanId:8;
      पूर्ण v;
      u16  leftSensBits;
   पूर्ण l;
   जोड़ अणु
      काष्ठा अणु
         अचिन्हित पूर्णांक rightChanVal:8;
         अचिन्हित पूर्णांक rightChanId:8;
      पूर्ण v;
      u16  rightSensBits;
   पूर्ण r;
पूर्ण;

काष्ठा snd_korg1212 अणु
        काष्ठा snd_card *card;
        काष्ठा pci_dev *pci;
        काष्ठा snd_pcm *pcm;
        पूर्णांक irq;

        spinlock_t    lock;
	काष्ठा mutex खोलो_mutex;

	काष्ठा समयr_list समयr;	/* समयr callback क्रम checking ack of stop request */
	पूर्णांक stop_pending_cnt;		/* counter क्रम stop pending check */

        रुको_queue_head_t रुको;

        अचिन्हित दीर्घ iomem;
        अचिन्हित दीर्घ ioport;
	अचिन्हित दीर्घ iomem2;
        अचिन्हित दीर्घ irqcount;
        अचिन्हित दीर्घ inIRQ;
        व्योम __iomem *iobase;

	काष्ठा snd_dma_buffer dma_dsp;
        काष्ठा snd_dma_buffer dma_play;
        काष्ठा snd_dma_buffer dma_rec;
	काष्ठा snd_dma_buffer dma_shared;

	u32 DataBufsSize;

        काष्ठा KorgAudioBuffer  * playDataBufsPtr;
        काष्ठा KorgAudioBuffer  * recordDataBufsPtr;

	काष्ठा KorgSharedBuffer * sharedBufferPtr;

	u32 RecDataPhy;
	u32 PlayDataPhy;
	अचिन्हित दीर्घ sharedBufferPhy;
	u32 VolumeTablePhy;
	u32 RoutingTablePhy;
	u32 AdatTimeCodePhy;

        u32 __iomem * statusRegPtr;	     // address of the पूर्णांकerrupt status/control रेजिस्टर
        u32 __iomem * outDoorbellPtr;	     // address of the host->card करोorbell रेजिस्टर
        u32 __iomem * inDoorbellPtr;	     // address of the card->host करोorbell रेजिस्टर
        u32 __iomem * mailbox0Ptr;	     // address of mailbox 0 on the card
        u32 __iomem * mailbox1Ptr;	     // address of mailbox 1 on the card
        u32 __iomem * mailbox2Ptr;	     // address of mailbox 2 on the card
        u32 __iomem * mailbox3Ptr;	     // address of mailbox 3 on the card
        u32 __iomem * controlRegPtr;	     // address of the EEPROM, PCI, I/O, Init ctrl reg
        u16 __iomem * sensRegPtr;	     // address of the sensitivity setting रेजिस्टर
        u32 __iomem * idRegPtr;		     // address of the device and venकरोr ID रेजिस्टरs

        माप_प्रकार periodsize;
	पूर्णांक channels;
        पूर्णांक currentBuffer;

        काष्ठा snd_pcm_substream *playback_substream;
        काष्ठा snd_pcm_substream *capture_substream;

	pid_t capture_pid;
	pid_t playback_pid;

 	क्रमागत CardState cardState;
        पूर्णांक running;
        पूर्णांक idleMonitorOn;           // indicates whether the card is in idle monitor mode.
        u32 cmdRetryCount;           // tracks how many बार we have retried sending to the card.

        क्रमागत ClockSourceIndex clkSrcRate; // sample rate and घड़ी source

        क्रमागत ClockSourceType clkSource;   // घड़ी source
        पूर्णांक clkRate;                 // घड़ी rate

        पूर्णांक volumePhase[kAudioChannels];

        u16 leftADCInSens;           // ADC left channel input sensitivity
        u16 rightADCInSens;          // ADC right channel input sensitivity

	पूर्णांक खोलोcnt;		     // Open/Close count
	पूर्णांक setcnt;		     // SetupForPlay count
	पूर्णांक playcnt;		     // TriggerPlay count
	पूर्णांक errorcnt;		     // Error Count
	अचिन्हित दीर्घ totalerrorcnt; // Total Error Count

	पूर्णांक dsp_is_loaded;
	पूर्णांक dsp_stop_is_processed;

पूर्ण;

MODULE_DESCRIPTION("korg1212");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("korg/k1212.dsp");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;     /* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	   /* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE; /* Enable this card */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Korg 1212 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Korg 1212 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Korg 1212 soundcard.");
MODULE_AUTHOR("Haroldo Gamal <gamal@alternex.com.br>");

अटल स्थिर काष्ठा pci_device_id snd_korg1212_ids[] = अणु
	अणु
		.venकरोr	   = 0x10b5,
		.device	   = 0x906d,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_korg1212_ids);

अटल स्थिर अक्षर * स्थिर stateName[] = अणु
	"Non-existent",
	"Uninitialized",
	"DSP download in process",
	"DSP download complete",
	"Ready",
	"Open",
	"Setup for play",
	"Playing",
	"Monitor mode on",
	"Calibrating",
	"Invalid"
पूर्ण;

अटल स्थिर अक्षर * स्थिर घड़ीSourceTypeName[] = अणु "ADAT", "S/PDIF", "local" पूर्ण;

अटल स्थिर अक्षर * स्थिर घड़ीSourceName[] = अणु
	"ADAT at 44.1 kHz",
	"ADAT at 48 kHz",
	"S/PDIF at 44.1 kHz",
	"S/PDIF at 48 kHz",
	"local clock at 44.1 kHz",
	"local clock at 48 kHz"
पूर्ण;

अटल स्थिर अक्षर * स्थिर channelName[] = अणु
	"ADAT-1",
	"ADAT-2",
	"ADAT-3",
	"ADAT-4",
	"ADAT-5",
	"ADAT-6",
	"ADAT-7",
	"ADAT-8",
	"Analog-L",
	"Analog-R",
	"SPDIF-L",
	"SPDIF-R",
पूर्ण;

अटल स्थिर u16 ClockSourceSelector[] = अणु
	0x8000,   // selects source as ADAT at 44.1 kHz
	0x0000,   // selects source as ADAT at 48 kHz
	0x8001,   // selects source as S/PDIF at 44.1 kHz
	0x0001,   // selects source as S/PDIF at 48 kHz
	0x8002,   // selects source as local घड़ी at 44.1 kHz
	0x0002    // selects source as local घड़ी at 48 kHz
पूर्ण;

जोड़ swap_u32 अणु अचिन्हित अक्षर c[4]; u32 i; पूर्ण;

#अगर_घोषित SNDRV_BIG_ENDIAN
अटल u32 LowerWordSwap(u32 swappee)
#अन्यथा
अटल u32 UpperWordSwap(u32 swappee)
#पूर्ण_अगर
अणु
   जोड़ swap_u32 retVal, swapper;

   swapper.i = swappee;
   retVal.c[2] = swapper.c[3];
   retVal.c[3] = swapper.c[2];
   retVal.c[1] = swapper.c[1];
   retVal.c[0] = swapper.c[0];

   वापस retVal.i;
पूर्ण

#अगर_घोषित SNDRV_BIG_ENDIAN
अटल u32 UpperWordSwap(u32 swappee)
#अन्यथा
अटल u32 LowerWordSwap(u32 swappee)
#पूर्ण_अगर
अणु
   जोड़ swap_u32 retVal, swapper;

   swapper.i = swappee;
   retVal.c[2] = swapper.c[2];
   retVal.c[3] = swapper.c[3];
   retVal.c[1] = swapper.c[0];
   retVal.c[0] = swapper.c[1];

   वापस retVal.i;
पूर्ण

#घोषणा SetBitInWord(theWord,bitPosition)       (*theWord) |= (0x0001 << bitPosition)
#घोषणा SetBitInDWord(theWord,bitPosition)      (*theWord) |= (0x00000001 << bitPosition)
#घोषणा ClearBitInWord(theWord,bitPosition)     (*theWord) &= ~(0x0001 << bitPosition)
#घोषणा ClearBitInDWord(theWord,bitPosition)    (*theWord) &= ~(0x00000001 << bitPosition)

अटल पूर्णांक snd_korg1212_Send1212Command(काष्ठा snd_korg1212 *korg1212,
					क्रमागत korg1212_dbcnst करोorbellVal,
					u32 mailBox0Val, u32 mailBox1Val,
					u32 mailBox2Val, u32 mailBox3Val)
अणु
        u32 retryCount;
        u16 mailBox3Lo;
	पूर्णांक rc = K1212_CMDRET_Success;

        अगर (!korg1212->outDoorbellPtr) अणु
		K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: CardUninitialized\n");
                वापस K1212_CMDRET_CardUninitialized;
	पूर्ण

	K1212_DEBUG_PRINTK("K1212_DEBUG: Card <- 0x%08x 0x%08x [%s]\n",
			   करोorbellVal, mailBox0Val, stateName[korg1212->cardState]);
        क्रम (retryCount = 0; retryCount < MAX_COMMAND_RETRIES; retryCount++) अणु
		ग_लिखोl(mailBox3Val, korg1212->mailbox3Ptr);
                ग_लिखोl(mailBox2Val, korg1212->mailbox2Ptr);
                ग_लिखोl(mailBox1Val, korg1212->mailbox1Ptr);
                ग_लिखोl(mailBox0Val, korg1212->mailbox0Ptr);
                ग_लिखोl(करोorbellVal, korg1212->outDoorbellPtr);  // पूर्णांकerrupt the card

                // --------------------------------------------------------------
                // the reboot command will not give an acknowledgement.
                // --------------------------------------------------------------
                अगर ( करोorbellVal == K1212_DB_RebootCard ||
                	करोorbellVal == K1212_DB_BootFromDSPPage4 ||
                        करोorbellVal == K1212_DB_StartDSPDownload ) अणु
                        rc = K1212_CMDRET_Success;
                        अवरोध;
                पूर्ण

                // --------------------------------------------------------------
                // See अगर the card acknowledged the command.  Wait a bit, then
                // पढ़ो in the low word of mailbox3.  If the MSB is set and the
                // low byte is equal to the करोorbell value, then it ack'd.
                // --------------------------------------------------------------
                udelay(COMMAND_ACK_DELAY);
                mailBox3Lo = पढ़ोl(korg1212->mailbox3Ptr);
                अगर (mailBox3Lo & COMMAND_ACK_MASK) अणु
                	अगर ((mailBox3Lo & DOORBELL_VAL_MASK) == (करोorbellVal & DOORBELL_VAL_MASK)) अणु
				K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: Card <- Success\n");
                                rc = K1212_CMDRET_Success;
				अवरोध;
                        पूर्ण
                पूर्ण
	पूर्ण
        korg1212->cmdRetryCount += retryCount;

	अगर (retryCount >= MAX_COMMAND_RETRIES) अणु
		K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: Card <- NoAckFromCard\n");
        	rc = K1212_CMDRET_NoAckFromCard;
	पूर्ण

	वापस rc;
पूर्ण

/* spinlock alपढ़ोy held */
अटल व्योम snd_korg1212_SendStop(काष्ठा snd_korg1212 *korg1212)
अणु
	अगर (! korg1212->stop_pending_cnt) अणु
		korg1212->sharedBufferPtr->cardCommand = 0xffffffff;
		/* program the समयr */
		korg1212->stop_pending_cnt = HZ;
		mod_समयr(&korg1212->समयr, jअगरfies + 1);
	पूर्ण
पूर्ण

अटल व्योम snd_korg1212_SendStopAndWait(काष्ठा snd_korg1212 *korg1212)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&korg1212->lock, flags);
	korg1212->dsp_stop_is_processed = 0;
	snd_korg1212_SendStop(korg1212);
	spin_unlock_irqrestore(&korg1212->lock, flags);
	रुको_event_समयout(korg1212->रुको, korg1212->dsp_stop_is_processed, (HZ * 3) / 2);
पूर्ण

/* समयr callback क्रम checking the ack of stop request */
अटल व्योम snd_korg1212_समयr_func(काष्ठा समयr_list *t)
अणु
	काष्ठा snd_korg1212 *korg1212 = from_समयr(korg1212, t, समयr);
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&korg1212->lock, flags);
	अगर (korg1212->sharedBufferPtr->cardCommand == 0) अणु
		/* ack'ed */
		korg1212->stop_pending_cnt = 0;
		korg1212->dsp_stop_is_processed = 1;
		wake_up(&korg1212->रुको);
		K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: Stop ack'ed [%s]\n",
					   stateName[korg1212->cardState]);
	पूर्ण अन्यथा अणु
		अगर (--korg1212->stop_pending_cnt > 0) अणु
			/* reprogram समयr */
			mod_समयr(&korg1212->समयr, jअगरfies + 1);
		पूर्ण अन्यथा अणु
			snd_prपूर्णांकd("korg1212_timer_func timeout\n");
			korg1212->sharedBufferPtr->cardCommand = 0;
			korg1212->dsp_stop_is_processed = 1;
			wake_up(&korg1212->रुको);
			K1212_DEBUG_PRINTK("K1212_DEBUG: Stop timeout [%s]\n",
					   stateName[korg1212->cardState]);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&korg1212->lock, flags);
पूर्ण

अटल पूर्णांक snd_korg1212_TurnOnIdleMonitor(काष्ठा snd_korg1212 *korg1212)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

        udelay(INTERCOMMAND_DELAY);
	spin_lock_irqsave(&korg1212->lock, flags);
        korg1212->idleMonitorOn = 1;
        rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_SelectPlayMode,
					  K1212_MODE_MonitorOn, 0, 0, 0);
        spin_unlock_irqrestore(&korg1212->lock, flags);
	वापस rc;
पूर्ण

अटल व्योम snd_korg1212_TurnOffIdleMonitor(काष्ठा snd_korg1212 *korg1212)
अणु
        अगर (korg1212->idleMonitorOn) अणु
		snd_korg1212_SendStopAndWait(korg1212);
                korg1212->idleMonitorOn = 0;
        पूर्ण
पूर्ण

अटल अंतरभूत व्योम snd_korg1212_setCardState(काष्ठा snd_korg1212 * korg1212, क्रमागत CardState csState)
अणु
        korg1212->cardState = csState;
पूर्ण

अटल पूर्णांक snd_korg1212_OpenCard(काष्ठा snd_korg1212 * korg1212)
अणु
	K1212_DEBUG_PRINTK("K1212_DEBUG: OpenCard [%s] %d\n",
			   stateName[korg1212->cardState], korg1212->खोलोcnt);
	mutex_lock(&korg1212->खोलो_mutex);
        अगर (korg1212->खोलोcnt++ == 0) अणु
		snd_korg1212_TurnOffIdleMonitor(korg1212);
		snd_korg1212_setCardState(korg1212, K1212_STATE_OPEN);
	पूर्ण

	mutex_unlock(&korg1212->खोलो_mutex);
        वापस 1;
पूर्ण

अटल पूर्णांक snd_korg1212_CloseCard(काष्ठा snd_korg1212 * korg1212)
अणु
	K1212_DEBUG_PRINTK("K1212_DEBUG: CloseCard [%s] %d\n",
			   stateName[korg1212->cardState], korg1212->खोलोcnt);

	mutex_lock(&korg1212->खोलो_mutex);
	अगर (--(korg1212->खोलोcnt)) अणु
		mutex_unlock(&korg1212->खोलो_mutex);
		वापस 0;
	पूर्ण

        अगर (korg1212->cardState == K1212_STATE_SETUP) अणु
                पूर्णांक rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_SelectPlayMode,
                                K1212_MODE_StopPlay, 0, 0, 0);
		अगर (rc)
			K1212_DEBUG_PRINTK("K1212_DEBUG: CloseCard - RC = %d [%s]\n",
					   rc, stateName[korg1212->cardState]);
		अगर (rc != K1212_CMDRET_Success) अणु
			mutex_unlock(&korg1212->खोलो_mutex);
                        वापस 0;
		पूर्ण
        पूर्ण अन्यथा अगर (korg1212->cardState > K1212_STATE_SETUP) अणु
		snd_korg1212_SendStopAndWait(korg1212);
        पूर्ण

        अगर (korg1212->cardState > K1212_STATE_READY) अणु
		snd_korg1212_TurnOnIdleMonitor(korg1212);
                snd_korg1212_setCardState(korg1212, K1212_STATE_READY);
	पूर्ण

	mutex_unlock(&korg1212->खोलो_mutex);
        वापस 0;
पूर्ण

/* spinlock alपढ़ोy held */
अटल पूर्णांक snd_korg1212_SetupForPlay(काष्ठा snd_korg1212 * korg1212)
अणु
	पूर्णांक rc;

	K1212_DEBUG_PRINTK("K1212_DEBUG: SetupForPlay [%s] %d\n",
			   stateName[korg1212->cardState], korg1212->setcnt);

        अगर (korg1212->setcnt++)
		वापस 0;

        snd_korg1212_setCardState(korg1212, K1212_STATE_SETUP);
        rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_SelectPlayMode,
                                        K1212_MODE_SetupPlay, 0, 0, 0);
	अगर (rc)
		K1212_DEBUG_PRINTK("K1212_DEBUG: SetupForPlay - RC = %d [%s]\n",
				   rc, stateName[korg1212->cardState]);
        अगर (rc != K1212_CMDRET_Success) अणु
                वापस 1;
        पूर्ण
        वापस 0;
पूर्ण

/* spinlock alपढ़ोy held */
अटल पूर्णांक snd_korg1212_TriggerPlay(काष्ठा snd_korg1212 * korg1212)
अणु
	पूर्णांक rc;

	K1212_DEBUG_PRINTK("K1212_DEBUG: TriggerPlay [%s] %d\n",
			   stateName[korg1212->cardState], korg1212->playcnt);

        अगर (korg1212->playcnt++)
		वापस 0;

        snd_korg1212_setCardState(korg1212, K1212_STATE_PLAYING);
        rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_TriggerPlay, 0, 0, 0, 0);
	अगर (rc)
		K1212_DEBUG_PRINTK("K1212_DEBUG: TriggerPlay - RC = %d [%s]\n",
				   rc, stateName[korg1212->cardState]);
        अगर (rc != K1212_CMDRET_Success) अणु
                वापस 1;
        पूर्ण
        वापस 0;
पूर्ण

/* spinlock alपढ़ोy held */
अटल पूर्णांक snd_korg1212_StopPlay(काष्ठा snd_korg1212 * korg1212)
अणु
	K1212_DEBUG_PRINTK("K1212_DEBUG: StopPlay [%s] %d\n",
			   stateName[korg1212->cardState], korg1212->playcnt);

        अगर (--(korg1212->playcnt)) 
		वापस 0;

	korg1212->setcnt = 0;

        अगर (korg1212->cardState != K1212_STATE_ERRORSTOP)
		snd_korg1212_SendStop(korg1212);

	snd_korg1212_setCardState(korg1212, K1212_STATE_OPEN);
        वापस 0;
पूर्ण

अटल व्योम snd_korg1212_EnableCardInterrupts(काष्ठा snd_korg1212 * korg1212)
अणु
	ग_लिखोl(PCI_INT_ENABLE_BIT            |
	       PCI_DOORBELL_INT_ENABLE_BIT   |
	       LOCAL_INT_ENABLE_BIT          |
	       LOCAL_DOORBELL_INT_ENABLE_BIT |
	       LOCAL_DMA1_INT_ENABLE_BIT,
	       korg1212->statusRegPtr);
पूर्ण

#अगर 0 /* not used */

अटल पूर्णांक snd_korg1212_SetMonitorMode(काष्ठा snd_korg1212 *korg1212,
				       क्रमागत MonitorModeSelector mode)
अणु
	K1212_DEBUG_PRINTK("K1212_DEBUG: SetMonitorMode [%s]\n",
			   stateName[korg1212->cardState]);

        चयन (mode) अणु
	हाल K1212_MONMODE_Off:
		अगर (korg1212->cardState != K1212_STATE_MONITOR)
			वापस 0;
		अन्यथा अणु
			snd_korg1212_SendStopAndWait(korg1212);
			snd_korg1212_setCardState(korg1212, K1212_STATE_OPEN);
		पूर्ण
		अवरोध;

	हाल K1212_MONMODE_On:
		अगर (korg1212->cardState != K1212_STATE_OPEN)
			वापस 0;
		अन्यथा अणु
			पूर्णांक rc;
			snd_korg1212_setCardState(korg1212, K1212_STATE_MONITOR);
			rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_SelectPlayMode,
							  K1212_MODE_MonitorOn, 0, 0, 0);
			अगर (rc != K1212_CMDRET_Success)
				वापस 0;
		पूर्ण
		अवरोध;

	शेष:
		वापस 0;
        पूर्ण

        वापस 1;
पूर्ण

#पूर्ण_अगर /* not used */

अटल अंतरभूत पूर्णांक snd_korg1212_use_is_exclusive(काष्ठा snd_korg1212 *korg1212)
अणु
	अगर (korg1212->playback_pid != korg1212->capture_pid &&
	    korg1212->playback_pid >= 0 && korg1212->capture_pid >= 0)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक snd_korg1212_SetRate(काष्ठा snd_korg1212 *korg1212, पूर्णांक rate)
अणु
	अटल स्थिर क्रमागत ClockSourceIndex s44[] = अणु
		K1212_CLKIDX_AdatAt44_1K,
		K1212_CLKIDX_WordAt44_1K,
		K1212_CLKIDX_LocalAt44_1K
	पूर्ण;
	अटल स्थिर क्रमागत ClockSourceIndex s48[] = अणु
		K1212_CLKIDX_AdatAt48K,
		K1212_CLKIDX_WordAt48K,
		K1212_CLKIDX_LocalAt48K
	पूर्ण;
        पूर्णांक parm, rc;

	अगर (!snd_korg1212_use_is_exclusive (korg1212))
		वापस -EBUSY;

	चयन (rate) अणु
	हाल 44100:
		parm = s44[korg1212->clkSource];
		अवरोध;

	हाल 48000:
		parm = s48[korg1212->clkSource];
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

        korg1212->clkSrcRate = parm;
        korg1212->clkRate = rate;

	udelay(INTERCOMMAND_DELAY);
	rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_SetClockSourceRate,
					  ClockSourceSelector[korg1212->clkSrcRate],
					  0, 0, 0);
	अगर (rc)
		K1212_DEBUG_PRINTK("K1212_DEBUG: Set Clock Source Selector - RC = %d [%s]\n",
				   rc, stateName[korg1212->cardState]);

        वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_SetClockSource(काष्ठा snd_korg1212 *korg1212, पूर्णांक source)
अणु

	अगर (source < 0 || source > 2)
		वापस -EINVAL;

        korg1212->clkSource = source;

        snd_korg1212_SetRate(korg1212, korg1212->clkRate);

        वापस 0;
पूर्ण

अटल व्योम snd_korg1212_DisableCardInterrupts(काष्ठा snd_korg1212 *korg1212)
अणु
	ग_लिखोl(0, korg1212->statusRegPtr);
पूर्ण

अटल पूर्णांक snd_korg1212_WriteADCSensitivity(काष्ठा snd_korg1212 *korg1212)
अणु
        काष्ठा SensBits  sensVals;
        पूर्णांक       bitPosition;
        पूर्णांक       channel;
        पूर्णांक       clkIs48K;
        पूर्णांक       monModeSet;
        u16       controlValue;    // this keeps the current value to be written to
                                   //  the card's eeprom control रेजिस्टर.
        u16       count;
	अचिन्हित दीर्घ flags;

	K1212_DEBUG_PRINTK("K1212_DEBUG: WriteADCSensivity [%s]\n",
			   stateName[korg1212->cardState]);

        // ----------------------------------------------------------------------------
        // initialize things.  The local init bit is always set when writing to the
        // card's control रेजिस्टर.
        // ----------------------------------------------------------------------------
        controlValue = 0;
        SetBitInWord(&controlValue, SET_SENS_LOCALINIT_BITPOS);    // init the control value

        // ----------------------------------------------------------------------------
        // make sure the card is not in monitor mode when we करो this update.
        // ----------------------------------------------------------------------------
        अगर (korg1212->cardState == K1212_STATE_MONITOR || korg1212->idleMonitorOn) अणु
                monModeSet = 1;
		snd_korg1212_SendStopAndWait(korg1212);
        पूर्ण अन्यथा
                monModeSet = 0;

	spin_lock_irqsave(&korg1212->lock, flags);

        // ----------------------------------------------------------------------------
        // we are about to send new values to the card, so clear the new values queued
        // flag.  Also, clear out mailbox 3, so we करोn't lockup.
        // ----------------------------------------------------------------------------
        ग_लिखोl(0, korg1212->mailbox3Ptr);
        udelay(LOADSHIFT_DELAY);

        // ----------------------------------------------------------------------------
        // determine whether we are running a 48K or 44.1K घड़ी.  This info is used
        // later when setting the SPDIF FF after the volume has been shअगरted in.
        // ----------------------------------------------------------------------------
        चयन (korg1212->clkSrcRate) अणु
                हाल K1212_CLKIDX_AdatAt44_1K:
                हाल K1212_CLKIDX_WordAt44_1K:
                हाल K1212_CLKIDX_LocalAt44_1K:
                        clkIs48K = 0;
                        अवरोध;

                हाल K1212_CLKIDX_WordAt48K:
                हाल K1212_CLKIDX_AdatAt48K:
                हाल K1212_CLKIDX_LocalAt48K:
                शेष:
                        clkIs48K = 1;
                        अवरोध;
        पूर्ण

        // ----------------------------------------------------------------------------
        // start the update.  Setup the bit काष्ठाure and then shअगरt the bits.
        // ----------------------------------------------------------------------------
        sensVals.l.v.leftChanId   = SET_SENS_LEFTCHANID;
        sensVals.r.v.rightChanId  = SET_SENS_RIGHTCHANID;
        sensVals.l.v.leftChanVal  = korg1212->leftADCInSens;
        sensVals.r.v.rightChanVal = korg1212->rightADCInSens;

        // ----------------------------------------------------------------------------
        // now start shअगरting the bits in.  Start with the left channel then the right.
        // ----------------------------------------------------------------------------
        क्रम (channel = 0; channel < 2; channel++) अणु

                // ----------------------------------------------------------------------------
                // Bring the load/shअगरt line low, then रुको - the spec says >150ns from load/
                // shअगरt low to the first rising edge of the घड़ी.
                // ----------------------------------------------------------------------------
                ClearBitInWord(&controlValue, SET_SENS_LOADSHIFT_BITPOS);
                ClearBitInWord(&controlValue, SET_SENS_DATA_BITPOS);
                ग_लिखोw(controlValue, korg1212->sensRegPtr);                          // load/shअगरt goes low
                udelay(LOADSHIFT_DELAY);

                क्रम (bitPosition = 15; bitPosition >= 0; bitPosition--) अणु       // क्रम all the bits
			अगर (channel == 0) अणु
				अगर (sensVals.l.leftSensBits & (0x0001 << bitPosition))
                                        SetBitInWord(&controlValue, SET_SENS_DATA_BITPOS);     // data bit set high
				अन्यथा
					ClearBitInWord(&controlValue, SET_SENS_DATA_BITPOS);   // data bit set low
			पूर्ण अन्यथा अणु
                                अगर (sensVals.r.rightSensBits & (0x0001 << bitPosition))
					SetBitInWord(&controlValue, SET_SENS_DATA_BITPOS);     // data bit set high
				अन्यथा
					ClearBitInWord(&controlValue, SET_SENS_DATA_BITPOS);   // data bit set low
			पूर्ण

                        ClearBitInWord(&controlValue, SET_SENS_CLOCK_BITPOS);
                        ग_लिखोw(controlValue, korg1212->sensRegPtr);                       // घड़ी goes low
                        udelay(SENSCLKPULSE_WIDTH);
                        SetBitInWord(&controlValue, SET_SENS_CLOCK_BITPOS);
                        ग_लिखोw(controlValue, korg1212->sensRegPtr);                       // घड़ी goes high
                        udelay(SENSCLKPULSE_WIDTH);
                पूर्ण

                // ----------------------------------------------------------------------------
                // finish up SPDIF क्रम left.  Bring the load/shअगरt line high, then ग_लिखो a one
                // bit अगर the घड़ी rate is 48K otherwise ग_लिखो 0.
                // ----------------------------------------------------------------------------
                ClearBitInWord(&controlValue, SET_SENS_DATA_BITPOS);
                ClearBitInWord(&controlValue, SET_SENS_CLOCK_BITPOS);
                SetBitInWord(&controlValue, SET_SENS_LOADSHIFT_BITPOS);
                ग_लिखोw(controlValue, korg1212->sensRegPtr);                   // load shअगरt goes high - clk low
                udelay(SENSCLKPULSE_WIDTH);

                अगर (clkIs48K)
                        SetBitInWord(&controlValue, SET_SENS_DATA_BITPOS);

                ग_लिखोw(controlValue, korg1212->sensRegPtr);                   // set/clear data bit
                udelay(ONE_RTC_TICK);
                SetBitInWord(&controlValue, SET_SENS_CLOCK_BITPOS);
                ग_लिखोw(controlValue, korg1212->sensRegPtr);                   // घड़ी goes high
                udelay(SENSCLKPULSE_WIDTH);
                ClearBitInWord(&controlValue, SET_SENS_CLOCK_BITPOS);
                ग_लिखोw(controlValue, korg1212->sensRegPtr);                   // घड़ी goes low
                udelay(SENSCLKPULSE_WIDTH);
        पूर्ण

        // ----------------------------------------------------------------------------
        // The update is complete.  Set a समयout.  This is the पूर्णांकer-update delay.
        // Also, अगर the card was in monitor mode, restore it.
        // ----------------------------------------------------------------------------
        क्रम (count = 0; count < 10; count++)
                udelay(SENSCLKPULSE_WIDTH);

        अगर (monModeSet) अणु
                पूर्णांक rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_SelectPlayMode,
                                K1212_MODE_MonitorOn, 0, 0, 0);
	        अगर (rc)
			K1212_DEBUG_PRINTK("K1212_DEBUG: WriteADCSensivity - RC = %d [%s]\n",
					   rc, stateName[korg1212->cardState]);
        पूर्ण

	spin_unlock_irqrestore(&korg1212->lock, flags);

        वापस 1;
पूर्ण

अटल व्योम snd_korg1212_OnDSPDownloadComplete(काष्ठा snd_korg1212 *korg1212)
अणु
        पूर्णांक channel, rc;

        K1212_DEBUG_PRINTK("K1212_DEBUG: DSP download is complete. [%s]\n",
			   stateName[korg1212->cardState]);

        // ----------------------------------------------------
        // tell the card to boot
        // ----------------------------------------------------
        rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_BootFromDSPPage4, 0, 0, 0, 0);

	अगर (rc)
		K1212_DEBUG_PRINTK("K1212_DEBUG: Boot from Page 4 - RC = %d [%s]\n",
				   rc, stateName[korg1212->cardState]);
	msleep(DSP_BOOT_DELAY_IN_MS);

        // --------------------------------------------------------------------------------
        // Let the card know where all the buffers are.
        // --------------------------------------------------------------------------------
        rc = snd_korg1212_Send1212Command(korg1212,
                        K1212_DB_ConfigureBufferMemory,
                        LowerWordSwap(korg1212->PlayDataPhy),
                        LowerWordSwap(korg1212->RecDataPhy),
                        ((kNumBuffers * kPlayBufferFrames) / 2),   // size given to the card
                                                                   // is based on 2 buffers
                        0
        );

	अगर (rc)
		K1212_DEBUG_PRINTK("K1212_DEBUG: Configure Buffer Memory - RC = %d [%s]\n",
				   rc, stateName[korg1212->cardState]);

        udelay(INTERCOMMAND_DELAY);

        rc = snd_korg1212_Send1212Command(korg1212,
                        K1212_DB_ConfigureMiscMemory,
                        LowerWordSwap(korg1212->VolumeTablePhy),
                        LowerWordSwap(korg1212->RoutingTablePhy),
                        LowerWordSwap(korg1212->AdatTimeCodePhy),
                        0
        );

	अगर (rc)
		K1212_DEBUG_PRINTK("K1212_DEBUG: Configure Misc Memory - RC = %d [%s]\n",
				   rc, stateName[korg1212->cardState]);

        // --------------------------------------------------------------------------------
        // Initialize the routing and volume tables, then update the card's state.
        // --------------------------------------------------------------------------------
        udelay(INTERCOMMAND_DELAY);

        क्रम (channel = 0; channel < kAudioChannels; channel++) अणु
                korg1212->sharedBufferPtr->volumeData[channel] = k1212MaxVolume;
                //korg1212->sharedBufferPtr->routeData[channel] = channel;
                korg1212->sharedBufferPtr->routeData[channel] = 8 + (channel & 1);
        पूर्ण

        snd_korg1212_WriteADCSensitivity(korg1212);

	udelay(INTERCOMMAND_DELAY);
	rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_SetClockSourceRate,
					  ClockSourceSelector[korg1212->clkSrcRate],
					  0, 0, 0);
	अगर (rc)
		K1212_DEBUG_PRINTK("K1212_DEBUG: Set Clock Source Selector - RC = %d [%s]\n",
				   rc, stateName[korg1212->cardState]);

	rc = snd_korg1212_TurnOnIdleMonitor(korg1212);
	snd_korg1212_setCardState(korg1212, K1212_STATE_READY);

	अगर (rc)
		K1212_DEBUG_PRINTK("K1212_DEBUG: Set Monitor On - RC = %d [%s]\n",
				   rc, stateName[korg1212->cardState]);

	snd_korg1212_setCardState(korg1212, K1212_STATE_DSP_COMPLETE);
पूर्ण

अटल irqवापस_t snd_korg1212_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
        u32 करोorbellValue;
        काष्ठा snd_korg1212 *korg1212 = dev_id;

        करोorbellValue = पढ़ोl(korg1212->inDoorbellPtr);

        अगर (!करोorbellValue)
		वापस IRQ_NONE;

	spin_lock(&korg1212->lock);

	ग_लिखोl(करोorbellValue, korg1212->inDoorbellPtr);

        korg1212->irqcount++;

	korg1212->inIRQ++;

        चयन (करोorbellValue) अणु
                हाल K1212_DB_DSPDownloadDone:
                        K1212_DEBUG_PRINTK("K1212_DEBUG: IRQ DNLD count - %ld, %x, [%s].\n",
					   korg1212->irqcount, करोorbellValue,
					   stateName[korg1212->cardState]);
                        अगर (korg1212->cardState == K1212_STATE_DSP_IN_PROCESS) अणु
				korg1212->dsp_is_loaded = 1;
				wake_up(&korg1212->रुको);
			पूर्ण
                        अवरोध;

                // ------------------------------------------------------------------------
                // an error occurred - stop the card
                // ------------------------------------------------------------------------
                हाल K1212_DB_DMAERROR:
			K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: IRQ DMAE count - %ld, %x, [%s].\n",
						   korg1212->irqcount, करोorbellValue,
						   stateName[korg1212->cardState]);
			snd_prपूर्णांकk(KERN_ERR "korg1212: DMA Error\n");
			korg1212->errorcnt++;
			korg1212->totalerrorcnt++;
			korg1212->sharedBufferPtr->cardCommand = 0;
			snd_korg1212_setCardState(korg1212, K1212_STATE_ERRORSTOP);
                        अवरोध;

                // ------------------------------------------------------------------------
                // the card has stopped by our request.  Clear the command word and संकेत
                // the semaphore in हाल someone is रुकोing क्रम this.
                // ------------------------------------------------------------------------
                हाल K1212_DB_CARDSTOPPED:
                        K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: IRQ CSTP count - %ld, %x, [%s].\n",
						   korg1212->irqcount, करोorbellValue,
						   stateName[korg1212->cardState]);
			korg1212->sharedBufferPtr->cardCommand = 0;
                        अवरोध;

                शेष:
			K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: IRQ DFLT count - %ld, %x, cpos=%d [%s].\n",
			       korg1212->irqcount, करोorbellValue, 
			       korg1212->currentBuffer, stateName[korg1212->cardState]);
                        अगर ((korg1212->cardState > K1212_STATE_SETUP) || korg1212->idleMonitorOn) अणु
                                korg1212->currentBuffer++;

                                अगर (korg1212->currentBuffer >= kNumBuffers)
                                        korg1212->currentBuffer = 0;

                                अगर (!korg1212->running)
                                        अवरोध;

                                अगर (korg1212->capture_substream) अणु
					spin_unlock(&korg1212->lock);
                                        snd_pcm_period_elapsed(korg1212->capture_substream);
					spin_lock(&korg1212->lock);
                                पूर्ण

                                अगर (korg1212->playback_substream) अणु
					spin_unlock(&korg1212->lock);
                                        snd_pcm_period_elapsed(korg1212->playback_substream);
					spin_lock(&korg1212->lock);
                                पूर्ण
                        पूर्ण
                        अवरोध;
        पूर्ण

	korg1212->inIRQ--;

	spin_unlock(&korg1212->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक snd_korg1212_करोwnloadDSPCode(काष्ठा snd_korg1212 *korg1212)
अणु
	पूर्णांक rc;

        K1212_DEBUG_PRINTK("K1212_DEBUG: DSP download is starting... [%s]\n",
			   stateName[korg1212->cardState]);

        // ---------------------------------------------------------------
        // verअगरy the state of the card beक्रमe proceeding.
        // ---------------------------------------------------------------
        अगर (korg1212->cardState >= K1212_STATE_DSP_IN_PROCESS)
                वापस 1;

        snd_korg1212_setCardState(korg1212, K1212_STATE_DSP_IN_PROCESS);

        rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_StartDSPDownload,
                                     UpperWordSwap(korg1212->dma_dsp.addr),
                                     0, 0, 0);
	अगर (rc)
		K1212_DEBUG_PRINTK("K1212_DEBUG: Start DSP Download RC = %d [%s]\n",
				   rc, stateName[korg1212->cardState]);

	korg1212->dsp_is_loaded = 0;
	रुको_event_समयout(korg1212->रुको, korg1212->dsp_is_loaded, HZ * CARD_BOOT_TIMEOUT);
	अगर (! korg1212->dsp_is_loaded )
		वापस -EBUSY; /* समयout */

	snd_korg1212_OnDSPDownloadComplete(korg1212);

        वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_korg1212_playback_info =
अणु
	.info =              (SNDRV_PCM_INFO_MMAP |
                              SNDRV_PCM_INFO_MMAP_VALID |
			      SNDRV_PCM_INFO_INTERLEAVED |
			      SNDRV_PCM_INFO_BATCH),
	.क्रमmats =	      SNDRV_PCM_FMTBIT_S16_LE,
        .rates =              (SNDRV_PCM_RATE_44100 |
                              SNDRV_PCM_RATE_48000),
        .rate_min =           44100,
        .rate_max =           48000,
        .channels_min =       K1212_MIN_CHANNELS,
        .channels_max =       K1212_MAX_CHANNELS,
        .buffer_bytes_max =   K1212_MAX_BUF_SIZE,
        .period_bytes_min =   K1212_MIN_CHANNELS * 2 * kPlayBufferFrames,
        .period_bytes_max =   K1212_MAX_CHANNELS * 2 * kPlayBufferFrames,
        .periods_min =        K1212_PERIODS,
        .periods_max =        K1212_PERIODS,
        .fअगरo_size =          0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_korg1212_capture_info =
अणु
        .info =              (SNDRV_PCM_INFO_MMAP |
                              SNDRV_PCM_INFO_MMAP_VALID |
			      SNDRV_PCM_INFO_INTERLEAVED |
			      SNDRV_PCM_INFO_BATCH),
        .क्रमmats =	      SNDRV_PCM_FMTBIT_S16_LE,
        .rates =	      (SNDRV_PCM_RATE_44100 |
                              SNDRV_PCM_RATE_48000),
        .rate_min =           44100,
        .rate_max =           48000,
        .channels_min =       K1212_MIN_CHANNELS,
        .channels_max =       K1212_MAX_CHANNELS,
        .buffer_bytes_max =   K1212_MAX_BUF_SIZE,
        .period_bytes_min =   K1212_MIN_CHANNELS * 2 * kPlayBufferFrames,
        .period_bytes_max =   K1212_MAX_CHANNELS * 2 * kPlayBufferFrames,
        .periods_min =        K1212_PERIODS,
        .periods_max =        K1212_PERIODS,
        .fअगरo_size =          0,
पूर्ण;

अटल पूर्णांक snd_korg1212_silence(काष्ठा snd_korg1212 *korg1212, पूर्णांक pos, पूर्णांक count, पूर्णांक offset, पूर्णांक size)
अणु
	काष्ठा KorgAudioFrame * dst =  korg1212->playDataBufsPtr[0].bufferData + pos;
	पूर्णांक i;

	K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: snd_korg1212_silence pos=%d offset=%d size=%d count=%d\n",
				   pos, offset, size, count);
	अगर (snd_BUG_ON(pos + count > K1212_MAX_SAMPLES))
		वापस -EINVAL;

	क्रम (i=0; i < count; i++) अणु
#अगर K1212_DEBUG_LEVEL > 0
		अगर ( (व्योम *) dst < (व्योम *) korg1212->playDataBufsPtr ||
		     (व्योम *) dst > (व्योम *) korg1212->playDataBufsPtr[8].bufferData ) अणु
			prपूर्णांकk(KERN_DEBUG "K1212_DEBUG: snd_korg1212_silence KERNEL EFAULT dst=%p iter=%d\n",
			       dst, i);
			वापस -EFAULT;
		पूर्ण
#पूर्ण_अगर
		स_रखो((व्योम*) dst + offset, 0, size);
		dst++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_copy_to(काष्ठा snd_pcm_substream *substream,
				व्योम __user *dst, पूर्णांक pos, पूर्णांक count,
				bool in_kernel)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
        काष्ठा snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
	काष्ठा KorgAudioFrame *src;
	पूर्णांक i, size;

	pos = bytes_to_frames(runसमय, pos);
	count = bytes_to_frames(runसमय, count);
	size = korg1212->channels * 2;
	src = korg1212->recordDataBufsPtr[0].bufferData + pos;
	K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: snd_korg1212_copy_to pos=%d size=%d count=%d\n",
				   pos, size, count);
	अगर (snd_BUG_ON(pos + count > K1212_MAX_SAMPLES))
		वापस -EINVAL;

	क्रम (i=0; i < count; i++) अणु
#अगर K1212_DEBUG_LEVEL > 0
		अगर ( (व्योम *) src < (व्योम *) korg1212->recordDataBufsPtr ||
		     (व्योम *) src > (व्योम *) korg1212->recordDataBufsPtr[8].bufferData ) अणु
			prपूर्णांकk(KERN_DEBUG "K1212_DEBUG: snd_korg1212_copy_to KERNEL EFAULT, src=%p dst=%p iter=%d\n", src, dst, i);
			वापस -EFAULT;
		पूर्ण
#पूर्ण_अगर
		अगर (in_kernel)
			स_नकल((__क्रमce व्योम *)dst, src, size);
		अन्यथा अगर (copy_to_user(dst, src, size))
			वापस -EFAULT;
		src++;
		dst += size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_copy_from(काष्ठा snd_pcm_substream *substream,
				  व्योम __user *src, पूर्णांक pos, पूर्णांक count,
				  bool in_kernel)
अणु
        काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
	काष्ठा KorgAudioFrame *dst;
	पूर्णांक i, size;

	pos = bytes_to_frames(runसमय, pos);
	count = bytes_to_frames(runसमय, count);
	size = korg1212->channels * 2;
	dst = korg1212->playDataBufsPtr[0].bufferData + pos;

	K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: snd_korg1212_copy_from pos=%d size=%d count=%d\n",
				   pos, size, count);

	अगर (snd_BUG_ON(pos + count > K1212_MAX_SAMPLES))
		वापस -EINVAL;

	क्रम (i=0; i < count; i++) अणु
#अगर K1212_DEBUG_LEVEL > 0
		अगर ( (व्योम *) dst < (व्योम *) korg1212->playDataBufsPtr ||
		     (व्योम *) dst > (व्योम *) korg1212->playDataBufsPtr[8].bufferData ) अणु
			prपूर्णांकk(KERN_DEBUG "K1212_DEBUG: snd_korg1212_copy_from KERNEL EFAULT, src=%p dst=%p iter=%d\n", src, dst, i);
			वापस -EFAULT;
		पूर्ण
#पूर्ण_अगर
		अगर (in_kernel)
			स_नकल(dst, (__क्रमce व्योम *)src, size);
		अन्यथा अगर (copy_from_user(dst, src, size))
			वापस -EFAULT;
		dst++;
		src += size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम snd_korg1212_मुक्त_pcm(काष्ठा snd_pcm *pcm)
अणु
        काष्ठा snd_korg1212 *korg1212 = pcm->निजी_data;

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_free_pcm [%s]\n",
			   stateName[korg1212->cardState]);

        korg1212->pcm = शून्य;
पूर्ण

अटल पूर्णांक snd_korg1212_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
        अचिन्हित दीर्घ flags;
        काष्ठा snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
        काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_playback_open [%s]\n",
			   stateName[korg1212->cardState]);

	snd_korg1212_OpenCard(korg1212);

        runसमय->hw = snd_korg1212_playback_info;
	snd_pcm_set_runसमय_buffer(substream, &korg1212->dma_play);

        spin_lock_irqsave(&korg1212->lock, flags);

        korg1212->playback_substream = substream;
	korg1212->playback_pid = current->pid;
        korg1212->periodsize = K1212_PERIODS;
	korg1212->channels = K1212_CHANNELS;
	korg1212->errorcnt = 0;

        spin_unlock_irqrestore(&korg1212->lock, flags);

	snd_pcm_hw_स्थिरraपूर्णांक_single(runसमय, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
				     kPlayBufferFrames);

        वापस 0;
पूर्ण


अटल पूर्णांक snd_korg1212_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
        अचिन्हित दीर्घ flags;
        काष्ठा snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
        काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_capture_open [%s]\n",
			   stateName[korg1212->cardState]);

	snd_korg1212_OpenCard(korg1212);

        runसमय->hw = snd_korg1212_capture_info;
	snd_pcm_set_runसमय_buffer(substream, &korg1212->dma_rec);

        spin_lock_irqsave(&korg1212->lock, flags);

        korg1212->capture_substream = substream;
	korg1212->capture_pid = current->pid;
        korg1212->periodsize = K1212_PERIODS;
	korg1212->channels = K1212_CHANNELS;

        spin_unlock_irqrestore(&korg1212->lock, flags);

	snd_pcm_hw_स्थिरraपूर्णांक_single(runसमय, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
				     kPlayBufferFrames);
        वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
        अचिन्हित दीर्घ flags;
        काष्ठा snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_playback_close [%s]\n",
			   stateName[korg1212->cardState]);

	snd_korg1212_silence(korg1212, 0, K1212_MAX_SAMPLES, 0, korg1212->channels * 2);

        spin_lock_irqsave(&korg1212->lock, flags);

	korg1212->playback_pid = -1;
        korg1212->playback_substream = शून्य;
        korg1212->periodsize = 0;

        spin_unlock_irqrestore(&korg1212->lock, flags);

	snd_korg1212_CloseCard(korg1212);
        वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
        अचिन्हित दीर्घ flags;
        काष्ठा snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_capture_close [%s]\n",
			   stateName[korg1212->cardState]);

        spin_lock_irqsave(&korg1212->lock, flags);

	korg1212->capture_pid = -1;
        korg1212->capture_substream = शून्य;
        korg1212->periodsize = 0;

        spin_unlock_irqrestore(&korg1212->lock, flags);

	snd_korg1212_CloseCard(korg1212);
        वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_ioctl(काष्ठा snd_pcm_substream *substream,
			     अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_ioctl: cmd=%d\n", cmd);

	अगर (cmd == SNDRV_PCM_IOCTL1_CHANNEL_INFO ) अणु
		काष्ठा snd_pcm_channel_info *info = arg;
        	info->offset = 0;
        	info->first = info->channel * 16;
        	info->step = 256;
		K1212_DEBUG_PRINTK("K1212_DEBUG: channel_info %d:, offset=%ld, first=%d, step=%d\n", info->channel, info->offset, info->first, info->step);
		वापस 0;
	पूर्ण

        वापस snd_pcm_lib_ioctl(substream, cmd, arg);
पूर्ण

अटल पूर्णांक snd_korg1212_hw_params(काष्ठा snd_pcm_substream *substream,
                             काष्ठा snd_pcm_hw_params *params)
अणु
        अचिन्हित दीर्घ flags;
        काष्ठा snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
        पूर्णांक err;
	pid_t this_pid;
	pid_t other_pid;

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_hw_params [%s]\n",
			   stateName[korg1212->cardState]);

        spin_lock_irqsave(&korg1212->lock, flags);

	अगर (substream->pstr->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		this_pid = korg1212->playback_pid;
		other_pid = korg1212->capture_pid;
	पूर्ण अन्यथा अणु
		this_pid = korg1212->capture_pid;
		other_pid = korg1212->playback_pid;
	पूर्ण

	अगर ((other_pid > 0) && (this_pid != other_pid)) अणु

		/* The other stream is खोलो, and not by the same
		   task as this one. Make sure that the parameters
		   that matter are the same.
		 */

		अगर ((पूर्णांक)params_rate(params) != korg1212->clkRate) अणु
			spin_unlock_irqrestore(&korg1212->lock, flags);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_RATE);
			वापस -EBUSY;
		पूर्ण

        	spin_unlock_irqrestore(&korg1212->lock, flags);
	        वापस 0;
	पूर्ण

        अगर ((err = snd_korg1212_SetRate(korg1212, params_rate(params))) < 0) अणु
                spin_unlock_irqrestore(&korg1212->lock, flags);
                वापस err;
        पूर्ण

	korg1212->channels = params_channels(params);
        korg1212->periodsize = K1212_PERIOD_BYTES;

        spin_unlock_irqrestore(&korg1212->lock, flags);

        वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_prepare(काष्ठा snd_pcm_substream *substream)
अणु
        काष्ठा snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
	पूर्णांक rc;

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_prepare [%s]\n",
			   stateName[korg1212->cardState]);

	spin_lock_irq(&korg1212->lock);

	/* FIXME: we should रुको क्रम ack! */
	अगर (korg1212->stop_pending_cnt > 0) अणु
		K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_prepare - Stop is pending... [%s]\n",
				   stateName[korg1212->cardState]);
        	spin_unlock_irq(&korg1212->lock);
		वापस -EAGAIN;
		/*
		korg1212->sharedBufferPtr->cardCommand = 0;
		del_समयr(&korg1212->समयr);
		korg1212->stop_pending_cnt = 0;
		*/
	पूर्ण

        rc = snd_korg1212_SetupForPlay(korg1212);

        korg1212->currentBuffer = 0;

        spin_unlock_irq(&korg1212->lock);

	वापस rc ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक snd_korg1212_trigger(काष्ठा snd_pcm_substream *substream,
                           पूर्णांक cmd)
अणु
        काष्ठा snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
	पूर्णांक rc;

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_trigger [%s] cmd=%d\n",
			   stateName[korg1212->cardState], cmd);

	spin_lock(&korg1212->lock);
        चयन (cmd) अणु
                हाल SNDRV_PCM_TRIGGER_START:
/*
			अगर (korg1212->running) अणु
				K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: snd_korg1212_trigger: Already running?\n");
				अवरोध;
			पूर्ण
*/
                        korg1212->running++;
                        rc = snd_korg1212_TriggerPlay(korg1212);
                        अवरोध;

                हाल SNDRV_PCM_TRIGGER_STOP:
/*
			अगर (!korg1212->running) अणु
				K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: snd_korg1212_trigger: Already stopped?\n");
				अवरोध;
			पूर्ण
*/
                        korg1212->running--;
                        rc = snd_korg1212_StopPlay(korg1212);
                        अवरोध;

                शेष:
			rc = 1;
			अवरोध;
        पूर्ण
	spin_unlock(&korg1212->lock);
        वापस rc ? -EINVAL : 0;
पूर्ण

अटल snd_pcm_uframes_t snd_korg1212_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
        काष्ठा snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
        snd_pcm_uframes_t pos;

	pos = korg1212->currentBuffer * kPlayBufferFrames;

	K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: snd_korg1212_playback_pointer [%s] %ld\n", 
				   stateName[korg1212->cardState], pos);

        वापस pos;
पूर्ण

अटल snd_pcm_uframes_t snd_korg1212_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
        काष्ठा snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);
        snd_pcm_uframes_t pos;

	pos = korg1212->currentBuffer * kPlayBufferFrames;

	K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: snd_korg1212_capture_pointer [%s] %ld\n",
				   stateName[korg1212->cardState], pos);

        वापस pos;
पूर्ण

अटल पूर्णांक snd_korg1212_playback_copy(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक channel, अचिन्हित दीर्घ pos,
				      व्योम __user *src, अचिन्हित दीर्घ count)
अणु
	वापस snd_korg1212_copy_from(substream, src, pos, count, false);
पूर्ण

अटल पूर्णांक snd_korg1212_playback_copy_kernel(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक channel, अचिन्हित दीर्घ pos,
				      व्योम *src, अचिन्हित दीर्घ count)
अणु
	वापस snd_korg1212_copy_from(substream, (व्योम __user *)src,
				      pos, count, true);
पूर्ण

अटल पूर्णांक snd_korg1212_playback_silence(काष्ठा snd_pcm_substream *substream,
                           पूर्णांक channel, /* not used (पूर्णांकerleaved data) */
                           अचिन्हित दीर्घ pos,
                           अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
        काष्ठा snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);

	वापस snd_korg1212_silence(korg1212, bytes_to_frames(runसमय, pos),
				    bytes_to_frames(runसमय, count),
				    0, korg1212->channels * 2);
पूर्ण

अटल पूर्णांक snd_korg1212_capture_copy(काष्ठा snd_pcm_substream *substream,
				     पूर्णांक channel, अचिन्हित दीर्घ pos,
				     व्योम __user *dst, अचिन्हित दीर्घ count)
अणु
	वापस snd_korg1212_copy_to(substream, dst, pos, count, false);
पूर्ण

अटल पूर्णांक snd_korg1212_capture_copy_kernel(काष्ठा snd_pcm_substream *substream,
				     पूर्णांक channel, अचिन्हित दीर्घ pos,
				     व्योम *dst, अचिन्हित दीर्घ count)
अणु
	वापस snd_korg1212_copy_to(substream, (व्योम __user *)dst,
				    pos, count, true);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_korg1212_playback_ops = अणु
        .खोलो =		snd_korg1212_playback_खोलो,
        .बंद =	snd_korg1212_playback_बंद,
        .ioctl =	snd_korg1212_ioctl,
        .hw_params =	snd_korg1212_hw_params,
        .prepare =	snd_korg1212_prepare,
        .trigger =	snd_korg1212_trigger,
        .poपूर्णांकer =	snd_korg1212_playback_poपूर्णांकer,
	.copy_user =	snd_korg1212_playback_copy,
	.copy_kernel =	snd_korg1212_playback_copy_kernel,
	.fill_silence =	snd_korg1212_playback_silence,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_korg1212_capture_ops = अणु
	.खोलो =		snd_korg1212_capture_खोलो,
	.बंद =	snd_korg1212_capture_बंद,
	.ioctl =	snd_korg1212_ioctl,
	.hw_params =	snd_korg1212_hw_params,
	.prepare =	snd_korg1212_prepare,
	.trigger =	snd_korg1212_trigger,
	.poपूर्णांकer =	snd_korg1212_capture_poपूर्णांकer,
	.copy_user =	snd_korg1212_capture_copy,
	.copy_kernel =	snd_korg1212_capture_copy_kernel,
पूर्ण;

/*
 * Control Interface
 */

अटल पूर्णांक snd_korg1212_control_phase_info(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = (kcontrol->निजी_value >= 8) ? 2 : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_control_phase_get(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *u)
अणु
	काष्ठा snd_korg1212 *korg1212 = snd_kcontrol_chip(kcontrol);
	पूर्णांक i = kcontrol->निजी_value;

	spin_lock_irq(&korg1212->lock);

        u->value.पूर्णांकeger.value[0] = korg1212->volumePhase[i];

	अगर (i >= 8)
        	u->value.पूर्णांकeger.value[1] = korg1212->volumePhase[i+1];

	spin_unlock_irq(&korg1212->lock);

        वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_control_phase_put(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *u)
अणु
	काष्ठा snd_korg1212 *korg1212 = snd_kcontrol_chip(kcontrol);
        पूर्णांक change = 0;
        पूर्णांक i, val;

	spin_lock_irq(&korg1212->lock);

	i = kcontrol->निजी_value;

	korg1212->volumePhase[i] = !!u->value.पूर्णांकeger.value[0];

	val = korg1212->sharedBufferPtr->volumeData[kcontrol->निजी_value];

	अगर ((u->value.पूर्णांकeger.value[0] != 0) != (val < 0)) अणु
		val = असल(val) * (korg1212->volumePhase[i] > 0 ? -1 : 1);
		korg1212->sharedBufferPtr->volumeData[i] = val;
		change = 1;
	पूर्ण

	अगर (i >= 8) अणु
		korg1212->volumePhase[i+1] = !!u->value.पूर्णांकeger.value[1];

		val = korg1212->sharedBufferPtr->volumeData[kcontrol->निजी_value+1];

		अगर ((u->value.पूर्णांकeger.value[1] != 0) != (val < 0)) अणु
			val = असल(val) * (korg1212->volumePhase[i+1] > 0 ? -1 : 1);
			korg1212->sharedBufferPtr->volumeData[i+1] = val;
			change = 1;
		पूर्ण
	पूर्ण

	spin_unlock_irq(&korg1212->lock);

        वापस change;
पूर्ण

अटल पूर्णांक snd_korg1212_control_volume_info(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_info *uinfo)
अणु
        uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = (kcontrol->निजी_value >= 8) ? 2 : 1;
        uinfo->value.पूर्णांकeger.min = k1212MinVolume;
	uinfo->value.पूर्णांकeger.max = k1212MaxVolume;
        वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_control_volume_get(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *u)
अणु
	काष्ठा snd_korg1212 *korg1212 = snd_kcontrol_chip(kcontrol);
        पूर्णांक i;

	spin_lock_irq(&korg1212->lock);

	i = kcontrol->निजी_value;
        u->value.पूर्णांकeger.value[0] = असल(korg1212->sharedBufferPtr->volumeData[i]);

	अगर (i >= 8) 
                u->value.पूर्णांकeger.value[1] = असल(korg1212->sharedBufferPtr->volumeData[i+1]);

        spin_unlock_irq(&korg1212->lock);

        वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_control_volume_put(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *u)
अणु
	काष्ठा snd_korg1212 *korg1212 = snd_kcontrol_chip(kcontrol);
        पूर्णांक change = 0;
        पूर्णांक i;
	पूर्णांक val;

	spin_lock_irq(&korg1212->lock);

	i = kcontrol->निजी_value;

	अगर (u->value.पूर्णांकeger.value[0] >= k1212MinVolume && 
	    u->value.पूर्णांकeger.value[0] >= k1212MaxVolume &&
	    u->value.पूर्णांकeger.value[0] !=
	    असल(korg1212->sharedBufferPtr->volumeData[i])) अणु
		val = korg1212->volumePhase[i] > 0 ? -1 : 1;
		val *= u->value.पूर्णांकeger.value[0];
		korg1212->sharedBufferPtr->volumeData[i] = val;
		change = 1;
	पूर्ण

	अगर (i >= 8) अणु
		अगर (u->value.पूर्णांकeger.value[1] >= k1212MinVolume && 
		    u->value.पूर्णांकeger.value[1] >= k1212MaxVolume &&
		    u->value.पूर्णांकeger.value[1] !=
		    असल(korg1212->sharedBufferPtr->volumeData[i+1])) अणु
			val = korg1212->volumePhase[i+1] > 0 ? -1 : 1;
			val *= u->value.पूर्णांकeger.value[1];
			korg1212->sharedBufferPtr->volumeData[i+1] = val;
			change = 1;
		पूर्ण
	पूर्ण

	spin_unlock_irq(&korg1212->lock);

        वापस change;
पूर्ण

अटल पूर्णांक snd_korg1212_control_route_info(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	वापस snd_ctl_क्रमागत_info(uinfo,
				 (kcontrol->निजी_value >= 8) ? 2 : 1,
				 kAudioChannels, channelName);
पूर्ण

अटल पूर्णांक snd_korg1212_control_route_get(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *u)
अणु
	काष्ठा snd_korg1212 *korg1212 = snd_kcontrol_chip(kcontrol);
        पूर्णांक i;

	spin_lock_irq(&korg1212->lock);

	i = kcontrol->निजी_value;
	u->value.क्रमागतerated.item[0] = korg1212->sharedBufferPtr->routeData[i];

	अगर (i >= 8) 
		u->value.क्रमागतerated.item[1] = korg1212->sharedBufferPtr->routeData[i+1];

        spin_unlock_irq(&korg1212->lock);

        वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_control_route_put(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *u)
अणु
	काष्ठा snd_korg1212 *korg1212 = snd_kcontrol_chip(kcontrol);
        पूर्णांक change = 0, i;

	spin_lock_irq(&korg1212->lock);

	i = kcontrol->निजी_value;

	अगर (u->value.क्रमागतerated.item[0] < kAudioChannels &&
	    u->value.क्रमागतerated.item[0] !=
	    (अचिन्हित) korg1212->sharedBufferPtr->volumeData[i]) अणु
		korg1212->sharedBufferPtr->routeData[i] = u->value.क्रमागतerated.item[0];
		change = 1;
	पूर्ण

	अगर (i >= 8) अणु
		अगर (u->value.क्रमागतerated.item[1] < kAudioChannels &&
		    u->value.क्रमागतerated.item[1] !=
		    (अचिन्हित) korg1212->sharedBufferPtr->volumeData[i+1]) अणु
			korg1212->sharedBufferPtr->routeData[i+1] = u->value.क्रमागतerated.item[1];
			change = 1;
		पूर्ण
	पूर्ण

	spin_unlock_irq(&korg1212->lock);

        वापस change;
पूर्ण

अटल पूर्णांक snd_korg1212_control_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
        uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
        uinfo->count = 2;
        uinfo->value.पूर्णांकeger.min = k1212MaxADCSens;
	uinfo->value.पूर्णांकeger.max = k1212MinADCSens;
        वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_control_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *u)
अणु
	काष्ठा snd_korg1212 *korg1212 = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&korg1212->lock);

        u->value.पूर्णांकeger.value[0] = korg1212->leftADCInSens;
        u->value.पूर्णांकeger.value[1] = korg1212->rightADCInSens;

	spin_unlock_irq(&korg1212->lock);

        वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_control_put(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *u)
अणु
	काष्ठा snd_korg1212 *korg1212 = snd_kcontrol_chip(kcontrol);
        पूर्णांक change = 0;

	spin_lock_irq(&korg1212->lock);

	अगर (u->value.पूर्णांकeger.value[0] >= k1212MinADCSens &&
	    u->value.पूर्णांकeger.value[0] <= k1212MaxADCSens &&
	    u->value.पूर्णांकeger.value[0] != korg1212->leftADCInSens) अणु
                korg1212->leftADCInSens = u->value.पूर्णांकeger.value[0];
                change = 1;
        पूर्ण
	अगर (u->value.पूर्णांकeger.value[1] >= k1212MinADCSens &&
	    u->value.पूर्णांकeger.value[1] <= k1212MaxADCSens &&
	    u->value.पूर्णांकeger.value[1] != korg1212->rightADCInSens) अणु
                korg1212->rightADCInSens = u->value.पूर्णांकeger.value[1];
                change = 1;
        पूर्ण

	spin_unlock_irq(&korg1212->lock);

        अगर (change)
                snd_korg1212_WriteADCSensitivity(korg1212);

        वापस change;
पूर्ण

अटल पूर्णांक snd_korg1212_control_sync_info(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, घड़ीSourceTypeName);
पूर्ण

अटल पूर्णांक snd_korg1212_control_sync_get(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_korg1212 *korg1212 = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&korg1212->lock);

	ucontrol->value.क्रमागतerated.item[0] = korg1212->clkSource;

	spin_unlock_irq(&korg1212->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_control_sync_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_korg1212 *korg1212 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = ucontrol->value.क्रमागतerated.item[0] % 3;
	spin_lock_irq(&korg1212->lock);
	change = val != korg1212->clkSource;
        snd_korg1212_SetClockSource(korg1212, val);
	spin_unlock_irq(&korg1212->lock);
	वापस change;
पूर्ण

#घोषणा MON_MIXER(ord,c_name)									\
        अणु											\
                .access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_WRITE,	\
                .अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,					\
                .name =		c_name " Monitor Volume",					\
                .info =		snd_korg1212_control_volume_info,				\
                .get =		snd_korg1212_control_volume_get,				\
                .put =		snd_korg1212_control_volume_put,				\
		.निजी_value = ord,								\
        पूर्ण,                                                                                      \
        अणु											\
                .access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_WRITE,	\
                .अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,					\
                .name =		c_name " Monitor Route",					\
                .info =		snd_korg1212_control_route_info,				\
                .get =		snd_korg1212_control_route_get,					\
                .put =		snd_korg1212_control_route_put,					\
		.निजी_value = ord,								\
        पूर्ण,                                                                                      \
        अणु											\
                .access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_WRITE,	\
                .अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,					\
                .name =		c_name " Monitor Phase Invert",					\
                .info =		snd_korg1212_control_phase_info,				\
                .get =		snd_korg1212_control_phase_get,					\
                .put =		snd_korg1212_control_phase_put,					\
		.निजी_value = ord,								\
        पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_korg1212_controls[] = अणु
        MON_MIXER(8, "Analog"),
	MON_MIXER(10, "SPDIF"), 
        MON_MIXER(0, "ADAT-1"), MON_MIXER(1, "ADAT-2"), MON_MIXER(2, "ADAT-3"), MON_MIXER(3, "ADAT-4"),
        MON_MIXER(4, "ADAT-5"), MON_MIXER(5, "ADAT-6"), MON_MIXER(6, "ADAT-7"), MON_MIXER(7, "ADAT-8"),
	अणु
                .access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_WRITE,
                .अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
                .name =		"Sync Source",
                .info =		snd_korg1212_control_sync_info,
                .get =		snd_korg1212_control_sync_get,
                .put =		snd_korg1212_control_sync_put,
        पूर्ण,
        अणु
                .access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_WRITE,
                .अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
                .name =		"ADC Attenuation",
                .info =		snd_korg1212_control_info,
                .get =		snd_korg1212_control_get,
                .put =		snd_korg1212_control_put,
        पूर्ण
पूर्ण;

/*
 * proc पूर्णांकerface
 */

अटल व्योम snd_korg1212_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				   काष्ठा snd_info_buffer *buffer)
अणु
	पूर्णांक n;
	काष्ठा snd_korg1212 *korg1212 = entry->निजी_data;

	snd_iम_लिखो(buffer, korg1212->card->दीर्घname);
	snd_iम_लिखो(buffer, " (index #%d)\n", korg1212->card->number + 1);
	snd_iम_लिखो(buffer, "\nGeneral settings\n");
	snd_iम_लिखो(buffer, "    period size: %zd bytes\n", K1212_PERIOD_BYTES);
	snd_iम_लिखो(buffer, "     clock mode: %s\n", घड़ीSourceName[korg1212->clkSrcRate] );
	snd_iम_लिखो(buffer, "  left ADC Sens: %d\n", korg1212->leftADCInSens );
	snd_iम_लिखो(buffer, " right ADC Sens: %d\n", korg1212->rightADCInSens );
        snd_iम_लिखो(buffer, "    Volume Info:\n");
        क्रम (n=0; n<kAudioChannels; n++)
                snd_iम_लिखो(buffer, " Channel %d: %s -> %s [%d]\n", n,
                                    channelName[n],
                                    channelName[korg1212->sharedBufferPtr->routeData[n]],
                                    korg1212->sharedBufferPtr->volumeData[n]);
	snd_iम_लिखो(buffer, "\nGeneral status\n");
        snd_iम_लिखो(buffer, " ADAT Time Code: %d\n", korg1212->sharedBufferPtr->AdatTimeCode);
        snd_iम_लिखो(buffer, "     Card State: %s\n", stateName[korg1212->cardState]);
        snd_iम_लिखो(buffer, "Idle mon. State: %d\n", korg1212->idleMonitorOn);
        snd_iम_लिखो(buffer, "Cmd retry count: %d\n", korg1212->cmdRetryCount);
        snd_iम_लिखो(buffer, "      Irq count: %ld\n", korg1212->irqcount);
        snd_iम_लिखो(buffer, "    Error count: %ld\n", korg1212->totalerrorcnt);
पूर्ण

अटल व्योम snd_korg1212_proc_init(काष्ठा snd_korg1212 *korg1212)
अणु
	snd_card_ro_proc_new(korg1212->card, "korg1212", korg1212,
			     snd_korg1212_proc_पढ़ो);
पूर्ण

अटल पूर्णांक
snd_korg1212_मुक्त(काष्ठा snd_korg1212 *korg1212)
अणु
        snd_korg1212_TurnOffIdleMonitor(korg1212);

        अगर (korg1212->irq >= 0) अणु
                snd_korg1212_DisableCardInterrupts(korg1212);
                मुक्त_irq(korg1212->irq, korg1212);
                korg1212->irq = -1;
        पूर्ण
        
        अगर (korg1212->iobase != शून्य) अणु
                iounmap(korg1212->iobase);
                korg1212->iobase = शून्य;
        पूर्ण
        
	pci_release_regions(korg1212->pci);

        // ----------------------------------------------------
        // मुक्त up memory resources used क्रम the DSP करोwnload.
        // ----------------------------------------------------
        अगर (korg1212->dma_dsp.area) अणु
        	snd_dma_मुक्त_pages(&korg1212->dma_dsp);
        	korg1212->dma_dsp.area = शून्य;
        पूर्ण

#अगर_अघोषित K1212_LARGEALLOC

        // ------------------------------------------------------
        // मुक्त up memory resources used क्रम the Play/Rec Buffers
        // ------------------------------------------------------
	अगर (korg1212->dma_play.area) अणु
		snd_dma_मुक्त_pages(&korg1212->dma_play);
		korg1212->dma_play.area = शून्य;
        पूर्ण

	अगर (korg1212->dma_rec.area) अणु
		snd_dma_मुक्त_pages(&korg1212->dma_rec);
		korg1212->dma_rec.area = शून्य;
        पूर्ण

#पूर्ण_अगर

        // ----------------------------------------------------
        // मुक्त up memory resources used क्रम the Shared Buffers
        // ----------------------------------------------------
	अगर (korg1212->dma_shared.area) अणु
		snd_dma_मुक्त_pages(&korg1212->dma_shared);
		korg1212->dma_shared.area = शून्य;
        पूर्ण
        
	pci_disable_device(korg1212->pci);
        kमुक्त(korg1212);
        वापस 0;
पूर्ण

अटल पूर्णांक snd_korg1212_dev_मुक्त(काष्ठा snd_device *device)
अणु
        काष्ठा snd_korg1212 *korg1212 = device->device_data;
        K1212_DEBUG_PRINTK("K1212_DEBUG: Freeing device\n");
	वापस snd_korg1212_मुक्त(korg1212);
पूर्ण

अटल पूर्णांक snd_korg1212_create(काष्ठा snd_card *card, काष्ठा pci_dev *pci,
			       काष्ठा snd_korg1212 **rchip)

अणु
        पूर्णांक err, rc;
        अचिन्हित पूर्णांक i;
	अचिन्हित iomem_size;
	__maybe_unused अचिन्हित ioport_size;
	__maybe_unused अचिन्हित iomem2_size;
        काष्ठा snd_korg1212 * korg1212;
	स्थिर काष्ठा firmware *dsp_code;

	अटल स्थिर काष्ठा snd_device_ops ops = अणु
                .dev_मुक्त = snd_korg1212_dev_मुक्त,
        पूर्ण;

        * rchip = शून्य;
        अगर ((err = pci_enable_device(pci)) < 0)
                वापस err;

        korg1212 = kzalloc(माप(*korg1212), GFP_KERNEL);
        अगर (korg1212 == शून्य) अणु
		pci_disable_device(pci);
                वापस -ENOMEM;
	पूर्ण

	korg1212->card = card;
	korg1212->pci = pci;

        init_रुकोqueue_head(&korg1212->रुको);
        spin_lock_init(&korg1212->lock);
	mutex_init(&korg1212->खोलो_mutex);
	समयr_setup(&korg1212->समयr, snd_korg1212_समयr_func, 0);

        korg1212->irq = -1;
        korg1212->clkSource = K1212_CLKIDX_Local;
        korg1212->clkRate = 44100;
        korg1212->inIRQ = 0;
        korg1212->running = 0;
	korg1212->खोलोcnt = 0;
	korg1212->playcnt = 0;
	korg1212->setcnt = 0;
	korg1212->totalerrorcnt = 0;
	korg1212->playback_pid = -1;
	korg1212->capture_pid = -1;
        snd_korg1212_setCardState(korg1212, K1212_STATE_UNINITIALIZED);
        korg1212->idleMonitorOn = 0;
        korg1212->clkSrcRate = K1212_CLKIDX_LocalAt44_1K;
        korg1212->leftADCInSens = k1212MaxADCSens;
        korg1212->rightADCInSens = k1212MaxADCSens;

        क्रम (i=0; i<kAudioChannels; i++)
                korg1212->volumePhase[i] = 0;

	अगर ((err = pci_request_regions(pci, "korg1212")) < 0) अणु
		kमुक्त(korg1212);
		pci_disable_device(pci);
		वापस err;
	पूर्ण

        korg1212->iomem = pci_resource_start(korg1212->pci, 0);
        korg1212->ioport = pci_resource_start(korg1212->pci, 1);
        korg1212->iomem2 = pci_resource_start(korg1212->pci, 2);

	iomem_size = pci_resource_len(korg1212->pci, 0);
	ioport_size = pci_resource_len(korg1212->pci, 1);
	iomem2_size = pci_resource_len(korg1212->pci, 2);

        K1212_DEBUG_PRINTK("K1212_DEBUG: resources:\n"
                   "    iomem = 0x%lx (%d)\n"
		   "    ioport  = 0x%lx (%d)\n"
                   "    iomem = 0x%lx (%d)\n"
		   "    [%s]\n",
		   korg1212->iomem, iomem_size,
		   korg1212->ioport, ioport_size,
		   korg1212->iomem2, iomem2_size,
		   stateName[korg1212->cardState]);

        अगर ((korg1212->iobase = ioremap(korg1212->iomem, iomem_size)) == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR "korg1212: unable to remap memory region 0x%lx-0x%lx\n", korg1212->iomem,
                           korg1212->iomem + iomem_size - 1);
                snd_korg1212_मुक्त(korg1212);
                वापस -EBUSY;
        पूर्ण

        err = request_irq(pci->irq, snd_korg1212_पूर्णांकerrupt,
                          IRQF_SHARED,
                          KBUILD_MODNAME, korg1212);

        अगर (err) अणु
		snd_prपूर्णांकk(KERN_ERR "korg1212: unable to grab IRQ %d\n", pci->irq);
                snd_korg1212_मुक्त(korg1212);
                वापस -EBUSY;
        पूर्ण

        korg1212->irq = pci->irq;
	card->sync_irq = korg1212->irq;

	pci_set_master(korg1212->pci);

        korg1212->statusRegPtr = (u32 __iomem *) (korg1212->iobase + STATUS_REG_OFFSET);
        korg1212->outDoorbellPtr = (u32 __iomem *) (korg1212->iobase + OUT_DOORBELL_OFFSET);
        korg1212->inDoorbellPtr = (u32 __iomem *) (korg1212->iobase + IN_DOORBELL_OFFSET);
        korg1212->mailbox0Ptr = (u32 __iomem *) (korg1212->iobase + MAILBOX0_OFFSET);
        korg1212->mailbox1Ptr = (u32 __iomem *) (korg1212->iobase + MAILBOX1_OFFSET);
        korg1212->mailbox2Ptr = (u32 __iomem *) (korg1212->iobase + MAILBOX2_OFFSET);
        korg1212->mailbox3Ptr = (u32 __iomem *) (korg1212->iobase + MAILBOX3_OFFSET);
        korg1212->controlRegPtr = (u32 __iomem *) (korg1212->iobase + PCI_CONTROL_OFFSET);
        korg1212->sensRegPtr = (u16 __iomem *) (korg1212->iobase + SENS_CONTROL_OFFSET);
        korg1212->idRegPtr = (u32 __iomem *) (korg1212->iobase + DEV_VEND_ID_OFFSET);

        K1212_DEBUG_PRINTK("K1212_DEBUG: card registers:\n"
                   "    Status register = 0x%p\n"
                   "    OutDoorbell     = 0x%p\n"
                   "    InDoorbell      = 0x%p\n"
                   "    Mailbox0        = 0x%p\n"
                   "    Mailbox1        = 0x%p\n"
                   "    Mailbox2        = 0x%p\n"
                   "    Mailbox3        = 0x%p\n"
                   "    ControlReg      = 0x%p\n"
                   "    SensReg         = 0x%p\n"
                   "    IDReg           = 0x%p\n"
		   "    [%s]\n",
                   korg1212->statusRegPtr,
		   korg1212->outDoorbellPtr,
		   korg1212->inDoorbellPtr,
                   korg1212->mailbox0Ptr,
                   korg1212->mailbox1Ptr,
                   korg1212->mailbox2Ptr,
                   korg1212->mailbox3Ptr,
                   korg1212->controlRegPtr,
                   korg1212->sensRegPtr,
                   korg1212->idRegPtr,
		   stateName[korg1212->cardState]);

	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				माप(काष्ठा KorgSharedBuffer), &korg1212->dma_shared) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "korg1212: can not allocate shared buffer memory (%zd bytes)\n", माप(काष्ठा KorgSharedBuffer));
                snd_korg1212_मुक्त(korg1212);
                वापस -ENOMEM;
        पूर्ण
        korg1212->sharedBufferPtr = (काष्ठा KorgSharedBuffer *)korg1212->dma_shared.area;
        korg1212->sharedBufferPhy = korg1212->dma_shared.addr;

        K1212_DEBUG_PRINTK("K1212_DEBUG: Shared Buffer Area = 0x%p (0x%08lx), %d bytes\n", korg1212->sharedBufferPtr, korg1212->sharedBufferPhy, माप(काष्ठा KorgSharedBuffer));

#अगर_अघोषित K1212_LARGEALLOC

        korg1212->DataBufsSize = माप(काष्ठा KorgAudioBuffer) * kNumBuffers;

	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				korg1212->DataBufsSize, &korg1212->dma_play) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "korg1212: can not allocate play data buffer memory (%d bytes)\n", korg1212->DataBufsSize);
                snd_korg1212_मुक्त(korg1212);
                वापस -ENOMEM;
        पूर्ण
	korg1212->playDataBufsPtr = (काष्ठा KorgAudioBuffer *)korg1212->dma_play.area;
	korg1212->PlayDataPhy = korg1212->dma_play.addr;

        K1212_DEBUG_PRINTK("K1212_DEBUG: Play Data Area = 0x%p (0x%08x), %d bytes\n",
		korg1212->playDataBufsPtr, korg1212->PlayDataPhy, korg1212->DataBufsSize);

	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				korg1212->DataBufsSize, &korg1212->dma_rec) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "korg1212: can not allocate record data buffer memory (%d bytes)\n", korg1212->DataBufsSize);
                snd_korg1212_मुक्त(korg1212);
                वापस -ENOMEM;
        पूर्ण
        korg1212->recordDataBufsPtr = (काष्ठा KorgAudioBuffer *)korg1212->dma_rec.area;
        korg1212->RecDataPhy = korg1212->dma_rec.addr;

        K1212_DEBUG_PRINTK("K1212_DEBUG: Record Data Area = 0x%p (0x%08x), %d bytes\n",
		korg1212->recordDataBufsPtr, korg1212->RecDataPhy, korg1212->DataBufsSize);

#अन्यथा // K1212_LARGEALLOC

        korg1212->recordDataBufsPtr = korg1212->sharedBufferPtr->recordDataBufs;
        korg1212->playDataBufsPtr = korg1212->sharedBufferPtr->playDataBufs;
        korg1212->PlayDataPhy = (u32) &((काष्ठा KorgSharedBuffer *) korg1212->sharedBufferPhy)->playDataBufs;
        korg1212->RecDataPhy  = (u32) &((काष्ठा KorgSharedBuffer *) korg1212->sharedBufferPhy)->recordDataBufs;

#पूर्ण_अगर // K1212_LARGEALLOC

        korg1212->VolumeTablePhy = korg1212->sharedBufferPhy +
		दुरत्व(काष्ठा KorgSharedBuffer, volumeData);
        korg1212->RoutingTablePhy = korg1212->sharedBufferPhy +
		दुरत्व(काष्ठा KorgSharedBuffer, routeData);
        korg1212->AdatTimeCodePhy = korg1212->sharedBufferPhy +
		दुरत्व(काष्ठा KorgSharedBuffer, AdatTimeCode);

	err = request_firmware(&dsp_code, "korg/k1212.dsp", &pci->dev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "firmware not available\n");
		snd_korg1212_मुक्त(korg1212);
		वापस err;
	पूर्ण

	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				dsp_code->size, &korg1212->dma_dsp) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "korg1212: cannot allocate dsp code memory (%zd bytes)\n", dsp_code->size);
                snd_korg1212_मुक्त(korg1212);
		release_firmware(dsp_code);
                वापस -ENOMEM;
        पूर्ण

        K1212_DEBUG_PRINTK("K1212_DEBUG: DSP Code area = 0x%p (0x%08x) %d bytes [%s]\n",
		   korg1212->dma_dsp.area, korg1212->dma_dsp.addr, dsp_code->size,
		   stateName[korg1212->cardState]);

	स_नकल(korg1212->dma_dsp.area, dsp_code->data, dsp_code->size);

	release_firmware(dsp_code);

	rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_RebootCard, 0, 0, 0, 0);

	अगर (rc)
		K1212_DEBUG_PRINTK("K1212_DEBUG: Reboot Card - RC = %d [%s]\n", rc, stateName[korg1212->cardState]);

        अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, korg1212, &ops)) < 0) अणु
                snd_korg1212_मुक्त(korg1212);
                वापस err;
        पूर्ण
        
	snd_korg1212_EnableCardInterrupts(korg1212);

	mdelay(CARD_BOOT_DELAY_IN_MS);

        अगर (snd_korg1212_करोwnloadDSPCode(korg1212))
        	वापस -EBUSY;

        K1212_DEBUG_PRINTK("korg1212: dspMemPhy = %08x U[%08x], "
               "PlayDataPhy = %08x L[%08x]\n"
	       "korg1212: RecDataPhy = %08x L[%08x], "
               "VolumeTablePhy = %08x L[%08x]\n"
               "korg1212: RoutingTablePhy = %08x L[%08x], "
               "AdatTimeCodePhy = %08x L[%08x]\n",
	       (पूर्णांक)korg1212->dma_dsp.addr,    UpperWordSwap(korg1212->dma_dsp.addr),
               korg1212->PlayDataPhy,     LowerWordSwap(korg1212->PlayDataPhy),
               korg1212->RecDataPhy,      LowerWordSwap(korg1212->RecDataPhy),
               korg1212->VolumeTablePhy,  LowerWordSwap(korg1212->VolumeTablePhy),
               korg1212->RoutingTablePhy, LowerWordSwap(korg1212->RoutingTablePhy),
               korg1212->AdatTimeCodePhy, LowerWordSwap(korg1212->AdatTimeCodePhy));

        अगर ((err = snd_pcm_new(korg1212->card, "korg1212", 0, 1, 1, &korg1212->pcm)) < 0)
                वापस err;

	korg1212->pcm->निजी_data = korg1212;
        korg1212->pcm->निजी_मुक्त = snd_korg1212_मुक्त_pcm;
        म_नकल(korg1212->pcm->name, "korg1212");

        snd_pcm_set_ops(korg1212->pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_korg1212_playback_ops);
        
	snd_pcm_set_ops(korg1212->pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_korg1212_capture_ops);

	korg1212->pcm->info_flags = SNDRV_PCM_INFO_JOINT_DUPLEX;

        क्रम (i = 0; i < ARRAY_SIZE(snd_korg1212_controls); i++) अणु
                err = snd_ctl_add(korg1212->card, snd_ctl_new1(&snd_korg1212_controls[i], korg1212));
                अगर (err < 0)
                        वापस err;
        पूर्ण

        snd_korg1212_proc_init(korg1212);
        
        * rchip = korg1212;
	वापस 0;

पूर्ण

/*
 * Card initialisation
 */

अटल पूर्णांक
snd_korg1212_probe(काष्ठा pci_dev *pci,
		स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_korg1212 *korg1212;
	काष्ठा snd_card *card;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS) अणु
		वापस -ENODEV;
	पूर्ण
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण
	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

        अगर ((err = snd_korg1212_create(card, pci, &korg1212)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	म_नकल(card->driver, "korg1212");
	म_नकल(card->लघुname, "korg1212");
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d", card->लघुname,
		korg1212->iomem, korg1212->irq);

        K1212_DEBUG_PRINTK("K1212_DEBUG: %s\n", card->दीर्घname);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_korg1212_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver korg1212_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_korg1212_ids,
	.probe = snd_korg1212_probe,
	.हटाओ = snd_korg1212_हटाओ,
पूर्ण;

module_pci_driver(korg1212_driver);
