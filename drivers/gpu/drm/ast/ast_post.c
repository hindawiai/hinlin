<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors: Dave Airlie <airlied@redhat.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "ast_dram_tables.h"
#समावेश "ast_drv.h"

अटल व्योम ast_post_chip_2300(काष्ठा drm_device *dev);
अटल व्योम ast_post_chip_2500(काष्ठा drm_device *dev);

व्योम ast_enable_vga(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);

	ast_io_ग_लिखो8(ast, AST_IO_VGA_ENABLE_PORT, 0x01);
	ast_io_ग_लिखो8(ast, AST_IO_MISC_PORT_WRITE, 0x01);
पूर्ण

व्योम ast_enable_mmio(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);

	ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0xa1, 0x06);
पूर्ण


bool ast_is_vga_enabled(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	u8 ch;

	ch = ast_io_पढ़ो8(ast, AST_IO_VGA_ENABLE_PORT);

	वापस !!(ch & 0x01);
पूर्ण

अटल स्थिर u8 extreginfo[] = अणु 0x0f, 0x04, 0x1c, 0xff पूर्ण;
अटल स्थिर u8 extreginfo_ast2300a0[] = अणु 0x0f, 0x04, 0x1c, 0xff पूर्ण;
अटल स्थिर u8 extreginfo_ast2300[] = अणु 0x0f, 0x04, 0x1f, 0xff पूर्ण;

अटल व्योम
ast_set_def_ext_reg(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	u8 i, index, reg;
	स्थिर u8 *ext_reg_info;

	/* reset scratch */
	क्रम (i = 0x81; i <= 0x9f; i++)
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, i, 0x00);

	अगर (ast->chip == AST2300 || ast->chip == AST2400 ||
	    ast->chip == AST2500) अणु
		अगर (pdev->revision >= 0x20)
			ext_reg_info = extreginfo_ast2300;
		अन्यथा
			ext_reg_info = extreginfo_ast2300a0;
	पूर्ण अन्यथा
		ext_reg_info = extreginfo;

	index = 0xa0;
	जबतक (*ext_reg_info != 0xff) अणु
		ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, index, 0x00, *ext_reg_info);
		index++;
		ext_reg_info++;
	पूर्ण

	/* disable standard IO/MEM decode अगर secondary */
	/* ast_set_index_reg-mask(ast, AST_IO_CRTC_PORT, 0xa1, 0xff, 0x3); */

	/* Set Ext. Default */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x8c, 0x00, 0x01);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb7, 0x00, 0x00);

	/* Enable RAMDAC क्रम A1 */
	reg = 0x04;
	अगर (ast->chip == AST2300 || ast->chip == AST2400 ||
	    ast->chip == AST2500)
		reg |= 0x20;
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xb6, 0xff, reg);
पूर्ण

u32 ast_mindwm(काष्ठा ast_निजी *ast, u32 r)
अणु
	uपूर्णांक32_t data;

	ast_ग_लिखो32(ast, 0xf004, r & 0xffff0000);
	ast_ग_लिखो32(ast, 0xf000, 0x1);

	करो अणु
		data = ast_पढ़ो32(ast, 0xf004) & 0xffff0000;
	पूर्ण जबतक (data != (r & 0xffff0000));
	वापस ast_पढ़ो32(ast, 0x10000 + (r & 0x0000ffff));
पूर्ण

व्योम ast_moutdwm(काष्ठा ast_निजी *ast, u32 r, u32 v)
अणु
	uपूर्णांक32_t data;
	ast_ग_लिखो32(ast, 0xf004, r & 0xffff0000);
	ast_ग_लिखो32(ast, 0xf000, 0x1);
	करो अणु
		data = ast_पढ़ो32(ast, 0xf004) & 0xffff0000;
	पूर्ण जबतक (data != (r & 0xffff0000));
	ast_ग_लिखो32(ast, 0x10000 + (r & 0x0000ffff), v);
पूर्ण

/*
 * AST2100/2150 DLL CBR Setting
 */
#घोषणा CBR_SIZE_AST2150	     ((16 << 10) - 1)
#घोषणा CBR_PASSNUM_AST2150          5
#घोषणा CBR_THRESHOLD_AST2150        10
#घोषणा CBR_THRESHOLD2_AST2150       10
#घोषणा TIMEOUT_AST2150              5000000

#घोषणा CBR_PATNUM_AST2150           8

अटल स्थिर u32 pattern_AST2150[14] = अणु
	0xFF00FF00,
	0xCC33CC33,
	0xAA55AA55,
	0xFFFE0001,
	0x683501FE,
	0x0F1929B0,
	0x2D0B4346,
	0x60767F02,
	0x6FBE36A6,
	0x3A253035,
	0x3019686D,
	0x41C6167E,
	0x620152BF,
	0x20F050E0
पूर्ण;

अटल u32 mmctestburst2_ast2150(काष्ठा ast_निजी *ast, u32 datagen)
अणु
	u32 data, समयout;

	ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
	ast_moutdwm(ast, 0x1e6e0070, 0x00000001 | (datagen << 3));
	समयout = 0;
	करो अणु
		data = ast_mindwm(ast, 0x1e6e0070) & 0x40;
		अगर (++समयout > TIMEOUT_AST2150) अणु
			ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
			वापस 0xffffffff;
		पूर्ण
	पूर्ण जबतक (!data);
	ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
	ast_moutdwm(ast, 0x1e6e0070, 0x00000003 | (datagen << 3));
	समयout = 0;
	करो अणु
		data = ast_mindwm(ast, 0x1e6e0070) & 0x40;
		अगर (++समयout > TIMEOUT_AST2150) अणु
			ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
			वापस 0xffffffff;
		पूर्ण
	पूर्ण जबतक (!data);
	data = (ast_mindwm(ast, 0x1e6e0070) & 0x80) >> 7;
	ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
	वापस data;
पूर्ण

#अगर 0 /* unused in DDX driver - here क्रम completeness */
अटल u32 mmctestsingle2_ast2150(काष्ठा ast_निजी *ast, u32 datagen)
अणु
	u32 data, समयout;

	ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
	ast_moutdwm(ast, 0x1e6e0070, 0x00000005 | (datagen << 3));
	समयout = 0;
	करो अणु
		data = ast_mindwm(ast, 0x1e6e0070) & 0x40;
		अगर (++समयout > TIMEOUT_AST2150) अणु
			ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
			वापस 0xffffffff;
		पूर्ण
	पूर्ण जबतक (!data);
	data = (ast_mindwm(ast, 0x1e6e0070) & 0x80) >> 7;
	ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
	वापस data;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cbrtest_ast2150(काष्ठा ast_निजी *ast)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		अगर (mmctestburst2_ast2150(ast, i))
			वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक cbrscan_ast2150(काष्ठा ast_निजी *ast, पूर्णांक busw)
अणु
	u32 patcnt, loop;

	क्रम (patcnt = 0; patcnt < CBR_PATNUM_AST2150; patcnt++) अणु
		ast_moutdwm(ast, 0x1e6e007c, pattern_AST2150[patcnt]);
		क्रम (loop = 0; loop < CBR_PASSNUM_AST2150; loop++) अणु
			अगर (cbrtest_ast2150(ast))
				अवरोध;
		पूर्ण
		अगर (loop == CBR_PASSNUM_AST2150)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण


अटल व्योम cbrdlli_ast2150(काष्ठा ast_निजी *ast, पूर्णांक busw)
अणु
	u32 dll_min[4], dll_max[4], dlli, data, passcnt;

cbr_start:
	dll_min[0] = dll_min[1] = dll_min[2] = dll_min[3] = 0xff;
	dll_max[0] = dll_max[1] = dll_max[2] = dll_max[3] = 0x0;
	passcnt = 0;

	क्रम (dlli = 0; dlli < 100; dlli++) अणु
		ast_moutdwm(ast, 0x1e6e0068, dlli | (dlli << 8) | (dlli << 16) | (dlli << 24));
		data = cbrscan_ast2150(ast, busw);
		अगर (data != 0) अणु
			अगर (data & 0x1) अणु
				अगर (dll_min[0] > dlli)
					dll_min[0] = dlli;
				अगर (dll_max[0] < dlli)
					dll_max[0] = dlli;
			पूर्ण
			passcnt++;
		पूर्ण अन्यथा अगर (passcnt >= CBR_THRESHOLD_AST2150)
			जाओ cbr_start;
	पूर्ण
	अगर (dll_max[0] == 0 || (dll_max[0]-dll_min[0]) < CBR_THRESHOLD_AST2150)
		जाओ cbr_start;

	dlli = dll_min[0] + (((dll_max[0] - dll_min[0]) * 7) >> 4);
	ast_moutdwm(ast, 0x1e6e0068, dlli | (dlli << 8) | (dlli << 16) | (dlli << 24));
पूर्ण



अटल व्योम ast_init_dram_reg(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	u8 j;
	u32 data, temp, i;
	स्थिर काष्ठा ast_dramकाष्ठा *dram_reg_info;

	j = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd0, 0xff);

	अगर ((j & 0x80) == 0) अणु /* VGA only */
		अगर (ast->chip == AST2000) अणु
			dram_reg_info = ast2000_dram_table_data;
			ast_ग_लिखो32(ast, 0xf004, 0x1e6e0000);
			ast_ग_लिखो32(ast, 0xf000, 0x1);
			ast_ग_लिखो32(ast, 0x10100, 0xa8);

			करो अणु
				;
			पूर्ण जबतक (ast_पढ़ो32(ast, 0x10100) != 0xa8);
		पूर्ण अन्यथा अणु/* AST2100/1100 */
			अगर (ast->chip == AST2100 || ast->chip == 2200)
				dram_reg_info = ast2100_dram_table_data;
			अन्यथा
				dram_reg_info = ast1100_dram_table_data;

			ast_ग_लिखो32(ast, 0xf004, 0x1e6e0000);
			ast_ग_लिखो32(ast, 0xf000, 0x1);
			ast_ग_लिखो32(ast, 0x12000, 0x1688A8A8);
			करो अणु
				;
			पूर्ण जबतक (ast_पढ़ो32(ast, 0x12000) != 0x01);

			ast_ग_लिखो32(ast, 0x10000, 0xfc600309);
			करो अणु
				;
			पूर्ण जबतक (ast_पढ़ो32(ast, 0x10000) != 0x01);
		पूर्ण

		जबतक (dram_reg_info->index != 0xffff) अणु
			अगर (dram_reg_info->index == 0xff00) अणु/* delay fn */
				क्रम (i = 0; i < 15; i++)
					udelay(dram_reg_info->data);
			पूर्ण अन्यथा अगर (dram_reg_info->index == 0x4 && ast->chip != AST2000) अणु
				data = dram_reg_info->data;
				अगर (ast->dram_type == AST_DRAM_1Gx16)
					data = 0x00000d89;
				अन्यथा अगर (ast->dram_type == AST_DRAM_1Gx32)
					data = 0x00000c8d;

				temp = ast_पढ़ो32(ast, 0x12070);
				temp &= 0xc;
				temp <<= 2;
				ast_ग_लिखो32(ast, 0x10000 + dram_reg_info->index, data | temp);
			पूर्ण अन्यथा
				ast_ग_लिखो32(ast, 0x10000 + dram_reg_info->index, dram_reg_info->data);
			dram_reg_info++;
		पूर्ण

		/* AST 2100/2150 DRAM calibration */
		data = ast_पढ़ो32(ast, 0x10120);
		अगर (data == 0x5061) अणु /* 266Mhz */
			data = ast_पढ़ो32(ast, 0x10004);
			अगर (data & 0x40)
				cbrdlli_ast2150(ast, 16); /* 16 bits */
			अन्यथा
				cbrdlli_ast2150(ast, 32); /* 32 bits */
		पूर्ण

		चयन (ast->chip) अणु
		हाल AST2000:
			temp = ast_पढ़ो32(ast, 0x10140);
			ast_ग_लिखो32(ast, 0x10140, temp | 0x40);
			अवरोध;
		हाल AST1100:
		हाल AST2100:
		हाल AST2200:
		हाल AST2150:
			temp = ast_पढ़ो32(ast, 0x1200c);
			ast_ग_लिखो32(ast, 0x1200c, temp & 0xfffffffd);
			temp = ast_पढ़ो32(ast, 0x12040);
			ast_ग_लिखो32(ast, 0x12040, temp | 0x40);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* रुको पढ़ोy */
	करो अणु
		j = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd0, 0xff);
	पूर्ण जबतक ((j & 0x40) == 0);
पूर्ण

व्योम ast_post_gpu(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	u32 reg;

	pci_पढ़ो_config_dword(pdev, 0x04, &reg);
	reg |= 0x3;
	pci_ग_लिखो_config_dword(pdev, 0x04, reg);

	ast_enable_vga(dev);
	ast_खोलो_key(ast);
	ast_enable_mmio(dev);
	ast_set_def_ext_reg(dev);

	अगर (ast->config_mode == ast_use_p2a) अणु
		अगर (ast->chip == AST2500)
			ast_post_chip_2500(dev);
		अन्यथा अगर (ast->chip == AST2300 || ast->chip == AST2400)
			ast_post_chip_2300(dev);
		अन्यथा
			ast_init_dram_reg(dev);

		ast_init_3rdtx(dev);
	पूर्ण अन्यथा अणु
		अगर (ast->tx_chip_type != AST_TX_NONE)
			ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa3, 0xcf, 0x80);	/* Enable DVO */
	पूर्ण
पूर्ण

/* AST 2300 DRAM settings */
#घोषणा AST_DDR3 0
#घोषणा AST_DDR2 1

काष्ठा ast2300_dram_param अणु
	u32 dram_type;
	u32 dram_chipid;
	u32 dram_freq;
	u32 vram_size;
	u32 odt;
	u32 wodt;
	u32 rodt;
	u32 dram_config;
	u32 reg_PERIOD;
	u32 reg_MADJ;
	u32 reg_SADJ;
	u32 reg_MRS;
	u32 reg_EMRS;
	u32 reg_AC1;
	u32 reg_AC2;
	u32 reg_DQSIC;
	u32 reg_DRV;
	u32 reg_IOZ;
	u32 reg_DQIDLY;
	u32 reg_FREQ;
	u32 madj_max;
	u32 dll2_finetune_step;
पूर्ण;

/*
 * DQSI DLL CBR Setting
 */
#घोषणा CBR_SIZE0            ((1  << 10) - 1)
#घोषणा CBR_SIZE1            ((4  << 10) - 1)
#घोषणा CBR_SIZE2            ((64 << 10) - 1)
#घोषणा CBR_PASSNUM          5
#घोषणा CBR_PASSNUM2         5
#घोषणा CBR_THRESHOLD        10
#घोषणा CBR_THRESHOLD2       10
#घोषणा TIMEOUT              5000000
#घोषणा CBR_PATNUM           8

अटल स्थिर u32 pattern[8] = अणु
	0xFF00FF00,
	0xCC33CC33,
	0xAA55AA55,
	0x88778877,
	0x92CC4D6E,
	0x543D3CDE,
	0xF1E843C7,
	0x7C61D253
पूर्ण;

अटल bool mmc_test(काष्ठा ast_निजी *ast, u32 datagen, u8 test_ctl)
अणु
	u32 data, समयout;

	ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
	ast_moutdwm(ast, 0x1e6e0070, (datagen << 3) | test_ctl);
	समयout = 0;
	करो अणु
		data = ast_mindwm(ast, 0x1e6e0070) & 0x3000;
		अगर (data & 0x2000)
			वापस false;
		अगर (++समयout > TIMEOUT) अणु
			ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
			वापस false;
		पूर्ण
	पूर्ण जबतक (!data);
	ast_moutdwm(ast, 0x1e6e0070, 0x0);
	वापस true;
पूर्ण

अटल u32 mmc_test2(काष्ठा ast_निजी *ast, u32 datagen, u8 test_ctl)
अणु
	u32 data, समयout;

	ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
	ast_moutdwm(ast, 0x1e6e0070, (datagen << 3) | test_ctl);
	समयout = 0;
	करो अणु
		data = ast_mindwm(ast, 0x1e6e0070) & 0x1000;
		अगर (++समयout > TIMEOUT) अणु
			ast_moutdwm(ast, 0x1e6e0070, 0x0);
			वापस 0xffffffff;
		पूर्ण
	पूर्ण जबतक (!data);
	data = ast_mindwm(ast, 0x1e6e0078);
	data = (data | (data >> 16)) & 0xffff;
	ast_moutdwm(ast, 0x1e6e0070, 0x00000000);
	वापस data;
पूर्ण


अटल bool mmc_test_burst(काष्ठा ast_निजी *ast, u32 datagen)
अणु
	वापस mmc_test(ast, datagen, 0xc1);
पूर्ण

अटल u32 mmc_test_burst2(काष्ठा ast_निजी *ast, u32 datagen)
अणु
	वापस mmc_test2(ast, datagen, 0x41);
पूर्ण

अटल bool mmc_test_single(काष्ठा ast_निजी *ast, u32 datagen)
अणु
	वापस mmc_test(ast, datagen, 0xc5);
पूर्ण

अटल u32 mmc_test_single2(काष्ठा ast_निजी *ast, u32 datagen)
अणु
	वापस mmc_test2(ast, datagen, 0x05);
पूर्ण

अटल bool mmc_test_single_2500(काष्ठा ast_निजी *ast, u32 datagen)
अणु
	वापस mmc_test(ast, datagen, 0x85);
पूर्ण

अटल पूर्णांक cbr_test(काष्ठा ast_निजी *ast)
अणु
	u32 data;
	पूर्णांक i;
	data = mmc_test_single2(ast, 0);
	अगर ((data & 0xff) && (data & 0xff00))
		वापस 0;
	क्रम (i = 0; i < 8; i++) अणु
		data = mmc_test_burst2(ast, i);
		अगर ((data & 0xff) && (data & 0xff00))
			वापस 0;
	पूर्ण
	अगर (!data)
		वापस 3;
	अन्यथा अगर (data & 0xff)
		वापस 2;
	वापस 1;
पूर्ण

अटल पूर्णांक cbr_scan(काष्ठा ast_निजी *ast)
अणु
	u32 data, data2, patcnt, loop;

	data2 = 3;
	क्रम (patcnt = 0; patcnt < CBR_PATNUM; patcnt++) अणु
		ast_moutdwm(ast, 0x1e6e007c, pattern[patcnt]);
		क्रम (loop = 0; loop < CBR_PASSNUM2; loop++) अणु
			अगर ((data = cbr_test(ast)) != 0) अणु
				data2 &= data;
				अगर (!data2)
					वापस 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (loop == CBR_PASSNUM2)
			वापस 0;
	पूर्ण
	वापस data2;
पूर्ण

अटल u32 cbr_test2(काष्ठा ast_निजी *ast)
अणु
	u32 data;

	data = mmc_test_burst2(ast, 0);
	अगर (data == 0xffff)
		वापस 0;
	data |= mmc_test_single2(ast, 0);
	अगर (data == 0xffff)
		वापस 0;

	वापस ~data & 0xffff;
पूर्ण

अटल u32 cbr_scan2(काष्ठा ast_निजी *ast)
अणु
	u32 data, data2, patcnt, loop;

	data2 = 0xffff;
	क्रम (patcnt = 0; patcnt < CBR_PATNUM; patcnt++) अणु
		ast_moutdwm(ast, 0x1e6e007c, pattern[patcnt]);
		क्रम (loop = 0; loop < CBR_PASSNUM2; loop++) अणु
			अगर ((data = cbr_test2(ast)) != 0) अणु
				data2 &= data;
				अगर (!data2)
					वापस 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (loop == CBR_PASSNUM2)
			वापस 0;
	पूर्ण
	वापस data2;
पूर्ण

अटल bool cbr_test3(काष्ठा ast_निजी *ast)
अणु
	अगर (!mmc_test_burst(ast, 0))
		वापस false;
	अगर (!mmc_test_single(ast, 0))
		वापस false;
	वापस true;
पूर्ण

अटल bool cbr_scan3(काष्ठा ast_निजी *ast)
अणु
	u32 patcnt, loop;

	क्रम (patcnt = 0; patcnt < CBR_PATNUM; patcnt++) अणु
		ast_moutdwm(ast, 0x1e6e007c, pattern[patcnt]);
		क्रम (loop = 0; loop < 2; loop++) अणु
			अगर (cbr_test3(ast))
				अवरोध;
		पूर्ण
		अगर (loop == 2)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool finetuneDQI_L(काष्ठा ast_निजी *ast, काष्ठा ast2300_dram_param *param)
अणु
	u32 gold_sadj[2], dllmin[16], dllmax[16], dlli, data, cnt, mask, passcnt, retry = 0;
	bool status = false;
FINETUNE_START:
	क्रम (cnt = 0; cnt < 16; cnt++) अणु
		dllmin[cnt] = 0xff;
		dllmax[cnt] = 0x0;
	पूर्ण
	passcnt = 0;
	क्रम (dlli = 0; dlli < 76; dlli++) अणु
		ast_moutdwm(ast, 0x1E6E0068, 0x00001400 | (dlli << 16) | (dlli << 24));
		ast_moutdwm(ast, 0x1E6E0074, CBR_SIZE1);
		data = cbr_scan2(ast);
		अगर (data != 0) अणु
			mask = 0x00010001;
			क्रम (cnt = 0; cnt < 16; cnt++) अणु
				अगर (data & mask) अणु
					अगर (dllmin[cnt] > dlli) अणु
						dllmin[cnt] = dlli;
					पूर्ण
					अगर (dllmax[cnt] < dlli) अणु
						dllmax[cnt] = dlli;
					पूर्ण
				पूर्ण
				mask <<= 1;
			पूर्ण
			passcnt++;
		पूर्ण अन्यथा अगर (passcnt >= CBR_THRESHOLD2) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	gold_sadj[0] = 0x0;
	passcnt = 0;
	क्रम (cnt = 0; cnt < 16; cnt++) अणु
		अगर ((dllmax[cnt] > dllmin[cnt]) && ((dllmax[cnt] - dllmin[cnt]) >= CBR_THRESHOLD2)) अणु
			gold_sadj[0] += dllmin[cnt];
			passcnt++;
		पूर्ण
	पूर्ण
	अगर (retry++ > 10)
		जाओ FINETUNE_DONE;
	अगर (passcnt != 16) अणु
		जाओ FINETUNE_START;
	पूर्ण
	status = true;
FINETUNE_DONE:
	gold_sadj[0] = gold_sadj[0] >> 4;
	gold_sadj[1] = gold_sadj[0];

	data = 0;
	क्रम (cnt = 0; cnt < 8; cnt++) अणु
		data >>= 3;
		अगर ((dllmax[cnt] > dllmin[cnt]) && ((dllmax[cnt] - dllmin[cnt]) >= CBR_THRESHOLD2)) अणु
			dlli = dllmin[cnt];
			अगर (gold_sadj[0] >= dlli) अणु
				dlli = ((gold_sadj[0] - dlli) * 19) >> 5;
				अगर (dlli > 3) अणु
					dlli = 3;
				पूर्ण
			पूर्ण अन्यथा अणु
				dlli = ((dlli - gold_sadj[0]) * 19) >> 5;
				अगर (dlli > 4) अणु
					dlli = 4;
				पूर्ण
				dlli = (8 - dlli) & 0x7;
			पूर्ण
			data |= dlli << 21;
		पूर्ण
	पूर्ण
	ast_moutdwm(ast, 0x1E6E0080, data);

	data = 0;
	क्रम (cnt = 8; cnt < 16; cnt++) अणु
		data >>= 3;
		अगर ((dllmax[cnt] > dllmin[cnt]) && ((dllmax[cnt] - dllmin[cnt]) >= CBR_THRESHOLD2)) अणु
			dlli = dllmin[cnt];
			अगर (gold_sadj[1] >= dlli) अणु
				dlli = ((gold_sadj[1] - dlli) * 19) >> 5;
				अगर (dlli > 3) अणु
					dlli = 3;
				पूर्ण अन्यथा अणु
					dlli = (dlli - 1) & 0x7;
				पूर्ण
			पूर्ण अन्यथा अणु
				dlli = ((dlli - gold_sadj[1]) * 19) >> 5;
				dlli += 1;
				अगर (dlli > 4) अणु
					dlli = 4;
				पूर्ण
				dlli = (8 - dlli) & 0x7;
			पूर्ण
			data |= dlli << 21;
		पूर्ण
	पूर्ण
	ast_moutdwm(ast, 0x1E6E0084, data);
	वापस status;
पूर्ण /* finetuneDQI_L */

अटल व्योम finetuneDQSI(काष्ठा ast_निजी *ast)
अणु
	u32 dlli, dqsip, dqidly;
	u32 reg_mcr18, reg_mcr0c, passcnt[2], dअगरf;
	u32 g_dqidly, g_dqsip, g_margin, g_side;
	u16 pass[32][2][2];
	अक्षर tag[2][76];

	/* Disable DQI CBR */
	reg_mcr0c  = ast_mindwm(ast, 0x1E6E000C);
	reg_mcr18  = ast_mindwm(ast, 0x1E6E0018);
	reg_mcr18 &= 0x0000ffff;
	ast_moutdwm(ast, 0x1E6E0018, reg_mcr18);

	क्रम (dlli = 0; dlli < 76; dlli++) अणु
		tag[0][dlli] = 0x0;
		tag[1][dlli] = 0x0;
	पूर्ण
	क्रम (dqidly = 0; dqidly < 32; dqidly++) अणु
		pass[dqidly][0][0] = 0xff;
		pass[dqidly][0][1] = 0x0;
		pass[dqidly][1][0] = 0xff;
		pass[dqidly][1][1] = 0x0;
	पूर्ण
	क्रम (dqidly = 0; dqidly < 32; dqidly++) अणु
		passcnt[0] = passcnt[1] = 0;
		क्रम (dqsip = 0; dqsip < 2; dqsip++) अणु
			ast_moutdwm(ast, 0x1E6E000C, 0);
			ast_moutdwm(ast, 0x1E6E0018, reg_mcr18 | (dqidly << 16) | (dqsip << 23));
			ast_moutdwm(ast, 0x1E6E000C, reg_mcr0c);
			क्रम (dlli = 0; dlli < 76; dlli++) अणु
				ast_moutdwm(ast, 0x1E6E0068, 0x00001300 | (dlli << 16) | (dlli << 24));
				ast_moutdwm(ast, 0x1E6E0070, 0);
				ast_moutdwm(ast, 0x1E6E0074, CBR_SIZE0);
				अगर (cbr_scan3(ast)) अणु
					अगर (dlli == 0)
						अवरोध;
					passcnt[dqsip]++;
					tag[dqsip][dlli] = 'P';
					अगर (dlli < pass[dqidly][dqsip][0])
						pass[dqidly][dqsip][0] = (u16) dlli;
					अगर (dlli > pass[dqidly][dqsip][1])
						pass[dqidly][dqsip][1] = (u16) dlli;
				पूर्ण अन्यथा अगर (passcnt[dqsip] >= 5)
					अवरोध;
				अन्यथा अणु
					pass[dqidly][dqsip][0] = 0xff;
					pass[dqidly][dqsip][1] = 0x0;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (passcnt[0] == 0 && passcnt[1] == 0)
			dqidly++;
	पूर्ण
	/* Search margin */
	g_dqidly = g_dqsip = g_margin = g_side = 0;

	क्रम (dqidly = 0; dqidly < 32; dqidly++) अणु
		क्रम (dqsip = 0; dqsip < 2; dqsip++) अणु
			अगर (pass[dqidly][dqsip][0] > pass[dqidly][dqsip][1])
				जारी;
			dअगरf = pass[dqidly][dqsip][1] - pass[dqidly][dqsip][0];
			अगर ((dअगरf+2) < g_margin)
				जारी;
			passcnt[0] = passcnt[1] = 0;
			क्रम (dlli = pass[dqidly][dqsip][0]; dlli > 0  && tag[dqsip][dlli] != 0; dlli--, passcnt[0]++);
			क्रम (dlli = pass[dqidly][dqsip][1]; dlli < 76 && tag[dqsip][dlli] != 0; dlli++, passcnt[1]++);
			अगर (passcnt[0] > passcnt[1])
				passcnt[0] = passcnt[1];
			passcnt[1] = 0;
			अगर (passcnt[0] > g_side)
				passcnt[1] = passcnt[0] - g_side;
			अगर (dअगरf > (g_margin+1) && (passcnt[1] > 0 || passcnt[0] > 8)) अणु
				g_margin = dअगरf;
				g_dqidly = dqidly;
				g_dqsip  = dqsip;
				g_side   = passcnt[0];
			पूर्ण अन्यथा अगर (passcnt[1] > 1 && g_side < 8) अणु
				अगर (dअगरf > g_margin)
					g_margin = dअगरf;
				g_dqidly = dqidly;
				g_dqsip  = dqsip;
				g_side   = passcnt[0];
			पूर्ण
		पूर्ण
	पूर्ण
	reg_mcr18 = reg_mcr18 | (g_dqidly << 16) | (g_dqsip << 23);
	ast_moutdwm(ast, 0x1E6E0018, reg_mcr18);

पूर्ण
अटल bool cbr_dll2(काष्ठा ast_निजी *ast, काष्ठा ast2300_dram_param *param)
अणु
	u32 dllmin[2], dllmax[2], dlli, data, passcnt, retry = 0;
	bool status = false;

	finetuneDQSI(ast);
	अगर (finetuneDQI_L(ast, param) == false)
		वापस status;

CBR_START2:
	dllmin[0] = dllmin[1] = 0xff;
	dllmax[0] = dllmax[1] = 0x0;
	passcnt = 0;
	क्रम (dlli = 0; dlli < 76; dlli++) अणु
		ast_moutdwm(ast, 0x1E6E0068, 0x00001300 | (dlli << 16) | (dlli << 24));
		ast_moutdwm(ast, 0x1E6E0074, CBR_SIZE2);
		data = cbr_scan(ast);
		अगर (data != 0) अणु
			अगर (data & 0x1) अणु
				अगर (dllmin[0] > dlli) अणु
					dllmin[0] = dlli;
				पूर्ण
				अगर (dllmax[0] < dlli) अणु
					dllmax[0] = dlli;
				पूर्ण
			पूर्ण
			अगर (data & 0x2) अणु
				अगर (dllmin[1] > dlli) अणु
					dllmin[1] = dlli;
				पूर्ण
				अगर (dllmax[1] < dlli) अणु
					dllmax[1] = dlli;
				पूर्ण
			पूर्ण
			passcnt++;
		पूर्ण अन्यथा अगर (passcnt >= CBR_THRESHOLD) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (retry++ > 10)
		जाओ CBR_DONE2;
	अगर (dllmax[0] == 0 || (dllmax[0]-dllmin[0]) < CBR_THRESHOLD) अणु
		जाओ CBR_START2;
	पूर्ण
	अगर (dllmax[1] == 0 || (dllmax[1]-dllmin[1]) < CBR_THRESHOLD) अणु
		जाओ CBR_START2;
	पूर्ण
	status = true;
CBR_DONE2:
	dlli  = (dllmin[1] + dllmax[1]) >> 1;
	dlli <<= 8;
	dlli += (dllmin[0] + dllmax[0]) >> 1;
	ast_moutdwm(ast, 0x1E6E0068, ast_mindwm(ast, 0x1E720058) | (dlli << 16));
	वापस status;
पूर्ण /* CBRDLL2 */

अटल व्योम get_ddr3_info(काष्ठा ast_निजी *ast, काष्ठा ast2300_dram_param *param)
अणु
	u32 trap, trap_AC2, trap_MRS;

	ast_moutdwm(ast, 0x1E6E2000, 0x1688A8A8);

	/* Ger trap info */
	trap = (ast_mindwm(ast, 0x1E6E2070) >> 25) & 0x3;
	trap_AC2  = 0x00020000 + (trap << 16);
	trap_AC2 |= 0x00300000 + ((trap & 0x2) << 19);
	trap_MRS  = 0x00000010 + (trap << 4);
	trap_MRS |= ((trap & 0x2) << 18);

	param->reg_MADJ       = 0x00034C4C;
	param->reg_SADJ       = 0x00001800;
	param->reg_DRV        = 0x000000F0;
	param->reg_PERIOD     = param->dram_freq;
	param->rodt           = 0;

	चयन (param->dram_freq) अणु
	हाल 336:
		ast_moutdwm(ast, 0x1E6E2020, 0x0190);
		param->wodt          = 0;
		param->reg_AC1       = 0x22202725;
		param->reg_AC2       = 0xAA007613 | trap_AC2;
		param->reg_DQSIC     = 0x000000BA;
		param->reg_MRS       = 0x04001400 | trap_MRS;
		param->reg_EMRS      = 0x00000000;
		param->reg_IOZ       = 0x00000023;
		param->reg_DQIDLY    = 0x00000074;
		param->reg_FREQ      = 0x00004DC0;
		param->madj_max      = 96;
		param->dll2_finetune_step = 3;
		चयन (param->dram_chipid) अणु
		शेष:
		हाल AST_DRAM_512Mx16:
		हाल AST_DRAM_1Gx16:
			param->reg_AC2   = 0xAA007613 | trap_AC2;
			अवरोध;
		हाल AST_DRAM_2Gx16:
			param->reg_AC2   = 0xAA00761C | trap_AC2;
			अवरोध;
		हाल AST_DRAM_4Gx16:
			param->reg_AC2   = 0xAA007636 | trap_AC2;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
	हाल 396:
		ast_moutdwm(ast, 0x1E6E2020, 0x03F1);
		param->wodt          = 1;
		param->reg_AC1       = 0x33302825;
		param->reg_AC2       = 0xCC009617 | trap_AC2;
		param->reg_DQSIC     = 0x000000E2;
		param->reg_MRS       = 0x04001600 | trap_MRS;
		param->reg_EMRS      = 0x00000000;
		param->reg_IOZ       = 0x00000034;
		param->reg_DRV       = 0x000000FA;
		param->reg_DQIDLY    = 0x00000089;
		param->reg_FREQ      = 0x00005040;
		param->madj_max      = 96;
		param->dll2_finetune_step = 4;

		चयन (param->dram_chipid) अणु
		शेष:
		हाल AST_DRAM_512Mx16:
		हाल AST_DRAM_1Gx16:
			param->reg_AC2   = 0xCC009617 | trap_AC2;
			अवरोध;
		हाल AST_DRAM_2Gx16:
			param->reg_AC2   = 0xCC009622 | trap_AC2;
			अवरोध;
		हाल AST_DRAM_4Gx16:
			param->reg_AC2   = 0xCC00963F | trap_AC2;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 408:
		ast_moutdwm(ast, 0x1E6E2020, 0x01F0);
		param->wodt          = 1;
		param->reg_AC1       = 0x33302825;
		param->reg_AC2       = 0xCC009617 | trap_AC2;
		param->reg_DQSIC     = 0x000000E2;
		param->reg_MRS       = 0x04001600 | trap_MRS;
		param->reg_EMRS      = 0x00000000;
		param->reg_IOZ       = 0x00000023;
		param->reg_DRV       = 0x000000FA;
		param->reg_DQIDLY    = 0x00000089;
		param->reg_FREQ      = 0x000050C0;
		param->madj_max      = 96;
		param->dll2_finetune_step = 4;

		चयन (param->dram_chipid) अणु
		शेष:
		हाल AST_DRAM_512Mx16:
		हाल AST_DRAM_1Gx16:
			param->reg_AC2   = 0xCC009617 | trap_AC2;
			अवरोध;
		हाल AST_DRAM_2Gx16:
			param->reg_AC2   = 0xCC009622 | trap_AC2;
			अवरोध;
		हाल AST_DRAM_4Gx16:
			param->reg_AC2   = 0xCC00963F | trap_AC2;
			अवरोध;
		पूर्ण

		अवरोध;
	हाल 456:
		ast_moutdwm(ast, 0x1E6E2020, 0x0230);
		param->wodt          = 0;
		param->reg_AC1       = 0x33302926;
		param->reg_AC2       = 0xCD44961A;
		param->reg_DQSIC     = 0x000000FC;
		param->reg_MRS       = 0x00081830;
		param->reg_EMRS      = 0x00000000;
		param->reg_IOZ       = 0x00000045;
		param->reg_DQIDLY    = 0x00000097;
		param->reg_FREQ      = 0x000052C0;
		param->madj_max      = 88;
		param->dll2_finetune_step = 4;
		अवरोध;
	हाल 504:
		ast_moutdwm(ast, 0x1E6E2020, 0x0270);
		param->wodt          = 1;
		param->reg_AC1       = 0x33302926;
		param->reg_AC2       = 0xDE44A61D;
		param->reg_DQSIC     = 0x00000117;
		param->reg_MRS       = 0x00081A30;
		param->reg_EMRS      = 0x00000000;
		param->reg_IOZ       = 0x070000BB;
		param->reg_DQIDLY    = 0x000000A0;
		param->reg_FREQ      = 0x000054C0;
		param->madj_max      = 79;
		param->dll2_finetune_step = 4;
		अवरोध;
	हाल 528:
		ast_moutdwm(ast, 0x1E6E2020, 0x0290);
		param->wodt          = 1;
		param->rodt          = 1;
		param->reg_AC1       = 0x33302926;
		param->reg_AC2       = 0xEF44B61E;
		param->reg_DQSIC     = 0x00000125;
		param->reg_MRS       = 0x00081A30;
		param->reg_EMRS      = 0x00000040;
		param->reg_DRV       = 0x000000F5;
		param->reg_IOZ       = 0x00000023;
		param->reg_DQIDLY    = 0x00000088;
		param->reg_FREQ      = 0x000055C0;
		param->madj_max      = 76;
		param->dll2_finetune_step = 3;
		अवरोध;
	हाल 576:
		ast_moutdwm(ast, 0x1E6E2020, 0x0140);
		param->reg_MADJ      = 0x00136868;
		param->reg_SADJ      = 0x00004534;
		param->wodt          = 1;
		param->rodt          = 1;
		param->reg_AC1       = 0x33302A37;
		param->reg_AC2       = 0xEF56B61E;
		param->reg_DQSIC     = 0x0000013F;
		param->reg_MRS       = 0x00101A50;
		param->reg_EMRS      = 0x00000040;
		param->reg_DRV       = 0x000000FA;
		param->reg_IOZ       = 0x00000023;
		param->reg_DQIDLY    = 0x00000078;
		param->reg_FREQ      = 0x000057C0;
		param->madj_max      = 136;
		param->dll2_finetune_step = 3;
		अवरोध;
	हाल 600:
		ast_moutdwm(ast, 0x1E6E2020, 0x02E1);
		param->reg_MADJ      = 0x00136868;
		param->reg_SADJ      = 0x00004534;
		param->wodt          = 1;
		param->rodt          = 1;
		param->reg_AC1       = 0x32302A37;
		param->reg_AC2       = 0xDF56B61F;
		param->reg_DQSIC     = 0x0000014D;
		param->reg_MRS       = 0x00101A50;
		param->reg_EMRS      = 0x00000004;
		param->reg_DRV       = 0x000000F5;
		param->reg_IOZ       = 0x00000023;
		param->reg_DQIDLY    = 0x00000078;
		param->reg_FREQ      = 0x000058C0;
		param->madj_max      = 132;
		param->dll2_finetune_step = 3;
		अवरोध;
	हाल 624:
		ast_moutdwm(ast, 0x1E6E2020, 0x0160);
		param->reg_MADJ      = 0x00136868;
		param->reg_SADJ      = 0x00004534;
		param->wodt          = 1;
		param->rodt          = 1;
		param->reg_AC1       = 0x32302A37;
		param->reg_AC2       = 0xEF56B621;
		param->reg_DQSIC     = 0x0000015A;
		param->reg_MRS       = 0x02101A50;
		param->reg_EMRS      = 0x00000004;
		param->reg_DRV       = 0x000000F5;
		param->reg_IOZ       = 0x00000034;
		param->reg_DQIDLY    = 0x00000078;
		param->reg_FREQ      = 0x000059C0;
		param->madj_max      = 128;
		param->dll2_finetune_step = 3;
		अवरोध;
	पूर्ण /* चयन freq */

	चयन (param->dram_chipid) अणु
	हाल AST_DRAM_512Mx16:
		param->dram_config = 0x130;
		अवरोध;
	शेष:
	हाल AST_DRAM_1Gx16:
		param->dram_config = 0x131;
		अवरोध;
	हाल AST_DRAM_2Gx16:
		param->dram_config = 0x132;
		अवरोध;
	हाल AST_DRAM_4Gx16:
		param->dram_config = 0x133;
		अवरोध;
	पूर्ण /* चयन size */

	चयन (param->vram_size) अणु
	शेष:
	हाल AST_VIDMEM_SIZE_8M:
		param->dram_config |= 0x00;
		अवरोध;
	हाल AST_VIDMEM_SIZE_16M:
		param->dram_config |= 0x04;
		अवरोध;
	हाल AST_VIDMEM_SIZE_32M:
		param->dram_config |= 0x08;
		अवरोध;
	हाल AST_VIDMEM_SIZE_64M:
		param->dram_config |= 0x0c;
		अवरोध;
	पूर्ण

पूर्ण

अटल व्योम ddr3_init(काष्ठा ast_निजी *ast, काष्ठा ast2300_dram_param *param)
अणु
	u32 data, data2, retry = 0;

ddr3_init_start:
	ast_moutdwm(ast, 0x1E6E0000, 0xFC600309);
	ast_moutdwm(ast, 0x1E6E0018, 0x00000100);
	ast_moutdwm(ast, 0x1E6E0024, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0034, 0x00000000);
	udelay(10);
	ast_moutdwm(ast, 0x1E6E0064, param->reg_MADJ);
	ast_moutdwm(ast, 0x1E6E0068, param->reg_SADJ);
	udelay(10);
	ast_moutdwm(ast, 0x1E6E0064, param->reg_MADJ | 0xC0000);
	udelay(10);

	ast_moutdwm(ast, 0x1E6E0004, param->dram_config);
	ast_moutdwm(ast, 0x1E6E0008, 0x90040f);
	ast_moutdwm(ast, 0x1E6E0010, param->reg_AC1);
	ast_moutdwm(ast, 0x1E6E0014, param->reg_AC2);
	ast_moutdwm(ast, 0x1E6E0020, param->reg_DQSIC);
	ast_moutdwm(ast, 0x1E6E0080, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0084, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0088, param->reg_DQIDLY);
	ast_moutdwm(ast, 0x1E6E0018, 0x4000A170);
	ast_moutdwm(ast, 0x1E6E0018, 0x00002370);
	ast_moutdwm(ast, 0x1E6E0038, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0040, 0xFF444444);
	ast_moutdwm(ast, 0x1E6E0044, 0x22222222);
	ast_moutdwm(ast, 0x1E6E0048, 0x22222222);
	ast_moutdwm(ast, 0x1E6E004C, 0x00000002);
	ast_moutdwm(ast, 0x1E6E0050, 0x80000000);
	ast_moutdwm(ast, 0x1E6E0050, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0054, 0);
	ast_moutdwm(ast, 0x1E6E0060, param->reg_DRV);
	ast_moutdwm(ast, 0x1E6E006C, param->reg_IOZ);
	ast_moutdwm(ast, 0x1E6E0070, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0074, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0078, 0x00000000);
	ast_moutdwm(ast, 0x1E6E007C, 0x00000000);
	/* Wait MCLK2X lock to MCLK */
	करो अणु
		data = ast_mindwm(ast, 0x1E6E001C);
	पूर्ण जबतक (!(data & 0x08000000));
	data = ast_mindwm(ast, 0x1E6E001C);
	data = (data >> 8) & 0xff;
	जबतक ((data & 0x08) || ((data & 0x7) < 2) || (data < 4)) अणु
		data2 = (ast_mindwm(ast, 0x1E6E0064) & 0xfff3ffff) + 4;
		अगर ((data2 & 0xff) > param->madj_max) अणु
			अवरोध;
		पूर्ण
		ast_moutdwm(ast, 0x1E6E0064, data2);
		अगर (data2 & 0x00100000) अणु
			data2 = ((data2 & 0xff) >> 3) + 3;
		पूर्ण अन्यथा अणु
			data2 = ((data2 & 0xff) >> 2) + 5;
		पूर्ण
		data = ast_mindwm(ast, 0x1E6E0068) & 0xffff00ff;
		data2 += data & 0xff;
		data = data | (data2 << 8);
		ast_moutdwm(ast, 0x1E6E0068, data);
		udelay(10);
		ast_moutdwm(ast, 0x1E6E0064, ast_mindwm(ast, 0x1E6E0064) | 0xC0000);
		udelay(10);
		data = ast_mindwm(ast, 0x1E6E0018) & 0xfffff1ff;
		ast_moutdwm(ast, 0x1E6E0018, data);
		data = data | 0x200;
		ast_moutdwm(ast, 0x1E6E0018, data);
		करो अणु
			data = ast_mindwm(ast, 0x1E6E001C);
		पूर्ण जबतक (!(data & 0x08000000));

		data = ast_mindwm(ast, 0x1E6E001C);
		data = (data >> 8) & 0xff;
	पूर्ण
	ast_moutdwm(ast, 0x1E720058, ast_mindwm(ast, 0x1E6E0068) & 0xffff);
	data = ast_mindwm(ast, 0x1E6E0018) | 0xC00;
	ast_moutdwm(ast, 0x1E6E0018, data);

	ast_moutdwm(ast, 0x1E6E0034, 0x00000001);
	ast_moutdwm(ast, 0x1E6E000C, 0x00000040);
	udelay(50);
	/* Mode Register Setting */
	ast_moutdwm(ast, 0x1E6E002C, param->reg_MRS | 0x100);
	ast_moutdwm(ast, 0x1E6E0030, param->reg_EMRS);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000005);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000007);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000003);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000001);
	ast_moutdwm(ast, 0x1E6E002C, param->reg_MRS);
	ast_moutdwm(ast, 0x1E6E000C, 0x00005C08);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000001);

	ast_moutdwm(ast, 0x1E6E000C, 0x00005C01);
	data = 0;
	अगर (param->wodt) अणु
		data = 0x300;
	पूर्ण
	अगर (param->rodt) अणु
		data = data | 0x3000 | ((param->reg_AC2 & 0x60000) >> 3);
	पूर्ण
	ast_moutdwm(ast, 0x1E6E0034, data | 0x3);

	/* Calibrate the DQSI delay */
	अगर ((cbr_dll2(ast, param) == false) && (retry++ < 10))
		जाओ ddr3_init_start;

	ast_moutdwm(ast, 0x1E6E0120, param->reg_FREQ);
	/* ECC Memory Initialization */
#अगर_घोषित ECC
	ast_moutdwm(ast, 0x1E6E007C, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0070, 0x221);
	करो अणु
		data = ast_mindwm(ast, 0x1E6E0070);
	पूर्ण जबतक (!(data & 0x00001000));
	ast_moutdwm(ast, 0x1E6E0070, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0050, 0x80000000);
	ast_moutdwm(ast, 0x1E6E0050, 0x00000000);
#पूर्ण_अगर


पूर्ण

अटल व्योम get_ddr2_info(काष्ठा ast_निजी *ast, काष्ठा ast2300_dram_param *param)
अणु
	u32 trap, trap_AC2, trap_MRS;

	ast_moutdwm(ast, 0x1E6E2000, 0x1688A8A8);

	/* Ger trap info */
	trap = (ast_mindwm(ast, 0x1E6E2070) >> 25) & 0x3;
	trap_AC2  = (trap << 20) | (trap << 16);
	trap_AC2 += 0x00110000;
	trap_MRS  = 0x00000040 | (trap << 4);


	param->reg_MADJ       = 0x00034C4C;
	param->reg_SADJ       = 0x00001800;
	param->reg_DRV        = 0x000000F0;
	param->reg_PERIOD     = param->dram_freq;
	param->rodt           = 0;

	चयन (param->dram_freq) अणु
	हाल 264:
		ast_moutdwm(ast, 0x1E6E2020, 0x0130);
		param->wodt          = 0;
		param->reg_AC1       = 0x11101513;
		param->reg_AC2       = 0x78117011;
		param->reg_DQSIC     = 0x00000092;
		param->reg_MRS       = 0x00000842;
		param->reg_EMRS      = 0x00000000;
		param->reg_DRV       = 0x000000F0;
		param->reg_IOZ       = 0x00000034;
		param->reg_DQIDLY    = 0x0000005A;
		param->reg_FREQ      = 0x00004AC0;
		param->madj_max      = 138;
		param->dll2_finetune_step = 3;
		अवरोध;
	हाल 336:
		ast_moutdwm(ast, 0x1E6E2020, 0x0190);
		param->wodt          = 1;
		param->reg_AC1       = 0x22202613;
		param->reg_AC2       = 0xAA009016 | trap_AC2;
		param->reg_DQSIC     = 0x000000BA;
		param->reg_MRS       = 0x00000A02 | trap_MRS;
		param->reg_EMRS      = 0x00000040;
		param->reg_DRV       = 0x000000FA;
		param->reg_IOZ       = 0x00000034;
		param->reg_DQIDLY    = 0x00000074;
		param->reg_FREQ      = 0x00004DC0;
		param->madj_max      = 96;
		param->dll2_finetune_step = 3;
		चयन (param->dram_chipid) अणु
		शेष:
		हाल AST_DRAM_512Mx16:
			param->reg_AC2   = 0xAA009012 | trap_AC2;
			अवरोध;
		हाल AST_DRAM_1Gx16:
			param->reg_AC2   = 0xAA009016 | trap_AC2;
			अवरोध;
		हाल AST_DRAM_2Gx16:
			param->reg_AC2   = 0xAA009023 | trap_AC2;
			अवरोध;
		हाल AST_DRAM_4Gx16:
			param->reg_AC2   = 0xAA00903B | trap_AC2;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
	हाल 396:
		ast_moutdwm(ast, 0x1E6E2020, 0x03F1);
		param->wodt          = 1;
		param->rodt          = 0;
		param->reg_AC1       = 0x33302714;
		param->reg_AC2       = 0xCC00B01B | trap_AC2;
		param->reg_DQSIC     = 0x000000E2;
		param->reg_MRS       = 0x00000C02 | trap_MRS;
		param->reg_EMRS      = 0x00000040;
		param->reg_DRV       = 0x000000FA;
		param->reg_IOZ       = 0x00000034;
		param->reg_DQIDLY    = 0x00000089;
		param->reg_FREQ      = 0x00005040;
		param->madj_max      = 96;
		param->dll2_finetune_step = 4;

		चयन (param->dram_chipid) अणु
		हाल AST_DRAM_512Mx16:
			param->reg_AC2   = 0xCC00B016 | trap_AC2;
			अवरोध;
		शेष:
		हाल AST_DRAM_1Gx16:
			param->reg_AC2   = 0xCC00B01B | trap_AC2;
			अवरोध;
		हाल AST_DRAM_2Gx16:
			param->reg_AC2   = 0xCC00B02B | trap_AC2;
			अवरोध;
		हाल AST_DRAM_4Gx16:
			param->reg_AC2   = 0xCC00B03F | trap_AC2;
			अवरोध;
		पूर्ण

		अवरोध;

	हाल 408:
		ast_moutdwm(ast, 0x1E6E2020, 0x01F0);
		param->wodt          = 1;
		param->rodt          = 0;
		param->reg_AC1       = 0x33302714;
		param->reg_AC2       = 0xCC00B01B | trap_AC2;
		param->reg_DQSIC     = 0x000000E2;
		param->reg_MRS       = 0x00000C02 | trap_MRS;
		param->reg_EMRS      = 0x00000040;
		param->reg_DRV       = 0x000000FA;
		param->reg_IOZ       = 0x00000034;
		param->reg_DQIDLY    = 0x00000089;
		param->reg_FREQ      = 0x000050C0;
		param->madj_max      = 96;
		param->dll2_finetune_step = 4;

		चयन (param->dram_chipid) अणु
		हाल AST_DRAM_512Mx16:
			param->reg_AC2   = 0xCC00B016 | trap_AC2;
			अवरोध;
		शेष:
		हाल AST_DRAM_1Gx16:
			param->reg_AC2   = 0xCC00B01B | trap_AC2;
			अवरोध;
		हाल AST_DRAM_2Gx16:
			param->reg_AC2   = 0xCC00B02B | trap_AC2;
			अवरोध;
		हाल AST_DRAM_4Gx16:
			param->reg_AC2   = 0xCC00B03F | trap_AC2;
			अवरोध;
		पूर्ण

		अवरोध;
	हाल 456:
		ast_moutdwm(ast, 0x1E6E2020, 0x0230);
		param->wodt          = 0;
		param->reg_AC1       = 0x33302815;
		param->reg_AC2       = 0xCD44B01E;
		param->reg_DQSIC     = 0x000000FC;
		param->reg_MRS       = 0x00000E72;
		param->reg_EMRS      = 0x00000000;
		param->reg_DRV       = 0x00000000;
		param->reg_IOZ       = 0x00000034;
		param->reg_DQIDLY    = 0x00000097;
		param->reg_FREQ      = 0x000052C0;
		param->madj_max      = 88;
		param->dll2_finetune_step = 3;
		अवरोध;
	हाल 504:
		ast_moutdwm(ast, 0x1E6E2020, 0x0261);
		param->wodt          = 1;
		param->rodt          = 1;
		param->reg_AC1       = 0x33302815;
		param->reg_AC2       = 0xDE44C022;
		param->reg_DQSIC     = 0x00000117;
		param->reg_MRS       = 0x00000E72;
		param->reg_EMRS      = 0x00000040;
		param->reg_DRV       = 0x0000000A;
		param->reg_IOZ       = 0x00000045;
		param->reg_DQIDLY    = 0x000000A0;
		param->reg_FREQ      = 0x000054C0;
		param->madj_max      = 79;
		param->dll2_finetune_step = 3;
		अवरोध;
	हाल 528:
		ast_moutdwm(ast, 0x1E6E2020, 0x0120);
		param->wodt          = 1;
		param->rodt          = 1;
		param->reg_AC1       = 0x33302815;
		param->reg_AC2       = 0xEF44D024;
		param->reg_DQSIC     = 0x00000125;
		param->reg_MRS       = 0x00000E72;
		param->reg_EMRS      = 0x00000004;
		param->reg_DRV       = 0x000000F9;
		param->reg_IOZ       = 0x00000045;
		param->reg_DQIDLY    = 0x000000A7;
		param->reg_FREQ      = 0x000055C0;
		param->madj_max      = 76;
		param->dll2_finetune_step = 3;
		अवरोध;
	हाल 552:
		ast_moutdwm(ast, 0x1E6E2020, 0x02A1);
		param->wodt          = 1;
		param->rodt          = 1;
		param->reg_AC1       = 0x43402915;
		param->reg_AC2       = 0xFF44E025;
		param->reg_DQSIC     = 0x00000132;
		param->reg_MRS       = 0x00000E72;
		param->reg_EMRS      = 0x00000040;
		param->reg_DRV       = 0x0000000A;
		param->reg_IOZ       = 0x00000045;
		param->reg_DQIDLY    = 0x000000AD;
		param->reg_FREQ      = 0x000056C0;
		param->madj_max      = 76;
		param->dll2_finetune_step = 3;
		अवरोध;
	हाल 576:
		ast_moutdwm(ast, 0x1E6E2020, 0x0140);
		param->wodt          = 1;
		param->rodt          = 1;
		param->reg_AC1       = 0x43402915;
		param->reg_AC2       = 0xFF44E027;
		param->reg_DQSIC     = 0x0000013F;
		param->reg_MRS       = 0x00000E72;
		param->reg_EMRS      = 0x00000004;
		param->reg_DRV       = 0x000000F5;
		param->reg_IOZ       = 0x00000045;
		param->reg_DQIDLY    = 0x000000B3;
		param->reg_FREQ      = 0x000057C0;
		param->madj_max      = 76;
		param->dll2_finetune_step = 3;
		अवरोध;
	पूर्ण

	चयन (param->dram_chipid) अणु
	हाल AST_DRAM_512Mx16:
		param->dram_config = 0x100;
		अवरोध;
	शेष:
	हाल AST_DRAM_1Gx16:
		param->dram_config = 0x121;
		अवरोध;
	हाल AST_DRAM_2Gx16:
		param->dram_config = 0x122;
		अवरोध;
	हाल AST_DRAM_4Gx16:
		param->dram_config = 0x123;
		अवरोध;
	पूर्ण /* चयन size */

	चयन (param->vram_size) अणु
	शेष:
	हाल AST_VIDMEM_SIZE_8M:
		param->dram_config |= 0x00;
		अवरोध;
	हाल AST_VIDMEM_SIZE_16M:
		param->dram_config |= 0x04;
		अवरोध;
	हाल AST_VIDMEM_SIZE_32M:
		param->dram_config |= 0x08;
		अवरोध;
	हाल AST_VIDMEM_SIZE_64M:
		param->dram_config |= 0x0c;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ddr2_init(काष्ठा ast_निजी *ast, काष्ठा ast2300_dram_param *param)
अणु
	u32 data, data2, retry = 0;

ddr2_init_start:
	ast_moutdwm(ast, 0x1E6E0000, 0xFC600309);
	ast_moutdwm(ast, 0x1E6E0018, 0x00000100);
	ast_moutdwm(ast, 0x1E6E0024, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0064, param->reg_MADJ);
	ast_moutdwm(ast, 0x1E6E0068, param->reg_SADJ);
	udelay(10);
	ast_moutdwm(ast, 0x1E6E0064, param->reg_MADJ | 0xC0000);
	udelay(10);

	ast_moutdwm(ast, 0x1E6E0004, param->dram_config);
	ast_moutdwm(ast, 0x1E6E0008, 0x90040f);
	ast_moutdwm(ast, 0x1E6E0010, param->reg_AC1);
	ast_moutdwm(ast, 0x1E6E0014, param->reg_AC2);
	ast_moutdwm(ast, 0x1E6E0020, param->reg_DQSIC);
	ast_moutdwm(ast, 0x1E6E0080, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0084, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0088, param->reg_DQIDLY);
	ast_moutdwm(ast, 0x1E6E0018, 0x4000A130);
	ast_moutdwm(ast, 0x1E6E0018, 0x00002330);
	ast_moutdwm(ast, 0x1E6E0038, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0040, 0xFF808000);
	ast_moutdwm(ast, 0x1E6E0044, 0x88848466);
	ast_moutdwm(ast, 0x1E6E0048, 0x44440008);
	ast_moutdwm(ast, 0x1E6E004C, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0050, 0x80000000);
	ast_moutdwm(ast, 0x1E6E0050, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0054, 0);
	ast_moutdwm(ast, 0x1E6E0060, param->reg_DRV);
	ast_moutdwm(ast, 0x1E6E006C, param->reg_IOZ);
	ast_moutdwm(ast, 0x1E6E0070, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0074, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0078, 0x00000000);
	ast_moutdwm(ast, 0x1E6E007C, 0x00000000);

	/* Wait MCLK2X lock to MCLK */
	करो अणु
		data = ast_mindwm(ast, 0x1E6E001C);
	पूर्ण जबतक (!(data & 0x08000000));
	data = ast_mindwm(ast, 0x1E6E001C);
	data = (data >> 8) & 0xff;
	जबतक ((data & 0x08) || ((data & 0x7) < 2) || (data < 4)) अणु
		data2 = (ast_mindwm(ast, 0x1E6E0064) & 0xfff3ffff) + 4;
		अगर ((data2 & 0xff) > param->madj_max) अणु
			अवरोध;
		पूर्ण
		ast_moutdwm(ast, 0x1E6E0064, data2);
		अगर (data2 & 0x00100000) अणु
			data2 = ((data2 & 0xff) >> 3) + 3;
		पूर्ण अन्यथा अणु
			data2 = ((data2 & 0xff) >> 2) + 5;
		पूर्ण
		data = ast_mindwm(ast, 0x1E6E0068) & 0xffff00ff;
		data2 += data & 0xff;
		data = data | (data2 << 8);
		ast_moutdwm(ast, 0x1E6E0068, data);
		udelay(10);
		ast_moutdwm(ast, 0x1E6E0064, ast_mindwm(ast, 0x1E6E0064) | 0xC0000);
		udelay(10);
		data = ast_mindwm(ast, 0x1E6E0018) & 0xfffff1ff;
		ast_moutdwm(ast, 0x1E6E0018, data);
		data = data | 0x200;
		ast_moutdwm(ast, 0x1E6E0018, data);
		करो अणु
			data = ast_mindwm(ast, 0x1E6E001C);
		पूर्ण जबतक (!(data & 0x08000000));

		data = ast_mindwm(ast, 0x1E6E001C);
		data = (data >> 8) & 0xff;
	पूर्ण
	ast_moutdwm(ast, 0x1E720058, ast_mindwm(ast, 0x1E6E0008) & 0xffff);
	data = ast_mindwm(ast, 0x1E6E0018) | 0xC00;
	ast_moutdwm(ast, 0x1E6E0018, data);

	ast_moutdwm(ast, 0x1E6E0034, 0x00000001);
	ast_moutdwm(ast, 0x1E6E000C, 0x00000000);
	udelay(50);
	/* Mode Register Setting */
	ast_moutdwm(ast, 0x1E6E002C, param->reg_MRS | 0x100);
	ast_moutdwm(ast, 0x1E6E0030, param->reg_EMRS);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000005);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000007);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000003);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000001);

	ast_moutdwm(ast, 0x1E6E000C, 0x00005C08);
	ast_moutdwm(ast, 0x1E6E002C, param->reg_MRS);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000001);
	ast_moutdwm(ast, 0x1E6E0030, param->reg_EMRS | 0x380);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000003);
	ast_moutdwm(ast, 0x1E6E0030, param->reg_EMRS);
	ast_moutdwm(ast, 0x1E6E0028, 0x00000003);

	ast_moutdwm(ast, 0x1E6E000C, 0x7FFF5C01);
	data = 0;
	अगर (param->wodt) अणु
		data = 0x500;
	पूर्ण
	अगर (param->rodt) अणु
		data = data | 0x3000 | ((param->reg_AC2 & 0x60000) >> 3);
	पूर्ण
	ast_moutdwm(ast, 0x1E6E0034, data | 0x3);
	ast_moutdwm(ast, 0x1E6E0120, param->reg_FREQ);

	/* Calibrate the DQSI delay */
	अगर ((cbr_dll2(ast, param) == false) && (retry++ < 10))
		जाओ ddr2_init_start;

	/* ECC Memory Initialization */
#अगर_घोषित ECC
	ast_moutdwm(ast, 0x1E6E007C, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0070, 0x221);
	करो अणु
		data = ast_mindwm(ast, 0x1E6E0070);
	पूर्ण जबतक (!(data & 0x00001000));
	ast_moutdwm(ast, 0x1E6E0070, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0050, 0x80000000);
	ast_moutdwm(ast, 0x1E6E0050, 0x00000000);
#पूर्ण_अगर

पूर्ण

अटल व्योम ast_post_chip_2300(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	काष्ठा ast2300_dram_param param;
	u32 temp;
	u8 reg;

	reg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd0, 0xff);
	अगर ((reg & 0x80) == 0) अणु/* vga only */
		ast_ग_लिखो32(ast, 0xf004, 0x1e6e0000);
		ast_ग_लिखो32(ast, 0xf000, 0x1);
		ast_ग_लिखो32(ast, 0x12000, 0x1688a8a8);
		करो अणु
			;
		पूर्ण जबतक (ast_पढ़ो32(ast, 0x12000) != 0x1);

		ast_ग_लिखो32(ast, 0x10000, 0xfc600309);
		करो अणु
			;
		पूर्ण जबतक (ast_पढ़ो32(ast, 0x10000) != 0x1);

		/* Slow करोwn CPU/AHB CLK in VGA only mode */
		temp = ast_पढ़ो32(ast, 0x12008);
		temp |= 0x73;
		ast_ग_लिखो32(ast, 0x12008, temp);

		param.dram_freq = 396;
		param.dram_type = AST_DDR3;
		temp = ast_mindwm(ast, 0x1e6e2070);
		अगर (temp & 0x01000000)
			param.dram_type = AST_DDR2;
                चयन (temp & 0x18000000) अणु
		हाल 0:
			param.dram_chipid = AST_DRAM_512Mx16;
			अवरोध;
		शेष:
		हाल 0x08000000:
			param.dram_chipid = AST_DRAM_1Gx16;
			अवरोध;
		हाल 0x10000000:
			param.dram_chipid = AST_DRAM_2Gx16;
			अवरोध;
		हाल 0x18000000:
			param.dram_chipid = AST_DRAM_4Gx16;
			अवरोध;
		पूर्ण
                चयन (temp & 0x0c) अणु
                शेष:
		हाल 0x00:
			param.vram_size = AST_VIDMEM_SIZE_8M;
			अवरोध;

		हाल 0x04:
			param.vram_size = AST_VIDMEM_SIZE_16M;
			अवरोध;

		हाल 0x08:
			param.vram_size = AST_VIDMEM_SIZE_32M;
			अवरोध;

		हाल 0x0c:
			param.vram_size = AST_VIDMEM_SIZE_64M;
			अवरोध;
		पूर्ण

		अगर (param.dram_type == AST_DDR3) अणु
			get_ddr3_info(ast, &param);
			ddr3_init(ast, &param);
		पूर्ण अन्यथा अणु
			get_ddr2_info(ast, &param);
			ddr2_init(ast, &param);
		पूर्ण

		temp = ast_mindwm(ast, 0x1e6e2040);
		ast_moutdwm(ast, 0x1e6e2040, temp | 0x40);
	पूर्ण

	/* रुको पढ़ोy */
	करो अणु
		reg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd0, 0xff);
	पूर्ण जबतक ((reg & 0x40) == 0);
पूर्ण

अटल bool cbr_test_2500(काष्ठा ast_निजी *ast)
अणु
	ast_moutdwm(ast, 0x1E6E0074, 0x0000FFFF);
	ast_moutdwm(ast, 0x1E6E007C, 0xFF00FF00);
	अगर (!mmc_test_burst(ast, 0))
		वापस false;
	अगर (!mmc_test_single_2500(ast, 0))
		वापस false;
	वापस true;
पूर्ण

अटल bool ddr_test_2500(काष्ठा ast_निजी *ast)
अणु
	ast_moutdwm(ast, 0x1E6E0074, 0x0000FFFF);
	ast_moutdwm(ast, 0x1E6E007C, 0xFF00FF00);
	अगर (!mmc_test_burst(ast, 0))
		वापस false;
	अगर (!mmc_test_burst(ast, 1))
		वापस false;
	अगर (!mmc_test_burst(ast, 2))
		वापस false;
	अगर (!mmc_test_burst(ast, 3))
		वापस false;
	अगर (!mmc_test_single_2500(ast, 0))
		वापस false;
	वापस true;
पूर्ण

अटल व्योम ddr_init_common_2500(काष्ठा ast_निजी *ast)
अणु
	ast_moutdwm(ast, 0x1E6E0034, 0x00020080);
	ast_moutdwm(ast, 0x1E6E0008, 0x2003000F);
	ast_moutdwm(ast, 0x1E6E0038, 0x00000FFF);
	ast_moutdwm(ast, 0x1E6E0040, 0x88448844);
	ast_moutdwm(ast, 0x1E6E0044, 0x24422288);
	ast_moutdwm(ast, 0x1E6E0048, 0x22222222);
	ast_moutdwm(ast, 0x1E6E004C, 0x22222222);
	ast_moutdwm(ast, 0x1E6E0050, 0x80000000);
	ast_moutdwm(ast, 0x1E6E0208, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0218, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0220, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0228, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0230, 0x00000000);
	ast_moutdwm(ast, 0x1E6E02A8, 0x00000000);
	ast_moutdwm(ast, 0x1E6E02B0, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0240, 0x86000000);
	ast_moutdwm(ast, 0x1E6E0244, 0x00008600);
	ast_moutdwm(ast, 0x1E6E0248, 0x80000000);
	ast_moutdwm(ast, 0x1E6E024C, 0x80808080);
पूर्ण

अटल व्योम ddr_phy_init_2500(काष्ठा ast_निजी *ast)
अणु
	u32 data, pass, समयcnt;

	pass = 0;
	ast_moutdwm(ast, 0x1E6E0060, 0x00000005);
	जबतक (!pass) अणु
		क्रम (समयcnt = 0; समयcnt < TIMEOUT; समयcnt++) अणु
			data = ast_mindwm(ast, 0x1E6E0060) & 0x1;
			अगर (!data)
				अवरोध;
		पूर्ण
		अगर (समयcnt != TIMEOUT) अणु
			data = ast_mindwm(ast, 0x1E6E0300) & 0x000A0000;
			अगर (!data)
				pass = 1;
		पूर्ण
		अगर (!pass) अणु
			ast_moutdwm(ast, 0x1E6E0060, 0x00000000);
			udelay(10); /* delay 10 us */
			ast_moutdwm(ast, 0x1E6E0060, 0x00000005);
		पूर्ण
	पूर्ण

	ast_moutdwm(ast, 0x1E6E0060, 0x00000006);
पूर्ण

/*
 * Check DRAM Size
 * 1Gb : 0x80000000 ~ 0x87FFFFFF
 * 2Gb : 0x80000000 ~ 0x8FFFFFFF
 * 4Gb : 0x80000000 ~ 0x9FFFFFFF
 * 8Gb : 0x80000000 ~ 0xBFFFFFFF
 */
अटल व्योम check_dram_size_2500(काष्ठा ast_निजी *ast, u32 tRFC)
अणु
	u32 reg_04, reg_14;

	reg_04 = ast_mindwm(ast, 0x1E6E0004) & 0xfffffffc;
	reg_14 = ast_mindwm(ast, 0x1E6E0014) & 0xffffff00;

	ast_moutdwm(ast, 0xA0100000, 0x41424344);
	ast_moutdwm(ast, 0x90100000, 0x35363738);
	ast_moutdwm(ast, 0x88100000, 0x292A2B2C);
	ast_moutdwm(ast, 0x80100000, 0x1D1E1F10);

	/* Check 8Gbit */
	अगर (ast_mindwm(ast, 0xA0100000) == 0x41424344) अणु
		reg_04 |= 0x03;
		reg_14 |= (tRFC >> 24) & 0xFF;
		/* Check 4Gbit */
	पूर्ण अन्यथा अगर (ast_mindwm(ast, 0x90100000) == 0x35363738) अणु
		reg_04 |= 0x02;
		reg_14 |= (tRFC >> 16) & 0xFF;
		/* Check 2Gbit */
	पूर्ण अन्यथा अगर (ast_mindwm(ast, 0x88100000) == 0x292A2B2C) अणु
		reg_04 |= 0x01;
		reg_14 |= (tRFC >> 8) & 0xFF;
	पूर्ण अन्यथा अणु
		reg_14 |= tRFC & 0xFF;
	पूर्ण
	ast_moutdwm(ast, 0x1E6E0004, reg_04);
	ast_moutdwm(ast, 0x1E6E0014, reg_14);
पूर्ण

अटल व्योम enable_cache_2500(काष्ठा ast_निजी *ast)
अणु
	u32 reg_04, data;

	reg_04 = ast_mindwm(ast, 0x1E6E0004);
	ast_moutdwm(ast, 0x1E6E0004, reg_04 | 0x1000);

	करो
		data = ast_mindwm(ast, 0x1E6E0004);
	जबतक (!(data & 0x80000));
	ast_moutdwm(ast, 0x1E6E0004, reg_04 | 0x400);
पूर्ण

अटल व्योम set_mpll_2500(काष्ठा ast_निजी *ast)
अणु
	u32 addr, data, param;

	/* Reset MMC */
	ast_moutdwm(ast, 0x1E6E0000, 0xFC600309);
	ast_moutdwm(ast, 0x1E6E0034, 0x00020080);
	क्रम (addr = 0x1e6e0004; addr < 0x1e6e0090;) अणु
		ast_moutdwm(ast, addr, 0x0);
		addr += 4;
	पूर्ण
	ast_moutdwm(ast, 0x1E6E0034, 0x00020000);

	ast_moutdwm(ast, 0x1E6E2000, 0x1688A8A8);
	data = ast_mindwm(ast, 0x1E6E2070) & 0x00800000;
	अगर (data) अणु
		/* CLKIN = 25MHz */
		param = 0x930023E0;
		ast_moutdwm(ast, 0x1E6E2160, 0x00011320);
	पूर्ण अन्यथा अणु
		/* CLKIN = 24MHz */
		param = 0x93002400;
	पूर्ण
	ast_moutdwm(ast, 0x1E6E2020, param);
	udelay(100);
पूर्ण

अटल व्योम reset_mmc_2500(काष्ठा ast_निजी *ast)
अणु
	ast_moutdwm(ast, 0x1E78505C, 0x00000004);
	ast_moutdwm(ast, 0x1E785044, 0x00000001);
	ast_moutdwm(ast, 0x1E785048, 0x00004755);
	ast_moutdwm(ast, 0x1E78504C, 0x00000013);
	mdelay(100);
	ast_moutdwm(ast, 0x1E785054, 0x00000077);
	ast_moutdwm(ast, 0x1E6E0000, 0xFC600309);
पूर्ण

अटल व्योम ddr3_init_2500(काष्ठा ast_निजी *ast, स्थिर u32 *ddr_table)
अणु

	ast_moutdwm(ast, 0x1E6E0004, 0x00000303);
	ast_moutdwm(ast, 0x1E6E0010, ddr_table[REGIDX_010]);
	ast_moutdwm(ast, 0x1E6E0014, ddr_table[REGIDX_014]);
	ast_moutdwm(ast, 0x1E6E0018, ddr_table[REGIDX_018]);
	ast_moutdwm(ast, 0x1E6E0020, ddr_table[REGIDX_020]);	     /* MODEREG4/6 */
	ast_moutdwm(ast, 0x1E6E0024, ddr_table[REGIDX_024]);	     /* MODEREG5 */
	ast_moutdwm(ast, 0x1E6E002C, ddr_table[REGIDX_02C] | 0x100); /* MODEREG0/2 */
	ast_moutdwm(ast, 0x1E6E0030, ddr_table[REGIDX_030]);	     /* MODEREG1/3 */

	/* DDR PHY Setting */
	ast_moutdwm(ast, 0x1E6E0200, 0x02492AAE);
	ast_moutdwm(ast, 0x1E6E0204, 0x00001001);
	ast_moutdwm(ast, 0x1E6E020C, 0x55E00B0B);
	ast_moutdwm(ast, 0x1E6E0210, 0x20000000);
	ast_moutdwm(ast, 0x1E6E0214, ddr_table[REGIDX_214]);
	ast_moutdwm(ast, 0x1E6E02E0, ddr_table[REGIDX_2E0]);
	ast_moutdwm(ast, 0x1E6E02E4, ddr_table[REGIDX_2E4]);
	ast_moutdwm(ast, 0x1E6E02E8, ddr_table[REGIDX_2E8]);
	ast_moutdwm(ast, 0x1E6E02EC, ddr_table[REGIDX_2EC]);
	ast_moutdwm(ast, 0x1E6E02F0, ddr_table[REGIDX_2F0]);
	ast_moutdwm(ast, 0x1E6E02F4, ddr_table[REGIDX_2F4]);
	ast_moutdwm(ast, 0x1E6E02F8, ddr_table[REGIDX_2F8]);
	ast_moutdwm(ast, 0x1E6E0290, 0x00100008);
	ast_moutdwm(ast, 0x1E6E02C0, 0x00000006);

	/* Controller Setting */
	ast_moutdwm(ast, 0x1E6E0034, 0x00020091);

	/* Wait DDR PHY init करोne */
	ddr_phy_init_2500(ast);

	ast_moutdwm(ast, 0x1E6E0120, ddr_table[REGIDX_PLL]);
	ast_moutdwm(ast, 0x1E6E000C, 0x42AA5C81);
	ast_moutdwm(ast, 0x1E6E0034, 0x0001AF93);

	check_dram_size_2500(ast, ddr_table[REGIDX_RFC]);
	enable_cache_2500(ast);
	ast_moutdwm(ast, 0x1E6E001C, 0x00000008);
	ast_moutdwm(ast, 0x1E6E0038, 0xFFFFFF00);
पूर्ण

अटल व्योम ddr4_init_2500(काष्ठा ast_निजी *ast, स्थिर u32 *ddr_table)
अणु
	u32 data, data2, pass, retrycnt;
	u32 ddr_vref, phy_vref;
	u32 min_ddr_vref = 0, min_phy_vref = 0;
	u32 max_ddr_vref = 0, max_phy_vref = 0;

	ast_moutdwm(ast, 0x1E6E0004, 0x00000313);
	ast_moutdwm(ast, 0x1E6E0010, ddr_table[REGIDX_010]);
	ast_moutdwm(ast, 0x1E6E0014, ddr_table[REGIDX_014]);
	ast_moutdwm(ast, 0x1E6E0018, ddr_table[REGIDX_018]);
	ast_moutdwm(ast, 0x1E6E0020, ddr_table[REGIDX_020]);	     /* MODEREG4/6 */
	ast_moutdwm(ast, 0x1E6E0024, ddr_table[REGIDX_024]);	     /* MODEREG5 */
	ast_moutdwm(ast, 0x1E6E002C, ddr_table[REGIDX_02C] | 0x100); /* MODEREG0/2 */
	ast_moutdwm(ast, 0x1E6E0030, ddr_table[REGIDX_030]);	     /* MODEREG1/3 */

	/* DDR PHY Setting */
	ast_moutdwm(ast, 0x1E6E0200, 0x42492AAE);
	ast_moutdwm(ast, 0x1E6E0204, 0x09002000);
	ast_moutdwm(ast, 0x1E6E020C, 0x55E00B0B);
	ast_moutdwm(ast, 0x1E6E0210, 0x20000000);
	ast_moutdwm(ast, 0x1E6E0214, ddr_table[REGIDX_214]);
	ast_moutdwm(ast, 0x1E6E02E0, ddr_table[REGIDX_2E0]);
	ast_moutdwm(ast, 0x1E6E02E4, ddr_table[REGIDX_2E4]);
	ast_moutdwm(ast, 0x1E6E02E8, ddr_table[REGIDX_2E8]);
	ast_moutdwm(ast, 0x1E6E02EC, ddr_table[REGIDX_2EC]);
	ast_moutdwm(ast, 0x1E6E02F0, ddr_table[REGIDX_2F0]);
	ast_moutdwm(ast, 0x1E6E02F4, ddr_table[REGIDX_2F4]);
	ast_moutdwm(ast, 0x1E6E02F8, ddr_table[REGIDX_2F8]);
	ast_moutdwm(ast, 0x1E6E0290, 0x00100008);
	ast_moutdwm(ast, 0x1E6E02C4, 0x3C183C3C);
	ast_moutdwm(ast, 0x1E6E02C8, 0x00631E0E);

	/* Controller Setting */
	ast_moutdwm(ast, 0x1E6E0034, 0x0001A991);

	/* Train PHY Vref first */
	pass = 0;

	क्रम (retrycnt = 0; retrycnt < 4 && pass == 0; retrycnt++) अणु
		max_phy_vref = 0x0;
		pass = 0;
		ast_moutdwm(ast, 0x1E6E02C0, 0x00001C06);
		क्रम (phy_vref = 0x40; phy_vref < 0x80; phy_vref++) अणु
			ast_moutdwm(ast, 0x1E6E000C, 0x00000000);
			ast_moutdwm(ast, 0x1E6E0060, 0x00000000);
			ast_moutdwm(ast, 0x1E6E02CC, phy_vref | (phy_vref << 8));
			/* Fire DFI Init */
			ddr_phy_init_2500(ast);
			ast_moutdwm(ast, 0x1E6E000C, 0x00005C01);
			अगर (cbr_test_2500(ast)) अणु
				pass++;
				data = ast_mindwm(ast, 0x1E6E03D0);
				data2 = data >> 8;
				data  = data & 0xff;
				अगर (data > data2)
					data = data2;
				अगर (max_phy_vref < data) अणु
					max_phy_vref = data;
					min_phy_vref = phy_vref;
				पूर्ण
			पूर्ण अन्यथा अगर (pass > 0)
				अवरोध;
		पूर्ण
	पूर्ण
	ast_moutdwm(ast, 0x1E6E02CC, min_phy_vref | (min_phy_vref << 8));

	/* Train DDR Vref next */
	pass = 0;

	क्रम (retrycnt = 0; retrycnt < 4 && pass == 0; retrycnt++) अणु
		min_ddr_vref = 0xFF;
		max_ddr_vref = 0x0;
		pass = 0;
		क्रम (ddr_vref = 0x00; ddr_vref < 0x40; ddr_vref++) अणु
			ast_moutdwm(ast, 0x1E6E000C, 0x00000000);
			ast_moutdwm(ast, 0x1E6E0060, 0x00000000);
			ast_moutdwm(ast, 0x1E6E02C0, 0x00000006 | (ddr_vref << 8));
			/* Fire DFI Init */
			ddr_phy_init_2500(ast);
			ast_moutdwm(ast, 0x1E6E000C, 0x00005C01);
			अगर (cbr_test_2500(ast)) अणु
				pass++;
				अगर (min_ddr_vref > ddr_vref)
					min_ddr_vref = ddr_vref;
				अगर (max_ddr_vref < ddr_vref)
					max_ddr_vref = ddr_vref;
			पूर्ण अन्यथा अगर (pass != 0)
				अवरोध;
		पूर्ण
	पूर्ण

	ast_moutdwm(ast, 0x1E6E000C, 0x00000000);
	ast_moutdwm(ast, 0x1E6E0060, 0x00000000);
	ddr_vref = (min_ddr_vref + max_ddr_vref + 1) >> 1;
	ast_moutdwm(ast, 0x1E6E02C0, 0x00000006 | (ddr_vref << 8));

	/* Wait DDR PHY init करोne */
	ddr_phy_init_2500(ast);

	ast_moutdwm(ast, 0x1E6E0120, ddr_table[REGIDX_PLL]);
	ast_moutdwm(ast, 0x1E6E000C, 0x42AA5C81);
	ast_moutdwm(ast, 0x1E6E0034, 0x0001AF93);

	check_dram_size_2500(ast, ddr_table[REGIDX_RFC]);
	enable_cache_2500(ast);
	ast_moutdwm(ast, 0x1E6E001C, 0x00000008);
	ast_moutdwm(ast, 0x1E6E0038, 0xFFFFFF00);
पूर्ण

अटल bool ast_dram_init_2500(काष्ठा ast_निजी *ast)
अणु
	u32 data;
	u32 max_tries = 5;

	करो अणु
		अगर (max_tries-- == 0)
			वापस false;
		set_mpll_2500(ast);
		reset_mmc_2500(ast);
		ddr_init_common_2500(ast);

		data = ast_mindwm(ast, 0x1E6E2070);
		अगर (data & 0x01000000)
			ddr4_init_2500(ast, ast2500_ddr4_1600_timing_table);
		अन्यथा
			ddr3_init_2500(ast, ast2500_ddr3_1600_timing_table);
	पूर्ण जबतक (!ddr_test_2500(ast));

	ast_moutdwm(ast, 0x1E6E2040, ast_mindwm(ast, 0x1E6E2040) | 0x41);

	/* Patch code */
	data = ast_mindwm(ast, 0x1E6E200C) & 0xF9FFFFFF;
	ast_moutdwm(ast, 0x1E6E200C, data | 0x10000000);

	वापस true;
पूर्ण

व्योम ast_post_chip_2500(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	u32 temp;
	u8 reg;

	reg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd0, 0xff);
	अगर ((reg & 0x80) == 0) अणु/* vga only */
		/* Clear bus lock condition */
		ast_moutdwm(ast, 0x1e600000, 0xAEED1A03);
		ast_moutdwm(ast, 0x1e600084, 0x00010000);
		ast_moutdwm(ast, 0x1e600088, 0x00000000);
		ast_moutdwm(ast, 0x1e6e2000, 0x1688A8A8);
		ast_ग_लिखो32(ast, 0xf004, 0x1e6e0000);
		ast_ग_लिखो32(ast, 0xf000, 0x1);
		ast_ग_लिखो32(ast, 0x12000, 0x1688a8a8);
		जबतक (ast_पढ़ो32(ast, 0x12000) != 0x1)
			;

		ast_ग_लिखो32(ast, 0x10000, 0xfc600309);
		जबतक (ast_पढ़ो32(ast, 0x10000) != 0x1)
			;

		/* Slow करोwn CPU/AHB CLK in VGA only mode */
		temp = ast_पढ़ो32(ast, 0x12008);
		temp |= 0x73;
		ast_ग_लिखो32(ast, 0x12008, temp);

		/* Reset USB port to patch USB unknown device issue */
		ast_moutdwm(ast, 0x1e6e2090, 0x20000000);
		temp  = ast_mindwm(ast, 0x1e6e2094);
		temp |= 0x00004000;
		ast_moutdwm(ast, 0x1e6e2094, temp);
		temp  = ast_mindwm(ast, 0x1e6e2070);
		अगर (temp & 0x00800000) अणु
			ast_moutdwm(ast, 0x1e6e207c, 0x00800000);
			mdelay(100);
			ast_moutdwm(ast, 0x1e6e2070, 0x00800000);
		पूर्ण

		अगर (!ast_dram_init_2500(ast))
			drm_err(dev, "DRAM init failed !\n");

		temp = ast_mindwm(ast, 0x1e6e2040);
		ast_moutdwm(ast, 0x1e6e2040, temp | 0x40);
	पूर्ण

	/* रुको पढ़ोy */
	करो अणु
		reg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd0, 0xff);
	पूर्ण जबतक ((reg & 0x40) == 0);
पूर्ण
