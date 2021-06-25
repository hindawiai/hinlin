<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012-2016, Intel Corporation. All rights reserved
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/mei.h>

#समावेश "mei_dev.h"
#समावेश "client.h"
#समावेश "hw.h"

अटल पूर्णांक mei_dbgfs_meclients_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा mei_device *dev = m->निजी;
	काष्ठा mei_me_client *me_cl;
	पूर्णांक i = 0;

	अगर (!dev)
		वापस -ENODEV;

	करोwn_पढ़ो(&dev->me_clients_rwsem);

	seq_माला_दो(m, "  |id|fix|         UUID                       |con|msg len|sb|refc|vt|\n");

	/*  अगर the driver is not enabled the list won't be consistent */
	अगर (dev->dev_state != MEI_DEV_ENABLED)
		जाओ out;

	list_क्रम_each_entry(me_cl, &dev->me_clients, list) अणु
		अगर (!mei_me_cl_get(me_cl))
			जारी;

		seq_म_लिखो(m, "%2d|%2d|%3d|%pUl|%3d|%7d|%2d|%4d|%2d|\n",
			   i++, me_cl->client_id,
			   me_cl->props.fixed_address,
			   &me_cl->props.protocol_name,
			   me_cl->props.max_number_of_connections,
			   me_cl->props.max_msg_length,
			   me_cl->props.single_recv_buf,
			   kref_पढ़ो(&me_cl->refcnt),
			   me_cl->props.vt_supported);
		mei_me_cl_put(me_cl);
	पूर्ण

out:
	up_पढ़ो(&dev->me_clients_rwsem);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(mei_dbgfs_meclients);

अटल पूर्णांक mei_dbgfs_active_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा mei_device *dev = m->निजी;
	काष्ठा mei_cl *cl;
	पूर्णांक i = 0;

	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->device_lock);

	seq_माला_दो(m, "   |me|host|state|rd|wr|wrq\n");

	/*  अगर the driver is not enabled the list won't be consistent */
	अगर (dev->dev_state != MEI_DEV_ENABLED)
		जाओ out;

	list_क्रम_each_entry(cl, &dev->file_list, link) अणु

		seq_म_लिखो(m, "%3d|%2d|%4d|%5d|%2d|%2d|%3u\n",
			   i, mei_cl_me_id(cl), cl->host_client_id, cl->state,
			   !list_empty(&cl->rd_completed), cl->writing_state,
			   cl->tx_cb_queued);
		i++;
	पूर्ण
out:
	mutex_unlock(&dev->device_lock);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(mei_dbgfs_active);

अटल पूर्णांक mei_dbgfs_devstate_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा mei_device *dev = m->निजी;

	seq_म_लिखो(m, "dev: %s\n", mei_dev_state_str(dev->dev_state));
	seq_म_लिखो(m, "hbm: %s\n", mei_hbm_state_str(dev->hbm_state));

	अगर (dev->hbm_state >= MEI_HBM_ENUM_CLIENTS &&
	    dev->hbm_state <= MEI_HBM_STARTED) अणु
		seq_माला_दो(m, "hbm features:\n");
		seq_म_लिखो(m, "\tPG: %01d\n", dev->hbm_f_pg_supported);
		seq_म_लिखो(m, "\tDC: %01d\n", dev->hbm_f_dc_supported);
		seq_म_लिखो(m, "\tIE: %01d\n", dev->hbm_f_ie_supported);
		seq_म_लिखो(m, "\tDOT: %01d\n", dev->hbm_f_करोt_supported);
		seq_म_लिखो(m, "\tEV: %01d\n", dev->hbm_f_ev_supported);
		seq_म_लिखो(m, "\tFA: %01d\n", dev->hbm_f_fa_supported);
		seq_म_लिखो(m, "\tOS: %01d\n", dev->hbm_f_os_supported);
		seq_म_लिखो(m, "\tDR: %01d\n", dev->hbm_f_dr_supported);
		seq_म_लिखो(m, "\tVT: %01d\n", dev->hbm_f_vt_supported);
		seq_म_लिखो(m, "\tCAP: %01d\n", dev->hbm_f_cap_supported);
		seq_म_लिखो(m, "\tCD: %01d\n", dev->hbm_f_cd_supported);
	पूर्ण

	seq_म_लिखो(m, "pg:  %s, %s\n",
		   mei_pg_is_enabled(dev) ? "ENABLED" : "DISABLED",
		   mei_pg_state_str(mei_pg_state(dev)));
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(mei_dbgfs_devstate);

अटल sमाप_प्रकार mei_dbgfs_ग_लिखो_allow_fa(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mei_device *dev;
	पूर्णांक ret;

	dev = container_of(file->निजी_data,
			   काष्ठा mei_device, allow_fixed_address);

	ret = debugfs_ग_लिखो_file_bool(file, user_buf, count, ppos);
	अगर (ret < 0)
		वापस ret;
	dev->override_fixed_address = true;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations mei_dbgfs_allow_fa_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = debugfs_पढ़ो_file_bool,
	.ग_लिखो = mei_dbgfs_ग_लिखो_allow_fa,
	.llseek = generic_file_llseek,
पूर्ण;

/**
 * mei_dbgfs_deरेजिस्टर - Remove the debugfs files and directories
 *
 * @dev: the mei device काष्ठाure
 */
व्योम mei_dbgfs_deरेजिस्टर(काष्ठा mei_device *dev)
अणु
	अगर (!dev->dbgfs_dir)
		वापस;
	debugfs_हटाओ_recursive(dev->dbgfs_dir);
	dev->dbgfs_dir = शून्य;
पूर्ण

/**
 * mei_dbgfs_रेजिस्टर - Add the debugfs files
 *
 * @dev: the mei device काष्ठाure
 * @name: the mei device name
 */
व्योम mei_dbgfs_रेजिस्टर(काष्ठा mei_device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir(name, शून्य);
	dev->dbgfs_dir = dir;

	debugfs_create_file("meclients", S_IRUSR, dir, dev,
			    &mei_dbgfs_meclients_fops);
	debugfs_create_file("active", S_IRUSR, dir, dev,
			    &mei_dbgfs_active_fops);
	debugfs_create_file("devstate", S_IRUSR, dir, dev,
			    &mei_dbgfs_devstate_fops);
	debugfs_create_file("allow_fixed_address", S_IRUSR | S_IWUSR, dir,
			    &dev->allow_fixed_address,
			    &mei_dbgfs_allow_fa_fops);
पूर्ण
