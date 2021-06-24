<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Mellanox Technologies. All rights reserved */

#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "netdevsim.h"

अटल पूर्णांक
nsim_dev_empty_reporter_dump(काष्ठा devlink_health_reporter *reporter,
			     काष्ठा devlink_fmsg *fmsg, व्योम *priv_ctx,
			     काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
nsim_dev_empty_reporter_diagnose(काष्ठा devlink_health_reporter *reporter,
				 काष्ठा devlink_fmsg *fmsg,
				 काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल स्थिर
काष्ठा devlink_health_reporter_ops nsim_dev_empty_reporter_ops = अणु
	.name = "empty",
	.dump = nsim_dev_empty_reporter_dump,
	.diagnose = nsim_dev_empty_reporter_diagnose,
पूर्ण;

काष्ठा nsim_dev_dummy_reporter_ctx अणु
	अक्षर *अवरोध_msg;
पूर्ण;

अटल पूर्णांक
nsim_dev_dummy_reporter_recover(काष्ठा devlink_health_reporter *reporter,
				व्योम *priv_ctx,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nsim_dev_health *health = devlink_health_reporter_priv(reporter);
	काष्ठा nsim_dev_dummy_reporter_ctx *ctx = priv_ctx;

	अगर (health->fail_recover) अणु
		/* For testing purposes, user set debugfs fail_recover
		 * value to true. Fail right away.
		 */
		NL_SET_ERR_MSG_MOD(extack, "User setup the recover to fail for testing purposes");
		वापस -EINVAL;
	पूर्ण
	अगर (ctx) अणु
		kमुक्त(health->recovered_अवरोध_msg);
		health->recovered_अवरोध_msg = kstrdup(ctx->अवरोध_msg,
						      GFP_KERNEL);
		अगर (!health->recovered_अवरोध_msg)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nsim_dev_dummy_fmsg_put(काष्ठा devlink_fmsg *fmsg, u32 binary_len)
अणु
	अक्षर *binary;
	पूर्णांक err;
	पूर्णांक i;

	err = devlink_fmsg_bool_pair_put(fmsg, "test_bool", true);
	अगर (err)
		वापस err;
	err = devlink_fmsg_u8_pair_put(fmsg, "test_u8", 1);
	अगर (err)
		वापस err;
	err = devlink_fmsg_u32_pair_put(fmsg, "test_u32", 3);
	अगर (err)
		वापस err;
	err = devlink_fmsg_u64_pair_put(fmsg, "test_u64", 4);
	अगर (err)
		वापस err;
	err = devlink_fmsg_string_pair_put(fmsg, "test_string", "somestring");
	अगर (err)
		वापस err;

	binary = kदो_स्मृति(binary_len, GFP_KERNEL | __GFP_NOWARN);
	अगर (!binary)
		वापस -ENOMEM;
	get_अक्रमom_bytes(binary, binary_len);
	err = devlink_fmsg_binary_pair_put(fmsg, "test_binary", binary, binary_len);
	kमुक्त(binary);
	अगर (err)
		वापस err;

	err = devlink_fmsg_pair_nest_start(fmsg, "test_nest");
	अगर (err)
		वापस err;
	err = devlink_fmsg_obj_nest_start(fmsg);
	अगर (err)
		वापस err;
	err = devlink_fmsg_bool_pair_put(fmsg, "nested_test_bool", false);
	अगर (err)
		वापस err;
	err = devlink_fmsg_u8_pair_put(fmsg, "nested_test_u8", false);
	अगर (err)
		वापस err;
	err = devlink_fmsg_obj_nest_end(fmsg);
	अगर (err)
		वापस err;
	err = devlink_fmsg_pair_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "test_bool_array");
	अगर (err)
		वापस err;
	क्रम (i = 0; i < 10; i++) अणु
		err = devlink_fmsg_bool_put(fmsg, true);
		अगर (err)
			वापस err;
	पूर्ण
	err = devlink_fmsg_arr_pair_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "test_u8_array");
	अगर (err)
		वापस err;
	क्रम (i = 0; i < 10; i++) अणु
		err = devlink_fmsg_u8_put(fmsg, i);
		अगर (err)
			वापस err;
	पूर्ण
	err = devlink_fmsg_arr_pair_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "test_u32_array");
	अगर (err)
		वापस err;
	क्रम (i = 0; i < 10; i++) अणु
		err = devlink_fmsg_u32_put(fmsg, i);
		अगर (err)
			वापस err;
	पूर्ण
	err = devlink_fmsg_arr_pair_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "test_u64_array");
	अगर (err)
		वापस err;
	क्रम (i = 0; i < 10; i++) अणु
		err = devlink_fmsg_u64_put(fmsg, i);
		अगर (err)
			वापस err;
	पूर्ण
	err = devlink_fmsg_arr_pair_nest_end(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "test_array_of_objects");
	अगर (err)
		वापस err;
	क्रम (i = 0; i < 10; i++) अणु
		err = devlink_fmsg_obj_nest_start(fmsg);
		अगर (err)
			वापस err;
		err = devlink_fmsg_bool_pair_put(fmsg,
						 "in_array_nested_test_bool",
						 false);
		अगर (err)
			वापस err;
		err = devlink_fmsg_u8_pair_put(fmsg,
					       "in_array_nested_test_u8",
					       i);
		अगर (err)
			वापस err;
		err = devlink_fmsg_obj_nest_end(fmsg);
		अगर (err)
			वापस err;
	पूर्ण
	वापस devlink_fmsg_arr_pair_nest_end(fmsg);
पूर्ण

अटल पूर्णांक
nsim_dev_dummy_reporter_dump(काष्ठा devlink_health_reporter *reporter,
			     काष्ठा devlink_fmsg *fmsg, व्योम *priv_ctx,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nsim_dev_health *health = devlink_health_reporter_priv(reporter);
	काष्ठा nsim_dev_dummy_reporter_ctx *ctx = priv_ctx;
	पूर्णांक err;

	अगर (ctx) अणु
		err = devlink_fmsg_string_pair_put(fmsg, "break_message",
						   ctx->अवरोध_msg);
		अगर (err)
			वापस err;
	पूर्ण
	वापस nsim_dev_dummy_fmsg_put(fmsg, health->binary_len);
पूर्ण

अटल पूर्णांक
nsim_dev_dummy_reporter_diagnose(काष्ठा devlink_health_reporter *reporter,
				 काष्ठा devlink_fmsg *fmsg,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nsim_dev_health *health = devlink_health_reporter_priv(reporter);
	पूर्णांक err;

	अगर (health->recovered_अवरोध_msg) अणु
		err = devlink_fmsg_string_pair_put(fmsg,
						   "recovered_break_message",
						   health->recovered_अवरोध_msg);
		अगर (err)
			वापस err;
	पूर्ण
	वापस nsim_dev_dummy_fmsg_put(fmsg, health->binary_len);
पूर्ण

अटल स्थिर
काष्ठा devlink_health_reporter_ops nsim_dev_dummy_reporter_ops = अणु
	.name = "dummy",
	.recover = nsim_dev_dummy_reporter_recover,
	.dump = nsim_dev_dummy_reporter_dump,
	.diagnose = nsim_dev_dummy_reporter_diagnose,
पूर्ण;

अटल sमाप_प्रकार nsim_dev_health_अवरोध_ग_लिखो(काष्ठा file *file,
					   स्थिर अक्षर __user *data,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा nsim_dev_health *health = file->निजी_data;
	काष्ठा nsim_dev_dummy_reporter_ctx ctx;
	अक्षर *अवरोध_msg;
	पूर्णांक err;

	अवरोध_msg = memdup_user_nul(data, count);
	अगर (IS_ERR(अवरोध_msg))
		वापस PTR_ERR(अवरोध_msg);

	अगर (अवरोध_msg[count - 1] == '\n')
		अवरोध_msg[count - 1] = '\0';

	ctx.अवरोध_msg = अवरोध_msg;
	err = devlink_health_report(health->dummy_reporter, अवरोध_msg, &ctx);
	अगर (err)
		जाओ out;

out:
	kमुक्त(अवरोध_msg);
	वापस err ?: count;
पूर्ण

अटल स्थिर काष्ठा file_operations nsim_dev_health_अवरोध_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = nsim_dev_health_अवरोध_ग_लिखो,
	.llseek = generic_file_llseek,
	.owner = THIS_MODULE,
पूर्ण;

पूर्णांक nsim_dev_health_init(काष्ठा nsim_dev *nsim_dev, काष्ठा devlink *devlink)
अणु
	काष्ठा nsim_dev_health *health = &nsim_dev->health;
	पूर्णांक err;

	health->empty_reporter =
		devlink_health_reporter_create(devlink,
					       &nsim_dev_empty_reporter_ops,
					       0, health);
	अगर (IS_ERR(health->empty_reporter))
		वापस PTR_ERR(health->empty_reporter);

	health->dummy_reporter =
		devlink_health_reporter_create(devlink,
					       &nsim_dev_dummy_reporter_ops,
					       0, health);
	अगर (IS_ERR(health->dummy_reporter)) अणु
		err = PTR_ERR(health->dummy_reporter);
		जाओ err_empty_reporter_destroy;
	पूर्ण

	health->ddir = debugfs_create_dir("health", nsim_dev->ddir);
	अगर (IS_ERR(health->ddir)) अणु
		err = PTR_ERR(health->ddir);
		जाओ err_dummy_reporter_destroy;
	पूर्ण

	health->recovered_अवरोध_msg = शून्य;
	debugfs_create_file("break_health", 0200, health->ddir, health,
			    &nsim_dev_health_अवरोध_fops);
	health->binary_len = 16;
	debugfs_create_u32("binary_len", 0600, health->ddir,
			   &health->binary_len);
	health->fail_recover = false;
	debugfs_create_bool("fail_recover", 0600, health->ddir,
			    &health->fail_recover);
	वापस 0;

err_dummy_reporter_destroy:
	devlink_health_reporter_destroy(health->dummy_reporter);
err_empty_reporter_destroy:
	devlink_health_reporter_destroy(health->empty_reporter);
	वापस err;
पूर्ण

व्योम nsim_dev_health_निकास(काष्ठा nsim_dev *nsim_dev)
अणु
	काष्ठा nsim_dev_health *health = &nsim_dev->health;

	debugfs_हटाओ_recursive(health->ddir);
	kमुक्त(health->recovered_अवरोध_msg);
	devlink_health_reporter_destroy(health->dummy_reporter);
	devlink_health_reporter_destroy(health->empty_reporter);
पूर्ण
