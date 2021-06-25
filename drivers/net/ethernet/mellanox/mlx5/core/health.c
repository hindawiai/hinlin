<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_core.h"
#समावेश "lib/eq.h"
#समावेश "lib/mlx5.h"
#समावेश "lib/pci_vsc.h"
#समावेश "diag/fw_tracer.h"

क्रमागत अणु
	MLX5_HEALTH_POLL_INTERVAL	= 2 * HZ,
	MAX_MISSES			= 3,
पूर्ण;

क्रमागत अणु
	MLX5_HEALTH_SYNDR_FW_ERR		= 0x1,
	MLX5_HEALTH_SYNDR_IRISC_ERR		= 0x7,
	MLX5_HEALTH_SYNDR_HW_UNRECOVERABLE_ERR	= 0x8,
	MLX5_HEALTH_SYNDR_CRC_ERR		= 0x9,
	MLX5_HEALTH_SYNDR_FETCH_PCI_ERR		= 0xa,
	MLX5_HEALTH_SYNDR_HW_FTL_ERR		= 0xb,
	MLX5_HEALTH_SYNDR_ASYNC_EQ_OVERRUN_ERR	= 0xc,
	MLX5_HEALTH_SYNDR_EQ_ERR		= 0xd,
	MLX5_HEALTH_SYNDR_EQ_INV		= 0xe,
	MLX5_HEALTH_SYNDR_FFSER_ERR		= 0xf,
	MLX5_HEALTH_SYNDR_HIGH_TEMP		= 0x10
पूर्ण;

क्रमागत अणु
	MLX5_DROP_NEW_HEALTH_WORK,
पूर्ण;

क्रमागत  अणु
	MLX5_SENSOR_NO_ERR		= 0,
	MLX5_SENSOR_PCI_COMM_ERR	= 1,
	MLX5_SENSOR_PCI_ERR		= 2,
	MLX5_SENSOR_NIC_DISABLED	= 3,
	MLX5_SENSOR_NIC_SW_RESET	= 4,
	MLX5_SENSOR_FW_SYND_RFR		= 5,
पूर्ण;

u8 mlx5_get_nic_state(काष्ठा mlx5_core_dev *dev)
अणु
	वापस (ioपढ़ो32be(&dev->iseg->cmdq_addr_l_sz) >> 8) & 7;
पूर्ण

व्योम mlx5_set_nic_state(काष्ठा mlx5_core_dev *dev, u8 state)
अणु
	u32 cur_cmdq_addr_l_sz;

	cur_cmdq_addr_l_sz = ioपढ़ो32be(&dev->iseg->cmdq_addr_l_sz);
	ioग_लिखो32be((cur_cmdq_addr_l_sz & 0xFFFFF000) |
		    state << MLX5_NIC_IFC_OFFSET,
		    &dev->iseg->cmdq_addr_l_sz);
पूर्ण

अटल bool sensor_pci_not_working(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_health *health = &dev->priv.health;
	काष्ठा health_buffer __iomem *h = health->health;

	/* Offline PCI पढ़ोs वापस 0xffffffff */
	वापस (ioपढ़ो32be(&h->fw_ver) == 0xffffffff);
पूर्ण

अटल bool sensor_fw_synd_rfr(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_health *health = &dev->priv.health;
	काष्ठा health_buffer __iomem *h = health->health;
	u32 rfr = ioपढ़ो32be(&h->rfr) >> MLX5_RFR_OFFSET;
	u8 synd = ioपढ़ो8(&h->synd);

	अगर (rfr && synd)
		mlx5_core_dbg(dev, "FW requests reset, synd: %d\n", synd);
	वापस rfr && synd;
पूर्ण

u32 mlx5_health_check_fatal_sensors(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (sensor_pci_not_working(dev))
		वापस MLX5_SENSOR_PCI_COMM_ERR;
	अगर (pci_channel_offline(dev->pdev))
		वापस MLX5_SENSOR_PCI_ERR;
	अगर (mlx5_get_nic_state(dev) == MLX5_NIC_IFC_DISABLED)
		वापस MLX5_SENSOR_NIC_DISABLED;
	अगर (mlx5_get_nic_state(dev) == MLX5_NIC_IFC_SW_RESET)
		वापस MLX5_SENSOR_NIC_SW_RESET;
	अगर (sensor_fw_synd_rfr(dev))
		वापस MLX5_SENSOR_FW_SYND_RFR;

	वापस MLX5_SENSOR_NO_ERR;
पूर्ण

अटल पूर्णांक lock_sem_sw_reset(काष्ठा mlx5_core_dev *dev, bool lock)
अणु
	क्रमागत mlx5_vsc_state state;
	पूर्णांक ret;

	अगर (!mlx5_core_is_pf(dev))
		वापस -EBUSY;

	/* Try to lock GW access, this stage करोesn't वापस
	 * EBUSY because locked GW करोes not mean that other PF
	 * alपढ़ोy started the reset.
	 */
	ret = mlx5_vsc_gw_lock(dev);
	अगर (ret == -EBUSY)
		वापस -EINVAL;
	अगर (ret)
		वापस ret;

	state = lock ? MLX5_VSC_LOCK : MLX5_VSC_UNLOCK;
	/* At this stage, अगर the वापस status == EBUSY, then we know
	 * क्रम sure that another PF started the reset, so करोn't allow
	 * another reset.
	 */
	ret = mlx5_vsc_sem_set_space(dev, MLX5_SEMAPHORE_SW_RESET, state);
	अगर (ret)
		mlx5_core_warn(dev, "Failed to lock SW reset semaphore\n");

	/* Unlock GW access */
	mlx5_vsc_gw_unlock(dev);

	वापस ret;
पूर्ण

अटल bool reset_fw_अगर_needed(काष्ठा mlx5_core_dev *dev)
अणु
	bool supported = (ioपढ़ो32be(&dev->iseg->initializing) >>
			  MLX5_FW_RESET_SUPPORTED_OFFSET) & 1;
	u32 fatal_error;

	अगर (!supported)
		वापस false;

	/* The reset only needs to be issued by one PF. The health buffer is
	 * shared between all functions, and will be cleared during a reset.
	 * Check again to aव्योम a redundant 2nd reset. If the fatal erros was
	 * PCI related a reset won't help.
	 */
	fatal_error = mlx5_health_check_fatal_sensors(dev);
	अगर (fatal_error == MLX5_SENSOR_PCI_COMM_ERR ||
	    fatal_error == MLX5_SENSOR_NIC_DISABLED ||
	    fatal_error == MLX5_SENSOR_NIC_SW_RESET) अणु
		mlx5_core_warn(dev, "Not issuing FW reset. Either it's already done or won't help.");
		वापस false;
	पूर्ण

	mlx5_core_warn(dev, "Issuing FW Reset\n");
	/* Write the NIC पूर्णांकerface field to initiate the reset, the command
	 * पूर्णांकerface address also resides here, करोn't overग_लिखो it.
	 */
	mlx5_set_nic_state(dev, MLX5_NIC_IFC_SW_RESET);

	वापस true;
पूर्ण

अटल व्योम enter_error_state(काष्ठा mlx5_core_dev *dev, bool क्रमce)
अणु
	अगर (mlx5_health_check_fatal_sensors(dev) || क्रमce) अणु /* रक्षित state setting */
		dev->state = MLX5_DEVICE_STATE_INTERNAL_ERROR;
		mlx5_cmd_flush(dev);
	पूर्ण

	mlx5_notअगरier_call_chain(dev->priv.events, MLX5_DEV_EVENT_SYS_ERROR, (व्योम *)1);
पूर्ण

व्योम mlx5_enter_error_state(काष्ठा mlx5_core_dev *dev, bool क्रमce)
अणु
	bool err_detected = false;

	/* Mark the device as fatal in order to पात FW commands */
	अगर ((mlx5_health_check_fatal_sensors(dev) || क्रमce) &&
	    dev->state == MLX5_DEVICE_STATE_UP) अणु
		dev->state = MLX5_DEVICE_STATE_INTERNAL_ERROR;
		err_detected = true;
	पूर्ण
	mutex_lock(&dev->पूर्णांकf_state_mutex);
	अगर (!err_detected && dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR)
		जाओ unlock;/* a previous error is still being handled */
	अगर (dev->state == MLX5_DEVICE_STATE_UNINITIALIZED) अणु
		dev->state = MLX5_DEVICE_STATE_INTERNAL_ERROR;
		जाओ unlock;
	पूर्ण

	enter_error_state(dev, क्रमce);
unlock:
	mutex_unlock(&dev->पूर्णांकf_state_mutex);
पूर्ण

#घोषणा MLX5_CRDUMP_WAIT_MS	60000
#घोषणा MLX5_FW_RESET_WAIT_MS	1000
व्योम mlx5_error_sw_reset(काष्ठा mlx5_core_dev *dev)
अणु
	अचिन्हित दीर्घ end, delay_ms = MLX5_FW_RESET_WAIT_MS;
	पूर्णांक lock = -EBUSY;

	mutex_lock(&dev->पूर्णांकf_state_mutex);
	अगर (dev->state != MLX5_DEVICE_STATE_INTERNAL_ERROR)
		जाओ unlock;

	mlx5_core_err(dev, "start\n");

	अगर (mlx5_health_check_fatal_sensors(dev) == MLX5_SENSOR_FW_SYND_RFR) अणु
		/* Get cr-dump and reset FW semaphore */
		lock = lock_sem_sw_reset(dev, true);

		अगर (lock == -EBUSY) अणु
			delay_ms = MLX5_CRDUMP_WAIT_MS;
			जाओ recover_from_sw_reset;
		पूर्ण
		/* Execute SW reset */
		reset_fw_अगर_needed(dev);
	पूर्ण

recover_from_sw_reset:
	/* Recover from SW reset */
	end = jअगरfies + msecs_to_jअगरfies(delay_ms);
	करो अणु
		अगर (mlx5_get_nic_state(dev) == MLX5_NIC_IFC_DISABLED)
			अवरोध;

		msleep(20);
	पूर्ण जबतक (!समय_after(jअगरfies, end));

	अगर (mlx5_get_nic_state(dev) != MLX5_NIC_IFC_DISABLED) अणु
		dev_err(&dev->pdev->dev, "NIC IFC still %d after %lums.\n",
			mlx5_get_nic_state(dev), delay_ms);
	पूर्ण

	/* Release FW semaphore अगर you are the lock owner */
	अगर (!lock)
		lock_sem_sw_reset(dev, false);

	mlx5_core_err(dev, "end\n");

unlock:
	mutex_unlock(&dev->पूर्णांकf_state_mutex);
पूर्ण

अटल व्योम mlx5_handle_bad_state(काष्ठा mlx5_core_dev *dev)
अणु
	u8 nic_पूर्णांकerface = mlx5_get_nic_state(dev);

	चयन (nic_पूर्णांकerface) अणु
	हाल MLX5_NIC_IFC_FULL:
		mlx5_core_warn(dev, "Expected to see disabled NIC but it is full driver\n");
		अवरोध;

	हाल MLX5_NIC_IFC_DISABLED:
		mlx5_core_warn(dev, "starting teardown\n");
		अवरोध;

	हाल MLX5_NIC_IFC_NO_DRAM_NIC:
		mlx5_core_warn(dev, "Expected to see disabled NIC but it is no dram nic\n");
		अवरोध;

	हाल MLX5_NIC_IFC_SW_RESET:
		/* The IFC mode field is 3 bits, so it will पढ़ो 0x7 in 2 हालs:
		 * 1. PCI has been disabled (ie. PCI-AER, PF driver unloaded
		 *    and this is a VF), this is not recoverable by SW reset.
		 *    Logging of this is handled अन्यथाwhere.
		 * 2. FW reset has been issued by another function, driver can
		 *    be reloaded to recover after the mode चयनes to
		 *    MLX5_NIC_IFC_DISABLED.
		 */
		अगर (dev->priv.health.fatal_error != MLX5_SENSOR_PCI_COMM_ERR)
			mlx5_core_warn(dev, "NIC SW reset in progress\n");
		अवरोध;

	शेष:
		mlx5_core_warn(dev, "Expected to see disabled NIC but it is has invalid value %d\n",
			       nic_पूर्णांकerface);
	पूर्ण

	mlx5_disable_device(dev);
पूर्ण

/* How much समय to रुको until health resetting the driver (in msecs) */
#घोषणा MLX5_RECOVERY_WAIT_MSECS 60000
पूर्णांक mlx5_health_रुको_pci_up(काष्ठा mlx5_core_dev *dev)
अणु
	अचिन्हित दीर्घ end;

	end = jअगरfies + msecs_to_jअगरfies(MLX5_RECOVERY_WAIT_MSECS);
	जबतक (sensor_pci_not_working(dev)) अणु
		अगर (समय_after(jअगरfies, end))
			वापस -ETIMEDOUT;
		msleep(100);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_health_try_recover(काष्ठा mlx5_core_dev *dev)
अणु
	mlx5_core_warn(dev, "handling bad device here\n");
	mlx5_handle_bad_state(dev);
	अगर (mlx5_health_रुको_pci_up(dev)) अणु
		mlx5_core_err(dev, "health recovery flow aborted, PCI reads still not working\n");
		वापस -EIO;
	पूर्ण
	mlx5_core_err(dev, "starting health recovery flow\n");
	अगर (mlx5_recover_device(dev) || mlx5_health_check_fatal_sensors(dev)) अणु
		mlx5_core_err(dev, "health recovery failed\n");
		वापस -EIO;
	पूर्ण

	mlx5_core_info(dev, "health recovery succeeded\n");
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *hsynd_str(u8 synd)
अणु
	चयन (synd) अणु
	हाल MLX5_HEALTH_SYNDR_FW_ERR:
		वापस "firmware internal error";
	हाल MLX5_HEALTH_SYNDR_IRISC_ERR:
		वापस "irisc not responding";
	हाल MLX5_HEALTH_SYNDR_HW_UNRECOVERABLE_ERR:
		वापस "unrecoverable hardware error";
	हाल MLX5_HEALTH_SYNDR_CRC_ERR:
		वापस "firmware CRC error";
	हाल MLX5_HEALTH_SYNDR_FETCH_PCI_ERR:
		वापस "ICM fetch PCI error";
	हाल MLX5_HEALTH_SYNDR_HW_FTL_ERR:
		वापस "HW fatal error\n";
	हाल MLX5_HEALTH_SYNDR_ASYNC_EQ_OVERRUN_ERR:
		वापस "async EQ buffer overrun";
	हाल MLX5_HEALTH_SYNDR_EQ_ERR:
		वापस "EQ error";
	हाल MLX5_HEALTH_SYNDR_EQ_INV:
		वापस "Invalid EQ referenced";
	हाल MLX5_HEALTH_SYNDR_FFSER_ERR:
		वापस "FFSER error";
	हाल MLX5_HEALTH_SYNDR_HIGH_TEMP:
		वापस "High temperature";
	शेष:
		वापस "unrecognized error";
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_health_info(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_health *health = &dev->priv.health;
	काष्ठा health_buffer __iomem *h = health->health;
	अक्षर fw_str[18];
	u32 fw;
	पूर्णांक i;

	/* If the syndrome is 0, the device is OK and no need to prपूर्णांक buffer */
	अगर (!ioपढ़ो8(&h->synd))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(h->निश्चित_var); i++)
		mlx5_core_err(dev, "assert_var[%d] 0x%08x\n", i,
			      ioपढ़ो32be(h->निश्चित_var + i));

	mlx5_core_err(dev, "assert_exit_ptr 0x%08x\n",
		      ioपढ़ो32be(&h->निश्चित_निकास_ptr));
	mlx5_core_err(dev, "assert_callra 0x%08x\n",
		      ioपढ़ो32be(&h->निश्चित_callra));
	प्र_लिखो(fw_str, "%d.%d.%d", fw_rev_maj(dev), fw_rev_min(dev), fw_rev_sub(dev));
	mlx5_core_err(dev, "fw_ver %s\n", fw_str);
	mlx5_core_err(dev, "hw_id 0x%08x\n", ioपढ़ो32be(&h->hw_id));
	mlx5_core_err(dev, "irisc_index %d\n", ioपढ़ो8(&h->irisc_index));
	mlx5_core_err(dev, "synd 0x%x: %s\n", ioपढ़ो8(&h->synd),
		      hsynd_str(ioपढ़ो8(&h->synd)));
	mlx5_core_err(dev, "ext_synd 0x%04x\n", ioपढ़ो16be(&h->ext_synd));
	fw = ioपढ़ो32be(&h->fw_ver);
	mlx5_core_err(dev, "raw fw_ver 0x%08x\n", fw);
पूर्ण

अटल पूर्णांक
mlx5_fw_reporter_diagnose(काष्ठा devlink_health_reporter *reporter,
			  काष्ठा devlink_fmsg *fmsg,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_health_reporter_priv(reporter);
	काष्ठा mlx5_core_health *health = &dev->priv.health;
	काष्ठा health_buffer __iomem *h = health->health;
	u8 synd;
	पूर्णांक err;

	synd = ioपढ़ो8(&h->synd);
	err = devlink_fmsg_u8_pair_put(fmsg, "Syndrome", synd);
	अगर (err || !synd)
		वापस err;
	वापस devlink_fmsg_string_pair_put(fmsg, "Description", hsynd_str(synd));
पूर्ण

काष्ठा mlx5_fw_reporter_ctx अणु
	u8 err_synd;
	पूर्णांक miss_counter;
पूर्ण;

अटल पूर्णांक
mlx5_fw_reporter_ctx_pairs_put(काष्ठा devlink_fmsg *fmsg,
			       काष्ठा mlx5_fw_reporter_ctx *fw_reporter_ctx)
अणु
	पूर्णांक err;

	err = devlink_fmsg_u8_pair_put(fmsg, "syndrome",
				       fw_reporter_ctx->err_synd);
	अगर (err)
		वापस err;
	err = devlink_fmsg_u32_pair_put(fmsg, "fw_miss_counter",
					fw_reporter_ctx->miss_counter);
	अगर (err)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_fw_reporter_heath_buffer_data_put(काष्ठा mlx5_core_dev *dev,
				       काष्ठा devlink_fmsg *fmsg)
अणु
	काष्ठा mlx5_core_health *health = &dev->priv.health;
	काष्ठा health_buffer __iomem *h = health->health;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!ioपढ़ो8(&h->synd))
		वापस 0;

	err = devlink_fmsg_pair_nest_start(fmsg, "health buffer");
	अगर (err)
		वापस err;
	err = devlink_fmsg_obj_nest_start(fmsg);
	अगर (err)
		वापस err;
	err = devlink_fmsg_arr_pair_nest_start(fmsg, "assert_var");
	अगर (err)
		वापस err;

	क्रम (i = 0; i < ARRAY_SIZE(h->निश्चित_var); i++) अणु
		err = devlink_fmsg_u32_put(fmsg, ioपढ़ो32be(h->निश्चित_var + i));
		अगर (err)
			वापस err;
	पूर्ण
	err = devlink_fmsg_arr_pair_nest_end(fmsg);
	अगर (err)
		वापस err;
	err = devlink_fmsg_u32_pair_put(fmsg, "assert_exit_ptr",
					ioपढ़ो32be(&h->निश्चित_निकास_ptr));
	अगर (err)
		वापस err;
	err = devlink_fmsg_u32_pair_put(fmsg, "assert_callra",
					ioपढ़ो32be(&h->निश्चित_callra));
	अगर (err)
		वापस err;
	err = devlink_fmsg_u32_pair_put(fmsg, "hw_id", ioपढ़ो32be(&h->hw_id));
	अगर (err)
		वापस err;
	err = devlink_fmsg_u8_pair_put(fmsg, "irisc_index",
				       ioपढ़ो8(&h->irisc_index));
	अगर (err)
		वापस err;
	err = devlink_fmsg_u8_pair_put(fmsg, "synd", ioपढ़ो8(&h->synd));
	अगर (err)
		वापस err;
	err = devlink_fmsg_u32_pair_put(fmsg, "ext_synd",
					ioपढ़ो16be(&h->ext_synd));
	अगर (err)
		वापस err;
	err = devlink_fmsg_u32_pair_put(fmsg, "raw_fw_ver",
					ioपढ़ो32be(&h->fw_ver));
	अगर (err)
		वापस err;
	err = devlink_fmsg_obj_nest_end(fmsg);
	अगर (err)
		वापस err;
	वापस devlink_fmsg_pair_nest_end(fmsg);
पूर्ण

अटल पूर्णांक
mlx5_fw_reporter_dump(काष्ठा devlink_health_reporter *reporter,
		      काष्ठा devlink_fmsg *fmsg, व्योम *priv_ctx,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_health_reporter_priv(reporter);
	पूर्णांक err;

	err = mlx5_fw_tracer_trigger_core_dump_general(dev);
	अगर (err)
		वापस err;

	अगर (priv_ctx) अणु
		काष्ठा mlx5_fw_reporter_ctx *fw_reporter_ctx = priv_ctx;

		err = mlx5_fw_reporter_ctx_pairs_put(fmsg, fw_reporter_ctx);
		अगर (err)
			वापस err;
	पूर्ण

	err = mlx5_fw_reporter_heath_buffer_data_put(dev, fmsg);
	अगर (err)
		वापस err;
	वापस mlx5_fw_tracer_get_saved_traces_objects(dev->tracer, fmsg);
पूर्ण

अटल व्योम mlx5_fw_reporter_err_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_fw_reporter_ctx fw_reporter_ctx;
	काष्ठा mlx5_core_health *health;

	health = container_of(work, काष्ठा mlx5_core_health, report_work);

	अगर (IS_ERR_OR_शून्य(health->fw_reporter))
		वापस;

	fw_reporter_ctx.err_synd = health->synd;
	fw_reporter_ctx.miss_counter = health->miss_counter;
	अगर (fw_reporter_ctx.err_synd) अणु
		devlink_health_report(health->fw_reporter,
				      "FW syndrom reported", &fw_reporter_ctx);
		वापस;
	पूर्ण
	अगर (fw_reporter_ctx.miss_counter)
		devlink_health_report(health->fw_reporter,
				      "FW miss counter reported",
				      &fw_reporter_ctx);
पूर्ण

अटल स्थिर काष्ठा devlink_health_reporter_ops mlx5_fw_reporter_ops = अणु
		.name = "fw",
		.diagnose = mlx5_fw_reporter_diagnose,
		.dump = mlx5_fw_reporter_dump,
पूर्ण;

अटल पूर्णांक
mlx5_fw_fatal_reporter_recover(काष्ठा devlink_health_reporter *reporter,
			       व्योम *priv_ctx,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_health_reporter_priv(reporter);

	वापस mlx5_health_try_recover(dev);
पूर्ण

अटल पूर्णांक
mlx5_fw_fatal_reporter_dump(काष्ठा devlink_health_reporter *reporter,
			    काष्ठा devlink_fmsg *fmsg, व्योम *priv_ctx,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_health_reporter_priv(reporter);
	u32 crdump_size = dev->priv.health.crdump_size;
	u32 *cr_data;
	पूर्णांक err;

	अगर (!mlx5_core_is_pf(dev))
		वापस -EPERM;

	cr_data = kvदो_स्मृति(crdump_size, GFP_KERNEL);
	अगर (!cr_data)
		वापस -ENOMEM;
	err = mlx5_crdump_collect(dev, cr_data);
	अगर (err)
		जाओ मुक्त_data;

	अगर (priv_ctx) अणु
		काष्ठा mlx5_fw_reporter_ctx *fw_reporter_ctx = priv_ctx;

		err = mlx5_fw_reporter_ctx_pairs_put(fmsg, fw_reporter_ctx);
		अगर (err)
			जाओ मुक्त_data;
	पूर्ण

	err = devlink_fmsg_binary_pair_put(fmsg, "crdump_data", cr_data, crdump_size);

मुक्त_data:
	kvमुक्त(cr_data);
	वापस err;
पूर्ण

अटल व्योम mlx5_fw_fatal_reporter_err_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_fw_reporter_ctx fw_reporter_ctx;
	काष्ठा mlx5_core_health *health;
	काष्ठा mlx5_core_dev *dev;
	काष्ठा mlx5_priv *priv;

	health = container_of(work, काष्ठा mlx5_core_health, fatal_report_work);
	priv = container_of(health, काष्ठा mlx5_priv, health);
	dev = container_of(priv, काष्ठा mlx5_core_dev, priv);

	enter_error_state(dev, false);
	अगर (IS_ERR_OR_शून्य(health->fw_fatal_reporter)) अणु
		अगर (mlx5_health_try_recover(dev))
			mlx5_core_err(dev, "health recovery failed\n");
		वापस;
	पूर्ण
	fw_reporter_ctx.err_synd = health->synd;
	fw_reporter_ctx.miss_counter = health->miss_counter;
	devlink_health_report(health->fw_fatal_reporter,
			      "FW fatal error reported", &fw_reporter_ctx);
पूर्ण

अटल स्थिर काष्ठा devlink_health_reporter_ops mlx5_fw_fatal_reporter_ops = अणु
		.name = "fw_fatal",
		.recover = mlx5_fw_fatal_reporter_recover,
		.dump = mlx5_fw_fatal_reporter_dump,
पूर्ण;

#घोषणा MLX5_REPORTER_FW_GRACEFUL_PERIOD 1200000
अटल व्योम mlx5_fw_reporters_create(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_health *health = &dev->priv.health;
	काष्ठा devlink *devlink = priv_to_devlink(dev);

	health->fw_reporter =
		devlink_health_reporter_create(devlink, &mlx5_fw_reporter_ops,
					       0, dev);
	अगर (IS_ERR(health->fw_reporter))
		mlx5_core_warn(dev, "Failed to create fw reporter, err = %ld\n",
			       PTR_ERR(health->fw_reporter));

	health->fw_fatal_reporter =
		devlink_health_reporter_create(devlink,
					       &mlx5_fw_fatal_reporter_ops,
					       MLX5_REPORTER_FW_GRACEFUL_PERIOD,
					       dev);
	अगर (IS_ERR(health->fw_fatal_reporter))
		mlx5_core_warn(dev, "Failed to create fw fatal reporter, err = %ld\n",
			       PTR_ERR(health->fw_fatal_reporter));
पूर्ण

अटल व्योम mlx5_fw_reporters_destroy(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_health *health = &dev->priv.health;

	अगर (!IS_ERR_OR_शून्य(health->fw_reporter))
		devlink_health_reporter_destroy(health->fw_reporter);

	अगर (!IS_ERR_OR_शून्य(health->fw_fatal_reporter))
		devlink_health_reporter_destroy(health->fw_fatal_reporter);
पूर्ण

अटल अचिन्हित दीर्घ get_next_poll_jअगरfies(व्योम)
अणु
	अचिन्हित दीर्घ next;

	get_अक्रमom_bytes(&next, माप(next));
	next %= HZ;
	next += jअगरfies + MLX5_HEALTH_POLL_INTERVAL;

	वापस next;
पूर्ण

व्योम mlx5_trigger_health_work(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_health *health = &dev->priv.health;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&health->wq_lock, flags);
	अगर (!test_bit(MLX5_DROP_NEW_HEALTH_WORK, &health->flags))
		queue_work(health->wq, &health->fatal_report_work);
	अन्यथा
		mlx5_core_err(dev, "new health works are not permitted at this stage\n");
	spin_unlock_irqrestore(&health->wq_lock, flags);
पूर्ण

अटल व्योम poll_health(काष्ठा समयr_list *t)
अणु
	काष्ठा mlx5_core_dev *dev = from_समयr(dev, t, priv.health.समयr);
	काष्ठा mlx5_core_health *health = &dev->priv.health;
	काष्ठा health_buffer __iomem *h = health->health;
	u32 fatal_error;
	u8 prev_synd;
	u32 count;

	अगर (dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR)
		जाओ out;

	fatal_error = mlx5_health_check_fatal_sensors(dev);

	अगर (fatal_error && !health->fatal_error) अणु
		mlx5_core_err(dev, "Fatal error %u detected\n", fatal_error);
		dev->priv.health.fatal_error = fatal_error;
		prपूर्णांक_health_info(dev);
		dev->state = MLX5_DEVICE_STATE_INTERNAL_ERROR;
		mlx5_trigger_health_work(dev);
		वापस;
	पूर्ण

	count = ioपढ़ो32be(health->health_counter);
	अगर (count == health->prev)
		++health->miss_counter;
	अन्यथा
		health->miss_counter = 0;

	health->prev = count;
	अगर (health->miss_counter == MAX_MISSES) अणु
		mlx5_core_err(dev, "device's health compromised - reached miss count\n");
		prपूर्णांक_health_info(dev);
		queue_work(health->wq, &health->report_work);
	पूर्ण

	prev_synd = health->synd;
	health->synd = ioपढ़ो8(&h->synd);
	अगर (health->synd && health->synd != prev_synd)
		queue_work(health->wq, &health->report_work);

out:
	mod_समयr(&health->समयr, get_next_poll_jअगरfies());
पूर्ण

व्योम mlx5_start_health_poll(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_health *health = &dev->priv.health;

	समयr_setup(&health->समयr, poll_health, 0);
	health->fatal_error = MLX5_SENSOR_NO_ERR;
	clear_bit(MLX5_DROP_NEW_HEALTH_WORK, &health->flags);
	health->health = &dev->iseg->health;
	health->health_counter = &dev->iseg->health_counter;

	health->समयr.expires = round_jअगरfies(jअगरfies + MLX5_HEALTH_POLL_INTERVAL);
	add_समयr(&health->समयr);
पूर्ण

व्योम mlx5_stop_health_poll(काष्ठा mlx5_core_dev *dev, bool disable_health)
अणु
	काष्ठा mlx5_core_health *health = &dev->priv.health;
	अचिन्हित दीर्घ flags;

	अगर (disable_health) अणु
		spin_lock_irqsave(&health->wq_lock, flags);
		set_bit(MLX5_DROP_NEW_HEALTH_WORK, &health->flags);
		spin_unlock_irqrestore(&health->wq_lock, flags);
	पूर्ण

	del_समयr_sync(&health->समयr);
पूर्ण

व्योम mlx5_drain_health_wq(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_health *health = &dev->priv.health;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&health->wq_lock, flags);
	set_bit(MLX5_DROP_NEW_HEALTH_WORK, &health->flags);
	spin_unlock_irqrestore(&health->wq_lock, flags);
	cancel_work_sync(&health->report_work);
	cancel_work_sync(&health->fatal_report_work);
पूर्ण

व्योम mlx5_health_flush(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_health *health = &dev->priv.health;

	flush_workqueue(health->wq);
पूर्ण

व्योम mlx5_health_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_health *health = &dev->priv.health;

	destroy_workqueue(health->wq);
	mlx5_fw_reporters_destroy(dev);
पूर्ण

पूर्णांक mlx5_health_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_health *health;
	अक्षर *name;

	mlx5_fw_reporters_create(dev);

	health = &dev->priv.health;
	name = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!name)
		जाओ out_err;

	म_नकल(name, "mlx5_health");
	म_जोड़ो(name, dev_name(dev->device));
	health->wq = create_singlethपढ़ो_workqueue(name);
	kमुक्त(name);
	अगर (!health->wq)
		जाओ out_err;
	spin_lock_init(&health->wq_lock);
	INIT_WORK(&health->fatal_report_work, mlx5_fw_fatal_reporter_err_work);
	INIT_WORK(&health->report_work, mlx5_fw_reporter_err_work);

	वापस 0;

out_err:
	mlx5_fw_reporters_destroy(dev);
	वापस -ENOMEM;
पूर्ण
