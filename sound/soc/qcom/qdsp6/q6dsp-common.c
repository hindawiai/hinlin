<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2011-2017, The Linux Foundation. All rights reserved.
// Copyright (c) 2018, Linaro Limited

#समावेश "q6dsp-common.h"
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>

पूर्णांक q6dsp_map_channels(u8 ch_map[PCM_MAX_NUM_CHANNEL], पूर्णांक ch)
अणु
	स_रखो(ch_map, 0, PCM_MAX_NUM_CHANNEL);

	चयन (ch) अणु
	हाल 1:
		ch_map[0] = PCM_CHANNEL_FC;
		अवरोध;
	हाल 2:
		ch_map[0] = PCM_CHANNEL_FL;
		ch_map[1] = PCM_CHANNEL_FR;
		अवरोध;
	हाल 3:
		ch_map[0] = PCM_CHANNEL_FL;
		ch_map[1] = PCM_CHANNEL_FR;
		ch_map[2] = PCM_CHANNEL_FC;
		अवरोध;
	हाल 4:
		ch_map[0] = PCM_CHANNEL_FL;
		ch_map[1] = PCM_CHANNEL_FR;
		ch_map[2] = PCM_CHANNEL_LS;
		ch_map[3] = PCM_CHANNEL_RS;
		अवरोध;
	हाल 5:
		ch_map[0] = PCM_CHANNEL_FL;
		ch_map[1] = PCM_CHANNEL_FR;
		ch_map[2] = PCM_CHANNEL_FC;
		ch_map[3] = PCM_CHANNEL_LS;
		ch_map[4] = PCM_CHANNEL_RS;
		अवरोध;
	हाल 6:
		ch_map[0] = PCM_CHANNEL_FL;
		ch_map[1] = PCM_CHANNEL_FR;
		ch_map[2] = PCM_CHANNEL_LFE;
		ch_map[3] = PCM_CHANNEL_FC;
		ch_map[4] = PCM_CHANNEL_LS;
		ch_map[5] = PCM_CHANNEL_RS;
		अवरोध;
	हाल 8:
		ch_map[0] = PCM_CHANNEL_FL;
		ch_map[1] = PCM_CHANNEL_FR;
		ch_map[2] = PCM_CHANNEL_LFE;
		ch_map[3] = PCM_CHANNEL_FC;
		ch_map[4] = PCM_CHANNEL_LS;
		ch_map[5] = PCM_CHANNEL_RS;
		ch_map[6] = PCM_CHANNEL_LB;
		ch_map[7] = PCM_CHANNEL_RB;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(q6dsp_map_channels);
MODULE_LICENSE("GPL v2");
