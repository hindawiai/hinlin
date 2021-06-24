<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __Q6DSP_COMMON_H__
#घोषणा __Q6DSP_COMMON_H__

#समावेश <linux/kernel.h>

#घोषणा PCM_MAX_NUM_CHANNEL  8
#घोषणा PCM_CHANNEL_शून्य 0

#घोषणा PCM_CHANNEL_FL    1	/* Front left channel. */
#घोषणा PCM_CHANNEL_FR    2	/* Front right channel. */
#घोषणा PCM_CHANNEL_FC    3	/* Front center channel. */
#घोषणा PCM_CHANNEL_LS   4	/* Left surround channel. */
#घोषणा PCM_CHANNEL_RS   5	/* Right surround channel. */
#घोषणा PCM_CHANNEL_LFE  6	/* Low frequency effect channel. */
#घोषणा PCM_CHANNEL_CS   7	/* Center surround channel; Rear center ch */
#घोषणा PCM_CHANNEL_LB   8	/* Left back channel; Rear left channel. */
#घोषणा PCM_CHANNEL_RB   9	/* Right back channel; Rear right channel. */
#घोषणा PCM_CHANNELS   10	/* Top surround channel. */

पूर्णांक q6dsp_map_channels(u8 ch_map[PCM_MAX_NUM_CHANNEL], पूर्णांक ch);

#पूर्ण_अगर /* __Q6DSP_COMMON_H__ */
