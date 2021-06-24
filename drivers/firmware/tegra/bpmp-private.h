<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018, NVIDIA CORPORATION.
 */

#अगर_अघोषित __FIRMWARE_TEGRA_BPMP_PRIVATE_H
#घोषणा __FIRMWARE_TEGRA_BPMP_PRIVATE_H

#समावेश <soc/tegra/bpmp.h>

काष्ठा tegra_bpmp_ops अणु
	पूर्णांक (*init)(काष्ठा tegra_bpmp *bpmp);
	व्योम (*deinit)(काष्ठा tegra_bpmp *bpmp);
	bool (*is_response_पढ़ोy)(काष्ठा tegra_bpmp_channel *channel);
	bool (*is_request_पढ़ोy)(काष्ठा tegra_bpmp_channel *channel);
	पूर्णांक (*ack_response)(काष्ठा tegra_bpmp_channel *channel);
	पूर्णांक (*ack_request)(काष्ठा tegra_bpmp_channel *channel);
	bool (*is_response_channel_मुक्त)(काष्ठा tegra_bpmp_channel *channel);
	bool (*is_request_channel_मुक्त)(काष्ठा tegra_bpmp_channel *channel);
	पूर्णांक (*post_response)(काष्ठा tegra_bpmp_channel *channel);
	पूर्णांक (*post_request)(काष्ठा tegra_bpmp_channel *channel);
	पूर्णांक (*ring_करोorbell)(काष्ठा tegra_bpmp *bpmp);
	पूर्णांक (*resume)(काष्ठा tegra_bpmp *bpmp);
पूर्ण;

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_186_SOC) || \
    IS_ENABLED(CONFIG_ARCH_TEGRA_194_SOC)
बाह्य स्थिर काष्ठा tegra_bpmp_ops tegra186_bpmp_ops;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_210_SOC)
बाह्य स्थिर काष्ठा tegra_bpmp_ops tegra210_bpmp_ops;
#पूर्ण_अगर

#पूर्ण_अगर
