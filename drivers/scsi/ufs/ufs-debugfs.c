<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 Intel Corporation

#समावेश <linux/debugfs.h>

#समावेश "ufs-debugfs.h"
#समावेश "ufshcd.h"

अटल काष्ठा dentry *ufs_debugfs_root;

व्योम __init ufs_debugfs_init(व्योम)
अणु
	ufs_debugfs_root = debugfs_create_dir("ufshcd", शून्य);
पूर्ण

व्योम __निकास ufs_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(ufs_debugfs_root);
पूर्ण

अटल पूर्णांक ufs_debugfs_stats_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा ufs_hba *hba = s->निजी;
	काष्ठा ufs_event_hist *e = hba->ufs_stats.event;

#घोषणा PRT(fmt, typ) \
	seq_म_लिखो(s, fmt, e[UFS_EVT_ ## typ].cnt)

	PRT("PHY Adapter Layer errors (except LINERESET): %llu\n", PA_ERR);
	PRT("Data Link Layer errors: %llu\n", DL_ERR);
	PRT("Network Layer errors: %llu\n", NL_ERR);
	PRT("Transport Layer errors: %llu\n", TL_ERR);
	PRT("Generic DME errors: %llu\n", DME_ERR);
	PRT("Auto-hibernate errors: %llu\n", AUTO_HIBERN8_ERR);
	PRT("IS Fatal errors (CEFES, SBFES, HCFES, DFES): %llu\n", FATAL_ERR);
	PRT("DME Link Startup errors: %llu\n", LINK_STARTUP_FAIL);
	PRT("PM Resume errors: %llu\n", RESUME_ERR);
	PRT("PM Suspend errors : %llu\n", SUSPEND_ERR);
	PRT("Logical Unit Resets: %llu\n", DEV_RESET);
	PRT("Host Resets: %llu\n", HOST_RESET);
	PRT("SCSI command aborts: %llu\n", ABORT);
#अघोषित PRT
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ufs_debugfs_stats);

अटल पूर्णांक ee_usr_mask_get(व्योम *data, u64 *val)
अणु
	काष्ठा ufs_hba *hba = data;

	*val = hba->ee_usr_mask;
	वापस 0;
पूर्ण

अटल पूर्णांक ufs_debugfs_get_user_access(काष्ठा ufs_hba *hba)
__acquires(&hba->host_sem)
अणु
	करोwn(&hba->host_sem);
	अगर (!ufshcd_is_user_access_allowed(hba)) अणु
		up(&hba->host_sem);
		वापस -EBUSY;
	पूर्ण
	pm_runसमय_get_sync(hba->dev);
	वापस 0;
पूर्ण

अटल व्योम ufs_debugfs_put_user_access(काष्ठा ufs_hba *hba)
__releases(&hba->host_sem)
अणु
	pm_runसमय_put_sync(hba->dev);
	up(&hba->host_sem);
पूर्ण

अटल पूर्णांक ee_usr_mask_set(व्योम *data, u64 val)
अणु
	काष्ठा ufs_hba *hba = data;
	पूर्णांक err;

	अगर (val & ~(u64)MASK_EE_STATUS)
		वापस -EINVAL;
	err = ufs_debugfs_get_user_access(hba);
	अगर (err)
		वापस err;
	err = ufshcd_update_ee_usr_mask(hba, val, MASK_EE_STATUS);
	ufs_debugfs_put_user_access(hba);
	वापस err;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(ee_usr_mask_fops, ee_usr_mask_get, ee_usr_mask_set, "%#llx\n");

व्योम ufs_debugfs_exception_event(काष्ठा ufs_hba *hba, u16 status)
अणु
	bool chgd = false;
	u16 ee_ctrl_mask;
	पूर्णांक err = 0;

	अगर (!hba->debugfs_ee_rate_limit_ms || !status)
		वापस;

	mutex_lock(&hba->ee_ctrl_mutex);
	ee_ctrl_mask = hba->ee_drv_mask | (hba->ee_usr_mask & ~status);
	chgd = ee_ctrl_mask != hba->ee_ctrl_mask;
	अगर (chgd) अणु
		err = __ufshcd_ग_लिखो_ee_control(hba, ee_ctrl_mask);
		अगर (err)
			dev_err(hba->dev, "%s: failed to write ee control %d\n",
				__func__, err);
	पूर्ण
	mutex_unlock(&hba->ee_ctrl_mutex);

	अगर (chgd && !err) अणु
		अचिन्हित दीर्घ delay = msecs_to_jअगरfies(hba->debugfs_ee_rate_limit_ms);

		queue_delayed_work(प्रणाली_मुक्तzable_wq, &hba->debugfs_ee_work, delay);
	पूर्ण
पूर्ण

अटल व्योम ufs_debugfs_restart_ee(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ufs_hba *hba = container_of(work, काष्ठा ufs_hba, debugfs_ee_work.work);

	अगर (!hba->ee_usr_mask || pm_runसमय_suspended(hba->dev) ||
	    ufs_debugfs_get_user_access(hba))
		वापस;
	ufshcd_ग_लिखो_ee_control(hba);
	ufs_debugfs_put_user_access(hba);
पूर्ण

व्योम ufs_debugfs_hba_init(काष्ठा ufs_hba *hba)
अणु
	/* Set शेष exception event rate limit period to 20ms */
	hba->debugfs_ee_rate_limit_ms = 20;
	INIT_DELAYED_WORK(&hba->debugfs_ee_work, ufs_debugfs_restart_ee);
	hba->debugfs_root = debugfs_create_dir(dev_name(hba->dev), ufs_debugfs_root);
	debugfs_create_file("stats", 0400, hba->debugfs_root, hba, &ufs_debugfs_stats_fops);
	debugfs_create_file("exception_event_mask", 0600, hba->debugfs_root,
			    hba, &ee_usr_mask_fops);
	debugfs_create_u32("exception_event_rate_limit_ms", 0600, hba->debugfs_root,
			   &hba->debugfs_ee_rate_limit_ms);
पूर्ण

व्योम ufs_debugfs_hba_निकास(काष्ठा ufs_hba *hba)
अणु
	debugfs_हटाओ_recursive(hba->debugfs_root);
	cancel_delayed_work_sync(&hba->debugfs_ee_work);
पूर्ण
