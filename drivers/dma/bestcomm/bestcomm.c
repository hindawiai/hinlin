<शैली गुरु>
/*
 * Driver क्रम MPC52xx processor BestComm peripheral controller
 *
 *
 * Copyright (C) 2006-2007 Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2005      Varma Electronics Oy,
 *                         ( by Andrey Volkov <avolkov@varma-el.com> )
 * Copyright (C) 2003-2004 MontaVista, Software, Inc.
 *                         ( by Dale Farnsworth <dfarnsworth@mvista.com> )
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mpc52xx.h>

#समावेश <linux/fsl/bestcomm/sram.h>
#समावेश <linux/fsl/bestcomm/bestcomm_priv.h>
#समावेश "linux/fsl/bestcomm/bestcomm.h"

#घोषणा DRIVER_NAME "bestcomm-core"

/* MPC5200 device tree match tables */
अटल स्थिर काष्ठा of_device_id mpc52xx_sram_ids[] = अणु
	अणु .compatible = "fsl,mpc5200-sram", पूर्ण,
	अणु .compatible = "mpc5200-sram", पूर्ण,
	अणुपूर्ण
पूर्ण;


काष्ठा bcom_engine *bcom_eng = शून्य;
EXPORT_SYMBOL_GPL(bcom_eng);	/* needed क्रम अंतरभूत functions */

/* ======================================================================== */
/* Public and निजी API                                                   */
/* ======================================================================== */

/* Private API */

काष्ठा bcom_task *
bcom_task_alloc(पूर्णांक bd_count, पूर्णांक bd_size, पूर्णांक priv_size)
अणु
	पूर्णांक i, tasknum = -1;
	काष्ठा bcom_task *tsk;

	/* Don't try to करो anything अगर bestcomm init failed */
	अगर (!bcom_eng)
		वापस शून्य;

	/* Get and reserve a task num */
	spin_lock(&bcom_eng->lock);

	क्रम (i=0; i<BCOM_MAX_TASKS; i++)
		अगर (!bcom_eng->tdt[i].stop) अणु	/* we use stop as a marker */
			bcom_eng->tdt[i].stop = 0xfffffffful; /* dummy addr */
			tasknum = i;
			अवरोध;
		पूर्ण

	spin_unlock(&bcom_eng->lock);

	अगर (tasknum < 0)
		वापस शून्य;

	/* Allocate our काष्ठाure */
	tsk = kzalloc(माप(काष्ठा bcom_task) + priv_size, GFP_KERNEL);
	अगर (!tsk)
		जाओ error;

	tsk->tasknum = tasknum;
	अगर (priv_size)
		tsk->priv = (व्योम*)tsk + माप(काष्ठा bcom_task);

	/* Get IRQ of that task */
	tsk->irq = irq_of_parse_and_map(bcom_eng->ofnode, tsk->tasknum);
	अगर (!tsk->irq)
		जाओ error;

	/* Init the BDs, अगर needed */
	अगर (bd_count) अणु
		tsk->cookie = kदो_स्मृति_array(bd_count, माप(व्योम *),
					    GFP_KERNEL);
		अगर (!tsk->cookie)
			जाओ error;

		tsk->bd = bcom_sram_alloc(bd_count * bd_size, 4, &tsk->bd_pa);
		अगर (!tsk->bd)
			जाओ error;
		स_रखो(tsk->bd, 0x00, bd_count * bd_size);

		tsk->num_bd = bd_count;
		tsk->bd_size = bd_size;
	पूर्ण

	वापस tsk;

error:
	अगर (tsk) अणु
		अगर (tsk->irq)
			irq_dispose_mapping(tsk->irq);
		bcom_sram_मुक्त(tsk->bd);
		kमुक्त(tsk->cookie);
		kमुक्त(tsk);
	पूर्ण

	bcom_eng->tdt[tasknum].stop = 0;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_task_alloc);

व्योम
bcom_task_मुक्त(काष्ठा bcom_task *tsk)
अणु
	/* Stop the task */
	bcom_disable_task(tsk->tasknum);

	/* Clear TDT */
	bcom_eng->tdt[tsk->tasknum].start = 0;
	bcom_eng->tdt[tsk->tasknum].stop  = 0;

	/* Free everything */
	irq_dispose_mapping(tsk->irq);
	bcom_sram_मुक्त(tsk->bd);
	kमुक्त(tsk->cookie);
	kमुक्त(tsk);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_task_मुक्त);

पूर्णांक
bcom_load_image(पूर्णांक task, u32 *task_image)
अणु
	काष्ठा bcom_task_header *hdr = (काष्ठा bcom_task_header *)task_image;
	काष्ठा bcom_tdt *tdt;
	u32 *desc, *var, *inc;
	u32 *desc_src, *var_src, *inc_src;

	/* Safety checks */
	अगर (hdr->magic != BCOM_TASK_MAGIC) अणु
		prपूर्णांकk(KERN_ERR DRIVER_NAME
			": Trying to load invalid microcode\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((task < 0) || (task >= BCOM_MAX_TASKS)) अणु
		prपूर्णांकk(KERN_ERR DRIVER_NAME
			": Trying to load invalid task %d\n", task);
		वापस -EINVAL;
	पूर्ण

	/* Initial load or reload */
	tdt = &bcom_eng->tdt[task];

	अगर (tdt->start) अणु
		desc = bcom_task_desc(task);
		अगर (hdr->desc_size != bcom_task_num_descs(task)) अणु
			prपूर्णांकk(KERN_ERR DRIVER_NAME
				": Trying to reload wrong task image "
				"(%d size %d/%d)!\n",
				task,
				hdr->desc_size,
				bcom_task_num_descs(task));
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		phys_addr_t start_pa;

		desc = bcom_sram_alloc(hdr->desc_size * माप(u32), 4, &start_pa);
		अगर (!desc)
			वापस -ENOMEM;

		tdt->start = start_pa;
		tdt->stop = start_pa + ((hdr->desc_size-1) * माप(u32));
	पूर्ण

	var = bcom_task_var(task);
	inc = bcom_task_inc(task);

	/* Clear & copy */
	स_रखो(var, 0x00, BCOM_VAR_SIZE);
	स_रखो(inc, 0x00, BCOM_INC_SIZE);

	desc_src = (u32 *)(hdr + 1);
	var_src = desc_src + hdr->desc_size;
	inc_src = var_src + hdr->var_size;

	स_नकल(desc, desc_src, hdr->desc_size * माप(u32));
	स_नकल(var + hdr->first_var, var_src, hdr->var_size * माप(u32));
	स_नकल(inc, inc_src, hdr->inc_size * माप(u32));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_load_image);

व्योम
bcom_set_initiator(पूर्णांक task, पूर्णांक initiator)
अणु
	पूर्णांक i;
	पूर्णांक num_descs;
	u32 *desc;
	पूर्णांक next_drd_has_initiator;

	bcom_set_tcr_initiator(task, initiator);

	/* Just setting tcr is apparently not enough due to some problem */
	/* with it. So we just go thru all the microcode and replace in  */
	/* the DRD directly */

	desc = bcom_task_desc(task);
	next_drd_has_initiator = 1;
	num_descs = bcom_task_num_descs(task);

	क्रम (i=0; i<num_descs; i++, desc++) अणु
		अगर (!bcom_desc_is_drd(*desc))
			जारी;
		अगर (next_drd_has_initiator)
			अगर (bcom_desc_initiator(*desc) != BCOM_INITIATOR_ALWAYS)
				bcom_set_desc_initiator(desc, initiator);
		next_drd_has_initiator = !bcom_drd_is_extended(*desc);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(bcom_set_initiator);


/* Public API */

व्योम
bcom_enable(काष्ठा bcom_task *tsk)
अणु
	bcom_enable_task(tsk->tasknum);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_enable);

व्योम
bcom_disable(काष्ठा bcom_task *tsk)
अणु
	bcom_disable_task(tsk->tasknum);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_disable);


/* ======================================================================== */
/* Engine init/cleanup                                                      */
/* ======================================================================== */

/* Function Descriptor table */
/* this will need to be updated अगर Freescale changes their task code FDT */
अटल u32 fdt_ops[] = अणु
	0xa0045670,	/* FDT[48] - load_acc()	  */
	0x80045670,	/* FDT[49] - unload_acc() */
	0x21800000,	/* FDT[50] - and()        */
	0x21e00000,	/* FDT[51] - or()         */
	0x21500000,	/* FDT[52] - xor()        */
	0x21400000,	/* FDT[53] - andn()       */
	0x21500000,	/* FDT[54] - not()        */
	0x20400000,	/* FDT[55] - add()        */
	0x20500000,	/* FDT[56] - sub()        */
	0x20800000,	/* FDT[57] - lsh()        */
	0x20a00000,	/* FDT[58] - rsh()        */
	0xc0170000,	/* FDT[59] - crc8()       */
	0xc0145670,	/* FDT[60] - crc16()      */
	0xc0345670,	/* FDT[61] - crc32()      */
	0xa0076540,	/* FDT[62] - endian32()   */
	0xa0000760,	/* FDT[63] - endian16()   */
पूर्ण;


अटल पूर्णांक bcom_engine_init(व्योम)
अणु
	पूर्णांक task;
	phys_addr_t tdt_pa, ctx_pa, var_pa, fdt_pa;
	अचिन्हित पूर्णांक tdt_size, ctx_size, var_size, fdt_size;

	/* Allocate & clear SRAM zones क्रम FDT, TDTs, contexts and vars/incs */
	tdt_size = BCOM_MAX_TASKS * माप(काष्ठा bcom_tdt);
	ctx_size = BCOM_MAX_TASKS * BCOM_CTX_SIZE;
	var_size = BCOM_MAX_TASKS * (BCOM_VAR_SIZE + BCOM_INC_SIZE);
	fdt_size = BCOM_FDT_SIZE;

	bcom_eng->tdt = bcom_sram_alloc(tdt_size, माप(u32), &tdt_pa);
	bcom_eng->ctx = bcom_sram_alloc(ctx_size, BCOM_CTX_ALIGN, &ctx_pa);
	bcom_eng->var = bcom_sram_alloc(var_size, BCOM_VAR_ALIGN, &var_pa);
	bcom_eng->fdt = bcom_sram_alloc(fdt_size, BCOM_FDT_ALIGN, &fdt_pa);

	अगर (!bcom_eng->tdt || !bcom_eng->ctx || !bcom_eng->var || !bcom_eng->fdt) अणु
		prपूर्णांकk(KERN_ERR "DMA: SRAM alloc failed in engine init !\n");

		bcom_sram_मुक्त(bcom_eng->tdt);
		bcom_sram_मुक्त(bcom_eng->ctx);
		bcom_sram_मुक्त(bcom_eng->var);
		bcom_sram_मुक्त(bcom_eng->fdt);

		वापस -ENOMEM;
	पूर्ण

	स_रखो(bcom_eng->tdt, 0x00, tdt_size);
	स_रखो(bcom_eng->ctx, 0x00, ctx_size);
	स_रखो(bcom_eng->var, 0x00, var_size);
	स_रखो(bcom_eng->fdt, 0x00, fdt_size);

	/* Copy the FDT क्रम the EU#3 */
	स_नकल(&bcom_eng->fdt[48], fdt_ops, माप(fdt_ops));

	/* Initialize Task base काष्ठाure */
	क्रम (task=0; task<BCOM_MAX_TASKS; task++)
	अणु
		out_be16(&bcom_eng->regs->tcr[task], 0);
		out_8(&bcom_eng->regs->ipr[task], 0);

		bcom_eng->tdt[task].context	= ctx_pa;
		bcom_eng->tdt[task].var	= var_pa;
		bcom_eng->tdt[task].fdt	= fdt_pa;

		var_pa += BCOM_VAR_SIZE + BCOM_INC_SIZE;
		ctx_pa += BCOM_CTX_SIZE;
	पूर्ण

	out_be32(&bcom_eng->regs->taskBar, tdt_pa);

	/* Init 'always' initiator */
	out_8(&bcom_eng->regs->ipr[BCOM_INITIATOR_ALWAYS], BCOM_IPR_ALWAYS);

	/* Disable COMM Bus Prefetch on the original 5200; it's broken */
	अगर ((mfspr(SPRN_SVR) & MPC5200_SVR_MASK) == MPC5200_SVR)
		bcom_disable_prefetch();

	/* Init lock */
	spin_lock_init(&bcom_eng->lock);

	वापस 0;
पूर्ण

अटल व्योम
bcom_engine_cleanup(व्योम)
अणु
	पूर्णांक task;

	/* Stop all tasks */
	क्रम (task=0; task<BCOM_MAX_TASKS; task++)
	अणु
		out_be16(&bcom_eng->regs->tcr[task], 0);
		out_8(&bcom_eng->regs->ipr[task], 0);
	पूर्ण

	out_be32(&bcom_eng->regs->taskBar, 0ul);

	/* Release the SRAM zones */
	bcom_sram_मुक्त(bcom_eng->tdt);
	bcom_sram_मुक्त(bcom_eng->ctx);
	bcom_sram_मुक्त(bcom_eng->var);
	bcom_sram_मुक्त(bcom_eng->fdt);
पूर्ण


/* ======================================================================== */
/* OF platक्रमm driver                                                       */
/* ======================================================================== */

अटल पूर्णांक mpc52xx_bcom_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *ofn_sram;
	काष्ठा resource res_bcom;

	पूर्णांक rv;

	/* Inक्रमm user we're ok so far */
	prपूर्णांकk(KERN_INFO "DMA: MPC52xx BestComm driver\n");

	/* Get the bestcomm node */
	of_node_get(op->dev.of_node);

	/* Prepare SRAM */
	ofn_sram = of_find_matching_node(शून्य, mpc52xx_sram_ids);
	अगर (!ofn_sram) अणु
		prपूर्णांकk(KERN_ERR DRIVER_NAME ": "
			"No SRAM found in device tree\n");
		rv = -ENODEV;
		जाओ error_ofput;
	पूर्ण
	rv = bcom_sram_init(ofn_sram, DRIVER_NAME);
	of_node_put(ofn_sram);

	अगर (rv) अणु
		prपूर्णांकk(KERN_ERR DRIVER_NAME ": "
			"Error in SRAM init\n");
		जाओ error_ofput;
	पूर्ण

	/* Get a clean काष्ठा */
	bcom_eng = kzalloc(माप(काष्ठा bcom_engine), GFP_KERNEL);
	अगर (!bcom_eng) अणु
		rv = -ENOMEM;
		जाओ error_sramclean;
	पूर्ण

	/* Save the node */
	bcom_eng->ofnode = op->dev.of_node;

	/* Get, reserve & map io */
	अगर (of_address_to_resource(op->dev.of_node, 0, &res_bcom)) अणु
		prपूर्णांकk(KERN_ERR DRIVER_NAME ": "
			"Can't get resource\n");
		rv = -EINVAL;
		जाओ error_sramclean;
	पूर्ण

	अगर (!request_mem_region(res_bcom.start, resource_size(&res_bcom),
				DRIVER_NAME)) अणु
		prपूर्णांकk(KERN_ERR DRIVER_NAME ": "
			"Can't request registers region\n");
		rv = -EBUSY;
		जाओ error_sramclean;
	पूर्ण

	bcom_eng->regs_base = res_bcom.start;
	bcom_eng->regs = ioremap(res_bcom.start, माप(काष्ठा mpc52xx_sdma));
	अगर (!bcom_eng->regs) अणु
		prपूर्णांकk(KERN_ERR DRIVER_NAME ": "
			"Can't map registers\n");
		rv = -ENOMEM;
		जाओ error_release;
	पूर्ण

	/* Now, करो the real init */
	rv = bcom_engine_init();
	अगर (rv)
		जाओ error_unmap;

	/* Done ! */
	prपूर्णांकk(KERN_INFO "DMA: MPC52xx BestComm engine @%08lx ok !\n",
		(दीर्घ)bcom_eng->regs_base);

	वापस 0;

	/* Error path */
error_unmap:
	iounmap(bcom_eng->regs);
error_release:
	release_mem_region(res_bcom.start, माप(काष्ठा mpc52xx_sdma));
error_sramclean:
	kमुक्त(bcom_eng);
	bcom_sram_cleanup();
error_ofput:
	of_node_put(op->dev.of_node);

	prपूर्णांकk(KERN_ERR "DMA: MPC52xx BestComm init failed !\n");

	वापस rv;
पूर्ण


अटल पूर्णांक mpc52xx_bcom_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	/* Clean up the engine */
	bcom_engine_cleanup();

	/* Cleanup SRAM */
	bcom_sram_cleanup();

	/* Release regs */
	iounmap(bcom_eng->regs);
	release_mem_region(bcom_eng->regs_base, माप(काष्ठा mpc52xx_sdma));

	/* Release the node */
	of_node_put(bcom_eng->ofnode);

	/* Release memory */
	kमुक्त(bcom_eng);
	bcom_eng = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc52xx_bcom_of_match[] = अणु
	अणु .compatible = "fsl,mpc5200-bestcomm", पूर्ण,
	अणु .compatible = "mpc5200-bestcomm", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, mpc52xx_bcom_of_match);


अटल काष्ठा platक्रमm_driver mpc52xx_bcom_of_platक्रमm_driver = अणु
	.probe		= mpc52xx_bcom_probe,
	.हटाओ		= mpc52xx_bcom_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = mpc52xx_bcom_of_match,
	पूर्ण,
पूर्ण;


/* ======================================================================== */
/* Module                                                                   */
/* ======================================================================== */

अटल पूर्णांक __init
mpc52xx_bcom_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mpc52xx_bcom_of_platक्रमm_driver);
पूर्ण

अटल व्योम __निकास
mpc52xx_bcom_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mpc52xx_bcom_of_platक्रमm_driver);
पूर्ण

/* If we're not a module, we must make sure everything is setup beक्रमe  */
/* anyone tries to use us ... that's why we use subsys_initcall instead */
/* of module_init. */
subsys_initcall(mpc52xx_bcom_init);
module_निकास(mpc52xx_bcom_निकास);

MODULE_DESCRIPTION("Freescale MPC52xx BestComm DMA");
MODULE_AUTHOR("Sylvain Munaut <tnt@246tNt.com>");
MODULE_AUTHOR("Andrey Volkov <avolkov@varma-el.com>");
MODULE_AUTHOR("Dale Farnsworth <dfarnsworth@mvista.com>");
MODULE_LICENSE("GPL v2");

