<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Routines क्रम control of EMU10K1 WaveTable synth
 */

#समावेश "emu10k1_synth_local.h"
#समावेश <linux/init.h>
#समावेश <linux/module.h>

MODULE_AUTHOR("Takashi Iwai");
MODULE_DESCRIPTION("Routines for control of EMU10K1 WaveTable synth");
MODULE_LICENSE("GPL");

/*
 * create a new hardware dependent device क्रम Emu10k1
 */
अटल पूर्णांक snd_emu10k1_synth_probe(काष्ठा device *_dev)
अणु
	काष्ठा snd_seq_device *dev = to_seq_dev(_dev);
	काष्ठा snd_emux *emux;
	काष्ठा snd_emu10k1 *hw;
	काष्ठा snd_emu10k1_synth_arg *arg;
	अचिन्हित दीर्घ flags;

	arg = SNDRV_SEQ_DEVICE_ARGPTR(dev);
	अगर (arg == शून्य)
		वापस -EINVAL;

	अगर (arg->seq_ports <= 0)
		वापस 0; /* nothing */
	अगर (arg->max_voices < 1)
		arg->max_voices = 1;
	अन्यथा अगर (arg->max_voices > 64)
		arg->max_voices = 64;

	अगर (snd_emux_new(&emux) < 0)
		वापस -ENOMEM;

	snd_emu10k1_ops_setup(emux);
	hw = arg->hwptr;
	emux->hw = hw;
	emux->max_voices = arg->max_voices;
	emux->num_ports = arg->seq_ports;
	emux->pitch_shअगरt = -501;
	emux->memhdr = hw->memhdr;
	/* maximum two ports */
	emux->midi_ports = arg->seq_ports < 2 ? arg->seq_ports : 2;
	/* audigy has two बाह्यal midis */
	emux->midi_devidx = hw->audigy ? 2 : 1;
	emux->linear_panning = 0;
	emux->hwdep_idx = 2; /* FIXED */

	अगर (snd_emux_रेजिस्टर(emux, dev->card, arg->index, "Emu10k1") < 0) अणु
		snd_emux_मुक्त(emux);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&hw->voice_lock, flags);
	hw->synth = emux;
	hw->get_synth_voice = snd_emu10k1_synth_get_voice;
	spin_unlock_irqrestore(&hw->voice_lock, flags);

	dev->driver_data = emux;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_synth_हटाओ(काष्ठा device *_dev)
अणु
	काष्ठा snd_seq_device *dev = to_seq_dev(_dev);
	काष्ठा snd_emux *emux;
	काष्ठा snd_emu10k1 *hw;
	अचिन्हित दीर्घ flags;

	अगर (dev->driver_data == शून्य)
		वापस 0; /* not रेजिस्टरed actually */

	emux = dev->driver_data;

	hw = emux->hw;
	spin_lock_irqsave(&hw->voice_lock, flags);
	hw->synth = शून्य;
	hw->get_synth_voice = शून्य;
	spin_unlock_irqrestore(&hw->voice_lock, flags);

	snd_emux_मुक्त(emux);
	वापस 0;
पूर्ण

/*
 *  INIT part
 */

अटल काष्ठा snd_seq_driver emu10k1_synth_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.probe = snd_emu10k1_synth_probe,
		.हटाओ = snd_emu10k1_synth_हटाओ,
	पूर्ण,
	.id = SNDRV_SEQ_DEV_ID_EMU10K1_SYNTH,
	.argsize = माप(काष्ठा snd_emu10k1_synth_arg),
पूर्ण;

module_snd_seq_driver(emu10k1_synth_driver);
