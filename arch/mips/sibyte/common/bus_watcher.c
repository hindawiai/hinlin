<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2002,2003 Broadcom Corporation
 */

/*
 * The Bus Watcher monitors पूर्णांकernal bus transactions and मुख्यtains
 * counts of transactions with error status, logging details and
 * causing one of several पूर्णांकerrupts.  This driver provides a handler
 * क्रम those पूर्णांकerrupts which aggregates the counts (to aव्योम
 * saturating the 8-bit counters) and provides a presence in
 * /proc/bus_watcher अगर PROC_FS is on.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/sibyte/sb1250.h>
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/sb1250_पूर्णांक.h>
#समावेश <यंत्र/sibyte/sb1250_scd.h>
#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
#समावेश <यंत्र/sibyte/bcm1480_regs.h>
#पूर्ण_अगर


काष्ठा bw_stats_काष्ठा अणु
	uपूर्णांक64_t status;
	uपूर्णांक32_t l2_err;
	uपूर्णांक32_t memio_err;
	पूर्णांक status_prपूर्णांकed;
	अचिन्हित दीर्घ l2_cor_d;
	अचिन्हित दीर्घ l2_bad_d;
	अचिन्हित दीर्घ l2_cor_t;
	अचिन्हित दीर्घ l2_bad_t;
	अचिन्हित दीर्घ mem_cor_d;
	अचिन्हित दीर्घ mem_bad_d;
	अचिन्हित दीर्घ bus_error;
पूर्ण bw_stats;


अटल व्योम prपूर्णांक_summary(uपूर्णांक32_t status, uपूर्णांक32_t l2_err,
			  uपूर्णांक32_t memio_err)
अणु
	prपूर्णांकk("Bus watcher error counters: %08x %08x\n", l2_err, memio_err);
	prपूर्णांकk("\nLast recorded signature:\n");
	prपूर्णांकk("Request %02x from %d, answered by %d with Dcode %d\n",
	       (अचिन्हित पूर्णांक)(G_SCD_BERR_TID(status) & 0x3f),
	       (पूर्णांक)(G_SCD_BERR_TID(status) >> 6),
	       (पूर्णांक)G_SCD_BERR_RID(status),
	       (पूर्णांक)G_SCD_BERR_DCODE(status));
पूर्ण

/*
 * check_bus_watcher is exported क्रम use in situations where we want
 * to see the most recent status of the bus watcher, which might have
 * alपढ़ोy been deकाष्ठाively पढ़ो out of the रेजिस्टरs.
 *
 * notes: this is currently used by the cache error handler
 *	  should provide locking against the पूर्णांकerrupt handler
 */
व्योम check_bus_watcher(व्योम)
अणु
	u32 status, l2_err, memio_err;

#अगर defined(CONFIG_SIBYTE_BCM112X) || defined(CONFIG_SIBYTE_SB1250)
	/* Use non-deकाष्ठाive रेजिस्टर */
	status = csr_in32(IOADDR(A_SCD_BUS_ERR_STATUS_DEBUG));
#या_अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
	/* Use non-deकाष्ठाive रेजिस्टर */
	/* Same as 1250 except BUS_ERR_STATUS_DEBUG is in a dअगरferent place. */
	status = csr_in32(IOADDR(A_BCM1480_BUS_ERR_STATUS_DEBUG));
#अन्यथा
#त्रुटि bus watcher being built क्रम unknown Sibyte SOC!
#पूर्ण_अगर
	अगर (!(status & 0x7fffffff)) अणु
		prपूर्णांकk("Using last values reaped by bus watcher driver\n");
		status = bw_stats.status;
		l2_err = bw_stats.l2_err;
		memio_err = bw_stats.memio_err;
	पूर्ण अन्यथा अणु
		l2_err = csr_in32(IOADDR(A_BUS_L2_ERRORS));
		memio_err = csr_in32(IOADDR(A_BUS_MEM_IO_ERRORS));
	पूर्ण
	अगर (status & ~(1UL << 31))
		prपूर्णांक_summary(status, l2_err, memio_err);
	अन्यथा
		prपूर्णांकk("Bus watcher indicates no error\n");
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

/* For simplicity, I want to assume a single पढ़ो is required each
   समय */
अटल पूर्णांक bw_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा bw_stats_काष्ठा *stats = m->निजी;

	seq_माला_दो(m, "SiByte Bus Watcher statistics\n");
	seq_माला_दो(m, "-----------------------------\n");
	seq_म_लिखो(m, "L2-d-cor %8ld\nL2-d-bad %8ld\n",
		   stats->l2_cor_d, stats->l2_bad_d);
	seq_म_लिखो(m, "L2-t-cor %8ld\nL2-t-bad %8ld\n",
		   stats->l2_cor_t, stats->l2_bad_t);
	seq_म_लिखो(m, "MC-d-cor %8ld\nMC-d-bad %8ld\n",
		   stats->mem_cor_d, stats->mem_bad_d);
	seq_म_लिखो(m, "IO-err   %8ld\n", stats->bus_error);
	seq_माला_दो(m, "\nLast recorded signature:\n");
	seq_म_लिखो(m, "Request %02x from %d, answered by %d with Dcode %d\n",
		   (अचिन्हित पूर्णांक)(G_SCD_BERR_TID(stats->status) & 0x3f),
		   (पूर्णांक)(G_SCD_BERR_TID(stats->status) >> 6),
		   (पूर्णांक)G_SCD_BERR_RID(stats->status),
		   (पूर्णांक)G_SCD_BERR_DCODE(stats->status));
	/* XXXKW indicate multiple errors between prपूर्णांकings, or stats
	   collection (or both)? */
	अगर (stats->status & M_SCD_BERR_MULTERRS)
		seq_माला_दो(m, "Multiple errors observed since last check.\n");
	अगर (stats->status_prपूर्णांकed) अणु
		seq_माला_दो(m, "(no change since last printing)\n");
	पूर्ण अन्यथा अणु
		stats->status_prपूर्णांकed = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम create_proc_decoder(काष्ठा bw_stats_काष्ठा *stats)
अणु
	काष्ठा proc_dir_entry *ent;

	ent = proc_create_single_data("bus_watcher", S_IWUSR | S_IRUGO, शून्य,
			bw_proc_show, stats);
	अगर (!ent) अणु
		prपूर्णांकk(KERN_INFO "Unable to initialize bus_watcher /proc entry\n");
		वापस;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_PROC_FS */

/*
 * sibyte_bw_पूर्णांक - handle bus watcher पूर्णांकerrupts and accumulate counts
 *
 * notes: possible re-entry due to multiple sources
 *	  should check/indicate saturation
 */
अटल irqवापस_t sibyte_bw_पूर्णांक(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bw_stats_काष्ठा *stats = data;
	अचिन्हित दीर्घ cntr;
#अगर_घोषित CONFIG_SIBYTE_BW_TRACE
	पूर्णांक i;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SIBYTE_BW_TRACE
	csr_out32(M_SCD_TRACE_CFG_FREEZE, IOADDR(A_SCD_TRACE_CFG));
	csr_out32(M_SCD_TRACE_CFG_START_READ, IOADDR(A_SCD_TRACE_CFG));

	क्रम (i=0; i<256*6; i++)
		prपूर्णांकk("%016llx\n",
		       (दीर्घ दीर्घ)__raw_पढ़ोq(IOADDR(A_SCD_TRACE_READ)));

	csr_out32(M_SCD_TRACE_CFG_RESET, IOADDR(A_SCD_TRACE_CFG));
	csr_out32(M_SCD_TRACE_CFG_START, IOADDR(A_SCD_TRACE_CFG));
#पूर्ण_अगर

	/* Deकाष्ठाive पढ़ो, clears रेजिस्टर and पूर्णांकerrupt */
	stats->status = csr_in32(IOADDR(A_SCD_BUS_ERR_STATUS));
	stats->status_prपूर्णांकed = 0;

	stats->l2_err = cntr = csr_in32(IOADDR(A_BUS_L2_ERRORS));
	stats->l2_cor_d += G_SCD_L2ECC_CORR_D(cntr);
	stats->l2_bad_d += G_SCD_L2ECC_BAD_D(cntr);
	stats->l2_cor_t += G_SCD_L2ECC_CORR_T(cntr);
	stats->l2_bad_t += G_SCD_L2ECC_BAD_T(cntr);
	csr_out32(0, IOADDR(A_BUS_L2_ERRORS));

	stats->memio_err = cntr = csr_in32(IOADDR(A_BUS_MEM_IO_ERRORS));
	stats->mem_cor_d += G_SCD_MEM_ECC_CORR(cntr);
	stats->mem_bad_d += G_SCD_MEM_ECC_BAD(cntr);
	stats->bus_error += G_SCD_MEM_BUSERR(cntr);
	csr_out32(0, IOADDR(A_BUS_MEM_IO_ERRORS));

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक __init sibyte_bus_watcher(व्योम)
अणु
	स_रखो(&bw_stats, 0, माप(काष्ठा bw_stats_काष्ठा));
	bw_stats.status_prपूर्णांकed = 1;

	अगर (request_irq(K_INT_BAD_ECC, sibyte_bw_पूर्णांक, 0, "Bus watcher", &bw_stats)) अणु
		prपूर्णांकk("Failed to register bus watcher BAD_ECC irq\n");
		वापस -1;
	पूर्ण
	अगर (request_irq(K_INT_COR_ECC, sibyte_bw_पूर्णांक, 0, "Bus watcher", &bw_stats)) अणु
		मुक्त_irq(K_INT_BAD_ECC, &bw_stats);
		prपूर्णांकk("Failed to register bus watcher COR_ECC irq\n");
		वापस -1;
	पूर्ण
	अगर (request_irq(K_INT_IO_BUS, sibyte_bw_पूर्णांक, 0, "Bus watcher", &bw_stats)) अणु
		मुक्त_irq(K_INT_BAD_ECC, &bw_stats);
		मुक्त_irq(K_INT_COR_ECC, &bw_stats);
		prपूर्णांकk("Failed to register bus watcher IO_BUS irq\n");
		वापस -1;
	पूर्ण

#अगर_घोषित CONFIG_PROC_FS
	create_proc_decoder(&bw_stats);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SIBYTE_BW_TRACE
	csr_out32((M_SCD_TRSEQ_ASAMPLE | M_SCD_TRSEQ_DSAMPLE |
		   K_SCD_TRSEQ_TRIGGER_ALL),
		  IOADDR(A_SCD_TRACE_SEQUENCE_0));
	csr_out32(M_SCD_TRACE_CFG_RESET, IOADDR(A_SCD_TRACE_CFG));
	csr_out32(M_SCD_TRACE_CFG_START, IOADDR(A_SCD_TRACE_CFG));
#पूर्ण_अगर

	वापस 0;
पूर्ण

device_initcall(sibyte_bus_watcher);
