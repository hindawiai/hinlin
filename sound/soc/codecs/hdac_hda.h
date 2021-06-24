<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2015-18 Intel Corporation.
 */

#अगर_अघोषित __HDAC_HDA_H__
#घोषणा __HDAC_HDA_H__

क्रमागत अणु
	HDAC_ANALOG_DAI_ID = 0,
	HDAC_DIGITAL_DAI_ID,
	HDAC_ALT_ANALOG_DAI_ID,
	HDAC_HDMI_0_DAI_ID,
	HDAC_HDMI_1_DAI_ID,
	HDAC_HDMI_2_DAI_ID,
	HDAC_HDMI_3_DAI_ID,
	HDAC_LAST_DAI_ID = HDAC_HDMI_3_DAI_ID,
पूर्ण;

काष्ठा hdac_hda_pcm अणु
	पूर्णांक stream_tag[2];
	अचिन्हित पूर्णांक क्रमmat_val[2];
पूर्ण;

काष्ठा hdac_hda_priv अणु
	काष्ठा hda_codec codec;
	काष्ठा hdac_hda_pcm pcm[HDAC_LAST_DAI_ID];
	bool need_display_घातer;
पूर्ण;

काष्ठा hdac_ext_bus_ops *snd_soc_hdac_hda_get_ops(व्योम);

#पूर्ण_अगर /* __HDAC_HDA_H__ */
