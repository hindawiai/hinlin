<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LCD driver क्रम MIPI DBI-C / DCS compatible LCDs
 *
 * Copyright (C) 2006 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 */
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>

#समावेश <linux/platक्रमm_data/lcd-mipid.h>

#समावेश "omapfb.h"

#घोषणा MIPID_MODULE_NAME		"lcd_mipid"

#घोषणा MIPID_CMD_READ_DISP_ID		0x04
#घोषणा MIPID_CMD_READ_RED		0x06
#घोषणा MIPID_CMD_READ_GREEN		0x07
#घोषणा MIPID_CMD_READ_BLUE		0x08
#घोषणा MIPID_CMD_READ_DISP_STATUS	0x09
#घोषणा MIPID_CMD_RDDSDR		0x0F
#घोषणा MIPID_CMD_SLEEP_IN		0x10
#घोषणा MIPID_CMD_SLEEP_OUT		0x11
#घोषणा MIPID_CMD_DISP_OFF		0x28
#घोषणा MIPID_CMD_DISP_ON		0x29

#घोषणा MIPID_ESD_CHECK_PERIOD		msecs_to_jअगरfies(5000)

#घोषणा to_mipid_device(p)		container_of(p, काष्ठा mipid_device, \
						panel)
काष्ठा mipid_device अणु
	पूर्णांक		enabled;
	पूर्णांक		revision;
	अचिन्हित पूर्णांक	saved_bklight_level;
	अचिन्हित दीर्घ	hw_guard_end;		/* next value of jअगरfies
						   when we can issue the
						   next sleep in/out command */
	अचिन्हित दीर्घ	hw_guard_रुको;		/* max guard समय in jअगरfies */

	काष्ठा omapfb_device	*fbdev;
	काष्ठा spi_device	*spi;
	काष्ठा mutex		mutex;
	काष्ठा lcd_panel	panel;

	काष्ठा delayed_work	esd_work;
	व्योम			(*esd_check)(काष्ठा mipid_device *m);
पूर्ण;

अटल व्योम mipid_transfer(काष्ठा mipid_device *md, पूर्णांक cmd, स्थिर u8 *wbuf,
			   पूर्णांक wlen, u8 *rbuf, पूर्णांक rlen)
अणु
	काष्ठा spi_message	m;
	काष्ठा spi_transfer	*x, xfer[4];
	u16			w;
	पूर्णांक			r;

	BUG_ON(md->spi == शून्य);

	spi_message_init(&m);

	स_रखो(xfer, 0, माप(xfer));
	x = &xfer[0];

	cmd &=  0xff;
	x->tx_buf		= &cmd;
	x->bits_per_word	= 9;
	x->len			= 2;
	spi_message_add_tail(x, &m);

	अगर (wlen) अणु
		x++;
		x->tx_buf		= wbuf;
		x->len			= wlen;
		x->bits_per_word	= 9;
		spi_message_add_tail(x, &m);
	पूर्ण

	अगर (rlen) अणु
		x++;
		x->rx_buf	= &w;
		x->len		= 1;
		spi_message_add_tail(x, &m);

		अगर (rlen > 1) अणु
			/* Arrange क्रम the extra घड़ी beक्रमe the first
			 * data bit.
			 */
			x->bits_per_word = 9;
			x->len		 = 2;

			x++;
			x->rx_buf	 = &rbuf[1];
			x->len		 = rlen - 1;
			spi_message_add_tail(x, &m);
		पूर्ण
	पूर्ण

	r = spi_sync(md->spi, &m);
	अगर (r < 0)
		dev_dbg(&md->spi->dev, "spi_sync %d\n", r);

	अगर (rlen)
		rbuf[0] = w & 0xff;
पूर्ण

अटल अंतरभूत व्योम mipid_cmd(काष्ठा mipid_device *md, पूर्णांक cmd)
अणु
	mipid_transfer(md, cmd, शून्य, 0, शून्य, 0);
पूर्ण

अटल अंतरभूत व्योम mipid_ग_लिखो(काष्ठा mipid_device *md,
			       पूर्णांक reg, स्थिर u8 *buf, पूर्णांक len)
अणु
	mipid_transfer(md, reg, buf, len, शून्य, 0);
पूर्ण

अटल अंतरभूत व्योम mipid_पढ़ो(काष्ठा mipid_device *md,
			      पूर्णांक reg, u8 *buf, पूर्णांक len)
अणु
	mipid_transfer(md, reg, शून्य, 0, buf, len);
पूर्ण

अटल व्योम set_data_lines(काष्ठा mipid_device *md, पूर्णांक data_lines)
अणु
	u16 par;

	चयन (data_lines) अणु
	हाल 16:
		par = 0x150;
		अवरोध;
	हाल 18:
		par = 0x160;
		अवरोध;
	हाल 24:
		par = 0x170;
		अवरोध;
	पूर्ण
	mipid_ग_लिखो(md, 0x3a, (u8 *)&par, 2);
पूर्ण

अटल व्योम send_init_string(काष्ठा mipid_device *md)
अणु
	u16 initpar[] = अणु 0x0102, 0x0100, 0x0100 पूर्ण;

	mipid_ग_लिखो(md, 0xc2, (u8 *)initpar, माप(initpar));
	set_data_lines(md, md->panel.data_lines);
पूर्ण

अटल व्योम hw_guard_start(काष्ठा mipid_device *md, पूर्णांक guard_msec)
अणु
	md->hw_guard_रुको = msecs_to_jअगरfies(guard_msec);
	md->hw_guard_end = jअगरfies + md->hw_guard_रुको;
पूर्ण

अटल व्योम hw_guard_रुको(काष्ठा mipid_device *md)
अणु
	अचिन्हित दीर्घ रुको = md->hw_guard_end - jअगरfies;

	अगर ((दीर्घ)रुको > 0 && समय_beक्रमe_eq(रुको,  md->hw_guard_रुको)) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(रुको);
	पूर्ण
पूर्ण

अटल व्योम set_sleep_mode(काष्ठा mipid_device *md, पूर्णांक on)
अणु
	पूर्णांक cmd, sleep_समय = 50;

	अगर (on)
		cmd = MIPID_CMD_SLEEP_IN;
	अन्यथा
		cmd = MIPID_CMD_SLEEP_OUT;
	hw_guard_रुको(md);
	mipid_cmd(md, cmd);
	hw_guard_start(md, 120);
	/*
	 * When we enable the panel, it seems we _have_ to sleep
	 * 120 ms beक्रमe sending the init string. When disabling the
	 * panel we'll sleep क्रम the duration of 2 frames, so that the
	 * controller can still provide the PCLK,HS,VS संकेतs.
	 */
	अगर (!on)
		sleep_समय = 120;
	msleep(sleep_समय);
पूर्ण

अटल व्योम set_display_state(काष्ठा mipid_device *md, पूर्णांक enabled)
अणु
	पूर्णांक cmd = enabled ? MIPID_CMD_DISP_ON : MIPID_CMD_DISP_OFF;

	mipid_cmd(md, cmd);
पूर्ण

अटल पूर्णांक mipid_set_bklight_level(काष्ठा lcd_panel *panel, अचिन्हित पूर्णांक level)
अणु
	काष्ठा mipid_device *md = to_mipid_device(panel);
	काष्ठा mipid_platक्रमm_data *pd = md->spi->dev.platक्रमm_data;

	अगर (pd->get_bklight_max == शून्य || pd->set_bklight_level == शून्य)
		वापस -ENODEV;
	अगर (level > pd->get_bklight_max(pd))
		वापस -EINVAL;
	अगर (!md->enabled) अणु
		md->saved_bklight_level = level;
		वापस 0;
	पूर्ण
	pd->set_bklight_level(pd, level);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक mipid_get_bklight_level(काष्ठा lcd_panel *panel)
अणु
	काष्ठा mipid_device *md = to_mipid_device(panel);
	काष्ठा mipid_platक्रमm_data *pd = md->spi->dev.platक्रमm_data;

	अगर (pd->get_bklight_level == शून्य)
		वापस -ENODEV;
	वापस pd->get_bklight_level(pd);
पूर्ण

अटल अचिन्हित पूर्णांक mipid_get_bklight_max(काष्ठा lcd_panel *panel)
अणु
	काष्ठा mipid_device *md = to_mipid_device(panel);
	काष्ठा mipid_platक्रमm_data *pd = md->spi->dev.platक्रमm_data;

	अगर (pd->get_bklight_max == शून्य)
		वापस -ENODEV;

	वापस pd->get_bklight_max(pd);
पूर्ण

अटल अचिन्हित दीर्घ mipid_get_caps(काष्ठा lcd_panel *panel)
अणु
	वापस OMAPFB_CAPS_SET_BACKLIGHT;
पूर्ण

अटल u16 पढ़ो_first_pixel(काष्ठा mipid_device *md)
अणु
	u16 pixel;
	u8 red, green, blue;

	mutex_lock(&md->mutex);
	mipid_पढ़ो(md, MIPID_CMD_READ_RED, &red, 1);
	mipid_पढ़ो(md, MIPID_CMD_READ_GREEN, &green, 1);
	mipid_पढ़ो(md, MIPID_CMD_READ_BLUE, &blue, 1);
	mutex_unlock(&md->mutex);

	चयन (md->panel.data_lines) अणु
	हाल 16:
		pixel = ((red >> 1) << 11) | (green << 5) | (blue >> 1);
		अवरोध;
	हाल 24:
		/* 24 bit -> 16 bit */
		pixel = ((red >> 3) << 11) | ((green >> 2) << 5) |
			(blue >> 3);
		अवरोध;
	शेष:
		pixel = 0;
		BUG();
	पूर्ण

	वापस pixel;
पूर्ण

अटल पूर्णांक mipid_run_test(काष्ठा lcd_panel *panel, पूर्णांक test_num)
अणु
	काष्ठा mipid_device *md = to_mipid_device(panel);
	अटल स्थिर u16 test_values[4] = अणु
		0x0000, 0xffff, 0xaaaa, 0x5555,
	पूर्ण;
	पूर्णांक i;

	अगर (test_num != MIPID_TEST_RGB_LINES)
		वापस MIPID_TEST_INVALID;

	क्रम (i = 0; i < ARRAY_SIZE(test_values); i++) अणु
		पूर्णांक delay;
		अचिन्हित दीर्घ पंचांगo;

		omapfb_ग_लिखो_first_pixel(md->fbdev, test_values[i]);
		पंचांगo = jअगरfies + msecs_to_jअगरfies(100);
		delay = 25;
		जबतक (1) अणु
			u16 pixel;

			msleep(delay);
			pixel = पढ़ो_first_pixel(md);
			अगर (pixel == test_values[i])
				अवरोध;
			अगर (समय_after(jअगरfies, पंचांगo)) अणु
				dev_err(&md->spi->dev,
					"MIPI LCD RGB I/F test failed: "
					"expecting %04x, got %04x\n",
					test_values[i], pixel);
				वापस MIPID_TEST_FAILED;
			पूर्ण
			delay = 10;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ls041y3_esd_recover(काष्ठा mipid_device *md)
अणु
	dev_err(&md->spi->dev, "performing LCD ESD recovery\n");
	set_sleep_mode(md, 1);
	set_sleep_mode(md, 0);
पूर्ण

अटल व्योम ls041y3_esd_check_mode1(काष्ठा mipid_device *md)
अणु
	u8 state1, state2;

	mipid_पढ़ो(md, MIPID_CMD_RDDSDR, &state1, 1);
	set_sleep_mode(md, 0);
	mipid_पढ़ो(md, MIPID_CMD_RDDSDR, &state2, 1);
	dev_dbg(&md->spi->dev, "ESD mode 1 state1 %02x state2 %02x\n",
		state1, state2);
	/* Each sleep out command will trigger a self diagnostic and flip
	* Bit6 अगर the test passes.
	*/
	अगर (!((state1 ^ state2) & (1 << 6)))
		ls041y3_esd_recover(md);
पूर्ण

अटल व्योम ls041y3_esd_check_mode2(काष्ठा mipid_device *md)
अणु
	पूर्णांक i;
	u8 rbuf[2];
	अटल स्थिर काष्ठा अणु
		पूर्णांक	cmd;
		पूर्णांक	wlen;
		u16	wbuf[3];
	पूर्ण *rd, rd_ctrl[7] = अणु
		अणु 0xb0, 4, अणु 0x0101, 0x01fe, पूर्ण पूर्ण,
		अणु 0xb1, 4, अणु 0x01de, 0x0121, पूर्ण पूर्ण,
		अणु 0xc2, 4, अणु 0x0100, 0x0100, पूर्ण पूर्ण,
		अणु 0xbd, 2, अणु 0x0100, पूर्ण पूर्ण,
		अणु 0xc2, 4, अणु 0x01fc, 0x0103, पूर्ण पूर्ण,
		अणु 0xb4, 0, पूर्ण,
		अणु 0x00, 0, पूर्ण,
	पूर्ण;

	rd = rd_ctrl;
	क्रम (i = 0; i < 3; i++, rd++)
		mipid_ग_लिखो(md, rd->cmd, (u8 *)rd->wbuf, rd->wlen);

	udelay(10);
	mipid_पढ़ो(md, rd->cmd, rbuf, 2);
	rd++;

	क्रम (i = 0; i < 3; i++, rd++) अणु
		udelay(10);
		mipid_ग_लिखो(md, rd->cmd, (u8 *)rd->wbuf, rd->wlen);
	पूर्ण

	dev_dbg(&md->spi->dev, "ESD mode 2 state %02x\n", rbuf[1]);
	अगर (rbuf[1] == 0x00)
		ls041y3_esd_recover(md);
पूर्ण

अटल व्योम ls041y3_esd_check(काष्ठा mipid_device *md)
अणु
	ls041y3_esd_check_mode1(md);
	अगर (md->revision >= 0x88)
		ls041y3_esd_check_mode2(md);
पूर्ण

अटल व्योम mipid_esd_start_check(काष्ठा mipid_device *md)
अणु
	अगर (md->esd_check != शून्य)
		schedule_delayed_work(&md->esd_work,
				   MIPID_ESD_CHECK_PERIOD);
पूर्ण

अटल व्योम mipid_esd_stop_check(काष्ठा mipid_device *md)
अणु
	अगर (md->esd_check != शून्य)
		cancel_delayed_work_sync(&md->esd_work);
पूर्ण

अटल व्योम mipid_esd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mipid_device *md = container_of(work, काष्ठा mipid_device,
					       esd_work.work);

	mutex_lock(&md->mutex);
	md->esd_check(md);
	mutex_unlock(&md->mutex);
	mipid_esd_start_check(md);
पूर्ण

अटल पूर्णांक mipid_enable(काष्ठा lcd_panel *panel)
अणु
	काष्ठा mipid_device *md = to_mipid_device(panel);

	mutex_lock(&md->mutex);

	अगर (md->enabled) अणु
		mutex_unlock(&md->mutex);
		वापस 0;
	पूर्ण
	set_sleep_mode(md, 0);
	md->enabled = 1;
	send_init_string(md);
	set_display_state(md, 1);
	mipid_set_bklight_level(panel, md->saved_bklight_level);
	mipid_esd_start_check(md);

	mutex_unlock(&md->mutex);
	वापस 0;
पूर्ण

अटल व्योम mipid_disable(काष्ठा lcd_panel *panel)
अणु
	काष्ठा mipid_device *md = to_mipid_device(panel);

	/*
	 * A final ESD work might be called beक्रमe वापसing,
	 * so करो this without holding the lock.
	 */
	mipid_esd_stop_check(md);
	mutex_lock(&md->mutex);

	अगर (!md->enabled) अणु
		mutex_unlock(&md->mutex);
		वापस;
	पूर्ण
	md->saved_bklight_level = mipid_get_bklight_level(panel);
	mipid_set_bklight_level(panel, 0);
	set_display_state(md, 0);
	set_sleep_mode(md, 1);
	md->enabled = 0;

	mutex_unlock(&md->mutex);
पूर्ण

अटल पूर्णांक panel_enabled(काष्ठा mipid_device *md)
अणु
	u32 disp_status;
	पूर्णांक enabled;

	mipid_पढ़ो(md, MIPID_CMD_READ_DISP_STATUS, (u8 *)&disp_status, 4);
	disp_status = __be32_to_cpu(disp_status);
	enabled = (disp_status & (1 << 17)) && (disp_status & (1 << 10));
	dev_dbg(&md->spi->dev,
		"LCD panel %senabled by bootloader (status 0x%04x)\n",
		enabled ? "" : "not ", disp_status);
	वापस enabled;
पूर्ण

अटल पूर्णांक mipid_init(काष्ठा lcd_panel *panel,
			    काष्ठा omapfb_device *fbdev)
अणु
	काष्ठा mipid_device *md = to_mipid_device(panel);

	md->fbdev = fbdev;
	INIT_DELAYED_WORK(&md->esd_work, mipid_esd_work);
	mutex_init(&md->mutex);

	md->enabled = panel_enabled(md);

	अगर (md->enabled)
		mipid_esd_start_check(md);
	अन्यथा
		md->saved_bklight_level = mipid_get_bklight_level(panel);

	वापस 0;
पूर्ण

अटल व्योम mipid_cleanup(काष्ठा lcd_panel *panel)
अणु
	काष्ठा mipid_device *md = to_mipid_device(panel);

	अगर (md->enabled)
		mipid_esd_stop_check(md);
पूर्ण

अटल स्थिर काष्ठा lcd_panel mipid_panel = अणु
	.config		= OMAP_LCDC_PANEL_TFT,

	.bpp		= 16,
	.x_res		= 800,
	.y_res		= 480,
	.pixel_घड़ी	= 21940,
	.hsw		= 50,
	.hfp		= 20,
	.hbp		= 15,
	.vsw		= 2,
	.vfp		= 1,
	.vbp		= 3,

	.init			= mipid_init,
	.cleanup		= mipid_cleanup,
	.enable			= mipid_enable,
	.disable		= mipid_disable,
	.get_caps		= mipid_get_caps,
	.set_bklight_level	= mipid_set_bklight_level,
	.get_bklight_level	= mipid_get_bklight_level,
	.get_bklight_max	= mipid_get_bklight_max,
	.run_test		= mipid_run_test,
पूर्ण;

अटल पूर्णांक mipid_detect(काष्ठा mipid_device *md)
अणु
	काष्ठा mipid_platक्रमm_data *pdata;
	u8 display_id[3];

	pdata = md->spi->dev.platक्रमm_data;
	अगर (pdata == शून्य) अणु
		dev_err(&md->spi->dev, "missing platform data\n");
		वापस -ENOENT;
	पूर्ण

	mipid_पढ़ो(md, MIPID_CMD_READ_DISP_ID, display_id, 3);
	dev_dbg(&md->spi->dev, "MIPI display ID: %02x%02x%02x\n",
		display_id[0], display_id[1], display_id[2]);

	चयन (display_id[0]) अणु
	हाल 0x45:
		md->panel.name = "lph8923";
		अवरोध;
	हाल 0x83:
		md->panel.name = "ls041y3";
		md->esd_check = ls041y3_esd_check;
		अवरोध;
	शेष:
		md->panel.name = "unknown";
		dev_err(&md->spi->dev, "invalid display ID\n");
		वापस -ENODEV;
	पूर्ण

	md->revision = display_id[1];
	md->panel.data_lines = pdata->data_lines;
	pr_info("omapfb: %s rev %02x LCD detected, %d data lines\n",
			md->panel.name, md->revision, md->panel.data_lines);

	वापस 0;
पूर्ण

अटल पूर्णांक mipid_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा mipid_device *md;
	पूर्णांक r;

	md = kzalloc(माप(*md), GFP_KERNEL);
	अगर (md == शून्य) अणु
		dev_err(&spi->dev, "out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	spi->mode = SPI_MODE_0;
	md->spi = spi;
	dev_set_drvdata(&spi->dev, md);
	md->panel = mipid_panel;

	r = mipid_detect(md);
	अगर (r < 0)
		वापस r;

	omapfb_रेजिस्टर_panel(&md->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक mipid_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा mipid_device *md = dev_get_drvdata(&spi->dev);

	mipid_disable(&md->panel);
	kमुक्त(md);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver mipid_spi_driver = अणु
	.driver = अणु
		.name	= MIPID_MODULE_NAME,
	पूर्ण,
	.probe	= mipid_spi_probe,
	.हटाओ	= mipid_spi_हटाओ,
पूर्ण;

module_spi_driver(mipid_spi_driver);

MODULE_DESCRIPTION("MIPI display driver");
MODULE_LICENSE("GPL");
