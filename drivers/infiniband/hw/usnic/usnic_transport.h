<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
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
 *
 */

#अगर_अघोषित USNIC_TRANSPORT_H_
#घोषणा USNIC_TRANSPORT_H_

#समावेश "usnic_abi.h"

स्थिर अक्षर *usnic_transport_to_str(क्रमागत usnic_transport_type trans_type);
/*
 * Returns number of bytes written, excluding null terminator. If
 * nothing was written, the function वापसs 0.
 */
पूर्णांक usnic_transport_sock_to_str(अक्षर *buf, पूर्णांक buf_sz,
					काष्ठा socket *sock);
/*
 * Reserve a port. If "port_num" is set, then the function will try
 * to reserve that particular port.
 */
u16 usnic_transport_rsrv_port(क्रमागत usnic_transport_type type, u16 port_num);
व्योम usnic_transport_unrsrv_port(क्रमागत usnic_transport_type type, u16 port_num);
/*
 * Do a fget on the socket refered to by sock_fd and वापसs the socket.
 * Socket will not be destroyed beक्रमe usnic_transport_put_socket has
 * been called.
 */
काष्ठा socket *usnic_transport_get_socket(पूर्णांक sock_fd);
व्योम usnic_transport_put_socket(काष्ठा socket *sock);
/*
 * Call usnic_transport_get_socket beक्रमe calling *_sock_get_addr
 */
पूर्णांक usnic_transport_sock_get_addr(काष्ठा socket *sock, पूर्णांक *proto,
					uपूर्णांक32_t *addr, uपूर्णांक16_t *port);
पूर्णांक usnic_transport_init(व्योम);
व्योम usnic_transport_fini(व्योम);
#पूर्ण_अगर /* !USNIC_TRANSPORT_H */
