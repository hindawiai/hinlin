<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Turris Mox rWTM firmware driver
 *
 * Copyright (C) 2019 Marek Behथजn <kabel@kernel.org>
 */

#समावेश <linux/armada-37xx-rwपंचांग-mailbox.h>
#समावेश <linux/completion.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा DRIVER_NAME		"turris-mox-rwtm"

/*
 * The macros and स्थिरants below come from Turris Mox's rWTM firmware code.
 * This firmware is खोलो source and it's sources can be found at
 * https://gitlab.द_असल.nic.cz/turris/mox-boot-builder/tree/master/wपंचांगi.
 */

#घोषणा MBOX_STS_SUCCESS	(0 << 30)
#घोषणा MBOX_STS_FAIL		(1 << 30)
#घोषणा MBOX_STS_BADCMD		(2 << 30)
#घोषणा MBOX_STS_ERROR(s)	((s) & (3 << 30))
#घोषणा MBOX_STS_VALUE(s)	(((s) >> 10) & 0xfffff)
#घोषणा MBOX_STS_CMD(s)		((s) & 0x3ff)

क्रमागत mbox_cmd अणु
	MBOX_CMD_GET_RANDOM	= 1,
	MBOX_CMD_BOARD_INFO	= 2,
	MBOX_CMD_ECDSA_PUB_KEY	= 3,
	MBOX_CMD_HASH		= 4,
	MBOX_CMD_SIGN		= 5,
	MBOX_CMD_VERIFY		= 6,

	MBOX_CMD_OTP_READ	= 7,
	MBOX_CMD_OTP_WRITE	= 8,
पूर्ण;

काष्ठा mox_kobject;

काष्ठा mox_rwपंचांग अणु
	काष्ठा device *dev;
	काष्ठा mbox_client mbox_client;
	काष्ठा mbox_chan *mbox;
	काष्ठा mox_kobject *kobj;
	काष्ठा hwrng hwrng;

	काष्ठा armada_37xx_rwपंचांग_rx_msg reply;

	व्योम *buf;
	dma_addr_t buf_phys;

	काष्ठा mutex busy;
	काष्ठा completion cmd_करोne;

	/* board inक्रमmation */
	पूर्णांक has_board_info;
	u64 serial_number;
	पूर्णांक board_version, ram_size;
	u8 mac_address1[6], mac_address2[6];

	/* खुला key burned in eFuse */
	पूर्णांक has_pubkey;
	u8 pubkey[135];

#अगर_घोषित CONFIG_DEBUG_FS
	/*
	 * Signature process. This is currently करोne via debugfs, because it
	 * करोes not conक्रमm to the sysfs standard "one file per attribute".
	 * It should be rewritten via crypto API once akcipher API is available
	 * from userspace.
	 */
	काष्ठा dentry *debugfs_root;
	u32 last_sig[34];
	पूर्णांक last_sig_करोne;
#पूर्ण_अगर
पूर्ण;

काष्ठा mox_kobject अणु
	काष्ठा kobject kobj;
	काष्ठा mox_rwपंचांग *rwपंचांग;
पूर्ण;

अटल अंतरभूत काष्ठा kobject *rwपंचांग_to_kobj(काष्ठा mox_rwपंचांग *rwपंचांग)
अणु
	वापस &rwपंचांग->kobj->kobj;
पूर्ण

अटल अंतरभूत काष्ठा mox_rwपंचांग *to_rwपंचांग(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा mox_kobject, kobj)->rwपंचांग;
पूर्ण

अटल व्योम mox_kobj_release(काष्ठा kobject *kobj)
अणु
	kमुक्त(to_rwपंचांग(kobj)->kobj);
पूर्ण

अटल काष्ठा kobj_type mox_kobj_ktype = अणु
	.release	= mox_kobj_release,
	.sysfs_ops	= &kobj_sysfs_ops,
पूर्ण;

अटल पूर्णांक mox_kobj_create(काष्ठा mox_rwपंचांग *rwपंचांग)
अणु
	rwपंचांग->kobj = kzalloc(माप(*rwपंचांग->kobj), GFP_KERNEL);
	अगर (!rwपंचांग->kobj)
		वापस -ENOMEM;

	kobject_init(rwपंचांग_to_kobj(rwपंचांग), &mox_kobj_ktype);
	अगर (kobject_add(rwपंचांग_to_kobj(rwपंचांग), firmware_kobj, "turris-mox-rwtm")) अणु
		kobject_put(rwपंचांग_to_kobj(rwपंचांग));
		वापस -ENXIO;
	पूर्ण

	rwपंचांग->kobj->rwपंचांग = rwपंचांग;

	वापस 0;
पूर्ण

#घोषणा MOX_ATTR_RO(name, क्रमmat, cat)				\
अटल sमाप_प्रकार							\
name##_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *a,	\
	    अक्षर *buf)						\
अणु								\
	काष्ठा mox_rwपंचांग *rwपंचांग = to_rwपंचांग(kobj);	\
	अगर (!rwपंचांग->has_##cat)					\
		वापस -ENODATA;				\
	वापस प्र_लिखो(buf, क्रमmat, rwपंचांग->name);		\
पूर्ण								\
अटल काष्ठा kobj_attribute mox_attr_##name = __ATTR_RO(name)

MOX_ATTR_RO(serial_number, "%016llX\n", board_info);
MOX_ATTR_RO(board_version, "%i\n", board_info);
MOX_ATTR_RO(ram_size, "%i\n", board_info);
MOX_ATTR_RO(mac_address1, "%pM\n", board_info);
MOX_ATTR_RO(mac_address2, "%pM\n", board_info);
MOX_ATTR_RO(pubkey, "%s\n", pubkey);

अटल पूर्णांक mox_get_status(क्रमागत mbox_cmd cmd, u32 retval)
अणु
	अगर (MBOX_STS_CMD(retval) != cmd ||
	    MBOX_STS_ERROR(retval) != MBOX_STS_SUCCESS)
		वापस -EIO;
	अन्यथा अगर (MBOX_STS_ERROR(retval) == MBOX_STS_FAIL)
		वापस -(पूर्णांक)MBOX_STS_VALUE(retval);
	अन्यथा
		वापस MBOX_STS_VALUE(retval);
पूर्ण

अटल स्थिर काष्ठा attribute *mox_rwपंचांग_attrs[] = अणु
	&mox_attr_serial_number.attr,
	&mox_attr_board_version.attr,
	&mox_attr_ram_size.attr,
	&mox_attr_mac_address1.attr,
	&mox_attr_mac_address2.attr,
	&mox_attr_pubkey.attr,
	शून्य
पूर्ण;

अटल व्योम mox_rwपंचांग_rx_callback(काष्ठा mbox_client *cl, व्योम *data)
अणु
	काष्ठा mox_rwपंचांग *rwपंचांग = dev_get_drvdata(cl->dev);
	काष्ठा armada_37xx_rwपंचांग_rx_msg *msg = data;

	rwपंचांग->reply = *msg;
	complete(&rwपंचांग->cmd_करोne);
पूर्ण

अटल व्योम reply_to_mac_addr(u8 *mac, u32 t1, u32 t2)
अणु
	mac[0] = t1 >> 8;
	mac[1] = t1;
	mac[2] = t2 >> 24;
	mac[3] = t2 >> 16;
	mac[4] = t2 >> 8;
	mac[5] = t2;
पूर्ण

अटल पूर्णांक mox_get_board_info(काष्ठा mox_rwपंचांग *rwपंचांग)
अणु
	काष्ठा armada_37xx_rwपंचांग_tx_msg msg;
	काष्ठा armada_37xx_rwपंचांग_rx_msg *reply = &rwपंचांग->reply;
	पूर्णांक ret;

	msg.command = MBOX_CMD_BOARD_INFO;
	ret = mbox_send_message(rwपंचांग->mbox, &msg);
	अगर (ret < 0)
		वापस ret;

	ret = रुको_क्रम_completion_समयout(&rwपंचांग->cmd_करोne, HZ / 2);
	अगर (ret < 0)
		वापस ret;

	ret = mox_get_status(MBOX_CMD_BOARD_INFO, reply->retval);
	अगर (ret < 0 && ret != -ENODATA) अणु
		वापस ret;
	पूर्ण अन्यथा अगर (ret == -ENODATA) अणु
		dev_warn(rwपंचांग->dev,
			 "Board does not have manufacturing information burned!\n");
	पूर्ण अन्यथा अणु
		rwपंचांग->serial_number = reply->status[1];
		rwपंचांग->serial_number <<= 32;
		rwपंचांग->serial_number |= reply->status[0];
		rwपंचांग->board_version = reply->status[2];
		rwपंचांग->ram_size = reply->status[3];
		reply_to_mac_addr(rwपंचांग->mac_address1, reply->status[4],
				  reply->status[5]);
		reply_to_mac_addr(rwपंचांग->mac_address2, reply->status[6],
				  reply->status[7]);
		rwपंचांग->has_board_info = 1;

		pr_info("Turris Mox serial number %016llX\n",
			rwपंचांग->serial_number);
		pr_info("           board version %i\n", rwपंचांग->board_version);
		pr_info("           burned RAM size %i MiB\n", rwपंचांग->ram_size);
	पूर्ण

	msg.command = MBOX_CMD_ECDSA_PUB_KEY;
	ret = mbox_send_message(rwपंचांग->mbox, &msg);
	अगर (ret < 0)
		वापस ret;

	ret = रुको_क्रम_completion_समयout(&rwपंचांग->cmd_करोne, HZ / 2);
	अगर (ret < 0)
		वापस ret;

	ret = mox_get_status(MBOX_CMD_ECDSA_PUB_KEY, reply->retval);
	अगर (ret < 0 && ret != -ENODATA) अणु
		वापस ret;
	पूर्ण अन्यथा अगर (ret == -ENODATA) अणु
		dev_warn(rwपंचांग->dev, "Board has no public key burned!\n");
	पूर्ण अन्यथा अणु
		u32 *s = reply->status;

		rwपंचांग->has_pubkey = 1;
		प्र_लिखो(rwपंचांग->pubkey,
			"%06x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x",
			ret, s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7],
			s[8], s[9], s[10], s[11], s[12], s[13], s[14], s[15]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mox_hwrng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको)
अणु
	काष्ठा mox_rwपंचांग *rwपंचांग = (काष्ठा mox_rwपंचांग *) rng->priv;
	काष्ठा armada_37xx_rwपंचांग_tx_msg msg;
	पूर्णांक ret;

	अगर (max > 4096)
		max = 4096;

	msg.command = MBOX_CMD_GET_RANDOM;
	msg.args[0] = 1;
	msg.args[1] = rwपंचांग->buf_phys;
	msg.args[2] = (max + 3) & ~3;

	अगर (!रुको) अणु
		अगर (!mutex_trylock(&rwपंचांग->busy))
			वापस -EBUSY;
	पूर्ण अन्यथा अणु
		mutex_lock(&rwपंचांग->busy);
	पूर्ण

	ret = mbox_send_message(rwपंचांग->mbox, &msg);
	अगर (ret < 0)
		जाओ unlock_mutex;

	ret = रुको_क्रम_completion_पूर्णांकerruptible(&rwपंचांग->cmd_करोne);
	अगर (ret < 0)
		जाओ unlock_mutex;

	ret = mox_get_status(MBOX_CMD_GET_RANDOM, rwपंचांग->reply.retval);
	अगर (ret < 0)
		जाओ unlock_mutex;

	स_नकल(data, rwपंचांग->buf, max);
	ret = max;

unlock_mutex:
	mutex_unlock(&rwपंचांग->busy);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक rwपंचांग_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = inode->i_निजी;

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार करो_sign_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार len,
			    loff_t *ppos)
अणु
	काष्ठा mox_rwपंचांग *rwपंचांग = file->निजी_data;
	sमाप_प्रकार ret;

	/* only allow one पढ़ो, of 136 bytes, from position 0 */
	अगर (*ppos != 0)
		वापस 0;

	अगर (len < 136)
		वापस -EINVAL;

	अगर (!rwपंचांग->last_sig_करोne)
		वापस -ENODATA;

	/* 2 arrays of 17 32-bit words are 136 bytes */
	ret = simple_पढ़ो_from_buffer(buf, len, ppos, rwपंचांग->last_sig, 136);
	rwपंचांग->last_sig_करोne = 0;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार करो_sign_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा mox_rwपंचांग *rwपंचांग = file->निजी_data;
	काष्ठा armada_37xx_rwपंचांग_rx_msg *reply = &rwपंचांग->reply;
	काष्ठा armada_37xx_rwपंचांग_tx_msg msg;
	loff_t dummy = 0;
	sमाप_प्रकार ret;

	/* the input is a SHA-512 hash, so exactly 64 bytes have to be पढ़ो */
	अगर (len != 64)
		वापस -EINVAL;

	/* अगर last result is not zero user has not पढ़ो that inक्रमmation yet */
	अगर (rwपंचांग->last_sig_करोne)
		वापस -EBUSY;

	अगर (!mutex_trylock(&rwपंचांग->busy))
		वापस -EBUSY;

	/*
	 * Here we have to send:
	 *   1. Address of the input to sign.
	 *      The input is an array of 17 32-bit words, the first (most
	 *      signअगरicat) is 0, the rest 16 words are copied from the SHA-512
	 *      hash given by the user and converted from BE to LE.
	 *   2. Address of the buffer where ECDSA signature value R shall be
	 *      stored by the rWTM firmware.
	 *   3. Address of the buffer where ECDSA signature value S shall be
	 *      stored by the rWTM firmware.
	 */
	स_रखो(rwपंचांग->buf, 0, 4);
	ret = simple_ग_लिखो_to_buffer(rwपंचांग->buf + 4, 64, &dummy, buf, len);
	अगर (ret < 0)
		जाओ unlock_mutex;
	be32_to_cpu_array(rwपंचांग->buf, rwपंचांग->buf, 17);

	msg.command = MBOX_CMD_SIGN;
	msg.args[0] = 1;
	msg.args[1] = rwपंचांग->buf_phys;
	msg.args[2] = rwपंचांग->buf_phys + 68;
	msg.args[3] = rwपंचांग->buf_phys + 2 * 68;
	ret = mbox_send_message(rwपंचांग->mbox, &msg);
	अगर (ret < 0)
		जाओ unlock_mutex;

	ret = रुको_क्रम_completion_पूर्णांकerruptible(&rwपंचांग->cmd_करोne);
	अगर (ret < 0)
		जाओ unlock_mutex;

	ret = MBOX_STS_VALUE(reply->retval);
	अगर (MBOX_STS_ERROR(reply->retval) != MBOX_STS_SUCCESS)
		जाओ unlock_mutex;

	/*
	 * Here we पढ़ो the R and S values of the ECDSA signature
	 * computed by the rWTM firmware and convert their words from
	 * LE to BE.
	 */
	स_नकल(rwपंचांग->last_sig, rwपंचांग->buf + 68, 136);
	cpu_to_be32_array(rwपंचांग->last_sig, rwपंचांग->last_sig, 34);
	rwपंचांग->last_sig_करोne = 1;

	mutex_unlock(&rwपंचांग->busy);
	वापस len;
unlock_mutex:
	mutex_unlock(&rwपंचांग->busy);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations करो_sign_fops = अणु
	.owner	= THIS_MODULE,
	.खोलो	= rwपंचांग_debug_खोलो,
	.पढ़ो	= करो_sign_पढ़ो,
	.ग_लिखो	= करो_sign_ग_लिखो,
	.llseek	= no_llseek,
पूर्ण;

अटल पूर्णांक rwपंचांग_रेजिस्टर_debugfs(काष्ठा mox_rwपंचांग *rwपंचांग)
अणु
	काष्ठा dentry *root, *entry;

	root = debugfs_create_dir("turris-mox-rwtm", शून्य);

	अगर (IS_ERR(root))
		वापस PTR_ERR(root);

	entry = debugfs_create_file_unsafe("do_sign", 0600, root, rwपंचांग,
					   &करो_sign_fops);
	अगर (IS_ERR(entry))
		जाओ err_हटाओ;

	rwपंचांग->debugfs_root = root;

	वापस 0;
err_हटाओ:
	debugfs_हटाओ_recursive(root);
	वापस PTR_ERR(entry);
पूर्ण

अटल व्योम rwपंचांग_unरेजिस्टर_debugfs(काष्ठा mox_rwपंचांग *rwपंचांग)
अणु
	debugfs_हटाओ_recursive(rwपंचांग->debugfs_root);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक rwपंचांग_रेजिस्टर_debugfs(काष्ठा mox_rwपंचांग *rwपंचांग)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rwपंचांग_unरेजिस्टर_debugfs(काष्ठा mox_rwपंचांग *rwपंचांग)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक turris_mox_rwपंचांग_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mox_rwपंचांग *rwपंचांग;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	rwपंचांग = devm_kzalloc(dev, माप(*rwपंचांग), GFP_KERNEL);
	अगर (!rwपंचांग)
		वापस -ENOMEM;

	rwपंचांग->dev = dev;
	rwपंचांग->buf = dmam_alloc_coherent(dev, PAGE_SIZE, &rwपंचांग->buf_phys,
					GFP_KERNEL);
	अगर (!rwपंचांग->buf)
		वापस -ENOMEM;

	ret = mox_kobj_create(rwपंचांग);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot create turris-mox-rwtm kobject!\n");
		वापस ret;
	पूर्ण

	ret = sysfs_create_files(rwपंचांग_to_kobj(rwपंचांग), mox_rwपंचांग_attrs);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot create sysfs files!\n");
		जाओ put_kobj;
	पूर्ण

	platक्रमm_set_drvdata(pdev, rwपंचांग);

	mutex_init(&rwपंचांग->busy);

	rwपंचांग->mbox_client.dev = dev;
	rwपंचांग->mbox_client.rx_callback = mox_rwपंचांग_rx_callback;

	rwपंचांग->mbox = mbox_request_channel(&rwपंचांग->mbox_client, 0);
	अगर (IS_ERR(rwपंचांग->mbox)) अणु
		ret = PTR_ERR(rwपंचांग->mbox);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Cannot request mailbox channel: %i\n",
				ret);
		जाओ हटाओ_files;
	पूर्ण

	init_completion(&rwपंचांग->cmd_करोne);

	ret = mox_get_board_info(rwपंचांग);
	अगर (ret < 0)
		dev_warn(dev, "Cannot read board information: %i\n", ret);

	rwपंचांग->hwrng.name = DRIVER_NAME "_hwrng";
	rwपंचांग->hwrng.पढ़ो = mox_hwrng_पढ़ो;
	rwपंचांग->hwrng.priv = (अचिन्हित दीर्घ) rwपंचांग;
	rwपंचांग->hwrng.quality = 1024;

	ret = devm_hwrng_रेजिस्टर(dev, &rwपंचांग->hwrng);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot register HWRNG: %i\n", ret);
		जाओ मुक्त_channel;
	पूर्ण

	ret = rwपंचांग_रेजिस्टर_debugfs(rwपंचांग);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed creating debugfs entries: %i\n", ret);
		जाओ मुक्त_channel;
	पूर्ण

	वापस 0;

मुक्त_channel:
	mbox_मुक्त_channel(rwपंचांग->mbox);
हटाओ_files:
	sysfs_हटाओ_files(rwपंचांग_to_kobj(rwपंचांग), mox_rwपंचांग_attrs);
put_kobj:
	kobject_put(rwपंचांग_to_kobj(rwपंचांग));
	वापस ret;
पूर्ण

अटल पूर्णांक turris_mox_rwपंचांग_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mox_rwपंचांग *rwपंचांग = platक्रमm_get_drvdata(pdev);

	rwपंचांग_unरेजिस्टर_debugfs(rwपंचांग);
	sysfs_हटाओ_files(rwपंचांग_to_kobj(rwपंचांग), mox_rwपंचांग_attrs);
	kobject_put(rwपंचांग_to_kobj(rwपंचांग));
	mbox_मुक्त_channel(rwपंचांग->mbox);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id turris_mox_rwपंचांग_match[] = अणु
	अणु .compatible = "cznic,turris-mox-rwtm", पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, turris_mox_rwपंचांग_match);

अटल काष्ठा platक्रमm_driver turris_mox_rwपंचांग_driver = अणु
	.probe	= turris_mox_rwपंचांग_probe,
	.हटाओ	= turris_mox_rwपंचांग_हटाओ,
	.driver	= अणु
		.name		= DRIVER_NAME,
		.of_match_table	= turris_mox_rwपंचांग_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(turris_mox_rwपंचांग_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Turris Mox rWTM firmware driver");
MODULE_AUTHOR("Marek Behun <kabel@kernel.org>");
