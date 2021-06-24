<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/types.h>
#समावेश <linux/kconfig.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/umh.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>

#समावेश "fallback.h"
#समावेश "firmware.h"

/*
 * firmware fallback mechanism
 */

MODULE_IMPORT_NS(FIRMWARE_LOADER_PRIVATE);

बाह्य काष्ठा firmware_fallback_config fw_fallback_config;

/* These getters are vetted to use पूर्णांक properly */
अटल अंतरभूत पूर्णांक __firmware_loading_समयout(व्योम)
अणु
	वापस fw_fallback_config.loading_समयout;
पूर्ण

/* These setters are vetted to use पूर्णांक properly */
अटल व्योम __fw_fallback_set_समयout(पूर्णांक समयout)
अणु
	fw_fallback_config.loading_समयout = समयout;
पूर्ण

/*
 * use small loading समयout क्रम caching devices' firmware because all these
 * firmware images have been loaded successfully at lease once, also प्रणाली is
 * पढ़ोy क्रम completing firmware loading now. The maximum size of firmware in
 * current distributions is about 2M bytes, so 10 secs should be enough.
 */
व्योम fw_fallback_set_cache_समयout(व्योम)
अणु
	fw_fallback_config.old_समयout = __firmware_loading_समयout();
	__fw_fallback_set_समयout(10);
पूर्ण

/* Restores the समयout to the value last configured during normal operation */
व्योम fw_fallback_set_शेष_समयout(व्योम)
अणु
	__fw_fallback_set_समयout(fw_fallback_config.old_समयout);
पूर्ण

अटल दीर्घ firmware_loading_समयout(व्योम)
अणु
	वापस __firmware_loading_समयout() > 0 ?
		__firmware_loading_समयout() * HZ : MAX_JIFFY_OFFSET;
पूर्ण

अटल अंतरभूत bool fw_sysfs_करोne(काष्ठा fw_priv *fw_priv)
अणु
	वापस __fw_state_check(fw_priv, FW_STATUS_DONE);
पूर्ण

अटल अंतरभूत bool fw_sysfs_loading(काष्ठा fw_priv *fw_priv)
अणु
	वापस __fw_state_check(fw_priv, FW_STATUS_LOADING);
पूर्ण

अटल अंतरभूत पूर्णांक fw_sysfs_रुको_समयout(काष्ठा fw_priv *fw_priv,  दीर्घ समयout)
अणु
	वापस __fw_state_रुको_common(fw_priv, समयout);
पूर्ण

काष्ठा fw_sysfs अणु
	bool noरुको;
	काष्ठा device dev;
	काष्ठा fw_priv *fw_priv;
	काष्ठा firmware *fw;
पूर्ण;

अटल काष्ठा fw_sysfs *to_fw_sysfs(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा fw_sysfs, dev);
पूर्ण

अटल व्योम __fw_load_पात(काष्ठा fw_priv *fw_priv)
अणु
	/*
	 * There is a small winकरोw in which user can ग_लिखो to 'loading'
	 * between loading करोne and disappearance of 'loading'
	 */
	अगर (fw_sysfs_करोne(fw_priv))
		वापस;

	list_del_init(&fw_priv->pending_list);
	fw_state_पातed(fw_priv);
पूर्ण

अटल व्योम fw_load_पात(काष्ठा fw_sysfs *fw_sysfs)
अणु
	काष्ठा fw_priv *fw_priv = fw_sysfs->fw_priv;

	__fw_load_पात(fw_priv);
पूर्ण

अटल LIST_HEAD(pending_fw_head);

व्योम समाप्त_pending_fw_fallback_reqs(bool only_समाप्त_custom)
अणु
	काष्ठा fw_priv *fw_priv;
	काष्ठा fw_priv *next;

	mutex_lock(&fw_lock);
	list_क्रम_each_entry_safe(fw_priv, next, &pending_fw_head,
				 pending_list) अणु
		अगर (!fw_priv->need_uevent || !only_समाप्त_custom)
			 __fw_load_पात(fw_priv);
	पूर्ण
	mutex_unlock(&fw_lock);
पूर्ण

अटल sमाप_प्रकार समयout_show(काष्ठा class *class, काष्ठा class_attribute *attr,
			    अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", __firmware_loading_समयout());
पूर्ण

/**
 * समयout_store() - set number of seconds to रुको क्रम firmware
 * @class: device class poपूर्णांकer
 * @attr: device attribute poपूर्णांकer
 * @buf: buffer to scan क्रम समयout value
 * @count: number of bytes in @buf
 *
 *	Sets the number of seconds to रुको क्रम the firmware.  Once
 *	this expires an error will be वापसed to the driver and no
 *	firmware will be provided.
 *
 *	Note: zero means 'wait forever'.
 **/
अटल sमाप_प्रकार समयout_store(काष्ठा class *class, काष्ठा class_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक पंचांगp_loading_समयout = simple_म_से_दीर्घ(buf, शून्य, 10);

	अगर (पंचांगp_loading_समयout < 0)
		पंचांगp_loading_समयout = 0;

	__fw_fallback_set_समयout(पंचांगp_loading_समयout);

	वापस count;
पूर्ण
अटल CLASS_ATTR_RW(समयout);

अटल काष्ठा attribute *firmware_class_attrs[] = अणु
	&class_attr_समयout.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(firmware_class);

अटल व्योम fw_dev_release(काष्ठा device *dev)
अणु
	काष्ठा fw_sysfs *fw_sysfs = to_fw_sysfs(dev);

	kमुक्त(fw_sysfs);
पूर्ण

अटल पूर्णांक करो_firmware_uevent(काष्ठा fw_sysfs *fw_sysfs, काष्ठा kobj_uevent_env *env)
अणु
	अगर (add_uevent_var(env, "FIRMWARE=%s", fw_sysfs->fw_priv->fw_name))
		वापस -ENOMEM;
	अगर (add_uevent_var(env, "TIMEOUT=%i", __firmware_loading_समयout()))
		वापस -ENOMEM;
	अगर (add_uevent_var(env, "ASYNC=%d", fw_sysfs->noरुको))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक firmware_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	पूर्णांक err = 0;

	mutex_lock(&fw_lock);
	अगर (fw_sysfs->fw_priv)
		err = करो_firmware_uevent(fw_sysfs, env);
	mutex_unlock(&fw_lock);
	वापस err;
पूर्ण

अटल काष्ठा class firmware_class = अणु
	.name		= "firmware",
	.class_groups	= firmware_class_groups,
	.dev_uevent	= firmware_uevent,
	.dev_release	= fw_dev_release,
पूर्ण;

पूर्णांक रेजिस्टर_sysfs_loader(व्योम)
अणु
	वापस class_रेजिस्टर(&firmware_class);
पूर्ण

व्योम unरेजिस्टर_sysfs_loader(व्योम)
अणु
	class_unरेजिस्टर(&firmware_class);
पूर्ण

अटल sमाप_प्रकार firmware_loading_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	पूर्णांक loading = 0;

	mutex_lock(&fw_lock);
	अगर (fw_sysfs->fw_priv)
		loading = fw_sysfs_loading(fw_sysfs->fw_priv);
	mutex_unlock(&fw_lock);

	वापस sysfs_emit(buf, "%d\n", loading);
पूर्ण

/**
 * firmware_loading_store() - set value in the 'loading' control file
 * @dev: device poपूर्णांकer
 * @attr: device attribute poपूर्णांकer
 * @buf: buffer to scan क्रम loading control value
 * @count: number of bytes in @buf
 *
 *	The relevant values are:
 *
 *	 1: Start a load, discarding any previous partial load.
 *	 0: Conclude the load and hand the data to the driver code.
 *	-1: Conclude the load with an error and discard any written data.
 **/
अटल sमाप_प्रकार firmware_loading_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	काष्ठा fw_priv *fw_priv;
	sमाप_प्रकार written = count;
	पूर्णांक loading = simple_म_से_दीर्घ(buf, शून्य, 10);

	mutex_lock(&fw_lock);
	fw_priv = fw_sysfs->fw_priv;
	अगर (fw_state_is_पातed(fw_priv))
		जाओ out;

	चयन (loading) अणु
	हाल 1:
		/* discarding any previous partial load */
		अगर (!fw_sysfs_करोne(fw_priv)) अणु
			fw_मुक्त_paged_buf(fw_priv);
			fw_state_start(fw_priv);
		पूर्ण
		अवरोध;
	हाल 0:
		अगर (fw_sysfs_loading(fw_priv)) अणु
			पूर्णांक rc;

			/*
			 * Several loading requests may be pending on
			 * one same firmware buf, so let all requests
			 * see the mapped 'buf->data' once the loading
			 * is completed.
			 * */
			rc = fw_map_paged_buf(fw_priv);
			अगर (rc)
				dev_err(dev, "%s: map pages failed\n",
					__func__);
			अन्यथा
				rc = security_kernel_post_load_data(fw_priv->data,
						fw_priv->size,
						LOADING_FIRMWARE, "blob");

			/*
			 * Same logic as fw_load_पात, only the DONE bit
			 * is ignored and we set ABORT only on failure.
			 */
			list_del_init(&fw_priv->pending_list);
			अगर (rc) अणु
				fw_state_पातed(fw_priv);
				written = rc;
			पूर्ण अन्यथा अणु
				fw_state_करोne(fw_priv);
			पूर्ण
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		dev_err(dev, "%s: unexpected value (%d)\n", __func__, loading);
		fallthrough;
	हाल -1:
		fw_load_पात(fw_sysfs);
		अवरोध;
	पूर्ण
out:
	mutex_unlock(&fw_lock);
	वापस written;
पूर्ण

अटल DEVICE_ATTR(loading, 0644, firmware_loading_show, firmware_loading_store);

अटल व्योम firmware_rw_data(काष्ठा fw_priv *fw_priv, अक्षर *buffer,
			   loff_t offset, माप_प्रकार count, bool पढ़ो)
अणु
	अगर (पढ़ो)
		स_नकल(buffer, fw_priv->data + offset, count);
	अन्यथा
		स_नकल(fw_priv->data + offset, buffer, count);
पूर्ण

अटल व्योम firmware_rw(काष्ठा fw_priv *fw_priv, अक्षर *buffer,
			loff_t offset, माप_प्रकार count, bool पढ़ो)
अणु
	जबतक (count) अणु
		व्योम *page_data;
		पूर्णांक page_nr = offset >> PAGE_SHIFT;
		पूर्णांक page_ofs = offset & (PAGE_SIZE-1);
		पूर्णांक page_cnt = min_t(माप_प्रकार, PAGE_SIZE - page_ofs, count);

		page_data = kmap(fw_priv->pages[page_nr]);

		अगर (पढ़ो)
			स_नकल(buffer, page_data + page_ofs, page_cnt);
		अन्यथा
			स_नकल(page_data + page_ofs, buffer, page_cnt);

		kunmap(fw_priv->pages[page_nr]);
		buffer += page_cnt;
		offset += page_cnt;
		count -= page_cnt;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार firmware_data_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				  काष्ठा bin_attribute *bin_attr,
				  अक्षर *buffer, loff_t offset, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	काष्ठा fw_priv *fw_priv;
	sमाप_प्रकार ret_count;

	mutex_lock(&fw_lock);
	fw_priv = fw_sysfs->fw_priv;
	अगर (!fw_priv || fw_sysfs_करोne(fw_priv)) अणु
		ret_count = -ENODEV;
		जाओ out;
	पूर्ण
	अगर (offset > fw_priv->size) अणु
		ret_count = 0;
		जाओ out;
	पूर्ण
	अगर (count > fw_priv->size - offset)
		count = fw_priv->size - offset;

	ret_count = count;

	अगर (fw_priv->data)
		firmware_rw_data(fw_priv, buffer, offset, count, true);
	अन्यथा
		firmware_rw(fw_priv, buffer, offset, count, true);

out:
	mutex_unlock(&fw_lock);
	वापस ret_count;
पूर्ण

अटल पूर्णांक fw_पुनः_स्मृति_pages(काष्ठा fw_sysfs *fw_sysfs, पूर्णांक min_size)
अणु
	पूर्णांक err;

	err = fw_grow_paged_buf(fw_sysfs->fw_priv,
				PAGE_ALIGN(min_size) >> PAGE_SHIFT);
	अगर (err)
		fw_load_पात(fw_sysfs);
	वापस err;
पूर्ण

/**
 * firmware_data_ग_लिखो() - ग_लिखो method क्रम firmware
 * @filp: खोलो sysfs file
 * @kobj: kobject क्रम the device
 * @bin_attr: bin_attr काष्ठाure
 * @buffer: buffer being written
 * @offset: buffer offset क्रम ग_लिखो in total data store area
 * @count: buffer size
 *
 *	Data written to the 'data' attribute will be later handed to
 *	the driver as a firmware image.
 **/
अटल sमाप_प्रकार firmware_data_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				   काष्ठा bin_attribute *bin_attr,
				   अक्षर *buffer, loff_t offset, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा fw_sysfs *fw_sysfs = to_fw_sysfs(dev);
	काष्ठा fw_priv *fw_priv;
	sमाप_प्रकार retval;

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	mutex_lock(&fw_lock);
	fw_priv = fw_sysfs->fw_priv;
	अगर (!fw_priv || fw_sysfs_करोne(fw_priv)) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (fw_priv->data) अणु
		अगर (offset + count > fw_priv->allocated_size) अणु
			retval = -ENOMEM;
			जाओ out;
		पूर्ण
		firmware_rw_data(fw_priv, buffer, offset, count, false);
		retval = count;
	पूर्ण अन्यथा अणु
		retval = fw_पुनः_स्मृति_pages(fw_sysfs, offset + count);
		अगर (retval)
			जाओ out;

		retval = count;
		firmware_rw(fw_priv, buffer, offset, count, false);
	पूर्ण

	fw_priv->size = max_t(माप_प्रकार, offset + count, fw_priv->size);
out:
	mutex_unlock(&fw_lock);
	वापस retval;
पूर्ण

अटल काष्ठा bin_attribute firmware_attr_data = अणु
	.attr = अणु .name = "data", .mode = 0644 पूर्ण,
	.size = 0,
	.पढ़ो = firmware_data_पढ़ो,
	.ग_लिखो = firmware_data_ग_लिखो,
पूर्ण;

अटल काष्ठा attribute *fw_dev_attrs[] = अणु
	&dev_attr_loading.attr,
	शून्य
पूर्ण;

अटल काष्ठा bin_attribute *fw_dev_bin_attrs[] = अणु
	&firmware_attr_data,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group fw_dev_attr_group = अणु
	.attrs = fw_dev_attrs,
	.bin_attrs = fw_dev_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *fw_dev_attr_groups[] = अणु
	&fw_dev_attr_group,
	शून्य
पूर्ण;

अटल काष्ठा fw_sysfs *
fw_create_instance(काष्ठा firmware *firmware, स्थिर अक्षर *fw_name,
		   काष्ठा device *device, u32 opt_flags)
अणु
	काष्ठा fw_sysfs *fw_sysfs;
	काष्ठा device *f_dev;

	fw_sysfs = kzalloc(माप(*fw_sysfs), GFP_KERNEL);
	अगर (!fw_sysfs) अणु
		fw_sysfs = ERR_PTR(-ENOMEM);
		जाओ निकास;
	पूर्ण

	fw_sysfs->noरुको = !!(opt_flags & FW_OPT_NOWAIT);
	fw_sysfs->fw = firmware;
	f_dev = &fw_sysfs->dev;

	device_initialize(f_dev);
	dev_set_name(f_dev, "%s", fw_name);
	f_dev->parent = device;
	f_dev->class = &firmware_class;
	f_dev->groups = fw_dev_attr_groups;
निकास:
	वापस fw_sysfs;
पूर्ण

/**
 * fw_load_sysfs_fallback() - load a firmware via the sysfs fallback mechanism
 * @fw_sysfs: firmware sysfs inक्रमmation क्रम the firmware to load
 * @समयout: समयout to रुको क्रम the load
 *
 * In अक्षरge of स्थिरructing a sysfs fallback पूर्णांकerface क्रम firmware loading.
 **/
अटल पूर्णांक fw_load_sysfs_fallback(काष्ठा fw_sysfs *fw_sysfs, दीर्घ समयout)
अणु
	पूर्णांक retval = 0;
	काष्ठा device *f_dev = &fw_sysfs->dev;
	काष्ठा fw_priv *fw_priv = fw_sysfs->fw_priv;

	/* fall back on userspace loading */
	अगर (!fw_priv->data)
		fw_priv->is_paged_buf = true;

	dev_set_uevent_suppress(f_dev, true);

	retval = device_add(f_dev);
	अगर (retval) अणु
		dev_err(f_dev, "%s: device_register failed\n", __func__);
		जाओ err_put_dev;
	पूर्ण

	mutex_lock(&fw_lock);
	list_add(&fw_priv->pending_list, &pending_fw_head);
	mutex_unlock(&fw_lock);

	अगर (fw_priv->opt_flags & FW_OPT_UEVENT) अणु
		fw_priv->need_uevent = true;
		dev_set_uevent_suppress(f_dev, false);
		dev_dbg(f_dev, "firmware: requesting %s\n", fw_priv->fw_name);
		kobject_uevent(&fw_sysfs->dev.kobj, KOBJ_ADD);
	पूर्ण अन्यथा अणु
		समयout = MAX_JIFFY_OFFSET;
	पूर्ण

	retval = fw_sysfs_रुको_समयout(fw_priv, समयout);
	अगर (retval < 0 && retval != -ENOENT) अणु
		mutex_lock(&fw_lock);
		fw_load_पात(fw_sysfs);
		mutex_unlock(&fw_lock);
	पूर्ण

	अगर (fw_state_is_पातed(fw_priv)) अणु
		अगर (retval == -ERESTARTSYS)
			retval = -EINTR;
		अन्यथा
			retval = -EAGAIN;
	पूर्ण अन्यथा अगर (fw_priv->is_paged_buf && !fw_priv->data)
		retval = -ENOMEM;

	device_del(f_dev);
err_put_dev:
	put_device(f_dev);
	वापस retval;
पूर्ण

अटल पूर्णांक fw_load_from_user_helper(काष्ठा firmware *firmware,
				    स्थिर अक्षर *name, काष्ठा device *device,
				    u32 opt_flags)
अणु
	काष्ठा fw_sysfs *fw_sysfs;
	दीर्घ समयout;
	पूर्णांक ret;

	समयout = firmware_loading_समयout();
	अगर (opt_flags & FW_OPT_NOWAIT) अणु
		समयout = usermodehelper_पढ़ो_lock_रुको(समयout);
		अगर (!समयout) अणु
			dev_dbg(device, "firmware: %s loading timed out\n",
				name);
			वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = usermodehelper_पढ़ो_trylock();
		अगर (WARN_ON(ret)) अणु
			dev_err(device, "firmware: %s will not be loaded\n",
				name);
			वापस ret;
		पूर्ण
	पूर्ण

	fw_sysfs = fw_create_instance(firmware, name, device, opt_flags);
	अगर (IS_ERR(fw_sysfs)) अणु
		ret = PTR_ERR(fw_sysfs);
		जाओ out_unlock;
	पूर्ण

	fw_sysfs->fw_priv = firmware->priv;
	ret = fw_load_sysfs_fallback(fw_sysfs, समयout);

	अगर (!ret)
		ret = assign_fw(firmware, device);

out_unlock:
	usermodehelper_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल bool fw_क्रमce_sysfs_fallback(u32 opt_flags)
अणु
	अगर (fw_fallback_config.क्रमce_sysfs_fallback)
		वापस true;
	अगर (!(opt_flags & FW_OPT_USERHELPER))
		वापस false;
	वापस true;
पूर्ण

अटल bool fw_run_sysfs_fallback(u32 opt_flags)
अणु
	पूर्णांक ret;

	अगर (fw_fallback_config.ignore_sysfs_fallback) अणु
		pr_info_once("Ignoring firmware sysfs fallback due to sysctl knob\n");
		वापस false;
	पूर्ण

	अगर ((opt_flags & FW_OPT_NOFALLBACK_SYSFS))
		वापस false;

	/* Also permit LSMs and IMA to fail firmware sysfs fallback */
	ret = security_kernel_load_data(LOADING_FIRMWARE, true);
	अगर (ret < 0)
		वापस false;

	वापस fw_क्रमce_sysfs_fallback(opt_flags);
पूर्ण

/**
 * firmware_fallback_sysfs() - use the fallback mechanism to find firmware
 * @fw: poपूर्णांकer to firmware image
 * @name: name of firmware file to look क्रम
 * @device: device क्रम which firmware is being loaded
 * @opt_flags: options to control firmware loading behaviour, as defined by
 *	       &क्रमागत fw_opt
 * @ret: वापस value from direct lookup which triggered the fallback mechanism
 *
 * This function is called अगर direct lookup क्रम the firmware failed, it enables
 * a fallback mechanism through userspace by exposing a sysfs loading
 * पूर्णांकerface. Userspace is in अक्षरge of loading the firmware through the sysfs
 * loading पूर्णांकerface. This sysfs fallback mechanism may be disabled completely
 * on a प्रणाली by setting the proc sysctl value ignore_sysfs_fallback to true.
 * If this is false we check अगर the पूर्णांकernal API caller set the
 * @FW_OPT_NOFALLBACK_SYSFS flag, अगर so it would also disable the fallback
 * mechanism. A प्रणाली may want to enक्रमce the sysfs fallback mechanism at all
 * बार, it can करो this by setting ignore_sysfs_fallback to false and
 * क्रमce_sysfs_fallback to true.
 * Enabling क्रमce_sysfs_fallback is functionally equivalent to build a kernel
 * with CONFIG_FW_LOADER_USER_HELPER_FALLBACK.
 **/
पूर्णांक firmware_fallback_sysfs(काष्ठा firmware *fw, स्थिर अक्षर *name,
			    काष्ठा device *device,
			    u32 opt_flags,
			    पूर्णांक ret)
अणु
	अगर (!fw_run_sysfs_fallback(opt_flags))
		वापस ret;

	अगर (!(opt_flags & FW_OPT_NO_WARN))
		dev_warn(device, "Falling back to sysfs fallback for: %s\n",
				 name);
	अन्यथा
		dev_dbg(device, "Falling back to sysfs fallback for: %s\n",
				name);
	वापस fw_load_from_user_helper(fw, name, device, opt_flags);
पूर्ण
