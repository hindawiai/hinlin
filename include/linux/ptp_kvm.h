<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Virtual PTP 1588 घड़ी क्रम use with KVM guests
 *
 * Copyright (C) 2017 Red Hat Inc.
 */

#अगर_अघोषित _PTP_KVM_H_
#घोषणा _PTP_KVM_H_

काष्ठा बारpec64;
काष्ठा घड़ीsource;

पूर्णांक kvm_arch_ptp_init(व्योम);
पूर्णांक kvm_arch_ptp_get_घड़ी(काष्ठा बारpec64 *ts);
पूर्णांक kvm_arch_ptp_get_crosststamp(u64 *cycle,
		काष्ठा बारpec64 *tspec, काष्ठा घड़ीsource **cs);

#पूर्ण_अगर /* _PTP_KVM_H_ */
