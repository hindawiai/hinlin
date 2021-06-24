<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies, Ltd.  All rights reserved.
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
#अगर_अघोषित __MLX5_VXLAN_H__
#घोषणा __MLX5_VXLAN_H__

#समावेश <linux/mlx5/driver.h>

काष्ठा mlx5_vxlan;
काष्ठा mlx5_vxlan_port;

अटल अंतरभूत u8 mlx5_vxlan_max_udp_ports(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस MLX5_CAP_ETH(mdev, max_vxlan_udp_ports) ?: 4;
पूर्ण

अटल अंतरभूत bool mlx5_vxlan_allowed(काष्ठा mlx5_vxlan *vxlan)
अणु
	/* not allowed reason is encoded in vxlan poपूर्णांकer as error,
	 * on mlx5_vxlan_create
	 */
	वापस !IS_ERR_OR_शून्य(vxlan);
पूर्ण

#अगर IS_ENABLED(CONFIG_VXLAN)
काष्ठा mlx5_vxlan *mlx5_vxlan_create(काष्ठा mlx5_core_dev *mdev);
व्योम mlx5_vxlan_destroy(काष्ठा mlx5_vxlan *vxlan);
पूर्णांक mlx5_vxlan_add_port(काष्ठा mlx5_vxlan *vxlan, u16 port);
पूर्णांक mlx5_vxlan_del_port(काष्ठा mlx5_vxlan *vxlan, u16 port);
bool mlx5_vxlan_lookup_port(काष्ठा mlx5_vxlan *vxlan, u16 port);
व्योम mlx5_vxlan_reset_to_शेष(काष्ठा mlx5_vxlan *vxlan);
#अन्यथा
अटल अंतरभूत काष्ठा mlx5_vxlan*
mlx5_vxlan_create(काष्ठा mlx5_core_dev *mdev) अणु वापस ERR_PTR(-EOPNOTSUPP); पूर्ण
अटल अंतरभूत व्योम mlx5_vxlan_destroy(काष्ठा mlx5_vxlan *vxlan) अणु वापस; पूर्ण
अटल अंतरभूत पूर्णांक mlx5_vxlan_add_port(काष्ठा mlx5_vxlan *vxlan, u16 port) अणु वापस -EOPNOTSUPP; पूर्ण
अटल अंतरभूत पूर्णांक mlx5_vxlan_del_port(काष्ठा mlx5_vxlan *vxlan, u16 port) अणु वापस -EOPNOTSUPP; पूर्ण
अटल अंतरभूत bool mlx5_vxlan_lookup_port(काष्ठा mlx5_vxlan *vxlan, u16 port) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम mlx5_vxlan_reset_to_शेष(काष्ठा mlx5_vxlan *vxlan) अणु वापस; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MLX5_VXLAN_H__ */
