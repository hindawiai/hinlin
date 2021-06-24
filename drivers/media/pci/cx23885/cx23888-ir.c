<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX23885/7/8 PCIe bridge
 *
 *  CX23888 Integrated Consumer Infrared Controller
 *
 *  Copyright (C) 2009  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx23885.h"
#समावेश "cx23888-ir.h"

#समावेश <linux/kfअगरo.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/rc-core.h>

अटल अचिन्हित पूर्णांक ir_888_debug;
module_param(ir_888_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(ir_888_debug, "enable debug messages [CX23888 IR controller]");

#घोषणा CX23888_IR_REG_BASE	0x170000
/*
 * These CX23888 रेजिस्टर offsets have a straightक्रमward one to one mapping
 * to the CX23885 रेजिस्टर offsets of 0x200 through 0x218
 */
#घोषणा CX23888_IR_CNTRL_REG	0x170000
#घोषणा CNTRL_WIN_3_3	0x00000000
#घोषणा CNTRL_WIN_4_3	0x00000001
#घोषणा CNTRL_WIN_3_4	0x00000002
#घोषणा CNTRL_WIN_4_4	0x00000003
#घोषणा CNTRL_WIN	0x00000003
#घोषणा CNTRL_EDG_NONE	0x00000000
#घोषणा CNTRL_EDG_FALL	0x00000004
#घोषणा CNTRL_EDG_RISE	0x00000008
#घोषणा CNTRL_EDG_BOTH	0x0000000C
#घोषणा CNTRL_EDG	0x0000000C
#घोषणा CNTRL_DMD	0x00000010
#घोषणा CNTRL_MOD	0x00000020
#घोषणा CNTRL_RFE	0x00000040
#घोषणा CNTRL_TFE	0x00000080
#घोषणा CNTRL_RXE	0x00000100
#घोषणा CNTRL_TXE	0x00000200
#घोषणा CNTRL_RIC	0x00000400
#घोषणा CNTRL_TIC	0x00000800
#घोषणा CNTRL_CPL	0x00001000
#घोषणा CNTRL_LBM	0x00002000
#घोषणा CNTRL_R		0x00004000
/* CX23888 specअगरic control flag */
#घोषणा CNTRL_IVO	0x00008000

#घोषणा CX23888_IR_TXCLK_REG	0x170004
#घोषणा TXCLK_TCD	0x0000FFFF

#घोषणा CX23888_IR_RXCLK_REG	0x170008
#घोषणा RXCLK_RCD	0x0000FFFF

#घोषणा CX23888_IR_CDUTY_REG	0x17000C
#घोषणा CDUTY_CDC	0x0000000F

#घोषणा CX23888_IR_STATS_REG	0x170010
#घोषणा STATS_RTO	0x00000001
#घोषणा STATS_ROR	0x00000002
#घोषणा STATS_RBY	0x00000004
#घोषणा STATS_TBY	0x00000008
#घोषणा STATS_RSR	0x00000010
#घोषणा STATS_TSR	0x00000020

#घोषणा CX23888_IR_IRQEN_REG	0x170014
#घोषणा IRQEN_RTE	0x00000001
#घोषणा IRQEN_ROE	0x00000002
#घोषणा IRQEN_RSE	0x00000010
#घोषणा IRQEN_TSE	0x00000020

#घोषणा CX23888_IR_FILTR_REG	0x170018
#घोषणा FILTR_LPF	0x0000FFFF

/* This रेजिस्टर करोesn't follow the pattern; it's 0x23C on a CX23885 */
#घोषणा CX23888_IR_FIFO_REG	0x170040
#घोषणा FIFO_RXTX	0x0000FFFF
#घोषणा FIFO_RXTX_LVL	0x00010000
#घोषणा FIFO_RXTX_RTO	0x0001FFFF
#घोषणा FIFO_RX_NDV	0x00020000
#घोषणा FIFO_RX_DEPTH	8
#घोषणा FIFO_TX_DEPTH	8

/* CX23888 unique रेजिस्टरs */
#घोषणा CX23888_IR_SEEDP_REG	0x17001C
#घोषणा CX23888_IR_TIMOL_REG	0x170020
#घोषणा CX23888_IR_WAKE0_REG	0x170024
#घोषणा CX23888_IR_WAKE1_REG	0x170028
#घोषणा CX23888_IR_WAKE2_REG	0x17002C
#घोषणा CX23888_IR_MASK0_REG	0x170030
#घोषणा CX23888_IR_MASK1_REG	0x170034
#घोषणा CX23888_IR_MAKS2_REG	0x170038
#घोषणा CX23888_IR_DPIPG_REG	0x17003C
#घोषणा CX23888_IR_LEARN_REG	0x170044

#घोषणा CX23888_VIDCLK_FREQ	108000000 /* 108 MHz, BT.656 */
#घोषणा CX23888_IR_REFCLK_FREQ	(CX23888_VIDCLK_FREQ / 2)

/*
 * We use this जोड़ पूर्णांकernally क्रम convenience, but callers to tx_ग_लिखो
 * and rx_पढ़ो will be expecting records of type काष्ठा ir_raw_event.
 * Always ensure the size of this जोड़ is dictated by काष्ठा ir_raw_event.
 */
जोड़ cx23888_ir_fअगरo_rec अणु
	u32 hw_fअगरo_data;
	काष्ठा ir_raw_event ir_core_data;
पूर्ण;

#घोषणा CX23888_IR_RX_KFIFO_SIZE    (256 * माप(जोड़ cx23888_ir_fअगरo_rec))
#घोषणा CX23888_IR_TX_KFIFO_SIZE    (256 * माप(जोड़ cx23888_ir_fअगरo_rec))

काष्ठा cx23888_ir_state अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा cx23885_dev *dev;

	काष्ठा v4l2_subdev_ir_parameters rx_params;
	काष्ठा mutex rx_params_lock;
	atomic_t rxclk_भागider;
	atomic_t rx_invert;

	काष्ठा kfअगरo rx_kfअगरo;
	spinlock_t rx_kfअगरo_lock;

	काष्ठा v4l2_subdev_ir_parameters tx_params;
	काष्ठा mutex tx_params_lock;
	atomic_t txclk_भागider;
पूर्ण;

अटल अंतरभूत काष्ठा cx23888_ir_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस v4l2_get_subdevdata(sd);
पूर्ण

/*
 * IR रेजिस्टर block पढ़ो and ग_लिखो functions
 */
अटल
अंतरभूत पूर्णांक cx23888_ir_ग_लिखो4(काष्ठा cx23885_dev *dev, u32 addr, u32 value)
अणु
	cx_ग_लिखो(addr, value);
	वापस 0;
पूर्ण

अटल अंतरभूत u32 cx23888_ir_पढ़ो4(काष्ठा cx23885_dev *dev, u32 addr)
अणु
	वापस cx_पढ़ो(addr);
पूर्ण

अटल अंतरभूत पूर्णांक cx23888_ir_and_or4(काष्ठा cx23885_dev *dev, u32 addr,
				     u32 and_mask, u32 or_value)
अणु
	cx_anकरोr(addr, ~and_mask, or_value);
	वापस 0;
पूर्ण

/*
 * Rx and Tx Clock Divider रेजिस्टर computations
 *
 * Note the largest घड़ी भागider value of 0xffff corresponds to:
 *	(0xffff + 1) * 1000 / 108/2 MHz = 1,213,629.629... ns
 * which fits in 21 bits, so we'll use अचिन्हित पूर्णांक क्रम समय arguments.
 */
अटल अंतरभूत u16 count_to_घड़ी_भागider(अचिन्हित पूर्णांक d)
अणु
	अगर (d > RXCLK_RCD + 1)
		d = RXCLK_RCD;
	अन्यथा अगर (d < 2)
		d = 1;
	अन्यथा
		d--;
	वापस (u16) d;
पूर्ण

अटल अंतरभूत u16 carrier_freq_to_घड़ी_भागider(अचिन्हित पूर्णांक freq)
अणु
	वापस count_to_घड़ी_भागider(
			  DIV_ROUND_CLOSEST(CX23888_IR_REFCLK_FREQ, freq * 16));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक घड़ी_भागider_to_carrier_freq(अचिन्हित पूर्णांक भागider)
अणु
	वापस DIV_ROUND_CLOSEST(CX23888_IR_REFCLK_FREQ, (भागider + 1) * 16);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक घड़ी_भागider_to_freq(अचिन्हित पूर्णांक भागider,
						 अचिन्हित पूर्णांक rollovers)
अणु
	वापस DIV_ROUND_CLOSEST(CX23888_IR_REFCLK_FREQ,
				 (भागider + 1) * rollovers);
पूर्ण

/*
 * Low Pass Filter रेजिस्टर calculations
 *
 * Note the largest count value of 0xffff corresponds to:
 *	0xffff * 1000 / 108/2 MHz = 1,213,611.11... ns
 * which fits in 21 bits, so we'll use अचिन्हित पूर्णांक क्रम समय arguments.
 */
अटल अंतरभूत u16 count_to_lpf_count(अचिन्हित पूर्णांक d)
अणु
	अगर (d > FILTR_LPF)
		d = FILTR_LPF;
	अन्यथा अगर (d < 4)
		d = 0;
	वापस (u16) d;
पूर्ण

अटल अंतरभूत u16 ns_to_lpf_count(अचिन्हित पूर्णांक ns)
अणु
	वापस count_to_lpf_count(
		DIV_ROUND_CLOSEST(CX23888_IR_REFCLK_FREQ / 1000000 * ns, 1000));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक lpf_count_to_ns(अचिन्हित पूर्णांक count)
अणु
	/* Duration of the Low Pass Filter rejection winकरोw in ns */
	वापस DIV_ROUND_CLOSEST(count * 1000,
				 CX23888_IR_REFCLK_FREQ / 1000000);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक lpf_count_to_us(अचिन्हित पूर्णांक count)
अणु
	/* Duration of the Low Pass Filter rejection winकरोw in us */
	वापस DIV_ROUND_CLOSEST(count, CX23888_IR_REFCLK_FREQ / 1000000);
पूर्ण

/*
 * FIFO रेजिस्टर pulse width count computations
 */
अटल u32 घड़ी_भागider_to_resolution(u16 भागider)
अणु
	/*
	 * Resolution is the duration of 1 tick of the पढ़ोable portion of
	 * of the pulse width counter as पढ़ो from the FIFO.  The two lsb's are
	 * not पढ़ोable, hence the << 2.  This function वापसs ns.
	 */
	वापस DIV_ROUND_CLOSEST((1 << 2)  * ((u32) भागider + 1) * 1000,
				 CX23888_IR_REFCLK_FREQ / 1000000);
पूर्ण

अटल u64 pulse_width_count_to_ns(u16 count, u16 भागider)
अणु
	u64 n;
	u32 rem;

	/*
	 * The 2 lsb's of the pulse width समयr count are not पढ़ोable, hence
	 * the (count << 2) | 0x3
	 */
	n = (((u64) count << 2) | 0x3) * (भागider + 1) * 1000; /* millicycles */
	rem = करो_भाग(n, CX23888_IR_REFCLK_FREQ / 1000000);     /* / MHz => ns */
	अगर (rem >= CX23888_IR_REFCLK_FREQ / 1000000 / 2)
		n++;
	वापस n;
पूर्ण

अटल अचिन्हित पूर्णांक pulse_width_count_to_us(u16 count, u16 भागider)
अणु
	u64 n;
	u32 rem;

	/*
	 * The 2 lsb's of the pulse width समयr count are not पढ़ोable, hence
	 * the (count << 2) | 0x3
	 */
	n = (((u64) count << 2) | 0x3) * (भागider + 1);    /* cycles      */
	rem = करो_भाग(n, CX23888_IR_REFCLK_FREQ / 1000000); /* / MHz => us */
	अगर (rem >= CX23888_IR_REFCLK_FREQ / 1000000 / 2)
		n++;
	वापस (अचिन्हित पूर्णांक) n;
पूर्ण

/*
 * Pulse Clocks computations: Combined Pulse Width Count & Rx Clock Counts
 *
 * The total pulse घड़ी count is an 18 bit pulse width समयr count as the most
 * signअगरicant part and (up to) 16 bit घड़ी भागider count as a modulus.
 * When the Rx घड़ी भागider ticks करोwn to 0, it increments the 18 bit pulse
 * width समयr count's least signअगरicant bit.
 */
अटल u64 ns_to_pulse_घड़ीs(u32 ns)
अणु
	u64 घड़ीs;
	u32 rem;
	घड़ीs = CX23888_IR_REFCLK_FREQ / 1000000 * (u64) ns; /* millicycles  */
	rem = करो_भाग(घड़ीs, 1000);                         /* /1000 = cycles */
	अगर (rem >= 1000 / 2)
		घड़ीs++;
	वापस घड़ीs;
पूर्ण

अटल u16 pulse_घड़ीs_to_घड़ी_भागider(u64 count)
अणु
	करो_भाग(count, (FIFO_RXTX << 2) | 0x3);

	/* net result needs to be rounded करोwn and decremented by 1 */
	अगर (count > RXCLK_RCD + 1)
		count = RXCLK_RCD;
	अन्यथा अगर (count < 2)
		count = 1;
	अन्यथा
		count--;
	वापस (u16) count;
पूर्ण

/*
 * IR Control Register helpers
 */
क्रमागत tx_fअगरo_watermark अणु
	TX_FIFO_HALF_EMPTY = 0,
	TX_FIFO_EMPTY      = CNTRL_TIC,
पूर्ण;

क्रमागत rx_fअगरo_watermark अणु
	RX_FIFO_HALF_FULL = 0,
	RX_FIFO_NOT_EMPTY = CNTRL_RIC,
पूर्ण;

अटल अंतरभूत व्योम control_tx_irq_watermark(काष्ठा cx23885_dev *dev,
					    क्रमागत tx_fअगरo_watermark level)
अणु
	cx23888_ir_and_or4(dev, CX23888_IR_CNTRL_REG, ~CNTRL_TIC, level);
पूर्ण

अटल अंतरभूत व्योम control_rx_irq_watermark(काष्ठा cx23885_dev *dev,
					    क्रमागत rx_fअगरo_watermark level)
अणु
	cx23888_ir_and_or4(dev, CX23888_IR_CNTRL_REG, ~CNTRL_RIC, level);
पूर्ण

अटल अंतरभूत व्योम control_tx_enable(काष्ठा cx23885_dev *dev, bool enable)
अणु
	cx23888_ir_and_or4(dev, CX23888_IR_CNTRL_REG, ~(CNTRL_TXE | CNTRL_TFE),
			   enable ? (CNTRL_TXE | CNTRL_TFE) : 0);
पूर्ण

अटल अंतरभूत व्योम control_rx_enable(काष्ठा cx23885_dev *dev, bool enable)
अणु
	cx23888_ir_and_or4(dev, CX23888_IR_CNTRL_REG, ~(CNTRL_RXE | CNTRL_RFE),
			   enable ? (CNTRL_RXE | CNTRL_RFE) : 0);
पूर्ण

अटल अंतरभूत व्योम control_tx_modulation_enable(काष्ठा cx23885_dev *dev,
						bool enable)
अणु
	cx23888_ir_and_or4(dev, CX23888_IR_CNTRL_REG, ~CNTRL_MOD,
			   enable ? CNTRL_MOD : 0);
पूर्ण

अटल अंतरभूत व्योम control_rx_demodulation_enable(काष्ठा cx23885_dev *dev,
						  bool enable)
अणु
	cx23888_ir_and_or4(dev, CX23888_IR_CNTRL_REG, ~CNTRL_DMD,
			   enable ? CNTRL_DMD : 0);
पूर्ण

अटल अंतरभूत व्योम control_rx_s_edge_detection(काष्ठा cx23885_dev *dev,
					       u32 edge_types)
अणु
	cx23888_ir_and_or4(dev, CX23888_IR_CNTRL_REG, ~CNTRL_EDG_BOTH,
			   edge_types & CNTRL_EDG_BOTH);
पूर्ण

अटल व्योम control_rx_s_carrier_winकरोw(काष्ठा cx23885_dev *dev,
					अचिन्हित पूर्णांक carrier,
					अचिन्हित पूर्णांक *carrier_range_low,
					अचिन्हित पूर्णांक *carrier_range_high)
अणु
	u32 v;
	अचिन्हित पूर्णांक c16 = carrier * 16;

	अगर (*carrier_range_low < DIV_ROUND_CLOSEST(c16, 16 + 3)) अणु
		v = CNTRL_WIN_3_4;
		*carrier_range_low = DIV_ROUND_CLOSEST(c16, 16 + 4);
	पूर्ण अन्यथा अणु
		v = CNTRL_WIN_3_3;
		*carrier_range_low = DIV_ROUND_CLOSEST(c16, 16 + 3);
	पूर्ण

	अगर (*carrier_range_high > DIV_ROUND_CLOSEST(c16, 16 - 3)) अणु
		v |= CNTRL_WIN_4_3;
		*carrier_range_high = DIV_ROUND_CLOSEST(c16, 16 - 4);
	पूर्ण अन्यथा अणु
		v |= CNTRL_WIN_3_3;
		*carrier_range_high = DIV_ROUND_CLOSEST(c16, 16 - 3);
	पूर्ण
	cx23888_ir_and_or4(dev, CX23888_IR_CNTRL_REG, ~CNTRL_WIN, v);
पूर्ण

अटल अंतरभूत व्योम control_tx_polarity_invert(काष्ठा cx23885_dev *dev,
					      bool invert)
अणु
	cx23888_ir_and_or4(dev, CX23888_IR_CNTRL_REG, ~CNTRL_CPL,
			   invert ? CNTRL_CPL : 0);
पूर्ण

अटल अंतरभूत व्योम control_tx_level_invert(काष्ठा cx23885_dev *dev,
					  bool invert)
अणु
	cx23888_ir_and_or4(dev, CX23888_IR_CNTRL_REG, ~CNTRL_IVO,
			   invert ? CNTRL_IVO : 0);
पूर्ण

/*
 * IR Rx & Tx Clock Register helpers
 */
अटल अचिन्हित पूर्णांक txclk_tx_s_carrier(काष्ठा cx23885_dev *dev,
				       अचिन्हित पूर्णांक freq,
				       u16 *भागider)
अणु
	*भागider = carrier_freq_to_घड़ी_भागider(freq);
	cx23888_ir_ग_लिखो4(dev, CX23888_IR_TXCLK_REG, *भागider);
	वापस घड़ी_भागider_to_carrier_freq(*भागider);
पूर्ण

अटल अचिन्हित पूर्णांक rxclk_rx_s_carrier(काष्ठा cx23885_dev *dev,
				       अचिन्हित पूर्णांक freq,
				       u16 *भागider)
अणु
	*भागider = carrier_freq_to_घड़ी_भागider(freq);
	cx23888_ir_ग_लिखो4(dev, CX23888_IR_RXCLK_REG, *भागider);
	वापस घड़ी_भागider_to_carrier_freq(*भागider);
पूर्ण

अटल u32 txclk_tx_s_max_pulse_width(काष्ठा cx23885_dev *dev, u32 ns,
				      u16 *भागider)
अणु
	u64 pulse_घड़ीs;

	अगर (ns > IR_MAX_DURATION)
		ns = IR_MAX_DURATION;
	pulse_घड़ीs = ns_to_pulse_घड़ीs(ns);
	*भागider = pulse_घड़ीs_to_घड़ी_भागider(pulse_घड़ीs);
	cx23888_ir_ग_लिखो4(dev, CX23888_IR_TXCLK_REG, *भागider);
	वापस (u32) pulse_width_count_to_ns(FIFO_RXTX, *भागider);
पूर्ण

अटल u32 rxclk_rx_s_max_pulse_width(काष्ठा cx23885_dev *dev, u32 ns,
				      u16 *भागider)
अणु
	u64 pulse_घड़ीs;

	अगर (ns > IR_MAX_DURATION)
		ns = IR_MAX_DURATION;
	pulse_घड़ीs = ns_to_pulse_घड़ीs(ns);
	*भागider = pulse_घड़ीs_to_घड़ी_भागider(pulse_घड़ीs);
	cx23888_ir_ग_लिखो4(dev, CX23888_IR_RXCLK_REG, *भागider);
	वापस (u32) pulse_width_count_to_ns(FIFO_RXTX, *भागider);
पूर्ण

/*
 * IR Tx Carrier Duty Cycle रेजिस्टर helpers
 */
अटल अचिन्हित पूर्णांक cduty_tx_s_duty_cycle(काष्ठा cx23885_dev *dev,
					  अचिन्हित पूर्णांक duty_cycle)
अणु
	u32 n;
	n = DIV_ROUND_CLOSEST(duty_cycle * 100, 625); /* 16ths of 100% */
	अगर (n != 0)
		n--;
	अगर (n > 15)
		n = 15;
	cx23888_ir_ग_लिखो4(dev, CX23888_IR_CDUTY_REG, n);
	वापस DIV_ROUND_CLOSEST((n + 1) * 100, 16);
पूर्ण

/*
 * IR Filter Register helpers
 */
अटल u32 filter_rx_s_min_width(काष्ठा cx23885_dev *dev, u32 min_width_ns)
अणु
	u32 count = ns_to_lpf_count(min_width_ns);
	cx23888_ir_ग_लिखो4(dev, CX23888_IR_FILTR_REG, count);
	वापस lpf_count_to_ns(count);
पूर्ण

/*
 * IR IRQ Enable Register helpers
 */
अटल अंतरभूत व्योम irqenable_rx(काष्ठा cx23885_dev *dev, u32 mask)
अणु
	mask &= (IRQEN_RTE | IRQEN_ROE | IRQEN_RSE);
	cx23888_ir_and_or4(dev, CX23888_IR_IRQEN_REG,
			   ~(IRQEN_RTE | IRQEN_ROE | IRQEN_RSE), mask);
पूर्ण

अटल अंतरभूत व्योम irqenable_tx(काष्ठा cx23885_dev *dev, u32 mask)
अणु
	mask &= IRQEN_TSE;
	cx23888_ir_and_or4(dev, CX23888_IR_IRQEN_REG, ~IRQEN_TSE, mask);
पूर्ण

/*
 * V4L2 Subdevice IR Ops
 */
अटल पूर्णांक cx23888_ir_irq_handler(काष्ठा v4l2_subdev *sd, u32 status,
				  bool *handled)
अणु
	काष्ठा cx23888_ir_state *state = to_state(sd);
	काष्ठा cx23885_dev *dev = state->dev;
	अचिन्हित दीर्घ flags;

	u32 cntrl = cx23888_ir_पढ़ो4(dev, CX23888_IR_CNTRL_REG);
	u32 irqen = cx23888_ir_पढ़ो4(dev, CX23888_IR_IRQEN_REG);
	u32 stats = cx23888_ir_पढ़ो4(dev, CX23888_IR_STATS_REG);

	जोड़ cx23888_ir_fअगरo_rec rx_data[FIFO_RX_DEPTH];
	अचिन्हित पूर्णांक i, j, k;
	u32 events, v;
	पूर्णांक tsr, rsr, rto, ror, tse, rse, rte, roe, kror;

	tsr = stats & STATS_TSR; /* Tx FIFO Service Request */
	rsr = stats & STATS_RSR; /* Rx FIFO Service Request */
	rto = stats & STATS_RTO; /* Rx Pulse Width Timer Time Out */
	ror = stats & STATS_ROR; /* Rx FIFO Over Run */

	tse = irqen & IRQEN_TSE; /* Tx FIFO Service Request IRQ Enable */
	rse = irqen & IRQEN_RSE; /* Rx FIFO Service Request IRQ Enable */
	rte = irqen & IRQEN_RTE; /* Rx Pulse Width Timer Time Out IRQ Enable */
	roe = irqen & IRQEN_ROE; /* Rx FIFO Over Run IRQ Enable */

	*handled = false;
	v4l2_dbg(2, ir_888_debug, sd, "IRQ Status:  %s %s %s %s %s %s\n",
		 tsr ? "tsr" : "   ", rsr ? "rsr" : "   ",
		 rto ? "rto" : "   ", ror ? "ror" : "   ",
		 stats & STATS_TBY ? "tby" : "   ",
		 stats & STATS_RBY ? "rby" : "   ");

	v4l2_dbg(2, ir_888_debug, sd, "IRQ Enables: %s %s %s %s\n",
		 tse ? "tse" : "   ", rse ? "rse" : "   ",
		 rte ? "rte" : "   ", roe ? "roe" : "   ");

	/*
	 * Transmitter पूर्णांकerrupt service
	 */
	अगर (tse && tsr) अणु
		/*
		 * TODO:
		 * Check the watermark threshold setting
		 * Pull FIFO_TX_DEPTH or FIFO_TX_DEPTH/2 entries from tx_kfअगरo
		 * Push the data to the hardware FIFO.
		 * If there was nothing more to send in the tx_kfअगरo, disable
		 *	the TSR IRQ and notअगरy the v4l2_device.
		 * If there was something in the tx_kfअगरo, check the tx_kfअगरo
		 *      level and notअगरy the v4l2_device, अगर it is low.
		 */
		/* For now, inhibit TSR पूर्णांकerrupt until Tx is implemented */
		irqenable_tx(dev, 0);
		events = V4L2_SUBDEV_IR_TX_FIFO_SERVICE_REQ;
		v4l2_subdev_notअगरy(sd, V4L2_SUBDEV_IR_TX_NOTIFY, &events);
		*handled = true;
	पूर्ण

	/*
	 * Receiver पूर्णांकerrupt service
	 */
	kror = 0;
	अगर ((rse && rsr) || (rte && rto)) अणु
		/*
		 * Receive data on RSR to clear the STATS_RSR.
		 * Receive data on RTO, since we may not have yet hit the RSR
		 * watermark when we receive the RTO.
		 */
		क्रम (i = 0, v = FIFO_RX_NDV;
		     (v & FIFO_RX_NDV) && !kror; i = 0) अणु
			क्रम (j = 0;
			     (v & FIFO_RX_NDV) && j < FIFO_RX_DEPTH; j++) अणु
				v = cx23888_ir_पढ़ो4(dev, CX23888_IR_FIFO_REG);
				rx_data[i].hw_fअगरo_data = v & ~FIFO_RX_NDV;
				i++;
			पूर्ण
			अगर (i == 0)
				अवरोध;
			j = i * माप(जोड़ cx23888_ir_fअगरo_rec);
			k = kfअगरo_in_locked(&state->rx_kfअगरo,
				      (अचिन्हित अक्षर *) rx_data, j,
				      &state->rx_kfअगरo_lock);
			अगर (k != j)
				kror++; /* rx_kfअगरo over run */
		पूर्ण
		*handled = true;
	पूर्ण

	events = 0;
	v = 0;
	अगर (kror) अणु
		events |= V4L2_SUBDEV_IR_RX_SW_FIFO_OVERRUN;
		v4l2_err(sd, "IR receiver software FIFO overrun\n");
	पूर्ण
	अगर (roe && ror) अणु
		/*
		 * The RX FIFO Enable (CNTRL_RFE) must be toggled to clear
		 * the Rx FIFO Over Run status (STATS_ROR)
		 */
		v |= CNTRL_RFE;
		events |= V4L2_SUBDEV_IR_RX_HW_FIFO_OVERRUN;
		v4l2_err(sd, "IR receiver hardware FIFO overrun\n");
	पूर्ण
	अगर (rte && rto) अणु
		/*
		 * The IR Receiver Enable (CNTRL_RXE) must be toggled to clear
		 * the Rx Pulse Width Timer Time Out (STATS_RTO)
		 */
		v |= CNTRL_RXE;
		events |= V4L2_SUBDEV_IR_RX_END_OF_RX_DETECTED;
	पूर्ण
	अगर (v) अणु
		/* Clear STATS_ROR & STATS_RTO as needed by resetting hardware */
		cx23888_ir_ग_लिखो4(dev, CX23888_IR_CNTRL_REG, cntrl & ~v);
		cx23888_ir_ग_लिखो4(dev, CX23888_IR_CNTRL_REG, cntrl);
		*handled = true;
	पूर्ण

	spin_lock_irqsave(&state->rx_kfअगरo_lock, flags);
	अगर (kfअगरo_len(&state->rx_kfअगरo) >= CX23888_IR_RX_KFIFO_SIZE / 2)
		events |= V4L2_SUBDEV_IR_RX_FIFO_SERVICE_REQ;
	spin_unlock_irqrestore(&state->rx_kfअगरo_lock, flags);

	अगर (events)
		v4l2_subdev_notअगरy(sd, V4L2_SUBDEV_IR_RX_NOTIFY, &events);
	वापस 0;
पूर्ण

/* Receiver */
अटल पूर्णांक cx23888_ir_rx_पढ़ो(काष्ठा v4l2_subdev *sd, u8 *buf, माप_प्रकार count,
			      sमाप_प्रकार *num)
अणु
	काष्ठा cx23888_ir_state *state = to_state(sd);
	bool invert = (bool) atomic_पढ़ो(&state->rx_invert);
	u16 भागider = (u16) atomic_पढ़ो(&state->rxclk_भागider);

	अचिन्हित पूर्णांक i, n;
	जोड़ cx23888_ir_fअगरo_rec *p;
	अचिन्हित u, v, w;

	n = count / माप(जोड़ cx23888_ir_fअगरo_rec)
		* माप(जोड़ cx23888_ir_fअगरo_rec);
	अगर (n == 0) अणु
		*num = 0;
		वापस 0;
	पूर्ण

	n = kfअगरo_out_locked(&state->rx_kfअगरo, buf, n, &state->rx_kfअगरo_lock);

	n /= माप(जोड़ cx23888_ir_fअगरo_rec);
	*num = n * माप(जोड़ cx23888_ir_fअगरo_rec);

	क्रम (p = (जोड़ cx23888_ir_fअगरo_rec *) buf, i = 0; i < n; p++, i++) अणु

		अगर ((p->hw_fअगरo_data & FIFO_RXTX_RTO) == FIFO_RXTX_RTO) अणु
			/* Assume RTO was because of no IR light input */
			u = 0;
			w = 1;
		पूर्ण अन्यथा अणु
			u = (p->hw_fअगरo_data & FIFO_RXTX_LVL) ? 1 : 0;
			अगर (invert)
				u = u ? 0 : 1;
			w = 0;
		पूर्ण

		v = (अचिन्हित) pulse_width_count_to_ns(
				  (u16)(p->hw_fअगरo_data & FIFO_RXTX), भागider) / 1000;
		अगर (v > IR_MAX_DURATION)
			v = IR_MAX_DURATION;

		p->ir_core_data = (काष्ठा ir_raw_event)
			अणु .pulse = u, .duration = v, .समयout = w पूर्ण;

		v4l2_dbg(2, ir_888_debug, sd, "rx read: %10u ns  %s  %s\n",
			 v, u ? "mark" : "space", w ? "(timed out)" : "");
		अगर (w)
			v4l2_dbg(2, ir_888_debug, sd, "rx read: end of rx\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx23888_ir_rx_g_parameters(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_ir_parameters *p)
अणु
	काष्ठा cx23888_ir_state *state = to_state(sd);
	mutex_lock(&state->rx_params_lock);
	स_नकल(p, &state->rx_params, माप(काष्ठा v4l2_subdev_ir_parameters));
	mutex_unlock(&state->rx_params_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक cx23888_ir_rx_shutकरोwn(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा cx23888_ir_state *state = to_state(sd);
	काष्ठा cx23885_dev *dev = state->dev;

	mutex_lock(&state->rx_params_lock);

	/* Disable or slow करोwn all IR Rx circuits and counters */
	irqenable_rx(dev, 0);
	control_rx_enable(dev, false);
	control_rx_demodulation_enable(dev, false);
	control_rx_s_edge_detection(dev, CNTRL_EDG_NONE);
	filter_rx_s_min_width(dev, 0);
	cx23888_ir_ग_लिखो4(dev, CX23888_IR_RXCLK_REG, RXCLK_RCD);

	state->rx_params.shutकरोwn = true;

	mutex_unlock(&state->rx_params_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक cx23888_ir_rx_s_parameters(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_ir_parameters *p)
अणु
	काष्ठा cx23888_ir_state *state = to_state(sd);
	काष्ठा cx23885_dev *dev = state->dev;
	काष्ठा v4l2_subdev_ir_parameters *o = &state->rx_params;
	u16 rxclk_भागider;

	अगर (p->shutकरोwn)
		वापस cx23888_ir_rx_shutकरोwn(sd);

	अगर (p->mode != V4L2_SUBDEV_IR_MODE_PULSE_WIDTH)
		वापस -ENOSYS;

	mutex_lock(&state->rx_params_lock);

	o->shutकरोwn = p->shutकरोwn;

	o->mode = p->mode = V4L2_SUBDEV_IR_MODE_PULSE_WIDTH;

	o->bytes_per_data_element = p->bytes_per_data_element
				  = माप(जोड़ cx23888_ir_fअगरo_rec);

	/* Beक्रमe we tweak the hardware, we have to disable the receiver */
	irqenable_rx(dev, 0);
	control_rx_enable(dev, false);

	control_rx_demodulation_enable(dev, p->modulation);
	o->modulation = p->modulation;

	अगर (p->modulation) अणु
		p->carrier_freq = rxclk_rx_s_carrier(dev, p->carrier_freq,
						     &rxclk_भागider);

		o->carrier_freq = p->carrier_freq;

		o->duty_cycle = p->duty_cycle = 50;

		control_rx_s_carrier_winकरोw(dev, p->carrier_freq,
					    &p->carrier_range_lower,
					    &p->carrier_range_upper);
		o->carrier_range_lower = p->carrier_range_lower;
		o->carrier_range_upper = p->carrier_range_upper;

		p->max_pulse_width =
			(u32) pulse_width_count_to_ns(FIFO_RXTX, rxclk_भागider);
	पूर्ण अन्यथा अणु
		p->max_pulse_width =
			    rxclk_rx_s_max_pulse_width(dev, p->max_pulse_width,
						       &rxclk_भागider);
	पूर्ण
	o->max_pulse_width = p->max_pulse_width;
	atomic_set(&state->rxclk_भागider, rxclk_भागider);

	p->noise_filter_min_width =
			  filter_rx_s_min_width(dev, p->noise_filter_min_width);
	o->noise_filter_min_width = p->noise_filter_min_width;

	p->resolution = घड़ी_भागider_to_resolution(rxclk_भागider);
	o->resolution = p->resolution;

	/* FIXME - make this dependent on resolution क्रम better perक्रमmance */
	control_rx_irq_watermark(dev, RX_FIFO_HALF_FULL);

	control_rx_s_edge_detection(dev, CNTRL_EDG_BOTH);

	o->invert_level = p->invert_level;
	atomic_set(&state->rx_invert, p->invert_level);

	o->पूर्णांकerrupt_enable = p->पूर्णांकerrupt_enable;
	o->enable = p->enable;
	अगर (p->enable) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&state->rx_kfअगरo_lock, flags);
		kfअगरo_reset(&state->rx_kfअगरo);
		/* reset tx_fअगरo too अगर there is one... */
		spin_unlock_irqrestore(&state->rx_kfअगरo_lock, flags);
		अगर (p->पूर्णांकerrupt_enable)
			irqenable_rx(dev, IRQEN_RSE | IRQEN_RTE | IRQEN_ROE);
		control_rx_enable(dev, p->enable);
	पूर्ण

	mutex_unlock(&state->rx_params_lock);
	वापस 0;
पूर्ण

/* Transmitter */
अटल पूर्णांक cx23888_ir_tx_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 *buf, माप_प्रकार count,
			       sमाप_प्रकार *num)
अणु
	काष्ठा cx23888_ir_state *state = to_state(sd);
	काष्ठा cx23885_dev *dev = state->dev;
	/* For now enable the Tx FIFO Service पूर्णांकerrupt & pretend we did work */
	irqenable_tx(dev, IRQEN_TSE);
	*num = count;
	वापस 0;
पूर्ण

अटल पूर्णांक cx23888_ir_tx_g_parameters(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_ir_parameters *p)
अणु
	काष्ठा cx23888_ir_state *state = to_state(sd);
	mutex_lock(&state->tx_params_lock);
	स_नकल(p, &state->tx_params, माप(काष्ठा v4l2_subdev_ir_parameters));
	mutex_unlock(&state->tx_params_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक cx23888_ir_tx_shutकरोwn(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा cx23888_ir_state *state = to_state(sd);
	काष्ठा cx23885_dev *dev = state->dev;

	mutex_lock(&state->tx_params_lock);

	/* Disable or slow करोwn all IR Tx circuits and counters */
	irqenable_tx(dev, 0);
	control_tx_enable(dev, false);
	control_tx_modulation_enable(dev, false);
	cx23888_ir_ग_लिखो4(dev, CX23888_IR_TXCLK_REG, TXCLK_TCD);

	state->tx_params.shutकरोwn = true;

	mutex_unlock(&state->tx_params_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक cx23888_ir_tx_s_parameters(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_ir_parameters *p)
अणु
	काष्ठा cx23888_ir_state *state = to_state(sd);
	काष्ठा cx23885_dev *dev = state->dev;
	काष्ठा v4l2_subdev_ir_parameters *o = &state->tx_params;
	u16 txclk_भागider;

	अगर (p->shutकरोwn)
		वापस cx23888_ir_tx_shutकरोwn(sd);

	अगर (p->mode != V4L2_SUBDEV_IR_MODE_PULSE_WIDTH)
		वापस -ENOSYS;

	mutex_lock(&state->tx_params_lock);

	o->shutकरोwn = p->shutकरोwn;

	o->mode = p->mode = V4L2_SUBDEV_IR_MODE_PULSE_WIDTH;

	o->bytes_per_data_element = p->bytes_per_data_element
				  = माप(जोड़ cx23888_ir_fअगरo_rec);

	/* Beक्रमe we tweak the hardware, we have to disable the transmitter */
	irqenable_tx(dev, 0);
	control_tx_enable(dev, false);

	control_tx_modulation_enable(dev, p->modulation);
	o->modulation = p->modulation;

	अगर (p->modulation) अणु
		p->carrier_freq = txclk_tx_s_carrier(dev, p->carrier_freq,
						     &txclk_भागider);
		o->carrier_freq = p->carrier_freq;

		p->duty_cycle = cduty_tx_s_duty_cycle(dev, p->duty_cycle);
		o->duty_cycle = p->duty_cycle;

		p->max_pulse_width =
			(u32) pulse_width_count_to_ns(FIFO_RXTX, txclk_भागider);
	पूर्ण अन्यथा अणु
		p->max_pulse_width =
			    txclk_tx_s_max_pulse_width(dev, p->max_pulse_width,
						       &txclk_भागider);
	पूर्ण
	o->max_pulse_width = p->max_pulse_width;
	atomic_set(&state->txclk_भागider, txclk_भागider);

	p->resolution = घड़ी_भागider_to_resolution(txclk_भागider);
	o->resolution = p->resolution;

	/* FIXME - make this dependent on resolution क्रम better perक्रमmance */
	control_tx_irq_watermark(dev, TX_FIFO_HALF_EMPTY);

	control_tx_polarity_invert(dev, p->invert_carrier_sense);
	o->invert_carrier_sense = p->invert_carrier_sense;

	control_tx_level_invert(dev, p->invert_level);
	o->invert_level = p->invert_level;

	o->पूर्णांकerrupt_enable = p->पूर्णांकerrupt_enable;
	o->enable = p->enable;
	अगर (p->enable) अणु
		अगर (p->पूर्णांकerrupt_enable)
			irqenable_tx(dev, IRQEN_TSE);
		control_tx_enable(dev, p->enable);
	पूर्ण

	mutex_unlock(&state->tx_params_lock);
	वापस 0;
पूर्ण


/*
 * V4L2 Subdevice Core Ops
 */
अटल पूर्णांक cx23888_ir_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा cx23888_ir_state *state = to_state(sd);
	काष्ठा cx23885_dev *dev = state->dev;
	अक्षर *s;
	पूर्णांक i, j;

	u32 cntrl = cx23888_ir_पढ़ो4(dev, CX23888_IR_CNTRL_REG);
	u32 txclk = cx23888_ir_पढ़ो4(dev, CX23888_IR_TXCLK_REG) & TXCLK_TCD;
	u32 rxclk = cx23888_ir_पढ़ो4(dev, CX23888_IR_RXCLK_REG) & RXCLK_RCD;
	u32 cduty = cx23888_ir_पढ़ो4(dev, CX23888_IR_CDUTY_REG) & CDUTY_CDC;
	u32 stats = cx23888_ir_पढ़ो4(dev, CX23888_IR_STATS_REG);
	u32 irqen = cx23888_ir_पढ़ो4(dev, CX23888_IR_IRQEN_REG);
	u32 filtr = cx23888_ir_पढ़ो4(dev, CX23888_IR_FILTR_REG) & FILTR_LPF;

	v4l2_info(sd, "IR Receiver:\n");
	v4l2_info(sd, "\tEnabled:                           %s\n",
		  cntrl & CNTRL_RXE ? "yes" : "no");
	v4l2_info(sd, "\tDemodulation from a carrier:       %s\n",
		  cntrl & CNTRL_DMD ? "enabled" : "disabled");
	v4l2_info(sd, "\tFIFO:                              %s\n",
		  cntrl & CNTRL_RFE ? "enabled" : "disabled");
	चयन (cntrl & CNTRL_EDG) अणु
	हाल CNTRL_EDG_NONE:
		s = "disabled";
		अवरोध;
	हाल CNTRL_EDG_FALL:
		s = "falling edge";
		अवरोध;
	हाल CNTRL_EDG_RISE:
		s = "rising edge";
		अवरोध;
	हाल CNTRL_EDG_BOTH:
		s = "rising & falling edges";
		अवरोध;
	शेष:
		s = "??? edge";
		अवरोध;
	पूर्ण
	v4l2_info(sd, "\tPulse timers' start/stop trigger:  %s\n", s);
	v4l2_info(sd, "\tFIFO data on pulse timer overflow: %s\n",
		  cntrl & CNTRL_R ? "not loaded" : "overflow marker");
	v4l2_info(sd, "\tFIFO interrupt watermark:          %s\n",
		  cntrl & CNTRL_RIC ? "not empty" : "half full or greater");
	v4l2_info(sd, "\tLoopback mode:                     %s\n",
		  cntrl & CNTRL_LBM ? "loopback active" : "normal receive");
	अगर (cntrl & CNTRL_DMD) अणु
		v4l2_info(sd, "\tExpected carrier (16 clocks):      %u Hz\n",
			  घड़ी_भागider_to_carrier_freq(rxclk));
		चयन (cntrl & CNTRL_WIN) अणु
		हाल CNTRL_WIN_3_3:
			i = 3;
			j = 3;
			अवरोध;
		हाल CNTRL_WIN_4_3:
			i = 4;
			j = 3;
			अवरोध;
		हाल CNTRL_WIN_3_4:
			i = 3;
			j = 4;
			अवरोध;
		हाल CNTRL_WIN_4_4:
			i = 4;
			j = 4;
			अवरोध;
		शेष:
			i = 0;
			j = 0;
			अवरोध;
		पूर्ण
		v4l2_info(sd, "\tNext carrier edge window:	    16 clocks -%1d/+%1d, %u to %u Hz\n",
			  i, j,
			  घड़ी_भागider_to_freq(rxclk, 16 + j),
			  घड़ी_भागider_to_freq(rxclk, 16 - i));
	पूर्ण
	v4l2_info(sd, "\tMax measurable pulse width:        %u us, %llu ns\n",
		  pulse_width_count_to_us(FIFO_RXTX, rxclk),
		  pulse_width_count_to_ns(FIFO_RXTX, rxclk));
	v4l2_info(sd, "\tLow pass filter:                   %s\n",
		  filtr ? "enabled" : "disabled");
	अगर (filtr)
		v4l2_info(sd, "\tMin acceptable pulse width (LPF):  %u us, %u ns\n",
			  lpf_count_to_us(filtr),
			  lpf_count_to_ns(filtr));
	v4l2_info(sd, "\tPulse width timer timed-out:       %s\n",
		  stats & STATS_RTO ? "yes" : "no");
	v4l2_info(sd, "\tPulse width timer time-out intr:   %s\n",
		  irqen & IRQEN_RTE ? "enabled" : "disabled");
	v4l2_info(sd, "\tFIFO overrun:                      %s\n",
		  stats & STATS_ROR ? "yes" : "no");
	v4l2_info(sd, "\tFIFO overrun interrupt:            %s\n",
		  irqen & IRQEN_ROE ? "enabled" : "disabled");
	v4l2_info(sd, "\tBusy:                              %s\n",
		  stats & STATS_RBY ? "yes" : "no");
	v4l2_info(sd, "\tFIFO service requested:            %s\n",
		  stats & STATS_RSR ? "yes" : "no");
	v4l2_info(sd, "\tFIFO service request interrupt:    %s\n",
		  irqen & IRQEN_RSE ? "enabled" : "disabled");

	v4l2_info(sd, "IR Transmitter:\n");
	v4l2_info(sd, "\tEnabled:                           %s\n",
		  cntrl & CNTRL_TXE ? "yes" : "no");
	v4l2_info(sd, "\tModulation onto a carrier:         %s\n",
		  cntrl & CNTRL_MOD ? "enabled" : "disabled");
	v4l2_info(sd, "\tFIFO:                              %s\n",
		  cntrl & CNTRL_TFE ? "enabled" : "disabled");
	v4l2_info(sd, "\tFIFO interrupt watermark:          %s\n",
		  cntrl & CNTRL_TIC ? "not empty" : "half full or less");
	v4l2_info(sd, "\tOutput pin level inversion         %s\n",
		  cntrl & CNTRL_IVO ? "yes" : "no");
	v4l2_info(sd, "\tCarrier polarity:                  %s\n",
		  cntrl & CNTRL_CPL ? "space:burst mark:noburst"
				    : "space:noburst mark:burst");
	अगर (cntrl & CNTRL_MOD) अणु
		v4l2_info(sd, "\tCarrier (16 clocks):               %u Hz\n",
			  घड़ी_भागider_to_carrier_freq(txclk));
		v4l2_info(sd, "\tCarrier duty cycle:                %2u/16\n",
			  cduty + 1);
	पूर्ण
	v4l2_info(sd, "\tMax pulse width:                   %u us, %llu ns\n",
		  pulse_width_count_to_us(FIFO_RXTX, txclk),
		  pulse_width_count_to_ns(FIFO_RXTX, txclk));
	v4l2_info(sd, "\tBusy:                              %s\n",
		  stats & STATS_TBY ? "yes" : "no");
	v4l2_info(sd, "\tFIFO service requested:            %s\n",
		  stats & STATS_TSR ? "yes" : "no");
	v4l2_info(sd, "\tFIFO service request interrupt:    %s\n",
		  irqen & IRQEN_TSE ? "enabled" : "disabled");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक cx23888_ir_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cx23888_ir_state *state = to_state(sd);
	u32 addr = CX23888_IR_REG_BASE + (u32) reg->reg;

	अगर ((addr & 0x3) != 0)
		वापस -EINVAL;
	अगर (addr < CX23888_IR_CNTRL_REG || addr > CX23888_IR_LEARN_REG)
		वापस -EINVAL;
	reg->size = 4;
	reg->val = cx23888_ir_पढ़ो4(state->dev, addr);
	वापस 0;
पूर्ण

अटल पूर्णांक cx23888_ir_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
				 स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cx23888_ir_state *state = to_state(sd);
	u32 addr = CX23888_IR_REG_BASE + (u32) reg->reg;

	अगर ((addr & 0x3) != 0)
		वापस -EINVAL;
	अगर (addr < CX23888_IR_CNTRL_REG || addr > CX23888_IR_LEARN_REG)
		वापस -EINVAL;
	cx23888_ir_ग_लिखो4(state->dev, addr, reg->val);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा v4l2_subdev_core_ops cx23888_ir_core_ops = अणु
	.log_status = cx23888_ir_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = cx23888_ir_g_रेजिस्टर,
	.s_रेजिस्टर = cx23888_ir_s_रेजिस्टर,
#पूर्ण_अगर
	.पूर्णांकerrupt_service_routine = cx23888_ir_irq_handler,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ir_ops cx23888_ir_ir_ops = अणु
	.rx_पढ़ो = cx23888_ir_rx_पढ़ो,
	.rx_g_parameters = cx23888_ir_rx_g_parameters,
	.rx_s_parameters = cx23888_ir_rx_s_parameters,

	.tx_ग_लिखो = cx23888_ir_tx_ग_लिखो,
	.tx_g_parameters = cx23888_ir_tx_g_parameters,
	.tx_s_parameters = cx23888_ir_tx_s_parameters,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops cx23888_ir_controller_ops = अणु
	.core = &cx23888_ir_core_ops,
	.ir = &cx23888_ir_ir_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ir_parameters शेष_rx_params = अणु
	.bytes_per_data_element = माप(जोड़ cx23888_ir_fअगरo_rec),
	.mode = V4L2_SUBDEV_IR_MODE_PULSE_WIDTH,

	.enable = false,
	.पूर्णांकerrupt_enable = false,
	.shutकरोwn = true,

	.modulation = true,
	.carrier_freq = 36000, /* 36 kHz - RC-5, RC-6, and RC-6A carrier */

	/* RC-5:    666,667 ns = 1/36 kHz * 32 cycles * 1 mark * 0.75 */
	/* RC-6A:   333,333 ns = 1/36 kHz * 16 cycles * 1 mark * 0.75 */
	.noise_filter_min_width = 333333, /* ns */
	.carrier_range_lower = 35000,
	.carrier_range_upper = 37000,
	.invert_level = false,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ir_parameters शेष_tx_params = अणु
	.bytes_per_data_element = माप(जोड़ cx23888_ir_fअगरo_rec),
	.mode = V4L2_SUBDEV_IR_MODE_PULSE_WIDTH,

	.enable = false,
	.पूर्णांकerrupt_enable = false,
	.shutकरोwn = true,

	.modulation = true,
	.carrier_freq = 36000, /* 36 kHz - RC-5 carrier */
	.duty_cycle = 25,      /* 25 %   - RC-5 carrier */
	.invert_level = false,
	.invert_carrier_sense = false,
पूर्ण;

पूर्णांक cx23888_ir_probe(काष्ठा cx23885_dev *dev)
अणु
	काष्ठा cx23888_ir_state *state;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_subdev_ir_parameters शेष_params;
	पूर्णांक ret;

	state = kzalloc(माप(काष्ठा cx23888_ir_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;

	spin_lock_init(&state->rx_kfअगरo_lock);
	अगर (kfअगरo_alloc(&state->rx_kfअगरo, CX23888_IR_RX_KFIFO_SIZE,
			GFP_KERNEL)) अणु
		kमुक्त(state);
		वापस -ENOMEM;
	पूर्ण

	state->dev = dev;
	sd = &state->sd;

	v4l2_subdev_init(sd, &cx23888_ir_controller_ops);
	v4l2_set_subdevdata(sd, state);
	/* FIXME - fix the क्रमmatting of dev->v4l2_dev.name and use it */
	snम_लिखो(sd->name, माप(sd->name), "%s/888-ir", dev->name);
	sd->grp_id = CX23885_HW_888_IR;

	ret = v4l2_device_रेजिस्टर_subdev(&dev->v4l2_dev, sd);
	अगर (ret == 0) अणु
		/*
		 * Ensure no पूर्णांकerrupts arrive from '888 specअगरic conditions,
		 * since we ignore them in this driver to have commonality with
		 * similar IR controller cores.
		 */
		cx23888_ir_ग_लिखो4(dev, CX23888_IR_IRQEN_REG, 0);

		mutex_init(&state->rx_params_lock);
		शेष_params = शेष_rx_params;
		v4l2_subdev_call(sd, ir, rx_s_parameters, &शेष_params);

		mutex_init(&state->tx_params_lock);
		शेष_params = शेष_tx_params;
		v4l2_subdev_call(sd, ir, tx_s_parameters, &शेष_params);
	पूर्ण अन्यथा अणु
		kfअगरo_मुक्त(&state->rx_kfअगरo);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक cx23888_ir_हटाओ(काष्ठा cx23885_dev *dev)
अणु
	काष्ठा v4l2_subdev *sd;
	काष्ठा cx23888_ir_state *state;

	sd = cx23885_find_hw(dev, CX23885_HW_888_IR);
	अगर (sd == शून्य)
		वापस -ENODEV;

	cx23888_ir_rx_shutकरोwn(sd);
	cx23888_ir_tx_shutकरोwn(sd);

	state = to_state(sd);
	v4l2_device_unरेजिस्टर_subdev(sd);
	kfअगरo_मुक्त(&state->rx_kfअगरo);
	kमुक्त(state);
	/* Nothing more to मुक्त() as state held the actual v4l2_subdev object */
	वापस 0;
पूर्ण
