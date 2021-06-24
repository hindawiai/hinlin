<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drivers/media/i2c/ccs/ccs-quirk.h
 *
 * Generic driver क्रम MIPI CCS/SMIA/SMIA++ compliant camera sensors
 *
 * Copyright (C) 2020 Intel Corporation
 * Copyright (C) 2011--2012 Nokia Corporation
 * Contact: Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __CCS_QUIRK__
#घोषणा __CCS_QUIRK__

काष्ठा ccs_sensor;

/**
 * काष्ठा ccs_quirk - quirks क्रम sensors that deviate from SMIA++ standard
 *
 * @limits: Replace sensor->limits with values which can't be पढ़ो from
 *	    sensor रेजिस्टरs. Called the first समय the sensor is घातered up.
 * @post_घातeron: Called always after the sensor has been fully घातered on.
 * @pre_streamon: Called just beक्रमe streaming is enabled.
 * @post_streamoff: Called right after stopping streaming.
 * @pll_flags: Return flags क्रम the PLL calculator.
 * @init: Quirk initialisation, called the last in probe(). This is
 *	  also appropriate क्रम adding sensor specअगरic controls, क्रम instance.
 * @reg_access: Register access quirk. The quirk may भागert the access
 *		to another रेजिस्टर, or no रेजिस्टर at all.
 *
 *		@ग_लिखो: Is this पढ़ो (false) or ग_लिखो (true) access?
 *		@reg: Poपूर्णांकer to the रेजिस्टर to access
 *		@value: Register value, set by the caller on ग_लिखो, or
 *			by the quirk on पढ़ो
 *
 * @flags: Quirk flags
 *
 *		@वापस: 0 on success, -ENOIOCTLCMD अगर no रेजिस्टर
 *			 access may be करोne by the caller (शेष पढ़ो
 *			 value is zero), अन्यथा negative error code on error
 */
काष्ठा ccs_quirk अणु
	पूर्णांक (*limits)(काष्ठा ccs_sensor *sensor);
	पूर्णांक (*post_घातeron)(काष्ठा ccs_sensor *sensor);
	पूर्णांक (*pre_streamon)(काष्ठा ccs_sensor *sensor);
	पूर्णांक (*post_streamoff)(काष्ठा ccs_sensor *sensor);
	अचिन्हित दीर्घ (*pll_flags)(काष्ठा ccs_sensor *sensor);
	पूर्णांक (*init)(काष्ठा ccs_sensor *sensor);
	पूर्णांक (*reg_access)(काष्ठा ccs_sensor *sensor, bool ग_लिखो, u32 *reg,
			  u32 *val);
	अचिन्हित दीर्घ flags;
पूर्ण;

#घोषणा CCS_QUIRK_FLAG_8BIT_READ_ONLY			(1 << 0)

काष्ठा ccs_reg_8 अणु
	u16 reg;
	u8 val;
पूर्ण;

#घोषणा CCS_MK_QUIRK_REG_8(_reg, _val) \
	अणु				\
		.reg = (u16)_reg,	\
		.val = _val,		\
	पूर्ण

#घोषणा ccs_call_quirk(sensor, _quirk, ...)				\
	((sensor)->minfo.quirk &&					\
	 (sensor)->minfo.quirk->_quirk ?				\
	 (sensor)->minfo.quirk->_quirk(sensor, ##__VA_ARGS__) : 0)

#घोषणा ccs_needs_quirk(sensor, _quirk)		\
	((sensor)->minfo.quirk ?			\
	 (sensor)->minfo.quirk->flags & _quirk : 0)

बाह्य स्थिर काष्ठा ccs_quirk smiapp_jt8ev1_quirk;
बाह्य स्थिर काष्ठा ccs_quirk smiapp_imx125es_quirk;
बाह्य स्थिर काष्ठा ccs_quirk smiapp_jt8ew9_quirk;
बाह्य स्थिर काष्ठा ccs_quirk smiapp_tcm8500md_quirk;

#पूर्ण_अगर /* __CCS_QUIRK__ */
