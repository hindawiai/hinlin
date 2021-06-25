<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Dummy soundcard क्रम भव rawmidi devices
 *
 *  Copyright (c) 2000 by Takashi Iwai <tiwai@suse.de>
 */

/*
 * VIRTUAL RAW MIDI DEVICE CARDS
 *
 * This dummy card contains up to 4 भव rawmidi devices.
 * They are not real rawmidi devices but just associated with sequencer
 * clients, so that any input/output sources can be connected as a raw
 * MIDI device arbitrary.
 * Also, multiple access is allowed to a single rawmidi device.
 *
 * Typical usage is like following:
 * - Load snd-virmidi module.
 *	# modprobe snd-virmidi index=2
 *   Then, sequencer clients 72:0 to 75:0 will be created, which are
 *   mapped from /dev/snd/midiC1D0 to /dev/snd/midiC1D3, respectively.
 *
 * - Connect input/output via aconnect.
 *	% aconnect 64:0 72:0	# keyboard input redirection 64:0 -> 72:0
 *	% aconnect 72:0 65:0	# output device redirection 72:0 -> 65:0
 *
 * - Run application using a midi device (eg. /dev/snd/midiC1D0)
 */

#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/seq_kernel.h>
#समावेश <sound/seq_virmidi.h>
#समावेश <sound/initval.h>

/* hack: OSS defines midi_devs, so undefine it (versioned symbols) */
#अघोषित midi_devs

MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("Dummy soundcard for virtual rawmidi devices");
MODULE_LICENSE("GPL");

#घोषणा MAX_MIDI_DEVICES	4

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = अणु1, [1 ... (SNDRV_CARDS - 1)] = 0पूर्ण;
अटल पूर्णांक midi_devs[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 4पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for virmidi soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for virmidi soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable this soundcard.");
module_param_array(midi_devs, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(midi_devs, "MIDI devices # (1-4)");

काष्ठा snd_card_virmidi अणु
	काष्ठा snd_card *card;
	काष्ठा snd_rawmidi *midi[MAX_MIDI_DEVICES];
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[SNDRV_CARDS];


अटल पूर्णांक snd_virmidi_probe(काष्ठा platक्रमm_device *devptr)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_card_virmidi *vmidi;
	पूर्णांक idx, err;
	पूर्णांक dev = devptr->id;

	err = snd_card_new(&devptr->dev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_card_virmidi), &card);
	अगर (err < 0)
		वापस err;
	vmidi = card->निजी_data;
	vmidi->card = card;

	अगर (midi_devs[dev] > MAX_MIDI_DEVICES) अणु
		snd_prपूर्णांकk(KERN_WARNING
			   "too much midi devices for virmidi %d: force to use %d\n",
			   dev, MAX_MIDI_DEVICES);
		midi_devs[dev] = MAX_MIDI_DEVICES;
	पूर्ण
	क्रम (idx = 0; idx < midi_devs[dev]; idx++) अणु
		काष्ठा snd_rawmidi *rmidi;
		काष्ठा snd_virmidi_dev *rdev;

		err = snd_virmidi_new(card, idx, &rmidi);
		अगर (err < 0)
			जाओ __nodev;
		rdev = rmidi->निजी_data;
		vmidi->midi[idx] = rmidi;
		म_नकल(rmidi->name, "Virtual Raw MIDI");
		rdev->seq_mode = SNDRV_VIRMIDI_SEQ_DISPATCH;
	पूर्ण

	म_नकल(card->driver, "VirMIDI");
	म_नकल(card->लघुname, "VirMIDI");
	प्र_लिखो(card->दीर्घname, "Virtual MIDI Card %i", dev + 1);

	err = snd_card_रेजिस्टर(card);
	अगर (!err) अणु
		platक्रमm_set_drvdata(devptr, card);
		वापस 0;
	पूर्ण
__nodev:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक snd_virmidi_हटाओ(काष्ठा platक्रमm_device *devptr)
अणु
	snd_card_मुक्त(platक्रमm_get_drvdata(devptr));
	वापस 0;
पूर्ण

#घोषणा SND_VIRMIDI_DRIVER	"snd_virmidi"

अटल काष्ठा platक्रमm_driver snd_virmidi_driver = अणु
	.probe		= snd_virmidi_probe,
	.हटाओ		= snd_virmidi_हटाओ,
	.driver		= अणु
		.name	= SND_VIRMIDI_DRIVER,
	पूर्ण,
पूर्ण;

अटल व्योम snd_virmidi_unरेजिस्टर_all(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(devices); ++i)
		platक्रमm_device_unरेजिस्टर(devices[i]);
	platक्रमm_driver_unरेजिस्टर(&snd_virmidi_driver);
पूर्ण

अटल पूर्णांक __init alsa_card_virmidi_init(व्योम)
अणु
	पूर्णांक i, cards, err;

	err = platक्रमm_driver_रेजिस्टर(&snd_virmidi_driver);
	अगर (err < 0)
		वापस err;

	cards = 0;
	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		काष्ठा platक्रमm_device *device;

		अगर (!enable[i])
			जारी;
		device = platक्रमm_device_रेजिस्टर_simple(SND_VIRMIDI_DRIVER,
							 i, शून्य, 0);
		अगर (IS_ERR(device))
			जारी;
		अगर (!platक्रमm_get_drvdata(device)) अणु
			platक्रमm_device_unरेजिस्टर(device);
			जारी;
		पूर्ण
		devices[i] = device;
		cards++;
	पूर्ण
	अगर (!cards) अणु
#अगर_घोषित MODULE
		prपूर्णांकk(KERN_ERR "Card-VirMIDI soundcard not found or device busy\n");
#पूर्ण_अगर
		snd_virmidi_unरेजिस्टर_all();
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_card_virmidi_निकास(व्योम)
अणु
	snd_virmidi_unरेजिस्टर_all();
पूर्ण

module_init(alsa_card_virmidi_init)
module_निकास(alsa_card_virmidi_निकास)
