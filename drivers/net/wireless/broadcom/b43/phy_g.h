<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_B43_PHY_G_H_
#घोषणा LINUX_B43_PHY_G_H_

/* OFDM PHY रेजिस्टरs are defined in the A-PHY header. */
#समावेश "phy_a.h"

/* CCK (B) PHY Registers */
#घोषणा B43_PHY_VERSION_CCK		B43_PHY_CCK(0x00)	/* Versioning रेजिस्टर क्रम B-PHY */
#घोषणा B43_PHY_CCKBBANDCFG		B43_PHY_CCK(0x01)	/* Contains antenna 0/1 control bit */
#घोषणा B43_PHY_PGACTL			B43_PHY_CCK(0x15)	/* PGA control */
#घोषणा  B43_PHY_PGACTL_LPF		0x1000	/* Low pass filter (?) */
#घोषणा  B43_PHY_PGACTL_LOWBANDW	0x0040	/* Low bandwidth flag */
#घोषणा  B43_PHY_PGACTL_UNKNOWN		0xEFA0
#घोषणा B43_PHY_FBCTL1			B43_PHY_CCK(0x18)	/* Frequency bandwidth control 1 */
#घोषणा B43_PHY_ITSSI			B43_PHY_CCK(0x29)	/* Idle TSSI */
#घोषणा B43_PHY_LO_LEAKAGE		B43_PHY_CCK(0x2D)	/* Measured LO leakage */
#घोषणा B43_PHY_ENERGY			B43_PHY_CCK(0x33)	/* Energy */
#घोषणा B43_PHY_SYNCCTL			B43_PHY_CCK(0x35)
#घोषणा B43_PHY_FBCTL2			B43_PHY_CCK(0x38)	/* Frequency bandwidth control 2 */
#घोषणा B43_PHY_DACCTL			B43_PHY_CCK(0x60)	/* DAC control */
#घोषणा B43_PHY_RCCALOVER		B43_PHY_CCK(0x78)	/* RC calibration override */

/* Extended G-PHY Registers */
#घोषणा B43_PHY_CLASSCTL		B43_PHY_EXTG(0x02)	/* Classअगरy control */
#घोषणा B43_PHY_GTABCTL			B43_PHY_EXTG(0x03)	/* G-PHY table control (see below) */
#घोषणा  B43_PHY_GTABOFF		0x03FF	/* G-PHY table offset (see below) */
#घोषणा  B43_PHY_GTABNR			0xFC00	/* G-PHY table number (see below) */
#घोषणा  B43_PHY_GTABNR_SHIFT		10
#घोषणा B43_PHY_GTABDATA		B43_PHY_EXTG(0x04)	/* G-PHY table data */
#घोषणा B43_PHY_LO_MASK			B43_PHY_EXTG(0x0F)	/* Local Oscillator control mask */
#घोषणा B43_PHY_LO_CTL			B43_PHY_EXTG(0x10)	/* Local Oscillator control */
#घोषणा B43_PHY_RFOVER			B43_PHY_EXTG(0x11)	/* RF override */
#घोषणा B43_PHY_RFOVERVAL		B43_PHY_EXTG(0x12)	/* RF override value */
#घोषणा  B43_PHY_RFOVERVAL_EXTLNA	0x8000
#घोषणा  B43_PHY_RFOVERVAL_LNA		0x7000
#घोषणा  B43_PHY_RFOVERVAL_LNA_SHIFT	12
#घोषणा  B43_PHY_RFOVERVAL_PGA		0x0F00
#घोषणा  B43_PHY_RFOVERVAL_PGA_SHIFT	8
#घोषणा  B43_PHY_RFOVERVAL_UNK		0x0010	/* Unknown, always set. */
#घोषणा  B43_PHY_RFOVERVAL_TRSWRX	0x00E0
#घोषणा  B43_PHY_RFOVERVAL_BW		0x0003	/* Bandwidth flags */
#घोषणा   B43_PHY_RFOVERVAL_BW_LPF	0x0001	/* Low Pass Filter */
#घोषणा   B43_PHY_RFOVERVAL_BW_LBW	0x0002	/* Low Bandwidth (when set), high when unset */
#घोषणा B43_PHY_ANALOGOVER		B43_PHY_EXTG(0x14)	/* Analog override */
#घोषणा B43_PHY_ANALOGOVERVAL		B43_PHY_EXTG(0x15)	/* Analog override value */


/*** G-PHY table numbers */
#घोषणा B43_GTAB(number, offset)	(((number) << B43_PHY_GTABNR_SHIFT) | (offset))
#घोषणा B43_GTAB_NRSSI			B43_GTAB(0x00, 0)
#घोषणा B43_GTAB_TRFEMW			B43_GTAB(0x0C, 0x120)
#घोषणा B43_GTAB_ORIGTR			B43_GTAB(0x2E, 0x298)

u16 b43_gtab_पढ़ो(काष्ठा b43_wldev *dev, u16 table, u16 offset);
व्योम b43_gtab_ग_लिखो(काष्ठा b43_wldev *dev, u16 table, u16 offset, u16 value);


/* Returns the boolean whether "TX Magnification" is enabled. */
#घोषणा has_tx_magnअगरication(phy) \
	(((phy)->rev >= 2) &&			\
	 ((phy)->radio_ver == 0x2050) &&	\
	 ((phy)->radio_rev == 8))
/* Card uses the loopback gain stuff */
#घोषणा has_loopback_gain(phy) \
	(((phy)->rev > 1) || ((phy)->gmode))

/* Radio Attenuation (RF Attenuation) */
काष्ठा b43_rfatt अणु
	u8 att;			/* Attenuation value */
	bool with_padmix;	/* Flag, PAD Mixer enabled. */
पूर्ण;
काष्ठा b43_rfatt_list अणु
	/* Attenuation values list */
	स्थिर काष्ठा b43_rfatt *list;
	u8 len;
	/* Minimum/Maximum attenuation values */
	u8 min_val;
	u8 max_val;
पूर्ण;

/* Returns true, अगर the values are the same. */
अटल अंतरभूत bool b43_compare_rfatt(स्थिर काष्ठा b43_rfatt *a,
				     स्थिर काष्ठा b43_rfatt *b)
अणु
	वापस ((a->att == b->att) &&
		(a->with_padmix == b->with_padmix));
पूर्ण

/* Baseband Attenuation */
काष्ठा b43_bbatt अणु
	u8 att;			/* Attenuation value */
पूर्ण;
काष्ठा b43_bbatt_list अणु
	/* Attenuation values list */
	स्थिर काष्ठा b43_bbatt *list;
	u8 len;
	/* Minimum/Maximum attenuation values */
	u8 min_val;
	u8 max_val;
पूर्ण;

/* Returns true, अगर the values are the same. */
अटल अंतरभूत bool b43_compare_bbatt(स्थिर काष्ठा b43_bbatt *a,
				     स्थिर काष्ठा b43_bbatt *b)
अणु
	वापस (a->att == b->att);
पूर्ण

/* tx_control bits. */
#घोषणा B43_TXCTL_PA3DB		0x40	/* PA Gain 3dB */
#घोषणा B43_TXCTL_PA2DB		0x20	/* PA Gain 2dB */
#घोषणा B43_TXCTL_TXMIX		0x10	/* TX Mixer Gain */

काष्ठा b43_txघातer_lo_control;

काष्ठा b43_phy_g अणु
	/* ACI (adjacent channel पूर्णांकerference) flags. */
	bool aci_enable;
	bool aci_wlan_स्वतःmatic;
	bool aci_hw_rssi;

	/* Radio चयनed on/off */
	bool radio_on;
	काष्ठा अणु
		/* Values saved when turning the radio off.
		 * They are needed when turning it on again. */
		bool valid;
		u16 rfover;
		u16 rfoverval;
	पूर्ण radio_off_context;

	u16 minlowsig[2];
	u16 minlowsigpos[2];

	/* Poपूर्णांकer to the table used to convert a
	 * TSSI value to dBm-Q5.2 */
	स्थिर s8 *tssi2dbm;
	/* tssi2dbm is kदो_स्मृति()ed. Only used क्रम मुक्त()ing. */
	bool dyn_tssi_tbl;
	/* Target idle TSSI */
	पूर्णांक tgt_idle_tssi;
	/* Current idle TSSI */
	पूर्णांक cur_idle_tssi;
	/* The current average TSSI. */
	u8 average_tssi;
	/* Current TX घातer level attenuation control values */
	काष्ठा b43_bbatt bbatt;
	काष्ठा b43_rfatt rfatt;
	u8 tx_control;		/* B43_TXCTL_XXX */
	/* The calculated attenuation deltas that are used later
	 * when adjusting the actual घातer output. */
	पूर्णांक bbatt_delta;
	पूर्णांक rfatt_delta;

	/* LocalOscillator control values. */
	काष्ठा b43_txघातer_lo_control *lo_control;
	/* Values from b43_calc_loopback_gain() */
	s16 max_lb_gain;	/* Maximum Loopback gain in hdB */
	s16 trsw_rx_gain;	/* TRSW RX gain in hdB */
	s16 lna_lod_gain;	/* LNA lod */
	s16 lna_gain;		/* LNA */
	s16 pga_gain;		/* PGA */

	/* Current Interference Mitigation mode */
	पूर्णांक पूर्णांकerभ_शेषe;
	/* Stack of saved values from the Interference Mitigation code.
	 * Each value in the stack is laid out as follows:
	 * bit 0-11:  offset
	 * bit 12-15: रेजिस्टर ID
	 * bit 16-32: value
	 * रेजिस्टर ID is: 0x1 PHY, 0x2 Radio, 0x3 ILT
	 */
#घोषणा B43_INTERFSTACK_SIZE	26
	u32 पूर्णांकerfstack[B43_INTERFSTACK_SIZE];	//FIXME: use a data काष्ठाure

	/* Saved values from the NRSSI Slope calculation */
	s16 nrssi[2];
	s32 nrssislope;
	/* In memory nrssi lookup table. */
	s8 nrssi_lt[64];

	u16 lofcal;

	u16 initval;		//FIXME नाम?

	/* The device करोes address स्वतः increment क्रम the OFDM tables.
	 * We cache the previously used address here and omit the address
	 * ग_लिखो on the next table access, अगर possible. */
	u16 ofdmtab_addr; /* The address currently set in hardware. */
	क्रमागत अणु /* The last data flow direction. */
		B43_OFDMTAB_सूचीECTION_UNKNOWN = 0,
		B43_OFDMTAB_सूचीECTION_READ,
		B43_OFDMTAB_सूचीECTION_WRITE,
	पूर्ण ofdmtab_addr_direction;
पूर्ण;

व्योम b43_gphy_set_baseband_attenuation(काष्ठा b43_wldev *dev,
				       u16 baseband_attenuation);
व्योम b43_gphy_channel_चयन(काष्ठा b43_wldev *dev,
			     अचिन्हित पूर्णांक channel,
			     bool synthetic_pu_workaround);
u8 * b43_generate_dyn_tssi2dbm_tab(काष्ठा b43_wldev *dev,
				   s16 pab0, s16 pab1, s16 pab2);

काष्ठा b43_phy_operations;
बाह्य स्थिर काष्ठा b43_phy_operations b43_phyops_g;

#पूर्ण_अगर /* LINUX_B43_PHY_G_H_ */
