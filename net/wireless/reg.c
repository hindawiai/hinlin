<शैली गुरु>
/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright 2007	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2008-2011	Luis R. Rodriguez <mcgrof@qca.qualcomm.com>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright      2017  Intel Deutschland GmbH
 * Copyright (C) 2018 - 2021 Intel Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


/**
 * DOC: Wireless regulatory infraकाष्ठाure
 *
 * The usual implementation is क्रम a driver to पढ़ो a device EEPROM to
 * determine which regulatory करोमुख्य it should be operating under, then
 * looking up the allowable channels in a driver-local table and finally
 * रेजिस्टरing those channels in the wiphy काष्ठाure.
 *
 * Another set of compliance enक्रमcement is क्रम drivers to use their
 * own compliance limits which can be stored on the EEPROM. The host
 * driver or firmware may ensure these are used.
 *
 * In addition to all this we provide an extra layer of regulatory
 * conक्रमmance. For drivers which करो not have any regulatory
 * inक्रमmation CRDA provides the complete regulatory solution.
 * For others it provides a community efक्रमt on further restrictions
 * to enhance compliance.
 *
 * Note: When number of rules --> infinity we will not be able to
 * index on alpha2 any more, instead we'll probably have to
 * rely on some SHA1 checksum of the regकरोमुख्य क्रम example.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/nl80211.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/verअगरication.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/firmware.h>
#समावेश <net/cfg80211.h>
#समावेश "core.h"
#समावेश "reg.h"
#समावेश "rdev-ops.h"
#समावेश "nl80211.h"

/*
 * Grace period we give beक्रमe making sure all current पूर्णांकerfaces reside on
 * channels allowed by the current regulatory करोमुख्य.
 */
#घोषणा REG_ENFORCE_GRACE_MS 60000

/**
 * क्रमागत reg_request_treaपंचांगent - regulatory request treaपंचांगent
 *
 * @REG_REQ_OK: जारी processing the regulatory request
 * @REG_REQ_IGNORE: ignore the regulatory request
 * @REG_REQ_INTERSECT: the regulatory करोमुख्य resulting from this request should
 *	be पूर्णांकersected with the current one.
 * @REG_REQ_ALREADY_SET: the regulatory request will not change the current
 *	regulatory settings, and no further processing is required.
 */
क्रमागत reg_request_treaपंचांगent अणु
	REG_REQ_OK,
	REG_REQ_IGNORE,
	REG_REQ_INTERSECT,
	REG_REQ_ALREADY_SET,
पूर्ण;

अटल काष्ठा regulatory_request core_request_world = अणु
	.initiator = NL80211_REGDOM_SET_BY_CORE,
	.alpha2[0] = '0',
	.alpha2[1] = '0',
	.पूर्णांकersect = false,
	.processed = true,
	.country_ie_env = ENVIRON_ANY,
पूर्ण;

/*
 * Receipt of inक्रमmation from last regulatory request,
 * रक्षित by RTNL (and can be accessed with RCU protection)
 */
अटल काष्ठा regulatory_request __rcu *last_request =
	(व्योम __क्रमce __rcu *)&core_request_world;

/* To trigger userspace events and load firmware */
अटल काष्ठा platक्रमm_device *reg_pdev;

/*
 * Central wireless core regulatory करोमुख्यs, we only need two,
 * the current one and a world regulatory करोमुख्य in हाल we have no
 * inक्रमmation to give us an alpha2.
 * (रक्षित by RTNL, can be पढ़ो under RCU)
 */
स्थिर काष्ठा ieee80211_regकरोमुख्य __rcu *cfg80211_regकरोमुख्य;

/*
 * Number of devices that रेजिस्टरed to the core
 * that support cellular base station regulatory hपूर्णांकs
 * (रक्षित by RTNL)
 */
अटल पूर्णांक reg_num_devs_support_basehपूर्णांक;

/*
 * State variable indicating अगर the platक्रमm on which the devices
 * are attached is operating in an inकरोor environment. The state variable
 * is relevant क्रम all रेजिस्टरed devices.
 */
अटल bool reg_is_inकरोor;
अटल DEFINE_SPINLOCK(reg_inकरोor_lock);

/* Used to track the userspace process controlling the inकरोor setting */
अटल u32 reg_is_inकरोor_portid;

अटल व्योम restore_regulatory_settings(bool reset_user, bool cached);
अटल व्योम prपूर्णांक_regकरोमुख्य(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd);

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य *get_cfg80211_regकरोm(व्योम)
अणु
	वापस rcu_dereference_rtnl(cfg80211_regकरोमुख्य);
पूर्ण

/*
 * Returns the regulatory करोमुख्य associated with the wiphy.
 *
 * Requires any of RTNL, wiphy mutex or RCU protection.
 */
स्थिर काष्ठा ieee80211_regकरोमुख्य *get_wiphy_regकरोm(काष्ठा wiphy *wiphy)
अणु
	वापस rcu_dereference_check(wiphy->regd,
				     lockdep_is_held(&wiphy->mtx) ||
				     lockdep_rtnl_is_held());
पूर्ण
EXPORT_SYMBOL(get_wiphy_regकरोm);

अटल स्थिर अक्षर *reg_dfs_region_str(क्रमागत nl80211_dfs_regions dfs_region)
अणु
	चयन (dfs_region) अणु
	हाल NL80211_DFS_UNSET:
		वापस "unset";
	हाल NL80211_DFS_FCC:
		वापस "FCC";
	हाल NL80211_DFS_ETSI:
		वापस "ETSI";
	हाल NL80211_DFS_JP:
		वापस "JP";
	पूर्ण
	वापस "Unknown";
पूर्ण

क्रमागत nl80211_dfs_regions reg_get_dfs_region(काष्ठा wiphy *wiphy)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd = शून्य;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *wiphy_regd = शून्य;

	rcu_पढ़ो_lock();
	regd = get_cfg80211_regकरोm();

	अगर (!wiphy)
		जाओ out;

	wiphy_regd = get_wiphy_regकरोm(wiphy);
	अगर (!wiphy_regd)
		जाओ out;

	अगर (wiphy_regd->dfs_region == regd->dfs_region)
		जाओ out;

	pr_debug("%s: device specific dfs_region (%s) disagrees with cfg80211's central dfs_region (%s)\n",
		 dev_name(&wiphy->dev),
		 reg_dfs_region_str(wiphy_regd->dfs_region),
		 reg_dfs_region_str(regd->dfs_region));

out:
	rcu_पढ़ो_unlock();

	वापस regd->dfs_region;
पूर्ण

अटल व्योम rcu_मुक्त_regकरोm(स्थिर काष्ठा ieee80211_regकरोमुख्य *r)
अणु
	अगर (!r)
		वापस;
	kमुक्त_rcu((काष्ठा ieee80211_regकरोमुख्य *)r, rcu_head);
पूर्ण

अटल काष्ठा regulatory_request *get_last_request(व्योम)
अणु
	वापस rcu_dereference_rtnl(last_request);
पूर्ण

/* Used to queue up regulatory hपूर्णांकs */
अटल LIST_HEAD(reg_requests_list);
अटल DEFINE_SPINLOCK(reg_requests_lock);

/* Used to queue up beacon hपूर्णांकs क्रम review */
अटल LIST_HEAD(reg_pending_beacons);
अटल DEFINE_SPINLOCK(reg_pending_beacons_lock);

/* Used to keep track of processed beacon hपूर्णांकs */
अटल LIST_HEAD(reg_beacon_list);

काष्ठा reg_beacon अणु
	काष्ठा list_head list;
	काष्ठा ieee80211_channel chan;
पूर्ण;

अटल व्योम reg_check_chans_work(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(reg_check_chans, reg_check_chans_work);

अटल व्योम reg_toकरो(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(reg_work, reg_toकरो);

/* We keep a अटल world regulatory करोमुख्य in हाल of the असलence of CRDA */
अटल स्थिर काष्ठा ieee80211_regकरोमुख्य world_regकरोm = अणु
	.n_reg_rules = 8,
	.alpha2 =  "00",
	.reg_rules = अणु
		/* IEEE 802.11b/g, channels 1..11 */
		REG_RULE(2412-10, 2462+10, 40, 6, 20, 0),
		/* IEEE 802.11b/g, channels 12..13. */
		REG_RULE(2467-10, 2472+10, 20, 6, 20,
			NL80211_RRF_NO_IR | NL80211_RRF_AUTO_BW),
		/* IEEE 802.11 channel 14 - Only JP enables
		 * this and क्रम 802.11b only */
		REG_RULE(2484-10, 2484+10, 20, 6, 20,
			NL80211_RRF_NO_IR |
			NL80211_RRF_NO_OFDM),
		/* IEEE 802.11a, channel 36..48 */
		REG_RULE(5180-10, 5240+10, 80, 6, 20,
                        NL80211_RRF_NO_IR |
                        NL80211_RRF_AUTO_BW),

		/* IEEE 802.11a, channel 52..64 - DFS required */
		REG_RULE(5260-10, 5320+10, 80, 6, 20,
			NL80211_RRF_NO_IR |
			NL80211_RRF_AUTO_BW |
			NL80211_RRF_DFS),

		/* IEEE 802.11a, channel 100..144 - DFS required */
		REG_RULE(5500-10, 5720+10, 160, 6, 20,
			NL80211_RRF_NO_IR |
			NL80211_RRF_DFS),

		/* IEEE 802.11a, channel 149..165 */
		REG_RULE(5745-10, 5825+10, 80, 6, 20,
			NL80211_RRF_NO_IR),

		/* IEEE 802.11ad (60GHz), channels 1..3 */
		REG_RULE(56160+2160*1-1080, 56160+2160*3+1080, 2160, 0, 0, 0),
	पूर्ण
पूर्ण;

/* रक्षित by RTNL */
अटल स्थिर काष्ठा ieee80211_regकरोमुख्य *cfg80211_world_regकरोm =
	&world_regकरोm;

अटल अक्षर *ieee80211_regकरोm = "00";
अटल अक्षर user_alpha2[2];
अटल स्थिर काष्ठा ieee80211_regकरोमुख्य *cfg80211_user_regकरोm;

module_param(ieee80211_regकरोm, अक्षरp, 0444);
MODULE_PARM_DESC(ieee80211_regकरोm, "IEEE 802.11 regulatory domain code");

अटल व्योम reg_मुक्त_request(काष्ठा regulatory_request *request)
अणु
	अगर (request == &core_request_world)
		वापस;

	अगर (request != get_last_request())
		kमुक्त(request);
पूर्ण

अटल व्योम reg_मुक्त_last_request(व्योम)
अणु
	काष्ठा regulatory_request *lr = get_last_request();

	अगर (lr != &core_request_world && lr)
		kमुक्त_rcu(lr, rcu_head);
पूर्ण

अटल व्योम reg_update_last_request(काष्ठा regulatory_request *request)
अणु
	काष्ठा regulatory_request *lr;

	lr = get_last_request();
	अगर (lr == request)
		वापस;

	reg_मुक्त_last_request();
	rcu_assign_poपूर्णांकer(last_request, request);
पूर्ण

अटल व्योम reset_regकरोमुख्यs(bool full_reset,
			     स्थिर काष्ठा ieee80211_regकरोमुख्य *new_regकरोm)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *r;

	ASSERT_RTNL();

	r = get_cfg80211_regकरोm();

	/* aव्योम मुक्तing अटल inक्रमmation or मुक्तing something twice */
	अगर (r == cfg80211_world_regकरोm)
		r = शून्य;
	अगर (cfg80211_world_regकरोm == &world_regकरोm)
		cfg80211_world_regकरोm = शून्य;
	अगर (r == &world_regकरोm)
		r = शून्य;

	rcu_मुक्त_regकरोm(r);
	rcu_मुक्त_regकरोm(cfg80211_world_regकरोm);

	cfg80211_world_regकरोm = &world_regकरोm;
	rcu_assign_poपूर्णांकer(cfg80211_regकरोमुख्य, new_regकरोm);

	अगर (!full_reset)
		वापस;

	reg_update_last_request(&core_request_world);
पूर्ण

/*
 * Dynamic world regulatory करोमुख्य requested by the wireless
 * core upon initialization
 */
अटल व्योम update_world_regकरोमुख्य(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd)
अणु
	काष्ठा regulatory_request *lr;

	lr = get_last_request();

	WARN_ON(!lr);

	reset_regकरोमुख्यs(false, rd);

	cfg80211_world_regकरोm = rd;
पूर्ण

bool is_world_regकरोm(स्थिर अक्षर *alpha2)
अणु
	अगर (!alpha2)
		वापस false;
	वापस alpha2[0] == '0' && alpha2[1] == '0';
पूर्ण

अटल bool is_alpha2_set(स्थिर अक्षर *alpha2)
अणु
	अगर (!alpha2)
		वापस false;
	वापस alpha2[0] && alpha2[1];
पूर्ण

अटल bool is_unknown_alpha2(स्थिर अक्षर *alpha2)
अणु
	अगर (!alpha2)
		वापस false;
	/*
	 * Special हाल where regulatory करोमुख्य was built by driver
	 * but a specअगरic alpha2 cannot be determined
	 */
	वापस alpha2[0] == '9' && alpha2[1] == '9';
पूर्ण

अटल bool is_पूर्णांकersected_alpha2(स्थिर अक्षर *alpha2)
अणु
	अगर (!alpha2)
		वापस false;
	/*
	 * Special हाल where regulatory करोमुख्य is the
	 * result of an पूर्णांकersection between two regulatory करोमुख्य
	 * काष्ठाures
	 */
	वापस alpha2[0] == '9' && alpha2[1] == '8';
पूर्ण

अटल bool is_an_alpha2(स्थिर अक्षर *alpha2)
अणु
	अगर (!alpha2)
		वापस false;
	वापस है_अक्षर(alpha2[0]) && है_अक्षर(alpha2[1]);
पूर्ण

अटल bool alpha2_equal(स्थिर अक्षर *alpha2_x, स्थिर अक्षर *alpha2_y)
अणु
	अगर (!alpha2_x || !alpha2_y)
		वापस false;
	वापस alpha2_x[0] == alpha2_y[0] && alpha2_x[1] == alpha2_y[1];
पूर्ण

अटल bool regकरोm_changes(स्थिर अक्षर *alpha2)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *r = get_cfg80211_regकरोm();

	अगर (!r)
		वापस true;
	वापस !alpha2_equal(r->alpha2, alpha2);
पूर्ण

/*
 * The NL80211_REGDOM_SET_BY_USER regकरोm alpha2 is cached, this lets
 * you know अगर a valid regulatory hपूर्णांक with NL80211_REGDOM_SET_BY_USER
 * has ever been issued.
 */
अटल bool is_user_regकरोm_saved(व्योम)
अणु
	अगर (user_alpha2[0] == '9' && user_alpha2[1] == '7')
		वापस false;

	/* This would indicate a mistake on the design */
	अगर (WARN(!is_world_regकरोm(user_alpha2) && !is_an_alpha2(user_alpha2),
		 "Unexpected user alpha2: %c%c\n",
		 user_alpha2[0], user_alpha2[1]))
		वापस false;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य *
reg_copy_regd(स्थिर काष्ठा ieee80211_regकरोमुख्य *src_regd)
अणु
	काष्ठा ieee80211_regकरोमुख्य *regd;
	अचिन्हित पूर्णांक i;

	regd = kzalloc(काष्ठा_size(regd, reg_rules, src_regd->n_reg_rules),
		       GFP_KERNEL);
	अगर (!regd)
		वापस ERR_PTR(-ENOMEM);

	स_नकल(regd, src_regd, माप(काष्ठा ieee80211_regकरोमुख्य));

	क्रम (i = 0; i < src_regd->n_reg_rules; i++)
		स_नकल(&regd->reg_rules[i], &src_regd->reg_rules[i],
		       माप(काष्ठा ieee80211_reg_rule));

	वापस regd;
पूर्ण

अटल व्योम cfg80211_save_user_regकरोm(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd)
अणु
	ASSERT_RTNL();

	अगर (!IS_ERR(cfg80211_user_regकरोm))
		kमुक्त(cfg80211_user_regकरोm);
	cfg80211_user_regकरोm = reg_copy_regd(rd);
पूर्ण

काष्ठा reg_regdb_apply_request अणु
	काष्ठा list_head list;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regकरोm;
पूर्ण;

अटल LIST_HEAD(reg_regdb_apply_list);
अटल DEFINE_MUTEX(reg_regdb_apply_mutex);

अटल व्योम reg_regdb_apply(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा reg_regdb_apply_request *request;

	rtnl_lock();

	mutex_lock(&reg_regdb_apply_mutex);
	जबतक (!list_empty(&reg_regdb_apply_list)) अणु
		request = list_first_entry(&reg_regdb_apply_list,
					   काष्ठा reg_regdb_apply_request,
					   list);
		list_del(&request->list);

		set_regकरोm(request->regकरोm, REGD_SOURCE_INTERNAL_DB);
		kमुक्त(request);
	पूर्ण
	mutex_unlock(&reg_regdb_apply_mutex);

	rtnl_unlock();
पूर्ण

अटल DECLARE_WORK(reg_regdb_work, reg_regdb_apply);

अटल पूर्णांक reg_schedule_apply(स्थिर काष्ठा ieee80211_regकरोमुख्य *regकरोm)
अणु
	काष्ठा reg_regdb_apply_request *request;

	request = kzalloc(माप(काष्ठा reg_regdb_apply_request), GFP_KERNEL);
	अगर (!request) अणु
		kमुक्त(regकरोm);
		वापस -ENOMEM;
	पूर्ण

	request->regकरोm = regकरोm;

	mutex_lock(&reg_regdb_apply_mutex);
	list_add_tail(&request->list, &reg_regdb_apply_list);
	mutex_unlock(&reg_regdb_apply_mutex);

	schedule_work(&reg_regdb_work);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CFG80211_CRDA_SUPPORT
/* Max number of consecutive attempts to communicate with CRDA  */
#घोषणा REG_MAX_CRDA_TIMEOUTS 10

अटल u32 reg_crda_समयouts;

अटल व्योम crda_समयout_work(काष्ठा work_काष्ठा *work);
अटल DECLARE_DELAYED_WORK(crda_समयout, crda_समयout_work);

अटल व्योम crda_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	pr_debug("Timeout while waiting for CRDA to reply, restoring regulatory settings\n");
	rtnl_lock();
	reg_crda_समयouts++;
	restore_regulatory_settings(true, false);
	rtnl_unlock();
पूर्ण

अटल व्योम cancel_crda_समयout(व्योम)
अणु
	cancel_delayed_work(&crda_समयout);
पूर्ण

अटल व्योम cancel_crda_समयout_sync(व्योम)
अणु
	cancel_delayed_work_sync(&crda_समयout);
पूर्ण

अटल व्योम reset_crda_समयouts(व्योम)
अणु
	reg_crda_समयouts = 0;
पूर्ण

/*
 * This lets us keep regulatory code which is updated on a regulatory
 * basis in userspace.
 */
अटल पूर्णांक call_crda(स्थिर अक्षर *alpha2)
अणु
	अक्षर country[12];
	अक्षर *env[] = अणु country, शून्य पूर्ण;
	पूर्णांक ret;

	snम_लिखो(country, माप(country), "COUNTRY=%c%c",
		 alpha2[0], alpha2[1]);

	अगर (reg_crda_समयouts > REG_MAX_CRDA_TIMEOUTS) अणु
		pr_debug("Exceeded CRDA call max attempts. Not calling CRDA\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!is_world_regकरोm((अक्षर *) alpha2))
		pr_debug("Calling CRDA for country: %c%c\n",
			 alpha2[0], alpha2[1]);
	अन्यथा
		pr_debug("Calling CRDA to update world regulatory domain\n");

	ret = kobject_uevent_env(&reg_pdev->dev.kobj, KOBJ_CHANGE, env);
	अगर (ret)
		वापस ret;

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &crda_समयout, msecs_to_jअगरfies(3142));
	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cancel_crda_समयout(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम cancel_crda_समयout_sync(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम reset_crda_समयouts(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक call_crda(स्थिर अक्षर *alpha2)
अणु
	वापस -ENODATA;
पूर्ण
#पूर्ण_अगर /* CONFIG_CFG80211_CRDA_SUPPORT */

/* code to directly load a firmware database through request_firmware */
अटल स्थिर काष्ठा fwdb_header *regdb;

काष्ठा fwdb_country अणु
	u8 alpha2[2];
	__be16 coll_ptr;
	/* this काष्ठा cannot be extended */
पूर्ण __packed __aligned(4);

काष्ठा fwdb_collection अणु
	u8 len;
	u8 n_rules;
	u8 dfs_region;
	/* no optional data yet */
	/* aligned to 2, then followed by __be16 array of rule poपूर्णांकers */
पूर्ण __packed __aligned(4);

क्रमागत fwdb_flags अणु
	FWDB_FLAG_NO_OFDM	= BIT(0),
	FWDB_FLAG_NO_OUTDOOR	= BIT(1),
	FWDB_FLAG_DFS		= BIT(2),
	FWDB_FLAG_NO_IR		= BIT(3),
	FWDB_FLAG_AUTO_BW	= BIT(4),
पूर्ण;

काष्ठा fwdb_wmm_ac अणु
	u8 ecw;
	u8 aअगरsn;
	__be16 cot;
पूर्ण __packed;

काष्ठा fwdb_wmm_rule अणु
	काष्ठा fwdb_wmm_ac client[IEEE80211_NUM_ACS];
	काष्ठा fwdb_wmm_ac ap[IEEE80211_NUM_ACS];
पूर्ण __packed;

काष्ठा fwdb_rule अणु
	u8 len;
	u8 flags;
	__be16 max_eirp;
	__be32 start, end, max_bw;
	/* start of optional data */
	__be16 cac_समयout;
	__be16 wmm_ptr;
पूर्ण __packed __aligned(4);

#घोषणा FWDB_MAGIC 0x52474442
#घोषणा FWDB_VERSION 20

काष्ठा fwdb_header अणु
	__be32 magic;
	__be32 version;
	काष्ठा fwdb_country country[];
पूर्ण __packed __aligned(4);

अटल पूर्णांक ecw2cw(पूर्णांक ecw)
अणु
	वापस (1 << ecw) - 1;
पूर्ण

अटल bool valid_wmm(काष्ठा fwdb_wmm_rule *rule)
अणु
	काष्ठा fwdb_wmm_ac *ac = (काष्ठा fwdb_wmm_ac *)rule;
	पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_NUM_ACS * 2; i++) अणु
		u16 cw_min = ecw2cw((ac[i].ecw & 0xf0) >> 4);
		u16 cw_max = ecw2cw(ac[i].ecw & 0x0f);
		u8 aअगरsn = ac[i].aअगरsn;

		अगर (cw_min >= cw_max)
			वापस false;

		अगर (aअगरsn < 1)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool valid_rule(स्थिर u8 *data, अचिन्हित पूर्णांक size, u16 rule_ptr)
अणु
	काष्ठा fwdb_rule *rule = (व्योम *)(data + (rule_ptr << 2));

	अगर ((u8 *)rule + माप(rule->len) > data + size)
		वापस false;

	/* mandatory fields */
	अगर (rule->len < दुरत्वend(काष्ठा fwdb_rule, max_bw))
		वापस false;
	अगर (rule->len >= दुरत्वend(काष्ठा fwdb_rule, wmm_ptr)) अणु
		u32 wmm_ptr = be16_to_cpu(rule->wmm_ptr) << 2;
		काष्ठा fwdb_wmm_rule *wmm;

		अगर (wmm_ptr + माप(काष्ठा fwdb_wmm_rule) > size)
			वापस false;

		wmm = (व्योम *)(data + wmm_ptr);

		अगर (!valid_wmm(wmm))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool valid_country(स्थिर u8 *data, अचिन्हित पूर्णांक size,
			  स्थिर काष्ठा fwdb_country *country)
अणु
	अचिन्हित पूर्णांक ptr = be16_to_cpu(country->coll_ptr) << 2;
	काष्ठा fwdb_collection *coll = (व्योम *)(data + ptr);
	__be16 *rules_ptr;
	अचिन्हित पूर्णांक i;

	/* make sure we can पढ़ो len/n_rules */
	अगर ((u8 *)coll + दुरत्वend(typeof(*coll), n_rules) > data + size)
		वापस false;

	/* make sure base काष्ठा and all rules fit */
	अगर ((u8 *)coll + ALIGN(coll->len, 2) +
	    (coll->n_rules * 2) > data + size)
		वापस false;

	/* mandatory fields must exist */
	अगर (coll->len < दुरत्वend(काष्ठा fwdb_collection, dfs_region))
		वापस false;

	rules_ptr = (व्योम *)((u8 *)coll + ALIGN(coll->len, 2));

	क्रम (i = 0; i < coll->n_rules; i++) अणु
		u16 rule_ptr = be16_to_cpu(rules_ptr[i]);

		अगर (!valid_rule(data, size, rule_ptr))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_CFG80211_REQUIRE_SIGNED_REGDB
अटल काष्ठा key *builtin_regdb_keys;

अटल व्योम __init load_keys_from_buffer(स्थिर u8 *p, अचिन्हित पूर्णांक buflen)
अणु
	स्थिर u8 *end = p + buflen;
	माप_प्रकार plen;
	key_ref_t key;

	जबतक (p < end) अणु
		/* Each cert begins with an ASN.1 SEQUENCE tag and must be more
		 * than 256 bytes in size.
		 */
		अगर (end - p < 4)
			जाओ करोdgy_cert;
		अगर (p[0] != 0x30 &&
		    p[1] != 0x82)
			जाओ करोdgy_cert;
		plen = (p[2] << 8) | p[3];
		plen += 4;
		अगर (plen > end - p)
			जाओ करोdgy_cert;

		key = key_create_or_update(make_key_ref(builtin_regdb_keys, 1),
					   "asymmetric", शून्य, p, plen,
					   ((KEY_POS_ALL & ~KEY_POS_SETATTR) |
					    KEY_USR_VIEW | KEY_USR_READ),
					   KEY_ALLOC_NOT_IN_QUOTA |
					   KEY_ALLOC_BUILT_IN |
					   KEY_ALLOC_BYPASS_RESTRICTION);
		अगर (IS_ERR(key)) अणु
			pr_err("Problem loading in-kernel X.509 certificate (%ld)\n",
			       PTR_ERR(key));
		पूर्ण अन्यथा अणु
			pr_notice("Loaded X.509 cert '%s'\n",
				  key_ref_to_ptr(key)->description);
			key_ref_put(key);
		पूर्ण
		p += plen;
	पूर्ण

	वापस;

करोdgy_cert:
	pr_err("Problem parsing in-kernel X.509 certificate list\n");
पूर्ण

अटल पूर्णांक __init load_builtin_regdb_keys(व्योम)
अणु
	builtin_regdb_keys =
		keyring_alloc(".builtin_regdb_keys",
			      KUIDT_INIT(0), KGIDT_INIT(0), current_cred(),
			      ((KEY_POS_ALL & ~KEY_POS_SETATTR) |
			      KEY_USR_VIEW | KEY_USR_READ | KEY_USR_SEARCH),
			      KEY_ALLOC_NOT_IN_QUOTA, शून्य, शून्य);
	अगर (IS_ERR(builtin_regdb_keys))
		वापस PTR_ERR(builtin_regdb_keys);

	pr_notice("Loading compiled-in X.509 certificates for regulatory database\n");

#अगर_घोषित CONFIG_CFG80211_USE_KERNEL_REGDB_KEYS
	load_keys_from_buffer(shipped_regdb_certs, shipped_regdb_certs_len);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CFG80211_EXTRA_REGDB_KEYसूची
	अगर (CONFIG_CFG80211_EXTRA_REGDB_KEYसूची[0] != '\0')
		load_keys_from_buffer(extra_regdb_certs, extra_regdb_certs_len);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल bool regdb_has_valid_signature(स्थिर u8 *data, अचिन्हित पूर्णांक size)
अणु
	स्थिर काष्ठा firmware *sig;
	bool result;

	अगर (request_firmware(&sig, "regulatory.db.p7s", &reg_pdev->dev))
		वापस false;

	result = verअगरy_pkcs7_signature(data, size, sig->data, sig->size,
					builtin_regdb_keys,
					VERIFYING_UNSPECIFIED_SIGNATURE,
					शून्य, शून्य) == 0;

	release_firmware(sig);

	वापस result;
पूर्ण

अटल व्योम मुक्त_regdb_keyring(व्योम)
अणु
	key_put(builtin_regdb_keys);
पूर्ण
#अन्यथा
अटल पूर्णांक load_builtin_regdb_keys(व्योम)
अणु
	वापस 0;
पूर्ण

अटल bool regdb_has_valid_signature(स्थिर u8 *data, अचिन्हित पूर्णांक size)
अणु
	वापस true;
पूर्ण

अटल व्योम मुक्त_regdb_keyring(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_CFG80211_REQUIRE_SIGNED_REGDB */

अटल bool valid_regdb(स्थिर u8 *data, अचिन्हित पूर्णांक size)
अणु
	स्थिर काष्ठा fwdb_header *hdr = (व्योम *)data;
	स्थिर काष्ठा fwdb_country *country;

	अगर (size < माप(*hdr))
		वापस false;

	अगर (hdr->magic != cpu_to_be32(FWDB_MAGIC))
		वापस false;

	अगर (hdr->version != cpu_to_be32(FWDB_VERSION))
		वापस false;

	अगर (!regdb_has_valid_signature(data, size))
		वापस false;

	country = &hdr->country[0];
	जबतक ((u8 *)(country + 1) <= data + size) अणु
		अगर (!country->coll_ptr)
			अवरोध;
		अगर (!valid_country(data, size, country))
			वापस false;
		country++;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम set_wmm_rule(स्थिर काष्ठा fwdb_header *db,
			 स्थिर काष्ठा fwdb_country *country,
			 स्थिर काष्ठा fwdb_rule *rule,
			 काष्ठा ieee80211_reg_rule *rrule)
अणु
	काष्ठा ieee80211_wmm_rule *wmm_rule = &rrule->wmm_rule;
	काष्ठा fwdb_wmm_rule *wmm;
	अचिन्हित पूर्णांक i, wmm_ptr;

	wmm_ptr = be16_to_cpu(rule->wmm_ptr) << 2;
	wmm = (व्योम *)((u8 *)db + wmm_ptr);

	अगर (!valid_wmm(wmm)) अणु
		pr_err("Invalid regulatory WMM rule %u-%u in domain %c%c\n",
		       be32_to_cpu(rule->start), be32_to_cpu(rule->end),
		       country->alpha2[0], country->alpha2[1]);
		वापस;
	पूर्ण

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		wmm_rule->client[i].cw_min =
			ecw2cw((wmm->client[i].ecw & 0xf0) >> 4);
		wmm_rule->client[i].cw_max = ecw2cw(wmm->client[i].ecw & 0x0f);
		wmm_rule->client[i].aअगरsn =  wmm->client[i].aअगरsn;
		wmm_rule->client[i].cot =
			1000 * be16_to_cpu(wmm->client[i].cot);
		wmm_rule->ap[i].cw_min = ecw2cw((wmm->ap[i].ecw & 0xf0) >> 4);
		wmm_rule->ap[i].cw_max = ecw2cw(wmm->ap[i].ecw & 0x0f);
		wmm_rule->ap[i].aअगरsn = wmm->ap[i].aअगरsn;
		wmm_rule->ap[i].cot = 1000 * be16_to_cpu(wmm->ap[i].cot);
	पूर्ण

	rrule->has_wmm = true;
पूर्ण

अटल पूर्णांक __regdb_query_wmm(स्थिर काष्ठा fwdb_header *db,
			     स्थिर काष्ठा fwdb_country *country, पूर्णांक freq,
			     काष्ठा ieee80211_reg_rule *rrule)
अणु
	अचिन्हित पूर्णांक ptr = be16_to_cpu(country->coll_ptr) << 2;
	काष्ठा fwdb_collection *coll = (व्योम *)((u8 *)db + ptr);
	पूर्णांक i;

	क्रम (i = 0; i < coll->n_rules; i++) अणु
		__be16 *rules_ptr = (व्योम *)((u8 *)coll + ALIGN(coll->len, 2));
		अचिन्हित पूर्णांक rule_ptr = be16_to_cpu(rules_ptr[i]) << 2;
		काष्ठा fwdb_rule *rule = (व्योम *)((u8 *)db + rule_ptr);

		अगर (rule->len < दुरत्वend(काष्ठा fwdb_rule, wmm_ptr))
			जारी;

		अगर (freq >= KHZ_TO_MHZ(be32_to_cpu(rule->start)) &&
		    freq <= KHZ_TO_MHZ(be32_to_cpu(rule->end))) अणु
			set_wmm_rule(db, country, rule, rrule);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENODATA;
पूर्ण

पूर्णांक reg_query_regdb_wmm(अक्षर *alpha2, पूर्णांक freq, काष्ठा ieee80211_reg_rule *rule)
अणु
	स्थिर काष्ठा fwdb_header *hdr = regdb;
	स्थिर काष्ठा fwdb_country *country;

	अगर (!regdb)
		वापस -ENODATA;

	अगर (IS_ERR(regdb))
		वापस PTR_ERR(regdb);

	country = &hdr->country[0];
	जबतक (country->coll_ptr) अणु
		अगर (alpha2_equal(alpha2, country->alpha2))
			वापस __regdb_query_wmm(regdb, country, freq, rule);

		country++;
	पूर्ण

	वापस -ENODATA;
पूर्ण
EXPORT_SYMBOL(reg_query_regdb_wmm);

अटल पूर्णांक regdb_query_country(स्थिर काष्ठा fwdb_header *db,
			       स्थिर काष्ठा fwdb_country *country)
अणु
	अचिन्हित पूर्णांक ptr = be16_to_cpu(country->coll_ptr) << 2;
	काष्ठा fwdb_collection *coll = (व्योम *)((u8 *)db + ptr);
	काष्ठा ieee80211_regकरोमुख्य *regकरोm;
	अचिन्हित पूर्णांक i;

	regकरोm = kzalloc(काष्ठा_size(regकरोm, reg_rules, coll->n_rules),
			 GFP_KERNEL);
	अगर (!regकरोm)
		वापस -ENOMEM;

	regकरोm->n_reg_rules = coll->n_rules;
	regकरोm->alpha2[0] = country->alpha2[0];
	regकरोm->alpha2[1] = country->alpha2[1];
	regकरोm->dfs_region = coll->dfs_region;

	क्रम (i = 0; i < regकरोm->n_reg_rules; i++) अणु
		__be16 *rules_ptr = (व्योम *)((u8 *)coll + ALIGN(coll->len, 2));
		अचिन्हित पूर्णांक rule_ptr = be16_to_cpu(rules_ptr[i]) << 2;
		काष्ठा fwdb_rule *rule = (व्योम *)((u8 *)db + rule_ptr);
		काष्ठा ieee80211_reg_rule *rrule = &regकरोm->reg_rules[i];

		rrule->freq_range.start_freq_khz = be32_to_cpu(rule->start);
		rrule->freq_range.end_freq_khz = be32_to_cpu(rule->end);
		rrule->freq_range.max_bandwidth_khz = be32_to_cpu(rule->max_bw);

		rrule->घातer_rule.max_antenna_gain = 0;
		rrule->घातer_rule.max_eirp = be16_to_cpu(rule->max_eirp);

		rrule->flags = 0;
		अगर (rule->flags & FWDB_FLAG_NO_OFDM)
			rrule->flags |= NL80211_RRF_NO_OFDM;
		अगर (rule->flags & FWDB_FLAG_NO_OUTDOOR)
			rrule->flags |= NL80211_RRF_NO_OUTDOOR;
		अगर (rule->flags & FWDB_FLAG_DFS)
			rrule->flags |= NL80211_RRF_DFS;
		अगर (rule->flags & FWDB_FLAG_NO_IR)
			rrule->flags |= NL80211_RRF_NO_IR;
		अगर (rule->flags & FWDB_FLAG_AUTO_BW)
			rrule->flags |= NL80211_RRF_AUTO_BW;

		rrule->dfs_cac_ms = 0;

		/* handle optional data */
		अगर (rule->len >= दुरत्वend(काष्ठा fwdb_rule, cac_समयout))
			rrule->dfs_cac_ms =
				1000 * be16_to_cpu(rule->cac_समयout);
		अगर (rule->len >= दुरत्वend(काष्ठा fwdb_rule, wmm_ptr))
			set_wmm_rule(db, country, rule, rrule);
	पूर्ण

	वापस reg_schedule_apply(regकरोm);
पूर्ण

अटल पूर्णांक query_regdb(स्थिर अक्षर *alpha2)
अणु
	स्थिर काष्ठा fwdb_header *hdr = regdb;
	स्थिर काष्ठा fwdb_country *country;

	ASSERT_RTNL();

	अगर (IS_ERR(regdb))
		वापस PTR_ERR(regdb);

	country = &hdr->country[0];
	जबतक (country->coll_ptr) अणु
		अगर (alpha2_equal(alpha2, country->alpha2))
			वापस regdb_query_country(regdb, country);
		country++;
	पूर्ण

	वापस -ENODATA;
पूर्ण

अटल व्योम regdb_fw_cb(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	पूर्णांक set_error = 0;
	bool restore = true;
	व्योम *db;

	अगर (!fw) अणु
		pr_info("failed to load regulatory.db\n");
		set_error = -ENODATA;
	पूर्ण अन्यथा अगर (!valid_regdb(fw->data, fw->size)) अणु
		pr_info("loaded regulatory.db is malformed or signature is missing/invalid\n");
		set_error = -EINVAL;
	पूर्ण

	rtnl_lock();
	अगर (regdb && !IS_ERR(regdb)) अणु
		/* negative हाल - a bug
		 * positive हाल - can happen due to race in हाल of multiple cb's in
		 * queue, due to usage of asynchronous callback
		 *
		 * Either हाल, just restore and मुक्त new db.
		 */
	पूर्ण अन्यथा अगर (set_error) अणु
		regdb = ERR_PTR(set_error);
	पूर्ण अन्यथा अगर (fw) अणु
		db = kmemdup(fw->data, fw->size, GFP_KERNEL);
		अगर (db) अणु
			regdb = db;
			restore = context && query_regdb(context);
		पूर्ण अन्यथा अणु
			restore = true;
		पूर्ण
	पूर्ण

	अगर (restore)
		restore_regulatory_settings(true, false);

	rtnl_unlock();

	kमुक्त(context);

	release_firmware(fw);
पूर्ण

अटल पूर्णांक query_regdb_file(स्थिर अक्षर *alpha2)
अणु
	ASSERT_RTNL();

	अगर (regdb)
		वापस query_regdb(alpha2);

	alpha2 = kmemdup(alpha2, 2, GFP_KERNEL);
	अगर (!alpha2)
		वापस -ENOMEM;

	वापस request_firmware_noरुको(THIS_MODULE, true, "regulatory.db",
				       &reg_pdev->dev, GFP_KERNEL,
				       (व्योम *)alpha2, regdb_fw_cb);
पूर्ण

पूर्णांक reg_reload_regdb(व्योम)
अणु
	स्थिर काष्ठा firmware *fw;
	व्योम *db;
	पूर्णांक err;

	err = request_firmware(&fw, "regulatory.db", &reg_pdev->dev);
	अगर (err)
		वापस err;

	अगर (!valid_regdb(fw->data, fw->size)) अणु
		err = -ENODATA;
		जाओ out;
	पूर्ण

	db = kmemdup(fw->data, fw->size, GFP_KERNEL);
	अगर (!db) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	rtnl_lock();
	अगर (!IS_ERR_OR_शून्य(regdb))
		kमुक्त(regdb);
	regdb = db;
	rtnl_unlock();

 out:
	release_firmware(fw);
	वापस err;
पूर्ण

अटल bool reg_query_database(काष्ठा regulatory_request *request)
अणु
	अगर (query_regdb_file(request->alpha2) == 0)
		वापस true;

	अगर (call_crda(request->alpha2) == 0)
		वापस true;

	वापस false;
पूर्ण

bool reg_is_valid_request(स्थिर अक्षर *alpha2)
अणु
	काष्ठा regulatory_request *lr = get_last_request();

	अगर (!lr || lr->processed)
		वापस false;

	वापस alpha2_equal(lr->alpha2, alpha2);
पूर्ण

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य *reg_get_regकरोमुख्य(काष्ठा wiphy *wiphy)
अणु
	काष्ठा regulatory_request *lr = get_last_request();

	/*
	 * Follow the driver's regulatory करोमुख्य, अगर present, unless a country
	 * IE has been processed or a user wants to help complaince further
	 */
	अगर (lr->initiator != NL80211_REGDOM_SET_BY_COUNTRY_IE &&
	    lr->initiator != NL80211_REGDOM_SET_BY_USER &&
	    wiphy->regd)
		वापस get_wiphy_regकरोm(wiphy);

	वापस get_cfg80211_regकरोm();
पूर्ण

अटल अचिन्हित पूर्णांक
reg_get_max_bandwidth_from_range(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd,
				 स्थिर काष्ठा ieee80211_reg_rule *rule)
अणु
	स्थिर काष्ठा ieee80211_freq_range *freq_range = &rule->freq_range;
	स्थिर काष्ठा ieee80211_freq_range *freq_range_पंचांगp;
	स्थिर काष्ठा ieee80211_reg_rule *पंचांगp;
	u32 start_freq, end_freq, idx, no;

	क्रम (idx = 0; idx < rd->n_reg_rules; idx++)
		अगर (rule == &rd->reg_rules[idx])
			अवरोध;

	अगर (idx == rd->n_reg_rules)
		वापस 0;

	/* get start_freq */
	no = idx;

	जबतक (no) अणु
		पंचांगp = &rd->reg_rules[--no];
		freq_range_पंचांगp = &पंचांगp->freq_range;

		अगर (freq_range_पंचांगp->end_freq_khz < freq_range->start_freq_khz)
			अवरोध;

		freq_range = freq_range_पंचांगp;
	पूर्ण

	start_freq = freq_range->start_freq_khz;

	/* get end_freq */
	freq_range = &rule->freq_range;
	no = idx;

	जबतक (no < rd->n_reg_rules - 1) अणु
		पंचांगp = &rd->reg_rules[++no];
		freq_range_पंचांगp = &पंचांगp->freq_range;

		अगर (freq_range_पंचांगp->start_freq_khz > freq_range->end_freq_khz)
			अवरोध;

		freq_range = freq_range_पंचांगp;
	पूर्ण

	end_freq = freq_range->end_freq_khz;

	वापस end_freq - start_freq;
पूर्ण

अचिन्हित पूर्णांक reg_get_max_bandwidth(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd,
				   स्थिर काष्ठा ieee80211_reg_rule *rule)
अणु
	अचिन्हित पूर्णांक bw = reg_get_max_bandwidth_from_range(rd, rule);

	अगर (rule->flags & NL80211_RRF_NO_160MHZ)
		bw = min_t(अचिन्हित पूर्णांक, bw, MHZ_TO_KHZ(80));
	अगर (rule->flags & NL80211_RRF_NO_80MHZ)
		bw = min_t(अचिन्हित पूर्णांक, bw, MHZ_TO_KHZ(40));

	/*
	 * HT40+/HT40- limits are handled per-channel. Only limit BW अगर both
	 * are not allowed.
	 */
	अगर (rule->flags & NL80211_RRF_NO_HT40MINUS &&
	    rule->flags & NL80211_RRF_NO_HT40PLUS)
		bw = min_t(अचिन्हित पूर्णांक, bw, MHZ_TO_KHZ(20));

	वापस bw;
पूर्ण

/* Sanity check on a regulatory rule */
अटल bool is_valid_reg_rule(स्थिर काष्ठा ieee80211_reg_rule *rule)
अणु
	स्थिर काष्ठा ieee80211_freq_range *freq_range = &rule->freq_range;
	u32 freq_dअगरf;

	अगर (freq_range->start_freq_khz <= 0 || freq_range->end_freq_khz <= 0)
		वापस false;

	अगर (freq_range->start_freq_khz > freq_range->end_freq_khz)
		वापस false;

	freq_dअगरf = freq_range->end_freq_khz - freq_range->start_freq_khz;

	अगर (freq_range->end_freq_khz <= freq_range->start_freq_khz ||
	    freq_range->max_bandwidth_khz > freq_dअगरf)
		वापस false;

	वापस true;
पूर्ण

अटल bool is_valid_rd(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd)
अणु
	स्थिर काष्ठा ieee80211_reg_rule *reg_rule = शून्य;
	अचिन्हित पूर्णांक i;

	अगर (!rd->n_reg_rules)
		वापस false;

	अगर (WARN_ON(rd->n_reg_rules > NL80211_MAX_SUPP_REG_RULES))
		वापस false;

	क्रम (i = 0; i < rd->n_reg_rules; i++) अणु
		reg_rule = &rd->reg_rules[i];
		अगर (!is_valid_reg_rule(reg_rule))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * freq_in_rule_band - tells us अगर a frequency is in a frequency band
 * @freq_range: frequency rule we want to query
 * @freq_khz: frequency we are inquiring about
 *
 * This lets us know अगर a specअगरic frequency rule is or is not relevant to
 * a specअगरic frequency's band. Bands are device specअगरic and artअगरicial
 * definitions (the "2.4 GHz band", the "5 GHz band" and the "60GHz band"),
 * however it is safe क्रम now to assume that a frequency rule should not be
 * part of a frequency's band अगर the start freq or end freq are off by more
 * than 2 GHz क्रम the 2.4 and 5 GHz bands, and by more than 20 GHz क्रम the
 * 60 GHz band.
 * This resolution can be lowered and should be considered as we add
 * regulatory rule support क्रम other "bands".
 **/
अटल bool freq_in_rule_band(स्थिर काष्ठा ieee80211_freq_range *freq_range,
			      u32 freq_khz)
अणु
#घोषणा ONE_GHZ_IN_KHZ	1000000
	/*
	 * From 802.11ad: directional multi-gigabit (DMG):
	 * Pertaining to operation in a frequency band containing a channel
	 * with the Channel starting frequency above 45 GHz.
	 */
	u32 limit = freq_khz > 45 * ONE_GHZ_IN_KHZ ?
			20 * ONE_GHZ_IN_KHZ : 2 * ONE_GHZ_IN_KHZ;
	अगर (असल(freq_khz - freq_range->start_freq_khz) <= limit)
		वापस true;
	अगर (असल(freq_khz - freq_range->end_freq_khz) <= limit)
		वापस true;
	वापस false;
#अघोषित ONE_GHZ_IN_KHZ
पूर्ण

/*
 * Later on we can perhaps use the more restrictive DFS
 * region but we करोn't have inक्रमmation क्रम that yet so
 * क्रम now simply disallow conflicts.
 */
अटल क्रमागत nl80211_dfs_regions
reg_पूर्णांकersect_dfs_region(स्थिर क्रमागत nl80211_dfs_regions dfs_region1,
			 स्थिर क्रमागत nl80211_dfs_regions dfs_region2)
अणु
	अगर (dfs_region1 != dfs_region2)
		वापस NL80211_DFS_UNSET;
	वापस dfs_region1;
पूर्ण

अटल व्योम reg_wmm_rules_पूर्णांकersect(स्थिर काष्ठा ieee80211_wmm_ac *wmm_ac1,
				    स्थिर काष्ठा ieee80211_wmm_ac *wmm_ac2,
				    काष्ठा ieee80211_wmm_ac *पूर्णांकersect)
अणु
	पूर्णांकersect->cw_min = max_t(u16, wmm_ac1->cw_min, wmm_ac2->cw_min);
	पूर्णांकersect->cw_max = max_t(u16, wmm_ac1->cw_max, wmm_ac2->cw_max);
	पूर्णांकersect->cot = min_t(u16, wmm_ac1->cot, wmm_ac2->cot);
	पूर्णांकersect->aअगरsn = max_t(u8, wmm_ac1->aअगरsn, wmm_ac2->aअगरsn);
पूर्ण

/*
 * Helper क्रम regकरोm_पूर्णांकersect(), this करोes the real
 * mathematical पूर्णांकersection fun
 */
अटल पूर्णांक reg_rules_पूर्णांकersect(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd1,
			       स्थिर काष्ठा ieee80211_regकरोमुख्य *rd2,
			       स्थिर काष्ठा ieee80211_reg_rule *rule1,
			       स्थिर काष्ठा ieee80211_reg_rule *rule2,
			       काष्ठा ieee80211_reg_rule *पूर्णांकersected_rule)
अणु
	स्थिर काष्ठा ieee80211_freq_range *freq_range1, *freq_range2;
	काष्ठा ieee80211_freq_range *freq_range;
	स्थिर काष्ठा ieee80211_घातer_rule *घातer_rule1, *घातer_rule2;
	काष्ठा ieee80211_घातer_rule *घातer_rule;
	स्थिर काष्ठा ieee80211_wmm_rule *wmm_rule1, *wmm_rule2;
	काष्ठा ieee80211_wmm_rule *wmm_rule;
	u32 freq_dअगरf, max_bandwidth1, max_bandwidth2;

	freq_range1 = &rule1->freq_range;
	freq_range2 = &rule2->freq_range;
	freq_range = &पूर्णांकersected_rule->freq_range;

	घातer_rule1 = &rule1->घातer_rule;
	घातer_rule2 = &rule2->घातer_rule;
	घातer_rule = &पूर्णांकersected_rule->घातer_rule;

	wmm_rule1 = &rule1->wmm_rule;
	wmm_rule2 = &rule2->wmm_rule;
	wmm_rule = &पूर्णांकersected_rule->wmm_rule;

	freq_range->start_freq_khz = max(freq_range1->start_freq_khz,
					 freq_range2->start_freq_khz);
	freq_range->end_freq_khz = min(freq_range1->end_freq_khz,
				       freq_range2->end_freq_khz);

	max_bandwidth1 = freq_range1->max_bandwidth_khz;
	max_bandwidth2 = freq_range2->max_bandwidth_khz;

	अगर (rule1->flags & NL80211_RRF_AUTO_BW)
		max_bandwidth1 = reg_get_max_bandwidth(rd1, rule1);
	अगर (rule2->flags & NL80211_RRF_AUTO_BW)
		max_bandwidth2 = reg_get_max_bandwidth(rd2, rule2);

	freq_range->max_bandwidth_khz = min(max_bandwidth1, max_bandwidth2);

	पूर्णांकersected_rule->flags = rule1->flags | rule2->flags;

	/*
	 * In हाल NL80211_RRF_AUTO_BW requested क्रम both rules
	 * set AUTO_BW in पूर्णांकersected rule also. Next we will
	 * calculate BW correctly in handle_channel function.
	 * In other हाल हटाओ AUTO_BW flag जबतक we calculate
	 * maximum bandwidth correctly and स्वतः calculation is
	 * not required.
	 */
	अगर ((rule1->flags & NL80211_RRF_AUTO_BW) &&
	    (rule2->flags & NL80211_RRF_AUTO_BW))
		पूर्णांकersected_rule->flags |= NL80211_RRF_AUTO_BW;
	अन्यथा
		पूर्णांकersected_rule->flags &= ~NL80211_RRF_AUTO_BW;

	freq_dअगरf = freq_range->end_freq_khz - freq_range->start_freq_khz;
	अगर (freq_range->max_bandwidth_khz > freq_dअगरf)
		freq_range->max_bandwidth_khz = freq_dअगरf;

	घातer_rule->max_eirp = min(घातer_rule1->max_eirp,
		घातer_rule2->max_eirp);
	घातer_rule->max_antenna_gain = min(घातer_rule1->max_antenna_gain,
		घातer_rule2->max_antenna_gain);

	पूर्णांकersected_rule->dfs_cac_ms = max(rule1->dfs_cac_ms,
					   rule2->dfs_cac_ms);

	अगर (rule1->has_wmm && rule2->has_wmm) अणु
		u8 ac;

		क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
			reg_wmm_rules_पूर्णांकersect(&wmm_rule1->client[ac],
						&wmm_rule2->client[ac],
						&wmm_rule->client[ac]);
			reg_wmm_rules_पूर्णांकersect(&wmm_rule1->ap[ac],
						&wmm_rule2->ap[ac],
						&wmm_rule->ap[ac]);
		पूर्ण

		पूर्णांकersected_rule->has_wmm = true;
	पूर्ण अन्यथा अगर (rule1->has_wmm) अणु
		*wmm_rule = *wmm_rule1;
		पूर्णांकersected_rule->has_wmm = true;
	पूर्ण अन्यथा अगर (rule2->has_wmm) अणु
		*wmm_rule = *wmm_rule2;
		पूर्णांकersected_rule->has_wmm = true;
	पूर्ण अन्यथा अणु
		पूर्णांकersected_rule->has_wmm = false;
	पूर्ण

	अगर (!is_valid_reg_rule(पूर्णांकersected_rule))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* check whether old rule contains new rule */
अटल bool rule_contains(काष्ठा ieee80211_reg_rule *r1,
			  काष्ठा ieee80211_reg_rule *r2)
अणु
	/* क्रम simplicity, currently consider only same flags */
	अगर (r1->flags != r2->flags)
		वापस false;

	/* verअगरy r1 is more restrictive */
	अगर ((r1->घातer_rule.max_antenna_gain >
	     r2->घातer_rule.max_antenna_gain) ||
	    r1->घातer_rule.max_eirp > r2->घातer_rule.max_eirp)
		वापस false;

	/* make sure r2's range is contained within r1 */
	अगर (r1->freq_range.start_freq_khz > r2->freq_range.start_freq_khz ||
	    r1->freq_range.end_freq_khz < r2->freq_range.end_freq_khz)
		वापस false;

	/* and finally verअगरy that r1.max_bw >= r2.max_bw */
	अगर (r1->freq_range.max_bandwidth_khz <
	    r2->freq_range.max_bandwidth_khz)
		वापस false;

	वापस true;
पूर्ण

/* add or extend current rules. करो nothing अगर rule is alपढ़ोy contained */
अटल व्योम add_rule(काष्ठा ieee80211_reg_rule *rule,
		     काष्ठा ieee80211_reg_rule *reg_rules, u32 *n_rules)
अणु
	काष्ठा ieee80211_reg_rule *पंचांगp_rule;
	पूर्णांक i;

	क्रम (i = 0; i < *n_rules; i++) अणु
		पंचांगp_rule = &reg_rules[i];
		/* rule is alपढ़ोy contained - करो nothing */
		अगर (rule_contains(पंचांगp_rule, rule))
			वापस;

		/* extend rule अगर possible */
		अगर (rule_contains(rule, पंचांगp_rule)) अणु
			स_नकल(पंचांगp_rule, rule, माप(*rule));
			वापस;
		पूर्ण
	पूर्ण

	स_नकल(&reg_rules[*n_rules], rule, माप(*rule));
	(*n_rules)++;
पूर्ण

/**
 * regकरोm_पूर्णांकersect - करो the पूर्णांकersection between two regulatory करोमुख्यs
 * @rd1: first regulatory करोमुख्य
 * @rd2: second regulatory करोमुख्य
 *
 * Use this function to get the पूर्णांकersection between two regulatory करोमुख्यs.
 * Once completed we will mark the alpha2 क्रम the rd as पूर्णांकersected, "98",
 * as no one single alpha2 can represent this regulatory करोमुख्य.
 *
 * Returns a poपूर्णांकer to the regulatory करोमुख्य काष्ठाure which will hold the
 * resulting पूर्णांकersection of rules between rd1 and rd2. We will
 * kzalloc() this काष्ठाure क्रम you.
 */
अटल काष्ठा ieee80211_regकरोमुख्य *
regकरोm_पूर्णांकersect(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd1,
		 स्थिर काष्ठा ieee80211_regकरोमुख्य *rd2)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक x, y;
	अचिन्हित पूर्णांक num_rules = 0;
	स्थिर काष्ठा ieee80211_reg_rule *rule1, *rule2;
	काष्ठा ieee80211_reg_rule पूर्णांकersected_rule;
	काष्ठा ieee80211_regकरोमुख्य *rd;

	अगर (!rd1 || !rd2)
		वापस शून्य;

	/*
	 * First we get a count of the rules we'll need, then we actually
	 * build them. This is to so we can दो_स्मृति() and मुक्त() a
	 * regकरोमुख्य once. The reason we use reg_rules_पूर्णांकersect() here
	 * is it will वापस -EINVAL अगर the rule computed makes no sense.
	 * All rules that करो check out OK are valid.
	 */

	क्रम (x = 0; x < rd1->n_reg_rules; x++) अणु
		rule1 = &rd1->reg_rules[x];
		क्रम (y = 0; y < rd2->n_reg_rules; y++) अणु
			rule2 = &rd2->reg_rules[y];
			अगर (!reg_rules_पूर्णांकersect(rd1, rd2, rule1, rule2,
						 &पूर्णांकersected_rule))
				num_rules++;
		पूर्ण
	पूर्ण

	अगर (!num_rules)
		वापस शून्य;

	rd = kzalloc(काष्ठा_size(rd, reg_rules, num_rules), GFP_KERNEL);
	अगर (!rd)
		वापस शून्य;

	क्रम (x = 0; x < rd1->n_reg_rules; x++) अणु
		rule1 = &rd1->reg_rules[x];
		क्रम (y = 0; y < rd2->n_reg_rules; y++) अणु
			rule2 = &rd2->reg_rules[y];
			r = reg_rules_पूर्णांकersect(rd1, rd2, rule1, rule2,
						&पूर्णांकersected_rule);
			/*
			 * No need to स_रखो here the पूर्णांकersected rule here as
			 * we're not using the stack anymore
			 */
			अगर (r)
				जारी;

			add_rule(&पूर्णांकersected_rule, rd->reg_rules,
				 &rd->n_reg_rules);
		पूर्ण
	पूर्ण

	rd->alpha2[0] = '9';
	rd->alpha2[1] = '8';
	rd->dfs_region = reg_पूर्णांकersect_dfs_region(rd1->dfs_region,
						  rd2->dfs_region);

	वापस rd;
पूर्ण

/*
 * XXX: add support क्रम the rest of क्रमागत nl80211_reg_rule_flags, we may
 * want to just have the channel काष्ठाure use these
 */
अटल u32 map_regकरोm_flags(u32 rd_flags)
अणु
	u32 channel_flags = 0;
	अगर (rd_flags & NL80211_RRF_NO_IR_ALL)
		channel_flags |= IEEE80211_CHAN_NO_IR;
	अगर (rd_flags & NL80211_RRF_DFS)
		channel_flags |= IEEE80211_CHAN_RADAR;
	अगर (rd_flags & NL80211_RRF_NO_OFDM)
		channel_flags |= IEEE80211_CHAN_NO_OFDM;
	अगर (rd_flags & NL80211_RRF_NO_OUTDOOR)
		channel_flags |= IEEE80211_CHAN_INDOOR_ONLY;
	अगर (rd_flags & NL80211_RRF_IR_CONCURRENT)
		channel_flags |= IEEE80211_CHAN_IR_CONCURRENT;
	अगर (rd_flags & NL80211_RRF_NO_HT40MINUS)
		channel_flags |= IEEE80211_CHAN_NO_HT40MINUS;
	अगर (rd_flags & NL80211_RRF_NO_HT40PLUS)
		channel_flags |= IEEE80211_CHAN_NO_HT40PLUS;
	अगर (rd_flags & NL80211_RRF_NO_80MHZ)
		channel_flags |= IEEE80211_CHAN_NO_80MHZ;
	अगर (rd_flags & NL80211_RRF_NO_160MHZ)
		channel_flags |= IEEE80211_CHAN_NO_160MHZ;
	अगर (rd_flags & NL80211_RRF_NO_HE)
		channel_flags |= IEEE80211_CHAN_NO_HE;
	वापस channel_flags;
पूर्ण

अटल स्थिर काष्ठा ieee80211_reg_rule *
freq_reg_info_regd(u32 center_freq,
		   स्थिर काष्ठा ieee80211_regकरोमुख्य *regd, u32 bw)
अणु
	पूर्णांक i;
	bool band_rule_found = false;
	bool bw_fits = false;

	अगर (!regd)
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < regd->n_reg_rules; i++) अणु
		स्थिर काष्ठा ieee80211_reg_rule *rr;
		स्थिर काष्ठा ieee80211_freq_range *fr = शून्य;

		rr = &regd->reg_rules[i];
		fr = &rr->freq_range;

		/*
		 * We only need to know अगर one frequency rule was
		 * in center_freq's band, that's enough, so let's
		 * not overग_लिखो it once found
		 */
		अगर (!band_rule_found)
			band_rule_found = freq_in_rule_band(fr, center_freq);

		bw_fits = cfg80211_करोes_bw_fit_range(fr, center_freq, bw);

		अगर (band_rule_found && bw_fits)
			वापस rr;
	पूर्ण

	अगर (!band_rule_found)
		वापस ERR_PTR(-दुस्फल);

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल स्थिर काष्ठा ieee80211_reg_rule *
__freq_reg_info(काष्ठा wiphy *wiphy, u32 center_freq, u32 min_bw)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd = reg_get_regकरोमुख्य(wiphy);
	अटल स्थिर u32 bws[] = अणु0, 1, 2, 4, 5, 8, 10, 16, 20पूर्ण;
	स्थिर काष्ठा ieee80211_reg_rule *reg_rule = ERR_PTR(-दुस्फल);
	पूर्णांक i = ARRAY_SIZE(bws) - 1;
	u32 bw;

	क्रम (bw = MHZ_TO_KHZ(bws[i]); bw >= min_bw; bw = MHZ_TO_KHZ(bws[i--])) अणु
		reg_rule = freq_reg_info_regd(center_freq, regd, bw);
		अगर (!IS_ERR(reg_rule))
			वापस reg_rule;
	पूर्ण

	वापस reg_rule;
पूर्ण

स्थिर काष्ठा ieee80211_reg_rule *freq_reg_info(काष्ठा wiphy *wiphy,
					       u32 center_freq)
अणु
	u32 min_bw = center_freq < MHZ_TO_KHZ(1000) ? 1 : 20;

	वापस __freq_reg_info(wiphy, center_freq, MHZ_TO_KHZ(min_bw));
पूर्ण
EXPORT_SYMBOL(freq_reg_info);

स्थिर अक्षर *reg_initiator_name(क्रमागत nl80211_reg_initiator initiator)
अणु
	चयन (initiator) अणु
	हाल NL80211_REGDOM_SET_BY_CORE:
		वापस "core";
	हाल NL80211_REGDOM_SET_BY_USER:
		वापस "user";
	हाल NL80211_REGDOM_SET_BY_DRIVER:
		वापस "driver";
	हाल NL80211_REGDOM_SET_BY_COUNTRY_IE:
		वापस "country element";
	शेष:
		WARN_ON(1);
		वापस "bug";
	पूर्ण
पूर्ण
EXPORT_SYMBOL(reg_initiator_name);

अटल uपूर्णांक32_t reg_rule_to_chan_bw_flags(स्थिर काष्ठा ieee80211_regकरोमुख्य *regd,
					  स्थिर काष्ठा ieee80211_reg_rule *reg_rule,
					  स्थिर काष्ठा ieee80211_channel *chan)
अणु
	स्थिर काष्ठा ieee80211_freq_range *freq_range = शून्य;
	u32 max_bandwidth_khz, center_freq_khz, bw_flags = 0;
	bool is_s1g = chan->band == NL80211_BAND_S1GHZ;

	freq_range = &reg_rule->freq_range;

	max_bandwidth_khz = freq_range->max_bandwidth_khz;
	center_freq_khz = ieee80211_channel_to_khz(chan);
	/* Check अगर स्वतः calculation requested */
	अगर (reg_rule->flags & NL80211_RRF_AUTO_BW)
		max_bandwidth_khz = reg_get_max_bandwidth(regd, reg_rule);

	/* If we get a reg_rule we can assume that at least 5Mhz fit */
	अगर (!cfg80211_करोes_bw_fit_range(freq_range,
					center_freq_khz,
					MHZ_TO_KHZ(10)))
		bw_flags |= IEEE80211_CHAN_NO_10MHZ;
	अगर (!cfg80211_करोes_bw_fit_range(freq_range,
					center_freq_khz,
					MHZ_TO_KHZ(20)))
		bw_flags |= IEEE80211_CHAN_NO_20MHZ;

	अगर (is_s1g) अणु
		/* S1G is strict about non overlapping channels. We can
		 * calculate which bandwidth is allowed per channel by finding
		 * the largest bandwidth which cleanly भागides the freq_range.
		 */
		पूर्णांक edge_offset;
		पूर्णांक ch_bw = max_bandwidth_khz;

		जबतक (ch_bw) अणु
			edge_offset = (center_freq_khz - ch_bw / 2) -
				      freq_range->start_freq_khz;
			अगर (edge_offset % ch_bw == 0) अणु
				चयन (KHZ_TO_MHZ(ch_bw)) अणु
				हाल 1:
					bw_flags |= IEEE80211_CHAN_1MHZ;
					अवरोध;
				हाल 2:
					bw_flags |= IEEE80211_CHAN_2MHZ;
					अवरोध;
				हाल 4:
					bw_flags |= IEEE80211_CHAN_4MHZ;
					अवरोध;
				हाल 8:
					bw_flags |= IEEE80211_CHAN_8MHZ;
					अवरोध;
				हाल 16:
					bw_flags |= IEEE80211_CHAN_16MHZ;
					अवरोध;
				शेष:
					/* If we got here, no bandwidths fit on
					 * this frequency, ie. band edge.
					 */
					bw_flags |= IEEE80211_CHAN_DISABLED;
					अवरोध;
				पूर्ण
				अवरोध;
			पूर्ण
			ch_bw /= 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (max_bandwidth_khz < MHZ_TO_KHZ(10))
			bw_flags |= IEEE80211_CHAN_NO_10MHZ;
		अगर (max_bandwidth_khz < MHZ_TO_KHZ(20))
			bw_flags |= IEEE80211_CHAN_NO_20MHZ;
		अगर (max_bandwidth_khz < MHZ_TO_KHZ(40))
			bw_flags |= IEEE80211_CHAN_NO_HT40;
		अगर (max_bandwidth_khz < MHZ_TO_KHZ(80))
			bw_flags |= IEEE80211_CHAN_NO_80MHZ;
		अगर (max_bandwidth_khz < MHZ_TO_KHZ(160))
			bw_flags |= IEEE80211_CHAN_NO_160MHZ;
	पूर्ण
	वापस bw_flags;
पूर्ण

अटल व्योम handle_channel_single_rule(काष्ठा wiphy *wiphy,
				       क्रमागत nl80211_reg_initiator initiator,
				       काष्ठा ieee80211_channel *chan,
				       u32 flags,
				       काष्ठा regulatory_request *lr,
				       काष्ठा wiphy *request_wiphy,
				       स्थिर काष्ठा ieee80211_reg_rule *reg_rule)
अणु
	u32 bw_flags = 0;
	स्थिर काष्ठा ieee80211_घातer_rule *घातer_rule = शून्य;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd;

	regd = reg_get_regकरोमुख्य(wiphy);

	घातer_rule = &reg_rule->घातer_rule;
	bw_flags = reg_rule_to_chan_bw_flags(regd, reg_rule, chan);

	अगर (lr->initiator == NL80211_REGDOM_SET_BY_DRIVER &&
	    request_wiphy && request_wiphy == wiphy &&
	    request_wiphy->regulatory_flags & REGULATORY_STRICT_REG) अणु
		/*
		 * This guarantees the driver's requested regulatory करोमुख्य
		 * will always be used as a base क्रम further regulatory
		 * settings
		 */
		chan->flags = chan->orig_flags =
			map_regकरोm_flags(reg_rule->flags) | bw_flags;
		chan->max_antenna_gain = chan->orig_mag =
			(पूर्णांक) MBI_TO_DBI(घातer_rule->max_antenna_gain);
		chan->max_reg_घातer = chan->max_घातer = chan->orig_mpwr =
			(पूर्णांक) MBM_TO_DBM(घातer_rule->max_eirp);

		अगर (chan->flags & IEEE80211_CHAN_RADAR) अणु
			chan->dfs_cac_ms = IEEE80211_DFS_MIN_CAC_TIME_MS;
			अगर (reg_rule->dfs_cac_ms)
				chan->dfs_cac_ms = reg_rule->dfs_cac_ms;
		पूर्ण

		वापस;
	पूर्ण

	chan->dfs_state = NL80211_DFS_USABLE;
	chan->dfs_state_entered = jअगरfies;

	chan->beacon_found = false;
	chan->flags = flags | bw_flags | map_regकरोm_flags(reg_rule->flags);
	chan->max_antenna_gain =
		min_t(पूर्णांक, chan->orig_mag,
		      MBI_TO_DBI(घातer_rule->max_antenna_gain));
	chan->max_reg_घातer = (पूर्णांक) MBM_TO_DBM(घातer_rule->max_eirp);

	अगर (chan->flags & IEEE80211_CHAN_RADAR) अणु
		अगर (reg_rule->dfs_cac_ms)
			chan->dfs_cac_ms = reg_rule->dfs_cac_ms;
		अन्यथा
			chan->dfs_cac_ms = IEEE80211_DFS_MIN_CAC_TIME_MS;
	पूर्ण

	अगर (chan->orig_mpwr) अणु
		/*
		 * Devices that use REGULATORY_COUNTRY_IE_FOLLOW_POWER
		 * will always follow the passed country IE घातer settings.
		 */
		अगर (initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE &&
		    wiphy->regulatory_flags & REGULATORY_COUNTRY_IE_FOLLOW_POWER)
			chan->max_घातer = chan->max_reg_घातer;
		अन्यथा
			chan->max_घातer = min(chan->orig_mpwr,
					      chan->max_reg_घातer);
	पूर्ण अन्यथा
		chan->max_घातer = chan->max_reg_घातer;
पूर्ण

अटल व्योम handle_channel_adjacent_rules(काष्ठा wiphy *wiphy,
					  क्रमागत nl80211_reg_initiator initiator,
					  काष्ठा ieee80211_channel *chan,
					  u32 flags,
					  काष्ठा regulatory_request *lr,
					  काष्ठा wiphy *request_wiphy,
					  स्थिर काष्ठा ieee80211_reg_rule *rrule1,
					  स्थिर काष्ठा ieee80211_reg_rule *rrule2,
					  काष्ठा ieee80211_freq_range *comb_range)
अणु
	u32 bw_flags1 = 0;
	u32 bw_flags2 = 0;
	स्थिर काष्ठा ieee80211_घातer_rule *घातer_rule1 = शून्य;
	स्थिर काष्ठा ieee80211_घातer_rule *घातer_rule2 = शून्य;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd;

	regd = reg_get_regकरोमुख्य(wiphy);

	घातer_rule1 = &rrule1->घातer_rule;
	घातer_rule2 = &rrule2->घातer_rule;
	bw_flags1 = reg_rule_to_chan_bw_flags(regd, rrule1, chan);
	bw_flags2 = reg_rule_to_chan_bw_flags(regd, rrule2, chan);

	अगर (lr->initiator == NL80211_REGDOM_SET_BY_DRIVER &&
	    request_wiphy && request_wiphy == wiphy &&
	    request_wiphy->regulatory_flags & REGULATORY_STRICT_REG) अणु
		/* This guarantees the driver's requested regulatory करोमुख्य
		 * will always be used as a base क्रम further regulatory
		 * settings
		 */
		chan->flags =
			map_regकरोm_flags(rrule1->flags) |
			map_regकरोm_flags(rrule2->flags) |
			bw_flags1 |
			bw_flags2;
		chan->orig_flags = chan->flags;
		chan->max_antenna_gain =
			min_t(पूर्णांक, MBI_TO_DBI(घातer_rule1->max_antenna_gain),
			      MBI_TO_DBI(घातer_rule2->max_antenna_gain));
		chan->orig_mag = chan->max_antenna_gain;
		chan->max_reg_घातer =
			min_t(पूर्णांक, MBM_TO_DBM(घातer_rule1->max_eirp),
			      MBM_TO_DBM(घातer_rule2->max_eirp));
		chan->max_घातer = chan->max_reg_घातer;
		chan->orig_mpwr = chan->max_reg_घातer;

		अगर (chan->flags & IEEE80211_CHAN_RADAR) अणु
			chan->dfs_cac_ms = IEEE80211_DFS_MIN_CAC_TIME_MS;
			अगर (rrule1->dfs_cac_ms || rrule2->dfs_cac_ms)
				chan->dfs_cac_ms = max_t(अचिन्हित पूर्णांक,
							 rrule1->dfs_cac_ms,
							 rrule2->dfs_cac_ms);
		पूर्ण

		वापस;
	पूर्ण

	chan->dfs_state = NL80211_DFS_USABLE;
	chan->dfs_state_entered = jअगरfies;

	chan->beacon_found = false;
	chan->flags = flags | bw_flags1 | bw_flags2 |
		      map_regकरोm_flags(rrule1->flags) |
		      map_regकरोm_flags(rrule2->flags);

	/* reg_rule_to_chan_bw_flags may क्रमbids 10 and क्रमbids 20 MHz
	 * (otherwise no adj. rule हाल), recheck thereक्रमe
	 */
	अगर (cfg80211_करोes_bw_fit_range(comb_range,
				       ieee80211_channel_to_khz(chan),
				       MHZ_TO_KHZ(10)))
		chan->flags &= ~IEEE80211_CHAN_NO_10MHZ;
	अगर (cfg80211_करोes_bw_fit_range(comb_range,
				       ieee80211_channel_to_khz(chan),
				       MHZ_TO_KHZ(20)))
		chan->flags &= ~IEEE80211_CHAN_NO_20MHZ;

	chan->max_antenna_gain =
		min_t(पूर्णांक, chan->orig_mag,
		      min_t(पूर्णांक,
			    MBI_TO_DBI(घातer_rule1->max_antenna_gain),
			    MBI_TO_DBI(घातer_rule2->max_antenna_gain)));
	chan->max_reg_घातer = min_t(पूर्णांक,
				    MBM_TO_DBM(घातer_rule1->max_eirp),
				    MBM_TO_DBM(घातer_rule2->max_eirp));

	अगर (chan->flags & IEEE80211_CHAN_RADAR) अणु
		अगर (rrule1->dfs_cac_ms || rrule2->dfs_cac_ms)
			chan->dfs_cac_ms = max_t(अचिन्हित पूर्णांक,
						 rrule1->dfs_cac_ms,
						 rrule2->dfs_cac_ms);
		अन्यथा
			chan->dfs_cac_ms = IEEE80211_DFS_MIN_CAC_TIME_MS;
	पूर्ण

	अगर (chan->orig_mpwr) अणु
		/* Devices that use REGULATORY_COUNTRY_IE_FOLLOW_POWER
		 * will always follow the passed country IE घातer settings.
		 */
		अगर (initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE &&
		    wiphy->regulatory_flags & REGULATORY_COUNTRY_IE_FOLLOW_POWER)
			chan->max_घातer = chan->max_reg_घातer;
		अन्यथा
			chan->max_घातer = min(chan->orig_mpwr,
					      chan->max_reg_घातer);
	पूर्ण अन्यथा अणु
		chan->max_घातer = chan->max_reg_घातer;
	पूर्ण
पूर्ण

/* Note that right now we assume the desired channel bandwidth
 * is always 20 MHz क्रम each inभागidual channel (HT40 uses 20 MHz
 * per channel, the primary and the extension channel).
 */
अटल व्योम handle_channel(काष्ठा wiphy *wiphy,
			   क्रमागत nl80211_reg_initiator initiator,
			   काष्ठा ieee80211_channel *chan)
अणु
	स्थिर u32 orig_chan_freq = ieee80211_channel_to_khz(chan);
	काष्ठा regulatory_request *lr = get_last_request();
	काष्ठा wiphy *request_wiphy = wiphy_idx_to_wiphy(lr->wiphy_idx);
	स्थिर काष्ठा ieee80211_reg_rule *rrule = शून्य;
	स्थिर काष्ठा ieee80211_reg_rule *rrule1 = शून्य;
	स्थिर काष्ठा ieee80211_reg_rule *rrule2 = शून्य;

	u32 flags = chan->orig_flags;

	rrule = freq_reg_info(wiphy, orig_chan_freq);
	अगर (IS_ERR(rrule)) अणु
		/* check क्रम adjacent match, thereक्रमe get rules क्रम
		 * chan - 20 MHz and chan + 20 MHz and test
		 * अगर reg rules are adjacent
		 */
		rrule1 = freq_reg_info(wiphy,
				       orig_chan_freq - MHZ_TO_KHZ(20));
		rrule2 = freq_reg_info(wiphy,
				       orig_chan_freq + MHZ_TO_KHZ(20));
		अगर (!IS_ERR(rrule1) && !IS_ERR(rrule2)) अणु
			काष्ठा ieee80211_freq_range comb_range;

			अगर (rrule1->freq_range.end_freq_khz !=
			    rrule2->freq_range.start_freq_khz)
				जाओ disable_chan;

			comb_range.start_freq_khz =
				rrule1->freq_range.start_freq_khz;
			comb_range.end_freq_khz =
				rrule2->freq_range.end_freq_khz;
			comb_range.max_bandwidth_khz =
				min_t(u32,
				      rrule1->freq_range.max_bandwidth_khz,
				      rrule2->freq_range.max_bandwidth_khz);

			अगर (!cfg80211_करोes_bw_fit_range(&comb_range,
							orig_chan_freq,
							MHZ_TO_KHZ(20)))
				जाओ disable_chan;

			handle_channel_adjacent_rules(wiphy, initiator, chan,
						      flags, lr, request_wiphy,
						      rrule1, rrule2,
						      &comb_range);
			वापस;
		पूर्ण

disable_chan:
		/* We will disable all channels that करो not match our
		 * received regulatory rule unless the hपूर्णांक is coming
		 * from a Country IE and the Country IE had no inक्रमmation
		 * about a band. The IEEE 802.11 spec allows क्रम an AP
		 * to send only a subset of the regulatory rules allowed,
		 * so an AP in the US that only supports 2.4 GHz may only send
		 * a country IE with inक्रमmation क्रम the 2.4 GHz band
		 * जबतक 5 GHz is still supported.
		 */
		अगर (initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE &&
		    PTR_ERR(rrule) == -दुस्फल)
			वापस;

		अगर (lr->initiator == NL80211_REGDOM_SET_BY_DRIVER &&
		    request_wiphy && request_wiphy == wiphy &&
		    request_wiphy->regulatory_flags & REGULATORY_STRICT_REG) अणु
			pr_debug("Disabling freq %d.%03d MHz for good\n",
				 chan->center_freq, chan->freq_offset);
			chan->orig_flags |= IEEE80211_CHAN_DISABLED;
			chan->flags = chan->orig_flags;
		पूर्ण अन्यथा अणु
			pr_debug("Disabling freq %d.%03d MHz\n",
				 chan->center_freq, chan->freq_offset);
			chan->flags |= IEEE80211_CHAN_DISABLED;
		पूर्ण
		वापस;
	पूर्ण

	handle_channel_single_rule(wiphy, initiator, chan, flags, lr,
				   request_wiphy, rrule);
पूर्ण

अटल व्योम handle_band(काष्ठा wiphy *wiphy,
			क्रमागत nl80211_reg_initiator initiator,
			काष्ठा ieee80211_supported_band *sband)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!sband)
		वापस;

	क्रम (i = 0; i < sband->n_channels; i++)
		handle_channel(wiphy, initiator, &sband->channels[i]);
पूर्ण

अटल bool reg_request_cell_base(काष्ठा regulatory_request *request)
अणु
	अगर (request->initiator != NL80211_REGDOM_SET_BY_USER)
		वापस false;
	वापस request->user_reg_hपूर्णांक_type == NL80211_USER_REG_HINT_CELL_BASE;
पूर्ण

bool reg_last_request_cell_base(व्योम)
अणु
	वापस reg_request_cell_base(get_last_request());
पूर्ण

#अगर_घोषित CONFIG_CFG80211_REG_CELLULAR_HINTS
/* Core specअगरic check */
अटल क्रमागत reg_request_treaपंचांगent
reg_ignore_cell_hपूर्णांक(काष्ठा regulatory_request *pending_request)
अणु
	काष्ठा regulatory_request *lr = get_last_request();

	अगर (!reg_num_devs_support_basehपूर्णांक)
		वापस REG_REQ_IGNORE;

	अगर (reg_request_cell_base(lr) &&
	    !regकरोm_changes(pending_request->alpha2))
		वापस REG_REQ_ALREADY_SET;

	वापस REG_REQ_OK;
पूर्ण

/* Device specअगरic check */
अटल bool reg_dev_ignore_cell_hपूर्णांक(काष्ठा wiphy *wiphy)
अणु
	वापस !(wiphy->features & NL80211_FEATURE_CELL_BASE_REG_HINTS);
पूर्ण
#अन्यथा
अटल क्रमागत reg_request_treaपंचांगent
reg_ignore_cell_hपूर्णांक(काष्ठा regulatory_request *pending_request)
अणु
	वापस REG_REQ_IGNORE;
पूर्ण

अटल bool reg_dev_ignore_cell_hपूर्णांक(काष्ठा wiphy *wiphy)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल bool wiphy_strict_alpha2_regd(काष्ठा wiphy *wiphy)
अणु
	अगर (wiphy->regulatory_flags & REGULATORY_STRICT_REG &&
	    !(wiphy->regulatory_flags & REGULATORY_CUSTOM_REG))
		वापस true;
	वापस false;
पूर्ण

अटल bool ignore_reg_update(काष्ठा wiphy *wiphy,
			      क्रमागत nl80211_reg_initiator initiator)
अणु
	काष्ठा regulatory_request *lr = get_last_request();

	अगर (wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED)
		वापस true;

	अगर (!lr) अणु
		pr_debug("Ignoring regulatory request set by %s since last_request is not set\n",
			 reg_initiator_name(initiator));
		वापस true;
	पूर्ण

	अगर (initiator == NL80211_REGDOM_SET_BY_CORE &&
	    wiphy->regulatory_flags & REGULATORY_CUSTOM_REG) अणु
		pr_debug("Ignoring regulatory request set by %s since the driver uses its own custom regulatory domain\n",
			 reg_initiator_name(initiator));
		वापस true;
	पूर्ण

	/*
	 * wiphy->regd will be set once the device has its own
	 * desired regulatory करोमुख्य set
	 */
	अगर (wiphy_strict_alpha2_regd(wiphy) && !wiphy->regd &&
	    initiator != NL80211_REGDOM_SET_BY_COUNTRY_IE &&
	    !is_world_regकरोm(lr->alpha2)) अणु
		pr_debug("Ignoring regulatory request set by %s since the driver requires its own regulatory domain to be set first\n",
			 reg_initiator_name(initiator));
		वापस true;
	पूर्ण

	अगर (reg_request_cell_base(lr))
		वापस reg_dev_ignore_cell_hपूर्णांक(wiphy);

	वापस false;
पूर्ण

अटल bool reg_is_world_roaming(काष्ठा wiphy *wiphy)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *cr = get_cfg80211_regकरोm();
	स्थिर काष्ठा ieee80211_regकरोमुख्य *wr = get_wiphy_regकरोm(wiphy);
	काष्ठा regulatory_request *lr = get_last_request();

	अगर (is_world_regकरोm(cr->alpha2) || (wr && is_world_regकरोm(wr->alpha2)))
		वापस true;

	अगर (lr && lr->initiator != NL80211_REGDOM_SET_BY_COUNTRY_IE &&
	    wiphy->regulatory_flags & REGULATORY_CUSTOM_REG)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम handle_reg_beacon(काष्ठा wiphy *wiphy, अचिन्हित पूर्णांक chan_idx,
			      काष्ठा reg_beacon *reg_beacon)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *chan;
	bool channel_changed = false;
	काष्ठा ieee80211_channel chan_beक्रमe;

	sband = wiphy->bands[reg_beacon->chan.band];
	chan = &sband->channels[chan_idx];

	अगर (likely(!ieee80211_channel_equal(chan, &reg_beacon->chan)))
		वापस;

	अगर (chan->beacon_found)
		वापस;

	chan->beacon_found = true;

	अगर (!reg_is_world_roaming(wiphy))
		वापस;

	अगर (wiphy->regulatory_flags & REGULATORY_DISABLE_BEACON_HINTS)
		वापस;

	chan_beक्रमe = *chan;

	अगर (chan->flags & IEEE80211_CHAN_NO_IR) अणु
		chan->flags &= ~IEEE80211_CHAN_NO_IR;
		channel_changed = true;
	पूर्ण

	अगर (channel_changed)
		nl80211_send_beacon_hपूर्णांक_event(wiphy, &chan_beक्रमe, chan);
पूर्ण

/*
 * Called when a scan on a wiphy finds a beacon on
 * new channel
 */
अटल व्योम wiphy_update_new_beacon(काष्ठा wiphy *wiphy,
				    काष्ठा reg_beacon *reg_beacon)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ieee80211_supported_band *sband;

	अगर (!wiphy->bands[reg_beacon->chan.band])
		वापस;

	sband = wiphy->bands[reg_beacon->chan.band];

	क्रम (i = 0; i < sband->n_channels; i++)
		handle_reg_beacon(wiphy, i, reg_beacon);
पूर्ण

/*
 * Called upon reg changes or a new wiphy is added
 */
अटल व्योम wiphy_update_beacon_reg(काष्ठा wiphy *wiphy)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा reg_beacon *reg_beacon;

	list_क्रम_each_entry(reg_beacon, &reg_beacon_list, list) अणु
		अगर (!wiphy->bands[reg_beacon->chan.band])
			जारी;
		sband = wiphy->bands[reg_beacon->chan.band];
		क्रम (i = 0; i < sband->n_channels; i++)
			handle_reg_beacon(wiphy, i, reg_beacon);
	पूर्ण
पूर्ण

/* Reap the advantages of previously found beacons */
अटल व्योम reg_process_beacons(काष्ठा wiphy *wiphy)
अणु
	/*
	 * Means we are just firing up cfg80211, so no beacons would
	 * have been processed yet.
	 */
	अगर (!last_request)
		वापस;
	wiphy_update_beacon_reg(wiphy);
पूर्ण

अटल bool is_ht40_allowed(काष्ठा ieee80211_channel *chan)
अणु
	अगर (!chan)
		वापस false;
	अगर (chan->flags & IEEE80211_CHAN_DISABLED)
		वापस false;
	/* This would happen when regulatory rules disallow HT40 completely */
	अगर ((chan->flags & IEEE80211_CHAN_NO_HT40) == IEEE80211_CHAN_NO_HT40)
		वापस false;
	वापस true;
पूर्ण

अटल व्योम reg_process_ht_flags_channel(काष्ठा wiphy *wiphy,
					 काष्ठा ieee80211_channel *channel)
अणु
	काष्ठा ieee80211_supported_band *sband = wiphy->bands[channel->band];
	काष्ठा ieee80211_channel *channel_beक्रमe = शून्य, *channel_after = शून्य;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd;
	अचिन्हित पूर्णांक i;
	u32 flags;

	अगर (!is_ht40_allowed(channel)) अणु
		channel->flags |= IEEE80211_CHAN_NO_HT40;
		वापस;
	पूर्ण

	/*
	 * We need to ensure the extension channels exist to
	 * be able to use HT40- or HT40+, this finds them (or not)
	 */
	क्रम (i = 0; i < sband->n_channels; i++) अणु
		काष्ठा ieee80211_channel *c = &sband->channels[i];

		अगर (c->center_freq == (channel->center_freq - 20))
			channel_beक्रमe = c;
		अगर (c->center_freq == (channel->center_freq + 20))
			channel_after = c;
	पूर्ण

	flags = 0;
	regd = get_wiphy_regकरोm(wiphy);
	अगर (regd) अणु
		स्थिर काष्ठा ieee80211_reg_rule *reg_rule =
			freq_reg_info_regd(MHZ_TO_KHZ(channel->center_freq),
					   regd, MHZ_TO_KHZ(20));

		अगर (!IS_ERR(reg_rule))
			flags = reg_rule->flags;
	पूर्ण

	/*
	 * Please note that this assumes target bandwidth is 20 MHz,
	 * अगर that ever changes we also need to change the below logic
	 * to include that as well.
	 */
	अगर (!is_ht40_allowed(channel_beक्रमe) ||
	    flags & NL80211_RRF_NO_HT40MINUS)
		channel->flags |= IEEE80211_CHAN_NO_HT40MINUS;
	अन्यथा
		channel->flags &= ~IEEE80211_CHAN_NO_HT40MINUS;

	अगर (!is_ht40_allowed(channel_after) ||
	    flags & NL80211_RRF_NO_HT40PLUS)
		channel->flags |= IEEE80211_CHAN_NO_HT40PLUS;
	अन्यथा
		channel->flags &= ~IEEE80211_CHAN_NO_HT40PLUS;
पूर्ण

अटल व्योम reg_process_ht_flags_band(काष्ठा wiphy *wiphy,
				      काष्ठा ieee80211_supported_band *sband)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!sband)
		वापस;

	क्रम (i = 0; i < sband->n_channels; i++)
		reg_process_ht_flags_channel(wiphy, &sband->channels[i]);
पूर्ण

अटल व्योम reg_process_ht_flags(काष्ठा wiphy *wiphy)
अणु
	क्रमागत nl80211_band band;

	अगर (!wiphy)
		वापस;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++)
		reg_process_ht_flags_band(wiphy, wiphy->bands[band]);
पूर्ण

अटल व्योम reg_call_notअगरier(काष्ठा wiphy *wiphy,
			      काष्ठा regulatory_request *request)
अणु
	अगर (wiphy->reg_notअगरier)
		wiphy->reg_notअगरier(wiphy, request);
पूर्ण

अटल bool reg_wdev_chan_valid(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_chan_def chandef = अणुपूर्ण;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	क्रमागत nl80211_अगरtype अगरtype;

	wdev_lock(wdev);
	अगरtype = wdev->अगरtype;

	/* make sure the पूर्णांकerface is active */
	अगर (!wdev->netdev || !netअगर_running(wdev->netdev))
		जाओ wdev_inactive_unlock;

	चयन (अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
		अगर (!wdev->beacon_पूर्णांकerval)
			जाओ wdev_inactive_unlock;
		chandef = wdev->chandef;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		अगर (!wdev->ssid_len)
			जाओ wdev_inactive_unlock;
		chandef = wdev->chandef;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		अगर (!wdev->current_bss ||
		    !wdev->current_bss->pub.channel)
			जाओ wdev_inactive_unlock;

		अगर (!rdev->ops->get_channel ||
		    rdev_get_channel(rdev, wdev, &chandef))
			cfg80211_chandef_create(&chandef,
						wdev->current_bss->pub.channel,
						NL80211_CHAN_NO_HT);
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_P2P_DEVICE:
		/* no enक्रमcement required */
		अवरोध;
	शेष:
		/* others not implemented क्रम now */
		WARN_ON(1);
		अवरोध;
	पूर्ण

	wdev_unlock(wdev);

	चयन (अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_ADHOC:
		वापस cfg80211_reg_can_beacon_relax(wiphy, &chandef, अगरtype);
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		वापस cfg80211_chandef_usable(wiphy, &chandef,
					       IEEE80211_CHAN_DISABLED);
	शेष:
		अवरोध;
	पूर्ण

	वापस true;

wdev_inactive_unlock:
	wdev_unlock(wdev);
	वापस true;
पूर्ण

अटल व्योम reg_leave_invalid_chans(काष्ठा wiphy *wiphy)
अणु
	काष्ठा wireless_dev *wdev;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	ASSERT_RTNL();

	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list)
		अगर (!reg_wdev_chan_valid(wiphy, wdev))
			cfg80211_leave(rdev, wdev);
पूर्ण

अटल व्योम reg_check_chans_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	pr_debug("Verifying active interfaces after reg change\n");
	rtnl_lock();

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list)
		अगर (!(rdev->wiphy.regulatory_flags &
		      REGULATORY_IGNORE_STALE_KICKOFF))
			reg_leave_invalid_chans(&rdev->wiphy);

	rtnl_unlock();
पूर्ण

अटल व्योम reg_check_channels(व्योम)
अणु
	/*
	 * Give usermode a chance to करो something nicer (move to another
	 * channel, orderly disconnection), beक्रमe क्रमcing a disconnection.
	 */
	mod_delayed_work(प्रणाली_घातer_efficient_wq,
			 &reg_check_chans,
			 msecs_to_jअगरfies(REG_ENFORCE_GRACE_MS));
पूर्ण

अटल व्योम wiphy_update_regulatory(काष्ठा wiphy *wiphy,
				    क्रमागत nl80211_reg_initiator initiator)
अणु
	क्रमागत nl80211_band band;
	काष्ठा regulatory_request *lr = get_last_request();

	अगर (ignore_reg_update(wiphy, initiator)) अणु
		/*
		 * Regulatory updates set by CORE are ignored क्रम custom
		 * regulatory cards. Let us notअगरy the changes to the driver,
		 * as some drivers used this to restore its orig_* reg करोमुख्य.
		 */
		अगर (initiator == NL80211_REGDOM_SET_BY_CORE &&
		    wiphy->regulatory_flags & REGULATORY_CUSTOM_REG &&
		    !(wiphy->regulatory_flags &
		      REGULATORY_WIPHY_SELF_MANAGED))
			reg_call_notअगरier(wiphy, lr);
		वापस;
	पूर्ण

	lr->dfs_region = get_cfg80211_regकरोm()->dfs_region;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++)
		handle_band(wiphy, initiator, wiphy->bands[band]);

	reg_process_beacons(wiphy);
	reg_process_ht_flags(wiphy);
	reg_call_notअगरier(wiphy, lr);
पूर्ण

अटल व्योम update_all_wiphy_regulatory(क्रमागत nl80211_reg_initiator initiator)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wiphy *wiphy;

	ASSERT_RTNL();

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		wiphy = &rdev->wiphy;
		wiphy_update_regulatory(wiphy, initiator);
	पूर्ण

	reg_check_channels();
पूर्ण

अटल व्योम handle_channel_custom(काष्ठा wiphy *wiphy,
				  काष्ठा ieee80211_channel *chan,
				  स्थिर काष्ठा ieee80211_regकरोमुख्य *regd,
				  u32 min_bw)
अणु
	u32 bw_flags = 0;
	स्थिर काष्ठा ieee80211_reg_rule *reg_rule = शून्य;
	स्थिर काष्ठा ieee80211_घातer_rule *घातer_rule = शून्य;
	u32 bw, center_freq_khz;

	center_freq_khz = ieee80211_channel_to_khz(chan);
	क्रम (bw = MHZ_TO_KHZ(20); bw >= min_bw; bw = bw / 2) अणु
		reg_rule = freq_reg_info_regd(center_freq_khz, regd, bw);
		अगर (!IS_ERR(reg_rule))
			अवरोध;
	पूर्ण

	अगर (IS_ERR_OR_शून्य(reg_rule)) अणु
		pr_debug("Disabling freq %d.%03d MHz as custom regd has no rule that fits it\n",
			 chan->center_freq, chan->freq_offset);
		अगर (wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED) अणु
			chan->flags |= IEEE80211_CHAN_DISABLED;
		पूर्ण अन्यथा अणु
			chan->orig_flags |= IEEE80211_CHAN_DISABLED;
			chan->flags = chan->orig_flags;
		पूर्ण
		वापस;
	पूर्ण

	घातer_rule = &reg_rule->घातer_rule;
	bw_flags = reg_rule_to_chan_bw_flags(regd, reg_rule, chan);

	chan->dfs_state_entered = jअगरfies;
	chan->dfs_state = NL80211_DFS_USABLE;

	chan->beacon_found = false;

	अगर (wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED)
		chan->flags = chan->orig_flags | bw_flags |
			      map_regकरोm_flags(reg_rule->flags);
	अन्यथा
		chan->flags |= map_regकरोm_flags(reg_rule->flags) | bw_flags;

	chan->max_antenna_gain = (पूर्णांक) MBI_TO_DBI(घातer_rule->max_antenna_gain);
	chan->max_reg_घातer = chan->max_घातer =
		(पूर्णांक) MBM_TO_DBM(घातer_rule->max_eirp);

	अगर (chan->flags & IEEE80211_CHAN_RADAR) अणु
		अगर (reg_rule->dfs_cac_ms)
			chan->dfs_cac_ms = reg_rule->dfs_cac_ms;
		अन्यथा
			chan->dfs_cac_ms = IEEE80211_DFS_MIN_CAC_TIME_MS;
	पूर्ण

	chan->max_घातer = chan->max_reg_घातer;
पूर्ण

अटल व्योम handle_band_custom(काष्ठा wiphy *wiphy,
			       काष्ठा ieee80211_supported_band *sband,
			       स्थिर काष्ठा ieee80211_regकरोमुख्य *regd)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!sband)
		वापस;

	/*
	 * We currently assume that you always want at least 20 MHz,
	 * otherwise channel 12 might get enabled अगर this rule is
	 * compatible to US, which permits 2402 - 2472 MHz.
	 */
	क्रम (i = 0; i < sband->n_channels; i++)
		handle_channel_custom(wiphy, &sband->channels[i], regd,
				      MHZ_TO_KHZ(20));
पूर्ण

/* Used by drivers prior to wiphy registration */
व्योम wiphy_apply_custom_regulatory(काष्ठा wiphy *wiphy,
				   स्थिर काष्ठा ieee80211_regकरोमुख्य *regd)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *new_regd, *पंचांगp;
	क्रमागत nl80211_band band;
	अचिन्हित पूर्णांक bands_set = 0;

	WARN(!(wiphy->regulatory_flags & REGULATORY_CUSTOM_REG),
	     "wiphy should have REGULATORY_CUSTOM_REG\n");
	wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		अगर (!wiphy->bands[band])
			जारी;
		handle_band_custom(wiphy, wiphy->bands[band], regd);
		bands_set++;
	पूर्ण

	/*
	 * no poपूर्णांक in calling this अगर it won't have any effect
	 * on your device's supported bands.
	 */
	WARN_ON(!bands_set);
	new_regd = reg_copy_regd(regd);
	अगर (IS_ERR(new_regd))
		वापस;

	rtnl_lock();
	wiphy_lock(wiphy);

	पंचांगp = get_wiphy_regकरोm(wiphy);
	rcu_assign_poपूर्णांकer(wiphy->regd, new_regd);
	rcu_मुक्त_regकरोm(पंचांगp);

	wiphy_unlock(wiphy);
	rtnl_unlock();
पूर्ण
EXPORT_SYMBOL(wiphy_apply_custom_regulatory);

अटल व्योम reg_set_request_processed(व्योम)
अणु
	bool need_more_processing = false;
	काष्ठा regulatory_request *lr = get_last_request();

	lr->processed = true;

	spin_lock(&reg_requests_lock);
	अगर (!list_empty(&reg_requests_list))
		need_more_processing = true;
	spin_unlock(&reg_requests_lock);

	cancel_crda_समयout();

	अगर (need_more_processing)
		schedule_work(&reg_work);
पूर्ण

/**
 * reg_process_hपूर्णांक_core - process core regulatory requests
 * @core_request: a pending core regulatory request
 *
 * The wireless subप्रणाली can use this function to process
 * a regulatory request issued by the regulatory core.
 */
अटल क्रमागत reg_request_treaपंचांगent
reg_process_hपूर्णांक_core(काष्ठा regulatory_request *core_request)
अणु
	अगर (reg_query_database(core_request)) अणु
		core_request->पूर्णांकersect = false;
		core_request->processed = false;
		reg_update_last_request(core_request);
		वापस REG_REQ_OK;
	पूर्ण

	वापस REG_REQ_IGNORE;
पूर्ण

अटल क्रमागत reg_request_treaपंचांगent
__reg_process_hपूर्णांक_user(काष्ठा regulatory_request *user_request)
अणु
	काष्ठा regulatory_request *lr = get_last_request();

	अगर (reg_request_cell_base(user_request))
		वापस reg_ignore_cell_hपूर्णांक(user_request);

	अगर (reg_request_cell_base(lr))
		वापस REG_REQ_IGNORE;

	अगर (lr->initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE)
		वापस REG_REQ_INTERSECT;
	/*
	 * If the user knows better the user should set the regकरोm
	 * to their country beक्रमe the IE is picked up
	 */
	अगर (lr->initiator == NL80211_REGDOM_SET_BY_USER &&
	    lr->पूर्णांकersect)
		वापस REG_REQ_IGNORE;
	/*
	 * Process user requests only after previous user/driver/core
	 * requests have been processed
	 */
	अगर ((lr->initiator == NL80211_REGDOM_SET_BY_CORE ||
	     lr->initiator == NL80211_REGDOM_SET_BY_DRIVER ||
	     lr->initiator == NL80211_REGDOM_SET_BY_USER) &&
	    regकरोm_changes(lr->alpha2))
		वापस REG_REQ_IGNORE;

	अगर (!regकरोm_changes(user_request->alpha2))
		वापस REG_REQ_ALREADY_SET;

	वापस REG_REQ_OK;
पूर्ण

/**
 * reg_process_hपूर्णांक_user - process user regulatory requests
 * @user_request: a pending user regulatory request
 *
 * The wireless subप्रणाली can use this function to process
 * a regulatory request initiated by userspace.
 */
अटल क्रमागत reg_request_treaपंचांगent
reg_process_hपूर्णांक_user(काष्ठा regulatory_request *user_request)
अणु
	क्रमागत reg_request_treaपंचांगent treaपंचांगent;

	treaपंचांगent = __reg_process_hपूर्णांक_user(user_request);
	अगर (treaपंचांगent == REG_REQ_IGNORE ||
	    treaपंचांगent == REG_REQ_ALREADY_SET)
		वापस REG_REQ_IGNORE;

	user_request->पूर्णांकersect = treaपंचांगent == REG_REQ_INTERSECT;
	user_request->processed = false;

	अगर (reg_query_database(user_request)) अणु
		reg_update_last_request(user_request);
		user_alpha2[0] = user_request->alpha2[0];
		user_alpha2[1] = user_request->alpha2[1];
		वापस REG_REQ_OK;
	पूर्ण

	वापस REG_REQ_IGNORE;
पूर्ण

अटल क्रमागत reg_request_treaपंचांगent
__reg_process_hपूर्णांक_driver(काष्ठा regulatory_request *driver_request)
अणु
	काष्ठा regulatory_request *lr = get_last_request();

	अगर (lr->initiator == NL80211_REGDOM_SET_BY_CORE) अणु
		अगर (regकरोm_changes(driver_request->alpha2))
			वापस REG_REQ_OK;
		वापस REG_REQ_ALREADY_SET;
	पूर्ण

	/*
	 * This would happen अगर you unplug and plug your card
	 * back in or अगर you add a new device क्रम which the previously
	 * loaded card also agrees on the regulatory करोमुख्य.
	 */
	अगर (lr->initiator == NL80211_REGDOM_SET_BY_DRIVER &&
	    !regकरोm_changes(driver_request->alpha2))
		वापस REG_REQ_ALREADY_SET;

	वापस REG_REQ_INTERSECT;
पूर्ण

/**
 * reg_process_hपूर्णांक_driver - process driver regulatory requests
 * @wiphy: the wireless device क्रम the regulatory request
 * @driver_request: a pending driver regulatory request
 *
 * The wireless subप्रणाली can use this function to process
 * a regulatory request issued by an 802.11 driver.
 *
 * Returns one of the dअगरferent reg request treaपंचांगent values.
 */
अटल क्रमागत reg_request_treaपंचांगent
reg_process_hपूर्णांक_driver(काष्ठा wiphy *wiphy,
			काष्ठा regulatory_request *driver_request)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd, *पंचांगp;
	क्रमागत reg_request_treaपंचांगent treaपंचांगent;

	treaपंचांगent = __reg_process_hपूर्णांक_driver(driver_request);

	चयन (treaपंचांगent) अणु
	हाल REG_REQ_OK:
		अवरोध;
	हाल REG_REQ_IGNORE:
		वापस REG_REQ_IGNORE;
	हाल REG_REQ_INTERSECT:
	हाल REG_REQ_ALREADY_SET:
		regd = reg_copy_regd(get_cfg80211_regकरोm());
		अगर (IS_ERR(regd))
			वापस REG_REQ_IGNORE;

		पंचांगp = get_wiphy_regकरोm(wiphy);
		ASSERT_RTNL();
		wiphy_lock(wiphy);
		rcu_assign_poपूर्णांकer(wiphy->regd, regd);
		wiphy_unlock(wiphy);
		rcu_मुक्त_regकरोm(पंचांगp);
	पूर्ण


	driver_request->पूर्णांकersect = treaपंचांगent == REG_REQ_INTERSECT;
	driver_request->processed = false;

	/*
	 * Since CRDA will not be called in this हाल as we alपढ़ोy
	 * have applied the requested regulatory करोमुख्य beक्रमe we just
	 * inक्रमm userspace we have processed the request
	 */
	अगर (treaपंचांगent == REG_REQ_ALREADY_SET) अणु
		nl80211_send_reg_change_event(driver_request);
		reg_update_last_request(driver_request);
		reg_set_request_processed();
		वापस REG_REQ_ALREADY_SET;
	पूर्ण

	अगर (reg_query_database(driver_request)) अणु
		reg_update_last_request(driver_request);
		वापस REG_REQ_OK;
	पूर्ण

	वापस REG_REQ_IGNORE;
पूर्ण

अटल क्रमागत reg_request_treaपंचांगent
__reg_process_hपूर्णांक_country_ie(काष्ठा wiphy *wiphy,
			      काष्ठा regulatory_request *country_ie_request)
अणु
	काष्ठा wiphy *last_wiphy = शून्य;
	काष्ठा regulatory_request *lr = get_last_request();

	अगर (reg_request_cell_base(lr)) अणु
		/* Trust a Cell base station over the AP's country IE */
		अगर (regकरोm_changes(country_ie_request->alpha2))
			वापस REG_REQ_IGNORE;
		वापस REG_REQ_ALREADY_SET;
	पूर्ण अन्यथा अणु
		अगर (wiphy->regulatory_flags & REGULATORY_COUNTRY_IE_IGNORE)
			वापस REG_REQ_IGNORE;
	पूर्ण

	अगर (unlikely(!is_an_alpha2(country_ie_request->alpha2)))
		वापस -EINVAL;

	अगर (lr->initiator != NL80211_REGDOM_SET_BY_COUNTRY_IE)
		वापस REG_REQ_OK;

	last_wiphy = wiphy_idx_to_wiphy(lr->wiphy_idx);

	अगर (last_wiphy != wiphy) अणु
		/*
		 * Two cards with two APs claiming dअगरferent
		 * Country IE alpha2s. We could
		 * पूर्णांकersect them, but that seems unlikely
		 * to be correct. Reject second one क्रम now.
		 */
		अगर (regकरोm_changes(country_ie_request->alpha2))
			वापस REG_REQ_IGNORE;
		वापस REG_REQ_ALREADY_SET;
	पूर्ण

	अगर (regकरोm_changes(country_ie_request->alpha2))
		वापस REG_REQ_OK;
	वापस REG_REQ_ALREADY_SET;
पूर्ण

/**
 * reg_process_hपूर्णांक_country_ie - process regulatory requests from country IEs
 * @wiphy: the wireless device क्रम the regulatory request
 * @country_ie_request: a regulatory request from a country IE
 *
 * The wireless subप्रणाली can use this function to process
 * a regulatory request issued by a country Inक्रमmation Element.
 *
 * Returns one of the dअगरferent reg request treaपंचांगent values.
 */
अटल क्रमागत reg_request_treaपंचांगent
reg_process_hपूर्णांक_country_ie(काष्ठा wiphy *wiphy,
			    काष्ठा regulatory_request *country_ie_request)
अणु
	क्रमागत reg_request_treaपंचांगent treaपंचांगent;

	treaपंचांगent = __reg_process_hपूर्णांक_country_ie(wiphy, country_ie_request);

	चयन (treaपंचांगent) अणु
	हाल REG_REQ_OK:
		अवरोध;
	हाल REG_REQ_IGNORE:
		वापस REG_REQ_IGNORE;
	हाल REG_REQ_ALREADY_SET:
		reg_मुक्त_request(country_ie_request);
		वापस REG_REQ_ALREADY_SET;
	हाल REG_REQ_INTERSECT:
		/*
		 * This करोesn't happen yet, not sure we
		 * ever want to support it क्रम this हाल.
		 */
		WARN_ONCE(1, "Unexpected intersection for country elements");
		वापस REG_REQ_IGNORE;
	पूर्ण

	country_ie_request->पूर्णांकersect = false;
	country_ie_request->processed = false;

	अगर (reg_query_database(country_ie_request)) अणु
		reg_update_last_request(country_ie_request);
		वापस REG_REQ_OK;
	पूर्ण

	वापस REG_REQ_IGNORE;
पूर्ण

bool reg_dfs_करोमुख्य_same(काष्ठा wiphy *wiphy1, काष्ठा wiphy *wiphy2)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *wiphy1_regd = शून्य;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *wiphy2_regd = शून्य;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *cfg80211_regd = शून्य;
	bool dfs_करोमुख्य_same;

	rcu_पढ़ो_lock();

	cfg80211_regd = rcu_dereference(cfg80211_regकरोमुख्य);
	wiphy1_regd = rcu_dereference(wiphy1->regd);
	अगर (!wiphy1_regd)
		wiphy1_regd = cfg80211_regd;

	wiphy2_regd = rcu_dereference(wiphy2->regd);
	अगर (!wiphy2_regd)
		wiphy2_regd = cfg80211_regd;

	dfs_करोमुख्य_same = wiphy1_regd->dfs_region == wiphy2_regd->dfs_region;

	rcu_पढ़ो_unlock();

	वापस dfs_करोमुख्य_same;
पूर्ण

अटल व्योम reg_copy_dfs_chan_state(काष्ठा ieee80211_channel *dst_chan,
				    काष्ठा ieee80211_channel *src_chan)
अणु
	अगर (!(dst_chan->flags & IEEE80211_CHAN_RADAR) ||
	    !(src_chan->flags & IEEE80211_CHAN_RADAR))
		वापस;

	अगर (dst_chan->flags & IEEE80211_CHAN_DISABLED ||
	    src_chan->flags & IEEE80211_CHAN_DISABLED)
		वापस;

	अगर (src_chan->center_freq == dst_chan->center_freq &&
	    dst_chan->dfs_state == NL80211_DFS_USABLE) अणु
		dst_chan->dfs_state = src_chan->dfs_state;
		dst_chan->dfs_state_entered = src_chan->dfs_state_entered;
	पूर्ण
पूर्ण

अटल व्योम wiphy_share_dfs_chan_state(काष्ठा wiphy *dst_wiphy,
				       काष्ठा wiphy *src_wiphy)
अणु
	काष्ठा ieee80211_supported_band *src_sband, *dst_sband;
	काष्ठा ieee80211_channel *src_chan, *dst_chan;
	पूर्णांक i, j, band;

	अगर (!reg_dfs_करोमुख्य_same(dst_wiphy, src_wiphy))
		वापस;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		dst_sband = dst_wiphy->bands[band];
		src_sband = src_wiphy->bands[band];
		अगर (!dst_sband || !src_sband)
			जारी;

		क्रम (i = 0; i < dst_sband->n_channels; i++) अणु
			dst_chan = &dst_sband->channels[i];
			क्रम (j = 0; j < src_sband->n_channels; j++) अणु
				src_chan = &src_sband->channels[j];
				reg_copy_dfs_chan_state(dst_chan, src_chan);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम wiphy_all_share_dfs_chan_state(काष्ठा wiphy *wiphy)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	ASSERT_RTNL();

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		अगर (wiphy == &rdev->wiphy)
			जारी;
		wiphy_share_dfs_chan_state(wiphy, &rdev->wiphy);
	पूर्ण
पूर्ण

/* This processes *all* regulatory hपूर्णांकs */
अटल व्योम reg_process_hपूर्णांक(काष्ठा regulatory_request *reg_request)
अणु
	काष्ठा wiphy *wiphy = शून्य;
	क्रमागत reg_request_treaपंचांगent treaपंचांगent;
	क्रमागत nl80211_reg_initiator initiator = reg_request->initiator;

	अगर (reg_request->wiphy_idx != WIPHY_IDX_INVALID)
		wiphy = wiphy_idx_to_wiphy(reg_request->wiphy_idx);

	चयन (initiator) अणु
	हाल NL80211_REGDOM_SET_BY_CORE:
		treaपंचांगent = reg_process_hपूर्णांक_core(reg_request);
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_USER:
		treaपंचांगent = reg_process_hपूर्णांक_user(reg_request);
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_DRIVER:
		अगर (!wiphy)
			जाओ out_मुक्त;
		treaपंचांगent = reg_process_hपूर्णांक_driver(wiphy, reg_request);
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_COUNTRY_IE:
		अगर (!wiphy)
			जाओ out_मुक्त;
		treaपंचांगent = reg_process_hपूर्णांक_country_ie(wiphy, reg_request);
		अवरोध;
	शेष:
		WARN(1, "invalid initiator %d\n", initiator);
		जाओ out_मुक्त;
	पूर्ण

	अगर (treaपंचांगent == REG_REQ_IGNORE)
		जाओ out_मुक्त;

	WARN(treaपंचांगent != REG_REQ_OK && treaपंचांगent != REG_REQ_ALREADY_SET,
	     "unexpected treatment value %d\n", treaपंचांगent);

	/* This is required so that the orig_* parameters are saved.
	 * NOTE: treaपंचांगent must be set क्रम any हाल that reaches here!
	 */
	अगर (treaपंचांगent == REG_REQ_ALREADY_SET && wiphy &&
	    wiphy->regulatory_flags & REGULATORY_STRICT_REG) अणु
		wiphy_update_regulatory(wiphy, initiator);
		wiphy_all_share_dfs_chan_state(wiphy);
		reg_check_channels();
	पूर्ण

	वापस;

out_मुक्त:
	reg_मुक्त_request(reg_request);
पूर्ण

अटल व्योम notअगरy_self_managed_wiphys(काष्ठा regulatory_request *request)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wiphy *wiphy;

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		wiphy = &rdev->wiphy;
		अगर (wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED &&
		    request->initiator == NL80211_REGDOM_SET_BY_USER)
			reg_call_notअगरier(wiphy, request);
	पूर्ण
पूर्ण

/*
 * Processes regulatory hपूर्णांकs, this is all the NL80211_REGDOM_SET_BY_*
 * Regulatory hपूर्णांकs come on a first come first serve basis and we
 * must process each one atomically.
 */
अटल व्योम reg_process_pending_hपूर्णांकs(व्योम)
अणु
	काष्ठा regulatory_request *reg_request, *lr;

	lr = get_last_request();

	/* When last_request->processed becomes true this will be rescheduled */
	अगर (lr && !lr->processed) अणु
		pr_debug("Pending regulatory request, waiting for it to be processed...\n");
		वापस;
	पूर्ण

	spin_lock(&reg_requests_lock);

	अगर (list_empty(&reg_requests_list)) अणु
		spin_unlock(&reg_requests_lock);
		वापस;
	पूर्ण

	reg_request = list_first_entry(&reg_requests_list,
				       काष्ठा regulatory_request,
				       list);
	list_del_init(&reg_request->list);

	spin_unlock(&reg_requests_lock);

	notअगरy_self_managed_wiphys(reg_request);

	reg_process_hपूर्णांक(reg_request);

	lr = get_last_request();

	spin_lock(&reg_requests_lock);
	अगर (!list_empty(&reg_requests_list) && lr && lr->processed)
		schedule_work(&reg_work);
	spin_unlock(&reg_requests_lock);
पूर्ण

/* Processes beacon hपूर्णांकs -- this has nothing to करो with country IEs */
अटल व्योम reg_process_pending_beacon_hपूर्णांकs(व्योम)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा reg_beacon *pending_beacon, *पंचांगp;

	/* This goes through the _pending_ beacon list */
	spin_lock_bh(&reg_pending_beacons_lock);

	list_क्रम_each_entry_safe(pending_beacon, पंचांगp,
				 &reg_pending_beacons, list) अणु
		list_del_init(&pending_beacon->list);

		/* Applies the beacon hपूर्णांक to current wiphys */
		list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list)
			wiphy_update_new_beacon(&rdev->wiphy, pending_beacon);

		/* Remembers the beacon hपूर्णांक क्रम new wiphys or reg changes */
		list_add_tail(&pending_beacon->list, &reg_beacon_list);
	पूर्ण

	spin_unlock_bh(&reg_pending_beacons_lock);
पूर्ण

अटल व्योम reg_process_self_managed_hपूर्णांक(काष्ठा wiphy *wiphy)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	स्थिर काष्ठा ieee80211_regकरोमुख्य *पंचांगp;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd;
	क्रमागत nl80211_band band;
	काष्ठा regulatory_request request = अणुपूर्ण;

	ASSERT_RTNL();
	lockdep_निश्चित_wiphy(wiphy);

	spin_lock(&reg_requests_lock);
	regd = rdev->requested_regd;
	rdev->requested_regd = शून्य;
	spin_unlock(&reg_requests_lock);

	अगर (!regd)
		वापस;

	पंचांगp = get_wiphy_regकरोm(wiphy);
	rcu_assign_poपूर्णांकer(wiphy->regd, regd);
	rcu_मुक्त_regकरोm(पंचांगp);

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++)
		handle_band_custom(wiphy, wiphy->bands[band], regd);

	reg_process_ht_flags(wiphy);

	request.wiphy_idx = get_wiphy_idx(wiphy);
	request.alpha2[0] = regd->alpha2[0];
	request.alpha2[1] = regd->alpha2[1];
	request.initiator = NL80211_REGDOM_SET_BY_DRIVER;

	nl80211_send_wiphy_reg_change_event(&request);
पूर्ण

अटल व्योम reg_process_self_managed_hपूर्णांकs(व्योम)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	ASSERT_RTNL();

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		wiphy_lock(&rdev->wiphy);
		reg_process_self_managed_hपूर्णांक(&rdev->wiphy);
		wiphy_unlock(&rdev->wiphy);
	पूर्ण

	reg_check_channels();
पूर्ण

अटल व्योम reg_toकरो(काष्ठा work_काष्ठा *work)
अणु
	rtnl_lock();
	reg_process_pending_hपूर्णांकs();
	reg_process_pending_beacon_hपूर्णांकs();
	reg_process_self_managed_hपूर्णांकs();
	rtnl_unlock();
पूर्ण

अटल व्योम queue_regulatory_request(काष्ठा regulatory_request *request)
अणु
	request->alpha2[0] = बड़े(request->alpha2[0]);
	request->alpha2[1] = बड़े(request->alpha2[1]);

	spin_lock(&reg_requests_lock);
	list_add_tail(&request->list, &reg_requests_list);
	spin_unlock(&reg_requests_lock);

	schedule_work(&reg_work);
पूर्ण

/*
 * Core regulatory hपूर्णांक -- happens during cfg80211_init()
 * and when we restore regulatory settings.
 */
अटल पूर्णांक regulatory_hपूर्णांक_core(स्थिर अक्षर *alpha2)
अणु
	काष्ठा regulatory_request *request;

	request = kzalloc(माप(काष्ठा regulatory_request), GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;

	request->alpha2[0] = alpha2[0];
	request->alpha2[1] = alpha2[1];
	request->initiator = NL80211_REGDOM_SET_BY_CORE;
	request->wiphy_idx = WIPHY_IDX_INVALID;

	queue_regulatory_request(request);

	वापस 0;
पूर्ण

/* User hपूर्णांकs */
पूर्णांक regulatory_hपूर्णांक_user(स्थिर अक्षर *alpha2,
			 क्रमागत nl80211_user_reg_hपूर्णांक_type user_reg_hपूर्णांक_type)
अणु
	काष्ठा regulatory_request *request;

	अगर (WARN_ON(!alpha2))
		वापस -EINVAL;

	अगर (!is_world_regकरोm(alpha2) && !is_an_alpha2(alpha2))
		वापस -EINVAL;

	request = kzalloc(माप(काष्ठा regulatory_request), GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;

	request->wiphy_idx = WIPHY_IDX_INVALID;
	request->alpha2[0] = alpha2[0];
	request->alpha2[1] = alpha2[1];
	request->initiator = NL80211_REGDOM_SET_BY_USER;
	request->user_reg_hपूर्णांक_type = user_reg_hपूर्णांक_type;

	/* Allow calling CRDA again */
	reset_crda_समयouts();

	queue_regulatory_request(request);

	वापस 0;
पूर्ण

पूर्णांक regulatory_hपूर्णांक_inकरोor(bool is_inकरोor, u32 portid)
अणु
	spin_lock(&reg_inकरोor_lock);

	/* It is possible that more than one user space process is trying to
	 * configure the inकरोor setting. To handle such हालs, clear the inकरोor
	 * setting in हाल that some process करोes not think that the device
	 * is operating in an inकरोor environment. In addition, अगर a user space
	 * process indicates that it is controlling the inकरोor setting, save its
	 * portid, i.e., make it the owner.
	 */
	reg_is_inकरोor = is_inकरोor;
	अगर (reg_is_inकरोor) अणु
		अगर (!reg_is_inकरोor_portid)
			reg_is_inकरोor_portid = portid;
	पूर्ण अन्यथा अणु
		reg_is_inकरोor_portid = 0;
	पूर्ण

	spin_unlock(&reg_inकरोor_lock);

	अगर (!is_inकरोor)
		reg_check_channels();

	वापस 0;
पूर्ण

व्योम regulatory_netlink_notअगरy(u32 portid)
अणु
	spin_lock(&reg_inकरोor_lock);

	अगर (reg_is_inकरोor_portid != portid) अणु
		spin_unlock(&reg_inकरोor_lock);
		वापस;
	पूर्ण

	reg_is_inकरोor = false;
	reg_is_inकरोor_portid = 0;

	spin_unlock(&reg_inकरोor_lock);

	reg_check_channels();
पूर्ण

/* Driver hपूर्णांकs */
पूर्णांक regulatory_hपूर्णांक(काष्ठा wiphy *wiphy, स्थिर अक्षर *alpha2)
अणु
	काष्ठा regulatory_request *request;

	अगर (WARN_ON(!alpha2 || !wiphy))
		वापस -EINVAL;

	wiphy->regulatory_flags &= ~REGULATORY_CUSTOM_REG;

	request = kzalloc(माप(काष्ठा regulatory_request), GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;

	request->wiphy_idx = get_wiphy_idx(wiphy);

	request->alpha2[0] = alpha2[0];
	request->alpha2[1] = alpha2[1];
	request->initiator = NL80211_REGDOM_SET_BY_DRIVER;

	/* Allow calling CRDA again */
	reset_crda_समयouts();

	queue_regulatory_request(request);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(regulatory_hपूर्णांक);

व्योम regulatory_hपूर्णांक_country_ie(काष्ठा wiphy *wiphy, क्रमागत nl80211_band band,
				स्थिर u8 *country_ie, u8 country_ie_len)
अणु
	अक्षर alpha2[2];
	क्रमागत environment_cap env = ENVIRON_ANY;
	काष्ठा regulatory_request *request = शून्य, *lr;

	/* IE len must be evenly भागisible by 2 */
	अगर (country_ie_len & 0x01)
		वापस;

	अगर (country_ie_len < IEEE80211_COUNTRY_IE_MIN_LEN)
		वापस;

	request = kzalloc(माप(*request), GFP_KERNEL);
	अगर (!request)
		वापस;

	alpha2[0] = country_ie[0];
	alpha2[1] = country_ie[1];

	अगर (country_ie[2] == 'I')
		env = ENVIRON_INDOOR;
	अन्यथा अगर (country_ie[2] == 'O')
		env = ENVIRON_OUTDOOR;

	rcu_पढ़ो_lock();
	lr = get_last_request();

	अगर (unlikely(!lr))
		जाओ out;

	/*
	 * We will run this only upon a successful connection on cfg80211.
	 * We leave conflict resolution to the workqueue, where can hold
	 * the RTNL.
	 */
	अगर (lr->initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE &&
	    lr->wiphy_idx != WIPHY_IDX_INVALID)
		जाओ out;

	request->wiphy_idx = get_wiphy_idx(wiphy);
	request->alpha2[0] = alpha2[0];
	request->alpha2[1] = alpha2[1];
	request->initiator = NL80211_REGDOM_SET_BY_COUNTRY_IE;
	request->country_ie_env = env;

	/* Allow calling CRDA again */
	reset_crda_समयouts();

	queue_regulatory_request(request);
	request = शून्य;
out:
	kमुक्त(request);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम restore_alpha2(अक्षर *alpha2, bool reset_user)
अणु
	/* indicates there is no alpha2 to consider क्रम restoration */
	alpha2[0] = '9';
	alpha2[1] = '7';

	/* The user setting has precedence over the module parameter */
	अगर (is_user_regकरोm_saved()) अणु
		/* Unless we're asked to ignore it and reset it */
		अगर (reset_user) अणु
			pr_debug("Restoring regulatory settings including user preference\n");
			user_alpha2[0] = '9';
			user_alpha2[1] = '7';

			/*
			 * If we're ignoring user settings, we still need to
			 * check the module parameter to ensure we put things
			 * back as they were क्रम a full restore.
			 */
			अगर (!is_world_regकरोm(ieee80211_regकरोm)) अणु
				pr_debug("Keeping preference on module parameter ieee80211_regdom: %c%c\n",
					 ieee80211_regकरोm[0], ieee80211_regकरोm[1]);
				alpha2[0] = ieee80211_regकरोm[0];
				alpha2[1] = ieee80211_regकरोm[1];
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_debug("Restoring regulatory settings while preserving user preference for: %c%c\n",
				 user_alpha2[0], user_alpha2[1]);
			alpha2[0] = user_alpha2[0];
			alpha2[1] = user_alpha2[1];
		पूर्ण
	पूर्ण अन्यथा अगर (!is_world_regकरोm(ieee80211_regकरोm)) अणु
		pr_debug("Keeping preference on module parameter ieee80211_regdom: %c%c\n",
			 ieee80211_regकरोm[0], ieee80211_regकरोm[1]);
		alpha2[0] = ieee80211_regकरोm[0];
		alpha2[1] = ieee80211_regकरोm[1];
	पूर्ण अन्यथा
		pr_debug("Restoring regulatory settings\n");
पूर्ण

अटल व्योम restore_custom_reg_settings(काष्ठा wiphy *wiphy)
अणु
	काष्ठा ieee80211_supported_band *sband;
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_channel *chan;
	पूर्णांक i;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		sband = wiphy->bands[band];
		अगर (!sband)
			जारी;
		क्रम (i = 0; i < sband->n_channels; i++) अणु
			chan = &sband->channels[i];
			chan->flags = chan->orig_flags;
			chan->max_antenna_gain = chan->orig_mag;
			chan->max_घातer = chan->orig_mpwr;
			chan->beacon_found = false;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Restoring regulatory settings involves ignoring any
 * possibly stale country IE inक्रमmation and user regulatory
 * settings अगर so desired, this includes any beacon hपूर्णांकs
 * learned as we could have traveled outside to another country
 * after disconnection. To restore regulatory settings we करो
 * exactly what we did at bootup:
 *
 *   - send a core regulatory hपूर्णांक
 *   - send a user regulatory hपूर्णांक अगर applicable
 *
 * Device drivers that send a regulatory hपूर्णांक क्रम a specअगरic country
 * keep their own regulatory करोमुख्य on wiphy->regd so that करोes
 * not need to be remembered.
 */
अटल व्योम restore_regulatory_settings(bool reset_user, bool cached)
अणु
	अक्षर alpha2[2];
	अक्षर world_alpha2[2];
	काष्ठा reg_beacon *reg_beacon, *bपंचांगp;
	LIST_HEAD(पंचांगp_reg_req_list);
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	ASSERT_RTNL();

	/*
	 * Clear the inकरोor setting in हाल that it is not controlled by user
	 * space, as otherwise there is no guarantee that the device is still
	 * operating in an inकरोor environment.
	 */
	spin_lock(&reg_inकरोor_lock);
	अगर (reg_is_inकरोor && !reg_is_inकरोor_portid) अणु
		reg_is_inकरोor = false;
		reg_check_channels();
	पूर्ण
	spin_unlock(&reg_inकरोor_lock);

	reset_regकरोमुख्यs(true, &world_regकरोm);
	restore_alpha2(alpha2, reset_user);

	/*
	 * If there's any pending requests we simply
	 * stash them to a temporary pending queue and
	 * add then after we've restored regulatory
	 * settings.
	 */
	spin_lock(&reg_requests_lock);
	list_splice_tail_init(&reg_requests_list, &पंचांगp_reg_req_list);
	spin_unlock(&reg_requests_lock);

	/* Clear beacon hपूर्णांकs */
	spin_lock_bh(&reg_pending_beacons_lock);
	list_क्रम_each_entry_safe(reg_beacon, bपंचांगp, &reg_pending_beacons, list) अणु
		list_del(&reg_beacon->list);
		kमुक्त(reg_beacon);
	पूर्ण
	spin_unlock_bh(&reg_pending_beacons_lock);

	list_क्रम_each_entry_safe(reg_beacon, bपंचांगp, &reg_beacon_list, list) अणु
		list_del(&reg_beacon->list);
		kमुक्त(reg_beacon);
	पूर्ण

	/* First restore to the basic regulatory settings */
	world_alpha2[0] = cfg80211_world_regकरोm->alpha2[0];
	world_alpha2[1] = cfg80211_world_regकरोm->alpha2[1];

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		अगर (rdev->wiphy.regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED)
			जारी;
		अगर (rdev->wiphy.regulatory_flags & REGULATORY_CUSTOM_REG)
			restore_custom_reg_settings(&rdev->wiphy);
	पूर्ण

	अगर (cached && (!is_an_alpha2(alpha2) ||
		       !IS_ERR_OR_शून्य(cfg80211_user_regकरोm))) अणु
		reset_regकरोमुख्यs(false, cfg80211_world_regकरोm);
		update_all_wiphy_regulatory(NL80211_REGDOM_SET_BY_CORE);
		prपूर्णांक_regकरोमुख्य(get_cfg80211_regकरोm());
		nl80211_send_reg_change_event(&core_request_world);
		reg_set_request_processed();

		अगर (is_an_alpha2(alpha2) &&
		    !regulatory_hपूर्णांक_user(alpha2, NL80211_USER_REG_HINT_USER)) अणु
			काष्ठा regulatory_request *ureq;

			spin_lock(&reg_requests_lock);
			ureq = list_last_entry(&reg_requests_list,
					       काष्ठा regulatory_request,
					       list);
			list_del(&ureq->list);
			spin_unlock(&reg_requests_lock);

			notअगरy_self_managed_wiphys(ureq);
			reg_update_last_request(ureq);
			set_regकरोm(reg_copy_regd(cfg80211_user_regकरोm),
				   REGD_SOURCE_CACHED);
		पूर्ण
	पूर्ण अन्यथा अणु
		regulatory_hपूर्णांक_core(world_alpha2);

		/*
		 * This restores the ieee80211_regकरोm module parameter
		 * preference or the last user requested regulatory
		 * settings, user regulatory settings takes precedence.
		 */
		अगर (is_an_alpha2(alpha2))
			regulatory_hपूर्णांक_user(alpha2, NL80211_USER_REG_HINT_USER);
	पूर्ण

	spin_lock(&reg_requests_lock);
	list_splice_tail_init(&पंचांगp_reg_req_list, &reg_requests_list);
	spin_unlock(&reg_requests_lock);

	pr_debug("Kicking the queue\n");

	schedule_work(&reg_work);
पूर्ण

अटल bool is_wiphy_all_set_reg_flag(क्रमागत ieee80211_regulatory_flags flag)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wireless_dev *wdev;

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
			wdev_lock(wdev);
			अगर (!(wdev->wiphy->regulatory_flags & flag)) अणु
				wdev_unlock(wdev);
				वापस false;
			पूर्ण
			wdev_unlock(wdev);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

व्योम regulatory_hपूर्णांक_disconnect(व्योम)
अणु
	/* Restore of regulatory settings is not required when wiphy(s)
	 * ignore IE from connected access poपूर्णांक but clearance of beacon hपूर्णांकs
	 * is required when wiphy(s) supports beacon hपूर्णांकs.
	 */
	अगर (is_wiphy_all_set_reg_flag(REGULATORY_COUNTRY_IE_IGNORE)) अणु
		काष्ठा reg_beacon *reg_beacon, *bपंचांगp;

		अगर (is_wiphy_all_set_reg_flag(REGULATORY_DISABLE_BEACON_HINTS))
			वापस;

		spin_lock_bh(&reg_pending_beacons_lock);
		list_क्रम_each_entry_safe(reg_beacon, bपंचांगp,
					 &reg_pending_beacons, list) अणु
			list_del(&reg_beacon->list);
			kमुक्त(reg_beacon);
		पूर्ण
		spin_unlock_bh(&reg_pending_beacons_lock);

		list_क्रम_each_entry_safe(reg_beacon, bपंचांगp,
					 &reg_beacon_list, list) अणु
			list_del(&reg_beacon->list);
			kमुक्त(reg_beacon);
		पूर्ण

		वापस;
	पूर्ण

	pr_debug("All devices are disconnected, going to restore regulatory settings\n");
	restore_regulatory_settings(false, true);
पूर्ण

अटल bool freq_is_chan_12_13_14(u32 freq)
अणु
	अगर (freq == ieee80211_channel_to_frequency(12, NL80211_BAND_2GHZ) ||
	    freq == ieee80211_channel_to_frequency(13, NL80211_BAND_2GHZ) ||
	    freq == ieee80211_channel_to_frequency(14, NL80211_BAND_2GHZ))
		वापस true;
	वापस false;
पूर्ण

अटल bool pending_reg_beacon(काष्ठा ieee80211_channel *beacon_chan)
अणु
	काष्ठा reg_beacon *pending_beacon;

	list_क्रम_each_entry(pending_beacon, &reg_pending_beacons, list)
		अगर (ieee80211_channel_equal(beacon_chan,
					    &pending_beacon->chan))
			वापस true;
	वापस false;
पूर्ण

पूर्णांक regulatory_hपूर्णांक_found_beacon(काष्ठा wiphy *wiphy,
				 काष्ठा ieee80211_channel *beacon_chan,
				 gfp_t gfp)
अणु
	काष्ठा reg_beacon *reg_beacon;
	bool processing;

	अगर (beacon_chan->beacon_found ||
	    beacon_chan->flags & IEEE80211_CHAN_RADAR ||
	    (beacon_chan->band == NL80211_BAND_2GHZ &&
	     !freq_is_chan_12_13_14(beacon_chan->center_freq)))
		वापस 0;

	spin_lock_bh(&reg_pending_beacons_lock);
	processing = pending_reg_beacon(beacon_chan);
	spin_unlock_bh(&reg_pending_beacons_lock);

	अगर (processing)
		वापस 0;

	reg_beacon = kzalloc(माप(काष्ठा reg_beacon), gfp);
	अगर (!reg_beacon)
		वापस -ENOMEM;

	pr_debug("Found new beacon on frequency: %d.%03d MHz (Ch %d) on %s\n",
		 beacon_chan->center_freq, beacon_chan->freq_offset,
		 ieee80211_freq_khz_to_channel(
			 ieee80211_channel_to_khz(beacon_chan)),
		 wiphy_name(wiphy));

	स_नकल(&reg_beacon->chan, beacon_chan,
	       माप(काष्ठा ieee80211_channel));

	/*
	 * Since we can be called from BH or and non-BH context
	 * we must use spin_lock_bh()
	 */
	spin_lock_bh(&reg_pending_beacons_lock);
	list_add_tail(&reg_beacon->list, &reg_pending_beacons);
	spin_unlock_bh(&reg_pending_beacons_lock);

	schedule_work(&reg_work);

	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_rd_rules(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर काष्ठा ieee80211_reg_rule *reg_rule = शून्य;
	स्थिर काष्ठा ieee80211_freq_range *freq_range = शून्य;
	स्थिर काष्ठा ieee80211_घातer_rule *घातer_rule = शून्य;
	अक्षर bw[32], cac_समय[32];

	pr_debug("  (start_freq - end_freq @ bandwidth), (max_antenna_gain, max_eirp), (dfs_cac_time)\n");

	क्रम (i = 0; i < rd->n_reg_rules; i++) अणु
		reg_rule = &rd->reg_rules[i];
		freq_range = &reg_rule->freq_range;
		घातer_rule = &reg_rule->घातer_rule;

		अगर (reg_rule->flags & NL80211_RRF_AUTO_BW)
			snम_लिखो(bw, माप(bw), "%d KHz, %u KHz AUTO",
				 freq_range->max_bandwidth_khz,
				 reg_get_max_bandwidth(rd, reg_rule));
		अन्यथा
			snम_लिखो(bw, माप(bw), "%d KHz",
				 freq_range->max_bandwidth_khz);

		अगर (reg_rule->flags & NL80211_RRF_DFS)
			scnम_लिखो(cac_समय, माप(cac_समय), "%u s",
				  reg_rule->dfs_cac_ms/1000);
		अन्यथा
			scnम_लिखो(cac_समय, माप(cac_समय), "N/A");


		/*
		 * There may not be करोcumentation क्रम max antenna gain
		 * in certain regions
		 */
		अगर (घातer_rule->max_antenna_gain)
			pr_debug("  (%d KHz - %d KHz @ %s), (%d mBi, %d mBm), (%s)\n",
				freq_range->start_freq_khz,
				freq_range->end_freq_khz,
				bw,
				घातer_rule->max_antenna_gain,
				घातer_rule->max_eirp,
				cac_समय);
		अन्यथा
			pr_debug("  (%d KHz - %d KHz @ %s), (N/A, %d mBm), (%s)\n",
				freq_range->start_freq_khz,
				freq_range->end_freq_khz,
				bw,
				घातer_rule->max_eirp,
				cac_समय);
	पूर्ण
पूर्ण

bool reg_supported_dfs_region(क्रमागत nl80211_dfs_regions dfs_region)
अणु
	चयन (dfs_region) अणु
	हाल NL80211_DFS_UNSET:
	हाल NL80211_DFS_FCC:
	हाल NL80211_DFS_ETSI:
	हाल NL80211_DFS_JP:
		वापस true;
	शेष:
		pr_debug("Ignoring unknown DFS master region: %d\n", dfs_region);
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_regकरोमुख्य(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd)
अणु
	काष्ठा regulatory_request *lr = get_last_request();

	अगर (is_पूर्णांकersected_alpha2(rd->alpha2)) अणु
		अगर (lr->initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE) अणु
			काष्ठा cfg80211_रेजिस्टरed_device *rdev;
			rdev = cfg80211_rdev_by_wiphy_idx(lr->wiphy_idx);
			अगर (rdev) अणु
				pr_debug("Current regulatory domain updated by AP to: %c%c\n",
					rdev->country_ie_alpha2[0],
					rdev->country_ie_alpha2[1]);
			पूर्ण अन्यथा
				pr_debug("Current regulatory domain intersected:\n");
		पूर्ण अन्यथा
			pr_debug("Current regulatory domain intersected:\n");
	पूर्ण अन्यथा अगर (is_world_regकरोm(rd->alpha2)) अणु
		pr_debug("World regulatory domain updated:\n");
	पूर्ण अन्यथा अणु
		अगर (is_unknown_alpha2(rd->alpha2))
			pr_debug("Regulatory domain changed to driver built-in settings (unknown country)\n");
		अन्यथा अणु
			अगर (reg_request_cell_base(lr))
				pr_debug("Regulatory domain changed to country: %c%c by Cell Station\n",
					rd->alpha2[0], rd->alpha2[1]);
			अन्यथा
				pr_debug("Regulatory domain changed to country: %c%c\n",
					rd->alpha2[0], rd->alpha2[1]);
		पूर्ण
	पूर्ण

	pr_debug(" DFS Master region: %s", reg_dfs_region_str(rd->dfs_region));
	prपूर्णांक_rd_rules(rd);
पूर्ण

अटल व्योम prपूर्णांक_regकरोमुख्य_info(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd)
अणु
	pr_debug("Regulatory domain: %c%c\n", rd->alpha2[0], rd->alpha2[1]);
	prपूर्णांक_rd_rules(rd);
पूर्ण

अटल पूर्णांक reg_set_rd_core(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd)
अणु
	अगर (!is_world_regकरोm(rd->alpha2))
		वापस -EINVAL;
	update_world_regकरोमुख्य(rd);
	वापस 0;
पूर्ण

अटल पूर्णांक reg_set_rd_user(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd,
			   काष्ठा regulatory_request *user_request)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *पूर्णांकersected_rd = शून्य;

	अगर (!regकरोm_changes(rd->alpha2))
		वापस -EALREADY;

	अगर (!is_valid_rd(rd)) अणु
		pr_err("Invalid regulatory domain detected: %c%c\n",
		       rd->alpha2[0], rd->alpha2[1]);
		prपूर्णांक_regकरोमुख्य_info(rd);
		वापस -EINVAL;
	पूर्ण

	अगर (!user_request->पूर्णांकersect) अणु
		reset_regकरोमुख्यs(false, rd);
		वापस 0;
	पूर्ण

	पूर्णांकersected_rd = regकरोm_पूर्णांकersect(rd, get_cfg80211_regकरोm());
	अगर (!पूर्णांकersected_rd)
		वापस -EINVAL;

	kमुक्त(rd);
	rd = शून्य;
	reset_regकरोमुख्यs(false, पूर्णांकersected_rd);

	वापस 0;
पूर्ण

अटल पूर्णांक reg_set_rd_driver(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd,
			     काष्ठा regulatory_request *driver_request)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *पूर्णांकersected_rd = शून्य;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *पंचांगp;
	काष्ठा wiphy *request_wiphy;

	अगर (is_world_regकरोm(rd->alpha2))
		वापस -EINVAL;

	अगर (!regकरोm_changes(rd->alpha2))
		वापस -EALREADY;

	अगर (!is_valid_rd(rd)) अणु
		pr_err("Invalid regulatory domain detected: %c%c\n",
		       rd->alpha2[0], rd->alpha2[1]);
		prपूर्णांक_regकरोमुख्य_info(rd);
		वापस -EINVAL;
	पूर्ण

	request_wiphy = wiphy_idx_to_wiphy(driver_request->wiphy_idx);
	अगर (!request_wiphy)
		वापस -ENODEV;

	अगर (!driver_request->पूर्णांकersect) अणु
		ASSERT_RTNL();
		wiphy_lock(request_wiphy);
		अगर (request_wiphy->regd) अणु
			wiphy_unlock(request_wiphy);
			वापस -EALREADY;
		पूर्ण

		regd = reg_copy_regd(rd);
		अगर (IS_ERR(regd)) अणु
			wiphy_unlock(request_wiphy);
			वापस PTR_ERR(regd);
		पूर्ण

		rcu_assign_poपूर्णांकer(request_wiphy->regd, regd);
		wiphy_unlock(request_wiphy);
		reset_regकरोमुख्यs(false, rd);
		वापस 0;
	पूर्ण

	पूर्णांकersected_rd = regकरोm_पूर्णांकersect(rd, get_cfg80211_regकरोm());
	अगर (!पूर्णांकersected_rd)
		वापस -EINVAL;

	/*
	 * We can trash what CRDA provided now.
	 * However अगर a driver requested this specअगरic regulatory
	 * करोमुख्य we keep it क्रम its निजी use
	 */
	पंचांगp = get_wiphy_regकरोm(request_wiphy);
	rcu_assign_poपूर्णांकer(request_wiphy->regd, rd);
	rcu_मुक्त_regकरोm(पंचांगp);

	rd = शून्य;

	reset_regकरोमुख्यs(false, पूर्णांकersected_rd);

	वापस 0;
पूर्ण

अटल पूर्णांक reg_set_rd_country_ie(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd,
				 काष्ठा regulatory_request *country_ie_request)
अणु
	काष्ठा wiphy *request_wiphy;

	अगर (!is_alpha2_set(rd->alpha2) && !is_an_alpha2(rd->alpha2) &&
	    !is_unknown_alpha2(rd->alpha2))
		वापस -EINVAL;

	/*
	 * Lets only bother proceeding on the same alpha2 अगर the current
	 * rd is non अटल (it means CRDA was present and was used last)
	 * and the pending request came in from a country IE
	 */

	अगर (!is_valid_rd(rd)) अणु
		pr_err("Invalid regulatory domain detected: %c%c\n",
		       rd->alpha2[0], rd->alpha2[1]);
		prपूर्णांक_regकरोमुख्य_info(rd);
		वापस -EINVAL;
	पूर्ण

	request_wiphy = wiphy_idx_to_wiphy(country_ie_request->wiphy_idx);
	अगर (!request_wiphy)
		वापस -ENODEV;

	अगर (country_ie_request->पूर्णांकersect)
		वापस -EINVAL;

	reset_regकरोमुख्यs(false, rd);
	वापस 0;
पूर्ण

/*
 * Use this call to set the current regulatory करोमुख्य. Conflicts with
 * multiple drivers can be ironed out later. Caller must've alपढ़ोy
 * kदो_स्मृति'd the rd काष्ठाure.
 */
पूर्णांक set_regकरोm(स्थिर काष्ठा ieee80211_regकरोमुख्य *rd,
	       क्रमागत ieee80211_regd_source regd_src)
अणु
	काष्ठा regulatory_request *lr;
	bool user_reset = false;
	पूर्णांक r;

	अगर (IS_ERR_OR_शून्य(rd))
		वापस -ENODATA;

	अगर (!reg_is_valid_request(rd->alpha2)) अणु
		kमुक्त(rd);
		वापस -EINVAL;
	पूर्ण

	अगर (regd_src == REGD_SOURCE_CRDA)
		reset_crda_समयouts();

	lr = get_last_request();

	/* Note that this करोesn't update the wiphys, this is करोne below */
	चयन (lr->initiator) अणु
	हाल NL80211_REGDOM_SET_BY_CORE:
		r = reg_set_rd_core(rd);
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_USER:
		cfg80211_save_user_regकरोm(rd);
		r = reg_set_rd_user(rd, lr);
		user_reset = true;
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_DRIVER:
		r = reg_set_rd_driver(rd, lr);
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_COUNTRY_IE:
		r = reg_set_rd_country_ie(rd, lr);
		अवरोध;
	शेष:
		WARN(1, "invalid initiator %d\n", lr->initiator);
		kमुक्त(rd);
		वापस -EINVAL;
	पूर्ण

	अगर (r) अणु
		चयन (r) अणु
		हाल -EALREADY:
			reg_set_request_processed();
			अवरोध;
		शेष:
			/* Back to world regulatory in हाल of errors */
			restore_regulatory_settings(user_reset, false);
		पूर्ण

		kमुक्त(rd);
		वापस r;
	पूर्ण

	/* This would make this whole thing poपूर्णांकless */
	अगर (WARN_ON(!lr->पूर्णांकersect && rd != get_cfg80211_regकरोm()))
		वापस -EINVAL;

	/* update all wiphys now with the new established regulatory करोमुख्य */
	update_all_wiphy_regulatory(lr->initiator);

	prपूर्णांक_regकरोमुख्य(get_cfg80211_regकरोm());

	nl80211_send_reg_change_event(lr);

	reg_set_request_processed();

	वापस 0;
पूर्ण

अटल पूर्णांक __regulatory_set_wiphy_regd(काष्ठा wiphy *wiphy,
				       काष्ठा ieee80211_regकरोमुख्य *rd)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *prev_regd;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	अगर (WARN_ON(!wiphy || !rd))
		वापस -EINVAL;

	अगर (WARN(!(wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED),
		 "wiphy should have REGULATORY_WIPHY_SELF_MANAGED\n"))
		वापस -EPERM;

	अगर (WARN(!is_valid_rd(rd), "Invalid regulatory domain detected\n")) अणु
		prपूर्णांक_regकरोमुख्य_info(rd);
		वापस -EINVAL;
	पूर्ण

	regd = reg_copy_regd(rd);
	अगर (IS_ERR(regd))
		वापस PTR_ERR(regd);

	rdev = wiphy_to_rdev(wiphy);

	spin_lock(&reg_requests_lock);
	prev_regd = rdev->requested_regd;
	rdev->requested_regd = regd;
	spin_unlock(&reg_requests_lock);

	kमुक्त(prev_regd);
	वापस 0;
पूर्ण

पूर्णांक regulatory_set_wiphy_regd(काष्ठा wiphy *wiphy,
			      काष्ठा ieee80211_regकरोमुख्य *rd)
अणु
	पूर्णांक ret = __regulatory_set_wiphy_regd(wiphy, rd);

	अगर (ret)
		वापस ret;

	schedule_work(&reg_work);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(regulatory_set_wiphy_regd);

पूर्णांक regulatory_set_wiphy_regd_sync(काष्ठा wiphy *wiphy,
				   काष्ठा ieee80211_regकरोमुख्य *rd)
अणु
	पूर्णांक ret;

	ASSERT_RTNL();

	ret = __regulatory_set_wiphy_regd(wiphy, rd);
	अगर (ret)
		वापस ret;

	/* process the request immediately */
	reg_process_self_managed_hपूर्णांक(wiphy);
	reg_check_channels();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(regulatory_set_wiphy_regd_sync);

व्योम wiphy_regulatory_रेजिस्टर(काष्ठा wiphy *wiphy)
अणु
	काष्ठा regulatory_request *lr = get_last_request();

	/* self-managed devices ignore beacon hपूर्णांकs and country IE */
	अगर (wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED) अणु
		wiphy->regulatory_flags |= REGULATORY_DISABLE_BEACON_HINTS |
					   REGULATORY_COUNTRY_IE_IGNORE;

		/*
		 * The last request may have been received beक्रमe this
		 * registration call. Call the driver notअगरier अगर
		 * initiator is USER.
		 */
		अगर (lr->initiator == NL80211_REGDOM_SET_BY_USER)
			reg_call_notअगरier(wiphy, lr);
	पूर्ण

	अगर (!reg_dev_ignore_cell_hपूर्णांक(wiphy))
		reg_num_devs_support_basehपूर्णांक++;

	wiphy_update_regulatory(wiphy, lr->initiator);
	wiphy_all_share_dfs_chan_state(wiphy);
पूर्ण

व्योम wiphy_regulatory_deरेजिस्टर(काष्ठा wiphy *wiphy)
अणु
	काष्ठा wiphy *request_wiphy = शून्य;
	काष्ठा regulatory_request *lr;

	lr = get_last_request();

	अगर (!reg_dev_ignore_cell_hपूर्णांक(wiphy))
		reg_num_devs_support_basehपूर्णांक--;

	rcu_मुक्त_regकरोm(get_wiphy_regकरोm(wiphy));
	RCU_INIT_POINTER(wiphy->regd, शून्य);

	अगर (lr)
		request_wiphy = wiphy_idx_to_wiphy(lr->wiphy_idx);

	अगर (!request_wiphy || request_wiphy != wiphy)
		वापस;

	lr->wiphy_idx = WIPHY_IDX_INVALID;
	lr->country_ie_env = ENVIRON_ANY;
पूर्ण

/*
 * See FCC notices क्रम UNII band definitions
 *  5GHz: https://www.fcc.gov/करोcument/5-ghz-unlicensed-spectrum-unii
 *  6GHz: https://www.fcc.gov/करोcument/fcc-proposes-more-spectrum-unlicensed-use-0
 */
पूर्णांक cfg80211_get_unii(पूर्णांक freq)
अणु
	/* UNII-1 */
	अगर (freq >= 5150 && freq <= 5250)
		वापस 0;

	/* UNII-2A */
	अगर (freq > 5250 && freq <= 5350)
		वापस 1;

	/* UNII-2B */
	अगर (freq > 5350 && freq <= 5470)
		वापस 2;

	/* UNII-2C */
	अगर (freq > 5470 && freq <= 5725)
		वापस 3;

	/* UNII-3 */
	अगर (freq > 5725 && freq <= 5825)
		वापस 4;

	/* UNII-5 */
	अगर (freq > 5925 && freq <= 6425)
		वापस 5;

	/* UNII-6 */
	अगर (freq > 6425 && freq <= 6525)
		वापस 6;

	/* UNII-7 */
	अगर (freq > 6525 && freq <= 6875)
		वापस 7;

	/* UNII-8 */
	अगर (freq > 6875 && freq <= 7125)
		वापस 8;

	वापस -EINVAL;
पूर्ण

bool regulatory_inकरोor_allowed(व्योम)
अणु
	वापस reg_is_inकरोor;
पूर्ण

bool regulatory_pre_cac_allowed(काष्ठा wiphy *wiphy)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd = शून्य;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *wiphy_regd = शून्य;
	bool pre_cac_allowed = false;

	rcu_पढ़ो_lock();

	regd = rcu_dereference(cfg80211_regकरोमुख्य);
	wiphy_regd = rcu_dereference(wiphy->regd);
	अगर (!wiphy_regd) अणु
		अगर (regd->dfs_region == NL80211_DFS_ETSI)
			pre_cac_allowed = true;

		rcu_पढ़ो_unlock();

		वापस pre_cac_allowed;
	पूर्ण

	अगर (regd->dfs_region == wiphy_regd->dfs_region &&
	    wiphy_regd->dfs_region == NL80211_DFS_ETSI)
		pre_cac_allowed = true;

	rcu_पढ़ो_unlock();

	वापस pre_cac_allowed;
पूर्ण
EXPORT_SYMBOL(regulatory_pre_cac_allowed);

अटल व्योम cfg80211_check_and_end_cac(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा wireless_dev *wdev;
	/* If we finished CAC or received radar, we should end any
	 * CAC running on the same channels.
	 * the check !cfg80211_chandef_dfs_usable contain 2 options:
	 * either all channels are available - those the CAC_FINISHED
	 * event has effected another wdev state, or there is a channel
	 * in unavailable state in wdev chandef - those the RADAR_DETECTED
	 * event has effected another wdev state.
	 * In both हालs we should end the CAC on the wdev.
	 */
	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
		अगर (wdev->cac_started &&
		    !cfg80211_chandef_dfs_usable(&rdev->wiphy, &wdev->chandef))
			rdev_end_cac(rdev, wdev->netdev);
	पूर्ण
पूर्ण

व्योम regulatory_propagate_dfs_state(काष्ठा wiphy *wiphy,
				    काष्ठा cfg80211_chan_def *chandef,
				    क्रमागत nl80211_dfs_state dfs_state,
				    क्रमागत nl80211_radar_event event)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	ASSERT_RTNL();

	अगर (WARN_ON(!cfg80211_chandef_valid(chandef)))
		वापस;

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		अगर (wiphy == &rdev->wiphy)
			जारी;

		अगर (!reg_dfs_करोमुख्य_same(wiphy, &rdev->wiphy))
			जारी;

		अगर (!ieee80211_get_channel(&rdev->wiphy,
					   chandef->chan->center_freq))
			जारी;

		cfg80211_set_dfs_state(&rdev->wiphy, chandef, dfs_state);

		अगर (event == NL80211_RADAR_DETECTED ||
		    event == NL80211_RADAR_CAC_FINISHED) अणु
			cfg80211_sched_dfs_chan_update(rdev);
			cfg80211_check_and_end_cac(rdev);
		पूर्ण

		nl80211_radar_notअगरy(rdev, chandef, event, शून्य, GFP_KERNEL);
	पूर्ण
पूर्ण

अटल पूर्णांक __init regulatory_init_db(व्योम)
अणु
	पूर्णांक err;

	/*
	 * It's possible that - due to other bugs/issues - cfg80211
	 * never called regulatory_init() below, or that it failed;
	 * in that हाल, करोn't try to करो any further work here as
	 * it's करोomed to lead to crashes.
	 */
	अगर (IS_ERR_OR_शून्य(reg_pdev))
		वापस -EINVAL;

	err = load_builtin_regdb_keys();
	अगर (err)
		वापस err;

	/* We always try to get an update क्रम the अटल regकरोमुख्य */
	err = regulatory_hपूर्णांक_core(cfg80211_world_regकरोm->alpha2);
	अगर (err) अणु
		अगर (err == -ENOMEM) अणु
			platक्रमm_device_unरेजिस्टर(reg_pdev);
			वापस err;
		पूर्ण
		/*
		 * N.B. kobject_uevent_env() can fail मुख्यly क्रम when we're out
		 * memory which is handled and propagated appropriately above
		 * but it can also fail during a netlink_broadcast() or during
		 * early boot क्रम call_usermodehelper(). For now treat these
		 * errors as non-fatal.
		 */
		pr_err("kobject_uevent_env() was unable to call CRDA during init\n");
	पूर्ण

	/*
	 * Finally, अगर the user set the module parameter treat it
	 * as a user hपूर्णांक.
	 */
	अगर (!is_world_regकरोm(ieee80211_regकरोm))
		regulatory_hपूर्णांक_user(ieee80211_regकरोm,
				     NL80211_USER_REG_HINT_USER);

	वापस 0;
पूर्ण
#अगर_अघोषित MODULE
late_initcall(regulatory_init_db);
#पूर्ण_अगर

पूर्णांक __init regulatory_init(व्योम)
अणु
	reg_pdev = platक्रमm_device_रेजिस्टर_simple("regulatory", 0, शून्य, 0);
	अगर (IS_ERR(reg_pdev))
		वापस PTR_ERR(reg_pdev);

	rcu_assign_poपूर्णांकer(cfg80211_regकरोमुख्य, cfg80211_world_regकरोm);

	user_alpha2[0] = '9';
	user_alpha2[1] = '7';

#अगर_घोषित MODULE
	वापस regulatory_init_db();
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

व्योम regulatory_निकास(व्योम)
अणु
	काष्ठा regulatory_request *reg_request, *पंचांगp;
	काष्ठा reg_beacon *reg_beacon, *bपंचांगp;

	cancel_work_sync(&reg_work);
	cancel_crda_समयout_sync();
	cancel_delayed_work_sync(&reg_check_chans);

	/* Lock to suppress warnings */
	rtnl_lock();
	reset_regकरोमुख्यs(true, शून्य);
	rtnl_unlock();

	dev_set_uevent_suppress(&reg_pdev->dev, true);

	platक्रमm_device_unरेजिस्टर(reg_pdev);

	list_क्रम_each_entry_safe(reg_beacon, bपंचांगp, &reg_pending_beacons, list) अणु
		list_del(&reg_beacon->list);
		kमुक्त(reg_beacon);
	पूर्ण

	list_क्रम_each_entry_safe(reg_beacon, bपंचांगp, &reg_beacon_list, list) अणु
		list_del(&reg_beacon->list);
		kमुक्त(reg_beacon);
	पूर्ण

	list_क्रम_each_entry_safe(reg_request, पंचांगp, &reg_requests_list, list) अणु
		list_del(&reg_request->list);
		kमुक्त(reg_request);
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(regdb))
		kमुक्त(regdb);
	अगर (!IS_ERR_OR_शून्य(cfg80211_user_regकरोm))
		kमुक्त(cfg80211_user_regकरोm);

	मुक्त_regdb_keyring();
पूर्ण
