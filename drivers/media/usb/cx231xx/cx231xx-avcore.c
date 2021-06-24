<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   cx231xx_avcore.c - driver क्रम Conexant Cx23100/101/102
		      USB video capture devices

   Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>

   This program contains the specअगरic code to control the avdecoder chip and
   other related usb control functions क्रम cx231xx based chipset.

 */

#समावेश "cx231xx.h"
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <media/tuner.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "cx231xx-dif.h"

#घोषणा TUNER_MODE_FM_RADIO 0
/******************************************************************************
			-: BLOCK ARRANGEMENT :-
	I2S block ----------------------|
	[I2S audio]			|
					|
	Analog Front End --> Direct IF -|-> Cx25840 --> Audio
	[video & audio]			|   [Audio]
					|
					|-> Cx25840 --> Video
					    [Video]

*******************************************************************************/
/******************************************************************************
 *                    VERVE REGISTER                                          *
 *									      *
 ******************************************************************************/
अटल पूर्णांक verve_ग_लिखो_byte(काष्ठा cx231xx *dev, u8 saddr, u8 data)
अणु
	वापस cx231xx_ग_लिखो_i2c_data(dev, VERVE_I2C_ADDRESS,
					saddr, 1, data, 1);
पूर्ण

अटल पूर्णांक verve_पढ़ो_byte(काष्ठा cx231xx *dev, u8 saddr, u8 *data)
अणु
	पूर्णांक status;
	u32 temp = 0;

	status = cx231xx_पढ़ो_i2c_data(dev, VERVE_I2C_ADDRESS,
					saddr, 1, &temp, 1);
	*data = (u8) temp;
	वापस status;
पूर्ण
व्योम initGPIO(काष्ठा cx231xx *dev)
अणु
	u32 _gpio_direction = 0;
	u32 value = 0;
	u8 val = 0;

	_gpio_direction = _gpio_direction & 0xFC0003FF;
	_gpio_direction = _gpio_direction | 0x03FDFC00;
	cx231xx_send_gpio_cmd(dev, _gpio_direction, (u8 *)&value, 4, 0, 0);

	verve_पढ़ो_byte(dev, 0x07, &val);
	dev_dbg(dev->dev, "verve_read_byte address0x07=0x%x\n", val);
	verve_ग_लिखो_byte(dev, 0x07, 0xF4);
	verve_पढ़ो_byte(dev, 0x07, &val);
	dev_dbg(dev->dev, "verve_read_byte address0x07=0x%x\n", val);

	cx231xx_capture_start(dev, 1, Vbi);

	cx231xx_mode_रेजिस्टर(dev, EP_MODE_SET, 0x0500FE00);
	cx231xx_mode_रेजिस्टर(dev, GBULK_BIT_EN, 0xFFFDFFFF);

पूर्ण
व्योम uninitGPIO(काष्ठा cx231xx *dev)
अणु
	u8 value[4] = अणु 0, 0, 0, 0 पूर्ण;

	cx231xx_capture_start(dev, 0, Vbi);
	verve_ग_लिखो_byte(dev, 0x07, 0x14);
	cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
			0x68, value, 4);
पूर्ण

/******************************************************************************
 *                    A F E - B L O C K    C O N T R O L   functions          *
 *				[ANALOG FRONT END]			      *
 ******************************************************************************/
अटल पूर्णांक afe_ग_लिखो_byte(काष्ठा cx231xx *dev, u16 saddr, u8 data)
अणु
	वापस cx231xx_ग_लिखो_i2c_data(dev, AFE_DEVICE_ADDRESS,
					saddr, 2, data, 1);
पूर्ण

अटल पूर्णांक afe_पढ़ो_byte(काष्ठा cx231xx *dev, u16 saddr, u8 *data)
अणु
	पूर्णांक status;
	u32 temp = 0;

	status = cx231xx_पढ़ो_i2c_data(dev, AFE_DEVICE_ADDRESS,
					saddr, 2, &temp, 1);
	*data = (u8) temp;
	वापस status;
पूर्ण

पूर्णांक cx231xx_afe_init_super_block(काष्ठा cx231xx *dev, u32 ref_count)
अणु
	पूर्णांक status = 0;
	u8 temp = 0;
	u8 afe_घातer_status = 0;
	पूर्णांक i = 0;

	/* super block initialize */
	temp = (u8) (ref_count & 0xff);
	status = afe_ग_लिखो_byte(dev, SUP_BLK_TUNE2, temp);
	अगर (status < 0)
		वापस status;

	status = afe_पढ़ो_byte(dev, SUP_BLK_TUNE2, &afe_घातer_status);
	अगर (status < 0)
		वापस status;

	temp = (u8) ((ref_count & 0x300) >> 8);
	temp |= 0x40;
	status = afe_ग_लिखो_byte(dev, SUP_BLK_TUNE1, temp);
	अगर (status < 0)
		वापस status;

	status = afe_ग_लिखो_byte(dev, SUP_BLK_PLL2, 0x0f);
	अगर (status < 0)
		वापस status;

	/* enable pll     */
	जबतक (afe_घातer_status != 0x18) अणु
		status = afe_ग_लिखो_byte(dev, SUP_BLK_PWRDN, 0x18);
		अगर (status < 0) अणु
			dev_dbg(dev->dev,
				"%s: Init Super Block failed in send cmd\n",
				__func__);
			अवरोध;
		पूर्ण

		status = afe_पढ़ो_byte(dev, SUP_BLK_PWRDN, &afe_घातer_status);
		afe_घातer_status &= 0xff;
		अगर (status < 0) अणु
			dev_dbg(dev->dev,
				"%s: Init Super Block failed in receive cmd\n",
				__func__);
			अवरोध;
		पूर्ण
		i++;
		अगर (i == 10) अणु
			dev_dbg(dev->dev,
				"%s: Init Super Block force break in loop !!!!\n",
				__func__);
			status = -1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (status < 0)
		वापस status;

	/* start tuning filter */
	status = afe_ग_लिखो_byte(dev, SUP_BLK_TUNE3, 0x40);
	अगर (status < 0)
		वापस status;

	msleep(5);

	/* निकास tuning */
	status = afe_ग_लिखो_byte(dev, SUP_BLK_TUNE3, 0x00);

	वापस status;
पूर्ण

पूर्णांक cx231xx_afe_init_channels(काष्ठा cx231xx *dev)
अणु
	पूर्णांक status = 0;

	/* घातer up all 3 channels, clear pd_buffer */
	status = afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH1, 0x00);
	status = afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH2, 0x00);
	status = afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH3, 0x00);

	/* Enable quantizer calibration */
	status = afe_ग_लिखो_byte(dev, ADC_COM_QUANT, 0x02);

	/* channel initialize, क्रमce modulator (fb) reset */
	status = afe_ग_लिखो_byte(dev, ADC_FB_FRCRST_CH1, 0x17);
	status = afe_ग_लिखो_byte(dev, ADC_FB_FRCRST_CH2, 0x17);
	status = afe_ग_लिखो_byte(dev, ADC_FB_FRCRST_CH3, 0x17);

	/* start quantilizer calibration  */
	status = afe_ग_लिखो_byte(dev, ADC_CAL_ATEST_CH1, 0x10);
	status = afe_ग_लिखो_byte(dev, ADC_CAL_ATEST_CH2, 0x10);
	status = afe_ग_लिखो_byte(dev, ADC_CAL_ATEST_CH3, 0x10);
	msleep(5);

	/* निकास modulator (fb) reset */
	status = afe_ग_लिखो_byte(dev, ADC_FB_FRCRST_CH1, 0x07);
	status = afe_ग_लिखो_byte(dev, ADC_FB_FRCRST_CH2, 0x07);
	status = afe_ग_लिखो_byte(dev, ADC_FB_FRCRST_CH3, 0x07);

	/* enable the pre_clamp in each channel क्रम single-ended input */
	status = afe_ग_लिखो_byte(dev, ADC_NTF_PRECLMP_EN_CH1, 0xf0);
	status = afe_ग_लिखो_byte(dev, ADC_NTF_PRECLMP_EN_CH2, 0xf0);
	status = afe_ग_लिखो_byte(dev, ADC_NTF_PRECLMP_EN_CH3, 0xf0);

	/* use diode instead of resistor, so set term_en to 0, res_en to 0  */
	status = cx231xx_reg_mask_ग_लिखो(dev, AFE_DEVICE_ADDRESS, 8,
				   ADC_QGAIN_RES_TRM_CH1, 3, 7, 0x00);
	status = cx231xx_reg_mask_ग_लिखो(dev, AFE_DEVICE_ADDRESS, 8,
				   ADC_QGAIN_RES_TRM_CH2, 3, 7, 0x00);
	status = cx231xx_reg_mask_ग_लिखो(dev, AFE_DEVICE_ADDRESS, 8,
				   ADC_QGAIN_RES_TRM_CH3, 3, 7, 0x00);

	/* dynamic element matching off */
	status = afe_ग_लिखो_byte(dev, ADC_DCSERVO_DEM_CH1, 0x03);
	status = afe_ग_लिखो_byte(dev, ADC_DCSERVO_DEM_CH2, 0x03);
	status = afe_ग_लिखो_byte(dev, ADC_DCSERVO_DEM_CH3, 0x03);

	वापस status;
पूर्ण

पूर्णांक cx231xx_afe_setup_AFE_क्रम_baseband(काष्ठा cx231xx *dev)
अणु
	u8 c_value = 0;
	पूर्णांक status = 0;

	status = afe_पढ़ो_byte(dev, ADC_PWRDN_CLAMP_CH2, &c_value);
	c_value &= (~(0x50));
	status = afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH2, c_value);

	वापस status;
पूर्ण

/*
	The Analog Front End in Cx231xx has 3 channels. These
	channels are used to share between dअगरferent inमाला_दो
	like tuner, s-video and composite inमाला_दो.

	channel 1 ----- pin 1  to pin4(in reg is 1-4)
	channel 2 ----- pin 5  to pin8(in reg is 5-8)
	channel 3 ----- pin 9 to pin 12(in reg is 9-11)
*/
पूर्णांक cx231xx_afe_set_input_mux(काष्ठा cx231xx *dev, u32 input_mux)
अणु
	u8 ch1_setting = (u8) input_mux;
	u8 ch2_setting = (u8) (input_mux >> 8);
	u8 ch3_setting = (u8) (input_mux >> 16);
	पूर्णांक status = 0;
	u8 value = 0;

	अगर (ch1_setting != 0) अणु
		status = afe_पढ़ो_byte(dev, ADC_INPUT_CH1, &value);
		value &= ~INPUT_SEL_MASK;
		value |= (ch1_setting - 1) << 4;
		value &= 0xff;
		status = afe_ग_लिखो_byte(dev, ADC_INPUT_CH1, value);
	पूर्ण

	अगर (ch2_setting != 0) अणु
		status = afe_पढ़ो_byte(dev, ADC_INPUT_CH2, &value);
		value &= ~INPUT_SEL_MASK;
		value |= (ch2_setting - 1) << 4;
		value &= 0xff;
		status = afe_ग_लिखो_byte(dev, ADC_INPUT_CH2, value);
	पूर्ण

	/* For ch3_setting, the value to put in the रेजिस्टर is
	   7 less than the input number */
	अगर (ch3_setting != 0) अणु
		status = afe_पढ़ो_byte(dev, ADC_INPUT_CH3, &value);
		value &= ~INPUT_SEL_MASK;
		value |= (ch3_setting - 1) << 4;
		value &= 0xff;
		status = afe_ग_लिखो_byte(dev, ADC_INPUT_CH3, value);
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक cx231xx_afe_set_mode(काष्ठा cx231xx *dev, क्रमागत AFE_MODE mode)
अणु
	पूर्णांक status = 0;

	/*
	* FIXME: We need to implement the AFE code क्रम LOW IF and क्रम HI IF.
	* Currently, only baseband works.
	*/

	चयन (mode) अणु
	हाल AFE_MODE_LOW_IF:
		cx231xx_Setup_AFE_क्रम_LowIF(dev);
		अवरोध;
	हाल AFE_MODE_BASEBAND:
		status = cx231xx_afe_setup_AFE_क्रम_baseband(dev);
		अवरोध;
	हाल AFE_MODE_EU_HI_IF:
		/* SetupAFEक्रमEuHiIF(); */
		अवरोध;
	हाल AFE_MODE_US_HI_IF:
		/* SetupAFEक्रमUsHiIF(); */
		अवरोध;
	हाल AFE_MODE_JAPAN_HI_IF:
		/* SetupAFEक्रमJapanHiIF(); */
		अवरोध;
	पूर्ण

	अगर ((mode != dev->afe_mode) &&
		(dev->video_input == CX231XX_VMUX_TELEVISION))
		status = cx231xx_afe_adjust_ref_count(dev,
						     CX231XX_VMUX_TELEVISION);

	dev->afe_mode = mode;

	वापस status;
पूर्ण

पूर्णांक cx231xx_afe_update_घातer_control(काष्ठा cx231xx *dev,
					क्रमागत AV_MODE avmode)
अणु
	u8 afe_घातer_status = 0;
	पूर्णांक status = 0;

	चयन (dev->model) अणु
	हाल CX231XX_BOARD_CNXT_CARRAERA:
	हाल CX231XX_BOARD_CNXT_RDE_250:
	हाल CX231XX_BOARD_CNXT_SHELBY:
	हाल CX231XX_BOARD_CNXT_RDU_250:
	हाल CX231XX_BOARD_CNXT_RDE_253S:
	हाल CX231XX_BOARD_CNXT_RDU_253S:
	हाल CX231XX_BOARD_CNXT_VIDEO_GRABBER:
	हाल CX231XX_BOARD_HAUPPAUGE_EXETER:
	हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xx:
	हाल CX231XX_BOARD_HAUPPAUGE_USBLIVE2:
	हाल CX231XX_BOARD_PV_PLAYTV_USB_HYBRID:
	हाल CX231XX_BOARD_HAUPPAUGE_USB2_FM_PAL:
	हाल CX231XX_BOARD_HAUPPAUGE_USB2_FM_NTSC:
	हाल CX231XX_BOARD_OTG102:
		अगर (avmode == POLARIS_AVMODE_ANALOGT_TV) अणु
			जबतक (afe_घातer_status != (FLD_PWRDN_TUNING_BIAS |
						FLD_PWRDN_ENABLE_PLL)) अणु
				status = afe_ग_लिखो_byte(dev, SUP_BLK_PWRDN,
							FLD_PWRDN_TUNING_BIAS |
							FLD_PWRDN_ENABLE_PLL);
				status |= afe_पढ़ो_byte(dev, SUP_BLK_PWRDN,
							&afe_घातer_status);
				अगर (status < 0)
					अवरोध;
			पूर्ण

			status = afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH1,
							0x00);
			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH2,
							0x00);
			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH3,
							0x00);
		पूर्ण अन्यथा अगर (avmode == POLARIS_AVMODE_DIGITAL) अणु
			status = afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH1,
							0x70);
			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH2,
							0x70);
			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH3,
							0x70);

			status |= afe_पढ़ो_byte(dev, SUP_BLK_PWRDN,
						  &afe_घातer_status);
			afe_घातer_status |= FLD_PWRDN_PD_BANDGAP |
						FLD_PWRDN_PD_BIAS |
						FLD_PWRDN_PD_TUNECK;
			status |= afe_ग_लिखो_byte(dev, SUP_BLK_PWRDN,
						   afe_घातer_status);
		पूर्ण अन्यथा अगर (avmode == POLARIS_AVMODE_ENXTERNAL_AV) अणु
			जबतक (afe_घातer_status != (FLD_PWRDN_TUNING_BIAS |
						FLD_PWRDN_ENABLE_PLL)) अणु
				status = afe_ग_लिखो_byte(dev, SUP_BLK_PWRDN,
							FLD_PWRDN_TUNING_BIAS |
							FLD_PWRDN_ENABLE_PLL);
				status |= afe_पढ़ो_byte(dev, SUP_BLK_PWRDN,
							&afe_घातer_status);
				अगर (status < 0)
					अवरोध;
			पूर्ण

			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH1,
						0x00);
			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH2,
						0x00);
			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH3,
						0x00);
		पूर्ण अन्यथा अणु
			dev_dbg(dev->dev, "Invalid AV mode input\n");
			status = -1;
		पूर्ण
		अवरोध;
	शेष:
		अगर (avmode == POLARIS_AVMODE_ANALOGT_TV) अणु
			जबतक (afe_घातer_status != (FLD_PWRDN_TUNING_BIAS |
						FLD_PWRDN_ENABLE_PLL)) अणु
				status = afe_ग_लिखो_byte(dev, SUP_BLK_PWRDN,
							FLD_PWRDN_TUNING_BIAS |
							FLD_PWRDN_ENABLE_PLL);
				status |= afe_पढ़ो_byte(dev, SUP_BLK_PWRDN,
							&afe_घातer_status);
				अगर (status < 0)
					अवरोध;
			पूर्ण

			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH1,
							0x40);
			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH2,
							0x40);
			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH3,
							0x00);
		पूर्ण अन्यथा अगर (avmode == POLARIS_AVMODE_DIGITAL) अणु
			status = afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH1,
							0x70);
			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH2,
							0x70);
			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH3,
							0x70);

			status |= afe_पढ़ो_byte(dev, SUP_BLK_PWRDN,
						       &afe_घातer_status);
			afe_घातer_status |= FLD_PWRDN_PD_BANDGAP |
						FLD_PWRDN_PD_BIAS |
						FLD_PWRDN_PD_TUNECK;
			status |= afe_ग_लिखो_byte(dev, SUP_BLK_PWRDN,
							afe_घातer_status);
		पूर्ण अन्यथा अगर (avmode == POLARIS_AVMODE_ENXTERNAL_AV) अणु
			जबतक (afe_घातer_status != (FLD_PWRDN_TUNING_BIAS |
						FLD_PWRDN_ENABLE_PLL)) अणु
				status = afe_ग_लिखो_byte(dev, SUP_BLK_PWRDN,
							FLD_PWRDN_TUNING_BIAS |
							FLD_PWRDN_ENABLE_PLL);
				status |= afe_पढ़ो_byte(dev, SUP_BLK_PWRDN,
							&afe_घातer_status);
				अगर (status < 0)
					अवरोध;
			पूर्ण

			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH1,
							0x00);
			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH2,
							0x00);
			status |= afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH3,
							0x40);
		पूर्ण अन्यथा अणु
			dev_dbg(dev->dev, "Invalid AV mode input\n");
			status = -1;
		पूर्ण
	पूर्ण			/* चयन  */

	वापस status;
पूर्ण

पूर्णांक cx231xx_afe_adjust_ref_count(काष्ठा cx231xx *dev, u32 video_input)
अणु
	u8 input_mode = 0;
	u8 ntf_mode = 0;
	पूर्णांक status = 0;

	dev->video_input = video_input;

	अगर (video_input == CX231XX_VMUX_TELEVISION) अणु
		status = afe_पढ़ो_byte(dev, ADC_INPUT_CH3, &input_mode);
		status = afe_पढ़ो_byte(dev, ADC_NTF_PRECLMP_EN_CH3,
					&ntf_mode);
	पूर्ण अन्यथा अणु
		status = afe_पढ़ो_byte(dev, ADC_INPUT_CH1, &input_mode);
		status = afe_पढ़ो_byte(dev, ADC_NTF_PRECLMP_EN_CH1,
					&ntf_mode);
	पूर्ण

	input_mode = (ntf_mode & 0x3) | ((input_mode & 0x6) << 1);

	चयन (input_mode) अणु
	हाल SINGLE_ENDED:
		dev->afe_ref_count = 0x23C;
		अवरोध;
	हाल LOW_IF:
		dev->afe_ref_count = 0x24C;
		अवरोध;
	हाल EU_IF:
		dev->afe_ref_count = 0x258;
		अवरोध;
	हाल US_IF:
		dev->afe_ref_count = 0x260;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	status = cx231xx_afe_init_super_block(dev, dev->afe_ref_count);

	वापस status;
पूर्ण

/******************************************************************************
 *     V I D E O / A U D I O    D E C O D E R    C O N T R O L   functions    *
 ******************************************************************************/
अटल पूर्णांक vid_blk_ग_लिखो_byte(काष्ठा cx231xx *dev, u16 saddr, u8 data)
अणु
	वापस cx231xx_ग_लिखो_i2c_data(dev, VID_BLK_I2C_ADDRESS,
					saddr, 2, data, 1);
पूर्ण

अटल पूर्णांक vid_blk_पढ़ो_byte(काष्ठा cx231xx *dev, u16 saddr, u8 *data)
अणु
	पूर्णांक status;
	u32 temp = 0;

	status = cx231xx_पढ़ो_i2c_data(dev, VID_BLK_I2C_ADDRESS,
					saddr, 2, &temp, 1);
	*data = (u8) temp;
	वापस status;
पूर्ण

अटल पूर्णांक vid_blk_ग_लिखो_word(काष्ठा cx231xx *dev, u16 saddr, u32 data)
अणु
	वापस cx231xx_ग_लिखो_i2c_data(dev, VID_BLK_I2C_ADDRESS,
					saddr, 2, data, 4);
पूर्ण

अटल पूर्णांक vid_blk_पढ़ो_word(काष्ठा cx231xx *dev, u16 saddr, u32 *data)
अणु
	वापस cx231xx_पढ़ो_i2c_data(dev, VID_BLK_I2C_ADDRESS,
					saddr, 2, data, 4);
पूर्ण
पूर्णांक cx231xx_check_fw(काष्ठा cx231xx *dev)
अणु
	u8 temp = 0;
	पूर्णांक status = 0;
	status = vid_blk_पढ़ो_byte(dev, DL_CTL_ADDRESS_LOW, &temp);
	अगर (status < 0)
		वापस status;
	अन्यथा
		वापस temp;

पूर्ण

पूर्णांक cx231xx_set_video_input_mux(काष्ठा cx231xx *dev, u8 input)
अणु
	पूर्णांक status = 0;

	चयन (INPUT(input)->type) अणु
	हाल CX231XX_VMUX_COMPOSITE1:
	हाल CX231XX_VMUX_SVIDEO:
		अगर ((dev->current_pcb_config.type == USB_BUS_POWER) &&
		    (dev->घातer_mode != POLARIS_AVMODE_ENXTERNAL_AV)) अणु
			/* External AV */
			status = cx231xx_set_घातer_mode(dev,
					POLARIS_AVMODE_ENXTERNAL_AV);
			अगर (status < 0) अणु
				dev_err(dev->dev,
					"%s: Failed to set Power - errCode [%d]!\n",
					__func__, status);
				वापस status;
			पूर्ण
		पूर्ण
		status = cx231xx_set_decoder_video_input(dev,
							 INPUT(input)->type,
							 INPUT(input)->vmux);
		अवरोध;
	हाल CX231XX_VMUX_TELEVISION:
	हाल CX231XX_VMUX_CABLE:
		अगर ((dev->current_pcb_config.type == USB_BUS_POWER) &&
		    (dev->घातer_mode != POLARIS_AVMODE_ANALOGT_TV)) अणु
			/* Tuner */
			status = cx231xx_set_घातer_mode(dev,
						POLARIS_AVMODE_ANALOGT_TV);
			अगर (status < 0) अणु
				dev_err(dev->dev,
					"%s: Failed to set Power - errCode [%d]!\n",
					__func__, status);
				वापस status;
			पूर्ण
		पूर्ण
		चयन (dev->model) अणु /* i2c device tuners */
		हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx:
		हाल CX231XX_BOARD_HAUPPAUGE_935C:
		हाल CX231XX_BOARD_HAUPPAUGE_955Q:
		हाल CX231XX_BOARD_HAUPPAUGE_975:
		हाल CX231XX_BOARD_EVROMEDIA_FULL_HYBRID_FULLHD:
			status = cx231xx_set_decoder_video_input(dev,
							CX231XX_VMUX_TELEVISION,
							INPUT(input)->vmux);
			अवरोध;
		शेष:
			अगर (dev->tuner_type == TUNER_NXP_TDA18271)
				status = cx231xx_set_decoder_video_input(dev,
							CX231XX_VMUX_TELEVISION,
							INPUT(input)->vmux);
			अन्यथा
				status = cx231xx_set_decoder_video_input(dev,
							CX231XX_VMUX_COMPOSITE1,
							INPUT(input)->vmux);
			अवरोध;
		पूर्ण

		अवरोध;
	शेष:
		dev_err(dev->dev, "%s: Unknown Input %d !\n",
			__func__, INPUT(input)->type);
		अवरोध;
	पूर्ण

	/* save the selection */
	dev->video_input = input;

	वापस status;
पूर्ण

पूर्णांक cx231xx_set_decoder_video_input(काष्ठा cx231xx *dev,
				u8 pin_type, u8 input)
अणु
	पूर्णांक status = 0;
	u32 value = 0;

	अगर (pin_type != dev->video_input) अणु
		status = cx231xx_afe_adjust_ref_count(dev, pin_type);
		अगर (status < 0) अणु
			dev_err(dev->dev,
				"%s: adjust_ref_count :Failed to set AFE input mux - errCode [%d]!\n",
				__func__, status);
			वापस status;
		पूर्ण
	पूर्ण

	/* call afe block to set video inमाला_दो */
	status = cx231xx_afe_set_input_mux(dev, input);
	अगर (status < 0) अणु
		dev_err(dev->dev,
			"%s: set_input_mux :Failed to set AFE input mux - errCode [%d]!\n",
			__func__, status);
		वापस status;
	पूर्ण

	चयन (pin_type) अणु
	हाल CX231XX_VMUX_COMPOSITE1:
		status = vid_blk_पढ़ो_word(dev, AFE_CTRL, &value);
		value |= (0 << 13) | (1 << 4);
		value &= ~(1 << 5);

		/* set [24:23] [22:15] to 0  */
		value &= (~(0x1ff8000));
		/* set FUNC_MODE[24:23] = 2 IF_MOD[22:15] = 0  */
		value |= 0x1000000;
		status = vid_blk_ग_लिखो_word(dev, AFE_CTRL, value);

		status = vid_blk_पढ़ो_word(dev, OUT_CTRL1, &value);
		value |= (1 << 7);
		status = vid_blk_ग_लिखो_word(dev, OUT_CTRL1, value);

		/* Set output mode */
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							OUT_CTRL1,
							FLD_OUT_MODE,
							dev->board.output_mode);

		/* Tell DIF object to go to baseband mode  */
		status = cx231xx_dअगर_set_standard(dev, DIF_USE_BASEBAND);
		अगर (status < 0) अणु
			dev_err(dev->dev,
				"%s: cx231xx_dif set to By pass mode- errCode [%d]!\n",
				__func__, status);
			वापस status;
		पूर्ण

		/* Read the DFE_CTRL1 रेजिस्टर */
		status = vid_blk_पढ़ो_word(dev, DFE_CTRL1, &value);

		/* enable the VBI_GATE_EN */
		value |= FLD_VBI_GATE_EN;

		/* Enable the स्वतः-VGA enable */
		value |= FLD_VGA_AUTO_EN;

		/* Write it back */
		status = vid_blk_ग_लिखो_word(dev, DFE_CTRL1, value);

		/* Disable स्वतः config of रेजिस्टरs */
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
					VID_BLK_I2C_ADDRESS,
					MODE_CTRL, FLD_ACFG_DIS,
					cx231xx_set_field(FLD_ACFG_DIS, 1));

		/* Set CVBS input mode */
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
			VID_BLK_I2C_ADDRESS,
			MODE_CTRL, FLD_INPUT_MODE,
			cx231xx_set_field(FLD_INPUT_MODE, INPUT_MODE_CVBS_0));
		अवरोध;
	हाल CX231XX_VMUX_SVIDEO:
		/* Disable the use of  DIF */

		status = vid_blk_पढ़ो_word(dev, AFE_CTRL, &value);

		/* set [24:23] [22:15] to 0 */
		value &= (~(0x1ff8000));
		/* set FUNC_MODE[24:23] = 2
		IF_MOD[22:15] = 0 DCR_BYP_CH2[4:4] = 1; */
		value |= 0x1000010;
		status = vid_blk_ग_लिखो_word(dev, AFE_CTRL, value);

		/* Tell DIF object to go to baseband mode */
		status = cx231xx_dअगर_set_standard(dev, DIF_USE_BASEBAND);
		अगर (status < 0) अणु
			dev_err(dev->dev,
				"%s: cx231xx_dif set to By pass mode- errCode [%d]!\n",
				__func__, status);
			वापस status;
		पूर्ण

		/* Read the DFE_CTRL1 रेजिस्टर */
		status = vid_blk_पढ़ो_word(dev, DFE_CTRL1, &value);

		/* enable the VBI_GATE_EN */
		value |= FLD_VBI_GATE_EN;

		/* Enable the स्वतः-VGA enable */
		value |= FLD_VGA_AUTO_EN;

		/* Write it back */
		status = vid_blk_ग_लिखो_word(dev, DFE_CTRL1, value);

		/* Disable स्वतः config of रेजिस्टरs  */
		status =  cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
					VID_BLK_I2C_ADDRESS,
					MODE_CTRL, FLD_ACFG_DIS,
					cx231xx_set_field(FLD_ACFG_DIS, 1));

		/* Set YC input mode */
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
			VID_BLK_I2C_ADDRESS,
			MODE_CTRL,
			FLD_INPUT_MODE,
			cx231xx_set_field(FLD_INPUT_MODE, INPUT_MODE_YC_1));

		/* Chroma to ADC2 */
		status = vid_blk_पढ़ो_word(dev, AFE_CTRL, &value);
		value |= FLD_CHROMA_IN_SEL;	/* set the chroma in select */

		/* Clear VGA_SEL_CH2 and VGA_SEL_CH3 (bits 7 and 8)
		   This sets them to use video
		   rather than audio.  Only one of the two will be in use. */
		value &= ~(FLD_VGA_SEL_CH2 | FLD_VGA_SEL_CH3);

		status = vid_blk_ग_लिखो_word(dev, AFE_CTRL, value);

		status = cx231xx_afe_set_mode(dev, AFE_MODE_BASEBAND);
		अवरोध;
	हाल CX231XX_VMUX_TELEVISION:
	हाल CX231XX_VMUX_CABLE:
	शेष:
		/* TODO: Test अगर this is also needed क्रम xc2028/xc3028 */
		अगर (dev->board.tuner_type == TUNER_XC5000) अणु
			/* Disable the use of  DIF   */

			status = vid_blk_पढ़ो_word(dev, AFE_CTRL, &value);
			value |= (0 << 13) | (1 << 4);
			value &= ~(1 << 5);

			/* set [24:23] [22:15] to 0 */
			value &= (~(0x1FF8000));
			/* set FUNC_MODE[24:23] = 2 IF_MOD[22:15] = 0 */
			value |= 0x1000000;
			status = vid_blk_ग_लिखो_word(dev, AFE_CTRL, value);

			status = vid_blk_पढ़ो_word(dev, OUT_CTRL1, &value);
			value |= (1 << 7);
			status = vid_blk_ग_लिखो_word(dev, OUT_CTRL1, value);

			/* Set output mode */
			status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							OUT_CTRL1, FLD_OUT_MODE,
							dev->board.output_mode);

			/* Tell DIF object to go to baseband mode */
			status = cx231xx_dअगर_set_standard(dev,
							  DIF_USE_BASEBAND);
			अगर (status < 0) अणु
				dev_err(dev->dev,
					"%s: cx231xx_dif set to By pass mode- errCode [%d]!\n",
				       __func__, status);
				वापस status;
			पूर्ण

			/* Read the DFE_CTRL1 रेजिस्टर */
			status = vid_blk_पढ़ो_word(dev, DFE_CTRL1, &value);

			/* enable the VBI_GATE_EN */
			value |= FLD_VBI_GATE_EN;

			/* Enable the स्वतः-VGA enable */
			value |= FLD_VGA_AUTO_EN;

			/* Write it back */
			status = vid_blk_ग_लिखो_word(dev, DFE_CTRL1, value);

			/* Disable स्वतः config of रेजिस्टरs */
			status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
					VID_BLK_I2C_ADDRESS,
					MODE_CTRL, FLD_ACFG_DIS,
					cx231xx_set_field(FLD_ACFG_DIS, 1));

			/* Set CVBS input mode */
			status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
				VID_BLK_I2C_ADDRESS,
				MODE_CTRL, FLD_INPUT_MODE,
				cx231xx_set_field(FLD_INPUT_MODE,
						INPUT_MODE_CVBS_0));
		पूर्ण अन्यथा अणु
			/* Enable the DIF क्रम the tuner */

			/* Reinitialize the DIF */
			status = cx231xx_dअगर_set_standard(dev, dev->norm);
			अगर (status < 0) अणु
				dev_err(dev->dev,
					"%s: cx231xx_dif set to By pass mode- errCode [%d]!\n",
					__func__, status);
				वापस status;
			पूर्ण

			/* Make sure bypass is cleared */
			status = vid_blk_पढ़ो_word(dev, DIF_MISC_CTRL, &value);

			/* Clear the bypass bit */
			value &= ~FLD_DIF_DIF_BYPASS;

			/* Enable the use of the DIF block */
			status = vid_blk_ग_लिखो_word(dev, DIF_MISC_CTRL, value);

			/* Read the DFE_CTRL1 रेजिस्टर */
			status = vid_blk_पढ़ो_word(dev, DFE_CTRL1, &value);

			/* Disable the VBI_GATE_EN */
			value &= ~FLD_VBI_GATE_EN;

			/* Enable the स्वतः-VGA enable, AGC, and
			   set the skip count to 2 */
			value |= FLD_VGA_AUTO_EN | FLD_AGC_AUTO_EN | 0x00200000;

			/* Write it back */
			status = vid_blk_ग_लिखो_word(dev, DFE_CTRL1, value);

			/* Wait until AGC locks up */
			msleep(1);

			/* Disable the स्वतः-VGA enable AGC */
			value &= ~(FLD_VGA_AUTO_EN);

			/* Write it back */
			status = vid_blk_ग_लिखो_word(dev, DFE_CTRL1, value);

			/* Enable Polaris B0 AGC output */
			status = vid_blk_पढ़ो_word(dev, PIN_CTRL, &value);
			value |= (FLD_OEF_AGC_RF) |
				 (FLD_OEF_AGC_IFVGA) |
				 (FLD_OEF_AGC_IF);
			status = vid_blk_ग_लिखो_word(dev, PIN_CTRL, value);

			/* Set output mode */
			status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
						VID_BLK_I2C_ADDRESS,
						OUT_CTRL1, FLD_OUT_MODE,
						dev->board.output_mode);

			/* Disable स्वतः config of रेजिस्टरs */
			status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
					VID_BLK_I2C_ADDRESS,
					MODE_CTRL, FLD_ACFG_DIS,
					cx231xx_set_field(FLD_ACFG_DIS, 1));

			/* Set CVBS input mode */
			status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
				VID_BLK_I2C_ADDRESS,
				MODE_CTRL, FLD_INPUT_MODE,
				cx231xx_set_field(FLD_INPUT_MODE,
						INPUT_MODE_CVBS_0));

			/* Set some bits in AFE_CTRL so that channel 2 or 3
			 * is पढ़ोy to receive audio */
			/* Clear clamp क्रम channels 2 and 3      (bit 16-17) */
			/* Clear droop comp                      (bit 19-20) */
			/* Set VGA_SEL (क्रम audio control)       (bit 7-8) */
			status = vid_blk_पढ़ो_word(dev, AFE_CTRL, &value);

			/*Set Func mode:01-DIF 10-baseband 11-YUV*/
			value &= (~(FLD_FUNC_MODE));
			value |= 0x800000;

			value |= FLD_VGA_SEL_CH3 | FLD_VGA_SEL_CH2;

			status = vid_blk_ग_लिखो_word(dev, AFE_CTRL, value);

			अगर (dev->tuner_type == TUNER_NXP_TDA18271) अणु
				status = vid_blk_पढ़ो_word(dev, PIN_CTRL,
				 &value);
				status = vid_blk_ग_लिखो_word(dev, PIN_CTRL,
				 (value & 0xFFFFFFEF));
			पूर्ण

			अवरोध;

		पूर्ण
		अवरोध;
	पूर्ण

	/* Set raw VBI mode */
	status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
				VID_BLK_I2C_ADDRESS,
				OUT_CTRL1, FLD_VBIHACTRAW_EN,
				cx231xx_set_field(FLD_VBIHACTRAW_EN, 1));

	status = vid_blk_पढ़ो_word(dev, OUT_CTRL1, &value);
	अगर (value & 0x02) अणु
		value |= (1 << 19);
		status = vid_blk_ग_लिखो_word(dev, OUT_CTRL1, value);
	पूर्ण

	वापस status;
पूर्ण

व्योम cx231xx_enable656(काष्ठा cx231xx *dev)
अणु
	u8 temp = 0;
	/*enable TS1 data[0:7] as output to export 656*/

	vid_blk_ग_लिखो_byte(dev, TS1_PIN_CTL0, 0xFF);

	/*enable TS1 घड़ी as output to export 656*/

	vid_blk_पढ़ो_byte(dev, TS1_PIN_CTL1, &temp);
	temp = temp|0x04;

	vid_blk_ग_लिखो_byte(dev, TS1_PIN_CTL1, temp);
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_enable656);

व्योम cx231xx_disable656(काष्ठा cx231xx *dev)
अणु
	u8 temp = 0;

	vid_blk_ग_लिखो_byte(dev, TS1_PIN_CTL0, 0x00);

	vid_blk_पढ़ो_byte(dev, TS1_PIN_CTL1, &temp);
	temp = temp&0xFB;

	vid_blk_ग_लिखो_byte(dev, TS1_PIN_CTL1, temp);
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_disable656);

/*
 * Handle any video-mode specअगरic overrides that are dअगरferent
 * on a per video standards basis after touching the MODE_CTRL
 * रेजिस्टर which resets many values क्रम स्वतःdetect
 */
पूर्णांक cx231xx_करो_mode_ctrl_overrides(काष्ठा cx231xx *dev)
अणु
	पूर्णांक status = 0;

	dev_dbg(dev->dev, "%s: 0x%x\n",
		__func__, (अचिन्हित पूर्णांक)dev->norm);

	/* Change the DFE_CTRL3 bp_percent to fix flagging */
	status = vid_blk_ग_लिखो_word(dev, DFE_CTRL3, 0xCD3F0280);

	अगर (dev->norm & (V4L2_STD_NTSC | V4L2_STD_PAL_M)) अणु
		dev_dbg(dev->dev, "%s: NTSC\n", __func__);

		/* Move the बंद caption lines out of active video,
		   adjust the active video start poपूर्णांक */
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_VBLANK_CNT, 0x18);
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_VACTIVE_CNT,
							0x1E7000);
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_V656BLANK_CNT,
							0x1C000000);

		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							HORIZ_TIM_CTRL,
							FLD_HBLANK_CNT,
							cx231xx_set_field
							(FLD_HBLANK_CNT, 0x79));

	पूर्ण अन्यथा अगर (dev->norm & V4L2_STD_SECAM) अणु
		dev_dbg(dev->dev, "%s: SECAM\n", __func__);
		status =  cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_VBLANK_CNT, 0x20);
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_VACTIVE_CNT,
							cx231xx_set_field
							(FLD_VACTIVE_CNT,
							 0x244));
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_V656BLANK_CNT,
							cx231xx_set_field
							(FLD_V656BLANK_CNT,
							0x24));
		/* Adjust the active video horizontal start poपूर्णांक */
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							HORIZ_TIM_CTRL,
							FLD_HBLANK_CNT,
							cx231xx_set_field
							(FLD_HBLANK_CNT, 0x85));
	पूर्ण अन्यथा अणु
		dev_dbg(dev->dev, "%s: PAL\n", __func__);
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_VBLANK_CNT, 0x20);
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_VACTIVE_CNT,
							cx231xx_set_field
							(FLD_VACTIVE_CNT,
							 0x244));
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							VERT_TIM_CTRL,
							FLD_V656BLANK_CNT,
							cx231xx_set_field
							(FLD_V656BLANK_CNT,
							0x24));
		/* Adjust the active video horizontal start poपूर्णांक */
		status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
							VID_BLK_I2C_ADDRESS,
							HORIZ_TIM_CTRL,
							FLD_HBLANK_CNT,
							cx231xx_set_field
							(FLD_HBLANK_CNT, 0x85));

	पूर्ण

	वापस status;
पूर्ण

पूर्णांक cx231xx_unmute_audio(काष्ठा cx231xx *dev)
अणु
	वापस vid_blk_ग_लिखो_byte(dev, PATH1_VOL_CTL, 0x24);
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_unmute_audio);

अटल पूर्णांक stopAudioFirmware(काष्ठा cx231xx *dev)
अणु
	वापस vid_blk_ग_लिखो_byte(dev, DL_CTL_CONTROL, 0x03);
पूर्ण

अटल पूर्णांक restartAudioFirmware(काष्ठा cx231xx *dev)
अणु
	वापस vid_blk_ग_लिखो_byte(dev, DL_CTL_CONTROL, 0x13);
पूर्ण

पूर्णांक cx231xx_set_audio_input(काष्ठा cx231xx *dev, u8 input)
अणु
	पूर्णांक status = 0;
	क्रमागत AUDIO_INPUT ainput = AUDIO_INPUT_LINE;

	चयन (INPUT(input)->amux) अणु
	हाल CX231XX_AMUX_VIDEO:
		ainput = AUDIO_INPUT_TUNER_TV;
		अवरोध;
	हाल CX231XX_AMUX_LINE_IN:
		status = cx231xx_i2s_blk_set_audio_input(dev, input);
		ainput = AUDIO_INPUT_LINE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	status = cx231xx_set_audio_decoder_input(dev, ainput);

	वापस status;
पूर्ण

पूर्णांक cx231xx_set_audio_decoder_input(काष्ठा cx231xx *dev,
				    क्रमागत AUDIO_INPUT audio_input)
अणु
	u32 dwval;
	पूर्णांक status;
	u8 gen_ctrl;
	u32 value = 0;

	/* Put it in soft reset   */
	status = vid_blk_पढ़ो_byte(dev, GENERAL_CTL, &gen_ctrl);
	gen_ctrl |= 1;
	status = vid_blk_ग_लिखो_byte(dev, GENERAL_CTL, gen_ctrl);

	चयन (audio_input) अणु
	हाल AUDIO_INPUT_LINE:
		/* setup AUD_IO control from Merlin paralle output */
		value = cx231xx_set_field(FLD_AUD_CHAN1_SRC,
					  AUD_CHAN_SRC_PARALLEL);
		status = vid_blk_ग_लिखो_word(dev, AUD_IO_CTRL, value);

		/* setup input to Merlin, SRC2 connect to AC97
		   bypass upsample-by-2, slave mode, sony mode, left justअगरy
		   adr 091c, dat 01000000 */
		status = vid_blk_पढ़ो_word(dev, AC97_CTL, &dwval);

		status = vid_blk_ग_लिखो_word(dev, AC97_CTL,
					   (dwval | FLD_AC97_UP2X_BYPASS));

		/* select the parallel1 and SRC3 */
		status = vid_blk_ग_लिखो_word(dev, BAND_OUT_SEL,
				cx231xx_set_field(FLD_SRC3_IN_SEL, 0x0) |
				cx231xx_set_field(FLD_SRC3_CLK_SEL, 0x0) |
				cx231xx_set_field(FLD_PARALLEL1_SRC_SEL, 0x0));

		/* unmute all, AC97 in, independence mode
		   adr 08d0, data 0x00063073 */
		status = vid_blk_ग_लिखो_word(dev, DL_CTL, 0x3000001);
		status = vid_blk_ग_लिखो_word(dev, PATH1_CTL1, 0x00063073);

		/* set AVC maximum threshold, adr 08d4, dat ffff0024 */
		status = vid_blk_पढ़ो_word(dev, PATH1_VOL_CTL, &dwval);
		status = vid_blk_ग_लिखो_word(dev, PATH1_VOL_CTL,
					   (dwval | FLD_PATH1_AVC_THRESHOLD));

		/* set SC maximum threshold, adr 08ec, dat ffffb3a3 */
		status = vid_blk_पढ़ो_word(dev, PATH1_SC_CTL, &dwval);
		status = vid_blk_ग_लिखो_word(dev, PATH1_SC_CTL,
					   (dwval | FLD_PATH1_SC_THRESHOLD));
		अवरोध;

	हाल AUDIO_INPUT_TUNER_TV:
	शेष:
		status = stopAudioFirmware(dev);
		/* Setup SRC sources and घड़ीs */
		status = vid_blk_ग_लिखो_word(dev, BAND_OUT_SEL,
			cx231xx_set_field(FLD_SRC6_IN_SEL, 0x00)         |
			cx231xx_set_field(FLD_SRC6_CLK_SEL, 0x01)        |
			cx231xx_set_field(FLD_SRC5_IN_SEL, 0x00)         |
			cx231xx_set_field(FLD_SRC5_CLK_SEL, 0x02)        |
			cx231xx_set_field(FLD_SRC4_IN_SEL, 0x02)         |
			cx231xx_set_field(FLD_SRC4_CLK_SEL, 0x03)        |
			cx231xx_set_field(FLD_SRC3_IN_SEL, 0x00)         |
			cx231xx_set_field(FLD_SRC3_CLK_SEL, 0x00)        |
			cx231xx_set_field(FLD_BASEBAND_BYPASS_CTL, 0x00) |
			cx231xx_set_field(FLD_AC97_SRC_SEL, 0x03)        |
			cx231xx_set_field(FLD_I2S_SRC_SEL, 0x00)         |
			cx231xx_set_field(FLD_PARALLEL2_SRC_SEL, 0x02)   |
			cx231xx_set_field(FLD_PARALLEL1_SRC_SEL, 0x01));

		/* Setup the AUD_IO control */
		status = vid_blk_ग_लिखो_word(dev, AUD_IO_CTRL,
			cx231xx_set_field(FLD_I2S_PORT_सूची, 0x00)  |
			cx231xx_set_field(FLD_I2S_OUT_SRC, 0x00)   |
			cx231xx_set_field(FLD_AUD_CHAN3_SRC, 0x00) |
			cx231xx_set_field(FLD_AUD_CHAN2_SRC, 0x00) |
			cx231xx_set_field(FLD_AUD_CHAN1_SRC, 0x03));

		status = vid_blk_ग_लिखो_word(dev, PATH1_CTL1, 0x1F063870);

		/* setAudioStandard(_audio_standard); */
		status = vid_blk_ग_लिखो_word(dev, PATH1_CTL1, 0x00063870);

		status = restartAudioFirmware(dev);

		चयन (dev->board.tuner_type) अणु
		हाल TUNER_XC5000:
			/* SIF passthrough at 28.6363 MHz sample rate */
			status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
					VID_BLK_I2C_ADDRESS,
					CHIP_CTRL,
					FLD_SIF_EN,
					cx231xx_set_field(FLD_SIF_EN, 1));
			अवरोध;
		हाल TUNER_NXP_TDA18271:
			/* Normal mode: SIF passthrough at 14.32 MHz */
			status = cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(dev,
					VID_BLK_I2C_ADDRESS,
					CHIP_CTRL,
					FLD_SIF_EN,
					cx231xx_set_field(FLD_SIF_EN, 0));
			अवरोध;
		शेष:
			चयन (dev->model) अणु /* i2c device tuners */
			हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx:
			हाल CX231XX_BOARD_HAUPPAUGE_935C:
			हाल CX231XX_BOARD_HAUPPAUGE_955Q:
			हाल CX231XX_BOARD_HAUPPAUGE_975:
			हाल CX231XX_BOARD_EVROMEDIA_FULL_HYBRID_FULLHD:
			/* TODO: Normal mode: SIF passthrough at 14.32 MHz?? */
				अवरोध;
			शेष:
			/* This is just a casual suggestion to people adding
			   new boards in हाल they use a tuner type we करोn't
			   currently know about */
				dev_info(dev->dev,
					 "Unknown tuner type configuring SIF");
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल AUDIO_INPUT_TUNER_FM:
		/*  use SIF क्रम FM radio
		   setupFM();
		   setAudioStandard(_audio_standard);
		 */
		अवरोध;

	हाल AUDIO_INPUT_MUTE:
		status = vid_blk_ग_लिखो_word(dev, PATH1_CTL1, 0x1F011012);
		अवरोध;
	पूर्ण

	/* Take it out of soft reset */
	status = vid_blk_पढ़ो_byte(dev, GENERAL_CTL, &gen_ctrl);
	gen_ctrl &= ~1;
	status = vid_blk_ग_लिखो_byte(dev, GENERAL_CTL, gen_ctrl);

	वापस status;
पूर्ण

/******************************************************************************
 *                    C H I P Specअगरic  C O N T R O L   functions             *
 ******************************************************************************/
पूर्णांक cx231xx_init_ctrl_pin_status(काष्ठा cx231xx *dev)
अणु
	u32 value;
	पूर्णांक status = 0;

	status = vid_blk_पढ़ो_word(dev, PIN_CTRL, &value);
	value |= (~dev->board.ctl_pin_status_mask);
	status = vid_blk_ग_लिखो_word(dev, PIN_CTRL, value);

	वापस status;
पूर्ण

पूर्णांक cx231xx_set_agc_analog_digital_mux_select(काष्ठा cx231xx *dev,
					      u8 analog_or_digital)
अणु
	पूर्णांक status;

	/* first set the direction to output */
	status = cx231xx_set_gpio_direction(dev,
					    dev->board.
					    agc_analog_digital_select_gpio, 1);

	/* 0 - demod ; 1 - Analog mode */
	status = cx231xx_set_gpio_value(dev,
				   dev->board.agc_analog_digital_select_gpio,
				   analog_or_digital);

	अगर (status < 0)
		वापस status;

	वापस 0;
पूर्ण

पूर्णांक cx231xx_enable_i2c_port_3(काष्ठा cx231xx *dev, bool is_port_3)
अणु
	u8 value[4] = अणु 0, 0, 0, 0 पूर्ण;
	पूर्णांक status = 0;
	bool current_is_port_3;

	/*
	 * Should this code check dev->port_3_चयन_enabled first
	 * to skip unnecessary पढ़ोing of the रेजिस्टर?
	 * If yes, the flag dev->port_3_चयन_enabled must be initialized
	 * correctly.
	 */

	status = cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER,
				       PWR_CTL_EN, value, 4);
	अगर (status < 0)
		वापस status;

	current_is_port_3 = value[0] & I2C_DEMOD_EN ? true : false;

	/* Just वापस, अगर alपढ़ोy using the right port */
	अगर (current_is_port_3 == is_port_3)
		वापस 0;

	अगर (is_port_3)
		value[0] |= I2C_DEMOD_EN;
	अन्यथा
		value[0] &= ~I2C_DEMOD_EN;

	status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
					PWR_CTL_EN, value, 4);

	/* remember status of the चयन क्रम usage in is_tuner */
	अगर (status >= 0)
		dev->port_3_चयन_enabled = is_port_3;

	वापस status;

पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_enable_i2c_port_3);

व्योम update_HH_रेजिस्टर_after_set_DIF(काष्ठा cx231xx *dev)
अणु
/*
	u8 status = 0;
	u32 value = 0;

	vid_blk_ग_लिखो_word(dev, PIN_CTRL, 0xA0FFF82F);
	vid_blk_ग_लिखो_word(dev, DIF_MISC_CTRL, 0x0A203F11);
	vid_blk_ग_लिखो_word(dev, DIF_SRC_PHASE_INC, 0x1BEFBF06);

	status = vid_blk_पढ़ो_word(dev, AFE_CTRL_C2HH_SRC_CTRL, &value);
	vid_blk_ग_लिखो_word(dev, AFE_CTRL_C2HH_SRC_CTRL, 0x4485D390);
	status = vid_blk_पढ़ो_word(dev, AFE_CTRL_C2HH_SRC_CTRL,  &value);
*/
पूर्ण

व्योम cx231xx_dump_HH_reg(काष्ठा cx231xx *dev)
अणु
	u32 value = 0;
	u16  i = 0;

	value = 0x45005390;
	vid_blk_ग_लिखो_word(dev, 0x104, value);

	क्रम (i = 0x100; i < 0x140; i++) अणु
		vid_blk_पढ़ो_word(dev, i, &value);
		dev_dbg(dev->dev, "reg0x%x=0x%x\n", i, value);
		i = i+3;
	पूर्ण

	क्रम (i = 0x300; i < 0x400; i++) अणु
		vid_blk_पढ़ो_word(dev, i, &value);
		dev_dbg(dev->dev, "reg0x%x=0x%x\n", i, value);
		i = i+3;
	पूर्ण

	क्रम (i = 0x400; i < 0x440; i++) अणु
		vid_blk_पढ़ो_word(dev, i,  &value);
		dev_dbg(dev->dev, "reg0x%x=0x%x\n", i, value);
		i = i+3;
	पूर्ण

	vid_blk_पढ़ो_word(dev, AFE_CTRL_C2HH_SRC_CTRL, &value);
	dev_dbg(dev->dev, "AFE_CTRL_C2HH_SRC_CTRL=0x%x\n", value);
	vid_blk_ग_लिखो_word(dev, AFE_CTRL_C2HH_SRC_CTRL, 0x4485D390);
	vid_blk_पढ़ो_word(dev, AFE_CTRL_C2HH_SRC_CTRL, &value);
	dev_dbg(dev->dev, "AFE_CTRL_C2HH_SRC_CTRL=0x%x\n", value);
पूर्ण

#अगर 0
अटल व्योम cx231xx_dump_SC_reg(काष्ठा cx231xx *dev)
अणु
	u8 value[4] = अणु 0, 0, 0, 0 पूर्ण;
	dev_dbg(dev->dev, "%s!\n", __func__);

	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, BOARD_CFG_STAT,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", BOARD_CFG_STAT, value[0],
		value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, TS_MODE_REG,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", TS_MODE_REG, value[0],
		 value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, TS1_CFG_REG,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", TS1_CFG_REG, value[0],
		 value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, TS1_LENGTH_REG,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", TS1_LENGTH_REG, value[0],
		value[1], value[2], value[3]);

	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, TS2_CFG_REG,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", TS2_CFG_REG, value[0],
		value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, TS2_LENGTH_REG,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", TS2_LENGTH_REG, value[0],
		value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, EP_MODE_SET,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", EP_MODE_SET, value[0],
		 value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, CIR_PWR_PTN1,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIR_PWR_PTN1, value[0],
		value[1], value[2], value[3]);

	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, CIR_PWR_PTN2,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIR_PWR_PTN2, value[0],
		value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, CIR_PWR_PTN3,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIR_PWR_PTN3, value[0],
		value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, CIR_PWR_MASK0,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIR_PWR_MASK0, value[0],
		value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, CIR_PWR_MASK1,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIR_PWR_MASK1, value[0],
		value[1], value[2], value[3]);

	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, CIR_PWR_MASK2,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIR_PWR_MASK2, value[0],
		value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, CIR_GAIN,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIR_GAIN, value[0],
		value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, CIR_CAR_REG,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIR_CAR_REG, value[0],
		value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, CIR_OT_CFG1,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIR_OT_CFG1, value[0],
		value[1], value[2], value[3]);

	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, CIR_OT_CFG2,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", CIR_OT_CFG2, value[0],
		value[1], value[2], value[3]);
	cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, PWR_CTL_EN,
				 value, 4);
	dev_dbg(dev->dev,
		"reg0x%x=0x%x 0x%x 0x%x 0x%x\n", PWR_CTL_EN, value[0],
		value[1], value[2], value[3]);
पूर्ण
#पूर्ण_अगर

व्योम cx231xx_Setup_AFE_क्रम_LowIF(काष्ठा cx231xx *dev)

अणु
	u8 value = 0;

	afe_पढ़ो_byte(dev, ADC_STATUS2_CH3, &value);
	value = (value & 0xFE)|0x01;
	afe_ग_लिखो_byte(dev, ADC_STATUS2_CH3, value);

	afe_पढ़ो_byte(dev, ADC_STATUS2_CH3, &value);
	value = (value & 0xFE)|0x00;
	afe_ग_लिखो_byte(dev, ADC_STATUS2_CH3, value);


/*
	config colibri to lo-अगर mode

	FIXME: ntf_mode = 2'b00 by शेष. But set 0x1 would reduce
		the dअगरf IF input by half,

		क्रम low-अगर agc defect
*/

	afe_पढ़ो_byte(dev, ADC_NTF_PRECLMP_EN_CH3, &value);
	value = (value & 0xFC)|0x00;
	afe_ग_लिखो_byte(dev, ADC_NTF_PRECLMP_EN_CH3, value);

	afe_पढ़ो_byte(dev, ADC_INPUT_CH3, &value);
	value = (value & 0xF9)|0x02;
	afe_ग_लिखो_byte(dev, ADC_INPUT_CH3, value);

	afe_पढ़ो_byte(dev, ADC_FB_FRCRST_CH3, &value);
	value = (value & 0xFB)|0x04;
	afe_ग_लिखो_byte(dev, ADC_FB_FRCRST_CH3, value);

	afe_पढ़ो_byte(dev, ADC_DCSERVO_DEM_CH3, &value);
	value = (value & 0xFC)|0x03;
	afe_ग_लिखो_byte(dev, ADC_DCSERVO_DEM_CH3, value);

	afe_पढ़ो_byte(dev, ADC_CTRL_DAC1_CH3, &value);
	value = (value & 0xFB)|0x04;
	afe_ग_लिखो_byte(dev, ADC_CTRL_DAC1_CH3, value);

	afe_पढ़ो_byte(dev, ADC_CTRL_DAC23_CH3, &value);
	value = (value & 0xF8)|0x06;
	afe_ग_लिखो_byte(dev, ADC_CTRL_DAC23_CH3, value);

	afe_पढ़ो_byte(dev, ADC_CTRL_DAC23_CH3, &value);
	value = (value & 0x8F)|0x40;
	afe_ग_लिखो_byte(dev, ADC_CTRL_DAC23_CH3, value);

	afe_पढ़ो_byte(dev, ADC_PWRDN_CLAMP_CH3, &value);
	value = (value & 0xDF)|0x20;
	afe_ग_लिखो_byte(dev, ADC_PWRDN_CLAMP_CH3, value);
पूर्ण

व्योम cx231xx_set_Colibri_For_LowIF(काष्ठा cx231xx *dev, u32 अगर_freq,
		 u8 spectral_invert, u32 mode)
अणु
	u32 colibri_carrier_offset = 0;
	u32 func_mode = 0x01; /* Device has a DIF अगर this function is called */
	u32 standard = 0;
	u8 value[4] = अणु 0, 0, 0, 0 पूर्ण;

	dev_dbg(dev->dev, "Enter cx231xx_set_Colibri_For_LowIF()\n");
	value[0] = (u8) 0x6F;
	value[1] = (u8) 0x6F;
	value[2] = (u8) 0x6F;
	value[3] = (u8) 0x6F;
	cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
					PWR_CTL_EN, value, 4);

	/*Set colibri क्रम low IF*/
	cx231xx_afe_set_mode(dev, AFE_MODE_LOW_IF);

	/* Set C2HH क्रम low IF operation.*/
	standard = dev->norm;
	cx231xx_dअगर_configure_C2HH_क्रम_low_IF(dev, dev->active_mode,
						       func_mode, standard);

	/* Get colibri offsets.*/
	colibri_carrier_offset = cx231xx_Get_Colibri_CarrierOffset(mode,
								   standard);

	dev_dbg(dev->dev, "colibri_carrier_offset=%d, standard=0x%x\n",
		     colibri_carrier_offset, standard);

	/* Set the band Pass filter क्रम DIF*/
	cx231xx_set_DIF_bandpass(dev, (अगर_freq+colibri_carrier_offset),
				 spectral_invert, mode);
पूर्ण

u32 cx231xx_Get_Colibri_CarrierOffset(u32 mode, u32 standerd)
अणु
	u32 colibri_carrier_offset = 0;

	अगर (mode == TUNER_MODE_FM_RADIO) अणु
		colibri_carrier_offset = 1100000;
	पूर्ण अन्यथा अगर (standerd & (V4L2_STD_MN | V4L2_STD_NTSC_M_JP)) अणु
		colibri_carrier_offset = 4832000;  /*4.83MHz	*/
	पूर्ण अन्यथा अगर (standerd & (V4L2_STD_PAL_B | V4L2_STD_PAL_G)) अणु
		colibri_carrier_offset = 2700000;  /*2.70MHz       */
	पूर्ण अन्यथा अगर (standerd & (V4L2_STD_PAL_D | V4L2_STD_PAL_I
			| V4L2_STD_SECAM)) अणु
		colibri_carrier_offset = 2100000;  /*2.10MHz	*/
	पूर्ण

	वापस colibri_carrier_offset;
पूर्ण

व्योम cx231xx_set_DIF_bandpass(काष्ठा cx231xx *dev, u32 अगर_freq,
		 u8 spectral_invert, u32 mode)
अणु
	अचिन्हित दीर्घ pll_freq_word;
	u32 dअगर_misc_ctrl_value = 0;
	u64 pll_freq_u64 = 0;
	u32 i = 0;

	dev_dbg(dev->dev, "if_freq=%d;spectral_invert=0x%x;mode=0x%x\n",
		अगर_freq, spectral_invert, mode);


	अगर (mode == TUNER_MODE_FM_RADIO) अणु
		pll_freq_word = 0x905A1CAC;
		vid_blk_ग_लिखो_word(dev, DIF_PLL_FREQ_WORD,  pll_freq_word);

	पूर्ण अन्यथा /*KSPROPERTY_TUNER_MODE_TV*/अणु
		/* Calculate the PLL frequency word based on the adjusted अगर_freq*/
		pll_freq_word = अगर_freq;
		pll_freq_u64 = (u64)pll_freq_word << 28L;
		करो_भाग(pll_freq_u64, 50000000);
		pll_freq_word = (u32)pll_freq_u64;
		/*pll_freq_word = 0x3463497;*/
		vid_blk_ग_लिखो_word(dev, DIF_PLL_FREQ_WORD,  pll_freq_word);

		अगर (spectral_invert) अणु
			अगर_freq -= 400000;
			/* Enable Spectral Invert*/
			vid_blk_पढ़ो_word(dev, DIF_MISC_CTRL,
					  &dअगर_misc_ctrl_value);
			dअगर_misc_ctrl_value = dअगर_misc_ctrl_value | 0x00200000;
			vid_blk_ग_लिखो_word(dev, DIF_MISC_CTRL,
					  dअगर_misc_ctrl_value);
		पूर्ण अन्यथा अणु
			अगर_freq += 400000;
			/* Disable Spectral Invert*/
			vid_blk_पढ़ो_word(dev, DIF_MISC_CTRL,
					  &dअगर_misc_ctrl_value);
			dअगर_misc_ctrl_value = dअगर_misc_ctrl_value & 0xFFDFFFFF;
			vid_blk_ग_लिखो_word(dev, DIF_MISC_CTRL,
					  dअगर_misc_ctrl_value);
		पूर्ण

		अगर_freq = (अगर_freq / 100000) * 100000;

		अगर (अगर_freq < 3000000)
			अगर_freq = 3000000;

		अगर (अगर_freq > 16000000)
			अगर_freq = 16000000;
	पूर्ण

	dev_dbg(dev->dev, "Enter IF=%zu\n", ARRAY_SIZE(Dअगर_set_array));
	क्रम (i = 0; i < ARRAY_SIZE(Dअगर_set_array); i++) अणु
		अगर (Dअगर_set_array[i].अगर_freq == अगर_freq) अणु
			vid_blk_ग_लिखो_word(dev,
			Dअगर_set_array[i].रेजिस्टर_address, Dअगर_set_array[i].value);
		पूर्ण
	पूर्ण
पूर्ण

/******************************************************************************
 *                 D I F - B L O C K    C O N T R O L   functions             *
 ******************************************************************************/
पूर्णांक cx231xx_dअगर_configure_C2HH_क्रम_low_IF(काष्ठा cx231xx *dev, u32 mode,
					  u32 function_mode, u32 standard)
अणु
	पूर्णांक status = 0;


	अगर (mode == V4L2_TUNER_RADIO) अणु
		/* C2HH */
		/* lo अगर big संकेत */
		status = cx231xx_reg_mask_ग_लिखो(dev,
				VID_BLK_I2C_ADDRESS, 32,
				AFE_CTRL_C2HH_SRC_CTRL, 30, 31, 0x1);
		/* FUNC_MODE = DIF */
		status = cx231xx_reg_mask_ग_लिखो(dev,
				VID_BLK_I2C_ADDRESS, 32,
				AFE_CTRL_C2HH_SRC_CTRL, 23, 24, function_mode);
		/* IF_MODE */
		status = cx231xx_reg_mask_ग_लिखो(dev,
				VID_BLK_I2C_ADDRESS, 32,
				AFE_CTRL_C2HH_SRC_CTRL, 15, 22, 0xFF);
		/* no inv */
		status = cx231xx_reg_mask_ग_लिखो(dev,
				VID_BLK_I2C_ADDRESS, 32,
				AFE_CTRL_C2HH_SRC_CTRL, 9, 9, 0x1);
	पूर्ण अन्यथा अगर (standard != DIF_USE_BASEBAND) अणु
		अगर (standard & V4L2_STD_MN) अणु
			/* lo अगर big संकेत */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 30, 31, 0x1);
			/* FUNC_MODE = DIF */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 23, 24,
					function_mode);
			/* IF_MODE */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 15, 22, 0xb);
			/* no inv */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 9, 9, 0x1);
			/* 0x124, AUD_CHAN1_SRC = 0x3 */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AUD_IO_CTRL, 0, 31, 0x00000003);
		पूर्ण अन्यथा अगर ((standard == V4L2_STD_PAL_I) |
			(standard & V4L2_STD_PAL_D) |
			(standard & V4L2_STD_SECAM)) अणु
			/* C2HH setup */
			/* lo अगर big संकेत */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 30, 31, 0x1);
			/* FUNC_MODE = DIF */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 23, 24,
					function_mode);
			/* IF_MODE */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 15, 22, 0xF);
			/* no inv */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 9, 9, 0x1);
		पूर्ण अन्यथा अणु
			/* शेष PAL BG */
			/* C2HH setup */
			/* lo अगर big संकेत */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 30, 31, 0x1);
			/* FUNC_MODE = DIF */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 23, 24,
					function_mode);
			/* IF_MODE */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 15, 22, 0xE);
			/* no inv */
			status = cx231xx_reg_mask_ग_लिखो(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 9, 9, 0x1);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक cx231xx_dअगर_set_standard(काष्ठा cx231xx *dev, u32 standard)
अणु
	पूर्णांक status = 0;
	u32 dअगर_misc_ctrl_value = 0;
	u32 func_mode = 0;

	dev_dbg(dev->dev, "%s: setStandard to %x\n", __func__, standard);

	status = vid_blk_पढ़ो_word(dev, DIF_MISC_CTRL, &dअगर_misc_ctrl_value);
	अगर (standard != DIF_USE_BASEBAND)
		dev->norm = standard;

	चयन (dev->model) अणु
	हाल CX231XX_BOARD_CNXT_CARRAERA:
	हाल CX231XX_BOARD_CNXT_RDE_250:
	हाल CX231XX_BOARD_CNXT_SHELBY:
	हाल CX231XX_BOARD_CNXT_RDU_250:
	हाल CX231XX_BOARD_CNXT_VIDEO_GRABBER:
	हाल CX231XX_BOARD_HAUPPAUGE_EXETER:
	हाल CX231XX_BOARD_OTG102:
		func_mode = 0x03;
		अवरोध;
	हाल CX231XX_BOARD_CNXT_RDE_253S:
	हाल CX231XX_BOARD_CNXT_RDU_253S:
	हाल CX231XX_BOARD_HAUPPAUGE_USB2_FM_PAL:
	हाल CX231XX_BOARD_HAUPPAUGE_USB2_FM_NTSC:
		func_mode = 0x01;
		अवरोध;
	शेष:
		func_mode = 0x01;
	पूर्ण

	status = cx231xx_dअगर_configure_C2HH_क्रम_low_IF(dev, dev->active_mode,
						  func_mode, standard);

	अगर (standard == DIF_USE_BASEBAND) अणु	/* base band */
		/* There is a dअगरferent SRC_PHASE_INC value
		   क्रम baseband vs. DIF */
		status = vid_blk_ग_लिखो_word(dev, DIF_SRC_PHASE_INC, 0xDF7DF83);
		status = vid_blk_पढ़ो_word(dev, DIF_MISC_CTRL,
						&dअगर_misc_ctrl_value);
		dअगर_misc_ctrl_value |= FLD_DIF_DIF_BYPASS;
		status = vid_blk_ग_लिखो_word(dev, DIF_MISC_CTRL,
						dअगर_misc_ctrl_value);
	पूर्ण अन्यथा अगर (standard & V4L2_STD_PAL_D) अणु
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL, 0, 31, 0x6503bc0c);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL1, 0, 31, 0xbd038c85);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL2, 0, 31, 0x1db4640a);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL3, 0, 31, 0x00008800);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_IF_REF, 0, 31, 0x444C1380);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_IF, 0, 31, 0xDA302600);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_INT, 0, 31, 0xDA261700);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_RF, 0, 31, 0xDA262600);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_IF_INT_CURRENT, 0, 31,
					   0x26001700);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_RF_CURRENT, 0, 31,
					   0x00002660);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_VIDEO_AGC_CTRL, 0, 31,
					   0x72500800);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_VID_AUD_OVERRIDE, 0, 31,
					   0x27000100);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AV_SEP_CTRL, 0, 31, 0x3F3934EA);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_COMP_FLT_CTRL, 0, 31,
					   0x00000000);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_SRC_PHASE_INC, 0, 31,
					   0x1befbf06);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_SRC_GAIN_CONTROL, 0, 31,
					   0x000035e8);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_RPT_VARIANCE, 0, 31, 0x00000000);
		/* Save the Spec Inversion value */
		dअगर_misc_ctrl_value &= FLD_DIF_SPEC_INV;
		dअगर_misc_ctrl_value |= 0x3a023F11;
	पूर्ण अन्यथा अगर (standard & V4L2_STD_PAL_I) अणु
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL, 0, 31, 0x6503bc0c);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL1, 0, 31, 0xbd038c85);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL2, 0, 31, 0x1db4640a);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL3, 0, 31, 0x00008800);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_IF_REF, 0, 31, 0x444C1380);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_IF, 0, 31, 0xDA302600);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_INT, 0, 31, 0xDA261700);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_RF, 0, 31, 0xDA262600);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_IF_INT_CURRENT, 0, 31,
					   0x26001700);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_RF_CURRENT, 0, 31,
					   0x00002660);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_VIDEO_AGC_CTRL, 0, 31,
					   0x72500800);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_VID_AUD_OVERRIDE, 0, 31,
					   0x27000100);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AV_SEP_CTRL, 0, 31, 0x5F39A934);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_COMP_FLT_CTRL, 0, 31,
					   0x00000000);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_SRC_PHASE_INC, 0, 31,
					   0x1befbf06);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_SRC_GAIN_CONTROL, 0, 31,
					   0x000035e8);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_RPT_VARIANCE, 0, 31, 0x00000000);
		/* Save the Spec Inversion value */
		dअगर_misc_ctrl_value &= FLD_DIF_SPEC_INV;
		dअगर_misc_ctrl_value |= 0x3a033F11;
	पूर्ण अन्यथा अगर (standard & V4L2_STD_PAL_M) अणु
		/* improved Low Frequency Phase Noise */
		status = vid_blk_ग_लिखो_word(dev, DIF_PLL_CTRL, 0xFF01FF0C);
		status = vid_blk_ग_लिखो_word(dev, DIF_PLL_CTRL1, 0xbd038c85);
		status = vid_blk_ग_लिखो_word(dev, DIF_PLL_CTRL2, 0x1db4640a);
		status = vid_blk_ग_लिखो_word(dev, DIF_PLL_CTRL3, 0x00008800);
		status = vid_blk_ग_लिखो_word(dev, DIF_AGC_IF_REF, 0x444C1380);
		status = vid_blk_ग_लिखो_word(dev, DIF_AGC_IF_INT_CURRENT,
						0x26001700);
		status = vid_blk_ग_लिखो_word(dev, DIF_AGC_RF_CURRENT,
						0x00002660);
		status = vid_blk_ग_लिखो_word(dev, DIF_VIDEO_AGC_CTRL,
						0x72500800);
		status = vid_blk_ग_लिखो_word(dev, DIF_VID_AUD_OVERRIDE,
						0x27000100);
		status = vid_blk_ग_लिखो_word(dev, DIF_AV_SEP_CTRL, 0x012c405d);
		status = vid_blk_ग_लिखो_word(dev, DIF_COMP_FLT_CTRL,
						0x009f50c1);
		status = vid_blk_ग_लिखो_word(dev, DIF_SRC_PHASE_INC,
						0x1befbf06);
		status = vid_blk_ग_लिखो_word(dev, DIF_SRC_GAIN_CONTROL,
						0x000035e8);
		status = vid_blk_ग_लिखो_word(dev, DIF_SOFT_RST_CTRL_REVB,
						0x00000000);
		/* Save the Spec Inversion value */
		dअगर_misc_ctrl_value &= FLD_DIF_SPEC_INV;
		dअगर_misc_ctrl_value |= 0x3A0A3F10;
	पूर्ण अन्यथा अगर (standard & (V4L2_STD_PAL_N | V4L2_STD_PAL_Nc)) अणु
		/* improved Low Frequency Phase Noise */
		status = vid_blk_ग_लिखो_word(dev, DIF_PLL_CTRL, 0xFF01FF0C);
		status = vid_blk_ग_लिखो_word(dev, DIF_PLL_CTRL1, 0xbd038c85);
		status = vid_blk_ग_लिखो_word(dev, DIF_PLL_CTRL2, 0x1db4640a);
		status = vid_blk_ग_लिखो_word(dev, DIF_PLL_CTRL3, 0x00008800);
		status = vid_blk_ग_लिखो_word(dev, DIF_AGC_IF_REF, 0x444C1380);
		status = vid_blk_ग_लिखो_word(dev, DIF_AGC_IF_INT_CURRENT,
						0x26001700);
		status = vid_blk_ग_लिखो_word(dev, DIF_AGC_RF_CURRENT,
						0x00002660);
		status = vid_blk_ग_लिखो_word(dev, DIF_VIDEO_AGC_CTRL,
						0x72500800);
		status = vid_blk_ग_लिखो_word(dev, DIF_VID_AUD_OVERRIDE,
						0x27000100);
		status = vid_blk_ग_लिखो_word(dev, DIF_AV_SEP_CTRL,
						0x012c405d);
		status = vid_blk_ग_लिखो_word(dev, DIF_COMP_FLT_CTRL,
						0x009f50c1);
		status = vid_blk_ग_लिखो_word(dev, DIF_SRC_PHASE_INC,
						0x1befbf06);
		status = vid_blk_ग_लिखो_word(dev, DIF_SRC_GAIN_CONTROL,
						0x000035e8);
		status = vid_blk_ग_लिखो_word(dev, DIF_SOFT_RST_CTRL_REVB,
						0x00000000);
		/* Save the Spec Inversion value */
		dअगर_misc_ctrl_value &= FLD_DIF_SPEC_INV;
		dअगर_misc_ctrl_value = 0x3A093F10;
	पूर्ण अन्यथा अगर (standard &
		  (V4L2_STD_SECAM_B | V4L2_STD_SECAM_D | V4L2_STD_SECAM_G |
		   V4L2_STD_SECAM_K | V4L2_STD_SECAM_K1)) अणु

		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL, 0, 31, 0x6503bc0c);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL1, 0, 31, 0xbd038c85);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL2, 0, 31, 0x1db4640a);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL3, 0, 31, 0x00008800);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_IF_REF, 0, 31, 0x888C0380);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_IF, 0, 31, 0xe0262600);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_INT, 0, 31, 0xc2171700);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_RF, 0, 31, 0xc2262600);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_IF_INT_CURRENT, 0, 31,
					   0x26001700);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_RF_CURRENT, 0, 31,
					   0x00002660);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_VID_AUD_OVERRIDE, 0, 31,
					   0x27000100);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AV_SEP_CTRL, 0, 31, 0x3F3530ec);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_COMP_FLT_CTRL, 0, 31,
					   0x00000000);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_SRC_PHASE_INC, 0, 31,
					   0x1befbf06);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_SRC_GAIN_CONTROL, 0, 31,
					   0x000035e8);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_RPT_VARIANCE, 0, 31, 0x00000000);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_VIDEO_AGC_CTRL, 0, 31,
					   0xf4000000);

		/* Save the Spec Inversion value */
		dअगर_misc_ctrl_value &= FLD_DIF_SPEC_INV;
		dअगर_misc_ctrl_value |= 0x3a023F11;
	पूर्ण अन्यथा अगर (standard & (V4L2_STD_SECAM_L | V4L2_STD_SECAM_LC)) अणु
		/* Is it SECAM_L1? */
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL, 0, 31, 0x6503bc0c);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL1, 0, 31, 0xbd038c85);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL2, 0, 31, 0x1db4640a);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL3, 0, 31, 0x00008800);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_IF_REF, 0, 31, 0x888C0380);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_IF, 0, 31, 0xe0262600);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_INT, 0, 31, 0xc2171700);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_RF, 0, 31, 0xc2262600);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_IF_INT_CURRENT, 0, 31,
					   0x26001700);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_RF_CURRENT, 0, 31,
					   0x00002660);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_VID_AUD_OVERRIDE, 0, 31,
					   0x27000100);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AV_SEP_CTRL, 0, 31, 0x3F3530ec);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_COMP_FLT_CTRL, 0, 31,
					   0x00000000);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_SRC_PHASE_INC, 0, 31,
					   0x1befbf06);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_SRC_GAIN_CONTROL, 0, 31,
					   0x000035e8);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_RPT_VARIANCE, 0, 31, 0x00000000);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_VIDEO_AGC_CTRL, 0, 31,
					   0xf2560000);

		/* Save the Spec Inversion value */
		dअगर_misc_ctrl_value &= FLD_DIF_SPEC_INV;
		dअगर_misc_ctrl_value |= 0x3a023F11;

	पूर्ण अन्यथा अगर (standard & V4L2_STD_NTSC_M) अणु
		/* V4L2_STD_NTSC_M (75 IRE Setup) Or
		   V4L2_STD_NTSC_M_JP (Japan,  0 IRE Setup) */

		/* For NTSC the centre frequency of video coming out of
		   sidewinder is around 7.1MHz or 3.6MHz depending on the
		   spectral inversion. so क्रम a non spectrally inverted channel
		   the pll freq word is 0x03420c49
		 */

		status = vid_blk_ग_लिखो_word(dev, DIF_PLL_CTRL, 0x6503BC0C);
		status = vid_blk_ग_लिखो_word(dev, DIF_PLL_CTRL1, 0xBD038C85);
		status = vid_blk_ग_लिखो_word(dev, DIF_PLL_CTRL2, 0x1DB4640A);
		status = vid_blk_ग_लिखो_word(dev, DIF_PLL_CTRL3, 0x00008800);
		status = vid_blk_ग_लिखो_word(dev, DIF_AGC_IF_REF, 0x444C0380);
		status = vid_blk_ग_लिखो_word(dev, DIF_AGC_IF_INT_CURRENT,
						0x26001700);
		status = vid_blk_ग_लिखो_word(dev, DIF_AGC_RF_CURRENT,
						0x00002660);
		status = vid_blk_ग_लिखो_word(dev, DIF_VIDEO_AGC_CTRL,
						0x04000800);
		status = vid_blk_ग_लिखो_word(dev, DIF_VID_AUD_OVERRIDE,
						0x27000100);
		status = vid_blk_ग_लिखो_word(dev, DIF_AV_SEP_CTRL, 0x01296e1f);

		status = vid_blk_ग_लिखो_word(dev, DIF_COMP_FLT_CTRL,
						0x009f50c1);
		status = vid_blk_ग_लिखो_word(dev, DIF_SRC_PHASE_INC,
						0x1befbf06);
		status = vid_blk_ग_लिखो_word(dev, DIF_SRC_GAIN_CONTROL,
						0x000035e8);

		status = vid_blk_ग_लिखो_word(dev, DIF_AGC_CTRL_IF, 0xC2262600);
		status = vid_blk_ग_लिखो_word(dev, DIF_AGC_CTRL_INT,
						0xC2262600);
		status = vid_blk_ग_लिखो_word(dev, DIF_AGC_CTRL_RF, 0xC2262600);

		/* Save the Spec Inversion value */
		dअगर_misc_ctrl_value &= FLD_DIF_SPEC_INV;
		dअगर_misc_ctrl_value |= 0x3a003F10;
	पूर्ण अन्यथा अणु
		/* शेष PAL BG */
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL, 0, 31, 0x6503bc0c);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL1, 0, 31, 0xbd038c85);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL2, 0, 31, 0x1db4640a);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_PLL_CTRL3, 0, 31, 0x00008800);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_IF_REF, 0, 31, 0x444C1380);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_IF, 0, 31, 0xDA302600);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_INT, 0, 31, 0xDA261700);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_CTRL_RF, 0, 31, 0xDA262600);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_IF_INT_CURRENT, 0, 31,
					   0x26001700);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AGC_RF_CURRENT, 0, 31,
					   0x00002660);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_VIDEO_AGC_CTRL, 0, 31,
					   0x72500800);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_VID_AUD_OVERRIDE, 0, 31,
					   0x27000100);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_AV_SEP_CTRL, 0, 31, 0x3F3530EC);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_COMP_FLT_CTRL, 0, 31,
					   0x00A653A8);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_SRC_PHASE_INC, 0, 31,
					   0x1befbf06);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_SRC_GAIN_CONTROL, 0, 31,
					   0x000035e8);
		status = cx231xx_reg_mask_ग_लिखो(dev, VID_BLK_I2C_ADDRESS, 32,
					   DIF_RPT_VARIANCE, 0, 31, 0x00000000);
		/* Save the Spec Inversion value */
		dअगर_misc_ctrl_value &= FLD_DIF_SPEC_INV;
		dअगर_misc_ctrl_value |= 0x3a013F11;
	पूर्ण

	/* The AGC values should be the same क्रम all standards,
	   AUD_SRC_SEL[19] should always be disabled    */
	dअगर_misc_ctrl_value &= ~FLD_DIF_AUD_SRC_SEL;

	/* It is still possible to get Set Standard calls even when we
	   are in FM mode.
	   This is करोne to override the value क्रम FM. */
	अगर (dev->active_mode == V4L2_TUNER_RADIO)
		dअगर_misc_ctrl_value = 0x7a080000;

	/* Write the calculated value क्रम misc ontrol रेजिस्टर      */
	status = vid_blk_ग_लिखो_word(dev, DIF_MISC_CTRL, dअगर_misc_ctrl_value);

	वापस status;
पूर्ण

पूर्णांक cx231xx_tuner_pre_channel_change(काष्ठा cx231xx *dev)
अणु
	पूर्णांक status = 0;
	u32 dwval;

	/* Set the RF and IF k_agc values to 3 */
	status = vid_blk_पढ़ो_word(dev, DIF_AGC_IF_REF, &dwval);
	dwval &= ~(FLD_DIF_K_AGC_RF | FLD_DIF_K_AGC_IF);
	dwval |= 0x33000000;

	status = vid_blk_ग_लिखो_word(dev, DIF_AGC_IF_REF, dwval);

	वापस status;
पूर्ण

पूर्णांक cx231xx_tuner_post_channel_change(काष्ठा cx231xx *dev)
अणु
	पूर्णांक status = 0;
	u32 dwval;
	dev_dbg(dev->dev, "%s: dev->tuner_type =0%d\n",
		__func__, dev->tuner_type);
	/* Set the RF and IF k_agc values to 4 क्रम PAL/NTSC and 8 क्रम
	 * SECAM L/B/D standards */
	status = vid_blk_पढ़ो_word(dev, DIF_AGC_IF_REF, &dwval);
	dwval &= ~(FLD_DIF_K_AGC_RF | FLD_DIF_K_AGC_IF);

	अगर (dev->norm & (V4L2_STD_SECAM_L | V4L2_STD_SECAM_B |
			 V4L2_STD_SECAM_D)) अणु
			अगर (dev->tuner_type == TUNER_NXP_TDA18271) अणु
				dwval &= ~FLD_DIF_IF_REF;
				dwval |= 0x88000300;
			पूर्ण अन्यथा
				dwval |= 0x88000000;
		पूर्ण अन्यथा अणु
			अगर (dev->tuner_type == TUNER_NXP_TDA18271) अणु
				dwval &= ~FLD_DIF_IF_REF;
				dwval |= 0xCC000300;
			पूर्ण अन्यथा
				dwval |= 0x44000000;
		पूर्ण

	status = vid_blk_ग_लिखो_word(dev, DIF_AGC_IF_REF, dwval);

	वापस status == माप(dwval) ? 0 : -EIO;
पूर्ण

/******************************************************************************
 *		    I 2 S - B L O C K    C O N T R O L   functions            *
 ******************************************************************************/
पूर्णांक cx231xx_i2s_blk_initialize(काष्ठा cx231xx *dev)
अणु
	पूर्णांक status = 0;
	u32 value;

	status = cx231xx_पढ़ो_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
				       CH_PWR_CTRL1, 1, &value, 1);
	/* enables घड़ी to delta-sigma and decimation filter */
	value |= 0x80;
	status = cx231xx_ग_लिखो_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
					CH_PWR_CTRL1, 1, value, 1);
	/* घातer up all channel */
	status = cx231xx_ग_लिखो_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
					CH_PWR_CTRL2, 1, 0x00, 1);

	वापस status;
पूर्ण

पूर्णांक cx231xx_i2s_blk_update_घातer_control(काष्ठा cx231xx *dev,
					क्रमागत AV_MODE avmode)
अणु
	पूर्णांक status = 0;
	u32 value = 0;

	अगर (avmode != POLARIS_AVMODE_ENXTERNAL_AV) अणु
		status = cx231xx_पढ़ो_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
					  CH_PWR_CTRL2, 1, &value, 1);
		value |= 0xfe;
		status = cx231xx_ग_लिखो_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
						CH_PWR_CTRL2, 1, value, 1);
	पूर्ण अन्यथा अणु
		status = cx231xx_ग_लिखो_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
						CH_PWR_CTRL2, 1, 0x00, 1);
	पूर्ण

	वापस status;
पूर्ण

/* set i2s_blk क्रम audio input types */
पूर्णांक cx231xx_i2s_blk_set_audio_input(काष्ठा cx231xx *dev, u8 audio_input)
अणु
	पूर्णांक status = 0;

	चयन (audio_input) अणु
	हाल CX231XX_AMUX_LINE_IN:
		status = cx231xx_ग_लिखो_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
						CH_PWR_CTRL2, 1, 0x00, 1);
		status = cx231xx_ग_लिखो_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
						CH_PWR_CTRL1, 1, 0x80, 1);
		अवरोध;
	हाल CX231XX_AMUX_VIDEO:
	शेष:
		अवरोध;
	पूर्ण

	dev->ctl_ainput = audio_input;

	वापस status;
पूर्ण

/******************************************************************************
 *                  P O W E R      C O N T R O L   functions                  *
 ******************************************************************************/
पूर्णांक cx231xx_set_घातer_mode(काष्ठा cx231xx *dev, क्रमागत AV_MODE mode)
अणु
	u8 value[4] = अणु 0, 0, 0, 0 पूर्ण;
	u32 पंचांगp = 0;
	पूर्णांक status = 0;

	अगर (dev->घातer_mode != mode)
		dev->घातer_mode = mode;
	अन्यथा अणु
		dev_dbg(dev->dev, "%s: mode = %d, No Change req.\n",
			 __func__, mode);
		वापस 0;
	पूर्ण

	status = cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, PWR_CTL_EN, value,
				       4);
	अगर (status < 0)
		वापस status;

	पंचांगp = le32_to_cpu(*((__le32 *) value));

	चयन (mode) अणु
	हाल POLARIS_AVMODE_ENXTERNAL_AV:

		पंचांगp &= (~PWR_MODE_MASK);

		पंचांगp |= PWR_AV_EN;
		value[0] = (u8) पंचांगp;
		value[1] = (u8) (पंचांगp >> 8);
		value[2] = (u8) (पंचांगp >> 16);
		value[3] = (u8) (पंचांगp >> 24);
		status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
						PWR_CTL_EN, value, 4);
		msleep(PWR_SLEEP_INTERVAL);

		पंचांगp |= PWR_ISO_EN;
		value[0] = (u8) पंचांगp;
		value[1] = (u8) (पंचांगp >> 8);
		value[2] = (u8) (पंचांगp >> 16);
		value[3] = (u8) (पंचांगp >> 24);
		status =
		    cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER, PWR_CTL_EN,
					   value, 4);
		msleep(PWR_SLEEP_INTERVAL);

		पंचांगp |= POLARIS_AVMODE_ENXTERNAL_AV;
		value[0] = (u8) पंचांगp;
		value[1] = (u8) (पंचांगp >> 8);
		value[2] = (u8) (पंचांगp >> 16);
		value[3] = (u8) (पंचांगp >> 24);
		status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
						PWR_CTL_EN, value, 4);

		/* reset state of xceive tuner */
		dev->xc_fw_load_करोne = 0;
		अवरोध;

	हाल POLARIS_AVMODE_ANALOGT_TV:

		पंचांगp |= PWR_DEMOD_EN;
		value[0] = (u8) पंचांगp;
		value[1] = (u8) (पंचांगp >> 8);
		value[2] = (u8) (पंचांगp >> 16);
		value[3] = (u8) (पंचांगp >> 24);
		status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
						PWR_CTL_EN, value, 4);
		msleep(PWR_SLEEP_INTERVAL);

		अगर (!(पंचांगp & PWR_TUNER_EN)) अणु
			पंचांगp |= (PWR_TUNER_EN);
			value[0] = (u8) पंचांगp;
			value[1] = (u8) (पंचांगp >> 8);
			value[2] = (u8) (पंचांगp >> 16);
			value[3] = (u8) (पंचांगp >> 24);
			status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
							PWR_CTL_EN, value, 4);
			msleep(PWR_SLEEP_INTERVAL);
		पूर्ण

		अगर (!(पंचांगp & PWR_AV_EN)) अणु
			पंचांगp |= PWR_AV_EN;
			value[0] = (u8) पंचांगp;
			value[1] = (u8) (पंचांगp >> 8);
			value[2] = (u8) (पंचांगp >> 16);
			value[3] = (u8) (पंचांगp >> 24);
			status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
							PWR_CTL_EN, value, 4);
			msleep(PWR_SLEEP_INTERVAL);
		पूर्ण
		अगर (!(पंचांगp & PWR_ISO_EN)) अणु
			पंचांगp |= PWR_ISO_EN;
			value[0] = (u8) पंचांगp;
			value[1] = (u8) (पंचांगp >> 8);
			value[2] = (u8) (पंचांगp >> 16);
			value[3] = (u8) (पंचांगp >> 24);
			status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
							PWR_CTL_EN, value, 4);
			msleep(PWR_SLEEP_INTERVAL);
		पूर्ण

		अगर (!(पंचांगp & POLARIS_AVMODE_ANALOGT_TV)) अणु
			पंचांगp |= POLARIS_AVMODE_ANALOGT_TV;
			value[0] = (u8) पंचांगp;
			value[1] = (u8) (पंचांगp >> 8);
			value[2] = (u8) (पंचांगp >> 16);
			value[3] = (u8) (पंचांगp >> 24);
			status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
							PWR_CTL_EN, value, 4);
			msleep(PWR_SLEEP_INTERVAL);
		पूर्ण

		अगर (dev->board.tuner_type != TUNER_ABSENT) अणु
			/* reset the Tuner */
			अगर (dev->board.tuner_gpio)
				cx231xx_gpio_set(dev, dev->board.tuner_gpio);

			अगर (dev->cx231xx_reset_analog_tuner)
				dev->cx231xx_reset_analog_tuner(dev);
		पूर्ण

		अवरोध;

	हाल POLARIS_AVMODE_DIGITAL:
		अगर (!(पंचांगp & PWR_TUNER_EN)) अणु
			पंचांगp |= (PWR_TUNER_EN);
			value[0] = (u8) पंचांगp;
			value[1] = (u8) (पंचांगp >> 8);
			value[2] = (u8) (पंचांगp >> 16);
			value[3] = (u8) (पंचांगp >> 24);
			status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
							PWR_CTL_EN, value, 4);
			msleep(PWR_SLEEP_INTERVAL);
		पूर्ण
		अगर (!(पंचांगp & PWR_AV_EN)) अणु
			पंचांगp |= PWR_AV_EN;
			value[0] = (u8) पंचांगp;
			value[1] = (u8) (पंचांगp >> 8);
			value[2] = (u8) (पंचांगp >> 16);
			value[3] = (u8) (पंचांगp >> 24);
			status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
							PWR_CTL_EN, value, 4);
			msleep(PWR_SLEEP_INTERVAL);
		पूर्ण
		अगर (!(पंचांगp & PWR_ISO_EN)) अणु
			पंचांगp |= PWR_ISO_EN;
			value[0] = (u8) पंचांगp;
			value[1] = (u8) (पंचांगp >> 8);
			value[2] = (u8) (पंचांगp >> 16);
			value[3] = (u8) (पंचांगp >> 24);
			status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
							PWR_CTL_EN, value, 4);
			msleep(PWR_SLEEP_INTERVAL);
		पूर्ण

		पंचांगp &= (~PWR_AV_MODE);
		पंचांगp |= POLARIS_AVMODE_DIGITAL;
		value[0] = (u8) पंचांगp;
		value[1] = (u8) (पंचांगp >> 8);
		value[2] = (u8) (पंचांगp >> 16);
		value[3] = (u8) (पंचांगp >> 24);
		status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
						PWR_CTL_EN, value, 4);
		msleep(PWR_SLEEP_INTERVAL);

		अगर (!(पंचांगp & PWR_DEMOD_EN)) अणु
			पंचांगp |= PWR_DEMOD_EN;
			value[0] = (u8) पंचांगp;
			value[1] = (u8) (पंचांगp >> 8);
			value[2] = (u8) (पंचांगp >> 16);
			value[3] = (u8) (पंचांगp >> 24);
			status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
							PWR_CTL_EN, value, 4);
			msleep(PWR_SLEEP_INTERVAL);
		पूर्ण

		अगर (dev->board.tuner_type != TUNER_ABSENT) अणु
			/* reset the Tuner */
			अगर (dev->board.tuner_gpio)
				cx231xx_gpio_set(dev, dev->board.tuner_gpio);

			अगर (dev->cx231xx_reset_analog_tuner)
				dev->cx231xx_reset_analog_tuner(dev);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	msleep(PWR_SLEEP_INTERVAL);

	/* For घातer saving, only enable Pwr_resetout_n
	   when digital TV is selected. */
	अगर (mode == POLARIS_AVMODE_DIGITAL) अणु
		पंचांगp |= PWR_RESETOUT_EN;
		value[0] = (u8) पंचांगp;
		value[1] = (u8) (पंचांगp >> 8);
		value[2] = (u8) (पंचांगp >> 16);
		value[3] = (u8) (पंचांगp >> 24);
		status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
						PWR_CTL_EN, value, 4);
		msleep(PWR_SLEEP_INTERVAL);
	पूर्ण

	/* update घातer control क्रम afe */
	status = cx231xx_afe_update_घातer_control(dev, mode);

	/* update घातer control क्रम i2s_blk */
	status = cx231xx_i2s_blk_update_घातer_control(dev, mode);

	status = cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, PWR_CTL_EN, value,
				       4);

	वापस status;
पूर्ण

पूर्णांक cx231xx_घातer_suspend(काष्ठा cx231xx *dev)
अणु
	u8 value[4] = अणु 0, 0, 0, 0 पूर्ण;
	u32 पंचांगp = 0;
	पूर्णांक status = 0;

	status = cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, PWR_CTL_EN,
				       value, 4);
	अगर (status > 0)
		वापस status;

	पंचांगp = le32_to_cpu(*((__le32 *) value));
	पंचांगp &= (~PWR_MODE_MASK);

	value[0] = (u8) पंचांगp;
	value[1] = (u8) (पंचांगp >> 8);
	value[2] = (u8) (पंचांगp >> 16);
	value[3] = (u8) (पंचांगp >> 24);
	status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER, PWR_CTL_EN,
					value, 4);

	वापस status;
पूर्ण

/******************************************************************************
 *                  S T R E A M    C O N T R O L   functions                  *
 ******************************************************************************/
पूर्णांक cx231xx_start_stream(काष्ठा cx231xx *dev, u32 ep_mask)
अणु
	u8 value[4] = अणु 0x0, 0x0, 0x0, 0x0 पूर्ण;
	u32 पंचांगp = 0;
	पूर्णांक status = 0;

	dev_dbg(dev->dev, "%s: ep_mask = %x\n", __func__, ep_mask);
	status = cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, EP_MODE_SET,
				       value, 4);
	अगर (status < 0)
		वापस status;

	पंचांगp = le32_to_cpu(*((__le32 *) value));
	पंचांगp |= ep_mask;
	value[0] = (u8) पंचांगp;
	value[1] = (u8) (पंचांगp >> 8);
	value[2] = (u8) (पंचांगp >> 16);
	value[3] = (u8) (पंचांगp >> 24);

	status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER, EP_MODE_SET,
					value, 4);

	वापस status;
पूर्ण

पूर्णांक cx231xx_stop_stream(काष्ठा cx231xx *dev, u32 ep_mask)
अणु
	u8 value[4] = अणु 0x0, 0x0, 0x0, 0x0 पूर्ण;
	u32 पंचांगp = 0;
	पूर्णांक status = 0;

	dev_dbg(dev->dev, "%s: ep_mask = %x\n", __func__, ep_mask);
	status =
	    cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, EP_MODE_SET, value, 4);
	अगर (status < 0)
		वापस status;

	पंचांगp = le32_to_cpu(*((__le32 *) value));
	पंचांगp &= (~ep_mask);
	value[0] = (u8) पंचांगp;
	value[1] = (u8) (पंचांगp >> 8);
	value[2] = (u8) (पंचांगp >> 16);
	value[3] = (u8) (पंचांगp >> 24);

	status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER, EP_MODE_SET,
					value, 4);

	वापस status;
पूर्ण

पूर्णांक cx231xx_initialize_stream_xfer(काष्ठा cx231xx *dev, u32 media_type)
अणु
	पूर्णांक status = 0;
	u32 value = 0;
	u8 val[4] = अणु 0, 0, 0, 0 पूर्ण;

	अगर (dev->udev->speed == USB_SPEED_HIGH) अणु
		चयन (media_type) अणु
		हाल Audio:
			dev_dbg(dev->dev,
				"%s: Audio enter HANC\n", __func__);
			status =
			    cx231xx_mode_रेजिस्टर(dev, TS_MODE_REG, 0x9300);
			अवरोध;

		हाल Vbi:
			dev_dbg(dev->dev,
				"%s: set vanc registers\n", __func__);
			status = cx231xx_mode_रेजिस्टर(dev, TS_MODE_REG, 0x300);
			अवरोध;

		हाल Sliced_cc:
			dev_dbg(dev->dev,
				"%s: set hanc registers\n", __func__);
			status =
			    cx231xx_mode_रेजिस्टर(dev, TS_MODE_REG, 0x1300);
			अवरोध;

		हाल Raw_Video:
			dev_dbg(dev->dev,
				"%s: set video registers\n", __func__);
			status = cx231xx_mode_रेजिस्टर(dev, TS_MODE_REG, 0x100);
			अवरोध;

		हाल TS1_serial_mode:
			dev_dbg(dev->dev,
				"%s: set ts1 registers", __func__);

			अगर (dev->board.has_417) अणु
				dev_dbg(dev->dev,
					"%s: MPEG\n", __func__);
				value &= 0xFFFFFFFC;
				value |= 0x3;

				status = cx231xx_mode_रेजिस्टर(dev,
							 TS_MODE_REG, value);

				val[0] = 0x04;
				val[1] = 0xA3;
				val[2] = 0x3B;
				val[3] = 0x00;
				status = cx231xx_ग_लिखो_ctrl_reg(dev,
							VRT_SET_REGISTER,
							TS1_CFG_REG, val, 4);

				val[0] = 0x00;
				val[1] = 0x08;
				val[2] = 0x00;
				val[3] = 0x08;
				status = cx231xx_ग_लिखो_ctrl_reg(dev,
							VRT_SET_REGISTER,
							TS1_LENGTH_REG, val, 4);
			पूर्ण अन्यथा अणु
				dev_dbg(dev->dev, "%s: BDA\n", __func__);
				status = cx231xx_mode_रेजिस्टर(dev,
							 TS_MODE_REG, 0x101);
				status = cx231xx_mode_रेजिस्टर(dev,
							TS1_CFG_REG, 0x010);
			पूर्ण
			अवरोध;

		हाल TS1_parallel_mode:
			dev_dbg(dev->dev,
				"%s: set ts1 parallel mode registers\n",
				__func__);
			status = cx231xx_mode_रेजिस्टर(dev, TS_MODE_REG, 0x100);
			status = cx231xx_mode_रेजिस्टर(dev, TS1_CFG_REG, 0x400);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = cx231xx_mode_रेजिस्टर(dev, TS_MODE_REG, 0x101);
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक cx231xx_capture_start(काष्ठा cx231xx *dev, पूर्णांक start, u8 media_type)
अणु
	पूर्णांक rc = -1;
	u32 ep_mask = -1;
	काष्ठा pcb_config *pcb_config;

	/* get EP क्रम media type */
	pcb_config = (काष्ठा pcb_config *)&dev->current_pcb_config;

	अगर (pcb_config->config_num) अणु
		चयन (media_type) अणु
		हाल Raw_Video:
			ep_mask = ENABLE_EP4;	/* ep4  [00:1000] */
			अवरोध;
		हाल Audio:
			ep_mask = ENABLE_EP3;	/* ep3  [00:0100] */
			अवरोध;
		हाल Vbi:
			ep_mask = ENABLE_EP5;	/* ep5 [01:0000] */
			अवरोध;
		हाल Sliced_cc:
			ep_mask = ENABLE_EP6;	/* ep6 [10:0000] */
			अवरोध;
		हाल TS1_serial_mode:
		हाल TS1_parallel_mode:
			ep_mask = ENABLE_EP1;	/* ep1 [00:0001] */
			अवरोध;
		हाल TS2:
			ep_mask = ENABLE_EP2;	/* ep2 [00:0010] */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (start) अणु
		rc = cx231xx_initialize_stream_xfer(dev, media_type);

		अगर (rc < 0)
			वापस rc;

		/* enable video capture */
		अगर (ep_mask > 0)
			rc = cx231xx_start_stream(dev, ep_mask);
	पूर्ण अन्यथा अणु
		/* disable video capture */
		अगर (ep_mask > 0)
			rc = cx231xx_stop_stream(dev, ep_mask);
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_capture_start);

/*****************************************************************************
*                   G P I O   B I T control functions                        *
******************************************************************************/
अटल पूर्णांक cx231xx_set_gpio_bit(काष्ठा cx231xx *dev, u32 gpio_bit, u32 gpio_val)
अणु
	पूर्णांक status = 0;

	gpio_val = (__क्रमce u32)cpu_to_le32(gpio_val);
	status = cx231xx_send_gpio_cmd(dev, gpio_bit, (u8 *)&gpio_val, 4, 0, 0);

	वापस status;
पूर्ण

अटल पूर्णांक cx231xx_get_gpio_bit(काष्ठा cx231xx *dev, u32 gpio_bit, u32 *gpio_val)
अणु
	__le32 पंचांगp;
	पूर्णांक status = 0;

	status = cx231xx_send_gpio_cmd(dev, gpio_bit, (u8 *)&पंचांगp, 4, 0, 1);
	*gpio_val = le32_to_cpu(पंचांगp);

	वापस status;
पूर्ण

/*
* cx231xx_set_gpio_direction
*      Sets the direction of the GPIO pin to input or output
*
* Parameters :
*      pin_number : The GPIO Pin number to program the direction क्रम
*                   from 0 to 31
*      pin_value : The Direction of the GPIO Pin under reference.
*                      0 = Input direction
*                      1 = Output direction
*/
पूर्णांक cx231xx_set_gpio_direction(काष्ठा cx231xx *dev,
			       पूर्णांक pin_number, पूर्णांक pin_value)
अणु
	पूर्णांक status = 0;
	u32 value = 0;

	/* Check क्रम valid pin_number - अगर 32 , bail out */
	अगर (pin_number >= 32)
		वापस -EINVAL;

	/* input */
	अगर (pin_value == 0)
		value = dev->gpio_dir & (~(1 << pin_number));	/* clear */
	अन्यथा
		value = dev->gpio_dir | (1 << pin_number);

	status = cx231xx_set_gpio_bit(dev, value, dev->gpio_val);

	/* cache the value क्रम future */
	dev->gpio_dir = value;

	वापस status;
पूर्ण

/*
* cx231xx_set_gpio_value
*      Sets the value of the GPIO pin to Logic high or low. The Pin under
*      reference should ALREADY BE SET IN OUTPUT MODE !!!!!!!!!
*
* Parameters :
*      pin_number : The GPIO Pin number to program the direction क्रम
*      pin_value : The value of the GPIO Pin under reference.
*                      0 = set it to 0
*                      1 = set it to 1
*/
पूर्णांक cx231xx_set_gpio_value(काष्ठा cx231xx *dev, पूर्णांक pin_number, पूर्णांक pin_value)
अणु
	पूर्णांक status = 0;
	u32 value = 0;

	/* Check क्रम valid pin_number - अगर 0xFF , bail out */
	अगर (pin_number >= 32)
		वापस -EINVAL;

	/* first करो a sanity check - अगर the Pin is not output, make it output */
	अगर ((dev->gpio_dir & (1 << pin_number)) == 0x00) अणु
		/* It was in input mode */
		value = dev->gpio_dir | (1 << pin_number);
		dev->gpio_dir = value;
		status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
					      dev->gpio_val);
		value = 0;
	पूर्ण

	अगर (pin_value == 0)
		value = dev->gpio_val & (~(1 << pin_number));
	अन्यथा
		value = dev->gpio_val | (1 << pin_number);

	/* store the value */
	dev->gpio_val = value;

	/* toggle bit0 of GP_IO */
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	वापस status;
पूर्ण

/*****************************************************************************
*                      G P I O I2C related functions                         *
******************************************************************************/
पूर्णांक cx231xx_gpio_i2c_start(काष्ठा cx231xx *dev)
अणु
	पूर्णांक status = 0;

	/* set SCL to output 1 ; set SDA to output 1 */
	dev->gpio_dir |= 1 << dev->board.tuner_scl_gpio;
	dev->gpio_dir |= 1 << dev->board.tuner_sda_gpio;
	dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
	dev->gpio_val |= 1 << dev->board.tuner_sda_gpio;

	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);
	अगर (status < 0)
		वापस -EINVAL;

	/* set SCL to output 1; set SDA to output 0 */
	dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
	dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);

	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);
	अगर (status < 0)
		वापस -EINVAL;

	/* set SCL to output 0; set SDA to output 0      */
	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);

	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);
	अगर (status < 0)
		वापस -EINVAL;

	वापस status;
पूर्ण

पूर्णांक cx231xx_gpio_i2c_end(काष्ठा cx231xx *dev)
अणु
	पूर्णांक status = 0;

	/* set SCL to output 0; set SDA to output 0      */
	dev->gpio_dir |= 1 << dev->board.tuner_scl_gpio;
	dev->gpio_dir |= 1 << dev->board.tuner_sda_gpio;

	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);

	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);
	अगर (status < 0)
		वापस -EINVAL;

	/* set SCL to output 1; set SDA to output 0      */
	dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
	dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);

	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);
	अगर (status < 0)
		वापस -EINVAL;

	/* set SCL to input ,release SCL cable control
	   set SDA to input ,release SDA cable control */
	dev->gpio_dir &= ~(1 << dev->board.tuner_scl_gpio);
	dev->gpio_dir &= ~(1 << dev->board.tuner_sda_gpio);

	status =
	    cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);
	अगर (status < 0)
		वापस -EINVAL;

	वापस status;
पूर्ण

पूर्णांक cx231xx_gpio_i2c_ग_लिखो_byte(काष्ठा cx231xx *dev, u8 data)
अणु
	पूर्णांक status = 0;
	u8 i;

	/* set SCL to output ; set SDA to output */
	dev->gpio_dir |= 1 << dev->board.tuner_scl_gpio;
	dev->gpio_dir |= 1 << dev->board.tuner_sda_gpio;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (((data << i) & 0x80) == 0) अणु
			/* set SCL to output 0; set SDA to output 0     */
			dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
			dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);
			status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
						      dev->gpio_val);

			/* set SCL to output 1; set SDA to output 0     */
			dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
			status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
						      dev->gpio_val);

			/* set SCL to output 0; set SDA to output 0     */
			dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
			status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
						      dev->gpio_val);
		पूर्ण अन्यथा अणु
			/* set SCL to output 0; set SDA to output 1     */
			dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
			dev->gpio_val |= 1 << dev->board.tuner_sda_gpio;
			status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
						      dev->gpio_val);

			/* set SCL to output 1; set SDA to output 1     */
			dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
			status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
						      dev->gpio_val);

			/* set SCL to output 0; set SDA to output 1     */
			dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
			status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
						      dev->gpio_val);
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक cx231xx_gpio_i2c_पढ़ो_byte(काष्ठा cx231xx *dev, u8 *buf)
अणु
	u8 value = 0;
	पूर्णांक status = 0;
	u32 gpio_logic_value = 0;
	u8 i;

	/* पढ़ो byte */
	क्रम (i = 0; i < 8; i++) अणु	/* send ग_लिखो I2c addr */

		/* set SCL to output 0; set SDA to input */
		dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
		status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
					      dev->gpio_val);

		/* set SCL to output 1; set SDA to input */
		dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
		status = cx231xx_set_gpio_bit(dev, dev->gpio_dir,
					      dev->gpio_val);

		/* get SDA data bit */
		gpio_logic_value = dev->gpio_val;
		status = cx231xx_get_gpio_bit(dev, dev->gpio_dir,
					      &dev->gpio_val);
		अगर ((dev->gpio_val & (1 << dev->board.tuner_sda_gpio)) != 0)
			value |= (1 << (8 - i - 1));

		dev->gpio_val = gpio_logic_value;
	पूर्ण

	/* set SCL to output 0,finish the पढ़ो latest SCL संकेत.
	   !!!set SDA to input, never to modअगरy SDA direction at
	   the same बार */
	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	/* store the value */
	*buf = value & 0xff;

	वापस status;
पूर्ण

पूर्णांक cx231xx_gpio_i2c_पढ़ो_ack(काष्ठा cx231xx *dev)
अणु
	पूर्णांक status = 0;
	u32 gpio_logic_value = 0;
	पूर्णांक nCnt = 10;
	पूर्णांक nInit = nCnt;

	/* घड़ी stretch; set SCL to input; set SDA to input;
	   get SCL value till SCL = 1 */
	dev->gpio_dir &= ~(1 << dev->board.tuner_sda_gpio);
	dev->gpio_dir &= ~(1 << dev->board.tuner_scl_gpio);

	gpio_logic_value = dev->gpio_val;
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	करो अणु
		msleep(2);
		status = cx231xx_get_gpio_bit(dev, dev->gpio_dir,
					      &dev->gpio_val);
		nCnt--;
	पूर्ण जबतक (((dev->gpio_val &
			  (1 << dev->board.tuner_scl_gpio)) == 0) &&
			 (nCnt > 0));

	अगर (nCnt == 0)
		dev_dbg(dev->dev,
			"No ACK after %d msec -GPIO I2C failed!",
			nInit * 10);

	/*
	 * पढ़ोAck
	 * through घड़ी stretch, slave has given a SCL संकेत,
	 * so the SDA data can be directly पढ़ो.
	 */
	status = cx231xx_get_gpio_bit(dev, dev->gpio_dir, &dev->gpio_val);

	अगर ((dev->gpio_val & 1 << dev->board.tuner_sda_gpio) == 0) अणु
		dev->gpio_val = gpio_logic_value;
		dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);
		status = 0;
	पूर्ण अन्यथा अणु
		dev->gpio_val = gpio_logic_value;
		dev->gpio_val |= (1 << dev->board.tuner_sda_gpio);
	पूर्ण

	/* पढ़ो SDA end, set the SCL to output 0, after this operation,
	   SDA direction can be changed. */
	dev->gpio_val = gpio_logic_value;
	dev->gpio_dir |= (1 << dev->board.tuner_scl_gpio);
	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	वापस status;
पूर्ण

पूर्णांक cx231xx_gpio_i2c_ग_लिखो_ack(काष्ठा cx231xx *dev)
अणु
	पूर्णांक status = 0;

	/* set SDA to output */
	dev->gpio_dir |= 1 << dev->board.tuner_sda_gpio;
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	/* set SCL = 0 (output); set SDA = 0 (output) */
	dev->gpio_val &= ~(1 << dev->board.tuner_sda_gpio);
	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	/* set SCL = 1 (output); set SDA = 0 (output) */
	dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	/* set SCL = 0 (output); set SDA = 0 (output) */
	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	/* set SDA to input,and then the slave will पढ़ो data from SDA. */
	dev->gpio_dir &= ~(1 << dev->board.tuner_sda_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	वापस status;
पूर्ण

पूर्णांक cx231xx_gpio_i2c_ग_लिखो_nak(काष्ठा cx231xx *dev)
अणु
	पूर्णांक status = 0;

	/* set scl to output ; set sda to input */
	dev->gpio_dir |= 1 << dev->board.tuner_scl_gpio;
	dev->gpio_dir &= ~(1 << dev->board.tuner_sda_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	/* set scl to output 0; set sda to input */
	dev->gpio_val &= ~(1 << dev->board.tuner_scl_gpio);
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	/* set scl to output 1; set sda to input */
	dev->gpio_val |= 1 << dev->board.tuner_scl_gpio;
	status = cx231xx_set_gpio_bit(dev, dev->gpio_dir, dev->gpio_val);

	वापस status;
पूर्ण

/*****************************************************************************
*                      G P I O I2C related functions                         *
******************************************************************************/
/* cx231xx_gpio_i2c_पढ़ो
 * Function to पढ़ो data from gpio based I2C पूर्णांकerface
 */
पूर्णांक cx231xx_gpio_i2c_पढ़ो(काष्ठा cx231xx *dev, u8 dev_addr, u8 *buf, u8 len)
अणु
	पूर्णांक status = 0;
	पूर्णांक i = 0;

	/* get the lock */
	mutex_lock(&dev->gpio_i2c_lock);

	/* start */
	status = cx231xx_gpio_i2c_start(dev);

	/* ग_लिखो dev_addr */
	status = cx231xx_gpio_i2c_ग_लिखो_byte(dev, (dev_addr << 1) + 1);

	/* पढ़ोAck */
	status = cx231xx_gpio_i2c_पढ़ो_ack(dev);

	/* पढ़ो data */
	क्रम (i = 0; i < len; i++) अणु
		/* पढ़ो data */
		buf[i] = 0;
		status = cx231xx_gpio_i2c_पढ़ो_byte(dev, &buf[i]);

		अगर ((i + 1) != len) अणु
			/* only करो ग_लिखो ack अगर we more length */
			status = cx231xx_gpio_i2c_ग_लिखो_ack(dev);
		पूर्ण
	पूर्ण

	/* ग_लिखो NAK - inक्रमm पढ़ोs are complete */
	status = cx231xx_gpio_i2c_ग_लिखो_nak(dev);

	/* ग_लिखो end */
	status = cx231xx_gpio_i2c_end(dev);

	/* release the lock */
	mutex_unlock(&dev->gpio_i2c_lock);

	वापस status;
पूर्ण

/* cx231xx_gpio_i2c_ग_लिखो
 * Function to ग_लिखो data to gpio based I2C पूर्णांकerface
 */
पूर्णांक cx231xx_gpio_i2c_ग_लिखो(काष्ठा cx231xx *dev, u8 dev_addr, u8 *buf, u8 len)
अणु
	पूर्णांक i = 0;

	/* get the lock */
	mutex_lock(&dev->gpio_i2c_lock);

	/* start */
	cx231xx_gpio_i2c_start(dev);

	/* ग_लिखो dev_addr */
	cx231xx_gpio_i2c_ग_लिखो_byte(dev, dev_addr << 1);

	/* पढ़ो Ack */
	cx231xx_gpio_i2c_पढ़ो_ack(dev);

	क्रम (i = 0; i < len; i++) अणु
		/* Write data */
		cx231xx_gpio_i2c_ग_लिखो_byte(dev, buf[i]);

		/* पढ़ो Ack */
		cx231xx_gpio_i2c_पढ़ो_ack(dev);
	पूर्ण

	/* ग_लिखो End */
	cx231xx_gpio_i2c_end(dev);

	/* release the lock */
	mutex_unlock(&dev->gpio_i2c_lock);

	वापस 0;
पूर्ण
