<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * renesas-ceu.h - Renesas CEU driver पूर्णांकerface
 *
 * Copyright 2017-2018 Jacopo Mondi <jacopo+renesas@jmondi.org>
 */

#अगर_अघोषित __MEDIA_DRV_INTF_RENESAS_CEU_H__
#घोषणा __MEDIA_DRV_INTF_RENESAS_CEU_H__

#घोषणा CEU_MAX_SUBDEVS		2

काष्ठा ceu_async_subdev अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर bus_width;
	अचिन्हित अक्षर bus_shअगरt;
	अचिन्हित पूर्णांक i2c_adapter_id;
	अचिन्हित पूर्णांक i2c_address;
पूर्ण;

काष्ठा ceu_platक्रमm_data अणु
	अचिन्हित पूर्णांक num_subdevs;
	काष्ठा ceu_async_subdev subdevs[CEU_MAX_SUBDEVS];
पूर्ण;

#पूर्ण_अगर /* ___MEDIA_DRV_INTF_RENESAS_CEU_H__ */
