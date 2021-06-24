<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ultra45_env.c: Driver क्रम Ultra45 PIC16F747 environmental monitor.
 *
 * Copyright (C) 2008 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>

#घोषणा DRV_MODULE_VERSION	"0.1"

MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_DESCRIPTION("Ultra45 environmental monitor driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

/* PIC device रेजिस्टरs */
#घोषणा REG_CMD		0x00UL
#घोषणा  REG_CMD_RESET	0x80
#घोषणा  REG_CMD_ESTAR	0x01
#घोषणा REG_STAT	0x01UL
#घोषणा  REG_STAT_FWVER	0xf0
#घोषणा  REG_STAT_TGOOD	0x08
#घोषणा  REG_STAT_STALE	0x04
#घोषणा  REG_STAT_BUSY	0x02
#घोषणा  REG_STAT_FAULT	0x01
#घोषणा REG_DATA	0x40UL
#घोषणा REG_ADDR	0x41UL
#घोषणा REG_SIZE	0x42UL

/* Registers accessed indirectly via REG_DATA/REG_ADDR */
#घोषणा IREG_FAN0		0x00
#घोषणा IREG_FAN1		0x01
#घोषणा IREG_FAN2		0x02
#घोषणा IREG_FAN3		0x03
#घोषणा IREG_FAN4		0x04
#घोषणा IREG_FAN5		0x05
#घोषणा IREG_LCL_TEMP		0x06
#घोषणा IREG_RMT1_TEMP		0x07
#घोषणा IREG_RMT2_TEMP		0x08
#घोषणा IREG_RMT3_TEMP		0x09
#घोषणा IREG_LM95221_TEMP	0x0a
#घोषणा IREG_FIRE_TEMP		0x0b
#घोषणा IREG_LSI1064_TEMP	0x0c
#घोषणा IREG_FRONT_TEMP		0x0d
#घोषणा IREG_FAN_STAT		0x0e
#घोषणा IREG_VCORE0		0x0f
#घोषणा IREG_VCORE1		0x10
#घोषणा IREG_VMEM0		0x11
#घोषणा IREG_VMEM1		0x12
#घोषणा IREG_PSU_TEMP		0x13

काष्ठा env अणु
	व्योम __iomem	*regs;
	spinlock_t	lock;

	काष्ठा device	*hwmon_dev;
पूर्ण;

अटल u8 env_पढ़ो(काष्ठा env *p, u8 ireg)
अणु
	u8 ret;

	spin_lock(&p->lock);
	ग_लिखोb(ireg, p->regs + REG_ADDR);
	ret = पढ़ोb(p->regs + REG_DATA);
	spin_unlock(&p->lock);

	वापस ret;
पूर्ण

अटल व्योम env_ग_लिखो(काष्ठा env *p, u8 ireg, u8 val)
अणु
	spin_lock(&p->lock);
	ग_लिखोb(ireg, p->regs + REG_ADDR);
	ग_लिखोb(val, p->regs + REG_DATA);
	spin_unlock(&p->lock);
पूर्ण

/*
 * There seems to be a adr7462 providing these values, thus a lot
 * of these calculations are borrowed from the adt7470 driver.
 */
#घोषणा FAN_PERIOD_TO_RPM(x)	((90000 * 60) / (x))
#घोषणा FAN_RPM_TO_PERIOD	FAN_PERIOD_TO_RPM
#घोषणा FAN_PERIOD_INVALID	(0xff << 8)
#घोषणा FAN_DATA_VALID(x)	((x) && (x) != FAN_PERIOD_INVALID)

अटल sमाप_प्रकार show_fan_speed(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	पूर्णांक fan_nr = to_sensor_dev_attr(attr)->index;
	काष्ठा env *p = dev_get_drvdata(dev);
	पूर्णांक rpm, period;
	u8 val;

	val = env_पढ़ो(p, IREG_FAN0 + fan_nr);
	period = (पूर्णांक) val << 8;
	अगर (FAN_DATA_VALID(period))
		rpm = FAN_PERIOD_TO_RPM(period);
	अन्यथा
		rpm = 0;

	वापस प्र_लिखो(buf, "%d\n", rpm);
पूर्ण

अटल sमाप_प्रकार set_fan_speed(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक fan_nr = to_sensor_dev_attr(attr)->index;
	अचिन्हित दीर्घ rpm;
	काष्ठा env *p = dev_get_drvdata(dev);
	पूर्णांक period;
	u8 val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &rpm);
	अगर (err)
		वापस err;

	अगर (!rpm)
		वापस -EINVAL;

	period = FAN_RPM_TO_PERIOD(rpm);
	val = period >> 8;
	env_ग_लिखो(p, IREG_FAN0 + fan_nr, val);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_fan_fault(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	पूर्णांक fan_nr = to_sensor_dev_attr(attr)->index;
	काष्ठा env *p = dev_get_drvdata(dev);
	u8 val = env_पढ़ो(p, IREG_FAN_STAT);
	वापस प्र_लिखो(buf, "%d\n", (val & (1 << fan_nr)) ? 1 : 0);
पूर्ण

#घोषणा fan(index)							\
अटल SENSOR_DEVICE_ATTR(fan##index##_speed, S_IRUGO | S_IWUSR,	\
		show_fan_speed, set_fan_speed, index);			\
अटल SENSOR_DEVICE_ATTR(fan##index##_fault, S_IRUGO,			\
		show_fan_fault, शून्य, index)

fan(0);
fan(1);
fan(2);
fan(3);
fan(4);

अटल SENSOR_DEVICE_ATTR(psu_fan_fault, S_IRUGO, show_fan_fault, शून्य, 6);

अटल sमाप_प्रकार show_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	पूर्णांक temp_nr = to_sensor_dev_attr(attr)->index;
	काष्ठा env *p = dev_get_drvdata(dev);
	s8 val;

	val = env_पढ़ो(p, IREG_LCL_TEMP + temp_nr);
	वापस प्र_लिखो(buf, "%d\n", ((पूर्णांक) val) - 64);
पूर्ण

अटल SENSOR_DEVICE_ATTR(adt7462_local_temp, S_IRUGO, show_temp, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(cpu0_temp, S_IRUGO, show_temp, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(cpu1_temp, S_IRUGO, show_temp, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(motherboard_temp, S_IRUGO, show_temp, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(lm95221_local_temp, S_IRUGO, show_temp, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(fire_temp, S_IRUGO, show_temp, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(lsi1064_local_temp, S_IRUGO, show_temp, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(front_panel_temp, S_IRUGO, show_temp, शून्य, 7);
अटल SENSOR_DEVICE_ATTR(psu_temp, S_IRUGO, show_temp, शून्य, 13);

अटल sमाप_प्रकार show_stat_bit(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा env *p = dev_get_drvdata(dev);
	u8 val;

	val = पढ़ोb(p->regs + REG_STAT);
	वापस प्र_लिखो(buf, "%d\n", (val & (1 << index)) ? 1 : 0);
पूर्ण

अटल SENSOR_DEVICE_ATTR(fan_failure, S_IRUGO, show_stat_bit, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(env_bus_busy, S_IRUGO, show_stat_bit, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(env_data_stale, S_IRUGO, show_stat_bit, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(tpm_self_test_passed, S_IRUGO, show_stat_bit, शून्य,
			  3);

अटल sमाप_प्रकार show_fwver(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा env *p = dev_get_drvdata(dev);
	u8 val;

	val = पढ़ोb(p->regs + REG_STAT);
	वापस प्र_लिखो(buf, "%d\n", val >> 4);
पूर्ण

अटल SENSOR_DEVICE_ATTR(firmware_version, S_IRUGO, show_fwver, शून्य, 0);

अटल sमाप_प्रकार show_name(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "ultra45\n");
पूर्ण

अटल SENSOR_DEVICE_ATTR(name, S_IRUGO, show_name, शून्य, 0);

अटल काष्ठा attribute *env_attributes[] = अणु
	&sensor_dev_attr_fan0_speed.dev_attr.attr,
	&sensor_dev_attr_fan0_fault.dev_attr.attr,
	&sensor_dev_attr_fan1_speed.dev_attr.attr,
	&sensor_dev_attr_fan1_fault.dev_attr.attr,
	&sensor_dev_attr_fan2_speed.dev_attr.attr,
	&sensor_dev_attr_fan2_fault.dev_attr.attr,
	&sensor_dev_attr_fan3_speed.dev_attr.attr,
	&sensor_dev_attr_fan3_fault.dev_attr.attr,
	&sensor_dev_attr_fan4_speed.dev_attr.attr,
	&sensor_dev_attr_fan4_fault.dev_attr.attr,
	&sensor_dev_attr_psu_fan_fault.dev_attr.attr,
	&sensor_dev_attr_adt7462_local_temp.dev_attr.attr,
	&sensor_dev_attr_cpu0_temp.dev_attr.attr,
	&sensor_dev_attr_cpu1_temp.dev_attr.attr,
	&sensor_dev_attr_motherboard_temp.dev_attr.attr,
	&sensor_dev_attr_lm95221_local_temp.dev_attr.attr,
	&sensor_dev_attr_fire_temp.dev_attr.attr,
	&sensor_dev_attr_lsi1064_local_temp.dev_attr.attr,
	&sensor_dev_attr_front_panel_temp.dev_attr.attr,
	&sensor_dev_attr_psu_temp.dev_attr.attr,
	&sensor_dev_attr_fan_failure.dev_attr.attr,
	&sensor_dev_attr_env_bus_busy.dev_attr.attr,
	&sensor_dev_attr_env_data_stale.dev_attr.attr,
	&sensor_dev_attr_tpm_self_test_passed.dev_attr.attr,
	&sensor_dev_attr_firmware_version.dev_attr.attr,
	&sensor_dev_attr_name.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group env_group = अणु
	.attrs = env_attributes,
पूर्ण;

अटल पूर्णांक env_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा env *p = devm_kzalloc(&op->dev, माप(*p), GFP_KERNEL);
	पूर्णांक err = -ENOMEM;

	अगर (!p)
		जाओ out;

	spin_lock_init(&p->lock);

	p->regs = of_ioremap(&op->resource[0], 0, REG_SIZE, "pic16f747");
	अगर (!p->regs)
		जाओ out;

	err = sysfs_create_group(&op->dev.kobj, &env_group);
	अगर (err)
		जाओ out_iounmap;

	p->hwmon_dev = hwmon_device_रेजिस्टर(&op->dev);
	अगर (IS_ERR(p->hwmon_dev)) अणु
		err = PTR_ERR(p->hwmon_dev);
		जाओ out_sysfs_हटाओ_group;
	पूर्ण

	platक्रमm_set_drvdata(op, p);
	err = 0;

out:
	वापस err;

out_sysfs_हटाओ_group:
	sysfs_हटाओ_group(&op->dev.kobj, &env_group);

out_iounmap:
	of_iounmap(&op->resource[0], p->regs, REG_SIZE);

	जाओ out;
पूर्ण

अटल पूर्णांक env_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा env *p = platक्रमm_get_drvdata(op);

	अगर (p) अणु
		sysfs_हटाओ_group(&op->dev.kobj, &env_group);
		hwmon_device_unरेजिस्टर(p->hwmon_dev);
		of_iounmap(&op->resource[0], p->regs, REG_SIZE);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id env_match[] = अणु
	अणु
		.name = "env-monitor",
		.compatible = "SUNW,ebus-pic16f747-env",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, env_match);

अटल काष्ठा platक्रमm_driver env_driver = अणु
	.driver = अणु
		.name = "ultra45_env",
		.of_match_table = env_match,
	पूर्ण,
	.probe		= env_probe,
	.हटाओ		= env_हटाओ,
पूर्ण;

module_platक्रमm_driver(env_driver);
