<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dice-tc_electronic.c - a part of driver क्रम DICE based devices
 *
 * Copyright (c) 2018 Takashi Sakamoto
 */

#समावेश "dice.h"

काष्ठा dice_tc_spec अणु
	अचिन्हित पूर्णांक tx_pcm_chs[MAX_STREAMS][SND_DICE_RATE_MODE_COUNT];
	अचिन्हित पूर्णांक rx_pcm_chs[MAX_STREAMS][SND_DICE_RATE_MODE_COUNT];
	bool has_midi;
पूर्ण;

अटल स्थिर काष्ठा dice_tc_spec desktop_konnekt6 = अणु
	.tx_pcm_chs = अणुअणु6, 6, 2पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	.rx_pcm_chs = अणुअणु6, 6, 4पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	.has_midi = false,
पूर्ण;

अटल स्थिर काष्ठा dice_tc_spec impact_twin = अणु
	.tx_pcm_chs = अणुअणु14, 10, 6पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	.rx_pcm_chs = अणुअणु14, 10, 6पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	.has_midi = true,
पूर्ण;

अटल स्थिर काष्ठा dice_tc_spec konnekt_8 = अणु
	.tx_pcm_chs = अणुअणु4, 4, 3पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	.rx_pcm_chs = अणुअणु4, 4, 3पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	.has_midi = true,
पूर्ण;

अटल स्थिर काष्ठा dice_tc_spec konnekt_24d = अणु
	.tx_pcm_chs = अणुअणु16, 16, 6पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	.rx_pcm_chs = अणुअणु16, 16, 6पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	.has_midi = true,
पूर्ण;

अटल स्थिर काष्ठा dice_tc_spec konnekt_live = अणु
	.tx_pcm_chs = अणुअणु16, 16, 6पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	.rx_pcm_chs = अणुअणु16, 16, 6पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	.has_midi = true,
पूर्ण;

अटल स्थिर काष्ठा dice_tc_spec studio_konnekt_48 = अणु
	.tx_pcm_chs = अणुअणु16, 16, 8पूर्ण, अणु16, 16, 7पूर्ण पूर्ण,
	.rx_pcm_chs = अणुअणु16, 16, 8पूर्ण, अणु14, 14, 7पूर्ण पूर्ण,
	.has_midi = true,
पूर्ण;

अटल स्थिर काष्ठा dice_tc_spec digital_konnekt_x32 = अणु
	.tx_pcm_chs = अणुअणु16, 16, 4पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	.rx_pcm_chs = अणुअणु16, 16, 4पूर्ण, अणु0, 0, 0पूर्ण पूर्ण,
	.has_midi = false,
पूर्ण;

पूर्णांक snd_dice_detect_tcelectronic_क्रमmats(काष्ठा snd_dice *dice)
अणु
	अटल स्थिर काष्ठा अणु
		u32 model_id;
		स्थिर काष्ठा dice_tc_spec *spec;
	पूर्ण *entry, entries[] = अणु
		अणु0x00000020, &konnekt_24dपूर्ण,
		अणु0x00000021, &konnekt_8पूर्ण,
		अणु0x00000022, &studio_konnekt_48पूर्ण,
		अणु0x00000023, &konnekt_liveपूर्ण,
		अणु0x00000024, &desktop_konnekt6पूर्ण,
		अणु0x00000027, &impact_twinपूर्ण,
		अणु0x00000030, &digital_konnekt_x32पूर्ण,
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
