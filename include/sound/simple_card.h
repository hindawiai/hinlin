<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * ASoC simple sound card support
 *
 * Copyright (C) 2012 Renesas Solutions Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */

#अगर_अघोषित __SIMPLE_CARD_H
#घोषणा __SIMPLE_CARD_H

#समावेश <sound/soc.h>
#समावेश <sound/simple_card_utils.h>

काष्ठा asoc_simple_card_info अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *card;
	स्थिर अक्षर *codec;
	स्थिर अक्षर *platक्रमm;

	अचिन्हित पूर्णांक daअगरmt;
	काष्ठा asoc_simple_dai cpu_dai;
	काष्ठा asoc_simple_dai codec_dai;
पूर्ण;

#पूर्ण_अगर /* __SIMPLE_CARD_H */
