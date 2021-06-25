<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: gmac.h                                                              *
 * $Revision: 1.6 $                                                          *
 * $Date: 2005/06/21 18:29:47 $                                              *
 * Description:                                                              *
 *  Generic MAC functionality.                                               *
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

#अगर_अघोषित _CXGB_GMAC_H_
#घोषणा _CXGB_GMAC_H_

#समावेश "common.h"

क्रमागत अणु
	MAC_STATS_UPDATE_FAST,
	MAC_STATS_UPDATE_FULL
पूर्ण;

क्रमागत अणु
	MAC_सूचीECTION_RX = 1,
	MAC_सूचीECTION_TX = 2
पूर्ण;

काष्ठा cmac_statistics अणु
	/* Transmit */
	u64 TxOctetsOK;
	u64 TxOctetsBad;
	u64 TxUnicastFramesOK;
	u64 TxMulticastFramesOK;
	u64 TxBroadcastFramesOK;
	u64 TxPauseFrames;
	u64 TxFramesWithDeferredXmissions;
	u64 TxLateCollisions;
	u64 TxTotalCollisions;
	u64 TxFramesAbortedDueToXSCollisions;
	u64 TxUnderrun;
	u64 TxLengthErrors;
	u64 TxInternalMACXmitError;
	u64 TxFramesWithExcessiveDeferral;
	u64 TxFCSErrors;
	u64 TxJumboFramesOK;
	u64 TxJumboOctetsOK;

	/* Receive */
	u64 RxOctetsOK;
	u64 RxOctetsBad;
	u64 RxUnicastFramesOK;
	u64 RxMulticastFramesOK;
	u64 RxBroadcastFramesOK;
	u64 RxPauseFrames;
	u64 RxFCSErrors;
	u64 RxAlignErrors;
	u64 RxSymbolErrors;
	u64 RxDataErrors;
	u64 RxSequenceErrors;
	u64 RxRuntErrors;
	u64 RxJabberErrors;
	u64 RxInternalMACRcvError;
	u64 RxInRangeLengthErrors;
	u64 RxOutOfRangeLengthField;
	u64 RxFrameTooLongErrors;
	u64 RxJumboFramesOK;
	u64 RxJumboOctetsOK;
पूर्ण;

काष्ठा cmac_ops अणु
	व्योम (*destroy)(काष्ठा cmac *);
	पूर्णांक (*reset)(काष्ठा cmac *);
	पूर्णांक (*पूर्णांकerrupt_enable)(काष्ठा cmac *);
	पूर्णांक (*पूर्णांकerrupt_disable)(काष्ठा cmac *);
	पूर्णांक (*पूर्णांकerrupt_clear)(काष्ठा cmac *);
	पूर्णांक (*पूर्णांकerrupt_handler)(काष्ठा cmac *);

	पूर्णांक (*enable)(काष्ठा cmac *, पूर्णांक);
	पूर्णांक (*disable)(काष्ठा cmac *, पूर्णांक);

	पूर्णांक (*loopback_enable)(काष्ठा cmac *);
	पूर्णांक (*loopback_disable)(काष्ठा cmac *);

	पूर्णांक (*set_mtu)(काष्ठा cmac *, पूर्णांक mtu);
	पूर्णांक (*set_rx_mode)(काष्ठा cmac *, काष्ठा t1_rx_mode *rm);

	पूर्णांक (*set_speed_duplex_fc)(काष्ठा cmac *, पूर्णांक speed, पूर्णांक duplex, पूर्णांक fc);
	पूर्णांक (*get_speed_duplex_fc)(काष्ठा cmac *, पूर्णांक *speed, पूर्णांक *duplex,
				   पूर्णांक *fc);

	स्थिर काष्ठा cmac_statistics *(*statistics_update)(काष्ठा cmac *, पूर्णांक);

	पूर्णांक (*macaddress_get)(काष्ठा cmac *, u8 mac_addr[6]);
	पूर्णांक (*macaddress_set)(काष्ठा cmac *, u8 mac_addr[6]);
पूर्ण;

प्रकार काष्ठा _cmac_instance cmac_instance;

काष्ठा cmac अणु
	काष्ठा cmac_statistics stats;
	adapter_t *adapter;
	स्थिर काष्ठा cmac_ops *ops;
	cmac_instance *instance;
पूर्ण;

काष्ठा gmac अणु
	अचिन्हित पूर्णांक stats_update_period;
	काष्ठा cmac *(*create)(adapter_t *adapter, पूर्णांक index);
	पूर्णांक (*reset)(adapter_t *);
पूर्ण;

बाह्य स्थिर काष्ठा gmac t1_pm3393_ops;
बाह्य स्थिर काष्ठा gmac t1_vsc7326_ops;

#पूर्ण_अगर /* _CXGB_GMAC_H_ */
