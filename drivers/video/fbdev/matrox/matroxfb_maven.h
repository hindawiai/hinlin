<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MATROXFB_MAVEN_H__
#घोषणा __MATROXFB_MAVEN_H__

#समावेश <linux/ioctl.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश "matroxfb_base.h"

काष्ठा i2c_bit_adapter अणु
	काष्ठा i2c_adapter		adapter;
	पूर्णांक				initialized;
	काष्ठा i2c_algo_bit_data	bac;
	काष्ठा matrox_fb_info*		minfo;
	काष्ठा अणु
		अचिन्हित पूर्णांक		data;
		अचिन्हित पूर्णांक		घड़ी;
				      पूर्ण mask;
पूर्ण;

#पूर्ण_अगर /* __MATROXFB_MAVEN_H__ */
