<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(C) 2015 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#समावेश <linux/pid_namespace.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sysfs.h>
#समावेश "coresight-etm.h"
#समावेश "coresight-priv.h"

अटल sमाप_प्रकार nr_addr_cmp_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->nr_addr_cmp;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(nr_addr_cmp);

अटल sमाप_प्रकार nr_cntr_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->nr_cntr;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(nr_cntr);

अटल sमाप_प्रकार nr_ctxid_cmp_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->nr_ctxid_cmp;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(nr_ctxid_cmp);

अटल sमाप_प्रकार eपंचांगsr_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ flags, val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);

	pm_runसमय_get_sync(dev->parent);
	spin_lock_irqsave(&drvdata->spinlock, flags);
	CS_UNLOCK(drvdata->base);

	val = eपंचांग_पढ़ोl(drvdata, ETMSR);

	CS_LOCK(drvdata->base);
	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	pm_runसमय_put(dev->parent);

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(eपंचांगsr);

अटल sमाप_प्रकार reset_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक i, ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	अगर (val) अणु
		spin_lock(&drvdata->spinlock);
		स_रखो(config, 0, माप(काष्ठा eपंचांग_config));
		config->mode = ETM_MODE_EXCLUDE;
		config->trigger_event = ETM_DEFAULT_EVENT_VAL;
		क्रम (i = 0; i < drvdata->nr_addr_cmp; i++) अणु
			config->addr_type[i] = ETM_ADDR_TYPE_NONE;
		पूर्ण

		eपंचांग_set_शेष(config);
		spin_unlock(&drvdata->spinlock);
	पूर्ण

	वापस size;
पूर्ण
अटल DEVICE_ATTR_WO(reset);

अटल sमाप_प्रकार mode_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->mode;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार mode_store(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	spin_lock(&drvdata->spinlock);
	config->mode = val & ETM_MODE_ALL;

	अगर (config->mode & ETM_MODE_EXCLUDE)
		config->enable_ctrl1 |= ETMTECR1_INC_EXC;
	अन्यथा
		config->enable_ctrl1 &= ~ETMTECR1_INC_EXC;

	अगर (config->mode & ETM_MODE_CYCACC)
		config->ctrl |= ETMCR_CYC_ACC;
	अन्यथा
		config->ctrl &= ~ETMCR_CYC_ACC;

	अगर (config->mode & ETM_MODE_STALL) अणु
		अगर (!(drvdata->eपंचांगccr & ETMCCR_FIFOFULL)) अणु
			dev_warn(dev, "stall mode not supported\n");
			ret = -EINVAL;
			जाओ err_unlock;
		पूर्ण
		config->ctrl |= ETMCR_STALL_MODE;
	पूर्ण अन्यथा
		config->ctrl &= ~ETMCR_STALL_MODE;

	अगर (config->mode & ETM_MODE_TIMESTAMP) अणु
		अगर (!(drvdata->eपंचांगccer & ETMCCER_TIMESTAMP)) अणु
			dev_warn(dev, "timestamp not supported\n");
			ret = -EINVAL;
			जाओ err_unlock;
		पूर्ण
		config->ctrl |= ETMCR_TIMESTAMP_EN;
	पूर्ण अन्यथा
		config->ctrl &= ~ETMCR_TIMESTAMP_EN;

	अगर (config->mode & ETM_MODE_CTXID)
		config->ctrl |= ETMCR_CTXID_SIZE;
	अन्यथा
		config->ctrl &= ~ETMCR_CTXID_SIZE;

	अगर (config->mode & ETM_MODE_BBROAD)
		config->ctrl |= ETMCR_BRANCH_BROADCAST;
	अन्यथा
		config->ctrl &= ~ETMCR_BRANCH_BROADCAST;

	अगर (config->mode & ETM_MODE_RET_STACK)
		config->ctrl |= ETMCR_RETURN_STACK;
	अन्यथा
		config->ctrl &= ~ETMCR_RETURN_STACK;

	अगर (config->mode & (ETM_MODE_EXCL_KERN | ETM_MODE_EXCL_USER))
		eपंचांग_config_trace_mode(config);

	spin_unlock(&drvdata->spinlock);

	वापस size;

err_unlock:
	spin_unlock(&drvdata->spinlock);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(mode);

अटल sमाप_प्रकार trigger_event_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->trigger_event;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार trigger_event_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	config->trigger_event = val & ETM_EVENT_MASK;

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(trigger_event);

अटल sमाप_प्रकार enable_event_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->enable_event;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार enable_event_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	config->enable_event = val & ETM_EVENT_MASK;

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(enable_event);

अटल sमाप_प्रकार fअगरofull_level_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->fअगरofull_level;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार fअगरofull_level_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	config->fअगरofull_level = val;

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(fअगरofull_level);

अटल sमाप_प्रकार addr_idx_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->addr_idx;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार addr_idx_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	अगर (val >= drvdata->nr_addr_cmp)
		वापस -EINVAL;

	/*
	 * Use spinlock to ensure index करोesn't change जबतक it माला_लो
	 * dereferenced multiple बार within a spinlock block अन्यथाwhere.
	 */
	spin_lock(&drvdata->spinlock);
	config->addr_idx = val;
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_idx);

अटल sमाप_प्रकार addr_single_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	      config->addr_type[idx] == ETM_ADDR_TYPE_SINGLE)) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EINVAL;
	पूर्ण

	val = config->addr_val[idx];
	spin_unlock(&drvdata->spinlock);

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार addr_single_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	      config->addr_type[idx] == ETM_ADDR_TYPE_SINGLE)) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EINVAL;
	पूर्ण

	config->addr_val[idx] = val;
	config->addr_type[idx] = ETM_ADDR_TYPE_SINGLE;
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_single);

अटल sमाप_प्रकार addr_range_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val1, val2;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (idx % 2 != 0) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण
	अगर (!((config->addr_type[idx] == ETM_ADDR_TYPE_NONE &&
	       config->addr_type[idx + 1] == ETM_ADDR_TYPE_NONE) ||
	      (config->addr_type[idx] == ETM_ADDR_TYPE_RANGE &&
	       config->addr_type[idx + 1] == ETM_ADDR_TYPE_RANGE))) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण

	val1 = config->addr_val[idx];
	val2 = config->addr_val[idx + 1];
	spin_unlock(&drvdata->spinlock);

	वापस प्र_लिखो(buf, "%#lx %#lx\n", val1, val2);
पूर्ण

अटल sमाप_प्रकार addr_range_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val1, val2;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	अगर (माला_पूछो(buf, "%lx %lx", &val1, &val2) != 2)
		वापस -EINVAL;
	/* Lower address comparator cannot have a higher address value */
	अगर (val1 > val2)
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (idx % 2 != 0) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण
	अगर (!((config->addr_type[idx] == ETM_ADDR_TYPE_NONE &&
	       config->addr_type[idx + 1] == ETM_ADDR_TYPE_NONE) ||
	      (config->addr_type[idx] == ETM_ADDR_TYPE_RANGE &&
	       config->addr_type[idx + 1] == ETM_ADDR_TYPE_RANGE))) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण

	config->addr_val[idx] = val1;
	config->addr_type[idx] = ETM_ADDR_TYPE_RANGE;
	config->addr_val[idx + 1] = val2;
	config->addr_type[idx + 1] = ETM_ADDR_TYPE_RANGE;
	config->enable_ctrl1 |= (1 << (idx/2));
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_range);

अटल sमाप_प्रकार addr_start_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	      config->addr_type[idx] == ETM_ADDR_TYPE_START)) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण

	val = config->addr_val[idx];
	spin_unlock(&drvdata->spinlock);

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार addr_start_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	      config->addr_type[idx] == ETM_ADDR_TYPE_START)) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण

	config->addr_val[idx] = val;
	config->addr_type[idx] = ETM_ADDR_TYPE_START;
	config->startstop_ctrl |= (1 << idx);
	config->enable_ctrl1 |= BIT(25);
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_start);

अटल sमाप_प्रकार addr_stop_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	      config->addr_type[idx] == ETM_ADDR_TYPE_STOP)) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण

	val = config->addr_val[idx];
	spin_unlock(&drvdata->spinlock);

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार addr_stop_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	      config->addr_type[idx] == ETM_ADDR_TYPE_STOP)) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण

	config->addr_val[idx] = val;
	config->addr_type[idx] = ETM_ADDR_TYPE_STOP;
	config->startstop_ctrl |= (1 << (idx + 16));
	config->enable_ctrl1 |= ETMTECR1_START_STOP;
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_stop);

अटल sमाप_प्रकार addr_acctype_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	val = config->addr_acctype[config->addr_idx];
	spin_unlock(&drvdata->spinlock);

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार addr_acctype_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	spin_lock(&drvdata->spinlock);
	config->addr_acctype[config->addr_idx] = val;
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_acctype);

अटल sमाप_प्रकार cntr_idx_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->cntr_idx;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार cntr_idx_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	अगर (val >= drvdata->nr_cntr)
		वापस -EINVAL;
	/*
	 * Use spinlock to ensure index करोesn't change जबतक it माला_लो
	 * dereferenced multiple बार within a spinlock block अन्यथाwhere.
	 */
	spin_lock(&drvdata->spinlock);
	config->cntr_idx = val;
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(cntr_idx);

अटल sमाप_प्रकार cntr_rld_val_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	val = config->cntr_rld_val[config->cntr_idx];
	spin_unlock(&drvdata->spinlock);

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार cntr_rld_val_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	spin_lock(&drvdata->spinlock);
	config->cntr_rld_val[config->cntr_idx] = val;
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(cntr_rld_val);

अटल sमाप_प्रकार cntr_event_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	val = config->cntr_event[config->cntr_idx];
	spin_unlock(&drvdata->spinlock);

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार cntr_event_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	spin_lock(&drvdata->spinlock);
	config->cntr_event[config->cntr_idx] = val & ETM_EVENT_MASK;
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(cntr_event);

अटल sमाप_प्रकार cntr_rld_event_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	val = config->cntr_rld_event[config->cntr_idx];
	spin_unlock(&drvdata->spinlock);

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार cntr_rld_event_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	spin_lock(&drvdata->spinlock);
	config->cntr_rld_event[config->cntr_idx] = val & ETM_EVENT_MASK;
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(cntr_rld_event);

अटल sमाप_प्रकार cntr_val_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i, ret = 0;
	u32 val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	अगर (!local_पढ़ो(&drvdata->mode)) अणु
		spin_lock(&drvdata->spinlock);
		क्रम (i = 0; i < drvdata->nr_cntr; i++)
			ret += प्र_लिखो(buf, "counter %d: %x\n",
				       i, config->cntr_val[i]);
		spin_unlock(&drvdata->spinlock);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < drvdata->nr_cntr; i++) अणु
		val = eपंचांग_पढ़ोl(drvdata, ETMCNTVRn(i));
		ret += प्र_लिखो(buf, "counter %d: %x\n", i, val);
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार cntr_val_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	spin_lock(&drvdata->spinlock);
	config->cntr_val[config->cntr_idx] = val;
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(cntr_val);

अटल sमाप_प्रकार seq_12_event_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->seq_12_event;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार seq_12_event_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	config->seq_12_event = val & ETM_EVENT_MASK;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(seq_12_event);

अटल sमाप_प्रकार seq_21_event_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->seq_21_event;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार seq_21_event_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	config->seq_21_event = val & ETM_EVENT_MASK;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(seq_21_event);

अटल sमाप_प्रकार seq_23_event_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->seq_23_event;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार seq_23_event_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	config->seq_23_event = val & ETM_EVENT_MASK;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(seq_23_event);

अटल sमाप_प्रकार seq_31_event_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->seq_31_event;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार seq_31_event_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	config->seq_31_event = val & ETM_EVENT_MASK;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(seq_31_event);

अटल sमाप_प्रकार seq_32_event_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->seq_32_event;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार seq_32_event_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	config->seq_32_event = val & ETM_EVENT_MASK;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(seq_32_event);

अटल sमाप_प्रकार seq_13_event_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->seq_13_event;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार seq_13_event_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	config->seq_13_event = val & ETM_EVENT_MASK;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(seq_13_event);

अटल sमाप_प्रकार seq_curr_state_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val, flags;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	अगर (!local_पढ़ो(&drvdata->mode)) अणु
		val = config->seq_curr_state;
		जाओ out;
	पूर्ण

	pm_runसमय_get_sync(dev->parent);
	spin_lock_irqsave(&drvdata->spinlock, flags);

	CS_UNLOCK(drvdata->base);
	val = (eपंचांग_पढ़ोl(drvdata, ETMSQR) & ETM_SQR_MASK);
	CS_LOCK(drvdata->base);

	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	pm_runसमय_put(dev->parent);
out:
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार seq_curr_state_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	अगर (val > ETM_SEQ_STATE_MAX_VAL)
		वापस -EINVAL;

	config->seq_curr_state = val;

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(seq_curr_state);

अटल sमाप_प्रकार ctxid_idx_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->ctxid_idx;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार ctxid_idx_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	अगर (val >= drvdata->nr_ctxid_cmp)
		वापस -EINVAL;

	/*
	 * Use spinlock to ensure index करोesn't change जबतक it माला_लो
	 * dereferenced multiple बार within a spinlock block अन्यथाwhere.
	 */
	spin_lock(&drvdata->spinlock);
	config->ctxid_idx = val;
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(ctxid_idx);

अटल sमाप_प्रकार ctxid_pid_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	/*
	 * Don't use contextID tracing अगर coming from a PID namespace.  See
	 * comment in ctxid_pid_store().
	 */
	अगर (task_active_pid_ns(current) != &init_pid_ns)
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	val = config->ctxid_pid[config->ctxid_idx];
	spin_unlock(&drvdata->spinlock);

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार ctxid_pid_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ pid;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	/*
	 * When contextID tracing is enabled the tracers will insert the
	 * value found in the contextID रेजिस्टर in the trace stream.  But अगर
	 * a process is in a namespace the PID of that process as seen from the
	 * namespace won't be what the kernel sees, something that makes the
	 * feature confusing and can potentially leak kernel only inक्रमmation.
	 * As such refuse to use the feature अगर @current is not in the initial
	 * PID namespace.
	 */
	अगर (task_active_pid_ns(current) != &init_pid_ns)
		वापस -EINVAL;

	ret = kम_से_अदीर्घ(buf, 16, &pid);
	अगर (ret)
		वापस ret;

	spin_lock(&drvdata->spinlock);
	config->ctxid_pid[config->ctxid_idx] = pid;
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(ctxid_pid);

अटल sमाप_प्रकार ctxid_mask_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	/*
	 * Don't use contextID tracing अगर coming from a PID namespace.  See
	 * comment in ctxid_pid_store().
	 */
	अगर (task_active_pid_ns(current) != &init_pid_ns)
		वापस -EINVAL;

	val = config->ctxid_mask;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार ctxid_mask_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	/*
	 * Don't use contextID tracing अगर coming from a PID namespace.  See
	 * comment in ctxid_pid_store().
	 */
	अगर (task_active_pid_ns(current) != &init_pid_ns)
		वापस -EINVAL;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	config->ctxid_mask = val;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(ctxid_mask);

अटल sमाप_प्रकार sync_freq_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->sync_freq;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार sync_freq_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	config->sync_freq = val & ETM_SYNC_MASK;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(sync_freq);

अटल sमाप_प्रकार बारtamp_event_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	val = config->बारtamp_event;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार बारtamp_event_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांग_config *config = &drvdata->config;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	config->बारtamp_event = val & ETM_EVENT_MASK;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(बारtamp_event);

अटल sमाप_प्रकार cpu_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->cpu;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", val);

पूर्ण
अटल DEVICE_ATTR_RO(cpu);

अटल sमाप_प्रकार traceid_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = eपंचांग_get_trace_id(drvdata);

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार traceid_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	drvdata->traceid = val & ETM_TRACEID_MASK;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(traceid);

अटल काष्ठा attribute *coresight_eपंचांग_attrs[] = अणु
	&dev_attr_nr_addr_cmp.attr,
	&dev_attr_nr_cntr.attr,
	&dev_attr_nr_ctxid_cmp.attr,
	&dev_attr_eपंचांगsr.attr,
	&dev_attr_reset.attr,
	&dev_attr_mode.attr,
	&dev_attr_trigger_event.attr,
	&dev_attr_enable_event.attr,
	&dev_attr_fअगरofull_level.attr,
	&dev_attr_addr_idx.attr,
	&dev_attr_addr_single.attr,
	&dev_attr_addr_range.attr,
	&dev_attr_addr_start.attr,
	&dev_attr_addr_stop.attr,
	&dev_attr_addr_acctype.attr,
	&dev_attr_cntr_idx.attr,
	&dev_attr_cntr_rld_val.attr,
	&dev_attr_cntr_event.attr,
	&dev_attr_cntr_rld_event.attr,
	&dev_attr_cntr_val.attr,
	&dev_attr_seq_12_event.attr,
	&dev_attr_seq_21_event.attr,
	&dev_attr_seq_23_event.attr,
	&dev_attr_seq_31_event.attr,
	&dev_attr_seq_32_event.attr,
	&dev_attr_seq_13_event.attr,
	&dev_attr_seq_curr_state.attr,
	&dev_attr_ctxid_idx.attr,
	&dev_attr_ctxid_pid.attr,
	&dev_attr_ctxid_mask.attr,
	&dev_attr_sync_freq.attr,
	&dev_attr_बारtamp_event.attr,
	&dev_attr_traceid.attr,
	&dev_attr_cpu.attr,
	शून्य,
पूर्ण;

#घोषणा coresight_eपंचांग3x_reg(name, offset)			\
	coresight_simple_reg32(काष्ठा eपंचांग_drvdata, name, offset)

coresight_eपंचांग3x_reg(eपंचांगccr, ETMCCR);
coresight_eपंचांग3x_reg(eपंचांगccer, ETMCCER);
coresight_eपंचांग3x_reg(eपंचांगscr, ETMSCR);
coresight_eपंचांग3x_reg(eपंचांगidr, ETMIDR);
coresight_eपंचांग3x_reg(eपंचांगcr, ETMCR);
coresight_eपंचांग3x_reg(eपंचांगtraceidr, ETMTRACEIDR);
coresight_eपंचांग3x_reg(eपंचांगteevr, ETMTEEVR);
coresight_eपंचांग3x_reg(eपंचांगtssvr, ETMTSSCR);
coresight_eपंचांग3x_reg(eपंचांगtecr1, ETMTECR1);
coresight_eपंचांग3x_reg(eपंचांगtecr2, ETMTECR2);

अटल काष्ठा attribute *coresight_eपंचांग_mgmt_attrs[] = अणु
	&dev_attr_eपंचांगccr.attr,
	&dev_attr_eपंचांगccer.attr,
	&dev_attr_eपंचांगscr.attr,
	&dev_attr_eपंचांगidr.attr,
	&dev_attr_eपंचांगcr.attr,
	&dev_attr_eपंचांगtraceidr.attr,
	&dev_attr_eपंचांगteevr.attr,
	&dev_attr_eपंचांगtssvr.attr,
	&dev_attr_eपंचांगtecr1.attr,
	&dev_attr_eपंचांगtecr2.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_eपंचांग_group = अणु
	.attrs = coresight_eपंचांग_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_eपंचांग_mgmt_group = अणु
	.attrs = coresight_eपंचांग_mgmt_attrs,
	.name = "mgmt",
पूर्ण;

स्थिर काष्ठा attribute_group *coresight_eपंचांग_groups[] = अणु
	&coresight_eपंचांग_group,
	&coresight_eपंचांग_mgmt_group,
	शून्य,
पूर्ण;
