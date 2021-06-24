<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/video/mmp/panel/tpo_tj032md01bw.c
 * active panel using spi पूर्णांकerface to करो init
 *
 * Copyright (C) 2012 Marvell Technology Group Ltd.
 * Authors:  Guoqing Li <ligq@marvell.com>
 *          Lisa Du <cldu@marvell.com>
 *          Zhou Zhu <zzhu3@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/spi/spi.h>
#समावेश <video/mmp_disp.h>

अटल u16 init[] = अणु
	0x0801,
	0x0800,
	0x0200,
	0x0304,
	0x040e,
	0x0903,
	0x0b18,
	0x0c53,
	0x0d01,
	0x0ee0,
	0x0f01,
	0x1058,
	0x201e,
	0x210a,
	0x220a,
	0x231e,
	0x2400,
	0x2532,
	0x2600,
	0x27ac,
	0x2904,
	0x2aa2,
	0x2b45,
	0x2c45,
	0x2d15,
	0x2e5a,
	0x2fff,
	0x306b,
	0x310d,
	0x3248,
	0x3382,
	0x34bd,
	0x35e7,
	0x3618,
	0x3794,
	0x3801,
	0x395d,
	0x3aae,
	0x3bff,
	0x07c9,
पूर्ण;

अटल u16 घातeroff[] = अणु
	0x07d9,
पूर्ण;

काष्ठा tpohvga_plat_data अणु
	व्योम (*plat_onoff)(पूर्णांक status);
	काष्ठा spi_device *spi;
पूर्ण;

अटल व्योम tpohvga_onoff(काष्ठा mmp_panel *panel, पूर्णांक status)
अणु
	काष्ठा tpohvga_plat_data *plat = panel->plat_data;
	पूर्णांक ret;

	अगर (status) अणु
		plat->plat_onoff(1);

		ret = spi_ग_लिखो(plat->spi, init, माप(init));
		अगर (ret < 0)
			dev_warn(panel->dev, "init cmd failed(%d)\n", ret);
	पूर्ण अन्यथा अणु
		ret = spi_ग_लिखो(plat->spi, घातeroff, माप(घातeroff));
		अगर (ret < 0)
			dev_warn(panel->dev, "poweroff cmd failed(%d)\n", ret);

		plat->plat_onoff(0);
	पूर्ण
पूर्ण

अटल काष्ठा mmp_mode mmp_modes_tpohvga[] = अणु
	[0] = अणु
		.pixघड़ी_freq = 10394400,
		.refresh = 60,
		.xres = 320,
		.yres = 480,
		.hsync_len = 10,
		.left_margin = 15,
		.right_margin = 10,
		.vsync_len = 2,
		.upper_margin = 4,
		.lower_margin = 2,
		.invert_pixघड़ी = 1,
		.pix_fmt_out = PIXFMT_RGB565,
	पूर्ण,
पूर्ण;

अटल पूर्णांक tpohvga_get_modelist(काष्ठा mmp_panel *panel,
		काष्ठा mmp_mode **modelist)
अणु
	*modelist = mmp_modes_tpohvga;
	वापस 1;
पूर्ण

अटल काष्ठा mmp_panel panel_tpohvga = अणु
	.name = "tpohvga",
	.panel_type = PANELTYPE_ACTIVE,
	.get_modelist = tpohvga_get_modelist,
	.set_onoff = tpohvga_onoff,
पूर्ण;

अटल पूर्णांक tpohvga_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा mmp_mach_panel_info *mi;
	पूर्णांक ret;
	काष्ठा tpohvga_plat_data *plat_data;

	/* get configs from platक्रमm data */
	mi = spi->dev.platक्रमm_data;
	अगर (mi == शून्य) अणु
		dev_err(&spi->dev, "%s: no platform data defined\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* setup spi related info */
	spi->bits_per_word = 16;
	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "spi setup failed %d", ret);
		वापस ret;
	पूर्ण

	plat_data = kzalloc(माप(*plat_data), GFP_KERNEL);
	अगर (plat_data == शून्य)
		वापस -ENOMEM;

	plat_data->spi = spi;
	plat_data->plat_onoff = mi->plat_set_onoff;
	panel_tpohvga.plat_data = plat_data;
	panel_tpohvga.plat_path_name = mi->plat_path_name;
	panel_tpohvga.dev = &spi->dev;

	mmp_रेजिस्टर_panel(&panel_tpohvga);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver panel_tpohvga_driver = अणु
	.driver		= अणु
		.name	= "tpo-hvga",
	पूर्ण,
	.probe		= tpohvga_probe,
पूर्ण;
module_spi_driver(panel_tpohvga_driver);

MODULE_AUTHOR("Lisa Du<cldu@marvell.com>");
MODULE_DESCRIPTION("Panel driver for tpohvga");
MODULE_LICENSE("GPL");
