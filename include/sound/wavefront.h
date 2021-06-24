<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_WAVEFRONT_H__
#घोषणा __SOUND_WAVEFRONT_H__

/*
 *  Driver क्रम Turtle Beach Wavefront cards (Maui,Tropez,Tropez+)
 *
 *  Copyright (c) by Paul Barton-Davis <pbd@op.net>
 */

#अगर (!defined(__GNUC__) && !defined(__GNUG__))

     You will not be able to compile this file correctly without gcc, because
     it is necessary to pack the "wavefront_alias" काष्ठाure to a size
     of 22 bytes, corresponding to 16-bit alignment (as would have been
     the हाल on the original platक्रमm, MS-DOS). If this is not करोne,
     then WavePatch-क्रमmat files cannot be पढ़ो/written correctly.
     The method used to करो this here ("__attribute__((packed)") is
     completely compiler dependent.
     
     All other wavefront_* types end up aligned to 32 bit values and
     still have the same (correct) size.

#अन्यथा

     /* However, note that as of G++ 2.7.3.2, g++ was unable to
	correctly parse *type* __attribute__ tags. It will करो the
	right thing अगर we use the "packed" attribute on each काष्ठा
	member, which has the same semantics anyway. 
     */

#पूर्ण_अगर /* __GNUC__ */

/***************************** WARNING ********************************
  PLEASE DO NOT MODIFY THIS खाता IN ANY WAY THAT AFFECTS ITS ABILITY TO 
  BE USED WITH EITHER C *OR* C++.
 **********************************************************************/

#अगर_अघोषित NUM_MIDIKEYS 
#घोषणा NUM_MIDIKEYS 128
#पूर्ण_अगर  /* NUM_MIDIKEYS */

#अगर_अघोषित NUM_MIDICHANNELS
#घोषणा NUM_MIDICHANNELS 16
#पूर्ण_अगर  /* NUM_MIDICHANNELS */

/* These are very useful/important. the original wavefront पूर्णांकerface
   was developed on a 16 bit प्रणाली, where माप(पूर्णांक) = 2
   bytes. Defining things like this makes the code much more portable, and
   easier to understand without having to toggle back and क्रमth
   between a 16-bit view of the world and a 32-bit one. 
 */   

#अगर_अघोषित __KERNEL__
/* keep them क्रम compatibility */
प्रकार लघु s16;
प्रकार अचिन्हित लघु u16;
प्रकार पूर्णांक s32;
प्रकार अचिन्हित पूर्णांक u32;
प्रकार अक्षर s8;
प्रकार अचिन्हित अक्षर u8;
प्रकार s16 INT16;
प्रकार u16 UINT16;
प्रकार s32 INT32;
प्रकार u32 UINT32;
प्रकार s8 CHAR8;
प्रकार u8 UCHAR8;
#पूर्ण_अगर

/* Pseuकरो-commands not part of the WaveFront command set.
   These are used क्रम various driver controls and direct
   hardware control.
 */

#घोषणा WFC_DEBUG_DRIVER                0
#घोषणा WFC_FX_IOCTL                    1
#घोषणा WFC_PATCH_STATUS                2
#घोषणा WFC_PROGRAM_STATUS              3
#घोषणा WFC_SAMPLE_STATUS               4
#घोषणा WFC_DISABLE_INTERRUPTS          5
#घोषणा WFC_ENABLE_INTERRUPTS           6
#घोषणा WFC_INTERRUPT_STATUS            7
#घोषणा WFC_ROMSAMPLES_RDONLY           8
#घोषणा WFC_IDENTIFY_SLOT_TYPE          9

/* Wavefront synth commands
 */

#घोषणा WFC_DOWNLOAD_SAMPLE		0x80
#घोषणा WFC_DOWNLOAD_BLOCK		0x81
#घोषणा WFC_DOWNLOAD_MULTISAMPLE	0x82
#घोषणा WFC_DOWNLOAD_SAMPLE_ALIAS	0x83
#घोषणा WFC_DELETE_SAMPLE		0x84
#घोषणा WFC_REPORT_FREE_MEMORY		0x85
#घोषणा WFC_DOWNLOAD_PATCH		0x86
#घोषणा WFC_DOWNLOAD_PROGRAM		0x87
#घोषणा WFC_SET_SYNTHVOL		0x89
#घोषणा WFC_SET_NVOICES			0x8B
#घोषणा WFC_DOWNLOAD_DRUM		0x90
#घोषणा WFC_GET_SYNTHVOL		0x92
#घोषणा WFC_GET_NVOICES			0x94
#घोषणा WFC_DISABLE_CHANNEL		0x9A
#घोषणा WFC_ENABLE_CHANNEL		0x9B
#घोषणा WFC_MISYNTH_OFF			0x9D
#घोषणा WFC_MISYNTH_ON			0x9E
#घोषणा WFC_FIRMWARE_VERSION		0x9F
#घोषणा WFC_GET_NSAMPLES		0xA0
#घोषणा WFC_DISABLE_DRUM_PROGRAM	0xA2
#घोषणा WFC_UPLOAD_PATCH		0xA3
#घोषणा WFC_UPLOAD_PROGRAM		0xA4
#घोषणा WFC_SET_TUNING			0xA6
#घोषणा WFC_GET_TUNING			0xA7
#घोषणा WFC_VMIDI_ON			0xA8
#घोषणा WFC_VMIDI_OFF			0xA9
#घोषणा WFC_MIDI_STATUS			0xAA
#घोषणा WFC_GET_CHANNEL_STATUS		0xAB
#घोषणा WFC_DOWNLOAD_SAMPLE_HEADER	0xAC
#घोषणा WFC_UPLOAD_SAMPLE_HEADER	0xAD
#घोषणा WFC_UPLOAD_MULTISAMPLE		0xAE
#घोषणा WFC_UPLOAD_SAMPLE_ALIAS		0xAF
#घोषणा WFC_IDENTIFY_SAMPLE_TYPE	0xB0
#घोषणा WFC_DOWNLOAD_EDRUM_PROGRAM	0xB1
#घोषणा WFC_UPLOAD_EDRUM_PROGRAM	0xB2
#घोषणा WFC_SET_EDRUM_CHANNEL		0xB3
#घोषणा WFC_INSTOUT_LEVELS		0xB4
#घोषणा WFC_PEAKOUT_LEVELS		0xB5
#घोषणा WFC_REPORT_CHANNEL_PROGRAMS	0xB6
#घोषणा WFC_HARDWARE_VERSION		0xCF
#घोषणा WFC_UPLOAD_SAMPLE_PARAMS	0xD7
#घोषणा WFC_DOWNLOAD_OS			0xF1
#घोषणा WFC_NOOP                        0xFF

#घोषणा WF_MAX_SAMPLE   512
#घोषणा WF_MAX_PATCH    256
#घोषणा WF_MAX_PROGRAM  128

#घोषणा WF_SECTION_MAX  44   /* दीर्घest OS section length */

/* # of bytes we send to the board when sending it various kinds of
   substantive data, such as samples, patches and programs.
*/

#घोषणा WF_PROGRAM_BYTES 32
#घोषणा WF_PATCH_BYTES 132
#घोषणा WF_SAMPLE_BYTES 27
#घोषणा WF_SAMPLE_HDR_BYTES 25
#घोषणा WF_ALIAS_BYTES 25
#घोषणा WF_DRUM_BYTES 9
#घोषणा WF_MSAMPLE_BYTES 259 /* (MIDI_KEYS * 2) + 3 */

#घोषणा WF_ACK     0x80
#घोषणा WF_DMA_ACK 0x81

/* OR-values क्रम MIDI status bits */

#घोषणा WF_MIDI_VIRTUAL_ENABLED 0x1
#घोषणा WF_MIDI_VIRTUAL_IS_EXTERNAL 0x2
#घोषणा WF_MIDI_IN_TO_SYNTH_DISABLED 0x4

/* slot indexes क्रम काष्ठा address_info: makes code a little more mnemonic */

#घोषणा WF_SYNTH_SLOT         0
#घोषणा WF_INTERNAL_MIDI_SLOT 1
#घोषणा WF_EXTERNAL_MIDI_SLOT 2

/* Magic MIDI bytes used to चयन I/O streams on the ICS2115 MPU401
   emulation. Note these NEVER show up in output from the device and
   should NEVER be used in input unless Virtual MIDI mode has been 
   disabled. If they करो show up as input, the results are unpredictable.
*/

#घोषणा WF_EXTERNAL_SWITCH  0xFD
#घोषणा WF_INTERNAL_SWITCH  0xF9

/* Debugging flags */

#घोषणा WF_DEBUG_CMD 0x1
#घोषणा WF_DEBUG_DATA 0x2
#घोषणा WF_DEBUG_LOAD_PATCH 0x4
#घोषणा WF_DEBUG_IO 0x8

/* WavePatch file क्रमmat stuff */

#घोषणा WF_WAVEPATCH_VERSION     120;  /*  Current version number (1.2)  */
#घोषणा WF_MAX_COMMENT           64    /*  Comment length */
#घोषणा WF_NUM_LAYERS            4
#घोषणा WF_NAME_LENGTH           32
#घोषणा WF_SOURCE_LENGTH         260

#घोषणा BankFileID     "Bank"
#घोषणा DrumkitFileID  "DrumKit"
#घोषणा ProgramFileID  "Program"

काष्ठा wf_envelope
अणु
    u8 attack_समय:7;
    u8 Unused1:1;

    u8 decay1_समय:7;
    u8 Unused2:1;

    u8 decay2_समय:7;
    u8 Unused3:1;

    u8 sustain_समय:7;
    u8 Unused4:1;

    u8 release_समय:7;
    u8 Unused5:1;

    u8 release2_समय:7;
    u8 Unused6:1;

    s8 attack_level;
    s8 decay1_level;
    s8 decay2_level;
    s8 sustain_level;
    s8 release_level;

    u8 attack_velocity:7;
    u8 Unused7:1;

    u8 volume_velocity:7;
    u8 Unused8:1;

    u8 keyboard_scaling:7;
    u8 Unused9:1;
पूर्ण;
प्रकार काष्ठा wf_envelope wavefront_envelope;

काष्ठा wf_lfo
अणु
    u8 sample_number;

    u8 frequency:7;
    u8 Unused1:1;

    u8 am_src:4;
    u8 fm_src:4;

    s8 fm_amount;
    s8 am_amount;
    s8 start_level;
    s8 end_level;

    u8 ramp_delay:7;
    u8 wave_restart:1; /* क्रम LFO2 only */

    u8 ramp_समय:7;
    u8 Unused2:1;
पूर्ण;
प्रकार काष्ठा wf_lfo wavefront_lfo;

काष्ठा wf_patch
अणु
    s16  frequency_bias;         /*  ** THIS IS IN MOTOROLA FORMAT!! ** */

    u8 amplitude_bias:7;
    u8 Unused1:1;

    u8 portamento:7;
    u8 Unused2:1;

    u8 sample_number;

    u8 pitch_bend:4;
    u8 sample_msb:1;
    u8 Unused3:3;

    u8 mono:1;
    u8 retrigger:1;
    u8 nohold:1;
    u8 restart:1;
    u8 filterconfig:2; /* SDK says "not used" */
    u8 reuse:1;
    u8 reset_lfo:1;    

    u8 fm_src2:4;
    u8 fm_src1:4;   

    s8 fm_amount1;
    s8 fm_amount2;

    u8 am_src:4;
    u8 Unused4:4;

    s8 am_amount;

    u8 fc1_mode:4;
    u8 fc2_mode:4;

    s8 fc1_mod_amount;
    s8 fc1_keyboard_scaling;
    s8 fc1_bias;
    s8 fc2_mod_amount;
    s8 fc2_keyboard_scaling;
    s8 fc2_bias;

    u8 अक्रमomizer:7;
    u8 Unused5:1;

    काष्ठा wf_envelope envelope1;
    काष्ठा wf_envelope envelope2;
    काष्ठा wf_lfo lfo1;
    काष्ठा wf_lfo lfo2;
पूर्ण;
प्रकार काष्ठा wf_patch wavefront_patch;

काष्ठा wf_layer
अणु
    u8 patch_number;

    u8 mix_level:7;
    u8 mute:1;

    u8 split_poपूर्णांक:7;
    u8 play_below:1;

    u8 pan_mod_src:2;
    u8 pan_or_mod:1;
    u8 pan:4;
    u8 split_type:1;
पूर्ण;
प्रकार काष्ठा wf_layer wavefront_layer;

काष्ठा wf_program
अणु
    काष्ठा wf_layer layer[WF_NUM_LAYERS];
पूर्ण;
प्रकार काष्ठा wf_program wavefront_program;

काष्ठा wf_sample_offset
अणु
    s32 Fraction:4;
    s32 Integer:20;
    s32 Unused:8;
पूर्ण;
प्रकार काष्ठा wf_sample_offset wavefront_sample_offset;          
     
/* Sample slot types */

#घोषणा WF_ST_SAMPLE      0
#घोषणा WF_ST_MULTISAMPLE 1
#घोषणा WF_ST_ALIAS       2
#घोषणा WF_ST_EMPTY       3

/* pseuकरो's */

#घोषणा WF_ST_DRUM        4
#घोषणा WF_ST_PROGRAM     5
#घोषणा WF_ST_PATCH       6
#घोषणा WF_ST_SAMPLEHDR   7

#घोषणा WF_ST_MASK        0xf

/* Flags क्रम slot status. These occupy the upper bits of the same byte
   as a sample type.
*/

#घोषणा WF_SLOT_USED      0x80   /* XXX करोn't rely on this being accurate */
#घोषणा WF_SLOT_FILLED    0x40
#घोषणा WF_SLOT_ROM       0x20

#घोषणा WF_SLOT_MASK      0xf0

/* channel स्थिरants */

#घोषणा WF_CH_MONO  0
#घोषणा WF_CH_LEFT  1
#घोषणा WF_CH_RIGHT 2

/* Sample क्रमmats */

#घोषणा LINEAR_16BIT 0
#घोषणा WHITE_NOISE  1
#घोषणा LINEAR_8BIT  2
#घोषणा MULAW_8BIT   3

#घोषणा WF_SAMPLE_IS_8BIT(smpl) ((smpl)->SampleResolution&2)


/* 

  Because most/all of the sample data we pass in via poपूर्णांकers has
  never been copied (just mmap-ed पूर्णांकo user space straight from the
  disk), it would be nice to allow handling of multi-channel sample
  data without क्रमcing user-level extraction of the relevant bytes.
  
  So, we need a way of specअगरying which channel to use (the WaveFront
  only handles mono samples in a given slot), and the only way to करो
  this without using some काष्ठा other than wavefront_sample as the
  पूर्णांकerface is the awful hack of using the unused bits in a
  wavefront_sample:
  
  Val      Meaning
  ---      -------
  0        no channel selection (use channel 1, sample is MONO)
  1        use first channel, and skip one
  2        use second channel, and skip one
  3        use third channel, and skip two
  4        use fourth channel, skip three
  5        use fअगरth channel, skip four
  6        use six channel, skip five


  This can handle up to 4 channels, and anyone करोwnloading >4 channels
  of sample data just to select one of them needs to find some tools
  like sox ...

  NOTE: values 0, 1 and 2 correspond to WF_CH_* above. This is 
  important.

*/

#घोषणा WF_SET_CHANNEL(samp,chn) \
 (samp)->Unused1 = chn & 0x1; \
 (samp)->Unused2 = chn & 0x2; \
 (samp)->Unused3 = chn & 0x4 
  
#घोषणा WF_GET_CHANNEL(samp) \
  (((samp)->Unused3 << 2)|((samp)->Unused2<<1)|(samp)->Unused1)
  
प्रकार काष्ठा wf_sample अणु
    काष्ठा wf_sample_offset sampleStartOffset;
    काष्ठा wf_sample_offset loopStartOffset;
    काष्ठा wf_sample_offset loopEndOffset;
    काष्ठा wf_sample_offset sampleEndOffset;
    s16 FrequencyBias;
    u8 SampleResolution:2;  /* sample_क्रमmat */
    u8 Unused1:1;
    u8 Loop:1;
    u8 Bidirectional:1;
    u8 Unused2:1;
    u8 Reverse:1;
    u8 Unused3:1;
पूर्ण wavefront_sample;

प्रकार काष्ठा wf_multisample अणु
    s16 NumberOfSamples;   /* log2 of the number of samples */
    s16 SampleNumber[NUM_MIDIKEYS];
पूर्ण wavefront_multisample;

प्रकार काष्ठा wf_alias अणु
    s16 OriginalSample;

    काष्ठा wf_sample_offset sampleStartOffset;
    काष्ठा wf_sample_offset loopStartOffset;
    काष्ठा wf_sample_offset sampleEndOffset;
    काष्ठा wf_sample_offset loopEndOffset;

    s16  FrequencyBias;

    u8 SampleResolution:2;
    u8 Unused1:1;
    u8 Loop:1;
    u8 Bidirectional:1;
    u8 Unused2:1;
    u8 Reverse:1;
    u8 Unused3:1;
    
    /* This काष्ठाure is meant to be padded only to 16 bits on their
       original. Of course, whoever wrote their करोcumentation didn't
       realize that माप(काष्ठा) can be >=
       sum(माप(काष्ठा-fields)) and so thought that giving a C level
       description of the काष्ठाs used in WavePatch files was
       sufficient. I suppose it was, as दीर्घ as you remember the 
       standard 16->32 bit issues.
    */

    u8 sixteen_bit_padding;
पूर्ण __attribute__((packed)) wavefront_alias;

प्रकार काष्ठा wf_drum अणु
    u8 PatchNumber;
    u8 MixLevel:7;
    u8 Unmute:1;
    u8 Group:4;
    u8 Unused1:4;
    u8 PanModSource:2;
    u8 PanModulated:1;
    u8 PanAmount:4;
    u8 Unused2:1;
पूर्ण wavefront_drum;

प्रकार काष्ठा wf_drumkit अणु
    काष्ठा wf_drum drum[NUM_MIDIKEYS];
पूर्ण wavefront_drumkit;

प्रकार काष्ठा wf_channel_programs अणु
    u8 Program[NUM_MIDICHANNELS];
पूर्ण wavefront_channel_programs;

/* How to get MIDI channel status from the data वापसed by
   a WFC_GET_CHANNEL_STATUS command (a काष्ठा wf_channel_programs)
*/

#घोषणा WF_CHANNEL_STATUS(ch,wcp) (wcp)[(ch/7)] & (1<<((ch)%7))

प्रकार जोड़ wf_any अणु
    wavefront_sample s;
    wavefront_multisample ms;
    wavefront_alias a;
    wavefront_program pr;
    wavefront_patch p;
    wavefront_drum d;
पूर्ण wavefront_any;

/* Hannu Solvainen hoped that his "patch_info" काष्ठा in soundcard.h
   might work क्रम other wave-table based patch loading situations.
   Alas, his fears were correct. The WaveFront करोesn't even come with
   just "patches", but several dअगरferent kind of काष्ठाures that
   control the sound generation process.
 */

प्रकार काष्ठा wf_patch_info अणु
    
    /* the first two fields are used by the OSS "patch loading" पूर्णांकerface
       only, and are unused by the current user-level library.
    */

    s16   key;               /* Use WAVEFRONT_PATCH here */
    u16  devno;             /* fill in when sending */
    u8  subkey;            /* WF_ST_अणुSAMPLE,ALIAS,etc.पूर्ण */

#घोषणा WAVEFRONT_FIND_FREE_SAMPLE_SLOT 999

    u16  number;            /* patch/sample/prog number */

    u32  size;              /* size of any data included in 
				  one of the fields in `hdrptr', or
				  as `dataptr'.

				  NOTE: क्रम actual samples, this is
				  the size of the *SELECTED CHANNEL*
				  even अगर more data is actually available.
				  
				  So, a stereo sample (2 channels) of
				  6000 bytes total has `size' = 3000.

				  See the macros and comments क्रम
				  WF_अणुGET,SETपूर्ण_CHANNEL above.

			       */
    wavefront_any __user *hdrptr;      /* user-space ptr to hdr bytes */
    u16 __user *dataptr;            /* actual sample data */

    wavefront_any hdr;          /* kernel-space copy of hdr bytes */         
पूर्ण wavefront_patch_info;

/* The maximum number of bytes we will ever move to or from user space
   in response to a WFC_* command.  This obviously करोesn't cover
   actual sample data.
*/

#घोषणा WF_MAX_READ माप(wavefront_multisample)
#घोषणा WF_MAX_WRITE माप(wavefront_multisample)

/*
   This allows us to execute any WF command except the करोwnload/upload
   ones, which are handled dअगरferently due to copyin/copyout issues as
   well as data-nybbling to/from the card.
 */

प्रकार काष्ठा wavefront_control अणु
    पूर्णांक cmd;                           /* WFC_* */
    अक्षर status;                       /* वापस status to user-space */
    अचिन्हित अक्षर rbuf[WF_MAX_READ];   /* bytes पढ़ो from card */
    अचिन्हित अक्षर wbuf[WF_MAX_WRITE];  /* bytes written to card */
पूर्ण wavefront_control;

#घोषणा WFCTL_WFCMD    0x1
#घोषणा WFCTL_LOAD_SPP 0x2

/* Modulator table */

#घोषणा WF_MOD_LFO1      0
#घोषणा WF_MOD_LFO2      1
#घोषणा WF_MOD_ENV1      2
#घोषणा WF_MOD_ENV2      3
#घोषणा WF_MOD_KEYBOARD  4
#घोषणा WF_MOD_LOGKEY    5
#घोषणा WF_MOD_VELOCITY  6
#घोषणा WF_MOD_LOGVEL    7
#घोषणा WF_MOD_RANDOM    8
#घोषणा WF_MOD_PRESSURE  9
#घोषणा WF_MOD_MOD_WHEEL 10
#घोषणा WF_MOD_1         WF_MOD_MOD_WHEEL 
#घोषणा WF_MOD_BREATH    11
#घोषणा WF_MOD_2         WF_MOD_BREATH
#घोषणा WF_MOD_FOOT      12
#घोषणा WF_MOD_4         WF_MOD_FOOT
#घोषणा WF_MOD_VOLUME    13
#घोषणा WF_MOD_7         WF_MOD_VOLUME
#घोषणा WF_MOD_PAN       14
#घोषणा WF_MOD_10        WF_MOD_PAN
#घोषणा WF_MOD_EXPR      15
#घोषणा WF_MOD_11        WF_MOD_EXPR

/* FX-related material */

प्रकार काष्ठा wf_fx_info अणु
    पूर्णांक request;             /* see list below */
    दीर्घ data[4];             /* we करोn't need much */
पूर्ण wavefront_fx_info;

/* support क्रम each of these will be क्रमthcoming once I or someone 
   अन्यथा has figured out which of the addresses on page 6 and page 7 of 
   the YSS225 control each parameter. Incidentally, these come from
   the Winकरोws driver पूर्णांकerface, but again, Turtle Beach didn't
   करोcument the API to use them.
*/

#घोषणा WFFX_SETOUTGAIN		        0
#घोषणा WFFX_SETSTEREOOUTGAIN		1
#घोषणा WFFX_SETREVERBIN1GAIN		2
#घोषणा WFFX_SETREVERBIN2GAIN		3
#घोषणा WFFX_SETREVERBIN3GAIN		4
#घोषणा WFFX_SETCHORUSINPORT		5
#घोषणा WFFX_SETREVERBIN1PORT		6
#घोषणा WFFX_SETREVERBIN2PORT		7
#घोषणा WFFX_SETREVERBIN3PORT		8
#घोषणा WFFX_SETEFFECTPORT		9
#घोषणा WFFX_SETAUXPORT		        10
#घोषणा WFFX_SETREVERBTYPE		11
#घोषणा WFFX_SETREVERBDELAY		12
#घोषणा WFFX_SETCHORUSLFO		13
#घोषणा WFFX_SETCHORUSPMD		14
#घोषणा WFFX_SETCHORUSAMD		15
#घोषणा WFFX_SETEFFECT		        16
#घोषणा WFFX_SETBASEALL		        17
#घोषणा WFFX_SETREVERBALL		18
#घोषणा WFFX_SETCHORUSALL		20
#घोषणा WFFX_SETREVERBDEF		22
#घोषणा WFFX_SETCHORUSDEF		23
#घोषणा WFFX_DELAYSETINGAIN		24
#घोषणा WFFX_DELAYSETFBGAIN	        25
#घोषणा WFFX_DELAYSETFBLPF		26
#घोषणा WFFX_DELAYSETGAIN		27
#घोषणा WFFX_DELAYSETTIME		28
#घोषणा WFFX_DELAYSETFBTIME		29
#घोषणा WFFX_DELAYSETALL		30
#घोषणा WFFX_DELAYSETDEF		32
#घोषणा WFFX_SDELAYSETINGAIN		33
#घोषणा WFFX_SDELAYSETFBGAIN		34
#घोषणा WFFX_SDELAYSETFBLPF		35
#घोषणा WFFX_SDELAYSETGAIN		36
#घोषणा WFFX_SDELAYSETTIME		37
#घोषणा WFFX_SDELAYSETFBTIME		38
#घोषणा WFFX_SDELAYSETALL		39
#घोषणा WFFX_SDELAYSETDEF		41
#घोषणा WFFX_DEQSETINGAIN		42
#घोषणा WFFX_DEQSETFILTER		43
#घोषणा WFFX_DEQSETALL		        44
#घोषणा WFFX_DEQSETDEF		        46
#घोषणा WFFX_MUTE		        47
#घोषणा WFFX_FLANGESETBALANCE	        48	
#घोषणा WFFX_FLANGESETDELAY		49
#घोषणा WFFX_FLANGESETDWFFX_TH		50
#घोषणा WFFX_FLANGESETFBGAIN		51
#घोषणा WFFX_FLANGESETINGAIN		52
#घोषणा WFFX_FLANGESETLFO		53
#घोषणा WFFX_FLANGESETALL		54
#घोषणा WFFX_FLANGESETDEF		56
#घोषणा WFFX_PITCHSETSHIFT		57
#घोषणा WFFX_PITCHSETBALANCE		58
#घोषणा WFFX_PITCHSETALL		59
#घोषणा WFFX_PITCHSETDEF		61
#घोषणा WFFX_SRSSETINGAIN		62
#घोषणा WFFX_SRSSETSPACE		63
#घोषणा WFFX_SRSSETCENTER		64
#घोषणा WFFX_SRSSETGAIN		        65
#घोषणा WFFX_SRSSETMODE	        	66
#घोषणा WFFX_SRSSETDEF		        68

/* Allow direct user-space control over FX memory/coefficient data.
   In theory this could be used to करोwnload the FX microprogram,
   but it would be a little slower, and involve some weird code.
 */

#घोषणा WFFX_MEMSET              69

#पूर्ण_अगर /* __SOUND_WAVEFRONT_H__ */
