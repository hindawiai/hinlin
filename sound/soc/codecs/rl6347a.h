<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * rl6347a.h - RL6347A class device shared support
 *
 * Copyright 2015 Realtek Semiconductor Corp.
 *
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */
#अगर_अघोषित __RL6347A_H__
#घोषणा __RL6347A_H__

#समावेश <sound/hda_verbs.h>

#घोषणा VERB_CMD(V, N, D) ((N << 20) | (V << 8) | D)

#घोषणा RL6347A_VENDOR_REGISTERS	0x20

#घोषणा RL6347A_COEF_INDEX\
	VERB_CMD(AC_VERB_SET_COEF_INDEX, RL6347A_VENDOR_REGISTERS, 0)
#घोषणा RL6347A_PROC_COEF\
	VERB_CMD(AC_VERB_SET_PROC_COEF, RL6347A_VENDOR_REGISTERS, 0)

काष्ठा rl6347a_priv अणु
	काष्ठा reg_शेष *index_cache;
	पूर्णांक index_cache_size;
पूर्ण;

पूर्णांक rl6347a_hw_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value);
पूर्णांक rl6347a_hw_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *value);

#पूर्ण_अगर /* __RL6347A_H__ */
