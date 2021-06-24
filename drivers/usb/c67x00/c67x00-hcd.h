<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * c67x00-hcd.h: Cypress C67X00 USB HCD
 *
 * Copyright (C) 2006-2008 Barco N.V.
 *    Derived from the Cypress cy7c67200/300 ezusb linux driver and
 *    based on multiple host controller drivers inside the linux kernel.
 */

#अगर_अघोषित _USB_C67X00_HCD_H
#घोषणा _USB_C67X00_HCD_H

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश "c67x00.h"

/*
 * The following parameters depend on the CPU speed, bus speed, ...
 * These can be tuned क्रम specअगरic use हालs, e.g. अगर isochronous transfers
 * are very important, bandwidth can be sacrअगरiced to guarantee that the
 * 1ms deadline will be met.
 * If bulk transfers are important, the MAX_FRAME_BW can be increased,
 * but some (or many) isochronous deadlines might not be met.
 *
 * The values are specअगरied in bitसमय.
 */

/*
 * The current implementation चयनes between _STD (शेष) and _ISO (when
 * isochronous transfers are scheduled), in order to optimize the throughput
 * in normal circumstances, but also provide good isochronous behaviour.
 *
 * Bandwidth is described in bit समय so with a 12MHz USB घड़ी and 1ms
 * frames; there are 12000 bit बार per frame.
 */

#घोषणा TOTAL_FRAME_BW		12000
#घोषणा DEFAULT_EOT		2250

#घोषणा MAX_FRAME_BW_STD	(TOTAL_FRAME_BW - DEFAULT_EOT)
#घोषणा MAX_FRAME_BW_ISO	2400

/*
 * Periodic transfers may only use 90% of the full frame, but as
 * we currently करोn't even use 90% of the full frame, we may
 * use the full usable समय क्रम periodic transfers.
 */
#घोषणा MAX_PERIODIC_BW(full_bw)	full_bw

/* -------------------------------------------------------------------------- */

काष्ठा c67x00_hcd अणु
	spinlock_t lock;
	काष्ठा c67x00_sie *sie;
	अचिन्हित पूर्णांक low_speed_ports;	/* biपंचांगask of low speed ports */
	अचिन्हित पूर्णांक urb_count;
	अचिन्हित पूर्णांक urb_iso_count;

	काष्ठा list_head list[4];	/* iso, पूर्णांक, ctrl, bulk */
#अगर PIPE_BULK != 3
#त्रुटि "Sanity check failed, this code presumes PIPE_... to range from 0 to 3"
#पूर्ण_अगर

	/* USB bandwidth allocated to td_list */
	पूर्णांक bandwidth_allocated;
	/* USB bandwidth allocated क्रम isoc/पूर्णांक transfer */
	पूर्णांक periodic_bw_allocated;
	काष्ठा list_head td_list;
	पूर्णांक max_frame_bw;

	u16 td_base_addr;
	u16 buf_base_addr;
	u16 next_td_addr;
	u16 next_buf_addr;

	काष्ठा work_काष्ठा work;

	काष्ठा completion endpoपूर्णांक_disable;

	u16 current_frame;
	u16 last_frame;
पूर्ण;

अटल अंतरभूत काष्ठा c67x00_hcd *hcd_to_c67x00_hcd(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा c67x00_hcd *)(hcd->hcd_priv);
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *c67x00_hcd_to_hcd(काष्ठा c67x00_hcd *c67x00)
अणु
	वापस container_of((व्योम *)c67x00, काष्ठा usb_hcd, hcd_priv);
पूर्ण

/* ---------------------------------------------------------------------
 * Functions used by c67x00-drv
 */

पूर्णांक c67x00_hcd_probe(काष्ठा c67x00_sie *sie);
व्योम c67x00_hcd_हटाओ(काष्ठा c67x00_sie *sie);

/* ---------------------------------------------------------------------
 * Transfer Descriptor scheduling functions
 */
पूर्णांक c67x00_urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, gfp_t mem_flags);
पूर्णांक c67x00_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status);
व्योम c67x00_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
			     काष्ठा usb_host_endpoपूर्णांक *ep);

व्योम c67x00_hcd_msg_received(काष्ठा c67x00_sie *sie, u16 msg);
व्योम c67x00_sched_kick(काष्ठा c67x00_hcd *c67x00);
पूर्णांक c67x00_sched_start_scheduler(काष्ठा c67x00_hcd *c67x00);
व्योम c67x00_sched_stop_scheduler(काष्ठा c67x00_hcd *c67x00);

#घोषणा c67x00_hcd_dev(x)	(c67x00_hcd_to_hcd(x)->self.controller)

#पूर्ण_अगर				/* _USB_C67X00_HCD_H */
