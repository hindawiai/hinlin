<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2005 Arnaud Patard <arnaud.patard@rtp-net.org>
*/

#अगर_अघोषित __TOUCHSCREEN_S3C2410_H
#घोषणा __TOUCHSCREEN_S3C2410_H

काष्ठा s3c2410_ts_mach_info अणु
	पूर्णांक delay;
	पूर्णांक presc;
	पूर्णांक oversampling_shअगरt;
	व्योम (*cfg_gpio)(काष्ठा platक्रमm_device *dev);
पूर्ण;

बाह्य व्योम s3c24xx_ts_set_platdata(काष्ठा s3c2410_ts_mach_info *);
बाह्य व्योम s3c64xx_ts_set_platdata(काष्ठा s3c2410_ts_mach_info *);

/* defined by architecture to configure gpio */
बाह्य व्योम s3c24xx_ts_cfg_gpio(काष्ठा platक्रमm_device *dev);

#पूर्ण_अगर /*__TOUCHSCREEN_S3C2410_H */
