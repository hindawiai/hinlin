<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DFL device driver क्रम EMIF निजी feature
 *
 * Copyright (C) 2020 Intel Corporation, Inc.
 *
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/dfl.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#घोषणा FME_FEATURE_ID_EMIF		0x9

#घोषणा EMIF_STAT			0x8
#घोषणा EMIF_STAT_INIT_DONE_SFT		0
#घोषणा EMIF_STAT_CALC_FAIL_SFT		8
#घोषणा EMIF_STAT_CLEAR_BUSY_SFT	16
#घोषणा EMIF_CTRL			0x10
#घोषणा EMIF_CTRL_CLEAR_EN_SFT		0
#घोषणा EMIF_CTRL_CLEAR_EN_MSK		GENMASK_ULL(3, 0)

#घोषणा EMIF_POLL_INVL			10000 /* us */
#घोषणा EMIF_POLL_TIMEOUT		5000000 /* us */

काष्ठा dfl_emअगर अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	spinlock_t lock;	/* Serialises access to EMIF_CTRL reg */
पूर्ण;

काष्ठा emअगर_attr अणु
	काष्ठा device_attribute attr;
	u32 shअगरt;
	u32 index;
पूर्ण;

#घोषणा to_emअगर_attr(dev_attr) \
	container_of(dev_attr, काष्ठा emअगर_attr, attr)

अटल sमाप_प्रकार emअगर_state_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा emअगर_attr *eattr = to_emअगर_attr(attr);
	काष्ठा dfl_emअगर *de = dev_get_drvdata(dev);
	u64 val;

	val = पढ़ोq(de->base + EMIF_STAT);

	वापस sysfs_emit(buf, "%u\n",
			  !!(val & BIT_ULL(eattr->shअगरt + eattr->index)));
पूर्ण

अटल sमाप_प्रकार emअगर_clear_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा emअगर_attr *eattr = to_emअगर_attr(attr);
	काष्ठा dfl_emअगर *de = dev_get_drvdata(dev);
	u64 clear_busy_msk, clear_en_msk, val;
	व्योम __iomem *base = de->base;

	अगर (!sysfs_streq(buf, "1"))
		वापस -EINVAL;

	clear_busy_msk = BIT_ULL(EMIF_STAT_CLEAR_BUSY_SFT + eattr->index);
	clear_en_msk = BIT_ULL(EMIF_CTRL_CLEAR_EN_SFT + eattr->index);

	spin_lock(&de->lock);
	/* The CLEAR_EN field is WO, but other fields are RW */
	val = पढ़ोq(base + EMIF_CTRL);
	val &= ~EMIF_CTRL_CLEAR_EN_MSK;
	val |= clear_en_msk;
	ग_लिखोq(val, base + EMIF_CTRL);
	spin_unlock(&de->lock);

	अगर (पढ़ोq_poll_समयout(base + EMIF_STAT, val,
			       !(val & clear_busy_msk),
			       EMIF_POLL_INVL, EMIF_POLL_TIMEOUT)) अणु
		dev_err(de->dev, "timeout, fail to clear\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस count;
पूर्ण

#घोषणा emअगर_state_attr(_name, _shअगरt, _index)				\
	अटल काष्ठा emअगर_attr emअगर_attr_##inf##_index##_##_name =	\
		अणु .attr = __ATTR(inf##_index##_##_name, 0444,		\
				 emअगर_state_show, शून्य),		\
		  .shअगरt = (_shअगरt), .index = (_index) पूर्ण

#घोषणा emअगर_clear_attr(_index)						\
	अटल काष्ठा emअगर_attr emअगर_attr_##inf##_index##_clear =	\
		अणु .attr = __ATTR(inf##_index##_clear, 0200,		\
				 शून्य, emअगर_clear_store),		\
		  .index = (_index) पूर्ण

emअगर_state_attr(init_करोne, EMIF_STAT_INIT_DONE_SFT, 0);
emअगर_state_attr(init_करोne, EMIF_STAT_INIT_DONE_SFT, 1);
emअगर_state_attr(init_करोne, EMIF_STAT_INIT_DONE_SFT, 2);
emअगर_state_attr(init_करोne, EMIF_STAT_INIT_DONE_SFT, 3);

emअगर_state_attr(cal_fail, EMIF_STAT_CALC_FAIL_SFT, 0);
emअगर_state_attr(cal_fail, EMIF_STAT_CALC_FAIL_SFT, 1);
emअगर_state_attr(cal_fail, EMIF_STAT_CALC_FAIL_SFT, 2);
emअगर_state_attr(cal_fail, EMIF_STAT_CALC_FAIL_SFT, 3);

emअगर_clear_attr(0);
emअगर_clear_attr(1);
emअगर_clear_attr(2);
emअगर_clear_attr(3);

अटल काष्ठा attribute *dfl_emअगर_attrs[] = अणु
	&emअगर_attr_inf0_init_करोne.attr.attr,
	&emअगर_attr_inf0_cal_fail.attr.attr,
	&emअगर_attr_inf0_clear.attr.attr,

	&emअगर_attr_inf1_init_करोne.attr.attr,
	&emअगर_attr_inf1_cal_fail.attr.attr,
	&emअगर_attr_inf1_clear.attr.attr,

	&emअगर_attr_inf2_init_करोne.attr.attr,
	&emअगर_attr_inf2_cal_fail.attr.attr,
	&emअगर_attr_inf2_clear.attr.attr,

	&emअगर_attr_inf3_init_करोne.attr.attr,
	&emअगर_attr_inf3_cal_fail.attr.attr,
	&emअगर_attr_inf3_clear.attr.attr,

	शून्य,
पूर्ण;

अटल umode_t dfl_emअगर_visible(काष्ठा kobject *kobj,
				काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा dfl_emअगर *de = dev_get_drvdata(kobj_to_dev(kobj));
	काष्ठा emअगर_attr *eattr = container_of(attr, काष्ठा emअगर_attr,
					       attr.attr);
	u64 val;

	/*
	 * This device supports upto 4 memory पूर्णांकerfaces, but not all
	 * पूर्णांकerfaces are used on dअगरferent platक्रमms. The पढ़ो out value of
	 * CLEAN_EN field (which is a biपंचांगap) could tell how many पूर्णांकerfaces
	 * are available.
	 */
	val = FIELD_GET(EMIF_CTRL_CLEAR_EN_MSK, पढ़ोq(de->base + EMIF_CTRL));

	वापस (val & BIT_ULL(eattr->index)) ? attr->mode : 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group dfl_emअगर_group = अणु
	.is_visible = dfl_emअगर_visible,
	.attrs = dfl_emअगर_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *dfl_emअगर_groups[] = अणु
	&dfl_emअगर_group,
	शून्य,
पूर्ण;

अटल पूर्णांक dfl_emअगर_probe(काष्ठा dfl_device *ddev)
अणु
	काष्ठा device *dev = &ddev->dev;
	काष्ठा dfl_emअगर *de;

	de = devm_kzalloc(dev, माप(*de), GFP_KERNEL);
	अगर (!de)
		वापस -ENOMEM;

	de->base = devm_ioremap_resource(dev, &ddev->mmio_res);
	अगर (IS_ERR(de->base))
		वापस PTR_ERR(de->base);

	de->dev = dev;
	spin_lock_init(&de->lock);
	dev_set_drvdata(dev, de);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dfl_device_id dfl_emअगर_ids[] = अणु
	अणु FME_ID, FME_FEATURE_ID_EMIF पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dfl, dfl_emअगर_ids);

अटल काष्ठा dfl_driver dfl_emअगर_driver = अणु
	.drv	= अणु
		.name       = "dfl-emif",
		.dev_groups = dfl_emअगर_groups,
	पूर्ण,
	.id_table = dfl_emअगर_ids,
	.probe   = dfl_emअगर_probe,
पूर्ण;
module_dfl_driver(dfl_emअगर_driver);

MODULE_DESCRIPTION("DFL EMIF driver");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
