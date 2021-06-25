<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Vincent Abriou <vincent.abriou@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश <sound/hdmi-codec.h>

#समावेश "sti_hdmi.h"
#समावेश "sti_hdmi_tx3g4c28phy.h"
#समावेश "sti_vtg.h"

#घोषणा HDMI_CFG                        0x0000
#घोषणा HDMI_INT_EN                     0x0004
#घोषणा HDMI_INT_STA                    0x0008
#घोषणा HDMI_INT_CLR                    0x000C
#घोषणा HDMI_STA                        0x0010
#घोषणा HDMI_ACTIVE_VID_XMIN            0x0100
#घोषणा HDMI_ACTIVE_VID_XMAX            0x0104
#घोषणा HDMI_ACTIVE_VID_YMIN            0x0108
#घोषणा HDMI_ACTIVE_VID_YMAX            0x010C
#घोषणा HDMI_DFLT_CHL0_DAT              0x0110
#घोषणा HDMI_DFLT_CHL1_DAT              0x0114
#घोषणा HDMI_DFLT_CHL2_DAT              0x0118
#घोषणा HDMI_AUDIO_CFG                  0x0200
#घोषणा HDMI_SPDIF_FIFO_STATUS          0x0204
#घोषणा HDMI_SW_DI_1_HEAD_WORD          0x0210
#घोषणा HDMI_SW_DI_1_PKT_WORD0          0x0214
#घोषणा HDMI_SW_DI_1_PKT_WORD1          0x0218
#घोषणा HDMI_SW_DI_1_PKT_WORD2          0x021C
#घोषणा HDMI_SW_DI_1_PKT_WORD3          0x0220
#घोषणा HDMI_SW_DI_1_PKT_WORD4          0x0224
#घोषणा HDMI_SW_DI_1_PKT_WORD5          0x0228
#घोषणा HDMI_SW_DI_1_PKT_WORD6          0x022C
#घोषणा HDMI_SW_DI_CFG                  0x0230
#घोषणा HDMI_SAMPLE_FLAT_MASK           0x0244
#घोषणा HDMI_AUDN                       0x0400
#घोषणा HDMI_AUD_CTS                    0x0404
#घोषणा HDMI_SW_DI_2_HEAD_WORD          0x0600
#घोषणा HDMI_SW_DI_2_PKT_WORD0          0x0604
#घोषणा HDMI_SW_DI_2_PKT_WORD1          0x0608
#घोषणा HDMI_SW_DI_2_PKT_WORD2          0x060C
#घोषणा HDMI_SW_DI_2_PKT_WORD3          0x0610
#घोषणा HDMI_SW_DI_2_PKT_WORD4          0x0614
#घोषणा HDMI_SW_DI_2_PKT_WORD5          0x0618
#घोषणा HDMI_SW_DI_2_PKT_WORD6          0x061C
#घोषणा HDMI_SW_DI_3_HEAD_WORD          0x0620
#घोषणा HDMI_SW_DI_3_PKT_WORD0          0x0624
#घोषणा HDMI_SW_DI_3_PKT_WORD1          0x0628
#घोषणा HDMI_SW_DI_3_PKT_WORD2          0x062C
#घोषणा HDMI_SW_DI_3_PKT_WORD3          0x0630
#घोषणा HDMI_SW_DI_3_PKT_WORD4          0x0634
#घोषणा HDMI_SW_DI_3_PKT_WORD5          0x0638
#घोषणा HDMI_SW_DI_3_PKT_WORD6          0x063C

#घोषणा HDMI_IFRAME_SLOT_AVI            1
#घोषणा HDMI_IFRAME_SLOT_AUDIO          2
#घोषणा HDMI_IFRAME_SLOT_VENDOR         3

#घोषणा  XCAT(prefix, x, suffix)        prefix ## x ## suffix
#घोषणा  HDMI_SW_DI_N_HEAD_WORD(x)      XCAT(HDMI_SW_DI_, x, _HEAD_WORD)
#घोषणा  HDMI_SW_DI_N_PKT_WORD0(x)      XCAT(HDMI_SW_DI_, x, _PKT_WORD0)
#घोषणा  HDMI_SW_DI_N_PKT_WORD1(x)      XCAT(HDMI_SW_DI_, x, _PKT_WORD1)
#घोषणा  HDMI_SW_DI_N_PKT_WORD2(x)      XCAT(HDMI_SW_DI_, x, _PKT_WORD2)
#घोषणा  HDMI_SW_DI_N_PKT_WORD3(x)      XCAT(HDMI_SW_DI_, x, _PKT_WORD3)
#घोषणा  HDMI_SW_DI_N_PKT_WORD4(x)      XCAT(HDMI_SW_DI_, x, _PKT_WORD4)
#घोषणा  HDMI_SW_DI_N_PKT_WORD5(x)      XCAT(HDMI_SW_DI_, x, _PKT_WORD5)
#घोषणा  HDMI_SW_DI_N_PKT_WORD6(x)      XCAT(HDMI_SW_DI_, x, _PKT_WORD6)

#घोषणा HDMI_SW_DI_MAX_WORD             7

#घोषणा HDMI_IFRAME_DISABLED            0x0
#घोषणा HDMI_IFRAME_SINGLE_SHOT         0x1
#घोषणा HDMI_IFRAME_FIELD               0x2
#घोषणा HDMI_IFRAME_FRAME               0x3
#घोषणा HDMI_IFRAME_MASK                0x3
#घोषणा HDMI_IFRAME_CFG_DI_N(x, n)       ((x) << ((n-1)*4)) /* n from 1 to 6 */

#घोषणा HDMI_CFG_DEVICE_EN              BIT(0)
#घोषणा HDMI_CFG_HDMI_NOT_DVI           BIT(1)
#घोषणा HDMI_CFG_HDCP_EN                BIT(2)
#घोषणा HDMI_CFG_ESS_NOT_OESS           BIT(3)
#घोषणा HDMI_CFG_H_SYNC_POL_NEG         BIT(4)
#घोषणा HDMI_CFG_V_SYNC_POL_NEG         BIT(6)
#घोषणा HDMI_CFG_422_EN                 BIT(8)
#घोषणा HDMI_CFG_FIFO_OVERRUN_CLR       BIT(12)
#घोषणा HDMI_CFG_FIFO_UNDERRUN_CLR      BIT(13)
#घोषणा HDMI_CFG_SW_RST_EN              BIT(31)

#घोषणा HDMI_INT_GLOBAL                 BIT(0)
#घोषणा HDMI_INT_SW_RST                 BIT(1)
#घोषणा HDMI_INT_PIX_CAP                BIT(3)
#घोषणा HDMI_INT_HOT_PLUG               BIT(4)
#घोषणा HDMI_INT_DLL_LCK                BIT(5)
#घोषणा HDMI_INT_NEW_FRAME              BIT(6)
#घोषणा HDMI_INT_GENCTRL_PKT            BIT(7)
#घोषणा HDMI_INT_AUDIO_FIFO_XRUN        BIT(8)
#घोषणा HDMI_INT_SINK_TERM_PRESENT      BIT(11)

#घोषणा HDMI_DEFAULT_INT (HDMI_INT_SINK_TERM_PRESENT \
			| HDMI_INT_DLL_LCK \
			| HDMI_INT_HOT_PLUG \
			| HDMI_INT_GLOBAL)

#घोषणा HDMI_WORKING_INT (HDMI_INT_SINK_TERM_PRESENT \
			| HDMI_INT_AUDIO_FIFO_XRUN \
			| HDMI_INT_GENCTRL_PKT \
			| HDMI_INT_NEW_FRAME \
			| HDMI_INT_DLL_LCK \
			| HDMI_INT_HOT_PLUG \
			| HDMI_INT_PIX_CAP \
			| HDMI_INT_SW_RST \
			| HDMI_INT_GLOBAL)

#घोषणा HDMI_STA_SW_RST                 BIT(1)

#घोषणा HDMI_AUD_CFG_8CH		BIT(0)
#घोषणा HDMI_AUD_CFG_SPDIF_DIV_2	BIT(1)
#घोषणा HDMI_AUD_CFG_SPDIF_DIV_3	BIT(2)
#घोषणा HDMI_AUD_CFG_SPDIF_CLK_DIV_4	(BIT(1) | BIT(2))
#घोषणा HDMI_AUD_CFG_CTS_CLK_256FS	BIT(12)
#घोषणा HDMI_AUD_CFG_DTS_INVALID	BIT(16)
#घोषणा HDMI_AUD_CFG_ONE_BIT_INVALID	(BIT(18) | BIT(19) | BIT(20) |  BIT(21))
#घोषणा HDMI_AUD_CFG_CH12_VALID	BIT(28)
#घोषणा HDMI_AUD_CFG_CH34_VALID	BIT(29)
#घोषणा HDMI_AUD_CFG_CH56_VALID	BIT(30)
#घोषणा HDMI_AUD_CFG_CH78_VALID	BIT(31)

/* sample flat mask */
#घोषणा HDMI_SAMPLE_FLAT_NO	 0
#घोषणा HDMI_SAMPLE_FLAT_SP0 BIT(0)
#घोषणा HDMI_SAMPLE_FLAT_SP1 BIT(1)
#घोषणा HDMI_SAMPLE_FLAT_SP2 BIT(2)
#घोषणा HDMI_SAMPLE_FLAT_SP3 BIT(3)
#घोषणा HDMI_SAMPLE_FLAT_ALL (HDMI_SAMPLE_FLAT_SP0 | HDMI_SAMPLE_FLAT_SP1 |\
			      HDMI_SAMPLE_FLAT_SP2 | HDMI_SAMPLE_FLAT_SP3)

#घोषणा HDMI_INFOFRAME_HEADER_TYPE(x)    (((x) & 0xff) <<  0)
#घोषणा HDMI_INFOFRAME_HEADER_VERSION(x) (((x) & 0xff) <<  8)
#घोषणा HDMI_INFOFRAME_HEADER_LEN(x)     (((x) & 0x0f) << 16)

काष्ठा sti_hdmi_connector अणु
	काष्ठा drm_connector drm_connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा sti_hdmi *hdmi;
	काष्ठा drm_property *colorspace_property;
पूर्ण;

#घोषणा to_sti_hdmi_connector(x) \
	container_of(x, काष्ठा sti_hdmi_connector, drm_connector)

अटल स्थिर काष्ठा drm_prop_क्रमागत_list colorspace_mode_names[] = अणु
	अणु HDMI_COLORSPACE_RGB, "rgb" पूर्ण,
	अणु HDMI_COLORSPACE_YUV422, "yuv422" पूर्ण,
	अणु HDMI_COLORSPACE_YUV444, "yuv444" पूर्ण,
पूर्ण;

u32 hdmi_पढ़ो(काष्ठा sti_hdmi *hdmi, पूर्णांक offset)
अणु
	वापस पढ़ोl(hdmi->regs + offset);
पूर्ण

व्योम hdmi_ग_लिखो(काष्ठा sti_hdmi *hdmi, u32 val, पूर्णांक offset)
अणु
	ग_लिखोl(val, hdmi->regs + offset);
पूर्ण

/**
 * HDMI पूर्णांकerrupt handler thपढ़ोed
 *
 * @irq: irq number
 * @arg: connector काष्ठाure
 */
अटल irqवापस_t hdmi_irq_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा sti_hdmi *hdmi = arg;

	/* Hot plug/unplug IRQ */
	अगर (hdmi->irq_status & HDMI_INT_HOT_PLUG) अणु
		hdmi->hpd = पढ़ोl(hdmi->regs + HDMI_STA) & HDMI_STA_HOT_PLUG;
		अगर (hdmi->drm_dev)
			drm_helper_hpd_irq_event(hdmi->drm_dev);
	पूर्ण

	/* Sw reset and PLL lock are exclusive so we can use the same
	 * event to संकेत them
	 */
	अगर (hdmi->irq_status & (HDMI_INT_SW_RST | HDMI_INT_DLL_LCK)) अणु
		hdmi->event_received = true;
		wake_up_पूर्णांकerruptible(&hdmi->रुको_event);
	पूर्ण

	/* Audio FIFO underrun IRQ */
	अगर (hdmi->irq_status & HDMI_INT_AUDIO_FIFO_XRUN)
		DRM_INFO("Warning: audio FIFO underrun occurs!\n");

	वापस IRQ_HANDLED;
पूर्ण

/**
 * HDMI पूर्णांकerrupt handler
 *
 * @irq: irq number
 * @arg: connector काष्ठाure
 */
अटल irqवापस_t hdmi_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा sti_hdmi *hdmi = arg;

	/* पढ़ो पूर्णांकerrupt status */
	hdmi->irq_status = hdmi_पढ़ो(hdmi, HDMI_INT_STA);

	/* clear पूर्णांकerrupt status */
	hdmi_ग_लिखो(hdmi, hdmi->irq_status, HDMI_INT_CLR);

	/* क्रमce sync bus ग_लिखो */
	hdmi_पढ़ो(hdmi, HDMI_INT_STA);

	वापस IRQ_WAKE_THREAD;
पूर्ण

/**
 * Set hdmi active area depending on the drm display mode selected
 *
 * @hdmi: poपूर्णांकer on the hdmi पूर्णांकernal काष्ठाure
 */
अटल व्योम hdmi_active_area(काष्ठा sti_hdmi *hdmi)
अणु
	u32 xmin, xmax;
	u32 ymin, ymax;

	xmin = sti_vtg_get_pixel_number(hdmi->mode, 1);
	xmax = sti_vtg_get_pixel_number(hdmi->mode, hdmi->mode.hdisplay);
	ymin = sti_vtg_get_line_number(hdmi->mode, 0);
	ymax = sti_vtg_get_line_number(hdmi->mode, hdmi->mode.vdisplay - 1);

	hdmi_ग_लिखो(hdmi, xmin, HDMI_ACTIVE_VID_XMIN);
	hdmi_ग_लिखो(hdmi, xmax, HDMI_ACTIVE_VID_XMAX);
	hdmi_ग_लिखो(hdmi, ymin, HDMI_ACTIVE_VID_YMIN);
	hdmi_ग_लिखो(hdmi, ymax, HDMI_ACTIVE_VID_YMAX);
पूर्ण

/**
 * Overall hdmi configuration
 *
 * @hdmi: poपूर्णांकer on the hdmi पूर्णांकernal काष्ठाure
 */
अटल व्योम hdmi_config(काष्ठा sti_hdmi *hdmi)
अणु
	u32 conf;

	DRM_DEBUG_DRIVER("\n");

	/* Clear overrun and underrun fअगरo */
	conf = HDMI_CFG_FIFO_OVERRUN_CLR | HDMI_CFG_FIFO_UNDERRUN_CLR;

	/* Select encryption type and the framing mode */
	conf |= HDMI_CFG_ESS_NOT_OESS;
	अगर (hdmi->hdmi_monitor)
		conf |= HDMI_CFG_HDMI_NOT_DVI;

	/* Set Hsync polarity */
	अगर (hdmi->mode.flags & DRM_MODE_FLAG_NHSYNC) अणु
		DRM_DEBUG_DRIVER("H Sync Negative\n");
		conf |= HDMI_CFG_H_SYNC_POL_NEG;
	पूर्ण

	/* Set Vsync polarity */
	अगर (hdmi->mode.flags & DRM_MODE_FLAG_NVSYNC) अणु
		DRM_DEBUG_DRIVER("V Sync Negative\n");
		conf |= HDMI_CFG_V_SYNC_POL_NEG;
	पूर्ण

	/* Enable HDMI */
	conf |= HDMI_CFG_DEVICE_EN;

	hdmi_ग_लिखो(hdmi, conf, HDMI_CFG);
पूर्ण

/*
 * Helper to reset info frame
 *
 * @hdmi: poपूर्णांकer on the hdmi पूर्णांकernal काष्ठाure
 * @slot: infoframe to reset
 */
अटल व्योम hdmi_infoframe_reset(काष्ठा sti_hdmi *hdmi,
				 u32 slot)
अणु
	u32 val, i;
	u32 head_offset, pack_offset;

	चयन (slot) अणु
	हाल HDMI_IFRAME_SLOT_AVI:
		head_offset = HDMI_SW_DI_N_HEAD_WORD(HDMI_IFRAME_SLOT_AVI);
		pack_offset = HDMI_SW_DI_N_PKT_WORD0(HDMI_IFRAME_SLOT_AVI);
		अवरोध;
	हाल HDMI_IFRAME_SLOT_AUDIO:
		head_offset = HDMI_SW_DI_N_HEAD_WORD(HDMI_IFRAME_SLOT_AUDIO);
		pack_offset = HDMI_SW_DI_N_PKT_WORD0(HDMI_IFRAME_SLOT_AUDIO);
		अवरोध;
	हाल HDMI_IFRAME_SLOT_VENDOR:
		head_offset = HDMI_SW_DI_N_HEAD_WORD(HDMI_IFRAME_SLOT_VENDOR);
		pack_offset = HDMI_SW_DI_N_PKT_WORD0(HDMI_IFRAME_SLOT_VENDOR);
		अवरोध;
	शेष:
		DRM_ERROR("unsupported infoframe slot: %#x\n", slot);
		वापस;
	पूर्ण

	/* Disable transmission क्रम the selected slot */
	val = hdmi_पढ़ो(hdmi, HDMI_SW_DI_CFG);
	val &= ~HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, slot);
	hdmi_ग_लिखो(hdmi, val, HDMI_SW_DI_CFG);

	/* Reset info frame रेजिस्टरs */
	hdmi_ग_लिखो(hdmi, 0x0, head_offset);
	क्रम (i = 0; i < HDMI_SW_DI_MAX_WORD; i += माप(u32))
		hdmi_ग_लिखो(hdmi, 0x0, pack_offset + i);
पूर्ण

/**
 * Helper to concatenate infoframe in 32 bits word
 *
 * @ptr: poपूर्णांकer on the hdmi पूर्णांकernal काष्ठाure
 * @size: size to ग_लिखो
 */
अटल अंतरभूत अचिन्हित पूर्णांक hdmi_infoframe_subpack(स्थिर u8 *ptr, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ value = 0;
	माप_प्रकार i;

	क्रम (i = size; i > 0; i--)
		value = (value << 8) | ptr[i - 1];

	वापस value;
पूर्ण

/**
 * Helper to ग_लिखो info frame
 *
 * @hdmi: poपूर्णांकer on the hdmi पूर्णांकernal काष्ठाure
 * @data: infoframe to ग_लिखो
 * @size: size to ग_लिखो
 */
अटल व्योम hdmi_infoframe_ग_लिखो_infopack(काष्ठा sti_hdmi *hdmi,
					  स्थिर u8 *data,
					  माप_प्रकार size)
अणु
	स्थिर u8 *ptr = data;
	u32 val, slot, mode, i;
	u32 head_offset, pack_offset;

	चयन (*ptr) अणु
	हाल HDMI_INFOFRAME_TYPE_AVI:
		slot = HDMI_IFRAME_SLOT_AVI;
		mode = HDMI_IFRAME_FIELD;
		head_offset = HDMI_SW_DI_N_HEAD_WORD(HDMI_IFRAME_SLOT_AVI);
		pack_offset = HDMI_SW_DI_N_PKT_WORD0(HDMI_IFRAME_SLOT_AVI);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_AUDIO:
		slot = HDMI_IFRAME_SLOT_AUDIO;
		mode = HDMI_IFRAME_FRAME;
		head_offset = HDMI_SW_DI_N_HEAD_WORD(HDMI_IFRAME_SLOT_AUDIO);
		pack_offset = HDMI_SW_DI_N_PKT_WORD0(HDMI_IFRAME_SLOT_AUDIO);
		अवरोध;
	हाल HDMI_INFOFRAME_TYPE_VENDOR:
		slot = HDMI_IFRAME_SLOT_VENDOR;
		mode = HDMI_IFRAME_FRAME;
		head_offset = HDMI_SW_DI_N_HEAD_WORD(HDMI_IFRAME_SLOT_VENDOR);
		pack_offset = HDMI_SW_DI_N_PKT_WORD0(HDMI_IFRAME_SLOT_VENDOR);
		अवरोध;
	शेष:
		DRM_ERROR("unsupported infoframe type: %#x\n", *ptr);
		वापस;
	पूर्ण

	/* Disable transmission slot क्रम updated infoframe */
	val = hdmi_पढ़ो(hdmi, HDMI_SW_DI_CFG);
	val &= ~HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, slot);
	hdmi_ग_लिखो(hdmi, val, HDMI_SW_DI_CFG);

	val = HDMI_INFOFRAME_HEADER_TYPE(*ptr++);
	val |= HDMI_INFOFRAME_HEADER_VERSION(*ptr++);
	val |= HDMI_INFOFRAME_HEADER_LEN(*ptr++);
	ग_लिखोl(val, hdmi->regs + head_offset);

	/*
	 * Each subpack contains 4 bytes
	 * The First Bytes of the first subpacket must contain the checksum
	 * Packet size is increase by one.
	 */
	size = size - HDMI_INFOFRAME_HEADER_SIZE + 1;
	क्रम (i = 0; i < size; i += माप(u32)) अणु
		माप_प्रकार num;

		num = min_t(माप_प्रकार, size - i, माप(u32));
		val = hdmi_infoframe_subpack(ptr, num);
		ptr += माप(u32);
		ग_लिखोl(val, hdmi->regs + pack_offset + i);
	पूर्ण

	/* Enable transmission slot क्रम updated infoframe */
	val = hdmi_पढ़ो(hdmi, HDMI_SW_DI_CFG);
	val |= HDMI_IFRAME_CFG_DI_N(mode, slot);
	hdmi_ग_लिखो(hdmi, val, HDMI_SW_DI_CFG);
पूर्ण

/**
 * Prepare and configure the AVI infoframe
 *
 * AVI infoframe are transmitted at least once per two video field and
 * contains inक्रमmation about HDMI transmission mode such as color space,
 * colorimetry, ...
 *
 * @hdmi: poपूर्णांकer on the hdmi पूर्णांकernal काष्ठाure
 *
 * Return negative value अगर error occurs
 */
अटल पूर्णांक hdmi_avi_infoframe_config(काष्ठा sti_hdmi *hdmi)
अणु
	काष्ठा drm_display_mode *mode = &hdmi->mode;
	काष्ठा hdmi_avi_infoframe infoframe;
	u8 buffer[HDMI_INFOFRAME_SIZE(AVI)];
	पूर्णांक ret;

	DRM_DEBUG_DRIVER("\n");

	ret = drm_hdmi_avi_infoframe_from_display_mode(&infoframe,
						       hdmi->drm_connector, mode);
	अगर (ret < 0) अणु
		DRM_ERROR("failed to setup AVI infoframe: %d\n", ret);
		वापस ret;
	पूर्ण

	/* fixed infoframe configuration not linked to the mode */
	infoframe.colorspace = hdmi->colorspace;
	infoframe.quantization_range = HDMI_QUANTIZATION_RANGE_DEFAULT;
	infoframe.colorimetry = HDMI_COLORIMETRY_NONE;

	ret = hdmi_avi_infoframe_pack(&infoframe, buffer, माप(buffer));
	अगर (ret < 0) अणु
		DRM_ERROR("failed to pack AVI infoframe: %d\n", ret);
		वापस ret;
	पूर्ण

	hdmi_infoframe_ग_लिखो_infopack(hdmi, buffer, ret);

	वापस 0;
पूर्ण

/**
 * Prepare and configure the AUDIO infoframe
 *
 * AUDIO infoframe are transmitted once per frame and
 * contains inक्रमmation about HDMI transmission mode such as audio codec,
 * sample size, ...
 *
 * @hdmi: poपूर्णांकer on the hdmi पूर्णांकernal काष्ठाure
 *
 * Return negative value अगर error occurs
 */
अटल पूर्णांक hdmi_audio_infoframe_config(काष्ठा sti_hdmi *hdmi)
अणु
	काष्ठा hdmi_audio_params *audio = &hdmi->audio;
	u8 buffer[HDMI_INFOFRAME_SIZE(AUDIO)];
	पूर्णांक ret, val;

	DRM_DEBUG_DRIVER("enter %s, AIF %s\n", __func__,
			 audio->enabled ? "enable" : "disable");
	अगर (audio->enabled) अणु
		/* set audio parameters stored*/
		ret = hdmi_audio_infoframe_pack(&audio->cea, buffer,
						माप(buffer));
		अगर (ret < 0) अणु
			DRM_ERROR("failed to pack audio infoframe: %d\n", ret);
			वापस ret;
		पूर्ण
		hdmi_infoframe_ग_लिखो_infopack(hdmi, buffer, ret);
	पूर्ण अन्यथा अणु
		/*disable audio info frame transmission */
		val = hdmi_पढ़ो(hdmi, HDMI_SW_DI_CFG);
		val &= ~HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK,
					     HDMI_IFRAME_SLOT_AUDIO);
		hdmi_ग_लिखो(hdmi, val, HDMI_SW_DI_CFG);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Prepare and configure the VS infoframe
 *
 * Venकरोr Specअगरic infoframe are transmitted once per frame and
 * contains venकरोr specअगरic inक्रमmation.
 *
 * @hdmi: poपूर्णांकer on the hdmi पूर्णांकernal काष्ठाure
 *
 * Return negative value अगर error occurs
 */
#घोषणा HDMI_VENDOR_INFOFRAME_MAX_SIZE 6
अटल पूर्णांक hdmi_venकरोr_infoframe_config(काष्ठा sti_hdmi *hdmi)
अणु
	काष्ठा drm_display_mode *mode = &hdmi->mode;
	काष्ठा hdmi_venकरोr_infoframe infoframe;
	u8 buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_VENDOR_INFOFRAME_MAX_SIZE];
	पूर्णांक ret;

	DRM_DEBUG_DRIVER("\n");

	ret = drm_hdmi_venकरोr_infoframe_from_display_mode(&infoframe,
							  hdmi->drm_connector,
							  mode);
	अगर (ret < 0) अणु
		/*
		 * Going पूर्णांकo that statement करोes not means venकरोr infoframe
		 * fails. It just inक्रमmed us that venकरोr infoframe is not
		 * needed क्रम the selected mode. Only  4k or stereoscopic 3D
		 * mode requires venकरोr infoframe. So just simply वापस 0.
		 */
		वापस 0;
	पूर्ण

	ret = hdmi_venकरोr_infoframe_pack(&infoframe, buffer, माप(buffer));
	अगर (ret < 0) अणु
		DRM_ERROR("failed to pack VS infoframe: %d\n", ret);
		वापस ret;
	पूर्ण

	hdmi_infoframe_ग_लिखो_infopack(hdmi, buffer, ret);

	वापस 0;
पूर्ण

#घोषणा HDMI_TIMEOUT_SWRESET  100   /*milliseconds */

/**
 * Software reset of the hdmi subप्रणाली
 *
 * @hdmi: poपूर्णांकer on the hdmi पूर्णांकernal काष्ठाure
 *
 */
अटल व्योम hdmi_swreset(काष्ठा sti_hdmi *hdmi)
अणु
	u32 val;

	DRM_DEBUG_DRIVER("\n");

	/* Enable hdmi_audio घड़ी only during hdmi reset */
	अगर (clk_prepare_enable(hdmi->clk_audio))
		DRM_INFO("Failed to prepare/enable hdmi_audio clk\n");

	/* Sw reset */
	hdmi->event_received = false;

	val = hdmi_पढ़ो(hdmi, HDMI_CFG);
	val |= HDMI_CFG_SW_RST_EN;
	hdmi_ग_लिखो(hdmi, val, HDMI_CFG);

	/* Wait reset completed */
	रुको_event_पूर्णांकerruptible_समयout(hdmi->रुको_event,
					 hdmi->event_received,
					 msecs_to_jअगरfies
					 (HDMI_TIMEOUT_SWRESET));

	/*
	 * HDMI_STA_SW_RST bit is set to '1' when SW_RST bit in HDMI_CFG is
	 * set to '1' and clk_audio is running.
	 */
	अगर ((hdmi_पढ़ो(hdmi, HDMI_STA) & HDMI_STA_SW_RST) == 0)
		DRM_DEBUG_DRIVER("Warning: HDMI sw reset timeout occurs\n");

	val = hdmi_पढ़ो(hdmi, HDMI_CFG);
	val &= ~HDMI_CFG_SW_RST_EN;
	hdmi_ग_लिखो(hdmi, val, HDMI_CFG);

	/* Disable hdmi_audio घड़ी. Not used anymore क्रम drm purpose */
	clk_disable_unprepare(hdmi->clk_audio);
पूर्ण

#घोषणा DBGFS_PRINT_STR(str1, str2) seq_म_लिखो(s, "%-24s %s\n", str1, str2)
#घोषणा DBGFS_PRINT_INT(str1, पूर्णांक2) seq_म_लिखो(s, "%-24s %d\n", str1, पूर्णांक2)
#घोषणा DBGFS_DUMP(str, reg) seq_म_लिखो(s, "%s  %-25s 0x%08X", str, #reg, \
					hdmi_पढ़ो(hdmi, reg))
#घोषणा DBGFS_DUMP_DI(reg, slot) DBGFS_DUMP("\n", reg(slot))

अटल व्योम hdmi_dbg_cfg(काष्ठा seq_file *s, पूर्णांक val)
अणु
	पूर्णांक पंचांगp;

	seq_अ_दो(s, '\t');
	पंचांगp = val & HDMI_CFG_HDMI_NOT_DVI;
	DBGFS_PRINT_STR("mode:", पंचांगp ? "HDMI" : "DVI");
	seq_माला_दो(s, "\t\t\t\t\t");
	पंचांगp = val & HDMI_CFG_HDCP_EN;
	DBGFS_PRINT_STR("HDCP:", पंचांगp ? "enable" : "disable");
	seq_माला_दो(s, "\t\t\t\t\t");
	पंचांगp = val & HDMI_CFG_ESS_NOT_OESS;
	DBGFS_PRINT_STR("HDCP mode:", पंचांगp ? "ESS enable" : "OESS enable");
	seq_माला_दो(s, "\t\t\t\t\t");
	पंचांगp = val & HDMI_CFG_H_SYNC_POL_NEG;
	DBGFS_PRINT_STR("Hsync polarity:", पंचांगp ? "inverted" : "normal");
	seq_माला_दो(s, "\t\t\t\t\t");
	पंचांगp = val & HDMI_CFG_V_SYNC_POL_NEG;
	DBGFS_PRINT_STR("Vsync polarity:", पंचांगp ? "inverted" : "normal");
	seq_माला_दो(s, "\t\t\t\t\t");
	पंचांगp = val & HDMI_CFG_422_EN;
	DBGFS_PRINT_STR("YUV422 format:", पंचांगp ? "enable" : "disable");
पूर्ण

अटल व्योम hdmi_dbg_sta(काष्ठा seq_file *s, पूर्णांक val)
अणु
	पूर्णांक पंचांगp;

	seq_अ_दो(s, '\t');
	पंचांगp = (val & HDMI_STA_DLL_LCK);
	DBGFS_PRINT_STR("pll:", पंचांगp ? "locked" : "not locked");
	seq_माला_दो(s, "\t\t\t\t\t");
	पंचांगp = (val & HDMI_STA_HOT_PLUG);
	DBGFS_PRINT_STR("hdmi cable:", पंचांगp ? "connected" : "not connected");
पूर्ण

अटल व्योम hdmi_dbg_sw_di_cfg(काष्ठा seq_file *s, पूर्णांक val)
अणु
	पूर्णांक पंचांगp;
	अक्षर *स्थिर en_di[] = अणु"no transmission",
			       "single transmission",
			       "once every field",
			       "once every frame"पूर्ण;

	seq_अ_दो(s, '\t');
	पंचांगp = (val & HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, 1));
	DBGFS_PRINT_STR("Data island 1:", en_di[पंचांगp]);
	seq_माला_दो(s, "\t\t\t\t\t");
	पंचांगp = (val & HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, 2)) >> 4;
	DBGFS_PRINT_STR("Data island 2:", en_di[पंचांगp]);
	seq_माला_दो(s, "\t\t\t\t\t");
	पंचांगp = (val & HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, 3)) >> 8;
	DBGFS_PRINT_STR("Data island 3:", en_di[पंचांगp]);
	seq_माला_दो(s, "\t\t\t\t\t");
	पंचांगp = (val & HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, 4)) >> 12;
	DBGFS_PRINT_STR("Data island 4:", en_di[पंचांगp]);
	seq_माला_दो(s, "\t\t\t\t\t");
	पंचांगp = (val & HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, 5)) >> 16;
	DBGFS_PRINT_STR("Data island 5:", en_di[पंचांगp]);
	seq_माला_दो(s, "\t\t\t\t\t");
	पंचांगp = (val & HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, 6)) >> 20;
	DBGFS_PRINT_STR("Data island 6:", en_di[पंचांगp]);
पूर्ण

अटल पूर्णांक hdmi_dbg_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा sti_hdmi *hdmi = (काष्ठा sti_hdmi *)node->info_ent->data;

	seq_म_लिखो(s, "HDMI: (vaddr = 0x%p)", hdmi->regs);
	DBGFS_DUMP("\n", HDMI_CFG);
	hdmi_dbg_cfg(s, hdmi_पढ़ो(hdmi, HDMI_CFG));
	DBGFS_DUMP("", HDMI_INT_EN);
	DBGFS_DUMP("\n", HDMI_STA);
	hdmi_dbg_sta(s, hdmi_पढ़ो(hdmi, HDMI_STA));
	DBGFS_DUMP("", HDMI_ACTIVE_VID_XMIN);
	seq_अ_दो(s, '\t');
	DBGFS_PRINT_INT("Xmin:", hdmi_पढ़ो(hdmi, HDMI_ACTIVE_VID_XMIN));
	DBGFS_DUMP("", HDMI_ACTIVE_VID_XMAX);
	seq_अ_दो(s, '\t');
	DBGFS_PRINT_INT("Xmax:", hdmi_पढ़ो(hdmi, HDMI_ACTIVE_VID_XMAX));
	DBGFS_DUMP("", HDMI_ACTIVE_VID_YMIN);
	seq_अ_दो(s, '\t');
	DBGFS_PRINT_INT("Ymin:", hdmi_पढ़ो(hdmi, HDMI_ACTIVE_VID_YMIN));
	DBGFS_DUMP("", HDMI_ACTIVE_VID_YMAX);
	seq_अ_दो(s, '\t');
	DBGFS_PRINT_INT("Ymax:", hdmi_पढ़ो(hdmi, HDMI_ACTIVE_VID_YMAX));
	DBGFS_DUMP("", HDMI_SW_DI_CFG);
	hdmi_dbg_sw_di_cfg(s, hdmi_पढ़ो(hdmi, HDMI_SW_DI_CFG));

	DBGFS_DUMP("\n", HDMI_AUDIO_CFG);
	DBGFS_DUMP("\n", HDMI_SPDIF_FIFO_STATUS);
	DBGFS_DUMP("\n", HDMI_AUDN);

	seq_म_लिखो(s, "\n AVI Infoframe (Data Island slot N=%d):",
		   HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_HEAD_WORD, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD0, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD1, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD2, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD3, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD4, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD5, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD6, HDMI_IFRAME_SLOT_AVI);
	seq_म_लिखो(s, "\n\n AUDIO Infoframe (Data Island slot N=%d):",
		   HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_HEAD_WORD, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD0, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD1, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD2, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD3, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD4, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD5, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD6, HDMI_IFRAME_SLOT_AUDIO);
	seq_म_लिखो(s, "\n\n VENDOR SPECIFIC Infoframe (Data Island slot N=%d):",
		   HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_HEAD_WORD, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD0, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD1, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD2, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD3, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD4, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD5, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD6, HDMI_IFRAME_SLOT_VENDOR);
	seq_अ_दो(s, '\n');
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list hdmi_debugfs_files[] = अणु
	अणु "hdmi", hdmi_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

अटल व्योम hdmi_debugfs_init(काष्ठा sti_hdmi *hdmi, काष्ठा drm_minor *minor)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hdmi_debugfs_files); i++)
		hdmi_debugfs_files[i].data = hdmi;

	drm_debugfs_create_files(hdmi_debugfs_files,
				 ARRAY_SIZE(hdmi_debugfs_files),
				 minor->debugfs_root, minor);
पूर्ण

अटल व्योम sti_hdmi_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा sti_hdmi *hdmi = bridge->driver_निजी;

	u32 val = hdmi_पढ़ो(hdmi, HDMI_CFG);

	अगर (!hdmi->enabled)
		वापस;

	DRM_DEBUG_DRIVER("\n");

	/* Disable HDMI */
	val &= ~HDMI_CFG_DEVICE_EN;
	hdmi_ग_लिखो(hdmi, val, HDMI_CFG);

	hdmi_ग_लिखो(hdmi, 0xffffffff, HDMI_INT_CLR);

	/* Stop the phy */
	hdmi->phy_ops->stop(hdmi);

	/* Reset info frame transmission */
	hdmi_infoframe_reset(hdmi, HDMI_IFRAME_SLOT_AVI);
	hdmi_infoframe_reset(hdmi, HDMI_IFRAME_SLOT_AUDIO);
	hdmi_infoframe_reset(hdmi, HDMI_IFRAME_SLOT_VENDOR);

	/* Set the शेष channel data to be a dark red */
	hdmi_ग_लिखो(hdmi, 0x0000, HDMI_DFLT_CHL0_DAT);
	hdmi_ग_लिखो(hdmi, 0x0000, HDMI_DFLT_CHL1_DAT);
	hdmi_ग_लिखो(hdmi, 0x0060, HDMI_DFLT_CHL2_DAT);

	/* Disable/unprepare hdmi घड़ी */
	clk_disable_unprepare(hdmi->clk_phy);
	clk_disable_unprepare(hdmi->clk_पंचांगds);
	clk_disable_unprepare(hdmi->clk_pix);

	hdmi->enabled = false;

	cec_notअगरier_set_phys_addr(hdmi->notअगरier, CEC_PHYS_ADDR_INVALID);
पूर्ण

/**
 * sti_hdmi_audio_get_non_coherent_n() - get N parameter क्रम non-coherent
 * घड़ीs. None-coherent घड़ीs means that audio and TMDS घड़ीs have not the
 * same source (drअगरts between घड़ीs). In this हाल assumption is that CTS is
 * स्वतःmatically calculated by hardware.
 *
 * @audio_fs: audio frame घड़ी frequency in Hz
 *
 * Values computed are based on table described in HDMI specअगरication 1.4b
 *
 * Returns n value.
 */
अटल पूर्णांक sti_hdmi_audio_get_non_coherent_n(अचिन्हित पूर्णांक audio_fs)
अणु
	अचिन्हित पूर्णांक n;

	चयन (audio_fs) अणु
	हाल 32000:
		n = 4096;
		अवरोध;
	हाल 44100:
		n = 6272;
		अवरोध;
	हाल 48000:
		n = 6144;
		अवरोध;
	हाल 88200:
		n = 6272 * 2;
		अवरोध;
	हाल 96000:
		n = 6144 * 2;
		अवरोध;
	हाल 176400:
		n = 6272 * 4;
		अवरोध;
	हाल 192000:
		n = 6144 * 4;
		अवरोध;
	शेष:
		/* Not pre-defined, recommended value: 128 * fs / 1000 */
		n = (audio_fs * 128) / 1000;
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक hdmi_audio_configure(काष्ठा sti_hdmi *hdmi)
अणु
	पूर्णांक audio_cfg, n;
	काष्ठा hdmi_audio_params *params = &hdmi->audio;
	काष्ठा hdmi_audio_infoframe *info = &params->cea;

	DRM_DEBUG_DRIVER("\n");

	अगर (!hdmi->enabled)
		वापस 0;

	/* update N parameter */
	n = sti_hdmi_audio_get_non_coherent_n(params->sample_rate);

	DRM_DEBUG_DRIVER("Audio rate = %d Hz, TMDS clock = %d Hz, n = %d\n",
			 params->sample_rate, hdmi->mode.घड़ी * 1000, n);
	hdmi_ग_लिखो(hdmi, n, HDMI_AUDN);

	/* update HDMI रेजिस्टरs according to configuration */
	audio_cfg = HDMI_AUD_CFG_SPDIF_DIV_2 | HDMI_AUD_CFG_DTS_INVALID |
		    HDMI_AUD_CFG_ONE_BIT_INVALID;

	चयन (info->channels) अणु
	हाल 8:
		audio_cfg |= HDMI_AUD_CFG_CH78_VALID;
		fallthrough;
	हाल 6:
		audio_cfg |= HDMI_AUD_CFG_CH56_VALID;
		fallthrough;
	हाल 4:
		audio_cfg |= HDMI_AUD_CFG_CH34_VALID | HDMI_AUD_CFG_8CH;
		fallthrough;
	हाल 2:
		audio_cfg |= HDMI_AUD_CFG_CH12_VALID;
		अवरोध;
	शेष:
		DRM_ERROR("ERROR: Unsupported number of channels (%d)!\n",
			  info->channels);
		वापस -EINVAL;
	पूर्ण

	hdmi_ग_लिखो(hdmi, audio_cfg, HDMI_AUDIO_CFG);

	वापस hdmi_audio_infoframe_config(hdmi);
पूर्ण

अटल व्योम sti_hdmi_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा sti_hdmi *hdmi = bridge->driver_निजी;

	DRM_DEBUG_DRIVER("\n");

	अगर (hdmi->enabled)
		वापस;

	/* Prepare/enable घड़ीs */
	अगर (clk_prepare_enable(hdmi->clk_pix))
		DRM_ERROR("Failed to prepare/enable hdmi_pix clk\n");
	अगर (clk_prepare_enable(hdmi->clk_पंचांगds))
		DRM_ERROR("Failed to prepare/enable hdmi_tmds clk\n");
	अगर (clk_prepare_enable(hdmi->clk_phy))
		DRM_ERROR("Failed to prepare/enable hdmi_rejec_pll clk\n");

	hdmi->enabled = true;

	/* Program hdmi serializer and start phy */
	अगर (!hdmi->phy_ops->start(hdmi)) अणु
		DRM_ERROR("Unable to start hdmi phy\n");
		वापस;
	पूर्ण

	/* Program hdmi active area */
	hdmi_active_area(hdmi);

	/* Enable working पूर्णांकerrupts */
	hdmi_ग_लिखो(hdmi, HDMI_WORKING_INT, HDMI_INT_EN);

	/* Program hdmi config */
	hdmi_config(hdmi);

	/* Program AVI infoframe */
	अगर (hdmi_avi_infoframe_config(hdmi))
		DRM_ERROR("Unable to configure AVI infoframe\n");

	अगर (hdmi->audio.enabled) अणु
		अगर (hdmi_audio_configure(hdmi))
			DRM_ERROR("Unable to configure audio\n");
	पूर्ण अन्यथा अणु
		hdmi_audio_infoframe_config(hdmi);
	पूर्ण

	/* Program VS infoframe */
	अगर (hdmi_venकरोr_infoframe_config(hdmi))
		DRM_ERROR("Unable to configure VS infoframe\n");

	/* Sw reset */
	hdmi_swreset(hdmi);
पूर्ण

अटल व्योम sti_hdmi_set_mode(काष्ठा drm_bridge *bridge,
			      स्थिर काष्ठा drm_display_mode *mode,
			      स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा sti_hdmi *hdmi = bridge->driver_निजी;
	पूर्णांक ret;

	DRM_DEBUG_DRIVER("\n");

	/* Copy the drm display mode in the connector local काष्ठाure */
	स_नकल(&hdmi->mode, mode, माप(काष्ठा drm_display_mode));

	/* Update घड़ी framerate according to the selected mode */
	ret = clk_set_rate(hdmi->clk_pix, mode->घड़ी * 1000);
	अगर (ret < 0) अणु
		DRM_ERROR("Cannot set rate (%dHz) for hdmi_pix clk\n",
			  mode->घड़ी * 1000);
		वापस;
	पूर्ण
	ret = clk_set_rate(hdmi->clk_phy, mode->घड़ी * 1000);
	अगर (ret < 0) अणु
		DRM_ERROR("Cannot set rate (%dHz) for hdmi_rejection_pll clk\n",
			  mode->घड़ी * 1000);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम sti_hdmi_bridge_nope(काष्ठा drm_bridge *bridge)
अणु
	/* करो nothing */
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs sti_hdmi_bridge_funcs = अणु
	.pre_enable = sti_hdmi_pre_enable,
	.enable = sti_hdmi_bridge_nope,
	.disable = sti_hdmi_disable,
	.post_disable = sti_hdmi_bridge_nope,
	.mode_set = sti_hdmi_set_mode,
पूर्ण;

अटल पूर्णांक sti_hdmi_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा sti_hdmi_connector *hdmi_connector
		= to_sti_hdmi_connector(connector);
	काष्ठा sti_hdmi *hdmi = hdmi_connector->hdmi;
	काष्ठा edid *edid;
	पूर्णांक count;

	DRM_DEBUG_DRIVER("\n");

	edid = drm_get_edid(connector, hdmi->ddc_adapt);
	अगर (!edid)
		जाओ fail;

	hdmi->hdmi_monitor = drm_detect_hdmi_monitor(edid);
	DRM_DEBUG_KMS("%s : %dx%d cm\n",
		      (hdmi->hdmi_monitor ? "hdmi monitor" : "dvi monitor"),
		      edid->width_cm, edid->height_cm);
	cec_notअगरier_set_phys_addr_from_edid(hdmi->notअगरier, edid);

	count = drm_add_edid_modes(connector, edid);
	drm_connector_update_edid_property(connector, edid);

	kमुक्त(edid);
	वापस count;

fail:
	DRM_ERROR("Can't read HDMI EDID\n");
	वापस 0;
पूर्ण

#घोषणा CLK_TOLERANCE_HZ 50

अटल पूर्णांक sti_hdmi_connector_mode_valid(काष्ठा drm_connector *connector,
					काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक target = mode->घड़ी * 1000;
	पूर्णांक target_min = target - CLK_TOLERANCE_HZ;
	पूर्णांक target_max = target + CLK_TOLERANCE_HZ;
	पूर्णांक result;
	काष्ठा sti_hdmi_connector *hdmi_connector
		= to_sti_hdmi_connector(connector);
	काष्ठा sti_hdmi *hdmi = hdmi_connector->hdmi;


	result = clk_round_rate(hdmi->clk_pix, target);

	DRM_DEBUG_DRIVER("target rate = %d => available rate = %d\n",
			 target, result);

	अगर ((result < target_min) || (result > target_max)) अणु
		DRM_DEBUG_DRIVER("hdmi pixclk=%d not supported\n", target);
		वापस MODE_BAD;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल स्थिर
काष्ठा drm_connector_helper_funcs sti_hdmi_connector_helper_funcs = अणु
	.get_modes = sti_hdmi_connector_get_modes,
	.mode_valid = sti_hdmi_connector_mode_valid,
पूर्ण;

/* get detection status of display device */
अटल क्रमागत drm_connector_status
sti_hdmi_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा sti_hdmi_connector *hdmi_connector
		= to_sti_hdmi_connector(connector);
	काष्ठा sti_hdmi *hdmi = hdmi_connector->hdmi;

	DRM_DEBUG_DRIVER("\n");

	अगर (hdmi->hpd) अणु
		DRM_DEBUG_DRIVER("hdmi cable connected\n");
		वापस connector_status_connected;
	पूर्ण

	DRM_DEBUG_DRIVER("hdmi cable disconnected\n");
	cec_notअगरier_set_phys_addr(hdmi->notअगरier, CEC_PHYS_ADDR_INVALID);
	वापस connector_status_disconnected;
पूर्ण

अटल व्योम sti_hdmi_connector_init_property(काष्ठा drm_device *drm_dev,
					     काष्ठा drm_connector *connector)
अणु
	काष्ठा sti_hdmi_connector *hdmi_connector
		= to_sti_hdmi_connector(connector);
	काष्ठा sti_hdmi *hdmi = hdmi_connector->hdmi;
	काष्ठा drm_property *prop;

	/* colorspace property */
	hdmi->colorspace = DEFAULT_COLORSPACE_MODE;
	prop = drm_property_create_क्रमागत(drm_dev, 0, "colorspace",
					colorspace_mode_names,
					ARRAY_SIZE(colorspace_mode_names));
	अगर (!prop) अणु
		DRM_ERROR("fails to create colorspace property\n");
		वापस;
	पूर्ण
	hdmi_connector->colorspace_property = prop;
	drm_object_attach_property(&connector->base, prop, hdmi->colorspace);
पूर्ण

अटल पूर्णांक
sti_hdmi_connector_set_property(काष्ठा drm_connector *connector,
				काष्ठा drm_connector_state *state,
				काष्ठा drm_property *property,
				uपूर्णांक64_t val)
अणु
	काष्ठा sti_hdmi_connector *hdmi_connector
		= to_sti_hdmi_connector(connector);
	काष्ठा sti_hdmi *hdmi = hdmi_connector->hdmi;

	अगर (property == hdmi_connector->colorspace_property) अणु
		hdmi->colorspace = val;
		वापस 0;
	पूर्ण

	DRM_ERROR("failed to set hdmi connector property\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
sti_hdmi_connector_get_property(काष्ठा drm_connector *connector,
				स्थिर काष्ठा drm_connector_state *state,
				काष्ठा drm_property *property,
				uपूर्णांक64_t *val)
अणु
	काष्ठा sti_hdmi_connector *hdmi_connector
		= to_sti_hdmi_connector(connector);
	काष्ठा sti_hdmi *hdmi = hdmi_connector->hdmi;

	अगर (property == hdmi_connector->colorspace_property) अणु
		*val = hdmi->colorspace;
		वापस 0;
	पूर्ण

	DRM_ERROR("failed to get hdmi connector property\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sti_hdmi_late_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा sti_hdmi_connector *hdmi_connector
		= to_sti_hdmi_connector(connector);
	काष्ठा sti_hdmi *hdmi = hdmi_connector->hdmi;

	hdmi_debugfs_init(hdmi, hdmi->drm_dev->primary);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs sti_hdmi_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = sti_hdmi_connector_detect,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_set_property = sti_hdmi_connector_set_property,
	.atomic_get_property = sti_hdmi_connector_get_property,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.late_रेजिस्टर = sti_hdmi_late_रेजिस्टर,
पूर्ण;

अटल काष्ठा drm_encoder *sti_hdmi_find_encoder(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_encoder *encoder;

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->encoder_type == DRM_MODE_ENCODER_TMDS)
			वापस encoder;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम hdmi_audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा sti_hdmi *hdmi = dev_get_drvdata(dev);
	पूर्णांक audio_cfg;

	DRM_DEBUG_DRIVER("\n");

	/* disable audio */
	audio_cfg = HDMI_AUD_CFG_SPDIF_DIV_2 | HDMI_AUD_CFG_DTS_INVALID |
		    HDMI_AUD_CFG_ONE_BIT_INVALID;
	hdmi_ग_लिखो(hdmi, audio_cfg, HDMI_AUDIO_CFG);

	hdmi->audio.enabled = false;
	hdmi_audio_infoframe_config(hdmi);
पूर्ण

अटल पूर्णांक hdmi_audio_hw_params(काष्ठा device *dev,
				व्योम *data,
				काष्ठा hdmi_codec_daअगरmt *daअगरmt,
				काष्ठा hdmi_codec_params *params)
अणु
	काष्ठा sti_hdmi *hdmi = dev_get_drvdata(dev);
	पूर्णांक ret;

	DRM_DEBUG_DRIVER("\n");

	अगर ((daअगरmt->fmt != HDMI_I2S) || daअगरmt->bit_clk_inv ||
	    daअगरmt->frame_clk_inv || daअगरmt->bit_clk_master ||
	    daअगरmt->frame_clk_master) अणु
		dev_err(dev, "%s: Bad flags %d %d %d %d\n", __func__,
			daअगरmt->bit_clk_inv, daअगरmt->frame_clk_inv,
			daअगरmt->bit_clk_master,
			daअगरmt->frame_clk_master);
		वापस -EINVAL;
	पूर्ण

	hdmi->audio.sample_width = params->sample_width;
	hdmi->audio.sample_rate = params->sample_rate;
	hdmi->audio.cea = params->cea;

	hdmi->audio.enabled = true;

	ret = hdmi_audio_configure(hdmi);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_audio_mute(काष्ठा device *dev, व्योम *data,
			   bool enable, पूर्णांक direction)
अणु
	काष्ठा sti_hdmi *hdmi = dev_get_drvdata(dev);

	DRM_DEBUG_DRIVER("%s\n", enable ? "enable" : "disable");

	अगर (enable)
		hdmi_ग_लिखो(hdmi, HDMI_SAMPLE_FLAT_ALL, HDMI_SAMPLE_FLAT_MASK);
	अन्यथा
		hdmi_ग_लिखो(hdmi, HDMI_SAMPLE_FLAT_NO, HDMI_SAMPLE_FLAT_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_audio_get_eld(काष्ठा device *dev, व्योम *data, uपूर्णांक8_t *buf, माप_प्रकार len)
अणु
	काष्ठा sti_hdmi *hdmi = dev_get_drvdata(dev);
	काष्ठा drm_connector *connector = hdmi->drm_connector;

	DRM_DEBUG_DRIVER("\n");
	स_नकल(buf, connector->eld, min(माप(connector->eld), len));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hdmi_codec_ops audio_codec_ops = अणु
	.hw_params = hdmi_audio_hw_params,
	.audio_shutकरोwn = hdmi_audio_shutकरोwn,
	.mute_stream = hdmi_audio_mute,
	.get_eld = hdmi_audio_get_eld,
	.no_capture_mute = 1,
पूर्ण;

अटल पूर्णांक sti_hdmi_रेजिस्टर_audio_driver(काष्ठा device *dev,
					  काष्ठा sti_hdmi *hdmi)
अणु
	काष्ठा hdmi_codec_pdata codec_data = अणु
		.ops = &audio_codec_ops,
		.max_i2s_channels = 8,
		.i2s = 1,
	पूर्ण;

	DRM_DEBUG_DRIVER("\n");

	hdmi->audio.enabled = false;

	hdmi->audio_pdev = platक्रमm_device_रेजिस्टर_data(
		dev, HDMI_CODEC_DRV_NAME, PLATFORM_DEVID_AUTO,
		&codec_data, माप(codec_data));

	अगर (IS_ERR(hdmi->audio_pdev))
		वापस PTR_ERR(hdmi->audio_pdev);

	DRM_INFO("%s Driver bound %s\n", HDMI_CODEC_DRV_NAME, dev_name(dev));

	वापस 0;
पूर्ण

अटल पूर्णांक sti_hdmi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा sti_hdmi *hdmi = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा drm_encoder *encoder;
	काष्ठा sti_hdmi_connector *connector;
	काष्ठा cec_connector_info conn_info;
	काष्ठा drm_connector *drm_connector;
	काष्ठा drm_bridge *bridge;
	पूर्णांक err;

	/* Set the drm device handle */
	hdmi->drm_dev = drm_dev;

	encoder = sti_hdmi_find_encoder(drm_dev);
	अगर (!encoder)
		वापस -EINVAL;

	connector = devm_kzalloc(dev, माप(*connector), GFP_KERNEL);
	अगर (!connector)
		वापस -EINVAL;

	connector->hdmi = hdmi;

	bridge = devm_kzalloc(dev, माप(*bridge), GFP_KERNEL);
	अगर (!bridge)
		वापस -EINVAL;

	bridge->driver_निजी = hdmi;
	bridge->funcs = &sti_hdmi_bridge_funcs;
	drm_bridge_attach(encoder, bridge, शून्य, 0);

	connector->encoder = encoder;

	drm_connector = (काष्ठा drm_connector *)connector;

	drm_connector->polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_init_with_ddc(drm_dev, drm_connector,
				    &sti_hdmi_connector_funcs,
				    DRM_MODE_CONNECTOR_HDMIA,
				    hdmi->ddc_adapt);
	drm_connector_helper_add(drm_connector,
			&sti_hdmi_connector_helper_funcs);

	/* initialise property */
	sti_hdmi_connector_init_property(drm_dev, drm_connector);

	hdmi->drm_connector = drm_connector;

	err = drm_connector_attach_encoder(drm_connector, encoder);
	अगर (err) अणु
		DRM_ERROR("Failed to attach a connector to a encoder\n");
		जाओ err_sysfs;
	पूर्ण

	err = sti_hdmi_रेजिस्टर_audio_driver(dev, hdmi);
	अगर (err) अणु
		DRM_ERROR("Failed to attach an audio codec\n");
		जाओ err_sysfs;
	पूर्ण

	/* Initialize audio infoframe */
	err = hdmi_audio_infoframe_init(&hdmi->audio.cea);
	अगर (err) अणु
		DRM_ERROR("Failed to init audio infoframe\n");
		जाओ err_sysfs;
	पूर्ण

	cec_fill_conn_info_from_drm(&conn_info, drm_connector);
	hdmi->notअगरier = cec_notअगरier_conn_रेजिस्टर(&hdmi->dev, शून्य,
						    &conn_info);
	अगर (!hdmi->notअगरier) अणु
		hdmi->drm_connector = शून्य;
		वापस -ENOMEM;
	पूर्ण

	/* Enable शेष पूर्णांकerrupts */
	hdmi_ग_लिखो(hdmi, HDMI_DEFAULT_INT, HDMI_INT_EN);

	वापस 0;

err_sysfs:
	hdmi->drm_connector = शून्य;
	वापस -EINVAL;
पूर्ण

अटल व्योम sti_hdmi_unbind(काष्ठा device *dev,
		काष्ठा device *master, व्योम *data)
अणु
	काष्ठा sti_hdmi *hdmi = dev_get_drvdata(dev);

	cec_notअगरier_conn_unरेजिस्टर(hdmi->notअगरier);
पूर्ण

अटल स्थिर काष्ठा component_ops sti_hdmi_ops = अणु
	.bind = sti_hdmi_bind,
	.unbind = sti_hdmi_unbind,
पूर्ण;

अटल स्थिर काष्ठा of_device_id hdmi_of_match[] = अणु
	अणु
		.compatible = "st,stih407-hdmi",
		.data = &tx3g4c28phy_ops,
	पूर्ण, अणु
		/* end node */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hdmi_of_match);

अटल पूर्णांक sti_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sti_hdmi *hdmi;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource *res;
	काष्ठा device_node *ddc;
	पूर्णांक ret;

	DRM_INFO("%s\n", __func__);

	hdmi = devm_kzalloc(dev, माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi)
		वापस -ENOMEM;

	ddc = of_parse_phandle(pdev->dev.of_node, "ddc", 0);
	अगर (ddc) अणु
		hdmi->ddc_adapt = of_get_i2c_adapter_by_node(ddc);
		of_node_put(ddc);
		अगर (!hdmi->ddc_adapt)
			वापस -EPROBE_DEFER;
	पूर्ण

	hdmi->dev = pdev->dev;

	/* Get resources */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "hdmi-reg");
	अगर (!res) अणु
		DRM_ERROR("Invalid hdmi resource\n");
		ret = -ENOMEM;
		जाओ release_adapter;
	पूर्ण
	hdmi->regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!hdmi->regs) अणु
		ret = -ENOMEM;
		जाओ release_adapter;
	पूर्ण

	hdmi->phy_ops = (काष्ठा hdmi_phy_ops *)
		of_match_node(hdmi_of_match, np)->data;

	/* Get घड़ी resources */
	hdmi->clk_pix = devm_clk_get(dev, "pix");
	अगर (IS_ERR(hdmi->clk_pix)) अणु
		DRM_ERROR("Cannot get hdmi_pix clock\n");
		ret = PTR_ERR(hdmi->clk_pix);
		जाओ release_adapter;
	पूर्ण

	hdmi->clk_पंचांगds = devm_clk_get(dev, "tmds");
	अगर (IS_ERR(hdmi->clk_पंचांगds)) अणु
		DRM_ERROR("Cannot get hdmi_tmds clock\n");
		ret = PTR_ERR(hdmi->clk_पंचांगds);
		जाओ release_adapter;
	पूर्ण

	hdmi->clk_phy = devm_clk_get(dev, "phy");
	अगर (IS_ERR(hdmi->clk_phy)) अणु
		DRM_ERROR("Cannot get hdmi_phy clock\n");
		ret = PTR_ERR(hdmi->clk_phy);
		जाओ release_adapter;
	पूर्ण

	hdmi->clk_audio = devm_clk_get(dev, "audio");
	अगर (IS_ERR(hdmi->clk_audio)) अणु
		DRM_ERROR("Cannot get hdmi_audio clock\n");
		ret = PTR_ERR(hdmi->clk_audio);
		जाओ release_adapter;
	पूर्ण

	hdmi->hpd = पढ़ोl(hdmi->regs + HDMI_STA) & HDMI_STA_HOT_PLUG;

	init_रुकोqueue_head(&hdmi->रुको_event);

	hdmi->irq = platक्रमm_get_irq_byname(pdev, "irq");
	अगर (hdmi->irq < 0) अणु
		DRM_ERROR("Cannot get HDMI irq\n");
		ret = hdmi->irq;
		जाओ release_adapter;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, hdmi->irq, hdmi_irq,
			hdmi_irq_thपढ़ो, IRQF_ONESHOT, dev_name(dev), hdmi);
	अगर (ret) अणु
		DRM_ERROR("Failed to register HDMI interrupt\n");
		जाओ release_adapter;
	पूर्ण

	hdmi->reset = devm_reset_control_get(dev, "hdmi");
	/* Take hdmi out of reset */
	अगर (!IS_ERR(hdmi->reset))
		reset_control_deनिश्चित(hdmi->reset);

	platक्रमm_set_drvdata(pdev, hdmi);

	वापस component_add(&pdev->dev, &sti_hdmi_ops);

 release_adapter:
	i2c_put_adapter(hdmi->ddc_adapt);

	वापस ret;
पूर्ण

अटल पूर्णांक sti_hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sti_hdmi *hdmi = dev_get_drvdata(&pdev->dev);

	i2c_put_adapter(hdmi->ddc_adapt);
	अगर (hdmi->audio_pdev)
		platक्रमm_device_unरेजिस्टर(hdmi->audio_pdev);
	component_del(&pdev->dev, &sti_hdmi_ops);

	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver sti_hdmi_driver = अणु
	.driver = अणु
		.name = "sti-hdmi",
		.owner = THIS_MODULE,
		.of_match_table = hdmi_of_match,
	पूर्ण,
	.probe = sti_hdmi_probe,
	.हटाओ = sti_hdmi_हटाओ,
पूर्ण;

MODULE_AUTHOR("Benjamin Gaignard <benjamin.gaignard@st.com>");
MODULE_DESCRIPTION("STMicroelectronics SoC DRM driver");
MODULE_LICENSE("GPL");
