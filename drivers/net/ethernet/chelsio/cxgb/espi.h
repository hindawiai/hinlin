<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: espi.h                                                              *
 * $Revision: 1.7 $                                                          *
 * $Date: 2005/06/21 18:29:47 $                                              *
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

#अगर_अघोषित _CXGB_ESPI_H_
#घोषणा _CXGB_ESPI_H_

#समावेश "common.h"

काष्ठा espi_पूर्णांकr_counts अणु
	अचिन्हित पूर्णांक DIP4_err;
	अचिन्हित पूर्णांक rx_drops;
	अचिन्हित पूर्णांक tx_drops;
	अचिन्हित पूर्णांक rx_ovflw;
	अचिन्हित पूर्णांक parity_err;
	अचिन्हित पूर्णांक DIP2_parity_err;
पूर्ण;

काष्ठा peespi;

काष्ठा peespi *t1_espi_create(adapter_t *adapter);
व्योम t1_espi_destroy(काष्ठा peespi *espi);
पूर्णांक t1_espi_init(काष्ठा peespi *espi, पूर्णांक mac_type, पूर्णांक nports);

व्योम t1_espi_पूर्णांकr_enable(काष्ठा peespi *);
व्योम t1_espi_पूर्णांकr_clear(काष्ठा peespi *);
व्योम t1_espi_पूर्णांकr_disable(काष्ठा peespi *);
पूर्णांक t1_espi_पूर्णांकr_handler(काष्ठा peespi *);
स्थिर काष्ठा espi_पूर्णांकr_counts *t1_espi_get_पूर्णांकr_counts(काष्ठा peespi *espi);

u32 t1_espi_get_mon(adapter_t *adapter, u32 addr, u8 रुको);
पूर्णांक t1_espi_get_mon_t204(adapter_t *, u32 *, u8);

#पूर्ण_अगर /* _CXGB_ESPI_H_ */
