<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Debug support क्रम HID Nपूर्णांकenकरो Wii / Wii U peripherals
 * Copyright (c) 2011-2013 David Herrmann <dh.herrmann@gmail.com>
 */

/*
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश "hid-wiimote.h"

काष्ठा wiimote_debug अणु
	काष्ठा wiimote_data *wdata;
	काष्ठा dentry *eeprom;
	काष्ठा dentry *drm;
पूर्ण;

अटल sमाप_प्रकार wiidebug_eeprom_पढ़ो(काष्ठा file *f, अक्षर __user *u, माप_प्रकार s,
								loff_t *off)
अणु
	काष्ठा wiimote_debug *dbg = f->निजी_data;
	काष्ठा wiimote_data *wdata = dbg->wdata;
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार ret;
	अक्षर buf[16];
	__u16 size = 0;

	अगर (s == 0)
		वापस -EINVAL;
	अगर (*off > 0xffffff)
		वापस 0;
	अगर (s > 16)
		s = 16;

	ret = wiimote_cmd_acquire(wdata);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.cmd_पढ़ो_size = s;
	wdata->state.cmd_पढ़ो_buf = buf;
	wiimote_cmd_set(wdata, WIIPROTO_REQ_RMEM, *off & 0xffff);
	wiiproto_req_reeprom(wdata, *off, s);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	ret = wiimote_cmd_रुको(wdata);
	अगर (!ret)
		size = wdata->state.cmd_पढ़ो_size;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.cmd_पढ़ो_buf = शून्य;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	wiimote_cmd_release(wdata);

	अगर (ret)
		वापस ret;
	अन्यथा अगर (size == 0)
		वापस -EIO;

	अगर (copy_to_user(u, buf, size))
		वापस -EFAULT;

	*off += size;
	ret = size;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations wiidebug_eeprom_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = wiidebug_eeprom_पढ़ो,
	.llseek = generic_file_llseek,
पूर्ण;

अटल स्थिर अक्षर *wiidebug_drmmap[] = अणु
	[WIIPROTO_REQ_शून्य] = "NULL",
	[WIIPROTO_REQ_DRM_K] = "K",
	[WIIPROTO_REQ_DRM_KA] = "KA",
	[WIIPROTO_REQ_DRM_KE] = "KE",
	[WIIPROTO_REQ_DRM_KAI] = "KAI",
	[WIIPROTO_REQ_DRM_KEE] = "KEE",
	[WIIPROTO_REQ_DRM_KAE] = "KAE",
	[WIIPROTO_REQ_DRM_KIE] = "KIE",
	[WIIPROTO_REQ_DRM_KAIE] = "KAIE",
	[WIIPROTO_REQ_DRM_E] = "E",
	[WIIPROTO_REQ_DRM_SKAI1] = "SKAI1",
	[WIIPROTO_REQ_DRM_SKAI2] = "SKAI2",
	[WIIPROTO_REQ_MAX] = शून्य
पूर्ण;

अटल पूर्णांक wiidebug_drm_show(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा wiimote_debug *dbg = f->निजी;
	स्थिर अक्षर *str = शून्य;
	अचिन्हित दीर्घ flags;
	__u8 drm;

	spin_lock_irqsave(&dbg->wdata->state.lock, flags);
	drm = dbg->wdata->state.drm;
	spin_unlock_irqrestore(&dbg->wdata->state.lock, flags);

	अगर (drm < WIIPROTO_REQ_MAX)
		str = wiidebug_drmmap[drm];
	अगर (!str)
		str = "unknown";

	seq_म_लिखो(f, "%s\n", str);

	वापस 0;
पूर्ण

अटल पूर्णांक wiidebug_drm_खोलो(काष्ठा inode *i, काष्ठा file *f)
अणु
	वापस single_खोलो(f, wiidebug_drm_show, i->i_निजी);
पूर्ण

अटल sमाप_प्रकार wiidebug_drm_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *u,
							माप_प्रकार s, loff_t *off)
अणु
	काष्ठा seq_file *sf = f->निजी_data;
	काष्ठा wiimote_debug *dbg = sf->निजी;
	अचिन्हित दीर्घ flags;
	अक्षर buf[16];
	sमाप_प्रकार len;
	पूर्णांक i;

	अगर (s == 0)
		वापस -EINVAL;

	len = min((माप_प्रकार) 15, s);
	अगर (copy_from_user(buf, u, len))
		वापस -EFAULT;

	buf[len] = 0;

	क्रम (i = 0; i < WIIPROTO_REQ_MAX; ++i) अणु
		अगर (!wiidebug_drmmap[i])
			जारी;
		अगर (!strहालcmp(buf, wiidebug_drmmap[i]))
			अवरोध;
	पूर्ण

	अगर (i == WIIPROTO_REQ_MAX)
		i = simple_म_से_अदीर्घ(buf, शून्य, 16);

	spin_lock_irqsave(&dbg->wdata->state.lock, flags);
	dbg->wdata->state.flags &= ~WIIPROTO_FLAG_DRM_LOCKED;
	wiiproto_req_drm(dbg->wdata, (__u8) i);
	अगर (i != WIIPROTO_REQ_शून्य)
		dbg->wdata->state.flags |= WIIPROTO_FLAG_DRM_LOCKED;
	spin_unlock_irqrestore(&dbg->wdata->state.lock, flags);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations wiidebug_drm_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = wiidebug_drm_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.ग_लिखो = wiidebug_drm_ग_लिखो,
	.release = single_release,
पूर्ण;

पूर्णांक wiidebug_init(काष्ठा wiimote_data *wdata)
अणु
	काष्ठा wiimote_debug *dbg;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -ENOMEM;

	dbg = kzalloc(माप(*dbg), GFP_KERNEL);
	अगर (!dbg)
		वापस -ENOMEM;

	dbg->wdata = wdata;

	dbg->eeprom = debugfs_create_file("eeprom", S_IRUSR,
		dbg->wdata->hdev->debug_dir, dbg, &wiidebug_eeprom_fops);
	अगर (!dbg->eeprom)
		जाओ err;

	dbg->drm = debugfs_create_file("drm", S_IRUSR,
			dbg->wdata->hdev->debug_dir, dbg, &wiidebug_drm_fops);
	अगर (!dbg->drm)
		जाओ err_drm;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->debug = dbg;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	वापस 0;

err_drm:
	debugfs_हटाओ(dbg->eeprom);
err:
	kमुक्त(dbg);
	वापस ret;
पूर्ण

व्योम wiidebug_deinit(काष्ठा wiimote_data *wdata)
अणु
	काष्ठा wiimote_debug *dbg = wdata->debug;
	अचिन्हित दीर्घ flags;

	अगर (!dbg)
		वापस;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->debug = शून्य;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	debugfs_हटाओ(dbg->drm);
	debugfs_हटाओ(dbg->eeprom);
	kमुक्त(dbg);
पूर्ण
