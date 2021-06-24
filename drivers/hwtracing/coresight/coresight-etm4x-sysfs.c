<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(C) 2015 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#समावेश <linux/pid_namespace.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sysfs.h>
#समावेश "coresight-etm4x.h"
#समावेश "coresight-priv.h"

अटल पूर्णांक eपंचांग4_set_mode_exclude(काष्ठा eपंचांगv4_drvdata *drvdata, bool exclude)
अणु
	u8 idx;
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	idx = config->addr_idx;

	/*
	 * TRCACATRn.TYPE bit[1:0]: type of comparison
	 * the trace unit perक्रमms
	 */
	अगर (BMVAL(config->addr_acc[idx], 0, 1) == ETM_INSTR_ADDR) अणु
		अगर (idx % 2 != 0)
			वापस -EINVAL;

		/*
		 * We are perक्रमming inकाष्ठाion address comparison. Set the
		 * relevant bit of ViewInst Include/Exclude Control रेजिस्टर
		 * क्रम corresponding address comparator pair.
		 */
		अगर (config->addr_type[idx] != ETM_ADDR_TYPE_RANGE ||
		    config->addr_type[idx + 1] != ETM_ADDR_TYPE_RANGE)
			वापस -EINVAL;

		अगर (exclude == true) अणु
			/*
			 * Set exclude bit and unset the include bit
			 * corresponding to comparator pair
			 */
			config->viiectlr |= BIT(idx / 2 + 16);
			config->viiectlr &= ~BIT(idx / 2);
		पूर्ण अन्यथा अणु
			/*
			 * Set include bit and unset exclude bit
			 * corresponding to comparator pair
			 */
			config->viiectlr |= BIT(idx / 2);
			config->viiectlr &= ~BIT(idx / 2 + 16);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार nr_pe_cmp_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->nr_pe_cmp;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(nr_pe_cmp);

अटल sमाप_प्रकार nr_addr_cmp_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->nr_addr_cmp;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(nr_addr_cmp);

अटल sमाप_प्रकार nr_cntr_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->nr_cntr;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(nr_cntr);

अटल sमाप_प्रकार nr_ext_inp_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->nr_ext_inp;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(nr_ext_inp);

अटल sमाप_प्रकार numcidc_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->numcidc;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(numcidc);

अटल sमाप_प्रकार numvmidc_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->numvmidc;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(numvmidc);

अटल sमाप_प्रकार nrseqstate_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->nrseqstate;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(nrseqstate);

अटल sमाप_प्रकार nr_resource_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->nr_resource;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(nr_resource);

अटल sमाप_प्रकार nr_ss_cmp_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->nr_ss_cmp;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(nr_ss_cmp);

अटल sमाप_प्रकार reset_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	अगर (val)
		config->mode = 0x0;

	/* Disable data tracing: करो not trace load and store data transfers */
	config->mode &= ~(ETM_MODE_LOAD | ETM_MODE_STORE);
	config->cfg &= ~(BIT(1) | BIT(2));

	/* Disable data value and data address tracing */
	config->mode &= ~(ETM_MODE_DATA_TRACE_ADDR |
			   ETM_MODE_DATA_TRACE_VAL);
	config->cfg &= ~(BIT(16) | BIT(17));

	/* Disable all events tracing */
	config->eventctrl0 = 0x0;
	config->eventctrl1 = 0x0;

	/* Disable बारtamp event */
	config->ts_ctrl = 0x0;

	/* Disable stalling */
	config->stall_ctrl = 0x0;

	/* Reset trace synchronization period  to 2^8 = 256 bytes*/
	अगर (drvdata->syncpr == false)
		config->syncfreq = 0x8;

	/*
	 * Enable ViewInst to trace everything with start-stop logic in
	 * started state. ARM recommends start-stop logic is set beक्रमe
	 * each trace run.
	 */
	config->vinst_ctrl = BIT(0);
	अगर (drvdata->nr_addr_cmp > 0) अणु
		config->mode |= ETM_MODE_VIEWINST_STARTSTOP;
		/* SSSTATUS, bit[9] */
		config->vinst_ctrl |= BIT(9);
	पूर्ण

	/* No address range filtering क्रम ViewInst */
	config->viiectlr = 0x0;

	/* No start-stop filtering क्रम ViewInst */
	config->vissctlr = 0x0;
	config->vipcssctlr = 0x0;

	/* Disable seq events */
	क्रम (i = 0; i < drvdata->nrseqstate-1; i++)
		config->seq_ctrl[i] = 0x0;
	config->seq_rst = 0x0;
	config->seq_state = 0x0;

	/* Disable बाह्यal input events */
	config->ext_inp = 0x0;

	config->cntr_idx = 0x0;
	क्रम (i = 0; i < drvdata->nr_cntr; i++) अणु
		config->cntrldvr[i] = 0x0;
		config->cntr_ctrl[i] = 0x0;
		config->cntr_val[i] = 0x0;
	पूर्ण

	config->res_idx = 0x0;
	क्रम (i = 2; i < 2 * drvdata->nr_resource; i++)
		config->res_ctrl[i] = 0x0;

	config->ss_idx = 0x0;
	क्रम (i = 0; i < drvdata->nr_ss_cmp; i++) अणु
		config->ss_ctrl[i] = 0x0;
		config->ss_pe_cmp[i] = 0x0;
	पूर्ण

	config->addr_idx = 0x0;
	क्रम (i = 0; i < drvdata->nr_addr_cmp * 2; i++) अणु
		config->addr_val[i] = 0x0;
		config->addr_acc[i] = 0x0;
		config->addr_type[i] = ETM_ADDR_TYPE_NONE;
	पूर्ण

	config->ctxid_idx = 0x0;
	क्रम (i = 0; i < drvdata->numcidc; i++)
		config->ctxid_pid[i] = 0x0;

	config->ctxid_mask0 = 0x0;
	config->ctxid_mask1 = 0x0;

	config->vmid_idx = 0x0;
	क्रम (i = 0; i < drvdata->numvmidc; i++)
		config->vmid_val[i] = 0x0;
	config->vmid_mask0 = 0x0;
	config->vmid_mask1 = 0x0;

	drvdata->trcid = drvdata->cpu + 1;

	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_WO(reset);

अटल sमाप_प्रकार mode_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->mode;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार mode_store(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val, mode;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	config->mode = val & ETMv4_MODE_ALL;

	अगर (drvdata->instrp0 == true) अणु
		/* start by clearing inकाष्ठाion P0 field */
		config->cfg  &= ~(BIT(1) | BIT(2));
		अगर (config->mode & ETM_MODE_LOAD)
			/* 0b01 Trace load inकाष्ठाions as P0 inकाष्ठाions */
			config->cfg  |= BIT(1);
		अगर (config->mode & ETM_MODE_STORE)
			/* 0b10 Trace store inकाष्ठाions as P0 inकाष्ठाions */
			config->cfg  |= BIT(2);
		अगर (config->mode & ETM_MODE_LOAD_STORE)
			/*
			 * 0b11 Trace load and store inकाष्ठाions
			 * as P0 inकाष्ठाions
			 */
			config->cfg  |= BIT(1) | BIT(2);
	पूर्ण

	/* bit[3], Branch broadcast mode */
	अगर ((config->mode & ETM_MODE_BB) && (drvdata->trcbb == true))
		config->cfg |= BIT(3);
	अन्यथा
		config->cfg &= ~BIT(3);

	/* bit[4], Cycle counting inकाष्ठाion trace bit */
	अगर ((config->mode & ETMv4_MODE_CYCACC) &&
		(drvdata->trccci == true))
		config->cfg |= BIT(4);
	अन्यथा
		config->cfg &= ~BIT(4);

	/* bit[6], Context ID tracing bit */
	अगर ((config->mode & ETMv4_MODE_CTXID) && (drvdata->ctxid_size))
		config->cfg |= BIT(6);
	अन्यथा
		config->cfg &= ~BIT(6);

	अगर ((config->mode & ETM_MODE_VMID) && (drvdata->vmid_size))
		config->cfg |= BIT(7);
	अन्यथा
		config->cfg &= ~BIT(7);

	/* bits[10:8], Conditional inकाष्ठाion tracing bit */
	mode = ETM_MODE_COND(config->mode);
	अगर (drvdata->trccond == true) अणु
		config->cfg &= ~(BIT(8) | BIT(9) | BIT(10));
		config->cfg |= mode << 8;
	पूर्ण

	/* bit[11], Global बारtamp tracing bit */
	अगर ((config->mode & ETMv4_MODE_TIMESTAMP) && (drvdata->ts_size))
		config->cfg |= BIT(11);
	अन्यथा
		config->cfg &= ~BIT(11);

	/* bit[12], Return stack enable bit */
	अगर ((config->mode & ETM_MODE_RETURNSTACK) &&
					(drvdata->retstack == true))
		config->cfg |= BIT(12);
	अन्यथा
		config->cfg &= ~BIT(12);

	/* bits[14:13], Q element enable field */
	mode = ETM_MODE_QELEM(config->mode);
	/* start by clearing QE bits */
	config->cfg &= ~(BIT(13) | BIT(14));
	/* अगर supported, Q elements with inकाष्ठाion counts are enabled */
	अगर ((mode & BIT(0)) && (drvdata->q_support & BIT(0)))
		config->cfg |= BIT(13);
	/*
	 * अगर supported, Q elements with and without inकाष्ठाion
	 * counts are enabled
	 */
	अगर ((mode & BIT(1)) && (drvdata->q_support & BIT(1)))
		config->cfg |= BIT(14);

	/* bit[11], AMBA Trace Bus (ATB) trigger enable bit */
	अगर ((config->mode & ETM_MODE_ATB_TRIGGER) &&
	    (drvdata->atbtrig == true))
		config->eventctrl1 |= BIT(11);
	अन्यथा
		config->eventctrl1 &= ~BIT(11);

	/* bit[12], Low-घातer state behavior override bit */
	अगर ((config->mode & ETM_MODE_LPOVERRIDE) &&
	    (drvdata->lpoverride == true))
		config->eventctrl1 |= BIT(12);
	अन्यथा
		config->eventctrl1 &= ~BIT(12);

	/* bit[8], Inकाष्ठाion stall bit */
	अगर ((config->mode & ETM_MODE_ISTALL_EN) && (drvdata->stallctl == true))
		config->stall_ctrl |= BIT(8);
	अन्यथा
		config->stall_ctrl &= ~BIT(8);

	/* bit[10], Prioritize inकाष्ठाion trace bit */
	अगर (config->mode & ETM_MODE_INSTPRIO)
		config->stall_ctrl |= BIT(10);
	अन्यथा
		config->stall_ctrl &= ~BIT(10);

	/* bit[13], Trace overflow prevention bit */
	अगर ((config->mode & ETM_MODE_NOOVERFLOW) &&
		(drvdata->nooverflow == true))
		config->stall_ctrl |= BIT(13);
	अन्यथा
		config->stall_ctrl &= ~BIT(13);

	/* bit[9] Start/stop logic control bit */
	अगर (config->mode & ETM_MODE_VIEWINST_STARTSTOP)
		config->vinst_ctrl |= BIT(9);
	अन्यथा
		config->vinst_ctrl &= ~BIT(9);

	/* bit[10], Whether a trace unit must trace a Reset exception */
	अगर (config->mode & ETM_MODE_TRACE_RESET)
		config->vinst_ctrl |= BIT(10);
	अन्यथा
		config->vinst_ctrl &= ~BIT(10);

	/* bit[11], Whether a trace unit must trace a प्रणाली error exception */
	अगर ((config->mode & ETM_MODE_TRACE_ERR) &&
		(drvdata->trc_error == true))
		config->vinst_ctrl |= BIT(11);
	अन्यथा
		config->vinst_ctrl &= ~BIT(11);

	अगर (config->mode & (ETM_MODE_EXCL_KERN | ETM_MODE_EXCL_USER))
		eपंचांग4_config_trace_mode(config);

	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(mode);

अटल sमाप_प्रकार pe_show(काष्ठा device *dev,
		       काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->pe_sel;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार pe_store(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	अगर (val > drvdata->nr_pe) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EINVAL;
	पूर्ण

	config->pe_sel = val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(pe);

अटल sमाप_प्रकार event_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->eventctrl0;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार event_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	चयन (drvdata->nr_event) अणु
	हाल 0x0:
		/* EVENT0, bits[7:0] */
		config->eventctrl0 = val & 0xFF;
		अवरोध;
	हाल 0x1:
		 /* EVENT1, bits[15:8] */
		config->eventctrl0 = val & 0xFFFF;
		अवरोध;
	हाल 0x2:
		/* EVENT2, bits[23:16] */
		config->eventctrl0 = val & 0xFFFFFF;
		अवरोध;
	हाल 0x3:
		/* EVENT3, bits[31:24] */
		config->eventctrl0 = val;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(event);

अटल sमाप_प्रकार event_instren_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = BMVAL(config->eventctrl1, 0, 3);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार event_instren_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	/* start by clearing all inकाष्ठाion event enable bits */
	config->eventctrl1 &= ~(BIT(0) | BIT(1) | BIT(2) | BIT(3));
	चयन (drvdata->nr_event) अणु
	हाल 0x0:
		/* generate Event element क्रम event 1 */
		config->eventctrl1 |= val & BIT(1);
		अवरोध;
	हाल 0x1:
		/* generate Event element क्रम event 1 and 2 */
		config->eventctrl1 |= val & (BIT(0) | BIT(1));
		अवरोध;
	हाल 0x2:
		/* generate Event element क्रम event 1, 2 and 3 */
		config->eventctrl1 |= val & (BIT(0) | BIT(1) | BIT(2));
		अवरोध;
	हाल 0x3:
		/* generate Event element क्रम all 4 events */
		config->eventctrl1 |= val & 0xF;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(event_instren);

अटल sमाप_प्रकार event_ts_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->ts_ctrl;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार event_ts_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (!drvdata->ts_size)
		वापस -EINVAL;

	config->ts_ctrl = val & ETMv4_EVENT_MASK;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(event_ts);

अटल sमाप_प्रकार syncfreq_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->syncfreq;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार syncfreq_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (drvdata->syncpr == true)
		वापस -EINVAL;

	config->syncfreq = val & ETMv4_SYNC_MASK;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(syncfreq);

अटल sमाप_प्रकार cyc_threshold_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->ccctlr;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार cyc_threshold_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	/* mask off max threshold beक्रमe checking min value */
	val &= ETM_CYC_THRESHOLD_MASK;
	अगर (val < drvdata->cciपंचांगin)
		वापस -EINVAL;

	config->ccctlr = val;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(cyc_threshold);

अटल sमाप_प्रकार bb_ctrl_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->bb_ctrl;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार bb_ctrl_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (drvdata->trcbb == false)
		वापस -EINVAL;
	अगर (!drvdata->nr_addr_cmp)
		वापस -EINVAL;

	/*
	 * Bit[8] controls include(1) / exclude(0), bits[0-7] select
	 * inभागidual range comparators. If include then at least 1
	 * range must be selected.
	 */
	अगर ((val & BIT(8)) && (BMVAL(val, 0, 7) == 0))
		वापस -EINVAL;

	config->bb_ctrl = val & GENMASK(8, 0);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(bb_ctrl);

अटल sमाप_प्रकार event_vinst_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->vinst_ctrl & ETMv4_EVENT_MASK;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार event_vinst_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	val &= ETMv4_EVENT_MASK;
	config->vinst_ctrl &= ~ETMv4_EVENT_MASK;
	config->vinst_ctrl |= val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(event_vinst);

अटल sमाप_प्रकार s_exlevel_vinst_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = (config->vinst_ctrl & TRCVICTLR_EXLEVEL_S_MASK) >> TRCVICTLR_EXLEVEL_S_SHIFT;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार s_exlevel_vinst_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	/* clear all EXLEVEL_S bits  */
	config->vinst_ctrl &= ~(TRCVICTLR_EXLEVEL_S_MASK);
	/* enable inकाष्ठाion tracing क्रम corresponding exception level */
	val &= drvdata->s_ex_level;
	config->vinst_ctrl |= (val << TRCVICTLR_EXLEVEL_S_SHIFT);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(s_exlevel_vinst);

अटल sमाप_प्रकार ns_exlevel_vinst_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	/* EXLEVEL_NS, bits[23:20] */
	val = (config->vinst_ctrl & TRCVICTLR_EXLEVEL_NS_MASK) >> TRCVICTLR_EXLEVEL_NS_SHIFT;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार ns_exlevel_vinst_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	/* clear EXLEVEL_NS bits  */
	config->vinst_ctrl &= ~(TRCVICTLR_EXLEVEL_NS_MASK);
	/* enable inकाष्ठाion tracing क्रम corresponding exception level */
	val &= drvdata->ns_ex_level;
	config->vinst_ctrl |= (val << TRCVICTLR_EXLEVEL_NS_SHIFT);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(ns_exlevel_vinst);

अटल sमाप_प्रकार addr_idx_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->addr_idx;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार addr_idx_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (val >= drvdata->nr_addr_cmp * 2)
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

अटल sमाप_प्रकार addr_instdatatype_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	sमाप_प्रकार len;
	u8 val, idx;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	val = BMVAL(config->addr_acc[idx], 0, 1);
	len = scnम_लिखो(buf, PAGE_SIZE, "%s\n",
			val == ETM_INSTR_ADDR ? "instr" :
			(val == ETM_DATA_LOAD_ADDR ? "data_load" :
			(val == ETM_DATA_STORE_ADDR ? "data_store" :
			"data_load_store")));
	spin_unlock(&drvdata->spinlock);
	वापस len;
पूर्ण

अटल sमाप_प्रकार addr_instdatatype_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अक्षर str[20] = "";
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (म_माप(buf) >= 20)
		वापस -EINVAL;
	अगर (माला_पूछो(buf, "%s", str) != 1)
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (!म_भेद(str, "instr"))
		/* TYPE, bits[1:0] */
		config->addr_acc[idx] &= ~(BIT(0) | BIT(1));

	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_instdatatype);

अटल sमाप_प्रकार addr_single_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	idx = config->addr_idx;
	spin_lock(&drvdata->spinlock);
	अगर (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	      config->addr_type[idx] == ETM_ADDR_TYPE_SINGLE)) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण
	val = (अचिन्हित दीर्घ)config->addr_val[idx];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार addr_single_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	      config->addr_type[idx] == ETM_ADDR_TYPE_SINGLE)) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण

	config->addr_val[idx] = (u64)val;
	config->addr_type[idx] = ETM_ADDR_TYPE_SINGLE;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_single);

अटल sमाप_प्रकार addr_range_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val1, val2;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

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

	val1 = (अचिन्हित दीर्घ)config->addr_val[idx];
	val2 = (अचिन्हित दीर्घ)config->addr_val[idx + 1];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx %#lx\n", val1, val2);
पूर्ण

अटल sमाप_प्रकार addr_range_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val1, val2;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;
	पूर्णांक elements, exclude;

	elements = माला_पूछो(buf, "%lx %lx %x", &val1, &val2, &exclude);

	/*  exclude is optional, but need at least two parameter */
	अगर (elements < 2)
		वापस -EINVAL;
	/* lower address comparator cannot have a higher address value */
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

	config->addr_val[idx] = (u64)val1;
	config->addr_type[idx] = ETM_ADDR_TYPE_RANGE;
	config->addr_val[idx + 1] = (u64)val2;
	config->addr_type[idx + 1] = ETM_ADDR_TYPE_RANGE;
	/*
	 * Program include or exclude control bits क्रम vinst or vdata
	 * whenever we change addr comparators to ETM_ADDR_TYPE_RANGE
	 * use supplied value, or शेष to bit set in 'mode'
	 */
	अगर (elements != 3)
		exclude = config->mode & ETM_MODE_EXCLUDE;
	eपंचांग4_set_mode_exclude(drvdata, exclude ? true : false);

	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_range);

अटल sमाप_प्रकार addr_start_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;

	अगर (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	      config->addr_type[idx] == ETM_ADDR_TYPE_START)) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण

	val = (अचिन्हित दीर्घ)config->addr_val[idx];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार addr_start_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (!drvdata->nr_addr_cmp) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EINVAL;
	पूर्ण
	अगर (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	      config->addr_type[idx] == ETM_ADDR_TYPE_START)) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण

	config->addr_val[idx] = (u64)val;
	config->addr_type[idx] = ETM_ADDR_TYPE_START;
	config->vissctlr |= BIT(idx);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_start);

अटल sमाप_प्रकार addr_stop_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;

	अगर (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	      config->addr_type[idx] == ETM_ADDR_TYPE_STOP)) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण

	val = (अचिन्हित दीर्घ)config->addr_val[idx];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार addr_stop_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (!drvdata->nr_addr_cmp) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EINVAL;
	पूर्ण
	अगर (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	       config->addr_type[idx] == ETM_ADDR_TYPE_STOP)) अणु
		spin_unlock(&drvdata->spinlock);
		वापस -EPERM;
	पूर्ण

	config->addr_val[idx] = (u64)val;
	config->addr_type[idx] = ETM_ADDR_TYPE_STOP;
	config->vissctlr |= BIT(idx + 16);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_stop);

अटल sमाप_प्रकार addr_ctxtype_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	sमाप_प्रकार len;
	u8 idx, val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	/* CONTEXTTYPE, bits[3:2] */
	val = BMVAL(config->addr_acc[idx], 2, 3);
	len = scnम_लिखो(buf, PAGE_SIZE, "%s\n", val == ETM_CTX_NONE ? "none" :
			(val == ETM_CTX_CTXID ? "ctxid" :
			(val == ETM_CTX_VMID ? "vmid" : "all")));
	spin_unlock(&drvdata->spinlock);
	वापस len;
पूर्ण

अटल sमाप_प्रकार addr_ctxtype_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अक्षर str[10] = "";
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (म_माप(buf) >= 10)
		वापस -EINVAL;
	अगर (माला_पूछो(buf, "%s", str) != 1)
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	अगर (!म_भेद(str, "none"))
		/* start by clearing context type bits */
		config->addr_acc[idx] &= ~(BIT(2) | BIT(3));
	अन्यथा अगर (!म_भेद(str, "ctxid")) अणु
		/* 0b01 The trace unit perक्रमms a Context ID */
		अगर (drvdata->numcidc) अणु
			config->addr_acc[idx] |= BIT(2);
			config->addr_acc[idx] &= ~BIT(3);
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेद(str, "vmid")) अणु
		/* 0b10 The trace unit perक्रमms a VMID */
		अगर (drvdata->numvmidc) अणु
			config->addr_acc[idx] &= ~BIT(2);
			config->addr_acc[idx] |= BIT(3);
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेद(str, "all")) अणु
		/*
		 * 0b11 The trace unit perक्रमms a Context ID
		 * comparison and a VMID
		 */
		अगर (drvdata->numcidc)
			config->addr_acc[idx] |= BIT(2);
		अगर (drvdata->numvmidc)
			config->addr_acc[idx] |= BIT(3);
	पूर्ण
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_ctxtype);

अटल sमाप_प्रकार addr_context_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	/* context ID comparator bits[6:4] */
	val = BMVAL(config->addr_acc[idx], 4, 6);
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार addr_context_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर ((drvdata->numcidc <= 1) && (drvdata->numvmidc <= 1))
		वापस -EINVAL;
	अगर (val >=  (drvdata->numcidc >= drvdata->numvmidc ?
		     drvdata->numcidc : drvdata->numvmidc))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	/* clear context ID comparator bits[6:4] */
	config->addr_acc[idx] &= ~(BIT(4) | BIT(5) | BIT(6));
	config->addr_acc[idx] |= (val << 4);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_context);

अटल sमाप_प्रकार addr_exlevel_s_ns_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	val = BMVAL(config->addr_acc[idx], 8, 14);
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार addr_exlevel_s_ns_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val & ~((GENMASK(14, 8) >> 8)))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	/* clear Exlevel_ns & Exlevel_s bits[14:12, 11:8], bit[15] is res0 */
	config->addr_acc[idx] &= ~(GENMASK(14, 8));
	config->addr_acc[idx] |= (val << 8);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(addr_exlevel_s_ns);

अटल स्थिर अक्षर * स्थिर addr_type_names[] = अणु
	"unused",
	"single",
	"range",
	"start",
	"stop"
पूर्ण;

अटल sमाप_प्रकार addr_cmp_view_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u8 idx, addr_type;
	अचिन्हित दीर्घ addr_v, addr_v2, addr_ctrl;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;
	पूर्णांक size = 0;
	bool exclude = false;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	addr_v = config->addr_val[idx];
	addr_ctrl = config->addr_acc[idx];
	addr_type = config->addr_type[idx];
	अगर (addr_type == ETM_ADDR_TYPE_RANGE) अणु
		अगर (idx & 0x1) अणु
			idx -= 1;
			addr_v2 = addr_v;
			addr_v = config->addr_val[idx];
		पूर्ण अन्यथा अणु
			addr_v2 = config->addr_val[idx + 1];
		पूर्ण
		exclude = config->viiectlr & BIT(idx / 2 + 16);
	पूर्ण
	spin_unlock(&drvdata->spinlock);
	अगर (addr_type) अणु
		size = scnम_लिखो(buf, PAGE_SIZE, "addr_cmp[%i] %s %#lx", idx,
				 addr_type_names[addr_type], addr_v);
		अगर (addr_type == ETM_ADDR_TYPE_RANGE) अणु
			size += scnम_लिखो(buf + size, PAGE_SIZE - size,
					  " %#lx %s", addr_v2,
					  exclude ? "exclude" : "include");
		पूर्ण
		size += scnम_लिखो(buf + size, PAGE_SIZE - size,
				  " ctrl(%#lx)\n", addr_ctrl);
	पूर्ण अन्यथा अणु
		size = scnम_लिखो(buf, PAGE_SIZE, "addr_cmp[%i] unused\n", idx);
	पूर्ण
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RO(addr_cmp_view);

अटल sमाप_प्रकार vinst_pe_cmp_start_stop_show(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (!drvdata->nr_pe_cmp)
		वापस -EINVAL;
	val = config->vipcssctlr;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण
अटल sमाप_प्रकार vinst_pe_cmp_start_stop_store(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (!drvdata->nr_pe_cmp)
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	config->vipcssctlr = val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(vinst_pe_cmp_start_stop);

अटल sमाप_प्रकार seq_idx_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->seq_idx;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार seq_idx_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (val >= drvdata->nrseqstate - 1)
		वापस -EINVAL;

	/*
	 * Use spinlock to ensure index करोesn't change जबतक it माला_लो
	 * dereferenced multiple बार within a spinlock block अन्यथाwhere.
	 */
	spin_lock(&drvdata->spinlock);
	config->seq_idx = val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(seq_idx);

अटल sमाप_प्रकार seq_state_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->seq_state;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार seq_state_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (val >= drvdata->nrseqstate)
		वापस -EINVAL;

	config->seq_state = val;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(seq_state);

अटल sमाप_प्रकार seq_event_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->seq_idx;
	val = config->seq_ctrl[idx];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार seq_event_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->seq_idx;
	/* Seq control has two masks B[15:8] F[7:0] */
	config->seq_ctrl[idx] = val & 0xFFFF;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(seq_event);

अटल sमाप_प्रकार seq_reset_event_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->seq_rst;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार seq_reset_event_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (!(drvdata->nrseqstate))
		वापस -EINVAL;

	config->seq_rst = val & ETMv4_EVENT_MASK;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(seq_reset_event);

अटल sमाप_प्रकार cntr_idx_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->cntr_idx;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार cntr_idx_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
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

अटल sमाप_प्रकार cntrldvr_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->cntr_idx;
	val = config->cntrldvr[idx];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार cntrldvr_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (val > ETM_CNTR_MAX_VAL)
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->cntr_idx;
	config->cntrldvr[idx] = val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(cntrldvr);

अटल sमाप_प्रकार cntr_val_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->cntr_idx;
	val = config->cntr_val[idx];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार cntr_val_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (val > ETM_CNTR_MAX_VAL)
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->cntr_idx;
	config->cntr_val[idx] = val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(cntr_val);

अटल sमाप_प्रकार cntr_ctrl_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->cntr_idx;
	val = config->cntr_ctrl[idx];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार cntr_ctrl_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->cntr_idx;
	config->cntr_ctrl[idx] = val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(cntr_ctrl);

अटल sमाप_प्रकार res_idx_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->res_idx;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार res_idx_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	/*
	 * Resource selector pair 0 is always implemented and reserved,
	 * namely an idx with 0 and 1 is illegal.
	 */
	अगर ((val < 2) || (val >= 2 * drvdata->nr_resource))
		वापस -EINVAL;

	/*
	 * Use spinlock to ensure index करोesn't change जबतक it माला_लो
	 * dereferenced multiple बार within a spinlock block अन्यथाwhere.
	 */
	spin_lock(&drvdata->spinlock);
	config->res_idx = val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(res_idx);

अटल sमाप_प्रकार res_ctrl_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->res_idx;
	val = config->res_ctrl[idx];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार res_ctrl_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->res_idx;
	/* For odd idx pair inversal bit is RES0 */
	अगर (idx % 2 != 0)
		/* PAIRINV, bit[21] */
		val &= ~BIT(21);
	config->res_ctrl[idx] = val & GENMASK(21, 0);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(res_ctrl);

अटल sमाप_प्रकार sshot_idx_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->ss_idx;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार sshot_idx_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (val >= drvdata->nr_ss_cmp)
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	config->ss_idx = val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(sshot_idx);

अटल sमाप_प्रकार sshot_ctrl_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	val = config->ss_ctrl[config->ss_idx];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार sshot_ctrl_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->ss_idx;
	config->ss_ctrl[idx] = val & GENMASK(24, 0);
	/* must clear bit 31 in related status रेजिस्टर on programming */
	config->ss_status[idx] &= ~BIT(31);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(sshot_ctrl);

अटल sमाप_प्रकार sshot_status_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	val = config->ss_status[config->ss_idx];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(sshot_status);

अटल sमाप_प्रकार sshot_pe_ctrl_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	val = config->ss_pe_cmp[config->ss_idx];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार sshot_pe_ctrl_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->ss_idx;
	config->ss_pe_cmp[idx] = val & GENMASK(7, 0);
	/* must clear bit 31 in related status रेजिस्टर on programming */
	config->ss_status[idx] &= ~BIT(31);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(sshot_pe_ctrl);

अटल sमाप_प्रकार ctxid_idx_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->ctxid_idx;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार ctxid_idx_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (val >= drvdata->numcidc)
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
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	u8 idx;
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	/*
	 * Don't use contextID tracing अगर coming from a PID namespace.  See
	 * comment in ctxid_pid_store().
	 */
	अगर (task_active_pid_ns(current) != &init_pid_ns)
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->ctxid_idx;
	val = (अचिन्हित दीर्घ)config->ctxid_pid[idx];
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार ctxid_pid_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 idx;
	अचिन्हित दीर्घ pid;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

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

	/*
	 * only implemented when ctxid tracing is enabled, i.e. at least one
	 * ctxid comparator is implemented and ctxid is greater than 0 bits
	 * in length
	 */
	अगर (!drvdata->ctxid_size || !drvdata->numcidc)
		वापस -EINVAL;
	अगर (kम_से_अदीर्घ(buf, 16, &pid))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->ctxid_idx;
	config->ctxid_pid[idx] = (u64)pid;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(ctxid_pid);

अटल sमाप_प्रकार ctxid_masks_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	अचिन्हित दीर्घ val1, val2;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	/*
	 * Don't use contextID tracing अगर coming from a PID namespace.  See
	 * comment in ctxid_pid_store().
	 */
	अगर (task_active_pid_ns(current) != &init_pid_ns)
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	val1 = config->ctxid_mask0;
	val2 = config->ctxid_mask1;
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx %#lx\n", val1, val2);
पूर्ण

अटल sमाप_प्रकार ctxid_masks_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 i, j, maskbyte;
	अचिन्हित दीर्घ val1, val2, mask;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;
	पूर्णांक nr_inमाला_दो;

	/*
	 * Don't use contextID tracing अगर coming from a PID namespace.  See
	 * comment in ctxid_pid_store().
	 */
	अगर (task_active_pid_ns(current) != &init_pid_ns)
		वापस -EINVAL;

	/*
	 * only implemented when ctxid tracing is enabled, i.e. at least one
	 * ctxid comparator is implemented and ctxid is greater than 0 bits
	 * in length
	 */
	अगर (!drvdata->ctxid_size || !drvdata->numcidc)
		वापस -EINVAL;
	/* one mask अगर <= 4 comparators, two क्रम up to 8 */
	nr_inमाला_दो = माला_पूछो(buf, "%lx %lx", &val1, &val2);
	अगर ((drvdata->numcidc > 4) && (nr_inमाला_दो != 2))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	/*
	 * each byte[0..3] controls mask value applied to ctxid
	 * comparator[0..3]
	 */
	चयन (drvdata->numcidc) अणु
	हाल 0x1:
		/* COMP0, bits[7:0] */
		config->ctxid_mask0 = val1 & 0xFF;
		अवरोध;
	हाल 0x2:
		/* COMP1, bits[15:8] */
		config->ctxid_mask0 = val1 & 0xFFFF;
		अवरोध;
	हाल 0x3:
		/* COMP2, bits[23:16] */
		config->ctxid_mask0 = val1 & 0xFFFFFF;
		अवरोध;
	हाल 0x4:
		 /* COMP3, bits[31:24] */
		config->ctxid_mask0 = val1;
		अवरोध;
	हाल 0x5:
		/* COMP4, bits[7:0] */
		config->ctxid_mask0 = val1;
		config->ctxid_mask1 = val2 & 0xFF;
		अवरोध;
	हाल 0x6:
		/* COMP5, bits[15:8] */
		config->ctxid_mask0 = val1;
		config->ctxid_mask1 = val2 & 0xFFFF;
		अवरोध;
	हाल 0x7:
		/* COMP6, bits[23:16] */
		config->ctxid_mask0 = val1;
		config->ctxid_mask1 = val2 & 0xFFFFFF;
		अवरोध;
	हाल 0x8:
		/* COMP7, bits[31:24] */
		config->ctxid_mask0 = val1;
		config->ctxid_mask1 = val2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/*
	 * If software sets a mask bit to 1, it must program relevant byte
	 * of ctxid comparator value 0x0, otherwise behavior is unpredictable.
	 * For example, अगर bit[3] of ctxid_mask0 is 1, we must clear bits[31:24]
	 * of ctxid comparator0 value (corresponding to byte 0) रेजिस्टर.
	 */
	mask = config->ctxid_mask0;
	क्रम (i = 0; i < drvdata->numcidc; i++) अणु
		/* mask value of corresponding ctxid comparator */
		maskbyte = mask & ETMv4_EVENT_MASK;
		/*
		 * each bit corresponds to a byte of respective ctxid comparator
		 * value रेजिस्टर
		 */
		क्रम (j = 0; j < 8; j++) अणु
			अगर (maskbyte & 1)
				config->ctxid_pid[i] &= ~(0xFFUL << (j * 8));
			maskbyte >>= 1;
		पूर्ण
		/* Select the next ctxid comparator mask value */
		अगर (i == 3)
			/* ctxid comparators[4-7] */
			mask = config->ctxid_mask1;
		अन्यथा
			mask >>= 0x8;
	पूर्ण

	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(ctxid_masks);

अटल sमाप_प्रकार vmid_idx_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = config->vmid_idx;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार vmid_idx_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;
	अगर (val >= drvdata->numvmidc)
		वापस -EINVAL;

	/*
	 * Use spinlock to ensure index करोesn't change जबतक it माला_लो
	 * dereferenced multiple बार within a spinlock block अन्यथाwhere.
	 */
	spin_lock(&drvdata->spinlock);
	config->vmid_idx = val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(vmid_idx);

अटल sमाप_प्रकार vmid_val_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	val = (अचिन्हित दीर्घ)config->vmid_val[config->vmid_idx];
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार vmid_val_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	/*
	 * only implemented when vmid tracing is enabled, i.e. at least one
	 * vmid comparator is implemented and at least 8 bit vmid size
	 */
	अगर (!drvdata->vmid_size || !drvdata->numvmidc)
		वापस -EINVAL;
	अगर (kम_से_अदीर्घ(buf, 16, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	config->vmid_val[config->vmid_idx] = (u64)val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(vmid_val);

अटल sमाप_प्रकार vmid_masks_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val1, val2;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	val1 = config->vmid_mask0;
	val2 = config->vmid_mask1;
	spin_unlock(&drvdata->spinlock);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx %#lx\n", val1, val2);
पूर्ण

अटल sमाप_प्रकार vmid_masks_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u8 i, j, maskbyte;
	अचिन्हित दीर्घ val1, val2, mask;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा eपंचांगv4_config *config = &drvdata->config;
	पूर्णांक nr_inमाला_दो;

	/*
	 * only implemented when vmid tracing is enabled, i.e. at least one
	 * vmid comparator is implemented and at least 8 bit vmid size
	 */
	अगर (!drvdata->vmid_size || !drvdata->numvmidc)
		वापस -EINVAL;
	/* one mask अगर <= 4 comparators, two क्रम up to 8 */
	nr_inमाला_दो = माला_पूछो(buf, "%lx %lx", &val1, &val2);
	अगर ((drvdata->numvmidc > 4) && (nr_inमाला_दो != 2))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);

	/*
	 * each byte[0..3] controls mask value applied to vmid
	 * comparator[0..3]
	 */
	चयन (drvdata->numvmidc) अणु
	हाल 0x1:
		/* COMP0, bits[7:0] */
		config->vmid_mask0 = val1 & 0xFF;
		अवरोध;
	हाल 0x2:
		/* COMP1, bits[15:8] */
		config->vmid_mask0 = val1 & 0xFFFF;
		अवरोध;
	हाल 0x3:
		/* COMP2, bits[23:16] */
		config->vmid_mask0 = val1 & 0xFFFFFF;
		अवरोध;
	हाल 0x4:
		/* COMP3, bits[31:24] */
		config->vmid_mask0 = val1;
		अवरोध;
	हाल 0x5:
		/* COMP4, bits[7:0] */
		config->vmid_mask0 = val1;
		config->vmid_mask1 = val2 & 0xFF;
		अवरोध;
	हाल 0x6:
		/* COMP5, bits[15:8] */
		config->vmid_mask0 = val1;
		config->vmid_mask1 = val2 & 0xFFFF;
		अवरोध;
	हाल 0x7:
		/* COMP6, bits[23:16] */
		config->vmid_mask0 = val1;
		config->vmid_mask1 = val2 & 0xFFFFFF;
		अवरोध;
	हाल 0x8:
		/* COMP7, bits[31:24] */
		config->vmid_mask0 = val1;
		config->vmid_mask1 = val2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * If software sets a mask bit to 1, it must program relevant byte
	 * of vmid comparator value 0x0, otherwise behavior is unpredictable.
	 * For example, अगर bit[3] of vmid_mask0 is 1, we must clear bits[31:24]
	 * of vmid comparator0 value (corresponding to byte 0) रेजिस्टर.
	 */
	mask = config->vmid_mask0;
	क्रम (i = 0; i < drvdata->numvmidc; i++) अणु
		/* mask value of corresponding vmid comparator */
		maskbyte = mask & ETMv4_EVENT_MASK;
		/*
		 * each bit corresponds to a byte of respective vmid comparator
		 * value रेजिस्टर
		 */
		क्रम (j = 0; j < 8; j++) अणु
			अगर (maskbyte & 1)
				config->vmid_val[i] &= ~(0xFFUL << (j * 8));
			maskbyte >>= 1;
		पूर्ण
		/* Select the next vmid comparator mask value */
		अगर (i == 3)
			/* vmid comparators[4-7] */
			mask = config->vmid_mask1;
		अन्यथा
			mask >>= 0x8;
	पूर्ण
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(vmid_masks);

अटल sमाप_प्रकार cpu_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक val;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->cpu;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", val);

पूर्ण
अटल DEVICE_ATTR_RO(cpu);

अटल काष्ठा attribute *coresight_eपंचांगv4_attrs[] = अणु
	&dev_attr_nr_pe_cmp.attr,
	&dev_attr_nr_addr_cmp.attr,
	&dev_attr_nr_cntr.attr,
	&dev_attr_nr_ext_inp.attr,
	&dev_attr_numcidc.attr,
	&dev_attr_numvmidc.attr,
	&dev_attr_nrseqstate.attr,
	&dev_attr_nr_resource.attr,
	&dev_attr_nr_ss_cmp.attr,
	&dev_attr_reset.attr,
	&dev_attr_mode.attr,
	&dev_attr_pe.attr,
	&dev_attr_event.attr,
	&dev_attr_event_instren.attr,
	&dev_attr_event_ts.attr,
	&dev_attr_syncfreq.attr,
	&dev_attr_cyc_threshold.attr,
	&dev_attr_bb_ctrl.attr,
	&dev_attr_event_vinst.attr,
	&dev_attr_s_exlevel_vinst.attr,
	&dev_attr_ns_exlevel_vinst.attr,
	&dev_attr_addr_idx.attr,
	&dev_attr_addr_instdatatype.attr,
	&dev_attr_addr_single.attr,
	&dev_attr_addr_range.attr,
	&dev_attr_addr_start.attr,
	&dev_attr_addr_stop.attr,
	&dev_attr_addr_ctxtype.attr,
	&dev_attr_addr_context.attr,
	&dev_attr_addr_exlevel_s_ns.attr,
	&dev_attr_addr_cmp_view.attr,
	&dev_attr_vinst_pe_cmp_start_stop.attr,
	&dev_attr_sshot_idx.attr,
	&dev_attr_sshot_ctrl.attr,
	&dev_attr_sshot_pe_ctrl.attr,
	&dev_attr_sshot_status.attr,
	&dev_attr_seq_idx.attr,
	&dev_attr_seq_state.attr,
	&dev_attr_seq_event.attr,
	&dev_attr_seq_reset_event.attr,
	&dev_attr_cntr_idx.attr,
	&dev_attr_cntrldvr.attr,
	&dev_attr_cntr_val.attr,
	&dev_attr_cntr_ctrl.attr,
	&dev_attr_res_idx.attr,
	&dev_attr_res_ctrl.attr,
	&dev_attr_ctxid_idx.attr,
	&dev_attr_ctxid_pid.attr,
	&dev_attr_ctxid_masks.attr,
	&dev_attr_vmid_idx.attr,
	&dev_attr_vmid_val.attr,
	&dev_attr_vmid_masks.attr,
	&dev_attr_cpu.attr,
	शून्य,
पूर्ण;

काष्ठा eपंचांगv4_reg अणु
	काष्ठा coresight_device *csdev;
	u32 offset;
	u32 data;
पूर्ण;

अटल व्योम करो_smp_cross_पढ़ो(व्योम *data)
अणु
	काष्ठा eपंचांगv4_reg *reg = data;

	reg->data = eपंचांग4x_relaxed_पढ़ो32(&reg->csdev->access, reg->offset);
पूर्ण

अटल u32 eपंचांगv4_cross_पढ़ो(स्थिर काष्ठा eपंचांगv4_drvdata *drvdata, u32 offset)
अणु
	काष्ठा eपंचांगv4_reg reg;

	reg.offset = offset;
	reg.csdev = drvdata->csdev;

	/*
	 * smp cross call ensures the CPU will be घातered up beक्रमe
	 * accessing the ETMv4 trace core रेजिस्टरs
	 */
	smp_call_function_single(drvdata->cpu, करो_smp_cross_पढ़ो, &reg, 1);
	वापस reg.data;
पूर्ण

अटल अंतरभूत u32 coresight_eपंचांग4x_attr_to_offset(काष्ठा device_attribute *attr)
अणु
	काष्ठा dev_ext_attribute *eattr;

	eattr = container_of(attr, काष्ठा dev_ext_attribute, attr);
	वापस (u32)(अचिन्हित दीर्घ)eattr->var;
पूर्ण

अटल sमाप_प्रकार coresight_eपंचांग4x_reg_show(काष्ठा device *dev,
					काष्ठा device_attribute *d_attr,
					अक्षर *buf)
अणु
	u32 val, offset;
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);

	offset = coresight_eपंचांग4x_attr_to_offset(d_attr);

	pm_runसमय_get_sync(dev->parent);
	val = eपंचांगv4_cross_पढ़ो(drvdata, offset);
	pm_runसमय_put_sync(dev->parent);

	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%x\n", val);
पूर्ण

अटल अंतरभूत bool
eपंचांग4x_रेजिस्टर_implemented(काष्ठा eपंचांगv4_drvdata *drvdata, u32 offset)
अणु
	चयन (offset) अणु
	ETM_COMMON_SYSREG_LIST_CASES
		/*
		 * Common रेजिस्टरs to ETE & ETM4x accessible via प्रणाली
		 * inकाष्ठाions are always implemented.
		 */
		वापस true;

	ETM4x_ONLY_SYSREG_LIST_CASES
		/*
		 * We only support eपंचांग4x and ete. So अगर the device is not
		 * ETE, it must be ETMv4x.
		 */
		वापस !eपंचांग4x_is_ete(drvdata);

	ETM4x_MMAP_LIST_CASES
		/*
		 * Registers accessible only via memory-mapped रेजिस्टरs
		 * must not be accessed via प्रणाली inकाष्ठाions.
		 * We cannot access the drvdata->csdev here, as this
		 * function is called during the device creation, via
		 * coresight_रेजिस्टर() and the csdev is not initialized
		 * until that is करोne. So rely on the drvdata->base to
		 * detect अगर we have a memory mapped access.
		 * Also ETE करोesn't implement memory mapped access, thus
		 * it is sufficient to check that we are using mmio.
		 */
		वापस !!drvdata->base;

	ETE_ONLY_SYSREG_LIST_CASES
		वापस eपंचांग4x_is_ete(drvdata);
	पूर्ण

	वापस false;
पूर्ण

/*
 * Hide the ETM4x रेजिस्टरs that may not be available on the
 * hardware.
 * There are certain management रेजिस्टरs unavailable via प्रणाली
 * inकाष्ठाions. Make those sysfs attributes hidden on such
 * प्रणालीs.
 */
अटल umode_t
coresight_eपंचांग4x_attr_reg_implemented(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, पूर्णांक unused)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा eपंचांगv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा device_attribute *d_attr;
	u32 offset;

	d_attr = container_of(attr, काष्ठा device_attribute, attr);
	offset = coresight_eपंचांग4x_attr_to_offset(d_attr);

	अगर (eपंचांग4x_रेजिस्टर_implemented(drvdata, offset))
		वापस attr->mode;
	वापस 0;
पूर्ण

#घोषणा coresight_eपंचांग4x_reg(name, offset)				\
	&((काष्ठा dev_ext_attribute[]) अणु				\
	   अणु								\
		__ATTR(name, 0444, coresight_eपंचांग4x_reg_show, शून्य),	\
		(व्योम *)(अचिन्हित दीर्घ)offset				\
	   पूर्ण								\
	पूर्ण)[0].attr.attr

अटल काष्ठा attribute *coresight_eपंचांगv4_mgmt_attrs[] = अणु
	coresight_eपंचांग4x_reg(trcpdcr, TRCPDCR),
	coresight_eपंचांग4x_reg(trcpdsr, TRCPDSR),
	coresight_eपंचांग4x_reg(trclsr, TRCLSR),
	coresight_eपंचांग4x_reg(trcauthstatus, TRCAUTHSTATUS),
	coresight_eपंचांग4x_reg(trcdevid, TRCDEVID),
	coresight_eपंचांग4x_reg(trcdevtype, TRCDEVTYPE),
	coresight_eपंचांग4x_reg(trcpidr0, TRCPIDR0),
	coresight_eपंचांग4x_reg(trcpidr1, TRCPIDR1),
	coresight_eपंचांग4x_reg(trcpidr2, TRCPIDR2),
	coresight_eपंचांग4x_reg(trcpidr3, TRCPIDR3),
	coresight_eपंचांग4x_reg(trcoslsr, TRCOSLSR),
	coresight_eपंचांग4x_reg(trcconfig, TRCCONFIGR),
	coresight_eपंचांग4x_reg(trctraceid, TRCTRACEIDR),
	coresight_eपंचांग4x_reg(trcdevarch, TRCDEVARCH),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *coresight_eपंचांगv4_trcidr_attrs[] = अणु
	coresight_eपंचांग4x_reg(trcidr0, TRCIDR0),
	coresight_eपंचांग4x_reg(trcidr1, TRCIDR1),
	coresight_eपंचांग4x_reg(trcidr2, TRCIDR2),
	coresight_eपंचांग4x_reg(trcidr3, TRCIDR3),
	coresight_eपंचांग4x_reg(trcidr4, TRCIDR4),
	coresight_eपंचांग4x_reg(trcidr5, TRCIDR5),
	/* trcidr[6,7] are reserved */
	coresight_eपंचांग4x_reg(trcidr8, TRCIDR8),
	coresight_eपंचांग4x_reg(trcidr9, TRCIDR9),
	coresight_eपंचांग4x_reg(trcidr10, TRCIDR10),
	coresight_eपंचांग4x_reg(trcidr11, TRCIDR11),
	coresight_eपंचांग4x_reg(trcidr12, TRCIDR12),
	coresight_eपंचांग4x_reg(trcidr13, TRCIDR13),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_eपंचांगv4_group = अणु
	.attrs = coresight_eपंचांगv4_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_eपंचांगv4_mgmt_group = अणु
	.is_visible = coresight_eपंचांग4x_attr_reg_implemented,
	.attrs = coresight_eपंचांगv4_mgmt_attrs,
	.name = "mgmt",
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_eपंचांगv4_trcidr_group = अणु
	.attrs = coresight_eपंचांगv4_trcidr_attrs,
	.name = "trcidr",
पूर्ण;

स्थिर काष्ठा attribute_group *coresight_eपंचांगv4_groups[] = अणु
	&coresight_eपंचांगv4_group,
	&coresight_eपंचांगv4_mgmt_group,
	&coresight_eपंचांगv4_trcidr_group,
	शून्य,
पूर्ण;
