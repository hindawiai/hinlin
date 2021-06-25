<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * bdc_dbg.h - header क्रम the BDC debug functions
 *
 * Copyright (C) 2014 Broadcom Corporation
 *
 * Author: Ashwini Pahuja
 */
#अगर_अघोषित __LINUX_BDC_DBG_H__
#घोषणा __LINUX_BDC_DBG_H__

#समावेश "bdc.h"

#अगर_घोषित CONFIG_USB_GADGET_VERBOSE
व्योम bdc_dbg_bd_list(काष्ठा bdc *bdc, काष्ठा bdc_ep *ep);
व्योम bdc_dbg_srr(काष्ठा bdc *bdc, u32 srr_num);
व्योम bdc_dbg_regs(काष्ठा bdc *bdc);
व्योम bdc_dump_epsts(काष्ठा bdc *bdc);
#अन्यथा
अटल अंतरभूत व्योम bdc_dbg_regs(काष्ठा bdc *bdc)
अणु पूर्ण

अटल अंतरभूत व्योम bdc_dbg_srr(काष्ठा bdc *bdc, u32 srr_num)
अणु पूर्ण

अटल अंतरभूत व्योम bdc_dbg_bd_list(काष्ठा bdc *bdc, काष्ठा bdc_ep *ep)
अणु पूर्ण

अटल अंतरभूत व्योम bdc_dump_epsts(काष्ठा bdc *bdc)
अणु पूर्ण
#पूर्ण_अगर /* CONFIG_USB_GADGET_VERBOSE */
#पूर्ण_अगर /* __LINUX_BDC_DBG_H__ */
