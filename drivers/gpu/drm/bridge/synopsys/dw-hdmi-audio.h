<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DW_HDMI_AUDIO_H
#घोषणा DW_HDMI_AUDIO_H

काष्ठा dw_hdmi;

काष्ठा dw_hdmi_audio_data अणु
	phys_addr_t phys;
	व्योम __iomem *base;
	पूर्णांक irq;
	काष्ठा dw_hdmi *hdmi;
	u8 *eld;
पूर्ण;

काष्ठा dw_hdmi_i2s_audio_data अणु
	काष्ठा dw_hdmi *hdmi;
	u8 *eld;

	व्योम (*ग_लिखो)(काष्ठा dw_hdmi *hdmi, u8 val, पूर्णांक offset);
	u8 (*पढ़ो)(काष्ठा dw_hdmi *hdmi, पूर्णांक offset);
पूर्ण;

#पूर्ण_अगर
