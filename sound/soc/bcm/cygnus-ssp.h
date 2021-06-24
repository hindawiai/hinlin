<शैली गुरु>
/*
 * Copyright (C) 2014-2015 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#अगर_अघोषित __CYGNUS_SSP_H__
#घोषणा __CYGNUS_SSP_H__

#घोषणा CYGNUS_TDM_DAI_MAX_SLOTS 16

#घोषणा CYGNUS_MAX_PLAYBACK_PORTS 4
#घोषणा CYGNUS_MAX_CAPTURE_PORTS 3
#घोषणा CYGNUS_MAX_I2S_PORTS 3
#घोषणा CYGNUS_MAX_PORTS  CYGNUS_MAX_PLAYBACK_PORTS
#घोषणा CYGNUS_AUIDO_MAX_NUM_CLKS 3

#घोषणा CYGNUS_SSP_FRAMEBITS_DIV 1

#घोषणा CYGNUS_SSPMODE_I2S 0
#घोषणा CYGNUS_SSPMODE_TDM 1
#घोषणा CYGNUS_SSPMODE_UNKNOWN -1

#घोषणा CYGNUS_SSP_CLKSRC_PLL      0

/* Max string length of our dt property names */
#घोषणा PROP_LEN_MAX 40

काष्ठा ringbuf_regs अणु
	अचिन्हित rdaddr;
	अचिन्हित wraddr;
	अचिन्हित baseaddr;
	अचिन्हित endaddr;
	अचिन्हित fmark;   /* मुक्तmark क्रम play, fullmark क्रम caputure */
	अचिन्हित period_bytes;
	अचिन्हित buf_size;
पूर्ण;

#घोषणा RINGBUF_REG_PLAYBACK(num) ((काष्ठा ringbuf_regs) अणु \
	.rdaddr = SRC_RBUF_ ##num## _RDADDR_OFFSET, \
	.wraddr = SRC_RBUF_ ##num## _WRADDR_OFFSET, \
	.baseaddr = SRC_RBUF_ ##num## _BASEADDR_OFFSET, \
	.endaddr = SRC_RBUF_ ##num## _ENDADDR_OFFSET, \
	.fmark = SRC_RBUF_ ##num## _FREE_MARK_OFFSET, \
	.period_bytes = 0, \
	.buf_size = 0, \
पूर्ण)

#घोषणा RINGBUF_REG_CAPTURE(num) ((काष्ठा ringbuf_regs)  अणु \
	.rdaddr = DST_RBUF_ ##num## _RDADDR_OFFSET, \
	.wraddr = DST_RBUF_ ##num## _WRADDR_OFFSET, \
	.baseaddr = DST_RBUF_ ##num## _BASEADDR_OFFSET, \
	.endaddr = DST_RBUF_ ##num## _ENDADDR_OFFSET, \
	.fmark = DST_RBUF_ ##num## _FULL_MARK_OFFSET, \
	.period_bytes = 0, \
	.buf_size = 0, \
पूर्ण)

क्रमागत cygnus_audio_port_type अणु
	PORT_TDM,
	PORT_SPDIF,
पूर्ण;

काष्ठा cygnus_ssp_regs अणु
	u32 i2s_stream_cfg;
	u32 i2s_cfg;
	u32 i2s_cap_stream_cfg;
	u32 i2s_cap_cfg;
	u32 i2s_mclk_cfg;

	u32 bf_destch_ctrl;
	u32 bf_destch_cfg;
	u32 bf_sourcech_ctrl;
	u32 bf_sourcech_cfg;
	u32 bf_sourcech_grp;
पूर्ण;

काष्ठा cygnus_track_clk अणु
	bool cap_en;
	bool play_en;
	bool cap_clk_en;
	bool play_clk_en;
पूर्ण;

काष्ठा cygnus_aio_port अणु
	पूर्णांक portnum;
	पूर्णांक mode;
	bool is_slave;
	पूर्णांक streams_on;   /* will be 0 अगर both capture and play are off */
	पूर्णांक fsync_width;
	पूर्णांक port_type;

	u32 mclk;
	u32 lrclk;
	u32 bit_per_frame;
	u32 pll_clk_num;

	काष्ठा cygnus_audio *cygaud;
	काष्ठा cygnus_ssp_regs regs;

	काष्ठा ringbuf_regs play_rb_regs;
	काष्ठा ringbuf_regs capture_rb_regs;

	काष्ठा snd_pcm_substream *play_stream;
	काष्ठा snd_pcm_substream *capture_stream;

	काष्ठा cygnus_track_clk clk_trace;
पूर्ण;


काष्ठा cygnus_audio अणु
	काष्ठा cygnus_aio_port  portinfo[CYGNUS_MAX_PORTS];

	पूर्णांक irq_num;
	व्योम __iomem *audio;
	काष्ठा device *dev;
	व्योम __iomem *i2s_in;

	काष्ठा clk *audio_clk[CYGNUS_AUIDO_MAX_NUM_CLKS];
	पूर्णांक active_ports;
	अचिन्हित दीर्घ vco_rate;
पूर्ण;

बाह्य पूर्णांक cygnus_ssp_get_mode(काष्ठा snd_soc_dai *cpu_dai);
बाह्य पूर्णांक cygnus_ssp_add_pll_tweak_controls(काष्ठा snd_soc_pcm_runसमय *rtd);
बाह्य पूर्णांक cygnus_ssp_set_custom_fsync_width(काष्ठा snd_soc_dai *cpu_dai,
						पूर्णांक len);
बाह्य पूर्णांक cygnus_soc_platक्रमm_रेजिस्टर(काष्ठा device *dev,
					काष्ठा cygnus_audio *cygaud);
बाह्य पूर्णांक cygnus_soc_platक्रमm_unरेजिस्टर(काष्ठा device *dev);
बाह्य पूर्णांक cygnus_ssp_set_custom_fsync_width(काष्ठा snd_soc_dai *cpu_dai,
	पूर्णांक len);
#पूर्ण_अगर
