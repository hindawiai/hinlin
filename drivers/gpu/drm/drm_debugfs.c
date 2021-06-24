<शैली गुरु>
/*
 * Created: Sun Dec 21 13:08:50 2008 by bgamari@gmail.com
 *
 * Copyright 2008 Ben Gamari <bgamari@gmail.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_auth.h>
#समावेश <drm/drm_client.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_gem.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"

#अगर defined(CONFIG_DEBUG_FS)

/***************************************************
 * Initialization, etc.
 **************************************************/

अटल पूर्णांक drm_name_info(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_minor *minor = node->minor;
	काष्ठा drm_device *dev = minor->dev;
	काष्ठा drm_master *master;

	mutex_lock(&dev->master_mutex);
	master = dev->master;
	seq_म_लिखो(m, "%s", dev->driver->name);
	अगर (dev->dev)
		seq_म_लिखो(m, " dev=%s", dev_name(dev->dev));
	अगर (master && master->unique)
		seq_म_लिखो(m, " master=%s", master->unique);
	अगर (dev->unique)
		seq_म_लिखो(m, " unique=%s", dev->unique);
	seq_म_लिखो(m, "\n");
	mutex_unlock(&dev->master_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक drm_clients_info(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा drm_file *priv;
	kuid_t uid;

	seq_म_लिखो(m,
		   "%20s %5s %3s master a %5s %10s\n",
		   "command",
		   "pid",
		   "dev",
		   "uid",
		   "magic");

	/* dev->filelist is sorted youngest first, but we want to present
	 * oldest first (i.e. kernel, servers, clients), so walk backwardss.
	 */
	mutex_lock(&dev->filelist_mutex);
	list_क्रम_each_entry_reverse(priv, &dev->filelist, lhead) अणु
		काष्ठा task_काष्ठा *task;

		rcu_पढ़ो_lock(); /* locks pid_task()->comm */
		task = pid_task(priv->pid, PIDTYPE_PID);
		uid = task ? __task_cred(task)->euid : GLOBAL_ROOT_UID;
		seq_म_लिखो(m, "%20s %5d %3d   %c    %c %5d %10u\n",
			   task ? task->comm : "<unknown>",
			   pid_vnr(priv->pid),
			   priv->minor->index,
			   drm_is_current_master(priv) ? 'y' : 'n',
			   priv->authenticated ? 'y' : 'n',
			   from_kuid_munged(seq_user_ns(m), uid),
			   priv->magic);
		rcu_पढ़ो_unlock();
	पूर्ण
	mutex_unlock(&dev->filelist_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक drm_gem_one_name_info(पूर्णांक id, व्योम *ptr, व्योम *data)
अणु
	काष्ठा drm_gem_object *obj = ptr;
	काष्ठा seq_file *m = data;

	seq_म_लिखो(m, "%6d %8zd %7d %8d\n",
		   obj->name, obj->size,
		   obj->handle_count,
		   kref_पढ़ो(&obj->refcount));
	वापस 0;
पूर्ण

अटल पूर्णांक drm_gem_name_info(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;

	seq_म_लिखो(m, "  name     size handles refcount\n");

	mutex_lock(&dev->object_name_lock);
	idr_क्रम_each(&dev->object_name_idr, drm_gem_one_name_info, m);
	mutex_unlock(&dev->object_name_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_info_list drm_debugfs_list[] = अणु
	अणु"name", drm_name_info, 0पूर्ण,
	अणु"clients", drm_clients_info, 0पूर्ण,
	अणु"gem_names", drm_gem_name_info, DRIVER_GEMपूर्ण,
पूर्ण;
#घोषणा DRM_DEBUGFS_ENTRIES ARRAY_SIZE(drm_debugfs_list)


अटल पूर्णांक drm_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_info_node *node = inode->i_निजी;

	वापस single_खोलो(file, node->info_ent->show, node);
पूर्ण


अटल स्थिर काष्ठा file_operations drm_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_debugfs_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;


/**
 * drm_debugfs_create_files - Initialize a given set of debugfs files क्रम DRM
 * 			minor
 * @files: The array of files to create
 * @count: The number of files given
 * @root: DRI debugfs dir entry.
 * @minor: device minor number
 *
 * Create a given set of debugfs files represented by an array of
 * &काष्ठा drm_info_list in the given root directory. These files will be हटाओd
 * स्वतःmatically on drm_debugfs_cleanup().
 */
व्योम drm_debugfs_create_files(स्थिर काष्ठा drm_info_list *files, पूर्णांक count,
			      काष्ठा dentry *root, काष्ठा drm_minor *minor)
अणु
	काष्ठा drm_device *dev = minor->dev;
	काष्ठा drm_info_node *पंचांगp;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		u32 features = files[i].driver_features;

		अगर (features && !drm_core_check_all_features(dev, features))
			जारी;

		पंचांगp = kदो_स्मृति(माप(काष्ठा drm_info_node), GFP_KERNEL);
		अगर (पंचांगp == शून्य)
			जारी;

		पंचांगp->minor = minor;
		पंचांगp->dent = debugfs_create_file(files[i].name,
						S_IFREG | S_IRUGO, root, पंचांगp,
						&drm_debugfs_fops);
		पंचांगp->info_ent = &files[i];

		mutex_lock(&minor->debugfs_lock);
		list_add(&पंचांगp->list, &minor->debugfs_list);
		mutex_unlock(&minor->debugfs_lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_debugfs_create_files);

पूर्णांक drm_debugfs_init(काष्ठा drm_minor *minor, पूर्णांक minor_id,
		     काष्ठा dentry *root)
अणु
	काष्ठा drm_device *dev = minor->dev;
	अक्षर name[64];

	INIT_LIST_HEAD(&minor->debugfs_list);
	mutex_init(&minor->debugfs_lock);
	प्र_लिखो(name, "%d", minor_id);
	minor->debugfs_root = debugfs_create_dir(name, root);

	drm_debugfs_create_files(drm_debugfs_list, DRM_DEBUGFS_ENTRIES,
				 minor->debugfs_root, minor);

	अगर (drm_drv_uses_atomic_modeset(dev)) अणु
		drm_atomic_debugfs_init(minor);
	पूर्ण

	अगर (drm_core_check_feature(dev, DRIVER_MODESET)) अणु
		drm_framebuffer_debugfs_init(minor);

		drm_client_debugfs_init(minor);
	पूर्ण

	अगर (dev->driver->debugfs_init)
		dev->driver->debugfs_init(minor);

	वापस 0;
पूर्ण


पूर्णांक drm_debugfs_हटाओ_files(स्थिर काष्ठा drm_info_list *files, पूर्णांक count,
			     काष्ठा drm_minor *minor)
अणु
	काष्ठा list_head *pos, *q;
	काष्ठा drm_info_node *पंचांगp;
	पूर्णांक i;

	mutex_lock(&minor->debugfs_lock);
	क्रम (i = 0; i < count; i++) अणु
		list_क्रम_each_safe(pos, q, &minor->debugfs_list) अणु
			पंचांगp = list_entry(pos, काष्ठा drm_info_node, list);
			अगर (पंचांगp->info_ent == &files[i]) अणु
				debugfs_हटाओ(पंचांगp->dent);
				list_del(pos);
				kमुक्त(पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&minor->debugfs_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_debugfs_हटाओ_files);

अटल व्योम drm_debugfs_हटाओ_all_files(काष्ठा drm_minor *minor)
अणु
	काष्ठा drm_info_node *node, *पंचांगp;

	mutex_lock(&minor->debugfs_lock);
	list_क्रम_each_entry_safe(node, पंचांगp, &minor->debugfs_list, list) अणु
		debugfs_हटाओ(node->dent);
		list_del(&node->list);
		kमुक्त(node);
	पूर्ण
	mutex_unlock(&minor->debugfs_lock);
पूर्ण

व्योम drm_debugfs_cleanup(काष्ठा drm_minor *minor)
अणु
	अगर (!minor->debugfs_root)
		वापस;

	drm_debugfs_हटाओ_all_files(minor);

	debugfs_हटाओ_recursive(minor->debugfs_root);
	minor->debugfs_root = शून्य;
पूर्ण

अटल पूर्णांक connector_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_connector *connector = m->निजी;

	seq_म_लिखो(m, "%s\n", drm_get_connector_क्रमce_name(connector->क्रमce));

	वापस 0;
पूर्ण

अटल पूर्णांक connector_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_connector *dev = inode->i_निजी;

	वापस single_खोलो(file, connector_show, dev);
पूर्ण

अटल sमाप_प्रकार connector_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			       माप_प्रकार len, loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा drm_connector *connector = m->निजी;
	अक्षर buf[12];

	अगर (len > माप(buf) - 1)
		वापस -EINVAL;

	अगर (copy_from_user(buf, ubuf, len))
		वापस -EFAULT;

	buf[len] = '\0';

	अगर (sysfs_streq(buf, "on"))
		connector->क्रमce = DRM_FORCE_ON;
	अन्यथा अगर (sysfs_streq(buf, "digital"))
		connector->क्रमce = DRM_FORCE_ON_DIGITAL;
	अन्यथा अगर (sysfs_streq(buf, "off"))
		connector->क्रमce = DRM_FORCE_OFF;
	अन्यथा अगर (sysfs_streq(buf, "unspecified"))
		connector->क्रमce = DRM_FORCE_UNSPECIFIED;
	अन्यथा
		वापस -EINVAL;

	वापस len;
पूर्ण

अटल पूर्णांक edid_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_connector *connector = m->निजी;
	काष्ठा drm_property_blob *edid = connector->edid_blob_ptr;

	अगर (connector->override_edid && edid)
		seq_ग_लिखो(m, edid->data, edid->length);

	वापस 0;
पूर्ण

अटल पूर्णांक edid_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_connector *dev = inode->i_निजी;

	वापस single_खोलो(file, edid_show, dev);
पूर्ण

अटल sमाप_प्रकार edid_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			  माप_प्रकार len, loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा drm_connector *connector = m->निजी;
	अक्षर *buf;
	काष्ठा edid *edid;
	पूर्णांक ret;

	buf = memdup_user(ubuf, len);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	edid = (काष्ठा edid *) buf;

	अगर (len == 5 && !म_भेदन(buf, "reset", 5)) अणु
		connector->override_edid = false;
		ret = drm_connector_update_edid_property(connector, शून्य);
	पूर्ण अन्यथा अगर (len < EDID_LENGTH ||
		   EDID_LENGTH * (1 + edid->extensions) > len)
		ret = -EINVAL;
	अन्यथा अणु
		connector->override_edid = false;
		ret = drm_connector_update_edid_property(connector, edid);
		अगर (!ret)
			connector->override_edid = true;
	पूर्ण

	kमुक्त(buf);

	वापस (ret) ? ret : len;
पूर्ण

/*
 * Returns the min and max vrr vfreq through the connector's debugfs file.
 * Example usage: cat /sys/kernel/debug/dri/0/DP-1/vrr_range
 */
अटल पूर्णांक vrr_range_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_connector *connector = m->निजी;

	अगर (connector->status != connector_status_connected)
		वापस -ENODEV;

	seq_म_लिखो(m, "Min: %u\n", (u8)connector->display_info.monitor_range.min_vfreq);
	seq_म_लिखो(m, "Max: %u\n", (u8)connector->display_info.monitor_range.max_vfreq);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(vrr_range);

अटल स्थिर काष्ठा file_operations drm_edid_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = edid_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = edid_ग_लिखो
पूर्ण;


अटल स्थिर काष्ठा file_operations drm_connector_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = connector_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
	.ग_लिखो = connector_ग_लिखो
पूर्ण;

व्योम drm_debugfs_connector_add(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_minor *minor = connector->dev->primary;
	काष्ठा dentry *root;

	अगर (!minor->debugfs_root)
		वापस;

	root = debugfs_create_dir(connector->name, minor->debugfs_root);
	connector->debugfs_entry = root;

	/* क्रमce */
	debugfs_create_file("force", S_IRUGO | S_IWUSR, root, connector,
			    &drm_connector_fops);

	/* edid */
	debugfs_create_file("edid_override", S_IRUGO | S_IWUSR, root, connector,
			    &drm_edid_fops);

	/* vrr range */
	debugfs_create_file("vrr_range", S_IRUGO, root, connector,
			    &vrr_range_fops);
पूर्ण

व्योम drm_debugfs_connector_हटाओ(काष्ठा drm_connector *connector)
अणु
	अगर (!connector->debugfs_entry)
		वापस;

	debugfs_हटाओ_recursive(connector->debugfs_entry);

	connector->debugfs_entry = शून्य;
पूर्ण

व्योम drm_debugfs_crtc_add(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_minor *minor = crtc->dev->primary;
	काष्ठा dentry *root;
	अक्षर *name;

	name = kaप्र_लिखो(GFP_KERNEL, "crtc-%d", crtc->index);
	अगर (!name)
		वापस;

	root = debugfs_create_dir(name, minor->debugfs_root);
	kमुक्त(name);

	crtc->debugfs_entry = root;

	drm_debugfs_crtc_crc_add(crtc);
पूर्ण

व्योम drm_debugfs_crtc_हटाओ(काष्ठा drm_crtc *crtc)
अणु
	debugfs_हटाओ_recursive(crtc->debugfs_entry);
	crtc->debugfs_entry = शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */
