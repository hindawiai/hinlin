<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * File: sysctl.c
 *
 * Phonet /proc/sys/net/phonet पूर्णांकerface implementation
 *
 * Copyright (C) 2008 Nokia Corporation.
 *
 * Author: Rथऊmi Denis-Courmont
 */

#समावेश <linux/seqlock.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>

#समावेश <net/sock.h>
#समावेश <linux/phonet.h>
#समावेश <net/phonet/phonet.h>

#घोषणा DYNAMIC_PORT_MIN	0x40
#घोषणा DYNAMIC_PORT_MAX	0x7f

अटल DEFINE_SEQLOCK(local_port_range_lock);
अटल पूर्णांक local_port_range_min[2] = अणु0, 0पूर्ण;
अटल पूर्णांक local_port_range_max[2] = अणु1023, 1023पूर्ण;
अटल पूर्णांक local_port_range[2] = अणुDYNAMIC_PORT_MIN, DYNAMIC_PORT_MAXपूर्ण;
अटल काष्ठा ctl_table_header *phonet_table_hrd;

अटल व्योम set_local_port_range(पूर्णांक range[2])
अणु
	ग_लिखो_seqlock(&local_port_range_lock);
	local_port_range[0] = range[0];
	local_port_range[1] = range[1];
	ग_लिखो_sequnlock(&local_port_range_lock);
पूर्ण

व्योम phonet_get_local_port_range(पूर्णांक *min, पूर्णांक *max)
अणु
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = पढ़ो_seqbegin(&local_port_range_lock);
		अगर (min)
			*min = local_port_range[0];
		अगर (max)
			*max = local_port_range[1];
	पूर्ण जबतक (पढ़ो_seqretry(&local_port_range_lock, seq));
पूर्ण

अटल पूर्णांक proc_local_port_range(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;
	पूर्णांक range[2] = अणुlocal_port_range[0], local_port_range[1]पूर्ण;
	काष्ठा ctl_table पंचांगp = अणु
		.data = &range,
		.maxlen = माप(range),
		.mode = table->mode,
		.extra1 = &local_port_range_min,
		.extra2 = &local_port_range_max,
	पूर्ण;

	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && ret == 0) अणु
		अगर (range[1] < range[0])
			ret = -EINVAL;
		अन्यथा
			set_local_port_range(range);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा ctl_table phonet_table[] = अणु
	अणु
		.procname	= "local_port_range",
		.data		= &local_port_range,
		.maxlen		= माप(local_port_range),
		.mode		= 0644,
		.proc_handler	= proc_local_port_range,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

पूर्णांक __init phonet_sysctl_init(व्योम)
अणु
	phonet_table_hrd = रेजिस्टर_net_sysctl(&init_net, "net/phonet", phonet_table);
	वापस phonet_table_hrd == शून्य ? -ENOMEM : 0;
पूर्ण

व्योम phonet_sysctl_निकास(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(phonet_table_hrd);
पूर्ण
