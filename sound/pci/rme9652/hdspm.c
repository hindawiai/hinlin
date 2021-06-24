<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम RME Hammerfall DSP MADI audio पूर्णांकerface(s)
 *
 *      Copyright (c) 2003 Winfried Ritsch (IEM)
 *      code based on hdsp.c   Paul Davis
 *                             Marcus Andersson
 *                             Thomas Charbonnel
 *      Modअगरied 2006-06-01 क्रम AES32 support by Remy Bruno
 *                                               <remy.bruno@trinnov.com>
 *
 *      Modअगरied 2009-04-13 क्रम proper metering by Florian Faber
 *                                               <faber@faberman.de>
 *
 *      Modअगरied 2009-04-14 क्रम native भग्न support by Florian Faber
 *                                               <faber@faberman.de>
 *
 *      Modअगरied 2009-04-26 fixed bug in rms metering by Florian Faber
 *                                               <faber@faberman.de>
 *
 *      Modअगरied 2009-04-30 added hw serial number support by Florian Faber
 *
 *      Modअगरied 2011-01-14 added S/PDIF input on RayDATs by Adrian Knoth
 *
 *	Modअगरied 2011-01-25 variable period sizes on RayDAT/AIO by Adrian Knoth
 *
 *      Modअगरied 2019-05-23 fix AIO single speed ADAT capture and playback
 *      by Philippe.Bekaert@uhasselt.be
 */

/* *************    Register Documentation   *******************************************************
 *
 * Work in progress! Documentation is based on the code in this file.
 *
 * --------- HDSPM_controlRegister ---------
 * :7654.3210:7654.3210:7654.3210:7654.3210: bit number per byte
 * :||||.||||:||||.||||:||||.||||:||||.||||:
 * :3322.2222:2222.1111:1111.1100:0000.0000: bit number
 * :1098.7654:3210.9876:5432.1098:7654.3210: 0..31
 * :||||.||||:||||.||||:||||.||||:||||.||||:
 * :8421.8421:8421.8421:8421.8421:8421.8421: hex digit
 * :    .    :    .    :    .    :  x .    :  HDSPM_AudioInterruptEnable \_ setting both bits
 * :    .    :    .    :    .    :    .   x:  HDSPM_Start                /  enables audio IO
 * :    .    :    .    :    .    :   x.    :  HDSPM_ClockModeMaster - 1: Master, 0: Slave
 * :    .    :    .    :    .    :    .210 :  HDSPM_LatencyMask - 3 Bit value क्रम latency
 * :    .    :    .    :    .    :    .    :      0:64, 1:128, 2:256, 3:512,
 * :    .    :    .    :    .    :    .    :      4:1024, 5:2048, 6:4096, 7:8192
 * :x   .    :    .    :    .   x:xx  .    :  HDSPM_FrequencyMask
 * :    .    :    .    :    .    :10  .    :  HDSPM_Frequency1|HDSPM_Frequency0: 1=32K,2=44.1K,3=48K,0=??
 * :    .    :    .    :    .   x:    .    :  <MADI> HDSPM_DoubleSpeed
 * :x   .    :    .    :    .    :    .    :  <MADI> HDSPM_QuadSpeed
 * :    .  3 :    .  10:  2 .    :    .    :  HDSPM_SyncRefMask :
 * :    .    :    .   x:    .    :    .    :  HDSPM_SyncRef0
 * :    .    :    .  x :    .    :    .    :  HDSPM_SyncRef1
 * :    .    :    .    :  x .    :    .    :  <AES32> HDSPM_SyncRef2
 * :    .  x :    .    :    .    :    .    :  <AES32> HDSPM_SyncRef3
 * :    .    :    .  10:    .    :    .    :  <MADI> sync ref: 0:WC, 1:Madi, 2:TCO, 3:SyncIn
 * :    .  3 :    .  10:  2 .    :    .    :  <AES32>  0:WC, 1:AES1 ... 8:AES8, 9: TCO, 10:SyncIn?
 * :    .  x :    .    :    .    :    .    :  <MADIe> HDSPe_FLOAT_FORMAT
 * :    .    :    .    : x  .    :    .    :  <MADI> HDSPM_InputSelect0 : 0=optical,1=coax
 * :    .    :    .    :x   .    :    .    :  <MADI> HDSPM_InputSelect1
 * :    .    :    .x   :    .    :    .    :  <MADI> HDSPM_clr_पंचांगs
 * :    .    :    .    :    . x  :    .    :  <MADI> HDSPM_TX_64ch
 * :    .    :    .    :    . x  :    .    :  <AES32> HDSPM_Emphasis
 * :    .    :    .    :    .x   :    .    :  <MADI> HDSPM_AutoInp
 * :    .    :    . x  :    .    :    .    :  <MADI> HDSPM_SMUX
 * :    .    :    .x   :    .    :    .    :  <MADI> HDSPM_clr_पंचांगs
 * :    .    :   x.    :    .    :    .    :  <MADI> HDSPM_taxi_reset
 * :    .   x:    .    :    .    :    .    :  <MADI> HDSPM_LineOut
 * :    .   x:    .    :    .    :    .    :  <AES32> ??????????????????
 * :    .    :   x.    :    .    :    .    :  <AES32> HDSPM_WCK48
 * :    .    :    .    :    .x   :    .    :  <AES32> HDSPM_Dolby
 * :    .    : x  .    :    .    :    .    :  HDSPM_Midi0InterruptEnable
 * :    .    :x   .    :    .    :    .    :  HDSPM_Midi1InterruptEnable
 * :    .    :  x .    :    .    :    .    :  HDSPM_Midi2InterruptEnable
 * :    . x  :    .    :    .    :    .    :  <MADI> HDSPM_Midi3InterruptEnable
 * :    . x  :    .    :    .    :    .    :  <AES32> HDSPM_DS_DoubleWire
 * :    .x   :    .    :    .    :    .    :  <AES32> HDSPM_QS_DoubleWire
 * :   x.    :    .    :    .    :    .    :  <AES32> HDSPM_QS_QuadWire
 * :    .    :    .    :    .  x :    .    :  <AES32> HDSPM_Professional
 * : x  .    :    .    :    .    :    .    :  HDSPM_wclk_sel
 * :    .    :    .    :    .    :    .    :
 * :7654.3210:7654.3210:7654.3210:7654.3210: bit number per byte
 * :||||.||||:||||.||||:||||.||||:||||.||||:
 * :3322.2222:2222.1111:1111.1100:0000.0000: bit number
 * :1098.7654:3210.9876:5432.1098:7654.3210: 0..31
 * :||||.||||:||||.||||:||||.||||:||||.||||:
 * :8421.8421:8421.8421:8421.8421:8421.8421:hex digit
 *
 *
 *
 * AIO / RayDAT only
 *
 * ------------ HDSPM_WR_SETTINGS ----------
 * :3322.2222:2222.1111:1111.1100:0000.0000: bit number per byte
 * :1098.7654:3210.9876:5432.1098:7654.3210:
 * :||||.||||:||||.||||:||||.||||:||||.||||: bit number
 * :7654.3210:7654.3210:7654.3210:7654.3210: 0..31
 * :||||.||||:||||.||||:||||.||||:||||.||||:
 * :8421.8421:8421.8421:8421.8421:8421.8421: hex digit
 * :    .    :    .    :    .    :    .   x: HDSPM_c0Master 1: Master, 0: Slave
 * :    .    :    .    :    .    :    .  x : HDSPM_c0_SyncRef0
 * :    .    :    .    :    .    :    . x  : HDSPM_c0_SyncRef1
 * :    .    :    .    :    .    :    .x   : HDSPM_c0_SyncRef2
 * :    .    :    .    :    .    :   x.    : HDSPM_c0_SyncRef3
 * :    .    :    .    :    .    :   3.210 : HDSPM_c0_SyncRefMask:
 * :    .    :    .    :    .    :    .    :  RayDat: 0:WC, 1:AES, 2:SPDIF, 3..6: ADAT1..4,
 * :    .    :    .    :    .    :    .    :          9:TCO, 10:SyncIn
 * :    .    :    .    :    .    :    .    :  AIO: 0:WC, 1:AES, 2: SPDIF, 3: ATAT,
 * :    .    :    .    :    .    :    .    :          9:TCO, 10:SyncIn
 * :    .    :    .    :    .    :    .    :
 * :    .    :    .    :    .    :    .    :
 * :3322.2222:2222.1111:1111.1100:0000.0000: bit number per byte
 * :1098.7654:3210.9876:5432.1098:7654.3210:
 * :||||.||||:||||.||||:||||.||||:||||.||||: bit number
 * :7654.3210:7654.3210:7654.3210:7654.3210: 0..31
 * :||||.||||:||||.||||:||||.||||:||||.||||:
 * :8421.8421:8421.8421:8421.8421:8421.8421: hex digit
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/math64.h>
#समावेश <linux/पन.स>
#समावेश <linux/nospec.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/info.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/initval.h>

#समावेश <sound/hdspm.h>

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	  /* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	  /* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;/* Enable this card */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for RME HDSPM interface.");

module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for RME HDSPM interface.");

module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable/disable specific HDSPM soundcards.");


MODULE_AUTHOR
(
	"Winfried Ritsch <ritsch_AT_iem.at>, "
	"Paul Davis <paul@linuxaudiosystems.com>, "
	"Marcus Andersson, Thomas Charbonnel <thomas@undata.org>, "
	"Remy Bruno <remy.bruno@trinnov.com>, "
	"Florian Faber <faberman@linuxproaudio.org>, "
	"Adrian Knoth <adi@drcomp.erfurt.thur.de>"
);
MODULE_DESCRIPTION("RME HDSPM");
MODULE_LICENSE("GPL");

/* --- Write रेजिस्टरs. ---
  These are defined as byte-offsets from the iobase value.  */

#घोषणा HDSPM_WR_SETTINGS             0
#घोषणा HDSPM_outputBufferAddress    32
#घोषणा HDSPM_inputBufferAddress     36
#घोषणा HDSPM_controlRegister	     64
#घोषणा HDSPM_पूर्णांकerruptConfirmation  96
#घोषणा HDSPM_control2Reg	     256  /* not in specs ???????? */
#घोषणा HDSPM_freqReg                256  /* क्रम setting arbitrary घड़ी values (DDS feature) */
#घोषणा HDSPM_midiDataOut0	     352  /* just believe in old code */
#घोषणा HDSPM_midiDataOut1	     356
#घोषणा HDSPM_eeprom_wr		     384  /* क्रम AES32 */

/* DMA enable क्रम 64 channels, only Bit 0 is relevant */
#घोषणा HDSPM_outputEnableBase       512  /* 512-767  input  DMA */
#घोषणा HDSPM_inputEnableBase        768  /* 768-1023 output DMA */

/* 16 page addresses क्रम each of the 64 channels DMA buffer in and out
   (each 64k=16*4k) Buffer must be 4k aligned (which is शेष i386 ????) */
#घोषणा HDSPM_pageAddressBufferOut       8192
#घोषणा HDSPM_pageAddressBufferIn        (HDSPM_pageAddressBufferOut+64*16*4)

#घोषणा HDSPM_MADI_mixerBase    32768	/* 32768-65535 क्रम 2x64x64 Fader */

#घोषणा HDSPM_MATRIX_MIXER_SIZE  8192	/* = 2*64*64 * 4 Byte => 32kB */

/* --- Read रेजिस्टरs. ---
   These are defined as byte-offsets from the iobase value */
#घोषणा HDSPM_statusRegister    0
/*#घोषणा HDSPM_statusRegister2  96 */
/* after RME Winकरोws driver sources, status2 is 4-byte word # 48 = word at
 * offset 192, क्रम AES32 *and* MADI
 * => need to check that offset 192 is working on MADI */
#घोषणा HDSPM_statusRegister2  192
#घोषणा HDSPM_समयcodeRegister 128

/* AIO, RayDAT */
#घोषणा HDSPM_RD_STATUS_0 0
#घोषणा HDSPM_RD_STATUS_1 64
#घोषणा HDSPM_RD_STATUS_2 128
#घोषणा HDSPM_RD_STATUS_3 192

#घोषणा HDSPM_RD_TCO           256
#घोषणा HDSPM_RD_PLL_FREQ      512
#घोषणा HDSPM_WR_TCO           128

#घोषणा HDSPM_TCO1_TCO_lock			0x00000001
#घोषणा HDSPM_TCO1_WCK_Input_Range_LSB		0x00000002
#घोषणा HDSPM_TCO1_WCK_Input_Range_MSB		0x00000004
#घोषणा HDSPM_TCO1_LTC_Input_valid		0x00000008
#घोषणा HDSPM_TCO1_WCK_Input_valid		0x00000010
#घोषणा HDSPM_TCO1_Video_Input_Format_NTSC	0x00000020
#घोषणा HDSPM_TCO1_Video_Input_Format_PAL	0x00000040

#घोषणा HDSPM_TCO1_set_TC			0x00000100
#घोषणा HDSPM_TCO1_set_drop_frame_flag		0x00000200
#घोषणा HDSPM_TCO1_LTC_Format_LSB		0x00000400
#घोषणा HDSPM_TCO1_LTC_Format_MSB		0x00000800

#घोषणा HDSPM_TCO2_TC_run			0x00010000
#घोषणा HDSPM_TCO2_WCK_IO_ratio_LSB		0x00020000
#घोषणा HDSPM_TCO2_WCK_IO_ratio_MSB		0x00040000
#घोषणा HDSPM_TCO2_set_num_drop_frames_LSB	0x00080000
#घोषणा HDSPM_TCO2_set_num_drop_frames_MSB	0x00100000
#घोषणा HDSPM_TCO2_set_jam_sync			0x00200000
#घोषणा HDSPM_TCO2_set_flywheel			0x00400000

#घोषणा HDSPM_TCO2_set_01_4			0x01000000
#घोषणा HDSPM_TCO2_set_pull_करोwn		0x02000000
#घोषणा HDSPM_TCO2_set_pull_up			0x04000000
#घोषणा HDSPM_TCO2_set_freq			0x08000000
#घोषणा HDSPM_TCO2_set_term_75R			0x10000000
#घोषणा HDSPM_TCO2_set_input_LSB		0x20000000
#घोषणा HDSPM_TCO2_set_input_MSB		0x40000000
#घोषणा HDSPM_TCO2_set_freq_from_app		0x80000000


#घोषणा HDSPM_midiDataOut0    352
#घोषणा HDSPM_midiDataOut1    356
#घोषणा HDSPM_midiDataOut2    368

#घोषणा HDSPM_midiDataIn0     360
#घोषणा HDSPM_midiDataIn1     364
#घोषणा HDSPM_midiDataIn2     372
#घोषणा HDSPM_midiDataIn3     376

/* status is data bytes in MIDI-FIFO (0-128) */
#घोषणा HDSPM_midiStatusOut0  384
#घोषणा HDSPM_midiStatusOut1  388
#घोषणा HDSPM_midiStatusOut2  400

#घोषणा HDSPM_midiStatusIn0   392
#घोषणा HDSPM_midiStatusIn1   396
#घोषणा HDSPM_midiStatusIn2   404
#घोषणा HDSPM_midiStatusIn3   408


/* the meters are regular i/o-mapped रेजिस्टरs, but offset
   considerably from the rest. the peak रेजिस्टरs are reset
   when पढ़ो; the least-signअगरicant 4 bits are full-scale counters;
   the actual peak value is in the most-signअगरicant 24 bits.
*/

#घोषणा HDSPM_MADI_INPUT_PEAK		4096
#घोषणा HDSPM_MADI_PLAYBACK_PEAK	4352
#घोषणा HDSPM_MADI_OUTPUT_PEAK		4608

#घोषणा HDSPM_MADI_INPUT_RMS_L		6144
#घोषणा HDSPM_MADI_PLAYBACK_RMS_L	6400
#घोषणा HDSPM_MADI_OUTPUT_RMS_L		6656

#घोषणा HDSPM_MADI_INPUT_RMS_H		7168
#घोषणा HDSPM_MADI_PLAYBACK_RMS_H	7424
#घोषणा HDSPM_MADI_OUTPUT_RMS_H		7680

/* --- Control Register bits --------- */
#घोषणा HDSPM_Start                (1<<0) /* start engine */

#घोषणा HDSPM_Latency0             (1<<1) /* buffer size = 2^n */
#घोषणा HDSPM_Latency1             (1<<2) /* where n is defined */
#घोषणा HDSPM_Latency2             (1<<3) /* by Latencyअणु2,1,0पूर्ण */

#घोषणा HDSPM_ClockModeMaster      (1<<4) /* 1=Master, 0=Autosync */
#घोषणा HDSPM_c0Master		0x1    /* Master घड़ी bit in settings
					  रेजिस्टर [RayDAT, AIO] */

#घोषणा HDSPM_AudioInterruptEnable (1<<5) /* what करो you think ? */

#घोषणा HDSPM_Frequency0  (1<<6)  /* 0=44.1kHz/88.2kHz 1=48kHz/96kHz */
#घोषणा HDSPM_Frequency1  (1<<7)  /* 0=32kHz/64kHz */
#घोषणा HDSPM_DoubleSpeed (1<<8)  /* 0=normal speed, 1=द्विगुन speed */
#घोषणा HDSPM_QuadSpeed   (1<<31) /* quad speed bit */

#घोषणा HDSPM_Professional (1<<9) /* Professional */ /* AES32 ONLY */
#घोषणा HDSPM_TX_64ch     (1<<10) /* Output 64channel MODE=1,
				     56channelMODE=0 */ /* MADI ONLY*/
#घोषणा HDSPM_Emphasis    (1<<10) /* Emphasis */ /* AES32 ONLY */

#घोषणा HDSPM_AutoInp     (1<<11) /* Auto Input (takeover) == Safe Mode,
                                     0=off, 1=on  */ /* MADI ONLY */
#घोषणा HDSPM_Dolby       (1<<11) /* Dolby = "NonAudio" ?? */ /* AES32 ONLY */

#घोषणा HDSPM_InputSelect0 (1<<14) /* Input select 0= optical, 1=coax
				    * -- MADI ONLY
				    */
#घोषणा HDSPM_InputSelect1 (1<<15) /* should be 0 */

#घोषणा HDSPM_SyncRef2     (1<<13)
#घोषणा HDSPM_SyncRef3     (1<<25)

#घोषणा HDSPM_SMUX         (1<<18) /* Frame ??? */ /* MADI ONY */
#घोषणा HDSPM_clr_पंचांगs      (1<<19) /* clear track marker, करो not use
                                      AES additional bits in
				      lower 5 Audiodatabits ??? */
#घोषणा HDSPM_taxi_reset   (1<<20) /* ??? */ /* MADI ONLY ? */
#घोषणा HDSPM_WCK48        (1<<20) /* Frame ??? = HDSPM_SMUX */ /* AES32 ONLY */

#घोषणा HDSPM_Midi0InterruptEnable 0x0400000
#घोषणा HDSPM_Midi1InterruptEnable 0x0800000
#घोषणा HDSPM_Midi2InterruptEnable 0x0200000
#घोषणा HDSPM_Midi3InterruptEnable 0x4000000

#घोषणा HDSPM_LineOut (1<<24) /* Analog Out on channel 63/64 on=1, mute=0 */
#घोषणा HDSPe_FLOAT_FORMAT         0x2000000

#घोषणा HDSPM_DS_DoubleWire (1<<26) /* AES32 ONLY */
#घोषणा HDSPM_QS_DoubleWire (1<<27) /* AES32 ONLY */
#घोषणा HDSPM_QS_QuadWire   (1<<28) /* AES32 ONLY */

#घोषणा HDSPM_wclk_sel (1<<30)

/* additional control रेजिस्टर bits क्रम AIO*/
#घोषणा HDSPM_c0_Wck48				0x20 /* also RayDAT */
#घोषणा HDSPM_c0_Input0				0x1000
#घोषणा HDSPM_c0_Input1				0x2000
#घोषणा HDSPM_c0_Spdअगर_Opt			0x4000
#घोषणा HDSPM_c0_Pro				0x8000
#घोषणा HDSPM_c0_clr_पंचांगs			0x10000
#घोषणा HDSPM_c0_AEB1				0x20000
#घोषणा HDSPM_c0_AEB2				0x40000
#घोषणा HDSPM_c0_LineOut			0x80000
#घोषणा HDSPM_c0_AD_GAIN0			0x100000
#घोषणा HDSPM_c0_AD_GAIN1			0x200000
#घोषणा HDSPM_c0_DA_GAIN0			0x400000
#घोषणा HDSPM_c0_DA_GAIN1			0x800000
#घोषणा HDSPM_c0_PH_GAIN0			0x1000000
#घोषणा HDSPM_c0_PH_GAIN1			0x2000000
#घोषणा HDSPM_c0_Sym6db				0x4000000


/* --- bit helper defines */
#घोषणा HDSPM_LatencyMask    (HDSPM_Latency0|HDSPM_Latency1|HDSPM_Latency2)
#घोषणा HDSPM_FrequencyMask  (HDSPM_Frequency0|HDSPM_Frequency1|\
			      HDSPM_DoubleSpeed|HDSPM_QuadSpeed)
#घोषणा HDSPM_InputMask      (HDSPM_InputSelect0|HDSPM_InputSelect1)
#घोषणा HDSPM_InputOptical   0
#घोषणा HDSPM_InputCoaxial   (HDSPM_InputSelect0)
#घोषणा HDSPM_SyncRefMask    (HDSPM_SyncRef0|HDSPM_SyncRef1|\
			      HDSPM_SyncRef2|HDSPM_SyncRef3)

#घोषणा HDSPM_c0_SyncRef0      0x2
#घोषणा HDSPM_c0_SyncRef1      0x4
#घोषणा HDSPM_c0_SyncRef2      0x8
#घोषणा HDSPM_c0_SyncRef3      0x10
#घोषणा HDSPM_c0_SyncRefMask   (HDSPM_c0_SyncRef0 | HDSPM_c0_SyncRef1 |\
				HDSPM_c0_SyncRef2 | HDSPM_c0_SyncRef3)

#घोषणा HDSPM_SYNC_FROM_WORD    0	/* Preferred sync reference */
#घोषणा HDSPM_SYNC_FROM_MADI    1	/* choices - used by "pref_sync_ref" */
#घोषणा HDSPM_SYNC_FROM_TCO     2
#घोषणा HDSPM_SYNC_FROM_SYNC_IN 3

#घोषणा HDSPM_Frequency32KHz    HDSPM_Frequency0
#घोषणा HDSPM_Frequency44_1KHz  HDSPM_Frequency1
#घोषणा HDSPM_Frequency48KHz   (HDSPM_Frequency1|HDSPM_Frequency0)
#घोषणा HDSPM_Frequency64KHz   (HDSPM_DoubleSpeed|HDSPM_Frequency0)
#घोषणा HDSPM_Frequency88_2KHz (HDSPM_DoubleSpeed|HDSPM_Frequency1)
#घोषणा HDSPM_Frequency96KHz   (HDSPM_DoubleSpeed|HDSPM_Frequency1|\
				HDSPM_Frequency0)
#घोषणा HDSPM_Frequency128KHz   (HDSPM_QuadSpeed|HDSPM_Frequency0)
#घोषणा HDSPM_Frequency176_4KHz   (HDSPM_QuadSpeed|HDSPM_Frequency1)
#घोषणा HDSPM_Frequency192KHz   (HDSPM_QuadSpeed|HDSPM_Frequency1|\
				 HDSPM_Frequency0)


/* Synccheck Status */
#घोषणा HDSPM_SYNC_CHECK_NO_LOCK 0
#घोषणा HDSPM_SYNC_CHECK_LOCK    1
#घोषणा HDSPM_SYNC_CHECK_SYNC	 2

/* AutoSync References - used by "autosync_ref" control चयन */
#घोषणा HDSPM_AUTOSYNC_FROM_WORD      0
#घोषणा HDSPM_AUTOSYNC_FROM_MADI      1
#घोषणा HDSPM_AUTOSYNC_FROM_TCO       2
#घोषणा HDSPM_AUTOSYNC_FROM_SYNC_IN   3
#घोषणा HDSPM_AUTOSYNC_FROM_NONE      4

/* Possible sources of MADI input */
#घोषणा HDSPM_OPTICAL 0		/* optical   */
#घोषणा HDSPM_COAXIAL 1		/* BNC */

#घोषणा hdspm_encode_latency(x)       (((x)<<1) & HDSPM_LatencyMask)
#घोषणा hdspm_decode_latency(x)       ((((x) & HDSPM_LatencyMask)>>1))

#घोषणा hdspm_encode_in(x) (((x)&0x3)<<14)
#घोषणा hdspm_decode_in(x) (((x)>>14)&0x3)

/* --- control2 रेजिस्टर bits --- */
#घोषणा HDSPM_TMS             (1<<0)
#घोषणा HDSPM_TCK             (1<<1)
#घोषणा HDSPM_TDI             (1<<2)
#घोषणा HDSPM_JTAG            (1<<3)
#घोषणा HDSPM_PWDN            (1<<4)
#घोषणा HDSPM_PROGRAM	      (1<<5)
#घोषणा HDSPM_CONFIG_MODE_0   (1<<6)
#घोषणा HDSPM_CONFIG_MODE_1   (1<<7)
/*#घोषणा HDSPM_VERSION_BIT     (1<<8) not defined any more*/
#घोषणा HDSPM_BIGENDIAN_MODE  (1<<9)
#घोषणा HDSPM_RD_MULTIPLE     (1<<10)

/* --- Status Register bits --- */ /* MADI ONLY */ /* Bits defined here and
     that करो not conflict with specअगरic bits क्रम AES32 seem to be valid also
     क्रम the AES32
 */
#घोषणा HDSPM_audioIRQPending    (1<<0)	/* IRQ is high and pending */
#घोषणा HDSPM_RX_64ch            (1<<1)	/* Input 64chan. MODE=1, 56chn MODE=0 */
#घोषणा HDSPM_AB_पूर्णांक             (1<<2)	/* InputChannel Opt=0, Coax=1
					 * (like inp0)
					 */

#घोषणा HDSPM_madiLock           (1<<3)	/* MADI Locked =1, no=0 */
#घोषणा HDSPM_madiSync          (1<<18) /* MADI is in sync */

#घोषणा HDSPM_tcoLockMadi    0x00000020 /* Optional TCO locked status क्रम HDSPe MADI*/
#घोषणा HDSPM_tcoSync    0x10000000 /* Optional TCO sync status क्रम HDSPe MADI and AES32!*/

#घोषणा HDSPM_syncInLock 0x00010000 /* Sync In lock status क्रम HDSPe MADI! */
#घोषणा HDSPM_syncInSync 0x00020000 /* Sync In sync status क्रम HDSPe MADI! */

#घोषणा HDSPM_BufferPositionMask 0x000FFC0 /* Bit 6..15 : h/w buffer poपूर्णांकer */
			/* since 64byte accurate, last 6 bits are not used */



#घोषणा HDSPM_DoubleSpeedStatus (1<<19) /* (input) card in द्विगुन speed */

#घोषणा HDSPM_madiFreq0         (1<<22)	/* प्रणाली freq 0=error */
#घोषणा HDSPM_madiFreq1         (1<<23)	/* 1=32, 2=44.1 3=48 */
#घोषणा HDSPM_madiFreq2         (1<<24)	/* 4=64, 5=88.2 6=96 */
#घोषणा HDSPM_madiFreq3         (1<<25)	/* 7=128, 8=176.4 9=192 */

#घोषणा HDSPM_BufferID          (1<<26)	/* (Double)Buffer ID toggles with
					 * Interrupt
					 */
#घोषणा HDSPM_tco_detect         0x08000000
#घोषणा HDSPM_tcoLockAes         0x20000000 /* Optional TCO locked status क्रम HDSPe AES */

#घोषणा HDSPM_s2_tco_detect      0x00000040
#घोषणा HDSPM_s2_AEBO_D          0x00000080
#घोषणा HDSPM_s2_AEBI_D          0x00000100


#घोषणा HDSPM_midi0IRQPending    0x40000000
#घोषणा HDSPM_midi1IRQPending    0x80000000
#घोषणा HDSPM_midi2IRQPending    0x20000000
#घोषणा HDSPM_midi2IRQPendingAES 0x00000020
#घोषणा HDSPM_midi3IRQPending    0x00200000

/* --- status bit helpers */
#घोषणा HDSPM_madiFreqMask  (HDSPM_madiFreq0|HDSPM_madiFreq1|\
			     HDSPM_madiFreq2|HDSPM_madiFreq3)
#घोषणा HDSPM_madiFreq32    (HDSPM_madiFreq0)
#घोषणा HDSPM_madiFreq44_1  (HDSPM_madiFreq1)
#घोषणा HDSPM_madiFreq48    (HDSPM_madiFreq0|HDSPM_madiFreq1)
#घोषणा HDSPM_madiFreq64    (HDSPM_madiFreq2)
#घोषणा HDSPM_madiFreq88_2  (HDSPM_madiFreq0|HDSPM_madiFreq2)
#घोषणा HDSPM_madiFreq96    (HDSPM_madiFreq1|HDSPM_madiFreq2)
#घोषणा HDSPM_madiFreq128   (HDSPM_madiFreq0|HDSPM_madiFreq1|HDSPM_madiFreq2)
#घोषणा HDSPM_madiFreq176_4 (HDSPM_madiFreq3)
#घोषणा HDSPM_madiFreq192   (HDSPM_madiFreq3|HDSPM_madiFreq0)

/* Status2 Register bits */ /* MADI ONLY */

#घोषणा HDSPM_version0 (1<<0)	/* not really defined but I guess */
#घोषणा HDSPM_version1 (1<<1)	/* in क्रमmer cards it was ??? */
#घोषणा HDSPM_version2 (1<<2)

#घोषणा HDSPM_wcLock (1<<3)	/* Wordघड़ी is detected and locked */
#घोषणा HDSPM_wcSync (1<<4)	/* Wordघड़ी is in sync with प्रणालीघड़ी */

#घोषणा HDSPM_wc_freq0 (1<<5)	/* input freq detected via स्वतःsync  */
#घोषणा HDSPM_wc_freq1 (1<<6)	/* 001=32, 010==44.1, 011=48, */
#घोषणा HDSPM_wc_freq2 (1<<7)	/* 100=64, 101=88.2, 110=96, 111=128 */
#घोषणा HDSPM_wc_freq3 0x800	/* 1000=176.4, 1001=192 */

#घोषणा HDSPM_SyncRef0 0x10000  /* Sync Reference */
#घोषणा HDSPM_SyncRef1 0x20000

#घोषणा HDSPM_SelSyncRef0 (1<<8)	/* AutoSync Source */
#घोषणा HDSPM_SelSyncRef1 (1<<9)	/* 000=word, 001=MADI, */
#घोषणा HDSPM_SelSyncRef2 (1<<10)	/* 111=no valid संकेत */

#घोषणा HDSPM_wc_valid (HDSPM_wcLock|HDSPM_wcSync)

#घोषणा HDSPM_wcFreqMask  (HDSPM_wc_freq0|HDSPM_wc_freq1|HDSPM_wc_freq2|\
			    HDSPM_wc_freq3)
#घोषणा HDSPM_wcFreq32    (HDSPM_wc_freq0)
#घोषणा HDSPM_wcFreq44_1  (HDSPM_wc_freq1)
#घोषणा HDSPM_wcFreq48    (HDSPM_wc_freq0|HDSPM_wc_freq1)
#घोषणा HDSPM_wcFreq64    (HDSPM_wc_freq2)
#घोषणा HDSPM_wcFreq88_2  (HDSPM_wc_freq0|HDSPM_wc_freq2)
#घोषणा HDSPM_wcFreq96    (HDSPM_wc_freq1|HDSPM_wc_freq2)
#घोषणा HDSPM_wcFreq128   (HDSPM_wc_freq0|HDSPM_wc_freq1|HDSPM_wc_freq2)
#घोषणा HDSPM_wcFreq176_4 (HDSPM_wc_freq3)
#घोषणा HDSPM_wcFreq192   (HDSPM_wc_freq0|HDSPM_wc_freq3)

#घोषणा HDSPM_status1_F_0 0x0400000
#घोषणा HDSPM_status1_F_1 0x0800000
#घोषणा HDSPM_status1_F_2 0x1000000
#घोषणा HDSPM_status1_F_3 0x2000000
#घोषणा HDSPM_status1_freqMask (HDSPM_status1_F_0|HDSPM_status1_F_1|HDSPM_status1_F_2|HDSPM_status1_F_3)


#घोषणा HDSPM_SelSyncRefMask       (HDSPM_SelSyncRef0|HDSPM_SelSyncRef1|\
				    HDSPM_SelSyncRef2)
#घोषणा HDSPM_SelSyncRef_WORD      0
#घोषणा HDSPM_SelSyncRef_MADI      (HDSPM_SelSyncRef0)
#घोषणा HDSPM_SelSyncRef_TCO       (HDSPM_SelSyncRef1)
#घोषणा HDSPM_SelSyncRef_SyncIn    (HDSPM_SelSyncRef0|HDSPM_SelSyncRef1)
#घोषणा HDSPM_SelSyncRef_NVALID    (HDSPM_SelSyncRef0|HDSPM_SelSyncRef1|\
				    HDSPM_SelSyncRef2)

/*
   For AES32, bits क्रम status, status2 and समयcode are dअगरferent
*/
/* status */
#घोषणा HDSPM_AES32_wcLock	0x0200000
#घोषणा HDSPM_AES32_wcSync	0x0100000
#घोषणा HDSPM_AES32_wcFreq_bit  22
/* (status >> HDSPM_AES32_wcFreq_bit) & 0xF gives WC frequency (cf function
  HDSPM_bit2freq */
#घोषणा HDSPM_AES32_syncref_bit  16
/* (status >> HDSPM_AES32_syncref_bit) & 0xF gives sync source */

#घोषणा HDSPM_AES32_AUTOSYNC_FROM_WORD 0
#घोषणा HDSPM_AES32_AUTOSYNC_FROM_AES1 1
#घोषणा HDSPM_AES32_AUTOSYNC_FROM_AES2 2
#घोषणा HDSPM_AES32_AUTOSYNC_FROM_AES3 3
#घोषणा HDSPM_AES32_AUTOSYNC_FROM_AES4 4
#घोषणा HDSPM_AES32_AUTOSYNC_FROM_AES5 5
#घोषणा HDSPM_AES32_AUTOSYNC_FROM_AES6 6
#घोषणा HDSPM_AES32_AUTOSYNC_FROM_AES7 7
#घोषणा HDSPM_AES32_AUTOSYNC_FROM_AES8 8
#घोषणा HDSPM_AES32_AUTOSYNC_FROM_TCO 9
#घोषणा HDSPM_AES32_AUTOSYNC_FROM_SYNC_IN 10
#घोषणा HDSPM_AES32_AUTOSYNC_FROM_NONE 11

/*  status2 */
/* HDSPM_LockAES_bit is given by HDSPM_LockAES >> (AES# - 1) */
#घोषणा HDSPM_LockAES   0x80
#घोषणा HDSPM_LockAES1  0x80
#घोषणा HDSPM_LockAES2  0x40
#घोषणा HDSPM_LockAES3  0x20
#घोषणा HDSPM_LockAES4  0x10
#घोषणा HDSPM_LockAES5  0x8
#घोषणा HDSPM_LockAES6  0x4
#घोषणा HDSPM_LockAES7  0x2
#घोषणा HDSPM_LockAES8  0x1
/*
   Timecode
   After winकरोws driver sources, bits 4*i to 4*i+3 give the input frequency on
   AES i+1
 bits 3210
      0001  32kHz
      0010  44.1kHz
      0011  48kHz
      0100  64kHz
      0101  88.2kHz
      0110  96kHz
      0111  128kHz
      1000  176.4kHz
      1001  192kHz
  NB: Timecode रेजिस्टर करोesn't seem to work on AES32 card revision 230
*/

/* Mixer Values */
#घोषणा UNITY_GAIN          32768	/* = 65536/2 */
#घोषणा MINUS_अनन्त_GAIN 0

/* Number of channels क्रम dअगरferent Speed Modes */
#घोषणा MADI_SS_CHANNELS       64
#घोषणा MADI_DS_CHANNELS       32
#घोषणा MADI_QS_CHANNELS       16

#घोषणा RAYDAT_SS_CHANNELS     36
#घोषणा RAYDAT_DS_CHANNELS     20
#घोषणा RAYDAT_QS_CHANNELS     12

#घोषणा AIO_IN_SS_CHANNELS        14
#घोषणा AIO_IN_DS_CHANNELS        10
#घोषणा AIO_IN_QS_CHANNELS        8
#घोषणा AIO_OUT_SS_CHANNELS        16
#घोषणा AIO_OUT_DS_CHANNELS        12
#घोषणा AIO_OUT_QS_CHANNELS        10

#घोषणा AES32_CHANNELS		16

/* the size of a substream (1 mono data stream) */
#घोषणा HDSPM_CHANNEL_BUFFER_SAMPLES  (16*1024)
#घोषणा HDSPM_CHANNEL_BUFFER_BYTES    (4*HDSPM_CHANNEL_BUFFER_SAMPLES)

/* the size of the area we need to allocate क्रम DMA transfers. the
   size is the same regardless of the number of channels, and
   also the latency to use.
   क्रम one direction !!!
*/
#घोषणा HDSPM_DMA_AREA_BYTES (HDSPM_MAX_CHANNELS * HDSPM_CHANNEL_BUFFER_BYTES)
#घोषणा HDSPM_DMA_AREA_KILOBYTES (HDSPM_DMA_AREA_BYTES/1024)

#घोषणा HDSPM_RAYDAT_REV	211
#घोषणा HDSPM_AIO_REV		212
#घोषणा HDSPM_MADIFACE_REV	213

/* speed factor modes */
#घोषणा HDSPM_SPEED_SINGLE 0
#घोषणा HDSPM_SPEED_DOUBLE 1
#घोषणा HDSPM_SPEED_QUAD   2

/* names क्रम speed modes */
अटल स्थिर अक्षर * स्थिर hdspm_speed_names[] = अणु "single", "double", "quad" पूर्ण;

अटल स्थिर अक्षर *स्थिर texts_स्वतःsync_aes_tco[] = अणु "Word Clock",
					  "AES1", "AES2", "AES3", "AES4",
					  "AES5", "AES6", "AES7", "AES8",
					  "TCO", "Sync In"
पूर्ण;
अटल स्थिर अक्षर *स्थिर texts_स्वतःsync_aes[] = अणु "Word Clock",
				      "AES1", "AES2", "AES3", "AES4",
				      "AES5", "AES6", "AES7", "AES8",
				      "Sync In"
पूर्ण;
अटल स्थिर अक्षर *स्थिर texts_स्वतःsync_madi_tco[] = अणु "Word Clock",
					   "MADI", "TCO", "Sync In" पूर्ण;
अटल स्थिर अक्षर *स्थिर texts_स्वतःsync_madi[] = अणु "Word Clock",
				       "MADI", "Sync In" पूर्ण;

अटल स्थिर अक्षर *स्थिर texts_स्वतःsync_raydat_tco[] = अणु
	"Word Clock",
	"ADAT 1", "ADAT 2", "ADAT 3", "ADAT 4",
	"AES", "SPDIF", "TCO", "Sync In"
पूर्ण;
अटल स्थिर अक्षर *स्थिर texts_स्वतःsync_raydat[] = अणु
	"Word Clock",
	"ADAT 1", "ADAT 2", "ADAT 3", "ADAT 4",
	"AES", "SPDIF", "Sync In"
पूर्ण;
अटल स्थिर अक्षर *स्थिर texts_स्वतःsync_aio_tco[] = अणु
	"Word Clock",
	"ADAT", "AES", "SPDIF", "TCO", "Sync In"
पूर्ण;
अटल स्थिर अक्षर *स्थिर texts_स्वतःsync_aio[] = अणु "Word Clock",
				      "ADAT", "AES", "SPDIF", "Sync In" पूर्ण;

अटल स्थिर अक्षर *स्थिर texts_freq[] = अणु
	"No Lock",
	"32 kHz",
	"44.1 kHz",
	"48 kHz",
	"64 kHz",
	"88.2 kHz",
	"96 kHz",
	"128 kHz",
	"176.4 kHz",
	"192 kHz"
पूर्ण;

अटल स्थिर अक्षर * स्थिर texts_ports_madi[] = अणु
	"MADI.1", "MADI.2", "MADI.3", "MADI.4", "MADI.5", "MADI.6",
	"MADI.7", "MADI.8", "MADI.9", "MADI.10", "MADI.11", "MADI.12",
	"MADI.13", "MADI.14", "MADI.15", "MADI.16", "MADI.17", "MADI.18",
	"MADI.19", "MADI.20", "MADI.21", "MADI.22", "MADI.23", "MADI.24",
	"MADI.25", "MADI.26", "MADI.27", "MADI.28", "MADI.29", "MADI.30",
	"MADI.31", "MADI.32", "MADI.33", "MADI.34", "MADI.35", "MADI.36",
	"MADI.37", "MADI.38", "MADI.39", "MADI.40", "MADI.41", "MADI.42",
	"MADI.43", "MADI.44", "MADI.45", "MADI.46", "MADI.47", "MADI.48",
	"MADI.49", "MADI.50", "MADI.51", "MADI.52", "MADI.53", "MADI.54",
	"MADI.55", "MADI.56", "MADI.57", "MADI.58", "MADI.59", "MADI.60",
	"MADI.61", "MADI.62", "MADI.63", "MADI.64",
पूर्ण;


अटल स्थिर अक्षर * स्थिर texts_ports_raydat_ss[] = अणु
	"ADAT1.1", "ADAT1.2", "ADAT1.3", "ADAT1.4", "ADAT1.5", "ADAT1.6",
	"ADAT1.7", "ADAT1.8", "ADAT2.1", "ADAT2.2", "ADAT2.3", "ADAT2.4",
	"ADAT2.5", "ADAT2.6", "ADAT2.7", "ADAT2.8", "ADAT3.1", "ADAT3.2",
	"ADAT3.3", "ADAT3.4", "ADAT3.5", "ADAT3.6", "ADAT3.7", "ADAT3.8",
	"ADAT4.1", "ADAT4.2", "ADAT4.3", "ADAT4.4", "ADAT4.5", "ADAT4.6",
	"ADAT4.7", "ADAT4.8",
	"AES.L", "AES.R",
	"SPDIF.L", "SPDIF.R"
पूर्ण;

अटल स्थिर अक्षर * स्थिर texts_ports_raydat_ds[] = अणु
	"ADAT1.1", "ADAT1.2", "ADAT1.3", "ADAT1.4",
	"ADAT2.1", "ADAT2.2", "ADAT2.3", "ADAT2.4",
	"ADAT3.1", "ADAT3.2", "ADAT3.3", "ADAT3.4",
	"ADAT4.1", "ADAT4.2", "ADAT4.3", "ADAT4.4",
	"AES.L", "AES.R",
	"SPDIF.L", "SPDIF.R"
पूर्ण;

अटल स्थिर अक्षर * स्थिर texts_ports_raydat_qs[] = अणु
	"ADAT1.1", "ADAT1.2",
	"ADAT2.1", "ADAT2.2",
	"ADAT3.1", "ADAT3.2",
	"ADAT4.1", "ADAT4.2",
	"AES.L", "AES.R",
	"SPDIF.L", "SPDIF.R"
पूर्ण;


अटल स्थिर अक्षर * स्थिर texts_ports_aio_in_ss[] = अणु
	"Analogue.L", "Analogue.R",
	"AES.L", "AES.R",
	"SPDIF.L", "SPDIF.R",
	"ADAT.1", "ADAT.2", "ADAT.3", "ADAT.4", "ADAT.5", "ADAT.6",
	"ADAT.7", "ADAT.8",
	"AEB.1", "AEB.2", "AEB.3", "AEB.4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर texts_ports_aio_out_ss[] = अणु
	"Analogue.L", "Analogue.R",
	"AES.L", "AES.R",
	"SPDIF.L", "SPDIF.R",
	"ADAT.1", "ADAT.2", "ADAT.3", "ADAT.4", "ADAT.5", "ADAT.6",
	"ADAT.7", "ADAT.8",
	"Phone.L", "Phone.R",
	"AEB.1", "AEB.2", "AEB.3", "AEB.4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर texts_ports_aio_in_ds[] = अणु
	"Analogue.L", "Analogue.R",
	"AES.L", "AES.R",
	"SPDIF.L", "SPDIF.R",
	"ADAT.1", "ADAT.2", "ADAT.3", "ADAT.4",
	"AEB.1", "AEB.2", "AEB.3", "AEB.4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर texts_ports_aio_out_ds[] = अणु
	"Analogue.L", "Analogue.R",
	"AES.L", "AES.R",
	"SPDIF.L", "SPDIF.R",
	"ADAT.1", "ADAT.2", "ADAT.3", "ADAT.4",
	"Phone.L", "Phone.R",
	"AEB.1", "AEB.2", "AEB.3", "AEB.4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर texts_ports_aio_in_qs[] = अणु
	"Analogue.L", "Analogue.R",
	"AES.L", "AES.R",
	"SPDIF.L", "SPDIF.R",
	"ADAT.1", "ADAT.2", "ADAT.3", "ADAT.4",
	"AEB.1", "AEB.2", "AEB.3", "AEB.4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर texts_ports_aio_out_qs[] = अणु
	"Analogue.L", "Analogue.R",
	"AES.L", "AES.R",
	"SPDIF.L", "SPDIF.R",
	"ADAT.1", "ADAT.2", "ADAT.3", "ADAT.4",
	"Phone.L", "Phone.R",
	"AEB.1", "AEB.2", "AEB.3", "AEB.4"
पूर्ण;

अटल स्थिर अक्षर * स्थिर texts_ports_aes32[] = अणु
	"AES.1", "AES.2", "AES.3", "AES.4", "AES.5", "AES.6", "AES.7",
	"AES.8", "AES.9.", "AES.10", "AES.11", "AES.12", "AES.13", "AES.14",
	"AES.15", "AES.16"
पूर्ण;

/* These tables map the ALSA channels 1..N to the channels that we
   need to use in order to find the relevant channel buffer. RME
   refers to this kind of mapping as between "the ADAT channel and
   the DMA channel." We index it using the logical audio channel,
   and the value is the DMA channel (i.e. channel buffer number)
   where the data क्रम that channel can be पढ़ो/written from/to.
*/

अटल स्थिर अक्षर channel_map_unity_ss[HDSPM_MAX_CHANNELS] = अणु
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 29, 30, 31,
	32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47,
	48, 49, 50, 51, 52, 53, 54, 55,
	56, 57, 58, 59, 60, 61, 62, 63
पूर्ण;

अटल स्थिर अक्षर channel_map_raydat_ss[HDSPM_MAX_CHANNELS] = अणु
	4, 5, 6, 7, 8, 9, 10, 11,	/* ADAT 1 */
	12, 13, 14, 15, 16, 17, 18, 19,	/* ADAT 2 */
	20, 21, 22, 23, 24, 25, 26, 27,	/* ADAT 3 */
	28, 29, 30, 31, 32, 33, 34, 35,	/* ADAT 4 */
	0, 1,			/* AES */
	2, 3,			/* SPDIF */
	-1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
पूर्ण;

अटल स्थिर अक्षर channel_map_raydat_ds[HDSPM_MAX_CHANNELS] = अणु
	4, 5, 6, 7,		/* ADAT 1 */
	8, 9, 10, 11,		/* ADAT 2 */
	12, 13, 14, 15,		/* ADAT 3 */
	16, 17, 18, 19,		/* ADAT 4 */
	0, 1,			/* AES */
	2, 3,			/* SPDIF */
	-1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
पूर्ण;

अटल स्थिर अक्षर channel_map_raydat_qs[HDSPM_MAX_CHANNELS] = अणु
	4, 5,			/* ADAT 1 */
	6, 7,			/* ADAT 2 */
	8, 9,			/* ADAT 3 */
	10, 11,			/* ADAT 4 */
	0, 1,			/* AES */
	2, 3,			/* SPDIF */
	-1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
पूर्ण;

अटल स्थिर अक्षर channel_map_aio_in_ss[HDSPM_MAX_CHANNELS] = अणु
	0, 1,			/* line in */
	8, 9,			/* aes in, */
	10, 11,			/* spdअगर in */
	12, 13, 14, 15, 16, 17, 18, 19,	/* ADAT in */
	2, 3, 4, 5,		/* AEB */
	-1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
पूर्ण;

अटल स्थिर अक्षर channel_map_aio_out_ss[HDSPM_MAX_CHANNELS] = अणु
	0, 1,			/* line out */
	8, 9,			/* aes out */
	10, 11,			/* spdअगर out */
	12, 13, 14, 15, 16, 17, 18, 19,	/* ADAT out */
	6, 7,			/* phone out */
	2, 3, 4, 5,		/* AEB */
	-1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
पूर्ण;

अटल स्थिर अक्षर channel_map_aio_in_ds[HDSPM_MAX_CHANNELS] = अणु
	0, 1,			/* line in */
	8, 9,			/* aes in */
	10, 11,			/* spdअगर in */
	12, 14, 16, 18,		/* adat in */
	2, 3, 4, 5,		/* AEB */
	-1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1
पूर्ण;

अटल स्थिर अक्षर channel_map_aio_out_ds[HDSPM_MAX_CHANNELS] = अणु
	0, 1,			/* line out */
	8, 9,			/* aes out */
	10, 11,			/* spdअगर out */
	12, 14, 16, 18,		/* adat out */
	6, 7,			/* phone out */
	2, 3, 4, 5,		/* AEB */
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1
पूर्ण;

अटल स्थिर अक्षर channel_map_aio_in_qs[HDSPM_MAX_CHANNELS] = अणु
	0, 1,			/* line in */
	8, 9,			/* aes in */
	10, 11,			/* spdअगर in */
	12, 16,			/* adat in */
	2, 3, 4, 5,		/* AEB */
	-1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1
पूर्ण;

अटल स्थिर अक्षर channel_map_aio_out_qs[HDSPM_MAX_CHANNELS] = अणु
	0, 1,			/* line out */
	8, 9,			/* aes out */
	10, 11,			/* spdअगर out */
	12, 16,			/* adat out */
	6, 7,			/* phone out */
	2, 3, 4, 5,		/* AEB */
	-1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1
पूर्ण;

अटल स्थिर अक्षर channel_map_aes32[HDSPM_MAX_CHANNELS] = अणु
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 9, 10, 11, 12, 13, 14, 15,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1
पूर्ण;

काष्ठा hdspm_midi अणु
	काष्ठा hdspm *hdspm;
	पूर्णांक id;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *input;
	काष्ठा snd_rawmidi_substream *output;
	अक्षर isसमयr;		/* समयr in use */
	काष्ठा समयr_list समयr;
	spinlock_t lock;
	पूर्णांक pending;
	पूर्णांक dataIn;
	पूर्णांक statusIn;
	पूर्णांक dataOut;
	पूर्णांक statusOut;
	पूर्णांक ie;
	पूर्णांक irq;
पूर्ण;

काष्ठा hdspm_tco अणु
	पूर्णांक input; /* 0: LTC, 1:Video, 2: WC*/
	पूर्णांक framerate; /* 0=24, 1=25, 2=29.97, 3=29.97d, 4=30, 5=30d */
	पूर्णांक wordघड़ी; /* 0=1:1, 1=44.1->48, 2=48->44.1 */
	पूर्णांक samplerate; /* 0=44.1, 1=48, 2= freq from app */
	पूर्णांक pull; /*   0=0, 1=+0.1%, 2=-0.1%, 3=+4%, 4=-4%*/
	पूर्णांक term; /* 0 = off, 1 = on */
पूर्ण;

काष्ठा hdspm अणु
        spinlock_t lock;
	/* only one playback and/or capture stream */
        काष्ठा snd_pcm_substream *capture_substream;
        काष्ठा snd_pcm_substream *playback_substream;

	अक्षर *card_name;	     /* क्रम procinfo */
	अचिन्हित लघु firmware_rev; /* करोnt know अगर relevant (yes अगर AES32)*/

	uपूर्णांक8_t io_type;

	पूर्णांक monitor_outs;	/* set up monitoring outs init flag */

	u32 control_रेजिस्टर;	/* cached value */
	u32 control2_रेजिस्टर;	/* cached value */
	u32 settings_रेजिस्टर;  /* cached value क्रम AIO / RayDat (sync reference, master/slave) */

	काष्ठा hdspm_midi midi[4];
	काष्ठा work_काष्ठा midi_work;

	माप_प्रकार period_bytes;
	अचिन्हित अक्षर ss_in_channels;
	अचिन्हित अक्षर ds_in_channels;
	अचिन्हित अक्षर qs_in_channels;
	अचिन्हित अक्षर ss_out_channels;
	अचिन्हित अक्षर ds_out_channels;
	अचिन्हित अक्षर qs_out_channels;

	अचिन्हित अक्षर max_channels_in;
	अचिन्हित अक्षर max_channels_out;

	स्थिर चिन्हित अक्षर *channel_map_in;
	स्थिर चिन्हित अक्षर *channel_map_out;

	स्थिर चिन्हित अक्षर *channel_map_in_ss, *channel_map_in_ds, *channel_map_in_qs;
	स्थिर चिन्हित अक्षर *channel_map_out_ss, *channel_map_out_ds, *channel_map_out_qs;

	स्थिर अक्षर * स्थिर *port_names_in;
	स्थिर अक्षर * स्थिर *port_names_out;

	स्थिर अक्षर * स्थिर *port_names_in_ss;
	स्थिर अक्षर * स्थिर *port_names_in_ds;
	स्थिर अक्षर * स्थिर *port_names_in_qs;
	स्थिर अक्षर * स्थिर *port_names_out_ss;
	स्थिर अक्षर * स्थिर *port_names_out_ds;
	स्थिर अक्षर * स्थिर *port_names_out_qs;

	अचिन्हित अक्षर *playback_buffer;	/* suitably aligned address */
	अचिन्हित अक्षर *capture_buffer;	/* suitably aligned address */

	pid_t capture_pid;	/* process id which uses capture */
	pid_t playback_pid;	/* process id which uses capture */
	पूर्णांक running;		/* running status */

	पूर्णांक last_बाह्यal_sample_rate;	/* samplerate mystic ... */
	पूर्णांक last_पूर्णांकernal_sample_rate;
	पूर्णांक प्रणाली_sample_rate;

	पूर्णांक dev;		/* Hardware vars... */
	पूर्णांक irq;
	अचिन्हित दीर्घ port;
	व्योम __iomem *iobase;

	पूर्णांक irq_count;		/* क्रम debug */
	पूर्णांक midiPorts;

	काष्ठा snd_card *card;	/* one card */
	काष्ठा snd_pcm *pcm;		/* has one pcm */
	काष्ठा snd_hwdep *hwdep;	/* and a hwdep क्रम additional ioctl */
	काष्ठा pci_dev *pci;	/* and an pci info */

	/* Mixer vars */
	/* fast alsa mixer */
	काष्ठा snd_kcontrol *playback_mixer_ctls[HDSPM_MAX_CHANNELS];
	/* but input to much, so not used */
	काष्ठा snd_kcontrol *input_mixer_ctls[HDSPM_MAX_CHANNELS];
	/* full mixer accessible over mixer ioctl or hwdep-device */
	काष्ठा hdspm_mixer *mixer;

	काष्ठा hdspm_tco *tco;  /* शून्य अगर no TCO detected */

	स्थिर अक्षर *स्थिर *texts_स्वतःsync;
	पूर्णांक texts_स्वतःsync_items;

	cycles_t last_पूर्णांकerrupt;

	अचिन्हित पूर्णांक serial;

	काष्ठा hdspm_peak_rms peak_rms;
पूर्ण;


अटल स्थिर काष्ठा pci_device_id snd_hdspm_ids[] = अणु
	अणु
	 .venकरोr = PCI_VENDOR_ID_XILINX,
	 .device = PCI_DEVICE_ID_XILINX_HAMMERFALL_DSP_MADI,
	 .subvenकरोr = PCI_ANY_ID,
	 .subdevice = PCI_ANY_ID,
	 .class = 0,
	 .class_mask = 0,
	 .driver_data = 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_hdspm_ids);

/* prototypes */
अटल पूर्णांक snd_hdspm_create_alsa_devices(काष्ठा snd_card *card,
					 काष्ठा hdspm *hdspm);
अटल पूर्णांक snd_hdspm_create_pcm(काष्ठा snd_card *card,
				काष्ठा hdspm *hdspm);

अटल अंतरभूत व्योम snd_hdspm_initialize_midi_flush(काष्ठा hdspm *hdspm);
अटल अंतरभूत पूर्णांक hdspm_get_pll_freq(काष्ठा hdspm *hdspm);
अटल पूर्णांक hdspm_update_simple_mixer_controls(काष्ठा hdspm *hdspm);
अटल पूर्णांक hdspm_स्वतःsync_ref(काष्ठा hdspm *hdspm);
अटल पूर्णांक hdspm_set_toggle_setting(काष्ठा hdspm *hdspm, u32 regmask, पूर्णांक out);
अटल पूर्णांक snd_hdspm_set_शेषs(काष्ठा hdspm *hdspm);
अटल पूर्णांक hdspm_प्रणाली_घड़ी_mode(काष्ठा hdspm *hdspm);
अटल व्योम hdspm_set_channel_dma_addr(काष्ठा hdspm *hdspm,
				       काष्ठा snd_pcm_substream *substream,
				       अचिन्हित पूर्णांक reg, पूर्णांक channels);

अटल पूर्णांक hdspm_aes_sync_check(काष्ठा hdspm *hdspm, पूर्णांक idx);
अटल पूर्णांक hdspm_wc_sync_check(काष्ठा hdspm *hdspm);
अटल पूर्णांक hdspm_tco_sync_check(काष्ठा hdspm *hdspm);
अटल पूर्णांक hdspm_sync_in_sync_check(काष्ठा hdspm *hdspm);

अटल पूर्णांक hdspm_get_aes_sample_rate(काष्ठा hdspm *hdspm, पूर्णांक index);
अटल पूर्णांक hdspm_get_tco_sample_rate(काष्ठा hdspm *hdspm);
अटल पूर्णांक hdspm_get_wc_sample_rate(काष्ठा hdspm *hdspm);



अटल अंतरभूत पूर्णांक HDSPM_bit2freq(पूर्णांक n)
अणु
	अटल स्थिर पूर्णांक bit2freq_tab[] = अणु
		0, 32000, 44100, 48000, 64000, 88200,
		96000, 128000, 176400, 192000 पूर्ण;
	अगर (n < 1 || n > 9)
		वापस 0;
	वापस bit2freq_tab[n];
पूर्ण

अटल bool hdspm_is_raydat_or_aio(काष्ठा hdspm *hdspm)
अणु
	वापस ((AIO == hdspm->io_type) || (RayDAT == hdspm->io_type));
पूर्ण


/* Write/पढ़ो to/from HDSPM with Adresses in Bytes
   not words but only 32Bit ग_लिखोs are allowed */

अटल अंतरभूत व्योम hdspm_ग_लिखो(काष्ठा hdspm * hdspm, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl(val, hdspm->iobase + reg);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hdspm_पढ़ो(काष्ठा hdspm * hdspm, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(hdspm->iobase + reg);
पूर्ण

/* क्रम each output channel (chan) I have an Input (in) and Playback (pb) Fader
   mixer is ग_लिखो only on hardware so we have to cache him क्रम पढ़ो
   each fader is a u32, but uses only the first 16 bit */

अटल अंतरभूत पूर्णांक hdspm_पढ़ो_in_gain(काष्ठा hdspm * hdspm, अचिन्हित पूर्णांक chan,
				     अचिन्हित पूर्णांक in)
अणु
	अगर (chan >= HDSPM_MIXER_CHANNELS || in >= HDSPM_MIXER_CHANNELS)
		वापस 0;

	वापस hdspm->mixer->ch[chan].in[in];
पूर्ण

अटल अंतरभूत पूर्णांक hdspm_पढ़ो_pb_gain(काष्ठा hdspm * hdspm, अचिन्हित पूर्णांक chan,
				     अचिन्हित पूर्णांक pb)
अणु
	अगर (chan >= HDSPM_MIXER_CHANNELS || pb >= HDSPM_MIXER_CHANNELS)
		वापस 0;
	वापस hdspm->mixer->ch[chan].pb[pb];
पूर्ण

अटल पूर्णांक hdspm_ग_लिखो_in_gain(काष्ठा hdspm *hdspm, अचिन्हित पूर्णांक chan,
				      अचिन्हित पूर्णांक in, अचिन्हित लघु data)
अणु
	अगर (chan >= HDSPM_MIXER_CHANNELS || in >= HDSPM_MIXER_CHANNELS)
		वापस -1;

	hdspm_ग_लिखो(hdspm,
		    HDSPM_MADI_mixerBase +
		    ((in + 128 * chan) * माप(u32)),
		    (hdspm->mixer->ch[chan].in[in] = data & 0xFFFF));
	वापस 0;
पूर्ण

अटल पूर्णांक hdspm_ग_लिखो_pb_gain(काष्ठा hdspm *hdspm, अचिन्हित पूर्णांक chan,
				      अचिन्हित पूर्णांक pb, अचिन्हित लघु data)
अणु
	अगर (chan >= HDSPM_MIXER_CHANNELS || pb >= HDSPM_MIXER_CHANNELS)
		वापस -1;

	hdspm_ग_लिखो(hdspm,
		    HDSPM_MADI_mixerBase +
		    ((64 + pb + 128 * chan) * माप(u32)),
		    (hdspm->mixer->ch[chan].pb[pb] = data & 0xFFFF));
	वापस 0;
पूर्ण


/* enable DMA क्रम specअगरic channels, now available क्रम DSP-MADI */
अटल अंतरभूत व्योम snd_hdspm_enable_in(काष्ठा hdspm * hdspm, पूर्णांक i, पूर्णांक v)
अणु
	hdspm_ग_लिखो(hdspm, HDSPM_inputEnableBase + (4 * i), v);
पूर्ण

अटल अंतरभूत व्योम snd_hdspm_enable_out(काष्ठा hdspm * hdspm, पूर्णांक i, पूर्णांक v)
अणु
	hdspm_ग_लिखो(hdspm, HDSPM_outputEnableBase + (4 * i), v);
पूर्ण

/* check अगर same process is writing and पढ़ोing */
अटल पूर्णांक snd_hdspm_use_is_exclusive(काष्ठा hdspm *hdspm)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 1;

	spin_lock_irqsave(&hdspm->lock, flags);
	अगर ((hdspm->playback_pid != hdspm->capture_pid) &&
	    (hdspm->playback_pid >= 0) && (hdspm->capture_pid >= 0)) अणु
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&hdspm->lock, flags);
	वापस ret;
पूर्ण

/* round arbitrary sample rates to commonly known rates */
अटल पूर्णांक hdspm_round_frequency(पूर्णांक rate)
अणु
	अगर (rate < 38050)
		वापस 32000;
	अगर (rate < 46008)
		वापस 44100;
	अन्यथा
		वापस 48000;
पूर्ण

/* QS and DS rates normally can not be detected
 * स्वतःmatically by the card. Only exception is MADI
 * in 96k frame mode.
 *
 * So अगर we पढ़ो SS values (32 .. 48k), check क्रम
 * user-provided DS/QS bits in the control रेजिस्टर
 * and multiply the base frequency accordingly.
 */
अटल पूर्णांक hdspm_rate_multiplier(काष्ठा hdspm *hdspm, पूर्णांक rate)
अणु
	अगर (rate <= 48000) अणु
		अगर (hdspm->control_रेजिस्टर & HDSPM_QuadSpeed)
			वापस rate * 4;
		अन्यथा अगर (hdspm->control_रेजिस्टर &
				HDSPM_DoubleSpeed)
			वापस rate * 2;
	पूर्ण
	वापस rate;
पूर्ण

/* check क्रम बाह्यal sample rate, वापसs the sample rate in Hz*/
अटल पूर्णांक hdspm_बाह्यal_sample_rate(काष्ठा hdspm *hdspm)
अणु
	अचिन्हित पूर्णांक status, status2;
	पूर्णांक syncref, rate = 0, rate_bits;

	चयन (hdspm->io_type) अणु
	हाल AES32:
		status2 = hdspm_पढ़ो(hdspm, HDSPM_statusRegister2);
		status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);

		syncref = hdspm_स्वतःsync_ref(hdspm);
		चयन (syncref) अणु
		हाल HDSPM_AES32_AUTOSYNC_FROM_WORD:
		/* Check WC sync and get sample rate */
			अगर (hdspm_wc_sync_check(hdspm))
				वापस HDSPM_bit2freq(hdspm_get_wc_sample_rate(hdspm));
			अवरोध;

		हाल HDSPM_AES32_AUTOSYNC_FROM_AES1:
		हाल HDSPM_AES32_AUTOSYNC_FROM_AES2:
		हाल HDSPM_AES32_AUTOSYNC_FROM_AES3:
		हाल HDSPM_AES32_AUTOSYNC_FROM_AES4:
		हाल HDSPM_AES32_AUTOSYNC_FROM_AES5:
		हाल HDSPM_AES32_AUTOSYNC_FROM_AES6:
		हाल HDSPM_AES32_AUTOSYNC_FROM_AES7:
		हाल HDSPM_AES32_AUTOSYNC_FROM_AES8:
		/* Check AES sync and get sample rate */
			अगर (hdspm_aes_sync_check(hdspm, syncref - HDSPM_AES32_AUTOSYNC_FROM_AES1))
				वापस HDSPM_bit2freq(hdspm_get_aes_sample_rate(hdspm,
							syncref - HDSPM_AES32_AUTOSYNC_FROM_AES1));
			अवरोध;


		हाल HDSPM_AES32_AUTOSYNC_FROM_TCO:
		/* Check TCO sync and get sample rate */
			अगर (hdspm_tco_sync_check(hdspm))
				वापस HDSPM_bit2freq(hdspm_get_tco_sample_rate(hdspm));
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण /* end चयन(syncref) */
		अवरोध;

	हाल MADIface:
		status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);

		अगर (!(status & HDSPM_madiLock)) अणु
			rate = 0;  /* no lock */
		पूर्ण अन्यथा अणु
			चयन (status & (HDSPM_status1_freqMask)) अणु
			हाल HDSPM_status1_F_0*1:
				rate = 32000; अवरोध;
			हाल HDSPM_status1_F_0*2:
				rate = 44100; अवरोध;
			हाल HDSPM_status1_F_0*3:
				rate = 48000; अवरोध;
			हाल HDSPM_status1_F_0*4:
				rate = 64000; अवरोध;
			हाल HDSPM_status1_F_0*5:
				rate = 88200; अवरोध;
			हाल HDSPM_status1_F_0*6:
				rate = 96000; अवरोध;
			हाल HDSPM_status1_F_0*7:
				rate = 128000; अवरोध;
			हाल HDSPM_status1_F_0*8:
				rate = 176400; अवरोध;
			हाल HDSPM_status1_F_0*9:
				rate = 192000; अवरोध;
			शेष:
				rate = 0; अवरोध;
			पूर्ण
		पूर्ण

		अवरोध;

	हाल MADI:
	हाल AIO:
	हाल RayDAT:
		status2 = hdspm_पढ़ो(hdspm, HDSPM_statusRegister2);
		status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
		rate = 0;

		/* अगर wordघड़ी has synced freq and wordघड़ी is valid */
		अगर ((status2 & HDSPM_wcLock) != 0 &&
				(status2 & HDSPM_SelSyncRef0) == 0) अणु

			rate_bits = status2 & HDSPM_wcFreqMask;


			चयन (rate_bits) अणु
			हाल HDSPM_wcFreq32:
				rate = 32000;
				अवरोध;
			हाल HDSPM_wcFreq44_1:
				rate = 44100;
				अवरोध;
			हाल HDSPM_wcFreq48:
				rate = 48000;
				अवरोध;
			हाल HDSPM_wcFreq64:
				rate = 64000;
				अवरोध;
			हाल HDSPM_wcFreq88_2:
				rate = 88200;
				अवरोध;
			हाल HDSPM_wcFreq96:
				rate = 96000;
				अवरोध;
			हाल HDSPM_wcFreq128:
				rate = 128000;
				अवरोध;
			हाल HDSPM_wcFreq176_4:
				rate = 176400;
				अवरोध;
			हाल HDSPM_wcFreq192:
				rate = 192000;
				अवरोध;
			शेष:
				rate = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		/* अगर rate detected and Syncref is Word than have it,
		 * word has priority to MADI
		 */
		अगर (rate != 0 &&
		(status2 & HDSPM_SelSyncRefMask) == HDSPM_SelSyncRef_WORD)
			वापस hdspm_rate_multiplier(hdspm, rate);

		/* maybe a madi input (which is taken अगर sel sync is madi) */
		अगर (status & HDSPM_madiLock) अणु
			rate_bits = status & HDSPM_madiFreqMask;

			चयन (rate_bits) अणु
			हाल HDSPM_madiFreq32:
				rate = 32000;
				अवरोध;
			हाल HDSPM_madiFreq44_1:
				rate = 44100;
				अवरोध;
			हाल HDSPM_madiFreq48:
				rate = 48000;
				अवरोध;
			हाल HDSPM_madiFreq64:
				rate = 64000;
				अवरोध;
			हाल HDSPM_madiFreq88_2:
				rate = 88200;
				अवरोध;
			हाल HDSPM_madiFreq96:
				rate = 96000;
				अवरोध;
			हाल HDSPM_madiFreq128:
				rate = 128000;
				अवरोध;
			हाल HDSPM_madiFreq176_4:
				rate = 176400;
				अवरोध;
			हाल HDSPM_madiFreq192:
				rate = 192000;
				अवरोध;
			शेष:
				rate = 0;
				अवरोध;
			पूर्ण

		पूर्ण /* endअगर HDSPM_madiLock */

		/* check sample rate from TCO or SYNC_IN */
		अणु
			bool is_valid_input = 0;
			bool has_sync = 0;

			syncref = hdspm_स्वतःsync_ref(hdspm);
			अगर (HDSPM_AUTOSYNC_FROM_TCO == syncref) अणु
				is_valid_input = 1;
				has_sync = (HDSPM_SYNC_CHECK_SYNC ==
					hdspm_tco_sync_check(hdspm));
			पूर्ण अन्यथा अगर (HDSPM_AUTOSYNC_FROM_SYNC_IN == syncref) अणु
				is_valid_input = 1;
				has_sync = (HDSPM_SYNC_CHECK_SYNC ==
					hdspm_sync_in_sync_check(hdspm));
			पूर्ण

			अगर (is_valid_input && has_sync) अणु
				rate = hdspm_round_frequency(
					hdspm_get_pll_freq(hdspm));
			पूर्ण
		पूर्ण

		rate = hdspm_rate_multiplier(hdspm, rate);

		अवरोध;
	पूर्ण

	वापस rate;
पूर्ण

/* वापस latency in samples per period */
अटल पूर्णांक hdspm_get_latency(काष्ठा hdspm *hdspm)
अणु
	पूर्णांक n;

	n = hdspm_decode_latency(hdspm->control_रेजिस्टर);

	/* Special हाल क्रम new RME cards with 32 samples period size.
	 * The three latency bits in the control रेजिस्टर
	 * (HDSP_LatencyMask) encode latency values of 64 samples as
	 * 0, 128 samples as 1 ... 4096 samples as 6. For old cards, 7
	 * denotes 8192 samples, but on new cards like RayDAT or AIO,
	 * it corresponds to 32 samples.
	 */
	अगर ((7 == n) && (RayDAT == hdspm->io_type || AIO == hdspm->io_type))
		n = -1;

	वापस 1 << (n + 6);
पूर्ण

/* Latency function */
अटल अंतरभूत व्योम hdspm_compute_period_size(काष्ठा hdspm *hdspm)
अणु
	hdspm->period_bytes = 4 * hdspm_get_latency(hdspm);
पूर्ण


अटल snd_pcm_uframes_t hdspm_hw_poपूर्णांकer(काष्ठा hdspm *hdspm)
अणु
	पूर्णांक position;

	position = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);

	चयन (hdspm->io_type) अणु
	हाल RayDAT:
	हाल AIO:
		position &= HDSPM_BufferPositionMask;
		position /= 4; /* Bytes per sample */
		अवरोध;
	शेष:
		position = (position & HDSPM_BufferID) ?
			(hdspm->period_bytes / 4) : 0;
	पूर्ण

	वापस position;
पूर्ण


अटल अंतरभूत व्योम hdspm_start_audio(काष्ठा hdspm * s)
अणु
	s->control_रेजिस्टर |= (HDSPM_AudioInterruptEnable | HDSPM_Start);
	hdspm_ग_लिखो(s, HDSPM_controlRegister, s->control_रेजिस्टर);
पूर्ण

अटल अंतरभूत व्योम hdspm_stop_audio(काष्ठा hdspm * s)
अणु
	s->control_रेजिस्टर &= ~(HDSPM_Start | HDSPM_AudioInterruptEnable);
	hdspm_ग_लिखो(s, HDSPM_controlRegister, s->control_रेजिस्टर);
पूर्ण

/* should I silence all or only खोलोed ones ? करोit all क्रम first even is 4MB*/
अटल व्योम hdspm_silence_playback(काष्ठा hdspm *hdspm)
अणु
	पूर्णांक i;
	पूर्णांक n = hdspm->period_bytes;
	व्योम *buf = hdspm->playback_buffer;

	अगर (!buf)
		वापस;

	क्रम (i = 0; i < HDSPM_MAX_CHANNELS; i++) अणु
		स_रखो(buf, 0, n);
		buf += HDSPM_CHANNEL_BUFFER_BYTES;
	पूर्ण
पूर्ण

अटल पूर्णांक hdspm_set_पूर्णांकerrupt_पूर्णांकerval(काष्ठा hdspm *s, अचिन्हित पूर्णांक frames)
अणु
	पूर्णांक n;

	spin_lock_irq(&s->lock);

	अगर (32 == frames) अणु
		/* Special हाल क्रम new RME cards like RayDAT/AIO which
		 * support period sizes of 32 samples. Since latency is
		 * encoded in the three bits of HDSP_LatencyMask, we can only
		 * have values from 0 .. 7. While 0 still means 64 samples and
		 * 6 represents 4096 samples on all cards, 7 represents 8192
		 * on older cards and 32 samples on new cards.
		 *
		 * In other words, period size in samples is calculated by
		 * 2^(n+6) with n ranging from 0 .. 7.
		 */
		n = 7;
	पूर्ण अन्यथा अणु
		frames >>= 7;
		n = 0;
		जबतक (frames) अणु
			n++;
			frames >>= 1;
		पूर्ण
	पूर्ण

	s->control_रेजिस्टर &= ~HDSPM_LatencyMask;
	s->control_रेजिस्टर |= hdspm_encode_latency(n);

	hdspm_ग_लिखो(s, HDSPM_controlRegister, s->control_रेजिस्टर);

	hdspm_compute_period_size(s);

	spin_unlock_irq(&s->lock);

	वापस 0;
पूर्ण

अटल u64 hdspm_calc_dds_value(काष्ठा hdspm *hdspm, u64 period)
अणु
	u64 freq_स्थिर;

	अगर (period == 0)
		वापस 0;

	चयन (hdspm->io_type) अणु
	हाल MADI:
	हाल AES32:
		freq_स्थिर = 110069313433624ULL;
		अवरोध;
	हाल RayDAT:
	हाल AIO:
		freq_स्थिर = 104857600000000ULL;
		अवरोध;
	हाल MADIface:
		freq_स्थिर = 131072000000000ULL;
		अवरोध;
	शेष:
		snd_BUG();
		वापस 0;
	पूर्ण

	वापस भाग_u64(freq_स्थिर, period);
पूर्ण


अटल व्योम hdspm_set_dds_value(काष्ठा hdspm *hdspm, पूर्णांक rate)
अणु
	u64 n;

	अगर (snd_BUG_ON(rate <= 0))
		वापस;

	अगर (rate >= 112000)
		rate /= 4;
	अन्यथा अगर (rate >= 56000)
		rate /= 2;

	चयन (hdspm->io_type) अणु
	हाल MADIface:
		n = 131072000000000ULL;  /* 125 MHz */
		अवरोध;
	हाल MADI:
	हाल AES32:
		n = 110069313433624ULL;  /* 105 MHz */
		अवरोध;
	हाल RayDAT:
	हाल AIO:
		n = 104857600000000ULL;  /* 100 MHz */
		अवरोध;
	शेष:
		snd_BUG();
		वापस;
	पूर्ण

	n = भाग_u64(n, rate);
	/* n should be less than 2^32 क्रम being written to FREQ रेजिस्टर */
	snd_BUG_ON(n >> 32);
	hdspm_ग_लिखो(hdspm, HDSPM_freqReg, (u32)n);
पूर्ण

/* dummy set rate lets see what happens */
अटल पूर्णांक hdspm_set_rate(काष्ठा hdspm * hdspm, पूर्णांक rate, पूर्णांक called_पूर्णांकernally)
अणु
	पूर्णांक current_rate;
	पूर्णांक rate_bits;
	पूर्णांक not_set = 0;
	पूर्णांक current_speed, target_speed;

	/* ASSUMPTION: hdspm->lock is either set, or there is no need क्रम
	   it (e.g. during module initialization).
	 */

	अगर (!(hdspm->control_रेजिस्टर & HDSPM_ClockModeMaster)) अणु

		/* SLAVE --- */
		अगर (called_पूर्णांकernally) अणु

			/* request from ctl or card initialization
			   just make a warning an remember setting
			   क्रम future master mode चयनing */

			dev_warn(hdspm->card->dev,
				 "Warning: device is not running as a clock master.\n");
			not_set = 1;
		पूर्ण अन्यथा अणु

			/* hw_param request जबतक in AutoSync mode */
			पूर्णांक बाह्यal_freq =
			    hdspm_बाह्यal_sample_rate(hdspm);

			अगर (hdspm_स्वतःsync_ref(hdspm) ==
			    HDSPM_AUTOSYNC_FROM_NONE) अणु

				dev_warn(hdspm->card->dev,
					 "Detected no External Sync\n");
				not_set = 1;

			पूर्ण अन्यथा अगर (rate != बाह्यal_freq) अणु

				dev_warn(hdspm->card->dev,
					 "Warning: No AutoSync source for requested rate\n");
				not_set = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	current_rate = hdspm->प्रणाली_sample_rate;

	/* Changing between Singe, Double and Quad speed is not
	   allowed अगर any substreams are खोलो. This is because such a change
	   causes a shअगरt in the location of the DMA buffers and a reduction
	   in the number of available buffers.

	   Note that a similar but essentially insoluble problem exists क्रम
	   बाह्यally-driven rate changes. All we can करो is to flag rate
	   changes in the पढ़ो/ग_लिखो routines.
	 */

	अगर (current_rate <= 48000)
		current_speed = HDSPM_SPEED_SINGLE;
	अन्यथा अगर (current_rate <= 96000)
		current_speed = HDSPM_SPEED_DOUBLE;
	अन्यथा
		current_speed = HDSPM_SPEED_QUAD;

	अगर (rate <= 48000)
		target_speed = HDSPM_SPEED_SINGLE;
	अन्यथा अगर (rate <= 96000)
		target_speed = HDSPM_SPEED_DOUBLE;
	अन्यथा
		target_speed = HDSPM_SPEED_QUAD;

	चयन (rate) अणु
	हाल 32000:
		rate_bits = HDSPM_Frequency32KHz;
		अवरोध;
	हाल 44100:
		rate_bits = HDSPM_Frequency44_1KHz;
		अवरोध;
	हाल 48000:
		rate_bits = HDSPM_Frequency48KHz;
		अवरोध;
	हाल 64000:
		rate_bits = HDSPM_Frequency64KHz;
		अवरोध;
	हाल 88200:
		rate_bits = HDSPM_Frequency88_2KHz;
		अवरोध;
	हाल 96000:
		rate_bits = HDSPM_Frequency96KHz;
		अवरोध;
	हाल 128000:
		rate_bits = HDSPM_Frequency128KHz;
		अवरोध;
	हाल 176400:
		rate_bits = HDSPM_Frequency176_4KHz;
		अवरोध;
	हाल 192000:
		rate_bits = HDSPM_Frequency192KHz;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (current_speed != target_speed
	    && (hdspm->capture_pid >= 0 || hdspm->playback_pid >= 0)) अणु
		dev_err(hdspm->card->dev,
			"cannot change from %s speed to %s speed mode (capture PID = %d, playback PID = %d)\n",
			hdspm_speed_names[current_speed],
			hdspm_speed_names[target_speed],
			hdspm->capture_pid, hdspm->playback_pid);
		वापस -EBUSY;
	पूर्ण

	hdspm->control_रेजिस्टर &= ~HDSPM_FrequencyMask;
	hdspm->control_रेजिस्टर |= rate_bits;
	hdspm_ग_लिखो(hdspm, HDSPM_controlRegister, hdspm->control_रेजिस्टर);

	/* For AES32, need to set DDS value in FREQ रेजिस्टर
	   For MADI, also apparently */
	hdspm_set_dds_value(hdspm, rate);

	अगर (AES32 == hdspm->io_type && rate != current_rate)
		hdspm_ग_लिखो(hdspm, HDSPM_eeprom_wr, 0);

	hdspm->प्रणाली_sample_rate = rate;

	अगर (rate <= 48000) अणु
		hdspm->channel_map_in = hdspm->channel_map_in_ss;
		hdspm->channel_map_out = hdspm->channel_map_out_ss;
		hdspm->max_channels_in = hdspm->ss_in_channels;
		hdspm->max_channels_out = hdspm->ss_out_channels;
		hdspm->port_names_in = hdspm->port_names_in_ss;
		hdspm->port_names_out = hdspm->port_names_out_ss;
	पूर्ण अन्यथा अगर (rate <= 96000) अणु
		hdspm->channel_map_in = hdspm->channel_map_in_ds;
		hdspm->channel_map_out = hdspm->channel_map_out_ds;
		hdspm->max_channels_in = hdspm->ds_in_channels;
		hdspm->max_channels_out = hdspm->ds_out_channels;
		hdspm->port_names_in = hdspm->port_names_in_ds;
		hdspm->port_names_out = hdspm->port_names_out_ds;
	पूर्ण अन्यथा अणु
		hdspm->channel_map_in = hdspm->channel_map_in_qs;
		hdspm->channel_map_out = hdspm->channel_map_out_qs;
		hdspm->max_channels_in = hdspm->qs_in_channels;
		hdspm->max_channels_out = hdspm->qs_out_channels;
		hdspm->port_names_in = hdspm->port_names_in_qs;
		hdspm->port_names_out = hdspm->port_names_out_qs;
	पूर्ण

	अगर (not_set != 0)
		वापस -1;

	वापस 0;
पूर्ण

/* मुख्यly क्रम init to 0 on load */
अटल व्योम all_in_all_mixer(काष्ठा hdspm * hdspm, पूर्णांक sgain)
अणु
	पूर्णांक i, j;
	अचिन्हित पूर्णांक gain;

	अगर (sgain > UNITY_GAIN)
		gain = UNITY_GAIN;
	अन्यथा अगर (sgain < 0)
		gain = 0;
	अन्यथा
		gain = sgain;

	क्रम (i = 0; i < HDSPM_MIXER_CHANNELS; i++)
		क्रम (j = 0; j < HDSPM_MIXER_CHANNELS; j++) अणु
			hdspm_ग_लिखो_in_gain(hdspm, i, j, gain);
			hdspm_ग_लिखो_pb_gain(hdspm, i, j, gain);
		पूर्ण
पूर्ण

/*----------------------------------------------------------------------------
   MIDI
  ----------------------------------------------------------------------------*/

अटल अंतरभूत अचिन्हित अक्षर snd_hdspm_midi_पढ़ो_byte (काष्ठा hdspm *hdspm,
						      पूर्णांक id)
अणु
	/* the hardware alपढ़ोy करोes the relevant bit-mask with 0xff */
	वापस hdspm_पढ़ो(hdspm, hdspm->midi[id].dataIn);
पूर्ण

अटल अंतरभूत व्योम snd_hdspm_midi_ग_लिखो_byte (काष्ठा hdspm *hdspm, पूर्णांक id,
					      पूर्णांक val)
अणु
	/* the hardware alपढ़ोy करोes the relevant bit-mask with 0xff */
	वापस hdspm_ग_लिखो(hdspm, hdspm->midi[id].dataOut, val);
पूर्ण

अटल अंतरभूत पूर्णांक snd_hdspm_midi_input_available (काष्ठा hdspm *hdspm, पूर्णांक id)
अणु
	वापस hdspm_पढ़ो(hdspm, hdspm->midi[id].statusIn) & 0xFF;
पूर्ण

अटल अंतरभूत पूर्णांक snd_hdspm_midi_output_possible (काष्ठा hdspm *hdspm, पूर्णांक id)
अणु
	पूर्णांक fअगरo_bytes_used;

	fअगरo_bytes_used = hdspm_पढ़ो(hdspm, hdspm->midi[id].statusOut) & 0xFF;

	अगर (fअगरo_bytes_used < 128)
		वापस  128 - fअगरo_bytes_used;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम snd_hdspm_flush_midi_input(काष्ठा hdspm *hdspm, पूर्णांक id)
अणु
	जबतक (snd_hdspm_midi_input_available (hdspm, id))
		snd_hdspm_midi_पढ़ो_byte (hdspm, id);
पूर्ण

अटल पूर्णांक snd_hdspm_midi_output_ग_लिखो (काष्ठा hdspm_midi *hmidi)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक n_pending;
	पूर्णांक to_ग_लिखो;
	पूर्णांक i;
	अचिन्हित अक्षर buf[128];

	/* Output is not पूर्णांकerrupt driven */

	spin_lock_irqsave (&hmidi->lock, flags);
	अगर (hmidi->output &&
	    !snd_rawmidi_transmit_empty (hmidi->output)) अणु
		n_pending = snd_hdspm_midi_output_possible (hmidi->hdspm,
							    hmidi->id);
		अगर (n_pending > 0) अणु
			अगर (n_pending > (पूर्णांक)माप (buf))
				n_pending = माप (buf);

			to_ग_लिखो = snd_rawmidi_transmit (hmidi->output, buf,
							 n_pending);
			अगर (to_ग_लिखो > 0) अणु
				क्रम (i = 0; i < to_ग_लिखो; ++i)
					snd_hdspm_midi_ग_लिखो_byte (hmidi->hdspm,
								   hmidi->id,
								   buf[i]);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore (&hmidi->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_midi_input_पढ़ो (काष्ठा hdspm_midi *hmidi)
अणु
	अचिन्हित अक्षर buf[128]; /* this buffer is deचिन्हित to match the MIDI
				 * input FIFO size
				 */
	अचिन्हित दीर्घ flags;
	पूर्णांक n_pending;
	पूर्णांक i;

	spin_lock_irqsave (&hmidi->lock, flags);
	n_pending = snd_hdspm_midi_input_available (hmidi->hdspm, hmidi->id);
	अगर (n_pending > 0) अणु
		अगर (hmidi->input) अणु
			अगर (n_pending > (पूर्णांक)माप (buf))
				n_pending = माप (buf);
			क्रम (i = 0; i < n_pending; ++i)
				buf[i] = snd_hdspm_midi_पढ़ो_byte (hmidi->hdspm,
								   hmidi->id);
			अगर (n_pending)
				snd_rawmidi_receive (hmidi->input, buf,
						     n_pending);
		पूर्ण अन्यथा अणु
			/* flush the MIDI input FIFO */
			जबतक (n_pending--)
				snd_hdspm_midi_पढ़ो_byte (hmidi->hdspm,
							  hmidi->id);
		पूर्ण
	पूर्ण
	hmidi->pending = 0;
	spin_unlock_irqrestore(&hmidi->lock, flags);

	spin_lock_irqsave(&hmidi->hdspm->lock, flags);
	hmidi->hdspm->control_रेजिस्टर |= hmidi->ie;
	hdspm_ग_लिखो(hmidi->hdspm, HDSPM_controlRegister,
		    hmidi->hdspm->control_रेजिस्टर);
	spin_unlock_irqrestore(&hmidi->hdspm->lock, flags);

	वापस snd_hdspm_midi_output_ग_लिखो (hmidi);
पूर्ण

अटल व्योम
snd_hdspm_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा hdspm *hdspm;
	काष्ठा hdspm_midi *hmidi;
	अचिन्हित दीर्घ flags;

	hmidi = substream->rmidi->निजी_data;
	hdspm = hmidi->hdspm;

	spin_lock_irqsave (&hdspm->lock, flags);
	अगर (up) अणु
		अगर (!(hdspm->control_रेजिस्टर & hmidi->ie)) अणु
			snd_hdspm_flush_midi_input (hdspm, hmidi->id);
			hdspm->control_रेजिस्टर |= hmidi->ie;
		पूर्ण
	पूर्ण अन्यथा अणु
		hdspm->control_रेजिस्टर &= ~hmidi->ie;
	पूर्ण

	hdspm_ग_लिखो(hdspm, HDSPM_controlRegister, hdspm->control_रेजिस्टर);
	spin_unlock_irqrestore (&hdspm->lock, flags);
पूर्ण

अटल व्योम snd_hdspm_midi_output_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा hdspm_midi *hmidi = from_समयr(hmidi, t, समयr);
	अचिन्हित दीर्घ flags;

	snd_hdspm_midi_output_ग_लिखो(hmidi);
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

अटल व्योम
snd_hdspm_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा hdspm_midi *hmidi;
	अचिन्हित दीर्घ flags;

	hmidi = substream->rmidi->निजी_data;
	spin_lock_irqsave (&hmidi->lock, flags);
	अगर (up) अणु
		अगर (!hmidi->isसमयr) अणु
			समयr_setup(&hmidi->समयr,
				    snd_hdspm_midi_output_समयr, 0);
			mod_समयr(&hmidi->समयr, 1 + jअगरfies);
			hmidi->isसमयr++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hmidi->isसमयr && --hmidi->isसमयr <= 0)
			del_समयr (&hmidi->समयr);
	पूर्ण
	spin_unlock_irqrestore (&hmidi->lock, flags);
	अगर (up)
		snd_hdspm_midi_output_ग_लिखो(hmidi);
पूर्ण

अटल पूर्णांक snd_hdspm_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा hdspm_midi *hmidi;

	hmidi = substream->rmidi->निजी_data;
	spin_lock_irq (&hmidi->lock);
	snd_hdspm_flush_midi_input (hmidi->hdspm, hmidi->id);
	hmidi->input = substream;
	spin_unlock_irq (&hmidi->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा hdspm_midi *hmidi;

	hmidi = substream->rmidi->निजी_data;
	spin_lock_irq (&hmidi->lock);
	hmidi->output = substream;
	spin_unlock_irq (&hmidi->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा hdspm_midi *hmidi;

	snd_hdspm_midi_input_trigger (substream, 0);

	hmidi = substream->rmidi->निजी_data;
	spin_lock_irq (&hmidi->lock);
	hmidi->input = शून्य;
	spin_unlock_irq (&hmidi->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा hdspm_midi *hmidi;

	snd_hdspm_midi_output_trigger (substream, 0);

	hmidi = substream->rmidi->निजी_data;
	spin_lock_irq (&hmidi->lock);
	hmidi->output = शून्य;
	spin_unlock_irq (&hmidi->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops snd_hdspm_midi_output =
अणु
	.खोलो =		snd_hdspm_midi_output_खोलो,
	.बंद =	snd_hdspm_midi_output_बंद,
	.trigger =	snd_hdspm_midi_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_hdspm_midi_input =
अणु
	.खोलो =		snd_hdspm_midi_input_खोलो,
	.बंद =	snd_hdspm_midi_input_बंद,
	.trigger =	snd_hdspm_midi_input_trigger,
पूर्ण;

अटल पूर्णांक snd_hdspm_create_midi(काष्ठा snd_card *card,
				 काष्ठा hdspm *hdspm, पूर्णांक id)
अणु
	पूर्णांक err;
	अक्षर buf[64];

	hdspm->midi[id].id = id;
	hdspm->midi[id].hdspm = hdspm;
	spin_lock_init (&hdspm->midi[id].lock);

	अगर (0 == id) अणु
		अगर (MADIface == hdspm->io_type) अणु
			/* MIDI-over-MADI on HDSPe MADIface */
			hdspm->midi[0].dataIn = HDSPM_midiDataIn2;
			hdspm->midi[0].statusIn = HDSPM_midiStatusIn2;
			hdspm->midi[0].dataOut = HDSPM_midiDataOut2;
			hdspm->midi[0].statusOut = HDSPM_midiStatusOut2;
			hdspm->midi[0].ie = HDSPM_Midi2InterruptEnable;
			hdspm->midi[0].irq = HDSPM_midi2IRQPending;
		पूर्ण अन्यथा अणु
			hdspm->midi[0].dataIn = HDSPM_midiDataIn0;
			hdspm->midi[0].statusIn = HDSPM_midiStatusIn0;
			hdspm->midi[0].dataOut = HDSPM_midiDataOut0;
			hdspm->midi[0].statusOut = HDSPM_midiStatusOut0;
			hdspm->midi[0].ie = HDSPM_Midi0InterruptEnable;
			hdspm->midi[0].irq = HDSPM_midi0IRQPending;
		पूर्ण
	पूर्ण अन्यथा अगर (1 == id) अणु
		hdspm->midi[1].dataIn = HDSPM_midiDataIn1;
		hdspm->midi[1].statusIn = HDSPM_midiStatusIn1;
		hdspm->midi[1].dataOut = HDSPM_midiDataOut1;
		hdspm->midi[1].statusOut = HDSPM_midiStatusOut1;
		hdspm->midi[1].ie = HDSPM_Midi1InterruptEnable;
		hdspm->midi[1].irq = HDSPM_midi1IRQPending;
	पूर्ण अन्यथा अगर ((2 == id) && (MADI == hdspm->io_type)) अणु
		/* MIDI-over-MADI on HDSPe MADI */
		hdspm->midi[2].dataIn = HDSPM_midiDataIn2;
		hdspm->midi[2].statusIn = HDSPM_midiStatusIn2;
		hdspm->midi[2].dataOut = HDSPM_midiDataOut2;
		hdspm->midi[2].statusOut = HDSPM_midiStatusOut2;
		hdspm->midi[2].ie = HDSPM_Midi2InterruptEnable;
		hdspm->midi[2].irq = HDSPM_midi2IRQPending;
	पूर्ण अन्यथा अगर (2 == id) अणु
		/* TCO MTC, पढ़ो only */
		hdspm->midi[2].dataIn = HDSPM_midiDataIn2;
		hdspm->midi[2].statusIn = HDSPM_midiStatusIn2;
		hdspm->midi[2].dataOut = -1;
		hdspm->midi[2].statusOut = -1;
		hdspm->midi[2].ie = HDSPM_Midi2InterruptEnable;
		hdspm->midi[2].irq = HDSPM_midi2IRQPendingAES;
	पूर्ण अन्यथा अगर (3 == id) अणु
		/* TCO MTC on HDSPe MADI */
		hdspm->midi[3].dataIn = HDSPM_midiDataIn3;
		hdspm->midi[3].statusIn = HDSPM_midiStatusIn3;
		hdspm->midi[3].dataOut = -1;
		hdspm->midi[3].statusOut = -1;
		hdspm->midi[3].ie = HDSPM_Midi3InterruptEnable;
		hdspm->midi[3].irq = HDSPM_midi3IRQPending;
	पूर्ण

	अगर ((id < 2) || ((2 == id) && ((MADI == hdspm->io_type) ||
					(MADIface == hdspm->io_type)))) अणु
		अगर ((id == 0) && (MADIface == hdspm->io_type)) अणु
			snम_लिखो(buf, माप(buf), "%s MIDIoverMADI",
				 card->लघुname);
		पूर्ण अन्यथा अगर ((id == 2) && (MADI == hdspm->io_type)) अणु
			snम_लिखो(buf, माप(buf), "%s MIDIoverMADI",
				 card->लघुname);
		पूर्ण अन्यथा अणु
			snम_लिखो(buf, माप(buf), "%s MIDI %d",
				 card->लघुname, id+1);
		पूर्ण
		err = snd_rawmidi_new(card, buf, id, 1, 1,
				&hdspm->midi[id].rmidi);
		अगर (err < 0)
			वापस err;

		snम_लिखो(hdspm->midi[id].rmidi->name,
			 माप(hdspm->midi[id].rmidi->name),
			 "%s MIDI %d", card->id, id+1);
		hdspm->midi[id].rmidi->निजी_data = &hdspm->midi[id];

		snd_rawmidi_set_ops(hdspm->midi[id].rmidi,
				SNDRV_RAWMIDI_STREAM_OUTPUT,
				&snd_hdspm_midi_output);
		snd_rawmidi_set_ops(hdspm->midi[id].rmidi,
				SNDRV_RAWMIDI_STREAM_INPUT,
				&snd_hdspm_midi_input);

		hdspm->midi[id].rmidi->info_flags |=
			SNDRV_RAWMIDI_INFO_OUTPUT |
			SNDRV_RAWMIDI_INFO_INPUT |
			SNDRV_RAWMIDI_INFO_DUPLEX;
	पूर्ण अन्यथा अणु
		/* TCO MTC, पढ़ो only */
		snम_लिखो(buf, माप(buf), "%s MTC %d",
			 card->लघुname, id+1);
		err = snd_rawmidi_new(card, buf, id, 1, 1,
				&hdspm->midi[id].rmidi);
		अगर (err < 0)
			वापस err;

		snम_लिखो(hdspm->midi[id].rmidi->name,
			 माप(hdspm->midi[id].rmidi->name),
			 "%s MTC %d", card->id, id+1);
		hdspm->midi[id].rmidi->निजी_data = &hdspm->midi[id];

		snd_rawmidi_set_ops(hdspm->midi[id].rmidi,
				SNDRV_RAWMIDI_STREAM_INPUT,
				&snd_hdspm_midi_input);

		hdspm->midi[id].rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT;
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम hdspm_midi_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdspm *hdspm = container_of(work, काष्ठा hdspm, midi_work);
	पूर्णांक i = 0;

	जबतक (i < hdspm->midiPorts) अणु
		अगर (hdspm->midi[i].pending)
			snd_hdspm_midi_input_पढ़ो(&hdspm->midi[i]);

		i++;
	पूर्ण
पूर्ण


/*-----------------------------------------------------------------------------
  Status Interface
  ----------------------------------------------------------------------------*/

/* get the प्रणाली sample rate which is set */


अटल अंतरभूत पूर्णांक hdspm_get_pll_freq(काष्ठा hdspm *hdspm)
अणु
	अचिन्हित पूर्णांक period, rate;

	period = hdspm_पढ़ो(hdspm, HDSPM_RD_PLL_FREQ);
	rate = hdspm_calc_dds_value(hdspm, period);

	वापस rate;
पूर्ण

/*
 * Calculate the real sample rate from the
 * current DDS value.
 */
अटल पूर्णांक hdspm_get_प्रणाली_sample_rate(काष्ठा hdspm *hdspm)
अणु
	अचिन्हित पूर्णांक rate;

	rate = hdspm_get_pll_freq(hdspm);

	अगर (rate > 207000) अणु
		/* Unreasonable high sample rate as seen on PCI MADI cards. */
		अगर (0 == hdspm_प्रणाली_घड़ी_mode(hdspm)) अणु
			/* master mode, वापस पूर्णांकernal sample rate */
			rate = hdspm->प्रणाली_sample_rate;
		पूर्ण अन्यथा अणु
			/* slave mode, वापस बाह्यal sample rate */
			rate = hdspm_बाह्यal_sample_rate(hdspm);
			अगर (!rate)
				rate = hdspm->प्रणाली_sample_rate;
		पूर्ण
	पूर्ण

	वापस rate;
पूर्ण


#घोषणा HDSPM_SYSTEM_SAMPLE_RATE(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |\
		SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_प्रणाली_sample_rate, \
	.put = snd_hdspm_put_प्रणाली_sample_rate, \
	.get = snd_hdspm_get_प्रणाली_sample_rate \
पूर्ण

अटल पूर्णांक snd_hdspm_info_प्रणाली_sample_rate(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 27000;
	uinfo->value.पूर्णांकeger.max = 207000;
	uinfo->value.पूर्णांकeger.step = 1;
	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdspm_get_प्रणाली_sample_rate(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *
					    ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = hdspm_get_प्रणाली_sample_rate(hdspm);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_प्रणाली_sample_rate(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *
					    ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक rate = ucontrol->value.पूर्णांकeger.value[0];

	अगर (rate < 27000 || rate > 207000)
		वापस -EINVAL;
	hdspm_set_dds_value(hdspm, ucontrol->value.पूर्णांकeger.value[0]);
	वापस 0;
पूर्ण


/*
 * Returns the WordClock sample rate class क्रम the given card.
 */
अटल पूर्णांक hdspm_get_wc_sample_rate(काष्ठा hdspm *hdspm)
अणु
	पूर्णांक status;

	चयन (hdspm->io_type) अणु
	हाल RayDAT:
	हाल AIO:
		status = hdspm_पढ़ो(hdspm, HDSPM_RD_STATUS_1);
		वापस (status >> 16) & 0xF;
	हाल AES32:
		status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
		वापस (status >> HDSPM_AES32_wcFreq_bit) & 0xF;
	शेष:
		अवरोध;
	पूर्ण


	वापस 0;
पूर्ण


/*
 * Returns the TCO sample rate class क्रम the given card.
 */
अटल पूर्णांक hdspm_get_tco_sample_rate(काष्ठा hdspm *hdspm)
अणु
	पूर्णांक status;

	अगर (hdspm->tco) अणु
		चयन (hdspm->io_type) अणु
		हाल RayDAT:
		हाल AIO:
			status = hdspm_पढ़ो(hdspm, HDSPM_RD_STATUS_1);
			वापस (status >> 20) & 0xF;
		हाल AES32:
			status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
			वापस (status >> 1) & 0xF;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


/*
 * Returns the SYNC_IN sample rate class क्रम the given card.
 */
अटल पूर्णांक hdspm_get_sync_in_sample_rate(काष्ठा hdspm *hdspm)
अणु
	पूर्णांक status;

	अगर (hdspm->tco) अणु
		चयन (hdspm->io_type) अणु
		हाल RayDAT:
		हाल AIO:
			status = hdspm_पढ़ो(hdspm, HDSPM_RD_STATUS_2);
			वापस (status >> 12) & 0xF;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Returns the AES sample rate class क्रम the given card.
 */
अटल पूर्णांक hdspm_get_aes_sample_rate(काष्ठा hdspm *hdspm, पूर्णांक index)
अणु
	पूर्णांक समयcode;

	चयन (hdspm->io_type) अणु
	हाल AES32:
		समयcode = hdspm_पढ़ो(hdspm, HDSPM_समयcodeRegister);
		वापस (समयcode >> (4*index)) & 0xF;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Returns the sample rate class क्रम input source <idx> क्रम
 * 'new style' cards like the AIO and RayDAT.
 */
अटल पूर्णांक hdspm_get_s1_sample_rate(काष्ठा hdspm *hdspm, अचिन्हित पूर्णांक idx)
अणु
	पूर्णांक status = hdspm_पढ़ो(hdspm, HDSPM_RD_STATUS_2);

	वापस (status >> (idx*4)) & 0xF;
पूर्ण

#घोषणा ENUMERATED_CTL_INFO(info, texts) \
	snd_ctl_क्रमागत_info(info, 1, ARRAY_SIZE(texts), texts)


/* Helper function to query the बाह्यal sample rate and वापस the
 * corresponding क्रमागत to be वापसed to userspace.
 */
अटल पूर्णांक hdspm_बाह्यal_rate_to_क्रमागत(काष्ठा hdspm *hdspm)
अणु
	पूर्णांक rate = hdspm_बाह्यal_sample_rate(hdspm);
	पूर्णांक i, selected_rate = 0;
	क्रम (i = 1; i < 10; i++)
		अगर (HDSPM_bit2freq(i) == rate) अणु
			selected_rate = i;
			अवरोध;
		पूर्ण
	वापस selected_rate;
पूर्ण


#घोषणा HDSPM_AUTOSYNC_SAMPLE_RATE(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.निजी_value = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READ, \
	.info = snd_hdspm_info_स्वतःsync_sample_rate, \
	.get = snd_hdspm_get_स्वतःsync_sample_rate \
पूर्ण


अटल पूर्णांक snd_hdspm_info_स्वतःsync_sample_rate(काष्ठा snd_kcontrol *kcontrol,
					       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	ENUMERATED_CTL_INFO(uinfo, texts_freq);
	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdspm_get_स्वतःsync_sample_rate(काष्ठा snd_kcontrol *kcontrol,
					      काष्ठा snd_ctl_elem_value *
					      ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	चयन (hdspm->io_type) अणु
	हाल RayDAT:
		चयन (kcontrol->निजी_value) अणु
		हाल 0:
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_get_wc_sample_rate(hdspm);
			अवरोध;
		हाल 7:
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_get_tco_sample_rate(hdspm);
			अवरोध;
		हाल 8:
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_get_sync_in_sample_rate(hdspm);
			अवरोध;
		शेष:
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_get_s1_sample_rate(hdspm,
						kcontrol->निजी_value-1);
		पूर्ण
		अवरोध;

	हाल AIO:
		चयन (kcontrol->निजी_value) अणु
		हाल 0: /* WC */
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_get_wc_sample_rate(hdspm);
			अवरोध;
		हाल 4: /* TCO */
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_get_tco_sample_rate(hdspm);
			अवरोध;
		हाल 5: /* SYNC_IN */
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_get_sync_in_sample_rate(hdspm);
			अवरोध;
		शेष:
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_get_s1_sample_rate(hdspm,
						kcontrol->निजी_value-1);
		पूर्ण
		अवरोध;

	हाल AES32:

		चयन (kcontrol->निजी_value) अणु
		हाल 0: /* WC */
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_get_wc_sample_rate(hdspm);
			अवरोध;
		हाल 9: /* TCO */
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_get_tco_sample_rate(hdspm);
			अवरोध;
		हाल 10: /* SYNC_IN */
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_get_sync_in_sample_rate(hdspm);
			अवरोध;
		हाल 11: /* External Rate */
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_बाह्यal_rate_to_क्रमागत(hdspm);
			अवरोध;
		शेष: /* AES1 to AES8 */
			ucontrol->value.क्रमागतerated.item[0] =
				hdspm_get_aes_sample_rate(hdspm,
						kcontrol->निजी_value -
						HDSPM_AES32_AUTOSYNC_FROM_AES1);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल MADI:
	हाल MADIface:
		ucontrol->value.क्रमागतerated.item[0] =
			hdspm_बाह्यal_rate_to_क्रमागत(hdspm);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


#घोषणा HDSPM_SYSTEM_CLOCK_MODE(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |\
		SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_प्रणाली_घड़ी_mode, \
	.get = snd_hdspm_get_प्रणाली_घड़ी_mode, \
	.put = snd_hdspm_put_प्रणाली_घड़ी_mode, \
पूर्ण


/*
 * Returns the प्रणाली घड़ी mode क्रम the given card.
 * @वापसs 0 - master, 1 - slave
 */
अटल पूर्णांक hdspm_प्रणाली_घड़ी_mode(काष्ठा hdspm *hdspm)
अणु
	चयन (hdspm->io_type) अणु
	हाल AIO:
	हाल RayDAT:
		अगर (hdspm->settings_रेजिस्टर & HDSPM_c0Master)
			वापस 0;
		अवरोध;

	शेष:
		अगर (hdspm->control_रेजिस्टर & HDSPM_ClockModeMaster)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण


/*
 * Sets the प्रणाली घड़ी mode.
 * @param mode 0 - master, 1 - slave
 */
अटल व्योम hdspm_set_प्रणाली_घड़ी_mode(काष्ठा hdspm *hdspm, पूर्णांक mode)
अणु
	hdspm_set_toggle_setting(hdspm,
			(hdspm_is_raydat_or_aio(hdspm)) ?
			HDSPM_c0Master : HDSPM_ClockModeMaster,
			(0 == mode));
पूर्ण


अटल पूर्णांक snd_hdspm_info_प्रणाली_घड़ी_mode(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु "Master", "AutoSync" पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_प्रणाली_घड़ी_mode(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdspm_प्रणाली_घड़ी_mode(hdspm);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_प्रणाली_घड़ी_mode(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक val;

	अगर (!snd_hdspm_use_is_exclusive(hdspm))
		वापस -EBUSY;

	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (val < 0)
		val = 0;
	अन्यथा अगर (val > 1)
		val = 1;

	hdspm_set_प्रणाली_घड़ी_mode(hdspm, val);

	वापस 0;
पूर्ण


#घोषणा HDSPM_INTERNAL_CLOCK(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.info = snd_hdspm_info_घड़ी_source, \
	.get = snd_hdspm_get_घड़ी_source, \
	.put = snd_hdspm_put_घड़ी_source \
पूर्ण


अटल पूर्णांक hdspm_घड़ी_source(काष्ठा hdspm * hdspm)
अणु
	चयन (hdspm->प्रणाली_sample_rate) अणु
	हाल 32000: वापस 0;
	हाल 44100: वापस 1;
	हाल 48000: वापस 2;
	हाल 64000: वापस 3;
	हाल 88200: वापस 4;
	हाल 96000: वापस 5;
	हाल 128000: वापस 6;
	हाल 176400: वापस 7;
	हाल 192000: वापस 8;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक hdspm_set_घड़ी_source(काष्ठा hdspm * hdspm, पूर्णांक mode)
अणु
	पूर्णांक rate;
	चयन (mode) अणु
	हाल 0:
		rate = 32000; अवरोध;
	हाल 1:
		rate = 44100; अवरोध;
	हाल 2:
		rate = 48000; अवरोध;
	हाल 3:
		rate = 64000; अवरोध;
	हाल 4:
		rate = 88200; अवरोध;
	हाल 5:
		rate = 96000; अवरोध;
	हाल 6:
		rate = 128000; अवरोध;
	हाल 7:
		rate = 176400; अवरोध;
	हाल 8:
		rate = 192000; अवरोध;
	शेष:
		rate = 48000;
	पूर्ण
	hdspm_set_rate(hdspm, rate, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_info_घड़ी_source(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 9, texts_freq + 1);
पूर्ण

अटल पूर्णांक snd_hdspm_get_घड़ी_source(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdspm_घड़ी_source(hdspm);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_घड़ी_source(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक val;

	अगर (!snd_hdspm_use_is_exclusive(hdspm))
		वापस -EBUSY;
	val = ucontrol->value.क्रमागतerated.item[0];
	अगर (val < 0)
		val = 0;
	अगर (val > 9)
		val = 9;
	spin_lock_irq(&hdspm->lock);
	अगर (val != hdspm_घड़ी_source(hdspm))
		change = (hdspm_set_घड़ी_source(hdspm, val) == 0) ? 1 : 0;
	अन्यथा
		change = 0;
	spin_unlock_irq(&hdspm->lock);
	वापस change;
पूर्ण


#घोषणा HDSPM_PREF_SYNC_REF(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |\
			SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_pref_sync_ref, \
	.get = snd_hdspm_get_pref_sync_ref, \
	.put = snd_hdspm_put_pref_sync_ref \
पूर्ण


/*
 * Returns the current preferred sync reference setting.
 * The semantics of the वापस value are depending on the
 * card, please see the comments क्रम clarअगरication.
 */
अटल पूर्णांक hdspm_pref_sync_ref(काष्ठा hdspm * hdspm)
अणु
	चयन (hdspm->io_type) अणु
	हाल AES32:
		चयन (hdspm->control_रेजिस्टर & HDSPM_SyncRefMask) अणु
		हाल 0: वापस 0;  /* WC */
		हाल HDSPM_SyncRef0: वापस 1; /* AES 1 */
		हाल HDSPM_SyncRef1: वापस 2; /* AES 2 */
		हाल HDSPM_SyncRef1+HDSPM_SyncRef0: वापस 3; /* AES 3 */
		हाल HDSPM_SyncRef2: वापस 4; /* AES 4 */
		हाल HDSPM_SyncRef2+HDSPM_SyncRef0: वापस 5; /* AES 5 */
		हाल HDSPM_SyncRef2+HDSPM_SyncRef1: वापस 6; /* AES 6 */
		हाल HDSPM_SyncRef2+HDSPM_SyncRef1+HDSPM_SyncRef0:
						    वापस 7; /* AES 7 */
		हाल HDSPM_SyncRef3: वापस 8; /* AES 8 */
		हाल HDSPM_SyncRef3+HDSPM_SyncRef0: वापस 9; /* TCO */
		पूर्ण
		अवरोध;

	हाल MADI:
	हाल MADIface:
		अगर (hdspm->tco) अणु
			चयन (hdspm->control_रेजिस्टर & HDSPM_SyncRefMask) अणु
			हाल 0: वापस 0;  /* WC */
			हाल HDSPM_SyncRef0: वापस 1;  /* MADI */
			हाल HDSPM_SyncRef1: वापस 2;  /* TCO */
			हाल HDSPM_SyncRef1+HDSPM_SyncRef0:
					     वापस 3;  /* SYNC_IN */
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (hdspm->control_रेजिस्टर & HDSPM_SyncRefMask) अणु
			हाल 0: वापस 0;  /* WC */
			हाल HDSPM_SyncRef0: वापस 1;  /* MADI */
			हाल HDSPM_SyncRef1+HDSPM_SyncRef0:
					     वापस 2;  /* SYNC_IN */
			पूर्ण
		पूर्ण
		अवरोध;

	हाल RayDAT:
		अगर (hdspm->tco) अणु
			चयन ((hdspm->settings_रेजिस्टर &
				HDSPM_c0_SyncRefMask) / HDSPM_c0_SyncRef0) अणु
			हाल 0: वापस 0;  /* WC */
			हाल 3: वापस 1;  /* ADAT 1 */
			हाल 4: वापस 2;  /* ADAT 2 */
			हाल 5: वापस 3;  /* ADAT 3 */
			हाल 6: वापस 4;  /* ADAT 4 */
			हाल 1: वापस 5;  /* AES */
			हाल 2: वापस 6;  /* SPDIF */
			हाल 9: वापस 7;  /* TCO */
			हाल 10: वापस 8; /* SYNC_IN */
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन ((hdspm->settings_रेजिस्टर &
				HDSPM_c0_SyncRefMask) / HDSPM_c0_SyncRef0) अणु
			हाल 0: वापस 0;  /* WC */
			हाल 3: वापस 1;  /* ADAT 1 */
			हाल 4: वापस 2;  /* ADAT 2 */
			हाल 5: वापस 3;  /* ADAT 3 */
			हाल 6: वापस 4;  /* ADAT 4 */
			हाल 1: वापस 5;  /* AES */
			हाल 2: वापस 6;  /* SPDIF */
			हाल 10: वापस 7; /* SYNC_IN */
			पूर्ण
		पूर्ण

		अवरोध;

	हाल AIO:
		अगर (hdspm->tco) अणु
			चयन ((hdspm->settings_रेजिस्टर &
				HDSPM_c0_SyncRefMask) / HDSPM_c0_SyncRef0) अणु
			हाल 0: वापस 0;  /* WC */
			हाल 3: वापस 1;  /* ADAT */
			हाल 1: वापस 2;  /* AES */
			हाल 2: वापस 3;  /* SPDIF */
			हाल 9: वापस 4;  /* TCO */
			हाल 10: वापस 5; /* SYNC_IN */
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन ((hdspm->settings_रेजिस्टर &
				HDSPM_c0_SyncRefMask) / HDSPM_c0_SyncRef0) अणु
			हाल 0: वापस 0;  /* WC */
			हाल 3: वापस 1;  /* ADAT */
			हाल 1: वापस 2;  /* AES */
			हाल 2: वापस 3;  /* SPDIF */
			हाल 10: वापस 4; /* SYNC_IN */
			पूर्ण
		पूर्ण

		अवरोध;
	पूर्ण

	वापस -1;
पूर्ण


/*
 * Set the preferred sync reference to <pref>. The semantics
 * of <pref> are depending on the card type, see the comments
 * क्रम clarअगरication.
 */
अटल पूर्णांक hdspm_set_pref_sync_ref(काष्ठा hdspm * hdspm, पूर्णांक pref)
अणु
	पूर्णांक p = 0;

	चयन (hdspm->io_type) अणु
	हाल AES32:
		hdspm->control_रेजिस्टर &= ~HDSPM_SyncRefMask;
		चयन (pref) अणु
		हाल 0: /* WC  */
			अवरोध;
		हाल 1: /* AES 1 */
			hdspm->control_रेजिस्टर |= HDSPM_SyncRef0;
			अवरोध;
		हाल 2: /* AES 2 */
			hdspm->control_रेजिस्टर |= HDSPM_SyncRef1;
			अवरोध;
		हाल 3: /* AES 3 */
			hdspm->control_रेजिस्टर |=
				HDSPM_SyncRef1+HDSPM_SyncRef0;
			अवरोध;
		हाल 4: /* AES 4 */
			hdspm->control_रेजिस्टर |= HDSPM_SyncRef2;
			अवरोध;
		हाल 5: /* AES 5 */
			hdspm->control_रेजिस्टर |=
				HDSPM_SyncRef2+HDSPM_SyncRef0;
			अवरोध;
		हाल 6: /* AES 6 */
			hdspm->control_रेजिस्टर |=
				HDSPM_SyncRef2+HDSPM_SyncRef1;
			अवरोध;
		हाल 7: /* AES 7 */
			hdspm->control_रेजिस्टर |=
				HDSPM_SyncRef2+HDSPM_SyncRef1+HDSPM_SyncRef0;
			अवरोध;
		हाल 8: /* AES 8 */
			hdspm->control_रेजिस्टर |= HDSPM_SyncRef3;
			अवरोध;
		हाल 9: /* TCO */
			hdspm->control_रेजिस्टर |=
				HDSPM_SyncRef3+HDSPM_SyncRef0;
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण

		अवरोध;

	हाल MADI:
	हाल MADIface:
		hdspm->control_रेजिस्टर &= ~HDSPM_SyncRefMask;
		अगर (hdspm->tco) अणु
			चयन (pref) अणु
			हाल 0: /* WC */
				अवरोध;
			हाल 1: /* MADI */
				hdspm->control_रेजिस्टर |= HDSPM_SyncRef0;
				अवरोध;
			हाल 2: /* TCO */
				hdspm->control_रेजिस्टर |= HDSPM_SyncRef1;
				अवरोध;
			हाल 3: /* SYNC_IN */
				hdspm->control_रेजिस्टर |=
					HDSPM_SyncRef0+HDSPM_SyncRef1;
				अवरोध;
			शेष:
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (pref) अणु
			हाल 0: /* WC */
				अवरोध;
			हाल 1: /* MADI */
				hdspm->control_रेजिस्टर |= HDSPM_SyncRef0;
				अवरोध;
			हाल 2: /* SYNC_IN */
				hdspm->control_रेजिस्टर |=
					HDSPM_SyncRef0+HDSPM_SyncRef1;
				अवरोध;
			शेष:
				वापस -1;
			पूर्ण
		पूर्ण

		अवरोध;

	हाल RayDAT:
		अगर (hdspm->tco) अणु
			चयन (pref) अणु
			हाल 0: p = 0; अवरोध;  /* WC */
			हाल 1: p = 3; अवरोध;  /* ADAT 1 */
			हाल 2: p = 4; अवरोध;  /* ADAT 2 */
			हाल 3: p = 5; अवरोध;  /* ADAT 3 */
			हाल 4: p = 6; अवरोध;  /* ADAT 4 */
			हाल 5: p = 1; अवरोध;  /* AES */
			हाल 6: p = 2; अवरोध;  /* SPDIF */
			हाल 7: p = 9; अवरोध;  /* TCO */
			हाल 8: p = 10; अवरोध; /* SYNC_IN */
			शेष: वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (pref) अणु
			हाल 0: p = 0; अवरोध;  /* WC */
			हाल 1: p = 3; अवरोध;  /* ADAT 1 */
			हाल 2: p = 4; अवरोध;  /* ADAT 2 */
			हाल 3: p = 5; अवरोध;  /* ADAT 3 */
			हाल 4: p = 6; अवरोध;  /* ADAT 4 */
			हाल 5: p = 1; अवरोध;  /* AES */
			हाल 6: p = 2; अवरोध;  /* SPDIF */
			हाल 7: p = 10; अवरोध; /* SYNC_IN */
			शेष: वापस -1;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल AIO:
		अगर (hdspm->tco) अणु
			चयन (pref) अणु
			हाल 0: p = 0; अवरोध;  /* WC */
			हाल 1: p = 3; अवरोध;  /* ADAT */
			हाल 2: p = 1; अवरोध;  /* AES */
			हाल 3: p = 2; अवरोध;  /* SPDIF */
			हाल 4: p = 9; अवरोध;  /* TCO */
			हाल 5: p = 10; अवरोध; /* SYNC_IN */
			शेष: वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (pref) अणु
			हाल 0: p = 0; अवरोध;  /* WC */
			हाल 1: p = 3; अवरोध;  /* ADAT */
			हाल 2: p = 1; अवरोध;  /* AES */
			हाल 3: p = 2; अवरोध;  /* SPDIF */
			हाल 4: p = 10; अवरोध; /* SYNC_IN */
			शेष: वापस -1;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	चयन (hdspm->io_type) अणु
	हाल RayDAT:
	हाल AIO:
		hdspm->settings_रेजिस्टर &= ~HDSPM_c0_SyncRefMask;
		hdspm->settings_रेजिस्टर |= HDSPM_c0_SyncRef0 * p;
		hdspm_ग_लिखो(hdspm, HDSPM_WR_SETTINGS, hdspm->settings_रेजिस्टर);
		अवरोध;

	हाल MADI:
	हाल MADIface:
	हाल AES32:
		hdspm_ग_लिखो(hdspm, HDSPM_controlRegister,
				hdspm->control_रेजिस्टर);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdspm_info_pref_sync_ref(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	snd_ctl_क्रमागत_info(uinfo, 1, hdspm->texts_स्वतःsync_items, hdspm->texts_स्वतःsync);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_pref_sync_ref(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक psf = hdspm_pref_sync_ref(hdspm);

	अगर (psf >= 0) अणु
		ucontrol->value.क्रमागतerated.item[0] = psf;
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक snd_hdspm_put_pref_sync_ref(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक val, change = 0;

	अगर (!snd_hdspm_use_is_exclusive(hdspm))
		वापस -EBUSY;

	val = ucontrol->value.क्रमागतerated.item[0];

	अगर (val < 0)
		val = 0;
	अन्यथा अगर (val >= hdspm->texts_स्वतःsync_items)
		val = hdspm->texts_स्वतःsync_items-1;

	spin_lock_irq(&hdspm->lock);
	अगर (val != hdspm_pref_sync_ref(hdspm))
		change = (0 == hdspm_set_pref_sync_ref(hdspm, val)) ? 1 : 0;

	spin_unlock_irq(&hdspm->lock);
	वापस change;
पूर्ण


#घोषणा HDSPM_AUTOSYNC_REF(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READ, \
	.info = snd_hdspm_info_स्वतःsync_ref, \
	.get = snd_hdspm_get_स्वतःsync_ref, \
पूर्ण

अटल पूर्णांक hdspm_स्वतःsync_ref(काष्ठा hdspm *hdspm)
अणु
	/* This looks at the स्वतःsync selected sync reference */
	अगर (AES32 == hdspm->io_type) अणु

		अचिन्हित पूर्णांक status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
		अचिन्हित पूर्णांक syncref = (status >> HDSPM_AES32_syncref_bit) & 0xF;
		/* syncref >= HDSPM_AES32_AUTOSYNC_FROM_WORD is always true */
		अगर (syncref <= HDSPM_AES32_AUTOSYNC_FROM_SYNC_IN) अणु
			वापस syncref;
		पूर्ण
		वापस HDSPM_AES32_AUTOSYNC_FROM_NONE;

	पूर्ण अन्यथा अगर (MADI == hdspm->io_type) अणु

		अचिन्हित पूर्णांक status2 = hdspm_पढ़ो(hdspm, HDSPM_statusRegister2);
		चयन (status2 & HDSPM_SelSyncRefMask) अणु
		हाल HDSPM_SelSyncRef_WORD:
			वापस HDSPM_AUTOSYNC_FROM_WORD;
		हाल HDSPM_SelSyncRef_MADI:
			वापस HDSPM_AUTOSYNC_FROM_MADI;
		हाल HDSPM_SelSyncRef_TCO:
			वापस HDSPM_AUTOSYNC_FROM_TCO;
		हाल HDSPM_SelSyncRef_SyncIn:
			वापस HDSPM_AUTOSYNC_FROM_SYNC_IN;
		हाल HDSPM_SelSyncRef_NVALID:
			वापस HDSPM_AUTOSYNC_FROM_NONE;
		शेष:
			वापस HDSPM_AUTOSYNC_FROM_NONE;
		पूर्ण

	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdspm_info_स्वतःsync_ref(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	अगर (AES32 == hdspm->io_type) अणु
		अटल स्थिर अक्षर *स्थिर texts[] = अणु "WordClock", "AES1", "AES2", "AES3",
			"AES4",	"AES5", "AES6", "AES7", "AES8", "TCO", "Sync In", "None"पूर्ण;

		ENUMERATED_CTL_INFO(uinfo, texts);
	पूर्ण अन्यथा अगर (MADI == hdspm->io_type) अणु
		अटल स्थिर अक्षर *स्थिर texts[] = अणु"Word Clock", "MADI", "TCO",
			"Sync In", "None" पूर्ण;

		ENUMERATED_CTL_INFO(uinfo, texts);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_स्वतःsync_ref(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdspm_स्वतःsync_ref(hdspm);
	वापस 0;
पूर्ण



#घोषणा HDSPM_TCO_VIDEO_INPUT_FORMAT(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.access = SNDRV_CTL_ELEM_ACCESS_READ |\
		SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_tco_video_input_क्रमmat, \
	.get = snd_hdspm_get_tco_video_input_क्रमmat, \
पूर्ण

अटल पूर्णांक snd_hdspm_info_tco_video_input_क्रमmat(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु"No video", "NTSC", "PAL"पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_tco_video_input_क्रमmat(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	u32 status;
	पूर्णांक ret = 0;

	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	status = hdspm_पढ़ो(hdspm, HDSPM_RD_TCO + 4);
	चयन (status & (HDSPM_TCO1_Video_Input_Format_NTSC |
			HDSPM_TCO1_Video_Input_Format_PAL)) अणु
	हाल HDSPM_TCO1_Video_Input_Format_NTSC:
		/* ntsc */
		ret = 1;
		अवरोध;
	हाल HDSPM_TCO1_Video_Input_Format_PAL:
		/* pal */
		ret = 2;
		अवरोध;
	शेष:
		/* no video */
		ret = 0;
		अवरोध;
	पूर्ण
	ucontrol->value.क्रमागतerated.item[0] = ret;
	वापस 0;
पूर्ण



#घोषणा HDSPM_TCO_LTC_FRAMES(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.access = SNDRV_CTL_ELEM_ACCESS_READ |\
		SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_tco_ltc_frames, \
	.get = snd_hdspm_get_tco_ltc_frames, \
पूर्ण

अटल पूर्णांक snd_hdspm_info_tco_ltc_frames(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु"No lock", "24 fps", "25 fps", "29.97 fps",
				"30 fps"पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक hdspm_tco_ltc_frames(काष्ठा hdspm *hdspm)
अणु
	u32 status;
	पूर्णांक ret = 0;

	status = hdspm_पढ़ो(hdspm, HDSPM_RD_TCO + 4);
	अगर (status & HDSPM_TCO1_LTC_Input_valid) अणु
		चयन (status & (HDSPM_TCO1_LTC_Format_LSB |
					HDSPM_TCO1_LTC_Format_MSB)) अणु
		हाल 0:
			/* 24 fps */
			ret = fps_24;
			अवरोध;
		हाल HDSPM_TCO1_LTC_Format_LSB:
			/* 25 fps */
			ret = fps_25;
			अवरोध;
		हाल HDSPM_TCO1_LTC_Format_MSB:
			/* 29.97 fps */
			ret = fps_2997;
			अवरोध;
		शेष:
			/* 30 fps */
			ret = fps_30;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक snd_hdspm_get_tco_ltc_frames(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdspm_tco_ltc_frames(hdspm);
	वापस 0;
पूर्ण

#घोषणा HDSPM_TOGGLE_SETTING(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.निजी_value = xindex, \
	.info = snd_hdspm_info_toggle_setting, \
	.get = snd_hdspm_get_toggle_setting, \
	.put = snd_hdspm_put_toggle_setting \
पूर्ण

अटल पूर्णांक hdspm_toggle_setting(काष्ठा hdspm *hdspm, u32 regmask)
अणु
	u32 reg;

	अगर (hdspm_is_raydat_or_aio(hdspm))
		reg = hdspm->settings_रेजिस्टर;
	अन्यथा
		reg = hdspm->control_रेजिस्टर;

	वापस (reg & regmask) ? 1 : 0;
पूर्ण

अटल पूर्णांक hdspm_set_toggle_setting(काष्ठा hdspm *hdspm, u32 regmask, पूर्णांक out)
अणु
	u32 *reg;
	u32 target_reg;

	अगर (hdspm_is_raydat_or_aio(hdspm)) अणु
		reg = &(hdspm->settings_रेजिस्टर);
		target_reg = HDSPM_WR_SETTINGS;
	पूर्ण अन्यथा अणु
		reg = &(hdspm->control_रेजिस्टर);
		target_reg = HDSPM_controlRegister;
	पूर्ण

	अगर (out)
		*reg |= regmask;
	अन्यथा
		*reg &= ~regmask;

	hdspm_ग_लिखो(hdspm, target_reg, *reg);

	वापस 0;
पूर्ण

#घोषणा snd_hdspm_info_toggle_setting		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_hdspm_get_toggle_setting(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	u32 regmask = kcontrol->निजी_value;

	spin_lock_irq(&hdspm->lock);
	ucontrol->value.पूर्णांकeger.value[0] = hdspm_toggle_setting(hdspm, regmask);
	spin_unlock_irq(&hdspm->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_toggle_setting(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	u32 regmask = kcontrol->निजी_value;
	पूर्णांक change;
	अचिन्हित पूर्णांक val;

	अगर (!snd_hdspm_use_is_exclusive(hdspm))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0] & 1;
	spin_lock_irq(&hdspm->lock);
	change = (पूर्णांक) val != hdspm_toggle_setting(hdspm, regmask);
	hdspm_set_toggle_setting(hdspm, regmask, val);
	spin_unlock_irq(&hdspm->lock);
	वापस change;
पूर्ण

#घोषणा HDSPM_INPUT_SELECT(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.info = snd_hdspm_info_input_select, \
	.get = snd_hdspm_get_input_select, \
	.put = snd_hdspm_put_input_select \
पूर्ण

अटल पूर्णांक hdspm_input_select(काष्ठा hdspm * hdspm)
अणु
	वापस (hdspm->control_रेजिस्टर & HDSPM_InputSelect0) ? 1 : 0;
पूर्ण

अटल पूर्णांक hdspm_set_input_select(काष्ठा hdspm * hdspm, पूर्णांक out)
अणु
	अगर (out)
		hdspm->control_रेजिस्टर |= HDSPM_InputSelect0;
	अन्यथा
		hdspm->control_रेजिस्टर &= ~HDSPM_InputSelect0;
	hdspm_ग_लिखो(hdspm, HDSPM_controlRegister, hdspm->control_रेजिस्टर);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_info_input_select(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु "optical", "coaxial" पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_input_select(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&hdspm->lock);
	ucontrol->value.क्रमागतerated.item[0] = hdspm_input_select(hdspm);
	spin_unlock_irq(&hdspm->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_input_select(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;

	अगर (!snd_hdspm_use_is_exclusive(hdspm))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0] & 1;
	spin_lock_irq(&hdspm->lock);
	change = (पूर्णांक) val != hdspm_input_select(hdspm);
	hdspm_set_input_select(hdspm, val);
	spin_unlock_irq(&hdspm->lock);
	वापस change;
पूर्ण


#घोषणा HDSPM_DS_WIRE(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.info = snd_hdspm_info_ds_wire, \
	.get = snd_hdspm_get_ds_wire, \
	.put = snd_hdspm_put_ds_wire \
पूर्ण

अटल पूर्णांक hdspm_ds_wire(काष्ठा hdspm * hdspm)
अणु
	वापस (hdspm->control_रेजिस्टर & HDSPM_DS_DoubleWire) ? 1 : 0;
पूर्ण

अटल पूर्णांक hdspm_set_ds_wire(काष्ठा hdspm * hdspm, पूर्णांक ds)
अणु
	अगर (ds)
		hdspm->control_रेजिस्टर |= HDSPM_DS_DoubleWire;
	अन्यथा
		hdspm->control_रेजिस्टर &= ~HDSPM_DS_DoubleWire;
	hdspm_ग_लिखो(hdspm, HDSPM_controlRegister, hdspm->control_रेजिस्टर);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_info_ds_wire(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु "Single", "Double" पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_ds_wire(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&hdspm->lock);
	ucontrol->value.क्रमागतerated.item[0] = hdspm_ds_wire(hdspm);
	spin_unlock_irq(&hdspm->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_ds_wire(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	अचिन्हित पूर्णांक val;

	अगर (!snd_hdspm_use_is_exclusive(hdspm))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0] & 1;
	spin_lock_irq(&hdspm->lock);
	change = (पूर्णांक) val != hdspm_ds_wire(hdspm);
	hdspm_set_ds_wire(hdspm, val);
	spin_unlock_irq(&hdspm->lock);
	वापस change;
पूर्ण


#घोषणा HDSPM_QS_WIRE(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.info = snd_hdspm_info_qs_wire, \
	.get = snd_hdspm_get_qs_wire, \
	.put = snd_hdspm_put_qs_wire \
पूर्ण

अटल पूर्णांक hdspm_qs_wire(काष्ठा hdspm * hdspm)
अणु
	अगर (hdspm->control_रेजिस्टर & HDSPM_QS_DoubleWire)
		वापस 1;
	अगर (hdspm->control_रेजिस्टर & HDSPM_QS_QuadWire)
		वापस 2;
	वापस 0;
पूर्ण

अटल पूर्णांक hdspm_set_qs_wire(काष्ठा hdspm * hdspm, पूर्णांक mode)
अणु
	hdspm->control_रेजिस्टर &= ~(HDSPM_QS_DoubleWire | HDSPM_QS_QuadWire);
	चयन (mode) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		hdspm->control_रेजिस्टर |= HDSPM_QS_DoubleWire;
		अवरोध;
	हाल 2:
		hdspm->control_रेजिस्टर |= HDSPM_QS_QuadWire;
		अवरोध;
	पूर्ण
	hdspm_ग_लिखो(hdspm, HDSPM_controlRegister, hdspm->control_रेजिस्टर);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_info_qs_wire(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु "Single", "Double", "Quad" पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_qs_wire(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&hdspm->lock);
	ucontrol->value.क्रमागतerated.item[0] = hdspm_qs_wire(hdspm);
	spin_unlock_irq(&hdspm->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_qs_wire(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक val;

	अगर (!snd_hdspm_use_is_exclusive(hdspm))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (val < 0)
		val = 0;
	अगर (val > 2)
		val = 2;
	spin_lock_irq(&hdspm->lock);
	change = val != hdspm_qs_wire(hdspm);
	hdspm_set_qs_wire(hdspm, val);
	spin_unlock_irq(&hdspm->lock);
	वापस change;
पूर्ण

#घोषणा HDSPM_CONTROL_TRISTATE(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.निजी_value = xindex, \
	.info = snd_hdspm_info_tristate, \
	.get = snd_hdspm_get_tristate, \
	.put = snd_hdspm_put_tristate \
पूर्ण

अटल पूर्णांक hdspm_tristate(काष्ठा hdspm *hdspm, u32 regmask)
अणु
	u32 reg = hdspm->settings_रेजिस्टर & (regmask * 3);
	वापस reg / regmask;
पूर्ण

अटल पूर्णांक hdspm_set_tristate(काष्ठा hdspm *hdspm, पूर्णांक mode, u32 regmask)
अणु
	hdspm->settings_रेजिस्टर &= ~(regmask * 3);
	hdspm->settings_रेजिस्टर |= (regmask * mode);
	hdspm_ग_लिखो(hdspm, HDSPM_WR_SETTINGS, hdspm->settings_रेजिस्टर);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_info_tristate(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	u32 regmask = kcontrol->निजी_value;

	अटल स्थिर अक्षर *स्थिर texts_spdअगर[] = अणु "Optical", "Coaxial", "Internal" पूर्ण;
	अटल स्थिर अक्षर *स्थिर texts_levels[] = अणु "Hi Gain", "+4 dBu", "-10 dBV" पूर्ण;

	चयन (regmask) अणु
	हाल HDSPM_c0_Input0:
		ENUMERATED_CTL_INFO(uinfo, texts_spdअगर);
		अवरोध;
	शेष:
		ENUMERATED_CTL_INFO(uinfo, texts_levels);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_tristate(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	u32 regmask = kcontrol->निजी_value;

	spin_lock_irq(&hdspm->lock);
	ucontrol->value.क्रमागतerated.item[0] = hdspm_tristate(hdspm, regmask);
	spin_unlock_irq(&hdspm->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_tristate(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	u32 regmask = kcontrol->निजी_value;
	पूर्णांक change;
	पूर्णांक val;

	अगर (!snd_hdspm_use_is_exclusive(hdspm))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (val < 0)
		val = 0;
	अगर (val > 2)
		val = 2;

	spin_lock_irq(&hdspm->lock);
	change = val != hdspm_tristate(hdspm, regmask);
	hdspm_set_tristate(hdspm, val, regmask);
	spin_unlock_irq(&hdspm->lock);
	वापस change;
पूर्ण

#घोषणा HDSPM_MADI_SPEEDMODE(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.info = snd_hdspm_info_madi_speedmode, \
	.get = snd_hdspm_get_madi_speedmode, \
	.put = snd_hdspm_put_madi_speedmode \
पूर्ण

अटल पूर्णांक hdspm_madi_speedmode(काष्ठा hdspm *hdspm)
अणु
	अगर (hdspm->control_रेजिस्टर & HDSPM_QuadSpeed)
		वापस 2;
	अगर (hdspm->control_रेजिस्टर & HDSPM_DoubleSpeed)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक hdspm_set_madi_speedmode(काष्ठा hdspm *hdspm, पूर्णांक mode)
अणु
	hdspm->control_रेजिस्टर &= ~(HDSPM_DoubleSpeed | HDSPM_QuadSpeed);
	चयन (mode) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		hdspm->control_रेजिस्टर |= HDSPM_DoubleSpeed;
		अवरोध;
	हाल 2:
		hdspm->control_रेजिस्टर |= HDSPM_QuadSpeed;
		अवरोध;
	पूर्ण
	hdspm_ग_लिखो(hdspm, HDSPM_controlRegister, hdspm->control_रेजिस्टर);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_info_madi_speedmode(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु "Single", "Double", "Quad" पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_madi_speedmode(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&hdspm->lock);
	ucontrol->value.क्रमागतerated.item[0] = hdspm_madi_speedmode(hdspm);
	spin_unlock_irq(&hdspm->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_madi_speedmode(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक val;

	अगर (!snd_hdspm_use_is_exclusive(hdspm))
		वापस -EBUSY;
	val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (val < 0)
		val = 0;
	अगर (val > 2)
		val = 2;
	spin_lock_irq(&hdspm->lock);
	change = val != hdspm_madi_speedmode(hdspm);
	hdspm_set_madi_speedmode(hdspm, val);
	spin_unlock_irq(&hdspm->lock);
	वापस change;
पूर्ण

#घोषणा HDSPM_MIXER(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_HWDEP, \
	.name = xname, \
	.index = xindex, \
	.device = 0, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE | \
		SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_mixer, \
	.get = snd_hdspm_get_mixer, \
	.put = snd_hdspm_put_mixer \
पूर्ण

अटल पूर्णांक snd_hdspm_info_mixer(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 3;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 65535;
	uinfo->value.पूर्णांकeger.step = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_mixer(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक source;
	पूर्णांक destination;

	source = ucontrol->value.पूर्णांकeger.value[0];
	अगर (source < 0)
		source = 0;
	अन्यथा अगर (source >= 2 * HDSPM_MAX_CHANNELS)
		source = 2 * HDSPM_MAX_CHANNELS - 1;

	destination = ucontrol->value.पूर्णांकeger.value[1];
	अगर (destination < 0)
		destination = 0;
	अन्यथा अगर (destination >= HDSPM_MAX_CHANNELS)
		destination = HDSPM_MAX_CHANNELS - 1;

	spin_lock_irq(&hdspm->lock);
	अगर (source >= HDSPM_MAX_CHANNELS)
		ucontrol->value.पूर्णांकeger.value[2] =
		    hdspm_पढ़ो_pb_gain(hdspm, destination,
				       source - HDSPM_MAX_CHANNELS);
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[2] =
		    hdspm_पढ़ो_in_gain(hdspm, destination, source);

	spin_unlock_irq(&hdspm->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_mixer(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक source;
	पूर्णांक destination;
	पूर्णांक gain;

	अगर (!snd_hdspm_use_is_exclusive(hdspm))
		वापस -EBUSY;

	source = ucontrol->value.पूर्णांकeger.value[0];
	destination = ucontrol->value.पूर्णांकeger.value[1];

	अगर (source < 0 || source >= 2 * HDSPM_MAX_CHANNELS)
		वापस -1;
	अगर (destination < 0 || destination >= HDSPM_MAX_CHANNELS)
		वापस -1;

	gain = ucontrol->value.पूर्णांकeger.value[2];

	spin_lock_irq(&hdspm->lock);

	अगर (source >= HDSPM_MAX_CHANNELS)
		change = gain != hdspm_पढ़ो_pb_gain(hdspm, destination,
						    source -
						    HDSPM_MAX_CHANNELS);
	अन्यथा
		change = gain != hdspm_पढ़ो_in_gain(hdspm, destination,
						    source);

	अगर (change) अणु
		अगर (source >= HDSPM_MAX_CHANNELS)
			hdspm_ग_लिखो_pb_gain(hdspm, destination,
					    source - HDSPM_MAX_CHANNELS,
					    gain);
		अन्यथा
			hdspm_ग_लिखो_in_gain(hdspm, destination, source,
					    gain);
	पूर्ण
	spin_unlock_irq(&hdspm->lock);

	वापस change;
पूर्ण

/* The simple mixer control(s) provide gain control क्रम the
   basic 1:1 mappings of playback streams to output
   streams.
*/

#घोषणा HDSPM_PLAYBACK_MIXER \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_WRITE | \
		SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_playback_mixer, \
	.get = snd_hdspm_get_playback_mixer, \
	.put = snd_hdspm_put_playback_mixer \
पूर्ण

अटल पूर्णांक snd_hdspm_info_playback_mixer(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 64;
	uinfo->value.पूर्णांकeger.step = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_playback_mixer(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक channel;

	channel = ucontrol->id.index - 1;

	अगर (snd_BUG_ON(channel < 0 || channel >= HDSPM_MAX_CHANNELS))
		वापस -EINVAL;

	spin_lock_irq(&hdspm->lock);
	ucontrol->value.पूर्णांकeger.value[0] =
	  (hdspm_पढ़ो_pb_gain(hdspm, channel, channel)*64)/UNITY_GAIN;
	spin_unlock_irq(&hdspm->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_playback_mixer(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	पूर्णांक channel;
	पूर्णांक gain;

	अगर (!snd_hdspm_use_is_exclusive(hdspm))
		वापस -EBUSY;

	channel = ucontrol->id.index - 1;

	अगर (snd_BUG_ON(channel < 0 || channel >= HDSPM_MAX_CHANNELS))
		वापस -EINVAL;

	gain = ucontrol->value.पूर्णांकeger.value[0]*UNITY_GAIN/64;

	spin_lock_irq(&hdspm->lock);
	change =
	    gain != hdspm_पढ़ो_pb_gain(hdspm, channel,
				       channel);
	अगर (change)
		hdspm_ग_लिखो_pb_gain(hdspm, channel, channel,
				    gain);
	spin_unlock_irq(&hdspm->lock);
	वापस change;
पूर्ण

#घोषणा HDSPM_SYNC_CHECK(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.निजी_value = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_sync_check, \
	.get = snd_hdspm_get_sync_check \
पूर्ण

#घोषणा HDSPM_TCO_LOCK_CHECK(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.निजी_value = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_tco_info_lock_check, \
	.get = snd_hdspm_get_sync_check \
पूर्ण



अटल पूर्णांक snd_hdspm_info_sync_check(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु "No Lock", "Lock", "Sync", "N/A" पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_tco_info_lock_check(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु "No Lock", "Lock" पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक hdspm_wc_sync_check(काष्ठा hdspm *hdspm)
अणु
	पूर्णांक status, status2;

	चयन (hdspm->io_type) अणु
	हाल AES32:
		status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
		अगर (status & HDSPM_AES32_wcLock) अणु
			अगर (status & HDSPM_AES32_wcSync)
				वापस 2;
			अन्यथा
				वापस 1;
		पूर्ण
		वापस 0;

	हाल MADI:
		status2 = hdspm_पढ़ो(hdspm, HDSPM_statusRegister2);
		अगर (status2 & HDSPM_wcLock) अणु
			अगर (status2 & HDSPM_wcSync)
				वापस 2;
			अन्यथा
				वापस 1;
		पूर्ण
		वापस 0;

	हाल RayDAT:
	हाल AIO:
		status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);

		अगर (status & 0x2000000)
			वापस 2;
		अन्यथा अगर (status & 0x1000000)
			वापस 1;
		वापस 0;

	हाल MADIface:
		अवरोध;
	पूर्ण


	वापस 3;
पूर्ण


अटल पूर्णांक hdspm_madi_sync_check(काष्ठा hdspm *hdspm)
अणु
	पूर्णांक status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
	अगर (status & HDSPM_madiLock) अणु
		अगर (status & HDSPM_madiSync)
			वापस 2;
		अन्यथा
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक hdspm_s1_sync_check(काष्ठा hdspm *hdspm, पूर्णांक idx)
अणु
	पूर्णांक status, lock, sync;

	status = hdspm_पढ़ो(hdspm, HDSPM_RD_STATUS_1);

	lock = (status & (0x1<<idx)) ? 1 : 0;
	sync = (status & (0x100<<idx)) ? 1 : 0;

	अगर (lock && sync)
		वापस 2;
	अन्यथा अगर (lock)
		वापस 1;
	वापस 0;
पूर्ण


अटल पूर्णांक hdspm_sync_in_sync_check(काष्ठा hdspm *hdspm)
अणु
	पूर्णांक status, lock = 0, sync = 0;

	चयन (hdspm->io_type) अणु
	हाल RayDAT:
	हाल AIO:
		status = hdspm_पढ़ो(hdspm, HDSPM_RD_STATUS_3);
		lock = (status & 0x400) ? 1 : 0;
		sync = (status & 0x800) ? 1 : 0;
		अवरोध;

	हाल MADI:
		status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
		lock = (status & HDSPM_syncInLock) ? 1 : 0;
		sync = (status & HDSPM_syncInSync) ? 1 : 0;
		अवरोध;

	हाल AES32:
		status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister2);
		lock = (status & 0x100000) ? 1 : 0;
		sync = (status & 0x200000) ? 1 : 0;
		अवरोध;

	हाल MADIface:
		अवरोध;
	पूर्ण

	अगर (lock && sync)
		वापस 2;
	अन्यथा अगर (lock)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक hdspm_aes_sync_check(काष्ठा hdspm *hdspm, पूर्णांक idx)
अणु
	पूर्णांक status2, lock, sync;
	status2 = hdspm_पढ़ो(hdspm, HDSPM_statusRegister2);

	lock = (status2 & (0x0080 >> idx)) ? 1 : 0;
	sync = (status2 & (0x8000 >> idx)) ? 1 : 0;

	अगर (sync)
		वापस 2;
	अन्यथा अगर (lock)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक hdspm_tco_input_check(काष्ठा hdspm *hdspm, u32 mask)
अणु
	u32 status;
	status = hdspm_पढ़ो(hdspm, HDSPM_RD_TCO + 4);

	वापस (status & mask) ? 1 : 0;
पूर्ण


अटल पूर्णांक hdspm_tco_sync_check(काष्ठा hdspm *hdspm)
अणु
	पूर्णांक status;

	अगर (hdspm->tco) अणु
		चयन (hdspm->io_type) अणु
		हाल MADI:
			status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
			अगर (status & HDSPM_tcoLockMadi) अणु
				अगर (status & HDSPM_tcoSync)
					वापस 2;
				अन्यथा
					वापस 1;
			पूर्ण
			वापस 0;
		हाल AES32:
			status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
			अगर (status & HDSPM_tcoLockAes) अणु
				अगर (status & HDSPM_tcoSync)
					वापस 2;
				अन्यथा
					वापस 1;
			पूर्ण
			वापस 0;
		हाल RayDAT:
		हाल AIO:
			status = hdspm_पढ़ो(hdspm, HDSPM_RD_STATUS_1);

			अगर (status & 0x8000000)
				वापस 2; /* Sync */
			अगर (status & 0x4000000)
				वापस 1; /* Lock */
			वापस 0; /* No संकेत */

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 3; /* N/A */
पूर्ण


अटल पूर्णांक snd_hdspm_get_sync_check(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	पूर्णांक val = -1;

	चयन (hdspm->io_type) अणु
	हाल RayDAT:
		चयन (kcontrol->निजी_value) अणु
		हाल 0: /* WC */
			val = hdspm_wc_sync_check(hdspm); अवरोध;
		हाल 7: /* TCO */
			val = hdspm_tco_sync_check(hdspm); अवरोध;
		हाल 8: /* SYNC IN */
			val = hdspm_sync_in_sync_check(hdspm); अवरोध;
		शेष:
			val = hdspm_s1_sync_check(hdspm,
					kcontrol->निजी_value-1);
		पूर्ण
		अवरोध;

	हाल AIO:
		चयन (kcontrol->निजी_value) अणु
		हाल 0: /* WC */
			val = hdspm_wc_sync_check(hdspm); अवरोध;
		हाल 4: /* TCO */
			val = hdspm_tco_sync_check(hdspm); अवरोध;
		हाल 5: /* SYNC IN */
			val = hdspm_sync_in_sync_check(hdspm); अवरोध;
		शेष:
			val = hdspm_s1_sync_check(hdspm,
					kcontrol->निजी_value-1);
		पूर्ण
		अवरोध;

	हाल MADI:
		चयन (kcontrol->निजी_value) अणु
		हाल 0: /* WC */
			val = hdspm_wc_sync_check(hdspm); अवरोध;
		हाल 1: /* MADI */
			val = hdspm_madi_sync_check(hdspm); अवरोध;
		हाल 2: /* TCO */
			val = hdspm_tco_sync_check(hdspm); अवरोध;
		हाल 3: /* SYNC_IN */
			val = hdspm_sync_in_sync_check(hdspm); अवरोध;
		पूर्ण
		अवरोध;

	हाल MADIface:
		val = hdspm_madi_sync_check(hdspm); /* MADI */
		अवरोध;

	हाल AES32:
		चयन (kcontrol->निजी_value) अणु
		हाल 0: /* WC */
			val = hdspm_wc_sync_check(hdspm); अवरोध;
		हाल 9: /* TCO */
			val = hdspm_tco_sync_check(hdspm); अवरोध;
		हाल 10 /* SYNC IN */:
			val = hdspm_sync_in_sync_check(hdspm); अवरोध;
		शेष: /* AES1 to AES8 */
			 val = hdspm_aes_sync_check(hdspm,
					 kcontrol->निजी_value-1);
		पूर्ण
		अवरोध;

	पूर्ण

	अगर (hdspm->tco) अणु
		चयन (kcontrol->निजी_value) अणु
		हाल 11:
			/* Check TCO क्रम lock state of its current input */
			val = hdspm_tco_input_check(hdspm, HDSPM_TCO1_TCO_lock);
			अवरोध;
		हाल 12:
			/* Check TCO क्रम valid समय code on LTC input. */
			val = hdspm_tco_input_check(hdspm,
				HDSPM_TCO1_LTC_Input_valid);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (-1 == val)
		val = 3;

	ucontrol->value.क्रमागतerated.item[0] = val;
	वापस 0;
पूर्ण



/*
 * TCO controls
 */
अटल व्योम hdspm_tco_ग_लिखो(काष्ठा hdspm *hdspm)
अणु
	अचिन्हित पूर्णांक tc[4] = अणु 0, 0, 0, 0पूर्ण;

	चयन (hdspm->tco->input) अणु
	हाल 0:
		tc[2] |= HDSPM_TCO2_set_input_MSB;
		अवरोध;
	हाल 1:
		tc[2] |= HDSPM_TCO2_set_input_LSB;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (hdspm->tco->framerate) अणु
	हाल 1:
		tc[1] |= HDSPM_TCO1_LTC_Format_LSB;
		अवरोध;
	हाल 2:
		tc[1] |= HDSPM_TCO1_LTC_Format_MSB;
		अवरोध;
	हाल 3:
		tc[1] |= HDSPM_TCO1_LTC_Format_MSB +
			HDSPM_TCO1_set_drop_frame_flag;
		अवरोध;
	हाल 4:
		tc[1] |= HDSPM_TCO1_LTC_Format_LSB +
			HDSPM_TCO1_LTC_Format_MSB;
		अवरोध;
	हाल 5:
		tc[1] |= HDSPM_TCO1_LTC_Format_LSB +
			HDSPM_TCO1_LTC_Format_MSB +
			HDSPM_TCO1_set_drop_frame_flag;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (hdspm->tco->wordघड़ी) अणु
	हाल 1:
		tc[2] |= HDSPM_TCO2_WCK_IO_ratio_LSB;
		अवरोध;
	हाल 2:
		tc[2] |= HDSPM_TCO2_WCK_IO_ratio_MSB;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (hdspm->tco->samplerate) अणु
	हाल 1:
		tc[2] |= HDSPM_TCO2_set_freq;
		अवरोध;
	हाल 2:
		tc[2] |= HDSPM_TCO2_set_freq_from_app;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (hdspm->tco->pull) अणु
	हाल 1:
		tc[2] |= HDSPM_TCO2_set_pull_up;
		अवरोध;
	हाल 2:
		tc[2] |= HDSPM_TCO2_set_pull_करोwn;
		अवरोध;
	हाल 3:
		tc[2] |= HDSPM_TCO2_set_pull_up + HDSPM_TCO2_set_01_4;
		अवरोध;
	हाल 4:
		tc[2] |= HDSPM_TCO2_set_pull_करोwn + HDSPM_TCO2_set_01_4;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (1 == hdspm->tco->term) अणु
		tc[2] |= HDSPM_TCO2_set_term_75R;
	पूर्ण

	hdspm_ग_लिखो(hdspm, HDSPM_WR_TCO, tc[0]);
	hdspm_ग_लिखो(hdspm, HDSPM_WR_TCO+4, tc[1]);
	hdspm_ग_लिखो(hdspm, HDSPM_WR_TCO+8, tc[2]);
	hdspm_ग_लिखो(hdspm, HDSPM_WR_TCO+12, tc[3]);
पूर्ण


#घोषणा HDSPM_TCO_SAMPLE_RATE(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |\
		SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_tco_sample_rate, \
	.get = snd_hdspm_get_tco_sample_rate, \
	.put = snd_hdspm_put_tco_sample_rate \
पूर्ण

अटल पूर्णांक snd_hdspm_info_tco_sample_rate(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	/* TODO freq from app could be supported here, see tco->samplerate */
	अटल स्थिर अक्षर *स्थिर texts[] = अणु "44.1 kHz", "48 kHz" पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_tco_sample_rate(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdspm->tco->samplerate;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_tco_sample_rate(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	अगर (hdspm->tco->samplerate != ucontrol->value.क्रमागतerated.item[0]) अणु
		hdspm->tco->samplerate = ucontrol->value.क्रमागतerated.item[0];

		hdspm_tco_ग_लिखो(hdspm);

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण


#घोषणा HDSPM_TCO_PULL(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |\
		SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_tco_pull, \
	.get = snd_hdspm_get_tco_pull, \
	.put = snd_hdspm_put_tco_pull \
पूर्ण

अटल पूर्णांक snd_hdspm_info_tco_pull(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु "0", "+ 0.1 %", "- 0.1 %",
		"+ 4 %", "- 4 %" पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_tco_pull(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdspm->tco->pull;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_tco_pull(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	अगर (hdspm->tco->pull != ucontrol->value.क्रमागतerated.item[0]) अणु
		hdspm->tco->pull = ucontrol->value.क्रमागतerated.item[0];

		hdspm_tco_ग_लिखो(hdspm);

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा HDSPM_TCO_WCK_CONVERSION(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |\
			SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_tco_wck_conversion, \
	.get = snd_hdspm_get_tco_wck_conversion, \
	.put = snd_hdspm_put_tco_wck_conversion \
पूर्ण

अटल पूर्णांक snd_hdspm_info_tco_wck_conversion(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु "1:1", "44.1 -> 48", "48 -> 44.1" पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_tco_wck_conversion(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdspm->tco->wordघड़ी;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_tco_wck_conversion(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	अगर (hdspm->tco->wordघड़ी != ucontrol->value.क्रमागतerated.item[0]) अणु
		hdspm->tco->wordघड़ी = ucontrol->value.क्रमागतerated.item[0];

		hdspm_tco_ग_लिखो(hdspm);

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण


#घोषणा HDSPM_TCO_FRAME_RATE(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |\
			SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_tco_frame_rate, \
	.get = snd_hdspm_get_tco_frame_rate, \
	.put = snd_hdspm_put_tco_frame_rate \
पूर्ण

अटल पूर्णांक snd_hdspm_info_tco_frame_rate(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु "24 fps", "25 fps", "29.97fps",
		"29.97 dfps", "30 fps", "30 dfps" पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_tco_frame_rate(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdspm->tco->framerate;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_tco_frame_rate(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	अगर (hdspm->tco->framerate != ucontrol->value.क्रमागतerated.item[0]) अणु
		hdspm->tco->framerate = ucontrol->value.क्रमागतerated.item[0];

		hdspm_tco_ग_लिखो(hdspm);

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण


#घोषणा HDSPM_TCO_SYNC_SOURCE(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |\
			SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_tco_sync_source, \
	.get = snd_hdspm_get_tco_sync_source, \
	.put = snd_hdspm_put_tco_sync_source \
पूर्ण

अटल पूर्णांक snd_hdspm_info_tco_sync_source(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[] = अणु "LTC", "Video", "WCK" पूर्ण;
	ENUMERATED_CTL_INFO(uinfo, texts);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_get_tco_sync_source(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.क्रमागतerated.item[0] = hdspm->tco->input;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_put_tco_sync_source(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	अगर (hdspm->tco->input != ucontrol->value.क्रमागतerated.item[0]) अणु
		hdspm->tco->input = ucontrol->value.क्रमागतerated.item[0];

		hdspm_tco_ग_लिखो(hdspm);

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण


#घोषणा HDSPM_TCO_WORD_TERM(xname, xindex) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.index = xindex, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |\
			SNDRV_CTL_ELEM_ACCESS_VOLATILE, \
	.info = snd_hdspm_info_tco_word_term, \
	.get = snd_hdspm_get_tco_word_term, \
	.put = snd_hdspm_put_tco_word_term \
पूर्ण

अटल पूर्णांक snd_hdspm_info_tco_word_term(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;

	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdspm_get_tco_word_term(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = hdspm->tco->term;

	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdspm_put_tco_word_term(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hdspm *hdspm = snd_kcontrol_chip(kcontrol);

	अगर (hdspm->tco->term != ucontrol->value.पूर्णांकeger.value[0]) अणु
		hdspm->tco->term = ucontrol->value.पूर्णांकeger.value[0];

		hdspm_tco_ग_लिखो(hdspm);

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण




अटल स्थिर काष्ठा snd_kcontrol_new snd_hdspm_controls_madi[] = अणु
	HDSPM_MIXER("Mixer", 0),
	HDSPM_INTERNAL_CLOCK("Internal Clock", 0),
	HDSPM_SYSTEM_CLOCK_MODE("System Clock Mode", 0),
	HDSPM_PREF_SYNC_REF("Preferred Sync Reference", 0),
	HDSPM_AUTOSYNC_REF("AutoSync Reference", 0),
	HDSPM_SYSTEM_SAMPLE_RATE("System Sample Rate", 0),
	HDSPM_AUTOSYNC_SAMPLE_RATE("External Rate", 0),
	HDSPM_SYNC_CHECK("WC SyncCheck", 0),
	HDSPM_SYNC_CHECK("MADI SyncCheck", 1),
	HDSPM_SYNC_CHECK("TCO SyncCheck", 2),
	HDSPM_SYNC_CHECK("SYNC IN SyncCheck", 3),
	HDSPM_TOGGLE_SETTING("Line Out", HDSPM_LineOut),
	HDSPM_TOGGLE_SETTING("TX 64 channels mode", HDSPM_TX_64ch),
	HDSPM_TOGGLE_SETTING("Disable 96K frames", HDSPM_SMUX),
	HDSPM_TOGGLE_SETTING("Clear Track Marker", HDSPM_clr_पंचांगs),
	HDSPM_TOGGLE_SETTING("Safe Mode", HDSPM_AutoInp),
	HDSPM_INPUT_SELECT("Input Select", 0),
	HDSPM_MADI_SPEEDMODE("MADI Speed Mode", 0)
पूर्ण;


अटल स्थिर काष्ठा snd_kcontrol_new snd_hdspm_controls_madअगरace[] = अणु
	HDSPM_MIXER("Mixer", 0),
	HDSPM_INTERNAL_CLOCK("Internal Clock", 0),
	HDSPM_SYSTEM_CLOCK_MODE("System Clock Mode", 0),
	HDSPM_SYSTEM_SAMPLE_RATE("System Sample Rate", 0),
	HDSPM_AUTOSYNC_SAMPLE_RATE("External Rate", 0),
	HDSPM_SYNC_CHECK("MADI SyncCheck", 0),
	HDSPM_TOGGLE_SETTING("TX 64 channels mode", HDSPM_TX_64ch),
	HDSPM_TOGGLE_SETTING("Clear Track Marker", HDSPM_clr_पंचांगs),
	HDSPM_TOGGLE_SETTING("Safe Mode", HDSPM_AutoInp),
	HDSPM_MADI_SPEEDMODE("MADI Speed Mode", 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_hdspm_controls_aio[] = अणु
	HDSPM_MIXER("Mixer", 0),
	HDSPM_INTERNAL_CLOCK("Internal Clock", 0),
	HDSPM_SYSTEM_CLOCK_MODE("System Clock Mode", 0),
	HDSPM_PREF_SYNC_REF("Preferred Sync Reference", 0),
	HDSPM_SYSTEM_SAMPLE_RATE("System Sample Rate", 0),
	HDSPM_AUTOSYNC_SAMPLE_RATE("External Rate", 0),
	HDSPM_SYNC_CHECK("WC SyncCheck", 0),
	HDSPM_SYNC_CHECK("AES SyncCheck", 1),
	HDSPM_SYNC_CHECK("SPDIF SyncCheck", 2),
	HDSPM_SYNC_CHECK("ADAT SyncCheck", 3),
	HDSPM_SYNC_CHECK("TCO SyncCheck", 4),
	HDSPM_SYNC_CHECK("SYNC IN SyncCheck", 5),
	HDSPM_AUTOSYNC_SAMPLE_RATE("WC Frequency", 0),
	HDSPM_AUTOSYNC_SAMPLE_RATE("AES Frequency", 1),
	HDSPM_AUTOSYNC_SAMPLE_RATE("SPDIF Frequency", 2),
	HDSPM_AUTOSYNC_SAMPLE_RATE("ADAT Frequency", 3),
	HDSPM_AUTOSYNC_SAMPLE_RATE("TCO Frequency", 4),
	HDSPM_AUTOSYNC_SAMPLE_RATE("SYNC IN Frequency", 5),
	HDSPM_CONTROL_TRISTATE("S/PDIF Input", HDSPM_c0_Input0),
	HDSPM_TOGGLE_SETTING("S/PDIF Out Optical", HDSPM_c0_Spdअगर_Opt),
	HDSPM_TOGGLE_SETTING("S/PDIF Out Professional", HDSPM_c0_Pro),
	HDSPM_TOGGLE_SETTING("ADAT internal (AEB/TEB)", HDSPM_c0_AEB1),
	HDSPM_TOGGLE_SETTING("XLR Breakout Cable", HDSPM_c0_Sym6db),
	HDSPM_TOGGLE_SETTING("Single Speed WordClock Out", HDSPM_c0_Wck48),
	HDSPM_CONTROL_TRISTATE("Input Level", HDSPM_c0_AD_GAIN0),
	HDSPM_CONTROL_TRISTATE("Output Level", HDSPM_c0_DA_GAIN0),
	HDSPM_CONTROL_TRISTATE("Phones Level", HDSPM_c0_PH_GAIN0)

		/*
		   HDSPM_INPUT_SELECT("Input Select", 0),
		   HDSPM_SPDIF_OPTICAL("SPDIF Out Optical", 0),
		   HDSPM_PROFESSIONAL("SPDIF Out Professional", 0);
		   HDSPM_SPDIF_IN("SPDIF In", 0);
		   HDSPM_BREAKOUT_CABLE("Breakout Cable", 0);
		   HDSPM_INPUT_LEVEL("Input Level", 0);
		   HDSPM_OUTPUT_LEVEL("Output Level", 0);
		   HDSPM_PHONES("Phones", 0);
		   */
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_hdspm_controls_raydat[] = अणु
	HDSPM_MIXER("Mixer", 0),
	HDSPM_INTERNAL_CLOCK("Internal Clock", 0),
	HDSPM_SYSTEM_CLOCK_MODE("Clock Mode", 0),
	HDSPM_PREF_SYNC_REF("Pref Sync Ref", 0),
	HDSPM_SYSTEM_SAMPLE_RATE("System Sample Rate", 0),
	HDSPM_SYNC_CHECK("WC SyncCheck", 0),
	HDSPM_SYNC_CHECK("AES SyncCheck", 1),
	HDSPM_SYNC_CHECK("SPDIF SyncCheck", 2),
	HDSPM_SYNC_CHECK("ADAT1 SyncCheck", 3),
	HDSPM_SYNC_CHECK("ADAT2 SyncCheck", 4),
	HDSPM_SYNC_CHECK("ADAT3 SyncCheck", 5),
	HDSPM_SYNC_CHECK("ADAT4 SyncCheck", 6),
	HDSPM_SYNC_CHECK("TCO SyncCheck", 7),
	HDSPM_SYNC_CHECK("SYNC IN SyncCheck", 8),
	HDSPM_AUTOSYNC_SAMPLE_RATE("WC Frequency", 0),
	HDSPM_AUTOSYNC_SAMPLE_RATE("AES Frequency", 1),
	HDSPM_AUTOSYNC_SAMPLE_RATE("SPDIF Frequency", 2),
	HDSPM_AUTOSYNC_SAMPLE_RATE("ADAT1 Frequency", 3),
	HDSPM_AUTOSYNC_SAMPLE_RATE("ADAT2 Frequency", 4),
	HDSPM_AUTOSYNC_SAMPLE_RATE("ADAT3 Frequency", 5),
	HDSPM_AUTOSYNC_SAMPLE_RATE("ADAT4 Frequency", 6),
	HDSPM_AUTOSYNC_SAMPLE_RATE("TCO Frequency", 7),
	HDSPM_AUTOSYNC_SAMPLE_RATE("SYNC IN Frequency", 8),
	HDSPM_TOGGLE_SETTING("S/PDIF Out Professional", HDSPM_c0_Pro),
	HDSPM_TOGGLE_SETTING("Single Speed WordClock Out", HDSPM_c0_Wck48)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_hdspm_controls_aes32[] = अणु
	HDSPM_MIXER("Mixer", 0),
	HDSPM_INTERNAL_CLOCK("Internal Clock", 0),
	HDSPM_SYSTEM_CLOCK_MODE("System Clock Mode", 0),
	HDSPM_PREF_SYNC_REF("Preferred Sync Reference", 0),
	HDSPM_AUTOSYNC_REF("AutoSync Reference", 0),
	HDSPM_SYSTEM_SAMPLE_RATE("System Sample Rate", 0),
	HDSPM_AUTOSYNC_SAMPLE_RATE("External Rate", 11),
	HDSPM_SYNC_CHECK("WC Sync Check", 0),
	HDSPM_SYNC_CHECK("AES1 Sync Check", 1),
	HDSPM_SYNC_CHECK("AES2 Sync Check", 2),
	HDSPM_SYNC_CHECK("AES3 Sync Check", 3),
	HDSPM_SYNC_CHECK("AES4 Sync Check", 4),
	HDSPM_SYNC_CHECK("AES5 Sync Check", 5),
	HDSPM_SYNC_CHECK("AES6 Sync Check", 6),
	HDSPM_SYNC_CHECK("AES7 Sync Check", 7),
	HDSPM_SYNC_CHECK("AES8 Sync Check", 8),
	HDSPM_SYNC_CHECK("TCO Sync Check", 9),
	HDSPM_SYNC_CHECK("SYNC IN Sync Check", 10),
	HDSPM_AUTOSYNC_SAMPLE_RATE("WC Frequency", 0),
	HDSPM_AUTOSYNC_SAMPLE_RATE("AES1 Frequency", 1),
	HDSPM_AUTOSYNC_SAMPLE_RATE("AES2 Frequency", 2),
	HDSPM_AUTOSYNC_SAMPLE_RATE("AES3 Frequency", 3),
	HDSPM_AUTOSYNC_SAMPLE_RATE("AES4 Frequency", 4),
	HDSPM_AUTOSYNC_SAMPLE_RATE("AES5 Frequency", 5),
	HDSPM_AUTOSYNC_SAMPLE_RATE("AES6 Frequency", 6),
	HDSPM_AUTOSYNC_SAMPLE_RATE("AES7 Frequency", 7),
	HDSPM_AUTOSYNC_SAMPLE_RATE("AES8 Frequency", 8),
	HDSPM_AUTOSYNC_SAMPLE_RATE("TCO Frequency", 9),
	HDSPM_AUTOSYNC_SAMPLE_RATE("SYNC IN Frequency", 10),
	HDSPM_TOGGLE_SETTING("Line Out", HDSPM_LineOut),
	HDSPM_TOGGLE_SETTING("Emphasis", HDSPM_Emphasis),
	HDSPM_TOGGLE_SETTING("Non Audio", HDSPM_Dolby),
	HDSPM_TOGGLE_SETTING("Professional", HDSPM_Professional),
	HDSPM_TOGGLE_SETTING("Clear Track Marker", HDSPM_clr_पंचांगs),
	HDSPM_DS_WIRE("Double Speed Wire Mode", 0),
	HDSPM_QS_WIRE("Quad Speed Wire Mode", 0),
पूर्ण;



/* Control elements क्रम the optional TCO module */
अटल स्थिर काष्ठा snd_kcontrol_new snd_hdspm_controls_tco[] = अणु
	HDSPM_TCO_SAMPLE_RATE("TCO Sample Rate", 0),
	HDSPM_TCO_PULL("TCO Pull", 0),
	HDSPM_TCO_WCK_CONVERSION("TCO WCK Conversion", 0),
	HDSPM_TCO_FRAME_RATE("TCO Frame Rate", 0),
	HDSPM_TCO_SYNC_SOURCE("TCO Sync Source", 0),
	HDSPM_TCO_WORD_TERM("TCO Word Term", 0),
	HDSPM_TCO_LOCK_CHECK("TCO Input Check", 11),
	HDSPM_TCO_LOCK_CHECK("TCO LTC Valid", 12),
	HDSPM_TCO_LTC_FRAMES("TCO Detected Frame Rate", 0),
	HDSPM_TCO_VIDEO_INPUT_FORMAT("Video Input Format", 0)
पूर्ण;


अटल काष्ठा snd_kcontrol_new snd_hdspm_playback_mixer = HDSPM_PLAYBACK_MIXER;


अटल पूर्णांक hdspm_update_simple_mixer_controls(काष्ठा hdspm * hdspm)
अणु
	पूर्णांक i;

	क्रम (i = hdspm->ds_out_channels; i < hdspm->ss_out_channels; ++i) अणु
		अगर (hdspm->प्रणाली_sample_rate > 48000) अणु
			hdspm->playback_mixer_ctls[i]->vd[0].access =
				SNDRV_CTL_ELEM_ACCESS_INACTIVE |
				SNDRV_CTL_ELEM_ACCESS_READ |
				SNDRV_CTL_ELEM_ACCESS_VOLATILE;
		पूर्ण अन्यथा अणु
			hdspm->playback_mixer_ctls[i]->vd[0].access =
				SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_VOLATILE;
		पूर्ण
		snd_ctl_notअगरy(hdspm->card, SNDRV_CTL_EVENT_MASK_VALUE |
				SNDRV_CTL_EVENT_MASK_INFO,
				&hdspm->playback_mixer_ctls[i]->id);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdspm_create_controls(काष्ठा snd_card *card,
					काष्ठा hdspm *hdspm)
अणु
	अचिन्हित पूर्णांक idx, limit;
	पूर्णांक err;
	काष्ठा snd_kcontrol *kctl;
	स्थिर काष्ठा snd_kcontrol_new *list = शून्य;

	चयन (hdspm->io_type) अणु
	हाल MADI:
		list = snd_hdspm_controls_madi;
		limit = ARRAY_SIZE(snd_hdspm_controls_madi);
		अवरोध;
	हाल MADIface:
		list = snd_hdspm_controls_madअगरace;
		limit = ARRAY_SIZE(snd_hdspm_controls_madअगरace);
		अवरोध;
	हाल AIO:
		list = snd_hdspm_controls_aio;
		limit = ARRAY_SIZE(snd_hdspm_controls_aio);
		अवरोध;
	हाल RayDAT:
		list = snd_hdspm_controls_raydat;
		limit = ARRAY_SIZE(snd_hdspm_controls_raydat);
		अवरोध;
	हाल AES32:
		list = snd_hdspm_controls_aes32;
		limit = ARRAY_SIZE(snd_hdspm_controls_aes32);
		अवरोध;
	पूर्ण

	अगर (list) अणु
		क्रम (idx = 0; idx < limit; idx++) अणु
			err = snd_ctl_add(card,
					snd_ctl_new1(&list[idx], hdspm));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण


	/* create simple 1:1 playback mixer controls */
	snd_hdspm_playback_mixer.name = "Chn";
	अगर (hdspm->प्रणाली_sample_rate >= 128000) अणु
		limit = hdspm->qs_out_channels;
	पूर्ण अन्यथा अगर (hdspm->प्रणाली_sample_rate >= 64000) अणु
		limit = hdspm->ds_out_channels;
	पूर्ण अन्यथा अणु
		limit = hdspm->ss_out_channels;
	पूर्ण
	क्रम (idx = 0; idx < limit; ++idx) अणु
		snd_hdspm_playback_mixer.index = idx + 1;
		kctl = snd_ctl_new1(&snd_hdspm_playback_mixer, hdspm);
		err = snd_ctl_add(card, kctl);
		अगर (err < 0)
			वापस err;
		hdspm->playback_mixer_ctls[idx] = kctl;
	पूर्ण


	अगर (hdspm->tco) अणु
		/* add tco control elements */
		list = snd_hdspm_controls_tco;
		limit = ARRAY_SIZE(snd_hdspm_controls_tco);
		क्रम (idx = 0; idx < limit; idx++) अणु
			err = snd_ctl_add(card,
					snd_ctl_new1(&list[idx], hdspm));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*------------------------------------------------------------
   /proc पूर्णांकerface
 ------------------------------------------------------------*/

अटल व्योम
snd_hdspm_proc_पढ़ो_tco(काष्ठा snd_info_entry *entry,
					काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा hdspm *hdspm = entry->निजी_data;
	अचिन्हित पूर्णांक status, control;
	पूर्णांक a, ltc, frames, seconds, minutes, hours;
	अचिन्हित पूर्णांक period;
	u64 freq_स्थिर = 0;
	u32 rate;

	snd_iम_लिखो(buffer, "--- TCO ---\n");

	status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
	control = hdspm->control_रेजिस्टर;


	अगर (status & HDSPM_tco_detect) अणु
		snd_iम_लिखो(buffer, "TCO module detected.\n");
		a = hdspm_पढ़ो(hdspm, HDSPM_RD_TCO+4);
		अगर (a & HDSPM_TCO1_LTC_Input_valid) अणु
			snd_iम_लिखो(buffer, "  LTC valid, ");
			चयन (a & (HDSPM_TCO1_LTC_Format_LSB |
						HDSPM_TCO1_LTC_Format_MSB)) अणु
			हाल 0:
				snd_iम_लिखो(buffer, "24 fps, ");
				अवरोध;
			हाल HDSPM_TCO1_LTC_Format_LSB:
				snd_iम_लिखो(buffer, "25 fps, ");
				अवरोध;
			हाल HDSPM_TCO1_LTC_Format_MSB:
				snd_iम_लिखो(buffer, "29.97 fps, ");
				अवरोध;
			शेष:
				snd_iम_लिखो(buffer, "30 fps, ");
				अवरोध;
			पूर्ण
			अगर (a & HDSPM_TCO1_set_drop_frame_flag) अणु
				snd_iम_लिखो(buffer, "drop frame\n");
			पूर्ण अन्यथा अणु
				snd_iम_लिखो(buffer, "full frame\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "  no LTC\n");
		पूर्ण
		अगर (a & HDSPM_TCO1_Video_Input_Format_NTSC) अणु
			snd_iम_लिखो(buffer, "  Video: NTSC\n");
		पूर्ण अन्यथा अगर (a & HDSPM_TCO1_Video_Input_Format_PAL) अणु
			snd_iम_लिखो(buffer, "  Video: PAL\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "  No video\n");
		पूर्ण
		अगर (a & HDSPM_TCO1_TCO_lock) अणु
			snd_iम_लिखो(buffer, "  Sync: lock\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, "  Sync: no lock\n");
		पूर्ण

		चयन (hdspm->io_type) अणु
		हाल MADI:
		हाल AES32:
			freq_स्थिर = 110069313433624ULL;
			अवरोध;
		हाल RayDAT:
		हाल AIO:
			freq_स्थिर = 104857600000000ULL;
			अवरोध;
		हाल MADIface:
			अवरोध; /* no TCO possible */
		पूर्ण

		period = hdspm_पढ़ो(hdspm, HDSPM_RD_PLL_FREQ);
		snd_iम_लिखो(buffer, "    period: %u\n", period);


		/* rate = freq_स्थिर/period; */
		rate = भाग_u64(freq_स्थिर, period);

		अगर (control & HDSPM_QuadSpeed) अणु
			rate *= 4;
		पूर्ण अन्यथा अगर (control & HDSPM_DoubleSpeed) अणु
			rate *= 2;
		पूर्ण

		snd_iम_लिखो(buffer, "  Frequency: %u Hz\n",
				(अचिन्हित पूर्णांक) rate);

		ltc = hdspm_पढ़ो(hdspm, HDSPM_RD_TCO);
		frames = ltc & 0xF;
		ltc >>= 4;
		frames += (ltc & 0x3) * 10;
		ltc >>= 4;
		seconds = ltc & 0xF;
		ltc >>= 4;
		seconds += (ltc & 0x7) * 10;
		ltc >>= 4;
		minutes = ltc & 0xF;
		ltc >>= 4;
		minutes += (ltc & 0x7) * 10;
		ltc >>= 4;
		hours = ltc & 0xF;
		ltc >>= 4;
		hours += (ltc & 0x3) * 10;
		snd_iम_लिखो(buffer,
			"  LTC In: %02d:%02d:%02d:%02d\n",
			hours, minutes, seconds, frames);

	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "No TCO module detected.\n");
	पूर्ण
पूर्ण

अटल व्योम
snd_hdspm_proc_पढ़ो_madi(काष्ठा snd_info_entry *entry,
			 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा hdspm *hdspm = entry->निजी_data;
	अचिन्हित पूर्णांक status, status2;

	अक्षर *pref_sync_ref;
	अक्षर *स्वतःsync_ref;
	अक्षर *प्रणाली_घड़ी_mode;
	पूर्णांक x, x2;

	status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
	status2 = hdspm_पढ़ो(hdspm, HDSPM_statusRegister2);

	snd_iम_लिखो(buffer, "%s (Card #%d) Rev.%x Status2first3bits: %x\n",
			hdspm->card_name, hdspm->card->number + 1,
			hdspm->firmware_rev,
			(status2 & HDSPM_version0) |
			(status2 & HDSPM_version1) | (status2 &
				HDSPM_version2));

	snd_iम_लिखो(buffer, "HW Serial: 0x%06x%06x\n",
			(hdspm_पढ़ो(hdspm, HDSPM_midiStatusIn1)>>8) & 0xFFFFFF,
			hdspm->serial);

	snd_iम_लिखो(buffer, "IRQ: %d Registers bus: 0x%lx VM: 0x%lx\n",
			hdspm->irq, hdspm->port, (अचिन्हित दीर्घ)hdspm->iobase);

	snd_iम_लिखो(buffer, "--- System ---\n");

	snd_iम_लिखो(buffer,
		"IRQ Pending: Audio=%d, MIDI0=%d, MIDI1=%d, IRQcount=%d\n",
		status & HDSPM_audioIRQPending,
		(status & HDSPM_midi0IRQPending) ? 1 : 0,
		(status & HDSPM_midi1IRQPending) ? 1 : 0,
		hdspm->irq_count);
	snd_iम_लिखो(buffer,
		"HW pointer: id = %d, rawptr = %d (%d->%d) "
		"estimated= %ld (bytes)\n",
		((status & HDSPM_BufferID) ? 1 : 0),
		(status & HDSPM_BufferPositionMask),
		(status & HDSPM_BufferPositionMask) %
		(2 * (पूर्णांक)hdspm->period_bytes),
		((status & HDSPM_BufferPositionMask) - 64) %
		(2 * (पूर्णांक)hdspm->period_bytes),
		(दीर्घ) hdspm_hw_poपूर्णांकer(hdspm) * 4);

	snd_iम_लिखो(buffer,
		"MIDI FIFO: Out1=0x%x, Out2=0x%x, In1=0x%x, In2=0x%x \n",
		hdspm_पढ़ो(hdspm, HDSPM_midiStatusOut0) & 0xFF,
		hdspm_पढ़ो(hdspm, HDSPM_midiStatusOut1) & 0xFF,
		hdspm_पढ़ो(hdspm, HDSPM_midiStatusIn0) & 0xFF,
		hdspm_पढ़ो(hdspm, HDSPM_midiStatusIn1) & 0xFF);
	snd_iम_लिखो(buffer,
		"MIDIoverMADI FIFO: In=0x%x, Out=0x%x \n",
		hdspm_पढ़ो(hdspm, HDSPM_midiStatusIn2) & 0xFF,
		hdspm_पढ़ो(hdspm, HDSPM_midiStatusOut2) & 0xFF);
	snd_iम_लिखो(buffer,
		"Register: ctrl1=0x%x, ctrl2=0x%x, status1=0x%x, "
		"status2=0x%x\n",
		hdspm->control_रेजिस्टर, hdspm->control2_रेजिस्टर,
		status, status2);


	snd_iम_लिखो(buffer, "--- Settings ---\n");

	x = hdspm_get_latency(hdspm);

	snd_iम_लिखो(buffer,
		"Size (Latency): %d samples (2 periods of %lu bytes)\n",
		x, (अचिन्हित दीर्घ) hdspm->period_bytes);

	snd_iम_लिखो(buffer, "Line out: %s\n",
		(hdspm->control_रेजिस्टर & HDSPM_LineOut) ? "on " : "off");

	snd_iम_लिखो(buffer,
		"ClearTrackMarker = %s, Transmit in %s Channel Mode, "
		"Auto Input %s\n",
		(hdspm->control_रेजिस्टर & HDSPM_clr_पंचांगs) ? "on" : "off",
		(hdspm->control_रेजिस्टर & HDSPM_TX_64ch) ? "64" : "56",
		(hdspm->control_रेजिस्टर & HDSPM_AutoInp) ? "on" : "off");


	अगर (!(hdspm->control_रेजिस्टर & HDSPM_ClockModeMaster))
		प्रणाली_घड़ी_mode = "AutoSync";
	अन्यथा
		प्रणाली_घड़ी_mode = "Master";
	snd_iम_लिखो(buffer, "AutoSync Reference: %s\n", प्रणाली_घड़ी_mode);

	चयन (hdspm_pref_sync_ref(hdspm)) अणु
	हाल HDSPM_SYNC_FROM_WORD:
		pref_sync_ref = "Word Clock";
		अवरोध;
	हाल HDSPM_SYNC_FROM_MADI:
		pref_sync_ref = "MADI Sync";
		अवरोध;
	हाल HDSPM_SYNC_FROM_TCO:
		pref_sync_ref = "TCO";
		अवरोध;
	हाल HDSPM_SYNC_FROM_SYNC_IN:
		pref_sync_ref = "Sync In";
		अवरोध;
	शेष:
		pref_sync_ref = "XXXX Clock";
		अवरोध;
	पूर्ण
	snd_iम_लिखो(buffer, "Preferred Sync Reference: %s\n",
			pref_sync_ref);

	snd_iम_लिखो(buffer, "System Clock Frequency: %d\n",
			hdspm->प्रणाली_sample_rate);


	snd_iम_लिखो(buffer, "--- Status:\n");

	x = status & HDSPM_madiSync;
	x2 = status2 & HDSPM_wcSync;

	snd_iम_लिखो(buffer, "Inputs MADI=%s, WordClock=%s\n",
			(status & HDSPM_madiLock) ? (x ? "Sync" : "Lock") :
			"NoLock",
			(status2 & HDSPM_wcLock) ? (x2 ? "Sync" : "Lock") :
			"NoLock");

	चयन (hdspm_स्वतःsync_ref(hdspm)) अणु
	हाल HDSPM_AUTOSYNC_FROM_SYNC_IN:
		स्वतःsync_ref = "Sync In";
		अवरोध;
	हाल HDSPM_AUTOSYNC_FROM_TCO:
		स्वतःsync_ref = "TCO";
		अवरोध;
	हाल HDSPM_AUTOSYNC_FROM_WORD:
		स्वतःsync_ref = "Word Clock";
		अवरोध;
	हाल HDSPM_AUTOSYNC_FROM_MADI:
		स्वतःsync_ref = "MADI Sync";
		अवरोध;
	हाल HDSPM_AUTOSYNC_FROM_NONE:
		स्वतःsync_ref = "Input not valid";
		अवरोध;
	शेष:
		स्वतःsync_ref = "---";
		अवरोध;
	पूर्ण
	snd_iम_लिखो(buffer,
		"AutoSync: Reference= %s, Freq=%d (MADI = %d, Word = %d)\n",
		स्वतःsync_ref, hdspm_बाह्यal_sample_rate(hdspm),
		(status & HDSPM_madiFreqMask) >> 22,
		(status2 & HDSPM_wcFreqMask) >> 5);

	snd_iम_लिखो(buffer, "Input: %s, Mode=%s\n",
		(status & HDSPM_AB_पूर्णांक) ? "Coax" : "Optical",
		(status & HDSPM_RX_64ch) ? "64 channels" :
		"56 channels");

	/* call पढ़ोout function क्रम TCO specअगरic status */
	snd_hdspm_proc_पढ़ो_tco(entry, buffer);

	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम
snd_hdspm_proc_पढ़ो_aes32(काष्ठा snd_info_entry * entry,
			  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा hdspm *hdspm = entry->निजी_data;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक status2;
	अचिन्हित पूर्णांक समयcode;
	अचिन्हित पूर्णांक wcLock, wcSync;
	पूर्णांक pref_syncref;
	अक्षर *स्वतःsync_ref;
	पूर्णांक x;

	status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
	status2 = hdspm_पढ़ो(hdspm, HDSPM_statusRegister2);
	समयcode = hdspm_पढ़ो(hdspm, HDSPM_समयcodeRegister);

	snd_iम_लिखो(buffer, "%s (Card #%d) Rev.%x\n",
		    hdspm->card_name, hdspm->card->number + 1,
		    hdspm->firmware_rev);

	snd_iम_लिखो(buffer, "IRQ: %d Registers bus: 0x%lx VM: 0x%lx\n",
		    hdspm->irq, hdspm->port, (अचिन्हित दीर्घ)hdspm->iobase);

	snd_iम_लिखो(buffer, "--- System ---\n");

	snd_iम_लिखो(buffer,
		    "IRQ Pending: Audio=%d, MIDI0=%d, MIDI1=%d, IRQcount=%d\n",
		    status & HDSPM_audioIRQPending,
		    (status & HDSPM_midi0IRQPending) ? 1 : 0,
		    (status & HDSPM_midi1IRQPending) ? 1 : 0,
		    hdspm->irq_count);
	snd_iम_लिखो(buffer,
		    "HW pointer: id = %d, rawptr = %d (%d->%d) "
		    "estimated= %ld (bytes)\n",
		    ((status & HDSPM_BufferID) ? 1 : 0),
		    (status & HDSPM_BufferPositionMask),
		    (status & HDSPM_BufferPositionMask) %
		    (2 * (पूर्णांक)hdspm->period_bytes),
		    ((status & HDSPM_BufferPositionMask) - 64) %
		    (2 * (पूर्णांक)hdspm->period_bytes),
		    (दीर्घ) hdspm_hw_poपूर्णांकer(hdspm) * 4);

	snd_iम_लिखो(buffer,
		    "MIDI FIFO: Out1=0x%x, Out2=0x%x, In1=0x%x, In2=0x%x \n",
		    hdspm_पढ़ो(hdspm, HDSPM_midiStatusOut0) & 0xFF,
		    hdspm_पढ़ो(hdspm, HDSPM_midiStatusOut1) & 0xFF,
		    hdspm_पढ़ो(hdspm, HDSPM_midiStatusIn0) & 0xFF,
		    hdspm_पढ़ो(hdspm, HDSPM_midiStatusIn1) & 0xFF);
	snd_iम_लिखो(buffer,
		    "MIDIoverMADI FIFO: In=0x%x, Out=0x%x \n",
		    hdspm_पढ़ो(hdspm, HDSPM_midiStatusIn2) & 0xFF,
		    hdspm_पढ़ो(hdspm, HDSPM_midiStatusOut2) & 0xFF);
	snd_iम_लिखो(buffer,
		    "Register: ctrl1=0x%x, ctrl2=0x%x, status1=0x%x, "
		    "status2=0x%x\n",
		    hdspm->control_रेजिस्टर, hdspm->control2_रेजिस्टर,
		    status, status2);

	snd_iम_लिखो(buffer, "--- Settings ---\n");

	x = hdspm_get_latency(hdspm);

	snd_iम_लिखो(buffer,
		    "Size (Latency): %d samples (2 periods of %lu bytes)\n",
		    x, (अचिन्हित दीर्घ) hdspm->period_bytes);

	snd_iम_लिखो(buffer, "Line out: %s\n",
		    (hdspm->
		     control_रेजिस्टर & HDSPM_LineOut) ? "on " : "off");

	snd_iम_लिखो(buffer,
		    "ClearTrackMarker %s, Emphasis %s, Dolby %s\n",
		    (hdspm->
		     control_रेजिस्टर & HDSPM_clr_पंचांगs) ? "on" : "off",
		    (hdspm->
		     control_रेजिस्टर & HDSPM_Emphasis) ? "on" : "off",
		    (hdspm->
		     control_रेजिस्टर & HDSPM_Dolby) ? "on" : "off");


	pref_syncref = hdspm_pref_sync_ref(hdspm);
	अगर (pref_syncref == 0)
		snd_iम_लिखो(buffer, "Preferred Sync Reference: Word Clock\n");
	अन्यथा
		snd_iम_लिखो(buffer, "Preferred Sync Reference: AES%d\n",
				pref_syncref);

	snd_iम_लिखो(buffer, "System Clock Frequency: %d\n",
		    hdspm->प्रणाली_sample_rate);

	snd_iम_लिखो(buffer, "Double speed: %s\n",
			hdspm->control_रेजिस्टर & HDSPM_DS_DoubleWire?
			"Double wire" : "Single wire");
	snd_iम_लिखो(buffer, "Quad speed: %s\n",
			hdspm->control_रेजिस्टर & HDSPM_QS_DoubleWire?
			"Double wire" :
			hdspm->control_रेजिस्टर & HDSPM_QS_QuadWire?
			"Quad wire" : "Single wire");

	snd_iम_लिखो(buffer, "--- Status:\n");

	wcLock = status & HDSPM_AES32_wcLock;
	wcSync = wcLock && (status & HDSPM_AES32_wcSync);

	snd_iम_लिखो(buffer, "Word: %s  Frequency: %d\n",
		    (wcLock) ? (wcSync ? "Sync   " : "Lock   ") : "No Lock",
		    HDSPM_bit2freq((status >> HDSPM_AES32_wcFreq_bit) & 0xF));

	क्रम (x = 0; x < 8; x++) अणु
		snd_iम_लिखो(buffer, "AES%d: %s  Frequency: %d\n",
			    x+1,
			    (status2 & (HDSPM_LockAES >> x)) ?
			    "Sync   " : "No Lock",
			    HDSPM_bit2freq((समयcode >> (4*x)) & 0xF));
	पूर्ण

	चयन (hdspm_स्वतःsync_ref(hdspm)) अणु
	हाल HDSPM_AES32_AUTOSYNC_FROM_NONE:
		स्वतःsync_ref = "None"; अवरोध;
	हाल HDSPM_AES32_AUTOSYNC_FROM_WORD:
		स्वतःsync_ref = "Word Clock"; अवरोध;
	हाल HDSPM_AES32_AUTOSYNC_FROM_AES1:
		स्वतःsync_ref = "AES1"; अवरोध;
	हाल HDSPM_AES32_AUTOSYNC_FROM_AES2:
		स्वतःsync_ref = "AES2"; अवरोध;
	हाल HDSPM_AES32_AUTOSYNC_FROM_AES3:
		स्वतःsync_ref = "AES3"; अवरोध;
	हाल HDSPM_AES32_AUTOSYNC_FROM_AES4:
		स्वतःsync_ref = "AES4"; अवरोध;
	हाल HDSPM_AES32_AUTOSYNC_FROM_AES5:
		स्वतःsync_ref = "AES5"; अवरोध;
	हाल HDSPM_AES32_AUTOSYNC_FROM_AES6:
		स्वतःsync_ref = "AES6"; अवरोध;
	हाल HDSPM_AES32_AUTOSYNC_FROM_AES7:
		स्वतःsync_ref = "AES7"; अवरोध;
	हाल HDSPM_AES32_AUTOSYNC_FROM_AES8:
		स्वतःsync_ref = "AES8"; अवरोध;
	हाल HDSPM_AES32_AUTOSYNC_FROM_TCO:
		स्वतःsync_ref = "TCO"; अवरोध;
	हाल HDSPM_AES32_AUTOSYNC_FROM_SYNC_IN:
		स्वतःsync_ref = "Sync In"; अवरोध;
	शेष:
		स्वतःsync_ref = "---"; अवरोध;
	पूर्ण
	snd_iम_लिखो(buffer, "AutoSync ref = %s\n", स्वतःsync_ref);

	/* call पढ़ोout function क्रम TCO specअगरic status */
	snd_hdspm_proc_पढ़ो_tco(entry, buffer);

	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम
snd_hdspm_proc_पढ़ो_raydat(काष्ठा snd_info_entry *entry,
			 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा hdspm *hdspm = entry->निजी_data;
	अचिन्हित पूर्णांक status1, status2, status3, i;
	अचिन्हित पूर्णांक lock, sync;

	status1 = hdspm_पढ़ो(hdspm, HDSPM_RD_STATUS_1); /* s1 */
	status2 = hdspm_पढ़ो(hdspm, HDSPM_RD_STATUS_2); /* freq */
	status3 = hdspm_पढ़ो(hdspm, HDSPM_RD_STATUS_3); /* s2 */

	snd_iम_लिखो(buffer, "STATUS1: 0x%08x\n", status1);
	snd_iम_लिखो(buffer, "STATUS2: 0x%08x\n", status2);
	snd_iम_लिखो(buffer, "STATUS3: 0x%08x\n", status3);


	snd_iम_लिखो(buffer, "\n*** CLOCK MODE\n\n");

	snd_iम_लिखो(buffer, "Clock mode      : %s\n",
		(hdspm_प्रणाली_घड़ी_mode(hdspm) == 0) ? "master" : "slave");
	snd_iम_लिखो(buffer, "System frequency: %d Hz\n",
		hdspm_get_प्रणाली_sample_rate(hdspm));

	snd_iम_लिखो(buffer, "\n*** INPUT STATUS\n\n");

	lock = 0x1;
	sync = 0x100;

	क्रम (i = 0; i < 8; i++) अणु
		snd_iम_लिखो(buffer, "s1_input %d: Lock %d, Sync %d, Freq %s\n",
				i,
				(status1 & lock) ? 1 : 0,
				(status1 & sync) ? 1 : 0,
				texts_freq[(status2 >> (i * 4)) & 0xF]);

		lock = lock<<1;
		sync = sync<<1;
	पूर्ण

	snd_iम_लिखो(buffer, "WC input: Lock %d, Sync %d, Freq %s\n",
			(status1 & 0x1000000) ? 1 : 0,
			(status1 & 0x2000000) ? 1 : 0,
			texts_freq[(status1 >> 16) & 0xF]);

	snd_iम_लिखो(buffer, "TCO input: Lock %d, Sync %d, Freq %s\n",
			(status1 & 0x4000000) ? 1 : 0,
			(status1 & 0x8000000) ? 1 : 0,
			texts_freq[(status1 >> 20) & 0xF]);

	snd_iम_लिखो(buffer, "SYNC IN: Lock %d, Sync %d, Freq %s\n",
			(status3 & 0x400) ? 1 : 0,
			(status3 & 0x800) ? 1 : 0,
			texts_freq[(status2 >> 12) & 0xF]);

पूर्ण

#अगर_घोषित CONFIG_SND_DEBUG
अटल व्योम
snd_hdspm_proc_पढ़ो_debug(काष्ठा snd_info_entry *entry,
			  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा hdspm *hdspm = entry->निजी_data;

	पूर्णांक j,i;

	क्रम (i = 0; i < 256 /* 1024*64 */; i += j) अणु
		snd_iम_लिखो(buffer, "0x%08X: ", i);
		क्रम (j = 0; j < 16; j += 4)
			snd_iम_लिखो(buffer, "%08X ", hdspm_पढ़ो(hdspm, i + j));
		snd_iम_लिखो(buffer, "\n");
	पूर्ण
पूर्ण
#पूर्ण_अगर


अटल व्योम snd_hdspm_proc_ports_in(काष्ठा snd_info_entry *entry,
			  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा hdspm *hdspm = entry->निजी_data;
	पूर्णांक i;

	snd_iम_लिखो(buffer, "# generated by hdspm\n");

	क्रम (i = 0; i < hdspm->max_channels_in; i++) अणु
		snd_iम_लिखो(buffer, "%d=%s\n", i+1, hdspm->port_names_in[i]);
	पूर्ण
पूर्ण

अटल व्योम snd_hdspm_proc_ports_out(काष्ठा snd_info_entry *entry,
			  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा hdspm *hdspm = entry->निजी_data;
	पूर्णांक i;

	snd_iम_लिखो(buffer, "# generated by hdspm\n");

	क्रम (i = 0; i < hdspm->max_channels_out; i++) अणु
		snd_iम_लिखो(buffer, "%d=%s\n", i+1, hdspm->port_names_out[i]);
	पूर्ण
पूर्ण


अटल व्योम snd_hdspm_proc_init(काष्ठा hdspm *hdspm)
अणु
	व्योम (*पढ़ो)(काष्ठा snd_info_entry *, काष्ठा snd_info_buffer *) = शून्य;

	चयन (hdspm->io_type) अणु
	हाल AES32:
		पढ़ो = snd_hdspm_proc_पढ़ो_aes32;
		अवरोध;
	हाल MADI:
		पढ़ो = snd_hdspm_proc_पढ़ो_madi;
		अवरोध;
	हाल MADIface:
		/* पढ़ो = snd_hdspm_proc_पढ़ो_madअगरace; */
		अवरोध;
	हाल RayDAT:
		पढ़ो = snd_hdspm_proc_पढ़ो_raydat;
		अवरोध;
	हाल AIO:
		अवरोध;
	पूर्ण

	snd_card_ro_proc_new(hdspm->card, "hdspm", hdspm, पढ़ो);
	snd_card_ro_proc_new(hdspm->card, "ports.in", hdspm,
			     snd_hdspm_proc_ports_in);
	snd_card_ro_proc_new(hdspm->card, "ports.out", hdspm,
			     snd_hdspm_proc_ports_out);

#अगर_घोषित CONFIG_SND_DEBUG
	/* debug file to पढ़ो all hdspm रेजिस्टरs */
	snd_card_ro_proc_new(hdspm->card, "debug", hdspm,
			     snd_hdspm_proc_पढ़ो_debug);
#पूर्ण_अगर
पूर्ण

/*------------------------------------------------------------
   hdspm पूर्णांकitialize
 ------------------------------------------------------------*/

अटल पूर्णांक snd_hdspm_set_शेषs(काष्ठा hdspm * hdspm)
अणु
	/* ASSUMPTION: hdspm->lock is either held, or there is no need to
	   hold it (e.g. during module initialization).
	   */

	/* set शेषs:       */

	hdspm->settings_रेजिस्टर = 0;

	चयन (hdspm->io_type) अणु
	हाल MADI:
	हाल MADIface:
		hdspm->control_रेजिस्टर =
			0x2 + 0x8 + 0x10 + 0x80 + 0x400 + 0x4000 + 0x1000000;
		अवरोध;

	हाल RayDAT:
	हाल AIO:
		hdspm->settings_रेजिस्टर = 0x1 + 0x1000;
		/* Magic values are: LAT_0, LAT_2, Master, freq1, tx64ch, inp_0,
		 * line_out */
		hdspm->control_रेजिस्टर =
			0x2 + 0x8 + 0x10 + 0x80 + 0x400 + 0x4000 + 0x1000000;
		अवरोध;

	हाल AES32:
		hdspm->control_रेजिस्टर =
			HDSPM_ClockModeMaster |	/* Master Clock Mode on */
			hdspm_encode_latency(7) | /* latency max=8192samples */
			HDSPM_SyncRef0 |	/* AES1 is syncघड़ी */
			HDSPM_LineOut |	/* Analog output in */
			HDSPM_Professional;  /* Professional mode */
		अवरोध;
	पूर्ण

	hdspm_ग_लिखो(hdspm, HDSPM_controlRegister, hdspm->control_रेजिस्टर);

	अगर (AES32 == hdspm->io_type) अणु
		/* No control2 रेजिस्टर क्रम AES32 */
#अगर_घोषित SNDRV_BIG_ENDIAN
		hdspm->control2_रेजिस्टर = HDSPM_BIGENDIAN_MODE;
#अन्यथा
		hdspm->control2_रेजिस्टर = 0;
#पूर्ण_अगर

		hdspm_ग_लिखो(hdspm, HDSPM_control2Reg, hdspm->control2_रेजिस्टर);
	पूर्ण
	hdspm_compute_period_size(hdspm);

	/* silence everything */

	all_in_all_mixer(hdspm, 0 * UNITY_GAIN);

	अगर (hdspm_is_raydat_or_aio(hdspm))
		hdspm_ग_लिखो(hdspm, HDSPM_WR_SETTINGS, hdspm->settings_रेजिस्टर);

	/* set a शेष rate so that the channel map is set up. */
	hdspm_set_rate(hdspm, 48000, 1);

	वापस 0;
पूर्ण


/*------------------------------------------------------------
   पूर्णांकerrupt
 ------------------------------------------------------------*/

अटल irqवापस_t snd_hdspm_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hdspm *hdspm = (काष्ठा hdspm *) dev_id;
	अचिन्हित पूर्णांक status;
	पूर्णांक i, audio, midi, schedule = 0;
	/* cycles_t now; */

	status = hdspm_पढ़ो(hdspm, HDSPM_statusRegister);

	audio = status & HDSPM_audioIRQPending;
	midi = status & (HDSPM_midi0IRQPending | HDSPM_midi1IRQPending |
			HDSPM_midi2IRQPending | HDSPM_midi3IRQPending);

	/* now = get_cycles(); */
	/*
	 *   LAT_2..LAT_0 period  counter (win)  counter (mac)
	 *          6       4096   ~256053425     ~514672358
	 *          5       2048   ~128024983     ~257373821
	 *          4       1024    ~64023706     ~128718089
	 *          3        512    ~32005945      ~64385999
	 *          2        256    ~16003039      ~32260176
	 *          1        128     ~7998738      ~16194507
	 *          0         64     ~3998231       ~8191558
	 */
	/*
	  dev_info(hdspm->card->dev, "snd_hdspm_interrupt %llu @ %llx\n",
	   now-hdspm->last_पूर्णांकerrupt, status & 0xFFC0);
	   hdspm->last_पूर्णांकerrupt = now;
	*/

	अगर (!audio && !midi)
		वापस IRQ_NONE;

	hdspm_ग_लिखो(hdspm, HDSPM_पूर्णांकerruptConfirmation, 0);
	hdspm->irq_count++;


	अगर (audio) अणु
		अगर (hdspm->capture_substream)
			snd_pcm_period_elapsed(hdspm->capture_substream);

		अगर (hdspm->playback_substream)
			snd_pcm_period_elapsed(hdspm->playback_substream);
	पूर्ण

	अगर (midi) अणु
		i = 0;
		जबतक (i < hdspm->midiPorts) अणु
			अगर ((hdspm_पढ़ो(hdspm,
				hdspm->midi[i].statusIn) & 0xff) &&
					(status & hdspm->midi[i].irq)) अणु
				/* we disable पूर्णांकerrupts क्रम this input until
				 * processing is करोne
				 */
				hdspm->control_रेजिस्टर &= ~hdspm->midi[i].ie;
				hdspm_ग_लिखो(hdspm, HDSPM_controlRegister,
						hdspm->control_रेजिस्टर);
				hdspm->midi[i].pending = 1;
				schedule = 1;
			पूर्ण

			i++;
		पूर्ण

		अगर (schedule)
			queue_work(प्रणाली_highpri_wq, &hdspm->midi_work);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*------------------------------------------------------------
   pcm पूर्णांकerface
  ------------------------------------------------------------*/


अटल snd_pcm_uframes_t snd_hdspm_hw_poपूर्णांकer(काष्ठा snd_pcm_substream
					      *substream)
अणु
	काष्ठा hdspm *hdspm = snd_pcm_substream_chip(substream);
	वापस hdspm_hw_poपूर्णांकer(hdspm);
पूर्ण


अटल पूर्णांक snd_hdspm_reset(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा hdspm *hdspm = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *other;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		other = hdspm->capture_substream;
	अन्यथा
		other = hdspm->playback_substream;

	अगर (hdspm->running)
		runसमय->status->hw_ptr = hdspm_hw_poपूर्णांकer(hdspm);
	अन्यथा
		runसमय->status->hw_ptr = 0;
	अगर (other) अणु
		काष्ठा snd_pcm_substream *s;
		काष्ठा snd_pcm_runसमय *orunसमय = other->runसमय;
		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			अगर (s == other) अणु
				orunसमय->status->hw_ptr =
					runसमय->status->hw_ptr;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा hdspm *hdspm = snd_pcm_substream_chip(substream);
	पूर्णांक err;
	पूर्णांक i;
	pid_t this_pid;
	pid_t other_pid;

	spin_lock_irq(&hdspm->lock);

	अगर (substream->pstr->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		this_pid = hdspm->playback_pid;
		other_pid = hdspm->capture_pid;
	पूर्ण अन्यथा अणु
		this_pid = hdspm->capture_pid;
		other_pid = hdspm->playback_pid;
	पूर्ण

	अगर (other_pid > 0 && this_pid != other_pid) अणु

		/* The other stream is खोलो, and not by the same
		   task as this one. Make sure that the parameters
		   that matter are the same.
		   */

		अगर (params_rate(params) != hdspm->प्रणाली_sample_rate) अणु
			spin_unlock_irq(&hdspm->lock);
			_snd_pcm_hw_param_setempty(params,
					SNDRV_PCM_HW_PARAM_RATE);
			वापस -EBUSY;
		पूर्ण

		अगर (params_period_size(params) != hdspm->period_bytes / 4) अणु
			spin_unlock_irq(&hdspm->lock);
			_snd_pcm_hw_param_setempty(params,
					SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
			वापस -EBUSY;
		पूर्ण

	पूर्ण
	/* We're fine. */
	spin_unlock_irq(&hdspm->lock);

	/* how to make sure that the rate matches an बाह्यally-set one ?   */

	spin_lock_irq(&hdspm->lock);
	err = hdspm_set_rate(hdspm, params_rate(params), 0);
	अगर (err < 0) अणु
		dev_info(hdspm->card->dev, "err on hdspm_set_rate: %d\n", err);
		spin_unlock_irq(&hdspm->lock);
		_snd_pcm_hw_param_setempty(params,
				SNDRV_PCM_HW_PARAM_RATE);
		वापस err;
	पूर्ण
	spin_unlock_irq(&hdspm->lock);

	err = hdspm_set_पूर्णांकerrupt_पूर्णांकerval(hdspm,
			params_period_size(params));
	अगर (err < 0) अणु
		dev_info(hdspm->card->dev,
			 "err on hdspm_set_interrupt_interval: %d\n", err);
		_snd_pcm_hw_param_setempty(params,
				SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
		वापस err;
	पूर्ण

	/* Memory allocation, takashi's method, करोnt know अगर we should
	 * spinlock
	 */
	/* दो_स्मृति all buffer even अगर not enabled to get sure */
	/* Update क्रम MADI rev 204: we need to allocate क्रम all channels,
	 * otherwise it करोesn't work at 96kHz */

	err =
		snd_pcm_lib_दो_स्मृति_pages(substream, HDSPM_DMA_AREA_BYTES);
	अगर (err < 0) अणु
		dev_info(hdspm->card->dev,
			 "err on snd_pcm_lib_malloc_pages: %d\n", err);
		वापस err;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु

		क्रम (i = 0; i < params_channels(params); ++i) अणु
			पूर्णांक c = hdspm->channel_map_out[i];

			अगर (c < 0)
				जारी;      /* just make sure */
			hdspm_set_channel_dma_addr(hdspm, substream,
						   HDSPM_pageAddressBufferOut,
						   c);
			snd_hdspm_enable_out(hdspm, c, 1);
		पूर्ण

		hdspm->playback_buffer =
			(अचिन्हित अक्षर *) substream->runसमय->dma_area;
		dev_dbg(hdspm->card->dev,
			"Allocated sample buffer for playback at %p\n",
				hdspm->playback_buffer);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < params_channels(params); ++i) अणु
			पूर्णांक c = hdspm->channel_map_in[i];

			अगर (c < 0)
				जारी;
			hdspm_set_channel_dma_addr(hdspm, substream,
						   HDSPM_pageAddressBufferIn,
						   c);
			snd_hdspm_enable_in(hdspm, c, 1);
		पूर्ण

		hdspm->capture_buffer =
			(अचिन्हित अक्षर *) substream->runसमय->dma_area;
		dev_dbg(hdspm->card->dev,
			"Allocated sample buffer for capture at %p\n",
				hdspm->capture_buffer);
	पूर्ण

	/*
	   dev_dbg(hdspm->card->dev,
	   "Allocated sample buffer for %s at 0x%08X\n",
	   substream->stream == SNDRV_PCM_STREAM_PLAYBACK ?
	   "playback" : "capture",
	   snd_pcm_sgbuf_get_addr(substream, 0));
	   */
	/*
	   dev_dbg(hdspm->card->dev,
	   "set_hwparams: %s %d Hz, %d channels, bs = %d\n",
	   substream->stream == SNDRV_PCM_STREAM_PLAYBACK ?
	   "playback" : "capture",
	   params_rate(params), params_channels(params),
	   params_buffer_size(params));
	   */


	/*  For AES cards, the भग्न क्रमmat bit is the same as the
	 *  preferred sync reference. Since we करोn't want to अवरोध
	 *  sync settings, we have to skip the reमुख्यing part of this
	 *  function.
	 */
	अगर (hdspm->io_type == AES32) अणु
		वापस 0;
	पूर्ण


	/* Switch to native भग्न क्रमmat अगर requested */
	अगर (SNDRV_PCM_FORMAT_FLOAT_LE == params_क्रमmat(params)) अणु
		अगर (!(hdspm->control_रेजिस्टर & HDSPe_FLOAT_FORMAT))
			dev_info(hdspm->card->dev,
				 "Switching to native 32bit LE float format.\n");

		hdspm->control_रेजिस्टर |= HDSPe_FLOAT_FORMAT;
	पूर्ण अन्यथा अगर (SNDRV_PCM_FORMAT_S32_LE == params_क्रमmat(params)) अणु
		अगर (hdspm->control_रेजिस्टर & HDSPe_FLOAT_FORMAT)
			dev_info(hdspm->card->dev,
				 "Switching to native 32bit LE integer format.\n");

		hdspm->control_रेजिस्टर &= ~HDSPe_FLOAT_FORMAT;
	पूर्ण
	hdspm_ग_लिखो(hdspm, HDSPM_controlRegister, hdspm->control_रेजिस्टर);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक i;
	काष्ठा hdspm *hdspm = snd_pcm_substream_chip(substream);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		/* Just disable all channels. The saving when disabling a */
		/* smaller set is not worth the trouble. */
		क्रम (i = 0; i < HDSPM_MAX_CHANNELS; ++i)
			snd_hdspm_enable_out(hdspm, i, 0);

		hdspm->playback_buffer = शून्य;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < HDSPM_MAX_CHANNELS; ++i)
			snd_hdspm_enable_in(hdspm, i, 0);

		hdspm->capture_buffer = शून्य;
	पूर्ण

	snd_pcm_lib_मुक्त_pages(substream);

	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdspm_channel_info(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_channel_info *info)
अणु
	काष्ठा hdspm *hdspm = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक channel = info->channel;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (snd_BUG_ON(channel >= hdspm->max_channels_out)) अणु
			dev_info(hdspm->card->dev,
				 "snd_hdspm_channel_info: output channel out of range (%d)\n",
				 channel);
			वापस -EINVAL;
		पूर्ण

		channel = array_index_nospec(channel, hdspm->max_channels_out);
		अगर (hdspm->channel_map_out[channel] < 0) अणु
			dev_info(hdspm->card->dev,
				 "snd_hdspm_channel_info: output channel %d mapped out\n",
				 channel);
			वापस -EINVAL;
		पूर्ण

		info->offset = hdspm->channel_map_out[channel] *
			HDSPM_CHANNEL_BUFFER_BYTES;
	पूर्ण अन्यथा अणु
		अगर (snd_BUG_ON(channel >= hdspm->max_channels_in)) अणु
			dev_info(hdspm->card->dev,
				 "snd_hdspm_channel_info: input channel out of range (%d)\n",
				 channel);
			वापस -EINVAL;
		पूर्ण

		channel = array_index_nospec(channel, hdspm->max_channels_in);
		अगर (hdspm->channel_map_in[channel] < 0) अणु
			dev_info(hdspm->card->dev,
				 "snd_hdspm_channel_info: input channel %d mapped out\n",
				 channel);
			वापस -EINVAL;
		पूर्ण

		info->offset = hdspm->channel_map_in[channel] *
			HDSPM_CHANNEL_BUFFER_BYTES;
	पूर्ण

	info->first = 0;
	info->step = 32;
	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdspm_ioctl(काष्ठा snd_pcm_substream *substream,
		अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल SNDRV_PCM_IOCTL1_RESET:
		वापस snd_hdspm_reset(substream);

	हाल SNDRV_PCM_IOCTL1_CHANNEL_INFO:
		अणु
			काष्ठा snd_pcm_channel_info *info = arg;
			वापस snd_hdspm_channel_info(substream, info);
		पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस snd_pcm_lib_ioctl(substream, cmd, arg);
पूर्ण

अटल पूर्णांक snd_hdspm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा hdspm *hdspm = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *other;
	पूर्णांक running;

	spin_lock(&hdspm->lock);
	running = hdspm->running;
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		running |= 1 << substream->stream;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		running &= ~(1 << substream->stream);
		अवरोध;
	शेष:
		snd_BUG();
		spin_unlock(&hdspm->lock);
		वापस -EINVAL;
	पूर्ण
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		other = hdspm->capture_substream;
	अन्यथा
		other = hdspm->playback_substream;

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
			अगर (!(running & (1 << SNDRV_PCM_STREAM_PLAYBACK))
					&& substream->stream ==
					SNDRV_PCM_STREAM_CAPTURE)
				hdspm_silence_playback(hdspm);
		पूर्ण अन्यथा अणु
			अगर (running &&
				substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
				hdspm_silence_playback(hdspm);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			hdspm_silence_playback(hdspm);
	पूर्ण
_ok:
	snd_pcm_trigger_करोne(substream, substream);
	अगर (!hdspm->running && running)
		hdspm_start_audio(hdspm);
	अन्यथा अगर (hdspm->running && !running)
		hdspm_stop_audio(hdspm);
	hdspm->running = running;
	spin_unlock(&hdspm->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_hdspm_playback_subinfo = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_NONINTERLEAVED |
		 SNDRV_PCM_INFO_SYNC_START | SNDRV_PCM_INFO_DOUBLE),
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
	.rates = (SNDRV_PCM_RATE_32000 |
		  SNDRV_PCM_RATE_44100 |
		  SNDRV_PCM_RATE_48000 |
		  SNDRV_PCM_RATE_64000 |
		  SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 |
		  SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000 ),
	.rate_min = 32000,
	.rate_max = 192000,
	.channels_min = 1,
	.channels_max = HDSPM_MAX_CHANNELS,
	.buffer_bytes_max =
	    HDSPM_CHANNEL_BUFFER_BYTES * HDSPM_MAX_CHANNELS,
	.period_bytes_min = (32 * 4),
	.period_bytes_max = (8192 * 4) * HDSPM_MAX_CHANNELS,
	.periods_min = 2,
	.periods_max = 512,
	.fअगरo_size = 0
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_hdspm_capture_subinfo = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_NONINTERLEAVED |
		 SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
	.rates = (SNDRV_PCM_RATE_32000 |
		  SNDRV_PCM_RATE_44100 |
		  SNDRV_PCM_RATE_48000 |
		  SNDRV_PCM_RATE_64000 |
		  SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 |
		  SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000),
	.rate_min = 32000,
	.rate_max = 192000,
	.channels_min = 1,
	.channels_max = HDSPM_MAX_CHANNELS,
	.buffer_bytes_max =
	    HDSPM_CHANNEL_BUFFER_BYTES * HDSPM_MAX_CHANNELS,
	.period_bytes_min = (32 * 4),
	.period_bytes_max = (8192 * 4) * HDSPM_MAX_CHANNELS,
	.periods_min = 2,
	.periods_max = 512,
	.fअगरo_size = 0
पूर्ण;

अटल पूर्णांक snd_hdspm_hw_rule_in_channels_rate(काष्ठा snd_pcm_hw_params *params,
					   काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा hdspm *hdspm = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c =
	    hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *r =
	    hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);

	अगर (r->min > 96000 && r->max <= 192000) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = hdspm->qs_in_channels,
			.max = hdspm->qs_in_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण अन्यथा अगर (r->min > 48000 && r->max <= 96000) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = hdspm->ds_in_channels,
			.max = hdspm->ds_in_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण अन्यथा अगर (r->max < 64000) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = hdspm->ss_in_channels,
			.max = hdspm->ss_in_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_hw_rule_out_channels_rate(काष्ठा snd_pcm_hw_params *params,
					   काष्ठा snd_pcm_hw_rule * rule)
अणु
	काष्ठा hdspm *hdspm = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c =
	    hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *r =
	    hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);

	अगर (r->min > 96000 && r->max <= 192000) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = hdspm->qs_out_channels,
			.max = hdspm->qs_out_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण अन्यथा अगर (r->min > 48000 && r->max <= 96000) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = hdspm->ds_out_channels,
			.max = hdspm->ds_out_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण अन्यथा अगर (r->max < 64000) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = hdspm->ss_out_channels,
			.max = hdspm->ss_out_channels,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(c, &t);
	पूर्ण अन्यथा अणु
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_hw_rule_rate_in_channels(काष्ठा snd_pcm_hw_params *params,
					   काष्ठा snd_pcm_hw_rule * rule)
अणु
	काष्ठा hdspm *hdspm = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c =
	    hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *r =
	    hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);

	अगर (c->min >= hdspm->ss_in_channels) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 32000,
			.max = 48000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण अन्यथा अगर (c->max <= hdspm->qs_in_channels) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 128000,
			.max = 192000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण अन्यथा अगर (c->max <= hdspm->ds_in_channels) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 64000,
			.max = 96000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण

	वापस 0;
पूर्ण
अटल पूर्णांक snd_hdspm_hw_rule_rate_out_channels(काष्ठा snd_pcm_hw_params *params,
					   काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा hdspm *hdspm = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c =
	    hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *r =
	    hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);

	अगर (c->min >= hdspm->ss_out_channels) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 32000,
			.max = 48000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण अन्यथा अगर (c->max <= hdspm->qs_out_channels) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 128000,
			.max = 192000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण अन्यथा अगर (c->max <= hdspm->ds_out_channels) अणु
		काष्ठा snd_पूर्णांकerval t = अणु
			.min = 64000,
			.max = 96000,
			.पूर्णांकeger = 1,
		पूर्ण;
		वापस snd_पूर्णांकerval_refine(r, &t);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_hw_rule_in_channels(काष्ठा snd_pcm_hw_params *params,
				      काष्ठा snd_pcm_hw_rule *rule)
अणु
	अचिन्हित पूर्णांक list[3];
	काष्ठा hdspm *hdspm = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_CHANNELS);

	list[0] = hdspm->qs_in_channels;
	list[1] = hdspm->ds_in_channels;
	list[2] = hdspm->ss_in_channels;
	वापस snd_पूर्णांकerval_list(c, 3, list, 0);
पूर्ण

अटल पूर्णांक snd_hdspm_hw_rule_out_channels(काष्ठा snd_pcm_hw_params *params,
				      काष्ठा snd_pcm_hw_rule *rule)
अणु
	अचिन्हित पूर्णांक list[3];
	काष्ठा hdspm *hdspm = rule->निजी;
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_CHANNELS);

	list[0] = hdspm->qs_out_channels;
	list[1] = hdspm->ds_out_channels;
	list[2] = hdspm->ss_out_channels;
	वापस snd_पूर्णांकerval_list(c, 3, list, 0);
पूर्ण


अटल स्थिर अचिन्हित पूर्णांक hdspm_aes32_sample_rates[] = अणु
	32000, 44100, 48000, 64000, 88200, 96000, 128000, 176400, 192000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list
hdspm_hw_स्थिरraपूर्णांकs_aes32_sample_rates = अणु
	.count = ARRAY_SIZE(hdspm_aes32_sample_rates),
	.list = hdspm_aes32_sample_rates,
	.mask = 0
पूर्ण;

अटल पूर्णांक snd_hdspm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdspm *hdspm = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	bool playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);

	spin_lock_irq(&hdspm->lock);
	snd_pcm_set_sync(substream);
	runसमय->hw = (playback) ? snd_hdspm_playback_subinfo :
		snd_hdspm_capture_subinfo;

	अगर (playback) अणु
		अगर (!hdspm->capture_substream)
			hdspm_stop_audio(hdspm);

		hdspm->playback_pid = current->pid;
		hdspm->playback_substream = substream;
	पूर्ण अन्यथा अणु
		अगर (!hdspm->playback_substream)
			hdspm_stop_audio(hdspm);

		hdspm->capture_pid = current->pid;
		hdspm->capture_substream = substream;
	पूर्ण

	spin_unlock_irq(&hdspm->lock);

	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	snd_pcm_hw_स्थिरraपूर्णांक_घात2(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);

	चयन (hdspm->io_type) अणु
	हाल AIO:
	हाल RayDAT:
		snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
					     SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					     32, 4096);
		/* RayDAT & AIO have a fixed buffer of 16384 samples per channel */
		snd_pcm_hw_स्थिरraपूर्णांक_single(runसमय,
					     SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					     16384);
		अवरोध;

	शेष:
		snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
					     SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					     64, 8192);
		snd_pcm_hw_स्थिरraपूर्णांक_single(runसमय,
					     SNDRV_PCM_HW_PARAM_PERIODS, 2);
		अवरोध;
	पूर्ण

	अगर (AES32 == hdspm->io_type) अणु
		runसमय->hw.rates |= SNDRV_PCM_RATE_KNOT;
		snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				&hdspm_hw_स्थिरraपूर्णांकs_aes32_sample_rates);
	पूर्ण अन्यथा अणु
		snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				(playback ?
				 snd_hdspm_hw_rule_rate_out_channels :
				 snd_hdspm_hw_rule_rate_in_channels), hdspm,
				SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	पूर्ण

	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			(playback ? snd_hdspm_hw_rule_out_channels :
			 snd_hdspm_hw_rule_in_channels), hdspm,
			SNDRV_PCM_HW_PARAM_CHANNELS, -1);

	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			(playback ? snd_hdspm_hw_rule_out_channels_rate :
			 snd_hdspm_hw_rule_in_channels_rate), hdspm,
			SNDRV_PCM_HW_PARAM_RATE, -1);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_release(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdspm *hdspm = snd_pcm_substream_chip(substream);
	bool playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);

	spin_lock_irq(&hdspm->lock);

	अगर (playback) अणु
		hdspm->playback_pid = -1;
		hdspm->playback_substream = शून्य;
	पूर्ण अन्यथा अणु
		hdspm->capture_pid = -1;
		hdspm->capture_substream = शून्य;
	पूर्ण

	spin_unlock_irq(&hdspm->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_hwdep_dummy_op(काष्ठा snd_hwdep *hw, काष्ठा file *file)
अणु
	/* we have nothing to initialize but the call is required */
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक copy_u32_le(व्योम __user *dest, व्योम __iomem *src)
अणु
	u32 val = पढ़ोl(src);
	वापस copy_to_user(dest, &val, 4);
पूर्ण

अटल पूर्णांक snd_hdspm_hwdep_ioctl(काष्ठा snd_hwdep *hw, काष्ठा file *file,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा hdspm *hdspm = hw->निजी_data;
	काष्ठा hdspm_mixer_ioctl mixer;
	काष्ठा hdspm_config info;
	काष्ठा hdspm_status status;
	काष्ठा hdspm_version hdspm_version;
	काष्ठा hdspm_peak_rms *levels;
	काष्ठा hdspm_ltc ltc;
	अचिन्हित पूर्णांक statusरेजिस्टर;
	दीर्घ अचिन्हित पूर्णांक s;
	पूर्णांक i = 0;

	चयन (cmd) अणु

	हाल SNDRV_HDSPM_IOCTL_GET_PEAK_RMS:
		levels = &hdspm->peak_rms;
		क्रम (i = 0; i < HDSPM_MAX_CHANNELS; i++) अणु
			levels->input_peaks[i] =
				पढ़ोl(hdspm->iobase +
						HDSPM_MADI_INPUT_PEAK + i*4);
			levels->playback_peaks[i] =
				पढ़ोl(hdspm->iobase +
						HDSPM_MADI_PLAYBACK_PEAK + i*4);
			levels->output_peaks[i] =
				पढ़ोl(hdspm->iobase +
						HDSPM_MADI_OUTPUT_PEAK + i*4);

			levels->input_rms[i] =
				((uपूर्णांक64_t) पढ़ोl(hdspm->iobase +
					HDSPM_MADI_INPUT_RMS_H + i*4) << 32) |
				(uपूर्णांक64_t) पढ़ोl(hdspm->iobase +
						HDSPM_MADI_INPUT_RMS_L + i*4);
			levels->playback_rms[i] =
				((uपूर्णांक64_t)पढ़ोl(hdspm->iobase +
					HDSPM_MADI_PLAYBACK_RMS_H+i*4) << 32) |
				(uपूर्णांक64_t)पढ़ोl(hdspm->iobase +
					HDSPM_MADI_PLAYBACK_RMS_L + i*4);
			levels->output_rms[i] =
				((uपूर्णांक64_t)पढ़ोl(hdspm->iobase +
					HDSPM_MADI_OUTPUT_RMS_H + i*4) << 32) |
				(uपूर्णांक64_t)पढ़ोl(hdspm->iobase +
						HDSPM_MADI_OUTPUT_RMS_L + i*4);
		पूर्ण

		अगर (hdspm->प्रणाली_sample_rate > 96000) अणु
			levels->speed = qs;
		पूर्ण अन्यथा अगर (hdspm->प्रणाली_sample_rate > 48000) अणु
			levels->speed = ds;
		पूर्ण अन्यथा अणु
			levels->speed = ss;
		पूर्ण
		levels->status2 = hdspm_पढ़ो(hdspm, HDSPM_statusRegister2);

		s = copy_to_user(argp, levels, माप(*levels));
		अगर (0 != s) अणु
			/* dev_err(hdspm->card->dev, "copy_to_user(.., .., %lu): %lu
			 [Levels]\न", माप(काष्ठा hdspm_peak_rms), s);
			 */
			वापस -EFAULT;
		पूर्ण
		अवरोध;

	हाल SNDRV_HDSPM_IOCTL_GET_LTC:
		ltc.ltc = hdspm_पढ़ो(hdspm, HDSPM_RD_TCO);
		i = hdspm_पढ़ो(hdspm, HDSPM_RD_TCO + 4);
		अगर (i & HDSPM_TCO1_LTC_Input_valid) अणु
			चयन (i & (HDSPM_TCO1_LTC_Format_LSB |
				HDSPM_TCO1_LTC_Format_MSB)) अणु
			हाल 0:
				ltc.क्रमmat = fps_24;
				अवरोध;
			हाल HDSPM_TCO1_LTC_Format_LSB:
				ltc.क्रमmat = fps_25;
				अवरोध;
			हाल HDSPM_TCO1_LTC_Format_MSB:
				ltc.क्रमmat = fps_2997;
				अवरोध;
			शेष:
				ltc.क्रमmat = fps_30;
				अवरोध;
			पूर्ण
			अगर (i & HDSPM_TCO1_set_drop_frame_flag) अणु
				ltc.frame = drop_frame;
			पूर्ण अन्यथा अणु
				ltc.frame = full_frame;
			पूर्ण
		पूर्ण अन्यथा अणु
			ltc.क्रमmat = क्रमmat_invalid;
			ltc.frame = frame_invalid;
		पूर्ण
		अगर (i & HDSPM_TCO1_Video_Input_Format_NTSC) अणु
			ltc.input_क्रमmat = ntsc;
		पूर्ण अन्यथा अगर (i & HDSPM_TCO1_Video_Input_Format_PAL) अणु
			ltc.input_क्रमmat = pal;
		पूर्ण अन्यथा अणु
			ltc.input_क्रमmat = no_video;
		पूर्ण

		s = copy_to_user(argp, &ltc, माप(ltc));
		अगर (0 != s) अणु
			/*
			  dev_err(hdspm->card->dev, "copy_to_user(.., .., %lu): %lu [LTC]\n", माप(काष्ठा hdspm_ltc), s); */
			वापस -EFAULT;
		पूर्ण

		अवरोध;

	हाल SNDRV_HDSPM_IOCTL_GET_CONFIG:

		स_रखो(&info, 0, माप(info));
		spin_lock_irq(&hdspm->lock);
		info.pref_sync_ref = hdspm_pref_sync_ref(hdspm);
		info.wordघड़ी_sync_check = hdspm_wc_sync_check(hdspm);

		info.प्रणाली_sample_rate = hdspm->प्रणाली_sample_rate;
		info.स्वतःsync_sample_rate =
			hdspm_बाह्यal_sample_rate(hdspm);
		info.प्रणाली_घड़ी_mode = hdspm_प्रणाली_घड़ी_mode(hdspm);
		info.घड़ी_source = hdspm_घड़ी_source(hdspm);
		info.स्वतःsync_ref = hdspm_स्वतःsync_ref(hdspm);
		info.line_out = hdspm_toggle_setting(hdspm, HDSPM_LineOut);
		info.passthru = 0;
		spin_unlock_irq(&hdspm->lock);
		अगर (copy_to_user(argp, &info, माप(info)))
			वापस -EFAULT;
		अवरोध;

	हाल SNDRV_HDSPM_IOCTL_GET_STATUS:
		स_रखो(&status, 0, माप(status));

		status.card_type = hdspm->io_type;

		status.स्वतःsync_source = hdspm_स्वतःsync_ref(hdspm);

		status.card_घड़ी = 110069313433624ULL;
		status.master_period = hdspm_पढ़ो(hdspm, HDSPM_RD_PLL_FREQ);

		चयन (hdspm->io_type) अणु
		हाल MADI:
		हाल MADIface:
			status.card_specअगरic.madi.sync_wc =
				hdspm_wc_sync_check(hdspm);
			status.card_specअगरic.madi.sync_madi =
				hdspm_madi_sync_check(hdspm);
			status.card_specअगरic.madi.sync_tco =
				hdspm_tco_sync_check(hdspm);
			status.card_specअगरic.madi.sync_in =
				hdspm_sync_in_sync_check(hdspm);

			statusरेजिस्टर =
				hdspm_पढ़ो(hdspm, HDSPM_statusRegister);
			status.card_specअगरic.madi.madi_input =
				(statusरेजिस्टर & HDSPM_AB_पूर्णांक) ? 1 : 0;
			status.card_specअगरic.madi.channel_क्रमmat =
				(statusरेजिस्टर & HDSPM_RX_64ch) ? 1 : 0;
			/* TODO: Mac driver sets it when f_s>48kHz */
			status.card_specअगरic.madi.frame_क्रमmat = 0;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		अगर (copy_to_user(argp, &status, माप(status)))
			वापस -EFAULT;


		अवरोध;

	हाल SNDRV_HDSPM_IOCTL_GET_VERSION:
		स_रखो(&hdspm_version, 0, माप(hdspm_version));

		hdspm_version.card_type = hdspm->io_type;
		strscpy(hdspm_version.cardname, hdspm->card_name,
				माप(hdspm_version.cardname));
		hdspm_version.serial = hdspm->serial;
		hdspm_version.firmware_rev = hdspm->firmware_rev;
		hdspm_version.adकरोns = 0;
		अगर (hdspm->tco)
			hdspm_version.adकरोns |= HDSPM_ADDON_TCO;

		अगर (copy_to_user(argp, &hdspm_version,
					माप(hdspm_version)))
			वापस -EFAULT;
		अवरोध;

	हाल SNDRV_HDSPM_IOCTL_GET_MIXER:
		अगर (copy_from_user(&mixer, argp, माप(mixer)))
			वापस -EFAULT;
		अगर (copy_to_user((व्योम __user *)mixer.mixer, hdspm->mixer,
				 माप(*mixer.mixer)))
			वापस -EFAULT;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_hdspm_ops = अणु
	.खोलो = snd_hdspm_खोलो,
	.बंद = snd_hdspm_release,
	.ioctl = snd_hdspm_ioctl,
	.hw_params = snd_hdspm_hw_params,
	.hw_मुक्त = snd_hdspm_hw_मुक्त,
	.prepare = snd_hdspm_prepare,
	.trigger = snd_hdspm_trigger,
	.poपूर्णांकer = snd_hdspm_hw_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_hdspm_create_hwdep(काष्ठा snd_card *card,
				  काष्ठा hdspm *hdspm)
अणु
	काष्ठा snd_hwdep *hw;
	पूर्णांक err;

	err = snd_hwdep_new(card, "HDSPM hwdep", 0, &hw);
	अगर (err < 0)
		वापस err;

	hdspm->hwdep = hw;
	hw->निजी_data = hdspm;
	म_नकल(hw->name, "HDSPM hwdep interface");

	hw->ops.खोलो = snd_hdspm_hwdep_dummy_op;
	hw->ops.ioctl = snd_hdspm_hwdep_ioctl;
	hw->ops.ioctl_compat = snd_hdspm_hwdep_ioctl;
	hw->ops.release = snd_hdspm_hwdep_dummy_op;

	वापस 0;
पूर्ण


/*------------------------------------------------------------
   memory पूर्णांकerface
 ------------------------------------------------------------*/
अटल पूर्णांक snd_hdspm_pपुनः_स्मृतिate_memory(काष्ठा hdspm *hdspm)
अणु
	काष्ठा snd_pcm *pcm;
	माप_प्रकार wanted;

	pcm = hdspm->pcm;

	wanted = HDSPM_DMA_AREA_BYTES;

	snd_pcm_lib_pपुनः_स्मृतिate_pages_क्रम_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
					      &hdspm->pci->dev,
					      wanted, wanted);
	dev_dbg(hdspm->card->dev, " Preallocated %zd Bytes\n", wanted);
	वापस 0;
पूर्ण

/* Inक्रमm the card what DMA addresses to use क्रम the indicated channel. */
/* Each channel got 16 4K pages allocated क्रम DMA transfers. */
अटल व्योम hdspm_set_channel_dma_addr(काष्ठा hdspm *hdspm,
				       काष्ठा snd_pcm_substream *substream,
				       अचिन्हित पूर्णांक reg, पूर्णांक channel)
अणु
	पूर्णांक i;

	क्रम (i = channel * 16; i < channel * 16 + 16; i++)
		hdspm_ग_लिखो(hdspm, reg + 4 * i,
			    snd_pcm_sgbuf_get_addr(substream, 4096 * i));
पूर्ण


/* ------------- ALSA Devices ---------------------------- */
अटल पूर्णांक snd_hdspm_create_pcm(काष्ठा snd_card *card,
				काष्ठा hdspm *hdspm)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(card, hdspm->card_name, 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	hdspm->pcm = pcm;
	pcm->निजी_data = hdspm;
	म_नकल(pcm->name, hdspm->card_name);

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_hdspm_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_hdspm_ops);

	pcm->info_flags = SNDRV_PCM_INFO_JOINT_DUPLEX;

	err = snd_hdspm_pपुनः_स्मृतिate_memory(hdspm);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम snd_hdspm_initialize_midi_flush(काष्ठा hdspm * hdspm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hdspm->midiPorts; i++)
		snd_hdspm_flush_midi_input(hdspm, i);
पूर्ण

अटल पूर्णांक snd_hdspm_create_alsa_devices(काष्ठा snd_card *card,
					 काष्ठा hdspm *hdspm)
अणु
	पूर्णांक err, i;

	dev_dbg(card->dev, "Create card...\n");
	err = snd_hdspm_create_pcm(card, hdspm);
	अगर (err < 0)
		वापस err;

	i = 0;
	जबतक (i < hdspm->midiPorts) अणु
		err = snd_hdspm_create_midi(card, hdspm, i);
		अगर (err < 0) अणु
			वापस err;
		पूर्ण
		i++;
	पूर्ण

	err = snd_hdspm_create_controls(card, hdspm);
	अगर (err < 0)
		वापस err;

	err = snd_hdspm_create_hwdep(card, hdspm);
	अगर (err < 0)
		वापस err;

	dev_dbg(card->dev, "proc init...\n");
	snd_hdspm_proc_init(hdspm);

	hdspm->प्रणाली_sample_rate = -1;
	hdspm->last_बाह्यal_sample_rate = -1;
	hdspm->last_पूर्णांकernal_sample_rate = -1;
	hdspm->playback_pid = -1;
	hdspm->capture_pid = -1;
	hdspm->capture_substream = शून्य;
	hdspm->playback_substream = शून्य;

	dev_dbg(card->dev, "Set defaults...\n");
	err = snd_hdspm_set_शेषs(hdspm);
	अगर (err < 0)
		वापस err;

	dev_dbg(card->dev, "Update mixer controls...\n");
	hdspm_update_simple_mixer_controls(hdspm);

	dev_dbg(card->dev, "Initializing complete?\n");

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0) अणु
		dev_err(card->dev, "error registering card\n");
		वापस err;
	पूर्ण

	dev_dbg(card->dev, "... yes now\n");

	वापस 0;
पूर्ण

अटल पूर्णांक snd_hdspm_create(काष्ठा snd_card *card,
			    काष्ठा hdspm *hdspm)
अणु

	काष्ठा pci_dev *pci = hdspm->pci;
	पूर्णांक err;
	अचिन्हित दीर्घ io_extent;

	hdspm->irq = -1;
	hdspm->card = card;

	spin_lock_init(&hdspm->lock);
	INIT_WORK(&hdspm->midi_work, hdspm_midi_work);

	pci_पढ़ो_config_word(hdspm->pci,
			PCI_CLASS_REVISION, &hdspm->firmware_rev);

	म_नकल(card->mixername, "Xilinx FPGA");
	म_नकल(card->driver, "HDSPM");

	चयन (hdspm->firmware_rev) अणु
	हाल HDSPM_RAYDAT_REV:
		hdspm->io_type = RayDAT;
		hdspm->card_name = "RME RayDAT";
		hdspm->midiPorts = 2;
		अवरोध;
	हाल HDSPM_AIO_REV:
		hdspm->io_type = AIO;
		hdspm->card_name = "RME AIO";
		hdspm->midiPorts = 1;
		अवरोध;
	हाल HDSPM_MADIFACE_REV:
		hdspm->io_type = MADIface;
		hdspm->card_name = "RME MADIface";
		hdspm->midiPorts = 1;
		अवरोध;
	शेष:
		अगर ((hdspm->firmware_rev == 0xf0) ||
			((hdspm->firmware_rev >= 0xe6) &&
					(hdspm->firmware_rev <= 0xea))) अणु
			hdspm->io_type = AES32;
			hdspm->card_name = "RME AES32";
			hdspm->midiPorts = 2;
		पूर्ण अन्यथा अगर ((hdspm->firmware_rev == 0xd2) ||
			((hdspm->firmware_rev >= 0xc8)  &&
				(hdspm->firmware_rev <= 0xcf))) अणु
			hdspm->io_type = MADI;
			hdspm->card_name = "RME MADI";
			hdspm->midiPorts = 3;
		पूर्ण अन्यथा अणु
			dev_err(card->dev,
				"unknown firmware revision %x\n",
				hdspm->firmware_rev);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;

	pci_set_master(hdspm->pci);

	err = pci_request_regions(pci, "hdspm");
	अगर (err < 0)
		वापस err;

	hdspm->port = pci_resource_start(pci, 0);
	io_extent = pci_resource_len(pci, 0);

	dev_dbg(card->dev, "grabbed memory region 0x%lx-0x%lx\n",
			hdspm->port, hdspm->port + io_extent - 1);

	hdspm->iobase = ioremap(hdspm->port, io_extent);
	अगर (!hdspm->iobase) अणु
		dev_err(card->dev, "unable to remap region 0x%lx-0x%lx\n",
				hdspm->port, hdspm->port + io_extent - 1);
		वापस -EBUSY;
	पूर्ण
	dev_dbg(card->dev, "remapped region (0x%lx) 0x%lx-0x%lx\n",
			(अचिन्हित दीर्घ)hdspm->iobase, hdspm->port,
			hdspm->port + io_extent - 1);

	अगर (request_irq(pci->irq, snd_hdspm_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, hdspm)) अणु
		dev_err(card->dev, "unable to use IRQ %d\n", pci->irq);
		वापस -EBUSY;
	पूर्ण

	dev_dbg(card->dev, "use IRQ %d\n", pci->irq);

	hdspm->irq = pci->irq;
	card->sync_irq = hdspm->irq;

	dev_dbg(card->dev, "kmalloc Mixer memory of %zd Bytes\n",
		माप(*hdspm->mixer));
	hdspm->mixer = kzalloc(माप(*hdspm->mixer), GFP_KERNEL);
	अगर (!hdspm->mixer)
		वापस -ENOMEM;

	hdspm->port_names_in = शून्य;
	hdspm->port_names_out = शून्य;

	चयन (hdspm->io_type) अणु
	हाल AES32:
		hdspm->ss_in_channels = hdspm->ss_out_channels = AES32_CHANNELS;
		hdspm->ds_in_channels = hdspm->ds_out_channels = AES32_CHANNELS;
		hdspm->qs_in_channels = hdspm->qs_out_channels = AES32_CHANNELS;

		hdspm->channel_map_in_ss = hdspm->channel_map_out_ss =
			channel_map_aes32;
		hdspm->channel_map_in_ds = hdspm->channel_map_out_ds =
			channel_map_aes32;
		hdspm->channel_map_in_qs = hdspm->channel_map_out_qs =
			channel_map_aes32;
		hdspm->port_names_in_ss = hdspm->port_names_out_ss =
			texts_ports_aes32;
		hdspm->port_names_in_ds = hdspm->port_names_out_ds =
			texts_ports_aes32;
		hdspm->port_names_in_qs = hdspm->port_names_out_qs =
			texts_ports_aes32;

		hdspm->max_channels_out = hdspm->max_channels_in =
			AES32_CHANNELS;
		hdspm->port_names_in = hdspm->port_names_out =
			texts_ports_aes32;
		hdspm->channel_map_in = hdspm->channel_map_out =
			channel_map_aes32;

		अवरोध;

	हाल MADI:
	हाल MADIface:
		hdspm->ss_in_channels = hdspm->ss_out_channels =
			MADI_SS_CHANNELS;
		hdspm->ds_in_channels = hdspm->ds_out_channels =
			MADI_DS_CHANNELS;
		hdspm->qs_in_channels = hdspm->qs_out_channels =
			MADI_QS_CHANNELS;

		hdspm->channel_map_in_ss = hdspm->channel_map_out_ss =
			channel_map_unity_ss;
		hdspm->channel_map_in_ds = hdspm->channel_map_out_ds =
			channel_map_unity_ss;
		hdspm->channel_map_in_qs = hdspm->channel_map_out_qs =
			channel_map_unity_ss;

		hdspm->port_names_in_ss = hdspm->port_names_out_ss =
			texts_ports_madi;
		hdspm->port_names_in_ds = hdspm->port_names_out_ds =
			texts_ports_madi;
		hdspm->port_names_in_qs = hdspm->port_names_out_qs =
			texts_ports_madi;
		अवरोध;

	हाल AIO:
		hdspm->ss_in_channels = AIO_IN_SS_CHANNELS;
		hdspm->ds_in_channels = AIO_IN_DS_CHANNELS;
		hdspm->qs_in_channels = AIO_IN_QS_CHANNELS;
		hdspm->ss_out_channels = AIO_OUT_SS_CHANNELS;
		hdspm->ds_out_channels = AIO_OUT_DS_CHANNELS;
		hdspm->qs_out_channels = AIO_OUT_QS_CHANNELS;

		अगर (0 == (hdspm_पढ़ो(hdspm, HDSPM_statusRegister2) & HDSPM_s2_AEBI_D)) अणु
			dev_info(card->dev, "AEB input board found\n");
			hdspm->ss_in_channels += 4;
			hdspm->ds_in_channels += 4;
			hdspm->qs_in_channels += 4;
		पूर्ण

		अगर (0 == (hdspm_पढ़ो(hdspm, HDSPM_statusRegister2) & HDSPM_s2_AEBO_D)) अणु
			dev_info(card->dev, "AEB output board found\n");
			hdspm->ss_out_channels += 4;
			hdspm->ds_out_channels += 4;
			hdspm->qs_out_channels += 4;
		पूर्ण

		hdspm->channel_map_out_ss = channel_map_aio_out_ss;
		hdspm->channel_map_out_ds = channel_map_aio_out_ds;
		hdspm->channel_map_out_qs = channel_map_aio_out_qs;

		hdspm->channel_map_in_ss = channel_map_aio_in_ss;
		hdspm->channel_map_in_ds = channel_map_aio_in_ds;
		hdspm->channel_map_in_qs = channel_map_aio_in_qs;

		hdspm->port_names_in_ss = texts_ports_aio_in_ss;
		hdspm->port_names_out_ss = texts_ports_aio_out_ss;
		hdspm->port_names_in_ds = texts_ports_aio_in_ds;
		hdspm->port_names_out_ds = texts_ports_aio_out_ds;
		hdspm->port_names_in_qs = texts_ports_aio_in_qs;
		hdspm->port_names_out_qs = texts_ports_aio_out_qs;

		अवरोध;

	हाल RayDAT:
		hdspm->ss_in_channels = hdspm->ss_out_channels =
			RAYDAT_SS_CHANNELS;
		hdspm->ds_in_channels = hdspm->ds_out_channels =
			RAYDAT_DS_CHANNELS;
		hdspm->qs_in_channels = hdspm->qs_out_channels =
			RAYDAT_QS_CHANNELS;

		hdspm->max_channels_in = RAYDAT_SS_CHANNELS;
		hdspm->max_channels_out = RAYDAT_SS_CHANNELS;

		hdspm->channel_map_in_ss = hdspm->channel_map_out_ss =
			channel_map_raydat_ss;
		hdspm->channel_map_in_ds = hdspm->channel_map_out_ds =
			channel_map_raydat_ds;
		hdspm->channel_map_in_qs = hdspm->channel_map_out_qs =
			channel_map_raydat_qs;
		hdspm->channel_map_in = hdspm->channel_map_out =
			channel_map_raydat_ss;

		hdspm->port_names_in_ss = hdspm->port_names_out_ss =
			texts_ports_raydat_ss;
		hdspm->port_names_in_ds = hdspm->port_names_out_ds =
			texts_ports_raydat_ds;
		hdspm->port_names_in_qs = hdspm->port_names_out_qs =
			texts_ports_raydat_qs;


		अवरोध;

	पूर्ण

	/* TCO detection */
	चयन (hdspm->io_type) अणु
	हाल AIO:
	हाल RayDAT:
		अगर (hdspm_पढ़ो(hdspm, HDSPM_statusRegister2) &
				HDSPM_s2_tco_detect) अणु
			hdspm->midiPorts++;
			hdspm->tco = kzalloc(माप(*hdspm->tco), GFP_KERNEL);
			अगर (hdspm->tco)
				hdspm_tco_ग_लिखो(hdspm);

			dev_info(card->dev, "AIO/RayDAT TCO module found\n");
		पूर्ण अन्यथा अणु
			hdspm->tco = शून्य;
		पूर्ण
		अवरोध;

	हाल MADI:
	हाल AES32:
		अगर (hdspm_पढ़ो(hdspm, HDSPM_statusRegister) & HDSPM_tco_detect) अणु
			hdspm->midiPorts++;
			hdspm->tco = kzalloc(माप(*hdspm->tco), GFP_KERNEL);
			अगर (hdspm->tco)
				hdspm_tco_ग_लिखो(hdspm);

			dev_info(card->dev, "MADI/AES TCO module found\n");
		पूर्ण अन्यथा अणु
			hdspm->tco = शून्य;
		पूर्ण
		अवरोध;

	शेष:
		hdspm->tco = शून्य;
	पूर्ण

	/* texts */
	चयन (hdspm->io_type) अणु
	हाल AES32:
		अगर (hdspm->tco) अणु
			hdspm->texts_स्वतःsync = texts_स्वतःsync_aes_tco;
			hdspm->texts_स्वतःsync_items =
				ARRAY_SIZE(texts_स्वतःsync_aes_tco);
		पूर्ण अन्यथा अणु
			hdspm->texts_स्वतःsync = texts_स्वतःsync_aes;
			hdspm->texts_स्वतःsync_items =
				ARRAY_SIZE(texts_स्वतःsync_aes);
		पूर्ण
		अवरोध;

	हाल MADI:
		अगर (hdspm->tco) अणु
			hdspm->texts_स्वतःsync = texts_स्वतःsync_madi_tco;
			hdspm->texts_स्वतःsync_items = 4;
		पूर्ण अन्यथा अणु
			hdspm->texts_स्वतःsync = texts_स्वतःsync_madi;
			hdspm->texts_स्वतःsync_items = 3;
		पूर्ण
		अवरोध;

	हाल MADIface:

		अवरोध;

	हाल RayDAT:
		अगर (hdspm->tco) अणु
			hdspm->texts_स्वतःsync = texts_स्वतःsync_raydat_tco;
			hdspm->texts_स्वतःsync_items = 9;
		पूर्ण अन्यथा अणु
			hdspm->texts_स्वतःsync = texts_स्वतःsync_raydat;
			hdspm->texts_स्वतःsync_items = 8;
		पूर्ण
		अवरोध;

	हाल AIO:
		अगर (hdspm->tco) अणु
			hdspm->texts_स्वतःsync = texts_स्वतःsync_aio_tco;
			hdspm->texts_स्वतःsync_items = 6;
		पूर्ण अन्यथा अणु
			hdspm->texts_स्वतःsync = texts_स्वतःsync_aio;
			hdspm->texts_स्वतःsync_items = 5;
		पूर्ण
		अवरोध;

	पूर्ण

	अगर (hdspm->io_type != MADIface) अणु
		hdspm->serial = (hdspm_पढ़ो(hdspm,
				HDSPM_midiStatusIn0)>>8) & 0xFFFFFF;
		/* id contains either a user-provided value or the शेष
		 * शून्य. If it's the default, we're safe to
		 * fill card->id with the serial number.
		 *
		 * If the serial number is 0xFFFFFF, then we're dealing with
		 * an old PCI revision that comes without a sane number. In
		 * this हाल, we करोn't set card->id to aव्योम collisions
		 * when running with multiple cards.
		 */
		अगर (!id[hdspm->dev] && hdspm->serial != 0xFFFFFF) अणु
			snम_लिखो(card->id, माप(card->id),
				 "HDSPMx%06x", hdspm->serial);
			snd_card_set_id(card, card->id);
		पूर्ण
	पूर्ण

	dev_dbg(card->dev, "create alsa devices.\n");
	err = snd_hdspm_create_alsa_devices(card, hdspm);
	अगर (err < 0)
		वापस err;

	snd_hdspm_initialize_midi_flush(hdspm);

	वापस 0;
पूर्ण


अटल पूर्णांक snd_hdspm_मुक्त(काष्ठा hdspm * hdspm)
अणु

	अगर (hdspm->port) अणु
		cancel_work_sync(&hdspm->midi_work);

		/* stop th audio, and cancel all पूर्णांकerrupts */
		hdspm->control_रेजिस्टर &=
		    ~(HDSPM_Start | HDSPM_AudioInterruptEnable |
		      HDSPM_Midi0InterruptEnable | HDSPM_Midi1InterruptEnable |
		      HDSPM_Midi2InterruptEnable | HDSPM_Midi3InterruptEnable);
		hdspm_ग_लिखो(hdspm, HDSPM_controlRegister,
			    hdspm->control_रेजिस्टर);
	पूर्ण

	अगर (hdspm->irq >= 0)
		मुक्त_irq(hdspm->irq, (व्योम *) hdspm);

	kमुक्त(hdspm->mixer);
	iounmap(hdspm->iobase);

	अगर (hdspm->port)
		pci_release_regions(hdspm->pci);

	अगर (pci_is_enabled(hdspm->pci))
		pci_disable_device(hdspm->pci);
	वापस 0;
पूर्ण


अटल व्योम snd_hdspm_card_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा hdspm *hdspm = card->निजी_data;

	अगर (hdspm)
		snd_hdspm_मुक्त(hdspm);
पूर्ण


अटल पूर्णांक snd_hdspm_probe(काष्ठा pci_dev *pci,
			   स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा hdspm *hdspm;
	काष्ठा snd_card *card;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev],
			   THIS_MODULE, माप(*hdspm), &card);
	अगर (err < 0)
		वापस err;

	hdspm = card->निजी_data;
	card->निजी_मुक्त = snd_hdspm_card_मुक्त;
	hdspm->dev = dev;
	hdspm->pci = pci;

	err = snd_hdspm_create(card, hdspm);
	अगर (err < 0)
		जाओ मुक्त_card;

	अगर (hdspm->io_type != MADIface) अणु
		snम_लिखो(card->लघुname, माप(card->लघुname), "%s_%x",
			hdspm->card_name, hdspm->serial);
		snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
			 "%s S/N 0x%x at 0x%lx, irq %d",
			 hdspm->card_name, hdspm->serial,
			 hdspm->port, hdspm->irq);
	पूर्ण अन्यथा अणु
		snम_लिखो(card->लघुname, माप(card->लघुname), "%s",
			 hdspm->card_name);
		snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
			 "%s at 0x%lx, irq %d",
			 hdspm->card_name, hdspm->port, hdspm->irq);
	पूर्ण

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ मुक्त_card;

	pci_set_drvdata(pci, card);

	dev++;
	वापस 0;

मुक्त_card:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_hdspm_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver hdspm_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_hdspm_ids,
	.probe = snd_hdspm_probe,
	.हटाओ = snd_hdspm_हटाओ,
पूर्ण;

module_pci_driver(hdspm_driver);
