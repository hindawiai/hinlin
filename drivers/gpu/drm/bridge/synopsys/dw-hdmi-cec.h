<शैली गुरु>
#अगर_अघोषित DW_HDMI_CEC_H
#घोषणा DW_HDMI_CEC_H

काष्ठा dw_hdmi;

काष्ठा dw_hdmi_cec_ops अणु
	व्योम (*ग_लिखो)(काष्ठा dw_hdmi *hdmi, u8 val, पूर्णांक offset);
	u8 (*पढ़ो)(काष्ठा dw_hdmi *hdmi, पूर्णांक offset);
	व्योम (*enable)(काष्ठा dw_hdmi *hdmi);
	व्योम (*disable)(काष्ठा dw_hdmi *hdmi);
पूर्ण;

काष्ठा dw_hdmi_cec_data अणु
	काष्ठा dw_hdmi *hdmi;
	स्थिर काष्ठा dw_hdmi_cec_ops *ops;
	पूर्णांक irq;
पूर्ण;

#पूर्ण_अगर
