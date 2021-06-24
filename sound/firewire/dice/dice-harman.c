<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// dice-harman.c - a part of driver क्रम DICE based devices
//
// Copyright (c) 2021 Takashi Sakamoto
//
// Licensed under the terms of the GNU General Public License, version 2.

#समावेश "dice.h"

पूर्णांक snd_dice_detect_harman_क्रमmats(काष्ठा snd_dice *dice)
अणु
	पूर्णांक i;

	// Lexicon I-ONYX FW810s supports sampling transfer frequency up to
	// 96.0 kHz, 12 PCM channels and 1 MIDI channel in its first tx stream
	// , 10 PCM channels and 1 MIDI channel in its first rx stream क्रम all
	// of the frequencies.
	क्रम (i = 0; i < 2; ++i) अणु
		dice->tx_pcm_chs[0][i] = 12;
		dice->tx_midi_ports[0] = 1;
		dice->rx_pcm_chs[0][i] = 10;
		dice->rx_midi_ports[0] = 1;
	पूर्ण

	वापस 0;
पूर्ण
