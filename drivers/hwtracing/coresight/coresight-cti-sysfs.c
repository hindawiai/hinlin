<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 Linaro Limited, All rights reserved.
 * Author: Mike Leach <mike.leach@linaro.org>
 */

#समावेश <linux/atomic.h>
#समावेश <linux/coresight.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysfs.h>

#समावेश "coresight-cti.h"

/*
 * Declare the number of अटल declared attribute groups
 * Value includes groups + शून्य value at end of table.
 */
#घोषणा CORESIGHT_CTI_STATIC_GROUPS_MAX 5

/*
 * List of trigger संकेत type names. Match the स्थिरants declared in
 * include\dt-bindings\चrm\coresight-cti-dt.h
 */
अटल स्थिर अक्षर * स्थिर sig_type_names[] = अणु
	"genio",	/* GEN_IO */
	"intreq",	/* GEN_INTREQ */
	"intack",	/* GEN_INTACK */
	"haltreq",	/* GEN_HALTREQ */
	"restartreq",	/* GEN_RESTARTREQ */
	"pe_edbgreq",	/* PE_EDBGREQ */
	"pe_dbgrestart",/* PE_DBGRESTART */
	"pe_ctiirq",	/* PE_CTIIRQ */
	"pe_pmuirq",	/* PE_PMUIRQ */
	"pe_dbgtrigger",/* PE_DBGTRIGGER */
	"etm_extout",	/* ETM_EXTOUT */
	"etm_extin",	/* ETM_EXTIN */
	"snk_full",	/* SNK_FULL */
	"snk_acqcomp",	/* SNK_ACQCOMP */
	"snk_flushcomp",/* SNK_FLUSHCOMP */
	"snk_flushin",	/* SNK_FLUSHIN */
	"snk_trigin",	/* SNK_TRIGIN */
	"stm_asyncout",	/* STM_ASYNCOUT */
	"stm_tout_spte",/* STM_TOUT_SPTE */
	"stm_tout_sw",	/* STM_TOUT_SW */
	"stm_tout_hete",/* STM_TOUT_HETE */
	"stm_hwevent",	/* STM_HWEVENT */
	"ela_tstart",	/* ELA_TSTART */
	"ela_tstop",	/* ELA_TSTOP */
	"ela_dbgreq",	/* ELA_DBGREQ */
पूर्ण;

/* Show function poपूर्णांकer used in the connections dynamic declared attributes*/
प्रकार sमाप_प्रकार (*p_show_fn)(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf);

/* Connection attribute types */
क्रमागत cti_conn_attr_type अणु
	CTI_CON_ATTR_NAME,
	CTI_CON_ATTR_TRIGIN_SIG,
	CTI_CON_ATTR_TRIGOUT_SIG,
	CTI_CON_ATTR_TRIGIN_TYPES,
	CTI_CON_ATTR_TRIGOUT_TYPES,
	CTI_CON_ATTR_MAX,
पूर्ण;

/* Names क्रम the connection attributes */
अटल स्थिर अक्षर * स्थिर con_attr_names[CTI_CON_ATTR_MAX] = अणु
	"name",
	"in_signals",
	"out_signals",
	"in_types",
	"out_types",
पूर्ण;

/* basic attributes */
अटल sमाप_प्रकार enable_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक enable_req;
	bool enabled, घातered;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	enable_req = atomic_पढ़ो(&drvdata->config.enable_req_count);
	spin_lock(&drvdata->spinlock);
	घातered = drvdata->config.hw_घातered;
	enabled = drvdata->config.hw_enabled;
	spin_unlock(&drvdata->spinlock);

	अगर (घातered)
		वापस प्र_लिखो(buf, "%d\n", enabled);
	अन्यथा
		वापस प्र_लिखो(buf, "%d\n", !!enable_req);
पूर्ण

अटल sमाप_प्रकार enable_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ val;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val)
		ret = cti_enable(drvdata->csdev);
	अन्यथा
		ret = cti_disable(drvdata->csdev);
	अगर (ret)
		वापस ret;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(enable);

अटल sमाप_प्रकार घातered_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	bool घातered;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	spin_lock(&drvdata->spinlock);
	घातered = drvdata->config.hw_घातered;
	spin_unlock(&drvdata->spinlock);

	वापस प्र_लिखो(buf, "%d\n", घातered);
पूर्ण
अटल DEVICE_ATTR_RO(घातered);

अटल sमाप_प्रकार cपंचांगid_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	वापस प्र_लिखो(buf, "%d\n", drvdata->ctidev.cपंचांग_id);
पूर्ण
अटल DEVICE_ATTR_RO(cपंचांगid);

अटल sमाप_प्रकार nr_trigger_cons_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	वापस प्र_लिखो(buf, "%d\n", drvdata->ctidev.nr_trig_con);
पूर्ण
अटल DEVICE_ATTR_RO(nr_trigger_cons);

/* attribute and group sysfs tables. */
अटल काष्ठा attribute *coresight_cti_attrs[] = अणु
	&dev_attr_enable.attr,
	&dev_attr_घातered.attr,
	&dev_attr_cपंचांगid.attr,
	&dev_attr_nr_trigger_cons.attr,
	शून्य,
पूर्ण;

/* रेजिस्टर based attributes */

/* macro to access RO रेजिस्टरs with घातer check only (no enable check). */
#घोषणा coresight_cti_reg(name, offset)			\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);	\
	u32 val = 0;							\
	pm_runसमय_get_sync(dev->parent);				\
	spin_lock(&drvdata->spinlock);					\
	अगर (drvdata->config.hw_घातered)					\
		val = पढ़ोl_relaxed(drvdata->base + offset);		\
	spin_unlock(&drvdata->spinlock);				\
	pm_runसमय_put_sync(dev->parent);				\
	वापस प्र_लिखो(buf, "0x%x\n", val);				\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

/* coresight management रेजिस्टरs */
coresight_cti_reg(devaff0, CTIDEVAFF0);
coresight_cti_reg(devaff1, CTIDEVAFF1);
coresight_cti_reg(authstatus, CORESIGHT_AUTHSTATUS);
coresight_cti_reg(devarch, CORESIGHT_DEVARCH);
coresight_cti_reg(devid, CORESIGHT_DEVID);
coresight_cti_reg(devtype, CORESIGHT_DEVTYPE);
coresight_cti_reg(pidr0, CORESIGHT_PERIPHIDR0);
coresight_cti_reg(pidr1, CORESIGHT_PERIPHIDR1);
coresight_cti_reg(pidr2, CORESIGHT_PERIPHIDR2);
coresight_cti_reg(pidr3, CORESIGHT_PERIPHIDR3);
coresight_cti_reg(pidr4, CORESIGHT_PERIPHIDR4);

अटल काष्ठा attribute *coresight_cti_mgmt_attrs[] = अणु
	&dev_attr_devaff0.attr,
	&dev_attr_devaff1.attr,
	&dev_attr_authstatus.attr,
	&dev_attr_devarch.attr,
	&dev_attr_devid.attr,
	&dev_attr_devtype.attr,
	&dev_attr_pidr0.attr,
	&dev_attr_pidr1.attr,
	&dev_attr_pidr2.attr,
	&dev_attr_pidr3.attr,
	&dev_attr_pidr4.attr,
	शून्य,
पूर्ण;

/* CTI low level programming रेजिस्टरs */

/*
 * Show a simple 32 bit value अगर enabled and घातered.
 * If inaccessible & pcached_val not शून्य then show cached value.
 */
अटल sमाप_प्रकार cti_reg32_show(काष्ठा device *dev, अक्षर *buf,
			      u32 *pcached_val, पूर्णांक reg_offset)
अणु
	u32 val = 0;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	अगर ((reg_offset >= 0) && cti_active(config)) अणु
		CS_UNLOCK(drvdata->base);
		val = पढ़ोl_relaxed(drvdata->base + reg_offset);
		अगर (pcached_val)
			*pcached_val = val;
		CS_LOCK(drvdata->base);
	पूर्ण अन्यथा अगर (pcached_val) अणु
		val = *pcached_val;
	पूर्ण
	spin_unlock(&drvdata->spinlock);
	वापस प्र_लिखो(buf, "%#x\n", val);
पूर्ण

/*
 * Store a simple 32 bit value.
 * If pcached_val not शून्य, then copy to here too,
 * अगर reg_offset >= 0 then ग_लिखो through अगर enabled.
 */
अटल sमाप_प्रकार cti_reg32_store(काष्ठा device *dev, स्थिर अक्षर *buf,
			       माप_प्रकार size, u32 *pcached_val, पूर्णांक reg_offset)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	/* local store */
	अगर (pcached_val)
		*pcached_val = (u32)val;

	/* ग_लिखो through अगर offset and enabled */
	अगर ((reg_offset >= 0) && cti_active(config))
		cti_ग_लिखो_single_reg(drvdata, reg_offset, val);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण

/* Standard macro क्रम simple rw cti config रेजिस्टरs */
#घोषणा cti_config_reg32_rw(name, cfgname, offset)			\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr,		\
			   अक्षर *buf)					\
अणु									\
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);	\
	वापस cti_reg32_show(dev, buf,					\
			      &drvdata->config.cfgname, offset);	\
पूर्ण									\
									\
अटल sमाप_प्रकार name##_store(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr,		\
			    स्थिर अक्षर *buf, माप_प्रकार size)		\
अणु									\
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);	\
	वापस cti_reg32_store(dev, buf, size,				\
			       &drvdata->config.cfgname, offset);	\
पूर्ण									\
अटल DEVICE_ATTR_RW(name)

अटल sमाप_प्रकार inout_sel_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	u32 val;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = (u32)drvdata->config.ctiinout_sel;
	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार inout_sel_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;
	अगर (val > (CTIINOUTEN_MAX - 1))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	drvdata->config.ctiinout_sel = val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(inout_sel);

अटल sमाप_प्रकार inen_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक index;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	spin_lock(&drvdata->spinlock);
	index = drvdata->config.ctiinout_sel;
	val = drvdata->config.ctiinen[index];
	spin_unlock(&drvdata->spinlock);
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार inen_store(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक index;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	index = config->ctiinout_sel;
	config->ctiinen[index] = val;

	/* ग_लिखो through अगर enabled */
	अगर (cti_active(config))
		cti_ग_लिखो_single_reg(drvdata, CTIINEN(index), val);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(inen);

अटल sमाप_प्रकार outen_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक index;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	spin_lock(&drvdata->spinlock);
	index = drvdata->config.ctiinout_sel;
	val = drvdata->config.ctiouten[index];
	spin_unlock(&drvdata->spinlock);
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार outen_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक index;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	index = config->ctiinout_sel;
	config->ctiouten[index] = val;

	/* ग_लिखो through अगर enabled */
	अगर (cti_active(config))
		cti_ग_लिखो_single_reg(drvdata, CTIOUTEN(index), val);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(outen);

अटल sमाप_प्रकार पूर्णांकack_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	cti_ग_लिखो_पूर्णांकack(dev, val);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_WO(पूर्णांकack);

cti_config_reg32_rw(gate, ctigate, CTIGATE);
cti_config_reg32_rw(asicctl, asicctl, ASICCTL);
cti_config_reg32_rw(appset, ctiappset, CTIAPPSET);

अटल sमाप_प्रकार appclear_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);

	/* a 1'b1 in appclr clears करोwn the same bit in appset*/
	config->ctiappset &= ~val;

	/* ग_लिखो through अगर enabled */
	अगर (cti_active(config))
		cti_ग_लिखो_single_reg(drvdata, CTIAPPCLEAR, val);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_WO(appclear);

अटल sमाप_प्रकार apppulse_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *config = &drvdata->config;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);

	/* ग_लिखो through अगर enabled */
	अगर (cti_active(config))
		cti_ग_लिखो_single_reg(drvdata, CTIAPPPULSE, val);
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_WO(apppulse);

coresight_cti_reg(triginstatus, CTITRIGINSTATUS);
coresight_cti_reg(trigoutstatus, CTITRIGOUTSTATUS);
coresight_cti_reg(chinstatus, CTICHINSTATUS);
coresight_cti_reg(choutstatus, CTICHOUTSTATUS);

/*
 * Define CONFIG_CORESIGHT_CTI_INTEGRATION_REGS to enable the access to the
 * पूर्णांकegration control रेजिस्टरs. Normally only used to investigate connection
 * data.
 */
#अगर_घोषित CONFIG_CORESIGHT_CTI_INTEGRATION_REGS

/* macro to access RW रेजिस्टरs with घातer check only (no enable check). */
#घोषणा coresight_cti_reg_rw(name, offset)				\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);	\
	u32 val = 0;							\
	pm_runसमय_get_sync(dev->parent);				\
	spin_lock(&drvdata->spinlock);					\
	अगर (drvdata->config.hw_घातered)					\
		val = पढ़ोl_relaxed(drvdata->base + offset);		\
	spin_unlock(&drvdata->spinlock);				\
	pm_runसमय_put_sync(dev->parent);				\
	वापस प्र_लिखो(buf, "0x%x\n", val);				\
पूर्ण									\
									\
अटल sमाप_प्रकार name##_store(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr,		\
			    स्थिर अक्षर *buf, माप_प्रकार size)		\
अणु									\
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);	\
	अचिन्हित दीर्घ val = 0;						\
	अगर (kम_से_अदीर्घ(buf, 0, &val))					\
		वापस -EINVAL;						\
									\
	pm_runसमय_get_sync(dev->parent);				\
	spin_lock(&drvdata->spinlock);					\
	अगर (drvdata->config.hw_घातered)					\
		cti_ग_लिखो_single_reg(drvdata, offset, val);		\
	spin_unlock(&drvdata->spinlock);				\
	pm_runसमय_put_sync(dev->parent);				\
	वापस size;							\
पूर्ण									\
अटल DEVICE_ATTR_RW(name)

/* macro to access WO रेजिस्टरs with घातer check only (no enable check). */
#घोषणा coresight_cti_reg_wo(name, offset)				\
अटल sमाप_प्रकार name##_store(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr,		\
			    स्थिर अक्षर *buf, माप_प्रकार size)		\
अणु									\
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);	\
	अचिन्हित दीर्घ val = 0;						\
	अगर (kम_से_अदीर्घ(buf, 0, &val))					\
		वापस -EINVAL;						\
									\
	pm_runसमय_get_sync(dev->parent);				\
	spin_lock(&drvdata->spinlock);					\
	अगर (drvdata->config.hw_घातered)					\
		cti_ग_लिखो_single_reg(drvdata, offset, val);		\
	spin_unlock(&drvdata->spinlock);				\
	pm_runसमय_put_sync(dev->parent);				\
	वापस size;							\
पूर्ण									\
अटल DEVICE_ATTR_WO(name)

coresight_cti_reg_rw(itchout, ITCHOUT);
coresight_cti_reg_rw(ittrigout, ITTRIGOUT);
coresight_cti_reg_rw(itctrl, CORESIGHT_ITCTRL);
coresight_cti_reg_wo(itchinack, ITCHINACK);
coresight_cti_reg_wo(ittriginack, ITTRIGINACK);
coresight_cti_reg(ittrigin, ITTRIGIN);
coresight_cti_reg(itchin, ITCHIN);
coresight_cti_reg(itchoutack, ITCHOUTACK);
coresight_cti_reg(ittrigoutack, ITTRIGOUTACK);

#पूर्ण_अगर /* CORESIGHT_CTI_INTEGRATION_REGS */

अटल काष्ठा attribute *coresight_cti_regs_attrs[] = अणु
	&dev_attr_inout_sel.attr,
	&dev_attr_inen.attr,
	&dev_attr_outen.attr,
	&dev_attr_gate.attr,
	&dev_attr_asicctl.attr,
	&dev_attr_पूर्णांकack.attr,
	&dev_attr_appset.attr,
	&dev_attr_appclear.attr,
	&dev_attr_apppulse.attr,
	&dev_attr_triginstatus.attr,
	&dev_attr_trigoutstatus.attr,
	&dev_attr_chinstatus.attr,
	&dev_attr_choutstatus.attr,
#अगर_घोषित CONFIG_CORESIGHT_CTI_INTEGRATION_REGS
	&dev_attr_itctrl.attr,
	&dev_attr_ittrigin.attr,
	&dev_attr_itchin.attr,
	&dev_attr_ittrigout.attr,
	&dev_attr_itchout.attr,
	&dev_attr_itchoutack.attr,
	&dev_attr_ittrigoutack.attr,
	&dev_attr_ittriginack.attr,
	&dev_attr_itchinack.attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;

/* CTI channel x-trigger programming */
अटल पूर्णांक
cti_trig_op_parse(काष्ठा device *dev, क्रमागत cti_chan_op op,
		  क्रमागत cti_trig_dir dir, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	u32 chan_idx;
	u32 trig_idx;
	पूर्णांक items, err = -EINVAL;

	/* extract chan idx and trigger idx */
	items = माला_पूछो(buf, "%d %d", &chan_idx, &trig_idx);
	अगर (items == 2) अणु
		err = cti_channel_trig_op(dev, op, dir, chan_idx, trig_idx);
		अगर (!err)
			err = size;
	पूर्ण
	वापस err;
पूर्ण

अटल sमाप_प्रकार trigin_attach_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस cti_trig_op_parse(dev, CTI_CHAN_ATTACH, CTI_TRIG_IN,
				 buf, size);
पूर्ण
अटल DEVICE_ATTR_WO(trigin_attach);

अटल sमाप_प्रकार trigin_detach_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस cti_trig_op_parse(dev, CTI_CHAN_DETACH, CTI_TRIG_IN,
				 buf, size);
पूर्ण
अटल DEVICE_ATTR_WO(trigin_detach);

अटल sमाप_प्रकार trigout_attach_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस cti_trig_op_parse(dev, CTI_CHAN_ATTACH, CTI_TRIG_OUT,
				 buf, size);
पूर्ण
अटल DEVICE_ATTR_WO(trigout_attach);

अटल sमाप_प्रकार trigout_detach_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	वापस cti_trig_op_parse(dev, CTI_CHAN_DETACH, CTI_TRIG_OUT,
				 buf, size);
पूर्ण
अटल DEVICE_ATTR_WO(trigout_detach);


अटल sमाप_प्रकार chan_gate_enable_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक err = 0, channel = 0;

	अगर (kstrtoपूर्णांक(buf, 0, &channel))
		वापस -EINVAL;

	err = cti_channel_gate_op(dev, CTI_GATE_CHAN_ENABLE, channel);
	वापस err ? err : size;
पूर्ण

अटल sमाप_प्रकार chan_gate_enable_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *cfg = &drvdata->config;
	अचिन्हित दीर्घ ctigate_biपंचांगask = cfg->ctigate;
	पूर्णांक size = 0;

	अगर (cfg->ctigate == 0)
		size = प्र_लिखो(buf, "\n");
	अन्यथा
		size = biपंचांगap_prपूर्णांक_to_pagebuf(true, buf, &ctigate_biपंचांगask,
					       cfg->nr_cपंचांग_channels);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(chan_gate_enable);

अटल sमाप_प्रकार chan_gate_disable_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक err = 0, channel = 0;

	अगर (kstrtoपूर्णांक(buf, 0, &channel))
		वापस -EINVAL;

	err = cti_channel_gate_op(dev, CTI_GATE_CHAN_DISABLE, channel);
	वापस err ? err : size;
पूर्ण
अटल DEVICE_ATTR_WO(chan_gate_disable);

अटल पूर्णांक
chan_op_parse(काष्ठा device *dev, क्रमागत cti_chan_set_op op, स्थिर अक्षर *buf)
अणु
	पूर्णांक err = 0, channel = 0;

	अगर (kstrtoपूर्णांक(buf, 0, &channel))
		वापस -EINVAL;

	err = cti_channel_setop(dev, op, channel);
	वापस err;

पूर्ण

अटल sमाप_प्रकार chan_set_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक err = chan_op_parse(dev, CTI_CHAN_SET, buf);

	वापस err ? err : size;
पूर्ण
अटल DEVICE_ATTR_WO(chan_set);

अटल sमाप_प्रकार chan_clear_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक err = chan_op_parse(dev, CTI_CHAN_CLR, buf);

	वापस err ? err : size;
पूर्ण
अटल DEVICE_ATTR_WO(chan_clear);

अटल sमाप_प्रकार chan_pulse_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक err = chan_op_parse(dev, CTI_CHAN_PULSE, buf);

	वापस err ? err : size;
पूर्ण
अटल DEVICE_ATTR_WO(chan_pulse);

अटल sमाप_प्रकार trig_filter_enable_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	u32 val;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	spin_lock(&drvdata->spinlock);
	val = drvdata->config.trig_filter_enable;
	spin_unlock(&drvdata->spinlock);
	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार trig_filter_enable_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	drvdata->config.trig_filter_enable = !!val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(trig_filter_enable);

अटल sमाप_प्रकार trigout_filtered_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *cfg = &drvdata->config;
	पूर्णांक size = 0, nr_trig_max = cfg->nr_trig_max;
	अचिन्हित दीर्घ mask = cfg->trig_out_filter;

	अगर (mask)
		size = biपंचांगap_prपूर्णांक_to_pagebuf(true, buf, &mask, nr_trig_max);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RO(trigout_filtered);

/* clear all xtrigger / channel programming */
अटल sमाप_प्रकार chan_xtrigs_reset_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक i;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);

	/* clear the CTI trigger / channel programming रेजिस्टरs */
	क्रम (i = 0; i < config->nr_trig_max; i++) अणु
		config->ctiinen[i] = 0;
		config->ctiouten[i] = 0;
	पूर्ण

	/* clear the other regs */
	config->ctigate = GENMASK(config->nr_cपंचांग_channels - 1, 0);
	config->asicctl = 0;
	config->ctiappset = 0;
	config->ctiinout_sel = 0;
	config->xtrig_rchan_sel = 0;

	/* अगर enabled then ग_लिखो through */
	अगर (cti_active(config))
		cti_ग_लिखो_all_hw_regs(drvdata);

	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR_WO(chan_xtrigs_reset);

/*
 * Write to select a channel to view, पढ़ो to display the
 * cross triggers क्रम the selected channel.
 */
अटल sमाप_प्रकार chan_xtrigs_sel_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;
	अगर (val > (drvdata->config.nr_cपंचांग_channels - 1))
		वापस -EINVAL;

	spin_lock(&drvdata->spinlock);
	drvdata->config.xtrig_rchan_sel = val;
	spin_unlock(&drvdata->spinlock);
	वापस size;
पूर्ण

अटल sमाप_प्रकार chan_xtrigs_sel_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);

	spin_lock(&drvdata->spinlock);
	val = drvdata->config.xtrig_rchan_sel;
	spin_unlock(&drvdata->spinlock);

	वापस प्र_लिखो(buf, "%ld\n", val);
पूर्ण
अटल DEVICE_ATTR_RW(chan_xtrigs_sel);

अटल sमाप_प्रकार chan_xtrigs_in_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *cfg = &drvdata->config;
	पूर्णांक used = 0, reg_idx;
	पूर्णांक nr_trig_max = drvdata->config.nr_trig_max;
	u32 chan_mask = BIT(cfg->xtrig_rchan_sel);

	क्रम (reg_idx = 0; reg_idx < nr_trig_max; reg_idx++) अणु
		अगर (chan_mask & cfg->ctiinen[reg_idx])
			used += प्र_लिखो(buf + used, "%d ", reg_idx);
	पूर्ण

	used += प्र_लिखो(buf + used, "\n");
	वापस used;
पूर्ण
अटल DEVICE_ATTR_RO(chan_xtrigs_in);

अटल sमाप_प्रकार chan_xtrigs_out_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *cfg = &drvdata->config;
	पूर्णांक used = 0, reg_idx;
	पूर्णांक nr_trig_max = drvdata->config.nr_trig_max;
	u32 chan_mask = BIT(cfg->xtrig_rchan_sel);

	क्रम (reg_idx = 0; reg_idx < nr_trig_max; reg_idx++) अणु
		अगर (chan_mask & cfg->ctiouten[reg_idx])
			used += प्र_लिखो(buf + used, "%d ", reg_idx);
	पूर्ण

	used += प्र_लिखो(buf + used, "\n");
	वापस used;
पूर्ण
अटल DEVICE_ATTR_RO(chan_xtrigs_out);

अटल sमाप_प्रकार prपूर्णांक_chan_list(काष्ठा device *dev,
			       अक्षर *buf, bool inuse)
अणु
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *config = &drvdata->config;
	पूर्णांक size, i;
	अचिन्हित दीर्घ inuse_bits = 0, chan_mask;

	/* scan regs to get biपंचांगap of channels in use. */
	spin_lock(&drvdata->spinlock);
	क्रम (i = 0; i < config->nr_trig_max; i++) अणु
		inuse_bits |= config->ctiinen[i];
		inuse_bits |= config->ctiouten[i];
	पूर्ण
	spin_unlock(&drvdata->spinlock);

	/* inverse bits अगर prपूर्णांकing मुक्त channels */
	अगर (!inuse)
		inuse_bits = ~inuse_bits;

	/* list of channels, or 'none' */
	chan_mask = GENMASK(config->nr_cपंचांग_channels - 1, 0);
	अगर (inuse_bits & chan_mask)
		size = biपंचांगap_prपूर्णांक_to_pagebuf(true, buf, &inuse_bits,
					       config->nr_cपंचांग_channels);
	अन्यथा
		size = प्र_लिखो(buf, "\n");
	वापस size;
पूर्ण

अटल sमाप_प्रकार chan_inuse_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	वापस prपूर्णांक_chan_list(dev, buf, true);
पूर्ण
अटल DEVICE_ATTR_RO(chan_inuse);

अटल sमाप_प्रकार chan_मुक्त_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस prपूर्णांक_chan_list(dev, buf, false);
पूर्ण
अटल DEVICE_ATTR_RO(chan_मुक्त);

अटल काष्ठा attribute *coresight_cti_channel_attrs[] = अणु
	&dev_attr_trigin_attach.attr,
	&dev_attr_trigin_detach.attr,
	&dev_attr_trigout_attach.attr,
	&dev_attr_trigout_detach.attr,
	&dev_attr_trig_filter_enable.attr,
	&dev_attr_trigout_filtered.attr,
	&dev_attr_chan_gate_enable.attr,
	&dev_attr_chan_gate_disable.attr,
	&dev_attr_chan_set.attr,
	&dev_attr_chan_clear.attr,
	&dev_attr_chan_pulse.attr,
	&dev_attr_chan_inuse.attr,
	&dev_attr_chan_मुक्त.attr,
	&dev_attr_chan_xtrigs_sel.attr,
	&dev_attr_chan_xtrigs_in.attr,
	&dev_attr_chan_xtrigs_out.attr,
	&dev_attr_chan_xtrigs_reset.attr,
	शून्य,
पूर्ण;

/* Create the connections trigger groups and attrs dynamically */
/*
 * Each connection has dynamic group triggers<N> + name, trigin/out sigs/types
 * attributes, + each device has अटल nr_trigger_cons giving the number
 * of groups. e.g. in sysfs:-
 * /cti_<name>/triggers0
 * /cti_<name>/triggers1
 * /cti_<name>/nr_trigger_cons
 * where nr_trigger_cons = 2
 */
अटल sमाप_प्रकार con_name_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *ext_attr =
		container_of(attr, काष्ठा dev_ext_attribute, attr);
	काष्ठा cti_trig_con *con = (काष्ठा cti_trig_con *)ext_attr->var;

	वापस प्र_लिखो(buf, "%s\n", con->con_dev_name);
पूर्ण

अटल sमाप_प्रकार trigin_sig_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *ext_attr =
		container_of(attr, काष्ठा dev_ext_attribute, attr);
	काष्ठा cti_trig_con *con = (काष्ठा cti_trig_con *)ext_attr->var;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *cfg = &drvdata->config;
	अचिन्हित दीर्घ mask = con->con_in->used_mask;

	वापस biपंचांगap_prपूर्णांक_to_pagebuf(true, buf, &mask, cfg->nr_trig_max);
पूर्ण

अटल sमाप_प्रकार trigout_sig_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *ext_attr =
		container_of(attr, काष्ठा dev_ext_attribute, attr);
	काष्ठा cti_trig_con *con = (काष्ठा cti_trig_con *)ext_attr->var;
	काष्ठा cti_drvdata *drvdata = dev_get_drvdata(dev->parent);
	काष्ठा cti_config *cfg = &drvdata->config;
	अचिन्हित दीर्घ mask = con->con_out->used_mask;

	वापस biपंचांगap_prपूर्णांक_to_pagebuf(true, buf, &mask, cfg->nr_trig_max);
पूर्ण

/* convert a sig type id to a name */
अटल स्थिर अक्षर *
cti_sig_type_name(काष्ठा cti_trig_con *con, पूर्णांक used_count, bool in)
अणु
	पूर्णांक idx = 0;
	काष्ठा cti_trig_grp *grp = in ? con->con_in : con->con_out;

	अगर (used_count < grp->nr_sigs)
		idx = grp->sig_types[used_count];
	वापस sig_type_names[idx];
पूर्ण

अटल sमाप_प्रकार trigin_type_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *ext_attr =
		container_of(attr, काष्ठा dev_ext_attribute, attr);
	काष्ठा cti_trig_con *con = (काष्ठा cti_trig_con *)ext_attr->var;
	पूर्णांक sig_idx, used = 0;
	स्थिर अक्षर *name;

	क्रम (sig_idx = 0; sig_idx < con->con_in->nr_sigs; sig_idx++) अणु
		name = cti_sig_type_name(con, sig_idx, true);
		used += प्र_लिखो(buf + used, "%s ", name);
	पूर्ण
	used += प्र_लिखो(buf + used, "\n");
	वापस used;
पूर्ण

अटल sमाप_प्रकार trigout_type_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *ext_attr =
		container_of(attr, काष्ठा dev_ext_attribute, attr);
	काष्ठा cti_trig_con *con = (काष्ठा cti_trig_con *)ext_attr->var;
	पूर्णांक sig_idx, used = 0;
	स्थिर अक्षर *name;

	क्रम (sig_idx = 0; sig_idx < con->con_out->nr_sigs; sig_idx++) अणु
		name = cti_sig_type_name(con, sig_idx, false);
		used += प्र_लिखो(buf + used, "%s ", name);
	पूर्ण
	used += प्र_लिखो(buf + used, "\n");
	वापस used;
पूर्ण

/*
 * Array of show function names declared above to allow selection
 * क्रम the connection attributes
 */
अटल p_show_fn show_fns[CTI_CON_ATTR_MAX] = अणु
	con_name_show,
	trigin_sig_show,
	trigout_sig_show,
	trigin_type_show,
	trigout_type_show,
पूर्ण;

अटल पूर्णांक cti_create_con_sysfs_attr(काष्ठा device *dev,
				     काष्ठा cti_trig_con *con,
				     क्रमागत cti_conn_attr_type attr_type,
				     पूर्णांक attr_idx)
अणु
	काष्ठा dev_ext_attribute *eattr;
	अक्षर *name;

	eattr = devm_kzalloc(dev, माप(काष्ठा dev_ext_attribute),
				    GFP_KERNEL);
	अगर (eattr) अणु
		name = devm_kstrdup(dev, con_attr_names[attr_type],
				    GFP_KERNEL);
		अगर (name) अणु
			/* fill out the underlying attribute काष्ठा */
			eattr->attr.attr.name = name;
			eattr->attr.attr.mode = 0444;

			/* now the device_attribute काष्ठा */
			eattr->attr.show = show_fns[attr_type];
		पूर्ण अन्यथा अणु
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -ENOMEM;
	पूर्ण
	eattr->var = con;
	con->con_attrs[attr_idx] = &eattr->attr.attr;
	/*
	 * Initialize the dynamically allocated attribute
	 * to aव्योम LOCKDEP splat. See include/linux/sysfs.h
	 * क्रम more details.
	 */
	sysfs_attr_init(con->con_attrs[attr_idx]);

	वापस 0;
पूर्ण

अटल काष्ठा attribute_group *
cti_create_con_sysfs_group(काष्ठा device *dev, काष्ठा cti_device *ctidev,
			   पूर्णांक con_idx, काष्ठा cti_trig_con *tc)
अणु
	काष्ठा attribute_group *group = शून्य;
	पूर्णांक grp_idx;

	group = devm_kzalloc(dev, माप(काष्ठा attribute_group), GFP_KERNEL);
	अगर (!group)
		वापस शून्य;

	group->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "triggers%d", con_idx);
	अगर (!group->name)
		वापस शून्य;

	grp_idx = con_idx + CORESIGHT_CTI_STATIC_GROUPS_MAX - 1;
	ctidev->con_groups[grp_idx] = group;
	tc->attr_group = group;
	वापस group;
पूर्ण

/* create a triggers connection group and the attributes क्रम that group */
अटल पूर्णांक cti_create_con_attr_set(काष्ठा device *dev, पूर्णांक con_idx,
				   काष्ठा cti_device *ctidev,
				   काष्ठा cti_trig_con *tc)
अणु
	काष्ठा attribute_group *attr_group = शून्य;
	पूर्णांक attr_idx = 0;
	पूर्णांक err = -ENOMEM;

	attr_group = cti_create_con_sysfs_group(dev, ctidev, con_idx, tc);
	अगर (!attr_group)
		वापस -ENOMEM;

	/* allocate शून्य terminated array of attributes */
	tc->con_attrs = devm_kसुस्मृति(dev, CTI_CON_ATTR_MAX + 1,
				     माप(काष्ठा attribute *), GFP_KERNEL);
	अगर (!tc->con_attrs)
		वापस -ENOMEM;

	err = cti_create_con_sysfs_attr(dev, tc, CTI_CON_ATTR_NAME,
					attr_idx++);
	अगर (err)
		वापस err;

	अगर (tc->con_in->nr_sigs > 0) अणु
		err = cti_create_con_sysfs_attr(dev, tc,
						CTI_CON_ATTR_TRIGIN_SIG,
						attr_idx++);
		अगर (err)
			वापस err;

		err = cti_create_con_sysfs_attr(dev, tc,
						CTI_CON_ATTR_TRIGIN_TYPES,
						attr_idx++);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tc->con_out->nr_sigs > 0) अणु
		err = cti_create_con_sysfs_attr(dev, tc,
						CTI_CON_ATTR_TRIGOUT_SIG,
						attr_idx++);
		अगर (err)
			वापस err;

		err = cti_create_con_sysfs_attr(dev, tc,
						CTI_CON_ATTR_TRIGOUT_TYPES,
						attr_idx++);
		अगर (err)
			वापस err;
	पूर्ण
	attr_group->attrs = tc->con_attrs;
	वापस 0;
पूर्ण

/* create the array of group poपूर्णांकers क्रम the CTI sysfs groups */
अटल पूर्णांक cti_create_cons_groups(काष्ठा device *dev, काष्ठा cti_device *ctidev)
अणु
	पूर्णांक nr_groups;

	/* nr groups = dynamic + अटल + शून्य terminator */
	nr_groups = ctidev->nr_trig_con + CORESIGHT_CTI_STATIC_GROUPS_MAX;
	ctidev->con_groups = devm_kसुस्मृति(dev, nr_groups,
					  माप(काष्ठा attribute_group *),
					  GFP_KERNEL);
	अगर (!ctidev->con_groups)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

पूर्णांक cti_create_cons_sysfs(काष्ठा device *dev, काष्ठा cti_drvdata *drvdata)
अणु
	काष्ठा cti_device *ctidev = &drvdata->ctidev;
	पूर्णांक err, con_idx = 0, i;
	काष्ठा cti_trig_con *tc;

	err = cti_create_cons_groups(dev, ctidev);
	अगर (err)
		वापस err;

	/* populate first locations with the अटल set of groups */
	क्रम (i = 0; i < (CORESIGHT_CTI_STATIC_GROUPS_MAX - 1); i++)
		ctidev->con_groups[i] = coresight_cti_groups[i];

	/* add dynamic set क्रम each connection */
	list_क्रम_each_entry(tc, &ctidev->trig_cons, node) अणु
		err = cti_create_con_attr_set(dev, con_idx++, ctidev, tc);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/* attribute and group sysfs tables. */
अटल स्थिर काष्ठा attribute_group coresight_cti_group = अणु
	.attrs = coresight_cti_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_cti_mgmt_group = अणु
	.attrs = coresight_cti_mgmt_attrs,
	.name = "mgmt",
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_cti_regs_group = अणु
	.attrs = coresight_cti_regs_attrs,
	.name = "regs",
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_cti_channels_group = अणु
	.attrs = coresight_cti_channel_attrs,
	.name = "channels",
पूर्ण;

स्थिर काष्ठा attribute_group *
coresight_cti_groups[CORESIGHT_CTI_STATIC_GROUPS_MAX] = अणु
	&coresight_cti_group,
	&coresight_cti_mgmt_group,
	&coresight_cti_regs_group,
	&coresight_cti_channels_group,
	शून्य,
पूर्ण;
