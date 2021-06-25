<शैली गुरु>
/*
 * Copyright (c) 2018, Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित _MLX5_FS_HELPERS_
#घोषणा _MLX5_FS_HELPERS_

#समावेश <linux/mlx5/mlx5_अगरc.h>

#घोषणा MLX5_FS_IPV4_VERSION 4
#घोषणा MLX5_FS_IPV6_VERSION 6

अटल अंतरभूत bool mlx5_fs_is_ipsec_flow(स्थिर u32 *match_c)
अणु
	व्योम *misc_params_c = MLX5_ADDR_OF(fte_match_param, match_c,
					   misc_parameters);

	वापस MLX5_GET(fte_match_set_misc, misc_params_c, outer_esp_spi);
पूर्ण

अटल अंतरभूत bool _mlx5_fs_is_outer_ipproto_flow(स्थिर u32 *match_c,
						  स्थिर u32 *match_v, u8 match)
अणु
	स्थिर व्योम *headers_c = MLX5_ADDR_OF(fte_match_param, match_c,
					     outer_headers);
	स्थिर व्योम *headers_v = MLX5_ADDR_OF(fte_match_param, match_v,
					     outer_headers);

	वापस MLX5_GET(fte_match_set_lyr_2_4, headers_c, ip_protocol) == 0xff &&
		MLX5_GET(fte_match_set_lyr_2_4, headers_v, ip_protocol) == match;
पूर्ण

अटल अंतरभूत bool mlx5_fs_is_outer_tcp_flow(स्थिर u32 *match_c,
					     स्थिर u32 *match_v)
अणु
	वापस _mlx5_fs_is_outer_ipproto_flow(match_c, match_v, IPPROTO_TCP);
पूर्ण

अटल अंतरभूत bool mlx5_fs_is_outer_udp_flow(स्थिर u32 *match_c,
					     स्थिर u32 *match_v)
अणु
	वापस _mlx5_fs_is_outer_ipproto_flow(match_c, match_v, IPPROTO_UDP);
पूर्ण

अटल अंतरभूत bool mlx5_fs_is_vxlan_flow(स्थिर u32 *match_c)
अणु
	व्योम *misc_params_c = MLX5_ADDR_OF(fte_match_param, match_c,
					   misc_parameters);

	वापस MLX5_GET(fte_match_set_misc, misc_params_c, vxlan_vni);
पूर्ण

अटल अंतरभूत bool _mlx5_fs_is_outer_ipv_flow(काष्ठा mlx5_core_dev *mdev,
					      स्थिर u32 *match_c,
					      स्थिर u32 *match_v, पूर्णांक version)
अणु
	पूर्णांक match_ipv = MLX5_CAP_FLOWTABLE_NIC_RX(mdev,
						  ft_field_support.outer_ip_version);
	स्थिर व्योम *headers_c = MLX5_ADDR_OF(fte_match_param, match_c,
					     outer_headers);
	स्थिर व्योम *headers_v = MLX5_ADDR_OF(fte_match_param, match_v,
					     outer_headers);

	अगर (!match_ipv) अणु
		u16 ethertype;

		चयन (version) अणु
		हाल MLX5_FS_IPV4_VERSION:
			ethertype = ETH_P_IP;
			अवरोध;
		हाल MLX5_FS_IPV6_VERSION:
			ethertype = ETH_P_IPV6;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण

		वापस MLX5_GET(fte_match_set_lyr_2_4, headers_c,
				ethertype) == 0xffff &&
			MLX5_GET(fte_match_set_lyr_2_4, headers_v,
				 ethertype) == ethertype;
	पूर्ण

	वापस MLX5_GET(fte_match_set_lyr_2_4, headers_c,
			ip_version) == 0xf &&
		MLX5_GET(fte_match_set_lyr_2_4, headers_v,
			 ip_version) == version;
पूर्ण

अटल अंतरभूत bool
mlx5_fs_is_outer_ipv4_flow(काष्ठा mlx5_core_dev *mdev, स्थिर u32 *match_c,
			   स्थिर u32 *match_v)
अणु
	वापस _mlx5_fs_is_outer_ipv_flow(mdev, match_c, match_v,
					  MLX5_FS_IPV4_VERSION);
पूर्ण

अटल अंतरभूत bool
mlx5_fs_is_outer_ipv6_flow(काष्ठा mlx5_core_dev *mdev, स्थिर u32 *match_c,
			   स्थिर u32 *match_v)
अणु
	वापस _mlx5_fs_is_outer_ipv_flow(mdev, match_c, match_v,
					  MLX5_FS_IPV6_VERSION);
पूर्ण

अटल अंतरभूत bool mlx5_fs_is_outer_ipsec_flow(स्थिर u32 *match_c)
अणु
	व्योम *misc_params_c =
			MLX5_ADDR_OF(fte_match_param, match_c, misc_parameters);

	वापस MLX5_GET(fte_match_set_misc, misc_params_c, outer_esp_spi);
पूर्ण

#पूर्ण_अगर
