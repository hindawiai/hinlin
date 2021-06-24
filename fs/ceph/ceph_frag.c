<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ceph 'frag' type
 */
#समावेश <linux/module.h>
#समावेश <linux/ceph/types.h>

पूर्णांक ceph_frag_compare(__u32 a, __u32 b)
अणु
	अचिन्हित va = ceph_frag_value(a);
	अचिन्हित vb = ceph_frag_value(b);
	अगर (va < vb)
		वापस -1;
	अगर (va > vb)
		वापस 1;
	va = ceph_frag_bits(a);
	vb = ceph_frag_bits(b);
	अगर (va < vb)
		वापस -1;
	अगर (va > vb)
		वापस 1;
	वापस 0;
पूर्ण
