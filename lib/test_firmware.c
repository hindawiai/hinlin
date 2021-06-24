<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This module provides an पूर्णांकerface to trigger and test firmware loading.
 *
 * It is deचिन्हित to be used क्रम basic evaluation of the firmware loading
 * subप्रणाली (क्रम example when validating firmware verअगरication). It lacks
 * any extra dependencies, and will not normally be loaded by the प्रणाली
 * unless explicitly requested by name.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/completion.h>
#समावेश <linux/firmware.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/efi_embedded_fw.h>

MODULE_IMPORT_NS(TEST_FIRMWARE);

#घोषणा TEST_FIRMWARE_NAME	"test-firmware.bin"
#घोषणा TEST_FIRMWARE_NUM_REQS	4
#घोषणा TEST_FIRMWARE_BUF_SIZE	SZ_1K

अटल DEFINE_MUTEX(test_fw_mutex);
अटल स्थिर काष्ठा firmware *test_firmware;

काष्ठा test_batched_req अणु
	u8 idx;
	पूर्णांक rc;
	bool sent;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *name;
	काष्ठा completion completion;
	काष्ठा task_काष्ठा *task;
	काष्ठा device *dev;
पूर्ण;

/**
 * test_config - represents configuration क्रम the test क्रम dअगरferent triggers
 *
 * @name: the name of the firmware file to look क्रम
 * @पूर्णांकo_buf: when the पूर्णांकo_buf is used अगर this is true
 *	request_firmware_पूर्णांकo_buf() will be used instead.
 * @buf_size: size of buf to allocate when पूर्णांकo_buf is true
 * @file_offset: file offset to request when calling request_firmware_पूर्णांकo_buf
 * @partial: partial पढ़ो opt when calling request_firmware_पूर्णांकo_buf
 * @sync_direct: when the sync trigger is used अगर this is true
 *	request_firmware_direct() will be used instead.
 * @send_uevent: whether or not to send a uevent क्रम async requests
 * @num_requests: number of requests to try per test हाल. This is trigger
 *	specअगरic.
 * @reqs: stores all requests inक्रमmation
 * @पढ़ो_fw_idx: index of thपढ़ो from which we want to पढ़ो firmware results
 *	from through the पढ़ो_fw trigger.
 * @test_result: a test may use this to collect the result from the call
 *	of the request_firmware*() calls used in their tests. In order of
 *	priority we always keep first any setup error. If no setup errors were
 *	found then we move on to the first error encountered जबतक running the
 *	API. Note that क्रम async calls this typically will be a successful
 *	result (0) unless of course you've used bogus parameters, or the प्रणाली
 *	is out of memory.  In the async हाल the callback is expected to करो a
 *	bit more homework to figure out what happened, unक्रमtunately the only
 *	inक्रमmation passed today on error is the fact that no firmware was
 *	found so we can only assume -ENOENT on async calls अगर the firmware is
 *	शून्य.
 *
 *	Errors you can expect:
 *
 *	API specअगरic:
 *
 *	0:		success क्रम sync, क्रम async it means request was sent
 *	-EINVAL:	invalid parameters or request
 *	-ENOENT:	files not found
 *
 *	System environment:
 *
 *	-ENOMEM:	memory pressure on प्रणाली
 *	-ENODEV:	out of number of devices to test
 *	-EINVAL:	an unexpected error has occurred
 * @req_firmware: अगर @sync_direct is true this is set to
 *	request_firmware_direct(), otherwise request_firmware()
 */
काष्ठा test_config अणु
	अक्षर *name;
	bool पूर्णांकo_buf;
	माप_प्रकार buf_size;
	माप_प्रकार file_offset;
	bool partial;
	bool sync_direct;
	bool send_uevent;
	u8 num_requests;
	u8 पढ़ो_fw_idx;

	/*
	 * These below करोn't belong her but we'll move them once we create
	 * a काष्ठा fw_test_device and stuff the misc_dev under there later.
	 */
	काष्ठा test_batched_req *reqs;
	पूर्णांक test_result;
	पूर्णांक (*req_firmware)(स्थिर काष्ठा firmware **fw, स्थिर अक्षर *name,
			    काष्ठा device *device);
पूर्ण;

अटल काष्ठा test_config *test_fw_config;

अटल sमाप_प्रकार test_fw_misc_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				 माप_प्रकार size, loff_t *offset)
अणु
	sमाप_प्रकार rc = 0;

	mutex_lock(&test_fw_mutex);
	अगर (test_firmware)
		rc = simple_पढ़ो_from_buffer(buf, size, offset,
					     test_firmware->data,
					     test_firmware->size);
	mutex_unlock(&test_fw_mutex);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations test_fw_fops = अणु
	.owner          = THIS_MODULE,
	.पढ़ो           = test_fw_misc_पढ़ो,
पूर्ण;

अटल व्योम __test_release_all_firmware(व्योम)
अणु
	काष्ठा test_batched_req *req;
	u8 i;

	अगर (!test_fw_config->reqs)
		वापस;

	क्रम (i = 0; i < test_fw_config->num_requests; i++) अणु
		req = &test_fw_config->reqs[i];
		अगर (req->fw)
			release_firmware(req->fw);
	पूर्ण

	vमुक्त(test_fw_config->reqs);
	test_fw_config->reqs = शून्य;
पूर्ण

अटल व्योम test_release_all_firmware(व्योम)
अणु
	mutex_lock(&test_fw_mutex);
	__test_release_all_firmware();
	mutex_unlock(&test_fw_mutex);
पूर्ण


अटल व्योम __test_firmware_config_मुक्त(व्योम)
अणु
	__test_release_all_firmware();
	kमुक्त_स्थिर(test_fw_config->name);
	test_fw_config->name = शून्य;
पूर्ण

/*
 * XXX: move to kम_नकलन() once merged.
 *
 * Users should use kमुक्त_स्थिर() when मुक्तing these.
 */
अटल पूर्णांक __kम_नकलन(अक्षर **dst, स्थिर अक्षर *name, माप_प्रकार count, gfp_t gfp)
अणु
	*dst = kstrndup(name, count, gfp);
	अगर (!*dst)
		वापस -ENOSPC;
	वापस count;
पूर्ण

अटल पूर्णांक __test_firmware_config_init(व्योम)
अणु
	पूर्णांक ret;

	ret = __kम_नकलन(&test_fw_config->name, TEST_FIRMWARE_NAME,
			 म_माप(TEST_FIRMWARE_NAME), GFP_KERNEL);
	अगर (ret < 0)
		जाओ out;

	test_fw_config->num_requests = TEST_FIRMWARE_NUM_REQS;
	test_fw_config->send_uevent = true;
	test_fw_config->पूर्णांकo_buf = false;
	test_fw_config->buf_size = TEST_FIRMWARE_BUF_SIZE;
	test_fw_config->file_offset = 0;
	test_fw_config->partial = false;
	test_fw_config->sync_direct = false;
	test_fw_config->req_firmware = request_firmware;
	test_fw_config->test_result = 0;
	test_fw_config->reqs = शून्य;

	वापस 0;

out:
	__test_firmware_config_मुक्त();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार reset_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;

	mutex_lock(&test_fw_mutex);

	__test_firmware_config_मुक्त();

	ret = __test_firmware_config_init();
	अगर (ret < 0) अणु
		ret = -ENOMEM;
		pr_err("could not alloc settings for config trigger: %d\n",
		       ret);
		जाओ out;
	पूर्ण

	pr_info("reset\n");
	ret = count;

out:
	mutex_unlock(&test_fw_mutex);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_WO(reset);

अटल sमाप_प्रकार config_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक len = 0;

	mutex_lock(&test_fw_mutex);

	len += scnम_लिखो(buf, PAGE_SIZE - len,
			"Custom trigger configuration for: %s\n",
			dev_name(dev));

	अगर (test_fw_config->name)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				"name:\t%s\n",
				test_fw_config->name);
	अन्यथा
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				"name:\tEMTPY\n");

	len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"num_requests:\t%u\n", test_fw_config->num_requests);

	len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"send_uevent:\t\t%s\n",
			test_fw_config->send_uevent ?
			"FW_ACTION_HOTPLUG" :
			"FW_ACTION_NOHOTPLUG");
	len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"into_buf:\t\t%s\n",
			test_fw_config->पूर्णांकo_buf ? "true" : "false");
	len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"buf_size:\t%zu\n", test_fw_config->buf_size);
	len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"file_offset:\t%zu\n", test_fw_config->file_offset);
	len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"partial:\t\t%s\n",
			test_fw_config->partial ? "true" : "false");
	len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"sync_direct:\t\t%s\n",
			test_fw_config->sync_direct ? "true" : "false");
	len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"read_fw_idx:\t%u\n", test_fw_config->पढ़ो_fw_idx);

	mutex_unlock(&test_fw_mutex);

	वापस len;
पूर्ण
अटल DEVICE_ATTR_RO(config);

अटल sमाप_प्रकार config_name_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;

	mutex_lock(&test_fw_mutex);
	kमुक्त_स्थिर(test_fw_config->name);
	ret = __kम_नकलन(&test_fw_config->name, buf, count, GFP_KERNEL);
	mutex_unlock(&test_fw_mutex);

	वापस ret;
पूर्ण

/*
 * As per sysfs_kf_seq_show() the buf is max PAGE_SIZE.
 */
अटल sमाप_प्रकार config_test_show_str(अक्षर *dst,
				    अक्षर *src)
अणु
	पूर्णांक len;

	mutex_lock(&test_fw_mutex);
	len = snम_लिखो(dst, PAGE_SIZE, "%s\n", src);
	mutex_unlock(&test_fw_mutex);

	वापस len;
पूर्ण

अटल पूर्णांक test_dev_config_update_bool(स्थिर अक्षर *buf, माप_प्रकार size,
				       bool *cfg)
अणु
	पूर्णांक ret;

	mutex_lock(&test_fw_mutex);
	अगर (strtobool(buf, cfg) < 0)
		ret = -EINVAL;
	अन्यथा
		ret = size;
	mutex_unlock(&test_fw_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार test_dev_config_show_bool(अक्षर *buf, bool val)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", val);
पूर्ण

अटल पूर्णांक test_dev_config_update_माप_प्रकार(स्थिर अक्षर *buf,
					 माप_प्रकार size,
					 माप_प्रकार *cfg)
अणु
	पूर्णांक ret;
	दीर्घ new;

	ret = kम_से_दीर्घ(buf, 10, &new);
	अगर (ret)
		वापस ret;

	mutex_lock(&test_fw_mutex);
	*(माप_प्रकार *)cfg = new;
	mutex_unlock(&test_fw_mutex);

	/* Always वापस full ग_लिखो size even अगर we didn't consume all */
	वापस size;
पूर्ण

अटल sमाप_प्रकार test_dev_config_show_माप_प्रकार(अक्षर *buf, माप_प्रकार val)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%zu\n", val);
पूर्ण

अटल sमाप_प्रकार test_dev_config_show_पूर्णांक(अक्षर *buf, पूर्णांक val)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", val);
पूर्ण

अटल पूर्णांक test_dev_config_update_u8(स्थिर अक्षर *buf, माप_प्रकार size, u8 *cfg)
अणु
	u8 val;
	पूर्णांक ret;

	ret = kstrtou8(buf, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&test_fw_mutex);
	*(u8 *)cfg = val;
	mutex_unlock(&test_fw_mutex);

	/* Always वापस full ग_लिखो size even अगर we didn't consume all */
	वापस size;
पूर्ण

अटल sमाप_प्रकार test_dev_config_show_u8(अक्षर *buf, u8 val)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार config_name_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	वापस config_test_show_str(buf, test_fw_config->name);
पूर्ण
अटल DEVICE_ATTR_RW(config_name);

अटल sमाप_प्रकार config_num_requests_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;

	mutex_lock(&test_fw_mutex);
	अगर (test_fw_config->reqs) अणु
		pr_err("Must call release_all_firmware prior to changing config\n");
		rc = -EINVAL;
		mutex_unlock(&test_fw_mutex);
		जाओ out;
	पूर्ण
	mutex_unlock(&test_fw_mutex);

	rc = test_dev_config_update_u8(buf, count,
				       &test_fw_config->num_requests);

out:
	वापस rc;
पूर्ण

अटल sमाप_प्रकार config_num_requests_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	वापस test_dev_config_show_u8(buf, test_fw_config->num_requests);
पूर्ण
अटल DEVICE_ATTR_RW(config_num_requests);

अटल sमाप_प्रकार config_पूर्णांकo_buf_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस test_dev_config_update_bool(buf,
					   count,
					   &test_fw_config->पूर्णांकo_buf);
पूर्ण

अटल sमाप_प्रकार config_पूर्णांकo_buf_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	वापस test_dev_config_show_bool(buf, test_fw_config->पूर्णांकo_buf);
पूर्ण
अटल DEVICE_ATTR_RW(config_पूर्णांकo_buf);

अटल sमाप_प्रकार config_buf_size_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;

	mutex_lock(&test_fw_mutex);
	अगर (test_fw_config->reqs) अणु
		pr_err("Must call release_all_firmware prior to changing config\n");
		rc = -EINVAL;
		mutex_unlock(&test_fw_mutex);
		जाओ out;
	पूर्ण
	mutex_unlock(&test_fw_mutex);

	rc = test_dev_config_update_माप_प्रकार(buf, count,
					   &test_fw_config->buf_size);

out:
	वापस rc;
पूर्ण

अटल sमाप_प्रकार config_buf_size_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	वापस test_dev_config_show_माप_प्रकार(buf, test_fw_config->buf_size);
पूर्ण
अटल DEVICE_ATTR_RW(config_buf_size);

अटल sमाप_प्रकार config_file_offset_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;

	mutex_lock(&test_fw_mutex);
	अगर (test_fw_config->reqs) अणु
		pr_err("Must call release_all_firmware prior to changing config\n");
		rc = -EINVAL;
		mutex_unlock(&test_fw_mutex);
		जाओ out;
	पूर्ण
	mutex_unlock(&test_fw_mutex);

	rc = test_dev_config_update_माप_प्रकार(buf, count,
					   &test_fw_config->file_offset);

out:
	वापस rc;
पूर्ण

अटल sमाप_प्रकार config_file_offset_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	वापस test_dev_config_show_माप_प्रकार(buf, test_fw_config->file_offset);
पूर्ण
अटल DEVICE_ATTR_RW(config_file_offset);

अटल sमाप_प्रकार config_partial_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस test_dev_config_update_bool(buf,
					   count,
					   &test_fw_config->partial);
पूर्ण

अटल sमाप_प्रकार config_partial_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	वापस test_dev_config_show_bool(buf, test_fw_config->partial);
पूर्ण
अटल DEVICE_ATTR_RW(config_partial);

अटल sमाप_प्रकार config_sync_direct_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc = test_dev_config_update_bool(buf, count,
					     &test_fw_config->sync_direct);

	अगर (rc == count)
		test_fw_config->req_firmware = test_fw_config->sync_direct ?
				       request_firmware_direct :
				       request_firmware;
	वापस rc;
पूर्ण

अटल sमाप_प्रकार config_sync_direct_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	वापस test_dev_config_show_bool(buf, test_fw_config->sync_direct);
पूर्ण
अटल DEVICE_ATTR_RW(config_sync_direct);

अटल sमाप_प्रकार config_send_uevent_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस test_dev_config_update_bool(buf, count,
					   &test_fw_config->send_uevent);
पूर्ण

अटल sमाप_प्रकार config_send_uevent_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	वापस test_dev_config_show_bool(buf, test_fw_config->send_uevent);
पूर्ण
अटल DEVICE_ATTR_RW(config_send_uevent);

अटल sमाप_प्रकार config_पढ़ो_fw_idx_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस test_dev_config_update_u8(buf, count,
					 &test_fw_config->पढ़ो_fw_idx);
पूर्ण

अटल sमाप_प्रकार config_पढ़ो_fw_idx_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	वापस test_dev_config_show_u8(buf, test_fw_config->पढ़ो_fw_idx);
पूर्ण
अटल DEVICE_ATTR_RW(config_पढ़ो_fw_idx);


अटल sमाप_प्रकार trigger_request_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	अक्षर *name;

	name = kstrndup(buf, count, GFP_KERNEL);
	अगर (!name)
		वापस -ENOSPC;

	pr_info("loading '%s'\n", name);

	mutex_lock(&test_fw_mutex);
	release_firmware(test_firmware);
	test_firmware = शून्य;
	rc = request_firmware(&test_firmware, name, dev);
	अगर (rc) अणु
		pr_info("load of '%s' failed: %d\n", name, rc);
		जाओ out;
	पूर्ण
	pr_info("loaded: %zu\n", test_firmware->size);
	rc = count;

out:
	mutex_unlock(&test_fw_mutex);

	kमुक्त(name);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_WO(trigger_request);

#अगर_घोषित CONFIG_EFI_EMBEDDED_FIRMWARE
बाह्य काष्ठा list_head efi_embedded_fw_list;
बाह्य bool efi_embedded_fw_checked;

अटल sमाप_प्रकार trigger_request_platक्रमm_store(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अटल स्थिर u8 test_data[] = अणु
		0x55, 0xaa, 0x55, 0xaa, 0x01, 0x02, 0x03, 0x04,
		0x55, 0xaa, 0x55, 0xaa, 0x05, 0x06, 0x07, 0x08,
		0x55, 0xaa, 0x55, 0xaa, 0x10, 0x20, 0x30, 0x40,
		0x55, 0xaa, 0x55, 0xaa, 0x50, 0x60, 0x70, 0x80
	पूर्ण;
	काष्ठा efi_embedded_fw efi_embedded_fw;
	स्थिर काष्ठा firmware *firmware = शून्य;
	bool saved_efi_embedded_fw_checked;
	अक्षर *name;
	पूर्णांक rc;

	name = kstrndup(buf, count, GFP_KERNEL);
	अगर (!name)
		वापस -ENOSPC;

	pr_info("inserting test platform fw '%s'\n", name);
	efi_embedded_fw.name = name;
	efi_embedded_fw.data = (व्योम *)test_data;
	efi_embedded_fw.length = माप(test_data);
	list_add(&efi_embedded_fw.list, &efi_embedded_fw_list);
	saved_efi_embedded_fw_checked = efi_embedded_fw_checked;
	efi_embedded_fw_checked = true;

	pr_info("loading '%s'\n", name);
	rc = firmware_request_platक्रमm(&firmware, name, dev);
	अगर (rc) अणु
		pr_info("load of '%s' failed: %d\n", name, rc);
		जाओ out;
	पूर्ण
	अगर (firmware->size != माप(test_data) ||
	    स_भेद(firmware->data, test_data, माप(test_data)) != 0) अणु
		pr_info("firmware contents mismatch for '%s'\n", name);
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	pr_info("loaded: %zu\n", firmware->size);
	rc = count;

out:
	efi_embedded_fw_checked = saved_efi_embedded_fw_checked;
	release_firmware(firmware);
	list_del(&efi_embedded_fw.list);
	kमुक्त(name);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_WO(trigger_request_platक्रमm);
#पूर्ण_अगर

अटल DECLARE_COMPLETION(async_fw_करोne);

अटल व्योम trigger_async_request_cb(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	test_firmware = fw;
	complete(&async_fw_करोne);
पूर्ण

अटल sमाप_प्रकार trigger_async_request_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	अक्षर *name;

	name = kstrndup(buf, count, GFP_KERNEL);
	अगर (!name)
		वापस -ENOSPC;

	pr_info("loading '%s'\n", name);

	mutex_lock(&test_fw_mutex);
	release_firmware(test_firmware);
	test_firmware = शून्य;
	rc = request_firmware_noरुको(THIS_MODULE, 1, name, dev, GFP_KERNEL,
				     शून्य, trigger_async_request_cb);
	अगर (rc) अणु
		pr_info("async load of '%s' failed: %d\n", name, rc);
		kमुक्त(name);
		जाओ out;
	पूर्ण
	/* Free 'name' ASAP, to test क्रम race conditions */
	kमुक्त(name);

	रुको_क्रम_completion(&async_fw_करोne);

	अगर (test_firmware) अणु
		pr_info("loaded: %zu\n", test_firmware->size);
		rc = count;
	पूर्ण अन्यथा अणु
		pr_err("failed to async load firmware\n");
		rc = -ENOMEM;
	पूर्ण

out:
	mutex_unlock(&test_fw_mutex);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_WO(trigger_async_request);

अटल sमाप_प्रकार trigger_custom_fallback_store(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	अक्षर *name;

	name = kstrndup(buf, count, GFP_KERNEL);
	अगर (!name)
		वापस -ENOSPC;

	pr_info("loading '%s' using custom fallback mechanism\n", name);

	mutex_lock(&test_fw_mutex);
	release_firmware(test_firmware);
	test_firmware = शून्य;
	rc = request_firmware_noरुको(THIS_MODULE, FW_ACTION_NOHOTPLUG, name,
				     dev, GFP_KERNEL, शून्य,
				     trigger_async_request_cb);
	अगर (rc) अणु
		pr_info("async load of '%s' failed: %d\n", name, rc);
		kमुक्त(name);
		जाओ out;
	पूर्ण
	/* Free 'name' ASAP, to test क्रम race conditions */
	kमुक्त(name);

	रुको_क्रम_completion(&async_fw_करोne);

	अगर (test_firmware) अणु
		pr_info("loaded: %zu\n", test_firmware->size);
		rc = count;
	पूर्ण अन्यथा अणु
		pr_err("failed to async load firmware\n");
		rc = -ENODEV;
	पूर्ण

out:
	mutex_unlock(&test_fw_mutex);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_WO(trigger_custom_fallback);

अटल पूर्णांक test_fw_run_batch_request(व्योम *data)
अणु
	काष्ठा test_batched_req *req = data;

	अगर (!req) अणु
		test_fw_config->test_result = -EINVAL;
		वापस -EINVAL;
	पूर्ण

	अगर (test_fw_config->पूर्णांकo_buf) अणु
		व्योम *test_buf;

		test_buf = kzalloc(TEST_FIRMWARE_BUF_SIZE, GFP_KERNEL);
		अगर (!test_buf)
			वापस -ENOSPC;

		अगर (test_fw_config->partial)
			req->rc = request_partial_firmware_पूर्णांकo_buf
						(&req->fw,
						 req->name,
						 req->dev,
						 test_buf,
						 test_fw_config->buf_size,
						 test_fw_config->file_offset);
		अन्यथा
			req->rc = request_firmware_पूर्णांकo_buf
						(&req->fw,
						 req->name,
						 req->dev,
						 test_buf,
						 test_fw_config->buf_size);
		अगर (!req->fw)
			kमुक्त(test_buf);
	पूर्ण अन्यथा अणु
		req->rc = test_fw_config->req_firmware(&req->fw,
						       req->name,
						       req->dev);
	पूर्ण

	अगर (req->rc) अणु
		pr_info("#%u: batched sync load failed: %d\n",
			req->idx, req->rc);
		अगर (!test_fw_config->test_result)
			test_fw_config->test_result = req->rc;
	पूर्ण अन्यथा अगर (req->fw) अणु
		req->sent = true;
		pr_info("#%u: batched sync loaded %zu\n",
			req->idx, req->fw->size);
	पूर्ण
	complete(&req->completion);

	req->task = शून्य;

	वापस 0;
पूर्ण

/*
 * We use a kthपढ़ो as otherwise the kernel serializes all our sync requests
 * and we would not be able to mimic batched requests on a sync call. Batched
 * requests on a sync call can क्रम instance happen on a device driver when
 * multiple cards are used and firmware loading happens outside of probe.
 */
अटल sमाप_प्रकार trigger_batched_requests_store(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा test_batched_req *req;
	पूर्णांक rc;
	u8 i;

	mutex_lock(&test_fw_mutex);

	test_fw_config->reqs =
		vzalloc(array3_size(माप(काष्ठा test_batched_req),
				    test_fw_config->num_requests, 2));
	अगर (!test_fw_config->reqs) अणु
		rc = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	pr_info("batched sync firmware loading '%s' %u times\n",
		test_fw_config->name, test_fw_config->num_requests);

	क्रम (i = 0; i < test_fw_config->num_requests; i++) अणु
		req = &test_fw_config->reqs[i];
		req->fw = शून्य;
		req->idx = i;
		req->name = test_fw_config->name;
		req->dev = dev;
		init_completion(&req->completion);
		req->task = kthपढ़ो_run(test_fw_run_batch_request, req,
					     "%s-%u", KBUILD_MODNAME, req->idx);
		अगर (!req->task || IS_ERR(req->task)) अणु
			pr_err("Setting up thread %u failed\n", req->idx);
			req->task = शून्य;
			rc = -ENOMEM;
			जाओ out_bail;
		पूर्ण
	पूर्ण

	rc = count;

	/*
	 * We require an explicit release to enable more समय and delay of
	 * calling release_firmware() to improve our chances of क्रमcing a
	 * batched request. If we instead called release_firmware() right away
	 * then we might miss on an opportunity of having a successful firmware
	 * request pass on the opportunity to be come a batched request.
	 */

out_bail:
	क्रम (i = 0; i < test_fw_config->num_requests; i++) अणु
		req = &test_fw_config->reqs[i];
		अगर (req->task || req->sent)
			रुको_क्रम_completion(&req->completion);
	पूर्ण

	/* Override any worker error अगर we had a general setup error */
	अगर (rc < 0)
		test_fw_config->test_result = rc;

out_unlock:
	mutex_unlock(&test_fw_mutex);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_WO(trigger_batched_requests);

/*
 * We रुको क्रम each callback to वापस with the lock held, no need to lock here
 */
अटल व्योम trigger_batched_cb(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा test_batched_req *req = context;

	अगर (!req) अणु
		test_fw_config->test_result = -EINVAL;
		वापस;
	पूर्ण

	/* क्रमces *some* batched requests to queue up */
	अगर (!req->idx)
		ssleep(2);

	req->fw = fw;

	/*
	 * Unक्रमtunately the firmware API gives us nothing other than a null FW
	 * अगर the firmware was not found on async requests.  Best we can करो is
	 * just assume -ENOENT. A better API would pass the actual वापस
	 * value to the callback.
	 */
	अगर (!fw && !test_fw_config->test_result)
		test_fw_config->test_result = -ENOENT;

	complete(&req->completion);
पूर्ण

अटल
sमाप_प्रकार trigger_batched_requests_async_store(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा test_batched_req *req;
	bool send_uevent;
	पूर्णांक rc;
	u8 i;

	mutex_lock(&test_fw_mutex);

	test_fw_config->reqs =
		vzalloc(array3_size(माप(काष्ठा test_batched_req),
				    test_fw_config->num_requests, 2));
	अगर (!test_fw_config->reqs) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	pr_info("batched loading '%s' custom fallback mechanism %u times\n",
		test_fw_config->name, test_fw_config->num_requests);

	send_uevent = test_fw_config->send_uevent ? FW_ACTION_HOTPLUG :
		FW_ACTION_NOHOTPLUG;

	क्रम (i = 0; i < test_fw_config->num_requests; i++) अणु
		req = &test_fw_config->reqs[i];
		req->name = test_fw_config->name;
		req->fw = शून्य;
		req->idx = i;
		init_completion(&req->completion);
		rc = request_firmware_noरुको(THIS_MODULE, send_uevent,
					     req->name,
					     dev, GFP_KERNEL, req,
					     trigger_batched_cb);
		अगर (rc) अणु
			pr_info("#%u: batched async load failed setup: %d\n",
				i, rc);
			req->rc = rc;
			जाओ out_bail;
		पूर्ण अन्यथा
			req->sent = true;
	पूर्ण

	rc = count;

out_bail:

	/*
	 * We require an explicit release to enable more समय and delay of
	 * calling release_firmware() to improve our chances of क्रमcing a
	 * batched request. If we instead called release_firmware() right away
	 * then we might miss on an opportunity of having a successful firmware
	 * request pass on the opportunity to be come a batched request.
	 */

	क्रम (i = 0; i < test_fw_config->num_requests; i++) अणु
		req = &test_fw_config->reqs[i];
		अगर (req->sent)
			रुको_क्रम_completion(&req->completion);
	पूर्ण

	/* Override any worker error अगर we had a general setup error */
	अगर (rc < 0)
		test_fw_config->test_result = rc;

out:
	mutex_unlock(&test_fw_mutex);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_WO(trigger_batched_requests_async);

अटल sमाप_प्रकार test_result_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	वापस test_dev_config_show_पूर्णांक(buf, test_fw_config->test_result);
पूर्ण
अटल DEVICE_ATTR_RO(test_result);

अटल sमाप_प्रकार release_all_firmware_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	test_release_all_firmware();
	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(release_all_firmware);

अटल sमाप_प्रकार पढ़ो_firmware_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा test_batched_req *req;
	u8 idx;
	sमाप_प्रकार rc = 0;

	mutex_lock(&test_fw_mutex);

	idx = test_fw_config->पढ़ो_fw_idx;
	अगर (idx >= test_fw_config->num_requests) अणु
		rc = -दुस्फल;
		जाओ out;
	पूर्ण

	अगर (!test_fw_config->reqs) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	req = &test_fw_config->reqs[idx];
	अगर (!req->fw) अणु
		pr_err("#%u: failed to async load firmware\n", idx);
		rc = -ENOENT;
		जाओ out;
	पूर्ण

	pr_info("#%u: loaded %zu\n", idx, req->fw->size);

	अगर (req->fw->size > PAGE_SIZE) अणु
		pr_err("Testing interface must use PAGE_SIZE firmware for now\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	स_नकल(buf, req->fw->data, req->fw->size);

	rc = req->fw->size;
out:
	mutex_unlock(&test_fw_mutex);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(पढ़ो_firmware);

#घोषणा TEST_FW_DEV_ATTR(name)          &dev_attr_##name.attr

अटल काष्ठा attribute *test_dev_attrs[] = अणु
	TEST_FW_DEV_ATTR(reset),

	TEST_FW_DEV_ATTR(config),
	TEST_FW_DEV_ATTR(config_name),
	TEST_FW_DEV_ATTR(config_num_requests),
	TEST_FW_DEV_ATTR(config_पूर्णांकo_buf),
	TEST_FW_DEV_ATTR(config_buf_size),
	TEST_FW_DEV_ATTR(config_file_offset),
	TEST_FW_DEV_ATTR(config_partial),
	TEST_FW_DEV_ATTR(config_sync_direct),
	TEST_FW_DEV_ATTR(config_send_uevent),
	TEST_FW_DEV_ATTR(config_पढ़ो_fw_idx),

	/* These करोn't use the config at all - they could be ported! */
	TEST_FW_DEV_ATTR(trigger_request),
	TEST_FW_DEV_ATTR(trigger_async_request),
	TEST_FW_DEV_ATTR(trigger_custom_fallback),
#अगर_घोषित CONFIG_EFI_EMBEDDED_FIRMWARE
	TEST_FW_DEV_ATTR(trigger_request_platक्रमm),
#पूर्ण_अगर

	/* These use the config and can use the test_result */
	TEST_FW_DEV_ATTR(trigger_batched_requests),
	TEST_FW_DEV_ATTR(trigger_batched_requests_async),

	TEST_FW_DEV_ATTR(release_all_firmware),
	TEST_FW_DEV_ATTR(test_result),
	TEST_FW_DEV_ATTR(पढ़ो_firmware),
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(test_dev);

अटल काष्ठा miscdevice test_fw_misc_device = अणु
	.minor          = MISC_DYNAMIC_MINOR,
	.name           = "test_firmware",
	.fops           = &test_fw_fops,
	.groups 	= test_dev_groups,
पूर्ण;

अटल पूर्णांक __init test_firmware_init(व्योम)
अणु
	पूर्णांक rc;

	test_fw_config = kzalloc(माप(काष्ठा test_config), GFP_KERNEL);
	अगर (!test_fw_config)
		वापस -ENOMEM;

	rc = __test_firmware_config_init();
	अगर (rc) अणु
		kमुक्त(test_fw_config);
		pr_err("could not init firmware test config: %d\n", rc);
		वापस rc;
	पूर्ण

	rc = misc_रेजिस्टर(&test_fw_misc_device);
	अगर (rc) अणु
		kमुक्त(test_fw_config);
		pr_err("could not register misc device: %d\n", rc);
		वापस rc;
	पूर्ण

	pr_warn("interface ready\n");

	वापस 0;
पूर्ण

module_init(test_firmware_init);

अटल व्योम __निकास test_firmware_निकास(व्योम)
अणु
	mutex_lock(&test_fw_mutex);
	release_firmware(test_firmware);
	misc_deरेजिस्टर(&test_fw_misc_device);
	__test_firmware_config_मुक्त();
	kमुक्त(test_fw_config);
	mutex_unlock(&test_fw_mutex);

	pr_warn("removed interface\n");
पूर्ण

module_निकास(test_firmware_निकास);

MODULE_AUTHOR("Kees Cook <keescook@chromium.org>");
MODULE_LICENSE("GPL");
