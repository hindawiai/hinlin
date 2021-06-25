<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 Texas Instruments Inc
 */
#अगर_अघोषित _VPBE_H
#घोषणा _VPBE_H

#समावेश <linux/videodev2.h>
#समावेश <linux/i2c.h>

#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/davinci/vpbe_osd.h>
#समावेश <media/davinci/vpbe_venc.h>
#समावेश <media/davinci/vpbe_types.h>

/* OSD configuration info */
काष्ठा osd_config_info अणु
	अक्षर module_name[32];
पूर्ण;

काष्ठा vpbe_output अणु
	काष्ठा v4l2_output output;
	/*
	 * If output capabilities include dv_timings, list supported timings
	 * below
	 */
	अक्षर *subdev_name;
	/*
	 * defualt_mode identअगरies the शेष timings set at the venc or
	 * बाह्यal encoder.
	 */
	अक्षर *शेष_mode;
	/*
	 * Fields below are used क्रम supporting multiple modes. For example,
	 * LCD panel might support dअगरferent modes and they are listed here.
	 * Similarly क्रम supporting बाह्यal encoders, lcd controller port
	 * requires a set of non-standard timing values to be listed here क्रम
	 * each supported mode since venc is used in non-standard timing mode
	 * क्रम पूर्णांकerfacing with बाह्यal encoder similar to configuring lcd
	 * panel timings
	 */
	अचिन्हित पूर्णांक num_modes;
	काष्ठा vpbe_enc_mode_info *modes;
	/*
	 * Bus configuration goes here क्रम बाह्यal encoders. Some encoders
	 * may require multiple पूर्णांकerface types क्रम each of the output. For
	 * example, SD modes would use YCC8 where as HD mode would use YCC16.
	 * Not sure अगर this is needed on a per mode basis instead of per
	 * output basis. If per mode is needed, we may have to move this to
	 * mode_info काष्ठाure
	 */
	u32 अगर_params;
पूर्ण;

/* encoder configuration info */
काष्ठा encoder_config_info अणु
	अक्षर module_name[32];
	/* Is this an i2c device ? */
	अचिन्हित पूर्णांक is_i2c:1;
	/* i2c subdevice board info */
	काष्ठा i2c_board_info board_info;
पूर्ण;

/*amplअगरier configuration info */
काष्ठा amp_config_info अणु
	अक्षर module_name[32];
	/* Is this an i2c device ? */
	अचिन्हित पूर्णांक is_i2c:1;
	/* i2c subdevice board info */
	काष्ठा i2c_board_info board_info;
पूर्ण;

/* काष्ठाure क्रम defining vpbe display subप्रणाली components */
काष्ठा vpbe_config अणु
	अक्षर module_name[32];
	/* i2c bus adapter no */
	पूर्णांक i2c_adapter_id;
	काष्ठा osd_config_info osd;
	काष्ठा encoder_config_info venc;
	/* बाह्यal encoder inक्रमmation goes here */
	पूर्णांक num_ext_encoders;
	काष्ठा encoder_config_info *ext_encoders;
	/* amplअगरier inक्रमmation goes here */
	काष्ठा amp_config_info *amp;
	अचिन्हित पूर्णांक num_outमाला_दो;
	/* Order is venc outमाला_दो followed by LCD and then बाह्यal encoders */
	काष्ठा vpbe_output *outमाला_दो;
पूर्ण;

काष्ठा vpbe_device;

काष्ठा vpbe_device_ops अणु
	/* Enumerate the outमाला_दो */
	पूर्णांक (*क्रमागत_outमाला_दो)(काष्ठा vpbe_device *vpbe_dev,
			    काष्ठा v4l2_output *output);

	/* Set output to the given index */
	पूर्णांक (*set_output)(काष्ठा vpbe_device *vpbe_dev,
			 पूर्णांक index);

	/* Get current output */
	अचिन्हित पूर्णांक (*get_output)(काष्ठा vpbe_device *vpbe_dev);

	/* Set DV preset at current output */
	पूर्णांक (*s_dv_timings)(काष्ठा vpbe_device *vpbe_dev,
			   काष्ठा v4l2_dv_timings *dv_timings);

	/* Get DV presets supported at the output */
	पूर्णांक (*g_dv_timings)(काष्ठा vpbe_device *vpbe_dev,
			   काष्ठा v4l2_dv_timings *dv_timings);

	/* Enumerate the DV Presets supported at the output */
	पूर्णांक (*क्रमागत_dv_timings)(काष्ठा vpbe_device *vpbe_dev,
			       काष्ठा v4l2_क्रमागत_dv_timings *timings_info);

	/* Set std at the output */
	पूर्णांक (*s_std)(काष्ठा vpbe_device *vpbe_dev, v4l2_std_id std_id);

	/* Get the current std at the output */
	पूर्णांक (*g_std)(काष्ठा vpbe_device *vpbe_dev, v4l2_std_id *std_id);

	/* initialize the device */
	पूर्णांक (*initialize)(काष्ठा device *dev, काष्ठा vpbe_device *vpbe_dev);

	/* De-initialize the device */
	व्योम (*deinitialize)(काष्ठा device *dev, काष्ठा vpbe_device *vpbe_dev);

	/* Get the current mode info */
	पूर्णांक (*get_mode_info)(काष्ठा vpbe_device *vpbe_dev,
			     काष्ठा vpbe_enc_mode_info*);

	/*
	 * Set the current mode in the encoder. Alternate way of setting
	 * standard or DV preset or custom timings in the encoder
	 */
	पूर्णांक (*set_mode)(काष्ठा vpbe_device *vpbe_dev,
			काष्ठा vpbe_enc_mode_info*);
	/* Power management operations */
	पूर्णांक (*suspend)(काष्ठा vpbe_device *vpbe_dev);
	पूर्णांक (*resume)(काष्ठा vpbe_device *vpbe_dev);
पूर्ण;

/* काष्ठा क्रम vpbe device */
काष्ठा vpbe_device अणु
	/* V4l2 device */
	काष्ठा v4l2_device v4l2_dev;
	/* vpbe dispay controller cfg */
	काष्ठा vpbe_config *cfg;
	/* parent device */
	काष्ठा device *pdev;
	/* बाह्यal encoder v4l2 sub devices */
	काष्ठा v4l2_subdev **encoders;
	/* current encoder index */
	पूर्णांक current_sd_index;
	/* बाह्यal amplअगरier v4l2 subdevice */
	काष्ठा v4l2_subdev *amp;
	काष्ठा mutex lock;
	/* device initialized */
	पूर्णांक initialized;
	/* vpbe dac घड़ी */
	काष्ठा clk *dac_clk;
	/* osd_device poपूर्णांकer */
	काष्ठा osd_state *osd_device;
	/* venc device poपूर्णांकer */
	काष्ठा venc_platक्रमm_data *venc_device;
	/*
	 * fields below are accessed by users of vpbe_device. Not the
	 * ones above
	 */

	/* current output */
	पूर्णांक current_out_index;
	/* lock used by caller to करो atomic operation on vpbe device */
	/* current timings set in the controller */
	काष्ठा vpbe_enc_mode_info current_timings;
	/* venc sub device */
	काष्ठा v4l2_subdev *venc;
	/* device operations below */
	काष्ठा vpbe_device_ops ops;
पूर्ण;

#पूर्ण_अगर
