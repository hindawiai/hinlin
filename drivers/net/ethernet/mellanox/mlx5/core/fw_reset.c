<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020, Mellanox Technologies inc.  All rights reserved. */

#समावेश "fw_reset.h"
#समावेश "diag/fw_tracer.h"

क्रमागत अणु
	MLX5_FW_RESET_FLAGS_RESET_REQUESTED,
	MLX5_FW_RESET_FLAGS_NACK_RESET_REQUEST,
	MLX5_FW_RESET_FLAGS_PENDING_COMP
पूर्ण;

काष्ठा mlx5_fw_reset अणु
	काष्ठा mlx5_core_dev *dev;
	काष्ठा mlx5_nb nb;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा fw_live_patch_work;
	काष्ठा work_काष्ठा reset_request_work;
	काष्ठा work_काष्ठा reset_reload_work;
	काष्ठा work_काष्ठा reset_now_work;
	काष्ठा work_काष्ठा reset_पात_work;
	अचिन्हित दीर्घ reset_flags;
	काष्ठा समयr_list समयr;
	काष्ठा completion करोne;
	पूर्णांक ret;
पूर्ण;

व्योम mlx5_fw_reset_enable_remote_dev_reset_set(काष्ठा mlx5_core_dev *dev, bool enable)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = dev->priv.fw_reset;

	अगर (enable)
		clear_bit(MLX5_FW_RESET_FLAGS_NACK_RESET_REQUEST, &fw_reset->reset_flags);
	अन्यथा
		set_bit(MLX5_FW_RESET_FLAGS_NACK_RESET_REQUEST, &fw_reset->reset_flags);
पूर्ण

bool mlx5_fw_reset_enable_remote_dev_reset_get(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = dev->priv.fw_reset;

	वापस !test_bit(MLX5_FW_RESET_FLAGS_NACK_RESET_REQUEST, &fw_reset->reset_flags);
पूर्ण

अटल पूर्णांक mlx5_reg_mfrl_set(काष्ठा mlx5_core_dev *dev, u8 reset_level,
			     u8 reset_type_sel, u8 sync_resp, bool sync_start)
अणु
	u32 out[MLX5_ST_SZ_DW(mfrl_reg)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(mfrl_reg)] = अणुपूर्ण;

	MLX5_SET(mfrl_reg, in, reset_level, reset_level);
	MLX5_SET(mfrl_reg, in, rst_type_sel, reset_type_sel);
	MLX5_SET(mfrl_reg, in, pci_sync_क्रम_fw_update_resp, sync_resp);
	MLX5_SET(mfrl_reg, in, pci_sync_क्रम_fw_update_start, sync_start);

	वापस mlx5_core_access_reg(dev, in, माप(in), out, माप(out), MLX5_REG_MFRL, 0, 1);
पूर्ण

अटल पूर्णांक mlx5_reg_mfrl_query(काष्ठा mlx5_core_dev *dev, u8 *reset_level, u8 *reset_type)
अणु
	u32 out[MLX5_ST_SZ_DW(mfrl_reg)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(mfrl_reg)] = अणुपूर्ण;
	पूर्णांक err;

	err = mlx5_core_access_reg(dev, in, माप(in), out, माप(out), MLX5_REG_MFRL, 0, 0);
	अगर (err)
		वापस err;

	अगर (reset_level)
		*reset_level = MLX5_GET(mfrl_reg, out, reset_level);
	अगर (reset_type)
		*reset_type = MLX5_GET(mfrl_reg, out, reset_type);

	वापस 0;
पूर्ण

पूर्णांक mlx5_fw_reset_query(काष्ठा mlx5_core_dev *dev, u8 *reset_level, u8 *reset_type)
अणु
	वापस mlx5_reg_mfrl_query(dev, reset_level, reset_type);
पूर्ण

पूर्णांक mlx5_fw_reset_set_reset_sync(काष्ठा mlx5_core_dev *dev, u8 reset_type_sel)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = dev->priv.fw_reset;
	पूर्णांक err;

	set_bit(MLX5_FW_RESET_FLAGS_PENDING_COMP, &fw_reset->reset_flags);
	err = mlx5_reg_mfrl_set(dev, MLX5_MFRL_REG_RESET_LEVEL3, reset_type_sel, 0, true);
	अगर (err)
		clear_bit(MLX5_FW_RESET_FLAGS_PENDING_COMP, &fw_reset->reset_flags);
	वापस err;
पूर्ण

पूर्णांक mlx5_fw_reset_set_live_patch(काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5_reg_mfrl_set(dev, MLX5_MFRL_REG_RESET_LEVEL0, 0, 0, false);
पूर्ण

अटल व्योम mlx5_fw_reset_complete_reload(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = dev->priv.fw_reset;

	/* अगर this is the driver that initiated the fw reset, devlink completed the reload */
	अगर (test_bit(MLX5_FW_RESET_FLAGS_PENDING_COMP, &fw_reset->reset_flags)) अणु
		complete(&fw_reset->करोne);
	पूर्ण अन्यथा अणु
		mlx5_load_one(dev);
		devlink_remote_reload_actions_perक्रमmed(priv_to_devlink(dev), 0,
							BIT(DEVLINK_RELOAD_ACTION_DRIVER_REINIT) |
							BIT(DEVLINK_RELOAD_ACTION_FW_ACTIVATE));
	पूर्ण
पूर्ण

अटल व्योम mlx5_sync_reset_reload_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = container_of(work, काष्ठा mlx5_fw_reset,
						      reset_reload_work);
	काष्ठा mlx5_core_dev *dev = fw_reset->dev;
	पूर्णांक err;

	mlx5_enter_error_state(dev, true);
	mlx5_unload_one(dev);
	err = mlx5_health_रुको_pci_up(dev);
	अगर (err)
		mlx5_core_err(dev, "reset reload flow aborted, PCI reads still not working\n");
	fw_reset->ret = err;
	mlx5_fw_reset_complete_reload(dev);
पूर्ण

अटल व्योम mlx5_stop_sync_reset_poll(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = dev->priv.fw_reset;

	del_समयr(&fw_reset->समयr);
पूर्ण

अटल व्योम mlx5_sync_reset_clear_reset_requested(काष्ठा mlx5_core_dev *dev, bool poll_health)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = dev->priv.fw_reset;

	mlx5_stop_sync_reset_poll(dev);
	clear_bit(MLX5_FW_RESET_FLAGS_RESET_REQUESTED, &fw_reset->reset_flags);
	अगर (poll_health)
		mlx5_start_health_poll(dev);
पूर्ण

#घोषणा MLX5_RESET_POLL_INTERVAL	(HZ / 10)
अटल व्योम poll_sync_reset(काष्ठा समयr_list *t)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = from_समयr(fw_reset, t, समयr);
	काष्ठा mlx5_core_dev *dev = fw_reset->dev;
	u32 fatal_error;

	अगर (!test_bit(MLX5_FW_RESET_FLAGS_RESET_REQUESTED, &fw_reset->reset_flags))
		वापस;

	fatal_error = mlx5_health_check_fatal_sensors(dev);

	अगर (fatal_error) अणु
		mlx5_core_warn(dev, "Got Device Reset\n");
		mlx5_sync_reset_clear_reset_requested(dev, false);
		queue_work(fw_reset->wq, &fw_reset->reset_reload_work);
		वापस;
	पूर्ण

	mod_समयr(&fw_reset->समयr, round_jअगरfies(jअगरfies + MLX5_RESET_POLL_INTERVAL));
पूर्ण

अटल व्योम mlx5_start_sync_reset_poll(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = dev->priv.fw_reset;

	समयr_setup(&fw_reset->समयr, poll_sync_reset, 0);
	fw_reset->समयr.expires = round_jअगरfies(jअगरfies + MLX5_RESET_POLL_INTERVAL);
	add_समयr(&fw_reset->समयr);
पूर्ण

अटल पूर्णांक mlx5_fw_reset_set_reset_sync_ack(काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5_reg_mfrl_set(dev, MLX5_MFRL_REG_RESET_LEVEL3, 0, 1, false);
पूर्ण

अटल पूर्णांक mlx5_fw_reset_set_reset_sync_nack(काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5_reg_mfrl_set(dev, MLX5_MFRL_REG_RESET_LEVEL3, 0, 2, false);
पूर्ण

अटल व्योम mlx5_sync_reset_set_reset_requested(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = dev->priv.fw_reset;

	mlx5_stop_health_poll(dev, true);
	set_bit(MLX5_FW_RESET_FLAGS_RESET_REQUESTED, &fw_reset->reset_flags);
	mlx5_start_sync_reset_poll(dev);
पूर्ण

अटल व्योम mlx5_fw_live_patch_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = container_of(work, काष्ठा mlx5_fw_reset,
						      fw_live_patch_work);
	काष्ठा mlx5_core_dev *dev = fw_reset->dev;

	mlx5_core_info(dev, "Live patch updated firmware version: %d.%d.%d\n", fw_rev_maj(dev),
		       fw_rev_min(dev), fw_rev_sub(dev));

	अगर (mlx5_fw_tracer_reload(dev->tracer))
		mlx5_core_err(dev, "Failed to reload FW tracer\n");
पूर्ण

अटल व्योम mlx5_sync_reset_request_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = container_of(work, काष्ठा mlx5_fw_reset,
						      reset_request_work);
	काष्ठा mlx5_core_dev *dev = fw_reset->dev;
	पूर्णांक err;

	अगर (test_bit(MLX5_FW_RESET_FLAGS_NACK_RESET_REQUEST, &fw_reset->reset_flags)) अणु
		err = mlx5_fw_reset_set_reset_sync_nack(dev);
		mlx5_core_warn(dev, "PCI Sync FW Update Reset Nack %s",
			       err ? "Failed" : "Sent");
		वापस;
	पूर्ण
	mlx5_sync_reset_set_reset_requested(dev);
	err = mlx5_fw_reset_set_reset_sync_ack(dev);
	अगर (err)
		mlx5_core_warn(dev, "PCI Sync FW Update Reset Ack Failed. Error code: %d\n", err);
	अन्यथा
		mlx5_core_warn(dev, "PCI Sync FW Update Reset Ack. Device reset is expected.\n");
पूर्ण

#घोषणा MLX5_PCI_LINK_UP_TIMEOUT 2000

अटल पूर्णांक mlx5_pci_link_toggle(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा pci_bus *bridge_bus = dev->pdev->bus;
	काष्ठा pci_dev *bridge = bridge_bus->self;
	u16 reg16, dev_id, sdev_id;
	अचिन्हित दीर्घ समयout;
	काष्ठा pci_dev *sdev;
	पूर्णांक cap, err;
	u32 reg32;

	/* Check that all functions under the pci bridge are PFs of
	 * this device otherwise fail this function.
	 */
	err = pci_पढ़ो_config_word(dev->pdev, PCI_DEVICE_ID, &dev_id);
	अगर (err)
		वापस err;
	list_क्रम_each_entry(sdev, &bridge_bus->devices, bus_list) अणु
		err = pci_पढ़ो_config_word(sdev, PCI_DEVICE_ID, &sdev_id);
		अगर (err)
			वापस err;
		अगर (sdev_id != dev_id)
			वापस -EPERM;
	पूर्ण

	cap = pci_find_capability(bridge, PCI_CAP_ID_EXP);
	अगर (!cap)
		वापस -EOPNOTSUPP;

	list_क्रम_each_entry(sdev, &bridge_bus->devices, bus_list) अणु
		pci_save_state(sdev);
		pci_cfg_access_lock(sdev);
	पूर्ण
	/* PCI link toggle */
	err = pci_पढ़ो_config_word(bridge, cap + PCI_EXP_LNKCTL, &reg16);
	अगर (err)
		वापस err;
	reg16 |= PCI_EXP_LNKCTL_LD;
	err = pci_ग_लिखो_config_word(bridge, cap + PCI_EXP_LNKCTL, reg16);
	अगर (err)
		वापस err;
	msleep(500);
	reg16 &= ~PCI_EXP_LNKCTL_LD;
	err = pci_ग_लिखो_config_word(bridge, cap + PCI_EXP_LNKCTL, reg16);
	अगर (err)
		वापस err;

	/* Check link */
	err = pci_पढ़ो_config_dword(bridge, cap + PCI_EXP_LNKCAP, &reg32);
	अगर (err)
		वापस err;
	अगर (!(reg32 & PCI_EXP_LNKCAP_DLLLARC)) अणु
		mlx5_core_warn(dev, "No PCI link reporting capability (0x%08x)\n", reg32);
		msleep(1000);
		जाओ restore;
	पूर्ण

	समयout = jअगरfies + msecs_to_jअगरfies(MLX5_PCI_LINK_UP_TIMEOUT);
	करो अणु
		err = pci_पढ़ो_config_word(bridge, cap + PCI_EXP_LNKSTA, &reg16);
		अगर (err)
			वापस err;
		अगर (reg16 & PCI_EXP_LNKSTA_DLLLA)
			अवरोध;
		msleep(20);
	पूर्ण जबतक (!समय_after(jअगरfies, समयout));

	अगर (reg16 & PCI_EXP_LNKSTA_DLLLA) अणु
		mlx5_core_info(dev, "PCI Link up\n");
	पूर्ण अन्यथा अणु
		mlx5_core_err(dev, "PCI link not ready (0x%04x) after %d ms\n",
			      reg16, MLX5_PCI_LINK_UP_TIMEOUT);
		err = -ETIMEDOUT;
	पूर्ण

restore:
	list_क्रम_each_entry(sdev, &bridge_bus->devices, bus_list) अणु
		pci_cfg_access_unlock(sdev);
		pci_restore_state(sdev);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम mlx5_sync_reset_now_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = container_of(work, काष्ठा mlx5_fw_reset,
						      reset_now_work);
	काष्ठा mlx5_core_dev *dev = fw_reset->dev;
	पूर्णांक err;

	mlx5_sync_reset_clear_reset_requested(dev, false);

	mlx5_core_warn(dev, "Sync Reset now. Device is going to reset.\n");

	err = mlx5_cmd_fast_tearकरोwn_hca(dev);
	अगर (err) अणु
		mlx5_core_warn(dev, "Fast teardown failed, no reset done, err %d\n", err);
		जाओ करोne;
	पूर्ण

	err = mlx5_pci_link_toggle(dev);
	अगर (err) अणु
		mlx5_core_warn(dev, "mlx5_pci_link_toggle failed, no reset done, err %d\n", err);
		जाओ करोne;
	पूर्ण

	mlx5_enter_error_state(dev, true);
	mlx5_unload_one(dev);
करोne:
	fw_reset->ret = err;
	mlx5_fw_reset_complete_reload(dev);
पूर्ण

अटल व्योम mlx5_sync_reset_पात_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = container_of(work, काष्ठा mlx5_fw_reset,
						      reset_पात_work);
	काष्ठा mlx5_core_dev *dev = fw_reset->dev;

	अगर (!test_bit(MLX5_FW_RESET_FLAGS_RESET_REQUESTED, &fw_reset->reset_flags))
		वापस;

	mlx5_sync_reset_clear_reset_requested(dev, true);
	mlx5_core_warn(dev, "PCI Sync FW Update Reset Aborted.\n");
पूर्ण

अटल व्योम mlx5_sync_reset_events_handle(काष्ठा mlx5_fw_reset *fw_reset, काष्ठा mlx5_eqe *eqe)
अणु
	काष्ठा mlx5_eqe_sync_fw_update *sync_fw_update_eqe;
	u8 sync_event_rst_type;

	sync_fw_update_eqe = &eqe->data.sync_fw_update;
	sync_event_rst_type = sync_fw_update_eqe->sync_rst_state & SYNC_RST_STATE_MASK;
	चयन (sync_event_rst_type) अणु
	हाल MLX5_SYNC_RST_STATE_RESET_REQUEST:
		queue_work(fw_reset->wq, &fw_reset->reset_request_work);
		अवरोध;
	हाल MLX5_SYNC_RST_STATE_RESET_NOW:
		queue_work(fw_reset->wq, &fw_reset->reset_now_work);
		अवरोध;
	हाल MLX5_SYNC_RST_STATE_RESET_ABORT:
		queue_work(fw_reset->wq, &fw_reset->reset_पात_work);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक fw_reset_event_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = mlx5_nb_cof(nb, काष्ठा mlx5_fw_reset, nb);
	काष्ठा mlx5_eqe *eqe = data;

	चयन (eqe->sub_type) अणु
	हाल MLX5_GENERAL_SUBTYPE_FW_LIVE_PATCH_EVENT:
			queue_work(fw_reset->wq, &fw_reset->fw_live_patch_work);
		अवरोध;
	हाल MLX5_GENERAL_SUBTYPE_PCI_SYNC_FOR_FW_UPDATE_EVENT:
		mlx5_sync_reset_events_handle(fw_reset, eqe);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

#घोषणा MLX5_FW_RESET_TIMEOUT_MSEC 5000
पूर्णांक mlx5_fw_reset_रुको_reset_करोne(काष्ठा mlx5_core_dev *dev)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(MLX5_FW_RESET_TIMEOUT_MSEC);
	काष्ठा mlx5_fw_reset *fw_reset = dev->priv.fw_reset;
	पूर्णांक err;

	अगर (!रुको_क्रम_completion_समयout(&fw_reset->करोne, समयout)) अणु
		mlx5_core_warn(dev, "FW sync reset timeout after %d seconds\n",
			       MLX5_FW_RESET_TIMEOUT_MSEC / 1000);
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण
	err = fw_reset->ret;
out:
	clear_bit(MLX5_FW_RESET_FLAGS_PENDING_COMP, &fw_reset->reset_flags);
	वापस err;
पूर्ण

व्योम mlx5_fw_reset_events_start(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = dev->priv.fw_reset;

	MLX5_NB_INIT(&fw_reset->nb, fw_reset_event_notअगरier, GENERAL_EVENT);
	mlx5_eq_notअगरier_रेजिस्टर(dev, &fw_reset->nb);
पूर्ण

व्योम mlx5_fw_reset_events_stop(काष्ठा mlx5_core_dev *dev)
अणु
	mlx5_eq_notअगरier_unरेजिस्टर(dev, &dev->priv.fw_reset->nb);
पूर्ण

पूर्णांक mlx5_fw_reset_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = kzalloc(माप(*fw_reset), GFP_KERNEL);

	अगर (!fw_reset)
		वापस -ENOMEM;
	fw_reset->wq = create_singlethपढ़ो_workqueue("mlx5_fw_reset_events");
	अगर (!fw_reset->wq) अणु
		kमुक्त(fw_reset);
		वापस -ENOMEM;
	पूर्ण

	fw_reset->dev = dev;
	dev->priv.fw_reset = fw_reset;

	INIT_WORK(&fw_reset->fw_live_patch_work, mlx5_fw_live_patch_event);
	INIT_WORK(&fw_reset->reset_request_work, mlx5_sync_reset_request_event);
	INIT_WORK(&fw_reset->reset_reload_work, mlx5_sync_reset_reload_work);
	INIT_WORK(&fw_reset->reset_now_work, mlx5_sync_reset_now_event);
	INIT_WORK(&fw_reset->reset_पात_work, mlx5_sync_reset_पात_event);

	init_completion(&fw_reset->करोne);
	वापस 0;
पूर्ण

व्योम mlx5_fw_reset_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fw_reset *fw_reset = dev->priv.fw_reset;

	destroy_workqueue(fw_reset->wq);
	kमुक्त(dev->priv.fw_reset);
पूर्ण
