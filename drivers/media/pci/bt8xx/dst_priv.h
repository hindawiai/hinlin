<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * dst-bt878.h: part of the DST driver क्रम the TwinHan DST Frontend
 *
 * Copyright (C) 2003 Jamie Honan
 */

काष्ठा dst_gpio_enable अणु
	u32	mask;
	u32	enable;
पूर्ण;

काष्ठा dst_gpio_output अणु
	u32	mask;
	u32	highvals;
पूर्ण;

काष्ठा dst_gpio_पढ़ो अणु
	अचिन्हित दीर्घ value;
पूर्ण;

जोड़ dst_gpio_packet अणु
	काष्ठा dst_gpio_enable enb;
	काष्ठा dst_gpio_output outp;
	काष्ठा dst_gpio_पढ़ो rd;
	पूर्णांक    psize;
पूर्ण;

#घोषणा DST_IG_ENABLE	0
#घोषणा DST_IG_WRITE	1
#घोषणा DST_IG_READ	2
#घोषणा DST_IG_TS       3

काष्ठा bt878;

पूर्णांक bt878_device_control(काष्ठा bt878 *bt, अचिन्हित पूर्णांक cmd, जोड़ dst_gpio_packet *mp);
