<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>

#समावेश "ixgbe.h"

अटल काष्ठा dentry *ixgbe_dbg_root;

अटल अक्षर ixgbe_dbg_reg_ops_buf[256] = "";

अटल sमाप_प्रकार ixgbe_dbg_common_ops_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
					 माप_प्रकार count, loff_t *ppos,
					 अक्षर *dbg_buf)
अणु
	काष्ठा ixgbe_adapter *adapter = filp->निजी_data;
	अक्षर *buf;
	पूर्णांक len;

	/* करोn't allow partial पढ़ोs */
	अगर (*ppos != 0)
		वापस 0;

	buf = kaप्र_लिखो(GFP_KERNEL, "%s: %s\n",
			adapter->netdev->name, dbg_buf);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (count < म_माप(buf)) अणु
		kमुक्त(buf);
		वापस -ENOSPC;
	पूर्ण

	len = simple_पढ़ो_from_buffer(buffer, count, ppos, buf, म_माप(buf));

	kमुक्त(buf);
	वापस len;
पूर्ण

/**
 * ixgbe_dbg_reg_ops_पढ़ो - पढ़ो क्रम reg_ops datum
 * @filp: the खोलोed file
 * @buffer: where to ग_लिखो the data क्रम the user to पढ़ो
 * @count: the size of the user's buffer
 * @ppos: file position offset
 **/
अटल sमाप_प्रकार ixgbe_dbg_reg_ops_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				      माप_प्रकार count, loff_t *ppos)
अणु
	वापस ixgbe_dbg_common_ops_पढ़ो(filp, buffer, count, ppos,
					 ixgbe_dbg_reg_ops_buf);
पूर्ण

/**
 * ixgbe_dbg_reg_ops_ग_लिखो - ग_लिखो पूर्णांकo reg_ops datum
 * @filp: the खोलोed file
 * @buffer: where to find the user's data
 * @count: the length of the user's data
 * @ppos: file position offset
 **/
अटल sमाप_प्रकार ixgbe_dbg_reg_ops_ग_लिखो(काष्ठा file *filp,
				     स्थिर अक्षर __user *buffer,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ixgbe_adapter *adapter = filp->निजी_data;
	पूर्णांक len;

	/* करोn't allow partial ग_लिखोs */
	अगर (*ppos != 0)
		वापस 0;
	अगर (count >= माप(ixgbe_dbg_reg_ops_buf))
		वापस -ENOSPC;

	len = simple_ग_लिखो_to_buffer(ixgbe_dbg_reg_ops_buf,
				     माप(ixgbe_dbg_reg_ops_buf)-1,
				     ppos,
				     buffer,
				     count);
	अगर (len < 0)
		वापस len;

	ixgbe_dbg_reg_ops_buf[len] = '\0';

	अगर (म_भेदन(ixgbe_dbg_reg_ops_buf, "write", 5) == 0) अणु
		u32 reg, value;
		पूर्णांक cnt;
		cnt = माला_पूछो(&ixgbe_dbg_reg_ops_buf[5], "%x %x", &reg, &value);
		अगर (cnt == 2) अणु
			IXGBE_WRITE_REG(&adapter->hw, reg, value);
			value = IXGBE_READ_REG(&adapter->hw, reg);
			e_dev_info("write: 0x%08x = 0x%08x\n", reg, value);
		पूर्ण अन्यथा अणु
			e_dev_info("write <reg> <value>\n");
		पूर्ण
	पूर्ण अन्यथा अगर (म_भेदन(ixgbe_dbg_reg_ops_buf, "read", 4) == 0) अणु
		u32 reg, value;
		पूर्णांक cnt;
		cnt = माला_पूछो(&ixgbe_dbg_reg_ops_buf[4], "%x", &reg);
		अगर (cnt == 1) अणु
			value = IXGBE_READ_REG(&adapter->hw, reg);
			e_dev_info("read 0x%08x = 0x%08x\n", reg, value);
		पूर्ण अन्यथा अणु
			e_dev_info("read <reg>\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		e_dev_info("Unknown command %s\n", ixgbe_dbg_reg_ops_buf);
		e_dev_info("Available commands:\n");
		e_dev_info("   read <reg>\n");
		e_dev_info("   write <reg> <value>\n");
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations ixgbe_dbg_reg_ops_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो =  ixgbe_dbg_reg_ops_पढ़ो,
	.ग_लिखो = ixgbe_dbg_reg_ops_ग_लिखो,
पूर्ण;

अटल अक्षर ixgbe_dbg_netdev_ops_buf[256] = "";

/**
 * ixgbe_dbg_netdev_ops_पढ़ो - पढ़ो क्रम netdev_ops datum
 * @filp: the खोलोed file
 * @buffer: where to ग_लिखो the data क्रम the user to पढ़ो
 * @count: the size of the user's buffer
 * @ppos: file position offset
 **/
अटल sमाप_प्रकार ixgbe_dbg_netdev_ops_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
					 माप_प्रकार count, loff_t *ppos)
अणु
	वापस ixgbe_dbg_common_ops_पढ़ो(filp, buffer, count, ppos,
					 ixgbe_dbg_netdev_ops_buf);
पूर्ण

/**
 * ixgbe_dbg_netdev_ops_ग_लिखो - ग_लिखो पूर्णांकo netdev_ops datum
 * @filp: the खोलोed file
 * @buffer: where to find the user's data
 * @count: the length of the user's data
 * @ppos: file position offset
 **/
अटल sमाप_प्रकार ixgbe_dbg_netdev_ops_ग_लिखो(काष्ठा file *filp,
					  स्थिर अक्षर __user *buffer,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ixgbe_adapter *adapter = filp->निजी_data;
	पूर्णांक len;

	/* करोn't allow partial ग_लिखोs */
	अगर (*ppos != 0)
		वापस 0;
	अगर (count >= माप(ixgbe_dbg_netdev_ops_buf))
		वापस -ENOSPC;

	len = simple_ग_लिखो_to_buffer(ixgbe_dbg_netdev_ops_buf,
				     माप(ixgbe_dbg_netdev_ops_buf)-1,
				     ppos,
				     buffer,
				     count);
	अगर (len < 0)
		वापस len;

	ixgbe_dbg_netdev_ops_buf[len] = '\0';

	अगर (म_भेदन(ixgbe_dbg_netdev_ops_buf, "tx_timeout", 10) == 0) अणु
		/* TX Queue number below is wrong, but ixgbe करोes not use it */
		adapter->netdev->netdev_ops->nकरो_tx_समयout(adapter->netdev,
							    अच_पूर्णांक_उच्च);
		e_dev_info("tx_timeout called\n");
	पूर्ण अन्यथा अणु
		e_dev_info("Unknown command: %s\n", ixgbe_dbg_netdev_ops_buf);
		e_dev_info("Available commands:\n");
		e_dev_info("    tx_timeout\n");
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations ixgbe_dbg_netdev_ops_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = ixgbe_dbg_netdev_ops_पढ़ो,
	.ग_लिखो = ixgbe_dbg_netdev_ops_ग_लिखो,
पूर्ण;

/**
 * ixgbe_dbg_adapter_init - setup the debugfs directory क्रम the adapter
 * @adapter: the adapter that is starting up
 **/
व्योम ixgbe_dbg_adapter_init(काष्ठा ixgbe_adapter *adapter)
अणु
	स्थिर अक्षर *name = pci_name(adapter->pdev);

	adapter->ixgbe_dbg_adapter = debugfs_create_dir(name, ixgbe_dbg_root);
	debugfs_create_file("reg_ops", 0600, adapter->ixgbe_dbg_adapter,
			    adapter, &ixgbe_dbg_reg_ops_fops);
	debugfs_create_file("netdev_ops", 0600, adapter->ixgbe_dbg_adapter,
			    adapter, &ixgbe_dbg_netdev_ops_fops);
पूर्ण

/**
 * ixgbe_dbg_adapter_निकास - clear out the adapter's debugfs entries
 * @adapter: the adapter that is निकासing
 **/
व्योम ixgbe_dbg_adapter_निकास(काष्ठा ixgbe_adapter *adapter)
अणु
	debugfs_हटाओ_recursive(adapter->ixgbe_dbg_adapter);
	adapter->ixgbe_dbg_adapter = शून्य;
पूर्ण

/**
 * ixgbe_dbg_init - start up debugfs क्रम the driver
 **/
व्योम ixgbe_dbg_init(व्योम)
अणु
	ixgbe_dbg_root = debugfs_create_dir(ixgbe_driver_name, शून्य);
पूर्ण

/**
 * ixgbe_dbg_निकास - clean out the driver's debugfs entries
 **/
व्योम ixgbe_dbg_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(ixgbe_dbg_root);
पूर्ण
