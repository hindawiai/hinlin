<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * BSD LICENSE
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _SCI_SAS_H_
#घोषणा _SCI_SAS_H_

#समावेश <linux/kernel.h>

/*
 * SATA FIS Types These स्थिरants depict the various SATA FIS types devined in
 * the serial ATA specअगरication.
 * XXX: This needs to go पूर्णांकo <scsi/sas.h>
 */
#घोषणा FIS_REGH2D          0x27
#घोषणा FIS_REGD2H          0x34
#घोषणा FIS_SETDEVBITS      0xA1
#घोषणा FIS_DMA_ACTIVATE    0x39
#घोषणा FIS_DMA_SETUP       0x41
#घोषणा FIS_BIST_ACTIVATE   0x58
#घोषणा FIS_PIO_SETUP       0x5F
#घोषणा FIS_DATA            0x46

/**************************************************************************/
#घोषणा SSP_RESP_IU_MAX_SIZE	280

/*
 * contents of the SSP COMMAND INFORMATION UNIT.
 * For specअगरic inक्रमmation on each of these inभागidual fields please
 * reference the SAS specअगरication SSP transport layer section.
 * XXX: This needs to go पूर्णांकo <scsi/sas.h>
 */
काष्ठा ssp_cmd_iu अणु
	u8 LUN[8];
	u8 add_cdb_len:6;
	u8 _r_a:2;
	u8 _r_b;
	u8 en_fburst:1;
	u8 task_prio:4;
	u8 task_attr:3;
	u8 _r_c;

	u8 cdb[16];
पूर्ण  __packed;

/*
 * contents of the SSP TASK INFORMATION UNIT.
 * For specअगरic inक्रमmation on each of these inभागidual fields please
 * reference the SAS specअगरication SSP transport layer section.
 * XXX: This needs to go पूर्णांकo <scsi/sas.h>
 */
काष्ठा ssp_task_iu अणु
	u8 LUN[8];
	u8 _r_a;
	u8 task_func;
	u8 _r_b[4];
	u16 task_tag;
	u8 _r_c[12];
पूर्ण  __packed;


/*
 * काष्ठा smp_req_phy_id - This काष्ठाure defines the contents of
 *    an SMP Request that is comprised of the काष्ठा smp_request_header and a
 *    phy identअगरier.
 *    Examples: SMP_REQUEST_DISCOVER, SMP_REQUEST_REPORT_PHY_SATA.
 *
 * For specअगरic inक्रमmation on each of these inभागidual fields please reference
 * the SAS specअगरication.
 */
काष्ठा smp_req_phy_id अणु
	u8 _r_a[4];		/* bytes 4-7 */

	u8 ign_zone_grp:1;	/* byte 8 */
	u8 _r_b:7;

	u8 phy_id;		/* byte 9 */
	u8 _r_c;		/* byte 10 */
	u8 _r_d;		/* byte 11 */
पूर्ण  __packed;

/*
 * काष्ठा smp_req_config_route_info - This काष्ठाure defines the
 *    contents of an SMP Configure Route Inक्रमmation request.
 *
 * For specअगरic inक्रमmation on each of these inभागidual fields please reference
 * the SAS specअगरication.
 */
काष्ठा smp_req_conf_rtinfo अणु
	u16 exp_change_cnt;		/* bytes 4-5 */
	u8 exp_rt_idx_hi;		/* byte 6 */
	u8 exp_rt_idx;			/* byte 7 */

	u8 _r_a;			/* byte 8 */
	u8 phy_id;			/* byte 9 */
	u16 _r_b;			/* bytes 10-11 */

	u8 _r_c:7;			/* byte 12 */
	u8 dis_rt_entry:1;
	u8 _r_d[3];			/* bytes 13-15 */

	u8 rt_sas_addr[8];		/* bytes 16-23 */
	u8 _r_e[16];			/* bytes 24-39 */
पूर्ण  __packed;

/*
 * काष्ठा smp_req_phycntl - This काष्ठाure defines the contents of an
 *    SMP Phy Controller request.
 *
 * For specअगरic inक्रमmation on each of these inभागidual fields please reference
 * the SAS specअगरication.
 */
काष्ठा smp_req_phycntl अणु
	u16 exp_change_cnt;		/* byte 4-5 */

	u8 _r_a[3];			/* bytes 6-8 */

	u8 phy_id;			/* byte 9 */
	u8 phy_op;			/* byte 10 */

	u8 upd_pathway:1;		/* byte 11 */
	u8 _r_b:7;

	u8 _r_c[12];			/* byte 12-23 */

	u8 att_dev_name[8];             /* byte 24-31 */

	u8 _r_d:4;			/* byte 32 */
	u8 min_linkrate:4;

	u8 _r_e:4;			/* byte 33 */
	u8 max_linkrate:4;

	u8 _r_f[2];			/* byte 34-35 */

	u8 pathway:4;			/* byte 36 */
	u8 _r_g:4;

	u8 _r_h[3];			/* bytes 37-39 */
पूर्ण  __packed;

/*
 * काष्ठा smp_req - This काष्ठाure simply जोड़izes the existing request
 *    काष्ठाures पूर्णांकo a common request type.
 *
 * XXX: This data काष्ठाure may need to go to scsi/sas.h
 */
काष्ठा smp_req अणु
	u8 type;		/* byte 0 */
	u8 func;		/* byte 1 */
	u8 alloc_resp_len;	/* byte 2 */
	u8 req_len;		/* byte 3 */
	u8 req_data[];
पूर्ण  __packed;

/*
 * काष्ठा sci_sas_address - This काष्ठाure depicts how a SAS address is
 *    represented by SCI.
 * XXX convert this to u8 [SAS_ADDR_SIZE] like the rest of libsas
 *
 */
काष्ठा sci_sas_address अणु
	u32 high;
	u32 low;
पूर्ण;
#पूर्ण_अगर
