<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2012 Chelsio Communications, Inc. All rights reserved.
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

#अगर_अघोषित __CSIO_INIT_H__
#घोषणा __CSIO_INIT_H__

#समावेश <linux/pci.h>
#समावेश <linux/अगर_ether.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport_fc.h>

#समावेश "csio_scsi.h"
#समावेश "csio_lnode.h"
#समावेश "csio_rnode.h"
#समावेश "csio_hw.h"

#घोषणा CSIO_DRV_AUTHOR			"Chelsio Communications"
#घोषणा CSIO_DRV_DESC			"Chelsio FCoE driver"
#घोषणा CSIO_DRV_VERSION		"1.0.0-ko"

बाह्य काष्ठा fc_function_ढाँचा csio_fc_transport_funcs;
बाह्य काष्ठा fc_function_ढाँचा csio_fc_transport_vport_funcs;

व्योम csio_fchost_attr_init(काष्ठा csio_lnode *);

/* INTx handlers */
व्योम csio_scsi_पूर्णांकx_handler(काष्ठा csio_hw *, व्योम *, uपूर्णांक32_t,
			       काष्ठा csio_fl_dma_buf *, व्योम *);

व्योम csio_fwevt_पूर्णांकx_handler(काष्ठा csio_hw *, व्योम *, uपूर्णांक32_t,
				काष्ठा csio_fl_dma_buf *, व्योम *);

/* Common os lnode APIs */
व्योम csio_lnodes_block_request(काष्ठा csio_hw *);
व्योम csio_lnodes_unblock_request(काष्ठा csio_hw *);
व्योम csio_lnodes_block_by_port(काष्ठा csio_hw *, uपूर्णांक8_t);
व्योम csio_lnodes_unblock_by_port(काष्ठा csio_hw *, uपूर्णांक8_t);

काष्ठा csio_lnode *csio_shost_init(काष्ठा csio_hw *, काष्ठा device *, bool,
					काष्ठा csio_lnode *);
व्योम csio_shost_निकास(काष्ठा csio_lnode *);
व्योम csio_lnodes_निकास(काष्ठा csio_hw *, bool);

/* DebugFS helper routines */
व्योम csio_add_debugfs_mem(काष्ठा csio_hw *, स्थिर अक्षर *,
		अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);

अटल अंतरभूत काष्ठा Scsi_Host *
csio_ln_to_shost(काष्ठा csio_lnode *ln)
अणु
	वापस container_of((व्योम *)ln, काष्ठा Scsi_Host, hostdata[0]);
पूर्ण

/* SCSI -- locking version of get/put ioreqs  */
अटल अंतरभूत काष्ठा csio_ioreq *
csio_get_scsi_ioreq_lock(काष्ठा csio_hw *hw, काष्ठा csio_scsim *scsim)
अणु
	काष्ठा csio_ioreq *ioreq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&scsim->मुक्तlist_lock, flags);
	ioreq = csio_get_scsi_ioreq(scsim);
	spin_unlock_irqrestore(&scsim->मुक्तlist_lock, flags);

	वापस ioreq;
पूर्ण

अटल अंतरभूत व्योम
csio_put_scsi_ioreq_lock(काष्ठा csio_hw *hw, काष्ठा csio_scsim *scsim,
			 काष्ठा csio_ioreq *ioreq)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&scsim->मुक्तlist_lock, flags);
	csio_put_scsi_ioreq(scsim, ioreq);
	spin_unlock_irqrestore(&scsim->मुक्तlist_lock, flags);
पूर्ण

/* Called in पूर्णांकerrupt context */
अटल अंतरभूत व्योम
csio_put_scsi_ioreq_list_lock(काष्ठा csio_hw *hw, काष्ठा csio_scsim *scsim,
			      काष्ठा list_head *reqlist, पूर्णांक n)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&scsim->मुक्तlist_lock, flags);
	csio_put_scsi_ioreq_list(scsim, reqlist, n);
	spin_unlock_irqrestore(&scsim->मुक्तlist_lock, flags);
पूर्ण

/* Called in पूर्णांकerrupt context */
अटल अंतरभूत व्योम
csio_put_scsi_ddp_list_lock(काष्ठा csio_hw *hw, काष्ठा csio_scsim *scsim,
			      काष्ठा list_head *reqlist, पूर्णांक n)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->lock, flags);
	csio_put_scsi_ddp_list(scsim, reqlist, n);
	spin_unlock_irqrestore(&hw->lock, flags);
पूर्ण

#पूर्ण_अगर /* अगरndef __CSIO_INIT_H__ */
