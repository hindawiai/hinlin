<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_POWERPC_PERF_HV_GPCI_H_
#घोषणा LINUX_POWERPC_PERF_HV_GPCI_H_

/*
 * counter info version => fw version/reference (spec version)
 *
 * 8 => घातer8 (1.07)
 * [7 is skipped by spec 1.07]
 * 6 => TLBIE (1.07)
 * 5 => v7r7m0.phyp (1.05)
 * [4 skipped]
 * 3 => v7r6m0.phyp (?)
 * [1,2 skipped]
 * 0 => v7rअणु2,3,4पूर्णm0.phyp (?)
 */
#घोषणा COUNTER_INFO_VERSION_CURRENT 0x8

/* capability mask masks. */
क्रमागत अणु
	HV_GPCI_CM_GA = (1 << 7),
	HV_GPCI_CM_EXPANDED = (1 << 6),
	HV_GPCI_CM_LAB = (1 << 5)
पूर्ण;

#घोषणा REQUEST_खाता "../hv-gpci-requests.h"
#घोषणा NAME_LOWER hv_gpci
#घोषणा NAME_UPPER HV_GPCI
#समावेश "req-gen/perf.h"
#अघोषित REQUEST_खाता
#अघोषित NAME_LOWER
#अघोषित NAME_UPPER

#पूर्ण_अगर
