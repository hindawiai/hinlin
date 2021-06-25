<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम the National Semiconductor DP83640 PHYTER
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/crc32.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/phy.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/ptp_घड़ी_kernel.h>

#समावेश "dp83640_reg.h"

#घोषणा DP83640_PHY_ID	0x20005ce1
#घोषणा PAGESEL		0x13
#घोषणा MAX_RXTS	64
#घोषणा N_EXT_TS	6
#घोषणा N_PER_OUT	7
#घोषणा PSF_PTPVER	2
#घोषणा PSF_EVNT	0x4000
#घोषणा PSF_RX		0x2000
#घोषणा PSF_TX		0x1000
#घोषणा EXT_EVENT	1
#घोषणा CAL_EVENT	7
#घोषणा CAL_TRIGGER	1
#घोषणा DP83640_N_PINS	12

#घोषणा MII_DP83640_MICR 0x11
#घोषणा MII_DP83640_MISR 0x12

#घोषणा MII_DP83640_MICR_OE 0x1
#घोषणा MII_DP83640_MICR_IE 0x2

#घोषणा MII_DP83640_MISR_RHF_INT_EN 0x01
#घोषणा MII_DP83640_MISR_FHF_INT_EN 0x02
#घोषणा MII_DP83640_MISR_ANC_INT_EN 0x04
#घोषणा MII_DP83640_MISR_DUP_INT_EN 0x08
#घोषणा MII_DP83640_MISR_SPD_INT_EN 0x10
#घोषणा MII_DP83640_MISR_LINK_INT_EN 0x20
#घोषणा MII_DP83640_MISR_ED_INT_EN 0x40
#घोषणा MII_DP83640_MISR_LQ_INT_EN 0x80
#घोषणा MII_DP83640_MISR_ANC_INT 0x400
#घोषणा MII_DP83640_MISR_DUP_INT 0x800
#घोषणा MII_DP83640_MISR_SPD_INT 0x1000
#घोषणा MII_DP83640_MISR_LINK_INT 0x2000
#घोषणा MII_DP83640_MISR_INT_MASK (MII_DP83640_MISR_ANC_INT |\
				   MII_DP83640_MISR_DUP_INT |\
				   MII_DP83640_MISR_SPD_INT |\
				   MII_DP83640_MISR_LINK_INT)

/* phyter seems to miss the mark by 16 ns */
#घोषणा ADJTIME_FIX	16

#घोषणा SKB_TIMESTAMP_TIMEOUT	2 /* jअगरfies */

#अगर defined(__BIG_ENDIAN)
#घोषणा ENDIAN_FLAG	0
#या_अगर defined(__LITTLE_ENDIAN)
#घोषणा ENDIAN_FLAG	PSF_ENDIAN
#पूर्ण_अगर

काष्ठा dp83640_skb_info अणु
	पूर्णांक ptp_type;
	अचिन्हित दीर्घ पंचांगo;
पूर्ण;

काष्ठा phy_rxts अणु
	u16 ns_lo;   /* ns[15:0] */
	u16 ns_hi;   /* overflow[1:0], ns[29:16] */
	u16 sec_lo;  /* sec[15:0] */
	u16 sec_hi;  /* sec[31:16] */
	u16 seqid;   /* sequenceId[15:0] */
	u16 msgtype; /* messageType[3:0], hash[11:0] */
पूर्ण;

काष्ठा phy_txts अणु
	u16 ns_lo;   /* ns[15:0] */
	u16 ns_hi;   /* overflow[1:0], ns[29:16] */
	u16 sec_lo;  /* sec[15:0] */
	u16 sec_hi;  /* sec[31:16] */
पूर्ण;

काष्ठा rxts अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ पंचांगo;
	u64 ns;
	u16 seqid;
	u8  msgtype;
	u16 hash;
पूर्ण;

काष्ठा dp83640_घड़ी;

काष्ठा dp83640_निजी अणु
	काष्ठा list_head list;
	काष्ठा dp83640_घड़ी *घड़ी;
	काष्ठा phy_device *phydev;
	काष्ठा mii_बारtamper mii_ts;
	काष्ठा delayed_work ts_work;
	पूर्णांक hwts_tx_en;
	पूर्णांक hwts_rx_en;
	पूर्णांक layer;
	पूर्णांक version;
	/* remember state of cfg0 during calibration */
	पूर्णांक cfg0;
	/* remember the last event समय stamp */
	काष्ठा phy_txts edata;
	/* list of rx बारtamps */
	काष्ठा list_head rxts;
	काष्ठा list_head rxpool;
	काष्ठा rxts rx_pool_data[MAX_RXTS];
	/* protects above three fields from concurrent access */
	spinlock_t rx_lock;
	/* queues of incoming and outgoing packets */
	काष्ठा sk_buff_head rx_queue;
	काष्ठा sk_buff_head tx_queue;
पूर्ण;

काष्ठा dp83640_घड़ी अणु
	/* keeps the instance in the 'phyter_clocks' list */
	काष्ठा list_head list;
	/* we create one घड़ी instance per MII bus */
	काष्ठा mii_bus *bus;
	/* protects extended रेजिस्टरs from concurrent access */
	काष्ठा mutex extreg_lock;
	/* remembers which page was last selected */
	पूर्णांक page;
	/* our advertised capabilities */
	काष्ठा ptp_घड़ी_info caps;
	/* protects the three fields below from concurrent access */
	काष्ठा mutex घड़ी_lock;
	/* the one phyter from which we shall पढ़ो */
	काष्ठा dp83640_निजी *chosen;
	/* list of the other attached phyters, not chosen */
	काष्ठा list_head phylist;
	/* reference to our PTP hardware घड़ी */
	काष्ठा ptp_घड़ी *ptp_घड़ी;
पूर्ण;

/* globals */

क्रमागत अणु
	CALIBRATE_GPIO,
	PEROUT_GPIO,
	EXTTS0_GPIO,
	EXTTS1_GPIO,
	EXTTS2_GPIO,
	EXTTS3_GPIO,
	EXTTS4_GPIO,
	EXTTS5_GPIO,
	GPIO_TABLE_SIZE
पूर्ण;

अटल पूर्णांक chosen_phy = -1;
अटल uलघु gpio_tab[GPIO_TABLE_SIZE] = अणु
	1, 2, 3, 4, 8, 9, 10, 11
पूर्ण;

module_param(chosen_phy, पूर्णांक, 0444);
module_param_array(gpio_tab, uलघु, शून्य, 0444);

MODULE_PARM_DESC(chosen_phy, \
	"The address of the PHY to use for the ancillary clock features");
MODULE_PARM_DESC(gpio_tab, \
	"Which GPIO line to use for which purpose: cal,perout,extts1,...,extts6");

अटल व्योम dp83640_gpio_शेषs(काष्ठा ptp_pin_desc *pd)
अणु
	पूर्णांक i, index;

	क्रम (i = 0; i < DP83640_N_PINS; i++) अणु
		snम_लिखो(pd[i].name, माप(pd[i].name), "GPIO%d", 1 + i);
		pd[i].index = i;
	पूर्ण

	क्रम (i = 0; i < GPIO_TABLE_SIZE; i++) अणु
		अगर (gpio_tab[i] < 1 || gpio_tab[i] > DP83640_N_PINS) अणु
			pr_err("gpio_tab[%d]=%hu out of range", i, gpio_tab[i]);
			वापस;
		पूर्ण
	पूर्ण

	index = gpio_tab[CALIBRATE_GPIO] - 1;
	pd[index].func = PTP_PF_PHYSYNC;
	pd[index].chan = 0;

	index = gpio_tab[PEROUT_GPIO] - 1;
	pd[index].func = PTP_PF_PEROUT;
	pd[index].chan = 0;

	क्रम (i = EXTTS0_GPIO; i < GPIO_TABLE_SIZE; i++) अणु
		index = gpio_tab[i] - 1;
		pd[index].func = PTP_PF_EXTTS;
		pd[index].chan = i - EXTTS0_GPIO;
	पूर्ण
पूर्ण

/* a list of घड़ीs and a mutex to protect it */
अटल LIST_HEAD(phyter_घड़ीs);
अटल DEFINE_MUTEX(phyter_घड़ीs_lock);

अटल व्योम rx_बारtamp_work(काष्ठा work_काष्ठा *work);

/* extended रेजिस्टर access functions */

#घोषणा BROADCAST_ADDR 31

अटल अंतरभूत पूर्णांक broadcast_ग_लिखो(काष्ठा phy_device *phydev, u32 regnum,
				  u16 val)
अणु
	वापस mdiobus_ग_लिखो(phydev->mdio.bus, BROADCAST_ADDR, regnum, val);
पूर्ण

/* Caller must hold extreg_lock. */
अटल पूर्णांक ext_पढ़ो(काष्ठा phy_device *phydev, पूर्णांक page, u32 regnum)
अणु
	काष्ठा dp83640_निजी *dp83640 = phydev->priv;
	पूर्णांक val;

	अगर (dp83640->घड़ी->page != page) अणु
		broadcast_ग_लिखो(phydev, PAGESEL, page);
		dp83640->घड़ी->page = page;
	पूर्ण
	val = phy_पढ़ो(phydev, regnum);

	वापस val;
पूर्ण

/* Caller must hold extreg_lock. */
अटल व्योम ext_ग_लिखो(पूर्णांक broadcast, काष्ठा phy_device *phydev,
		      पूर्णांक page, u32 regnum, u16 val)
अणु
	काष्ठा dp83640_निजी *dp83640 = phydev->priv;

	अगर (dp83640->घड़ी->page != page) अणु
		broadcast_ग_लिखो(phydev, PAGESEL, page);
		dp83640->घड़ी->page = page;
	पूर्ण
	अगर (broadcast)
		broadcast_ग_लिखो(phydev, regnum, val);
	अन्यथा
		phy_ग_लिखो(phydev, regnum, val);
पूर्ण

/* Caller must hold extreg_lock. */
अटल पूर्णांक tdr_ग_लिखो(पूर्णांक bc, काष्ठा phy_device *dev,
		     स्थिर काष्ठा बारpec64 *ts, u16 cmd)
अणु
	ext_ग_लिखो(bc, dev, PAGE4, PTP_TDR, ts->tv_nsec & 0xffff);/* ns[15:0]  */
	ext_ग_लिखो(bc, dev, PAGE4, PTP_TDR, ts->tv_nsec >> 16);   /* ns[31:16] */
	ext_ग_लिखो(bc, dev, PAGE4, PTP_TDR, ts->tv_sec & 0xffff); /* sec[15:0] */
	ext_ग_लिखो(bc, dev, PAGE4, PTP_TDR, ts->tv_sec >> 16);    /* sec[31:16]*/

	ext_ग_लिखो(bc, dev, PAGE4, PTP_CTL, cmd);

	वापस 0;
पूर्ण

/* convert phy बारtamps पूर्णांकo driver बारtamps */

अटल व्योम phy2rxts(काष्ठा phy_rxts *p, काष्ठा rxts *rxts)
अणु
	u32 sec;

	sec = p->sec_lo;
	sec |= p->sec_hi << 16;

	rxts->ns = p->ns_lo;
	rxts->ns |= (p->ns_hi & 0x3fff) << 16;
	rxts->ns += ((u64)sec) * 1000000000ULL;
	rxts->seqid = p->seqid;
	rxts->msgtype = (p->msgtype >> 12) & 0xf;
	rxts->hash = p->msgtype & 0x0fff;
	rxts->पंचांगo = jअगरfies + SKB_TIMESTAMP_TIMEOUT;
पूर्ण

अटल u64 phy2txts(काष्ठा phy_txts *p)
अणु
	u64 ns;
	u32 sec;

	sec = p->sec_lo;
	sec |= p->sec_hi << 16;

	ns = p->ns_lo;
	ns |= (p->ns_hi & 0x3fff) << 16;
	ns += ((u64)sec) * 1000000000ULL;

	वापस ns;
पूर्ण

अटल पूर्णांक periodic_output(काष्ठा dp83640_घड़ी *घड़ी,
			   काष्ठा ptp_घड़ी_request *clkreq, bool on,
			   पूर्णांक trigger)
अणु
	काष्ठा dp83640_निजी *dp83640 = घड़ी->chosen;
	काष्ठा phy_device *phydev = dp83640->phydev;
	u32 sec, nsec, pwidth;
	u16 gpio, ptp_trig, val;

	अगर (on) अणु
		gpio = 1 + ptp_find_pin(घड़ी->ptp_घड़ी, PTP_PF_PEROUT,
					trigger);
		अगर (gpio < 1)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		gpio = 0;
	पूर्ण

	ptp_trig = TRIG_WR |
		(trigger & TRIG_CSEL_MASK) << TRIG_CSEL_SHIFT |
		(gpio & TRIG_GPIO_MASK) << TRIG_GPIO_SHIFT |
		TRIG_PER |
		TRIG_PULSE;

	val = (trigger & TRIG_SEL_MASK) << TRIG_SEL_SHIFT;

	अगर (!on) अणु
		val |= TRIG_DIS;
		mutex_lock(&घड़ी->extreg_lock);
		ext_ग_लिखो(0, phydev, PAGE5, PTP_TRIG, ptp_trig);
		ext_ग_लिखो(0, phydev, PAGE4, PTP_CTL, val);
		mutex_unlock(&घड़ी->extreg_lock);
		वापस 0;
	पूर्ण

	sec = clkreq->perout.start.sec;
	nsec = clkreq->perout.start.nsec;
	pwidth = clkreq->perout.period.sec * 1000000000UL;
	pwidth += clkreq->perout.period.nsec;
	pwidth /= 2;

	mutex_lock(&घड़ी->extreg_lock);

	ext_ग_लिखो(0, phydev, PAGE5, PTP_TRIG, ptp_trig);

	/*load trigger*/
	val |= TRIG_LOAD;
	ext_ग_लिखो(0, phydev, PAGE4, PTP_CTL, val);
	ext_ग_लिखो(0, phydev, PAGE4, PTP_TDR, nsec & 0xffff);   /* ns[15:0] */
	ext_ग_लिखो(0, phydev, PAGE4, PTP_TDR, nsec >> 16);      /* ns[31:16] */
	ext_ग_लिखो(0, phydev, PAGE4, PTP_TDR, sec & 0xffff);    /* sec[15:0] */
	ext_ग_लिखो(0, phydev, PAGE4, PTP_TDR, sec >> 16);       /* sec[31:16] */
	ext_ग_लिखो(0, phydev, PAGE4, PTP_TDR, pwidth & 0xffff); /* ns[15:0] */
	ext_ग_लिखो(0, phydev, PAGE4, PTP_TDR, pwidth >> 16);    /* ns[31:16] */
	/* Triggers 0 and 1 has programmable pulsewidth2 */
	अगर (trigger < 2) अणु
		ext_ग_लिखो(0, phydev, PAGE4, PTP_TDR, pwidth & 0xffff);
		ext_ग_लिखो(0, phydev, PAGE4, PTP_TDR, pwidth >> 16);
	पूर्ण

	/*enable trigger*/
	val &= ~TRIG_LOAD;
	val |= TRIG_EN;
	ext_ग_लिखो(0, phydev, PAGE4, PTP_CTL, val);

	mutex_unlock(&घड़ी->extreg_lock);
	वापस 0;
पूर्ण

/* ptp घड़ी methods */

अटल पूर्णांक ptp_dp83640_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	काष्ठा dp83640_घड़ी *घड़ी =
		container_of(ptp, काष्ठा dp83640_घड़ी, caps);
	काष्ठा phy_device *phydev = घड़ी->chosen->phydev;
	u64 rate;
	पूर्णांक neg_adj = 0;
	u16 hi, lo;

	अगर (scaled_ppm < 0) अणु
		neg_adj = 1;
		scaled_ppm = -scaled_ppm;
	पूर्ण
	rate = scaled_ppm;
	rate <<= 13;
	rate = भाग_u64(rate, 15625);

	hi = (rate >> 16) & PTP_RATE_HI_MASK;
	अगर (neg_adj)
		hi |= PTP_RATE_सूची;

	lo = rate & 0xffff;

	mutex_lock(&घड़ी->extreg_lock);

	ext_ग_लिखो(1, phydev, PAGE4, PTP_RATEH, hi);
	ext_ग_लिखो(1, phydev, PAGE4, PTP_RATEL, lo);

	mutex_unlock(&घड़ी->extreg_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_dp83640_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा dp83640_घड़ी *घड़ी =
		container_of(ptp, काष्ठा dp83640_घड़ी, caps);
	काष्ठा phy_device *phydev = घड़ी->chosen->phydev;
	काष्ठा बारpec64 ts;
	पूर्णांक err;

	delta += ADJTIME_FIX;

	ts = ns_to_बारpec64(delta);

	mutex_lock(&घड़ी->extreg_lock);

	err = tdr_ग_लिखो(1, phydev, &ts, PTP_STEP_CLK);

	mutex_unlock(&घड़ी->extreg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक ptp_dp83640_समय_लो(काष्ठा ptp_घड़ी_info *ptp,
			       काष्ठा बारpec64 *ts)
अणु
	काष्ठा dp83640_घड़ी *घड़ी =
		container_of(ptp, काष्ठा dp83640_घड़ी, caps);
	काष्ठा phy_device *phydev = घड़ी->chosen->phydev;
	अचिन्हित पूर्णांक val[4];

	mutex_lock(&घड़ी->extreg_lock);

	ext_ग_लिखो(0, phydev, PAGE4, PTP_CTL, PTP_RD_CLK);

	val[0] = ext_पढ़ो(phydev, PAGE4, PTP_TDR); /* ns[15:0] */
	val[1] = ext_पढ़ो(phydev, PAGE4, PTP_TDR); /* ns[31:16] */
	val[2] = ext_पढ़ो(phydev, PAGE4, PTP_TDR); /* sec[15:0] */
	val[3] = ext_पढ़ो(phydev, PAGE4, PTP_TDR); /* sec[31:16] */

	mutex_unlock(&घड़ी->extreg_lock);

	ts->tv_nsec = val[0] | (val[1] << 16);
	ts->tv_sec  = val[2] | (val[3] << 16);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_dp83640_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			       स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा dp83640_घड़ी *घड़ी =
		container_of(ptp, काष्ठा dp83640_घड़ी, caps);
	काष्ठा phy_device *phydev = घड़ी->chosen->phydev;
	पूर्णांक err;

	mutex_lock(&घड़ी->extreg_lock);

	err = tdr_ग_लिखो(1, phydev, ts, PTP_LOAD_CLK);

	mutex_unlock(&घड़ी->extreg_lock);

	वापस err;
पूर्ण

अटल पूर्णांक ptp_dp83640_enable(काष्ठा ptp_घड़ी_info *ptp,
			      काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा dp83640_घड़ी *घड़ी =
		container_of(ptp, काष्ठा dp83640_घड़ी, caps);
	काष्ठा phy_device *phydev = घड़ी->chosen->phydev;
	अचिन्हित पूर्णांक index;
	u16 evnt, event_num, gpio_num;

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_EXTTS:
		/* Reject requests with unsupported flags */
		अगर (rq->extts.flags & ~(PTP_ENABLE_FEATURE |
					PTP_RISING_EDGE |
					PTP_FALLING_EDGE |
					PTP_STRICT_FLAGS))
			वापस -EOPNOTSUPP;

		/* Reject requests to enable समय stamping on both edges. */
		अगर ((rq->extts.flags & PTP_STRICT_FLAGS) &&
		    (rq->extts.flags & PTP_ENABLE_FEATURE) &&
		    (rq->extts.flags & PTP_EXTTS_EDGES) == PTP_EXTTS_EDGES)
			वापस -EOPNOTSUPP;

		index = rq->extts.index;
		अगर (index >= N_EXT_TS)
			वापस -EINVAL;
		event_num = EXT_EVENT + index;
		evnt = EVNT_WR | (event_num & EVNT_SEL_MASK) << EVNT_SEL_SHIFT;
		अगर (on) अणु
			gpio_num = 1 + ptp_find_pin(घड़ी->ptp_घड़ी,
						    PTP_PF_EXTTS, index);
			अगर (gpio_num < 1)
				वापस -EINVAL;
			evnt |= (gpio_num & EVNT_GPIO_MASK) << EVNT_GPIO_SHIFT;
			अगर (rq->extts.flags & PTP_FALLING_EDGE)
				evnt |= EVNT_FALL;
			अन्यथा
				evnt |= EVNT_RISE;
		पूर्ण
		mutex_lock(&घड़ी->extreg_lock);
		ext_ग_लिखो(0, phydev, PAGE5, PTP_EVNT, evnt);
		mutex_unlock(&घड़ी->extreg_lock);
		वापस 0;

	हाल PTP_CLK_REQ_PEROUT:
		/* Reject requests with unsupported flags */
		अगर (rq->perout.flags)
			वापस -EOPNOTSUPP;
		अगर (rq->perout.index >= N_PER_OUT)
			वापस -EINVAL;
		वापस periodic_output(घड़ी, rq, on, rq->perout.index);

	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ptp_dp83640_verअगरy(काष्ठा ptp_घड़ी_info *ptp, अचिन्हित पूर्णांक pin,
			      क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा dp83640_घड़ी *घड़ी =
		container_of(ptp, काष्ठा dp83640_घड़ी, caps);

	अगर (घड़ी->caps.pin_config[pin].func == PTP_PF_PHYSYNC &&
	    !list_empty(&घड़ी->phylist))
		वापस 1;

	अगर (func == PTP_PF_PHYSYNC)
		वापस 1;

	वापस 0;
पूर्ण

अटल u8 status_frame_dst[6] = अणु 0x01, 0x1B, 0x19, 0x00, 0x00, 0x00 पूर्ण;
अटल u8 status_frame_src[6] = अणु 0x08, 0x00, 0x17, 0x0B, 0x6B, 0x0F पूर्ण;

अटल व्योम enable_status_frames(काष्ठा phy_device *phydev, bool on)
अणु
	काष्ठा dp83640_निजी *dp83640 = phydev->priv;
	काष्ठा dp83640_घड़ी *घड़ी = dp83640->घड़ी;
	u16 cfg0 = 0, ver;

	अगर (on)
		cfg0 = PSF_EVNT_EN | PSF_RXTS_EN | PSF_TXTS_EN | ENDIAN_FLAG;

	ver = (PSF_PTPVER & VERSIONPTP_MASK) << VERSIONPTP_SHIFT;

	mutex_lock(&घड़ी->extreg_lock);

	ext_ग_लिखो(0, phydev, PAGE5, PSF_CFG0, cfg0);
	ext_ग_लिखो(0, phydev, PAGE6, PSF_CFG1, ver);

	mutex_unlock(&घड़ी->extreg_lock);

	अगर (!phydev->attached_dev) अणु
		phydev_warn(phydev,
			    "expected to find an attached netdevice\n");
		वापस;
	पूर्ण

	अगर (on) अणु
		अगर (dev_mc_add(phydev->attached_dev, status_frame_dst))
			phydev_warn(phydev, "failed to add mc address\n");
	पूर्ण अन्यथा अणु
		अगर (dev_mc_del(phydev->attached_dev, status_frame_dst))
			phydev_warn(phydev, "failed to delete mc address\n");
	पूर्ण
पूर्ण

अटल bool is_status_frame(काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा ethhdr *h = eth_hdr(skb);

	अगर (PTP_CLASS_V2_L2 == type &&
	    !स_भेद(h->h_source, status_frame_src, माप(status_frame_src)))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक expired(काष्ठा rxts *rxts)
अणु
	वापस समय_after(jअगरfies, rxts->पंचांगo);
पूर्ण

/* Caller must hold rx_lock. */
अटल व्योम prune_rx_ts(काष्ठा dp83640_निजी *dp83640)
अणु
	काष्ठा list_head *this, *next;
	काष्ठा rxts *rxts;

	list_क्रम_each_safe(this, next, &dp83640->rxts) अणु
		rxts = list_entry(this, काष्ठा rxts, list);
		अगर (expired(rxts)) अणु
			list_del_init(&rxts->list);
			list_add(&rxts->list, &dp83640->rxpool);
		पूर्ण
	पूर्ण
पूर्ण

/* synchronize the phyters so they act as one घड़ी */

अटल व्योम enable_broadcast(काष्ठा phy_device *phydev, पूर्णांक init_page, पूर्णांक on)
अणु
	पूर्णांक val;
	phy_ग_लिखो(phydev, PAGESEL, 0);
	val = phy_पढ़ो(phydev, PHYCR2);
	अगर (on)
		val |= BC_WRITE;
	अन्यथा
		val &= ~BC_WRITE;
	phy_ग_लिखो(phydev, PHYCR2, val);
	phy_ग_लिखो(phydev, PAGESEL, init_page);
पूर्ण

अटल व्योम recalibrate(काष्ठा dp83640_घड़ी *घड़ी)
अणु
	s64 now, dअगरf;
	काष्ठा phy_txts event_ts;
	काष्ठा बारpec64 ts;
	काष्ठा list_head *this;
	काष्ठा dp83640_निजी *पंचांगp;
	काष्ठा phy_device *master = घड़ी->chosen->phydev;
	u16 cal_gpio, cfg0, evnt, ptp_trig, trigger, val;

	trigger = CAL_TRIGGER;
	cal_gpio = 1 + ptp_find_pin_unlocked(घड़ी->ptp_घड़ी, PTP_PF_PHYSYNC, 0);
	अगर (cal_gpio < 1) अणु
		pr_err("PHY calibration pin not available - PHY is not calibrated.");
		वापस;
	पूर्ण

	mutex_lock(&घड़ी->extreg_lock);

	/*
	 * enable broadcast, disable status frames, enable ptp घड़ी
	 */
	list_क्रम_each(this, &घड़ी->phylist) अणु
		पंचांगp = list_entry(this, काष्ठा dp83640_निजी, list);
		enable_broadcast(पंचांगp->phydev, घड़ी->page, 1);
		पंचांगp->cfg0 = ext_पढ़ो(पंचांगp->phydev, PAGE5, PSF_CFG0);
		ext_ग_लिखो(0, पंचांगp->phydev, PAGE5, PSF_CFG0, 0);
		ext_ग_लिखो(0, पंचांगp->phydev, PAGE4, PTP_CTL, PTP_ENABLE);
	पूर्ण
	enable_broadcast(master, घड़ी->page, 1);
	cfg0 = ext_पढ़ो(master, PAGE5, PSF_CFG0);
	ext_ग_लिखो(0, master, PAGE5, PSF_CFG0, 0);
	ext_ग_लिखो(0, master, PAGE4, PTP_CTL, PTP_ENABLE);

	/*
	 * enable an event बारtamp
	 */
	evnt = EVNT_WR | EVNT_RISE | EVNT_SINGLE;
	evnt |= (CAL_EVENT & EVNT_SEL_MASK) << EVNT_SEL_SHIFT;
	evnt |= (cal_gpio & EVNT_GPIO_MASK) << EVNT_GPIO_SHIFT;

	list_क्रम_each(this, &घड़ी->phylist) अणु
		पंचांगp = list_entry(this, काष्ठा dp83640_निजी, list);
		ext_ग_लिखो(0, पंचांगp->phydev, PAGE5, PTP_EVNT, evnt);
	पूर्ण
	ext_ग_लिखो(0, master, PAGE5, PTP_EVNT, evnt);

	/*
	 * configure a trigger
	 */
	ptp_trig = TRIG_WR | TRIG_IF_LATE | TRIG_PULSE;
	ptp_trig |= (trigger  & TRIG_CSEL_MASK) << TRIG_CSEL_SHIFT;
	ptp_trig |= (cal_gpio & TRIG_GPIO_MASK) << TRIG_GPIO_SHIFT;
	ext_ग_लिखो(0, master, PAGE5, PTP_TRIG, ptp_trig);

	/* load trigger */
	val = (trigger & TRIG_SEL_MASK) << TRIG_SEL_SHIFT;
	val |= TRIG_LOAD;
	ext_ग_लिखो(0, master, PAGE4, PTP_CTL, val);

	/* enable trigger */
	val &= ~TRIG_LOAD;
	val |= TRIG_EN;
	ext_ग_लिखो(0, master, PAGE4, PTP_CTL, val);

	/* disable trigger */
	val = (trigger & TRIG_SEL_MASK) << TRIG_SEL_SHIFT;
	val |= TRIG_DIS;
	ext_ग_लिखो(0, master, PAGE4, PTP_CTL, val);

	/*
	 * पढ़ो out and correct offsets
	 */
	val = ext_पढ़ो(master, PAGE4, PTP_STS);
	phydev_info(master, "master PTP_STS  0x%04hx\n", val);
	val = ext_पढ़ो(master, PAGE4, PTP_ESTS);
	phydev_info(master, "master PTP_ESTS 0x%04hx\n", val);
	event_ts.ns_lo  = ext_पढ़ो(master, PAGE4, PTP_EDATA);
	event_ts.ns_hi  = ext_पढ़ो(master, PAGE4, PTP_EDATA);
	event_ts.sec_lo = ext_पढ़ो(master, PAGE4, PTP_EDATA);
	event_ts.sec_hi = ext_पढ़ो(master, PAGE4, PTP_EDATA);
	now = phy2txts(&event_ts);

	list_क्रम_each(this, &घड़ी->phylist) अणु
		पंचांगp = list_entry(this, काष्ठा dp83640_निजी, list);
		val = ext_पढ़ो(पंचांगp->phydev, PAGE4, PTP_STS);
		phydev_info(पंचांगp->phydev, "slave  PTP_STS  0x%04hx\n", val);
		val = ext_पढ़ो(पंचांगp->phydev, PAGE4, PTP_ESTS);
		phydev_info(पंचांगp->phydev, "slave  PTP_ESTS 0x%04hx\n", val);
		event_ts.ns_lo  = ext_पढ़ो(पंचांगp->phydev, PAGE4, PTP_EDATA);
		event_ts.ns_hi  = ext_पढ़ो(पंचांगp->phydev, PAGE4, PTP_EDATA);
		event_ts.sec_lo = ext_पढ़ो(पंचांगp->phydev, PAGE4, PTP_EDATA);
		event_ts.sec_hi = ext_पढ़ो(पंचांगp->phydev, PAGE4, PTP_EDATA);
		dअगरf = now - (s64) phy2txts(&event_ts);
		phydev_info(पंचांगp->phydev, "slave offset %lld nanoseconds\n",
			    dअगरf);
		dअगरf += ADJTIME_FIX;
		ts = ns_to_बारpec64(dअगरf);
		tdr_ग_लिखो(0, पंचांगp->phydev, &ts, PTP_STEP_CLK);
	पूर्ण

	/*
	 * restore status frames
	 */
	list_क्रम_each(this, &घड़ी->phylist) अणु
		पंचांगp = list_entry(this, काष्ठा dp83640_निजी, list);
		ext_ग_लिखो(0, पंचांगp->phydev, PAGE5, PSF_CFG0, पंचांगp->cfg0);
	पूर्ण
	ext_ग_लिखो(0, master, PAGE5, PSF_CFG0, cfg0);

	mutex_unlock(&घड़ी->extreg_lock);
पूर्ण

/* समय stamping methods */

अटल अंतरभूत u16 exts_chan_to_edata(पूर्णांक ch)
अणु
	वापस 1 << ((ch + EXT_EVENT) * 2);
पूर्ण

अटल पूर्णांक decode_evnt(काष्ठा dp83640_निजी *dp83640,
		       व्योम *data, पूर्णांक len, u16 ests)
अणु
	काष्ठा phy_txts *phy_txts;
	काष्ठा ptp_घड़ी_event event;
	पूर्णांक i, parsed;
	पूर्णांक words = (ests >> EVNT_TS_LEN_SHIFT) & EVNT_TS_LEN_MASK;
	u16 ext_status = 0;

	/* calculate length of the event बारtamp status message */
	अगर (ests & MULT_EVNT)
		parsed = (words + 2) * माप(u16);
	अन्यथा
		parsed = (words + 1) * माप(u16);

	/* check अगर enough data is available */
	अगर (len < parsed)
		वापस len;

	अगर (ests & MULT_EVNT) अणु
		ext_status = *(u16 *) data;
		data += माप(ext_status);
	पूर्ण

	phy_txts = data;

	चयन (words) अणु
	हाल 3:
		dp83640->edata.sec_hi = phy_txts->sec_hi;
		fallthrough;
	हाल 2:
		dp83640->edata.sec_lo = phy_txts->sec_lo;
		fallthrough;
	हाल 1:
		dp83640->edata.ns_hi = phy_txts->ns_hi;
		fallthrough;
	हाल 0:
		dp83640->edata.ns_lo = phy_txts->ns_lo;
	पूर्ण

	अगर (!ext_status) अणु
		i = ((ests >> EVNT_NUM_SHIFT) & EVNT_NUM_MASK) - EXT_EVENT;
		ext_status = exts_chan_to_edata(i);
	पूर्ण

	event.type = PTP_CLOCK_EXTTS;
	event.बारtamp = phy2txts(&dp83640->edata);

	/* Compensate क्रम input path and synchronization delays */
	event.बारtamp -= 35;

	क्रम (i = 0; i < N_EXT_TS; i++) अणु
		अगर (ext_status & exts_chan_to_edata(i)) अणु
			event.index = i;
			ptp_घड़ी_event(dp83640->घड़ी->ptp_घड़ी, &event);
		पूर्ण
	पूर्ण

	वापस parsed;
पूर्ण

#घोषणा DP83640_PACKET_HASH_LEN		10

अटल पूर्णांक match(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक type, काष्ठा rxts *rxts)
अणु
	काष्ठा ptp_header *hdr;
	u8 msgtype;
	u16 seqid;
	u16 hash;

	/* check sequenceID, messageType, 12 bit hash of offset 20-29 */

	hdr = ptp_parse_header(skb, type);
	अगर (!hdr)
		वापस 0;

	msgtype = ptp_get_msgtype(hdr, type);

	अगर (rxts->msgtype != (msgtype & 0xf))
		वापस 0;

	seqid = be16_to_cpu(hdr->sequence_id);
	अगर (rxts->seqid != seqid)
		वापस 0;

	hash = ether_crc(DP83640_PACKET_HASH_LEN,
			 (अचिन्हित अक्षर *)&hdr->source_port_identity) >> 20;
	अगर (rxts->hash != hash)
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम decode_rxts(काष्ठा dp83640_निजी *dp83640,
			काष्ठा phy_rxts *phy_rxts)
अणु
	काष्ठा rxts *rxts;
	काष्ठा skb_shared_hwtstamps *shhwtstamps = शून्य;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	u8 overflow;

	overflow = (phy_rxts->ns_hi >> 14) & 0x3;
	अगर (overflow)
		pr_debug("rx timestamp queue overflow, count %d\n", overflow);

	spin_lock_irqsave(&dp83640->rx_lock, flags);

	prune_rx_ts(dp83640);

	अगर (list_empty(&dp83640->rxpool)) अणु
		pr_debug("rx timestamp pool is empty\n");
		जाओ out;
	पूर्ण
	rxts = list_first_entry(&dp83640->rxpool, काष्ठा rxts, list);
	list_del_init(&rxts->list);
	phy2rxts(phy_rxts, rxts);

	spin_lock(&dp83640->rx_queue.lock);
	skb_queue_walk(&dp83640->rx_queue, skb) अणु
		काष्ठा dp83640_skb_info *skb_info;

		skb_info = (काष्ठा dp83640_skb_info *)skb->cb;
		अगर (match(skb, skb_info->ptp_type, rxts)) अणु
			__skb_unlink(skb, &dp83640->rx_queue);
			shhwtstamps = skb_hwtstamps(skb);
			स_रखो(shhwtstamps, 0, माप(*shhwtstamps));
			shhwtstamps->hwtstamp = ns_to_kसमय(rxts->ns);
			list_add(&rxts->list, &dp83640->rxpool);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&dp83640->rx_queue.lock);

	अगर (!shhwtstamps)
		list_add_tail(&rxts->list, &dp83640->rxts);
out:
	spin_unlock_irqrestore(&dp83640->rx_lock, flags);

	अगर (shhwtstamps)
		netअगर_rx_ni(skb);
पूर्ण

अटल व्योम decode_txts(काष्ठा dp83640_निजी *dp83640,
			काष्ठा phy_txts *phy_txts)
अणु
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	काष्ठा dp83640_skb_info *skb_info;
	काष्ठा sk_buff *skb;
	u8 overflow;
	u64 ns;

	/* We must alपढ़ोy have the skb that triggered this. */
again:
	skb = skb_dequeue(&dp83640->tx_queue);
	अगर (!skb) अणु
		pr_debug("have timestamp but tx_queue empty\n");
		वापस;
	पूर्ण

	overflow = (phy_txts->ns_hi >> 14) & 0x3;
	अगर (overflow) अणु
		pr_debug("tx timestamp queue overflow, count %d\n", overflow);
		जबतक (skb) अणु
			kमुक्त_skb(skb);
			skb = skb_dequeue(&dp83640->tx_queue);
		पूर्ण
		वापस;
	पूर्ण
	skb_info = (काष्ठा dp83640_skb_info *)skb->cb;
	अगर (समय_after(jअगरfies, skb_info->पंचांगo)) अणु
		kमुक्त_skb(skb);
		जाओ again;
	पूर्ण

	ns = phy2txts(phy_txts);
	स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
	shhwtstamps.hwtstamp = ns_to_kसमय(ns);
	skb_complete_tx_बारtamp(skb, &shhwtstamps);
पूर्ण

अटल व्योम decode_status_frame(काष्ठा dp83640_निजी *dp83640,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा phy_rxts *phy_rxts;
	काष्ठा phy_txts *phy_txts;
	u8 *ptr;
	पूर्णांक len, size;
	u16 ests, type;

	ptr = skb->data + 2;

	क्रम (len = skb_headlen(skb) - 2; len > माप(type); len -= size) अणु

		type = *(u16 *)ptr;
		ests = type & 0x0fff;
		type = type & 0xf000;
		len -= माप(type);
		ptr += माप(type);

		अगर (PSF_RX == type && len >= माप(*phy_rxts)) अणु

			phy_rxts = (काष्ठा phy_rxts *) ptr;
			decode_rxts(dp83640, phy_rxts);
			size = माप(*phy_rxts);

		पूर्ण अन्यथा अगर (PSF_TX == type && len >= माप(*phy_txts)) अणु

			phy_txts = (काष्ठा phy_txts *) ptr;
			decode_txts(dp83640, phy_txts);
			size = माप(*phy_txts);

		पूर्ण अन्यथा अगर (PSF_EVNT == type) अणु

			size = decode_evnt(dp83640, ptr, len, ests);

		पूर्ण अन्यथा अणु
			size = 0;
			अवरोध;
		पूर्ण
		ptr += size;
	पूर्ण
पूर्ण

अटल पूर्णांक is_sync(काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा ptp_header *hdr;

	hdr = ptp_parse_header(skb, type);
	अगर (!hdr)
		वापस 0;

	वापस ptp_get_msgtype(hdr, type) == PTP_MSGTYPE_SYNC;
पूर्ण

अटल व्योम dp83640_मुक्त_घड़ीs(व्योम)
अणु
	काष्ठा dp83640_घड़ी *घड़ी;
	काष्ठा list_head *this, *next;

	mutex_lock(&phyter_घड़ीs_lock);

	list_क्रम_each_safe(this, next, &phyter_घड़ीs) अणु
		घड़ी = list_entry(this, काष्ठा dp83640_घड़ी, list);
		अगर (!list_empty(&घड़ी->phylist)) अणु
			pr_warn("phy list non-empty while unloading\n");
			BUG();
		पूर्ण
		list_del(&घड़ी->list);
		mutex_destroy(&घड़ी->extreg_lock);
		mutex_destroy(&घड़ी->घड़ी_lock);
		put_device(&घड़ी->bus->dev);
		kमुक्त(घड़ी->caps.pin_config);
		kमुक्त(घड़ी);
	पूर्ण

	mutex_unlock(&phyter_घड़ीs_lock);
पूर्ण

अटल व्योम dp83640_घड़ी_init(काष्ठा dp83640_घड़ी *घड़ी, काष्ठा mii_bus *bus)
अणु
	INIT_LIST_HEAD(&घड़ी->list);
	घड़ी->bus = bus;
	mutex_init(&घड़ी->extreg_lock);
	mutex_init(&घड़ी->घड़ी_lock);
	INIT_LIST_HEAD(&घड़ी->phylist);
	घड़ी->caps.owner = THIS_MODULE;
	प्र_लिखो(घड़ी->caps.name, "dp83640 timer");
	घड़ी->caps.max_adj	= 1953124;
	घड़ी->caps.n_alarm	= 0;
	घड़ी->caps.n_ext_ts	= N_EXT_TS;
	घड़ी->caps.n_per_out	= N_PER_OUT;
	घड़ी->caps.n_pins	= DP83640_N_PINS;
	घड़ी->caps.pps		= 0;
	घड़ी->caps.adjfine	= ptp_dp83640_adjfine;
	घड़ी->caps.adjसमय	= ptp_dp83640_adjसमय;
	घड़ी->caps.समय_लो64	= ptp_dp83640_समय_लो;
	घड़ी->caps.समय_रखो64	= ptp_dp83640_समय_रखो;
	घड़ी->caps.enable	= ptp_dp83640_enable;
	घड़ी->caps.verअगरy	= ptp_dp83640_verअगरy;
	/*
	 * Convert the module param शेषs पूर्णांकo a dynamic pin configuration.
	 */
	dp83640_gpio_शेषs(घड़ी->caps.pin_config);
	/*
	 * Get a reference to this bus instance.
	 */
	get_device(&bus->dev);
पूर्ण

अटल पूर्णांक choose_this_phy(काष्ठा dp83640_घड़ी *घड़ी,
			   काष्ठा phy_device *phydev)
अणु
	अगर (chosen_phy == -1 && !घड़ी->chosen)
		वापस 1;

	अगर (chosen_phy == phydev->mdio.addr)
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा dp83640_घड़ी *dp83640_घड़ी_get(काष्ठा dp83640_घड़ी *घड़ी)
अणु
	अगर (घड़ी)
		mutex_lock(&घड़ी->घड़ी_lock);
	वापस घड़ी;
पूर्ण

/*
 * Look up and lock a घड़ी by bus instance.
 * If there is no घड़ी क्रम this bus, then create it first.
 */
अटल काष्ठा dp83640_घड़ी *dp83640_घड़ी_get_bus(काष्ठा mii_bus *bus)
अणु
	काष्ठा dp83640_घड़ी *घड़ी = शून्य, *पंचांगp;
	काष्ठा list_head *this;

	mutex_lock(&phyter_घड़ीs_lock);

	list_क्रम_each(this, &phyter_घड़ीs) अणु
		पंचांगp = list_entry(this, काष्ठा dp83640_घड़ी, list);
		अगर (पंचांगp->bus == bus) अणु
			घड़ी = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (घड़ी)
		जाओ out;

	घड़ी = kzalloc(माप(काष्ठा dp83640_घड़ी), GFP_KERNEL);
	अगर (!घड़ी)
		जाओ out;

	घड़ी->caps.pin_config = kसुस्मृति(DP83640_N_PINS,
					 माप(काष्ठा ptp_pin_desc),
					 GFP_KERNEL);
	अगर (!घड़ी->caps.pin_config) अणु
		kमुक्त(घड़ी);
		घड़ी = शून्य;
		जाओ out;
	पूर्ण
	dp83640_घड़ी_init(घड़ी, bus);
	list_add_tail(&घड़ी->list, &phyter_घड़ीs);
out:
	mutex_unlock(&phyter_घड़ीs_lock);

	वापस dp83640_घड़ी_get(घड़ी);
पूर्ण

अटल व्योम dp83640_घड़ी_put(काष्ठा dp83640_घड़ी *घड़ी)
अणु
	mutex_unlock(&घड़ी->घड़ी_lock);
पूर्ण

अटल पूर्णांक dp83640_soft_reset(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = genphy_soft_reset(phydev);
	अगर (ret < 0)
		वापस ret;

	/* From DP83640 datasheet: "Software driver code must रुको 3 us
	 * following a software reset beक्रमe allowing further serial MII
	 * operations with the DP83640."
	 */
	udelay(10);		/* Taking udelay inaccuracy पूर्णांकo account */

	वापस 0;
पूर्ण

अटल पूर्णांक dp83640_config_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83640_निजी *dp83640 = phydev->priv;
	काष्ठा dp83640_घड़ी *घड़ी = dp83640->घड़ी;

	अगर (घड़ी->chosen && !list_empty(&घड़ी->phylist))
		recalibrate(घड़ी);
	अन्यथा अणु
		mutex_lock(&घड़ी->extreg_lock);
		enable_broadcast(phydev, घड़ी->page, 1);
		mutex_unlock(&घड़ी->extreg_lock);
	पूर्ण

	enable_status_frames(phydev, true);

	mutex_lock(&घड़ी->extreg_lock);
	ext_ग_लिखो(0, phydev, PAGE4, PTP_CTL, PTP_ENABLE);
	mutex_unlock(&घड़ी->extreg_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक dp83640_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err = phy_पढ़ो(phydev, MII_DP83640_MISR);

	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक dp83640_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक micr;
	पूर्णांक misr;
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = dp83640_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		misr = phy_पढ़ो(phydev, MII_DP83640_MISR);
		अगर (misr < 0)
			वापस misr;
		misr |=
			(MII_DP83640_MISR_ANC_INT_EN |
			MII_DP83640_MISR_DUP_INT_EN |
			MII_DP83640_MISR_SPD_INT_EN |
			MII_DP83640_MISR_LINK_INT_EN);
		err = phy_ग_लिखो(phydev, MII_DP83640_MISR, misr);
		अगर (err < 0)
			वापस err;

		micr = phy_पढ़ो(phydev, MII_DP83640_MICR);
		अगर (micr < 0)
			वापस micr;
		micr |=
			(MII_DP83640_MICR_OE |
			MII_DP83640_MICR_IE);
		वापस phy_ग_लिखो(phydev, MII_DP83640_MICR, micr);
	पूर्ण अन्यथा अणु
		micr = phy_पढ़ो(phydev, MII_DP83640_MICR);
		अगर (micr < 0)
			वापस micr;
		micr &=
			~(MII_DP83640_MICR_OE |
			MII_DP83640_MICR_IE);
		err = phy_ग_लिखो(phydev, MII_DP83640_MICR, micr);
		अगर (err < 0)
			वापस err;

		misr = phy_पढ़ो(phydev, MII_DP83640_MISR);
		अगर (misr < 0)
			वापस misr;
		misr &=
			~(MII_DP83640_MISR_ANC_INT_EN |
			MII_DP83640_MISR_DUP_INT_EN |
			MII_DP83640_MISR_SPD_INT_EN |
			MII_DP83640_MISR_LINK_INT_EN);
		err = phy_ग_लिखो(phydev, MII_DP83640_MISR, misr);
		अगर (err)
			वापस err;

		वापस dp83640_ack_पूर्णांकerrupt(phydev);
	पूर्ण
पूर्ण

अटल irqवापस_t dp83640_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_DP83640_MISR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & MII_DP83640_MISR_INT_MASK))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dp83640_hwtstamp(काष्ठा mii_बारtamper *mii_ts, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा dp83640_निजी *dp83640 =
		container_of(mii_ts, काष्ठा dp83640_निजी, mii_ts);
	काष्ठा hwtstamp_config cfg;
	u16 txcfg0, rxcfg0;

	अगर (copy_from_user(&cfg, अगरr->अगरr_data, माप(cfg)))
		वापस -EFAULT;

	अगर (cfg.flags) /* reserved क्रम future extensions */
		वापस -EINVAL;

	अगर (cfg.tx_type < 0 || cfg.tx_type > HWTSTAMP_TX_ONESTEP_SYNC)
		वापस -दुस्फल;

	dp83640->hwts_tx_en = cfg.tx_type;

	चयन (cfg.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		dp83640->hwts_rx_en = 0;
		dp83640->layer = 0;
		dp83640->version = 0;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		dp83640->hwts_rx_en = 1;
		dp83640->layer = PTP_CLASS_L4;
		dp83640->version = PTP_CLASS_V1;
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		dp83640->hwts_rx_en = 1;
		dp83640->layer = PTP_CLASS_L4;
		dp83640->version = PTP_CLASS_V2;
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		dp83640->hwts_rx_en = 1;
		dp83640->layer = PTP_CLASS_L2;
		dp83640->version = PTP_CLASS_V2;
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		dp83640->hwts_rx_en = 1;
		dp83640->layer = PTP_CLASS_L4 | PTP_CLASS_L2;
		dp83640->version = PTP_CLASS_V2;
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	txcfg0 = (dp83640->version & TX_PTP_VER_MASK) << TX_PTP_VER_SHIFT;
	rxcfg0 = (dp83640->version & TX_PTP_VER_MASK) << TX_PTP_VER_SHIFT;

	अगर (dp83640->layer & PTP_CLASS_L2) अणु
		txcfg0 |= TX_L2_EN;
		rxcfg0 |= RX_L2_EN;
	पूर्ण
	अगर (dp83640->layer & PTP_CLASS_L4) अणु
		txcfg0 |= TX_IPV6_EN | TX_IPV4_EN;
		rxcfg0 |= RX_IPV6_EN | RX_IPV4_EN;
	पूर्ण

	अगर (dp83640->hwts_tx_en)
		txcfg0 |= TX_TS_EN;

	अगर (dp83640->hwts_tx_en == HWTSTAMP_TX_ONESTEP_SYNC)
		txcfg0 |= SYNC_1STEP | CHK_1STEP;

	अगर (dp83640->hwts_rx_en)
		rxcfg0 |= RX_TS_EN;

	mutex_lock(&dp83640->घड़ी->extreg_lock);

	ext_ग_लिखो(0, dp83640->phydev, PAGE5, PTP_TXCFG0, txcfg0);
	ext_ग_लिखो(0, dp83640->phydev, PAGE5, PTP_RXCFG0, rxcfg0);

	mutex_unlock(&dp83640->घड़ी->extreg_lock);

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण

अटल व्योम rx_बारtamp_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dp83640_निजी *dp83640 =
		container_of(work, काष्ठा dp83640_निजी, ts_work.work);
	काष्ठा sk_buff *skb;

	/* Deliver expired packets. */
	जबतक ((skb = skb_dequeue(&dp83640->rx_queue))) अणु
		काष्ठा dp83640_skb_info *skb_info;

		skb_info = (काष्ठा dp83640_skb_info *)skb->cb;
		अगर (!समय_after(jअगरfies, skb_info->पंचांगo)) अणु
			skb_queue_head(&dp83640->rx_queue, skb);
			अवरोध;
		पूर्ण

		netअगर_rx_ni(skb);
	पूर्ण

	अगर (!skb_queue_empty(&dp83640->rx_queue))
		schedule_delayed_work(&dp83640->ts_work, SKB_TIMESTAMP_TIMEOUT);
पूर्ण

अटल bool dp83640_rxtstamp(काष्ठा mii_बारtamper *mii_ts,
			     काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा dp83640_निजी *dp83640 =
		container_of(mii_ts, काष्ठा dp83640_निजी, mii_ts);
	काष्ठा dp83640_skb_info *skb_info = (काष्ठा dp83640_skb_info *)skb->cb;
	काष्ठा list_head *this, *next;
	काष्ठा rxts *rxts;
	काष्ठा skb_shared_hwtstamps *shhwtstamps = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (is_status_frame(skb, type)) अणु
		decode_status_frame(dp83640, skb);
		kमुक्त_skb(skb);
		वापस true;
	पूर्ण

	अगर (!dp83640->hwts_rx_en)
		वापस false;

	अगर ((type & dp83640->version) == 0 || (type & dp83640->layer) == 0)
		वापस false;

	spin_lock_irqsave(&dp83640->rx_lock, flags);
	prune_rx_ts(dp83640);
	list_क्रम_each_safe(this, next, &dp83640->rxts) अणु
		rxts = list_entry(this, काष्ठा rxts, list);
		अगर (match(skb, type, rxts)) अणु
			shhwtstamps = skb_hwtstamps(skb);
			स_रखो(shhwtstamps, 0, माप(*shhwtstamps));
			shhwtstamps->hwtstamp = ns_to_kसमय(rxts->ns);
			list_del_init(&rxts->list);
			list_add(&rxts->list, &dp83640->rxpool);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dp83640->rx_lock, flags);

	अगर (!shhwtstamps) अणु
		skb_info->ptp_type = type;
		skb_info->पंचांगo = jअगरfies + SKB_TIMESTAMP_TIMEOUT;
		skb_queue_tail(&dp83640->rx_queue, skb);
		schedule_delayed_work(&dp83640->ts_work, SKB_TIMESTAMP_TIMEOUT);
	पूर्ण अन्यथा अणु
		netअगर_rx_ni(skb);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम dp83640_txtstamp(काष्ठा mii_बारtamper *mii_ts,
			     काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा dp83640_skb_info *skb_info = (काष्ठा dp83640_skb_info *)skb->cb;
	काष्ठा dp83640_निजी *dp83640 =
		container_of(mii_ts, काष्ठा dp83640_निजी, mii_ts);

	चयन (dp83640->hwts_tx_en) अणु

	हाल HWTSTAMP_TX_ONESTEP_SYNC:
		अगर (is_sync(skb, type)) अणु
			kमुक्त_skb(skb);
			वापस;
		पूर्ण
		fallthrough;
	हाल HWTSTAMP_TX_ON:
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		skb_info->पंचांगo = jअगरfies + SKB_TIMESTAMP_TIMEOUT;
		skb_queue_tail(&dp83640->tx_queue, skb);
		अवरोध;

	हाल HWTSTAMP_TX_OFF:
	शेष:
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक dp83640_ts_info(काष्ठा mii_बारtamper *mii_ts,
			   काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा dp83640_निजी *dp83640 =
		container_of(mii_ts, काष्ठा dp83640_निजी, mii_ts);

	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;
	info->phc_index = ptp_घड़ी_index(dp83640->घड़ी->ptp_घड़ी);
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON) |
		(1 << HWTSTAMP_TX_ONESTEP_SYNC);
	info->rx_filters =
		(1 << HWTSTAMP_FILTER_NONE) |
		(1 << HWTSTAMP_FILTER_PTP_V1_L4_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_EVENT);
	वापस 0;
पूर्ण

अटल पूर्णांक dp83640_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83640_घड़ी *घड़ी;
	काष्ठा dp83640_निजी *dp83640;
	पूर्णांक err = -ENOMEM, i;

	अगर (phydev->mdio.addr == BROADCAST_ADDR)
		वापस 0;

	घड़ी = dp83640_घड़ी_get_bus(phydev->mdio.bus);
	अगर (!घड़ी)
		जाओ no_घड़ी;

	dp83640 = kzalloc(माप(काष्ठा dp83640_निजी), GFP_KERNEL);
	अगर (!dp83640)
		जाओ no_memory;

	dp83640->phydev = phydev;
	dp83640->mii_ts.rxtstamp = dp83640_rxtstamp;
	dp83640->mii_ts.txtstamp = dp83640_txtstamp;
	dp83640->mii_ts.hwtstamp = dp83640_hwtstamp;
	dp83640->mii_ts.ts_info  = dp83640_ts_info;

	INIT_DELAYED_WORK(&dp83640->ts_work, rx_बारtamp_work);
	INIT_LIST_HEAD(&dp83640->rxts);
	INIT_LIST_HEAD(&dp83640->rxpool);
	क्रम (i = 0; i < MAX_RXTS; i++)
		list_add(&dp83640->rx_pool_data[i].list, &dp83640->rxpool);

	phydev->mii_ts = &dp83640->mii_ts;
	phydev->priv = dp83640;

	spin_lock_init(&dp83640->rx_lock);
	skb_queue_head_init(&dp83640->rx_queue);
	skb_queue_head_init(&dp83640->tx_queue);

	dp83640->घड़ी = घड़ी;

	अगर (choose_this_phy(घड़ी, phydev)) अणु
		घड़ी->chosen = dp83640;
		घड़ी->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&घड़ी->caps,
						      &phydev->mdio.dev);
		अगर (IS_ERR(घड़ी->ptp_घड़ी)) अणु
			err = PTR_ERR(घड़ी->ptp_घड़ी);
			जाओ no_रेजिस्टर;
		पूर्ण
	पूर्ण अन्यथा
		list_add_tail(&dp83640->list, &घड़ी->phylist);

	dp83640_घड़ी_put(घड़ी);
	वापस 0;

no_रेजिस्टर:
	घड़ी->chosen = शून्य;
	kमुक्त(dp83640);
no_memory:
	dp83640_घड़ी_put(घड़ी);
no_घड़ी:
	वापस err;
पूर्ण

अटल व्योम dp83640_हटाओ(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83640_घड़ी *घड़ी;
	काष्ठा list_head *this, *next;
	काष्ठा dp83640_निजी *पंचांगp, *dp83640 = phydev->priv;

	अगर (phydev->mdio.addr == BROADCAST_ADDR)
		वापस;

	phydev->mii_ts = शून्य;

	enable_status_frames(phydev, false);
	cancel_delayed_work_sync(&dp83640->ts_work);

	skb_queue_purge(&dp83640->rx_queue);
	skb_queue_purge(&dp83640->tx_queue);

	घड़ी = dp83640_घड़ी_get(dp83640->घड़ी);

	अगर (dp83640 == घड़ी->chosen) अणु
		ptp_घड़ी_unरेजिस्टर(घड़ी->ptp_घड़ी);
		घड़ी->chosen = शून्य;
	पूर्ण अन्यथा अणु
		list_क्रम_each_safe(this, next, &घड़ी->phylist) अणु
			पंचांगp = list_entry(this, काष्ठा dp83640_निजी, list);
			अगर (पंचांगp == dp83640) अणु
				list_del_init(&पंचांगp->list);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	dp83640_घड़ी_put(घड़ी);
	kमुक्त(dp83640);
पूर्ण

अटल काष्ठा phy_driver dp83640_driver = अणु
	.phy_id		= DP83640_PHY_ID,
	.phy_id_mask	= 0xfffffff0,
	.name		= "NatSemi DP83640",
	/* PHY_BASIC_FEATURES */
	.probe		= dp83640_probe,
	.हटाओ		= dp83640_हटाओ,
	.soft_reset	= dp83640_soft_reset,
	.config_init	= dp83640_config_init,
	.config_पूर्णांकr    = dp83640_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = dp83640_handle_पूर्णांकerrupt,
पूर्ण;

अटल पूर्णांक __init dp83640_init(व्योम)
अणु
	वापस phy_driver_रेजिस्टर(&dp83640_driver, THIS_MODULE);
पूर्ण

अटल व्योम __निकास dp83640_निकास(व्योम)
अणु
	dp83640_मुक्त_घड़ीs();
	phy_driver_unरेजिस्टर(&dp83640_driver);
पूर्ण

MODULE_DESCRIPTION("National Semiconductor DP83640 PHY driver");
MODULE_AUTHOR("Richard Cochran <richardcochran@gmail.com>");
MODULE_LICENSE("GPL");

module_init(dp83640_init);
module_निकास(dp83640_निकास);

अटल काष्ठा mdio_device_id __maybe_unused dp83640_tbl[] = अणु
	अणु DP83640_PHY_ID, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, dp83640_tbl);
