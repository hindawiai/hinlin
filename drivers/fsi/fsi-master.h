<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * FSI master definitions. These comprise the core <--> master पूर्णांकerface,
 * to allow the core to पूर्णांकeract with the (hardware-specअगरic) masters.
 *
 * Copyright (C) IBM Corporation 2016
 */

#अगर_अघोषित DRIVERS_FSI_MASTER_H
#घोषणा DRIVERS_FSI_MASTER_H

#समावेश <linux/device.h>
#समावेश <linux/mutex.h>

/*
 * Master रेजिस्टरs
 *
 * These are used by hardware masters, such as the one in the FSP2, AST2600 and
 * the hub master in POWER processors.
 */

/* Control Registers */
#घोषणा FSI_MMODE		0x0		/* R/W: mode */
#घोषणा FSI_MDLYR		0x4		/* R/W: delay */
#घोषणा FSI_MCRSP		0x8		/* R/W: घड़ी rate */
#घोषणा FSI_MENP0		0x10		/* R/W: enable */
#घोषणा FSI_MLEVP0		0x18		/* R: plug detect */
#घोषणा FSI_MSENP0		0x18		/* S: Set enable */
#घोषणा FSI_MCENP0		0x20		/* C: Clear enable */
#घोषणा FSI_MAEB		0x70		/* R: Error address */
#घोषणा FSI_MVER		0x74		/* R: master version/type */
#घोषणा FSI_MSTAP0		0xd0		/* R: Port status */
#घोषणा FSI_MRESP0		0xd0		/* W: Port reset */
#घोषणा FSI_MESRB0		0x1d0		/* R: Master error status */
#घोषणा FSI_MRESB0		0x1d0		/* W: Reset bridge */
#घोषणा FSI_MSCSB0		0x1d4		/* R: Master sub command stack */
#घोषणा FSI_MATRB0		0x1d8		/* R: Master address trace */
#घोषणा FSI_MDTRB0		0x1dc		/* R: Master data trace */
#घोषणा FSI_MECTRL		0x2e0		/* W: Error control */

/* MMODE: Mode control */
#घोषणा FSI_MMODE_EIP		0x80000000	/* Enable पूर्णांकerrupt polling */
#घोषणा FSI_MMODE_ECRC		0x40000000	/* Enable error recovery */
#घोषणा FSI_MMODE_RELA		0x20000000	/* Enable relative address commands */
#घोषणा FSI_MMODE_EPC		0x10000000	/* Enable parity checking */
#घोषणा FSI_MMODE_P8_TO_LSB	0x00000010	/* Timeout value LSB */
						/*   MSB=1, LSB=0 is 0.8 ms */
						/*   MSB=0, LSB=1 is 0.9 ms */
#घोषणा FSI_MMODE_CRS0SHFT	18		/* Clk rate selection 0 shअगरt */
#घोषणा FSI_MMODE_CRS0MASK	0x3ff		/* Clk rate selection 0 mask */
#घोषणा FSI_MMODE_CRS1SHFT	8		/* Clk rate selection 1 shअगरt */
#घोषणा FSI_MMODE_CRS1MASK	0x3ff		/* Clk rate selection 1 mask */

/* MRESB: Reset brindge */
#घोषणा FSI_MRESB_RST_GEN	0x80000000	/* General reset */
#घोषणा FSI_MRESB_RST_ERR	0x40000000	/* Error Reset */

/* MRESP: Reset port */
#घोषणा FSI_MRESP_RST_ALL_MASTER 0x20000000	/* Reset all FSI masters */
#घोषणा FSI_MRESP_RST_ALL_LINK	0x10000000	/* Reset all FSI port contr. */
#घोषणा FSI_MRESP_RST_MCR	0x08000000	/* Reset FSI master reg. */
#घोषणा FSI_MRESP_RST_PYE	0x04000000	/* Reset FSI parity error */
#घोषणा FSI_MRESP_RST_ALL	0xfc000000	/* Reset any error */

/* MECTRL: Error control */
#घोषणा FSI_MECTRL_EOAE		0x8000		/* Enable machine check when */
						/* master 0 in error */
#घोषणा FSI_MECTRL_P8_AUTO_TERM	0x4000		/* Auto terminate */

#घोषणा FSI_HUB_LINK_OFFSET		0x80000
#घोषणा FSI_HUB_LINK_SIZE		0x80000
#घोषणा FSI_HUB_MASTER_MAX_LINKS	8

/*
 * Protocol definitions
 *
 * These are used by low level masters that bit-bang out the protocol
 */

/* Various protocol delays */
#घोषणा	FSI_ECHO_DELAY_CLOCKS	16	/* Number घड़ीs क्रम echo delay */
#घोषणा	FSI_SEND_DELAY_CLOCKS	16	/* Number घड़ीs क्रम send delay */
#घोषणा	FSI_PRE_BREAK_CLOCKS	50	/* Number घड़ीs to prep क्रम अवरोध */
#घोषणा	FSI_BREAK_CLOCKS	256	/* Number of घड़ीs to issue अवरोध */
#घोषणा	FSI_POST_BREAK_CLOCKS	16000	/* Number घड़ीs to set up cfam */
#घोषणा	FSI_INIT_CLOCKS		5000	/* Clock out any old data */
#घोषणा	FSI_MASTER_DPOLL_CLOCKS	50      /* < 21 will cause slave to hang */
#घोषणा	FSI_MASTER_EPOLL_CLOCKS	50      /* Number of घड़ीs क्रम E_POLL retry */

/* Various retry maximums */
#घोषणा FSI_CRC_ERR_RETRIES	10
#घोषणा	FSI_MASTER_MAX_BUSY	200
#घोषणा	FSI_MASTER_MTOE_COUNT	1000

/* Command encodings */
#घोषणा	FSI_CMD_DPOLL		0x2
#घोषणा	FSI_CMD_EPOLL		0x3
#घोषणा	FSI_CMD_TERM		0x3f
#घोषणा FSI_CMD_ABS_AR		0x4
#घोषणा FSI_CMD_REL_AR		0x5
#घोषणा FSI_CMD_SAME_AR		0x3	/* but only a 2-bit opcode... */

/* Slave responses */
#घोषणा	FSI_RESP_ACK		0	/* Success */
#घोषणा	FSI_RESP_BUSY		1	/* Slave busy */
#घोषणा	FSI_RESP_ERRA		2	/* Any (misc) Error */
#घोषणा	FSI_RESP_ERRC		3	/* Slave reports master CRC error */

/* Misc */
#घोषणा	FSI_CRC_SIZE		4

/* fsi-master definition and flags */
#घोषणा FSI_MASTER_FLAG_SWCLOCK		0x1

/*
 * Structures and function prototypes
 *
 * These are common to all masters
 */

काष्ठा fsi_master अणु
	काष्ठा device	dev;
	पूर्णांक		idx;
	पूर्णांक		n_links;
	पूर्णांक		flags;
	काष्ठा mutex	scan_lock;
	पूर्णांक		(*पढ़ो)(काष्ठा fsi_master *, पूर्णांक link, uपूर्णांक8_t id,
				uपूर्णांक32_t addr, व्योम *val, माप_प्रकार size);
	पूर्णांक		(*ग_लिखो)(काष्ठा fsi_master *, पूर्णांक link, uपूर्णांक8_t id,
				uपूर्णांक32_t addr, स्थिर व्योम *val, माप_प्रकार size);
	पूर्णांक		(*term)(काष्ठा fsi_master *, पूर्णांक link, uपूर्णांक8_t id);
	पूर्णांक		(*send_अवरोध)(काष्ठा fsi_master *, पूर्णांक link);
	पूर्णांक		(*link_enable)(काष्ठा fsi_master *, पूर्णांक link,
				       bool enable);
	पूर्णांक		(*link_config)(काष्ठा fsi_master *, पूर्णांक link,
				       u8 t_send_delay, u8 t_echo_delay);
पूर्ण;

#घोषणा dev_to_fsi_master(d) container_of(d, काष्ठा fsi_master, dev)

/**
 * fsi_master registration & lअगरeसमय: the fsi_master_रेजिस्टर() and
 * fsi_master_unरेजिस्टर() functions will take ownership of the master, and
 * ->dev in particular. The registration path perक्रमms a get_device(), which
 * takes the first reference on the device. Similarly, the unregistration path
 * perक्रमms a put_device(), which may well drop the last reference.
 *
 * This means that master implementations *may* need to hold their own
 * reference (via get_device()) on master->dev. In particular, अगर the device's
 * ->release callback मुक्तs the fsi_master, then fsi_master_unरेजिस्टर will
 * invoke this मुक्त अगर no other reference is held.
 *
 * The same applies क्रम the error path of fsi_master_रेजिस्टर; अगर the call
 * fails, dev->release will have been invoked.
 */
बाह्य पूर्णांक fsi_master_रेजिस्टर(काष्ठा fsi_master *master);
बाह्य व्योम fsi_master_unरेजिस्टर(काष्ठा fsi_master *master);

बाह्य पूर्णांक fsi_master_rescan(काष्ठा fsi_master *master);

#पूर्ण_अगर /* DRIVERS_FSI_MASTER_H */
