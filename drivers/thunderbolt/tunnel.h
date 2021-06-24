<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Thunderbolt driver - Tunneling support
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2019, Intel Corporation
 */

#अगर_अघोषित TB_TUNNEL_H_
#घोषणा TB_TUNNEL_H_

#समावेश "tb.h"

क्रमागत tb_tunnel_type अणु
	TB_TUNNEL_PCI,
	TB_TUNNEL_DP,
	TB_TUNNEL_DMA,
	TB_TUNNEL_USB3,
पूर्ण;

/**
 * काष्ठा tb_tunnel - Tunnel between two ports
 * @tb: Poपूर्णांकer to the करोमुख्य
 * @src_port: Source port of the tunnel
 * @dst_port: Destination port of the tunnel. For discovered incomplete
 *	      tunnels may be %शून्य or null adapter port instead.
 * @paths: All paths required by the tunnel
 * @npaths: Number of paths in @paths
 * @init: Optional tunnel specअगरic initialization
 * @activate: Optional tunnel specअगरic activation/deactivation
 * @consumed_bandwidth: Return how much bandwidth the tunnel consumes
 * @release_unused_bandwidth: Release all unused bandwidth
 * @reclaim_available_bandwidth: Reclaim back available bandwidth
 * @list: Tunnels are linked using this field
 * @type: Type of the tunnel
 * @max_up: Maximum upstream bandwidth (Mb/s) available क्रम the tunnel.
 *	    Only set अगर the bandwidth needs to be limited.
 * @max_करोwn: Maximum करोwnstream bandwidth (Mb/s) available क्रम the tunnel.
 *	      Only set अगर the bandwidth needs to be limited.
 * @allocated_up: Allocated upstream bandwidth (only क्रम USB3)
 * @allocated_करोwn: Allocated करोwnstream bandwidth (only क्रम USB3)
 */
काष्ठा tb_tunnel अणु
	काष्ठा tb *tb;
	काष्ठा tb_port *src_port;
	काष्ठा tb_port *dst_port;
	काष्ठा tb_path **paths;
	माप_प्रकार npaths;
	पूर्णांक (*init)(काष्ठा tb_tunnel *tunnel);
	पूर्णांक (*activate)(काष्ठा tb_tunnel *tunnel, bool activate);
	पूर्णांक (*consumed_bandwidth)(काष्ठा tb_tunnel *tunnel, पूर्णांक *consumed_up,
				  पूर्णांक *consumed_करोwn);
	पूर्णांक (*release_unused_bandwidth)(काष्ठा tb_tunnel *tunnel);
	व्योम (*reclaim_available_bandwidth)(काष्ठा tb_tunnel *tunnel,
					    पूर्णांक *available_up,
					    पूर्णांक *available_करोwn);
	काष्ठा list_head list;
	क्रमागत tb_tunnel_type type;
	पूर्णांक max_up;
	पूर्णांक max_करोwn;
	पूर्णांक allocated_up;
	पूर्णांक allocated_करोwn;
पूर्ण;

काष्ठा tb_tunnel *tb_tunnel_discover_pci(काष्ठा tb *tb, काष्ठा tb_port *करोwn);
काष्ठा tb_tunnel *tb_tunnel_alloc_pci(काष्ठा tb *tb, काष्ठा tb_port *up,
				      काष्ठा tb_port *करोwn);
काष्ठा tb_tunnel *tb_tunnel_discover_dp(काष्ठा tb *tb, काष्ठा tb_port *in);
काष्ठा tb_tunnel *tb_tunnel_alloc_dp(काष्ठा tb *tb, काष्ठा tb_port *in,
				     काष्ठा tb_port *out, पूर्णांक max_up,
				     पूर्णांक max_करोwn);
काष्ठा tb_tunnel *tb_tunnel_alloc_dma(काष्ठा tb *tb, काष्ठा tb_port *nhi,
				      काष्ठा tb_port *dst, पूर्णांक transmit_path,
				      पूर्णांक transmit_ring, पूर्णांक receive_path,
				      पूर्णांक receive_ring);
bool tb_tunnel_match_dma(स्थिर काष्ठा tb_tunnel *tunnel, पूर्णांक transmit_path,
			 पूर्णांक transmit_ring, पूर्णांक receive_path, पूर्णांक receive_ring);
काष्ठा tb_tunnel *tb_tunnel_discover_usb3(काष्ठा tb *tb, काष्ठा tb_port *करोwn);
काष्ठा tb_tunnel *tb_tunnel_alloc_usb3(काष्ठा tb *tb, काष्ठा tb_port *up,
				       काष्ठा tb_port *करोwn, पूर्णांक max_up,
				       पूर्णांक max_करोwn);

व्योम tb_tunnel_मुक्त(काष्ठा tb_tunnel *tunnel);
पूर्णांक tb_tunnel_activate(काष्ठा tb_tunnel *tunnel);
पूर्णांक tb_tunnel_restart(काष्ठा tb_tunnel *tunnel);
व्योम tb_tunnel_deactivate(काष्ठा tb_tunnel *tunnel);
bool tb_tunnel_is_invalid(काष्ठा tb_tunnel *tunnel);
bool tb_tunnel_port_on_path(स्थिर काष्ठा tb_tunnel *tunnel,
			    स्थिर काष्ठा tb_port *port);
पूर्णांक tb_tunnel_consumed_bandwidth(काष्ठा tb_tunnel *tunnel, पूर्णांक *consumed_up,
				 पूर्णांक *consumed_करोwn);
पूर्णांक tb_tunnel_release_unused_bandwidth(काष्ठा tb_tunnel *tunnel);
व्योम tb_tunnel_reclaim_available_bandwidth(काष्ठा tb_tunnel *tunnel,
					   पूर्णांक *available_up,
					   पूर्णांक *available_करोwn);

अटल अंतरभूत bool tb_tunnel_is_pci(स्थिर काष्ठा tb_tunnel *tunnel)
अणु
	वापस tunnel->type == TB_TUNNEL_PCI;
पूर्ण

अटल अंतरभूत bool tb_tunnel_is_dp(स्थिर काष्ठा tb_tunnel *tunnel)
अणु
	वापस tunnel->type == TB_TUNNEL_DP;
पूर्ण

अटल अंतरभूत bool tb_tunnel_is_dma(स्थिर काष्ठा tb_tunnel *tunnel)
अणु
	वापस tunnel->type == TB_TUNNEL_DMA;
पूर्ण

अटल अंतरभूत bool tb_tunnel_is_usb3(स्थिर काष्ठा tb_tunnel *tunnel)
अणु
	वापस tunnel->type == TB_TUNNEL_USB3;
पूर्ण

#पूर्ण_अगर

