<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Mellanox boot control driver
 *
 * This driver provides a sysfs पूर्णांकerface क्रम प्रणालीs management
 * software to manage reset-समय actions.
 *
 * Copyright (C) 2019 Mellanox Technologies
 */

#समावेश <linux/acpi.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "mlxbf-bootctl.h"

#घोषणा MLXBF_BOOTCTL_SB_SECURE_MASK		0x03
#घोषणा MLXBF_BOOTCTL_SB_TEST_MASK		0x0c

#घोषणा MLXBF_SB_KEY_NUM			4

/* UUID used to probe ATF service. */
अटल स्थिर अक्षर *mlxbf_bootctl_svc_uuid_str =
	"89c036b4-e7d7-11e6-8797-001aca00bfc4";

काष्ठा mlxbf_bootctl_name अणु
	u32 value;
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा mlxbf_bootctl_name boot_names[] = अणु
	अणु MLXBF_BOOTCTL_EXTERNAL, "external" पूर्ण,
	अणु MLXBF_BOOTCTL_EMMC, "emmc" पूर्ण,
	अणु MLNX_BOOTCTL_SWAP_EMMC, "swap_emmc" पूर्ण,
	अणु MLXBF_BOOTCTL_EMMC_LEGACY, "emmc_legacy" पूर्ण,
	अणु MLXBF_BOOTCTL_NONE, "none" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mlxbf_bootctl_lअगरecycle_states[] = अणु
	[0] = "Production",
	[1] = "GA Secured",
	[2] = "GA Non-Secured",
	[3] = "RMA",
पूर्ण;

/* ARM SMC call which is atomic and no need क्रम lock. */
अटल पूर्णांक mlxbf_bootctl_smc(अचिन्हित पूर्णांक smc_op, पूर्णांक smc_arg)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(smc_op, smc_arg, 0, 0, 0, 0, 0, 0, &res);

	वापस res.a0;
पूर्ण

/* Return the action in पूर्णांकeger or an error code. */
अटल पूर्णांक mlxbf_bootctl_reset_action_to_val(स्थिर अक्षर *action)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(boot_names); i++)
		अगर (sysfs_streq(boot_names[i].name, action))
			वापस boot_names[i].value;

	वापस -EINVAL;
पूर्ण

/* Return the action in string. */
अटल स्थिर अक्षर *mlxbf_bootctl_action_to_string(पूर्णांक action)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(boot_names); i++)
		अगर (boot_names[i].value == action)
			वापस boot_names[i].name;

	वापस "invalid action";
पूर्ण

अटल sमाप_प्रकार post_reset_wकरोg_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;

	ret = mlxbf_bootctl_smc(MLXBF_BOOTCTL_GET_POST_RESET_WDOG, 0);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

अटल sमाप_प्रकार post_reset_wकरोg_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &value);
	अगर (ret)
		वापस ret;

	ret = mlxbf_bootctl_smc(MLXBF_BOOTCTL_SET_POST_RESET_WDOG, value);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार mlxbf_bootctl_show(पूर्णांक smc_op, अक्षर *buf)
अणु
	पूर्णांक action;

	action = mlxbf_bootctl_smc(smc_op, 0);
	अगर (action < 0)
		वापस action;

	वापस प्र_लिखो(buf, "%s\n", mlxbf_bootctl_action_to_string(action));
पूर्ण

अटल पूर्णांक mlxbf_bootctl_store(पूर्णांक smc_op, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret, action;

	action = mlxbf_bootctl_reset_action_to_val(buf);
	अगर (action < 0)
		वापस action;

	ret = mlxbf_bootctl_smc(smc_op, action);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार reset_action_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस mlxbf_bootctl_show(MLXBF_BOOTCTL_GET_RESET_ACTION, buf);
पूर्ण

अटल sमाप_प्रकार reset_action_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस mlxbf_bootctl_store(MLXBF_BOOTCTL_SET_RESET_ACTION, buf, count);
पूर्ण

अटल sमाप_प्रकार second_reset_action_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	वापस mlxbf_bootctl_show(MLXBF_BOOTCTL_GET_SECOND_RESET_ACTION, buf);
पूर्ण

अटल sमाप_प्रकार second_reset_action_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस mlxbf_bootctl_store(MLXBF_BOOTCTL_SET_SECOND_RESET_ACTION, buf,
				   count);
पूर्ण

अटल sमाप_प्रकार lअगरecycle_state_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक lc_state;

	lc_state = mlxbf_bootctl_smc(MLXBF_BOOTCTL_GET_TBB_FUSE_STATUS,
				     MLXBF_BOOTCTL_FUSE_STATUS_LIFECYCLE);
	अगर (lc_state < 0)
		वापस lc_state;

	lc_state &=
		MLXBF_BOOTCTL_SB_TEST_MASK | MLXBF_BOOTCTL_SB_SECURE_MASK;

	/*
	 * If the test bits are set, we specअगरy that the current state may be
	 * due to using the test bits.
	 */
	अगर (lc_state & MLXBF_BOOTCTL_SB_TEST_MASK) अणु
		lc_state &= MLXBF_BOOTCTL_SB_SECURE_MASK;

		वापस प्र_लिखो(buf, "%s(test)\n",
			       mlxbf_bootctl_lअगरecycle_states[lc_state]);
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", mlxbf_bootctl_lअगरecycle_states[lc_state]);
पूर्ण

अटल sमाप_प्रकार secure_boot_fuse_state_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	पूर्णांक burnt, valid, key, key_state, buf_len = 0, upper_key_used = 0;
	स्थिर अक्षर *status;

	key_state = mlxbf_bootctl_smc(MLXBF_BOOTCTL_GET_TBB_FUSE_STATUS,
				      MLXBF_BOOTCTL_FUSE_STATUS_KEYS);
	अगर (key_state < 0)
		वापस key_state;

	/*
	 * key_state contains the bits क्रम 4 Key versions, loaded from eFuses
	 * after a hard reset. Lower 4 bits are a thermometer code indicating
	 * key programming has started क्रम key n (0000 = none, 0001 = version 0,
	 * 0011 = version 1, 0111 = version 2, 1111 = version 3). Upper 4 bits
	 * are a thermometer code indicating key programming has completed क्रम
	 * key n (same encodings as the start bits). This allows क्रम detection
	 * of an पूर्णांकerruption in the programming process which has left the key
	 * partially programmed (and thus invalid). The process is to burn the
	 * eFuse क्रम the new key start bit, burn the key eFuses, then burn the
	 * eFuse क्रम the new key complete bit.
	 *
	 * For example 0000_0000: no key valid, 0001_0001: key version 0 valid,
	 * 0011_0011: key 1 version valid, 0011_0111: key version 2 started
	 * programming but did not complete, etc. The most recent key क्रम which
	 * both start and complete bit is set is loaded. On soft reset, this
	 * रेजिस्टर is not modअगरied.
	 */
	क्रम (key = MLXBF_SB_KEY_NUM - 1; key >= 0; key--) अणु
		burnt = key_state & BIT(key);
		valid = key_state & BIT(key + MLXBF_SB_KEY_NUM);

		अगर (burnt && valid)
			upper_key_used = 1;

		अगर (upper_key_used) अणु
			अगर (burnt)
				status = valid ? "Used" : "Wasted";
			अन्यथा
				status = valid ? "Invalid" : "Skipped";
		पूर्ण अन्यथा अणु
			अगर (burnt)
				status = valid ? "InUse" : "Incomplete";
			अन्यथा
				status = valid ? "Invalid" : "Free";
		पूर्ण
		buf_len += प्र_लिखो(buf + buf_len, "%d:%s ", key, status);
	पूर्ण
	buf_len += प्र_लिखो(buf + buf_len, "\n");

	वापस buf_len;
पूर्ण

अटल DEVICE_ATTR_RW(post_reset_wकरोg);
अटल DEVICE_ATTR_RW(reset_action);
अटल DEVICE_ATTR_RW(second_reset_action);
अटल DEVICE_ATTR_RO(lअगरecycle_state);
अटल DEVICE_ATTR_RO(secure_boot_fuse_state);

अटल काष्ठा attribute *mlxbf_bootctl_attrs[] = अणु
	&dev_attr_post_reset_wकरोg.attr,
	&dev_attr_reset_action.attr,
	&dev_attr_second_reset_action.attr,
	&dev_attr_lअगरecycle_state.attr,
	&dev_attr_secure_boot_fuse_state.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(mlxbf_bootctl);

अटल स्थिर काष्ठा acpi_device_id mlxbf_bootctl_acpi_ids[] = अणु
	अणु"MLNXBF04", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, mlxbf_bootctl_acpi_ids);

अटल bool mlxbf_bootctl_guid_match(स्थिर guid_t *guid,
				     स्थिर काष्ठा arm_smccc_res *res)
अणु
	guid_t id = GUID_INIT(res->a0, res->a1, res->a1 >> 16,
			      res->a2, res->a2 >> 8, res->a2 >> 16,
			      res->a2 >> 24, res->a3, res->a3 >> 8,
			      res->a3 >> 16, res->a3 >> 24);

	वापस guid_equal(guid, &id);
पूर्ण

अटल पूर्णांक mlxbf_bootctl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arm_smccc_res res = अणु 0 पूर्ण;
	guid_t guid;
	पूर्णांक ret;

	/* Ensure we have the UUID we expect क्रम this service. */
	arm_smccc_smc(MLXBF_BOOTCTL_SIP_SVC_UID, 0, 0, 0, 0, 0, 0, 0, &res);
	guid_parse(mlxbf_bootctl_svc_uuid_str, &guid);
	अगर (!mlxbf_bootctl_guid_match(&guid, &res))
		वापस -ENODEV;

	/*
	 * When watchकरोg is used, it sets boot mode to MLXBF_BOOTCTL_SWAP_EMMC
	 * in हाल of boot failures. However it करोesn't clear the state अगर there
	 * is no failure. Restore the शेष boot mode here to aव्योम any
	 * unnecessary boot partition swapping.
	 */
	ret = mlxbf_bootctl_smc(MLXBF_BOOTCTL_SET_RESET_ACTION,
				MLXBF_BOOTCTL_EMMC);
	अगर (ret < 0)
		dev_warn(&pdev->dev, "Unable to reset the EMMC boot mode\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mlxbf_bootctl_driver = अणु
	.probe = mlxbf_bootctl_probe,
	.driver = अणु
		.name = "mlxbf-bootctl",
		.dev_groups = mlxbf_bootctl_groups,
		.acpi_match_table = mlxbf_bootctl_acpi_ids,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(mlxbf_bootctl_driver);

MODULE_DESCRIPTION("Mellanox boot control driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Mellanox Technologies");
