<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017 IBM Corp.
#समावेश "ocxl_internal.h"


काष्ठा id_range अणु
	काष्ठा list_head list;
	u32 start;
	u32 end;
पूर्ण;

#अगर_घोषित DEBUG
अटल व्योम dump_list(काष्ठा list_head *head, अक्षर *type_str)
अणु
	काष्ठा id_range *cur;

	pr_debug("%s ranges allocated:\n", type_str);
	list_क्रम_each_entry(cur, head, list) अणु
		pr_debug("Range %d->%d\n", cur->start, cur->end);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक range_alloc(काष्ठा list_head *head, u32 size, पूर्णांक max_id,
		अक्षर *type_str)
अणु
	काष्ठा list_head *pos;
	काष्ठा id_range *cur, *new;
	पूर्णांक rc, last_end;

	new = kदो_स्मृति(माप(काष्ठा id_range), GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;

	pos = head;
	last_end = -1;
	list_क्रम_each_entry(cur, head, list) अणु
		अगर ((cur->start - last_end) > size)
			अवरोध;
		last_end = cur->end;
		pos = &cur->list;
	पूर्ण

	new->start = last_end + 1;
	new->end = new->start + size - 1;

	अगर (new->end > max_id) अणु
		kमुक्त(new);
		rc = -ENOSPC;
	पूर्ण अन्यथा अणु
		list_add(&new->list, pos);
		rc = new->start;
	पूर्ण

#अगर_घोषित DEBUG
	dump_list(head, type_str);
#पूर्ण_अगर
	वापस rc;
पूर्ण

अटल व्योम range_मुक्त(काष्ठा list_head *head, u32 start, u32 size,
		अक्षर *type_str)
अणु
	bool found = false;
	काष्ठा id_range *cur, *पंचांगp;

	list_क्रम_each_entry_safe(cur, पंचांगp, head, list) अणु
		अगर (cur->start == start && cur->end == (start + size - 1)) अणु
			found = true;
			list_del(&cur->list);
			kमुक्त(cur);
			अवरोध;
		पूर्ण
	पूर्ण
	WARN_ON(!found);
#अगर_घोषित DEBUG
	dump_list(head, type_str);
#पूर्ण_अगर
पूर्ण

पूर्णांक ocxl_pasid_afu_alloc(काष्ठा ocxl_fn *fn, u32 size)
अणु
	पूर्णांक max_pasid;

	अगर (fn->config.max_pasid_log < 0)
		वापस -ENOSPC;
	max_pasid = 1 << fn->config.max_pasid_log;
	वापस range_alloc(&fn->pasid_list, size, max_pasid, "afu pasid");
पूर्ण

व्योम ocxl_pasid_afu_मुक्त(काष्ठा ocxl_fn *fn, u32 start, u32 size)
अणु
	वापस range_मुक्त(&fn->pasid_list, start, size, "afu pasid");
पूर्ण

पूर्णांक ocxl_actag_afu_alloc(काष्ठा ocxl_fn *fn, u32 size)
अणु
	पूर्णांक max_actag;

	max_actag = fn->actag_enabled;
	वापस range_alloc(&fn->actag_list, size, max_actag, "afu actag");
पूर्ण

व्योम ocxl_actag_afu_मुक्त(काष्ठा ocxl_fn *fn, u32 start, u32 size)
अणु
	वापस range_मुक्त(&fn->actag_list, start, size, "afu actag");
पूर्ण
