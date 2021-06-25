<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
*/

#अगर_अघोषित __TEA5767_H__
#घोषणा __TEA5767_H__

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

क्रमागत tea5767_xtal अणु
	TEA5767_LOW_LO_32768    = 0,
	TEA5767_HIGH_LO_32768   = 1,
	TEA5767_LOW_LO_13MHz    = 2,
	TEA5767_HIGH_LO_13MHz   = 3,
पूर्ण;

काष्ठा tea5767_ctrl अणु
	अचिन्हित पूर्णांक		port1:1;
	अचिन्हित पूर्णांक		port2:1;
	अचिन्हित पूर्णांक		high_cut:1;
	अचिन्हित पूर्णांक		st_noise:1;
	अचिन्हित पूर्णांक		soft_mute:1;
	अचिन्हित पूर्णांक		japan_band:1;
	अचिन्हित पूर्णांक		deemph_75:1;
	अचिन्हित पूर्णांक		pllref:1;
	क्रमागत tea5767_xtal	xtal_freq;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_TEA5767)
बाह्य पूर्णांक tea5767_स्वतःdetection(काष्ठा i2c_adapter* i2c_adap, u8 i2c_addr);

बाह्य काष्ठा dvb_frontend *tea5767_attach(काष्ठा dvb_frontend *fe,
					   काष्ठा i2c_adapter* i2c_adap,
					   u8 i2c_addr);
#अन्यथा
अटल अंतरभूत पूर्णांक tea5767_स्वतःdetection(काष्ठा i2c_adapter* i2c_adap,
					u8 i2c_addr)
अणु
	prपूर्णांकk(KERN_INFO "%s: not probed - driver disabled by Kconfig\n",
	       __func__);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा dvb_frontend *tea5767_attach(काष्ठा dvb_frontend *fe,
						   काष्ठा i2c_adapter* i2c_adap,
						   u8 i2c_addr)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __TEA5767_H__ */
