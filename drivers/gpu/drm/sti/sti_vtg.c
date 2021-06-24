<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Benjamin Gaignard <benjamin.gaignard@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          Vincent Abriou <vincent.abriou@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "sti_drv.h"
#समावेश "sti_vtg.h"

#घोषणा VTG_MODE_MASTER         0

/* रेजिस्टरs offset */
#घोषणा VTG_MODE            0x0000
#घोषणा VTG_CLKLN           0x0008
#घोषणा VTG_HLFLN           0x000C
#घोषणा VTG_DRST_AUTOC      0x0010
#घोषणा VTG_VID_TFO         0x0040
#घोषणा VTG_VID_TFS         0x0044
#घोषणा VTG_VID_BFO         0x0048
#घोषणा VTG_VID_BFS         0x004C

#घोषणा VTG_HOST_ITS        0x0078
#घोषणा VTG_HOST_ITS_BCLR   0x007C
#घोषणा VTG_HOST_ITM_BCLR   0x0088
#घोषणा VTG_HOST_ITM_BSET   0x008C

#घोषणा VTG_H_HD_1          0x00C0
#घोषणा VTG_TOP_V_VD_1      0x00C4
#घोषणा VTG_BOT_V_VD_1      0x00C8
#घोषणा VTG_TOP_V_HD_1      0x00CC
#घोषणा VTG_BOT_V_HD_1      0x00D0

#घोषणा VTG_H_HD_2          0x00E0
#घोषणा VTG_TOP_V_VD_2      0x00E4
#घोषणा VTG_BOT_V_VD_2      0x00E8
#घोषणा VTG_TOP_V_HD_2      0x00EC
#घोषणा VTG_BOT_V_HD_2      0x00F0

#घोषणा VTG_H_HD_3          0x0100
#घोषणा VTG_TOP_V_VD_3      0x0104
#घोषणा VTG_BOT_V_VD_3      0x0108
#घोषणा VTG_TOP_V_HD_3      0x010C
#घोषणा VTG_BOT_V_HD_3      0x0110

#घोषणा VTG_H_HD_4          0x0120
#घोषणा VTG_TOP_V_VD_4      0x0124
#घोषणा VTG_BOT_V_VD_4      0x0128
#घोषणा VTG_TOP_V_HD_4      0x012c
#घोषणा VTG_BOT_V_HD_4      0x0130

#घोषणा VTG_IRQ_BOTTOM      BIT(0)
#घोषणा VTG_IRQ_TOP         BIT(1)
#घोषणा VTG_IRQ_MASK        (VTG_IRQ_TOP | VTG_IRQ_BOTTOM)

/* Delay पूर्णांकroduced by the HDMI in nb of pixel */
#घोषणा HDMI_DELAY          (5)

/* Delay पूर्णांकroduced by the DVO in nb of pixel */
#घोषणा DVO_DELAY           (7)

/* delay पूर्णांकroduced by the Arbitrary Waveक्रमm Generator in nb of pixels */
#घोषणा AWG_DELAY_HD        (-9)
#घोषणा AWG_DELAY_ED        (-8)
#घोषणा AWG_DELAY_SD        (-7)

/*
 * STI VTG रेजिस्टर offset काष्ठाure
 *
 *@h_hd:     stores the VTG_H_HD_x     रेजिस्टर offset
 *@top_v_vd: stores the VTG_TOP_V_VD_x रेजिस्टर offset
 *@bot_v_vd: stores the VTG_BOT_V_VD_x रेजिस्टर offset
 *@top_v_hd: stores the VTG_TOP_V_HD_x रेजिस्टर offset
 *@bot_v_hd: stores the VTG_BOT_V_HD_x रेजिस्टर offset
 */
काष्ठा sti_vtg_regs_offs अणु
	u32 h_hd;
	u32 top_v_vd;
	u32 bot_v_vd;
	u32 top_v_hd;
	u32 bot_v_hd;
पूर्ण;

#घोषणा VTG_MAX_SYNC_OUTPUT 4
अटल स्थिर काष्ठा sti_vtg_regs_offs vtg_regs_offs[VTG_MAX_SYNC_OUTPUT] = अणु
	अणु VTG_H_HD_1,
	  VTG_TOP_V_VD_1, VTG_BOT_V_VD_1, VTG_TOP_V_HD_1, VTG_BOT_V_HD_1 पूर्ण,
	अणु VTG_H_HD_2,
	  VTG_TOP_V_VD_2, VTG_BOT_V_VD_2, VTG_TOP_V_HD_2, VTG_BOT_V_HD_2 पूर्ण,
	अणु VTG_H_HD_3,
	  VTG_TOP_V_VD_3, VTG_BOT_V_VD_3, VTG_TOP_V_HD_3, VTG_BOT_V_HD_3 पूर्ण,
	अणु VTG_H_HD_4,
	  VTG_TOP_V_VD_4, VTG_BOT_V_VD_4, VTG_TOP_V_HD_4, VTG_BOT_V_HD_4 पूर्ण
पूर्ण;

/*
 * STI VTG synchronisation parameters काष्ठाure
 *
 *@hsync: sample number falling and rising edge
 *@vsync_line_top: vertical top field line number falling and rising edge
 *@vsync_line_bot: vertical bottom field line number falling and rising edge
 *@vsync_off_top: vertical top field sample number rising and falling edge
 *@vsync_off_bot: vertical bottom field sample number rising and falling edge
 */
काष्ठा sti_vtg_sync_params अणु
	u32 hsync;
	u32 vsync_line_top;
	u32 vsync_line_bot;
	u32 vsync_off_top;
	u32 vsync_off_bot;
पूर्ण;

/*
 * STI VTG काष्ठाure
 *
 * @regs: रेजिस्टर mapping
 * @sync_params: synchronisation parameters used to generate timings
 * @irq: VTG irq
 * @irq_status: store the IRQ status value
 * @notअगरier_list: notअगरier callback
 * @crtc: the CRTC क्रम vblank event
 */
काष्ठा sti_vtg अणु
	व्योम __iomem *regs;
	काष्ठा sti_vtg_sync_params sync_params[VTG_MAX_SYNC_OUTPUT];
	पूर्णांक irq;
	u32 irq_status;
	काष्ठा raw_notअगरier_head notअगरier_list;
	काष्ठा drm_crtc *crtc;
पूर्ण;

काष्ठा sti_vtg *of_vtg_find(काष्ठा device_node *np)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = of_find_device_by_node(np);
	अगर (!pdev)
		वापस शून्य;

	वापस (काष्ठा sti_vtg *)platक्रमm_get_drvdata(pdev);
पूर्ण

अटल व्योम vtg_reset(काष्ठा sti_vtg *vtg)
अणु
	ग_लिखोl(1, vtg->regs + VTG_DRST_AUTOC);
पूर्ण

अटल व्योम vtg_set_output_winकरोw(व्योम __iomem *regs,
				  स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 video_top_field_start;
	u32 video_top_field_stop;
	u32 video_bottom_field_start;
	u32 video_bottom_field_stop;
	u32 xstart = sti_vtg_get_pixel_number(*mode, 0);
	u32 ystart = sti_vtg_get_line_number(*mode, 0);
	u32 xstop = sti_vtg_get_pixel_number(*mode, mode->hdisplay - 1);
	u32 ystop = sti_vtg_get_line_number(*mode, mode->vdisplay - 1);

	/* Set output winकरोw to fit the display mode selected */
	video_top_field_start = (ystart << 16) | xstart;
	video_top_field_stop = (ystop << 16) | xstop;

	/* Only progressive supported क्रम now */
	video_bottom_field_start = video_top_field_start;
	video_bottom_field_stop = video_top_field_stop;

	ग_लिखोl(video_top_field_start, regs + VTG_VID_TFO);
	ग_लिखोl(video_top_field_stop, regs + VTG_VID_TFS);
	ग_लिखोl(video_bottom_field_start, regs + VTG_VID_BFO);
	ग_लिखोl(video_bottom_field_stop, regs + VTG_VID_BFS);
पूर्ण

अटल व्योम vtg_set_hsync_vsync_pos(काष्ठा sti_vtg_sync_params *sync,
				    पूर्णांक delay,
				    स्थिर काष्ठा drm_display_mode *mode)
अणु
	दीर्घ घड़ीsperline, start, stop;
	u32 risesync_top, fallsync_top;
	u32 risesync_offs_top, fallsync_offs_top;

	घड़ीsperline = mode->htotal;

	/* Get the hsync position */
	start = 0;
	stop = mode->hsync_end - mode->hsync_start;

	start += delay;
	stop  += delay;

	अगर (start < 0)
		start += घड़ीsperline;
	अन्यथा अगर (start >= घड़ीsperline)
		start -= घड़ीsperline;

	अगर (stop < 0)
		stop += घड़ीsperline;
	अन्यथा अगर (stop >= घड़ीsperline)
		stop -= घड़ीsperline;

	sync->hsync = (stop << 16) | start;

	/* Get the vsync position */
	अगर (delay >= 0) अणु
		risesync_top = 1;
		fallsync_top = risesync_top;
		fallsync_top += mode->vsync_end - mode->vsync_start;

		fallsync_offs_top = (u32)delay;
		risesync_offs_top = (u32)delay;
	पूर्ण अन्यथा अणु
		risesync_top = mode->vtotal;
		fallsync_top = mode->vsync_end - mode->vsync_start;

		fallsync_offs_top = घड़ीsperline + delay;
		risesync_offs_top = घड़ीsperline + delay;
	पूर्ण

	sync->vsync_line_top = (fallsync_top << 16) | risesync_top;
	sync->vsync_off_top = (fallsync_offs_top << 16) | risesync_offs_top;

	/* Only progressive supported क्रम now */
	sync->vsync_line_bot = sync->vsync_line_top;
	sync->vsync_off_bot = sync->vsync_off_top;
पूर्ण

अटल व्योम vtg_set_mode(काष्ठा sti_vtg *vtg,
			 पूर्णांक type,
			 काष्ठा sti_vtg_sync_params *sync,
			 स्थिर काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक i;

	/* Set the number of घड़ी cycles per line */
	ग_लिखोl(mode->htotal, vtg->regs + VTG_CLKLN);

	/* Set Half Line Per Field (only progressive supported क्रम now) */
	ग_लिखोl(mode->vtotal * 2, vtg->regs + VTG_HLFLN);

	/* Program output winकरोw */
	vtg_set_output_winकरोw(vtg->regs, mode);

	/* Set hsync and vsync position क्रम HDMI */
	vtg_set_hsync_vsync_pos(&sync[VTG_SYNC_ID_HDMI - 1], HDMI_DELAY, mode);

	/* Set hsync and vsync position क्रम HD DCS */
	vtg_set_hsync_vsync_pos(&sync[VTG_SYNC_ID_HDDCS - 1], 0, mode);

	/* Set hsync and vsync position क्रम HDF */
	vtg_set_hsync_vsync_pos(&sync[VTG_SYNC_ID_HDF - 1], AWG_DELAY_HD, mode);

	/* Set hsync and vsync position क्रम DVO */
	vtg_set_hsync_vsync_pos(&sync[VTG_SYNC_ID_DVO - 1], DVO_DELAY, mode);

	/* Progam the syncs outमाला_दो */
	क्रम (i = 0; i < VTG_MAX_SYNC_OUTPUT ; i++) अणु
		ग_लिखोl(sync[i].hsync,
		       vtg->regs + vtg_regs_offs[i].h_hd);
		ग_लिखोl(sync[i].vsync_line_top,
		       vtg->regs + vtg_regs_offs[i].top_v_vd);
		ग_लिखोl(sync[i].vsync_line_bot,
		       vtg->regs + vtg_regs_offs[i].bot_v_vd);
		ग_लिखोl(sync[i].vsync_off_top,
		       vtg->regs + vtg_regs_offs[i].top_v_hd);
		ग_लिखोl(sync[i].vsync_off_bot,
		       vtg->regs + vtg_regs_offs[i].bot_v_hd);
	पूर्ण

	/* mode */
	ग_लिखोl(type, vtg->regs + VTG_MODE);
पूर्ण

अटल व्योम vtg_enable_irq(काष्ठा sti_vtg *vtg)
अणु
	/* clear पूर्णांकerrupt status and mask */
	ग_लिखोl(0xFFFF, vtg->regs + VTG_HOST_ITS_BCLR);
	ग_लिखोl(0xFFFF, vtg->regs + VTG_HOST_ITM_BCLR);
	ग_लिखोl(VTG_IRQ_MASK, vtg->regs + VTG_HOST_ITM_BSET);
पूर्ण

व्योम sti_vtg_set_config(काष्ठा sti_vtg *vtg,
		स्थिर काष्ठा drm_display_mode *mode)
अणु
	/* ग_लिखो configuration */
	vtg_set_mode(vtg, VTG_MODE_MASTER, vtg->sync_params, mode);

	vtg_reset(vtg);

	vtg_enable_irq(vtg);
पूर्ण

/**
 * sti_vtg_get_line_number
 *
 * @mode: display mode to be used
 * @y:    line
 *
 * Return the line number according to the display mode taking
 * पूर्णांकo account the Sync and Back Porch inक्रमmation.
 * Video frame line numbers start at 1, y starts at 0.
 * In पूर्णांकerlaced modes the start line is the field line number of the odd
 * field, but y is still defined as a progressive frame.
 */
u32 sti_vtg_get_line_number(काष्ठा drm_display_mode mode, पूर्णांक y)
अणु
	u32 start_line = mode.vtotal - mode.vsync_start + 1;

	अगर (mode.flags & DRM_MODE_FLAG_INTERLACE)
		start_line *= 2;

	वापस start_line + y;
पूर्ण

/**
 * sti_vtg_get_pixel_number
 *
 * @mode: display mode to be used
 * @x:    row
 *
 * Return the pixel number according to the display mode taking
 * पूर्णांकo account the Sync and Back Porch inक्रमmation.
 * Pixels are counted from 0.
 */
u32 sti_vtg_get_pixel_number(काष्ठा drm_display_mode mode, पूर्णांक x)
अणु
	वापस mode.htotal - mode.hsync_start + x;
पूर्ण

पूर्णांक sti_vtg_रेजिस्टर_client(काष्ठा sti_vtg *vtg, काष्ठा notअगरier_block *nb,
			    काष्ठा drm_crtc *crtc)
अणु
	vtg->crtc = crtc;
	वापस raw_notअगरier_chain_रेजिस्टर(&vtg->notअगरier_list, nb);
पूर्ण

पूर्णांक sti_vtg_unरेजिस्टर_client(काष्ठा sti_vtg *vtg, काष्ठा notअगरier_block *nb)
अणु
	वापस raw_notअगरier_chain_unरेजिस्टर(&vtg->notअगरier_list, nb);
पूर्ण

अटल irqवापस_t vtg_irq_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा sti_vtg *vtg = arg;
	u32 event;

	event = (vtg->irq_status & VTG_IRQ_TOP) ?
		VTG_TOP_FIELD_EVENT : VTG_BOTTOM_FIELD_EVENT;

	raw_notअगरier_call_chain(&vtg->notअगरier_list, event, vtg->crtc);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t vtg_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा sti_vtg *vtg = arg;

	vtg->irq_status = पढ़ोl(vtg->regs + VTG_HOST_ITS);

	ग_लिखोl(vtg->irq_status, vtg->regs + VTG_HOST_ITS_BCLR);

	/* क्रमce sync bus ग_लिखो */
	पढ़ोl(vtg->regs + VTG_HOST_ITS);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल पूर्णांक vtg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sti_vtg *vtg;
	काष्ठा resource *res;
	पूर्णांक ret;

	vtg = devm_kzalloc(dev, माप(*vtg), GFP_KERNEL);
	अगर (!vtg)
		वापस -ENOMEM;

	/* Get Memory ressources */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		DRM_ERROR("Get memory resource failed\n");
		वापस -ENOMEM;
	पूर्ण
	vtg->regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!vtg->regs) अणु
		DRM_ERROR("failed to remap I/O memory\n");
		वापस -ENOMEM;
	पूर्ण

	vtg->irq = platक्रमm_get_irq(pdev, 0);
	अगर (vtg->irq < 0) अणु
		DRM_ERROR("Failed to get VTG interrupt\n");
		वापस vtg->irq;
	पूर्ण

	RAW_INIT_NOTIFIER_HEAD(&vtg->notअगरier_list);

	ret = devm_request_thपढ़ोed_irq(dev, vtg->irq, vtg_irq,
					vtg_irq_thपढ़ो, IRQF_ONESHOT,
					dev_name(dev), vtg);
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to register VTG interrupt\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, vtg);

	DRM_INFO("%s %s\n", __func__, dev_name(dev));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id vtg_of_match[] = अणु
	अणु .compatible = "st,vtg", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vtg_of_match);

काष्ठा platक्रमm_driver sti_vtg_driver = अणु
	.driver = अणु
		.name = "sti-vtg",
		.owner = THIS_MODULE,
		.of_match_table = vtg_of_match,
	पूर्ण,
	.probe	= vtg_probe,
पूर्ण;

MODULE_AUTHOR("Benjamin Gaignard <benjamin.gaignard@st.com>");
MODULE_DESCRIPTION("STMicroelectronics SoC DRM driver");
MODULE_LICENSE("GPL");
