<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_EMU8000_H
#घोषणा __SOUND_EMU8000_H
/*
 *  Defines क्रम the emu8000 (AWE32/64)
 *
 *  Copyright (C) 1999 Steve Ratclअगरfe
 *  Copyright (C) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <sound/emux_synth.h>
#समावेश <sound/seq_kernel.h>

/*
 * Hardware parameters.
 */
#घोषणा EMU8000_MAX_DRAM (28 * 1024 * 1024) /* Max on-board mem is 28Mb ???*/
#घोषणा EMU8000_DRAM_OFFSET 0x200000	/* Beginning of on board ram */
#घोषणा EMU8000_CHANNELS   32	/* Number of hardware channels */
#घोषणा EMU8000_DRAM_VOICES	30	/* number of normal voices */

/* Flags to set a dma channel to पढ़ो or ग_लिखो */
#घोषणा EMU8000_RAM_READ   0
#घोषणा EMU8000_RAM_WRITE  1
#घोषणा EMU8000_RAM_CLOSE  2
#घोषणा EMU8000_RAM_MODE_MASK	0x03
#घोषणा EMU8000_RAM_RIGHT	0x10	/* use 'right' DMA channel */

क्रमागत अणु
	EMU8000_CONTROL_BASS = 0,
	EMU8000_CONTROL_TREBLE,
	EMU8000_CONTROL_CHORUS_MODE,
	EMU8000_CONTROL_REVERB_MODE,
	EMU8000_CONTROL_FM_CHORUS_DEPTH,
	EMU8000_CONTROL_FM_REVERB_DEPTH,
	EMU8000_NUM_CONTROLS,
पूर्ण;

/*
 * Structure to hold all state inक्रमmation क्रम the emu8000 driver.
 *
 * Note 1: The chip supports 32 channels in hardware this is max_channels
 * some of the channels may be used क्रम other things so max_channels is
 * the number in use क्रम wave voices.
 */
काष्ठा snd_emu8000 अणु

	काष्ठा snd_emux *emu;

	पूर्णांक index;		/* sequencer client index */
	पूर्णांक seq_ports;		/* number of sequencer ports */
	पूर्णांक fm_chorus_depth;	/* FM OPL3 chorus depth */
	पूर्णांक fm_reverb_depth;	/* FM OPL3 reverb depth */

	पूर्णांक mem_size;		/* memory size */
	अचिन्हित दीर्घ port1;	/* Port usually base+0 */
	अचिन्हित दीर्घ port2;	/* Port usually at base+0x400 */
	अचिन्हित दीर्घ port3;	/* Port usually at base+0x800 */
	काष्ठा resource *res_port1;
	काष्ठा resource *res_port2;
	काष्ठा resource *res_port3;
	अचिन्हित लघु last_reg;/* Last रेजिस्टर command */
	spinlock_t reg_lock;

	पूर्णांक dram_checked;

	काष्ठा snd_card *card;		/* The card that this beदीर्घs to */

	पूर्णांक chorus_mode;
	पूर्णांक reverb_mode;
	पूर्णांक bass_level;
	पूर्णांक treble_level;

	काष्ठा snd_util_memhdr *memhdr;

	spinlock_t control_lock;
	काष्ठा snd_kcontrol *controls[EMU8000_NUM_CONTROLS];

	काष्ठा snd_pcm *pcm; /* pcm on emu8000 wavetable */

पूर्ण;

/* sequencer device id */
#घोषणा SNDRV_SEQ_DEV_ID_EMU8000	"emu8000-synth"


/* exported functions */
पूर्णांक snd_emu8000_new(काष्ठा snd_card *card, पूर्णांक device, दीर्घ port, पूर्णांक seq_ports,
		    काष्ठा snd_seq_device **ret);
व्योम snd_emu8000_poke(काष्ठा snd_emu8000 *emu, अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक reg,
		      अचिन्हित पूर्णांक val);
अचिन्हित लघु snd_emu8000_peek(काष्ठा snd_emu8000 *emu, अचिन्हित पूर्णांक port,
				अचिन्हित पूर्णांक reg);
व्योम snd_emu8000_poke_dw(काष्ठा snd_emu8000 *emu, अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक reg,
			 अचिन्हित पूर्णांक val);
अचिन्हित पूर्णांक snd_emu8000_peek_dw(काष्ठा snd_emu8000 *emu, अचिन्हित पूर्णांक port,
				 अचिन्हित पूर्णांक reg);
व्योम snd_emu8000_dma_chan(काष्ठा snd_emu8000 *emu, पूर्णांक ch, पूर्णांक mode);

व्योम snd_emu8000_init_fm(काष्ठा snd_emu8000 *emu);

व्योम snd_emu8000_update_chorus_mode(काष्ठा snd_emu8000 *emu);
व्योम snd_emu8000_update_reverb_mode(काष्ठा snd_emu8000 *emu);
व्योम snd_emu8000_update_equalizer(काष्ठा snd_emu8000 *emu);
पूर्णांक snd_emu8000_load_chorus_fx(काष्ठा snd_emu8000 *emu, पूर्णांक mode, स्थिर व्योम __user *buf, दीर्घ len);
पूर्णांक snd_emu8000_load_reverb_fx(काष्ठा snd_emu8000 *emu, पूर्णांक mode, स्थिर व्योम __user *buf, दीर्घ len);

#पूर्ण_अगर /* __SOUND_EMU8000_H */
