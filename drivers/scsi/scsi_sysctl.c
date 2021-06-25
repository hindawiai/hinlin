<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2003 Christoph Hellwig.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sysctl.h>

#समावेश "scsi_logging.h"
#समावेश "scsi_priv.h"


अटल काष्ठा ctl_table scsi_table[] = अणु
	अणु .procname	= "logging_level",
	  .data		= &scsi_logging_level,
	  .maxlen	= माप(scsi_logging_level),
	  .mode		= 0644,
	  .proc_handler	= proc_करोपूर्णांकvec पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table scsi_dir_table[] = अणु
	अणु .procname	= "scsi",
	  .mode		= 0555,
	  .child	= scsi_table पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table scsi_root_table[] = अणु
	अणु .procname	= "dev",
	  .mode		= 0555,
	  .child	= scsi_dir_table पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table_header *scsi_table_header;

पूर्णांक __init scsi_init_sysctl(व्योम)
अणु
	scsi_table_header = रेजिस्टर_sysctl_table(scsi_root_table);
	अगर (!scsi_table_header)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम scsi_निकास_sysctl(व्योम)
अणु
	unरेजिस्टर_sysctl_table(scsi_table_header);
पूर्ण
