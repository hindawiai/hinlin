<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sample fअगरo dma implementation
 *
 * Copyright (C) 2010 Stefani Seibold <stefani@seibold.net>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kfअगरo.h>

/*
 * This module shows how to handle fअगरo dma operations.
 */

/* fअगरo size in elements (bytes) */
#घोषणा FIFO_SIZE	32

अटल काष्ठा kfअगरo fअगरo;

अटल पूर्णांक __init example_init(व्योम)
अणु
	पूर्णांक			i;
	अचिन्हित पूर्णांक		ret;
	अचिन्हित पूर्णांक		nents;
	काष्ठा scatterlist	sg[10];

	prपूर्णांकk(KERN_INFO "DMA fifo test start\n");

	अगर (kfअगरo_alloc(&fअगरo, FIFO_SIZE, GFP_KERNEL)) अणु
		prपूर्णांकk(KERN_WARNING "error kfifo_alloc\n");
		वापस -ENOMEM;
	पूर्ण

	prपूर्णांकk(KERN_INFO "queue size: %u\n", kfअगरo_size(&fअगरo));

	kfअगरo_in(&fअगरo, "test", 4);

	क्रम (i = 0; i != 9; i++)
		kfअगरo_put(&fअगरo, i);

	/* kick away first byte */
	kfअगरo_skip(&fअगरo);

	prपूर्णांकk(KERN_INFO "queue len: %u\n", kfअगरo_len(&fअगरo));

	/*
	 * Configure the kfअगरo buffer to receive data from DMA input.
	 *
	 *  .--------------------------------------.
	 *  | 0 | 1 | 2 | ... | 12 | 13 | ... | 31 |
	 *  |---|------------------|---------------|
	 *   \_/ \________________/ \_____________/
	 *    \          \                  \
	 *     \          \_allocated data   \
	 *      \_*मुक्त space*                \_*मुक्त space*
	 *
	 * We need two dअगरferent SG entries: one क्रम the मुक्त space area at the
	 * end of the kfअगरo buffer (19 bytes) and another क्रम the first मुक्त
	 * byte at the beginning, after the kfअगरo_skip().
	 */
	sg_init_table(sg, ARRAY_SIZE(sg));
	nents = kfअगरo_dma_in_prepare(&fअगरo, sg, ARRAY_SIZE(sg), FIFO_SIZE);
	prपूर्णांकk(KERN_INFO "DMA sgl entries: %d\n", nents);
	अगर (!nents) अणु
		/* fअगरo is full and no sgl was created */
		prपूर्णांकk(KERN_WARNING "error kfifo_dma_in_prepare\n");
		वापस -EIO;
	पूर्ण

	/* receive data */
	prपूर्णांकk(KERN_INFO "scatterlist for receive:\n");
	क्रम (i = 0; i < nents; i++) अणु
		prपूर्णांकk(KERN_INFO
		"sg[%d] -> "
		"page %p offset 0x%.8x length 0x%.8x\n",
			i, sg_page(&sg[i]), sg[i].offset, sg[i].length);

		अगर (sg_is_last(&sg[i]))
			अवरोध;
	पूर्ण

	/* put here your code to setup and exectute the dma operation */
	/* ... */

	/* example: zero bytes received */
	ret = 0;

	/* finish the dma operation and update the received data */
	kfअगरo_dma_in_finish(&fअगरo, ret);

	/* Prepare to transmit data, example: 8 bytes */
	nents = kfअगरo_dma_out_prepare(&fअगरo, sg, ARRAY_SIZE(sg), 8);
	prपूर्णांकk(KERN_INFO "DMA sgl entries: %d\n", nents);
	अगर (!nents) अणु
		/* no data was available and no sgl was created */
		prपूर्णांकk(KERN_WARNING "error kfifo_dma_out_prepare\n");
		वापस -EIO;
	पूर्ण

	prपूर्णांकk(KERN_INFO "scatterlist for transmit:\n");
	क्रम (i = 0; i < nents; i++) अणु
		prपूर्णांकk(KERN_INFO
		"sg[%d] -> "
		"page %p offset 0x%.8x length 0x%.8x\n",
			i, sg_page(&sg[i]), sg[i].offset, sg[i].length);

		अगर (sg_is_last(&sg[i]))
			अवरोध;
	पूर्ण

	/* put here your code to setup and exectute the dma operation */
	/* ... */

	/* example: 5 bytes transmitted */
	ret = 5;

	/* finish the dma operation and update the transmitted data */
	kfअगरo_dma_out_finish(&fअगरo, ret);

	ret = kfअगरo_len(&fअगरo);
	prपूर्णांकk(KERN_INFO "queue len: %u\n", kfअगरo_len(&fअगरo));

	अगर (ret != 7) अणु
		prपूर्णांकk(KERN_WARNING "size mismatch: test failed");
		वापस -EIO;
	पूर्ण
	prपूर्णांकk(KERN_INFO "test passed\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास example_निकास(व्योम)
अणु
	kfअगरo_मुक्त(&fअगरo);
पूर्ण

module_init(example_init);
module_निकास(example_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stefani Seibold <stefani@seibold.net>");
