<शैली गुरु>
/*
 * Copyright (c) 2006 Cisco Systems, Inc.  All rights reserved.
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

#अगर_अघोषित MLX4_DRIVER_H
#घोषणा MLX4_DRIVER_H

#समावेश <net/devlink.h>
#समावेश <linux/mlx4/device.h>

काष्ठा mlx4_dev;

#घोषणा MLX4_MAC_MASK	   0xffffffffffffULL

क्रमागत mlx4_dev_event अणु
	MLX4_DEV_EVENT_CATASTROPHIC_ERROR,
	MLX4_DEV_EVENT_PORT_UP,
	MLX4_DEV_EVENT_PORT_DOWN,
	MLX4_DEV_EVENT_PORT_REINIT,
	MLX4_DEV_EVENT_PORT_MGMT_CHANGE,
	MLX4_DEV_EVENT_SLAVE_INIT,
	MLX4_DEV_EVENT_SLAVE_SHUTDOWN,
पूर्ण;

क्रमागत अणु
	MLX4_INTFF_BONDING	= 1 << 0
पूर्ण;

काष्ठा mlx4_पूर्णांकerface अणु
	व्योम *			(*add)	 (काष्ठा mlx4_dev *dev);
	व्योम			(*हटाओ)(काष्ठा mlx4_dev *dev, व्योम *context);
	व्योम			(*event) (काष्ठा mlx4_dev *dev, व्योम *context,
					  क्रमागत mlx4_dev_event event, अचिन्हित दीर्घ param);
	व्योम *			(*get_dev)(काष्ठा mlx4_dev *dev, व्योम *context, u8 port);
	व्योम			(*activate)(काष्ठा mlx4_dev *dev, व्योम *context);
	काष्ठा list_head	list;
	क्रमागत mlx4_protocol	protocol;
	पूर्णांक			flags;
पूर्ण;

पूर्णांक mlx4_रेजिस्टर_पूर्णांकerface(काष्ठा mlx4_पूर्णांकerface *पूर्णांकf);
व्योम mlx4_unरेजिस्टर_पूर्णांकerface(काष्ठा mlx4_पूर्णांकerface *पूर्णांकf);

पूर्णांक mlx4_bond(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_unbond(काष्ठा mlx4_dev *dev);
अटल अंतरभूत पूर्णांक mlx4_is_bonded(काष्ठा mlx4_dev *dev)
अणु
	वापस !!(dev->flags & MLX4_FLAG_BONDED);
पूर्ण

अटल अंतरभूत पूर्णांक mlx4_is_mf_bonded(काष्ठा mlx4_dev *dev)
अणु
	वापस (mlx4_is_bonded(dev) && mlx4_is_mfunc(dev));
पूर्ण

काष्ठा mlx4_port_map अणु
	u8	port1;
	u8	port2;
पूर्ण;

पूर्णांक mlx4_port_map_set(काष्ठा mlx4_dev *dev, काष्ठा mlx4_port_map *v2p);

व्योम *mlx4_get_protocol_dev(काष्ठा mlx4_dev *dev, क्रमागत mlx4_protocol proto, पूर्णांक port);

काष्ठा devlink_port *mlx4_get_devlink_port(काष्ठा mlx4_dev *dev, पूर्णांक port);

अटल अंतरभूत u64 mlx4_mac_to_u64(u8 *addr)
अणु
	u64 mac = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		mac <<= 8;
		mac |= addr[i];
	पूर्ण
	वापस mac;
पूर्ण

अटल अंतरभूत व्योम mlx4_u64_to_mac(u8 *addr, u64 mac)
अणु
	पूर्णांक i;

	क्रम (i = ETH_ALEN; i > 0; i--) अणु
		addr[i - 1] = mac & 0xFF;
		mac >>= 8;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* MLX4_DRIVER_H */
