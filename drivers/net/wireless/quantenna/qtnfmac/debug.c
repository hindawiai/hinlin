<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#समावेश "debug.h"

व्योम qtnf_debugfs_init(काष्ठा qtnf_bus *bus, स्थिर अक्षर *name)
अणु
	काष्ठा dentry *parent = qtnf_get_debugfs_dir();

	bus->dbg_dir = debugfs_create_dir(name, parent);
पूर्ण

व्योम qtnf_debugfs_हटाओ(काष्ठा qtnf_bus *bus)
अणु
	debugfs_हटाओ_recursive(bus->dbg_dir);
	bus->dbg_dir = शून्य;
पूर्ण

व्योम qtnf_debugfs_add_entry(काष्ठा qtnf_bus *bus, स्थिर अक्षर *name,
			    पूर्णांक (*fn)(काष्ठा seq_file *seq, व्योम *data))
अणु
	debugfs_create_devm_seqfile(bus->dev, name, bus->dbg_dir, fn);
पूर्ण
