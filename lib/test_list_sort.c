<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) "list_sort_test: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>

/*
 * The pattern of set bits in the list length determines which हालs
 * are hit in list_sort().
 */
#घोषणा TEST_LIST_LEN (512+128+2) /* not including head */

#घोषणा TEST_POISON1 0xDEADBEEF
#घोषणा TEST_POISON2 0xA324354C

काष्ठा debug_el अणु
	अचिन्हित पूर्णांक poison1;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक poison2;
	पूर्णांक value;
	अचिन्हित serial;
पूर्ण;

/* Array, containing poपूर्णांकers to all elements in the test list */
अटल काष्ठा debug_el **elts __initdata;

अटल पूर्णांक __init check(काष्ठा debug_el *ela, काष्ठा debug_el *elb)
अणु
	अगर (ela->serial >= TEST_LIST_LEN) अणु
		pr_err("error: incorrect serial %d\n", ela->serial);
		वापस -EINVAL;
	पूर्ण
	अगर (elb->serial >= TEST_LIST_LEN) अणु
		pr_err("error: incorrect serial %d\n", elb->serial);
		वापस -EINVAL;
	पूर्ण
	अगर (elts[ela->serial] != ela || elts[elb->serial] != elb) अणु
		pr_err("error: phantom element\n");
		वापस -EINVAL;
	पूर्ण
	अगर (ela->poison1 != TEST_POISON1 || ela->poison2 != TEST_POISON2) अणु
		pr_err("error: bad poison: %#x/%#x\n",
			ela->poison1, ela->poison2);
		वापस -EINVAL;
	पूर्ण
	अगर (elb->poison1 != TEST_POISON1 || elb->poison2 != TEST_POISON2) अणु
		pr_err("error: bad poison: %#x/%#x\n",
			elb->poison1, elb->poison2);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
		      स्थिर काष्ठा list_head *b)
अणु
	काष्ठा debug_el *ela, *elb;

	ela = container_of(a, काष्ठा debug_el, list);
	elb = container_of(b, काष्ठा debug_el, list);

	check(ela, elb);
	वापस ela->value - elb->value;
पूर्ण

अटल पूर्णांक __init list_sort_test(व्योम)
अणु
	पूर्णांक i, count = 1, err = -ENOMEM;
	काष्ठा debug_el *el;
	काष्ठा list_head *cur;
	LIST_HEAD(head);

	pr_debug("start testing list_sort()\n");

	elts = kसुस्मृति(TEST_LIST_LEN, माप(*elts), GFP_KERNEL);
	अगर (!elts)
		वापस err;

	क्रम (i = 0; i < TEST_LIST_LEN; i++) अणु
		el = kदो_स्मृति(माप(*el), GFP_KERNEL);
		अगर (!el)
			जाओ निकास;

		 /* क्रमce some equivalencies */
		el->value = pअक्रमom_u32() % (TEST_LIST_LEN / 3);
		el->serial = i;
		el->poison1 = TEST_POISON1;
		el->poison2 = TEST_POISON2;
		elts[i] = el;
		list_add_tail(&el->list, &head);
	पूर्ण

	list_sort(शून्य, &head, cmp);

	err = -EINVAL;
	क्रम (cur = head.next; cur->next != &head; cur = cur->next) अणु
		काष्ठा debug_el *el1;
		पूर्णांक cmp_result;

		अगर (cur->next->prev != cur) अणु
			pr_err("error: list is corrupted\n");
			जाओ निकास;
		पूर्ण

		cmp_result = cmp(शून्य, cur, cur->next);
		अगर (cmp_result > 0) अणु
			pr_err("error: list is not sorted\n");
			जाओ निकास;
		पूर्ण

		el = container_of(cur, काष्ठा debug_el, list);
		el1 = container_of(cur->next, काष्ठा debug_el, list);
		अगर (cmp_result == 0 && el->serial >= el1->serial) अणु
			pr_err("error: order of equivalent elements not "
				"preserved\n");
			जाओ निकास;
		पूर्ण

		अगर (check(el, el1)) अणु
			pr_err("error: element check failed\n");
			जाओ निकास;
		पूर्ण
		count++;
	पूर्ण
	अगर (head.prev != cur) अणु
		pr_err("error: list is corrupted\n");
		जाओ निकास;
	पूर्ण


	अगर (count != TEST_LIST_LEN) अणु
		pr_err("error: bad list length %d", count);
		जाओ निकास;
	पूर्ण

	err = 0;
निकास:
	क्रम (i = 0; i < TEST_LIST_LEN; i++)
		kमुक्त(elts[i]);
	kमुक्त(elts);
	वापस err;
पूर्ण
module_init(list_sort_test);
MODULE_LICENSE("GPL");
