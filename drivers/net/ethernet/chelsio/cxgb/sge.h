<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: sge.h                                                               *
 * $Revision: 1.11 $                                                          *
 * $Date: 2005/06/21 22:10:55 $                                              *
 * Description:                                                              *
 *  part of the Chelsio 10Gb Ethernet Driver.                                *
 *                                                                           *
 * This program is मुक्त software; you can redistribute it and/or modअगरy      *
 * it under the terms of the GNU General Public License, version 2, as       *
 * published by the Free Software Foundation.                                *
 *                                                                           *
 * You should have received a copy of the GNU General Public License aदीर्घ   *
 * with this program; अगर not, see <http://www.gnu.org/licenses/>.            *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED    *
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF      *
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.                     *
 *                                                                           *
 * http://www.chelsio.com                                                    *
 *                                                                           *
 * Copyright (c) 2003 - 2005 Chelsio Communications, Inc.                    *
 * All rights reserved.                                                      *
 *                                                                           *
 * Maपूर्णांकainers: मुख्यtainers@chelsio.com                                      *
 *                                                                           *
 * Authors: Dimitrios Michailidis   <dm@chelsio.com>                         *
 *          Tina Yang               <tainay@chelsio.com>                     *
 *          Felix Marti             <felix@chelsio.com>                      *
 *          Scott Barकरोne           <sbarकरोne@chelsio.com>                   *
 *          Kurt Ottaway            <kottaway@chelsio.com>                   *
 *          Frank DiMambro          <frank@chelsio.com>                      *
 *                                                                           *
 * History:                                                                  *
 *                                                                           *
 ****************************************************************************/

#अगर_अघोषित _CXGB_SGE_H_
#घोषणा _CXGB_SGE_H_

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/byteorder.h>

काष्ठा sge_पूर्णांकr_counts अणु
	अचिन्हित पूर्णांक rx_drops;        /* # of packets dropped due to no mem */
	अचिन्हित पूर्णांक pure_rsps;        /* # of non-payload responses */
	अचिन्हित पूर्णांक unhandled_irqs;   /* # of unhandled पूर्णांकerrupts */
	अचिन्हित पूर्णांक respQ_empty;      /* # बार respQ empty */
	अचिन्हित पूर्णांक respQ_overflow;   /* # respQ overflow (fatal) */
	अचिन्हित पूर्णांक मुक्तlistQ_empty;  /* # बार मुक्तlist empty */
	अचिन्हित पूर्णांक pkt_too_big;      /* packet too large (fatal) */
	अचिन्हित पूर्णांक pkt_mismatch;
	अचिन्हित पूर्णांक cmdQ_full[3];     /* not HW IRQ, host cmdQ[] full */
	अचिन्हित पूर्णांक cmdQ_restarted[3];/* # of बार cmdQ X was restarted */
पूर्ण;

काष्ठा sge_port_stats अणु
	u64 rx_cso_good;     /* # of successful RX csum offloads */
	u64 tx_cso;          /* # of TX checksum offloads */
	u64 tx_tso;          /* # of TSO requests */
	u64 vlan_xtract;     /* # of VLAN tag extractions */
	u64 vlan_insert;     /* # of VLAN tag insertions */
	u64 tx_need_hdrroom; /* # of TX skbs in need of more header room */
पूर्ण;

काष्ठा sk_buff;
काष्ठा net_device;
काष्ठा adapter;
काष्ठा sge_params;
काष्ठा sge;

काष्ठा sge *t1_sge_create(काष्ठा adapter *, काष्ठा sge_params *);
पूर्णांक t1_sge_configure(काष्ठा sge *, काष्ठा sge_params *);
पूर्णांक t1_sge_set_coalesce_params(काष्ठा sge *, काष्ठा sge_params *);
व्योम t1_sge_destroy(काष्ठा sge *);
irqवापस_t t1_पूर्णांकerrupt_thपढ़ो(पूर्णांक irq, व्योम *data);
irqवापस_t t1_पूर्णांकerrupt(पूर्णांक irq, व्योम *cookie);
पूर्णांक t1_poll(काष्ठा napi_काष्ठा *, पूर्णांक);

netdev_tx_t t1_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
व्योम t1_vlan_mode(काष्ठा adapter *adapter, netdev_features_t features);
व्योम t1_sge_start(काष्ठा sge *);
व्योम t1_sge_stop(काष्ठा sge *);
bool t1_sge_पूर्णांकr_error_handler(काष्ठा sge *sge);
व्योम t1_sge_पूर्णांकr_enable(काष्ठा sge *);
व्योम t1_sge_पूर्णांकr_disable(काष्ठा sge *);
व्योम t1_sge_पूर्णांकr_clear(काष्ठा sge *);
स्थिर काष्ठा sge_पूर्णांकr_counts *t1_sge_get_पूर्णांकr_counts(स्थिर काष्ठा sge *sge);
व्योम t1_sge_get_port_stats(स्थिर काष्ठा sge *sge, पूर्णांक port, काष्ठा sge_port_stats *);
अचिन्हित पूर्णांक t1_sched_update_parms(काष्ठा sge *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
			   अचिन्हित पूर्णांक);

#पूर्ण_अगर /* _CXGB_SGE_H_ */
