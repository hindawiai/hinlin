<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 Texas Instruments Inc
 */
#अगर_अघोषित _VPBE_VENC_H
#घोषणा _VPBE_VENC_H

#समावेश <media/v4l2-subdev.h>
#समावेश <media/davinci/vpbe_types.h>

#घोषणा DM644X_VPBE_VENC_SUBDEV_NAME	"dm644x,vpbe-venc"
#घोषणा DM365_VPBE_VENC_SUBDEV_NAME	"dm365,vpbe-venc"
#घोषणा DM355_VPBE_VENC_SUBDEV_NAME	"dm355,vpbe-venc"

/* venc events */
#घोषणा VENC_END_OF_FRAME	BIT(0)
#घोषणा VENC_FIRST_FIELD	BIT(1)
#घोषणा VENC_SECOND_FIELD	BIT(2)

काष्ठा venc_platक्रमm_data अणु
	पूर्णांक (*setup_pinmux)(u32 अगर_type, पूर्णांक field);
	पूर्णांक (*setup_घड़ी)(क्रमागत vpbe_enc_timings_type type,
			   अचिन्हित पूर्णांक pixघड़ी);
	पूर्णांक (*setup_अगर_config)(u32 pixcode);
	/* Number of LCD outमाला_दो supported */
	पूर्णांक num_lcd_outमाला_दो;
	काष्ठा vpbe_अगर_params *lcd_अगर_params;
पूर्ण;

क्रमागत venc_ioctls अणु
	VENC_GET_FLD = 1,
पूर्ण;

/* exported functions */
काष्ठा v4l2_subdev *venc_sub_dev_init(काष्ठा v4l2_device *v4l2_dev,
		स्थिर अक्षर *venc_name);
#पूर्ण_अगर
