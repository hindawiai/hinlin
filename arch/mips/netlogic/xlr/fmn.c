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

#समावेश <linux/kernel.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/netlogic/पूर्णांकerrupt.h>
#समावेश <यंत्र/netlogic/xlr/fmn.h>
#समावेश <यंत्र/netlogic/common.h>

#घोषणा COP2_CC_INIT_CPU_DEST(dest, conf) \
करो अणु \
	nlm_ग_लिखो_c2_cc##dest(0, conf[(dest * 8) + 0]); \
	nlm_ग_लिखो_c2_cc##dest(1, conf[(dest * 8) + 1]); \
	nlm_ग_लिखो_c2_cc##dest(2, conf[(dest * 8) + 2]); \
	nlm_ग_लिखो_c2_cc##dest(3, conf[(dest * 8) + 3]); \
	nlm_ग_लिखो_c2_cc##dest(4, conf[(dest * 8) + 4]); \
	nlm_ग_लिखो_c2_cc##dest(5, conf[(dest * 8) + 5]); \
	nlm_ग_लिखो_c2_cc##dest(6, conf[(dest * 8) + 6]); \
	nlm_ग_लिखो_c2_cc##dest(7, conf[(dest * 8) + 7]); \
पूर्ण जबतक (0)

काष्ठा fmn_message_handler अणु
	व्योम (*action)(पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, काष्ठा nlm_fmn_msg *, व्योम *);
	व्योम *arg;
पूर्ण msg_handlers[128];

/*
 * FMN पूर्णांकerrupt handler. We configure the FMN so that any messages in
 * any of the CPU buckets will trigger an पूर्णांकerrupt on the CPU.
 * The message can be from any device on the FMN (like NAE/SAE/DMA).
 * The source station id is used to figure out which of the रेजिस्टरed
 * handlers have to be called.
 */
अटल irqवापस_t fmn_message_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fmn_message_handler *hndlr;
	पूर्णांक bucket, rv;
	पूर्णांक size = 0, code = 0, src_stnid = 0;
	काष्ठा nlm_fmn_msg msg;
	uपूर्णांक32_t mflags, bkt_status;

	mflags = nlm_cop2_enable_irqsave();
	/* Disable message ring पूर्णांकerrupt */
	nlm_fmn_setup_पूर्णांकr(irq, 0);
	जबतक (1) अणु
		/* 8 bkts per core, [24:31] each bit represents one bucket
		 * Bit is Zero अगर bucket is not empty */
		bkt_status = (nlm_पढ़ो_c2_status0() >> 24) & 0xff;
		अगर (bkt_status == 0xff)
			अवरोध;
		क्रम (bucket = 0; bucket < 8; bucket++) अणु
			/* Continue on empty bucket */
			अगर (bkt_status & (1 << bucket))
				जारी;
			rv = nlm_fmn_receive(bucket, &size, &code, &src_stnid,
						&msg);
			अगर (rv != 0)
				जारी;

			hndlr = &msg_handlers[src_stnid];
			अगर (hndlr->action == शून्य)
				pr_warn("No msgring handler for stnid %d\n",
						src_stnid);
			अन्यथा अणु
				nlm_cop2_disable_irqrestore(mflags);
				hndlr->action(bucket, src_stnid, size, code,
					&msg, hndlr->arg);
				mflags = nlm_cop2_enable_irqsave();
			पूर्ण
		पूर्ण
	पूर्ण
	/* Enable message ring पूर्णांकr, to any thपढ़ो in core */
	nlm_fmn_setup_पूर्णांकr(irq, (1 << nlm_thपढ़ोs_per_core) - 1);
	nlm_cop2_disable_irqrestore(mflags);
	वापस IRQ_HANDLED;
पूर्ण

व्योम xlr_percpu_fmn_init(व्योम)
अणु
	काष्ठा xlr_fmn_info *cpu_fmn_info;
	पूर्णांक *bucket_sizes;
	uपूर्णांक32_t flags;
	पूर्णांक id;

	BUG_ON(nlm_thपढ़ो_id() != 0);
	id = nlm_core_id();

	bucket_sizes = xlr_board_fmn_config.bucket_size;
	cpu_fmn_info = &xlr_board_fmn_config.cpu[id];
	flags = nlm_cop2_enable_irqsave();

	/* Setup bucket sizes क्रम the core. */
	nlm_ग_लिखो_c2_bucksize(0, bucket_sizes[id * 8 + 0]);
	nlm_ग_लिखो_c2_bucksize(1, bucket_sizes[id * 8 + 1]);
	nlm_ग_लिखो_c2_bucksize(2, bucket_sizes[id * 8 + 2]);
	nlm_ग_लिखो_c2_bucksize(3, bucket_sizes[id * 8 + 3]);
	nlm_ग_लिखो_c2_bucksize(4, bucket_sizes[id * 8 + 4]);
	nlm_ग_लिखो_c2_bucksize(5, bucket_sizes[id * 8 + 5]);
	nlm_ग_लिखो_c2_bucksize(6, bucket_sizes[id * 8 + 6]);
	nlm_ग_लिखो_c2_bucksize(7, bucket_sizes[id * 8 + 7]);

	/*
	 * For sending FMN messages, we need credits on the destination
	 * bucket. Program the credits this core has on the 128 possible
	 * destination buckets.
	 * We cannot use a loop here, because the the first argument has
	 * to be a स्थिरant पूर्णांकeger value.
	 */
	COP2_CC_INIT_CPU_DEST(0, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(1, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(2, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(3, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(4, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(5, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(6, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(7, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(8, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(9, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(10, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(11, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(12, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(13, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(14, cpu_fmn_info->credit_config);
	COP2_CC_INIT_CPU_DEST(15, cpu_fmn_info->credit_config);

	/* enable FMN पूर्णांकerrupts on this CPU */
	nlm_fmn_setup_पूर्णांकr(IRQ_FMN, (1 << nlm_thपढ़ोs_per_core) - 1);
	nlm_cop2_disable_irqrestore(flags);
पूर्ण


/*
 * Register a FMN message handler with respect to the source station id
 * @stnid: source station id
 * @action: Handler function poपूर्णांकer
 */
पूर्णांक nlm_रेजिस्टर_fmn_handler(पूर्णांक start_stnid, पूर्णांक end_stnid,
	व्योम (*action)(पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, काष्ठा nlm_fmn_msg *, व्योम *),
	व्योम *arg)
अणु
	पूर्णांक sstnid;

	क्रम (sstnid = start_stnid; sstnid <= end_stnid; sstnid++) अणु
		msg_handlers[sstnid].arg = arg;
		smp_wmb();
		msg_handlers[sstnid].action = action;
	पूर्ण
	pr_debug("Registered FMN msg handler for stnid %d-%d\n",
			start_stnid, end_stnid);
	वापस 0;
पूर्ण

व्योम nlm_setup_fmn_irq(व्योम)
अणु
	uपूर्णांक32_t flags;

	/* request irq only once */
	अगर (request_irq(IRQ_FMN, fmn_message_handler, IRQF_PERCPU, "fmn", शून्य))
		pr_err("Failed to request irq %d (fmn)\n", IRQ_FMN);

	flags = nlm_cop2_enable_irqsave();
	nlm_fmn_setup_पूर्णांकr(IRQ_FMN, (1 << nlm_thपढ़ोs_per_core) - 1);
	nlm_cop2_disable_irqrestore(flags);
पूर्ण
