<शैली गुरु>
/***********************license start************************************
 * Copyright (c) 2003-2017 Cavium, Inc.
 * All rights reserved.
 *
 * License: one of 'Cavium License' or 'GNU General Public License Version 2'
 *
 * This file is provided under the terms of the Cavium License (see below)
 * or under the terms of GNU General Public License, Version 2, as
 * published by the Free Software Foundation. When using or redistributing
 * this file, you may करो so under either license.
 *
 * Cavium License:  Redistribution and use in source and binary क्रमms, with
 * or without modअगरication, are permitted provided that the following
 * conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary क्रमm must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the करोcumentation and/or other materials provided
 *    with the distribution.
 *
 *  * Neither the name of Cavium Inc. nor the names of its contributors may be
 *    used to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * This Software, including technical data, may be subject to U.S. export
 * control laws, including the U.S. Export Administration Act and its
 * associated regulations, and may be subject to export or import
 * regulations in other countries.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
 * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
 * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY)
 * WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A
 * PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
 * ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE
 * ENTIRE  RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES
 * WITH YOU.
 ***********************license end**************************************/

#अगर_अघोषित __ZIP_MAIN_H__
#घोषणा __ZIP_MAIN_H__

#समावेश "zip_device.h"
#समावेश "zip_regs.h"

/* PCI device IDs */
#घोषणा PCI_DEVICE_ID_THUNDERX_ZIP   0xA01A

/* ZIP device BARs */
#घोषणा PCI_CFG_ZIP_PF_BAR0   0  /* Base addr क्रम normal regs */

/* Maximum available zip queues */
#घोषणा ZIP_MAX_NUM_QUEUES    8

#घोषणा ZIP_128B_ALIGN        7

/* Command queue buffer size */
#घोषणा ZIP_CMD_QBUF_SIZE     (8064 + 8)

काष्ठा zip_रेजिस्टरs अणु
	अक्षर  *reg_name;
	u64   reg_offset;
पूर्ण;

/* ZIP Compression - Decompression stats */
काष्ठा zip_stats अणु
	atomic64_t    comp_req_submit;
	atomic64_t    comp_req_complete;
	atomic64_t    decomp_req_submit;
	atomic64_t    decomp_req_complete;
	atomic64_t    comp_in_bytes;
	atomic64_t    comp_out_bytes;
	atomic64_t    decomp_in_bytes;
	atomic64_t    decomp_out_bytes;
	atomic64_t    decomp_bad_reqs;
पूर्ण;

/* ZIP Inकाष्ठाion Queue */
काष्ठा zip_iq अणु
	u64        *sw_head;
	u64        *sw_tail;
	u64        *hw_tail;
	u64        करोne_cnt;
	u64        pend_cnt;
	u64        मुक्त_flag;

	/* ZIP IQ lock */
	spinlock_t  lock;
पूर्ण;

/* ZIP Device */
काष्ठा zip_device अणु
	u32               index;
	व्योम __iomem      *reg_base;
	काष्ठा pci_dev    *pdev;

	/* Dअगरferent ZIP Constants */
	u64               depth;
	u64               onfsize;
	u64               ctxsize;

	काष्ठा zip_iq     iq[ZIP_MAX_NUM_QUEUES];
	काष्ठा zip_stats  stats;
पूर्ण;

/* Prototypes */
काष्ठा zip_device *zip_get_device(पूर्णांक node_id);
पूर्णांक zip_get_node_id(व्योम);
व्योम zip_reg_ग_लिखो(u64 val, u64 __iomem *addr);
u64 zip_reg_पढ़ो(u64 __iomem *addr);
व्योम zip_update_cmd_bufs(काष्ठा zip_device *zip_dev, u32 queue);
u32 zip_load_instr(जोड़ zip_inst_s *instr, काष्ठा zip_device *zip_dev);

#पूर्ण_अगर /* ZIP_MAIN_H */
