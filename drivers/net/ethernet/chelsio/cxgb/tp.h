<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* $Date: 2005/03/07 23:59:05 $ $RCSfile: tp.h,v $ $Revision: 1.20 $ */
#अगर_अघोषित CHELSIO_TP_H
#घोषणा CHELSIO_TP_H

#समावेश "common.h"

#घोषणा TP_MAX_RX_COALESCING_SIZE 16224U

काष्ठा tp_mib_statistics अणु

	/* IP */
	u32 ipInReceive_hi;
	u32 ipInReceive_lo;
	u32 ipInHdrErrors_hi;
	u32 ipInHdrErrors_lo;
	u32 ipInAddrErrors_hi;
	u32 ipInAddrErrors_lo;
	u32 ipInUnknownProtos_hi;
	u32 ipInUnknownProtos_lo;
	u32 ipInDiscards_hi;
	u32 ipInDiscards_lo;
	u32 ipInDelivers_hi;
	u32 ipInDelivers_lo;
	u32 ipOutRequests_hi;
	u32 ipOutRequests_lo;
	u32 ipOutDiscards_hi;
	u32 ipOutDiscards_lo;
	u32 ipOutNoRoutes_hi;
	u32 ipOutNoRoutes_lo;
	u32 ipReयंत्रTimeout;
	u32 ipReयंत्रReqds;
	u32 ipReयंत्रOKs;
	u32 ipReयंत्रFails;

	u32 reserved[8];

	/* TCP */
	u32 tcpActiveOpens;
	u32 tcpPassiveOpens;
	u32 tcpAttemptFails;
	u32 tcpEstabResets;
	u32 tcpOutRsts;
	u32 tcpCurrEstab;
	u32 tcpInSegs_hi;
	u32 tcpInSegs_lo;
	u32 tcpOutSegs_hi;
	u32 tcpOutSegs_lo;
	u32 tcpRetransSeg_hi;
	u32 tcpRetransSeg_lo;
	u32 tcpInErrs_hi;
	u32 tcpInErrs_lo;
	u32 tcpRtoMin;
	u32 tcpRtoMax;
पूर्ण;

काष्ठा petp;
काष्ठा tp_params;

काष्ठा petp *t1_tp_create(adapter_t *adapter, काष्ठा tp_params *p);
व्योम t1_tp_destroy(काष्ठा petp *tp);

व्योम t1_tp_पूर्णांकr_disable(काष्ठा petp *tp);
व्योम t1_tp_पूर्णांकr_enable(काष्ठा petp *tp);
व्योम t1_tp_पूर्णांकr_clear(काष्ठा petp *tp);
पूर्णांक t1_tp_पूर्णांकr_handler(काष्ठा petp *tp);

व्योम t1_tp_get_mib_statistics(adapter_t *adap, काष्ठा tp_mib_statistics *tps);
व्योम t1_tp_set_tcp_checksum_offload(काष्ठा petp *tp, पूर्णांक enable);
व्योम t1_tp_set_ip_checksum_offload(काष्ठा petp *tp, पूर्णांक enable);
पूर्णांक t1_tp_set_coalescing_size(काष्ठा petp *tp, अचिन्हित पूर्णांक size);
पूर्णांक t1_tp_reset(काष्ठा petp *tp, काष्ठा tp_params *p, अचिन्हित पूर्णांक tp_clk);
#पूर्ण_अगर
