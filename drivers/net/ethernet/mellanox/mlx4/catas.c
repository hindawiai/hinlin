<शैली गुरु>
/*
 * Copyright (c) 2007 Cisco Systems, Inc. All rights reserved.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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

#समावेश <linux/workqueue.h>
#समावेश <linux/module.h>

#समावेश "mlx4.h"

क्रमागत अणु
	MLX4_CATAS_POLL_INTERVAL	= 5 * HZ,
पूर्ण;



पूर्णांक mlx4_पूर्णांकernal_err_reset = 1;
module_param_named(पूर्णांकernal_err_reset, mlx4_पूर्णांकernal_err_reset,  पूर्णांक, 0644);
MODULE_PARM_DESC(पूर्णांकernal_err_reset,
		 "Reset device on internal errors if non-zero (default 1)");

अटल पूर्णांक पढ़ो_venकरोr_id(काष्ठा mlx4_dev *dev)
अणु
	u16 venकरोr_id = 0;
	पूर्णांक ret;

	ret = pci_पढ़ो_config_word(dev->persist->pdev, 0, &venकरोr_id);
	अगर (ret) अणु
		mlx4_err(dev, "Failed to read vendor ID, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	अगर (venकरोr_id == 0xffff) अणु
		mlx4_err(dev, "PCI can't be accessed to read vendor id\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_reset_master(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक err = 0;

	अगर (mlx4_is_master(dev))
		mlx4_report_पूर्णांकernal_err_comm_event(dev);

	अगर (!pci_channel_offline(dev->persist->pdev)) अणु
		err = पढ़ो_venकरोr_id(dev);
		/* If PCI can't be accessed to पढ़ो venकरोr ID we assume that its
		 * link was disabled and chip was alपढ़ोy reset.
		 */
		अगर (err)
			वापस 0;

		err = mlx4_reset(dev);
		अगर (err)
			mlx4_err(dev, "Fail to reset HCA\n");
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_reset_slave(काष्ठा mlx4_dev *dev)
अणु
#घोषणा COM_CHAN_RST_REQ_OFFSET 0x10
#घोषणा COM_CHAN_RST_ACK_OFFSET 0x08

	u32 comm_flags;
	u32 rst_req;
	u32 rst_ack;
	अचिन्हित दीर्घ end;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	अगर (pci_channel_offline(dev->persist->pdev))
		वापस 0;

	comm_flags = swab32(पढ़ोl((__iomem अक्षर *)priv->mfunc.comm +
				  MLX4_COMM_CHAN_FLAGS));
	अगर (comm_flags == 0xffffffff) अणु
		mlx4_err(dev, "VF reset is not needed\n");
		वापस 0;
	पूर्ण

	अगर (!(dev->caps.vf_caps & MLX4_VF_CAP_FLAG_RESET)) अणु
		mlx4_err(dev, "VF reset is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	rst_req = (comm_flags & (u32)(1 << COM_CHAN_RST_REQ_OFFSET)) >>
		COM_CHAN_RST_REQ_OFFSET;
	rst_ack = (comm_flags & (u32)(1 << COM_CHAN_RST_ACK_OFFSET)) >>
		COM_CHAN_RST_ACK_OFFSET;
	अगर (rst_req != rst_ack) अणु
		mlx4_err(dev, "Communication channel isn't sync, fail to send reset\n");
		वापस -EIO;
	पूर्ण

	rst_req ^= 1;
	mlx4_warn(dev, "VF is sending reset request to Firmware\n");
	comm_flags = rst_req << COM_CHAN_RST_REQ_OFFSET;
	__raw_ग_लिखोl((__क्रमce u32)cpu_to_be32(comm_flags),
		     (__iomem अक्षर *)priv->mfunc.comm + MLX4_COMM_CHAN_FLAGS);

	end = msecs_to_jअगरfies(MLX4_COMM_TIME) + jअगरfies;
	जबतक (समय_beक्रमe(jअगरfies, end)) अणु
		comm_flags = swab32(पढ़ोl((__iomem अक्षर *)priv->mfunc.comm +
					  MLX4_COMM_CHAN_FLAGS));
		rst_ack = (comm_flags & (u32)(1 << COM_CHAN_RST_ACK_OFFSET)) >>
			COM_CHAN_RST_ACK_OFFSET;

		/* Reading rst_req again since the communication channel can
		 * be reset at any समय by the PF and all its bits will be
		 * set to zero.
		 */
		rst_req = (comm_flags & (u32)(1 << COM_CHAN_RST_REQ_OFFSET)) >>
			COM_CHAN_RST_REQ_OFFSET;

		अगर (rst_ack == rst_req) अणु
			mlx4_warn(dev, "VF Reset succeed\n");
			वापस 0;
		पूर्ण
		cond_resched();
	पूर्ण
	mlx4_err(dev, "Fail to send reset over the communication channel\n");
	वापस -ETIMEDOUT;
पूर्ण

पूर्णांक mlx4_comm_पूर्णांकernal_err(u32 slave_पढ़ो)
अणु
	वापस (u32)COMM_CHAN_EVENT_INTERNAL_ERR ==
		(slave_पढ़ो & (u32)COMM_CHAN_EVENT_INTERNAL_ERR) ? 1 : 0;
पूर्ण

व्योम mlx4_enter_error_state(काष्ठा mlx4_dev_persistent *persist)
अणु
	पूर्णांक err;
	काष्ठा mlx4_dev *dev;

	अगर (!mlx4_पूर्णांकernal_err_reset)
		वापस;

	mutex_lock(&persist->device_state_mutex);
	अगर (persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)
		जाओ out;

	dev = persist->dev;
	mlx4_err(dev, "device is going to be reset\n");
	अगर (mlx4_is_slave(dev)) अणु
		err = mlx4_reset_slave(dev);
	पूर्ण अन्यथा अणु
		mlx4_crdump_collect(dev);
		err = mlx4_reset_master(dev);
	पूर्ण

	अगर (!err) अणु
		mlx4_err(dev, "device was reset successfully\n");
	पूर्ण अन्यथा अणु
		/* EEH could have disabled the PCI channel during reset. That's
		 * recoverable and the PCI error flow will handle it.
		 */
		अगर (!pci_channel_offline(dev->persist->pdev))
			BUG_ON(1);
	पूर्ण
	dev->persist->state |= MLX4_DEVICE_STATE_INTERNAL_ERROR;
	mutex_unlock(&persist->device_state_mutex);

	/* At that step HW was alपढ़ोy reset, now notअगरy clients */
	mlx4_dispatch_event(dev, MLX4_DEV_EVENT_CATASTROPHIC_ERROR, 0);
	mlx4_cmd_wake_completions(dev);
	वापस;

out:
	mutex_unlock(&persist->device_state_mutex);
पूर्ण

अटल व्योम mlx4_handle_error_state(काष्ठा mlx4_dev_persistent *persist)
अणु
	पूर्णांक err = 0;

	mlx4_enter_error_state(persist);
	mutex_lock(&persist->पूर्णांकerface_state_mutex);
	अगर (persist->पूर्णांकerface_state & MLX4_INTERFACE_STATE_UP &&
	    !(persist->पूर्णांकerface_state & MLX4_INTERFACE_STATE_DELETION)) अणु
		err = mlx4_restart_one(persist->pdev);
		mlx4_info(persist->dev, "mlx4_restart_one was ended, ret=%d\n",
			  err);
	पूर्ण
	mutex_unlock(&persist->पूर्णांकerface_state_mutex);
पूर्ण

अटल व्योम dump_err_buf(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	पूर्णांक i;

	mlx4_err(dev, "Internal error detected:\n");
	क्रम (i = 0; i < priv->fw.catas_size; ++i)
		mlx4_err(dev, "  buf[%02x]: %08x\n",
			 i, swab32(पढ़ोl(priv->catas_err.map + i)));
पूर्ण

अटल व्योम poll_catas(काष्ठा समयr_list *t)
अणु
	काष्ठा mlx4_priv *priv = from_समयr(priv, t, catas_err.समयr);
	काष्ठा mlx4_dev *dev = &priv->dev;
	u32 slave_पढ़ो;

	अगर (mlx4_is_slave(dev)) अणु
		slave_पढ़ो = swab32(पढ़ोl(&priv->mfunc.comm->slave_पढ़ो));
		अगर (mlx4_comm_पूर्णांकernal_err(slave_पढ़ो)) अणु
			mlx4_warn(dev, "Internal error detected on the communication channel\n");
			जाओ पूर्णांकernal_err;
		पूर्ण
	पूर्ण अन्यथा अगर (पढ़ोl(priv->catas_err.map)) अणु
		dump_err_buf(dev);
		जाओ पूर्णांकernal_err;
	पूर्ण

	अगर (dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR) अणु
		mlx4_warn(dev, "Internal error mark was detected on device\n");
		जाओ पूर्णांकernal_err;
	पूर्ण

	mod_समयr(&priv->catas_err.समयr,
		  round_jअगरfies(jअगरfies + MLX4_CATAS_POLL_INTERVAL));
	वापस;

पूर्णांकernal_err:
	अगर (mlx4_पूर्णांकernal_err_reset)
		queue_work(dev->persist->catas_wq, &dev->persist->catas_work);
पूर्ण

अटल व्योम catas_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_dev_persistent *persist =
		container_of(work, काष्ठा mlx4_dev_persistent,
			     catas_work);

	mlx4_handle_error_state(persist);
पूर्ण

व्योम mlx4_start_catas_poll(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	phys_addr_t addr;

	INIT_LIST_HEAD(&priv->catas_err.list);
	समयr_setup(&priv->catas_err.समयr, poll_catas, 0);
	priv->catas_err.map = शून्य;

	अगर (!mlx4_is_slave(dev)) अणु
		addr = pci_resource_start(dev->persist->pdev,
					  priv->fw.catas_bar) +
					  priv->fw.catas_offset;

		priv->catas_err.map = ioremap(addr, priv->fw.catas_size * 4);
		अगर (!priv->catas_err.map) अणु
			mlx4_warn(dev, "Failed to map internal error buffer at 0x%llx\n",
				  (अचिन्हित दीर्घ दीर्घ)addr);
			वापस;
		पूर्ण
	पूर्ण

	priv->catas_err.समयr.expires  =
		round_jअगरfies(jअगरfies + MLX4_CATAS_POLL_INTERVAL);
	add_समयr(&priv->catas_err.समयr);
पूर्ण

व्योम mlx4_stop_catas_poll(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	del_समयr_sync(&priv->catas_err.समयr);

	अगर (priv->catas_err.map) अणु
		iounmap(priv->catas_err.map);
		priv->catas_err.map = शून्य;
	पूर्ण

	अगर (dev->persist->पूर्णांकerface_state & MLX4_INTERFACE_STATE_DELETION)
		flush_workqueue(dev->persist->catas_wq);
पूर्ण

पूर्णांक  mlx4_catas_init(काष्ठा mlx4_dev *dev)
अणु
	INIT_WORK(&dev->persist->catas_work, catas_reset);
	dev->persist->catas_wq = create_singlethपढ़ो_workqueue("mlx4_health");
	अगर (!dev->persist->catas_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम mlx4_catas_end(काष्ठा mlx4_dev *dev)
अणु
	अगर (dev->persist->catas_wq) अणु
		destroy_workqueue(dev->persist->catas_wq);
		dev->persist->catas_wq = शून्य;
	पूर्ण
पूर्ण
