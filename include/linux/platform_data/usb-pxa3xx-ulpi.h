<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * PXA3xx U2D header
 *
 * Copyright (C) 2010 CompuLab Ltd.
 *
 * Igor Grinberg <grinberg@compulab.co.il>
 */
#अगर_अघोषित __PXA310_U2D__
#घोषणा __PXA310_U2D__

#समावेश <linux/usb/ulpi.h>

काष्ठा pxa3xx_u2d_platक्रमm_data अणु

#घोषणा ULPI_SER_6PIN	(1 << 0)
#घोषणा ULPI_SER_3PIN	(1 << 1)
	अचिन्हित पूर्णांक ulpi_mode;

	पूर्णांक (*init)(काष्ठा device *);
	व्योम (*निकास)(काष्ठा device *);
पूर्ण;


/* Start PXA3xx U2D host */
पूर्णांक pxa3xx_u2d_start_hc(काष्ठा usb_bus *host);
/* Stop PXA3xx U2D host */
व्योम pxa3xx_u2d_stop_hc(काष्ठा usb_bus *host);

बाह्य व्योम pxa3xx_set_u2d_info(काष्ठा pxa3xx_u2d_platक्रमm_data *info);

#पूर्ण_अगर /* __PXA310_U2D__ */
