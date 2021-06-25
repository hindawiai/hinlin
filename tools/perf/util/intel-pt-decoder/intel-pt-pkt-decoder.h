<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * पूर्णांकel_pt_pkt_decoder.h: Intel Processor Trace support
 * Copyright (c) 2013-2014, Intel Corporation.
 */

#अगर_अघोषित INCLUDE__INTEL_PT_PKT_DECODER_H__
#घोषणा INCLUDE__INTEL_PT_PKT_DECODER_H__

#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>

#घोषणा INTEL_PT_PKT_DESC_MAX	256

#घोषणा INTEL_PT_NEED_MORE_BYTES	-1
#घोषणा INTEL_PT_BAD_PACKET		-2

#घोषणा INTEL_PT_PSB_STR		"\002\202\002\202\002\202\002\202" \
					"\002\202\002\202\002\202\002\202"
#घोषणा INTEL_PT_PSB_LEN		16

#घोषणा INTEL_PT_PKT_MAX_SZ		16

#घोषणा INTEL_PT_VMX_NR_FLAG		1

क्रमागत पूर्णांकel_pt_pkt_type अणु
	INTEL_PT_BAD,
	INTEL_PT_PAD,
	INTEL_PT_TNT,
	INTEL_PT_TIP_PGD,
	INTEL_PT_TIP_PGE,
	INTEL_PT_TSC,
	INTEL_PT_TMA,
	INTEL_PT_MODE_EXEC,
	INTEL_PT_MODE_TSX,
	INTEL_PT_MTC,
	INTEL_PT_TIP,
	INTEL_PT_FUP,
	INTEL_PT_CYC,
	INTEL_PT_VMCS,
	INTEL_PT_PSB,
	INTEL_PT_PSBEND,
	INTEL_PT_CBR,
	INTEL_PT_TRACESTOP,
	INTEL_PT_PIP,
	INTEL_PT_OVF,
	INTEL_PT_MNT,
	INTEL_PT_PTWRITE,
	INTEL_PT_PTWRITE_IP,
	INTEL_PT_EXSTOP,
	INTEL_PT_EXSTOP_IP,
	INTEL_PT_MWAIT,
	INTEL_PT_PWRE,
	INTEL_PT_PWRX,
	INTEL_PT_BBP,
	INTEL_PT_BIP,
	INTEL_PT_BEP,
	INTEL_PT_BEP_IP,
पूर्ण;

काष्ठा पूर्णांकel_pt_pkt अणु
	क्रमागत पूर्णांकel_pt_pkt_type	type;
	पूर्णांक			count;
	uपूर्णांक64_t		payload;
पूर्ण;

/*
 * Decoding of BIP packets conflicts with single-byte TNT packets. Since BIP
 * packets only occur in the context of a block (i.e. between BBP and BEP), that
 * context must be recorded and passed to the packet decoder.
 */
क्रमागत पूर्णांकel_pt_pkt_ctx अणु
	INTEL_PT_NO_CTX,	/* BIP packets are invalid */
	INTEL_PT_BLK_4_CTX,	/* 4-byte BIP packets */
	INTEL_PT_BLK_8_CTX,	/* 8-byte BIP packets */
पूर्ण;

स्थिर अक्षर *पूर्णांकel_pt_pkt_name(क्रमागत पूर्णांकel_pt_pkt_type);

पूर्णांक पूर्णांकel_pt_get_packet(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len,
			काष्ठा पूर्णांकel_pt_pkt *packet,
			क्रमागत पूर्णांकel_pt_pkt_ctx *ctx);

व्योम पूर्णांकel_pt_upd_pkt_ctx(स्थिर काष्ठा पूर्णांकel_pt_pkt *packet,
			  क्रमागत पूर्णांकel_pt_pkt_ctx *ctx);

पूर्णांक पूर्णांकel_pt_pkt_desc(स्थिर काष्ठा पूर्णांकel_pt_pkt *packet, अक्षर *buf, माप_प्रकार len);

#पूर्ण_अगर
