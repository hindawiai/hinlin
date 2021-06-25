<शैली गुरु>
/*
 * broadsheetfb.c -- FB driver क्रम E-Ink Broadsheet controller
 *
 * Copyright (C) 2008, Jaya Kumar
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Layout is based on skeletonfb.c by James Simmons and Geert Uytterhoeven.
 *
 * This driver is written to be used with the Broadsheet display controller.
 *
 * It is पूर्णांकended to be architecture independent. A board specअगरic driver
 * must be used to perक्रमm all the physical IO पूर्णांकeractions.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/list.h>
#समावेश <linux/firmware.h>
#समावेश <linux/uaccess.h>

#समावेश <video/broadsheetfb.h>

/* track panel specअगरic parameters */
काष्ठा panel_info अणु
	पूर्णांक w;
	पूर्णांक h;
	u16 sdcfg;
	u16 gdcfg;
	u16 lutfmt;
	u16 fsynclen;
	u16 fendfbegin;
	u16 lsynclen;
	u16 lendlbegin;
	u16 pixclk;
पूर्ण;

/* table of panel specअगरic parameters to be indexed पूर्णांकo by the board drivers */
अटल काष्ठा panel_info panel_table[] = अणु
	अणु	/* standard 6" on TFT backplane */
		.w = 800,
		.h = 600,
		.sdcfg = (100 | (1 << 8) | (1 << 9)),
		.gdcfg = 2,
		.lutfmt = (4 | (1 << 7)),
		.fsynclen = 4,
		.fendfbegin = (10 << 8) | 4,
		.lsynclen = 10,
		.lendlbegin = (100 << 8) | 4,
		.pixclk = 6,
	पूर्ण,
	अणु	/* custom 3.7" flexible on PET or steel */
		.w = 320,
		.h = 240,
		.sdcfg = (67 | (0 << 8) | (0 << 9) | (0 << 10) | (0 << 12)),
		.gdcfg = 3,
		.lutfmt = (4 | (1 << 7)),
		.fsynclen = 0,
		.fendfbegin = (80 << 8) | 4,
		.lsynclen = 10,
		.lendlbegin = (80 << 8) | 20,
		.pixclk = 14,
	पूर्ण,
	अणु	/* standard 9.7" on TFT backplane */
		.w = 1200,
		.h = 825,
		.sdcfg = (100 | (1 << 8) | (1 << 9) | (0 << 10) | (0 << 12)),
		.gdcfg = 2,
		.lutfmt = (4 | (1 << 7)),
		.fsynclen = 0,
		.fendfbegin = (4 << 8) | 4,
		.lsynclen = 4,
		.lendlbegin = (60 << 8) | 10,
		.pixclk = 3,
	पूर्ण,
पूर्ण;

#घोषणा DPY_W 800
#घोषणा DPY_H 600

अटल काष्ठा fb_fix_screeninfo broadsheetfb_fix = अणु
	.id =		"broadsheetfb",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_STATIC_PSEUDOCOLOR,
	.xpanstep =	0,
	.ypanstep =	0,
	.ywrapstep =	0,
	.line_length =	DPY_W,
	.accel =	FB_ACCEL_NONE,
पूर्ण;

अटल काष्ठा fb_var_screeninfo broadsheetfb_var = अणु
	.xres		= DPY_W,
	.yres		= DPY_H,
	.xres_भव	= DPY_W,
	.yres_भव	= DPY_H,
	.bits_per_pixel	= 8,
	.grayscale	= 1,
	.red =		अणु 0, 4, 0 पूर्ण,
	.green =	अणु 0, 4, 0 पूर्ण,
	.blue =		अणु 0, 4, 0 पूर्ण,
	.transp =	अणु 0, 0, 0 पूर्ण,
पूर्ण;

/* मुख्य broadsheetfb functions */
अटल व्योम broadsheet_gpio_issue_data(काष्ठा broadsheetfb_par *par, u16 data)
अणु
	par->board->set_ctl(par, BS_WR, 0);
	par->board->set_hdb(par, data);
	par->board->set_ctl(par, BS_WR, 1);
पूर्ण

अटल व्योम broadsheet_gpio_issue_cmd(काष्ठा broadsheetfb_par *par, u16 data)
अणु
	par->board->set_ctl(par, BS_DC, 0);
	broadsheet_gpio_issue_data(par, data);
पूर्ण

अटल व्योम broadsheet_gpio_send_command(काष्ठा broadsheetfb_par *par, u16 data)
अणु
	par->board->रुको_क्रम_rdy(par);

	par->board->set_ctl(par, BS_CS, 0);
	broadsheet_gpio_issue_cmd(par, data);
	par->board->set_ctl(par, BS_DC, 1);
	par->board->set_ctl(par, BS_CS, 1);
पूर्ण

अटल व्योम broadsheet_gpio_send_cmdargs(काष्ठा broadsheetfb_par *par, u16 cmd,
					पूर्णांक argc, u16 *argv)
अणु
	पूर्णांक i;

	par->board->रुको_क्रम_rdy(par);

	par->board->set_ctl(par, BS_CS, 0);
	broadsheet_gpio_issue_cmd(par, cmd);
	par->board->set_ctl(par, BS_DC, 1);

	क्रम (i = 0; i < argc; i++)
		broadsheet_gpio_issue_data(par, argv[i]);
	par->board->set_ctl(par, BS_CS, 1);
पूर्ण

अटल व्योम broadsheet_mmio_send_cmdargs(काष्ठा broadsheetfb_par *par, u16 cmd,
				    पूर्णांक argc, u16 *argv)
अणु
	पूर्णांक i;

	par->board->mmio_ग_लिखो(par, BS_MMIO_CMD, cmd);

	क्रम (i = 0; i < argc; i++)
		par->board->mmio_ग_लिखो(par, BS_MMIO_DATA, argv[i]);
पूर्ण

अटल व्योम broadsheet_send_command(काष्ठा broadsheetfb_par *par, u16 data)
अणु
	अगर (par->board->mmio_ग_लिखो)
		par->board->mmio_ग_लिखो(par, BS_MMIO_CMD, data);
	अन्यथा
		broadsheet_gpio_send_command(par, data);
पूर्ण

अटल व्योम broadsheet_send_cmdargs(काष्ठा broadsheetfb_par *par, u16 cmd,
				    पूर्णांक argc, u16 *argv)
अणु
	अगर (par->board->mmio_ग_लिखो)
		broadsheet_mmio_send_cmdargs(par, cmd, argc, argv);
	अन्यथा
		broadsheet_gpio_send_cmdargs(par, cmd, argc, argv);
पूर्ण

अटल व्योम broadsheet_gpio_burst_ग_लिखो(काष्ठा broadsheetfb_par *par, पूर्णांक size,
					u16 *data)
अणु
	पूर्णांक i;
	u16 पंचांगp;

	par->board->set_ctl(par, BS_CS, 0);
	par->board->set_ctl(par, BS_DC, 1);

	क्रम (i = 0; i < size; i++) अणु
		par->board->set_ctl(par, BS_WR, 0);
		पंचांगp = (data[i] & 0x0F) << 4;
		पंचांगp |= (data[i] & 0x0F00) << 4;
		par->board->set_hdb(par, पंचांगp);
		par->board->set_ctl(par, BS_WR, 1);
	पूर्ण

	par->board->set_ctl(par, BS_CS, 1);
पूर्ण

अटल व्योम broadsheet_mmio_burst_ग_लिखो(काष्ठा broadsheetfb_par *par, पूर्णांक size,
				   u16 *data)
अणु
	पूर्णांक i;
	u16 पंचांगp;

	क्रम (i = 0; i < size; i++) अणु
		पंचांगp = (data[i] & 0x0F) << 4;
		पंचांगp |= (data[i] & 0x0F00) << 4;
		par->board->mmio_ग_लिखो(par, BS_MMIO_DATA, पंचांगp);
	पूर्ण

पूर्ण

अटल व्योम broadsheet_burst_ग_लिखो(काष्ठा broadsheetfb_par *par, पूर्णांक size,
				   u16 *data)
अणु
	अगर (par->board->mmio_ग_लिखो)
		broadsheet_mmio_burst_ग_लिखो(par, size, data);
	अन्यथा
		broadsheet_gpio_burst_ग_लिखो(par, size, data);
पूर्ण

अटल u16 broadsheet_gpio_get_data(काष्ठा broadsheetfb_par *par)
अणु
	u16 res;
	/* रुको क्रम पढ़ोy to go hi. (lo is busy) */
	par->board->रुको_क्रम_rdy(par);

	/* cs lo, dc lo क्रम cmd, we lo क्रम each data, db as usual */
	par->board->set_ctl(par, BS_DC, 1);
	par->board->set_ctl(par, BS_CS, 0);
	par->board->set_ctl(par, BS_WR, 0);

	res = par->board->get_hdb(par);

	/* strobe wr */
	par->board->set_ctl(par, BS_WR, 1);
	par->board->set_ctl(par, BS_CS, 1);

	वापस res;
पूर्ण


अटल u16 broadsheet_get_data(काष्ठा broadsheetfb_par *par)
अणु
	अगर (par->board->mmio_पढ़ो)
		वापस par->board->mmio_पढ़ो(par);
	अन्यथा
		वापस broadsheet_gpio_get_data(par);
पूर्ण

अटल व्योम broadsheet_gpio_ग_लिखो_reg(काष्ठा broadsheetfb_par *par, u16 reg,
					u16 data)
अणु
	/* रुको क्रम पढ़ोy to go hi. (lo is busy) */
	par->board->रुको_क्रम_rdy(par);

	/* cs lo, dc lo क्रम cmd, we lo क्रम each data, db as usual */
	par->board->set_ctl(par, BS_CS, 0);

	broadsheet_gpio_issue_cmd(par, BS_CMD_WR_REG);

	par->board->set_ctl(par, BS_DC, 1);

	broadsheet_gpio_issue_data(par, reg);
	broadsheet_gpio_issue_data(par, data);

	par->board->set_ctl(par, BS_CS, 1);
पूर्ण

अटल व्योम broadsheet_mmio_ग_लिखो_reg(काष्ठा broadsheetfb_par *par, u16 reg,
				 u16 data)
अणु
	par->board->mmio_ग_लिखो(par, BS_MMIO_CMD, BS_CMD_WR_REG);
	par->board->mmio_ग_लिखो(par, BS_MMIO_DATA, reg);
	par->board->mmio_ग_लिखो(par, BS_MMIO_DATA, data);

पूर्ण

अटल व्योम broadsheet_ग_लिखो_reg(काष्ठा broadsheetfb_par *par, u16 reg,
					u16 data)
अणु
	अगर (par->board->mmio_ग_लिखो)
		broadsheet_mmio_ग_लिखो_reg(par, reg, data);
	अन्यथा
		broadsheet_gpio_ग_लिखो_reg(par, reg, data);
पूर्ण

अटल व्योम broadsheet_ग_लिखो_reg32(काष्ठा broadsheetfb_par *par, u16 reg,
					u32 data)
अणु
	broadsheet_ग_लिखो_reg(par, reg, cpu_to_le32(data) & 0xFFFF);
	broadsheet_ग_लिखो_reg(par, reg + 2, (cpu_to_le32(data) >> 16) & 0xFFFF);
पूर्ण


अटल u16 broadsheet_पढ़ो_reg(काष्ठा broadsheetfb_par *par, u16 reg)
अणु
	broadsheet_send_cmdargs(par, BS_CMD_RD_REG, 1, &reg);
	par->board->रुको_क्रम_rdy(par);
	वापस broadsheet_get_data(par);
पूर्ण

/* functions क्रम waveक्रमm manipulation */
अटल पूर्णांक is_broadsheet_pll_locked(काष्ठा broadsheetfb_par *par)
अणु
	वापस broadsheet_पढ़ो_reg(par, 0x000A) & 0x0001;
पूर्ण

अटल पूर्णांक broadsheet_setup_plls(काष्ठा broadsheetfb_par *par)
अणु
	पूर्णांक retry_count = 0;
	u16 पंचांगp;

	/* disable arral saemipu mode */
	broadsheet_ग_लिखो_reg(par, 0x0006, 0x0000);

	broadsheet_ग_लिखो_reg(par, 0x0010, 0x0004);
	broadsheet_ग_लिखो_reg(par, 0x0012, 0x5949);
	broadsheet_ग_लिखो_reg(par, 0x0014, 0x0040);
	broadsheet_ग_लिखो_reg(par, 0x0016, 0x0000);

	करो अणु
		अगर (retry_count++ > 100)
			वापस -ETIMEDOUT;
		mdelay(1);
	पूर्ण जबतक (!is_broadsheet_pll_locked(par));

	पंचांगp = broadsheet_पढ़ो_reg(par, 0x0006);
	पंचांगp &= ~0x1;
	broadsheet_ग_लिखो_reg(par, 0x0006, पंचांगp);

	वापस 0;
पूर्ण

अटल पूर्णांक broadsheet_setup_spi(काष्ठा broadsheetfb_par *par)
अणु

	broadsheet_ग_लिखो_reg(par, 0x0204, ((3 << 3) | 1));
	broadsheet_ग_लिखो_reg(par, 0x0208, 0x0001);

	वापस 0;
पूर्ण

अटल पूर्णांक broadsheet_setup_spअगरlash(काष्ठा broadsheetfb_par *par,
						u16 *orig_sfmcd)
अणु

	*orig_sfmcd = broadsheet_पढ़ो_reg(par, 0x0204);
	broadsheet_ग_लिखो_reg(par, 0x0208, 0);
	broadsheet_ग_लिखो_reg(par, 0x0204, 0);
	broadsheet_ग_लिखो_reg(par, 0x0204, ((3 << 3) | 1));

	वापस 0;
पूर्ण

अटल पूर्णांक broadsheet_spअगरlash_रुको_क्रम_bit(काष्ठा broadsheetfb_par *par,
						u16 reg, पूर्णांक bitnum, पूर्णांक val,
						पूर्णांक समयout)
अणु
	u16 पंचांगp;

	करो अणु
		पंचांगp = broadsheet_पढ़ो_reg(par, reg);
		अगर (((पंचांगp >> bitnum) & 1) == val)
			वापस 0;
		mdelay(1);
	पूर्ण जबतक (समयout--);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक broadsheet_spअगरlash_ग_लिखो_byte(काष्ठा broadsheetfb_par *par, u8 data)
अणु
	broadsheet_ग_लिखो_reg(par, 0x0202, (data | 0x100));

	वापस broadsheet_spअगरlash_रुको_क्रम_bit(par, 0x0206, 3, 0, 100);
पूर्ण

अटल पूर्णांक broadsheet_spअगरlash_पढ़ो_byte(काष्ठा broadsheetfb_par *par, u8 *data)
अणु
	पूर्णांक err;
	u16 पंचांगp;

	broadsheet_ग_लिखो_reg(par, 0x0202, 0);

	err = broadsheet_spअगरlash_रुको_क्रम_bit(par, 0x0206, 3, 0, 100);
	अगर (err)
		वापस err;

	पंचांगp = broadsheet_पढ़ो_reg(par, 0x200);

	*data = पंचांगp & 0xFF;

	वापस 0;
पूर्ण

अटल पूर्णांक broadsheet_spअगरlash_रुको_क्रम_status(काष्ठा broadsheetfb_par *par,
								पूर्णांक समयout)
अणु
	u8 पंचांगp;
	पूर्णांक err;

	करो अणु
		broadsheet_ग_लिखो_reg(par, 0x0208, 1);

		err = broadsheet_spअगरlash_ग_लिखो_byte(par, 0x05);
		अगर (err)
			जाओ failout;

		err = broadsheet_spअगरlash_पढ़ो_byte(par, &पंचांगp);
		अगर (err)
			जाओ failout;

		broadsheet_ग_लिखो_reg(par, 0x0208, 0);

		अगर (!(पंचांगp & 0x1))
			वापस 0;

		mdelay(5);
	पूर्ण जबतक (समयout--);

	dev_err(par->info->device, "Timed out waiting for spiflash status\n");
	वापस -ETIMEDOUT;

failout:
	broadsheet_ग_लिखो_reg(par, 0x0208, 0);
	वापस err;
पूर्ण

अटल पूर्णांक broadsheet_spअगरlash_op_on_address(काष्ठा broadsheetfb_par *par,
							u8 op, u32 addr)
अणु
	पूर्णांक i;
	u8 पंचांगp;
	पूर्णांक err;

	broadsheet_ग_लिखो_reg(par, 0x0208, 1);

	err = broadsheet_spअगरlash_ग_लिखो_byte(par, op);
	अगर (err)
		वापस err;

	क्रम (i = 2; i >= 0; i--) अणु
		पंचांगp = ((addr >> (i * 8)) & 0xFF);
		err = broadsheet_spअगरlash_ग_लिखो_byte(par, पंचांगp);
		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक broadsheet_verअगरy_spअगरlash(काष्ठा broadsheetfb_par *par,
						पूर्णांक *flash_type)
अणु
	पूर्णांक err = 0;
	u8 sig;

	err = broadsheet_spअगरlash_op_on_address(par, 0xAB, 0x00000000);
	अगर (err)
		जाओ failout;

	err = broadsheet_spअगरlash_पढ़ो_byte(par, &sig);
	अगर (err)
		जाओ failout;

	अगर ((sig != 0x10) && (sig != 0x11)) अणु
		dev_err(par->info->device, "Unexpected flash type\n");
		err = -EINVAL;
		जाओ failout;
	पूर्ण

	*flash_type = sig;

failout:
	broadsheet_ग_लिखो_reg(par, 0x0208, 0);
	वापस err;
पूर्ण

अटल पूर्णांक broadsheet_setup_क्रम_wfm_ग_लिखो(काष्ठा broadsheetfb_par *par,
					u16 *initial_sfmcd, पूर्णांक *flash_type)

अणु
	पूर्णांक err;

	err = broadsheet_setup_plls(par);
	अगर (err)
		वापस err;

	broadsheet_ग_लिखो_reg(par, 0x0106, 0x0203);

	err = broadsheet_setup_spi(par);
	अगर (err)
		वापस err;

	err = broadsheet_setup_spअगरlash(par, initial_sfmcd);
	अगर (err)
		वापस err;

	वापस broadsheet_verअगरy_spअगरlash(par, flash_type);
पूर्ण

अटल पूर्णांक broadsheet_spअगरlash_ग_लिखो_control(काष्ठा broadsheetfb_par *par,
						पूर्णांक mode)
अणु
	पूर्णांक err;

	broadsheet_ग_लिखो_reg(par, 0x0208, 1);
	अगर (mode)
		err = broadsheet_spअगरlash_ग_लिखो_byte(par, 0x06);
	अन्यथा
		err = broadsheet_spअगरlash_ग_लिखो_byte(par, 0x04);

	broadsheet_ग_लिखो_reg(par, 0x0208, 0);
	वापस err;
पूर्ण

अटल पूर्णांक broadsheet_spअगरlash_erase_sector(काष्ठा broadsheetfb_par *par,
						पूर्णांक addr)
अणु
	पूर्णांक err;

	broadsheet_spअगरlash_ग_लिखो_control(par, 1);

	err = broadsheet_spअगरlash_op_on_address(par, 0xD8, addr);

	broadsheet_ग_लिखो_reg(par, 0x0208, 0);

	अगर (err)
		वापस err;

	err = broadsheet_spअगरlash_रुको_क्रम_status(par, 1000);

	वापस err;
पूर्ण

अटल पूर्णांक broadsheet_spअगरlash_पढ़ो_range(काष्ठा broadsheetfb_par *par,
						पूर्णांक addr, पूर्णांक size, अक्षर *data)
अणु
	पूर्णांक err;
	पूर्णांक i;

	err = broadsheet_spअगरlash_op_on_address(par, 0x03, addr);
	अगर (err)
		जाओ failout;

	क्रम (i = 0; i < size; i++) अणु
		err = broadsheet_spअगरlash_पढ़ो_byte(par, &data[i]);
		अगर (err)
			जाओ failout;
	पूर्ण

failout:
	broadsheet_ग_लिखो_reg(par, 0x0208, 0);
	वापस err;
पूर्ण

#घोषणा BS_SPIFLASH_PAGE_SIZE 256
अटल पूर्णांक broadsheet_spअगरlash_ग_लिखो_page(काष्ठा broadsheetfb_par *par,
						पूर्णांक addr, स्थिर अक्षर *data)
अणु
	पूर्णांक err;
	पूर्णांक i;

	broadsheet_spअगरlash_ग_लिखो_control(par, 1);

	err = broadsheet_spअगरlash_op_on_address(par, 0x02, addr);
	अगर (err)
		जाओ failout;

	क्रम (i = 0; i < BS_SPIFLASH_PAGE_SIZE; i++) अणु
		err = broadsheet_spअगरlash_ग_लिखो_byte(par, data[i]);
		अगर (err)
			जाओ failout;
	पूर्ण

	broadsheet_ग_लिखो_reg(par, 0x0208, 0);

	err = broadsheet_spअगरlash_रुको_क्रम_status(par, 100);

failout:
	वापस err;
पूर्ण

अटल पूर्णांक broadsheet_spअगरlash_ग_लिखो_sector(काष्ठा broadsheetfb_par *par,
				पूर्णांक addr, स्थिर अक्षर *data, पूर्णांक sector_size)
अणु
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < sector_size; i += BS_SPIFLASH_PAGE_SIZE) अणु
		err = broadsheet_spअगरlash_ग_लिखो_page(par, addr + i, &data[i]);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * The caller must guarantee that the data to be rewritten is entirely
 * contained within this sector. That is, data_start_addr + data_len
 * must be less than sector_start_addr + sector_size.
 */
अटल पूर्णांक broadsheet_spअगरlash_reग_लिखो_sector(काष्ठा broadsheetfb_par *par,
					पूर्णांक sector_size, पूर्णांक data_start_addr,
					पूर्णांक data_len, स्थिर अक्षर *data)
अणु
	पूर्णांक err;
	अक्षर *sector_buffer;
	पूर्णांक tail_start_addr;
	पूर्णांक start_sector_addr;

	sector_buffer = kzalloc(sector_size, GFP_KERNEL);
	अगर (!sector_buffer)
		वापस -ENOMEM;

	/* the start address of the sector is the 0th byte of that sector */
	start_sector_addr = (data_start_addr / sector_size) * sector_size;

	/*
	 * check अगर there is head data that we need to पढ़ोback पूर्णांकo our sector
	 * buffer first
	 */
	अगर (data_start_addr != start_sector_addr) अणु
		/*
		 * we need to पढ़ो every byte up till the start address of our
		 * data and we put it पूर्णांकo our sector buffer.
		 */
		err = broadsheet_spअगरlash_पढ़ो_range(par, start_sector_addr,
						data_start_addr, sector_buffer);
		अगर (err)
			जाओ out;
	पूर्ण

	/* now we copy our data पूर्णांकo the right place in the sector buffer */
	स_नकल(sector_buffer + data_start_addr, data, data_len);

	/*
	 * now we check अगर there is a tail section of the sector that we need to
	 * पढ़ोback.
	 */
	tail_start_addr = (data_start_addr + data_len) % sector_size;

	अगर (tail_start_addr) अणु
		पूर्णांक tail_len;

		tail_len = sector_size - tail_start_addr;

		/* now we पढ़ो this tail पूर्णांकo our sector buffer */
		err = broadsheet_spअगरlash_पढ़ो_range(par, tail_start_addr,
			tail_len, sector_buffer + tail_start_addr);
		अगर (err)
			जाओ out;
	पूर्ण

	/* अगर we got here we have the full sector that we want to reग_लिखो. */

	/* first erase the sector */
	err = broadsheet_spअगरlash_erase_sector(par, start_sector_addr);
	अगर (err)
		जाओ out;

	/* now ग_लिखो it */
	err = broadsheet_spअगरlash_ग_लिखो_sector(par, start_sector_addr,
					sector_buffer, sector_size);
out:
	kमुक्त(sector_buffer);
	वापस err;
पूर्ण

अटल पूर्णांक broadsheet_ग_लिखो_spअगरlash(काष्ठा broadsheetfb_par *par, u32 wfm_addr,
				स्थिर u8 *wfm, पूर्णांक bytecount, पूर्णांक flash_type)
अणु
	पूर्णांक sector_size;
	पूर्णांक err;
	पूर्णांक cur_addr;
	पूर्णांक ग_लिखोcount;
	पूर्णांक maxlen;
	पूर्णांक offset = 0;

	चयन (flash_type) अणु
	हाल 0x10:
		sector_size = 32*1024;
		अवरोध;
	हाल 0x11:
	शेष:
		sector_size = 64*1024;
		अवरोध;
	पूर्ण

	जबतक (bytecount) अणु
		cur_addr = wfm_addr + offset;
		maxlen = roundup(cur_addr, sector_size) - cur_addr;
		ग_लिखोcount = min(bytecount, maxlen);

		err = broadsheet_spअगरlash_reग_लिखो_sector(par, sector_size,
				cur_addr, ग_लिखोcount, wfm + offset);
		अगर (err)
			वापस err;

		offset += ग_लिखोcount;
		bytecount -= ग_लिखोcount;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक broadsheet_store_waveक्रमm_to_spअगरlash(काष्ठा broadsheetfb_par *par,
						स्थिर u8 *wfm, माप_प्रकार wfm_size)
अणु
	पूर्णांक err = 0;
	u16 initial_sfmcd = 0;
	पूर्णांक flash_type = 0;

	err = broadsheet_setup_क्रम_wfm_ग_लिखो(par, &initial_sfmcd, &flash_type);
	अगर (err)
		जाओ failout;

	err = broadsheet_ग_लिखो_spअगरlash(par, 0x886, wfm, wfm_size, flash_type);

failout:
	broadsheet_ग_लिखो_reg(par, 0x0204, initial_sfmcd);
	वापस err;
पूर्ण

अटल sमाप_प्रकार broadsheet_loadstore_waveक्रमm(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक err;
	काष्ठा fb_info *info = dev_get_drvdata(dev);
	काष्ठा broadsheetfb_par *par = info->par;
	स्थिर काष्ठा firmware *fw_entry;

	अगर (len < 1)
		वापस -EINVAL;

	err = request_firmware(&fw_entry, "broadsheet.wbf", dev);
	अगर (err < 0) अणु
		dev_err(dev, "Failed to get broadsheet waveform\n");
		जाओ err_failed;
	पूर्ण

	/* try to enक्रमce reasonable min max on waveक्रमm */
	अगर ((fw_entry->size < 8*1024) || (fw_entry->size > 64*1024)) अणु
		dev_err(dev, "Invalid waveform\n");
		err = -EINVAL;
		जाओ err_fw;
	पूर्ण

	mutex_lock(&(par->io_lock));
	err = broadsheet_store_waveक्रमm_to_spअगरlash(par, fw_entry->data,
							fw_entry->size);

	mutex_unlock(&(par->io_lock));
	अगर (err < 0) अणु
		dev_err(dev, "Failed to store broadsheet waveform\n");
		जाओ err_fw;
	पूर्ण

	dev_info(dev, "Stored broadsheet waveform, size %zd\n", fw_entry->size);

	err = len;

err_fw:
	release_firmware(fw_entry);
err_failed:
	वापस err;
पूर्ण
अटल DEVICE_ATTR(loadstore_waveक्रमm, S_IWUSR, शून्य,
			broadsheet_loadstore_waveक्रमm);

/* upper level functions that manipulate the display and other stuff */
अटल व्योम broadsheet_init_display(काष्ठा broadsheetfb_par *par)
अणु
	u16 args[5];
	पूर्णांक xres = par->info->var.xres;
	पूर्णांक yres = par->info->var.yres;

	args[0] = panel_table[par->panel_index].w;
	args[1] = panel_table[par->panel_index].h;
	args[2] = panel_table[par->panel_index].sdcfg;
	args[3] = panel_table[par->panel_index].gdcfg;
	args[4] = panel_table[par->panel_index].lutfmt;
	broadsheet_send_cmdargs(par, BS_CMD_INIT_DSPE_CFG, 5, args);

	/* did the controller really set it? */
	broadsheet_send_cmdargs(par, BS_CMD_INIT_DSPE_CFG, 5, args);

	args[0] = panel_table[par->panel_index].fsynclen;
	args[1] = panel_table[par->panel_index].fendfbegin;
	args[2] = panel_table[par->panel_index].lsynclen;
	args[3] = panel_table[par->panel_index].lendlbegin;
	args[4] = panel_table[par->panel_index].pixclk;
	broadsheet_send_cmdargs(par, BS_CMD_INIT_DSPE_TMG, 5, args);

	broadsheet_ग_लिखो_reg32(par, 0x310, xres*yres*2);

	/* setup waveक्रमm */
	args[0] = 0x886;
	args[1] = 0;
	broadsheet_send_cmdargs(par, BS_CMD_RD_WFM_INFO, 2, args);

	broadsheet_send_command(par, BS_CMD_UPD_GDRV_CLR);

	broadsheet_send_command(par, BS_CMD_WAIT_DSPE_TRG);

	broadsheet_ग_लिखो_reg(par, 0x330, 0x84);

	broadsheet_send_command(par, BS_CMD_WAIT_DSPE_TRG);

	args[0] = (0x3 << 4);
	broadsheet_send_cmdargs(par, BS_CMD_LD_IMG, 1, args);

	args[0] = 0x154;
	broadsheet_send_cmdargs(par, BS_CMD_WR_REG, 1, args);

	broadsheet_burst_ग_लिखो(par, (panel_table[par->panel_index].w *
					panel_table[par->panel_index].h)/2,
					(u16 *) par->info->screen_base);

	broadsheet_send_command(par, BS_CMD_LD_IMG_END);

	args[0] = 0x4300;
	broadsheet_send_cmdargs(par, BS_CMD_UPD_FULL, 1, args);

	broadsheet_send_command(par, BS_CMD_WAIT_DSPE_TRG);

	broadsheet_send_command(par, BS_CMD_WAIT_DSPE_FREND);

	par->board->रुको_क्रम_rdy(par);
पूर्ण

अटल व्योम broadsheet_identअगरy(काष्ठा broadsheetfb_par *par)
अणु
	u16 rev, prc;
	काष्ठा device *dev = par->info->device;

	rev = broadsheet_पढ़ो_reg(par, BS_REG_REV);
	prc = broadsheet_पढ़ो_reg(par, BS_REG_PRC);
	dev_info(dev, "Broadsheet Rev 0x%x, Product Code 0x%x\n", rev, prc);

	अगर (prc != 0x0047)
		dev_warn(dev, "Unrecognized Broadsheet Product Code\n");
	अगर (rev != 0x0100)
		dev_warn(dev, "Unrecognized Broadsheet Revision\n");
पूर्ण

अटल व्योम broadsheet_init(काष्ठा broadsheetfb_par *par)
अणु
	broadsheet_send_command(par, BS_CMD_INIT_SYS_RUN);
	/* the controller needs a second */
	msleep(1000);
	broadsheet_init_display(par);
पूर्ण

अटल व्योम broadsheetfb_dpy_update_pages(काष्ठा broadsheetfb_par *par,
						u16 y1, u16 y2)
अणु
	u16 args[5];
	अचिन्हित अक्षर *buf = (अचिन्हित अक्षर *)par->info->screen_base;

	mutex_lock(&(par->io_lock));
	/* y1 must be a multiple of 4 so drop the lower bits */
	y1 &= 0xFFFC;
	/* y2 must be a multiple of 4 , but - 1 so up the lower bits */
	y2 |= 0x0003;

	args[0] = 0x3 << 4;
	args[1] = 0;
	args[2] = y1;
	args[3] = cpu_to_le16(par->info->var.xres);
	args[4] = y2;
	broadsheet_send_cmdargs(par, BS_CMD_LD_IMG_AREA, 5, args);

	args[0] = 0x154;
	broadsheet_send_cmdargs(par, BS_CMD_WR_REG, 1, args);

	buf += y1 * par->info->var.xres;
	broadsheet_burst_ग_लिखो(par, ((1 + y2 - y1) * par->info->var.xres)/2,
				(u16 *) buf);

	broadsheet_send_command(par, BS_CMD_LD_IMG_END);

	args[0] = 0x4300;
	broadsheet_send_cmdargs(par, BS_CMD_UPD_FULL, 1, args);

	broadsheet_send_command(par, BS_CMD_WAIT_DSPE_TRG);

	broadsheet_send_command(par, BS_CMD_WAIT_DSPE_FREND);

	par->board->रुको_क्रम_rdy(par);
	mutex_unlock(&(par->io_lock));

पूर्ण

अटल व्योम broadsheetfb_dpy_update(काष्ठा broadsheetfb_par *par)
अणु
	u16 args[5];

	mutex_lock(&(par->io_lock));
	args[0] = 0x3 << 4;
	broadsheet_send_cmdargs(par, BS_CMD_LD_IMG, 1, args);

	args[0] = 0x154;
	broadsheet_send_cmdargs(par, BS_CMD_WR_REG, 1, args);
	broadsheet_burst_ग_लिखो(par, (panel_table[par->panel_index].w *
					panel_table[par->panel_index].h)/2,
					(u16 *) par->info->screen_base);

	broadsheet_send_command(par, BS_CMD_LD_IMG_END);

	args[0] = 0x4300;
	broadsheet_send_cmdargs(par, BS_CMD_UPD_FULL, 1, args);

	broadsheet_send_command(par, BS_CMD_WAIT_DSPE_TRG);

	broadsheet_send_command(par, BS_CMD_WAIT_DSPE_FREND);

	par->board->रुको_क्रम_rdy(par);
	mutex_unlock(&(par->io_lock));
पूर्ण

/* this is called back from the deferred io workqueue */
अटल व्योम broadsheetfb_dpy_deferred_io(काष्ठा fb_info *info,
				काष्ठा list_head *pagelist)
अणु
	u16 y1 = 0, h = 0;
	पूर्णांक prev_index = -1;
	काष्ठा page *cur;
	काष्ठा fb_deferred_io *fbdefio = info->fbdefio;
	पूर्णांक h_inc;
	u16 yres = info->var.yres;
	u16 xres = info->var.xres;

	/* height increment is fixed per page */
	h_inc = DIV_ROUND_UP(PAGE_SIZE , xres);

	/* walk the written page list and swizzle the data */
	list_क्रम_each_entry(cur, &fbdefio->pagelist, lru) अणु
		अगर (prev_index < 0) अणु
			/* just starting so assign first page */
			y1 = (cur->index << PAGE_SHIFT) / xres;
			h = h_inc;
		पूर्ण अन्यथा अगर ((prev_index + 1) == cur->index) अणु
			/* this page is consecutive so increase our height */
			h += h_inc;
		पूर्ण अन्यथा अणु
			/* page not consecutive, issue previous update first */
			broadsheetfb_dpy_update_pages(info->par, y1, y1 + h);
			/* start over with our non consecutive page */
			y1 = (cur->index << PAGE_SHIFT) / xres;
			h = h_inc;
		पूर्ण
		prev_index = cur->index;
	पूर्ण

	/* अगर we still have any pages to update we करो so now */
	अगर (h >= yres) अणु
		/* its a full screen update, just करो it */
		broadsheetfb_dpy_update(info->par);
	पूर्ण अन्यथा अणु
		broadsheetfb_dpy_update_pages(info->par, y1,
						min((u16) (y1 + h), yres));
	पूर्ण
पूर्ण

अटल व्योम broadsheetfb_fillrect(काष्ठा fb_info *info,
				   स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा broadsheetfb_par *par = info->par;

	sys_fillrect(info, rect);

	broadsheetfb_dpy_update(par);
पूर्ण

अटल व्योम broadsheetfb_copyarea(काष्ठा fb_info *info,
				   स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा broadsheetfb_par *par = info->par;

	sys_copyarea(info, area);

	broadsheetfb_dpy_update(par);
पूर्ण

अटल व्योम broadsheetfb_imageblit(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा broadsheetfb_par *par = info->par;

	sys_imageblit(info, image);

	broadsheetfb_dpy_update(par);
पूर्ण

/*
 * this is the slow path from userspace. they can seek and ग_लिखो to
 * the fb. it's inefficient to करो anything less than a full screen draw
 */
अटल sमाप_प्रकार broadsheetfb_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा broadsheetfb_par *par = info->par;
	अचिन्हित दीर्घ p = *ppos;
	व्योम *dst;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ total_size;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस -EPERM;

	total_size = info->fix.smem_len;

	अगर (p > total_size)
		वापस -EFBIG;

	अगर (count > total_size) अणु
		err = -EFBIG;
		count = total_size;
	पूर्ण

	अगर (count + p > total_size) अणु
		अगर (!err)
			err = -ENOSPC;

		count = total_size - p;
	पूर्ण

	dst = (व्योम *)(info->screen_base + p);

	अगर (copy_from_user(dst, buf, count))
		err = -EFAULT;

	अगर  (!err)
		*ppos += count;

	broadsheetfb_dpy_update(par);

	वापस (err) ? err : count;
पूर्ण

अटल स्थिर काष्ठा fb_ops broadsheetfb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_पढ़ो        = fb_sys_पढ़ो,
	.fb_ग_लिखो	= broadsheetfb_ग_लिखो,
	.fb_fillrect	= broadsheetfb_fillrect,
	.fb_copyarea	= broadsheetfb_copyarea,
	.fb_imageblit	= broadsheetfb_imageblit,
पूर्ण;

अटल काष्ठा fb_deferred_io broadsheetfb_defio = अणु
	.delay		= HZ/4,
	.deferred_io	= broadsheetfb_dpy_deferred_io,
पूर्ण;

अटल पूर्णांक broadsheetfb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;
	काष्ठा broadsheet_board *board;
	पूर्णांक retval = -ENOMEM;
	पूर्णांक videomemorysize;
	अचिन्हित अक्षर *videomemory;
	काष्ठा broadsheetfb_par *par;
	पूर्णांक i;
	पूर्णांक dpyw, dpyh;
	पूर्णांक panel_index;

	/* pick up board specअगरic routines */
	board = dev->dev.platक्रमm_data;
	अगर (!board)
		वापस -EINVAL;

	/* try to count device specअगरic driver, अगर can't, platक्रमm recalls */
	अगर (!try_module_get(board->owner))
		वापस -ENODEV;

	info = framebuffer_alloc(माप(काष्ठा broadsheetfb_par), &dev->dev);
	अगर (!info)
		जाओ err;

	चयन (board->get_panel_type()) अणु
	हाल 37:
		panel_index = 1;
		अवरोध;
	हाल 97:
		panel_index = 2;
		अवरोध;
	हाल 6:
	शेष:
		panel_index = 0;
		अवरोध;
	पूर्ण

	dpyw = panel_table[panel_index].w;
	dpyh = panel_table[panel_index].h;

	videomemorysize = roundup((dpyw*dpyh), PAGE_SIZE);

	videomemory = vzalloc(videomemorysize);
	अगर (!videomemory)
		जाओ err_fb_rel;

	info->screen_base = (अक्षर *)videomemory;
	info->fbops = &broadsheetfb_ops;

	broadsheetfb_var.xres = dpyw;
	broadsheetfb_var.yres = dpyh;
	broadsheetfb_var.xres_भव = dpyw;
	broadsheetfb_var.yres_भव = dpyh;
	info->var = broadsheetfb_var;

	broadsheetfb_fix.line_length = dpyw;
	info->fix = broadsheetfb_fix;
	info->fix.smem_len = videomemorysize;
	par = info->par;
	par->panel_index = panel_index;
	par->info = info;
	par->board = board;
	par->ग_लिखो_reg = broadsheet_ग_लिखो_reg;
	par->पढ़ो_reg = broadsheet_पढ़ो_reg;
	init_रुकोqueue_head(&par->रुकोq);

	mutex_init(&par->io_lock);

	info->flags = FBINFO_FLAG_DEFAULT | FBINFO_VIRTFB;

	info->fbdefio = &broadsheetfb_defio;
	fb_deferred_io_init(info);

	retval = fb_alloc_cmap(&info->cmap, 16, 0);
	अगर (retval < 0) अणु
		dev_err(&dev->dev, "Failed to allocate colormap\n");
		जाओ err_vमुक्त;
	पूर्ण

	/* set cmap */
	क्रम (i = 0; i < 16; i++)
		info->cmap.red[i] = (((2*i)+1)*(0xFFFF))/32;
	स_नकल(info->cmap.green, info->cmap.red, माप(u16)*16);
	स_नकल(info->cmap.blue, info->cmap.red, माप(u16)*16);

	retval = par->board->setup_irq(info);
	अगर (retval < 0)
		जाओ err_cmap;

	/* this inits the dpy */
	retval = board->init(par);
	अगर (retval < 0)
		जाओ err_मुक्त_irq;

	broadsheet_identअगरy(par);

	broadsheet_init(par);

	retval = रेजिस्टर_framebuffer(info);
	अगर (retval < 0)
		जाओ err_मुक्त_irq;

	platक्रमm_set_drvdata(dev, info);

	retval = device_create_file(&dev->dev, &dev_attr_loadstore_waveक्रमm);
	अगर (retval < 0)
		जाओ err_unreg_fb;

	fb_info(info, "Broadsheet frame buffer, using %dK of video memory\n",
		videomemorysize >> 10);


	वापस 0;

err_unreg_fb:
	unरेजिस्टर_framebuffer(info);
err_मुक्त_irq:
	board->cleanup(par);
err_cmap:
	fb_dealloc_cmap(&info->cmap);
err_vमुक्त:
	vमुक्त(videomemory);
err_fb_rel:
	framebuffer_release(info);
err:
	module_put(board->owner);
	वापस retval;

पूर्ण

अटल पूर्णांक broadsheetfb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(dev);

	अगर (info) अणु
		काष्ठा broadsheetfb_par *par = info->par;

		device_हटाओ_file(info->dev, &dev_attr_loadstore_waveक्रमm);
		unरेजिस्टर_framebuffer(info);
		fb_deferred_io_cleanup(info);
		par->board->cleanup(par);
		fb_dealloc_cmap(&info->cmap);
		vमुक्त((व्योम *)info->screen_base);
		module_put(par->board->owner);
		framebuffer_release(info);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver broadsheetfb_driver = अणु
	.probe	= broadsheetfb_probe,
	.हटाओ = broadsheetfb_हटाओ,
	.driver	= अणु
		.name	= "broadsheetfb",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(broadsheetfb_driver);

MODULE_DESCRIPTION("fbdev driver for Broadsheet controller");
MODULE_AUTHOR("Jaya Kumar");
MODULE_LICENSE("GPL");
