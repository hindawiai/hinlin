<शैली गुरु>
/* bnx2x_fw_file_hdr.h: FW binary file header काष्ठाure.
 *
 * Copyright (c) 2007-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Vladislav Zolotarov
 * Based on the original idea of John Wright <john.wright@hp.com>.
 */

#अगर_अघोषित BNX2X_INIT_खाता_HDR_H
#घोषणा BNX2X_INIT_खाता_HDR_H

काष्ठा bnx2x_fw_file_section अणु
	__be32 len;
	__be32 offset;
पूर्ण;

काष्ठा bnx2x_fw_file_hdr अणु
	काष्ठा bnx2x_fw_file_section init_ops;
	काष्ठा bnx2x_fw_file_section init_ops_offsets;
	काष्ठा bnx2x_fw_file_section init_data;
	काष्ठा bnx2x_fw_file_section tsem_पूर्णांक_table_data;
	काष्ठा bnx2x_fw_file_section tsem_pram_data;
	काष्ठा bnx2x_fw_file_section usem_पूर्णांक_table_data;
	काष्ठा bnx2x_fw_file_section usem_pram_data;
	काष्ठा bnx2x_fw_file_section csem_पूर्णांक_table_data;
	काष्ठा bnx2x_fw_file_section csem_pram_data;
	काष्ठा bnx2x_fw_file_section xsem_पूर्णांक_table_data;
	काष्ठा bnx2x_fw_file_section xsem_pram_data;
	काष्ठा bnx2x_fw_file_section iro_arr;
	काष्ठा bnx2x_fw_file_section fw_version;
पूर्ण;

#पूर्ण_अगर /* BNX2X_INIT_खाता_HDR_H */
