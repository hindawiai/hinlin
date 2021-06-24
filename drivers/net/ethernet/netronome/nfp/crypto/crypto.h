<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2019 Netronome Systems, Inc. */

#अगर_अघोषित NFP_CRYPTO_H
#घोषणा NFP_CRYPTO_H 1

काष्ठा net_device;
काष्ठा nfp_net;
काष्ठा nfp_net_tls_resync_req;

काष्ठा nfp_net_tls_offload_ctx अणु
	__be32 fw_handle[2];

	u8 rx_end[0];
	/* Tx only fields follow - Rx side करोes not have enough driver state
	 * to fit these
	 */

	u32 next_seq;
पूर्ण;

#अगर_घोषित CONFIG_TLS_DEVICE
पूर्णांक nfp_net_tls_init(काष्ठा nfp_net *nn);
पूर्णांक nfp_net_tls_rx_resync_req(काष्ठा net_device *netdev,
			      काष्ठा nfp_net_tls_resync_req *req,
			      व्योम *pkt, अचिन्हित पूर्णांक pkt_len);
#अन्यथा
अटल अंतरभूत पूर्णांक nfp_net_tls_init(काष्ठा nfp_net *nn)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
nfp_net_tls_rx_resync_req(काष्ठा net_device *netdev,
			  काष्ठा nfp_net_tls_resync_req *req,
			  व्योम *pkt, अचिन्हित पूर्णांक pkt_len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
