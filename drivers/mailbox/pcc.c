<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Copyright (C) 2014 Linaro Ltd.
 *	Author:	Ashwin Chaugule <ashwin.chaugule@linaro.org>
 *
 *  PCC (Platक्रमm Communication Channel) is defined in the ACPI 5.0+
 *  specअगरication. It is a mailbox like mechanism to allow clients
 *  such as CPPC (Collaborative Processor Perक्रमmance Control), RAS
 *  (Reliability, Availability and Serviceability) and MPST (Memory
 *  Node Power State Table) to talk to the platक्रमm (e.g. BMC) through
 *  shared memory regions as defined in the PCC table entries. The PCC
 *  specअगरication supports a Doorbell mechanism क्रम the PCC clients
 *  to notअगरy the platक्रमm about new data. This Doorbell inक्रमmation
 *  is also specअगरied in each PCC table entry.
 *
 *  Typical high level flow of operation is:
 *
 *  PCC Reads:
 *  * Client tries to acquire a channel lock.
 *  * After it is acquired it ग_लिखोs READ cmd in communication region cmd
 *		address.
 *  * Client issues mbox_send_message() which rings the PCC करोorbell
 *		क्रम its PCC channel.
 *  * If command completes, then client has control over channel and
 *		it can proceed with its पढ़ोs.
 *  * Client releases lock.
 *
 *  PCC Writes:
 *  * Client tries to acquire channel lock.
 *  * Client ग_लिखोs to its communication region after it acquires a
 *		channel lock.
 *  * Client ग_लिखोs WRITE cmd in communication region cmd address.
 *  * Client issues mbox_send_message() which rings the PCC करोorbell
 *		क्रम its PCC channel.
 *  * If command completes, then ग_लिखोs have succeeded and it can release
 *		the channel lock.
 *
 *  There is a Nominal latency defined क्रम each channel which indicates
 *  how दीर्घ to रुको until a command completes. If command is not complete
 *  the client needs to retry or assume failure.
 *
 *	For more details about PCC, please see the ACPI specअगरication from
 *  http://www.uefi.org/ACPIv5.1 Section 14.
 *
 *  This file implements PCC as a Mailbox controller and allows क्रम PCC
 *  clients to be implemented as its Mailbox Client Channels.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <acpi/pcc.h>

#समावेश "mailbox.h"

#घोषणा MBOX_IRQ_NAME		"pcc-mbox"

अटल काष्ठा mbox_chan *pcc_mbox_channels;

/* Array of cached भव address क्रम करोorbell रेजिस्टरs */
अटल व्योम __iomem **pcc_करोorbell_vaddr;
/* Array of cached भव address क्रम करोorbell ack रेजिस्टरs */
अटल व्योम __iomem **pcc_करोorbell_ack_vaddr;
/* Array of करोorbell पूर्णांकerrupts */
अटल पूर्णांक *pcc_करोorbell_irq;

अटल काष्ठा mbox_controller pcc_mbox_ctrl = अणुपूर्ण;
/**
 * get_pcc_channel - Given a PCC subspace idx, get
 *	the respective mbox_channel.
 * @id: PCC subspace index.
 *
 * Return: ERR_PTR(त्रुटि_सं) अगर error, अन्यथा poपूर्णांकer
 *	to mbox channel.
 */
अटल काष्ठा mbox_chan *get_pcc_channel(पूर्णांक id)
अणु
	अगर (id < 0 || id >= pcc_mbox_ctrl.num_chans)
		वापस ERR_PTR(-ENOENT);

	वापस &pcc_mbox_channels[id];
पूर्ण

/*
 * PCC can be used with perf critical drivers such as CPPC
 * So it makes sense to locally cache the भव address and
 * use it to पढ़ो/ग_लिखो to PCC रेजिस्टरs such as करोorbell रेजिस्टर
 *
 * The below पढ़ो_रेजिस्टर and ग_लिखो_रेजिस्टरs are used to पढ़ो and
 * ग_लिखो from perf critical रेजिस्टरs such as PCC करोorbell रेजिस्टर
 */
अटल पूर्णांक पढ़ो_रेजिस्टर(व्योम __iomem *vaddr, u64 *val, अचिन्हित पूर्णांक bit_width)
अणु
	पूर्णांक ret_val = 0;

	चयन (bit_width) अणु
	हाल 8:
		*val = पढ़ोb(vaddr);
		अवरोध;
	हाल 16:
		*val = पढ़ोw(vaddr);
		अवरोध;
	हाल 32:
		*val = पढ़ोl(vaddr);
		अवरोध;
	हाल 64:
		*val = पढ़ोq(vaddr);
		अवरोध;
	शेष:
		pr_debug("Error: Cannot read register of %u bit width",
			bit_width);
		ret_val = -EFAULT;
		अवरोध;
	पूर्ण
	वापस ret_val;
पूर्ण

अटल पूर्णांक ग_लिखो_रेजिस्टर(व्योम __iomem *vaddr, u64 val, अचिन्हित पूर्णांक bit_width)
अणु
	पूर्णांक ret_val = 0;

	चयन (bit_width) अणु
	हाल 8:
		ग_लिखोb(val, vaddr);
		अवरोध;
	हाल 16:
		ग_लिखोw(val, vaddr);
		अवरोध;
	हाल 32:
		ग_लिखोl(val, vaddr);
		अवरोध;
	हाल 64:
		ग_लिखोq(val, vaddr);
		अवरोध;
	शेष:
		pr_debug("Error: Cannot write register of %u bit width",
			bit_width);
		ret_val = -EFAULT;
		अवरोध;
	पूर्ण
	वापस ret_val;
पूर्ण

/**
 * pcc_map_पूर्णांकerrupt - Map a PCC subspace GSI to a linux IRQ number
 * @पूर्णांकerrupt: GSI number.
 * @flags: पूर्णांकerrupt flags
 *
 * Returns: a valid linux IRQ number on success
 *		0 or -EINVAL on failure
 */
अटल पूर्णांक pcc_map_पूर्णांकerrupt(u32 पूर्णांकerrupt, u32 flags)
अणु
	पूर्णांक trigger, polarity;

	अगर (!पूर्णांकerrupt)
		वापस 0;

	trigger = (flags & ACPI_PCCT_INTERRUPT_MODE) ? ACPI_EDGE_SENSITIVE
			: ACPI_LEVEL_SENSITIVE;

	polarity = (flags & ACPI_PCCT_INTERRUPT_POLARITY) ? ACPI_ACTIVE_LOW
			: ACPI_ACTIVE_HIGH;

	वापस acpi_रेजिस्टर_gsi(शून्य, पूर्णांकerrupt, trigger, polarity);
पूर्ण

/**
 * pcc_mbox_irq - PCC mailbox पूर्णांकerrupt handler
 */
अटल irqवापस_t pcc_mbox_irq(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा acpi_generic_address *करोorbell_ack;
	काष्ठा acpi_pcct_hw_reduced *pcct_ss;
	काष्ठा mbox_chan *chan = p;
	u64 करोorbell_ack_preserve;
	u64 करोorbell_ack_ग_लिखो;
	u64 करोorbell_ack_val;
	पूर्णांक ret;

	pcct_ss = chan->con_priv;

	mbox_chan_received_data(chan, शून्य);

	अगर (pcct_ss->header.type == ACPI_PCCT_TYPE_HW_REDUCED_SUBSPACE_TYPE2) अणु
		काष्ठा acpi_pcct_hw_reduced_type2 *pcct2_ss = chan->con_priv;
		u32 id = chan - pcc_mbox_channels;

		करोorbell_ack = &pcct2_ss->platक्रमm_ack_रेजिस्टर;
		करोorbell_ack_preserve = pcct2_ss->ack_preserve_mask;
		करोorbell_ack_ग_लिखो = pcct2_ss->ack_ग_लिखो_mask;

		ret = पढ़ो_रेजिस्टर(pcc_करोorbell_ack_vaddr[id],
				    &करोorbell_ack_val,
				    करोorbell_ack->bit_width);
		अगर (ret)
			वापस IRQ_NONE;

		ret = ग_लिखो_रेजिस्टर(pcc_करोorbell_ack_vaddr[id],
				     (करोorbell_ack_val & करोorbell_ack_preserve)
					| करोorbell_ack_ग_लिखो,
				     करोorbell_ack->bit_width);
		अगर (ret)
			वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * pcc_mbox_request_channel - PCC clients call this function to
 *		request a poपूर्णांकer to their PCC subspace, from which they
 *		can get the details of communicating with the remote.
 * @cl: Poपूर्णांकer to Mailbox client, so we know where to bind the
 *		Channel.
 * @subspace_id: The PCC Subspace index as parsed in the PCC client
 *		ACPI package. This is used to lookup the array of PCC
 *		subspaces as parsed by the PCC Mailbox controller.
 *
 * Return: Poपूर्णांकer to the Mailbox Channel अगर successful or
 *		ERR_PTR.
 */
काष्ठा mbox_chan *pcc_mbox_request_channel(काष्ठा mbox_client *cl,
		पूर्णांक subspace_id)
अणु
	काष्ठा device *dev = pcc_mbox_ctrl.dev;
	काष्ठा mbox_chan *chan;
	अचिन्हित दीर्घ flags;

	/*
	 * Each PCC Subspace is a Mailbox Channel.
	 * The PCC Clients get their PCC Subspace ID
	 * from their own tables and pass it here.
	 * This वापसs a poपूर्णांकer to the PCC subspace
	 * क्रम the Client to operate on.
	 */
	chan = get_pcc_channel(subspace_id);

	अगर (IS_ERR(chan) || chan->cl) अणु
		dev_err(dev, "Channel not found for idx: %d\n", subspace_id);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	spin_lock_irqsave(&chan->lock, flags);
	chan->msg_मुक्त = 0;
	chan->msg_count = 0;
	chan->active_req = शून्य;
	chan->cl = cl;
	init_completion(&chan->tx_complete);

	अगर (chan->txकरोne_method == TXDONE_BY_POLL && cl->knows_txकरोne)
		chan->txकरोne_method = TXDONE_BY_ACK;

	spin_unlock_irqrestore(&chan->lock, flags);

	अगर (pcc_करोorbell_irq[subspace_id] > 0) अणु
		पूर्णांक rc;

		rc = devm_request_irq(dev, pcc_करोorbell_irq[subspace_id],
				      pcc_mbox_irq, 0, MBOX_IRQ_NAME, chan);
		अगर (unlikely(rc)) अणु
			dev_err(dev, "failed to register PCC interrupt %d\n",
				pcc_करोorbell_irq[subspace_id]);
			pcc_mbox_मुक्त_channel(chan);
			chan = ERR_PTR(rc);
		पूर्ण
	पूर्ण

	वापस chan;
पूर्ण
EXPORT_SYMBOL_GPL(pcc_mbox_request_channel);

/**
 * pcc_mbox_मुक्त_channel - Clients call this to मुक्त their Channel.
 *
 * @chan: Poपूर्णांकer to the mailbox channel as वापसed by
 *		pcc_mbox_request_channel()
 */
व्योम pcc_mbox_मुक्त_channel(काष्ठा mbox_chan *chan)
अणु
	u32 id = chan - pcc_mbox_channels;
	अचिन्हित दीर्घ flags;

	अगर (!chan || !chan->cl)
		वापस;

	अगर (id >= pcc_mbox_ctrl.num_chans) अणु
		pr_debug("pcc_mbox_free_channel: Invalid mbox_chan passed\n");
		वापस;
	पूर्ण

	अगर (pcc_करोorbell_irq[id] > 0)
		devm_मुक्त_irq(chan->mbox->dev, pcc_करोorbell_irq[id], chan);

	spin_lock_irqsave(&chan->lock, flags);
	chan->cl = शून्य;
	chan->active_req = शून्य;
	अगर (chan->txकरोne_method == TXDONE_BY_ACK)
		chan->txकरोne_method = TXDONE_BY_POLL;

	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(pcc_mbox_मुक्त_channel);

/**
 * pcc_send_data - Called from Mailbox Controller code. Used
 *		here only to ring the channel करोorbell. The PCC client
 *		specअगरic पढ़ो/ग_लिखो is करोne in the client driver in
 *		order to मुख्यtain atomicity over PCC channel once
 *		OS has control over it. See above क्रम flow of operations.
 * @chan: Poपूर्णांकer to Mailbox channel over which to send data.
 * @data: Client specअगरic data written over channel. Used here
 *		only क्रम debug after PCC transaction completes.
 *
 * Return: Err अगर something failed अन्यथा 0 क्रम success.
 */
अटल पूर्णांक pcc_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा acpi_pcct_hw_reduced *pcct_ss = chan->con_priv;
	काष्ठा acpi_generic_address *करोorbell;
	u64 करोorbell_preserve;
	u64 करोorbell_val;
	u64 करोorbell_ग_लिखो;
	u32 id = chan - pcc_mbox_channels;
	पूर्णांक ret = 0;

	अगर (id >= pcc_mbox_ctrl.num_chans) अणु
		pr_debug("pcc_send_data: Invalid mbox_chan passed\n");
		वापस -ENOENT;
	पूर्ण

	करोorbell = &pcct_ss->करोorbell_रेजिस्टर;
	करोorbell_preserve = pcct_ss->preserve_mask;
	करोorbell_ग_लिखो = pcct_ss->ग_लिखो_mask;

	/* Sync notअगरication from OS to Platक्रमm. */
	अगर (pcc_करोorbell_vaddr[id]) अणु
		ret = पढ़ो_रेजिस्टर(pcc_करोorbell_vaddr[id], &करोorbell_val,
			करोorbell->bit_width);
		अगर (ret)
			वापस ret;
		ret = ग_लिखो_रेजिस्टर(pcc_करोorbell_vaddr[id],
			(करोorbell_val & करोorbell_preserve) | करोorbell_ग_लिखो,
			करोorbell->bit_width);
	पूर्ण अन्यथा अणु
		ret = acpi_पढ़ो(&करोorbell_val, करोorbell);
		अगर (ret)
			वापस ret;
		ret = acpi_ग_लिखो((करोorbell_val & करोorbell_preserve) | करोorbell_ग_लिखो,
			करोorbell);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops pcc_chan_ops = अणु
	.send_data = pcc_send_data,
पूर्ण;

/**
 * parse_pcc_subspaces -- Count PCC subspaces defined
 * @header: Poपूर्णांकer to the ACPI subtable header under the PCCT.
 * @end: End of subtable entry.
 *
 * Return: If we find a PCC subspace entry of a valid type, वापस 0.
 *	Otherwise, वापस -EINVAL.
 *
 * This माला_लो called क्रम each entry in the PCC table.
 */
अटल पूर्णांक parse_pcc_subspace(जोड़ acpi_subtable_headers *header,
		स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_pcct_subspace *ss = (काष्ठा acpi_pcct_subspace *) header;

	अगर (ss->header.type < ACPI_PCCT_TYPE_RESERVED)
		वापस 0;

	वापस -EINVAL;
पूर्ण

/**
 * pcc_parse_subspace_irq - Parse the PCC IRQ and PCC ACK रेजिस्टर
 *		There should be one entry per PCC client.
 * @id: PCC subspace index.
 * @pcct_ss: Poपूर्णांकer to the ACPI subtable header under the PCCT.
 *
 * Return: 0 क्रम Success, अन्यथा त्रुटि_सं.
 *
 * This माला_लो called क्रम each entry in the PCC table.
 */
अटल पूर्णांक pcc_parse_subspace_irq(पूर्णांक id,
				  काष्ठा acpi_pcct_hw_reduced *pcct_ss)
अणु
	pcc_करोorbell_irq[id] = pcc_map_पूर्णांकerrupt(pcct_ss->platक्रमm_पूर्णांकerrupt,
						 (u32)pcct_ss->flags);
	अगर (pcc_करोorbell_irq[id] <= 0) अणु
		pr_err("PCC GSI %d not registered\n",
		       pcct_ss->platक्रमm_पूर्णांकerrupt);
		वापस -EINVAL;
	पूर्ण

	अगर (pcct_ss->header.type
		== ACPI_PCCT_TYPE_HW_REDUCED_SUBSPACE_TYPE2) अणु
		काष्ठा acpi_pcct_hw_reduced_type2 *pcct2_ss = (व्योम *)pcct_ss;

		pcc_करोorbell_ack_vaddr[id] = acpi_os_ioremap(
				pcct2_ss->platक्रमm_ack_रेजिस्टर.address,
				pcct2_ss->platक्रमm_ack_रेजिस्टर.bit_width / 8);
		अगर (!pcc_करोorbell_ack_vaddr[id]) अणु
			pr_err("Failed to ioremap PCC ACK register\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * acpi_pcc_probe - Parse the ACPI tree क्रम the PCCT.
 *
 * Return: 0 क्रम Success, अन्यथा त्रुटि_सं.
 */
अटल पूर्णांक __init acpi_pcc_probe(व्योम)
अणु
	काष्ठा acpi_table_header *pcct_tbl;
	काष्ठा acpi_subtable_header *pcct_entry;
	काष्ठा acpi_table_pcct *acpi_pcct_tbl;
	काष्ठा acpi_subtable_proc proc[ACPI_PCCT_TYPE_RESERVED];
	पूर्णांक count, i, rc;
	acpi_status status = AE_OK;

	/* Search क्रम PCCT */
	status = acpi_get_table(ACPI_SIG_PCCT, 0, &pcct_tbl);

	अगर (ACPI_FAILURE(status) || !pcct_tbl)
		वापस -ENODEV;

	/* Set up the subtable handlers */
	क्रम (i = ACPI_PCCT_TYPE_GENERIC_SUBSPACE;
	     i < ACPI_PCCT_TYPE_RESERVED; i++) अणु
		proc[i].id = i;
		proc[i].count = 0;
		proc[i].handler = parse_pcc_subspace;
	पूर्ण

	count = acpi_table_parse_entries_array(ACPI_SIG_PCCT,
			माप(काष्ठा acpi_table_pcct), proc,
			ACPI_PCCT_TYPE_RESERVED, MAX_PCC_SUBSPACES);
	अगर (count <= 0 || count > MAX_PCC_SUBSPACES) अणु
		अगर (count < 0)
			pr_warn("Error parsing PCC subspaces from PCCT\n");
		अन्यथा
			pr_warn("Invalid PCCT: %d PCC subspaces\n", count);

		rc = -EINVAL;
		जाओ err_put_pcct;
	पूर्ण

	pcc_mbox_channels = kसुस्मृति(count, माप(काष्ठा mbox_chan),
				    GFP_KERNEL);
	अगर (!pcc_mbox_channels) अणु
		pr_err("Could not allocate space for PCC mbox channels\n");
		rc = -ENOMEM;
		जाओ err_put_pcct;
	पूर्ण

	pcc_करोorbell_vaddr = kसुस्मृति(count, माप(व्योम *), GFP_KERNEL);
	अगर (!pcc_करोorbell_vaddr) अणु
		rc = -ENOMEM;
		जाओ err_मुक्त_mbox;
	पूर्ण

	pcc_करोorbell_ack_vaddr = kसुस्मृति(count, माप(व्योम *), GFP_KERNEL);
	अगर (!pcc_करोorbell_ack_vaddr) अणु
		rc = -ENOMEM;
		जाओ err_मुक्त_db_vaddr;
	पूर्ण

	pcc_करोorbell_irq = kसुस्मृति(count, माप(पूर्णांक), GFP_KERNEL);
	अगर (!pcc_करोorbell_irq) अणु
		rc = -ENOMEM;
		जाओ err_मुक्त_db_ack_vaddr;
	पूर्ण

	/* Poपूर्णांक to the first PCC subspace entry */
	pcct_entry = (काष्ठा acpi_subtable_header *) (
		(अचिन्हित दीर्घ) pcct_tbl + माप(काष्ठा acpi_table_pcct));

	acpi_pcct_tbl = (काष्ठा acpi_table_pcct *) pcct_tbl;
	अगर (acpi_pcct_tbl->flags & ACPI_PCCT_DOORBELL)
		pcc_mbox_ctrl.txकरोne_irq = true;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा acpi_generic_address *db_reg;
		काष्ठा acpi_pcct_subspace *pcct_ss;
		pcc_mbox_channels[i].con_priv = pcct_entry;

		अगर (pcct_entry->type == ACPI_PCCT_TYPE_HW_REDUCED_SUBSPACE ||
		    pcct_entry->type == ACPI_PCCT_TYPE_HW_REDUCED_SUBSPACE_TYPE2) अणु
			काष्ठा acpi_pcct_hw_reduced *pcct_hrss;

			pcct_hrss = (काष्ठा acpi_pcct_hw_reduced *) pcct_entry;

			अगर (pcc_mbox_ctrl.txकरोne_irq) अणु
				rc = pcc_parse_subspace_irq(i, pcct_hrss);
				अगर (rc < 0)
					जाओ err;
			पूर्ण
		पूर्ण
		pcct_ss = (काष्ठा acpi_pcct_subspace *) pcct_entry;

		/* If करोorbell is in प्रणाली memory cache the virt address */
		db_reg = &pcct_ss->करोorbell_रेजिस्टर;
		अगर (db_reg->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY)
			pcc_करोorbell_vaddr[i] = acpi_os_ioremap(db_reg->address,
							db_reg->bit_width/8);
		pcct_entry = (काष्ठा acpi_subtable_header *)
			((अचिन्हित दीर्घ) pcct_entry + pcct_entry->length);
	पूर्ण

	pcc_mbox_ctrl.num_chans = count;

	pr_info("Detected %d PCC Subspaces\n", pcc_mbox_ctrl.num_chans);

	वापस 0;

err:
	kमुक्त(pcc_करोorbell_irq);
err_मुक्त_db_ack_vaddr:
	kमुक्त(pcc_करोorbell_ack_vaddr);
err_मुक्त_db_vaddr:
	kमुक्त(pcc_करोorbell_vaddr);
err_मुक्त_mbox:
	kमुक्त(pcc_mbox_channels);
err_put_pcct:
	acpi_put_table(pcct_tbl);
	वापस rc;
पूर्ण

/**
 * pcc_mbox_probe - Called when we find a match क्रम the
 *	PCCT platक्रमm device. This is purely used to represent
 *	the PCCT as a भव device क्रम रेजिस्टरing with the
 *	generic Mailbox framework.
 *
 * @pdev: Poपूर्णांकer to platक्रमm device वापसed when a match
 *	is found.
 *
 *	Return: 0 क्रम Success, अन्यथा त्रुटि_सं.
 */
अटल पूर्णांक pcc_mbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;

	pcc_mbox_ctrl.chans = pcc_mbox_channels;
	pcc_mbox_ctrl.ops = &pcc_chan_ops;
	pcc_mbox_ctrl.dev = &pdev->dev;

	pr_info("Registering PCC driver as Mailbox controller\n");
	ret = mbox_controller_रेजिस्टर(&pcc_mbox_ctrl);

	अगर (ret) अणु
		pr_err("Err registering PCC as Mailbox controller: %d\n", ret);
		ret = -ENODEV;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver pcc_mbox_driver = अणु
	.probe = pcc_mbox_probe,
	.driver = अणु
		.name = "PCCT",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pcc_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा platक्रमm_device *pcc_pdev;

	अगर (acpi_disabled)
		वापस -ENODEV;

	/* Check अगर PCC support is available. */
	ret = acpi_pcc_probe();

	अगर (ret) अणु
		pr_debug("ACPI PCC probe failed.\n");
		वापस -ENODEV;
	पूर्ण

	pcc_pdev = platक्रमm_create_bundle(&pcc_mbox_driver,
			pcc_mbox_probe, शून्य, 0, शून्य, 0);

	अगर (IS_ERR(pcc_pdev)) अणु
		pr_debug("Err creating PCC platform bundle\n");
		वापस PTR_ERR(pcc_pdev);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Make PCC init postcore so that users of this mailbox
 * such as the ACPI Processor driver have it available
 * at their init.
 */
postcore_initcall(pcc_init);
