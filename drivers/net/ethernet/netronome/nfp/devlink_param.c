<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2019 Netronome Systems, Inc. */

#समावेश <net/devlink.h>

#समावेश "nfpcore/nfp.h"
#समावेश "nfpcore/nfp_nsp.h"
#समावेश "nfp_main.h"

/**
 * काष्ठा nfp_devlink_param_u8_arg - Devlink u8 parameter get/set arguments
 * @hwinfo_name:	HWinfo key name
 * @शेष_hi_val:	Default HWinfo value अगर HWinfo करोesn't exist
 * @invalid_dl_val:	Devlink value to use अगर HWinfo is unknown/invalid.
 *			-त्रुटि_सं अगर there is no unknown/invalid value available
 * @hi_to_dl:	HWinfo to devlink value mapping
 * @dl_to_hi:	Devlink to hwinfo value mapping
 * @max_dl_val:	Maximum devlink value supported, क्रम validation only
 * @max_hi_val:	Maximum HWinfo value supported, क्रम validation only
 */
काष्ठा nfp_devlink_param_u8_arg अणु
	स्थिर अक्षर *hwinfo_name;
	स्थिर अक्षर *शेष_hi_val;
	पूर्णांक invalid_dl_val;
	u8 hi_to_dl[4];
	u8 dl_to_hi[4];
	u8 max_dl_val;
	u8 max_hi_val;
पूर्ण;

अटल स्थिर काष्ठा nfp_devlink_param_u8_arg nfp_devlink_u8_args[] = अणु
	[DEVLINK_PARAM_GENERIC_ID_FW_LOAD_POLICY] = अणु
		.hwinfo_name = "app_fw_from_flash",
		.शेष_hi_val = NFP_NSP_APP_FW_LOAD_DEFAULT,
		.invalid_dl_val =
			DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_UNKNOWN,
		.hi_to_dl = अणु
			[NFP_NSP_APP_FW_LOAD_DISK] =
				DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DISK,
			[NFP_NSP_APP_FW_LOAD_FLASH] =
				DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_FLASH,
			[NFP_NSP_APP_FW_LOAD_PREF] =
				DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DRIVER,
		पूर्ण,
		.dl_to_hi = अणु
			[DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DRIVER] =
				NFP_NSP_APP_FW_LOAD_PREF,
			[DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_FLASH] =
				NFP_NSP_APP_FW_LOAD_FLASH,
			[DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DISK] =
				NFP_NSP_APP_FW_LOAD_DISK,
		पूर्ण,
		.max_dl_val = DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DISK,
		.max_hi_val = NFP_NSP_APP_FW_LOAD_PREF,
	पूर्ण,
	[DEVLINK_PARAM_GENERIC_ID_RESET_DEV_ON_DRV_PROBE] = अणु
		.hwinfo_name = "abi_drv_reset",
		.शेष_hi_val = NFP_NSP_DRV_RESET_DEFAULT,
		.invalid_dl_val =
			DEVLINK_PARAM_RESET_DEV_ON_DRV_PROBE_VALUE_UNKNOWN,
		.hi_to_dl = अणु
			[NFP_NSP_DRV_RESET_ALWAYS] =
				DEVLINK_PARAM_RESET_DEV_ON_DRV_PROBE_VALUE_ALWAYS,
			[NFP_NSP_DRV_RESET_NEVER] =
				DEVLINK_PARAM_RESET_DEV_ON_DRV_PROBE_VALUE_NEVER,
			[NFP_NSP_DRV_RESET_DISK] =
				DEVLINK_PARAM_RESET_DEV_ON_DRV_PROBE_VALUE_DISK,
		पूर्ण,
		.dl_to_hi = अणु
			[DEVLINK_PARAM_RESET_DEV_ON_DRV_PROBE_VALUE_ALWAYS] =
				NFP_NSP_DRV_RESET_ALWAYS,
			[DEVLINK_PARAM_RESET_DEV_ON_DRV_PROBE_VALUE_NEVER] =
				NFP_NSP_DRV_RESET_NEVER,
			[DEVLINK_PARAM_RESET_DEV_ON_DRV_PROBE_VALUE_DISK] =
				NFP_NSP_DRV_RESET_DISK,
		पूर्ण,
		.max_dl_val = DEVLINK_PARAM_RESET_DEV_ON_DRV_PROBE_VALUE_DISK,
		.max_hi_val = NFP_NSP_DRV_RESET_NEVER,
	पूर्ण
पूर्ण;

अटल पूर्णांक
nfp_devlink_param_u8_get(काष्ठा devlink *devlink, u32 id,
			 काष्ठा devlink_param_gset_ctx *ctx)
अणु
	स्थिर काष्ठा nfp_devlink_param_u8_arg *arg;
	काष्ठा nfp_pf *pf = devlink_priv(devlink);
	काष्ठा nfp_nsp *nsp;
	अक्षर hwinfo[32];
	दीर्घ value;
	पूर्णांक err;

	अगर (id >= ARRAY_SIZE(nfp_devlink_u8_args))
		वापस -EOPNOTSUPP;

	arg = &nfp_devlink_u8_args[id];

	nsp = nfp_nsp_खोलो(pf->cpp);
	अगर (IS_ERR(nsp)) अणु
		err = PTR_ERR(nsp);
		nfp_warn(pf->cpp, "can't access NSP: %d\n", err);
		वापस err;
	पूर्ण

	snम_लिखो(hwinfo, माप(hwinfo), arg->hwinfo_name);
	err = nfp_nsp_hwinfo_lookup_optional(nsp, hwinfo, माप(hwinfo),
					     arg->शेष_hi_val);
	अगर (err) अणु
		nfp_warn(pf->cpp, "HWinfo lookup failed: %d\n", err);
		जाओ निकास_बंद_nsp;
	पूर्ण

	err = kम_से_दीर्घ(hwinfo, 0, &value);
	अगर (err || value < 0 || value > arg->max_hi_val) अणु
		nfp_warn(pf->cpp, "HWinfo '%s' value %li invalid\n",
			 arg->hwinfo_name, value);

		अगर (arg->invalid_dl_val >= 0)
			ctx->val.vu8 = arg->invalid_dl_val;
		अन्यथा
			err = arg->invalid_dl_val;

		जाओ निकास_बंद_nsp;
	पूर्ण

	ctx->val.vu8 = arg->hi_to_dl[value];

निकास_बंद_nsp:
	nfp_nsp_बंद(nsp);
	वापस err;
पूर्ण

अटल पूर्णांक
nfp_devlink_param_u8_set(काष्ठा devlink *devlink, u32 id,
			 काष्ठा devlink_param_gset_ctx *ctx)
अणु
	स्थिर काष्ठा nfp_devlink_param_u8_arg *arg;
	काष्ठा nfp_pf *pf = devlink_priv(devlink);
	काष्ठा nfp_nsp *nsp;
	अक्षर hwinfo[32];
	पूर्णांक err;

	अगर (id >= ARRAY_SIZE(nfp_devlink_u8_args))
		वापस -EOPNOTSUPP;

	arg = &nfp_devlink_u8_args[id];

	nsp = nfp_nsp_खोलो(pf->cpp);
	अगर (IS_ERR(nsp)) अणु
		err = PTR_ERR(nsp);
		nfp_warn(pf->cpp, "can't access NSP: %d\n", err);
		वापस err;
	पूर्ण

	/* Note the value has alपढ़ोy been validated. */
	snम_लिखो(hwinfo, माप(hwinfo), "%s=%u",
		 arg->hwinfo_name, arg->dl_to_hi[ctx->val.vu8]);
	err = nfp_nsp_hwinfo_set(nsp, hwinfo, माप(hwinfo));
	अगर (err) अणु
		nfp_warn(pf->cpp, "HWinfo set failed: %d\n", err);
		जाओ निकास_बंद_nsp;
	पूर्ण

निकास_बंद_nsp:
	nfp_nsp_बंद(nsp);
	वापस err;
पूर्ण

अटल पूर्णांक
nfp_devlink_param_u8_validate(काष्ठा devlink *devlink, u32 id,
			      जोड़ devlink_param_value val,
			      काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा nfp_devlink_param_u8_arg *arg;

	अगर (id >= ARRAY_SIZE(nfp_devlink_u8_args))
		वापस -EOPNOTSUPP;

	arg = &nfp_devlink_u8_args[id];

	अगर (val.vu8 > arg->max_dl_val) अणु
		NL_SET_ERR_MSG_MOD(extack, "parameter out of range");
		वापस -EINVAL;
	पूर्ण

	अगर (val.vu8 == arg->invalid_dl_val) अणु
		NL_SET_ERR_MSG_MOD(extack, "unknown/invalid value specified");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा devlink_param nfp_devlink_params[] = अणु
	DEVLINK_PARAM_GENERIC(FW_LOAD_POLICY,
			      BIT(DEVLINK_PARAM_CMODE_PERMANENT),
			      nfp_devlink_param_u8_get,
			      nfp_devlink_param_u8_set,
			      nfp_devlink_param_u8_validate),
	DEVLINK_PARAM_GENERIC(RESET_DEV_ON_DRV_PROBE,
			      BIT(DEVLINK_PARAM_CMODE_PERMANENT),
			      nfp_devlink_param_u8_get,
			      nfp_devlink_param_u8_set,
			      nfp_devlink_param_u8_validate),
पूर्ण;

अटल पूर्णांक nfp_devlink_supports_params(काष्ठा nfp_pf *pf)
अणु
	काष्ठा nfp_nsp *nsp;
	bool supported;
	पूर्णांक err;

	nsp = nfp_nsp_खोलो(pf->cpp);
	अगर (IS_ERR(nsp)) अणु
		err = PTR_ERR(nsp);
		dev_err(&pf->pdev->dev, "Failed to access the NSP: %d\n", err);
		वापस err;
	पूर्ण

	supported = nfp_nsp_has_hwinfo_lookup(nsp) &&
		    nfp_nsp_has_hwinfo_set(nsp);

	nfp_nsp_बंद(nsp);
	वापस supported;
पूर्ण

पूर्णांक nfp_devlink_params_रेजिस्टर(काष्ठा nfp_pf *pf)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(pf);
	पूर्णांक err;

	err = nfp_devlink_supports_params(pf);
	अगर (err <= 0)
		वापस err;

	err = devlink_params_रेजिस्टर(devlink, nfp_devlink_params,
				      ARRAY_SIZE(nfp_devlink_params));
	अगर (err)
		वापस err;

	devlink_params_publish(devlink);
	वापस 0;
पूर्ण

व्योम nfp_devlink_params_unरेजिस्टर(काष्ठा nfp_pf *pf)
अणु
	पूर्णांक err;

	err = nfp_devlink_supports_params(pf);
	अगर (err <= 0)
		वापस;

	devlink_params_unरेजिस्टर(priv_to_devlink(pf), nfp_devlink_params,
				  ARRAY_SIZE(nfp_devlink_params));
पूर्ण
