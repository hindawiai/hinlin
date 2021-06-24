<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * thermal support क्रम the cell processor
 *
 * This module adds some sysfs attributes to cpu and spu nodes.
 * Base क्रम measurements are the digital thermal sensors (DTS)
 * located on the chip.
 * The accuracy is 2 degrees, starting from 65 up to 125 degrees celsius
 * The attributes can be found under
 * /sys/devices/प्रणाली/cpu/cpuX/thermal
 * /sys/devices/प्रणाली/spu/spuX/thermal
 *
 * The following attributes are added क्रम each node:
 * temperature:
 *	contains the current temperature measured by the DTS
 * throttle_begin:
 *	throttling begins when temperature is greater or equal to
 *	throttle_begin. Setting this value to 125 prevents throttling.
 * throttle_end:
 *	throttling is being ceased, अगर the temperature is lower than
 *	throttle_end. Due to a delay between applying throttling and
 *	a reduced temperature this value should be less than throttle_begin.
 *	A value equal to throttle_begin provides only a very little hysteresis.
 * throttle_full_stop:
 *	If the temperatrue is greater or equal to throttle_full_stop,
 *	full throttling is applied to the cpu or spu. This value should be
 *	greater than throttle_begin and throttle_end. Setting this value to
 *	65 prevents the unit from running code at all.
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * Author: Christian Krafft <krafft@de.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/cpu.h>
#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/cell-regs.h>

#समावेश "spu_priv1_mmio.h"

#घोषणा TEMP_MIN 65
#घोषणा TEMP_MAX 125

#घोषणा DEVICE_PREFIX_ATTR(_prefix,_name,_mode)			\
काष्ठा device_attribute attr_ ## _prefix ## _ ## _name = अणु	\
	.attr = अणु .name = __stringअगरy(_name), .mode = _mode पूर्ण,	\
	.show	= _prefix ## _show_ ## _name,			\
	.store	= _prefix ## _store_ ## _name,			\
पूर्ण;

अटल अंतरभूत u8 reg_to_temp(u8 reg_value)
अणु
	वापस ((reg_value & 0x3f) << 1) + TEMP_MIN;
पूर्ण

अटल अंतरभूत u8 temp_to_reg(u8 temp)
अणु
	वापस ((temp - TEMP_MIN) >> 1) & 0x3f;
पूर्ण

अटल काष्ठा cbe_pmd_regs __iomem *get_pmd_regs(काष्ठा device *dev)
अणु
	काष्ठा spu *spu;

	spu = container_of(dev, काष्ठा spu, dev);

	वापस cbe_get_pmd_regs(spu_devnode(spu));
पूर्ण

/* वापसs the value क्रम a given spu in a given रेजिस्टर */
अटल u8 spu_पढ़ो_रेजिस्टर_value(काष्ठा device *dev, जोड़ spe_reg __iomem *reg)
अणु
	जोड़ spe_reg value;
	काष्ठा spu *spu;

	spu = container_of(dev, काष्ठा spu, dev);
	value.val = in_be64(&reg->val);

	वापस value.spe[spu->spe_id];
पूर्ण

अटल sमाप_प्रकार spu_show_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	u8 value;
	काष्ठा cbe_pmd_regs __iomem *pmd_regs;

	pmd_regs = get_pmd_regs(dev);

	value = spu_पढ़ो_रेजिस्टर_value(dev, &pmd_regs->ts_ctsr1);

	वापस प्र_लिखो(buf, "%d\n", reg_to_temp(value));
पूर्ण

अटल sमाप_प्रकार show_throttle(काष्ठा cbe_pmd_regs __iomem *pmd_regs, अक्षर *buf, पूर्णांक pos)
अणु
	u64 value;

	value = in_be64(&pmd_regs->पंचांग_tpr.val);
	/* access the corresponding byte */
	value >>= pos;
	value &= 0x3F;

	वापस प्र_लिखो(buf, "%d\n", reg_to_temp(value));
पूर्ण

अटल sमाप_प्रकार store_throttle(काष्ठा cbe_pmd_regs __iomem *pmd_regs, स्थिर अक्षर *buf, माप_प्रकार size, पूर्णांक pos)
अणु
	u64 reg_value;
	अचिन्हित पूर्णांक temp;
	u64 new_value;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%u", &temp);

	अगर (ret != 1 || temp < TEMP_MIN || temp > TEMP_MAX)
		वापस -EINVAL;

	new_value = temp_to_reg(temp);

	reg_value = in_be64(&pmd_regs->पंचांग_tpr.val);

	/* zero out bits क्रम new value */
	reg_value &= ~(0xffull << pos);
	/* set bits to new value */
	reg_value |= new_value << pos;

	out_be64(&pmd_regs->पंचांग_tpr.val, reg_value);
	वापस size;
पूर्ण

अटल sमाप_प्रकार spu_show_throttle_end(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस show_throttle(get_pmd_regs(dev), buf, 0);
पूर्ण

अटल sमाप_प्रकार spu_show_throttle_begin(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस show_throttle(get_pmd_regs(dev), buf, 8);
पूर्ण

अटल sमाप_प्रकार spu_show_throttle_full_stop(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस show_throttle(get_pmd_regs(dev), buf, 16);
पूर्ण

अटल sमाप_प्रकार spu_store_throttle_end(काष्ठा device *dev,
			काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस store_throttle(get_pmd_regs(dev), buf, size, 0);
पूर्ण

अटल sमाप_प्रकार spu_store_throttle_begin(काष्ठा device *dev,
			काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस store_throttle(get_pmd_regs(dev), buf, size, 8);
पूर्ण

अटल sमाप_प्रकार spu_store_throttle_full_stop(काष्ठा device *dev,
			काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस store_throttle(get_pmd_regs(dev), buf, size, 16);
पूर्ण

अटल sमाप_प्रकार ppe_show_temp(काष्ठा device *dev, अक्षर *buf, पूर्णांक pos)
अणु
	काष्ठा cbe_pmd_regs __iomem *pmd_regs;
	u64 value;

	pmd_regs = cbe_get_cpu_pmd_regs(dev->id);
	value = in_be64(&pmd_regs->ts_ctsr2);

	value = (value >> pos) & 0x3f;

	वापस प्र_लिखो(buf, "%d\n", reg_to_temp(value));
पूर्ण


/* shows the temperature of the DTS on the PPE,
 * located near the linear thermal sensor */
अटल sमाप_प्रकार ppe_show_temp0(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस ppe_show_temp(dev, buf, 32);
पूर्ण

/* shows the temperature of the second DTS on the PPE */
अटल sमाप_प्रकार ppe_show_temp1(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस ppe_show_temp(dev, buf, 0);
पूर्ण

अटल sमाप_प्रकार ppe_show_throttle_end(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस show_throttle(cbe_get_cpu_pmd_regs(dev->id), buf, 32);
पूर्ण

अटल sमाप_प्रकार ppe_show_throttle_begin(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस show_throttle(cbe_get_cpu_pmd_regs(dev->id), buf, 40);
पूर्ण

अटल sमाप_प्रकार ppe_show_throttle_full_stop(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस show_throttle(cbe_get_cpu_pmd_regs(dev->id), buf, 48);
पूर्ण

अटल sमाप_प्रकार ppe_store_throttle_end(काष्ठा device *dev,
			काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस store_throttle(cbe_get_cpu_pmd_regs(dev->id), buf, size, 32);
पूर्ण

अटल sमाप_प्रकार ppe_store_throttle_begin(काष्ठा device *dev,
			काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस store_throttle(cbe_get_cpu_pmd_regs(dev->id), buf, size, 40);
पूर्ण

अटल sमाप_प्रकार ppe_store_throttle_full_stop(काष्ठा device *dev,
			काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस store_throttle(cbe_get_cpu_pmd_regs(dev->id), buf, size, 48);
पूर्ण


अटल काष्ठा device_attribute attr_spu_temperature = अणु
	.attr = अणु.name = "temperature", .mode = 0400 पूर्ण,
	.show = spu_show_temp,
पूर्ण;

अटल DEVICE_PREFIX_ATTR(spu, throttle_end, 0600);
अटल DEVICE_PREFIX_ATTR(spu, throttle_begin, 0600);
अटल DEVICE_PREFIX_ATTR(spu, throttle_full_stop, 0600);


अटल काष्ठा attribute *spu_attributes[] = अणु
	&attr_spu_temperature.attr,
	&attr_spu_throttle_end.attr,
	&attr_spu_throttle_begin.attr,
	&attr_spu_throttle_full_stop.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group spu_attribute_group = अणु
	.name	= "thermal",
	.attrs	= spu_attributes,
पूर्ण;

अटल काष्ठा device_attribute attr_ppe_temperature0 = अणु
	.attr = अणु.name = "temperature0", .mode = 0400 पूर्ण,
	.show = ppe_show_temp0,
पूर्ण;

अटल काष्ठा device_attribute attr_ppe_temperature1 = अणु
	.attr = अणु.name = "temperature1", .mode = 0400 पूर्ण,
	.show = ppe_show_temp1,
पूर्ण;

अटल DEVICE_PREFIX_ATTR(ppe, throttle_end, 0600);
अटल DEVICE_PREFIX_ATTR(ppe, throttle_begin, 0600);
अटल DEVICE_PREFIX_ATTR(ppe, throttle_full_stop, 0600);

अटल काष्ठा attribute *ppe_attributes[] = अणु
	&attr_ppe_temperature0.attr,
	&attr_ppe_temperature1.attr,
	&attr_ppe_throttle_end.attr,
	&attr_ppe_throttle_begin.attr,
	&attr_ppe_throttle_full_stop.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group ppe_attribute_group = अणु
	.name	= "thermal",
	.attrs	= ppe_attributes,
पूर्ण;

/*
 * initialize throttling with शेष values
 */
अटल पूर्णांक __init init_शेष_values(व्योम)
अणु
	पूर्णांक cpu;
	काष्ठा cbe_pmd_regs __iomem *pmd_regs;
	काष्ठा device *dev;
	जोड़ ppe_spe_reg tpr;
	जोड़ spe_reg str1;
	u64 str2;
	जोड़ spe_reg cr1;
	u64 cr2;

	/* TPR शेषs */
	/* ppe
	 *	1F - no full stop
	 *	08 - dynamic throttling starts अगर over 80 degrees
	 *	03 - dynamic throttling ceases अगर below 70 degrees */
	tpr.ppe = 0x1F0803;
	/* spe
	 *	10 - full stopped when over 96 degrees
	 *	08 - dynamic throttling starts अगर over 80 degrees
	 *	03 - dynamic throttling ceases अगर below 70 degrees
	 */
	tpr.spe = 0x100803;

	/* STR शेषs */
	/* str1
	 *	10 - stop 16 of 32 cycles
	 */
	str1.val = 0x1010101010101010ull;
	/* str2
	 *	10 - stop 16 of 32 cycles
	 */
	str2 = 0x10;

	/* CR शेषs */
	/* cr1
	 *	4 - normal operation
	 */
	cr1.val = 0x0404040404040404ull;
	/* cr2
	 *	4 - normal operation
	 */
	cr2 = 0x04;

	क्रम_each_possible_cpu (cpu) अणु
		pr_debug("processing cpu %d\n", cpu);
		dev = get_cpu_device(cpu);

		अगर (!dev) अणु
			pr_info("invalid dev pointer for cbe_thermal\n");
			वापस -EINVAL;
		पूर्ण

		pmd_regs = cbe_get_cpu_pmd_regs(dev->id);

		अगर (!pmd_regs) अणु
			pr_info("invalid CBE regs pointer for cbe_thermal\n");
			वापस -EINVAL;
		पूर्ण

		out_be64(&pmd_regs->पंचांग_str2, str2);
		out_be64(&pmd_regs->पंचांग_str1.val, str1.val);
		out_be64(&pmd_regs->पंचांग_tpr.val, tpr.val);
		out_be64(&pmd_regs->पंचांग_cr1.val, cr1.val);
		out_be64(&pmd_regs->पंचांग_cr2, cr2);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक __init thermal_init(व्योम)
अणु
	पूर्णांक rc = init_शेष_values();

	अगर (rc == 0) अणु
		spu_add_dev_attr_group(&spu_attribute_group);
		cpu_add_dev_attr_group(&ppe_attribute_group);
	पूर्ण

	वापस rc;
पूर्ण
module_init(thermal_init);

अटल व्योम __निकास thermal_निकास(व्योम)
अणु
	spu_हटाओ_dev_attr_group(&spu_attribute_group);
	cpu_हटाओ_dev_attr_group(&ppe_attribute_group);
पूर्ण
module_निकास(thermal_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Krafft <krafft@de.ibm.com>");

