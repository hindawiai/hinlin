<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "goyaP.h"

व्योम goya_set_pll_profile(काष्ठा hl_device *hdev, क्रमागत hl_pll_frequency freq)
अणु
	काष्ठा goya_device *goya = hdev->asic_specअगरic;

	चयन (freq) अणु
	हाल PLL_HIGH:
		hl_set_frequency(hdev, HL_GOYA_MME_PLL, hdev->high_pll);
		hl_set_frequency(hdev, HL_GOYA_TPC_PLL, hdev->high_pll);
		hl_set_frequency(hdev, HL_GOYA_IC_PLL, hdev->high_pll);
		अवरोध;
	हाल PLL_LOW:
		hl_set_frequency(hdev, HL_GOYA_MME_PLL, GOYA_PLL_FREQ_LOW);
		hl_set_frequency(hdev, HL_GOYA_TPC_PLL, GOYA_PLL_FREQ_LOW);
		hl_set_frequency(hdev, HL_GOYA_IC_PLL, GOYA_PLL_FREQ_LOW);
		अवरोध;
	हाल PLL_LAST:
		hl_set_frequency(hdev, HL_GOYA_MME_PLL, goya->mme_clk);
		hl_set_frequency(hdev, HL_GOYA_TPC_PLL, goya->tpc_clk);
		hl_set_frequency(hdev, HL_GOYA_IC_PLL, goya->ic_clk);
		अवरोध;
	शेष:
		dev_err(hdev->dev, "unknown frequency setting\n");
	पूर्ण
पूर्ण

पूर्णांक goya_get_clk_rate(काष्ठा hl_device *hdev, u32 *cur_clk, u32 *max_clk)
अणु
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	value = hl_get_frequency(hdev, HL_GOYA_MME_PLL, false);

	अगर (value < 0) अणु
		dev_err(hdev->dev, "Failed to retrieve device max clock %ld\n",
			value);
		वापस value;
	पूर्ण

	*max_clk = (value / 1000 / 1000);

	value = hl_get_frequency(hdev, HL_GOYA_MME_PLL, true);

	अगर (value < 0) अणु
		dev_err(hdev->dev,
			"Failed to retrieve device current clock %ld\n",
			value);
		वापस value;
	पूर्ण

	*cur_clk = (value / 1000 / 1000);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mme_clk_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	value = hl_get_frequency(hdev, HL_GOYA_MME_PLL, false);

	अगर (value < 0)
		वापस value;

	वापस प्र_लिखो(buf, "%lu\n", value);
पूर्ण

अटल sमाप_प्रकार mme_clk_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	पूर्णांक rc;
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य)) अणु
		count = -ENODEV;
		जाओ fail;
	पूर्ण

	अगर (hdev->pm_mng_profile == PM_AUTO) अणु
		count = -EPERM;
		जाओ fail;
	पूर्ण

	rc = kम_से_अदीर्घ(buf, 0, &value);

	अगर (rc) अणु
		count = -EINVAL;
		जाओ fail;
	पूर्ण

	hl_set_frequency(hdev, HL_GOYA_MME_PLL, value);
	goya->mme_clk = value;

fail:
	वापस count;
पूर्ण

अटल sमाप_प्रकार tpc_clk_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	value = hl_get_frequency(hdev, HL_GOYA_TPC_PLL, false);

	अगर (value < 0)
		वापस value;

	वापस प्र_लिखो(buf, "%lu\n", value);
पूर्ण

अटल sमाप_प्रकार tpc_clk_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	पूर्णांक rc;
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य)) अणु
		count = -ENODEV;
		जाओ fail;
	पूर्ण

	अगर (hdev->pm_mng_profile == PM_AUTO) अणु
		count = -EPERM;
		जाओ fail;
	पूर्ण

	rc = kम_से_अदीर्घ(buf, 0, &value);

	अगर (rc) अणु
		count = -EINVAL;
		जाओ fail;
	पूर्ण

	hl_set_frequency(hdev, HL_GOYA_TPC_PLL, value);
	goya->tpc_clk = value;

fail:
	वापस count;
पूर्ण

अटल sमाप_प्रकार ic_clk_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	value = hl_get_frequency(hdev, HL_GOYA_IC_PLL, false);

	अगर (value < 0)
		वापस value;

	वापस प्र_लिखो(buf, "%lu\n", value);
पूर्ण

अटल sमाप_प्रकार ic_clk_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	काष्ठा goya_device *goya = hdev->asic_specअगरic;
	पूर्णांक rc;
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य)) अणु
		count = -ENODEV;
		जाओ fail;
	पूर्ण

	अगर (hdev->pm_mng_profile == PM_AUTO) अणु
		count = -EPERM;
		जाओ fail;
	पूर्ण

	rc = kम_से_अदीर्घ(buf, 0, &value);

	अगर (rc) अणु
		count = -EINVAL;
		जाओ fail;
	पूर्ण

	hl_set_frequency(hdev, HL_GOYA_IC_PLL, value);
	goya->ic_clk = value;

fail:
	वापस count;
पूर्ण

अटल sमाप_प्रकार mme_clk_curr_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	value = hl_get_frequency(hdev, HL_GOYA_MME_PLL, true);

	अगर (value < 0)
		वापस value;

	वापस प्र_लिखो(buf, "%lu\n", value);
पूर्ण

अटल sमाप_प्रकार tpc_clk_curr_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	value = hl_get_frequency(hdev, HL_GOYA_TPC_PLL, true);

	अगर (value < 0)
		वापस value;

	वापस प्र_लिखो(buf, "%lu\n", value);
पूर्ण

अटल sमाप_प्रकार ic_clk_curr_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	दीर्घ value;

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	value = hl_get_frequency(hdev, HL_GOYA_IC_PLL, true);

	अगर (value < 0)
		वापस value;

	वापस प्र_लिखो(buf, "%lu\n", value);
पूर्ण

अटल sमाप_प्रकार pm_mng_profile_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%s\n",
			(hdev->pm_mng_profile == PM_AUTO) ? "auto" :
			(hdev->pm_mng_profile == PM_MANUAL) ? "manual" :
			"unknown");
पूर्ण

अटल sमाप_प्रकार pm_mng_profile_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	अगर (!hl_device_operational(hdev, शून्य)) अणु
		count = -ENODEV;
		जाओ out;
	पूर्ण

	mutex_lock(&hdev->fpriv_list_lock);

	अगर (hdev->compute_ctx) अणु
		dev_err(hdev->dev,
			"Can't change PM profile while compute context is opened on the device\n");
		count = -EPERM;
		जाओ unlock_mutex;
	पूर्ण

	अगर (म_भेदन("auto", buf, म_माप("auto")) == 0) अणु
		/* Make sure we are in LOW PLL when changing modes */
		अगर (hdev->pm_mng_profile == PM_MANUAL) अणु
			hdev->curr_pll_profile = PLL_HIGH;
			hdev->pm_mng_profile = PM_AUTO;
			hl_device_set_frequency(hdev, PLL_LOW);
		पूर्ण
	पूर्ण अन्यथा अगर (म_भेदन("manual", buf, म_माप("manual")) == 0) अणु
		अगर (hdev->pm_mng_profile == PM_AUTO) अणु
			/* Must release the lock because the work thपढ़ो also
			 * takes this lock. But beक्रमe we release it, set
			 * the mode to manual so nothing will change अगर a user
			 * suddenly खोलोs the device
			 */
			hdev->pm_mng_profile = PM_MANUAL;

			mutex_unlock(&hdev->fpriv_list_lock);

			/* Flush the current work so we can वापस to the user
			 * knowing that he is the only one changing frequencies
			 */
			flush_delayed_work(&hdev->work_freq);

			वापस count;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(hdev->dev, "value should be auto or manual\n");
		count = -EINVAL;
	पूर्ण

unlock_mutex:
	mutex_unlock(&hdev->fpriv_list_lock);
out:
	वापस count;
पूर्ण

अटल sमाप_प्रकार high_pll_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);

	अगर (!hl_device_operational(hdev, शून्य))
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%u\n", hdev->high_pll);
पूर्ण

अटल sमाप_प्रकार high_pll_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hl_device *hdev = dev_get_drvdata(dev);
	दीर्घ value;
	पूर्णांक rc;

	अगर (!hl_device_operational(hdev, शून्य)) अणु
		count = -ENODEV;
		जाओ out;
	पूर्ण

	rc = kम_से_अदीर्घ(buf, 0, &value);

	अगर (rc) अणु
		count = -EINVAL;
		जाओ out;
	पूर्ण

	hdev->high_pll = value;

out:
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(high_pll);
अटल DEVICE_ATTR_RW(ic_clk);
अटल DEVICE_ATTR_RO(ic_clk_curr);
अटल DEVICE_ATTR_RW(mme_clk);
अटल DEVICE_ATTR_RO(mme_clk_curr);
अटल DEVICE_ATTR_RW(pm_mng_profile);
अटल DEVICE_ATTR_RW(tpc_clk);
अटल DEVICE_ATTR_RO(tpc_clk_curr);

अटल काष्ठा attribute *goya_dev_attrs[] = अणु
	&dev_attr_high_pll.attr,
	&dev_attr_ic_clk.attr,
	&dev_attr_ic_clk_curr.attr,
	&dev_attr_mme_clk.attr,
	&dev_attr_mme_clk_curr.attr,
	&dev_attr_pm_mng_profile.attr,
	&dev_attr_tpc_clk.attr,
	&dev_attr_tpc_clk_curr.attr,
	शून्य,
पूर्ण;

व्योम goya_add_device_attr(काष्ठा hl_device *hdev,
			काष्ठा attribute_group *dev_attr_grp)
अणु
	dev_attr_grp->attrs = goya_dev_attrs;
पूर्ण
