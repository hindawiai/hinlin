<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Samsung CF-ATA platक्रमm_device info
*/

#अगर_अघोषित __ATA_SAMSUNG_CF_H
#घोषणा __ATA_SAMSUNG_CF_H __खाता__

/**
 * काष्ठा s3c_ide_platdata - S3C IDE driver platक्रमm data.
 * @setup_gpio: Setup the बाह्यal GPIO pins to the right state क्रम data
 * transfer in true-ide mode.
 */
काष्ठा s3c_ide_platdata अणु
	व्योम (*setup_gpio)(व्योम);
पूर्ण;

/*
 * s3c_ide_set_platdata() - Setup the platक्रमm specअगरc data क्रम IDE driver.
 * @pdata: Platक्रमm data क्रम IDE driver.
 */
बाह्य व्योम s3c_ide_set_platdata(काष्ठा s3c_ide_platdata *pdata);

/* architecture-specअगरic IDE configuration */
बाह्य व्योम s3c64xx_ide_setup_gpio(व्योम);
बाह्य व्योम s5pv210_ide_setup_gpio(व्योम);

#पूर्ण_अगर /*__ATA_SAMSUNG_CF_H */
