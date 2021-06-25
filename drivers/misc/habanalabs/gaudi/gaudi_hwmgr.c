<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2018 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "gaudiP.h"
#समावेश "../include/gaudi/gaudi_fw_if.h"

व्योम gaudi_set_pll_profile(काष्ठा hl_device *hdev, क्रमागत hl_pll_frequency freq)
अणु
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;

	अगर (freq == PLL_LAST)
		hl_set_frequency(hdev, HL_GAUDI_MME_PLL, gaudi->max_freq_value);
पूर्ण

पूर्णांक gaudi_get_clk_rate(काष्ठा hl_device *hdev, u32 *cur_clk, u32 *max_clk)
अणु
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	value = hl_get_frequency(hdev, HL_GAUDI_MME_PLL, false);

	अगर (value < 0) अणु
		dev_err(hdev->dev, "Failed to retrieve device max clock %ld\n",
			value);
		वापस value;
	पूर्ण

	*max_clk = (value / 1000 / 1000);

	value = hl_get_frequency(hdev, HL_GAUDI_MME_PLL, true);

	अगर (value < 0) अणु
		dev_err(hdev->dev,
			"Failed to retrieve device current clock %ld\n",
			value);
		वापस value;
	पूर्ण

	*cur_clk = (value / 1000 / 1000);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार clk_max_freq_mhz_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	value = hl_get_frequency(hdev, HL_GAUDI_MME_PLL, false);

	gaudi->max_freq_value = value;

	वापस प्र_लिखो(buf, "%lu\n", (value / 1000 / 1000));
पूर्ण

अटल sमाप_प्रकार clk_max_freq_mhz_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	काष्ठा gaudi_device *gaudi = hdev->asic_specअगरic;
	पूर्णांक rc;
	u64 value;

	अगर (!hl_device_operational(hdev, शून्य)) अणु
		count = -ENODEV;
		जाओ fail;
	पूर्ण

	rc = kम_से_अदीर्घl(buf, 0, &value);
	अगर (rc) अणु
		count = -EINVAL;
		जाओ fail;
	पूर्ण

	gaudi->max_freq_value = value * 1000 * 1000;

	hl_set_frequency(hdev, HL_GAUDI_MME_PLL, gaudi->max_freq_value);

fail:
	वापस count;
पूर्ण

अटल sमाप_प्रकार clk_cur_freq_mhz_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	value = hl_get_frequency(hdev, HL_GAUDI_MME_PLL, true);

	वापस प्र_लिखो(buf, "%lu\n", (value / 1000 / 1000));
पूर्ण

अटल DEVICE_ATTR_RW(clk_max_freq_mhz);
अटल DEVICE_ATTR_RO(clk_cur_freq_mhz);

अटल काष्ठा attribute *gaudi_dev_attrs[] = अणु
	&dev_attr_clk_max_freq_mhz.attr,
	&dev_attr_clk_cur_freq_mhz.attr,
	शून्य,
पूर्ण;

व्योम gaudi_add_device_attr(काष्ठा hl_device *hdev,
			काष्ठा attribute_group *dev_attr_grp)
अणु
	dev_attr_grp->attrs = gaudi_dev_attrs;
पूर्ण
