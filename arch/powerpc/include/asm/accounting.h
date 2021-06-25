<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Common समय accounting prototypes and such क्रम all ppc machines.
 */

#अगर_अघोषित __POWERPC_ACCOUNTING_H
#घोषणा __POWERPC_ACCOUNTING_H

/* Stuff क्रम accurate समय accounting */
काष्ठा cpu_accounting_data अणु
	/* Accumulated cpuसमय values to flush on ticks*/
	अचिन्हित दीर्घ uसमय;
	अचिन्हित दीर्घ sसमय;
#अगर_घोषित CONFIG_ARCH_HAS_SCALED_CPUTIME
	अचिन्हित दीर्घ uसमय_scaled;
	अचिन्हित दीर्घ sसमय_scaled;
#पूर्ण_अगर
	अचिन्हित दीर्घ gसमय;
	अचिन्हित दीर्घ hardirq_समय;
	अचिन्हित दीर्घ softirq_समय;
	अचिन्हित दीर्घ steal_समय;
	अचिन्हित दीर्घ idle_समय;
	/* Internal counters */
	अचिन्हित दीर्घ startसमय;	/* TB value snapshot */
	अचिन्हित दीर्घ startसमय_user;	/* TB value on निकास to usermode */
#अगर_घोषित CONFIG_ARCH_HAS_SCALED_CPUTIME
	अचिन्हित दीर्घ startspurr;	/* SPURR value snapshot */
	अचिन्हित दीर्घ uसमय_sspurr;	/* ->user_समय when ->startspurr set */
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर
