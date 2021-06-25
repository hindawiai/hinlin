<शैली गुरु>
/*
 * Copyright (c) 2003-2012 Broadcom Corporation
 * All Rights Reserved
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the Broadcom
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY BROADCOM ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BROADCOM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _NLM_FMN_H_
#घोषणा _NLM_FMN_H_

#समावेश <यंत्र/netlogic/mips-extns.h> /* क्रम COP2 access */

/* Station IDs */
#घोषणा FMN_STNID_CPU0			0x00
#घोषणा FMN_STNID_CPU1			0x08
#घोषणा FMN_STNID_CPU2			0x10
#घोषणा FMN_STNID_CPU3			0x18
#घोषणा FMN_STNID_CPU4			0x20
#घोषणा FMN_STNID_CPU5			0x28
#घोषणा FMN_STNID_CPU6			0x30
#घोषणा FMN_STNID_CPU7			0x38

#घोषणा FMN_STNID_XGS0_TX		64
#घोषणा FMN_STNID_XMAC0_00_TX		64
#घोषणा FMN_STNID_XMAC0_01_TX		65
#घोषणा FMN_STNID_XMAC0_02_TX		66
#घोषणा FMN_STNID_XMAC0_03_TX		67
#घोषणा FMN_STNID_XMAC0_04_TX		68
#घोषणा FMN_STNID_XMAC0_05_TX		69
#घोषणा FMN_STNID_XMAC0_06_TX		70
#घोषणा FMN_STNID_XMAC0_07_TX		71
#घोषणा FMN_STNID_XMAC0_08_TX		72
#घोषणा FMN_STNID_XMAC0_09_TX		73
#घोषणा FMN_STNID_XMAC0_10_TX		74
#घोषणा FMN_STNID_XMAC0_11_TX		75
#घोषणा FMN_STNID_XMAC0_12_TX		76
#घोषणा FMN_STNID_XMAC0_13_TX		77
#घोषणा FMN_STNID_XMAC0_14_TX		78
#घोषणा FMN_STNID_XMAC0_15_TX		79

#घोषणा FMN_STNID_XGS1_TX		80
#घोषणा FMN_STNID_XMAC1_00_TX		80
#घोषणा FMN_STNID_XMAC1_01_TX		81
#घोषणा FMN_STNID_XMAC1_02_TX		82
#घोषणा FMN_STNID_XMAC1_03_TX		83
#घोषणा FMN_STNID_XMAC1_04_TX		84
#घोषणा FMN_STNID_XMAC1_05_TX		85
#घोषणा FMN_STNID_XMAC1_06_TX		86
#घोषणा FMN_STNID_XMAC1_07_TX		87
#घोषणा FMN_STNID_XMAC1_08_TX		88
#घोषणा FMN_STNID_XMAC1_09_TX		89
#घोषणा FMN_STNID_XMAC1_10_TX		90
#घोषणा FMN_STNID_XMAC1_11_TX		91
#घोषणा FMN_STNID_XMAC1_12_TX		92
#घोषणा FMN_STNID_XMAC1_13_TX		93
#घोषणा FMN_STNID_XMAC1_14_TX		94
#घोषणा FMN_STNID_XMAC1_15_TX		95

#घोषणा FMN_STNID_GMAC			96
#घोषणा FMN_STNID_GMACJFR_0		96
#घोषणा FMN_STNID_GMACRFR_0		97
#घोषणा FMN_STNID_GMACTX0		98
#घोषणा FMN_STNID_GMACTX1		99
#घोषणा FMN_STNID_GMACTX2		100
#घोषणा FMN_STNID_GMACTX3		101
#घोषणा FMN_STNID_GMACJFR_1		102
#घोषणा FMN_STNID_GMACRFR_1		103

#घोषणा FMN_STNID_DMA			104
#घोषणा FMN_STNID_DMA_0			104
#घोषणा FMN_STNID_DMA_1			105
#घोषणा FMN_STNID_DMA_2			106
#घोषणा FMN_STNID_DMA_3			107

#घोषणा FMN_STNID_XGS0FR		112
#घोषणा FMN_STNID_XMAC0JFR		112
#घोषणा FMN_STNID_XMAC0RFR		113

#घोषणा FMN_STNID_XGS1FR		114
#घोषणा FMN_STNID_XMAC1JFR		114
#घोषणा FMN_STNID_XMAC1RFR		115
#घोषणा FMN_STNID_SEC			120
#घोषणा FMN_STNID_SEC0			120
#घोषणा FMN_STNID_SEC1			121
#घोषणा FMN_STNID_SEC2			122
#घोषणा FMN_STNID_SEC3			123
#घोषणा FMN_STNID_PK0			124
#घोषणा FMN_STNID_SEC_RSA		124
#घोषणा FMN_STNID_SEC_RSVD0		125
#घोषणा FMN_STNID_SEC_RSVD1		126
#घोषणा FMN_STNID_SEC_RSVD2		127

#घोषणा FMN_STNID_GMAC1			80
#घोषणा FMN_STNID_GMAC1_FR_0		81
#घोषणा FMN_STNID_GMAC1_TX0		82
#घोषणा FMN_STNID_GMAC1_TX1		83
#घोषणा FMN_STNID_GMAC1_TX2		84
#घोषणा FMN_STNID_GMAC1_TX3		85
#घोषणा FMN_STNID_GMAC1_FR_1		87
#घोषणा FMN_STNID_GMAC0			96
#घोषणा FMN_STNID_GMAC0_FR_0		97
#घोषणा FMN_STNID_GMAC0_TX0		98
#घोषणा FMN_STNID_GMAC0_TX1		99
#घोषणा FMN_STNID_GMAC0_TX2		100
#घोषणा FMN_STNID_GMAC0_TX3		101
#घोषणा FMN_STNID_GMAC0_FR_1		103
#घोषणा FMN_STNID_CMP_0			108
#घोषणा FMN_STNID_CMP_1			109
#घोषणा FMN_STNID_CMP_2			110
#घोषणा FMN_STNID_CMP_3			111
#घोषणा FMN_STNID_PCIE_0		116
#घोषणा FMN_STNID_PCIE_1		117
#घोषणा FMN_STNID_PCIE_2		118
#घोषणा FMN_STNID_PCIE_3		119
#घोषणा FMN_STNID_XLS_PK0		121

#घोषणा nlm_पढ़ो_c2_cc0(s)		__पढ़ो_32bit_c2_रेजिस्टर($16, s)
#घोषणा nlm_पढ़ो_c2_cc1(s)		__पढ़ो_32bit_c2_रेजिस्टर($17, s)
#घोषणा nlm_पढ़ो_c2_cc2(s)		__पढ़ो_32bit_c2_रेजिस्टर($18, s)
#घोषणा nlm_पढ़ो_c2_cc3(s)		__पढ़ो_32bit_c2_रेजिस्टर($19, s)
#घोषणा nlm_पढ़ो_c2_cc4(s)		__पढ़ो_32bit_c2_रेजिस्टर($20, s)
#घोषणा nlm_पढ़ो_c2_cc5(s)		__पढ़ो_32bit_c2_रेजिस्टर($21, s)
#घोषणा nlm_पढ़ो_c2_cc6(s)		__पढ़ो_32bit_c2_रेजिस्टर($22, s)
#घोषणा nlm_पढ़ो_c2_cc7(s)		__पढ़ो_32bit_c2_रेजिस्टर($23, s)
#घोषणा nlm_पढ़ो_c2_cc8(s)		__पढ़ो_32bit_c2_रेजिस्टर($24, s)
#घोषणा nlm_पढ़ो_c2_cc9(s)		__पढ़ो_32bit_c2_रेजिस्टर($25, s)
#घोषणा nlm_पढ़ो_c2_cc10(s)		__पढ़ो_32bit_c2_रेजिस्टर($26, s)
#घोषणा nlm_पढ़ो_c2_cc11(s)		__पढ़ो_32bit_c2_रेजिस्टर($27, s)
#घोषणा nlm_पढ़ो_c2_cc12(s)		__पढ़ो_32bit_c2_रेजिस्टर($28, s)
#घोषणा nlm_पढ़ो_c2_cc13(s)		__पढ़ो_32bit_c2_रेजिस्टर($29, s)
#घोषणा nlm_पढ़ो_c2_cc14(s)		__पढ़ो_32bit_c2_रेजिस्टर($30, s)
#घोषणा nlm_पढ़ो_c2_cc15(s)		__पढ़ो_32bit_c2_रेजिस्टर($31, s)

#घोषणा nlm_ग_लिखो_c2_cc0(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($16, s, v)
#घोषणा nlm_ग_लिखो_c2_cc1(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($17, s, v)
#घोषणा nlm_ग_लिखो_c2_cc2(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($18, s, v)
#घोषणा nlm_ग_लिखो_c2_cc3(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($19, s, v)
#घोषणा nlm_ग_लिखो_c2_cc4(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($20, s, v)
#घोषणा nlm_ग_लिखो_c2_cc5(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($21, s, v)
#घोषणा nlm_ग_लिखो_c2_cc6(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($22, s, v)
#घोषणा nlm_ग_लिखो_c2_cc7(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($23, s, v)
#घोषणा nlm_ग_लिखो_c2_cc8(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($24, s, v)
#घोषणा nlm_ग_लिखो_c2_cc9(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($25, s, v)
#घोषणा nlm_ग_लिखो_c2_cc10(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($26, s, v)
#घोषणा nlm_ग_लिखो_c2_cc11(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($27, s, v)
#घोषणा nlm_ग_लिखो_c2_cc12(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($28, s, v)
#घोषणा nlm_ग_लिखो_c2_cc13(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($29, s, v)
#घोषणा nlm_ग_लिखो_c2_cc14(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($30, s, v)
#घोषणा nlm_ग_लिखो_c2_cc15(s, v)		__ग_लिखो_32bit_c2_रेजिस्टर($31, s, v)

#घोषणा nlm_पढ़ो_c2_status0()		__पढ़ो_32bit_c2_रेजिस्टर($2, 0)
#घोषणा nlm_ग_लिखो_c2_status0(v)		__ग_लिखो_32bit_c2_रेजिस्टर($2, 0, v)
#घोषणा nlm_पढ़ो_c2_status1()		__पढ़ो_32bit_c2_रेजिस्टर($2, 1)
#घोषणा nlm_ग_लिखो_c2_status1(v)		__ग_लिखो_32bit_c2_रेजिस्टर($2, 1, v)
#घोषणा nlm_पढ़ो_c2_status(sel)		__पढ़ो_32bit_c2_रेजिस्टर($2, 0)
#घोषणा nlm_पढ़ो_c2_config()		__पढ़ो_32bit_c2_रेजिस्टर($3, 0)
#घोषणा nlm_ग_लिखो_c2_config(v)		__ग_लिखो_32bit_c2_रेजिस्टर($3, 0, v)
#घोषणा nlm_पढ़ो_c2_bucksize(b)		__पढ़ो_32bit_c2_रेजिस्टर($4, b)
#घोषणा nlm_ग_लिखो_c2_bucksize(b, v)	__ग_लिखो_32bit_c2_रेजिस्टर($4, b, v)

#घोषणा nlm_पढ़ो_c2_rx_msg0()		__पढ़ो_64bit_c2_रेजिस्टर($1, 0)
#घोषणा nlm_पढ़ो_c2_rx_msg1()		__पढ़ो_64bit_c2_रेजिस्टर($1, 1)
#घोषणा nlm_पढ़ो_c2_rx_msg2()		__पढ़ो_64bit_c2_रेजिस्टर($1, 2)
#घोषणा nlm_पढ़ो_c2_rx_msg3()		__पढ़ो_64bit_c2_रेजिस्टर($1, 3)

#घोषणा nlm_ग_लिखो_c2_tx_msg0(v)		__ग_लिखो_64bit_c2_रेजिस्टर($0, 0, v)
#घोषणा nlm_ग_लिखो_c2_tx_msg1(v)		__ग_लिखो_64bit_c2_रेजिस्टर($0, 1, v)
#घोषणा nlm_ग_लिखो_c2_tx_msg2(v)		__ग_लिखो_64bit_c2_रेजिस्टर($0, 2, v)
#घोषणा nlm_ग_लिखो_c2_tx_msg3(v)		__ग_लिखो_64bit_c2_रेजिस्टर($0, 3, v)

#घोषणा FMN_STN_RX_QSIZE		256
#घोषणा FMN_NSTATIONS			128
#घोषणा FMN_CORE_NBUCKETS		8

अटल अंतरभूत व्योम nlm_msgsnd(अचिन्हित पूर्णांक stid)
अणु
	__यंत्र__ अस्थिर (
	    ".set	push\n"
	    ".set	noreorder\n"
	    ".set	noat\n"
	    "move	$1, %0\n"
	    "c2		0x10001\n"	/* msgsnd $1 */
	    ".set	pop\n"
	    : : "r" (stid) : "$1"
	);
पूर्ण

अटल अंतरभूत व्योम nlm_msgld(अचिन्हित पूर्णांक pri)
अणु
	__यंत्र__ अस्थिर (
	    ".set	push\n"
	    ".set	noreorder\n"
	    ".set	noat\n"
	    "move	$1, %0\n"
	    "c2		0x10002\n"    /* msgld $1 */
	    ".set	pop\n"
	    : : "r" (pri) : "$1"
	);
पूर्ण

अटल अंतरभूत व्योम nlm_msgरुको(अचिन्हित पूर्णांक mask)
अणु
	__यंत्र__ अस्थिर (
	    ".set	push\n"
	    ".set	noreorder\n"
	    ".set	noat\n"
	    "move	$8, %0\n"
	    "c2		0x10003\n"    /* msgरुको $1 */
	    ".set	pop\n"
	    : : "r" (mask) : "$1"
	);
पूर्ण

/*
 * Disable पूर्णांकerrupts and enable COP2 access
 */
अटल अंतरभूत uपूर्णांक32_t nlm_cop2_enable_irqsave(व्योम)
अणु
	uपूर्णांक32_t sr = पढ़ो_c0_status();

	ग_लिखो_c0_status((sr & ~ST0_IE) | ST0_CU2);
	वापस sr;
पूर्ण

अटल अंतरभूत व्योम nlm_cop2_disable_irqrestore(uपूर्णांक32_t sr)
अणु
	ग_लिखो_c0_status(sr);
पूर्ण

अटल अंतरभूत व्योम nlm_fmn_setup_पूर्णांकr(पूर्णांक irq, अचिन्हित पूर्णांक पंचांगask)
अणु
	uपूर्णांक32_t config;

	config = (1 << 24)	/* पूर्णांकerrupt water mark - 1 msg */
		| (irq << 16)	/* irq */
		| (पंचांगask << 8)	/* thपढ़ो mask */
		| 0x2;		/* enable watermark पूर्णांकr, disable empty पूर्णांकr */
	nlm_ग_लिखो_c2_config(config);
पूर्ण

काष्ठा nlm_fmn_msg अणु
	uपूर्णांक64_t msg0;
	uपूर्णांक64_t msg1;
	uपूर्णांक64_t msg2;
	uपूर्णांक64_t msg3;
पूर्ण;

अटल अंतरभूत पूर्णांक nlm_fmn_send(अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक code,
		अचिन्हित पूर्णांक stid, काष्ठा nlm_fmn_msg *msg)
अणु
	अचिन्हित पूर्णांक dest;
	uपूर्णांक32_t status;
	पूर्णांक i;

	/*
	 * Make sure that all the ग_लिखोs pending at the cpu are flushed.
	 * Any ग_लिखोs pending on CPU will not be see by devices. L1/L2
	 * caches are coherent with IO, so no cache flush needed.
	 */
	__यंत्र __अस्थिर("sync");

	/* Load TX message buffers */
	nlm_ग_लिखो_c2_tx_msg0(msg->msg0);
	nlm_ग_लिखो_c2_tx_msg1(msg->msg1);
	nlm_ग_लिखो_c2_tx_msg2(msg->msg2);
	nlm_ग_लिखो_c2_tx_msg3(msg->msg3);
	dest = ((size - 1) << 16) | (code << 8) | stid;

	/*
	 * Retry a few बार on credit fail, this should be a
	 * transient condition, unless there is a configuration
	 * failure, or the receiver is stuck.
	 */
	क्रम (i = 0; i < 8; i++) अणु
		nlm_msgsnd(dest);
		status = nlm_पढ़ो_c2_status0();
		अगर ((status & 0x4) == 0)
			वापस 0;
	पूर्ण

	/* If there is a credit failure, वापस error */
	वापस status & 0x06;
पूर्ण

अटल अंतरभूत पूर्णांक nlm_fmn_receive(पूर्णांक bucket, पूर्णांक *size, पूर्णांक *code, पूर्णांक *stid,
		काष्ठा nlm_fmn_msg *msg)
अणु
	uपूर्णांक32_t status, पंचांगp;

	nlm_msgld(bucket);

	/* रुको क्रम load pending to clear */
	करो अणु
		status = nlm_पढ़ो_c2_status0();
	पूर्ण जबतक ((status & 0x08) != 0);

	/* receive error bits */
	पंचांगp = status & 0x30;
	अगर (पंचांगp != 0)
		वापस पंचांगp;

	*size = ((status & 0xc0) >> 6) + 1;
	*code = (status & 0xff00) >> 8;
	*stid = (status & 0x7f0000) >> 16;
	msg->msg0 = nlm_पढ़ो_c2_rx_msg0();
	msg->msg1 = nlm_पढ़ो_c2_rx_msg1();
	msg->msg2 = nlm_पढ़ो_c2_rx_msg2();
	msg->msg3 = nlm_पढ़ो_c2_rx_msg3();

	वापस 0;
पूर्ण

काष्ठा xlr_fmn_info अणु
	पूर्णांक num_buckets;
	पूर्णांक start_stn_id;
	पूर्णांक end_stn_id;
	पूर्णांक credit_config[128];
पूर्ण;

काष्ठा xlr_board_fmn_config अणु
	पूर्णांक bucket_size[128];		/* size of buckets क्रम all stations */
	काष्ठा xlr_fmn_info cpu[8];
	काष्ठा xlr_fmn_info gmac[2];
	काष्ठा xlr_fmn_info dma;
	काष्ठा xlr_fmn_info cmp;
	काष्ठा xlr_fmn_info sae;
	काष्ठा xlr_fmn_info xgmac[2];
पूर्ण;

बाह्य पूर्णांक nlm_रेजिस्टर_fmn_handler(पूर्णांक start, पूर्णांक end,
	व्योम (*fn)(पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, काष्ठा nlm_fmn_msg *, व्योम *),
	व्योम *arg);
बाह्य व्योम xlr_percpu_fmn_init(व्योम);
बाह्य व्योम nlm_setup_fmn_irq(व्योम);
बाह्य व्योम xlr_board_info_setup(व्योम);

बाह्य काष्ठा xlr_board_fmn_config xlr_board_fmn_config;
#पूर्ण_अगर
