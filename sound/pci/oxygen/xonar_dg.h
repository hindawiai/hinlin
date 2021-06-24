<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित XONAR_DG_H_INCLUDED
#घोषणा XONAR_DG_H_INCLUDED

#समावेश "oxygen.h"

#घोषणा GPIO_MAGIC		0x0008
#घोषणा GPIO_HP_DETECT		0x0010
#घोषणा GPIO_INPUT_ROUTE	0x0060
#घोषणा GPIO_HP_REAR		0x0080
#घोषणा GPIO_OUTPUT_ENABLE	0x0100

#घोषणा CAPTURE_SRC_MIC		0
#घोषणा CAPTURE_SRC_FP_MIC	1
#घोषणा CAPTURE_SRC_LINE	2
#घोषणा CAPTURE_SRC_AUX		3

#घोषणा PLAYBACK_DST_HP		0
#घोषणा PLAYBACK_DST_HP_FP	1
#घोषणा PLAYBACK_DST_MULTICH	2

क्रमागत cs4245_shaकरोw_operation अणु
	CS4245_SAVE_TO_SHADOW,
	CS4245_LOAD_FROM_SHADOW
पूर्ण;

काष्ठा dg अणु
	/* shaकरोw copy of the CS4245 रेजिस्टर space */
	अचिन्हित अक्षर cs4245_shaकरोw[17];
	/* output select: headphone/speakers */
	अचिन्हित अक्षर output_sel;
	/* volumes क्रम all capture sources */
	अक्षर input_vol[4][2];
	/* input select: mic/fp mic/line/aux */
	अचिन्हित अक्षर input_sel;
पूर्ण;

/* Xonar DG control routines */
पूर्णांक cs4245_ग_लिखो_spi(काष्ठा oxygen *chip, u8 reg);
पूर्णांक cs4245_पढ़ो_spi(काष्ठा oxygen *chip, u8 reg);
पूर्णांक cs4245_shaकरोw_control(काष्ठा oxygen *chip, क्रमागत cs4245_shaकरोw_operation op);
व्योम dg_init(काष्ठा oxygen *chip);
व्योम set_cs4245_dac_params(काष्ठा oxygen *chip,
				  काष्ठा snd_pcm_hw_params *params);
व्योम set_cs4245_adc_params(काष्ठा oxygen *chip,
				  काष्ठा snd_pcm_hw_params *params);
अचिन्हित पूर्णांक adjust_dg_dac_routing(काष्ठा oxygen *chip,
					  अचिन्हित पूर्णांक play_routing);
व्योम dump_cs4245_रेजिस्टरs(काष्ठा oxygen *chip,
				काष्ठा snd_info_buffer *buffer);
व्योम dg_suspend(काष्ठा oxygen *chip);
व्योम dg_resume(काष्ठा oxygen *chip);
व्योम dg_cleanup(काष्ठा oxygen *chip);

बाह्य स्थिर काष्ठा oxygen_model model_xonar_dg;

#पूर्ण_अगर
