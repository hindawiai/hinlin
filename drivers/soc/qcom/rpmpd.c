<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2017-2018, The Linux Foundation. All rights reserved. */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/soc/qcom/smd-rpm.h>

#समावेश <dt-bindings/घातer/qcom-rpmpd.h>

#घोषणा करोमुख्य_to_rpmpd(करोमुख्य) container_of(करोमुख्य, काष्ठा rpmpd, pd)

/* Resource types:
 * RPMPD_X is X encoded as a little-endian, lower-हाल, ASCII string */
#घोषणा RPMPD_SMPA 0x61706d73
#घोषणा RPMPD_LDOA 0x616f646c
#घोषणा RPMPD_SMPB 0x62706d73
#घोषणा RPMPD_LDOB 0x626f646c
#घोषणा RPMPD_RWCX 0x78637772
#घोषणा RPMPD_RWMX 0x786d7772
#घोषणा RPMPD_RWLC 0x636c7772
#घोषणा RPMPD_RWLM 0x6d6c7772
#घोषणा RPMPD_RWSC 0x63737772
#घोषणा RPMPD_RWSM 0x6d737772

/* Operation Keys */
#घोषणा KEY_CORNER		0x6e726f63 /* corn */
#घोषणा KEY_ENABLE		0x6e657773 /* swen */
#घोषणा KEY_FLOOR_CORNER	0x636676   /* vfc */
#घोषणा KEY_FLOOR_LEVEL		0x6c6676   /* vfl */
#घोषणा KEY_LEVEL		0x6c766c76 /* vlvl */

#घोषणा MAX_CORNER_RPMPD_STATE	6

#घोषणा DEFINE_RPMPD_PAIR(_platक्रमm, _name, _active, r_type, r_key,	\
			  r_id)						\
	अटल काष्ठा rpmpd _platक्रमm##_##_active;			\
	अटल काष्ठा rpmpd _platक्रमm##_##_name = अणु			\
		.pd = अणु	.name = #_name,	पूर्ण,				\
		.peer = &_platक्रमm##_##_active,				\
		.res_type = RPMPD_##r_type,				\
		.res_id = r_id,						\
		.key = KEY_##r_key,					\
	पूर्ण;								\
	अटल काष्ठा rpmpd _platक्रमm##_##_active = अणु			\
		.pd = अणु .name = #_active, पूर्ण,				\
		.peer = &_platक्रमm##_##_name,				\
		.active_only = true,					\
		.res_type = RPMPD_##r_type,				\
		.res_id = r_id,						\
		.key = KEY_##r_key,					\
	पूर्ण

#घोषणा DEFINE_RPMPD_CORNER(_platक्रमm, _name, r_type, r_id)		\
	अटल काष्ठा rpmpd _platक्रमm##_##_name = अणु			\
		.pd = अणु .name = #_name, पूर्ण,				\
		.res_type = RPMPD_##r_type,				\
		.res_id = r_id,						\
		.key = KEY_CORNER,					\
	पूर्ण

#घोषणा DEFINE_RPMPD_LEVEL(_platक्रमm, _name, r_type, r_id)		\
	अटल काष्ठा rpmpd _platक्रमm##_##_name = अणु			\
		.pd = अणु .name = #_name, पूर्ण,				\
		.res_type = RPMPD_##r_type,				\
		.res_id = r_id,						\
		.key = KEY_LEVEL,					\
	पूर्ण

#घोषणा DEFINE_RPMPD_VFC(_platक्रमm, _name, r_type, r_id)		\
	अटल काष्ठा rpmpd _platक्रमm##_##_name = अणु			\
		.pd = अणु .name = #_name, पूर्ण,				\
		.res_type = RPMPD_##r_type,				\
		.res_id = r_id,						\
		.key = KEY_FLOOR_CORNER,				\
	पूर्ण

#घोषणा DEFINE_RPMPD_VFL(_platक्रमm, _name, r_type, r_id)		\
	अटल काष्ठा rpmpd _platक्रमm##_##_name = अणु			\
		.pd = अणु .name = #_name, पूर्ण,				\
		.res_type = RPMPD_##r_type,				\
		.res_id = r_id,						\
		.key = KEY_FLOOR_LEVEL,					\
	पूर्ण

काष्ठा rpmpd_req अणु
	__le32 key;
	__le32 nbytes;
	__le32 value;
पूर्ण;

काष्ठा rpmpd अणु
	काष्ठा generic_pm_करोमुख्य pd;
	काष्ठा rpmpd *peer;
	स्थिर bool active_only;
	अचिन्हित पूर्णांक corner;
	bool enabled;
	स्थिर अक्षर *res_name;
	स्थिर पूर्णांक res_type;
	स्थिर पूर्णांक res_id;
	काष्ठा qcom_smd_rpm *rpm;
	अचिन्हित पूर्णांक max_state;
	__le32 key;
पूर्ण;

काष्ठा rpmpd_desc अणु
	काष्ठा rpmpd **rpmpds;
	माप_प्रकार num_pds;
	अचिन्हित पूर्णांक max_state;
पूर्ण;

अटल DEFINE_MUTEX(rpmpd_lock);

/* msm8939 RPM Power Doमुख्यs */
DEFINE_RPMPD_PAIR(msm8939, vddmd, vddmd_ao, SMPA, CORNER, 1);
DEFINE_RPMPD_VFC(msm8939, vddmd_vfc, SMPA, 1);

DEFINE_RPMPD_PAIR(msm8939, vddcx, vddcx_ao, SMPA, CORNER, 2);
DEFINE_RPMPD_VFC(msm8939, vddcx_vfc, SMPA, 2);

DEFINE_RPMPD_PAIR(msm8939, vddmx, vddmx_ao, LDOA, CORNER, 3);

अटल काष्ठा rpmpd *msm8939_rpmpds[] = अणु
	[MSM8939_VDDMDCX] =	&msm8939_vddmd,
	[MSM8939_VDDMDCX_AO] =	&msm8939_vddmd_ao,
	[MSM8939_VDDMDCX_VFC] =	&msm8939_vddmd_vfc,
	[MSM8939_VDDCX] =	&msm8939_vddcx,
	[MSM8939_VDDCX_AO] =	&msm8939_vddcx_ao,
	[MSM8939_VDDCX_VFC] =	&msm8939_vddcx_vfc,
	[MSM8939_VDDMX] =	&msm8939_vddmx,
	[MSM8939_VDDMX_AO] =	&msm8939_vddmx_ao,
पूर्ण;

अटल स्थिर काष्ठा rpmpd_desc msm8939_desc = अणु
	.rpmpds = msm8939_rpmpds,
	.num_pds = ARRAY_SIZE(msm8939_rpmpds),
	.max_state = MAX_CORNER_RPMPD_STATE,
पूर्ण;

/* msm8916 RPM Power Doमुख्यs */
DEFINE_RPMPD_PAIR(msm8916, vddcx, vddcx_ao, SMPA, CORNER, 1);
DEFINE_RPMPD_PAIR(msm8916, vddmx, vddmx_ao, LDOA, CORNER, 3);

DEFINE_RPMPD_VFC(msm8916, vddcx_vfc, SMPA, 1);

अटल काष्ठा rpmpd *msm8916_rpmpds[] = अणु
	[MSM8916_VDDCX] =	&msm8916_vddcx,
	[MSM8916_VDDCX_AO] =	&msm8916_vddcx_ao,
	[MSM8916_VDDCX_VFC] =	&msm8916_vddcx_vfc,
	[MSM8916_VDDMX] =	&msm8916_vddmx,
	[MSM8916_VDDMX_AO] =	&msm8916_vddmx_ao,
पूर्ण;

अटल स्थिर काष्ठा rpmpd_desc msm8916_desc = अणु
	.rpmpds = msm8916_rpmpds,
	.num_pds = ARRAY_SIZE(msm8916_rpmpds),
	.max_state = MAX_CORNER_RPMPD_STATE,
पूर्ण;

/* msm8976 RPM Power Doमुख्यs */
DEFINE_RPMPD_PAIR(msm8976, vddcx, vddcx_ao, SMPA, LEVEL, 2);
DEFINE_RPMPD_PAIR(msm8976, vddmx, vddmx_ao, SMPA, LEVEL, 6);

DEFINE_RPMPD_VFL(msm8976, vddcx_vfl, RWSC, 2);
DEFINE_RPMPD_VFL(msm8976, vddmx_vfl, RWSM, 6);

अटल काष्ठा rpmpd *msm8976_rpmpds[] = अणु
	[MSM8976_VDDCX] =	&msm8976_vddcx,
	[MSM8976_VDDCX_AO] =	&msm8976_vddcx_ao,
	[MSM8976_VDDCX_VFL] =	&msm8976_vddcx_vfl,
	[MSM8976_VDDMX] =	&msm8976_vddmx,
	[MSM8976_VDDMX_AO] =	&msm8976_vddmx_ao,
	[MSM8976_VDDMX_VFL] =	&msm8976_vddmx_vfl,
पूर्ण;

अटल स्थिर काष्ठा rpmpd_desc msm8976_desc = अणु
	.rpmpds = msm8976_rpmpds,
	.num_pds = ARRAY_SIZE(msm8976_rpmpds),
	.max_state = RPM_SMD_LEVEL_TURBO_HIGH,
पूर्ण;

/* msm8994 RPM Power करोमुख्यs */
DEFINE_RPMPD_PAIR(msm8994, vddcx, vddcx_ao, SMPA, CORNER, 1);
DEFINE_RPMPD_PAIR(msm8994, vddmx, vddmx_ao, SMPA, CORNER, 2);
/* Attention! *Some* 8994 boards with pm8004 may use SMPC here! */
DEFINE_RPMPD_CORNER(msm8994, vddgfx, SMPB, 2);

DEFINE_RPMPD_VFC(msm8994, vddcx_vfc, SMPA, 1);
DEFINE_RPMPD_VFC(msm8994, vddgfx_vfc, SMPB, 2);

अटल काष्ठा rpmpd *msm8994_rpmpds[] = अणु
	[MSM8994_VDDCX] =	&msm8994_vddcx,
	[MSM8994_VDDCX_AO] =	&msm8994_vddcx_ao,
	[MSM8994_VDDCX_VFC] =	&msm8994_vddcx_vfc,
	[MSM8994_VDDMX] =	&msm8994_vddmx,
	[MSM8994_VDDMX_AO] =	&msm8994_vddmx_ao,
	[MSM8994_VDDGFX] =	&msm8994_vddgfx,
	[MSM8994_VDDGFX_VFC] =	&msm8994_vddgfx_vfc,
पूर्ण;

अटल स्थिर काष्ठा rpmpd_desc msm8994_desc = अणु
	.rpmpds = msm8994_rpmpds,
	.num_pds = ARRAY_SIZE(msm8994_rpmpds),
	.max_state = MAX_CORNER_RPMPD_STATE,
पूर्ण;

/* msm8996 RPM Power करोमुख्यs */
DEFINE_RPMPD_PAIR(msm8996, vddcx, vddcx_ao, SMPA, CORNER, 1);
DEFINE_RPMPD_PAIR(msm8996, vddmx, vddmx_ao, SMPA, CORNER, 2);
DEFINE_RPMPD_CORNER(msm8996, vddsscx, LDOA, 26);

DEFINE_RPMPD_VFC(msm8996, vddcx_vfc, SMPA, 1);
DEFINE_RPMPD_VFC(msm8996, vddsscx_vfc, LDOA, 26);

अटल काष्ठा rpmpd *msm8996_rpmpds[] = अणु
	[MSM8996_VDDCX] =	&msm8996_vddcx,
	[MSM8996_VDDCX_AO] =	&msm8996_vddcx_ao,
	[MSM8996_VDDCX_VFC] =	&msm8996_vddcx_vfc,
	[MSM8996_VDDMX] =	&msm8996_vddmx,
	[MSM8996_VDDMX_AO] =	&msm8996_vddmx_ao,
	[MSM8996_VDDSSCX] =	&msm8996_vddsscx,
	[MSM8996_VDDSSCX_VFC] =	&msm8996_vddsscx_vfc,
पूर्ण;

अटल स्थिर काष्ठा rpmpd_desc msm8996_desc = अणु
	.rpmpds = msm8996_rpmpds,
	.num_pds = ARRAY_SIZE(msm8996_rpmpds),
	.max_state = MAX_CORNER_RPMPD_STATE,
पूर्ण;

/* msm8998 RPM Power करोमुख्यs */
DEFINE_RPMPD_PAIR(msm8998, vddcx, vddcx_ao, RWCX, LEVEL, 0);
DEFINE_RPMPD_VFL(msm8998, vddcx_vfl, RWCX, 0);

DEFINE_RPMPD_PAIR(msm8998, vddmx, vddmx_ao, RWMX, LEVEL, 0);
DEFINE_RPMPD_VFL(msm8998, vddmx_vfl, RWMX, 0);

DEFINE_RPMPD_LEVEL(msm8998, vdd_ssccx, RWSC, 0);
DEFINE_RPMPD_VFL(msm8998, vdd_ssccx_vfl, RWSC, 0);

DEFINE_RPMPD_LEVEL(msm8998, vdd_sscmx, RWSM, 0);
DEFINE_RPMPD_VFL(msm8998, vdd_sscmx_vfl, RWSM, 0);

अटल काष्ठा rpmpd *msm8998_rpmpds[] = अणु
	[MSM8998_VDDCX] =		&msm8998_vddcx,
	[MSM8998_VDDCX_AO] =		&msm8998_vddcx_ao,
	[MSM8998_VDDCX_VFL] =		&msm8998_vddcx_vfl,
	[MSM8998_VDDMX] =		&msm8998_vddmx,
	[MSM8998_VDDMX_AO] =		&msm8998_vddmx_ao,
	[MSM8998_VDDMX_VFL] =		&msm8998_vddmx_vfl,
	[MSM8998_SSCCX] =		&msm8998_vdd_ssccx,
	[MSM8998_SSCCX_VFL] =		&msm8998_vdd_ssccx_vfl,
	[MSM8998_SSCMX] =		&msm8998_vdd_sscmx,
	[MSM8998_SSCMX_VFL] =		&msm8998_vdd_sscmx_vfl,
पूर्ण;

अटल स्थिर काष्ठा rpmpd_desc msm8998_desc = अणु
	.rpmpds = msm8998_rpmpds,
	.num_pds = ARRAY_SIZE(msm8998_rpmpds),
	.max_state = RPM_SMD_LEVEL_BINNING,
पूर्ण;

/* qcs404 RPM Power करोमुख्यs */
DEFINE_RPMPD_PAIR(qcs404, vddmx, vddmx_ao, RWMX, LEVEL, 0);
DEFINE_RPMPD_VFL(qcs404, vddmx_vfl, RWMX, 0);

DEFINE_RPMPD_LEVEL(qcs404, vdd_lpicx, RWLC, 0);
DEFINE_RPMPD_VFL(qcs404, vdd_lpicx_vfl, RWLC, 0);

DEFINE_RPMPD_LEVEL(qcs404, vdd_lpimx, RWLM, 0);
DEFINE_RPMPD_VFL(qcs404, vdd_lpimx_vfl, RWLM, 0);

अटल काष्ठा rpmpd *qcs404_rpmpds[] = अणु
	[QCS404_VDDMX] = &qcs404_vddmx,
	[QCS404_VDDMX_AO] = &qcs404_vddmx_ao,
	[QCS404_VDDMX_VFL] = &qcs404_vddmx_vfl,
	[QCS404_LPICX] = &qcs404_vdd_lpicx,
	[QCS404_LPICX_VFL] = &qcs404_vdd_lpicx_vfl,
	[QCS404_LPIMX] = &qcs404_vdd_lpimx,
	[QCS404_LPIMX_VFL] = &qcs404_vdd_lpimx_vfl,
पूर्ण;

अटल स्थिर काष्ठा rpmpd_desc qcs404_desc = अणु
	.rpmpds = qcs404_rpmpds,
	.num_pds = ARRAY_SIZE(qcs404_rpmpds),
	.max_state = RPM_SMD_LEVEL_BINNING,
पूर्ण;

/* sdm660 RPM Power करोमुख्यs */
DEFINE_RPMPD_PAIR(sdm660, vddcx, vddcx_ao, RWCX, LEVEL, 0);
DEFINE_RPMPD_VFL(sdm660, vddcx_vfl, RWCX, 0);

DEFINE_RPMPD_PAIR(sdm660, vddmx, vddmx_ao, RWMX, LEVEL, 0);
DEFINE_RPMPD_VFL(sdm660, vddmx_vfl, RWMX, 0);

DEFINE_RPMPD_LEVEL(sdm660, vdd_ssccx, RWLC, 0);
DEFINE_RPMPD_VFL(sdm660, vdd_ssccx_vfl, RWLC, 0);

DEFINE_RPMPD_LEVEL(sdm660, vdd_sscmx, RWLM, 0);
DEFINE_RPMPD_VFL(sdm660, vdd_sscmx_vfl, RWLM, 0);

अटल काष्ठा rpmpd *sdm660_rpmpds[] = अणु
	[SDM660_VDDCX] =		&sdm660_vddcx,
	[SDM660_VDDCX_AO] =		&sdm660_vddcx_ao,
	[SDM660_VDDCX_VFL] =		&sdm660_vddcx_vfl,
	[SDM660_VDDMX] =		&sdm660_vddmx,
	[SDM660_VDDMX_AO] =		&sdm660_vddmx_ao,
	[SDM660_VDDMX_VFL] =		&sdm660_vddmx_vfl,
	[SDM660_SSCCX] =		&sdm660_vdd_ssccx,
	[SDM660_SSCCX_VFL] =		&sdm660_vdd_ssccx_vfl,
	[SDM660_SSCMX] =		&sdm660_vdd_sscmx,
	[SDM660_SSCMX_VFL] =		&sdm660_vdd_sscmx_vfl,
पूर्ण;

अटल स्थिर काष्ठा rpmpd_desc sdm660_desc = अणु
	.rpmpds = sdm660_rpmpds,
	.num_pds = ARRAY_SIZE(sdm660_rpmpds),
	.max_state = RPM_SMD_LEVEL_TURBO,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rpmpd_match_table[] = अणु
	अणु .compatible = "qcom,msm8916-rpmpd", .data = &msm8916_desc पूर्ण,
	अणु .compatible = "qcom,msm8939-rpmpd", .data = &msm8939_desc पूर्ण,
	अणु .compatible = "qcom,msm8976-rpmpd", .data = &msm8976_desc पूर्ण,
	अणु .compatible = "qcom,msm8994-rpmpd", .data = &msm8994_desc पूर्ण,
	अणु .compatible = "qcom,msm8996-rpmpd", .data = &msm8996_desc पूर्ण,
	अणु .compatible = "qcom,msm8998-rpmpd", .data = &msm8998_desc पूर्ण,
	अणु .compatible = "qcom,qcs404-rpmpd", .data = &qcs404_desc पूर्ण,
	अणु .compatible = "qcom,sdm660-rpmpd", .data = &sdm660_desc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rpmpd_match_table);

अटल पूर्णांक rpmpd_send_enable(काष्ठा rpmpd *pd, bool enable)
अणु
	काष्ठा rpmpd_req req = अणु
		.key = KEY_ENABLE,
		.nbytes = cpu_to_le32(माप(u32)),
		.value = cpu_to_le32(enable),
	पूर्ण;

	वापस qcom_rpm_smd_ग_लिखो(pd->rpm, QCOM_SMD_RPM_ACTIVE_STATE,
				  pd->res_type, pd->res_id, &req, माप(req));
पूर्ण

अटल पूर्णांक rpmpd_send_corner(काष्ठा rpmpd *pd, पूर्णांक state, अचिन्हित पूर्णांक corner)
अणु
	काष्ठा rpmpd_req req = अणु
		.key = pd->key,
		.nbytes = cpu_to_le32(माप(u32)),
		.value = cpu_to_le32(corner),
	पूर्ण;

	वापस qcom_rpm_smd_ग_लिखो(pd->rpm, state, pd->res_type, pd->res_id,
				  &req, माप(req));
पूर्ण;

अटल व्योम to_active_sleep(काष्ठा rpmpd *pd, अचिन्हित पूर्णांक corner,
			    अचिन्हित पूर्णांक *active, अचिन्हित पूर्णांक *sleep)
अणु
	*active = corner;

	अगर (pd->active_only)
		*sleep = 0;
	अन्यथा
		*sleep = *active;
पूर्ण

अटल पूर्णांक rpmpd_aggregate_corner(काष्ठा rpmpd *pd)
अणु
	पूर्णांक ret;
	काष्ठा rpmpd *peer = pd->peer;
	अचिन्हित पूर्णांक active_corner, sleep_corner;
	अचिन्हित पूर्णांक this_active_corner = 0, this_sleep_corner = 0;
	अचिन्हित पूर्णांक peer_active_corner = 0, peer_sleep_corner = 0;

	to_active_sleep(pd, pd->corner, &this_active_corner, &this_sleep_corner);

	अगर (peer && peer->enabled)
		to_active_sleep(peer, peer->corner, &peer_active_corner,
				&peer_sleep_corner);

	active_corner = max(this_active_corner, peer_active_corner);

	ret = rpmpd_send_corner(pd, QCOM_SMD_RPM_ACTIVE_STATE, active_corner);
	अगर (ret)
		वापस ret;

	sleep_corner = max(this_sleep_corner, peer_sleep_corner);

	वापस rpmpd_send_corner(pd, QCOM_SMD_RPM_SLEEP_STATE, sleep_corner);
पूर्ण

अटल पूर्णांक rpmpd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक ret;
	काष्ठा rpmpd *pd = करोमुख्य_to_rpmpd(करोमुख्य);

	mutex_lock(&rpmpd_lock);

	ret = rpmpd_send_enable(pd, true);
	अगर (ret)
		जाओ out;

	pd->enabled = true;

	अगर (pd->corner)
		ret = rpmpd_aggregate_corner(pd);

out:
	mutex_unlock(&rpmpd_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpmpd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक ret;
	काष्ठा rpmpd *pd = करोमुख्य_to_rpmpd(करोमुख्य);

	mutex_lock(&rpmpd_lock);

	ret = rpmpd_send_enable(pd, false);
	अगर (!ret)
		pd->enabled = false;

	mutex_unlock(&rpmpd_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpmpd_set_perक्रमmance(काष्ठा generic_pm_करोमुख्य *करोमुख्य,
				 अचिन्हित पूर्णांक state)
अणु
	पूर्णांक ret = 0;
	काष्ठा rpmpd *pd = करोमुख्य_to_rpmpd(करोमुख्य);

	अगर (state > pd->max_state)
		state = pd->max_state;

	mutex_lock(&rpmpd_lock);

	pd->corner = state;

	/* Always send updates क्रम vfc and vfl */
	अगर (!pd->enabled && pd->key != KEY_FLOOR_CORNER &&
	    pd->key != KEY_FLOOR_LEVEL)
		जाओ out;

	ret = rpmpd_aggregate_corner(pd);

out:
	mutex_unlock(&rpmpd_lock);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक rpmpd_get_perक्रमmance(काष्ठा generic_pm_करोमुख्य *genpd,
					  काष्ठा dev_pm_opp *opp)
अणु
	वापस dev_pm_opp_get_level(opp);
पूर्ण

अटल पूर्णांक rpmpd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	माप_प्रकार num;
	काष्ठा genpd_onecell_data *data;
	काष्ठा qcom_smd_rpm *rpm;
	काष्ठा rpmpd **rpmpds;
	स्थिर काष्ठा rpmpd_desc *desc;

	rpm = dev_get_drvdata(pdev->dev.parent);
	अगर (!rpm) अणु
		dev_err(&pdev->dev, "Unable to retrieve handle to RPM\n");
		वापस -ENODEV;
	पूर्ण

	desc = of_device_get_match_data(&pdev->dev);
	अगर (!desc)
		वापस -EINVAL;

	rpmpds = desc->rpmpds;
	num = desc->num_pds;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->करोमुख्यs = devm_kसुस्मृति(&pdev->dev, num, माप(*data->करोमुख्यs),
				     GFP_KERNEL);
	data->num_करोमुख्यs = num;

	क्रम (i = 0; i < num; i++) अणु
		अगर (!rpmpds[i]) अणु
			dev_warn(&pdev->dev, "rpmpds[] with empty entry at index=%d\n",
				 i);
			जारी;
		पूर्ण

		rpmpds[i]->rpm = rpm;
		rpmpds[i]->max_state = desc->max_state;
		rpmpds[i]->pd.घातer_off = rpmpd_घातer_off;
		rpmpds[i]->pd.घातer_on = rpmpd_घातer_on;
		rpmpds[i]->pd.set_perक्रमmance_state = rpmpd_set_perक्रमmance;
		rpmpds[i]->pd.opp_to_perक्रमmance_state = rpmpd_get_perक्रमmance;
		pm_genpd_init(&rpmpds[i]->pd, शून्य, true);

		data->करोमुख्यs[i] = &rpmpds[i]->pd;
	पूर्ण

	वापस of_genpd_add_provider_onecell(pdev->dev.of_node, data);
पूर्ण

अटल काष्ठा platक्रमm_driver rpmpd_driver = अणु
	.driver = अणु
		.name = "qcom-rpmpd",
		.of_match_table = rpmpd_match_table,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = rpmpd_probe,
पूर्ण;

अटल पूर्णांक __init rpmpd_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rpmpd_driver);
पूर्ण
core_initcall(rpmpd_init);

MODULE_DESCRIPTION("Qualcomm Technologies, Inc. RPM Power Domain Driver");
MODULE_LICENSE("GPL v2");
