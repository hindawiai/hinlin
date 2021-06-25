<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2011 Texas Instruments Inc
 */
#अगर_अघोषित _VPIF_TYPES_H
#घोषणा _VPIF_TYPES_H

#समावेश <linux/i2c.h>

#घोषणा VPIF_CAPTURE_MAX_CHANNELS	2
#घोषणा VPIF_DISPLAY_MAX_CHANNELS	2

क्रमागत vpअगर_अगर_type अणु
	VPIF_IF_BT656,
	VPIF_IF_BT1120,
	VPIF_IF_RAW_BAYER
पूर्ण;

काष्ठा vpअगर_पूर्णांकerface अणु
	क्रमागत vpअगर_अगर_type अगर_type;
	अचिन्हित hd_pol:1;
	अचिन्हित vd_pol:1;
	अचिन्हित fid_pol:1;
पूर्ण;

काष्ठा vpअगर_subdev_info अणु
	स्थिर अक्षर *name;
	काष्ठा i2c_board_info board_info;
पूर्ण;

काष्ठा vpअगर_output अणु
	काष्ठा v4l2_output output;
	स्थिर अक्षर *subdev_name;
	u32 input_route;
	u32 output_route;
पूर्ण;

काष्ठा vpअगर_display_chan_config अणु
	स्थिर काष्ठा vpअगर_output *outमाला_दो;
	पूर्णांक output_count;
	bool clip_en;
पूर्ण;

काष्ठा vpअगर_display_config अणु
	पूर्णांक (*set_घड़ी)(पूर्णांक, पूर्णांक);
	काष्ठा vpअगर_subdev_info *subdevinfo;
	पूर्णांक subdev_count;
	पूर्णांक i2c_adapter_id;
	काष्ठा vpअगर_display_chan_config chan_config[VPIF_DISPLAY_MAX_CHANNELS];
	स्थिर अक्षर *card_name;
पूर्ण;

काष्ठा vpअगर_input अणु
	काष्ठा v4l2_input input;
	अक्षर *subdev_name;
	u32 input_route;
	u32 output_route;
पूर्ण;

काष्ठा vpअगर_capture_chan_config अणु
	काष्ठा vpअगर_पूर्णांकerface vpअगर_अगर;
	काष्ठा vpअगर_input *inमाला_दो;
	पूर्णांक input_count;
पूर्ण;

काष्ठा vpअगर_capture_config अणु
	पूर्णांक (*setup_input_channel_mode)(पूर्णांक);
	पूर्णांक (*setup_input_path)(पूर्णांक, स्थिर अक्षर *);
	काष्ठा vpअगर_capture_chan_config chan_config[VPIF_CAPTURE_MAX_CHANNELS];
	काष्ठा vpअगर_subdev_info *subdev_info;
	पूर्णांक subdev_count;
	पूर्णांक i2c_adapter_id;
	स्थिर अक्षर *card_name;

	काष्ठा v4l2_async_subdev *asd[VPIF_CAPTURE_MAX_CHANNELS];
	पूर्णांक asd_sizes[VPIF_CAPTURE_MAX_CHANNELS];
पूर्ण;
#पूर्ण_अगर /* _VPIF_TYPES_H */
