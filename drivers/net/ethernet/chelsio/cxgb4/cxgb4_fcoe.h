<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2015 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __CXGB4_FCOE_H__
#घोषणा __CXGB4_FCOE_H__

#अगर_घोषित CONFIG_CHELSIO_T4_FCOE

#घोषणा CXGB_FCOE_TXPKT_CSUM_START	28
#घोषणा CXGB_FCOE_TXPKT_CSUM_END	8

/* fcoe flags */
क्रमागत अणु
	CXGB_FCOE_ENABLED     = (1 << 0),
पूर्ण;

काष्ठा cxgb_fcoe अणु
	u8	flags;
पूर्ण;

पूर्णांक cxgb_fcoe_enable(काष्ठा net_device *);
पूर्णांक cxgb_fcoe_disable(काष्ठा net_device *);
bool cxgb_fcoe_sof_eof_supported(काष्ठा adapter *, काष्ठा sk_buff *);

#पूर्ण_अगर /* CONFIG_CHELSIO_T4_FCOE */
#पूर्ण_अगर /* __CXGB4_FCOE_H__ */
