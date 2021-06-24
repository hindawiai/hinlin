<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* $Date: 2006/02/07 04:21:54 $ $RCSfile: tp.c,v $ $Revision: 1.73 $ */
#समावेश "common.h"
#समावेश "regs.h"
#समावेश "tp.h"
#अगर_घोषित CONFIG_CHELSIO_T1_1G
#समावेश "fpga_defs.h"
#पूर्ण_अगर

काष्ठा petp अणु
	adapter_t *adapter;
पूर्ण;

/* Pause deadlock aव्योमance parameters */
#घोषणा DROP_MSEC 16
#घोषणा DROP_PKTS_CNT  1

अटल व्योम tp_init(adapter_t * ap, स्थिर काष्ठा tp_params *p,
		    अचिन्हित पूर्णांक tp_clk)
अणु
	u32 val;

	अगर (!t1_is_asic(ap))
		वापस;

	val = F_TP_IN_CSPI_CPL | F_TP_IN_CSPI_CHECK_IP_CSUM |
		F_TP_IN_CSPI_CHECK_TCP_CSUM | F_TP_IN_ESPI_ETHERNET;
	अगर (!p->pm_size)
		val |= F_OFFLOAD_DISABLE;
	अन्यथा
		val |= F_TP_IN_ESPI_CHECK_IP_CSUM | F_TP_IN_ESPI_CHECK_TCP_CSUM;
	ग_लिखोl(val, ap->regs + A_TP_IN_CONFIG);
	ग_लिखोl(F_TP_OUT_CSPI_CPL |
	       F_TP_OUT_ESPI_ETHERNET |
	       F_TP_OUT_ESPI_GENERATE_IP_CSUM |
	       F_TP_OUT_ESPI_GENERATE_TCP_CSUM, ap->regs + A_TP_OUT_CONFIG);
	ग_लिखोl(V_IP_TTL(64) |
	       F_PATH_MTU /* IP DF bit */  |
	       V_5TUPLE_LOOKUP(p->use_5tuple_mode) |
	       V_SYN_COOKIE_PARAMETER(29), ap->regs + A_TP_GLOBAL_CONFIG);
	/*
	 * Enable छोड़ो frame deadlock prevention.
	 */
	अगर (is_T2(ap) && ap->params.nports > 1) अणु
		u32 drop_ticks = DROP_MSEC * (tp_clk / 1000);

		ग_लिखोl(F_ENABLE_TX_DROP | F_ENABLE_TX_ERROR |
		       V_DROP_TICKS_CNT(drop_ticks) |
		       V_NUM_PKTS_DROPPED(DROP_PKTS_CNT),
		       ap->regs + A_TP_TX_DROP_CONFIG);
	पूर्ण
पूर्ण

व्योम t1_tp_destroy(काष्ठा petp *tp)
अणु
	kमुक्त(tp);
पूर्ण

काष्ठा petp *t1_tp_create(adapter_t *adapter, काष्ठा tp_params *p)
अणु
	काष्ठा petp *tp = kzalloc(माप(*tp), GFP_KERNEL);

	अगर (!tp)
		वापस शून्य;

	tp->adapter = adapter;

	वापस tp;
पूर्ण

व्योम t1_tp_पूर्णांकr_enable(काष्ठा petp *tp)
अणु
	u32 tp_पूर्णांकr = पढ़ोl(tp->adapter->regs + A_PL_ENABLE);

#अगर_घोषित CONFIG_CHELSIO_T1_1G
	अगर (!t1_is_asic(tp->adapter)) अणु
		/* FPGA */
		ग_लिखोl(0xffffffff,
		       tp->adapter->regs + FPGA_TP_ADDR_INTERRUPT_ENABLE);
		ग_लिखोl(tp_पूर्णांकr | FPGA_PCIX_INTERRUPT_TP,
		       tp->adapter->regs + A_PL_ENABLE);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		/* We करोn't use any TP पूर्णांकerrupts */
		ग_लिखोl(0, tp->adapter->regs + A_TP_INT_ENABLE);
		ग_लिखोl(tp_पूर्णांकr | F_PL_INTR_TP,
		       tp->adapter->regs + A_PL_ENABLE);
	पूर्ण
पूर्ण

व्योम t1_tp_पूर्णांकr_disable(काष्ठा petp *tp)
अणु
	u32 tp_पूर्णांकr = पढ़ोl(tp->adapter->regs + A_PL_ENABLE);

#अगर_घोषित CONFIG_CHELSIO_T1_1G
	अगर (!t1_is_asic(tp->adapter)) अणु
		/* FPGA */
		ग_लिखोl(0, tp->adapter->regs + FPGA_TP_ADDR_INTERRUPT_ENABLE);
		ग_लिखोl(tp_पूर्णांकr & ~FPGA_PCIX_INTERRUPT_TP,
		       tp->adapter->regs + A_PL_ENABLE);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		ग_लिखोl(0, tp->adapter->regs + A_TP_INT_ENABLE);
		ग_लिखोl(tp_पूर्णांकr & ~F_PL_INTR_TP,
		       tp->adapter->regs + A_PL_ENABLE);
	पूर्ण
पूर्ण

व्योम t1_tp_पूर्णांकr_clear(काष्ठा petp *tp)
अणु
#अगर_घोषित CONFIG_CHELSIO_T1_1G
	अगर (!t1_is_asic(tp->adapter)) अणु
		ग_लिखोl(0xffffffff,
		       tp->adapter->regs + FPGA_TP_ADDR_INTERRUPT_CAUSE);
		ग_लिखोl(FPGA_PCIX_INTERRUPT_TP, tp->adapter->regs + A_PL_CAUSE);
		वापस;
	पूर्ण
#पूर्ण_अगर
	ग_लिखोl(0xffffffff, tp->adapter->regs + A_TP_INT_CAUSE);
	ग_लिखोl(F_PL_INTR_TP, tp->adapter->regs + A_PL_CAUSE);
पूर्ण

पूर्णांक t1_tp_पूर्णांकr_handler(काष्ठा petp *tp)
अणु
	u32 cause;

#अगर_घोषित CONFIG_CHELSIO_T1_1G
	/* FPGA करोesn't support TP पूर्णांकerrupts. */
	अगर (!t1_is_asic(tp->adapter))
		वापस 1;
#पूर्ण_अगर

	cause = पढ़ोl(tp->adapter->regs + A_TP_INT_CAUSE);
	ग_लिखोl(cause, tp->adapter->regs + A_TP_INT_CAUSE);
	वापस 0;
पूर्ण

अटल व्योम set_csum_offload(काष्ठा petp *tp, u32 csum_bit, पूर्णांक enable)
अणु
	u32 val = पढ़ोl(tp->adapter->regs + A_TP_GLOBAL_CONFIG);

	अगर (enable)
		val |= csum_bit;
	अन्यथा
		val &= ~csum_bit;
	ग_लिखोl(val, tp->adapter->regs + A_TP_GLOBAL_CONFIG);
पूर्ण

व्योम t1_tp_set_ip_checksum_offload(काष्ठा petp *tp, पूर्णांक enable)
अणु
	set_csum_offload(tp, F_IP_CSUM, enable);
पूर्ण

व्योम t1_tp_set_tcp_checksum_offload(काष्ठा petp *tp, पूर्णांक enable)
अणु
	set_csum_offload(tp, F_TCP_CSUM, enable);
पूर्ण

/*
 * Initialize TP state.  tp_params contains initial settings क्रम some TP
 * parameters, particularly the one-समय PM and CM settings.
 */
पूर्णांक t1_tp_reset(काष्ठा petp *tp, काष्ठा tp_params *p, अचिन्हित पूर्णांक tp_clk)
अणु
	adapter_t *adapter = tp->adapter;

	tp_init(adapter, p, tp_clk);
	ग_लिखोl(F_TP_RESET, adapter->regs +  A_TP_RESET);
	वापस 0;
पूर्ण
