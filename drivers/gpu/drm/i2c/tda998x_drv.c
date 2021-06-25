<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Texas Instruments
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/tda9950.h>
#समावेश <linux/irq.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/hdmi-codec.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <drm/i2c/tda998x.h>

#समावेश <media/cec-notअगरier.h>

#घोषणा DBG(fmt, ...) DRM_DEBUG(fmt"\n", ##__VA_ARGS__)

क्रमागत अणु
	AUDIO_ROUTE_I2S,
	AUDIO_ROUTE_SPDIF,
	AUDIO_ROUTE_NUM
पूर्ण;

काष्ठा tda998x_audio_route अणु
	u8 ena_aclk;
	u8 mux_ap;
	u8 aip_clksel;
पूर्ण;

काष्ठा tda998x_audio_settings अणु
	स्थिर काष्ठा tda998x_audio_route *route;
	काष्ठा hdmi_audio_infoframe cea;
	अचिन्हित पूर्णांक sample_rate;
	u8 status[5];
	u8 ena_ap;
	u8 i2s_क्रमmat;
	u8 cts_n;
पूर्ण;

काष्ठा tda998x_priv अणु
	काष्ठा i2c_client *cec;
	काष्ठा i2c_client *hdmi;
	काष्ठा mutex mutex;
	u16 rev;
	u8 cec_addr;
	u8 current_page;
	bool is_on;
	bool supports_infoframes;
	bool sink_has_audio;
	क्रमागत hdmi_quantization_range rgb_quant_range;
	u8 vip_cntrl_0;
	u8 vip_cntrl_1;
	u8 vip_cntrl_2;
	अचिन्हित दीर्घ पंचांगds_घड़ी;
	काष्ठा tda998x_audio_settings audio;

	काष्ठा platक्रमm_device *audio_pdev;
	काष्ठा mutex audio_mutex;

	काष्ठा mutex edid_mutex;
	रुको_queue_head_t wq_edid;
	अस्थिर पूर्णांक wq_edid_रुको;

	काष्ठा work_काष्ठा detect_work;
	काष्ठा समयr_list edid_delay_समयr;
	रुको_queue_head_t edid_delay_रुकोq;
	bool edid_delay_active;

	काष्ठा drm_encoder encoder;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_connector connector;

	u8 audio_port_enable[AUDIO_ROUTE_NUM];
	काष्ठा tda9950_glue cec_glue;
	काष्ठा gpio_desc *calib;
	काष्ठा cec_notअगरier *cec_notअगरy;
पूर्ण;

#घोषणा conn_to_tda998x_priv(x) \
	container_of(x, काष्ठा tda998x_priv, connector)
#घोषणा enc_to_tda998x_priv(x) \
	container_of(x, काष्ठा tda998x_priv, encoder)
#घोषणा bridge_to_tda998x_priv(x) \
	container_of(x, काष्ठा tda998x_priv, bridge)

/* The TDA9988 series of devices use a paged रेजिस्टर scheme.. to simplअगरy
 * things we encode the page # in upper bits of the रेजिस्टर #.  To पढ़ो/
 * ग_लिखो a given रेजिस्टर, we need to make sure CURPAGE रेजिस्टर is set
 * appropriately.  Which implies पढ़ोs/ग_लिखोs are not atomic.  Fun!
 */

#घोषणा REG(page, addr) (((page) << 8) | (addr))
#घोषणा REG2ADDR(reg)   ((reg) & 0xff)
#घोषणा REG2PAGE(reg)   (((reg) >> 8) & 0xff)

#घोषणा REG_CURPAGE               0xff                /* ग_लिखो */


/* Page 00h: General Control */
#घोषणा REG_VERSION_LSB           REG(0x00, 0x00)     /* पढ़ो */
#घोषणा REG_MAIN_CNTRL0           REG(0x00, 0x01)     /* पढ़ो/ग_लिखो */
# define MAIN_CNTRL0_SR           (1 << 0)
# define MAIN_CNTRL0_DECS         (1 << 1)
# define MAIN_CNTRL0_DEHS         (1 << 2)
# define MAIN_CNTRL0_CECS         (1 << 3)
# define MAIN_CNTRL0_CEHS         (1 << 4)
# define MAIN_CNTRL0_SCALER       (1 << 7)
#घोषणा REG_VERSION_MSB           REG(0x00, 0x02)     /* पढ़ो */
#घोषणा REG_SOFTRESET             REG(0x00, 0x0a)     /* ग_लिखो */
# define SOFTRESET_AUDIO          (1 << 0)
# define SOFTRESET_I2C_MASTER     (1 << 1)
#घोषणा REG_DDC_DISABLE           REG(0x00, 0x0b)     /* पढ़ो/ग_लिखो */
#घोषणा REG_CCLK_ON               REG(0x00, 0x0c)     /* पढ़ो/ग_लिखो */
#घोषणा REG_I2C_MASTER            REG(0x00, 0x0d)     /* पढ़ो/ग_लिखो */
# define I2C_MASTER_DIS_MM        (1 << 0)
# define I2C_MASTER_DIS_FILT      (1 << 1)
# define I2C_MASTER_APP_STRT_LAT  (1 << 2)
#घोषणा REG_FEAT_POWERDOWN        REG(0x00, 0x0e)     /* पढ़ो/ग_लिखो */
# define FEAT_POWERDOWN_PREFILT   BIT(0)
# define FEAT_POWERDOWN_CSC       BIT(1)
# define FEAT_POWERDOWN_SPDIF     (1 << 3)
#घोषणा REG_INT_FLAGS_0           REG(0x00, 0x0f)     /* पढ़ो/ग_लिखो */
#घोषणा REG_INT_FLAGS_1           REG(0x00, 0x10)     /* पढ़ो/ग_लिखो */
#घोषणा REG_INT_FLAGS_2           REG(0x00, 0x11)     /* पढ़ो/ग_लिखो */
# define INT_FLAGS_2_EDID_BLK_RD  (1 << 1)
#घोषणा REG_ENA_ACLK              REG(0x00, 0x16)     /* पढ़ो/ग_लिखो */
#घोषणा REG_ENA_VP_0              REG(0x00, 0x18)     /* पढ़ो/ग_लिखो */
#घोषणा REG_ENA_VP_1              REG(0x00, 0x19)     /* पढ़ो/ग_लिखो */
#घोषणा REG_ENA_VP_2              REG(0x00, 0x1a)     /* पढ़ो/ग_लिखो */
#घोषणा REG_ENA_AP                REG(0x00, 0x1e)     /* पढ़ो/ग_लिखो */
#घोषणा REG_VIP_CNTRL_0           REG(0x00, 0x20)     /* ग_लिखो */
# define VIP_CNTRL_0_MIRR_A       (1 << 7)
# define VIP_CNTRL_0_SWAP_A(x)    (((x) & 7) << 4)
# define VIP_CNTRL_0_MIRR_B       (1 << 3)
# define VIP_CNTRL_0_SWAP_B(x)    (((x) & 7) << 0)
#घोषणा REG_VIP_CNTRL_1           REG(0x00, 0x21)     /* ग_लिखो */
# define VIP_CNTRL_1_MIRR_C       (1 << 7)
# define VIP_CNTRL_1_SWAP_C(x)    (((x) & 7) << 4)
# define VIP_CNTRL_1_MIRR_D       (1 << 3)
# define VIP_CNTRL_1_SWAP_D(x)    (((x) & 7) << 0)
#घोषणा REG_VIP_CNTRL_2           REG(0x00, 0x22)     /* ग_लिखो */
# define VIP_CNTRL_2_MIRR_E       (1 << 7)
# define VIP_CNTRL_2_SWAP_E(x)    (((x) & 7) << 4)
# define VIP_CNTRL_2_MIRR_F       (1 << 3)
# define VIP_CNTRL_2_SWAP_F(x)    (((x) & 7) << 0)
#घोषणा REG_VIP_CNTRL_3           REG(0x00, 0x23)     /* ग_लिखो */
# define VIP_CNTRL_3_X_TGL        (1 << 0)
# define VIP_CNTRL_3_H_TGL        (1 << 1)
# define VIP_CNTRL_3_V_TGL        (1 << 2)
# define VIP_CNTRL_3_EMB          (1 << 3)
# define VIP_CNTRL_3_SYNC_DE      (1 << 4)
# define VIP_CNTRL_3_SYNC_HS      (1 << 5)
# define VIP_CNTRL_3_DE_INT       (1 << 6)
# define VIP_CNTRL_3_EDGE         (1 << 7)
#घोषणा REG_VIP_CNTRL_4           REG(0x00, 0x24)     /* ग_लिखो */
# define VIP_CNTRL_4_BLC(x)       (((x) & 3) << 0)
# define VIP_CNTRL_4_BLANKIT(x)   (((x) & 3) << 2)
# define VIP_CNTRL_4_CCIR656      (1 << 4)
# define VIP_CNTRL_4_656_ALT      (1 << 5)
# define VIP_CNTRL_4_TST_656      (1 << 6)
# define VIP_CNTRL_4_TST_PAT      (1 << 7)
#घोषणा REG_VIP_CNTRL_5           REG(0x00, 0x25)     /* ग_लिखो */
# define VIP_CNTRL_5_CKCASE       (1 << 0)
# define VIP_CNTRL_5_SP_CNT(x)    (((x) & 3) << 1)
#घोषणा REG_MUX_AP                REG(0x00, 0x26)     /* पढ़ो/ग_लिखो */
# define MUX_AP_SELECT_I2S	  0x64
# define MUX_AP_SELECT_SPDIF	  0x40
#घोषणा REG_MUX_VP_VIP_OUT        REG(0x00, 0x27)     /* पढ़ो/ग_लिखो */
#घोषणा REG_MAT_CONTRL            REG(0x00, 0x80)     /* ग_लिखो */
# define MAT_CONTRL_MAT_SC(x)     (((x) & 3) << 0)
# define MAT_CONTRL_MAT_BP        (1 << 2)
#घोषणा REG_VIDFORMAT             REG(0x00, 0xa0)     /* ग_लिखो */
#घोषणा REG_REFPIX_MSB            REG(0x00, 0xa1)     /* ग_लिखो */
#घोषणा REG_REFPIX_LSB            REG(0x00, 0xa2)     /* ग_लिखो */
#घोषणा REG_REFLINE_MSB           REG(0x00, 0xa3)     /* ग_लिखो */
#घोषणा REG_REFLINE_LSB           REG(0x00, 0xa4)     /* ग_लिखो */
#घोषणा REG_NPIX_MSB              REG(0x00, 0xa5)     /* ग_लिखो */
#घोषणा REG_NPIX_LSB              REG(0x00, 0xa6)     /* ग_लिखो */
#घोषणा REG_NLINE_MSB             REG(0x00, 0xa7)     /* ग_लिखो */
#घोषणा REG_NLINE_LSB             REG(0x00, 0xa8)     /* ग_लिखो */
#घोषणा REG_VS_LINE_STRT_1_MSB    REG(0x00, 0xa9)     /* ग_लिखो */
#घोषणा REG_VS_LINE_STRT_1_LSB    REG(0x00, 0xaa)     /* ग_लिखो */
#घोषणा REG_VS_PIX_STRT_1_MSB     REG(0x00, 0xab)     /* ग_लिखो */
#घोषणा REG_VS_PIX_STRT_1_LSB     REG(0x00, 0xac)     /* ग_लिखो */
#घोषणा REG_VS_LINE_END_1_MSB     REG(0x00, 0xad)     /* ग_लिखो */
#घोषणा REG_VS_LINE_END_1_LSB     REG(0x00, 0xae)     /* ग_लिखो */
#घोषणा REG_VS_PIX_END_1_MSB      REG(0x00, 0xaf)     /* ग_लिखो */
#घोषणा REG_VS_PIX_END_1_LSB      REG(0x00, 0xb0)     /* ग_लिखो */
#घोषणा REG_VS_LINE_STRT_2_MSB    REG(0x00, 0xb1)     /* ग_लिखो */
#घोषणा REG_VS_LINE_STRT_2_LSB    REG(0x00, 0xb2)     /* ग_लिखो */
#घोषणा REG_VS_PIX_STRT_2_MSB     REG(0x00, 0xb3)     /* ग_लिखो */
#घोषणा REG_VS_PIX_STRT_2_LSB     REG(0x00, 0xb4)     /* ग_लिखो */
#घोषणा REG_VS_LINE_END_2_MSB     REG(0x00, 0xb5)     /* ग_लिखो */
#घोषणा REG_VS_LINE_END_2_LSB     REG(0x00, 0xb6)     /* ग_लिखो */
#घोषणा REG_VS_PIX_END_2_MSB      REG(0x00, 0xb7)     /* ग_लिखो */
#घोषणा REG_VS_PIX_END_2_LSB      REG(0x00, 0xb8)     /* ग_लिखो */
#घोषणा REG_HS_PIX_START_MSB      REG(0x00, 0xb9)     /* ग_लिखो */
#घोषणा REG_HS_PIX_START_LSB      REG(0x00, 0xba)     /* ग_लिखो */
#घोषणा REG_HS_PIX_STOP_MSB       REG(0x00, 0xbb)     /* ग_लिखो */
#घोषणा REG_HS_PIX_STOP_LSB       REG(0x00, 0xbc)     /* ग_लिखो */
#घोषणा REG_VWIN_START_1_MSB      REG(0x00, 0xbd)     /* ग_लिखो */
#घोषणा REG_VWIN_START_1_LSB      REG(0x00, 0xbe)     /* ग_लिखो */
#घोषणा REG_VWIN_END_1_MSB        REG(0x00, 0xbf)     /* ग_लिखो */
#घोषणा REG_VWIN_END_1_LSB        REG(0x00, 0xc0)     /* ग_लिखो */
#घोषणा REG_VWIN_START_2_MSB      REG(0x00, 0xc1)     /* ग_लिखो */
#घोषणा REG_VWIN_START_2_LSB      REG(0x00, 0xc2)     /* ग_लिखो */
#घोषणा REG_VWIN_END_2_MSB        REG(0x00, 0xc3)     /* ग_लिखो */
#घोषणा REG_VWIN_END_2_LSB        REG(0x00, 0xc4)     /* ग_लिखो */
#घोषणा REG_DE_START_MSB          REG(0x00, 0xc5)     /* ग_लिखो */
#घोषणा REG_DE_START_LSB          REG(0x00, 0xc6)     /* ग_लिखो */
#घोषणा REG_DE_STOP_MSB           REG(0x00, 0xc7)     /* ग_लिखो */
#घोषणा REG_DE_STOP_LSB           REG(0x00, 0xc8)     /* ग_लिखो */
#घोषणा REG_TBG_CNTRL_0           REG(0x00, 0xca)     /* ग_लिखो */
# define TBG_CNTRL_0_TOP_TGL      (1 << 0)
# define TBG_CNTRL_0_TOP_SEL      (1 << 1)
# define TBG_CNTRL_0_DE_EXT       (1 << 2)
# define TBG_CNTRL_0_TOP_EXT      (1 << 3)
# define TBG_CNTRL_0_FRAME_DIS    (1 << 5)
# define TBG_CNTRL_0_SYNC_MTHD    (1 << 6)
# define TBG_CNTRL_0_SYNC_ONCE    (1 << 7)
#घोषणा REG_TBG_CNTRL_1           REG(0x00, 0xcb)     /* ग_लिखो */
# define TBG_CNTRL_1_H_TGL        (1 << 0)
# define TBG_CNTRL_1_V_TGL        (1 << 1)
# define TBG_CNTRL_1_TGL_EN       (1 << 2)
# define TBG_CNTRL_1_X_EXT        (1 << 3)
# define TBG_CNTRL_1_H_EXT        (1 << 4)
# define TBG_CNTRL_1_V_EXT        (1 << 5)
# define TBG_CNTRL_1_DWIN_DIS     (1 << 6)
#घोषणा REG_ENABLE_SPACE          REG(0x00, 0xd6)     /* ग_लिखो */
#घोषणा REG_HVF_CNTRL_0           REG(0x00, 0xe4)     /* ग_लिखो */
# define HVF_CNTRL_0_SM           (1 << 7)
# define HVF_CNTRL_0_RWB          (1 << 6)
# define HVF_CNTRL_0_PREFIL(x)    (((x) & 3) << 2)
# define HVF_CNTRL_0_INTPOL(x)    (((x) & 3) << 0)
#घोषणा REG_HVF_CNTRL_1           REG(0x00, 0xe5)     /* ग_लिखो */
# define HVF_CNTRL_1_FOR          (1 << 0)
# define HVF_CNTRL_1_YUVBLK       (1 << 1)
# define HVF_CNTRL_1_VQR(x)       (((x) & 3) << 2)
# define HVF_CNTRL_1_PAD(x)       (((x) & 3) << 4)
# define HVF_CNTRL_1_SEMI_PLANAR  (1 << 6)
#घोषणा REG_RPT_CNTRL             REG(0x00, 0xf0)     /* ग_लिखो */
# define RPT_CNTRL_REPEAT(x)      ((x) & 15)
#घोषणा REG_I2S_FORMAT            REG(0x00, 0xfc)     /* पढ़ो/ग_लिखो */
# define I2S_FORMAT_PHILIPS       (0 << 0)
# define I2S_FORMAT_LEFT_J        (2 << 0)
# define I2S_FORMAT_RIGHT_J       (3 << 0)
#घोषणा REG_AIP_CLKSEL            REG(0x00, 0xfd)     /* ग_लिखो */
# define AIP_CLKSEL_AIP_SPDIF	  (0 << 3)
# define AIP_CLKSEL_AIP_I2S	  (1 << 3)
# define AIP_CLKSEL_FS_ACLK	  (0 << 0)
# define AIP_CLKSEL_FS_MCLK	  (1 << 0)
# define AIP_CLKSEL_FS_FS64SPDIF  (2 << 0)

/* Page 02h: PLL settings */
#घोषणा REG_PLL_SERIAL_1          REG(0x02, 0x00)     /* पढ़ो/ग_लिखो */
# define PLL_SERIAL_1_SRL_FDN     (1 << 0)
# define PLL_SERIAL_1_SRL_IZ(x)   (((x) & 3) << 1)
# define PLL_SERIAL_1_SRL_MAN_IZ  (1 << 6)
#घोषणा REG_PLL_SERIAL_2          REG(0x02, 0x01)     /* पढ़ो/ग_लिखो */
# define PLL_SERIAL_2_SRL_NOSC(x) ((x) << 0)
# define PLL_SERIAL_2_SRL_PR(x)   (((x) & 0xf) << 4)
#घोषणा REG_PLL_SERIAL_3          REG(0x02, 0x02)     /* पढ़ो/ग_लिखो */
# define PLL_SERIAL_3_SRL_CCIR    (1 << 0)
# define PLL_SERIAL_3_SRL_DE      (1 << 2)
# define PLL_SERIAL_3_SRL_PXIN_SEL (1 << 4)
#घोषणा REG_SERIALIZER            REG(0x02, 0x03)     /* पढ़ो/ग_लिखो */
#घोषणा REG_BUFFER_OUT            REG(0x02, 0x04)     /* पढ़ो/ग_लिखो */
#घोषणा REG_PLL_SCG1              REG(0x02, 0x05)     /* पढ़ो/ग_लिखो */
#घोषणा REG_PLL_SCG2              REG(0x02, 0x06)     /* पढ़ो/ग_लिखो */
#घोषणा REG_PLL_SCGN1             REG(0x02, 0x07)     /* पढ़ो/ग_लिखो */
#घोषणा REG_PLL_SCGN2             REG(0x02, 0x08)     /* पढ़ो/ग_लिखो */
#घोषणा REG_PLL_SCGR1             REG(0x02, 0x09)     /* पढ़ो/ग_लिखो */
#घोषणा REG_PLL_SCGR2             REG(0x02, 0x0a)     /* पढ़ो/ग_लिखो */
#घोषणा REG_AUDIO_DIV             REG(0x02, 0x0e)     /* पढ़ो/ग_लिखो */
# define AUDIO_DIV_SERCLK_1       0
# define AUDIO_DIV_SERCLK_2       1
# define AUDIO_DIV_SERCLK_4       2
# define AUDIO_DIV_SERCLK_8       3
# define AUDIO_DIV_SERCLK_16      4
# define AUDIO_DIV_SERCLK_32      5
#घोषणा REG_SEL_CLK               REG(0x02, 0x11)     /* पढ़ो/ग_लिखो */
# define SEL_CLK_SEL_CLK1         (1 << 0)
# define SEL_CLK_SEL_VRF_CLK(x)   (((x) & 3) << 1)
# define SEL_CLK_ENA_SC_CLK       (1 << 3)
#घोषणा REG_ANA_GENERAL           REG(0x02, 0x12)     /* पढ़ो/ग_लिखो */


/* Page 09h: EDID Control */
#घोषणा REG_EDID_DATA_0           REG(0x09, 0x00)     /* पढ़ो */
/* next 127 successive रेजिस्टरs are the EDID block */
#घोषणा REG_EDID_CTRL             REG(0x09, 0xfa)     /* पढ़ो/ग_लिखो */
#घोषणा REG_DDC_ADDR              REG(0x09, 0xfb)     /* पढ़ो/ग_लिखो */
#घोषणा REG_DDC_OFFS              REG(0x09, 0xfc)     /* पढ़ो/ग_लिखो */
#घोषणा REG_DDC_SEGM_ADDR         REG(0x09, 0xfd)     /* पढ़ो/ग_लिखो */
#घोषणा REG_DDC_SEGM              REG(0x09, 0xfe)     /* पढ़ो/ग_लिखो */


/* Page 10h: inक्रमmation frames and packets */
#घोषणा REG_IF1_HB0               REG(0x10, 0x20)     /* पढ़ो/ग_लिखो */
#घोषणा REG_IF2_HB0               REG(0x10, 0x40)     /* पढ़ो/ग_लिखो */
#घोषणा REG_IF3_HB0               REG(0x10, 0x60)     /* पढ़ो/ग_लिखो */
#घोषणा REG_IF4_HB0               REG(0x10, 0x80)     /* पढ़ो/ग_लिखो */
#घोषणा REG_IF5_HB0               REG(0x10, 0xa0)     /* पढ़ो/ग_लिखो */


/* Page 11h: audio settings and content info packets */
#घोषणा REG_AIP_CNTRL_0           REG(0x11, 0x00)     /* पढ़ो/ग_लिखो */
# define AIP_CNTRL_0_RST_FIFO     (1 << 0)
# define AIP_CNTRL_0_SWAP         (1 << 1)
# define AIP_CNTRL_0_LAYOUT       (1 << 2)
# define AIP_CNTRL_0_ACR_MAN      (1 << 5)
# define AIP_CNTRL_0_RST_CTS      (1 << 6)
#घोषणा REG_CA_I2S                REG(0x11, 0x01)     /* पढ़ो/ग_लिखो */
# define CA_I2S_CA_I2S(x)         (((x) & 31) << 0)
# define CA_I2S_HBR_CHSTAT        (1 << 6)
#घोषणा REG_LATENCY_RD            REG(0x11, 0x04)     /* पढ़ो/ग_लिखो */
#घोषणा REG_ACR_CTS_0             REG(0x11, 0x05)     /* पढ़ो/ग_लिखो */
#घोषणा REG_ACR_CTS_1             REG(0x11, 0x06)     /* पढ़ो/ग_लिखो */
#घोषणा REG_ACR_CTS_2             REG(0x11, 0x07)     /* पढ़ो/ग_लिखो */
#घोषणा REG_ACR_N_0               REG(0x11, 0x08)     /* पढ़ो/ग_लिखो */
#घोषणा REG_ACR_N_1               REG(0x11, 0x09)     /* पढ़ो/ग_लिखो */
#घोषणा REG_ACR_N_2               REG(0x11, 0x0a)     /* पढ़ो/ग_लिखो */
#घोषणा REG_CTS_N                 REG(0x11, 0x0c)     /* पढ़ो/ग_लिखो */
# define CTS_N_K(x)               (((x) & 7) << 0)
# define CTS_N_M(x)               (((x) & 3) << 4)
#घोषणा REG_ENC_CNTRL             REG(0x11, 0x0d)     /* पढ़ो/ग_लिखो */
# define ENC_CNTRL_RST_ENC        (1 << 0)
# define ENC_CNTRL_RST_SEL        (1 << 1)
# define ENC_CNTRL_CTL_CODE(x)    (((x) & 3) << 2)
#घोषणा REG_DIP_FLAGS             REG(0x11, 0x0e)     /* पढ़ो/ग_लिखो */
# define DIP_FLAGS_ACR            (1 << 0)
# define DIP_FLAGS_GC             (1 << 1)
#घोषणा REG_DIP_IF_FLAGS          REG(0x11, 0x0f)     /* पढ़ो/ग_लिखो */
# define DIP_IF_FLAGS_IF1         (1 << 1)
# define DIP_IF_FLAGS_IF2         (1 << 2)
# define DIP_IF_FLAGS_IF3         (1 << 3)
# define DIP_IF_FLAGS_IF4         (1 << 4)
# define DIP_IF_FLAGS_IF5         (1 << 5)
#घोषणा REG_CH_STAT_B(x)          REG(0x11, 0x14 + (x)) /* पढ़ो/ग_लिखो */


/* Page 12h: HDCP and OTP */
#घोषणा REG_TX3                   REG(0x12, 0x9a)     /* पढ़ो/ग_लिखो */
#घोषणा REG_TX4                   REG(0x12, 0x9b)     /* पढ़ो/ग_लिखो */
# define TX4_PD_RAM               (1 << 1)
#घोषणा REG_TX33                  REG(0x12, 0xb8)     /* पढ़ो/ग_लिखो */
# define TX33_HDMI                (1 << 1)


/* Page 13h: Gamut related metadata packets */



/* CEC रेजिस्टरs: (not paged)
 */
#घोषणा REG_CEC_INTSTATUS	  0xee		      /* पढ़ो */
# define CEC_INTSTATUS_CEC	  (1 << 0)
# define CEC_INTSTATUS_HDMI	  (1 << 1)
#घोषणा REG_CEC_CAL_XOSC_CTRL1    0xf2
# define CEC_CAL_XOSC_CTRL1_ENA_CAL	BIT(0)
#घोषणा REG_CEC_DES_FREQ2         0xf5
# define CEC_DES_FREQ2_DIS_AUTOCAL BIT(7)
#घोषणा REG_CEC_CLK               0xf6
# define CEC_CLK_FRO              0x11
#घोषणा REG_CEC_FRO_IM_CLK_CTRL   0xfb                /* पढ़ो/ग_लिखो */
# define CEC_FRO_IM_CLK_CTRL_GHOST_DIS (1 << 7)
# define CEC_FRO_IM_CLK_CTRL_ENA_OTP   (1 << 6)
# define CEC_FRO_IM_CLK_CTRL_IMCLK_SEL (1 << 1)
# define CEC_FRO_IM_CLK_CTRL_FRO_DIV   (1 << 0)
#घोषणा REG_CEC_RXSHPDINTENA	  0xfc		      /* पढ़ो/ग_लिखो */
#घोषणा REG_CEC_RXSHPDINT	  0xfd		      /* पढ़ो */
# define CEC_RXSHPDINT_RXSENS     BIT(0)
# define CEC_RXSHPDINT_HPD        BIT(1)
#घोषणा REG_CEC_RXSHPDLEV         0xfe                /* पढ़ो */
# define CEC_RXSHPDLEV_RXSENS     (1 << 0)
# define CEC_RXSHPDLEV_HPD        (1 << 1)

#घोषणा REG_CEC_ENAMODS           0xff                /* पढ़ो/ग_लिखो */
# define CEC_ENAMODS_EN_CEC_CLK   (1 << 7)
# define CEC_ENAMODS_DIS_FRO      (1 << 6)
# define CEC_ENAMODS_DIS_CCLK     (1 << 5)
# define CEC_ENAMODS_EN_RXSENS    (1 << 2)
# define CEC_ENAMODS_EN_HDMI      (1 << 1)
# define CEC_ENAMODS_EN_CEC       (1 << 0)


/* Device versions: */
#घोषणा TDA9989N2                 0x0101
#घोषणा TDA19989                  0x0201
#घोषणा TDA19989N2                0x0202
#घोषणा TDA19988                  0x0301

अटल व्योम
cec_ग_लिखो(काष्ठा tda998x_priv *priv, u16 addr, u8 val)
अणु
	u8 buf[] = अणुaddr, valपूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = priv->cec_addr,
		.len = 2,
		.buf = buf,
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(priv->hdmi->adapter, &msg, 1);
	अगर (ret < 0)
		dev_err(&priv->hdmi->dev, "Error %d writing to cec:0x%x\n",
			ret, addr);
पूर्ण

अटल u8
cec_पढ़ो(काष्ठा tda998x_priv *priv, u8 addr)
अणु
	u8 val;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = priv->cec_addr,
			.len = 1,
			.buf = &addr,
		पूर्ण, अणु
			.addr = priv->cec_addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = &val,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(priv->hdmi->adapter, msg, ARRAY_SIZE(msg));
	अगर (ret < 0) अणु
		dev_err(&priv->hdmi->dev, "Error %d reading from cec:0x%x\n",
			ret, addr);
		val = 0;
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम cec_enamods(काष्ठा tda998x_priv *priv, u8 mods, bool enable)
अणु
	पूर्णांक val = cec_पढ़ो(priv, REG_CEC_ENAMODS);

	अगर (val < 0)
		वापस;

	अगर (enable)
		val |= mods;
	अन्यथा
		val &= ~mods;

	cec_ग_लिखो(priv, REG_CEC_ENAMODS, val);
पूर्ण

अटल व्योम tda998x_cec_set_calibration(काष्ठा tda998x_priv *priv, bool enable)
अणु
	अगर (enable) अणु
		u8 val;

		cec_ग_लिखो(priv, 0xf3, 0xc0);
		cec_ग_लिखो(priv, 0xf4, 0xd4);

		/* Enable स्वतःmatic calibration mode */
		val = cec_पढ़ो(priv, REG_CEC_DES_FREQ2);
		val &= ~CEC_DES_FREQ2_DIS_AUTOCAL;
		cec_ग_लिखो(priv, REG_CEC_DES_FREQ2, val);

		/* Enable मुक्त running oscillator */
		cec_ग_लिखो(priv, REG_CEC_CLK, CEC_CLK_FRO);
		cec_enamods(priv, CEC_ENAMODS_DIS_FRO, false);

		cec_ग_लिखो(priv, REG_CEC_CAL_XOSC_CTRL1,
			  CEC_CAL_XOSC_CTRL1_ENA_CAL);
	पूर्ण अन्यथा अणु
		cec_ग_लिखो(priv, REG_CEC_CAL_XOSC_CTRL1, 0);
	पूर्ण
पूर्ण

/*
 * Calibration क्रम the पूर्णांकernal oscillator: we need to set calibration mode,
 * and then pulse the IRQ line low क्रम a 10ms तऔ 1% period.
 */
अटल व्योम tda998x_cec_calibration(काष्ठा tda998x_priv *priv)
अणु
	काष्ठा gpio_desc *calib = priv->calib;

	mutex_lock(&priv->edid_mutex);
	अगर (priv->hdmi->irq > 0)
		disable_irq(priv->hdmi->irq);
	gpiod_direction_output(calib, 1);
	tda998x_cec_set_calibration(priv, true);

	local_irq_disable();
	gpiod_set_value(calib, 0);
	mdelay(10);
	gpiod_set_value(calib, 1);
	local_irq_enable();

	tda998x_cec_set_calibration(priv, false);
	gpiod_direction_input(calib);
	अगर (priv->hdmi->irq > 0)
		enable_irq(priv->hdmi->irq);
	mutex_unlock(&priv->edid_mutex);
पूर्ण

अटल पूर्णांक tda998x_cec_hook_init(व्योम *data)
अणु
	काष्ठा tda998x_priv *priv = data;
	काष्ठा gpio_desc *calib;

	calib = gpiod_get(&priv->hdmi->dev, "nxp,calib", GPIOD_ASIS);
	अगर (IS_ERR(calib)) अणु
		dev_warn(&priv->hdmi->dev, "failed to get calibration gpio: %ld\n",
			 PTR_ERR(calib));
		वापस PTR_ERR(calib);
	पूर्ण

	priv->calib = calib;

	वापस 0;
पूर्ण

अटल व्योम tda998x_cec_hook_निकास(व्योम *data)
अणु
	काष्ठा tda998x_priv *priv = data;

	gpiod_put(priv->calib);
	priv->calib = शून्य;
पूर्ण

अटल पूर्णांक tda998x_cec_hook_खोलो(व्योम *data)
अणु
	काष्ठा tda998x_priv *priv = data;

	cec_enamods(priv, CEC_ENAMODS_EN_CEC_CLK | CEC_ENAMODS_EN_CEC, true);
	tda998x_cec_calibration(priv);

	वापस 0;
पूर्ण

अटल व्योम tda998x_cec_hook_release(व्योम *data)
अणु
	काष्ठा tda998x_priv *priv = data;

	cec_enamods(priv, CEC_ENAMODS_EN_CEC_CLK | CEC_ENAMODS_EN_CEC, false);
पूर्ण

अटल पूर्णांक
set_page(काष्ठा tda998x_priv *priv, u16 reg)
अणु
	अगर (REG2PAGE(reg) != priv->current_page) अणु
		काष्ठा i2c_client *client = priv->hdmi;
		u8 buf[] = अणु
				REG_CURPAGE, REG2PAGE(reg)
		पूर्ण;
		पूर्णांक ret = i2c_master_send(client, buf, माप(buf));
		अगर (ret < 0) अणु
			dev_err(&client->dev, "%s %04x err %d\n", __func__,
					reg, ret);
			वापस ret;
		पूर्ण

		priv->current_page = REG2PAGE(reg);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
reg_पढ़ो_range(काष्ठा tda998x_priv *priv, u16 reg, अक्षर *buf, पूर्णांक cnt)
अणु
	काष्ठा i2c_client *client = priv->hdmi;
	u8 addr = REG2ADDR(reg);
	पूर्णांक ret;

	mutex_lock(&priv->mutex);
	ret = set_page(priv, reg);
	अगर (ret < 0)
		जाओ out;

	ret = i2c_master_send(client, &addr, माप(addr));
	अगर (ret < 0)
		जाओ fail;

	ret = i2c_master_recv(client, buf, cnt);
	अगर (ret < 0)
		जाओ fail;

	जाओ out;

fail:
	dev_err(&client->dev, "Error %d reading from 0x%x\n", ret, reg);
out:
	mutex_unlock(&priv->mutex);
	वापस ret;
पूर्ण

#घोषणा MAX_WRITE_RANGE_BUF 32

अटल व्योम
reg_ग_लिखो_range(काष्ठा tda998x_priv *priv, u16 reg, u8 *p, पूर्णांक cnt)
अणु
	काष्ठा i2c_client *client = priv->hdmi;
	/* This is the maximum size of the buffer passed in */
	u8 buf[MAX_WRITE_RANGE_BUF + 1];
	पूर्णांक ret;

	अगर (cnt > MAX_WRITE_RANGE_BUF) अणु
		dev_err(&client->dev, "Fixed write buffer too small (%d)\n",
				MAX_WRITE_RANGE_BUF);
		वापस;
	पूर्ण

	buf[0] = REG2ADDR(reg);
	स_नकल(&buf[1], p, cnt);

	mutex_lock(&priv->mutex);
	ret = set_page(priv, reg);
	अगर (ret < 0)
		जाओ out;

	ret = i2c_master_send(client, buf, cnt + 1);
	अगर (ret < 0)
		dev_err(&client->dev, "Error %d writing to 0x%x\n", ret, reg);
out:
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक
reg_पढ़ो(काष्ठा tda998x_priv *priv, u16 reg)
अणु
	u8 val = 0;
	पूर्णांक ret;

	ret = reg_पढ़ो_range(priv, reg, &val, माप(val));
	अगर (ret < 0)
		वापस ret;
	वापस val;
पूर्ण

अटल व्योम
reg_ग_लिखो(काष्ठा tda998x_priv *priv, u16 reg, u8 val)
अणु
	काष्ठा i2c_client *client = priv->hdmi;
	u8 buf[] = अणुREG2ADDR(reg), valपूर्ण;
	पूर्णांक ret;

	mutex_lock(&priv->mutex);
	ret = set_page(priv, reg);
	अगर (ret < 0)
		जाओ out;

	ret = i2c_master_send(client, buf, माप(buf));
	अगर (ret < 0)
		dev_err(&client->dev, "Error %d writing to 0x%x\n", ret, reg);
out:
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम
reg_ग_लिखो16(काष्ठा tda998x_priv *priv, u16 reg, u16 val)
अणु
	काष्ठा i2c_client *client = priv->hdmi;
	u8 buf[] = अणुREG2ADDR(reg), val >> 8, valपूर्ण;
	पूर्णांक ret;

	mutex_lock(&priv->mutex);
	ret = set_page(priv, reg);
	अगर (ret < 0)
		जाओ out;

	ret = i2c_master_send(client, buf, माप(buf));
	अगर (ret < 0)
		dev_err(&client->dev, "Error %d writing to 0x%x\n", ret, reg);
out:
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम
reg_set(काष्ठा tda998x_priv *priv, u16 reg, u8 val)
अणु
	पूर्णांक old_val;

	old_val = reg_पढ़ो(priv, reg);
	अगर (old_val >= 0)
		reg_ग_लिखो(priv, reg, old_val | val);
पूर्ण

अटल व्योम
reg_clear(काष्ठा tda998x_priv *priv, u16 reg, u8 val)
अणु
	पूर्णांक old_val;

	old_val = reg_पढ़ो(priv, reg);
	अगर (old_val >= 0)
		reg_ग_लिखो(priv, reg, old_val & ~val);
पूर्ण

अटल व्योम
tda998x_reset(काष्ठा tda998x_priv *priv)
अणु
	/* reset audio and i2c master: */
	reg_ग_लिखो(priv, REG_SOFTRESET, SOFTRESET_AUDIO | SOFTRESET_I2C_MASTER);
	msleep(50);
	reg_ग_लिखो(priv, REG_SOFTRESET, 0);
	msleep(50);

	/* reset transmitter: */
	reg_set(priv, REG_MAIN_CNTRL0, MAIN_CNTRL0_SR);
	reg_clear(priv, REG_MAIN_CNTRL0, MAIN_CNTRL0_SR);

	/* PLL रेजिस्टरs common configuration */
	reg_ग_लिखो(priv, REG_PLL_SERIAL_1, 0x00);
	reg_ग_लिखो(priv, REG_PLL_SERIAL_2, PLL_SERIAL_2_SRL_NOSC(1));
	reg_ग_लिखो(priv, REG_PLL_SERIAL_3, 0x00);
	reg_ग_लिखो(priv, REG_SERIALIZER,   0x00);
	reg_ग_लिखो(priv, REG_BUFFER_OUT,   0x00);
	reg_ग_लिखो(priv, REG_PLL_SCG1,     0x00);
	reg_ग_लिखो(priv, REG_AUDIO_DIV,    AUDIO_DIV_SERCLK_8);
	reg_ग_लिखो(priv, REG_SEL_CLK,      SEL_CLK_SEL_CLK1 | SEL_CLK_ENA_SC_CLK);
	reg_ग_लिखो(priv, REG_PLL_SCGN1,    0xfa);
	reg_ग_लिखो(priv, REG_PLL_SCGN2,    0x00);
	reg_ग_लिखो(priv, REG_PLL_SCGR1,    0x5b);
	reg_ग_लिखो(priv, REG_PLL_SCGR2,    0x00);
	reg_ग_लिखो(priv, REG_PLL_SCG2,     0x10);

	/* Write the शेष value MUX रेजिस्टर */
	reg_ग_लिखो(priv, REG_MUX_VP_VIP_OUT, 0x24);
पूर्ण

/*
 * The TDA998x has a problem when trying to पढ़ो the EDID बंद to a
 * HPD निश्चितion: it needs a delay of 100ms to aव्योम timing out जबतक
 * trying to पढ़ो EDID data.
 *
 * However, tda998x_connector_get_modes() may be called at any moment
 * after tda998x_connector_detect() indicates that we are connected, so
 * we need to delay probing modes in tda998x_connector_get_modes() after
 * we have seen a HPD inactive->active transition.  This code implements
 * that delay.
 */
अटल व्योम tda998x_edid_delay_करोne(काष्ठा समयr_list *t)
अणु
	काष्ठा tda998x_priv *priv = from_समयr(priv, t, edid_delay_समयr);

	priv->edid_delay_active = false;
	wake_up(&priv->edid_delay_रुकोq);
	schedule_work(&priv->detect_work);
पूर्ण

अटल व्योम tda998x_edid_delay_start(काष्ठा tda998x_priv *priv)
अणु
	priv->edid_delay_active = true;
	mod_समयr(&priv->edid_delay_समयr, jअगरfies + HZ/10);
पूर्ण

अटल पूर्णांक tda998x_edid_delay_रुको(काष्ठा tda998x_priv *priv)
अणु
	वापस रुको_event_समाप्तable(priv->edid_delay_रुकोq, !priv->edid_delay_active);
पूर्ण

/*
 * We need to run the KMS hotplug event helper outside of our thपढ़ोed
 * पूर्णांकerrupt routine as this can call back पूर्णांकo our get_modes method,
 * which will want to make use of पूर्णांकerrupts.
 */
अटल व्योम tda998x_detect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tda998x_priv *priv =
		container_of(work, काष्ठा tda998x_priv, detect_work);
	काष्ठा drm_device *dev = priv->connector.dev;

	अगर (dev)
		drm_kms_helper_hotplug_event(dev);
पूर्ण

/*
 * only 2 पूर्णांकerrupts may occur: screen plug/unplug and EDID पढ़ो
 */
अटल irqवापस_t tda998x_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tda998x_priv *priv = data;
	u8 sta, cec, lvl, flag0, flag1, flag2;
	bool handled = false;

	sta = cec_पढ़ो(priv, REG_CEC_INTSTATUS);
	अगर (sta & CEC_INTSTATUS_HDMI) अणु
		cec = cec_पढ़ो(priv, REG_CEC_RXSHPDINT);
		lvl = cec_पढ़ो(priv, REG_CEC_RXSHPDLEV);
		flag0 = reg_पढ़ो(priv, REG_INT_FLAGS_0);
		flag1 = reg_पढ़ो(priv, REG_INT_FLAGS_1);
		flag2 = reg_पढ़ो(priv, REG_INT_FLAGS_2);
		DRM_DEBUG_DRIVER(
			"tda irq sta %02x cec %02x lvl %02x f0 %02x f1 %02x f2 %02x\n",
			sta, cec, lvl, flag0, flag1, flag2);

		अगर (cec & CEC_RXSHPDINT_HPD) अणु
			अगर (lvl & CEC_RXSHPDLEV_HPD) अणु
				tda998x_edid_delay_start(priv);
			पूर्ण अन्यथा अणु
				schedule_work(&priv->detect_work);
				cec_notअगरier_phys_addr_invalidate(
						priv->cec_notअगरy);
			पूर्ण

			handled = true;
		पूर्ण

		अगर ((flag2 & INT_FLAGS_2_EDID_BLK_RD) && priv->wq_edid_रुको) अणु
			priv->wq_edid_रुको = 0;
			wake_up(&priv->wq_edid);
			handled = true;
		पूर्ण
	पूर्ण

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम
tda998x_ग_लिखो_अगर(काष्ठा tda998x_priv *priv, u8 bit, u16 addr,
		 जोड़ hdmi_infoframe *frame)
अणु
	u8 buf[MAX_WRITE_RANGE_BUF];
	sमाप_प्रकार len;

	len = hdmi_infoframe_pack(frame, buf, माप(buf));
	अगर (len < 0) अणु
		dev_err(&priv->hdmi->dev,
			"hdmi_infoframe_pack() type=0x%02x failed: %zd\n",
			frame->any.type, len);
		वापस;
	पूर्ण

	reg_clear(priv, REG_DIP_IF_FLAGS, bit);
	reg_ग_लिखो_range(priv, addr, buf, len);
	reg_set(priv, REG_DIP_IF_FLAGS, bit);
पूर्ण

अटल व्योम tda998x_ग_लिखो_aअगर(काष्ठा tda998x_priv *priv,
			      स्थिर काष्ठा hdmi_audio_infoframe *cea)
अणु
	जोड़ hdmi_infoframe frame;

	frame.audio = *cea;

	tda998x_ग_लिखो_अगर(priv, DIP_IF_FLAGS_IF4, REG_IF4_HB0, &frame);
पूर्ण

अटल व्योम
tda998x_ग_लिखो_avi(काष्ठा tda998x_priv *priv, स्थिर काष्ठा drm_display_mode *mode)
अणु
	जोड़ hdmi_infoframe frame;

	drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						 &priv->connector, mode);
	frame.avi.quantization_range = HDMI_QUANTIZATION_RANGE_FULL;
	drm_hdmi_avi_infoframe_quant_range(&frame.avi, &priv->connector, mode,
					   priv->rgb_quant_range);

	tda998x_ग_लिखो_अगर(priv, DIP_IF_FLAGS_IF2, REG_IF2_HB0, &frame);
पूर्ण

अटल व्योम tda998x_ग_लिखो_vsi(काष्ठा tda998x_priv *priv,
			      स्थिर काष्ठा drm_display_mode *mode)
अणु
	जोड़ hdmi_infoframe frame;

	अगर (drm_hdmi_venकरोr_infoframe_from_display_mode(&frame.venकरोr.hdmi,
							&priv->connector,
							mode))
		reg_clear(priv, REG_DIP_IF_FLAGS, DIP_IF_FLAGS_IF1);
	अन्यथा
		tda998x_ग_लिखो_अगर(priv, DIP_IF_FLAGS_IF1, REG_IF1_HB0, &frame);
पूर्ण

/* Audio support */

अटल स्थिर काष्ठा tda998x_audio_route tda998x_audio_route[AUDIO_ROUTE_NUM] = अणु
	[AUDIO_ROUTE_I2S] = अणु
		.ena_aclk = 1,
		.mux_ap = MUX_AP_SELECT_I2S,
		.aip_clksel = AIP_CLKSEL_AIP_I2S | AIP_CLKSEL_FS_ACLK,
	पूर्ण,
	[AUDIO_ROUTE_SPDIF] = अणु
		.ena_aclk = 0,
		.mux_ap = MUX_AP_SELECT_SPDIF,
		.aip_clksel = AIP_CLKSEL_AIP_SPDIF | AIP_CLKSEL_FS_FS64SPDIF,
	पूर्ण,
पूर्ण;

/* Configure the TDA998x audio data and घड़ी routing. */
अटल पूर्णांक tda998x_derive_routing(काष्ठा tda998x_priv *priv,
				  काष्ठा tda998x_audio_settings *s,
				  अचिन्हित पूर्णांक route)
अणु
	s->route = &tda998x_audio_route[route];
	s->ena_ap = priv->audio_port_enable[route];
	अगर (s->ena_ap == 0) अणु
		dev_err(&priv->hdmi->dev, "no audio configuration found\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The audio घड़ी भागisor रेजिस्टर controls a भागider producing Audio_Clk_Out
 * from SERclk by भागiding it by 2^n where 0 <= n <= 5.  We करोn't know what
 * Audio_Clk_Out or SERclk are. We guess SERclk is the same as TMDS घड़ी.
 *
 * It seems that Audio_Clk_Out must be the smallest value that is greater
 * than 128*fs, otherwise audio करोes not function. There is some suggestion
 * that 126*fs is a better value.
 */
अटल u8 tda998x_get_aभाग(काष्ठा tda998x_priv *priv, अचिन्हित पूर्णांक fs)
अणु
	अचिन्हित दीर्घ min_audio_clk = fs * 128;
	अचिन्हित दीर्घ ser_clk = priv->पंचांगds_घड़ी * 1000;
	u8 aभाग;

	क्रम (aभाग = AUDIO_DIV_SERCLK_32; aभाग != AUDIO_DIV_SERCLK_1; aभाग--)
		अगर (ser_clk > min_audio_clk << aभाग)
			अवरोध;

	dev_dbg(&priv->hdmi->dev,
		"ser_clk=%luHz fs=%uHz min_aclk=%luHz adiv=%d\n",
		ser_clk, fs, min_audio_clk, aभाग);

	वापस aभाग;
पूर्ण

/*
 * In स्वतः-CTS mode, the TDA998x uses a "measured time stamp" counter to
 * generate the CTS value.  It appears that the "measured time stamp" is
 * the number of TDMS घड़ी cycles within a number of audio input घड़ी
 * cycles defined by the k and N parameters defined below, in a similar
 * way to that which is set out in the CTS generation in the HDMI spec.
 *
 *  पंचांगdsclk ----> mts -> /m ---> CTS
 *                 ^
 *  sclk -> /k -> /N
 *
 * CTS = mts / m, where m is 2^M.
 * /k is a भागider based on the K value below, K+1 क्रम K < 4, or 8 क्रम K >= 4
 * /N is a भागider based on the HDMI specअगरied N value.
 *
 * This produces the following equation:
 *  CTS = पंचांगds_घड़ी * k * N / (sclk * m)
 *
 * When combined with the sink-side equation, and realising that sclk is
 * bclk_ratio * fs, we end up with:
 *  k = m * bclk_ratio / 128.
 *
 * Note: S/PDIF always uses a bclk_ratio of 64.
 */
अटल पूर्णांक tda998x_derive_cts_n(काष्ठा tda998x_priv *priv,
				काष्ठा tda998x_audio_settings *settings,
				अचिन्हित पूर्णांक ratio)
अणु
	चयन (ratio) अणु
	हाल 16:
		settings->cts_n = CTS_N_M(3) | CTS_N_K(0);
		अवरोध;
	हाल 32:
		settings->cts_n = CTS_N_M(3) | CTS_N_K(1);
		अवरोध;
	हाल 48:
		settings->cts_n = CTS_N_M(3) | CTS_N_K(2);
		अवरोध;
	हाल 64:
		settings->cts_n = CTS_N_M(3) | CTS_N_K(3);
		अवरोध;
	हाल 128:
		settings->cts_n = CTS_N_M(0) | CTS_N_K(0);
		अवरोध;
	शेष:
		dev_err(&priv->hdmi->dev, "unsupported bclk ratio %ufs\n",
			ratio);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tda998x_audio_mute(काष्ठा tda998x_priv *priv, bool on)
अणु
	अगर (on) अणु
		reg_set(priv, REG_SOFTRESET, SOFTRESET_AUDIO);
		reg_clear(priv, REG_SOFTRESET, SOFTRESET_AUDIO);
		reg_set(priv, REG_AIP_CNTRL_0, AIP_CNTRL_0_RST_FIFO);
	पूर्ण अन्यथा अणु
		reg_clear(priv, REG_AIP_CNTRL_0, AIP_CNTRL_0_RST_FIFO);
	पूर्ण
पूर्ण

अटल व्योम tda998x_configure_audio(काष्ठा tda998x_priv *priv)
अणु
	स्थिर काष्ठा tda998x_audio_settings *settings = &priv->audio;
	u8 buf[6], aभाग;
	u32 n;

	/* If audio is not configured, there is nothing to करो. */
	अगर (settings->ena_ap == 0)
		वापस;

	aभाग = tda998x_get_aभाग(priv, settings->sample_rate);

	/* Enable audio ports */
	reg_ग_लिखो(priv, REG_ENA_AP, settings->ena_ap);
	reg_ग_लिखो(priv, REG_ENA_ACLK, settings->route->ena_aclk);
	reg_ग_लिखो(priv, REG_MUX_AP, settings->route->mux_ap);
	reg_ग_लिखो(priv, REG_I2S_FORMAT, settings->i2s_क्रमmat);
	reg_ग_लिखो(priv, REG_AIP_CLKSEL, settings->route->aip_clksel);
	reg_clear(priv, REG_AIP_CNTRL_0, AIP_CNTRL_0_LAYOUT |
					AIP_CNTRL_0_ACR_MAN);	/* स्वतः CTS */
	reg_ग_लिखो(priv, REG_CTS_N, settings->cts_n);
	reg_ग_लिखो(priv, REG_AUDIO_DIV, aभाग);

	/*
	 * This is the approximate value of N, which happens to be
	 * the recommended values क्रम non-coherent घड़ीs.
	 */
	n = 128 * settings->sample_rate / 1000;

	/* Write the CTS and N values */
	buf[0] = 0x44;
	buf[1] = 0x42;
	buf[2] = 0x01;
	buf[3] = n;
	buf[4] = n >> 8;
	buf[5] = n >> 16;
	reg_ग_लिखो_range(priv, REG_ACR_CTS_0, buf, 6);

	/* Reset CTS generator */
	reg_set(priv, REG_AIP_CNTRL_0, AIP_CNTRL_0_RST_CTS);
	reg_clear(priv, REG_AIP_CNTRL_0, AIP_CNTRL_0_RST_CTS);

	/* Write the channel status
	 * The REG_CH_STAT_B-रेजिस्टरs skip IEC958 AES2 byte, because
	 * there is a separate रेजिस्टर क्रम each I2S wire.
	 */
	buf[0] = settings->status[0];
	buf[1] = settings->status[1];
	buf[2] = settings->status[3];
	buf[3] = settings->status[4];
	reg_ग_लिखो_range(priv, REG_CH_STAT_B(0), buf, 4);

	tda998x_audio_mute(priv, true);
	msleep(20);
	tda998x_audio_mute(priv, false);

	tda998x_ग_लिखो_aअगर(priv, &settings->cea);
पूर्ण

अटल पूर्णांक tda998x_audio_hw_params(काष्ठा device *dev, व्योम *data,
				   काष्ठा hdmi_codec_daअगरmt *daअगरmt,
				   काष्ठा hdmi_codec_params *params)
अणु
	काष्ठा tda998x_priv *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक bclk_ratio;
	bool spdअगर = daअगरmt->fmt == HDMI_SPDIF;
	पूर्णांक ret;
	काष्ठा tda998x_audio_settings audio = अणु
		.sample_rate = params->sample_rate,
		.cea = params->cea,
	पूर्ण;

	स_नकल(audio.status, params->iec.status,
	       min(माप(audio.status), माप(params->iec.status)));

	चयन (daअगरmt->fmt) अणु
	हाल HDMI_I2S:
		audio.i2s_क्रमmat = I2S_FORMAT_PHILIPS;
		अवरोध;
	हाल HDMI_LEFT_J:
		audio.i2s_क्रमmat = I2S_FORMAT_LEFT_J;
		अवरोध;
	हाल HDMI_RIGHT_J:
		audio.i2s_क्रमmat = I2S_FORMAT_RIGHT_J;
		अवरोध;
	हाल HDMI_SPDIF:
		audio.i2s_क्रमmat = 0;
		अवरोध;
	शेष:
		dev_err(dev, "%s: Invalid format %d\n", __func__, daअगरmt->fmt);
		वापस -EINVAL;
	पूर्ण

	अगर (!spdअगर &&
	    (daअगरmt->bit_clk_inv || daअगरmt->frame_clk_inv ||
	     daअगरmt->bit_clk_master || daअगरmt->frame_clk_master)) अणु
		dev_err(dev, "%s: Bad flags %d %d %d %d\n", __func__,
			daअगरmt->bit_clk_inv, daअगरmt->frame_clk_inv,
			daअगरmt->bit_clk_master,
			daअगरmt->frame_clk_master);
		वापस -EINVAL;
	पूर्ण

	ret = tda998x_derive_routing(priv, &audio, AUDIO_ROUTE_I2S + spdअगर);
	अगर (ret < 0)
		वापस ret;

	bclk_ratio = spdअगर ? 64 : params->sample_width * 2;
	ret = tda998x_derive_cts_n(priv, &audio, bclk_ratio);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&priv->audio_mutex);
	priv->audio = audio;
	अगर (priv->supports_infoframes && priv->sink_has_audio)
		tda998x_configure_audio(priv);
	mutex_unlock(&priv->audio_mutex);

	वापस 0;
पूर्ण

अटल व्योम tda998x_audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा tda998x_priv *priv = dev_get_drvdata(dev);

	mutex_lock(&priv->audio_mutex);

	reg_ग_लिखो(priv, REG_ENA_AP, 0);
	priv->audio.ena_ap = 0;

	mutex_unlock(&priv->audio_mutex);
पूर्ण

अटल पूर्णांक tda998x_audio_mute_stream(काष्ठा device *dev, व्योम *data,
				     bool enable, पूर्णांक direction)
अणु
	काष्ठा tda998x_priv *priv = dev_get_drvdata(dev);

	mutex_lock(&priv->audio_mutex);

	tda998x_audio_mute(priv, enable);

	mutex_unlock(&priv->audio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक tda998x_audio_get_eld(काष्ठा device *dev, व्योम *data,
				 uपूर्णांक8_t *buf, माप_प्रकार len)
अणु
	काष्ठा tda998x_priv *priv = dev_get_drvdata(dev);

	mutex_lock(&priv->audio_mutex);
	स_नकल(buf, priv->connector.eld,
	       min(माप(priv->connector.eld), len));
	mutex_unlock(&priv->audio_mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hdmi_codec_ops audio_codec_ops = अणु
	.hw_params = tda998x_audio_hw_params,
	.audio_shutकरोwn = tda998x_audio_shutकरोwn,
	.mute_stream = tda998x_audio_mute_stream,
	.get_eld = tda998x_audio_get_eld,
	.no_capture_mute = 1,
पूर्ण;

अटल पूर्णांक tda998x_audio_codec_init(काष्ठा tda998x_priv *priv,
				    काष्ठा device *dev)
अणु
	काष्ठा hdmi_codec_pdata codec_data = अणु
		.ops = &audio_codec_ops,
		.max_i2s_channels = 2,
	पूर्ण;

	अगर (priv->audio_port_enable[AUDIO_ROUTE_I2S])
		codec_data.i2s = 1;
	अगर (priv->audio_port_enable[AUDIO_ROUTE_SPDIF])
		codec_data.spdअगर = 1;

	priv->audio_pdev = platक्रमm_device_रेजिस्टर_data(
		dev, HDMI_CODEC_DRV_NAME, PLATFORM_DEVID_AUTO,
		&codec_data, माप(codec_data));

	वापस PTR_ERR_OR_ZERO(priv->audio_pdev);
पूर्ण

/* DRM connector functions */

अटल क्रमागत drm_connector_status
tda998x_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा tda998x_priv *priv = conn_to_tda998x_priv(connector);
	u8 val = cec_पढ़ो(priv, REG_CEC_RXSHPDLEV);

	वापस (val & CEC_RXSHPDLEV_HPD) ? connector_status_connected :
			connector_status_disconnected;
पूर्ण

अटल व्योम tda998x_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs tda998x_connector_funcs = अणु
	.reset = drm_atomic_helper_connector_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = tda998x_connector_detect,
	.destroy = tda998x_connector_destroy,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक पढ़ो_edid_block(व्योम *data, u8 *buf, अचिन्हित पूर्णांक blk, माप_प्रकार length)
अणु
	काष्ठा tda998x_priv *priv = data;
	u8 offset, segptr;
	पूर्णांक ret, i;

	offset = (blk & 1) ? 128 : 0;
	segptr = blk / 2;

	mutex_lock(&priv->edid_mutex);

	reg_ग_लिखो(priv, REG_DDC_ADDR, 0xa0);
	reg_ग_लिखो(priv, REG_DDC_OFFS, offset);
	reg_ग_लिखो(priv, REG_DDC_SEGM_ADDR, 0x60);
	reg_ग_लिखो(priv, REG_DDC_SEGM, segptr);

	/* enable पढ़ोing EDID: */
	priv->wq_edid_रुको = 1;
	reg_ग_लिखो(priv, REG_EDID_CTRL, 0x1);

	/* flag must be cleared by sw: */
	reg_ग_लिखो(priv, REG_EDID_CTRL, 0x0);

	/* रुको क्रम block पढ़ो to complete: */
	अगर (priv->hdmi->irq) अणु
		i = रुको_event_समयout(priv->wq_edid,
					!priv->wq_edid_रुको,
					msecs_to_jअगरfies(100));
		अगर (i < 0) अणु
			dev_err(&priv->hdmi->dev, "read edid wait err %d\n", i);
			ret = i;
			जाओ failed;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 100; i > 0; i--) अणु
			msleep(1);
			ret = reg_पढ़ो(priv, REG_INT_FLAGS_2);
			अगर (ret < 0)
				जाओ failed;
			अगर (ret & INT_FLAGS_2_EDID_BLK_RD)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == 0) अणु
		dev_err(&priv->hdmi->dev, "read edid timeout\n");
		ret = -ETIMEDOUT;
		जाओ failed;
	पूर्ण

	ret = reg_पढ़ो_range(priv, REG_EDID_DATA_0, buf, length);
	अगर (ret != length) अणु
		dev_err(&priv->hdmi->dev, "failed to read edid block %d: %d\n",
			blk, ret);
		जाओ failed;
	पूर्ण

	ret = 0;

 failed:
	mutex_unlock(&priv->edid_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक tda998x_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा tda998x_priv *priv = conn_to_tda998x_priv(connector);
	काष्ठा edid *edid;
	पूर्णांक n;

	/*
	 * If we get समाप्तed जबतक रुकोing क्रम the HPD समयout, वापस
	 * no modes found: we are not in a restartable path, so we
	 * can't handle संकेतs gracefully.
	 */
	अगर (tda998x_edid_delay_रुको(priv))
		वापस 0;

	अगर (priv->rev == TDA19988)
		reg_clear(priv, REG_TX4, TX4_PD_RAM);

	edid = drm_करो_get_edid(connector, पढ़ो_edid_block, priv);

	अगर (priv->rev == TDA19988)
		reg_set(priv, REG_TX4, TX4_PD_RAM);

	अगर (!edid) अणु
		dev_warn(&priv->hdmi->dev, "failed to read EDID\n");
		वापस 0;
	पूर्ण

	drm_connector_update_edid_property(connector, edid);
	cec_notअगरier_set_phys_addr_from_edid(priv->cec_notअगरy, edid);

	mutex_lock(&priv->audio_mutex);
	n = drm_add_edid_modes(connector, edid);
	priv->sink_has_audio = drm_detect_monitor_audio(edid);
	mutex_unlock(&priv->audio_mutex);

	kमुक्त(edid);

	वापस n;
पूर्ण

अटल काष्ठा drm_encoder *
tda998x_connector_best_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा tda998x_priv *priv = conn_to_tda998x_priv(connector);

	वापस priv->bridge.encoder;
पूर्ण

अटल
स्थिर काष्ठा drm_connector_helper_funcs tda998x_connector_helper_funcs = अणु
	.get_modes = tda998x_connector_get_modes,
	.best_encoder = tda998x_connector_best_encoder,
पूर्ण;

अटल पूर्णांक tda998x_connector_init(काष्ठा tda998x_priv *priv,
				  काष्ठा drm_device *drm)
अणु
	काष्ठा drm_connector *connector = &priv->connector;
	पूर्णांक ret;

	connector->पूर्णांकerlace_allowed = 1;

	अगर (priv->hdmi->irq)
		connector->polled = DRM_CONNECTOR_POLL_HPD;
	अन्यथा
		connector->polled = DRM_CONNECTOR_POLL_CONNECT |
			DRM_CONNECTOR_POLL_DISCONNECT;

	drm_connector_helper_add(connector, &tda998x_connector_helper_funcs);
	ret = drm_connector_init(drm, connector, &tda998x_connector_funcs,
				 DRM_MODE_CONNECTOR_HDMIA);
	अगर (ret)
		वापस ret;

	drm_connector_attach_encoder(&priv->connector,
				     priv->bridge.encoder);

	वापस 0;
पूर्ण

/* DRM bridge functions */

अटल पूर्णांक tda998x_bridge_attach(काष्ठा drm_bridge *bridge,
				 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा tda998x_priv *priv = bridge_to_tda998x_priv(bridge);

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR) अणु
		DRM_ERROR("Fix bridge driver to make connector optional!");
		वापस -EINVAL;
	पूर्ण

	वापस tda998x_connector_init(priv, bridge->dev);
पूर्ण

अटल व्योम tda998x_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tda998x_priv *priv = bridge_to_tda998x_priv(bridge);

	drm_connector_cleanup(&priv->connector);
पूर्ण

अटल क्रमागत drm_mode_status tda998x_bridge_mode_valid(काष्ठा drm_bridge *bridge,
				     स्थिर काष्ठा drm_display_info *info,
				     स्थिर काष्ठा drm_display_mode *mode)
अणु
	/* TDA19988 करोtघड़ी can go up to 165MHz */
	काष्ठा tda998x_priv *priv = bridge_to_tda998x_priv(bridge);

	अगर (mode->घड़ी > ((priv->rev == TDA19988) ? 165000 : 150000))
		वापस MODE_CLOCK_HIGH;
	अगर (mode->htotal >= BIT(13))
		वापस MODE_BAD_HVALUE;
	अगर (mode->vtotal >= BIT(11))
		वापस MODE_BAD_VVALUE;
	वापस MODE_OK;
पूर्ण

अटल व्योम tda998x_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tda998x_priv *priv = bridge_to_tda998x_priv(bridge);

	अगर (!priv->is_on) अणु
		/* enable video ports, audio will be enabled later */
		reg_ग_लिखो(priv, REG_ENA_VP_0, 0xff);
		reg_ग_लिखो(priv, REG_ENA_VP_1, 0xff);
		reg_ग_लिखो(priv, REG_ENA_VP_2, 0xff);
		/* set muxing after enabling ports: */
		reg_ग_लिखो(priv, REG_VIP_CNTRL_0, priv->vip_cntrl_0);
		reg_ग_लिखो(priv, REG_VIP_CNTRL_1, priv->vip_cntrl_1);
		reg_ग_लिखो(priv, REG_VIP_CNTRL_2, priv->vip_cntrl_2);

		priv->is_on = true;
	पूर्ण
पूर्ण

अटल व्योम tda998x_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tda998x_priv *priv = bridge_to_tda998x_priv(bridge);

	अगर (priv->is_on) अणु
		/* disable video ports */
		reg_ग_लिखो(priv, REG_ENA_VP_0, 0x00);
		reg_ग_लिखो(priv, REG_ENA_VP_1, 0x00);
		reg_ग_लिखो(priv, REG_ENA_VP_2, 0x00);

		priv->is_on = false;
	पूर्ण
पूर्ण

अटल व्योम tda998x_bridge_mode_set(काष्ठा drm_bridge *bridge,
				    स्थिर काष्ठा drm_display_mode *mode,
				    स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा tda998x_priv *priv = bridge_to_tda998x_priv(bridge);
	अचिन्हित दीर्घ पंचांगds_घड़ी;
	u16 ref_pix, ref_line, n_pix, n_line;
	u16 hs_pix_s, hs_pix_e;
	u16 vs1_pix_s, vs1_pix_e, vs1_line_s, vs1_line_e;
	u16 vs2_pix_s, vs2_pix_e, vs2_line_s, vs2_line_e;
	u16 vwin1_line_s, vwin1_line_e;
	u16 vwin2_line_s, vwin2_line_e;
	u16 de_pix_s, de_pix_e;
	u8 reg, भाग, rep, sel_clk;

	/*
	 * Since we are "computer" like, our source invariably produces
	 * full-range RGB.  If the monitor supports full-range, then use
	 * it, otherwise reduce to limited-range.
	 */
	priv->rgb_quant_range =
		priv->connector.display_info.rgb_quant_range_selectable ?
		HDMI_QUANTIZATION_RANGE_FULL :
		drm_शेष_rgb_quant_range(adjusted_mode);

	/*
	 * Internally TDA998x is using ITU-R BT.656 style sync but
	 * we get VESA style sync. TDA998x is using a reference pixel
	 * relative to ITU to sync to the input frame and क्रम output
	 * sync generation. Currently, we are using reference detection
	 * from HS/VS, i.e. REFPIX/REFLINE denote frame start sync poपूर्णांक
	 * which is position of rising VS with coincident rising HS.
	 *
	 * Now there is some issues to take care of:
	 * - HDMI data islands require sync-beक्रमe-active
	 * - TDA998x रेजिस्टर values must be > 0 to be enabled
	 * - REFLINE needs an additional offset of +1
	 * - REFPIX needs an addtional offset of +1 क्रम UYUV and +3 क्रम RGB
	 *
	 * So we add +1 to all horizontal and vertical रेजिस्टर values,
	 * plus an additional +3 क्रम REFPIX as we are using RGB input only.
	 */
	n_pix        = mode->htotal;
	n_line       = mode->vtotal;

	hs_pix_e     = mode->hsync_end - mode->hdisplay;
	hs_pix_s     = mode->hsync_start - mode->hdisplay;
	de_pix_e     = mode->htotal;
	de_pix_s     = mode->htotal - mode->hdisplay;
	ref_pix      = 3 + hs_pix_s;

	/*
	 * Attached LCD controllers may generate broken sync. Allow
	 * those to adjust the position of the rising VS edge by adding
	 * HSKEW to ref_pix.
	 */
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_HSKEW)
		ref_pix += adjusted_mode->hskew;

	अगर ((mode->flags & DRM_MODE_FLAG_INTERLACE) == 0) अणु
		ref_line     = 1 + mode->vsync_start - mode->vdisplay;
		vwin1_line_s = mode->vtotal - mode->vdisplay - 1;
		vwin1_line_e = vwin1_line_s + mode->vdisplay;
		vs1_pix_s    = vs1_pix_e = hs_pix_s;
		vs1_line_s   = mode->vsync_start - mode->vdisplay;
		vs1_line_e   = vs1_line_s +
			       mode->vsync_end - mode->vsync_start;
		vwin2_line_s = vwin2_line_e = 0;
		vs2_pix_s    = vs2_pix_e  = 0;
		vs2_line_s   = vs2_line_e = 0;
	पूर्ण अन्यथा अणु
		ref_line     = 1 + (mode->vsync_start - mode->vdisplay)/2;
		vwin1_line_s = (mode->vtotal - mode->vdisplay)/2;
		vwin1_line_e = vwin1_line_s + mode->vdisplay/2;
		vs1_pix_s    = vs1_pix_e = hs_pix_s;
		vs1_line_s   = (mode->vsync_start - mode->vdisplay)/2;
		vs1_line_e   = vs1_line_s +
			       (mode->vsync_end - mode->vsync_start)/2;
		vwin2_line_s = vwin1_line_s + mode->vtotal/2;
		vwin2_line_e = vwin2_line_s + mode->vdisplay/2;
		vs2_pix_s    = vs2_pix_e = hs_pix_s + mode->htotal/2;
		vs2_line_s   = vs1_line_s + mode->vtotal/2 ;
		vs2_line_e   = vs2_line_s +
			       (mode->vsync_end - mode->vsync_start)/2;
	पूर्ण

	/*
	 * Select pixel repeat depending on the द्विगुन-घड़ी flag
	 * (which means we have to repeat each pixel once.)
	 */
	rep = mode->flags & DRM_MODE_FLAG_DBLCLK ? 1 : 0;
	sel_clk = SEL_CLK_ENA_SC_CLK | SEL_CLK_SEL_CLK1 |
		  SEL_CLK_SEL_VRF_CLK(rep ? 2 : 0);

	/* the TMDS घड़ी is scaled up by the pixel repeat */
	पंचांगds_घड़ी = mode->घड़ी * (1 + rep);

	/*
	 * The भागisor is घातer-of-2. The TDA9983B datasheet gives
	 * this as ranges of Msample/s, which is 10x the TMDS घड़ी:
	 *   0 - 800 to 1500 Msample/s
	 *   1 - 400 to 800 Msample/s
	 *   2 - 200 to 400 Msample/s
	 *   3 - as 2 above
	 */
	क्रम (भाग = 0; भाग < 3; भाग++)
		अगर (80000 >> भाग <= पंचांगds_घड़ी)
			अवरोध;

	mutex_lock(&priv->audio_mutex);

	priv->पंचांगds_घड़ी = पंचांगds_घड़ी;

	/* mute the audio FIFO: */
	reg_set(priv, REG_AIP_CNTRL_0, AIP_CNTRL_0_RST_FIFO);

	/* set HDMI HDCP mode off: */
	reg_ग_लिखो(priv, REG_TBG_CNTRL_1, TBG_CNTRL_1_DWIN_DIS);
	reg_clear(priv, REG_TX33, TX33_HDMI);
	reg_ग_लिखो(priv, REG_ENC_CNTRL, ENC_CNTRL_CTL_CODE(0));

	/* no pre-filter or पूर्णांकerpolator: */
	reg_ग_लिखो(priv, REG_HVF_CNTRL_0, HVF_CNTRL_0_PREFIL(0) |
			HVF_CNTRL_0_INTPOL(0));
	reg_set(priv, REG_FEAT_POWERDOWN, FEAT_POWERDOWN_PREFILT);
	reg_ग_लिखो(priv, REG_VIP_CNTRL_5, VIP_CNTRL_5_SP_CNT(0));
	reg_ग_लिखो(priv, REG_VIP_CNTRL_4, VIP_CNTRL_4_BLANKIT(0) |
			VIP_CNTRL_4_BLC(0));

	reg_clear(priv, REG_PLL_SERIAL_1, PLL_SERIAL_1_SRL_MAN_IZ);
	reg_clear(priv, REG_PLL_SERIAL_3, PLL_SERIAL_3_SRL_CCIR |
					  PLL_SERIAL_3_SRL_DE);
	reg_ग_लिखो(priv, REG_SERIALIZER, 0);
	reg_ग_लिखो(priv, REG_HVF_CNTRL_1, HVF_CNTRL_1_VQR(0));

	reg_ग_लिखो(priv, REG_RPT_CNTRL, RPT_CNTRL_REPEAT(rep));
	reg_ग_लिखो(priv, REG_SEL_CLK, sel_clk);
	reg_ग_लिखो(priv, REG_PLL_SERIAL_2, PLL_SERIAL_2_SRL_NOSC(भाग) |
			PLL_SERIAL_2_SRL_PR(rep));

	/* set color matrix according to output rgb quant range */
	अगर (priv->rgb_quant_range == HDMI_QUANTIZATION_RANGE_LIMITED) अणु
		अटल u8 tda998x_full_to_limited_range[] = अणु
			MAT_CONTRL_MAT_SC(2),
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x03, 0x6f, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x03, 0x6f, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x03, 0x6f,
			0x00, 0x40, 0x00, 0x40, 0x00, 0x40
		पूर्ण;
		reg_clear(priv, REG_FEAT_POWERDOWN, FEAT_POWERDOWN_CSC);
		reg_ग_लिखो_range(priv, REG_MAT_CONTRL,
				tda998x_full_to_limited_range,
				माप(tda998x_full_to_limited_range));
	पूर्ण अन्यथा अणु
		reg_ग_लिखो(priv, REG_MAT_CONTRL, MAT_CONTRL_MAT_BP |
					MAT_CONTRL_MAT_SC(1));
		reg_set(priv, REG_FEAT_POWERDOWN, FEAT_POWERDOWN_CSC);
	पूर्ण

	/* set BIAS पंचांगds value: */
	reg_ग_लिखो(priv, REG_ANA_GENERAL, 0x09);

	/*
	 * Sync on rising HSYNC/VSYNC
	 */
	reg = VIP_CNTRL_3_SYNC_HS;

	/*
	 * TDA19988 requires high-active sync at input stage,
	 * so invert low-active sync provided by master encoder here
	 */
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		reg |= VIP_CNTRL_3_H_TGL;
	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		reg |= VIP_CNTRL_3_V_TGL;
	reg_ग_लिखो(priv, REG_VIP_CNTRL_3, reg);

	reg_ग_लिखो(priv, REG_VIDFORMAT, 0x00);
	reg_ग_लिखो16(priv, REG_REFPIX_MSB, ref_pix);
	reg_ग_लिखो16(priv, REG_REFLINE_MSB, ref_line);
	reg_ग_लिखो16(priv, REG_NPIX_MSB, n_pix);
	reg_ग_लिखो16(priv, REG_NLINE_MSB, n_line);
	reg_ग_लिखो16(priv, REG_VS_LINE_STRT_1_MSB, vs1_line_s);
	reg_ग_लिखो16(priv, REG_VS_PIX_STRT_1_MSB, vs1_pix_s);
	reg_ग_लिखो16(priv, REG_VS_LINE_END_1_MSB, vs1_line_e);
	reg_ग_लिखो16(priv, REG_VS_PIX_END_1_MSB, vs1_pix_e);
	reg_ग_लिखो16(priv, REG_VS_LINE_STRT_2_MSB, vs2_line_s);
	reg_ग_लिखो16(priv, REG_VS_PIX_STRT_2_MSB, vs2_pix_s);
	reg_ग_लिखो16(priv, REG_VS_LINE_END_2_MSB, vs2_line_e);
	reg_ग_लिखो16(priv, REG_VS_PIX_END_2_MSB, vs2_pix_e);
	reg_ग_लिखो16(priv, REG_HS_PIX_START_MSB, hs_pix_s);
	reg_ग_लिखो16(priv, REG_HS_PIX_STOP_MSB, hs_pix_e);
	reg_ग_लिखो16(priv, REG_VWIN_START_1_MSB, vwin1_line_s);
	reg_ग_लिखो16(priv, REG_VWIN_END_1_MSB, vwin1_line_e);
	reg_ग_लिखो16(priv, REG_VWIN_START_2_MSB, vwin2_line_s);
	reg_ग_लिखो16(priv, REG_VWIN_END_2_MSB, vwin2_line_e);
	reg_ग_लिखो16(priv, REG_DE_START_MSB, de_pix_s);
	reg_ग_लिखो16(priv, REG_DE_STOP_MSB, de_pix_e);

	अगर (priv->rev == TDA19988) अणु
		/* let incoming pixels fill the active space (अगर any) */
		reg_ग_लिखो(priv, REG_ENABLE_SPACE, 0x00);
	पूर्ण

	/*
	 * Always generate sync polarity relative to input sync and
	 * revert input stage toggled sync at output stage
	 */
	reg = TBG_CNTRL_1_DWIN_DIS | TBG_CNTRL_1_TGL_EN;
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		reg |= TBG_CNTRL_1_H_TGL;
	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		reg |= TBG_CNTRL_1_V_TGL;
	reg_ग_लिखो(priv, REG_TBG_CNTRL_1, reg);

	/* must be last रेजिस्टर set: */
	reg_ग_लिखो(priv, REG_TBG_CNTRL_0, 0);

	/* CEA-861B section 6 says that:
	 * CEA version 1 (CEA-861) has no support क्रम infoframes.
	 * CEA version 2 (CEA-861A) supports version 1 AVI infoframes,
	 * and optional basic audio.
	 * CEA version 3 (CEA-861B) supports version 1 and 2 AVI infoframes,
	 * and optional digital audio, with audio infoframes.
	 *
	 * Since we only support generation of version 2 AVI infoframes,
	 * ignore CEA version 2 and below (iow, behave as अगर we're a
	 * CEA-861 source.)
	 */
	priv->supports_infoframes = priv->connector.display_info.cea_rev >= 3;

	अगर (priv->supports_infoframes) अणु
		/* We need to turn HDMI HDCP stuff on to get audio through */
		reg &= ~TBG_CNTRL_1_DWIN_DIS;
		reg_ग_लिखो(priv, REG_TBG_CNTRL_1, reg);
		reg_ग_लिखो(priv, REG_ENC_CNTRL, ENC_CNTRL_CTL_CODE(1));
		reg_set(priv, REG_TX33, TX33_HDMI);

		tda998x_ग_लिखो_avi(priv, adjusted_mode);
		tda998x_ग_लिखो_vsi(priv, adjusted_mode);

		अगर (priv->sink_has_audio)
			tda998x_configure_audio(priv);
	पूर्ण

	mutex_unlock(&priv->audio_mutex);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs tda998x_bridge_funcs = अणु
	.attach = tda998x_bridge_attach,
	.detach = tda998x_bridge_detach,
	.mode_valid = tda998x_bridge_mode_valid,
	.disable = tda998x_bridge_disable,
	.mode_set = tda998x_bridge_mode_set,
	.enable = tda998x_bridge_enable,
पूर्ण;

/* I2C driver functions */

अटल पूर्णांक tda998x_get_audio_ports(काष्ठा tda998x_priv *priv,
				   काष्ठा device_node *np)
अणु
	स्थिर u32 *port_data;
	u32 size;
	पूर्णांक i;

	port_data = of_get_property(np, "audio-ports", &size);
	अगर (!port_data)
		वापस 0;

	size /= माप(u32);
	अगर (size > 2 * ARRAY_SIZE(priv->audio_port_enable) || size % 2 != 0) अणु
		dev_err(&priv->hdmi->dev,
			"Bad number of elements in audio-ports dt-property\n");
		वापस -EINVAL;
	पूर्ण

	size /= 2;

	क्रम (i = 0; i < size; i++) अणु
		अचिन्हित पूर्णांक route;
		u8 afmt = be32_to_cpup(&port_data[2*i]);
		u8 ena_ap = be32_to_cpup(&port_data[2*i+1]);

		चयन (afmt) अणु
		हाल AFMT_I2S:
			route = AUDIO_ROUTE_I2S;
			अवरोध;
		हाल AFMT_SPDIF:
			route = AUDIO_ROUTE_SPDIF;
			अवरोध;
		शेष:
			dev_err(&priv->hdmi->dev,
				"Bad audio format %u\n", afmt);
			वापस -EINVAL;
		पूर्ण

		अगर (!ena_ap) अणु
			dev_err(&priv->hdmi->dev, "invalid zero port config\n");
			जारी;
		पूर्ण

		अगर (priv->audio_port_enable[route]) अणु
			dev_err(&priv->hdmi->dev,
				"%s format already configured\n",
				route == AUDIO_ROUTE_SPDIF ? "SPDIF" : "I2S");
			वापस -EINVAL;
		पूर्ण

		priv->audio_port_enable[route] = ena_ap;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tda998x_set_config(काष्ठा tda998x_priv *priv,
			      स्थिर काष्ठा tda998x_encoder_params *p)
अणु
	priv->vip_cntrl_0 = VIP_CNTRL_0_SWAP_A(p->swap_a) |
			    (p->mirr_a ? VIP_CNTRL_0_MIRR_A : 0) |
			    VIP_CNTRL_0_SWAP_B(p->swap_b) |
			    (p->mirr_b ? VIP_CNTRL_0_MIRR_B : 0);
	priv->vip_cntrl_1 = VIP_CNTRL_1_SWAP_C(p->swap_c) |
			    (p->mirr_c ? VIP_CNTRL_1_MIRR_C : 0) |
			    VIP_CNTRL_1_SWAP_D(p->swap_d) |
			    (p->mirr_d ? VIP_CNTRL_1_MIRR_D : 0);
	priv->vip_cntrl_2 = VIP_CNTRL_2_SWAP_E(p->swap_e) |
			    (p->mirr_e ? VIP_CNTRL_2_MIRR_E : 0) |
			    VIP_CNTRL_2_SWAP_F(p->swap_f) |
			    (p->mirr_f ? VIP_CNTRL_2_MIRR_F : 0);

	अगर (p->audio_params.क्रमmat != AFMT_UNUSED) अणु
		अचिन्हित पूर्णांक ratio, route;
		bool spdअगर = p->audio_params.क्रमmat == AFMT_SPDIF;

		route = AUDIO_ROUTE_I2S + spdअगर;

		priv->audio.route = &tda998x_audio_route[route];
		priv->audio.cea = p->audio_params.cea;
		priv->audio.sample_rate = p->audio_params.sample_rate;
		स_नकल(priv->audio.status, p->audio_params.status,
		       min(माप(priv->audio.status),
			   माप(p->audio_params.status)));
		priv->audio.ena_ap = p->audio_params.config;
		priv->audio.i2s_क्रमmat = I2S_FORMAT_PHILIPS;

		ratio = spdअगर ? 64 : p->audio_params.sample_width * 2;
		वापस tda998x_derive_cts_n(priv, &priv->audio, ratio);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tda998x_destroy(काष्ठा device *dev)
अणु
	काष्ठा tda998x_priv *priv = dev_get_drvdata(dev);

	drm_bridge_हटाओ(&priv->bridge);

	/* disable all IRQs and मुक्त the IRQ handler */
	cec_ग_लिखो(priv, REG_CEC_RXSHPDINTENA, 0);
	reg_clear(priv, REG_INT_FLAGS_2, INT_FLAGS_2_EDID_BLK_RD);

	अगर (priv->audio_pdev)
		platक्रमm_device_unरेजिस्टर(priv->audio_pdev);

	अगर (priv->hdmi->irq)
		मुक्त_irq(priv->hdmi->irq, priv);

	del_समयr_sync(&priv->edid_delay_समयr);
	cancel_work_sync(&priv->detect_work);

	i2c_unरेजिस्टर_device(priv->cec);

	cec_notअगरier_conn_unरेजिस्टर(priv->cec_notअगरy);
पूर्ण

अटल पूर्णांक tda998x_create(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा device_node *np = client->dev.of_node;
	काष्ठा i2c_board_info cec_info;
	काष्ठा tda998x_priv *priv;
	u32 video;
	पूर्णांक rev_lo, rev_hi, ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(dev, priv);

	mutex_init(&priv->mutex);	/* protect the page access */
	mutex_init(&priv->audio_mutex); /* protect access from audio thपढ़ो */
	mutex_init(&priv->edid_mutex);
	INIT_LIST_HEAD(&priv->bridge.list);
	init_रुकोqueue_head(&priv->edid_delay_रुकोq);
	समयr_setup(&priv->edid_delay_समयr, tda998x_edid_delay_करोne, 0);
	INIT_WORK(&priv->detect_work, tda998x_detect_work);

	priv->vip_cntrl_0 = VIP_CNTRL_0_SWAP_A(2) | VIP_CNTRL_0_SWAP_B(3);
	priv->vip_cntrl_1 = VIP_CNTRL_1_SWAP_C(0) | VIP_CNTRL_1_SWAP_D(1);
	priv->vip_cntrl_2 = VIP_CNTRL_2_SWAP_E(4) | VIP_CNTRL_2_SWAP_F(5);

	/* CEC I2C address bound to TDA998x I2C addr by configuration pins */
	priv->cec_addr = 0x34 + (client->addr & 0x03);
	priv->current_page = 0xff;
	priv->hdmi = client;

	/* wake up the device: */
	cec_ग_लिखो(priv, REG_CEC_ENAMODS,
			CEC_ENAMODS_EN_RXSENS | CEC_ENAMODS_EN_HDMI);

	tda998x_reset(priv);

	/* पढ़ो version: */
	rev_lo = reg_पढ़ो(priv, REG_VERSION_LSB);
	अगर (rev_lo < 0) अणु
		dev_err(dev, "failed to read version: %d\n", rev_lo);
		वापस rev_lo;
	पूर्ण

	rev_hi = reg_पढ़ो(priv, REG_VERSION_MSB);
	अगर (rev_hi < 0) अणु
		dev_err(dev, "failed to read version: %d\n", rev_hi);
		वापस rev_hi;
	पूर्ण

	priv->rev = rev_lo | rev_hi << 8;

	/* mask off feature bits: */
	priv->rev &= ~0x30; /* not-hdcp and not-scalar bit */

	चयन (priv->rev) अणु
	हाल TDA9989N2:
		dev_info(dev, "found TDA9989 n2");
		अवरोध;
	हाल TDA19989:
		dev_info(dev, "found TDA19989");
		अवरोध;
	हाल TDA19989N2:
		dev_info(dev, "found TDA19989 n2");
		अवरोध;
	हाल TDA19988:
		dev_info(dev, "found TDA19988");
		अवरोध;
	शेष:
		dev_err(dev, "found unsupported device: %04x\n", priv->rev);
		वापस -ENXIO;
	पूर्ण

	/* after reset, enable DDC: */
	reg_ग_लिखो(priv, REG_DDC_DISABLE, 0x00);

	/* set घड़ी on DDC channel: */
	reg_ग_लिखो(priv, REG_TX3, 39);

	/* अगर necessary, disable multi-master: */
	अगर (priv->rev == TDA19989)
		reg_set(priv, REG_I2C_MASTER, I2C_MASTER_DIS_MM);

	cec_ग_लिखो(priv, REG_CEC_FRO_IM_CLK_CTRL,
			CEC_FRO_IM_CLK_CTRL_GHOST_DIS | CEC_FRO_IM_CLK_CTRL_IMCLK_SEL);

	/* ensure पूर्णांकerrupts are disabled */
	cec_ग_लिखो(priv, REG_CEC_RXSHPDINTENA, 0);

	/* clear pending पूर्णांकerrupts */
	cec_पढ़ो(priv, REG_CEC_RXSHPDINT);
	reg_पढ़ो(priv, REG_INT_FLAGS_0);
	reg_पढ़ो(priv, REG_INT_FLAGS_1);
	reg_पढ़ो(priv, REG_INT_FLAGS_2);

	/* initialize the optional IRQ */
	अगर (client->irq) अणु
		अचिन्हित दीर्घ irq_flags;

		/* init पढ़ो EDID रुकोqueue and HDP work */
		init_रुकोqueue_head(&priv->wq_edid);

		irq_flags =
			irqd_get_trigger_type(irq_get_irq_data(client->irq));

		priv->cec_glue.irq_flags = irq_flags;

		irq_flags |= IRQF_SHARED | IRQF_ONESHOT;
		ret = request_thपढ़ोed_irq(client->irq, शून्य,
					   tda998x_irq_thपढ़ो, irq_flags,
					   "tda998x", priv);
		अगर (ret) अणु
			dev_err(dev, "failed to request IRQ#%u: %d\n",
				client->irq, ret);
			जाओ err_irq;
		पूर्ण

		/* enable HPD irq */
		cec_ग_लिखो(priv, REG_CEC_RXSHPDINTENA, CEC_RXSHPDLEV_HPD);
	पूर्ण

	priv->cec_notअगरy = cec_notअगरier_conn_रेजिस्टर(dev, शून्य, शून्य);
	अगर (!priv->cec_notअगरy) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	priv->cec_glue.parent = dev;
	priv->cec_glue.data = priv;
	priv->cec_glue.init = tda998x_cec_hook_init;
	priv->cec_glue.निकास = tda998x_cec_hook_निकास;
	priv->cec_glue.खोलो = tda998x_cec_hook_खोलो;
	priv->cec_glue.release = tda998x_cec_hook_release;

	/*
	 * Some TDA998x are actually two I2C devices merged onto one piece
	 * of silicon: TDA9989 and TDA19989 combine the HDMI transmitter
	 * with a slightly modअगरied TDA9950 CEC device.  The CEC device
	 * is at the TDA9950 address, with the address pins strapped across
	 * to the TDA998x address pins.  Hence, it always has the same
	 * offset.
	 */
	स_रखो(&cec_info, 0, माप(cec_info));
	strlcpy(cec_info.type, "tda9950", माप(cec_info.type));
	cec_info.addr = priv->cec_addr;
	cec_info.platक्रमm_data = &priv->cec_glue;
	cec_info.irq = client->irq;

	priv->cec = i2c_new_client_device(client->adapter, &cec_info);
	अगर (IS_ERR(priv->cec)) अणु
		ret = PTR_ERR(priv->cec);
		जाओ fail;
	पूर्ण

	/* enable EDID पढ़ो irq: */
	reg_set(priv, REG_INT_FLAGS_2, INT_FLAGS_2_EDID_BLK_RD);

	अगर (np) अणु
		/* get the device tree parameters */
		ret = of_property_पढ़ो_u32(np, "video-ports", &video);
		अगर (ret == 0) अणु
			priv->vip_cntrl_0 = video >> 16;
			priv->vip_cntrl_1 = video >> 8;
			priv->vip_cntrl_2 = video;
		पूर्ण

		ret = tda998x_get_audio_ports(priv, np);
		अगर (ret)
			जाओ fail;

		अगर (priv->audio_port_enable[AUDIO_ROUTE_I2S] ||
		    priv->audio_port_enable[AUDIO_ROUTE_SPDIF])
			tda998x_audio_codec_init(priv, &client->dev);
	पूर्ण अन्यथा अगर (dev->platक्रमm_data) अणु
		ret = tda998x_set_config(priv, dev->platक्रमm_data);
		अगर (ret)
			जाओ fail;
	पूर्ण

	priv->bridge.funcs = &tda998x_bridge_funcs;
#अगर_घोषित CONFIG_OF
	priv->bridge.of_node = dev->of_node;
#पूर्ण_अगर

	drm_bridge_add(&priv->bridge);

	वापस 0;

fail:
	tda998x_destroy(dev);
err_irq:
	वापस ret;
पूर्ण

/* DRM encoder functions */

अटल पूर्णांक tda998x_encoder_init(काष्ठा device *dev, काष्ठा drm_device *drm)
अणु
	काष्ठा tda998x_priv *priv = dev_get_drvdata(dev);
	u32 crtcs = 0;
	पूर्णांक ret;

	अगर (dev->of_node)
		crtcs = drm_of_find_possible_crtcs(drm, dev->of_node);

	/* If no CRTCs were found, fall back to our old behaviour */
	अगर (crtcs == 0) अणु
		dev_warn(dev, "Falling back to first CRTC\n");
		crtcs = 1 << 0;
	पूर्ण

	priv->encoder.possible_crtcs = crtcs;

	ret = drm_simple_encoder_init(drm, &priv->encoder,
				      DRM_MODE_ENCODER_TMDS);
	अगर (ret)
		जाओ err_encoder;

	ret = drm_bridge_attach(&priv->encoder, &priv->bridge, शून्य, 0);
	अगर (ret)
		जाओ err_bridge;

	वापस 0;

err_bridge:
	drm_encoder_cleanup(&priv->encoder);
err_encoder:
	वापस ret;
पूर्ण

अटल पूर्णांक tda998x_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा drm_device *drm = data;

	वापस tda998x_encoder_init(dev, drm);
पूर्ण

अटल व्योम tda998x_unbind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा tda998x_priv *priv = dev_get_drvdata(dev);

	drm_encoder_cleanup(&priv->encoder);
पूर्ण

अटल स्थिर काष्ठा component_ops tda998x_ops = अणु
	.bind = tda998x_bind,
	.unbind = tda998x_unbind,
पूर्ण;

अटल पूर्णांक
tda998x_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_warn(&client->dev, "adapter does not support I2C\n");
		वापस -EIO;
	पूर्ण

	ret = tda998x_create(&client->dev);
	अगर (ret)
		वापस ret;

	ret = component_add(&client->dev, &tda998x_ops);
	अगर (ret)
		tda998x_destroy(&client->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक tda998x_हटाओ(काष्ठा i2c_client *client)
अणु
	component_del(&client->dev, &tda998x_ops);
	tda998x_destroy(&client->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tda998x_dt_ids[] = अणु
	अणु .compatible = "nxp,tda998x", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tda998x_dt_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id tda998x_ids[] = अणु
	अणु "tda998x", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tda998x_ids);

अटल काष्ठा i2c_driver tda998x_driver = अणु
	.probe = tda998x_probe,
	.हटाओ = tda998x_हटाओ,
	.driver = अणु
		.name = "tda998x",
		.of_match_table = of_match_ptr(tda998x_dt_ids),
	पूर्ण,
	.id_table = tda998x_ids,
पूर्ण;

module_i2c_driver(tda998x_driver);

MODULE_AUTHOR("Rob Clark <robdclark@gmail.com");
MODULE_DESCRIPTION("NXP Semiconductors TDA998X HDMI Encoder");
MODULE_LICENSE("GPL");
