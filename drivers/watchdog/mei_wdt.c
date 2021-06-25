<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Management Engine Interface (Intel MEI) Linux driver
 * Copyright (c) 2015, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/completion.h>
#समावेश <linux/watchकरोg.h>

#समावेश <linux/uuid.h>
#समावेश <linux/mei_cl_bus.h>

/*
 * iAMT Watchकरोg Device
 */
#घोषणा INTEL_AMT_WATCHDOG_ID "iamt_wdt"

#घोषणा MEI_WDT_DEFAULT_TIMEOUT   120  /* seconds */
#घोषणा MEI_WDT_MIN_TIMEOUT       120  /* seconds */
#घोषणा MEI_WDT_MAX_TIMEOUT     65535  /* seconds */

/* Commands */
#घोषणा MEI_MANAGEMENT_CONTROL 0x02

/* MEI Management Control version number */
#घोषणा MEI_MC_VERSION_NUMBER  0x10

/* Sub Commands */
#घोषणा MEI_MC_START_WD_TIMER_REQ  0x13
#घोषणा MEI_MC_START_WD_TIMER_RES  0x83
#घोषणा   MEI_WDT_STATUS_SUCCESS 0
#घोषणा   MEI_WDT_WDSTATE_NOT_REQUIRED 0x1
#घोषणा MEI_MC_STOP_WD_TIMER_REQ   0x14

/**
 * क्रमागत mei_wdt_state - पूर्णांकernal watchकरोg state
 *
 * @MEI_WDT_PROBE: wd in probing stage
 * @MEI_WDT_IDLE: wd is idle and not खोलोed
 * @MEI_WDT_START: wd was खोलोed, start was called
 * @MEI_WDT_RUNNING: wd is expecting keep alive pings
 * @MEI_WDT_STOPPING: wd is stopping and will move to IDLE
 * @MEI_WDT_NOT_REQUIRED: wd device is not required
 */
क्रमागत mei_wdt_state अणु
	MEI_WDT_PROBE,
	MEI_WDT_IDLE,
	MEI_WDT_START,
	MEI_WDT_RUNNING,
	MEI_WDT_STOPPING,
	MEI_WDT_NOT_REQUIRED,
पूर्ण;

अटल स्थिर अक्षर *mei_wdt_state_str(क्रमागत mei_wdt_state state)
अणु
	चयन (state) अणु
	हाल MEI_WDT_PROBE:
		वापस "PROBE";
	हाल MEI_WDT_IDLE:
		वापस "IDLE";
	हाल MEI_WDT_START:
		वापस "START";
	हाल MEI_WDT_RUNNING:
		वापस "RUNNING";
	हाल MEI_WDT_STOPPING:
		वापस "STOPPING";
	हाल MEI_WDT_NOT_REQUIRED:
		वापस "NOT_REQUIRED";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

/**
 * काष्ठा mei_wdt - mei watchकरोg driver
 * @wdd: watchकरोg device
 *
 * @cldev: mei watchकरोg client device
 * @state: watchकरोg पूर्णांकernal state
 * @resp_required: ping required response
 * @response: ping response completion
 * @unरेजिस्टर: unरेजिस्टर worker
 * @reg_lock: watchकरोg device registration lock
 * @समयout: watchकरोg current समयout
 *
 * @dbgfs_dir: debugfs dir entry
 */
काष्ठा mei_wdt अणु
	काष्ठा watchकरोg_device wdd;

	काष्ठा mei_cl_device *cldev;
	क्रमागत mei_wdt_state state;
	bool resp_required;
	काष्ठा completion response;
	काष्ठा work_काष्ठा unरेजिस्टर;
	काष्ठा mutex reg_lock;
	u16 समयout;

#अगर IS_ENABLED(CONFIG_DEBUG_FS)
	काष्ठा dentry *dbgfs_dir;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
पूर्ण;

/*
 * काष्ठा mei_mc_hdr - Management Control Command Header
 *
 * @command: Management Control (0x2)
 * @bytecount: Number of bytes in the message beyond this byte
 * @subcommand: Management Control Subcommand
 * @versionnumber: Management Control Version (0x10)
 */
काष्ठा mei_mc_hdr अणु
	u8 command;
	u8 bytecount;
	u8 subcommand;
	u8 versionnumber;
पूर्ण;

/**
 * काष्ठा mei_wdt_start_request watchकरोg start/ping
 *
 * @hdr: Management Control Command Header
 * @समयout: समयout value
 * @reserved: reserved (legacy)
 */
काष्ठा mei_wdt_start_request अणु
	काष्ठा mei_mc_hdr hdr;
	u16 समयout;
	u8 reserved[17];
पूर्ण __packed;

/**
 * काष्ठा mei_wdt_start_response watchकरोg start/ping response
 *
 * @hdr: Management Control Command Header
 * @status: operation status
 * @wdstate: watchकरोg status bit mask
 */
काष्ठा mei_wdt_start_response अणु
	काष्ठा mei_mc_hdr hdr;
	u8 status;
	u8 wdstate;
पूर्ण __packed;

/**
 * काष्ठा mei_wdt_stop_request - watchकरोg stop
 *
 * @hdr: Management Control Command Header
 */
काष्ठा mei_wdt_stop_request अणु
	काष्ठा mei_mc_hdr hdr;
पूर्ण __packed;

/**
 * mei_wdt_ping - send wd start/ping command
 *
 * @wdt: mei watchकरोg device
 *
 * Return: 0 on success,
 *         negative त्रुटि_सं code on failure
 */
अटल पूर्णांक mei_wdt_ping(काष्ठा mei_wdt *wdt)
अणु
	काष्ठा mei_wdt_start_request req;
	स्थिर माप_प्रकार req_len = माप(req);
	पूर्णांक ret;

	स_रखो(&req, 0, req_len);
	req.hdr.command = MEI_MANAGEMENT_CONTROL;
	req.hdr.bytecount = req_len - दुरत्व(काष्ठा mei_mc_hdr, subcommand);
	req.hdr.subcommand = MEI_MC_START_WD_TIMER_REQ;
	req.hdr.versionnumber = MEI_MC_VERSION_NUMBER;
	req.समयout = wdt->समयout;

	ret = mei_cldev_send(wdt->cldev, (u8 *)&req, req_len);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/**
 * mei_wdt_stop - send wd stop command
 *
 * @wdt: mei watchकरोg device
 *
 * Return: 0 on success,
 *         negative त्रुटि_सं code on failure
 */
अटल पूर्णांक mei_wdt_stop(काष्ठा mei_wdt *wdt)
अणु
	काष्ठा mei_wdt_stop_request req;
	स्थिर माप_प्रकार req_len = माप(req);
	पूर्णांक ret;

	स_रखो(&req, 0, req_len);
	req.hdr.command = MEI_MANAGEMENT_CONTROL;
	req.hdr.bytecount = req_len - दुरत्व(काष्ठा mei_mc_hdr, subcommand);
	req.hdr.subcommand = MEI_MC_STOP_WD_TIMER_REQ;
	req.hdr.versionnumber = MEI_MC_VERSION_NUMBER;

	ret = mei_cldev_send(wdt->cldev, (u8 *)&req, req_len);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/**
 * mei_wdt_ops_start - wd start command from the watchकरोg core.
 *
 * @wdd: watchकरोg device
 *
 * Return: 0 on success or -ENODEV;
 */
अटल पूर्णांक mei_wdt_ops_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा mei_wdt *wdt = watchकरोg_get_drvdata(wdd);

	wdt->state = MEI_WDT_START;
	wdd->समयout = wdt->समयout;
	वापस 0;
पूर्ण

/**
 * mei_wdt_ops_stop - wd stop command from the watchकरोg core.
 *
 * @wdd: watchकरोg device
 *
 * Return: 0 अगर success, negative त्रुटि_सं code क्रम failure
 */
अटल पूर्णांक mei_wdt_ops_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा mei_wdt *wdt = watchकरोg_get_drvdata(wdd);
	पूर्णांक ret;

	अगर (wdt->state != MEI_WDT_RUNNING)
		वापस 0;

	wdt->state = MEI_WDT_STOPPING;

	ret = mei_wdt_stop(wdt);
	अगर (ret)
		वापस ret;

	wdt->state = MEI_WDT_IDLE;

	वापस 0;
पूर्ण

/**
 * mei_wdt_ops_ping - wd ping command from the watchकरोg core.
 *
 * @wdd: watchकरोg device
 *
 * Return: 0 अगर success, negative त्रुटि_सं code on failure
 */
अटल पूर्णांक mei_wdt_ops_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा mei_wdt *wdt = watchकरोg_get_drvdata(wdd);
	पूर्णांक ret;

	अगर (wdt->state != MEI_WDT_START && wdt->state != MEI_WDT_RUNNING)
		वापस 0;

	अगर (wdt->resp_required)
		init_completion(&wdt->response);

	wdt->state = MEI_WDT_RUNNING;
	ret = mei_wdt_ping(wdt);
	अगर (ret)
		वापस ret;

	अगर (wdt->resp_required)
		ret = रुको_क्रम_completion_समाप्तable(&wdt->response);

	वापस ret;
पूर्ण

/**
 * mei_wdt_ops_set_समयout - wd set समयout command from the watchकरोg core.
 *
 * @wdd: watchकरोg device
 * @समयout: समयout value to set
 *
 * Return: 0 अगर success, negative त्रुटि_सं code क्रम failure
 */
अटल पूर्णांक mei_wdt_ops_set_समयout(काष्ठा watchकरोg_device *wdd,
				   अचिन्हित पूर्णांक समयout)
अणु

	काष्ठा mei_wdt *wdt = watchकरोg_get_drvdata(wdd);

	/* valid value is alपढ़ोy checked by the caller */
	wdt->समयout = समयout;
	wdd->समयout = समयout;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_ops wd_ops = अणु
	.owner       = THIS_MODULE,
	.start       = mei_wdt_ops_start,
	.stop        = mei_wdt_ops_stop,
	.ping        = mei_wdt_ops_ping,
	.set_समयout = mei_wdt_ops_set_समयout,
पूर्ण;

/* not स्थिर as the firmware_version field need to be retrieved */
अटल काष्ठा watchकरोg_info wd_info = अणु
	.identity = INTEL_AMT_WATCHDOG_ID,
	.options  = WDIOF_KEEPALIVEPING |
		    WDIOF_SETTIMEOUT |
		    WDIOF_ALARMONLY,
पूर्ण;

/**
 * __mei_wdt_is_रेजिस्टरed - check अगर wdt is रेजिस्टरed
 *
 * @wdt: mei watchकरोg device
 *
 * Return: true अगर the wdt is रेजिस्टरed with the watchकरोg subप्रणाली
 * Locking: should be called under wdt->reg_lock
 */
अटल अंतरभूत bool __mei_wdt_is_रेजिस्टरed(काष्ठा mei_wdt *wdt)
अणु
	वापस !!watchकरोg_get_drvdata(&wdt->wdd);
पूर्ण

/**
 * mei_wdt_unरेजिस्टर - unरेजिस्टर from the watchकरोg subप्रणाली
 *
 * @wdt: mei watchकरोg device
 */
अटल व्योम mei_wdt_unरेजिस्टर(काष्ठा mei_wdt *wdt)
अणु
	mutex_lock(&wdt->reg_lock);

	अगर (__mei_wdt_is_रेजिस्टरed(wdt)) अणु
		watchकरोg_unरेजिस्टर_device(&wdt->wdd);
		watchकरोg_set_drvdata(&wdt->wdd, शून्य);
		स_रखो(&wdt->wdd, 0, माप(wdt->wdd));
	पूर्ण

	mutex_unlock(&wdt->reg_lock);
पूर्ण

/**
 * mei_wdt_रेजिस्टर - रेजिस्टर with the watchकरोg subप्रणाली
 *
 * @wdt: mei watchकरोg device
 *
 * Return: 0 अगर success, negative त्रुटि_सं code क्रम failure
 */
अटल पूर्णांक mei_wdt_रेजिस्टर(काष्ठा mei_wdt *wdt)
अणु
	काष्ठा device *dev;
	पूर्णांक ret;

	अगर (!wdt || !wdt->cldev)
		वापस -EINVAL;

	dev = &wdt->cldev->dev;

	mutex_lock(&wdt->reg_lock);

	अगर (__mei_wdt_is_रेजिस्टरed(wdt)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	wdt->wdd.info = &wd_info;
	wdt->wdd.ops = &wd_ops;
	wdt->wdd.parent = dev;
	wdt->wdd.समयout = MEI_WDT_DEFAULT_TIMEOUT;
	wdt->wdd.min_समयout = MEI_WDT_MIN_TIMEOUT;
	wdt->wdd.max_समयout = MEI_WDT_MAX_TIMEOUT;

	watchकरोg_set_drvdata(&wdt->wdd, wdt);
	watchकरोg_stop_on_reboot(&wdt->wdd);
	watchकरोg_stop_on_unरेजिस्टर(&wdt->wdd);

	ret = watchकरोg_रेजिस्टर_device(&wdt->wdd);
	अगर (ret)
		watchकरोg_set_drvdata(&wdt->wdd, शून्य);

	wdt->state = MEI_WDT_IDLE;

out:
	mutex_unlock(&wdt->reg_lock);
	वापस ret;
पूर्ण

अटल व्योम mei_wdt_unरेजिस्टर_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mei_wdt *wdt = container_of(work, काष्ठा mei_wdt, unरेजिस्टर);

	mei_wdt_unरेजिस्टर(wdt);
पूर्ण

/**
 * mei_wdt_rx - callback क्रम data receive
 *
 * @cldev: bus device
 */
अटल व्योम mei_wdt_rx(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा mei_wdt *wdt = mei_cldev_get_drvdata(cldev);
	काष्ठा mei_wdt_start_response res;
	स्थिर माप_प्रकार res_len = माप(res);
	पूर्णांक ret;

	ret = mei_cldev_recv(wdt->cldev, (u8 *)&res, res_len);
	अगर (ret < 0) अणु
		dev_err(&cldev->dev, "failure in recv %d\n", ret);
		वापस;
	पूर्ण

	/* Empty response can be sent on stop */
	अगर (ret == 0)
		वापस;

	अगर (ret < माप(काष्ठा mei_mc_hdr)) अणु
		dev_err(&cldev->dev, "recv small data %d\n", ret);
		वापस;
	पूर्ण

	अगर (res.hdr.command != MEI_MANAGEMENT_CONTROL ||
	    res.hdr.versionnumber != MEI_MC_VERSION_NUMBER) अणु
		dev_err(&cldev->dev, "wrong command received\n");
		वापस;
	पूर्ण

	अगर (res.hdr.subcommand != MEI_MC_START_WD_TIMER_RES) अणु
		dev_warn(&cldev->dev, "unsupported command %d :%s[%d]\n",
			 res.hdr.subcommand,
			 mei_wdt_state_str(wdt->state),
			 wdt->state);
		वापस;
	पूर्ण

	/* Run the unregistration in a worker as this can be
	 * run only after ping completion, otherwise the flow will
	 * deadlock on watchकरोg core mutex.
	 */
	अगर (wdt->state == MEI_WDT_RUNNING) अणु
		अगर (res.wdstate & MEI_WDT_WDSTATE_NOT_REQUIRED) अणु
			wdt->state = MEI_WDT_NOT_REQUIRED;
			schedule_work(&wdt->unरेजिस्टर);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (wdt->state == MEI_WDT_PROBE) अणु
		अगर (res.wdstate & MEI_WDT_WDSTATE_NOT_REQUIRED) अणु
			wdt->state = MEI_WDT_NOT_REQUIRED;
		पूर्ण अन्यथा अणु
			/* stop the watchकरोg and रेजिस्टर watchकरोg device */
			mei_wdt_stop(wdt);
			mei_wdt_रेजिस्टर(wdt);
		पूर्ण
		वापस;
	पूर्ण

	dev_warn(&cldev->dev, "not in correct state %s[%d]\n",
			 mei_wdt_state_str(wdt->state), wdt->state);

out:
	अगर (!completion_करोne(&wdt->response))
		complete(&wdt->response);
पूर्ण

/*
 * mei_wdt_notअगर - callback क्रम event notअगरication
 *
 * @cldev: bus device
 */
अटल व्योम mei_wdt_notअगर(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा mei_wdt *wdt = mei_cldev_get_drvdata(cldev);

	अगर (wdt->state != MEI_WDT_NOT_REQUIRED)
		वापस;

	mei_wdt_रेजिस्टर(wdt);
पूर्ण

#अगर IS_ENABLED(CONFIG_DEBUG_FS)

अटल sमाप_प्रकार mei_dbgfs_पढ़ो_activation(काष्ठा file *file, अक्षर __user *ubuf,
					माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा mei_wdt *wdt = file->निजी_data;
	स्थिर माप_प्रकार bufsz = 32;
	अक्षर buf[32];
	sमाप_प्रकार pos;

	mutex_lock(&wdt->reg_lock);
	pos = scnम_लिखो(buf, bufsz, "%s\n",
		__mei_wdt_is_रेजिस्टरed(wdt) ? "activated" : "deactivated");
	mutex_unlock(&wdt->reg_lock);

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, pos);
पूर्ण

अटल स्थिर काष्ठा file_operations dbgfs_fops_activation = अणु
	.खोलो    = simple_खोलो,
	.पढ़ो    = mei_dbgfs_पढ़ो_activation,
	.llseek  = generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार mei_dbgfs_पढ़ो_state(काष्ठा file *file, अक्षर __user *ubuf,
				    माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा mei_wdt *wdt = file->निजी_data;
	अक्षर buf[32];
	sमाप_प्रकार pos;

	pos = scnम_लिखो(buf, माप(buf), "state: %s\n",
			mei_wdt_state_str(wdt->state));

	वापस simple_पढ़ो_from_buffer(ubuf, cnt, ppos, buf, pos);
पूर्ण

अटल स्थिर काष्ठा file_operations dbgfs_fops_state = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = mei_dbgfs_पढ़ो_state,
	.llseek = generic_file_llseek,
पूर्ण;

अटल व्योम dbgfs_unरेजिस्टर(काष्ठा mei_wdt *wdt)
अणु
	debugfs_हटाओ_recursive(wdt->dbgfs_dir);
	wdt->dbgfs_dir = शून्य;
पूर्ण

अटल व्योम dbgfs_रेजिस्टर(काष्ठा mei_wdt *wdt)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir(KBUILD_MODNAME, शून्य);
	wdt->dbgfs_dir = dir;

	debugfs_create_file("state", S_IRUSR, dir, wdt, &dbgfs_fops_state);

	debugfs_create_file("activation", S_IRUSR, dir, wdt,
			    &dbgfs_fops_activation);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम dbgfs_unरेजिस्टर(काष्ठा mei_wdt *wdt) अणुपूर्ण
अटल अंतरभूत व्योम dbgfs_रेजिस्टर(काष्ठा mei_wdt *wdt) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल पूर्णांक mei_wdt_probe(काष्ठा mei_cl_device *cldev,
			 स्थिर काष्ठा mei_cl_device_id *id)
अणु
	काष्ठा mei_wdt *wdt;
	पूर्णांक ret;

	wdt = kzalloc(माप(काष्ठा mei_wdt), GFP_KERNEL);
	अगर (!wdt)
		वापस -ENOMEM;

	wdt->समयout = MEI_WDT_DEFAULT_TIMEOUT;
	wdt->state = MEI_WDT_PROBE;
	wdt->cldev = cldev;
	wdt->resp_required = mei_cldev_ver(cldev) > 0x1;
	mutex_init(&wdt->reg_lock);
	init_completion(&wdt->response);
	INIT_WORK(&wdt->unरेजिस्टर, mei_wdt_unरेजिस्टर_work);

	mei_cldev_set_drvdata(cldev, wdt);

	ret = mei_cldev_enable(cldev);
	अगर (ret < 0) अणु
		dev_err(&cldev->dev, "Could not enable cl device\n");
		जाओ err_out;
	पूर्ण

	ret = mei_cldev_रेजिस्टर_rx_cb(wdt->cldev, mei_wdt_rx);
	अगर (ret) अणु
		dev_err(&cldev->dev, "Could not reg rx event ret=%d\n", ret);
		जाओ err_disable;
	पूर्ण

	ret = mei_cldev_रेजिस्टर_notअगर_cb(wdt->cldev, mei_wdt_notअगर);
	/* on legacy devices notअगरication is not supported
	 */
	अगर (ret && ret != -EOPNOTSUPP) अणु
		dev_err(&cldev->dev, "Could not reg notif event ret=%d\n", ret);
		जाओ err_disable;
	पूर्ण

	wd_info.firmware_version = mei_cldev_ver(cldev);

	अगर (wdt->resp_required)
		ret = mei_wdt_ping(wdt);
	अन्यथा
		ret = mei_wdt_रेजिस्टर(wdt);

	अगर (ret)
		जाओ err_disable;

	dbgfs_रेजिस्टर(wdt);

	वापस 0;

err_disable:
	mei_cldev_disable(cldev);

err_out:
	kमुक्त(wdt);

	वापस ret;
पूर्ण

अटल व्योम mei_wdt_हटाओ(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा mei_wdt *wdt = mei_cldev_get_drvdata(cldev);

	/* Free the caller in हाल of fw initiated or unexpected reset */
	अगर (!completion_करोne(&wdt->response))
		complete(&wdt->response);

	cancel_work_sync(&wdt->unरेजिस्टर);

	mei_wdt_unरेजिस्टर(wdt);

	mei_cldev_disable(cldev);

	dbgfs_unरेजिस्टर(wdt);

	kमुक्त(wdt);
पूर्ण

#घोषणा MEI_UUID_WD UUID_LE(0x05B79A6F, 0x4628, 0x4D7F, \
			    0x89, 0x9D, 0xA9, 0x15, 0x14, 0xCB, 0x32, 0xAB)

अटल स्थिर काष्ठा mei_cl_device_id mei_wdt_tbl[] = अणु
	अणु .uuid = MEI_UUID_WD, .version = MEI_CL_VERSION_ANY पूर्ण,
	/* required last entry */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mei, mei_wdt_tbl);

अटल काष्ठा mei_cl_driver mei_wdt_driver = अणु
	.id_table = mei_wdt_tbl,
	.name = KBUILD_MODNAME,

	.probe = mei_wdt_probe,
	.हटाओ = mei_wdt_हटाओ,
पूर्ण;

module_mei_cl_driver(mei_wdt_driver);

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Device driver for Intel MEI iAMT watchdog");
