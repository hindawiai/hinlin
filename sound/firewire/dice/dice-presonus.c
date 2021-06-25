<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// dice-presonus.c - a part of driver क्रम DICE based devices
//
// Copyright (c) 2019 Takashi Sakamoto
//
// Licensed under the terms of the GNU General Public License, version 2.

#समावेश "dice.h"

काष्ठा dice_presonus_spec अणु
	अचिन्हित पूर्णांक tx_pcm_chs[MAX_STREAMS][SND_DICE_RATE_MODE_COUNT];
	अचिन्हित पूर्णांक rx_pcm_chs[MAX_STREAMS][SND_DICE_RATE_MODE_COUNT];
	bool has_midi;
पूर्ण;

अटल स्थिर काष्ठा dice_presonus_spec dice_presonus_firesutio = अणु
	.tx_pcm_chs = अणुअणु16, 16, 0पूर्ण, अणु10, 2, 0पूर्ण पूर्ण,
	.rx_pcm_chs = अणुअणु16, 16, 0पूर्ण, अणु10, 2, 0पूर्ण पूर्ण,
	.has_midi = true,
पूर्ण;

पूर्णांक snd_dice_detect_presonus_क्रमmats(काष्ठा snd_dice *dice)
अणु
	अटल स्थिर काष्ठा अणु
		u32 model_id;
		स्थिर काष्ठा dice_presonus_spec *spec;
	पूर्ण *entry, entries[] = अणु
		अणु0x000008, &dice_presonus_firesutioपूर्ण,
	पूर्ण;
	काष्ठा fw_csr_iterator it;
	पूर्णांक key, val, model_id;
	पूर्णांक i;

	model_id = 0;
	fw_csr_iterator_init(&it, dice->unit->directory);
	जबतक (fw_csr_iterator_next(&it, &key, &val)) अणु
		अगर (key == CSR_MODEL) अणु
			model_id = val;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(entries); ++i) अणु
		entry = entries + i;
		अगर (entry->model_id == model_id)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(entries))
		वापस -ENODEV;

	स_नकल(dice->tx_pcm_chs, entry->spec->tx_pcm_chs,
	       MAX_STREAMS * SND_DICE_RATE_MODE_COUNT * माप(अचिन्हित पूर्णांक));
	स_नकल(dice->rx_pcm_chs, entry->spec->rx_pcm_chs,
	       MAX_STREAMS * SND_DICE_RATE_MODE_COUNT * माप(अचिन्हित पूर्णांक));

	अगर (entry->spec->has_midi) अणु
		dice->tx_midi_ports[0] = 1;
		dice->rx_midi_ports[0] = 1;
	पूर्ण

	वापस 0;
पूर्ण
