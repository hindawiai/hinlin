<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 */

#अगर_अघोषित MSP3400_DRIVER_H
#घोषणा MSP3400_DRIVER_H

#समावेश <media/drv-पूर्णांकf/msp3400.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-mc.h>

/* ---------------------------------------------------------------------- */

/* This macro is allowed क्रम *स्थिरants* only, gcc must calculate it
   at compile समय.  Remember -- no भग्नs in kernel mode */
#घोषणा MSP_CARRIER(freq) ((पूर्णांक)((भग्न)(freq / 18.432) * (1 << 24)))

#घोषणा MSP_MODE_AM_DETECT   0
#घोषणा MSP_MODE_FM_RADIO    2
#घोषणा MSP_MODE_FM_TERRA    3
#घोषणा MSP_MODE_FM_SAT      4
#घोषणा MSP_MODE_FM_NICAM1   5
#घोषणा MSP_MODE_FM_NICAM2   6
#घोषणा MSP_MODE_AM_NICAM    7
#घोषणा MSP_MODE_BTSC        8
#घोषणा MSP_MODE_EXTERN      9

#घोषणा SCART_IN1     0
#घोषणा SCART_IN2     1
#घोषणा SCART_IN3     2
#घोषणा SCART_IN4     3
#घोषणा SCART_IN1_DA  4
#घोषणा SCART_IN2_DA  5
#घोषणा SCART_MONO    6
#घोषणा SCART_MUTE    7

#घोषणा SCART_DSP_IN  0
#घोषणा SCART1_OUT    1
#घोषणा SCART2_OUT    2

#घोषणा OPMODE_AUTO       -1
#घोषणा OPMODE_MANUAL      0
#घोषणा OPMODE_AUTODETECT  1   /* use स्वतःdetect (>= msp3410 only) */
#घोषणा OPMODE_AUTOSELECT  2   /* use स्वतःdetect & स्वतःselect (>= msp34xxG)   */

/* module parameters */
बाह्य पूर्णांक msp_debug;
बाह्य bool msp_once;
बाह्य bool msp_amsound;
बाह्य पूर्णांक msp_standard;
बाह्य bool msp_करोlby;
बाह्य पूर्णांक msp_stereo_thresh;

क्रमागत msp3400_pads अणु
	MSP3400_PAD_IF_INPUT,
	MSP3400_PAD_OUT,
	MSP3400_NUM_PADS
पूर्ण;

काष्ठा msp_state अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	पूर्णांक rev1, rev2;
	पूर्णांक ident;
	u8 has_nicam;
	u8 has_radio;
	u8 has_headphones;
	u8 has_ntsc_jp_d_k3;
	u8 has_scart2;
	u8 has_scart3;
	u8 has_scart4;
	u8 has_scart2_out;
	u8 has_scart2_out_volume;
	u8 has_i2s_conf;
	u8 has_subwoofer;
	u8 has_sound_processing;
	u8 has_भव_करोlby_surround;
	u8 has_करोlby_pro_logic;
	u8 क्रमce_btsc;

	पूर्णांक radio;
	पूर्णांक opmode;
	पूर्णांक std;
	पूर्णांक mode;
	v4l2_std_id v4l2_std, detected_std;
	पूर्णांक nicam_on;
	पूर्णांक acb;
	पूर्णांक in_scart;
	पूर्णांक i2s_mode;
	पूर्णांक मुख्य, second;	/* sound carrier */
	पूर्णांक input;
	u32 route_in;
	u32 route_out;

	/* v4l2 */
	पूर्णांक audmode;
	पूर्णांक rxsubchans;

	काष्ठा अणु
		/* volume cluster */
		काष्ठा v4l2_ctrl *volume;
		काष्ठा v4l2_ctrl *muted;
	पूर्ण;

	पूर्णांक scan_in_progress;

	/* thपढ़ो */
	काष्ठा task_काष्ठा   *kthपढ़ो;
	रुको_queue_head_t    wq;
	अचिन्हित पूर्णांक         restart:1;
	अचिन्हित पूर्णांक         watch_stereo:1;

#अगर IS_ENABLED(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_pad pads[MSP3400_NUM_PADS];
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा msp_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा msp_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा msp_state *ctrl_to_state(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस container_of(ctrl->handler, काष्ठा msp_state, hdl);
पूर्ण

/* msp3400-driver.c */
पूर्णांक msp_ग_लिखो_dem(काष्ठा i2c_client *client, पूर्णांक addr, पूर्णांक val);
पूर्णांक msp_ग_लिखो_dsp(काष्ठा i2c_client *client, पूर्णांक addr, पूर्णांक val);
पूर्णांक msp_पढ़ो_dem(काष्ठा i2c_client *client, पूर्णांक addr);
पूर्णांक msp_पढ़ो_dsp(काष्ठा i2c_client *client, पूर्णांक addr);
पूर्णांक msp_reset(काष्ठा i2c_client *client);
व्योम msp_set_scart(काष्ठा i2c_client *client, पूर्णांक in, पूर्णांक out);
व्योम msp_update_volume(काष्ठा msp_state *state);
पूर्णांक msp_sleep(काष्ठा msp_state *state, पूर्णांक समयout);

/* msp3400-kthपढ़ोs.c */
स्थिर अक्षर *msp_standard_std_name(पूर्णांक std);
व्योम msp_set_audmode(काष्ठा i2c_client *client);
पूर्णांक msp_detect_stereo(काष्ठा i2c_client *client);
पूर्णांक msp3400c_thपढ़ो(व्योम *data);
पूर्णांक msp3410d_thपढ़ो(व्योम *data);
पूर्णांक msp34xxg_thपढ़ो(व्योम *data);
व्योम msp3400c_set_mode(काष्ठा i2c_client *client, पूर्णांक mode);
व्योम msp3400c_set_carrier(काष्ठा i2c_client *client, पूर्णांक cकरो1, पूर्णांक cकरो2);

#पूर्ण_अगर /* MSP3400_DRIVER_H */
