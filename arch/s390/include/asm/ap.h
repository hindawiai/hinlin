<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Adjunct processor (AP) पूर्णांकerfaces
 *
 * Copyright IBM Corp. 2017
 *
 * Author(s): Tony Krowiak <akrowia@linux.vnet.ibm.com>
 *	      Martin Schwidefsky <schwidefsky@de.ibm.com>
 *	      Harald Freudenberger <freude@de.ibm.com>
 */

#अगर_अघोषित _ASM_S390_AP_H_
#घोषणा _ASM_S390_AP_H_

/**
 * The ap_qid_t identअगरier of an ap queue.
 * If the AP facilities test (APFT) facility is available,
 * card and queue index are 8 bit values, otherwise
 * card index is 6 bit and queue index a 4 bit value.
 */
प्रकार अचिन्हित पूर्णांक ap_qid_t;

#घोषणा AP_MKQID(_card, _queue) (((_card) & 0xff) << 8 | ((_queue) & 0xff))
#घोषणा AP_QID_CARD(_qid) (((_qid) >> 8) & 0xff)
#घोषणा AP_QID_QUEUE(_qid) ((_qid) & 0xff)

/**
 * काष्ठा ap_queue_status - Holds the AP queue status.
 * @queue_empty: Shows अगर queue is empty
 * @replies_रुकोing: Waiting replies
 * @queue_full: Is 1 अगर the queue is full
 * @irq_enabled: Shows अगर पूर्णांकerrupts are enabled क्रम the AP
 * @response_code: Holds the 8 bit response code
 *
 * The ap queue status word is वापसed by all three AP functions
 * (PQAP, NQAP and DQAP).  There's a set of flags in the first
 * byte, followed by a 1 byte response code.
 */
काष्ठा ap_queue_status अणु
	अचिन्हित पूर्णांक queue_empty	: 1;
	अचिन्हित पूर्णांक replies_रुकोing	: 1;
	अचिन्हित पूर्णांक queue_full		: 1;
	अचिन्हित पूर्णांक _pad1		: 4;
	अचिन्हित पूर्णांक irq_enabled	: 1;
	अचिन्हित पूर्णांक response_code	: 8;
	अचिन्हित पूर्णांक _pad2		: 16;
पूर्ण;

/**
 * ap_पूर्णांकructions_available() - Test अगर AP inकाष्ठाions are available.
 *
 * Returns true अगर the AP inकाष्ठाions are installed, otherwise false.
 */
अटल अंतरभूत bool ap_inकाष्ठाions_available(व्योम)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र ("0") = AP_MKQID(0, 0);
	रेजिस्टर अचिन्हित दीर्घ reg1 यंत्र ("1") = 0;
	रेजिस्टर अचिन्हित दीर्घ reg2 यंत्र ("2") = 0;

	यंत्र अस्थिर(
		"   .long 0xb2af0000\n"		/* PQAP(TAPQ) */
		"0: la    %0,1\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: "+d" (reg1), "+d" (reg2)
		: "d" (reg0)
		: "cc");
	वापस reg1 != 0;
पूर्ण

/**
 * ap_tapq(): Test adjunct processor queue.
 * @qid: The AP queue number
 * @info: Poपूर्णांकer to queue descriptor
 *
 * Returns AP queue status काष्ठाure.
 */
अटल अंतरभूत काष्ठा ap_queue_status ap_tapq(ap_qid_t qid, अचिन्हित दीर्घ *info)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र ("0") = qid;
	रेजिस्टर काष्ठा ap_queue_status reg1 यंत्र ("1");
	रेजिस्टर अचिन्हित दीर्घ reg2 यंत्र ("2");

	यंत्र अस्थिर(".long 0xb2af0000"		/* PQAP(TAPQ) */
		     : "=d" (reg1), "=d" (reg2)
		     : "d" (reg0)
		     : "cc");
	अगर (info)
		*info = reg2;
	वापस reg1;
पूर्ण

/**
 * ap_test_queue(): Test adjunct processor queue.
 * @qid: The AP queue number
 * @tbit: Test facilities bit
 * @info: Poपूर्णांकer to queue descriptor
 *
 * Returns AP queue status काष्ठाure.
 */
अटल अंतरभूत काष्ठा ap_queue_status ap_test_queue(ap_qid_t qid,
						   पूर्णांक tbit,
						   अचिन्हित दीर्घ *info)
अणु
	अगर (tbit)
		qid |= 1UL << 23; /* set T bit*/
	वापस ap_tapq(qid, info);
पूर्ण

/**
 * ap_pqap_rapq(): Reset adjunct processor queue.
 * @qid: The AP queue number
 *
 * Returns AP queue status काष्ठाure.
 */
अटल अंतरभूत काष्ठा ap_queue_status ap_rapq(ap_qid_t qid)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र ("0") = qid | (1UL << 24);
	रेजिस्टर काष्ठा ap_queue_status reg1 यंत्र ("1");

	यंत्र अस्थिर(
		".long 0xb2af0000"		/* PQAP(RAPQ) */
		: "=d" (reg1)
		: "d" (reg0)
		: "cc");
	वापस reg1;
पूर्ण

/**
 * ap_pqap_zapq(): Reset and zeroize adjunct processor queue.
 * @qid: The AP queue number
 *
 * Returns AP queue status काष्ठाure.
 */
अटल अंतरभूत काष्ठा ap_queue_status ap_zapq(ap_qid_t qid)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र ("0") = qid | (2UL << 24);
	रेजिस्टर काष्ठा ap_queue_status reg1 यंत्र ("1");

	यंत्र अस्थिर(
		".long 0xb2af0000"		/* PQAP(ZAPQ) */
		: "=d" (reg1)
		: "d" (reg0)
		: "cc");
	वापस reg1;
पूर्ण

/**
 * काष्ठा ap_config_info - convenience काष्ठा क्रम AP crypto
 * config info as वापसed by the ap_qci() function.
 */
काष्ठा ap_config_info अणु
	अचिन्हित पूर्णांक apsc	 : 1;	/* S bit */
	अचिन्हित पूर्णांक apxa	 : 1;	/* N bit */
	अचिन्हित पूर्णांक qact	 : 1;	/* C bit */
	अचिन्हित पूर्णांक rc8a	 : 1;	/* R bit */
	अचिन्हित अक्षर _reserved1 : 4;
	अचिन्हित अक्षर _reserved2[3];
	अचिन्हित अक्षर Na;		/* max # of APs - 1 */
	अचिन्हित अक्षर Nd;		/* max # of Doमुख्यs - 1 */
	अचिन्हित अक्षर _reserved3[10];
	अचिन्हित पूर्णांक apm[8];		/* AP ID mask */
	अचिन्हित पूर्णांक aqm[8];		/* AP (usage) queue mask */
	अचिन्हित पूर्णांक adm[8];		/* AP (control) करोमुख्य mask */
	अचिन्हित अक्षर _reserved4[16];
पूर्ण __aligned(8);

/**
 * ap_qci(): Get AP configuration data
 *
 * Returns 0 on success, or -EOPNOTSUPP.
 */
अटल अंतरभूत पूर्णांक ap_qci(काष्ठा ap_config_info *config)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र ("0") = 4UL << 24;
	रेजिस्टर अचिन्हित दीर्घ reg1 यंत्र ("1") = -EOPNOTSUPP;
	रेजिस्टर काष्ठा ap_config_info *reg2 यंत्र ("2") = config;

	यंत्र अस्थिर(
		".long 0xb2af0000\n"		/* PQAP(QCI) */
		"0: la    %0,0\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		: "+d" (reg1)
		: "d" (reg0), "d" (reg2)
		: "cc", "memory");

	वापस reg1;
पूर्ण

/*
 * काष्ठा ap_qirq_ctrl - convenient काष्ठा क्रम easy invocation
 * of the ap_aqic() function. This काष्ठा is passed as GR1
 * parameter to the PQAP(AQIC) inकाष्ठाion. For details please
 * see the AR करोcumentation.
 */
काष्ठा ap_qirq_ctrl अणु
	अचिन्हित पूर्णांक _res1 : 8;
	अचिन्हित पूर्णांक zone  : 8;	/* zone info */
	अचिन्हित पूर्णांक ir    : 1;	/* ir flag: enable (1) or disable (0) irq */
	अचिन्हित पूर्णांक _res2 : 4;
	अचिन्हित पूर्णांक gisc  : 3;	/* guest isc field */
	अचिन्हित पूर्णांक _res3 : 6;
	अचिन्हित पूर्णांक gf    : 2;	/* gisa क्रमmat */
	अचिन्हित पूर्णांक _res4 : 1;
	अचिन्हित पूर्णांक gisa  : 27;	/* gisa origin */
	अचिन्हित पूर्णांक _res5 : 1;
	अचिन्हित पूर्णांक isc   : 3;	/* irq sub class */
पूर्ण;

/**
 * ap_aqic(): Control पूर्णांकerruption क्रम a specअगरic AP.
 * @qid: The AP queue number
 * @qirqctrl: काष्ठा ap_qirq_ctrl (64 bit value)
 * @ind: The notअगरication indicator byte
 *
 * Returns AP queue status.
 */
अटल अंतरभूत काष्ठा ap_queue_status ap_aqic(ap_qid_t qid,
					     काष्ठा ap_qirq_ctrl qirqctrl,
					     व्योम *ind)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र ("0") = qid | (3UL << 24);
	रेजिस्टर जोड़ अणु
		अचिन्हित दीर्घ value;
		काष्ठा ap_qirq_ctrl qirqctrl;
		काष्ठा ap_queue_status status;
	पूर्ण reg1 यंत्र ("1");
	रेजिस्टर व्योम *reg2 यंत्र ("2") = ind;

	reg1.qirqctrl = qirqctrl;

	यंत्र अस्थिर(
		".long 0xb2af0000"		/* PQAP(AQIC) */
		: "+d" (reg1)
		: "d" (reg0), "d" (reg2)
		: "cc");

	वापस reg1.status;
पूर्ण

/*
 * जोड़ ap_qact_ap_info - used together with the
 * ap_aqic() function to provide a convenient way
 * to handle the ap info needed by the qact function.
 */
जोड़ ap_qact_ap_info अणु
	अचिन्हित दीर्घ val;
	काष्ठा अणु
		अचिन्हित पूर्णांक	  : 3;
		अचिन्हित पूर्णांक mode : 3;
		अचिन्हित पूर्णांक	  : 26;
		अचिन्हित पूर्णांक cat  : 8;
		अचिन्हित पूर्णांक	  : 8;
		अचिन्हित अक्षर ver[2];
	पूर्ण;
पूर्ण;

/**
 * ap_qact(): Query AP combatibility type.
 * @qid: The AP queue number
 * @apinfo: On input the info about the AP queue. On output the
 *	    alternate AP queue info provided by the qact function
 *	    in GR2 is stored in.
 *
 * Returns AP queue status. Check response_code field क्रम failures.
 */
अटल अंतरभूत काष्ठा ap_queue_status ap_qact(ap_qid_t qid, पूर्णांक अगरbit,
					     जोड़ ap_qact_ap_info *apinfo)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र ("0") = qid | (5UL << 24)
		| ((अगरbit & 0x01) << 22);
	रेजिस्टर जोड़ अणु
		अचिन्हित दीर्घ value;
		काष्ठा ap_queue_status status;
	पूर्ण reg1 यंत्र ("1");
	रेजिस्टर अचिन्हित दीर्घ reg2 यंत्र ("2");

	reg1.value = apinfo->val;

	यंत्र अस्थिर(
		".long 0xb2af0000"		/* PQAP(QACT) */
		: "+d" (reg1), "=d" (reg2)
		: "d" (reg0)
		: "cc");
	apinfo->val = reg2;
	वापस reg1.status;
पूर्ण

/**
 * ap_nqap(): Send message to adjunct processor queue.
 * @qid: The AP queue number
 * @psmid: The program supplied message identअगरier
 * @msg: The message text
 * @length: The message length
 *
 * Returns AP queue status काष्ठाure.
 * Condition code 1 on NQAP can't happen because the L bit is 1.
 * Condition code 2 on NQAP also means the send is incomplete,
 * because a segment boundary was reached. The NQAP is repeated.
 */
अटल अंतरभूत काष्ठा ap_queue_status ap_nqap(ap_qid_t qid,
					     अचिन्हित दीर्घ दीर्घ psmid,
					     व्योम *msg, माप_प्रकार length)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र ("0") = qid | 0x40000000UL;
	रेजिस्टर काष्ठा ap_queue_status reg1 यंत्र ("1");
	रेजिस्टर अचिन्हित दीर्घ reg2 यंत्र ("2") = (अचिन्हित दीर्घ) msg;
	रेजिस्टर अचिन्हित दीर्घ reg3 यंत्र ("3") = (अचिन्हित दीर्घ) length;
	रेजिस्टर अचिन्हित दीर्घ reg4 यंत्र ("4") = (अचिन्हित पूर्णांक) (psmid >> 32);
	रेजिस्टर अचिन्हित दीर्घ reg5 यंत्र ("5") = psmid & 0xffffffff;

	यंत्र अस्थिर (
		"0: .long 0xb2ad0042\n"		/* NQAP */
		"   brc   2,0b"
		: "+d" (reg0), "=d" (reg1), "+d" (reg2), "+d" (reg3)
		: "d" (reg4), "d" (reg5)
		: "cc", "memory");
	वापस reg1;
पूर्ण

/**
 * ap_dqap(): Receive message from adjunct processor queue.
 * @qid: The AP queue number
 * @psmid: Poपूर्णांकer to program supplied message identअगरier
 * @msg: The message text
 * @length: The message length
 *
 * Returns AP queue status काष्ठाure.
 * Condition code 1 on DQAP means the receive has taken place
 * but only partially.	The response is incomplete, hence the
 * DQAP is repeated.
 * Condition code 2 on DQAP also means the receive is incomplete,
 * this समय because a segment boundary was reached. Again, the
 * DQAP is repeated.
 * Note that gpr2 is used by the DQAP inकाष्ठाion to keep track of
 * any 'residual' length, in हाल the inकाष्ठाion माला_लो पूर्णांकerrupted.
 * Hence it माला_लो zeroed beक्रमe the inकाष्ठाion.
 */
अटल अंतरभूत काष्ठा ap_queue_status ap_dqap(ap_qid_t qid,
					     अचिन्हित दीर्घ दीर्घ *psmid,
					     व्योम *msg, माप_प्रकार length)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र("0") = qid | 0x80000000UL;
	रेजिस्टर काष्ठा ap_queue_status reg1 यंत्र ("1");
	रेजिस्टर अचिन्हित दीर्घ reg2 यंत्र("2") = 0UL;
	रेजिस्टर अचिन्हित दीर्घ reg4 यंत्र("4") = (अचिन्हित दीर्घ) msg;
	रेजिस्टर अचिन्हित दीर्घ reg5 यंत्र("5") = (अचिन्हित दीर्घ) length;
	रेजिस्टर अचिन्हित दीर्घ reg6 यंत्र("6") = 0UL;
	रेजिस्टर अचिन्हित दीर्घ reg7 यंत्र("7") = 0UL;


	यंत्र अस्थिर(
		"0: .long 0xb2ae0064\n"		/* DQAP */
		"   brc   6,0b\n"
		: "+d" (reg0), "=d" (reg1), "+d" (reg2),
		  "+d" (reg4), "+d" (reg5), "+d" (reg6), "+d" (reg7)
		: : "cc", "memory");
	*psmid = (((अचिन्हित दीर्घ दीर्घ) reg6) << 32) + reg7;
	वापस reg1;
पूर्ण

/*
 * Interface to tell the AP bus code that a configuration
 * change has happened. The bus code should at least करो
 * an ap bus resource rescan.
 */
#अगर IS_ENABLED(CONFIG_ZCRYPT)
व्योम ap_bus_cfg_chg(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ap_bus_cfg_chg(व्योम)अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_S390_AP_H_ */
