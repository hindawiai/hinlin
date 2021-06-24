<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Epson HWA742 LCD controller driver
 *
 * Copyright (C) 2004-2005 Nokia Corporation
 * Authors:     Juha Yrjथघlथअ   <juha.yrjola@nokia.com>
 *	        Imre Deak     <imre.deak@nokia.com>
 * YUV support: Jussi Laako   <jussi.laako@nokia.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "omapfb.h"

#घोषणा HWA742_REV_CODE_REG       0x0
#घोषणा HWA742_CONFIG_REG         0x2
#घोषणा HWA742_PLL_DIV_REG        0x4
#घोषणा HWA742_PLL_0_REG          0x6
#घोषणा HWA742_PLL_1_REG          0x8
#घोषणा HWA742_PLL_2_REG          0xa
#घोषणा HWA742_PLL_3_REG          0xc
#घोषणा HWA742_PLL_4_REG          0xe
#घोषणा HWA742_CLK_SRC_REG        0x12
#घोषणा HWA742_PANEL_TYPE_REG     0x14
#घोषणा HWA742_H_DISP_REG         0x16
#घोषणा HWA742_H_NDP_REG          0x18
#घोषणा HWA742_V_DISP_1_REG       0x1a
#घोषणा HWA742_V_DISP_2_REG       0x1c
#घोषणा HWA742_V_NDP_REG          0x1e
#घोषणा HWA742_HS_W_REG           0x20
#घोषणा HWA742_HP_S_REG           0x22
#घोषणा HWA742_VS_W_REG           0x24
#घोषणा HWA742_VP_S_REG           0x26
#घोषणा HWA742_PCLK_POL_REG       0x28
#घोषणा HWA742_INPUT_MODE_REG     0x2a
#घोषणा HWA742_TRANSL_MODE_REG1   0x2e
#घोषणा HWA742_DISP_MODE_REG      0x34
#घोषणा HWA742_WINDOW_TYPE        0x36
#घोषणा HWA742_WINDOW_X_START_0   0x38
#घोषणा HWA742_WINDOW_X_START_1   0x3a
#घोषणा HWA742_WINDOW_Y_START_0   0x3c
#घोषणा HWA742_WINDOW_Y_START_1   0x3e
#घोषणा HWA742_WINDOW_X_END_0     0x40
#घोषणा HWA742_WINDOW_X_END_1     0x42
#घोषणा HWA742_WINDOW_Y_END_0     0x44
#घोषणा HWA742_WINDOW_Y_END_1     0x46
#घोषणा HWA742_MEMORY_WRITE_LSB   0x48
#घोषणा HWA742_MEMORY_WRITE_MSB   0x49
#घोषणा HWA742_MEMORY_READ_0      0x4a
#घोषणा HWA742_MEMORY_READ_1      0x4c
#घोषणा HWA742_MEMORY_READ_2      0x4e
#घोषणा HWA742_POWER_SAVE         0x56
#घोषणा HWA742_NDP_CTRL           0x58

#घोषणा HWA742_AUTO_UPDATE_TIME		(HZ / 20)

/* Reserve 4 request slots क्रम requests in irq context */
#घोषणा REQ_POOL_SIZE			24
#घोषणा IRQ_REQ_POOL_SIZE		4

#घोषणा REQ_FROM_IRQ_POOL 0x01

#घोषणा REQ_COMPLETE	0
#घोषणा REQ_PENDING	1

काष्ठा update_param अणु
	पूर्णांक	x, y, width, height;
	पूर्णांक	color_mode;
	पूर्णांक	flags;
पूर्ण;

काष्ठा hwa742_request अणु
	काष्ठा list_head entry;
	अचिन्हित पूर्णांक	 flags;

	पूर्णांक		 (*handler)(काष्ठा hwa742_request *req);
	व्योम		 (*complete)(व्योम *data);
	व्योम		 *complete_data;

	जोड़ अणु
		काष्ठा update_param	update;
		काष्ठा completion	*sync;
	पूर्ण par;
पूर्ण;

काष्ठा अणु
	क्रमागत omapfb_update_mode	update_mode;
	क्रमागत omapfb_update_mode	update_mode_beक्रमe_suspend;

	काष्ठा समयr_list	स्वतः_update_समयr;
	पूर्णांक			stop_स्वतः_update;
	काष्ठा omapfb_update_winकरोw	स्वतः_update_winकरोw;
	अचिन्हित		te_connected:1;
	अचिन्हित		vsync_only:1;

	काष्ठा hwa742_request	req_pool[REQ_POOL_SIZE];
	काष्ठा list_head	pending_req_list;
	काष्ठा list_head	मुक्त_req_list;

	/*
	 * @req_lock: protect request slots pool and its tracking lists
	 * @req_sema: counter; slot allocators from task contexts must
	 *            push it करोwn beक्रमe acquiring a slot. This
	 *            guarantees that atomic contexts will always have
	 *            a minimum of IRQ_REQ_POOL_SIZE slots available.
	 */
	काष्ठा semaphore	req_sema;
	spinlock_t		req_lock;

	काष्ठा extअगर_timings	reg_timings, lut_timings;

	पूर्णांक			prev_color_mode;
	पूर्णांक			prev_flags;
	पूर्णांक			winकरोw_type;

	u32			max_transmit_size;
	u32			extअगर_clk_period;
	अचिन्हित दीर्घ		pix_tx_समय;
	अचिन्हित दीर्घ		line_upd_समय;


	काष्ठा omapfb_device	*fbdev;
	काष्ठा lcd_ctrl_extअगर	*extअगर;
	स्थिर काष्ठा lcd_ctrl	*पूर्णांक_ctrl;

	काष्ठा clk		*sys_ck;
पूर्ण hwa742;

काष्ठा lcd_ctrl hwa742_ctrl;

अटल u8 hwa742_पढ़ो_reg(u8 reg)
अणु
	u8 data;

	hwa742.extअगर->set_bits_per_cycle(8);
	hwa742.extअगर->ग_लिखो_command(&reg, 1);
	hwa742.extअगर->पढ़ो_data(&data, 1);

	वापस data;
पूर्ण

अटल व्योम hwa742_ग_लिखो_reg(u8 reg, u8 data)
अणु
	hwa742.extअगर->set_bits_per_cycle(8);
	hwa742.extअगर->ग_लिखो_command(&reg, 1);
	hwa742.extअगर->ग_लिखो_data(&data, 1);
पूर्ण

अटल व्योम set_winकरोw_regs(पूर्णांक x_start, पूर्णांक y_start, पूर्णांक x_end, पूर्णांक y_end)
अणु
	u8 पंचांगp[8];
	u8 cmd;

	x_end--;
	y_end--;
	पंचांगp[0] = x_start;
	पंचांगp[1] = x_start >> 8;
	पंचांगp[2] = y_start;
	पंचांगp[3] = y_start >> 8;
	पंचांगp[4] = x_end;
	पंचांगp[5] = x_end >> 8;
	पंचांगp[6] = y_end;
	पंचांगp[7] = y_end >> 8;

	hwa742.extअगर->set_bits_per_cycle(8);
	cmd = HWA742_WINDOW_X_START_0;

	hwa742.extअगर->ग_लिखो_command(&cmd, 1);

	hwa742.extअगर->ग_लिखो_data(पंचांगp, 8);
पूर्ण

अटल व्योम set_क्रमmat_regs(पूर्णांक conv, पूर्णांक transl, पूर्णांक flags)
अणु
	अगर (flags & OMAPFB_FORMAT_FLAG_DOUBLE) अणु
		hwa742.winकरोw_type = ((hwa742.winकरोw_type & 0xfc) | 0x01);
#अगर_घोषित VERBOSE
		dev_dbg(hwa742.fbdev->dev, "hwa742: enabled pixel doubling\n");
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		hwa742.winकरोw_type = (hwa742.winकरोw_type & 0xfc);
#अगर_घोषित VERBOSE
		dev_dbg(hwa742.fbdev->dev, "hwa742: disabled pixel doubling\n");
#पूर्ण_अगर
	पूर्ण

	hwa742_ग_लिखो_reg(HWA742_INPUT_MODE_REG, conv);
	hwa742_ग_लिखो_reg(HWA742_TRANSL_MODE_REG1, transl);
	hwa742_ग_लिखो_reg(HWA742_WINDOW_TYPE, hwa742.winकरोw_type);
पूर्ण

अटल व्योम enable_tearsync(पूर्णांक y, पूर्णांक width, पूर्णांक height, पूर्णांक screen_height,
			    पूर्णांक क्रमce_vsync)
अणु
	u8 b;

	b = hwa742_पढ़ो_reg(HWA742_NDP_CTRL);
	b |= 1 << 2;
	hwa742_ग_लिखो_reg(HWA742_NDP_CTRL, b);

	अगर (likely(hwa742.vsync_only || क्रमce_vsync)) अणु
		hwa742.extअगर->enable_tearsync(1, 0);
		वापस;
	पूर्ण

	अगर (width * hwa742.pix_tx_समय < hwa742.line_upd_समय) अणु
		hwa742.extअगर->enable_tearsync(1, 0);
		वापस;
	पूर्ण

	अगर ((width * hwa742.pix_tx_समय / 1000) * height <
	    (y + height) * (hwa742.line_upd_समय / 1000)) अणु
		hwa742.extअगर->enable_tearsync(1, 0);
		वापस;
	पूर्ण

	hwa742.extअगर->enable_tearsync(1, y + 1);
पूर्ण

अटल व्योम disable_tearsync(व्योम)
अणु
	u8 b;

	hwa742.extअगर->enable_tearsync(0, 0);

	b = hwa742_पढ़ो_reg(HWA742_NDP_CTRL);
	b &= ~(1 << 2);
	hwa742_ग_लिखो_reg(HWA742_NDP_CTRL, b);
पूर्ण

अटल अंतरभूत काष्ठा hwa742_request *alloc_req(bool can_sleep)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hwa742_request *req;
	पूर्णांक req_flags = 0;

	अगर (can_sleep)
		करोwn(&hwa742.req_sema);
	अन्यथा
		req_flags = REQ_FROM_IRQ_POOL;

	spin_lock_irqsave(&hwa742.req_lock, flags);
	BUG_ON(list_empty(&hwa742.मुक्त_req_list));
	req = list_entry(hwa742.मुक्त_req_list.next,
			 काष्ठा hwa742_request, entry);
	list_del(&req->entry);
	spin_unlock_irqrestore(&hwa742.req_lock, flags);

	INIT_LIST_HEAD(&req->entry);
	req->flags = req_flags;

	वापस req;
पूर्ण

अटल अंतरभूत व्योम मुक्त_req(काष्ठा hwa742_request *req)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hwa742.req_lock, flags);

	list_move(&req->entry, &hwa742.मुक्त_req_list);
	अगर (!(req->flags & REQ_FROM_IRQ_POOL))
		up(&hwa742.req_sema);

	spin_unlock_irqrestore(&hwa742.req_lock, flags);
पूर्ण

अटल व्योम process_pending_requests(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hwa742.req_lock, flags);

	जबतक (!list_empty(&hwa742.pending_req_list)) अणु
		काष्ठा hwa742_request *req;
		व्योम (*complete)(व्योम *);
		व्योम *complete_data;

		req = list_entry(hwa742.pending_req_list.next,
				 काष्ठा hwa742_request, entry);
		spin_unlock_irqrestore(&hwa742.req_lock, flags);

		अगर (req->handler(req) == REQ_PENDING)
			वापस;

		complete = req->complete;
		complete_data = req->complete_data;
		मुक्त_req(req);

		अगर (complete)
			complete(complete_data);

		spin_lock_irqsave(&hwa742.req_lock, flags);
	पूर्ण

	spin_unlock_irqrestore(&hwa742.req_lock, flags);
पूर्ण

अटल व्योम submit_req_list(काष्ठा list_head *head)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक process = 1;

	spin_lock_irqsave(&hwa742.req_lock, flags);
	अगर (likely(!list_empty(&hwa742.pending_req_list)))
		process = 0;
	list_splice_init(head, hwa742.pending_req_list.prev);
	spin_unlock_irqrestore(&hwa742.req_lock, flags);

	अगर (process)
		process_pending_requests();
पूर्ण

अटल व्योम request_complete(व्योम *data)
अणु
	काष्ठा hwa742_request	*req = (काष्ठा hwa742_request *)data;
	व्योम			(*complete)(व्योम *);
	व्योम			*complete_data;

	complete = req->complete;
	complete_data = req->complete_data;

	मुक्त_req(req);

	अगर (complete)
		complete(complete_data);

	process_pending_requests();
पूर्ण

अटल पूर्णांक send_frame_handler(काष्ठा hwa742_request *req)
अणु
	काष्ठा update_param *par = &req->par.update;
	पूर्णांक x = par->x;
	पूर्णांक y = par->y;
	पूर्णांक w = par->width;
	पूर्णांक h = par->height;
	पूर्णांक bpp;
	पूर्णांक conv, transl;
	अचिन्हित दीर्घ offset;
	पूर्णांक color_mode = par->color_mode;
	पूर्णांक flags = par->flags;
	पूर्णांक scr_width = hwa742.fbdev->panel->x_res;
	पूर्णांक scr_height = hwa742.fbdev->panel->y_res;

#अगर_घोषित VERBOSE
	dev_dbg(hwa742.fbdev->dev, "x %d y %d w %d h %d scr_width %d "
		"color_mode %d flags %d\n",
		x, y, w, h, scr_width, color_mode, flags);
#पूर्ण_अगर

	चयन (color_mode) अणु
	हाल OMAPFB_COLOR_YUV422:
		bpp = 16;
		conv = 0x08;
		transl = 0x25;
		अवरोध;
	हाल OMAPFB_COLOR_YUV420:
		bpp = 12;
		conv = 0x09;
		transl = 0x25;
		अवरोध;
	हाल OMAPFB_COLOR_RGB565:
		bpp = 16;
		conv = 0x01;
		transl = 0x05;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (hwa742.prev_flags != flags ||
	    hwa742.prev_color_mode != color_mode) अणु
		set_क्रमmat_regs(conv, transl, flags);
		hwa742.prev_color_mode = color_mode;
		hwa742.prev_flags = flags;
	पूर्ण
	flags = req->par.update.flags;
	अगर (flags & OMAPFB_FORMAT_FLAG_TEARSYNC)
		enable_tearsync(y, scr_width, h, scr_height,
				flags & OMAPFB_FORMAT_FLAG_FORCE_VSYNC);
	अन्यथा
		disable_tearsync();

	set_winकरोw_regs(x, y, x + w, y + h);

	offset = (scr_width * y + x) * bpp / 8;

	hwa742.पूर्णांक_ctrl->setup_plane(OMAPFB_PLANE_GFX,
			OMAPFB_CHANNEL_OUT_LCD, offset, scr_width, 0, 0, w, h,
			color_mode);

	hwa742.extअगर->set_bits_per_cycle(16);

	hwa742.पूर्णांक_ctrl->enable_plane(OMAPFB_PLANE_GFX, 1);
	hwa742.extअगर->transfer_area(w, h, request_complete, req);

	वापस REQ_PENDING;
पूर्ण

अटल व्योम send_frame_complete(व्योम *data)
अणु
	hwa742.पूर्णांक_ctrl->enable_plane(OMAPFB_PLANE_GFX, 0);
पूर्ण

#घोषणा ADD_PREQ(_x, _y, _w, _h, can_sleep) करो अणु\
	req = alloc_req(can_sleep);		\
	req->handler	= send_frame_handler;	\
	req->complete	= send_frame_complete;	\
	req->par.update.x = _x;			\
	req->par.update.y = _y;			\
	req->par.update.width  = _w;		\
	req->par.update.height = _h;		\
	req->par.update.color_mode = color_mode;\
	req->par.update.flags	  = flags;	\
	list_add_tail(&req->entry, req_head);	\
पूर्ण जबतक(0)

अटल व्योम create_req_list(काष्ठा omapfb_update_winकरोw *win,
			    काष्ठा list_head *req_head,
			    bool can_sleep)
अणु
	काष्ठा hwa742_request *req;
	पूर्णांक x = win->x;
	पूर्णांक y = win->y;
	पूर्णांक width = win->width;
	पूर्णांक height = win->height;
	पूर्णांक color_mode;
	पूर्णांक flags;

	flags = win->क्रमmat & ~OMAPFB_FORMAT_MASK;
	color_mode = win->क्रमmat & OMAPFB_FORMAT_MASK;

	अगर (x & 1) अणु
		ADD_PREQ(x, y, 1, height, can_sleep);
		width--;
		x++;
		flags &= ~OMAPFB_FORMAT_FLAG_TEARSYNC;
	पूर्ण
	अगर (width & ~1) अणु
		अचिन्हित पूर्णांक xspan = width & ~1;
		अचिन्हित पूर्णांक ystart = y;
		अचिन्हित पूर्णांक yspan = height;

		अगर (xspan * height * 2 > hwa742.max_transmit_size) अणु
			yspan = hwa742.max_transmit_size / (xspan * 2);
			ADD_PREQ(x, ystart, xspan, yspan, can_sleep);
			ystart += yspan;
			yspan = height - yspan;
			flags &= ~OMAPFB_FORMAT_FLAG_TEARSYNC;
		पूर्ण

		ADD_PREQ(x, ystart, xspan, yspan, can_sleep);
		x += xspan;
		width -= xspan;
		flags &= ~OMAPFB_FORMAT_FLAG_TEARSYNC;
	पूर्ण
	अगर (width)
		ADD_PREQ(x, y, 1, height, can_sleep);
पूर्ण

अटल व्योम स्वतः_update_complete(व्योम *data)
अणु
	अगर (!hwa742.stop_स्वतः_update)
		mod_समयr(&hwa742.स्वतः_update_समयr,
			  jअगरfies + HWA742_AUTO_UPDATE_TIME);
पूर्ण

अटल व्योम __hwa742_update_winकरोw_स्वतः(bool can_sleep)
अणु
	LIST_HEAD(req_list);
	काष्ठा hwa742_request *last;

	create_req_list(&hwa742.स्वतः_update_winकरोw, &req_list, can_sleep);
	last = list_entry(req_list.prev, काष्ठा hwa742_request, entry);

	last->complete = स्वतः_update_complete;
	last->complete_data = शून्य;

	submit_req_list(&req_list);
पूर्ण

अटल व्योम hwa742_update_winकरोw_स्वतः(काष्ठा समयr_list *unused)
अणु
	__hwa742_update_winकरोw_स्वतः(false);
पूर्ण

पूर्णांक hwa742_update_winकरोw_async(काष्ठा fb_info *fbi,
				 काष्ठा omapfb_update_winकरोw *win,
				 व्योम (*complete_callback)(व्योम *arg),
				 व्योम *complete_callback_data)
अणु
	LIST_HEAD(req_list);
	काष्ठा hwa742_request *last;
	पूर्णांक r = 0;

	अगर (hwa742.update_mode != OMAPFB_MANUAL_UPDATE) अणु
		dev_dbg(hwa742.fbdev->dev, "invalid update mode\n");
		r = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (unlikely(win->क्रमmat &
	    ~(0x03 | OMAPFB_FORMAT_FLAG_DOUBLE |
	    OMAPFB_FORMAT_FLAG_TEARSYNC | OMAPFB_FORMAT_FLAG_FORCE_VSYNC))) अणु
		dev_dbg(hwa742.fbdev->dev, "invalid window flag\n");
		r = -EINVAL;
		जाओ out;
	पूर्ण

	create_req_list(win, &req_list, true);
	last = list_entry(req_list.prev, काष्ठा hwa742_request, entry);

	last->complete = complete_callback;
	last->complete_data = (व्योम *)complete_callback_data;

	submit_req_list(&req_list);

out:
	वापस r;
पूर्ण
EXPORT_SYMBOL(hwa742_update_winकरोw_async);

अटल पूर्णांक hwa742_setup_plane(पूर्णांक plane, पूर्णांक channel_out,
				  अचिन्हित दीर्घ offset, पूर्णांक screen_width,
				  पूर्णांक pos_x, पूर्णांक pos_y, पूर्णांक width, पूर्णांक height,
				  पूर्णांक color_mode)
अणु
	अगर (plane != OMAPFB_PLANE_GFX ||
	    channel_out != OMAPFB_CHANNEL_OUT_LCD)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक hwa742_enable_plane(पूर्णांक plane, पूर्णांक enable)
अणु
	अगर (plane != 0)
		वापस -EINVAL;

	hwa742.पूर्णांक_ctrl->enable_plane(plane, enable);

	वापस 0;
पूर्ण

अटल पूर्णांक sync_handler(काष्ठा hwa742_request *req)
अणु
	complete(req->par.sync);
	वापस REQ_COMPLETE;
पूर्ण

अटल व्योम hwa742_sync(व्योम)
अणु
	LIST_HEAD(req_list);
	काष्ठा hwa742_request *req;
	काष्ठा completion comp;

	req = alloc_req(true);

	req->handler = sync_handler;
	req->complete = शून्य;
	init_completion(&comp);
	req->par.sync = &comp;

	list_add(&req->entry, &req_list);
	submit_req_list(&req_list);

	रुको_क्रम_completion(&comp);
पूर्ण

अटल व्योम hwa742_bind_client(काष्ठा omapfb_notअगरier_block *nb)
अणु
	dev_dbg(hwa742.fbdev->dev, "update_mode %d\n", hwa742.update_mode);
	अगर (hwa742.update_mode == OMAPFB_MANUAL_UPDATE) अणु
		omapfb_notअगरy_clients(hwa742.fbdev, OMAPFB_EVENT_READY);
	पूर्ण
पूर्ण

अटल पूर्णांक hwa742_set_update_mode(क्रमागत omapfb_update_mode mode)
अणु
	अगर (mode != OMAPFB_MANUAL_UPDATE && mode != OMAPFB_AUTO_UPDATE &&
	    mode != OMAPFB_UPDATE_DISABLED)
		वापस -EINVAL;

	अगर (mode == hwa742.update_mode)
		वापस 0;

	dev_info(hwa742.fbdev->dev, "HWA742: setting update mode to %s\n",
			mode == OMAPFB_UPDATE_DISABLED ? "disabled" :
			(mode == OMAPFB_AUTO_UPDATE ? "auto" : "manual"));

	चयन (hwa742.update_mode) अणु
	हाल OMAPFB_MANUAL_UPDATE:
		omapfb_notअगरy_clients(hwa742.fbdev, OMAPFB_EVENT_DISABLED);
		अवरोध;
	हाल OMAPFB_AUTO_UPDATE:
		hwa742.stop_स्वतः_update = 1;
		del_समयr_sync(&hwa742.स्वतः_update_समयr);
		अवरोध;
	हाल OMAPFB_UPDATE_DISABLED:
		अवरोध;
	पूर्ण

	hwa742.update_mode = mode;
	hwa742_sync();
	hwa742.stop_स्वतः_update = 0;

	चयन (mode) अणु
	हाल OMAPFB_MANUAL_UPDATE:
		omapfb_notअगरy_clients(hwa742.fbdev, OMAPFB_EVENT_READY);
		अवरोध;
	हाल OMAPFB_AUTO_UPDATE:
		__hwa742_update_winकरोw_स्वतः(true);
		अवरोध;
	हाल OMAPFB_UPDATE_DISABLED:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत omapfb_update_mode hwa742_get_update_mode(व्योम)
अणु
	वापस hwa742.update_mode;
पूर्ण

अटल अचिन्हित दीर्घ round_to_extअगर_ticks(अचिन्हित दीर्घ ps, पूर्णांक भाग)
अणु
	पूर्णांक bus_tick = hwa742.extअगर_clk_period * भाग;
	वापस (ps + bus_tick - 1) / bus_tick * bus_tick;
पूर्ण

अटल पूर्णांक calc_reg_timing(अचिन्हित दीर्घ sysclk, पूर्णांक भाग)
अणु
	काष्ठा extअगर_timings *t;
	अचिन्हित दीर्घ systim;

	/* CSOnTime 0, WEOnTime 2 ns, REOnTime 2 ns,
	 * AccessTime 2 ns + 12.2 ns (regs),
	 * WEOffTime = WEOnTime + 1 ns,
	 * REOffTime = REOnTime + 16 ns (regs),
	 * CSOffTime = REOffTime + 1 ns
	 * ReadCycle = 2ns + 2*SYSCLK  (regs),
	 * WriteCycle = 2*SYSCLK + 2 ns,
	 * CSPulseWidth = 10 ns */
	systim = 1000000000 / (sysclk / 1000);
	dev_dbg(hwa742.fbdev->dev, "HWA742 systim %lu ps extif_clk_period %u ps"
		  "extif_clk_div %d\n", systim, hwa742.extअगर_clk_period, भाग);

	t = &hwa742.reg_timings;
	स_रखो(t, 0, माप(*t));
	t->clk_भाग = भाग;
	t->cs_on_समय = 0;
	t->we_on_समय = round_to_extअगर_ticks(t->cs_on_समय + 2000, भाग);
	t->re_on_समय = round_to_extअगर_ticks(t->cs_on_समय + 2000, भाग);
	t->access_समय = round_to_extअगर_ticks(t->re_on_समय + 12200, भाग);
	t->we_off_समय = round_to_extअगर_ticks(t->we_on_समय + 1000, भाग);
	t->re_off_समय = round_to_extअगर_ticks(t->re_on_समय + 16000, भाग);
	t->cs_off_समय = round_to_extअगर_ticks(t->re_off_समय + 1000, भाग);
	t->we_cycle_समय = round_to_extअगर_ticks(2 * systim + 2000, भाग);
	अगर (t->we_cycle_समय < t->we_off_समय)
		t->we_cycle_समय = t->we_off_समय;
	t->re_cycle_समय = round_to_extअगर_ticks(2 * systim + 2000, भाग);
	अगर (t->re_cycle_समय < t->re_off_समय)
		t->re_cycle_समय = t->re_off_समय;
	t->cs_pulse_width = 0;

	dev_dbg(hwa742.fbdev->dev, "[reg]cson %d csoff %d reon %d reoff %d\n",
		 t->cs_on_समय, t->cs_off_समय, t->re_on_समय, t->re_off_समय);
	dev_dbg(hwa742.fbdev->dev, "[reg]weon %d weoff %d recyc %d wecyc %d\n",
		 t->we_on_समय, t->we_off_समय, t->re_cycle_समय,
		 t->we_cycle_समय);
	dev_dbg(hwa742.fbdev->dev, "[reg]rdaccess %d cspulse %d\n",
		 t->access_समय, t->cs_pulse_width);

	वापस hwa742.extअगर->convert_timings(t);
पूर्ण

अटल पूर्णांक calc_lut_timing(अचिन्हित दीर्घ sysclk, पूर्णांक भाग)
अणु
	काष्ठा extअगर_timings *t;
	अचिन्हित दीर्घ systim;

	/* CSOnTime 0, WEOnTime 2 ns, REOnTime 2 ns,
	 * AccessTime 2 ns + 4 * SYSCLK + 26 (lut),
	 * WEOffTime = WEOnTime + 1 ns,
	 * REOffTime = REOnTime + 4*SYSCLK + 26 ns (lut),
	 * CSOffTime = REOffTime + 1 ns
	 * ReadCycle = 2ns + 4*SYSCLK + 26 ns (lut),
	 * WriteCycle = 2*SYSCLK + 2 ns,
	 * CSPulseWidth = 10 ns
	 */
	systim = 1000000000 / (sysclk / 1000);
	dev_dbg(hwa742.fbdev->dev, "HWA742 systim %lu ps extif_clk_period %u ps"
		  "extif_clk_div %d\n", systim, hwa742.extअगर_clk_period, भाग);

	t = &hwa742.lut_timings;
	स_रखो(t, 0, माप(*t));

	t->clk_भाग = भाग;

	t->cs_on_समय = 0;
	t->we_on_समय = round_to_extअगर_ticks(t->cs_on_समय + 2000, भाग);
	t->re_on_समय = round_to_extअगर_ticks(t->cs_on_समय + 2000, भाग);
	t->access_समय = round_to_extअगर_ticks(t->re_on_समय + 4 * systim +
					      26000, भाग);
	t->we_off_समय = round_to_extअगर_ticks(t->we_on_समय + 1000, भाग);
	t->re_off_समय = round_to_extअगर_ticks(t->re_on_समय + 4 * systim +
					      26000, भाग);
	t->cs_off_समय = round_to_extअगर_ticks(t->re_off_समय + 1000, भाग);
	t->we_cycle_समय = round_to_extअगर_ticks(2 * systim + 2000, भाग);
	अगर (t->we_cycle_समय < t->we_off_समय)
		t->we_cycle_समय = t->we_off_समय;
	t->re_cycle_समय = round_to_extअगर_ticks(2000 + 4 * systim + 26000, भाग);
	अगर (t->re_cycle_समय < t->re_off_समय)
		t->re_cycle_समय = t->re_off_समय;
	t->cs_pulse_width = 0;

	dev_dbg(hwa742.fbdev->dev, "[lut]cson %d csoff %d reon %d reoff %d\n",
		 t->cs_on_समय, t->cs_off_समय, t->re_on_समय, t->re_off_समय);
	dev_dbg(hwa742.fbdev->dev, "[lut]weon %d weoff %d recyc %d wecyc %d\n",
		 t->we_on_समय, t->we_off_समय, t->re_cycle_समय,
		 t->we_cycle_समय);
	dev_dbg(hwa742.fbdev->dev, "[lut]rdaccess %d cspulse %d\n",
		 t->access_समय, t->cs_pulse_width);

	वापस hwa742.extअगर->convert_timings(t);
पूर्ण

अटल पूर्णांक calc_extअगर_timings(अचिन्हित दीर्घ sysclk, पूर्णांक *extअगर_mem_भाग)
अणु
	पूर्णांक max_clk_भाग;
	पूर्णांक भाग;

	hwa742.extअगर->get_clk_info(&hwa742.extअगर_clk_period, &max_clk_भाग);
	क्रम (भाग = 1; भाग < max_clk_भाग; भाग++) अणु
		अगर (calc_reg_timing(sysclk, भाग) == 0)
			अवरोध;
	पूर्ण
	अगर (भाग >= max_clk_भाग)
		जाओ err;

	*extअगर_mem_भाग = भाग;

	क्रम (भाग = 1; भाग < max_clk_भाग; भाग++) अणु
		अगर (calc_lut_timing(sysclk, भाग) == 0)
			अवरोध;
	पूर्ण

	अगर (भाग >= max_clk_भाग)
		जाओ err;

	वापस 0;

err:
	dev_err(hwa742.fbdev->dev, "can't setup timings\n");
	वापस -1;
पूर्ण

अटल व्योम calc_hwa742_clk_rates(अचिन्हित दीर्घ ext_clk,
				अचिन्हित दीर्घ *sys_clk, अचिन्हित दीर्घ *pix_clk)
अणु
	पूर्णांक pix_clk_src;
	पूर्णांक sys_भाग = 0, sys_mul = 0;
	पूर्णांक pix_भाग;

	pix_clk_src = hwa742_पढ़ो_reg(HWA742_CLK_SRC_REG);
	pix_भाग = ((pix_clk_src >> 3) & 0x1f) + 1;
	अगर ((pix_clk_src & (0x3 << 1)) == 0) अणु
		/* Source is the PLL */
		sys_भाग = (hwa742_पढ़ो_reg(HWA742_PLL_DIV_REG) & 0x3f) + 1;
		sys_mul = (hwa742_पढ़ो_reg(HWA742_PLL_4_REG) & 0x7f) + 1;
		*sys_clk = ext_clk * sys_mul / sys_भाग;
	पूर्ण अन्यथा	/* अन्यथा source is ext clk, or oscillator */
		*sys_clk = ext_clk;

	*pix_clk = *sys_clk / pix_भाग;			/* HZ */
	dev_dbg(hwa742.fbdev->dev,
		"ext_clk %ld pix_src %d pix_div %d sys_div %d sys_mul %d\n",
		ext_clk, pix_clk_src & (0x3 << 1), pix_भाग, sys_भाग, sys_mul);
	dev_dbg(hwa742.fbdev->dev, "sys_clk %ld pix_clk %ld\n",
		*sys_clk, *pix_clk);
पूर्ण


अटल पूर्णांक setup_tearsync(अचिन्हित दीर्घ pix_clk, पूर्णांक extअगर_भाग)
अणु
	पूर्णांक hdisp, vdisp;
	पूर्णांक hndp, vndp;
	पूर्णांक hsw, vsw;
	पूर्णांक hs, vs;
	पूर्णांक hs_pol_inv, vs_pol_inv;
	पूर्णांक use_hsvs, use_ndp;
	u8  b;

	hsw = hwa742_पढ़ो_reg(HWA742_HS_W_REG);
	vsw = hwa742_पढ़ो_reg(HWA742_VS_W_REG);
	hs_pol_inv = !(hsw & 0x80);
	vs_pol_inv = !(vsw & 0x80);
	hsw = hsw & 0x7f;
	vsw = vsw & 0x3f;

	hdisp = (hwa742_पढ़ो_reg(HWA742_H_DISP_REG) & 0x7f) * 8;
	vdisp = hwa742_पढ़ो_reg(HWA742_V_DISP_1_REG) +
		((hwa742_पढ़ो_reg(HWA742_V_DISP_2_REG) & 0x3) << 8);

	hndp = hwa742_पढ़ो_reg(HWA742_H_NDP_REG) & 0x7f;
	vndp = hwa742_पढ़ो_reg(HWA742_V_NDP_REG);

	/* समय to transfer one pixel (16bpp) in ps */
	hwa742.pix_tx_समय = hwa742.reg_timings.we_cycle_समय;
	अगर (hwa742.extअगर->get_max_tx_rate != शून्य) अणु
		/*
		 * The बाह्यal पूर्णांकerface might have a rate limitation,
		 * अगर so, we have to maximize our transfer rate.
		 */
		अचिन्हित दीर्घ min_tx_समय;
		अचिन्हित दीर्घ max_tx_rate = hwa742.extअगर->get_max_tx_rate();

		dev_dbg(hwa742.fbdev->dev, "max_tx_rate %ld HZ\n",
			max_tx_rate);
		min_tx_समय = 1000000000 / (max_tx_rate / 1000);  /* ps */
		अगर (hwa742.pix_tx_समय < min_tx_समय)
			hwa742.pix_tx_समय = min_tx_समय;
	पूर्ण

	/* समय to update one line in ps */
	hwa742.line_upd_समय = (hdisp + hndp) * 1000000 / (pix_clk / 1000);
	hwa742.line_upd_समय *= 1000;
	अगर (hdisp * hwa742.pix_tx_समय > hwa742.line_upd_समय)
		/*
		 * transfer speed too low, we might have to use both
		 * HS and VS
		 */
		use_hsvs = 1;
	अन्यथा
		/* decent transfer speed, we'll always use only VS */
		use_hsvs = 0;

	अगर (use_hsvs && (hs_pol_inv || vs_pol_inv)) अणु
		/*
		 * HS or'ed with VS doesn't work, use the active high
		 * TE संकेत based on HNDP / VNDP
		 */
		use_ndp = 1;
		hs_pol_inv = 0;
		vs_pol_inv = 0;
		hs = hndp;
		vs = vndp;
	पूर्ण अन्यथा अणु
		/*
		 * Use HS or'ed with VS as a TE संकेत अगर both are needed
		 * or VNDP अगर only vsync is needed.
		 */
		use_ndp = 0;
		hs = hsw;
		vs = vsw;
		अगर (!use_hsvs) अणु
			hs_pol_inv = 0;
			vs_pol_inv = 0;
		पूर्ण
	पूर्ण

	hs = hs * 1000000 / (pix_clk / 1000);			/* ps */
	hs *= 1000;

	vs = vs * (hdisp + hndp) * 1000000 / (pix_clk / 1000);	/* ps */
	vs *= 1000;

	अगर (vs <= hs)
		वापस -गलत_तर्क;
	/* set VS to 120% of HS to minimize VS detection समय */
	vs = hs * 12 / 10;
	/* minimize HS too */
	hs = 10000;

	b = hwa742_पढ़ो_reg(HWA742_NDP_CTRL);
	b &= ~0x3;
	b |= use_hsvs ? 1 : 0;
	b |= (use_ndp && use_hsvs) ? 0 : 2;
	hwa742_ग_लिखो_reg(HWA742_NDP_CTRL, b);

	hwa742.vsync_only = !use_hsvs;

	dev_dbg(hwa742.fbdev->dev,
		"pix_clk %ld HZ pix_tx_time %ld ps line_upd_time %ld ps\n",
		pix_clk, hwa742.pix_tx_समय, hwa742.line_upd_समय);
	dev_dbg(hwa742.fbdev->dev,
		"hs %d ps vs %d ps mode %d vsync_only %d\n",
		hs, vs, (b & 0x3), !use_hsvs);

	वापस hwa742.extअगर->setup_tearsync(1, hs, vs,
					    hs_pol_inv, vs_pol_inv, extअगर_भाग);
पूर्ण

अटल व्योम hwa742_get_caps(पूर्णांक plane, काष्ठा omapfb_caps *caps)
अणु
	hwa742.पूर्णांक_ctrl->get_caps(plane, caps);
	caps->ctrl |= OMAPFB_CAPS_MANUAL_UPDATE |
		      OMAPFB_CAPS_WINDOW_PIXEL_DOUBLE;
	अगर (hwa742.te_connected)
		caps->ctrl |= OMAPFB_CAPS_TEARSYNC;
	caps->wnd_color |= (1 << OMAPFB_COLOR_RGB565) |
			   (1 << OMAPFB_COLOR_YUV420);
पूर्ण

अटल व्योम hwa742_suspend(व्योम)
अणु
	hwa742.update_mode_beक्रमe_suspend = hwa742.update_mode;
	hwa742_set_update_mode(OMAPFB_UPDATE_DISABLED);
	/* Enable sleep mode */
	hwa742_ग_लिखो_reg(HWA742_POWER_SAVE, 1 << 1);
	clk_disable(hwa742.sys_ck);
पूर्ण

अटल व्योम hwa742_resume(व्योम)
अणु
	clk_enable(hwa742.sys_ck);

	/* Disable sleep mode */
	hwa742_ग_लिखो_reg(HWA742_POWER_SAVE, 0);
	जबतक (1) अणु
		/* Loop until PLL output is stabilized */
		अगर (hwa742_पढ़ो_reg(HWA742_PLL_DIV_REG) & (1 << 7))
			अवरोध;
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(msecs_to_jअगरfies(5));
	पूर्ण
	hwa742_set_update_mode(hwa742.update_mode_beक्रमe_suspend);
पूर्ण

अटल पूर्णांक hwa742_init(काष्ठा omapfb_device *fbdev, पूर्णांक ext_mode,
		       काष्ठा omapfb_mem_desc *req_vram)
अणु
	पूर्णांक r = 0, i;
	u8 rev, conf;
	अचिन्हित दीर्घ ext_clk;
	अचिन्हित दीर्घ sys_clk, pix_clk;
	पूर्णांक extअगर_mem_भाग;
	काष्ठा omapfb_platक्रमm_data *omapfb_conf;

	BUG_ON(!fbdev->ext_अगर || !fbdev->पूर्णांक_ctrl);

	hwa742.fbdev = fbdev;
	hwa742.extअगर = fbdev->ext_अगर;
	hwa742.पूर्णांक_ctrl = fbdev->पूर्णांक_ctrl;

	omapfb_conf = dev_get_platdata(fbdev->dev);

	hwa742.sys_ck = clk_get(शून्य, "hwa_sys_ck");

	spin_lock_init(&hwa742.req_lock);

	अगर ((r = hwa742.पूर्णांक_ctrl->init(fbdev, 1, req_vram)) < 0)
		जाओ err1;

	अगर ((r = hwa742.extअगर->init(fbdev)) < 0)
		जाओ err2;

	ext_clk = clk_get_rate(hwa742.sys_ck);
	अगर ((r = calc_extअगर_timings(ext_clk, &extअगर_mem_भाग)) < 0)
		जाओ err3;
	hwa742.extअगर->set_timings(&hwa742.reg_timings);
	clk_enable(hwa742.sys_ck);

	calc_hwa742_clk_rates(ext_clk, &sys_clk, &pix_clk);
	अगर ((r = calc_extअगर_timings(sys_clk, &extअगर_mem_भाग)) < 0)
		जाओ err4;
	hwa742.extअगर->set_timings(&hwa742.reg_timings);

	rev = hwa742_पढ़ो_reg(HWA742_REV_CODE_REG);
	अगर ((rev & 0xfc) != 0x80) अणु
		dev_err(fbdev->dev, "HWA742: invalid revision %02x\n", rev);
		r = -ENODEV;
		जाओ err4;
	पूर्ण


	अगर (!(hwa742_पढ़ो_reg(HWA742_PLL_DIV_REG) & 0x80)) अणु
		dev_err(fbdev->dev,
		      "HWA742: controller not initialized by the bootloader\n");
		r = -ENODEV;
		जाओ err4;
	पूर्ण

	अगर ((r = setup_tearsync(pix_clk, extअगर_mem_भाग)) < 0) अणु
		dev_err(hwa742.fbdev->dev,
			"HWA742: can't setup tearing synchronization\n");
		जाओ err4;
	पूर्ण
	hwa742.te_connected = 1;

	hwa742.max_transmit_size = hwa742.extअगर->max_transmit_size;

	hwa742.update_mode = OMAPFB_UPDATE_DISABLED;

	hwa742.स्वतः_update_winकरोw.x = 0;
	hwa742.स्वतः_update_winकरोw.y = 0;
	hwa742.स्वतः_update_winकरोw.width = fbdev->panel->x_res;
	hwa742.स्वतः_update_winकरोw.height = fbdev->panel->y_res;
	hwa742.स्वतः_update_winकरोw.क्रमmat = 0;

	समयr_setup(&hwa742.स्वतः_update_समयr, hwa742_update_winकरोw_स्वतः, 0);

	hwa742.prev_color_mode = -1;
	hwa742.prev_flags = 0;

	hwa742.fbdev = fbdev;

	INIT_LIST_HEAD(&hwa742.मुक्त_req_list);
	INIT_LIST_HEAD(&hwa742.pending_req_list);
	क्रम (i = 0; i < ARRAY_SIZE(hwa742.req_pool); i++)
		list_add(&hwa742.req_pool[i].entry, &hwa742.मुक्त_req_list);
	BUG_ON(i <= IRQ_REQ_POOL_SIZE);
	sema_init(&hwa742.req_sema, i - IRQ_REQ_POOL_SIZE);

	conf = hwa742_पढ़ो_reg(HWA742_CONFIG_REG);
	dev_info(fbdev->dev, ": Epson HWA742 LCD controller rev %d "
			"initialized (CNF pins %x)\n", rev & 0x03, conf & 0x07);

	वापस 0;
err4:
	clk_disable(hwa742.sys_ck);
err3:
	hwa742.extअगर->cleanup();
err2:
	hwa742.पूर्णांक_ctrl->cleanup();
err1:
	वापस r;
पूर्ण

अटल व्योम hwa742_cleanup(व्योम)
अणु
	hwa742_set_update_mode(OMAPFB_UPDATE_DISABLED);
	hwa742.extअगर->cleanup();
	hwa742.पूर्णांक_ctrl->cleanup();
	clk_disable(hwa742.sys_ck);
पूर्ण

काष्ठा lcd_ctrl hwa742_ctrl = अणु
	.name			= "hwa742",
	.init			= hwa742_init,
	.cleanup		= hwa742_cleanup,
	.bind_client		= hwa742_bind_client,
	.get_caps		= hwa742_get_caps,
	.set_update_mode	= hwa742_set_update_mode,
	.get_update_mode	= hwa742_get_update_mode,
	.setup_plane		= hwa742_setup_plane,
	.enable_plane		= hwa742_enable_plane,
	.update_winकरोw		= hwa742_update_winकरोw_async,
	.sync			= hwa742_sync,
	.suspend		= hwa742_suspend,
	.resume			= hwa742_resume,
पूर्ण;

