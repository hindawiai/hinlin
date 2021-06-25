<शैली गुरु>
/*
 * AMD 10Gb Ethernet driver
 *
 * This file is available to you under your choice of the following two
 * licenses:
 *
 * License 1: GPLv2
 *
 * Copyright (c) 2016 Advanced Micro Devices, Inc.
 *
 * This file is मुक्त software; you may copy, redistribute and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at
 * your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * License 2: Modअगरied BSD
 *
 * Copyright (c) 2016 Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kmod.h>
#समावेश <linux/delay.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

#घोषणा XGBE_ABORT_COUNT	500
#घोषणा XGBE_DISABLE_COUNT	1000

#घोषणा XGBE_STD_SPEED		1

#घोषणा XGBE_INTR_RX_FULL	BIT(IC_RAW_INTR_STAT_RX_FULL_INDEX)
#घोषणा XGBE_INTR_TX_EMPTY	BIT(IC_RAW_INTR_STAT_TX_EMPTY_INDEX)
#घोषणा XGBE_INTR_TX_ABRT	BIT(IC_RAW_INTR_STAT_TX_ABRT_INDEX)
#घोषणा XGBE_INTR_STOP_DET	BIT(IC_RAW_INTR_STAT_STOP_DET_INDEX)
#घोषणा XGBE_DEFAULT_INT_MASK	(XGBE_INTR_RX_FULL  |	\
				 XGBE_INTR_TX_EMPTY |	\
				 XGBE_INTR_TX_ABRT  |	\
				 XGBE_INTR_STOP_DET)

#घोषणा XGBE_I2C_READ		BIT(8)
#घोषणा XGBE_I2C_STOP		BIT(9)

अटल पूर्णांक xgbe_i2c_पात(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक रुको = XGBE_ABORT_COUNT;

	/* Must be enabled to recognize the पात request */
	XI2C_IOWRITE_BITS(pdata, IC_ENABLE, EN, 1);

	/* Issue the पात */
	XI2C_IOWRITE_BITS(pdata, IC_ENABLE, ABORT, 1);

	जबतक (रुको--) अणु
		अगर (!XI2C_IOREAD_BITS(pdata, IC_ENABLE, ABORT))
			वापस 0;

		usleep_range(500, 600);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक xgbe_i2c_set_enable(काष्ठा xgbe_prv_data *pdata, bool enable)
अणु
	अचिन्हित पूर्णांक रुको = XGBE_DISABLE_COUNT;
	अचिन्हित पूर्णांक mode = enable ? 1 : 0;

	जबतक (रुको--) अणु
		XI2C_IOWRITE_BITS(pdata, IC_ENABLE, EN, mode);
		अगर (XI2C_IOREAD_BITS(pdata, IC_ENABLE_STATUS, EN) == mode)
			वापस 0;

		usleep_range(100, 110);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक xgbe_i2c_disable(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक ret;

	ret = xgbe_i2c_set_enable(pdata, false);
	अगर (ret) अणु
		/* Disable failed, try an पात */
		ret = xgbe_i2c_पात(pdata);
		अगर (ret)
			वापस ret;

		/* Abort succeeded, try to disable again */
		ret = xgbe_i2c_set_enable(pdata, false);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_i2c_enable(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस xgbe_i2c_set_enable(pdata, true);
पूर्ण

अटल व्योम xgbe_i2c_clear_all_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	XI2C_IOREAD(pdata, IC_CLR_INTR);
पूर्ण

अटल व्योम xgbe_i2c_disable_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	XI2C_IOWRITE(pdata, IC_INTR_MASK, 0);
पूर्ण

अटल व्योम xgbe_i2c_enable_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	XI2C_IOWRITE(pdata, IC_INTR_MASK, XGBE_DEFAULT_INT_MASK);
पूर्ण

अटल व्योम xgbe_i2c_ग_लिखो(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_i2c_op_state *state = &pdata->i2c.op_state;
	अचिन्हित पूर्णांक tx_slots;
	अचिन्हित पूर्णांक cmd;

	/* Configured to never receive Rx overflows, so fill up Tx fअगरo */
	tx_slots = pdata->i2c.tx_fअगरo_size - XI2C_IOREAD(pdata, IC_TXFLR);
	जबतक (tx_slots && state->tx_len) अणु
		अगर (state->op->cmd == XGBE_I2C_CMD_READ)
			cmd = XGBE_I2C_READ;
		अन्यथा
			cmd = *state->tx_buf++;

		अगर (state->tx_len == 1)
			XI2C_SET_BITS(cmd, IC_DATA_CMD, STOP, 1);

		XI2C_IOWRITE(pdata, IC_DATA_CMD, cmd);

		tx_slots--;
		state->tx_len--;
	पूर्ण

	/* No more Tx operations, so ignore TX_EMPTY and वापस */
	अगर (!state->tx_len)
		XI2C_IOWRITE_BITS(pdata, IC_INTR_MASK, TX_EMPTY, 0);
पूर्ण

अटल व्योम xgbe_i2c_पढ़ो(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_i2c_op_state *state = &pdata->i2c.op_state;
	अचिन्हित पूर्णांक rx_slots;

	/* Anything to be पढ़ो? */
	अगर (state->op->cmd != XGBE_I2C_CMD_READ)
		वापस;

	rx_slots = XI2C_IOREAD(pdata, IC_RXFLR);
	जबतक (rx_slots && state->rx_len) अणु
		*state->rx_buf++ = XI2C_IOREAD(pdata, IC_DATA_CMD);
		state->rx_len--;
		rx_slots--;
	पूर्ण
पूर्ण

अटल व्योम xgbe_i2c_clear_isr_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata,
					  अचिन्हित पूर्णांक isr)
अणु
	काष्ठा xgbe_i2c_op_state *state = &pdata->i2c.op_state;

	अगर (isr & XGBE_INTR_TX_ABRT) अणु
		state->tx_पात_source = XI2C_IOREAD(pdata, IC_TX_ABRT_SOURCE);
		XI2C_IOREAD(pdata, IC_CLR_TX_ABRT);
	पूर्ण

	अगर (isr & XGBE_INTR_STOP_DET)
		XI2C_IOREAD(pdata, IC_CLR_STOP_DET);
पूर्ण

अटल व्योम xgbe_i2c_isr_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा xgbe_prv_data *pdata = from_tasklet(pdata, t, tasklet_i2c);
	काष्ठा xgbe_i2c_op_state *state = &pdata->i2c.op_state;
	अचिन्हित पूर्णांक isr;

	isr = XI2C_IOREAD(pdata, IC_RAW_INTR_STAT);
	अगर (!isr)
		जाओ reissue_check;

	netअगर_dbg(pdata, पूर्णांकr, pdata->netdev,
		  "I2C interrupt received: status=%#010x\n", isr);

	xgbe_i2c_clear_isr_पूर्णांकerrupts(pdata, isr);

	अगर (isr & XGBE_INTR_TX_ABRT) अणु
		netअगर_dbg(pdata, link, pdata->netdev,
			  "I2C TX_ABRT received (%#010x) for target %#04x\n",
			  state->tx_पात_source, state->op->target);

		xgbe_i2c_disable_पूर्णांकerrupts(pdata);

		state->ret = -EIO;
		जाओ out;
	पूर्ण

	/* Check क्रम data in the Rx fअगरo */
	xgbe_i2c_पढ़ो(pdata);

	/* Fill up the Tx fअगरo next */
	xgbe_i2c_ग_लिखो(pdata);

out:
	/* Complete on an error or STOP condition */
	अगर (state->ret || XI2C_GET_BITS(isr, IC_RAW_INTR_STAT, STOP_DET))
		complete(&pdata->i2c_complete);

reissue_check:
	/* Reissue पूर्णांकerrupt अगर status is not clear */
	अगर (pdata->vdata->irq_reissue_support)
		XP_IOWRITE(pdata, XP_INT_REISSUE_EN, 1 << 2);
पूर्ण

अटल irqवापस_t xgbe_i2c_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xgbe_prv_data *pdata = (काष्ठा xgbe_prv_data *)data;

	अगर (pdata->isr_as_tasklet)
		tasklet_schedule(&pdata->tasklet_i2c);
	अन्यथा
		xgbe_i2c_isr_task(&pdata->tasklet_i2c);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम xgbe_i2c_set_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक reg;

	reg = XI2C_IOREAD(pdata, IC_CON);
	XI2C_SET_BITS(reg, IC_CON, MASTER_MODE, 1);
	XI2C_SET_BITS(reg, IC_CON, SLAVE_DISABLE, 1);
	XI2C_SET_BITS(reg, IC_CON, RESTART_EN, 1);
	XI2C_SET_BITS(reg, IC_CON, SPEED, XGBE_STD_SPEED);
	XI2C_SET_BITS(reg, IC_CON, RX_FIFO_FULL_HOLD, 1);
	XI2C_IOWRITE(pdata, IC_CON, reg);
पूर्ण

अटल व्योम xgbe_i2c_get_features(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_i2c *i2c = &pdata->i2c;
	अचिन्हित पूर्णांक reg;

	reg = XI2C_IOREAD(pdata, IC_COMP_PARAM_1);
	i2c->max_speed_mode = XI2C_GET_BITS(reg, IC_COMP_PARAM_1,
					    MAX_SPEED_MODE);
	i2c->rx_fअगरo_size = XI2C_GET_BITS(reg, IC_COMP_PARAM_1,
					  RX_BUFFER_DEPTH);
	i2c->tx_fअगरo_size = XI2C_GET_BITS(reg, IC_COMP_PARAM_1,
					  TX_BUFFER_DEPTH);

	अगर (netअगर_msg_probe(pdata))
		dev_dbg(pdata->dev, "I2C features: %s=%u, %s=%u, %s=%u\n",
			"MAX_SPEED_MODE", i2c->max_speed_mode,
			"RX_BUFFER_DEPTH", i2c->rx_fअगरo_size,
			"TX_BUFFER_DEPTH", i2c->tx_fअगरo_size);
पूर्ण

अटल व्योम xgbe_i2c_set_target(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक addr)
अणु
	XI2C_IOWRITE(pdata, IC_TAR, addr);
पूर्ण

अटल irqवापस_t xgbe_i2c_combined_isr(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_i2c_isr_task(&pdata->tasklet_i2c);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xgbe_i2c_xfer(काष्ठा xgbe_prv_data *pdata, काष्ठा xgbe_i2c_op *op)
अणु
	काष्ठा xgbe_i2c_op_state *state = &pdata->i2c.op_state;
	पूर्णांक ret;

	mutex_lock(&pdata->i2c_mutex);

	reinit_completion(&pdata->i2c_complete);

	ret = xgbe_i2c_disable(pdata);
	अगर (ret) अणु
		netdev_err(pdata->netdev, "failed to disable i2c master\n");
		जाओ unlock;
	पूर्ण

	xgbe_i2c_set_target(pdata, op->target);

	स_रखो(state, 0, माप(*state));
	state->op = op;
	state->tx_len = op->len;
	state->tx_buf = op->buf;
	state->rx_len = op->len;
	state->rx_buf = op->buf;

	xgbe_i2c_clear_all_पूर्णांकerrupts(pdata);
	ret = xgbe_i2c_enable(pdata);
	अगर (ret) अणु
		netdev_err(pdata->netdev, "failed to enable i2c master\n");
		जाओ unlock;
	पूर्ण

	/* Enabling the पूर्णांकerrupts will cause the TX FIFO empty पूर्णांकerrupt to
	 * fire and begin to process the command via the ISR.
	 */
	xgbe_i2c_enable_पूर्णांकerrupts(pdata);

	अगर (!रुको_क्रम_completion_समयout(&pdata->i2c_complete, HZ)) अणु
		netdev_err(pdata->netdev, "i2c operation timed out\n");
		ret = -ETIMEDOUT;
		जाओ disable;
	पूर्ण

	ret = state->ret;
	अगर (ret) अणु
		अगर (state->tx_पात_source & IC_TX_ABRT_7B_ADDR_NOACK)
			ret = -ENOTCONN;
		अन्यथा अगर (state->tx_पात_source & IC_TX_ABRT_ARB_LOST)
			ret = -EAGAIN;
	पूर्ण

disable:
	xgbe_i2c_disable_पूर्णांकerrupts(pdata);
	xgbe_i2c_disable(pdata);

unlock:
	mutex_unlock(&pdata->i2c_mutex);

	वापस ret;
पूर्ण

अटल व्योम xgbe_i2c_stop(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (!pdata->i2c.started)
		वापस;

	netअगर_dbg(pdata, link, pdata->netdev, "stopping I2C\n");

	pdata->i2c.started = 0;

	xgbe_i2c_disable_पूर्णांकerrupts(pdata);
	xgbe_i2c_disable(pdata);
	xgbe_i2c_clear_all_पूर्णांकerrupts(pdata);

	अगर (pdata->dev_irq != pdata->i2c_irq)
		devm_मुक्त_irq(pdata->dev, pdata->i2c_irq, pdata);
पूर्ण

अटल पूर्णांक xgbe_i2c_start(काष्ठा xgbe_prv_data *pdata)
अणु
	पूर्णांक ret;

	अगर (pdata->i2c.started)
		वापस 0;

	netअगर_dbg(pdata, link, pdata->netdev, "starting I2C\n");

	/* If we have a separate I2C irq, enable it */
	अगर (pdata->dev_irq != pdata->i2c_irq) अणु
		tasklet_setup(&pdata->tasklet_i2c, xgbe_i2c_isr_task);

		ret = devm_request_irq(pdata->dev, pdata->i2c_irq,
				       xgbe_i2c_isr, 0, pdata->i2c_name,
				       pdata);
		अगर (ret) अणु
			netdev_err(pdata->netdev, "i2c irq request failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	pdata->i2c.started = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_i2c_init(काष्ठा xgbe_prv_data *pdata)
अणु
	पूर्णांक ret;

	xgbe_i2c_disable_पूर्णांकerrupts(pdata);

	ret = xgbe_i2c_disable(pdata);
	अगर (ret) अणु
		dev_err(pdata->dev, "failed to disable i2c master\n");
		वापस ret;
	पूर्ण

	xgbe_i2c_get_features(pdata);

	xgbe_i2c_set_mode(pdata);

	xgbe_i2c_clear_all_पूर्णांकerrupts(pdata);

	वापस 0;
पूर्ण

व्योम xgbe_init_function_ptrs_i2c(काष्ठा xgbe_i2c_अगर *i2c_अगर)
अणु
	i2c_अगर->i2c_init		= xgbe_i2c_init;

	i2c_अगर->i2c_start		= xgbe_i2c_start;
	i2c_अगर->i2c_stop		= xgbe_i2c_stop;

	i2c_अगर->i2c_xfer		= xgbe_i2c_xfer;

	i2c_अगर->i2c_isr			= xgbe_i2c_combined_isr;
पूर्ण
