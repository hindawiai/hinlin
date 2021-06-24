<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Linux क्रम S/390 Lan Channel Station Network Driver
 *
 *  Copyright IBM Corp. 1999, 2009
 *  Author(s): Original Code written by
 *			DJ Barrow <djbarrow@de.ibm.com,barrow_dj@yahoo.com>
 *	       Rewritten by
 *			Frank Pavlic <fpavlic@de.ibm.com> and
 *			Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT		"lcs"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/अगर.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/fddidevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/igmp.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <net/arp.h>
#समावेश <net/ip.h>

#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/idals.h>
#समावेश <यंत्र/समयx.h>
#समावेश <linux/device.h>
#समावेश <यंत्र/ccwgroup.h>

#समावेश "lcs.h"


#अगर !defined(CONFIG_ETHERNET) && !defined(CONFIG_FDDI)
#त्रुटि Cannot compile lcs.c without some net devices चयनed on.
#पूर्ण_अगर

/**
 * initialization string क्रम output
 */

अटल अक्षर version[] __initdata = "LCS driver";

/**
  * the root device क्रम lcs group devices
  */
अटल काष्ठा device *lcs_root_dev;

/**
 * Some prototypes.
 */
अटल व्योम lcs_tasklet(अचिन्हित दीर्घ);
अटल व्योम lcs_start_kernel_thपढ़ो(काष्ठा work_काष्ठा *);
अटल व्योम lcs_get_frames_cb(काष्ठा lcs_channel *, काष्ठा lcs_buffer *);
#अगर_घोषित CONFIG_IP_MULTICAST
अटल पूर्णांक lcs_send_delipm(काष्ठा lcs_card *, काष्ठा lcs_ipm_list *);
#पूर्ण_अगर /* CONFIG_IP_MULTICAST */
अटल पूर्णांक lcs_recovery(व्योम *ptr);

/**
 * Debug Facility Stuff
 */
अटल अक्षर debug_buffer[255];
अटल debug_info_t *lcs_dbf_setup;
अटल debug_info_t *lcs_dbf_trace;

/**
 *  LCS Debug Facility functions
 */
अटल व्योम
lcs_unरेजिस्टर_debug_facility(व्योम)
अणु
	debug_unरेजिस्टर(lcs_dbf_setup);
	debug_unरेजिस्टर(lcs_dbf_trace);
पूर्ण

अटल पूर्णांक
lcs_रेजिस्टर_debug_facility(व्योम)
अणु
	lcs_dbf_setup = debug_रेजिस्टर("lcs_setup", 2, 1, 8);
	lcs_dbf_trace = debug_रेजिस्टर("lcs_trace", 4, 1, 8);
	अगर (lcs_dbf_setup == शून्य || lcs_dbf_trace == शून्य) अणु
		pr_err("Not enough memory for debug facility.\n");
		lcs_unरेजिस्टर_debug_facility();
		वापस -ENOMEM;
	पूर्ण
	debug_रेजिस्टर_view(lcs_dbf_setup, &debug_hex_ascii_view);
	debug_set_level(lcs_dbf_setup, 2);
	debug_रेजिस्टर_view(lcs_dbf_trace, &debug_hex_ascii_view);
	debug_set_level(lcs_dbf_trace, 2);
	वापस 0;
पूर्ण

/**
 * Allocate io buffers.
 */
अटल पूर्णांक
lcs_alloc_channel(काष्ठा lcs_channel *channel)
अणु
	पूर्णांक cnt;

	LCS_DBF_TEXT(2, setup, "ichalloc");
	क्रम (cnt = 0; cnt < LCS_NUM_BUFFS; cnt++) अणु
		/* alloc memory fo iobuffer */
		channel->iob[cnt].data =
			kzalloc(LCS_IOBUFFERSIZE, GFP_DMA | GFP_KERNEL);
		अगर (channel->iob[cnt].data == शून्य)
			अवरोध;
		channel->iob[cnt].state = LCS_BUF_STATE_EMPTY;
	पूर्ण
	अगर (cnt < LCS_NUM_BUFFS) अणु
		/* Not all io buffers could be allocated. */
		LCS_DBF_TEXT(2, setup, "echalloc");
		जबतक (cnt-- > 0)
			kमुक्त(channel->iob[cnt].data);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * Free io buffers.
 */
अटल व्योम
lcs_मुक्त_channel(काष्ठा lcs_channel *channel)
अणु
	पूर्णांक cnt;

	LCS_DBF_TEXT(2, setup, "ichfree");
	क्रम (cnt = 0; cnt < LCS_NUM_BUFFS; cnt++) अणु
		kमुक्त(channel->iob[cnt].data);
		channel->iob[cnt].data = शून्य;
	पूर्ण
पूर्ण

/*
 * Cleanup channel.
 */
अटल व्योम
lcs_cleanup_channel(काष्ठा lcs_channel *channel)
अणु
	LCS_DBF_TEXT(3, setup, "cleanch");
	/* Kill ग_लिखो channel tasklets. */
	tasklet_समाप्त(&channel->irq_tasklet);
	/* Free channel buffers. */
	lcs_मुक्त_channel(channel);
पूर्ण

/**
 * LCS मुक्त memory क्रम card and channels.
 */
अटल व्योम
lcs_मुक्त_card(काष्ठा lcs_card *card)
अणु
	LCS_DBF_TEXT(2, setup, "remcard");
	LCS_DBF_HEX(2, setup, &card, माप(व्योम*));
	kमुक्त(card);
पूर्ण

/**
 * LCS alloc memory क्रम card and channels
 */
अटल काष्ठा lcs_card *
lcs_alloc_card(व्योम)
अणु
	काष्ठा lcs_card *card;
	पूर्णांक rc;

	LCS_DBF_TEXT(2, setup, "alloclcs");

	card = kzalloc(माप(काष्ठा lcs_card), GFP_KERNEL | GFP_DMA);
	अगर (card == शून्य)
		वापस शून्य;
	card->lan_type = LCS_FRAME_TYPE_AUTO;
	card->pkt_seq = 0;
	card->lancmd_समयout = LCS_LANCMD_TIMEOUT_DEFAULT;
	/* Allocate io buffers क्रम the पढ़ो channel. */
	rc = lcs_alloc_channel(&card->पढ़ो);
	अगर (rc)अणु
		LCS_DBF_TEXT(2, setup, "iccwerr");
		lcs_मुक्त_card(card);
		वापस शून्य;
	पूर्ण
	/* Allocate io buffers क्रम the ग_लिखो channel. */
	rc = lcs_alloc_channel(&card->ग_लिखो);
	अगर (rc) अणु
		LCS_DBF_TEXT(2, setup, "iccwerr");
		lcs_cleanup_channel(&card->पढ़ो);
		lcs_मुक्त_card(card);
		वापस शून्य;
	पूर्ण

#अगर_घोषित CONFIG_IP_MULTICAST
	INIT_LIST_HEAD(&card->ipm_list);
#पूर्ण_अगर
	LCS_DBF_HEX(2, setup, &card, माप(व्योम*));
	वापस card;
पूर्ण

/*
 * Setup पढ़ो channel.
 */
अटल व्योम
lcs_setup_पढ़ो_ccws(काष्ठा lcs_card *card)
अणु
	पूर्णांक cnt;

	LCS_DBF_TEXT(2, setup, "ireadccw");
	/* Setup पढ़ो ccws. */
	स_रखो(card->पढ़ो.ccws, 0, माप (काष्ठा ccw1) * (LCS_NUM_BUFFS + 1));
	क्रम (cnt = 0; cnt < LCS_NUM_BUFFS; cnt++) अणु
		card->पढ़ो.ccws[cnt].cmd_code = LCS_CCW_READ;
		card->पढ़ो.ccws[cnt].count = LCS_IOBUFFERSIZE;
		card->पढ़ो.ccws[cnt].flags =
			CCW_FLAG_CC | CCW_FLAG_SLI | CCW_FLAG_PCI;
		/*
		 * Note: we have allocated the buffer with GFP_DMA, so
		 * we करो not need to करो set_normalized_cda.
		 */
		card->पढ़ो.ccws[cnt].cda =
			(__u32) __pa(card->पढ़ो.iob[cnt].data);
		((काष्ठा lcs_header *)
		 card->पढ़ो.iob[cnt].data)->offset = LCS_ILLEGAL_OFFSET;
		card->पढ़ो.iob[cnt].callback = lcs_get_frames_cb;
		card->पढ़ो.iob[cnt].state = LCS_BUF_STATE_READY;
		card->पढ़ो.iob[cnt].count = LCS_IOBUFFERSIZE;
	पूर्ण
	card->पढ़ो.ccws[0].flags &= ~CCW_FLAG_PCI;
	card->पढ़ो.ccws[LCS_NUM_BUFFS - 1].flags &= ~CCW_FLAG_PCI;
	card->पढ़ो.ccws[LCS_NUM_BUFFS - 1].flags |= CCW_FLAG_SUSPEND;
	/* Last ccw is a tic (transfer in channel). */
	card->पढ़ो.ccws[LCS_NUM_BUFFS].cmd_code = LCS_CCW_TRANSFER;
	card->पढ़ो.ccws[LCS_NUM_BUFFS].cda =
		(__u32) __pa(card->पढ़ो.ccws);
	/* Setg initial state of the पढ़ो channel. */
	card->पढ़ो.state = LCS_CH_STATE_INIT;

	card->पढ़ो.io_idx = 0;
	card->पढ़ो.buf_idx = 0;
पूर्ण

अटल व्योम
lcs_setup_पढ़ो(काष्ठा lcs_card *card)
अणु
	LCS_DBF_TEXT(3, setup, "initread");

	lcs_setup_पढ़ो_ccws(card);
	/* Initialize पढ़ो channel tasklet. */
	card->पढ़ो.irq_tasklet.data = (अचिन्हित दीर्घ) &card->पढ़ो;
	card->पढ़ो.irq_tasklet.func = lcs_tasklet;
	/* Initialize रुकोqueue. */
	init_रुकोqueue_head(&card->पढ़ो.रुको_q);
पूर्ण

/*
 * Setup ग_लिखो channel.
 */
अटल व्योम
lcs_setup_ग_लिखो_ccws(काष्ठा lcs_card *card)
अणु
	पूर्णांक cnt;

	LCS_DBF_TEXT(3, setup, "iwritccw");
	/* Setup ग_लिखो ccws. */
	स_रखो(card->ग_लिखो.ccws, 0, माप(काष्ठा ccw1) * (LCS_NUM_BUFFS + 1));
	क्रम (cnt = 0; cnt < LCS_NUM_BUFFS; cnt++) अणु
		card->ग_लिखो.ccws[cnt].cmd_code = LCS_CCW_WRITE;
		card->ग_लिखो.ccws[cnt].count = 0;
		card->ग_लिखो.ccws[cnt].flags =
			CCW_FLAG_SUSPEND | CCW_FLAG_CC | CCW_FLAG_SLI;
		/*
		 * Note: we have allocated the buffer with GFP_DMA, so
		 * we करो not need to करो set_normalized_cda.
		 */
		card->ग_लिखो.ccws[cnt].cda =
			(__u32) __pa(card->ग_लिखो.iob[cnt].data);
	पूर्ण
	/* Last ccw is a tic (transfer in channel). */
	card->ग_लिखो.ccws[LCS_NUM_BUFFS].cmd_code = LCS_CCW_TRANSFER;
	card->ग_लिखो.ccws[LCS_NUM_BUFFS].cda =
		(__u32) __pa(card->ग_लिखो.ccws);
	/* Set initial state of the ग_लिखो channel. */
	card->पढ़ो.state = LCS_CH_STATE_INIT;

	card->ग_लिखो.io_idx = 0;
	card->ग_लिखो.buf_idx = 0;
पूर्ण

अटल व्योम
lcs_setup_ग_लिखो(काष्ठा lcs_card *card)
अणु
	LCS_DBF_TEXT(3, setup, "initwrit");

	lcs_setup_ग_लिखो_ccws(card);
	/* Initialize ग_लिखो channel tasklet. */
	card->ग_लिखो.irq_tasklet.data = (अचिन्हित दीर्घ) &card->ग_लिखो;
	card->ग_लिखो.irq_tasklet.func = lcs_tasklet;
	/* Initialize रुकोqueue. */
	init_रुकोqueue_head(&card->ग_लिखो.रुको_q);
पूर्ण

अटल व्योम
lcs_set_allowed_thपढ़ोs(काष्ठा lcs_card *card, अचिन्हित दीर्घ thपढ़ोs)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->mask_lock, flags);
	card->thपढ़ो_allowed_mask = thपढ़ोs;
	spin_unlock_irqrestore(&card->mask_lock, flags);
	wake_up(&card->रुको_q);
पूर्ण
अटल पूर्णांक lcs_thपढ़ोs_running(काष्ठा lcs_card *card, अचिन्हित दीर्घ thपढ़ोs)
अणु
        अचिन्हित दीर्घ flags;
        पूर्णांक rc = 0;

	spin_lock_irqsave(&card->mask_lock, flags);
        rc = (card->thपढ़ो_running_mask & thपढ़ोs);
	spin_unlock_irqrestore(&card->mask_lock, flags);
        वापस rc;
पूर्ण

अटल पूर्णांक
lcs_रुको_क्रम_thपढ़ोs(काष्ठा lcs_card *card, अचिन्हित दीर्घ thपढ़ोs)
अणु
        वापस रुको_event_पूर्णांकerruptible(card->रुको_q,
                        lcs_thपढ़ोs_running(card, thपढ़ोs) == 0);
पूर्ण

अटल पूर्णांक lcs_set_thपढ़ो_start_bit(काष्ठा lcs_card *card, अचिन्हित दीर्घ thपढ़ो)
अणु
        अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->mask_lock, flags);
        अगर ( !(card->thपढ़ो_allowed_mask & thपढ़ो) ||
              (card->thपढ़ो_start_mask & thपढ़ो) ) अणु
                spin_unlock_irqrestore(&card->mask_lock, flags);
                वापस -EPERM;
        पूर्ण
        card->thपढ़ो_start_mask |= thपढ़ो;
	spin_unlock_irqrestore(&card->mask_lock, flags);
        वापस 0;
पूर्ण

अटल व्योम
lcs_clear_thपढ़ो_running_bit(काष्ठा lcs_card *card, अचिन्हित दीर्घ thपढ़ो)
अणु
        अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->mask_lock, flags);
        card->thपढ़ो_running_mask &= ~thपढ़ो;
	spin_unlock_irqrestore(&card->mask_lock, flags);
        wake_up(&card->रुको_q);
पूर्ण

अटल पूर्णांक __lcs_करो_run_thपढ़ो(काष्ठा lcs_card *card, अचिन्हित दीर्घ thपढ़ो)
अणु
        अचिन्हित दीर्घ flags;
        पूर्णांक rc = 0;

	spin_lock_irqsave(&card->mask_lock, flags);
        अगर (card->thपढ़ो_start_mask & thपढ़ो)अणु
                अगर ((card->thपढ़ो_allowed_mask & thपढ़ो) &&
                    !(card->thपढ़ो_running_mask & thपढ़ो))अणु
                        rc = 1;
                        card->thपढ़ो_start_mask &= ~thपढ़ो;
                        card->thपढ़ो_running_mask |= thपढ़ो;
                पूर्ण अन्यथा
                        rc = -EPERM;
        पूर्ण
	spin_unlock_irqrestore(&card->mask_lock, flags);
        वापस rc;
पूर्ण

अटल पूर्णांक
lcs_करो_run_thपढ़ो(काष्ठा lcs_card *card, अचिन्हित दीर्घ thपढ़ो)
अणु
        पूर्णांक rc = 0;
        रुको_event(card->रुको_q,
                   (rc = __lcs_करो_run_thपढ़ो(card, thपढ़ो)) >= 0);
        वापस rc;
पूर्ण

अटल पूर्णांक
lcs_करो_start_thपढ़ो(काष्ठा lcs_card *card, अचिन्हित दीर्घ thपढ़ो)
अणु
        अचिन्हित दीर्घ flags;
        पूर्णांक rc = 0;

	spin_lock_irqsave(&card->mask_lock, flags);
        LCS_DBF_TEXT_(4, trace, "  %02x%02x%02x",
                        (u8) card->thपढ़ो_start_mask,
                        (u8) card->thपढ़ो_allowed_mask,
                        (u8) card->thपढ़ो_running_mask);
        rc = (card->thपढ़ो_start_mask & thपढ़ो);
	spin_unlock_irqrestore(&card->mask_lock, flags);
        वापस rc;
पूर्ण

/**
 * Initialize channels,card and state machines.
 */
अटल व्योम
lcs_setup_card(काष्ठा lcs_card *card)
अणु
	LCS_DBF_TEXT(2, setup, "initcard");
	LCS_DBF_HEX(2, setup, &card, माप(व्योम*));

	lcs_setup_पढ़ो(card);
	lcs_setup_ग_लिखो(card);
	/* Set cards initial state. */
	card->state = DEV_STATE_DOWN;
	card->tx_buffer = शून्य;
	card->tx_emitted = 0;

	init_रुकोqueue_head(&card->रुको_q);
	spin_lock_init(&card->lock);
	spin_lock_init(&card->ipm_lock);
	spin_lock_init(&card->mask_lock);
#अगर_घोषित CONFIG_IP_MULTICAST
	INIT_LIST_HEAD(&card->ipm_list);
#पूर्ण_अगर
	INIT_LIST_HEAD(&card->lancmd_रुकोers);
पूर्ण

अटल व्योम lcs_clear_multicast_list(काष्ठा lcs_card *card)
अणु
#अगर_घोषित	CONFIG_IP_MULTICAST
	काष्ठा lcs_ipm_list *ipm;
	अचिन्हित दीर्घ flags;

	/* Free multicast list. */
	LCS_DBF_TEXT(3, setup, "clmclist");
	spin_lock_irqsave(&card->ipm_lock, flags);
	जबतक (!list_empty(&card->ipm_list))अणु
		ipm = list_entry(card->ipm_list.next,
				 काष्ठा lcs_ipm_list, list);
		list_del(&ipm->list);
		अगर (ipm->ipm_state != LCS_IPM_STATE_SET_REQUIRED)अणु
			spin_unlock_irqrestore(&card->ipm_lock, flags);
			lcs_send_delipm(card, ipm);
			spin_lock_irqsave(&card->ipm_lock, flags);
		पूर्ण
		kमुक्त(ipm);
	पूर्ण
	spin_unlock_irqrestore(&card->ipm_lock, flags);
#पूर्ण_अगर
पूर्ण
/**
 * Cleanup channels,card and state machines.
 */
अटल व्योम
lcs_cleanup_card(काष्ठा lcs_card *card)
अणु

	LCS_DBF_TEXT(3, setup, "cleancrd");
	LCS_DBF_HEX(2,setup,&card,माप(व्योम*));

	अगर (card->dev != शून्य)
		मुक्त_netdev(card->dev);
	/* Cleanup channels. */
	lcs_cleanup_channel(&card->ग_लिखो);
	lcs_cleanup_channel(&card->पढ़ो);
पूर्ण

/**
 * Start channel.
 */
अटल पूर्णांक
lcs_start_channel(काष्ठा lcs_channel *channel)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	LCS_DBF_TEXT_(4, trace,"ssch%s", dev_name(&channel->ccwdev->dev));
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	rc = ccw_device_start(channel->ccwdev,
			      channel->ccws + channel->io_idx, 0, 0,
			      DOIO_DENY_PREFETCH | DOIO_ALLOW_SUSPEND);
	अगर (rc == 0)
		channel->state = LCS_CH_STATE_RUNNING;
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
	अगर (rc) अणु
		LCS_DBF_TEXT_(4,trace,"essh%s",
			      dev_name(&channel->ccwdev->dev));
		dev_err(&channel->ccwdev->dev,
			"Starting an LCS device resulted in an error,"
			" rc=%d!\n", rc);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक
lcs_clear_channel(काष्ठा lcs_channel *channel)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	LCS_DBF_TEXT(4,trace,"clearch");
	LCS_DBF_TEXT_(4, trace, "%s", dev_name(&channel->ccwdev->dev));
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	rc = ccw_device_clear(channel->ccwdev, 0);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
	अगर (rc) अणु
		LCS_DBF_TEXT_(4, trace, "ecsc%s",
			      dev_name(&channel->ccwdev->dev));
		वापस rc;
	पूर्ण
	रुको_event(channel->रुको_q, (channel->state == LCS_CH_STATE_CLEARED));
	channel->state = LCS_CH_STATE_STOPPED;
	वापस rc;
पूर्ण


/**
 * Stop channel.
 */
अटल पूर्णांक
lcs_stop_channel(काष्ठा lcs_channel *channel)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	अगर (channel->state == LCS_CH_STATE_STOPPED)
		वापस 0;
	LCS_DBF_TEXT(4,trace,"haltsch");
	LCS_DBF_TEXT_(4, trace, "%s", dev_name(&channel->ccwdev->dev));
	channel->state = LCS_CH_STATE_INIT;
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	rc = ccw_device_halt(channel->ccwdev, 0);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
	अगर (rc) अणु
		LCS_DBF_TEXT_(4, trace, "ehsc%s",
			      dev_name(&channel->ccwdev->dev));
		वापस rc;
	पूर्ण
	/* Asynchronous halt initialted. Wait क्रम its completion. */
	रुको_event(channel->रुको_q, (channel->state == LCS_CH_STATE_HALTED));
	lcs_clear_channel(channel);
	वापस 0;
पूर्ण

/**
 * start पढ़ो and ग_लिखो channel
 */
अटल पूर्णांक
lcs_start_channels(काष्ठा lcs_card *card)
अणु
	पूर्णांक rc;

	LCS_DBF_TEXT(2, trace, "chstart");
	/* start पढ़ो channel */
	rc = lcs_start_channel(&card->पढ़ो);
	अगर (rc)
		वापस rc;
	/* start ग_लिखो channel */
	rc = lcs_start_channel(&card->ग_लिखो);
	अगर (rc)
		lcs_stop_channel(&card->पढ़ो);
	वापस rc;
पूर्ण

/**
 * stop पढ़ो and ग_लिखो channel
 */
अटल पूर्णांक
lcs_stop_channels(काष्ठा lcs_card *card)
अणु
	LCS_DBF_TEXT(2, trace, "chhalt");
	lcs_stop_channel(&card->पढ़ो);
	lcs_stop_channel(&card->ग_लिखो);
	वापस 0;
पूर्ण

/**
 * Get empty buffer.
 */
अटल काष्ठा lcs_buffer *
__lcs_get_buffer(काष्ठा lcs_channel *channel)
अणु
	पूर्णांक index;

	LCS_DBF_TEXT(5, trace, "_getbuff");
	index = channel->io_idx;
	करो अणु
		अगर (channel->iob[index].state == LCS_BUF_STATE_EMPTY) अणु
			channel->iob[index].state = LCS_BUF_STATE_LOCKED;
			वापस channel->iob + index;
		पूर्ण
		index = (index + 1) & (LCS_NUM_BUFFS - 1);
	पूर्ण जबतक (index != channel->io_idx);
	वापस शून्य;
पूर्ण

अटल काष्ठा lcs_buffer *
lcs_get_buffer(काष्ठा lcs_channel *channel)
अणु
	काष्ठा lcs_buffer *buffer;
	अचिन्हित दीर्घ flags;

	LCS_DBF_TEXT(5, trace, "getbuff");
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	buffer = __lcs_get_buffer(channel);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
	वापस buffer;
पूर्ण

/**
 * Resume channel program अगर the channel is suspended.
 */
अटल पूर्णांक
__lcs_resume_channel(काष्ठा lcs_channel *channel)
अणु
	पूर्णांक rc;

	अगर (channel->state != LCS_CH_STATE_SUSPENDED)
		वापस 0;
	अगर (channel->ccws[channel->io_idx].flags & CCW_FLAG_SUSPEND)
		वापस 0;
	LCS_DBF_TEXT_(5, trace, "rsch%s", dev_name(&channel->ccwdev->dev));
	rc = ccw_device_resume(channel->ccwdev);
	अगर (rc) अणु
		LCS_DBF_TEXT_(4, trace, "ersc%s",
			      dev_name(&channel->ccwdev->dev));
		dev_err(&channel->ccwdev->dev,
			"Sending data from the LCS device to the LAN failed"
			" with rc=%d\n",rc);
	पूर्ण अन्यथा
		channel->state = LCS_CH_STATE_RUNNING;
	वापस rc;

पूर्ण

/**
 * Make a buffer पढ़ोy क्रम processing.
 */
अटल व्योम __lcs_पढ़ोy_buffer_bits(काष्ठा lcs_channel *channel, पूर्णांक index)
अणु
	पूर्णांक prev, next;

	LCS_DBF_TEXT(5, trace, "rdybits");
	prev = (index - 1) & (LCS_NUM_BUFFS - 1);
	next = (index + 1) & (LCS_NUM_BUFFS - 1);
	/* Check अगर we may clear the suspend bit of this buffer. */
	अगर (channel->ccws[next].flags & CCW_FLAG_SUSPEND) अणु
		/* Check अगर we have to set the PCI bit. */
		अगर (!(channel->ccws[prev].flags & CCW_FLAG_SUSPEND))
			/* Suspend bit of the previous buffer is not set. */
			channel->ccws[index].flags |= CCW_FLAG_PCI;
		/* Suspend bit of the next buffer is set. */
		channel->ccws[index].flags &= ~CCW_FLAG_SUSPEND;
	पूर्ण
पूर्ण

अटल पूर्णांक
lcs_पढ़ोy_buffer(काष्ठा lcs_channel *channel, काष्ठा lcs_buffer *buffer)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक index, rc;

	LCS_DBF_TEXT(5, trace, "rdybuff");
	BUG_ON(buffer->state != LCS_BUF_STATE_LOCKED &&
	       buffer->state != LCS_BUF_STATE_PROCESSED);
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	buffer->state = LCS_BUF_STATE_READY;
	index = buffer - channel->iob;
	/* Set length. */
	channel->ccws[index].count = buffer->count;
	/* Check relevant PCI/suspend bits. */
	__lcs_पढ़ोy_buffer_bits(channel, index);
	rc = __lcs_resume_channel(channel);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
	वापस rc;
पूर्ण

/**
 * Mark the buffer as processed. Take care of the suspend bit
 * of the previous buffer. This function is called from
 * पूर्णांकerrupt context, so the lock must not be taken.
 */
अटल पूर्णांक
__lcs_processed_buffer(काष्ठा lcs_channel *channel, काष्ठा lcs_buffer *buffer)
अणु
	पूर्णांक index, prev, next;

	LCS_DBF_TEXT(5, trace, "prcsbuff");
	BUG_ON(buffer->state != LCS_BUF_STATE_READY);
	buffer->state = LCS_BUF_STATE_PROCESSED;
	index = buffer - channel->iob;
	prev = (index - 1) & (LCS_NUM_BUFFS - 1);
	next = (index + 1) & (LCS_NUM_BUFFS - 1);
	/* Set the suspend bit and clear the PCI bit of this buffer. */
	channel->ccws[index].flags |= CCW_FLAG_SUSPEND;
	channel->ccws[index].flags &= ~CCW_FLAG_PCI;
	/* Check the suspend bit of the previous buffer. */
	अगर (channel->iob[prev].state == LCS_BUF_STATE_READY) अणु
		/*
		 * Previous buffer is in state पढ़ोy. It might have
		 * happened in lcs_पढ़ोy_buffer that the suspend bit
		 * has not been cleared to aव्योम an endless loop.
		 * Do it now.
		 */
		__lcs_पढ़ोy_buffer_bits(channel, prev);
	पूर्ण
	/* Clear PCI bit of next buffer. */
	channel->ccws[next].flags &= ~CCW_FLAG_PCI;
	वापस __lcs_resume_channel(channel);
पूर्ण

/**
 * Put a processed buffer back to state empty.
 */
अटल व्योम
lcs_release_buffer(काष्ठा lcs_channel *channel, काष्ठा lcs_buffer *buffer)
अणु
	अचिन्हित दीर्घ flags;

	LCS_DBF_TEXT(5, trace, "relbuff");
	BUG_ON(buffer->state != LCS_BUF_STATE_LOCKED &&
	       buffer->state != LCS_BUF_STATE_PROCESSED);
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	buffer->state = LCS_BUF_STATE_EMPTY;
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
पूर्ण

/**
 * Get buffer क्रम a lan command.
 */
अटल काष्ठा lcs_buffer *
lcs_get_lancmd(काष्ठा lcs_card *card, पूर्णांक count)
अणु
	काष्ठा lcs_buffer *buffer;
	काष्ठा lcs_cmd *cmd;

	LCS_DBF_TEXT(4, trace, "getlncmd");
	/* Get buffer and रुको अगर none is available. */
	रुको_event(card->ग_लिखो.रुको_q,
		   ((buffer = lcs_get_buffer(&card->ग_लिखो)) != शून्य));
	count += माप(काष्ठा lcs_header);
	*(__u16 *)(buffer->data + count) = 0;
	buffer->count = count + माप(__u16);
	buffer->callback = lcs_release_buffer;
	cmd = (काष्ठा lcs_cmd *) buffer->data;
	cmd->offset = count;
	cmd->type = LCS_FRAME_TYPE_CONTROL;
	cmd->slot = 0;
	वापस buffer;
पूर्ण


अटल व्योम
lcs_get_reply(काष्ठा lcs_reply *reply)
अणु
	refcount_inc(&reply->refcnt);
पूर्ण

अटल व्योम
lcs_put_reply(काष्ठा lcs_reply *reply)
अणु
	अगर (refcount_dec_and_test(&reply->refcnt))
		kमुक्त(reply);
पूर्ण

अटल काष्ठा lcs_reply *
lcs_alloc_reply(काष्ठा lcs_cmd *cmd)
अणु
	काष्ठा lcs_reply *reply;

	LCS_DBF_TEXT(4, trace, "getreply");

	reply = kzalloc(माप(काष्ठा lcs_reply), GFP_ATOMIC);
	अगर (!reply)
		वापस शून्य;
	refcount_set(&reply->refcnt, 1);
	reply->sequence_no = cmd->sequence_no;
	reply->received = 0;
	reply->rc = 0;
	init_रुकोqueue_head(&reply->रुको_q);

	वापस reply;
पूर्ण

/**
 * Notअगरier function क्रम lancmd replies. Called from पढ़ो irq.
 */
अटल व्योम
lcs_notअगरy_lancmd_रुकोers(काष्ठा lcs_card *card, काष्ठा lcs_cmd *cmd)
अणु
	काष्ठा list_head *l, *n;
	काष्ठा lcs_reply *reply;

	LCS_DBF_TEXT(4, trace, "notiwait");
	spin_lock(&card->lock);
	list_क्रम_each_safe(l, n, &card->lancmd_रुकोers) अणु
		reply = list_entry(l, काष्ठा lcs_reply, list);
		अगर (reply->sequence_no == cmd->sequence_no) अणु
			lcs_get_reply(reply);
			list_del_init(&reply->list);
			अगर (reply->callback != शून्य)
				reply->callback(card, cmd);
			reply->received = 1;
			reply->rc = cmd->वापस_code;
			wake_up(&reply->रुको_q);
			lcs_put_reply(reply);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&card->lock);
पूर्ण

/**
 * Emit buffer of a lan command.
 */
अटल व्योम
lcs_lancmd_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा lcs_reply *reply = from_समयr(reply, t, समयr);
	काष्ठा lcs_reply *list_reply, *r;
	अचिन्हित दीर्घ flags;

	LCS_DBF_TEXT(4, trace, "timeout");
	spin_lock_irqsave(&reply->card->lock, flags);
	list_क्रम_each_entry_safe(list_reply, r,
				 &reply->card->lancmd_रुकोers,list) अणु
		अगर (reply == list_reply) अणु
			lcs_get_reply(reply);
			list_del_init(&reply->list);
			spin_unlock_irqrestore(&reply->card->lock, flags);
			reply->received = 1;
			reply->rc = -ETIME;
			wake_up(&reply->रुको_q);
			lcs_put_reply(reply);
			वापस;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&reply->card->lock, flags);
पूर्ण

अटल पूर्णांक
lcs_send_lancmd(काष्ठा lcs_card *card, काष्ठा lcs_buffer *buffer,
		व्योम (*reply_callback)(काष्ठा lcs_card *, काष्ठा lcs_cmd *))
अणु
	काष्ठा lcs_reply *reply;
	काष्ठा lcs_cmd *cmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	LCS_DBF_TEXT(4, trace, "sendcmd");
	cmd = (काष्ठा lcs_cmd *) buffer->data;
	cmd->वापस_code = 0;
	cmd->sequence_no = card->sequence_no++;
	reply = lcs_alloc_reply(cmd);
	अगर (!reply)
		वापस -ENOMEM;
	reply->callback = reply_callback;
	reply->card = card;
	spin_lock_irqsave(&card->lock, flags);
	list_add_tail(&reply->list, &card->lancmd_रुकोers);
	spin_unlock_irqrestore(&card->lock, flags);

	buffer->callback = lcs_release_buffer;
	rc = lcs_पढ़ोy_buffer(&card->ग_लिखो, buffer);
	अगर (rc)
		वापस rc;
	समयr_setup(&reply->समयr, lcs_lancmd_समयout, 0);
	mod_समयr(&reply->समयr, jअगरfies + HZ * card->lancmd_समयout);
	रुको_event(reply->रुको_q, reply->received);
	del_समयr_sync(&reply->समयr);
	LCS_DBF_TEXT_(4, trace, "rc:%d",reply->rc);
	rc = reply->rc;
	lcs_put_reply(reply);
	वापस rc ? -EIO : 0;
पूर्ण

/**
 * LCS startup command
 */
अटल पूर्णांक
lcs_send_startup(काष्ठा lcs_card *card, __u8 initiator)
अणु
	काष्ठा lcs_buffer *buffer;
	काष्ठा lcs_cmd *cmd;

	LCS_DBF_TEXT(2, trace, "startup");
	buffer = lcs_get_lancmd(card, LCS_STD_CMD_SIZE);
	cmd = (काष्ठा lcs_cmd *) buffer->data;
	cmd->cmd_code = LCS_CMD_STARTUP;
	cmd->initiator = initiator;
	cmd->cmd.lcs_startup.buff_size = LCS_IOBUFFERSIZE;
	वापस lcs_send_lancmd(card, buffer, शून्य);
पूर्ण

/**
 * LCS shutकरोwn command
 */
अटल पूर्णांक
lcs_send_shutकरोwn(काष्ठा lcs_card *card)
अणु
	काष्ठा lcs_buffer *buffer;
	काष्ठा lcs_cmd *cmd;

	LCS_DBF_TEXT(2, trace, "shutdown");
	buffer = lcs_get_lancmd(card, LCS_STD_CMD_SIZE);
	cmd = (काष्ठा lcs_cmd *) buffer->data;
	cmd->cmd_code = LCS_CMD_SHUTDOWN;
	cmd->initiator = LCS_INITIATOR_TCPIP;
	वापस lcs_send_lancmd(card, buffer, शून्य);
पूर्ण

/**
 * LCS lanstat command
 */
अटल व्योम
__lcs_lanstat_cb(काष्ठा lcs_card *card, काष्ठा lcs_cmd *cmd)
अणु
	LCS_DBF_TEXT(2, trace, "statcb");
	स_नकल(card->mac, cmd->cmd.lcs_lanstat_cmd.mac_addr, LCS_MAC_LENGTH);
पूर्ण

अटल पूर्णांक
lcs_send_lanstat(काष्ठा lcs_card *card)
अणु
	काष्ठा lcs_buffer *buffer;
	काष्ठा lcs_cmd *cmd;

	LCS_DBF_TEXT(2,trace, "cmdstat");
	buffer = lcs_get_lancmd(card, LCS_STD_CMD_SIZE);
	cmd = (काष्ठा lcs_cmd *) buffer->data;
	/* Setup lanstat command. */
	cmd->cmd_code = LCS_CMD_LANSTAT;
	cmd->initiator = LCS_INITIATOR_TCPIP;
	cmd->cmd.lcs_std_cmd.lan_type = card->lan_type;
	cmd->cmd.lcs_std_cmd.portno = card->portno;
	वापस lcs_send_lancmd(card, buffer, __lcs_lanstat_cb);
पूर्ण

/**
 * send stoplan command
 */
अटल पूर्णांक
lcs_send_stoplan(काष्ठा lcs_card *card, __u8 initiator)
अणु
	काष्ठा lcs_buffer *buffer;
	काष्ठा lcs_cmd *cmd;

	LCS_DBF_TEXT(2, trace, "cmdstpln");
	buffer = lcs_get_lancmd(card, LCS_STD_CMD_SIZE);
	cmd = (काष्ठा lcs_cmd *) buffer->data;
	cmd->cmd_code = LCS_CMD_STOPLAN;
	cmd->initiator = initiator;
	cmd->cmd.lcs_std_cmd.lan_type = card->lan_type;
	cmd->cmd.lcs_std_cmd.portno = card->portno;
	वापस lcs_send_lancmd(card, buffer, शून्य);
पूर्ण

/**
 * send startlan command
 */
अटल व्योम
__lcs_send_startlan_cb(काष्ठा lcs_card *card, काष्ठा lcs_cmd *cmd)
अणु
	LCS_DBF_TEXT(2, trace, "srtlancb");
	card->lan_type = cmd->cmd.lcs_std_cmd.lan_type;
	card->portno = cmd->cmd.lcs_std_cmd.portno;
पूर्ण

अटल पूर्णांक
lcs_send_startlan(काष्ठा lcs_card *card, __u8 initiator)
अणु
	काष्ठा lcs_buffer *buffer;
	काष्ठा lcs_cmd *cmd;

	LCS_DBF_TEXT(2, trace, "cmdstaln");
	buffer = lcs_get_lancmd(card, LCS_STD_CMD_SIZE);
	cmd = (काष्ठा lcs_cmd *) buffer->data;
	cmd->cmd_code = LCS_CMD_STARTLAN;
	cmd->initiator = initiator;
	cmd->cmd.lcs_std_cmd.lan_type = card->lan_type;
	cmd->cmd.lcs_std_cmd.portno = card->portno;
	वापस lcs_send_lancmd(card, buffer, __lcs_send_startlan_cb);
पूर्ण

#अगर_घोषित CONFIG_IP_MULTICAST
/**
 * send setipm command (Multicast)
 */
अटल पूर्णांक
lcs_send_setipm(काष्ठा lcs_card *card,काष्ठा lcs_ipm_list *ipm_list)
अणु
	काष्ठा lcs_buffer *buffer;
	काष्ठा lcs_cmd *cmd;

	LCS_DBF_TEXT(2, trace, "cmdsetim");
	buffer = lcs_get_lancmd(card, LCS_MULTICAST_CMD_SIZE);
	cmd = (काष्ठा lcs_cmd *) buffer->data;
	cmd->cmd_code = LCS_CMD_SETIPM;
	cmd->initiator = LCS_INITIATOR_TCPIP;
	cmd->cmd.lcs_qipassist.lan_type = card->lan_type;
	cmd->cmd.lcs_qipassist.portno = card->portno;
	cmd->cmd.lcs_qipassist.version = 4;
	cmd->cmd.lcs_qipassist.num_ip_pairs = 1;
	स_नकल(cmd->cmd.lcs_qipassist.lcs_ipass_ctlmsg.ip_mac_pair,
	       &ipm_list->ipm, माप (काष्ठा lcs_ip_mac_pair));
	LCS_DBF_TEXT_(2, trace, "%x",ipm_list->ipm.ip_addr);
	वापस lcs_send_lancmd(card, buffer, शून्य);
पूर्ण

/**
 * send delipm command (Multicast)
 */
अटल पूर्णांक
lcs_send_delipm(काष्ठा lcs_card *card,काष्ठा lcs_ipm_list *ipm_list)
अणु
	काष्ठा lcs_buffer *buffer;
	काष्ठा lcs_cmd *cmd;

	LCS_DBF_TEXT(2, trace, "cmddelim");
	buffer = lcs_get_lancmd(card, LCS_MULTICAST_CMD_SIZE);
	cmd = (काष्ठा lcs_cmd *) buffer->data;
	cmd->cmd_code = LCS_CMD_DELIPM;
	cmd->initiator = LCS_INITIATOR_TCPIP;
	cmd->cmd.lcs_qipassist.lan_type = card->lan_type;
	cmd->cmd.lcs_qipassist.portno = card->portno;
	cmd->cmd.lcs_qipassist.version = 4;
	cmd->cmd.lcs_qipassist.num_ip_pairs = 1;
	स_नकल(cmd->cmd.lcs_qipassist.lcs_ipass_ctlmsg.ip_mac_pair,
	       &ipm_list->ipm, माप (काष्ठा lcs_ip_mac_pair));
	LCS_DBF_TEXT_(2, trace, "%x",ipm_list->ipm.ip_addr);
	वापस lcs_send_lancmd(card, buffer, शून्य);
पूर्ण

/**
 * check अगर multicast is supported by LCS
 */
अटल व्योम
__lcs_check_multicast_cb(काष्ठा lcs_card *card, काष्ठा lcs_cmd *cmd)
अणु
	LCS_DBF_TEXT(2, trace, "chkmccb");
	card->ip_assists_supported =
		cmd->cmd.lcs_qipassist.ip_assists_supported;
	card->ip_assists_enabled =
		cmd->cmd.lcs_qipassist.ip_assists_enabled;
पूर्ण

अटल पूर्णांक
lcs_check_multicast_support(काष्ठा lcs_card *card)
अणु
	काष्ठा lcs_buffer *buffer;
	काष्ठा lcs_cmd *cmd;
	पूर्णांक rc;

	LCS_DBF_TEXT(2, trace, "cmdqipa");
	/* Send query ipassist. */
	buffer = lcs_get_lancmd(card, LCS_STD_CMD_SIZE);
	cmd = (काष्ठा lcs_cmd *) buffer->data;
	cmd->cmd_code = LCS_CMD_QIPASSIST;
	cmd->initiator = LCS_INITIATOR_TCPIP;
	cmd->cmd.lcs_qipassist.lan_type = card->lan_type;
	cmd->cmd.lcs_qipassist.portno = card->portno;
	cmd->cmd.lcs_qipassist.version = 4;
	cmd->cmd.lcs_qipassist.num_ip_pairs = 1;
	rc = lcs_send_lancmd(card, buffer, __lcs_check_multicast_cb);
	अगर (rc != 0) अणु
		pr_err("Query IPAssist failed. Assuming unsupported!\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (card->ip_assists_supported & LCS_IPASS_MULTICAST_SUPPORT)
		वापस 0;
	वापस -EOPNOTSUPP;
पूर्ण

/**
 * set or del multicast address on LCS card
 */
अटल व्योम
lcs_fix_multicast_list(काष्ठा lcs_card *card)
अणु
	काष्ठा list_head failed_list;
	काष्ठा lcs_ipm_list *ipm, *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	LCS_DBF_TEXT(4,trace, "fixipm");
	INIT_LIST_HEAD(&failed_list);
	spin_lock_irqsave(&card->ipm_lock, flags);
list_modअगरied:
	list_क्रम_each_entry_safe(ipm, पंचांगp, &card->ipm_list, list)अणु
		चयन (ipm->ipm_state) अणु
		हाल LCS_IPM_STATE_SET_REQUIRED:
			/* del from ipm_list so no one अन्यथा can tamper with
			 * this entry */
			list_del_init(&ipm->list);
			spin_unlock_irqrestore(&card->ipm_lock, flags);
			rc = lcs_send_setipm(card, ipm);
			spin_lock_irqsave(&card->ipm_lock, flags);
			अगर (rc) अणु
				pr_info("Adding multicast address failed."
					" Table possibly full!\n");
				/* store ipm in failed list -> will be added
				 * to ipm_list again, so a retry will be करोne
				 * during the next call of this function */
				list_add_tail(&ipm->list, &failed_list);
			पूर्ण अन्यथा अणु
				ipm->ipm_state = LCS_IPM_STATE_ON_CARD;
				/* re-insert पूर्णांकo ipm_list */
				list_add_tail(&ipm->list, &card->ipm_list);
			पूर्ण
			जाओ list_modअगरied;
		हाल LCS_IPM_STATE_DEL_REQUIRED:
			list_del(&ipm->list);
			spin_unlock_irqrestore(&card->ipm_lock, flags);
			lcs_send_delipm(card, ipm);
			spin_lock_irqsave(&card->ipm_lock, flags);
			kमुक्त(ipm);
			जाओ list_modअगरied;
		हाल LCS_IPM_STATE_ON_CARD:
			अवरोध;
		पूर्ण
	पूर्ण
	/* re-insert all entries from the failed_list पूर्णांकo ipm_list */
	list_क्रम_each_entry_safe(ipm, पंचांगp, &failed_list, list)
		list_move_tail(&ipm->list, &card->ipm_list);

	spin_unlock_irqrestore(&card->ipm_lock, flags);
पूर्ण

/**
 * get mac address क्रम the relevant Multicast address
 */
अटल व्योम
lcs_get_mac_क्रम_ipm(__be32 ipm, अक्षर *mac, काष्ठा net_device *dev)
अणु
	LCS_DBF_TEXT(4,trace, "getmac");
	ip_eth_mc_map(ipm, mac);
पूर्ण

/**
 * function called by net device to handle multicast address relevant things
 */
अटल व्योम lcs_हटाओ_mc_addresses(काष्ठा lcs_card *card,
				    काष्ठा in_device *in4_dev)
अणु
	काष्ठा ip_mc_list *im4;
	काष्ठा list_head *l;
	काष्ठा lcs_ipm_list *ipm;
	अचिन्हित दीर्घ flags;
	अक्षर buf[MAX_ADDR_LEN];

	LCS_DBF_TEXT(4, trace, "remmclst");
	spin_lock_irqsave(&card->ipm_lock, flags);
	list_क्रम_each(l, &card->ipm_list) अणु
		ipm = list_entry(l, काष्ठा lcs_ipm_list, list);
		क्रम (im4 = rcu_dereference(in4_dev->mc_list);
		     im4 != शून्य; im4 = rcu_dereference(im4->next_rcu)) अणु
			lcs_get_mac_क्रम_ipm(im4->multiaddr, buf, card->dev);
			अगर ( (ipm->ipm.ip_addr == im4->multiaddr) &&
			     (स_भेद(buf, &ipm->ipm.mac_addr,
				     LCS_MAC_LENGTH) == 0) )
				अवरोध;
		पूर्ण
		अगर (im4 == शून्य)
			ipm->ipm_state = LCS_IPM_STATE_DEL_REQUIRED;
	पूर्ण
	spin_unlock_irqrestore(&card->ipm_lock, flags);
पूर्ण

अटल काष्ठा lcs_ipm_list *lcs_check_addr_entry(काष्ठा lcs_card *card,
						 काष्ठा ip_mc_list *im4,
						 अक्षर *buf)
अणु
	काष्ठा lcs_ipm_list *पंचांगp, *ipm = शून्य;
	काष्ठा list_head *l;
	अचिन्हित दीर्घ flags;

	LCS_DBF_TEXT(4, trace, "chkmcent");
	spin_lock_irqsave(&card->ipm_lock, flags);
	list_क्रम_each(l, &card->ipm_list) अणु
		पंचांगp = list_entry(l, काष्ठा lcs_ipm_list, list);
		अगर ( (पंचांगp->ipm.ip_addr == im4->multiaddr) &&
		     (स_भेद(buf, &पंचांगp->ipm.mac_addr,
			     LCS_MAC_LENGTH) == 0) ) अणु
			ipm = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&card->ipm_lock, flags);
	वापस ipm;
पूर्ण

अटल व्योम lcs_set_mc_addresses(काष्ठा lcs_card *card,
				 काष्ठा in_device *in4_dev)
अणु

	काष्ठा ip_mc_list *im4;
	काष्ठा lcs_ipm_list *ipm;
	अक्षर buf[MAX_ADDR_LEN];
	अचिन्हित दीर्घ flags;

	LCS_DBF_TEXT(4, trace, "setmclst");
	क्रम (im4 = rcu_dereference(in4_dev->mc_list); im4 != शून्य;
	     im4 = rcu_dereference(im4->next_rcu)) अणु
		lcs_get_mac_क्रम_ipm(im4->multiaddr, buf, card->dev);
		ipm = lcs_check_addr_entry(card, im4, buf);
		अगर (ipm != शून्य)
			जारी;	/* Address alपढ़ोy in list. */
		ipm = kzalloc(माप(काष्ठा lcs_ipm_list), GFP_ATOMIC);
		अगर (ipm == शून्य) अणु
			pr_info("Not enough memory to add"
				" new multicast entry!\n");
			अवरोध;
		पूर्ण
		स_नकल(&ipm->ipm.mac_addr, buf, LCS_MAC_LENGTH);
		ipm->ipm.ip_addr = im4->multiaddr;
		ipm->ipm_state = LCS_IPM_STATE_SET_REQUIRED;
		spin_lock_irqsave(&card->ipm_lock, flags);
		LCS_DBF_HEX(2,trace,&ipm->ipm.ip_addr,4);
		list_add(&ipm->list, &card->ipm_list);
		spin_unlock_irqrestore(&card->ipm_lock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक
lcs_रेजिस्टर_mc_addresses(व्योम *data)
अणु
	काष्ठा lcs_card *card;
	काष्ठा in_device *in4_dev;

	card = (काष्ठा lcs_card *) data;

	अगर (!lcs_करो_run_thपढ़ो(card, LCS_SET_MC_THREAD))
		वापस 0;
	LCS_DBF_TEXT(4, trace, "regmulti");

	in4_dev = in_dev_get(card->dev);
	अगर (in4_dev == शून्य)
		जाओ out;
	rcu_पढ़ो_lock();
	lcs_हटाओ_mc_addresses(card,in4_dev);
	lcs_set_mc_addresses(card, in4_dev);
	rcu_पढ़ो_unlock();
	in_dev_put(in4_dev);

	netअगर_carrier_off(card->dev);
	netअगर_tx_disable(card->dev);
	रुको_event(card->ग_लिखो.रुको_q,
			(card->ग_लिखो.state != LCS_CH_STATE_RUNNING));
	lcs_fix_multicast_list(card);
	अगर (card->state == DEV_STATE_UP) अणु
		netअगर_carrier_on(card->dev);
		netअगर_wake_queue(card->dev);
	पूर्ण
out:
	lcs_clear_thपढ़ो_running_bit(card, LCS_SET_MC_THREAD);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_IP_MULTICAST */

/**
 * function called by net device to
 * handle multicast address relevant things
 */
अटल व्योम
lcs_set_multicast_list(काष्ठा net_device *dev)
अणु
#अगर_घोषित CONFIG_IP_MULTICAST
        काष्ठा lcs_card *card;

        LCS_DBF_TEXT(4, trace, "setmulti");
        card = (काष्ठा lcs_card *) dev->ml_priv;

        अगर (!lcs_set_thपढ़ो_start_bit(card, LCS_SET_MC_THREAD))
		schedule_work(&card->kernel_thपढ़ो_starter);
#पूर्ण_अगर /* CONFIG_IP_MULTICAST */
पूर्ण

अटल दीर्घ
lcs_check_irb_error(काष्ठा ccw_device *cdev, काष्ठा irb *irb)
अणु
	अगर (!IS_ERR(irb))
		वापस 0;

	चयन (PTR_ERR(irb)) अणु
	हाल -EIO:
		dev_warn(&cdev->dev,
			"An I/O-error occurred on the LCS device\n");
		LCS_DBF_TEXT(2, trace, "ckirberr");
		LCS_DBF_TEXT_(2, trace, "  rc%d", -EIO);
		अवरोध;
	हाल -ETIMEDOUT:
		dev_warn(&cdev->dev,
			"A command timed out on the LCS device\n");
		LCS_DBF_TEXT(2, trace, "ckirberr");
		LCS_DBF_TEXT_(2, trace, "  rc%d", -ETIMEDOUT);
		अवरोध;
	शेष:
		dev_warn(&cdev->dev,
			"An error occurred on the LCS device, rc=%ld\n",
			PTR_ERR(irb));
		LCS_DBF_TEXT(2, trace, "ckirberr");
		LCS_DBF_TEXT(2, trace, "  rc???");
	पूर्ण
	वापस PTR_ERR(irb);
पूर्ण

अटल पूर्णांक
lcs_get_problem(काष्ठा ccw_device *cdev, काष्ठा irb *irb)
अणु
	पूर्णांक dstat, cstat;
	अक्षर *sense;

	sense = (अक्षर *) irb->ecw;
	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;

	अगर (cstat & (SCHN_STAT_CHN_CTRL_CHK | SCHN_STAT_INTF_CTRL_CHK |
		     SCHN_STAT_CHN_DATA_CHK | SCHN_STAT_CHAIN_CHECK |
		     SCHN_STAT_PROT_CHECK   | SCHN_STAT_PROG_CHECK)) अणु
		LCS_DBF_TEXT(2, trace, "CGENCHK");
		वापस 1;
	पूर्ण
	अगर (dstat & DEV_STAT_UNIT_CHECK) अणु
		अगर (sense[LCS_SENSE_BYTE_1] &
		    LCS_SENSE_RESETTING_EVENT) अणु
			LCS_DBF_TEXT(2, trace, "REVIND");
			वापस 1;
		पूर्ण
		अगर (sense[LCS_SENSE_BYTE_0] &
		    LCS_SENSE_CMD_REJECT) अणु
			LCS_DBF_TEXT(2, trace, "CMDREJ");
			वापस 0;
		पूर्ण
		अगर ((!sense[LCS_SENSE_BYTE_0]) &&
		    (!sense[LCS_SENSE_BYTE_1]) &&
		    (!sense[LCS_SENSE_BYTE_2]) &&
		    (!sense[LCS_SENSE_BYTE_3])) अणु
			LCS_DBF_TEXT(2, trace, "ZEROSEN");
			वापस 0;
		पूर्ण
		LCS_DBF_TEXT(2, trace, "DGENCHK");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
lcs_schedule_recovery(काष्ठा lcs_card *card)
अणु
	LCS_DBF_TEXT(2, trace, "startrec");
	अगर (!lcs_set_thपढ़ो_start_bit(card, LCS_RECOVERY_THREAD))
		schedule_work(&card->kernel_thपढ़ो_starter);
पूर्ण

/**
 * IRQ Handler क्रम LCS channels
 */
अटल व्योम
lcs_irq(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ पूर्णांकparm, काष्ठा irb *irb)
अणु
	काष्ठा lcs_card *card;
	काष्ठा lcs_channel *channel;
	पूर्णांक rc, index;
	पूर्णांक cstat, dstat;

	अगर (lcs_check_irb_error(cdev, irb))
		वापस;

	card = CARD_FROM_DEV(cdev);
	अगर (card->पढ़ो.ccwdev == cdev)
		channel = &card->पढ़ो;
	अन्यथा
		channel = &card->ग_लिखो;

	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;
	LCS_DBF_TEXT_(5, trace, "Rint%s", dev_name(&cdev->dev));
	LCS_DBF_TEXT_(5, trace, "%4x%4x", irb->scsw.cmd.cstat,
		      irb->scsw.cmd.dstat);
	LCS_DBF_TEXT_(5, trace, "%4x%4x", irb->scsw.cmd.fctl,
		      irb->scsw.cmd.actl);

	/* Check क्रम channel and device errors presented */
	rc = lcs_get_problem(cdev, irb);
	अगर (rc || (dstat & DEV_STAT_UNIT_EXCEP)) अणु
		dev_warn(&cdev->dev,
			"The LCS device stopped because of an error,"
			" dstat=0x%X, cstat=0x%X \n",
			    dstat, cstat);
		अगर (rc) अणु
			channel->state = LCS_CH_STATE_ERROR;
		पूर्ण
	पूर्ण
	अगर (channel->state == LCS_CH_STATE_ERROR) अणु
		lcs_schedule_recovery(card);
		wake_up(&card->रुको_q);
		वापस;
	पूर्ण
	/* How far in the ccw chain have we processed? */
	अगर ((channel->state != LCS_CH_STATE_INIT) &&
	    (irb->scsw.cmd.fctl & SCSW_FCTL_START_FUNC) &&
	    (irb->scsw.cmd.cpa != 0)) अणु
		index = (काष्ठा ccw1 *) __va((addr_t) irb->scsw.cmd.cpa)
			- channel->ccws;
		अगर ((irb->scsw.cmd.actl & SCSW_ACTL_SUSPENDED) ||
		    (irb->scsw.cmd.cstat & SCHN_STAT_PCI))
			/* Bloody io subप्रणाली tells us lies about cpa... */
			index = (index - 1) & (LCS_NUM_BUFFS - 1);
		जबतक (channel->io_idx != index) अणु
			__lcs_processed_buffer(channel,
					       channel->iob + channel->io_idx);
			channel->io_idx =
				(channel->io_idx + 1) & (LCS_NUM_BUFFS - 1);
		पूर्ण
	पूर्ण

	अगर ((irb->scsw.cmd.dstat & DEV_STAT_DEV_END) ||
	    (irb->scsw.cmd.dstat & DEV_STAT_CHN_END) ||
	    (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK))
		/* Mark channel as stopped. */
		channel->state = LCS_CH_STATE_STOPPED;
	अन्यथा अगर (irb->scsw.cmd.actl & SCSW_ACTL_SUSPENDED)
		/* CCW execution stopped on a suspend bit. */
		channel->state = LCS_CH_STATE_SUSPENDED;
	अगर (irb->scsw.cmd.fctl & SCSW_FCTL_HALT_FUNC) अणु
		अगर (irb->scsw.cmd.cc != 0) अणु
			ccw_device_halt(channel->ccwdev, 0);
			वापस;
		पूर्ण
		/* The channel has been stopped by halt_IO. */
		channel->state = LCS_CH_STATE_HALTED;
	पूर्ण
	अगर (irb->scsw.cmd.fctl & SCSW_FCTL_CLEAR_FUNC)
		channel->state = LCS_CH_STATE_CLEARED;
	/* Do the rest in the tasklet. */
	tasklet_schedule(&channel->irq_tasklet);
पूर्ण

/**
 * Tasklet क्रम IRQ handler
 */
अटल व्योम
lcs_tasklet(अचिन्हित दीर्घ data)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा lcs_channel *channel;
	काष्ठा lcs_buffer *iob;
	पूर्णांक buf_idx;

	channel = (काष्ठा lcs_channel *) data;
	LCS_DBF_TEXT_(5, trace, "tlet%s", dev_name(&channel->ccwdev->dev));

	/* Check क्रम processed buffers. */
	iob = channel->iob;
	buf_idx = channel->buf_idx;
	जबतक (iob[buf_idx].state == LCS_BUF_STATE_PROCESSED) अणु
		/* Do the callback thing. */
		अगर (iob[buf_idx].callback != शून्य)
			iob[buf_idx].callback(channel, iob + buf_idx);
		buf_idx = (buf_idx + 1) & (LCS_NUM_BUFFS - 1);
	पूर्ण
	channel->buf_idx = buf_idx;

	अगर (channel->state == LCS_CH_STATE_STOPPED)
		lcs_start_channel(channel);
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	अगर (channel->state == LCS_CH_STATE_SUSPENDED &&
	    channel->iob[channel->io_idx].state == LCS_BUF_STATE_READY)
		__lcs_resume_channel(channel);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);

	/* Something happened on the channel. Wake up रुकोers. */
	wake_up(&channel->रुको_q);
पूर्ण

/**
 * Finish current tx buffer and make it पढ़ोy क्रम transmit.
 */
अटल व्योम
__lcs_emit_txbuffer(काष्ठा lcs_card *card)
अणु
	LCS_DBF_TEXT(5, trace, "emittx");
	*(__u16 *)(card->tx_buffer->data + card->tx_buffer->count) = 0;
	card->tx_buffer->count += 2;
	lcs_पढ़ोy_buffer(&card->ग_लिखो, card->tx_buffer);
	card->tx_buffer = शून्य;
	card->tx_emitted++;
पूर्ण

/**
 * Callback क्रम finished tx buffers.
 */
अटल व्योम
lcs_txbuffer_cb(काष्ठा lcs_channel *channel, काष्ठा lcs_buffer *buffer)
अणु
	काष्ठा lcs_card *card;

	LCS_DBF_TEXT(5, trace, "txbuffcb");
	/* Put buffer back to pool. */
	lcs_release_buffer(channel, buffer);
	card = container_of(channel, काष्ठा lcs_card, ग_लिखो);
	अगर (netअगर_queue_stopped(card->dev) && netअगर_carrier_ok(card->dev))
		netअगर_wake_queue(card->dev);
	spin_lock(&card->lock);
	card->tx_emitted--;
	अगर (card->tx_emitted <= 0 && card->tx_buffer != शून्य)
		/*
		 * Last running tx buffer has finished. Submit partially
		 * filled current buffer.
		 */
		__lcs_emit_txbuffer(card);
	spin_unlock(&card->lock);
पूर्ण

/**
 * Packet transmit function called by network stack
 */
अटल पूर्णांक
__lcs_start_xmit(काष्ठा lcs_card *card, काष्ठा sk_buff *skb,
		 काष्ठा net_device *dev)
अणु
	काष्ठा lcs_header *header;
	पूर्णांक rc = NETDEV_TX_OK;

	LCS_DBF_TEXT(5, trace, "hardxmit");
	अगर (skb == शून्य) अणु
		card->stats.tx_dropped++;
		card->stats.tx_errors++;
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (card->state != DEV_STATE_UP) अणु
		dev_kमुक्त_skb(skb);
		card->stats.tx_dropped++;
		card->stats.tx_errors++;
		card->stats.tx_carrier_errors++;
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	netअगर_stop_queue(card->dev);
	spin_lock(&card->lock);
	अगर (card->tx_buffer != शून्य &&
	    card->tx_buffer->count + माप(काष्ठा lcs_header) +
	    skb->len + माप(u16) > LCS_IOBUFFERSIZE)
		/* skb too big क्रम current tx buffer. */
		__lcs_emit_txbuffer(card);
	अगर (card->tx_buffer == शून्य) अणु
		/* Get new tx buffer */
		card->tx_buffer = lcs_get_buffer(&card->ग_लिखो);
		अगर (card->tx_buffer == शून्य) अणु
			card->stats.tx_dropped++;
			rc = NETDEV_TX_BUSY;
			जाओ out;
		पूर्ण
		card->tx_buffer->callback = lcs_txbuffer_cb;
		card->tx_buffer->count = 0;
	पूर्ण
	header = (काष्ठा lcs_header *)
		(card->tx_buffer->data + card->tx_buffer->count);
	card->tx_buffer->count += skb->len + माप(काष्ठा lcs_header);
	header->offset = card->tx_buffer->count;
	header->type = card->lan_type;
	header->slot = card->portno;
	skb_copy_from_linear_data(skb, header + 1, skb->len);
	spin_unlock(&card->lock);
	card->stats.tx_bytes += skb->len;
	card->stats.tx_packets++;
	dev_kमुक्त_skb(skb);
	netअगर_wake_queue(card->dev);
	spin_lock(&card->lock);
	अगर (card->tx_emitted <= 0 && card->tx_buffer != शून्य)
		/* If this is the first tx buffer emit it immediately. */
		__lcs_emit_txbuffer(card);
out:
	spin_unlock(&card->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक
lcs_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा lcs_card *card;
	पूर्णांक rc;

	LCS_DBF_TEXT(5, trace, "pktxmit");
	card = (काष्ठा lcs_card *) dev->ml_priv;
	rc = __lcs_start_xmit(card, skb, dev);
	वापस rc;
पूर्ण

/**
 * send startlan and lanstat command to make LCS device पढ़ोy
 */
अटल पूर्णांक
lcs_startlan_स्वतः(काष्ठा lcs_card *card)
अणु
	पूर्णांक rc;

	LCS_DBF_TEXT(2, trace, "strtauto");
#अगर_घोषित CONFIG_ETHERNET
	card->lan_type = LCS_FRAME_TYPE_ENET;
	rc = lcs_send_startlan(card, LCS_INITIATOR_TCPIP);
	अगर (rc == 0)
		वापस 0;

#पूर्ण_अगर
#अगर_घोषित CONFIG_FDDI
	card->lan_type = LCS_FRAME_TYPE_FDDI;
	rc = lcs_send_startlan(card, LCS_INITIATOR_TCPIP);
	अगर (rc == 0)
		वापस 0;
#पूर्ण_अगर
	वापस -EIO;
पूर्ण

अटल पूर्णांक
lcs_startlan(काष्ठा lcs_card *card)
अणु
	पूर्णांक rc, i;

	LCS_DBF_TEXT(2, trace, "startlan");
	rc = 0;
	अगर (card->portno != LCS_INVALID_PORT_NO) अणु
		अगर (card->lan_type == LCS_FRAME_TYPE_AUTO)
			rc = lcs_startlan_स्वतः(card);
		अन्यथा
			rc = lcs_send_startlan(card, LCS_INITIATOR_TCPIP);
	पूर्ण अन्यथा अणु
                क्रम (i = 0; i <= 16; i++) अणु
                        card->portno = i;
                        अगर (card->lan_type != LCS_FRAME_TYPE_AUTO)
                                rc = lcs_send_startlan(card,
                                                       LCS_INITIATOR_TCPIP);
                        अन्यथा
                                /* स्वतःdetecting lan type */
                                rc = lcs_startlan_स्वतः(card);
                        अगर (rc == 0)
                                अवरोध;
                पूर्ण
        पूर्ण
	अगर (rc == 0)
		वापस lcs_send_lanstat(card);
	वापस rc;
पूर्ण

/**
 * LCS detect function
 * setup channels and make them I/O पढ़ोy
 */
अटल पूर्णांक
lcs_detect(काष्ठा lcs_card *card)
अणु
	पूर्णांक rc = 0;

	LCS_DBF_TEXT(2, setup, "lcsdetct");
	/* start/reset card */
	अगर (card->dev)
		netअगर_stop_queue(card->dev);
	rc = lcs_stop_channels(card);
	अगर (rc == 0) अणु
		rc = lcs_start_channels(card);
		अगर (rc == 0) अणु
			rc = lcs_send_startup(card, LCS_INITIATOR_TCPIP);
			अगर (rc == 0)
				rc = lcs_startlan(card);
		पूर्ण
	पूर्ण
	अगर (rc == 0) अणु
		card->state = DEV_STATE_UP;
	पूर्ण अन्यथा अणु
		card->state = DEV_STATE_DOWN;
		card->ग_लिखो.state = LCS_CH_STATE_INIT;
		card->पढ़ो.state =  LCS_CH_STATE_INIT;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * LCS Stop card
 */
अटल पूर्णांक
lcs_stopcard(काष्ठा lcs_card *card)
अणु
	पूर्णांक rc;

	LCS_DBF_TEXT(3, setup, "stopcard");

	अगर (card->पढ़ो.state != LCS_CH_STATE_STOPPED &&
	    card->ग_लिखो.state != LCS_CH_STATE_STOPPED &&
	    card->पढ़ो.state != LCS_CH_STATE_ERROR &&
	    card->ग_लिखो.state != LCS_CH_STATE_ERROR &&
	    card->state == DEV_STATE_UP) अणु
		lcs_clear_multicast_list(card);
		rc = lcs_send_stoplan(card,LCS_INITIATOR_TCPIP);
		rc = lcs_send_shutकरोwn(card);
	पूर्ण
	rc = lcs_stop_channels(card);
	card->state = DEV_STATE_DOWN;

	वापस rc;
पूर्ण

/**
 * Kernel Thपढ़ो helper functions क्रम LGW initiated commands
 */
अटल व्योम
lcs_start_kernel_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lcs_card *card = container_of(work, काष्ठा lcs_card, kernel_thपढ़ो_starter);
	LCS_DBF_TEXT(5, trace, "krnthrd");
	अगर (lcs_करो_start_thपढ़ो(card, LCS_RECOVERY_THREAD))
		kthपढ़ो_run(lcs_recovery, card, "lcs_recover");
#अगर_घोषित CONFIG_IP_MULTICAST
	अगर (lcs_करो_start_thपढ़ो(card, LCS_SET_MC_THREAD))
		kthपढ़ो_run(lcs_रेजिस्टर_mc_addresses, card, "regipm");
#पूर्ण_अगर
पूर्ण

/**
 * Process control frames.
 */
अटल व्योम
lcs_get_control(काष्ठा lcs_card *card, काष्ठा lcs_cmd *cmd)
अणु
	LCS_DBF_TEXT(5, trace, "getctrl");
	अगर (cmd->initiator == LCS_INITIATOR_LGW) अणु
		चयन(cmd->cmd_code) अणु
		हाल LCS_CMD_STARTUP:
		हाल LCS_CMD_STARTLAN:
			lcs_schedule_recovery(card);
			अवरोध;
		हाल LCS_CMD_STOPLAN:
			pr_warn("Stoplan for %s initiated by LGW\n",
				card->dev->name);
			अगर (card->dev)
				netअगर_carrier_off(card->dev);
			अवरोध;
		शेष:
			LCS_DBF_TEXT(5, trace, "noLGWcmd");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		lcs_notअगरy_lancmd_रुकोers(card, cmd);
पूर्ण

/**
 * Unpack network packet.
 */
अटल व्योम
lcs_get_skb(काष्ठा lcs_card *card, अक्षर *skb_data, अचिन्हित पूर्णांक skb_len)
अणु
	काष्ठा sk_buff *skb;

	LCS_DBF_TEXT(5, trace, "getskb");
	अगर (card->dev == शून्य ||
	    card->state != DEV_STATE_UP)
		/* The card isn't up. Ignore the packet. */
		वापस;

	skb = dev_alloc_skb(skb_len);
	अगर (skb == शून्य) अणु
		dev_err(&card->dev->dev,
			" Allocating a socket buffer to interface %s failed\n",
			  card->dev->name);
		card->stats.rx_dropped++;
		वापस;
	पूर्ण
	skb_put_data(skb, skb_data, skb_len);
	skb->protocol =	card->lan_type_trans(skb, card->dev);
	card->stats.rx_bytes += skb_len;
	card->stats.rx_packets++;
	अगर (skb->protocol == htons(ETH_P_802_2))
		*((__u32 *)skb->cb) = ++card->pkt_seq;
	netअगर_rx(skb);
पूर्ण

/**
 * LCS मुख्य routine to get packets and lancmd replies from the buffers
 */
अटल व्योम
lcs_get_frames_cb(काष्ठा lcs_channel *channel, काष्ठा lcs_buffer *buffer)
अणु
	काष्ठा lcs_card *card;
	काष्ठा lcs_header *lcs_hdr;
	__u16 offset;

	LCS_DBF_TEXT(5, trace, "lcsgtpkt");
	lcs_hdr = (काष्ठा lcs_header *) buffer->data;
	अगर (lcs_hdr->offset == LCS_ILLEGAL_OFFSET) अणु
		LCS_DBF_TEXT(4, trace, "-eiogpkt");
		वापस;
	पूर्ण
	card = container_of(channel, काष्ठा lcs_card, पढ़ो);
	offset = 0;
	जबतक (lcs_hdr->offset != 0) अणु
		अगर (lcs_hdr->offset <= 0 ||
		    lcs_hdr->offset > LCS_IOBUFFERSIZE ||
		    lcs_hdr->offset < offset) अणु
			/* Offset invalid. */
			card->stats.rx_length_errors++;
			card->stats.rx_errors++;
			वापस;
		पूर्ण
		/* What kind of frame is it? */
		अगर (lcs_hdr->type == LCS_FRAME_TYPE_CONTROL)
			/* Control frame. */
			lcs_get_control(card, (काष्ठा lcs_cmd *) lcs_hdr);
		अन्यथा अगर (lcs_hdr->type == LCS_FRAME_TYPE_ENET ||
			 lcs_hdr->type == LCS_FRAME_TYPE_TR ||
			 lcs_hdr->type == LCS_FRAME_TYPE_FDDI)
			/* Normal network packet. */
			lcs_get_skb(card, (अक्षर *)(lcs_hdr + 1),
				    lcs_hdr->offset - offset -
				    माप(काष्ठा lcs_header));
		अन्यथा
			/* Unknown frame type. */
			; // FIXME: error message ?
		/* Proceed to next frame. */
		offset = lcs_hdr->offset;
		lcs_hdr->offset = LCS_ILLEGAL_OFFSET;
		lcs_hdr = (काष्ठा lcs_header *) (buffer->data + offset);
	पूर्ण
	/* The buffer is now empty. Make it पढ़ोy again. */
	lcs_पढ़ोy_buffer(&card->पढ़ो, buffer);
पूर्ण

/**
 * get network statistics क्रम अगरconfig and other user programs
 */
अटल काष्ठा net_device_stats *
lcs_माला_लोtats(काष्ठा net_device *dev)
अणु
	काष्ठा lcs_card *card;

	LCS_DBF_TEXT(4, trace, "netstats");
	card = (काष्ठा lcs_card *) dev->ml_priv;
	वापस &card->stats;
पूर्ण

/**
 * stop lcs device
 * This function will be called by user करोing अगरconfig xxx करोwn
 */
अटल पूर्णांक
lcs_stop_device(काष्ठा net_device *dev)
अणु
	काष्ठा lcs_card *card;
	पूर्णांक rc;

	LCS_DBF_TEXT(2, trace, "stopdev");
	card   = (काष्ठा lcs_card *) dev->ml_priv;
	netअगर_carrier_off(dev);
	netअगर_tx_disable(dev);
	dev->flags &= ~IFF_UP;
	रुको_event(card->ग_लिखो.रुको_q,
		(card->ग_लिखो.state != LCS_CH_STATE_RUNNING));
	rc = lcs_stopcard(card);
	अगर (rc)
		dev_err(&card->dev->dev,
			" Shutting down the LCS device failed\n");
	वापस rc;
पूर्ण

/**
 * start lcs device and make it runnable
 * This function will be called by user करोing अगरconfig xxx up
 */
अटल पूर्णांक
lcs_खोलो_device(काष्ठा net_device *dev)
अणु
	काष्ठा lcs_card *card;
	पूर्णांक rc;

	LCS_DBF_TEXT(2, trace, "opendev");
	card = (काष्ठा lcs_card *) dev->ml_priv;
	/* initialize statistics */
	rc = lcs_detect(card);
	अगर (rc) अणु
		pr_err("Error in opening device!\n");

	पूर्ण अन्यथा अणु
		dev->flags |= IFF_UP;
		netअगर_carrier_on(dev);
		netअगर_wake_queue(dev);
		card->state = DEV_STATE_UP;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * show function क्रम portno called by cat or similar things
 */
अटल sमाप_प्रकार
lcs_portno_show (काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
        काष्ठा lcs_card *card;

	card = dev_get_drvdata(dev);

        अगर (!card)
                वापस 0;

        वापस प्र_लिखो(buf, "%d\n", card->portno);
पूर्ण

/**
 * store the value which is piped to file portno
 */
अटल sमाप_प्रकार
lcs_portno_store (काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
        काष्ठा lcs_card *card;
	पूर्णांक rc;
	s16 value;

	card = dev_get_drvdata(dev);

        अगर (!card)
                वापस 0;

	rc = kstrtos16(buf, 0, &value);
	अगर (rc)
		वापस -EINVAL;
        /* TODO: sanity checks */
        card->portno = value;
	अगर (card->dev)
		card->dev->dev_port = card->portno;

        वापस count;

पूर्ण

अटल DEVICE_ATTR(portno, 0644, lcs_portno_show, lcs_portno_store);

अटल स्थिर अक्षर *lcs_type[] = अणु
	"not a channel",
	"2216 parallel",
	"2216 channel",
	"OSA LCS card",
	"unknown channel type",
	"unsupported channel type",
पूर्ण;

अटल sमाप_प्रकार
lcs_type_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ccwgroup_device *cgdev;

	cgdev = to_ccwgroupdev(dev);
	अगर (!cgdev)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%s\n", lcs_type[cgdev->cdev[0]->id.driver_info]);
पूर्ण

अटल DEVICE_ATTR(type, 0444, lcs_type_show, शून्य);

अटल sमाप_प्रकार
lcs_समयout_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lcs_card *card;

	card = dev_get_drvdata(dev);

	वापस card ? प्र_लिखो(buf, "%u\n", card->lancmd_समयout) : 0;
पूर्ण

अटल sमाप_प्रकार
lcs_समयout_store (काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
        काष्ठा lcs_card *card;
	अचिन्हित पूर्णांक value;
	पूर्णांक rc;

	card = dev_get_drvdata(dev);

        अगर (!card)
                वापस 0;

	rc = kstrtouपूर्णांक(buf, 0, &value);
	अगर (rc)
		वापस -EINVAL;
        /* TODO: sanity checks */
        card->lancmd_समयout = value;

        वापस count;

पूर्ण

अटल DEVICE_ATTR(lancmd_समयout, 0644, lcs_समयout_show, lcs_समयout_store);

अटल sमाप_प्रकार
lcs_dev_recover_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lcs_card *card = dev_get_drvdata(dev);
	अक्षर *पंचांगp;
	पूर्णांक i;

	अगर (!card)
		वापस -EINVAL;
	अगर (card->state != DEV_STATE_UP)
		वापस -EPERM;
	i = simple_म_से_अदीर्घ(buf, &पंचांगp, 16);
	अगर (i == 1)
		lcs_schedule_recovery(card);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(recover, 0200, शून्य, lcs_dev_recover_store);

अटल काष्ठा attribute * lcs_attrs[] = अणु
	&dev_attr_portno.attr,
	&dev_attr_type.attr,
	&dev_attr_lancmd_समयout.attr,
	&dev_attr_recover.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group lcs_attr_group = अणु
	.attrs = lcs_attrs,
पूर्ण;
अटल स्थिर काष्ठा attribute_group *lcs_attr_groups[] = अणु
	&lcs_attr_group,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा device_type lcs_devtype = अणु
	.name = "lcs",
	.groups = lcs_attr_groups,
पूर्ण;

/**
 * lcs_probe_device is called on establishing a new ccwgroup_device.
 */
अटल पूर्णांक
lcs_probe_device(काष्ठा ccwgroup_device *ccwgdev)
अणु
	काष्ठा lcs_card *card;

	अगर (!get_device(&ccwgdev->dev))
		वापस -ENODEV;

	LCS_DBF_TEXT(2, setup, "add_dev");
        card = lcs_alloc_card();
        अगर (!card) अणु
		LCS_DBF_TEXT_(2, setup, "  rc%d", -ENOMEM);
		put_device(&ccwgdev->dev);
                वापस -ENOMEM;
        पूर्ण
	dev_set_drvdata(&ccwgdev->dev, card);
	ccwgdev->cdev[0]->handler = lcs_irq;
	ccwgdev->cdev[1]->handler = lcs_irq;
	card->gdev = ccwgdev;
	INIT_WORK(&card->kernel_thपढ़ो_starter, lcs_start_kernel_thपढ़ो);
	card->thपढ़ो_start_mask = 0;
	card->thपढ़ो_allowed_mask = 0;
	card->thपढ़ो_running_mask = 0;
	ccwgdev->dev.type = &lcs_devtype;

	वापस 0;
पूर्ण

अटल पूर्णांक
lcs_रेजिस्टर_netdev(काष्ठा ccwgroup_device *ccwgdev)
अणु
	काष्ठा lcs_card *card;

	LCS_DBF_TEXT(2, setup, "regnetdv");
	card = dev_get_drvdata(&ccwgdev->dev);
	अगर (card->dev->reg_state != NETREG_UNINITIALIZED)
		वापस 0;
	SET_NETDEV_DEV(card->dev, &ccwgdev->dev);
	वापस रेजिस्टर_netdev(card->dev);
पूर्ण

/**
 * lcs_new_device will be called by setting the group device online.
 */
अटल स्थिर काष्ठा net_device_ops lcs_netdev_ops = अणु
	.nकरो_खोलो		= lcs_खोलो_device,
	.nकरो_stop		= lcs_stop_device,
	.nकरो_get_stats		= lcs_माला_लोtats,
	.nकरो_start_xmit		= lcs_start_xmit,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops lcs_mc_netdev_ops = अणु
	.nकरो_खोलो		= lcs_खोलो_device,
	.nकरो_stop		= lcs_stop_device,
	.nकरो_get_stats		= lcs_माला_लोtats,
	.nकरो_start_xmit		= lcs_start_xmit,
	.nकरो_set_rx_mode	= lcs_set_multicast_list,
पूर्ण;

अटल पूर्णांक
lcs_new_device(काष्ठा ccwgroup_device *ccwgdev)
अणु
	काष्ठा  lcs_card *card;
	काष्ठा net_device *dev=शून्य;
	क्रमागत lcs_dev_states recover_state;
	पूर्णांक rc;

	card = dev_get_drvdata(&ccwgdev->dev);
	अगर (!card)
		वापस -ENODEV;

	LCS_DBF_TEXT(2, setup, "newdev");
	LCS_DBF_HEX(3, setup, &card, माप(व्योम*));
	card->पढ़ो.ccwdev  = ccwgdev->cdev[0];
	card->ग_लिखो.ccwdev = ccwgdev->cdev[1];

	recover_state = card->state;
	rc = ccw_device_set_online(card->पढ़ो.ccwdev);
	अगर (rc)
		जाओ out_err;
	rc = ccw_device_set_online(card->ग_लिखो.ccwdev);
	अगर (rc)
		जाओ out_werr;

	LCS_DBF_TEXT(3, setup, "lcsnewdv");

	lcs_setup_card(card);
	rc = lcs_detect(card);
	अगर (rc) अणु
		LCS_DBF_TEXT(2, setup, "dtctfail");
		dev_err(&ccwgdev->dev,
			"Detecting a network adapter for LCS devices"
			" failed with rc=%d (0x%x)\n", rc, rc);
		lcs_stopcard(card);
		जाओ out;
	पूर्ण
	अगर (card->dev) अणु
		LCS_DBF_TEXT(2, setup, "samedev");
		LCS_DBF_HEX(3, setup, &card, माप(व्योम*));
		जाओ netdev_out;
	पूर्ण
	चयन (card->lan_type) अणु
#अगर_घोषित CONFIG_ETHERNET
	हाल LCS_FRAME_TYPE_ENET:
		card->lan_type_trans = eth_type_trans;
		dev = alloc_etherdev(0);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FDDI
	हाल LCS_FRAME_TYPE_FDDI:
		card->lan_type_trans = fddi_type_trans;
		dev = alloc_fddidev(0);
		अवरोध;
#पूर्ण_अगर
	शेष:
		LCS_DBF_TEXT(3, setup, "errinit");
		pr_err(" Initialization failed\n");
		जाओ out;
	पूर्ण
	अगर (!dev)
		जाओ out;
	card->dev = dev;
	card->dev->ml_priv = card;
	card->dev->netdev_ops = &lcs_netdev_ops;
	card->dev->dev_port = card->portno;
	स_नकल(card->dev->dev_addr, card->mac, LCS_MAC_LENGTH);
#अगर_घोषित CONFIG_IP_MULTICAST
	अगर (!lcs_check_multicast_support(card))
		card->dev->netdev_ops = &lcs_mc_netdev_ops;
#पूर्ण_अगर
netdev_out:
	lcs_set_allowed_thपढ़ोs(card,0xffffffff);
	अगर (recover_state == DEV_STATE_RECOVER) अणु
		lcs_set_multicast_list(card->dev);
		card->dev->flags |= IFF_UP;
		netअगर_carrier_on(card->dev);
		netअगर_wake_queue(card->dev);
		card->state = DEV_STATE_UP;
	पूर्ण अन्यथा अणु
		lcs_stopcard(card);
	पूर्ण

	अगर (lcs_रेजिस्टर_netdev(ccwgdev) != 0)
		जाओ out;

	/* Prपूर्णांक out supported assists: IPv6 */
	pr_info("LCS device %s %s IPv6 support\n", card->dev->name,
		(card->ip_assists_supported & LCS_IPASS_IPV6_SUPPORT) ?
		"with" : "without");
	/* Prपूर्णांक out supported assist: Multicast */
	pr_info("LCS device %s %s Multicast support\n", card->dev->name,
		(card->ip_assists_supported & LCS_IPASS_MULTICAST_SUPPORT) ?
		"with" : "without");
	वापस 0;
out:

	ccw_device_set_offline(card->ग_लिखो.ccwdev);
out_werr:
	ccw_device_set_offline(card->पढ़ो.ccwdev);
out_err:
	वापस -ENODEV;
पूर्ण

/**
 * lcs_shutकरोwn_device, called when setting the group device offline.
 */
अटल पूर्णांक
__lcs_shutकरोwn_device(काष्ठा ccwgroup_device *ccwgdev, पूर्णांक recovery_mode)
अणु
	काष्ठा lcs_card *card;
	क्रमागत lcs_dev_states recover_state;
	पूर्णांक ret = 0, ret2 = 0, ret3 = 0;

	LCS_DBF_TEXT(3, setup, "shtdndev");
	card = dev_get_drvdata(&ccwgdev->dev);
	अगर (!card)
		वापस -ENODEV;
	अगर (recovery_mode == 0) अणु
		lcs_set_allowed_thपढ़ोs(card, 0);
		अगर (lcs_रुको_क्रम_thपढ़ोs(card, LCS_SET_MC_THREAD))
			वापस -ERESTARTSYS;
	पूर्ण
	LCS_DBF_HEX(3, setup, &card, माप(व्योम*));
	recover_state = card->state;

	ret = lcs_stop_device(card->dev);
	ret2 = ccw_device_set_offline(card->पढ़ो.ccwdev);
	ret3 = ccw_device_set_offline(card->ग_लिखो.ccwdev);
	अगर (!ret)
		ret = (ret2) ? ret2 : ret3;
	अगर (ret)
		LCS_DBF_TEXT_(3, setup, "1err:%d", ret);
	अगर (recover_state == DEV_STATE_UP) अणु
		card->state = DEV_STATE_RECOVER;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
lcs_shutकरोwn_device(काष्ठा ccwgroup_device *ccwgdev)
अणु
	वापस __lcs_shutकरोwn_device(ccwgdev, 0);
पूर्ण

/**
 * drive lcs recovery after startup and startlan initiated by Lan Gateway
 */
अटल पूर्णांक
lcs_recovery(व्योम *ptr)
अणु
	काष्ठा lcs_card *card;
	काष्ठा ccwgroup_device *gdev;
        पूर्णांक rc;

	card = (काष्ठा lcs_card *) ptr;

	LCS_DBF_TEXT(4, trace, "recover1");
	अगर (!lcs_करो_run_thपढ़ो(card, LCS_RECOVERY_THREAD))
		वापस 0;
	LCS_DBF_TEXT(4, trace, "recover2");
	gdev = card->gdev;
	dev_warn(&gdev->dev,
		"A recovery process has been started for the LCS device\n");
	rc = __lcs_shutकरोwn_device(gdev, 1);
	rc = lcs_new_device(gdev);
	अगर (!rc)
		pr_info("Device %s successfully recovered!\n",
			card->dev->name);
	अन्यथा
		pr_info("Device %s could not be recovered!\n",
			card->dev->name);
	lcs_clear_thपढ़ो_running_bit(card, LCS_RECOVERY_THREAD);
	वापस 0;
पूर्ण

/**
 * lcs_हटाओ_device, मुक्त buffers and card
 */
अटल व्योम
lcs_हटाओ_device(काष्ठा ccwgroup_device *ccwgdev)
अणु
	काष्ठा lcs_card *card;

	card = dev_get_drvdata(&ccwgdev->dev);
	अगर (!card)
		वापस;

	LCS_DBF_TEXT(3, setup, "remdev");
	LCS_DBF_HEX(3, setup, &card, माप(व्योम*));
	अगर (ccwgdev->state == CCWGROUP_ONLINE) अणु
		lcs_shutकरोwn_device(ccwgdev);
	पूर्ण
	अगर (card->dev)
		unरेजिस्टर_netdev(card->dev);
	lcs_cleanup_card(card);
	lcs_मुक्त_card(card);
	dev_set_drvdata(&ccwgdev->dev, शून्य);
	put_device(&ccwgdev->dev);
पूर्ण

अटल काष्ठा ccw_device_id lcs_ids[] = अणु
	अणुCCW_DEVICE(0x3088, 0x08), .driver_info = lcs_channel_type_parallelपूर्ण,
	अणुCCW_DEVICE(0x3088, 0x1f), .driver_info = lcs_channel_type_2216पूर्ण,
	अणुCCW_DEVICE(0x3088, 0x60), .driver_info = lcs_channel_type_osa2पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ccw, lcs_ids);

अटल काष्ठा ccw_driver lcs_ccw_driver = अणु
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= "lcs",
	पूर्ण,
	.ids	= lcs_ids,
	.probe	= ccwgroup_probe_ccwdev,
	.हटाओ	= ccwgroup_हटाओ_ccwdev,
	.पूर्णांक_class = IRQIO_LCS,
पूर्ण;

/**
 * LCS ccwgroup driver registration
 */
अटल काष्ठा ccwgroup_driver lcs_group_driver = अणु
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= "lcs",
	पूर्ण,
	.ccw_driver  = &lcs_ccw_driver,
	.setup	     = lcs_probe_device,
	.हटाओ      = lcs_हटाओ_device,
	.set_online  = lcs_new_device,
	.set_offline = lcs_shutकरोwn_device,
पूर्ण;

अटल sमाप_प्रकार group_store(काष्ठा device_driver *ddrv, स्थिर अक्षर *buf,
			   माप_प्रकार count)
अणु
	पूर्णांक err;
	err = ccwgroup_create_dev(lcs_root_dev, &lcs_group_driver, 2, buf);
	वापस err ? err : count;
पूर्ण
अटल DRIVER_ATTR_WO(group);

अटल काष्ठा attribute *lcs_drv_attrs[] = अणु
	&driver_attr_group.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group lcs_drv_attr_group = अणु
	.attrs = lcs_drv_attrs,
पूर्ण;
अटल स्थिर काष्ठा attribute_group *lcs_drv_attr_groups[] = अणु
	&lcs_drv_attr_group,
	शून्य,
पूर्ण;

/**
 *  LCS Module/Kernel initialization function
 */
अटल पूर्णांक
__init lcs_init_module(व्योम)
अणु
	पूर्णांक rc;

	pr_info("Loading %s\n", version);
	rc = lcs_रेजिस्टर_debug_facility();
	LCS_DBF_TEXT(0, setup, "lcsinit");
	अगर (rc)
		जाओ out_err;
	lcs_root_dev = root_device_रेजिस्टर("lcs");
	rc = PTR_ERR_OR_ZERO(lcs_root_dev);
	अगर (rc)
		जाओ रेजिस्टर_err;
	rc = ccw_driver_रेजिस्टर(&lcs_ccw_driver);
	अगर (rc)
		जाओ ccw_err;
	lcs_group_driver.driver.groups = lcs_drv_attr_groups;
	rc = ccwgroup_driver_रेजिस्टर(&lcs_group_driver);
	अगर (rc)
		जाओ ccwgroup_err;
	वापस 0;

ccwgroup_err:
	ccw_driver_unरेजिस्टर(&lcs_ccw_driver);
ccw_err:
	root_device_unरेजिस्टर(lcs_root_dev);
रेजिस्टर_err:
	lcs_unरेजिस्टर_debug_facility();
out_err:
	pr_err("Initializing the lcs device driver failed\n");
	वापस rc;
पूर्ण


/**
 *  LCS module cleanup function
 */
अटल व्योम
__निकास lcs_cleanup_module(व्योम)
अणु
	pr_info("Terminating lcs module.\n");
	LCS_DBF_TEXT(0, trace, "cleanup");
	ccwgroup_driver_unरेजिस्टर(&lcs_group_driver);
	ccw_driver_unरेजिस्टर(&lcs_ccw_driver);
	root_device_unरेजिस्टर(lcs_root_dev);
	lcs_unरेजिस्टर_debug_facility();
पूर्ण

module_init(lcs_init_module);
module_निकास(lcs_cleanup_module);

MODULE_AUTHOR("Frank Pavlic <fpavlic@de.ibm.com>");
MODULE_LICENSE("GPL");

