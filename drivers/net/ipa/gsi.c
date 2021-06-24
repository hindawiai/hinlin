<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2021 Linaro Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/bits.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/mutex.h>
#समावेश <linux/completion.h>
#समावेश <linux/पन.स>
#समावेश <linux/bug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/netdevice.h>

#समावेश "gsi.h"
#समावेश "gsi_reg.h"
#समावेश "gsi_private.h"
#समावेश "gsi_trans.h"
#समावेश "ipa_gsi.h"
#समावेश "ipa_data.h"
#समावेश "ipa_version.h"

/**
 * DOC: The IPA Generic Software Interface
 *
 * The generic software पूर्णांकerface (GSI) is an पूर्णांकegral component of the IPA,
 * providing a well-defined communication layer between the AP subप्रणाली
 * and the IPA core.  The modem uses the GSI layer as well.
 *
 *	--------	     ---------
 *	|      |	     |	     |
 *	|  AP  +<---.	.----+ Modem |
 *	|      +--. |	| .->+	     |
 *	|      |  | |	| |  |	     |
 *	--------  | |	| |  ---------
 *		  v |	v |
 *		--+-+---+-+--
 *		|    GSI    |
 *		|-----------|
 *		|	    |
 *		|    IPA    |
 *		|	    |
 *		-------------
 *
 * In the above diagram, the AP and Modem represent "execution environments"
 * (EEs), which are independent operating environments that use the IPA क्रम
 * data transfer.
 *
 * Each EE uses a set of unidirectional GSI "channels," which allow transfer
 * of data to or from the IPA.  A channel is implemented as a ring buffer,
 * with a DRAM-resident array of "transfer elements" (TREs) available to
 * describe transfers to or from other EEs through the IPA.  A transfer
 * element can also contain an immediate command, requesting the IPA perक्रमm
 * actions other than data transfer.
 *
 * Each TRE refers to a block of data--also located DRAM.  After writing one
 * or more TREs to a channel, the ग_लिखोr (either the IPA or an EE) ग_लिखोs a
 * करोorbell रेजिस्टर to inक्रमm the receiving side how many elements have
 * been written.
 *
 * Each channel has a GSI "event ring" associated with it.  An event ring
 * is implemented very much like a channel ring, but is always directed from
 * the IPA to an EE.  The IPA notअगरies an EE (such as the AP) about channel
 * events by adding an entry to the event ring associated with the channel.
 * The GSI then ग_लिखोs its करोorbell क्रम the event ring, causing the target
 * EE to be पूर्णांकerrupted.  Each entry in an event ring contains a poपूर्णांकer
 * to the channel TRE whose completion the event represents.
 *
 * Each TRE in a channel ring has a set of flags.  One flag indicates whether
 * the completion of the transfer operation generates an entry (and possibly
 * an पूर्णांकerrupt) in the channel's event ring.  Other flags allow transfer
 * elements to be chained together, क्रमming a single logical transaction.
 * TRE flags are used to control whether and when पूर्णांकerrupts are generated
 * to संकेत completion of channel transfers.
 *
 * Elements in channel and event rings are completed (or consumed) strictly
 * in order.  Completion of one entry implies the completion of all preceding
 * entries.  A single completion पूर्णांकerrupt can thereक्रमe communicate the
 * completion of many transfers.
 *
 * Note that all GSI रेजिस्टरs are little-endian, which is the assumed
 * endianness of I/O space accesses.  The accessor functions perक्रमm byte
 * swapping अगर needed (i.e., क्रम a big endian CPU).
 */

/* Delay period क्रम पूर्णांकerrupt moderation (in 32KHz IPA पूर्णांकernal समयr ticks) */
#घोषणा GSI_EVT_RING_INT_MODT		(32 * 1) /* 1ms under 32KHz घड़ी */

#घोषणा GSI_CMD_TIMEOUT			50	/* milliseconds */

#घोषणा GSI_CHANNEL_STOP_RETRIES	10
#घोषणा GSI_CHANNEL_MODEM_HALT_RETRIES	10

#घोषणा GSI_MHI_EVENT_ID_START		10	/* 1st reserved event id */
#घोषणा GSI_MHI_EVENT_ID_END		16	/* Last reserved event id */

#घोषणा GSI_ISR_MAX_ITER		50	/* Detect पूर्णांकerrupt storms */

/* An entry in an event ring */
काष्ठा gsi_event अणु
	__le64 xfer_ptr;
	__le16 len;
	u8 reserved1;
	u8 code;
	__le16 reserved2;
	u8 type;
	u8 chid;
पूर्ण;

/** gsi_channel_scratch_gpi - GPI protocol scratch रेजिस्टर
 * @max_outstanding_tre:
 *	Defines the maximum number of TREs allowed in a single transaction
 *	on a channel (in bytes).  This determines the amount of prefetch
 *	perक्रमmed by the hardware.  We configure this to equal the size of
 *	the TLV FIFO क्रम the channel.
 * @outstanding_threshold:
 *	Defines the threshold (in bytes) determining when the sequencer
 *	should update the channel करोorbell.  We configure this to equal
 *	the size of two TREs.
 */
काष्ठा gsi_channel_scratch_gpi अणु
	u64 reserved1;
	u16 reserved2;
	u16 max_outstanding_tre;
	u16 reserved3;
	u16 outstanding_threshold;
पूर्ण;

/** gsi_channel_scratch - channel scratch configuration area
 *
 * The exact पूर्णांकerpretation of this रेजिस्टर is protocol-specअगरic.
 * We only use GPI channels; see काष्ठा gsi_channel_scratch_gpi, above.
 */
जोड़ gsi_channel_scratch अणु
	काष्ठा gsi_channel_scratch_gpi gpi;
	काष्ठा अणु
		u32 word1;
		u32 word2;
		u32 word3;
		u32 word4;
	पूर्ण data;
पूर्ण;

/* Check things that can be validated at build समय. */
अटल व्योम gsi_validate_build(व्योम)
अणु
	/* This is used as a भागisor */
	BUILD_BUG_ON(!GSI_RING_ELEMENT_SIZE);

	/* Code assumes the size of channel and event ring element are
	 * the same (and fixed).  Make sure the size of an event ring
	 * element is what's expected.
	 */
	BUILD_BUG_ON(माप(काष्ठा gsi_event) != GSI_RING_ELEMENT_SIZE);

	/* Hardware requires a 2^n ring size.  We ensure the number of
	 * elements in an event ring is a घातer of 2 अन्यथाwhere; this
	 * ensure the elements themselves meet the requirement.
	 */
	BUILD_BUG_ON(!is_घातer_of_2(GSI_RING_ELEMENT_SIZE));

	/* The channel element size must fit in this field */
	BUILD_BUG_ON(GSI_RING_ELEMENT_SIZE > field_max(ELEMENT_SIZE_FMASK));

	/* The event ring element size must fit in this field */
	BUILD_BUG_ON(GSI_RING_ELEMENT_SIZE > field_max(EV_ELEMENT_SIZE_FMASK));
पूर्ण

/* Return the channel id associated with a given channel */
अटल u32 gsi_channel_id(काष्ठा gsi_channel *channel)
अणु
	वापस channel - &channel->gsi->channel[0];
पूर्ण

/* An initialized channel has a non-null GSI poपूर्णांकer */
अटल bool gsi_channel_initialized(काष्ठा gsi_channel *channel)
अणु
	वापस !!channel->gsi;
पूर्ण

/* Update the GSI IRQ type रेजिस्टर with the cached value */
अटल व्योम gsi_irq_type_update(काष्ठा gsi *gsi, u32 val)
अणु
	gsi->type_enabled_biपंचांगap = val;
	ioग_लिखो32(val, gsi->virt + GSI_CNTXT_TYPE_IRQ_MSK_OFFSET);
पूर्ण

अटल व्योम gsi_irq_type_enable(काष्ठा gsi *gsi, क्रमागत gsi_irq_type_id type_id)
अणु
	gsi_irq_type_update(gsi, gsi->type_enabled_biपंचांगap | BIT(type_id));
पूर्ण

अटल व्योम gsi_irq_type_disable(काष्ठा gsi *gsi, क्रमागत gsi_irq_type_id type_id)
अणु
	gsi_irq_type_update(gsi, gsi->type_enabled_biपंचांगap & ~BIT(type_id));
पूर्ण

/* Turn off all GSI पूर्णांकerrupts initially; there is no gsi_irq_tearकरोwn() */
अटल व्योम gsi_irq_setup(काष्ठा gsi *gsi)
अणु
	/* Disable all पूर्णांकerrupt types */
	gsi_irq_type_update(gsi, 0);

	/* Clear all type-specअगरic पूर्णांकerrupt masks */
	ioग_लिखो32(0, gsi->virt + GSI_CNTXT_SRC_CH_IRQ_MSK_OFFSET);
	ioग_लिखो32(0, gsi->virt + GSI_CNTXT_SRC_EV_CH_IRQ_MSK_OFFSET);
	ioग_लिखो32(0, gsi->virt + GSI_CNTXT_GLOB_IRQ_EN_OFFSET);
	ioग_लिखो32(0, gsi->virt + GSI_CNTXT_SRC_IEOB_IRQ_MSK_OFFSET);

	/* The पूर्णांकer-EE रेजिस्टरs are in the non-adjusted address range */
	ioग_लिखो32(0, gsi->virt_raw + GSI_INTER_EE_SRC_CH_IRQ_MSK_OFFSET);
	ioग_लिखो32(0, gsi->virt_raw + GSI_INTER_EE_SRC_EV_CH_IRQ_MSK_OFFSET);

	ioग_लिखो32(0, gsi->virt + GSI_CNTXT_GSI_IRQ_EN_OFFSET);
पूर्ण

/* Event ring commands are perक्रमmed one at a समय.  Their completion
 * is संकेतed by the event ring control GSI पूर्णांकerrupt type, which is
 * only enabled when we issue an event ring command.  Only the event
 * ring being operated on has this पूर्णांकerrupt enabled.
 */
अटल व्योम gsi_irq_ev_ctrl_enable(काष्ठा gsi *gsi, u32 evt_ring_id)
अणु
	u32 val = BIT(evt_ring_id);

	/* There's a small chance that a previous command completed
	 * after the पूर्णांकerrupt was disabled, so make sure we have no
	 * pending पूर्णांकerrupts beक्रमe we enable them.
	 */
	ioग_लिखो32(~0, gsi->virt + GSI_CNTXT_SRC_EV_CH_IRQ_CLR_OFFSET);

	ioग_लिखो32(val, gsi->virt + GSI_CNTXT_SRC_EV_CH_IRQ_MSK_OFFSET);
	gsi_irq_type_enable(gsi, GSI_EV_CTRL);
पूर्ण

/* Disable event ring control पूर्णांकerrupts */
अटल व्योम gsi_irq_ev_ctrl_disable(काष्ठा gsi *gsi)
अणु
	gsi_irq_type_disable(gsi, GSI_EV_CTRL);
	ioग_लिखो32(0, gsi->virt + GSI_CNTXT_SRC_EV_CH_IRQ_MSK_OFFSET);
पूर्ण

/* Channel commands are perक्रमmed one at a समय.  Their completion is
 * संकेतed by the channel control GSI पूर्णांकerrupt type, which is only
 * enabled when we issue a channel command.  Only the channel being
 * operated on has this पूर्णांकerrupt enabled.
 */
अटल व्योम gsi_irq_ch_ctrl_enable(काष्ठा gsi *gsi, u32 channel_id)
अणु
	u32 val = BIT(channel_id);

	/* There's a small chance that a previous command completed
	 * after the पूर्णांकerrupt was disabled, so make sure we have no
	 * pending पूर्णांकerrupts beक्रमe we enable them.
	 */
	ioग_लिखो32(~0, gsi->virt + GSI_CNTXT_SRC_CH_IRQ_CLR_OFFSET);

	ioग_लिखो32(val, gsi->virt + GSI_CNTXT_SRC_CH_IRQ_MSK_OFFSET);
	gsi_irq_type_enable(gsi, GSI_CH_CTRL);
पूर्ण

/* Disable channel control पूर्णांकerrupts */
अटल व्योम gsi_irq_ch_ctrl_disable(काष्ठा gsi *gsi)
अणु
	gsi_irq_type_disable(gsi, GSI_CH_CTRL);
	ioग_लिखो32(0, gsi->virt + GSI_CNTXT_SRC_CH_IRQ_MSK_OFFSET);
पूर्ण

अटल व्योम gsi_irq_ieob_enable_one(काष्ठा gsi *gsi, u32 evt_ring_id)
अणु
	bool enable_ieob = !gsi->ieob_enabled_biपंचांगap;
	u32 val;

	gsi->ieob_enabled_biपंचांगap |= BIT(evt_ring_id);
	val = gsi->ieob_enabled_biपंचांगap;
	ioग_लिखो32(val, gsi->virt + GSI_CNTXT_SRC_IEOB_IRQ_MSK_OFFSET);

	/* Enable the पूर्णांकerrupt type अगर this is the first channel enabled */
	अगर (enable_ieob)
		gsi_irq_type_enable(gsi, GSI_IEOB);
पूर्ण

अटल व्योम gsi_irq_ieob_disable(काष्ठा gsi *gsi, u32 event_mask)
अणु
	u32 val;

	gsi->ieob_enabled_biपंचांगap &= ~event_mask;

	/* Disable the पूर्णांकerrupt type अगर this was the last enabled channel */
	अगर (!gsi->ieob_enabled_biपंचांगap)
		gsi_irq_type_disable(gsi, GSI_IEOB);

	val = gsi->ieob_enabled_biपंचांगap;
	ioग_लिखो32(val, gsi->virt + GSI_CNTXT_SRC_IEOB_IRQ_MSK_OFFSET);
पूर्ण

अटल व्योम gsi_irq_ieob_disable_one(काष्ठा gsi *gsi, u32 evt_ring_id)
अणु
	gsi_irq_ieob_disable(gsi, BIT(evt_ring_id));
पूर्ण

/* Enable all GSI_पूर्णांकerrupt types */
अटल व्योम gsi_irq_enable(काष्ठा gsi *gsi)
अणु
	u32 val;

	/* Global पूर्णांकerrupts include hardware error reports.  Enable
	 * that so we can at least report the error should it occur.
	 */
	ioग_लिखो32(BIT(ERROR_INT), gsi->virt + GSI_CNTXT_GLOB_IRQ_EN_OFFSET);
	gsi_irq_type_update(gsi, gsi->type_enabled_biपंचांगap | BIT(GSI_GLOB_EE));

	/* General GSI पूर्णांकerrupts are reported to all EEs; अगर they occur
	 * they are unrecoverable (without reset).  A अवरोधpoपूर्णांक पूर्णांकerrupt
	 * also exists, but we करोn't support that.  We want to be notअगरied
	 * of errors so we can report them, even अगर they can't be handled.
	 */
	val = BIT(BUS_ERROR);
	val |= BIT(CMD_FIFO_OVRFLOW);
	val |= BIT(MCS_STACK_OVRFLOW);
	ioग_लिखो32(val, gsi->virt + GSI_CNTXT_GSI_IRQ_EN_OFFSET);
	gsi_irq_type_update(gsi, gsi->type_enabled_biपंचांगap | BIT(GSI_GENERAL));
पूर्ण

/* Disable all GSI पूर्णांकerrupt types */
अटल व्योम gsi_irq_disable(काष्ठा gsi *gsi)
अणु
	gsi_irq_type_update(gsi, 0);

	/* Clear the type-specअगरic पूर्णांकerrupt masks set by gsi_irq_enable() */
	ioग_लिखो32(0, gsi->virt + GSI_CNTXT_GSI_IRQ_EN_OFFSET);
	ioग_लिखो32(0, gsi->virt + GSI_CNTXT_GLOB_IRQ_EN_OFFSET);
पूर्ण

/* Return the भव address associated with a ring index */
व्योम *gsi_ring_virt(काष्ठा gsi_ring *ring, u32 index)
अणु
	/* Note: index *must* be used modulo the ring count here */
	वापस ring->virt + (index % ring->count) * GSI_RING_ELEMENT_SIZE;
पूर्ण

/* Return the 32-bit DMA address associated with a ring index */
अटल u32 gsi_ring_addr(काष्ठा gsi_ring *ring, u32 index)
अणु
	वापस lower_32_bits(ring->addr) + index * GSI_RING_ELEMENT_SIZE;
पूर्ण

/* Return the ring index of a 32-bit ring offset */
अटल u32 gsi_ring_index(काष्ठा gsi_ring *ring, u32 offset)
अणु
	वापस (offset - gsi_ring_addr(ring, 0)) / GSI_RING_ELEMENT_SIZE;
पूर्ण

/* Issue a GSI command by writing a value to a रेजिस्टर, then रुको क्रम
 * completion to be संकेतed.  Returns true अगर the command completes
 * or false अगर it बार out.
 */
अटल bool
gsi_command(काष्ठा gsi *gsi, u32 reg, u32 val, काष्ठा completion *completion)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(GSI_CMD_TIMEOUT);

	reinit_completion(completion);

	ioग_लिखो32(val, gsi->virt + reg);

	वापस !!रुको_क्रम_completion_समयout(completion, समयout);
पूर्ण

/* Return the hardware's notion of the current state of an event ring */
अटल क्रमागत gsi_evt_ring_state
gsi_evt_ring_state(काष्ठा gsi *gsi, u32 evt_ring_id)
अणु
	u32 val;

	val = ioपढ़ो32(gsi->virt + GSI_EV_CH_E_CNTXT_0_OFFSET(evt_ring_id));

	वापस u32_get_bits(val, EV_CHSTATE_FMASK);
पूर्ण

/* Issue an event ring command and रुको क्रम it to complete */
अटल व्योम gsi_evt_ring_command(काष्ठा gsi *gsi, u32 evt_ring_id,
				 क्रमागत gsi_evt_cmd_opcode opcode)
अणु
	काष्ठा gsi_evt_ring *evt_ring = &gsi->evt_ring[evt_ring_id];
	काष्ठा completion *completion = &evt_ring->completion;
	काष्ठा device *dev = gsi->dev;
	bool समयout;
	u32 val;

	/* Enable the completion पूर्णांकerrupt क्रम the command */
	gsi_irq_ev_ctrl_enable(gsi, evt_ring_id);

	val = u32_encode_bits(evt_ring_id, EV_CHID_FMASK);
	val |= u32_encode_bits(opcode, EV_OPCODE_FMASK);

	समयout = !gsi_command(gsi, GSI_EV_CH_CMD_OFFSET, val, completion);

	gsi_irq_ev_ctrl_disable(gsi);

	अगर (!समयout)
		वापस;

	dev_err(dev, "GSI command %u for event ring %u timed out, state %u\n",
		opcode, evt_ring_id, gsi_evt_ring_state(gsi, evt_ring_id));
पूर्ण

/* Allocate an event ring in NOT_ALLOCATED state */
अटल पूर्णांक gsi_evt_ring_alloc_command(काष्ठा gsi *gsi, u32 evt_ring_id)
अणु
	क्रमागत gsi_evt_ring_state state;

	/* Get initial event ring state */
	state = gsi_evt_ring_state(gsi, evt_ring_id);
	अगर (state != GSI_EVT_RING_STATE_NOT_ALLOCATED) अणु
		dev_err(gsi->dev, "event ring %u bad state %u before alloc\n",
			evt_ring_id, state);
		वापस -EINVAL;
	पूर्ण

	gsi_evt_ring_command(gsi, evt_ring_id, GSI_EVT_ALLOCATE);

	/* If successful the event ring state will have changed */
	state = gsi_evt_ring_state(gsi, evt_ring_id);
	अगर (state == GSI_EVT_RING_STATE_ALLOCATED)
		वापस 0;

	dev_err(gsi->dev, "event ring %u bad state %u after alloc\n",
		evt_ring_id, state);

	वापस -EIO;
पूर्ण

/* Reset a GSI event ring in ALLOCATED or ERROR state. */
अटल व्योम gsi_evt_ring_reset_command(काष्ठा gsi *gsi, u32 evt_ring_id)
अणु
	क्रमागत gsi_evt_ring_state state;

	state = gsi_evt_ring_state(gsi, evt_ring_id);
	अगर (state != GSI_EVT_RING_STATE_ALLOCATED &&
	    state != GSI_EVT_RING_STATE_ERROR) अणु
		dev_err(gsi->dev, "event ring %u bad state %u before reset\n",
			evt_ring_id, state);
		वापस;
	पूर्ण

	gsi_evt_ring_command(gsi, evt_ring_id, GSI_EVT_RESET);

	/* If successful the event ring state will have changed */
	state = gsi_evt_ring_state(gsi, evt_ring_id);
	अगर (state == GSI_EVT_RING_STATE_ALLOCATED)
		वापस;

	dev_err(gsi->dev, "event ring %u bad state %u after reset\n",
		evt_ring_id, state);
पूर्ण

/* Issue a hardware de-allocation request क्रम an allocated event ring */
अटल व्योम gsi_evt_ring_de_alloc_command(काष्ठा gsi *gsi, u32 evt_ring_id)
अणु
	क्रमागत gsi_evt_ring_state state;

	state = gsi_evt_ring_state(gsi, evt_ring_id);
	अगर (state != GSI_EVT_RING_STATE_ALLOCATED) अणु
		dev_err(gsi->dev, "event ring %u state %u before dealloc\n",
			evt_ring_id, state);
		वापस;
	पूर्ण

	gsi_evt_ring_command(gsi, evt_ring_id, GSI_EVT_DE_ALLOC);

	/* If successful the event ring state will have changed */
	state = gsi_evt_ring_state(gsi, evt_ring_id);
	अगर (state == GSI_EVT_RING_STATE_NOT_ALLOCATED)
		वापस;

	dev_err(gsi->dev, "event ring %u bad state %u after dealloc\n",
		evt_ring_id, state);
पूर्ण

/* Fetch the current state of a channel from hardware */
अटल क्रमागत gsi_channel_state gsi_channel_state(काष्ठा gsi_channel *channel)
अणु
	u32 channel_id = gsi_channel_id(channel);
	व्योम __iomem *virt = channel->gsi->virt;
	u32 val;

	val = ioपढ़ो32(virt + GSI_CH_C_CNTXT_0_OFFSET(channel_id));

	वापस u32_get_bits(val, CHSTATE_FMASK);
पूर्ण

/* Issue a channel command and रुको क्रम it to complete */
अटल व्योम
gsi_channel_command(काष्ठा gsi_channel *channel, क्रमागत gsi_ch_cmd_opcode opcode)
अणु
	काष्ठा completion *completion = &channel->completion;
	u32 channel_id = gsi_channel_id(channel);
	काष्ठा gsi *gsi = channel->gsi;
	काष्ठा device *dev = gsi->dev;
	bool समयout;
	u32 val;

	/* Enable the completion पूर्णांकerrupt क्रम the command */
	gsi_irq_ch_ctrl_enable(gsi, channel_id);

	val = u32_encode_bits(channel_id, CH_CHID_FMASK);
	val |= u32_encode_bits(opcode, CH_OPCODE_FMASK);
	समयout = !gsi_command(gsi, GSI_CH_CMD_OFFSET, val, completion);

	gsi_irq_ch_ctrl_disable(gsi);

	अगर (!समयout)
		वापस;

	dev_err(dev, "GSI command %u for channel %u timed out, state %u\n",
		opcode, channel_id, gsi_channel_state(channel));
पूर्ण

/* Allocate GSI channel in NOT_ALLOCATED state */
अटल पूर्णांक gsi_channel_alloc_command(काष्ठा gsi *gsi, u32 channel_id)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];
	काष्ठा device *dev = gsi->dev;
	क्रमागत gsi_channel_state state;

	/* Get initial channel state */
	state = gsi_channel_state(channel);
	अगर (state != GSI_CHANNEL_STATE_NOT_ALLOCATED) अणु
		dev_err(dev, "channel %u bad state %u before alloc\n",
			channel_id, state);
		वापस -EINVAL;
	पूर्ण

	gsi_channel_command(channel, GSI_CH_ALLOCATE);

	/* If successful the channel state will have changed */
	state = gsi_channel_state(channel);
	अगर (state == GSI_CHANNEL_STATE_ALLOCATED)
		वापस 0;

	dev_err(dev, "channel %u bad state %u after alloc\n",
		channel_id, state);

	वापस -EIO;
पूर्ण

/* Start an ALLOCATED channel */
अटल पूर्णांक gsi_channel_start_command(काष्ठा gsi_channel *channel)
अणु
	काष्ठा device *dev = channel->gsi->dev;
	क्रमागत gsi_channel_state state;

	state = gsi_channel_state(channel);
	अगर (state != GSI_CHANNEL_STATE_ALLOCATED &&
	    state != GSI_CHANNEL_STATE_STOPPED) अणु
		dev_err(dev, "channel %u bad state %u before start\n",
			gsi_channel_id(channel), state);
		वापस -EINVAL;
	पूर्ण

	gsi_channel_command(channel, GSI_CH_START);

	/* If successful the channel state will have changed */
	state = gsi_channel_state(channel);
	अगर (state == GSI_CHANNEL_STATE_STARTED)
		वापस 0;

	dev_err(dev, "channel %u bad state %u after start\n",
		gsi_channel_id(channel), state);

	वापस -EIO;
पूर्ण

/* Stop a GSI channel in STARTED state */
अटल पूर्णांक gsi_channel_stop_command(काष्ठा gsi_channel *channel)
अणु
	काष्ठा device *dev = channel->gsi->dev;
	क्रमागत gsi_channel_state state;

	state = gsi_channel_state(channel);

	/* Channel could have entered STOPPED state since last call
	 * अगर it समयd out.  If so, we're करोne.
	 */
	अगर (state == GSI_CHANNEL_STATE_STOPPED)
		वापस 0;

	अगर (state != GSI_CHANNEL_STATE_STARTED &&
	    state != GSI_CHANNEL_STATE_STOP_IN_PROC) अणु
		dev_err(dev, "channel %u bad state %u before stop\n",
			gsi_channel_id(channel), state);
		वापस -EINVAL;
	पूर्ण

	gsi_channel_command(channel, GSI_CH_STOP);

	/* If successful the channel state will have changed */
	state = gsi_channel_state(channel);
	अगर (state == GSI_CHANNEL_STATE_STOPPED)
		वापस 0;

	/* We may have to try again अगर stop is in progress */
	अगर (state == GSI_CHANNEL_STATE_STOP_IN_PROC)
		वापस -EAGAIN;

	dev_err(dev, "channel %u bad state %u after stop\n",
		gsi_channel_id(channel), state);

	वापस -EIO;
पूर्ण

/* Reset a GSI channel in ALLOCATED or ERROR state. */
अटल व्योम gsi_channel_reset_command(काष्ठा gsi_channel *channel)
अणु
	काष्ठा device *dev = channel->gsi->dev;
	क्रमागत gsi_channel_state state;

	/* A लघु delay is required beक्रमe a RESET command */
	usleep_range(USEC_PER_MSEC, 2 * USEC_PER_MSEC);

	state = gsi_channel_state(channel);
	अगर (state != GSI_CHANNEL_STATE_STOPPED &&
	    state != GSI_CHANNEL_STATE_ERROR) अणु
		/* No need to reset a channel alपढ़ोy in ALLOCATED state */
		अगर (state != GSI_CHANNEL_STATE_ALLOCATED)
			dev_err(dev, "channel %u bad state %u before reset\n",
				gsi_channel_id(channel), state);
		वापस;
	पूर्ण

	gsi_channel_command(channel, GSI_CH_RESET);

	/* If successful the channel state will have changed */
	state = gsi_channel_state(channel);
	अगर (state != GSI_CHANNEL_STATE_ALLOCATED)
		dev_err(dev, "channel %u bad state %u after reset\n",
			gsi_channel_id(channel), state);
पूर्ण

/* Deallocate an ALLOCATED GSI channel */
अटल व्योम gsi_channel_de_alloc_command(काष्ठा gsi *gsi, u32 channel_id)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];
	काष्ठा device *dev = gsi->dev;
	क्रमागत gsi_channel_state state;

	state = gsi_channel_state(channel);
	अगर (state != GSI_CHANNEL_STATE_ALLOCATED) अणु
		dev_err(dev, "channel %u bad state %u before dealloc\n",
			channel_id, state);
		वापस;
	पूर्ण

	gsi_channel_command(channel, GSI_CH_DE_ALLOC);

	/* If successful the channel state will have changed */
	state = gsi_channel_state(channel);

	अगर (state != GSI_CHANNEL_STATE_NOT_ALLOCATED)
		dev_err(dev, "channel %u bad state %u after dealloc\n",
			channel_id, state);
पूर्ण

/* Ring an event ring करोorbell, reporting the last entry processed by the AP.
 * The index argument (modulo the ring count) is the first unfilled entry, so
 * we supply one less than that with the करोorbell.  Update the event ring
 * index field with the value provided.
 */
अटल व्योम gsi_evt_ring_करोorbell(काष्ठा gsi *gsi, u32 evt_ring_id, u32 index)
अणु
	काष्ठा gsi_ring *ring = &gsi->evt_ring[evt_ring_id].ring;
	u32 val;

	ring->index = index;	/* Next unused entry */

	/* Note: index *must* be used modulo the ring count here */
	val = gsi_ring_addr(ring, (index - 1) % ring->count);
	ioग_लिखो32(val, gsi->virt + GSI_EV_CH_E_DOORBELL_0_OFFSET(evt_ring_id));
पूर्ण

/* Program an event ring क्रम use */
अटल व्योम gsi_evt_ring_program(काष्ठा gsi *gsi, u32 evt_ring_id)
अणु
	काष्ठा gsi_evt_ring *evt_ring = &gsi->evt_ring[evt_ring_id];
	माप_प्रकार size = evt_ring->ring.count * GSI_RING_ELEMENT_SIZE;
	u32 val;

	/* We program all event rings as GPI type/protocol */
	val = u32_encode_bits(GSI_CHANNEL_TYPE_GPI, EV_CHTYPE_FMASK);
	val |= EV_INTYPE_FMASK;
	val |= u32_encode_bits(GSI_RING_ELEMENT_SIZE, EV_ELEMENT_SIZE_FMASK);
	ioग_लिखो32(val, gsi->virt + GSI_EV_CH_E_CNTXT_0_OFFSET(evt_ring_id));

	val = ev_r_length_encoded(gsi->version, size);
	ioग_लिखो32(val, gsi->virt + GSI_EV_CH_E_CNTXT_1_OFFSET(evt_ring_id));

	/* The context 2 and 3 रेजिस्टरs store the low-order and
	 * high-order 32 bits of the address of the event ring,
	 * respectively.
	 */
	val = lower_32_bits(evt_ring->ring.addr);
	ioग_लिखो32(val, gsi->virt + GSI_EV_CH_E_CNTXT_2_OFFSET(evt_ring_id));
	val = upper_32_bits(evt_ring->ring.addr);
	ioग_लिखो32(val, gsi->virt + GSI_EV_CH_E_CNTXT_3_OFFSET(evt_ring_id));

	/* Enable पूर्णांकerrupt moderation by setting the moderation delay */
	val = u32_encode_bits(GSI_EVT_RING_INT_MODT, MODT_FMASK);
	val |= u32_encode_bits(1, MODC_FMASK);	/* comes from channel */
	ioग_लिखो32(val, gsi->virt + GSI_EV_CH_E_CNTXT_8_OFFSET(evt_ring_id));

	/* No MSI ग_लिखो data, and MSI address high and low address is 0 */
	ioग_लिखो32(0, gsi->virt + GSI_EV_CH_E_CNTXT_9_OFFSET(evt_ring_id));
	ioग_लिखो32(0, gsi->virt + GSI_EV_CH_E_CNTXT_10_OFFSET(evt_ring_id));
	ioग_लिखो32(0, gsi->virt + GSI_EV_CH_E_CNTXT_11_OFFSET(evt_ring_id));

	/* We करोn't need to get event पढ़ो poपूर्णांकer updates */
	ioग_लिखो32(0, gsi->virt + GSI_EV_CH_E_CNTXT_12_OFFSET(evt_ring_id));
	ioग_लिखो32(0, gsi->virt + GSI_EV_CH_E_CNTXT_13_OFFSET(evt_ring_id));

	/* Finally, tell the hardware we've completed event 0 (arbitrary) */
	gsi_evt_ring_करोorbell(gsi, evt_ring_id, 0);
पूर्ण

/* Find the transaction whose completion indicates a channel is quiesced */
अटल काष्ठा gsi_trans *gsi_channel_trans_last(काष्ठा gsi_channel *channel)
अणु
	काष्ठा gsi_trans_info *trans_info = &channel->trans_info;
	स्थिर काष्ठा list_head *list;
	काष्ठा gsi_trans *trans;

	spin_lock_bh(&trans_info->spinlock);

	/* There is a small chance a TX transaction got allocated just
	 * beक्रमe we disabled transmits, so check क्रम that.
	 */
	अगर (channel->toward_ipa) अणु
		list = &trans_info->alloc;
		अगर (!list_empty(list))
			जाओ करोne;
		list = &trans_info->pending;
		अगर (!list_empty(list))
			जाओ करोne;
	पूर्ण

	/* Otherwise (TX or RX) we want to रुको क्रम anything that
	 * has completed, or has been polled but not released yet.
	 */
	list = &trans_info->complete;
	अगर (!list_empty(list))
		जाओ करोne;
	list = &trans_info->polled;
	अगर (list_empty(list))
		list = शून्य;
करोne:
	trans = list ? list_last_entry(list, काष्ठा gsi_trans, links) : शून्य;

	/* Caller will रुको क्रम this, so take a reference */
	अगर (trans)
		refcount_inc(&trans->refcount);

	spin_unlock_bh(&trans_info->spinlock);

	वापस trans;
पूर्ण

/* Wait क्रम transaction activity on a channel to complete */
अटल व्योम gsi_channel_trans_quiesce(काष्ठा gsi_channel *channel)
अणु
	काष्ठा gsi_trans *trans;

	/* Get the last transaction, and रुको क्रम it to complete */
	trans = gsi_channel_trans_last(channel);
	अगर (trans) अणु
		रुको_क्रम_completion(&trans->completion);
		gsi_trans_मुक्त(trans);
	पूर्ण
पूर्ण

/* Program a channel क्रम use; there is no gsi_channel_deprogram() */
अटल व्योम gsi_channel_program(काष्ठा gsi_channel *channel, bool करोorbell)
अणु
	माप_प्रकार size = channel->tre_ring.count * GSI_RING_ELEMENT_SIZE;
	u32 channel_id = gsi_channel_id(channel);
	जोड़ gsi_channel_scratch scr = अणु पूर्ण;
	काष्ठा gsi_channel_scratch_gpi *gpi;
	काष्ठा gsi *gsi = channel->gsi;
	u32 wrr_weight = 0;
	u32 val;

	/* Arbitrarily pick TRE 0 as the first channel element to use */
	channel->tre_ring.index = 0;

	/* We program all channels as GPI type/protocol */
	val = chtype_protocol_encoded(gsi->version, GSI_CHANNEL_TYPE_GPI);
	अगर (channel->toward_ipa)
		val |= CHTYPE_सूची_FMASK;
	val |= u32_encode_bits(channel->evt_ring_id, ERINDEX_FMASK);
	val |= u32_encode_bits(GSI_RING_ELEMENT_SIZE, ELEMENT_SIZE_FMASK);
	ioग_लिखो32(val, gsi->virt + GSI_CH_C_CNTXT_0_OFFSET(channel_id));

	val = r_length_encoded(gsi->version, size);
	ioग_लिखो32(val, gsi->virt + GSI_CH_C_CNTXT_1_OFFSET(channel_id));

	/* The context 2 and 3 रेजिस्टरs store the low-order and
	 * high-order 32 bits of the address of the channel ring,
	 * respectively.
	 */
	val = lower_32_bits(channel->tre_ring.addr);
	ioग_लिखो32(val, gsi->virt + GSI_CH_C_CNTXT_2_OFFSET(channel_id));
	val = upper_32_bits(channel->tre_ring.addr);
	ioग_लिखो32(val, gsi->virt + GSI_CH_C_CNTXT_3_OFFSET(channel_id));

	/* Command channel माला_लो low weighted round-robin priority */
	अगर (channel->command)
		wrr_weight = field_max(WRR_WEIGHT_FMASK);
	val = u32_encode_bits(wrr_weight, WRR_WEIGHT_FMASK);

	/* Max prefetch is 1 segment (करो not set MAX_PREFETCH_FMASK) */

	/* No need to use the करोorbell engine starting at IPA v4.0 */
	अगर (gsi->version < IPA_VERSION_4_0 && करोorbell)
		val |= USE_DB_ENG_FMASK;

	/* v4.0 पूर्णांकroduces an escape buffer क्रम prefetch.  We use it
	 * on all but the AP command channel.
	 */
	अगर (gsi->version >= IPA_VERSION_4_0 && !channel->command) अणु
		/* If not otherwise set, prefetch buffers are used */
		अगर (gsi->version < IPA_VERSION_4_5)
			val |= USE_ESCAPE_BUF_ONLY_FMASK;
		अन्यथा
			val |= u32_encode_bits(GSI_ESCAPE_BUF_ONLY,
					       PREFETCH_MODE_FMASK);
	पूर्ण
	/* All channels set DB_IN_BYTES */
	अगर (gsi->version >= IPA_VERSION_4_9)
		val |= DB_IN_BYTES;

	ioग_लिखो32(val, gsi->virt + GSI_CH_C_QOS_OFFSET(channel_id));

	/* Now update the scratch रेजिस्टरs क्रम GPI protocol */
	gpi = &scr.gpi;
	gpi->max_outstanding_tre = gsi_channel_trans_tre_max(gsi, channel_id) *
					GSI_RING_ELEMENT_SIZE;
	gpi->outstanding_threshold = 2 * GSI_RING_ELEMENT_SIZE;

	val = scr.data.word1;
	ioग_लिखो32(val, gsi->virt + GSI_CH_C_SCRATCH_0_OFFSET(channel_id));

	val = scr.data.word2;
	ioग_लिखो32(val, gsi->virt + GSI_CH_C_SCRATCH_1_OFFSET(channel_id));

	val = scr.data.word3;
	ioग_लिखो32(val, gsi->virt + GSI_CH_C_SCRATCH_2_OFFSET(channel_id));

	/* We must preserve the upper 16 bits of the last scratch रेजिस्टर.
	 * The next sequence assumes those bits reमुख्य unchanged between the
	 * पढ़ो and the ग_लिखो.
	 */
	val = ioपढ़ो32(gsi->virt + GSI_CH_C_SCRATCH_3_OFFSET(channel_id));
	val = (scr.data.word4 & GENMASK(31, 16)) | (val & GENMASK(15, 0));
	ioग_लिखो32(val, gsi->virt + GSI_CH_C_SCRATCH_3_OFFSET(channel_id));

	/* All करोne! */
पूर्ण

अटल पूर्णांक __gsi_channel_start(काष्ठा gsi_channel *channel, bool start)
अणु
	काष्ठा gsi *gsi = channel->gsi;
	पूर्णांक ret;

	अगर (!start)
		वापस 0;

	mutex_lock(&gsi->mutex);

	ret = gsi_channel_start_command(channel);

	mutex_unlock(&gsi->mutex);

	वापस ret;
पूर्ण

/* Start an allocated GSI channel */
पूर्णांक gsi_channel_start(काष्ठा gsi *gsi, u32 channel_id)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];
	पूर्णांक ret;

	/* Enable NAPI and the completion पूर्णांकerrupt */
	napi_enable(&channel->napi);
	gsi_irq_ieob_enable_one(gsi, channel->evt_ring_id);

	ret = __gsi_channel_start(channel, true);
	अगर (ret) अणु
		gsi_irq_ieob_disable_one(gsi, channel->evt_ring_id);
		napi_disable(&channel->napi);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gsi_channel_stop_retry(काष्ठा gsi_channel *channel)
अणु
	u32 retries = GSI_CHANNEL_STOP_RETRIES;
	पूर्णांक ret;

	करो अणु
		ret = gsi_channel_stop_command(channel);
		अगर (ret != -EAGAIN)
			अवरोध;
		usleep_range(3 * USEC_PER_MSEC, 5 * USEC_PER_MSEC);
	पूर्ण जबतक (retries--);

	वापस ret;
पूर्ण

अटल पूर्णांक __gsi_channel_stop(काष्ठा gsi_channel *channel, bool stop)
अणु
	काष्ठा gsi *gsi = channel->gsi;
	पूर्णांक ret;

	/* Wait क्रम any underway transactions to complete beक्रमe stopping. */
	gsi_channel_trans_quiesce(channel);

	अगर (!stop)
		वापस 0;

	mutex_lock(&gsi->mutex);

	ret = gsi_channel_stop_retry(channel);

	mutex_unlock(&gsi->mutex);

	वापस ret;
पूर्ण

/* Stop a started channel */
पूर्णांक gsi_channel_stop(काष्ठा gsi *gsi, u32 channel_id)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];
	पूर्णांक ret;

	ret = __gsi_channel_stop(channel, true);
	अगर (ret)
		वापस ret;

	/* Disable the completion पूर्णांकerrupt and NAPI अगर successful */
	gsi_irq_ieob_disable_one(gsi, channel->evt_ring_id);
	napi_disable(&channel->napi);

	वापस 0;
पूर्ण

/* Reset and reconfigure a channel, (possibly) enabling the करोorbell engine */
व्योम gsi_channel_reset(काष्ठा gsi *gsi, u32 channel_id, bool करोorbell)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];

	mutex_lock(&gsi->mutex);

	gsi_channel_reset_command(channel);
	/* Due to a hardware quirk we may need to reset RX channels twice. */
	अगर (gsi->version < IPA_VERSION_4_0 && !channel->toward_ipa)
		gsi_channel_reset_command(channel);

	gsi_channel_program(channel, करोorbell);
	gsi_channel_trans_cancel_pending(channel);

	mutex_unlock(&gsi->mutex);
पूर्ण

/* Stop a STARTED channel क्रम suspend (using stop अगर requested) */
पूर्णांक gsi_channel_suspend(काष्ठा gsi *gsi, u32 channel_id, bool stop)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];
	पूर्णांक ret;

	ret = __gsi_channel_stop(channel, stop);
	अगर (ret)
		वापस ret;

	/* Ensure NAPI polling has finished. */
	napi_synchronize(&channel->napi);

	वापस 0;
पूर्ण

/* Resume a suspended channel (starting will be requested अगर STOPPED) */
पूर्णांक gsi_channel_resume(काष्ठा gsi *gsi, u32 channel_id, bool start)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];

	वापस __gsi_channel_start(channel, start);
पूर्ण

/**
 * gsi_channel_tx_queued() - Report queued TX transfers क्रम a channel
 * @channel:	Channel क्रम which to report
 *
 * Report to the network stack the number of bytes and transactions that
 * have been queued to hardware since last call.  This and the next function
 * supply inक्रमmation used by the network stack क्रम throttling.
 *
 * For each channel we track the number of transactions used and bytes of
 * data those transactions represent.  We also track what those values are
 * each समय this function is called.  Subtracting the two tells us
 * the number of bytes and transactions that have been added between
 * successive calls.
 *
 * Calling this each समय we ring the channel करोorbell allows us to
 * provide accurate inक्रमmation to the network stack about how much
 * work we've given the hardware at any poपूर्णांक in समय.
 */
व्योम gsi_channel_tx_queued(काष्ठा gsi_channel *channel)
अणु
	u32 trans_count;
	u32 byte_count;

	byte_count = channel->byte_count - channel->queued_byte_count;
	trans_count = channel->trans_count - channel->queued_trans_count;
	channel->queued_byte_count = channel->byte_count;
	channel->queued_trans_count = channel->trans_count;

	ipa_gsi_channel_tx_queued(channel->gsi, gsi_channel_id(channel),
				  trans_count, byte_count);
पूर्ण

/**
 * gsi_channel_tx_update() - Report completed TX transfers
 * @channel:	Channel that has completed transmitting packets
 * @trans:	Last transation known to be complete
 *
 * Compute the number of transactions and bytes that have been transferred
 * over a TX channel since the given transaction was committed.  Report this
 * inक्रमmation to the network stack.
 *
 * At the समय a transaction is committed, we record its channel's
 * committed transaction and byte counts *in the transaction*.
 * Completions are संकेतed by the hardware with an पूर्णांकerrupt, and
 * we can determine the latest completed transaction at that समय.
 *
 * The dअगरference between the byte/transaction count recorded in
 * the transaction and the count last समय we recorded a completion
 * tells us exactly how much data has been transferred between
 * completions.
 *
 * Calling this each समय we learn of a newly-completed transaction
 * allows us to provide accurate inक्रमmation to the network stack
 * about how much work has been completed by the hardware at a given
 * poपूर्णांक in समय.
 */
अटल व्योम
gsi_channel_tx_update(काष्ठा gsi_channel *channel, काष्ठा gsi_trans *trans)
अणु
	u64 byte_count = trans->byte_count + trans->len;
	u64 trans_count = trans->trans_count + 1;

	byte_count -= channel->compl_byte_count;
	channel->compl_byte_count += byte_count;
	trans_count -= channel->compl_trans_count;
	channel->compl_trans_count += trans_count;

	ipa_gsi_channel_tx_completed(channel->gsi, gsi_channel_id(channel),
				     trans_count, byte_count);
पूर्ण

/* Channel control पूर्णांकerrupt handler */
अटल व्योम gsi_isr_chan_ctrl(काष्ठा gsi *gsi)
अणु
	u32 channel_mask;

	channel_mask = ioपढ़ो32(gsi->virt + GSI_CNTXT_SRC_CH_IRQ_OFFSET);
	ioग_लिखो32(channel_mask, gsi->virt + GSI_CNTXT_SRC_CH_IRQ_CLR_OFFSET);

	जबतक (channel_mask) अणु
		u32 channel_id = __ffs(channel_mask);
		काष्ठा gsi_channel *channel;

		channel_mask ^= BIT(channel_id);

		channel = &gsi->channel[channel_id];

		complete(&channel->completion);
	पूर्ण
पूर्ण

/* Event ring control पूर्णांकerrupt handler */
अटल व्योम gsi_isr_evt_ctrl(काष्ठा gsi *gsi)
अणु
	u32 event_mask;

	event_mask = ioपढ़ो32(gsi->virt + GSI_CNTXT_SRC_EV_CH_IRQ_OFFSET);
	ioग_लिखो32(event_mask, gsi->virt + GSI_CNTXT_SRC_EV_CH_IRQ_CLR_OFFSET);

	जबतक (event_mask) अणु
		u32 evt_ring_id = __ffs(event_mask);
		काष्ठा gsi_evt_ring *evt_ring;

		event_mask ^= BIT(evt_ring_id);

		evt_ring = &gsi->evt_ring[evt_ring_id];

		complete(&evt_ring->completion);
	पूर्ण
पूर्ण

/* Global channel error पूर्णांकerrupt handler */
अटल व्योम
gsi_isr_glob_chan_err(काष्ठा gsi *gsi, u32 err_ee, u32 channel_id, u32 code)
अणु
	अगर (code == GSI_OUT_OF_RESOURCES) अणु
		dev_err(gsi->dev, "channel %u out of resources\n", channel_id);
		complete(&gsi->channel[channel_id].completion);
		वापस;
	पूर्ण

	/* Report, but otherwise ignore all other error codes */
	dev_err(gsi->dev, "channel %u global error ee 0x%08x code 0x%08x\n",
		channel_id, err_ee, code);
पूर्ण

/* Global event error पूर्णांकerrupt handler */
अटल व्योम
gsi_isr_glob_evt_err(काष्ठा gsi *gsi, u32 err_ee, u32 evt_ring_id, u32 code)
अणु
	अगर (code == GSI_OUT_OF_RESOURCES) अणु
		काष्ठा gsi_evt_ring *evt_ring = &gsi->evt_ring[evt_ring_id];
		u32 channel_id = gsi_channel_id(evt_ring->channel);

		complete(&evt_ring->completion);
		dev_err(gsi->dev, "evt_ring for channel %u out of resources\n",
			channel_id);
		वापस;
	पूर्ण

	/* Report, but otherwise ignore all other error codes */
	dev_err(gsi->dev, "event ring %u global error ee %u code 0x%08x\n",
		evt_ring_id, err_ee, code);
पूर्ण

/* Global error पूर्णांकerrupt handler */
अटल व्योम gsi_isr_glob_err(काष्ठा gsi *gsi)
अणु
	क्रमागत gsi_err_type type;
	क्रमागत gsi_err_code code;
	u32 which;
	u32 val;
	u32 ee;

	/* Get the logged error, then reinitialize the log */
	val = ioपढ़ो32(gsi->virt + GSI_ERROR_LOG_OFFSET);
	ioग_लिखो32(0, gsi->virt + GSI_ERROR_LOG_OFFSET);
	ioग_लिखो32(~0, gsi->virt + GSI_ERROR_LOG_CLR_OFFSET);

	ee = u32_get_bits(val, ERR_EE_FMASK);
	type = u32_get_bits(val, ERR_TYPE_FMASK);
	which = u32_get_bits(val, ERR_VIRT_IDX_FMASK);
	code = u32_get_bits(val, ERR_CODE_FMASK);

	अगर (type == GSI_ERR_TYPE_CHAN)
		gsi_isr_glob_chan_err(gsi, ee, which, code);
	अन्यथा अगर (type == GSI_ERR_TYPE_EVT)
		gsi_isr_glob_evt_err(gsi, ee, which, code);
	अन्यथा	/* type GSI_ERR_TYPE_GLOB should be fatal */
		dev_err(gsi->dev, "unexpected global error 0x%08x\n", type);
पूर्ण

/* Generic EE पूर्णांकerrupt handler */
अटल व्योम gsi_isr_gp_पूर्णांक1(काष्ठा gsi *gsi)
अणु
	u32 result;
	u32 val;

	/* This पूर्णांकerrupt is used to handle completions of the two GENERIC
	 * GSI commands.  We use these to allocate and halt channels on
	 * the modem's behalf due to a hardware quirk on IPA v4.2.  Once
	 * allocated, the modem "owns" these channels, and as a result we
	 * have no way of knowing the channel's state at any given समय.
	 *
	 * It is recommended that we halt the modem channels we allocated
	 * when shutting करोwn, but it's possible the channel isn't running
	 * at the समय we issue the HALT command.  We'll get an error in
	 * that हाल, but it's harmless (the channel is alपढ़ोy halted).
	 *
	 * For this reason, we silently ignore a CHANNEL_NOT_RUNNING error
	 * अगर we receive it.
	 */
	val = ioपढ़ो32(gsi->virt + GSI_CNTXT_SCRATCH_0_OFFSET);
	result = u32_get_bits(val, GENERIC_EE_RESULT_FMASK);

	चयन (result) अणु
	हाल GENERIC_EE_SUCCESS:
	हाल GENERIC_EE_CHANNEL_NOT_RUNNING:
		gsi->result = 0;
		अवरोध;

	हाल GENERIC_EE_RETRY:
		gsi->result = -EAGAIN;
		अवरोध;

	शेष:
		dev_err(gsi->dev, "global INT1 generic result %u\n", result);
		gsi->result = -EIO;
		अवरोध;
	पूर्ण

	complete(&gsi->completion);
पूर्ण

/* Inter-EE पूर्णांकerrupt handler */
अटल व्योम gsi_isr_glob_ee(काष्ठा gsi *gsi)
अणु
	u32 val;

	val = ioपढ़ो32(gsi->virt + GSI_CNTXT_GLOB_IRQ_STTS_OFFSET);

	अगर (val & BIT(ERROR_INT))
		gsi_isr_glob_err(gsi);

	ioग_लिखो32(val, gsi->virt + GSI_CNTXT_GLOB_IRQ_CLR_OFFSET);

	val &= ~BIT(ERROR_INT);

	अगर (val & BIT(GP_INT1)) अणु
		val ^= BIT(GP_INT1);
		gsi_isr_gp_पूर्णांक1(gsi);
	पूर्ण

	अगर (val)
		dev_err(gsi->dev, "unexpected global interrupt 0x%08x\n", val);
पूर्ण

/* I/O completion पूर्णांकerrupt event */
अटल व्योम gsi_isr_ieob(काष्ठा gsi *gsi)
अणु
	u32 event_mask;

	event_mask = ioपढ़ो32(gsi->virt + GSI_CNTXT_SRC_IEOB_IRQ_OFFSET);
	gsi_irq_ieob_disable(gsi, event_mask);
	ioग_लिखो32(event_mask, gsi->virt + GSI_CNTXT_SRC_IEOB_IRQ_CLR_OFFSET);

	जबतक (event_mask) अणु
		u32 evt_ring_id = __ffs(event_mask);

		event_mask ^= BIT(evt_ring_id);

		napi_schedule(&gsi->evt_ring[evt_ring_id].channel->napi);
	पूर्ण
पूर्ण

/* General event पूर्णांकerrupts represent serious problems, so report them */
अटल व्योम gsi_isr_general(काष्ठा gsi *gsi)
अणु
	काष्ठा device *dev = gsi->dev;
	u32 val;

	val = ioपढ़ो32(gsi->virt + GSI_CNTXT_GSI_IRQ_STTS_OFFSET);
	ioग_लिखो32(val, gsi->virt + GSI_CNTXT_GSI_IRQ_CLR_OFFSET);

	dev_err(dev, "unexpected general interrupt 0x%08x\n", val);
पूर्ण

/**
 * gsi_isr() - Top level GSI पूर्णांकerrupt service routine
 * @irq:	Interrupt number (ignored)
 * @dev_id:	GSI poपूर्णांकer supplied to request_irq()
 *
 * This is the मुख्य handler function रेजिस्टरed क्रम the GSI IRQ. Each type
 * of पूर्णांकerrupt has a separate handler function that is called from here.
 */
अटल irqवापस_t gsi_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा gsi *gsi = dev_id;
	u32 पूर्णांकr_mask;
	u32 cnt = 0;

	/* क्रमागत gsi_irq_type_id defines GSI पूर्णांकerrupt types */
	जबतक ((पूर्णांकr_mask = ioपढ़ो32(gsi->virt + GSI_CNTXT_TYPE_IRQ_OFFSET))) अणु
		/* पूर्णांकr_mask contains biपंचांगask of pending GSI पूर्णांकerrupts */
		करो अणु
			u32 gsi_पूर्णांकr = BIT(__ffs(पूर्णांकr_mask));

			पूर्णांकr_mask ^= gsi_पूर्णांकr;

			चयन (gsi_पूर्णांकr) अणु
			हाल BIT(GSI_CH_CTRL):
				gsi_isr_chan_ctrl(gsi);
				अवरोध;
			हाल BIT(GSI_EV_CTRL):
				gsi_isr_evt_ctrl(gsi);
				अवरोध;
			हाल BIT(GSI_GLOB_EE):
				gsi_isr_glob_ee(gsi);
				अवरोध;
			हाल BIT(GSI_IEOB):
				gsi_isr_ieob(gsi);
				अवरोध;
			हाल BIT(GSI_GENERAL):
				gsi_isr_general(gsi);
				अवरोध;
			शेष:
				dev_err(gsi->dev,
					"unrecognized interrupt type 0x%08x\n",
					gsi_पूर्णांकr);
				अवरोध;
			पूर्ण
		पूर्ण जबतक (पूर्णांकr_mask);

		अगर (++cnt > GSI_ISR_MAX_ITER) अणु
			dev_err(gsi->dev, "interrupt flood\n");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gsi_irq_init(काष्ठा gsi *gsi, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित पूर्णांक irq;
	पूर्णांक ret;

	ret = platक्रमm_get_irq_byname(pdev, "gsi");
	अगर (ret <= 0)
		वापस ret ? : -EINVAL;

	irq = ret;

	ret = request_irq(irq, gsi_isr, 0, "gsi", gsi);
	अगर (ret) अणु
		dev_err(dev, "error %d requesting \"gsi\" IRQ\n", ret);
		वापस ret;
	पूर्ण
	gsi->irq = irq;

	वापस 0;
पूर्ण

अटल व्योम gsi_irq_निकास(काष्ठा gsi *gsi)
अणु
	मुक्त_irq(gsi->irq, gsi);
पूर्ण

/* Return the transaction associated with a transfer completion event */
अटल काष्ठा gsi_trans *gsi_event_trans(काष्ठा gsi_channel *channel,
					 काष्ठा gsi_event *event)
अणु
	u32 tre_offset;
	u32 tre_index;

	/* Event xfer_ptr records the TRE it's associated with */
	tre_offset = lower_32_bits(le64_to_cpu(event->xfer_ptr));
	tre_index = gsi_ring_index(&channel->tre_ring, tre_offset);

	वापस gsi_channel_trans_mapped(channel, tre_index);
पूर्ण

/**
 * gsi_evt_ring_rx_update() - Record lengths of received data
 * @evt_ring:	Event ring associated with channel that received packets
 * @index:	Event index in ring reported by hardware
 *
 * Events क्रम RX channels contain the actual number of bytes received पूर्णांकo
 * the buffer.  Every event has a transaction associated with it, and here
 * we update transactions to record their actual received lengths.
 *
 * This function is called whenever we learn that the GSI hardware has filled
 * new events since the last समय we checked.  The ring's index field tells
 * the first entry in need of processing.  The index provided is the
 * first *unfilled* event in the ring (following the last filled one).
 *
 * Events are sequential within the event ring, and transactions are
 * sequential within the transaction pool.
 *
 * Note that @index always refers to an element *within* the event ring.
 */
अटल व्योम gsi_evt_ring_rx_update(काष्ठा gsi_evt_ring *evt_ring, u32 index)
अणु
	काष्ठा gsi_channel *channel = evt_ring->channel;
	काष्ठा gsi_ring *ring = &evt_ring->ring;
	काष्ठा gsi_trans_info *trans_info;
	काष्ठा gsi_event *event_करोne;
	काष्ठा gsi_event *event;
	काष्ठा gsi_trans *trans;
	u32 byte_count = 0;
	u32 old_index;
	u32 event_avail;

	trans_info = &channel->trans_info;

	/* We'll start with the oldest un-processed event.  RX channels
	 * replenish receive buffers in single-TRE transactions, so we
	 * can just map that event to its transaction.  Transactions
	 * associated with completion events are consecutive.
	 */
	old_index = ring->index;
	event = gsi_ring_virt(ring, old_index);
	trans = gsi_event_trans(channel, event);

	/* Compute the number of events to process beक्रमe we wrap,
	 * and determine when we'll be करोne processing events.
	 */
	event_avail = ring->count - old_index % ring->count;
	event_करोne = gsi_ring_virt(ring, index);
	करो अणु
		trans->len = __le16_to_cpu(event->len);
		byte_count += trans->len;

		/* Move on to the next event and transaction */
		अगर (--event_avail)
			event++;
		अन्यथा
			event = gsi_ring_virt(ring, 0);
		trans = gsi_trans_pool_next(&trans_info->pool, trans);
	पूर्ण जबतक (event != event_करोne);

	/* We record RX bytes when they are received */
	channel->byte_count += byte_count;
	channel->trans_count++;
पूर्ण

/* Initialize a ring, including allocating DMA memory क्रम its entries */
अटल पूर्णांक gsi_ring_alloc(काष्ठा gsi *gsi, काष्ठा gsi_ring *ring, u32 count)
अणु
	u32 size = count * GSI_RING_ELEMENT_SIZE;
	काष्ठा device *dev = gsi->dev;
	dma_addr_t addr;

	/* Hardware requires a 2^n ring size, with alignment equal to size.
	 * The DMA address वापसed by dma_alloc_coherent() is guaranteed to
	 * be a घातer-of-2 number of pages, which satisfies the requirement.
	 */
	ring->virt = dma_alloc_coherent(dev, size, &addr, GFP_KERNEL);
	अगर (!ring->virt)
		वापस -ENOMEM;

	ring->addr = addr;
	ring->count = count;

	वापस 0;
पूर्ण

/* Free a previously-allocated ring */
अटल व्योम gsi_ring_मुक्त(काष्ठा gsi *gsi, काष्ठा gsi_ring *ring)
अणु
	माप_प्रकार size = ring->count * GSI_RING_ELEMENT_SIZE;

	dma_मुक्त_coherent(gsi->dev, size, ring->virt, ring->addr);
पूर्ण

/* Allocate an available event ring id */
अटल पूर्णांक gsi_evt_ring_id_alloc(काष्ठा gsi *gsi)
अणु
	u32 evt_ring_id;

	अगर (gsi->event_biपंचांगap == ~0U) अणु
		dev_err(gsi->dev, "event rings exhausted\n");
		वापस -ENOSPC;
	पूर्ण

	evt_ring_id = ffz(gsi->event_biपंचांगap);
	gsi->event_biपंचांगap |= BIT(evt_ring_id);

	वापस (पूर्णांक)evt_ring_id;
पूर्ण

/* Free a previously-allocated event ring id */
अटल व्योम gsi_evt_ring_id_मुक्त(काष्ठा gsi *gsi, u32 evt_ring_id)
अणु
	gsi->event_biपंचांगap &= ~BIT(evt_ring_id);
पूर्ण

/* Ring a channel करोorbell, reporting the first un-filled entry */
व्योम gsi_channel_करोorbell(काष्ठा gsi_channel *channel)
अणु
	काष्ठा gsi_ring *tre_ring = &channel->tre_ring;
	u32 channel_id = gsi_channel_id(channel);
	काष्ठा gsi *gsi = channel->gsi;
	u32 val;

	/* Note: index *must* be used modulo the ring count here */
	val = gsi_ring_addr(tre_ring, tre_ring->index % tre_ring->count);
	ioग_लिखो32(val, gsi->virt + GSI_CH_C_DOORBELL_0_OFFSET(channel_id));
पूर्ण

/* Consult hardware, move any newly completed transactions to completed list */
अटल काष्ठा gsi_trans *gsi_channel_update(काष्ठा gsi_channel *channel)
अणु
	u32 evt_ring_id = channel->evt_ring_id;
	काष्ठा gsi *gsi = channel->gsi;
	काष्ठा gsi_evt_ring *evt_ring;
	काष्ठा gsi_trans *trans;
	काष्ठा gsi_ring *ring;
	u32 offset;
	u32 index;

	evt_ring = &gsi->evt_ring[evt_ring_id];
	ring = &evt_ring->ring;

	/* See अगर there's anything new to process; if not, we're करोne.  Note
	 * that index always refers to an entry *within* the event ring.
	 */
	offset = GSI_EV_CH_E_CNTXT_4_OFFSET(evt_ring_id);
	index = gsi_ring_index(ring, ioपढ़ो32(gsi->virt + offset));
	अगर (index == ring->index % ring->count)
		वापस शून्य;

	/* Get the transaction क्रम the latest completed event.  Take a
	 * reference to keep it from completing beक्रमe we give the events
	 * क्रम this and previous transactions back to the hardware.
	 */
	trans = gsi_event_trans(channel, gsi_ring_virt(ring, index - 1));
	refcount_inc(&trans->refcount);

	/* For RX channels, update each completed transaction with the number
	 * of bytes that were actually received.  For TX channels, report
	 * the number of transactions and bytes this completion represents
	 * up the network stack.
	 */
	अगर (channel->toward_ipa)
		gsi_channel_tx_update(channel, trans);
	अन्यथा
		gsi_evt_ring_rx_update(evt_ring, index);

	gsi_trans_move_complete(trans);

	/* Tell the hardware we've handled these events */
	gsi_evt_ring_करोorbell(channel->gsi, channel->evt_ring_id, index);

	gsi_trans_मुक्त(trans);

	वापस gsi_channel_trans_complete(channel);
पूर्ण

/**
 * gsi_channel_poll_one() - Return a single completed transaction on a channel
 * @channel:	Channel to be polled
 *
 * Return:	Transaction poपूर्णांकer, or null अगर none are available
 *
 * This function वापसs the first entry on a channel's completed transaction
 * list.  If that list is empty, the hardware is consulted to determine
 * whether any new transactions have completed.  If so, they're moved to the
 * completed list and the new first entry is वापसed.  If there are no more
 * completed transactions, a null poपूर्णांकer is वापसed.
 */
अटल काष्ठा gsi_trans *gsi_channel_poll_one(काष्ठा gsi_channel *channel)
अणु
	काष्ठा gsi_trans *trans;

	/* Get the first transaction from the completed list */
	trans = gsi_channel_trans_complete(channel);
	अगर (!trans)	/* List is empty; see अगर there's more to करो */
		trans = gsi_channel_update(channel);

	अगर (trans)
		gsi_trans_move_polled(trans);

	वापस trans;
पूर्ण

/**
 * gsi_channel_poll() - NAPI poll function क्रम a channel
 * @napi:	NAPI काष्ठाure क्रम the channel
 * @budget:	Budget supplied by NAPI core
 *
 * Return:	Number of items polled (<= budget)
 *
 * Single transactions completed by hardware are polled until either
 * the budget is exhausted, or there are no more.  Each transaction
 * polled is passed to gsi_trans_complete(), to perक्रमm reमुख्यing
 * completion processing and retire/मुक्त the transaction.
 */
अटल पूर्णांक gsi_channel_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा gsi_channel *channel;
	पूर्णांक count;

	channel = container_of(napi, काष्ठा gsi_channel, napi);
	क्रम (count = 0; count < budget; count++) अणु
		काष्ठा gsi_trans *trans;

		trans = gsi_channel_poll_one(channel);
		अगर (!trans)
			अवरोध;
		gsi_trans_complete(trans);
	पूर्ण

	अगर (count < budget && napi_complete(napi))
		gsi_irq_ieob_enable_one(channel->gsi, channel->evt_ring_id);

	वापस count;
पूर्ण

/* The event biपंचांगap represents which event ids are available क्रम allocation.
 * Set bits are not available, clear bits can be used.  This function
 * initializes the map so all events supported by the hardware are available,
 * then precludes any reserved events from being allocated.
 */
अटल u32 gsi_event_biपंचांगap_init(u32 evt_ring_max)
अणु
	u32 event_biपंचांगap = GENMASK(BITS_PER_LONG - 1, evt_ring_max);

	event_biपंचांगap |= GENMASK(GSI_MHI_EVENT_ID_END, GSI_MHI_EVENT_ID_START);

	वापस event_biपंचांगap;
पूर्ण

/* Setup function क्रम a single channel */
अटल पूर्णांक gsi_channel_setup_one(काष्ठा gsi *gsi, u32 channel_id)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];
	u32 evt_ring_id = channel->evt_ring_id;
	पूर्णांक ret;

	अगर (!gsi_channel_initialized(channel))
		वापस 0;

	ret = gsi_evt_ring_alloc_command(gsi, evt_ring_id);
	अगर (ret)
		वापस ret;

	gsi_evt_ring_program(gsi, evt_ring_id);

	ret = gsi_channel_alloc_command(gsi, channel_id);
	अगर (ret)
		जाओ err_evt_ring_de_alloc;

	gsi_channel_program(channel, true);

	अगर (channel->toward_ipa)
		netअगर_tx_napi_add(&gsi->dummy_dev, &channel->napi,
				  gsi_channel_poll, NAPI_POLL_WEIGHT);
	अन्यथा
		netअगर_napi_add(&gsi->dummy_dev, &channel->napi,
			       gsi_channel_poll, NAPI_POLL_WEIGHT);

	वापस 0;

err_evt_ring_de_alloc:
	/* We've done nothing with the event ring yet so don't reset */
	gsi_evt_ring_de_alloc_command(gsi, evt_ring_id);

	वापस ret;
पूर्ण

/* Inverse of gsi_channel_setup_one() */
अटल व्योम gsi_channel_tearकरोwn_one(काष्ठा gsi *gsi, u32 channel_id)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];
	u32 evt_ring_id = channel->evt_ring_id;

	अगर (!gsi_channel_initialized(channel))
		वापस;

	netअगर_napi_del(&channel->napi);

	gsi_channel_de_alloc_command(gsi, channel_id);
	gsi_evt_ring_reset_command(gsi, evt_ring_id);
	gsi_evt_ring_de_alloc_command(gsi, evt_ring_id);
पूर्ण

अटल पूर्णांक gsi_generic_command(काष्ठा gsi *gsi, u32 channel_id,
			       क्रमागत gsi_generic_cmd_opcode opcode)
अणु
	काष्ठा completion *completion = &gsi->completion;
	bool समयout;
	u32 val;

	/* The error global पूर्णांकerrupt type is always enabled (until we
	 * tearकरोwn), so we won't change that.  A generic EE command
	 * completes with a GSI global पूर्णांकerrupt of type GP_INT1.  We
	 * only perक्रमm one generic command at a समय (to allocate or
	 * halt a modem channel) and only from this function.  So we
	 * enable the GP_INT1 IRQ type here जबतक we're expecting it.
	 */
	val = BIT(ERROR_INT) | BIT(GP_INT1);
	ioग_लिखो32(val, gsi->virt + GSI_CNTXT_GLOB_IRQ_EN_OFFSET);

	/* First zero the result code field */
	val = ioपढ़ो32(gsi->virt + GSI_CNTXT_SCRATCH_0_OFFSET);
	val &= ~GENERIC_EE_RESULT_FMASK;
	ioग_लिखो32(val, gsi->virt + GSI_CNTXT_SCRATCH_0_OFFSET);

	/* Now issue the command */
	val = u32_encode_bits(opcode, GENERIC_OPCODE_FMASK);
	val |= u32_encode_bits(channel_id, GENERIC_CHID_FMASK);
	val |= u32_encode_bits(GSI_EE_MODEM, GENERIC_EE_FMASK);

	समयout = !gsi_command(gsi, GSI_GENERIC_CMD_OFFSET, val, completion);

	/* Disable the GP_INT1 IRQ type again */
	ioग_लिखो32(BIT(ERROR_INT), gsi->virt + GSI_CNTXT_GLOB_IRQ_EN_OFFSET);

	अगर (!समयout)
		वापस gsi->result;

	dev_err(gsi->dev, "GSI generic command %u to channel %u timed out\n",
		opcode, channel_id);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक gsi_modem_channel_alloc(काष्ठा gsi *gsi, u32 channel_id)
अणु
	वापस gsi_generic_command(gsi, channel_id,
				   GSI_GENERIC_ALLOCATE_CHANNEL);
पूर्ण

अटल व्योम gsi_modem_channel_halt(काष्ठा gsi *gsi, u32 channel_id)
अणु
	u32 retries = GSI_CHANNEL_MODEM_HALT_RETRIES;
	पूर्णांक ret;

	करो
		ret = gsi_generic_command(gsi, channel_id,
					  GSI_GENERIC_HALT_CHANNEL);
	जबतक (ret == -EAGAIN && retries--);

	अगर (ret)
		dev_err(gsi->dev, "error %d halting modem channel %u\n",
			ret, channel_id);
पूर्ण

/* Setup function क्रम channels */
अटल पूर्णांक gsi_channel_setup(काष्ठा gsi *gsi)
अणु
	u32 channel_id = 0;
	u32 mask;
	पूर्णांक ret;

	gsi_irq_enable(gsi);

	mutex_lock(&gsi->mutex);

	करो अणु
		ret = gsi_channel_setup_one(gsi, channel_id);
		अगर (ret)
			जाओ err_unwind;
	पूर्ण जबतक (++channel_id < gsi->channel_count);

	/* Make sure no channels were defined that hardware करोes not support */
	जबतक (channel_id < GSI_CHANNEL_COUNT_MAX) अणु
		काष्ठा gsi_channel *channel = &gsi->channel[channel_id++];

		अगर (!gsi_channel_initialized(channel))
			जारी;

		ret = -EINVAL;
		dev_err(gsi->dev, "channel %u not supported by hardware\n",
			channel_id - 1);
		channel_id = gsi->channel_count;
		जाओ err_unwind;
	पूर्ण

	/* Allocate modem channels अगर necessary */
	mask = gsi->modem_channel_biपंचांगap;
	जबतक (mask) अणु
		u32 modem_channel_id = __ffs(mask);

		ret = gsi_modem_channel_alloc(gsi, modem_channel_id);
		अगर (ret)
			जाओ err_unwind_modem;

		/* Clear bit from mask only after success (क्रम unwind) */
		mask ^= BIT(modem_channel_id);
	पूर्ण

	mutex_unlock(&gsi->mutex);

	वापस 0;

err_unwind_modem:
	/* Compute which modem channels need to be deallocated */
	mask ^= gsi->modem_channel_biपंचांगap;
	जबतक (mask) अणु
		channel_id = __fls(mask);

		mask ^= BIT(channel_id);

		gsi_modem_channel_halt(gsi, channel_id);
	पूर्ण

err_unwind:
	जबतक (channel_id--)
		gsi_channel_tearकरोwn_one(gsi, channel_id);

	mutex_unlock(&gsi->mutex);

	gsi_irq_disable(gsi);

	वापस ret;
पूर्ण

/* Inverse of gsi_channel_setup() */
अटल व्योम gsi_channel_tearकरोwn(काष्ठा gsi *gsi)
अणु
	u32 mask = gsi->modem_channel_biपंचांगap;
	u32 channel_id;

	mutex_lock(&gsi->mutex);

	जबतक (mask) अणु
		channel_id = __fls(mask);

		mask ^= BIT(channel_id);

		gsi_modem_channel_halt(gsi, channel_id);
	पूर्ण

	channel_id = gsi->channel_count - 1;
	करो
		gsi_channel_tearकरोwn_one(gsi, channel_id);
	जबतक (channel_id--);

	mutex_unlock(&gsi->mutex);

	gsi_irq_disable(gsi);
पूर्ण

/* Setup function क्रम GSI.  GSI firmware must be loaded and initialized */
पूर्णांक gsi_setup(काष्ठा gsi *gsi)
अणु
	काष्ठा device *dev = gsi->dev;
	u32 val;

	/* Here is where we first touch the GSI hardware */
	val = ioपढ़ो32(gsi->virt + GSI_GSI_STATUS_OFFSET);
	अगर (!(val & ENABLED_FMASK)) अणु
		dev_err(dev, "GSI has not been enabled\n");
		वापस -EIO;
	पूर्ण

	gsi_irq_setup(gsi);		/* No matching tearकरोwn required */

	val = ioपढ़ो32(gsi->virt + GSI_GSI_HW_PARAM_2_OFFSET);

	gsi->channel_count = u32_get_bits(val, NUM_CH_PER_EE_FMASK);
	अगर (!gsi->channel_count) अणु
		dev_err(dev, "GSI reports zero channels supported\n");
		वापस -EINVAL;
	पूर्ण
	अगर (gsi->channel_count > GSI_CHANNEL_COUNT_MAX) अणु
		dev_warn(dev,
			 "limiting to %u channels; hardware supports %u\n",
			 GSI_CHANNEL_COUNT_MAX, gsi->channel_count);
		gsi->channel_count = GSI_CHANNEL_COUNT_MAX;
	पूर्ण

	gsi->evt_ring_count = u32_get_bits(val, NUM_EV_PER_EE_FMASK);
	अगर (!gsi->evt_ring_count) अणु
		dev_err(dev, "GSI reports zero event rings supported\n");
		वापस -EINVAL;
	पूर्ण
	अगर (gsi->evt_ring_count > GSI_EVT_RING_COUNT_MAX) अणु
		dev_warn(dev,
			 "limiting to %u event rings; hardware supports %u\n",
			 GSI_EVT_RING_COUNT_MAX, gsi->evt_ring_count);
		gsi->evt_ring_count = GSI_EVT_RING_COUNT_MAX;
	पूर्ण

	/* Initialize the error log */
	ioग_लिखो32(0, gsi->virt + GSI_ERROR_LOG_OFFSET);

	/* Writing 1 indicates IRQ पूर्णांकerrupts; 0 would be MSI */
	ioग_लिखो32(1, gsi->virt + GSI_CNTXT_INTSET_OFFSET);

	वापस gsi_channel_setup(gsi);
पूर्ण

/* Inverse of gsi_setup() */
व्योम gsi_tearकरोwn(काष्ठा gsi *gsi)
अणु
	gsi_channel_tearकरोwn(gsi);
पूर्ण

/* Initialize a channel's event ring */
अटल पूर्णांक gsi_channel_evt_ring_init(काष्ठा gsi_channel *channel)
अणु
	काष्ठा gsi *gsi = channel->gsi;
	काष्ठा gsi_evt_ring *evt_ring;
	पूर्णांक ret;

	ret = gsi_evt_ring_id_alloc(gsi);
	अगर (ret < 0)
		वापस ret;
	channel->evt_ring_id = ret;

	evt_ring = &gsi->evt_ring[channel->evt_ring_id];
	evt_ring->channel = channel;

	ret = gsi_ring_alloc(gsi, &evt_ring->ring, channel->event_count);
	अगर (!ret)
		वापस 0;	/* Success! */

	dev_err(gsi->dev, "error %d allocating channel %u event ring\n",
		ret, gsi_channel_id(channel));

	gsi_evt_ring_id_मुक्त(gsi, channel->evt_ring_id);

	वापस ret;
पूर्ण

/* Inverse of gsi_channel_evt_ring_init() */
अटल व्योम gsi_channel_evt_ring_निकास(काष्ठा gsi_channel *channel)
अणु
	u32 evt_ring_id = channel->evt_ring_id;
	काष्ठा gsi *gsi = channel->gsi;
	काष्ठा gsi_evt_ring *evt_ring;

	evt_ring = &gsi->evt_ring[evt_ring_id];
	gsi_ring_मुक्त(gsi, &evt_ring->ring);
	gsi_evt_ring_id_मुक्त(gsi, evt_ring_id);
पूर्ण

/* Init function क्रम event rings; there is no gsi_evt_ring_निकास() */
अटल व्योम gsi_evt_ring_init(काष्ठा gsi *gsi)
अणु
	u32 evt_ring_id = 0;

	gsi->event_biपंचांगap = gsi_event_biपंचांगap_init(GSI_EVT_RING_COUNT_MAX);
	gsi->ieob_enabled_biपंचांगap = 0;
	करो
		init_completion(&gsi->evt_ring[evt_ring_id].completion);
	जबतक (++evt_ring_id < GSI_EVT_RING_COUNT_MAX);
पूर्ण

अटल bool gsi_channel_data_valid(काष्ठा gsi *gsi,
				   स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data)
अणु
#अगर_घोषित IPA_VALIDATION
	u32 channel_id = data->channel_id;
	काष्ठा device *dev = gsi->dev;

	/* Make sure channel ids are in the range driver supports */
	अगर (channel_id >= GSI_CHANNEL_COUNT_MAX) अणु
		dev_err(dev, "bad channel id %u; must be less than %u\n",
			channel_id, GSI_CHANNEL_COUNT_MAX);
		वापस false;
	पूर्ण

	अगर (data->ee_id != GSI_EE_AP && data->ee_id != GSI_EE_MODEM) अणु
		dev_err(dev, "bad EE id %u; not AP or modem\n", data->ee_id);
		वापस false;
	पूर्ण

	अगर (!data->channel.tlv_count ||
	    data->channel.tlv_count > GSI_TLV_MAX) अणु
		dev_err(dev, "channel %u bad tlv_count %u; must be 1..%u\n",
			channel_id, data->channel.tlv_count, GSI_TLV_MAX);
		वापस false;
	पूर्ण

	/* We have to allow at least one maximally-sized transaction to
	 * be outstanding (which would use tlv_count TREs).  Given how
	 * gsi_channel_tre_max() is computed, tre_count has to be almost
	 * twice the TLV FIFO size to satisfy this requirement.
	 */
	अगर (data->channel.tre_count < 2 * data->channel.tlv_count - 1) अणु
		dev_err(dev, "channel %u TLV count %u exceeds TRE count %u\n",
			channel_id, data->channel.tlv_count,
			data->channel.tre_count);
		वापस false;
	पूर्ण

	अगर (!is_घातer_of_2(data->channel.tre_count)) अणु
		dev_err(dev, "channel %u bad tre_count %u; not power of 2\n",
			channel_id, data->channel.tre_count);
		वापस false;
	पूर्ण

	अगर (!is_घातer_of_2(data->channel.event_count)) अणु
		dev_err(dev, "channel %u bad event_count %u; not power of 2\n",
			channel_id, data->channel.event_count);
		वापस false;
	पूर्ण
#पूर्ण_अगर /* IPA_VALIDATION */

	वापस true;
पूर्ण

/* Init function क्रम a single channel */
अटल पूर्णांक gsi_channel_init_one(काष्ठा gsi *gsi,
				स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data,
				bool command)
अणु
	काष्ठा gsi_channel *channel;
	u32 tre_count;
	पूर्णांक ret;

	अगर (!gsi_channel_data_valid(gsi, data))
		वापस -EINVAL;

	/* Worst हाल we need an event क्रम every outstanding TRE */
	अगर (data->channel.tre_count > data->channel.event_count) अणु
		tre_count = data->channel.event_count;
		dev_warn(gsi->dev, "channel %u limited to %u TREs\n",
			 data->channel_id, tre_count);
	पूर्ण अन्यथा अणु
		tre_count = data->channel.tre_count;
	पूर्ण

	channel = &gsi->channel[data->channel_id];
	स_रखो(channel, 0, माप(*channel));

	channel->gsi = gsi;
	channel->toward_ipa = data->toward_ipa;
	channel->command = command;
	channel->tlv_count = data->channel.tlv_count;
	channel->tre_count = tre_count;
	channel->event_count = data->channel.event_count;
	init_completion(&channel->completion);

	ret = gsi_channel_evt_ring_init(channel);
	अगर (ret)
		जाओ err_clear_gsi;

	ret = gsi_ring_alloc(gsi, &channel->tre_ring, data->channel.tre_count);
	अगर (ret) अणु
		dev_err(gsi->dev, "error %d allocating channel %u ring\n",
			ret, data->channel_id);
		जाओ err_channel_evt_ring_निकास;
	पूर्ण

	ret = gsi_channel_trans_init(gsi, data->channel_id);
	अगर (ret)
		जाओ err_ring_मुक्त;

	अगर (command) अणु
		u32 tre_max = gsi_channel_tre_max(gsi, data->channel_id);

		ret = ipa_cmd_pool_init(channel, tre_max);
	पूर्ण
	अगर (!ret)
		वापस 0;	/* Success! */

	gsi_channel_trans_निकास(channel);
err_ring_मुक्त:
	gsi_ring_मुक्त(gsi, &channel->tre_ring);
err_channel_evt_ring_निकास:
	gsi_channel_evt_ring_निकास(channel);
err_clear_gsi:
	channel->gsi = शून्य;	/* Mark it not (fully) initialized */

	वापस ret;
पूर्ण

/* Inverse of gsi_channel_init_one() */
अटल व्योम gsi_channel_निकास_one(काष्ठा gsi_channel *channel)
अणु
	अगर (!gsi_channel_initialized(channel))
		वापस;

	अगर (channel->command)
		ipa_cmd_pool_निकास(channel);
	gsi_channel_trans_निकास(channel);
	gsi_ring_मुक्त(channel->gsi, &channel->tre_ring);
	gsi_channel_evt_ring_निकास(channel);
पूर्ण

/* Init function क्रम channels */
अटल पूर्णांक gsi_channel_init(काष्ठा gsi *gsi, u32 count,
			    स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data)
अणु
	bool modem_alloc;
	पूर्णांक ret = 0;
	u32 i;

	/* IPA v4.2 requires the AP to allocate channels क्रम the modem */
	modem_alloc = gsi->version == IPA_VERSION_4_2;

	gsi_evt_ring_init(gsi);			/* No matching निकास required */

	/* The endpoपूर्णांक data array is indexed by endpoपूर्णांक name */
	क्रम (i = 0; i < count; i++) अणु
		bool command = i == IPA_ENDPOINT_AP_COMMAND_TX;

		अगर (ipa_gsi_endpoपूर्णांक_data_empty(&data[i]))
			जारी;	/* Skip over empty slots */

		/* Mark modem channels to be allocated (hardware workaround) */
		अगर (data[i].ee_id == GSI_EE_MODEM) अणु
			अगर (modem_alloc)
				gsi->modem_channel_biपंचांगap |=
						BIT(data[i].channel_id);
			जारी;
		पूर्ण

		ret = gsi_channel_init_one(gsi, &data[i], command);
		अगर (ret)
			जाओ err_unwind;
	पूर्ण

	वापस ret;

err_unwind:
	जबतक (i--) अणु
		अगर (ipa_gsi_endpoपूर्णांक_data_empty(&data[i]))
			जारी;
		अगर (modem_alloc && data[i].ee_id == GSI_EE_MODEM) अणु
			gsi->modem_channel_biपंचांगap &= ~BIT(data[i].channel_id);
			जारी;
		पूर्ण
		gsi_channel_निकास_one(&gsi->channel[data->channel_id]);
	पूर्ण

	वापस ret;
पूर्ण

/* Inverse of gsi_channel_init() */
अटल व्योम gsi_channel_निकास(काष्ठा gsi *gsi)
अणु
	u32 channel_id = GSI_CHANNEL_COUNT_MAX - 1;

	करो
		gsi_channel_निकास_one(&gsi->channel[channel_id]);
	जबतक (channel_id--);
	gsi->modem_channel_biपंचांगap = 0;
पूर्ण

/* Init function क्रम GSI.  GSI hardware करोes not need to be "ready" */
पूर्णांक gsi_init(काष्ठा gsi *gsi, काष्ठा platक्रमm_device *pdev,
	     क्रमागत ipa_version version, u32 count,
	     स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	resource_माप_प्रकार size;
	u32 adjust;
	पूर्णांक ret;

	gsi_validate_build();

	gsi->dev = dev;
	gsi->version = version;

	/* GSI uses NAPI on all channels.  Create a dummy network device
	 * क्रम the channel NAPI contexts to be associated with.
	 */
	init_dummy_netdev(&gsi->dummy_dev);

	/* Get GSI memory range and map it */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "gsi");
	अगर (!res) अणु
		dev_err(dev, "DT error getting \"gsi\" memory property\n");
		वापस -ENODEV;
	पूर्ण

	size = resource_size(res);
	अगर (res->start > U32_MAX || size > U32_MAX - res->start) अणु
		dev_err(dev, "DT memory resource \"gsi\" out of range\n");
		वापस -EINVAL;
	पूर्ण

	/* Make sure we can make our poपूर्णांकer adjusपंचांगent अगर necessary */
	adjust = gsi->version < IPA_VERSION_4_5 ? 0 : GSI_EE_REG_ADJUST;
	अगर (res->start < adjust) अणु
		dev_err(dev, "DT memory resource \"gsi\" too low (< %u)\n",
			adjust);
		वापस -EINVAL;
	पूर्ण

	gsi->virt_raw = ioremap(res->start, size);
	अगर (!gsi->virt_raw) अणु
		dev_err(dev, "unable to remap \"gsi\" memory\n");
		वापस -ENOMEM;
	पूर्ण
	/* Most रेजिस्टरs are accessed using an adjusted रेजिस्टर range */
	gsi->virt = gsi->virt_raw - adjust;

	init_completion(&gsi->completion);

	ret = gsi_irq_init(gsi, pdev);
	अगर (ret)
		जाओ err_iounmap;

	ret = gsi_channel_init(gsi, count, data);
	अगर (ret)
		जाओ err_irq_निकास;

	mutex_init(&gsi->mutex);

	वापस 0;

err_irq_निकास:
	gsi_irq_निकास(gsi);
err_iounmap:
	iounmap(gsi->virt_raw);

	वापस ret;
पूर्ण

/* Inverse of gsi_init() */
व्योम gsi_निकास(काष्ठा gsi *gsi)
अणु
	mutex_destroy(&gsi->mutex);
	gsi_channel_निकास(gsi);
	gsi_irq_निकास(gsi);
	iounmap(gsi->virt_raw);
पूर्ण

/* The maximum number of outstanding TREs on a channel.  This limits
 * a channel's maximum number of transactions outstanding (worst हाल
 * is one TRE per transaction).
 *
 * The असलolute limit is the number of TREs in the channel's TRE ring,
 * and in theory we should be able use all of them.  But in practice,
 * करोing that led to the hardware reporting exhaustion of event ring
 * slots क्रम writing completion inक्रमmation.  So the hardware limit
 * would be (tre_count - 1).
 *
 * We reduce it a bit further though.  Transaction resource pools are
 * sized to be a little larger than this maximum, to allow resource
 * allocations to always be contiguous.  The number of entries in a
 * TRE ring buffer is a घातer of 2, and the extra resources in a pool
 * tends to nearly द्विगुन the memory allocated क्रम it.  Reducing the
 * maximum number of outstanding TREs allows the number of entries in
 * a pool to aव्योम crossing that घातer-of-2 boundary, and this can
 * substantially reduce pool memory requirements.  The number we
 * reduce it by matches the number added in gsi_trans_pool_init().
 */
u32 gsi_channel_tre_max(काष्ठा gsi *gsi, u32 channel_id)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];

	/* Hardware limit is channel->tre_count - 1 */
	वापस channel->tre_count - (channel->tlv_count - 1);
पूर्ण

/* Returns the maximum number of TREs in a single transaction क्रम a channel */
u32 gsi_channel_trans_tre_max(काष्ठा gsi *gsi, u32 channel_id)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];

	वापस channel->tlv_count;
पूर्ण
