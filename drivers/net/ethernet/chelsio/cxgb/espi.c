<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: espi.c                                                              *
 * $Revision: 1.14 $                                                         *
 * $Date: 2005/05/14 00:59:32 $                                              *
 * Description:                                                              *
 *  Ethernet SPI functionality.                                              *
 *  part of the Chelsio 10Gb Ethernet Driver.                                *
 *                                                                           *
 * This program is मुक्त software; you can redistribute it and/or modअगरy      *
 * it under the terms of the GNU General Public License, version 2, as       *
 * published by the Free Software Foundation.                                *
 *                                                                           *
 * You should have received a copy of the GNU General Public License aदीर्घ   *
 * with this program; अगर not, see <http://www.gnu.org/licenses/>.            *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED    *
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF      *
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.                     *
 *                                                                           *
 * http://www.chelsio.com                                                    *
 *                                                                           *
 * Copyright (c) 2003 - 2005 Chelsio Communications, Inc.                    *
 * All rights reserved.                                                      *
 *                                                                           *
 * Maपूर्णांकainers: मुख्यtainers@chelsio.com                                      *
 *                                                                           *
 * Authors: Dimitrios Michailidis   <dm@chelsio.com>                         *
 *          Tina Yang               <tainay@chelsio.com>                     *
 *          Felix Marti             <felix@chelsio.com>                      *
 *          Scott Barकरोne           <sbarकरोne@chelsio.com>                   *
 *          Kurt Ottaway            <kottaway@chelsio.com>                   *
 *          Frank DiMambro          <frank@chelsio.com>                      *
 *                                                                           *
 * History:                                                                  *
 *                                                                           *
 ****************************************************************************/

#समावेश "common.h"
#समावेश "regs.h"
#समावेश "espi.h"

काष्ठा peespi अणु
	adapter_t *adapter;
	काष्ठा espi_पूर्णांकr_counts पूर्णांकr_cnt;
	u32 misc_ctrl;
	spinlock_t lock;
पूर्ण;

#घोषणा ESPI_INTR_MASK (F_DIP4ERR | F_RXDROP | F_TXDROP | F_RXOVERFLOW | \
			F_RAMPARITYERR | F_DIP2PARITYERR)
#घोषणा MON_MASK  (V_MONITORED_PORT_NUM(3) | F_MONITORED_सूचीECTION \
		   | F_MONITORED_INTERFACE)

#घोषणा TRICN_CNFG 14
#घोषणा TRICN_CMD_READ  0x11
#घोषणा TRICN_CMD_WRITE 0x21
#घोषणा TRICN_CMD_ATTEMPTS 10

अटल पूर्णांक tricn_ग_लिखो(adapter_t *adapter, पूर्णांक bundle_addr, पूर्णांक module_addr,
		       पूर्णांक ch_addr, पूर्णांक reg_offset, u32 wr_data)
अणु
	पूर्णांक busy, attempts = TRICN_CMD_ATTEMPTS;

	ग_लिखोl(V_WRITE_DATA(wr_data) |
	       V_REGISTER_OFFSET(reg_offset) |
	       V_CHANNEL_ADDR(ch_addr) | V_MODULE_ADDR(module_addr) |
	       V_BUNDLE_ADDR(bundle_addr) |
	       V_SPI4_COMMAND(TRICN_CMD_WRITE),
	       adapter->regs + A_ESPI_CMD_ADDR);
	ग_लिखोl(0, adapter->regs + A_ESPI_GOSTAT);

	करो अणु
		busy = पढ़ोl(adapter->regs + A_ESPI_GOSTAT) & F_ESPI_CMD_BUSY;
	पूर्ण जबतक (busy && --attempts);

	अगर (busy)
		pr_err("%s: TRICN write timed out\n", adapter->name);

	वापस busy;
पूर्ण

अटल पूर्णांक tricn_init(adapter_t *adapter)
अणु
	पूर्णांक i, sme = 1;

	अगर (!(पढ़ोl(adapter->regs + A_ESPI_RX_RESET)  & F_RX_CLK_STATUS)) अणु
		pr_err("%s: ESPI clock not ready\n", adapter->name);
		वापस -1;
	पूर्ण

	ग_लिखोl(F_ESPI_RX_CORE_RST, adapter->regs + A_ESPI_RX_RESET);

	अगर (sme) अणु
		tricn_ग_लिखो(adapter, 0, 0, 0, TRICN_CNFG, 0x81);
		tricn_ग_लिखो(adapter, 0, 1, 0, TRICN_CNFG, 0x81);
		tricn_ग_लिखो(adapter, 0, 2, 0, TRICN_CNFG, 0x81);
	पूर्ण
	क्रम (i = 1; i <= 8; i++)
		tricn_ग_लिखो(adapter, 0, 0, i, TRICN_CNFG, 0xf1);
	क्रम (i = 1; i <= 2; i++)
		tricn_ग_लिखो(adapter, 0, 1, i, TRICN_CNFG, 0xf1);
	क्रम (i = 1; i <= 3; i++)
		tricn_ग_लिखो(adapter, 0, 2, i, TRICN_CNFG, 0xe1);
	tricn_ग_लिखो(adapter, 0, 2, 4, TRICN_CNFG, 0xf1);
	tricn_ग_लिखो(adapter, 0, 2, 5, TRICN_CNFG, 0xe1);
	tricn_ग_लिखो(adapter, 0, 2, 6, TRICN_CNFG, 0xf1);
	tricn_ग_लिखो(adapter, 0, 2, 7, TRICN_CNFG, 0x80);
	tricn_ग_लिखो(adapter, 0, 2, 8, TRICN_CNFG, 0xf1);

	ग_लिखोl(F_ESPI_RX_CORE_RST | F_ESPI_RX_LNK_RST,
	       adapter->regs + A_ESPI_RX_RESET);

	वापस 0;
पूर्ण

व्योम t1_espi_पूर्णांकr_enable(काष्ठा peespi *espi)
अणु
	u32 enable, pl_पूर्णांकr = पढ़ोl(espi->adapter->regs + A_PL_ENABLE);

	/*
	 * Cannot enable ESPI पूर्णांकerrupts on T1B because HW निश्चितs the
	 * पूर्णांकerrupt incorrectly, namely the driver माला_लो ESPI पूर्णांकerrupts
	 * but no data is actually dropped (can verअगरy this पढ़ोing the ESPI
	 * drop रेजिस्टरs).  Also, once the ESPI पूर्णांकerrupt is निश्चितed it
	 * cannot be cleared (HW bug).
	 */
	enable = t1_is_T1B(espi->adapter) ? 0 : ESPI_INTR_MASK;
	ग_लिखोl(enable, espi->adapter->regs + A_ESPI_INTR_ENABLE);
	ग_लिखोl(pl_पूर्णांकr | F_PL_INTR_ESPI, espi->adapter->regs + A_PL_ENABLE);
पूर्ण

व्योम t1_espi_पूर्णांकr_clear(काष्ठा peespi *espi)
अणु
	पढ़ोl(espi->adapter->regs + A_ESPI_DIP2_ERR_COUNT);
	ग_लिखोl(0xffffffff, espi->adapter->regs + A_ESPI_INTR_STATUS);
	ग_लिखोl(F_PL_INTR_ESPI, espi->adapter->regs + A_PL_CAUSE);
पूर्ण

व्योम t1_espi_पूर्णांकr_disable(काष्ठा peespi *espi)
अणु
	u32 pl_पूर्णांकr = पढ़ोl(espi->adapter->regs + A_PL_ENABLE);

	ग_लिखोl(0, espi->adapter->regs + A_ESPI_INTR_ENABLE);
	ग_लिखोl(pl_पूर्णांकr & ~F_PL_INTR_ESPI, espi->adapter->regs + A_PL_ENABLE);
पूर्ण

पूर्णांक t1_espi_पूर्णांकr_handler(काष्ठा peespi *espi)
अणु
	u32 status = पढ़ोl(espi->adapter->regs + A_ESPI_INTR_STATUS);

	अगर (status & F_DIP4ERR)
		espi->पूर्णांकr_cnt.DIP4_err++;
	अगर (status & F_RXDROP)
		espi->पूर्णांकr_cnt.rx_drops++;
	अगर (status & F_TXDROP)
		espi->पूर्णांकr_cnt.tx_drops++;
	अगर (status & F_RXOVERFLOW)
		espi->पूर्णांकr_cnt.rx_ovflw++;
	अगर (status & F_RAMPARITYERR)
		espi->पूर्णांकr_cnt.parity_err++;
	अगर (status & F_DIP2PARITYERR) अणु
		espi->पूर्णांकr_cnt.DIP2_parity_err++;

		/*
		 * Must पढ़ो the error count to clear the पूर्णांकerrupt
		 * that it causes.
		 */
		पढ़ोl(espi->adapter->regs + A_ESPI_DIP2_ERR_COUNT);
	पूर्ण

	/*
	 * For T1B we need to ग_लिखो 1 to clear ESPI पूर्णांकerrupts.  For T2+ we
	 * ग_लिखो the status as is.
	 */
	अगर (status && t1_is_T1B(espi->adapter))
		status = 1;
	ग_लिखोl(status, espi->adapter->regs + A_ESPI_INTR_STATUS);
	वापस 0;
पूर्ण

स्थिर काष्ठा espi_पूर्णांकr_counts *t1_espi_get_पूर्णांकr_counts(काष्ठा peespi *espi)
अणु
	वापस &espi->पूर्णांकr_cnt;
पूर्ण

अटल व्योम espi_setup_क्रम_pm3393(adapter_t *adapter)
अणु
	u32 wmark = t1_is_T1B(adapter) ? 0x4000 : 0x3200;

	ग_लिखोl(0x1f4, adapter->regs + A_ESPI_SCH_TOKEN0);
	ग_लिखोl(0x1f4, adapter->regs + A_ESPI_SCH_TOKEN1);
	ग_लिखोl(0x1f4, adapter->regs + A_ESPI_SCH_TOKEN2);
	ग_लिखोl(0x1f4, adapter->regs + A_ESPI_SCH_TOKEN3);
	ग_लिखोl(0x100, adapter->regs + A_ESPI_RX_FIFO_ALMOST_EMPTY_WATERMARK);
	ग_लिखोl(wmark, adapter->regs + A_ESPI_RX_FIFO_ALMOST_FULL_WATERMARK);
	ग_लिखोl(3, adapter->regs + A_ESPI_CALENDAR_LENGTH);
	ग_लिखोl(0x08000008, adapter->regs + A_ESPI_TRAIN);
	ग_लिखोl(V_RX_NPORTS(1) | V_TX_NPORTS(1), adapter->regs + A_PORT_CONFIG);
पूर्ण

अटल व्योम espi_setup_क्रम_vsc7321(adapter_t *adapter)
अणु
	ग_लिखोl(0x1f4, adapter->regs + A_ESPI_SCH_TOKEN0);
	ग_लिखोl(0x1f401f4, adapter->regs + A_ESPI_SCH_TOKEN1);
	ग_लिखोl(0x1f4, adapter->regs + A_ESPI_SCH_TOKEN2);
	ग_लिखोl(0xa00, adapter->regs + A_ESPI_RX_FIFO_ALMOST_FULL_WATERMARK);
	ग_लिखोl(0x1ff, adapter->regs + A_ESPI_RX_FIFO_ALMOST_EMPTY_WATERMARK);
	ग_लिखोl(1, adapter->regs + A_ESPI_CALENDAR_LENGTH);
	ग_लिखोl(V_RX_NPORTS(4) | V_TX_NPORTS(4), adapter->regs + A_PORT_CONFIG);

	ग_लिखोl(0x08000008, adapter->regs + A_ESPI_TRAIN);
पूर्ण

/*
 * Note that T1B requires at least 2 ports क्रम IXF1010 due to a HW bug.
 */
अटल व्योम espi_setup_क्रम_ixf1010(adapter_t *adapter, पूर्णांक nports)
अणु
	ग_लिखोl(1, adapter->regs + A_ESPI_CALENDAR_LENGTH);
	अगर (nports == 4) अणु
		अगर (is_T2(adapter)) अणु
			ग_लिखोl(0xf00, adapter->regs + A_ESPI_RX_FIFO_ALMOST_FULL_WATERMARK);
			ग_लिखोl(0x3c0, adapter->regs + A_ESPI_RX_FIFO_ALMOST_EMPTY_WATERMARK);
		पूर्ण अन्यथा अणु
			ग_लिखोl(0x7ff, adapter->regs + A_ESPI_RX_FIFO_ALMOST_FULL_WATERMARK);
			ग_लिखोl(0x1ff, adapter->regs + A_ESPI_RX_FIFO_ALMOST_EMPTY_WATERMARK);
		पूर्ण
	पूर्ण अन्यथा अणु
		ग_लिखोl(0x1fff, adapter->regs + A_ESPI_RX_FIFO_ALMOST_FULL_WATERMARK);
		ग_लिखोl(0x7ff, adapter->regs + A_ESPI_RX_FIFO_ALMOST_EMPTY_WATERMARK);
	पूर्ण
	ग_लिखोl(V_RX_NPORTS(nports) | V_TX_NPORTS(nports), adapter->regs + A_PORT_CONFIG);

पूर्ण

पूर्णांक t1_espi_init(काष्ठा peespi *espi, पूर्णांक mac_type, पूर्णांक nports)
अणु
	u32 status_enable_extra = 0;
	adapter_t *adapter = espi->adapter;

	/* Disable ESPI training.  MACs that can handle it enable it below. */
	ग_लिखोl(0, adapter->regs + A_ESPI_TRAIN);

	अगर (is_T2(adapter)) अणु
		ग_लिखोl(V_OUT_OF_SYNC_COUNT(4) |
		       V_DIP2_PARITY_ERR_THRES(3) |
		       V_DIP4_THRES(1), adapter->regs + A_ESPI_MISC_CONTROL);
		ग_लिखोl(nports == 4 ? 0x200040 : 0x1000080,
		       adapter->regs + A_ESPI_MAXBURST1_MAXBURST2);
	पूर्ण अन्यथा
		ग_लिखोl(0x800100, adapter->regs + A_ESPI_MAXBURST1_MAXBURST2);

	अगर (mac_type == CHBT_MAC_PM3393)
		espi_setup_क्रम_pm3393(adapter);
	अन्यथा अगर (mac_type == CHBT_MAC_VSC7321)
		espi_setup_क्रम_vsc7321(adapter);
	अन्यथा अगर (mac_type == CHBT_MAC_IXF1010) अणु
		status_enable_extra = F_INTEL1010MODE;
		espi_setup_क्रम_ixf1010(adapter, nports);
	पूर्ण अन्यथा
		वापस -1;

	ग_लिखोl(status_enable_extra | F_RXSTATUSENABLE,
	       adapter->regs + A_ESPI_FIFO_STATUS_ENABLE);

	अगर (is_T2(adapter)) अणु
		tricn_init(adapter);
		/*
		 * Always position the control at the 1st port egress IN
		 * (sop,eop) counter to reduce PIOs क्रम T/N210 workaround.
		 */
		espi->misc_ctrl = पढ़ोl(adapter->regs + A_ESPI_MISC_CONTROL);
		espi->misc_ctrl &= ~MON_MASK;
		espi->misc_ctrl |= F_MONITORED_सूचीECTION;
		अगर (adapter->params.nports == 1)
			espi->misc_ctrl |= F_MONITORED_INTERFACE;
		ग_लिखोl(espi->misc_ctrl, adapter->regs + A_ESPI_MISC_CONTROL);
		spin_lock_init(&espi->lock);
	पूर्ण

	वापस 0;
पूर्ण

व्योम t1_espi_destroy(काष्ठा peespi *espi)
अणु
	kमुक्त(espi);
पूर्ण

काष्ठा peespi *t1_espi_create(adapter_t *adapter)
अणु
	काष्ठा peespi *espi = kzalloc(माप(*espi), GFP_KERNEL);

	अगर (espi)
		espi->adapter = adapter;
	वापस espi;
पूर्ण

#अगर 0
व्योम t1_espi_set_misc_ctrl(adapter_t *adapter, u32 val)
अणु
	काष्ठा peespi *espi = adapter->espi;

	अगर (!is_T2(adapter))
		वापस;
	spin_lock(&espi->lock);
	espi->misc_ctrl = (val & ~MON_MASK) |
			  (espi->misc_ctrl & MON_MASK);
	ग_लिखोl(espi->misc_ctrl, adapter->regs + A_ESPI_MISC_CONTROL);
	spin_unlock(&espi->lock);
पूर्ण
#पूर्ण_अगर  /*  0  */

u32 t1_espi_get_mon(adapter_t *adapter, u32 addr, u8 रुको)
अणु
	काष्ठा peespi *espi = adapter->espi;
	u32 sel;

	अगर (!is_T2(adapter))
		वापस 0;

	sel = V_MONITORED_PORT_NUM((addr & 0x3c) >> 2);
	अगर (!रुको) अणु
		अगर (!spin_trylock(&espi->lock))
			वापस 0;
	पूर्ण अन्यथा
		spin_lock(&espi->lock);

	अगर ((sel != (espi->misc_ctrl & MON_MASK))) अणु
		ग_लिखोl(((espi->misc_ctrl & ~MON_MASK) | sel),
		       adapter->regs + A_ESPI_MISC_CONTROL);
		sel = पढ़ोl(adapter->regs + A_ESPI_SCH_TOKEN3);
		ग_लिखोl(espi->misc_ctrl, adapter->regs + A_ESPI_MISC_CONTROL);
	पूर्ण अन्यथा
		sel = पढ़ोl(adapter->regs + A_ESPI_SCH_TOKEN3);
	spin_unlock(&espi->lock);
	वापस sel;
पूर्ण

/*
 * This function is क्रम T204 only.
 * compare with t1_espi_get_mon(), it पढ़ोs espiInTxSop[0 ~ 3] in
 * one shot, since there is no per port counter on the out side.
 */
पूर्णांक t1_espi_get_mon_t204(adapter_t *adapter, u32 *valp, u8 रुको)
अणु
	काष्ठा peespi *espi = adapter->espi;
	u8 i, nport = (u8)adapter->params.nports;

	अगर (!रुको) अणु
		अगर (!spin_trylock(&espi->lock))
			वापस -1;
	पूर्ण अन्यथा
		spin_lock(&espi->lock);

	अगर ((espi->misc_ctrl & MON_MASK) != F_MONITORED_सूचीECTION) अणु
		espi->misc_ctrl = (espi->misc_ctrl & ~MON_MASK) |
					F_MONITORED_सूचीECTION;
		ग_लिखोl(espi->misc_ctrl, adapter->regs + A_ESPI_MISC_CONTROL);
	पूर्ण
	क्रम (i = 0 ; i < nport; i++, valp++) अणु
		अगर (i) अणु
			ग_लिखोl(espi->misc_ctrl | V_MONITORED_PORT_NUM(i),
			       adapter->regs + A_ESPI_MISC_CONTROL);
		पूर्ण
		*valp = पढ़ोl(adapter->regs + A_ESPI_SCH_TOKEN3);
	पूर्ण

	ग_लिखोl(espi->misc_ctrl, adapter->regs + A_ESPI_MISC_CONTROL);
	spin_unlock(&espi->lock);
	वापस 0;
पूर्ण
