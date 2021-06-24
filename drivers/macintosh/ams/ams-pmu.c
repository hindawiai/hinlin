<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Apple Motion Sensor driver (PMU variant)
 *
 * Copyright (C) 2006 Michael Hanselmann (linux-kernel@hansmi.ch)
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>

#समावेश "ams.h"

/* Attitude */
#घोषणा AMS_X			0x00
#घोषणा AMS_Y			0x01
#घोषणा AMS_Z			0x02

/* Not exactly known, maybe chip venकरोr */
#घोषणा AMS_VENDOR		0x03

/* Freefall रेजिस्टरs */
#घोषणा AMS_FF_CLEAR		0x04
#घोषणा AMS_FF_ENABLE		0x05
#घोषणा AMS_FF_LOW_LIMIT	0x06
#घोषणा AMS_FF_DEBOUNCE		0x07

/* Shock रेजिस्टरs */
#घोषणा AMS_SHOCK_CLEAR		0x08
#घोषणा AMS_SHOCK_ENABLE	0x09
#घोषणा AMS_SHOCK_HIGH_LIMIT	0x0a
#घोषणा AMS_SHOCK_DEBOUNCE	0x0b

/* Global पूर्णांकerrupt and घातer control रेजिस्टर */
#घोषणा AMS_CONTROL		0x0c

अटल u8 ams_pmu_cmd;

अटल व्योम ams_pmu_req_complete(काष्ठा adb_request *req)
अणु
	complete((काष्ठा completion *)req->arg);
पूर्ण

/* Only call this function from task context */
अटल व्योम ams_pmu_set_रेजिस्टर(u8 reg, u8 value)
अणु
	अटल काष्ठा adb_request req;
	DECLARE_COMPLETION(req_complete);

	req.arg = &req_complete;
	अगर (pmu_request(&req, ams_pmu_req_complete, 4, ams_pmu_cmd, 0x00, reg, value))
		वापस;

	रुको_क्रम_completion(&req_complete);
पूर्ण

/* Only call this function from task context */
अटल u8 ams_pmu_get_रेजिस्टर(u8 reg)
अणु
	अटल काष्ठा adb_request req;
	DECLARE_COMPLETION(req_complete);

	req.arg = &req_complete;
	अगर (pmu_request(&req, ams_pmu_req_complete, 3, ams_pmu_cmd, 0x01, reg))
		वापस 0;

	रुको_क्रम_completion(&req_complete);

	अगर (req.reply_len > 0)
		वापस req.reply[0];
	अन्यथा
		वापस 0;
पूर्ण

/* Enables or disables the specअगरied पूर्णांकerrupts */
अटल व्योम ams_pmu_set_irq(क्रमागत ams_irq reg, अक्षर enable)
अणु
	अगर (reg & AMS_IRQ_FREEFALL) अणु
		u8 val = ams_pmu_get_रेजिस्टर(AMS_FF_ENABLE);
		अगर (enable)
			val |= 0x80;
		अन्यथा
			val &= ~0x80;
		ams_pmu_set_रेजिस्टर(AMS_FF_ENABLE, val);
	पूर्ण

	अगर (reg & AMS_IRQ_SHOCK) अणु
		u8 val = ams_pmu_get_रेजिस्टर(AMS_SHOCK_ENABLE);
		अगर (enable)
			val |= 0x80;
		अन्यथा
			val &= ~0x80;
		ams_pmu_set_रेजिस्टर(AMS_SHOCK_ENABLE, val);
	पूर्ण

	अगर (reg & AMS_IRQ_GLOBAL) अणु
		u8 val = ams_pmu_get_रेजिस्टर(AMS_CONTROL);
		अगर (enable)
			val |= 0x80;
		अन्यथा
			val &= ~0x80;
		ams_pmu_set_रेजिस्टर(AMS_CONTROL, val);
	पूर्ण
पूर्ण

अटल व्योम ams_pmu_clear_irq(क्रमागत ams_irq reg)
अणु
	अगर (reg & AMS_IRQ_FREEFALL)
		ams_pmu_set_रेजिस्टर(AMS_FF_CLEAR, 0x00);

	अगर (reg & AMS_IRQ_SHOCK)
		ams_pmu_set_रेजिस्टर(AMS_SHOCK_CLEAR, 0x00);
पूर्ण

अटल u8 ams_pmu_get_venकरोr(व्योम)
अणु
	वापस ams_pmu_get_रेजिस्टर(AMS_VENDOR);
पूर्ण

अटल व्योम ams_pmu_get_xyz(s8 *x, s8 *y, s8 *z)
अणु
	*x = ams_pmu_get_रेजिस्टर(AMS_X);
	*y = ams_pmu_get_रेजिस्टर(AMS_Y);
	*z = ams_pmu_get_रेजिस्टर(AMS_Z);
पूर्ण

अटल व्योम ams_pmu_निकास(व्योम)
अणु
	ams_sensor_detach();

	/* Disable पूर्णांकerrupts */
	ams_pmu_set_irq(AMS_IRQ_ALL, 0);

	/* Clear पूर्णांकerrupts */
	ams_pmu_clear_irq(AMS_IRQ_ALL);

	ams_info.has_device = 0;

	prपूर्णांकk(KERN_INFO "ams: Unloading\n");
पूर्ण

पूर्णांक __init ams_pmu_init(काष्ठा device_node *np)
अणु
	स्थिर u32 *prop;
	पूर्णांक result;

	/* Set implementation stuff */
	ams_info.of_node = np;
	ams_info.निकास = ams_pmu_निकास;
	ams_info.get_venकरोr = ams_pmu_get_venकरोr;
	ams_info.get_xyz = ams_pmu_get_xyz;
	ams_info.clear_irq = ams_pmu_clear_irq;
	ams_info.bustype = BUS_HOST;

	/* Get PMU command, should be 0x4e, but we can never know */
	prop = of_get_property(ams_info.of_node, "reg", शून्य);
	अगर (!prop)
		वापस -ENODEV;

	ams_pmu_cmd = ((*prop) >> 8) & 0xff;

	/* Disable पूर्णांकerrupts */
	ams_pmu_set_irq(AMS_IRQ_ALL, 0);

	/* Clear पूर्णांकerrupts */
	ams_pmu_clear_irq(AMS_IRQ_ALL);

	result = ams_sensor_attach();
	अगर (result < 0)
		वापस result;

	/* Set शेष values */
	ams_pmu_set_रेजिस्टर(AMS_FF_LOW_LIMIT, 0x15);
	ams_pmu_set_रेजिस्टर(AMS_FF_ENABLE, 0x08);
	ams_pmu_set_रेजिस्टर(AMS_FF_DEBOUNCE, 0x14);

	ams_pmu_set_रेजिस्टर(AMS_SHOCK_HIGH_LIMIT, 0x60);
	ams_pmu_set_रेजिस्टर(AMS_SHOCK_ENABLE, 0x0f);
	ams_pmu_set_रेजिस्टर(AMS_SHOCK_DEBOUNCE, 0x14);

	ams_pmu_set_रेजिस्टर(AMS_CONTROL, 0x4f);

	/* Clear पूर्णांकerrupts */
	ams_pmu_clear_irq(AMS_IRQ_ALL);

	ams_info.has_device = 1;

	/* Enable पूर्णांकerrupts */
	ams_pmu_set_irq(AMS_IRQ_ALL, 1);

	prपूर्णांकk(KERN_INFO "ams: Found PMU based motion sensor\n");

	वापस 0;
पूर्ण
