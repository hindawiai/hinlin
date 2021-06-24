<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */
#समावेश <यंत्र/bootinfo.h>

#समावेश <loongson.h>

व्योम __init mach_prom_init_machtype(व्योम)
अणु
	/* We share the same kernel image file among Lemote 2F family
	 * of machines, and provide the machtype= kernel command line
	 * to users to indicate their machine, this command line will
	 * be passed by the latest PMON स्वतःmatically. and क्रमtunately,
	 * up to now, we can get the machine type from the PMON_VER=
	 * commandline directly except the NAS machine, In the old
	 * machines, this will help the users a lot.
	 *
	 * If no "machtype=" passed, get machine type from "PMON_VER=".
	 *	PMON_VER=LM8089		Lemote 8.9'' netbook
	 *		 LM8101		Lemote 10.1'' netbook
	 *	(The above two netbooks have the same kernel support)
	 *		 LM6XXX		Lemote FuLoong(2F) box series
	 *		 LM9XXX		Lemote LynLoong PC series
	 */
	अगर (म_माला(arcs_cmdline, "PMON_VER=LM")) अणु
		अगर (म_माला(arcs_cmdline, "PMON_VER=LM8"))
			mips_machtype = MACH_LEMOTE_YL2F89;
		अन्यथा अगर (म_माला(arcs_cmdline, "PMON_VER=LM6"))
			mips_machtype = MACH_LEMOTE_FL2F;
		अन्यथा अगर (म_माला(arcs_cmdline, "PMON_VER=LM9"))
			mips_machtype = MACH_LEMOTE_LL2F;
		अन्यथा
			mips_machtype = MACH_LEMOTE_NAS;

		म_जोड़ो(arcs_cmdline, " machtype=");
		म_जोड़ो(arcs_cmdline, get_प्रणाली_type());
		म_जोड़ो(arcs_cmdline, " ");
	पूर्ण
पूर्ण
