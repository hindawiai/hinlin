<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Authors:
 *   Bअक्रमen Bonaby <bअक्रमonbonaby94@gmail.com>
 */

#समावेश <linux/hyperv.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>

#समावेश "hyperv_vmbus.h"

अटल काष्ठा dentry *hv_debug_root;

अटल पूर्णांक hv_debugfs_delay_get(व्योम *data, u64 *val)
अणु
	*val = *(u32 *)data;
	वापस 0;
पूर्ण

अटल पूर्णांक hv_debugfs_delay_set(व्योम *data, u64 val)
अणु
	अगर (val > 1000)
		वापस -EINVAL;
	*(u32 *)data = val;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(hv_debugfs_delay_fops, hv_debugfs_delay_get,
			 hv_debugfs_delay_set, "%llu\n");

अटल पूर्णांक hv_debugfs_state_get(व्योम *data, u64 *val)
अणु
	*val = *(bool *)data;
	वापस 0;
पूर्ण

अटल पूर्णांक hv_debugfs_state_set(व्योम *data, u64 val)
अणु
	अगर (val == 1)
		*(bool *)data = true;
	अन्यथा अगर (val == 0)
		*(bool *)data = false;
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(hv_debugfs_state_fops, hv_debugfs_state_get,
			 hv_debugfs_state_set, "%llu\n");

/* Setup delay files to store test values */
अटल पूर्णांक hv_debug_delay_files(काष्ठा hv_device *dev, काष्ठा dentry *root)
अणु
	काष्ठा vmbus_channel *channel = dev->channel;
	अक्षर *buffer = "fuzz_test_buffer_interrupt_delay";
	अक्षर *message = "fuzz_test_message_delay";
	पूर्णांक *buffer_val = &channel->fuzz_testing_पूर्णांकerrupt_delay;
	पूर्णांक *message_val = &channel->fuzz_testing_message_delay;
	काष्ठा dentry *buffer_file, *message_file;

	buffer_file = debugfs_create_file(buffer, 0644, root,
					  buffer_val,
					  &hv_debugfs_delay_fops);
	अगर (IS_ERR(buffer_file)) अणु
		pr_debug("debugfs_hyperv: file %s not created\n", buffer);
		वापस PTR_ERR(buffer_file);
	पूर्ण

	message_file = debugfs_create_file(message, 0644, root,
					   message_val,
					   &hv_debugfs_delay_fops);
	अगर (IS_ERR(message_file)) अणु
		pr_debug("debugfs_hyperv: file %s not created\n", message);
		वापस PTR_ERR(message_file);
	पूर्ण

	वापस 0;
पूर्ण

/* Setup test state value क्रम vmbus device */
अटल पूर्णांक hv_debug_set_test_state(काष्ठा hv_device *dev, काष्ठा dentry *root)
अणु
	काष्ठा vmbus_channel *channel = dev->channel;
	bool *state = &channel->fuzz_testing_state;
	अक्षर *status = "fuzz_test_state";
	काष्ठा dentry *test_state;

	test_state = debugfs_create_file(status, 0644, root,
					 state,
					 &hv_debugfs_state_fops);
	अगर (IS_ERR(test_state)) अणु
		pr_debug("debugfs_hyperv: file %s not created\n", status);
		वापस PTR_ERR(test_state);
	पूर्ण

	वापस 0;
पूर्ण

/* Bind hv device to a dentry क्रम debugfs */
अटल व्योम hv_debug_set_dir_dentry(काष्ठा hv_device *dev, काष्ठा dentry *root)
अणु
	अगर (hv_debug_root)
		dev->debug_dir = root;
पूर्ण

/* Create all test dentry's and names क्रम fuzz testing */
पूर्णांक hv_debug_add_dev_dir(काष्ठा hv_device *dev)
अणु
	स्थिर अक्षर *device = dev_name(&dev->device);
	अक्षर *delay_name = "delay";
	काष्ठा dentry *delay, *dev_root;
	पूर्णांक ret;

	अगर (!IS_ERR(hv_debug_root)) अणु
		dev_root = debugfs_create_dir(device, hv_debug_root);
		अगर (IS_ERR(dev_root)) अणु
			pr_debug("debugfs_hyperv: hyperv/%s/ not created\n",
				 device);
			वापस PTR_ERR(dev_root);
		पूर्ण
		hv_debug_set_test_state(dev, dev_root);
		hv_debug_set_dir_dentry(dev, dev_root);
		delay = debugfs_create_dir(delay_name, dev_root);

		अगर (IS_ERR(delay)) अणु
			pr_debug("debugfs_hyperv: hyperv/%s/%s/ not created\n",
				 device, delay_name);
			वापस PTR_ERR(delay);
		पूर्ण
		ret = hv_debug_delay_files(dev, delay);

		वापस ret;
	पूर्ण
	pr_debug("debugfs_hyperv: hyperv/ not in root debugfs path\n");
	वापस PTR_ERR(hv_debug_root);
पूर्ण

/* Remove dentry associated with released hv device */
व्योम hv_debug_rm_dev_dir(काष्ठा hv_device *dev)
अणु
	अगर (!IS_ERR(hv_debug_root))
		debugfs_हटाओ_recursive(dev->debug_dir);
पूर्ण

/* Remove all dentrys associated with vmbus testing */
व्योम hv_debug_rm_all_dir(व्योम)
अणु
	debugfs_हटाओ_recursive(hv_debug_root);
पूर्ण

/* Delay buffer/message पढ़ोs on a vmbus channel */
व्योम hv_debug_delay_test(काष्ठा vmbus_channel *channel, क्रमागत delay delay_type)
अणु
	काष्ठा vmbus_channel *test_channel =    channel->primary_channel ?
						channel->primary_channel :
						channel;
	bool state = test_channel->fuzz_testing_state;

	अगर (state) अणु
		अगर (delay_type == 0)
			udelay(test_channel->fuzz_testing_पूर्णांकerrupt_delay);
		अन्यथा
			udelay(test_channel->fuzz_testing_message_delay);
	पूर्ण
पूर्ण

/* Initialize top dentry क्रम vmbus testing */
पूर्णांक hv_debug_init(व्योम)
अणु
	hv_debug_root = debugfs_create_dir("hyperv", शून्य);
	अगर (IS_ERR(hv_debug_root)) अणु
		pr_debug("debugfs_hyperv: hyperv/ not created\n");
		वापस PTR_ERR(hv_debug_root);
	पूर्ण
	वापस 0;
पूर्ण
