<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2018 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#अगर_अघोषित EFX_COMMON_H
#घोषणा EFX_COMMON_H

पूर्णांक efx_init_io(काष्ठा efx_nic *efx, पूर्णांक bar, dma_addr_t dma_mask,
		अचिन्हित पूर्णांक mem_map_size);
व्योम efx_fini_io(काष्ठा efx_nic *efx);
पूर्णांक efx_init_काष्ठा(काष्ठा efx_nic *efx, काष्ठा pci_dev *pci_dev,
		    काष्ठा net_device *net_dev);
व्योम efx_fini_काष्ठा(काष्ठा efx_nic *efx);

#घोषणा EFX_MAX_DMAQ_SIZE 4096UL
#घोषणा EFX_DEFAULT_DMAQ_SIZE 1024UL
#घोषणा EFX_MIN_DMAQ_SIZE 512UL

#घोषणा EFX_MAX_EVQ_SIZE 16384UL
#घोषणा EFX_MIN_EVQ_SIZE 512UL

व्योम efx_link_clear_advertising(काष्ठा efx_nic *efx);
व्योम efx_link_set_wanted_fc(काष्ठा efx_nic *efx, u8);

व्योम efx_start_all(काष्ठा efx_nic *efx);
व्योम efx_stop_all(काष्ठा efx_nic *efx);

व्योम efx_net_stats(काष्ठा net_device *net_dev, काष्ठा rtnl_link_stats64 *stats);

पूर्णांक efx_create_reset_workqueue(व्योम);
व्योम efx_queue_reset_work(काष्ठा efx_nic *efx);
व्योम efx_flush_reset_workqueue(काष्ठा efx_nic *efx);
व्योम efx_destroy_reset_workqueue(व्योम);

व्योम efx_start_monitor(काष्ठा efx_nic *efx);

पूर्णांक __efx_reconfigure_port(काष्ठा efx_nic *efx);
पूर्णांक efx_reconfigure_port(काष्ठा efx_nic *efx);

#घोषणा EFX_ASSERT_RESET_SERIALISED(efx)		\
	करो अणु						\
		अगर ((efx->state == STATE_READY) ||	\
		    (efx->state == STATE_RECOVERY) ||	\
		    (efx->state == STATE_DISABLED))	\
			ASSERT_RTNL();			\
	पूर्ण जबतक (0)

पूर्णांक efx_try_recovery(काष्ठा efx_nic *efx);
व्योम efx_reset_करोwn(काष्ठा efx_nic *efx, क्रमागत reset_type method);
व्योम efx_watchकरोg(काष्ठा net_device *net_dev, अचिन्हित पूर्णांक txqueue);
पूर्णांक efx_reset_up(काष्ठा efx_nic *efx, क्रमागत reset_type method, bool ok);
पूर्णांक efx_reset(काष्ठा efx_nic *efx, क्रमागत reset_type method);
व्योम efx_schedule_reset(काष्ठा efx_nic *efx, क्रमागत reset_type type);

/* Dummy PHY ops क्रम PHY drivers */
पूर्णांक efx_port_dummy_op_पूर्णांक(काष्ठा efx_nic *efx);
व्योम efx_port_dummy_op_व्योम(काष्ठा efx_nic *efx);

अटल अंतरभूत पूर्णांक efx_check_disabled(काष्ठा efx_nic *efx)
अणु
	अगर (efx->state == STATE_DISABLED || efx->state == STATE_RECOVERY) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "device is disabled due to earlier errors\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम efx_schedule_channel(काष्ठा efx_channel *channel)
अणु
	netअगर_vdbg(channel->efx, पूर्णांकr, channel->efx->net_dev,
		   "channel %d scheduling NAPI poll on CPU%d\n",
		   channel->channel, raw_smp_processor_id());

	napi_schedule(&channel->napi_str);
पूर्ण

अटल अंतरभूत व्योम efx_schedule_channel_irq(काष्ठा efx_channel *channel)
अणु
	channel->event_test_cpu = raw_smp_processor_id();
	efx_schedule_channel(channel);
पूर्ण

#अगर_घोषित CONFIG_SFC_MCDI_LOGGING
व्योम efx_init_mcdi_logging(काष्ठा efx_nic *efx);
व्योम efx_fini_mcdi_logging(काष्ठा efx_nic *efx);
#अन्यथा
अटल अंतरभूत व्योम efx_init_mcdi_logging(काष्ठा efx_nic *efx) अणुपूर्ण
अटल अंतरभूत व्योम efx_fini_mcdi_logging(काष्ठा efx_nic *efx) अणुपूर्ण
#पूर्ण_अगर

व्योम efx_mac_reconfigure(काष्ठा efx_nic *efx, bool mtu_only);
पूर्णांक efx_set_mac_address(काष्ठा net_device *net_dev, व्योम *data);
व्योम efx_set_rx_mode(काष्ठा net_device *net_dev);
पूर्णांक efx_set_features(काष्ठा net_device *net_dev, netdev_features_t data);
व्योम efx_link_status_changed(काष्ठा efx_nic *efx);
अचिन्हित पूर्णांक efx_xdp_max_mtu(काष्ठा efx_nic *efx);
पूर्णांक efx_change_mtu(काष्ठा net_device *net_dev, पूर्णांक new_mtu);

बाह्य स्थिर काष्ठा pci_error_handlers efx_err_handlers;

netdev_features_t efx_features_check(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				     netdev_features_t features);

पूर्णांक efx_get_phys_port_id(काष्ठा net_device *net_dev,
			 काष्ठा netdev_phys_item_id *ppid);

पूर्णांक efx_get_phys_port_name(काष्ठा net_device *net_dev,
			   अक्षर *name, माप_प्रकार len);
#पूर्ण_अगर
