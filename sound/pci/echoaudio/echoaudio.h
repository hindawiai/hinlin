<शैली गुरु>
/****************************************************************************

   Copyright Echo Digital Audio Corporation (c) 1998 - 2004
   All rights reserved
   www.echoaudio.com

   This file is part of Echo Digital Audio's generic driver library.

   Echo Digital Audio's generic driver library is मुक्त software;
   you can redistribute it and/or modअगरy it under the terms of
   the GNU General Public License as published by the Free Software
   Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License क्रम more details.

   You should have received a copy of the GNU General Public License
   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA  02111-1307, USA.

 ****************************************************************************

 Translation from C++ and adaptation क्रम use in ALSA-Driver
 were made by Giuliano Pochini <pochini@shiny.it>

 ****************************************************************************


   Here's a block diagram of how most of the cards work:

                  +-----------+
           record |           |<-------------------- Inमाला_दो
          <-------|           |        |
     PCI          | Transport |        |
     bus          |  engine   |       \|/
          ------->|           |    +-------+
            play  |           |--->|monitor|-------> Outमाला_दो
                  +-----------+    | mixer |
                                   +-------+

   The lines going to and from the PCI bus represent "pipes".  A pipe perक्रमms
   audio transport - moving audio data to and from buffers on the host via
   bus mastering.

   The inमाला_दो and outमाला_दो on the right represent input and output "busses."
   A bus is a physical, real connection to the outside world.  An example
   of a bus would be the 1/4" analog connectors on the back of Layla or
   an RCA S/PDIF connector.

   For most cards, there is a one-to-one correspondence between outमाला_दो
   and busses; that is, each inभागidual pipe is hard-wired to a single bus.

   Cards that work this way are Darla20, Gina20, Layla20, Darla24, Gina24,
   Layla24, Mona, and Indigo.


   Mia has a feature called "virtual outputs."


                  +-----------+
           record |           |<----------------------------- Inमाला_दो
          <-------|           |                  |
     PCI          | Transport |                  |
     bus          |  engine   |                 \|/
          ------->|           |   +------+   +-------+
            play  |           |-->|vmixer|-->|monitor|-------> Outमाला_दो
                  +-----------+   +------+   | mixer |
                                             +-------+


   Obviously, the dअगरference here is the box labeled "vmixer."  Vmixer is
   लघु क्रम "virtual output mixer."  For Mia, pipes are *not* hard-wired
   to a single bus; the vmixer lets you mix any pipe to any bus in any
   combination.

   Note, however, that the left-hand side of the diagram is unchanged.
   Transport works exactly the same way - the dअगरference is in the mixer stage.


   Pipes and busses are numbered starting at zero.



   Pipe index
   ==========

   A number of calls in CEchoGals refer to a "pipe index".  A pipe index is
   a unique number क्रम a pipe that unambiguously refers to a playback or record
   pipe.  Pipe indices are numbered starting with analog outमाला_दो, followed by
   digital outमाला_दो, then analog inमाला_दो, then digital inमाला_दो.

   Take Gina24 as an example:

   Pipe index

   0-7            Analog outमाला_दो (0 .. FirstDigitalBusOut-1)
   8-15           Digital outमाला_दो (FirstDigitalBusOut .. NumBussesOut-1)
   16-17          Analog inमाला_दो
   18-25          Digital inमाला_दो


   You get the pipe index by calling CEchoGals::OpenAudio; the other transport
   functions take the pipe index as a parameter.  If you need a pipe index क्रम
   some other reason, use the handy Makepipe_index method.


   Some calls take a CChannelMask parameter; CChannelMask is a handy way to
   group pipe indices.



   Digital mode चयन
   ===================

   Some cards (right now, Gina24, Layla24, and Mona) have a Digital Mode Switch
   or DMS.  Cards with a DMS can be set to one of three mutually exclusive
   digital modes: S/PDIF RCA, S/PDIF optical, or ADAT optical.

   This may create some confusion since ADAT optical is 8 channels wide and
   S/PDIF is only two channels wide.  Gina24, Layla24, and Mona handle this
   by acting as अगर they always have 8 digital outs and ins.  If you are in
   either S/PDIF mode, the last 6 channels करोn't करो anything - data sent
   out these channels is thrown away and you will always record zeros.

   Note that with Gina24, Layla24, and Mona, sample rates above 50 kHz are
   only available अगर you have the card configured क्रम S/PDIF optical or S/PDIF
   RCA.



   Double speed mode
   =================

   Some of the cards support 88.2 kHz and 96 kHz sampling (Darla24, Gina24,
   Layla24, Mona, Mia, and Indigo).  For these cards, the driver someबार has
   to worry about "double speed mode"; द्विगुन speed mode applies whenever the
   sampling rate is above 50 kHz.

   For instance, Mona and Layla24 support word घड़ी sync.  However, they
   actually support two dअगरferent word घड़ी modes - single speed (below
   50 kHz) and द्विगुन speed (above 50 kHz).  The hardware detects अगर a single
   or द्विगुन speed word घड़ी संकेत is present; the generic code uses that
   inक्रमmation to determine which mode to use.

   The generic code takes care of all this क्रम you.
*/


#अगर_अघोषित _ECHOAUDIO_H_
#घोषणा _ECHOAUDIO_H_


#समावेश "echoaudio_dsp.h"



/***********************************************************************

	PCI configuration space

***********************************************************************/

/*
 * PCI venकरोr ID and device IDs क्रम the hardware
 */
#घोषणा VENDOR_ID		0x1057
#घोषणा DEVICE_ID_56301		0x1801
#घोषणा DEVICE_ID_56361		0x3410
#घोषणा SUBVENDOR_ID		0xECC0


/*
 * Valid Echo PCI subप्रणाली card IDs
 */
#घोषणा DARLA20			0x0010
#घोषणा GINA20			0x0020
#घोषणा LAYLA20			0x0030
#घोषणा DARLA24			0x0040
#घोषणा GINA24			0x0050
#घोषणा LAYLA24			0x0060
#घोषणा MONA			0x0070
#घोषणा MIA			0x0080
#घोषणा INDIGO			0x0090
#घोषणा INDIGO_IO		0x00a0
#घोषणा INDIGO_DJ		0x00b0
#घोषणा DC8			0x00c0
#घोषणा INDIGO_IOX		0x00d0
#घोषणा INDIGO_DJX		0x00e0
#घोषणा ECHO3G			0x0100


/************************************************************************

	Array sizes and so क्रमth

***********************************************************************/

/*
 * Sizes
 */
#घोषणा ECHO_MAXAUDIOINPUTS	32	/* Max audio input channels */
#घोषणा ECHO_MAXAUDIOOUTPUTS	32	/* Max audio output channels */
#घोषणा ECHO_MAXAUDIOPIPES	32	/* Max number of input and output
					 * pipes */
#घोषणा E3G_MAX_OUTPUTS		16
#घोषणा ECHO_MAXMIDIJACKS	1	/* Max MIDI ports */
#घोषणा ECHO_MIDI_QUEUE_SZ 	512	/* Max MIDI input queue entries */
#घोषणा ECHO_MTC_QUEUE_SZ	32	/* Max MIDI समय code input queue
					 * entries */

/*
 * MIDI activity indicator समयout
 */
#घोषणा MIDI_ACTIVITY_TIMEOUT_USEC	200000


/****************************************************************************
 
   Clocks

*****************************************************************************/

/*
 * Clock numbers
 */
#घोषणा ECHO_CLOCK_INTERNAL		0
#घोषणा ECHO_CLOCK_WORD			1
#घोषणा ECHO_CLOCK_SUPER		2
#घोषणा ECHO_CLOCK_SPDIF		3
#घोषणा ECHO_CLOCK_ADAT			4
#घोषणा ECHO_CLOCK_ESYNC		5
#घोषणा ECHO_CLOCK_ESYNC96		6
#घोषणा ECHO_CLOCK_MTC			7
#घोषणा ECHO_CLOCK_NUMBER		8
#घोषणा ECHO_CLOCKS			0xffff

/*
 * Clock bit numbers - used to report capabilities and whatever घड़ीs
 * are being detected dynamically.
 */
#घोषणा ECHO_CLOCK_BIT_INTERNAL		(1 << ECHO_CLOCK_INTERNAL)
#घोषणा ECHO_CLOCK_BIT_WORD		(1 << ECHO_CLOCK_WORD)
#घोषणा ECHO_CLOCK_BIT_SUPER		(1 << ECHO_CLOCK_SUPER)
#घोषणा ECHO_CLOCK_BIT_SPDIF		(1 << ECHO_CLOCK_SPDIF)
#घोषणा ECHO_CLOCK_BIT_ADAT		(1 << ECHO_CLOCK_ADAT)
#घोषणा ECHO_CLOCK_BIT_ESYNC		(1 << ECHO_CLOCK_ESYNC)
#घोषणा ECHO_CLOCK_BIT_ESYNC96		(1 << ECHO_CLOCK_ESYNC96)
#घोषणा ECHO_CLOCK_BIT_MTC		(1<<ECHO_CLOCK_MTC)


/***************************************************************************

   Digital modes

****************************************************************************/

/*
 * Digital modes क्रम Mona, Layla24, and Gina24
 */
#घोषणा DIGITAL_MODE_NONE			0xFF
#घोषणा DIGITAL_MODE_SPDIF_RCA			0
#घोषणा DIGITAL_MODE_SPDIF_OPTICAL		1
#घोषणा DIGITAL_MODE_ADAT			2
#घोषणा DIGITAL_MODE_SPDIF_CDROM		3
#घोषणा DIGITAL_MODES				4

/*
 * Digital mode capability masks
 */
#घोषणा ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_RCA	(1 << DIGITAL_MODE_SPDIF_RCA)
#घोषणा ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_OPTICAL	(1 << DIGITAL_MODE_SPDIF_OPTICAL)
#घोषणा ECHOCAPS_HAS_DIGITAL_MODE_ADAT		(1 << DIGITAL_MODE_ADAT)
#घोषणा ECHOCAPS_HAS_DIGITAL_MODE_SPDIF_CDROM	(1 << DIGITAL_MODE_SPDIF_CDROM)


#घोषणा EXT_3GBOX_NC			0x01	/* 3G box not connected */
#घोषणा EXT_3GBOX_NOT_SET		0x02	/* 3G box not detected yet */


#घोषणा ECHOGAIN_MUTED		(-128)	/* Minimum possible gain */
#घोषणा ECHOGAIN_MINOUT		(-128)	/* Min output gain (dB) */
#घोषणा ECHOGAIN_MAXOUT		(6)	/* Max output gain (dB) */
#घोषणा ECHOGAIN_MININP		(-50)	/* Min input gain (0.5 dB) */
#घोषणा ECHOGAIN_MAXINP		(50)	/* Max input gain (0.5 dB) */

#घोषणा PIPE_STATE_STOPPED	0	/* Pipe has been reset */
#घोषणा PIPE_STATE_PAUSED	1	/* Pipe has been stopped */
#घोषणा PIPE_STATE_STARTED	2	/* Pipe has been started */
#घोषणा PIPE_STATE_PENDING	3	/* Pipe has pending start */



काष्ठा audiopipe अणु
	अस्थिर __le32 *dma_counter;	/* Commpage रेजिस्टर that contains
					 * the current dma position
					 * (lower 32 bits only)
					 */
	u32 last_period;                /* Counter position last समय a
					 * period elapsed
					 */
	u32 last_counter;		/* Used exclusively by pcm_poपूर्णांकer
					 * under PCM core locks.
					 * The last position, which is used
					 * to compute...
					 */
	u32 position;			/* ...the number of bytes tranferred
					 * by the DMA engine, modulo the
					 * buffer size
					 */
	लघु index;			/* Index of the first channel or <0
					 * अगर hw is not configured yet
					 */
	लघु पूर्णांकerleave;
	काष्ठा snd_dma_buffer sgpage;	/* Room क्रम the scatter-gather list */
	काष्ठा snd_pcm_hardware hw;
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरr;
	लघु sglist_head;
	अक्षर state;			/* pipe state */
पूर्ण;


काष्ठा audioक्रमmat अणु
	u8 पूर्णांकerleave;			/* How the data is arranged in memory:
					 * mono = 1, stereo = 2, ...
					 */
	u8 bits_per_sample;		/* 8, 16, 24, 32 (24 bits left aligned) */
	अक्षर mono_to_stereo;		/* Only used अगर पूर्णांकerleave is 1 and
					 * अगर this is an output pipe.
					 */
	अक्षर data_are_bigendian;	/* 1 = big endian, 0 = little endian */
पूर्ण;


काष्ठा echoaudio अणु
	spinlock_t lock;
	काष्ठा snd_pcm_substream *substream[DSP_MAXPIPES];
	काष्ठा mutex mode_mutex;
	u16 num_digital_modes, digital_mode_list[6];
	u16 num_घड़ी_sources, घड़ी_source_list[10];
	अचिन्हित पूर्णांक खोलोcount;  /* रक्षित by mode_mutex */
	काष्ठा snd_kcontrol *घड़ी_src_ctl;
	काष्ठा snd_pcm *analog_pcm, *digital_pcm;
	काष्ठा snd_card *card;
	स्थिर अक्षर *card_name;
	काष्ठा pci_dev *pci;
	अचिन्हित दीर्घ dsp_रेजिस्टरs_phys;
	काष्ठा resource *iores;
	काष्ठा snd_dma_buffer commpage_dma_buf;
	पूर्णांक irq;
#अगर_घोषित ECHOCARD_HAS_MIDI
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *midi_in, *midi_out;
#पूर्ण_अगर
	काष्ठा समयr_list समयr;
	अक्षर tinuse;				/* Timer in use */
	अक्षर midi_full;				/* MIDI output buffer is full */
	अक्षर can_set_rate;                      /* रक्षित by mode_mutex */
	अक्षर rate_set;                          /* रक्षित by mode_mutex */

	/* This stuff is used मुख्यly by the lowlevel code */
	काष्ठा comm_page *comm_page;	/* Virtual address of the memory
					 * seen by DSP
					 */
	u32 pipe_alloc_mask;		/* Biपंचांगask of allocated pipes */
	u32 pipe_cyclic_mask;		/* Biपंचांगask of pipes with cyclic
					 * buffers
					 */
	u32 sample_rate;		/* Card sample rate in Hz */
	u8 digital_mode;		/* Current digital mode
					 * (see DIGITAL_MODE_*)
					 */
	u8 spdअगर_status;		/* Gina20, Darla20, Darla24 - only */
	u8 घड़ी_state;			/* Gina20, Darla20, Darla24 - only */
	u8 input_घड़ी;			/* Currently selected sample घड़ी
					 * source
					 */
	u8 output_घड़ी;		/* Layla20 only */
	अक्षर meters_enabled;		/* VU-meters status */
	अक्षर asic_loaded;		/* Set true when ASIC loaded */
	अक्षर bad_board;			/* Set true अगर DSP won't load */
	अक्षर professional_spdअगर;	/* 0 = consumer; 1 = professional */
	अक्षर non_audio_spdअगर;		/* 3G - only */
	अक्षर digital_in_स्वतःmute;	/* Gina24, Layla24, Mona - only */
	अक्षर has_phantom_घातer;
	अक्षर hasnt_input_nominal_level;	/* Gina3G */
	अक्षर phantom_घातer;		/* Gina3G - only */
	अक्षर has_midi;
	अक्षर midi_input_enabled;

#अगर_घोषित ECHOCARD_ECHO3G
	/* External module -dependent pipe and bus indexes */
	अक्षर px_digital_out, px_analog_in, px_digital_in, px_num;
	अक्षर bx_digital_out, bx_analog_in, bx_digital_in, bx_num;
#पूर्ण_अगर

	अक्षर nominal_level[ECHO_MAXAUDIOPIPES];	/* True == -10dBV
						 * False == +4dBu */
	s8 input_gain[ECHO_MAXAUDIOINPUTS];	/* Input level -50..+50
						 * unit is 0.5dB */
	s8 output_gain[ECHO_MAXAUDIOOUTPUTS];	/* Output level -128..+6 dB
						 * (-128=muted) */
	s8 monitor_gain[ECHO_MAXAUDIOOUTPUTS][ECHO_MAXAUDIOINPUTS];
		/* -128..+6 dB */
	s8 vmixer_gain[ECHO_MAXAUDIOOUTPUTS][ECHO_MAXAUDIOOUTPUTS];
		/* -128..+6 dB */

	u16 digital_modes;		/* Biपंचांगask of supported modes
					 * (see ECHOCAPS_HAS_DIGITAL_MODE_*) */
	u16 input_घड़ी_प्रकारypes;		/* Suppoted input घड़ी types */
	u16 output_घड़ी_प्रकारypes;		/* Suppoted output घड़ी types -
					 * Layla20 only */
	u16 device_id, subdevice_id;
	u16 *dsp_code;			/* Current DSP code loaded,
					 * शून्य अगर nothing loaded */
	लघु dsp_code_to_load;		/* DSP code to load */
	लघु asic_code;		/* Current ASIC code */
	u32 comm_page_phys;			/* Physical address of the
						 * memory seen by DSP */
	u32 __iomem *dsp_रेजिस्टरs;		/* DSP's रेजिस्टर base */
	u32 active_mask;			/* Chs. active mask or
						 * punks out */
#अगर_घोषित CONFIG_PM_SLEEP
	स्थिर काष्ठा firmware *fw_cache[8];	/* Cached firmwares */
#पूर्ण_अगर

#अगर_घोषित ECHOCARD_HAS_MIDI
	u16 mtc_state;				/* State क्रम MIDI input parsing state machine */
	u8 midi_buffer[MIDI_IN_BUFFER_SIZE];
#पूर्ण_अगर
पूर्ण;


अटल पूर्णांक init_dsp_comm_page(काष्ठा echoaudio *chip);
अटल पूर्णांक init_line_levels(काष्ठा echoaudio *chip);
अटल पूर्णांक मुक्त_pipes(काष्ठा echoaudio *chip, काष्ठा audiopipe *pipe);
अटल पूर्णांक load_firmware(काष्ठा echoaudio *chip);
अटल पूर्णांक रुको_handshake(काष्ठा echoaudio *chip);
अटल पूर्णांक send_vector(काष्ठा echoaudio *chip, u32 command);
अटल पूर्णांक get_firmware(स्थिर काष्ठा firmware **fw_entry,
			काष्ठा echoaudio *chip, स्थिर लघु fw_index);
अटल व्योम मुक्त_firmware(स्थिर काष्ठा firmware *fw_entry,
			  काष्ठा echoaudio *chip);

#अगर_घोषित ECHOCARD_HAS_MIDI
अटल पूर्णांक enable_midi_input(काष्ठा echoaudio *chip, अक्षर enable);
अटल व्योम snd_echo_midi_output_trigger(
			काष्ठा snd_rawmidi_substream *substream, पूर्णांक up);
अटल पूर्णांक midi_service_irq(काष्ठा echoaudio *chip);
अटल पूर्णांक snd_echo_midi_create(काष्ठा snd_card *card,
				काष्ठा echoaudio *chip);
#पूर्ण_अगर


अटल अंतरभूत व्योम clear_handshake(काष्ठा echoaudio *chip)
अणु
	chip->comm_page->handshake = 0;
पूर्ण

अटल अंतरभूत u32 get_dsp_रेजिस्टर(काष्ठा echoaudio *chip, u32 index)
अणु
	वापस पढ़ोl(&chip->dsp_रेजिस्टरs[index]);
पूर्ण

अटल अंतरभूत व्योम set_dsp_रेजिस्टर(काष्ठा echoaudio *chip, u32 index,
				    u32 value)
अणु
	ग_लिखोl(value, &chip->dsp_रेजिस्टरs[index]);
पूर्ण


/* Pipe and bus indexes. PX_* and BX_* are defined as chip->px_* and chip->bx_*
क्रम 3G cards because they depend on the बाह्यal box. They are पूर्णांकeger
स्थिरants क्रम all other cards.
Never use those defines directly, use the following functions instead. */

अटल अंतरभूत पूर्णांक px_digital_out(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस PX_DIGITAL_OUT;
पूर्ण

अटल अंतरभूत पूर्णांक px_analog_in(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस PX_ANALOG_IN;
पूर्ण

अटल अंतरभूत पूर्णांक px_digital_in(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस PX_DIGITAL_IN;
पूर्ण

अटल अंतरभूत पूर्णांक px_num(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस PX_NUM;
पूर्ण

अटल अंतरभूत पूर्णांक bx_digital_out(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस BX_DIGITAL_OUT;
पूर्ण

अटल अंतरभूत पूर्णांक bx_analog_in(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस BX_ANALOG_IN;
पूर्ण

अटल अंतरभूत पूर्णांक bx_digital_in(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस BX_DIGITAL_IN;
पूर्ण

अटल अंतरभूत पूर्णांक bx_num(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस BX_NUM;
पूर्ण

अटल अंतरभूत पूर्णांक num_pipes_out(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस px_analog_in(chip);
पूर्ण

अटल अंतरभूत पूर्णांक num_pipes_in(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस px_num(chip) - px_analog_in(chip);
पूर्ण

अटल अंतरभूत पूर्णांक num_busses_out(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस bx_analog_in(chip);
पूर्ण

अटल अंतरभूत पूर्णांक num_busses_in(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस bx_num(chip) - bx_analog_in(chip);
पूर्ण

अटल अंतरभूत पूर्णांक num_analog_busses_out(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस bx_digital_out(chip);
पूर्ण

अटल अंतरभूत पूर्णांक num_analog_busses_in(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस bx_digital_in(chip) - bx_analog_in(chip);
पूर्ण

अटल अंतरभूत पूर्णांक num_digital_busses_out(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस num_busses_out(chip) - num_analog_busses_out(chip);
पूर्ण

अटल अंतरभूत पूर्णांक num_digital_busses_in(स्थिर काष्ठा echoaudio *chip)
अणु
	वापस num_busses_in(chip) - num_analog_busses_in(chip);
पूर्ण

/* The monitor array is a one-dimensional array; compute the offset
 * पूर्णांकo the array */
अटल अंतरभूत पूर्णांक monitor_index(स्थिर काष्ठा echoaudio *chip, पूर्णांक out, पूर्णांक in)
अणु
	वापस out * num_busses_in(chip) + in;
पूर्ण

#पूर्ण_अगर /* _ECHOAUDIO_H_ */
