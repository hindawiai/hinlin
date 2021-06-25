<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_CLP_H
#घोषणा _ASM_S390_CLP_H

/* CLP common request & response block size */
#घोषणा CLP_BLK_SIZE			PAGE_SIZE

/* Call Logical Processor - Command Code */
#घोषणा CLP_SLPC		0x0001

#घोषणा CLP_LPS_BASE	0
#घोषणा CLP_LPS_PCI	2

काष्ठा clp_req_hdr अणु
	u16 len;
	u16 cmd;
	u32 fmt		: 4;
	u32 reserved1	: 28;
	u64 reserved2;
पूर्ण __packed;

काष्ठा clp_rsp_hdr अणु
	u16 len;
	u16 rsp;
	u32 fmt		: 4;
	u32 reserved1	: 28;
	u64 reserved2;
पूर्ण __packed;

/* CLP Response Codes */
#घोषणा CLP_RC_OK			0x0010	/* Command request successfully */
#घोषणा CLP_RC_CMD			0x0020	/* Command code not recognized */
#घोषणा CLP_RC_PERM			0x0030	/* Command not authorized */
#घोषणा CLP_RC_FMT			0x0040	/* Invalid command request क्रमmat */
#घोषणा CLP_RC_LEN			0x0050	/* Invalid command request length */
#घोषणा CLP_RC_8K			0x0060	/* Command requires 8K LPCB */
#घोषणा CLP_RC_RESNOT0			0x0070	/* Reserved field not zero */
#घोषणा CLP_RC_NODATA			0x0080	/* No data available */
#घोषणा CLP_RC_FC_UNKNOWN		0x0100	/* Function code not recognized */

/* Store logical-processor अक्षरacteristics request */
काष्ठा clp_req_slpc अणु
	काष्ठा clp_req_hdr hdr;
पूर्ण __packed;

काष्ठा clp_rsp_slpc अणु
	काष्ठा clp_rsp_hdr hdr;
	u32 reserved2[4];
	u32 lpअगर[8];
	u32 reserved3[8];
	u32 lpic[8];
पूर्ण __packed;

काष्ठा clp_req_rsp_slpc अणु
	काष्ठा clp_req_slpc request;
	काष्ठा clp_rsp_slpc response;
पूर्ण __packed;

#पूर्ण_अगर
