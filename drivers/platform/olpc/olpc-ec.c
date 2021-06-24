<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic driver क्रम the OLPC Embedded Controller.
 *
 * Author: Andres Salomon <dilinger@queued.net>
 *
 * Copyright (C) 2011-2012 One Laptop per Child Foundation.
 */
#समावेश <linux/completion.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/olpc-ec.h>

काष्ठा ec_cmd_desc अणु
	u8 cmd;
	u8 *inbuf, *outbuf;
	माप_प्रकार inlen, outlen;

	पूर्णांक err;
	काष्ठा completion finished;
	काष्ठा list_head node;

	व्योम *priv;
पूर्ण;

काष्ठा olpc_ec_priv अणु
	काष्ठा olpc_ec_driver *drv;
	u8 version;
	काष्ठा work_काष्ठा worker;
	काष्ठा mutex cmd_lock;

	/* DCON regulator */
	bool dcon_enabled;

	/* Pending EC commands */
	काष्ठा list_head cmd_q;
	spinlock_t cmd_q_lock;

	काष्ठा dentry *dbgfs_dir;

	/*
	 * EC event mask to be applied during suspend (defining wakeup
	 * sources).
	 */
	u16 ec_wakeup_mask;

	/*
	 * Running an EC command जबतक suspending means we करोn't always finish
	 * the command beक्रमe the machine suspends.  This means that the EC
	 * is expecting the command protocol to finish, but we after a period
	 * of समय (जबतक the OS is asleep) the EC बार out and restarts its
	 * idle loop.  Meanजबतक, the OS wakes up, thinks it's still in the
	 * middle of the command protocol, starts throwing अक्रमom things at
	 * the EC... and everyone's uphappy.
	 */
	bool suspended;
पूर्ण;

अटल काष्ठा olpc_ec_driver *ec_driver;
अटल काष्ठा olpc_ec_priv *ec_priv;
अटल व्योम *ec_cb_arg;

व्योम olpc_ec_driver_रेजिस्टर(काष्ठा olpc_ec_driver *drv, व्योम *arg)
अणु
	ec_driver = drv;
	ec_cb_arg = arg;
पूर्ण
EXPORT_SYMBOL_GPL(olpc_ec_driver_रेजिस्टर);

अटल व्योम olpc_ec_worker(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा olpc_ec_priv *ec = container_of(w, काष्ठा olpc_ec_priv, worker);
	काष्ठा ec_cmd_desc *desc = शून्य;
	अचिन्हित दीर्घ flags;

	/* Grab the first pending command from the queue */
	spin_lock_irqsave(&ec->cmd_q_lock, flags);
	अगर (!list_empty(&ec->cmd_q)) अणु
		desc = list_first_entry(&ec->cmd_q, काष्ठा ec_cmd_desc, node);
		list_del(&desc->node);
	पूर्ण
	spin_unlock_irqrestore(&ec->cmd_q_lock, flags);

	/* Do we actually have anything to करो? */
	अगर (!desc)
		वापस;

	/* Protect the EC hw with a mutex; only run one cmd at a समय */
	mutex_lock(&ec->cmd_lock);
	desc->err = ec_driver->ec_cmd(desc->cmd, desc->inbuf, desc->inlen,
			desc->outbuf, desc->outlen, ec_cb_arg);
	mutex_unlock(&ec->cmd_lock);

	/* Finished, wake up olpc_ec_cmd() */
	complete(&desc->finished);

	/* Run the worker thपढ़ो again in हाल there are more cmds pending */
	schedule_work(&ec->worker);
पूर्ण

/*
 * Throw a cmd descripter onto the list.  We now have SMP OLPC machines, so
 * locking is pretty critical.
 */
अटल व्योम queue_ec_descriptor(काष्ठा ec_cmd_desc *desc,
		काष्ठा olpc_ec_priv *ec)
अणु
	अचिन्हित दीर्घ flags;

	INIT_LIST_HEAD(&desc->node);

	spin_lock_irqsave(&ec->cmd_q_lock, flags);
	list_add_tail(&desc->node, &ec->cmd_q);
	spin_unlock_irqrestore(&ec->cmd_q_lock, flags);

	schedule_work(&ec->worker);
पूर्ण

पूर्णांक olpc_ec_cmd(u8 cmd, u8 *inbuf, माप_प्रकार inlen, u8 *outbuf, माप_प्रकार outlen)
अणु
	काष्ठा olpc_ec_priv *ec = ec_priv;
	काष्ठा ec_cmd_desc desc;

	/* Driver not yet रेजिस्टरed. */
	अगर (!ec_driver)
		वापस -EPROBE_DEFER;

	अगर (WARN_ON(!ec_driver->ec_cmd))
		वापस -ENODEV;

	अगर (!ec)
		वापस -ENOMEM;

	/* Suspending in the middle of a command hoses things really badly */
	अगर (WARN_ON(ec->suspended))
		वापस -EBUSY;

	might_sleep();

	desc.cmd = cmd;
	desc.inbuf = inbuf;
	desc.outbuf = outbuf;
	desc.inlen = inlen;
	desc.outlen = outlen;
	desc.err = 0;
	init_completion(&desc.finished);

	queue_ec_descriptor(&desc, ec);

	/* Timeouts must be handled in the platक्रमm-specअगरic EC hook */
	रुको_क्रम_completion(&desc.finished);

	/* The worker thपढ़ो dequeues the cmd; no need to करो anything here */
	वापस desc.err;
पूर्ण
EXPORT_SYMBOL_GPL(olpc_ec_cmd);

व्योम olpc_ec_wakeup_set(u16 value)
अणु
	काष्ठा olpc_ec_priv *ec = ec_priv;

	अगर (WARN_ON(!ec))
		वापस;

	ec->ec_wakeup_mask |= value;
पूर्ण
EXPORT_SYMBOL_GPL(olpc_ec_wakeup_set);

व्योम olpc_ec_wakeup_clear(u16 value)
अणु
	काष्ठा olpc_ec_priv *ec = ec_priv;

	अगर (WARN_ON(!ec))
		वापस;

	ec->ec_wakeup_mask &= ~value;
पूर्ण
EXPORT_SYMBOL_GPL(olpc_ec_wakeup_clear);

पूर्णांक olpc_ec_mask_ग_लिखो(u16 bits)
अणु
	काष्ठा olpc_ec_priv *ec = ec_priv;

	अगर (WARN_ON(!ec))
		वापस -ENODEV;

	/* EC version 0x5f adds support क्रम wide SCI mask */
	अगर (ec->version >= 0x5f) अणु
		__be16 ec_word = cpu_to_be16(bits);

		वापस olpc_ec_cmd(EC_WRITE_EXT_SCI_MASK, (व्योम *)&ec_word, 2, शून्य, 0);
	पूर्ण अन्यथा अणु
		u8 ec_byte = bits & 0xff;

		वापस olpc_ec_cmd(EC_WRITE_SCI_MASK, &ec_byte, 1, शून्य, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(olpc_ec_mask_ग_लिखो);

/*
 * Returns true अगर the compile and runसमय configurations allow क्रम EC events
 * to wake the प्रणाली.
 */
bool olpc_ec_wakeup_available(व्योम)
अणु
	अगर (WARN_ON(!ec_driver))
		वापस false;

	वापस ec_driver->wakeup_available;
पूर्ण
EXPORT_SYMBOL_GPL(olpc_ec_wakeup_available);

पूर्णांक olpc_ec_sci_query(u16 *sci_value)
अणु
	काष्ठा olpc_ec_priv *ec = ec_priv;
	पूर्णांक ret;

	अगर (WARN_ON(!ec))
		वापस -ENODEV;

	/* EC version 0x5f adds support क्रम wide SCI mask */
	अगर (ec->version >= 0x5f) अणु
		__be16 ec_word;

		ret = olpc_ec_cmd(EC_EXT_SCI_QUERY, शून्य, 0, (व्योम *)&ec_word, 2);
		अगर (ret == 0)
			*sci_value = be16_to_cpu(ec_word);
	पूर्ण अन्यथा अणु
		u8 ec_byte;

		ret = olpc_ec_cmd(EC_SCI_QUERY, शून्य, 0, &ec_byte, 1);
		अगर (ret == 0)
			*sci_value = ec_byte;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(olpc_ec_sci_query);

#अगर_घोषित CONFIG_DEBUG_FS

/*
 * debugfs support क्रम "generic commands", to allow sending
 * arbitrary EC commands from userspace.
 */

#घोषणा EC_MAX_CMD_ARGS (5 + 1)		/* cmd byte + 5 args */
#घोषणा EC_MAX_CMD_REPLY (8)

अटल DEFINE_MUTEX(ec_dbgfs_lock);
अटल अचिन्हित अक्षर ec_dbgfs_resp[EC_MAX_CMD_REPLY];
अटल अचिन्हित पूर्णांक ec_dbgfs_resp_bytes;

अटल sमाप_प्रकार ec_dbgfs_cmd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार size, loff_t *ppos)
अणु
	पूर्णांक i, m;
	अचिन्हित अक्षर ec_cmd[EC_MAX_CMD_ARGS];
	अचिन्हित पूर्णांक ec_cmd_पूर्णांक[EC_MAX_CMD_ARGS];
	अक्षर cmdbuf[64];
	पूर्णांक ec_cmd_bytes;

	mutex_lock(&ec_dbgfs_lock);

	size = simple_ग_लिखो_to_buffer(cmdbuf, माप(cmdbuf), ppos, buf, size);

	m = माला_पूछो(cmdbuf, "%x:%u %x %x %x %x %x", &ec_cmd_पूर्णांक[0],
			&ec_dbgfs_resp_bytes, &ec_cmd_पूर्णांक[1], &ec_cmd_पूर्णांक[2],
			&ec_cmd_पूर्णांक[3], &ec_cmd_पूर्णांक[4], &ec_cmd_पूर्णांक[5]);
	अगर (m < 2 || ec_dbgfs_resp_bytes > EC_MAX_CMD_REPLY) अणु
		/* reset to prevent overflow on पढ़ो */
		ec_dbgfs_resp_bytes = 0;

		pr_debug("olpc-ec: bad ec cmd:  cmd:response-count [arg1 [arg2 ...]]\n");
		size = -EINVAL;
		जाओ out;
	पूर्ण

	/* convert म_पूछो'd पूर्णांकs to अक्षर */
	ec_cmd_bytes = m - 2;
	क्रम (i = 0; i <= ec_cmd_bytes; i++)
		ec_cmd[i] = ec_cmd_पूर्णांक[i];

	pr_debug("olpc-ec: debugfs cmd 0x%02x with %d args %5ph, want %d returns\n",
			ec_cmd[0], ec_cmd_bytes, ec_cmd + 1,
			ec_dbgfs_resp_bytes);

	olpc_ec_cmd(ec_cmd[0], (ec_cmd_bytes == 0) ? शून्य : &ec_cmd[1],
			ec_cmd_bytes, ec_dbgfs_resp, ec_dbgfs_resp_bytes);

	pr_debug("olpc-ec: response %8ph (%d bytes expected)\n",
			ec_dbgfs_resp, ec_dbgfs_resp_bytes);

out:
	mutex_unlock(&ec_dbgfs_lock);
	वापस size;
पूर्ण

अटल sमाप_प्रकार ec_dbgfs_cmd_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		माप_प्रकार size, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक i, r;
	अक्षर *rp;
	अक्षर respbuf[64];

	mutex_lock(&ec_dbgfs_lock);
	rp = respbuf;
	rp += प्र_लिखो(rp, "%02x", ec_dbgfs_resp[0]);
	क्रम (i = 1; i < ec_dbgfs_resp_bytes; i++)
		rp += प्र_लिखो(rp, ", %02x", ec_dbgfs_resp[i]);
	mutex_unlock(&ec_dbgfs_lock);
	rp += प्र_लिखो(rp, "\n");

	r = rp - respbuf;
	वापस simple_पढ़ो_from_buffer(buf, size, ppos, respbuf, r);
पूर्ण

अटल स्थिर काष्ठा file_operations ec_dbgfs_ops = अणु
	.ग_लिखो = ec_dbgfs_cmd_ग_लिखो,
	.पढ़ो = ec_dbgfs_cmd_पढ़ो,
पूर्ण;

अटल काष्ठा dentry *olpc_ec_setup_debugfs(व्योम)
अणु
	काष्ठा dentry *dbgfs_dir;

	dbgfs_dir = debugfs_create_dir("olpc-ec", शून्य);
	अगर (IS_ERR_OR_शून्य(dbgfs_dir))
		वापस शून्य;

	debugfs_create_file("cmd", 0600, dbgfs_dir, शून्य, &ec_dbgfs_ops);

	वापस dbgfs_dir;
पूर्ण

#अन्यथा

अटल काष्ठा dentry *olpc_ec_setup_debugfs(व्योम)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल पूर्णांक olpc_ec_set_dcon_घातer(काष्ठा olpc_ec_priv *ec, bool state)
अणु
	अचिन्हित अक्षर ec_byte = state;
	पूर्णांक ret;

	अगर (ec->dcon_enabled == state)
		वापस 0;

	ret = olpc_ec_cmd(EC_DCON_POWER_MODE, &ec_byte, 1, शून्य, 0);
	अगर (ret)
		वापस ret;

	ec->dcon_enabled = state;
	वापस 0;
पूर्ण

अटल पूर्णांक dcon_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा olpc_ec_priv *ec = rdev_get_drvdata(rdev);

	वापस olpc_ec_set_dcon_घातer(ec, true);
पूर्ण

अटल पूर्णांक dcon_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा olpc_ec_priv *ec = rdev_get_drvdata(rdev);

	वापस olpc_ec_set_dcon_घातer(ec, false);
पूर्ण

अटल पूर्णांक dcon_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा olpc_ec_priv *ec = rdev_get_drvdata(rdev);

	वापस ec->dcon_enabled ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops dcon_regulator_ops = अणु
	.enable		= dcon_regulator_enable,
	.disable	= dcon_regulator_disable,
	.is_enabled	= dcon_regulator_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc dcon_desc = अणु
	.name		= "dcon",
	.id		= 0,
	.ops		= &dcon_regulator_ops,
	.type		= REGULATOR_VOLTAGE,
	.owner		= THIS_MODULE,
	.enable_समय	= 25000,
पूर्ण;

अटल पूर्णांक olpc_ec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा olpc_ec_priv *ec;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *regulator;
	पूर्णांक err;

	अगर (!ec_driver)
		वापस -ENODEV;

	ec = kzalloc(माप(*ec), GFP_KERNEL);
	अगर (!ec)
		वापस -ENOMEM;

	ec->drv = ec_driver;
	INIT_WORK(&ec->worker, olpc_ec_worker);
	mutex_init(&ec->cmd_lock);

	INIT_LIST_HEAD(&ec->cmd_q);
	spin_lock_init(&ec->cmd_q_lock);

	ec_priv = ec;
	platक्रमm_set_drvdata(pdev, ec);

	/* get the EC revision */
	err = olpc_ec_cmd(EC_FIRMWARE_REV, शून्य, 0, &ec->version, 1);
	अगर (err)
		जाओ error;

	config.dev = pdev->dev.parent;
	config.driver_data = ec;
	ec->dcon_enabled = true;
	regulator = devm_regulator_रेजिस्टर(&pdev->dev, &dcon_desc, &config);
	अगर (IS_ERR(regulator)) अणु
		dev_err(&pdev->dev, "failed to register DCON regulator\n");
		err = PTR_ERR(regulator);
		जाओ error;
	पूर्ण

	ec->dbgfs_dir = olpc_ec_setup_debugfs();

	वापस 0;

error:
	ec_priv = शून्य;
	kमुक्त(ec);
	वापस err;
पूर्ण

अटल पूर्णांक olpc_ec_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा olpc_ec_priv *ec = platक्रमm_get_drvdata(pdev);
	पूर्णांक err = 0;

	olpc_ec_mask_ग_लिखो(ec->ec_wakeup_mask);

	अगर (ec_driver->suspend)
		err = ec_driver->suspend(pdev);
	अगर (!err)
		ec->suspended = true;

	वापस err;
पूर्ण

अटल पूर्णांक olpc_ec_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा olpc_ec_priv *ec = platक्रमm_get_drvdata(pdev);

	ec->suspended = false;
	वापस ec_driver->resume ? ec_driver->resume(pdev) : 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops olpc_ec_pm_ops = अणु
	.suspend_late = olpc_ec_suspend,
	.resume_early = olpc_ec_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver olpc_ec_plat_driver = अणु
	.probe = olpc_ec_probe,
	.driver = अणु
		.name = "olpc-ec",
		.pm = &olpc_ec_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init olpc_ec_init_module(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&olpc_ec_plat_driver);
पूर्ण
arch_initcall(olpc_ec_init_module);
