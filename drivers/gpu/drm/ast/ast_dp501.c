<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>

#समावेश "ast_drv.h"

MODULE_FIRMWARE("ast_dp501_fw.bin");

अटल व्योम ast_release_firmware(व्योम *data)
अणु
	काष्ठा ast_निजी *ast = data;

	release_firmware(ast->dp501_fw);
	ast->dp501_fw = शून्य;
पूर्ण

अटल पूर्णांक ast_load_dp501_microcode(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	पूर्णांक ret;

	ret = request_firmware(&ast->dp501_fw, "ast_dp501_fw.bin", dev->dev);
	अगर (ret)
		वापस ret;

	वापस devm_add_action_or_reset(dev->dev, ast_release_firmware, ast);
पूर्ण

अटल व्योम send_ack(काष्ठा ast_निजी *ast)
अणु
	u8 sendack;
	sendack = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x9b, 0xff);
	sendack |= 0x80;
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x9b, 0x00, sendack);
पूर्ण

अटल व्योम send_nack(काष्ठा ast_निजी *ast)
अणु
	u8 sendack;
	sendack = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x9b, 0xff);
	sendack &= ~0x80;
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x9b, 0x00, sendack);
पूर्ण

अटल bool रुको_ack(काष्ठा ast_निजी *ast)
अणु
	u8 रुकोack;
	u32 retry = 0;
	करो अणु
		रुकोack = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd2, 0xff);
		रुकोack &= 0x80;
		udelay(100);
	पूर्ण जबतक ((!रुकोack) && (retry++ < 1000));

	अगर (retry < 1000)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool रुको_nack(काष्ठा ast_निजी *ast)
अणु
	u8 रुकोack;
	u32 retry = 0;
	करो अणु
		रुकोack = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd2, 0xff);
		रुकोack &= 0x80;
		udelay(100);
	पूर्ण जबतक ((रुकोack) && (retry++ < 1000));

	अगर (retry < 1000)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम set_cmd_trigger(काष्ठा ast_निजी *ast)
अणु
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x9b, ~0x40, 0x40);
पूर्ण

अटल व्योम clear_cmd_trigger(काष्ठा ast_निजी *ast)
अणु
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x9b, ~0x40, 0x00);
पूर्ण

#अगर 0
अटल bool रुको_fw_पढ़ोy(काष्ठा ast_निजी *ast)
अणु
	u8 रुकोपढ़ोy;
	u32 retry = 0;
	करो अणु
		रुकोपढ़ोy = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd2, 0xff);
		रुकोपढ़ोy &= 0x40;
		udelay(100);
	पूर्ण जबतक ((!रुकोपढ़ोy) && (retry++ < 1000));

	अगर (retry < 1000)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण
#पूर्ण_अगर

अटल bool ast_ग_लिखो_cmd(काष्ठा drm_device *dev, u8 data)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	पूर्णांक retry = 0;
	अगर (रुको_nack(ast)) अणु
		send_nack(ast);
		ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x9a, 0x00, data);
		send_ack(ast);
		set_cmd_trigger(ast);
		करो अणु
			अगर (रुको_ack(ast)) अणु
				clear_cmd_trigger(ast);
				send_nack(ast);
				वापस true;
			पूर्ण
		पूर्ण जबतक (retry++ < 100);
	पूर्ण
	clear_cmd_trigger(ast);
	send_nack(ast);
	वापस false;
पूर्ण

अटल bool ast_ग_लिखो_data(काष्ठा drm_device *dev, u8 data)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);

	अगर (रुको_nack(ast)) अणु
		send_nack(ast);
		ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x9a, 0x00, data);
		send_ack(ast);
		अगर (रुको_ack(ast)) अणु
			send_nack(ast);
			वापस true;
		पूर्ण
	पूर्ण
	send_nack(ast);
	वापस false;
पूर्ण

#अगर 0
अटल bool ast_पढ़ो_data(काष्ठा drm_device *dev, u8 *data)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	u8 पंचांगp;

	*data = 0;

	अगर (रुको_ack(ast) == false)
		वापस false;
	पंचांगp = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd3, 0xff);
	*data = पंचांगp;
	अगर (रुको_nack(ast) == false) अणु
		send_nack(ast);
		वापस false;
	पूर्ण
	send_nack(ast);
	वापस true;
पूर्ण

अटल व्योम clear_cmd(काष्ठा ast_निजी *ast)
अणु
	send_nack(ast);
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x9a, 0x00, 0x00);
पूर्ण
#पूर्ण_अगर

व्योम ast_set_dp501_video_output(काष्ठा drm_device *dev, u8 mode)
अणु
	ast_ग_लिखो_cmd(dev, 0x40);
	ast_ग_लिखो_data(dev, mode);

	msleep(10);
पूर्ण

अटल u32 get_fw_base(काष्ठा ast_निजी *ast)
अणु
	वापस ast_mindwm(ast, 0x1e6e2104) & 0x7fffffff;
पूर्ण

bool ast_backup_fw(काष्ठा drm_device *dev, u8 *addr, u32 size)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	u32 i, data;
	u32 boot_address;

	data = ast_mindwm(ast, 0x1e6e2100) & 0x01;
	अगर (data) अणु
		boot_address = get_fw_base(ast);
		क्रम (i = 0; i < size; i += 4)
			*(u32 *)(addr + i) = ast_mindwm(ast, boot_address + i);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool ast_launch_m68k(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	u32 i, data, len = 0;
	u32 boot_address;
	u8 *fw_addr = शून्य;
	u8 jreg;

	data = ast_mindwm(ast, 0x1e6e2100) & 0x01;
	अगर (!data) अणु

		अगर (ast->dp501_fw_addr) अणु
			fw_addr = ast->dp501_fw_addr;
			len = 32*1024;
		पूर्ण अन्यथा अणु
			अगर (!ast->dp501_fw &&
			    ast_load_dp501_microcode(dev) < 0)
				वापस false;

			fw_addr = (u8 *)ast->dp501_fw->data;
			len = ast->dp501_fw->size;
		पूर्ण
		/* Get BootAddress */
		ast_moutdwm(ast, 0x1e6e2000, 0x1688a8a8);
		data = ast_mindwm(ast, 0x1e6e0004);
		चयन (data & 0x03) अणु
		हाल 0:
			boot_address = 0x44000000;
			अवरोध;
		शेष:
		हाल 1:
			boot_address = 0x48000000;
			अवरोध;
		हाल 2:
			boot_address = 0x50000000;
			अवरोध;
		हाल 3:
			boot_address = 0x60000000;
			अवरोध;
		पूर्ण
		boot_address -= 0x200000; /* -2MB */

		/* copy image to buffer */
		क्रम (i = 0; i < len; i += 4) अणु
			data = *(u32 *)(fw_addr + i);
			ast_moutdwm(ast, boot_address + i, data);
		पूर्ण

		/* Init SCU */
		ast_moutdwm(ast, 0x1e6e2000, 0x1688a8a8);

		/* Launch FW */
		ast_moutdwm(ast, 0x1e6e2104, 0x80000000 + boot_address);
		ast_moutdwm(ast, 0x1e6e2100, 1);

		/* Update Scratch */
		data = ast_mindwm(ast, 0x1e6e2040) & 0xfffff1ff;		/* D[11:9] = 100b: UEFI handling */
		data |= 0x800;
		ast_moutdwm(ast, 0x1e6e2040, data);

		jreg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0x99, 0xfc); /* D[1:0]: Reserved Video Buffer */
		jreg |= 0x02;
		ast_set_index_reg(ast, AST_IO_CRTC_PORT, 0x99, jreg);
	पूर्ण
	वापस true;
पूर्ण

u8 ast_get_dp501_max_clk(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	u32 boot_address, offset, data;
	u8 linkcap[4], linkrate, linklanes, maxclk = 0xff;

	boot_address = get_fw_base(ast);

	/* validate FW version */
	offset = 0xf000;
	data = ast_mindwm(ast, boot_address + offset);
	अगर ((data & 0xf0) != 0x10) /* version: 1x */
		वापस maxclk;

	/* Read Link Capability */
	offset  = 0xf014;
	*(u32 *)linkcap = ast_mindwm(ast, boot_address + offset);
	अगर (linkcap[2] == 0) अणु
		linkrate = linkcap[0];
		linklanes = linkcap[1];
		data = (linkrate == 0x0a) ? (90 * linklanes) : (54 * linklanes);
		अगर (data > 0xff)
			data = 0xff;
		maxclk = (u8)data;
	पूर्ण
	वापस maxclk;
पूर्ण

bool ast_dp501_पढ़ो_edid(काष्ठा drm_device *dev, u8 *ediddata)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	u32 i, boot_address, offset, data;

	boot_address = get_fw_base(ast);

	/* validate FW version */
	offset = 0xf000;
	data = ast_mindwm(ast, boot_address + offset);
	अगर ((data & 0xf0) != 0x10)
		वापस false;

	/* validate PnP Monitor */
	offset = 0xf010;
	data = ast_mindwm(ast, boot_address + offset);
	अगर (!(data & 0x01))
		वापस false;

	/* Read EDID */
	offset = 0xf020;
	क्रम (i = 0; i < 128; i += 4) अणु
		data = ast_mindwm(ast, boot_address + offset + i);
		*(u32 *)(ediddata + i) = data;
	पूर्ण

	वापस true;
पूर्ण

अटल bool ast_init_dvo(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	u8 jreg;
	u32 data;
	ast_ग_लिखो32(ast, 0xf004, 0x1e6e0000);
	ast_ग_लिखो32(ast, 0xf000, 0x1);
	ast_ग_लिखो32(ast, 0x12000, 0x1688a8a8);

	jreg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd0, 0xff);
	अगर (!(jreg & 0x80)) अणु
		/* Init SCU DVO Settings */
		data = ast_पढ़ो32(ast, 0x12008);
		/* delay phase */
		data &= 0xfffff8ff;
		data |= 0x00000500;
		ast_ग_लिखो32(ast, 0x12008, data);

		अगर (ast->chip == AST2300) अणु
			data = ast_पढ़ो32(ast, 0x12084);
			/* multi-pins क्रम DVO single-edge */
			data |= 0xfffe0000;
			ast_ग_लिखो32(ast, 0x12084, data);

			data = ast_पढ़ो32(ast, 0x12088);
			/* multi-pins क्रम DVO single-edge */
			data |= 0x000fffff;
			ast_ग_लिखो32(ast, 0x12088, data);

			data = ast_पढ़ो32(ast, 0x12090);
			/* multi-pins क्रम DVO single-edge */
			data &= 0xffffffcf;
			data |= 0x00000020;
			ast_ग_लिखो32(ast, 0x12090, data);
		पूर्ण अन्यथा अणु /* AST2400 */
			data = ast_पढ़ो32(ast, 0x12088);
			/* multi-pins क्रम DVO single-edge */
			data |= 0x30000000;
			ast_ग_लिखो32(ast, 0x12088, data);

			data = ast_पढ़ो32(ast, 0x1208c);
			/* multi-pins क्रम DVO single-edge */
			data |= 0x000000cf;
			ast_ग_लिखो32(ast, 0x1208c, data);

			data = ast_पढ़ो32(ast, 0x120a4);
			/* multi-pins क्रम DVO single-edge */
			data |= 0xffff0000;
			ast_ग_लिखो32(ast, 0x120a4, data);

			data = ast_पढ़ो32(ast, 0x120a8);
			/* multi-pins क्रम DVO single-edge */
			data |= 0x0000000f;
			ast_ग_लिखो32(ast, 0x120a8, data);

			data = ast_पढ़ो32(ast, 0x12094);
			/* multi-pins क्रम DVO single-edge */
			data |= 0x00000002;
			ast_ग_लिखो32(ast, 0x12094, data);
		पूर्ण
	पूर्ण

	/* Force to DVO */
	data = ast_पढ़ो32(ast, 0x1202c);
	data &= 0xfffbffff;
	ast_ग_लिखो32(ast, 0x1202c, data);

	/* Init VGA DVO Settings */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa3, 0xcf, 0x80);
	वापस true;
पूर्ण


अटल व्योम ast_init_analog(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	u32 data;

	/*
	 * Set DAC source to VGA mode in SCU2C via the P2A
	 * bridge. First configure the P2U to target the SCU
	 * in हाल it isn't at this stage.
	 */
	ast_ग_लिखो32(ast, 0xf004, 0x1e6e0000);
	ast_ग_लिखो32(ast, 0xf000, 0x1);

	/* Then unlock the SCU with the magic password */
	ast_ग_लिखो32(ast, 0x12000, 0x1688a8a8);
	ast_ग_लिखो32(ast, 0x12000, 0x1688a8a8);
	ast_ग_लिखो32(ast, 0x12000, 0x1688a8a8);

	/* Finally, clear bits [17:16] of SCU2c */
	data = ast_पढ़ो32(ast, 0x1202c);
	data &= 0xfffcffff;
	ast_ग_लिखो32(ast, 0, data);

	/* Disable DVO */
	ast_set_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xa3, 0xcf, 0x00);
पूर्ण

व्योम ast_init_3rdtx(काष्ठा drm_device *dev)
अणु
	काष्ठा ast_निजी *ast = to_ast_निजी(dev);
	u8 jreg;

	अगर (ast->chip == AST2300 || ast->chip == AST2400) अणु
		jreg = ast_get_index_reg_mask(ast, AST_IO_CRTC_PORT, 0xd1, 0xff);
		चयन (jreg & 0x0e) अणु
		हाल 0x04:
			ast_init_dvo(dev);
			अवरोध;
		हाल 0x08:
			ast_launch_m68k(dev);
			अवरोध;
		हाल 0x0c:
			ast_init_dvo(dev);
			अवरोध;
		शेष:
			अगर (ast->tx_chip_type == AST_TX_SIL164)
				ast_init_dvo(dev);
			अन्यथा
				ast_init_analog(dev);
		पूर्ण
	पूर्ण
पूर्ण
