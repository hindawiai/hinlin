<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2002 Intersil Americas Inc.
 *  Copyright (C) 2003-2004 Luis R. Rodriguez <mcgrof@ruslug.rutgers.edu>_
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/kसमय.स>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

#समावेश "prismcompat.h"
#समावेश "isl_38xx.h"
#समावेश "islpci_dev.h"
#समावेश "islpci_mgt.h"

/******************************************************************************
    Device Interface & Control functions
******************************************************************************/

/**
 * isl38xx_disable_पूर्णांकerrupts - disable all पूर्णांकerrupts
 * @device: pci memory base address
 *
 *  Inकाष्ठाs the device to disable all पूर्णांकerrupt reporting by निश्चितing
 *  the IRQ line. New events may still show up in the पूर्णांकerrupt identअगरication
 *  रेजिस्टर located at offset %ISL38XX_INT_IDENT_REG.
 */
व्योम
isl38xx_disable_पूर्णांकerrupts(व्योम __iomem *device)
अणु
	isl38xx_w32_flush(device, 0x00000000, ISL38XX_INT_EN_REG);
	udelay(ISL38XX_WRITEIO_DELAY);
पूर्ण

व्योम
isl38xx_handle_sleep_request(isl38xx_control_block *control_block,
			     पूर्णांक *घातerstate, व्योम __iomem *device_base)
अणु
	/* device requests to go पूर्णांकo sleep mode
	 * check whether the transmit queues क्रम data and management are empty */
	अगर (isl38xx_in_queue(control_block, ISL38XX_CB_TX_DATA_LQ))
		/* data tx queue not empty */
		वापस;

	अगर (isl38xx_in_queue(control_block, ISL38XX_CB_TX_MGMTQ))
		/* management tx queue not empty */
		वापस;

	/* check also whether received frames are pending */
	अगर (isl38xx_in_queue(control_block, ISL38XX_CB_RX_DATA_LQ))
		/* data rx queue not empty */
		वापस;

	अगर (isl38xx_in_queue(control_block, ISL38XX_CB_RX_MGMTQ))
		/* management rx queue not empty */
		वापस;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_TRACING, "Device going to sleep mode\n");
#पूर्ण_अगर

	/* all queues are empty, allow the device to go पूर्णांकo sleep mode */
	*घातerstate = ISL38XX_PSM_POWERSAVE_STATE;

	/* निश्चित the Sleep पूर्णांकerrupt in the Device Interrupt Register */
	isl38xx_w32_flush(device_base, ISL38XX_DEV_INT_SLEEP,
			  ISL38XX_DEV_INT_REG);
	udelay(ISL38XX_WRITEIO_DELAY);
पूर्ण

व्योम
isl38xx_handle_wakeup(isl38xx_control_block *control_block,
		      पूर्णांक *घातerstate, व्योम __iomem *device_base)
अणु
	/* device is in active state, update the घातerstate flag */
	*घातerstate = ISL38XX_PSM_ACTIVE_STATE;

	/* now check whether there are frames pending क्रम the card */
	अगर (!isl38xx_in_queue(control_block, ISL38XX_CB_TX_DATA_LQ)
	    && !isl38xx_in_queue(control_block, ISL38XX_CB_TX_MGMTQ))
		वापस;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_ANYTHING, "Wake up handler trigger the device\n");
#पूर्ण_अगर

	/* either data or management transmit queue has a frame pending
	 * trigger the device by setting the Update bit in the Device Int reg */
	isl38xx_w32_flush(device_base, ISL38XX_DEV_INT_UPDATE,
			  ISL38XX_DEV_INT_REG);
	udelay(ISL38XX_WRITEIO_DELAY);
पूर्ण

व्योम
isl38xx_trigger_device(पूर्णांक asleep, व्योम __iomem *device_base)
अणु
	u32 reg;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	u32 counter = 0;
	काष्ठा बारpec64 current_ts64;
	DEBUG(SHOW_FUNCTION_CALLS, "isl38xx trigger device\n");
#पूर्ण_अगर

	/* check whether the device is in घातer save mode */
	अगर (asleep) अणु
		/* device is in घातersave, trigger the device क्रम wakeup */
#अगर VERBOSE > SHOW_ERROR_MESSAGES
		kसमय_get_real_ts64(&current_ts64);
		DEBUG(SHOW_TRACING, "%lld.%09ld Device wakeup triggered\n",
		      (s64)current_ts64.tv_sec, current_ts64.tv_nsec);

		DEBUG(SHOW_TRACING, "%lld.%09ld Device register read %08x\n",
		      (s64)current_ts64.tv_sec, current_ts64.tv_nsec,
		      पढ़ोl(device_base + ISL38XX_CTRL_STAT_REG));
#पूर्ण_अगर

		reg = पढ़ोl(device_base + ISL38XX_INT_IDENT_REG);
		अगर (reg == 0xabadface) अणु
#अगर VERBOSE > SHOW_ERROR_MESSAGES
			kसमय_get_real_ts64(&current_ts64);
			DEBUG(SHOW_TRACING,
			      "%lld.%09ld Device register abadface\n",
			      (s64)current_ts64.tv_sec, current_ts64.tv_nsec);
#पूर्ण_अगर
			/* पढ़ो the Device Status Register until Sleepmode bit is set */
			जबतक (reg = पढ़ोl(device_base + ISL38XX_CTRL_STAT_REG),
			       (reg & ISL38XX_CTRL_STAT_SLEEPMODE) == 0) अणु
				udelay(ISL38XX_WRITEIO_DELAY);
#अगर VERBOSE > SHOW_ERROR_MESSAGES
				counter++;
#पूर्ण_अगर
			पूर्ण

#अगर VERBOSE > SHOW_ERROR_MESSAGES
			DEBUG(SHOW_TRACING,
			      "%lld.%09ld Device register read %08x\n",
			      (s64)current_ts64.tv_sec, current_ts64.tv_nsec,
			      पढ़ोl(device_base + ISL38XX_CTRL_STAT_REG));
			kसमय_get_real_ts64(&current_ts64);
			DEBUG(SHOW_TRACING,
			      "%lld.%09ld Device asleep counter %i\n",
			      (s64)current_ts64.tv_sec, current_ts64.tv_nsec,
			      counter);
#पूर्ण_अगर
		पूर्ण
		/* निश्चित the Wakeup पूर्णांकerrupt in the Device Interrupt Register */
		isl38xx_w32_flush(device_base, ISL38XX_DEV_INT_WAKEUP,
				  ISL38XX_DEV_INT_REG);

#अगर VERBOSE > SHOW_ERROR_MESSAGES
		udelay(ISL38XX_WRITEIO_DELAY);

		/* perक्रमm another पढ़ो on the Device Status Register */
		reg = पढ़ोl(device_base + ISL38XX_CTRL_STAT_REG);
		kसमय_get_real_ts64(&current_ts64);
		DEBUG(SHOW_TRACING, "%lld.%00ld Device register read %08x\n",
		      (s64)current_ts64.tv_sec, current_ts64.tv_nsec, reg);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* device is (still) awake  */
#अगर VERBOSE > SHOW_ERROR_MESSAGES
		DEBUG(SHOW_TRACING, "Device is in active state\n");
#पूर्ण_अगर
		/* trigger the device by setting the Update bit in the Device Int reg */

		isl38xx_w32_flush(device_base, ISL38XX_DEV_INT_UPDATE,
				  ISL38XX_DEV_INT_REG);
	पूर्ण
पूर्ण

व्योम
isl38xx_पूर्णांकerface_reset(व्योम __iomem *device_base, dma_addr_t host_address)
अणु
#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_FUNCTION_CALLS, "isl38xx_interface_reset\n");
#पूर्ण_अगर

	/* load the address of the control block in the device */
	isl38xx_w32_flush(device_base, host_address, ISL38XX_CTRL_BLK_BASE_REG);
	udelay(ISL38XX_WRITEIO_DELAY);

	/* set the reset bit in the Device Interrupt Register */
	isl38xx_w32_flush(device_base, ISL38XX_DEV_INT_RESET, ISL38XX_DEV_INT_REG);
	udelay(ISL38XX_WRITEIO_DELAY);

	/* enable the पूर्णांकerrupt क्रम detecting initialization */

	/* Note: Do not enable other पूर्णांकerrupts here. We want the
	 * device to have come up first 100% beक्रमe allowing any other
	 * पूर्णांकerrupts. */
	isl38xx_w32_flush(device_base, ISL38XX_INT_IDENT_INIT, ISL38XX_INT_EN_REG);
	udelay(ISL38XX_WRITEIO_DELAY);  /* allow complete full reset */
पूर्ण

व्योम
isl38xx_enable_common_पूर्णांकerrupts(व्योम __iomem *device_base)
अणु
	u32 reg;

	reg = ISL38XX_INT_IDENT_UPDATE | ISL38XX_INT_IDENT_SLEEP |
	      ISL38XX_INT_IDENT_WAKEUP;
	isl38xx_w32_flush(device_base, reg, ISL38XX_INT_EN_REG);
	udelay(ISL38XX_WRITEIO_DELAY);
पूर्ण

पूर्णांक
isl38xx_in_queue(isl38xx_control_block *cb, पूर्णांक queue)
अणु
	स्थिर s32 delta = (le32_to_cpu(cb->driver_curr_frag[queue]) -
			   le32_to_cpu(cb->device_curr_frag[queue]));

	/* determine the amount of fragments in the queue depending on the type
	 * of the queue, either transmit or receive */

	BUG_ON(delta < 0);	/* driver ptr must be ahead of device ptr */

	चयन (queue) अणु
		/* send queues */
	हाल ISL38XX_CB_TX_MGMTQ:
		BUG_ON(delta > ISL38XX_CB_MGMT_QSIZE);
		fallthrough;

	हाल ISL38XX_CB_TX_DATA_LQ:
	हाल ISL38XX_CB_TX_DATA_HQ:
		BUG_ON(delta > ISL38XX_CB_TX_QSIZE);
		वापस delta;

		/* receive queues */
	हाल ISL38XX_CB_RX_MGMTQ:
		BUG_ON(delta > ISL38XX_CB_MGMT_QSIZE);
		वापस ISL38XX_CB_MGMT_QSIZE - delta;

	हाल ISL38XX_CB_RX_DATA_LQ:
	हाल ISL38XX_CB_RX_DATA_HQ:
		BUG_ON(delta > ISL38XX_CB_RX_QSIZE);
		वापस ISL38XX_CB_RX_QSIZE - delta;
	पूर्ण
	BUG();
	वापस 0;
पूर्ण
