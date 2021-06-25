<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांग_idt77105.h - Driver-specअगरic declarations of the IDT77105 driver (क्रम
 * use by driver-specअगरic utilities) */

/* Written 1999 by Greg Banks <gnb@linuxfan.com>. Copied from aपंचांग_suni.h. */


#अगर_अघोषित LINUX_ATM_IDT77105_H
#घोषणा LINUX_ATM_IDT77105_H

#समावेश <linux/types.h>
#समावेश <linux/aपंचांगioc.h>
#समावेश <linux/aपंचांगdev.h>

/*
 * Structure क्रम IDT77105_GETSTAT and IDT77105_GETSTATZ ioctls.
 * Poपूर्णांकed to by `arg' in aपंचांगअगर_sioc.
 */
काष्ठा idt77105_stats अणु
        __u32 symbol_errors;  /* wire symbol errors */
        __u32 tx_cells;       /* cells transmitted */
        __u32 rx_cells;       /* cells received */
        __u32 rx_hec_errors;  /* Header Error Check errors on receive */
पूर्ण;

#घोषणा IDT77105_GETSTAT	_IOW('a',ATMIOC_PHYPRV+2,काष्ठा aपंचांगअगर_sioc)	/* get stats */
#घोषणा IDT77105_GETSTATZ	_IOW('a',ATMIOC_PHYPRV+3,काष्ठा aपंचांगअगर_sioc)	/* get stats and zero */

#पूर्ण_अगर
