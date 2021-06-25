<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश "common.h"

#समावेश "voltage.h"
#समावेश "vp.h"
#समावेश "prm-regbits-34xx.h"
#समावेश "prm-regbits-44xx.h"
#समावेश "prm44xx.h"

अटल u32 _vp_set_init_voltage(काष्ठा voltageकरोमुख्य *voltdm, u32 volt)
अणु
	काष्ठा omap_vp_instance *vp = voltdm->vp;
	u32 vpconfig;
	अक्षर vsel;

	vsel = voltdm->pmic->uv_to_vsel(volt);

	vpconfig = voltdm->पढ़ो(vp->vpconfig);
	vpconfig &= ~(vp->common->vpconfig_initvoltage_mask |
		      vp->common->vpconfig_क्रमceupdate |
		      vp->common->vpconfig_initvdd);
	vpconfig |= vsel << __ffs(vp->common->vpconfig_initvoltage_mask);
	voltdm->ग_लिखो(vpconfig, vp->vpconfig);

	/* Trigger initVDD value copy to voltage processor */
	voltdm->ग_लिखो((vpconfig | vp->common->vpconfig_initvdd),
		       vp->vpconfig);

	/* Clear initVDD copy trigger bit */
	voltdm->ग_लिखो(vpconfig, vp->vpconfig);

	वापस vpconfig;
पूर्ण

/* Generic voltage init functions */
व्योम __init omap_vp_init(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	काष्ठा omap_vp_instance *vp = voltdm->vp;
	u32 val, sys_clk_rate, समयout, रुकोसमय;
	u32 vddmin, vddmax, vstepmin, vstepmax;

	अगर (!voltdm->pmic || !voltdm->pmic->uv_to_vsel) अणु
		pr_err("%s: No PMIC info for vdd_%s\n", __func__, voltdm->name);
		वापस;
	पूर्ण

	अगर (!voltdm->पढ़ो || !voltdm->ग_लिखो) अणु
		pr_err("%s: No read/write API for accessing vdd_%s regs\n",
			__func__, voltdm->name);
		वापस;
	पूर्ण

	vp->enabled = false;

	/* Divide to aव्योम overflow */
	sys_clk_rate = voltdm->sys_clk.rate / 1000;

	समयout = (sys_clk_rate * voltdm->pmic->vp_समयout_us) / 1000;
	vddmin = max(voltdm->vp_param->vddmin, voltdm->pmic->vddmin);
	vddmax = min(voltdm->vp_param->vddmax, voltdm->pmic->vddmax);
	vddmin = voltdm->pmic->uv_to_vsel(vddmin);
	vddmax = voltdm->pmic->uv_to_vsel(vddmax);

	रुकोसमय = DIV_ROUND_UP(voltdm->pmic->step_size * sys_clk_rate,
				1000 * voltdm->pmic->slew_rate);
	vstepmin = voltdm->pmic->vp_vstepmin;
	vstepmax = voltdm->pmic->vp_vstepmax;

	/*
	 * VP_CONFIG: error gain is not set here, it will be updated
	 * on each scale, based on OPP.
	 */
	val = (voltdm->pmic->vp_erroroffset <<
	       __ffs(voltdm->vp->common->vpconfig_erroroffset_mask)) |
		vp->common->vpconfig_समयouten;
	voltdm->ग_लिखो(val, vp->vpconfig);

	/* VSTEPMIN */
	val = (रुकोसमय << vp->common->vstepmin_smpsरुकोसमयmin_shअगरt) |
		(vstepmin <<  vp->common->vstepmin_stepmin_shअगरt);
	voltdm->ग_लिखो(val, vp->vstepmin);

	/* VSTEPMAX */
	val = (vstepmax << vp->common->vstepmax_stepmax_shअगरt) |
		(रुकोसमय << vp->common->vstepmax_smpsरुकोसमयmax_shअगरt);
	voltdm->ग_लिखो(val, vp->vstepmax);

	/* VLIMITTO */
	val = (vddmax << vp->common->vlimitto_vddmax_shअगरt) |
		(vddmin << vp->common->vlimitto_vddmin_shअगरt) |
		(समयout <<  vp->common->vlimitto_समयout_shअगरt);
	voltdm->ग_लिखो(val, vp->vlimitto);
पूर्ण

पूर्णांक omap_vp_update_errorgain(काष्ठा voltageकरोमुख्य *voltdm,
			     अचिन्हित दीर्घ target_volt)
अणु
	काष्ठा omap_volt_data *volt_data;

	अगर (!voltdm->vp)
		वापस -EINVAL;

	/* Get volt_data corresponding to target_volt */
	volt_data = omap_voltage_get_voltdata(voltdm, target_volt);
	अगर (IS_ERR(volt_data))
		वापस -EINVAL;

	/* Setting vp errorgain based on the voltage */
	voltdm->rmw(voltdm->vp->common->vpconfig_errorgain_mask,
		    volt_data->vp_errgain <<
		    __ffs(voltdm->vp->common->vpconfig_errorgain_mask),
		    voltdm->vp->vpconfig);

	वापस 0;
पूर्ण

/* VP क्रमce update method of voltage scaling */
पूर्णांक omap_vp_क्रमceupdate_scale(काष्ठा voltageकरोमुख्य *voltdm,
			      अचिन्हित दीर्घ target_volt)
अणु
	काष्ठा omap_vp_instance *vp = voltdm->vp;
	u32 vpconfig;
	u8 target_vsel, current_vsel;
	पूर्णांक ret, समयout = 0;

	ret = omap_vc_pre_scale(voltdm, target_volt, &target_vsel, &current_vsel);
	अगर (ret)
		वापस ret;

	/*
	 * Clear all pending TransactionDone पूर्णांकerrupt/status. Typical latency
	 * is <3us
	 */
	जबतक (समयout++ < VP_TRANXDONE_TIMEOUT) अणु
		vp->common->ops->clear_txकरोne(vp->id);
		अगर (!vp->common->ops->check_txकरोne(vp->id))
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (समयout >= VP_TRANXDONE_TIMEOUT) अणु
		pr_warn("%s: vdd_%s TRANXDONE timeout exceeded. Voltage change aborted\n",
			__func__, voltdm->name);
		वापस -ETIMEDOUT;
	पूर्ण

	vpconfig = _vp_set_init_voltage(voltdm, target_volt);

	/* Force update of voltage */
	voltdm->ग_लिखो(vpconfig | vp->common->vpconfig_क्रमceupdate,
		      voltdm->vp->vpconfig);

	/*
	 * Wait क्रम TransactionDone. Typical latency is <200us.
	 * Depends on SMPSWAITTIMEMIN/MAX and voltage change
	 */
	समयout = 0;
	omap_test_समयout(vp->common->ops->check_txकरोne(vp->id),
			  VP_TRANXDONE_TIMEOUT, समयout);
	अगर (समयout >= VP_TRANXDONE_TIMEOUT)
		pr_err("%s: vdd_%s TRANXDONE timeout exceeded. TRANXDONE never got set after the voltage update\n",
		       __func__, voltdm->name);

	omap_vc_post_scale(voltdm, target_volt, target_vsel, current_vsel);

	/*
	 * Disable TransactionDone पूर्णांकerrupt , clear all status, clear
	 * control रेजिस्टरs
	 */
	समयout = 0;
	जबतक (समयout++ < VP_TRANXDONE_TIMEOUT) अणु
		vp->common->ops->clear_txकरोne(vp->id);
		अगर (!vp->common->ops->check_txकरोne(vp->id))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (समयout >= VP_TRANXDONE_TIMEOUT)
		pr_warn("%s: vdd_%s TRANXDONE timeout exceeded while trying to clear the TRANXDONE status\n",
			__func__, voltdm->name);

	/* Clear क्रमce bit */
	voltdm->ग_लिखो(vpconfig, vp->vpconfig);

	वापस 0;
पूर्ण

/**
 * omap_vp_enable() - API to enable a particular VP
 * @voltdm:	poपूर्णांकer to the VDD whose VP is to be enabled.
 *
 * This API enables a particular voltage processor. Needed by the smartreflex
 * class drivers.
 */
व्योम omap_vp_enable(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	काष्ठा omap_vp_instance *vp;
	u32 vpconfig, volt;

	अगर (!voltdm || IS_ERR(voltdm)) अणु
		pr_warn("%s: VDD specified does not exist!\n", __func__);
		वापस;
	पूर्ण

	vp = voltdm->vp;
	अगर (!voltdm->पढ़ो || !voltdm->ग_लिखो) अणु
		pr_err("%s: No read/write API for accessing vdd_%s regs\n",
			__func__, voltdm->name);
		वापस;
	पूर्ण

	/* If VP is alपढ़ोy enabled, करो nothing. Return */
	अगर (vp->enabled)
		वापस;

	volt = voltdm_get_voltage(voltdm);
	अगर (!volt) अणु
		pr_warn("%s: unable to find current voltage for %s\n",
			__func__, voltdm->name);
		वापस;
	पूर्ण

	vpconfig = _vp_set_init_voltage(voltdm, volt);

	/* Enable VP */
	vpconfig |= vp->common->vpconfig_vpenable;
	voltdm->ग_लिखो(vpconfig, vp->vpconfig);

	vp->enabled = true;
पूर्ण

/**
 * omap_vp_disable() - API to disable a particular VP
 * @voltdm:	poपूर्णांकer to the VDD whose VP is to be disabled.
 *
 * This API disables a particular voltage processor. Needed by the smartreflex
 * class drivers.
 */
व्योम omap_vp_disable(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	काष्ठा omap_vp_instance *vp;
	u32 vpconfig;
	पूर्णांक समयout;

	अगर (!voltdm || IS_ERR(voltdm)) अणु
		pr_warn("%s: VDD specified does not exist!\n", __func__);
		वापस;
	पूर्ण

	vp = voltdm->vp;
	अगर (!voltdm->पढ़ो || !voltdm->ग_लिखो) अणु
		pr_err("%s: No read/write API for accessing vdd_%s regs\n",
			__func__, voltdm->name);
		वापस;
	पूर्ण

	/* If VP is alपढ़ोy disabled, करो nothing. Return */
	अगर (!vp->enabled) अणु
		pr_warn("%s: Trying to disable VP for vdd_%s when it is already disabled\n",
			__func__, voltdm->name);
		वापस;
	पूर्ण

	/* Disable VP */
	vpconfig = voltdm->पढ़ो(vp->vpconfig);
	vpconfig &= ~vp->common->vpconfig_vpenable;
	voltdm->ग_लिखो(vpconfig, vp->vpconfig);

	/*
	 * Wait क्रम VP idle Typical latency is <2us. Maximum latency is ~100us
	 */
	omap_test_समयout((voltdm->पढ़ो(vp->vstatus)),
			  VP_IDLE_TIMEOUT, समयout);

	अगर (समयout >= VP_IDLE_TIMEOUT)
		pr_warn("%s: vdd_%s idle timedout\n", __func__, voltdm->name);

	vp->enabled = false;

	वापस;
पूर्ण
