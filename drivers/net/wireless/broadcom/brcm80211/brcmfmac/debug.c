<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012 Broadcom Corporation
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/devcoredump.h>

#समावेश <brcmu_wअगरi.h>
#समावेश <brcmu_utils.h>
#समावेश "core.h"
#समावेश "bus.h"
#समावेश "fweh.h"
#समावेश "debug.h"

पूर्णांक brcmf_debug_create_memdump(काष्ठा brcmf_bus *bus, स्थिर व्योम *data,
			       माप_प्रकार len)
अणु
	व्योम *dump;
	माप_प्रकार ramsize;
	पूर्णांक err;

	ramsize = brcmf_bus_get_ramsize(bus);
	अगर (!ramsize)
		वापस -ENOTSUPP;

	dump = vzalloc(len + ramsize);
	अगर (!dump)
		वापस -ENOMEM;

	अगर (data && len > 0)
		स_नकल(dump, data, len);
	err = brcmf_bus_get_memdump(bus, dump + len, ramsize);
	अगर (err) अणु
		vमुक्त(dump);
		वापस err;
	पूर्ण

	dev_coredumpv(bus->dev, dump, len + ramsize, GFP_KERNEL);

	वापस 0;
पूर्ण

काष्ठा dentry *brcmf_debugfs_get_devdir(काष्ठा brcmf_pub *drvr)
अणु
	वापस drvr->wiphy->debugfsdir;
पूर्ण

व्योम brcmf_debugfs_add_entry(काष्ठा brcmf_pub *drvr, स्थिर अक्षर *fn,
			    पूर्णांक (*पढ़ो_fn)(काष्ठा seq_file *seq, व्योम *data))
अणु
	WARN(!drvr->wiphy->debugfsdir, "wiphy not (yet) registered\n");
	debugfs_create_devm_seqfile(drvr->bus_अगर->dev, fn,
				    drvr->wiphy->debugfsdir, पढ़ो_fn);
पूर्ण
