<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx Zynq MPSoC Firmware layer
 *
 *  Copyright (C) 2014-2021 Xilinx, Inc.
 *
 *  Michal Simek <michal.simek@xilinx.com>
 *  Davorin Mista <davorin.mista@aggios.com>
 *  Jolly Shah <jollys@xilinx.com>
 *  Rajan Vaja <rajanv@xilinx.com>
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/compiler.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hashtable.h>

#समावेश <linux/firmware/xlnx-zynqmp.h>
#समावेश "zynqmp-debug.h"

/* Max HashMap Order क्रम PM API feature check (1<<7 = 128) */
#घोषणा PM_API_FEATURE_CHECK_MAX_ORDER  7

अटल bool feature_check_enabled;
अटल DEFINE_HASHTABLE(pm_api_features_map, PM_API_FEATURE_CHECK_MAX_ORDER);

/**
 * काष्ठा pm_api_feature_data - PM API Feature data
 * @pm_api_id:		PM API Id, used as key to index पूर्णांकo hashmap
 * @feature_status:	status of PM API feature: valid, invalid
 * @hentry:		hlist_node that hooks this entry पूर्णांकo hashtable
 */
काष्ठा pm_api_feature_data अणु
	u32 pm_api_id;
	पूर्णांक feature_status;
	काष्ठा hlist_node hentry;
पूर्ण;

अटल स्थिर काष्ठा mfd_cell firmware_devs[] = अणु
	अणु
		.name = "zynqmp_power_controller",
	पूर्ण,
पूर्ण;

/**
 * zynqmp_pm_ret_code() - Convert PMU-FW error codes to Linux error codes
 * @ret_status:		PMUFW वापस code
 *
 * Return: corresponding Linux error code
 */
अटल पूर्णांक zynqmp_pm_ret_code(u32 ret_status)
अणु
	चयन (ret_status) अणु
	हाल XST_PM_SUCCESS:
	हाल XST_PM_DOUBLE_REQ:
		वापस 0;
	हाल XST_PM_NO_FEATURE:
		वापस -ENOTSUPP;
	हाल XST_PM_NO_ACCESS:
		वापस -EACCES;
	हाल XST_PM_ABORT_SUSPEND:
		वापस -ECANCELED;
	हाल XST_PM_MULT_USER:
		वापस -EUSERS;
	हाल XST_PM_INTERNAL:
	हाल XST_PM_CONFLICT:
	हाल XST_PM_INVALID_NODE:
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल noअंतरभूत पूर्णांक करो_fw_call_fail(u64 arg0, u64 arg1, u64 arg2,
				    u32 *ret_payload)
अणु
	वापस -ENODEV;
पूर्ण

/*
 * PM function call wrapper
 * Invoke करो_fw_call_smc or करो_fw_call_hvc, depending on the configuration
 */
अटल पूर्णांक (*करो_fw_call)(u64, u64, u64, u32 *ret_payload) = करो_fw_call_fail;

/**
 * करो_fw_call_smc() - Call प्रणाली-level platक्रमm management layer (SMC)
 * @arg0:		Argument 0 to SMC call
 * @arg1:		Argument 1 to SMC call
 * @arg2:		Argument 2 to SMC call
 * @ret_payload:	Returned value array
 *
 * Invoke platक्रमm management function via SMC call (no hypervisor present).
 *
 * Return: Returns status, either success or error+reason
 */
अटल noअंतरभूत पूर्णांक करो_fw_call_smc(u64 arg0, u64 arg1, u64 arg2,
				   u32 *ret_payload)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(arg0, arg1, arg2, 0, 0, 0, 0, 0, &res);

	अगर (ret_payload) अणु
		ret_payload[0] = lower_32_bits(res.a0);
		ret_payload[1] = upper_32_bits(res.a0);
		ret_payload[2] = lower_32_bits(res.a1);
		ret_payload[3] = upper_32_bits(res.a1);
	पूर्ण

	वापस zynqmp_pm_ret_code((क्रमागत pm_ret_status)res.a0);
पूर्ण

/**
 * करो_fw_call_hvc() - Call प्रणाली-level platक्रमm management layer (HVC)
 * @arg0:		Argument 0 to HVC call
 * @arg1:		Argument 1 to HVC call
 * @arg2:		Argument 2 to HVC call
 * @ret_payload:	Returned value array
 *
 * Invoke platक्रमm management function via HVC
 * HVC-based क्रम communication through hypervisor
 * (no direct communication with ATF).
 *
 * Return: Returns status, either success or error+reason
 */
अटल noअंतरभूत पूर्णांक करो_fw_call_hvc(u64 arg0, u64 arg1, u64 arg2,
				   u32 *ret_payload)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_hvc(arg0, arg1, arg2, 0, 0, 0, 0, 0, &res);

	अगर (ret_payload) अणु
		ret_payload[0] = lower_32_bits(res.a0);
		ret_payload[1] = upper_32_bits(res.a0);
		ret_payload[2] = lower_32_bits(res.a1);
		ret_payload[3] = upper_32_bits(res.a1);
	पूर्ण

	वापस zynqmp_pm_ret_code((क्रमागत pm_ret_status)res.a0);
पूर्ण

/**
 * zynqmp_pm_feature() - Check weather given feature is supported or not
 * @api_id:		API ID to check
 *
 * Return: Returns status, either success or error+reason
 */
अटल पूर्णांक zynqmp_pm_feature(u32 api_id)
अणु
	पूर्णांक ret;
	u32 ret_payload[PAYLOAD_ARG_CNT];
	u64 smc_arg[2];
	काष्ठा pm_api_feature_data *feature_data;

	अगर (!feature_check_enabled)
		वापस 0;

	/* Check क्रम existing entry in hash table क्रम given api */
	hash_क्रम_each_possible(pm_api_features_map, feature_data, hentry,
			       api_id) अणु
		अगर (feature_data->pm_api_id == api_id)
			वापस feature_data->feature_status;
	पूर्ण

	/* Add new entry अगर not present */
	feature_data = kदो_स्मृति(माप(*feature_data), GFP_KERNEL);
	अगर (!feature_data)
		वापस -ENOMEM;

	feature_data->pm_api_id = api_id;
	smc_arg[0] = PM_SIP_SVC | PM_FEATURE_CHECK;
	smc_arg[1] = api_id;

	ret = करो_fw_call(smc_arg[0], smc_arg[1], 0, ret_payload);
	अगर (ret)
		ret = -EOPNOTSUPP;
	अन्यथा
		ret = ret_payload[1];

	feature_data->feature_status = ret;
	hash_add(pm_api_features_map, &feature_data->hentry, api_id);

	वापस ret;
पूर्ण

/**
 * zynqmp_pm_invoke_fn() - Invoke the प्रणाली-level platक्रमm management layer
 *			   caller function depending on the configuration
 * @pm_api_id:		Requested PM-API call
 * @arg0:		Argument 0 to requested PM-API call
 * @arg1:		Argument 1 to requested PM-API call
 * @arg2:		Argument 2 to requested PM-API call
 * @arg3:		Argument 3 to requested PM-API call
 * @ret_payload:	Returned value array
 *
 * Invoke platक्रमm management function क्रम SMC or HVC call, depending on
 * configuration.
 * Following SMC Calling Convention (SMCCC) क्रम SMC64:
 * Pm Function Identअगरier,
 * PM_SIP_SVC + PM_API_ID =
 *	((SMC_TYPE_FAST << FUNCID_TYPE_SHIFT)
 *	((SMC_64) << FUNCID_CC_SHIFT)
 *	((SIP_START) << FUNCID_OEN_SHIFT)
 *	((PM_API_ID) & FUNCID_NUM_MASK))
 *
 * PM_SIP_SVC	- Registered ZynqMP SIP Service Call.
 * PM_API_ID	- Platक्रमm Management API ID.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_invoke_fn(u32 pm_api_id, u32 arg0, u32 arg1,
			u32 arg2, u32 arg3, u32 *ret_payload)
अणु
	/*
	 * Added SIP service call Function Identअगरier
	 * Make sure to stay in x0 रेजिस्टर
	 */
	u64 smc_arg[4];
	पूर्णांक ret;

	/* Check अगर feature is supported or not */
	ret = zynqmp_pm_feature(pm_api_id);
	अगर (ret < 0)
		वापस ret;

	smc_arg[0] = PM_SIP_SVC | pm_api_id;
	smc_arg[1] = ((u64)arg1 << 32) | arg0;
	smc_arg[2] = ((u64)arg3 << 32) | arg2;

	वापस करो_fw_call(smc_arg[0], smc_arg[1], smc_arg[2], ret_payload);
पूर्ण

अटल u32 pm_api_version;
अटल u32 pm_tz_version;

/**
 * zynqmp_pm_get_api_version() - Get version number of PMU PM firmware
 * @version:	Returned version value
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_get_api_version(u32 *version)
अणु
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	अगर (!version)
		वापस -EINVAL;

	/* Check is PM API version alपढ़ोy verअगरied */
	अगर (pm_api_version > 0) अणु
		*version = pm_api_version;
		वापस 0;
	पूर्ण
	ret = zynqmp_pm_invoke_fn(PM_GET_API_VERSION, 0, 0, 0, 0, ret_payload);
	*version = ret_payload[1];

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_get_api_version);

/**
 * zynqmp_pm_get_chipid - Get silicon ID रेजिस्टरs
 * @idcode:     IDCODE रेजिस्टर
 * @version:    version रेजिस्टर
 *
 * Return:      Returns the status of the operation and the idcode and version
 *              रेजिस्टरs in @idcode and @version.
 */
पूर्णांक zynqmp_pm_get_chipid(u32 *idcode, u32 *version)
अणु
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	अगर (!idcode || !version)
		वापस -EINVAL;

	ret = zynqmp_pm_invoke_fn(PM_GET_CHIPID, 0, 0, 0, 0, ret_payload);
	*idcode = ret_payload[1];
	*version = ret_payload[2];

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_get_chipid);

/**
 * zynqmp_pm_get_trustzone_version() - Get secure trustzone firmware version
 * @version:	Returned version value
 *
 * Return: Returns status, either success or error+reason
 */
अटल पूर्णांक zynqmp_pm_get_trustzone_version(u32 *version)
अणु
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	अगर (!version)
		वापस -EINVAL;

	/* Check is PM trustzone version alपढ़ोy verअगरied */
	अगर (pm_tz_version > 0) अणु
		*version = pm_tz_version;
		वापस 0;
	पूर्ण
	ret = zynqmp_pm_invoke_fn(PM_GET_TRUSTZONE_VERSION, 0, 0,
				  0, 0, ret_payload);
	*version = ret_payload[1];

	वापस ret;
पूर्ण

/**
 * get_set_conduit_method() - Choose SMC or HVC based communication
 * @np:		Poपूर्णांकer to the device_node काष्ठाure
 *
 * Use SMC or HVC-based functions to communicate with EL2/EL3.
 *
 * Return: Returns 0 on success or error code
 */
अटल पूर्णांक get_set_conduit_method(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *method;

	अगर (of_property_पढ़ो_string(np, "method", &method)) अणु
		pr_warn("%s missing \"method\" property\n", __func__);
		वापस -ENXIO;
	पूर्ण

	अगर (!म_भेद("hvc", method)) अणु
		करो_fw_call = करो_fw_call_hvc;
	पूर्ण अन्यथा अगर (!म_भेद("smc", method)) अणु
		करो_fw_call = करो_fw_call_smc;
	पूर्ण अन्यथा अणु
		pr_warn("%s Invalid \"method\" property: %s\n",
			__func__, method);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zynqmp_pm_query_data() - Get query data from firmware
 * @qdata:	Variable to the zynqmp_pm_query_data काष्ठाure
 * @out:	Returned output value
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_query_data(काष्ठा zynqmp_pm_query_data qdata, u32 *out)
अणु
	पूर्णांक ret;

	ret = zynqmp_pm_invoke_fn(PM_QUERY_DATA, qdata.qid, qdata.arg1,
				  qdata.arg2, qdata.arg3, out);

	/*
	 * For घड़ी name query, all bytes in SMC response are घड़ी name
	 * अक्षरacters and वापस code is always success. For invalid घड़ीs,
	 * घड़ी name bytes would be zeros.
	 */
	वापस qdata.qid == PM_QID_CLOCK_GET_NAME ? 0 : ret;
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_query_data);

/**
 * zynqmp_pm_घड़ी_enable() - Enable the घड़ी क्रम given id
 * @घड़ी_id:	ID of the घड़ी to be enabled
 *
 * This function is used by master to enable the घड़ी
 * including peripherals and PLL घड़ीs.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_घड़ी_enable(u32 घड़ी_id)
अणु
	वापस zynqmp_pm_invoke_fn(PM_CLOCK_ENABLE, घड़ी_id, 0, 0, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_घड़ी_enable);

/**
 * zynqmp_pm_घड़ी_disable() - Disable the घड़ी क्रम given id
 * @घड़ी_id:	ID of the घड़ी to be disable
 *
 * This function is used by master to disable the घड़ी
 * including peripherals and PLL घड़ीs.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_घड़ी_disable(u32 घड़ी_id)
अणु
	वापस zynqmp_pm_invoke_fn(PM_CLOCK_DISABLE, घड़ी_id, 0, 0, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_घड़ी_disable);

/**
 * zynqmp_pm_घड़ी_माला_लोtate() - Get the घड़ी state क्रम given id
 * @घड़ी_id:	ID of the घड़ी to be queried
 * @state:	1/0 (Enabled/Disabled)
 *
 * This function is used by master to get the state of घड़ी
 * including peripherals and PLL घड़ीs.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_घड़ी_माला_लोtate(u32 घड़ी_id, u32 *state)
अणु
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	ret = zynqmp_pm_invoke_fn(PM_CLOCK_GETSTATE, घड़ी_id, 0,
				  0, 0, ret_payload);
	*state = ret_payload[1];

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_घड़ी_माला_लोtate);

/**
 * zynqmp_pm_घड़ी_setभागider() - Set the घड़ी भागider क्रम given id
 * @घड़ी_id:	ID of the घड़ी
 * @भागider:	भागider value
 *
 * This function is used by master to set भागider क्रम any घड़ी
 * to achieve desired rate.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_घड़ी_setभागider(u32 घड़ी_id, u32 भागider)
अणु
	वापस zynqmp_pm_invoke_fn(PM_CLOCK_SETDIVIDER, घड़ी_id, भागider,
				   0, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_घड़ी_setभागider);

/**
 * zynqmp_pm_घड़ी_getभागider() - Get the घड़ी भागider क्रम given id
 * @घड़ी_id:	ID of the घड़ी
 * @भागider:	भागider value
 *
 * This function is used by master to get भागider values
 * क्रम any घड़ी.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_घड़ी_getभागider(u32 घड़ी_id, u32 *भागider)
अणु
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	ret = zynqmp_pm_invoke_fn(PM_CLOCK_GETDIVIDER, घड़ी_id, 0,
				  0, 0, ret_payload);
	*भागider = ret_payload[1];

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_घड़ी_getभागider);

/**
 * zynqmp_pm_घड़ी_setrate() - Set the घड़ी rate क्रम given id
 * @घड़ी_id:	ID of the घड़ी
 * @rate:	rate value in hz
 *
 * This function is used by master to set rate क्रम any घड़ी.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_घड़ी_setrate(u32 घड़ी_id, u64 rate)
अणु
	वापस zynqmp_pm_invoke_fn(PM_CLOCK_SETRATE, घड़ी_id,
				   lower_32_bits(rate),
				   upper_32_bits(rate),
				   0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_घड़ी_setrate);

/**
 * zynqmp_pm_घड़ी_getrate() - Get the घड़ी rate क्रम given id
 * @घड़ी_id:	ID of the घड़ी
 * @rate:	rate value in hz
 *
 * This function is used by master to get rate
 * क्रम any घड़ी.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_घड़ी_getrate(u32 घड़ी_id, u64 *rate)
अणु
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	ret = zynqmp_pm_invoke_fn(PM_CLOCK_GETRATE, घड़ी_id, 0,
				  0, 0, ret_payload);
	*rate = ((u64)ret_payload[2] << 32) | ret_payload[1];

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_घड़ी_getrate);

/**
 * zynqmp_pm_घड़ी_setparent() - Set the घड़ी parent क्रम given id
 * @घड़ी_id:	ID of the घड़ी
 * @parent_id:	parent id
 *
 * This function is used by master to set parent क्रम any घड़ी.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_घड़ी_setparent(u32 घड़ी_id, u32 parent_id)
अणु
	वापस zynqmp_pm_invoke_fn(PM_CLOCK_SETPARENT, घड़ी_id,
				   parent_id, 0, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_घड़ी_setparent);

/**
 * zynqmp_pm_घड़ी_getparent() - Get the घड़ी parent क्रम given id
 * @घड़ी_id:	ID of the घड़ी
 * @parent_id:	parent id
 *
 * This function is used by master to get parent index
 * क्रम any घड़ी.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_घड़ी_getparent(u32 घड़ी_id, u32 *parent_id)
अणु
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	ret = zynqmp_pm_invoke_fn(PM_CLOCK_GETPARENT, घड़ी_id, 0,
				  0, 0, ret_payload);
	*parent_id = ret_payload[1];

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_घड़ी_getparent);

/**
 * zynqmp_pm_set_pll_frac_mode() - PM API क्रम set PLL mode
 *
 * @clk_id:	PLL घड़ी ID
 * @mode:	PLL mode (PLL_MODE_FRAC/PLL_MODE_INT)
 *
 * This function sets PLL mode
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_set_pll_frac_mode(u32 clk_id, u32 mode)
अणु
	वापस zynqmp_pm_invoke_fn(PM_IOCTL, 0, IOCTL_SET_PLL_FRAC_MODE,
				   clk_id, mode, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_set_pll_frac_mode);

/**
 * zynqmp_pm_get_pll_frac_mode() - PM API क्रम get PLL mode
 *
 * @clk_id:	PLL घड़ी ID
 * @mode:	PLL mode
 *
 * This function वापस current PLL mode
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_get_pll_frac_mode(u32 clk_id, u32 *mode)
अणु
	वापस zynqmp_pm_invoke_fn(PM_IOCTL, 0, IOCTL_GET_PLL_FRAC_MODE,
				   clk_id, 0, mode);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_get_pll_frac_mode);

/**
 * zynqmp_pm_set_pll_frac_data() - PM API क्रम setting pll fraction data
 *
 * @clk_id:	PLL घड़ी ID
 * @data:	fraction data
 *
 * This function sets fraction data.
 * It is valid क्रम fraction mode only.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_set_pll_frac_data(u32 clk_id, u32 data)
अणु
	वापस zynqmp_pm_invoke_fn(PM_IOCTL, 0, IOCTL_SET_PLL_FRAC_DATA,
				   clk_id, data, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_set_pll_frac_data);

/**
 * zynqmp_pm_get_pll_frac_data() - PM API क्रम getting pll fraction data
 *
 * @clk_id:	PLL घड़ी ID
 * @data:	fraction data
 *
 * This function वापसs fraction data value.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_get_pll_frac_data(u32 clk_id, u32 *data)
अणु
	वापस zynqmp_pm_invoke_fn(PM_IOCTL, 0, IOCTL_GET_PLL_FRAC_DATA,
				   clk_id, 0, data);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_get_pll_frac_data);

/**
 * zynqmp_pm_set_sd_tapdelay() -  Set tap delay क्रम the SD device
 *
 * @node_id:	Node ID of the device
 * @type:	Type of tap delay to set (input/output)
 * @value:	Value to set fot the tap delay
 *
 * This function sets input/output tap delay क्रम the SD device.
 *
 * Return:	Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_set_sd_tapdelay(u32 node_id, u32 type, u32 value)
अणु
	वापस zynqmp_pm_invoke_fn(PM_IOCTL, node_id, IOCTL_SET_SD_TAPDELAY,
				   type, value, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_set_sd_tapdelay);

/**
 * zynqmp_pm_sd_dll_reset() - Reset DLL logic
 *
 * @node_id:	Node ID of the device
 * @type:	Reset type
 *
 * This function resets DLL logic क्रम the SD device.
 *
 * Return:	Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_sd_dll_reset(u32 node_id, u32 type)
अणु
	वापस zynqmp_pm_invoke_fn(PM_IOCTL, node_id, IOCTL_SD_DLL_RESET,
				   type, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_sd_dll_reset);

/**
 * zynqmp_pm_ग_लिखो_ggs() - PM API क्रम writing global general storage (ggs)
 * @index:	GGS रेजिस्टर index
 * @value:	Register value to be written
 *
 * This function ग_लिखोs value to GGS रेजिस्टर.
 *
 * Return:      Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_ग_लिखो_ggs(u32 index, u32 value)
अणु
	वापस zynqmp_pm_invoke_fn(PM_IOCTL, 0, IOCTL_WRITE_GGS,
				   index, value, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_ग_लिखो_ggs);

/**
 * zynqmp_pm_ग_लिखो_ggs() - PM API क्रम पढ़ोing global general storage (ggs)
 * @index:	GGS रेजिस्टर index
 * @value:	Register value to be written
 *
 * This function वापसs GGS रेजिस्टर value.
 *
 * Return:	Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_पढ़ो_ggs(u32 index, u32 *value)
अणु
	वापस zynqmp_pm_invoke_fn(PM_IOCTL, 0, IOCTL_READ_GGS,
				   index, 0, value);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_पढ़ो_ggs);

/**
 * zynqmp_pm_ग_लिखो_pggs() - PM API क्रम writing persistent global general
 *			     storage (pggs)
 * @index:	PGGS रेजिस्टर index
 * @value:	Register value to be written
 *
 * This function ग_लिखोs value to PGGS रेजिस्टर.
 *
 * Return:	Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_ग_लिखो_pggs(u32 index, u32 value)
अणु
	वापस zynqmp_pm_invoke_fn(PM_IOCTL, 0, IOCTL_WRITE_PGGS, index, value,
				   शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_ग_लिखो_pggs);

/**
 * zynqmp_pm_ग_लिखो_pggs() - PM API क्रम पढ़ोing persistent global general
 *			     storage (pggs)
 * @index:	PGGS रेजिस्टर index
 * @value:	Register value to be written
 *
 * This function वापसs PGGS रेजिस्टर value.
 *
 * Return:	Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_पढ़ो_pggs(u32 index, u32 *value)
अणु
	वापस zynqmp_pm_invoke_fn(PM_IOCTL, 0, IOCTL_READ_PGGS, index, 0,
				   value);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_पढ़ो_pggs);

/**
 * zynqmp_pm_set_boot_health_status() - PM API क्रम setting healthy boot status
 * @value:	Status value to be written
 *
 * This function sets healthy bit value to indicate boot health status
 * to firmware.
 *
 * Return:	Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_set_boot_health_status(u32 value)
अणु
	वापस zynqmp_pm_invoke_fn(PM_IOCTL, 0, IOCTL_SET_BOOT_HEALTH_STATUS,
				   value, 0, शून्य);
पूर्ण

/**
 * zynqmp_pm_reset_निश्चित - Request setting of reset (1 - निश्चित, 0 - release)
 * @reset:		Reset to be configured
 * @निश्चित_flag:	Flag stating should reset be निश्चितed (1) or
 *			released (0)
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_reset_निश्चित(स्थिर क्रमागत zynqmp_pm_reset reset,
			   स्थिर क्रमागत zynqmp_pm_reset_action निश्चित_flag)
अणु
	वापस zynqmp_pm_invoke_fn(PM_RESET_ASSERT, reset, निश्चित_flag,
				   0, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_reset_निश्चित);

/**
 * zynqmp_pm_reset_get_status - Get status of the reset
 * @reset:      Reset whose status should be वापसed
 * @status:     Returned status
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_reset_get_status(स्थिर क्रमागत zynqmp_pm_reset reset, u32 *status)
अणु
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	अगर (!status)
		वापस -EINVAL;

	ret = zynqmp_pm_invoke_fn(PM_RESET_GET_STATUS, reset, 0,
				  0, 0, ret_payload);
	*status = ret_payload[1];

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_reset_get_status);

/**
 * zynqmp_pm_fpga_load - Perक्रमm the fpga load
 * @address:	Address to ग_लिखो to
 * @size:	pl bitstream size
 * @flags:	Bitstream type
 *	-XILINX_ZYNQMP_PM_FPGA_FULL:  FPGA full reconfiguration
 *	-XILINX_ZYNQMP_PM_FPGA_PARTIAL: FPGA partial reconfiguration
 *
 * This function provides access to pmufw. To transfer
 * the required bitstream पूर्णांकo PL.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_fpga_load(स्थिर u64 address, स्थिर u32 size, स्थिर u32 flags)
अणु
	वापस zynqmp_pm_invoke_fn(PM_FPGA_LOAD, lower_32_bits(address),
				   upper_32_bits(address), size, flags, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_fpga_load);

/**
 * zynqmp_pm_fpga_get_status - Read value from PCAP status रेजिस्टर
 * @value: Value to पढ़ो
 *
 * This function provides access to the pmufw to get the PCAP
 * status
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_fpga_get_status(u32 *value)
अणु
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	अगर (!value)
		वापस -EINVAL;

	ret = zynqmp_pm_invoke_fn(PM_FPGA_GET_STATUS, 0, 0, 0, 0, ret_payload);
	*value = ret_payload[1];

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_fpga_get_status);

/**
 * zynqmp_pm_pinctrl_request - Request Pin from firmware
 * @pin: Pin number to request
 *
 * This function requests pin from firmware.
 *
 * Return: Returns status, either success or error+reason.
 */
पूर्णांक zynqmp_pm_pinctrl_request(स्थिर u32 pin)
अणु
	वापस zynqmp_pm_invoke_fn(PM_PINCTRL_REQUEST, pin, 0, 0, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_pinctrl_request);

/**
 * zynqmp_pm_pinctrl_release - Inक्रमm firmware that Pin control is released
 * @pin: Pin number to release
 *
 * This function release pin from firmware.
 *
 * Return: Returns status, either success or error+reason.
 */
पूर्णांक zynqmp_pm_pinctrl_release(स्थिर u32 pin)
अणु
	वापस zynqmp_pm_invoke_fn(PM_PINCTRL_RELEASE, pin, 0, 0, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_pinctrl_release);

/**
 * zynqmp_pm_pinctrl_get_function - Read function id set क्रम the given pin
 * @pin: Pin number
 * @id: Buffer to store function ID
 *
 * This function provides the function currently set क्रम the given pin.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_pinctrl_get_function(स्थिर u32 pin, u32 *id)
अणु
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	अगर (!id)
		वापस -EINVAL;

	ret = zynqmp_pm_invoke_fn(PM_PINCTRL_GET_FUNCTION, pin, 0,
				  0, 0, ret_payload);
	*id = ret_payload[1];

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_pinctrl_get_function);

/**
 * zynqmp_pm_pinctrl_set_function - Set requested function क्रम the pin
 * @pin: Pin number
 * @id: Function ID to set
 *
 * This function sets requested function क्रम the given pin.
 *
 * Return: Returns status, either success or error+reason.
 */
पूर्णांक zynqmp_pm_pinctrl_set_function(स्थिर u32 pin, स्थिर u32 id)
अणु
	वापस zynqmp_pm_invoke_fn(PM_PINCTRL_SET_FUNCTION, pin, id,
				   0, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_pinctrl_set_function);

/**
 * zynqmp_pm_pinctrl_get_config - Get configuration parameter क्रम the pin
 * @pin: Pin number
 * @param: Parameter to get
 * @value: Buffer to store parameter value
 *
 * This function माला_लो requested configuration parameter क्रम the given pin.
 *
 * Return: Returns status, either success or error+reason.
 */
पूर्णांक zynqmp_pm_pinctrl_get_config(स्थिर u32 pin, स्थिर u32 param,
				 u32 *value)
अणु
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	अगर (!value)
		वापस -EINVAL;

	ret = zynqmp_pm_invoke_fn(PM_PINCTRL_CONFIG_PARAM_GET, pin, param,
				  0, 0, ret_payload);
	*value = ret_payload[1];

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_pinctrl_get_config);

/**
 * zynqmp_pm_pinctrl_set_config - Set configuration parameter क्रम the pin
 * @pin: Pin number
 * @param: Parameter to set
 * @value: Parameter value to set
 *
 * This function sets requested configuration parameter क्रम the given pin.
 *
 * Return: Returns status, either success or error+reason.
 */
पूर्णांक zynqmp_pm_pinctrl_set_config(स्थिर u32 pin, स्थिर u32 param,
				 u32 value)
अणु
	वापस zynqmp_pm_invoke_fn(PM_PINCTRL_CONFIG_PARAM_SET, pin,
				   param, value, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_pinctrl_set_config);

/**
 * zynqmp_pm_init_finalize() - PM call to inक्रमm firmware that the caller
 *			       master has initialized its own घातer management
 *
 * Return: Returns status, either success or error+reason
 *
 * This API function is to be used क्रम notअगरy the घातer management controller
 * about the completed घातer management initialization.
 */
पूर्णांक zynqmp_pm_init_finalize(व्योम)
अणु
	वापस zynqmp_pm_invoke_fn(PM_PM_INIT_FINALIZE, 0, 0, 0, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_init_finalize);

/**
 * zynqmp_pm_set_suspend_mode()	- Set प्रणाली suspend mode
 * @mode:	Mode to set क्रम प्रणाली suspend
 *
 * This API function is used to set mode of प्रणाली suspend.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_set_suspend_mode(u32 mode)
अणु
	वापस zynqmp_pm_invoke_fn(PM_SET_SUSPEND_MODE, mode, 0, 0, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_set_suspend_mode);

/**
 * zynqmp_pm_request_node() - Request a node with specअगरic capabilities
 * @node:		Node ID of the slave
 * @capabilities:	Requested capabilities of the slave
 * @qos:		Quality of service (not supported)
 * @ack:		Flag to specअगरy whether acknowledge is requested
 *
 * This function is used by master to request particular node from firmware.
 * Every master must request node beक्रमe using it.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_request_node(स्थिर u32 node, स्थिर u32 capabilities,
			   स्थिर u32 qos, स्थिर क्रमागत zynqmp_pm_request_ack ack)
अणु
	वापस zynqmp_pm_invoke_fn(PM_REQUEST_NODE, node, capabilities,
				   qos, ack, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_request_node);

/**
 * zynqmp_pm_release_node() - Release a node
 * @node:	Node ID of the slave
 *
 * This function is used by master to inक्रमm firmware that master
 * has released node. Once released, master must not use that node
 * without re-request.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_release_node(स्थिर u32 node)
अणु
	वापस zynqmp_pm_invoke_fn(PM_RELEASE_NODE, node, 0, 0, 0, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_release_node);

/**
 * zynqmp_pm_set_requirement() - PM call to set requirement क्रम PM slaves
 * @node:		Node ID of the slave
 * @capabilities:	Requested capabilities of the slave
 * @qos:		Quality of service (not supported)
 * @ack:		Flag to specअगरy whether acknowledge is requested
 *
 * This API function is to be used क्रम slaves a PU alपढ़ोy has requested
 * to change its capabilities.
 *
 * Return: Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_set_requirement(स्थिर u32 node, स्थिर u32 capabilities,
			      स्थिर u32 qos,
			      स्थिर क्रमागत zynqmp_pm_request_ack ack)
अणु
	वापस zynqmp_pm_invoke_fn(PM_SET_REQUIREMENT, node, capabilities,
				   qos, ack, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_set_requirement);

/**
 * zynqmp_pm_aes - Access AES hardware to encrypt/decrypt the data using
 * AES-GCM core.
 * @address:	Address of the AesParams काष्ठाure.
 * @out:	Returned output value
 *
 * Return:	Returns status, either success or error code.
 */
पूर्णांक zynqmp_pm_aes_engine(स्थिर u64 address, u32 *out)
अणु
	u32 ret_payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	अगर (!out)
		वापस -EINVAL;

	ret = zynqmp_pm_invoke_fn(PM_SECURE_AES, upper_32_bits(address),
				  lower_32_bits(address),
				  0, 0, ret_payload);
	*out = ret_payload[1];

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(zynqmp_pm_aes_engine);

/**
 * zynqmp_pm_प्रणाली_shutकरोwn - PM call to request a प्रणाली shutकरोwn or restart
 * @type:	Shutकरोwn or restart? 0 क्रम shutकरोwn, 1 क्रम restart
 * @subtype:	Specअगरies which प्रणाली should be restarted or shut करोwn
 *
 * Return:	Returns status, either success or error+reason
 */
पूर्णांक zynqmp_pm_प्रणाली_shutकरोwn(स्थिर u32 type, स्थिर u32 subtype)
अणु
	वापस zynqmp_pm_invoke_fn(PM_SYSTEM_SHUTDOWN, type, subtype,
				   0, 0, शून्य);
पूर्ण

/**
 * काष्ठा zynqmp_pm_shutकरोwn_scope - Struct क्रम shutकरोwn scope
 * @subtype:	Shutकरोwn subtype
 * @name:	Matching string क्रम scope argument
 *
 * This काष्ठा encapsulates mapping between shutकरोwn scope ID and string.
 */
काष्ठा zynqmp_pm_shutकरोwn_scope अणु
	स्थिर क्रमागत zynqmp_pm_shutकरोwn_subtype subtype;
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा zynqmp_pm_shutकरोwn_scope shutकरोwn_scopes[] = अणु
	[ZYNQMP_PM_SHUTDOWN_SUBTYPE_SUBSYSTEM] = अणु
		.subtype = ZYNQMP_PM_SHUTDOWN_SUBTYPE_SUBSYSTEM,
		.name = "subsystem",
	पूर्ण,
	[ZYNQMP_PM_SHUTDOWN_SUBTYPE_PS_ONLY] = अणु
		.subtype = ZYNQMP_PM_SHUTDOWN_SUBTYPE_PS_ONLY,
		.name = "ps_only",
	पूर्ण,
	[ZYNQMP_PM_SHUTDOWN_SUBTYPE_SYSTEM] = अणु
		.subtype = ZYNQMP_PM_SHUTDOWN_SUBTYPE_SYSTEM,
		.name = "system",
	पूर्ण,
पूर्ण;

अटल काष्ठा zynqmp_pm_shutकरोwn_scope *selected_scope =
		&shutकरोwn_scopes[ZYNQMP_PM_SHUTDOWN_SUBTYPE_SYSTEM];

/**
 * zynqmp_pm_is_shutकरोwn_scope_valid - Check अगर shutकरोwn scope string is valid
 * @scope_string:	Shutकरोwn scope string
 *
 * Return:		Return poपूर्णांकer to matching shutकरोwn scope काष्ठा from
 *			array of available options in प्रणाली अगर string is valid,
 *			otherwise वापसs शून्य.
 */
अटल काष्ठा zynqmp_pm_shutकरोwn_scope*
		zynqmp_pm_is_shutकरोwn_scope_valid(स्थिर अक्षर *scope_string)
अणु
	पूर्णांक count;

	क्रम (count = 0; count < ARRAY_SIZE(shutकरोwn_scopes); count++)
		अगर (sysfs_streq(scope_string, shutकरोwn_scopes[count].name))
			वापस &shutकरोwn_scopes[count];

	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार shutकरोwn_scope_show(काष्ठा device *device,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(shutकरोwn_scopes); i++) अणु
		अगर (&shutकरोwn_scopes[i] == selected_scope) अणु
			म_जोड़ो(buf, "[");
			म_जोड़ो(buf, shutकरोwn_scopes[i].name);
			म_जोड़ो(buf, "]");
		पूर्ण अन्यथा अणु
			म_जोड़ो(buf, shutकरोwn_scopes[i].name);
		पूर्ण
		म_जोड़ो(buf, " ");
	पूर्ण
	म_जोड़ो(buf, "\n");

	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार shutकरोwn_scope_store(काष्ठा device *device,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	काष्ठा zynqmp_pm_shutकरोwn_scope *scope;

	scope = zynqmp_pm_is_shutकरोwn_scope_valid(buf);
	अगर (!scope)
		वापस -EINVAL;

	ret = zynqmp_pm_प्रणाली_shutकरोwn(ZYNQMP_PM_SHUTDOWN_TYPE_SETSCOPE_ONLY,
					scope->subtype);
	अगर (ret) अणु
		pr_err("unable to set shutdown scope %s\n", buf);
		वापस ret;
	पूर्ण

	selected_scope = scope;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(shutकरोwn_scope);

अटल sमाप_प्रकार health_status_store(काष्ठा device *device,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक value;

	ret = kstrtouपूर्णांक(buf, 10, &value);
	अगर (ret)
		वापस ret;

	ret = zynqmp_pm_set_boot_health_status(value);
	अगर (ret) अणु
		dev_err(device, "unable to set healthy bit value to %u\n",
			value);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR_WO(health_status);

अटल sमाप_प्रकार ggs_show(काष्ठा device *device,
			काष्ठा device_attribute *attr,
			अक्षर *buf,
			u32 reg)
अणु
	पूर्णांक ret;
	u32 ret_payload[PAYLOAD_ARG_CNT];

	ret = zynqmp_pm_पढ़ो_ggs(reg, ret_payload);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "0x%x\n", ret_payload[1]);
पूर्ण

अटल sमाप_प्रकार ggs_store(काष्ठा device *device,
			 काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count,
			 u32 reg)
अणु
	दीर्घ value;
	पूर्णांक ret;

	अगर (reg >= GSS_NUM_REGS)
		वापस -EINVAL;

	ret = kम_से_दीर्घ(buf, 16, &value);
	अगर (ret) अणु
		count = -EFAULT;
		जाओ err;
	पूर्ण

	ret = zynqmp_pm_ग_लिखो_ggs(reg, value);
	अगर (ret)
		count = -EFAULT;
err:
	वापस count;
पूर्ण

/* GGS रेजिस्टर show functions */
#घोषणा GGS0_SHOW(N)						\
	sमाप_प्रकार ggs##N##_show(काष्ठा device *device,		\
			      काष्ठा device_attribute *attr,	\
			      अक्षर *buf)			\
	अणु							\
		वापस ggs_show(device, attr, buf, N);		\
	पूर्ण

अटल GGS0_SHOW(0);
अटल GGS0_SHOW(1);
अटल GGS0_SHOW(2);
अटल GGS0_SHOW(3);

/* GGS रेजिस्टर store function */
#घोषणा GGS0_STORE(N)						\
	sमाप_प्रकार ggs##N##_store(काष्ठा device *device,		\
			       काष्ठा device_attribute *attr,	\
			       स्थिर अक्षर *buf,			\
			       माप_प्रकार count)			\
	अणु							\
		वापस ggs_store(device, attr, buf, count, N);	\
	पूर्ण

अटल GGS0_STORE(0);
अटल GGS0_STORE(1);
अटल GGS0_STORE(2);
अटल GGS0_STORE(3);

अटल sमाप_प्रकार pggs_show(काष्ठा device *device,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf,
			 u32 reg)
अणु
	पूर्णांक ret;
	u32 ret_payload[PAYLOAD_ARG_CNT];

	ret = zynqmp_pm_पढ़ो_pggs(reg, ret_payload);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "0x%x\n", ret_payload[1]);
पूर्ण

अटल sमाप_प्रकार pggs_store(काष्ठा device *device,
			  काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count,
			  u32 reg)
अणु
	दीर्घ value;
	पूर्णांक ret;

	अगर (reg >= GSS_NUM_REGS)
		वापस -EINVAL;

	ret = kम_से_दीर्घ(buf, 16, &value);
	अगर (ret) अणु
		count = -EFAULT;
		जाओ err;
	पूर्ण

	ret = zynqmp_pm_ग_लिखो_pggs(reg, value);
	अगर (ret)
		count = -EFAULT;

err:
	वापस count;
पूर्ण

#घोषणा PGGS0_SHOW(N)						\
	sमाप_प्रकार pggs##N##_show(काष्ठा device *device,		\
			       काष्ठा device_attribute *attr,	\
			       अक्षर *buf)			\
	अणु							\
		वापस pggs_show(device, attr, buf, N);		\
	पूर्ण

#घोषणा PGGS0_STORE(N)						\
	sमाप_प्रकार pggs##N##_store(काष्ठा device *device,		\
				काष्ठा device_attribute *attr,	\
				स्थिर अक्षर *buf,		\
				माप_प्रकार count)			\
	अणु							\
		वापस pggs_store(device, attr, buf, count, N);	\
	पूर्ण

/* PGGS रेजिस्टर show functions */
अटल PGGS0_SHOW(0);
अटल PGGS0_SHOW(1);
अटल PGGS0_SHOW(2);
अटल PGGS0_SHOW(3);

/* PGGS रेजिस्टर store functions */
अटल PGGS0_STORE(0);
अटल PGGS0_STORE(1);
अटल PGGS0_STORE(2);
अटल PGGS0_STORE(3);

/* GGS रेजिस्टर attributes */
अटल DEVICE_ATTR_RW(ggs0);
अटल DEVICE_ATTR_RW(ggs1);
अटल DEVICE_ATTR_RW(ggs2);
अटल DEVICE_ATTR_RW(ggs3);

/* PGGS रेजिस्टर attributes */
अटल DEVICE_ATTR_RW(pggs0);
अटल DEVICE_ATTR_RW(pggs1);
अटल DEVICE_ATTR_RW(pggs2);
अटल DEVICE_ATTR_RW(pggs3);

अटल काष्ठा attribute *zynqmp_firmware_attrs[] = अणु
	&dev_attr_ggs0.attr,
	&dev_attr_ggs1.attr,
	&dev_attr_ggs2.attr,
	&dev_attr_ggs3.attr,
	&dev_attr_pggs0.attr,
	&dev_attr_pggs1.attr,
	&dev_attr_pggs2.attr,
	&dev_attr_pggs3.attr,
	&dev_attr_shutकरोwn_scope.attr,
	&dev_attr_health_status.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(zynqmp_firmware);

अटल पूर्णांक zynqmp_firmware_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np;
	पूर्णांक ret;

	np = of_find_compatible_node(शून्य, शून्य, "xlnx,zynqmp");
	अगर (!np) अणु
		np = of_find_compatible_node(शून्य, शून्य, "xlnx,versal");
		अगर (!np)
			वापस 0;

		feature_check_enabled = true;
	पूर्ण
	of_node_put(np);

	ret = get_set_conduit_method(dev->of_node);
	अगर (ret)
		वापस ret;

	/* Check PM API version number */
	zynqmp_pm_get_api_version(&pm_api_version);
	अगर (pm_api_version < ZYNQMP_PM_VERSION) अणु
		panic("%s Platform Management API version error. Expected: v%d.%d - Found: v%d.%d\n",
		      __func__,
		      ZYNQMP_PM_VERSION_MAJOR, ZYNQMP_PM_VERSION_MINOR,
		      pm_api_version >> 16, pm_api_version & 0xFFFF);
	पूर्ण

	pr_info("%s Platform Management API v%d.%d\n", __func__,
		pm_api_version >> 16, pm_api_version & 0xFFFF);

	/* Check trustzone version number */
	ret = zynqmp_pm_get_trustzone_version(&pm_tz_version);
	अगर (ret)
		panic("Legacy trustzone found without version support\n");

	अगर (pm_tz_version < ZYNQMP_TZ_VERSION)
		panic("%s Trustzone version error. Expected: v%d.%d - Found: v%d.%d\n",
		      __func__,
		      ZYNQMP_TZ_VERSION_MAJOR, ZYNQMP_TZ_VERSION_MINOR,
		      pm_tz_version >> 16, pm_tz_version & 0xFFFF);

	pr_info("%s Trustzone version v%d.%d\n", __func__,
		pm_tz_version >> 16, pm_tz_version & 0xFFFF);

	ret = mfd_add_devices(&pdev->dev, PLATFORM_DEVID_NONE, firmware_devs,
			      ARRAY_SIZE(firmware_devs), शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add MFD devices %d\n", ret);
		वापस ret;
	पूर्ण

	zynqmp_pm_api_debugfs_init();

	वापस of_platक्रमm_populate(dev->of_node, शून्य, शून्य, dev);
पूर्ण

अटल पूर्णांक zynqmp_firmware_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm_api_feature_data *feature_data;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	mfd_हटाओ_devices(&pdev->dev);
	zynqmp_pm_api_debugfs_निकास();

	hash_क्रम_each_safe(pm_api_features_map, i, पंचांगp, feature_data, hentry) अणु
		hash_del(&feature_data->hentry);
		kमुक्त(feature_data);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zynqmp_firmware_of_match[] = अणु
	अणु.compatible = "xlnx,zynqmp-firmware"पूर्ण,
	अणु.compatible = "xlnx,versal-firmware"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zynqmp_firmware_of_match);

अटल काष्ठा platक्रमm_driver zynqmp_firmware_driver = अणु
	.driver = अणु
		.name = "zynqmp_firmware",
		.of_match_table = zynqmp_firmware_of_match,
		.dev_groups = zynqmp_firmware_groups,
	पूर्ण,
	.probe = zynqmp_firmware_probe,
	.हटाओ = zynqmp_firmware_हटाओ,
पूर्ण;
module_platक्रमm_driver(zynqmp_firmware_driver);
