<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2012 Solarflare Communications Inc.
 */

#अगर_अघोषित EF4_SELFTEST_H
#घोषणा EF4_SELFTEST_H

#समावेश "net_driver.h"

/*
 * Self tests
 */

काष्ठा ef4_loopback_self_tests अणु
	पूर्णांक tx_sent[EF4_TXQ_TYPES];
	पूर्णांक tx_करोne[EF4_TXQ_TYPES];
	पूर्णांक rx_good;
	पूर्णांक rx_bad;
पूर्ण;

#घोषणा EF4_MAX_PHY_TESTS 20

/* Efx self test results
 * For fields which are not counters, 1 indicates success and -1
 * indicates failure; 0 indicates test could not be run.
 */
काष्ठा ef4_self_tests अणु
	/* online tests */
	पूर्णांक phy_alive;
	पूर्णांक nvram;
	पूर्णांक पूर्णांकerrupt;
	पूर्णांक eventq_dma[EF4_MAX_CHANNELS];
	पूर्णांक eventq_पूर्णांक[EF4_MAX_CHANNELS];
	/* offline tests */
	पूर्णांक memory;
	पूर्णांक रेजिस्टरs;
	पूर्णांक phy_ext[EF4_MAX_PHY_TESTS];
	काष्ठा ef4_loopback_self_tests loopback[LOOPBACK_TEST_MAX + 1];
पूर्ण;

व्योम ef4_loopback_rx_packet(काष्ठा ef4_nic *efx, स्थिर अक्षर *buf_ptr,
			    पूर्णांक pkt_len);
पूर्णांक ef4_selftest(काष्ठा ef4_nic *efx, काष्ठा ef4_self_tests *tests,
		 अचिन्हित flags);
व्योम ef4_selftest_async_start(काष्ठा ef4_nic *efx);
व्योम ef4_selftest_async_cancel(काष्ठा ef4_nic *efx);
व्योम ef4_selftest_async_work(काष्ठा work_काष्ठा *data);

#पूर्ण_अगर /* EF4_SELFTEST_H */
