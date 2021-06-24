<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2008-2009 Texas Instruments Inc
 *
 * ccdc device API
 */
#अगर_अघोषित _CCDC_HW_DEVICE_H
#घोषणा _CCDC_HW_DEVICE_H

#अगर_घोषित __KERNEL__
#समावेश <linux/videodev2.h>
#समावेश <linux/device.h>
#समावेश <media/davinci/vpfe_types.h>
#समावेश <media/davinci/ccdc_types.h>

/*
 * ccdc hw operations
 */
काष्ठा ccdc_hw_ops अणु
	/* Poपूर्णांकer to initialize function to initialize ccdc device */
	पूर्णांक (*खोलो) (काष्ठा device *dev);
	/* Poपूर्णांकer to deinitialize function */
	पूर्णांक (*बंद) (काष्ठा device *dev);
	/* set ccdc base address */
	व्योम (*set_ccdc_base)(व्योम *base, पूर्णांक size);
	/* Poपूर्णांकer to function to enable or disable ccdc */
	व्योम (*enable) (पूर्णांक en);
	/* reset sbl. only क्रम 6446 */
	व्योम (*reset) (व्योम);
	/* enable output to sdram */
	व्योम (*enable_out_to_sdram) (पूर्णांक en);
	/* Poपूर्णांकer to function to set hw parameters */
	पूर्णांक (*set_hw_अगर_params) (काष्ठा vpfe_hw_अगर_param *param);
	/* get पूर्णांकerface parameters */
	पूर्णांक (*get_hw_अगर_params) (काष्ठा vpfe_hw_अगर_param *param);
	/* Poपूर्णांकer to function to configure ccdc */
	पूर्णांक (*configure) (व्योम);

	/* Poपूर्णांकer to function to set buffer type */
	पूर्णांक (*set_buftype) (क्रमागत ccdc_buftype buf_type);
	/* Poपूर्णांकer to function to get buffer type */
	क्रमागत ccdc_buftype (*get_buftype) (व्योम);
	/* Poपूर्णांकer to function to set frame क्रमmat */
	पूर्णांक (*set_frame_क्रमmat) (क्रमागत ccdc_frmfmt frm_fmt);
	/* Poपूर्णांकer to function to get frame क्रमmat */
	क्रमागत ccdc_frmfmt (*get_frame_क्रमmat) (व्योम);
	/* क्रमागतerate hw pix क्रमmats */
	पूर्णांक (*क्रमागत_pix)(u32 *hw_pix, पूर्णांक i);
	/* Poपूर्णांकer to function to set buffer type */
	u32 (*get_pixel_क्रमmat) (व्योम);
	/* Poपूर्णांकer to function to get pixel क्रमmat. */
	पूर्णांक (*set_pixel_क्रमmat) (u32 pixfmt);
	/* Poपूर्णांकer to function to set image winकरोw */
	पूर्णांक (*set_image_winकरोw) (काष्ठा v4l2_rect *win);
	/* Poपूर्णांकer to function to set image winकरोw */
	व्योम (*get_image_winकरोw) (काष्ठा v4l2_rect *win);
	/* Poपूर्णांकer to function to get line length */
	अचिन्हित पूर्णांक (*get_line_length) (व्योम);

	/* Poपूर्णांकer to function to set frame buffer address */
	व्योम (*setfbaddr) (अचिन्हित दीर्घ addr);
	/* Poपूर्णांकer to function to get field id */
	पूर्णांक (*getfid) (व्योम);
पूर्ण;

काष्ठा ccdc_hw_device अणु
	/* ccdc device name */
	अक्षर name[32];
	/* module owner */
	काष्ठा module *owner;
	/* hw ops */
	काष्ठा ccdc_hw_ops hw_ops;
पूर्ण;

/* Used by CCDC module to रेजिस्टर & unरेजिस्टर with vpfe capture driver */
पूर्णांक vpfe_रेजिस्टर_ccdc_device(स्थिर काष्ठा ccdc_hw_device *dev);
व्योम vpfe_unरेजिस्टर_ccdc_device(स्थिर काष्ठा ccdc_hw_device *dev);

#पूर्ण_अगर
#पूर्ण_अगर
