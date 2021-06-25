<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OMAP SmartReflex Voltage Control
 *
 * Author: Thara Gopinath	<thara@ti.com>
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Thara Gopinath <thara@ti.com>
 *
 * Copyright (C) 2008 Nokia Corporation
 * Kalle Jokiniemi
 *
 * Copyright (C) 2007 Texas Instruments, Inc.
 * Lesly A M <x0080970@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/घातer/smartreflex.h>

#घोषणा DRIVER_NAME	"smartreflex"
#घोषणा SMARTREFLEX_NAME_LEN	32
#घोषणा NVALUE_NAME_LEN		40
#घोषणा SR_DISABLE_TIMEOUT	200

/* sr_list contains all the instances of smartreflex module */
अटल LIST_HEAD(sr_list);

अटल काष्ठा omap_sr_class_data *sr_class;
अटल काष्ठा dentry		*sr_dbg_dir;

अटल अंतरभूत व्योम sr_ग_लिखो_reg(काष्ठा omap_sr *sr, अचिन्हित offset, u32 value)
अणु
	__raw_ग_लिखोl(value, (sr->base + offset));
पूर्ण

अटल अंतरभूत व्योम sr_modअगरy_reg(काष्ठा omap_sr *sr, अचिन्हित offset, u32 mask,
					u32 value)
अणु
	u32 reg_val;

	/*
	 * Smartreflex error config रेजिस्टर is special as it contains
	 * certain status bits which अगर written a 1 पूर्णांकo means a clear
	 * of those bits. So in order to make sure no accidental ग_लिखो of
	 * 1 happens to those status bits, करो a clear of them in the पढ़ो
	 * value. This mean this API करोesn't reग_लिखो values in these bits
	 * अगर they are currently set, but करोes allow the caller to ग_लिखो
	 * those bits.
	 */
	अगर (sr->ip_type == SR_TYPE_V1 && offset == ERRCONFIG_V1)
		mask |= ERRCONFIG_STATUS_V1_MASK;
	अन्यथा अगर (sr->ip_type == SR_TYPE_V2 && offset == ERRCONFIG_V2)
		mask |= ERRCONFIG_VPBOUNDINTST_V2;

	reg_val = __raw_पढ़ोl(sr->base + offset);
	reg_val &= ~mask;

	value &= mask;

	reg_val |= value;

	__raw_ग_लिखोl(reg_val, (sr->base + offset));
पूर्ण

अटल अंतरभूत u32 sr_पढ़ो_reg(काष्ठा omap_sr *sr, अचिन्हित offset)
अणु
	वापस __raw_पढ़ोl(sr->base + offset);
पूर्ण

अटल काष्ठा omap_sr *_sr_lookup(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	काष्ठा omap_sr *sr_info;

	अगर (!voltdm) अणु
		pr_err("%s: Null voltage domain passed!\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	list_क्रम_each_entry(sr_info, &sr_list, node) अणु
		अगर (voltdm == sr_info->voltdm)
			वापस sr_info;
	पूर्ण

	वापस ERR_PTR(-ENODATA);
पूर्ण

अटल irqवापस_t sr_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा omap_sr *sr_info = data;
	u32 status = 0;

	चयन (sr_info->ip_type) अणु
	हाल SR_TYPE_V1:
		/* Read the status bits */
		status = sr_पढ़ो_reg(sr_info, ERRCONFIG_V1);

		/* Clear them by writing back */
		sr_ग_लिखो_reg(sr_info, ERRCONFIG_V1, status);
		अवरोध;
	हाल SR_TYPE_V2:
		/* Read the status bits */
		status = sr_पढ़ो_reg(sr_info, IRQSTATUS);

		/* Clear them by writing back */
		sr_ग_लिखो_reg(sr_info, IRQSTATUS, status);
		अवरोध;
	शेष:
		dev_err(&sr_info->pdev->dev, "UNKNOWN IP type %d\n",
			sr_info->ip_type);
		वापस IRQ_NONE;
	पूर्ण

	अगर (sr_class->notअगरy)
		sr_class->notअगरy(sr_info, status);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sr_set_clk_length(काष्ठा omap_sr *sr)
अणु
	काष्ठा clk *fck;
	u32 fclk_speed;

	/* Try पूर्णांकerconnect target module fck first अगर it alपढ़ोy exists */
	fck = clk_get(sr->pdev->dev.parent, "fck");
	अगर (IS_ERR(fck)) अणु
		fck = clk_get(&sr->pdev->dev, "fck");
		अगर (IS_ERR(fck)) अणु
			dev_err(&sr->pdev->dev,
				"%s: unable to get fck for device %s\n",
				__func__, dev_name(&sr->pdev->dev));
			वापस;
		पूर्ण
	पूर्ण

	fclk_speed = clk_get_rate(fck);
	clk_put(fck);

	चयन (fclk_speed) अणु
	हाल 12000000:
		sr->clk_length = SRCLKLENGTH_12MHZ_SYSCLK;
		अवरोध;
	हाल 13000000:
		sr->clk_length = SRCLKLENGTH_13MHZ_SYSCLK;
		अवरोध;
	हाल 19200000:
		sr->clk_length = SRCLKLENGTH_19MHZ_SYSCLK;
		अवरोध;
	हाल 26000000:
		sr->clk_length = SRCLKLENGTH_26MHZ_SYSCLK;
		अवरोध;
	हाल 38400000:
		sr->clk_length = SRCLKLENGTH_38MHZ_SYSCLK;
		अवरोध;
	शेष:
		dev_err(&sr->pdev->dev, "%s: Invalid fclk rate: %d\n",
			__func__, fclk_speed);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sr_start_vddस्वतःcomp(काष्ठा omap_sr *sr)
अणु
	अगर (!sr_class || !(sr_class->enable) || !(sr_class->configure)) अणु
		dev_warn(&sr->pdev->dev,
			 "%s: smartreflex class driver not registered\n",
			 __func__);
		वापस;
	पूर्ण

	अगर (!sr_class->enable(sr))
		sr->स्वतःcomp_active = true;
पूर्ण

अटल व्योम sr_stop_vddस्वतःcomp(काष्ठा omap_sr *sr)
अणु
	अगर (!sr_class || !(sr_class->disable)) अणु
		dev_warn(&sr->pdev->dev,
			 "%s: smartreflex class driver not registered\n",
			 __func__);
		वापस;
	पूर्ण

	अगर (sr->स्वतःcomp_active) अणु
		sr_class->disable(sr, 1);
		sr->स्वतःcomp_active = false;
	पूर्ण
पूर्ण

/*
 * This function handles the initializations which have to be करोne
 * only when both sr device and class driver regiter has
 * completed. This will be attempted to be called from both sr class
 * driver रेजिस्टर and sr device पूर्णांकializtion API's. Only one call
 * will ultimately succeed.
 *
 * Currently this function रेजिस्टरs पूर्णांकerrupt handler क्रम a particular SR
 * अगर smartreflex class driver is alपढ़ोy रेजिस्टरed and has
 * requested क्रम पूर्णांकerrupts and the SR पूर्णांकerrupt line in present.
 */
अटल पूर्णांक sr_late_init(काष्ठा omap_sr *sr_info)
अणु
	काष्ठा omap_sr_data *pdata = sr_info->pdev->dev.platक्रमm_data;
	पूर्णांक ret = 0;

	अगर (sr_class->notअगरy && sr_class->notअगरy_flags && sr_info->irq) अणु
		ret = devm_request_irq(&sr_info->pdev->dev, sr_info->irq,
				       sr_पूर्णांकerrupt, 0, sr_info->name, sr_info);
		अगर (ret)
			जाओ error;
		disable_irq(sr_info->irq);
	पूर्ण

	अगर (pdata && pdata->enable_on_init)
		sr_start_vddस्वतःcomp(sr_info);

	वापस ret;

error:
	list_del(&sr_info->node);
	dev_err(&sr_info->pdev->dev, "%s: ERROR in registering interrupt handler. Smartreflex will not function as desired\n",
		__func__);

	वापस ret;
पूर्ण

अटल व्योम sr_v1_disable(काष्ठा omap_sr *sr)
अणु
	पूर्णांक समयout = 0;
	पूर्णांक errconf_val = ERRCONFIG_MCUACCUMINTST | ERRCONFIG_MCUVALIDINTST |
			ERRCONFIG_MCUBOUNDINTST;

	/* Enable MCUDisableAcknowledge पूर्णांकerrupt */
	sr_modअगरy_reg(sr, ERRCONFIG_V1,
			ERRCONFIG_MCUDISACKINTEN, ERRCONFIG_MCUDISACKINTEN);

	/* SRCONFIG - disable SR */
	sr_modअगरy_reg(sr, SRCONFIG, SRCONFIG_SRENABLE, 0x0);

	/* Disable all other SR पूर्णांकerrupts and clear the status as needed */
	अगर (sr_पढ़ो_reg(sr, ERRCONFIG_V1) & ERRCONFIG_VPBOUNDINTST_V1)
		errconf_val |= ERRCONFIG_VPBOUNDINTST_V1;
	sr_modअगरy_reg(sr, ERRCONFIG_V1,
			(ERRCONFIG_MCUACCUMINTEN | ERRCONFIG_MCUVALIDINTEN |
			ERRCONFIG_MCUBOUNDINTEN | ERRCONFIG_VPBOUNDINTEN_V1),
			errconf_val);

	/*
	 * Wait क्रम SR to be disabled.
	 * रुको until ERRCONFIG.MCUDISACKINTST = 1. Typical latency is 1us.
	 */
	sr_test_cond_समयout((sr_पढ़ो_reg(sr, ERRCONFIG_V1) &
			     ERRCONFIG_MCUDISACKINTST), SR_DISABLE_TIMEOUT,
			     समयout);

	अगर (समयout >= SR_DISABLE_TIMEOUT)
		dev_warn(&sr->pdev->dev, "%s: Smartreflex disable timedout\n",
			 __func__);

	/* Disable MCUDisableAcknowledge पूर्णांकerrupt & clear pending पूर्णांकerrupt */
	sr_modअगरy_reg(sr, ERRCONFIG_V1, ERRCONFIG_MCUDISACKINTEN,
			ERRCONFIG_MCUDISACKINTST);
पूर्ण

अटल व्योम sr_v2_disable(काष्ठा omap_sr *sr)
अणु
	पूर्णांक समयout = 0;

	/* Enable MCUDisableAcknowledge पूर्णांकerrupt */
	sr_ग_लिखो_reg(sr, IRQENABLE_SET, IRQENABLE_MCUDISABLEACKINT);

	/* SRCONFIG - disable SR */
	sr_modअगरy_reg(sr, SRCONFIG, SRCONFIG_SRENABLE, 0x0);

	/*
	 * Disable all other SR पूर्णांकerrupts and clear the status
	 * ग_लिखो to status रेजिस्टर ONLY on need basis - only अगर status
	 * is set.
	 */
	अगर (sr_पढ़ो_reg(sr, ERRCONFIG_V2) & ERRCONFIG_VPBOUNDINTST_V2)
		sr_modअगरy_reg(sr, ERRCONFIG_V2, ERRCONFIG_VPBOUNDINTEN_V2,
			ERRCONFIG_VPBOUNDINTST_V2);
	अन्यथा
		sr_modअगरy_reg(sr, ERRCONFIG_V2, ERRCONFIG_VPBOUNDINTEN_V2,
				0x0);
	sr_ग_लिखो_reg(sr, IRQENABLE_CLR, (IRQENABLE_MCUACCUMINT |
			IRQENABLE_MCUVALIDINT |
			IRQENABLE_MCUBOUNDSINT));
	sr_ग_लिखो_reg(sr, IRQSTATUS, (IRQSTATUS_MCUACCUMINT |
			IRQSTATUS_MCVALIDINT |
			IRQSTATUS_MCBOUNDSINT));

	/*
	 * Wait क्रम SR to be disabled.
	 * रुको until IRQSTATUS.MCUDISACKINTST = 1. Typical latency is 1us.
	 */
	sr_test_cond_समयout((sr_पढ़ो_reg(sr, IRQSTATUS) &
			     IRQSTATUS_MCUDISABLEACKINT), SR_DISABLE_TIMEOUT,
			     समयout);

	अगर (समयout >= SR_DISABLE_TIMEOUT)
		dev_warn(&sr->pdev->dev, "%s: Smartreflex disable timedout\n",
			 __func__);

	/* Disable MCUDisableAcknowledge पूर्णांकerrupt & clear pending पूर्णांकerrupt */
	sr_ग_लिखो_reg(sr, IRQENABLE_CLR, IRQENABLE_MCUDISABLEACKINT);
	sr_ग_लिखो_reg(sr, IRQSTATUS, IRQSTATUS_MCUDISABLEACKINT);
पूर्ण

अटल काष्ठा omap_sr_nvalue_table *sr_retrieve_nvalue_row(
				काष्ठा omap_sr *sr, u32 efuse_offs)
अणु
	पूर्णांक i;

	अगर (!sr->nvalue_table) अणु
		dev_warn(&sr->pdev->dev, "%s: Missing ntarget value table\n",
			 __func__);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < sr->nvalue_count; i++) अणु
		अगर (sr->nvalue_table[i].efuse_offs == efuse_offs)
			वापस &sr->nvalue_table[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/* Public Functions */

/**
 * sr_configure_errgen() - Configures the SmartReflex to perक्रमm AVS using the
 *			 error generator module.
 * @sr:			SR module to be configured.
 *
 * This API is to be called from the smartreflex class driver to
 * configure the error generator module inside the smartreflex module.
 * SR settings अगर using the ERROR module inside Smartreflex.
 * SR CLASS 3 by शेष uses only the ERROR module where as
 * SR CLASS 2 can choose between ERROR module and MINMAXAVG
 * module. Returns 0 on success and error value in हाल of failure.
 */
पूर्णांक sr_configure_errgen(काष्ठा omap_sr *sr)
अणु
	u32 sr_config, sr_errconfig, errconfig_offs;
	u32 vpboundपूर्णांक_en, vpboundपूर्णांक_st;
	u32 senp_en = 0, senn_en = 0;
	u8 senp_shअगरt, senn_shअगरt;

	अगर (!sr) अणु
		pr_warn("%s: NULL omap_sr from %pS\n",
			__func__, (व्योम *)_RET_IP_);
		वापस -EINVAL;
	पूर्ण

	अगर (!sr->clk_length)
		sr_set_clk_length(sr);

	senp_en = sr->senp_mod;
	senn_en = sr->senn_mod;

	sr_config = (sr->clk_length << SRCONFIG_SRCLKLENGTH_SHIFT) |
		SRCONFIG_SENENABLE | SRCONFIG_ERRGEN_EN;

	चयन (sr->ip_type) अणु
	हाल SR_TYPE_V1:
		sr_config |= SRCONFIG_DELAYCTRL;
		senn_shअगरt = SRCONFIG_SENNENABLE_V1_SHIFT;
		senp_shअगरt = SRCONFIG_SENPENABLE_V1_SHIFT;
		errconfig_offs = ERRCONFIG_V1;
		vpboundपूर्णांक_en = ERRCONFIG_VPBOUNDINTEN_V1;
		vpboundपूर्णांक_st = ERRCONFIG_VPBOUNDINTST_V1;
		अवरोध;
	हाल SR_TYPE_V2:
		senn_shअगरt = SRCONFIG_SENNENABLE_V2_SHIFT;
		senp_shअगरt = SRCONFIG_SENPENABLE_V2_SHIFT;
		errconfig_offs = ERRCONFIG_V2;
		vpboundपूर्णांक_en = ERRCONFIG_VPBOUNDINTEN_V2;
		vpboundपूर्णांक_st = ERRCONFIG_VPBOUNDINTST_V2;
		अवरोध;
	शेष:
		dev_err(&sr->pdev->dev, "%s: Trying to Configure smartreflex module without specifying the ip\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	sr_config |= ((senn_en << senn_shअगरt) | (senp_en << senp_shअगरt));
	sr_ग_लिखो_reg(sr, SRCONFIG, sr_config);
	sr_errconfig = (sr->err_weight << ERRCONFIG_ERRWEIGHT_SHIFT) |
		(sr->err_maxlimit << ERRCONFIG_ERRMAXLIMIT_SHIFT) |
		(sr->err_minlimit <<  ERRCONFIG_ERRMINLIMIT_SHIFT);
	sr_modअगरy_reg(sr, errconfig_offs, (SR_ERRWEIGHT_MASK |
		SR_ERRMAXLIMIT_MASK | SR_ERRMINLIMIT_MASK),
		sr_errconfig);

	/* Enabling the पूर्णांकerrupts अगर the ERROR module is used */
	sr_modअगरy_reg(sr, errconfig_offs, (vpboundपूर्णांक_en | vpboundपूर्णांक_st),
		      vpboundपूर्णांक_en);

	वापस 0;
पूर्ण

/**
 * sr_disable_errgen() - Disables SmartReflex AVS module's errgen component
 * @sr:			SR module to be configured.
 *
 * This API is to be called from the smartreflex class driver to
 * disable the error generator module inside the smartreflex module.
 *
 * Returns 0 on success and error value in हाल of failure.
 */
पूर्णांक sr_disable_errgen(काष्ठा omap_sr *sr)
अणु
	u32 errconfig_offs;
	u32 vpboundपूर्णांक_en, vpboundपूर्णांक_st;

	अगर (!sr) अणु
		pr_warn("%s: NULL omap_sr from %pS\n",
			__func__, (व्योम *)_RET_IP_);
		वापस -EINVAL;
	पूर्ण

	चयन (sr->ip_type) अणु
	हाल SR_TYPE_V1:
		errconfig_offs = ERRCONFIG_V1;
		vpboundपूर्णांक_en = ERRCONFIG_VPBOUNDINTEN_V1;
		vpboundपूर्णांक_st = ERRCONFIG_VPBOUNDINTST_V1;
		अवरोध;
	हाल SR_TYPE_V2:
		errconfig_offs = ERRCONFIG_V2;
		vpboundपूर्णांक_en = ERRCONFIG_VPBOUNDINTEN_V2;
		vpboundपूर्णांक_st = ERRCONFIG_VPBOUNDINTST_V2;
		अवरोध;
	शेष:
		dev_err(&sr->pdev->dev, "%s: Trying to Configure smartreflex module without specifying the ip\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	/* Disable the Sensor and errorgen */
	sr_modअगरy_reg(sr, SRCONFIG, SRCONFIG_SENENABLE | SRCONFIG_ERRGEN_EN, 0);

	/*
	 * Disable the पूर्णांकerrupts of ERROR module
	 * NOTE: modअगरy is a पढ़ो, modअगरy,ग_लिखो - an implicit OCP barrier
	 * which is required is present here - sequencing is critical
	 * at this poपूर्णांक (after errgen is disabled, vpboundपूर्णांक disable)
	 */
	sr_modअगरy_reg(sr, errconfig_offs, vpboundपूर्णांक_en | vpboundपूर्णांक_st, 0);

	वापस 0;
पूर्ण

/**
 * sr_configure_minmax() - Configures the SmartReflex to perक्रमm AVS using the
 *			 minmaxavg module.
 * @sr:			SR module to be configured.
 *
 * This API is to be called from the smartreflex class driver to
 * configure the minmaxavg module inside the smartreflex module.
 * SR settings अगर using the ERROR module inside Smartreflex.
 * SR CLASS 3 by शेष uses only the ERROR module where as
 * SR CLASS 2 can choose between ERROR module and MINMAXAVG
 * module. Returns 0 on success and error value in हाल of failure.
 */
पूर्णांक sr_configure_minmax(काष्ठा omap_sr *sr)
अणु
	u32 sr_config, sr_avgwt;
	u32 senp_en = 0, senn_en = 0;
	u8 senp_shअगरt, senn_shअगरt;

	अगर (!sr) अणु
		pr_warn("%s: NULL omap_sr from %pS\n",
			__func__, (व्योम *)_RET_IP_);
		वापस -EINVAL;
	पूर्ण

	अगर (!sr->clk_length)
		sr_set_clk_length(sr);

	senp_en = sr->senp_mod;
	senn_en = sr->senn_mod;

	sr_config = (sr->clk_length << SRCONFIG_SRCLKLENGTH_SHIFT) |
		SRCONFIG_SENENABLE |
		(sr->accum_data << SRCONFIG_ACCUMDATA_SHIFT);

	चयन (sr->ip_type) अणु
	हाल SR_TYPE_V1:
		sr_config |= SRCONFIG_DELAYCTRL;
		senn_shअगरt = SRCONFIG_SENNENABLE_V1_SHIFT;
		senp_shअगरt = SRCONFIG_SENPENABLE_V1_SHIFT;
		अवरोध;
	हाल SR_TYPE_V2:
		senn_shअगरt = SRCONFIG_SENNENABLE_V2_SHIFT;
		senp_shअगरt = SRCONFIG_SENPENABLE_V2_SHIFT;
		अवरोध;
	शेष:
		dev_err(&sr->pdev->dev, "%s: Trying to Configure smartreflex module without specifying the ip\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	sr_config |= ((senn_en << senn_shअगरt) | (senp_en << senp_shअगरt));
	sr_ग_लिखो_reg(sr, SRCONFIG, sr_config);
	sr_avgwt = (sr->senp_avgweight << AVGWEIGHT_SENPAVGWEIGHT_SHIFT) |
		(sr->senn_avgweight << AVGWEIGHT_SENNAVGWEIGHT_SHIFT);
	sr_ग_लिखो_reg(sr, AVGWEIGHT, sr_avgwt);

	/*
	 * Enabling the पूर्णांकerrupts अगर MINMAXAVG module is used.
	 * TODO: check अगर all the पूर्णांकerrupts are mandatory
	 */
	चयन (sr->ip_type) अणु
	हाल SR_TYPE_V1:
		sr_modअगरy_reg(sr, ERRCONFIG_V1,
			(ERRCONFIG_MCUACCUMINTEN | ERRCONFIG_MCUVALIDINTEN |
			ERRCONFIG_MCUBOUNDINTEN),
			(ERRCONFIG_MCUACCUMINTEN | ERRCONFIG_MCUACCUMINTST |
			 ERRCONFIG_MCUVALIDINTEN | ERRCONFIG_MCUVALIDINTST |
			 ERRCONFIG_MCUBOUNDINTEN | ERRCONFIG_MCUBOUNDINTST));
		अवरोध;
	हाल SR_TYPE_V2:
		sr_ग_लिखो_reg(sr, IRQSTATUS,
			IRQSTATUS_MCUACCUMINT | IRQSTATUS_MCVALIDINT |
			IRQSTATUS_MCBOUNDSINT | IRQSTATUS_MCUDISABLEACKINT);
		sr_ग_लिखो_reg(sr, IRQENABLE_SET,
			IRQENABLE_MCUACCUMINT | IRQENABLE_MCUVALIDINT |
			IRQENABLE_MCUBOUNDSINT | IRQENABLE_MCUDISABLEACKINT);
		अवरोध;
	शेष:
		dev_err(&sr->pdev->dev, "%s: Trying to Configure smartreflex module without specifying the ip\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sr_enable() - Enables the smartreflex module.
 * @sr:		poपूर्णांकer to which the SR module to be configured beदीर्घs to.
 * @volt:	The voltage at which the Voltage करोमुख्य associated with
 *		the smartreflex module is operating at.
 *		This is required only to program the correct Ntarget value.
 *
 * This API is to be called from the smartreflex class driver to
 * enable a smartreflex module. Returns 0 on success. Returns error
 * value अगर the voltage passed is wrong or अगर ntarget value is wrong.
 */
पूर्णांक sr_enable(काष्ठा omap_sr *sr, अचिन्हित दीर्घ volt)
अणु
	काष्ठा omap_volt_data *volt_data;
	काष्ठा omap_sr_nvalue_table *nvalue_row;
	पूर्णांक ret;

	अगर (!sr) अणु
		pr_warn("%s: NULL omap_sr from %pS\n",
			__func__, (व्योम *)_RET_IP_);
		वापस -EINVAL;
	पूर्ण

	volt_data = omap_voltage_get_voltdata(sr->voltdm, volt);

	अगर (IS_ERR(volt_data)) अणु
		dev_warn(&sr->pdev->dev, "%s: Unable to get voltage table for nominal voltage %ld\n",
			 __func__, volt);
		वापस PTR_ERR(volt_data);
	पूर्ण

	nvalue_row = sr_retrieve_nvalue_row(sr, volt_data->sr_efuse_offs);

	अगर (!nvalue_row) अणु
		dev_warn(&sr->pdev->dev, "%s: failure getting SR data for this voltage %ld\n",
			 __func__, volt);
		वापस -ENODATA;
	पूर्ण

	/* errminlimit is opp dependent and hence linked to voltage */
	sr->err_minlimit = nvalue_row->errminlimit;

	pm_runसमय_get_sync(&sr->pdev->dev);

	/* Check अगर SR is alपढ़ोy enabled. If yes करो nothing */
	अगर (sr_पढ़ो_reg(sr, SRCONFIG) & SRCONFIG_SRENABLE)
		वापस 0;

	/* Configure SR */
	ret = sr_class->configure(sr);
	अगर (ret)
		वापस ret;

	sr_ग_लिखो_reg(sr, NVALUERECIPROCAL, nvalue_row->nvalue);

	/* SRCONFIG - enable SR */
	sr_modअगरy_reg(sr, SRCONFIG, SRCONFIG_SRENABLE, SRCONFIG_SRENABLE);
	वापस 0;
पूर्ण

/**
 * sr_disable() - Disables the smartreflex module.
 * @sr:		poपूर्णांकer to which the SR module to be configured beदीर्घs to.
 *
 * This API is to be called from the smartreflex class driver to
 * disable a smartreflex module.
 */
व्योम sr_disable(काष्ठा omap_sr *sr)
अणु
	अगर (!sr) अणु
		pr_warn("%s: NULL omap_sr from %pS\n",
			__func__, (व्योम *)_RET_IP_);
		वापस;
	पूर्ण

	/* Check अगर SR घड़ीs are alपढ़ोy disabled. If yes करो nothing */
	अगर (pm_runसमय_suspended(&sr->pdev->dev))
		वापस;

	/*
	 * Disable SR अगर only it is indeed enabled. Else just
	 * disable the घड़ीs.
	 */
	अगर (sr_पढ़ो_reg(sr, SRCONFIG) & SRCONFIG_SRENABLE) अणु
		चयन (sr->ip_type) अणु
		हाल SR_TYPE_V1:
			sr_v1_disable(sr);
			अवरोध;
		हाल SR_TYPE_V2:
			sr_v2_disable(sr);
			अवरोध;
		शेष:
			dev_err(&sr->pdev->dev, "UNKNOWN IP type %d\n",
				sr->ip_type);
		पूर्ण
	पूर्ण

	pm_runसमय_put_sync_suspend(&sr->pdev->dev);
पूर्ण

/**
 * sr_रेजिस्टर_class() - API to रेजिस्टर a smartreflex class parameters.
 * @class_data:	The काष्ठाure containing various sr class specअगरic data.
 *
 * This API is to be called by the smartreflex class driver to रेजिस्टर itself
 * with the smartreflex driver during init. Returns 0 on success अन्यथा the
 * error value.
 */
पूर्णांक sr_रेजिस्टर_class(काष्ठा omap_sr_class_data *class_data)
अणु
	काष्ठा omap_sr *sr_info;

	अगर (!class_data) अणु
		pr_warn("%s:, Smartreflex class data passed is NULL\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (sr_class) अणु
		pr_warn("%s: Smartreflex class driver already registered\n",
			__func__);
		वापस -EBUSY;
	पूर्ण

	sr_class = class_data;

	/*
	 * Call पूर्णांकo late init to करो initializations that require
	 * both sr driver and sr class driver to be initiallized.
	 */
	list_क्रम_each_entry(sr_info, &sr_list, node)
		sr_late_init(sr_info);

	वापस 0;
पूर्ण

/**
 * omap_sr_enable() -  API to enable SR घड़ीs and to call पूर्णांकo the
 *			रेजिस्टरed smartreflex class enable API.
 * @voltdm:	VDD poपूर्णांकer to which the SR module to be configured beदीर्घs to.
 *
 * This API is to be called from the kernel in order to enable
 * a particular smartreflex module. This API will करो the initial
 * configurations to turn on the smartreflex module and in turn call
 * पूर्णांकo the रेजिस्टरed smartreflex class enable API.
 */
व्योम omap_sr_enable(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	काष्ठा omap_sr *sr = _sr_lookup(voltdm);

	अगर (IS_ERR(sr)) अणु
		pr_warn("%s: omap_sr struct for voltdm not found\n", __func__);
		वापस;
	पूर्ण

	अगर (!sr->स्वतःcomp_active)
		वापस;

	अगर (!sr_class || !(sr_class->enable) || !(sr_class->configure)) अणु
		dev_warn(&sr->pdev->dev, "%s: smartreflex class driver not registered\n",
			 __func__);
		वापस;
	पूर्ण

	sr_class->enable(sr);
पूर्ण

/**
 * omap_sr_disable() - API to disable SR without resetting the voltage
 *			processor voltage
 * @voltdm:	VDD poपूर्णांकer to which the SR module to be configured beदीर्घs to.
 *
 * This API is to be called from the kernel in order to disable
 * a particular smartreflex module. This API will in turn call
 * पूर्णांकo the रेजिस्टरed smartreflex class disable API. This API will tell
 * the smartreflex class disable not to reset the VP voltage after
 * disabling smartreflex.
 */
व्योम omap_sr_disable(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	काष्ठा omap_sr *sr = _sr_lookup(voltdm);

	अगर (IS_ERR(sr)) अणु
		pr_warn("%s: omap_sr struct for voltdm not found\n", __func__);
		वापस;
	पूर्ण

	अगर (!sr->स्वतःcomp_active)
		वापस;

	अगर (!sr_class || !(sr_class->disable)) अणु
		dev_warn(&sr->pdev->dev, "%s: smartreflex class driver not registered\n",
			 __func__);
		वापस;
	पूर्ण

	sr_class->disable(sr, 0);
पूर्ण

/**
 * omap_sr_disable_reset_volt() - API to disable SR and reset the
 *				voltage processor voltage
 * @voltdm:	VDD poपूर्णांकer to which the SR module to be configured beदीर्घs to.
 *
 * This API is to be called from the kernel in order to disable
 * a particular smartreflex module. This API will in turn call
 * पूर्णांकo the रेजिस्टरed smartreflex class disable API. This API will tell
 * the smartreflex class disable to reset the VP voltage after
 * disabling smartreflex.
 */
व्योम omap_sr_disable_reset_volt(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	काष्ठा omap_sr *sr = _sr_lookup(voltdm);

	अगर (IS_ERR(sr)) अणु
		pr_warn("%s: omap_sr struct for voltdm not found\n", __func__);
		वापस;
	पूर्ण

	अगर (!sr->स्वतःcomp_active)
		वापस;

	अगर (!sr_class || !(sr_class->disable)) अणु
		dev_warn(&sr->pdev->dev, "%s: smartreflex class driver not registered\n",
			 __func__);
		वापस;
	पूर्ण

	sr_class->disable(sr, 1);
पूर्ण

/* PM Debug FS entries to enable and disable smartreflex. */
अटल पूर्णांक omap_sr_स्वतःcomp_show(व्योम *data, u64 *val)
अणु
	काष्ठा omap_sr *sr_info = data;

	अगर (!sr_info) अणु
		pr_warn("%s: omap_sr struct not found\n", __func__);
		वापस -EINVAL;
	पूर्ण

	*val = sr_info->स्वतःcomp_active;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_sr_स्वतःcomp_store(व्योम *data, u64 val)
अणु
	काष्ठा omap_sr *sr_info = data;

	अगर (!sr_info) अणु
		pr_warn("%s: omap_sr struct not found\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Sanity check */
	अगर (val > 1) अणु
		pr_warn("%s: Invalid argument %lld\n", __func__, val);
		वापस -EINVAL;
	पूर्ण

	/* control enable/disable only अगर there is a delta in value */
	अगर (sr_info->स्वतःcomp_active != val) अणु
		अगर (!val)
			sr_stop_vddस्वतःcomp(sr_info);
		अन्यथा
			sr_start_vddस्वतःcomp(sr_info);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(pm_sr_fops, omap_sr_स्वतःcomp_show,
			omap_sr_स्वतःcomp_store, "%llu\n");

अटल पूर्णांक omap_sr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_sr *sr_info;
	काष्ठा omap_sr_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा resource *mem, *irq;
	काष्ठा dentry *nvalue_dir;
	पूर्णांक i, ret = 0;

	sr_info = devm_kzalloc(&pdev->dev, माप(काष्ठा omap_sr), GFP_KERNEL);
	अगर (!sr_info)
		वापस -ENOMEM;

	sr_info->name = devm_kzalloc(&pdev->dev,
				     SMARTREFLEX_NAME_LEN, GFP_KERNEL);
	अगर (!sr_info->name)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, sr_info);

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "%s: platform data missing\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	sr_info->base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(sr_info->base)) अणु
		dev_err(&pdev->dev, "%s: ioremap fail\n", __func__);
		वापस PTR_ERR(sr_info->base);
	पूर्ण

	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_irq_safe(&pdev->dev);

	snम_लिखो(sr_info->name, SMARTREFLEX_NAME_LEN, "%s", pdata->name);

	sr_info->pdev = pdev;
	sr_info->srid = pdev->id;
	sr_info->voltdm = pdata->voltdm;
	sr_info->nvalue_table = pdata->nvalue_table;
	sr_info->nvalue_count = pdata->nvalue_count;
	sr_info->senn_mod = pdata->senn_mod;
	sr_info->senp_mod = pdata->senp_mod;
	sr_info->err_weight = pdata->err_weight;
	sr_info->err_maxlimit = pdata->err_maxlimit;
	sr_info->accum_data = pdata->accum_data;
	sr_info->senn_avgweight = pdata->senn_avgweight;
	sr_info->senp_avgweight = pdata->senp_avgweight;
	sr_info->स्वतःcomp_active = false;
	sr_info->ip_type = pdata->ip_type;

	अगर (irq)
		sr_info->irq = irq->start;

	sr_set_clk_length(sr_info);

	list_add(&sr_info->node, &sr_list);

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		जाओ err_list_del;
	पूर्ण

	/*
	 * Call पूर्णांकo late init to करो initializations that require
	 * both sr driver and sr class driver to be initiallized.
	 */
	अगर (sr_class) अणु
		ret = sr_late_init(sr_info);
		अगर (ret) अणु
			pr_warn("%s: Error in SR late init\n", __func__);
			जाओ err_list_del;
		पूर्ण
	पूर्ण

	dev_info(&pdev->dev, "%s: SmartReflex driver initialized\n", __func__);
	अगर (!sr_dbg_dir)
		sr_dbg_dir = debugfs_create_dir("smartreflex", शून्य);

	sr_info->dbg_dir = debugfs_create_dir(sr_info->name, sr_dbg_dir);

	debugfs_create_file("autocomp", S_IRUGO | S_IWUSR, sr_info->dbg_dir,
			    sr_info, &pm_sr_fops);
	debugfs_create_x32("errweight", S_IRUGO, sr_info->dbg_dir,
			   &sr_info->err_weight);
	debugfs_create_x32("errmaxlimit", S_IRUGO, sr_info->dbg_dir,
			   &sr_info->err_maxlimit);

	nvalue_dir = debugfs_create_dir("nvalue", sr_info->dbg_dir);

	अगर (sr_info->nvalue_count == 0 || !sr_info->nvalue_table) अणु
		dev_warn(&pdev->dev, "%s: %s: No Voltage table for the corresponding vdd. Cannot create debugfs entries for n-values\n",
			 __func__, sr_info->name);

		ret = -ENODATA;
		जाओ err_debugfs;
	पूर्ण

	क्रम (i = 0; i < sr_info->nvalue_count; i++) अणु
		अक्षर name[NVALUE_NAME_LEN + 1];

		snम_लिखो(name, माप(name), "volt_%lu",
				sr_info->nvalue_table[i].volt_nominal);
		debugfs_create_x32(name, S_IRUGO | S_IWUSR, nvalue_dir,
				   &(sr_info->nvalue_table[i].nvalue));
		snम_लिखो(name, माप(name), "errminlimit_%lu",
			 sr_info->nvalue_table[i].volt_nominal);
		debugfs_create_x32(name, S_IRUGO | S_IWUSR, nvalue_dir,
				   &(sr_info->nvalue_table[i].errminlimit));

	पूर्ण

	pm_runसमय_put_sync(&pdev->dev);

	वापस ret;

err_debugfs:
	debugfs_हटाओ_recursive(sr_info->dbg_dir);
err_list_del:
	list_del(&sr_info->node);

	pm_runसमय_put_sync(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_sr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_sr_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा omap_sr *sr_info;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "%s: platform data missing\n", __func__);
		वापस -EINVAL;
	पूर्ण

	sr_info = _sr_lookup(pdata->voltdm);
	अगर (IS_ERR(sr_info)) अणु
		dev_warn(&pdev->dev, "%s: omap_sr struct not found\n",
			__func__);
		वापस PTR_ERR(sr_info);
	पूर्ण

	अगर (sr_info->स्वतःcomp_active)
		sr_stop_vddस्वतःcomp(sr_info);
	debugfs_हटाओ_recursive(sr_info->dbg_dir);

	pm_runसमय_disable(&pdev->dev);
	list_del(&sr_info->node);
	वापस 0;
पूर्ण

अटल व्योम omap_sr_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_sr_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा omap_sr *sr_info;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "%s: platform data missing\n", __func__);
		वापस;
	पूर्ण

	sr_info = _sr_lookup(pdata->voltdm);
	अगर (IS_ERR(sr_info)) अणु
		dev_warn(&pdev->dev, "%s: omap_sr struct not found\n",
			__func__);
		वापस;
	पूर्ण

	अगर (sr_info->स्वतःcomp_active)
		sr_stop_vddस्वतःcomp(sr_info);

	वापस;
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_sr_match[] = अणु
	अणु .compatible = "ti,omap3-smartreflex-core", पूर्ण,
	अणु .compatible = "ti,omap3-smartreflex-mpu-iva", पूर्ण,
	अणु .compatible = "ti,omap4-smartreflex-core", पूर्ण,
	अणु .compatible = "ti,omap4-smartreflex-mpu", पूर्ण,
	अणु .compatible = "ti,omap4-smartreflex-iva", पूर्ण,
	अणु  पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_sr_match);

अटल काष्ठा platक्रमm_driver smartreflex_driver = अणु
	.probe		= omap_sr_probe,
	.हटाओ         = omap_sr_हटाओ,
	.shutकरोwn	= omap_sr_shutकरोwn,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.of_match_table	= omap_sr_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sr_init(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = platक्रमm_driver_रेजिस्टर(&smartreflex_driver);
	अगर (ret) अणु
		pr_err("%s: platform driver register failed for SR\n",
		       __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
late_initcall(sr_init);

अटल व्योम __निकास sr_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&smartreflex_driver);
पूर्ण
module_निकास(sr_निकास);

MODULE_DESCRIPTION("OMAP Smartreflex Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_AUTHOR("Texas Instruments Inc");
