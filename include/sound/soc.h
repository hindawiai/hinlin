<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * linux/sound/soc.h -- ALSA SoC Layer
 *
 * Author:	Liam Girdwood
 * Created:	Aug 11th 2005
 * Copyright:	Wolfson Microelectronics. PLC.
 */

#अगर_अघोषित __LINUX_SND_SOC_H
#घोषणा __LINUX_SND_SOC_H

#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/regmap.h>
#समावेश <linux/log2.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/compress_driver.h>
#समावेश <sound/control.h>
#समावेश <sound/ac97_codec.h>

/*
 * Convenience kcontrol builders
 */
#घोषणा SOC_DOUBLE_VALUE(xreg, shअगरt_left, shअगरt_right, xmax, xinvert, xस्वतःdisable) \
	((अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control) \
	अणु.reg = xreg, .rreg = xreg, .shअगरt = shअगरt_left, \
	.rshअगरt = shअगरt_right, .max = xmax, .platक्रमm_max = xmax, \
	.invert = xinvert, .स्वतःdisable = xस्वतःdisableपूर्ण)
#घोषणा SOC_DOUBLE_S_VALUE(xreg, shअगरt_left, shअगरt_right, xmin, xmax, xsign_bit, xinvert, xस्वतःdisable) \
	((अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control) \
	अणु.reg = xreg, .rreg = xreg, .shअगरt = shअगरt_left, \
	.rshअगरt = shअगरt_right, .min = xmin, .max = xmax, .platक्रमm_max = xmax, \
	.sign_bit = xsign_bit, .invert = xinvert, .स्वतःdisable = xस्वतःdisableपूर्ण)
#घोषणा SOC_SINGLE_VALUE(xreg, xshअगरt, xmax, xinvert, xस्वतःdisable) \
	SOC_DOUBLE_VALUE(xreg, xshअगरt, xshअगरt, xmax, xinvert, xस्वतःdisable)
#घोषणा SOC_SINGLE_VALUE_EXT(xreg, xmax, xinvert) \
	((अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control) \
	अणु.reg = xreg, .max = xmax, .platक्रमm_max = xmax, .invert = xinvertपूर्ण)
#घोषणा SOC_DOUBLE_R_VALUE(xlreg, xrreg, xshअगरt, xmax, xinvert) \
	((अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control) \
	अणु.reg = xlreg, .rreg = xrreg, .shअगरt = xshअगरt, .rshअगरt = xshअगरt, \
	.max = xmax, .platक्रमm_max = xmax, .invert = xinvertपूर्ण)
#घोषणा SOC_DOUBLE_R_S_VALUE(xlreg, xrreg, xshअगरt, xmin, xmax, xsign_bit, xinvert) \
	((अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control) \
	अणु.reg = xlreg, .rreg = xrreg, .shअगरt = xshअगरt, .rshअगरt = xshअगरt, \
	.max = xmax, .min = xmin, .platक्रमm_max = xmax, .sign_bit = xsign_bit, \
	.invert = xinvertपूर्ण)
#घोषणा SOC_DOUBLE_R_RANGE_VALUE(xlreg, xrreg, xshअगरt, xmin, xmax, xinvert) \
	((अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control) \
	अणु.reg = xlreg, .rreg = xrreg, .shअगरt = xshअगरt, .rshअगरt = xshअगरt, \
	.min = xmin, .max = xmax, .platक्रमm_max = xmax, .invert = xinvertपूर्ण)
#घोषणा SOC_SINGLE(xname, reg, shअगरt, max, invert) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
	.put = snd_soc_put_volsw, \
	.निजी_value = SOC_SINGLE_VALUE(reg, shअगरt, max, invert, 0) पूर्ण
#घोषणा SOC_SINGLE_RANGE(xname, xreg, xshअगरt, xmin, xmax, xinvert) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),\
	.info = snd_soc_info_volsw_range, .get = snd_soc_get_volsw_range, \
	.put = snd_soc_put_volsw_range, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control) \
		अणु.reg = xreg, .rreg = xreg, .shअगरt = xshअगरt, \
		 .rshअगरt = xshअगरt,  .min = xmin, .max = xmax, \
		 .platक्रमm_max = xmax, .invert = xinvertपूर्ण पूर्ण
#घोषणा SOC_SINGLE_TLV(xname, reg, shअगरt, max, invert, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
		 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
	.put = snd_soc_put_volsw, \
	.निजी_value = SOC_SINGLE_VALUE(reg, shअगरt, max, invert, 0) पूर्ण
#घोषणा SOC_SINGLE_SX_TLV(xname, xreg, xshअगरt, xmin, xmax, tlv_array) \
अणु       .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
	SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.tlv.p  = (tlv_array),\
	.info = snd_soc_info_volsw_sx, \
	.get = snd_soc_get_volsw_sx,\
	.put = snd_soc_put_volsw_sx, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control) \
		अणु.reg = xreg, .rreg = xreg, \
		.shअगरt = xshअगरt, .rshअगरt = xshअगरt, \
		.max = xmax, .min = xminपूर्ण पूर्ण
#घोषणा SOC_SINGLE_RANGE_TLV(xname, xreg, xshअगरt, xmin, xmax, xinvert, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),\
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
		 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw_range, \
	.get = snd_soc_get_volsw_range, .put = snd_soc_put_volsw_range, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control) \
		अणु.reg = xreg, .rreg = xreg, .shअगरt = xshअगरt, \
		 .rshअगरt = xshअगरt, .min = xmin, .max = xmax, \
		 .platक्रमm_max = xmax, .invert = xinvertपूर्ण पूर्ण
#घोषणा SOC_DOUBLE(xname, reg, shअगरt_left, shअगरt_right, max, invert) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),\
	.info = snd_soc_info_volsw, .get = snd_soc_get_volsw, \
	.put = snd_soc_put_volsw, \
	.निजी_value = SOC_DOUBLE_VALUE(reg, shअगरt_left, shअगरt_right, \
					  max, invert, 0) पूर्ण
#घोषणा SOC_DOUBLE_STS(xname, reg, shअगरt_left, shअगरt_right, max, invert) \
अणु									\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),		\
	.info = snd_soc_info_volsw, .get = snd_soc_get_volsw,		\
	.access = SNDRV_CTL_ELEM_ACCESS_READ |				\
		SNDRV_CTL_ELEM_ACCESS_VOLATILE,				\
	.निजी_value = SOC_DOUBLE_VALUE(reg, shअगरt_left, shअगरt_right,	\
					  max, invert, 0) पूर्ण
#घोषणा SOC_DOUBLE_R(xname, reg_left, reg_right, xshअगरt, xmax, xinvert) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.info = snd_soc_info_volsw, \
	.get = snd_soc_get_volsw, .put = snd_soc_put_volsw, \
	.निजी_value = SOC_DOUBLE_R_VALUE(reg_left, reg_right, xshअगरt, \
					    xmax, xinvert) पूर्ण
#घोषणा SOC_DOUBLE_R_RANGE(xname, reg_left, reg_right, xshअगरt, xmin, \
			   xmax, xinvert)		\
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),\
	.info = snd_soc_info_volsw_range, \
	.get = snd_soc_get_volsw_range, .put = snd_soc_put_volsw_range, \
	.निजी_value = SOC_DOUBLE_R_RANGE_VALUE(reg_left, reg_right, \
					    xshअगरt, xmin, xmax, xinvert) पूर्ण
#घोषणा SOC_DOUBLE_TLV(xname, reg, shअगरt_left, shअगरt_right, max, invert, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),\
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
		 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw, .get = snd_soc_get_volsw, \
	.put = snd_soc_put_volsw, \
	.निजी_value = SOC_DOUBLE_VALUE(reg, shअगरt_left, shअगरt_right, \
					  max, invert, 0) पूर्ण
#घोषणा SOC_DOUBLE_R_TLV(xname, reg_left, reg_right, xshअगरt, xmax, xinvert, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),\
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
		 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw, \
	.get = snd_soc_get_volsw, .put = snd_soc_put_volsw, \
	.निजी_value = SOC_DOUBLE_R_VALUE(reg_left, reg_right, xshअगरt, \
					    xmax, xinvert) पूर्ण
#घोषणा SOC_DOUBLE_R_RANGE_TLV(xname, reg_left, reg_right, xshअगरt, xmin, \
			       xmax, xinvert, tlv_array)		\
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),\
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
		 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw_range, \
	.get = snd_soc_get_volsw_range, .put = snd_soc_put_volsw_range, \
	.निजी_value = SOC_DOUBLE_R_RANGE_VALUE(reg_left, reg_right, \
					    xshअगरt, xmin, xmax, xinvert) पूर्ण
#घोषणा SOC_DOUBLE_R_SX_TLV(xname, xreg, xrreg, xshअगरt, xmin, xmax, tlv_array) \
अणु       .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
	SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.tlv.p  = (tlv_array), \
	.info = snd_soc_info_volsw_sx, \
	.get = snd_soc_get_volsw_sx, \
	.put = snd_soc_put_volsw_sx, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control) \
		अणु.reg = xreg, .rreg = xrreg, \
		.shअगरt = xshअगरt, .rshअगरt = xshअगरt, \
		.max = xmax, .min = xminपूर्ण पूर्ण
#घोषणा SOC_DOUBLE_R_S_TLV(xname, reg_left, reg_right, xshअगरt, xmin, xmax, xsign_bit, xinvert, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),\
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
		 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw, \
	.get = snd_soc_get_volsw, .put = snd_soc_put_volsw, \
	.निजी_value = SOC_DOUBLE_R_S_VALUE(reg_left, reg_right, xshअगरt, \
					    xmin, xmax, xsign_bit, xinvert) पूर्ण
#घोषणा SOC_SINGLE_S8_TLV(xname, xreg, xmin, xmax, tlv_array) \
अणु	.अगरace  = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
		  SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.tlv.p  = (tlv_array), \
	.info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
	.put = snd_soc_put_volsw, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control) \
	अणु.reg = xreg, .rreg = xreg,  \
	 .min = xmin, .max = xmax, .platक्रमm_max = xmax, \
	.sign_bit = 7,पूर्ण पूर्ण
#घोषणा SOC_DOUBLE_S8_TLV(xname, xreg, xmin, xmax, tlv_array) \
अणु	.अगरace  = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
		  SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.tlv.p  = (tlv_array), \
	.info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
	.put = snd_soc_put_volsw, \
	.निजी_value = SOC_DOUBLE_S_VALUE(xreg, 0, 8, xmin, xmax, 7, 0, 0) पूर्ण
#घोषणा SOC_ENUM_DOUBLE(xreg, xshअगरt_l, xshअगरt_r, xitems, xtexts) \
अणु	.reg = xreg, .shअगरt_l = xshअगरt_l, .shअगरt_r = xshअगरt_r, \
	.items = xitems, .texts = xtexts, \
	.mask = xitems ? roundup_घात_of_two(xitems) - 1 : 0पूर्ण
#घोषणा SOC_ENUM_SINGLE(xreg, xshअगरt, xitems, xtexts) \
	SOC_ENUM_DOUBLE(xreg, xshअगरt, xshअगरt, xitems, xtexts)
#घोषणा SOC_ENUM_SINGLE_EXT(xitems, xtexts) \
अणु	.items = xitems, .texts = xtexts पूर्ण
#घोषणा SOC_VALUE_ENUM_DOUBLE(xreg, xshअगरt_l, xshअगरt_r, xmask, xitems, xtexts, xvalues) \
अणु	.reg = xreg, .shअगरt_l = xshअगरt_l, .shअगरt_r = xshअगरt_r, \
	.mask = xmask, .items = xitems, .texts = xtexts, .values = xvaluesपूर्ण
#घोषणा SOC_VALUE_ENUM_SINGLE(xreg, xshअगरt, xmask, xitems, xtexts, xvalues) \
	SOC_VALUE_ENUM_DOUBLE(xreg, xshअगरt, xshअगरt, xmask, xitems, xtexts, xvalues)
#घोषणा SOC_VALUE_ENUM_SINGLE_AUTODISABLE(xreg, xshअगरt, xmask, xitems, xtexts, xvalues) \
अणु	.reg = xreg, .shअगरt_l = xshअगरt, .shअगरt_r = xshअगरt, \
	.mask = xmask, .items = xitems, .texts = xtexts, \
	.values = xvalues, .स्वतःdisable = 1पूर्ण
#घोषणा SOC_ENUM_SINGLE_VIRT(xitems, xtexts) \
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 0, xitems, xtexts)
#घोषणा SOC_ENUM(xname, xक्रमागत) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,\
	.info = snd_soc_info_क्रमागत_द्विगुन, \
	.get = snd_soc_get_क्रमागत_द्विगुन, .put = snd_soc_put_क्रमागत_द्विगुन, \
	.निजी_value = (अचिन्हित दीर्घ)&xक्रमागत पूर्ण
#घोषणा SOC_SINGLE_EXT(xname, xreg, xshअगरt, xmax, xinvert,\
	 xhandler_get, xhandler_put) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_volsw, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = SOC_SINGLE_VALUE(xreg, xshअगरt, xmax, xinvert, 0) पूर्ण
#घोषणा SOC_DOUBLE_EXT(xname, reg, shअगरt_left, shअगरt_right, max, invert,\
	 xhandler_get, xhandler_put) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),\
	.info = snd_soc_info_volsw, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = \
		SOC_DOUBLE_VALUE(reg, shअगरt_left, shअगरt_right, max, invert, 0) पूर्ण
#घोषणा SOC_DOUBLE_R_EXT(xname, reg_left, reg_right, xshअगरt, xmax, xinvert,\
	 xhandler_get, xhandler_put) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.info = snd_soc_info_volsw, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = SOC_DOUBLE_R_VALUE(reg_left, reg_right, xshअगरt, \
					    xmax, xinvert) पूर्ण
#घोषणा SOC_SINGLE_EXT_TLV(xname, xreg, xshअगरt, xmax, xinvert,\
	 xhandler_get, xhandler_put, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
		 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = SOC_SINGLE_VALUE(xreg, xshअगरt, xmax, xinvert, 0) पूर्ण
#घोषणा SOC_SINGLE_RANGE_EXT_TLV(xname, xreg, xshअगरt, xmin, xmax, xinvert, \
				 xhandler_get, xhandler_put, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),\
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
		 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw_range, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_mixer_control) \
		अणु.reg = xreg, .rreg = xreg, .shअगरt = xshअगरt, \
		 .rshअगरt = xshअगरt, .min = xmin, .max = xmax, \
		 .platक्रमm_max = xmax, .invert = xinvertपूर्ण पूर्ण
#घोषणा SOC_DOUBLE_EXT_TLV(xname, xreg, shअगरt_left, shअगरt_right, xmax, xinvert,\
	 xhandler_get, xhandler_put, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
		 SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = SOC_DOUBLE_VALUE(xreg, shअगरt_left, shअगरt_right, \
					  xmax, xinvert, 0) पूर्ण
#घोषणा SOC_DOUBLE_R_EXT_TLV(xname, reg_left, reg_right, xshअगरt, xmax, xinvert,\
	 xhandler_get, xhandler_put, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
		 SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = SOC_DOUBLE_R_VALUE(reg_left, reg_right, xshअगरt, \
					    xmax, xinvert) पूर्ण
#घोषणा SOC_SINGLE_BOOL_EXT(xname, xdata, xhandler_get, xhandler_put) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_bool_ext, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = xdata पूर्ण
#घोषणा SOC_ENUM_EXT(xname, xक्रमागत, xhandler_get, xhandler_put) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_क्रमागत_द्विगुन, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = (अचिन्हित दीर्घ)&xक्रमागत पूर्ण
#घोषणा SOC_VALUE_ENUM_EXT(xname, xक्रमागत, xhandler_get, xhandler_put) \
	SOC_ENUM_EXT(xname, xक्रमागत, xhandler_get, xhandler_put)

#घोषणा SND_SOC_BYTES(xname, xbase, xregs)		      \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,   \
	.info = snd_soc_bytes_info, .get = snd_soc_bytes_get, \
	.put = snd_soc_bytes_put, .निजी_value =	      \
		((अचिन्हित दीर्घ)&(काष्ठा soc_bytes)           \
		अणु.base = xbase, .num_regs = xregs पूर्ण) पूर्ण
#घोषणा SND_SOC_BYTES_E(xname, xbase, xregs, xhandler_get, xhandler_put) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_bytes_info, .get = xhandler_get, \
	.put = xhandler_put, .निजी_value = \
		((अचिन्हित दीर्घ)&(काष्ठा soc_bytes) \
		अणु.base = xbase, .num_regs = xregs पूर्ण) पूर्ण

#घोषणा SND_SOC_BYTES_MASK(xname, xbase, xregs, xmask)	      \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname,   \
	.info = snd_soc_bytes_info, .get = snd_soc_bytes_get, \
	.put = snd_soc_bytes_put, .निजी_value =	      \
		((अचिन्हित दीर्घ)&(काष्ठा soc_bytes)           \
		अणु.base = xbase, .num_regs = xregs,	      \
		 .mask = xmask पूर्ण) पूर्ण

/*
 * SND_SOC_BYTES_EXT is deprecated, please USE SND_SOC_BYTES_TLV instead
 */
#घोषणा SND_SOC_BYTES_EXT(xname, xcount, xhandler_get, xhandler_put) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_bytes_info_ext, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_bytes_ext) \
		अणु.max = xcountपूर्ण पूर्ण
#घोषणा SND_SOC_BYTES_TLV(xname, xcount, xhandler_get, xhandler_put) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READWRITE | \
		  SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK, \
	.tlv.c = (snd_soc_bytes_tlv_callback), \
	.info = snd_soc_bytes_info_ext, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_bytes_ext) \
		अणु.max = xcount, .get = xhandler_get, .put = xhandler_put, पूर्ण पूर्ण
#घोषणा SOC_SINGLE_XR_SX(xname, xregbase, xregcount, xnbits, \
		xmin, xmax, xinvert) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.info = snd_soc_info_xr_sx, .get = snd_soc_get_xr_sx, \
	.put = snd_soc_put_xr_sx, \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_mreg_control) \
		अणु.regbase = xregbase, .regcount = xregcount, .nbits = xnbits, \
		.invert = xinvert, .min = xmin, .max = xmaxपूर्ण पूर्ण

#घोषणा SOC_SINGLE_STROBE(xname, xreg, xshअगरt, xinvert) \
	SOC_SINGLE_EXT(xname, xreg, xshअगरt, 1, xinvert, \
		snd_soc_get_strobe, snd_soc_put_strobe)

/*
 * Simplअगरied versions of above macros, declaring a काष्ठा and calculating
 * ARRAY_SIZE पूर्णांकernally
 */
#घोषणा SOC_ENUM_DOUBLE_DECL(name, xreg, xshअगरt_l, xshअगरt_r, xtexts) \
	स्थिर काष्ठा soc_क्रमागत name = SOC_ENUM_DOUBLE(xreg, xshअगरt_l, xshअगरt_r, \
						ARRAY_SIZE(xtexts), xtexts)
#घोषणा SOC_ENUM_SINGLE_DECL(name, xreg, xshअगरt, xtexts) \
	SOC_ENUM_DOUBLE_DECL(name, xreg, xshअगरt, xshअगरt, xtexts)
#घोषणा SOC_ENUM_SINGLE_EXT_DECL(name, xtexts) \
	स्थिर काष्ठा soc_क्रमागत name = SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(xtexts), xtexts)
#घोषणा SOC_VALUE_ENUM_DOUBLE_DECL(name, xreg, xshअगरt_l, xshअगरt_r, xmask, xtexts, xvalues) \
	स्थिर काष्ठा soc_क्रमागत name = SOC_VALUE_ENUM_DOUBLE(xreg, xshअगरt_l, xshअगरt_r, xmask, \
							ARRAY_SIZE(xtexts), xtexts, xvalues)
#घोषणा SOC_VALUE_ENUM_SINGLE_DECL(name, xreg, xshअगरt, xmask, xtexts, xvalues) \
	SOC_VALUE_ENUM_DOUBLE_DECL(name, xreg, xshअगरt, xshअगरt, xmask, xtexts, xvalues)

#घोषणा SOC_VALUE_ENUM_SINGLE_AUTODISABLE_DECL(name, xreg, xshअगरt, xmask, xtexts, xvalues) \
	स्थिर काष्ठा soc_क्रमागत name = SOC_VALUE_ENUM_SINGLE_AUTODISABLE(xreg, \
		xshअगरt, xmask, ARRAY_SIZE(xtexts), xtexts, xvalues)

#घोषणा SOC_ENUM_SINGLE_VIRT_DECL(name, xtexts) \
	स्थिर काष्ठा soc_क्रमागत name = SOC_ENUM_SINGLE_VIRT(ARRAY_SIZE(xtexts), xtexts)

काष्ठा device_node;
काष्ठा snd_jack;
काष्ठा snd_soc_card;
काष्ठा snd_soc_pcm_stream;
काष्ठा snd_soc_ops;
काष्ठा snd_soc_pcm_runसमय;
काष्ठा snd_soc_dai;
काष्ठा snd_soc_dai_driver;
काष्ठा snd_soc_dai_link;
काष्ठा snd_soc_component;
काष्ठा snd_soc_component_driver;
काष्ठा soc_क्रमागत;
काष्ठा snd_soc_jack;
काष्ठा snd_soc_jack_zone;
काष्ठा snd_soc_jack_pin;
#समावेश <sound/soc-dapm.h>
#समावेश <sound/soc-dpcm.h>
#समावेश <sound/soc-topology.h>

काष्ठा snd_soc_jack_gpio;

प्रकार पूर्णांक (*hw_ग_लिखो_t)(व्योम *,स्थिर अक्षर* ,पूर्णांक);

क्रमागत snd_soc_pcm_subclass अणु
	SND_SOC_PCM_CLASS_PCM	= 0,
	SND_SOC_PCM_CLASS_BE	= 1,
पूर्ण;

पूर्णांक snd_soc_रेजिस्टर_card(काष्ठा snd_soc_card *card);
पूर्णांक snd_soc_unरेजिस्टर_card(काष्ठा snd_soc_card *card);
पूर्णांक devm_snd_soc_रेजिस्टर_card(काष्ठा device *dev, काष्ठा snd_soc_card *card);
#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक snd_soc_suspend(काष्ठा device *dev);
पूर्णांक snd_soc_resume(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_soc_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_soc_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
पूर्णांक snd_soc_घातeroff(काष्ठा device *dev);
पूर्णांक snd_soc_component_initialize(काष्ठा snd_soc_component *component,
				 स्थिर काष्ठा snd_soc_component_driver *driver,
				 काष्ठा device *dev);
पूर्णांक snd_soc_add_component(काष्ठा snd_soc_component *component,
			  काष्ठा snd_soc_dai_driver *dai_drv,
			  पूर्णांक num_dai);
पूर्णांक snd_soc_रेजिस्टर_component(काष्ठा device *dev,
			 स्थिर काष्ठा snd_soc_component_driver *component_driver,
			 काष्ठा snd_soc_dai_driver *dai_drv, पूर्णांक num_dai);
पूर्णांक devm_snd_soc_रेजिस्टर_component(काष्ठा device *dev,
			 स्थिर काष्ठा snd_soc_component_driver *component_driver,
			 काष्ठा snd_soc_dai_driver *dai_drv, पूर्णांक num_dai);
व्योम snd_soc_unरेजिस्टर_component(काष्ठा device *dev);
व्योम snd_soc_unरेजिस्टर_component_by_driver(काष्ठा device *dev,
			 स्थिर काष्ठा snd_soc_component_driver *component_driver);
काष्ठा snd_soc_component *snd_soc_lookup_component_nolocked(काष्ठा device *dev,
							    स्थिर अक्षर *driver_name);
काष्ठा snd_soc_component *snd_soc_lookup_component(काष्ठा device *dev,
						   स्थिर अक्षर *driver_name);

पूर्णांक soc_new_pcm(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक num);
#अगर_घोषित CONFIG_SND_SOC_COMPRESS
पूर्णांक snd_soc_new_compress(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक num);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_soc_new_compress(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक num)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम snd_soc_disconnect_sync(काष्ठा device *dev);

काष्ठा snd_soc_pcm_runसमय *snd_soc_get_pcm_runसमय(काष्ठा snd_soc_card *card,
				काष्ठा snd_soc_dai_link *dai_link);

bool snd_soc_runसमय_ignore_pmकरोwn_समय(काष्ठा snd_soc_pcm_runसमय *rtd);

व्योम snd_soc_runसमय_action(काष्ठा snd_soc_pcm_runसमय *rtd,
			    पूर्णांक stream, पूर्णांक action);
अटल अंतरभूत व्योम snd_soc_runसमय_activate(काष्ठा snd_soc_pcm_runसमय *rtd,
				     पूर्णांक stream)
अणु
	snd_soc_runसमय_action(rtd, stream, 1);
पूर्ण
अटल अंतरभूत व्योम snd_soc_runसमय_deactivate(काष्ठा snd_soc_pcm_runसमय *rtd,
				       पूर्णांक stream)
अणु
	snd_soc_runसमय_action(rtd, stream, -1);
पूर्ण

पूर्णांक snd_soc_runसमय_calc_hw(काष्ठा snd_soc_pcm_runसमय *rtd,
			    काष्ठा snd_pcm_hardware *hw, पूर्णांक stream);

पूर्णांक snd_soc_runसमय_set_dai_fmt(काष्ठा snd_soc_pcm_runसमय *rtd,
	अचिन्हित पूर्णांक dai_fmt);

#अगर_घोषित CONFIG_DMI
पूर्णांक snd_soc_set_dmi_name(काष्ठा snd_soc_card *card, स्थिर अक्षर *flavour);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_soc_set_dmi_name(काष्ठा snd_soc_card *card,
				       स्थिर अक्षर *flavour)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Utility functions to get घड़ी rates from various things */
पूर्णांक snd_soc_calc_frame_size(पूर्णांक sample_size, पूर्णांक channels, पूर्णांक tdm_slots);
पूर्णांक snd_soc_params_to_frame_size(काष्ठा snd_pcm_hw_params *params);
पूर्णांक snd_soc_calc_bclk(पूर्णांक fs, पूर्णांक sample_size, पूर्णांक channels, पूर्णांक tdm_slots);
पूर्णांक snd_soc_params_to_bclk(काष्ठा snd_pcm_hw_params *parms);

/* set runसमय hw params */
पूर्णांक snd_soc_set_runसमय_hwparams(काष्ठा snd_pcm_substream *substream,
	स्थिर काष्ठा snd_pcm_hardware *hw);

काष्ठा snd_ac97 *snd_soc_alloc_ac97_component(काष्ठा snd_soc_component *component);
काष्ठा snd_ac97 *snd_soc_new_ac97_component(काष्ठा snd_soc_component *component,
	अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक id_mask);
व्योम snd_soc_मुक्त_ac97_component(काष्ठा snd_ac97 *ac97);

#अगर_घोषित CONFIG_SND_SOC_AC97_BUS
पूर्णांक snd_soc_set_ac97_ops(काष्ठा snd_ac97_bus_ops *ops);
पूर्णांक snd_soc_set_ac97_ops_of_reset(काष्ठा snd_ac97_bus_ops *ops,
		काष्ठा platक्रमm_device *pdev);

बाह्य काष्ठा snd_ac97_bus_ops *soc_ac97_ops;
#अन्यथा
अटल अंतरभूत पूर्णांक snd_soc_set_ac97_ops_of_reset(काष्ठा snd_ac97_bus_ops *ops,
	काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_soc_set_ac97_ops(काष्ठा snd_ac97_bus_ops *ops)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 *Controls
 */
काष्ठा snd_kcontrol *snd_soc_cnew(स्थिर काष्ठा snd_kcontrol_new *_ढाँचा,
				  व्योम *data, स्थिर अक्षर *दीर्घ_name,
				  स्थिर अक्षर *prefix);
पूर्णांक snd_soc_add_component_controls(काष्ठा snd_soc_component *component,
	स्थिर काष्ठा snd_kcontrol_new *controls, अचिन्हित पूर्णांक num_controls);
पूर्णांक snd_soc_add_card_controls(काष्ठा snd_soc_card *soc_card,
	स्थिर काष्ठा snd_kcontrol_new *controls, पूर्णांक num_controls);
पूर्णांक snd_soc_add_dai_controls(काष्ठा snd_soc_dai *dai,
	स्थिर काष्ठा snd_kcontrol_new *controls, पूर्णांक num_controls);
पूर्णांक snd_soc_info_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_soc_get_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_put_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_info_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_soc_info_volsw_sx(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_info *uinfo);
#घोषणा snd_soc_info_bool_ext		snd_ctl_boolean_mono_info
पूर्णांक snd_soc_get_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_put_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
#घोषणा snd_soc_get_volsw_2r snd_soc_get_volsw
#घोषणा snd_soc_put_volsw_2r snd_soc_put_volsw
पूर्णांक snd_soc_get_volsw_sx(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_put_volsw_sx(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_info_volsw_range(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_soc_put_volsw_range(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_get_volsw_range(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_limit_volume(काष्ठा snd_soc_card *card,
	स्थिर अक्षर *name, पूर्णांक max);
पूर्णांक snd_soc_bytes_info(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_soc_bytes_get(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_bytes_put(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_bytes_info_ext(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *ucontrol);
पूर्णांक snd_soc_bytes_tlv_callback(काष्ठा snd_kcontrol *kcontrol, पूर्णांक op_flag,
	अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक __user *tlv);
पूर्णांक snd_soc_info_xr_sx(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_soc_get_xr_sx(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_put_xr_sx(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_get_strobe(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_soc_put_strobe(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol);

/* SoC PCM stream inक्रमmation */
काष्ठा snd_soc_pcm_stream अणु
	स्थिर अक्षर *stream_name;
	u64 क्रमmats;			/* SNDRV_PCM_FMTBIT_* */
	अचिन्हित पूर्णांक rates;		/* SNDRV_PCM_RATE_* */
	अचिन्हित पूर्णांक rate_min;		/* min rate */
	अचिन्हित पूर्णांक rate_max;		/* max rate */
	अचिन्हित पूर्णांक channels_min;	/* min channels */
	अचिन्हित पूर्णांक channels_max;	/* max channels */
	अचिन्हित पूर्णांक sig_bits;		/* number of bits of content */
पूर्ण;

/* SoC audio ops */
काष्ठा snd_soc_ops अणु
	पूर्णांक (*startup)(काष्ठा snd_pcm_substream *);
	व्योम (*shutकरोwn)(काष्ठा snd_pcm_substream *);
	पूर्णांक (*hw_params)(काष्ठा snd_pcm_substream *, काष्ठा snd_pcm_hw_params *);
	पूर्णांक (*hw_मुक्त)(काष्ठा snd_pcm_substream *);
	पूर्णांक (*prepare)(काष्ठा snd_pcm_substream *);
	पूर्णांक (*trigger)(काष्ठा snd_pcm_substream *, पूर्णांक);
पूर्ण;

काष्ठा snd_soc_compr_ops अणु
	पूर्णांक (*startup)(काष्ठा snd_compr_stream *);
	व्योम (*shutकरोwn)(काष्ठा snd_compr_stream *);
	पूर्णांक (*set_params)(काष्ठा snd_compr_stream *);
	पूर्णांक (*trigger)(काष्ठा snd_compr_stream *);
पूर्ण;

काष्ठा snd_soc_component*
snd_soc_rtdcom_lookup(काष्ठा snd_soc_pcm_runसमय *rtd,
		       स्थिर अक्षर *driver_name);

काष्ठा snd_soc_dai_link_component अणु
	स्थिर अक्षर *name;
	काष्ठा device_node *of_node;
	स्थिर अक्षर *dai_name;
पूर्ण;

काष्ठा snd_soc_dai_link अणु
	/* config - must be set by machine driver */
	स्थिर अक्षर *name;			/* Codec name */
	स्थिर अक्षर *stream_name;		/* Stream name */

	/*
	 * You MAY specअगरy the link's CPU-side device, either by device name,
	 * or by DT/OF node, but not both. If this inक्रमmation is omitted,
	 * the CPU-side DAI is matched using .cpu_dai_name only, which hence
	 * must be globally unique. These fields are currently typically used
	 * only क्रम codec to codec links, or प्रणालीs using device tree.
	 */
	/*
	 * You MAY specअगरy the DAI name of the CPU DAI. If this inक्रमmation is
	 * omitted, the CPU-side DAI is matched using .cpu_name/.cpu_of_node
	 * only, which only works well when that device exposes a single DAI.
	 */
	काष्ठा snd_soc_dai_link_component *cpus;
	अचिन्हित पूर्णांक num_cpus;

	/*
	 * You MUST specअगरy the link's codec, either by device name, or by
	 * DT/OF node, but not both.
	 */
	/* You MUST specअगरy the DAI name within the codec */
	काष्ठा snd_soc_dai_link_component *codecs;
	अचिन्हित पूर्णांक num_codecs;

	/*
	 * You MAY specअगरy the link's platक्रमm/PCM/DMA driver, either by
	 * device name, or by DT/OF node, but not both. Some क्रमms of link
	 * करो not need a platक्रमm. In such हाल, platक्रमms are not mandatory.
	 */
	काष्ठा snd_soc_dai_link_component *platक्रमms;
	अचिन्हित पूर्णांक num_platक्रमms;

	पूर्णांक id;	/* optional ID क्रम machine driver link identअगरication */

	स्थिर काष्ठा snd_soc_pcm_stream *params;
	अचिन्हित पूर्णांक num_params;

	अचिन्हित पूर्णांक dai_fmt;           /* क्रमmat to set on init */

	क्रमागत snd_soc_dpcm_trigger trigger[2]; /* trigger type क्रम DPCM */

	/* codec/machine specअगरic init - e.g. add machine controls */
	पूर्णांक (*init)(काष्ठा snd_soc_pcm_runसमय *rtd);

	/* codec/machine specअगरic निकास - dual of init() */
	व्योम (*निकास)(काष्ठा snd_soc_pcm_runसमय *rtd);

	/* optional hw_params re-writing क्रम BE and FE sync */
	पूर्णांक (*be_hw_params_fixup)(काष्ठा snd_soc_pcm_runसमय *rtd,
			काष्ठा snd_pcm_hw_params *params);

	/* machine stream operations */
	स्थिर काष्ठा snd_soc_ops *ops;
	स्थिर काष्ठा snd_soc_compr_ops *compr_ops;

	/* Mark this pcm with non atomic ops */
	अचिन्हित पूर्णांक nonatomic:1;

	/* For unidirectional dai links */
	अचिन्हित पूर्णांक playback_only:1;
	अचिन्हित पूर्णांक capture_only:1;

	/* Keep DAI active over suspend */
	अचिन्हित पूर्णांक ignore_suspend:1;

	/* Symmetry requirements */
	अचिन्हित पूर्णांक symmetric_rate:1;
	अचिन्हित पूर्णांक symmetric_channels:1;
	अचिन्हित पूर्णांक symmetric_sample_bits:1;

	/* Do not create a PCM क्रम this DAI link (Backend link) */
	अचिन्हित पूर्णांक no_pcm:1;

	/* This DAI link can route to other DAI links at runसमय (Frontend)*/
	अचिन्हित पूर्णांक dynamic:1;

	/* DPCM capture and Playback support */
	अचिन्हित पूर्णांक dpcm_capture:1;
	अचिन्हित पूर्णांक dpcm_playback:1;

	/* DPCM used FE & BE merged क्रमmat */
	अचिन्हित पूर्णांक dpcm_merged_क्रमmat:1;
	/* DPCM used FE & BE merged channel */
	अचिन्हित पूर्णांक dpcm_merged_chan:1;
	/* DPCM used FE & BE merged rate */
	अचिन्हित पूर्णांक dpcm_merged_rate:1;

	/* pmकरोwn_समय is ignored at stop */
	अचिन्हित पूर्णांक ignore_pmकरोwn_समय:1;

	/* Do not create a PCM क्रम this DAI link (Backend link) */
	अचिन्हित पूर्णांक ignore:1;

#अगर_घोषित CONFIG_SND_SOC_TOPOLOGY
	काष्ठा snd_soc_करोbj करोbj; /* For topology */
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा snd_soc_dai_link_component*
asoc_link_to_cpu(काष्ठा snd_soc_dai_link *link, पूर्णांक n) अणु
	वापस &(link)->cpus[n];
पूर्ण

अटल अंतरभूत काष्ठा snd_soc_dai_link_component*
asoc_link_to_codec(काष्ठा snd_soc_dai_link *link, पूर्णांक n) अणु
	वापस &(link)->codecs[n];
पूर्ण

अटल अंतरभूत काष्ठा snd_soc_dai_link_component*
asoc_link_to_platक्रमm(काष्ठा snd_soc_dai_link *link, पूर्णांक n) अणु
	वापस &(link)->platक्रमms[n];
पूर्ण

#घोषणा क्रम_each_link_codecs(link, i, codec)				\
	क्रम ((i) = 0;							\
	     ((i) < link->num_codecs) &&				\
		     ((codec) = asoc_link_to_codec(link, i));		\
	     (i)++)

#घोषणा क्रम_each_link_platक्रमms(link, i, platक्रमm)			\
	क्रम ((i) = 0;							\
	     ((i) < link->num_platक्रमms) &&				\
		     ((platक्रमm) = asoc_link_to_platक्रमm(link, i));	\
	     (i)++)

#घोषणा क्रम_each_link_cpus(link, i, cpu)				\
	क्रम ((i) = 0;							\
	     ((i) < link->num_cpus) &&					\
		     ((cpu) = asoc_link_to_cpu(link, i));		\
	     (i)++)

/*
 * Sample 1 : Single CPU/Codec/Platक्रमm
 *
 * SND_SOC_DAILINK_DEFS(test,
 *	DAILINK_COMP_ARRAY(COMP_CPU("cpu_dai")),
 *	DAILINK_COMP_ARRAY(COMP_CODEC("codec", "codec_dai")),
 *	DAILINK_COMP_ARRAY(COMP_PLATFORM("platform")));
 *
 * काष्ठा snd_soc_dai_link link = अणु
 *	...
 *	SND_SOC_DAILINK_REG(test),
 * पूर्ण;
 *
 * Sample 2 : Multi CPU/Codec, no Platक्रमm
 *
 * SND_SOC_DAILINK_DEFS(test,
 *	DAILINK_COMP_ARRAY(COMP_CPU("cpu_dai1"),
 *			   COMP_CPU("cpu_dai2")),
 *	DAILINK_COMP_ARRAY(COMP_CODEC("codec1", "codec_dai1"),
 *			   COMP_CODEC("codec2", "codec_dai2")));
 *
 * काष्ठा snd_soc_dai_link link = अणु
 *	...
 *	SND_SOC_DAILINK_REG(test),
 * पूर्ण;
 *
 * Sample 3 : Define each CPU/Codec/Platक्रमm manually
 *
 * SND_SOC_DAILINK_DEF(test_cpu,
 *		DAILINK_COMP_ARRAY(COMP_CPU("cpu_dai1"),
 *				   COMP_CPU("cpu_dai2")));
 * SND_SOC_DAILINK_DEF(test_codec,
 *		DAILINK_COMP_ARRAY(COMP_CODEC("codec1", "codec_dai1"),
 *				   COMP_CODEC("codec2", "codec_dai2")));
 * SND_SOC_DAILINK_DEF(test_platक्रमm,
 *		DAILINK_COMP_ARRAY(COMP_PLATFORM("platform")));
 *
 * काष्ठा snd_soc_dai_link link = अणु
 *	...
 *	SND_SOC_DAILINK_REG(test_cpu,
 *			    test_codec,
 *			    test_platक्रमm),
 * पूर्ण;
 *
 * Sample 4 : Sample3 without platक्रमm
 *
 * काष्ठा snd_soc_dai_link link = अणु
 *	...
 *	SND_SOC_DAILINK_REG(test_cpu,
 *			    test_codec);
 * पूर्ण;
 */

#घोषणा SND_SOC_DAILINK_REG1(name)	 SND_SOC_DAILINK_REG3(name##_cpus, name##_codecs, name##_platक्रमms)
#घोषणा SND_SOC_DAILINK_REG2(cpu, codec) SND_SOC_DAILINK_REG3(cpu, codec, null_dailink_component)
#घोषणा SND_SOC_DAILINK_REG3(cpu, codec, platक्रमm)	\
	.cpus		= cpu,				\
	.num_cpus	= ARRAY_SIZE(cpu),		\
	.codecs		= codec,			\
	.num_codecs	= ARRAY_SIZE(codec),		\
	.platक्रमms	= platक्रमm,			\
	.num_platक्रमms	= ARRAY_SIZE(platक्रमm)

#घोषणा SND_SOC_DAILINK_REGx(_1, _2, _3, func, ...) func
#घोषणा SND_SOC_DAILINK_REG(...) \
	SND_SOC_DAILINK_REGx(__VA_ARGS__,		\
			SND_SOC_DAILINK_REG3,	\
			SND_SOC_DAILINK_REG2,	\
			SND_SOC_DAILINK_REG1)(__VA_ARGS__)

#घोषणा SND_SOC_DAILINK_DEF(name, def...)		\
	अटल काष्ठा snd_soc_dai_link_component name[]	= अणु def पूर्ण

#घोषणा SND_SOC_DAILINK_DEFS(name, cpu, codec, platक्रमm...)	\
	SND_SOC_DAILINK_DEF(name##_cpus, cpu);			\
	SND_SOC_DAILINK_DEF(name##_codecs, codec);		\
	SND_SOC_DAILINK_DEF(name##_platक्रमms, platक्रमm)

#घोषणा DAILINK_COMP_ARRAY(param...)	param
#घोषणा COMP_EMPTY()			अणु पूर्ण
#घोषणा COMP_CPU(_dai)			अणु .dai_name = _dai, पूर्ण
#घोषणा COMP_CODEC(_name, _dai)		अणु .name = _name, .dai_name = _dai, पूर्ण
#घोषणा COMP_PLATFORM(_name)		अणु .name = _name पूर्ण
#घोषणा COMP_AUX(_name)			अणु .name = _name पूर्ण
#घोषणा COMP_CODEC_CONF(_name)		अणु .name = _name पूर्ण
#घोषणा COMP_DUMMY()			अणु .name = "snd-soc-dummy", .dai_name = "snd-soc-dummy-dai", पूर्ण

बाह्य काष्ठा snd_soc_dai_link_component null_dailink_component[0];


काष्ठा snd_soc_codec_conf अणु
	/*
	 * specअगरy device either by device name, or by
	 * DT/OF node, but not both.
	 */
	काष्ठा snd_soc_dai_link_component dlc;

	/*
	 * optional map of kcontrol, widget and path name prefixes that are
	 * associated per device
	 */
	स्थिर अक्षर *name_prefix;
पूर्ण;

काष्ठा snd_soc_aux_dev अणु
	/*
	 * specअगरy multi-codec either by device name, or by
	 * DT/OF node, but not both.
	 */
	काष्ठा snd_soc_dai_link_component dlc;

	/* codec/machine specअगरic init - e.g. add machine controls */
	पूर्णांक (*init)(काष्ठा snd_soc_component *component);
पूर्ण;

/* SoC card */
काष्ठा snd_soc_card अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *दीर्घ_name;
	स्थिर अक्षर *driver_name;
	स्थिर अक्षर *components;
#अगर_घोषित CONFIG_DMI
	अक्षर dmi_दीर्घname[80];
#पूर्ण_अगर /* CONFIG_DMI */
	अक्षर topology_लघुname[32];

	काष्ठा device *dev;
	काष्ठा snd_card *snd_card;
	काष्ठा module *owner;

	काष्ठा mutex mutex;
	काष्ठा mutex dapm_mutex;

	/* Mutex क्रम PCM operations */
	काष्ठा mutex pcm_mutex;
	क्रमागत snd_soc_pcm_subclass pcm_subclass;

	spinlock_t dpcm_lock;

	पूर्णांक (*probe)(काष्ठा snd_soc_card *card);
	पूर्णांक (*late_probe)(काष्ठा snd_soc_card *card);
	पूर्णांक (*हटाओ)(काष्ठा snd_soc_card *card);

	/* the pre and post PM functions are used to करो any PM work beक्रमe and
	 * after the codec and DAI's करो any PM work. */
	पूर्णांक (*suspend_pre)(काष्ठा snd_soc_card *card);
	पूर्णांक (*suspend_post)(काष्ठा snd_soc_card *card);
	पूर्णांक (*resume_pre)(काष्ठा snd_soc_card *card);
	पूर्णांक (*resume_post)(काष्ठा snd_soc_card *card);

	/* callbacks */
	पूर्णांक (*set_bias_level)(काष्ठा snd_soc_card *,
			      काष्ठा snd_soc_dapm_context *dapm,
			      क्रमागत snd_soc_bias_level level);
	पूर्णांक (*set_bias_level_post)(काष्ठा snd_soc_card *,
				   काष्ठा snd_soc_dapm_context *dapm,
				   क्रमागत snd_soc_bias_level level);

	पूर्णांक (*add_dai_link)(काष्ठा snd_soc_card *,
			    काष्ठा snd_soc_dai_link *link);
	व्योम (*हटाओ_dai_link)(काष्ठा snd_soc_card *,
			    काष्ठा snd_soc_dai_link *link);

	दीर्घ pmकरोwn_समय;

	/* CPU <--> Codec DAI links  */
	काष्ठा snd_soc_dai_link *dai_link;  /* predefined links only */
	पूर्णांक num_links;  /* predefined links only */

	काष्ठा list_head rtd_list;
	पूर्णांक num_rtd;

	/* optional codec specअगरic configuration */
	काष्ठा snd_soc_codec_conf *codec_conf;
	पूर्णांक num_configs;

	/*
	 * optional auxiliary devices such as amplअगरiers or codecs with DAI
	 * link unused
	 */
	काष्ठा snd_soc_aux_dev *aux_dev;
	पूर्णांक num_aux_devs;
	काष्ठा list_head aux_comp_list;

	स्थिर काष्ठा snd_kcontrol_new *controls;
	पूर्णांक num_controls;

	/*
	 * Card-specअगरic routes and widमाला_लो.
	 * Note: of_dapm_xxx क्रम Device Tree; Otherwise क्रम driver build-in.
	 */
	स्थिर काष्ठा snd_soc_dapm_widget *dapm_widमाला_लो;
	पूर्णांक num_dapm_widमाला_लो;
	स्थिर काष्ठा snd_soc_dapm_route *dapm_routes;
	पूर्णांक num_dapm_routes;
	स्थिर काष्ठा snd_soc_dapm_widget *of_dapm_widमाला_लो;
	पूर्णांक num_of_dapm_widमाला_लो;
	स्थिर काष्ठा snd_soc_dapm_route *of_dapm_routes;
	पूर्णांक num_of_dapm_routes;

	/* lists of probed devices beदीर्घing to this card */
	काष्ठा list_head component_dev_list;
	काष्ठा list_head list;

	काष्ठा list_head widमाला_लो;
	काष्ठा list_head paths;
	काष्ठा list_head dapm_list;
	काष्ठा list_head dapm_dirty;

	/* attached dynamic objects */
	काष्ठा list_head करोbj_list;

	/* Generic DAPM context क्रम the card */
	काष्ठा snd_soc_dapm_context dapm;
	काष्ठा snd_soc_dapm_stats dapm_stats;
	काष्ठा snd_soc_dapm_update *update;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_card_root;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM_SLEEP
	काष्ठा work_काष्ठा deferred_resume_work;
#पूर्ण_अगर
	u32 pop_समय;

	/* bit field */
	अचिन्हित पूर्णांक instantiated:1;
	अचिन्हित पूर्णांक topology_लघुname_created:1;
	अचिन्हित पूर्णांक fully_routed:1;
	अचिन्हित पूर्णांक disable_route_checks:1;
	अचिन्हित पूर्णांक probed:1;
	अचिन्हित पूर्णांक component_chaining:1;

	व्योम *drvdata;
पूर्ण;
#घोषणा क्रम_each_card_prelinks(card, i, link)				\
	क्रम ((i) = 0;							\
	     ((i) < (card)->num_links) && ((link) = &(card)->dai_link[i]); \
	     (i)++)
#घोषणा क्रम_each_card_pre_auxs(card, i, aux)				\
	क्रम ((i) = 0;							\
	     ((i) < (card)->num_aux_devs) && ((aux) = &(card)->aux_dev[i]); \
	     (i)++)

#घोषणा क्रम_each_card_rtds(card, rtd)			\
	list_क्रम_each_entry(rtd, &(card)->rtd_list, list)
#घोषणा क्रम_each_card_rtds_safe(card, rtd, _rtd)	\
	list_क्रम_each_entry_safe(rtd, _rtd, &(card)->rtd_list, list)

#घोषणा क्रम_each_card_auxs(card, component)			\
	list_क्रम_each_entry(component, &card->aux_comp_list, card_aux_list)
#घोषणा क्रम_each_card_auxs_safe(card, component, _comp)	\
	list_क्रम_each_entry_safe(component, _comp,	\
				 &card->aux_comp_list, card_aux_list)

#घोषणा क्रम_each_card_components(card, component)			\
	list_क्रम_each_entry(component, &(card)->component_dev_list, card_list)

#घोषणा क्रम_each_card_dapms(card, dapm)					\
	list_क्रम_each_entry(dapm, &card->dapm_list, list)

#घोषणा क्रम_each_card_widमाला_लो(card, w)\
	list_क्रम_each_entry(w, &card->widमाला_लो, list)
#घोषणा क्रम_each_card_widमाला_लो_safe(card, w, _w)	\
	list_क्रम_each_entry_safe(w, _w, &card->widमाला_लो, list)

/* SoC machine DAI configuration, glues a codec and cpu DAI together */
काष्ठा snd_soc_pcm_runसमय अणु
	काष्ठा device *dev;
	काष्ठा snd_soc_card *card;
	काष्ठा snd_soc_dai_link *dai_link;
	काष्ठा snd_pcm_ops ops;

	अचिन्हित पूर्णांक params_select; /* currently selected param क्रम dai link */

	/* Dynamic PCM BE runसमय data */
	काष्ठा snd_soc_dpcm_runसमय dpcm[2];

	दीर्घ pmकरोwn_समय;

	/* runसमय devices */
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_compr *compr;

	/*
	 * dais = cpu_dai + codec_dai
	 * see
	 *	soc_new_pcm_runसमय()
	 *	asoc_rtd_to_cpu()
	 *	asoc_rtd_to_codec()
	 */
	काष्ठा snd_soc_dai **dais;
	अचिन्हित पूर्णांक num_codecs;
	अचिन्हित पूर्णांक num_cpus;

	काष्ठा snd_soc_dapm_widget *playback_widget;
	काष्ठा snd_soc_dapm_widget *capture_widget;

	काष्ठा delayed_work delayed_work;
	व्योम (*बंद_delayed_work_func)(काष्ठा snd_soc_pcm_runसमय *rtd);
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_dpcm_root;
#पूर्ण_अगर

	अचिन्हित पूर्णांक num; /* 0-based and monotonic increasing */
	काष्ठा list_head list; /* rtd list of the soc card */

	/* function mark */
	काष्ठा snd_pcm_substream *mark_startup;
	काष्ठा snd_pcm_substream *mark_hw_params;
	काष्ठा snd_pcm_substream *mark_trigger;
	काष्ठा snd_compr_stream  *mark_compr_startup;

	/* bit field */
	अचिन्हित पूर्णांक pop_रुको:1;
	अचिन्हित पूर्णांक fe_compr:1; /* क्रम Dynamic PCM */

	पूर्णांक num_components;
	काष्ठा snd_soc_component *components[]; /* CPU/Codec/Platक्रमm */
पूर्ण;
/* see soc_new_pcm_runसमय()  */
#घोषणा asoc_rtd_to_cpu(rtd, n)   (rtd)->dais[n]
#घोषणा asoc_rtd_to_codec(rtd, n) (rtd)->dais[n + (rtd)->num_cpus]
#घोषणा asoc_substream_to_rtd(substream) \
	(काष्ठा snd_soc_pcm_runसमय *)snd_pcm_substream_chip(substream)

#घोषणा क्रम_each_rtd_components(rtd, i, component)			\
	क्रम ((i) = 0, component = शून्य;					\
	     ((i) < rtd->num_components) && ((component) = rtd->components[i]);\
	     (i)++)
#घोषणा क्रम_each_rtd_cpu_dais(rtd, i, dai)				\
	क्रम ((i) = 0;							\
	     ((i) < rtd->num_cpus) && ((dai) = asoc_rtd_to_cpu(rtd, i)); \
	     (i)++)
#घोषणा क्रम_each_rtd_codec_dais(rtd, i, dai)				\
	क्रम ((i) = 0;							\
	     ((i) < rtd->num_codecs) && ((dai) = asoc_rtd_to_codec(rtd, i)); \
	     (i)++)
#घोषणा क्रम_each_rtd_dais(rtd, i, dai)					\
	क्रम ((i) = 0;							\
	     ((i) < (rtd)->num_cpus + (rtd)->num_codecs) &&		\
		     ((dai) = (rtd)->dais[i]);				\
	     (i)++)

व्योम snd_soc_बंद_delayed_work(काष्ठा snd_soc_pcm_runसमय *rtd);

/* mixer control */
काष्ठा soc_mixer_control अणु
	पूर्णांक min, max, platक्रमm_max;
	पूर्णांक reg, rreg;
	अचिन्हित पूर्णांक shअगरt, rshअगरt;
	अचिन्हित पूर्णांक sign_bit;
	अचिन्हित पूर्णांक invert:1;
	अचिन्हित पूर्णांक स्वतःdisable:1;
#अगर_घोषित CONFIG_SND_SOC_TOPOLOGY
	काष्ठा snd_soc_करोbj करोbj;
#पूर्ण_अगर
पूर्ण;

काष्ठा soc_bytes अणु
	पूर्णांक base;
	पूर्णांक num_regs;
	u32 mask;
पूर्ण;

काष्ठा soc_bytes_ext अणु
	पूर्णांक max;
#अगर_घोषित CONFIG_SND_SOC_TOPOLOGY
	काष्ठा snd_soc_करोbj करोbj;
#पूर्ण_अगर
	/* used क्रम TLV byte control */
	पूर्णांक (*get)(काष्ठा snd_kcontrol *kcontrol, अचिन्हित पूर्णांक __user *bytes,
			अचिन्हित पूर्णांक size);
	पूर्णांक (*put)(काष्ठा snd_kcontrol *kcontrol, स्थिर अचिन्हित पूर्णांक __user *bytes,
			अचिन्हित पूर्णांक size);
पूर्ण;

/* multi रेजिस्टर control */
काष्ठा soc_mreg_control अणु
	दीर्घ min, max;
	अचिन्हित पूर्णांक regbase, regcount, nbits, invert;
पूर्ण;

/* क्रमागतerated kcontrol */
काष्ठा soc_क्रमागत अणु
	पूर्णांक reg;
	अचिन्हित अक्षर shअगरt_l;
	अचिन्हित अक्षर shअगरt_r;
	अचिन्हित पूर्णांक items;
	अचिन्हित पूर्णांक mask;
	स्थिर अक्षर * स्थिर *texts;
	स्थिर अचिन्हित पूर्णांक *values;
	अचिन्हित पूर्णांक स्वतःdisable:1;
#अगर_घोषित CONFIG_SND_SOC_TOPOLOGY
	काष्ठा snd_soc_करोbj करोbj;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत bool snd_soc_volsw_is_stereo(काष्ठा soc_mixer_control *mc)
अणु
	अगर (mc->reg == mc->rreg && mc->shअगरt == mc->rshअगरt)
		वापस false;
	/*
	 * mc->reg == mc->rreg && mc->shअगरt != mc->rshअगरt, or
	 * mc->reg != mc->rreg means that the control is
	 * stereo (bits in one रेजिस्टर or in two रेजिस्टरs)
	 */
	वापस true;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_soc_क्रमागत_val_to_item(काष्ठा soc_क्रमागत *e,
	अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!e->values)
		वापस val;

	क्रम (i = 0; i < e->items; i++)
		अगर (val == e->values[i])
			वापस i;

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_soc_क्रमागत_item_to_val(काष्ठा soc_क्रमागत *e,
	अचिन्हित पूर्णांक item)
अणु
	अगर (!e->values)
		वापस item;

	वापस e->values[item];
पूर्ण

/**
 * snd_soc_kcontrol_component() - Returns the component that रेजिस्टरed the
 *  control
 * @kcontrol: The control क्रम which to get the component
 *
 * Note: This function will work correctly अगर the control has been रेजिस्टरed
 * क्रम a component. With snd_soc_add_codec_controls() or via table based
 * setup क्रम either a CODEC or component driver. Otherwise the behavior is
 * undefined.
 */
अटल अंतरभूत काष्ठा snd_soc_component *snd_soc_kcontrol_component(
	काष्ठा snd_kcontrol *kcontrol)
अणु
	वापस snd_kcontrol_chip(kcontrol);
पूर्ण

पूर्णांक snd_soc_util_init(व्योम);
व्योम snd_soc_util_निकास(व्योम);

पूर्णांक snd_soc_of_parse_card_name(काष्ठा snd_soc_card *card,
			       स्थिर अक्षर *propname);
पूर्णांक snd_soc_of_parse_audio_simple_widमाला_लो(काष्ठा snd_soc_card *card,
					  स्थिर अक्षर *propname);
पूर्णांक snd_soc_of_get_slot_mask(काष्ठा device_node *np,
			     स्थिर अक्षर *prop_name,
			     अचिन्हित पूर्णांक *mask);
पूर्णांक snd_soc_of_parse_tdm_slot(काष्ठा device_node *np,
			      अचिन्हित पूर्णांक *tx_mask,
			      अचिन्हित पूर्णांक *rx_mask,
			      अचिन्हित पूर्णांक *slots,
			      अचिन्हित पूर्णांक *slot_width);
व्योम snd_soc_of_parse_node_prefix(काष्ठा device_node *np,
				   काष्ठा snd_soc_codec_conf *codec_conf,
				   काष्ठा device_node *of_node,
				   स्थिर अक्षर *propname);
अटल अंतरभूत
व्योम snd_soc_of_parse_audio_prefix(काष्ठा snd_soc_card *card,
				   काष्ठा snd_soc_codec_conf *codec_conf,
				   काष्ठा device_node *of_node,
				   स्थिर अक्षर *propname)
अणु
	snd_soc_of_parse_node_prefix(card->dev->of_node,
				     codec_conf, of_node, propname);
पूर्ण

पूर्णांक snd_soc_of_parse_audio_routing(काष्ठा snd_soc_card *card,
				   स्थिर अक्षर *propname);
पूर्णांक snd_soc_of_parse_aux_devs(काष्ठा snd_soc_card *card, स्थिर अक्षर *propname);
अचिन्हित पूर्णांक snd_soc_of_parse_daअगरmt(काष्ठा device_node *np,
				     स्थिर अक्षर *prefix,
				     काष्ठा device_node **bitclkmaster,
				     काष्ठा device_node **framemaster);
पूर्णांक snd_soc_get_dai_id(काष्ठा device_node *ep);
पूर्णांक snd_soc_get_dai_name(स्थिर काष्ठा of_phandle_args *args,
			 स्थिर अक्षर **dai_name);
पूर्णांक snd_soc_of_get_dai_name(काष्ठा device_node *of_node,
			    स्थिर अक्षर **dai_name);
पूर्णांक snd_soc_of_get_dai_link_codecs(काष्ठा device *dev,
				   काष्ठा device_node *of_node,
				   काष्ठा snd_soc_dai_link *dai_link);
व्योम snd_soc_of_put_dai_link_codecs(काष्ठा snd_soc_dai_link *dai_link);

पूर्णांक snd_soc_add_pcm_runसमय(काष्ठा snd_soc_card *card,
			    काष्ठा snd_soc_dai_link *dai_link);
व्योम snd_soc_हटाओ_pcm_runसमय(काष्ठा snd_soc_card *card,
				काष्ठा snd_soc_pcm_runसमय *rtd);

काष्ठा snd_soc_dai *snd_soc_रेजिस्टर_dai(काष्ठा snd_soc_component *component,
					 काष्ठा snd_soc_dai_driver *dai_drv,
					 bool legacy_dai_naming);
काष्ठा snd_soc_dai *devm_snd_soc_रेजिस्टर_dai(काष्ठा device *dev,
					      काष्ठा snd_soc_component *component,
					      काष्ठा snd_soc_dai_driver *dai_drv,
					      bool legacy_dai_naming);
व्योम snd_soc_unरेजिस्टर_dai(काष्ठा snd_soc_dai *dai);

काष्ठा snd_soc_dai *snd_soc_find_dai(
	स्थिर काष्ठा snd_soc_dai_link_component *dlc);
काष्ठा snd_soc_dai *snd_soc_find_dai_with_mutex(
	स्थिर काष्ठा snd_soc_dai_link_component *dlc);

#समावेश <sound/soc-dai.h>

अटल अंतरभूत
पूर्णांक snd_soc_fixup_dai_links_platक्रमm_name(काष्ठा snd_soc_card *card,
					  स्थिर अक्षर *platक्रमm_name)
अणु
	काष्ठा snd_soc_dai_link *dai_link;
	स्थिर अक्षर *name;
	पूर्णांक i;

	अगर (!platक्रमm_name) /* nothing to करो */
		वापस 0;

	/* set platक्रमm name क्रम each dailink */
	क्रम_each_card_prelinks(card, i, dai_link) अणु
		/* only single platक्रमm is supported क्रम now */
		अगर (dai_link->num_platक्रमms != 1)
			वापस -EINVAL;

		अगर (!dai_link->platक्रमms)
			वापस -EINVAL;

		name = devm_kstrdup(card->dev, platक्रमm_name, GFP_KERNEL);
		अगर (!name)
			वापस -ENOMEM;

		/* only single platक्रमm is supported क्रम now */
		dai_link->platक्रमms->name = name;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
बाह्य काष्ठा dentry *snd_soc_debugfs_root;
#पूर्ण_अगर

बाह्य स्थिर काष्ठा dev_pm_ops snd_soc_pm_ops;

/* Helper functions */
अटल अंतरभूत व्योम snd_soc_dapm_mutex_lock(काष्ठा snd_soc_dapm_context *dapm)
अणु
	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
पूर्ण

अटल अंतरभूत व्योम snd_soc_dapm_mutex_unlock(काष्ठा snd_soc_dapm_context *dapm)
अणु
	mutex_unlock(&dapm->card->dapm_mutex);
पूर्ण

#समावेश <sound/soc-component.h>
#समावेश <sound/soc-card.h>
#समावेश <sound/soc-jack.h>

#पूर्ण_अगर
