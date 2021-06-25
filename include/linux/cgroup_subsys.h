<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * List of cgroup subप्रणालीs.
 *
 * DO NOT ADD ANY SUBSYSTEM WITHOUT EXPLICIT ACKS FROM CGROUP MAINTAINERS.
 */

/*
 * This file *must* be included with SUBSYS() defined.
 */

#अगर IS_ENABLED(CONFIG_CPUSETS)
SUBSYS(cpuset)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_CGROUP_SCHED)
SUBSYS(cpu)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_CGROUP_CPUACCT)
SUBSYS(cpuacct)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_BLK_CGROUP)
SUBSYS(io)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MEMCG)
SUBSYS(memory)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_CGROUP_DEVICE)
SUBSYS(devices)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_CGROUP_FREEZER)
SUBSYS(मुक्तzer)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_CGROUP_NET_CLASSID)
SUBSYS(net_cls)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_CGROUP_PERF)
SUBSYS(perf_event)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_CGROUP_NET_PRIO)
SUBSYS(net_prio)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_CGROUP_HUGETLB)
SUBSYS(hugetlb)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_CGROUP_PIDS)
SUBSYS(pids)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_CGROUP_RDMA)
SUBSYS(rdma)
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_CGROUP_MISC)
SUBSYS(misc)
#पूर्ण_अगर

/*
 * The following subप्रणालीs are not supported on the शेष hierarchy.
 */
#अगर IS_ENABLED(CONFIG_CGROUP_DEBUG)
SUBSYS(debug)
#पूर्ण_अगर

/*
 * DO NOT ADD ANY SUBSYSTEM WITHOUT EXPLICIT ACKS FROM CGROUP MAINTAINERS.
 */
