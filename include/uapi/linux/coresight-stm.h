<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __UAPI_CORESIGHT_STM_H_
#घोषणा __UAPI_CORESIGHT_STM_H_

#समावेश <linux/स्थिर.h>

#घोषणा STM_FLAG_TIMESTAMPED   _BITUL(3)
#घोषणा STM_FLAG_MARKED        _BITUL(4)
#घोषणा STM_FLAG_GUARANTEED    _BITUL(7)

/*
 * The CoreSight STM supports guaranteed and invariant timing
 * transactions.  Guaranteed transactions are guaranteed to be
 * traced, this might involve stalling the bus or प्रणाली to
 * ensure the transaction is accepted by the STM.  While invariant
 * timing transactions are not guaranteed to be traced, they
 * will take an invariant amount of समय regardless of the
 * state of the STM.
 */
क्रमागत अणु
	STM_OPTION_GUARANTEED = 0,
	STM_OPTION_INVARIANT,
पूर्ण;

#पूर्ण_अगर
