<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright तऊ 2014 Broadcom
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>

#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

काष्ठा vc4_debugfs_info_entry अणु
	काष्ठा list_head link;
	काष्ठा drm_info_list info;
पूर्ण;

/*
 * Called at drm_dev_रेजिस्टर() समय on each of the minors रेजिस्टरed
 * by the DRM device, to attach the debugfs files.
 */
व्योम
vc4_debugfs_init(काष्ठा drm_minor *minor)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(minor->dev);
	काष्ठा vc4_debugfs_info_entry *entry;

	debugfs_create_bool("hvs_load_tracker", S_IRUGO | S_IWUSR,
			    minor->debugfs_root, &vc4->load_tracker_enabled);

	list_क्रम_each_entry(entry, &vc4->debugfs_list, link) अणु
		drm_debugfs_create_files(&entry->info, 1,
					 minor->debugfs_root, minor);
	पूर्ण
पूर्ण

अटल पूर्णांक vc4_debugfs_regset32(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा debugfs_regset32 *regset = node->info_ent->data;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	drm_prपूर्णांक_regset32(&p, regset);

	वापस 0;
पूर्ण

/*
 * Registers a debugfs file with a callback function क्रम a vc4 component.
 *
 * This is like drm_debugfs_create_files(), but that can only be
 * called a given DRM minor, जबतक the various VC4 components want to
 * रेजिस्टर their debugfs files during the component bind process.  We
 * track the request and delay it to be called on each minor during
 * vc4_debugfs_init().
 */
व्योम vc4_debugfs_add_file(काष्ठा drm_device *dev,
			  स्थिर अक्षर *name,
			  पूर्णांक (*show)(काष्ठा seq_file*, व्योम*),
			  व्योम *data)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	काष्ठा vc4_debugfs_info_entry *entry =
		devm_kzalloc(dev->dev, माप(*entry), GFP_KERNEL);

	अगर (!entry)
		वापस;

	entry->info.name = name;
	entry->info.show = show;
	entry->info.data = data;

	list_add(&entry->link, &vc4->debugfs_list);
पूर्ण

व्योम vc4_debugfs_add_regset32(काष्ठा drm_device *drm,
			      स्थिर अक्षर *name,
			      काष्ठा debugfs_regset32 *regset)
अणु
	vc4_debugfs_add_file(drm, name, vc4_debugfs_regset32, regset);
पूर्ण
