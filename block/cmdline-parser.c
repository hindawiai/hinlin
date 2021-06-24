<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Parse command line, get partition inक्रमmation
 *
 * Written by Cai Zhiyong <caizhiyong@huawei.com>
 *
 */
#समावेश <linux/export.h>
#समावेश <linux/cmdline-parser.h>

अटल पूर्णांक parse_subpart(काष्ठा cmdline_subpart **subpart, अक्षर *partdef)
अणु
	पूर्णांक ret = 0;
	काष्ठा cmdline_subpart *new_subpart;

	*subpart = शून्य;

	new_subpart = kzalloc(माप(काष्ठा cmdline_subpart), GFP_KERNEL);
	अगर (!new_subpart)
		वापस -ENOMEM;

	अगर (*partdef == '-') अणु
		new_subpart->size = (sector_t)(~0ULL);
		partdef++;
	पूर्ण अन्यथा अणु
		new_subpart->size = (sector_t)memparse(partdef, &partdef);
		अगर (new_subpart->size < (sector_t)PAGE_SIZE) अणु
			pr_warn("cmdline partition size is invalid.");
			ret = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (*partdef == '@') अणु
		partdef++;
		new_subpart->from = (sector_t)memparse(partdef, &partdef);
	पूर्ण अन्यथा अणु
		new_subpart->from = (sector_t)(~0ULL);
	पूर्ण

	अगर (*partdef == '(') अणु
		पूर्णांक length;
		अक्षर *next = म_अक्षर(++partdef, ')');

		अगर (!next) अणु
			pr_warn("cmdline partition format is invalid.");
			ret = -EINVAL;
			जाओ fail;
		पूर्ण

		length = min_t(पूर्णांक, next - partdef,
			       माप(new_subpart->name) - 1);
		म_नकलन(new_subpart->name, partdef, length);
		new_subpart->name[length] = '\0';

		partdef = ++next;
	पूर्ण अन्यथा
		new_subpart->name[0] = '\0';

	new_subpart->flags = 0;

	अगर (!म_भेदन(partdef, "ro", 2)) अणु
		new_subpart->flags |= PF_RDONLY;
		partdef += 2;
	पूर्ण

	अगर (!म_भेदन(partdef, "lk", 2)) अणु
		new_subpart->flags |= PF_POWERUP_LOCK;
		partdef += 2;
	पूर्ण

	*subpart = new_subpart;
	वापस 0;
fail:
	kमुक्त(new_subpart);
	वापस ret;
पूर्ण

अटल व्योम मुक्त_subpart(काष्ठा cmdline_parts *parts)
अणु
	काष्ठा cmdline_subpart *subpart;

	जबतक (parts->subpart) अणु
		subpart = parts->subpart;
		parts->subpart = subpart->next_subpart;
		kमुक्त(subpart);
	पूर्ण
पूर्ण

अटल पूर्णांक parse_parts(काष्ठा cmdline_parts **parts, स्थिर अक्षर *bdevdef)
अणु
	पूर्णांक ret = -EINVAL;
	अक्षर *next;
	पूर्णांक length;
	काष्ठा cmdline_subpart **next_subpart;
	काष्ठा cmdline_parts *newparts;
	अक्षर buf[BDEVNAME_SIZE + 32 + 4];

	*parts = शून्य;

	newparts = kzalloc(माप(काष्ठा cmdline_parts), GFP_KERNEL);
	अगर (!newparts)
		वापस -ENOMEM;

	next = म_अक्षर(bdevdef, ':');
	अगर (!next) अणु
		pr_warn("cmdline partition has no block device.");
		जाओ fail;
	पूर्ण

	length = min_t(पूर्णांक, next - bdevdef, माप(newparts->name) - 1);
	म_नकलन(newparts->name, bdevdef, length);
	newparts->name[length] = '\0';
	newparts->nr_subparts = 0;

	next_subpart = &newparts->subpart;

	जबतक (next && *(++next)) अणु
		bdevdef = next;
		next = म_अक्षर(bdevdef, ',');

		length = (!next) ? (माप(buf) - 1) :
			min_t(पूर्णांक, next - bdevdef, माप(buf) - 1);

		म_नकलन(buf, bdevdef, length);
		buf[length] = '\0';

		ret = parse_subpart(next_subpart, buf);
		अगर (ret)
			जाओ fail;

		newparts->nr_subparts++;
		next_subpart = &(*next_subpart)->next_subpart;
	पूर्ण

	अगर (!newparts->subpart) अणु
		pr_warn("cmdline partition has no valid partition.");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	*parts = newparts;

	वापस 0;
fail:
	मुक्त_subpart(newparts);
	kमुक्त(newparts);
	वापस ret;
पूर्ण

व्योम cmdline_parts_मुक्त(काष्ठा cmdline_parts **parts)
अणु
	काष्ठा cmdline_parts *next_parts;

	जबतक (*parts) अणु
		next_parts = (*parts)->next_parts;
		मुक्त_subpart(*parts);
		kमुक्त(*parts);
		*parts = next_parts;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cmdline_parts_मुक्त);

पूर्णांक cmdline_parts_parse(काष्ठा cmdline_parts **parts, स्थिर अक्षर *cmdline)
अणु
	पूर्णांक ret;
	अक्षर *buf;
	अक्षर *pbuf;
	अक्षर *next;
	काष्ठा cmdline_parts **next_parts;

	*parts = शून्य;

	next = pbuf = buf = kstrdup(cmdline, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	next_parts = parts;

	जबतक (next && *pbuf) अणु
		next = म_अक्षर(pbuf, ';');
		अगर (next)
			*next = '\0';

		ret = parse_parts(next_parts, pbuf);
		अगर (ret)
			जाओ fail;

		अगर (next)
			pbuf = ++next;

		next_parts = &(*next_parts)->next_parts;
	पूर्ण

	अगर (!*parts) अणु
		pr_warn("cmdline partition has no valid partition.");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	ret = 0;
करोne:
	kमुक्त(buf);
	वापस ret;

fail:
	cmdline_parts_मुक्त(parts);
	जाओ करोne;
पूर्ण
EXPORT_SYMBOL(cmdline_parts_parse);

काष्ठा cmdline_parts *cmdline_parts_find(काष्ठा cmdline_parts *parts,
					 स्थिर अक्षर *bdev)
अणु
	जबतक (parts && म_भेदन(bdev, parts->name, माप(parts->name)))
		parts = parts->next_parts;
	वापस parts;
पूर्ण
EXPORT_SYMBOL(cmdline_parts_find);

/*
 *  add_part()
 *    0 success.
 *    1 can not add so many partitions.
 */
पूर्णांक cmdline_parts_set(काष्ठा cmdline_parts *parts, sector_t disk_size,
		      पूर्णांक slot,
		      पूर्णांक (*add_part)(पूर्णांक, काष्ठा cmdline_subpart *, व्योम *),
		      व्योम *param)
अणु
	sector_t from = 0;
	काष्ठा cmdline_subpart *subpart;

	क्रम (subpart = parts->subpart; subpart;
	     subpart = subpart->next_subpart, slot++) अणु
		अगर (subpart->from == (sector_t)(~0ULL))
			subpart->from = from;
		अन्यथा
			from = subpart->from;

		अगर (from >= disk_size)
			अवरोध;

		अगर (subpart->size > (disk_size - from))
			subpart->size = disk_size - from;

		from += subpart->size;

		अगर (add_part(slot, subpart, param))
			अवरोध;
	पूर्ण

	वापस slot;
पूर्ण
EXPORT_SYMBOL(cmdline_parts_set);
