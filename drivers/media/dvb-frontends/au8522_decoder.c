<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Auvitek AU8522 QAM/8VSB demodulator driver and video decoder
 *
 * Copyright (C) 2009 Devin Heiपंचांगueller <dheiपंचांगueller@linuxtv.org>
 * Copyright (C) 2005-2008 Auvitek International, Ltd.
 */

/* Developer notes:
 *
 * Enough is implemented here क्रम CVBS and S-Video inमाला_दो, but the actual
 *  analog demodulator code isn't implemented (not needed क्रम xc5000 since it
 *  has its own demodulator and outमाला_दो CVBS)
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश "au8522.h"
#समावेश "au8522_priv.h"

MODULE_AUTHOR("Devin Heitmueller");
MODULE_LICENSE("GPL");

अटल पूर्णांक au8522_analog_debug;


module_param_named(analog_debug, au8522_analog_debug, पूर्णांक, 0644);

MODULE_PARM_DESC(analog_debug,
		 "Analog debugging messages [0=Off (default) 1=On]");

काष्ठा au8522_रेजिस्टर_config अणु
	u16 reg_name;
	u8 reg_val[8];
पूर्ण;


/* Video Decoder Filter Coefficients
   The values are as follows from left to right
   0="ATV RF" 1="ATV RF13" 2="CVBS" 3="S-Video" 4="PAL" 5=CVBS13" 6="SVideo13"
*/
अटल स्थिर काष्ठा au8522_रेजिस्टर_config filter_coef[] = अणु
	अणुAU8522_FILTER_COEF_R410, अणु0x25, 0x00, 0x25, 0x25, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R411, अणु0x20, 0x00, 0x20, 0x20, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R412, अणु0x03, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R413, अणु0xe6, 0x00, 0xe6, 0xe6, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R414, अणु0x40, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R415, अणु0x1b, 0x00, 0x1b, 0x1b, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R416, अणु0xc0, 0x00, 0xc0, 0x04, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R417, अणु0x04, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R418, अणु0x8c, 0x00, 0x8c, 0x8c, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R419, अणु0xa0, 0x40, 0xa0, 0xa0, 0x40, 0x40, 0x40पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R41A, अणु0x21, 0x09, 0x21, 0x21, 0x09, 0x09, 0x09पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R41B, अणु0x6c, 0x38, 0x6c, 0x6c, 0x38, 0x38, 0x38पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R41C, अणु0x03, 0xff, 0x03, 0x03, 0xff, 0xff, 0xffपूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R41D, अणु0xbf, 0xc7, 0xbf, 0xbf, 0xc7, 0xc7, 0xc7पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R41E, अणु0xa0, 0xdf, 0xa0, 0xa0, 0xdf, 0xdf, 0xdfपूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R41F, अणु0x10, 0x06, 0x10, 0x10, 0x06, 0x06, 0x06पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R420, अणु0xae, 0x30, 0xae, 0xae, 0x30, 0x30, 0x30पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R421, अणु0xc4, 0x01, 0xc4, 0xc4, 0x01, 0x01, 0x01पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R422, अणु0x54, 0xdd, 0x54, 0x54, 0xdd, 0xdd, 0xddपूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R423, अणु0xd0, 0xaf, 0xd0, 0xd0, 0xaf, 0xaf, 0xafपूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R424, अणु0x1c, 0xf7, 0x1c, 0x1c, 0xf7, 0xf7, 0xf7पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R425, अणु0x76, 0xdb, 0x76, 0x76, 0xdb, 0xdb, 0xdbपूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R426, अणु0x61, 0xc0, 0x61, 0x61, 0xc0, 0xc0, 0xc0पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R427, अणु0xd1, 0x2f, 0xd1, 0xd1, 0x2f, 0x2f, 0x2fपूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R428, अणु0x84, 0xd8, 0x84, 0x84, 0xd8, 0xd8, 0xd8पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R429, अणु0x06, 0xfb, 0x06, 0x06, 0xfb, 0xfb, 0xfbपूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R42A, अणु0x21, 0xd5, 0x21, 0x21, 0xd5, 0xd5, 0xd5पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R42B, अणु0x0a, 0x3e, 0x0a, 0x0a, 0x3e, 0x3e, 0x3eपूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R42C, अणु0xe6, 0x15, 0xe6, 0xe6, 0x15, 0x15, 0x15पूर्ण पूर्ण,
	अणुAU8522_FILTER_COEF_R42D, अणु0x01, 0x34, 0x01, 0x01, 0x34, 0x34, 0x34पूर्ण पूर्ण,

पूर्ण;
#घोषणा NUM_FILTER_COEF (माप(filter_coef)\
			 / माप(काष्ठा au8522_रेजिस्टर_config))


/* Registers 0x060b through 0x0652 are the LP Filter coefficients
   The values are as follows from left to right
   0="SIF" 1="ATVRF/ATVRF13"
   Note: the "ATVRF/ATVRF13" mode has never been tested
*/
अटल स्थिर काष्ठा au8522_रेजिस्टर_config lpfilter_coef[] = अणु
	अणु0x060b, अणु0x21, 0x0bपूर्ण पूर्ण,
	अणु0x060c, अणु0xad, 0xadपूर्ण पूर्ण,
	अणु0x060d, अणु0x70, 0xf0पूर्ण पूर्ण,
	अणु0x060e, अणु0xea, 0xe9पूर्ण पूर्ण,
	अणु0x060f, अणु0xdd, 0xddपूर्ण पूर्ण,
	अणु0x0610, अणु0x08, 0x64पूर्ण पूर्ण,
	अणु0x0611, अणु0x60, 0x60पूर्ण पूर्ण,
	अणु0x0612, अणु0xf8, 0xb2पूर्ण पूर्ण,
	अणु0x0613, अणु0x01, 0x02पूर्ण पूर्ण,
	अणु0x0614, अणु0xe4, 0xb4पूर्ण पूर्ण,
	अणु0x0615, अणु0x19, 0x02पूर्ण पूर्ण,
	अणु0x0616, अणु0xae, 0x2eपूर्ण पूर्ण,
	अणु0x0617, अणु0xee, 0xc5पूर्ण पूर्ण,
	अणु0x0618, अणु0x56, 0x56पूर्ण पूर्ण,
	अणु0x0619, अणु0x30, 0x58पूर्ण पूर्ण,
	अणु0x061a, अणु0xf9, 0xf8पूर्ण पूर्ण,
	अणु0x061b, अणु0x24, 0x64पूर्ण पूर्ण,
	अणु0x061c, अणु0x07, 0x07पूर्ण पूर्ण,
	अणु0x061d, अणु0x30, 0x30पूर्ण पूर्ण,
	अणु0x061e, अणु0xa9, 0xedपूर्ण पूर्ण,
	अणु0x061f, अणु0x09, 0x0bपूर्ण पूर्ण,
	अणु0x0620, अणु0x42, 0xc2पूर्ण पूर्ण,
	अणु0x0621, अणु0x1d, 0x2aपूर्ण पूर्ण,
	अणु0x0622, अणु0xd6, 0x56पूर्ण पूर्ण,
	अणु0x0623, अणु0x95, 0x8bपूर्ण पूर्ण,
	अणु0x0624, अणु0x2b, 0x2bपूर्ण पूर्ण,
	अणु0x0625, अणु0x30, 0x24पूर्ण पूर्ण,
	अणु0x0626, अणु0x3e, 0x3eपूर्ण पूर्ण,
	अणु0x0627, अणु0x62, 0xe2पूर्ण पूर्ण,
	अणु0x0628, अणु0xe9, 0xf5पूर्ण पूर्ण,
	अणु0x0629, अणु0x99, 0x19पूर्ण पूर्ण,
	अणु0x062a, अणु0xd4, 0x11पूर्ण पूर्ण,
	अणु0x062b, अणु0x03, 0x04पूर्ण पूर्ण,
	अणु0x062c, अणु0xb5, 0x85पूर्ण पूर्ण,
	अणु0x062d, अणु0x1e, 0x20पूर्ण पूर्ण,
	अणु0x062e, अणु0x2a, 0xeaपूर्ण पूर्ण,
	अणु0x062f, अणु0xd7, 0xd2पूर्ण पूर्ण,
	अणु0x0630, अणु0x15, 0x15पूर्ण पूर्ण,
	अणु0x0631, अणु0xa3, 0xa9पूर्ण पूर्ण,
	अणु0x0632, अणु0x1f, 0x1fपूर्ण पूर्ण,
	अणु0x0633, अणु0xf9, 0xd1पूर्ण पूर्ण,
	अणु0x0634, अणु0xc0, 0xc3पूर्ण पूर्ण,
	अणु0x0635, अणु0x4d, 0x8dपूर्ण पूर्ण,
	अणु0x0636, अणु0x21, 0x31पूर्ण पूर्ण,
	अणु0x0637, अणु0x83, 0x83पूर्ण पूर्ण,
	अणु0x0638, अणु0x08, 0x8cपूर्ण पूर्ण,
	अणु0x0639, अणु0x19, 0x19पूर्ण पूर्ण,
	अणु0x063a, अणु0x45, 0xa5पूर्ण पूर्ण,
	अणु0x063b, अणु0xef, 0xecपूर्ण पूर्ण,
	अणु0x063c, अणु0x8a, 0x8aपूर्ण पूर्ण,
	अणु0x063d, अणु0xf4, 0xf6पूर्ण पूर्ण,
	अणु0x063e, अणु0x8f, 0x8fपूर्ण पूर्ण,
	अणु0x063f, अणु0x44, 0x0cपूर्ण पूर्ण,
	अणु0x0640, अणु0xef, 0xf0पूर्ण पूर्ण,
	अणु0x0641, अणु0x66, 0x66पूर्ण पूर्ण,
	अणु0x0642, अणु0xcc, 0xd2पूर्ण पूर्ण,
	अणु0x0643, अणु0x41, 0x41पूर्ण पूर्ण,
	अणु0x0644, अणु0x63, 0x93पूर्ण पूर्ण,
	अणु0x0645, अणु0x8e, 0x8eपूर्ण पूर्ण,
	अणु0x0646, अणु0xa2, 0x42पूर्ण पूर्ण,
	अणु0x0647, अणु0x7b, 0x7bपूर्ण पूर्ण,
	अणु0x0648, अणु0x04, 0x04पूर्ण पूर्ण,
	अणु0x0649, अणु0x00, 0x00पूर्ण पूर्ण,
	अणु0x064a, अणु0x40, 0x40पूर्ण पूर्ण,
	अणु0x064b, अणु0x8c, 0x98पूर्ण पूर्ण,
	अणु0x064c, अणु0x00, 0x00पूर्ण पूर्ण,
	अणु0x064d, अणु0x63, 0xc3पूर्ण पूर्ण,
	अणु0x064e, अणु0x04, 0x04पूर्ण पूर्ण,
	अणु0x064f, अणु0x20, 0x20पूर्ण पूर्ण,
	अणु0x0650, अणु0x00, 0x00पूर्ण पूर्ण,
	अणु0x0651, अणु0x40, 0x40पूर्ण पूर्ण,
	अणु0x0652, अणु0x01, 0x01पूर्ण पूर्ण,
पूर्ण;
#घोषणा NUM_LPFILTER_COEF (माप(lpfilter_coef)\
			   / माप(काष्ठा au8522_रेजिस्टर_config))

अटल अंतरभूत काष्ठा au8522_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा au8522_state, sd);
पूर्ण

अटल व्योम setup_decoder_शेषs(काष्ठा au8522_state *state, bool is_svideo)
अणु
	पूर्णांक i;
	पूर्णांक filter_coef_type;

	/* Provide reasonable शेषs क्रम picture tuning values */
	au8522_ग_लिखोreg(state, AU8522_TVDEC_SHARPNESSREG009H, 0x07);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_BRIGHTNESS_REG00AH, 0xed);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_CONTRAST_REG00BH, 0x79);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_SATURATION_CB_REG00CH, 0x80);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_SATURATION_CR_REG00DH, 0x80);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_HUE_H_REG00EH, 0x00);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_HUE_L_REG00FH, 0x00);

	/* Other decoder रेजिस्टरs */
	au8522_ग_लिखोreg(state, AU8522_TVDEC_INT_MASK_REG010H, 0x00);

	अगर (is_svideo)
		au8522_ग_लिखोreg(state, AU8522_VIDEO_MODE_REG011H, 0x04);
	अन्यथा
		au8522_ग_लिखोreg(state, AU8522_VIDEO_MODE_REG011H, 0x00);

	au8522_ग_लिखोreg(state, AU8522_TVDEC_PGA_REG012H,
			AU8522_TVDEC_PGA_REG012H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_MODE_REG015H,
			AU8522_TVDEC_COMB_MODE_REG015H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDED_DBG_MODE_REG060H,
			AU8522_TVDED_DBG_MODE_REG060H_CVBS);

	अगर (state->std == V4L2_STD_PAL_M) अणु
		au8522_ग_लिखोreg(state, AU8522_TVDEC_FORMAT_CTRL1_REG061H,
				AU8522_TVDEC_FORMAT_CTRL1_REG061H_FIELD_LEN_525 |
				AU8522_TVDEC_FORMAT_CTRL1_REG061H_LINE_LEN_63_492 |
				AU8522_TVDEC_FORMAT_CTRL1_REG061H_SUBCARRIER_NTSC_AUTO);
		au8522_ग_लिखोreg(state, AU8522_TVDEC_FORMAT_CTRL2_REG062H,
				AU8522_TVDEC_FORMAT_CTRL2_REG062H_STD_PAL_M);
	पूर्ण अन्यथा अणु
		/* NTSC */
		au8522_ग_लिखोreg(state, AU8522_TVDEC_FORMAT_CTRL1_REG061H,
				AU8522_TVDEC_FORMAT_CTRL1_REG061H_FIELD_LEN_525 |
				AU8522_TVDEC_FORMAT_CTRL1_REG061H_LINE_LEN_63_492 |
				AU8522_TVDEC_FORMAT_CTRL1_REG061H_SUBCARRIER_NTSC_MN);
		au8522_ग_लिखोreg(state, AU8522_TVDEC_FORMAT_CTRL2_REG062H,
				AU8522_TVDEC_FORMAT_CTRL2_REG062H_STD_NTSC);
	पूर्ण
	au8522_ग_लिखोreg(state, AU8522_TVDEC_VCR_DET_LLIM_REG063H,
			AU8522_TVDEC_VCR_DET_LLIM_REG063H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_VCR_DET_HLIM_REG064H,
			AU8522_TVDEC_VCR_DET_HLIM_REG064H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_VDIF_THR1_REG065H,
			AU8522_TVDEC_COMB_VDIF_THR1_REG065H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_VDIF_THR2_REG066H,
			AU8522_TVDEC_COMB_VDIF_THR2_REG066H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_VDIF_THR3_REG067H,
			AU8522_TVDEC_COMB_VDIF_THR3_REG067H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_NOTCH_THR_REG068H,
			AU8522_TVDEC_COMB_NOTCH_THR_REG068H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_HDIF_THR1_REG069H,
			AU8522_TVDEC_COMB_HDIF_THR1_REG069H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_HDIF_THR2_REG06AH,
			AU8522_TVDEC_COMB_HDIF_THR2_REG06AH_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_HDIF_THR3_REG06BH,
			AU8522_TVDEC_COMB_HDIF_THR3_REG06BH_CVBS);
	अगर (is_svideo) अणु
		au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH,
				AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH_SVIDEO);
		au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH,
				AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH_SVIDEO);
	पूर्ण अन्यथा अणु
		au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH,
				AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH_CVBS);
		au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH,
				AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH_CVBS);
	पूर्ण
	au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_DCDIF_THR3_REG06EH,
			AU8522_TVDEC_COMB_DCDIF_THR3_REG06EH_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_UV_SEP_THR_REG06FH,
			AU8522_TVDEC_UV_SEP_THR_REG06FH_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_DC_THR1_NTSC_REG070H,
			AU8522_TVDEC_COMB_DC_THR1_NTSC_REG070H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_REG071H, AU8522_REG071H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_REG072H, AU8522_REG072H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_COMB_DC_THR2_NTSC_REG073H,
			AU8522_TVDEC_COMB_DC_THR2_NTSC_REG073H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_REG074H, AU8522_REG074H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_REG075H, AU8522_REG075H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_DCAGC_CTRL_REG077H,
			AU8522_TVDEC_DCAGC_CTRL_REG077H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_PIC_START_ADJ_REG078H,
			AU8522_TVDEC_PIC_START_ADJ_REG078H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_AGC_HIGH_LIMIT_REG079H,
			AU8522_TVDEC_AGC_HIGH_LIMIT_REG079H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_MACROVISION_SYNC_THR_REG07AH,
			AU8522_TVDEC_MACROVISION_SYNC_THR_REG07AH_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_INTRP_CTRL_REG07BH,
			AU8522_TVDEC_INTRP_CTRL_REG07BH_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TVDEC_AGC_LOW_LIMIT_REG0E4H,
			AU8522_TVDEC_AGC_LOW_LIMIT_REG0E4H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_TOREGAAGC_REG0E5H,
			AU8522_TOREGAAGC_REG0E5H_CVBS);
	au8522_ग_लिखोreg(state, AU8522_REG016H, AU8522_REG016H_CVBS);

	/*
	 * Despite what the table says, क्रम the HVR-950q we still need
	 * to be in CVBS mode क्रम the S-Video input (reason unknown).
	 */
	/* filter_coef_type = 3; */
	filter_coef_type = 5;

	/* Load the Video Decoder Filter Coefficients */
	क्रम (i = 0; i < NUM_FILTER_COEF; i++) अणु
		au8522_ग_लिखोreg(state, filter_coef[i].reg_name,
				filter_coef[i].reg_val[filter_coef_type]);
	पूर्ण

	/* It's not clear what these रेजिस्टरs are क्रम, but they are always
	   set to the same value regardless of what mode we're in */
	au8522_ग_लिखोreg(state, AU8522_REG42EH, 0x87);
	au8522_ग_लिखोreg(state, AU8522_REG42FH, 0xa2);
	au8522_ग_लिखोreg(state, AU8522_REG430H, 0xbf);
	au8522_ग_लिखोreg(state, AU8522_REG431H, 0xcb);
	au8522_ग_लिखोreg(state, AU8522_REG432H, 0xa1);
	au8522_ग_लिखोreg(state, AU8522_REG433H, 0x41);
	au8522_ग_लिखोreg(state, AU8522_REG434H, 0x88);
	au8522_ग_लिखोreg(state, AU8522_REG435H, 0xc2);
	au8522_ग_लिखोreg(state, AU8522_REG436H, 0x3c);
पूर्ण

अटल व्योम au8522_setup_cvbs_mode(काष्ठा au8522_state *state, u8 input_mode)
अणु
	/* here we're going to try the pre-programmed route */
	au8522_ग_लिखोreg(state, AU8522_MODULE_CLOCK_CONTROL_REG0A3H,
			AU8522_MODULE_CLOCK_CONTROL_REG0A3H_CVBS);

	/* PGA in स्वतःmatic mode */
	au8522_ग_लिखोreg(state, AU8522_PGA_CONTROL_REG082H, 0x00);

	/* Enable clamping control */
	au8522_ग_लिखोreg(state, AU8522_CLAMPING_CONTROL_REG083H, 0x00);

	au8522_ग_लिखोreg(state, AU8522_INPUT_CONTROL_REG081H, input_mode);

	setup_decoder_शेषs(state, false);

	au8522_ग_लिखोreg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
			AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_CVBS);
पूर्ण

अटल व्योम au8522_setup_cvbs_tuner_mode(काष्ठा au8522_state *state,
					 u8 input_mode)
अणु
	/* here we're going to try the pre-programmed route */
	au8522_ग_लिखोreg(state, AU8522_MODULE_CLOCK_CONTROL_REG0A3H,
			AU8522_MODULE_CLOCK_CONTROL_REG0A3H_CVBS);

	/* It's not clear why we have to have the PGA in स्वतःmatic mode जबतक
	   enabling clamp control, but it's what Winकरोws करोes */
	au8522_ग_लिखोreg(state, AU8522_PGA_CONTROL_REG082H, 0x00);

	/* Enable clamping control */
	au8522_ग_लिखोreg(state, AU8522_CLAMPING_CONTROL_REG083H, 0x0e);

	/* Disable स्वतःmatic PGA (since the CVBS is coming from the tuner) */
	au8522_ग_लिखोreg(state, AU8522_PGA_CONTROL_REG082H, 0x10);

	/* Set input mode to CVBS on channel 4 with SIF audio input enabled */
	au8522_ग_लिखोreg(state, AU8522_INPUT_CONTROL_REG081H, input_mode);

	setup_decoder_शेषs(state, false);

	au8522_ग_लिखोreg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
			AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_CVBS);
पूर्ण

अटल व्योम au8522_setup_svideo_mode(काष्ठा au8522_state *state,
				     u8 input_mode)
अणु
	au8522_ग_लिखोreg(state, AU8522_MODULE_CLOCK_CONTROL_REG0A3H,
			AU8522_MODULE_CLOCK_CONTROL_REG0A3H_SVIDEO);

	/* Set input to Y on Channe1, C on Channel 3 */
	au8522_ग_लिखोreg(state, AU8522_INPUT_CONTROL_REG081H, input_mode);

	/* PGA in स्वतःmatic mode */
	au8522_ग_लिखोreg(state, AU8522_PGA_CONTROL_REG082H, 0x00);

	/* Enable clamping control */
	au8522_ग_लिखोreg(state, AU8522_CLAMPING_CONTROL_REG083H, 0x00);

	setup_decoder_शेषs(state, true);

	au8522_ग_लिखोreg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
			AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_CVBS);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल व्योम disable_audio_input(काष्ठा au8522_state *state)
अणु
	au8522_ग_लिखोreg(state, AU8522_AUDIO_VOLUME_L_REG0F2H, 0x00);
	au8522_ग_लिखोreg(state, AU8522_AUDIO_VOLUME_R_REG0F3H, 0x00);
	au8522_ग_लिखोreg(state, AU8522_AUDIO_VOLUME_REG0F4H, 0x00);

	au8522_ग_लिखोreg(state, AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H, 0x04);
	au8522_ग_लिखोreg(state, AU8522_I2S_CTRL_2_REG112H, 0x02);

	au8522_ग_लिखोreg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
			AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_SVIDEO);
पूर्ण

/* 0=disable, 1=SIF */
अटल व्योम set_audio_input(काष्ठा au8522_state *state)
अणु
	पूर्णांक aud_input = state->aud_input;
	पूर्णांक i;

	/* Note that this function needs to be used in conjunction with setting
	   the input routing via रेजिस्टर 0x81 */

	अगर (aud_input == AU8522_AUDIO_NONE) अणु
		disable_audio_input(state);
		वापस;
	पूर्ण

	अगर (aud_input != AU8522_AUDIO_SIF) अणु
		/* The caller asked क्रम a mode we करोn't currently support */
		prपूर्णांकk(KERN_ERR "Unsupported audio mode requested! mode=%d\n",
		       aud_input);
		वापस;
	पूर्ण

	/* Load the Audio Decoder Filter Coefficients */
	क्रम (i = 0; i < NUM_LPFILTER_COEF; i++) अणु
		au8522_ग_लिखोreg(state, lpfilter_coef[i].reg_name,
				lpfilter_coef[i].reg_val[0]);
	पूर्ण

	/* Set the volume */
	au8522_ग_लिखोreg(state, AU8522_AUDIO_VOLUME_L_REG0F2H, 0x7F);
	au8522_ग_लिखोreg(state, AU8522_AUDIO_VOLUME_R_REG0F3H, 0x7F);
	au8522_ग_लिखोreg(state, AU8522_AUDIO_VOLUME_REG0F4H, 0xff);

	/* Not sure what this करोes */
	au8522_ग_लिखोreg(state, AU8522_REG0F9H, AU8522_REG0F9H_AUDIO);

	/* Setup the audio mode to stereo DBX */
	au8522_ग_लिखोreg(state, AU8522_AUDIO_MODE_REG0F1H, 0x82);
	msleep(70);

	/* Start the audio processing module */
	au8522_ग_लिखोreg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H, 0x9d);

	/* Set the audio frequency to 48 KHz */
	au8522_ग_लिखोreg(state, AU8522_AUDIOFREQ_REG606H, 0x03);

	/* Set the I2S parameters (WS, LSB, mode, sample rate */
	au8522_ग_लिखोreg(state, AU8522_I2S_CTRL_2_REG112H, 0xc2);

	/* Enable the I2S output */
	au8522_ग_लिखोreg(state, AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H, 0x09);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक au8522_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा au8522_state *state =
		container_of(ctrl->handler, काष्ठा au8522_state, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		au8522_ग_लिखोreg(state, AU8522_TVDEC_BRIGHTNESS_REG00AH,
				ctrl->val - 128);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		au8522_ग_लिखोreg(state, AU8522_TVDEC_CONTRAST_REG00BH,
				ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		au8522_ग_लिखोreg(state, AU8522_TVDEC_SATURATION_CB_REG00CH,
				ctrl->val);
		au8522_ग_लिखोreg(state, AU8522_TVDEC_SATURATION_CR_REG00DH,
				ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		au8522_ग_लिखोreg(state, AU8522_TVDEC_HUE_H_REG00EH,
				ctrl->val >> 8);
		au8522_ग_लिखोreg(state, AU8522_TVDEC_HUE_L_REG00FH,
				ctrl->val & 0xFF);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक au8522_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा au8522_state *state = to_state(sd);

	reg->val = au8522_पढ़ोreg(state, reg->reg & 0xffff);
	वापस 0;
पूर्ण

अटल पूर्णांक au8522_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा au8522_state *state = to_state(sd);

	au8522_ग_लिखोreg(state, reg->reg, reg->val & 0xff);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम au8522_video_set(काष्ठा au8522_state *state)
अणु
	u8 input_mode;

	au8522_ग_लिखोreg(state, 0xa4, 1 << 5);

	चयन (state->vid_input) अणु
	हाल AU8522_COMPOSITE_CH1:
		input_mode = AU8522_INPUT_CONTROL_REG081H_CVBS_CH1;
		au8522_setup_cvbs_mode(state, input_mode);
		अवरोध;
	हाल AU8522_COMPOSITE_CH2:
		input_mode = AU8522_INPUT_CONTROL_REG081H_CVBS_CH2;
		au8522_setup_cvbs_mode(state, input_mode);
		अवरोध;
	हाल AU8522_COMPOSITE_CH3:
		input_mode = AU8522_INPUT_CONTROL_REG081H_CVBS_CH3;
		au8522_setup_cvbs_mode(state, input_mode);
		अवरोध;
	हाल AU8522_COMPOSITE_CH4:
		input_mode = AU8522_INPUT_CONTROL_REG081H_CVBS_CH4;
		au8522_setup_cvbs_mode(state, input_mode);
		अवरोध;
	हाल AU8522_SVIDEO_CH13:
		input_mode = AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH13;
		au8522_setup_svideo_mode(state, input_mode);
		अवरोध;
	हाल AU8522_SVIDEO_CH24:
		input_mode = AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH24;
		au8522_setup_svideo_mode(state, input_mode);
		अवरोध;
	शेष:
	हाल AU8522_COMPOSITE_CH4_SIF:
		input_mode = AU8522_INPUT_CONTROL_REG081H_CVBS_CH4_SIF;
		au8522_setup_cvbs_tuner_mode(state, input_mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक au8522_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा au8522_state *state = to_state(sd);

	अगर (enable) अणु
		/*
		 * Clear out any state associated with the digital side of the
		 * chip, so that when it माला_लो घातered back up it won't think
		 * that it is alपढ़ोy tuned
		 */
		state->current_frequency = 0;

		au8522_ग_लिखोreg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
				0x01);
		msleep(10);

		au8522_video_set(state);
		set_audio_input(state);

		state->operational_mode = AU8522_ANALOG_MODE;
	पूर्ण अन्यथा अणु
		/* This करोes not completely घातer करोwn the device
		   (it only reduces it from around 140ma to 80ma) */
		au8522_ग_लिखोreg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
				1 << 5);
		state->operational_mode = AU8522_SUSPEND_MODE;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक au8522_s_video_routing(काष्ठा v4l2_subdev *sd,
					u32 input, u32 output, u32 config)
अणु
	काष्ठा au8522_state *state = to_state(sd);

	चयन (input) अणु
	हाल AU8522_COMPOSITE_CH1:
	हाल AU8522_SVIDEO_CH13:
	हाल AU8522_COMPOSITE_CH4_SIF:
		state->vid_input = input;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "au8522 mode not currently supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (state->operational_mode == AU8522_ANALOG_MODE)
		au8522_video_set(state);

	वापस 0;
पूर्ण

अटल पूर्णांक au8522_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा au8522_state *state = to_state(sd);

	अगर ((std & (V4L2_STD_PAL_M | V4L2_STD_NTSC_M)) == 0)
		वापस -EINVAL;

	state->std = std;

	अगर (state->operational_mode == AU8522_ANALOG_MODE)
		au8522_video_set(state);

	वापस 0;
पूर्ण

अटल पूर्णांक au8522_s_audio_routing(काष्ठा v4l2_subdev *sd,
					u32 input, u32 output, u32 config)
अणु
	काष्ठा au8522_state *state = to_state(sd);

	state->aud_input = input;

	अगर (state->operational_mode == AU8522_ANALOG_MODE)
		set_audio_input(state);

	वापस 0;
पूर्ण

अटल पूर्णांक au8522_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	पूर्णांक val = 0;
	काष्ठा au8522_state *state = to_state(sd);
	u8 lock_status;
	u8 pll_status;

	/* Interrogate the decoder to see अगर we are getting a real संकेत */
	lock_status = au8522_पढ़ोreg(state, 0x00);
	pll_status = au8522_पढ़ोreg(state, 0x7e);
	अगर ((lock_status == 0xa2) && (pll_status & 0x10))
		vt->संकेत = 0xffff;
	अन्यथा
		vt->संकेत = 0x00;

	vt->capability |=
		V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_LANG1 |
		V4L2_TUNER_CAP_LANG2 | V4L2_TUNER_CAP_SAP;

	val = V4L2_TUNER_SUB_MONO;
	vt->rxsubchans = val;
	vt->audmode = V4L2_TUNER_MODE_STEREO;
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops au8522_core_ops = अणु
	.log_status = v4l2_ctrl_subdev_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = au8522_g_रेजिस्टर,
	.s_रेजिस्टर = au8522_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops au8522_tuner_ops = अणु
	.g_tuner = au8522_g_tuner,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops au8522_audio_ops = अणु
	.s_routing = au8522_s_audio_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops au8522_video_ops = अणु
	.s_routing = au8522_s_video_routing,
	.s_stream = au8522_s_stream,
	.s_std = au8522_s_std,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops au8522_ops = अणु
	.core = &au8522_core_ops,
	.tuner = &au8522_tuner_ops,
	.audio = &au8522_audio_ops,
	.video = &au8522_video_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops au8522_ctrl_ops = अणु
	.s_ctrl = au8522_s_ctrl,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल पूर्णांक au8522_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *did)
अणु
	काष्ठा au8522_state *state;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक instance;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	पूर्णांक ret;
#पूर्ण_अगर

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		वापस -EIO;
	पूर्ण

	/* allocate memory क्रम the पूर्णांकernal state */
	instance = au8522_get_state(&state, client->adapter, client->addr);
	चयन (instance) अणु
	हाल 0:
		prपूर्णांकk(KERN_ERR "au8522_decoder allocation failed\n");
		वापस -EIO;
	हाल 1:
		/* new demod instance */
		prपूर्णांकk(KERN_INFO "au8522_decoder creating new instance...\n");
		अवरोध;
	शेष:
		/* existing demod instance */
		prपूर्णांकk(KERN_INFO "au8522_decoder attach existing instance.\n");
		अवरोध;
	पूर्ण

	state->config.demod_address = 0x8e >> 1;
	state->i2c = client->adapter;

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &au8522_ops);
#अगर defined(CONFIG_MEDIA_CONTROLLER)

	state->pads[AU8522_PAD_IF_INPUT].flags = MEDIA_PAD_FL_SINK;
	state->pads[AU8522_PAD_IF_INPUT].sig_type = PAD_SIGNAL_ANALOG;
	state->pads[AU8522_PAD_VID_OUT].flags = MEDIA_PAD_FL_SOURCE;
	state->pads[AU8522_PAD_VID_OUT].sig_type = PAD_SIGNAL_DV;
	state->pads[AU8522_PAD_AUDIO_OUT].flags = MEDIA_PAD_FL_SOURCE;
	state->pads[AU8522_PAD_AUDIO_OUT].sig_type = PAD_SIGNAL_AUDIO;
	sd->entity.function = MEDIA_ENT_F_ATV_DECODER;

	ret = media_entity_pads_init(&sd->entity, ARRAY_SIZE(state->pads),
				state->pads);
	अगर (ret < 0) अणु
		v4l_info(client, "failed to initialize media entity!\n");
		वापस ret;
	पूर्ण
#पूर्ण_अगर

	hdl = &state->hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &au8522_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 109);
	v4l2_ctrl_new_std(hdl, &au8522_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1,
			AU8522_TVDEC_CONTRAST_REG00BH_CVBS);
	v4l2_ctrl_new_std(hdl, &au8522_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &au8522_ctrl_ops,
			V4L2_CID_HUE, -32768, 32767, 1, 0);
	sd->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		पूर्णांक err = hdl->error;

		v4l2_ctrl_handler_मुक्त(hdl);
		au8522_release_state(state);
		वापस err;
	पूर्ण

	state->c = client;
	state->std = V4L2_STD_NTSC_M;
	state->vid_input = AU8522_COMPOSITE_CH1;
	state->aud_input = AU8522_AUDIO_NONE;
	state->id = 8522;
	state->rev = 0;

	/* Jam खोलो the i2c gate to the tuner */
	au8522_ग_लिखोreg(state, 0x106, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक au8522_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	au8522_release_state(to_state(sd));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id au8522_id[] = अणु
	अणु"au8522", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, au8522_id);

अटल काष्ठा i2c_driver au8522_driver = अणु
	.driver = अणु
		.name	= "au8522",
	पूर्ण,
	.probe		= au8522_probe,
	.हटाओ		= au8522_हटाओ,
	.id_table	= au8522_id,
पूर्ण;

module_i2c_driver(au8522_driver);
