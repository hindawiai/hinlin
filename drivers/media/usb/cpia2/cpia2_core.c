<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/****************************************************************************
 *
 *  Filename: cpia2_core.c
 *
 *  Copyright 2001, STMicrolectronics, Inc.
 *      Contact:  steve.miller@st.com
 *
 *  Description:
 *     This is a USB driver क्रम CPia2 based video cameras.
 *     The infraकाष्ठाure of this driver is based on the cpia usb driver by
 *     Jochen Sअक्षरrlach and Johannes Erdfeldt.
 *
 *  Stripped of 2.4 stuff पढ़ोy क्रम मुख्य kernel submit by
 *		Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 ****************************************************************************/

#समावेश "cpia2.h"

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/firmware.h>
#समावेश <linux/sched/संकेत.स>

#घोषणा FIRMWARE "cpia2/stv0672_vp4.bin"
MODULE_FIRMWARE(FIRMWARE);

/* #घोषणा _CPIA2_DEBUG_ */

#अगर_घोषित _CPIA2_DEBUG_

अटल स्थिर अक्षर *block_name[] = अणु
	"System",
	"VC",
	"VP",
	"IDATA"
पूर्ण;
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक debugs_on;	/* शेष 0 - DEBUG_REG */


/******************************************************************************
 *
 *  Forward Declarations
 *
 *****************************************************************************/
अटल पूर्णांक apply_vp_patch(काष्ठा camera_data *cam);
अटल पूर्णांक set_शेष_user_mode(काष्ठा camera_data *cam);
अटल पूर्णांक set_vw_size(काष्ठा camera_data *cam, पूर्णांक size);
अटल पूर्णांक configure_sensor(काष्ठा camera_data *cam,
			    पूर्णांक reqwidth, पूर्णांक reqheight);
अटल पूर्णांक config_sensor_410(काष्ठा camera_data *cam,
			    पूर्णांक reqwidth, पूर्णांक reqheight);
अटल पूर्णांक config_sensor_500(काष्ठा camera_data *cam,
			    पूर्णांक reqwidth, पूर्णांक reqheight);
अटल पूर्णांक set_all_properties(काष्ठा camera_data *cam);
अटल व्योम wake_प्रणाली(काष्ठा camera_data *cam);
अटल व्योम set_lowlight_boost(काष्ठा camera_data *cam);
अटल व्योम reset_camera_काष्ठा(काष्ठा camera_data *cam);
अटल पूर्णांक cpia2_set_high_घातer(काष्ठा camera_data *cam);

/* Here we want the physical address of the memory.
 * This is used when initializing the contents of the
 * area and marking the pages as reserved.
 */
अटल अंतरभूत अचिन्हित दीर्घ kvirt_to_pa(अचिन्हित दीर्घ adr)
अणु
	अचिन्हित दीर्घ kva, ret;

	kva = (अचिन्हित दीर्घ) page_address(vदो_स्मृति_to_page((व्योम *)adr));
	kva |= adr & (PAGE_SIZE-1); /* restore the offset */
	ret = __pa(kva);
	वापस ret;
पूर्ण

अटल व्योम *rvदो_स्मृति(अचिन्हित दीर्घ size)
अणु
	व्योम *mem;
	अचिन्हित दीर्घ adr;

	/* Round it off to PAGE_SIZE */
	size = PAGE_ALIGN(size);

	mem = vदो_स्मृति_32(size);
	अगर (!mem)
		वापस शून्य;

	स_रखो(mem, 0, size);	/* Clear the ram out, no junk to the user */
	adr = (अचिन्हित दीर्घ) mem;

	जबतक ((दीर्घ)size > 0) अणु
		SetPageReserved(vदो_स्मृति_to_page((व्योम *)adr));
		adr += PAGE_SIZE;
		size -= PAGE_SIZE;
	पूर्ण
	वापस mem;
पूर्ण

अटल व्योम rvमुक्त(व्योम *mem, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ adr;

	अगर (!mem)
		वापस;

	size = PAGE_ALIGN(size);

	adr = (अचिन्हित दीर्घ) mem;
	जबतक ((दीर्घ)size > 0) अणु
		ClearPageReserved(vदो_स्मृति_to_page((व्योम *)adr));
		adr += PAGE_SIZE;
		size -= PAGE_SIZE;
	पूर्ण
	vमुक्त(mem);
पूर्ण

/******************************************************************************
 *
 *  cpia2_करो_command
 *
 *  Send an arbitrary command to the camera.  For commands that पढ़ो from
 *  the camera, copy the buffers पूर्णांकo the proper param काष्ठाures.
 *****************************************************************************/
पूर्णांक cpia2_करो_command(काष्ठा camera_data *cam,
		     u32 command, u8 direction, u8 param)
अणु
	पूर्णांक retval = 0;
	काष्ठा cpia2_command cmd;
	अचिन्हित पूर्णांक device = cam->params.pnp_id.device_type;

	cmd.command = command;
	cmd.reg_count = 2;	/* शेष */
	cmd.direction = direction;

	/***
	 * Set up the command.
	 ***/
	चयन (command) अणु
	हाल CPIA2_CMD_GET_VERSION:
		cmd.req_mode =
		    CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_SYSTEM;
		cmd.start = CPIA2_SYSTEM_DEVICE_HI;
		अवरोध;
	हाल CPIA2_CMD_GET_PNP_ID:
		cmd.req_mode =
		    CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_SYSTEM;
		cmd.reg_count = 8;
		cmd.start = CPIA2_SYSTEM_DESCRIP_VID_HI;
		अवरोध;
	हाल CPIA2_CMD_GET_ASIC_TYPE:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VC;
		cmd.start = CPIA2_VC_ASIC_ID;
		अवरोध;
	हाल CPIA2_CMD_GET_SENSOR:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.start = CPIA2_VP_SENSOR_FLAGS;
		अवरोध;
	हाल CPIA2_CMD_GET_VP_DEVICE:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.start = CPIA2_VP_DEVICEH;
		अवरोध;
	हाल CPIA2_CMD_SET_VP_BRIGHTNESS:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_VP_BRIGHTNESS:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		अगर (device == DEVICE_STV_672)
			cmd.start = CPIA2_VP4_EXPOSURE_TARGET;
		अन्यथा
			cmd.start = CPIA2_VP5_EXPOSURE_TARGET;
		अवरोध;
	हाल CPIA2_CMD_SET_CONTRAST:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_CONTRAST:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VP_YRANGE;
		अवरोध;
	हाल CPIA2_CMD_SET_VP_SATURATION:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_VP_SATURATION:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		अगर (device == DEVICE_STV_672)
			cmd.start = CPIA2_VP_SATURATION;
		अन्यथा
			cmd.start = CPIA2_VP5_MCUVSATURATION;
		अवरोध;
	हाल CPIA2_CMD_SET_VP_GPIO_DATA:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_VP_GPIO_DATA:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VP_GPIO_DATA;
		अवरोध;
	हाल CPIA2_CMD_SET_VP_GPIO_सूचीECTION:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_VP_GPIO_सूचीECTION:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VP_GPIO_सूचीECTION;
		अवरोध;
	हाल CPIA2_CMD_SET_VC_MP_GPIO_DATA:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_VC_MP_GPIO_DATA:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VC;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VC_MP_DATA;
		अवरोध;
	हाल CPIA2_CMD_SET_VC_MP_GPIO_सूचीECTION:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_VC_MP_GPIO_सूचीECTION:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VC;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VC_MP_सूची;
		अवरोध;
	हाल CPIA2_CMD_ENABLE_PACKET_CTRL:
		cmd.req_mode =
		    CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_SYSTEM;
		cmd.start = CPIA2_SYSTEM_INT_PACKET_CTRL;
		cmd.reg_count = 1;
		cmd.buffer.block_data[0] = param;
		अवरोध;
	हाल CPIA2_CMD_SET_FLICKER_MODES:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_FLICKER_MODES:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VP_FLICKER_MODES;
		अवरोध;
	हाल CPIA2_CMD_RESET_FIFO:	/* clear fअगरo and enable stream block */
		cmd.req_mode = CAMERAACCESS_TYPE_RANDOM | CAMERAACCESS_VC;
		cmd.reg_count = 2;
		cmd.start = 0;
		cmd.buffer.रेजिस्टरs[0].index = CPIA2_VC_ST_CTRL;
		cmd.buffer.रेजिस्टरs[0].value = CPIA2_VC_ST_CTRL_SRC_VC |
		    CPIA2_VC_ST_CTRL_DST_USB | CPIA2_VC_ST_CTRL_खातापूर्ण_DETECT;
		cmd.buffer.रेजिस्टरs[1].index = CPIA2_VC_ST_CTRL;
		cmd.buffer.रेजिस्टरs[1].value = CPIA2_VC_ST_CTRL_SRC_VC |
		    CPIA2_VC_ST_CTRL_DST_USB |
		    CPIA2_VC_ST_CTRL_खातापूर्ण_DETECT |
		    CPIA2_VC_ST_CTRL_FIFO_ENABLE;
		अवरोध;
	हाल CPIA2_CMD_SET_HI_POWER:
		cmd.req_mode =
		    CAMERAACCESS_TYPE_RANDOM | CAMERAACCESS_SYSTEM;
		cmd.reg_count = 2;
		cmd.buffer.रेजिस्टरs[0].index =
		    CPIA2_SYSTEM_SYSTEM_CONTROL;
		cmd.buffer.रेजिस्टरs[1].index =
		    CPIA2_SYSTEM_SYSTEM_CONTROL;
		cmd.buffer.रेजिस्टरs[0].value = CPIA2_SYSTEM_CONTROL_CLEAR_ERR;
		cmd.buffer.रेजिस्टरs[1].value =
		    CPIA2_SYSTEM_CONTROL_HIGH_POWER;
		अवरोध;
	हाल CPIA2_CMD_SET_LOW_POWER:
		cmd.req_mode =
		    CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_SYSTEM;
		cmd.reg_count = 1;
		cmd.start = CPIA2_SYSTEM_SYSTEM_CONTROL;
		cmd.buffer.block_data[0] = 0;
		अवरोध;
	हाल CPIA2_CMD_CLEAR_V2W_ERR:
		cmd.req_mode =
		    CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_SYSTEM;
		cmd.reg_count = 1;
		cmd.start = CPIA2_SYSTEM_SYSTEM_CONTROL;
		cmd.buffer.block_data[0] = CPIA2_SYSTEM_CONTROL_CLEAR_ERR;
		अवरोध;
	हाल CPIA2_CMD_SET_USER_MODE:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_USER_MODE:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		अगर (device == DEVICE_STV_672)
			cmd.start = CPIA2_VP4_USER_MODE;
		अन्यथा
			cmd.start = CPIA2_VP5_USER_MODE;
		अवरोध;
	हाल CPIA2_CMD_FRAMERATE_REQ:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		अगर (device == DEVICE_STV_672)
			cmd.start = CPIA2_VP4_FRAMERATE_REQUEST;
		अन्यथा
			cmd.start = CPIA2_VP5_FRAMERATE_REQUEST;
		cmd.buffer.block_data[0] = param;
		अवरोध;
	हाल CPIA2_CMD_SET_WAKEUP:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_WAKEUP:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VC;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VC_WAKEUP;
		अवरोध;
	हाल CPIA2_CMD_SET_PW_CONTROL:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_PW_CONTROL:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VC;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VC_PW_CTRL;
		अवरोध;
	हाल CPIA2_CMD_GET_VP_SYSTEM_STATE:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VP_SYSTEMSTATE;
		अवरोध;
	हाल CPIA2_CMD_SET_SYSTEM_CTRL:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_SYSTEM_CTRL:
		cmd.req_mode =
		    CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_SYSTEM;
		cmd.reg_count = 1;
		cmd.start = CPIA2_SYSTEM_SYSTEM_CONTROL;
		अवरोध;
	हाल CPIA2_CMD_SET_VP_SYSTEM_CTRL:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_VP_SYSTEM_CTRL:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VP_SYSTEMCTRL;
		अवरोध;
	हाल CPIA2_CMD_SET_VP_EXP_MODES:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_VP_EXP_MODES:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VP_EXPOSURE_MODES;
		अवरोध;
	हाल CPIA2_CMD_SET_DEVICE_CONFIG:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_DEVICE_CONFIG:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VP_DEVICE_CONFIG;
		अवरोध;
	हाल CPIA2_CMD_SET_SERIAL_ADDR:
		cmd.buffer.block_data[0] = param;
		cmd.req_mode =
		    CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_SYSTEM;
		cmd.reg_count = 1;
		cmd.start = CPIA2_SYSTEM_VP_SERIAL_ADDR;
		अवरोध;
	हाल CPIA2_CMD_SET_SENSOR_CR1:
		cmd.buffer.block_data[0] = param;
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		cmd.start = CPIA2_SENSOR_CR1;
		अवरोध;
	हाल CPIA2_CMD_SET_VC_CONTROL:
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_VC_CONTROL:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VC;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VC_VC_CTRL;
		अवरोध;
	हाल CPIA2_CMD_SET_TARGET_KB:
		cmd.req_mode = CAMERAACCESS_TYPE_RANDOM | CAMERAACCESS_VC;
		cmd.reg_count = 1;
		cmd.buffer.रेजिस्टरs[0].index = CPIA2_VC_VC_TARGET_KB;
		cmd.buffer.रेजिस्टरs[0].value = param;
		अवरोध;
	हाल CPIA2_CMD_SET_DEF_JPEG_OPT:
		cmd.req_mode = CAMERAACCESS_TYPE_RANDOM | CAMERAACCESS_VC;
		cmd.reg_count = 4;
		cmd.buffer.रेजिस्टरs[0].index = CPIA2_VC_VC_JPEG_OPT;
		cmd.buffer.रेजिस्टरs[0].value =
		    CPIA2_VC_VC_JPEG_OPT_DOUBLE_SQUEEZE;
		cmd.buffer.रेजिस्टरs[1].index = CPIA2_VC_VC_USER_SQUEEZE;
		cmd.buffer.रेजिस्टरs[1].value = 20;
		cmd.buffer.रेजिस्टरs[2].index = CPIA2_VC_VC_CREEP_PERIOD;
		cmd.buffer.रेजिस्टरs[2].value = 2;
		cmd.buffer.रेजिस्टरs[3].index = CPIA2_VC_VC_JPEG_OPT;
		cmd.buffer.रेजिस्टरs[3].value = CPIA2_VC_VC_JPEG_OPT_DEFAULT;
		अवरोध;
	हाल CPIA2_CMD_REHASH_VP4:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		cmd.start = CPIA2_VP_REHASH_VALUES;
		cmd.buffer.block_data[0] = param;
		अवरोध;
	हाल CPIA2_CMD_SET_USER_EFFECTS:  /* Note: Be careful with this as
					     this रेजिस्टर can also affect
					     flicker modes */
		cmd.buffer.block_data[0] = param;
		fallthrough;
	हाल CPIA2_CMD_GET_USER_EFFECTS:
		cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
		cmd.reg_count = 1;
		अगर (device == DEVICE_STV_672)
			cmd.start = CPIA2_VP4_USER_EFFECTS;
		अन्यथा
			cmd.start = CPIA2_VP5_USER_EFFECTS;
		अवरोध;
	शेष:
		LOG("DoCommand received invalid command\n");
		वापस -EINVAL;
	पूर्ण

	retval = cpia2_send_command(cam, &cmd);
	अगर (retval) अणु
		वापस retval;
	पूर्ण

	/***
	 * Now copy any results from a पढ़ो पूर्णांकo the appropriate param काष्ठा.
	 ***/
	चयन (command) अणु
	हाल CPIA2_CMD_GET_VERSION:
		cam->params.version.firmware_revision_hi =
		    cmd.buffer.block_data[0];
		cam->params.version.firmware_revision_lo =
		    cmd.buffer.block_data[1];
		अवरोध;
	हाल CPIA2_CMD_GET_PNP_ID:
		cam->params.pnp_id.venकरोr = (cmd.buffer.block_data[0] << 8) |
					    cmd.buffer.block_data[1];
		cam->params.pnp_id.product = (cmd.buffer.block_data[2] << 8) |
					     cmd.buffer.block_data[3];
		cam->params.pnp_id.device_revision =
			(cmd.buffer.block_data[4] << 8) |
			cmd.buffer.block_data[5];
		अगर (cam->params.pnp_id.venकरोr == 0x553) अणु
			अगर (cam->params.pnp_id.product == 0x100) अणु
				cam->params.pnp_id.device_type = DEVICE_STV_672;
			पूर्ण अन्यथा अगर (cam->params.pnp_id.product == 0x140 ||
				   cam->params.pnp_id.product == 0x151) अणु
				cam->params.pnp_id.device_type = DEVICE_STV_676;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल CPIA2_CMD_GET_ASIC_TYPE:
		cam->params.version.asic_id = cmd.buffer.block_data[0];
		cam->params.version.asic_rev = cmd.buffer.block_data[1];
		अवरोध;
	हाल CPIA2_CMD_GET_SENSOR:
		cam->params.version.sensor_flags = cmd.buffer.block_data[0];
		cam->params.version.sensor_rev = cmd.buffer.block_data[1];
		अवरोध;
	हाल CPIA2_CMD_GET_VP_DEVICE:
		cam->params.version.vp_device_hi = cmd.buffer.block_data[0];
		cam->params.version.vp_device_lo = cmd.buffer.block_data[1];
		अवरोध;
	हाल CPIA2_CMD_GET_VP_GPIO_DATA:
		cam->params.vp_params.gpio_data = cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_VP_GPIO_सूचीECTION:
		cam->params.vp_params.gpio_direction = cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_VC_MP_GPIO_सूचीECTION:
		cam->params.vc_params.vc_mp_direction =cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_VC_MP_GPIO_DATA:
		cam->params.vc_params.vc_mp_data = cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_FLICKER_MODES:
		cam->params.flicker_control.cam_रेजिस्टर =
			cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_WAKEUP:
		cam->params.vc_params.wakeup = cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_PW_CONTROL:
		cam->params.vc_params.pw_control = cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_SYSTEM_CTRL:
		cam->params.camera_state.प्रणाली_ctrl = cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_VP_SYSTEM_STATE:
		cam->params.vp_params.प्रणाली_state = cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_VP_SYSTEM_CTRL:
		cam->params.vp_params.प्रणाली_ctrl = cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_VP_EXP_MODES:
		cam->params.vp_params.exposure_modes = cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_DEVICE_CONFIG:
		cam->params.vp_params.device_config = cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_VC_CONTROL:
		cam->params.vc_params.vc_control = cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_USER_MODE:
		cam->params.vp_params.video_mode = cmd.buffer.block_data[0];
		अवरोध;
	हाल CPIA2_CMD_GET_USER_EFFECTS:
		cam->params.vp_params.user_effects = cmd.buffer.block_data[0];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस retval;
पूर्ण

/******************************************************************************
 *
 *  cpia2_send_command
 *
 *****************************************************************************/

#घोषणा सूची(cmd) ((cmd->direction == TRANSFER_WRITE) ? "Write" : "Read")
#घोषणा BINDEX(cmd) (cmd->req_mode & 0x03)

पूर्णांक cpia2_send_command(काष्ठा camera_data *cam, काष्ठा cpia2_command *cmd)
अणु
	u8 count;
	u8 start;
	u8 *buffer;
	पूर्णांक retval;

	चयन (cmd->req_mode & 0x0c) अणु
	हाल CAMERAACCESS_TYPE_RANDOM:
		count = cmd->reg_count * माप(काष्ठा cpia2_रेजिस्टर);
		start = 0;
		buffer = (u8 *) & cmd->buffer;
		अगर (debugs_on & DEBUG_REG)
			DBG("%s Random: Register block %s\n", सूची(cmd),
			    block_name[BINDEX(cmd)]);
		अवरोध;
	हाल CAMERAACCESS_TYPE_BLOCK:
		count = cmd->reg_count;
		start = cmd->start;
		buffer = cmd->buffer.block_data;
		अगर (debugs_on & DEBUG_REG)
			DBG("%s Block: Register block %s\n", सूची(cmd),
			    block_name[BINDEX(cmd)]);
		अवरोध;
	हाल CAMERAACCESS_TYPE_MASK:
		count = cmd->reg_count * माप(काष्ठा cpia2_reg_mask);
		start = 0;
		buffer = (u8 *) & cmd->buffer;
		अगर (debugs_on & DEBUG_REG)
			DBG("%s Mask: Register block %s\n", सूची(cmd),
			    block_name[BINDEX(cmd)]);
		अवरोध;
	हाल CAMERAACCESS_TYPE_REPEAT:	/* For patch blocks only */
		count = cmd->reg_count;
		start = cmd->start;
		buffer = cmd->buffer.block_data;
		अगर (debugs_on & DEBUG_REG)
			DBG("%s Repeat: Register block %s\n", सूची(cmd),
			    block_name[BINDEX(cmd)]);
		अवरोध;
	शेष:
		LOG("%s: invalid request mode\n",__func__);
		वापस -EINVAL;
	पूर्ण

	retval = cpia2_usb_transfer_cmd(cam,
					buffer,
					cmd->req_mode,
					start, count, cmd->direction);
#अगर_घोषित _CPIA2_DEBUG_
	अगर (debugs_on & DEBUG_REG) अणु
		पूर्णांक i;
		क्रम (i = 0; i < cmd->reg_count; i++) अणु
			अगर((cmd->req_mode & 0x0c) == CAMERAACCESS_TYPE_BLOCK)
				KINFO("%s Block: [0x%02X] = 0x%02X\n",
				    सूची(cmd), start + i, buffer[i]);
			अगर((cmd->req_mode & 0x0c) == CAMERAACCESS_TYPE_RANDOM)
				KINFO("%s Random: [0x%02X] = 0x%02X\n",
				    सूची(cmd), cmd->buffer.रेजिस्टरs[i].index,
				    cmd->buffer.रेजिस्टरs[i].value);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस retval;
पूर्ण;

/*************
 * Functions to implement camera functionality
 *************/
/******************************************************************************
 *
 *  cpia2_get_version_info
 *
 *****************************************************************************/
अटल व्योम cpia2_get_version_info(काष्ठा camera_data *cam)
अणु
	cpia2_करो_command(cam, CPIA2_CMD_GET_VERSION, TRANSFER_READ, 0);
	cpia2_करो_command(cam, CPIA2_CMD_GET_PNP_ID, TRANSFER_READ, 0);
	cpia2_करो_command(cam, CPIA2_CMD_GET_ASIC_TYPE, TRANSFER_READ, 0);
	cpia2_करो_command(cam, CPIA2_CMD_GET_SENSOR, TRANSFER_READ, 0);
	cpia2_करो_command(cam, CPIA2_CMD_GET_VP_DEVICE, TRANSFER_READ, 0);
पूर्ण

/******************************************************************************
 *
 *  cpia2_reset_camera
 *
 *  Called at least during the खोलो process, sets up initial params.
 *****************************************************************************/
पूर्णांक cpia2_reset_camera(काष्ठा camera_data *cam)
अणु
	u8 पंचांगp_reg;
	पूर्णांक retval = 0;
	पूर्णांक target_kb;
	पूर्णांक i;
	काष्ठा cpia2_command cmd;

	/***
	 * VC setup
	 ***/
	retval = configure_sensor(cam,
				  cam->params.roi.width,
				  cam->params.roi.height);
	अगर (retval < 0) अणु
		ERR("Couldn't configure sensor, error=%d\n", retval);
		वापस retval;
	पूर्ण

	/* Clear FIFO and route/enable stream block */
	cmd.req_mode = CAMERAACCESS_TYPE_RANDOM | CAMERAACCESS_VC;
	cmd.direction = TRANSFER_WRITE;
	cmd.reg_count = 2;
	cmd.buffer.रेजिस्टरs[0].index = CPIA2_VC_ST_CTRL;
	cmd.buffer.रेजिस्टरs[0].value = CPIA2_VC_ST_CTRL_SRC_VC |
		CPIA2_VC_ST_CTRL_DST_USB | CPIA2_VC_ST_CTRL_खातापूर्ण_DETECT;
	cmd.buffer.रेजिस्टरs[1].index = CPIA2_VC_ST_CTRL;
	cmd.buffer.रेजिस्टरs[1].value = CPIA2_VC_ST_CTRL_SRC_VC |
		CPIA2_VC_ST_CTRL_DST_USB |
		CPIA2_VC_ST_CTRL_खातापूर्ण_DETECT | CPIA2_VC_ST_CTRL_FIFO_ENABLE;

	cpia2_send_command(cam, &cmd);

	cpia2_set_high_घातer(cam);

	अगर (cam->params.pnp_id.device_type == DEVICE_STV_672) अणु
		/* Enable button notअगरication */
		cmd.req_mode = CAMERAACCESS_TYPE_RANDOM | CAMERAACCESS_SYSTEM;
		cmd.buffer.रेजिस्टरs[0].index = CPIA2_SYSTEM_INT_PACKET_CTRL;
		cmd.buffer.रेजिस्टरs[0].value =
			CPIA2_SYSTEM_INT_PACKET_CTRL_ENABLE_SW_XX;
		cmd.reg_count = 1;
		cpia2_send_command(cam, &cmd);
	पूर्ण

	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(100));

	अगर (cam->params.pnp_id.device_type == DEVICE_STV_672)
		retval = apply_vp_patch(cam);

	/* रुको क्रम vp to go to sleep */
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(100));

	/***
	 * If this is a 676, apply VP5 fixes beक्रमe we start streaming
	 ***/
	अगर (cam->params.pnp_id.device_type == DEVICE_STV_676) अणु
		cmd.req_mode = CAMERAACCESS_TYPE_RANDOM | CAMERAACCESS_VP;

		/* The following ग_लिखोs improve the picture */
		cmd.buffer.रेजिस्टरs[0].index = CPIA2_VP5_MYBLACK_LEVEL;
		cmd.buffer.रेजिस्टरs[0].value = 0; /* reduce from the शेष
						    * rec 601 pedestal of 16 */
		cmd.buffer.रेजिस्टरs[1].index = CPIA2_VP5_MCYRANGE;
		cmd.buffer.रेजिस्टरs[1].value = 0x92; /* increase from 100% to
						       * (256/256 - 31) to fill
						       * available range */
		cmd.buffer.रेजिस्टरs[2].index = CPIA2_VP5_MYCEILING;
		cmd.buffer.रेजिस्टरs[2].value = 0xFF; /* Increase from the
						       * शेष rec 601 उच्चमानing
						       * of 240 */
		cmd.buffer.रेजिस्टरs[3].index = CPIA2_VP5_MCUVSATURATION;
		cmd.buffer.रेजिस्टरs[3].value = 0xFF; /* Increase from the rec
						       * 601 100% level (128)
						       * to 145-192 */
		cmd.buffer.रेजिस्टरs[4].index = CPIA2_VP5_ANTIFLKRSETUP;
		cmd.buffer.रेजिस्टरs[4].value = 0x80;  /* Inhibit the
							* anti-flicker */

		/* The following 4 ग_लिखोs are a fix to allow QVGA to work at 30 fps */
		cmd.buffer.रेजिस्टरs[5].index = CPIA2_VP_RAM_ADDR_H;
		cmd.buffer.रेजिस्टरs[5].value = 0x01;
		cmd.buffer.रेजिस्टरs[6].index = CPIA2_VP_RAM_ADDR_L;
		cmd.buffer.रेजिस्टरs[6].value = 0xE3;
		cmd.buffer.रेजिस्टरs[7].index = CPIA2_VP_RAM_DATA;
		cmd.buffer.रेजिस्टरs[7].value = 0x02;
		cmd.buffer.रेजिस्टरs[8].index = CPIA2_VP_RAM_DATA;
		cmd.buffer.रेजिस्टरs[8].value = 0xFC;

		cmd.direction = TRANSFER_WRITE;
		cmd.reg_count = 9;

		cpia2_send_command(cam, &cmd);
	पूर्ण

	/* Activate all settings and start the data stream */
	/* Set user mode */
	set_शेष_user_mode(cam);

	/* Give VP समय to wake up */
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(100));

	set_all_properties(cam);

	cpia2_करो_command(cam, CPIA2_CMD_GET_USER_MODE, TRANSFER_READ, 0);
	DBG("After SetAllProperties(cam), user mode is 0x%0X\n",
	    cam->params.vp_params.video_mode);

	/***
	 * Set audio regulator off.  This and the code to set the compresison
	 * state are too complex to क्रमm a CPIA2_CMD_, and seem to be somewhat
	 * पूर्णांकertwined.  This stuff came straight from the winकरोws driver.
	 ***/
	/* Turn AutoExposure off in VP and enable the serial bridge to the sensor */
	cpia2_करो_command(cam, CPIA2_CMD_GET_VP_SYSTEM_CTRL, TRANSFER_READ, 0);
	पंचांगp_reg = cam->params.vp_params.प्रणाली_ctrl;
	cmd.buffer.रेजिस्टरs[0].value = पंचांगp_reg &
		(पंचांगp_reg & (CPIA2_VP_SYSTEMCTRL_HK_CONTROL ^ 0xFF));

	cpia2_करो_command(cam, CPIA2_CMD_GET_DEVICE_CONFIG, TRANSFER_READ, 0);
	cmd.buffer.रेजिस्टरs[1].value = cam->params.vp_params.device_config |
					CPIA2_VP_DEVICE_CONFIG_SERIAL_BRIDGE;
	cmd.buffer.रेजिस्टरs[0].index = CPIA2_VP_SYSTEMCTRL;
	cmd.buffer.रेजिस्टरs[1].index = CPIA2_VP_DEVICE_CONFIG;
	cmd.req_mode = CAMERAACCESS_TYPE_RANDOM | CAMERAACCESS_VP;
	cmd.reg_count = 2;
	cmd.direction = TRANSFER_WRITE;
	cmd.start = 0;
	cpia2_send_command(cam, &cmd);

	/* Set the correct I2C address in the CPiA-2 प्रणाली रेजिस्टर */
	cpia2_करो_command(cam,
			 CPIA2_CMD_SET_SERIAL_ADDR,
			 TRANSFER_WRITE,
			 CPIA2_SYSTEM_VP_SERIAL_ADDR_SENSOR);

	/* Now have sensor access - set bit to turn the audio regulator off */
	cpia2_करो_command(cam,
			 CPIA2_CMD_SET_SENSOR_CR1,
			 TRANSFER_WRITE, CPIA2_SENSOR_CR1_DOWN_AUDIO_REGULATOR);

	/* Set the correct I2C address in the CPiA-2 प्रणाली रेजिस्टर */
	अगर (cam->params.pnp_id.device_type == DEVICE_STV_672)
		cpia2_करो_command(cam,
				 CPIA2_CMD_SET_SERIAL_ADDR,
				 TRANSFER_WRITE,
				 CPIA2_SYSTEM_VP_SERIAL_ADDR_VP); // 0x88
	अन्यथा
		cpia2_करो_command(cam,
				 CPIA2_CMD_SET_SERIAL_ADDR,
				 TRANSFER_WRITE,
				 CPIA2_SYSTEM_VP_SERIAL_ADDR_676_VP); // 0x8a

	/* increase संकेत drive strength */
	अगर (cam->params.pnp_id.device_type == DEVICE_STV_676)
		cpia2_करो_command(cam,
				 CPIA2_CMD_SET_VP_EXP_MODES,
				 TRANSFER_WRITE,
				 CPIA2_VP_EXPOSURE_MODES_COMPILE_EXP);

	/* Start स्वतःexposure */
	cpia2_करो_command(cam, CPIA2_CMD_GET_DEVICE_CONFIG, TRANSFER_READ, 0);
	cmd.buffer.रेजिस्टरs[0].value = cam->params.vp_params.device_config &
				  (CPIA2_VP_DEVICE_CONFIG_SERIAL_BRIDGE ^ 0xFF);

	cpia2_करो_command(cam, CPIA2_CMD_GET_VP_SYSTEM_CTRL, TRANSFER_READ, 0);
	cmd.buffer.रेजिस्टरs[1].value =
	    cam->params.vp_params.प्रणाली_ctrl | CPIA2_VP_SYSTEMCTRL_HK_CONTROL;

	cmd.buffer.रेजिस्टरs[0].index = CPIA2_VP_DEVICE_CONFIG;
	cmd.buffer.रेजिस्टरs[1].index = CPIA2_VP_SYSTEMCTRL;
	cmd.req_mode = CAMERAACCESS_TYPE_RANDOM | CAMERAACCESS_VP;
	cmd.reg_count = 2;
	cmd.direction = TRANSFER_WRITE;

	cpia2_send_command(cam, &cmd);

	/* Set compression state */
	cpia2_करो_command(cam, CPIA2_CMD_GET_VC_CONTROL, TRANSFER_READ, 0);
	अगर (cam->params.compression.inhibit_htables) अणु
		पंचांगp_reg = cam->params.vc_params.vc_control |
			  CPIA2_VC_VC_CTRL_INHIBIT_H_TABLES;
	पूर्ण अन्यथा  अणु
		पंचांगp_reg = cam->params.vc_params.vc_control &
			  ~CPIA2_VC_VC_CTRL_INHIBIT_H_TABLES;
	पूर्ण
	cpia2_करो_command(cam, CPIA2_CMD_SET_VC_CONTROL, TRANSFER_WRITE,पंचांगp_reg);

	/* Set target size (kb) on vc
	   This is a heuristic based on the quality parameter and the raw
	   framesize in kB भागided by 16 (the compression factor when the
	   quality is 100%) */
	target_kb = (cam->width * cam->height * 2 / 16384) *
				cam->params.vc_params.quality / 100;
	अगर (target_kb < 1)
		target_kb = 1;
	cpia2_करो_command(cam, CPIA2_CMD_SET_TARGET_KB,
			 TRANSFER_WRITE, target_kb);

	/* Wiggle VC Reset */
	/***
	 * First पढ़ो and रुको a bit.
	 ***/
	क्रम (i = 0; i < 50; i++) अणु
		cpia2_करो_command(cam, CPIA2_CMD_GET_PW_CONTROL,
				 TRANSFER_READ, 0);
	पूर्ण

	पंचांगp_reg = cam->params.vc_params.pw_control;
	पंचांगp_reg &= ~CPIA2_VC_PW_CTRL_VC_RESET_N;

	cpia2_करो_command(cam, CPIA2_CMD_SET_PW_CONTROL, TRANSFER_WRITE,पंचांगp_reg);

	पंचांगp_reg |= CPIA2_VC_PW_CTRL_VC_RESET_N;
	cpia2_करो_command(cam, CPIA2_CMD_SET_PW_CONTROL, TRANSFER_WRITE,पंचांगp_reg);

	cpia2_करो_command(cam, CPIA2_CMD_SET_DEF_JPEG_OPT, TRANSFER_WRITE, 0);

	cpia2_करो_command(cam, CPIA2_CMD_GET_USER_MODE, TRANSFER_READ, 0);
	DBG("After VC RESET, user mode is 0x%0X\n",
	    cam->params.vp_params.video_mode);

	वापस retval;
पूर्ण

/******************************************************************************
 *
 *  cpia2_set_high_घातer
 *
 *****************************************************************************/
अटल पूर्णांक cpia2_set_high_घातer(काष्ठा camera_data *cam)
अणु
	पूर्णांक i;
	क्रम (i = 0; i <= 50; i++) अणु
		/* Read प्रणाली status */
		cpia2_करो_command(cam,CPIA2_CMD_GET_SYSTEM_CTRL,TRANSFER_READ,0);

		/* If there is an error, clear it */
		अगर(cam->params.camera_state.प्रणाली_ctrl &
		   CPIA2_SYSTEM_CONTROL_V2W_ERR)
			cpia2_करो_command(cam, CPIA2_CMD_CLEAR_V2W_ERR,
					 TRANSFER_WRITE, 0);

		/* Try to set high घातer mode */
		cpia2_करो_command(cam, CPIA2_CMD_SET_SYSTEM_CTRL,
				 TRANSFER_WRITE, 1);

		/* Try to पढ़ो something in VP to check अगर everything is awake */
		cpia2_करो_command(cam, CPIA2_CMD_GET_VP_SYSTEM_STATE,
				 TRANSFER_READ, 0);
		अगर (cam->params.vp_params.प्रणाली_state &
		    CPIA2_VP_SYSTEMSTATE_HK_ALIVE) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (i == 50) अणु
			cam->params.camera_state.घातer_mode = LO_POWER_MODE;
			ERR("Camera did not wake up\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	DBG("System now in high power state\n");
	cam->params.camera_state.घातer_mode = HI_POWER_MODE;
	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  cpia2_set_low_घातer
 *
 *****************************************************************************/
पूर्णांक cpia2_set_low_घातer(काष्ठा camera_data *cam)
अणु
	cam->params.camera_state.घातer_mode = LO_POWER_MODE;
	cpia2_करो_command(cam, CPIA2_CMD_SET_SYSTEM_CTRL, TRANSFER_WRITE, 0);
	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  apply_vp_patch
 *
 *****************************************************************************/
अटल पूर्णांक cpia2_send_onebyte_command(काष्ठा camera_data *cam,
				      काष्ठा cpia2_command *cmd,
				      u8 start, u8 datum)
अणु
	cmd->buffer.block_data[0] = datum;
	cmd->start = start;
	cmd->reg_count = 1;
	वापस cpia2_send_command(cam, cmd);
पूर्ण

अटल पूर्णांक apply_vp_patch(काष्ठा camera_data *cam)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर fw_name[] = FIRMWARE;
	पूर्णांक i, ret;
	काष्ठा cpia2_command cmd;

	ret = request_firmware(&fw, fw_name, &cam->dev->dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "cpia2: failed to load VP patch \"%s\"\n",
		       fw_name);
		वापस ret;
	पूर्ण

	cmd.req_mode = CAMERAACCESS_TYPE_REPEAT | CAMERAACCESS_VP;
	cmd.direction = TRANSFER_WRITE;

	/* First send the start address... */
	cpia2_send_onebyte_command(cam, &cmd, 0x0A, fw->data[0]); /* hi */
	cpia2_send_onebyte_command(cam, &cmd, 0x0B, fw->data[1]); /* lo */

	/* ... followed by the data payload */
	क्रम (i = 2; i < fw->size; i += 64) अणु
		cmd.start = 0x0C; /* Data */
		cmd.reg_count = min_t(uपूर्णांक, 64, fw->size - i);
		स_नकल(cmd.buffer.block_data, &fw->data[i], cmd.reg_count);
		cpia2_send_command(cam, &cmd);
	पूर्ण

	/* Next send the start address... */
	cpia2_send_onebyte_command(cam, &cmd, 0x0A, fw->data[0]); /* hi */
	cpia2_send_onebyte_command(cam, &cmd, 0x0B, fw->data[1]); /* lo */

	/* ... followed by the 'goto' command */
	cpia2_send_onebyte_command(cam, &cmd, 0x0D, 1);

	release_firmware(fw);
	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  set_शेष_user_mode
 *
 *****************************************************************************/
अटल पूर्णांक set_शेष_user_mode(काष्ठा camera_data *cam)
अणु
	अचिन्हित अक्षर user_mode;
	अचिन्हित अक्षर frame_rate;
	पूर्णांक width = cam->params.roi.width;
	पूर्णांक height = cam->params.roi.height;

	चयन (cam->params.version.sensor_flags) अणु
	हाल CPIA2_VP_SENSOR_FLAGS_404:
	हाल CPIA2_VP_SENSOR_FLAGS_407:
	हाल CPIA2_VP_SENSOR_FLAGS_409:
	हाल CPIA2_VP_SENSOR_FLAGS_410:
		अगर ((width > STV_IMAGE_QCIF_COLS)
		    || (height > STV_IMAGE_QCIF_ROWS)) अणु
			user_mode = CPIA2_VP_USER_MODE_CIF;
		पूर्ण अन्यथा अणु
			user_mode = CPIA2_VP_USER_MODE_QCIFDS;
		पूर्ण
		frame_rate = CPIA2_VP_FRAMERATE_30;
		अवरोध;
	हाल CPIA2_VP_SENSOR_FLAGS_500:
		अगर ((width > STV_IMAGE_CIF_COLS)
		    || (height > STV_IMAGE_CIF_ROWS)) अणु
			user_mode = CPIA2_VP_USER_MODE_VGA;
		पूर्ण अन्यथा अणु
			user_mode = CPIA2_VP_USER_MODE_QVGADS;
		पूर्ण
		अगर (cam->params.pnp_id.device_type == DEVICE_STV_672)
			frame_rate = CPIA2_VP_FRAMERATE_15;
		अन्यथा
			frame_rate = CPIA2_VP_FRAMERATE_30;
		अवरोध;
	शेष:
		LOG("%s: Invalid sensor flag value 0x%0X\n",__func__,
		    cam->params.version.sensor_flags);
		वापस -EINVAL;
	पूर्ण

	DBG("Sensor flag = 0x%0x, user mode = 0x%0x, frame rate = 0x%X\n",
	    cam->params.version.sensor_flags, user_mode, frame_rate);
	cpia2_करो_command(cam, CPIA2_CMD_SET_USER_MODE, TRANSFER_WRITE,
			 user_mode);
	अगर(cam->params.vp_params.frame_rate > 0 &&
	   frame_rate > cam->params.vp_params.frame_rate)
		frame_rate = cam->params.vp_params.frame_rate;

	cpia2_set_fps(cam, frame_rate);

//	अगर (cam->params.pnp_id.device_type == DEVICE_STV_676)
//		cpia2_करो_command(cam,
//				 CPIA2_CMD_SET_VP_SYSTEM_CTRL,
//				 TRANSFER_WRITE,
//				 CPIA2_VP_SYSTEMCTRL_HK_CONTROL |
//				 CPIA2_VP_SYSTEMCTRL_POWER_CONTROL);

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  cpia2_match_video_size
 *
 *  वापस the best match, where 'best' is as always
 *  the largest that is not bigger than what is requested.
 *****************************************************************************/
पूर्णांक cpia2_match_video_size(पूर्णांक width, पूर्णांक height)
अणु
	अगर (width >= STV_IMAGE_VGA_COLS && height >= STV_IMAGE_VGA_ROWS)
		वापस VIDEOSIZE_VGA;

	अगर (width >= STV_IMAGE_CIF_COLS && height >= STV_IMAGE_CIF_ROWS)
		वापस VIDEOSIZE_CIF;

	अगर (width >= STV_IMAGE_QVGA_COLS && height >= STV_IMAGE_QVGA_ROWS)
		वापस VIDEOSIZE_QVGA;

	अगर (width >= 288 && height >= 216)
		वापस VIDEOSIZE_288_216;

	अगर (width >= 256 && height >= 192)
		वापस VIDEOSIZE_256_192;

	अगर (width >= 224 && height >= 168)
		वापस VIDEOSIZE_224_168;

	अगर (width >= 192 && height >= 144)
		वापस VIDEOSIZE_192_144;

	अगर (width >= STV_IMAGE_QCIF_COLS && height >= STV_IMAGE_QCIF_ROWS)
		वापस VIDEOSIZE_QCIF;

	वापस -1;
पूर्ण

/******************************************************************************
 *
 *  SetVideoSize
 *
 *****************************************************************************/
अटल पूर्णांक set_vw_size(काष्ठा camera_data *cam, पूर्णांक size)
अणु
	पूर्णांक retval = 0;

	cam->params.vp_params.video_size = size;

	चयन (size) अणु
	हाल VIDEOSIZE_VGA:
		DBG("Setting size to VGA\n");
		cam->params.roi.width = STV_IMAGE_VGA_COLS;
		cam->params.roi.height = STV_IMAGE_VGA_ROWS;
		cam->width = STV_IMAGE_VGA_COLS;
		cam->height = STV_IMAGE_VGA_ROWS;
		अवरोध;
	हाल VIDEOSIZE_CIF:
		DBG("Setting size to CIF\n");
		cam->params.roi.width = STV_IMAGE_CIF_COLS;
		cam->params.roi.height = STV_IMAGE_CIF_ROWS;
		cam->width = STV_IMAGE_CIF_COLS;
		cam->height = STV_IMAGE_CIF_ROWS;
		अवरोध;
	हाल VIDEOSIZE_QVGA:
		DBG("Setting size to QVGA\n");
		cam->params.roi.width = STV_IMAGE_QVGA_COLS;
		cam->params.roi.height = STV_IMAGE_QVGA_ROWS;
		cam->width = STV_IMAGE_QVGA_COLS;
		cam->height = STV_IMAGE_QVGA_ROWS;
		अवरोध;
	हाल VIDEOSIZE_288_216:
		cam->params.roi.width = 288;
		cam->params.roi.height = 216;
		cam->width = 288;
		cam->height = 216;
		अवरोध;
	हाल VIDEOSIZE_256_192:
		cam->width = 256;
		cam->height = 192;
		cam->params.roi.width = 256;
		cam->params.roi.height = 192;
		अवरोध;
	हाल VIDEOSIZE_224_168:
		cam->width = 224;
		cam->height = 168;
		cam->params.roi.width = 224;
		cam->params.roi.height = 168;
		अवरोध;
	हाल VIDEOSIZE_192_144:
		cam->width = 192;
		cam->height = 144;
		cam->params.roi.width = 192;
		cam->params.roi.height = 144;
		अवरोध;
	हाल VIDEOSIZE_QCIF:
		DBG("Setting size to QCIF\n");
		cam->params.roi.width = STV_IMAGE_QCIF_COLS;
		cam->params.roi.height = STV_IMAGE_QCIF_ROWS;
		cam->width = STV_IMAGE_QCIF_COLS;
		cam->height = STV_IMAGE_QCIF_ROWS;
		अवरोध;
	शेष:
		retval = -EINVAL;
	पूर्ण
	वापस retval;
पूर्ण

/******************************************************************************
 *
 *  configure_sensor
 *
 *****************************************************************************/
अटल पूर्णांक configure_sensor(काष्ठा camera_data *cam,
			    पूर्णांक req_width, पूर्णांक req_height)
अणु
	पूर्णांक retval;

	चयन (cam->params.version.sensor_flags) अणु
	हाल CPIA2_VP_SENSOR_FLAGS_404:
	हाल CPIA2_VP_SENSOR_FLAGS_407:
	हाल CPIA2_VP_SENSOR_FLAGS_409:
	हाल CPIA2_VP_SENSOR_FLAGS_410:
		retval = config_sensor_410(cam, req_width, req_height);
		अवरोध;
	हाल CPIA2_VP_SENSOR_FLAGS_500:
		retval = config_sensor_500(cam, req_width, req_height);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस retval;
पूर्ण

/******************************************************************************
 *
 *  config_sensor_410
 *
 *****************************************************************************/
अटल पूर्णांक config_sensor_410(काष्ठा camera_data *cam,
			    पूर्णांक req_width, पूर्णांक req_height)
अणु
	काष्ठा cpia2_command cmd;
	पूर्णांक i = 0;
	पूर्णांक image_size;
	पूर्णांक image_type;
	पूर्णांक width = req_width;
	पूर्णांक height = req_height;

	/***
	 *  Make sure size करोesn't exceed CIF.
	 ***/
	अगर (width > STV_IMAGE_CIF_COLS)
		width = STV_IMAGE_CIF_COLS;
	अगर (height > STV_IMAGE_CIF_ROWS)
		height = STV_IMAGE_CIF_ROWS;

	image_size = cpia2_match_video_size(width, height);

	DBG("Config 410: width = %d, height = %d\n", width, height);
	DBG("Image size returned is %d\n", image_size);
	अगर (image_size >= 0) अणु
		set_vw_size(cam, image_size);
		width = cam->params.roi.width;
		height = cam->params.roi.height;

		DBG("After set_vw_size(), width = %d, height = %d\n",
		    width, height);
		अगर (width <= 176 && height <= 144) अणु
			DBG("image type = VIDEOSIZE_QCIF\n");
			image_type = VIDEOSIZE_QCIF;
		पूर्ण
		अन्यथा अगर (width <= 320 && height <= 240) अणु
			DBG("image type = VIDEOSIZE_QVGA\n");
			image_type = VIDEOSIZE_QVGA;
		पूर्ण
		अन्यथा अणु
			DBG("image type = VIDEOSIZE_CIF\n");
			image_type = VIDEOSIZE_CIF;
		पूर्ण
	पूर्ण अन्यथा अणु
		ERR("ConfigSensor410 failed\n");
		वापस -EINVAL;
	पूर्ण

	cmd.req_mode = CAMERAACCESS_TYPE_RANDOM | CAMERAACCESS_VC;
	cmd.direction = TRANSFER_WRITE;

	/* VC Format */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_FORMAT;
	अगर (image_type == VIDEOSIZE_CIF) अणु
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (CPIA2_VC_VC_FORMAT_UFIRST |
			  CPIA2_VC_VC_FORMAT_SHORTLINE);
	पूर्ण अन्यथा अणु
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) CPIA2_VC_VC_FORMAT_UFIRST;
	पूर्ण

	/* VC Clocks */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_CLOCKS;
	अगर (image_type == VIDEOSIZE_QCIF) अणु
		अगर (cam->params.pnp_id.device_type == DEVICE_STV_672) अणु
			cmd.buffer.रेजिस्टरs[i++].value=
				(u8)(CPIA2_VC_VC_672_CLOCKS_CIF_DIV_BY_3 |
				     CPIA2_VC_VC_672_CLOCKS_SCALING |
				     CPIA2_VC_VC_CLOCKS_LOGDIV2);
			DBG("VC_Clocks (0xc4) should be B\n");
		पूर्ण
		अन्यथा अणु
			cmd.buffer.रेजिस्टरs[i++].value=
				(u8)(CPIA2_VC_VC_676_CLOCKS_CIF_DIV_BY_3 |
				     CPIA2_VC_VC_CLOCKS_LOGDIV2);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cam->params.pnp_id.device_type == DEVICE_STV_672) अणु
			cmd.buffer.रेजिस्टरs[i++].value =
			   (u8) (CPIA2_VC_VC_672_CLOCKS_CIF_DIV_BY_3 |
				 CPIA2_VC_VC_CLOCKS_LOGDIV0);
		पूर्ण
		अन्यथा अणु
			cmd.buffer.रेजिस्टरs[i++].value =
			   (u8) (CPIA2_VC_VC_676_CLOCKS_CIF_DIV_BY_3 |
				 CPIA2_VC_VC_676_CLOCKS_SCALING |
				 CPIA2_VC_VC_CLOCKS_LOGDIV0);
		पूर्ण
	पूर्ण
	DBG("VC_Clocks (0xc4) = 0x%0X\n", cmd.buffer.रेजिस्टरs[i-1].value);

	/* Input reqWidth from VC */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_IHSIZE_LO;
	अगर (image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (STV_IMAGE_QCIF_COLS / 4);
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (STV_IMAGE_CIF_COLS / 4);

	/* Timings */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_XLIM_HI;
	अगर (image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 0;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 1;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_XLIM_LO;
	अगर (image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 208;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 160;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_YLIM_HI;
	अगर (image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 0;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 1;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_YLIM_LO;
	अगर (image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 160;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 64;

	/* Output Image Size */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_OHSIZE;
	cmd.buffer.रेजिस्टरs[i++].value = cam->params.roi.width / 4;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_OVSIZE;
	cmd.buffer.रेजिस्टरs[i++].value = cam->params.roi.height / 4;

	/* Cropping */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_HCROP;
	अगर (image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (((STV_IMAGE_QCIF_COLS / 4) - (width / 4)) / 2);
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (((STV_IMAGE_CIF_COLS / 4) - (width / 4)) / 2);

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_VCROP;
	अगर (image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (((STV_IMAGE_QCIF_ROWS / 4) - (height / 4)) / 2);
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (((STV_IMAGE_CIF_ROWS / 4) - (height / 4)) / 2);

	/* Scaling रेजिस्टरs (शेषs) */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_HPHASE;
	cmd.buffer.रेजिस्टरs[i++].value = (u8) 0;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_VPHASE;
	cmd.buffer.रेजिस्टरs[i++].value = (u8) 0;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_HISPAN;
	cmd.buffer.रेजिस्टरs[i++].value = (u8) 31;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_VISPAN;
	cmd.buffer.रेजिस्टरs[i++].value = (u8) 31;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_HICROP;
	cmd.buffer.रेजिस्टरs[i++].value = (u8) 0;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_VICROP;
	cmd.buffer.रेजिस्टरs[i++].value = (u8) 0;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_HFRACT;
	cmd.buffer.रेजिस्टरs[i++].value = (u8) 0x81;	/* = 8/1 = 8 (HIBYTE/LOBYTE) */

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_VFRACT;
	cmd.buffer.रेजिस्टरs[i++].value = (u8) 0x81;	/* = 8/1 = 8 (HIBYTE/LOBYTE) */

	cmd.reg_count = i;

	cpia2_send_command(cam, &cmd);

	वापस i;
पूर्ण


/******************************************************************************
 *
 *  config_sensor_500(cam)
 *
 *****************************************************************************/
अटल पूर्णांक config_sensor_500(काष्ठा camera_data *cam,
			     पूर्णांक req_width, पूर्णांक req_height)
अणु
	काष्ठा cpia2_command cmd;
	पूर्णांक i = 0;
	पूर्णांक image_size = VIDEOSIZE_CIF;
	पूर्णांक image_type = VIDEOSIZE_VGA;
	पूर्णांक width = req_width;
	पूर्णांक height = req_height;
	अचिन्हित पूर्णांक device = cam->params.pnp_id.device_type;

	image_size = cpia2_match_video_size(width, height);

	अगर (width > STV_IMAGE_CIF_COLS || height > STV_IMAGE_CIF_ROWS)
		image_type = VIDEOSIZE_VGA;
	अन्यथा अगर (width > STV_IMAGE_QVGA_COLS || height > STV_IMAGE_QVGA_ROWS)
		image_type = VIDEOSIZE_CIF;
	अन्यथा अगर (width > STV_IMAGE_QCIF_COLS || height > STV_IMAGE_QCIF_ROWS)
		image_type = VIDEOSIZE_QVGA;
	अन्यथा
		image_type = VIDEOSIZE_QCIF;

	अगर (image_size >= 0) अणु
		set_vw_size(cam, image_size);
		width = cam->params.roi.width;
		height = cam->params.roi.height;
	पूर्ण अन्यथा अणु
		ERR("ConfigSensor500 failed\n");
		वापस -EINVAL;
	पूर्ण

	DBG("image_size = %d, width = %d, height = %d, type = %d\n",
	    image_size, width, height, image_type);

	cmd.req_mode = CAMERAACCESS_TYPE_RANDOM | CAMERAACCESS_VC;
	cmd.direction = TRANSFER_WRITE;
	i = 0;

	/* VC Format */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_FORMAT;
	cmd.buffer.रेजिस्टरs[i].value = (u8) CPIA2_VC_VC_FORMAT_UFIRST;
	अगर (image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i].value |= (u8) CPIA2_VC_VC_FORMAT_DECIMATING;
	i++;

	/* VC Clocks */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_CLOCKS;
	अगर (device == DEVICE_STV_672) अणु
		अगर (image_type == VIDEOSIZE_VGA)
			cmd.buffer.रेजिस्टरs[i].value =
				(u8)CPIA2_VC_VC_CLOCKS_LOGDIV1;
		अन्यथा
			cmd.buffer.रेजिस्टरs[i].value =
				(u8)(CPIA2_VC_VC_672_CLOCKS_SCALING |
				     CPIA2_VC_VC_CLOCKS_LOGDIV3);
	पूर्ण अन्यथा अणु
		अगर (image_type == VIDEOSIZE_VGA)
			cmd.buffer.रेजिस्टरs[i].value =
				(u8)CPIA2_VC_VC_CLOCKS_LOGDIV0;
		अन्यथा
			cmd.buffer.रेजिस्टरs[i].value =
				(u8)(CPIA2_VC_VC_676_CLOCKS_SCALING |
				     CPIA2_VC_VC_CLOCKS_LOGDIV2);
	पूर्ण
	i++;

	DBG("VC_CLOCKS = 0x%X\n", cmd.buffer.रेजिस्टरs[i-1].value);

	/* Input width from VP */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_IHSIZE_LO;
	अगर (image_type == VIDEOSIZE_VGA)
		cmd.buffer.रेजिस्टरs[i].value =
		    (u8) (STV_IMAGE_VGA_COLS / 4);
	अन्यथा
		cmd.buffer.रेजिस्टरs[i].value =
		    (u8) (STV_IMAGE_QVGA_COLS / 4);
	i++;
	DBG("Input width = %d\n", cmd.buffer.रेजिस्टरs[i-1].value);

	/* Timings */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_XLIM_HI;
	अगर (image_type == VIDEOSIZE_VGA)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 2;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 1;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_XLIM_LO;
	अगर (image_type == VIDEOSIZE_VGA)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 250;
	अन्यथा अगर (image_type == VIDEOSIZE_QVGA)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 125;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 160;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_YLIM_HI;
	अगर (image_type == VIDEOSIZE_VGA)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 2;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 1;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_YLIM_LO;
	अगर (image_type == VIDEOSIZE_VGA)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 12;
	अन्यथा अगर (image_type == VIDEOSIZE_QVGA)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 64;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 6;

	/* Output Image Size */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_OHSIZE;
	अगर (image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value = STV_IMAGE_CIF_COLS  / 4;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = width / 4;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_OVSIZE;
	अगर (image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value = STV_IMAGE_CIF_ROWS  / 4;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = height / 4;

	/* Cropping */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_HCROP;
	अगर (image_type == VIDEOSIZE_VGA)
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (((STV_IMAGE_VGA_COLS / 4) - (width / 4)) / 2);
	अन्यथा अगर (image_type == VIDEOSIZE_QVGA)
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (((STV_IMAGE_QVGA_COLS / 4) - (width / 4)) / 2);
	अन्यथा अगर (image_type == VIDEOSIZE_CIF)
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (((STV_IMAGE_CIF_COLS / 4) - (width / 4)) / 2);
	अन्यथा /*अगर (image_type == VIDEOSIZE_QCIF)*/
		cmd.buffer.रेजिस्टरs[i++].value =
			(u8) (((STV_IMAGE_QCIF_COLS / 4) - (width / 4)) / 2);

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_VCROP;
	अगर (image_type == VIDEOSIZE_VGA)
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (((STV_IMAGE_VGA_ROWS / 4) - (height / 4)) / 2);
	अन्यथा अगर (image_type == VIDEOSIZE_QVGA)
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (((STV_IMAGE_QVGA_ROWS / 4) - (height / 4)) / 2);
	अन्यथा अगर (image_type == VIDEOSIZE_CIF)
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (((STV_IMAGE_CIF_ROWS / 4) - (height / 4)) / 2);
	अन्यथा /*अगर (image_type == VIDEOSIZE_QCIF)*/
		cmd.buffer.रेजिस्टरs[i++].value =
		    (u8) (((STV_IMAGE_QCIF_ROWS / 4) - (height / 4)) / 2);

	/* Scaling रेजिस्टरs (शेषs) */
	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_HPHASE;
	अगर (image_type == VIDEOSIZE_CIF || image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 36;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 0;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_VPHASE;
	अगर (image_type == VIDEOSIZE_CIF || image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 32;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 0;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_HISPAN;
	अगर (image_type == VIDEOSIZE_CIF || image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 26;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 31;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_VISPAN;
	अगर (image_type == VIDEOSIZE_CIF || image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 21;
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 31;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_HICROP;
	cmd.buffer.रेजिस्टरs[i++].value = (u8) 0;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_VICROP;
	cmd.buffer.रेजिस्टरs[i++].value = (u8) 0;

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_HFRACT;
	अगर (image_type == VIDEOSIZE_CIF || image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 0x2B;	/* 2/11 */
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 0x81;	/* 8/1 */

	cmd.buffer.रेजिस्टरs[i].index = CPIA2_VC_VC_VFRACT;
	अगर (image_type == VIDEOSIZE_CIF || image_type == VIDEOSIZE_QCIF)
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 0x13;	/* 1/3 */
	अन्यथा
		cmd.buffer.रेजिस्टरs[i++].value = (u8) 0x81;	/* 8/1 */

	cmd.reg_count = i;

	cpia2_send_command(cam, &cmd);

	वापस i;
पूर्ण


/******************************************************************************
 *
 *  setallproperties
 *
 *  This sets all user changeable properties to the values in cam->params.
 *****************************************************************************/
अटल पूर्णांक set_all_properties(काष्ठा camera_data *cam)
अणु
	/**
	 * Don't set target_kb here, it will be set later.
	 * framerate and user_mode were alपढ़ोy set (set_शेष_user_mode).
	 **/

	cpia2_usb_change_streaming_alternate(cam,
					  cam->params.camera_state.stream_mode);

	cpia2_करो_command(cam,
			 CPIA2_CMD_SET_VC_MP_GPIO_सूचीECTION,
			 TRANSFER_WRITE, cam->params.vp_params.gpio_direction);
	cpia2_करो_command(cam, CPIA2_CMD_SET_VC_MP_GPIO_DATA, TRANSFER_WRITE,
			 cam->params.vp_params.gpio_data);

	v4l2_ctrl_handler_setup(&cam->hdl);

	wake_प्रणाली(cam);

	set_lowlight_boost(cam);

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  cpia2_save_camera_state
 *
 *****************************************************************************/
व्योम cpia2_save_camera_state(काष्ठा camera_data *cam)
अणु
	cpia2_करो_command(cam, CPIA2_CMD_GET_USER_EFFECTS, TRANSFER_READ, 0);
	cpia2_करो_command(cam, CPIA2_CMD_GET_VC_MP_GPIO_सूचीECTION, TRANSFER_READ,
			 0);
	cpia2_करो_command(cam, CPIA2_CMD_GET_VC_MP_GPIO_DATA, TRANSFER_READ, 0);
	/* Don't get framerate or target_kb. Trust the values we alपढ़ोy have */
पूर्ण


/******************************************************************************
 *
 *  cpia2_set_flicker_mode
 *
 *****************************************************************************/
पूर्णांक cpia2_set_flicker_mode(काष्ठा camera_data *cam, पूर्णांक mode)
अणु
	अचिन्हित अक्षर cam_reg;
	पूर्णांक err = 0;

	अगर(cam->params.pnp_id.device_type != DEVICE_STV_672)
		वापस -EINVAL;

	/* Set the appropriate bits in FLICKER_MODES, preserving the rest */
	अगर((err = cpia2_करो_command(cam, CPIA2_CMD_GET_FLICKER_MODES,
				   TRANSFER_READ, 0)))
		वापस err;
	cam_reg = cam->params.flicker_control.cam_रेजिस्टर;

	चयन(mode) अणु
	हाल NEVER_FLICKER:
		cam_reg |= CPIA2_VP_FLICKER_MODES_NEVER_FLICKER;
		cam_reg &= ~CPIA2_VP_FLICKER_MODES_50HZ;
		अवरोध;
	हाल FLICKER_60:
		cam_reg &= ~CPIA2_VP_FLICKER_MODES_NEVER_FLICKER;
		cam_reg &= ~CPIA2_VP_FLICKER_MODES_50HZ;
		अवरोध;
	हाल FLICKER_50:
		cam_reg &= ~CPIA2_VP_FLICKER_MODES_NEVER_FLICKER;
		cam_reg |= CPIA2_VP_FLICKER_MODES_50HZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर((err = cpia2_करो_command(cam, CPIA2_CMD_SET_FLICKER_MODES,
				   TRANSFER_WRITE, cam_reg)))
		वापस err;

	/* Set the appropriate bits in EXP_MODES, preserving the rest */
	अगर((err = cpia2_करो_command(cam, CPIA2_CMD_GET_VP_EXP_MODES,
				   TRANSFER_READ, 0)))
		वापस err;
	cam_reg = cam->params.vp_params.exposure_modes;

	अगर (mode == NEVER_FLICKER) अणु
		cam_reg |= CPIA2_VP_EXPOSURE_MODES_INHIBIT_FLICKER;
	पूर्ण अन्यथा अणु
		cam_reg &= ~CPIA2_VP_EXPOSURE_MODES_INHIBIT_FLICKER;
	पूर्ण

	अगर((err = cpia2_करो_command(cam, CPIA2_CMD_SET_VP_EXP_MODES,
				   TRANSFER_WRITE, cam_reg)))
		वापस err;

	अगर((err = cpia2_करो_command(cam, CPIA2_CMD_REHASH_VP4,
				   TRANSFER_WRITE, 1)))
		वापस err;

	चयन(mode) अणु
	हाल NEVER_FLICKER:
	हाल FLICKER_60:
	हाल FLICKER_50:
		cam->params.flicker_control.flicker_mode_req = mode;
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

/******************************************************************************
 *
 *  cpia2_set_property_flip
 *
 *****************************************************************************/
व्योम cpia2_set_property_flip(काष्ठा camera_data *cam, पूर्णांक prop_val)
अणु
	अचिन्हित अक्षर cam_reg;

	cpia2_करो_command(cam, CPIA2_CMD_GET_USER_EFFECTS, TRANSFER_READ, 0);
	cam_reg = cam->params.vp_params.user_effects;

	अगर (prop_val)
	अणु
		cam_reg |= CPIA2_VP_USER_EFFECTS_FLIP;
	पूर्ण
	अन्यथा
	अणु
		cam_reg &= ~CPIA2_VP_USER_EFFECTS_FLIP;
	पूर्ण
	cam->params.vp_params.user_effects = cam_reg;
	cpia2_करो_command(cam, CPIA2_CMD_SET_USER_EFFECTS, TRANSFER_WRITE,
			 cam_reg);
पूर्ण

/******************************************************************************
 *
 *  cpia2_set_property_mirror
 *
 *****************************************************************************/
व्योम cpia2_set_property_mirror(काष्ठा camera_data *cam, पूर्णांक prop_val)
अणु
	अचिन्हित अक्षर cam_reg;

	cpia2_करो_command(cam, CPIA2_CMD_GET_USER_EFFECTS, TRANSFER_READ, 0);
	cam_reg = cam->params.vp_params.user_effects;

	अगर (prop_val)
	अणु
		cam_reg |= CPIA2_VP_USER_EFFECTS_MIRROR;
	पूर्ण
	अन्यथा
	अणु
		cam_reg &= ~CPIA2_VP_USER_EFFECTS_MIRROR;
	पूर्ण
	cam->params.vp_params.user_effects = cam_reg;
	cpia2_करो_command(cam, CPIA2_CMD_SET_USER_EFFECTS, TRANSFER_WRITE,
			 cam_reg);
पूर्ण

/******************************************************************************
 *
 *  cpia2_set_gpio
 *
 *****************************************************************************/
पूर्णांक cpia2_set_gpio(काष्ठा camera_data *cam, अचिन्हित अक्षर setting)
अणु
	पूर्णांक ret;

	/* Set the microport direction (रेजिस्टर 0x90, should be defined
	 * alपढ़ोy) to 1 (user output), and set the microport data (0x91) to
	 * the value in the ioctl argument.
	 */

	ret = cpia2_करो_command(cam,
			       CPIA2_CMD_SET_VC_MP_GPIO_सूचीECTION,
			       CPIA2_VC_MP_सूची_OUTPUT,
			       255);
	अगर (ret < 0)
		वापस ret;
	cam->params.vp_params.gpio_direction = 255;

	ret = cpia2_करो_command(cam,
			       CPIA2_CMD_SET_VC_MP_GPIO_DATA,
			       CPIA2_VC_MP_सूची_OUTPUT,
			       setting);
	अगर (ret < 0)
		वापस ret;
	cam->params.vp_params.gpio_data = setting;

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  cpia2_set_fps
 *
 *****************************************************************************/
पूर्णांक cpia2_set_fps(काष्ठा camera_data *cam, पूर्णांक framerate)
अणु
	पूर्णांक retval;

	चयन(framerate) अणु
		हाल CPIA2_VP_FRAMERATE_30:
		हाल CPIA2_VP_FRAMERATE_25:
			अगर(cam->params.pnp_id.device_type == DEVICE_STV_672 &&
			   cam->params.version.sensor_flags ==
						    CPIA2_VP_SENSOR_FLAGS_500) अणु
				वापस -EINVAL;
			पूर्ण
			fallthrough;
		हाल CPIA2_VP_FRAMERATE_15:
		हाल CPIA2_VP_FRAMERATE_12_5:
		हाल CPIA2_VP_FRAMERATE_7_5:
		हाल CPIA2_VP_FRAMERATE_6_25:
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	अगर (cam->params.pnp_id.device_type == DEVICE_STV_672 &&
	    framerate == CPIA2_VP_FRAMERATE_15)
		framerate = 0; /* Work around bug in VP4 */

	retval = cpia2_करो_command(cam,
				 CPIA2_CMD_FRAMERATE_REQ,
				 TRANSFER_WRITE,
				 framerate);

	अगर(retval == 0)
		cam->params.vp_params.frame_rate = framerate;

	वापस retval;
पूर्ण

/******************************************************************************
 *
 *  cpia2_set_brightness
 *
 *****************************************************************************/
व्योम cpia2_set_brightness(काष्ठा camera_data *cam, अचिन्हित अक्षर value)
अणु
	/***
	 * Don't let the रेजिस्टर be set to zero - bug in VP4 - flash of full
	 * brightness
	 ***/
	अगर (cam->params.pnp_id.device_type == DEVICE_STV_672 && value == 0)
		value++;
	DBG("Setting brightness to %d (0x%0x)\n", value, value);
	cpia2_करो_command(cam, CPIA2_CMD_SET_VP_BRIGHTNESS, TRANSFER_WRITE, value);
पूर्ण

/******************************************************************************
 *
 *  cpia2_set_contrast
 *
 *****************************************************************************/
व्योम cpia2_set_contrast(काष्ठा camera_data *cam, अचिन्हित अक्षर value)
अणु
	DBG("Setting contrast to %d (0x%0x)\n", value, value);
	cpia2_करो_command(cam, CPIA2_CMD_SET_CONTRAST, TRANSFER_WRITE, value);
पूर्ण

/******************************************************************************
 *
 *  cpia2_set_saturation
 *
 *****************************************************************************/
व्योम cpia2_set_saturation(काष्ठा camera_data *cam, अचिन्हित अक्षर value)
अणु
	DBG("Setting saturation to %d (0x%0x)\n", value, value);
	cpia2_करो_command(cam,CPIA2_CMD_SET_VP_SATURATION, TRANSFER_WRITE,value);
पूर्ण

/******************************************************************************
 *
 *  wake_प्रणाली
 *
 *****************************************************************************/
अटल व्योम wake_प्रणाली(काष्ठा camera_data *cam)
अणु
	cpia2_करो_command(cam, CPIA2_CMD_SET_WAKEUP, TRANSFER_WRITE, 0);
पूर्ण

/******************************************************************************
 *
 *  set_lowlight_boost
 *
 *  Valid क्रम STV500 sensor only
 *****************************************************************************/
अटल व्योम set_lowlight_boost(काष्ठा camera_data *cam)
अणु
	काष्ठा cpia2_command cmd;

	अगर (cam->params.pnp_id.device_type != DEVICE_STV_672 ||
	    cam->params.version.sensor_flags != CPIA2_VP_SENSOR_FLAGS_500)
		वापस;

	cmd.direction = TRANSFER_WRITE;
	cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
	cmd.reg_count = 3;
	cmd.start = CPIA2_VP_RAM_ADDR_H;

	cmd.buffer.block_data[0] = 0;	/* High byte of address to ग_लिखो to */
	cmd.buffer.block_data[1] = 0x59;	/* Low byte of address to ग_लिखो to */
	cmd.buffer.block_data[2] = 0;	/* High byte of data to ग_लिखो */

	cpia2_send_command(cam, &cmd);

	अगर (cam->params.vp_params.lowlight_boost) अणु
		cmd.buffer.block_data[0] = 0x02;	/* Low byte data to ग_लिखो */
	पूर्ण अन्यथा अणु
		cmd.buffer.block_data[0] = 0x06;
	पूर्ण
	cmd.start = CPIA2_VP_RAM_DATA;
	cmd.reg_count = 1;
	cpia2_send_command(cam, &cmd);

	/* Rehash the VP4 values */
	cpia2_करो_command(cam, CPIA2_CMD_REHASH_VP4, TRANSFER_WRITE, 1);
पूर्ण

/******************************************************************************
 *
 *  cpia2_set_क्रमmat
 *
 *  Assumes that new size is alपढ़ोy set in param काष्ठा.
 *****************************************************************************/
व्योम cpia2_set_क्रमmat(काष्ठा camera_data *cam)
अणु
	cam->flush = true;

	cpia2_usb_stream_छोड़ो(cam);

	/* reset camera to new size */
	cpia2_set_low_घातer(cam);
	cpia2_reset_camera(cam);
	cam->flush = false;

	cpia2_dbg_dump_रेजिस्टरs(cam);

	cpia2_usb_stream_resume(cam);
पूर्ण

/******************************************************************************
 *
 * cpia2_dbg_dump_रेजिस्टरs
 *
 *****************************************************************************/
व्योम cpia2_dbg_dump_रेजिस्टरs(काष्ठा camera_data *cam)
अणु
#अगर_घोषित _CPIA2_DEBUG_
	काष्ठा cpia2_command cmd;

	अगर (!(debugs_on & DEBUG_DUMP_REGS))
		वापस;

	cmd.direction = TRANSFER_READ;

	/* Start with bank 0 (SYSTEM) */
	cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_SYSTEM;
	cmd.reg_count = 3;
	cmd.start = 0;
	cpia2_send_command(cam, &cmd);
	prपूर्णांकk(KERN_DEBUG "System Device Hi      = 0x%X\n",
	       cmd.buffer.block_data[0]);
	prपूर्णांकk(KERN_DEBUG "System Device Lo      = 0x%X\n",
	       cmd.buffer.block_data[1]);
	prपूर्णांकk(KERN_DEBUG "System_system control = 0x%X\n",
	       cmd.buffer.block_data[2]);

	/* Bank 1 (VC) */
	cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VC;
	cmd.reg_count = 4;
	cmd.start = 0x80;
	cpia2_send_command(cam, &cmd);
	prपूर्णांकk(KERN_DEBUG "ASIC_ID       = 0x%X\n",
	       cmd.buffer.block_data[0]);
	prपूर्णांकk(KERN_DEBUG "ASIC_REV      = 0x%X\n",
	       cmd.buffer.block_data[1]);
	prपूर्णांकk(KERN_DEBUG "PW_CONTRL     = 0x%X\n",
	       cmd.buffer.block_data[2]);
	prपूर्णांकk(KERN_DEBUG "WAKEUP        = 0x%X\n",
	       cmd.buffer.block_data[3]);

	cmd.start = 0xA0;	/* ST_CTRL */
	cmd.reg_count = 1;
	cpia2_send_command(cam, &cmd);
	prपूर्णांकk(KERN_DEBUG "Stream ctrl   = 0x%X\n",
	       cmd.buffer.block_data[0]);

	cmd.start = 0xA4;	/* Stream status */
	cpia2_send_command(cam, &cmd);
	prपूर्णांकk(KERN_DEBUG "Stream status = 0x%X\n",
	       cmd.buffer.block_data[0]);

	cmd.start = 0xA8;	/* USB status */
	cmd.reg_count = 3;
	cpia2_send_command(cam, &cmd);
	prपूर्णांकk(KERN_DEBUG "USB_CTRL      = 0x%X\n",
	       cmd.buffer.block_data[0]);
	prपूर्णांकk(KERN_DEBUG "USB_STRM      = 0x%X\n",
	       cmd.buffer.block_data[1]);
	prपूर्णांकk(KERN_DEBUG "USB_STATUS    = 0x%X\n",
	       cmd.buffer.block_data[2]);

	cmd.start = 0xAF;	/* USB settings */
	cmd.reg_count = 1;
	cpia2_send_command(cam, &cmd);
	prपूर्णांकk(KERN_DEBUG "USB settings  = 0x%X\n",
	       cmd.buffer.block_data[0]);

	cmd.start = 0xC0;	/* VC stuff */
	cmd.reg_count = 26;
	cpia2_send_command(cam, &cmd);
	prपूर्णांकk(KERN_DEBUG "VC Control    = 0x%0X\n",
	       cmd.buffer.block_data[0]);
	prपूर्णांकk(KERN_DEBUG "VC Format     = 0x%0X\n",
	       cmd.buffer.block_data[3]);
	prपूर्णांकk(KERN_DEBUG "VC Clocks     = 0x%0X\n",
	       cmd.buffer.block_data[4]);
	prपूर्णांकk(KERN_DEBUG "VC IHSize     = 0x%0X\n",
	       cmd.buffer.block_data[5]);
	prपूर्णांकk(KERN_DEBUG "VC Xlim Hi    = 0x%0X\n",
	       cmd.buffer.block_data[6]);
	prपूर्णांकk(KERN_DEBUG "VC XLim Lo    = 0x%0X\n",
	       cmd.buffer.block_data[7]);
	prपूर्णांकk(KERN_DEBUG "VC YLim Hi    = 0x%0X\n",
	       cmd.buffer.block_data[8]);
	prपूर्णांकk(KERN_DEBUG "VC YLim Lo    = 0x%0X\n",
	       cmd.buffer.block_data[9]);
	prपूर्णांकk(KERN_DEBUG "VC OHSize     = 0x%0X\n",
	       cmd.buffer.block_data[10]);
	prपूर्णांकk(KERN_DEBUG "VC OVSize     = 0x%0X\n",
	       cmd.buffer.block_data[11]);
	prपूर्णांकk(KERN_DEBUG "VC HCrop      = 0x%0X\n",
	       cmd.buffer.block_data[12]);
	prपूर्णांकk(KERN_DEBUG "VC VCrop      = 0x%0X\n",
	       cmd.buffer.block_data[13]);
	prपूर्णांकk(KERN_DEBUG "VC HPhase     = 0x%0X\n",
	       cmd.buffer.block_data[14]);
	prपूर्णांकk(KERN_DEBUG "VC VPhase     = 0x%0X\n",
	       cmd.buffer.block_data[15]);
	prपूर्णांकk(KERN_DEBUG "VC HIspan     = 0x%0X\n",
	       cmd.buffer.block_data[16]);
	prपूर्णांकk(KERN_DEBUG "VC VIspan     = 0x%0X\n",
	       cmd.buffer.block_data[17]);
	prपूर्णांकk(KERN_DEBUG "VC HiCrop     = 0x%0X\n",
	       cmd.buffer.block_data[18]);
	prपूर्णांकk(KERN_DEBUG "VC ViCrop     = 0x%0X\n",
	       cmd.buffer.block_data[19]);
	prपूर्णांकk(KERN_DEBUG "VC HiFract    = 0x%0X\n",
	       cmd.buffer.block_data[20]);
	prपूर्णांकk(KERN_DEBUG "VC ViFract    = 0x%0X\n",
	       cmd.buffer.block_data[21]);
	prपूर्णांकk(KERN_DEBUG "VC JPeg Opt   = 0x%0X\n",
	       cmd.buffer.block_data[22]);
	prपूर्णांकk(KERN_DEBUG "VC Creep Per  = 0x%0X\n",
	       cmd.buffer.block_data[23]);
	prपूर्णांकk(KERN_DEBUG "VC User Sq.   = 0x%0X\n",
	       cmd.buffer.block_data[24]);
	prपूर्णांकk(KERN_DEBUG "VC Target KB  = 0x%0X\n",
	       cmd.buffer.block_data[25]);

	/*** VP ***/
	cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VP;
	cmd.reg_count = 14;
	cmd.start = 0;
	cpia2_send_command(cam, &cmd);

	prपूर्णांकk(KERN_DEBUG "VP Dev Hi     = 0x%0X\n",
	       cmd.buffer.block_data[0]);
	prपूर्णांकk(KERN_DEBUG "VP Dev Lo     = 0x%0X\n",
	       cmd.buffer.block_data[1]);
	prपूर्णांकk(KERN_DEBUG "VP Sys State  = 0x%0X\n",
	       cmd.buffer.block_data[2]);
	prपूर्णांकk(KERN_DEBUG "VP Sys Ctrl   = 0x%0X\n",
	       cmd.buffer.block_data[3]);
	prपूर्णांकk(KERN_DEBUG "VP Sensor flg = 0x%0X\n",
	       cmd.buffer.block_data[5]);
	prपूर्णांकk(KERN_DEBUG "VP Sensor Rev = 0x%0X\n",
	       cmd.buffer.block_data[6]);
	prपूर्णांकk(KERN_DEBUG "VP Dev Config = 0x%0X\n",
	       cmd.buffer.block_data[7]);
	prपूर्णांकk(KERN_DEBUG "VP GPIO_DIR   = 0x%0X\n",
	       cmd.buffer.block_data[8]);
	prपूर्णांकk(KERN_DEBUG "VP GPIO_DATA  = 0x%0X\n",
	       cmd.buffer.block_data[9]);
	prपूर्णांकk(KERN_DEBUG "VP Ram ADDR H = 0x%0X\n",
	       cmd.buffer.block_data[10]);
	prपूर्णांकk(KERN_DEBUG "VP Ram ADDR L = 0x%0X\n",
	       cmd.buffer.block_data[11]);
	prपूर्णांकk(KERN_DEBUG "VP RAM Data   = 0x%0X\n",
	       cmd.buffer.block_data[12]);
	prपूर्णांकk(KERN_DEBUG "Do Call       = 0x%0X\n",
	       cmd.buffer.block_data[13]);

	अगर (cam->params.pnp_id.device_type == DEVICE_STV_672) अणु
		cmd.reg_count = 9;
		cmd.start = 0x0E;
		cpia2_send_command(cam, &cmd);
		prपूर्णांकk(KERN_DEBUG "VP Clock Ctrl = 0x%0X\n",
		       cmd.buffer.block_data[0]);
		prपूर्णांकk(KERN_DEBUG "VP Patch Rev  = 0x%0X\n",
		       cmd.buffer.block_data[1]);
		prपूर्णांकk(KERN_DEBUG "VP Vid Mode   = 0x%0X\n",
		       cmd.buffer.block_data[2]);
		prपूर्णांकk(KERN_DEBUG "VP Framerate  = 0x%0X\n",
		       cmd.buffer.block_data[3]);
		prपूर्णांकk(KERN_DEBUG "VP UserEffect = 0x%0X\n",
		       cmd.buffer.block_data[4]);
		prपूर्णांकk(KERN_DEBUG "VP White Bal  = 0x%0X\n",
		       cmd.buffer.block_data[5]);
		prपूर्णांकk(KERN_DEBUG "VP WB thresh  = 0x%0X\n",
		       cmd.buffer.block_data[6]);
		prपूर्णांकk(KERN_DEBUG "VP Exp Modes  = 0x%0X\n",
		       cmd.buffer.block_data[7]);
		prपूर्णांकk(KERN_DEBUG "VP Exp Target = 0x%0X\n",
		       cmd.buffer.block_data[8]);

		cmd.reg_count = 1;
		cmd.start = 0x1B;
		cpia2_send_command(cam, &cmd);
		prपूर्णांकk(KERN_DEBUG "VP FlickerMds = 0x%0X\n",
		       cmd.buffer.block_data[0]);
	पूर्ण अन्यथा अणु
		cmd.reg_count = 8 ;
		cmd.start = 0x0E;
		cpia2_send_command(cam, &cmd);
		prपूर्णांकk(KERN_DEBUG "VP Clock Ctrl = 0x%0X\n",
		       cmd.buffer.block_data[0]);
		prपूर्णांकk(KERN_DEBUG "VP Patch Rev  = 0x%0X\n",
		       cmd.buffer.block_data[1]);
		prपूर्णांकk(KERN_DEBUG "VP Vid Mode   = 0x%0X\n",
		       cmd.buffer.block_data[5]);
		prपूर्णांकk(KERN_DEBUG "VP Framerate  = 0x%0X\n",
		       cmd.buffer.block_data[6]);
		prपूर्णांकk(KERN_DEBUG "VP UserEffect = 0x%0X\n",
		       cmd.buffer.block_data[7]);

		cmd.reg_count = 1;
		cmd.start = CPIA2_VP5_EXPOSURE_TARGET;
		cpia2_send_command(cam, &cmd);
		prपूर्णांकk(KERN_DEBUG "VP5 Exp Target= 0x%0X\n",
		       cmd.buffer.block_data[0]);

		cmd.reg_count = 4;
		cmd.start = 0x3A;
		cpia2_send_command(cam, &cmd);
		prपूर्णांकk(KERN_DEBUG "VP5 MY Black  = 0x%0X\n",
		       cmd.buffer.block_data[0]);
		prपूर्णांकk(KERN_DEBUG "VP5 MCY Range = 0x%0X\n",
		       cmd.buffer.block_data[1]);
		prपूर्णांकk(KERN_DEBUG "VP5 MYCEILING = 0x%0X\n",
		       cmd.buffer.block_data[2]);
		prपूर्णांकk(KERN_DEBUG "VP5 MCUV Sat  = 0x%0X\n",
		       cmd.buffer.block_data[3]);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/******************************************************************************
 *
 *  reset_camera_काष्ठा
 *
 *  Sets all values to the शेषs
 *****************************************************************************/
अटल व्योम reset_camera_काष्ठा(काष्ठा camera_data *cam)
अणु
	/***
	 * The following parameter values are the शेषs from the रेजिस्टर map.
	 ***/
	cam->params.vp_params.lowlight_boost = 0;

	/* FlickerModes */
	cam->params.flicker_control.flicker_mode_req = NEVER_FLICKER;

	/* jpeg params */
	cam->params.compression.jpeg_options = CPIA2_VC_VC_JPEG_OPT_DEFAULT;
	cam->params.compression.creep_period = 2;
	cam->params.compression.user_squeeze = 20;
	cam->params.compression.inhibit_htables = false;

	/* gpio params */
	cam->params.vp_params.gpio_direction = 0;	/* ग_लिखो, the शेष safe mode */
	cam->params.vp_params.gpio_data = 0;

	/* Target kb params */
	cam->params.vc_params.quality = 100;

	/***
	 * Set Sensor FPS as fast as possible.
	 ***/
	अगर(cam->params.pnp_id.device_type == DEVICE_STV_672) अणु
		अगर(cam->params.version.sensor_flags == CPIA2_VP_SENSOR_FLAGS_500)
			cam->params.vp_params.frame_rate = CPIA2_VP_FRAMERATE_15;
		अन्यथा
			cam->params.vp_params.frame_rate = CPIA2_VP_FRAMERATE_30;
	पूर्ण अन्यथा अणु
		cam->params.vp_params.frame_rate = CPIA2_VP_FRAMERATE_30;
	पूर्ण

	/***
	 * Set शेष video mode as large as possible :
	 * क्रम vga sensor set to vga, क्रम cअगर sensor set to CIF.
	 ***/
	अगर (cam->params.version.sensor_flags == CPIA2_VP_SENSOR_FLAGS_500) अणु
		cam->sensor_type = CPIA2_SENSOR_500;
		cam->video_size = VIDEOSIZE_VGA;
		cam->params.roi.width = STV_IMAGE_VGA_COLS;
		cam->params.roi.height = STV_IMAGE_VGA_ROWS;
	पूर्ण अन्यथा अणु
		cam->sensor_type = CPIA2_SENSOR_410;
		cam->video_size = VIDEOSIZE_CIF;
		cam->params.roi.width = STV_IMAGE_CIF_COLS;
		cam->params.roi.height = STV_IMAGE_CIF_ROWS;
	पूर्ण

	cam->width = cam->params.roi.width;
	cam->height = cam->params.roi.height;
पूर्ण

/******************************************************************************
 *
 *  cpia2_init_camera_काष्ठा
 *
 *  Initializes camera काष्ठा, करोes not call reset to fill in शेषs.
 *****************************************************************************/
काष्ठा camera_data *cpia2_init_camera_काष्ठा(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा camera_data *cam;

	cam = kzalloc(माप(*cam), GFP_KERNEL);

	अगर (!cam) अणु
		ERR("couldn't kmalloc cpia2 struct\n");
		वापस शून्य;
	पूर्ण

	cam->v4l2_dev.release = cpia2_camera_release;
	अगर (v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &cam->v4l2_dev) < 0) अणु
		v4l2_err(&cam->v4l2_dev, "couldn't register v4l2_device\n");
		kमुक्त(cam);
		वापस शून्य;
	पूर्ण

	mutex_init(&cam->v4l2_lock);
	init_रुकोqueue_head(&cam->wq_stream);

	वापस cam;
पूर्ण

/******************************************************************************
 *
 *  cpia2_init_camera
 *
 *  Initializes camera.
 *****************************************************************************/
पूर्णांक cpia2_init_camera(काष्ठा camera_data *cam)
अणु
	DBG("Start\n");

	cam->mmapped = false;

	/* Get sensor and asic types beक्रमe reset. */
	cpia2_set_high_घातer(cam);
	cpia2_get_version_info(cam);
	अगर (cam->params.version.asic_id != CPIA2_ASIC_672) अणु
		ERR("Device IO error (asicID has incorrect value of 0x%X\n",
		    cam->params.version.asic_id);
		वापस -ENODEV;
	पूर्ण

	/* Set GPIO direction and data to a safe state. */
	cpia2_करो_command(cam, CPIA2_CMD_SET_VC_MP_GPIO_सूचीECTION,
			 TRANSFER_WRITE, 0);
	cpia2_करो_command(cam, CPIA2_CMD_SET_VC_MP_GPIO_DATA,
			 TRANSFER_WRITE, 0);

	/* resetting काष्ठा requires version info क्रम sensor and asic types */
	reset_camera_काष्ठा(cam);

	cpia2_set_low_घातer(cam);

	DBG("End\n");

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  cpia2_allocate_buffers
 *
 *****************************************************************************/
पूर्णांक cpia2_allocate_buffers(काष्ठा camera_data *cam)
अणु
	पूर्णांक i;

	अगर(!cam->buffers) अणु
		u32 size = cam->num_frames*माप(काष्ठा framebuf);
		cam->buffers = kदो_स्मृति(size, GFP_KERNEL);
		अगर(!cam->buffers) अणु
			ERR("couldn't kmalloc frame buffer structures\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर(!cam->frame_buffer) अणु
		cam->frame_buffer = rvदो_स्मृति(cam->frame_size*cam->num_frames);
		अगर (!cam->frame_buffer) अणु
			ERR("couldn't vmalloc frame buffer data area\n");
			kमुक्त(cam->buffers);
			cam->buffers = शून्य;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	क्रम(i=0; i<cam->num_frames-1; ++i) अणु
		cam->buffers[i].next = &cam->buffers[i+1];
		cam->buffers[i].data = cam->frame_buffer +i*cam->frame_size;
		cam->buffers[i].status = FRAME_EMPTY;
		cam->buffers[i].length = 0;
		cam->buffers[i].max_length = 0;
		cam->buffers[i].num = i;
	पूर्ण
	cam->buffers[i].next = cam->buffers;
	cam->buffers[i].data = cam->frame_buffer +i*cam->frame_size;
	cam->buffers[i].status = FRAME_EMPTY;
	cam->buffers[i].length = 0;
	cam->buffers[i].max_length = 0;
	cam->buffers[i].num = i;
	cam->curbuff = cam->buffers;
	cam->workbuff = cam->curbuff->next;
	DBG("buffers=%p, curbuff=%p, workbuff=%p\n", cam->buffers, cam->curbuff,
	    cam->workbuff);
	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  cpia2_मुक्त_buffers
 *
 *****************************************************************************/
व्योम cpia2_मुक्त_buffers(काष्ठा camera_data *cam)
अणु
	अगर(cam->buffers) अणु
		kमुक्त(cam->buffers);
		cam->buffers = शून्य;
	पूर्ण
	अगर(cam->frame_buffer) अणु
		rvमुक्त(cam->frame_buffer, cam->frame_size*cam->num_frames);
		cam->frame_buffer = शून्य;
	पूर्ण
पूर्ण

/******************************************************************************
 *
 *  cpia2_पढ़ो
 *
 *****************************************************************************/
दीर्घ cpia2_पढ़ो(काष्ठा camera_data *cam,
		अक्षर __user *buf, अचिन्हित दीर्घ count, पूर्णांक noblock)
अणु
	काष्ठा framebuf *frame;

	अगर (!count)
		वापस 0;

	अगर (!buf) अणु
		ERR("%s: buffer NULL\n",__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!cam) अणु
		ERR("%s: Internal error, camera_data NULL!\n",__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!cam->streaming) अणु
		/* Start streaming */
		cpia2_usb_stream_start(cam,
				       cam->params.camera_state.stream_mode);
	पूर्ण

	/* Copy cam->curbuff in हाल it changes जबतक we're processing */
	frame = cam->curbuff;
	अगर (noblock && frame->status != FRAME_READY) अणु
		वापस -EAGAIN;
	पूर्ण

	अगर (frame->status != FRAME_READY) अणु
		mutex_unlock(&cam->v4l2_lock);
		रुको_event_पूर्णांकerruptible(cam->wq_stream,
			       !video_is_रेजिस्टरed(&cam->vdev) ||
			       (frame = cam->curbuff)->status == FRAME_READY);
		mutex_lock(&cam->v4l2_lock);
		अगर (संकेत_pending(current))
			वापस -ERESTARTSYS;
		अगर (!video_is_रेजिस्टरed(&cam->vdev))
			वापस 0;
	पूर्ण

	/* copy data to user space */
	अगर (frame->length > count)
		वापस -EFAULT;
	अगर (copy_to_user(buf, frame->data, frame->length))
		वापस -EFAULT;

	count = frame->length;

	frame->status = FRAME_EMPTY;

	वापस count;
पूर्ण

/******************************************************************************
 *
 *  cpia2_poll
 *
 *****************************************************************************/
__poll_t cpia2_poll(काष्ठा camera_data *cam, काष्ठा file *filp,
			poll_table *रुको)
अणु
	__poll_t status = v4l2_ctrl_poll(filp, रुको);

	अगर ((poll_requested_events(रुको) & (EPOLLIN | EPOLLRDNORM)) &&
			!cam->streaming) अणु
		/* Start streaming */
		cpia2_usb_stream_start(cam,
				       cam->params.camera_state.stream_mode);
	पूर्ण

	poll_रुको(filp, &cam->wq_stream, रुको);

	अगर (cam->curbuff->status == FRAME_READY)
		status |= EPOLLIN | EPOLLRDNORM;

	वापस status;
पूर्ण

/******************************************************************************
 *
 *  cpia2_remap_buffer
 *
 *****************************************************************************/
पूर्णांक cpia2_remap_buffer(काष्ठा camera_data *cam, काष्ठा vm_area_काष्ठा *vma)
अणु
	स्थिर अक्षर *adr = (स्थिर अक्षर *)vma->vm_start;
	अचिन्हित दीर्घ size = vma->vm_end-vma->vm_start;
	अचिन्हित दीर्घ start_offset = vma->vm_pgoff << PAGE_SHIFT;
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) adr;
	अचिन्हित दीर्घ page, pos;

	DBG("mmap offset:%ld size:%ld\n", start_offset, size);

	अगर (!video_is_रेजिस्टरed(&cam->vdev))
		वापस -ENODEV;

	अगर (size > cam->frame_size*cam->num_frames  ||
	    (start_offset % cam->frame_size) != 0 ||
	    (start_offset+size > cam->frame_size*cam->num_frames))
		वापस -EINVAL;

	pos = ((अचिन्हित दीर्घ) (cam->frame_buffer)) + start_offset;
	जबतक (size > 0) अणु
		page = kvirt_to_pa(pos);
		अगर (remap_pfn_range(vma, start, page >> PAGE_SHIFT, PAGE_SIZE, PAGE_SHARED))
			वापस -EAGAIN;
		start += PAGE_SIZE;
		pos += PAGE_SIZE;
		अगर (size > PAGE_SIZE)
			size -= PAGE_SIZE;
		अन्यथा
			size = 0;
	पूर्ण

	cam->mmapped = true;
	वापस 0;
पूर्ण
