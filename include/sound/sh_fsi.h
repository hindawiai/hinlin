<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Fअगरo-attached Serial Interface (FSI) support क्रम SH7724
 *
 * Copyright (C) 2009 Renesas Solutions Corp.
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 */
#अगर_अघोषित __SOUND_FSI_H
#घोषणा __SOUND_FSI_H

#समावेश <linux/clk.h>
#समावेश <sound/soc.h>

/*
 * flags
 */
#घोषणा SH_FSI_FMT_SPDIF		(1 << 0) /* spdअगर क्रम HDMI */
#घोषणा SH_FSI_ENABLE_STREAM_MODE	(1 << 1) /* क्रम 16bit data */
#घोषणा SH_FSI_CLK_CPG			(1 << 2) /* FSIxCK + FSI-DIV */

काष्ठा sh_fsi_port_info अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक tx_id;
	पूर्णांक rx_id;
पूर्ण;

काष्ठा sh_fsi_platक्रमm_info अणु
	काष्ठा sh_fsi_port_info port_a;
	काष्ठा sh_fsi_port_info port_b;
पूर्ण;

#पूर्ण_अगर /* __SOUND_FSI_H */
