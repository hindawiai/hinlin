<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dice-alesis.c - a part of driver क्रम DICE based devices
 *
 * Copyright (c) 2018 Takashi Sakamoto
 */

#समावेश "dice.h"

अटल स्थिर अचिन्हित पूर्णांक
alesis_io14_tx_pcm_chs[MAX_STREAMS][SND_DICE_RATE_MODE_COUNT] = अणु
	अणु6, 6, 4पूर्ण,	/* Tx0 = Analog + S/PDIF. */
	अणु8, 4, 0पूर्ण,	/* Tx1 = ADAT1. */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक
alesis_io26_tx_pcm_chs[MAX_STREAMS][SND_DICE_RATE_MODE_COUNT] = अणु
	अणु10, 10, 4पूर्ण,	/* Tx0 = Analog + S/PDIF. */
	अणु16, 4, 0पूर्ण,	/* Tx1 = ADAT1 + ADAT2 (available at low rate). */
पूर्ण;

पूर्णांक snd_dice_detect_alesis_क्रमmats(काष्ठा snd_dice *dice)
अणु
	__be32 reg;
	u32 data;
	पूर्णांक i;
	पूर्णांक err;

	err = snd_dice_transaction_पढ़ो_tx(dice, TX_NUMBER_AUDIO, &reg,
					   माप(reg));
	अगर (err < 0)
		वापस err;
	data = be32_to_cpu(reg);

	अगर (data == 4 || data == 6) अणु
		स_नकल(dice->tx_pcm_chs, alesis_io14_tx_pcm_chs,
				MAX_STREAMS * SND_DICE_RATE_MODE_COUNT *
				माप(अचिन्हित पूर्णांक));
	पूर्ण अन्यथा अणु
		स_नकल(dice->tx_pcm_chs, alesis_io26_tx_pcm_chs,
				MAX_STREAMS * SND_DICE_RATE_MODE_COUNT *
				माप(अचिन्हित पूर्णांक));
	पूर्ण

	क्रम (i = 0; i < SND_DICE_RATE_MODE_COUNT; ++i)
		dice->rx_pcm_chs[0][i] = 8;

	dice->tx_midi_ports[0] = 1;
	dice->rx_midi_ports[0] = 1;

	वापस 0;
पूर्ण

पूर्णांक snd_dice_detect_alesis_mastercontrol_क्रमmats(काष्ठा snd_dice *dice)
अणु
	पूर्णांक i;

	dice->tx_pcm_chs[0][SND_DICE_RATE_MODE_LOW]	= 16;
	dice->tx_pcm_chs[1][SND_DICE_RATE_MODE_LOW]	= 12;
	dice->tx_pcm_chs[0][SND_DICE_RATE_MODE_MIDDLE]	= 12;
	dice->tx_pcm_chs[1][SND_DICE_RATE_MODE_MIDDLE]	= 4;
	dice->tx_pcm_chs[0][SND_DICE_RATE_MODE_HIGH]	= 8;
	dice->tx_pcm_chs[1][SND_DICE_RATE_MODE_HIGH]	= 0;

	क्रम (i = 0; i < SND_DICE_RATE_MODE_COUNT; ++i) अणु
		dice->rx_pcm_chs[0][i] = 6;
		dice->rx_pcm_chs[1][i] = 0;
	पूर्ण

	क्रम (i = 0; i < MAX_STREAMS; ++i) अणु
		dice->tx_midi_ports[i] = 2;
		dice->rx_midi_ports[i] = 2;
	पूर्ण

	वापस 0;
पूर्ण
