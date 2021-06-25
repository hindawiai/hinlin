<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  tracefs.h - a pseuकरो file प्रणाली क्रम activating tracing
 *
 * Based on debugfs by: 2004 Greg Kroah-Harपंचांगan <greg@kroah.com>
 *
 *  Copyright (C) 2014 Red Hat Inc, author: Steven Rostedt <srostedt@redhat.com>
 *
 * tracefs is the file प्रणाली that is used by the tracing infraकाष्ठाure.
 */

#अगर_अघोषित _TRACEFS_H_
#घोषणा _TRACEFS_H_

#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/types.h>

काष्ठा file_operations;

#अगर_घोषित CONFIG_TRACING

काष्ठा dentry *tracefs_create_file(स्थिर अक्षर *name, umode_t mode,
				   काष्ठा dentry *parent, व्योम *data,
				   स्थिर काष्ठा file_operations *fops);

काष्ठा dentry *tracefs_create_dir(स्थिर अक्षर *name, काष्ठा dentry *parent);

व्योम tracefs_हटाओ(काष्ठा dentry *dentry);

काष्ठा dentry *tracefs_create_instance_dir(स्थिर अक्षर *name, काष्ठा dentry *parent,
					   पूर्णांक (*सूची_गढ़ो)(स्थिर अक्षर *name),
					   पूर्णांक (*सूची_हटाओ)(स्थिर अक्षर *name));

bool tracefs_initialized(व्योम);

#पूर्ण_अगर /* CONFIG_TRACING */

#पूर्ण_अगर
