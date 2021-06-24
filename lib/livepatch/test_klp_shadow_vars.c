<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Joe Lawrence <joe.lawrence@redhat.com>

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/livepatch.h>
#समावेश <linux/slab.h>

/*
 * Keep a small list of poपूर्णांकers so that we can prपूर्णांक address-agnostic
 * poपूर्णांकer values.  Use a rolling पूर्णांकeger count to dअगरferentiate the values.
 * Ironically we could have used the shaकरोw variable API to करो this, but
 * let's not lean too heavily on the very code we're testing.
 */
अटल LIST_HEAD(ptr_list);
काष्ठा shaकरोw_ptr अणु
	व्योम *ptr;
	पूर्णांक id;
	काष्ठा list_head list;
पूर्ण;

अटल व्योम मुक्त_ptr_list(व्योम)
अणु
	काष्ठा shaकरोw_ptr *sp, *पंचांगp_sp;

	list_क्रम_each_entry_safe(sp, पंचांगp_sp, &ptr_list, list) अणु
		list_del(&sp->list);
		kमुक्त(sp);
	पूर्ण
पूर्ण

अटल पूर्णांक ptr_id(व्योम *ptr)
अणु
	काष्ठा shaकरोw_ptr *sp;
	अटल पूर्णांक count;

	list_क्रम_each_entry(sp, &ptr_list, list) अणु
		अगर (sp->ptr == ptr)
			वापस sp->id;
	पूर्ण

	sp = kदो_स्मृति(माप(*sp), GFP_ATOMIC);
	अगर (!sp)
		वापस -ENOMEM;
	sp->ptr = ptr;
	sp->id = count++;

	list_add(&sp->list, &ptr_list);

	वापस sp->id;
पूर्ण

/*
 * Shaकरोw variable wrapper functions that echo the function and arguments
 * to the kernel log क्रम testing verअगरication.  Don't display raw poपूर्णांकers,
 * but use the ptr_id() value instead.
 */
अटल व्योम *shaकरोw_get(व्योम *obj, अचिन्हित दीर्घ id)
अणु
	पूर्णांक **sv;

	sv = klp_shaकरोw_get(obj, id);
	pr_info("klp_%s(obj=PTR%d, id=0x%lx) = PTR%d\n",
		__func__, ptr_id(obj), id, ptr_id(sv));

	वापस sv;
पूर्ण

अटल व्योम *shaकरोw_alloc(व्योम *obj, अचिन्हित दीर्घ id, माप_प्रकार size,
			  gfp_t gfp_flags, klp_shaकरोw_ctor_t ctor,
			  व्योम *ctor_data)
अणु
	पूर्णांक **var = ctor_data;
	पूर्णांक **sv;

	sv = klp_shaकरोw_alloc(obj, id, size, gfp_flags, ctor, var);
	pr_info("klp_%s(obj=PTR%d, id=0x%lx, size=%zx, gfp_flags=%pGg), ctor=PTR%d, ctor_data=PTR%d = PTR%d\n",
		__func__, ptr_id(obj), id, size, &gfp_flags, ptr_id(ctor),
		ptr_id(*var), ptr_id(sv));

	वापस sv;
पूर्ण

अटल व्योम *shaकरोw_get_or_alloc(व्योम *obj, अचिन्हित दीर्घ id, माप_प्रकार size,
				 gfp_t gfp_flags, klp_shaकरोw_ctor_t ctor,
				 व्योम *ctor_data)
अणु
	पूर्णांक **var = ctor_data;
	पूर्णांक **sv;

	sv = klp_shaकरोw_get_or_alloc(obj, id, size, gfp_flags, ctor, var);
	pr_info("klp_%s(obj=PTR%d, id=0x%lx, size=%zx, gfp_flags=%pGg), ctor=PTR%d, ctor_data=PTR%d = PTR%d\n",
		__func__, ptr_id(obj), id, size, &gfp_flags, ptr_id(ctor),
		ptr_id(*var), ptr_id(sv));

	वापस sv;
पूर्ण

अटल व्योम shaकरोw_मुक्त(व्योम *obj, अचिन्हित दीर्घ id, klp_shaकरोw_dtor_t dtor)
अणु
	klp_shaकरोw_मुक्त(obj, id, dtor);
	pr_info("klp_%s(obj=PTR%d, id=0x%lx, dtor=PTR%d)\n",
		__func__, ptr_id(obj), id, ptr_id(dtor));
पूर्ण

अटल व्योम shaकरोw_मुक्त_all(अचिन्हित दीर्घ id, klp_shaकरोw_dtor_t dtor)
अणु
	klp_shaकरोw_मुक्त_all(id, dtor);
	pr_info("klp_%s(id=0x%lx, dtor=PTR%d)\n", __func__, id, ptr_id(dtor));
पूर्ण


/* Shaकरोw variable स्थिरructor - remember simple poपूर्णांकer data */
अटल पूर्णांक shaकरोw_ctor(व्योम *obj, व्योम *shaकरोw_data, व्योम *ctor_data)
अणु
	पूर्णांक **sv = shaकरोw_data;
	पूर्णांक **var = ctor_data;

	अगर (!var)
		वापस -EINVAL;

	*sv = *var;
	pr_info("%s: PTR%d -> PTR%d\n", __func__, ptr_id(sv), ptr_id(*var));

	वापस 0;
पूर्ण

/*
 * With more than one item to मुक्त in the list, order is not determined and
 * shaकरोw_dtor will not be passed to shaकरोw_मुक्त_all() which would make the
 * test fail. (see pass 6)
 */
अटल व्योम shaकरोw_dtor(व्योम *obj, व्योम *shaकरोw_data)
अणु
	पूर्णांक **sv = shaकरोw_data;

	pr_info("%s(obj=PTR%d, shadow_data=PTR%d)\n",
		__func__, ptr_id(obj), ptr_id(sv));
पूर्ण

/* number of objects we simulate that need shaकरोw vars */
#घोषणा NUM_OBJS 3

/* dynamically created obj fields have the following shaकरोw var id values */
#घोषणा SV_ID1 0x1234
#घोषणा SV_ID2 0x1235

/*
 * The मुख्य test हाल adds/हटाओs new fields (shaकरोw var) to each of these
 * test काष्ठाure instances. The last group of fields in the काष्ठा represent
 * the idea that shaकरोw variables may be added and हटाओd to and from the
 * काष्ठा during execution.
 */
काष्ठा test_object अणु
	 /* add anything here below and aव्योम to define an empty काष्ठा */
	काष्ठा shaकरोw_ptr sp;

	/* these represent shaकरोw vars added and हटाओd with SV_IDअणु1,2पूर्ण */
	/* अक्षर nfield1; */
	/* पूर्णांक  nfield2; */
पूर्ण;

अटल पूर्णांक test_klp_shaकरोw_vars_init(व्योम)
अणु
	काष्ठा test_object objs[NUM_OBJS];
	अक्षर nfields1[NUM_OBJS], *pnfields1[NUM_OBJS], **sv1[NUM_OBJS];
	अक्षर *pndup[NUM_OBJS];
	पूर्णांक nfields2[NUM_OBJS], *pnfields2[NUM_OBJS], **sv2[NUM_OBJS];
	व्योम **sv;
	पूर्णांक ret;
	पूर्णांक i;

	ptr_id(शून्य);

	/*
	 * With an empty shaकरोw variable hash table, expect not to find
	 * any matches.
	 */
	sv = shaकरोw_get(&objs[0], SV_ID1);
	अगर (!sv)
		pr_info("  got expected NULL result\n");

	/* pass 1: init & alloc a अक्षर+पूर्णांक pair of svars क्रम each objs */
	क्रम (i = 0; i < NUM_OBJS; i++) अणु
		pnfields1[i] = &nfields1[i];
		ptr_id(pnfields1[i]);

		अगर (i % 2) अणु
			sv1[i] = shaकरोw_alloc(&objs[i], SV_ID1,
					माप(pnfields1[i]), GFP_KERNEL,
					shaकरोw_ctor, &pnfields1[i]);
		पूर्ण अन्यथा अणु
			sv1[i] = shaकरोw_get_or_alloc(&objs[i], SV_ID1,
					माप(pnfields1[i]), GFP_KERNEL,
					shaकरोw_ctor, &pnfields1[i]);
		पूर्ण
		अगर (!sv1[i]) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		pnfields2[i] = &nfields2[i];
		ptr_id(pnfields2[i]);
		sv2[i] = shaकरोw_alloc(&objs[i], SV_ID2, माप(pnfields2[i]),
					GFP_KERNEL, shaकरोw_ctor, &pnfields2[i]);
		अगर (!sv2[i]) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	/* pass 2: verअगरy we find allocated svars and where they poपूर्णांक to */
	क्रम (i = 0; i < NUM_OBJS; i++) अणु
		/* check the "char" svar क्रम all objects */
		sv = shaकरोw_get(&objs[i], SV_ID1);
		अगर (!sv) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अगर ((अक्षर **)sv == sv1[i] && *sv1[i] == pnfields1[i])
			pr_info("  got expected PTR%d -> PTR%d result\n",
				ptr_id(sv1[i]), ptr_id(*sv1[i]));

		/* check the "int" svar क्रम all objects */
		sv = shaकरोw_get(&objs[i], SV_ID2);
		अगर (!sv) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अगर ((पूर्णांक **)sv == sv2[i] && *sv2[i] == pnfields2[i])
			pr_info("  got expected PTR%d -> PTR%d result\n",
				ptr_id(sv2[i]), ptr_id(*sv2[i]));
	पूर्ण

	/* pass 3: verअगरy that 'get_or_alloc' वापसs alपढ़ोy allocated svars */
	क्रम (i = 0; i < NUM_OBJS; i++) अणु
		pndup[i] = &nfields1[i];
		ptr_id(pndup[i]);

		sv = shaकरोw_get_or_alloc(&objs[i], SV_ID1, माप(pndup[i]),
					GFP_KERNEL, shaकरोw_ctor, &pndup[i]);
		अगर (!sv) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अगर ((अक्षर **)sv == sv1[i] && *sv1[i] == pnfields1[i])
			pr_info("  got expected PTR%d -> PTR%d result\n",
					ptr_id(sv1[i]), ptr_id(*sv1[i]));
	पूर्ण

	/* pass 4: मुक्त <objs[*], SV_ID1> pairs of svars, verअगरy removal */
	क्रम (i = 0; i < NUM_OBJS; i++) अणु
		shaकरोw_मुक्त(&objs[i], SV_ID1, shaकरोw_dtor); /* 'char' pairs */
		sv = shaकरोw_get(&objs[i], SV_ID1);
		अगर (!sv)
			pr_info("  got expected NULL result\n");
	पूर्ण

	/* pass 5: check we still find <objs[*], SV_ID2> svar pairs */
	क्रम (i = 0; i < NUM_OBJS; i++) अणु
		sv = shaकरोw_get(&objs[i], SV_ID2);	/* 'int' pairs */
		अगर (!sv) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अगर ((पूर्णांक **)sv == sv2[i] && *sv2[i] == pnfields2[i])
			pr_info("  got expected PTR%d -> PTR%d result\n",
					ptr_id(sv2[i]), ptr_id(*sv2[i]));
	पूर्ण

	/* pass 6: मुक्त all the <objs[*], SV_ID2> svar pairs too. */
	shaकरोw_मुक्त_all(SV_ID2, शून्य);		/* 'int' pairs */
	क्रम (i = 0; i < NUM_OBJS; i++) अणु
		sv = shaकरोw_get(&objs[i], SV_ID2);
		अगर (!sv)
			pr_info("  got expected NULL result\n");
	पूर्ण

	मुक्त_ptr_list();

	वापस 0;
out:
	shaकरोw_मुक्त_all(SV_ID1, शून्य);		/* 'char' pairs */
	shaकरोw_मुक्त_all(SV_ID2, शून्य);		/* 'int' pairs */
	मुक्त_ptr_list();

	वापस ret;
पूर्ण

अटल व्योम test_klp_shaकरोw_vars_निकास(व्योम)
अणु
पूर्ण

module_init(test_klp_shaकरोw_vars_init);
module_निकास(test_klp_shaकरोw_vars_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joe Lawrence <joe.lawrence@redhat.com>");
MODULE_DESCRIPTION("Livepatch test: shadow variables");
