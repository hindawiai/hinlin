<शैली गुरु>
/*
 * Copyright (C) 2009 Red Hat <bskeggs@redhat.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

/*
 * Authors:
 *  Ben Skeggs <bskeggs@redhat.com>
 */

#समावेश <linux/debugfs.h>
#समावेश <nvअगर/class.h>
#समावेश <nvअगर/अगर0001.h>
#समावेश "nouveau_debugfs.h"
#समावेश "nouveau_drv.h"

अटल पूर्णांक
nouveau_debugfs_vbios_image(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा nouveau_drm *drm = nouveau_drm(node->minor->dev);
	पूर्णांक i;

	क्रम (i = 0; i < drm->vbios.length; i++)
		seq_म_लिखो(m, "%c", drm->vbios.data[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_debugfs_strap_peek(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = m->निजी;
	काष्ठा nouveau_drm *drm = nouveau_drm(node->minor->dev);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(drm->dev->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_put_स्वतःsuspend(drm->dev->dev);
		वापस ret;
	पूर्ण

	seq_म_लिखो(m, "0x%08x\n",
		   nvअगर_rd32(&drm->client.device.object, 0x101000));

	pm_runसमय_mark_last_busy(drm->dev->dev);
	pm_runसमय_put_स्वतःsuspend(drm->dev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक
nouveau_debugfs_pstate_get(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_device *drm = m->निजी;
	काष्ठा nouveau_debugfs *debugfs = nouveau_debugfs(drm);
	काष्ठा nvअगर_object *ctrl = &debugfs->ctrl;
	काष्ठा nvअगर_control_pstate_info_v0 info = अणुपूर्ण;
	पूर्णांक ret, i;

	अगर (!debugfs)
		वापस -ENODEV;

	ret = nvअगर_mthd(ctrl, NVIF_CONTROL_PSTATE_INFO, &info, माप(info));
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < info.count + 1; i++) अणु
		स्थिर s32 state = i < info.count ? i :
			NVIF_CONTROL_PSTATE_ATTR_V0_STATE_CURRENT;
		काष्ठा nvअगर_control_pstate_attr_v0 attr = अणु
			.state = state,
			.index = 0,
		पूर्ण;

		ret = nvअगर_mthd(ctrl, NVIF_CONTROL_PSTATE_ATTR,
				&attr, माप(attr));
		अगर (ret)
			वापस ret;

		अगर (i < info.count)
			seq_म_लिखो(m, "%02x:", attr.state);
		अन्यथा
			seq_म_लिखो(m, "%s:", info.pwrsrc == 0 ? "DC" :
					     info.pwrsrc == 1 ? "AC" : "--");

		attr.index = 0;
		करो अणु
			attr.state = state;
			ret = nvअगर_mthd(ctrl, NVIF_CONTROL_PSTATE_ATTR,
					&attr, माप(attr));
			अगर (ret)
				वापस ret;

			seq_म_लिखो(m, " %s %d", attr.name, attr.min);
			अगर (attr.min != attr.max)
				seq_म_लिखो(m, "-%d", attr.max);
			seq_म_लिखो(m, " %s", attr.unit);
		पूर्ण जबतक (attr.index);

		अगर (state >= 0) अणु
			अगर (info.ustate_ac == state)
				seq_म_लिखो(m, " AC");
			अगर (info.ustate_dc == state)
				seq_म_लिखो(m, " DC");
			अगर (info.pstate == state)
				seq_म_लिखो(m, " *");
		पूर्ण अन्यथा अणु
			अगर (info.ustate_ac < -1)
				seq_म_लिखो(m, " AC");
			अगर (info.ustate_dc < -1)
				seq_म_लिखो(m, " DC");
		पूर्ण

		seq_म_लिखो(m, "\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
nouveau_debugfs_pstate_set(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			   माप_प्रकार len, loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा drm_device *drm = m->निजी;
	काष्ठा nouveau_debugfs *debugfs = nouveau_debugfs(drm);
	काष्ठा nvअगर_object *ctrl = &debugfs->ctrl;
	काष्ठा nvअगर_control_pstate_user_v0 args = अणु .pwrsrc = -EINVAL पूर्ण;
	अक्षर buf[32] = अणुपूर्ण, *पंचांगp, *cur = buf;
	दीर्घ value, ret;

	अगर (!debugfs)
		वापस -ENODEV;

	अगर (len >= माप(buf))
		वापस -EINVAL;

	अगर (copy_from_user(buf, ubuf, len))
		वापस -EFAULT;

	अगर ((पंचांगp = म_अक्षर(buf, '\n')))
		*पंचांगp = '\0';

	अगर (!strnहालcmp(cur, "dc:", 3)) अणु
		args.pwrsrc = 0;
		cur += 3;
	पूर्ण अन्यथा
	अगर (!strnहालcmp(cur, "ac:", 3)) अणु
		args.pwrsrc = 1;
		cur += 3;
	पूर्ण

	अगर (!strहालcmp(cur, "none"))
		args.ustate = NVIF_CONTROL_PSTATE_USER_V0_STATE_UNKNOWN;
	अन्यथा
	अगर (!strहालcmp(cur, "auto"))
		args.ustate = NVIF_CONTROL_PSTATE_USER_V0_STATE_PERFMON;
	अन्यथा अणु
		ret = kम_से_दीर्घ(cur, 16, &value);
		अगर (ret)
			वापस ret;
		args.ustate = value;
	पूर्ण

	ret = pm_runसमय_get_sync(drm->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_put_स्वतःsuspend(drm->dev);
		वापस ret;
	पूर्ण

	ret = nvअगर_mthd(ctrl, NVIF_CONTROL_PSTATE_USER, &args, माप(args));
	pm_runसमय_put_स्वतःsuspend(drm->dev);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण

अटल पूर्णांक
nouveau_debugfs_pstate_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, nouveau_debugfs_pstate_get, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations nouveau_pstate_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = nouveau_debugfs_pstate_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = nouveau_debugfs_pstate_set,
पूर्ण;

अटल काष्ठा drm_info_list nouveau_debugfs_list[] = अणु
	अणु "vbios.rom",  nouveau_debugfs_vbios_image, 0, शून्य पूर्ण,
	अणु "strap_peek", nouveau_debugfs_strap_peek, 0, शून्य पूर्ण,
पूर्ण;
#घोषणा NOUVEAU_DEBUGFS_ENTRIES ARRAY_SIZE(nouveau_debugfs_list)

अटल स्थिर काष्ठा nouveau_debugfs_files अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा file_operations *fops;
पूर्ण nouveau_debugfs_files[] = अणु
	अणु"pstate", &nouveau_pstate_fopsपूर्ण,
पूर्ण;

व्योम
nouveau_drm_debugfs_init(काष्ठा drm_minor *minor)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(minor->dev);
	काष्ठा dentry *dentry;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nouveau_debugfs_files); i++) अणु
		debugfs_create_file(nouveau_debugfs_files[i].name,
				    S_IRUGO | S_IWUSR,
				    minor->debugfs_root, minor->dev,
				    nouveau_debugfs_files[i].fops);
	पूर्ण

	drm_debugfs_create_files(nouveau_debugfs_list,
				 NOUVEAU_DEBUGFS_ENTRIES,
				 minor->debugfs_root, minor);

	/* Set the size of the vbios since we know it, and it's confusing to
	 * userspace अगर it wants to seek() but the file has a length of 0
	 */
	dentry = debugfs_lookup("vbios.rom", minor->debugfs_root);
	अगर (!dentry)
		वापस;

	d_inode(dentry)->i_size = drm->vbios.length;
	dput(dentry);
पूर्ण

पूर्णांक
nouveau_debugfs_init(काष्ठा nouveau_drm *drm)
अणु
	पूर्णांक ret;

	drm->debugfs = kzalloc(माप(*drm->debugfs), GFP_KERNEL);
	अगर (!drm->debugfs)
		वापस -ENOMEM;

	ret = nvअगर_object_ctor(&drm->client.device.object, "debugfsCtrl", 0,
			       NVIF_CLASS_CONTROL, शून्य, 0,
			       &drm->debugfs->ctrl);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

व्योम
nouveau_debugfs_fini(काष्ठा nouveau_drm *drm)
अणु
	अगर (drm->debugfs && drm->debugfs->ctrl.priv)
		nvअगर_object_dtor(&drm->debugfs->ctrl);

	kमुक्त(drm->debugfs);
	drm->debugfs = शून्य;
पूर्ण
