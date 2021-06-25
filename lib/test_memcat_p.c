<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test हालs क्रम memcat_p() in lib/memcat_p.c
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

काष्ठा test_काष्ठा अणु
	पूर्णांक		num;
	अचिन्हित पूर्णांक	magic;
पूर्ण;

#घोषणा MAGIC		0xf00ff00f
/* Size of each of the शून्य-terminated input arrays */
#घोषणा INPUT_MAX	128
/* Expected number of non-शून्य elements in the output array */
#घोषणा EXPECT		(INPUT_MAX * 2 - 2)

अटल पूर्णांक __init test_memcat_p_init(व्योम)
अणु
	काष्ठा test_काष्ठा **in0, **in1, **out, **p;
	पूर्णांक err = -ENOMEM, i, r, total = 0;

	in0 = kसुस्मृति(INPUT_MAX, माप(*in0), GFP_KERNEL);
	अगर (!in0)
		वापस err;

	in1 = kसुस्मृति(INPUT_MAX, माप(*in1), GFP_KERNEL);
	अगर (!in1)
		जाओ err_मुक्त_in0;

	क्रम (i = 0, r = 1; i < INPUT_MAX - 1; i++) अणु
		in0[i] = kदो_स्मृति(माप(**in0), GFP_KERNEL);
		अगर (!in0[i])
			जाओ err_मुक्त_elements;

		in1[i] = kदो_स्मृति(माप(**in1), GFP_KERNEL);
		अगर (!in1[i]) अणु
			kमुक्त(in0[i]);
			जाओ err_मुक्त_elements;
		पूर्ण

		/* lअगरted from test_sort.c */
		r = (r * 725861) % 6599;
		in0[i]->num = r;
		in1[i]->num = -r;
		in0[i]->magic = MAGIC;
		in1[i]->magic = MAGIC;
	पूर्ण

	in0[i] = in1[i] = शून्य;

	out = memcat_p(in0, in1);
	अगर (!out)
		जाओ err_मुक्त_all_elements;

	err = -EINVAL;
	क्रम (i = 0, p = out; *p && (i < INPUT_MAX * 2 - 1); p++, i++) अणु
		total += (*p)->num;

		अगर ((*p)->magic != MAGIC) अणु
			pr_err("test failed: wrong magic at %d: %u\n", i,
			       (*p)->magic);
			जाओ err_मुक्त_out;
		पूर्ण
	पूर्ण

	अगर (total) अणु
		pr_err("test failed: expected zero total, got %d\n", total);
		जाओ err_मुक्त_out;
	पूर्ण

	अगर (i != EXPECT) अणु
		pr_err("test failed: expected output size %d, got %d\n",
		       EXPECT, i);
		जाओ err_मुक्त_out;
	पूर्ण

	क्रम (i = 0; i < INPUT_MAX - 1; i++)
		अगर (out[i] != in0[i] || out[i + INPUT_MAX - 1] != in1[i]) अणु
			pr_err("test failed: wrong element order at %d\n", i);
			जाओ err_मुक्त_out;
		पूर्ण

	err = 0;
	pr_info("test passed\n");

err_मुक्त_out:
	kमुक्त(out);
err_मुक्त_all_elements:
	i = INPUT_MAX;
err_मुक्त_elements:
	क्रम (i--; i >= 0; i--) अणु
		kमुक्त(in1[i]);
		kमुक्त(in0[i]);
	पूर्ण

	kमुक्त(in1);
err_मुक्त_in0:
	kमुक्त(in0);

	वापस err;
पूर्ण

अटल व्योम __निकास test_memcat_p_निकास(व्योम)
अणु
पूर्ण

module_init(test_memcat_p_init);
module_निकास(test_memcat_p_निकास);

MODULE_LICENSE("GPL");
