<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Surface Platक्रमm Profile / Perक्रमmance Mode driver क्रम Surface System
 * Aggregator Module (thermal subप्रणाली).
 *
 * Copyright (C) 2021 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_profile.h>
#समावेश <linux/types.h>

#समावेश <linux/surface_aggregator/device.h>

क्रमागत ssam_पंचांगp_profile अणु
	SSAM_TMP_PROखाता_NORMAL             = 1,
	SSAM_TMP_PROखाता_BATTERY_SAVER      = 2,
	SSAM_TMP_PROखाता_BETTER_PERFORMANCE = 3,
	SSAM_TMP_PROखाता_BEST_PERFORMANCE   = 4,
पूर्ण;

काष्ठा ssam_पंचांगp_profile_info अणु
	__le32 profile;
	__le16 unknown1;
	__le16 unknown2;
पूर्ण __packed;

काष्ठा ssam_पंचांगp_profile_device अणु
	काष्ठा ssam_device *sdev;
	काष्ठा platक्रमm_profile_handler handler;
पूर्ण;

SSAM_DEFINE_SYNC_REQUEST_CL_R(__ssam_पंचांगp_profile_get, काष्ठा ssam_पंचांगp_profile_info, अणु
	.target_category = SSAM_SSH_TC_TMP,
	.command_id      = 0x02,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_CL_W(__ssam_पंचांगp_profile_set, __le32, अणु
	.target_category = SSAM_SSH_TC_TMP,
	.command_id      = 0x03,
पूर्ण);

अटल पूर्णांक ssam_पंचांगp_profile_get(काष्ठा ssam_device *sdev, क्रमागत ssam_पंचांगp_profile *p)
अणु
	काष्ठा ssam_पंचांगp_profile_info info;
	पूर्णांक status;

	status = ssam_retry(__ssam_पंचांगp_profile_get, sdev, &info);
	अगर (status < 0)
		वापस status;

	*p = le32_to_cpu(info.profile);
	वापस 0;
पूर्ण

अटल पूर्णांक ssam_पंचांगp_profile_set(काष्ठा ssam_device *sdev, क्रमागत ssam_पंचांगp_profile p)
अणु
	__le32 profile_le = cpu_to_le32(p);

	वापस ssam_retry(__ssam_पंचांगp_profile_set, sdev, &profile_le);
पूर्ण

अटल पूर्णांक convert_ssam_to_profile(काष्ठा ssam_device *sdev, क्रमागत ssam_पंचांगp_profile p)
अणु
	चयन (p) अणु
	हाल SSAM_TMP_PROखाता_NORMAL:
		वापस PLATFORM_PROखाता_BALANCED;

	हाल SSAM_TMP_PROखाता_BATTERY_SAVER:
		वापस PLATFORM_PROखाता_LOW_POWER;

	हाल SSAM_TMP_PROखाता_BETTER_PERFORMANCE:
		वापस PLATFORM_PROखाता_BALANCED_PERFORMANCE;

	हाल SSAM_TMP_PROखाता_BEST_PERFORMANCE:
		वापस PLATFORM_PROखाता_PERFORMANCE;

	शेष:
		dev_err(&sdev->dev, "invalid performance profile: %d", p);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक convert_profile_to_ssam(काष्ठा ssam_device *sdev, क्रमागत platक्रमm_profile_option p)
अणु
	चयन (p) अणु
	हाल PLATFORM_PROखाता_LOW_POWER:
		वापस SSAM_TMP_PROखाता_BATTERY_SAVER;

	हाल PLATFORM_PROखाता_BALANCED:
		वापस SSAM_TMP_PROखाता_NORMAL;

	हाल PLATFORM_PROखाता_BALANCED_PERFORMANCE:
		वापस SSAM_TMP_PROखाता_BETTER_PERFORMANCE;

	हाल PLATFORM_PROखाता_PERFORMANCE:
		वापस SSAM_TMP_PROखाता_BEST_PERFORMANCE;

	शेष:
		/* This should have alपढ़ोy been caught by platक्रमm_profile_store(). */
		WARN(true, "unsupported platform profile");
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ssam_platक्रमm_profile_get(काष्ठा platक्रमm_profile_handler *pprof,
				     क्रमागत platक्रमm_profile_option *profile)
अणु
	काष्ठा ssam_पंचांगp_profile_device *tpd;
	क्रमागत ssam_पंचांगp_profile tp;
	पूर्णांक status;

	tpd = container_of(pprof, काष्ठा ssam_पंचांगp_profile_device, handler);

	status = ssam_पंचांगp_profile_get(tpd->sdev, &tp);
	अगर (status)
		वापस status;

	status = convert_ssam_to_profile(tpd->sdev, tp);
	अगर (status < 0)
		वापस status;

	*profile = status;
	वापस 0;
पूर्ण

अटल पूर्णांक ssam_platक्रमm_profile_set(काष्ठा platक्रमm_profile_handler *pprof,
				     क्रमागत platक्रमm_profile_option profile)
अणु
	काष्ठा ssam_पंचांगp_profile_device *tpd;
	पूर्णांक tp;

	tpd = container_of(pprof, काष्ठा ssam_पंचांगp_profile_device, handler);

	tp = convert_profile_to_ssam(tpd->sdev, profile);
	अगर (tp < 0)
		वापस tp;

	वापस ssam_पंचांगp_profile_set(tpd->sdev, tp);
पूर्ण

अटल पूर्णांक surface_platक्रमm_profile_probe(काष्ठा ssam_device *sdev)
अणु
	काष्ठा ssam_पंचांगp_profile_device *tpd;

	tpd = devm_kzalloc(&sdev->dev, माप(*tpd), GFP_KERNEL);
	अगर (!tpd)
		वापस -ENOMEM;

	tpd->sdev = sdev;

	tpd->handler.profile_get = ssam_platक्रमm_profile_get;
	tpd->handler.profile_set = ssam_platक्रमm_profile_set;

	set_bit(PLATFORM_PROखाता_LOW_POWER, tpd->handler.choices);
	set_bit(PLATFORM_PROखाता_BALANCED, tpd->handler.choices);
	set_bit(PLATFORM_PROखाता_BALANCED_PERFORMANCE, tpd->handler.choices);
	set_bit(PLATFORM_PROखाता_PERFORMANCE, tpd->handler.choices);

	platक्रमm_profile_रेजिस्टर(&tpd->handler);
	वापस 0;
पूर्ण

अटल व्योम surface_platक्रमm_profile_हटाओ(काष्ठा ssam_device *sdev)
अणु
	platक्रमm_profile_हटाओ();
पूर्ण

अटल स्थिर काष्ठा ssam_device_id ssam_platक्रमm_profile_match[] = अणु
	अणु SSAM_SDEV(TMP, 0x01, 0x00, 0x01) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ssam, ssam_platक्रमm_profile_match);

अटल काष्ठा ssam_device_driver surface_platक्रमm_profile = अणु
	.probe = surface_platक्रमm_profile_probe,
	.हटाओ = surface_platक्रमm_profile_हटाओ,
	.match_table = ssam_platक्रमm_profile_match,
	.driver = अणु
		.name = "surface_platform_profile",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;
module_ssam_device_driver(surface_platक्रमm_profile);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("Platform Profile Support for Surface System Aggregator Module");
MODULE_LICENSE("GPL");
