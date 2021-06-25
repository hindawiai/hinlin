<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Device probe and रेजिस्टर.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 * Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 */
#अगर_अघोषित WFX_MAIN_H
#घोषणा WFX_MAIN_H

#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "hif_api_general.h"

काष्ठा wfx_dev;
काष्ठा hwbus_ops;

काष्ठा wfx_platक्रमm_data अणु
	/* Keyset and ".sec" extension will be appended to this string */
	स्थिर अक्षर *file_fw;
	स्थिर अक्षर *file_pds;
	काष्ठा gpio_desc *gpio_wakeup;
	/*
	 * अगर true HIF D_out is sampled on the rising edge of the घड़ी
	 * (पूर्णांकended to be used in 50Mhz SDIO)
	 */
	bool use_rising_clk;
पूर्ण;

काष्ठा wfx_dev *wfx_init_common(काष्ठा device *dev,
				स्थिर काष्ठा wfx_platक्रमm_data *pdata,
				स्थिर काष्ठा hwbus_ops *hwbus_ops,
				व्योम *hwbus_priv);

पूर्णांक wfx_probe(काष्ठा wfx_dev *wdev);
व्योम wfx_release(काष्ठा wfx_dev *wdev);

bool wfx_api_older_than(काष्ठा wfx_dev *wdev, पूर्णांक major, पूर्णांक minor);
पूर्णांक wfx_send_pds(काष्ठा wfx_dev *wdev, u8 *buf, माप_प्रकार len);

#पूर्ण_अगर
