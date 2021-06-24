<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * xor.c : Multiple Devices driver क्रम Linux
 *
 * Copyright (C) 1996, 1997, 1998, 1999, 2000,
 * Ingo Molnar, Matti Aarnio, Jakub Jelinek, Riअक्षरd Henderson.
 *
 * Dispatch optimized RAID-5 checksumming functions.
 */

#घोषणा BH_TRACE 0
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/raid/xor.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/preempt.h>
#समावेश <यंत्र/xor.h>

#अगर_अघोषित XOR_SELECT_TEMPLATE
#घोषणा XOR_SELECT_TEMPLATE(x) (x)
#पूर्ण_अगर

/* The xor routines to use.  */
अटल काष्ठा xor_block_ढाँचा *active_ढाँचा;

व्योम
xor_blocks(अचिन्हित पूर्णांक src_count, अचिन्हित पूर्णांक bytes, व्योम *dest, व्योम **srcs)
अणु
	अचिन्हित दीर्घ *p1, *p2, *p3, *p4;

	p1 = (अचिन्हित दीर्घ *) srcs[0];
	अगर (src_count == 1) अणु
		active_ढाँचा->करो_2(bytes, dest, p1);
		वापस;
	पूर्ण

	p2 = (अचिन्हित दीर्घ *) srcs[1];
	अगर (src_count == 2) अणु
		active_ढाँचा->करो_3(bytes, dest, p1, p2);
		वापस;
	पूर्ण

	p3 = (अचिन्हित दीर्घ *) srcs[2];
	अगर (src_count == 3) अणु
		active_ढाँचा->करो_4(bytes, dest, p1, p2, p3);
		वापस;
	पूर्ण

	p4 = (अचिन्हित दीर्घ *) srcs[3];
	active_ढाँचा->करो_5(bytes, dest, p1, p2, p3, p4);
पूर्ण
EXPORT_SYMBOL(xor_blocks);

/* Set of all रेजिस्टरed ढाँचाs.  */
अटल काष्ठा xor_block_ढाँचा *__initdata ढाँचा_list;

#अगर_अघोषित MODULE
अटल व्योम __init करो_xor_रेजिस्टर(काष्ठा xor_block_ढाँचा *पंचांगpl)
अणु
	पंचांगpl->next = ढाँचा_list;
	ढाँचा_list = पंचांगpl;
पूर्ण

अटल पूर्णांक __init रेजिस्टर_xor_blocks(व्योम)
अणु
	active_ढाँचा = XOR_SELECT_TEMPLATE(शून्य);

	अगर (!active_ढाँचा) अणु
#घोषणा xor_speed	करो_xor_रेजिस्टर
		// रेजिस्टर all the ढाँचाs and pick the first as the शेष
		XOR_TRY_TEMPLATES;
#अघोषित xor_speed
		active_ढाँचा = ढाँचा_list;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा BENCH_SIZE	4096
#घोषणा REPS		800U

अटल व्योम __init
करो_xor_speed(काष्ठा xor_block_ढाँचा *पंचांगpl, व्योम *b1, व्योम *b2)
अणु
	पूर्णांक speed;
	पूर्णांक i, j;
	kसमय_प्रकार min, start, dअगरf;

	पंचांगpl->next = ढाँचा_list;
	ढाँचा_list = पंचांगpl;

	preempt_disable();

	min = (kसमय_प्रकार)S64_MAX;
	क्रम (i = 0; i < 3; i++) अणु
		start = kसमय_get();
		क्रम (j = 0; j < REPS; j++) अणु
			mb(); /* prevent loop optimization */
			पंचांगpl->करो_2(BENCH_SIZE, b1, b2);
			mb();
		पूर्ण
		dअगरf = kसमय_sub(kसमय_get(), start);
		अगर (dअगरf < min)
			min = dअगरf;
	पूर्ण

	preempt_enable();

	// bytes/ns == GB/s, multiply by 1000 to get MB/s [not MiB/s]
	अगर (!min)
		min = 1;
	speed = (1000 * REPS * BENCH_SIZE) / (अचिन्हित पूर्णांक)kसमय_प्रकारo_ns(min);
	पंचांगpl->speed = speed;

	pr_info("   %-16s: %5d MB/sec\n", पंचांगpl->name, speed);
पूर्ण

अटल पूर्णांक __init
calibrate_xor_blocks(व्योम)
अणु
	व्योम *b1, *b2;
	काष्ठा xor_block_ढाँचा *f, *fastest;

	fastest = XOR_SELECT_TEMPLATE(शून्य);

	अगर (fastest) अणु
		prपूर्णांकk(KERN_INFO "xor: automatically using best "
				 "checksumming function   %-10s\n",
		       fastest->name);
		जाओ out;
	पूर्ण

	b1 = (व्योम *) __get_मुक्त_pages(GFP_KERNEL, 2);
	अगर (!b1) अणु
		prपूर्णांकk(KERN_WARNING "xor: Yikes!  No memory available.\n");
		वापस -ENOMEM;
	पूर्ण
	b2 = b1 + 2*PAGE_SIZE + BENCH_SIZE;

	/*
	 * If this arch/cpu has a लघु-circuited selection, करोn't loop through
	 * all the possible functions, just test the best one
	 */

#घोषणा xor_speed(templ)	करो_xor_speed((templ), b1, b2)

	prपूर्णांकk(KERN_INFO "xor: measuring software checksum speed\n");
	ढाँचा_list = शून्य;
	XOR_TRY_TEMPLATES;
	fastest = ढाँचा_list;
	क्रम (f = fastest; f; f = f->next)
		अगर (f->speed > fastest->speed)
			fastest = f;

	pr_info("xor: using function: %s (%d MB/sec)\n",
	       fastest->name, fastest->speed);

#अघोषित xor_speed

	मुक्त_pages((अचिन्हित दीर्घ)b1, 2);
out:
	active_ढाँचा = fastest;
	वापस 0;
पूर्ण

अटल __निकास व्योम xor_निकास(व्योम) अणु पूर्ण

MODULE_LICENSE("GPL");

#अगर_अघोषित MODULE
/* when built-in xor.o must initialize beक्रमe drivers/md/md.o */
core_initcall(रेजिस्टर_xor_blocks);
#पूर्ण_अगर

module_init(calibrate_xor_blocks);
module_निकास(xor_निकास);
