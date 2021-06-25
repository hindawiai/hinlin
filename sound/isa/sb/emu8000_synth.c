<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *     and (c) 1999 Steve Ratclअगरfe <steve@parabola.demon.co.uk>
 *  Copyright (C) 1999-2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Emu8000 synth plug-in routine
 */

#समावेश "emu8000_local.h"
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Takashi Iwai, Steve Ratcliffe");
MODULE_DESCRIPTION("Emu8000 synth plug-in routine");
MODULE_LICENSE("GPL");

/*----------------------------------------------------------------*/

/*
 * create a new hardware dependent device क्रम Emu8000
 */
अटल पूर्णांक snd_emu8000_probe(काष्ठा device *_dev)
अणु
	काष्ठा snd_seq_device *dev = to_seq_dev(_dev);
	काष्ठा snd_emu8000 *hw;
	काष्ठा snd_emux *emu;

	hw = *(काष्ठा snd_emu8000**)SNDRV_SEQ_DEVICE_ARGPTR(dev);
	अगर (hw == शून्य)
		वापस -EINVAL;

	अगर (hw->emu)
		वापस -EBUSY; /* alपढ़ोy exists..? */

	अगर (snd_emux_new(&emu) < 0)
		वापस -ENOMEM;

	hw->emu = emu;
	snd_emu8000_ops_setup(hw);

	emu->hw = hw;
	emu->max_voices = EMU8000_DRAM_VOICES;
	emu->num_ports = hw->seq_ports;

	अगर (hw->memhdr) अणु
		snd_prपूर्णांकk(KERN_ERR "memhdr is already initialized!?\n");
		snd_util_memhdr_मुक्त(hw->memhdr);
	पूर्ण
	hw->memhdr = snd_util_memhdr_new(hw->mem_size);
	अगर (hw->memhdr == शून्य) अणु
		snd_emux_मुक्त(emu);
		hw->emu = शून्य;
		वापस -ENOMEM;
	पूर्ण

	emu->memhdr = hw->memhdr;
	emu->midi_ports = hw->seq_ports < 2 ? hw->seq_ports : 2; /* number of virmidi ports */
	emu->midi_devidx = 1;
	emu->linear_panning = 1;
	emu->hwdep_idx = 2; /* FIXED */

	अगर (snd_emux_रेजिस्टर(emu, dev->card, hw->index, "Emu8000") < 0) अणु
		snd_emux_मुक्त(emu);
		snd_util_memhdr_मुक्त(hw->memhdr);
		hw->emu = शून्य;
		hw->memhdr = शून्य;
		वापस -ENOMEM;
	पूर्ण

	अगर (hw->mem_size > 0)
		snd_emu8000_pcm_new(dev->card, hw, 1);

	dev->driver_data = hw;

	वापस 0;
पूर्ण


/*
 * मुक्त all resources
 */
अटल पूर्णांक snd_emu8000_हटाओ(काष्ठा device *_dev)
अणु
	काष्ठा snd_seq_device *dev = to_seq_dev(_dev);
	काष्ठा snd_emu8000 *hw;

	अगर (dev->driver_data == शून्य)
		वापस 0; /* no synth was allocated actually */

	hw = dev->driver_data;
	अगर (hw->pcm)
		snd_device_मुक्त(dev->card, hw->pcm);
	snd_emux_मुक्त(hw->emu);
	snd_util_memhdr_मुक्त(hw->memhdr);
	hw->emu = शून्य;
	hw->memhdr = शून्य;
	वापस 0;
पूर्ण

/*
 *  INIT part
 */

अटल काष्ठा snd_seq_driver emu8000_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.probe = snd_emu8000_probe,
		.हटाओ = snd_emu8000_हटाओ,
	पूर्ण,
	.id = SNDRV_SEQ_DEV_ID_EMU8000,
	.argsize = माप(काष्ठा snd_emu8000 *),
पूर्ण;

module_snd_seq_driver(emu8000_driver);
