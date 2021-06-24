<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2021 Microsoft Corporation
 *
 * Author: Lakshmi Ramasubramanian (nramas@linux.microsoft.com)
 *
 * Measure critical data काष्ठाures मुख्यtaपूर्णांकed by SELinux
 * using IMA subप्रणाली.
 */

#अगर_अघोषित _SELINUX_IMA_H_
#घोषणा _SELINUX_IMA_H_

#समावेश "security.h"

#अगर_घोषित CONFIG_IMA
बाह्य व्योम selinux_ima_measure_state(काष्ठा selinux_state *selinux_state);
बाह्य व्योम selinux_ima_measure_state_locked(
			काष्ठा selinux_state *selinux_state);
#अन्यथा
अटल अंतरभूत व्योम selinux_ima_measure_state(काष्ठा selinux_state *selinux_state)
अणु
पूर्ण
अटल अंतरभूत व्योम selinux_ima_measure_state_locked(
			काष्ठा selinux_state *selinux_state)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* _SELINUX_IMA_H_ */
