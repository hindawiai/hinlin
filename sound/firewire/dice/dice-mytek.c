<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dice-mytek.c - a part of driver क्रम DICE based devices
 *
 * Copyright (c) 2018 Melvin Vermeeren
 */

#समावेश "dice.h"

काष्ठा dice_mytek_spec अणु
	अचिन्हित पूर्णांक tx_pcm_chs[MAX_STREAMS][SND_DICE_RATE_MODE_COUNT];
	अचिन्हित पूर्णांक rx_pcm_chs[MAX_STREAMS][SND_DICE_RATE_MODE_COUNT];
पूर्ण;

अटल स्थिर काष्ठा dice_mytek_spec stereo_192_dsd_dac = अणु
	/* AES, TOSLINK, SPDIF, ADAT inमाला_दो on device */
	.tx_pcm_chs = अणुअणु8, 8, 8पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	/* PCM 44.1-192, native DSD64/DSD128 to device */
	.rx_pcm_chs = अणुअणु4, 4, 4पूर्ण, अणु0, 0, 0पूर्ण पूर्ण
पूर्ण;

/*
 * Mytek has a few other firewire-capable devices, though newer models appear
 * to lack the port more often than not. As I करोn't have access to any of them
 * they are missing here. An example is the Mytek 8x192 ADDA, which is DICE.
 */

पूर्णांक snd_dice_detect_mytek_क्रमmats(काष्ठा snd_dice *dice)
अणु
	पूर्णांक i;
	स्थिर काष्ठा dice_mytek_spec *dev;

	dev = &stereo_192_dsd_dac;

	स_नकल(dice->tx_pcm_chs, dev->tx_pcm_chs,
	       MAX_STREAMS * SND_DICE_RATE_MODE_COUNT * माप(अचिन्हित पूर्णांक));
	स_नकल(dice->rx_pcm_chs, dev->rx_pcm_chs,
	       MAX_STREAMS * SND_DICE_RATE_MODE_COUNT * माप(अचिन्हित पूर्णांक));

	क्रम (i = 0; i < MAX_STREAMS; ++i) अणु
		dice->tx_midi_ports[i] = 0;
		dice->rx_midi_ports[i] = 0;
	पूर्ण

	वापस 0;
पूर्ण
