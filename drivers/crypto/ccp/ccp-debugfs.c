<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) driver
 *
 * Copyright (C) 2017 Advanced Micro Devices, Inc.
 *
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/ccp.h>

#समावेश "ccp-dev.h"

/* DebugFS helpers */
#घोषणा	OBUFP		(obuf + oboff)
#घोषणा	OBUFLEN		512
#घोषणा	OBUFSPC		(OBUFLEN - oboff)
#घोषणा	OSCNPRINTF(fmt, ...) \
		scnम_लिखो(OBUFP, OBUFSPC, fmt, ## __VA_ARGS__)

#घोषणा BUFLEN	63

#घोषणा	RI_VERSION_NUM	0x0000003F
#घोषणा	RI_AES_PRESENT	0x00000040
#घोषणा	RI_3DES_PRESENT	0x00000080
#घोषणा	RI_SHA_PRESENT	0x00000100
#घोषणा	RI_RSA_PRESENT	0x00000200
#घोषणा	RI_ECC_PRESENT	0x00000400
#घोषणा	RI_ZDE_PRESENT	0x00000800
#घोषणा	RI_ZCE_PRESENT	0x00001000
#घोषणा	RI_TRNG_PRESENT	0x00002000
#घोषणा	RI_ELFC_PRESENT	0x00004000
#घोषणा	RI_ELFC_SHIFT	14
#घोषणा	RI_NUM_VQM	0x00078000
#घोषणा	RI_NVQM_SHIFT	15
#घोषणा	RI_NVQM(r)	(((r) * RI_NUM_VQM) >> RI_NVQM_SHIFT)
#घोषणा	RI_LSB_ENTRIES	0x0FF80000
#घोषणा	RI_NLSB_SHIFT	19
#घोषणा	RI_NLSB(r)	(((r) * RI_LSB_ENTRIES) >> RI_NLSB_SHIFT)

अटल sमाप_प्रकार ccp5_debugfs_info_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				      माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा ccp_device *ccp = filp->निजी_data;
	अचिन्हित पूर्णांक oboff = 0;
	अचिन्हित पूर्णांक regval;
	sमाप_प्रकार ret;
	अक्षर *obuf;

	अगर (!ccp)
		वापस 0;

	obuf = kदो_स्मृति(OBUFLEN, GFP_KERNEL);
	अगर (!obuf)
		वापस -ENOMEM;

	oboff += OSCNPRINTF("Device name: %s\n", ccp->name);
	oboff += OSCNPRINTF("   RNG name: %s\n", ccp->rngname);
	oboff += OSCNPRINTF("   # Queues: %d\n", ccp->cmd_q_count);
	oboff += OSCNPRINTF("     # Cmds: %d\n", ccp->cmd_count);

	regval = ioपढ़ो32(ccp->io_regs + CMD5_PSP_CCP_VERSION);
	oboff += OSCNPRINTF("    Version: %d\n", regval & RI_VERSION_NUM);
	oboff += OSCNPRINTF("    Engines:");
	अगर (regval & RI_AES_PRESENT)
		oboff += OSCNPRINTF(" AES");
	अगर (regval & RI_3DES_PRESENT)
		oboff += OSCNPRINTF(" 3DES");
	अगर (regval & RI_SHA_PRESENT)
		oboff += OSCNPRINTF(" SHA");
	अगर (regval & RI_RSA_PRESENT)
		oboff += OSCNPRINTF(" RSA");
	अगर (regval & RI_ECC_PRESENT)
		oboff += OSCNPRINTF(" ECC");
	अगर (regval & RI_ZDE_PRESENT)
		oboff += OSCNPRINTF(" ZDE");
	अगर (regval & RI_ZCE_PRESENT)
		oboff += OSCNPRINTF(" ZCE");
	अगर (regval & RI_TRNG_PRESENT)
		oboff += OSCNPRINTF(" TRNG");
	oboff += OSCNPRINTF("\n");
	oboff += OSCNPRINTF("     Queues: %d\n",
		   (regval & RI_NUM_VQM) >> RI_NVQM_SHIFT);
	oboff += OSCNPRINTF("LSB Entries: %d\n",
		   (regval & RI_LSB_ENTRIES) >> RI_NLSB_SHIFT);

	ret = simple_पढ़ो_from_buffer(ubuf, count, offp, obuf, oboff);
	kमुक्त(obuf);

	वापस ret;
पूर्ण

/* Return a क्रमmatted buffer containing the current
 * statistics across all queues क्रम a CCP.
 */
अटल sमाप_प्रकार ccp5_debugfs_stats_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				       माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा ccp_device *ccp = filp->निजी_data;
	अचिन्हित दीर्घ total_xts_aes_ops = 0;
	अचिन्हित दीर्घ total_3des_ops = 0;
	अचिन्हित दीर्घ total_aes_ops = 0;
	अचिन्हित दीर्घ total_sha_ops = 0;
	अचिन्हित दीर्घ total_rsa_ops = 0;
	अचिन्हित दीर्घ total_ecc_ops = 0;
	अचिन्हित दीर्घ total_pt_ops = 0;
	अचिन्हित दीर्घ total_ops = 0;
	अचिन्हित पूर्णांक oboff = 0;
	sमाप_प्रकार ret = 0;
	अचिन्हित पूर्णांक i;
	अक्षर *obuf;

	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		काष्ठा ccp_cmd_queue *cmd_q = &ccp->cmd_q[i];

		total_ops += cmd_q->total_ops;
		total_aes_ops += cmd_q->total_aes_ops;
		total_xts_aes_ops += cmd_q->total_xts_aes_ops;
		total_3des_ops += cmd_q->total_3des_ops;
		total_sha_ops += cmd_q->total_sha_ops;
		total_rsa_ops += cmd_q->total_rsa_ops;
		total_pt_ops += cmd_q->total_pt_ops;
		total_ecc_ops += cmd_q->total_ecc_ops;
	पूर्ण

	obuf = kदो_स्मृति(OBUFLEN, GFP_KERNEL);
	अगर (!obuf)
		वापस -ENOMEM;

	oboff += OSCNPRINTF("Total Interrupts Handled: %ld\n",
			    ccp->total_पूर्णांकerrupts);
	oboff += OSCNPRINTF("        Total Operations: %ld\n",
			    total_ops);
	oboff += OSCNPRINTF("                     AES: %ld\n",
			    total_aes_ops);
	oboff += OSCNPRINTF("                 XTS AES: %ld\n",
			    total_xts_aes_ops);
	oboff += OSCNPRINTF("                     SHA: %ld\n",
			    total_3des_ops);
	oboff += OSCNPRINTF("                     SHA: %ld\n",
			    total_sha_ops);
	oboff += OSCNPRINTF("                     RSA: %ld\n",
			    total_rsa_ops);
	oboff += OSCNPRINTF("               Pass-Thru: %ld\n",
			    total_pt_ops);
	oboff += OSCNPRINTF("                     ECC: %ld\n",
			    total_ecc_ops);

	ret = simple_पढ़ो_from_buffer(ubuf, count, offp, obuf, oboff);
	kमुक्त(obuf);

	वापस ret;
पूर्ण

/* Reset the counters in a queue
 */
अटल व्योम ccp5_debugfs_reset_queue_stats(काष्ठा ccp_cmd_queue *cmd_q)
अणु
	cmd_q->total_ops = 0L;
	cmd_q->total_aes_ops = 0L;
	cmd_q->total_xts_aes_ops = 0L;
	cmd_q->total_3des_ops = 0L;
	cmd_q->total_sha_ops = 0L;
	cmd_q->total_rsa_ops = 0L;
	cmd_q->total_pt_ops = 0L;
	cmd_q->total_ecc_ops = 0L;
पूर्ण

/* A value was written to the stats variable, which
 * should be used to reset the queue counters across
 * that device.
 */
अटल sमाप_प्रकार ccp5_debugfs_stats_ग_लिखो(काष्ठा file *filp,
					स्थिर अक्षर __user *ubuf,
					माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा ccp_device *ccp = filp->निजी_data;
	पूर्णांक i;

	क्रम (i = 0; i < ccp->cmd_q_count; i++)
		ccp5_debugfs_reset_queue_stats(&ccp->cmd_q[i]);
	ccp->total_पूर्णांकerrupts = 0L;

	वापस count;
पूर्ण

/* Return a क्रमmatted buffer containing the current inक्रमmation
 * क्रम that queue
 */
अटल sमाप_प्रकार ccp5_debugfs_queue_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				       माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा ccp_cmd_queue *cmd_q = filp->निजी_data;
	अचिन्हित पूर्णांक oboff = 0;
	अचिन्हित पूर्णांक regval;
	sमाप_प्रकार ret;
	अक्षर *obuf;

	अगर (!cmd_q)
		वापस 0;

	obuf = kदो_स्मृति(OBUFLEN, GFP_KERNEL);
	अगर (!obuf)
		वापस -ENOMEM;

	oboff += OSCNPRINTF("  Total Queue Operations: %ld\n",
			    cmd_q->total_ops);
	oboff += OSCNPRINTF("                     AES: %ld\n",
			    cmd_q->total_aes_ops);
	oboff += OSCNPRINTF("                 XTS AES: %ld\n",
			    cmd_q->total_xts_aes_ops);
	oboff += OSCNPRINTF("                     SHA: %ld\n",
			    cmd_q->total_3des_ops);
	oboff += OSCNPRINTF("                     SHA: %ld\n",
			    cmd_q->total_sha_ops);
	oboff += OSCNPRINTF("                     RSA: %ld\n",
			    cmd_q->total_rsa_ops);
	oboff += OSCNPRINTF("               Pass-Thru: %ld\n",
			    cmd_q->total_pt_ops);
	oboff += OSCNPRINTF("                     ECC: %ld\n",
			    cmd_q->total_ecc_ops);

	regval = ioपढ़ो32(cmd_q->reg_पूर्णांक_enable);
	oboff += OSCNPRINTF("      Enabled Interrupts:");
	अगर (regval & INT_EMPTY_QUEUE)
		oboff += OSCNPRINTF(" EMPTY");
	अगर (regval & INT_QUEUE_STOPPED)
		oboff += OSCNPRINTF(" STOPPED");
	अगर (regval & INT_ERROR)
		oboff += OSCNPRINTF(" ERROR");
	अगर (regval & INT_COMPLETION)
		oboff += OSCNPRINTF(" COMPLETION");
	oboff += OSCNPRINTF("\n");

	ret = simple_पढ़ो_from_buffer(ubuf, count, offp, obuf, oboff);
	kमुक्त(obuf);

	वापस ret;
पूर्ण

/* A value was written to the stats variable क्रम a
 * queue. Reset the queue counters to this value.
 */
अटल sमाप_प्रकार ccp5_debugfs_queue_ग_लिखो(काष्ठा file *filp,
					स्थिर अक्षर __user *ubuf,
					माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा ccp_cmd_queue *cmd_q = filp->निजी_data;

	ccp5_debugfs_reset_queue_stats(cmd_q);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations ccp_debugfs_info_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = ccp5_debugfs_info_पढ़ो,
	.ग_लिखो = शून्य,
पूर्ण;

अटल स्थिर काष्ठा file_operations ccp_debugfs_queue_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = ccp5_debugfs_queue_पढ़ो,
	.ग_लिखो = ccp5_debugfs_queue_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations ccp_debugfs_stats_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = ccp5_debugfs_stats_पढ़ो,
	.ग_लिखो = ccp5_debugfs_stats_ग_लिखो,
पूर्ण;

अटल काष्ठा dentry *ccp_debugfs_dir;
अटल DEFINE_MUTEX(ccp_debugfs_lock);

#घोषणा	MAX_NAME_LEN	20

व्योम ccp5_debugfs_setup(काष्ठा ccp_device *ccp)
अणु
	काष्ठा ccp_cmd_queue *cmd_q;
	अक्षर name[MAX_NAME_LEN + 1];
	काष्ठा dentry *debugfs_q_instance;
	पूर्णांक i;

	अगर (!debugfs_initialized())
		वापस;

	mutex_lock(&ccp_debugfs_lock);
	अगर (!ccp_debugfs_dir)
		ccp_debugfs_dir = debugfs_create_dir(KBUILD_MODNAME, शून्य);
	mutex_unlock(&ccp_debugfs_lock);

	ccp->debugfs_instance = debugfs_create_dir(ccp->name, ccp_debugfs_dir);

	debugfs_create_file("info", 0400, ccp->debugfs_instance, ccp,
			    &ccp_debugfs_info_ops);

	debugfs_create_file("stats", 0600, ccp->debugfs_instance, ccp,
			    &ccp_debugfs_stats_ops);

	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		cmd_q = &ccp->cmd_q[i];

		snम_लिखो(name, MAX_NAME_LEN - 1, "q%d", cmd_q->id);

		debugfs_q_instance =
			debugfs_create_dir(name, ccp->debugfs_instance);

		debugfs_create_file("stats", 0600, debugfs_q_instance, cmd_q,
				    &ccp_debugfs_queue_ops);
	पूर्ण

	वापस;
पूर्ण

व्योम ccp5_debugfs_destroy(व्योम)
अणु
	debugfs_हटाओ_recursive(ccp_debugfs_dir);
पूर्ण
