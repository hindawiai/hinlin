<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * timb_video.h Platक्रमm काष्ठा क्रम the Timberdale video driver
 * Copyright (c) 2009-2010 Intel Corporation
 */

#अगर_अघोषित _TIMB_VIDEO_
#घोषणा _TIMB_VIDEO_ 1

#समावेश <linux/i2c.h>

काष्ठा timb_video_platक्रमm_data अणु
	पूर्णांक dma_channel;
	पूर्णांक i2c_adapter; /* The I2C adapter where the encoder is attached */
	काष्ठा अणु
		स्थिर अक्षर *module_name;
		काष्ठा i2c_board_info *info;
	पूर्ण encoder;
पूर्ण;

#पूर्ण_अगर
