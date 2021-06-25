<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_NPHY_H_
#घोषणा B43_NPHY_H_

#समावेश "phy_common.h"
#समावेश "ppr.h"


/* N-PHY रेजिस्टरs. */

#घोषणा B43_NPHY_BBCFG				B43_PHY_N(0x001) /* BB config */
#घोषणा  B43_NPHY_BBCFG_RSTCCA			0x4000 /* Reset CCA */
#घोषणा  B43_NPHY_BBCFG_RSTRX			0x8000 /* Reset RX */
#घोषणा B43_NPHY_CHANNEL			B43_PHY_N(0x005) /* Channel */
#घोषणा B43_NPHY_TXERR				B43_PHY_N(0x007) /* TX error */
#घोषणा B43_NPHY_BANDCTL			B43_PHY_N(0x009) /* Band control */
#घोषणा  B43_NPHY_BANDCTL_5GHZ			0x0001 /* Use the 5GHz band */
#घोषणा B43_NPHY_4WI_ADDR			B43_PHY_N(0x00B) /* Four-wire bus address */
#घोषणा B43_NPHY_4WI_DATAHI			B43_PHY_N(0x00C) /* Four-wire bus data high */
#घोषणा B43_NPHY_4WI_DATALO			B43_PHY_N(0x00D) /* Four-wire bus data low */
#घोषणा B43_NPHY_BIST_STAT0			B43_PHY_N(0x00E) /* Built-in self test status 0 */
#घोषणा B43_NPHY_BIST_STAT1			B43_PHY_N(0x00F) /* Built-in self test status 1 */

#घोषणा B43_NPHY_C1_DESPWR			B43_PHY_N(0x018) /* Core 1 desired घातer */
#घोषणा B43_NPHY_C1_CCK_DESPWR			B43_PHY_N(0x019) /* Core 1 CCK desired घातer */
#घोषणा B43_NPHY_C1_BCLIPBKOFF			B43_PHY_N(0x01A) /* Core 1 barely clip backoff */
#घोषणा B43_NPHY_C1_CCK_BCLIPBKOFF		B43_PHY_N(0x01B) /* Core 1 CCK barely clip backoff */
#घोषणा B43_NPHY_C1_CGAINI			B43_PHY_N(0x01C) /* Core 1 compute gain info */
#घोषणा  B43_NPHY_C1_CGAINI_GAINBKOFF		0x001F /* Gain backoff */
#घोषणा  B43_NPHY_C1_CGAINI_GAINBKOFF_SHIFT	0
#घोषणा  B43_NPHY_C1_CGAINI_CLIPGBKOFF		0x03E0 /* Clip gain backoff */
#घोषणा  B43_NPHY_C1_CGAINI_CLIPGBKOFF_SHIFT	5
#घोषणा  B43_NPHY_C1_CGAINI_GAINSTEP		0x1C00 /* Gain step */
#घोषणा  B43_NPHY_C1_CGAINI_GAINSTEP_SHIFT	10
#घोषणा  B43_NPHY_C1_CGAINI_CL2DETECT		0x2000 /* Clip 2 detect mask */
#घोषणा B43_NPHY_C1_CCK_CGAINI			B43_PHY_N(0x01D) /* Core 1 CCK compute gain info */
#घोषणा  B43_NPHY_C1_CCK_CGAINI_GAINBKOFF	0x001F /* Gain backoff */
#घोषणा  B43_NPHY_C1_CCK_CGAINI_CLIPGBKOFF	0x01E0 /* CCK barely clip gain backoff */
#घोषणा B43_NPHY_C1_MINMAX_GAIN			B43_PHY_N(0x01E) /* Core 1 min/max gain */
#घोषणा  B43_NPHY_C1_MINGAIN			0x00FF /* Minimum gain */
#घोषणा  B43_NPHY_C1_MINGAIN_SHIFT		0
#घोषणा  B43_NPHY_C1_MAXGAIN			0xFF00 /* Maximum gain */
#घोषणा  B43_NPHY_C1_MAXGAIN_SHIFT		8
#घोषणा B43_NPHY_C1_CCK_MINMAX_GAIN		B43_PHY_N(0x01F) /* Core 1 CCK min/max gain */
#घोषणा  B43_NPHY_C1_CCK_MINGAIN		0x00FF /* Minimum gain */
#घोषणा  B43_NPHY_C1_CCK_MINGAIN_SHIFT		0
#घोषणा  B43_NPHY_C1_CCK_MAXGAIN		0xFF00 /* Maximum gain */
#घोषणा  B43_NPHY_C1_CCK_MAXGAIN_SHIFT		8
#घोषणा B43_NPHY_C1_INITGAIN			B43_PHY_N(0x020) /* Core 1 initial gain code */
#घोषणा  B43_NPHY_C1_INITGAIN_EXTLNA		0x0001 /* External LNA index */
#घोषणा  B43_NPHY_C1_INITGAIN_LNA		0x0006 /* LNA index */
#घोषणा  B43_NPHY_C1_INITGAIN_LNAIDX_SHIFT	1
#घोषणा  B43_NPHY_C1_INITGAIN_HPVGA1		0x0078 /* HPVGA1 index */
#घोषणा  B43_NPHY_C1_INITGAIN_HPVGA1_SHIFT	3
#घोषणा  B43_NPHY_C1_INITGAIN_HPVGA2		0x0F80 /* HPVGA2 index */
#घोषणा  B43_NPHY_C1_INITGAIN_HPVGA2_SHIFT	7
#घोषणा  B43_NPHY_C1_INITGAIN_TRRX		0x1000 /* TR RX index */
#घोषणा  B43_NPHY_C1_INITGAIN_TRTX		0x2000 /* TR TX index */
#घोषणा B43_NPHY_REV3_C1_INITGAIN_A		B43_PHY_N(0x020)
#घोषणा B43_NPHY_C1_CLIP1_HIGAIN		B43_PHY_N(0x021) /* Core 1 clip1 high gain code */
#घोषणा B43_NPHY_REV3_C1_INITGAIN_B		B43_PHY_N(0x021)
#घोषणा B43_NPHY_C1_CLIP1_MEDGAIN		B43_PHY_N(0x022) /* Core 1 clip1 medium gain code */
#घोषणा B43_NPHY_REV3_C1_CLIP_HIGAIN_A		B43_PHY_N(0x022)
#घोषणा B43_NPHY_C1_CLIP1_LOGAIN		B43_PHY_N(0x023) /* Core 1 clip1 low gain code */
#घोषणा B43_NPHY_REV3_C1_CLIP_HIGAIN_B		B43_PHY_N(0x023)
#घोषणा B43_NPHY_C1_CLIP2_GAIN			B43_PHY_N(0x024) /* Core 1 clip2 gain code */
#घोषणा B43_NPHY_REV3_C1_CLIP_MEDGAIN_A		B43_PHY_N(0x024)
#घोषणा B43_NPHY_C1_FILTERGAIN			B43_PHY_N(0x025) /* Core 1 filter gain */
#घोषणा B43_NPHY_C1_LPF_QHPF_BW			B43_PHY_N(0x026) /* Core 1 LPF Q HP F bandwidth */
#घोषणा B43_NPHY_C1_CLIPWBTHRES			B43_PHY_N(0x027) /* Core 1 clip wideband threshold */
#घोषणा  B43_NPHY_C1_CLIPWBTHRES_CLIP2		0x003F /* Clip 2 */
#घोषणा  B43_NPHY_C1_CLIPWBTHRES_CLIP2_SHIFT	0
#घोषणा  B43_NPHY_C1_CLIPWBTHRES_CLIP1		0x0FC0 /* Clip 1 */
#घोषणा  B43_NPHY_C1_CLIPWBTHRES_CLIP1_SHIFT	6
#घोषणा B43_NPHY_C1_W1THRES			B43_PHY_N(0x028) /* Core 1 W1 threshold */
#घोषणा B43_NPHY_C1_EDTHRES			B43_PHY_N(0x029) /* Core 1 ED threshold */
#घोषणा B43_NPHY_C1_SMSIGTHRES			B43_PHY_N(0x02A) /* Core 1 small sig threshold */
#घोषणा B43_NPHY_C1_NBCLIPTHRES			B43_PHY_N(0x02B) /* Core 1 NB clip threshold */
#घोषणा B43_NPHY_C1_CLIP1THRES			B43_PHY_N(0x02C) /* Core 1 clip1 threshold */
#घोषणा B43_NPHY_C1_CLIP2THRES			B43_PHY_N(0x02D) /* Core 1 clip2 threshold */

#घोषणा B43_NPHY_C2_DESPWR			B43_PHY_N(0x02E) /* Core 2 desired घातer */
#घोषणा B43_NPHY_C2_CCK_DESPWR			B43_PHY_N(0x02F) /* Core 2 CCK desired घातer */
#घोषणा B43_NPHY_C2_BCLIPBKOFF			B43_PHY_N(0x030) /* Core 2 barely clip backoff */
#घोषणा B43_NPHY_C2_CCK_BCLIPBKOFF		B43_PHY_N(0x031) /* Core 2 CCK barely clip backoff */
#घोषणा B43_NPHY_C2_CGAINI			B43_PHY_N(0x032) /* Core 2 compute gain info */
#घोषणा  B43_NPHY_C2_CGAINI_GAINBKOFF		0x001F /* Gain backoff */
#घोषणा  B43_NPHY_C2_CGAINI_GAINBKOFF_SHIFT	0
#घोषणा  B43_NPHY_C2_CGAINI_CLIPGBKOFF		0x03E0 /* Clip gain backoff */
#घोषणा  B43_NPHY_C2_CGAINI_CLIPGBKOFF_SHIFT	5
#घोषणा  B43_NPHY_C2_CGAINI_GAINSTEP		0x1C00 /* Gain step */
#घोषणा  B43_NPHY_C2_CGAINI_GAINSTEP_SHIFT	10
#घोषणा  B43_NPHY_C2_CGAINI_CL2DETECT		0x2000 /* Clip 2 detect mask */
#घोषणा B43_NPHY_C2_CCK_CGAINI			B43_PHY_N(0x033) /* Core 2 CCK compute gain info */
#घोषणा  B43_NPHY_C2_CCK_CGAINI_GAINBKOFF	0x001F /* Gain backoff */
#घोषणा  B43_NPHY_C2_CCK_CGAINI_CLIPGBKOFF	0x01E0 /* CCK barely clip gain backoff */
#घोषणा B43_NPHY_C2_MINMAX_GAIN			B43_PHY_N(0x034) /* Core 2 min/max gain */
#घोषणा  B43_NPHY_C2_MINGAIN			0x00FF /* Minimum gain */
#घोषणा  B43_NPHY_C2_MINGAIN_SHIFT		0
#घोषणा  B43_NPHY_C2_MAXGAIN			0xFF00 /* Maximum gain */
#घोषणा  B43_NPHY_C2_MAXGAIN_SHIFT		8
#घोषणा B43_NPHY_C2_CCK_MINMAX_GAIN		B43_PHY_N(0x035) /* Core 2 CCK min/max gain */
#घोषणा  B43_NPHY_C2_CCK_MINGAIN		0x00FF /* Minimum gain */
#घोषणा  B43_NPHY_C2_CCK_MINGAIN_SHIFT		0
#घोषणा  B43_NPHY_C2_CCK_MAXGAIN		0xFF00 /* Maximum gain */
#घोषणा  B43_NPHY_C2_CCK_MAXGAIN_SHIFT		8
#घोषणा B43_NPHY_C2_INITGAIN			B43_PHY_N(0x036) /* Core 2 initial gain code */
#घोषणा  B43_NPHY_C2_INITGAIN_EXTLNA		0x0001 /* External LNA index */
#घोषणा  B43_NPHY_C2_INITGAIN_LNA		0x0006 /* LNA index */
#घोषणा  B43_NPHY_C2_INITGAIN_LNAIDX_SHIFT	1
#घोषणा  B43_NPHY_C2_INITGAIN_HPVGA1		0x0078 /* HPVGA1 index */
#घोषणा  B43_NPHY_C2_INITGAIN_HPVGA1_SHIFT	3
#घोषणा  B43_NPHY_C2_INITGAIN_HPVGA2		0x0F80 /* HPVGA2 index */
#घोषणा  B43_NPHY_C2_INITGAIN_HPVGA2_SHIFT	7
#घोषणा  B43_NPHY_C2_INITGAIN_TRRX		0x1000 /* TR RX index */
#घोषणा  B43_NPHY_C2_INITGAIN_TRTX		0x2000 /* TR TX index */
#घोषणा B43_NPHY_REV3_C1_CLIP_MEDGAIN_B		B43_PHY_N(0x036)
#घोषणा B43_NPHY_C2_CLIP1_HIGAIN		B43_PHY_N(0x037) /* Core 2 clip1 high gain code */
#घोषणा B43_NPHY_REV3_C1_CLIP_LOGAIN_A		B43_PHY_N(0x037)
#घोषणा B43_NPHY_C2_CLIP1_MEDGAIN		B43_PHY_N(0x038) /* Core 2 clip1 medium gain code */
#घोषणा B43_NPHY_REV3_C1_CLIP_LOGAIN_B		B43_PHY_N(0x038)
#घोषणा B43_NPHY_C2_CLIP1_LOGAIN		B43_PHY_N(0x039) /* Core 2 clip1 low gain code */
#घोषणा B43_NPHY_REV3_C1_CLIP2_GAIN_A		B43_PHY_N(0x039)
#घोषणा B43_NPHY_C2_CLIP2_GAIN			B43_PHY_N(0x03A) /* Core 2 clip2 gain code */
#घोषणा B43_NPHY_REV3_C1_CLIP2_GAIN_B		B43_PHY_N(0x03A)
#घोषणा B43_NPHY_C2_FILTERGAIN			B43_PHY_N(0x03B) /* Core 2 filter gain */
#घोषणा B43_NPHY_C2_LPF_QHPF_BW			B43_PHY_N(0x03C) /* Core 2 LPF Q HP F bandwidth */
#घोषणा B43_NPHY_C2_CLIPWBTHRES			B43_PHY_N(0x03D) /* Core 2 clip wideband threshold */
#घोषणा  B43_NPHY_C2_CLIPWBTHRES_CLIP2		0x003F /* Clip 2 */
#घोषणा  B43_NPHY_C2_CLIPWBTHRES_CLIP2_SHIFT	0
#घोषणा  B43_NPHY_C2_CLIPWBTHRES_CLIP1		0x0FC0 /* Clip 1 */
#घोषणा  B43_NPHY_C2_CLIPWBTHRES_CLIP1_SHIFT	6
#घोषणा B43_NPHY_C2_W1THRES			B43_PHY_N(0x03E) /* Core 2 W1 threshold */
#घोषणा B43_NPHY_C2_EDTHRES			B43_PHY_N(0x03F) /* Core 2 ED threshold */
#घोषणा B43_NPHY_C2_SMSIGTHRES			B43_PHY_N(0x040) /* Core 2 small sig threshold */
#घोषणा B43_NPHY_C2_NBCLIPTHRES			B43_PHY_N(0x041) /* Core 2 NB clip threshold */
#घोषणा B43_NPHY_C2_CLIP1THRES			B43_PHY_N(0x042) /* Core 2 clip1 threshold */
#घोषणा B43_NPHY_C2_CLIP2THRES			B43_PHY_N(0x043) /* Core 2 clip2 threshold */

#घोषणा B43_NPHY_CRS_THRES1			B43_PHY_N(0x044) /* CRS threshold 1 */
#घोषणा B43_NPHY_CRS_THRES2			B43_PHY_N(0x045) /* CRS threshold 2 */
#घोषणा B43_NPHY_CRS_THRES3			B43_PHY_N(0x046) /* CRS threshold 3 */
#घोषणा B43_NPHY_CRSCTL				B43_PHY_N(0x047) /* CRS control */
#घोषणा B43_NPHY_DCFADDR			B43_PHY_N(0x048) /* DC filter address */
#घोषणा B43_NPHY_RXF20_NUM0			B43_PHY_N(0x049) /* RX filter 20 numerator 0 */
#घोषणा B43_NPHY_RXF20_NUM1			B43_PHY_N(0x04A) /* RX filter 20 numerator 1 */
#घोषणा B43_NPHY_RXF20_NUM2			B43_PHY_N(0x04B) /* RX filter 20 numerator 2 */
#घोषणा B43_NPHY_RXF20_DENOM0			B43_PHY_N(0x04C) /* RX filter 20 denominator 0 */
#घोषणा B43_NPHY_RXF20_DENOM1			B43_PHY_N(0x04D) /* RX filter 20 denominator 1 */
#घोषणा B43_NPHY_RXF20_NUM10			B43_PHY_N(0x04E) /* RX filter 20 numerator 10 */
#घोषणा B43_NPHY_RXF20_NUM11			B43_PHY_N(0x04F) /* RX filter 20 numerator 11 */
#घोषणा B43_NPHY_RXF20_NUM12			B43_PHY_N(0x050) /* RX filter 20 numerator 12 */
#घोषणा B43_NPHY_RXF20_DENOM10			B43_PHY_N(0x051) /* RX filter 20 denominator 10 */
#घोषणा B43_NPHY_RXF20_DENOM11			B43_PHY_N(0x052) /* RX filter 20 denominator 11 */
#घोषणा B43_NPHY_RXF40_NUM0			B43_PHY_N(0x053) /* RX filter 40 numerator 0 */
#घोषणा B43_NPHY_RXF40_NUM1			B43_PHY_N(0x054) /* RX filter 40 numerator 1 */
#घोषणा B43_NPHY_RXF40_NUM2			B43_PHY_N(0x055) /* RX filter 40 numerator 2 */
#घोषणा B43_NPHY_RXF40_DENOM0			B43_PHY_N(0x056) /* RX filter 40 denominator 0 */
#घोषणा B43_NPHY_RXF40_DENOM1			B43_PHY_N(0x057) /* RX filter 40 denominator 1 */
#घोषणा B43_NPHY_RXF40_NUM10			B43_PHY_N(0x058) /* RX filter 40 numerator 10 */
#घोषणा B43_NPHY_RXF40_NUM11			B43_PHY_N(0x059) /* RX filter 40 numerator 11 */
#घोषणा B43_NPHY_RXF40_NUM12			B43_PHY_N(0x05A) /* RX filter 40 numerator 12 */
#घोषणा B43_NPHY_RXF40_DENOM10			B43_PHY_N(0x05B) /* RX filter 40 denominator 10 */
#घोषणा B43_NPHY_RXF40_DENOM11			B43_PHY_N(0x05C) /* RX filter 40 denominator 11 */
#घोषणा B43_NPHY_PPROC_RSTLEN			B43_PHY_N(0x060) /* Packet processing reset length */
#घोषणा B43_NPHY_INITCARR_DLEN			B43_PHY_N(0x061) /* Initial carrier detection length */
#घोषणा B43_NPHY_CLIP1CARR_DLEN			B43_PHY_N(0x062) /* Clip1 carrier detection length */
#घोषणा B43_NPHY_CLIP2CARR_DLEN			B43_PHY_N(0x063) /* Clip2 carrier detection length */
#घोषणा B43_NPHY_INITGAIN_SLEN			B43_PHY_N(0x064) /* Initial gain settle length */
#घोषणा B43_NPHY_CLIP1GAIN_SLEN			B43_PHY_N(0x065) /* Clip1 gain settle length */
#घोषणा B43_NPHY_CLIP2GAIN_SLEN			B43_PHY_N(0x066) /* Clip2 gain settle length */
#घोषणा B43_NPHY_PACKGAIN_SLEN			B43_PHY_N(0x067) /* Packet gain settle length */
#घोषणा B43_NPHY_CARRSRC_TLEN			B43_PHY_N(0x068) /* Carrier search समयout length */
#घोषणा B43_NPHY_TISRC_TLEN			B43_PHY_N(0x069) /* Timing search समयout length */
#घोषणा B43_NPHY_ENDROP_TLEN			B43_PHY_N(0x06A) /* Energy drop समयout length */
#घोषणा B43_NPHY_CLIP1_NBDWELL_LEN		B43_PHY_N(0x06B) /* Clip1 NB dwell length */
#घोषणा B43_NPHY_CLIP2_NBDWELL_LEN		B43_PHY_N(0x06C) /* Clip2 NB dwell length */
#घोषणा B43_NPHY_W1CLIP1_DWELL_LEN		B43_PHY_N(0x06D) /* W1 clip1 dwell length */
#घोषणा B43_NPHY_W1CLIP2_DWELL_LEN		B43_PHY_N(0x06E) /* W1 clip2 dwell length */
#घोषणा B43_NPHY_W2CLIP1_DWELL_LEN		B43_PHY_N(0x06F) /* W2 clip1 dwell length */
#घोषणा B43_NPHY_PLOAD_CSENSE_EXTLEN		B43_PHY_N(0x070) /* Payload carrier sense extension length */
#घोषणा B43_NPHY_EDROP_CSENSE_EXTLEN		B43_PHY_N(0x071) /* Energy drop carrier sense extension length */
#घोषणा B43_NPHY_TABLE_ADDR			B43_PHY_N(0x072) /* Table address */
#घोषणा B43_NPHY_TABLE_DATALO			B43_PHY_N(0x073) /* Table data low */
#घोषणा B43_NPHY_TABLE_DATAHI			B43_PHY_N(0x074) /* Table data high */
#घोषणा B43_NPHY_WWISE_LENIDX			B43_PHY_N(0x075) /* WWiSE length index */
#घोषणा B43_NPHY_TGNSYNC_LENIDX			B43_PHY_N(0x076) /* TGNsync length index */
#घोषणा B43_NPHY_TXMACIF_HOLDOFF		B43_PHY_N(0x077) /* TX MAC IF Hold off */
#घोषणा B43_NPHY_RFCTL_CMD			B43_PHY_N(0x078) /* RF control (command) */
#घोषणा  B43_NPHY_RFCTL_CMD_START		0x0001 /* Start sequence */
#घोषणा  B43_NPHY_RFCTL_CMD_RXTX		0x0002 /* RX/TX */
#घोषणा  B43_NPHY_RFCTL_CMD_CORESEL		0x0038 /* Core select */
#घोषणा  B43_NPHY_RFCTL_CMD_CORESEL_SHIFT	3
#घोषणा  B43_NPHY_RFCTL_CMD_PORFORCE		0x0040 /* POR क्रमce */
#घोषणा  B43_NPHY_RFCTL_CMD_OEPORFORCE		0x0080 /* OE POR क्रमce */
#घोषणा  B43_NPHY_RFCTL_CMD_RXEN		0x0100 /* RX enable */
#घोषणा  B43_NPHY_RFCTL_CMD_TXEN		0x0200 /* TX enable */
#घोषणा  B43_NPHY_RFCTL_CMD_CHIP0PU		0x0400 /* Chip0 PU */
#घोषणा  B43_NPHY_RFCTL_CMD_EN			0x0800 /* Radio enabled */
#घोषणा  B43_NPHY_RFCTL_CMD_SEQENCORE		0xF000 /* Seq en core */
#घोषणा  B43_NPHY_RFCTL_CMD_SEQENCORE_SHIFT	12
#घोषणा B43_NPHY_RFCTL_RSSIO1			B43_PHY_N(0x07A) /* RF control (RSSI others 1) */
#घोषणा  B43_NPHY_RFCTL_RSSIO1_RXPD		0x0001 /* RX PD */
#घोषणा  B43_NPHY_RFCTL_RSSIO1_TXPD		0x0002 /* TX PD */
#घोषणा  B43_NPHY_RFCTL_RSSIO1_PAPD		0x0004 /* PA PD */
#घोषणा  B43_NPHY_RFCTL_RSSIO1_RSSICTL		0x0030 /* RSSI control */
#घोषणा  B43_NPHY_RFCTL_RSSIO1_LPFBW		0x00C0 /* LPF bandwidth */
#घोषणा  B43_NPHY_RFCTL_RSSIO1_HPFBWHI		0x0100 /* HPF bandwidth high */
#घोषणा  B43_NPHY_RFCTL_RSSIO1_HIQDISCO		0x0200 /* HIQ dis core */
#घोषणा B43_NPHY_RFCTL_RXG1			B43_PHY_N(0x07B) /* RF control (RX gain 1) */
#घोषणा B43_NPHY_RFCTL_TXG1			B43_PHY_N(0x07C) /* RF control (TX gain 1) */
#घोषणा B43_NPHY_RFCTL_RSSIO2			B43_PHY_N(0x07D) /* RF control (RSSI others 2) */
#घोषणा  B43_NPHY_RFCTL_RSSIO2_RXPD		0x0001 /* RX PD */
#घोषणा  B43_NPHY_RFCTL_RSSIO2_TXPD		0x0002 /* TX PD */
#घोषणा  B43_NPHY_RFCTL_RSSIO2_PAPD		0x0004 /* PA PD */
#घोषणा  B43_NPHY_RFCTL_RSSIO2_RSSICTL		0x0030 /* RSSI control */
#घोषणा  B43_NPHY_RFCTL_RSSIO2_LPFBW		0x00C0 /* LPF bandwidth */
#घोषणा  B43_NPHY_RFCTL_RSSIO2_HPFBWHI		0x0100 /* HPF bandwidth high */
#घोषणा  B43_NPHY_RFCTL_RSSIO2_HIQDISCO		0x0200 /* HIQ dis core */
#घोषणा B43_NPHY_RFCTL_RXG2			B43_PHY_N(0x07E) /* RF control (RX gain 2) */
#घोषणा B43_NPHY_RFCTL_TXG2			B43_PHY_N(0x07F) /* RF control (TX gain 2) */
#घोषणा B43_NPHY_RFCTL_RSSIO3			B43_PHY_N(0x080) /* RF control (RSSI others 3) */
#घोषणा  B43_NPHY_RFCTL_RSSIO3_RXPD		0x0001 /* RX PD */
#घोषणा  B43_NPHY_RFCTL_RSSIO3_TXPD		0x0002 /* TX PD */
#घोषणा  B43_NPHY_RFCTL_RSSIO3_PAPD		0x0004 /* PA PD */
#घोषणा  B43_NPHY_RFCTL_RSSIO3_RSSICTL		0x0030 /* RSSI control */
#घोषणा  B43_NPHY_RFCTL_RSSIO3_LPFBW		0x00C0 /* LPF bandwidth */
#घोषणा  B43_NPHY_RFCTL_RSSIO3_HPFBWHI		0x0100 /* HPF bandwidth high */
#घोषणा  B43_NPHY_RFCTL_RSSIO3_HIQDISCO		0x0200 /* HIQ dis core */
#घोषणा B43_NPHY_RFCTL_RXG3			B43_PHY_N(0x081) /* RF control (RX gain 3) */
#घोषणा B43_NPHY_RFCTL_TXG3			B43_PHY_N(0x082) /* RF control (TX gain 3) */
#घोषणा B43_NPHY_RFCTL_RSSIO4			B43_PHY_N(0x083) /* RF control (RSSI others 4) */
#घोषणा  B43_NPHY_RFCTL_RSSIO4_RXPD		0x0001 /* RX PD */
#घोषणा  B43_NPHY_RFCTL_RSSIO4_TXPD		0x0002 /* TX PD */
#घोषणा  B43_NPHY_RFCTL_RSSIO4_PAPD		0x0004 /* PA PD */
#घोषणा  B43_NPHY_RFCTL_RSSIO4_RSSICTL		0x0030 /* RSSI control */
#घोषणा  B43_NPHY_RFCTL_RSSIO4_LPFBW		0x00C0 /* LPF bandwidth */
#घोषणा  B43_NPHY_RFCTL_RSSIO4_HPFBWHI		0x0100 /* HPF bandwidth high */
#घोषणा  B43_NPHY_RFCTL_RSSIO4_HIQDISCO		0x0200 /* HIQ dis core */
#घोषणा B43_NPHY_RFCTL_RXG4			B43_PHY_N(0x084) /* RF control (RX gain 4) */
#घोषणा B43_NPHY_RFCTL_TXG4			B43_PHY_N(0x085) /* RF control (TX gain 4) */
#घोषणा B43_NPHY_C1_TXIQ_COMP_OFF		B43_PHY_N(0x087) /* Core 1 TX I/Q comp offset */
#घोषणा B43_NPHY_C2_TXIQ_COMP_OFF		B43_PHY_N(0x088) /* Core 2 TX I/Q comp offset */
#घोषणा B43_NPHY_C1_TXCTL			B43_PHY_N(0x08B) /* Core 1 TX control */
#घोषणा B43_NPHY_C2_TXCTL			B43_PHY_N(0x08C) /* Core 2 TX control */
#घोषणा B43_NPHY_AFECTL_OVER1			B43_PHY_N(0x08F) /* AFE control override 1 */
#घोषणा B43_NPHY_SCRAM_SIGCTL			B43_PHY_N(0x090) /* Scram संकेत control */
#घोषणा  B43_NPHY_SCRAM_SIGCTL_INITST		0x007F /* Initial state value */
#घोषणा  B43_NPHY_SCRAM_SIGCTL_INITST_SHIFT	0
#घोषणा  B43_NPHY_SCRAM_SIGCTL_SCM		0x0080 /* Scram control mode */
#घोषणा  B43_NPHY_SCRAM_SIGCTL_SICE		0x0100 /* Scram index control enable */
#घोषणा  B43_NPHY_SCRAM_SIGCTL_START		0xFE00 /* Scram start bit */
#घोषणा  B43_NPHY_SCRAM_SIGCTL_START_SHIFT	9
#घोषणा B43_NPHY_RFCTL_INTC1			B43_PHY_N(0x091) /* RF control (पूर्णांकc 1) */
#घोषणा B43_NPHY_RFCTL_INTC2			B43_PHY_N(0x092) /* RF control (पूर्णांकc 2) */
#घोषणा B43_NPHY_RFCTL_INTC3			B43_PHY_N(0x093) /* RF control (पूर्णांकc 3) */
#घोषणा B43_NPHY_RFCTL_INTC4			B43_PHY_N(0x094) /* RF control (पूर्णांकc 4) */
#घोषणा B43_NPHY_NRDTO_WWISE			B43_PHY_N(0x095) /* # datatones WWiSE */
#घोषणा B43_NPHY_NRDTO_TGNSYNC			B43_PHY_N(0x096) /* # datatones TGNsync */
#घोषणा B43_NPHY_SIGFMOD_WWISE			B43_PHY_N(0x097) /* Signal field mod WWiSE */
#घोषणा B43_NPHY_LEG_SIGFMOD_11N		B43_PHY_N(0x098) /* Legacy संकेत field mod 11n */
#घोषणा B43_NPHY_HT_SIGFMOD_11N			B43_PHY_N(0x099) /* HT संकेत field mod 11n */
#घोषणा B43_NPHY_C1_RXIQ_COMPA0			B43_PHY_N(0x09A) /* Core 1 RX I/Q comp A0 */
#घोषणा B43_NPHY_C1_RXIQ_COMPB0			B43_PHY_N(0x09B) /* Core 1 RX I/Q comp B0 */
#घोषणा B43_NPHY_C2_RXIQ_COMPA1			B43_PHY_N(0x09C) /* Core 2 RX I/Q comp A1 */
#घोषणा B43_NPHY_C2_RXIQ_COMPB1			B43_PHY_N(0x09D) /* Core 2 RX I/Q comp B1 */
#घोषणा B43_NPHY_RXCTL				B43_PHY_N(0x0A0) /* RX control */
#घोषणा  B43_NPHY_RXCTL_BSELU20			0x0010 /* Band select upper 20 */
#घोषणा  B43_NPHY_RXCTL_RIFSEN			0x0080 /* RIFS enable */
#घोषणा B43_NPHY_RFSEQMODE			B43_PHY_N(0x0A1) /* RF seq mode */
#घोषणा  B43_NPHY_RFSEQMODE_CAOVER		0x0001 /* Core active override */
#घोषणा  B43_NPHY_RFSEQMODE_TROVER		0x0002 /* Trigger override */
#घोषणा B43_NPHY_RFSEQCA			B43_PHY_N(0x0A2) /* RF seq core active */
#घोषणा  B43_NPHY_RFSEQCA_TXEN			0x000F /* TX enable */
#घोषणा  B43_NPHY_RFSEQCA_TXEN_SHIFT		0
#घोषणा  B43_NPHY_RFSEQCA_RXEN			0x00F0 /* RX enable */
#घोषणा  B43_NPHY_RFSEQCA_RXEN_SHIFT		4
#घोषणा  B43_NPHY_RFSEQCA_TXDIS			0x0F00 /* TX disable */
#घोषणा  B43_NPHY_RFSEQCA_TXDIS_SHIFT		8
#घोषणा  B43_NPHY_RFSEQCA_RXDIS			0xF000 /* RX disable */
#घोषणा  B43_NPHY_RFSEQCA_RXDIS_SHIFT		12
#घोषणा B43_NPHY_RFSEQTR			B43_PHY_N(0x0A3) /* RF seq trigger */
#घोषणा  B43_NPHY_RFSEQTR_RX2TX			0x0001 /* RX2TX */
#घोषणा  B43_NPHY_RFSEQTR_TX2RX			0x0002 /* TX2RX */
#घोषणा  B43_NPHY_RFSEQTR_UPGH			0x0004 /* Update gain H */
#घोषणा  B43_NPHY_RFSEQTR_UPGL			0x0008 /* Update gain L */
#घोषणा  B43_NPHY_RFSEQTR_UPGU			0x0010 /* Update gain U */
#घोषणा  B43_NPHY_RFSEQTR_RST2RX		0x0020 /* Reset to RX */
#घोषणा B43_NPHY_RFSEQST			B43_PHY_N(0x0A4) /* RF seq status. Values same as trigger. */
#घोषणा B43_NPHY_AFECTL_OVER			B43_PHY_N(0x0A5) /* AFE control override */
#घोषणा B43_NPHY_AFECTL_C1			B43_PHY_N(0x0A6) /* AFE control core 1 */
#घोषणा B43_NPHY_AFECTL_C2			B43_PHY_N(0x0A7) /* AFE control core 2 */
#घोषणा B43_NPHY_AFECTL_C3			B43_PHY_N(0x0A8) /* AFE control core 3 */
#घोषणा B43_NPHY_AFECTL_C4			B43_PHY_N(0x0A9) /* AFE control core 4 */
#घोषणा B43_NPHY_AFECTL_DACGAIN1		B43_PHY_N(0x0AA) /* AFE control DAC gain 1 */
#घोषणा B43_NPHY_AFECTL_DACGAIN2		B43_PHY_N(0x0AB) /* AFE control DAC gain 2 */
#घोषणा B43_NPHY_AFECTL_DACGAIN3		B43_PHY_N(0x0AC) /* AFE control DAC gain 3 */
#घोषणा B43_NPHY_AFECTL_DACGAIN4		B43_PHY_N(0x0AD) /* AFE control DAC gain 4 */
#घोषणा B43_NPHY_STR_ADDR1			B43_PHY_N(0x0AE) /* STR address 1 */
#घोषणा B43_NPHY_STR_ADDR2			B43_PHY_N(0x0AF) /* STR address 2 */
#घोषणा B43_NPHY_CLASSCTL			B43_PHY_N(0x0B0) /* Classअगरier control */
#घोषणा  B43_NPHY_CLASSCTL_CCKEN		0x0001 /* CCK enable */
#घोषणा  B43_NPHY_CLASSCTL_OFDMEN		0x0002 /* OFDM enable */
#घोषणा  B43_NPHY_CLASSCTL_WAITEDEN		0x0004 /* Waited enable */
#घोषणा B43_NPHY_IQFLIP				B43_PHY_N(0x0B1) /* I/Q flip */
#घोषणा  B43_NPHY_IQFLIP_ADC1			0x0001 /* ADC1 */
#घोषणा  B43_NPHY_IQFLIP_ADC2			0x0010 /* ADC2 */
#घोषणा B43_NPHY_SISO_SNR_THRES			B43_PHY_N(0x0B2) /* SISO SNR threshold */
#घोषणा B43_NPHY_SIGMA_N_MULT			B43_PHY_N(0x0B3) /* Sigma N multiplier */
#घोषणा B43_NPHY_TXMACDELAY			B43_PHY_N(0x0B4) /* TX MAC delay */
#घोषणा B43_NPHY_TXFRAMEDELAY			B43_PHY_N(0x0B5) /* TX frame delay */
#घोषणा B43_NPHY_MLPARM				B43_PHY_N(0x0B6) /* ML parameters */
#घोषणा B43_NPHY_MLCTL				B43_PHY_N(0x0B7) /* ML control */
#घोषणा B43_NPHY_WWISE_20NCYCDAT		B43_PHY_N(0x0B8) /* WWiSE 20 N cyc data */
#घोषणा B43_NPHY_WWISE_40NCYCDAT		B43_PHY_N(0x0B9) /* WWiSE 40 N cyc data */
#घोषणा B43_NPHY_TGNSYNC_20NCYCDAT		B43_PHY_N(0x0BA) /* TGNsync 20 N cyc data */
#घोषणा B43_NPHY_TGNSYNC_40NCYCDAT		B43_PHY_N(0x0BB) /* TGNsync 40 N cyc data */
#घोषणा B43_NPHY_INITSWIZP			B43_PHY_N(0x0BC) /* Initial swizzle pattern */
#घोषणा B43_NPHY_TXTAILCNT			B43_PHY_N(0x0BD) /* TX tail count value */
#घोषणा B43_NPHY_BPHY_CTL1			B43_PHY_N(0x0BE) /* B PHY control 1 */
#घोषणा B43_NPHY_BPHY_CTL2			B43_PHY_N(0x0BF) /* B PHY control 2 */
#घोषणा  B43_NPHY_BPHY_CTL2_LUT			0x001F /* LUT index */
#घोषणा  B43_NPHY_BPHY_CTL2_LUT_SHIFT		0
#घोषणा  B43_NPHY_BPHY_CTL2_MACDEL		0x7FE0 /* MAC delay */
#घोषणा  B43_NPHY_BPHY_CTL2_MACDEL_SHIFT	5
#घोषणा B43_NPHY_IQLOCAL_CMD			B43_PHY_N(0x0C0) /* I/Q LO cal command */
#घोषणा  B43_NPHY_IQLOCAL_CMD_EN		0x8000
#घोषणा B43_NPHY_IQLOCAL_CMDNNUM		B43_PHY_N(0x0C1) /* I/Q LO cal command N num */
#घोषणा B43_NPHY_IQLOCAL_CMDGCTL		B43_PHY_N(0x0C2) /* I/Q LO cal command G control */
#घोषणा B43_NPHY_SAMP_CMD			B43_PHY_N(0x0C3) /* Sample command */
#घोषणा  B43_NPHY_SAMP_CMD_STOP			0x0002 /* Stop */
#घोषणा B43_NPHY_SAMP_LOOPCNT			B43_PHY_N(0x0C4) /* Sample loop count */
#घोषणा B43_NPHY_SAMP_WAITCNT			B43_PHY_N(0x0C5) /* Sample रुको count */
#घोषणा B43_NPHY_SAMP_DEPCNT			B43_PHY_N(0x0C6) /* Sample depth count */
#घोषणा B43_NPHY_SAMP_STAT			B43_PHY_N(0x0C7) /* Sample status */
#घोषणा B43_NPHY_GPIO_LOOEN			B43_PHY_N(0x0C8) /* GPIO low out enable */
#घोषणा B43_NPHY_GPIO_HIOEN			B43_PHY_N(0x0C9) /* GPIO high out enable */
#घोषणा B43_NPHY_GPIO_SEL			B43_PHY_N(0x0CA) /* GPIO select */
#घोषणा B43_NPHY_GPIO_CLKCTL			B43_PHY_N(0x0CB) /* GPIO घड़ी control */
#घोषणा B43_NPHY_TXF_20CO_AS0			B43_PHY_N(0x0CC) /* TX filter 20 coeff A stage 0 */
#घोषणा B43_NPHY_TXF_20CO_AS1			B43_PHY_N(0x0CD) /* TX filter 20 coeff A stage 1 */
#घोषणा B43_NPHY_TXF_20CO_AS2			B43_PHY_N(0x0CE) /* TX filter 20 coeff A stage 2 */
#घोषणा B43_NPHY_TXF_20CO_B32S0			B43_PHY_N(0x0CF) /* TX filter 20 coeff B32 stage 0 */
#घोषणा B43_NPHY_TXF_20CO_B1S0			B43_PHY_N(0x0D0) /* TX filter 20 coeff B1 stage 0 */
#घोषणा B43_NPHY_TXF_20CO_B32S1			B43_PHY_N(0x0D1) /* TX filter 20 coeff B32 stage 1 */
#घोषणा B43_NPHY_TXF_20CO_B1S1			B43_PHY_N(0x0D2) /* TX filter 20 coeff B1 stage 1 */
#घोषणा B43_NPHY_TXF_20CO_B32S2			B43_PHY_N(0x0D3) /* TX filter 20 coeff B32 stage 2 */
#घोषणा B43_NPHY_TXF_20CO_B1S2			B43_PHY_N(0x0D4) /* TX filter 20 coeff B1 stage 2 */
#घोषणा B43_NPHY_SIGFLDTOL			B43_PHY_N(0x0D5) /* Signal fld tolerance */
#घोषणा B43_NPHY_TXSERFLD			B43_PHY_N(0x0D6) /* TX service field */
#घोषणा B43_NPHY_AFESEQ_RX2TX_PUD		B43_PHY_N(0x0D7) /* AFE seq RX2TX घातer up/करोwn delay */
#घोषणा B43_NPHY_AFESEQ_TX2RX_PUD		B43_PHY_N(0x0D8) /* AFE seq TX2RX घातer up/करोwn delay */
#घोषणा B43_NPHY_TGNSYNC_SCRAMI0		B43_PHY_N(0x0D9) /* TGNsync scram init 0 */
#घोषणा B43_NPHY_TGNSYNC_SCRAMI1		B43_PHY_N(0x0DA) /* TGNsync scram init 1 */
#घोषणा B43_NPHY_INITSWIZPATTLEG		B43_PHY_N(0x0DB) /* Initial swizzle pattern leg */
#घोषणा B43_NPHY_BPHY_CTL3			B43_PHY_N(0x0DC) /* B PHY control 3 */
#घोषणा  B43_NPHY_BPHY_CTL3_SCALE		0x00FF /* Scale */
#घोषणा  B43_NPHY_BPHY_CTL3_SCALE_SHIFT		0
#घोषणा  B43_NPHY_BPHY_CTL3_FSC			0xFF00 /* Frame start count value */
#घोषणा  B43_NPHY_BPHY_CTL3_FSC_SHIFT		8
#घोषणा B43_NPHY_BPHY_CTL4			B43_PHY_N(0x0DD) /* B PHY control 4 */
#घोषणा B43_NPHY_C1_TXBBMULT			B43_PHY_N(0x0DE) /* Core 1 TX BB multiplier */
#घोषणा B43_NPHY_C2_TXBBMULT			B43_PHY_N(0x0DF) /* Core 2 TX BB multiplier */
#घोषणा B43_NPHY_TXF_40CO_AS0			B43_PHY_N(0x0E1) /* TX filter 40 coeff A stage 0 */
#घोषणा B43_NPHY_TXF_40CO_AS1			B43_PHY_N(0x0E2) /* TX filter 40 coeff A stage 1 */
#घोषणा B43_NPHY_TXF_40CO_AS2			B43_PHY_N(0x0E3) /* TX filter 40 coeff A stage 2 */
#घोषणा B43_NPHY_TXF_40CO_B32S0			B43_PHY_N(0x0E4) /* TX filter 40 coeff B32 stage 0 */
#घोषणा B43_NPHY_TXF_40CO_B1S0			B43_PHY_N(0x0E5) /* TX filter 40 coeff B1 stage 0 */
#घोषणा B43_NPHY_TXF_40CO_B32S1			B43_PHY_N(0x0E6) /* TX filter 40 coeff B32 stage 1 */
#घोषणा B43_NPHY_TXF_40CO_B1S1			B43_PHY_N(0x0E7) /* TX filter 40 coeff B1 stage 1 */
#घोषणा B43_NPHY_REV3_RFCTL_OVER0		B43_PHY_N(0x0E7)
#घोषणा B43_NPHY_TXF_40CO_B32S2			B43_PHY_N(0x0E8) /* TX filter 40 coeff B32 stage 2 */
#घोषणा B43_NPHY_TXF_40CO_B1S2			B43_PHY_N(0x0E9) /* TX filter 40 coeff B1 stage 2 */
#घोषणा B43_NPHY_BIST_STAT2			B43_PHY_N(0x0EA) /* BIST status 2 */
#घोषणा B43_NPHY_BIST_STAT3			B43_PHY_N(0x0EB) /* BIST status 3 */
#घोषणा B43_NPHY_RFCTL_OVER			B43_PHY_N(0x0EC) /* RF control override */
#घोषणा B43_NPHY_REV3_RFCTL_OVER1		B43_PHY_N(0x0EC)
#घोषणा B43_NPHY_MIMOCFG			B43_PHY_N(0x0ED) /* MIMO config */
#घोषणा  B43_NPHY_MIMOCFG_GFMIX			0x0004 /* Greenfield or mixed mode */
#घोषणा  B43_NPHY_MIMOCFG_AUTO			0x0100 /* Greenfield/mixed mode स्वतः */
#घोषणा B43_NPHY_RADAR_BLNKCTL			B43_PHY_N(0x0EE) /* Radar blank control */
#घोषणा B43_NPHY_A0RADAR_FIFOCTL		B43_PHY_N(0x0EF) /* Antenna 0 radar FIFO control */
#घोषणा B43_NPHY_A1RADAR_FIFOCTL		B43_PHY_N(0x0F0) /* Antenna 1 radar FIFO control */
#घोषणा B43_NPHY_A0RADAR_FIFODAT		B43_PHY_N(0x0F1) /* Antenna 0 radar FIFO data */
#घोषणा B43_NPHY_A1RADAR_FIFODAT		B43_PHY_N(0x0F2) /* Antenna 1 radar FIFO data */
#घोषणा B43_NPHY_RADAR_THRES0			B43_PHY_N(0x0F3) /* Radar threshold 0 */
#घोषणा B43_NPHY_RADAR_THRES1			B43_PHY_N(0x0F4) /* Radar threshold 1 */
#घोषणा B43_NPHY_RADAR_THRES0R			B43_PHY_N(0x0F5) /* Radar threshold 0R */
#घोषणा B43_NPHY_RADAR_THRES1R			B43_PHY_N(0x0F6) /* Radar threshold 1R */
#घोषणा B43_NPHY_CSEN_20IN40_DLEN		B43_PHY_N(0x0F7) /* Carrier sense 20 in 40 dwell length */
#घोषणा B43_NPHY_RFCTL_LUT_TRSW_LO1		B43_PHY_N(0x0F8) /* RF control LUT TRSW lower 1 */
#घोषणा B43_NPHY_RFCTL_LUT_TRSW_UP1		B43_PHY_N(0x0F9) /* RF control LUT TRSW upper 1 */
#घोषणा B43_NPHY_RFCTL_LUT_TRSW_LO2		B43_PHY_N(0x0FA) /* RF control LUT TRSW lower 2 */
#घोषणा B43_NPHY_RFCTL_LUT_TRSW_UP2		B43_PHY_N(0x0FB) /* RF control LUT TRSW upper 2 */
#घोषणा B43_NPHY_RFCTL_LUT_TRSW_LO3		B43_PHY_N(0x0FC) /* RF control LUT TRSW lower 3 */
#घोषणा B43_NPHY_RFCTL_LUT_TRSW_UP3		B43_PHY_N(0x0FD) /* RF control LUT TRSW upper 3 */
#घोषणा B43_NPHY_RFCTL_LUT_TRSW_LO4		B43_PHY_N(0x0FE) /* RF control LUT TRSW lower 4 */
#घोषणा B43_NPHY_RFCTL_LUT_TRSW_UP4		B43_PHY_N(0x0FF) /* RF control LUT TRSW upper 4 */
#घोषणा B43_NPHY_RFCTL_LUT_LNAPA1		B43_PHY_N(0x100) /* RF control LUT LNA PA 1 */
#घोषणा B43_NPHY_RFCTL_LUT_LNAPA2		B43_PHY_N(0x101) /* RF control LUT LNA PA 2 */
#घोषणा B43_NPHY_RFCTL_LUT_LNAPA3		B43_PHY_N(0x102) /* RF control LUT LNA PA 3 */
#घोषणा B43_NPHY_RFCTL_LUT_LNAPA4		B43_PHY_N(0x103) /* RF control LUT LNA PA 4 */
#घोषणा B43_NPHY_TGNSYNC_CRCM0			B43_PHY_N(0x104) /* TGNsync CRC mask 0 */
#घोषणा B43_NPHY_TGNSYNC_CRCM1			B43_PHY_N(0x105) /* TGNsync CRC mask 1 */
#घोषणा B43_NPHY_TGNSYNC_CRCM2			B43_PHY_N(0x106) /* TGNsync CRC mask 2 */
#घोषणा B43_NPHY_TGNSYNC_CRCM3			B43_PHY_N(0x107) /* TGNsync CRC mask 3 */
#घोषणा B43_NPHY_TGNSYNC_CRCM4			B43_PHY_N(0x108) /* TGNsync CRC mask 4 */
#घोषणा B43_NPHY_CRCPOLY			B43_PHY_N(0x109) /* CRC polynomial */
#घोषणा B43_NPHY_SIGCNT				B43_PHY_N(0x10A) /* # sig count */
#घोषणा B43_NPHY_SIGSTARTBIT_CTL		B43_PHY_N(0x10B) /* Sig start bit control */
#घोषणा B43_NPHY_CRCPOLY_ORDER			B43_PHY_N(0x10C) /* CRC polynomial order */
#घोषणा B43_NPHY_RFCTL_CST0			B43_PHY_N(0x10D) /* RF control core swap table 0 */
#घोषणा B43_NPHY_RFCTL_CST1			B43_PHY_N(0x10E) /* RF control core swap table 1 */
#घोषणा B43_NPHY_RFCTL_CST2O			B43_PHY_N(0x10F) /* RF control core swap table 2 + others */
#घोषणा B43_NPHY_BPHY_CTL5			B43_PHY_N(0x111) /* B PHY control 5 */
#घोषणा B43_NPHY_RFSEQ_LPFBW			B43_PHY_N(0x112) /* RF seq LPF bandwidth */
#घोषणा B43_NPHY_TSSIBIAS1			B43_PHY_N(0x114) /* TSSI bias val 1 */
#घोषणा B43_NPHY_TSSIBIAS2			B43_PHY_N(0x115) /* TSSI bias val 2 */
#घोषणा  B43_NPHY_TSSIBIAS_BIAS			0x00FF /* Bias */
#घोषणा  B43_NPHY_TSSIBIAS_BIAS_SHIFT		0
#घोषणा  B43_NPHY_TSSIBIAS_VAL			0xFF00 /* Value */
#घोषणा  B43_NPHY_TSSIBIAS_VAL_SHIFT		8
#घोषणा B43_NPHY_ESTPWR1			B43_PHY_N(0x118) /* Estimated घातer 1 */
#घोषणा B43_NPHY_ESTPWR2			B43_PHY_N(0x119) /* Estimated घातer 2 */
#घोषणा  B43_NPHY_ESTPWR_PWR			0x00FF /* Estimated घातer */
#घोषणा  B43_NPHY_ESTPWR_PWR_SHIFT		0
#घोषणा  B43_NPHY_ESTPWR_VALID			0x0100 /* Estimated घातer valid */
#घोषणा B43_NPHY_TSSI_MAXTXFDT			B43_PHY_N(0x11C) /* TSSI max TX frame delay समय */
#घोषणा  B43_NPHY_TSSI_MAXTXFDT_VAL		0x00FF /* max TX frame delay समय */
#घोषणा  B43_NPHY_TSSI_MAXTXFDT_VAL_SHIFT	0
#घोषणा B43_NPHY_TSSI_MAXTDT			B43_PHY_N(0x11D) /* TSSI max TSSI delay समय */
#घोषणा  B43_NPHY_TSSI_MAXTDT_VAL		0x00FF /* max TSSI delay समय */
#घोषणा  B43_NPHY_TSSI_MAXTDT_VAL_SHIFT		0
#घोषणा B43_NPHY_ITSSI1				B43_PHY_N(0x11E) /* TSSI idle 1 */
#घोषणा B43_NPHY_ITSSI2				B43_PHY_N(0x11F) /* TSSI idle 2 */
#घोषणा  B43_NPHY_ITSSI_VAL			0x00FF /* Idle TSSI */
#घोषणा  B43_NPHY_ITSSI_VAL_SHIFT		0
#घोषणा B43_NPHY_TSSIMODE			B43_PHY_N(0x122) /* TSSI mode */
#घोषणा  B43_NPHY_TSSIMODE_EN			0x0001 /* TSSI enable */
#घोषणा  B43_NPHY_TSSIMODE_PDEN			0x0002 /* Power det enable */
#घोषणा B43_NPHY_RXMACIFM			B43_PHY_N(0x123) /* RX Macअगर mode */
#घोषणा B43_NPHY_CRSIT_COCNT_LO			B43_PHY_N(0x124) /* CRS idle समय CRS-on count (low) */
#घोषणा B43_NPHY_CRSIT_COCNT_HI			B43_PHY_N(0x125) /* CRS idle समय CRS-on count (high) */
#घोषणा B43_NPHY_CRSIT_MTCNT_LO			B43_PHY_N(0x126) /* CRS idle समय measure समय count (low) */
#घोषणा B43_NPHY_CRSIT_MTCNT_HI			B43_PHY_N(0x127) /* CRS idle समय measure समय count (high) */
#घोषणा B43_NPHY_SAMTWC				B43_PHY_N(0x128) /* Sample tail रुको count */
#घोषणा B43_NPHY_IQEST_CMD			B43_PHY_N(0x129) /* I/Q estimate command */
#घोषणा  B43_NPHY_IQEST_CMD_START		0x0001 /* Start */
#घोषणा  B43_NPHY_IQEST_CMD_MODE		0x0002 /* Mode */
#घोषणा B43_NPHY_IQEST_WT			B43_PHY_N(0x12A) /* I/Q estimate रुको समय */
#घोषणा  B43_NPHY_IQEST_WT_VAL			0x00FF /* Wait समय */
#घोषणा  B43_NPHY_IQEST_WT_VAL_SHIFT		0
#घोषणा B43_NPHY_IQEST_SAMCNT			B43_PHY_N(0x12B) /* I/Q estimate sample count */
#घोषणा B43_NPHY_IQEST_IQACC_LO0		B43_PHY_N(0x12C) /* I/Q estimate I/Q acc lo 0 */
#घोषणा B43_NPHY_IQEST_IQACC_HI0		B43_PHY_N(0x12D) /* I/Q estimate I/Q acc hi 0 */
#घोषणा B43_NPHY_IQEST_IPACC_LO0		B43_PHY_N(0x12E) /* I/Q estimate I घातer acc lo 0 */
#घोषणा B43_NPHY_IQEST_IPACC_HI0		B43_PHY_N(0x12F) /* I/Q estimate I घातer acc hi 0 */
#घोषणा B43_NPHY_IQEST_QPACC_LO0		B43_PHY_N(0x130) /* I/Q estimate Q घातer acc lo 0 */
#घोषणा B43_NPHY_IQEST_QPACC_HI0		B43_PHY_N(0x131) /* I/Q estimate Q घातer acc hi 0 */
#घोषणा B43_NPHY_IQEST_IQACC_LO1		B43_PHY_N(0x134) /* I/Q estimate I/Q acc lo 1 */
#घोषणा B43_NPHY_IQEST_IQACC_HI1		B43_PHY_N(0x135) /* I/Q estimate I/Q acc hi 1 */
#घोषणा B43_NPHY_IQEST_IPACC_LO1		B43_PHY_N(0x136) /* I/Q estimate I घातer acc lo 1 */
#घोषणा B43_NPHY_IQEST_IPACC_HI1		B43_PHY_N(0x137) /* I/Q estimate I घातer acc hi 1 */
#घोषणा B43_NPHY_IQEST_QPACC_LO1		B43_PHY_N(0x138) /* I/Q estimate Q घातer acc lo 1 */
#घोषणा B43_NPHY_IQEST_QPACC_HI1		B43_PHY_N(0x139) /* I/Q estimate Q घातer acc hi 1 */
#घोषणा B43_NPHY_MIMO_CRSTXEXT			B43_PHY_N(0x13A) /* MIMO PHY CRS TX extension */
#घोषणा B43_NPHY_PWRDET1			B43_PHY_N(0x13B) /* Power det 1 */
#घोषणा B43_NPHY_PWRDET2			B43_PHY_N(0x13C) /* Power det 2 */
#घोषणा B43_NPHY_MAXRSSI_DTIME			B43_PHY_N(0x13F) /* RSSI max RSSI delay समय */
#घोषणा B43_NPHY_PIL_DW0			B43_PHY_N(0x141) /* Pilot data weight 0 */
#घोषणा B43_NPHY_PIL_DW1			B43_PHY_N(0x142) /* Pilot data weight 1 */
#घोषणा B43_NPHY_PIL_DW2			B43_PHY_N(0x143) /* Pilot data weight 2 */
#घोषणा  B43_NPHY_PIL_DW_BPSK			0x000F /* BPSK */
#घोषणा  B43_NPHY_PIL_DW_BPSK_SHIFT		0
#घोषणा  B43_NPHY_PIL_DW_QPSK			0x00F0 /* QPSK */
#घोषणा  B43_NPHY_PIL_DW_QPSK_SHIFT		4
#घोषणा  B43_NPHY_PIL_DW_16QAM			0x0F00 /* 16-QAM */
#घोषणा  B43_NPHY_PIL_DW_16QAM_SHIFT		8
#घोषणा  B43_NPHY_PIL_DW_64QAM			0xF000 /* 64-QAM */
#घोषणा  B43_NPHY_PIL_DW_64QAM_SHIFT		12
#घोषणा B43_NPHY_FMDEM_CFG			B43_PHY_N(0x144) /* FM demodulation config */
#घोषणा B43_NPHY_PHASETR_A0			B43_PHY_N(0x145) /* Phase track alpha 0 */
#घोषणा B43_NPHY_PHASETR_A1			B43_PHY_N(0x146) /* Phase track alpha 1 */
#घोषणा B43_NPHY_PHASETR_A2			B43_PHY_N(0x147) /* Phase track alpha 2 */
#घोषणा B43_NPHY_PHASETR_B0			B43_PHY_N(0x148) /* Phase track beta 0 */
#घोषणा B43_NPHY_PHASETR_B1			B43_PHY_N(0x149) /* Phase track beta 1 */
#घोषणा B43_NPHY_PHASETR_B2			B43_PHY_N(0x14A) /* Phase track beta 2 */
#घोषणा B43_NPHY_PHASETR_CHG0			B43_PHY_N(0x14B) /* Phase track change 0 */
#घोषणा B43_NPHY_PHASETR_CHG1			B43_PHY_N(0x14C) /* Phase track change 1 */
#घोषणा B43_NPHY_PHASETW_OFF			B43_PHY_N(0x14D) /* Phase track offset */
#घोषणा B43_NPHY_RFCTL_DBG			B43_PHY_N(0x14E) /* RF control debug */
#घोषणा B43_NPHY_CCK_SHIFTB_REF			B43_PHY_N(0x150) /* CCK shअगरtbits reference var */
#घोषणा B43_NPHY_OVER_DGAIN0			B43_PHY_N(0x152) /* Override digital gain 0 */
#घोषणा B43_NPHY_OVER_DGAIN1			B43_PHY_N(0x153) /* Override digital gain 1 */
#घोषणा  B43_NPHY_OVER_DGAIN_FDGV		0x0007 /* Force digital gain value */
#घोषणा  B43_NPHY_OVER_DGAIN_FDGV_SHIFT		0
#घोषणा  B43_NPHY_OVER_DGAIN_FDGEN		0x0008 /* Force digital gain enable */
#घोषणा  B43_NPHY_OVER_DGAIN_CCKDGECV		0xFF00 /* CCK digital gain enable count value */
#घोषणा  B43_NPHY_OVER_DGAIN_CCKDGECV_SHIFT	8
#घोषणा B43_NPHY_BIST_STAT4			B43_PHY_N(0x156) /* BIST status 4 */
#घोषणा B43_NPHY_RADAR_MAL			B43_PHY_N(0x157) /* Radar MA length */
#घोषणा B43_NPHY_RADAR_SRCCTL			B43_PHY_N(0x158) /* Radar search control */
#घोषणा B43_NPHY_VLD_DTSIG			B43_PHY_N(0x159) /* VLD data tones sig */
#घोषणा B43_NPHY_VLD_DTDAT			B43_PHY_N(0x15A) /* VLD data tones data */
#घोषणा B43_NPHY_C1_BPHY_RXIQCA0		B43_PHY_N(0x15B) /* Core 1 B PHY RX I/Q comp A0 */
#घोषणा B43_NPHY_C1_BPHY_RXIQCB0		B43_PHY_N(0x15C) /* Core 1 B PHY RX I/Q comp B0 */
#घोषणा B43_NPHY_C2_BPHY_RXIQCA1		B43_PHY_N(0x15D) /* Core 2 B PHY RX I/Q comp A1 */
#घोषणा B43_NPHY_C2_BPHY_RXIQCB1		B43_PHY_N(0x15E) /* Core 2 B PHY RX I/Q comp B1 */
#घोषणा B43_NPHY_FREQGAIN0			B43_PHY_N(0x160) /* Frequency gain 0 */
#घोषणा B43_NPHY_FREQGAIN1			B43_PHY_N(0x161) /* Frequency gain 1 */
#घोषणा B43_NPHY_FREQGAIN2			B43_PHY_N(0x162) /* Frequency gain 2 */
#घोषणा B43_NPHY_FREQGAIN3			B43_PHY_N(0x163) /* Frequency gain 3 */
#घोषणा B43_NPHY_FREQGAIN4			B43_PHY_N(0x164) /* Frequency gain 4 */
#घोषणा B43_NPHY_FREQGAIN5			B43_PHY_N(0x165) /* Frequency gain 5 */
#घोषणा B43_NPHY_FREQGAIN6			B43_PHY_N(0x166) /* Frequency gain 6 */
#घोषणा B43_NPHY_FREQGAIN7			B43_PHY_N(0x167) /* Frequency gain 7 */
#घोषणा B43_NPHY_FREQGAIN_BYPASS		B43_PHY_N(0x168) /* Frequency gain bypass */
#घोषणा B43_NPHY_TRLOSS				B43_PHY_N(0x169) /* TR loss value */
#घोषणा B43_NPHY_C1_ADCCLIP			B43_PHY_N(0x16A) /* Core 1 ADC clip */
#घोषणा B43_NPHY_C2_ADCCLIP			B43_PHY_N(0x16B) /* Core 2 ADC clip */
#घोषणा B43_NPHY_LTRN_OFFGAIN			B43_PHY_N(0x16F) /* LTRN offset gain */
#घोषणा B43_NPHY_LTRN_OFF			B43_PHY_N(0x170) /* LTRN offset */
#घोषणा B43_NPHY_NRDATAT_WWISE20SIG		B43_PHY_N(0x171) /* # data tones WWiSE 20 sig */
#घोषणा B43_NPHY_NRDATAT_WWISE40SIG		B43_PHY_N(0x172) /* # data tones WWiSE 40 sig */
#घोषणा B43_NPHY_NRDATAT_TGNSYNC20SIG		B43_PHY_N(0x173) /* # data tones TGNsync 20 sig */
#घोषणा B43_NPHY_NRDATAT_TGNSYNC40SIG		B43_PHY_N(0x174) /* # data tones TGNsync 40 sig */
#घोषणा B43_NPHY_WWISE_CRCM0			B43_PHY_N(0x175) /* WWiSE CRC mask 0 */
#घोषणा B43_NPHY_WWISE_CRCM1			B43_PHY_N(0x176) /* WWiSE CRC mask 1 */
#घोषणा B43_NPHY_WWISE_CRCM2			B43_PHY_N(0x177) /* WWiSE CRC mask 2 */
#घोषणा B43_NPHY_WWISE_CRCM3			B43_PHY_N(0x178) /* WWiSE CRC mask 3 */
#घोषणा B43_NPHY_WWISE_CRCM4			B43_PHY_N(0x179) /* WWiSE CRC mask 4 */
#घोषणा B43_NPHY_CHANEST_CDDSH			B43_PHY_N(0x17A) /* Channel estimate CDD shअगरt */
#घोषणा B43_NPHY_HTAGC_WCNT			B43_PHY_N(0x17B) /* HT ADC रुको counters */
#घोषणा B43_NPHY_SQPARM				B43_PHY_N(0x17C) /* SQ params */
#घोषणा B43_NPHY_MCSDUP6M			B43_PHY_N(0x17D) /* MCS dup 6M */
#घोषणा B43_NPHY_NDATAT_DUP40			B43_PHY_N(0x17E) /* # data tones dup 40 */
#घोषणा B43_NPHY_DUP40_TGNSYNC_CYCD		B43_PHY_N(0x17F) /* Dup40 TGNsync cycle data */
#घोषणा B43_NPHY_DUP40_GFBL			B43_PHY_N(0x180) /* Dup40 GF क्रमmat BL address */
#घोषणा B43_NPHY_DUP40_BL			B43_PHY_N(0x181) /* Dup40 क्रमmat BL address */
#घोषणा B43_NPHY_LEGDUP_FTA			B43_PHY_N(0x182) /* Legacy dup frm table address */
#घोषणा B43_NPHY_PACPROC_DBG			B43_PHY_N(0x183) /* Packet processing debug */
#घोषणा B43_NPHY_PIL_CYC1			B43_PHY_N(0x184) /* Pilot cycle counter 1 */
#घोषणा B43_NPHY_PIL_CYC2			B43_PHY_N(0x185) /* Pilot cycle counter 2 */
#घोषणा B43_NPHY_TXF_20CO_S0A1			B43_PHY_N(0x186) /* TX filter 20 coeff stage 0 A1 */
#घोषणा B43_NPHY_TXF_20CO_S0A2			B43_PHY_N(0x187) /* TX filter 20 coeff stage 0 A2 */
#घोषणा B43_NPHY_TXF_20CO_S1A1			B43_PHY_N(0x188) /* TX filter 20 coeff stage 1 A1 */
#घोषणा B43_NPHY_TXF_20CO_S1A2			B43_PHY_N(0x189) /* TX filter 20 coeff stage 1 A2 */
#घोषणा B43_NPHY_TXF_20CO_S2A1			B43_PHY_N(0x18A) /* TX filter 20 coeff stage 2 A1 */
#घोषणा B43_NPHY_TXF_20CO_S2A2			B43_PHY_N(0x18B) /* TX filter 20 coeff stage 2 A2 */
#घोषणा B43_NPHY_TXF_20CO_S0B1			B43_PHY_N(0x18C) /* TX filter 20 coeff stage 0 B1 */
#घोषणा B43_NPHY_TXF_20CO_S0B2			B43_PHY_N(0x18D) /* TX filter 20 coeff stage 0 B2 */
#घोषणा B43_NPHY_TXF_20CO_S0B3			B43_PHY_N(0x18E) /* TX filter 20 coeff stage 0 B3 */
#घोषणा B43_NPHY_TXF_20CO_S1B1			B43_PHY_N(0x18F) /* TX filter 20 coeff stage 1 B1 */
#घोषणा B43_NPHY_TXF_20CO_S1B2			B43_PHY_N(0x190) /* TX filter 20 coeff stage 1 B2 */
#घोषणा B43_NPHY_TXF_20CO_S1B3			B43_PHY_N(0x191) /* TX filter 20 coeff stage 1 B3 */
#घोषणा B43_NPHY_TXF_20CO_S2B1			B43_PHY_N(0x192) /* TX filter 20 coeff stage 2 B1 */
#घोषणा B43_NPHY_TXF_20CO_S2B2			B43_PHY_N(0x193) /* TX filter 20 coeff stage 2 B2 */
#घोषणा B43_NPHY_TXF_20CO_S2B3			B43_PHY_N(0x194) /* TX filter 20 coeff stage 2 B3 */
#घोषणा B43_NPHY_TXF_40CO_S0A1			B43_PHY_N(0x195) /* TX filter 40 coeff stage 0 A1 */
#घोषणा B43_NPHY_TXF_40CO_S0A2			B43_PHY_N(0x196) /* TX filter 40 coeff stage 0 A2 */
#घोषणा B43_NPHY_TXF_40CO_S1A1			B43_PHY_N(0x197) /* TX filter 40 coeff stage 1 A1 */
#घोषणा B43_NPHY_TXF_40CO_S1A2			B43_PHY_N(0x198) /* TX filter 40 coeff stage 1 A2 */
#घोषणा B43_NPHY_TXF_40CO_S2A1			B43_PHY_N(0x199) /* TX filter 40 coeff stage 2 A1 */
#घोषणा B43_NPHY_TXF_40CO_S2A2			B43_PHY_N(0x19A) /* TX filter 40 coeff stage 2 A2 */
#घोषणा B43_NPHY_TXF_40CO_S0B1			B43_PHY_N(0x19B) /* TX filter 40 coeff stage 0 B1 */
#घोषणा B43_NPHY_TXF_40CO_S0B2			B43_PHY_N(0x19C) /* TX filter 40 coeff stage 0 B2 */
#घोषणा B43_NPHY_TXF_40CO_S0B3			B43_PHY_N(0x19D) /* TX filter 40 coeff stage 0 B3 */
#घोषणा B43_NPHY_TXF_40CO_S1B1			B43_PHY_N(0x19E) /* TX filter 40 coeff stage 1 B1 */
#घोषणा B43_NPHY_TXF_40CO_S1B2			B43_PHY_N(0x19F) /* TX filter 40 coeff stage 1 B2 */
#घोषणा B43_NPHY_TXF_40CO_S1B3			B43_PHY_N(0x1A0) /* TX filter 40 coeff stage 1 B3 */
#घोषणा B43_NPHY_TXF_40CO_S2B1			B43_PHY_N(0x1A1) /* TX filter 40 coeff stage 2 B1 */
#घोषणा B43_NPHY_TXF_40CO_S2B2			B43_PHY_N(0x1A2) /* TX filter 40 coeff stage 2 B2 */
#घोषणा B43_NPHY_TXF_40CO_S2B3			B43_PHY_N(0x1A3) /* TX filter 40 coeff stage 2 B3 */
#घोषणा B43_NPHY_RSSIMC_0I_RSSI_X		B43_PHY_N(0x1A4) /* RSSI multiplication coefficient 0 I RSSI X */
#घोषणा B43_NPHY_RSSIMC_0I_RSSI_Y		B43_PHY_N(0x1A5) /* RSSI multiplication coefficient 0 I RSSI Y */
#घोषणा B43_NPHY_RSSIMC_0I_RSSI_Z		B43_PHY_N(0x1A6) /* RSSI multiplication coefficient 0 I RSSI Z */
#घोषणा B43_NPHY_RSSIMC_0I_TBD			B43_PHY_N(0x1A7) /* RSSI multiplication coefficient 0 I TBD */
#घोषणा B43_NPHY_RSSIMC_0I_PWRDET		B43_PHY_N(0x1A8) /* RSSI multiplication coefficient 0 I घातer det */
#घोषणा B43_NPHY_RSSIMC_0I_TSSI			B43_PHY_N(0x1A9) /* RSSI multiplication coefficient 0 I TSSI */
#घोषणा B43_NPHY_RSSIMC_0Q_RSSI_X		B43_PHY_N(0x1AA) /* RSSI multiplication coefficient 0 Q RSSI X */
#घोषणा B43_NPHY_RSSIMC_0Q_RSSI_Y		B43_PHY_N(0x1AB) /* RSSI multiplication coefficient 0 Q RSSI Y */
#घोषणा B43_NPHY_RSSIMC_0Q_RSSI_Z		B43_PHY_N(0x1AC) /* RSSI multiplication coefficient 0 Q RSSI Z */
#घोषणा B43_NPHY_RSSIMC_0Q_TBD			B43_PHY_N(0x1AD) /* RSSI multiplication coefficient 0 Q TBD */
#घोषणा B43_NPHY_RSSIMC_0Q_PWRDET		B43_PHY_N(0x1AE) /* RSSI multiplication coefficient 0 Q घातer det */
#घोषणा B43_NPHY_RSSIMC_0Q_TSSI			B43_PHY_N(0x1AF) /* RSSI multiplication coefficient 0 Q TSSI */
#घोषणा B43_NPHY_RSSIMC_1I_RSSI_X		B43_PHY_N(0x1B0) /* RSSI multiplication coefficient 1 I RSSI X */
#घोषणा B43_NPHY_RSSIMC_1I_RSSI_Y		B43_PHY_N(0x1B1) /* RSSI multiplication coefficient 1 I RSSI Y */
#घोषणा B43_NPHY_RSSIMC_1I_RSSI_Z		B43_PHY_N(0x1B2) /* RSSI multiplication coefficient 1 I RSSI Z */
#घोषणा B43_NPHY_RSSIMC_1I_TBD			B43_PHY_N(0x1B3) /* RSSI multiplication coefficient 1 I TBD */
#घोषणा B43_NPHY_RSSIMC_1I_PWRDET		B43_PHY_N(0x1B4) /* RSSI multiplication coefficient 1 I घातer det */
#घोषणा B43_NPHY_RSSIMC_1I_TSSI			B43_PHY_N(0x1B5) /* RSSI multiplication coefficient 1 I TSSI */
#घोषणा B43_NPHY_RSSIMC_1Q_RSSI_X		B43_PHY_N(0x1B6) /* RSSI multiplication coefficient 1 Q RSSI X */
#घोषणा B43_NPHY_RSSIMC_1Q_RSSI_Y		B43_PHY_N(0x1B7) /* RSSI multiplication coefficient 1 Q RSSI Y */
#घोषणा B43_NPHY_RSSIMC_1Q_RSSI_Z		B43_PHY_N(0x1B8) /* RSSI multiplication coefficient 1 Q RSSI Z */
#घोषणा B43_NPHY_RSSIMC_1Q_TBD			B43_PHY_N(0x1B9) /* RSSI multiplication coefficient 1 Q TBD */
#घोषणा B43_NPHY_RSSIMC_1Q_PWRDET		B43_PHY_N(0x1BA) /* RSSI multiplication coefficient 1 Q घातer det */
#घोषणा B43_NPHY_RSSIMC_1Q_TSSI			B43_PHY_N(0x1BB) /* RSSI multiplication coefficient 1 Q TSSI */
#घोषणा B43_NPHY_SAMC_WCNT			B43_PHY_N(0x1BC) /* Sample collect रुको counter */
#घोषणा B43_NPHY_PTHROUGH_CNT			B43_PHY_N(0x1BD) /* Pass-through counter */
#घोषणा B43_NPHY_LTRN_OFF_G20L			B43_PHY_N(0x1C4) /* LTRN offset gain 20L */
#घोषणा B43_NPHY_LTRN_OFF_20L			B43_PHY_N(0x1C5) /* LTRN offset 20L */
#घोषणा B43_NPHY_LTRN_OFF_G20U			B43_PHY_N(0x1C6) /* LTRN offset gain 20U */
#घोषणा B43_NPHY_LTRN_OFF_20U			B43_PHY_N(0x1C7) /* LTRN offset 20U */
#घोषणा B43_NPHY_DSSSCCK_GAINSL			B43_PHY_N(0x1C8) /* DSSS/CCK gain settle length */
#घोषणा B43_NPHY_GPIO_LOOUT			B43_PHY_N(0x1C9) /* GPIO low out */
#घोषणा B43_NPHY_GPIO_HIOUT			B43_PHY_N(0x1CA) /* GPIO high out */
#घोषणा B43_NPHY_CRS_CHECK			B43_PHY_N(0x1CB) /* CRS check */
#घोषणा B43_NPHY_ML_LOGSS_RAT			B43_PHY_N(0x1CC) /* ML/logss ratio */
#घोषणा B43_NPHY_DUPSCALE			B43_PHY_N(0x1CD) /* Dup scale */
#घोषणा B43_NPHY_BW1A				B43_PHY_N(0x1CE) /* BW 1A */
#घोषणा B43_NPHY_BW2				B43_PHY_N(0x1CF) /* BW 2 */
#घोषणा B43_NPHY_BW3				B43_PHY_N(0x1D0) /* BW 3 */
#घोषणा B43_NPHY_BW4				B43_PHY_N(0x1D1) /* BW 4 */
#घोषणा B43_NPHY_BW5				B43_PHY_N(0x1D2) /* BW 5 */
#घोषणा B43_NPHY_BW6				B43_PHY_N(0x1D3) /* BW 6 */
#घोषणा B43_NPHY_COALEN0			B43_PHY_N(0x1D4) /* Coarse length 0 */
#घोषणा B43_NPHY_COALEN1			B43_PHY_N(0x1D5) /* Coarse length 1 */
#घोषणा B43_NPHY_CRSTHRES_1U			B43_PHY_N(0x1D6) /* CRS threshold 1 U */
#घोषणा B43_NPHY_CRSTHRES_2U			B43_PHY_N(0x1D7) /* CRS threshold 2 U */
#घोषणा B43_NPHY_CRSTHRES_3U			B43_PHY_N(0x1D8) /* CRS threshold 3 U */
#घोषणा B43_NPHY_CRSCTL_U			B43_PHY_N(0x1D9) /* CRS control U */
#घोषणा B43_NPHY_CRSTHRES_1L			B43_PHY_N(0x1DA) /* CRS threshold 1 L */
#घोषणा B43_NPHY_CRSTHRES_2L			B43_PHY_N(0x1DB) /* CRS threshold 2 L */
#घोषणा B43_NPHY_CRSTHRES_3L			B43_PHY_N(0x1DC) /* CRS threshold 3 L */
#घोषणा B43_NPHY_CRSCTL_L			B43_PHY_N(0x1DD) /* CRS control L */
#घोषणा B43_NPHY_STRA_1U			B43_PHY_N(0x1DE) /* STR address 1 U */
#घोषणा B43_NPHY_STRA_2U			B43_PHY_N(0x1DF) /* STR address 2 U */
#घोषणा B43_NPHY_STRA_1L			B43_PHY_N(0x1E0) /* STR address 1 L */
#घोषणा B43_NPHY_STRA_2L			B43_PHY_N(0x1E1) /* STR address 2 L */
#घोषणा B43_NPHY_CRSCHECK1			B43_PHY_N(0x1E2) /* CRS check 1 */
#घोषणा B43_NPHY_CRSCHECK2			B43_PHY_N(0x1E3) /* CRS check 2 */
#घोषणा B43_NPHY_CRSCHECK3			B43_PHY_N(0x1E4) /* CRS check 3 */
#घोषणा B43_NPHY_JMPSTP0			B43_PHY_N(0x1E5) /* Jump step 0 */
#घोषणा B43_NPHY_JMPSTP1			B43_PHY_N(0x1E6) /* Jump step 1 */
#घोषणा B43_NPHY_TXPCTL_CMD			B43_PHY_N(0x1E7) /* TX घातer control command */
#घोषणा  B43_NPHY_TXPCTL_CMD_INIT		0x007F /* Init */
#घोषणा  B43_NPHY_TXPCTL_CMD_INIT_SHIFT		0
#घोषणा  B43_NPHY_TXPCTL_CMD_COEFF		0x2000 /* Power control coefficients */
#घोषणा  B43_NPHY_TXPCTL_CMD_HWPCTLEN		0x4000 /* Hardware TX घातer control enable */
#घोषणा  B43_NPHY_TXPCTL_CMD_PCTLEN		0x8000 /* TX घातer control enable */
#घोषणा B43_NPHY_TXPCTL_N			B43_PHY_N(0x1E8) /* TX घातer control N num */
#घोषणा  B43_NPHY_TXPCTL_N_TSSID		0x00FF /* N TSSI delay */
#घोषणा  B43_NPHY_TXPCTL_N_TSSID_SHIFT		0
#घोषणा  B43_NPHY_TXPCTL_N_NPTIL2		0x0700 /* N PT पूर्णांकeger log2 */
#घोषणा  B43_NPHY_TXPCTL_N_NPTIL2_SHIFT		8
#घोषणा B43_NPHY_TXPCTL_ITSSI			B43_PHY_N(0x1E9) /* TX घातer control idle TSSI */
#घोषणा  B43_NPHY_TXPCTL_ITSSI_0		0x003F /* Idle TSSI 0 */
#घोषणा  B43_NPHY_TXPCTL_ITSSI_0_SHIFT		0
#घोषणा  B43_NPHY_TXPCTL_ITSSI_1		0x3F00 /* Idle TSSI 1 */
#घोषणा  B43_NPHY_TXPCTL_ITSSI_1_SHIFT		8
#घोषणा  B43_NPHY_TXPCTL_ITSSI_BINF		0x8000 /* Raw TSSI offset bin क्रमmat */
#घोषणा B43_NPHY_TXPCTL_TPWR			B43_PHY_N(0x1EA) /* TX घातer control target घातer */
#घोषणा  B43_NPHY_TXPCTL_TPWR_0			0x00FF /* Power 0 */
#घोषणा  B43_NPHY_TXPCTL_TPWR_0_SHIFT		0
#घोषणा  B43_NPHY_TXPCTL_TPWR_1			0xFF00 /* Power 1 */
#घोषणा  B43_NPHY_TXPCTL_TPWR_1_SHIFT		8
#घोषणा B43_NPHY_TXPCTL_BIDX			B43_PHY_N(0x1EB) /* TX घातer control base index */
#घोषणा  B43_NPHY_TXPCTL_BIDX_0			0x007F /* uC base index 0 */
#घोषणा  B43_NPHY_TXPCTL_BIDX_0_SHIFT		0
#घोषणा  B43_NPHY_TXPCTL_BIDX_1			0x7F00 /* uC base index 1 */
#घोषणा  B43_NPHY_TXPCTL_BIDX_1_SHIFT		8
#घोषणा  B43_NPHY_TXPCTL_BIDX_LOAD		0x8000 /* Load base index */
#घोषणा B43_NPHY_TXPCTL_PIDX			B43_PHY_N(0x1EC) /* TX घातer control घातer index */
#घोषणा  B43_NPHY_TXPCTL_PIDX_0			0x007F /* uC घातer index 0 */
#घोषणा  B43_NPHY_TXPCTL_PIDX_0_SHIFT		0
#घोषणा  B43_NPHY_TXPCTL_PIDX_1			0x7F00 /* uC घातer index 1 */
#घोषणा  B43_NPHY_TXPCTL_PIDX_1_SHIFT		8
#घोषणा B43_NPHY_C1_TXPCTL_STAT			B43_PHY_N(0x1ED) /* Core 1 TX घातer control status */
#घोषणा B43_NPHY_C2_TXPCTL_STAT			B43_PHY_N(0x1EE) /* Core 2 TX घातer control status */
#घोषणा  B43_NPHY_TXPCTL_STAT_EST		0x00FF /* Estimated घातer */
#घोषणा  B43_NPHY_TXPCTL_STAT_EST_SHIFT		0
#घोषणा  B43_NPHY_TXPCTL_STAT_BIDX		0x7F00 /* Base index */
#घोषणा  B43_NPHY_TXPCTL_STAT_BIDX_SHIFT	8
#घोषणा  B43_NPHY_TXPCTL_STAT_ESTVALID		0x8000 /* Estimated घातer valid */
#घोषणा B43_NPHY_SMALLSGS_LEN			B43_PHY_N(0x1EF) /* Small sig gain settle length */
#घोषणा B43_NPHY_PHYSTAT_GAIN0			B43_PHY_N(0x1F0) /* PHY stats gain info 0 */
#घोषणा B43_NPHY_PHYSTAT_GAIN1			B43_PHY_N(0x1F1) /* PHY stats gain info 1 */
#घोषणा B43_NPHY_PHYSTAT_FREQEST		B43_PHY_N(0x1F2) /* PHY stats frequency estimate */
#घोषणा B43_NPHY_PHYSTAT_ADVRET			B43_PHY_N(0x1F3) /* PHY stats ADV retard */
#घोषणा B43_NPHY_PHYLB_MODE			B43_PHY_N(0x1F4) /* PHY loopback mode */
#घोषणा B43_NPHY_TONE_MIDX20_1			B43_PHY_N(0x1F5) /* Tone map index 20/1 */
#घोषणा B43_NPHY_TONE_MIDX20_2			B43_PHY_N(0x1F6) /* Tone map index 20/2 */
#घोषणा B43_NPHY_TONE_MIDX20_3			B43_PHY_N(0x1F7) /* Tone map index 20/3 */
#घोषणा B43_NPHY_TONE_MIDX40_1			B43_PHY_N(0x1F8) /* Tone map index 40/1 */
#घोषणा B43_NPHY_TONE_MIDX40_2			B43_PHY_N(0x1F9) /* Tone map index 40/2 */
#घोषणा B43_NPHY_TONE_MIDX40_3			B43_PHY_N(0x1FA) /* Tone map index 40/3 */
#घोषणा B43_NPHY_TONE_MIDX40_4			B43_PHY_N(0x1FB) /* Tone map index 40/4 */
#घोषणा B43_NPHY_PILTONE_MIDX1			B43_PHY_N(0x1FC) /* Pilot tone map index 1 */
#घोषणा B43_NPHY_PILTONE_MIDX2			B43_PHY_N(0x1FD) /* Pilot tone map index 2 */
#घोषणा B43_NPHY_PILTONE_MIDX3			B43_PHY_N(0x1FE) /* Pilot tone map index 3 */
#घोषणा B43_NPHY_TXRIFS_FRDEL			B43_PHY_N(0x1FF) /* TX RIFS frame delay */
#घोषणा B43_NPHY_AFESEQ_RX2TX_PUD_40M		B43_PHY_N(0x200) /* AFE seq rx2tx घातer up/करोwn delay 40M */
#घोषणा B43_NPHY_AFESEQ_TX2RX_PUD_40M		B43_PHY_N(0x201) /* AFE seq tx2rx घातer up/करोwn delay 40M */
#घोषणा B43_NPHY_AFESEQ_RX2TX_PUD_20M		B43_PHY_N(0x202) /* AFE seq rx2tx घातer up/करोwn delay 20M */
#घोषणा B43_NPHY_AFESEQ_TX2RX_PUD_20M		B43_PHY_N(0x203) /* AFE seq tx2rx घातer up/करोwn delay 20M */
#घोषणा B43_NPHY_RX_SIGCTL			B43_PHY_N(0x204) /* RX संकेत control */
#घोषणा B43_NPHY_RXPIL_CYCNT0			B43_PHY_N(0x205) /* RX pilot cycle counter 0 */
#घोषणा B43_NPHY_RXPIL_CYCNT1			B43_PHY_N(0x206) /* RX pilot cycle counter 1 */
#घोषणा B43_NPHY_RXPIL_CYCNT2			B43_PHY_N(0x207) /* RX pilot cycle counter 2 */
#घोषणा B43_NPHY_AFESEQ_RX2TX_PUD_10M		B43_PHY_N(0x208) /* AFE seq rx2tx घातer up/करोwn delay 10M */
#घोषणा B43_NPHY_AFESEQ_TX2RX_PUD_10M		B43_PHY_N(0x209) /* AFE seq tx2rx घातer up/करोwn delay 10M */
#घोषणा B43_NPHY_DSSSCCK_CRSEXTL		B43_PHY_N(0x20A) /* DSSS/CCK CRS extension length */
#घोषणा B43_NPHY_ML_LOGSS_RATSLOPE		B43_PHY_N(0x20B) /* ML/logss ratio slope */
#घोषणा B43_NPHY_RIFS_SRCTL			B43_PHY_N(0x20C) /* RIFS search समयout length */
#घोषणा B43_NPHY_TXREALFD			B43_PHY_N(0x20D) /* TX real frame delay */
#घोषणा B43_NPHY_HPANT_SWTHRES			B43_PHY_N(0x20E) /* High घातer antenna चयन threshold */
#घोषणा B43_NPHY_EDCRS_ASSTHRES0		B43_PHY_N(0x210) /* ED CRS निश्चित threshold 0 */
#घोषणा B43_NPHY_EDCRS_ASSTHRES1		B43_PHY_N(0x211) /* ED CRS निश्चित threshold 1 */
#घोषणा B43_NPHY_EDCRS_DEASSTHRES0		B43_PHY_N(0x212) /* ED CRS deनिश्चित threshold 0 */
#घोषणा B43_NPHY_EDCRS_DEASSTHRES1		B43_PHY_N(0x213) /* ED CRS deनिश्चित threshold 1 */
#घोषणा B43_NPHY_STR_WTIME20U			B43_PHY_N(0x214) /* STR रुको समय 20U */
#घोषणा B43_NPHY_STR_WTIME20L			B43_PHY_N(0x215) /* STR रुको समय 20L */
#घोषणा B43_NPHY_TONE_MIDX657M			B43_PHY_N(0x216) /* Tone map index 657M */
#घोषणा B43_NPHY_HTSIGTONES			B43_PHY_N(0x217) /* HT संकेत tones */
#घोषणा B43_NPHY_RSSI1				B43_PHY_N(0x219) /* RSSI value 1 */
#घोषणा B43_NPHY_RSSI2				B43_PHY_N(0x21A) /* RSSI value 2 */
#घोषणा B43_NPHY_CHAN_ESTHANG			B43_PHY_N(0x21D) /* Channel estimate hang */
#घोषणा B43_NPHY_FINERX2_CGC			B43_PHY_N(0x221) /* Fine RX 2 घड़ी gate control */
#घोषणा  B43_NPHY_FINERX2_CGC_DECGC		0x0008 /* Decode gated घड़ीs */
#घोषणा B43_NPHY_TXPCTL_INIT			B43_PHY_N(0x222) /* TX घातer control init */
#घोषणा  B43_NPHY_TXPCTL_INIT_PIDXI1		0x00FF /* Power index init 1 */
#घोषणा  B43_NPHY_TXPCTL_INIT_PIDXI1_SHIFT	0
#घोषणा B43_NPHY_ED_CRSEN			B43_PHY_N(0x223)
#घोषणा B43_NPHY_ED_CRS40ASSERTTHRESH0		B43_PHY_N(0x224)
#घोषणा B43_NPHY_ED_CRS40ASSERTTHRESH1		B43_PHY_N(0x225)
#घोषणा B43_NPHY_ED_CRS40DEASSERTTHRESH0	B43_PHY_N(0x226)
#घोषणा B43_NPHY_ED_CRS40DEASSERTTHRESH1	B43_PHY_N(0x227)
#घोषणा B43_NPHY_ED_CRS20LASSERTTHRESH0		B43_PHY_N(0x228)
#घोषणा B43_NPHY_ED_CRS20LASSERTTHRESH1		B43_PHY_N(0x229)
#घोषणा B43_NPHY_ED_CRS20LDEASSERTTHRESH0	B43_PHY_N(0x22A)
#घोषणा B43_NPHY_ED_CRS20LDEASSERTTHRESH1	B43_PHY_N(0x22B)
#घोषणा B43_NPHY_ED_CRS20UASSERTTHRESH0		B43_PHY_N(0x22C)
#घोषणा B43_NPHY_ED_CRS20UASSERTTHRESH1		B43_PHY_N(0x22D)
#घोषणा B43_NPHY_ED_CRS20UDEASSERTTHRESH0	B43_PHY_N(0x22E)
#घोषणा B43_NPHY_ED_CRS20UDEASSERTTHRESH1	B43_PHY_N(0x22F)
#घोषणा B43_NPHY_ED_CRS				B43_PHY_N(0x230)
#घोषणा B43_NPHY_TIMEOUTEN			B43_PHY_N(0x231)
#घोषणा B43_NPHY_OFDMPAYDECODETIMEOUTLEN	B43_PHY_N(0x232)
#घोषणा B43_NPHY_CCKPAYDECODETIMEOUTLEN		B43_PHY_N(0x233)
#घोषणा B43_NPHY_NONPAYDECODETIMEOUTLEN		B43_PHY_N(0x234)
#घोषणा B43_NPHY_TIMEOUTSTATUS			B43_PHY_N(0x235)
#घोषणा B43_NPHY_RFCTRLCORE0GPIO0		B43_PHY_N(0x236)
#घोषणा B43_NPHY_RFCTRLCORE0GPIO1		B43_PHY_N(0x237)
#घोषणा B43_NPHY_RFCTRLCORE0GPIO2		B43_PHY_N(0x238)
#घोषणा B43_NPHY_RFCTRLCORE0GPIO3		B43_PHY_N(0x239)
#घोषणा B43_NPHY_RFCTRLCORE1GPIO0		B43_PHY_N(0x23A)
#घोषणा B43_NPHY_RFCTRLCORE1GPIO1		B43_PHY_N(0x23B)
#घोषणा B43_NPHY_RFCTRLCORE1GPIO2		B43_PHY_N(0x23C)
#घोषणा B43_NPHY_RFCTRLCORE1GPIO3		B43_PHY_N(0x23D)
#घोषणा B43_NPHY_BPHYTESTCONTROL		B43_PHY_N(0x23E)
/* REV3+ */
#घोषणा B43_NPHY_FORCEFRONT0			B43_PHY_N(0x23F)
#घोषणा B43_NPHY_FORCEFRONT1			B43_PHY_N(0x240)
#घोषणा B43_NPHY_NORMVARHYSTTH			B43_PHY_N(0x241)
#घोषणा B43_NPHY_TXCCKERROR			B43_PHY_N(0x242)
#घोषणा B43_NPHY_AFESEQINITDACGAIN		B43_PHY_N(0x243)
#घोषणा B43_NPHY_TXANTSWLUT			B43_PHY_N(0x244)
#घोषणा B43_NPHY_CORECONFIG			B43_PHY_N(0x245)
#घोषणा B43_NPHY_ANTENNADIVDWELLTIME		B43_PHY_N(0x246)
#घोषणा B43_NPHY_ANTENNACCKDIVDWELLTIME		B43_PHY_N(0x247)
#घोषणा B43_NPHY_ANTENNADIVBACKOFFGAIN		B43_PHY_N(0x248)
#घोषणा B43_NPHY_ANTENNADIVMINGAIN		B43_PHY_N(0x249)
#घोषणा B43_NPHY_BRDSEL_NORMVARHYSTTH		B43_PHY_N(0x24A)
#घोषणा B43_NPHY_RXANTSWITCHCTRL		B43_PHY_N(0x24B)
#घोषणा B43_NPHY_ENERGYDROPTIMEOUTLEN2		B43_PHY_N(0x24C)
#घोषणा B43_NPHY_ML_LOG_TXEVM0			B43_PHY_N(0x250)
#घोषणा B43_NPHY_ML_LOG_TXEVM1			B43_PHY_N(0x251)
#घोषणा B43_NPHY_ML_LOG_TXEVM2			B43_PHY_N(0x252)
#घोषणा B43_NPHY_ML_LOG_TXEVM3			B43_PHY_N(0x253)
#घोषणा B43_NPHY_ML_LOG_TXEVM4			B43_PHY_N(0x254)
#घोषणा B43_NPHY_ML_LOG_TXEVM5			B43_PHY_N(0x255)
#घोषणा B43_NPHY_ML_LOG_TXEVM6			B43_PHY_N(0x256)
#घोषणा B43_NPHY_ML_LOG_TXEVM7			B43_PHY_N(0x257)
#घोषणा B43_NPHY_ML_SCALE_TWEAK			B43_PHY_N(0x258)
#घोषणा B43_NPHY_MLUA				B43_PHY_N(0x259)
#घोषणा B43_NPHY_ZFUA				B43_PHY_N(0x25A)
#घोषणा B43_NPHY_CHANUPSYM01			B43_PHY_N(0x25B)
#घोषणा B43_NPHY_CHANUPSYM2			B43_PHY_N(0x25C)
#घोषणा B43_NPHY_RXSTRNFILT20NUM00		B43_PHY_N(0x25D)
#घोषणा B43_NPHY_RXSTRNFILT20NUM01		B43_PHY_N(0x25E)
#घोषणा B43_NPHY_RXSTRNFILT20NUM02		B43_PHY_N(0x25F)
#घोषणा B43_NPHY_RXSTRNFILT20DEN00		B43_PHY_N(0x260)
#घोषणा B43_NPHY_RXSTRNFILT20DEN01		B43_PHY_N(0x261)
#घोषणा B43_NPHY_RXSTRNFILT20NUM10		B43_PHY_N(0x262)
#घोषणा B43_NPHY_RXSTRNFILT20NUM11		B43_PHY_N(0x263)
#घोषणा B43_NPHY_RXSTRNFILT20NUM12		B43_PHY_N(0x264)
#घोषणा B43_NPHY_RXSTRNFILT20DEN10		B43_PHY_N(0x265)
#घोषणा B43_NPHY_RXSTRNFILT20DEN11		B43_PHY_N(0x266)
#घोषणा B43_NPHY_RXSTRNFILT40NUM00		B43_PHY_N(0x267)
#घोषणा B43_NPHY_RXSTRNFILT40NUM01		B43_PHY_N(0x268)
#घोषणा B43_NPHY_RXSTRNFILT40NUM02		B43_PHY_N(0x269)
#घोषणा B43_NPHY_RXSTRNFILT40DEN00		B43_PHY_N(0x26A)
#घोषणा B43_NPHY_RXSTRNFILT40DEN01		B43_PHY_N(0x26B)
#घोषणा B43_NPHY_RXSTRNFILT40NUM10		B43_PHY_N(0x26C)
#घोषणा B43_NPHY_RXSTRNFILT40NUM11		B43_PHY_N(0x26D)
#घोषणा B43_NPHY_RXSTRNFILT40NUM12		B43_PHY_N(0x26E)
#घोषणा B43_NPHY_RXSTRNFILT40DEN10		B43_PHY_N(0x26F)
#घोषणा B43_NPHY_RXSTRNFILT40DEN11		B43_PHY_N(0x270)
#घोषणा B43_NPHY_CRSHIGHPOWTHRESHOLD1		B43_PHY_N(0x271)
#घोषणा B43_NPHY_CRSHIGHPOWTHRESHOLD2		B43_PHY_N(0x272)
#घोषणा B43_NPHY_CRSHIGHLOWPOWTHRESHOLD		B43_PHY_N(0x273)
#घोषणा B43_NPHY_CRSHIGHPOWTHRESHOLD1L		B43_PHY_N(0x274)
#घोषणा B43_NPHY_CRSHIGHPOWTHRESHOLD2L		B43_PHY_N(0x275)
#घोषणा B43_NPHY_CRSHIGHLOWPOWTHRESHOLDL	B43_PHY_N(0x276)
#घोषणा B43_NPHY_CRSHIGHPOWTHRESHOLD1U		B43_PHY_N(0x277)
#घोषणा B43_NPHY_CRSHIGHPOWTHRESHOLD2U		B43_PHY_N(0x278)
#घोषणा B43_NPHY_CRSHIGHLOWPOWTHRESHOLDU	B43_PHY_N(0x279)
#घोषणा B43_NPHY_CRSACIDETECTTHRESH		B43_PHY_N(0x27A)
#घोषणा B43_NPHY_CRSACIDETECTTHRESHL		B43_PHY_N(0x27B)
#घोषणा B43_NPHY_CRSACIDETECTTHRESHU		B43_PHY_N(0x27C)
#घोषणा B43_NPHY_CRSMINPOWER0			B43_PHY_N(0x27D)
#घोषणा B43_NPHY_CRSMINPOWER1			B43_PHY_N(0x27E)
#घोषणा B43_NPHY_CRSMINPOWER2			B43_PHY_N(0x27F)
#घोषणा B43_NPHY_CRSMINPOWERL0			B43_PHY_N(0x280)
#घोषणा B43_NPHY_CRSMINPOWERL1			B43_PHY_N(0x281)
#घोषणा B43_NPHY_CRSMINPOWERL2			B43_PHY_N(0x282)
#घोषणा B43_NPHY_CRSMINPOWERU0			B43_PHY_N(0x283)
#घोषणा B43_NPHY_CRSMINPOWERU1			B43_PHY_N(0x284)
#घोषणा B43_NPHY_CRSMINPOWERU2			B43_PHY_N(0x285)
#घोषणा B43_NPHY_STRPARAM			B43_PHY_N(0x286)
#घोषणा B43_NPHY_STRPARAML			B43_PHY_N(0x287)
#घोषणा B43_NPHY_STRPARAMU			B43_PHY_N(0x288)
#घोषणा B43_NPHY_BPHYCRSMINPOWER0		B43_PHY_N(0x289)
#घोषणा B43_NPHY_BPHYCRSMINPOWER1		B43_PHY_N(0x28A)
#घोषणा B43_NPHY_BPHYCRSMINPOWER2		B43_PHY_N(0x28B)
#घोषणा B43_NPHY_BPHYFILTDEN0COEF		B43_PHY_N(0x28C)
#घोषणा B43_NPHY_BPHYFILTDEN1COEF		B43_PHY_N(0x28D)
#घोषणा B43_NPHY_BPHYFILTDEN2COEF		B43_PHY_N(0x28E)
#घोषणा B43_NPHY_BPHYFILTNUM0COEF		B43_PHY_N(0x28F)
#घोषणा B43_NPHY_BPHYFILTNUM1COEF		B43_PHY_N(0x290)
#घोषणा B43_NPHY_BPHYFILTNUM2COEF		B43_PHY_N(0x291)
#घोषणा B43_NPHY_BPHYFILTNUM01COEF2		B43_PHY_N(0x292)
#घोषणा B43_NPHY_BPHYFILTBYPASS			B43_PHY_N(0x293)
#घोषणा B43_NPHY_SGILTRNOFFSET			B43_PHY_N(0x294)
#घोषणा B43_NPHY_RADAR_T2_MIN			B43_PHY_N(0x295)
#घोषणा B43_NPHY_TXPWRCTRLDAMPING		B43_PHY_N(0x296)
#घोषणा B43_NPHY_PAPD_EN0			B43_PHY_N(0x297) /* PAPD Enable0 TBD */
#घोषणा B43_NPHY_EPS_TABLE_ADJ0			B43_PHY_N(0x298) /* EPS Table Adj0 TBD */
#घोषणा B43_NPHY_EPS_OVERRIDEI_0		B43_PHY_N(0x299)
#घोषणा B43_NPHY_EPS_OVERRIDEQ_0		B43_PHY_N(0x29A)
#घोषणा B43_NPHY_PAPD_EN1			B43_PHY_N(0x29B) /* PAPD Enable1 TBD */
#घोषणा B43_NPHY_EPS_TABLE_ADJ1			B43_PHY_N(0x29C) /* EPS Table Adj1 TBD */
#घोषणा B43_NPHY_EPS_OVERRIDEI_1		B43_PHY_N(0x29D)
#घोषणा B43_NPHY_EPS_OVERRIDEQ_1		B43_PHY_N(0x29E)
#घोषणा B43_NPHY_PAPD_CAL_ADDRESS		B43_PHY_N(0x29F)
#घोषणा B43_NPHY_PAPD_CAL_YREFEPSILON		B43_PHY_N(0x2A0)
#घोषणा B43_NPHY_PAPD_CAL_SETTLE		B43_PHY_N(0x2A1)
#घोषणा B43_NPHY_PAPD_CAL_CORRELATE		B43_PHY_N(0x2A2)
#घोषणा B43_NPHY_PAPD_CAL_SHIFTS0		B43_PHY_N(0x2A3)
#घोषणा B43_NPHY_PAPD_CAL_SHIFTS1		B43_PHY_N(0x2A4)
#घोषणा B43_NPHY_SAMPLE_START_ADDR		B43_PHY_N(0x2A5)
#घोषणा B43_NPHY_RADAR_ADC_TO_DBM		B43_PHY_N(0x2A6)
#घोषणा B43_NPHY_REV3_C2_INITGAIN_A		B43_PHY_N(0x2A7)
#घोषणा B43_NPHY_REV3_C2_INITGAIN_B		B43_PHY_N(0x2A8)
#घोषणा B43_NPHY_REV3_C2_CLIP_HIGAIN_A		B43_PHY_N(0x2A9)
#घोषणा B43_NPHY_REV3_C2_CLIP_HIGAIN_B		B43_PHY_N(0x2AA)
#घोषणा B43_NPHY_REV3_C2_CLIP_MEDGAIN_A		B43_PHY_N(0x2AB)
#घोषणा B43_NPHY_REV3_C2_CLIP_MEDGAIN_B		B43_PHY_N(0x2AC)
#घोषणा B43_NPHY_REV3_C2_CLIP_LOGAIN_A		B43_PHY_N(0x2AD)
#घोषणा B43_NPHY_REV3_C2_CLIP_LOGAIN_B		B43_PHY_N(0x2AE)
#घोषणा B43_NPHY_REV3_C2_CLIP2_GAIN_A		B43_PHY_N(0x2AF)
#घोषणा B43_NPHY_REV3_C2_CLIP2_GAIN_B		B43_PHY_N(0x2B0)

#घोषणा B43_NPHY_REV7_RF_CTL_MISC_REG3		B43_PHY_N(0x340)
#घोषणा B43_NPHY_REV7_RF_CTL_MISC_REG4		B43_PHY_N(0x341)
#घोषणा B43_NPHY_REV7_RF_CTL_OVER3		B43_PHY_N(0x342)
#घोषणा B43_NPHY_REV7_RF_CTL_OVER4		B43_PHY_N(0x343)
#घोषणा B43_NPHY_REV7_RF_CTL_MISC_REG5		B43_PHY_N(0x344)
#घोषणा B43_NPHY_REV7_RF_CTL_MISC_REG6		B43_PHY_N(0x345)
#घोषणा B43_NPHY_REV7_RF_CTL_OVER5		B43_PHY_N(0x346)
#घोषणा B43_NPHY_REV7_RF_CTL_OVER6		B43_PHY_N(0x347)

#घोषणा B43_PHY_B_BBCFG				B43_PHY_N_BMODE(0x001) /* BB config */
#घोषणा  B43_PHY_B_BBCFG_RSTCCA			0x4000 /* Reset CCA */
#घोषणा  B43_PHY_B_BBCFG_RSTRX			0x8000 /* Reset RX */
#घोषणा B43_PHY_B_TEST				B43_PHY_N_BMODE(0x00A)

काष्ठा b43_wldev;

क्रमागत b43_nphy_spur_aव्योम अणु
	B43_SPUR_AVOID_DISABLE,
	B43_SPUR_AVOID_AUTO,
	B43_SPUR_AVOID_FORCE,
पूर्ण;

काष्ठा b43_chanspec अणु
	u16 center_freq;
	क्रमागत nl80211_channel_type channel_type;
पूर्ण;

काष्ठा b43_phy_n_iq_comp अणु
	s16 a0;
	s16 b0;
	s16 a1;
	s16 b1;
पूर्ण;

काष्ठा b43_phy_n_rssical_cache अणु
	u16 rssical_radio_regs_2G[2];
	u16 rssical_phy_regs_2G[12];

	u16 rssical_radio_regs_5G[2];
	u16 rssical_phy_regs_5G[12];
पूर्ण;

काष्ठा b43_phy_n_cal_cache अणु
	u16 txcal_radio_regs_2G[8];
	u16 txcal_coeffs_2G[8];
	काष्ठा b43_phy_n_iq_comp rxcal_coeffs_2G;

	u16 txcal_radio_regs_5G[8];
	u16 txcal_coeffs_5G[8];
	काष्ठा b43_phy_n_iq_comp rxcal_coeffs_5G;
पूर्ण;

काष्ठा b43_phy_n_txpwrindex अणु
	s8 index;
	s8 index_पूर्णांकernal;
	s8 index_पूर्णांकernal_save;
	u16 AfectrlOverride;
	u16 AfeCtrlDacGain;
	u16 rad_gain;
	u8 bbmult;
	u16 iqcomp_a;
	u16 iqcomp_b;
	u16 locomp;
पूर्ण;

काष्ठा b43_phy_n_pwr_ctl_info अणु
	u8 idle_tssi_2g;
	u8 idle_tssi_5g;
पूर्ण;

काष्ठा b43_phy_n अणु
	u8 antsel_type;
	u8 cal_orig_pwr_idx[2];
	u8 measure_hold;
	u8 phyrxchain;
	u8 hw_phyrxchain;
	u8 hw_phytxchain;
	u8 perical;
	u32 deaf_count;
	u32 rxcalparams;
	bool hang_aव्योम;
	bool mute;
	u16 papd_epsilon_offset[2];
	s32 preamble_override;
	u32 bb_mult_save;

	bool gain_boost;
	bool elna_gain_config;
	bool band5g_pwrgain;
	bool use_पूर्णांक_tx_iq_lo_cal;
	bool lpf_bw_overrode_क्रम_sample_play;

	u8 mphase_cal_phase_id;
	u16 mphase_txcal_cmdidx;
	u16 mphase_txcal_numcmds;
	u16 mphase_txcal_bestcoeffs[11];

	bool txpwrctrl;
	bool pwg_gain_5ghz;
	u8 tx_pwr_idx[2];
	s8 tx_घातer_offset[101];
	u16 adj_pwr_tbl[84];
	u16 txcal_bbmult;
	u16 txiqlocal_bestc[11];
	bool txiqlocal_coeffsvalid;
	काष्ठा b43_phy_n_txpwrindex txpwrindex[2];
	काष्ठा b43_phy_n_pwr_ctl_info pwr_ctl_info[2];
	काष्ठा b43_chanspec txiqlocal_chanspec;
	काष्ठा b43_ppr tx_pwr_max_ppr;
	u16 tx_pwr_last_recalc_freq;
	पूर्णांक tx_pwr_last_recalc_limit;

	u8 txrx_chain;
	u16 tx_rx_cal_phy_saveregs[11];
	u16 tx_rx_cal_radio_saveregs[22];

	u16 rfctrl_पूर्णांकc1_save;
	u16 rfctrl_पूर्णांकc2_save;

	u16 classअगरier_state;
	u16 clip_state[2];

	क्रमागत b43_nphy_spur_aव्योम spur_aव्योम;
	bool aband_spurwar_en;
	bool gband_spurwar_en;

	bool ipa2g_on;
	काष्ठा b43_chanspec iqcal_chanspec_2G;
	काष्ठा b43_chanspec rssical_chanspec_2G;

	bool ipa5g_on;
	काष्ठा b43_chanspec iqcal_chanspec_5G;
	काष्ठा b43_chanspec rssical_chanspec_5G;

	काष्ठा b43_phy_n_rssical_cache rssical_cache;
	काष्ठा b43_phy_n_cal_cache cal_cache;
	bool crsminpwr_adjusted;
	bool noisevars_adjusted;
पूर्ण;


काष्ठा b43_phy_operations;
बाह्य स्थिर काष्ठा b43_phy_operations b43_phyops_n;

#पूर्ण_अगर /* B43_NPHY_H_ */
