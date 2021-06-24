<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * TI Common Platक्रमm Time Sync
 *
 * Copyright (C) 2012 Riअक्षरd Cochran <riअक्षरdcochran@gmail.com>
 *
 */
#अगर_अघोषित _TI_CPTS_H_
#घोषणा _TI_CPTS_H_

#अगर IS_ENABLED(CONFIG_TI_CPTS)

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/of.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/समयcounter.h>

काष्ठा cpsw_cpts अणु
	u32 idver;                /* Identअगरication and version */
	u32 control;              /* Time sync control */
	u32 rftclk_sel;		  /* Reference Clock Select Register */
	u32 ts_push;              /* Time stamp event push */
	u32 ts_load_val;          /* Time stamp load value */
	u32 ts_load_en;           /* Time stamp load enable */
	u32 res2[2];
	u32 पूर्णांकstat_raw;          /* Time sync पूर्णांकerrupt status raw */
	u32 पूर्णांकstat_masked;       /* Time sync पूर्णांकerrupt status masked */
	u32 पूर्णांक_enable;           /* Time sync पूर्णांकerrupt enable */
	u32 res3;
	u32 event_pop;            /* Event पूर्णांकerrupt pop */
	u32 event_low;            /* 32 Bit Event Time Stamp */
	u32 event_high;           /* Event Type Fields */
पूर्ण;

/* Bit definitions क्रम the IDVER रेजिस्टर */
#घोषणा TX_IDENT_SHIFT       (16)    /* TX Identअगरication Value */
#घोषणा TX_IDENT_MASK        (0xffff)
#घोषणा RTL_VER_SHIFT        (11)    /* RTL Version Value */
#घोषणा RTL_VER_MASK         (0x1f)
#घोषणा MAJOR_VER_SHIFT      (8)     /* Major Version Value */
#घोषणा MAJOR_VER_MASK       (0x7)
#घोषणा MINOR_VER_SHIFT      (0)     /* Minor Version Value */
#घोषणा MINOR_VER_MASK       (0xff)

/* Bit definitions क्रम the CONTROL रेजिस्टर */
#घोषणा HW4_TS_PUSH_EN       (1<<11) /* Hardware push 4 enable */
#घोषणा HW3_TS_PUSH_EN       (1<<10) /* Hardware push 3 enable */
#घोषणा HW2_TS_PUSH_EN       (1<<9)  /* Hardware push 2 enable */
#घोषणा HW1_TS_PUSH_EN       (1<<8)  /* Hardware push 1 enable */
#घोषणा INT_TEST             (1<<1)  /* Interrupt Test */
#घोषणा CPTS_EN              (1<<0)  /* Time Sync Enable */

/*
 * Definitions क्रम the single bit resisters:
 * TS_PUSH TS_LOAD_EN  INTSTAT_RAW INTSTAT_MASKED INT_ENABLE EVENT_POP
 */
#घोषणा TS_PUSH             (1<<0)  /* Time stamp event push */
#घोषणा TS_LOAD_EN          (1<<0)  /* Time Stamp Load */
#घोषणा TS_PEND_RAW         (1<<0)  /* पूर्णांक पढ़ो (beक्रमe enable) */
#घोषणा TS_PEND             (1<<0)  /* masked पूर्णांकerrupt पढ़ो (after enable) */
#घोषणा TS_PEND_EN          (1<<0)  /* masked पूर्णांकerrupt enable */
#घोषणा EVENT_POP           (1<<0)  /* writing discards one event */

/* Bit definitions क्रम the EVENT_HIGH रेजिस्टर */
#घोषणा PORT_NUMBER_SHIFT    (24)    /* Indicates Ethernet port or HW pin */
#घोषणा PORT_NUMBER_MASK     (0x1f)
#घोषणा EVENT_TYPE_SHIFT     (20)    /* Time sync event type */
#घोषणा EVENT_TYPE_MASK      (0xf)
#घोषणा MESSAGE_TYPE_SHIFT   (16)    /* PTP message type */
#घोषणा MESSAGE_TYPE_MASK    (0xf)
#घोषणा SEQUENCE_ID_SHIFT    (0)     /* PTP message sequence ID */
#घोषणा SEQUENCE_ID_MASK     (0xffff)

क्रमागत अणु
	CPTS_EV_PUSH, /* Time Stamp Push Event */
	CPTS_EV_ROLL, /* Time Stamp Rollover Event */
	CPTS_EV_HALF, /* Time Stamp Half Rollover Event */
	CPTS_EV_HW,   /* Hardware Time Stamp Push Event */
	CPTS_EV_RX,   /* Ethernet Receive Event */
	CPTS_EV_TX,   /* Ethernet Transmit Event */
पूर्ण;

#घोषणा CPTS_FIFO_DEPTH 16
#घोषणा CPTS_MAX_EVENTS 32

काष्ठा cpts_event अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ पंचांगo;
	u32 high;
	u32 low;
	u64 बारtamp;
पूर्ण;

काष्ठा cpts अणु
	काष्ठा device *dev;
	काष्ठा cpsw_cpts __iomem *reg;
	पूर्णांक tx_enable;
	पूर्णांक rx_enable;
	काष्ठा ptp_घड़ी_info info;
	काष्ठा ptp_घड़ी *घड़ी;
	spinlock_t lock; /* protects fअगरo/events */
	u32 cc_mult; /* क्रम the nominal frequency */
	काष्ठा cyclecounter cc;
	काष्ठा समयcounter tc;
	पूर्णांक phc_index;
	काष्ठा clk *refclk;
	काष्ठा list_head events;
	काष्ठा list_head pool;
	काष्ठा cpts_event pool_data[CPTS_MAX_EVENTS];
	अचिन्हित दीर्घ ov_check_period;
	काष्ठा sk_buff_head txq;
	u64 cur_बारtamp;
	u32 mult_new;
	काष्ठा mutex ptp_clk_mutex; /* sync PTP पूर्णांकerface and worker */
	bool irq_poll;
	काष्ठा completion	ts_push_complete;
	u32 hw_ts_enable;
पूर्ण;

व्योम cpts_rx_बारtamp(काष्ठा cpts *cpts, काष्ठा sk_buff *skb);
व्योम cpts_tx_बारtamp(काष्ठा cpts *cpts, काष्ठा sk_buff *skb);
पूर्णांक cpts_रेजिस्टर(काष्ठा cpts *cpts);
व्योम cpts_unरेजिस्टर(काष्ठा cpts *cpts);
काष्ठा cpts *cpts_create(काष्ठा device *dev, व्योम __iomem *regs,
			 काष्ठा device_node *node, u32 n_ext_ts);
व्योम cpts_release(काष्ठा cpts *cpts);
व्योम cpts_misc_पूर्णांकerrupt(काष्ठा cpts *cpts);

अटल अंतरभूत bool cpts_can_बारtamp(काष्ठा cpts *cpts, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक class = ptp_classअगरy_raw(skb);

	अगर (class == PTP_CLASS_NONE)
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत व्योम cpts_set_irqpoll(काष्ठा cpts *cpts, bool en)
अणु
	cpts->irq_poll = en;
पूर्ण

#अन्यथा
काष्ठा cpts;

अटल अंतरभूत व्योम cpts_rx_बारtamp(काष्ठा cpts *cpts, काष्ठा sk_buff *skb)
अणु
पूर्ण
अटल अंतरभूत व्योम cpts_tx_बारtamp(काष्ठा cpts *cpts, काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत
काष्ठा cpts *cpts_create(काष्ठा device *dev, व्योम __iomem *regs,
			 काष्ठा device_node *node, u32 n_ext_ts)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम cpts_release(काष्ठा cpts *cpts)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
cpts_रेजिस्टर(काष्ठा cpts *cpts)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cpts_unरेजिस्टर(काष्ठा cpts *cpts)
अणु
पूर्ण

अटल अंतरभूत bool cpts_can_बारtamp(काष्ठा cpts *cpts, काष्ठा sk_buff *skb)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम cpts_misc_पूर्णांकerrupt(काष्ठा cpts *cpts)
अणु
पूर्ण

अटल अंतरभूत व्योम cpts_set_irqpoll(काष्ठा cpts *cpts, bool en)
अणु
पूर्ण
#पूर्ण_अगर


#पूर्ण_अगर
