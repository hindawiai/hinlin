<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/omapfb-sysfs.c
 *
 * Copyright (C) 2008 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#समावेश <linux/fb.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/omapfb.h>

#समावेश <video/omapfb_dss.h>
#समावेश <video/omapvrfb.h>

#समावेश "omapfb.h"

अटल sमाप_प्रकार show_rotate_type(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ofbi->rotation_type);
पूर्ण

अटल sमाप_प्रकार store_rotate_type(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_mem_region *rg;
	पूर्णांक rot_type;
	पूर्णांक r;

	r = kstrtoपूर्णांक(buf, 0, &rot_type);
	अगर (r)
		वापस r;

	अगर (rot_type != OMAP_DSS_ROT_DMA && rot_type != OMAP_DSS_ROT_VRFB)
		वापस -EINVAL;

	lock_fb_info(fbi);

	r = 0;
	अगर (rot_type == ofbi->rotation_type)
		जाओ out;

	rg = omapfb_get_mem_region(ofbi->region);

	अगर (rg->size) अणु
		r = -EBUSY;
		जाओ put_region;
	पूर्ण

	ofbi->rotation_type = rot_type;

	/*
	 * Since the VRAM क्रम this FB is not allocated at the moment we करोn't
	 * need to करो any further parameter checking at this poपूर्णांक.
	 */
put_region:
	omapfb_put_mem_region(rg);
out:
	unlock_fb_info(fbi);

	वापस r ? r : count;
पूर्ण


अटल sमाप_प्रकार show_mirror(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ofbi->mirror);
पूर्ण

अटल sमाप_प्रकार store_mirror(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	bool mirror;
	पूर्णांक r;
	काष्ठा fb_var_screeninfo new_var;

	r = strtobool(buf, &mirror);
	अगर (r)
		वापस r;

	lock_fb_info(fbi);

	ofbi->mirror = mirror;

	omapfb_get_mem_region(ofbi->region);

	स_नकल(&new_var, &fbi->var, माप(new_var));
	r = check_fb_var(fbi, &new_var);
	अगर (r)
		जाओ out;
	स_नकल(&fbi->var, &new_var, माप(fbi->var));

	set_fb_fix(fbi);

	r = omapfb_apply_changes(fbi, 0);
	अगर (r)
		जाओ out;

	r = count;
out:
	omapfb_put_mem_region(ofbi->region);

	unlock_fb_info(fbi);

	वापस r;
पूर्ण

अटल sमाप_प्रकार show_overlays(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	sमाप_प्रकार l = 0;
	पूर्णांक t;

	lock_fb_info(fbi);
	omapfb_lock(fbdev);

	क्रम (t = 0; t < ofbi->num_overlays; t++) अणु
		काष्ठा omap_overlay *ovl = ofbi->overlays[t];
		पूर्णांक ovlnum;

		क्रम (ovlnum = 0; ovlnum < fbdev->num_overlays; ++ovlnum)
			अगर (ovl == fbdev->overlays[ovlnum])
				अवरोध;

		l += scnम_लिखो(buf + l, PAGE_SIZE - l, "%s%d",
				t == 0 ? "" : ",", ovlnum);
	पूर्ण

	l += scnम_लिखो(buf + l, PAGE_SIZE - l, "\n");

	omapfb_unlock(fbdev);
	unlock_fb_info(fbi);

	वापस l;
पूर्ण

अटल काष्ठा omapfb_info *get_overlay_fb(काष्ठा omapfb2_device *fbdev,
		काष्ठा omap_overlay *ovl)
अणु
	पूर्णांक i, t;

	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		काष्ठा omapfb_info *ofbi = FB2OFB(fbdev->fbs[i]);

		क्रम (t = 0; t < ofbi->num_overlays; t++) अणु
			अगर (ofbi->overlays[t] == ovl)
				वापस ofbi;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार store_overlays(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omap_overlay *ovls[OMAPFB_MAX_OVL_PER_FB];
	काष्ठा omap_overlay *ovl;
	पूर्णांक num_ovls, r, i;
	पूर्णांक len;
	bool added = false;

	num_ovls = 0;

	len = म_माप(buf);
	अगर (buf[len - 1] == '\n')
		len = len - 1;

	lock_fb_info(fbi);
	omapfb_lock(fbdev);

	अगर (len > 0) अणु
		अक्षर *p = (अक्षर *)buf;
		पूर्णांक ovlnum;

		जबतक (p < buf + len) अणु
			पूर्णांक found;
			अगर (num_ovls == OMAPFB_MAX_OVL_PER_FB) अणु
				r = -EINVAL;
				जाओ out;
			पूर्ण

			ovlnum = simple_म_से_अदीर्घ(p, &p, 0);
			अगर (ovlnum > fbdev->num_overlays) अणु
				r = -EINVAL;
				जाओ out;
			पूर्ण

			found = 0;
			क्रम (i = 0; i < num_ovls; ++i) अणु
				अगर (ovls[i] == fbdev->overlays[ovlnum]) अणु
					found = 1;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (!found)
				ovls[num_ovls++] = fbdev->overlays[ovlnum];

			p++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_ovls; ++i) अणु
		काष्ठा omapfb_info *ofbi2 = get_overlay_fb(fbdev, ovls[i]);
		अगर (ofbi2 && ofbi2 != ofbi) अणु
			dev_err(fbdev->dev, "overlay already in use\n");
			r = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/* detach unused overlays */
	क्रम (i = 0; i < ofbi->num_overlays; ++i) अणु
		पूर्णांक t, found;

		ovl = ofbi->overlays[i];

		found = 0;

		क्रम (t = 0; t < num_ovls; ++t) अणु
			अगर (ovl == ovls[t]) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (found)
			जारी;

		DBG("detaching %d\n", ofbi->overlays[i]->id);

		omapfb_get_mem_region(ofbi->region);

		omapfb_overlay_enable(ovl, 0);

		अगर (ovl->manager)
			ovl->manager->apply(ovl->manager);

		omapfb_put_mem_region(ofbi->region);

		क्रम (t = i + 1; t < ofbi->num_overlays; t++) अणु
			ofbi->rotation[t-1] = ofbi->rotation[t];
			ofbi->overlays[t-1] = ofbi->overlays[t];
		पूर्ण

		ofbi->num_overlays--;
		i--;
	पूर्ण

	क्रम (i = 0; i < num_ovls; ++i) अणु
		पूर्णांक t, found;

		ovl = ovls[i];

		found = 0;

		क्रम (t = 0; t < ofbi->num_overlays; ++t) अणु
			अगर (ovl == ofbi->overlays[t]) अणु
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (found)
			जारी;
		ofbi->rotation[ofbi->num_overlays] = 0;
		ofbi->overlays[ofbi->num_overlays++] = ovl;

		added = true;
	पूर्ण

	अगर (added) अणु
		omapfb_get_mem_region(ofbi->region);

		r = omapfb_apply_changes(fbi, 0);

		omapfb_put_mem_region(ofbi->region);

		अगर (r)
			जाओ out;
	पूर्ण

	r = count;
out:
	omapfb_unlock(fbdev);
	unlock_fb_info(fbi);

	वापस r;
पूर्ण

अटल sमाप_प्रकार show_overlays_rotate(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	sमाप_प्रकार l = 0;
	पूर्णांक t;

	lock_fb_info(fbi);

	क्रम (t = 0; t < ofbi->num_overlays; t++) अणु
		l += scnम_लिखो(buf + l, PAGE_SIZE - l, "%s%d",
				t == 0 ? "" : ",", ofbi->rotation[t]);
	पूर्ण

	l += scnम_लिखो(buf + l, PAGE_SIZE - l, "\n");

	unlock_fb_info(fbi);

	वापस l;
पूर्ण

अटल sमाप_प्रकार store_overlays_rotate(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	पूर्णांक num_ovls = 0, r, i;
	पूर्णांक len;
	bool changed = false;
	u8 rotation[OMAPFB_MAX_OVL_PER_FB];

	len = म_माप(buf);
	अगर (buf[len - 1] == '\n')
		len = len - 1;

	lock_fb_info(fbi);

	अगर (len > 0) अणु
		अक्षर *p = (अक्षर *)buf;

		जबतक (p < buf + len) अणु
			पूर्णांक rot;

			अगर (num_ovls == ofbi->num_overlays) अणु
				r = -EINVAL;
				जाओ out;
			पूर्ण

			rot = simple_म_से_अदीर्घ(p, &p, 0);
			अगर (rot < 0 || rot > 3) अणु
				r = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (ofbi->rotation[num_ovls] != rot)
				changed = true;

			rotation[num_ovls++] = rot;

			p++;
		पूर्ण
	पूर्ण

	अगर (num_ovls != ofbi->num_overlays) अणु
		r = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (changed) अणु
		क्रम (i = 0; i < num_ovls; ++i)
			ofbi->rotation[i] = rotation[i];

		omapfb_get_mem_region(ofbi->region);

		r = omapfb_apply_changes(fbi, 0);

		omapfb_put_mem_region(ofbi->region);

		अगर (r)
			जाओ out;

		/* FIXME error handling? */
	पूर्ण

	r = count;
out:
	unlock_fb_info(fbi);

	वापस r;
पूर्ण

अटल sमाप_प्रकार show_size(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);

	वापस snम_लिखो(buf, PAGE_SIZE, "%lu\n", ofbi->region->size);
पूर्ण

अटल sमाप_प्रकार store_size(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omap_dss_device *display = fb2display(fbi);
	काष्ठा omapfb2_mem_region *rg;
	अचिन्हित दीर्घ size;
	पूर्णांक r;
	पूर्णांक i;

	r = kम_से_अदीर्घ(buf, 0, &size);
	अगर (r)
		वापस r;

	size = PAGE_ALIGN(size);

	lock_fb_info(fbi);

	अगर (display && display->driver->sync)
		display->driver->sync(display);

	rg = ofbi->region;

	करोwn_ग_लिखो_nested(&rg->lock, rg->id);
	atomic_inc(&rg->lock_count);

	अगर (atomic_पढ़ो(&rg->map_count)) अणु
		r = -EBUSY;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		काष्ठा omapfb_info *ofbi2 = FB2OFB(fbdev->fbs[i]);
		पूर्णांक j;

		अगर (ofbi2->region != rg)
			जारी;

		क्रम (j = 0; j < ofbi2->num_overlays; j++) अणु
			काष्ठा omap_overlay *ovl;
			ovl = ofbi2->overlays[j];
			अगर (ovl->is_enabled(ovl)) अणु
				r = -EBUSY;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (size != ofbi->region->size) अणु
		r = omapfb_पुनः_स्मृति_fbmem(fbi, size, ofbi->region->type);
		अगर (r) अणु
			dev_err(dev, "realloc fbmem failed\n");
			जाओ out;
		पूर्ण
	पूर्ण

	r = count;
out:
	atomic_dec(&rg->lock_count);
	up_ग_लिखो(&rg->lock);

	unlock_fb_info(fbi);

	वापस r;
पूर्ण

अटल sमाप_प्रकार show_phys(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);

	वापस snम_लिखो(buf, PAGE_SIZE, "%0x\n", ofbi->region->paddr);
पूर्ण

अटल sमाप_प्रकार show_virt(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);

	वापस snम_लिखो(buf, PAGE_SIZE, "%p\n", ofbi->region->vaddr);
पूर्ण

अटल sमाप_प्रकार show_upd_mode(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	क्रमागत omapfb_update_mode mode;
	पूर्णांक r;

	r = omapfb_get_update_mode(fbi, &mode);

	अगर (r)
		वापस r;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", (अचिन्हित)mode);
पूर्ण

अटल sमाप_प्रकार store_upd_mode(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fbi = dev_get_drvdata(dev);
	अचिन्हित mode;
	पूर्णांक r;

	r = kstrtouपूर्णांक(buf, 0, &mode);
	अगर (r)
		वापस r;

	r = omapfb_set_update_mode(fbi, mode);
	अगर (r)
		वापस r;

	वापस count;
पूर्ण

अटल काष्ठा device_attribute omapfb_attrs[] = अणु
	__ATTR(rotate_type, S_IRUGO | S_IWUSR, show_rotate_type,
			store_rotate_type),
	__ATTR(mirror, S_IRUGO | S_IWUSR, show_mirror, store_mirror),
	__ATTR(size, S_IRUGO | S_IWUSR, show_size, store_size),
	__ATTR(overlays, S_IRUGO | S_IWUSR, show_overlays, store_overlays),
	__ATTR(overlays_rotate, S_IRUGO | S_IWUSR, show_overlays_rotate,
			store_overlays_rotate),
	__ATTR(phys_addr, S_IRUGO, show_phys, शून्य),
	__ATTR(virt_addr, S_IRUGO, show_virt, शून्य),
	__ATTR(update_mode, S_IRUGO | S_IWUSR, show_upd_mode, store_upd_mode),
पूर्ण;

पूर्णांक omapfb_create_sysfs(काष्ठा omapfb2_device *fbdev)
अणु
	पूर्णांक i;
	पूर्णांक r;

	DBG("create sysfs for fbs\n");
	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		पूर्णांक t;
		क्रम (t = 0; t < ARRAY_SIZE(omapfb_attrs); t++) अणु
			r = device_create_file(fbdev->fbs[i]->dev,
					&omapfb_attrs[t]);

			अगर (r) अणु
				dev_err(fbdev->dev, "failed to create sysfs "
						"file\n");
				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम omapfb_हटाओ_sysfs(काष्ठा omapfb2_device *fbdev)
अणु
	पूर्णांक i, t;

	DBG("remove sysfs for fbs\n");
	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		क्रम (t = 0; t < ARRAY_SIZE(omapfb_attrs); t++)
			device_हटाओ_file(fbdev->fbs[i]->dev,
					&omapfb_attrs[t]);
	पूर्ण
पूर्ण

