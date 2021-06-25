<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * bdc_cmd.h - header क्रम the BDC debug functions
 *
 * Copyright (C) 2014 Broadcom Corporation
 *
 * Author: Ashwini Pahuja
 */
#अगर_अघोषित __LINUX_BDC_CMD_H__
#घोषणा __LINUX_BDC_CMD_H__

/* Command operations */
पूर्णांक bdc_address_device(काष्ठा bdc *bdc, u32 add);
पूर्णांक bdc_config_ep(काष्ठा bdc *bdc, काष्ठा bdc_ep *ep);
पूर्णांक bdc_dconfig_ep(काष्ठा bdc *bdc, काष्ठा bdc_ep *ep);
पूर्णांक bdc_stop_ep(काष्ठा bdc *bdc, पूर्णांक epnum);
पूर्णांक bdc_ep_set_stall(काष्ठा bdc *bdc, पूर्णांक epnum);
पूर्णांक bdc_ep_clear_stall(काष्ठा bdc *bdc, पूर्णांक epnum);
पूर्णांक bdc_ep_bla(काष्ठा bdc *bdc, काष्ठा bdc_ep *ep, dma_addr_t dma_addr);
पूर्णांक bdc_function_wake(काष्ठा bdc *bdc, u8 पूर्णांकf);
पूर्णांक bdc_function_wake_fh(काष्ठा bdc *bdc, u8 पूर्णांकf);

#पूर्ण_अगर /* __LINUX_BDC_CMD_H__ */
