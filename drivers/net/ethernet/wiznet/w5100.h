<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Ethernet driver क्रम the WIZnet W5100 chip.
 *
 * Copyright (C) 2006-2008 WIZnet Co.,Ltd.
 * Copyright (C) 2012 Mike Sinkovsky <msink@permonline.ru>
 */

क्रमागत अणु
	W5100,
	W5200,
	W5500,
पूर्ण;

काष्ठा w5100_ops अणु
	bool may_sleep;
	पूर्णांक chip_id;
	पूर्णांक (*पढ़ो)(काष्ठा net_device *ndev, u32 addr);
	पूर्णांक (*ग_लिखो)(काष्ठा net_device *ndev, u32 addr, u8 data);
	पूर्णांक (*पढ़ो16)(काष्ठा net_device *ndev, u32 addr);
	पूर्णांक (*ग_लिखो16)(काष्ठा net_device *ndev, u32 addr, u16 data);
	पूर्णांक (*पढ़ोbulk)(काष्ठा net_device *ndev, u32 addr, u8 *buf, पूर्णांक len);
	पूर्णांक (*ग_लिखोbulk)(काष्ठा net_device *ndev, u32 addr, स्थिर u8 *buf,
			 पूर्णांक len);
	पूर्णांक (*reset)(काष्ठा net_device *ndev);
	पूर्णांक (*init)(काष्ठा net_device *ndev);
पूर्ण;

व्योम *w5100_ops_priv(स्थिर काष्ठा net_device *ndev);

पूर्णांक w5100_probe(काष्ठा device *dev, स्थिर काष्ठा w5100_ops *ops,
		पूर्णांक माप_ops_priv, स्थिर व्योम *mac_addr, पूर्णांक irq,
		पूर्णांक link_gpio);
पूर्णांक w5100_हटाओ(काष्ठा device *dev);

बाह्य स्थिर काष्ठा dev_pm_ops w5100_pm_ops;
