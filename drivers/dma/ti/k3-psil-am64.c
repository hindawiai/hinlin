<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2020 Texas Instruments Incorporated - https://www.ti.com
 *  Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/kernel.h>

#समावेश "k3-psil-priv.h"

#घोषणा PSIL_PDMA_XY_TR(x)					\
	अणु							\
		.thपढ़ो_id = x,					\
		.ep_config = अणु					\
			.ep_type = PSIL_EP_PDMA_XY,		\
			.mapped_channel_id = -1,		\
			.शेष_flow_id = -1,			\
		पूर्ण,						\
	पूर्ण

#घोषणा PSIL_PDMA_XY_PKT(x)					\
	अणु							\
		.thपढ़ो_id = x,					\
		.ep_config = अणु					\
			.ep_type = PSIL_EP_PDMA_XY,		\
			.mapped_channel_id = -1,		\
			.शेष_flow_id = -1,			\
			.pkt_mode = 1,				\
		पूर्ण,						\
	पूर्ण

#घोषणा PSIL_ETHERNET(x, ch, flow_base, flow_cnt)		\
	अणु							\
		.thपढ़ो_id = x,					\
		.ep_config = अणु					\
			.ep_type = PSIL_EP_NATIVE,		\
			.pkt_mode = 1,				\
			.needs_epib = 1,			\
			.psd_size = 16,				\
			.mapped_channel_id = ch,		\
			.flow_start = flow_base,		\
			.flow_num = flow_cnt,			\
			.शेष_flow_id = flow_base,		\
		पूर्ण,						\
	पूर्ण

#घोषणा PSIL_SAUL(x, ch, flow_base, flow_cnt, शेष_flow, tx)	\
	अणु							\
		.thपढ़ो_id = x,					\
		.ep_config = अणु					\
			.ep_type = PSIL_EP_NATIVE,		\
			.pkt_mode = 1,				\
			.needs_epib = 1,			\
			.psd_size = 64,				\
			.mapped_channel_id = ch,		\
			.flow_start = flow_base,		\
			.flow_num = flow_cnt,			\
			.शेष_flow_id = शेष_flow,	\
			.notdpkt = tx,				\
		पूर्ण,						\
	पूर्ण

/* PSI-L source thपढ़ो IDs, used क्रम RX (DMA_DEV_TO_MEM) */
अटल काष्ठा psil_ep am64_src_ep_map[] = अणु
	/* SAUL */
	PSIL_SAUL(0x4000, 17, 32, 8, 32, 0),
	PSIL_SAUL(0x4001, 18, 32, 8, 33, 0),
	PSIL_SAUL(0x4002, 19, 40, 8, 40, 0),
	PSIL_SAUL(0x4003, 20, 40, 8, 41, 0),
	/* ICSS_G0 */
	PSIL_ETHERNET(0x4100, 21, 48, 16),
	PSIL_ETHERNET(0x4101, 22, 64, 16),
	PSIL_ETHERNET(0x4102, 23, 80, 16),
	PSIL_ETHERNET(0x4103, 24, 96, 16),
	/* ICSS_G1 */
	PSIL_ETHERNET(0x4200, 25, 112, 16),
	PSIL_ETHERNET(0x4201, 26, 128, 16),
	PSIL_ETHERNET(0x4202, 27, 144, 16),
	PSIL_ETHERNET(0x4203, 28, 160, 16),
	/* PDMA_MAIN0 - SPI0-3 */
	PSIL_PDMA_XY_PKT(0x4300),
	PSIL_PDMA_XY_PKT(0x4301),
	PSIL_PDMA_XY_PKT(0x4302),
	PSIL_PDMA_XY_PKT(0x4303),
	PSIL_PDMA_XY_PKT(0x4304),
	PSIL_PDMA_XY_PKT(0x4305),
	PSIL_PDMA_XY_PKT(0x4306),
	PSIL_PDMA_XY_PKT(0x4307),
	PSIL_PDMA_XY_PKT(0x4308),
	PSIL_PDMA_XY_PKT(0x4309),
	PSIL_PDMA_XY_PKT(0x430a),
	PSIL_PDMA_XY_PKT(0x430b),
	PSIL_PDMA_XY_PKT(0x430c),
	PSIL_PDMA_XY_PKT(0x430d),
	PSIL_PDMA_XY_PKT(0x430e),
	PSIL_PDMA_XY_PKT(0x430f),
	/* PDMA_MAIN0 - USART0-1 */
	PSIL_PDMA_XY_PKT(0x4310),
	PSIL_PDMA_XY_PKT(0x4311),
	/* PDMA_MAIN1 - SPI4 */
	PSIL_PDMA_XY_PKT(0x4400),
	PSIL_PDMA_XY_PKT(0x4401),
	PSIL_PDMA_XY_PKT(0x4402),
	PSIL_PDMA_XY_PKT(0x4403),
	/* PDMA_MAIN1 - USART2-6 */
	PSIL_PDMA_XY_PKT(0x4404),
	PSIL_PDMA_XY_PKT(0x4405),
	PSIL_PDMA_XY_PKT(0x4406),
	PSIL_PDMA_XY_PKT(0x4407),
	PSIL_PDMA_XY_PKT(0x4408),
	/* PDMA_MAIN1 - ADCs */
	PSIL_PDMA_XY_TR(0x440f),
	PSIL_PDMA_XY_TR(0x4410),
	/* CPSW2 */
	PSIL_ETHERNET(0x4500, 16, 16, 16),
पूर्ण;

/* PSI-L destination thपढ़ो IDs, used क्रम TX (DMA_MEM_TO_DEV) */
अटल काष्ठा psil_ep am64_dst_ep_map[] = अणु
	/* SAUL */
	PSIL_SAUL(0xc000, 24, 80, 8, 80, 1),
	PSIL_SAUL(0xc001, 25, 88, 8, 88, 1),
	/* ICSS_G0 */
	PSIL_ETHERNET(0xc100, 26, 96, 1),
	PSIL_ETHERNET(0xc101, 27, 97, 1),
	PSIL_ETHERNET(0xc102, 28, 98, 1),
	PSIL_ETHERNET(0xc103, 29, 99, 1),
	PSIL_ETHERNET(0xc104, 30, 100, 1),
	PSIL_ETHERNET(0xc105, 31, 101, 1),
	PSIL_ETHERNET(0xc106, 32, 102, 1),
	PSIL_ETHERNET(0xc107, 33, 103, 1),
	/* ICSS_G1 */
	PSIL_ETHERNET(0xc200, 34, 104, 1),
	PSIL_ETHERNET(0xc201, 35, 105, 1),
	PSIL_ETHERNET(0xc202, 36, 106, 1),
	PSIL_ETHERNET(0xc203, 37, 107, 1),
	PSIL_ETHERNET(0xc204, 38, 108, 1),
	PSIL_ETHERNET(0xc205, 39, 109, 1),
	PSIL_ETHERNET(0xc206, 40, 110, 1),
	PSIL_ETHERNET(0xc207, 41, 111, 1),
	/* CPSW2 */
	PSIL_ETHERNET(0xc500, 16, 16, 8),
	PSIL_ETHERNET(0xc501, 17, 24, 8),
	PSIL_ETHERNET(0xc502, 18, 32, 8),
	PSIL_ETHERNET(0xc503, 19, 40, 8),
	PSIL_ETHERNET(0xc504, 20, 48, 8),
	PSIL_ETHERNET(0xc505, 21, 56, 8),
	PSIL_ETHERNET(0xc506, 22, 64, 8),
	PSIL_ETHERNET(0xc507, 23, 72, 8),
पूर्ण;

काष्ठा psil_ep_map am64_ep_map = अणु
	.name = "am64",
	.src = am64_src_ep_map,
	.src_count = ARRAY_SIZE(am64_src_ep_map),
	.dst = am64_dst_ep_map,
	.dst_count = ARRAY_SIZE(am64_dst_ep_map),
पूर्ण;
