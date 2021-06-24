<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम RME Hammerfall DSP audio पूर्णांकerface(s)
 *
 *      Copyright (c) 2002  Paul Davis
 *                          Marcus Andersson
 *                          Thomas Charbonnel
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/math64.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पन.स>
#समावेश <linux/nospec.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/info.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/initval.h>
#समावेश <sound/hdsp.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/current.h>

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for RME Hammerfall DSP interface.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for RME Hammerfall DSP interface.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable/disable specific Hammerfall DSP soundcards.");
MODULE_AUTHOR("Paul Davis <paul@linuxaudiosystems.com>, Marcus Andersson, Thomas Charbonnel <thomas@undata.org>");
MODULE_DESCRIPTION("RME Hammerfall DSP");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("rpm_firmware.bin");
MODULE_FIRMWARE("multiface_firmware.bin");
MODULE_FIRMWARE("multiface_firmware_rev11.bin");
MODULE_FIRMWARE("digiface_firmware.bin");
MODULE_FIRMWARE("digiface_firmware_rev11.bin");

#घोषणा HDSP_MAX_CHANNELS        26
#घोषणा HDSP_MAX_DS_CHANNELS     14
#घोषणा HDSP_MAX_QS_CHANNELS     8
#घोषणा DIGIFACE_SS_CHANNELS     26
#घोषणा DIGIFACE_DS_CHANNELS     14
#घोषणा MULTIFACE_SS_CHANNELS    18
#घोषणा MULTIFACE_DS_CHANNELS    14
#घोषणा H9652_SS_CHANNELS        26
#घोषणा H9652_DS_CHANNELS        14
/* This करोes not include possible Analog Extension Boards
   AEBs are detected at card initialization
*/
#घोषणा H9632_SS_CHANNELS	 12
#घोषणा H9632_DS_CHANNELS	 8
#घोषणा H9632_QS_CHANNELS	 4
#घोषणा RPM_CHANNELS             6

/* Write रेजिस्टरs. These are defined as byte-offsets from the iobase value.
 */
#घोषणा HDSP_resetPoपूर्णांकer               0
#घोषणा HDSP_freqReg			0
#घोषणा HDSP_outputBufferAddress	32
#घोषणा HDSP_inputBufferAddress		36
#घोषणा HDSP_controlRegister		64
#घोषणा HDSP_पूर्णांकerruptConfirmation	96
#घोषणा HDSP_outputEnable	  	128
#घोषणा HDSP_control2Reg		256
#घोषणा HDSP_midiDataOut0  		352
#घोषणा HDSP_midiDataOut1  		356
#घोषणा HDSP_fअगरoData  			368
#घोषणा HDSP_inputEnable	 	384

/* Read रेजिस्टरs. These are defined as byte-offsets from the iobase value
 */

#घोषणा HDSP_statusRegister    0
#घोषणा HDSP_समयcode        128
#घोषणा HDSP_status2Register 192
#घोषणा HDSP_midiDataIn0     360
#घोषणा HDSP_midiDataIn1     364
#घोषणा HDSP_midiStatusOut0  384
#घोषणा HDSP_midiStatusOut1  388
#घोषणा HDSP_midiStatusIn0   392
#घोषणा HDSP_midiStatusIn1   396
#घोषणा HDSP_fअगरoStatus      400

/* the meters are regular i/o-mapped रेजिस्टरs, but offset
   considerably from the rest. the peak रेजिस्टरs are reset
   when पढ़ो; the least-signअगरicant 4 bits are full-scale counters;
   the actual peak value is in the most-signअगरicant 24 bits.
*/

#घोषणा HDSP_playbackPeakLevel  4096  /* 26 * 32 bit values */
#घोषणा HDSP_inputPeakLevel     4224  /* 26 * 32 bit values */
#घोषणा HDSP_outputPeakLevel    4352  /* (26+2) * 32 bit values */
#घोषणा HDSP_playbackRmsLevel   4612  /* 26 * 64 bit values */
#घोषणा HDSP_inputRmsLevel      4868  /* 26 * 64 bit values */


/* This is क्रम H9652 cards
   Peak values are पढ़ो करोwnward from the base
   Rms values are पढ़ो upward
   There are rms values क्रम the outमाला_दो too
   26*3 values are पढ़ो in ss mode
   14*3 in ds mode, with no gap between values
*/
#घोषणा HDSP_9652_peakBase	7164
#घोषणा HDSP_9652_rmsBase	4096

/* c.f. the hdsp_9632_meters_t काष्ठा */
#घोषणा HDSP_9632_metersBase	4096

#घोषणा HDSP_IO_EXTENT     7168

/* control2 रेजिस्टर bits */

#घोषणा HDSP_TMS                0x01
#घोषणा HDSP_TCK                0x02
#घोषणा HDSP_TDI                0x04
#घोषणा HDSP_JTAG               0x08
#घोषणा HDSP_PWDN               0x10
#घोषणा HDSP_PROGRAM	        0x020
#घोषणा HDSP_CONFIG_MODE_0	0x040
#घोषणा HDSP_CONFIG_MODE_1	0x080
#घोषणा HDSP_VERSION_BIT	(0x100 | HDSP_S_LOAD)
#घोषणा HDSP_BIGENDIAN_MODE     0x200
#घोषणा HDSP_RD_MULTIPLE        0x400
#घोषणा HDSP_9652_ENABLE_MIXER  0x800
#घोषणा HDSP_S200		0x800
#घोषणा HDSP_S300		(0x100 | HDSP_S200) /* dummy, purpose of 0x100 unknown */
#घोषणा HDSP_CYCLIC_MODE	0x1000
#घोषणा HDSP_TDO                0x10000000

#घोषणा HDSP_S_PROGRAM	    (HDSP_CYCLIC_MODE|HDSP_PROGRAM|HDSP_CONFIG_MODE_0)
#घोषणा HDSP_S_LOAD	    (HDSP_CYCLIC_MODE|HDSP_PROGRAM|HDSP_CONFIG_MODE_1)

/* Control Register bits */

#घोषणा HDSP_Start                (1<<0)  /* start engine */
#घोषणा HDSP_Latency0             (1<<1)  /* buffer size = 2^n where n is defined by Latencyअणु2,1,0पूर्ण */
#घोषणा HDSP_Latency1             (1<<2)  /* [ see above ] */
#घोषणा HDSP_Latency2             (1<<3)  /* [ see above ] */
#घोषणा HDSP_ClockModeMaster      (1<<4)  /* 1=Master, 0=Slave/Autosync */
#घोषणा HDSP_AudioInterruptEnable (1<<5)  /* what करो you think ? */
#घोषणा HDSP_Frequency0           (1<<6)  /* 0=44.1kHz/88.2kHz/176.4kHz 1=48kHz/96kHz/192kHz */
#घोषणा HDSP_Frequency1           (1<<7)  /* 0=32kHz/64kHz/128kHz */
#घोषणा HDSP_DoubleSpeed          (1<<8)  /* 0=normal speed, 1=द्विगुन speed */
#घोषणा HDSP_SPDIFProfessional    (1<<9)  /* 0=consumer, 1=professional */
#घोषणा HDSP_SPDIFEmphasis        (1<<10) /* 0=none, 1=on */
#घोषणा HDSP_SPDIFNonAudio        (1<<11) /* 0=off, 1=on */
#घोषणा HDSP_SPDIFOpticalOut      (1<<12) /* 1=use 1st ADAT connector क्रम SPDIF, 0=करो not */
#घोषणा HDSP_SyncRef2             (1<<13)
#घोषणा HDSP_SPDIFInputSelect0    (1<<14)
#घोषणा HDSP_SPDIFInputSelect1    (1<<15)
#घोषणा HDSP_SyncRef0             (1<<16)
#घोषणा HDSP_SyncRef1             (1<<17)
#घोषणा HDSP_AnalogExtensionBoard (1<<18) /* For H9632 cards */
#घोषणा HDSP_XLRBreakoutCable     (1<<20) /* For H9632 cards */
#घोषणा HDSP_Midi0InterruptEnable (1<<22)
#घोषणा HDSP_Midi1InterruptEnable (1<<23)
#घोषणा HDSP_LineOut              (1<<24)
#घोषणा HDSP_ADGain0		  (1<<25) /* From here : H9632 specअगरic */
#घोषणा HDSP_ADGain1		  (1<<26)
#घोषणा HDSP_DAGain0		  (1<<27)
#घोषणा HDSP_DAGain1		  (1<<28)
#घोषणा HDSP_PhoneGain0		  (1<<29)
#घोषणा HDSP_PhoneGain1		  (1<<30)
#घोषणा HDSP_QuadSpeed	  	  (1<<31)

/* RPM uses some of the रेजिस्टरs क्रम special purposes */
#घोषणा HDSP_RPM_Inp12            0x04A00
#घोषणा HDSP_RPM_Inp12_Phon_6dB   0x00800  /* Dolby */
#घोषणा HDSP_RPM_Inp12_Phon_0dB   0x00000  /* .. */
#घोषणा HDSP_RPM_Inp12_Phon_n6dB  0x04000  /* inp_0 */
#घोषणा HDSP_RPM_Inp12_Line_0dB   0x04200  /* Dolby+PRO */
#घोषणा HDSP_RPM_Inp12_Line_n6dB  0x00200  /* PRO */

#घोषणा HDSP_RPM_Inp34            0x32000
#घोषणा HDSP_RPM_Inp34_Phon_6dB   0x20000  /* SyncRef1 */
#घोषणा HDSP_RPM_Inp34_Phon_0dB   0x00000  /* .. */
#घोषणा HDSP_RPM_Inp34_Phon_n6dB  0x02000  /* SyncRef2 */
#घोषणा HDSP_RPM_Inp34_Line_0dB   0x30000  /* SyncRef1+SyncRef0 */
#घोषणा HDSP_RPM_Inp34_Line_n6dB  0x10000  /* SyncRef0 */

#घोषणा HDSP_RPM_Bypass           0x01000

#घोषणा HDSP_RPM_Disconnect       0x00001

#घोषणा HDSP_ADGainMask       (HDSP_ADGain0|HDSP_ADGain1)
#घोषणा HDSP_ADGainMinus10dBV  HDSP_ADGainMask
#घोषणा HDSP_ADGainPlus4dBu   (HDSP_ADGain0)
#घोषणा HDSP_ADGainLowGain     0

#घोषणा HDSP_DAGainMask         (HDSP_DAGain0|HDSP_DAGain1)
#घोषणा HDSP_DAGainHighGain      HDSP_DAGainMask
#घोषणा HDSP_DAGainPlus4dBu     (HDSP_DAGain0)
#घोषणा HDSP_DAGainMinus10dBV    0

#घोषणा HDSP_PhoneGainMask      (HDSP_PhoneGain0|HDSP_PhoneGain1)
#घोषणा HDSP_PhoneGain0dB        HDSP_PhoneGainMask
#घोषणा HDSP_PhoneGainMinus6dB  (HDSP_PhoneGain0)
#घोषणा HDSP_PhoneGainMinus12dB  0

#घोषणा HDSP_LatencyMask    (HDSP_Latency0|HDSP_Latency1|HDSP_Latency2)
#घोषणा HDSP_FrequencyMask  (HDSP_Frequency0|HDSP_Frequency1|HDSP_DoubleSpeed|HDSP_QuadSpeed)

#घोषणा HDSP_SPDIFInputMask    (HDSP_SPDIFInputSelect0|HDSP_SPDIFInputSelect1)
#घोषणा HDSP_SPDIFInputADAT1    0
#घोषणा HDSP_SPDIFInputCoaxial (HDSP_SPDIFInputSelect0)
#घोषणा HDSP_SPDIFInputCdrom   (HDSP_SPDIFInputSelect1)
#घोषणा HDSP_SPDIFInputAES     (HDSP_SPDIFInputSelect0|HDSP_SPDIFInputSelect1)

#घोषणा HDSP_SyncRefMask        (HDSP_SyncRef0|HDSP_SyncRef1|HDSP_SyncRef2)
#घोषणा HDSP_SyncRef_ADAT1       0
#घोषणा HDSP_SyncRef_ADAT2      (HDSP_SyncRef0)
#घोषणा HDSP_SyncRef_ADAT3      (HDSP_SyncRef1)
#घोषणा HDSP_SyncRef_SPDIF      (HDSP_SyncRef0|HDSP_SyncRef1)
#घोषणा HDSP_SyncRef_WORD       (HDSP_SyncRef2)
#घोषणा HDSP_SyncRef_ADAT_SYNC  (HDSP_SyncRef0|HDSP_SyncRef2)

/* Sample Clock Sources */

#घोषणा HDSP_CLOCK_SOURCE_AUTOSYNC           0
#घोषणा HDSP_CLOCK_SOURCE_INTERNAL_32KHZ     1
#घोषणा HDSP_CLOCK_SOURCE_INTERNAL_44_1KHZ   2
#घोषणा HDSP_CLOCK_SOURCE_INTERNAL_48KHZ     3
#घोषणा HDSP_CLOCK_SOURCE_INTERNAL_64KHZ     4
#घोषणा HDSP_CLOCK_SOURCE_INTERNAL_88_2KHZ   5
#घोषणा HDSP_CLOCK_SOURCE_INTERNAL_96KHZ     6
#घोषणा HDSP_CLOCK_SOURCE_INTERNAL_128KHZ    7
#घोषणा HDSP_CLOCK_SOURCE_INTERNAL_176_4KHZ  8
#घोषणा HDSP_CLOCK_SOURCE_INTERNAL_192KHZ    9

/* Preferred sync reference choices - used by "pref_sync_ref" control चयन */

#घोषणा HDSP_SYNC_FROM_WORD      0
#घोषणा HDSP_SYNC_FROM_SPDIF     1
#घोषणा HDSP_SYNC_FROM_ADAT1     2
#घोषणा HDSP_SYNC_FROM_ADAT_SYNC 3
#घोषणा HDSP_SYNC_FROM_ADAT2     4
#घोषणा HDSP_SYNC_FROM_ADAT3     5

/* SyncCheck status */

#घोषणा HDSP_SYNC_CHECK_NO_LOCK 0
#घोषणा HDSP_SYNC_CHECK_LOCK    1
#घोषणा HDSP_SYNC_CHECK_SYNC	2

/* AutoSync references - used by "autosync_ref" control चयन */

#घोषणा HDSP_AUTOSYNC_FROM_WORD      0
#घोषणा HDSP_AUTOSYNC_FROM_ADAT_SYNC 1
#घोषणा HDSP_AUTOSYNC_FROM_SPDIF     2
#घोषणा HDSP_AUTOSYNC_FROM_NONE	     3
#घोषणा HDSP_AUTOSYNC_FROM_ADAT1     4
#घोषणा HDSP_AUTOSYNC_FROM_ADAT2     5
#घोषणा HDSP_AUTOSYNC_FROM_ADAT3     6

/* Possible sources of S/PDIF input */

#घोषणा HDSP_SPDIFIN_OPTICAL  0	/* optical  (ADAT1) */
#घोषणा HDSP_SPDIFIN_COAXIAL  1	/* coaxial (RCA) */
#घोषणा HDSP_SPDIFIN_INTERNAL 2	/* पूर्णांकernal (CDROM) */
#घोषणा HDSP_SPDIFIN_AES      3 /* xlr क्रम H9632 (AES)*/

#घोषणा HDSP_Frequency32KHz    HDSP_Frequency0
#घोषणा HDSP_Frequency44_1KHz  HDSP_Frequency1
#घोषणा HDSP_Frequency48KHz    (HDSP_Frequency1|HDSP_Frequency0)
#घोषणा HDSP_Frequency64KHz    (HDSP_DoubleSpeed|HDSP_Frequency0)
#घोषणा HDSP_Frequency88_2KHz  (HDSP_DoubleSpeed|HDSP_Frequency1)
#घोषणा HDSP_Frequency96KHz    (HDSP_DoubleSpeed|HDSP_Frequency1|HDSP_Frequency0)
/* For H9632 cards */
#घोषणा HDSP_Frequency128KHz   (HDSP_QuadSpeed|HDSP_DoubleSpeed|HDSP_Frequency0)
#घोषणा HDSP_Frequency176_4KHz (HDSP_QuadSpeed|HDSP_DoubleSpeed|HDSP_Frequency1)
#घोषणा HDSP_Frequency192KHz   (HDSP_QuadSpeed|HDSP_DoubleSpeed|HDSP_Frequency1|HDSP_Frequency0)
/* RME says n = 104857600000000, but in the winकरोws MADI driver, I see:
	वापस 104857600000000 / rate; // 100 MHz
	वापस 110100480000000 / rate; // 105 MHz
*/
#घोषणा DDS_NUMERATOR 104857600000000ULL;  /*  =  2^20 * 10^8 */

#घोषणा hdsp_encode_latency(x)       (((x)<<1) & HDSP_LatencyMask)
#घोषणा hdsp_decode_latency(x)       (((x) & HDSP_LatencyMask)>>1)

#घोषणा hdsp_encode_spdअगर_in(x) (((x)&0x3)<<14)
#घोषणा hdsp_decode_spdअगर_in(x) (((x)>>14)&0x3)

/* Status Register bits */

#घोषणा HDSP_audioIRQPending    (1<<0)
#घोषणा HDSP_Lock2              (1<<1)     /* this is क्रम Digअगरace and H9652 */
#घोषणा HDSP_spdअगरFrequency3	HDSP_Lock2 /* this is क्रम H9632 only */
#घोषणा HDSP_Lock1              (1<<2)
#घोषणा HDSP_Lock0              (1<<3)
#घोषणा HDSP_SPDIFSync          (1<<4)
#घोषणा HDSP_TimecodeLock       (1<<5)
#घोषणा HDSP_BufferPositionMask 0x000FFC0 /* Bit 6..15 : h/w buffer poपूर्णांकer */
#घोषणा HDSP_Sync2              (1<<16)
#घोषणा HDSP_Sync1              (1<<17)
#घोषणा HDSP_Sync0              (1<<18)
#घोषणा HDSP_DoubleSpeedStatus  (1<<19)
#घोषणा HDSP_ConfigError        (1<<20)
#घोषणा HDSP_DllError           (1<<21)
#घोषणा HDSP_spdअगरFrequency0    (1<<22)
#घोषणा HDSP_spdअगरFrequency1    (1<<23)
#घोषणा HDSP_spdअगरFrequency2    (1<<24)
#घोषणा HDSP_SPDIFErrorFlag     (1<<25)
#घोषणा HDSP_BufferID           (1<<26)
#घोषणा HDSP_TimecodeSync       (1<<27)
#घोषणा HDSP_AEBO          	(1<<28) /* H9632 specअगरic Analog Extension Boards */
#घोषणा HDSP_AEBI		(1<<29) /* 0 = present, 1 = असलent */
#घोषणा HDSP_midi0IRQPending    (1<<30)
#घोषणा HDSP_midi1IRQPending    (1<<31)

#घोषणा HDSP_spdअगरFrequencyMask    (HDSP_spdअगरFrequency0|HDSP_spdअगरFrequency1|HDSP_spdअगरFrequency2)
#घोषणा HDSP_spdअगरFrequencyMask_9632 (HDSP_spdअगरFrequency0|\
				      HDSP_spdअगरFrequency1|\
				      HDSP_spdअगरFrequency2|\
				      HDSP_spdअगरFrequency3)

#घोषणा HDSP_spdअगरFrequency32KHz   (HDSP_spdअगरFrequency0)
#घोषणा HDSP_spdअगरFrequency44_1KHz (HDSP_spdअगरFrequency1)
#घोषणा HDSP_spdअगरFrequency48KHz   (HDSP_spdअगरFrequency0|HDSP_spdअगरFrequency1)

#घोषणा HDSP_spdअगरFrequency64KHz   (HDSP_spdअगरFrequency2)
#घोषणा HDSP_spdअगरFrequency88_2KHz (HDSP_spdअगरFrequency0|HDSP_spdअगरFrequency2)
#घोषणा HDSP_spdअगरFrequency96KHz   (HDSP_spdअगरFrequency2|HDSP_spdअगरFrequency1)

/* This is क्रम H9632 cards */
#घोषणा HDSP_spdअगरFrequency128KHz   (HDSP_spdअगरFrequency0|\
				     HDSP_spdअगरFrequency1|\
				     HDSP_spdअगरFrequency2)
#घोषणा HDSP_spdअगरFrequency176_4KHz HDSP_spdअगरFrequency3
#घोषणा HDSP_spdअगरFrequency192KHz   (HDSP_spdअगरFrequency3|HDSP_spdअगरFrequency0)

/* Status2 Register bits */

#घोषणा HDSP_version0     (1<<0)
#घोषणा HDSP_version1     (1<<1)
#घोषणा HDSP_version2     (1<<2)
#घोषणा HDSP_wc_lock      (1<<3)
#घोषणा HDSP_wc_sync      (1<<4)
#घोषणा HDSP_inp_freq0    (1<<5)
#घोषणा HDSP_inp_freq1    (1<<6)
#घोषणा HDSP_inp_freq2    (1<<7)
#घोषणा HDSP_SelSyncRef0  (1<<8)
#घोषणा HDSP_SelSyncRef1  (1<<9)
#घोषणा HDSP_SelSyncRef2  (1<<10)

#घोषणा HDSP_wc_valid (HDSP_wc_lock|HDSP_wc_sync)

#घोषणा HDSP_प्रणालीFrequencyMask (HDSP_inp_freq0|HDSP_inp_freq1|HDSP_inp_freq2)
#घोषणा HDSP_प्रणालीFrequency32   (HDSP_inp_freq0)
#घोषणा HDSP_प्रणालीFrequency44_1 (HDSP_inp_freq1)
#घोषणा HDSP_प्रणालीFrequency48   (HDSP_inp_freq0|HDSP_inp_freq1)
#घोषणा HDSP_प्रणालीFrequency64   (HDSP_inp_freq2)
#घोषणा HDSP_प्रणालीFrequency88_2 (HDSP_inp_freq0|HDSP_inp_freq2)
#घोषणा HDSP_प्रणालीFrequency96   (HDSP_inp_freq1|HDSP_inp_freq2)
/* FIXME : more values क्रम 9632 cards ? */

#घोषणा HDSP_SelSyncRefMask        (HDSP_SelSyncRef0|HDSP_SelSyncRef1|HDSP_SelSyncRef2)
#घोषणा HDSP_SelSyncRef_ADAT1      0
#घोषणा HDSP_SelSyncRef_ADAT2      (HDSP_SelSyncRef0)
#घोषणा HDSP_SelSyncRef_ADAT3      (HDSP_SelSyncRef1)
#घोषणा HDSP_SelSyncRef_SPDIF      (HDSP_SelSyncRef0|HDSP_SelSyncRef1)
#घोषणा HDSP_SelSyncRef_WORD       (HDSP_SelSyncRef2)
#घोषणा HDSP_SelSyncRef_ADAT_SYNC  (HDSP_SelSyncRef0|HDSP_SelSyncRef2)

/* Card state flags */

#घोषणा HDSP_InitializationComplete  (1<<0)
#घोषणा HDSP_FirmwareLoaded	     (1<<1)
#घोषणा HDSP_FirmwareCached	     (1<<2)

/* FIFO रुको बार, defined in terms of 1/10ths of msecs */

#घोषणा HDSP_LONG_WAIT	 5000
#घोषणा HDSP_SHORT_WAIT  30

#घोषणा UNITY_GAIN                       32768
#घोषणा MINUS_अनन्त_GAIN              0

/* the size of a substream (1 mono data stream) */

#घोषणा HDSP_CHANNEL_BUFFER_SAMPLES  (16*1024)
#घोषणा HDSP_CHANNEL_BUFFER_BYTES    (4*HDSP_CHANNEL_BUFFER_SAMPLES)

/* the size of the area we need to allocate क्रम DMA transfers. the
   size is the same regardless of the number of channels - the
   Multअगरace still uses the same memory area.

   Note that we allocate 1 more channel than is apparently needed
   because the h/w seems to ग_लिखो 1 byte beyond the end of the last
   page. Sigh.
*/

#घोषणा HDSP_DMA_AREA_BYTES ((HDSP_MAX_CHANNELS+1) * HDSP_CHANNEL_BUFFER_BYTES)
#घोषणा HDSP_DMA_AREA_KILOBYTES (HDSP_DMA_AREA_BYTES/1024)

#घोषणा HDSP_FIRMWARE_SIZE	(24413 * 4)

काष्ठा hdsp_9632_meters अणु
    u32 input_peak[16];
    u32 playback_peak[16];
    u32 output_peak[16];
    u32 xxx_peak[16];
    u32 padding[64];
    u32 input_rms_low[16];
    u32 playback_rms_low[16];
    u32 output_rms_low[16];
    u32 xxx_rms_low[16];
    u32 input_rms_high[16];
    u32 playback_rms_high[16];
    u32 output_rms_high[16];
    u32 xxx_rms_high[16];
पूर्ण;

काष्ठा hdsp_midi अणु
    काष्ठा hdsp             *hdsp;
    पूर्णांक                      id;
    काष्ठा snd_rawmidi           *rmidi;
    काष्ठा snd_rawmidi_substream *input;
    काष्ठा snd_rawmidi_substream *output;
    अक्षर                     isसमयr; /* समयr in use */
    काष्ठा समयr_list	     समयr;
    spinlock_t               lock;
    पूर्णांक			     pending;
पूर्ण;

काष्ठा hdsp अणु
	spinlock_t            lock;
	काष्ठा snd_pcm_substream *capture_substream;
	काष्ठा snd_pcm_substream *playback_substream;
        काष्ठा hdsp_midi      midi[2];
	काष्ठा work_काष्ठा    midi_work;
	पूर्णांक		      use_midi_work;
	पूर्णांक                   precise_ptr;
	u32                   control_रेजिस्टर;	     /* cached value */
	u32                   control2_रेजिस्टर;     /* cached value */
	u32                   creg_spdअगर;
	u32                   creg_spdअगर_stream;
	पूर्णांक                   घड़ी_source_locked;
	अक्षर                 *card_name;	 /* digअगरace/multअगरace/rpm */
	क्रमागत HDSP_IO_Type     io_type;               /* ditto, but क्रम code use */
        अचिन्हित लघु        firmware_rev;
	अचिन्हित लघु	      state;		     /* stores state bits */
	स्थिर काष्ठा firmware *firmware;
	u32                  *fw_uploaded;
	माप_प्रकार                period_bytes; 	     /* guess what this is */
	अचिन्हित अक्षर	      max_channels;
	अचिन्हित अक्षर	      qs_in_channels;	     /* quad speed mode क्रम H9632 */
	अचिन्हित अक्षर         ds_in_channels;
	अचिन्हित अक्षर         ss_in_channels;	    /* dअगरferent क्रम multअगरace/digअगरace */
	अचिन्हित अक्षर	      qs_out_channels;
	अचिन्हित अक्षर         ds_out_channels;
	अचिन्हित अक्षर         ss_out_channels;
	u32                   io_loopback;          /* output loopback channel states*/

	काष्ठा snd_dma_buffer capture_dma_buf;
	काष्ठा snd_dma_buffer playback_dma_buf;
	अचिन्हित अक्षर        *capture_buffer;	    /* suitably aligned address */
	अचिन्हित अक्षर        *playback_buffer;	    /* suitably aligned address */

	pid_t                 capture_pid;
	pid_t                 playback_pid;
	पूर्णांक                   running;
	पूर्णांक                   प्रणाली_sample_rate;
	स्थिर अक्षर           *channel_map;
	पूर्णांक                   dev;
	पूर्णांक                   irq;
	अचिन्हित दीर्घ         port;
        व्योम __iomem         *iobase;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_hwdep          *hwdep;
	काष्ठा pci_dev       *pci;
	काष्ठा snd_kcontrol *spdअगर_ctl;
        अचिन्हित लघु        mixer_matrix[HDSP_MATRIX_MIXER_SIZE];
	अचिन्हित पूर्णांक          dds_value; /* last value written to freq रेजिस्टर */
पूर्ण;

/* These tables map the ALSA channels 1..N to the channels that we
   need to use in order to find the relevant channel buffer. RME
   refer to this kind of mapping as between "the ADAT channel and
   the DMA channel." We index it using the logical audio channel,
   and the value is the DMA channel (i.e. channel buffer number)
   where the data क्रम that channel can be पढ़ो/written from/to.
*/

अटल स्थिर अक्षर channel_map_df_ss[HDSP_MAX_CHANNELS] = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25
पूर्ण;

अटल स्थिर अक्षर channel_map_mf_ss[HDSP_MAX_CHANNELS] = अणु /* Multअगरace */
	/* Analog */
	0, 1, 2, 3, 4, 5, 6, 7,
	/* ADAT 2 */
	16, 17, 18, 19, 20, 21, 22, 23,
	/* SPDIF */
	24, 25,
	-1, -1, -1, -1, -1, -1, -1, -1
पूर्ण;

अटल स्थिर अक्षर channel_map_ds[HDSP_MAX_CHANNELS] = अणु
	/* ADAT channels are remapped */
	1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23,
	/* channels 12 and 13 are S/PDIF */
	24, 25,
	/* others करोn't exist */
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
पूर्ण;

अटल स्थिर अक्षर channel_map_H9632_ss[HDSP_MAX_CHANNELS] = अणु
	/* ADAT channels */
	0, 1, 2, 3, 4, 5, 6, 7,
	/* SPDIF */
	8, 9,
	/* Analog */
	10, 11,
	/* AO4S-192 and AI4S-192 extension boards */
	12, 13, 14, 15,
	/* others करोn't exist */
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1
पूर्ण;

अटल स्थिर अक्षर channel_map_H9632_ds[HDSP_MAX_CHANNELS] = अणु
	/* ADAT */
	1, 3, 5, 7,
	/* SPDIF */
	8, 9,
	/* Analog */
	10, 11,
	/* AO4S-192 and AI4S-192 extension boards */
	12, 13, 14, 15,
	/* others करोn't exist */
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1
पूर्ण;

अटल स्थिर अक्षर channel_map_H9632_qs[HDSP_MAX_CHANNELS] = अणु
	/* ADAT is disabled in this mode */
	/* SPDIF */
	8, 9,
	/* Analog */
	10, 11,
	/* AO4S-192 and AI4S-192 extension boards */
	12, 13, 14, 15,
	/* others करोn't exist */
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1
पूर्ण;

अटल पूर्णांक snd_hammerfall_get_buffer(काष्ठा pci_dev *pci, काष्ठा snd_dma_buffer *dmab, माप_प्रकार size)
अणु
	वापस snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev, size, dmab);
पूर्ण

अटल व्योम snd_hammerfall_मुक्त_buffer(काष्ठा snd_dma_buffer *dmab, काष्ठा pci_dev *pci)
अणु
	अगर (dmab->area)
		snd_dma_मुक्त_pages(dmab);
पूर्ण


अटल स्थिर काष्ठा pci_device_id snd_hdsp_ids[] = अणु
	अणु
		.venकरोr = PCI_VENDOR_ID_XILINX,
		.device = PCI_DEVICE_ID_XILINX_HAMMERFALL_DSP,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	पूर्ण, /* RME Hammerfall-DSP */
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_hdsp_ids);

/* prototypes */
अटल पूर्णांक snd_hdsp_create_alsa_devices(काष्ठा snd_card *card, काष्ठा hdsp *hdsp);
अटल पूर्णांक snd_hdsp_create_pcm(काष्ठा snd_card *card, काष्ठा hdsp *hdsp);
अटल पूर्णांक snd_hdsp_enable_io (काष्ठा hdsp *hdsp);
अटल व्योम snd_hdsp_initialize_midi_flush (काष्ठा hdsp *hdsp);
अटल व्योम snd_hdsp_initialize_channels (काष्ठा hdsp *hdsp);
अटल पूर्णांक hdsp_fअगरo_रुको(काष्ठा hdsp *hdsp, पूर्णांक count, पूर्णांक समयout);
अटल पूर्णांक hdsp_स्वतःsync_ref(काष्ठा hdsp *hdsp);
अटल पूर्णांक snd_hdsp_set_शेषs(काष्ठा hdsp *hdsp);
अटल व्योम snd_hdsp_9652_enable_mixer (काष्ठा hdsp *hdsp);

अटल पूर्णांक hdsp_playback_to_output_key (काष्ठा hdsp *hdsp, पूर्णांक in, पूर्णांक out)
अणु
	चयन (hdsp->io_type) अणु
	हाल Multअगरace:
	हाल Digअगरace:
	हाल RPM:
	शेष:
		अगर (hdsp->firmware_rev == 0xa)
			वापस (64 * out) + (32 + (in));
		अन्यथा
			वापस (52 * out) + (26 + (in));
	हाल H9632:
		वापस (32 * out) + (16 + (in));
	हाल H9652:
		वापस (52 * out) + (26 + (in));
	पूर्ण
पूर्ण

अटल पूर्णांक hdsp_input_to_output_key (काष्ठा hdsp *hdsp, पूर्णांक in, पूर्णांक out)
अणु
	चयन (hdsp->io_type) अणु
	हाल Multअगरace:
	हाल Digअगरace:
	हाल RPM:
	शेष:
		अगर (hdsp->firmware_rev == 0xa)
			वापस (64 * out) + in;
		अन्यथा
			वापस (52 * out) + in;
	हाल H9632:
		वापस (32 * out) + in;
	हाल H9652:
		वापस (52 * out) + in;
	पूर्ण
पूर्ण

अटल व्योम hdsp_ग_लिखो(काष्ठा hdsp *hdsp, पूर्णांक reg, पूर्णांक val)
अणु
	ग_लिखोl(val, hdsp->iobase + reg);
पूर्ण

अटल अचिन्हित पूर्णांक hdsp_पढ़ो(काष्ठा hdsp *hdsp, पूर्णांक reg)
अणु
	वापस पढ़ोl (hdsp->iobase + reg);
पूर्ण

अटल पूर्णांक hdsp_check_क्रम_iobox (काष्ठा hdsp *hdsp)
अणु
	पूर्णांक i;

	अगर (hdsp->io_type == H9652 || hdsp->io_type == H9632) वापस 0;
	क्रम (i = 0; i < 500; i++) अणु
		अगर (0 == (hdsp_पढ़ो(hdsp, HDSP_statusRegister) &
					HDSP_ConfigError)) अणु
			अगर (i) अणु
				dev_dbg(hdsp->card->dev,
					"IO box found after %d ms\n",
						(20 * i));
			पूर्ण
			वापस 0;
		पूर्ण
		msleep(20);
	पूर्ण
	dev_err(hdsp->card->dev, "no IO box connected!\n");
	hdsp->state &= ~HDSP_FirmwareLoaded;
	वापस -EIO;
पूर्ण

अटल पूर्णांक hdsp_रुको_क्रम_iobox(काष्ठा hdsp *hdsp, अचिन्हित पूर्णांक loops,
			       अचिन्हित पूर्णांक delay)
अणु
	अचिन्हित पूर्णांक i;

	अगर (hdsp->io_type == H9652 || hdsp->io_type == H9632)
		वापस 0;

	क्रम (i = 0; i != loops; ++i) अणु
		अगर (hdsp_पढ़ो(hdsp, HDSP_statusRegister) & HDSP_ConfigError)
			msleep(delay);
		अन्यथा अणु
			dev_dbg(hdsp->card->dev, "iobox found after %ums!\n",
				   i * delay);
			वापस 0;
		पूर्ण
	पूर्ण

	dev_info(hdsp->card->dev, "no IO box connected!\n");
	hdsp->state &= ~HDSP_FirmwareLoaded;
	वापस -EIO;
पूर्ण

अटल पूर्णांक snd_hdsp_load_firmware_from_cache(काष्ठा hdsp *hdsp) अणु

	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	स्थिर u32 *cache;

	अगर (hdsp->fw_uploaded)
		cache = hdsp->fw_uploaded;
	अन्यथा अणु
		अगर (!hdsp->firmware)
			वापस -ENODEV;
		cache = (u32 *)hdsp->firmware->data;
		अगर (!cache)
			वापस -ENODEV;
	पूर्ण

	अगर ((hdsp_पढ़ो (hdsp, HDSP_statusRegister) & HDSP_DllError) != 0) अणु

		dev_info(hdsp->card->dev, "loading firmware\n");

		hdsp_ग_लिखो (hdsp, HDSP_control2Reg, HDSP_S_PROGRAM);
		hdsp_ग_लिखो (hdsp, HDSP_fअगरoData, 0);

		अगर (hdsp_fअगरo_रुको (hdsp, 0, HDSP_LONG_WAIT)) अणु
			dev_info(hdsp->card->dev,
				 "timeout waiting for download preparation\n");
			hdsp_ग_लिखो(hdsp, HDSP_control2Reg, HDSP_S200);
			वापस -EIO;
		पूर्ण

		hdsp_ग_लिखो (hdsp, HDSP_control2Reg, HDSP_S_LOAD);

		क्रम (i = 0; i < HDSP_FIRMWARE_SIZE / 4; ++i) अणु
			hdsp_ग_लिखो(hdsp, HDSP_fअगरoData, cache[i]);
			अगर (hdsp_fअगरo_रुको (hdsp, 127, HDSP_LONG_WAIT)) अणु
				dev_info(hdsp->card->dev,
					 "timeout during firmware loading\n");
				hdsp_ग_लिखो(hdsp, HDSP_control2Reg, HDSP_S200);
				वापस -EIO;
			पूर्ण
		पूर्ण

		hdsp_fअगरo_रुको(hdsp, 3, HDSP_LONG_WAIT);
		hdsp_ग_लिखो(hdsp, HDSP_control2Reg, HDSP_S200);

		ssleep(3);
#अगर_घोषित SNDRV_BIG_ENDIAN
		hdsp->control2_रेजिस्टर = HDSP_BIGENDIAN_MODE;
#अन्यथा
		hdsp->control2_रेजिस्टर = 0;
#पूर्ण_अगर
		hdsp_ग_लिखो (hdsp, HDSP_control2Reg, hdsp->control2_रेजिस्टर);
		dev_info(hdsp->card->dev, "finished firmware loading\n");

	पूर्ण
	अगर (hdsp->state & HDSP_InitializationComplete) अणु
		dev_info(hdsp->card->dev,
			 "firmware loaded from cache, restoring defaults\n");
		spin_lock_irqsave(&hdsp->lock, flags);
		snd_hdsp_set_शेषs(hdsp);
		spin_unlock_irqrestore(&hdsp->lock, flags);
	पूर्ण

	hdsp->state |= HDSP_FirmwareLoaded;

	वापस 0;
पूर्ण

अटल पूर्णांक hdsp_get_iobox_version (काष्ठा hdsp *hdsp)
अणु
	अगर ((hdsp_पढ़ो (hdsp, HDSP_statusRegister) & HDSP_DllError) != 0) अणु

		hdsp_ग_लिखो(hdsp, HDSP_control2Reg, HDSP_S_LOAD);
		hdsp_ग_लिखो(hdsp, HDSP_fअगरoData, 0);

		अगर (hdsp_fअगरo_रुको(hdsp, 0, HDSP_SHORT_WAIT) < 0) अणु
			hdsp_ग_लिखो(hdsp, HDSP_control2Reg, HDSP_S300);
			hdsp_ग_लिखो(hdsp, HDSP_control2Reg, HDSP_S_LOAD);
		पूर्ण

		hdsp_ग_लिखो(hdsp, HDSP_control2Reg, HDSP_S200 | HDSP_PROGRAM);
		hdsp_ग_लिखो (hdsp, HDSP_fअगरoData, 0);
		अगर (hdsp_fअगरo_रुको(hdsp, 0, HDSP_SHORT_WAIT) < 0)
			जाओ set_multi;

		hdsp_ग_लिखो(hdsp, HDSP_control2Reg, HDSP_S_LOAD);
		hdsp_ग_लिखो(hdsp, HDSP_fअगरoData, 0);
		अगर (hdsp_fअगरo_रुको(hdsp, 0, HDSP_SHORT_WAIT) == 0) अणु
			hdsp->io_type = Digअगरace;
			dev_info(hdsp->card->dev, "Digiface found\n");
			वापस 0;
		पूर्ण

		hdsp_ग_लिखो(hdsp, HDSP_control2Reg, HDSP_S300);
		hdsp_ग_लिखो(hdsp, HDSP_control2Reg, HDSP_S_LOAD);
		hdsp_ग_लिखो(hdsp, HDSP_fअगरoData, 0);
		अगर (hdsp_fअगरo_रुको(hdsp, 0, HDSP_SHORT_WAIT) == 0)
			जाओ set_multi;

		hdsp_ग_लिखो(hdsp, HDSP_control2Reg, HDSP_S300);
		hdsp_ग_लिखो(hdsp, HDSP_control2Reg, HDSP_S_LOAD);
		hdsp_ग_लिखो(hdsp, HDSP_fअगरoData, 0);
		अगर (hdsp_fअगरo_रुको(hdsp, 0, HDSP_SHORT_WAIT) < 0)
			जाओ set_multi;

		hdsp->io_type = RPM;
		dev_info(hdsp->card->dev, "RPM found\n");
		वापस 0;
	पूर्ण अन्यथा अणु
		/* firmware was alपढ़ोy loaded, get iobox type */
		अगर (hdsp_पढ़ो(hdsp, HDSP_status2Register) & HDSP_version2)
			hdsp->io_type = RPM;
		अन्यथा अगर (hdsp_पढ़ो(hdsp, HDSP_status2Register) & HDSP_version1)
			hdsp->io_type = Multअगरace;
		अन्यथा
			hdsp->io_type = Digअगरace;
	पूर्ण
	वापस 0;

set_multi:
	hdsp->io_type = Multअगरace;
	dev_info(hdsp->card->dev, "Multiface found\n");
	वापस 0;
पूर्ण


अटल पूर्णांक hdsp_request_fw_loader(काष्ठा hdsp *hdsp);

अटल पूर्णांक hdsp_check_क्रम_firmware (काष्ठा hdsp *hdsp, पूर्णांक load_on_demand)
अणु
	अगर (hdsp->io_type == H9652 || hdsp->io_type == H9632)
		वापस 0;
	अगर ((hdsp_पढ़ो (hdsp, HDSP_statusRegister) & HDSP_DllError) != 0) अणु
		hdsp->state &= ~HDSP_FirmwareLoaded;
		अगर (! load_on_demand)
			वापस -EIO;
		dev_err(hdsp->card->dev, "firmware not present.\n");
		/* try to load firmware */
		अगर (! (hdsp->state & HDSP_FirmwareCached)) अणु
			अगर (! hdsp_request_fw_loader(hdsp))
				वापस 0;
			dev_err(hdsp->card->dev,
				   "No firmware loaded nor cached, please upload firmware.\n");
			वापस -EIO;
		पूर्ण
		अगर (snd_hdsp_load_firmware_from_cache(hdsp) != 0) अणु
			dev_err(hdsp->card->dev,
				   "Firmware loading from cache failed, please upload manually.\n");
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक hdsp_fअगरo_रुको(काष्ठा hdsp *hdsp, पूर्णांक count, पूर्णांक समयout)
अणु
	पूर्णांक i;

	/* the fअगरoStatus रेजिस्टरs reports on how many words
	   are available in the command FIFO.
	*/

	क्रम (i = 0; i < समयout; i++) अणु

		अगर ((पूर्णांक)(hdsp_पढ़ो (hdsp, HDSP_fअगरoStatus) & 0xff) <= count)
			वापस 0;

		/* not very मित्रly, but we only करो this during a firmware
		   load and changing the mixer, so we just put up with it.
		*/

		udelay (100);
	पूर्ण

	dev_warn(hdsp->card->dev,
		 "wait for FIFO status <= %d failed after %d iterations\n",
		    count, समयout);
	वापस -1;
पूर्ण

अटल पूर्णांक hdsp_पढ़ो_gain (काष्ठा hdsp *hdsp, अचिन्हित पूर्णांक addr)
अणु
	अगर (addr >= HDSP_MATRIX_MIXER_SIZE)
		वापस 0;

	वापस hdsp->mixer_matrix[addr];
पूर्ण

अटल पूर्णांक hdsp_ग_लिखो_gain(काष्ठा hdsp *hdsp, अचिन्हित पूर्णांक addr, अचिन्हित लघु data)
अणु
	अचिन्हित पूर्णांक ad;

	अगर (addr >= HDSP_MATRIX_MIXER_SIZE)
		वापस -1;

	अगर (hdsp->io_type == H9652 || hdsp->io_type == H9632) अणु

		/* from martin bjornsen:

		   "You can only ग_लिखो dwords to the
		   mixer memory which contain two
		   mixer values in the low and high
		   word. So अगर you want to change
		   value 0 you have to पढ़ो value 1
		   from the cache and ग_लिखो both to
		   the first dword in the mixer
		   memory."
		*/

		अगर (hdsp->io_type == H9632 && addr >= 512)
			वापस 0;

		अगर (hdsp->io_type == H9652 && addr >= 1352)
			वापस 0;

		hdsp->mixer_matrix[addr] = data;


		/* `addr' addresses a 16-bit wide address, but
		   the address space accessed via hdsp_ग_लिखो
		   uses byte offsets. put another way, addr
		   varies from 0 to 1351, but to access the
		   corresponding memory location, we need
		   to access 0 to 2703 ...
		*/
		ad = addr/2;

		hdsp_ग_लिखो (hdsp, 4096 + (ad*4),
			    (hdsp->mixer_matrix[(addr&0x7fe)+1] << 16) +
			    hdsp->mixer_matrix[addr&0x7fe]);

		वापस 0;

	पूर्ण अन्यथा अणु

		ad = (addr << 16) + data;

		अगर (hdsp_fअगरo_रुको(hdsp, 127, HDSP_LONG_WAIT))
			वापस -1;

		hdsp_ग_लिखो (hdsp, HDSP_fअगरoData, ad);
		hdsp->mixer_matrix[addr] = data;

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_use_is_exclusive(काष्ठा hdsp *hdsp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 1;

	spin_lock_irqsave(&hdsp->lock, flags);
	अगर ((hdsp->playback_pid != hdsp->capture_pid) &&
	    (hdsp->playback_pid >= 0) && (hdsp->capture_pid >= 0))
		ret = 0;
	spin_unlock_irqrestore(&hdsp->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक hdsp_spdअगर_sample_rate(काष्ठा hdsp *hdsp)
अणु
	अचिन्हित पूर्णांक status = hdsp_पढ़ो(hdsp, HDSP_statusRegister);
	अचिन्हित पूर्णांक rate_bits = (status & HDSP_spdअगरFrequencyMask);

	/* For the 9632, the mask is dअगरferent */
	अगर (hdsp->io_type == H9632)
		 rate_bits = (status & HDSP_spdअगरFrequencyMask_9632);

	अगर (status & HDSP_SPDIFErrorFlag)
		वापस 0;

	चयन (rate_bits) अणु
	हाल HDSP_spdअगरFrequency32KHz: वापस 32000;
	हाल HDSP_spdअगरFrequency44_1KHz: वापस 44100;
	हाल HDSP_spdअगरFrequency48KHz: वापस 48000;
	हाल HDSP_spdअगरFrequency64KHz: वापस 64000;
	हाल HDSP_spdअगरFrequency88_2KHz: वापस 88200;
	हाल HDSP_spdअगरFrequency96KHz: वापस 96000;
	हाल HDSP_spdअगरFrequency128KHz:
		अगर (hdsp->io_type == H9632) वापस 128000;
		अवरोध;
	हाल HDSP_spdअगरFrequency176_4KHz:
		अगर (hdsp->io_type == H9632) वापस 176400;
		अवरोध;
	हाल HDSP_spdअगरFrequency192KHz:
		अगर (hdsp->io_type == H9632) वापस 192000;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	dev_warn(hdsp->card->dev,
		 "unknown spdif frequency status; bits = 0x%x, status = 0x%x\n",
		 rate_bits, status);
	वापस 0;
पूर्ण

अटल पूर्णांक hdsp_बाह्यal_sample_rate(काष्ठा hdsp *hdsp)
अणु
	अचिन्हित पूर्णांक status2 = hdsp_पढ़ो(hdsp, HDSP_status2Register);
	अचिन्हित पूर्णांक rate_bits = status2 & HDSP_प्रणालीFrequencyMask;

	/* For the 9632 card, there seems to be no bit क्रम indicating बाह्यal
	 * sample rate greater than 96kHz. The card reports the corresponding
	 * single speed. So the best means seems to get spdअगर rate when
	 * स्वतःsync reference is spdअगर */
	अगर (hdsp->io_type == H9632 &&
	    hdsp_स्वतःsync_ref(hdsp) == HDSP_AUTOSYNC_FROM_SPDIF)
		 वापस hdsp_spdअगर_sample_rate(hdsp);

	चयन (rate_bits) अणु
	हाल HDSP_प्रणालीFrequency32:   वापस 32000;
	हाल HDSP_प्रणालीFrequency44_1: वापस 44100;
	हाल HDSP_प्रणालीFrequency48:   वापस 48000;
	हाल HDSP_प्रणालीFrequency64:   वापस 64000;
	हाल HDSP_प्रणालीFrequency88_2: वापस 88200;
	हाल HDSP_प्रणालीFrequency96:   वापस 96000;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम hdsp_compute_period_size(काष्ठा hdsp *hdsp)
अणु
	hdsp->period_bytes = 1 << ((hdsp_decode_latency(hdsp->control_रेजिस्टर) + 8));
पूर्ण

अटल snd_pcm_uframes_t hdsp_hw_poपूर्णांकer(काष्ठा hdsp *hdsp)
अणु
	पूर्णांक position;

	position = hdsp_पढ़ो(hdsp, HDSP_statusRegister);

	अगर (!hdsp->precise_ptr)
		वापस (position & HDSP_BufferID) ? (hdsp->period_bytes / 4) : 0;

	position &= HDSP_BufferPositionMask;
	position /= 4;
	position &= (hdsp->period_bytes/2) - 1;
	वापस position;
पूर्ण

अटल व्योम hdsp_reset_hw_poपूर्णांकer(काष्ठा hdsp *hdsp)
अणु
	hdsp_ग_लिखो (hdsp, HDSP_resetPoपूर्णांकer, 0);
	अगर (hdsp->io_type == H9632 && hdsp->firmware_rev >= 152)
		/* HDSP_resetPoपूर्णांकer = HDSP_freqReg, which is strange and
		 * requires (?) to ग_लिखो again DDS value after a reset poपूर्णांकer
		 * (at least, it works like this) */
		hdsp_ग_लिखो (hdsp, HDSP_freqReg, hdsp->dds_value);
पूर्ण

अटल व्योम hdsp_start_audio(काष्ठा hdsp *s)
अणु
	s->control_रेजिस्टर |= (HDSP_AudioInterruptEnable | HDSP_Start);
	hdsp_ग_लिखो(s, HDSP_controlRegister, s->control_रेजिस्टर);
पूर्ण

अटल व्योम hdsp_stop_audio(काष्ठा hdsp *s)
अणु
	s->control_रेजिस्टर &= ~(HDSP_Start | HDSP_AudioInterruptEnable);
	hdsp_ग_लिखो(s, HDSP_controlRegister, s->control_रेजिस्टर);
पूर्ण

अटल व्योम hdsp_silence_playback(काष्ठा hdsp *hdsp)
अणु
	स_रखो(hdsp->playback_buffer, 0, HDSP_DMA_AREA_BYTES);
पूर्ण

अटल पूर्णांक hdsp_set_पूर्णांकerrupt_पूर्णांकerval(काष्ठा hdsp *s, अचिन्हित पूर्णांक frames)
अणु
	पूर्णांक n;

	spin_lock_irq(&s->lock);

	frames >>= 7;
	n = 0;
	जबतक (frames) अणु
		n++;
		frames >>= 1;
	पूर्ण

	s->control_रेजिस्टर &= ~HDSP_LatencyMask;
	s->control_रेजिस्टर |= hdsp_encode_latency(n);

	hdsp_ग_लिखो(s, HDSP_controlRegister, s->control_रेजिस्टर);

	hdsp_compute_period_size(s);

	spin_unlock_irq(&s->lock);

	वापस 0;
पूर्ण

अटल व्योम hdsp_set_dds_value(काष्ठा hdsp *hdsp, पूर्णांक rate)
अणु
	u64 n;

	अगर (rate >= 112000)
		rate /= 4;
	अन्यथा अगर (rate >= 56000)
		rate /= 2;

	n = DDS_NUMERATOR;
	n = भाग_u64(n, rate);
	/* n should be less than 2^32 क्रम being written to FREQ रेजिस्टर */
	snd_BUG_ON(n >> 32);
	/* HDSP_freqReg and HDSP_resetPoपूर्णांकer are the same, so keep the DDS
	   value to ग_लिखो it after a reset */
	hdsp->dds_value = n;
	hdsp_ग_लिखो(hdsp, HDSP_freqReg, hdsp->dds_value);
पूर्ण

अटल पूर्णांक hdsp_set_rate(काष्ठा hdsp *hdsp, पूर्णांक rate, पूर्णांक called_पूर्णांकernally)
अणु
	पूर्णांक reject_अगर_खोलो = 0;
	पूर्णांक current_rate;
	पूर्णांक rate_bits;

	/* ASSUMPTION: hdsp->lock is either held, or
	   there is no need क्रम it (e.g. during module
	   initialization).
	*/

	अगर (!(hdsp->control_रेजिस्टर & HDSP_ClockModeMaster)) अणु
		अगर (called_पूर्णांकernally) अणु
			/* request from ctl or card initialization */
			dev_err(hdsp->card->dev,
				"device is not running as a clock master: cannot set sample rate.\n");
			वापस -1;
		पूर्ण अन्यथा अणु
			/* hw_param request जबतक in AutoSync mode */
			पूर्णांक बाह्यal_freq = hdsp_बाह्यal_sample_rate(hdsp);
			पूर्णांक spdअगर_freq = hdsp_spdअगर_sample_rate(hdsp);

			अगर ((spdअगर_freq == बाह्यal_freq*2) && (hdsp_स्वतःsync_ref(hdsp) >= HDSP_AUTOSYNC_FROM_ADAT1))
				dev_info(hdsp->card->dev,
					 "Detected ADAT in double speed mode\n");
			अन्यथा अगर (hdsp->io_type == H9632 && (spdअगर_freq == बाह्यal_freq*4) && (hdsp_स्वतःsync_ref(hdsp) >= HDSP_AUTOSYNC_FROM_ADAT1))
				dev_info(hdsp->card->dev,
					 "Detected ADAT in quad speed mode\n");
			अन्यथा अगर (rate != बाह्यal_freq) अणु
				dev_info(hdsp->card->dev,
					 "No AutoSync source for requested rate\n");
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण

	current_rate = hdsp->प्रणाली_sample_rate;

	/* Changing from a "single speed" to a "double speed" rate is
	   not allowed अगर any substreams are खोलो. This is because
	   such a change causes a shअगरt in the location of
	   the DMA buffers and a reduction in the number of available
	   buffers.

	   Note that a similar but essentially insoluble problem
	   exists क्रम बाह्यally-driven rate changes. All we can करो
	   is to flag rate changes in the पढ़ो/ग_लिखो routines.  */

	अगर (rate > 96000 && hdsp->io_type != H9632)
		वापस -EINVAL;

	चयन (rate) अणु
	हाल 32000:
		अगर (current_rate > 48000)
			reject_अगर_खोलो = 1;
		rate_bits = HDSP_Frequency32KHz;
		अवरोध;
	हाल 44100:
		अगर (current_rate > 48000)
			reject_अगर_खोलो = 1;
		rate_bits = HDSP_Frequency44_1KHz;
		अवरोध;
	हाल 48000:
		अगर (current_rate > 48000)
			reject_अगर_खोलो = 1;
		rate_bits = HDSP_Frequency48KHz;
		अवरोध;
	हाल 64000:
		अगर (current_rate <= 48000 || current_rate > 96000)
			reject_अगर_खोलो = 1;
		rate_bits = HDSP_Frequency64KHz;
		अवरोध;
	हाल 88200:
		अगर (current_rate <= 48000 || current_rate > 96000)
			reject_अगर_खोलो = 1;
		rate_bits = HDSP_Frequency88_2KHz;
		अवरोध;
	हाल 96000:
		अगर (current_rate <= 48000 || current_rate > 96000)
			reject_अगर_खोलो = 1;
		rate_bits = HDSP_Frequency96KHz;
		अवरोध;
	हाल 128000:
		अगर (current_rate < 128000)
			reject_अगर_खोलो = 1;
		rate_bits = HDSP_Frequency128KHz;
		अवरोध;
	हाल 176400:
		अगर (current_rate < 128000)
			reject_अगर_खोलो = 1;
		rate_bits = HDSP_Frequency176_4KHz;
		अवरोध;
	हाल 192000:
		अगर (current_rate < 128000)
			reject_अगर_खोलो = 1;
		rate_bits = HDSP_Frequency192KHz;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (reject_अगर_खोलो && (hdsp->capture_pid >= 0 || hdsp->playback_pid >= 0)) अणु
		dev_warn(hdsp->card->dev,
			 "cannot change speed mode (capture PID = %d, playback PID = %d)\n",
			    hdsp->capture_pid,
			    hdsp->playback_pid);
		वापस -EBUSY;
	पूर्ण

	hdsp->control_रेजिस्टर &= ~HDSP_FrequencyMask;
	hdsp->control_रेजिस्टर |= rate_bits;
	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);

	/* For HDSP9632 rev 152, need to set DDS value in FREQ रेजिस्टर */
	अगर (hdsp->io_type == H9632 && hdsp->firmware_rev >= 152)
		hdsp_set_dds_value(hdsp, rate);

	अगर (rate >= 128000) अणु
		hdsp->channel_map = channel_map_H9632_qs;
	पूर्ण अन्यथा अगर (rate > 48000) अणु
		अगर (hdsp->io_type == H9632)
			hdsp->channel_map = channel_map_H9632_ds;
		अन्यथा
			hdsp->channel_map = channel_map_ds;
	पूर्ण अन्यथा अणु
		चयन (hdsp->io_type) अणु
		हाल RPM:
		हाल Multअगरace:
			hdsp->channel_map = channel_map_mf_ss;
			अवरोध;
		हाल Digअगरace:
		हाल H9652:
			hdsp->channel_map = channel_map_df_ss;
			अवरोध;
		हाल H9632:
			hdsp->channel_map = channel_map_H9632_ss;
			अवरोध;
		शेष:
			/* should never happen */
			अवरोध;
		पूर्ण
	पूर्ण

	hdsp->प्रणाली_sample_rate = rate;

	वापस 0;
पूर्ण

/*----------------------------------------------------------------------------
   MIDI
  ----------------------------------------------------------------------------*/

अटल अचिन्हित अक्षर snd_hdsp_midi_पढ़ो_byte (काष्ठा hdsp *hdsp, पूर्णांक id)
अणु
	/* the hardware alपढ़ोy करोes the relevant bit-mask with 0xff */
	अगर (id)
		वापस hdsp_पढ़ो(hdsp, HDSP_midiDataIn1);
	अन्यथा
		वापस hdsp_पढ़ो(hdsp, HDSP_midiDataIn0);
पूर्ण

अटल व्योम snd_hdsp_midi_ग_लिखो_byte (काष्ठा hdsp *hdsp, पूर्णांक id, पूर्णांक val)
अणु
	/* the hardware alपढ़ोy करोes the relevant bit-mask with 0xff */
	अगर (id)
		hdsp_ग_लिखो(hdsp, HDSP_midiDataOut1, val);
	अन्यथा
		hdsp_ग_लिखो(hdsp, HDSP_midiDataOut0, val);
पूर्ण

अटल पूर्णांक snd_hdsp_midi_input_available (काष्ठा hdsp *hdsp, पूर्णांक id)
अणु
	अगर (id)
		वापस (hdsp_पढ़ो(hdsp, HDSP_midiStatusIn1) & 0xff);
	अन्यथा
		वापस (hdsp_पढ़ो(hdsp, HDSP_midiStatusIn0) & 0xff);
पूर्ण

अटल पूर्णांक snd_hdsp_midi_output_possible (काष्ठा hdsp *hdsp, पूर्णांक id)
अणु
	पूर्णांक fअगरo_bytes_used;

	अगर (id)
		fअगरo_bytes_used = hdsp_पढ़ो(hdsp, HDSP_midiStatusOut1) & 0xff;
	अन्यथा
		fअगरo_bytes_used = hdsp_पढ़ो(hdsp, HDSP_midiStatusOut0) & 0xff;

	अगर (fअगरo_bytes_used < 128)
		वापस  128 - fअगरo_bytes_used;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम snd_hdsp_flush_midi_input (काष्ठा hdsp *hdsp, पूर्णांक id)
अणु
	जबतक (snd_hdsp_midi_input_available (hdsp, id))
		snd_hdsp_midi_पढ़ो_byte (hdsp, id);
पूर्ण

अटल पूर्णांक snd_hdsp_midi_output_ग_लिखो (काष्ठा hdsp_midi *hmidi)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक n_pending;
	पूर्णांक to_ग_लिखो;
	पूर्णांक i;
	अचिन्हित अक्षर buf[128];

	/* Output is not पूर्णांकerrupt driven */

	spin_lock_irqsave (&hmidi->lock, flags);
	अगर (hmidi->output) अणु
		अगर (!snd_rawmidi_transmit_empty (hmidi->output)) अणु
			अगर ((n_pending = snd_hdsp_midi_output_possible (hmidi->hdsp, hmidi->id)) > 0) अणु
				अगर (n_pending > (पूर्णांक)माप (buf))
					n_pending = माप (buf);

				अगर ((to_ग_लिखो = snd_rawmidi_transmit (hmidi->output, buf, n_pending)) > 0) अणु
					क्रम (i = 0; i < to_ग_लिखो; ++i)
						snd_hdsp_midi_ग_लिखो_byte (hmidi->hdsp, hmidi->id, buf[i]);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore (&hmidi->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_midi_input_पढ़ो (काष्ठा hdsp_midi *hmidi)
अणु
	अचिन्हित अक्षर buf[128]; /* this buffer is deचिन्हित to match the MIDI input FIFO size */
	अचिन्हित दीर्घ flags;
	पूर्णांक n_pending;
	पूर्णांक i;

	spin_lock_irqsave (&hmidi->lock, flags);
	अगर ((n_pending = snd_hdsp_midi_input_available (hmidi->hdsp, hmidi->id)) > 0) अणु
		अगर (hmidi->input) अणु
			अगर (n_pending > (पूर्णांक)माप (buf))
				n_pending = माप (buf);
			क्रम (i = 0; i < n_pending; ++i)
				buf[i] = snd_hdsp_midi_पढ़ो_byte (hmidi->hdsp, hmidi->id);
			अगर (n_pending)
				snd_rawmidi_receive (hmidi->input, buf, n_pending);
		पूर्ण अन्यथा अणु
			/* flush the MIDI input FIFO */
			जबतक (--n_pending)
				snd_hdsp_midi_पढ़ो_byte (hmidi->hdsp, hmidi->id);
		पूर्ण
	पूर्ण
	hmidi->pending = 0;
	अगर (hmidi->id)
		hmidi->hdsp->control_रेजिस्टर |= HDSP_Midi1InterruptEnable;
	अन्यथा
		hmidi->hdsp->control_रेजिस्टर |= HDSP_Midi0InterruptEnable;
	hdsp_ग_लिखो(hmidi->hdsp, HDSP_controlRegister, hmidi->hdsp->control_रेजिस्टर);
	spin_unlock_irqrestore (&hmidi->lock, flags);
	वापस snd_hdsp_midi_output_ग_लिखो (hmidi);
पूर्ण

अटल व्योम snd_hdsp_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा hdsp *hdsp;
	काष्ठा hdsp_midi *hmidi;
	अचिन्हित दीर्घ flags;
	u32 ie;

	hmidi = (काष्ठा hdsp_midi *) substream->rmidi->निजी_data;
	hdsp = hmidi->hdsp;
	ie = hmidi->id ? HDSP_Midi1InterruptEnable : HDSP_Midi0InterruptEnable;
	spin_lock_irqsave (&hdsp->lock, flags);
	अगर (up) अणु
		अगर (!(hdsp->control_रेजिस्टर & ie)) अणु
			snd_hdsp_flush_midi_input (hdsp, hmidi->id);
			hdsp->control_रेजिस्टर |= ie;
		पूर्ण
	पूर्ण अन्यथा अणु
		hdsp->control_रेजिस्टर &= ~ie;
	पूर्ण

	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	spin_unlock_irqrestore (&hdsp->lock, flags);
पूर्ण

अटल व्योम snd_hdsp_midi_output_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा hdsp_midi *hmidi = from_समयr(hmidi, t, समयr);
	अचिन्हित दीर्घ flags;

	snd_hdsp_midi_output_ग_लिखो(hmidi);
	spin_lock_irqsave (&hmidi->lock, flags);

	/* this करोes not bump hmidi->isसमयr, because the
	   kernel स्वतःmatically हटाओd the समयr when it
	   expired, and we are now adding it back, thus
	   leaving isसमयr wherever it was set beक्रमe.
	*/

	अगर (hmidi->isसमयr)
		mod_समयr(&hmidi->समयr, 1 + jअगरfies);

	spin_unlock_irqrestore (&hmidi->lock, flags);
पूर्ण

अटल व्योम snd_hdsp_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा hdsp_midi *hmidi;
	अचिन्हित दीर्घ flags;

	hmidi = (काष्ठा hdsp_midi *) substream->rmidi->निजी_data;
	spin_lock_irqsave (&hmidi->lock, flags);
	अगर (up) अणु
		अगर (!hmidi->isसमयr) अणु
			समयr_setup(&hmidi->समयr, snd_hdsp_midi_output_समयr,
				    0);
			mod_समयr(&hmidi->समयr, 1 + jअगरfies);
			hmidi->isसमयr++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hmidi->isसमयr && --hmidi->isसमयr <= 0)
			del_समयr (&hmidi->समयr);
	पूर्ण
	spin_unlock_irqrestore (&hmidi->lock, flags);
	अगर (up)
		snd_hdsp_midi_output_ग_लिखो(hmidi);
पूर्ण

अटल पूर्णांक snd_hdsp_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा hdsp_midi *hmidi;

	hmidi = (काष्ठा hdsp_midi *) substream->rmidi->निजी_data;
	spin_lock_irq (&hmidi->lock);
	snd_hdsp_flush_midi_input (hmidi->hdsp, hmidi->id);
	hmidi->input = substream;
	spin_unlock_irq (&hmidi->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा hdsp_midi *hmidi;

	hmidi = (काष्ठा hdsp_midi *) substream->rmidi->निजी_data;
	spin_lock_irq (&hmidi->lock);
	hmidi->output = substream;
	spin_unlock_irq (&hmidi->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा hdsp_midi *hmidi;

	snd_hdsp_midi_input_trigger (substream, 0);

	hmidi = (काष्ठा hdsp_midi *) substream->rmidi->निजी_data;
	spin_lock_irq (&hmidi->lock);
	hmidi->input = शून्य;
	spin_unlock_irq (&hmidi->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा hdsp_midi *hmidi;

	snd_hdsp_midi_output_trigger (substream, 0);

	hmidi = (काष्ठा hdsp_midi *) substream->rmidi->निजी_data;
	spin_lock_irq (&hmidi->lock);
	hmidi->output = शून्य;
	spin_unlock_irq (&hmidi->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops snd_hdsp_midi_output =
अणु
	.खोलो =		snd_hdsp_midi_output_खोलो,
	.बंद =	snd_hdsp_midi_output_बंद,
	.trigger =	snd_hdsp_midi_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_hdsp_midi_input =
अणु
	.खोलो =		snd_hdsp_midi_input_खोलो,
	.बंद =	snd_hdsp_midi_input_बंद,
	.trigger =	snd_hdsp_midi_input_trigger,
पूर्ण;

अटल पूर्णांक snd_hdsp_create_midi (काष्ठा snd_card *card, काष्ठा hdsp *hdsp, पूर्णांक id)
अणु
	अक्षर buf[40];

	hdsp->midi[id].id = id;
	hdsp->midi[id].rmidi = शून्य;
	hdsp->midi[id].input = शून्य;
	hdsp->midi[id].output = शून्य;
	hdsp->midi[id].hdsp = hdsp;
	hdsp->midi[id].isसमयr = 0;
	hdsp->midi[id].pending = 0;
	spin_lock_init (&hdsp->midi[id].lock);

	snम_लिखो(buf, माप(buf), "%s MIDI %d", card->लघुname, id + 1);
	अगर (snd_rawmidi_new (card, buf, id, 1, 1, &hdsp->midi[id].rmidi) < 0)
		वापस -1;

	प्र_लिखो(hdsp->midi[id].rmidi->name, "HDSP MIDI %d", id+1);
	hdsp->midi[id].rmidi->निजी_data = &hdsp->midi[id];

	snd_rawmidi_set_ops (hdsp->midi[id].rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_hdsp_midi_output);
	snd_rawmidi_set_ops (hdsp->midi[id].rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_hdsp_midi_input);

	hdsp->midi[id].rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT |
		SNDRV_RAWMIDI_INFO_INPUT |
		SNDRV_RAWMIDI_INFO_DUPLEX;

	वापस 0;
पूर्ण

/*-----------------------------------------------------------------------------
  Control Interface
  ----------------------------------------------------------------------------*/

अटल u32 snd_hdsp_convert_from_aes(काष्ठा snd_aes_iec958 *aes)
अणु
	u32 val = 0;
	val |= (aes->status[0] & IEC958_AES0_PROFESSIONAL) ? HDSP_SPDIFProfessional : 0;
	val |= (aes->status[0] & IEC958_AES0_NONAUDIO) ? HDSP_SPDIFNonAudio : 0;
	अगर (val & HDSP_SPDIFProfessional)
		val |= (aes->status[0] & IEC958_AES0_PRO_EMPHASIS_5015) ? HDSP_SPDIFEmphasis : 0;
	अन्यथा
		val |= (aes->status[0] & IEC958_AES0_CON_EMPHASIS_5015) ? HDSP_SPDIFEmphasis : 0;
	वापस val;
पूर्ण

अटल व्योम snd_hdsp_convert_to_aes(काष्ठा snd_aes_iec958 *aes, u32 val)
अणु
	aes->status[0] = ((val & HDSP_SPDIFProfessional) ? IEC958_AES0_PROFESSIONAL : 0) |
			 ((val & HDSP_SPDIFNonAudio) ? IEC958_AES0_NONAUDIO : 0);
	अगर (val & HDSP_SPDIFProfessional)
		aes->status[0] |= (val & HDSP_SPDIFEmphasis) ? IEC958_AES0_PRO_EMPHASIS_5015 : 0;
	अन्यथा
		aes->status[0] |= (val & HDSP_SPDIFEmphasis) ? IEC958_AES0_CON_EMPHASIS_5015 : 0;
पूर्ण

अटल पूर्णांक snd_hdsp_control_spdअगर_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_control_spdअगर_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	snd_hdsp_convert_to_aes(&ucontrol->value.iec958, hdsp->creg_spdअगर);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_control_spdअगर_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	u32 val;

	val = snd_hdsp_convert_from_aes(&ucontrol->value.iec958);
	spin_lock_irq(&hdsp->lock);
	change = val != hdsp->creg_spdअगर;
	hdsp->creg_spdअगर = val;
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_hdsp_control_spdअगर_stream_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_control_spdअगर_stream_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	snd_hdsp_convert_to_aes(&ucontrol->value.iec958, hdsp->creg_spdअगर_stream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_control_spdअगर_stream_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	u32 val;

	val = snd_hdsp_convert_from_aes(&ucontrol->value.iec958);
	spin_lock_irq(&hdsp->lock);
	change = val != hdsp->creg_spdअगर_stream;
	hdsp->creg_spdअगर_stream = val;
	hdsp->control_रेजिस्टर &= ~(HDSP_SPDIFProfessional | HDSP_SPDIFNonAudio | HDSP_SPDIFEmphasis);
	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर |= val);
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_hdsp_control_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_control_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = kcontrol->निजी_value;
	वापस 0;
पूर्ण

#घोषणा HDSP_SPDIF_IN(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_spdअगर_in, \
  .get = snd_hdsp_get_spdअगर_in, \
  .put = snd_hdsp_put_spdअगर_in पूर्ण

अटल अचिन्हित पूर्णांक hdsp_spdअगर_in(काष्ठा hdsp *hdsp)
अणु
	वापस hdsp_decode_spdअगर_in(hdsp->control_रेजिस्टर & HDSP_SPDIFInputMask);
पूर्ण

अटल पूर्णांक hdsp_set_spdअगर_input(काष्ठा hdsp *hdsp, पूर्णांक in)
अणु
	hdsp->control_रेजिस्टर &= ~HDSP_SPDIFInputMask;
	hdsp->control_रेजिस्टर |= hdsp_encode_spdअगर_in(in);
	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_info_spdअगर_in(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"Optical", "Coaxial", "Internal", "AES"
	पूर्ण;
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	वापस snd_ctl_क्रमागत_info(uinfo, 1, (hdsp->io_type == H9632) ? 4 : 3,
				 texts);
पूर्ण

अटल पूर्णांक snd_hdsp_get_spdअगर_in(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_spdअगर_in(hdsp);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_put_spdअगर_in(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.क्रमागतerated.item[0] % ((hdsp->io_type == H9632) ? 4 : 3);
	spin_lock_irq(&hdsp->lock);
	change = val != hdsp_spdअगर_in(hdsp);
	अगर (change)
		hdsp_set_spdअगर_input(hdsp, val);
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

#घोषणा HDSP_TOGGLE_SETTING(xname, xindex) \
अणु   .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.निजी_value = xindex, \
	.info = snd_hdsp_info_toggle_setting, \
	.get = snd_hdsp_get_toggle_setting, \
	.put = snd_hdsp_put_toggle_setting \
पूर्ण

अटल पूर्णांक hdsp_toggle_setting(काष्ठा hdsp *hdsp, u32 regmask)
अणु
	वापस (hdsp->control_रेजिस्टर & regmask) ? 1 : 0;
पूर्ण

अटल पूर्णांक hdsp_set_toggle_setting(काष्ठा hdsp *hdsp, u32 regmask, पूर्णांक out)
अणु
	अगर (out)
		hdsp->control_रेजिस्टर |= regmask;
	अन्यथा
		hdsp->control_रेजिस्टर &= ~regmask;
	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);

	वापस 0;
पूर्ण

#घोषणा snd_hdsp_info_toggle_setting		   snd_ctl_boolean_mono_info

अटल पूर्णांक snd_hdsp_get_toggle_setting(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	u32 regmask = kcontrol->निजी_value;

	spin_lock_irq(&hdsp->lock);
	ucontrol->value.पूर्णांकeger.value[0] = hdsp_toggle_setting(hdsp, regmask);
	spin_unlock_irq(&hdsp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_put_toggle_setting(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	u32 regmask = kcontrol->निजी_value;
	पूर्णांक change;
	अचिन्हित पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0] & 1;
	spin_lock_irq(&hdsp->lock);
	change = (पूर्णांक) val != hdsp_toggle_setting(hdsp, regmask);
	अगर (change)
		hdsp_set_toggle_setting(hdsp, regmask, val);
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

#घोषणा HDSP_SPDIF_SAMPLE_RATE(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READ, \
  .info = snd_hdsp_info_spdअगर_sample_rate, \
  .get = snd_hdsp_get_spdअगर_sample_rate \
पूर्ण

अटल पूर्णांक snd_hdsp_info_spdअगर_sample_rate(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"32000", "44100", "48000", "64000", "88200", "96000",
		"None", "128000", "176400", "192000"
	पूर्ण;
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	वापस snd_ctl_क्रमागत_info(uinfo, 1, (hdsp->io_type == H9632) ? 10 : 7,
				 texts);
पूर्ण

अटल पूर्णांक snd_hdsp_get_spdअगर_sample_rate(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	चयन (hdsp_spdअगर_sample_rate(hdsp)) अणु
	हाल 32000:
		ucontrol->value.क्रमागतerated.item[0] = 0;
		अवरोध;
	हाल 44100:
		ucontrol->value.क्रमागतerated.item[0] = 1;
		अवरोध;
	हाल 48000:
		ucontrol->value.क्रमागतerated.item[0] = 2;
		अवरोध;
	हाल 64000:
		ucontrol->value.क्रमागतerated.item[0] = 3;
		अवरोध;
	हाल 88200:
		ucontrol->value.क्रमागतerated.item[0] = 4;
		अवरोध;
	हाल 96000:
		ucontrol->value.क्रमागतerated.item[0] = 5;
		अवरोध;
	हाल 128000:
		ucontrol->value.क्रमागतerated.item[0] = 7;
		अवरोध;
	हाल 176400:
		ucontrol->value.क्रमागतerated.item[0] = 8;
		अवरोध;
	हाल 192000:
		ucontrol->value.क्रमागतerated.item[0] = 9;
		अवरोध;
	शेष:
		ucontrol->value.क्रमागतerated.item[0] = 6;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा HDSP_SYSTEM_SAMPLE_RATE(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READ, \
  .info = snd_hdsp_info_प्रणाली_sample_rate, \
  .get = snd_hdsp_get_प्रणाली_sample_rate \
पूर्ण

अटल पूर्णांक snd_hdsp_info_प्रणाली_sample_rate(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_get_प्रणाली_sample_rate(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp->प्रणाली_sample_rate;
	वापस 0;
पूर्ण

#घोषणा HDSP_AUTOSYNC_SAMPLE_RATE(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READ, \
  .info = snd_hdsp_info_स्वतःsync_sample_rate, \
  .get = snd_hdsp_get_स्वतःsync_sample_rate \
पूर्ण

अटल पूर्णांक snd_hdsp_info_स्वतःsync_sample_rate(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"32000", "44100", "48000", "64000", "88200", "96000",
		"None", "128000", "176400", "192000"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, (hdsp->io_type == H9632) ? 10 : 7,
				 texts);
पूर्ण

अटल पूर्णांक snd_hdsp_get_स्वतःsync_sample_rate(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	चयन (hdsp_बाह्यal_sample_rate(hdsp)) अणु
	हाल 32000:
		ucontrol->value.क्रमागतerated.item[0] = 0;
		अवरोध;
	हाल 44100:
		ucontrol->value.क्रमागतerated.item[0] = 1;
		अवरोध;
	हाल 48000:
		ucontrol->value.क्रमागतerated.item[0] = 2;
		अवरोध;
	हाल 64000:
		ucontrol->value.क्रमागतerated.item[0] = 3;
		अवरोध;
	हाल 88200:
		ucontrol->value.क्रमागतerated.item[0] = 4;
		अवरोध;
	हाल 96000:
		ucontrol->value.क्रमागतerated.item[0] = 5;
		अवरोध;
	हाल 128000:
		ucontrol->value.क्रमागतerated.item[0] = 7;
		अवरोध;
	हाल 176400:
		ucontrol->value.क्रमागतerated.item[0] = 8;
		अवरोध;
	हाल 192000:
		ucontrol->value.क्रमागतerated.item[0] = 9;
		अवरोध;
	शेष:
		ucontrol->value.क्रमागतerated.item[0] = 6;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा HDSP_SYSTEM_CLOCK_MODE(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READ, \
  .info = snd_hdsp_info_प्रणाली_घड़ी_mode, \
  .get = snd_hdsp_get_प्रणाली_घड़ी_mode \
पूर्ण

अटल पूर्णांक hdsp_प्रणाली_घड़ी_mode(काष्ठा hdsp *hdsp)
अणु
	अगर (hdsp->control_रेजिस्टर & HDSP_ClockModeMaster)
		वापस 0;
	अन्यथा अगर (hdsp_बाह्यal_sample_rate(hdsp) != hdsp->प्रणाली_sample_rate)
			वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक snd_hdsp_info_प्रणाली_घड़ी_mode(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु"Master", "Slave" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_hdsp_get_प्रणाली_घड़ी_mode(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_प्रणाली_घड़ी_mode(hdsp);
	वापस 0;
पूर्ण

#घोषणा HDSP_CLOCK_SOURCE(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_घड़ी_source, \
  .get = snd_hdsp_get_घड़ी_source, \
  .put = snd_hdsp_put_घड़ी_source \
पूर्ण

अटल पूर्णांक hdsp_घड़ी_source(काष्ठा hdsp *hdsp)
अणु
	अगर (hdsp->control_रेजिस्टर & HDSP_ClockModeMaster) अणु
		चयन (hdsp->प्रणाली_sample_rate) अणु
		हाल 32000:
			वापस 1;
		हाल 44100:
			वापस 2;
		हाल 48000:
			वापस 3;
		हाल 64000:
			वापस 4;
		हाल 88200:
			वापस 5;
		हाल 96000:
			वापस 6;
		हाल 128000:
			वापस 7;
		हाल 176400:
			वापस 8;
		हाल 192000:
			वापस 9;
		शेष:
			वापस 3;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक hdsp_set_घड़ी_source(काष्ठा hdsp *hdsp, पूर्णांक mode)
अणु
	पूर्णांक rate;
	चयन (mode) अणु
	हाल HDSP_CLOCK_SOURCE_AUTOSYNC:
		अगर (hdsp_बाह्यal_sample_rate(hdsp) != 0) अणु
		    अगर (!hdsp_set_rate(hdsp, hdsp_बाह्यal_sample_rate(hdsp), 1)) अणु
			hdsp->control_रेजिस्टर &= ~HDSP_ClockModeMaster;
			hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
			वापस 0;
		    पूर्ण
		पूर्ण
		वापस -1;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_32KHZ:
		rate = 32000;
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_44_1KHZ:
		rate = 44100;
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_48KHZ:
		rate = 48000;
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_64KHZ:
		rate = 64000;
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_88_2KHZ:
		rate = 88200;
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_96KHZ:
		rate = 96000;
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_128KHZ:
		rate = 128000;
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_176_4KHZ:
		rate = 176400;
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_192KHZ:
		rate = 192000;
		अवरोध;
	शेष:
		rate = 48000;
	पूर्ण
	hdsp->control_रेजिस्टर |= HDSP_ClockModeMaster;
	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	hdsp_set_rate(hdsp, rate, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_info_घड़ी_source(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"AutoSync", "Internal 32.0 kHz", "Internal 44.1 kHz",
		"Internal 48.0 kHz", "Internal 64.0 kHz", "Internal 88.2 kHz",
		"Internal 96.0 kHz", "Internal 128 kHz", "Internal 176.4 kHz",
		"Internal 192.0 KHz"
	पूर्ण;
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	वापस snd_ctl_क्रमागत_info(uinfo, 1, (hdsp->io_type == H9632) ? 10 : 7,
				 texts);
पूर्ण

अटल पूर्णांक snd_hdsp_get_घड़ी_source(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_घड़ी_source(hdsp);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_put_घड़ी_source(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (val < 0) val = 0;
	अगर (hdsp->io_type == H9632) अणु
		अगर (val > 9)
			val = 9;
	पूर्ण अन्यथा अणु
		अगर (val > 6)
			val = 6;
	पूर्ण
	spin_lock_irq(&hdsp->lock);
	अगर (val != hdsp_घड़ी_source(hdsp))
		change = (hdsp_set_घड़ी_source(hdsp, val) == 0) ? 1 : 0;
	अन्यथा
		change = 0;
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

#घोषणा snd_hdsp_info_घड़ी_source_lock		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_hdsp_get_घड़ी_source_lock(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = hdsp->घड़ी_source_locked;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_put_घड़ी_source_lock(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;

	change = (पूर्णांक)ucontrol->value.पूर्णांकeger.value[0] != hdsp->घड़ी_source_locked;
	अगर (change)
		hdsp->घड़ी_source_locked = !!ucontrol->value.पूर्णांकeger.value[0];
	वापस change;
पूर्ण

#घोषणा HDSP_DA_GAIN(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_da_gain, \
  .get = snd_hdsp_get_da_gain, \
  .put = snd_hdsp_put_da_gain \
पूर्ण

अटल पूर्णांक hdsp_da_gain(काष्ठा hdsp *hdsp)
अणु
	चयन (hdsp->control_रेजिस्टर & HDSP_DAGainMask) अणु
	हाल HDSP_DAGainHighGain:
		वापस 0;
	हाल HDSP_DAGainPlus4dBu:
		वापस 1;
	हाल HDSP_DAGainMinus10dBV:
		वापस 2;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक hdsp_set_da_gain(काष्ठा hdsp *hdsp, पूर्णांक mode)
अणु
	hdsp->control_रेजिस्टर &= ~HDSP_DAGainMask;
	चयन (mode) अणु
	हाल 0:
		hdsp->control_रेजिस्टर |= HDSP_DAGainHighGain;
		अवरोध;
	हाल 1:
		hdsp->control_रेजिस्टर |= HDSP_DAGainPlus4dBu;
		अवरोध;
	हाल 2:
		hdsp->control_रेजिस्टर |= HDSP_DAGainMinus10dBV;
		अवरोध;
	शेष:
		वापस -1;

	पूर्ण
	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_info_da_gain(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु"Hi Gain", "+4 dBu", "-10 dbV"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_hdsp_get_da_gain(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_da_gain(hdsp);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_put_da_gain(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (val < 0) val = 0;
	अगर (val > 2) val = 2;
	spin_lock_irq(&hdsp->lock);
	अगर (val != hdsp_da_gain(hdsp))
		change = (hdsp_set_da_gain(hdsp, val) == 0) ? 1 : 0;
	अन्यथा
		change = 0;
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

#घोषणा HDSP_AD_GAIN(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_ad_gain, \
  .get = snd_hdsp_get_ad_gain, \
  .put = snd_hdsp_put_ad_gain \
पूर्ण

अटल पूर्णांक hdsp_ad_gain(काष्ठा hdsp *hdsp)
अणु
	चयन (hdsp->control_रेजिस्टर & HDSP_ADGainMask) अणु
	हाल HDSP_ADGainMinus10dBV:
		वापस 0;
	हाल HDSP_ADGainPlus4dBu:
		वापस 1;
	हाल HDSP_ADGainLowGain:
		वापस 2;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक hdsp_set_ad_gain(काष्ठा hdsp *hdsp, पूर्णांक mode)
अणु
	hdsp->control_रेजिस्टर &= ~HDSP_ADGainMask;
	चयन (mode) अणु
	हाल 0:
		hdsp->control_रेजिस्टर |= HDSP_ADGainMinus10dBV;
		अवरोध;
	हाल 1:
		hdsp->control_रेजिस्टर |= HDSP_ADGainPlus4dBu;
		अवरोध;
	हाल 2:
		hdsp->control_रेजिस्टर |= HDSP_ADGainLowGain;
		अवरोध;
	शेष:
		वापस -1;

	पूर्ण
	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_info_ad_gain(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु"-10 dBV", "+4 dBu", "Lo Gain"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_hdsp_get_ad_gain(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_ad_gain(hdsp);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_put_ad_gain(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (val < 0) val = 0;
	अगर (val > 2) val = 2;
	spin_lock_irq(&hdsp->lock);
	अगर (val != hdsp_ad_gain(hdsp))
		change = (hdsp_set_ad_gain(hdsp, val) == 0) ? 1 : 0;
	अन्यथा
		change = 0;
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

#घोषणा HDSP_PHONE_GAIN(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_phone_gain, \
  .get = snd_hdsp_get_phone_gain, \
  .put = snd_hdsp_put_phone_gain \
पूर्ण

अटल पूर्णांक hdsp_phone_gain(काष्ठा hdsp *hdsp)
अणु
	चयन (hdsp->control_रेजिस्टर & HDSP_PhoneGainMask) अणु
	हाल HDSP_PhoneGain0dB:
		वापस 0;
	हाल HDSP_PhoneGainMinus6dB:
		वापस 1;
	हाल HDSP_PhoneGainMinus12dB:
		वापस 2;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक hdsp_set_phone_gain(काष्ठा hdsp *hdsp, पूर्णांक mode)
अणु
	hdsp->control_रेजिस्टर &= ~HDSP_PhoneGainMask;
	चयन (mode) अणु
	हाल 0:
		hdsp->control_रेजिस्टर |= HDSP_PhoneGain0dB;
		अवरोध;
	हाल 1:
		hdsp->control_रेजिस्टर |= HDSP_PhoneGainMinus6dB;
		अवरोध;
	हाल 2:
		hdsp->control_रेजिस्टर |= HDSP_PhoneGainMinus12dB;
		अवरोध;
	शेष:
		वापस -1;

	पूर्ण
	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_info_phone_gain(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु"0 dB", "-6 dB", "-12 dB"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_hdsp_get_phone_gain(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_phone_gain(hdsp);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_put_phone_gain(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (val < 0) val = 0;
	अगर (val > 2) val = 2;
	spin_lock_irq(&hdsp->lock);
	अगर (val != hdsp_phone_gain(hdsp))
		change = (hdsp_set_phone_gain(hdsp, val) == 0) ? 1 : 0;
	अन्यथा
		change = 0;
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

#घोषणा HDSP_PREF_SYNC_REF(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_pref_sync_ref, \
  .get = snd_hdsp_get_pref_sync_ref, \
  .put = snd_hdsp_put_pref_sync_ref \
पूर्ण

अटल पूर्णांक hdsp_pref_sync_ref(काष्ठा hdsp *hdsp)
अणु
	/* Notice that this looks at the requested sync source,
	   not the one actually in use.
	*/

	चयन (hdsp->control_रेजिस्टर & HDSP_SyncRefMask) अणु
	हाल HDSP_SyncRef_ADAT1:
		वापस HDSP_SYNC_FROM_ADAT1;
	हाल HDSP_SyncRef_ADAT2:
		वापस HDSP_SYNC_FROM_ADAT2;
	हाल HDSP_SyncRef_ADAT3:
		वापस HDSP_SYNC_FROM_ADAT3;
	हाल HDSP_SyncRef_SPDIF:
		वापस HDSP_SYNC_FROM_SPDIF;
	हाल HDSP_SyncRef_WORD:
		वापस HDSP_SYNC_FROM_WORD;
	हाल HDSP_SyncRef_ADAT_SYNC:
		वापस HDSP_SYNC_FROM_ADAT_SYNC;
	शेष:
		वापस HDSP_SYNC_FROM_WORD;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hdsp_set_pref_sync_ref(काष्ठा hdsp *hdsp, पूर्णांक pref)
अणु
	hdsp->control_रेजिस्टर &= ~HDSP_SyncRefMask;
	चयन (pref) अणु
	हाल HDSP_SYNC_FROM_ADAT1:
		hdsp->control_रेजिस्टर &= ~HDSP_SyncRefMask; /* clear SyncRef bits */
		अवरोध;
	हाल HDSP_SYNC_FROM_ADAT2:
		hdsp->control_रेजिस्टर |= HDSP_SyncRef_ADAT2;
		अवरोध;
	हाल HDSP_SYNC_FROM_ADAT3:
		hdsp->control_रेजिस्टर |= HDSP_SyncRef_ADAT3;
		अवरोध;
	हाल HDSP_SYNC_FROM_SPDIF:
		hdsp->control_रेजिस्टर |= HDSP_SyncRef_SPDIF;
		अवरोध;
	हाल HDSP_SYNC_FROM_WORD:
		hdsp->control_रेजिस्टर |= HDSP_SyncRef_WORD;
		अवरोध;
	हाल HDSP_SYNC_FROM_ADAT_SYNC:
		hdsp->control_रेजिस्टर |= HDSP_SyncRef_ADAT_SYNC;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_info_pref_sync_ref(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"Word", "IEC958", "ADAT1", "ADAT Sync", "ADAT2", "ADAT3"
	पूर्ण;
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक num_items;

	चयन (hdsp->io_type) अणु
	हाल Digअगरace:
	हाल H9652:
		num_items = 6;
		अवरोध;
	हाल Multअगरace:
		num_items = 4;
		अवरोध;
	हाल H9632:
		num_items = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस snd_ctl_क्रमागत_info(uinfo, 1, num_items, texts);
पूर्ण

अटल पूर्णांक snd_hdsp_get_pref_sync_ref(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_pref_sync_ref(hdsp);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_put_pref_sync_ref(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, max;
	अचिन्हित पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;

	चयन (hdsp->io_type) अणु
	हाल Digअगरace:
	हाल H9652:
		max = 6;
		अवरोध;
	हाल Multअगरace:
		max = 4;
		अवरोध;
	हाल H9632:
		max = 3;
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण

	val = ucontrol->value.क्रमागतerated.item[0] % max;
	spin_lock_irq(&hdsp->lock);
	change = (पूर्णांक)val != hdsp_pref_sync_ref(hdsp);
	hdsp_set_pref_sync_ref(hdsp, val);
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

#घोषणा HDSP_AUTOSYNC_REF(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READ, \
  .info = snd_hdsp_info_स्वतःsync_ref, \
  .get = snd_hdsp_get_स्वतःsync_ref, \
पूर्ण

अटल पूर्णांक hdsp_स्वतःsync_ref(काष्ठा hdsp *hdsp)
अणु
	/* This looks at the स्वतःsync selected sync reference */
	अचिन्हित पूर्णांक status2 = hdsp_पढ़ो(hdsp, HDSP_status2Register);

	चयन (status2 & HDSP_SelSyncRefMask) अणु
	हाल HDSP_SelSyncRef_WORD:
		वापस HDSP_AUTOSYNC_FROM_WORD;
	हाल HDSP_SelSyncRef_ADAT_SYNC:
		वापस HDSP_AUTOSYNC_FROM_ADAT_SYNC;
	हाल HDSP_SelSyncRef_SPDIF:
		वापस HDSP_AUTOSYNC_FROM_SPDIF;
	हाल HDSP_SelSyncRefMask:
		वापस HDSP_AUTOSYNC_FROM_NONE;
	हाल HDSP_SelSyncRef_ADAT1:
		वापस HDSP_AUTOSYNC_FROM_ADAT1;
	हाल HDSP_SelSyncRef_ADAT2:
		वापस HDSP_AUTOSYNC_FROM_ADAT2;
	हाल HDSP_SelSyncRef_ADAT3:
		वापस HDSP_AUTOSYNC_FROM_ADAT3;
	शेष:
		वापस HDSP_AUTOSYNC_FROM_WORD;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_info_स्वतःsync_ref(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"Word", "ADAT Sync", "IEC958", "None", "ADAT1", "ADAT2", "ADAT3"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 7, texts);
पूर्ण

अटल पूर्णांक snd_hdsp_get_स्वतःsync_ref(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_स्वतःsync_ref(hdsp);
	वापस 0;
पूर्ण

#घोषणा HDSP_PRECISE_POINTER(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_CARD, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_precise_poपूर्णांकer, \
  .get = snd_hdsp_get_precise_poपूर्णांकer, \
  .put = snd_hdsp_put_precise_poपूर्णांकer \
पूर्ण

अटल पूर्णांक hdsp_set_precise_poपूर्णांकer(काष्ठा hdsp *hdsp, पूर्णांक precise)
अणु
	अगर (precise)
		hdsp->precise_ptr = 1;
	अन्यथा
		hdsp->precise_ptr = 0;
	वापस 0;
पूर्ण

#घोषणा snd_hdsp_info_precise_poपूर्णांकer		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_hdsp_get_precise_poपूर्णांकer(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&hdsp->lock);
	ucontrol->value.पूर्णांकeger.value[0] = hdsp->precise_ptr;
	spin_unlock_irq(&hdsp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_put_precise_poपूर्णांकer(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0] & 1;
	spin_lock_irq(&hdsp->lock);
	change = (पूर्णांक)val != hdsp->precise_ptr;
	hdsp_set_precise_poपूर्णांकer(hdsp, val);
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

#घोषणा HDSP_USE_MIDI_WORK(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_CARD, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_use_midi_work, \
  .get = snd_hdsp_get_use_midi_work, \
  .put = snd_hdsp_put_use_midi_work \
पूर्ण

अटल पूर्णांक hdsp_set_use_midi_work(काष्ठा hdsp *hdsp, पूर्णांक use_work)
अणु
	अगर (use_work)
		hdsp->use_midi_work = 1;
	अन्यथा
		hdsp->use_midi_work = 0;
	वापस 0;
पूर्ण

#घोषणा snd_hdsp_info_use_midi_work		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_hdsp_get_use_midi_work(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&hdsp->lock);
	ucontrol->value.पूर्णांकeger.value[0] = hdsp->use_midi_work;
	spin_unlock_irq(&hdsp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_put_use_midi_work(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0] & 1;
	spin_lock_irq(&hdsp->lock);
	change = (पूर्णांक)val != hdsp->use_midi_work;
	hdsp_set_use_midi_work(hdsp, val);
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

#घोषणा HDSP_MIXER(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_HWDEP, \
  .name = xname, \
  .index = xindex, \
  .device = 0, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | \
		 SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
  .info = snd_hdsp_info_mixer, \
  .get = snd_hdsp_get_mixer, \
  .put = snd_hdsp_put_mixer \
पूर्ण

अटल पूर्णांक snd_hdsp_info_mixer(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 3;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 65536;
	uinfo->value.पूर्णांकeger.step = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_get_mixer(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक source;
	पूर्णांक destination;
	पूर्णांक addr;

	source = ucontrol->value.पूर्णांकeger.value[0];
	destination = ucontrol->value.पूर्णांकeger.value[1];

	अगर (source >= hdsp->max_channels)
		addr = hdsp_playback_to_output_key(hdsp,source-hdsp->max_channels,destination);
	अन्यथा
		addr = hdsp_input_to_output_key(hdsp,source, destination);

	spin_lock_irq(&hdsp->lock);
	ucontrol->value.पूर्णांकeger.value[2] = hdsp_पढ़ो_gain (hdsp, addr);
	spin_unlock_irq(&hdsp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_put_mixer(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक source;
	पूर्णांक destination;
	पूर्णांक gain;
	पूर्णांक addr;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;

	source = ucontrol->value.पूर्णांकeger.value[0];
	destination = ucontrol->value.पूर्णांकeger.value[1];

	अगर (source >= hdsp->max_channels)
		addr = hdsp_playback_to_output_key(hdsp,source-hdsp->max_channels, destination);
	अन्यथा
		addr = hdsp_input_to_output_key(hdsp,source, destination);

	gain = ucontrol->value.पूर्णांकeger.value[2];

	spin_lock_irq(&hdsp->lock);
	change = gain != hdsp_पढ़ो_gain(hdsp, addr);
	अगर (change)
		hdsp_ग_लिखो_gain(hdsp, addr, gain);
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

#घोषणा HDSP_WC_SYNC_CHECK(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
  .info = snd_hdsp_info_sync_check, \
  .get = snd_hdsp_get_wc_sync_check \
पूर्ण

अटल पूर्णांक snd_hdsp_info_sync_check(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु"No Lock", "Lock", "Sync" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक hdsp_wc_sync_check(काष्ठा hdsp *hdsp)
अणु
	पूर्णांक status2 = hdsp_पढ़ो(hdsp, HDSP_status2Register);
	अगर (status2 & HDSP_wc_lock) अणु
		अगर (status2 & HDSP_wc_sync)
			वापस 2;
		अन्यथा
			 वापस 1;
	पूर्ण अन्यथा
		वापस 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_get_wc_sync_check(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_wc_sync_check(hdsp);
	वापस 0;
पूर्ण

#घोषणा HDSP_SPDIF_SYNC_CHECK(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
  .info = snd_hdsp_info_sync_check, \
  .get = snd_hdsp_get_spdअगर_sync_check \
पूर्ण

अटल पूर्णांक hdsp_spdअगर_sync_check(काष्ठा hdsp *hdsp)
अणु
	पूर्णांक status = hdsp_पढ़ो(hdsp, HDSP_statusRegister);
	अगर (status & HDSP_SPDIFErrorFlag)
		वापस 0;
	अन्यथा अणु
		अगर (status & HDSP_SPDIFSync)
			वापस 2;
		अन्यथा
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_get_spdअगर_sync_check(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_spdअगर_sync_check(hdsp);
	वापस 0;
पूर्ण

#घोषणा HDSP_ADATSYNC_SYNC_CHECK(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
  .info = snd_hdsp_info_sync_check, \
  .get = snd_hdsp_get_adatsync_sync_check \
पूर्ण

अटल पूर्णांक hdsp_adatsync_sync_check(काष्ठा hdsp *hdsp)
अणु
	पूर्णांक status = hdsp_पढ़ो(hdsp, HDSP_statusRegister);
	अगर (status & HDSP_TimecodeLock) अणु
		अगर (status & HDSP_TimecodeSync)
			वापस 2;
		अन्यथा
			वापस 1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_get_adatsync_sync_check(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_adatsync_sync_check(hdsp);
	वापस 0;
पूर्ण

#घोषणा HDSP_ADAT_SYNC_CHECK \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
  .info = snd_hdsp_info_sync_check, \
  .get = snd_hdsp_get_adat_sync_check \
पूर्ण

अटल पूर्णांक hdsp_adat_sync_check(काष्ठा hdsp *hdsp, पूर्णांक idx)
अणु
	पूर्णांक status = hdsp_पढ़ो(hdsp, HDSP_statusRegister);

	अगर (status & (HDSP_Lock0>>idx)) अणु
		अगर (status & (HDSP_Sync0>>idx))
			वापस 2;
		अन्यथा
			वापस 1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_get_adat_sync_check(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक offset;
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	offset = ucontrol->id.index - 1;
	अगर (snd_BUG_ON(offset < 0))
		वापस -EINVAL;

	चयन (hdsp->io_type) अणु
	हाल Digअगरace:
	हाल H9652:
		अगर (offset >= 3)
			वापस -EINVAL;
		अवरोध;
	हाल Multअगरace:
	हाल H9632:
		अगर (offset >= 1)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण

	ucontrol->value.क्रमागतerated.item[0] = hdsp_adat_sync_check(hdsp, offset);
	वापस 0;
पूर्ण

#घोषणा HDSP_DDS_OFFSET(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .info = snd_hdsp_info_dds_offset, \
  .get = snd_hdsp_get_dds_offset, \
  .put = snd_hdsp_put_dds_offset \
पूर्ण

अटल पूर्णांक hdsp_dds_offset(काष्ठा hdsp *hdsp)
अणु
	u64 n;
	अचिन्हित पूर्णांक dds_value = hdsp->dds_value;
	पूर्णांक प्रणाली_sample_rate = hdsp->प्रणाली_sample_rate;

	अगर (!dds_value)
		वापस 0;

	n = DDS_NUMERATOR;
	/*
	 * dds_value = n / rate
	 * rate = n / dds_value
	 */
	n = भाग_u64(n, dds_value);
	अगर (प्रणाली_sample_rate >= 112000)
		n *= 4;
	अन्यथा अगर (प्रणाली_sample_rate >= 56000)
		n *= 2;
	वापस ((पूर्णांक)n) - प्रणाली_sample_rate;
पूर्ण

अटल पूर्णांक hdsp_set_dds_offset(काष्ठा hdsp *hdsp, पूर्णांक offset_hz)
अणु
	पूर्णांक rate = hdsp->प्रणाली_sample_rate + offset_hz;
	hdsp_set_dds_value(hdsp, rate);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_info_dds_offset(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = -5000;
	uinfo->value.पूर्णांकeger.max = 5000;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_get_dds_offset(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = hdsp_dds_offset(hdsp);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_put_dds_offset(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0];
	spin_lock_irq(&hdsp->lock);
	अगर (val != hdsp_dds_offset(hdsp))
		change = (hdsp_set_dds_offset(hdsp, val) == 0) ? 1 : 0;
	अन्यथा
		change = 0;
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_hdsp_9632_controls[] = अणु
HDSP_DA_GAIN("DA Gain", 0),
HDSP_AD_GAIN("AD Gain", 0),
HDSP_PHONE_GAIN("Phones Gain", 0),
HDSP_TOGGLE_SETTING("XLR Breakout Cable", HDSP_XLRBreakoutCable),
HDSP_DDS_OFFSET("DDS Sample Rate Offset", 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_hdsp_controls[] = अणु
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.info =		snd_hdsp_control_spdअगर_info,
	.get =		snd_hdsp_control_spdअगर_get,
	.put =		snd_hdsp_control_spdअगर_put,
पूर्ण,
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,PCM_STREAM),
	.info =		snd_hdsp_control_spdअगर_stream_info,
	.get =		snd_hdsp_control_spdअगर_stream_get,
	.put =		snd_hdsp_control_spdअगर_stream_put,
पूर्ण,
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,CON_MASK),
	.info =		snd_hdsp_control_spdअगर_mask_info,
	.get =		snd_hdsp_control_spdअगर_mask_get,
	.निजी_value = IEC958_AES0_NONAUDIO |
  			 IEC958_AES0_PROFESSIONAL |
			 IEC958_AES0_CON_EMPHASIS,
पूर्ण,
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,PRO_MASK),
	.info =		snd_hdsp_control_spdअगर_mask_info,
	.get =		snd_hdsp_control_spdअगर_mask_get,
	.निजी_value = IEC958_AES0_NONAUDIO |
			 IEC958_AES0_PROFESSIONAL |
			 IEC958_AES0_PRO_EMPHASIS,
पूर्ण,
HDSP_MIXER("Mixer", 0),
HDSP_SPDIF_IN("IEC958 Input Connector", 0),
HDSP_TOGGLE_SETTING("IEC958 Output also on ADAT1", HDSP_SPDIFOpticalOut),
HDSP_TOGGLE_SETTING("IEC958 Professional Bit", HDSP_SPDIFProfessional),
HDSP_TOGGLE_SETTING("IEC958 Emphasis Bit", HDSP_SPDIFEmphasis),
HDSP_TOGGLE_SETTING("IEC958 Non-audio Bit", HDSP_SPDIFNonAudio),
/* 'Sample Clock Source' complies with the alsa control naming scheme */
HDSP_CLOCK_SOURCE("Sample Clock Source", 0),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Sample Clock Source Locking",
	.info = snd_hdsp_info_घड़ी_source_lock,
	.get = snd_hdsp_get_घड़ी_source_lock,
	.put = snd_hdsp_put_घड़ी_source_lock,
पूर्ण,
HDSP_SYSTEM_CLOCK_MODE("System Clock Mode", 0),
HDSP_PREF_SYNC_REF("Preferred Sync Reference", 0),
HDSP_AUTOSYNC_REF("AutoSync Reference", 0),
HDSP_SPDIF_SAMPLE_RATE("SPDIF Sample Rate", 0),
HDSP_SYSTEM_SAMPLE_RATE("System Sample Rate", 0),
/* 'External Rate' complies with the alsa control naming scheme */
HDSP_AUTOSYNC_SAMPLE_RATE("External Rate", 0),
HDSP_WC_SYNC_CHECK("Word Clock Lock Status", 0),
HDSP_SPDIF_SYNC_CHECK("SPDIF Lock Status", 0),
HDSP_ADATSYNC_SYNC_CHECK("ADAT Sync Lock Status", 0),
HDSP_TOGGLE_SETTING("Line Out", HDSP_LineOut),
HDSP_PRECISE_POINTER("Precise Pointer", 0),
HDSP_USE_MIDI_WORK("Use Midi Tasklet", 0),
पूर्ण;


अटल पूर्णांक hdsp_rpm_input12(काष्ठा hdsp *hdsp)
अणु
	चयन (hdsp->control_रेजिस्टर & HDSP_RPM_Inp12) अणु
	हाल HDSP_RPM_Inp12_Phon_6dB:
		वापस 0;
	हाल HDSP_RPM_Inp12_Phon_n6dB:
		वापस 2;
	हाल HDSP_RPM_Inp12_Line_0dB:
		वापस 3;
	हाल HDSP_RPM_Inp12_Line_n6dB:
		वापस 4;
	पूर्ण
	वापस 1;
पूर्ण


अटल पूर्णांक snd_hdsp_get_rpm_input12(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_rpm_input12(hdsp);
	वापस 0;
पूर्ण


अटल पूर्णांक hdsp_set_rpm_input12(काष्ठा hdsp *hdsp, पूर्णांक mode)
अणु
	hdsp->control_रेजिस्टर &= ~HDSP_RPM_Inp12;
	चयन (mode) अणु
	हाल 0:
		hdsp->control_रेजिस्टर |= HDSP_RPM_Inp12_Phon_6dB;
		अवरोध;
	हाल 1:
		अवरोध;
	हाल 2:
		hdsp->control_रेजिस्टर |= HDSP_RPM_Inp12_Phon_n6dB;
		अवरोध;
	हाल 3:
		hdsp->control_रेजिस्टर |= HDSP_RPM_Inp12_Line_0dB;
		अवरोध;
	हाल 4:
		hdsp->control_रेजिस्टर |= HDSP_RPM_Inp12_Line_n6dB;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdsp_put_rpm_input12(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (val < 0)
		val = 0;
	अगर (val > 4)
		val = 4;
	spin_lock_irq(&hdsp->lock);
	अगर (val != hdsp_rpm_input12(hdsp))
		change = (hdsp_set_rpm_input12(hdsp, val) == 0) ? 1 : 0;
	अन्यथा
		change = 0;
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण


अटल पूर्णांक snd_hdsp_info_rpm_input(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"Phono +6dB", "Phono 0dB", "Phono -6dB", "Line 0dB", "Line -6dB"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 5, texts);
पूर्ण


अटल पूर्णांक hdsp_rpm_input34(काष्ठा hdsp *hdsp)
अणु
	चयन (hdsp->control_रेजिस्टर & HDSP_RPM_Inp34) अणु
	हाल HDSP_RPM_Inp34_Phon_6dB:
		वापस 0;
	हाल HDSP_RPM_Inp34_Phon_n6dB:
		वापस 2;
	हाल HDSP_RPM_Inp34_Line_0dB:
		वापस 3;
	हाल HDSP_RPM_Inp34_Line_n6dB:
		वापस 4;
	पूर्ण
	वापस 1;
पूर्ण


अटल पूर्णांक snd_hdsp_get_rpm_input34(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdsp_rpm_input34(hdsp);
	वापस 0;
पूर्ण


अटल पूर्णांक hdsp_set_rpm_input34(काष्ठा hdsp *hdsp, पूर्णांक mode)
अणु
	hdsp->control_रेजिस्टर &= ~HDSP_RPM_Inp34;
	चयन (mode) अणु
	हाल 0:
		hdsp->control_रेजिस्टर |= HDSP_RPM_Inp34_Phon_6dB;
		अवरोध;
	हाल 1:
		अवरोध;
	हाल 2:
		hdsp->control_रेजिस्टर |= HDSP_RPM_Inp34_Phon_n6dB;
		अवरोध;
	हाल 3:
		hdsp->control_रेजिस्टर |= HDSP_RPM_Inp34_Line_0dB;
		अवरोध;
	हाल 4:
		hdsp->control_रेजिस्टर |= HDSP_RPM_Inp34_Line_n6dB;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdsp_put_rpm_input34(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (val < 0)
		val = 0;
	अगर (val > 4)
		val = 4;
	spin_lock_irq(&hdsp->lock);
	अगर (val != hdsp_rpm_input34(hdsp))
		change = (hdsp_set_rpm_input34(hdsp, val) == 0) ? 1 : 0;
	अन्यथा
		change = 0;
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण


/* RPM Bypass चयन */
अटल पूर्णांक hdsp_rpm_bypass(काष्ठा hdsp *hdsp)
अणु
	वापस (hdsp->control_रेजिस्टर & HDSP_RPM_Bypass) ? 1 : 0;
पूर्ण


अटल पूर्णांक snd_hdsp_get_rpm_bypass(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = hdsp_rpm_bypass(hdsp);
	वापस 0;
पूर्ण


अटल पूर्णांक hdsp_set_rpm_bypass(काष्ठा hdsp *hdsp, पूर्णांक on)
अणु
	अगर (on)
		hdsp->control_रेजिस्टर |= HDSP_RPM_Bypass;
	अन्यथा
		hdsp->control_रेजिस्टर &= ~HDSP_RPM_Bypass;
	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdsp_put_rpm_bypass(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0] & 1;
	spin_lock_irq(&hdsp->lock);
	change = (पूर्णांक)val != hdsp_rpm_bypass(hdsp);
	hdsp_set_rpm_bypass(hdsp, val);
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण


अटल पूर्णांक snd_hdsp_info_rpm_bypass(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु"On", "Off"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण


/* RPM Disconnect चयन */
अटल पूर्णांक hdsp_rpm_disconnect(काष्ठा hdsp *hdsp)
अणु
	वापस (hdsp->control_रेजिस्टर & HDSP_RPM_Disconnect) ? 1 : 0;
पूर्ण


अटल पूर्णांक snd_hdsp_get_rpm_disconnect(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = hdsp_rpm_disconnect(hdsp);
	वापस 0;
पूर्ण


अटल पूर्णांक hdsp_set_rpm_disconnect(काष्ठा hdsp *hdsp, पूर्णांक on)
अणु
	अगर (on)
		hdsp->control_रेजिस्टर |= HDSP_RPM_Disconnect;
	अन्यथा
		hdsp->control_रेजिस्टर &= ~HDSP_RPM_Disconnect;
	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdsp_put_rpm_disconnect(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;

	अगर (!snd_hdsp_use_is_exclusive(hdsp))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0] & 1;
	spin_lock_irq(&hdsp->lock);
	change = (पूर्णांक)val != hdsp_rpm_disconnect(hdsp);
	hdsp_set_rpm_disconnect(hdsp, val);
	spin_unlock_irq(&hdsp->lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_hdsp_info_rpm_disconnect(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु"On", "Off"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_hdsp_rpm_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "RPM Bypass",
		.get = snd_hdsp_get_rpm_bypass,
		.put = snd_hdsp_put_rpm_bypass,
		.info = snd_hdsp_info_rpm_bypass
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "RPM Disconnect",
		.get = snd_hdsp_get_rpm_disconnect,
		.put = snd_hdsp_put_rpm_disconnect,
		.info = snd_hdsp_info_rpm_disconnect
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Input 1/2",
		.get = snd_hdsp_get_rpm_input12,
		.put = snd_hdsp_put_rpm_input12,
		.info = snd_hdsp_info_rpm_input
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Input 3/4",
		.get = snd_hdsp_get_rpm_input34,
		.put = snd_hdsp_put_rpm_input34,
		.info = snd_hdsp_info_rpm_input
	पूर्ण,
	HDSP_SYSTEM_SAMPLE_RATE("System Sample Rate", 0),
	HDSP_MIXER("Mixer", 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_hdsp_96xx_aeb =
	HDSP_TOGGLE_SETTING("Analog Extension Board",
			HDSP_AnalogExtensionBoard);
अटल काष्ठा snd_kcontrol_new snd_hdsp_adat_sync_check = HDSP_ADAT_SYNC_CHECK;


अटल bool hdsp_loopback_get(काष्ठा hdsp *स्थिर hdsp, स्थिर u8 channel)
अणु
	वापस hdsp->io_loopback & (1 << channel);
पूर्ण

अटल पूर्णांक hdsp_loopback_set(काष्ठा hdsp *स्थिर hdsp, स्थिर u8 channel, स्थिर bool enable)
अणु
	अगर (hdsp_loopback_get(hdsp, channel) == enable)
		वापस 0;

	hdsp->io_loopback ^= (1 << channel);

	hdsp_ग_लिखो(hdsp, HDSP_inputEnable + (4 * (hdsp->max_channels + channel)), enable);

	वापस 1;
पूर्ण

अटल पूर्णांक snd_hdsp_loopback_get(काष्ठा snd_kcontrol *स्थिर kcontrol,
				 काष्ठा snd_ctl_elem_value *स्थिर ucontrol)
अणु
	काष्ठा hdsp *स्थिर hdsp = snd_kcontrol_chip(kcontrol);
	स्थिर u8 channel = snd_ctl_get_ioff(kcontrol, &ucontrol->id);

	अगर (channel >= hdsp->max_channels)
		वापस -ENOENT;

	ucontrol->value.पूर्णांकeger.value[0] = hdsp_loopback_get(hdsp, channel);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_loopback_put(काष्ठा snd_kcontrol *स्थिर kcontrol,
				 काष्ठा snd_ctl_elem_value *स्थिर ucontrol)
अणु
	काष्ठा hdsp *स्थिर hdsp = snd_kcontrol_chip(kcontrol);
	स्थिर u8 channel = snd_ctl_get_ioff(kcontrol, &ucontrol->id);
	स्थिर bool enable = ucontrol->value.पूर्णांकeger.value[0] & 1;

	अगर (channel >= hdsp->max_channels)
		वापस -ENOENT;

	वापस hdsp_loopback_set(hdsp, channel, enable);
पूर्ण

अटल काष्ठा snd_kcontrol_new snd_hdsp_loopback_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_HWDEP,
	.name = "Output Loopback",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = snd_ctl_boolean_mono_info,
	.get = snd_hdsp_loopback_get,
	.put = snd_hdsp_loopback_put
पूर्ण;

अटल पूर्णांक snd_hdsp_create_controls(काष्ठा snd_card *card, काष्ठा hdsp *hdsp)
अणु
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;
	काष्ठा snd_kcontrol *kctl;

	अगर (hdsp->io_type == RPM) अणु
		/* RPM Bypass, Disconnect and Input चयनes */
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_hdsp_rpm_controls); idx++) अणु
			err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_hdsp_rpm_controls[idx], hdsp));
			अगर (err < 0)
				वापस err;
		पूर्ण
		वापस 0;
	पूर्ण

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_hdsp_controls); idx++) अणु
		अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_hdsp_controls[idx], hdsp))) < 0)
			वापस err;
		अगर (idx == 1)	/* IEC958 (S/PDIF) Stream */
			hdsp->spdअगर_ctl = kctl;
	पूर्ण

	/* ADAT SyncCheck status */
	snd_hdsp_adat_sync_check.name = "ADAT Lock Status";
	snd_hdsp_adat_sync_check.index = 1;
	अगर ((err = snd_ctl_add (card, kctl = snd_ctl_new1(&snd_hdsp_adat_sync_check, hdsp))))
		वापस err;
	अगर (hdsp->io_type == Digअगरace || hdsp->io_type == H9652) अणु
		क्रम (idx = 1; idx < 3; ++idx) अणु
			snd_hdsp_adat_sync_check.index = idx+1;
			अगर ((err = snd_ctl_add (card, kctl = snd_ctl_new1(&snd_hdsp_adat_sync_check, hdsp))))
				वापस err;
		पूर्ण
	पूर्ण

	/* DA, AD and Phone gain and XLR अवरोधout cable controls क्रम H9632 cards */
	अगर (hdsp->io_type == H9632) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_hdsp_9632_controls); idx++) अणु
			अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_hdsp_9632_controls[idx], hdsp))) < 0)
				वापस err;
		पूर्ण
	पूर्ण

	/* Output loopback controls क्रम H9632 cards */
	अगर (hdsp->io_type == H9632) अणु
		snd_hdsp_loopback_control.count = hdsp->max_channels;
		kctl = snd_ctl_new1(&snd_hdsp_loopback_control, hdsp);
		अगर (kctl == शून्य)
			वापस -ENOMEM;
		err = snd_ctl_add(card, kctl);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* AEB control क्रम H96xx card */
	अगर (hdsp->io_type == H9632 || hdsp->io_type == H9652) अणु
		अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_hdsp_96xx_aeb, hdsp))) < 0)
				वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*------------------------------------------------------------
   /proc पूर्णांकerface
 ------------------------------------------------------------*/

अटल व्योम
snd_hdsp_proc_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा hdsp *hdsp = entry->निजी_data;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक status2;
	अक्षर *pref_sync_ref;
	अक्षर *स्वतःsync_ref;
	अक्षर *प्रणाली_घड़ी_mode;
	अक्षर *घड़ी_source;
	पूर्णांक x;

	status = hdsp_पढ़ो(hdsp, HDSP_statusRegister);
	status2 = hdsp_पढ़ो(hdsp, HDSP_status2Register);

	snd_iम_लिखो(buffer, "%s (Card #%d)\n", hdsp->card_name,
		    hdsp->card->number + 1);
	snd_iम_लिखो(buffer, "Buffers: capture %p playback %p\n",
		    hdsp->capture_buffer, hdsp->playback_buffer);
	snd_iम_लिखो(buffer, "IRQ: %d Registers bus: 0x%lx VM: 0x%lx\n",
		    hdsp->irq, hdsp->port, (अचिन्हित दीर्घ)hdsp->iobase);
	snd_iम_लिखो(buffer, "Control register: 0x%x\n", hdsp->control_रेजिस्टर);
	snd_iम_लिखो(buffer, "Control2 register: 0x%x\n",
		    hdsp->control2_रेजिस्टर);
	snd_iम_लिखो(buffer, "Status register: 0x%x\n", status);
	snd_iम_लिखो(buffer, "Status2 register: 0x%x\n", status2);

	अगर (hdsp_check_क्रम_iobox(hdsp)) अणु
		snd_iम_लिखो(buffer, "No I/O box connected.\n"
			    "Please connect one and upload firmware.\n");
		वापस;
	पूर्ण

	अगर (hdsp_check_क्रम_firmware(hdsp, 0)) अणु
		अगर (hdsp->state & HDSP_FirmwareCached) अणु
			अगर (snd_hdsp_load_firmware_from_cache(hdsp) != 0) अणु
				snd_iम_लिखो(buffer, "Firmware loading from "
					    "cache failed, "
					    "please upload manually.\n");
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक err;

			err = hdsp_request_fw_loader(hdsp);
			अगर (err < 0) अणु
				snd_iम_लिखो(buffer,
					    "No firmware loaded nor cached, "
					    "please upload firmware.\n");
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	snd_iम_लिखो(buffer, "FIFO status: %d\n", hdsp_पढ़ो(hdsp, HDSP_fअगरoStatus) & 0xff);
	snd_iम_लिखो(buffer, "MIDI1 Output status: 0x%x\n", hdsp_पढ़ो(hdsp, HDSP_midiStatusOut0));
	snd_iम_लिखो(buffer, "MIDI1 Input status: 0x%x\n", hdsp_पढ़ो(hdsp, HDSP_midiStatusIn0));
	snd_iम_लिखो(buffer, "MIDI2 Output status: 0x%x\n", hdsp_पढ़ो(hdsp, HDSP_midiStatusOut1));
	snd_iम_लिखो(buffer, "MIDI2 Input status: 0x%x\n", hdsp_पढ़ो(hdsp, HDSP_midiStatusIn1));
	snd_iम_लिखो(buffer, "Use Midi Tasklet: %s\n", hdsp->use_midi_work ? "on" : "off");

	snd_iम_लिखो(buffer, "\n");

	x = 1 << (6 + hdsp_decode_latency(hdsp->control_रेजिस्टर & HDSP_LatencyMask));

	snd_iम_लिखो(buffer, "Buffer Size (Latency): %d samples (2 periods of %lu bytes)\n", x, (अचिन्हित दीर्घ) hdsp->period_bytes);
	snd_iम_लिखो(buffer, "Hardware pointer (frames): %ld\n", hdsp_hw_poपूर्णांकer(hdsp));
	snd_iम_लिखो(buffer, "Precise pointer: %s\n", hdsp->precise_ptr ? "on" : "off");
	snd_iम_लिखो(buffer, "Line out: %s\n", (hdsp->control_रेजिस्टर & HDSP_LineOut) ? "on" : "off");

	snd_iम_लिखो(buffer, "Firmware version: %d\n", (status2&HDSP_version0)|(status2&HDSP_version1)<<1|(status2&HDSP_version2)<<2);

	snd_iम_लिखो(buffer, "\n");

	चयन (hdsp_घड़ी_source(hdsp)) अणु
	हाल HDSP_CLOCK_SOURCE_AUTOSYNC:
		घड़ी_source = "AutoSync";
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_32KHZ:
		घड़ी_source = "Internal 32 kHz";
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_44_1KHZ:
		घड़ी_source = "Internal 44.1 kHz";
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_48KHZ:
		घड़ी_source = "Internal 48 kHz";
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_64KHZ:
		घड़ी_source = "Internal 64 kHz";
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_88_2KHZ:
		घड़ी_source = "Internal 88.2 kHz";
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_96KHZ:
		घड़ी_source = "Internal 96 kHz";
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_128KHZ:
		घड़ी_source = "Internal 128 kHz";
		अवरोध;
	हाल HDSP_CLOCK_SOURCE_INTERNAL_176_4KHZ:
		घड़ी_source = "Internal 176.4 kHz";
		अवरोध;
		हाल HDSP_CLOCK_SOURCE_INTERNAL_192KHZ:
		घड़ी_source = "Internal 192 kHz";
		अवरोध;
	शेष:
		घड़ी_source = "Error";
	पूर्ण
	snd_iम_लिखो (buffer, "Sample Clock Source: %s\n", घड़ी_source);

	अगर (hdsp_प्रणाली_घड़ी_mode(hdsp))
		प्रणाली_घड़ी_mode = "Slave";
	अन्यथा
		प्रणाली_घड़ी_mode = "Master";

	चयन (hdsp_pref_sync_ref (hdsp)) अणु
	हाल HDSP_SYNC_FROM_WORD:
		pref_sync_ref = "Word Clock";
		अवरोध;
	हाल HDSP_SYNC_FROM_ADAT_SYNC:
		pref_sync_ref = "ADAT Sync";
		अवरोध;
	हाल HDSP_SYNC_FROM_SPDIF:
		pref_sync_ref = "SPDIF";
		अवरोध;
	हाल HDSP_SYNC_FROM_ADAT1:
		pref_sync_ref = "ADAT1";
		अवरोध;
	हाल HDSP_SYNC_FROM_ADAT2:
		pref_sync_ref = "ADAT2";
		अवरोध;
	हाल HDSP_SYNC_FROM_ADAT3:
		pref_sync_ref = "ADAT3";
		अवरोध;
	शेष:
		pref_sync_ref = "Word Clock";
		अवरोध;
	पूर्ण
	snd_iम_लिखो (buffer, "Preferred Sync Reference: %s\n", pref_sync_ref);

	चयन (hdsp_स्वतःsync_ref (hdsp)) अणु
	हाल HDSP_AUTOSYNC_FROM_WORD:
		स्वतःsync_ref = "Word Clock";
		अवरोध;
	हाल HDSP_AUTOSYNC_FROM_ADAT_SYNC:
		स्वतःsync_ref = "ADAT Sync";
		अवरोध;
	हाल HDSP_AUTOSYNC_FROM_SPDIF:
		स्वतःsync_ref = "SPDIF";
		अवरोध;
	हाल HDSP_AUTOSYNC_FROM_NONE:
		स्वतःsync_ref = "None";
		अवरोध;
	हाल HDSP_AUTOSYNC_FROM_ADAT1:
		स्वतःsync_ref = "ADAT1";
		अवरोध;
	हाल HDSP_AUTOSYNC_FROM_ADAT2:
		स्वतःsync_ref = "ADAT2";
		अवरोध;
	हाल HDSP_AUTOSYNC_FROM_ADAT3:
		स्वतःsync_ref = "ADAT3";
		अवरोध;
	शेष:
		स्वतःsync_ref = "---";
		अवरोध;
	पूर्ण
	snd_iम_लिखो (buffer, "AutoSync Reference: %s\n", स्वतःsync_ref);

	snd_iम_लिखो (buffer, "AutoSync Frequency: %d\n", hdsp_बाह्यal_sample_rate(hdsp));

	snd_iम_लिखो (buffer, "System Clock Mode: %s\n", प्रणाली_घड़ी_mode);

	snd_iम_लिखो (buffer, "System Clock Frequency: %d\n", hdsp->प्रणाली_sample_rate);
	snd_iम_लिखो (buffer, "System Clock Locked: %s\n", hdsp->घड़ी_source_locked ? "Yes" : "No");

	snd_iम_लिखो(buffer, "\n");

	अगर (hdsp->io_type != RPM) अणु
		चयन (hdsp_spdअगर_in(hdsp)) अणु
		हाल HDSP_SPDIFIN_OPTICAL:
			snd_iम_लिखो(buffer, "IEC958 input: Optical\n");
			अवरोध;
		हाल HDSP_SPDIFIN_COAXIAL:
			snd_iम_लिखो(buffer, "IEC958 input: Coaxial\n");
			अवरोध;
		हाल HDSP_SPDIFIN_INTERNAL:
			snd_iम_लिखो(buffer, "IEC958 input: Internal\n");
			अवरोध;
		हाल HDSP_SPDIFIN_AES:
			snd_iम_लिखो(buffer, "IEC958 input: AES\n");
			अवरोध;
		शेष:
			snd_iम_लिखो(buffer, "IEC958 input: ???\n");
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (RPM == hdsp->io_type) अणु
		अगर (hdsp->control_रेजिस्टर & HDSP_RPM_Bypass)
			snd_iम_लिखो(buffer, "RPM Bypass: disabled\n");
		अन्यथा
			snd_iम_लिखो(buffer, "RPM Bypass: enabled\n");
		अगर (hdsp->control_रेजिस्टर & HDSP_RPM_Disconnect)
			snd_iम_लिखो(buffer, "RPM disconnected\n");
		अन्यथा
			snd_iम_लिखो(buffer, "RPM connected\n");

		चयन (hdsp->control_रेजिस्टर & HDSP_RPM_Inp12) अणु
		हाल HDSP_RPM_Inp12_Phon_6dB:
			snd_iम_लिखो(buffer, "Input 1/2: Phono, 6dB\n");
			अवरोध;
		हाल HDSP_RPM_Inp12_Phon_0dB:
			snd_iम_लिखो(buffer, "Input 1/2: Phono, 0dB\n");
			अवरोध;
		हाल HDSP_RPM_Inp12_Phon_n6dB:
			snd_iम_लिखो(buffer, "Input 1/2: Phono, -6dB\n");
			अवरोध;
		हाल HDSP_RPM_Inp12_Line_0dB:
			snd_iम_लिखो(buffer, "Input 1/2: Line, 0dB\n");
			अवरोध;
		हाल HDSP_RPM_Inp12_Line_n6dB:
			snd_iम_लिखो(buffer, "Input 1/2: Line, -6dB\n");
			अवरोध;
		शेष:
			snd_iम_लिखो(buffer, "Input 1/2: ???\n");
		पूर्ण

		चयन (hdsp->control_रेजिस्टर & HDSP_RPM_Inp34) अणु
		हाल HDSP_RPM_Inp34_Phon_6dB:
			snd_iम_लिखो(buffer, "Input 3/4: Phono, 6dB\n");
			अवरोध;
		हाल HDSP_RPM_Inp34_Phon_0dB:
			snd_iम_लिखो(buffer, "Input 3/4: Phono, 0dB\n");
			अवरोध;
		हाल HDSP_RPM_Inp34_Phon_n6dB:
			snd_iम_लिखो(buffer, "Input 3/4: Phono, -6dB\n");
			अवरोध;
		हाल HDSP_RPM_Inp34_Line_0dB:
			snd_iम_लिखो(buffer, "Input 3/4: Line, 0dB\n");
			अवरोध;
		हाल HDSP_RPM_Inp34_Line_n6dB:
			snd_iम_लिखो(buffer, "Input 3/4: Line, -6dB\n");
			अवरोध;
		शेष:
			snd_iम_लिखो(buffer, "Input 3/4: ???\n");
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (hdsp->control_रेजिस्टर & HDSP_SPDIFOpticalOut)
			snd_iम_लिखो(buffer, "IEC958 output: Coaxial & ADAT1\n");
		अन्यथा
			snd_iम_लिखो(buffer, "IEC958 output: Coaxial only\n");

		अगर (hdsp->control_रेजिस्टर & HDSP_SPDIFProfessional)
			snd_iम_लिखो(buffer, "IEC958 quality: Professional\n");
		अन्यथा
			snd_iम_लिखो(buffer, "IEC958 quality: Consumer\n");

		अगर (hdsp->control_रेजिस्टर & HDSP_SPDIFEmphasis)
			snd_iम_लिखो(buffer, "IEC958 emphasis: on\n");
		अन्यथा
			snd_iम_लिखो(buffer, "IEC958 emphasis: off\n");

		अगर (hdsp->control_रेजिस्टर & HDSP_SPDIFNonAudio)
			snd_iम_लिखो(buffer, "IEC958 NonAudio: on\n");
		अन्यथा
			snd_iम_लिखो(buffer, "IEC958 NonAudio: off\n");
		x = hdsp_spdअगर_sample_rate(hdsp);
		अगर (x != 0)
			snd_iम_लिखो(buffer, "IEC958 sample rate: %d\n", x);
		अन्यथा
			snd_iम_लिखो(buffer, "IEC958 sample rate: Error flag set\n");
	पूर्ण
	snd_iम_लिखो(buffer, "\n");

	/* Sync Check */
	x = status & HDSP_Sync0;
	अगर (status & HDSP_Lock0)
		snd_iम_लिखो(buffer, "ADAT1: %s\n", x ? "Sync" : "Lock");
	अन्यथा
		snd_iम_लिखो(buffer, "ADAT1: No Lock\n");

	चयन (hdsp->io_type) अणु
	हाल Digअगरace:
	हाल H9652:
		x = status & HDSP_Sync1;
		अगर (status & HDSP_Lock1)
			snd_iम_लिखो(buffer, "ADAT2: %s\n", x ? "Sync" : "Lock");
		अन्यथा
			snd_iम_लिखो(buffer, "ADAT2: No Lock\n");
		x = status & HDSP_Sync2;
		अगर (status & HDSP_Lock2)
			snd_iम_लिखो(buffer, "ADAT3: %s\n", x ? "Sync" : "Lock");
		अन्यथा
			snd_iम_लिखो(buffer, "ADAT3: No Lock\n");
		अवरोध;
	शेष:
		/* relax */
		अवरोध;
	पूर्ण

	x = status & HDSP_SPDIFSync;
	अगर (status & HDSP_SPDIFErrorFlag)
		snd_iम_लिखो (buffer, "SPDIF: No Lock\n");
	अन्यथा
		snd_iम_लिखो (buffer, "SPDIF: %s\n", x ? "Sync" : "Lock");

	x = status2 & HDSP_wc_sync;
	अगर (status2 & HDSP_wc_lock)
		snd_iम_लिखो (buffer, "Word Clock: %s\n", x ? "Sync" : "Lock");
	अन्यथा
		snd_iम_लिखो (buffer, "Word Clock: No Lock\n");

	x = status & HDSP_TimecodeSync;
	अगर (status & HDSP_TimecodeLock)
		snd_iम_लिखो(buffer, "ADAT Sync: %s\n", x ? "Sync" : "Lock");
	अन्यथा
		snd_iम_लिखो(buffer, "ADAT Sync: No Lock\n");

	snd_iम_लिखो(buffer, "\n");

	/* Inक्रमmations about H9632 specअगरic controls */
	अगर (hdsp->io_type == H9632) अणु
		अक्षर *पंचांगp;

		चयन (hdsp_ad_gain(hdsp)) अणु
		हाल 0:
			पंचांगp = "-10 dBV";
			अवरोध;
		हाल 1:
			पंचांगp = "+4 dBu";
			अवरोध;
		शेष:
			पंचांगp = "Lo Gain";
			अवरोध;
		पूर्ण
		snd_iम_लिखो(buffer, "AD Gain : %s\n", पंचांगp);

		चयन (hdsp_da_gain(hdsp)) अणु
		हाल 0:
			पंचांगp = "Hi Gain";
			अवरोध;
		हाल 1:
			पंचांगp = "+4 dBu";
			अवरोध;
		शेष:
			पंचांगp = "-10 dBV";
			अवरोध;
		पूर्ण
		snd_iम_लिखो(buffer, "DA Gain : %s\n", पंचांगp);

		चयन (hdsp_phone_gain(hdsp)) अणु
		हाल 0:
			पंचांगp = "0 dB";
			अवरोध;
		हाल 1:
			पंचांगp = "-6 dB";
			अवरोध;
		शेष:
			पंचांगp = "-12 dB";
			अवरोध;
		पूर्ण
		snd_iम_लिखो(buffer, "Phones Gain : %s\n", पंचांगp);

		snd_iम_लिखो(buffer, "XLR Breakout Cable : %s\n",
			hdsp_toggle_setting(hdsp, HDSP_XLRBreakoutCable) ?
			"yes" : "no");

		अगर (hdsp->control_रेजिस्टर & HDSP_AnalogExtensionBoard)
			snd_iम_लिखो(buffer, "AEB : on (ADAT1 internal)\n");
		अन्यथा
			snd_iम_लिखो(buffer, "AEB : off (ADAT1 external)\n");
		snd_iम_लिखो(buffer, "\n");
	पूर्ण

पूर्ण

अटल व्योम snd_hdsp_proc_init(काष्ठा hdsp *hdsp)
अणु
	snd_card_ro_proc_new(hdsp->card, "hdsp", hdsp, snd_hdsp_proc_पढ़ो);
पूर्ण

अटल व्योम snd_hdsp_मुक्त_buffers(काष्ठा hdsp *hdsp)
अणु
	snd_hammerfall_मुक्त_buffer(&hdsp->capture_dma_buf, hdsp->pci);
	snd_hammerfall_मुक्त_buffer(&hdsp->playback_dma_buf, hdsp->pci);
पूर्ण

अटल पूर्णांक snd_hdsp_initialize_memory(काष्ठा hdsp *hdsp)
अणु
	अचिन्हित दीर्घ pb_bus, cb_bus;

	अगर (snd_hammerfall_get_buffer(hdsp->pci, &hdsp->capture_dma_buf, HDSP_DMA_AREA_BYTES) < 0 ||
	    snd_hammerfall_get_buffer(hdsp->pci, &hdsp->playback_dma_buf, HDSP_DMA_AREA_BYTES) < 0) अणु
		अगर (hdsp->capture_dma_buf.area)
			snd_dma_मुक्त_pages(&hdsp->capture_dma_buf);
		dev_err(hdsp->card->dev,
			"%s: no buffers available\n", hdsp->card_name);
		वापस -ENOMEM;
	पूर्ण

	/* Align to bus-space 64K boundary */

	cb_bus = ALIGN(hdsp->capture_dma_buf.addr, 0x10000ul);
	pb_bus = ALIGN(hdsp->playback_dma_buf.addr, 0x10000ul);

	/* Tell the card where it is */

	hdsp_ग_लिखो(hdsp, HDSP_inputBufferAddress, cb_bus);
	hdsp_ग_लिखो(hdsp, HDSP_outputBufferAddress, pb_bus);

	hdsp->capture_buffer = hdsp->capture_dma_buf.area + (cb_bus - hdsp->capture_dma_buf.addr);
	hdsp->playback_buffer = hdsp->playback_dma_buf.area + (pb_bus - hdsp->playback_dma_buf.addr);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_set_शेषs(काष्ठा hdsp *hdsp)
अणु
	अचिन्हित पूर्णांक i;

	/* ASSUMPTION: hdsp->lock is either held, or
	   there is no need to hold it (e.g. during module
	   initialization).
	 */

	/* set शेषs:

	   SPDIF Input via Coax
	   Master घड़ी mode
	   maximum latency (7 => 2^7 = 8192 samples, 64Kbyte buffer,
	                    which implies 2 4096 sample, 32Kbyte periods).
           Enable line out.
	 */

	hdsp->control_रेजिस्टर = HDSP_ClockModeMaster |
		                 HDSP_SPDIFInputCoaxial |
		                 hdsp_encode_latency(7) |
		                 HDSP_LineOut;


	hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);

#अगर_घोषित SNDRV_BIG_ENDIAN
	hdsp->control2_रेजिस्टर = HDSP_BIGENDIAN_MODE;
#अन्यथा
	hdsp->control2_रेजिस्टर = 0;
#पूर्ण_अगर
	अगर (hdsp->io_type == H9652)
	        snd_hdsp_9652_enable_mixer (hdsp);
	अन्यथा
		hdsp_ग_लिखो (hdsp, HDSP_control2Reg, hdsp->control2_रेजिस्टर);

	hdsp_reset_hw_poपूर्णांकer(hdsp);
	hdsp_compute_period_size(hdsp);

	/* silence everything */

	क्रम (i = 0; i < HDSP_MATRIX_MIXER_SIZE; ++i)
		hdsp->mixer_matrix[i] = MINUS_अनन्त_GAIN;

	क्रम (i = 0; i < ((hdsp->io_type == H9652 || hdsp->io_type == H9632) ? 1352 : HDSP_MATRIX_MIXER_SIZE); ++i) अणु
		अगर (hdsp_ग_लिखो_gain (hdsp, i, MINUS_अनन्त_GAIN))
			वापस -EIO;
	पूर्ण

	/* H9632 specअगरic शेषs */
	अगर (hdsp->io_type == H9632) अणु
		hdsp->control_रेजिस्टर |= (HDSP_DAGainPlus4dBu | HDSP_ADGainPlus4dBu | HDSP_PhoneGain0dB);
		hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	पूर्ण

	/* set a शेष rate so that the channel map is set up.
	 */

	hdsp_set_rate(hdsp, 48000, 1);

	वापस 0;
पूर्ण

अटल व्योम hdsp_midi_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdsp *hdsp = container_of(work, काष्ठा hdsp, midi_work);

	अगर (hdsp->midi[0].pending)
		snd_hdsp_midi_input_पढ़ो (&hdsp->midi[0]);
	अगर (hdsp->midi[1].pending)
		snd_hdsp_midi_input_पढ़ो (&hdsp->midi[1]);
पूर्ण

अटल irqवापस_t snd_hdsp_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hdsp *hdsp = (काष्ठा hdsp *) dev_id;
	अचिन्हित पूर्णांक status;
	पूर्णांक audio;
	पूर्णांक midi0;
	पूर्णांक midi1;
	अचिन्हित पूर्णांक midi0status;
	अचिन्हित पूर्णांक midi1status;
	पूर्णांक schedule = 0;

	status = hdsp_पढ़ो(hdsp, HDSP_statusRegister);

	audio = status & HDSP_audioIRQPending;
	midi0 = status & HDSP_midi0IRQPending;
	midi1 = status & HDSP_midi1IRQPending;

	अगर (!audio && !midi0 && !midi1)
		वापस IRQ_NONE;

	hdsp_ग_लिखो(hdsp, HDSP_पूर्णांकerruptConfirmation, 0);

	midi0status = hdsp_पढ़ो (hdsp, HDSP_midiStatusIn0) & 0xff;
	midi1status = hdsp_पढ़ो (hdsp, HDSP_midiStatusIn1) & 0xff;

	अगर (!(hdsp->state & HDSP_InitializationComplete))
		वापस IRQ_HANDLED;

	अगर (audio) अणु
		अगर (hdsp->capture_substream)
			snd_pcm_period_elapsed(hdsp->pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream);

		अगर (hdsp->playback_substream)
			snd_pcm_period_elapsed(hdsp->pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream);
	पूर्ण

	अगर (midi0 && midi0status) अणु
		अगर (hdsp->use_midi_work) अणु
			/* we disable पूर्णांकerrupts क्रम this input until processing is करोne */
			hdsp->control_रेजिस्टर &= ~HDSP_Midi0InterruptEnable;
			hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
			hdsp->midi[0].pending = 1;
			schedule = 1;
		पूर्ण अन्यथा अणु
			snd_hdsp_midi_input_पढ़ो (&hdsp->midi[0]);
		पूर्ण
	पूर्ण
	अगर (hdsp->io_type != Multअगरace && hdsp->io_type != RPM && hdsp->io_type != H9632 && midi1 && midi1status) अणु
		अगर (hdsp->use_midi_work) अणु
			/* we disable पूर्णांकerrupts क्रम this input until processing is करोne */
			hdsp->control_रेजिस्टर &= ~HDSP_Midi1InterruptEnable;
			hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
			hdsp->midi[1].pending = 1;
			schedule = 1;
		पूर्ण अन्यथा अणु
			snd_hdsp_midi_input_पढ़ो (&hdsp->midi[1]);
		पूर्ण
	पूर्ण
	अगर (hdsp->use_midi_work && schedule)
		queue_work(प्रणाली_highpri_wq, &hdsp->midi_work);
	वापस IRQ_HANDLED;
पूर्ण

अटल snd_pcm_uframes_t snd_hdsp_hw_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	वापस hdsp_hw_poपूर्णांकer(hdsp);
पूर्ण

अटल अक्षर *hdsp_channel_buffer_location(काष्ठा hdsp *hdsp,
					     पूर्णांक stream,
					     पूर्णांक channel)

अणु
	पूर्णांक mapped_channel;

        अगर (snd_BUG_ON(channel < 0 || channel >= hdsp->max_channels))
		वापस शून्य;

	अगर ((mapped_channel = hdsp->channel_map[channel]) < 0)
		वापस शून्य;

	अगर (stream == SNDRV_PCM_STREAM_CAPTURE)
		वापस hdsp->capture_buffer + (mapped_channel * HDSP_CHANNEL_BUFFER_BYTES);
	अन्यथा
		वापस hdsp->playback_buffer + (mapped_channel * HDSP_CHANNEL_BUFFER_BYTES);
पूर्ण

अटल पूर्णांक snd_hdsp_playback_copy(काष्ठा snd_pcm_substream *substream,
				  पूर्णांक channel, अचिन्हित दीर्घ pos,
				  व्योम __user *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	अक्षर *channel_buf;

	अगर (snd_BUG_ON(pos + count > HDSP_CHANNEL_BUFFER_BYTES))
		वापस -EINVAL;

	channel_buf = hdsp_channel_buffer_location (hdsp, substream->pstr->stream, channel);
	अगर (snd_BUG_ON(!channel_buf))
		वापस -EIO;
	अगर (copy_from_user(channel_buf + pos, src, count))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_playback_copy_kernel(काष्ठा snd_pcm_substream *substream,
					 पूर्णांक channel, अचिन्हित दीर्घ pos,
					 व्योम *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	अक्षर *channel_buf;

	channel_buf = hdsp_channel_buffer_location(hdsp, substream->pstr->stream, channel);
	अगर (snd_BUG_ON(!channel_buf))
		वापस -EIO;
	स_नकल(channel_buf + pos, src, count);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_capture_copy(काष्ठा snd_pcm_substream *substream,
				 पूर्णांक channel, अचिन्हित दीर्घ pos,
				 व्योम __user *dst, अचिन्हित दीर्घ count)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	अक्षर *channel_buf;

	अगर (snd_BUG_ON(pos + count > HDSP_CHANNEL_BUFFER_BYTES))
		वापस -EINVAL;

	channel_buf = hdsp_channel_buffer_location (hdsp, substream->pstr->stream, channel);
	अगर (snd_BUG_ON(!channel_buf))
		वापस -EIO;
	अगर (copy_to_user(dst, channel_buf + pos, count))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_capture_copy_kernel(काष्ठा snd_pcm_substream *substream,
					पूर्णांक channel, अचिन्हित दीर्घ pos,
					व्योम *dst, अचिन्हित दीर्घ count)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	अक्षर *channel_buf;

	channel_buf = hdsp_channel_buffer_location(hdsp, substream->pstr->stream, channel);
	अगर (snd_BUG_ON(!channel_buf))
		वापस -EIO;
	स_नकल(dst, channel_buf + pos, count);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_hw_silence(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक channel, अचिन्हित दीर्घ pos,
			       अचिन्हित दीर्घ count)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	अक्षर *channel_buf;

	channel_buf = hdsp_channel_buffer_location (hdsp, substream->pstr->stream, channel);
	अगर (snd_BUG_ON(!channel_buf))
		वापस -EIO;
	स_रखो(channel_buf + pos, 0, count);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_reset(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *other;
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		other = hdsp->capture_substream;
	अन्यथा
		other = hdsp->playback_substream;
	अगर (hdsp->running)
		runसमय->status->hw_ptr = hdsp_hw_poपूर्णांकer(hdsp);
	अन्यथा
		runसमय->status->hw_ptr = 0;
	अगर (other) अणु
		काष्ठा snd_pcm_substream *s;
		काष्ठा snd_pcm_runसमय *orunसमय = other->runसमय;
		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			अगर (s == other) अणु
				orunसमय->status->hw_ptr = runसमय->status->hw_ptr;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	पूर्णांक err;
	pid_t this_pid;
	pid_t other_pid;

	अगर (hdsp_check_क्रम_iobox (hdsp))
		वापस -EIO;

	अगर (hdsp_check_क्रम_firmware(hdsp, 1))
		वापस -EIO;

	spin_lock_irq(&hdsp->lock);

	अगर (substream->pstr->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		hdsp->control_रेजिस्टर &= ~(HDSP_SPDIFProfessional | HDSP_SPDIFNonAudio | HDSP_SPDIFEmphasis);
		hdsp_ग_लिखो(hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर |= hdsp->creg_spdअगर_stream);
		this_pid = hdsp->playback_pid;
		other_pid = hdsp->capture_pid;
	पूर्ण अन्यथा अणु
		this_pid = hdsp->capture_pid;
		other_pid = hdsp->playback_pid;
	पूर्ण

	अगर ((other_pid > 0) && (this_pid != other_pid)) अणु

		/* The other stream is खोलो, and not by the same
		   task as this one. Make sure that the parameters
		   that matter are the same.
		 */

		अगर (params_rate(params) != hdsp->प्रणाली_sample_rate) अणु
			spin_unlock_irq(&hdsp->lock);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_RATE);
			वापस -EBUSY;
		पूर्ण

		अगर (params_period_size(params) != hdsp->period_bytes / 4) अणु
			spin_unlock_irq(&hdsp->lock);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
			वापस -EBUSY;
		पूर्ण

		/* We're fine. */

		spin_unlock_irq(&hdsp->lock);
 		वापस 0;

	पूर्ण अन्यथा अणु
		spin_unlock_irq(&hdsp->lock);
	पूर्ण

	/* how to make sure that the rate matches an बाह्यally-set one ?
	 */

	spin_lock_irq(&hdsp->lock);
	अगर (! hdsp->घड़ी_source_locked) अणु
		अगर ((err = hdsp_set_rate(hdsp, params_rate(params), 0)) < 0) अणु
			spin_unlock_irq(&hdsp->lock);
			_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_RATE);
			वापस err;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&hdsp->lock);

	अगर ((err = hdsp_set_पूर्णांकerrupt_पूर्णांकerval(hdsp, params_period_size(params))) < 0) अणु
		_snd_pcm_hw_param_setempty(params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_channel_info(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_channel_info *info)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक channel = info->channel;

	अगर (snd_BUG_ON(channel >= hdsp->max_channels))
		वापस -EINVAL;
	channel = array_index_nospec(channel, hdsp->max_channels);

	अगर (hdsp->channel_map[channel] < 0)
		वापस -EINVAL;

	info->offset = hdsp->channel_map[channel] * HDSP_CHANNEL_BUFFER_BYTES;
	info->first = 0;
	info->step = 32;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_ioctl(काष्ठा snd_pcm_substream *substream,
			     अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल SNDRV_PCM_IOCTL1_RESET:
		वापस snd_hdsp_reset(substream);
	हाल SNDRV_PCM_IOCTL1_CHANNEL_INFO:
		वापस snd_hdsp_channel_info(substream, arg);
	शेष:
		अवरोध;
	पूर्ण

	वापस snd_pcm_lib_ioctl(substream, cmd, arg);
पूर्ण

अटल पूर्णांक snd_hdsp_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *other;
	पूर्णांक running;

	अगर (hdsp_check_क्रम_iobox (hdsp))
		वापस -EIO;

	अगर (hdsp_check_क्रम_firmware(hdsp, 0)) /* no स्वतः-loading in trigger */
		वापस -EIO;

	spin_lock(&hdsp->lock);
	running = hdsp->running;
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		running |= 1 << substream->stream;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		running &= ~(1 << substream->stream);
		अवरोध;
	शेष:
		snd_BUG();
		spin_unlock(&hdsp->lock);
		वापस -EINVAL;
	पूर्ण
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		other = hdsp->capture_substream;
	अन्यथा
		other = hdsp->playback_substream;

	अगर (other) अणु
		काष्ठा snd_pcm_substream *s;
		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			अगर (s == other) अणु
				snd_pcm_trigger_करोne(s, substream);
				अगर (cmd == SNDRV_PCM_TRIGGER_START)
					running |= 1 << s->stream;
				अन्यथा
					running &= ~(1 << s->stream);
				जाओ _ok;
			पूर्ण
		पूर्ण
		अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
			अगर (!(running & (1 << SNDRV_PCM_STREAM_PLAYBACK)) &&
			    substream->stream == SNDRV_PCM_STREAM_CAPTURE)
				hdsp_silence_playback(hdsp);
		पूर्ण अन्यथा अणु
			अगर (running &&
			    substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
				hdsp_silence_playback(hdsp);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
				hdsp_silence_playback(hdsp);
	पूर्ण
 _ok:
	snd_pcm_trigger_करोne(substream, substream);
	अगर (!hdsp->running && running)
		hdsp_start_audio(hdsp);
	अन्यथा अगर (hdsp->running && !running)
		hdsp_stop_audio(hdsp);
	hdsp->running = running;
	spin_unlock(&hdsp->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	पूर्णांक result = 0;

	अगर (hdsp_check_क्रम_iobox (hdsp))
		वापस -EIO;

	अगर (hdsp_check_क्रम_firmware(hdsp, 1))
		वापस -EIO;

	spin_lock_irq(&hdsp->lock);
	अगर (!hdsp->running)
		hdsp_reset_hw_poपूर्णांकer(hdsp);
	spin_unlock_irq(&hdsp->lock);
	वापस result;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_hdsp_playback_subinfo =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_NONINTERLEAVED |
				 SNDRV_PCM_INFO_SYNC_START |
				 SNDRV_PCM_INFO_DOUBLE),
#अगर_घोषित SNDRV_BIG_ENDIAN
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_BE,
#अन्यथा
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_LE,
#पूर्ण_अगर
	.rates =		(SNDRV_PCM_RATE_32000 |
				 SNDRV_PCM_RATE_44100 |
				 SNDRV_PCM_RATE_48000 |
				 SNDRV_PCM_RATE_64000 |
				 SNDRV_PCM_RATE_88200 |
				 SNDRV_PCM_RATE_96000),
	.rate_min =		32000,
	.rate_max =		96000,
	.channels_min =		6,
	.channels_max =		HDSP_MAX_CHANNELS,
	.buffer_bytes_max =	HDSP_CHANNEL_BUFFER_BYTES * HDSP_MAX_CHANNELS,
	.period_bytes_min =	(64 * 4) * 10,
	.period_bytes_max =	(8192 * 4) * HDSP_MAX_CHANNELS,
	.periods_min =		2,
	.periods_max =		2,
	.fअगरo_size =		0
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_hdsp_capture_subinfo =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_NONINTERLEAVED |
				 SNDRV_PCM_INFO_SYNC_START),
#अगर_घोषित SNDRV_BIG_ENDIAN
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_BE,
#अन्यथा
	.क्रमmats =		SNDRV_PCM_FMTBIT_S32_LE,
#पूर्ण_अगर
	.rates =		(SNDRV_PCM_RATE_32000 |
				 SNDRV_PCM_RATE_44100 |
				 SNDRV_PCM_RATE_48000 |
				 SNDRV_PCM_RATE_64000 |
				 SNDRV_PCM_RATE_88200 |
				 SNDRV_PCM_RATE_96000),
	.rate_min =		32000,
	.rate_max =		96000,
	.channels_min =		5,
	.channels_max =		HDSP_MAX_CHANNELS,
	.buffer_bytes_max =	HDSP_CHANNEL_BUFFER_BYTES * HDSP_MAX_CHANNELS,
	.period_bytes_min =	(64 * 4) * 10,
	.period_bytes_max =	(8192 * 4) * HDSP_MAX_CHANNELS,
	.periods_min =		2,
	.periods_max =		2,
	.fअगरo_size =		0
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक hdsp_period_sizes[] = अणु 64, 128, 256, 512, 1024, 2048, 4096, 8192 पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hdsp_hw_स्थिरraपूर्णांकs_period_sizes = अणु
	.count = ARRAY_SIZE(hdsp_period_sizes),
	.list = hdsp_period_sizes,
	.mask = 0
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक hdsp_9632_sample_rates[] = अणु 32000, 44100, 48000, 64000, 88200, 96000, 128000, 176400, 192000 पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hdsp_hw_स्थिरraपूर्णांकs_9632_sample_rates = अणु
	.count = ARRAY_SIZE(hdsp_9632_sample_rates),
	.list = hdsp_9632_sample_rates,
	.mask = 0
पूर्ण;

अटल पूर्णांक snd_hdsp_hw_rule_in_channels(काष्ठा snd_pcm_hw_params *params,
					काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा hdsp *hdsp = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	अगर (hdsp->io_type == H9632) अणु
		अचिन्हित पूर्णांक list[3];
		list[0] = hdsp->qs_in_channels;
		list[1] = hdsp->ds_in_channels;
		list[2] = hdsp->ss_in_channels;
		वापस snd_पूर्णांकerval_list(c, 3, list, 0);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक list[2];
		list[0] = hdsp->ds_in_channels;
		list[1] = hdsp->ss_in_channels;
		वापस snd_पूर्णांकerval_list(c, 2, list, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_hdsp_hw_rule_out_channels(काष्ठा snd_pcm_hw_params *params,
					काष्ठा snd_pcm_hw_rule *rule)
अणु
	अचिन्हित पूर्णांक list[3];
	काष्ठा hdsp *hdsp = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	अगर (hdsp->io_type == H9632) अणु
		list[0] = hdsp->qs_out_channels;
		list[1] = hdsp->ds_out_channels;
		list[2] = hdsp->ss_out_channels;
		वापस snd_पूर्णांकerval_list(c, 3, list, 0);
	पूर्ण अन्यथा अणु
		list[0] = hdsp->ds_out_channels;
		list[1] = hdsp->ss_out_channels;
	पूर्ण
	वापस snd_पूर्णांकerval_list(c, 2, list, 0);
पूर्ण

अटल पूर्णांक snd_hdsp_hw_rule_in_channels_rate(काष्ठा snd_pcm_hw_params *params,
					     काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा hdsp *hdsp = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *r = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	अगर (r->min > 96000 && hdsp->io_type == H9632) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = hdsp->qs_in_channels,
			.max = hdsp->qs_in_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण अन्यथा अगर (r->min > 48000 && r->max <= 96000) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = hdsp->ds_in_channels,
			.max = hdsp->ds_in_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण अन्यथा अगर (r->max < 64000) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = hdsp->ss_in_channels,
			.max = hdsp->ss_in_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_hw_rule_out_channels_rate(काष्ठा snd_pcm_hw_params *params,
					     काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा hdsp *hdsp = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *r = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	अगर (r->min > 96000 && hdsp->io_type == H9632) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = hdsp->qs_out_channels,
			.max = hdsp->qs_out_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण अन्यथा अगर (r->min > 48000 && r->max <= 96000) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = hdsp->ds_out_channels,
			.max = hdsp->ds_out_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण अन्यथा अगर (r->max < 64000) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = hdsp->ss_out_channels,
			.max = hdsp->ss_out_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_hw_rule_rate_out_channels(काष्ठा snd_pcm_hw_params *params,
					     काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा hdsp *hdsp = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *r = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	अगर (c->min >= hdsp->ss_out_channels) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 32000,
			.max = 48000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण अन्यथा अगर (c->max <= hdsp->qs_out_channels && hdsp->io_type == H9632) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 128000,
			.max = 192000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण अन्यथा अगर (c->max <= hdsp->ds_out_channels) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 64000,
			.max = 96000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_hw_rule_rate_in_channels(काष्ठा snd_pcm_hw_params *params,
					     काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा hdsp *hdsp = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *r = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	अगर (c->min >= hdsp->ss_in_channels) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 32000,
			.max = 48000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण अन्यथा अगर (c->max <= hdsp->qs_in_channels && hdsp->io_type == H9632) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 128000,
			.max = 192000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण अन्यथा अगर (c->max <= hdsp->ds_in_channels) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 64000,
			.max = 96000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (hdsp_check_क्रम_iobox (hdsp))
		वापस -EIO;

	अगर (hdsp_check_क्रम_firmware(hdsp, 1))
		वापस -EIO;

	spin_lock_irq(&hdsp->lock);

	snd_pcm_set_sync(substream);

        runसमय->hw = snd_hdsp_playback_subinfo;
	runसमय->dma_area = hdsp->playback_buffer;
	runसमय->dma_bytes = HDSP_DMA_AREA_BYTES;

	hdsp->playback_pid = current->pid;
	hdsp->playback_substream = substream;

	spin_unlock_irq(&hdsp->lock);

	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, &hdsp_hw_स्थिरraपूर्णांकs_period_sizes);
	अगर (hdsp->घड़ी_source_locked) अणु
		runसमय->hw.rate_min = runसमय->hw.rate_max = hdsp->प्रणाली_sample_rate;
	पूर्ण अन्यथा अगर (hdsp->io_type == H9632) अणु
		runसमय->hw.rate_max = 192000;
		runसमय->hw.rates = SNDRV_PCM_RATE_KNOT;
		snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE, &hdsp_hw_स्थिरraपूर्णांकs_9632_sample_rates);
	पूर्ण
	अगर (hdsp->io_type == H9632) अणु
		runसमय->hw.channels_min = hdsp->qs_out_channels;
		runसमय->hw.channels_max = hdsp->ss_out_channels;
	पूर्ण

	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			     snd_hdsp_hw_rule_out_channels, hdsp,
			     SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			     snd_hdsp_hw_rule_out_channels_rate, hdsp,
			     SNDRV_PCM_HW_PARAM_RATE, -1);
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
			     snd_hdsp_hw_rule_rate_out_channels, hdsp,
			     SNDRV_PCM_HW_PARAM_CHANNELS, -1);

	अगर (RPM != hdsp->io_type) अणु
		hdsp->creg_spdअगर_stream = hdsp->creg_spdअगर;
		hdsp->spdअगर_ctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notअगरy(hdsp->card, SNDRV_CTL_EVENT_MASK_VALUE |
			SNDRV_CTL_EVENT_MASK_INFO, &hdsp->spdअगर_ctl->id);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_playback_release(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);

	spin_lock_irq(&hdsp->lock);

	hdsp->playback_pid = -1;
	hdsp->playback_substream = शून्य;

	spin_unlock_irq(&hdsp->lock);

	अगर (RPM != hdsp->io_type) अणु
		hdsp->spdअगर_ctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notअगरy(hdsp->card, SNDRV_CTL_EVENT_MASK_VALUE |
			SNDRV_CTL_EVENT_MASK_INFO, &hdsp->spdअगर_ctl->id);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdsp_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (hdsp_check_क्रम_iobox (hdsp))
		वापस -EIO;

	अगर (hdsp_check_क्रम_firmware(hdsp, 1))
		वापस -EIO;

	spin_lock_irq(&hdsp->lock);

	snd_pcm_set_sync(substream);

	runसमय->hw = snd_hdsp_capture_subinfo;
	runसमय->dma_area = hdsp->capture_buffer;
	runसमय->dma_bytes = HDSP_DMA_AREA_BYTES;

	hdsp->capture_pid = current->pid;
	hdsp->capture_substream = substream;

	spin_unlock_irq(&hdsp->lock);

	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, &hdsp_hw_स्थिरraपूर्णांकs_period_sizes);
	अगर (hdsp->io_type == H9632) अणु
		runसमय->hw.channels_min = hdsp->qs_in_channels;
		runसमय->hw.channels_max = hdsp->ss_in_channels;
		runसमय->hw.rate_max = 192000;
		runसमय->hw.rates = SNDRV_PCM_RATE_KNOT;
		snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE, &hdsp_hw_स्थिरraपूर्णांकs_9632_sample_rates);
	पूर्ण
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			     snd_hdsp_hw_rule_in_channels, hdsp,
			     SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			     snd_hdsp_hw_rule_in_channels_rate, hdsp,
			     SNDRV_PCM_HW_PARAM_RATE, -1);
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
			     snd_hdsp_hw_rule_rate_in_channels, hdsp,
			     SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_capture_release(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdsp *hdsp = snd_pcm_substream_chip(substream);

	spin_lock_irq(&hdsp->lock);

	hdsp->capture_pid = -1;
	hdsp->capture_substream = शून्य;

	spin_unlock_irq(&hdsp->lock);
	वापस 0;
पूर्ण

/* helper functions क्रम copying meter values */
अटल अंतरभूत पूर्णांक copy_u32_le(व्योम __user *dest, व्योम __iomem *src)
अणु
	u32 val = पढ़ोl(src);
	वापस copy_to_user(dest, &val, 4);
पूर्ण

अटल अंतरभूत पूर्णांक copy_u64_le(व्योम __user *dest, व्योम __iomem *src_low, व्योम __iomem *src_high)
अणु
	u32 rms_low, rms_high;
	u64 rms;
	rms_low = पढ़ोl(src_low);
	rms_high = पढ़ोl(src_high);
	rms = ((u64)rms_high << 32) | rms_low;
	वापस copy_to_user(dest, &rms, 8);
पूर्ण

अटल अंतरभूत पूर्णांक copy_u48_le(व्योम __user *dest, व्योम __iomem *src_low, व्योम __iomem *src_high)
अणु
	u32 rms_low, rms_high;
	u64 rms;
	rms_low = पढ़ोl(src_low) & 0xffffff00;
	rms_high = पढ़ोl(src_high) & 0xffffff00;
	rms = ((u64)rms_high << 32) | rms_low;
	वापस copy_to_user(dest, &rms, 8);
पूर्ण

अटल पूर्णांक hdsp_9652_get_peak(काष्ठा hdsp *hdsp, काष्ठा hdsp_peak_rms __user *peak_rms)
अणु
	पूर्णांक द्विगुनspeed = 0;
	पूर्णांक i, j, channels, ofs;

	अगर (hdsp_पढ़ो (hdsp, HDSP_statusRegister) & HDSP_DoubleSpeedStatus)
		द्विगुनspeed = 1;
	channels = द्विगुनspeed ? 14 : 26;
	क्रम (i = 0, j = 0; i < 26; ++i) अणु
		अगर (द्विगुनspeed && (i & 4))
			जारी;
		ofs = HDSP_9652_peakBase - j * 4;
		अगर (copy_u32_le(&peak_rms->input_peaks[i], hdsp->iobase + ofs))
			वापस -EFAULT;
		ofs -= channels * 4;
		अगर (copy_u32_le(&peak_rms->playback_peaks[i], hdsp->iobase + ofs))
			वापस -EFAULT;
		ofs -= channels * 4;
		अगर (copy_u32_le(&peak_rms->output_peaks[i], hdsp->iobase + ofs))
			वापस -EFAULT;
		ofs = HDSP_9652_rmsBase + j * 8;
		अगर (copy_u48_le(&peak_rms->input_rms[i], hdsp->iobase + ofs,
				hdsp->iobase + ofs + 4))
			वापस -EFAULT;
		ofs += channels * 8;
		अगर (copy_u48_le(&peak_rms->playback_rms[i], hdsp->iobase + ofs,
				hdsp->iobase + ofs + 4))
			वापस -EFAULT;
		ofs += channels * 8;
		अगर (copy_u48_le(&peak_rms->output_rms[i], hdsp->iobase + ofs,
				hdsp->iobase + ofs + 4))
			वापस -EFAULT;
		j++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hdsp_9632_get_peak(काष्ठा hdsp *hdsp, काष्ठा hdsp_peak_rms __user *peak_rms)
अणु
	पूर्णांक i, j;
	काष्ठा hdsp_9632_meters __iomem *m;
	पूर्णांक द्विगुनspeed = 0;

	अगर (hdsp_पढ़ो (hdsp, HDSP_statusRegister) & HDSP_DoubleSpeedStatus)
		द्विगुनspeed = 1;
	m = (काष्ठा hdsp_9632_meters __iomem *)(hdsp->iobase+HDSP_9632_metersBase);
	क्रम (i = 0, j = 0; i < 16; ++i, ++j) अणु
		अगर (copy_u32_le(&peak_rms->input_peaks[i], &m->input_peak[j]))
			वापस -EFAULT;
		अगर (copy_u32_le(&peak_rms->playback_peaks[i], &m->playback_peak[j]))
			वापस -EFAULT;
		अगर (copy_u32_le(&peak_rms->output_peaks[i], &m->output_peak[j]))
			वापस -EFAULT;
		अगर (copy_u64_le(&peak_rms->input_rms[i], &m->input_rms_low[j],
				&m->input_rms_high[j]))
			वापस -EFAULT;
		अगर (copy_u64_le(&peak_rms->playback_rms[i], &m->playback_rms_low[j],
				&m->playback_rms_high[j]))
			वापस -EFAULT;
		अगर (copy_u64_le(&peak_rms->output_rms[i], &m->output_rms_low[j],
				&m->output_rms_high[j]))
			वापस -EFAULT;
		अगर (द्विगुनspeed && i == 3) i += 4;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hdsp_get_peak(काष्ठा hdsp *hdsp, काष्ठा hdsp_peak_rms __user *peak_rms)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 26; i++) अणु
		अगर (copy_u32_le(&peak_rms->playback_peaks[i],
				hdsp->iobase + HDSP_playbackPeakLevel + i * 4))
			वापस -EFAULT;
		अगर (copy_u32_le(&peak_rms->input_peaks[i],
				hdsp->iobase + HDSP_inputPeakLevel + i * 4))
			वापस -EFAULT;
	पूर्ण
	क्रम (i = 0; i < 28; i++) अणु
		अगर (copy_u32_le(&peak_rms->output_peaks[i],
				hdsp->iobase + HDSP_outputPeakLevel + i * 4))
			वापस -EFAULT;
	पूर्ण
	क्रम (i = 0; i < 26; ++i) अणु
		अगर (copy_u64_le(&peak_rms->playback_rms[i],
				hdsp->iobase + HDSP_playbackRmsLevel + i * 8 + 4,
				hdsp->iobase + HDSP_playbackRmsLevel + i * 8))
			वापस -EFAULT;
		अगर (copy_u64_le(&peak_rms->input_rms[i],
				hdsp->iobase + HDSP_inputRmsLevel + i * 8 + 4,
				hdsp->iobase + HDSP_inputRmsLevel + i * 8))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_hwdep_ioctl(काष्ठा snd_hwdep *hw, काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hdsp *hdsp = hw->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल SNDRV_HDSP_IOCTL_GET_PEAK_RMS: अणु
		काष्ठा hdsp_peak_rms __user *peak_rms = (काष्ठा hdsp_peak_rms __user *)arg;

		err = hdsp_check_क्रम_iobox(hdsp);
		अगर (err < 0)
			वापस err;

		err = hdsp_check_क्रम_firmware(hdsp, 1);
		अगर (err < 0)
			वापस err;

		अगर (!(hdsp->state & HDSP_FirmwareLoaded)) अणु
			dev_err(hdsp->card->dev,
				"firmware needs to be uploaded to the card.\n");
			वापस -EINVAL;
		पूर्ण

		चयन (hdsp->io_type) अणु
		हाल H9652:
			वापस hdsp_9652_get_peak(hdsp, peak_rms);
		हाल H9632:
			वापस hdsp_9632_get_peak(hdsp, peak_rms);
		शेष:
			वापस hdsp_get_peak(hdsp, peak_rms);
		पूर्ण
	पूर्ण
	हाल SNDRV_HDSP_IOCTL_GET_CONFIG_INFO: अणु
		काष्ठा hdsp_config_info info;
		अचिन्हित दीर्घ flags;
		पूर्णांक i;

		err = hdsp_check_क्रम_iobox(hdsp);
		अगर (err < 0)
			वापस err;

		err = hdsp_check_क्रम_firmware(hdsp, 1);
		अगर (err < 0)
			वापस err;

		स_रखो(&info, 0, माप(info));
		spin_lock_irqsave(&hdsp->lock, flags);
		info.pref_sync_ref = (अचिन्हित अक्षर)hdsp_pref_sync_ref(hdsp);
		info.wordघड़ी_sync_check = (अचिन्हित अक्षर)hdsp_wc_sync_check(hdsp);
		अगर (hdsp->io_type != H9632)
		    info.adatsync_sync_check = (अचिन्हित अक्षर)hdsp_adatsync_sync_check(hdsp);
		info.spdअगर_sync_check = (अचिन्हित अक्षर)hdsp_spdअगर_sync_check(hdsp);
		क्रम (i = 0; i < ((hdsp->io_type != Multअगरace && hdsp->io_type != RPM && hdsp->io_type != H9632) ? 3 : 1); ++i)
			info.adat_sync_check[i] = (अचिन्हित अक्षर)hdsp_adat_sync_check(hdsp, i);
		info.spdअगर_in = (अचिन्हित अक्षर)hdsp_spdअगर_in(hdsp);
		info.spdअगर_out = (अचिन्हित अक्षर)hdsp_toggle_setting(hdsp,
				HDSP_SPDIFOpticalOut);
		info.spdअगर_professional = (अचिन्हित अक्षर)
			hdsp_toggle_setting(hdsp, HDSP_SPDIFProfessional);
		info.spdअगर_emphasis = (अचिन्हित अक्षर)
			hdsp_toggle_setting(hdsp, HDSP_SPDIFEmphasis);
		info.spdअगर_nonaudio = (अचिन्हित अक्षर)
			hdsp_toggle_setting(hdsp, HDSP_SPDIFNonAudio);
		info.spdअगर_sample_rate = hdsp_spdअगर_sample_rate(hdsp);
		info.प्रणाली_sample_rate = hdsp->प्रणाली_sample_rate;
		info.स्वतःsync_sample_rate = hdsp_बाह्यal_sample_rate(hdsp);
		info.प्रणाली_घड़ी_mode = (अचिन्हित अक्षर)hdsp_प्रणाली_घड़ी_mode(hdsp);
		info.घड़ी_source = (अचिन्हित अक्षर)hdsp_घड़ी_source(hdsp);
		info.स्वतःsync_ref = (अचिन्हित अक्षर)hdsp_स्वतःsync_ref(hdsp);
		info.line_out = (अचिन्हित अक्षर)
			hdsp_toggle_setting(hdsp, HDSP_LineOut);
		अगर (hdsp->io_type == H9632) अणु
			info.da_gain = (अचिन्हित अक्षर)hdsp_da_gain(hdsp);
			info.ad_gain = (अचिन्हित अक्षर)hdsp_ad_gain(hdsp);
			info.phone_gain = (अचिन्हित अक्षर)hdsp_phone_gain(hdsp);
			info.xlr_अवरोधout_cable =
				(अचिन्हित अक्षर)hdsp_toggle_setting(hdsp,
					HDSP_XLRBreakoutCable);

		पूर्ण अन्यथा अगर (hdsp->io_type == RPM) अणु
			info.da_gain = (अचिन्हित अक्षर) hdsp_rpm_input12(hdsp);
			info.ad_gain = (अचिन्हित अक्षर) hdsp_rpm_input34(hdsp);
		पूर्ण
		अगर (hdsp->io_type == H9632 || hdsp->io_type == H9652)
			info.analog_extension_board =
				(अचिन्हित अक्षर)hdsp_toggle_setting(hdsp,
					    HDSP_AnalogExtensionBoard);
		spin_unlock_irqrestore(&hdsp->lock, flags);
		अगर (copy_to_user(argp, &info, माप(info)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल SNDRV_HDSP_IOCTL_GET_9632_AEB: अणु
		काष्ठा hdsp_9632_aeb h9632_aeb;

		अगर (hdsp->io_type != H9632) वापस -EINVAL;
		h9632_aeb.aebi = hdsp->ss_in_channels - H9632_SS_CHANNELS;
		h9632_aeb.aebo = hdsp->ss_out_channels - H9632_SS_CHANNELS;
		अगर (copy_to_user(argp, &h9632_aeb, माप(h9632_aeb)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल SNDRV_HDSP_IOCTL_GET_VERSION: अणु
		काष्ठा hdsp_version hdsp_version;
		पूर्णांक err;

		अगर (hdsp->io_type == H9652 || hdsp->io_type == H9632) वापस -EINVAL;
		अगर (hdsp->io_type == Undefined) अणु
			अगर ((err = hdsp_get_iobox_version(hdsp)) < 0)
				वापस err;
		पूर्ण
		स_रखो(&hdsp_version, 0, माप(hdsp_version));
		hdsp_version.io_type = hdsp->io_type;
		hdsp_version.firmware_rev = hdsp->firmware_rev;
		अगर ((err = copy_to_user(argp, &hdsp_version, माप(hdsp_version))))
		    	वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल SNDRV_HDSP_IOCTL_UPLOAD_FIRMWARE: अणु
		काष्ठा hdsp_firmware firmware;
		u32 __user *firmware_data;
		पूर्णांक err;

		अगर (hdsp->io_type == H9652 || hdsp->io_type == H9632) वापस -EINVAL;
		/* SNDRV_HDSP_IOCTL_GET_VERSION must have been called */
		अगर (hdsp->io_type == Undefined) वापस -EINVAL;

		अगर (hdsp->state & (HDSP_FirmwareCached | HDSP_FirmwareLoaded))
			वापस -EBUSY;

		dev_info(hdsp->card->dev,
			 "initializing firmware upload\n");
		अगर (copy_from_user(&firmware, argp, माप(firmware)))
			वापस -EFAULT;
		firmware_data = (u32 __user *)firmware.firmware_data;

		अगर (hdsp_check_क्रम_iobox (hdsp))
			वापस -EIO;

		अगर (!hdsp->fw_uploaded) अणु
			hdsp->fw_uploaded = vदो_स्मृति(HDSP_FIRMWARE_SIZE);
			अगर (!hdsp->fw_uploaded)
				वापस -ENOMEM;
		पूर्ण

		अगर (copy_from_user(hdsp->fw_uploaded, firmware_data,
				   HDSP_FIRMWARE_SIZE)) अणु
			vमुक्त(hdsp->fw_uploaded);
			hdsp->fw_uploaded = शून्य;
			वापस -EFAULT;
		पूर्ण

		hdsp->state |= HDSP_FirmwareCached;

		अगर ((err = snd_hdsp_load_firmware_from_cache(hdsp)) < 0)
			वापस err;

		अगर (!(hdsp->state & HDSP_InitializationComplete)) अणु
			अगर ((err = snd_hdsp_enable_io(hdsp)) < 0)
				वापस err;

			snd_hdsp_initialize_channels(hdsp);
			snd_hdsp_initialize_midi_flush(hdsp);

			अगर ((err = snd_hdsp_create_alsa_devices(hdsp->card, hdsp)) < 0) अणु
				dev_err(hdsp->card->dev,
					"error creating alsa devices\n");
				वापस err;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	हाल SNDRV_HDSP_IOCTL_GET_MIXER: अणु
		काष्ठा hdsp_mixer __user *mixer = (काष्ठा hdsp_mixer __user *)argp;
		अगर (copy_to_user(mixer->matrix, hdsp->mixer_matrix, माप(अचिन्हित लघु)*HDSP_MATRIX_MIXER_SIZE))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_hdsp_playback_ops = अणु
	.खोलो =		snd_hdsp_playback_खोलो,
	.बंद =	snd_hdsp_playback_release,
	.ioctl =	snd_hdsp_ioctl,
	.hw_params =	snd_hdsp_hw_params,
	.prepare =	snd_hdsp_prepare,
	.trigger =	snd_hdsp_trigger,
	.poपूर्णांकer =	snd_hdsp_hw_poपूर्णांकer,
	.copy_user =	snd_hdsp_playback_copy,
	.copy_kernel =	snd_hdsp_playback_copy_kernel,
	.fill_silence =	snd_hdsp_hw_silence,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_hdsp_capture_ops = अणु
	.खोलो =		snd_hdsp_capture_खोलो,
	.बंद =	snd_hdsp_capture_release,
	.ioctl =	snd_hdsp_ioctl,
	.hw_params =	snd_hdsp_hw_params,
	.prepare =	snd_hdsp_prepare,
	.trigger =	snd_hdsp_trigger,
	.poपूर्णांकer =	snd_hdsp_hw_poपूर्णांकer,
	.copy_user =	snd_hdsp_capture_copy,
	.copy_kernel =	snd_hdsp_capture_copy_kernel,
पूर्ण;

अटल पूर्णांक snd_hdsp_create_hwdep(काष्ठा snd_card *card, काष्ठा hdsp *hdsp)
अणु
	काष्ठा snd_hwdep *hw;
	पूर्णांक err;

	अगर ((err = snd_hwdep_new(card, "HDSP hwdep", 0, &hw)) < 0)
		वापस err;

	hdsp->hwdep = hw;
	hw->निजी_data = hdsp;
	म_नकल(hw->name, "HDSP hwdep interface");

	hw->ops.ioctl = snd_hdsp_hwdep_ioctl;
	hw->ops.ioctl_compat = snd_hdsp_hwdep_ioctl;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_create_pcm(काष्ठा snd_card *card, काष्ठा hdsp *hdsp)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(card, hdsp->card_name, 0, 1, 1, &pcm)) < 0)
		वापस err;

	hdsp->pcm = pcm;
	pcm->निजी_data = hdsp;
	म_नकल(pcm->name, hdsp->card_name);

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_hdsp_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_hdsp_capture_ops);

	pcm->info_flags = SNDRV_PCM_INFO_JOINT_DUPLEX;

	वापस 0;
पूर्ण

अटल व्योम snd_hdsp_9652_enable_mixer (काष्ठा hdsp *hdsp)
अणु
        hdsp->control2_रेजिस्टर |= HDSP_9652_ENABLE_MIXER;
	hdsp_ग_लिखो (hdsp, HDSP_control2Reg, hdsp->control2_रेजिस्टर);
पूर्ण

अटल पूर्णांक snd_hdsp_enable_io (काष्ठा hdsp *hdsp)
अणु
	पूर्णांक i;

	अगर (hdsp_fअगरo_रुको (hdsp, 0, 100)) अणु
		dev_err(hdsp->card->dev,
			"enable_io fifo_wait failed\n");
		वापस -EIO;
	पूर्ण

	क्रम (i = 0; i < hdsp->max_channels; ++i) अणु
		hdsp_ग_लिखो (hdsp, HDSP_inputEnable + (4 * i), 1);
		hdsp_ग_लिखो (hdsp, HDSP_outputEnable + (4 * i), 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम snd_hdsp_initialize_channels(काष्ठा hdsp *hdsp)
अणु
	पूर्णांक status, aebi_channels, aebo_channels, i;

	चयन (hdsp->io_type) अणु
	हाल Digअगरace:
		hdsp->card_name = "RME Hammerfall DSP + Digiface";
		hdsp->ss_in_channels = hdsp->ss_out_channels = DIGIFACE_SS_CHANNELS;
		hdsp->ds_in_channels = hdsp->ds_out_channels = DIGIFACE_DS_CHANNELS;
		अवरोध;

	हाल H9652:
		hdsp->card_name = "RME Hammerfall HDSP 9652";
		hdsp->ss_in_channels = hdsp->ss_out_channels = H9652_SS_CHANNELS;
		hdsp->ds_in_channels = hdsp->ds_out_channels = H9652_DS_CHANNELS;
		अवरोध;

	हाल H9632:
		status = hdsp_पढ़ो(hdsp, HDSP_statusRegister);
		/* HDSP_AEBx bits are low when AEB are connected */
		aebi_channels = (status & HDSP_AEBI) ? 0 : 4;
		aebo_channels = (status & HDSP_AEBO) ? 0 : 4;
		hdsp->card_name = "RME Hammerfall HDSP 9632";
		hdsp->ss_in_channels = H9632_SS_CHANNELS+aebi_channels;
		hdsp->ds_in_channels = H9632_DS_CHANNELS+aebi_channels;
		hdsp->qs_in_channels = H9632_QS_CHANNELS+aebi_channels;
		hdsp->ss_out_channels = H9632_SS_CHANNELS+aebo_channels;
		hdsp->ds_out_channels = H9632_DS_CHANNELS+aebo_channels;
		hdsp->qs_out_channels = H9632_QS_CHANNELS+aebo_channels;
		/* Disable loopback of output channels, as the set function
		 * only sets on a change we fake all bits (channels) as enabled.
		 */
		hdsp->io_loopback = 0xffffffff;
		क्रम (i = 0; i < hdsp->max_channels; ++i)
			hdsp_loopback_set(hdsp, i, false);
		अवरोध;

	हाल Multअगरace:
		hdsp->card_name = "RME Hammerfall DSP + Multiface";
		hdsp->ss_in_channels = hdsp->ss_out_channels = MULTIFACE_SS_CHANNELS;
		hdsp->ds_in_channels = hdsp->ds_out_channels = MULTIFACE_DS_CHANNELS;
		अवरोध;

	हाल RPM:
		hdsp->card_name = "RME Hammerfall DSP + RPM";
		hdsp->ss_in_channels = RPM_CHANNELS-1;
		hdsp->ss_out_channels = RPM_CHANNELS;
		hdsp->ds_in_channels = RPM_CHANNELS-1;
		hdsp->ds_out_channels = RPM_CHANNELS;
		अवरोध;

	शेष:
 		/* should never get here */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम snd_hdsp_initialize_midi_flush (काष्ठा hdsp *hdsp)
अणु
	snd_hdsp_flush_midi_input (hdsp, 0);
	snd_hdsp_flush_midi_input (hdsp, 1);
पूर्ण

अटल पूर्णांक snd_hdsp_create_alsa_devices(काष्ठा snd_card *card, काष्ठा hdsp *hdsp)
अणु
	पूर्णांक err;

	अगर ((err = snd_hdsp_create_pcm(card, hdsp)) < 0) अणु
		dev_err(card->dev,
			"Error creating pcm interface\n");
		वापस err;
	पूर्ण


	अगर ((err = snd_hdsp_create_midi(card, hdsp, 0)) < 0) अणु
		dev_err(card->dev,
			"Error creating first midi interface\n");
		वापस err;
	पूर्ण

	अगर (hdsp->io_type == Digअगरace || hdsp->io_type == H9652) अणु
		अगर ((err = snd_hdsp_create_midi(card, hdsp, 1)) < 0) अणु
			dev_err(card->dev,
				"Error creating second midi interface\n");
			वापस err;
		पूर्ण
	पूर्ण

	अगर ((err = snd_hdsp_create_controls(card, hdsp)) < 0) अणु
		dev_err(card->dev,
			"Error creating ctl interface\n");
		वापस err;
	पूर्ण

	snd_hdsp_proc_init(hdsp);

	hdsp->प्रणाली_sample_rate = -1;
	hdsp->playback_pid = -1;
	hdsp->capture_pid = -1;
	hdsp->capture_substream = शून्य;
	hdsp->playback_substream = शून्य;

	अगर ((err = snd_hdsp_set_शेषs(hdsp)) < 0) अणु
		dev_err(card->dev,
			"Error setting default values\n");
		वापस err;
	पूर्ण

	अगर (!(hdsp->state & HDSP_InitializationComplete)) अणु
		म_नकल(card->लघुname, "Hammerfall DSP");
		प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d", hdsp->card_name,
			hdsp->port, hdsp->irq);

		अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
			dev_err(card->dev,
				"error registering card\n");
			वापस err;
		पूर्ण
		hdsp->state |= HDSP_InitializationComplete;
	पूर्ण

	वापस 0;
पूर्ण

/* load firmware via hotplug fw loader */
अटल पूर्णांक hdsp_request_fw_loader(काष्ठा hdsp *hdsp)
अणु
	स्थिर अक्षर *fwfile;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक err;

	अगर (hdsp->io_type == H9652 || hdsp->io_type == H9632)
		वापस 0;
	अगर (hdsp->io_type == Undefined) अणु
		अगर ((err = hdsp_get_iobox_version(hdsp)) < 0)
			वापस err;
		अगर (hdsp->io_type == H9652 || hdsp->io_type == H9632)
			वापस 0;
	पूर्ण

	/* caution: max length of firmware filename is 30! */
	चयन (hdsp->io_type) अणु
	हाल RPM:
		fwfile = "rpm_firmware.bin";
		अवरोध;
	हाल Multअगरace:
		अगर (hdsp->firmware_rev == 0xa)
			fwfile = "multiface_firmware.bin";
		अन्यथा
			fwfile = "multiface_firmware_rev11.bin";
		अवरोध;
	हाल Digअगरace:
		अगर (hdsp->firmware_rev == 0xa)
			fwfile = "digiface_firmware.bin";
		अन्यथा
			fwfile = "digiface_firmware_rev11.bin";
		अवरोध;
	शेष:
		dev_err(hdsp->card->dev,
			"invalid io_type %d\n", hdsp->io_type);
		वापस -EINVAL;
	पूर्ण

	अगर (request_firmware(&fw, fwfile, &hdsp->pci->dev)) अणु
		dev_err(hdsp->card->dev,
			"cannot load firmware %s\n", fwfile);
		वापस -ENOENT;
	पूर्ण
	अगर (fw->size < HDSP_FIRMWARE_SIZE) अणु
		dev_err(hdsp->card->dev,
			"too short firmware size %d (expected %d)\n",
			   (पूर्णांक)fw->size, HDSP_FIRMWARE_SIZE);
		release_firmware(fw);
		वापस -EINVAL;
	पूर्ण

	hdsp->firmware = fw;

	hdsp->state |= HDSP_FirmwareCached;

	अगर ((err = snd_hdsp_load_firmware_from_cache(hdsp)) < 0)
		वापस err;

	अगर (!(hdsp->state & HDSP_InitializationComplete)) अणु
		अगर ((err = snd_hdsp_enable_io(hdsp)) < 0)
			वापस err;

		अगर ((err = snd_hdsp_create_hwdep(hdsp->card, hdsp)) < 0) अणु
			dev_err(hdsp->card->dev,
				"error creating hwdep device\n");
			वापस err;
		पूर्ण
		snd_hdsp_initialize_channels(hdsp);
		snd_hdsp_initialize_midi_flush(hdsp);
		अगर ((err = snd_hdsp_create_alsa_devices(hdsp->card, hdsp)) < 0) अणु
			dev_err(hdsp->card->dev,
				"error creating alsa devices\n");
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_create(काष्ठा snd_card *card,
			   काष्ठा hdsp *hdsp)
अणु
	काष्ठा pci_dev *pci = hdsp->pci;
	पूर्णांक err;
	पूर्णांक is_9652 = 0;
	पूर्णांक is_9632 = 0;

	hdsp->irq = -1;
	hdsp->state = 0;
	hdsp->midi[0].rmidi = शून्य;
	hdsp->midi[1].rmidi = शून्य;
	hdsp->midi[0].input = शून्य;
	hdsp->midi[1].input = शून्य;
	hdsp->midi[0].output = शून्य;
	hdsp->midi[1].output = शून्य;
	hdsp->midi[0].pending = 0;
	hdsp->midi[1].pending = 0;
	spin_lock_init(&hdsp->midi[0].lock);
	spin_lock_init(&hdsp->midi[1].lock);
	hdsp->iobase = शून्य;
	hdsp->control_रेजिस्टर = 0;
	hdsp->control2_रेजिस्टर = 0;
	hdsp->io_type = Undefined;
	hdsp->max_channels = 26;

	hdsp->card = card;

	spin_lock_init(&hdsp->lock);

	INIT_WORK(&hdsp->midi_work, hdsp_midi_work);

	pci_पढ़ो_config_word(hdsp->pci, PCI_CLASS_REVISION, &hdsp->firmware_rev);
	hdsp->firmware_rev &= 0xff;

	/* From Martin Bjoernsen :
	    "It is important that the card's latency समयr रेजिस्टर in
	    the PCI configuration space is set to a value much larger
	    than 0 by the computer's BIOS or the driver.
	    The winकरोws driver always sets this 8 bit रेजिस्टर [...]
	    to its maximum 255 to aव्योम problems with some computers."
	*/
	pci_ग_लिखो_config_byte(hdsp->pci, PCI_LATENCY_TIMER, 0xFF);

	म_नकल(card->driver, "H-DSP");
	म_नकल(card->mixername, "Xilinx FPGA");

	अगर (hdsp->firmware_rev < 0xa)
		वापस -ENODEV;
	अन्यथा अगर (hdsp->firmware_rev < 0x64)
		hdsp->card_name = "RME Hammerfall DSP";
	अन्यथा अगर (hdsp->firmware_rev < 0x96) अणु
		hdsp->card_name = "RME HDSP 9652";
		is_9652 = 1;
	पूर्ण अन्यथा अणु
		hdsp->card_name = "RME HDSP 9632";
		hdsp->max_channels = 16;
		is_9632 = 1;
	पूर्ण

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	pci_set_master(hdsp->pci);

	अगर ((err = pci_request_regions(pci, "hdsp")) < 0)
		वापस err;
	hdsp->port = pci_resource_start(pci, 0);
	अगर ((hdsp->iobase = ioremap(hdsp->port, HDSP_IO_EXTENT)) == शून्य) अणु
		dev_err(hdsp->card->dev, "unable to remap region 0x%lx-0x%lx\n",
			hdsp->port, hdsp->port + HDSP_IO_EXTENT - 1);
		वापस -EBUSY;
	पूर्ण

	अगर (request_irq(pci->irq, snd_hdsp_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, hdsp)) अणु
		dev_err(hdsp->card->dev, "unable to use IRQ %d\n", pci->irq);
		वापस -EBUSY;
	पूर्ण

	hdsp->irq = pci->irq;
	card->sync_irq = hdsp->irq;
	hdsp->precise_ptr = 0;
	hdsp->use_midi_work = 1;
	hdsp->dds_value = 0;

	अगर ((err = snd_hdsp_initialize_memory(hdsp)) < 0)
		वापस err;

	अगर (!is_9652 && !is_9632) अणु
		/* we रुको a maximum of 10 seconds to let freshly
		 * inserted cardbus cards करो their hardware init */
		err = hdsp_रुको_क्रम_iobox(hdsp, 1000, 10);

		अगर (err < 0)
			वापस err;

		अगर ((hdsp_पढ़ो (hdsp, HDSP_statusRegister) & HDSP_DllError) != 0) अणु
			अगर ((err = hdsp_request_fw_loader(hdsp)) < 0)
				/* we करोn't fail as this can happen
				   अगर userspace is not पढ़ोy क्रम
				   firmware upload
				*/
				dev_err(hdsp->card->dev,
					"couldn't get firmware from userspace. try using hdsploader\n");
			अन्यथा
				/* init is complete, we वापस */
				वापस 0;
			/* we defer initialization */
			dev_info(hdsp->card->dev,
				 "card initialization pending : waiting for firmware\n");
			अगर ((err = snd_hdsp_create_hwdep(card, hdsp)) < 0)
				वापस err;
			वापस 0;
		पूर्ण अन्यथा अणु
			dev_info(hdsp->card->dev,
				 "Firmware already present, initializing card.\n");
			अगर (hdsp_पढ़ो(hdsp, HDSP_status2Register) & HDSP_version2)
				hdsp->io_type = RPM;
			अन्यथा अगर (hdsp_पढ़ो(hdsp, HDSP_status2Register) & HDSP_version1)
				hdsp->io_type = Multअगरace;
			अन्यथा
				hdsp->io_type = Digअगरace;
		पूर्ण
	पूर्ण

	अगर ((err = snd_hdsp_enable_io(hdsp)) != 0)
		वापस err;

	अगर (is_9652)
	        hdsp->io_type = H9652;

	अगर (is_9632)
		hdsp->io_type = H9632;

	अगर ((err = snd_hdsp_create_hwdep(card, hdsp)) < 0)
		वापस err;

	snd_hdsp_initialize_channels(hdsp);
	snd_hdsp_initialize_midi_flush(hdsp);

	hdsp->state |= HDSP_FirmwareLoaded;

	अगर ((err = snd_hdsp_create_alsa_devices(card, hdsp)) < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdsp_मुक्त(काष्ठा hdsp *hdsp)
अणु
	अगर (hdsp->port) अणु
		/* stop the audio, and cancel all पूर्णांकerrupts */
		cancel_work_sync(&hdsp->midi_work);
		hdsp->control_रेजिस्टर &= ~(HDSP_Start|HDSP_AudioInterruptEnable|HDSP_Midi0InterruptEnable|HDSP_Midi1InterruptEnable);
		hdsp_ग_लिखो (hdsp, HDSP_controlRegister, hdsp->control_रेजिस्टर);
	पूर्ण

	अगर (hdsp->irq >= 0)
		मुक्त_irq(hdsp->irq, (व्योम *)hdsp);

	snd_hdsp_मुक्त_buffers(hdsp);

	release_firmware(hdsp->firmware);
	vमुक्त(hdsp->fw_uploaded);
	iounmap(hdsp->iobase);

	अगर (hdsp->port)
		pci_release_regions(hdsp->pci);

	अगर (pci_is_enabled(hdsp->pci))
		pci_disable_device(hdsp->pci);
	वापस 0;
पूर्ण

अटल व्योम snd_hdsp_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा hdsp *hdsp = card->निजी_data;

	अगर (hdsp)
		snd_hdsp_मुक्त(hdsp);
पूर्ण

अटल पूर्णांक snd_hdsp_probe(काष्ठा pci_dev *pci,
			  स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा hdsp *hdsp;
	काष्ठा snd_card *card;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा hdsp), &card);
	अगर (err < 0)
		वापस err;

	hdsp = card->निजी_data;
	card->निजी_मुक्त = snd_hdsp_card_मुक्त;
	hdsp->dev = dev;
	hdsp->pci = pci;
	err = snd_hdsp_create(card, hdsp);
	अगर (err)
		जाओ मुक्त_card;

	म_नकल(card->लघुname, "Hammerfall DSP");
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d", hdsp->card_name,
		hdsp->port, hdsp->irq);
	err = snd_card_रेजिस्टर(card);
	अगर (err) अणु
मुक्त_card:
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_hdsp_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver hdsp_driver = अणु
	.name =     KBUILD_MODNAME,
	.id_table = snd_hdsp_ids,
	.probe =    snd_hdsp_probe,
	.हटाओ = snd_hdsp_हटाओ,
पूर्ण;

module_pci_driver(hdsp_driver);
