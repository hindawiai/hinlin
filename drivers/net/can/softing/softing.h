<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * softing common पूर्णांकerfaces
 *
 * by Kurt Van Dijck, 2008-2010
 */

#समावेश <linux/atomic.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>

#समावेश "softing_platform.h"

काष्ठा softing;

काष्ठा softing_priv अणु
	काष्ठा can_priv can; /* must be the first member! */
	काष्ठा net_device *netdev;
	काष्ठा softing *card;
	काष्ठा अणु
		पूर्णांक pending;
		/* variables which hold the circular buffer */
		पूर्णांक echo_put;
		पूर्णांक echo_get;
	पूर्ण tx;
	काष्ठा can_bittiming_स्थिर btr_स्थिर;
	पूर्णांक index;
	uपूर्णांक8_t output;
	uपूर्णांक16_t chip;
पूर्ण;
#घोषणा netdev2softing(netdev)	((काष्ठा softing_priv *)netdev_priv(netdev))

काष्ठा softing अणु
	स्थिर काष्ठा softing_platक्रमm_data *pdat;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा net_device *net[2];
	spinlock_t spin; /* protect this काष्ठाure & DPRAM access */
	kसमय_प्रकार ts_ref;
	kसमय_प्रकार ts_overflow; /* बारtamp overflow value, in kसमय */

	काष्ठा अणु
		/* indication of firmware status */
		पूर्णांक up;
		/* protection of the 'up' variable */
		काष्ठा mutex lock;
	पूर्ण fw;
	काष्ठा अणु
		पूर्णांक nr;
		पूर्णांक requested;
		पूर्णांक svc_count;
		अचिन्हित पूर्णांक dpram_position;
	पूर्ण irq;
	काष्ठा अणु
		पूर्णांक pending;
		पूर्णांक last_bus;
		/*
		 * keep the bus that last tx'd a message,
		 * in order to let every netdev queue resume
		 */
	पूर्ण tx;
	__iomem uपूर्णांक8_t *dpram;
	अचिन्हित दीर्घ dpram_phys;
	अचिन्हित दीर्घ dpram_size;
	काष्ठा अणु
		uपूर्णांक16_t fw_version, hw_version, license, serial;
		uपूर्णांक16_t chip[2];
		अचिन्हित पूर्णांक freq; /* remote cpu's operating frequency */
	पूर्ण id;
पूर्ण;

पूर्णांक softing_शेष_output(काष्ठा net_device *netdev);

kसमय_प्रकार softing_raw2kसमय(काष्ठा softing *card, u32 raw);

पूर्णांक softing_chip_घातeron(काष्ठा softing *card);

पूर्णांक softing_bootloader_command(काष्ठा softing *card, पूर्णांक16_t cmd,
			       स्थिर अक्षर *msg);

/* Load firmware after reset */
पूर्णांक softing_load_fw(स्थिर अक्षर *file, काष्ठा softing *card,
		    __iomem uपूर्णांक8_t *virt, अचिन्हित पूर्णांक size, पूर्णांक offset);

/* Load final application firmware after bootloader */
पूर्णांक softing_load_app_fw(स्थिर अक्षर *file, काष्ठा softing *card);

/*
 * enable or disable irq
 * only called with fw.lock locked
 */
पूर्णांक softing_enable_irq(काष्ठा softing *card, पूर्णांक enable);

/* start/stop 1 bus on card */
पूर्णांक softing_startstop(काष्ठा net_device *netdev, पूर्णांक up);

/* netअगर_rx() */
पूर्णांक softing_netdev_rx(काष्ठा net_device *netdev, स्थिर काष्ठा can_frame *msg,
		      kसमय_प्रकार kसमय);

/* SOFTING DPRAM mappings */
#घोषणा DPRAM_RX		0x0000
	#घोषणा DPRAM_RX_SIZE	32
	#घोषणा DPRAM_RX_CNT	16
#घोषणा DPRAM_RX_RD		0x0201	/* uपूर्णांक8_t */
#घोषणा DPRAM_RX_WR		0x0205	/* uपूर्णांक8_t */
#घोषणा DPRAM_RX_LOST		0x0207	/* uपूर्णांक8_t */

#घोषणा DPRAM_FCT_PARAM		0x0300	/* पूर्णांक16_t [20] */
#घोषणा DPRAM_FCT_RESULT	0x0328	/* पूर्णांक16_t */
#घोषणा DPRAM_FCT_HOST		0x032b	/* uपूर्णांक16_t */

#घोषणा DPRAM_INFO_BUSSTATE	0x0331	/* uपूर्णांक16_t */
#घोषणा DPRAM_INFO_BUSSTATE2	0x0335	/* uपूर्णांक16_t */
#घोषणा DPRAM_INFO_ERRSTATE	0x0339	/* uपूर्णांक16_t */
#घोषणा DPRAM_INFO_ERRSTATE2	0x033d	/* uपूर्णांक16_t */
#घोषणा DPRAM_RESET		0x0341	/* uपूर्णांक16_t */
#घोषणा DPRAM_CLR_RECV_FIFO	0x0345	/* uपूर्णांक16_t */
#घोषणा DPRAM_RESET_TIME	0x034d	/* uपूर्णांक16_t */
#घोषणा DPRAM_TIME		0x0350	/* uपूर्णांक64_t */
#घोषणा DPRAM_WR_START		0x0358	/* uपूर्णांक8_t */
#घोषणा DPRAM_WR_END		0x0359	/* uपूर्णांक8_t */
#घोषणा DPRAM_RESET_RX_FIFO	0x0361	/* uपूर्णांक16_t */
#घोषणा DPRAM_RESET_TX_FIFO	0x0364	/* uपूर्णांक8_t */
#घोषणा DPRAM_READ_FIFO_LEVEL	0x0365	/* uपूर्णांक8_t */
#घोषणा DPRAM_RX_FIFO_LEVEL	0x0366	/* uपूर्णांक16_t */
#घोषणा DPRAM_TX_FIFO_LEVEL	0x0366	/* uपूर्णांक16_t */

#घोषणा DPRAM_TX		0x0400	/* uपूर्णांक16_t */
	#घोषणा DPRAM_TX_SIZE	16
	#घोषणा DPRAM_TX_CNT	32
#घोषणा DPRAM_TX_RD		0x0601	/* uपूर्णांक8_t */
#घोषणा DPRAM_TX_WR		0x0605	/* uपूर्णांक8_t */

#घोषणा DPRAM_COMMAND		0x07e0	/* uपूर्णांक16_t */
#घोषणा DPRAM_RECEIPT		0x07f0	/* uपूर्णांक16_t */
#घोषणा DPRAM_IRQ_TOHOST	0x07fe	/* uपूर्णांक8_t */
#घोषणा DPRAM_IRQ_TOCARD	0x07ff	/* uपूर्णांक8_t */

#घोषणा DPRAM_V2_RESET		0x0e00	/* uपूर्णांक8_t */
#घोषणा DPRAM_V2_IRQ_TOHOST	0x0e02	/* uपूर्णांक8_t */

#घोषणा TXMAX	(DPRAM_TX_CNT - 1)

/* DPRAM वापस codes */
#घोषणा RES_NONE	0
#घोषणा RES_OK		1
#घोषणा RES_NOK		2
#घोषणा RES_UNKNOWN	3
/* DPRAM flags */
#घोषणा CMD_TX		0x01
#घोषणा CMD_ACK		0x02
#घोषणा CMD_XTD		0x04
#घोषणा CMD_RTR		0x08
#घोषणा CMD_ERR		0x10
#घोषणा CMD_BUS2	0x80

/* वापसed fअगरo entry bus state masks */
#घोषणा SF_MASK_BUSOFF		0x80
#घोषणा SF_MASK_EPASSIVE	0x60

/* bus states */
#घोषणा STATE_BUSOFF	2
#घोषणा STATE_EPASSIVE	1
#घोषणा STATE_EACTIVE	0
