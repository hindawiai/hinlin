<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Windfarm PowerMac thermal control. FCU fan control
 *
 * Copyright 2012 Benjamin Herrenschmidt, IBM Corp.
 */
#अघोषित DEBUG

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <linux/i2c.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sections.h>

#समावेश "windfarm.h"
#समावेश "windfarm_mpu.h"

#घोषणा VERSION "1.0"

#अगर_घोषित DEBUG
#घोषणा DBG(args...)	prपूर्णांकk(args)
#अन्यथा
#घोषणा DBG(args...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

/*
 * This option is "weird" :) Basically, अगर you define this to 1
 * the control loop क्रम the RPMs fans (not PWMs) will apply the
 * correction factor obtained from the PID to the actual RPM
 * speed पढ़ो from the FCU.
 *
 * If you define the below स्थिरant to 0, then it will be
 * applied to the setpoपूर्णांक RPM speed, that is basically the
 * speed we proviously "asked" क्रम.
 *
 * I'm using 0 क्रम now which is what therm_pm72 used to करो and
 * what Darwin -apparently- करोes based on observed behaviour.
 */
#घोषणा RPM_PID_USE_ACTUAL_SPEED	0

/* Default min/max क्रम pumps */
#घोषणा CPU_PUMP_OUTPUT_MAX		3200
#घोषणा CPU_PUMP_OUTPUT_MIN		1250

#घोषणा FCU_FAN_RPM		0
#घोषणा FCU_FAN_PWM		1

काष्ठा wf_fcu_priv अणु
	काष्ठा kref		ref;
	काष्ठा i2c_client	*i2c;
	काष्ठा mutex		lock;
	काष्ठा list_head	fan_list;
	पूर्णांक			rpm_shअगरt;
पूर्ण;

काष्ठा wf_fcu_fan अणु
	काष्ठा list_head	link;
	पूर्णांक			id;
	s32			min, max, target;
	काष्ठा wf_fcu_priv	*fcu_priv;
	काष्ठा wf_control	ctrl;
पूर्ण;

अटल व्योम wf_fcu_release(काष्ठा kref *ref)
अणु
	काष्ठा wf_fcu_priv *pv = container_of(ref, काष्ठा wf_fcu_priv, ref);

	kमुक्त(pv);
पूर्ण

अटल व्योम wf_fcu_fan_release(काष्ठा wf_control *ct)
अणु
	काष्ठा wf_fcu_fan *fan = ct->priv;

	kref_put(&fan->fcu_priv->ref, wf_fcu_release);
	kमुक्त(fan);
पूर्ण

अटल पूर्णांक wf_fcu_पढ़ो_reg(काष्ठा wf_fcu_priv *pv, पूर्णांक reg,
			   अचिन्हित अक्षर *buf, पूर्णांक nb)
अणु
	पूर्णांक tries, nr, nw;

	mutex_lock(&pv->lock);

	buf[0] = reg;
	tries = 0;
	क्रम (;;) अणु
		nw = i2c_master_send(pv->i2c, buf, 1);
		अगर (nw > 0 || (nw < 0 && nw != -EIO) || tries >= 100)
			अवरोध;
		msleep(10);
		++tries;
	पूर्ण
	अगर (nw <= 0) अणु
		pr_err("Failure writing address to FCU: %d", nw);
		nr = nw;
		जाओ bail;
	पूर्ण
	tries = 0;
	क्रम (;;) अणु
		nr = i2c_master_recv(pv->i2c, buf, nb);
		अगर (nr > 0 || (nr < 0 && nr != -ENODEV) || tries >= 100)
			अवरोध;
		msleep(10);
		++tries;
	पूर्ण
	अगर (nr <= 0)
		pr_err("wf_fcu: Failure reading data from FCU: %d", nw);
 bail:
	mutex_unlock(&pv->lock);
	वापस nr;
पूर्ण

अटल पूर्णांक wf_fcu_ग_लिखो_reg(काष्ठा wf_fcu_priv *pv, पूर्णांक reg,
			    स्थिर अचिन्हित अक्षर *ptr, पूर्णांक nb)
अणु
	पूर्णांक tries, nw;
	अचिन्हित अक्षर buf[16];

	buf[0] = reg;
	स_नकल(buf+1, ptr, nb);
	++nb;
	tries = 0;
	क्रम (;;) अणु
		nw = i2c_master_send(pv->i2c, buf, nb);
		अगर (nw > 0 || (nw < 0 && nw != -EIO) || tries >= 100)
			अवरोध;
		msleep(10);
		++tries;
	पूर्ण
	अगर (nw < 0)
		pr_err("wf_fcu: Failure writing to FCU: %d", nw);
	वापस nw;
पूर्ण

अटल पूर्णांक wf_fcu_fan_set_rpm(काष्ठा wf_control *ct, s32 value)
अणु
	काष्ठा wf_fcu_fan *fan = ct->priv;
	काष्ठा wf_fcu_priv *pv = fan->fcu_priv;
	पूर्णांक rc, shअगरt = pv->rpm_shअगरt;
	अचिन्हित अक्षर buf[2];

	अगर (value < fan->min)
		value = fan->min;
	अगर (value > fan->max)
		value = fan->max;

	fan->target = value;

	buf[0] = value >> (8 - shअगरt);
	buf[1] = value << shअगरt;
	rc = wf_fcu_ग_लिखो_reg(pv, 0x10 + (fan->id * 2), buf, 2);
	अगर (rc < 0)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक wf_fcu_fan_get_rpm(काष्ठा wf_control *ct, s32 *value)
अणु
	काष्ठा wf_fcu_fan *fan = ct->priv;
	काष्ठा wf_fcu_priv *pv = fan->fcu_priv;
	पूर्णांक rc, reg_base, shअगरt = pv->rpm_shअगरt;
	अचिन्हित अक्षर failure;
	अचिन्हित अक्षर active;
	अचिन्हित अक्षर buf[2];

	rc = wf_fcu_पढ़ो_reg(pv, 0xb, &failure, 1);
	अगर (rc != 1)
		वापस -EIO;
	अगर ((failure & (1 << fan->id)) != 0)
		वापस -EFAULT;
	rc = wf_fcu_पढ़ो_reg(pv, 0xd, &active, 1);
	अगर (rc != 1)
		वापस -EIO;
	अगर ((active & (1 << fan->id)) == 0)
		वापस -ENXIO;

	/* Programmed value or real current speed */
#अगर RPM_PID_USE_ACTUAL_SPEED
	reg_base = 0x11;
#अन्यथा
	reg_base = 0x10;
#पूर्ण_अगर
	rc = wf_fcu_पढ़ो_reg(pv, reg_base + (fan->id * 2), buf, 2);
	अगर (rc != 2)
		वापस -EIO;

	*value = (buf[0] << (8 - shअगरt)) | buf[1] >> shअगरt;

	वापस 0;
पूर्ण

अटल पूर्णांक wf_fcu_fan_set_pwm(काष्ठा wf_control *ct, s32 value)
अणु
	काष्ठा wf_fcu_fan *fan = ct->priv;
	काष्ठा wf_fcu_priv *pv = fan->fcu_priv;
	अचिन्हित अक्षर buf[2];
	पूर्णांक rc;

	अगर (value < fan->min)
		value = fan->min;
	अगर (value > fan->max)
		value = fan->max;

	fan->target = value;

	value = (value * 2559) / 1000;
	buf[0] = value;
	rc = wf_fcu_ग_लिखो_reg(pv, 0x30 + (fan->id * 2), buf, 1);
	अगर (rc < 0)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक wf_fcu_fan_get_pwm(काष्ठा wf_control *ct, s32 *value)
अणु
	काष्ठा wf_fcu_fan *fan = ct->priv;
	काष्ठा wf_fcu_priv *pv = fan->fcu_priv;
	अचिन्हित अक्षर failure;
	अचिन्हित अक्षर active;
	अचिन्हित अक्षर buf[2];
	पूर्णांक rc;

	rc = wf_fcu_पढ़ो_reg(pv, 0x2b, &failure, 1);
	अगर (rc != 1)
		वापस -EIO;
	अगर ((failure & (1 << fan->id)) != 0)
		वापस -EFAULT;
	rc = wf_fcu_पढ़ो_reg(pv, 0x2d, &active, 1);
	अगर (rc != 1)
		वापस -EIO;
	अगर ((active & (1 << fan->id)) == 0)
		वापस -ENXIO;

	rc = wf_fcu_पढ़ो_reg(pv, 0x30 + (fan->id * 2), buf, 1);
	अगर (rc != 1)
		वापस -EIO;

	*value = (((s32)buf[0]) * 1000) / 2559;

	वापस 0;
पूर्ण

अटल s32 wf_fcu_fan_min(काष्ठा wf_control *ct)
अणु
	काष्ठा wf_fcu_fan *fan = ct->priv;

	वापस fan->min;
पूर्ण

अटल s32 wf_fcu_fan_max(काष्ठा wf_control *ct)
अणु
	काष्ठा wf_fcu_fan *fan = ct->priv;

	वापस fan->max;
पूर्ण

अटल स्थिर काष्ठा wf_control_ops wf_fcu_fan_rpm_ops = अणु
	.set_value	= wf_fcu_fan_set_rpm,
	.get_value	= wf_fcu_fan_get_rpm,
	.get_min	= wf_fcu_fan_min,
	.get_max	= wf_fcu_fan_max,
	.release	= wf_fcu_fan_release,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा wf_control_ops wf_fcu_fan_pwm_ops = अणु
	.set_value	= wf_fcu_fan_set_pwm,
	.get_value	= wf_fcu_fan_get_pwm,
	.get_min	= wf_fcu_fan_min,
	.get_max	= wf_fcu_fan_max,
	.release	= wf_fcu_fan_release,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम wf_fcu_get_pump_minmax(काष्ठा wf_fcu_fan *fan)
अणु
	स्थिर काष्ठा mpu_data *mpu = wf_get_mpu(0);
	u16 pump_min = 0, pump_max = 0xffff;
	u16 पंचांगp[4];

	/* Try to fetch pumps min/max infos from eeprom */
	अगर (mpu) अणु
		स_नकल(&पंचांगp, mpu->processor_part_num, 8);
		अगर (पंचांगp[0] != 0xffff && पंचांगp[1] != 0xffff) अणु
			pump_min = max(pump_min, पंचांगp[0]);
			pump_max = min(pump_max, पंचांगp[1]);
		पूर्ण
		अगर (पंचांगp[2] != 0xffff && पंचांगp[3] != 0xffff) अणु
			pump_min = max(pump_min, पंचांगp[2]);
			pump_max = min(pump_max, पंचांगp[3]);
		पूर्ण
	पूर्ण

	/* Double check the values, this _IS_ needed as the EEPROM on
	 * some dual 2.5Ghz G5s seem, at least, to have both min & max
	 * same to the same value ... (grrrr)
	 */
	अगर (pump_min == pump_max || pump_min == 0 || pump_max == 0xffff) अणु
		pump_min = CPU_PUMP_OUTPUT_MIN;
		pump_max = CPU_PUMP_OUTPUT_MAX;
	पूर्ण

	fan->min = pump_min;
	fan->max = pump_max;

	DBG("wf_fcu: pump min/max for %s set to: [%d..%d] RPM\n",
	    fan->ctrl.name, pump_min, pump_max);
पूर्ण

अटल व्योम wf_fcu_get_rpmfan_minmax(काष्ठा wf_fcu_fan *fan)
अणु
	काष्ठा wf_fcu_priv *pv = fan->fcu_priv;
	स्थिर काष्ठा mpu_data *mpu0 = wf_get_mpu(0);
	स्थिर काष्ठा mpu_data *mpu1 = wf_get_mpu(1);

	/* Default */
	fan->min = 2400 >> pv->rpm_shअगरt;
	fan->max = 56000 >> pv->rpm_shअगरt;

	/* CPU fans have min/max in MPU */
	अगर (mpu0 && !म_भेद(fan->ctrl.name, "cpu-front-fan-0")) अणु
		fan->min = max(fan->min, (s32)mpu0->rminn_पूर्णांकake_fan);
		fan->max = min(fan->max, (s32)mpu0->rmaxn_पूर्णांकake_fan);
		जाओ bail;
	पूर्ण
	अगर (mpu1 && !म_भेद(fan->ctrl.name, "cpu-front-fan-1")) अणु
		fan->min = max(fan->min, (s32)mpu1->rminn_पूर्णांकake_fan);
		fan->max = min(fan->max, (s32)mpu1->rmaxn_पूर्णांकake_fan);
		जाओ bail;
	पूर्ण
	अगर (mpu0 && !म_भेद(fan->ctrl.name, "cpu-rear-fan-0")) अणु
		fan->min = max(fan->min, (s32)mpu0->rminn_exhaust_fan);
		fan->max = min(fan->max, (s32)mpu0->rmaxn_exhaust_fan);
		जाओ bail;
	पूर्ण
	अगर (mpu1 && !म_भेद(fan->ctrl.name, "cpu-rear-fan-1")) अणु
		fan->min = max(fan->min, (s32)mpu1->rminn_exhaust_fan);
		fan->max = min(fan->max, (s32)mpu1->rmaxn_exhaust_fan);
		जाओ bail;
	पूर्ण
	/* Rackmac variants, we just use mpu0 पूर्णांकake */
	अगर (!म_भेदन(fan->ctrl.name, "cpu-fan", 7)) अणु
		fan->min = max(fan->min, (s32)mpu0->rminn_पूर्णांकake_fan);
		fan->max = min(fan->max, (s32)mpu0->rmaxn_पूर्णांकake_fan);
		जाओ bail;
	पूर्ण
 bail:
	DBG("wf_fcu: fan min/max for %s set to: [%d..%d] RPM\n",
	    fan->ctrl.name, fan->min, fan->max);
पूर्ण

अटल व्योम wf_fcu_add_fan(काष्ठा wf_fcu_priv *pv, स्थिर अक्षर *name,
			   पूर्णांक type, पूर्णांक id)
अणु
	काष्ठा wf_fcu_fan *fan;

	fan = kzalloc(माप(*fan), GFP_KERNEL);
	अगर (!fan)
		वापस;
	fan->fcu_priv = pv;
	fan->id = id;
	fan->ctrl.name = name;
	fan->ctrl.priv = fan;

	/* min/max is oddball but the code comes from
	 * therm_pm72 which seems to work so ...
	 */
	अगर (type == FCU_FAN_RPM) अणु
		अगर (!म_भेदन(name, "cpu-pump", म_माप("cpu-pump")))
			wf_fcu_get_pump_minmax(fan);
		अन्यथा
			wf_fcu_get_rpmfan_minmax(fan);
		fan->ctrl.type = WF_CONTROL_RPM_FAN;
		fan->ctrl.ops = &wf_fcu_fan_rpm_ops;
	पूर्ण अन्यथा अणु
		fan->min = 10;
		fan->max = 100;
		fan->ctrl.type = WF_CONTROL_PWM_FAN;
		fan->ctrl.ops = &wf_fcu_fan_pwm_ops;
	पूर्ण

	अगर (wf_रेजिस्टर_control(&fan->ctrl)) अणु
		pr_err("wf_fcu: Failed to register fan %s\n", name);
		kमुक्त(fan);
		वापस;
	पूर्ण
	list_add(&fan->link, &pv->fan_list);
	kref_get(&pv->ref);
पूर्ण

अटल व्योम wf_fcu_lookup_fans(काष्ठा wf_fcu_priv *pv)
अणु
	/* Translation of device-tree location properties to
	 * windfarm fan names
	 */
	अटल स्थिर काष्ठा अणु
		स्थिर अक्षर *dt_name;	/* Device-tree name */
		स्थिर अक्षर *ct_name;	/* Control name */
	पूर्ण loc_trans[] = अणु
		अणु "BACKSIDE",		"backside-fan",		पूर्ण,
		अणु "SYS CTRLR FAN",	"backside-fan",		पूर्ण,
		अणु "DRIVE BAY",		"drive-bay-fan",	पूर्ण,
		अणु "SLOT",		"slots-fan",		पूर्ण,
		अणु "PCI FAN",		"slots-fan",		पूर्ण,
		अणु "CPU A INTAKE",	"cpu-front-fan-0",	पूर्ण,
		अणु "CPU A EXHAUST",	"cpu-rear-fan-0",	पूर्ण,
		अणु "CPU B INTAKE",	"cpu-front-fan-1",	पूर्ण,
		अणु "CPU B EXHAUST",	"cpu-rear-fan-1",	पूर्ण,
		अणु "CPU A PUMP",		"cpu-pump-0",		पूर्ण,
		अणु "CPU B PUMP",		"cpu-pump-1",		पूर्ण,
		अणु "CPU A 1",		"cpu-fan-a-0",		पूर्ण,
		अणु "CPU A 2",		"cpu-fan-b-0",		पूर्ण,
		अणु "CPU A 3",		"cpu-fan-c-0",		पूर्ण,
		अणु "CPU B 1",		"cpu-fan-a-1",		पूर्ण,
		अणु "CPU B 2",		"cpu-fan-b-1",		पूर्ण,
		अणु "CPU B 3",		"cpu-fan-c-1",		पूर्ण,
	पूर्ण;
	काष्ठा device_node *np, *fcu = pv->i2c->dev.of_node;
	पूर्णांक i;

	DBG("Looking up FCU controls in device-tree...\n");

	क्रम_each_child_of_node(fcu, np) अणु
		पूर्णांक id, type = -1;
		स्थिर अक्षर *loc;
		स्थिर अक्षर *name;
		स्थिर u32 *reg;

		DBG(" control: %pOFn, type: %s\n", np, of_node_get_device_type(np));

		/* Detect control type */
		अगर (of_node_is_type(np, "fan-rpm-control") ||
		    of_node_is_type(np, "fan-rpm"))
			type = FCU_FAN_RPM;
		अगर (of_node_is_type(np, "fan-pwm-control") ||
		    of_node_is_type(np, "fan-pwm"))
			type = FCU_FAN_PWM;
		/* Only care about fans क्रम now */
		अगर (type == -1)
			जारी;

		/* Lookup क्रम a matching location */
		loc = of_get_property(np, "location", शून्य);
		reg = of_get_property(np, "reg", शून्य);
		अगर (loc == शून्य || reg == शून्य)
			जारी;
		DBG(" matching location: %s, reg: 0x%08x\n", loc, *reg);

		क्रम (i = 0; i < ARRAY_SIZE(loc_trans); i++) अणु
			अगर (म_भेदन(loc, loc_trans[i].dt_name,
				    म_माप(loc_trans[i].dt_name)))
				जारी;
			name = loc_trans[i].ct_name;

			DBG(" location match, name: %s\n", name);

			अगर (type == FCU_FAN_RPM)
				id = ((*reg) - 0x10) / 2;
			अन्यथा
				id = ((*reg) - 0x30) / 2;
			अगर (id > 7) अणु
				pr_warn("wf_fcu: Can't parse fan ID in device-tree for %pOF\n", np);
				अवरोध;
			पूर्ण
			wf_fcu_add_fan(pv, name, type, id);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम wf_fcu_शेष_fans(काष्ठा wf_fcu_priv *pv)
अणु
	/* We only support the शेष fans क्रम PowerMac7,2 */
	अगर (!of_machine_is_compatible("PowerMac7,2"))
		वापस;

	wf_fcu_add_fan(pv, "backside-fan",	FCU_FAN_PWM, 1);
	wf_fcu_add_fan(pv, "drive-bay-fan",	FCU_FAN_RPM, 2);
	wf_fcu_add_fan(pv, "slots-fan",		FCU_FAN_PWM, 2);
	wf_fcu_add_fan(pv, "cpu-front-fan-0",	FCU_FAN_RPM, 3);
	wf_fcu_add_fan(pv, "cpu-rear-fan-0",	FCU_FAN_RPM, 4);
	wf_fcu_add_fan(pv, "cpu-front-fan-1",	FCU_FAN_RPM, 5);
	wf_fcu_add_fan(pv, "cpu-rear-fan-1",	FCU_FAN_RPM, 6);
पूर्ण

अटल पूर्णांक wf_fcu_init_chip(काष्ठा wf_fcu_priv *pv)
अणु
	अचिन्हित अक्षर buf = 0xff;
	पूर्णांक rc;

	rc = wf_fcu_ग_लिखो_reg(pv, 0xe, &buf, 1);
	अगर (rc < 0)
		वापस -EIO;
	rc = wf_fcu_ग_लिखो_reg(pv, 0x2e, &buf, 1);
	अगर (rc < 0)
		वापस -EIO;
	rc = wf_fcu_पढ़ो_reg(pv, 0, &buf, 1);
	अगर (rc < 0)
		वापस -EIO;
	pv->rpm_shअगरt = (buf == 1) ? 2 : 3;

	pr_debug("wf_fcu: FCU Initialized, RPM fan shift is %d\n",
		 pv->rpm_shअगरt);

	वापस 0;
पूर्ण

अटल पूर्णांक wf_fcu_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wf_fcu_priv *pv;

	pv = kzalloc(माप(*pv), GFP_KERNEL);
	अगर (!pv)
		वापस -ENOMEM;

	kref_init(&pv->ref);
	mutex_init(&pv->lock);
	INIT_LIST_HEAD(&pv->fan_list);
	pv->i2c = client;

	/*
	 * First we must start the FCU which will query the
	 * shअगरt value to apply to RPMs
	 */
	अगर (wf_fcu_init_chip(pv)) अणु
		pr_err("wf_fcu: Initialization failed !\n");
		kमुक्त(pv);
		वापस -ENXIO;
	पूर्ण

	/* First lookup fans in the device-tree */
	wf_fcu_lookup_fans(pv);

	/*
	 * Older machines करोn't have the device-tree entries
	 * we are looking क्रम, just hard code the list
	 */
	अगर (list_empty(&pv->fan_list))
		wf_fcu_शेष_fans(pv);

	/* Still no fans ? FAIL */
	अगर (list_empty(&pv->fan_list)) अणु
		pr_err("wf_fcu: Failed to find fans for your machine\n");
		kमुक्त(pv);
		वापस -ENODEV;
	पूर्ण

	dev_set_drvdata(&client->dev, pv);

	वापस 0;
पूर्ण

अटल पूर्णांक wf_fcu_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा wf_fcu_priv *pv = dev_get_drvdata(&client->dev);
	काष्ठा wf_fcu_fan *fan;

	जबतक (!list_empty(&pv->fan_list)) अणु
		fan = list_first_entry(&pv->fan_list, काष्ठा wf_fcu_fan, link);
		list_del(&fan->link);
		wf_unरेजिस्टर_control(&fan->ctrl);
	पूर्ण
	kref_put(&pv->ref, wf_fcu_release);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wf_fcu_id[] = अणु
	अणु "MAC,fcu", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wf_fcu_id);

अटल स्थिर काष्ठा of_device_id wf_fcu_of_id[] = अणु
	अणु .compatible = "fcu", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wf_fcu_of_id);

अटल काष्ठा i2c_driver wf_fcu_driver = अणु
	.driver = अणु
		.name	= "wf_fcu",
		.of_match_table = wf_fcu_of_id,
	पूर्ण,
	.probe		= wf_fcu_probe,
	.हटाओ		= wf_fcu_हटाओ,
	.id_table	= wf_fcu_id,
पूर्ण;

module_i2c_driver(wf_fcu_driver);

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("FCU control objects for PowerMacs thermal control");
MODULE_LICENSE("GPL");

