<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2017-2019 Intel Corporation.

#समावेश <linux/device.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश "bus.h"

अटल काष्ठा dentry *sdw_debugfs_root;

व्योम sdw_bus_debugfs_init(काष्ठा sdw_bus *bus)
अणु
	अक्षर name[16];

	अगर (!sdw_debugfs_root)
		वापस;

	/* create the debugfs master-N */
	snम_लिखो(name, माप(name), "master-%d", bus->link_id);
	bus->debugfs = debugfs_create_dir(name, sdw_debugfs_root);
पूर्ण

व्योम sdw_bus_debugfs_निकास(काष्ठा sdw_bus *bus)
अणु
	debugfs_हटाओ_recursive(bus->debugfs);
पूर्ण

#घोषणा RD_BUF (3 * PAGE_SIZE)

अटल sमाप_प्रकार sdw_प्र_लिखो(काष्ठा sdw_slave *slave,
			   अक्षर *buf, माप_प्रकार pos, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक value;

	value = sdw_पढ़ो(slave, reg);

	अगर (value < 0)
		वापस scnम_लिखो(buf + pos, RD_BUF - pos, "%3x\tXX\n", reg);
	अन्यथा
		वापस scnम_लिखो(buf + pos, RD_BUF - pos,
				"%3x\t%2x\n", reg, value);
पूर्ण

अटल पूर्णांक sdw_slave_reg_show(काष्ठा seq_file *s_file, व्योम *data)
अणु
	काष्ठा sdw_slave *slave = s_file->निजी;
	अक्षर *buf;
	sमाप_प्रकार ret;
	पूर्णांक i, j;

	buf = kzalloc(RD_BUF, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = scnम_लिखो(buf, RD_BUF, "Register  Value\n");

	/* DP0 non-banked रेजिस्टरs */
	ret += scnम_लिखो(buf + ret, RD_BUF - ret, "\nDP0\n");
	क्रम (i = SDW_DP0_INT; i <= SDW_DP0_PREPARECTRL; i++)
		ret += sdw_प्र_लिखो(slave, buf, ret, i);

	/* DP0 Bank 0 रेजिस्टरs */
	ret += scnम_लिखो(buf + ret, RD_BUF - ret, "Bank0\n");
	ret += sdw_प्र_लिखो(slave, buf, ret, SDW_DP0_CHANNELEN);
	क्रम (i = SDW_DP0_SAMPLECTRL1; i <= SDW_DP0_LANECTRL; i++)
		ret += sdw_प्र_लिखो(slave, buf, ret, i);

	/* DP0 Bank 1 रेजिस्टरs */
	ret += scnम_लिखो(buf + ret, RD_BUF - ret, "Bank1\n");
	ret += sdw_प्र_लिखो(slave, buf, ret,
			SDW_DP0_CHANNELEN + SDW_BANK1_OFFSET);
	क्रम (i = SDW_DP0_SAMPLECTRL1 + SDW_BANK1_OFFSET;
			i <= SDW_DP0_LANECTRL + SDW_BANK1_OFFSET; i++)
		ret += sdw_प्र_लिखो(slave, buf, ret, i);

	/* SCP रेजिस्टरs */
	ret += scnम_लिखो(buf + ret, RD_BUF - ret, "\nSCP\n");
	क्रम (i = SDW_SCP_INT1; i <= SDW_SCP_BANKDELAY; i++)
		ret += sdw_प्र_लिखो(slave, buf, ret, i);
	क्रम (i = SDW_SCP_DEVID_0; i <= SDW_SCP_DEVID_5; i++)
		ret += sdw_प्र_लिखो(slave, buf, ret, i);

	/*
	 * SCP Bank 0/1 रेजिस्टरs are पढ़ो-only and cannot be
	 * retrieved from the Slave. The Master typically keeps track
	 * of the current frame size so the inक्रमmation can be found
	 * in other places
	 */

	/* DP1..14 रेजिस्टरs */
	क्रम (i = 1; SDW_VALID_PORT_RANGE(i); i++) अणु

		/* DPi रेजिस्टरs */
		ret += scnम_लिखो(buf + ret, RD_BUF - ret, "\nDP%d\n", i);
		क्रम (j = SDW_DPN_INT(i); j <= SDW_DPN_PREPARECTRL(i); j++)
			ret += sdw_प्र_लिखो(slave, buf, ret, j);

		/* DPi Bank0 रेजिस्टरs */
		ret += scnम_लिखो(buf + ret, RD_BUF - ret, "Bank0\n");
		क्रम (j = SDW_DPN_CHANNELEN_B0(i);
		     j <= SDW_DPN_LANECTRL_B0(i); j++)
			ret += sdw_प्र_लिखो(slave, buf, ret, j);

		/* DPi Bank1 रेजिस्टरs */
		ret += scnम_लिखो(buf + ret, RD_BUF - ret, "Bank1\n");
		क्रम (j = SDW_DPN_CHANNELEN_B1(i);
		     j <= SDW_DPN_LANECTRL_B1(i); j++)
			ret += sdw_प्र_लिखो(slave, buf, ret, j);
	पूर्ण

	seq_म_लिखो(s_file, "%s", buf);
	kमुक्त(buf);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(sdw_slave_reg);

व्योम sdw_slave_debugfs_init(काष्ठा sdw_slave *slave)
अणु
	काष्ठा dentry *master;
	काष्ठा dentry *d;
	अक्षर name[32];

	master = slave->bus->debugfs;

	/* create the debugfs slave-name */
	snम_लिखो(name, माप(name), "%s", dev_name(&slave->dev));
	d = debugfs_create_dir(name, master);

	debugfs_create_file("registers", 0400, d, slave, &sdw_slave_reg_fops);

	slave->debugfs = d;
पूर्ण

व्योम sdw_slave_debugfs_निकास(काष्ठा sdw_slave *slave)
अणु
	debugfs_हटाओ_recursive(slave->debugfs);
पूर्ण

व्योम sdw_debugfs_init(व्योम)
अणु
	sdw_debugfs_root = debugfs_create_dir("soundwire", शून्य);
पूर्ण

व्योम sdw_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(sdw_debugfs_root);
पूर्ण
